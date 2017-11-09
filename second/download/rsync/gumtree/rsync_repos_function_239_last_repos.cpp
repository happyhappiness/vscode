static void simple_send_token(int f, int32 token, struct map_struct *buf,
			      OFF_T offset, int32 n)
{
	if (n > 0) {
		int32 len = 0;
		while (len < n) {
			int32 n1 = MIN(CHUNK_SIZE, n-len);
			write_int(f, n1);
			write_buf(f, map_ptr(buf, offset+len, n1), n1);
			len += n1;
		}
	}
	/* a -2 token means to send data only and no token */
	if (token != -2)
		write_int(f, -(token+1));
}