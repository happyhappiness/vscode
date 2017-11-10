void ap_xlate_proto_to_ascii(char *buffer, apr_size_t len)
{
    apr_size_t inbytes_left, outbytes_left;

    inbytes_left = outbytes_left = len;
    apr_xlate_conv_buffer(ap_hdrs_to_ascii, buffer, &inbytes_left,
                          buffer, &outbytes_left);
}