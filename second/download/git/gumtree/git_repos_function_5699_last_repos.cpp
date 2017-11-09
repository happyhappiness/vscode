static void print_signature(FILE *file)
{
	if (!signature || !*signature)
		return;

	fprintf(file, "-- \n%s", signature);
	if (signature[strlen(signature)-1] != '\n')
		putc('\n', file);
	putc('\n', file);
}