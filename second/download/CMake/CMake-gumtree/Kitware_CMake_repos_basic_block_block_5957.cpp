f(scopeidx == 0) {
            infof(data, "Invalid network interface: %s; %s\n", ifname,
                  strerror(errno));
          }