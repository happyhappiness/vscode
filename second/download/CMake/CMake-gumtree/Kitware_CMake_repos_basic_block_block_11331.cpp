{
				int l;

				if (strm->avail_out <= 0)
					/* Output buffer is empty. */
					return (ARCHIVE_OK);
				if (strm->avail_in <= 0) {
					/* Input buffer is empty. */
					if (last)
						goto failed;
					return (ARCHIVE_OK);
				}
				l = (int)ds->block_bytes_avail;
				if (l > ds->w_size - ds->w_pos)
					l = ds->w_size - ds->w_pos;
				if (l > strm->avail_out)
					l = (int)strm->avail_out;
				if (l > strm->avail_in)
					l = (int)strm->avail_in;
				memcpy(strm->next_out, strm->next_in, l);
				memcpy(&(ds->w_buff[ds->w_pos]),
				    strm->next_in, l);
				strm->next_in += l;
				strm->avail_in -= l;
				strm->next_out += l;
				strm->avail_out -= l;
				strm->total_out += l;
				ds->w_pos = (ds->w_pos + l) & ds->w_mask;
				ds->block_bytes_avail -= l;
			}