{
		isoent->file->content.location = location;
		size = fd_boot_image_size(iso9660->el_torito.media_type);
		if (size == 0)
			size = (size_t)archive_entry_size(isoent->file->entry);
		block = ((int)size + LOGICAL_BLOCK_SIZE -1)
		    >> LOGICAL_BLOCK_BITS;
		location += block;
		iso9660->total_file_block += block;
		isoent->file->content.blocks = block;
	}