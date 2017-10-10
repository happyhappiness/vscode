		if (obj->type == OBJ_TREE) {
			obj->flags |= flags;
			add_object_array(obj, name, &ent);
		} else if (obj->type == OBJ_BLOB) {
			if (2 <= blobs)
				die(_("more than two blobs given: '%s'"), name);
			hashcpy(blob[blobs].oid.hash, obj->oid.hash);
			blob[blobs].name = name;
			blob[blobs].mode = entry->mode;
			blobs++;

		} else {
			die(_("unhandled object '%s' given."), name);
		}
	}
