        if (!strcasecmp(type, "Basic"))
            ap_note_basic_auth_failure(r);
        else if (!strcasecmp(type, "Digest"))
            ap_note_digest_auth_failure(r);
    }
    else {
        ap_log_rerror(APLOG_MARK, APLOG_ERR,
                      0, r, "need AuthType to note auth failure: %s", r->uri);
    }
}

AP_DECLARE(void) ap_note_basic_auth_failure(request_rec *r)
{
