(!lzx_br_read_ahead(strm, br, 3)) {
				ds->state = ST_RD_BLOCK_TYPE;
				if (last)
					goto failed;
				return (ARCHIVE_OK);
			}