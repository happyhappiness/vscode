static int authorize_userless(request_rec *r)
{
    return authorize_user_core(r, 0);
}