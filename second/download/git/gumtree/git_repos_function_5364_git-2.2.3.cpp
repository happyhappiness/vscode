void fast_export_delete(const char *path)
{
	putchar('D');
	putchar(' ');
	quote_c_style(path, NULL, stdout, 0);
	putchar('\n');
}