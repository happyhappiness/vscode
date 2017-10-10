		}
		if (read_ref(ref, sha1)) {
			error(_("tag '%s' not found."), *p);
			had_error = 1;
			continue;
		}
		if (fn(*p, ref, sha1))
			had_error = 1;
	}
	return had_error;
}

static int delete_tag(const char *name, const char *ref,
				const unsigned char *sha1)
{
	if (delete_ref(ref, sha1, 0))
		return 1;
	printf(_("Deleted tag '%s' (was %s)\n"), name, find_unique_abbrev(sha1, DEFAULT_ABBREV));
	return 0;
}

static int verify_tag(const char *name, const char *ref,
				const unsigned char *sha1)
{
	return gpg_verify_tag(sha1, name, GPG_VERIFY_VERBOSE);
}

static int do_sign(struct strbuf *buffer)
{
	return sign_buffer(buffer, buffer, get_signing_key());
}
