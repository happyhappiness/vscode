ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(02969)
                         "stapling_check_response: response has certificate "
                         "status %s (reason: %s) for serial number %s",
                         OCSP_cert_status_str(status),
                         (reason != OCSP_REVOKED_STATUS_NOSTATUS) ?
                         OCSP_crl_reason_str(reason) : "n/a",
                         snum[0] ? snum : "[n/a]");