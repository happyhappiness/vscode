		(*callback) (level, msg);

		le = le->next;
	}
} /* void plugin_log */

const data_set_t *plugin_get_ds (const char *name)
{
	data_set_t *ds;

	if (c_avl_get (data_sets, name, (void *) &ds) != 0)
	{
		DEBUG ("No such dataset registered: %s", name);
		return (NULL);
	}

	return (ds);
} /* data_set_t *plugin_get_ds */
