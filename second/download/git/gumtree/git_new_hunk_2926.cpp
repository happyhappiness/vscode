		return fsck_walk_tree((struct tree *)obj, data, options);
	case OBJ_COMMIT:
		return fsck_walk_commit((struct commit *)obj, data, options);
	case OBJ_TAG:
		return fsck_walk_tag((struct tag *)obj, data, options);
	default:
		error("Unknown object type for %s", oid_to_hex(&obj->oid));
		return -1;
	}
}

/*
 * The entries in a tree are ordered in the _path_ order,
