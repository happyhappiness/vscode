#endif

  return 0;
}


/* create any hard links in the flist */
void do_hard_links(struct file_list *flist)
{
#if SUPPORT_HARD_LINKS
  int i;
  
  if (!hlink_list) return;

  for (i=1;i<hlink_count;i++) {
    if (S_ISREG(hlink_list[i].mode) &&
	S_ISREG(hlink_list[i-1].mode) &&
	hlink_list[i].basename && hlink_list[i-1].basename &&
	hlink_list[i].dev == hlink_list[i-1].dev &&
	hlink_list[i].inode == hlink_list[i-1].inode) {
      struct stat st1,st2;

      if (link_stat(f_name(&hlink_list[i-1]),&st1) != 0) continue;
      if (link_stat(f_name(&hlink_list[i]),&st2) != 0) {
	if (do_link(f_name(&hlink_list[i-1]),f_name(&hlink_list[i])) != 0) {
		if (verbose > 0)
			fprintf(FINFO,"link %s => %s : %s\n",
				f_name(&hlink_list[i]),
				f_name(&hlink_list[i-1]),strerror(errno));
	  continue;
	}
      } else {
	if (st2.st_dev == st1.st_dev && st2.st_ino == st1.st_ino) continue;
	
	if (do_unlink(f_name(&hlink_list[i])) != 0 ||
	    do_link(f_name(&hlink_list[i-1]),f_name(&hlink_list[i])) != 0) {
		if (verbose > 0)
			fprintf(FINFO,"link %s => %s : %s\n",
				f_name(&hlink_list[i]),
				f_name(&hlink_list[i-1]),strerror(errno));
	  continue;
	}
      }
      if (verbose > 0)
	      fprintf(FINFO,"%s => %s\n",
		      f_name(&hlink_list[i]),f_name(&hlink_list[i-1]));
    }	
  }
#endif
}
