static void check_mergetags(struct commit *commit, int argc, const char **argv)
{
	struct check_mergetag_data mergetag_data;

	mergetag_data.argc = argc;
	mergetag_data.argv = argv;
	for_each_mergetag(check_one_mergetag, commit, &mergetag_data);
}