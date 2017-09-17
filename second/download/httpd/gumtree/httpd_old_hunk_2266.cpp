    ap_hard_timeout("send directory", r);

    /* Spew HTML preamble */

    title_endp = title_name + strlen(title_name) - 1;

    while (title_endp > title_name && *title_endp == '/')
	*title_endp-- = '\0';

    if ((!(tmp = find_header(autoindex_conf, r)))
	|| (!(insert_readme(name, tmp, title_name, NO_HRULE, FRONT_MATTER, r)))
	) {
	emit_preamble(r, title_name);
	ap_rvputs(r, "<H1>Index of ", title_name, "</H1>\n", NULL);
