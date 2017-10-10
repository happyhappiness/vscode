	 * except if it was in a pack-file and we didn't
	 * do a full fsck
	 */
	if (!(obj->flags & HAS_OBJ)) {
		if (has_sha1_pack(obj->sha1))
			return; /* it is in pack - forget about it */
		printf("missing %s %s\n", typename(obj->type), sha1_to_hex(obj->sha1));
		errors_found |= ERROR_REACHABLE;
		return;
	}
}

