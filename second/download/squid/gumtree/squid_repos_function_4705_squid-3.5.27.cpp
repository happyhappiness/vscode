bool
ACLUserData::match(char const *user)
{
    debugs(28, 7, "user is " << user << ", case_insensitive is " << flags.case_insensitive);

    if (user == NULL || strcmp(user, "-") == 0)
        return 0;

    if (flags.required) {
        debugs(28, 7, "aclMatchUser: user REQUIRED and auth-info present.");
        return 1;
    }

    bool result = (userDataNames.find(SBuf(user)) != userDataNames.end());
    debugs(28, 7, "returning " << result);
    return result;
}