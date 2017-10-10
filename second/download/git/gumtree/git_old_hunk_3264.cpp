			     chain_histogram[i]),
			  i + 1,
			  chain_histogram[i]);
	}
}

int cmd_index_pack(int argc, const char **argv, const char *prefix)
{
	int i, fix_thin_pack = 0, verify = 0, stat_only = 0;
	const char *curr_index;
	const char *index_name = NULL, *pack_name = NULL;
	const char *keep_name = NULL, *keep_msg = NULL;
