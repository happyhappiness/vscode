void send_token(int f, int32 token, struct map_struct *buf, OFF_T offset,
		int32 n, int32 toklen)
{
	if (!do_compression)
		simple_send_token(f, token, buf, offset, n);
	else
		send_deflated_token(f, token, buf, offset, n, toklen);
}