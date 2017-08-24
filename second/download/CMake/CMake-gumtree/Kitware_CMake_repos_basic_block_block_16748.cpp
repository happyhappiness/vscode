do {
		if (mtree->output_global_set) {
			/*
			 * Collect attribute information to know which value
			 * is frequently used among the children.
			 */
			attr_counter_set_reset(mtree);
			ARCHIVE_RB_TREE_FOREACH(n, &(np->dir_info->rbtree)) {
				struct mtree_entry *e = (struct mtree_entry *)n;
				if (attr_counter_set_collect(mtree, e) < 0) {
					archive_set_error(&a->archive, ENOMEM,
					    "Can't allocate memory");
					return (ARCHIVE_FATAL);
				}
			}
		}
		if (!np->dir_info->virtual || mtree->classic) {
			ret = write_mtree_entry(a, np);
			if (ret != ARCHIVE_OK)
				return (ARCHIVE_FATAL);
		} else {
			/* Whenever output_global_set is enabled
			 * output global value(/set keywords)
			 * even if the directory entry is not allowed
			 * to be written because the global values
			 * can be used for the children. */
			if (mtree->output_global_set)
				write_global(mtree);
		}
		/*
		 * Output the attribute of all files except directory files.
		 */
		mtree->depth++;
		ARCHIVE_RB_TREE_FOREACH(n, &(np->dir_info->rbtree)) {
			struct mtree_entry *e = (struct mtree_entry *)n;

			if (e->dir_info)
				mtree_entry_add_child_tail(np, e);
			else {
				ret = write_mtree_entry(a, e);
				if (ret != ARCHIVE_OK)
					return (ARCHIVE_FATAL);
			}
		}
		mtree->depth--;

		if (np->dir_info->children.first != NULL) {
			/*
			 * Descend the tree.
			 */
			np = np->dir_info->children.first;
			if (mtree->indent)
				mtree->depth++;
			continue;
		} else if (mtree->classic) {
			/*
			 * While printing mtree classic, if there are not
			 * any directory files(except "." and "..") in the
			 * directory, output two dots ".." as returning
			 * the parent directory.
			 */
			ret = write_dot_dot_entry(a, np);
			if (ret != ARCHIVE_OK)
				return (ARCHIVE_FATAL);
		}

		while (np != np->parent) {
			if (np->dir_info->chnext == NULL) {
				/*
				 * Ascend the tree; go back to the parent.
				 */
				if (mtree->indent)
					mtree->depth--;
				if (mtree->classic) {
					ret = write_dot_dot_entry(a,
						np->parent);
					if (ret != ARCHIVE_OK)
						return (ARCHIVE_FATAL);
				}
				np = np->parent;
			} else {
				/*
				 * Switch to next mtree entry in the directory.
				 */
				np = np->dir_info->chnext;
				break;
			}
		}
	} while (np != np->parent);