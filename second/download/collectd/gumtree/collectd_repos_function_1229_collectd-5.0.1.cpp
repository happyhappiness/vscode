int c_notify_shutdown (void)
{
	plugin_unregister_init ("notify_desktop");
	plugin_unregister_notification ("notify_desktop");
	plugin_unregister_shutdown ("notify_desktop");

	if (notify_is_initted ())
		notify_uninit ();
	return 0;
}