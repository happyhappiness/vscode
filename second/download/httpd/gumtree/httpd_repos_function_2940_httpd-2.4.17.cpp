static void *merge_session_cookie_dir_config(apr_pool_t * p, void *basev,
                                             void *addv)
{
    session_cookie_dir_conf *new = (session_cookie_dir_conf *)
                                apr_pcalloc(p, sizeof(session_cookie_dir_conf));
    session_cookie_dir_conf *add = (session_cookie_dir_conf *) addv;
    session_cookie_dir_conf *base = (session_cookie_dir_conf *) basev;

    new->name = (add->name_set == 0) ? base->name : add->name;
    new->name_attrs = (add->name_set == 0) ? base->name_attrs : add->name_attrs;
    new->name_set = add->name_set || base->name_set;
    new->name2 = (add->name2_set == 0) ? base->name2 : add->name2;
    new->name2_attrs = (add->name2_set == 0) ? base->name2_attrs : add->name2_attrs;
    new->name2_set = add->name2_set || base->name2_set;
    new->remove = (add->remove_set == 0) ? base->remove : add->remove;
    new->remove_set = add->remove_set || base->remove_set;

    return new;
}