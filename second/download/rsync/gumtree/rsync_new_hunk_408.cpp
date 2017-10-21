}


#if SUPPORT_HARD_LINKS
static void hard_link_one(int i)
{
	STRUCT_STAT st1,st2;

	if (link_stat(f_name(&hlink_list[i-1]),&st1) != 0) return;

	if (link_stat(f_name(&hlink_list[i]),&st2) != 0) {
		if (do_link(f_name(&hlink_list[i-1]),f_name(&hlink_list[i])) != 0) {
			if (verbose > 0)
				rprintf(FINFO,"link %s => %s : %s\n",
					f_name(&hlink_list[i]),
					f_name(&hlink_list[i-1]),strerror(errno));
			return;
		}
	} else {
		if (st2.st_dev == st1.st_dev && st2.st_ino == st1.st_ino) return;
		
		if (do_unlink(f_name(&hlink_list[i])) != 0 ||
		    do_link(f_name(&hlink_list[i-1]),f_name(&hlink_list[i])) != 0) {
			if (verbose > 0)
				rprintf(FINFO,"link %s => %s : %s\n",
					f_name(&hlink_list[i]),
					f_name(&hlink_list[i-1]),strerror(errno));
			return;
		}
	}
	if (verbose > 0)
		rprintf(FINFO,"%s => %s\n",
			f_name(&hlink_list[i]),f_name(&hlink_list[i-1]));
}
#endif

/* create any hard links in the flist */
void do_hard_links(struct file_list *flist)
