		write_filename_info(suspect->path);
		maybe_flush_or_die(stdout, "stdout");
	}
}

/*
 * The main loop -- while the scoreboard has lines whose true origin
 * is still unknown, pick one blame_entry, and allow its current
 * suspect to pass blames to its parents.
 */
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
