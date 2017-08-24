{
					skip = p - (const char *)h;
					__archive_read_consume(a, skip);
					skipped += skip;
					if (skipped > 0) {
						archive_set_error(&a->archive,
						    0,
						    "Skipped %d bytes before "
						    "finding valid header",
						    (int)skipped);
						return (ARCHIVE_WARN);
					}
					return (ARCHIVE_OK);
				}