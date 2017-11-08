ssl_expr *ssl_expr_make(ssl_expr_node_op op, void *a1, void *a2)
{
    ssl_expr *node;

    node = (ssl_expr *)apr_palloc(ssl_expr_info.pool, sizeof(ssl_expr));
    node->node_op   = op;
    node->node_arg1 = (char *)a1;
    node->node_arg2 = (char *)a2;
    return node;
}