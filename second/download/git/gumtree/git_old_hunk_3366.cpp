				continue;
		}
		ce = active_cache[pos];

		if (lstat(ce->name, &st) < 0) {
			if (errno != ENOENT && errno != ENOTDIR)
				warning("'%s': %s", ce->name, strerror(errno));
			/* It already vanished from the working tree */
			continue;
		}
		else if (S_ISDIR(st.st_mode)) {
			/* if a file was removed and it is now a
			 * directory, that is the same as ENOENT as
