static void conn_submit_all (void)
{
  port_entry_t *pe;

  if (port_collect_total)
    conn_submit_port_total ();

  for (pe = port_list_head; pe != NULL; pe = pe->next)
    conn_submit_port_entry (pe);
}