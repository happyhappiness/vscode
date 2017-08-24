{
				ds->state = ST_RD_ALIGNED_OFFSET;
				if (last)
					goto failed;
				return (ARCHIVE_OK);
			}