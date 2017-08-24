{
        *port = '\0';
        port++;
        entry->port = (unsigned short)strtol(port, NULL, 10);
      }