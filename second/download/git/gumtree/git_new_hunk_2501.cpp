	if (cb_data.unique)
		return cb_data.dst_ref;
	free(cb_data.dst_ref);
	return NULL;
}

static int parse_branchname_arg(int argc, const char **argv,
				int dwim_new_local_branch_ok,
				struct branch_info *new,
				struct checkout_opts *opts,
				unsigned char rev[20])
{
