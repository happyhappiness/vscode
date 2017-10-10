		if (obj->type == OBJ_TREE) {
			obj->flags |= flags;
			add_object_array(obj, name, &ent);
		} else if (obj->type == OBJ_BLOB) {
			if (2 <= blobs)
				die(_("more than two blobs given: '%s'"), name);
			blob[blobs] = entry;
			blobs++;

		} else {
			die(_("unhandled object '%s' given."), name);
		}
	}
