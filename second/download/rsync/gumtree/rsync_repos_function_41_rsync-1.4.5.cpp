int check_hard_link(struct file_struct *file)
{
#if SUPPORT_HARD_LINKS
  int low=0,high=hlink_count;
  int mid=0,ret=0;

  if (!hlink_list || !S_ISREG(file->mode)) return 0;

  while (low != high) {
    mid = (low+high)/2;
    ret = hlink_compare(&hlink_list[mid],file);
    if (ret == 0) break;
    if (ret > 0) 
      high=mid;
    else
      low=mid+1;
  }

  if (hlink_compare(&hlink_list[mid],file) != 0) return 0;

  if (mid > 0 &&
      S_ISREG(hlink_list[mid-1].mode) &&
      file->dev == hlink_list[mid-1].dev &&
      file->inode == hlink_list[mid-1].inode)
    return 1;
#endif

  return 0;
}