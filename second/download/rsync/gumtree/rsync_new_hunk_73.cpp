  if (!name) 
    return NULL;

  if (mkdir(name,0777) != 0) {
    fprintf(stderr,"mkdir %s : %s\n",name,strerror(errno));
    exit(1);
  } else {
    fprintf(am_server?stderr:stdout,"created directory %s\n",name);
  }

  if (chdir(name) != 0) {
    fprintf(stderr,"chdir %s : %s\n",name,strerror(errno));
    exit(1);
  }
