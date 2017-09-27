 #endif
 
 #ifdef OS
     printf(" -D OS=\"" OS "\"\n");
 #endif
 
-#ifdef APACHE_MPM_DIR
-    printf(" -D APACHE_MPM_DIR=\"" APACHE_MPM_DIR "\"\n");
-#endif
-
 #ifdef HAVE_SHMGET
     printf(" -D HAVE_SHMGET\n");
 #endif
 
 #if APR_FILE_BASED_SHM
     printf(" -D APR_FILE_BASED_SHM\n");
