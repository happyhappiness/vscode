	if (cb_data.unique)
		return cb_data.dst_ref;
	free(cb_data.dst_ref);
	return NULL;
}

static int parse_branchname_arg(int argc, const char **argv,
				int dwim_new_local_branch_ok,
				struct branch_info *new,
				struct tree **source_tree,
				unsigned char rev[20],
				const char **new_branch)
{
	int argcount = 0;
	unsigned char branch_rev[20];
	const char *arg;
	int dash_dash_pos;
	int has_dash_dash = 0;
	int i;
