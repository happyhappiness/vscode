static int
traverse_json(const unsigned char *json, uint32_t json_len, yajl_handle hand)
{
    yajl_status status = yajl_parse(hand, json, json_len);
    unsigned char *msg;

    switch(status)
    {
        case yajl_status_error:
            msg = yajl_get_error(hand, /* verbose = */ 1,
                                       /* jsonText = */ (unsigned char *) json,
                                                      (unsigned int) json_len);
            ERROR ("ceph plugin: yajl_parse failed: %s", msg);
            yajl_free_error(hand, msg);
            return 1;
        case yajl_status_client_canceled:
            return 1;
        default:
            return 0;
    }
}