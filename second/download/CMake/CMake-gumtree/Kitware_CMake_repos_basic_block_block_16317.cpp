{
		l = get_path_component(name, sizeof(name), fn);
		if (l == 0)
			break;
		fn += l;
		if (fn[0] == '/')
			fn++;

		np = isoent_find_child(isoent, name);
		if (np == NULL)
			break;
		if (fn[0] == '\0')
			break;/* We found out the entry */

		/* Try sub directory. */
		isoent = np;
		np = NULL;
		if (!isoent->dir)
			break;/* Not directory */
	}