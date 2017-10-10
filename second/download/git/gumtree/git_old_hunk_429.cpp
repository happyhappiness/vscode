				hdr->hdr_entries = htonl(strtoul(c + 1, &c, 10));
				if (*c)
					die("bad %s", arg);
				len = sizeof(*hdr);
				continue;
			}
			usage(unpack_usage);
		}

		/* We don't take any non-flag arguments now.. Maybe some day */
		usage(unpack_usage);
	}
