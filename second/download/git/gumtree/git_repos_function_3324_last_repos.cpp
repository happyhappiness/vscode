static void write_zip_data_desc(unsigned long size,
				unsigned long compressed_size,
				unsigned long crc)
{
	if (size >= 0xffffffff || compressed_size >= 0xffffffff) {
		struct zip64_data_desc trailer;
		copy_le32(trailer.magic, 0x08074b50);
		copy_le32(trailer.crc32, crc);
		copy_le64(trailer.compressed_size, compressed_size);
		copy_le64(trailer.size, size);
		write_or_die(1, &trailer, ZIP64_DATA_DESC_SIZE);
		zip_offset += ZIP64_DATA_DESC_SIZE;
	} else {
		struct zip_data_desc trailer;
		copy_le32(trailer.magic, 0x08074b50);
		copy_le32(trailer.crc32, crc);
		copy_le32(trailer.compressed_size, compressed_size);
		copy_le32(trailer.size, size);
		write_or_die(1, &trailer, ZIP_DATA_DESC_SIZE);
		zip_offset += ZIP_DATA_DESC_SIZE;
	}
}