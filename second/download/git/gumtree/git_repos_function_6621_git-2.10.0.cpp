static int expand_refs_wildcard(const char *ls_remote_result, int numrefs,
				const char **refs)
{
	int i, matchlen, replacelen;
	int found_one = 0;
	const char *remote = *refs++;
	numrefs--;

	if (numrefs == 0) {
		fprintf(stderr, "Nothing specified for fetching with remote.%s.fetch\n",
			remote);
		printf("empty\n");
	}

	for (i = 0; i < numrefs; i++) {
		const char *ref = refs[i];
		const char *lref = ref;
		const char *colon;
		const char *tail;
		const char *ls;
		const char *next;

		if (*lref == '+')
			lref++;
		colon = strchr(lref, ':');
		tail = lref + strlen(lref);
		if (!(colon &&
		      2 < colon - lref &&
		      colon[-1] == '*' &&
		      colon[-2] == '/' &&
		      2 < tail - (colon + 1) &&
		      tail[-1] == '*' &&
		      tail[-2] == '/')) {
			/* not a glob */
			if (!found_one++)
				printf("explicit\n");
			printf("%s\n", ref);
			continue;
		}

		/* glob */
		if (!found_one++)
			printf("glob\n");

		/* lref to colon-2 is remote hierarchy name;
		 * colon+1 to tail-2 is local.
		 */
		matchlen = (colon-1) - lref;
		replacelen = (tail-1) - (colon+1);
		for (ls = ls_remote_result; ls; ls = next) {
			const char *eol;
			unsigned char sha1[20];
			int namelen;

			while (*ls && isspace(*ls))
				ls++;
			next = strchr(ls, '\n');
			eol = !next ? (ls + strlen(ls)) : next;
			if (!memcmp("^{}", eol-3, 3))
				continue;
			if (eol - ls < 40)
				continue;
			if (get_sha1_hex(ls, sha1))
				continue;
			ls += 40;
			while (ls < eol && isspace(*ls))
				ls++;
			/* ls to next (or eol) is the name.
			 * is it identical to lref to colon-2?
			 */
			if ((eol - ls) <= matchlen ||
			    strncmp(ls, lref, matchlen))
				continue;

			/* Yes, it is a match */
			namelen = eol - ls;
			if (lref != ref)
				putchar('+');
			printf("%.*s:%.*s%.*s\n",
			       namelen, ls,
			       replacelen, colon + 1,
			       namelen - matchlen, ls + matchlen);
		}
	}
	return 0;
}