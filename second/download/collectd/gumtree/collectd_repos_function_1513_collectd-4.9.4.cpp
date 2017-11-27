static void destroy_read_heap (void) /* {{{ */
{
	if (read_heap == NULL)
		return;

	while (42)
	{
		callback_func_t *cf;

		cf = c_heap_get_root (read_heap);
		if (cf == NULL)
			break;

		destroy_callback (cf);
	}

	c_heap_destroy (read_heap);
	read_heap = NULL;
}