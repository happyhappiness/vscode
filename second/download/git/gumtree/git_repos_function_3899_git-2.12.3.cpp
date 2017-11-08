static char hexchar(unsigned int b)
{
	return b < 10 ? '0' + b : 'a' + (b - 10);
}