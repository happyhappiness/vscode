void
txt2c(char *sym, FILE *fp)
{
	unsigned char buf[per_line];
	int i;
	int sz = 0;

	printf("unsigned char %s[] = {\n", sym);
	while (1) {
		sz = fread(buf, sizeof(unsigned char), per_line, fp);
		if (sz == 0)
			break;
		printf("\t");
		for (i = 0; i < sz; i++)
			printf("0x%02x, ", buf[i]);
		printf("\n");
	}

	printf("\t0x00\n};\n");
}