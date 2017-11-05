void transport_check_allowed(const char *type)
{
	if (!is_transport_allowed(type))
		die("transport '%s' not allowed", type);
}