static int threeway_callback(int n, unsigned long mask, unsigned long dirmask, struct name_entry *entry, struct traverse_info *info)
{
	/* Same in both? */
	if (same_entry(entry+1, entry+2) || both_empty(entry+1, entry+2)) {
		/* Modified, added or removed identically */
		resolve(info, NULL, entry+1);
		return mask;
	}

	if (same_entry(entry+0, entry+1)) {
		if (entry[2].oid && !S_ISDIR(entry[2].mode)) {
			/* We did not touch, they modified -- take theirs */
			resolve(info, entry+1, entry+2);
			return mask;
		}
		/*
		 * If we did not touch a directory but they made it
		 * into a file, we fall through and unresolved()
		 * recurses down.  Likewise for the opposite case.
		 */
	}

	if (same_entry(entry+0, entry+2) || both_empty(entry+0, entry+2)) {
		/* We added, modified or removed, they did not touch -- take ours */
		resolve(info, NULL, entry+1);
		return mask;
	}

	unresolved(info, entry);
	return mask;
}