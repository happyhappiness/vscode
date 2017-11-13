static void find_copy_in_blob(struct scoreboard *sb,
			      struct blame_entry *ent,
			      struct origin *parent,
			      struct blame_entry *split,
			      mmfile_t *file_p)
{
	const char *cp;
	mmfile_t file_o;
	struct handle_split_cb_data d;

	memset(&d, 0, sizeof(d));
	d.sb = sb; d.ent = ent; d.parent = parent; d.split = split;
	/*
	 * Prepare mmfile that contains only the lines in ent.
	 */
	cp = nth_line(sb, ent->lno);
	file_o.ptr = (char *) cp;
	file_o.size = nth_line(sb, ent->lno + ent->num_lines) - cp;

	/*
	 * file_o is a part of final image we are annotating.
	 * file_p partially may match that image.
	 */
	memset(split, 0, sizeof(struct blame_entry [3]));
	if (diff_hunks(file_p, &file_o, 1, handle_split_cb, &d))
		die("unable to generate diff (%s)",
		    sha1_to_hex(parent->commit->object.sha1));
	/* remainder, if any, all match the preimage */
	handle_split(sb, ent, d.tlno, d.plno, ent->num_lines, parent, split);
}