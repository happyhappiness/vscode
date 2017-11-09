int dir_iterator_abort(struct dir_iterator *dir_iterator)
{
	struct dir_iterator_int *iter = (struct dir_iterator_int *)dir_iterator;

	for (; iter->levels_nr; iter->levels_nr--) {
		struct dir_iterator_level *level =
			&iter->levels[iter->levels_nr - 1];

		if (level->dir && closedir(level->dir)) {
			strbuf_setlen(&iter->base.path, level->prefix_len);
			warning("error closing directory %s: %s",
				iter->base.path.buf, strerror(errno));
		}
	}

	free(iter->levels);
	strbuf_release(&iter->base.path);
	free(iter);
	return ITER_DONE;
}