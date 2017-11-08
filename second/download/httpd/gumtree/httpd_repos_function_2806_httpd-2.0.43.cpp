static void rotate_counterclockwise(overlap_key **root,
                                    overlap_key *rotate_node)
{
    overlap_key *child = rotate_node->tree_right;
    rotate_node->tree_right = child->tree_left;
    if (rotate_node->tree_right) {
        rotate_node->tree_right->tree_parent = rotate_node;
    }
    child->tree_parent = rotate_node->tree_parent;
    if (child->tree_parent == NULL) {
        *root = child;
    }
    else {
        if (rotate_node == rotate_node->tree_parent->tree_left) {
            rotate_node->tree_parent->tree_left = child;
        }
        else {
            rotate_node->tree_parent->tree_right = child;
        }
    }
    child->tree_left = rotate_node;
    rotate_node->tree_parent = child;
}