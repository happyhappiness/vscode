{
		re->rede_files.first = file->re_next;
		if (re->rede_files.first == NULL)
			re->rede_files.last =
			    &(re->rede_files.first);
	}