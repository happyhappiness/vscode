static inline void sha1write_u8(struct sha1file *f, uint8_t data)
{
	sha1write(f, &data, sizeof(data));
}