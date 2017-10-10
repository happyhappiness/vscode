}

/*
 * The blame_entry is found to be guilty for the range.
 * Show it in incremental output.
 */
static void found_guilty_entry(struct blame_entry *ent,
			   struct progress_info *pi)
{
	if (incremental) {
		struct origin *suspect = ent->suspect;

		printf("%s %d %d %d\n",
		       oid_to_hex(&suspect->commit->object.oid),
		       ent->s_lno + 1, ent->lno + 1, ent->num_lines);
		emit_one_suspect_detail(suspect, 0);
		write_filename_info(suspect);
		maybe_flush_or_die(stdout, "stdout");
	}
	pi->blamed_lines += ent->num_lines;
	display_progress(pi->progress, pi->blamed_lines);
}

/*
 * The main loop -- while we have blobs with lines whose true origin
 * is still unknown, pick one blob, and allow its lines to pass blames
 * to its parents. */
static void assign_blame(struct scoreboard *sb, int opt)
{
	struct rev_info *revs = sb->revs;
	struct commit *commit = prio_queue_get(&sb->commits);
	struct progress_info pi = { NULL, 0 };

	if (show_progress)
		pi.progress = start_progress_delay(_("Blaming lines"),
						   sb->num_lines, 50, 1);

	while (commit) {
		struct blame_entry *ent;
		struct origin *suspect = commit->util;

		/* find one suspect to break down */
		while (suspect && !suspect->suspects)
			suspect = suspect->next;

		if (!suspect) {
			commit = prio_queue_get(&sb->commits);
			continue;
		}

		assert(commit == suspect->commit);

		/*
		 * We will use this suspect later in the loop,
		 * so hold onto it in the meantime.
		 */
		origin_incref(suspect);
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
		ent = suspect->suspects;
		if (ent) {
			suspect->guilty = 1;
			for (;;) {
				struct blame_entry *next = ent->next;
				found_guilty_entry(ent, &pi);
				if (next) {
					ent = next;
					continue;
				}
				ent->next = sb->ent;
				sb->ent = suspect->suspects;
				suspect->suspects = NULL;
				break;
			}
		}
		origin_decref(suspect);

		if (DEBUG) /* sanity */
			sanity_check_refcnt(sb);
	}

	stop_progress(&pi.progress);
}

static const char *format_time(unsigned long time, const char *tz_str,
			       int show_raw_time)
{
	static struct strbuf time_buf = STRBUF_INIT;

	strbuf_reset(&time_buf);
	if (show_raw_time) {
		strbuf_addf(&time_buf, "%lu %s", time, tz_str);
	}
	else {
		const char *time_str;
		size_t time_width;
		int tz;
		tz = atoi(tz_str);
