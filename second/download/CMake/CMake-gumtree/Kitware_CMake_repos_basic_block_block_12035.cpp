{
				if (last)
					goto failed;/* Truncated data. */
				ds->state = ST_RD_LITERAL_1;
				return (ARCHIVE_OK);
			}