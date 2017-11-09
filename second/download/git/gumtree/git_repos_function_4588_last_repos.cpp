void remove_nonexistent_theirs_shallow(struct shallow_info *info)
{
	struct object_id *oid = info->shallow->oid;
	int i, dst;
	trace_printf_key(&trace_shallow, "shallow: remove_nonexistent_theirs_shallow\n");
	for (i = dst = 0; i < info->nr_theirs; i++) {
		if (i != dst)
			info->theirs[dst] = info->theirs[i];
		if (has_object_file(oid + info->theirs[i]))
			dst++;
	}
	info->nr_theirs = dst;
}