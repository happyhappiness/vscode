		if (!object) {
			if (flags & UNINTERESTING)
				return NULL;
			die("bad object %s", sha1_to_hex(tag->tagged->sha1));
		}
		object->flags |= flags;
	}

	/*
	 * Commit object? Just return it, we'll do all the complex
	 * reachability crud.
	 */
