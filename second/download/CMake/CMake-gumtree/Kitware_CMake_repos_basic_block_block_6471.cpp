f(CFStringGetCString(cert_summary,
                                cert_summary_c,
                                128,
                                kCFStringEncodingUTF8)) {
            infof(data, "Client certificate: %s\n", cert_summary_c);
          }