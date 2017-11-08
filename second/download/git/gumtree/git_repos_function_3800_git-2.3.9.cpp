static inline unsigned long has_zero(unsigned long a)
{
	return ((a - ONEBYTES) & ~a) & HIGHBITS;
}