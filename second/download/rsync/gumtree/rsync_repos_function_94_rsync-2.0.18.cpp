static void simple_send_token(int f,int token,
			      struct map_struct *buf,OFF_T offset,int n)
{
	if (n > 0) {
		int l = 0;
		while (l < n) {
			int n1 = MIN(CHUNK_SIZE,n-l);
			write_int(f,n1);
			write_buf(f,map_ptr(buf,offset+l,n1),n1);
			l += n1;
		}
	}
	/* a -2 token means to send data only and no token */
	if (token != -2) {
		write_int(f,-(token+1));
	}
}