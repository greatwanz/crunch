# crunch

A fork of Unity crunch compressor that allows for compression and decompression of textures at runtime. Managed folder in Unity_Crunch contains wrapper classes that can be used in Unity and C#.

ImageHelper.cs can be used to decompress .crn files to .dds files, which is useful in case the crunch file is incompatible with a version of Unity.

Crunch compression is performed on a separate thread, which allows the main thread to continue executing while performing the compression.
