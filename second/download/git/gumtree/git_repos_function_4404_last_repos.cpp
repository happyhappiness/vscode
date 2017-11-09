static void add_fetch_refspec(struct remote *remote, const char *ref)
{
	ALLOC_GROW(remote->fetch_refspec,
		   remote->fetch_refspec_nr + 1,
		   remote->fetch_refspec_alloc);
	remote->fetch_refspec[remote->fetch_refspec_nr++] = ref;
}