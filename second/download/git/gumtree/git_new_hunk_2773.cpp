	 * file_o is a part of final image we are annotating.
	 * file_p partially may match that image.
	 */
	memset(split, 0, sizeof(struct blame_entry [3]));
	if (diff_hunks(file_p, &file_o, 1, handle_split_cb, &d))
		die("unable to generate diff (%s)",
		    oid_to_hex(&parent->commit->object.oid));
	/* remainder, if any, all match the preimage */
	handle_split(sb, ent, d.tlno, d.plno, ent->num_lines, parent, split);
}

/* Move all blame entries from list *source that have a score smaller
 * than score_min to the front of list *small.
