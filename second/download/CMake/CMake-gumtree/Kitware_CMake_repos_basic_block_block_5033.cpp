{
      Sockbuf *sb;
      ldap_get_option(li->ld, LDAP_OPT_SOCKBUF, &sb);
      ber_sockbuf_add_io(sb, &ldapsb_tls, LBER_SBIOD_LEVEL_TRANSPORT, conn);
      li->sslinst = TRUE;
      li->recv = conn->recv[FIRSTSOCKET];
      li->send = conn->send[FIRSTSOCKET];
    }