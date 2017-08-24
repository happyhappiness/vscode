do {
			fsetnum(p, n->avail->rename_num++);
		} while (!__archive_rb_tree_insert_node(
		    &(idr->rbtree), &(n->rbnode)));