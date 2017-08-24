(!file_add_child_tail(xar->cur_dirent, file)) {
			np = (struct file *)__archive_rb_tree_find_node(
			    &(xar->cur_dirent->rbtree),
			    file->basename.s);
			goto same_entry;
		}