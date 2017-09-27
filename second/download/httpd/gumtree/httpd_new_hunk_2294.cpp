    return AUTHZ_DENIED;
}

static authz_status validuser_check_authorization(request_rec *r, const char *require_line)
{
    if (!r->user) {
        return AUTHZ_DENIED_NO_USER;
    }

    return AUTHZ_GRANTED;
}

static const authz_provider authz_user_provider =
