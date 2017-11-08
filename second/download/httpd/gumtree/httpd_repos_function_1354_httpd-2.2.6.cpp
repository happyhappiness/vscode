static void terminate_header(apr_bucket_brigade *bb)
{
    char tmp[] = "X-Pad: avoid browser bug" CRLF;
    char crlf[] = CRLF;
    apr_off_t len;
    apr_size_t buflen;

    (void) apr_brigade_length(bb, 1, &len);

    if (len >= 255 && len <= 257) {
        buflen = strlen(tmp);
        ap_xlate_proto_to_ascii(tmp, buflen);
        apr_brigade_write(bb, NULL, NULL, tmp, buflen);
    }
    buflen = strlen(crlf);
    ap_xlate_proto_to_ascii(crlf, buflen);
    apr_brigade_write(bb, NULL, NULL, crlf, buflen);
}