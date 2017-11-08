static void indent(int in)
{
	while (in-- > 0)
		fputc(' ', stderr);
}