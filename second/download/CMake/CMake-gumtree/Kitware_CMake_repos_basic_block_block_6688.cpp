{
        failf(data, "server certificate verification failed. CAfile: %s "
              "CRLfile: %s", SSL_CONN_CONFIG(CAfile) ? SSL_CONN_CONFIG(CAfile):
              "none",
              SSL_SET_OPTION(CRLfile)?SSL_SET_OPTION(CRLfile):"none");
        return CURLE_SSL_CACERT;
      }