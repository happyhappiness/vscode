static void
write_global(struct mtree_writer *mtree)
{
	struct archive_string setstr;
	struct archive_string unsetstr;
	struct att_counter_set *acs;
	int keys, oldkeys, effkeys;

	archive_string_init(&setstr);
	archive_string_init(&unsetstr);
	keys = mtree->keys & SET_KEYS;
	oldkeys = mtree->set.keys;
	effkeys = keys;
	acs = &mtree->acs;
	if (mtree->set.processing) {
		/*
		 * Check if the global data needs updating.
		 */
		effkeys &= ~F_TYPE;
		if (acs->uid_list == NULL)
			effkeys &= ~(F_UNAME | F_UID);
		else if (oldkeys & (F_UNAME | F_UID)) {
			if (acs->uid_list->count < 2 ||
			    mtree->set.uid == acs->uid_list->m_entry->uid)
				effkeys &= ~(F_UNAME | F_UID);
		}
		if (acs->gid_list == NULL)
			effkeys &= ~(F_GNAME | F_GID);
		else if (oldkeys & (F_GNAME | F_GID)) {
			if (acs->gid_list->count < 2 ||
			    mtree->set.gid == acs->gid_list->m_entry->gid)
				effkeys &= ~(F_GNAME | F_GID);
		}
		if (acs->mode_list == NULL)
			effkeys &= ~F_MODE;
		else if (oldkeys & F_MODE) {
			if (acs->mode_list->count < 2 ||
			    mtree->set.mode == acs->mode_list->m_entry->mode)
				effkeys &= ~F_MODE;
		}
		if (acs->flags_list == NULL)
			effkeys &= ~F_FLAGS;
		else if ((oldkeys & F_FLAGS) != 0) {
			if (acs->flags_list->count < 2 ||
			    (acs->flags_list->m_entry->fflags_set ==
				mtree->set.fflags_set &&
			     acs->flags_list->m_entry->fflags_clear ==
				mtree->set.fflags_clear))
				effkeys &= ~F_FLAGS;
		}
	} else {
		if (acs->uid_list == NULL)
			keys &= ~(F_UNAME | F_UID);
		if (acs->gid_list == NULL)
			keys &= ~(F_GNAME | F_GID);
		if (acs->mode_list == NULL)
			keys &= ~F_MODE;
		if (acs->flags_list == NULL)
			keys &= ~F_FLAGS;
	}
	if ((keys & effkeys & F_TYPE) != 0) {
		if (mtree->dironly) {
			archive_strcat(&setstr, " type=dir");
			mtree->set.type = AE_IFDIR;
		} else {
			archive_strcat(&setstr, " type=file");
			mtree->set.type = AE_IFREG;
		}
	}
	if ((keys & effkeys & F_UNAME) != 0) {
		if (archive_strlen(&(acs->uid_list->m_entry->uname)) > 0) {
			archive_strcat(&setstr, " uname=");
			mtree_quote(&setstr, acs->uid_list->m_entry->uname.s);
		} else {
			keys &= ~F_UNAME;
			if ((oldkeys & F_UNAME) != 0)
				archive_strcat(&unsetstr, " uname");
		}
	}
	if ((keys & effkeys & F_UID) != 0) {
		mtree->set.uid = acs->uid_list->m_entry->uid;
		archive_string_sprintf(&setstr, " uid=%jd",
		    (intmax_t)mtree->set.uid);
	}
	if ((keys & effkeys & F_GNAME) != 0) {
		if (archive_strlen(&(acs->gid_list->m_entry->gname)) > 0) {
			archive_strcat(&setstr, " gname=");
			mtree_quote(&setstr, acs->gid_list->m_entry->gname.s);
		} else {
			keys &= ~F_GNAME;
			if ((oldkeys & F_GNAME) != 0)
				archive_strcat(&unsetstr, " gname");
		}
	}
	if ((keys & effkeys & F_GID) != 0) {
		mtree->set.gid = acs->gid_list->m_entry->gid;
		archive_string_sprintf(&setstr, " gid=%jd",
		    (intmax_t)mtree->set.gid);
	}
	if ((keys & effkeys & F_MODE) != 0) {
		mtree->set.mode = acs->mode_list->m_entry->mode;
		archive_string_sprintf(&setstr, " mode=%o",
		    (unsigned int)mtree->set.mode);
	}
	if ((keys & effkeys & F_FLAGS) != 0) {
		if (archive_strlen(
		    &(acs->flags_list->m_entry->fflags_text)) > 0) {
			archive_strcat(&setstr, " flags=");
			mtree_quote(&setstr,
			    acs->flags_list->m_entry->fflags_text.s);
			mtree->set.fflags_set =
			    acs->flags_list->m_entry->fflags_set;
			mtree->set.fflags_clear =
			    acs->flags_list->m_entry->fflags_clear;
		} else {
			keys &= ~F_FLAGS;
			if ((oldkeys & F_FLAGS) != 0)
				archive_strcat(&unsetstr, " flags");
		}
	}
	if (unsetstr.length > 0)
		archive_string_sprintf(&mtree->buf, "/unset%s\n", unsetstr.s);
	archive_string_free(&unsetstr);
	if (setstr.length > 0)
		archive_string_sprintf(&mtree->buf, "/set%s\n", setstr.s);
	archive_string_free(&setstr);
	mtree->set.keys = keys;
	mtree->set.processing = 1;
}