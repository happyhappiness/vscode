static int get_sha1_1(const char *name, int len, unsigned char *sha1, unsigned lookup_flags)
{
	int ret, has_suffix;
	const char *cp;

	/*
	 * "name~3" is "name^^^", "name~" is "name~1", and "name^" is "name^1".
	 */
	has_suffix = 0;
	for (cp = name + len - 1; name <= cp; cp--) {
		int ch = *cp;
		if ('0' <= ch && ch <= '9')
			continue;
		if (ch == '~' || ch == '^')
			has_suffix = ch;
		break;
	}

	if (has_suffix) {
		int num = 0;
		int len1 = cp - name;
		cp++;
		while (cp < name + len)
			num = num * 10 + *cp++ - '0';
		if (!num && len1 == len - 1)
			num = 1;
		if (has_suffix == '^')
			return get_parent(name, len1, sha1, num);
		/* else if (has_suffix == '~') -- goes without saying */
		return get_nth_ancestor(name, len1, sha1, num);
	}

	ret = peel_onion(name, len, sha1);
	if (!ret)
		return 0;

	ret = get_sha1_basic(name, len, sha1);
	if (!ret)
		return 0;

	/* It could be describe output that is "SOMETHING-gXXXX" */
	ret = get_describe_name(name, len, sha1);
	if (!ret)
		return 0;

	return get_short_sha1(name, len, sha1, lookup_flags);
}