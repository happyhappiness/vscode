void prepare_shallow_info(struct shallow_info *info, struct oid_array *sa)
{
	int i;
	trace_printf_key(&trace_shallow, "shallow: prepare_shallow_info\n");
	memset(info, 0, sizeof(*info));
	info->shallow = sa;
	if (!sa)
		return;
	ALLOC_ARRAY(info->ours, sa->nr);
	ALLOC_ARRAY(info->theirs, sa->nr);
	for (i = 0; i < sa->nr; i++) {
		if (has_object_file(sa->oid + i)) {
			struct commit_graft *graft;
			graft = lookup_commit_graft(sa->oid[i].hash);
			if (graft && graft->nr_parent < 0)
				continue;
			info->ours[info->nr_ours++] = i;
		} else
			info->theirs[info->nr_theirs++] = i;
	}
}