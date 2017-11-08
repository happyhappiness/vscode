void show_flist(int index, struct file_struct **fptr)
{
	/*  for debugging    show_flist(flist->count, flist->files * */

	int i;
	for (i = 0; i < index; i++) {
		rprintf(FINFO, "flist->flags=%#x\n", fptr[i]->flags);
		rprintf(FINFO, "flist->modtime=%#lx\n",
			(long unsigned) fptr[i]->modtime);
		rprintf(FINFO, "flist->length=%.0f\n",
			(double) fptr[i]->length);
		rprintf(FINFO, "flist->mode=%#o\n", (int) fptr[i]->mode);
		rprintf(FINFO, "flist->basename=%s\n",
			safe_fname(fptr[i]->basename));
		if (fptr[i]->dirname) {
			rprintf(FINFO, "flist->dirname=%s\n",
				safe_fname(fptr[i]->dirname));
		}
		if (am_sender && fptr[i]->dir.root) {
			rprintf(FINFO, "flist->dir.root=%s\n",
				safe_fname(fptr[i]->dir.root));
		}
	}
}