void
init_args(struct main_args *margs)
{
    margs->nlist = NULL;
    margs->glist = NULL;
    margs->llist = NULL;
    margs->ulist = NULL;
    margs->tlist = NULL;
    margs->luser = NULL;
    margs->lpass = NULL;
    margs->lbind = NULL;
    margs->lurl = NULL;
    margs->ssl = NULL;
    margs->rc_allow = 0;
    margs->AD = 0;
    margs->mdepth = 5;
    margs->nokerberos = 0;
    margs->ddomain = NULL;
    margs->groups = NULL;
    margs->ndoms = NULL;
    margs->lservs = NULL;
}