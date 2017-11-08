static ap_filter_rec_t *get_filter_handle(const char *name,
                                          const filter_trie_node *filter_set)
{
    if (filter_set) {
        const char *n;
        const filter_trie_node *node;

        node = filter_set;
        for (n = name; *n; n++) {
            int start, end;
            start = 0;
            end = node->nchildren - 1;
            while (end >= start) {
                int middle = (end + start) / 2;
                char ch = node->children[middle].c;
                if (*n == ch) {
                    node = node->children[middle].child;
                    break;
                }
                else if (*n < ch) {
                    end = middle - 1;
                }
                else {
                    start = middle + 1;
                }
            }
            if (end < start) {
                node = NULL;
                break;
            }
        }

        if (node && node->frec) {
            return node->frec;
        }
    }
    return NULL;
}