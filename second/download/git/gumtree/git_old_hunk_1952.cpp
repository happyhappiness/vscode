		}
	}

	if (cpath.nr) {
		struct string_list_item *item;

		sort_string_list(&cpath);
		for_each_string_list_item(item, &cpath)
			fprintf(stderr, "U %s\n", item->string);
		string_list_clear(&cpath, 0);

		rerere(0);
	}
