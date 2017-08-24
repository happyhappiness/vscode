(iso9660->el_torito.boot != NULL) {
		file = iso9660->el_torito.boot->file;
		blocks = file->content.blocks;
		offset = file->content.offset_of_temp;
		if (offset != 0) {
			r = write_file_contents(a, offset,
			    blocks << LOGICAL_BLOCK_BITS);
			if (r < 0)
				return (r);
			blocks = 0;
			offset = 0;
		}
	}