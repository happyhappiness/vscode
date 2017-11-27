 		if (plugin_load_file (filename) == 0)
 		{
 			/* success */
 			ret = 0;
 			break;
 		}
+		else
+		{
+			fprintf (stderr, "Unable to load plugin %s.\n", type);
+		}
 	}
 
 	closedir (dh);
 
 	return (ret);
 }
