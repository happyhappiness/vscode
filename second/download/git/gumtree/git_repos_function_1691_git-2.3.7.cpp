int for_each_packed_object(each_packed_object_fn cb, void *data)
{
	struct packed_git *p;
	int r = 0;

	prepare_packed_git();
	for (p = packed_git; p; p = p->next) {
		r = for_each_object_in_pack(p, cb, data);
		if (r)
			break;
	}
	return r;
}