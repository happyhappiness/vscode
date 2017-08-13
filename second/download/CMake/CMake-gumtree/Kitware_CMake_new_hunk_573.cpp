
   dosHeader = (PIMAGE_DOS_HEADER)lpFileBase;
   if (dosHeader->e_magic == IMAGE_DOS_SIGNATURE) {
      fprintf(stderr, "File is an executable.  I don't dump those.\n");
      return;
   }
   /* Does it look like a i386 COFF OBJ file??? */
   else if (
