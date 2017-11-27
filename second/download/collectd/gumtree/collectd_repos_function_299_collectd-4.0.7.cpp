static int data_set2av (data_set_t *ds, AV *array)
{
	int i = 0;

	if ((NULL == ds) || (NULL == array))
		return -1;

	Perl_av_extend (perl, array, ds->ds_num);

	for (i = 0; i < ds->ds_num; ++i) {
		HV *source = Perl_newHV (perl);

		if (NULL == Perl_hv_store (perl, source, "name", 4,
				Perl_newSVpv (perl, ds->ds[i].name, 0), 0))
			return -1;

		if (NULL == Perl_hv_store (perl, source, "type", 4,
				Perl_newSViv (perl, ds->ds[i].type), 0))
			return -1;

		if (! isnan (ds->ds[i].min))
			if (NULL == Perl_hv_store (perl, source, "min", 3,
					Perl_newSVnv (perl, ds->ds[i].min), 0))
				return -1;

		if (! isnan (ds->ds[i].max))
			if (NULL == Perl_hv_store (perl, source, "max", 3,
					Perl_newSVnv (perl, ds->ds[i].max), 0))
				return -1;

		if (NULL == Perl_av_store (perl, array, i,
				Perl_newRV_noinc (perl, (SV *)source)))
			return -1;
	}
	return 0;
}