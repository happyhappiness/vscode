static int network_shutdown (void)
{
	listen_loop++;

	if (listen_thread != (pthread_t) 0)
	{
		pthread_kill (listen_thread, SIGTERM);
		pthread_join (listen_thread, NULL /* no return value */);
		listen_thread = (pthread_t) 0;
	}

	if (send_buffer_fill > 0)
		flush_buffer ();

	if (cache_tree != NULL)
	{
		void *key;
		void *value;

		while (c_avl_pick (cache_tree, &key, &value) == 0)
		{
			sfree (key);
			sfree (value);
		}
		c_avl_destroy (cache_tree);
		cache_tree = NULL;
	}

	/* TODO: Close `sending_sockets' */

	plugin_unregister_config ("network");
	plugin_unregister_init ("network");
	plugin_unregister_write ("network");
	plugin_unregister_shutdown ("network");

	return (0);
}