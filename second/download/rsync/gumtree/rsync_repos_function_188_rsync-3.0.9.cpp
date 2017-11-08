static inline void
write_varint30(int f, int32 x)
{
	if (protocol_version < 30)
		write_int(f, x);
	else
		write_varint(f, x);
}