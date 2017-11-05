static int xdl_prepare_ctx(unsigned int pass, mmfile_t *mf, long narec, xpparam_t const *xpp,
			   xdlclassifier_t *cf, xdfile_t *xdf) {
	unsigned int hbits;
	long nrec, hsize, bsize;
	unsigned long hav;
	char const *blk, *cur, *top, *prev;
	xrecord_t *crec;
	xrecord_t **recs, **rrecs;
	xrecord_t **rhash;
	unsigned long *ha;
	char *rchg;
	long *rindex;

	ha = NULL;
	rindex = NULL;
	rchg = NULL;
	rhash = NULL;
	recs = NULL;

	if (xdl_cha_init(&xdf->rcha, sizeof(xrecord_t), narec / 4 + 1) < 0)
		goto abort;
	if (!(recs = (xrecord_t **) xdl_malloc(narec * sizeof(xrecord_t *))))
		goto abort;

	if (XDF_DIFF_ALG(xpp->flags) == XDF_HISTOGRAM_DIFF)
		hbits = hsize = 0;
	else {
		hbits = xdl_hashbits((unsigned int) narec);
		hsize = 1 << hbits;
		if (!(rhash = (xrecord_t **) xdl_malloc(hsize * sizeof(xrecord_t *))))
			goto abort;
		memset(rhash, 0, hsize * sizeof(xrecord_t *));
	}

	nrec = 0;
	if ((cur = blk = xdl_mmfile_first(mf, &bsize)) != NULL) {
		for (top = blk + bsize; cur < top; ) {
			prev = cur;
			hav = xdl_hash_record(&cur, top, xpp->flags);
			if (nrec >= narec) {
				narec *= 2;
				if (!(rrecs = (xrecord_t **) xdl_realloc(recs, narec * sizeof(xrecord_t *))))
					goto abort;
				recs = rrecs;
			}
			if (!(crec = xdl_cha_alloc(&xdf->rcha)))
				goto abort;
			crec->ptr = prev;
			crec->size = (long) (cur - prev);
			crec->ha = hav;
			recs[nrec++] = crec;

			if ((XDF_DIFF_ALG(xpp->flags) != XDF_HISTOGRAM_DIFF) &&
			    xdl_classify_record(pass, cf, rhash, hbits, crec) < 0)
				goto abort;
		}
	}

	if (!(rchg = (char *) xdl_malloc((nrec + 2) * sizeof(char))))
		goto abort;
	memset(rchg, 0, (nrec + 2) * sizeof(char));

	if (!(rindex = (long *) xdl_malloc((nrec + 1) * sizeof(long))))
		goto abort;
	if (!(ha = (unsigned long *) xdl_malloc((nrec + 1) * sizeof(unsigned long))))
		goto abort;

	xdf->nrec = nrec;
	xdf->recs = recs;
	xdf->hbits = hbits;
	xdf->rhash = rhash;
	xdf->rchg = rchg + 1;
	xdf->rindex = rindex;
	xdf->nreff = 0;
	xdf->ha = ha;
	xdf->dstart = 0;
	xdf->dend = nrec - 1;

	return 0;

abort:
	xdl_free(ha);
	xdl_free(rindex);
	xdl_free(rchg);
	xdl_free(rhash);
	xdl_free(recs);
	xdl_cha_free(&xdf->rcha);
	return -1;
}