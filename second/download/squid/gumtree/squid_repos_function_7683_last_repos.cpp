static void
_heap_swap_element(heap * hp, heap_node * elm1, heap_node * elm2)
{
    int elm1Id = elm1->id;
    elm1->id = elm2->id;
    elm2->id = elm1Id;
    hp->nodes[elm1->id] = elm1;
    hp->nodes[elm2->id] = elm2;
}