static int pmatch_create (const oconfig_item_t *ci, void **user_data)
{
	return fc_create (FC_MATCH, ci, user_data);
}