static void get_pseudo_node_identifier(unsigned char *node)
{
    get_random_info(node);
    node[0] |= 0x80;                    /* this designates a random node ID */
}