{
      acc += nva[i].namelen + nva[i].valuelen;

      DEBUGF(infof(conn->data, "h2 header: %.*s:%.*s\n",
                   nva[i].namelen, nva[i].name,
                   nva[i].valuelen, nva[i].value));
    }