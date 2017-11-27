static int oconfig_item2hv (pTHX_ oconfig_item_t *ci, HV *hash)
{
	AV *values;
	AV *children;

	if (NULL == hv_store (hash, "key", 3, newSVpv (ci->key, 0), 0))
		return -1;

	values = newAV ();
	if (0 < ci->values_num)
		av_extend (values, ci->values_num);

	if (NULL == hv_store (hash, "values", 6, newRV_noinc ((SV *)values), 0)) {
		av_clear (values);
		av_undef (values);
		return -1;
	}

	for (int i = 0; i < ci->values_num; ++i) {
		SV *value;

		switch (ci->values[i].type) {
			case OCONFIG_TYPE_STRING:
				value = newSVpv (ci->values[i].value.string, 0);
				break;
			case OCONFIG_TYPE_NUMBER:
				value = newSVnv ((NV)ci->values[i].value.number);
				break;
			case OCONFIG_TYPE_BOOLEAN:
				value = ci->values[i].value.boolean ? &PL_sv_yes : &PL_sv_no;
				break;
			default:
				log_err ("oconfig_item2hv: Invalid value type %i.",
						ci->values[i].type);
				value = &PL_sv_undef;
		}

		if (NULL == av_store (values, i, value)) {
			sv_free (value);
			return -1;
		}
	}

	/* ignoring 'parent' member which is uninteresting in this case */

	children = newAV ();
	if (0 < ci->children_num)
		av_extend (children, ci->children_num);

	if (NULL == hv_store (hash, "children", 8, newRV_noinc ((SV *)children), 0)) {
		av_clear (children);
		av_undef (children);
		return -1;
	}

	for (int i = 0; i < ci->children_num; ++i) {
		HV *child = newHV ();

		if (0 != oconfig_item2hv (aTHX_ ci->children + i, child)) {
			hv_clear (child);
			hv_undef (child);
			return -1;
		}

		if (NULL == av_store (children, i, newRV_noinc ((SV *)child))) {
			hv_clear (child);
			hv_undef (child);
			return -1;
		}
	}
	return 0;
}