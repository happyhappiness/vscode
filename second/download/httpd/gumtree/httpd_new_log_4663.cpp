ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(01897)
                         "Init: Oops, you want to request client "
                         "authentication, but no CAs are known for "
                         "verification!?  [Hint: SSLCACertificate*]");