	struct ref_lock *ref_lock;
	struct strbuf sb = STRBUF_INIT;
	int ret;

	read_cache();
	if (checkout_fast_forward(from, to, 1))
		exit(128); /* the callee should have complained already */
	ref_lock = lock_any_ref_for_update("HEAD", unborn ? null_sha1 : from,
					   0, NULL);
	if (!ref_lock)
		return error(_("Failed to lock HEAD during fast_forward_to"));

	strbuf_addf(&sb, "%s: fast-forward", action_name(opts));
	ret = write_ref_sha1(ref_lock, to, sb.buf);

	strbuf_release(&sb);
	return ret;
}

static int do_recursive_merge(struct commit *base, struct commit *next,
			      const char *base_label, const char *next_label,
