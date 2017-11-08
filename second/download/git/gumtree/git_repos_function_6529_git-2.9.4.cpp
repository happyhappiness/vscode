static int pick_rref(int sha1_only, const char *rref, const char *ls_remote_result)
{
	int err = 0;
	int lrr_count = lrr_count, i, pass;
	const char *cp;
	struct lrr {
		const char *line;
		const char *name;
		int namelen;
		int shown;
	} *lrr_list = lrr_list;

	for (pass = 0; pass < 2; pass++) {
		/* pass 0 counts and allocates, pass 1 fills... */
		cp = ls_remote_result;
		i = 0;
		while (1) {
			const char *np;
			while (*cp && isspace(*cp))
				cp++;
			if (!*cp)
				break;
			np = strchrnul(cp, '\n');
			if (pass) {
				lrr_list[i].line = cp;
				lrr_list[i].name = cp + 41;
				lrr_list[i].namelen = np - (cp + 41);
			}
			i++;
			cp = np;
		}
		if (!pass) {
			lrr_count = i;
			lrr_list = xcalloc(lrr_count, sizeof(*lrr_list));
		}
	}

	while (1) {
		const char *next;
		int rreflen;
		int i;

		while (*rref && isspace(*rref))
			rref++;
		if (!*rref)
			break;
		next = strchrnul(rref, '\n');
		rreflen = next - rref;

		for (i = 0; i < lrr_count; i++) {
			struct lrr *lrr = &(lrr_list[i]);

			if (rreflen == lrr->namelen &&
			    !memcmp(lrr->name, rref, rreflen)) {
				if (!lrr->shown)
					printf("%.*s\n",
					       sha1_only ? 40 : lrr->namelen + 41,
					       lrr->line);
				lrr->shown = 1;
				break;
			}
		}
		if (lrr_count <= i) {
			error("pick-rref: %.*s not found", rreflen, rref);
			err = 1;
		}
		rref = next;
	}
	free(lrr_list);
	return err;
}