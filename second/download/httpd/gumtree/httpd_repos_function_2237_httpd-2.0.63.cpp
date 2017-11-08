static int startup_children(int number_to_start)
{
    int i;

    for (i = 0; number_to_start && i < num_daemons; ++i) {
        if (ap_child_table[i].pid) {
            continue;
        }
        if (make_child(ap_server_conf, i) < 0) {
            break;
        }
        --number_to_start;
    }
    return number_to_start;
}