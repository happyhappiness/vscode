(copy_pos > 1) {
				/* We need an additional adjustment number to
				 * the position. */
				int p = copy_pos - 1;
				if (!lzh_br_read_ahead(strm, &bre, p)) {
					if (last)
						goto failed;/* Truncated data.*/
					state = ST_GET_POS_2;
					ds->copy_len = copy_len;
					ds->copy_pos = copy_pos;
					goto next_data;
				}
				copy_pos = (1 << p) + lzh_br_bits(&bre, p);
				lzh_br_consume(&bre, p);
			}