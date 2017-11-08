static int get_sha1_basic(const char *str, int len, unsigned char *sha1,
			  unsigned int flags)
{
	static const char *warn_msg = "refname '%.*s' is ambiguous.";
	static const char *object_name_msg = N_(
	"Git normally never creates a ref that ends with 40 hex characters\n"
	"because it will be ignored when you just specify 40-hex. These refs\n"
	"may be created by mistake. For example,\n"
	"\n"
	"  git checkout -b $br $(git rev-parse ...)\n"
	"\n"
	"where \"$br\" is somehow empty and a 40-hex ref is created. Please\n"
	"examine these refs and maybe delete them. Turn this message off by\n"
	"running \"git config advice.objectNameWarning false\"");
	unsigned char tmp_sha1[20];
	char *real_ref = NULL;
	int refs_found = 0;
	int at, reflog_len, nth_prior = 0;

	if (len == 40 && !get_sha1_hex(str, sha1)) {
		if (warn_ambiguous_refs && warn_on_object_refname_ambiguity) {
			refs_found = dwim_ref(str, len, tmp_sha1, &real_ref);
			if (refs_found > 0) {
				warning(warn_msg, len, str);
				if (advice_object_name_warning)
					fprintf(stderr, "%s\n", _(object_name_msg));
			}
			free(real_ref);
		}
		return 0;
	}

	/* basic@{time or number or -number} format to query ref-log */
	reflog_len = at = 0;
	if (len && str[len-1] == '}') {
		for (at = len-4; at >= 0; at--) {
			if (str[at] == '@' && str[at+1] == '{') {
				if (str[at+2] == '-') {
					if (at != 0)
						/* @{-N} not at start */
						return -1;
					nth_prior = 1;
					continue;
				}
				if (!upstream_mark(str + at, len - at) &&
				    !push_mark(str + at, len - at)) {
					reflog_len = (len-1) - (at+2);
					len = at;
				}
				break;
			}
		}
	}

	/* Accept only unambiguous ref paths. */
	if (len && ambiguous_path(str, len))
		return -1;

	if (nth_prior) {
		struct strbuf buf = STRBUF_INIT;
		int detached;

		if (interpret_nth_prior_checkout(str, len, &buf) > 0) {
			detached = (buf.len == 40 && !get_sha1_hex(buf.buf, sha1));
			strbuf_release(&buf);
			if (detached)
				return 0;
		}
	}

	if (!len && reflog_len)
		/* allow "@{...}" to mean the current branch reflog */
		refs_found = dwim_ref("HEAD", 4, sha1, &real_ref);
	else if (reflog_len)
		refs_found = dwim_log(str, len, sha1, &real_ref);
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
		unsigned long at_time;
		unsigned long co_time;
		int co_tz, co_cnt;

		/* Is it asking for N-th entry, or approxidate? */
		for (i = nth = 0; 0 <= nth && i < reflog_len; i++) {
			char ch = str[at+2+i];
			if ('0' <= ch && ch <= '9')
				nth = nth * 10 + ch - '0';
			else
				nth = -1;
		}
		if (100000000 <= nth) {
			at_time = nth;
			nth = -1;
		} else if (0 <= nth)
			at_time = 0;
		else {
			int errors = 0;
			char *tmp = xstrndup(str + at + 2, reflog_len);
			at_time = approxidate_careful(tmp, &errors);
			free(tmp);
			if (errors) {
				free(real_ref);
				return -1;
			}
		}
		if (read_ref_at(real_ref, flags, at_time, nth, sha1, NULL,
				&co_time, &co_tz, &co_cnt)) {
			if (!len) {
				if (starts_with(real_ref, "refs/heads/")) {
					str = real_ref + 11;
					len = strlen(real_ref + 11);
				} else {
					/* detached HEAD */
					str = "HEAD";
					len = 4;
				}
			}
			if (at_time) {
				if (!(flags & GET_SHA1_QUIETLY)) {
					warning("Log for '%.*s' only goes "
						"back to %s.", len, str,
						show_date(co_time, co_tz, DATE_RFC2822));
				}
			} else {
				if (flags & GET_SHA1_QUIETLY) {
					exit(128);
				}
				die("Log for '%.*s' only has %d entries.",
				    len, str, co_cnt);
			}
		}
	}

	free(real_ref);
	return 0;
}