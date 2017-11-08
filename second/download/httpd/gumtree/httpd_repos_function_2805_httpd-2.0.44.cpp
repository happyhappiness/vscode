static void overlap_hash(overlap_key *elt,
                         overlap_key **hash_table, int nhash,
                         unsigned flags)
{
    /* Each bucket in the hash table holds a red-black tree
     * containing the overlap_keys that hash into that bucket
     */
    overlap_key **child = &(hash_table[elt->elt->key_checksum & (nhash - 1)]);
    overlap_key **root = child;
    overlap_key *parent = NULL;
    overlap_key *next;

    /* Look for the element in the tree */
    while ((next = *child) != NULL) {
        int direction = strcasecmp(elt->elt->key, next->elt->key);
        if (direction < 0) {
            parent = next;
            child = &(next->tree_left);
        }
        else if (direction > 0) {
            parent = next;
            child = &(next->tree_right);
        }
        else {
            /* This is the key we're looking for */
            if (flags == APR_OVERLAP_TABLES_MERGE) {
                /* Just link this node at the end of the list
                 * of values for the key.  It doesn't need to
                 * be linked into the tree, because the node at
                 * the head of this key's value list is in the
                 * tree already.
                 */
                elt->skip = 1;
                elt->merge_next = NULL;
                if (next->merge_last) {
                    next->merge_last->merge_next = elt;
                }
                else {
                    next->merge_next = elt;
                }
                next->merge_last = elt;
            }
            else {
                /* In the "set" case, don't bother storing
                 * this value in the tree if it's already
                 * there, except if the previous value was
                 * from table 'a' (level==0) and this value
                 * is from table 'b' (level==1)
                 */
                if (elt->level > next->level) {
                    elt->tree_left = next->tree_left;
                    if (next->tree_left) {
                        next->tree_left->tree_parent = elt;
                    }
                    elt->tree_right = next->tree_right;
                    if (next->tree_right) {
                        next->tree_right->tree_parent = elt;
                    }
                    elt->tree_parent = next->tree_parent;
                    elt->color = next->color;
                    (*child) = elt;
                    elt->merge_next = NULL;
                    elt->merge_last = NULL;
                    elt->skip = 0;
                    next->skip = 1;
                }
                else {
                    elt->skip = 1;
                }
            }
            return;
        }
    }

    /* The element wasn't in the tree, so add it */
    elt->tree_left = NULL;
    elt->tree_right = NULL;
    elt->tree_parent = parent;
    (*child) = elt;
    elt->merge_next = NULL;
    elt->merge_last = NULL;
    elt->skip = 0;
    elt->color = RED;

    /* Shuffle the nodes to maintain the red-black tree's balanced
     * shape property.  (This is what guarantees O(n*log(n)) worst-case
     * performance for apr_table_overlap().)
     */
    next = elt;
    while ((next->tree_parent) && (next->tree_parent->color == RED)) {
        /* Note: Root is always black, and red and black nodes
         * alternate on any path down the tree.  So if we're inside
         * this block, the grandparent node is non-NULL.
         */
        overlap_key *grandparent = next->tree_parent->tree_parent;
        if (next->tree_parent == grandparent->tree_left) {
            overlap_key *parent_sibling = grandparent->tree_right;
            if (parent_sibling && (parent_sibling->color == RED)) {
                next->tree_parent->color = BLACK;
                parent_sibling->color = BLACK;
                grandparent->color = RED;
                next = grandparent;
            }
            else {
                if (next == next->tree_parent->tree_right) {
                    next = next->tree_parent;
                    rotate_counterclockwise(root, next);
                }
                next->tree_parent->color = BLACK;
                next->tree_parent->tree_parent->color = RED;
                rotate_clockwise(root, next->tree_parent->tree_parent);
            }
        }
        else {
            overlap_key *parent_sibling = grandparent->tree_left;
            if (parent_sibling && (parent_sibling->color == RED)) {
                next->tree_parent->color = BLACK;
                parent_sibling->color = BLACK;
                grandparent->color = RED;
                next = grandparent;
            }
            else {
                if (next == next->tree_parent->tree_left) {
                    next = next->tree_parent;
                    rotate_clockwise(root, next);
                }
                next->tree_parent->color = BLACK;
                next->tree_parent->tree_parent->color = RED;
                rotate_counterclockwise(root, next->tree_parent->tree_parent);
            }
        }
    }
    (*root)->color = BLACK;
}