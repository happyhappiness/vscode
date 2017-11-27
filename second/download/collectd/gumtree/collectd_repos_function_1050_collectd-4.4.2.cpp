pingobj_iter_t *ping_iterator_get (pingobj_t *obj)
{
	return ((pingobj_iter_t *) obj->head);
}