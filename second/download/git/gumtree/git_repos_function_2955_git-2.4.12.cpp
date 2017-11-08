static struct diff_filespec *filespec_from_entry(struct diff_filespec *target,
						 struct stage_data *entry,
						 int stage)
{
	unsigned char *sha = entry->stages[stage].sha;
	unsigned mode = entry->stages[stage].mode;
	if (mode == 0 || is_null_sha1(sha))
		return NULL;
	hashcpy(target->sha1, sha);
	target->mode = mode;
	return target;
}