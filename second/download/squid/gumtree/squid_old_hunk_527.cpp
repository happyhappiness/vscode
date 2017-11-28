
void
Auth::UserRequest::addAuthenticationInfoTrailer(HttpReply * rep, int accelerated)
{}

void
Auth::UserRequest::onConnectionClose(ConnStateData *)
{}

const char *
Auth::UserRequest::connLastHeader()
{
    fatal("Auth::UserRequest::connLastHeader should always be overridden by conn based auth schemes");
