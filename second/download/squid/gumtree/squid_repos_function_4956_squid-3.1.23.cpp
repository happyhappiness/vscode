int
AuthDigestUserRequest::module_direction()
{
    switch (credentials()) {

    case Unchecked:
        return -1;

    case Ok:

        return 0;

    case Pending:
        return -1;

    case Failed:

        /* send new challenge */
        return 1;
    }

    return -2;
}