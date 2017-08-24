{
					__archive_rb_tree_insert_node(
					    &zip->tree, &zip_entry->node);
					/* Expose its parent directories. */
					expose_parent_dirs(zip, name,
					    filename_length);
				}