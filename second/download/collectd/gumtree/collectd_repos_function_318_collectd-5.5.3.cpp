static int update_iflist (struct ifinfomsg *msg, const char *dev)
{
  /* Update the `iflist'. It's used to know which interfaces exist and query
   * them later for qdiscs and classes. */
  if ((msg->ifi_index >= 0) && ((size_t) msg->ifi_index >= iflist_len))
  {
    char **temp;

    temp = (char **) realloc (iflist, (msg->ifi_index + 1) * sizeof (char *));
    if (temp == NULL)
    {
      ERROR ("netlink plugin: update_iflist: realloc failed.");
      return (-1);
    }

    memset (temp + iflist_len, '\0',
        (msg->ifi_index + 1 - iflist_len) * sizeof (char *));
    iflist = temp;
    iflist_len = msg->ifi_index + 1;
  }
  if ((iflist[msg->ifi_index] == NULL)
      || (strcmp (iflist[msg->ifi_index], dev) != 0))
  {
    sfree (iflist[msg->ifi_index]);
    iflist[msg->ifi_index] = strdup (dev);
  }

  return (0);
}