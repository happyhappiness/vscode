	error("%s", msg);
	usage_with_options(check_attr_usage, check_attr_options);
}

int cmd_check_attr(int argc, const char **argv, const char *prefix)
{
	struct git_attr_check *check;
	int cnt, i, doubledash, filei;

	if (!is_bare_repository())
		setup_work_tree();

	git_config(git_default_config, NULL);
