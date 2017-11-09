static uint32_t take2(const unsigned char *sha1)
{
	return ((sha1[0] << 8) | sha1[1]);
}