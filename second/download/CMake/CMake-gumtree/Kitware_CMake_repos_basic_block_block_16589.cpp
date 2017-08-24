(ret == ARCHIVE_OK) {
		/*
		 * Change the boot file content from zisofs'ed data
		 * to plain data.
		 */
		file->content.offset_of_temp = new_offset;
		file->content.size = file->zisofs.uncompressed_size;
		archive_entry_set_size(file->entry, file->content.size);
		/* Set to be no zisofs. */
		file->zisofs.header_size = 0;
		file->zisofs.log2_bs = 0;
		file->zisofs.uncompressed_size = 0;
		r = wb_write_padding_to_temp(a, file->content.size);
		if (r < 0)
			ret = ARCHIVE_FATAL;
	}