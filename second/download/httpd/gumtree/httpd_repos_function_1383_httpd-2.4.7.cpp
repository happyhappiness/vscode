static void close_disk_cache_fd(disk_cache_file_t *file)
{
   if (file->fd != NULL) {
       apr_file_close(file->fd);
       file->fd = NULL;
   }
   if (file->tempfd != NULL) {
       apr_file_close(file->tempfd);
       file->tempfd = NULL;
   }
}