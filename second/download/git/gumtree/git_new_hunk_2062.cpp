			loginfo("userpath <%s>, request <%s>, namlen %d, restlen %d, slash <%s>", user_path, dir, namlen, restlen, slash);
			snprintf(rpath, PATH_MAX, "%.*s/%s%.*s",
				 namlen, dir, user_path, restlen, slash);
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
