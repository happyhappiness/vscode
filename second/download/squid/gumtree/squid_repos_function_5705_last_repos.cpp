void
Auth::UserRequest::operator delete (void *)
{
    fatal("Auth::UserRequest child failed to override operator delete\n");
}