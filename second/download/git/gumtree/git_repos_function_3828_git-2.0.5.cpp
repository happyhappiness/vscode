static void assign_blame(struct scoreboard *sb, int opt)
{
	struct rev_info *revs = sb->revs;

	while (1) {
		struct blame_entry *ent;
		struct commit *commit;
		struct origin *suspect = NULL;

		/* find one suspect to break down */
		for (ent = sb->ent; !suspect && ent; ent = ent->next)
			if (!ent->guilty)
				suspect = ent->suspect;
		if (!suspect)
			return; /* all done */

		/*
		 * We will use this suspect later in the loop,
		 * so hold onto it in the meantime.
		 */
		origin_incref(suspect);
		commit = suspect->commit;
		parse_commit(commit);
		if (reverse ||
		    (!(commit->object.flags & UNINTERESTING) &&
		     !(revs->max_age != -1 && commit->date < revs->max_age)))
			pass_blame(sb, suspect, opt);
		else {
			commit->object.flags |= UNINTERESTING;
			if (commit->object.parsed)
				mark_parents_uninteresting(commit);
		}
		/* treat root commit as boundary */
		if (!commit->parents && !show_root)
			commit->object.flags |= UNINTERESTING;

		/* Take responsibility for the remaining entries */
		for (ent = sb->ent; ent; ent = ent->next)
			if (ent->suspect == suspect)
				found_guilty_entry(ent);
		origin_decref(suspect);

		if (DEBUG) /* sanity */
			sanity_check_refcnt(sb);
	}
}