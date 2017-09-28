     /* Return early when the context has seen an error. */
     if (c->err)
         return REDIS_ERR;
 
     nread = read(c->fd,buf,sizeof(buf));
     if (nread == -1) {
-        if (errno == EAGAIN && !(c->flags & REDIS_BLOCK)) {
+        if ((errno == EAGAIN && !(c->flags & REDIS_BLOCK)) || (errno == EINTR)) {
             /* Try again later */
         } else {
             __redisSetError(c,REDIS_ERR_IO,NULL);
             return REDIS_ERR;
         }
     } else if (nread == 0) {
