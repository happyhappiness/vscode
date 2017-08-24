{
				ds->state = ST_LENGTH_TREE;
				if (last)
					goto failed;
				return (ARCHIVE_OK);
			}