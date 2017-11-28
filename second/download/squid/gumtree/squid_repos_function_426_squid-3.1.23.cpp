static void
my_free(void *p)
{
    user_data *u = p;
    xfree(u->user);
    xfree(u->passwd);
    xfree(u);
}