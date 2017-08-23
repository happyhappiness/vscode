{
			archive_set_error(&a->archive, ENOMEM,
			    "No memory for CAB reader");
			*avail = ARCHIVE_FATAL;
			return (NULL);
		}