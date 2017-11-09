static int next_flush(struct fetch_pack_args *args, int count)
{
	if (args->stateless_rpc) {
		if (count < LARGE_FLUSH)
			count <<= 1;
		else
			count = count * 11 / 10;
	} else {
		if (count < PIPESAFE_FLUSH)
			count <<= 1;
		else
			count += PIPESAFE_FLUSH;
	}
	return count;
}