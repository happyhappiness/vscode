void prepare_shallow_info(struct shallow_info *info, struct sha1_array *sa)
{
	int i;
	trace_printf_key(&trace_shallow, "shallow: prepare_shallow_info\n");
	memset(info, 0, sizeof(*info));
	info->shallow = sa;
	if (!sa)
		return;
	info->ours = xmalloc(sizeof(*info->ours) * sa->nr);
	info->theirs = xmalloc(sizeof(*info->theirs) * sa->nr);
	for (i = 0; i < sa->nr; i++) {
		if (has_sha1_file(sa->sha1[i])) {
			struct commit_graft *graft;
			graft = lookup_commit_graft(sa->sha1[i]);
			if (graft && graft->nr_parent < 0)
				continue;
			info->ours[info->nr_ours++] = i;
		} else
			info->theirs[info->nr_theirs++] = i;
	}
}