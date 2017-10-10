
	if (result)
		unlink(path);
	return result;
}

void enable_delayed_checkout(struct checkout *state)
{
	if (!state->delayed_checkout) {
		state->delayed_checkout = xmalloc(sizeof(*state->delayed_checkout));
		state->delayed_checkout->state = CE_CAN_DELAY;
		string_list_init(&state->delayed_checkout->filters, 0);
		string_list_init(&state->delayed_checkout->paths, 0);
	}
}

static int remove_available_paths(struct string_list_item *item, void *cb_data)
{
	struct string_list *available_paths = cb_data;
	struct string_list_item *available;

	available = string_list_lookup(available_paths, item->string);
	if (available)
		available->util = (void *)item->string;
	return !available;
}

int finish_delayed_checkout(struct checkout *state)
{
	int errs = 0;
	struct string_list_item *filter, *path;
	struct delayed_checkout *dco = state->delayed_checkout;

	if (!state->delayed_checkout)
		return errs;

	dco->state = CE_RETRY;
	while (dco->filters.nr > 0) {
		for_each_string_list_item(filter, &dco->filters) {
			struct string_list available_paths = STRING_LIST_INIT_NODUP;

			if (!async_query_available_blobs(filter->string, &available_paths)) {
				/* Filter reported an error */
				errs = 1;
				filter->string = "";
				continue;
			}
			if (available_paths.nr <= 0) {
				/*
				 * Filter responded with no entries. That means
				 * the filter is done and we can remove the
				 * filter from the list (see
				 * "string_list_remove_empty_items" call below).
				 */
				filter->string = "";
				continue;
			}

			/*
			 * In dco->paths we store a list of all delayed paths.
			 * The filter just send us a list of available paths.
			 * Remove them from the list.
			 */
			filter_string_list(&dco->paths, 0,
				&remove_available_paths, &available_paths);

			for_each_string_list_item(path, &available_paths) {
				struct cache_entry* ce;

				if (!path->util) {
					error("external filter '%s' signaled that '%s' "
					      "is now available although it has not been "
					      "delayed earlier",
					      filter->string, path->string);
					errs |= 1;

					/*
					 * Do not ask the filter for available blobs,
					 * again, as the filter is likely buggy.
					 */
					filter->string = "";
					continue;
				}
				ce = index_file_exists(state->istate, path->string,
						       strlen(path->string), 0);
				errs |= (ce ? checkout_entry(ce, state, NULL) : 1);
			}
		}
		string_list_remove_empty_items(&dco->filters, 0);
	}
	string_list_clear(&dco->filters, 0);

	/* At this point we should not have any delayed paths anymore. */
	errs |= dco->paths.nr;
	for_each_string_list_item(path, &dco->paths) {
		error("'%s' was not filtered properly", path->string);
	}
	string_list_clear(&dco->paths, 0);

	free(dco);
	state->delayed_checkout = NULL;

	return errs;
}

static int write_entry(struct cache_entry *ce,
		       char *path, const struct checkout *state, int to_tempfile)
{
	unsigned int ce_mode_s_ifmt = ce->ce_mode & S_IFMT;
	int fd, ret, fstat_done = 0;
	char *new;
