infof(conn->data, "SMTP %p state change from %s to %s\n",
          (void *)smtpc, names[smtpc->state], names[newstate])