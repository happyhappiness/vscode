static inline void sha1write_be32(struct sha1file *f, uint32_t data)
{
	data = htonl(data);
	sha1write(f, &data, sizeof(data));
}