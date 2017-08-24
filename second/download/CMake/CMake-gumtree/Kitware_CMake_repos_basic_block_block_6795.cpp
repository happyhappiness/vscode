{
          result = Curl_extract_certinfo(conn, i++, (char *)cert->derCert.data,
                                         (char *)cert->derCert.data +
                                                 cert->derCert.len);
          if(result)
            break;

          if(cert->isRoot) {
            CERT_DestroyCertificate(cert);
            break;
          }

          cert2 = CERT_FindCertIssuer(cert, now, certUsageSSLCA);
          CERT_DestroyCertificate(cert);
        }