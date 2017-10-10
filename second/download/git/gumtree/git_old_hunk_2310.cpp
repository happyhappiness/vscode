
		refname = parse_ref_line(&line, sha1);
		if (refname) {
			int flag = REF_ISPACKED;

			if (check_refname_format(refname, REFNAME_ALLOW_ONELEVEL)) {
				hashclr(sha1);
				flag |= REF_BAD_NAME | REF_ISBROKEN;
			}
			last = create_ref_entry(refname, sha1, flag, 0);
			if (peeled == PEELED_FULLY ||
			    (peeled == PEELED_TAGS && starts_with(refname, "refs/tags/")))
