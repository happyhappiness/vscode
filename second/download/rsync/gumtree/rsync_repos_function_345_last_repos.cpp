static inline void
SIVAL64(char *buf, int pos, int64 val)
{
	union {
		char *b;
		int64 *num;
	} u;
	u.b = buf + pos;
	*u.num = val;
}