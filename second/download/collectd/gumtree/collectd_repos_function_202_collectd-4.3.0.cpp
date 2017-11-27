static int us_write (const data_set_t *ds, const value_list_t *vl)
{
	cache_update (ds, vl);
	cache_flush (2 * interval_g);

	return (0);
}