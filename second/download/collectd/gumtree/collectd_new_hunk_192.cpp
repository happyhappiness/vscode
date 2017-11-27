		fprintf (fh, "-1 Identifier too long.\n");
		fflush (fh);
		sfree (identifier_copy);
		return (-1);
	}

	sstrncpy (vl.host, hostname, sizeof (vl.host));
	sstrncpy (vl.plugin, plugin, sizeof (vl.plugin));
	if (plugin_instance != NULL)
		sstrncpy (vl.plugin_instance, plugin_instance, sizeof (vl.plugin_instance));
	if (type_instance != NULL)
		sstrncpy (vl.type_instance, type_instance, sizeof (vl.type_instance));

	ds = plugin_get_ds (type);
	if (ds == NULL) {
		sfree (identifier_copy);
		return (-1);
	}
