int walker_fetch(struct walker *walker, int targets, char **target,
		 const char **write_ref, const char *write_ref_log_details)
{
	struct ref_lock **lock = xcalloc(targets, sizeof(struct ref_lock *));
	unsigned char *sha1 = xmalloc(targets * 20);
	const char *msg;
	char *to_free = NULL;
	int ret;
	int i;

	save_commit_buffer = 0;

	for (i = 0; i < targets; i++) {
		if (!write_ref || !write_ref[i])
			continue;

		lock[i] = lock_ref_sha1(write_ref[i], NULL);
		if (!lock[i]) {
			error("Can't lock ref %s", write_ref[i]);
			goto unlock_and_fail;
		}
	}

	if (!walker->get_recover)
		for_each_ref(mark_complete, NULL);

	for (i = 0; i < targets; i++) {
		if (interpret_target(walker, target[i], &sha1[20 * i])) {
			error("Could not interpret response from server '%s' as something to pull", target[i]);
			goto unlock_and_fail;
		}
		if (process(walker, lookup_unknown_object(&sha1[20 * i])))
			goto unlock_and_fail;
	}

	if (loop(walker))
		goto unlock_and_fail;

	if (write_ref_log_details)
		msg = to_free = xstrfmt("fetch from %s", write_ref_log_details);
	else
		msg = "fetch (unknown)";
	for (i = 0; i < targets; i++) {
		if (!write_ref || !write_ref[i])
			continue;
		ret = write_ref_sha1(lock[i], &sha1[20 * i], msg);
		lock[i] = NULL;
		if (ret)
			goto unlock_and_fail;
	}
	free(to_free);

	return 0;

unlock_and_fail:
	for (i = 0; i < targets; i++)
		if (lock[i])
			unlock_ref(lock[i]);
	free(to_free);

	return -1;
}