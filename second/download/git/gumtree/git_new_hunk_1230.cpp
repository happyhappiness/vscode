}

/*
 * The blame_entry is found to be guilty for the range.
 * Show it in incremental output.
 */
static void found_guilty_entry(struct blame_entry *ent, void *data)
{
	struct progress_info *pi = (struct progress_info *)data;

	if (incremental) {
		struct blame_origin *suspect = ent->suspect;

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

static const char *format_time(timestamp_t time, const char *tz_str,
			       int show_raw_time)
{
	static struct strbuf time_buf = STRBUF_INIT;

	strbuf_reset(&time_buf);
	if (show_raw_time) {
		strbuf_addf(&time_buf, "%"PRItime" %s", time, tz_str);
	}
	else {
		const char *time_str;
		size_t time_width;
		int tz;
		tz = atoi(tz_str);
