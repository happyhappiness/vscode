			did_repo_setup = 1;
		}

		if (!strcmp(arg, "--git-path")) {
			if (!argv[i + 1])
				die("--git-path requires an argument");
			strbuf_reset(&buf);
			puts(relative_path(git_path("%s", argv[i + 1]),
					   prefix, &buf));
			i++;
			continue;
		}
		if (as_is) {
			if (show_file(arg, output_prefix) && as_is < 2)
				verify_filename(prefix, arg, 0);
