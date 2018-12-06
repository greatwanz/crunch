#include "CrunchObject.h"
#define LIBRARY_EXPORT __declspec(dllexport)

extern "C" LIBRARY_EXPORT CrunchObject* new_CrunchObject();
extern "C" LIBRARY_EXPORT void delete_CrunchObject(CrunchObject* instance);
extern "C" LIBRARY_EXPORT void compress(CrunchObject* instance, char * filepath, int width, int height);
extern "C" LIBRARY_EXPORT void* decompress(CrunchObject* instance, char* filepath);
extern "C" LIBRARY_EXPORT int get_dds_filesize(CrunchObject* instance);