int 
compare_stat (struct stat *osb, struct stat *nsb)
{
  if (osb->st_dev != nsb->st_dev || osb->st_ino != nsb->st_ino ||
      osb->st_rdev != nsb->st_rdev)
  {
    return -1;
  }

  return 0;
}