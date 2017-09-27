        PKCS7_free(p7);
        break;

    default:
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02213)
                     "Don't understand PKCS7 file %s", pkcs7);
        ssl_die(s);
    }

    if (!certs) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02214)
                     "No certificates in %s", pkcs7);
        ssl_die(s);
    }

    fclose(f);

    return certs;
}
