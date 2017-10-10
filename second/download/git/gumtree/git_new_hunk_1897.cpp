		if (!revs->tree_objects)
			return NULL;
		if (flags & UNINTERESTING) {
			mark_tree_contents_uninteresting(tree);
			return NULL;
		}
		add_pending_object_with_path(revs, object, name, mode, path);
		return NULL;
	}

	/*
	 * Blob object? You know the drill by now..
	 */
	if (object->type == OBJ_BLOB) {
		if (!revs->blob_objects)
			return NULL;
		if (flags & UNINTERESTING)
			return NULL;
		add_pending_object_with_path(revs, object, name, mode, path);
		return NULL;
	}
	die("%s is unknown object", name);
}

static int everybody_uninteresting(struct commit_list *orig)
