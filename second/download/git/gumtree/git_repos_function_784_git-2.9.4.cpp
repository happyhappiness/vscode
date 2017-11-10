struct commit_extra_header *read_commit_extra_headers(struct commit *commit,
						      const char **exclude)
{
	struct commit_extra_header *extra = NULL;
	unsigned long size;
	const char *buffer = get_commit_buffer(commit, &size);
	extra = read_commit_extra_header_lines(buffer, size, exclude);
	unuse_commit_buffer(commit, buffer);
	return extra;
}