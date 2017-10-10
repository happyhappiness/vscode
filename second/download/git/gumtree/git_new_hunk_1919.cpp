	else
		refs_found = dwim_ref(str, len, sha1, &real_ref);

	if (!refs_found)
		return -1;

	if (warn_ambiguous_refs && !(flags & GET_SHA1_QUIETLY) &&
	    (refs_found > 1 ||
	     !get_short_sha1(str, len, tmp_sha1, GET_SHA1_QUIETLY)))
		warning(warn_msg, len, str);

	if (reflog_len) {
		int nth, i;
