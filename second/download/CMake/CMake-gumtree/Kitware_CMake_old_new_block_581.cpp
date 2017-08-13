{
				archive_set_error(&a->archive, errno,
						"Can't open %s", path);
				r = ARCHIVE_WARN;
			}