{
			/*
			 * Save the information of one zisofs block.
			 */
			iso9660->zisofs.block_pointers_idx ++;
			archive_le32enc(&(iso9660->zisofs.block_pointers[
			    iso9660->zisofs.block_pointers_idx]),
				(uint32_t)iso9660->zisofs.total_size);
			r = zisofs_init_zstream(a);
			if (r != ARCHIVE_OK)
				return (ARCHIVE_FATAL);
			iso9660->zisofs.allzero = 1;
			iso9660->zisofs.block_offset = file->cur_content->size;
		}