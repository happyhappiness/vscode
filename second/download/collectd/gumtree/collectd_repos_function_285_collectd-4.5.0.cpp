static int config_set_query (c_psql_database_t *db, const oconfig_item_t *ci)
{
	if ((0 != ci->children_num) || (1 != ci->values_num)
			|| (OCONFIG_TYPE_STRING != ci->values[0].type)) {
		log_err ("Query expects a single string argument.");
		return 1;
	}
	return set_query (db, ci->values[0].value.string);
}