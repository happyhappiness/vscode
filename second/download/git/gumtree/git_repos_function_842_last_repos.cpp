int parse_opt_approxidate_cb(const struct option *opt, const char *arg,
			     int unset)
{
	*(timestamp_t *)(opt->value) = approxidate(arg);
	return 0;
}