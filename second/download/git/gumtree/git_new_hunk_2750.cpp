			die("bad object %s", sha1_to_hex(tag->tagged->sha1));
		}
		object->flags |= flags;
		/*
		 * We'll handle the tagged object by looping or dropping
		 * through to the non-tag handlers below. Do not
		 * propagate path data from the tag's pending entry.
		 */
		path = NULL;
		mode = 0;
	}

	/*
	 * Commit object? Just return it, we'll do all the complex
