static void remove_variant(struct rerere_id *id)
{
	unlink_or_warn(rerere_path(id, "postimage"));
	unlink_or_warn(rerere_path(id, "preimage"));
	id->collection->status[id->variant] = 0;
}