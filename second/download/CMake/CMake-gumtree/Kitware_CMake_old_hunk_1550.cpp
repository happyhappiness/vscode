  printf("th_set_device(): major = %d, minor = %d\n",

         major(device), minor(device));

#endif

#ifndef major

# define major(dev) ((int)(((dev) >> 8) & 0xff))

#endif

#ifndef minor

# define minor(dev) ((int)((dev) & 0xff))

#endif

  int_to_oct(major(device), t->th_buf.devmajor, 8);

  int_to_oct(minor(device), t->th_buf.devminor, 8);

}

