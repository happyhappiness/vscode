	S_ISREG(hlink_list[i-1].mode) &&
	hlink_list[i].name && hlink_list[i-1].name &&
	hlink_list[i].dev == hlink_list[i-1].dev &&
	hlink_list[i].inode == hlink_list[i-1].inode) {
      struct stat st1,st2;

      if (stat(hlink_list[i-1].name,&st1) != 0) continue;
      if (stat(hlink_list[i].name,&st2) != 0) {
	if (!dry_run && link(hlink_list[i-1].name,hlink_list[i].name) != 0) {
	  fprintf(FINFO,"link %s => %s : %s\n",
		  hlink_list[i].name,hlink_list[i-1].name,strerror(errno));
	  continue;
	}
      } else {
