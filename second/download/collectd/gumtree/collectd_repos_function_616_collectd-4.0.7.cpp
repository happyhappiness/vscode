static uint16_t ping_icmp4_checksum (char *buf, size_t len)
{
	uint32_t sum = 0;
	uint16_t ret = 0;

	uint16_t *ptr;

	for (ptr = (uint16_t *) buf; len > 1; ptr++, len -= 2)
		sum += *ptr;

	if (len == 1)
	{
		*(char *) &ret = *(char *) ptr;
		sum += ret;
	}

	/* Do this twice to get all possible carries.. */
	sum = (sum >> 16) + (sum & 0xFFFF);
	sum = (sum >> 16) + (sum & 0xFFFF);

	ret = ~sum;

	return (ret);
}