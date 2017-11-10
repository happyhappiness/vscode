static void get_pseudo_node_identifier(unsigned char *node)
{
    get_random_info(node);
    node[0] |= 0x01;                    /* this designates a random multicast node ID */
}