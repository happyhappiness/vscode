{
			tar->realsize = tar_atol10(value, strlen(value));
			archive_entry_set_size(entry, tar->realsize);
		}