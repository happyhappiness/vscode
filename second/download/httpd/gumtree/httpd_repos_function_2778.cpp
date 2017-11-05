static ap_parse_node_t *ap_expr_clone_tree(apr_pool_t *pool,
                                           ap_parse_node_t *pnode,
                                           ap_parse_node_t *parent)
{
    ap_parse_node_t *ret;
    ret = apr_pmemdup(pool, pnode, sizeof(ap_parse_node_t));
    if (pnode->left) {
        ret->left = ap_expr_clone_tree(pool, pnode->left, ret);
    }
    if (pnode->right) {
        ret->right = ap_expr_clone_tree(pool, pnode->right, ret);
    }
    ret->parent = parent;
    return ret;
}