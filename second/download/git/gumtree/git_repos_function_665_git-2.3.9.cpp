void free_commit_extra_headers(struct commit_extra_header *extra)
{
	while (extra) {
		struct commit_extra_header *next = extra->next;
		free(extra->key);
		free(extra->value);
		free(extra);
		extra = next;
	}
}