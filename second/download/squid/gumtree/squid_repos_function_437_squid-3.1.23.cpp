static void
my_free(void *p)
{
    user_data *u = p;
    xfree(u->hash.key);
    xfree(u->passwd);
    xfree(u);
}