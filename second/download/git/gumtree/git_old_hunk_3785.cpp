
		entries = get_unmerged();
		record_df_conflict_files(o, entries);
		re_head  = get_renames(o, head, common, head, merge, entries);
		re_merge = get_renames(o, merge, common, head, merge, entries);
		clean = process_renames(o, re_head, re_merge);
		for (i = entries->nr-1; 0 <= i; i--) {
			const char *path = entries->items[i].string;
			struct stage_data *e = entries->items[i].util;
			if (!e->processed
				&& !process_entry(o, path, e))
				clean = 0;
		}
		for (i = 0; i < entries->nr; i++) {
			struct stage_data *e = entries->items[i].util;
			if (!e->processed)
				die(_("Unprocessed path??? %s"),
				    entries->items[i].string);
		}

		string_list_clear(re_merge, 0);
		string_list_clear(re_head, 0);
		string_list_clear(entries, 1);
