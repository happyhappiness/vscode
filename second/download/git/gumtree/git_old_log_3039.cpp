warning("failed utime() on %s: %s",
			rerere_path(id, "postimage"),
			strerror(errno));