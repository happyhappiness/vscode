			mid = (lo + hi)/2;
			if (base_offset < obj_list[mid].offset) {
				hi = mid;
			} else if (base_offset > obj_list[mid].offset) {
				lo = mid + 1;
			} else {
				oidcpy(&base_oid, &obj_list[mid].oid);
				base_found = !is_null_oid(&base_oid);
				break;
			}
		}
		if (!base_found) {
			/*
			 * The delta base object is itself a delta that
			 * has not been resolved yet.
			 */
			oidclr(&obj_list[nr].oid);
			add_delta_to_list(nr, &null_oid, base_offset, delta_data, delta_size);
			return;
		}
	}

	if (resolve_against_held(nr, &base_oid, delta_data, delta_size))
		return;

	base = read_sha1_file(base_oid.hash, &type, &base_size);
	if (!base) {
		error("failed to read delta-pack base object %s",
		      oid_to_hex(&base_oid));
		if (!recover)
			exit(1);
		has_errors = 1;
		return;
	}
	resolve_delta(nr, type, base, base_size, delta_data, delta_size);
