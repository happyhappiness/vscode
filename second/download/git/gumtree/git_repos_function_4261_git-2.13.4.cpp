static void add_push_refspec(struct remote *remote, const char *ref)
{
	ALLOC_GROW(remote->push_refspec,
		   remote->push_refspec_nr + 1,
		   remote->push_refspec_alloc);
	remote->push_refspec[remote->push_refspec_nr++] = ref;
}