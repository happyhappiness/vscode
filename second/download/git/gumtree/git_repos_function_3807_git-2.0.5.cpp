static int pass_blame_to_parent(struct scoreboard *sb,
				struct origin *target,
				struct origin *parent)
{
	int last_in_target;
	mmfile_t file_p, file_o;
	struct blame_chunk_cb_data d;

	memset(&d, 0, sizeof(d));
	d.sb = sb; d.target = target; d.parent = parent;
	last_in_target = find_last_in_target(sb, target);
	if (last_in_target < 0)
		return 1; /* nothing remains for this target */

	fill_origin_blob(&sb->revs->diffopt, parent, &file_p);
	fill_origin_blob(&sb->revs->diffopt, target, &file_o);
	num_get_patch++;

	diff_hunks(&file_p, &file_o, 0, blame_chunk_cb, &d);
	/* The rest (i.e. anything after tlno) are the same as the parent */
	blame_chunk(sb, d.tlno, d.plno, last_in_target, target, parent);

	return 0;
}