 
 	if (fd < 0 && (oflags & O_ACCMODE) != O_RDONLY && errno == EACCES) {
 		DWORD attrs = GetFileAttributesW(wfilename);
 		if (attrs != INVALID_FILE_ATTRIBUTES && (attrs & FILE_ATTRIBUTE_DIRECTORY))
 			errno = EISDIR;
 	}
+	if ((oflags & O_CREAT) && needs_hiding(filename)) {
+		/*
+		 * Internally, _wopen() uses the CreateFile() API which errors
+		 * out with an ERROR_ACCESS_DENIED if CREATE_ALWAYS was
+		 * specified and an already existing file's attributes do not
+		 * match *exactly*. As there is no mode or flag we can set that
+		 * would correspond to FILE_ATTRIBUTE_HIDDEN, let's just try
+		 * again *without* the O_CREAT flag (that corresponds to the
+		 * CREATE_ALWAYS flag of CreateFile()).
+		 */
+		if (fd < 0 && errno == EACCES)
+			fd = _wopen(wfilename, oflags & ~O_CREAT, mode);
+		if (fd >= 0 && set_hidden_flag(wfilename, 1))
+			warning("could not mark '%s' as hidden.", filename);
+	}
 	return fd;
 }
 
 static BOOL WINAPI ctrl_ignore(DWORD type)
 {
 	return TRUE;
