{
			archive_set_error(&a->archive, errno, "chdir() failure");
			ret = ARCHIVE_FATAL;
		}