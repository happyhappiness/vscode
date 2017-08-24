(p[3] == '\010' && p[2] == '\007'
				    && p[1] == 'K' && p[0] == 'P') {
					if (zip->entry->flags & LA_USED_ZIP64)
						__archive_read_consume(a,
						    p - buff + 24);
					else
						__archive_read_consume(a,
						    p - buff + 16);
					return ARCHIVE_OK;
				}