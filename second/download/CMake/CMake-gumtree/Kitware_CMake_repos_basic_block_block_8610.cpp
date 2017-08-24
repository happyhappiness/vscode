(ap = acl->acl_head; ap != NULL; ap = ap->next) {
		if ((ap->type & want_type) == 0)
			continue;
		/*
		 * Filemode-mapping ACL entries are stored exclusively in
		 * ap->mode so they should not be in the list
		 */
		if ((ap->type == ARCHIVE_ENTRY_ACL_TYPE_ACCESS)
		    && (ap->tag == ARCHIVE_ENTRY_ACL_USER_OBJ
		    || ap->tag == ARCHIVE_ENTRY_ACL_GROUP_OBJ
		    || ap->tag == ARCHIVE_ENTRY_ACL_OTHER))
			continue;
		if (ap->type == ARCHIVE_ENTRY_ACL_TYPE_DEFAULT &&
		    (flags & ARCHIVE_ENTRY_ACL_STYLE_MARK_DEFAULT) != 0)
			prefix = "default:";
		else
			prefix = NULL;
		r = archive_mstring_get_mbs_l(
		    &ap->name, &name, &len, sc);
		if (r != 0)
			return (NULL);
		if (count > 0)
			*p++ = separator;
		if (name == NULL ||
		    (flags & ARCHIVE_ENTRY_ACL_STYLE_EXTRA_ID)) {
			id = ap->id;
		} else {
			id = -1;
		}
		append_entry(&p, prefix, ap->type, ap->tag, flags, name,
		    ap->permset, id);
		count++;
	}