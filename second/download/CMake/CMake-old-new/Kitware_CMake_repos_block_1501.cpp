{
				archive_set_error(&a->archive, EINVAL,
				    "Can't find string table");
				return (ARCHIVE_WARN);
			}