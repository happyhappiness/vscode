static const char *copy_line(const char *buf)
{
	const char *eol = strchrnul(buf, '\n');
	return xmemdupz(buf, eol - buf);
}