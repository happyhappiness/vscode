void plugin_init_all (void)
{
	char const *chain_name;
	llentry_t *le;
	int status;

	/* Init the value cache */
	uc_init ();

	if (IS_TRUE (global_option_get ("CollectInternalStats")))
		record_statistics = 1;

	chain_name = global_option_get ("PreCacheChain");
	pre_cache_chain = fc_chain_get_by_name (chain_name);

	chain_name = global_option_get ("PostCacheChain");
	post_cache_chain = fc_chain_get_by_name (chain_name);

	write_limit_high = global_option_get_long ("WriteQueueLimitHigh",
			/* default = */ 0);
	if (write_limit_high < 0)
	{
		ERROR ("WriteQueueLimitHigh must be positive or zero.");
		write_limit_high = 0;
	}

	write_limit_low = global_option_get_long ("WriteQueueLimitLow",
			/* default = */ write_limit_high / 2);
	if (write_limit_low < 0)
	{
		ERROR ("WriteQueueLimitLow must be positive or zero.");
		write_limit_low = write_limit_high / 2;
	}
	else if (write_limit_low > write_limit_high)
	{
		ERROR ("WriteQueueLimitLow must not be larger than "
				"WriteQueueLimitHigh.");
		write_limit_low = write_limit_high;
	}

	write_threads_num = global_option_get_long ("WriteThreads",
			/* default = */ 5);
	if (write_threads_num < 1)
	{
		ERROR ("WriteThreads must be positive.");
		write_threads_num = 5;
	}

	if ((list_init == NULL) && (read_heap == NULL))
		return;

	/* Calling all init callbacks before checking if read callbacks
	 * are available allows the init callbacks to register the read
	 * callback. */
	le = llist_head (list_init);
	while (le != NULL)
	{
		callback_func_t *cf;
		plugin_init_cb callback;
		plugin_ctx_t old_ctx;

		cf = le->value;
		old_ctx = plugin_set_ctx (cf->cf_ctx);
		callback = cf->cf_callback;
		status = (*callback) ();
		plugin_set_ctx (old_ctx);

		if (status != 0)
		{
			ERROR ("Initialization of plugin `%s' "
					"failed with status %i. "
					"Plugin will be unloaded.",
					le->key, status);
			/* Plugins that register read callbacks from the init
			 * callback should take care of appropriate error
			 * handling themselves. */
			/* FIXME: Unload _all_ functions */
			plugin_unregister_read (le->key);
		}

		le = le->next;
	}

	start_write_threads ((size_t) write_threads_num);

	max_read_interval = global_option_get_time ("MaxReadInterval",
			DEFAULT_MAX_READ_INTERVAL);

	/* Start read-threads */
	if (read_heap != NULL)
	{
		const char *rt;
		int num;

		rt = global_option_get ("ReadThreads");
		num = atoi (rt);
		if (num != -1)
			start_read_threads ((num > 0) ? num : 5);
	}
}