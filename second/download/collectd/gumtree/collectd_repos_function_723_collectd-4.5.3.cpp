static void *do_flush (void *arg)
{
	INFO ("Flushing all data.");
	plugin_flush (NULL, -1, NULL);
	INFO ("Finished flushing all data.");
	pthread_exit (NULL);
	return NULL;
}