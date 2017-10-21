 	       (long) buf.st_uid, (long) buf.st_gid,
 	       buf.st_nlink,
 	       datebuf, fname, linkbuf);
 }
 
 
-int main (int argc, char *argv[])
+int
+main(int argc, char *argv[])
 {
 	if (argc < 2) {
 		fprintf (stderr, "usage: " PROGRAM " DIR ...\n"
 			 "Trivial file listing program for portably checking rsync\n");
 		return 1;
 	}
