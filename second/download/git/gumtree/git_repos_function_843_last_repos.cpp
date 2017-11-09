int parse_opt_expiry_date_cb(const struct option *opt, const char *arg,
			     int unset)
{
	return parse_expiry_date(arg, (timestamp_t *)opt->value);
}