#include "CrunchWrapper.h"

extern "C" LIBRARY_EXPORT CrunchObject* new_CrunchObject()
{
	return new CrunchObject();
}
extern "C" LIBRARY_EXPORT void delete_CrunchObject(CrunchObject* instance)
{
	delete instance;
}

extern "C" LIBRARY_EXPORT void compress(CrunchObject* instance, char * filepath, int width, int height)
{
	instance->compress(filepath, width, height,true);
}

extern "C" LIBRARY_EXPORT void* decompress(CrunchObject* instance, char* filepath)
{
	return instance->decompress(filepath);
}

extern "C" LIBRARY_EXPORT int get_dds_filesize(CrunchObject* instance)
{
	return instance->get_dds_filesize();
}