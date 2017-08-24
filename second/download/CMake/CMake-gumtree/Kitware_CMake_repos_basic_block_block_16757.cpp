(!np->dir_info->virtual || mtree->classic) {
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