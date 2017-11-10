int xdl_merge(mmfile_t *orig, mmfile_t *mf1, mmfile_t *mf2,
		xmparam_t const *xmp, mmbuffer_t *result)
{
	xdchange_t *xscr1, *xscr2;
	xdfenv_t xe1, xe2;
	int status;
	xpparam_t const *xpp = &xmp->xpp;

	result->ptr = NULL;
	result->size = 0;

	if (xdl_do_diff(orig, mf1, xpp, &xe1) < 0) {
		return -1;
	}
	if (xdl_do_diff(orig, mf2, xpp, &xe2) < 0) {
		xdl_free_env(&xe1);
		return -1;
	}
	if (xdl_change_compact(&xe1.xdf1, &xe1.xdf2, xpp->flags) < 0 ||
	    xdl_change_compact(&xe1.xdf2, &xe1.xdf1, xpp->flags) < 0 ||
	    xdl_build_script(&xe1, &xscr1) < 0) {
		xdl_free_env(&xe1);
		return -1;
	}
	if (xdl_change_compact(&xe2.xdf1, &xe2.xdf2, xpp->flags) < 0 ||
	    xdl_change_compact(&xe2.xdf2, &xe2.xdf1, xpp->flags) < 0 ||
	    xdl_build_script(&xe2, &xscr2) < 0) {
		xdl_free_script(xscr1);
		xdl_free_env(&xe1);
		xdl_free_env(&xe2);
		return -1;
	}
	status = 0;
	if (!xscr1) {
		result->ptr = xdl_malloc(mf2->size);
		memcpy(result->ptr, mf2->ptr, mf2->size);
		result->size = mf2->size;
	} else if (!xscr2) {
		result->ptr = xdl_malloc(mf1->size);
		memcpy(result->ptr, mf1->ptr, mf1->size);
		result->size = mf1->size;
	} else {
		status = xdl_do_merge(&xe1, xscr1,
				      &xe2, xscr2,
				      xmp, result);
	}
	xdl_free_script(xscr1);
	xdl_free_script(xscr2);

	xdl_free_env(&xe1);
	xdl_free_env(&xe2);

	return status;
}