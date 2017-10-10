	/* renumber them */
	qsort(info, num_pack, sizeof(info[0]), compare_info);
	for (i = 0; i < num_pack; i++)
		info[i]->new_num = i;
}

static void free_pack_info(void)
{
	int i;
	for (i = 0; i < num_pack; i++)
		free(info[i]);
	free(info);
}

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

static int update_info_packs(int force)
{
	char *infofile = mkpathdup("%s/info/packs", get_object_directory());
	int ret;

	init_pack_info(infofile, force);
	ret = update_info_file(infofile, write_pack_info_file);
	free_pack_info();
	free(infofile);
	return ret;
}

/* public */
int update_server_info(int force)
{
	/* We would add more dumb-server support files later,
