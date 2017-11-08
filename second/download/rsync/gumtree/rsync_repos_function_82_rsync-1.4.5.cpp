int flist_find(struct file_list *flist,struct file_struct *f)
{
  int low=0,high=flist->count;

  while (low != high) {
    int mid = (low+high)/2;
    int ret = file_compare(&flist->files[mid],f);
    if (ret == 0) return mid;
    if (ret > 0) 
      high=mid;
    else
      low=mid+1;
  }
  if (file_compare(&flist->files[low],f) == 0)
    return low;
  return -1;
}