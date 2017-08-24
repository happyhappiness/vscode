{
		me->dir_info = calloc(1, sizeof(*me->dir_info));
		if (me->dir_info == NULL) {
			mtree_entry_free(me);
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory for a mtree entry");
			*m_entry = NULL;
			return (ARCHIVE_FATAL);
		}
		__archive_rb_tree_init(&me->dir_info->rbtree, &rb_ops);
		me->dir_info->children.first = NULL;
		me->dir_info->children.last = &(me->dir_info->children.first);
		me->dir_info->chnext = NULL;
	}