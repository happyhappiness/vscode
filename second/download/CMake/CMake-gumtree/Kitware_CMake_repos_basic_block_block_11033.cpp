(strncmp(filename, "#1/", 3) == 0)
			a->archive.archive_format = ARCHIVE_FORMAT_AR_BSD;
		else if (strchr(filename, '/') != NULL)
			a->archive.archive_format = ARCHIVE_FORMAT_AR_GNU;
		else if (strncmp(filename, "__.SYMDEF", 9) == 0)
			a->archive.archive_format = ARCHIVE_FORMAT_AR_BSD