            break;

        ++itr;
    }

    if (*state == HDR_STATE_DONE_WITH_HEADERS) {
        return 1;
    }

    return 0;
}

static void dump_header_to_log(request_rec *r, unsigned char fheader[],
