{
				archive_set_error(&a->archive, ERANGE,
				    "string table offset too large");
				return (ARCHIVE_WARN);
			}