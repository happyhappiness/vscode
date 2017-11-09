void see_token(char *data, int32 toklen)
{
	if (do_compression == 1)
		see_deflate_token(data, toklen);
}