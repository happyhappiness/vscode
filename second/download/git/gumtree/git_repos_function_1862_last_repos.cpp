void *alloc_blob_node(void)
{
	struct blob *b = alloc_node(&blob_state, sizeof(struct blob));
	b->object.type = OBJ_BLOB;
	return b;
}