{
      conn->tunnel_state[sockindex] = TUNNEL_INIT;
      infof(data, "TUNNEL_STATE switched to: %d\n",
            conn->tunnel_state[sockindex]);
    }