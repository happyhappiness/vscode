error("cannot fdopen %s (%s)",
			      get_lock_file_path(&reflog_lock), strerror(errno));