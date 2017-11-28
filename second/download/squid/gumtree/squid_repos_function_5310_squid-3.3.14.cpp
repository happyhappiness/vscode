Auth::Direction
Auth::Digest::UserRequest::module_direction()
{
    if (user()->auth_type != Auth::AUTH_DIGEST)
        return Auth::CRED_ERROR;

    switch (user()->credentials()) {

    case Auth::Ok:
        return Auth::CRED_VALID;

    case Auth::Failed:
        /* send new challenge */
        return Auth::CRED_CHALLENGE;

    case Auth::Unchecked:
    case Auth::Pending:
        return Auth::CRED_LOOKUP;

    default:
        return Auth::CRED_ERROR;
    }
}