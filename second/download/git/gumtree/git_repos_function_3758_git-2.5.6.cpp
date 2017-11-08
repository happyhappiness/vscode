static inline char *reencode_string(const char *in,
				    const char *out_encoding,
				    const char *in_encoding)
{
	return reencode_string_len(in, strlen(in),
				   out_encoding, in_encoding,
				   NULL);
}