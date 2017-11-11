int dir_iterator_advance(struct dir_iterator *dir_iterator)
{
	struct dir_iterator_int *iter =
		(struct dir_iterator_int *)dir_iterator;

	while (1) {
		struct dir_iterator_level *level =
			&iter->levels[iter->levels_nr - 1];
		struct dirent *de;

		if (!level->initialized) {
			/*
			 * Note: dir_iterator_begin() ensures that
			 * path is not the empty string.
			 */
			if (!is_dir_sep(iter->base.path.buf[iter->base.path.len - 1]))
				strbuf_addch(&iter->base.path, '/');
			level->prefix_len = iter->base.path.len;

			level->dir = opendir(iter->base.path.buf);
			if (!level->dir && errno != ENOENT) {
				warning("error opening directory %s: %s",
					iter->base.path.buf, strerror(errno));
				/* Popping the level is handled below */
			}

			level->initialized = 1;
		} else if (S_ISDIR(iter->base.st.st_mode)) {
			if (level->dir_state == DIR_STATE_ITER) {
				/*
				 * The directory was just iterated
				 * over; now prepare to iterate into
				 * it.
				 */
				level->dir_state = DIR_STATE_RECURSE;
				ALLOC_GROW(iter->levels, iter->levels_nr + 1,
					   iter->levels_alloc);
				level = &iter->levels[iter->levels_nr++];
				level->initialized = 0;
				continue;
			} else {
				/*
				 * The directory has already been
				 * iterated over and iterated into;
				 * we're done with it.
				 */
			}
		}

		if (!level->dir) {
			/*
			 * This level is exhausted (or wasn't opened
			 * successfully); pop up a level.
			 */
			if (--iter->levels_nr == 0)
				return dir_iterator_abort(dir_iterator);

			continue;
		}

		/*
		 * Loop until we find an entry that we can give back
		 * to the caller:
		 */
		while (1) {
			strbuf_setlen(&iter->base.path, level->prefix_len);
			errno = 0;
			de = readdir(level->dir);

			if (!de) {
				/* This level is exhausted; pop up a level. */
				if (errno) {
					warning("error reading directory %s: %s",
						iter->base.path.buf, strerror(errno));
				} else if (closedir(level->dir))
					warning("error closing directory %s: %s",
						iter->base.path.buf, strerror(errno));

				level->dir = NULL;
				if (--iter->levels_nr == 0)
					return dir_iterator_abort(dir_iterator);
				break;
			}

			if (is_dot_or_dotdot(de->d_name))
				continue;

			strbuf_addstr(&iter->base.path, de->d_name);
			if (lstat(iter->base.path.buf, &iter->base.st) < 0) {
				if (errno != ENOENT)
					warning("error reading path '%s': %s",
						iter->base.path.buf,
						strerror(errno));
				continue;
			}

			/*
			 * We have to set these each time because
			 * the path strbuf might have been realloc()ed.
			 */
			iter->base.relative_path =
				iter->base.path.buf + iter->levels[0].prefix_len;
			iter->base.basename =
				iter->base.path.buf + level->prefix_len;
			level->dir_state = DIR_STATE_ITER;

			return ITER_OK;
		}
	}
}