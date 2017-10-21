  
  if (!hlink_list) return;

  for (i=1;i<hlink_count;i++) {
    if (S_ISREG(hlink_list[i].mode) &&
	S_ISREG(hlink_list[i-1].mode) &&
	hlink_list[i].name && hlink_list[i-1].name &&
	hlink_list[i].dev == hlink_list[i-1].dev &&
	hlink_list[i].inode == hlink_list[i-1].inode) {
      struct stat st1,st2;

      if (link_stat(hlink_list[i-1].name,&st1) != 0) continue;
      if (link_stat(hlink_list[i].name,&st2) != 0) {
	if (!dry_run && link(hlink_list[i-1].name,hlink_list[i].name) != 0) {
		if (verbose > 0)
			fprintf(FINFO,"link %s => %s : %s\n",
				hlink_list[i].name,
				hlink_list[i-1].name,strerror(errno));
	  continue;
	}
      } else {
	if (st2.st_dev == st1.st_dev && st2.st_ino == st1.st_ino) continue;
	
	if (!dry_run && (unlink(hlink_list[i].name) != 0 ||
			 link(hlink_list[i-1].name,hlink_list[i].name) != 0)) {
		if (verbose > 0)
			fprintf(FINFO,"link %s => %s : %s\n",
				hlink_list[i].name,
				hlink_list[i-1].name,strerror(errno));
	  continue;
	}
      }
      if (verbose > 0)
	      fprintf(FINFO,"%s => %s\n",
		      hlink_list[i].name,hlink_list[i-1].name);
    }	
  }
#endif
}
