{
					ds->r2 = archive_le32dec(ds->rbytes);
					if (ds->r2 < 0)
						goto failed;
					/* We've gotten all repeated offsets. */
					ds->state = ST_COPY_UNCOMP1;
				}