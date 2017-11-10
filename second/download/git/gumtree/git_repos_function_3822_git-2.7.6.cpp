static void post_assign_shallow(struct shallow_info *info,
				struct ref_bitmap *ref_bitmap,
				int *ref_status)
{
	unsigned char (*sha1)[20] = info->shallow->sha1;
	struct commit *c;
	uint32_t **bitmap;
	int dst, i, j;
	int bitmap_nr = (info->ref->nr + 31) / 32;
	struct commit_array ca;

	trace_printf_key(&trace_shallow, "shallow: post_assign_shallow\n");
	if (ref_status)
		memset(ref_status, 0, sizeof(*ref_status) * info->ref->nr);

	/* Remove unreachable shallow commits from "theirs" */
	for (i = dst = 0; i < info->nr_theirs; i++) {
		if (i != dst)
			info->theirs[dst] = info->theirs[i];
		c = lookup_commit(sha1[info->theirs[i]]);
		bitmap = ref_bitmap_at(ref_bitmap, c);
		if (!*bitmap)
			continue;
		for (j = 0; j < bitmap_nr; j++)
			if (bitmap[0][j]) {
				update_refstatus(ref_status, info->ref->nr, *bitmap);
				dst++;
				break;
			}
	}
	info->nr_theirs = dst;

	memset(&ca, 0, sizeof(ca));
	head_ref(add_ref, &ca);
	for_each_ref(add_ref, &ca);

	/* Remove unreachable shallow commits from "ours" */
	for (i = dst = 0; i < info->nr_ours; i++) {
		if (i != dst)
			info->ours[dst] = info->ours[i];
		c = lookup_commit(sha1[info->ours[i]]);
		bitmap = ref_bitmap_at(ref_bitmap, c);
		if (!*bitmap)
			continue;
		for (j = 0; j < bitmap_nr; j++)
			if (bitmap[0][j] &&
			    /* Step 7, reachability test at commit level */
			    !in_merge_bases_many(c, ca.nr, ca.commits)) {
				update_refstatus(ref_status, info->ref->nr, *bitmap);
				dst++;
				break;
			}
	}
	info->nr_ours = dst;

	free(ca.commits);
}