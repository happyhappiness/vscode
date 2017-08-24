(address_prefix_match(sa->sa_family, sa,
              prefix->Address.lpSockaddr, prefix->PrefixLength)) {
            prefix_len = prefix->PrefixLength;
          }