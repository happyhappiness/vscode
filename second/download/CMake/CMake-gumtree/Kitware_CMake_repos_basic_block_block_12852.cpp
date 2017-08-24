{
				archive_entry_set_size(entry,
				    tar->entry_bytes_remaining);
				tar->realsize
				    = tar->entry_bytes_remaining;
			}