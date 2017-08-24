infof(conn->data, "SMB request %p state change from %s to %s\n",
          (void *)req, names[req->state], names[newstate])