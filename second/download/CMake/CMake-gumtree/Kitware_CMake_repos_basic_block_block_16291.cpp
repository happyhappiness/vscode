{
		isoent->file->content.location = location;
		block = (int)((archive_entry_size(isoent->file->entry) +
		    LOGICAL_BLOCK_SIZE -1) >> LOGICAL_BLOCK_BITS);
		location += block;
		iso9660->total_file_block += block;
	}