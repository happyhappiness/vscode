 	 */
 	in_fd = open(config_filename, O_RDONLY);
 	if ( in_fd < 0 ) {
 		free(store.key);
 
 		if ( ENOENT != errno ) {
-			error("opening %s: %s", config_filename,
-			      strerror(errno));
+			error_errno("opening %s", config_filename);
 			ret = CONFIG_INVALID_FILE; /* same as "invalid config file" */
 			goto out_free;
 		}
 		/* if nothing to unset, error out */
 		if (value == NULL) {
 			ret = CONFIG_NOTHING_SET;
