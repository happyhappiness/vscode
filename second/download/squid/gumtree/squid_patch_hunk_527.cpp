 
 void
 Auth::UserRequest::addAuthenticationInfoTrailer(HttpReply * rep, int accelerated)
 {}
 
 void
-Auth::UserRequest::onConnectionClose(ConnStateData *)
+Auth::UserRequest::releaseAuthServer()
 {}
 
 const char *
 Auth::UserRequest::connLastHeader()
 {
     fatal("Auth::UserRequest::connLastHeader should always be overridden by conn based auth schemes");
