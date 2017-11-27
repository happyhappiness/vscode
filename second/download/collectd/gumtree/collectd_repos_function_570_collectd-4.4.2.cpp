static unsigned char
fromhex(char c)
{
	if(isdigit((int)c)) {
		return (c - '0');
	} else if(islower((int)c)) {
		return (c - 'a' + 10);
	} else {
		return (c - 'A' + 10);
	}
}