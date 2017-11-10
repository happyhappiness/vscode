static void init_state(void)
{
    uuid_state_seqnum = true_random();
    get_pseudo_node_identifier(uuid_state_node);
}