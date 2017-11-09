static const char *unpack_with_sideband(struct shallow_info *si)
{
	struct async muxer;
	const char *ret;

	if (!use_sideband)
		return unpack(0, si);

	use_keepalive = KEEPALIVE_AFTER_NUL;
	memset(&muxer, 0, sizeof(muxer));
	muxer.proc = copy_to_sideband;
	muxer.in = -1;
	if (start_async(&muxer))
		return NULL;

	ret = unpack(muxer.in, si);

	finish_async(&muxer);
	return ret;
}