static int next_flush(struct fetch_pack_args *args, int count)
{
	int flush_limit = args->stateless_rpc ? LARGE_FLUSH : PIPESAFE_FLUSH;

	if (count < flush_limit)
		count <<= 1;
	else
		count += flush_limit;
	return count;
}