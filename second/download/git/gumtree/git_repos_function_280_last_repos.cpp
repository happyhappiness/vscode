static int write_entry(struct cache_entry *ce,
		       char *path, const struct checkout *state, int to_tempfile)
{
	unsigned int ce_mode_s_ifmt = ce->ce_mode & S_IFMT;
	int fd, ret, fstat_done = 0;
	char *new;
	struct strbuf buf = STRBUF_INIT;
	unsigned long size;
	size_t wrote, newsize = 0;
	struct stat st;
	const struct submodule *sub;

	if (ce_mode_s_ifmt == S_IFREG) {
		struct stream_filter *filter = get_stream_filter(ce->name,
								 ce->oid.hash);
		if (filter &&
		    !streaming_write_entry(ce, path, filter,
					   state, to_tempfile,
					   &fstat_done, &st))
			goto finish;
	}

	switch (ce_mode_s_ifmt) {
	case S_IFREG:
	case S_IFLNK:
		new = read_blob_entry(ce, &size);
		if (!new)
			return error("unable to read sha1 file of %s (%s)",
				path, oid_to_hex(&ce->oid));

		if (ce_mode_s_ifmt == S_IFLNK && has_symlinks && !to_tempfile) {
			ret = symlink(new, path);
			free(new);
			if (ret)
				return error_errno("unable to create symlink %s",
						   path);
			break;
		}

		/*
		 * Convert from git internal format to working tree format
		 */
		if (ce_mode_s_ifmt == S_IFREG) {
			struct delayed_checkout *dco = state->delayed_checkout;
			if (dco && dco->state != CE_NO_DELAY) {
				/* Do not send the blob in case of a retry. */
				if (dco->state == CE_RETRY) {
					new = NULL;
					size = 0;
				}
				ret = async_convert_to_working_tree(
					ce->name, new, size, &buf, dco);
				if (ret && string_list_has_string(&dco->paths, ce->name)) {
					free(new);
					goto finish;
				}
			} else
				ret = convert_to_working_tree(
					ce->name, new, size, &buf);

			if (ret) {
				free(new);
				new = strbuf_detach(&buf, &newsize);
				size = newsize;
			}
			/*
			 * No "else" here as errors from convert are OK at this
			 * point. If the error would have been fatal (e.g.
			 * filter is required), then we would have died already.
			 */
		}

		fd = open_output_fd(path, ce, to_tempfile);
		if (fd < 0) {
			free(new);
			return error_errno("unable to create file %s", path);
		}

		wrote = write_in_full(fd, new, size);
		if (!to_tempfile)
			fstat_done = fstat_output(fd, state, &st);
		close(fd);
		free(new);
		if (wrote != size)
			return error("unable to write file %s", path);
		break;
	case S_IFGITLINK:
		if (to_tempfile)
			return error("cannot create temporary submodule %s", path);
		if (mkdir(path, 0777) < 0)
			return error("cannot create submodule directory %s", path);
		sub = submodule_from_ce(ce);
		if (sub)
			return submodule_move_head(ce->name,
				NULL, oid_to_hex(&ce->oid),
				state->force ? SUBMODULE_MOVE_HEAD_FORCE : 0);
		break;
	default:
		return error("unknown file mode for %s in index", path);
	}

finish:
	if (state->refresh_cache) {
		assert(state->istate);
		if (!fstat_done)
			lstat(ce->name, &st);
		fill_stat_cache_info(ce, &st);
		ce->ce_flags |= CE_UPDATE_IN_BASE;
		state->istate->cache_changed |= CE_ENTRY_CHANGED;
	}
	return 0;
}