{
					archive_set_error(&a->archive, 0,
					    "Cannot remove intervening "
					    "symlink %ls", a->name);
					pn[0] = c;
					return (ARCHIVE_FAILED);
				}