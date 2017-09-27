            return apr_snprintf(buffer, maxlen,
                                "type=%d[length=%d, flags=%d, stream=%d]",
                                frame->hd.type, (int)frame->hd.length,
                                frame->hd.flags, frame->hd.stream_id);
    }
}
