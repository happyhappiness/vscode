static void close_deflated_stream(struct git_istream *st)
{
	if (st->z_state == z_used)
		git_inflate_end(&st->z);
}