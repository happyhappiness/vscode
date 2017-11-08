int ref_storage_backend_exists(const char *name)
{
	return find_ref_storage_backend(name) != NULL;
}