static void conn_submit_all (void)
{
  port_entry_t *pe;

  for (pe = port_list_head; pe != NULL; pe = pe->next)
    conn_submit_port_entry (pe);
}