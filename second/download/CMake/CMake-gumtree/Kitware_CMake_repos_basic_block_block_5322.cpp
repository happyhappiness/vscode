infof(conn->data, "SMB conn %p state change from %s to %s\n",
          (void *)smb, names[smb->state], names[newstate])