	  if (strcmp(flist->files[j].name,".")==0) continue;
	  if (last_name &&
	      flist->files[j].name[strlen(last_name)] == '/' &&
	      strncmp(flist->files[j].name,last_name, strlen(last_name))==0)
		  continue;
	  last_name = flist->files[j].name;
	  if (verbose > 1)
		  fprintf(FINFO,"deleting in %s\n", last_name);
	  if (!(local_file_list = send_file_list(-1,1,&last_name)))
		  return;

	  for (i=local_file_list->count-1;i>=0;i--) {
		  if (!local_file_list->files[i].name) continue;
		  if (-1 == flist_find(flist,&local_file_list->files[i])) {
			  delete_one(&local_file_list->files[i]);
		  }    
