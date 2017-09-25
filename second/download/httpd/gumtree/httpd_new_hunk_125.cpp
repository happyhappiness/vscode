 * with a .htaccess file which turns FollowSymLinks back on --- and
 * access in such a case must be denied.  So, whatever it is that
 * checks FollowSymLinks needs to know the state of the options as
 * they change, all the way down.
 */


/*
 * resolve_symlink must _always_ be called on an APR_LNK file type!
 * It will resolve the actual target file type, modification date, etc,
 * and provide any processing required for symlink evaluation.
 * Path must already be cleaned, no trailing slash, no multi-slashes,
