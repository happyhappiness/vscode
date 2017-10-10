			default:
				return "Invalid denyDeleteCurrent setting";
			}
		}
	}

	if (deny_non_fast_forwards && !is_null_oid(new_oid) &&
	    !is_null_oid(old_oid) &&
	    starts_with(name, "refs/heads/")) {
		struct object *old_object, *new_object;
		struct commit *old_commit, *new_commit;

		old_object = parse_object(old_oid->hash);
		new_object = parse_object(new_oid->hash);

		if (!old_object || !new_object ||
		    old_object->type != OBJ_COMMIT ||
		    new_object->type != OBJ_COMMIT) {
			error("bad sha1 objects for %s", name);
			return "bad ref";
