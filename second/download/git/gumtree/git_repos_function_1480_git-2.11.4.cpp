const char *diff_aligned_abbrev(const struct object_id *oid, int len)
{
	int abblen;
	const char *abbrev;

	if (len == GIT_SHA1_HEXSZ)
		return oid_to_hex(oid);

	abbrev = diff_abbrev_oid(oid, len);
	abblen = strlen(abbrev);

	/*
	 * In well-behaved cases, where the abbbreviated result is the
	 * same as the requested length, append three dots after the
	 * abbreviation (hence the whole logic is limited to the case
	 * where abblen < 37); when the actual abbreviated result is a
	 * bit longer than the requested length, we reduce the number
	 * of dots so that they match the well-behaved ones.  However,
	 * if the actual abbreviation is longer than the requested
	 * length by more than three, we give up on aligning, and add
	 * three dots anyway, to indicate that the output is not the
	 * full object name.  Yes, this may be suboptimal, but this
	 * appears only in "diff --raw --abbrev" output and it is not
	 * worth the effort to change it now.  Note that this would
	 * likely to work fine when the automatic sizing of default
	 * abbreviation length is used--we would be fed -1 in "len" in
	 * that case, and will end up always appending three-dots, but
	 * the automatic sizing is supposed to give abblen that ensures
	 * uniqueness across all objects (statistically speaking).
	 */
	if (abblen < GIT_SHA1_HEXSZ - 3) {
		static char hex[GIT_SHA1_HEXSZ + 1];
		if (len < abblen && abblen <= len + 2)
			xsnprintf(hex, sizeof(hex), "%s%.*s", abbrev, len+3-abblen, "..");
		else
			xsnprintf(hex, sizeof(hex), "%s...", abbrev);
		return hex;
	}

	return oid_to_hex(oid);
}