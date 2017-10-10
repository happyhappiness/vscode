		/* Avoid adding the same thing twice */
		for (i = 0; i < ref_name_cnt; i++)
			if (!strcmp(refname, ref_name[i]))
				return 0;
	}
	if (MAX_REVS <= ref_name_cnt) {
		warning("ignoring %s; cannot handle more than %d refs",
			refname, MAX_REVS);
		return 0;
	}
	ref_name[ref_name_cnt++] = xstrdup(refname);
	ref_name[ref_name_cnt] = NULL;
	return 0;
}
