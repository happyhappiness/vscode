void see_token(char *data, int toklen)
{
	if (do_compression)
		see_deflate_token(data, toklen);
}