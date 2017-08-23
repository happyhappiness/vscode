{
				archive_set_error(&a->archive, 0,
				    "Cannot extract through symlink %ls",
				    a->name);
				pn[0] = c;
				return (ARCHIVE_FAILED);
			}