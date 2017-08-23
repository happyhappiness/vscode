{
					archive_set_error(
						&filter->archive->archive,
						ENOMEM,
					    "Unable to allocate copy buffer");
					filter->fatal = 1;
					if (avail != NULL)
						*avail = ARCHIVE_FATAL;
					return (NULL);
				}