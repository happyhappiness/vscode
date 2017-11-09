static int32 recv_deflated_token(int f, char **data)
{
	static int init_done;
	static int32 saved_flag;
	int32 n, flag;
	int r;

	for (;;) {
		switch (recv_state) {
		case r_init:
			if (!init_done) {
				rx_strm.next_out = NULL;
				rx_strm.zalloc = NULL;
				rx_strm.zfree = NULL;
				if (inflateInit2(&rx_strm, -15) != Z_OK) {
					rprintf(FERROR, "inflate init failed\n");
					exit_cleanup(RERR_PROTOCOL);
				}
				if (!(cbuf = new_array(char, MAX_DATA_COUNT))
				    || !(dbuf = new_array(char, AVAIL_OUT_SIZE(CHUNK_SIZE))))
					out_of_memory("recv_deflated_token");
				init_done = 1;
			} else {
				inflateReset(&rx_strm);
			}
			recv_state = r_idle;
			rx_token = 0;
			break;

		case r_idle:
		case r_inflated:
			if (saved_flag) {
				flag = saved_flag & 0xff;
				saved_flag = 0;
			} else
				flag = read_byte(f);
			if ((flag & 0xC0) == DEFLATED_DATA) {
				n = ((flag & 0x3f) << 8) + read_byte(f);
				read_buf(f, cbuf, n);
				rx_strm.next_in = (Bytef *)cbuf;
				rx_strm.avail_in = n;
				recv_state = r_inflating;
				break;
			}
			if (recv_state == r_inflated) {
				/* check previous inflated stuff ended correctly */
				rx_strm.avail_in = 0;
				rx_strm.next_out = (Bytef *)dbuf;
				rx_strm.avail_out = AVAIL_OUT_SIZE(CHUNK_SIZE);
				r = inflate(&rx_strm, Z_SYNC_FLUSH);
				n = AVAIL_OUT_SIZE(CHUNK_SIZE) - rx_strm.avail_out;
				/*
				 * Z_BUF_ERROR just means no progress was
				 * made, i.e. the decompressor didn't have
				 * any pending output for us.
				 */
				if (r != Z_OK && r != Z_BUF_ERROR) {
					rprintf(FERROR, "inflate flush returned %d (%d bytes)\n",
						r, n);
					exit_cleanup(RERR_STREAMIO);
				}
				if (n != 0 && r != Z_BUF_ERROR) {
					/* have to return some more data and
					   save the flag for later. */
					saved_flag = flag + 0x10000;
					*data = dbuf;
					return n;
				}
				/*
				 * At this point the decompressor should
				 * be expecting to see the 0, 0, ff, ff bytes.
				 */
				if (!inflateSyncPoint(&rx_strm)) {
					rprintf(FERROR, "decompressor lost sync!\n");
					exit_cleanup(RERR_STREAMIO);
				}
				rx_strm.avail_in = 4;
				rx_strm.next_in = (Bytef *)cbuf;
				cbuf[0] = cbuf[1] = 0;
				cbuf[2] = cbuf[3] = 0xff;
				inflate(&rx_strm, Z_SYNC_FLUSH);
				recv_state = r_idle;
			}
			if (flag == END_FLAG) {
				/* that's all folks */
				recv_state = r_init;
				return 0;
			}

			/* here we have a token of some kind */
			if (flag & TOKEN_REL) {
				rx_token += flag & 0x3f;
				flag >>= 6;
			} else
				rx_token = read_int(f);
			if (flag & 1) {
				rx_run = read_byte(f);
				rx_run += read_byte(f) << 8;
				recv_state = r_running;
			}
			return -1 - rx_token;

		case r_inflating:
			rx_strm.next_out = (Bytef *)dbuf;
			rx_strm.avail_out = AVAIL_OUT_SIZE(CHUNK_SIZE);
			r = inflate(&rx_strm, Z_NO_FLUSH);
			n = AVAIL_OUT_SIZE(CHUNK_SIZE) - rx_strm.avail_out;
			if (r != Z_OK) {
				rprintf(FERROR, "inflate returned %d (%d bytes)\n", r, n);
				exit_cleanup(RERR_STREAMIO);
			}
			if (rx_strm.avail_in == 0)
				recv_state = r_inflated;
			if (n != 0) {
				*data = dbuf;
				return n;
			}
			break;

		case r_running:
			++rx_token;
			if (--rx_run == 0)
				recv_state = r_idle;
			return -1 - rx_token;
		}
	}
}