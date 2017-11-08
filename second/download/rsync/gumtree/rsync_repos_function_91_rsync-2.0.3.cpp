void send_token(int f,int token,struct map_struct *buf,int offset,
		int n,int toklen)
{
  if (!do_compression) {
    simple_send_token(f,token,buf,offset,n);
  } else {
    send_deflated_token(f, token, buf, offset, n, toklen);
  }
}