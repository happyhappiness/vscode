{
				ds->state = ST_RD_PRE_MAIN_TREE_256;
				if (last)
					goto failed;
				return (ARCHIVE_OK);
			}