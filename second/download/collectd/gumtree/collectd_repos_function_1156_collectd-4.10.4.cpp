static int c_notify_init (void)
{
	char *name         = NULL;
	char *vendor       = NULL;
	char *version      = NULL;
	char *spec_version = NULL;

	if (! notify_init (PACKAGE_STRING)) {
		log_err ("Failed to initialize libnotify.");
		return -1;
	}

	if (! notify_get_server_info (&name, &vendor, &version, &spec_version))
		log_warn ("Failed to get the notification server info. "
				"Check if you have a notification daemon running.");
	else {
		log_info ("Found notification daemon: %s (%s) %s (spec version %s)",
				name, vendor, version, spec_version);
		free (name);
		free (vendor);
		free (version);
		free (spec_version);
	}

	plugin_register_notification ("notify_desktop", c_notify,
			/* user_data = */ NULL);
	plugin_register_shutdown ("notify_desktop", c_notify_shutdown);
	return 0;
}