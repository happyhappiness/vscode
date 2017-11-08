static int authorize_user(request_rec *r)
{
    return authorize_user_core(r, 1);
}