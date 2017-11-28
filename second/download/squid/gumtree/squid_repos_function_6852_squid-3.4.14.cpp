static void
_heap_ify_down(heap * hp, heap_node * elm)
{
    heap_node *kid;
    int left = 0, right = 0;
    int isTrue = 1;
    while (isTrue) {
        left = Left(elm->id);
        right = Right(elm->id);
        if (!_heap_node_exist(hp, left)) {
            /* At the bottom of the heap (no child). */

            assert(!_heap_node_exist(hp, right));
            break;
        } else if (!_heap_node_exist(hp, right))
            /*  Only left child exists. */

            kid = hp->nodes[left];
        else {
            if (hp->nodes[right]->key < hp->nodes[left]->key)
                kid = hp->nodes[right];
            else
                kid = hp->nodes[left];
        }
        if (elm->key <= kid->key)
            break;
        _heap_swap_element(hp, kid, elm);
    }
}