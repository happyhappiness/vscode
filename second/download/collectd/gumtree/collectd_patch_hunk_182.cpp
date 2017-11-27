 				"expected at least 3.\n",
 				fields_num);
 		fflush (fh);
 		return (-1);
 	}
 
-	status = parse_identifier (fields[1], &hostname,
+	/* parse_identifier() modifies its first argument,
+	 * returning pointers into it */
+	identifier_copy = sstrdup (fields[1]);
+
+	status = parse_identifier (identifier_copy, &hostname,
 			&plugin, &plugin_instance,
 			&type, &type_instance);
 	if (status != 0)
 	{
 		DEBUG ("cmd putval: Cannot parse `%s'", fields[1]);
 		fprintf (fh, "-1 Cannot parse identifier.\n");
 		fflush (fh);
+		sfree (identifier_copy);
 		return (-1);
 	}
 
 	if ((strlen (hostname) >= sizeof (vl.host))
 			|| (strlen (plugin) >= sizeof (vl.plugin))
 			|| ((plugin_instance != NULL)
 				&& (strlen (plugin_instance) >= sizeof (vl.plugin_instance)))
 			|| ((type_instance != NULL)
 				&& (strlen (type_instance) >= sizeof (vl.type_instance))))
 	{
-		fprintf (fh, "-1 Identifier too long.");
+		fprintf (fh, "-1 Identifier too long.\n");
+		fflush (fh);
+		sfree (identifier_copy);
 		return (-1);
 	}
 
 	strcpy (vl.host, hostname);
 	strcpy (vl.plugin, plugin);
 	if (plugin_instance != NULL)
 		strcpy (vl.plugin_instance, plugin_instance);
 	if (type_instance != NULL)
 		strcpy (vl.type_instance, type_instance);
 
 	ds = plugin_get_ds (type);
-	if (ds == NULL)
+	if (ds == NULL) {
+		sfree (identifier_copy);
 		return (-1);
+	}
 
 	vl.values_len = ds->ds_num;
 	vl.values = (value_t *) malloc (vl.values_len * sizeof (value_t));
 	if (vl.values == NULL)
 	{
-		fprintf (fh, "-1 malloc failed.");
+		fprintf (fh, "-1 malloc failed.\n");
+		fflush (fh);
+		sfree (identifier_copy);
 		return (-1);
 	}
 
 	/* All the remaining fields are part of the optionlist. */
 	for (i = 2; i < fields_num; i++)
 	{
