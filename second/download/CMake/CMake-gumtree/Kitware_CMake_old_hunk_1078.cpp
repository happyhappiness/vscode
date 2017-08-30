	    offset >= file->offset) ||

	    offset < iso9660->current_position ||

	    (((uint64_t)file->ce_offset) + file->ce_size)

	      > iso9660->logical_block_size ||

	    offset + file->ce_offset + file->ce_size

		  > iso9660->volume_size) {

		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,

