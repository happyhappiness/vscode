void
clean_args(struct main_args *margs)
{
    safe_free(margs->glist);
    safe_free(margs->ulist);
    safe_free(margs->tlist);
    safe_free(margs->nlist);
    safe_free(margs->llist);
    safe_free(margs->luser);
    safe_free(margs->lpass);
    safe_free(margs->lbind);
    safe_free(margs->lurl);
    safe_free(margs->ssl);
    safe_free(margs->ddomain);
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