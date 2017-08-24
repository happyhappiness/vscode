(!isoent_add_child_tail(iso9660->cur_dirent, isoent)) {
			np = (struct isoent *)__archive_rb_tree_find_node(
			    &(iso9660->cur_dirent->rbtree),
			    isoent->file->basename.s);
			goto same_entry;
		}