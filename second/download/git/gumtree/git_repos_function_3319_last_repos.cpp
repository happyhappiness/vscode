static void copy_le16_clamp(unsigned char *dest, uint64_t n, int *clamped)
{
	copy_le16(dest, clamp_max(n, 0xffff, clamped));
}