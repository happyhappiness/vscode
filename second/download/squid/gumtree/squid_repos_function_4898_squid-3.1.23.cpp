AuthUser *
BasicUser::makeCachedFrom()
{
    /* the user doesn't exist in the username cache yet */
    debugs(29, 9, HERE << "Creating new user '" << username() << "'");
    BasicUser *basic_user = new BasicUser(&basicConfig);
    /* save the credentials */
    basic_user->username(username());
    username(NULL);
    basic_user->passwd = passwd;
    passwd = NULL;
    /* set the auth_user type */
    basic_user->auth_type = AUTH_BASIC;
    /* current time for timeouts */
    basic_user->expiretime = current_time.tv_sec;

    /* this basic_user struct is the 'lucky one' to get added to the username cache */
    /* the requests after this link to the basic_user */
    /* store user in hash */
    basic_user->addToNameCache();
    return basic_user;
}