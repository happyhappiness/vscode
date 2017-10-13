warning("failed utime() on %s: %s",
					rerere_path(name, "postimage"),
					strerror(errno));