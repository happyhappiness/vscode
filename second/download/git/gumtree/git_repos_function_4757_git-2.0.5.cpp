int cmd_pack_redundant(int argc, const char **argv, const char *prefix)
{
	int i;
	struct pack_list *min, *red, *pl;
	struct llist *ignore;
	unsigned char *sha1;
	char buf[42]; /* 40 byte sha1 + \n + \0 */

	if (argc == 2 && !strcmp(argv[1], "-h"))
		usage(pack_redundant_usage);

	for (i = 1; i < argc; i++) {
		const char *arg = argv[i];
		if (!strcmp(arg, "--")) {
			i++;
			break;
		}
		if (!strcmp(arg, "--all")) {
			load_all_packs = 1;
			continue;
		}
		if (!strcmp(arg, "--verbose")) {
			verbose = 1;
			continue;
		}
		if (!strcmp(arg, "--alt-odb")) {
			alt_odb = 1;
			continue;
		}
		if (*arg == '-')
			usage(pack_redundant_usage);
		else
			break;
	}

	prepare_packed_git();

	if (load_all_packs)
		load_all();
	else
		while (*(argv + i) != NULL)
			add_pack_file(*(argv + i++));

	if (local_packs == NULL)
		die("Zero packs found!");

	load_all_objects();

	cmp_local_packs();
	if (alt_odb)
		scan_alt_odb_packs();

	/* ignore objects given on stdin */
	llist_init(&ignore);
	if (!isatty(0)) {
		while (fgets(buf, sizeof(buf), stdin)) {
			sha1 = xmalloc(20);
			if (get_sha1_hex(buf, sha1))
				die("Bad sha1 on stdin: %s", buf);
			llist_insert_sorted_unique(ignore, sha1, NULL);
		}
	}
	llist_sorted_difference_inplace(all_objects, ignore);
	pl = local_packs;
	while (pl) {
		llist_sorted_difference_inplace(pl->unique_objects, ignore);
		pl = pl->next;
	}

	minimize(&min);

	if (verbose) {
		fprintf(stderr, "There are %lu packs available in alt-odbs.\n",
			(unsigned long)pack_list_size(altodb_packs));
		fprintf(stderr, "The smallest (bytewise) set of packs is:\n");
		pl = min;
		while (pl) {
			fprintf(stderr, "\t%s\n", pl->pack->pack_name);
			pl = pl->next;
		}
		fprintf(stderr, "containing %lu duplicate objects "
				"with a total size of %lukb.\n",
			(unsigned long)get_pack_redundancy(min),
			(unsigned long)pack_set_bytecount(min)/1024);
		fprintf(stderr, "A total of %lu unique objects were considered.\n",
			(unsigned long)all_objects->size);
		fprintf(stderr, "Redundant packs (with indexes):\n");
	}
	pl = red = pack_list_difference(local_packs, min);
	while (pl) {
		printf("%s\n%s\n",
		       sha1_pack_index_name(pl->pack->sha1),
		       pl->pack->pack_name);
		pl = pl->next;
	}
	if (verbose)
		fprintf(stderr, "%luMB of redundant packs in total.\n",
			(unsigned long)pack_set_bytecount(red)/(1024*1024));

	return 0;
}