(np->dir_info->chnext == NULL) {
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