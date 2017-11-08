static void store_variant_list(request_rec *r, negotiation_state *neg)
{
    if (r->main == NULL) {
        apr_table_setn(r->notes, "variant-list", make_variant_list(r, neg));
    }
    else {
        apr_table_setn(r->main->notes, "variant-list",
                      make_variant_list(r->main, neg));
    }
}