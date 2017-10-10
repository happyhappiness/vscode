			last = dir->entries[i++] = entry;
	}
	dir->sorted = dir->nr = i;
}

/*
 * Return true if refname, which has the specified oid and flags, can
 * be resolved to an object in the database. If the referred-to object
 * does not exist, emit a warning and return false.
 */
static int ref_resolves_to_object(const char *refname,
				  const struct object_id *oid,
				  unsigned int flags)
{
	if (flags & REF_ISBROKEN)
		return 0;
	if (!has_sha1_file(oid->hash)) {
		error("%s does not point to a valid object!", refname);
		return 0;
	}
	return 1;
}

/*
 * Return true if the reference described by entry can be resolved to
 * an object in the database; otherwise, emit a warning and return
 * false.
 */
static int entry_resolves_to_object(struct ref_entry *entry)
{
	return ref_resolves_to_object(entry->name,
				      &entry->u.value.oid, entry->flag);
}

typedef int each_ref_entry_fn(struct ref_entry *entry, void *cb_data);

/*
 * Call fn for each reference in dir that has index in the range
 * offset <= index < dir->nr.  Recurse into subdirectories that are in
 * that index range, sorting them before iterating.  This function
 * does not sort dir itself; it should be sorted beforehand.  fn is
 * called for all references, including broken ones.
