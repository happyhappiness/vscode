(mtree->output_global_set) {
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