
	lst = preq->lst;
	while (*lst != p)
		lst = &((*lst)->next);
	*lst = (*lst)->next;

	tmp_idx = xstrdup(preq->tmpfile);
	strcpy(tmp_idx + strlen(tmp_idx) - strlen(".pack.temp"),
	       ".idx.temp");

	ip_argv[0] = "index-pack";
	ip_argv[1] = "-o";
	ip_argv[2] = tmp_idx;
	ip_argv[3] = preq->tmpfile;
	ip_argv[4] = NULL;
