f(r == CHUNKE_STOP) {
              /* we're done reading chunks! */
              infof(data, "chunk reading DONE\n");
              keepon = FALSE;
              /* we did the full CONNECT treatment, go COMPLETE */
              conn->tunnel_state[sockindex] = TUNNEL_COMPLETE;
            }