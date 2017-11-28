    return message;
}

char const *
Auth::UserRequest::denyMessage(char const * const default_message)
{
    if (getDenyMessage() == NULL)
        return default_message;

    return getDenyMessage();
}

static void
authenticateAuthUserRequestSetIp(Auth::UserRequest::Pointer auth_user_request, Ip::Address &ipaddr)
