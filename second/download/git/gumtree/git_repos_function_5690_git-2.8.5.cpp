static int merge_commit(struct notes_merge_options *o)
{
	struct strbuf msg = STRBUF_INIT;
	unsigned char sha1[20], parent_sha1[20];
	struct notes_tree *t;
	struct commit *partial;
	struct pretty_print_context pretty_ctx;
	void *local_ref_to_free;
	int ret;

	/*
	 * Read partial merge result from .git/NOTES_MERGE_PARTIAL,
	 * and target notes ref from .git/NOTES_MERGE_REF.
	 */

	if (get_sha1("NOTES_MERGE_PARTIAL", sha1))
		die("Failed to read ref NOTES_MERGE_PARTIAL");
	else if (!(partial = lookup_commit_reference(sha1)))
		die("Could not find commit from NOTES_MERGE_PARTIAL.");
	else if (parse_commit(partial))
		die("Could not parse commit from NOTES_MERGE_PARTIAL.");

	if (partial->parents)
		hashcpy(parent_sha1, partial->parents->item->object.oid.hash);
	else
		hashclr(parent_sha1);

	t = xcalloc(1, sizeof(struct notes_tree));
	init_notes(t, "NOTES_MERGE_PARTIAL", combine_notes_overwrite, 0);

	o->local_ref = local_ref_to_free =
		resolve_refdup("NOTES_MERGE_REF", 0, sha1, NULL);
	if (!o->local_ref)
		die("Failed to resolve NOTES_MERGE_REF");

	if (notes_merge_commit(o, t, partial, sha1))
		die("Failed to finalize notes merge");

	/* Reuse existing commit message in reflog message */
	memset(&pretty_ctx, 0, sizeof(pretty_ctx));
	format_commit_message(partial, "%s", &msg, &pretty_ctx);
	strbuf_trim(&msg);
	strbuf_insert(&msg, 0, "notes: ", 7);
	update_ref(msg.buf, o->local_ref, sha1,
		   is_null_sha1(parent_sha1) ? NULL : parent_sha1,
		   0, UPDATE_REFS_DIE_ON_ERR);

	free_notes(t);
	strbuf_release(&msg);
	ret = merge_abort(o);
	free(local_ref_to_free);
	return ret;
}