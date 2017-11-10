static int die_webcgi_recursing(void)
{
	return dead++ > 1;
}