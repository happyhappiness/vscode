  printf("th_set_device(): major = %d, minor = %d\n",

         major(device), minor(device));

#endif

  int_to_oct(major(device), t->th_buf.devmajor, 8);

  int_to_oct(minor(device), t->th_buf.devminor, 8);

}

