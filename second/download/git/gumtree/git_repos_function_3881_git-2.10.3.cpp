static void zlib_post_call(git_zstream *s)
{
	unsigned long bytes_consumed;
	unsigned long bytes_produced;

	bytes_consumed = s->z.next_in - s->next_in;
	bytes_produced = s->z.next_out - s->next_out;
	if (s->z.total_out != s->total_out + bytes_produced)
		die("BUG: total_out mismatch");
	if (s->z.total_in != s->total_in + bytes_consumed)
		die("BUG: total_in mismatch");

	s->total_out = s->z.total_out;
	s->total_in = s->z.total_in;
	s->next_in = s->z.next_in;
	s->next_out = s->z.next_out;
	s->avail_in -= bytes_consumed;
	s->avail_out -= bytes_produced;
}