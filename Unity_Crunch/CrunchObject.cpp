#include "CrunchObject.h"
#include <vector>
#include "crnlib.h"
#include "crunch.h"

CrunchObject::CrunchObject()
{
	pDDS_file_data = NULL;
}

CrunchObject::~CrunchObject()
{
	//If dds file contains data, free the data 
	if (pDDS_file_data != NULL)
		crn_free_block(pDDS_file_data);
}

void CrunchObject::compress(const char * filepath, const int width, const int height, const bool quiet) const
{
	//vector used to add parameters to. List of optional parameters are listed in the crunch.h file.
	//More parameters can added in the future.
	std::vector<const char*> params;
	params.push_back("-file");
	params.push_back(filepath);
	params.push_back("-outsamedir");
	params.push_back("-yflip");

	//Whether to print out debug info on console
	if (quiet)
	{
		params.push_back("-quiet");
		params.push_back("-noprogress");
	}

	std::string string_width = std::to_string(width);
	const char* w = string_width.c_str();
	std::string string_height = std::to_string(height);
	const char* h = string_height.c_str();

	if (width != NULL && height != NULL)
	{
		params.push_back("-rescale");
		params.push_back(w);
		params.push_back(h);
	}

	//pass in parameters and size of vector as number of parameters
	crunch::main_internal(params.size(), &params[0]);
}

void* CrunchObject::decompress(const char* filepath)
{
	filesize = 0;
	crn_uint32 src_file_size;
	crn_uint8* pSrc_file_data = read_file_into_buffer(filepath, src_file_size);
	if (!pSrc_file_data)
		return NULL;

	// Decompress/transcode CRN to DDS.
	printf("Decompressing CRN to DDS\n");

	// Transcode the CRN file to a DDS file in memory.
	crn_uint32 dds_file_size = src_file_size;
	pDDS_file_data = crn_decompress_crn_to_dds(pSrc_file_data, dds_file_size);
	filesize = dds_file_size;

	if (!pDDS_file_data) {
		free(pSrc_file_data);

		return NULL;
	}
	return pDDS_file_data;
}

//Test decompressing CRN
const int CrunchObject::decompress_write(const char* filepath) const
{
	char drive_buf[_MAX_DRIVE], dir_buf[_MAX_DIR], fname_buf[_MAX_FNAME], ext_buf[_MAX_EXT];
	_splitpath_s(filepath, drive_buf, _MAX_DRIVE, dir_buf, _MAX_DIR, fname_buf, _MAX_FNAME, ext_buf, _MAX_EXT);

	crn_uint32 src_file_size;
	crn_uint8* pSrc_file_data = read_file_into_buffer(filepath, src_file_size);
	if (!pSrc_file_data)
		return error("Unable to read source file\n");

	// Decompress/transcode CRN to DDS.
	printf("Decompressing CRN to DDS\n");

	// Transcode the CRN file to a DDS file in memory.
	crn_uint32 dds_file_size = src_file_size;
	void* pDDS_file_data = crn_decompress_crn_to_dds(pSrc_file_data, dds_file_size);
	if (!pDDS_file_data) {
		free(pSrc_file_data);
		return error("Failed decompressing CRN file!\n");
	}

	// Now write the DDS file to disk.
	char dst_filename[FILENAME_MAX];
	sprintf_s(dst_filename, sizeof(dst_filename), "%s%s%s.dds", drive_buf, dir_buf, fname_buf);

	printf("Writing file: %s\n", dst_filename);
	FILE* pFile = fopen(dst_filename, "wb");
	if ((!pFile) || (fwrite(pDDS_file_data, dds_file_size, 1, pFile) != 1) || (fclose(pFile) == EOF)) {
		crn_free_block(pDDS_file_data);
		free(pSrc_file_data);
		return error("Failed writing to output file!\n");
	}
	crn_free_block(pDDS_file_data);
	return 0;
}

//Used to help convert decompressed dds file into array of bytes
const int CrunchObject::get_dds_filesize() const
{
	return filesize;
}