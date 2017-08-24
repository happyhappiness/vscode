{
						state = ST_COPY_DATA;
						ds->copy_len = copy_len - l;
						ds->copy_pos =
						    (copy_pos + l) & w_mask;
					}