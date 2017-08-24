{
    next = curr->next;
    if(!curr->expires) {
      if(first == curr)
        first = next;

      if(prev == curr)
        prev = next;
      else
        prev->next = next;

      freecookie(curr);
      cookies->numcookies--;
    }
    else
      prev = curr;
  }