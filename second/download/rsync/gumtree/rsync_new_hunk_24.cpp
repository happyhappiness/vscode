	fprintf(stderr,"chdir %s : %s\n",name,strerror(errno));
	exit(1);
      }
      return NULL;
    }
    if (flist->count > 1) {
      fprintf(stderr,"ERROR: destination must be a directory when copying more than 1 file\n");
      exit(1);
    }
    return name;
  }

  if (flist->count == 1)
    return name;

  if (!name) 
    return NULL;

  if (mkdir(name,0777) != 0) {
    fprintf(stderr,"mkdir %s : %s\n",name,strerror(errno));
    exit(1);
  }

  if (chdir(name) != 0) {
