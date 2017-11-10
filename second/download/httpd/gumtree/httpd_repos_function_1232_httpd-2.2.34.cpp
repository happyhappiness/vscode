static void maybe_add_default_accepts(negotiation_state *neg,
                                      int prefer_scripts)
{
    accept_rec *new_accept;

    if (!neg->accepts) {
        neg->accepts = apr_array_make(neg->pool, 4, sizeof(accept_rec));

        new_accept = (accept_rec *) apr_array_push(neg->accepts);

        new_accept->name = "*/*";
        new_accept->quality = 1.0f;
        new_accept->level = 0.0f;
    }

    new_accept = (accept_rec *) apr_array_push(neg->accepts);

    new_accept->name = CGI_MAGIC_TYPE;
    if (neg->use_rvsa) {
        new_accept->quality = 0;
    }
    else {
        new_accept->quality = prefer_scripts ? 2.0f : 0.001f;
    }
    new_accept->level = 0.0f;
}