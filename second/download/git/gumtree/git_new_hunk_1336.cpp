			if (!strcmp(line, "--not")) {
				flags ^= UNINTERESTING;
				write_bitmap_index = 0;
				continue;
			}
			if (starts_with(line, "--shallow ")) {
				struct object_id oid;
				if (get_oid_hex(line + 10, &oid))
					die("not an SHA-1 '%s'", line + 10);
				register_shallow(&oid);
				use_bitmap_index = 0;
				continue;
			}
			die("not a rev '%s'", line);
		}
		if (handle_revision_arg(line, &revs, flags, REVARG_CANNOT_BE_FILENAME))
