static void found_guilty_entry(struct blame_entry *ent)
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
}
