        ap_xlate_proto_to_ascii(ascii_s, len);
        if (ap_rputs(ascii_s, r) < 0)
            return -1;
        written += len;
    }
    va_end(va);

    return written;
}
#endif /* APR_CHARSET_EBCDIC */
