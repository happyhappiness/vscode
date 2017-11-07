static const char *path_ok(const char *directory, struct hostinfo *hi)
{
	static char rpath[PATH_MAX];
	static char interp_path[PATH_MAX];
	size_t rlen;
	const char *path;
	const char *dir;

	dir = directory;

	if (daemon_avoid_alias(dir)) {
		logerror("'%s': aliased", dir);
		return NULL;
	}

	if (*dir == '~') {
		if (!user_path) {
			logerror("'%s': User-path not allowed", dir);
			return NULL;
		}
		if (*user_path) {
			/* Got either "~alice" or "~alice/foo";
			 * rewrite them to "~alice/%s" or
			 * "~alice/%s/foo".
			 */
			int namlen, restlen = strlen(dir);
			const char *slash = strchr(dir, '/');
			if (!slash)
				slash = dir + restlen;
			namlen = slash - dir;
			restlen -= namlen;
			loginfo("userpath <%s>, request <%s>, namlen %d, restlen %d, slash <%s>", user_path, dir, namlen, restlen, slash);
			rlen = snprintf(rpath, sizeof(rpath), "%.*s/%s%.*s",
					namlen, dir, user_path, restlen, slash);
			if (rlen >= sizeof(rpath)) {
				logerror("user-path too large: %s", rpath);
				return NULL;
			}
			dir = rpath;
		}
	}
	else if (interpolated_path && hi->saw_extended_args) {
		struct strbuf expanded_path = STRBUF_INIT;
		struct expand_path_context context;

		context.directory = directory;
		context.hostinfo = hi;

		if (*dir != '/') {
			/* Allow only absolute */
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
		 * if we fail and base_path_relaxed is enabled, try without
		 * prefixing the base path
		 */
		dir = directory;
		path = enter_repo(dir, strict_paths);
	}

	if (!path) {
		logerror("'%s' does not appear to be a git repository", dir);
		return NULL;
	}

	if ( ok_paths && *ok_paths ) {
		const char **pp;
		int pathlen = strlen(path);

		/* The validation is done on the paths after enter_repo
		 * appends optional {.git,.git/.git} and friends, but
		 * it does not use getcwd().  So if your /pub is
		 * a symlink to /mnt/pub, you can whitelist /pub and
		 * do not have to say /mnt/pub.
		 * Do not say /pub/.
		 */
		for ( pp = ok_paths ; *pp ; pp++ ) {
			int len = strlen(*pp);
			if (len <= pathlen &&
			    !memcmp(*pp, path, len) &&
			    (path[len] == '\0' ||
			     (!strict_paths && path[len] == '/')))
				return path;
		}
	}
	else {
		/* be backwards compatible */
		if (!strict_paths)
			return path;
	}

	logerror("'%s': not in whitelist", path);
	return NULL;		/* Fallthrough. Deny by default */
}