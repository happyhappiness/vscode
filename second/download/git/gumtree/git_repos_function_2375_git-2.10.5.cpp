static inline int sq_must_quote(char c)
{
	return sq_lookup[(unsigned char)c] + quote_path_fully > 0;
}