		entry->flag &= ~REF_INCOMPLETE;
	}
	return dir;
}

struct ref_entry *create_ref_entry(const char *refname,
				   const struct object_id *oid, int flag)
{
	struct ref_entry *ref;

	FLEX_ALLOC_STR(ref, name, refname);
	oidcpy(&ref->u.value.oid, oid);
	oidclr(&ref->u.value.peeled);
	ref->flag = flag;
	return ref;
}

struct ref_cache *create_ref_cache(struct ref_store *refs,
