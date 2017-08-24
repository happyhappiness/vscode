{
					if (strm->avail_in <= 0) {
						if (last)
							goto failed;
						return (ARCHIVE_OK);
					}
					ds->rbytes[ds->rbytes_avail++] =
					    *strm->next_in++;
					strm->avail_in--;
				}