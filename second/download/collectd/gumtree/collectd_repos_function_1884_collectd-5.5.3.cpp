static void sigrok_free_drvopts(struct sr_config *src)
{
	g_variant_unref(src->data);
	g_free(src);
}