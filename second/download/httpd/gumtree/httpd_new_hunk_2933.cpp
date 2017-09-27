     */
    for (i = 0; i < (apr_uint32_t)arr->nelts; i++) {
        if (!strncmp(elts[i].key, "AJP_", 4)) {
            if (ajp_msg_append_uint8(msg, SC_A_REQ_ATTRIBUTE) ||
                ajp_msg_append_string(msg, elts[i].key + 4)   ||
                ajp_msg_append_string(msg, elts[i].val)) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00981)
                        "ajp_marshal_into_msgb: "
                        "Error appending attribute %s=%s",
                        elts[i].key, elts[i].val);
                return AJP_EOVERFLOW;
            }
        }
    }

    if (ajp_msg_append_uint8(msg, SC_A_ARE_DONE)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00982)
               "ajp_marshal_into_msgb: "
               "Error appending the message end");
        return AJP_EOVERFLOW;
    }

    ap_log_rerror(APLOG_MARK, APLOG_TRACE8, 0, r,
            "ajp_marshal_into_msgb: Done");
    return APR_SUCCESS;
}

/*
AJPV13_RESPONSE/AJPV14_RESPONSE:=
