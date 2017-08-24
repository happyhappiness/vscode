(filename_length >= 9 &&
			    strncmp("__MACOSX/", name, 9) == 0) {
				/* If this file is not a resource fork nor
				 * a directory. We should treat it as a non
				 * resource fork file to expose it. */
				if (name[filename_length-1] != '/' &&
				    (r - name < 3 || r[0] != '.' || r[1] != '_')) {
					__archive_rb_tree_insert_node(
					    &zip->tree, &zip_entry->node);
					/* Expose its parent directories. */
					expose_parent_dirs(zip, name,
					    filename_length);
				} else {
					/* This file is a resource fork file or
					 * a directory. */
					archive_strncpy(&(zip_entry->rsrcname),
					     name, filename_length);
					__archive_rb_tree_insert_node(
					    &zip->tree_rsrc, &zip_entry->node);
				}
			} else {
				/* Generate resource fork name to find its
				 * resource file at zip->tree_rsrc. */
				archive_strcpy(&(zip_entry->rsrcname),
				    "__MACOSX/");
				archive_strncat(&(zip_entry->rsrcname),
				    name, r - name);
				archive_strcat(&(zip_entry->rsrcname), "._");
				archive_strncat(&(zip_entry->rsrcname),
				    name + (r - name),
				    filename_length - (r - name));
				/* Register an entry to RB tree to sort it by
				 * file offset. */
				__archive_rb_tree_insert_node(&zip->tree,
				    &zip_entry->node);
			}