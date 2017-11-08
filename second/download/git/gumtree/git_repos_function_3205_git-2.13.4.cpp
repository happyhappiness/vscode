static void set_zip_dir_data_desc(struct zip_dir_header *header,
				  unsigned long size,
				  unsigned long compressed_size,
				  unsigned long crc)
{
	copy_le32(header->crc32, crc);
	copy_le32(header->compressed_size, compressed_size);
	copy_le32(header->size, size);
}