 				size_t outsz = prec_dir->dirent_nfc->max_name_len;
 				errno = 0;
 				iconv(prec_dir->ic_precompose, &cp, &inleft, &outpos, &outsz);
 				if (errno || inleft) {
 					/*
 					 * iconv() failed and errno could be E2BIG, EILSEQ, EINVAL, EBADF
-					 * MacOS X avoids illegal byte sequemces.
+					 * MacOS X avoids illegal byte sequences.
 					 * If they occur on a mounted drive (e.g. NFS) it is not worth to
 					 * die() for that, but rather let the user see the original name
 					*/
 					namelenz = 0; /* trigger strlcpy */
 				}
 			}
