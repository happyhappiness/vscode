static int fast_forward_to(const unsigned char *to, const unsigned char *from,
			int unborn, struct replay_opts *opts)
{
	struct ref_lock *ref_lock;
	struct strbuf sb = STRBUF_INIT;
	int ret;

	read_cache();
	if (checkout_fast_forward(from, to, 1))
		exit(1); /* the callee should have complained already */
	ref_lock = lock_any_ref_for_update("HEAD", unborn ? null_sha1 : from,
					   0, NULL);
	strbuf_addf(&sb, "%s: fast-forward", action_name(opts));
	ret = write_ref_sha1(ref_lock, to, sb.buf);
	strbuf_release(&sb);
	return ret;
}