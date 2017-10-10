				continue;
			}
			if (!strcmp(arg, "--symbolic-full-name")) {
				symbolic = SHOW_SYMBOLIC_FULL;
				continue;
			}
			if (starts_with(arg, "--abbrev-ref") &&
			    (!arg[12] || arg[12] == '=')) {
				abbrev_ref = 1;
				abbrev_ref_strict = warn_ambiguous_refs;
				if (arg[12] == '=') {
					if (!strcmp(arg + 13, "strict"))
						abbrev_ref_strict = 1;
					else if (!strcmp(arg + 13, "loose"))
						abbrev_ref_strict = 0;
					else
						die("unknown mode for %s", arg);
				}
				continue;
			}
			if (!strcmp(arg, "--all")) {
				for_each_ref(show_reference, NULL);
				continue;
			}
			if (starts_with(arg, "--disambiguate=")) {
				for_each_abbrev(arg + 15, show_abbrev, NULL);
				continue;
			}
			if (!strcmp(arg, "--bisect")) {
				for_each_ref_in("refs/bisect/bad", show_reference, NULL);
				for_each_ref_in("refs/bisect/good", anti_reference, NULL);
				continue;
			}
			if (starts_with(arg, "--branches=")) {
				for_each_glob_ref_in(show_reference, arg + 11,
					"refs/heads/", NULL);
				clear_ref_exclusion(&ref_excludes);
				continue;
			}
			if (!strcmp(arg, "--branches")) {
				for_each_branch_ref(show_reference, NULL);
				clear_ref_exclusion(&ref_excludes);
				continue;
			}
			if (starts_with(arg, "--tags=")) {
				for_each_glob_ref_in(show_reference, arg + 7,
					"refs/tags/", NULL);
				clear_ref_exclusion(&ref_excludes);
				continue;
			}
			if (!strcmp(arg, "--tags")) {
				for_each_tag_ref(show_reference, NULL);
				clear_ref_exclusion(&ref_excludes);
				continue;
			}
			if (starts_with(arg, "--glob=")) {
				for_each_glob_ref(show_reference, arg + 7, NULL);
				clear_ref_exclusion(&ref_excludes);
				continue;
			}
			if (starts_with(arg, "--remotes=")) {
				for_each_glob_ref_in(show_reference, arg + 10,
					"refs/remotes/", NULL);
				clear_ref_exclusion(&ref_excludes);
				continue;
			}
			if (!strcmp(arg, "--remotes")) {
				for_each_remote_ref(show_reference, NULL);
				clear_ref_exclusion(&ref_excludes);
				continue;
			}
			if (starts_with(arg, "--exclude=")) {
				add_ref_exclusion(&ref_excludes, arg + 10);
				continue;
			}
			if (!strcmp(arg, "--show-toplevel")) {
				const char *work_tree = get_git_work_tree();
				if (work_tree)
					puts(work_tree);
