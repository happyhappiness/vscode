static int config_name_cmp(const struct submodule_entry *a,
			   const struct submodule_entry *b,
			   const void *unused)
{
	return strcmp(a->config->name, b->config->name) ||
	       hashcmp(a->config->gitmodules_sha1, b->config->gitmodules_sha1);
}