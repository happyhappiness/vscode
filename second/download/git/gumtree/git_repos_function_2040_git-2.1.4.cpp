static void show_mergetag(struct rev_info *opt, struct commit *commit)
{
	for_each_mergetag(show_one_mergetag, commit, opt);
}