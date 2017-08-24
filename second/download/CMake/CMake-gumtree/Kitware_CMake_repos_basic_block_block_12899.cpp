{
		tar->realsize
		    = tar_atol(header->realsize, sizeof(header->realsize));
		archive_entry_set_size(entry, tar->realsize);
	}