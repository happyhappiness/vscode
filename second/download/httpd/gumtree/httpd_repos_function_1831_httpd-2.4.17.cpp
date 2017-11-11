static int http_send_options(request_rec *r)
{
    if ((r->method_number == M_OPTIONS) && r->uri && (r->uri[0] == '*') &&
         (r->uri[1] == '\0')) {
        return DONE;           /* Send HTTP pong, without Allow header */
    }
    return DECLINED;
}