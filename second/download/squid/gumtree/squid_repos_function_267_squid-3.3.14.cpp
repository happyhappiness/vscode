void
clean_args(struct main_args *margs)
{
    if (margs->glist) {
        xfree(margs->glist);
        margs->glist = NULL;
    }
    if (margs->ulist) {
        xfree(margs->ulist);
        margs->ulist = NULL;
    }
    if (margs->tlist) {
        xfree(margs->tlist);
        margs->tlist = NULL;
    }
    if (margs->nlist) {
        xfree(margs->nlist);
        margs->nlist = NULL;
    }
    if (margs->llist) {
        xfree(margs->llist);
        margs->llist = NULL;
    }
    if (margs->luser) {
        xfree(margs->luser);
        margs->luser = NULL;
    }
    if (margs->lpass) {
        xfree(margs->lpass);
        margs->lpass = NULL;
    }
    if (margs->lbind) {
        xfree(margs->lbind);
        margs->lbind = NULL;
    }
    if (margs->lurl) {
        xfree(margs->lurl);
        margs->lurl = NULL;
    }
    if (margs->ssl) {
        xfree(margs->ssl);
        margs->ssl = NULL;
    }
    if (margs->ddomain) {
        xfree(margs->ddomain);
        margs->ddomain = NULL;
    }
    if (margs->groups) {
        clean_gd(margs->groups);
        margs->groups = NULL;
    }
    if (margs->ndoms) {
        clean_nd(margs->ndoms);
        margs->ndoms = NULL;
    }
    if (margs->lservs) {
        clean_ls(margs->lservs);
        margs->lservs = NULL;
    }
}