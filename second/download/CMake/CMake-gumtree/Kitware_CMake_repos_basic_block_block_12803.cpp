{
		archive_entry_set_rdevmajor(entry, (dev_t)
		    tar_atol(header->rdevmajor, sizeof(header->rdevmajor)));
		archive_entry_set_rdevminor(entry, (dev_t)
		    tar_atol(header->rdevminor, sizeof(header->rdevminor)));
	}