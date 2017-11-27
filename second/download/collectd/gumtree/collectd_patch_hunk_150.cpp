 			fprintf (stderr, "Unable to load plugin %s.\n", type);
 		}
 	}
 
 	closedir (dh);
 
+	if (filename[0] == '\0')
+		fprintf (stderr, "Could not find plugin %s.\n", type);
+
 	return (ret);
 }
 
 /*
  * The `register_*' functions follow
  */
