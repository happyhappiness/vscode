 		fprintf (fh, "-1 Identifier too long.\n");
 		fflush (fh);
 		sfree (identifier_copy);
 		return (-1);
 	}
 
-	strcpy (vl.host, hostname);
-	strcpy (vl.plugin, plugin);
+	sstrncpy (vl.host, hostname, sizeof (vl.host));
+	sstrncpy (vl.plugin, plugin, sizeof (vl.plugin));
 	if (plugin_instance != NULL)
-		strcpy (vl.plugin_instance, plugin_instance);
+		sstrncpy (vl.plugin_instance, plugin_instance, sizeof (vl.plugin_instance));
 	if (type_instance != NULL)
-		strcpy (vl.type_instance, type_instance);
+		sstrncpy (vl.type_instance, type_instance, sizeof (vl.type_instance));
 
 	ds = plugin_get_ds (type);
 	if (ds == NULL) {
 		sfree (identifier_copy);
 		return (-1);
 	}
