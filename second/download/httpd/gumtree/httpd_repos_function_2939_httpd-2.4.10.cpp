static int handle_headers(request_rec *r,
                          int *state,
                          char *readbuf)
{
    const char *itr = readbuf;

    while (*itr) {
        if (*itr == '\r') {
            switch (*state) {
                case HDR_STATE_GOT_CRLF:
                    *state = HDR_STATE_GOT_CRLFCR;
                    break;

                default:
                    *state = HDR_STATE_GOT_CR;
                    break;
            }
        }
        else if (*itr == '\n') {
            switch (*state) {
                 case HDR_STATE_GOT_LF:
                     *state = HDR_STATE_DONE_WITH_HEADERS;
                     break;

                 case HDR_STATE_GOT_CR:
                     *state = HDR_STATE_GOT_CRLF;
                     break;

                 case HDR_STATE_GOT_CRLFCR:
                     *state = HDR_STATE_DONE_WITH_HEADERS;
                     break;

                 default:
                     *state = HDR_STATE_GOT_LF;
                     break;
            }
        }
        else {
            *state = HDR_STATE_READING_HEADERS;
        }

        if (*state == HDR_STATE_DONE_WITH_HEADERS)
            break;

        ++itr;
    }

    if (*state == HDR_STATE_DONE_WITH_HEADERS) {
        return 1;
    }

    return 0;
}