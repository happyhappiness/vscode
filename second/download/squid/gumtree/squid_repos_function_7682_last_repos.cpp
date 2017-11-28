static void
_heap_ify_up(heap * hp, heap_node * elm)
{
    heap_node *parentNode;
    while (elm->id > 0) {
        parentNode = hp->nodes[Parent(elm->id)];
        if (parentNode->key <= elm->key)
            break;
        _heap_swap_element(hp, parentNode, elm);    /* Demote the parent. */
    }
}