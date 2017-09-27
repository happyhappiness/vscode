 	 */
 	if (l == c->rwrite)
 	    break;
 
 #ifdef USE_SSL
         if (ssl != 1)
+#endif
 	if (e != APR_SUCCESS) {
 	    /*
 	     * Let's hope this traps EWOULDBLOCK too !
 	     */
 	    if (!APR_STATUS_IS_EAGAIN(e)) {
 		epipe++;
 		printf("Send request failed!\n");
 		close_connection(c);
 	    }
 	    return;
 	}
-#endif
 	c->rwrote += l;
 	c->rwrite -= l;
     } while (1);
 
     totalposted += c->rwrite;
     c->state = STATE_READ;
