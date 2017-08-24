{
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