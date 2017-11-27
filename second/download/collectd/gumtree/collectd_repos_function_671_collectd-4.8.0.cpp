static int pmatch_match (const data_set_t *ds, const value_list_t *vl,
		notification_meta_t **meta, void **user_data)
{
	return fc_exec (FC_MATCH, ds, vl, meta, user_data);
}