static inline void
write_varlong30(int f, int64 x, uchar min_bytes)
{
	if (protocol_version < 30)
		write_longint(f, x);
	else
		write_varlong(f, x, min_bytes);
}