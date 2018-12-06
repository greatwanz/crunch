using System;

namespace WS
{
    public class ManagedCrunchObject
    {
        private IntPtr native_instance_;

        public ManagedCrunchObject()
        {
            native_instance_ = ManagedCrunchWrapper.new_CrunchObject();
        }

        public void delete()
        {
            ManagedCrunchWrapper.delete_CrunchObject(native_instance_);
        }

        public void compress(string filepath, int width = 0, int height = 0)
        {
            ManagedCrunchWrapper.compress(native_instance_, filepath, width, height);
        }

        public IntPtr decompress(string filepath)
        {
            return ManagedCrunchWrapper.decompress(native_instance_, filepath);
        }

        public int get_dds_filesize()
        {
            return ManagedCrunchWrapper.get_dds_filesize(native_instance_);
        }
    }
}
