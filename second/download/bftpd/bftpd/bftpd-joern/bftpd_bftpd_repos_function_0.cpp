void print_file(int number, char *filename)
{
	FILE *phile;
	char foo[MAX_STRING_LENGTH];
	phile = fopen(filename, "r");
	if (phile) {
		while (fgets(foo, MAX_STRING_LENGTH, phile)) {
			foo[strlen(foo) - 1] = '\0';
			control_printf(SL_SUCCESS, "%i-%s", number, foo);
		}
		fclose(phile);
	}
}