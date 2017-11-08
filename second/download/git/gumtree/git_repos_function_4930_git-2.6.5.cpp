static int rev_is_head(char *head, int headlen, char *name,
		       unsigned char *head_sha1, unsigned char *sha1)
{
	if ((!head[0]) ||
	    (head_sha1 && sha1 && hashcmp(head_sha1, sha1)))
		return 0;
	if (starts_with(head, "refs/heads/"))
		head += 11;
	if (starts_with(name, "refs/heads/"))
		name += 11;
	else if (starts_with(name, "heads/"))
		name += 6;
	return !strcmp(head, name);
}