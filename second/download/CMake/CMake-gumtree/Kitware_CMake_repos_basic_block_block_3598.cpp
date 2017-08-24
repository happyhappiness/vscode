{
      /* O_NONBLOCK source test */
      int flags = 0;
      if(0 != fcntl(0, F_SETFL, flags | O_NONBLOCK))
          return 1;
      return 0;
}