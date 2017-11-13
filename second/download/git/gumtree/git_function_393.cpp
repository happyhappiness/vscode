static int print_alternate(struct alternate_object_database *alt, void *data)
{
	printf("alternate: ");
	quote_c_style(alt->path, NULL, stdout, 0);
	putchar('\n');
	return 0;
}