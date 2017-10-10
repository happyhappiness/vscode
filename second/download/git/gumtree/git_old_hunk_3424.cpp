		 * could be due to a simultaneous repack. But anything else
		 * we should abort, since we might then fail to mark objects
		 * which should not be pruned.
		 */
		if (errno == ENOENT)
			return 0;
		return error("unable to stat %s: %s",
			     sha1_to_hex(sha1), strerror(errno));
	}

	add_recent_object(sha1, st.st_mtime, data);
	return 0;
}

