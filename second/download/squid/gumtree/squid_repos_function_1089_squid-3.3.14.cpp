static void
free_cachemgrpasswd(Mgr::ActionPasswordList ** head)
{
    Mgr::ActionPasswordList *p;

    while ((p = *head) != NULL) {
        *head = p->next;
        xfree(p->passwd);
        wordlistDestroy(&p->actions);
        xfree(p);
    }
}