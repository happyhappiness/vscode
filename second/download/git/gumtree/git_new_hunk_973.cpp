			}
			if (!strcmp(arg, "--shared-index-path")) {
				if (read_cache() < 0)
					die(_("Could not read the index"));
				if (the_index.split_index) {
					const unsigned char *sha1 = the_index.split_index->base_sha1;
					const char *path = git_path("sharedindex.%s", sha1_to_hex(sha1));
					strbuf_reset(&buf);
					puts(relative_path(path, prefix, &buf));
				}
				continue;
			}
			if (skip_prefix(arg, "--since=", &arg)) {
				show_datestring("--max-age=", arg);
				continue;
