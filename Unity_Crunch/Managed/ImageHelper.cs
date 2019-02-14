using UnityEngine;
using System.IO;
using System;
using System.Runtime.InteropServices;

public static class ImageHelper
{    
    public static Texture2D LoadTextureDXT(string absoluteTexturePath)
        {
            if (!File.Exists(absoluteTexturePath))
                return null;

            int DDS_HEADER_SIZE = 128;
            ManagedCrunchObject myObj = new ManagedCrunchObject();
            IntPtr ptr = myObj.decompress(absoluteTexturePath);
            byte[] managedArray = new byte[myObj.get_dds_filesize()];
            Marshal.Copy(ptr, managedArray, 0, managedArray.Length);
            TextureFormat textureFormat = TextureFormat.DXT1;
            byte ddsSizeCheck = managedArray[4];
            if (ddsSizeCheck != 124)
                throw new Exception("Invalid DDS DXTn texture. Unable to read");  //this header byte should be 124 for DDS image files

            int height = managedArray[13] * 256 + managedArray[12];
            int width = managedArray[17] * 256 + managedArray[16];

            byte[] dxtBytes = new byte[managedArray.Length - DDS_HEADER_SIZE];
            Buffer.BlockCopy(managedArray, DDS_HEADER_SIZE, dxtBytes, 0, managedArray.Length - DDS_HEADER_SIZE);
            Texture2D texture = new Texture2D(width, height, textureFormat, false);
            texture.LoadRawTextureData(dxtBytes);
            texture.Apply();
            myObj.delete();

            return (texture);
        }
}