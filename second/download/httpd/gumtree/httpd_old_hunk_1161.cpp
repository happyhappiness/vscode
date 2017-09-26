                             "Error ajp_marshal_into_msgb - "
                             "Error appending the SSL key size");
                return APR_EGENERAL;
            }
        }
    }
    /* Use the environment vars prefixed with AJP_
     * and pass it to the header striping that prefix.
     */
    for (i = 0; i < (apr_uint32_t)arr->nelts; i++) {
        if (!strncmp(elts[i].key, "AJP_", 4)) {
            if (ajp_msg_append_uint8(msg, SC_A_REQ_ATTRIBUTE) ||
