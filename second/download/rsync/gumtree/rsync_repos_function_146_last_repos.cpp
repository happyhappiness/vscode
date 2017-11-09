int get_redo_num(void)
{
	return flist_ndx_pop(&redo_list);
}