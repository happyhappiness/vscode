static void print_signature(void)
{
	if (!signature || !*signature)
		return;

	printf("-- \n%s", signature);
	if (signature[strlen(signature)-1] != '\n')
		putchar('\n');
	putchar('\n');
}