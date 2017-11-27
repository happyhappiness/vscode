static int cconn_process_json(struct cconn *io)
{
    if((io->request_type != ASOK_REQ_DATA) &&
            (io->request_type != ASOK_REQ_SCHEMA))
    {
        return -EDOM;
    }

    int result = 1;
    yajl_handle hand;
    yajl_status status;

    hand = yajl_alloc(&callbacks,
#if HAVE_YAJL_V2
      /* alloc funcs = */ NULL,
#else
      /* alloc funcs = */ NULL, NULL,
#endif
      /* context = */ (void *)(&io->yajl));

    if(!hand)
    {
        ERROR ("ceph plugin: yajl_alloc failed.");
        return ENOMEM;
    }

    io->yajl.depth = 0;

    switch(io->request_type)
    {
        case ASOK_REQ_DATA:
            io->yajl.handler = node_handler_fetch_data;
            result = cconn_process_data(io, &io->yajl, hand);
            break;
        case ASOK_REQ_SCHEMA:
            //init daemon specific variables
            io->d->ds_num = 0;
            io->d->last_idx = 0;
            io->d->last_poll_data = NULL;
            io->yajl.handler = node_handler_define_schema;
            io->yajl.handler_arg = io->d;
            result = traverse_json(io->json, io->json_len, hand);
            break;
    }

    if(result)
    {
        goto done;
    }

#if HAVE_YAJL_V2
    status = yajl_complete_parse(hand);
#else
    status = yajl_parse_complete(hand);
#endif

    if (status != yajl_status_ok)
    {
      unsigned char *errmsg = yajl_get_error (hand, /* verbose = */ 0,
          /* jsonText = */ NULL, /* jsonTextLen = */ 0);
      ERROR ("ceph plugin: yajl_parse_complete failed: %s",
          (char *) errmsg);
      yajl_free_error (hand, errmsg);
      yajl_free (hand);
      return 1;
    }

    done:
    yajl_free (hand);
    return result;
}