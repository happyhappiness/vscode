			if (!end || *end || depth <= 0)
				die("Invalid deepen: %s", line);
			continue;
		}
		if (skip_prefix(line, "deepen-since ", &arg)) {
			char *end = NULL;
			deepen_since = strtoul(arg, &end, 0);
			if (!end || *end || !deepen_since ||
			    /* revisions.c's max_age -1 is special */
			    deepen_since == -1)
				die("Invalid deepen-since: %s", line);
			deepen_rev_list = 1;
			continue;
		}
		if (skip_prefix(line, "deepen-not ", &arg)) {
			char *ref = NULL;
			unsigned char sha1[20];
			if (expand_ref(arg, strlen(arg), sha1, &ref) != 1)
				die("git upload-pack: ambiguous deepen-not: %s", line);
			string_list_append(&deepen_not, ref);
			free(ref);
			deepen_rev_list = 1;
			continue;
		}
		if (!skip_prefix(line, "want ", &arg) ||
		    get_sha1_hex(arg, sha1_buf))
			die("git upload-pack: protocol error, "
			    "expected to get sha, not '%s'", line);

		features = arg + 40;

		if (parse_feature_request(features, "deepen-relative"))
