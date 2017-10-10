			logerror("'%s': Non-absolute path denied (interpolated-path active)", dir);
			return NULL;
		}

		strbuf_expand(&expanded_path, interpolated_path,
			      expand_path, &context);
		strlcpy(interp_path, expanded_path.buf, PATH_MAX);
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
		snprintf(rpath, PATH_MAX, "%s%s", base_path, dir);
		dir = rpath;
	}

	path = enter_repo(dir, strict_paths);
	if (!path && base_path && base_path_relaxed) {
		/*
