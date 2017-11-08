static char *end_of_line(char *cp, unsigned long *left)
{
	unsigned long l = *left;
	while (l && *cp != '\n') {
		l--;
		cp++;
	}
	*left = l;
	return cp;
}