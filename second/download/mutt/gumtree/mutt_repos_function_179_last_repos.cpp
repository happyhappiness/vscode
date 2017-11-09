static int mutt_put_file_in_place (const char *path, const char *safe_file, const char *safe_dir)
{
  int rv;
  
  rv = safe_rename (safe_file, path);
  unlink (safe_file);
  rmdir (safe_dir);
  return rv;
}