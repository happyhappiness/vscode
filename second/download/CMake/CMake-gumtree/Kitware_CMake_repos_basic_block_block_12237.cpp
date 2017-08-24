{
		if (mtree->this_entry == NULL)
			return (ARCHIVE_EOF);
		if (strcmp(mtree->this_entry->name, "..") == 0) {
			mtree->this_entry->used = 1;
			if (archive_strlen(&mtree->current_dir) > 0) {
				/* Roll back current path. */
				p = mtree->current_dir.s
				    + mtree->current_dir.length - 1;
				while (p >= mtree->current_dir.s && *p != '/')
					--p;
				if (p >= mtree->current_dir.s)
					--p;
				mtree->current_dir.length
				    = p - mtree->current_dir.s + 1;
			}
		}
		if (!mtree->this_entry->used) {
			use_next = 0;
			r = parse_file(a, entry, mtree, mtree->this_entry,
				&use_next);
			if (use_next == 0)
				return (r);
		}
		mtree->this_entry = mtree->this_entry->next;
	}