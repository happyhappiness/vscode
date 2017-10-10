 		data.format = REPLACE_FORMAT_LONG;
 	else
 		die("invalid replace format '%s'\n"
 		    "valid formats are 'short', 'medium' and 'long'\n",
 		    format);
 
-	for_each_replace_ref(show_reference, (void *) &data);
+	for_each_replace_ref(show_reference, (void *)&data);
 
 	return 0;
 }
 
 typedef int (*each_replace_name_fn)(const char *name, const char *ref,
 				    const unsigned char *sha1);
