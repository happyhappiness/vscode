{
        int alert = gnutls_alert_get(session);
        strerr = gnutls_alert_get_name(alert);
      }