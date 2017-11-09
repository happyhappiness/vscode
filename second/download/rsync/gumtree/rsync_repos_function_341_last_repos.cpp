static inline void
SIVALu(uchar *buf, int pos, uint32 val)
{
	union {
		uchar *b;
		uint32 *num;
	} u;
	u.b = buf + pos;
	*u.num = val;
}