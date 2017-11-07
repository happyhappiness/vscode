void remove_nonexistent_theirs_shallow(struct shallow_info *info)
{
	unsigned char (*sha1)[20] = info->shallow->sha1;
	int i, dst;
	trace_printf_key(TRACE_KEY, "shallow: remove_nonexistent_theirs_shallow\n");
	for (i = dst = 0; i < info->nr_theirs; i++) {
		if (i != dst)
			info->theirs[dst] = info->theirs[i];
		if (has_sha1_file(sha1[info->theirs[i]]))
			dst++;
	}
	info->nr_theirs = dst;
}