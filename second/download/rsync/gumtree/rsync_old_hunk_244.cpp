  if (!d) {
    fprintf(FERROR,"%s: %s\n",
	    dir,strerror(errno));
    return;
  }

  strcpy(fname,dir);
  l = strlen(fname);
  if (fname[l-1] != '/')
    strcat(fname,"/");
  p = fname + strlen(fname);

  if (cvs_exclude) {
    strcpy(p,".cvsignore");
    local_exclude_list = make_exclude_list(fname,NULL,0);
  }  

  for (di=readdir(d); di; di=readdir(d)) {
    if (strcmp(di->d_name,".")==0 ||
	strcmp(di->d_name,"..")==0)
      continue;
    strcpy(p,di->d_name);
    send_file_name(f,flist,fname);
  }

  closedir(d);
}

