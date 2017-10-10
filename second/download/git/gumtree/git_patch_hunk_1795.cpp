 		munmap(contents, contents_sz);
 	}
 
 	if (commit_lock_file(lock) < 0) {
 		error("could not commit config file %s", config_filename);
 		ret = CONFIG_NO_WRITE;
+		lock = NULL;
 		goto out_free;
 	}
 
 	/*
 	 * lock is committed, so don't try to roll it back below.
 	 * NOTE: Since lockfile.c keeps a linked list of all created
 	 * lock_file structures, it isn't safe to free(lock).  It's
 	 * better to just leave it hanging around.
 	 */
 	lock = NULL;
 	ret = 0;
 
+	/* Invalidate the config cache */
+	git_config_clear();
+
 out_free:
 	if (lock)
 		rollback_lock_file(lock);
 	free(filename_buf);
 	return ret;
 
 write_err_out:
-	ret = write_error(lock->filename);
+	ret = write_error(lock->filename.buf);
 	goto out_free;
 
 }
 
 int git_config_set_multivar(const char *key, const char *value,
 			const char *value_regex, int multi_replace)
