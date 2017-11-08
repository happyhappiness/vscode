int check_push_refs(struct ref *src, int nr_refspec, const char **refspec_names)
{
	struct refspec *refspec = parse_push_refspec(nr_refspec, refspec_names);
	int ret = 0;
	int i;

	for (i = 0; i < nr_refspec; i++) {
		struct refspec *rs = refspec + i;

		if (rs->pattern || rs->matching)
			continue;

		ret |= match_explicit_lhs(src, rs, NULL, NULL);
	}

	free_refspec(nr_refspec, refspec);
	return ret;
}