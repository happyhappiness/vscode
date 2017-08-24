{
					if (last)
						goto failed;/* Truncated data.*/
					ds->loop = i;
					ds->state = ST_RD_LITERAL_3;
					return (ARCHIVE_OK);
				}