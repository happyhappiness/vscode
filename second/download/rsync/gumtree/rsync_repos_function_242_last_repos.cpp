static void see_deflate_token(char *buf, int32 len)
{
#ifndef EXTERNAL_ZLIB
	int r;
	int32 blklen;
	unsigned char hdr[5];

	rx_strm.avail_in = 0;
	blklen = 0;
	hdr[0] = 0;
	do {
		if (rx_strm.avail_in == 0 && len != 0) {
			if (blklen == 0) {
				/* Give it a fake stored-block header. */
				rx_strm.next_in = (Bytef *)hdr;
				rx_strm.avail_in = 5;
				blklen = len;
				if (blklen > 0xffff)
					blklen = 0xffff;
				hdr[1] = blklen;
				hdr[2] = blklen >> 8;
				hdr[3] = ~hdr[1];
				hdr[4] = ~hdr[2];
			} else {
				rx_strm.next_in = (Bytef *)buf;
				rx_strm.avail_in = blklen;
				if (protocol_version >= 31) /* Newer protocols avoid a data-duplicating bug */
					buf += blklen;
				len -= blklen;
				blklen = 0;
			}
		}
		rx_strm.next_out = (Bytef *)dbuf;
		rx_strm.avail_out = AVAIL_OUT_SIZE(CHUNK_SIZE);
		r = inflate(&rx_strm, Z_SYNC_FLUSH);
		if (r != Z_OK && r != Z_BUF_ERROR) {
			rprintf(FERROR, "inflate (token) returned %d\n", r);
			exit_cleanup(RERR_STREAMIO);
		}
	} while (len || rx_strm.avail_out == 0);
#else
	buf++; len++;
	rprintf(FERROR, "Impossible error in external-zlib code (2).\n");
	exit_cleanup(RERR_STREAMIO);
#endif
}