	new->item = commit;
	*next = new;
	new->next = NULL;
	return &new->next;
}

const char *find_commit_header(const char *msg, const char *key, size_t *out_len)
{
	int key_len = strlen(key);
	const char *line = msg;

	while (line) {
