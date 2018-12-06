#include <stdlib.h>

/// /// <summary>
/// File: CrunchObject.h - Compress and decompress image files into crunch format
/// </summary>
class CrunchObject
{
	public: 
	CrunchObject();
	~CrunchObject(void);

	//Compresses image files into .crn. More optional parameters may be added in the future.
	void compress(const char * filepath, const int width = NULL,const int height = NULL,const bool quiet = false) const;
	//Decompresses a .crn file. Returns a pointer to the decompressed dds file data.
	void* decompress(const char* filepath);
	//Get the file size of the resultant .dds file after it is decompressed.
	const int get_dds_filesize() const;
	//Test decompression, provide filepath of file to decompress, decompresses to same path
	const int decompress_write(const char* filepath) const;

	private:
	//filesize of the image
	int filesize;
	//pointer to the dds file data after decompression
	void* pDDS_file_data;
};