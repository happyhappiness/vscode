static void move_to_hold(h2_bucket_beam *beam, 
                         apr_bucket_brigade *sender_bb)
{
    apr_bucket *b;
    while (sender_bb && !APR_BRIGADE_EMPTY(sender_bb)) {
        b = APR_BRIGADE_FIRST(sender_bb);
        APR_BUCKET_REMOVE(b);
        H2_BLIST_INSERT_TAIL(&beam->send_list, b);
    }
}