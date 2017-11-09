static int linelen(const char *msg)
{
	return strchrnul(msg, '\n') - msg;
}