static inline int64
read_varlong30(int f, uchar min_bytes)
{
	if (protocol_version < 30)
		return read_longint(f);
	return read_varlong(f, min_bytes);
}