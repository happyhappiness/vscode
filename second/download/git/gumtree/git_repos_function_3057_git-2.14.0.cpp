static void ensure_configured(void)
{
	if (configured)
		return;

	/* Default config must be setup first */
	git_config(git_trailer_default_config, NULL);
	git_config(git_trailer_config, NULL);
	configured = 1;
}