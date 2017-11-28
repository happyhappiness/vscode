heap_t
heap_delete(heap * hp, heap_node * elm)
{
    heap_node *lastNode;
    heap_t data = elm->data;

    assert(_heap_node_exist(hp, hp->last - 1));

    lastNode = hp->nodes[hp->last - 1];
    _heap_swap_element(hp, lastNode, elm);
    heap_extractlast(hp);

    if (elm == lastNode) {
        /*
         * lastNode just got freed, so don't access it in the next
         * block.
         */
        (void) 0;
    } else if (hp->last > 0) {
        if (lastNode->key < hp->nodes[Parent(lastNode->id)]->key)
            _heap_ify_up(hp, lastNode);		/* COOL! */
        _heap_ify_down(hp, lastNode);
    }
    return data;
}