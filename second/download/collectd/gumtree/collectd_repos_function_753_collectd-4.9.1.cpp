static int ptarget_create (const oconfig_item_t *ci, void **user_data)
{
	return fc_create (FC_TARGET, ci, user_data);
}