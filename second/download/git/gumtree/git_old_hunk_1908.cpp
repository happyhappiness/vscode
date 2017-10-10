	/* renumber them */
	qsort(info, num_pack, sizeof(info[0]), compare_info);
	for (i = 0; i < num_pack; i++)
		info[i]->new_num = i;
}

static void write_pack_info_file(FILE *fp)
{
	int i;
	for (i = 0; i < num_pack; i++)
		fprintf(fp, "P %s\n", info[i]->p->pack_name + objdirlen + 6);
	fputc('\n', fp);
}

static int update_info_packs(int force)
{
	char infofile[PATH_MAX];
	char name[PATH_MAX];
	int namelen;
	FILE *fp;

	namelen = sprintf(infofile, "%s/info/packs", get_object_directory());
	strcpy(name, infofile);
	strcpy(name + namelen, "+");

	init_pack_info(infofile, force);

	safe_create_leading_directories(name);
	fp = fopen(name, "w");
	if (!fp)
		return error("cannot open %s", name);
	write_pack_info_file(fp);
	fclose(fp);
	adjust_shared_perm(name);
	rename(name, infofile);
	return 0;
}

/* public */
int update_server_info(int force)
{
	/* We would add more dumb-server support files later,
