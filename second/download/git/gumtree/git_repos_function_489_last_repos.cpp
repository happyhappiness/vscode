static void pass_blame_to_parent(struct blame_scoreboard *sb,
				 struct blame_origin *target,
				 struct blame_origin *parent)
{
	mmfile_t file_p, file_o;
	struct blame_chunk_cb_data d;
	struct blame_entry *newdest = NULL;

	if (!target->suspects)
		return; /* nothing remains for this target */

	d.parent = parent;
	d.offset = 0;
	d.dstq = &newdest; d.srcq = &target->suspects;

	fill_origin_blob(&sb->revs->diffopt, parent, &file_p, &sb->num_read_blob);
	fill_origin_blob(&sb->revs->diffopt, target, &file_o, &sb->num_read_blob);
	sb->num_get_patch++;

	if (diff_hunks(&file_p, &file_o, blame_chunk_cb, &d, sb->xdl_opts))
		die("unable to generate diff (%s -> %s)",
		    oid_to_hex(&parent->commit->object.oid),
		    oid_to_hex(&target->commit->object.oid));
	/* The rest are the same as the parent */
	blame_chunk(&d.dstq, &d.srcq, INT_MAX, d.offset, INT_MAX, parent);
	*d.dstq = NULL;
	queue_blames(sb, parent, newdest);

	return;
}