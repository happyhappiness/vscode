static int sigrok_shutdown(void)
{
	struct config_device *cfdev;
	GSList *l;

	if (sr_thread_running) {
		pthread_cancel(sr_thread);
		pthread_join(sr_thread, NULL);
	}

	for (l = config_devices; l; l = l->next) {
		cfdev = l->data;
		free(cfdev->name);
		free(cfdev->driver);
		free(cfdev->conn);
		free(cfdev->serialcomm);
		free(cfdev);
	}
	g_slist_free(config_devices);

	return 0;
}