@@ -157,12 +157,6 @@ th_set_device(TAR *t, dev_t device)
   printf("th_set_device(): major = %d, minor = %d\n",
          major(device), minor(device));
 #endif
-#ifndef major
-# define major(dev) ((int)(((dev) >> 8) & 0xff))
-#endif
-#ifndef minor
-# define minor(dev) ((int)((dev) & 0xff))
-#endif
   int_to_oct(major(device), t->th_buf.devmajor, 8);
   int_to_oct(minor(device), t->th_buf.devminor, 8);
 }
@@ -209,7 +203,8 @@ th_set_mode(TAR *t, mode_t fmode)
     fmode |= S_IFIFO;
   }
 #endif
-  int_to_oct(fmode, (t)->th_buf.mode, 8);
+  /* Looks like on windows the st_mode is longer than 8 characters. */
+  int_to_oct(fmode & 07777777, (t)->th_buf.mode, 8);
 }
 
 