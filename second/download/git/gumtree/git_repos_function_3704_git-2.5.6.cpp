static int crud(unsigned char c)
{
	return  c <= 32  ||
		c == '.' ||
		c == ',' ||
		c == ':' ||
		c == ';' ||
		c == '<' ||
		c == '>' ||
		c == '"' ||
		c == '\\' ||
		c == '\'';
}