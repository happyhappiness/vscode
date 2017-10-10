		if (write_locked_index(&the_index, &index_lock, COMMIT_LOCK))
			die("Unable to write new index file");
	} else
		rollback_lock_file(&index_lock);
}

static void remove_variant(struct rerere_id *id)
{
	unlink_or_warn(rerere_path(id, "postimage"));
	unlink_or_warn(rerere_path(id, "preimage"));
	id->collection->status[id->variant] = 0;
}

/*
 * The path indicated by rr_item may still have conflict for which we
 * have a recorded resolution, in which case replay it and optionally
 * update it.  Or it may have been resolved by the user and we may
 * only have the preimage for that conflict, in which case the result
 * needs to be recorded as a resolution in a postimage file.
 */
static void do_rerere_one_path(struct string_list_item *rr_item,
			       struct string_list *update)
{
	const char *path = rr_item->string;
	struct rerere_id *id = rr_item->util;
	struct rerere_dir *rr_dir = id->collection;
	int variant;

	variant = id->variant;

	/* Has the user resolved it already? */
	if (variant >= 0) {
		if (!handle_file(path, NULL, NULL)) {
			copy_file(rerere_path(id, "postimage"), path, 0666);
			id->collection->status[variant] |= RR_HAS_POSTIMAGE;
			fprintf(stderr, "Recorded resolution for '%s'.\n", path);
			free_rerere_id(rr_item);
			rr_item->util = NULL;
			return;
		}
		/*
		 * There may be other variants that can cleanly
		 * replay.  Try them and update the variant number for
		 * this one.
		 */
	}

	/* Does any existing resolution apply cleanly? */
	for (variant = 0; variant < rr_dir->status_nr; variant++) {
		const int both = RR_HAS_PREIMAGE | RR_HAS_POSTIMAGE;
		struct rerere_id vid = *id;

		if ((rr_dir->status[variant] & both) != both)
			continue;

		vid.variant = variant;
		if (merge(&vid, path))
			continue; /* failed to replay */

		/*
		 * If there already is a different variant that applies
		 * cleanly, there is no point maintaining our own variant.
		 */
		if (0 <= id->variant && id->variant != variant)
			remove_variant(id);

		if (rerere_autoupdate)
			string_list_insert(update, path);
		else
			fprintf(stderr,
				"Resolved '%s' using previous resolution.\n",
				path);
		free_rerere_id(rr_item);
		rr_item->util = NULL;
		return;
	}

	/* None of the existing one applies; we need a new variant */
	assign_variant(id);

	variant = id->variant;
	handle_file(path, NULL, rerere_path(id, "preimage"));
	if (id->collection->status[variant] & RR_HAS_POSTIMAGE) {
		const char *path = rerere_path(id, "postimage");
		if (unlink(path))
			die_errno("cannot unlink stray '%s'", path);
		id->collection->status[variant] &= ~RR_HAS_POSTIMAGE;
	}
	id->collection->status[variant] |= RR_HAS_PREIMAGE;
	fprintf(stderr, "Recorded preimage for '%s'\n", path);
}

static int do_plain_rerere(struct string_list *rr, int fd)
{
	struct string_list conflict = STRING_LIST_INIT_DUP;
	struct string_list update = STRING_LIST_INIT_DUP;
