static inline uint32
IVALu(const uchar *buf, int pos)
{
	union {
		const uchar *b;
		const uint32 *num;
	} u;
	u.b = buf + pos;
	return *u.num;
}