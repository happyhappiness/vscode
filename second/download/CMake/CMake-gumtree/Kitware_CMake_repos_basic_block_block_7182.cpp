e{
            failf(data,
                  "schannel: connection hostname (%s) "
                  "does not match certificate name (%s)",
                  conn->host.name,
                  cert_hostname);
            result = CURLE_PEER_FAILED_VERIFICATION;
          }