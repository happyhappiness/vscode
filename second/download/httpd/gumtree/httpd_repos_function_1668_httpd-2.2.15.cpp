static void debug_dump_tree(include_ctx_t *ctx, parse_node_t *root)
{
    parse_node_t *current;
    char *is;

    if (!root) {
        debug_printf(ctx, "     -- Parse Tree empty --\n\n");
        return;
    }

    debug_printf(ctx, "     ----- Parse Tree -----\n");
    current = root;
    is = "     ";

    while (current) {
        switch (current->token.type) {
        case TOKEN_STRING:
        case TOKEN_RE:
            debug_printf(ctx, "%s%s (%s)\n", is, current->token.s,
                         current->token.value);
            current->dump_done = 1;
            current = current->parent;
            continue;

        case TOKEN_NOT:
        case TOKEN_GROUP:
        case TOKEN_RBRACE:
        case TOKEN_LBRACE:
            if (!current->dump_done) {
                debug_printf(ctx, "%s%s\n", is, current->token.s);
                is = apr_pstrcat(ctx->dpool, is, "    ", NULL);
                current->dump_done = 1;
            }

            DUMP__CHILD(ctx, is, current, right)

            if (!current->right || current->right->dump_done) {
                is = apr_pstrmemdup(ctx->dpool, is, strlen(is) - 4);
                if (current->right) current->right->dump_done = 0;
                current = current->parent;
            }
            continue;

        default:
            if (!current->dump_done) {
                debug_printf(ctx, "%s%s\n", is, current->token.s);
                is = apr_pstrcat(ctx->dpool, is, "    ", NULL);
                current->dump_done = 1;
            }

            DUMP__CHILD(ctx, is, current, left)
            DUMP__CHILD(ctx, is, current, right)

            if ((!current->left || current->left->dump_done) &&
                (!current->right || current->right->dump_done)) {

                is = apr_pstrmemdup(ctx->dpool, is, strlen(is) - 4);
                if (current->left) current->left->dump_done = 0;
                if (current->right) current->right->dump_done = 0;
                current = current->parent;
            }
            continue;
        }
    }

    /* it is possible to call this function within the parser loop, to see
     * how the tree is built. That way, we must cleanup after us to dump
     * always the whole tree
     */
    root->dump_done = 0;
    if (root->left) root->left->dump_done = 0;
    if (root->right) root->right->dump_done = 0;

    debug_printf(ctx, "     --- End Parse Tree ---\n\n");

    return;
}