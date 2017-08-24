{
	if (s == 0)
		return (v);
	v = format_hex_recursive(v, p+1, s-1);
	*p = "0123456789abcdef"[v & 0xf];
	return (v >> 4);
}