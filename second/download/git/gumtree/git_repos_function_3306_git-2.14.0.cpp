static void copy_le32_clamp(unsigned char *dest, uint64_t n, int *clamped)
{
	copy_le32(dest, clamp_max(n, 0xffffffff, clamped));
}