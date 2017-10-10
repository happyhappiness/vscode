 		return fdi;
 	if ((fdo = open(dst, O_WRONLY | O_CREAT | O_EXCL, mode)) < 0) {
 		close(fdi);
 		return fdo;
 	}
 	status = copy_fd(fdi, fdo);
+	close(fdi);
 	if (close(fdo) != 0)
 		return error("%s: close error: %s", dst, strerror(errno));
 
 	if (!status && adjust_shared_perm(dst))
 		return -1;
 
