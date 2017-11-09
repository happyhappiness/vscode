static void *create_session_dbd_dir_config(apr_pool_t * p, char *dummy)
{
    session_dbd_dir_conf *new =
    (session_dbd_dir_conf *) apr_pcalloc(p, sizeof(session_dbd_dir_conf));

    new->remove = 1;

    new->selectlabel = "selectsession";
    new->insertlabel = "insertsession";
    new->updatelabel = "updatesession";
    new->deletelabel = "deletesession";

    return (void *) new;
}