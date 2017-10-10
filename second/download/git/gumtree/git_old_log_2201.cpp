ret = error("chmod on %s failed: %s",
				lock->filename.buf, strerror(errno));