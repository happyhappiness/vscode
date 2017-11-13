static void pass_blame_to_parent(struct scoreboard *sb,
				 struct origin *target,
				 struct origin *parent)
{
	mmfile_t file_p, file_o;
	struct blame_chunk_cb_data d;
	struct blame_entry *newdest = NULL;

	if (!target->suspects)
		return; /* nothing remains for this target */

	d.parent = parent;
	d.offset = 0;
	d.dstq = &newdest; d.srcq = &target->suspects;

	fill_origin_blob(&sb->revs->diffopt, parent, &file_p);
	fill_origin_blob(&sb->revs->diffopt, target, &file_o);
	num_get_patch++;

	if (diff_hunks(&file_p, &file_o, blame_chunk_cb, &d))
		die("unable to generate diff (%s -> %s)",
		    oid_to_hex(&parent->commit->object.oid),
		    oid_to_hex(&target->commit->object.oid));
	/* The rest are the same as the parent */
	blame_chunk(&d.dstq, &d.srcq, INT_MAX, d.offset, INT_MAX, parent);
	*d.dstq = NULL;
	queue_blames(sb, parent, newdest);

	return;
}