				hdr->hdr_entries = htonl(strtoul(c + 1, &c, 10));
				if (*c)
					die(_("bad %s"), arg);
				input_len = sizeof(*hdr);
			} else if (!strcmp(arg, "-v")) {
				verbose = 1;
			} else if (!strcmp(arg, "-o")) {
				if (index_name || (i+1) >= argc)
					usage(index_pack_usage);
				index_name = argv[++i];
			} else if (starts_with(arg, "--index-version=")) {
				char *c;
