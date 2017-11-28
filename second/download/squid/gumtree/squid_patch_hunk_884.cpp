                       (int) reply->date,
                       (int) reply->last_modified,
                       (int) reply->expires,
                       SQUIDSTRINGPRINT(ctype),
                       reply->content_length,
                       e->contentLen(),
-                      RequestMethodStr(mem->method),
-                      mem->log_url);
+                      SQUIDSBUFPRINT(mem->method.image()),
+                      mem->logUri());
         logfileLineEnd(storelog);
     } else {
         /* no mem object. Most RELEASE cases */
         logfileLineStart(storelog);
         logfilePrintf(storelog, "%9d.%03d %-7s %02d %08X %s   ?         ?         ?         ? ?/? ?/? ? ?\n",
                       (int) current_time.tv_sec,
