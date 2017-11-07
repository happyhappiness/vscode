static char *ref_msg(const char *line, const char *endp)
{
	const char *ep;
	line += 82;
	ep = memchr(line, '\n', endp - line);
	if (!ep)
		ep = endp;
	return xmemdupz(line, ep - line);
}