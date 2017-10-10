			logerror("'%s': Non-absolute path denied (interpolated-path active)", dir);
			return NULL;
		}

		strbuf_expand(&expanded_path, interpolated_path,
			      expand_path, &context);

		rlen = strlcpy(interp_path, expanded_path.buf,
			       sizeof(interp_path));
		if (rlen >= sizeof(interp_path)) {
			logerror("interpolated path too large: %s",
				 interp_path);
			return NULL;
		}

		strbuf_release(&expanded_path);
		loginfo("Interpolated dir '%s'", interp_path);

		dir = interp_path;
	}
	else if (base_path) {
		if (*dir != '/') {
			/* Allow only absolute */
			logerror("'%s': Non-absolute path denied (base-path active)", dir);
			return NULL;
		}
		rlen = snprintf(rpath, sizeof(rpath), "%s%s", base_path, dir);
		if (rlen >= sizeof(rpath)) {
			logerror("base-path too large: %s", rpath);
			return NULL;
		}
		dir = rpath;
	}

	path = enter_repo(dir, strict_paths);
	if (!path && base_path && base_path_relaxed) {
		/*
