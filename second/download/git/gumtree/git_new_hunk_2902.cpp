			i--;

	for (i = 0; i < req_nr; i++)
		if (!(refs.objects[i].item->flags & SHOWN)) {
			if (++ret == 1)
				error("%s", message);
			error("%s %s", oid_to_hex(&refs.objects[i].item->oid),
				refs.objects[i].name);
		}

	clear_commit_marks_for_object_array(&refs, ALL_REV_FLAGS);
	free(refs.objects);

