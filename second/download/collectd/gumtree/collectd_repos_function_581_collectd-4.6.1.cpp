static int ptarget_invoke (const data_set_t *ds, value_list_t *vl,
		notification_meta_t **meta, void **user_data)
{
	return fc_exec (FC_TARGET, ds, vl, meta, user_data);
}