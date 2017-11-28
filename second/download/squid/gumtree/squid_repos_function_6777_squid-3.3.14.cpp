static void
_heap_copy_element(heap_node * src, heap_node * dest)
{
    dest->key = src->key;
    dest->data = src->data;
}