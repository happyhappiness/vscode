{
		n = (struct idrent *)__archive_rb_tree_find_node(
		    &(idr->rbtree), idrent->isoent);
		if (n != NULL) {
			/* this `idrent' needs to rename. */
			idrent->avail = n;
			*idr->wait_list.last = idrent;
			idr->wait_list.last = &(idrent->wnext);
		}
	}