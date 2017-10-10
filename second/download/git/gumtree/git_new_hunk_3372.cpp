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
