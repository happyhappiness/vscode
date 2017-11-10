static void prune_one(struct rerere_id *id, time_t now,
		      int cutoff_resolve, int cutoff_noresolve)
{
	time_t then;
	int cutoff;

	then = rerere_last_used_at(id);
	if (then)
		cutoff = cutoff_resolve;
	else {
		then = rerere_created_at(id);
		if (!then)
			return;
		cutoff = cutoff_noresolve;
	}
	if (then < now - cutoff * 86400)
		unlink_rr_item(id);
}