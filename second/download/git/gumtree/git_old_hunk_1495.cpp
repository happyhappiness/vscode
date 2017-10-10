	}
	return 0;
}

int parse_opt_commits(const struct option *opt, const char *arg, int unset)
{
	unsigned char sha1[20];
	struct commit *commit;

	if (!arg)
		return -1;
	if (get_sha1(arg, sha1))
		return error("malformed object name %s", arg);
	commit = lookup_commit_reference(sha1);
	if (!commit)
		return error("no such commit %s", arg);
	commit_list_insert(commit, opt->value);
	return 0;
}

