const char *strip_namespace(const char *namespaced_ref)
{
	if (!starts_with(namespaced_ref, get_git_namespace()))
		return NULL;
	return namespaced_ref + namespace_len;
}