				continue;
			}
			if (!strcmp(arg, "--symbolic-full-name")) {
				symbolic = SHOW_SYMBOLIC_FULL;
				continue;
			}
			if (opt_with_value(arg, "--abbrev-ref", &arg)) {
				abbrev_ref = 1;
				abbrev_ref_strict = warn_ambiguous_refs;
				if (arg) {
					if (!strcmp(arg, "strict"))
						abbrev_ref_strict = 1;
					else if (!strcmp(arg, "loose"))
						abbrev_ref_strict = 0;
					else
						die("unknown mode for --abbrev-ref: %s",
						    arg);
				}
				continue;
			}
			if (!strcmp(arg, "--all")) {
				for_each_ref(show_reference, NULL);
				continue;
			}
			if (skip_prefix(arg, "--disambiguate=", &arg)) {
				for_each_abbrev(arg, show_abbrev, NULL);
				continue;
			}
			if (!strcmp(arg, "--bisect")) {
				for_each_ref_in("refs/bisect/bad", show_reference, NULL);
				for_each_ref_in("refs/bisect/good", anti_reference, NULL);
				continue;
			}
			if (opt_with_value(arg, "--branches", &arg)) {
				handle_ref_opt(arg, "refs/heads/");
				continue;
			}
			if (opt_with_value(arg, "--tags", &arg)) {
				handle_ref_opt(arg, "refs/tags/");
				continue;
			}
			if (skip_prefix(arg, "--glob=", &arg)) {
				handle_ref_opt(arg, NULL);
				continue;
			}
			if (opt_with_value(arg, "--remotes", &arg)) {
				handle_ref_opt(arg, "refs/remotes/");
				continue;
			}
			if (skip_prefix(arg, "--exclude=", &arg)) {
				add_ref_exclusion(&ref_excludes, arg);
				continue;
			}
			if (!strcmp(arg, "--show-toplevel")) {
				const char *work_tree = get_git_work_tree();
				if (work_tree)
					puts(work_tree);
