static struct bitmap *find_objects(struct rev_info *revs,
				   struct object_list *roots,
				   struct bitmap *seen)
{
	struct bitmap *base = NULL;
	int needs_walk = 0;

	struct object_list *not_mapped = NULL;

	/*
	 * Go through all the roots for the walk. The ones that have bitmaps
	 * on the bitmap index will be `or`ed together to form an initial
	 * global reachability analysis.
	 *
	 * The ones without bitmaps in the index will be stored in the
	 * `not_mapped_list` for further processing.
	 */
	while (roots) {
		struct object *object = roots->item;
		roots = roots->next;

		if (object->type == OBJ_COMMIT) {
			khiter_t pos = kh_get_sha1(bitmap_git.bitmaps, object->sha1);

			if (pos < kh_end(bitmap_git.bitmaps)) {
				struct stored_bitmap *st = kh_value(bitmap_git.bitmaps, pos);
				struct ewah_bitmap *or_with = lookup_stored_bitmap(st);

				if (base == NULL)
					base = ewah_to_bitmap(or_with);
				else
					bitmap_or_ewah(base, or_with);

				object->flags |= SEEN;
				continue;
			}
		}

		object_list_insert(object, &not_mapped);
	}

	/*
	 * Best case scenario: We found bitmaps for all the roots,
	 * so the resulting `or` bitmap has the full reachability analysis
	 */
	if (not_mapped == NULL)
		return base;

	roots = not_mapped;

	/*
	 * Let's iterate through all the roots that don't have bitmaps to
	 * check if we can determine them to be reachable from the existing
	 * global bitmap.
	 *
	 * If we cannot find them in the existing global bitmap, we'll need
	 * to push them to an actual walk and run it until we can confirm
	 * they are reachable
	 */
	while (roots) {
		struct object *object = roots->item;
		int pos;

		roots = roots->next;
		pos = bitmap_position(object->sha1);

		if (pos < 0 || base == NULL || !bitmap_get(base, pos)) {
			object->flags &= ~UNINTERESTING;
			add_pending_object(revs, object, "");
			needs_walk = 1;
		} else {
			object->flags |= SEEN;
		}
	}

	if (needs_walk) {
		struct include_data incdata;

		if (base == NULL)
			base = bitmap_new();

		incdata.base = base;
		incdata.seen = seen;

		revs->include_check = should_include;
		revs->include_check_data = &incdata;

		if (prepare_revision_walk(revs))
			die("revision walk setup failed");

		traverse_commit_list(revs, show_commit, show_object, base);
	}

	return base;
}