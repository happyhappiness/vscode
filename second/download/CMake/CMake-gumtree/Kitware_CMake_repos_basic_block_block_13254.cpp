{
					xar->file->link = (unsigned)atol10(attr->value,
					    strlen(attr->value));
					if (xar->file->link > 0)
						if (add_link(a, xar, xar->file) != ARCHIVE_OK) {
							return (ARCHIVE_FATAL);
						};
				}