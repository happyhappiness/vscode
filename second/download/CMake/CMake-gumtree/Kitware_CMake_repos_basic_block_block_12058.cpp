{
				int l;

				l = copy_len;
				if (copy_pos > w_pos) {
					if (l > w_size - copy_pos)
						l = w_size - copy_pos;
				} else {
					if (l > w_size - w_pos)
						l = w_size - w_pos;
				}
				if ((copy_pos + l < w_pos)
				    || (w_pos + l < copy_pos)) {
					/* No overlap. */
					memcpy(w_buff + w_pos,
					    w_buff + copy_pos, l);
				} else {
					const unsigned char *s;
					unsigned char *d;
					int li;

					d = w_buff + w_pos;
					s = w_buff + copy_pos;
					for (li = 0; li < l-1;) {
						d[li] = s[li];li++;
						d[li] = s[li];li++;
					}
					if (li < l)
						d[li] = s[li];
				}
				w_pos += l;
				if (w_pos == w_size) {
					w_pos = 0;
					lzh_emit_window(strm, w_size);
					if (copy_len <= l)
						state = ST_GET_LITERAL;
					else {
						state = ST_COPY_DATA;
						ds->copy_len = copy_len - l;
						ds->copy_pos =
						    (copy_pos + l) & w_mask;
					}
					goto next_data;
				}
				if (copy_len <= l)
					/* A copy of current pattern ended. */
					break;
				copy_len -= l;
				copy_pos = (copy_pos + l) & w_mask;
			}