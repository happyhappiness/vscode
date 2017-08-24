{
        case 2: /* DNS name. */
          len = utf8asn1str(&dnsname, CURL_ASN1_IA5_STRING,
                            name.beg, name.end);
          if(len > 0 && (size_t)len == strlen(dnsname))
            matched = Curl_cert_hostcheck(dnsname, hostname);
          else
            matched = 0;
          free(dnsname);
          break;

        case 7: /* IP address. */
          matched = (size_t) (name.end - q) == addrlen &&
                    !memcmp(&addr, q, addrlen);
          break;
        }