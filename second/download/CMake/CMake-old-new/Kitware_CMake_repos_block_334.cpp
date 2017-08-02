{
				archive_set_error(&a->archive, -1,
				    "Can't restore SUID bit");
				r = ARCHIVE_WARN;
			}