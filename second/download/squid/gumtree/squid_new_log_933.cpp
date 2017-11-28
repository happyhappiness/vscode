snprintf(memory_keytab_name, strlen("MEMORY:negotiate_kerberos_auth_")+16,
                 "MEMORY:negotiate_kerberos_auth_%d", (unsigned int) getpid());