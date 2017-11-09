static void unlink_rr_item(struct rerere_id *id)
{
	unlink_or_warn(rerere_path(id, "thisimage"));
	remove_variant(id);
	id->collection->status[id->variant] = 0;
}