static void simple_send_token(int f,int token,
			      struct map_struct *buf,OFF_T offset,int n)
{
	extern int write_batch; /* dw */
	int hold_int; /* dw */

	if (n > 0) {
		int l = 0;
		while (l < n) {
			int n1 = MIN(CHUNK_SIZE,n-l);
			write_int(f,n1);
			write_buf(f,map_ptr(buf,offset+l,n1),n1);
			if (write_batch) {
			    write_batch_delta_file( (char *) &n1, sizeof(int) );
			    write_batch_delta_file(map_ptr(buf,offset+l,n1),n1);
			}
			l += n1;
		}
	}
	/* a -2 token means to send data only and no token */
	if (token != -2) {
		write_int(f,-(token+1));
		if (write_batch) {
		    hold_int = -(token+1);
		    write_batch_delta_file( (char *) &hold_int, sizeof(int) );
		}
	}
}