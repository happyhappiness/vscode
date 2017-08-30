}

#endif



#if ARCHIVE_XATTR_LINUX || ARCHIVE_XATTR_DARWIN || ARCHIVE_XATTR_AIX



/*

 * Linux, Darwin and AIX extended attribute support.

 *

 * TODO:  By using a stack-allocated buffer for the first

 * call to getxattr(), we might be able to avoid the second

