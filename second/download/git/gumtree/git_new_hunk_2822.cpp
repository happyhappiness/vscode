
	/*
	 * Unreachable object that exists? Show it if asked to,
	 * since this is something that is prunable.
	 */
	if (show_unreachable) {
		printf("unreachable %s %s\n", typename(obj->type), oid_to_hex(&obj->oid));
		return;
	}

	/*
	 * "!used" means that nothing at all points to it, including
	 * other unreachable objects. In other words, it's the "tip"
