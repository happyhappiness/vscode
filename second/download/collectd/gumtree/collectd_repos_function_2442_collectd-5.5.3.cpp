static void plugin_free_data_sets (void)
{
	void *key;
	void *value;

	if (data_sets == NULL)
		return;

	while (c_avl_pick (data_sets, &key, &value) == 0)
	{
		data_set_t *ds = value;
		/* key is a pointer to ds->type */

		sfree (ds->ds);
		sfree (ds);
	}

	c_avl_destroy (data_sets);
	data_sets = NULL;
}