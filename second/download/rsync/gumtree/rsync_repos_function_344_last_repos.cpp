static inline int64
IVAL64(const char *buf, int pos)
{
	union {
		const char *b;
		const int64 *num;
	} u;
	u.b = buf + pos;
	return *u.num;
}