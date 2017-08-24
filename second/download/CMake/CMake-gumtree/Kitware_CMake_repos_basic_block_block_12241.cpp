{
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