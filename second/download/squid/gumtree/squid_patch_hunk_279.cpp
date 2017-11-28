                       (int) reply->expires,
                       SQUIDSTRINGPRINT(ctype),
                       reply->content_length,
                       e->contentLen(),
                       RequestMethodStr(mem->method),
                       mem->log_url);
+        logfileLineEnd(storelog);
     } else {
         /* no mem object. Most RELEASE cases */
+        logfileLineStart(storelog);
         logfilePrintf(storelog, "%9d.%03d %-7s %02d %08X %s   ?         ?         ?         ? ?/? ?/? ? ?\n",
                       (int) current_time.tv_sec,
                       (int) current_time.tv_usec / 1000,
                       storeLogTags[tag],
                       e->swap_dirn,
                       e->swap_filen,
                       e->getMD5Text());
+        logfileLineEnd(storelog);
     }
 }
 
 void
 storeLogRotate(void)
 {
