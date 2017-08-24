{
        cert2 = CERT_FindCertIssuer(cert, now, certUsageSSLCA);
        while(cert2) {
          i++;
          if(cert2->isRoot) {
            CERT_DestroyCertificate(cert2);
            break;
          }
          cert3 = CERT_FindCertIssuer(cert2, now, certUsageSSLCA);
          CERT_DestroyCertificate(cert2);
          cert2 = cert3;
        }
      }