(flush == Z_FINISH && iso9660->zisofs.allzero &&
		    avail + zstrm->total_in == ZF_BLOCK_SIZE) {
			if (iso9660->zisofs.block_offset !=
			    file->cur_content->size) {
				int64_t diff;

				r = wb_set_offset(a,
				    file->cur_content->offset_of_temp +
				        iso9660->zisofs.block_offset);
				if (r != ARCHIVE_OK)
					return (r);
				diff = file->cur_content->size -
				    iso9660->zisofs.block_offset;
				file->cur_content->size -= diff;
				iso9660->zisofs.total_size -= diff;
			}
			zstrm->avail_in = 0;
		}