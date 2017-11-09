static int include_config(char *include, int manage_globals)
{
    STRUCT_STAT sb;
    char *match = manage_globals ? "*.conf" : "*.inc";
    int ret;

    if (do_stat(include, &sb) < 0) {
	rsyserr(FLOG, errno, "unable to stat config file \"%s\"", include);
	return 0;
    }

    if (S_ISREG(sb.st_mode)) {
	if (manage_globals && the_sfunc)
	    the_sfunc("]push");
	ret = pm_process(include, the_sfunc, the_pfunc);
	if (manage_globals && the_sfunc)
	    the_sfunc("]pop");
    } else if (S_ISDIR(sb.st_mode)) {
	char buf[MAXPATHLEN], **bpp;
	item_list conf_list;
	struct dirent *di;
	size_t j;
	DIR *d;

	if (!(d = opendir(include))) {
	    rsyserr(FLOG, errno, "unable to open config dir \"%s\"", include);
	    return 0;
	}

	memset(&conf_list, 0, sizeof conf_list);

	while ((di = readdir(d)) != NULL) {
	    char *dname = d_name(di);
	    if (!wildmatch(match, dname))
		continue;
	    bpp = EXPAND_ITEM_LIST(&conf_list, char *, 32);
	    pathjoin(buf, sizeof buf, include, dname);
	    *bpp = strdup(buf);
	}
	closedir(d);

	if (!(bpp = conf_list.items))
	    return 1;

	if (conf_list.count > 1)
	    qsort(bpp, conf_list.count, sizeof (char *), name_cmp);

	for (j = 0, ret = 1; j < conf_list.count; j++) {
	    if (manage_globals && the_sfunc)
		the_sfunc(j == 0 ? "]push" : "]reset");
	    if ((ret = pm_process(bpp[j], the_sfunc, the_pfunc)) != 1)
		break;
	}

	if (manage_globals && the_sfunc)
	    the_sfunc("]pop");

	for (j = 0; j < conf_list.count; j++)
	    free(bpp[j]);
	free(bpp);
    } else
	ret = 0;

    return ret;
}