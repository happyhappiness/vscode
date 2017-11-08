void see_token(char *data, int32 toklen)
{
	if (do_compression)
		see_deflate_token(data, toklen);
}