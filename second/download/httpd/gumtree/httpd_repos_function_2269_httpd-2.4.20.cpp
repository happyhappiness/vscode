void h2_push_policy_determine(struct h2_request *req, apr_pool_t *p, int push_enabled)
{
    h2_push_policy policy = H2_PUSH_NONE;
    if (push_enabled) {
        const char *val = apr_table_get(req->headers, "accept-push-policy");
        if (val) {
            if (ap_find_token(p, val, "fast-load")) {
                policy = H2_PUSH_FAST_LOAD;
            }
            else if (ap_find_token(p, val, "head")) {
                policy = H2_PUSH_HEAD;
            }
            else if (ap_find_token(p, val, "default")) {
                policy = H2_PUSH_DEFAULT;
            }
            else if (ap_find_token(p, val, "none")) {
                policy = H2_PUSH_NONE;
            }
            else {
                /* nothing known found in this header, go by default */
                policy = H2_PUSH_DEFAULT;
            }
        }
        else {
            policy = H2_PUSH_DEFAULT;
        }
    }
    req->push_policy = policy;
}