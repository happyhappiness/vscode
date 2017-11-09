static int subject_prefix_callback(const struct option *opt, const char *arg,
			    int unset)
{
	subject_prefix = 1;
	((struct rev_info *)opt->value)->subject_prefix = arg;
	return 0;
}