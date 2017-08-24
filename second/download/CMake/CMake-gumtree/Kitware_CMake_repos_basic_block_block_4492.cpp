{
              ldap_value_free_len(vals);
#if defined(USE_WIN32_LDAP)
              Curl_unicodefree(attr);
#endif
              ldap_memfree(attribute);
              if(ber)
                ber_free(ber, 0);

              goto quit;
            }