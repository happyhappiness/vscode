{
	if (s == 0)
		return (v);
	v = format_octal_recursive(v, p+1, s-1);
	*p = '0' + ((char)v & 7);
	return (v >> 3);
}