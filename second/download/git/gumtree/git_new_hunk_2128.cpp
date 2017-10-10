				 namlen, dir, user_path, restlen, slash);
			dir = rpath;
		}
	}
	else if (interpolated_path && saw_extended_args) {
		struct strbuf expanded_path = STRBUF_INIT;
		struct expand_path_context context;

		context.directory = directory;

		if (*dir != '/') {
			/* Allow only absolute */
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
