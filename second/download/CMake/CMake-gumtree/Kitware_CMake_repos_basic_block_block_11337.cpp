{
					ds->r0 = archive_le32dec(ds->rbytes);
					if (ds->r0 < 0)
						goto failed;
					ds->state = ST_RD_R1;
				}