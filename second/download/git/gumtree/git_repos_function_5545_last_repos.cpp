static int rev_is_head(const char *head, const char *name,
		       unsigned char *head_sha1, unsigned char *sha1)
{
	if (!head || (head_sha1 && sha1 && hashcmp(head_sha1, sha1)))
		return 0;
	skip_prefix(head, "refs/heads/", &head);
	if (!skip_prefix(name, "refs/heads/", &name))
		skip_prefix(name, "heads/", &name);
	return !strcmp(head, name);
}