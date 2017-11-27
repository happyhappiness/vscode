 	status = parse_identifier (identifier_copy, &hostname,
 			&plugin, &plugin_instance,
 			&type, &type_instance);
 	if (status != 0)
 	{
 		DEBUG ("cmd putval: Cannot parse `%s'", fields[1]);
-		fprintf (fh, "-1 Cannot parse identifier.\n");
-		fflush (fh);
+		print_to_socket (fh, "-1 Cannot parse identifier.\n");
 		sfree (identifier_copy);
 		return (-1);
 	}
 
 	if ((strlen (hostname) >= sizeof (vl.host))
 			|| (strlen (plugin) >= sizeof (vl.plugin))
 			|| ((plugin_instance != NULL)
 				&& (strlen (plugin_instance) >= sizeof (vl.plugin_instance)))
 			|| ((type_instance != NULL)
 				&& (strlen (type_instance) >= sizeof (vl.type_instance))))
 	{
-		fprintf (fh, "-1 Identifier too long.\n");
-		fflush (fh);
+		print_to_socket (fh, "-1 Identifier too long.\n");
 		sfree (identifier_copy);
 		return (-1);
 	}
 
-	sstrncpy (vl.host, hostname, sizeof (vl.host));
-	sstrncpy (vl.plugin, plugin, sizeof (vl.plugin));
+	strcpy (vl.host, hostname);
+	strcpy (vl.plugin, plugin);
 	if (plugin_instance != NULL)
-		sstrncpy (vl.plugin_instance, plugin_instance, sizeof (vl.plugin_instance));
+		strcpy (vl.plugin_instance, plugin_instance);
 	if (type_instance != NULL)
-		sstrncpy (vl.type_instance, type_instance, sizeof (vl.type_instance));
+		strcpy (vl.type_instance, type_instance);
 
 	ds = plugin_get_ds (type);
 	if (ds == NULL) {
 		sfree (identifier_copy);
 		return (-1);
 	}
 
 	vl.values_len = ds->ds_num;
 	vl.values = (value_t *) malloc (vl.values_len * sizeof (value_t));
 	if (vl.values == NULL)
 	{
-		fprintf (fh, "-1 malloc failed.\n");
-		fflush (fh);
+		print_to_socket (fh, "-1 malloc failed.\n");
 		sfree (identifier_copy);
 		return (-1);
 	}
 
 	/* All the remaining fields are part of the optionlist. */
 	for (i = 2; i < fields_num; i++)
