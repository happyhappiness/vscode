static void mod_info_show_parents(request_rec * r, ap_directive_t * node,
                                  int from, int to)
{
    if (from < to)
        mod_info_show_parents(r, node->parent, from, to - 1);
    mod_info_show_open(r, node, to);
}