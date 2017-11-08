int32 recv_token(int f, char **data)
{
	int tok;

	if (!do_compression) {
		tok = simple_recv_token(f,data);
	} else {
		tok = recv_deflated_token(f, data);
	}
	return tok;
}