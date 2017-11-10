static dav_error * dav_add_if_state(apr_pool_t *p, dav_if_header *ih,
                                    const char *state_token,
                                    dav_if_state_type t, int condition,
                                    const dav_hooks_locks *locks_hooks)
{
    dav_if_state_list *new_sl;

    new_sl = apr_pcalloc(p, sizeof(*new_sl));

    new_sl->condition = condition;
    new_sl->type      = t;

    if (t == dav_if_opaquelock) {
        dav_error *err;

        if ((err = (*locks_hooks->parse_locktoken)(p, state_token,
                                                   &new_sl->locktoken)) != NULL) {
            /* If the state token cannot be parsed, treat it as an
             * unknown state; this will evaluate to "false" later
             * during If header validation. */
            if (err->error_id == DAV_ERR_LOCK_UNK_STATE_TOKEN) {
                new_sl->type = dav_if_unknown;
            }
            else {
                /* ### maybe add a higher-level description */
                return err;
            }
        }
    }
    else
        new_sl->etag = state_token;

    new_sl->next = ih->state;
    ih->state = new_sl;

    return NULL;
}