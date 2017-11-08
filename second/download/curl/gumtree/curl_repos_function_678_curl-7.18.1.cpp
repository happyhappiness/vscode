static void close_connections(struct SessionHandle *data)
{
  /* Loop through all open connections and kill them one by one */
  while(-1 != ConnectionKillOne(data))
    ; /* empty loop */
}