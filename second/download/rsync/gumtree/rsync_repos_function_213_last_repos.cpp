static inline int32
read_varint30(int f)
{
	if (protocol_version < 30)
		return read_int(f);
	return read_varint(f);
}