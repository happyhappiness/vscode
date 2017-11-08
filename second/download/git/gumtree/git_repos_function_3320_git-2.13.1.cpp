const char *refs_resolve_ref_unsafe(struct ref_store *refs,
				    const char *refname,
				    int resolve_flags,
				    unsigned char *sha1, int *flags)
{
	static struct strbuf sb_refname = STRBUF_INIT;
	int unused_flags;
	int symref_count;

	if (!flags)
		flags = &unused_flags;

	*flags = 0;

	if (check_refname_format(refname, REFNAME_ALLOW_ONELEVEL)) {
		if (!(resolve_flags & RESOLVE_REF_ALLOW_BAD_NAME) ||
		    !refname_is_safe(refname)) {
			errno = EINVAL;
			return NULL;
		}

		/*
		 * dwim_ref() uses REF_ISBROKEN to distinguish between
		 * missing refs and refs that were present but invalid,
		 * to complain about the latter to stderr.
		 *
		 * We don't know whether the ref exists, so don't set
		 * REF_ISBROKEN yet.
		 */
		*flags |= REF_BAD_NAME;
	}

	for (symref_count = 0; symref_count < SYMREF_MAXDEPTH; symref_count++) {
		unsigned int read_flags = 0;

		if (refs_read_raw_ref(refs, refname,
				      sha1, &sb_refname, &read_flags)) {
			*flags |= read_flags;
			if (errno != ENOENT || (resolve_flags & RESOLVE_REF_READING))
				return NULL;
			hashclr(sha1);
			if (*flags & REF_BAD_NAME)
				*flags |= REF_ISBROKEN;
			return refname;
		}

		*flags |= read_flags;

		if (!(read_flags & REF_ISSYMREF)) {
			if (*flags & REF_BAD_NAME) {
				hashclr(sha1);
				*flags |= REF_ISBROKEN;
			}
			return refname;
		}

		refname = sb_refname.buf;
		if (resolve_flags & RESOLVE_REF_NO_RECURSE) {
			hashclr(sha1);
			return refname;
		}
		if (check_refname_format(refname, REFNAME_ALLOW_ONELEVEL)) {
			if (!(resolve_flags & RESOLVE_REF_ALLOW_BAD_NAME) ||
			    !refname_is_safe(refname)) {
				errno = EINVAL;
				return NULL;
			}

			*flags |= REF_ISBROKEN | REF_BAD_NAME;
		}
	}

	errno = ELOOP;
	return NULL;
}