 #include "../git-compat-util.h"
 
 void *git_mmap(void *start, size_t length, int prot, int flags, int fd, off_t offset)
 {
-	HANDLE hmap;
+	HANDLE osfhandle, hmap;
 	void *temp;
-	off_t len;
-	struct stat st;
+	LARGE_INTEGER len;
 	uint64_t o = offset;
 	uint32_t l = o & 0xFFFFFFFF;
 	uint32_t h = (o >> 32) & 0xFFFFFFFF;
 
-	if (!fstat(fd, &st))
-		len = st.st_size;
-	else
+	osfhandle = (HANDLE)_get_osfhandle(fd);
+	if (!GetFileSizeEx(osfhandle, &len))
 		die("mmap: could not determine filesize");
 
-	if ((length + offset) > len)
-		length = xsize_t(len - offset);
+	if ((length + offset) > len.QuadPart)
+		length = xsize_t(len.QuadPart - offset);
 
 	if (!(flags & MAP_PRIVATE))
 		die("Invalid usage of mmap when built with USE_WIN32_MMAP");
 
-	hmap = CreateFileMapping((HANDLE)_get_osfhandle(fd), NULL,
-		PAGE_WRITECOPY, 0, 0, NULL);
+	hmap = CreateFileMapping(osfhandle, NULL,
+		prot == PROT_READ ? PAGE_READONLY : PAGE_WRITECOPY, 0, 0, NULL);
 
-	if (!hmap)
+	if (!hmap) {
+		errno = EINVAL;
 		return MAP_FAILED;
+	}
 
-	temp = MapViewOfFileEx(hmap, FILE_MAP_COPY, h, l, length, start);
+	temp = MapViewOfFileEx(hmap, prot == PROT_READ ?
+			FILE_MAP_READ : FILE_MAP_COPY, h, l, length, start);
 
 	if (!CloseHandle(hmap))
 		warning("unable to close file mapping handle");
 
-	return temp ? temp : MAP_FAILED;
+	if (temp)
+		return temp;
+
+	errno = GetLastError() == ERROR_COMMITMENT_LIMIT ? EFBIG : EINVAL;
+	return MAP_FAILED;
 }
 
 int git_munmap(void *start, size_t length)
 {
 	return !UnmapViewOfFile(start);
 }
