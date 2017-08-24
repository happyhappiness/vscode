{
			archive_entry_set_rdevmajor(entry,
			    (dev_t)tar_atol10(value, strlen(value)));
		}