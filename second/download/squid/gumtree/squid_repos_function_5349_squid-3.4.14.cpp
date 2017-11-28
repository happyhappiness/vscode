Auth::Direction
Auth::Ntlm::UserRequest::module_direction()
{
    /* null auth_user is checked for by Auth::UserRequest::direction() */

    if (waiting || client_blob)
        return Auth::CRED_LOOKUP; /* need helper response to continue */

    if (user()->auth_type != Auth::AUTH_NTLM)
        return Auth::CRED_ERROR;

    switch (user()->credentials()) {

    case Auth::Handshake:
        assert(server_blob);
        return Auth::CRED_CHALLENGE;

    case Auth::Ok:
        return Auth::CRED_VALID;

    case Auth::Failed:
        return Auth::CRED_ERROR; // XXX: really? not VALID or CHALLENGE?

    default:
        debugs(29, DBG_IMPORTANT, "WARNING: NTLM Authentication in unexpected state: " << user()->credentials());
        return Auth::CRED_ERROR;
    }
}