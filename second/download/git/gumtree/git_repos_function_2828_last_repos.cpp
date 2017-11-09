struct commit *next_reflog_entry(struct reflog_walk_info *walk)
{
	struct commit_reflog *best = NULL;
	struct commit *best_commit = NULL;
	size_t i;

	for (i = 0; i < walk->nr; i++) {
		struct commit_reflog *log = walk->logs[i];
		struct commit *commit = next_reflog_commit(log);

		if (!commit)
			continue;

		if (!best || log_timestamp(log) > log_timestamp(best)) {
			best = log;
			best_commit = commit;
		}
	}

	if (best) {
		best->recno--;
		walk->last_commit_reflog = best;
		return best_commit;
	}

	return NULL;
}