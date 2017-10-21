 				out_of_memory("rsync_xal_get");
 			*ptr = XSTATE_ABBREV;
 			sum_end(ptr + 1);
 		} else
 			name_offset = datum_len;
 
-#ifdef HAVE_LINUX_XATTRS
-		if (am_root < 0 && name_len > RPRE_LEN && name[RPRE_LEN] != '%'
-		 && HAS_PREFIX(name, RSYNC_PREFIX)) {
-			name += RPRE_LEN;
-			name_len -= RPRE_LEN;
-		}
-#endif
-
 		rxa = EXPAND_ITEM_LIST(xalp, rsync_xa, RSYNC_XAL_INITIAL);
 		rxa->name = ptr + name_offset;
 		memcpy(rxa->name, name, name_len);
 		rxa->datum = ptr;
 		rxa->name_len = name_len;
 		rxa->datum_len = datum_len;
