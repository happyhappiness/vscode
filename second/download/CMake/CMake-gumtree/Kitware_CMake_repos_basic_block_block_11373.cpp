(!lzx_br_read_ahead(strm, &bre, offbits)) {
					state = ST_OFFSET;
					if (last)
						goto failed;
					goto next_data;
				}