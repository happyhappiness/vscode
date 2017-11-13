error("unable to fdopen %s: %s",
			     lock->lk->tempfile.filename.buf, strerror(errno));