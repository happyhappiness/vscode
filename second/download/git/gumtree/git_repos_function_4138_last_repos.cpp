void order_objects(const char *orderfile, obj_path_fn_t obj_path,
		   struct obj_order *objs, int nr)
{
	int i;

	if (!nr)
		return;

	prepare_order(orderfile);
	for (i = 0; i < nr; i++) {
		objs[i].orig_order = i;
		objs[i].order = match_order(obj_path(objs[i].obj));
	}
	QSORT(objs, nr, compare_objs_order);
}