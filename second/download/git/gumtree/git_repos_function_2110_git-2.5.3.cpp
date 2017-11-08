static inline int need_bs_quote(char c)
{
	return (c == '\'' || c == '!');
}