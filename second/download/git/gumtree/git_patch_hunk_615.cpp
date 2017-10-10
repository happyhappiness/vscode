 		ret = error("could not lock config file %s", config_filename);
 		goto out;
 	}
 
 	if (!(config_file = fopen(config_filename, "rb"))) {
 		/* no config file means nothing to rename, no error */
-		goto unlock_and_out;
+		goto commit_and_out;
 	}
 
-	fstat(fileno(config_file), &st);
+	if (fstat(fileno(config_file), &st) == -1) {
+		ret = error_errno(_("fstat on %s failed"), config_filename);
+		goto out;
+	}
 
 	if (chmod(get_lock_file_path(lock), st.st_mode & 07777) < 0) {
 		ret = error_errno("chmod on %s failed",
 				  get_lock_file_path(lock));
 		goto out;
 	}
