archive_string_sprintf(&zip->format_name, "ZIP %d.%d (%s)",
	    version / 10, version % 10,
	    compression_name(zip->entry->compression))