static void free_disk(disk_t *disk) /* {{{ */
{
  disk_t *next;

  if (disk == NULL)
    return;

  next = disk->next;

  sfree(disk->name);
  sfree(disk);

  free_disk(next);
}