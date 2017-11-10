static void *merge_session_dbd_dir_config(apr_pool_t * p, void *basev, void *addv)
{
    session_dbd_dir_conf *new = (session_dbd_dir_conf *) apr_pcalloc(p, sizeof(session_dbd_dir_conf));
    session_dbd_dir_conf *add = (session_dbd_dir_conf *) addv;
    session_dbd_dir_conf *base = (session_dbd_dir_conf *) basev;

    new->name = (add->name_set == 0) ? base->name : add->name;
    new->name_attrs = (add->name_set == 0) ? base->name_attrs : add->name_attrs;
    new->name_set = add->name_set || base->name_set;
    new->name2 = (add->name2_set == 0) ? base->name2 : add->name2;
    new->name2_attrs = (add->name2_set == 0) ? base->name2_attrs : add->name2_attrs;
    new->name2_set = add->name2_set || base->name2_set;
    new->peruser = (add->peruser_set == 0) ? base->peruser : add->peruser;
    new->peruser_set = add->peruser_set || base->peruser_set;
    new->remove = (add->remove_set == 0) ? base->remove : add->remove;
    new->remove_set = add->remove_set || base->remove_set;
    new->selectlabel = (!add->selectlabel) ? base->selectlabel : add->selectlabel;
    new->updatelabel = (!add->updatelabel) ? base->updatelabel : add->updatelabel;
    new->insertlabel = (!add->insertlabel) ? base->insertlabel : add->insertlabel;
    new->deletelabel = (!add->deletelabel) ? base->deletelabel : add->deletelabel;

    return new;
}