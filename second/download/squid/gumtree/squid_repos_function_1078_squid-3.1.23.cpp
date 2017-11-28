static void
free_cachemgrpasswd(cachemgr_passwd ** head)
{
    cachemgr_passwd *p;

    while ((p = *head) != NULL) {
        *head = p->next;
        xfree(p->passwd);
        wordlistDestroy(&p->actions);
        xfree(p);
    }
}