char *url_normalize(const char *url, struct url_info *out_info)
{
	/*
	 * Normalize NUL-terminated url using the following rules:
	 *
	 * 1. Case-insensitive parts of url will be converted to lower case
	 * 2. %-encoded characters that do not need to be will be unencoded
	 * 3. Characters that are not %-encoded and must be will be encoded
	 * 4. All %-encodings will be converted to upper case hexadecimal
	 * 5. Leading 0s are removed from port numbers
	 * 6. If the default port for the scheme is given it will be removed
	 * 7. A path part (including empty) not starting with '/' has one added
	 * 8. Any dot segments (. or ..) in the path are resolved and removed
	 * 9. IPv6 host literals are allowed (but not normalized or validated)
	 *
	 * The rules are based on information in RFC 3986.
	 *
	 * Please note this function requires a full URL including a scheme
	 * and host part (except for file: URLs which may have an empty host).
	 *
	 * The return value is a newly allocated string that must be freed
	 * or NULL if the url is not valid.
	 *
	 * If out_info is non-NULL, the url and err fields therein will always
	 * be set.  If a non-NULL value is returned, it will be stored in
	 * out_info->url as well, out_info->err will be set to NULL and the
	 * other fields of *out_info will also be filled in.  If a NULL value
	 * is returned, NULL will be stored in out_info->url and out_info->err
	 * will be set to a brief, translated, error message, but no other
	 * fields will be filled in.
	 *
	 * This is NOT a URL validation function.  Full URL validation is NOT
	 * performed.  Some invalid host names are passed through this function
	 * undetected.  However, most all other problems that make a URL invalid
	 * will be detected (including a missing host for non file: URLs).
	 */

	size_t url_len = strlen(url);
	struct strbuf norm;
	size_t spanned;
	size_t scheme_len, user_off=0, user_len=0, passwd_off=0, passwd_len=0;
	size_t host_off=0, host_len=0, port_len=0, path_off, path_len, result_len;
	const char *slash_ptr, *at_ptr, *colon_ptr, *path_start;
	char *result;

	/*
	 * Copy lowercased scheme and :// suffix, %-escapes are not allowed
	 * First character of scheme must be URL_ALPHA
	 */
	spanned = strspn(url, URL_SCHEME_CHARS);
	if (!spanned || !isalpha(url[0]) || spanned + 3 > url_len ||
	    url[spanned] != ':' || url[spanned+1] != '/' || url[spanned+2] != '/') {
		if (out_info) {
			out_info->url = NULL;
			out_info->err = _("invalid URL scheme name or missing '://' suffix");
		}
		return NULL; /* Bad scheme and/or missing "://" part */
	}
	strbuf_init(&norm, url_len);
	scheme_len = spanned;
	spanned += 3;
	url_len -= spanned;
	while (spanned--)
		strbuf_addch(&norm, tolower(*url++));


	/*
	 * Copy any username:password if present normalizing %-escapes
	 */
	at_ptr = strchr(url, '@');
	slash_ptr = url + strcspn(url, "/?#");
	if (at_ptr && at_ptr < slash_ptr) {
		user_off = norm.len;
		if (at_ptr > url) {
			if (!append_normalized_escapes(&norm, url, at_ptr - url,
						       "", URL_RESERVED)) {
				if (out_info) {
					out_info->url = NULL;
					out_info->err = _("invalid %XX escape sequence");
				}
				strbuf_release(&norm);
				return NULL;
			}
			colon_ptr = strchr(norm.buf + scheme_len + 3, ':');
			if (colon_ptr) {
				passwd_off = (colon_ptr + 1) - norm.buf;
				passwd_len = norm.len - passwd_off;
				user_len = (passwd_off - 1) - (scheme_len + 3);
			} else {
				user_len = norm.len - (scheme_len + 3);
			}
		}
		strbuf_addch(&norm, '@');
		url_len -= (++at_ptr - url);
		url = at_ptr;
	}


	/*
	 * Copy the host part excluding any port part, no %-escapes allowed
	 */
	if (!url_len || strchr(":/?#", *url)) {
		/* Missing host invalid for all URL schemes except file */
		if (strncmp(norm.buf, "file:", 5)) {
			if (out_info) {
				out_info->url = NULL;
				out_info->err = _("missing host and scheme is not 'file:'");
			}
			strbuf_release(&norm);
			return NULL;
		}
	} else {
		host_off = norm.len;
	}
	colon_ptr = slash_ptr - 1;
	while (colon_ptr > url && *colon_ptr != ':' && *colon_ptr != ']')
		colon_ptr--;
	if (*colon_ptr != ':') {
		colon_ptr = slash_ptr;
	} else if (!host_off && colon_ptr < slash_ptr && colon_ptr + 1 != slash_ptr) {
		/* file: URLs may not have a port number */
		if (out_info) {
			out_info->url = NULL;
			out_info->err = _("a 'file:' URL may not have a port number");
		}
		strbuf_release(&norm);
		return NULL;
	}
	spanned = strspn(url, URL_HOST_CHARS);
	if (spanned < colon_ptr - url) {
		/* Host name has invalid characters */
		if (out_info) {
			out_info->url = NULL;
			out_info->err = _("invalid characters in host name");
		}
		strbuf_release(&norm);
		return NULL;
	}
	while (url < colon_ptr) {
		strbuf_addch(&norm, tolower(*url++));
		url_len--;
	}


	/*
	 * Check the port part and copy if not the default (after removing any
	 * leading 0s); no %-escapes allowed
	 */
	if (colon_ptr < slash_ptr) {
		/* skip the ':' and leading 0s but not the last one if all 0s */
		url++;
		url += strspn(url, "0");
		if (url == slash_ptr && url[-1] == '0')
			url--;
		if (url == slash_ptr) {
			/* Skip ":" port with no number, it's same as default */
		} else if (slash_ptr - url == 2 &&
			   !strncmp(norm.buf, "http:", 5) &&
			   !strncmp(url, "80", 2)) {
			/* Skip http :80 as it's the default */
		} else if (slash_ptr - url == 3 &&
			   !strncmp(norm.buf, "https:", 6) &&
			   !strncmp(url, "443", 3)) {
			/* Skip https :443 as it's the default */
		} else {
			/*
			 * Port number must be all digits with leading 0s removed
			 * and since all the protocols we deal with have a 16-bit
			 * port number it must also be in the range 1..65535
			 * 0 is not allowed because that means "next available"
			 * on just about every system and therefore cannot be used
			 */
			unsigned long pnum = 0;
			spanned = strspn(url, URL_DIGIT);
			if (spanned < slash_ptr - url) {
				/* port number has invalid characters */
				if (out_info) {
					out_info->url = NULL;
					out_info->err = _("invalid port number");
				}
				strbuf_release(&norm);
				return NULL;
			}
			if (slash_ptr - url <= 5)
				pnum = strtoul(url, NULL, 10);
			if (pnum == 0 || pnum > 65535) {
				/* port number not in range 1..65535 */
				if (out_info) {
					out_info->url = NULL;
					out_info->err = _("invalid port number");
				}
				strbuf_release(&norm);
				return NULL;
			}
			strbuf_addch(&norm, ':');
			strbuf_add(&norm, url, slash_ptr - url);
			port_len = slash_ptr - url;
		}
		url_len -= slash_ptr - colon_ptr;
		url = slash_ptr;
	}
	if (host_off)
		host_len = norm.len - host_off;


	/*
	 * Now copy the path resolving any . and .. segments being careful not
	 * to corrupt the URL by unescaping any delimiters, but do add an
	 * initial '/' if it's missing and do normalize any %-escape sequences.
	 */
	path_off = norm.len;
	path_start = norm.buf + path_off;
	strbuf_addch(&norm, '/');
	if (*url == '/') {
		url++;
		url_len--;
	}
	for (;;) {
		const char *seg_start;
		size_t seg_start_off = norm.len;
		const char *next_slash = url + strcspn(url, "/?#");
		int skip_add_slash = 0;

		/*
		 * RFC 3689 indicates that any . or .. segments should be
		 * unescaped before being checked for.
		 */
		if (!append_normalized_escapes(&norm, url, next_slash - url, "",
					       URL_RESERVED)) {
			if (out_info) {
				out_info->url = NULL;
				out_info->err = _("invalid %XX escape sequence");
			}
			strbuf_release(&norm);
			return NULL;
		}

		seg_start = norm.buf + seg_start_off;
		if (!strcmp(seg_start, ".")) {
			/* ignore a . segment; be careful not to remove initial '/' */
			if (seg_start == path_start + 1) {
				strbuf_setlen(&norm, norm.len - 1);
				skip_add_slash = 1;
			} else {
				strbuf_setlen(&norm, norm.len - 2);
			}
		} else if (!strcmp(seg_start, "..")) {
			/*
			 * ignore a .. segment and remove the previous segment;
			 * be careful not to remove initial '/' from path
			 */
			const char *prev_slash = norm.buf + norm.len - 3;
			if (prev_slash == path_start) {
				/* invalid .. because no previous segment to remove */
				if (out_info) {
					out_info->url = NULL;
					out_info->err = _("invalid '..' path segment");
				}
				strbuf_release(&norm);
				return NULL;
			}
			while (*--prev_slash != '/') {}
			if (prev_slash == path_start) {
				strbuf_setlen(&norm, prev_slash - norm.buf + 1);
				skip_add_slash = 1;
			} else {
				strbuf_setlen(&norm, prev_slash - norm.buf);
			}
		}
		url_len -= next_slash - url;
		url = next_slash;
		/* if the next char is not '/' done with the path */
		if (*url != '/')
			break;
		url++;
		url_len--;
		if (!skip_add_slash)
			strbuf_addch(&norm, '/');
	}
	path_len = norm.len - path_off;


	/*
	 * Now simply copy the rest, if any, only normalizing %-escapes and
	 * being careful not to corrupt the URL by unescaping any delimiters.
	 */
	if (*url) {
		if (!append_normalized_escapes(&norm, url, url_len, "", URL_RESERVED)) {
			if (out_info) {
				out_info->url = NULL;
				out_info->err = _("invalid %XX escape sequence");
			}
			strbuf_release(&norm);
			return NULL;
		}
	}


	result = strbuf_detach(&norm, &result_len);
	if (out_info) {
		out_info->url = result;
		out_info->err = NULL;
		out_info->url_len = result_len;
		out_info->scheme_len = scheme_len;
		out_info->user_off = user_off;
		out_info->user_len = user_len;
		out_info->passwd_off = passwd_off;
		out_info->passwd_len = passwd_len;
		out_info->host_off = host_off;
		out_info->host_len = host_len;
		out_info->port_len = port_len;
		out_info->path_off = path_off;
		out_info->path_len = path_len;
	}
	return result;
}