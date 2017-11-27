static int data_set2av (pTHX_ data_set_t *ds, AV *array)
{
	if ((NULL == ds) || (NULL == array))
		return -1;

	av_extend (array, ds->ds_num);

	for (size_t i = 0; i < ds->ds_num; ++i) {
		HV *source = newHV ();

		if (NULL == hv_store (source, "name", 4,
				newSVpv (ds->ds[i].name, 0), 0))
			return -1;

		if (NULL == hv_store (source, "type", 4, newSViv (ds->ds[i].type), 0))
			return -1;

		if (! isnan (ds->ds[i].min))
			if (NULL == hv_store (source, "min", 3,
					newSVnv (ds->ds[i].min), 0))
				return -1;

		if (! isnan (ds->ds[i].max))
			if (NULL == hv_store (source, "max", 3,
					newSVnv (ds->ds[i].max), 0))
				return -1;

		if (NULL == av_store (array, i, newRV_noinc ((SV *)source)))
			return -1;
	}
	return 0;
}