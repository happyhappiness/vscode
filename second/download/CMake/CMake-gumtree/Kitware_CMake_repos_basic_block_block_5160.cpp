{
        struct site_blacklist_entry *site;

        site = curr->ptr;
        if(strcasecompare(site->hostname, conn->host.name) &&
           site->port == conn->remote_port) {
          infof(handle, "Site %s:%d is pipeline blacklisted\n",
                conn->host.name, conn->remote_port);
          return TRUE;
        }
        curr = curr->next;
      }