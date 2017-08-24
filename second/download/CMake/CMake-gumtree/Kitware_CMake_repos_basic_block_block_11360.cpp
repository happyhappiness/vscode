{
				const unsigned char *s;
				int l;

				l = copy_len;
				if (copy_pos > w_pos) {
					if (l > w_size - copy_pos)
						l = w_size - copy_pos;
				} else {
					if (l > w_size - w_pos)
						l = w_size - w_pos;
				}
				if (noutp + l >= endp)
					l = (int)(endp - noutp);
				s = w_buff + copy_pos;
				if (l >= 8 && ((copy_pos + l < w_pos)
				  || (w_pos + l < copy_pos))) {
					memcpy(w_buff + w_pos, s, l);
					memcpy(noutp, s, l);
				} else {
					unsigned char *d;
					int li;

					d = w_buff + w_pos;
					for (li = 0; li < l; li++)
						noutp[li] = d[li] = s[li];
				}
				noutp += l;
				copy_pos = (copy_pos + l) & w_mask;
				w_pos = (w_pos + l) & w_mask;
				block_bytes_avail -= l;
				if (copy_len <= l)
					/* A copy of current pattern ended. */
					break;
				copy_len -= l;
				if (noutp >= endp) {
					/* Output buffer is empty. */
					state = ST_COPY;
					goto next_data;
				}
			}