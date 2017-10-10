		read_loose_refs(entry->name, dir);
		entry->flag &= ~REF_INCOMPLETE;
	}
	return dir;
}

static struct ref_entry *create_ref_entry(const char *refname,
					  const unsigned char *sha1, int flag,
					  int check_name)
{
	int len;
	struct ref_entry *ref;

	if (check_name &&
	    check_refname_format(refname, REFNAME_ALLOW_ONELEVEL|REFNAME_DOT_COMPONENT))
		die("Reference has invalid format: '%s'", refname);
	len = strlen(refname) + 1;
	ref = xmalloc(sizeof(struct ref_entry) + len);
	hashcpy(ref->u.value.sha1, sha1);
	hashclr(ref->u.value.peeled);
	memcpy(ref->name, refname, len);
	ref->flag = flag;
