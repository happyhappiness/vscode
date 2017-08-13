{
				zip->ppmd7_stat = -1;
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Failed to initialize PPMd range decorder");
				return (ARCHIVE_FAILED);
			}