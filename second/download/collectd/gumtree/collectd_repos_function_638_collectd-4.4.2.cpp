static void *do_flush (void *arg)
{
	INFO ("Flushing all data.");
	plugin_flush_all (-1);
	INFO ("Finished flushing all data.");
	pthread_exit (NULL);
	return NULL;
}