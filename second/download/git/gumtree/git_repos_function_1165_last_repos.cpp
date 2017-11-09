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
		in_encoding = fallback_encoding(in_encoding);
		out_encoding = fallback_encoding(out_encoding);

		conv = iconv_open(out_encoding, in_encoding);
		if (conv == (iconv_t) -1)
			return NULL;
	}

	out = reencode_string_iconv(in, insz, conv, outsz);
	iconv_close(conv);
	return out;
}