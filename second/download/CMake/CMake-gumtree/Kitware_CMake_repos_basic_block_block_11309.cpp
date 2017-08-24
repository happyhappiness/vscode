(!r) {
				ds->state = ST_MAIN_TREE_REM;
				if (last)
					goto failed;
				return (ARCHIVE_OK);
			}