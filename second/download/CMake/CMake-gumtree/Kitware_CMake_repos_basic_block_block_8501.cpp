{
		ap2 = acl_new_entry(dest,
		    ap->type, ap->permset, ap->tag, ap->id);
		if (ap2 != NULL)
			archive_mstring_copy(&ap2->name, &ap->name);
		ap = ap->next;
	}