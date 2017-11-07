int decimal_width(int number)
{
	int i, width;

	for (width = 1, i = 10; i <= number; width++)
		i *= 10;
	return width;
}