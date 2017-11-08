static void move_to_hold(h2_bucket_beam *beam, 
                         apr_bucket_brigade *red_brigade)
{
    apr_bucket *b;
    while (red_brigade && !APR_BRIGADE_EMPTY(red_brigade)) {
        b = APR_BRIGADE_FIRST(red_brigade);
        APR_BUCKET_REMOVE(b);
        H2_BLIST_INSERT_TAIL(&beam->send_list, b);
    }
}