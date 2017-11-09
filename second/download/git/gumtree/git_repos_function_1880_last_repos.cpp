static int write_pack_info_file(FILE *fp)
{
	int i;
	for (i = 0; i < num_pack; i++) {
		if (fprintf(fp, "P %s\n", info[i]->p->pack_name + objdirlen + 6) < 0)
			return -1;
	}
	if (fputc('\n', fp) == EOF)
		return -1;
	return 0;
}