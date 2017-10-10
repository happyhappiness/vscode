		}

		switch(commit->object.type) {
		case OBJ_COMMIT:
			break;
		case OBJ_BLOB:
			export_blob(&commit->object.oid);
			continue;
		default: /* OBJ_TAG (nested tags) is already handled */
			warning("Tag points to object of unexpected type %s, skipping.",
				typename(commit->object.type));
			continue;
		}
