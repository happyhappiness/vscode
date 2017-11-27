static void tbl_result_clear (tbl_result_t *res)
{
	sfree (res->type);

	sfree (res->instance_prefix);
	sfree (res->instances);
	res->instances_num = 0;

	sfree (res->values);
	res->values_num = 0;

	res->ds = NULL;
}