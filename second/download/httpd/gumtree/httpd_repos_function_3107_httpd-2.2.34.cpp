char *_crypt_blowfish_rn(const char *key, const char *setting,
	char *output, int size)
{
	const char *test_key = "8b \xd0\xc1\xd2\xcf\xcc\xd8";
	const char *test_setting = "$2a$00$abcdefghijklmnopqrstuu";
	static const char * const test_hash[2] =
		{"VUrPmXD6q/nVSSp7pNDhCR9071IfIRe\0\x55", /* $2x$ */
		"i1D709vfamulimlGcq0qq3UvuUasvEa\0\x55"}; /* $2a$, $2y$ */
	char *retval;
	const char *p;
	int save_errno, ok;
	struct {
		char s[7 + 22 + 1];
		char o[7 + 22 + 31 + 1 + 1 + 1];
	} buf;

/* Hash the supplied password */
	_crypt_output_magic(setting, output, size);
	retval = BF_crypt(key, setting, output, size, 16);
	save_errno = errno;

/*
 * Do a quick self-test.  It is important that we make both calls to BF_crypt()
 * from the same scope such that they likely use the same stack locations,
 * which makes the second call overwrite the first call's sensitive data on the
 * stack and makes it more likely that any alignment related issues would be
 * detected by the self-test.
 */
	memcpy(buf.s, test_setting, sizeof(buf.s));
	if (retval)
		buf.s[2] = setting[2];
	memset(buf.o, 0x55, sizeof(buf.o));
	buf.o[sizeof(buf.o) - 1] = 0;
	p = BF_crypt(test_key, buf.s, buf.o, sizeof(buf.o) - (1 + 1), 1);

	ok = (p == buf.o &&
	    !memcmp(p, buf.s, 7 + 22) &&
	    !memcmp(p + (7 + 22),
	    test_hash[(unsigned int)(unsigned char)buf.s[2] & 1],
	    31 + 1 + 1 + 1));

	{
		const char *k = "\xff\xa3" "34" "\xff\xff\xff\xa3" "345";
		BF_key ae, ai, ye, yi;
		BF_set_key(k, ae, ai, 2); /* $2a$ */
		BF_set_key(k, ye, yi, 4); /* $2y$ */
		ai[0] ^= 0x10000; /* undo the safety (for comparison) */
		ok = ok && ai[0] == 0xdb9c59bc && ye[17] == 0x33343500 &&
		    !memcmp(ae, ye, sizeof(ae)) &&
		    !memcmp(ai, yi, sizeof(ai));
	}

	__set_errno(save_errno);
	if (ok)
		return retval;

/* Should not happen */
	_crypt_output_magic(setting, output, size);
	__set_errno(EINVAL); /* pretend we don't support this hash type */
	return NULL;
}