{
    nx = co->next;
    if(co->expires && co->expires < now) {
      if(co == cookies->cookies) {
        cookies->cookies = co->next;
      }
      else {
        pv->next = co->next;
      }
      cookies->numcookies--;
      freecookie(co);
    }
    else {
      pv = co;
    }
    co = nx;
  }