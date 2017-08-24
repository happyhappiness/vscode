{
				archive_set_error(&a->archive, GetLastError(),
				    "Can't FindFirstFileW");
				return (ARCHIVE_FAILED);
			}