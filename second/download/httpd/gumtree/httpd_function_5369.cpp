static int get_form_auth(request_rec * r,
                             const char *username,
                             const char *password,
                             const char *location,
                             const char *method,
                             const char *mimetype,
                             const char *body,
                             const char **sent_user,
                             const char **sent_pw,
                             const char **sent_loc,
                             const char **sent_method,
                             const char **sent_mimetype,
                             apr_bucket_brigade **sent_body,
                             auth_form_config_rec * conf)
{
    /* sanity check - are we a POST request? */

    /* find the username and password in the form */
    apr_array_header_t *pairs = NULL;
    apr_off_t len;
    apr_size_t size;
    int res;
    char *buffer;

    /* have we isolated the user and pw before? */
    get_notes_auth(r, sent_user, sent_pw, sent_method, sent_mimetype);
    if (*sent_user && *sent_pw) {
        return OK;
    }

    res = ap_parse_form_data(r, NULL, &pairs, -1, conf->form_size);
    if (res != OK) {
        return res;
    }
    while (pairs && !apr_is_empty_array(pairs)) {
        ap_form_pair_t *pair = (ap_form_pair_t *) apr_array_pop(pairs);
        if (username && !strcmp(pair->name, username) && sent_user) {
            apr_brigade_length(pair->value, 1, &len);
            size = (apr_size_t) len;
            buffer = apr_palloc(r->pool, size + 1);
            apr_brigade_flatten(pair->value, buffer, &size);
            buffer[len] = 0;
            *sent_user = buffer;
        }
        else if (password && !strcmp(pair->name, password) && sent_pw) {
            apr_brigade_length(pair->value, 1, &len);
            size = (apr_size_t) len;
            buffer = apr_palloc(r->pool, size + 1);
            apr_brigade_flatten(pair->value, buffer, &size);
            buffer[len] = 0;
            *sent_pw = buffer;
        }
        else if (location && !strcmp(pair->name, location) && sent_loc) {
            apr_brigade_length(pair->value, 1, &len);
            size = (apr_size_t) len;
            buffer = apr_palloc(r->pool, size + 1);
            apr_brigade_flatten(pair->value, buffer, &size);
            buffer[len] = 0;
            *sent_loc = buffer;
        }
        else if (method && !strcmp(pair->name, method) && sent_method) {
            apr_brigade_length(pair->value, 1, &len);
            size = (apr_size_t) len;
            buffer = apr_palloc(r->pool, size + 1);
            apr_brigade_flatten(pair->value, buffer, &size);
            buffer[len] = 0;
            *sent_method = buffer;
        }
        else if (mimetype && !strcmp(pair->name, mimetype) && sent_mimetype) {
            apr_brigade_length(pair->value, 1, &len);
            size = (apr_size_t) len;
            buffer = apr_palloc(r->pool, size + 1);
            apr_brigade_flatten(pair->value, buffer, &size);
            buffer[len] = 0;
            *sent_mimetype = buffer;
        }
        else if (body && !strcmp(pair->name, body) && sent_body) {
            *sent_body = pair->value;
        }
    }

    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r,
                  "from form: user: %s, pw: %s, method: %s, mimetype: %s, location: %s",
                  sent_user ? *sent_user : "<null>", sent_pw ? *sent_pw : "<null>",
                  sent_method ? *sent_method : "<null>",
                  sent_mimetype ? *sent_mimetype : "<null>",
                  sent_loc ? *sent_loc : "<null>");

    /* set the user, even though the user is unauthenticated at this point */
    if (sent_user && *sent_user) {
        r->user = (char *) *sent_user;
    }

    /* a missing username or missing password means auth denied */
    if (!sent_user || !*sent_user) {

        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "form parsed, but username field '%s' was missing or empty, unauthorized",
                      username);

        return HTTP_UNAUTHORIZED;
    }
    if (!sent_pw || !*sent_pw) {

        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                      "form parsed, but password field '%s' was missing or empty, unauthorized",
                      password);

        return HTTP_UNAUTHORIZED;
    }

    /*
     * save away the username, password, mimetype and method, so that they
     * are available should the auth need to be run again.
     */
    set_notes_auth(r, *sent_user, *sent_pw, sent_method ? *sent_method : NULL,
                   sent_mimetype ? *sent_mimetype : NULL);

    return OK;
}