(r < 0)
				goto failed;
			else if (!r) {
				ds->state = ST_MAIN_TREE_REM;
				if (last)
					goto failed;
				return (ARCHIVE_OK);
			}