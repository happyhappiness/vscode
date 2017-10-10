		if (ret < 1)
			continue;

		id = new_rerere_id(sha1);
		string_list_insert(rr, path)->util = id;

		/* Ensure that the directory exists. */
		mkdir_in_gitdir(rerere_path(id, NULL));
	}

	for (i = 0; i < rr->nr; i++)
		do_rerere_one_path(&rr->items[i], &update);

	if (update.nr)
