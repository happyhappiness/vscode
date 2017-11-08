static void trie_node_link(apr_pool_t *p, filter_trie_node *parent,
                           filter_trie_node *child, int c)
{
    int i, j;

    if (parent->nchildren == parent->size) {
        filter_trie_child_ptr *new;
        parent->size *= 2;
        new = (filter_trie_child_ptr *)apr_palloc(p, parent->size *
                                             sizeof(filter_trie_child_ptr));
        memcpy(new, parent->children, parent->nchildren *
               sizeof(filter_trie_child_ptr));
        parent->children = new;
    }

    for (i = 0; i < parent->nchildren; i++) {
        if (c == parent->children[i].c) {
            return;
        }
        else if (c < parent->children[i].c) {
            break;
        }
    }
    for (j = parent->nchildren; j > i; j--) {
        parent->children[j].c = parent->children[j - 1].c;
        parent->children[j].child = parent->children[j - 1].child;
    }
    parent->children[i].c = c;
    parent->children[i].child = child;

    parent->nchildren++;
}