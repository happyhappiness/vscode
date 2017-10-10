	 * Read partial merge result from .git/NOTES_MERGE_PARTIAL,
	 * and target notes ref from .git/NOTES_MERGE_REF.
	 */

	if (get_oid("NOTES_MERGE_PARTIAL", &oid))
		die(_("failed to read ref NOTES_MERGE_PARTIAL"));
	else if (!(partial = lookup_commit_reference(oid.hash)))
		die(_("could not find commit from NOTES_MERGE_PARTIAL."));
	else if (parse_commit(partial))
		die(_("could not parse commit from NOTES_MERGE_PARTIAL."));

	if (partial->parents)
		oidcpy(&parent_oid, &partial->parents->item->object.oid);
