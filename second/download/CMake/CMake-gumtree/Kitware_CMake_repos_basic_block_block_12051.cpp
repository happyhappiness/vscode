{
				if (last)
					goto failed;/* Truncated data. */
				ds->state = ST_RD_PT_1;
				return (ARCHIVE_OK);
			}