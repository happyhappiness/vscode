(strcmp(name, "xar") == 0)
			xar->xmlsts = XAR;
		else
			if (unknowntag_start(a, xar, name) != ARCHIVE_OK)
				return (ARCHIVE_FATAL);