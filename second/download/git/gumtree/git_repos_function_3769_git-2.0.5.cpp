static void warn_unspecified_push_default_configuration(void)
{
	static int warn_once;

	if (warn_once++)
		return;
	warning("%s\n", _(warn_unspecified_push_default_msg));
}