{
			if (__archive_read_consume(a, skip) < 0)
				return (ARCHIVE_FATAL);
			cab->cab_offset =
			    cab->entry_cffolder->cfdata_offset_in_cab;
		}