static int unpack_failed(struct unpack_trees_options *o, const char *message)
{
	discard_index(&o->result);
	if (!o->gently && !o->exiting_early) {
		if (message)
			return error("%s", message);
		return -1;
	}
	return -1;
}