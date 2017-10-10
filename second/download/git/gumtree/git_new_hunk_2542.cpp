		if (arg)
			unpack_unreachable_expiration = approxidate(arg);
	}
	return 0;
}

int cmd_pack_objects(int argc, const char **argv, const char *prefix)
{
	int use_internal_rev_list = 0;
	int thin = 0;
	int shallow = 0;
	int all_progress_implied = 0;
