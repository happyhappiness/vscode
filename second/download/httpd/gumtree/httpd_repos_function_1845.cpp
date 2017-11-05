static void fcgi_begin_request_body_to_array(fcgi_begin_request_body *h,
                                             unsigned char a[])
{
    a[FCGI_BRB_ROLEB1_OFFSET]    = h->roleB1;
    a[FCGI_BRB_ROLEB0_OFFSET]    = h->roleB0;
    a[FCGI_BRB_FLAGS_OFFSET]     = h->flags;
    a[FCGI_BRB_RESERVED0_OFFSET] = h->reserved[0];
    a[FCGI_BRB_RESERVED1_OFFSET] = h->reserved[1];
    a[FCGI_BRB_RESERVED2_OFFSET] = h->reserved[2];
    a[FCGI_BRB_RESERVED3_OFFSET] = h->reserved[3];
    a[FCGI_BRB_RESERVED4_OFFSET] = h->reserved[4];
}