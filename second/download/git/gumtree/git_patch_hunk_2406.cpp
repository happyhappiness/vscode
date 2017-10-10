 		/* write the rest of the config */
 		if (copy_begin < contents_sz)
 			if (write_in_full(fd, contents + copy_begin,
 					  contents_sz - copy_begin) <
 			    contents_sz - copy_begin)
 				goto write_err_out;
+
+		munmap(contents, contents_sz);
+		contents = NULL;
 	}
 
 	if (commit_lock_file(lock) < 0) {
 		error("could not commit config file %s", config_filename);
 		ret = CONFIG_NO_WRITE;
 		lock = NULL;
