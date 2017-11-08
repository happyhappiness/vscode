static void write_zip_data_desc(unsigned long size,
				unsigned long compressed_size,
				unsigned long crc)
{
	struct zip_data_desc trailer;

	copy_le32(trailer.magic, 0x08074b50);
	copy_le32(trailer.crc32, crc);
	copy_le32(trailer.compressed_size, compressed_size);
	copy_le32(trailer.size, size);
	write_or_die(1, &trailer, ZIP_DATA_DESC_SIZE);
}