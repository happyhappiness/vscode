int is_empty_cas(const struct push_cas_option *cas)
{
	return !cas->use_tracking_for_rest && !cas->nr;
}