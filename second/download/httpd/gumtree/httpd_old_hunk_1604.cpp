        vec_next->iov_base = CRLF;
        vec_next->iov_len = sizeof(CRLF) - 1;
        vec_next++;
        t_elt++;
    } while (t_elt < t_end);

#if APR_CHARSET_EBCDIC
    {
        apr_size_t len;
        char *tmp = apr_pstrcatv(r->pool, vec, vec_next - vec, &len);
        ap_xlate_proto_to_ascii(tmp, len);
        return apr_brigade_write(h->bb, NULL, NULL, tmp, len);
