
	o->local_ref = local_ref_to_free =
		resolve_refdup("NOTES_MERGE_REF", 0, oid.hash, NULL);
	if (!o->local_ref)
		die(_("failed to resolve NOTES_MERGE_REF"));

	if (notes_merge_commit(o, t, partial, oid.hash))
		die(_("failed to finalize notes merge"));

	/* Reuse existing commit message in reflog message */
	memset(&pretty_ctx, 0, sizeof(pretty_ctx));
	format_commit_message(partial, "%s", &msg, &pretty_ctx);
	strbuf_trim(&msg);
