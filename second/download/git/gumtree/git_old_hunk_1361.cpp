		name = arg;
		type = NORMAL;
		if (*arg == '^') {
			name++;
			type = REVERSED;
		}
		if (!get_sha1_with_context(name, flags, sha1, &unused)) {
			if (verify)
				revs_count++;
			else
				show_rev(type, sha1, name);
			continue;
		}
		if (verify)
			die_no_single_rev(quiet);
		if (has_dashdash)
			die("bad revision '%s'", arg);
