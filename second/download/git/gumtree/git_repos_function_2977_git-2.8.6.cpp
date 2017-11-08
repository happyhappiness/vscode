static void unlink_rr_item(struct rerere_id *id)
{
	unlink(rerere_path(id, "thisimage"));
	unlink(rerere_path(id, "preimage"));
	unlink(rerere_path(id, "postimage"));
	/*
	 * NEEDSWORK: what if this rmdir() fails?  Wouldn't we then
	 * assume that we already have preimage recorded in
	 * do_plain_rerere()?
	 */
	rmdir(rerere_path(id, NULL));
}