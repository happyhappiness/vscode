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
			hard_link_one(i);
		}	
	}
#endif
}