static void
send_deflated_token(int f, int token,
		    struct map_struct *buf, OFF_T offset, int nb, int toklen)
{
	int n, r;
	static int init_done, flush_pending;
	extern int write_batch;
	char temp_byte;

	if (last_token == -1) {
		/* initialization */
		if (!init_done) {
			tx_strm.next_in = NULL;
			tx_strm.zalloc = NULL;
			tx_strm.zfree = NULL;
			if (deflateInit2(&tx_strm, compression_level,
					 Z_DEFLATED, -15, 8,
					 Z_DEFAULT_STRATEGY) != Z_OK) {
				rprintf(FERROR, "compression init failed\n");
				exit_cleanup(RERR_STREAMIO);
			}
			if ((obuf = new_array(char, OBUF_SIZE)) == NULL)
				out_of_memory("send_deflated_token");
			init_done = 1;
		} else
			deflateReset(&tx_strm);
		last_run_end = 0;
		run_start = token;
		flush_pending = 0;

	} else if (last_token == -2) {
		run_start = token;

	} else if (nb != 0 || token != last_token + 1
		   || token >= run_start + 65536) {
		/* output previous run */
		r = run_start - last_run_end;
		n = last_token - run_start;
		if (r >= 0 && r <= 63) {
			write_byte(f, (n==0? TOKEN_REL: TOKENRUN_REL) + r);
			if (write_batch) {
				temp_byte = (char)( (n==0? TOKEN_REL: TOKENRUN_REL) + r);
				write_batch_delta_file(&temp_byte,sizeof(char));
			}
		} else {
			write_byte(f, (n==0? TOKEN_LONG: TOKENRUN_LONG));
			write_int(f, run_start);
			if (write_batch) {
				temp_byte = (char)(n==0? TOKEN_LONG: TOKENRUN_LONG);
				write_batch_delta_file(&temp_byte,sizeof(temp_byte));
				write_batch_delta_file((char *)&run_start,sizeof(run_start));
			}
		}
		if (n != 0) {
			write_byte(f, n);
			write_byte(f, n >> 8);
			if (write_batch) {
				write_batch_delta_file((char *)&n,sizeof(char));
				temp_byte = (char)(n >> 8);
				write_batch_delta_file(&temp_byte,sizeof(temp_byte));
			}
		}
		last_run_end = last_token;
		run_start = token;
	}

	last_token = token;

	if (nb != 0 || flush_pending) {
		/* deflate the data starting at offset */
		int flush = Z_NO_FLUSH;
		tx_strm.avail_in = 0;
		tx_strm.avail_out = 0;
		do {
			if (tx_strm.avail_in == 0 && nb != 0) {
				/* give it some more input */
				n = MIN(nb, CHUNK_SIZE);
				tx_strm.next_in = (Bytef *)
					map_ptr(buf, offset, n);
				tx_strm.avail_in = n;
				nb -= n;
				offset += n;
			}
			if (tx_strm.avail_out == 0) {
				tx_strm.next_out = (Bytef *)(obuf + 2);
				tx_strm.avail_out = MAX_DATA_COUNT;
				if (flush != Z_NO_FLUSH) {
					/*
					 * We left the last 4 bytes in the
					 * buffer, in case they are the
					 * last 4.  Move them to the front.
					 */
					memcpy(tx_strm.next_out,
					       obuf+MAX_DATA_COUNT-2, 4);
					tx_strm.next_out += 4;
					tx_strm.avail_out -= 4;
				}
			}
			if (nb == 0 && token != -2)
				flush = Z_SYNC_FLUSH;
			r = deflate(&tx_strm, flush);
			if (r != Z_OK) {
				rprintf(FERROR, "deflate returned %d\n", r);
				exit_cleanup(RERR_STREAMIO);
			}
			if (nb == 0 || tx_strm.avail_out == 0) {
				n = MAX_DATA_COUNT - tx_strm.avail_out;
				if (flush != Z_NO_FLUSH) {
					/*
					 * We have to trim off the last 4
					 * bytes of output when flushing
					 * (they are just 0, 0, ff, ff).
					 */
					n -= 4;
				}
				if (n > 0) {
					obuf[0] = DEFLATED_DATA + (n >> 8);
					obuf[1] = n;
					write_buf(f, obuf, n+2);
					if (write_batch)
						write_batch_delta_file(obuf,n+2);
				}
			}
		} while (nb != 0 || tx_strm.avail_out == 0);
		flush_pending = token == -2;
	}

	if (token == -1) {
		/* end of file - clean up */
		write_byte(f, END_FLAG);
		if (write_batch) {
			temp_byte = END_FLAG;
			write_batch_delta_file((char *)&temp_byte,sizeof(temp_byte));
		}

	} else if (token != -2) {
		/* add the data in the current block to the compressor's
		   history and hash table */
		tx_strm.next_in = (Bytef *) map_ptr(buf, offset, toklen);
		tx_strm.avail_in = toklen;
		tx_strm.next_out = (Bytef *) obuf;
		tx_strm.avail_out = AVAIL_OUT_SIZE(CHUNK_SIZE);
		r = deflate(&tx_strm, Z_INSERT_ONLY);
		if (r != Z_OK || tx_strm.avail_in != 0) {
			rprintf(FERROR, "deflate on token returned %d (%d bytes left)\n",
				r, tx_strm.avail_in);
			exit_cleanup(RERR_STREAMIO);
		}
	}
}