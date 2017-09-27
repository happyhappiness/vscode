        certs = p7->d.signed_and_enveloped->cert;
        p7->d.signed_and_enveloped->cert = NULL;
        PKCS7_free(p7);
        break;

    default:
        ap_log_error(APLOG_MARK, APLOG_CRIT|APLOG_NOERRNO, 0, s,
                     "Don't understand PKCS7 file %s", pkcs7);
        ssl_die();
    }

    if (!certs) {
        ap_log_error(APLOG_MARK, APLOG_CRIT|APLOG_NOERRNO, 0, s,
                     "No certificates in %s", pkcs7);
        ssl_die();
    }

    fclose(f);

