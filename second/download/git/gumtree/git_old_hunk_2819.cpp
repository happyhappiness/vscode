	 * mark_object_reachable() calls us.  All the callers of
	 * that function has non-NULL obj hence ...
	 */
	if (!obj) {
		/* ... these references to parent->fld are safe here */
		printf("broken link from %7s %s\n",
			   typename(parent->type), sha1_to_hex(parent->sha1));
		printf("broken link from %7s %s\n",
			   (type == OBJ_ANY ? "unknown" : typename(type)), "unknown");
		errors_found |= ERROR_REACHABLE;
		return 1;
	}

