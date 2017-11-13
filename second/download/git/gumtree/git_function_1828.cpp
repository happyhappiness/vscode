static int curate_packed_ref_fn(struct ref_entry *entry, void *cb_data)
{
	struct string_list *refs_to_delete = cb_data;

	if (entry->flag & REF_ISBROKEN) {
		/* This shouldn't happen to packed refs. */
		error("%s is broken!", entry->name);
		string_list_append(refs_to_delete, entry->name);
		return 0;
	}
	if (!has_sha1_file(entry->u.value.sha1)) {
		unsigned char sha1[20];
		int flags;

		if (read_ref_full(entry->name, 0, sha1, &flags))
			/* We should at least have found the packed ref. */
			die("Internal error");
		if ((flags & REF_ISSYMREF) || !(flags & REF_ISPACKED)) {
			/*
			 * This packed reference is overridden by a
			 * loose reference, so it is OK that its value
			 * is no longer valid; for example, it might
			 * refer to an object that has been garbage
			 * collected.  For this purpose we don't even
			 * care whether the loose reference itself is
			 * invalid, broken, symbolic, etc.  Silently
			 * remove the packed reference.
			 */
			string_list_append(refs_to_delete, entry->name);
			return 0;
		}
		/*
		 * There is no overriding loose reference, so the fact
		 * that this reference doesn't refer to a valid object
		 * indicates some kind of repository corruption.
		 * Report the problem, then omit the reference from
		 * the output.
		 */
		error("%s does not point to a valid object!", entry->name);
		string_list_append(refs_to_delete, entry->name);
		return 0;
	}

	return 0;
}