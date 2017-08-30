

  md5this = (unsigned char *) aprintf("%s:%s", request, uripath);



  if(digest->qop && strcasecompare(digest->qop, "auth-int")) {

    /* We don't support auth-int for PUT or POST at the moment.

       TODO: replace md5 of empty string with entity-body for PUT/POST */

    unsigned char *md5this2 = (unsigned char *)

