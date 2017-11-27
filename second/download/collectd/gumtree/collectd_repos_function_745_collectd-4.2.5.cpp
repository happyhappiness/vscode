pingobj_iter_t *ping_iterator_next (pingobj_iter_t *iter)
{
	return ((pingobj_iter_t *) iter->next);
}