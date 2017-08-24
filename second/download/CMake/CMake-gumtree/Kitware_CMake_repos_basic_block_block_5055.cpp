f(error) {
            ber_memfree(bvals);
            ber_free(ber, 0);
            ldap_msgfree(msg);
            *err = error;
            return -1;
          }