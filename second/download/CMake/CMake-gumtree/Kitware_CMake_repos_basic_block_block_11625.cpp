{
#ifdef HAVE_ZLIB_H
		struct zisofs  *zisofs;

		zisofs = &iso9660->entry_zisofs;
		zisofs->initialized = 0;
		zisofs->pz_log2_bs = file->pz_log2_bs;
		zisofs->pz_uncompressed_size = file->pz_uncompressed_size;
		zisofs->pz_offset = 0;
		zisofs->header_avail = 0;
		zisofs->header_passed = 0;
		zisofs->block_pointers_avail = 0;
#endif
		archive_entry_set_size(entry, file->pz_uncompressed_size);
	}