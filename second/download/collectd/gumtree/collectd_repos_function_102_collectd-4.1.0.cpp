void llentry_destroy (llentry_t *e)
{
	free (e->key);
	free (e);
}