        s = va_arg(va, const char *);
        if (s == NULL)
            break;
        len = strlen(s);
        ascii_s = apr_pstrmemdup(r->pool, s, len);
        ap_xlate_proto_to_ascii(ascii_s, len);
        if (ap_rputs(ascii_s, r) < 0) {
            va_end(va);
            return -1;
        }
        written += len;
    }
    va_end(va);

    return written;
}
