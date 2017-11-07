static unsigned int convert_mode(unsigned int mode)
{
	unsigned int newmode;

	newmode = mode & S_IFMT;
	if (S_ISREG(mode))
		newmode |= (mode & 0100) ? 0755 : 0644;
	return newmode;
}