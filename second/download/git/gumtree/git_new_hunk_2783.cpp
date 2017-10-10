
	free(name);

	return(ret);
}

static void fill_tracking_info(struct strbuf *stat, const char *branch_name,
		int show_upstream_ref)
{
	int ours, theirs;
	char *ref = NULL;
	struct branch *branch = branch_get(branch_name);
