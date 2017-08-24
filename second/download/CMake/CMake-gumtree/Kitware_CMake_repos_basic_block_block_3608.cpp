{

        int flags = 0;
        if(0 != ioctl(0, FIONBIO, &flags))
          return 1;

  ;
  return 0;
}