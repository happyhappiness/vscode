 	/*
 	 * Read partial merge result from .git/NOTES_MERGE_PARTIAL,
 	 * and target notes ref from .git/NOTES_MERGE_REF.
 	 */
 
 	if (get_sha1("NOTES_MERGE_PARTIAL", sha1))
-		die("Failed to read ref NOTES_MERGE_PARTIAL");
+		die(_("failed to read ref NOTES_MERGE_PARTIAL"));
 	else if (!(partial = lookup_commit_reference(sha1)))
-		die("Could not find commit from NOTES_MERGE_PARTIAL.");
+		die(_("could not find commit from NOTES_MERGE_PARTIAL."));
 	else if (parse_commit(partial))
-		die("Could not parse commit from NOTES_MERGE_PARTIAL.");
+		die(_("could not parse commit from NOTES_MERGE_PARTIAL."));
 
 	if (partial->parents)
 		hashcpy(parent_sha1, partial->parents->item->object.oid.hash);
 	else
 		hashclr(parent_sha1);
 
 	t = xcalloc(1, sizeof(struct notes_tree));
 	init_notes(t, "NOTES_MERGE_PARTIAL", combine_notes_overwrite, 0);
 
 	o->local_ref = local_ref_to_free =
 		resolve_refdup("NOTES_MERGE_REF", 0, sha1, NULL);
 	if (!o->local_ref)
-		die("Failed to resolve NOTES_MERGE_REF");
+		die(_("failed to resolve NOTES_MERGE_REF"));
 
 	if (notes_merge_commit(o, t, partial, sha1))
-		die("Failed to finalize notes merge");
+		die(_("failed to finalize notes merge"));
 
 	/* Reuse existing commit message in reflog message */
 	memset(&pretty_ctx, 0, sizeof(pretty_ctx));
 	format_commit_message(partial, "%s", &msg, &pretty_ctx);
 	strbuf_trim(&msg);
 	strbuf_insert(&msg, 0, "notes: ", 7);
