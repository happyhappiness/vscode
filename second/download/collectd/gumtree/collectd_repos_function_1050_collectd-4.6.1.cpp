int plugin_register_write (const char *name,
		int (*callback) (const data_set_t *ds, const value_list_t *vl))
{
	return (register_callback (&list_write, name, (void *) callback));
}