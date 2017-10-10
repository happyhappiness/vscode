				free(entry);
				continue;
			}
			hashmap_add(&working_tree_dups, entry);

			if (!use_wt_file(workdir, dst_path, &roid)) {
				if (checkout_path(rmode, &roid, dst_path, &rstate))
					return error("could not write '%s'",
						     dst_path);
			} else if (!is_null_oid(&roid)) {
				/*
				 * Changes in the working tree need special
				 * treatment since they are not part of the
				 * index.
				 */
