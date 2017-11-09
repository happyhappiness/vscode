static void copy_le64(unsigned char *dest, uint64_t n)
{
	dest[0] = 0xff & n;
	dest[1] = 0xff & (n >> 010);
	dest[2] = 0xff & (n >> 020);
	dest[3] = 0xff & (n >> 030);
	dest[4] = 0xff & (n >> 040);
	dest[5] = 0xff & (n >> 050);
	dest[6] = 0xff & (n >> 060);
	dest[7] = 0xff & (n >> 070);
}