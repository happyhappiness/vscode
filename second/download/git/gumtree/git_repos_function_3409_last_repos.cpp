int dwim_ref(const char *str, int len, unsigned char *sha1, char **ref)
{
	char *last_branch = substitute_branch_name(&str, &len);
	int   refs_found  = expand_ref(str, len, sha1, ref);
	free(last_branch);
	return refs_found;
}