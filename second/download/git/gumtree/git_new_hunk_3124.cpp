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
		write_filename_info(suspect->path);
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
