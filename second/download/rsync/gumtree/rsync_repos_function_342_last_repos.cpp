static inline uint32
IVAL(const char *buf, int pos)
{
	return IVALu((uchar*)buf, pos);
}