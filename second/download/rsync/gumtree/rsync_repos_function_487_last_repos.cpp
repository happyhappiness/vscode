static int id_access_sorter(const void *r1, const void *r2)
{
	id_access *ida1 = (id_access *)r1;
	id_access *ida2 = (id_access *)r2;
	id_t rid1 = ida1->id, rid2 = ida2->id;
	if ((ida1->access ^ ida2->access) & NAME_IS_USER)
		return ida1->access & NAME_IS_USER ? -1 : 1;
	return rid1 == rid2 ? 0 : rid1 < rid2 ? -1 : 1;
}