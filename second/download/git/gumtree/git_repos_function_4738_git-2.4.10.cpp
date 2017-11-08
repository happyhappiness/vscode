static int update_shallow_ref(struct command *cmd, struct shallow_info *si)
{
	static struct lock_file shallow_lock;
	struct sha1_array extra = SHA1_ARRAY_INIT;
	const char *alt_file;
	uint32_t mask = 1 << (cmd->index % 32);
	int i;

	trace_printf_key(&trace_shallow,
			 "shallow: update_shallow_ref %s\n", cmd->ref_name);
	for (i = 0; i < si->shallow->nr; i++)
		if (si->used_shallow[i] &&
		    (si->used_shallow[i][cmd->index / 32] & mask) &&
		    !delayed_reachability_test(si, i))
			sha1_array_append(&extra, si->shallow->sha1[i]);

	setup_alternate_shallow(&shallow_lock, &alt_file, &extra);
	if (check_shallow_connected(command_singleton_iterator,
				    0, cmd, alt_file)) {
		rollback_lock_file(&shallow_lock);
		sha1_array_clear(&extra);
		return -1;
	}

	commit_lock_file(&shallow_lock);

	/*
	 * Make sure setup_alternate_shallow() for the next ref does
	 * not lose these new roots..
	 */
	for (i = 0; i < extra.nr; i++)
		register_shallow(extra.sha1[i]);

	si->shallow_ref[cmd->index] = 0;
	sha1_array_clear(&extra);
	return 0;
}