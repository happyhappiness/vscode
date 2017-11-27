static void conn_submit_all (void)
{
  if (port_collect_total)
    conn_submit_port_total ();

  for (port_entry_t *pe = port_list_head; pe != NULL; pe = pe->next)
    conn_submit_port_entry (pe);
}