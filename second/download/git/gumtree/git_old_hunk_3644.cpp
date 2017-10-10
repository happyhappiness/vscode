
			/* Error is printed by lookup_object(). */
			if (!obj)
				continue;

			obj->used = 1;
			mark_object_reachable(obj);
			heads++;
			continue;
		}
		error("invalid parameter: expected sha1, got '%s'", arg);
	}
