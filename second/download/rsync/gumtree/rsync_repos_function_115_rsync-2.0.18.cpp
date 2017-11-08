int check_hard_link(struct file_struct *file)
{
#if SUPPORT_HARD_LINKS
  int low=0,high=hlink_count-1;
  int ret=0;

  if (!hlink_list || !S_ISREG(file->mode)) return 0;

  while (low != high) {
    int mid = (low+high)/2;
    ret = hlink_compare(&hlink_list[mid],file);
    if (ret == 0) {
	    low = mid;
	    break;
    }
    if (ret > 0) 
      high=mid;
    else
      low=mid+1;
  }

  if (hlink_compare(&hlink_list[low],file) != 0) return 0;

  if (low > 0 &&
      S_ISREG(hlink_list[low-1].mode) &&
      file->dev == hlink_list[low-1].dev &&
      file->inode == hlink_list[low-1].inode)
    return 1;
#endif

  return 0;
}