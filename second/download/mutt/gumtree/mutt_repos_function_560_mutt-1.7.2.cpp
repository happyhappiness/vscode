void mutt_socket_free (CONNECTION* conn)
{
  CONNECTION* iter;
  CONNECTION* tmp;

  iter = Connections;

  /* head is special case, doesn't need prev updated */
  if (iter == conn)
  {
    Connections = iter->next;
    FREE (&iter);
    return;
  }

  while (iter->next)
  {
    if (iter->next == conn)
    {
      tmp = iter->next;
      iter->next = tmp->next;
      FREE (&tmp);
      return;
    }
    iter = iter->next;
  }
}