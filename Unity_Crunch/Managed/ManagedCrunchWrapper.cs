using System.Runtime.InteropServices;
using System;

namespace WS
{
    public static class ManagedCrunchWrapper
    {
        [DllImport("Unity_Crunch")]
        public static extern IntPtr new_CrunchObject();

        [DllImport("Unity_Crunch")]
        public static extern void delete_CrunchObject(IntPtr instance);

        [DllImport("Unity_Crunch")]
        public static extern void compress(IntPtr instance, string filepath, int width, int height);

        [DllImport("Unity_Crunch")]
        public static extern IntPtr decompress(IntPtr instance, string filepath);

        [DllImport("Unity_Crunch")]
        public static extern int get_dds_filesize(IntPtr instance);
    }
}