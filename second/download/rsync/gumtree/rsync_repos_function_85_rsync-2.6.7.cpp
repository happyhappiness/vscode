void decrement_active_files(int ndx)
{
	active_filecnt--;
	active_bytecnt -= the_file_list->files[ndx]->length;
}