  if (flist->count == 1)
    return name;

  if (!name) 
    return NULL;

  if (mkdir(name,0777) != 0) {
    fprintf(FERROR,"mkdir %s : %s\n",name,strerror(errno));
    exit_cleanup(1);
  } else {
    fprintf(FINFO,"created directory %s\n",name);
  }

