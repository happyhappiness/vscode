static int flist_up(struct file_list *flist, int i)
{
	while (!flist->files[i].name) i++;
	return i;
}