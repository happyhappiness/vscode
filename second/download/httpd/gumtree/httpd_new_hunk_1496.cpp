            }
            else {
                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
                              "No matching SSL virtual host for servername "
                              "%s found (using default/first virtual host)",
                              servername);
                /*
                 * RFC 6066 section 3 says "It is NOT RECOMMENDED to send
                 * a warning-level unrecognized_name(112) alert, because
                 * the client's behavior in response to warning-level alerts
                 * is unpredictable."
                 *
                 * To maintain backwards compatibility in mod_ssl, we
                 * no longer send any alert (neither warning- nor fatal-level),
                 * i.e. we take the second action suggested in RFC 6066:
                 * "If the server understood the ClientHello extension but
                 * does not recognize the server name, the server SHOULD take
                 * one of two actions: either abort the handshake by sending
                 * a fatal-level unrecognized_name(112) alert or continue
                 * the handshake."
                 */
            }
        }
    }

    return SSL_TLSEXT_ERR_NOACK;
}
