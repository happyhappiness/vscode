static filter_trie_node *trie_node_alloc(apr_pool_t *p,
                                         filter_trie_node *parent, char c)
{
    filter_trie_node *new_node;
    if (parent) {
        int i;
        for (i = 0; i < parent->nchildren; i++) {
            if (c == parent->children[i].c) {
                return parent->children[i].child;
            }
            else if (c < parent->children[i].c) {
                break;
            }
        }
        new_node =
            (filter_trie_node *)apr_palloc(p, sizeof(filter_trie_node));
        trie_node_link(p, parent, new_node, c);
    }
    else { /* No parent node */
        new_node = (filter_trie_node *)apr_palloc(p,
                                                  sizeof(filter_trie_node));
    }

    new_node->frec = NULL;
    new_node->nchildren = 0;
    new_node->size = TRIE_INITIAL_SIZE;
    new_node->children = (filter_trie_child_ptr *)apr_palloc(p,
                             new_node->size * sizeof(filter_trie_child_ptr));
    return new_node;
}