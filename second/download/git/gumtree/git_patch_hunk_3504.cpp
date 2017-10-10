  */
 extern ssize_t strbuf_read_once(struct strbuf *, int fd, size_t hint);
 
 /**
  * Read the contents of a file, specified by its path. The third argument
  * can be used to give a hint about the file size, to avoid reallocs.
+ * Return the number of bytes read or a negative value if some error
+ * occurred while opening or reading the file.
  */
 extern ssize_t strbuf_read_file(struct strbuf *sb, const char *path, size_t hint);
 
 /**
  * Read the target of a symbolic link, specified by its path.  The third
  * argument can be used to give a hint about the size, to avoid reallocs.
