			die("object not found: %s", oid_to_hex(&oid));

		if (type != OBJ_COMMIT)
			/* only commits */
			continue;

		commit = lookup_commit(&oid);
		if (!commit)
			die("not a commit? can't happen: %s", oid_to_hex(&oid));

		object = &commit->object;

		if (object->flags & SHOWN)
