static int config_set_element_cmp(const void *unused_cmp_data,
				  const struct config_set_element *e1,
				  const struct config_set_element *e2,
				  const void *unused_keydata)
{
	return strcmp(e1->key, e2->key);
}