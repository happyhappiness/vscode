ret = error("cannot seek back reflog for %s: %s",
				    refname, strerror(errno));