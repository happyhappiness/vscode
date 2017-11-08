char *reencode_string_len(const char *in, int insz,
			  const char *out_encoding, const char *in_encoding,
			  int *outsz)
{
	iconv_t conv;
	char *out;

	if (!in_encoding)
		return NULL;

	conv = iconv_open(out_encoding, in_encoding);
	if (conv == (iconv_t) -1) {
		/*
		 * Some platforms do not have the variously spelled variants of
		 * UTF-8, so let's fall back to trying the most official
		 * spelling. We do so only as a fallback in case the platform
		 * does understand the user's spelling, but not our official
		 * one.
		 */
		if (is_encoding_utf8(in_encoding))
			in_encoding = "UTF-8";
		if (is_encoding_utf8(out_encoding))
			out_encoding = "UTF-8";
		conv = iconv_open(out_encoding, in_encoding);
		if (conv == (iconv_t) -1)
			return NULL;
	}

	out = reencode_string_iconv(in, insz, conv, outsz);
	iconv_close(conv);
	return out;
}