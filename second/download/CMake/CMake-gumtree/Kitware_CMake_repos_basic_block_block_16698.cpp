{
	struct mtree_entry *me;
	const char *s;
	int r;
	static const struct archive_rb_tree_ops rb_ops = {
		mtree_entry_cmp_node, mtree_entry_cmp_key
	};

	me = calloc(1, sizeof(*me));
	if (me == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate memory for a mtree entry");
		*m_entry = NULL;
		return (ARCHIVE_FATAL);
	}

	r = mtree_entry_setup_filenames(a, me, entry);
	if (r < ARCHIVE_WARN) {
		mtree_entry_free(me);
		*m_entry = NULL;
		return (r);
	}

	if ((s = archive_entry_symlink(entry)) != NULL)
		archive_strcpy(&me->symlink, s);
	me->nlink = archive_entry_nlink(entry);
	me->filetype = archive_entry_filetype(entry);
	me->mode = archive_entry_mode(entry) & 07777;
	me->uid = archive_entry_uid(entry);
	me->gid = archive_entry_gid(entry);
	if ((s = archive_entry_uname(entry)) != NULL)
		archive_strcpy(&me->uname, s);
	if ((s = archive_entry_gname(entry)) != NULL)
		archive_strcpy(&me->gname, s);
	if ((s = archive_entry_fflags_text(entry)) != NULL)
		archive_strcpy(&me->fflags_text, s);
	archive_entry_fflags(entry, &me->fflags_set, &me->fflags_clear);
	me->mtime = archive_entry_mtime(entry);
	me->mtime_nsec = archive_entry_mtime_nsec(entry);
	me->rdevmajor = archive_entry_rdevmajor(entry);
	me->rdevminor = archive_entry_rdevminor(entry);
	me->devmajor = archive_entry_devmajor(entry);
	me->devminor = archive_entry_devminor(entry);
	me->ino = archive_entry_ino(entry);
	me->size = archive_entry_size(entry);
	if (me->filetype == AE_IFDIR) {
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
	} else if (me->filetype == AE_IFREG) {
		me->reg_info = calloc(1, sizeof(*me->reg_info));
		if (me->reg_info == NULL) {
			mtree_entry_free(me);
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory for a mtree entry");
			*m_entry = NULL;
			return (ARCHIVE_FATAL);
		}
		me->reg_info->compute_sum = 0;
	}

	*m_entry = me;
	return (ARCHIVE_OK);
}