static int network_shutdown (void)
{
	listen_loop++;

	/* Kill the listening thread */
	if (receive_thread_id != (pthread_t) 0)
	{
		pthread_kill (receive_thread_id, SIGTERM);
		pthread_join (receive_thread_id, NULL /* no return value */);
		receive_thread_id = (pthread_t) 0;
	}

	/* Shutdown the dispatching thread */
	if (dispatch_thread_id != (pthread_t) 0)
		pthread_cond_broadcast (&receive_list_cond);

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