static inline void
SIVAL(char *buf, int pos, uint32 val)
{
	SIVALu((uchar*)buf, pos, val);
}