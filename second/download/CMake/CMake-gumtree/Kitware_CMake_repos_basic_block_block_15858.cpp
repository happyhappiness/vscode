{
			if (wb_write_to_temp(a, buff, ts) != ARCHIVE_OK)
				return (ARCHIVE_FATAL);
			iso9660->cur_file->cur_content->size += ts;
		}