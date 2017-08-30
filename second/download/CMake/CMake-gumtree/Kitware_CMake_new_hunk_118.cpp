    fprintf(stderr, "File is an executable.  I don't dump those.\n");

    return false;

  }

  /* Does it look like a COFF OBJ file??? */

  else if (((dosHeader->e_magic == IMAGE_FILE_MACHINE_I386) ||

            (dosHeader->e_magic == IMAGE_FILE_MACHINE_AMD64) ||

            (dosHeader->e_magic == IMAGE_FILE_MACHINE_ARMNT)) &&

           (dosHeader->e_sp == 0)) {

    /*

    * The two tests above aren't what they look like.  They're

