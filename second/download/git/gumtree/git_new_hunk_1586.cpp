			if (!end || *end || depth <= 0)
				die("Invalid deepen: %s", line);
			continue;
		}
		if (skip_prefix(line, "deepen-since ", &arg)) {
			char *end = NULL;
			deepen_since = parse_timestamp(arg, &end, 0);
			if (!end || *end || !deepen_since ||
			    /* revisions.c's max_age -1 is special */
			    deepen_since == -1)
				die("Invalid deepen-since: %s", line);
			deepen_rev_list = 1;
			continue;
		}
		if (skip_prefix(line, "deepen-not ", &arg)) {
			char *ref = NULL;
			struct object_id oid;
			if (expand_ref(arg, strlen(arg), oid.hash, &ref) != 1)
				die("git upload-pack: ambiguous deepen-not: %s", line);
			string_list_append(&deepen_not, ref);
			free(ref);
			deepen_rev_list = 1;
			continue;
		}
		if (!skip_prefix(line, "want ", &arg) ||
		    get_oid_hex(arg, &oid_buf))
			die("git upload-pack: protocol error, "
			    "expected to get sha, not '%s'", line);

		features = arg + 40;

		if (parse_feature_request(features, "deepen-relative"))
