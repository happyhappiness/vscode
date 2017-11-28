    /* finally return ok */
    debugs(29, 5, HERE << "Validated. Auth::UserRequest '" << this << "'.");
    return true;
}

void *
Auth::UserRequest::operator new (size_t)
{
    fatal("Auth::UserRequest not directly allocatable\n");
    return (void *)1;
}

void
Auth::UserRequest::operator delete (void *)
{
    fatal("Auth::UserRequest child failed to override operator delete\n");
}

Auth::UserRequest::UserRequest():
    _auth_user(NULL),
