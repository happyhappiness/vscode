	/*
	 * Missing unreachable object? Ignore it. It's not like
	 * we miss it (since it can't be reached), nor do we want
	 * to complain about it being unreachable (since it does
	 * not exist).
	 */
	if (!obj->parsed)
		return;

	/*
	 * Unreachable object that exists? Show it if asked to,
	 * since this is something that is prunable.
	 */
	if (show_unreachable) {
		printf("unreachable %s %s\n", typename(obj->type),
			describe_object(obj));
		return;
	}

	/*
	 * "!used" means that nothing at all points to it, including
