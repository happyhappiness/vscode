error("cannot fdopen %s (%s)",
			      reflog_lock.filename.buf, strerror(errno));