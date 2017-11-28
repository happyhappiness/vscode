static void
my_free(void *p)
{
    user_data *u = static_cast<user_data*>(p);
    xfree(u->user);
    xfree(u->passwd);
    xfree(u);
}