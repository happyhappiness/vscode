static void clear_cas_option(struct push_cas_option *cas)
{
	int i;

	for (i = 0; i < cas->nr; i++)
		free(cas->entry[i].refname);
	free(cas->entry);
	memset(cas, 0, sizeof(*cas));
}