			}
			if (!strcmp(arg, "--shared-index-path")) {
				if (read_cache() < 0)
					die(_("Could not read the index"));
				if (the_index.split_index) {
					const unsigned char *sha1 = the_index.split_index->base_sha1;
					puts(git_path("sharedindex.%s", sha1_to_hex(sha1)));
				}
				continue;
			}
			if (skip_prefix(arg, "--since=", &arg)) {
				show_datestring("--max-age=", arg);
				continue;
