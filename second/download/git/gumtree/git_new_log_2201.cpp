ret = error("chmod on %s failed: %s",
			    get_lock_file_path(lock), strerror(errno));