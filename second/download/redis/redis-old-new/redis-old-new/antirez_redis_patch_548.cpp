@@ -295,7 +295,7 @@ static int anetTcpGenericConnect(char *err, char *addr, int port,
             if ((rv = getaddrinfo(source_addr, NULL, &hints, &bservinfo)) != 0)
             {
                 anetSetError(err, "%s", gai_strerror(rv));
-                goto end;
+                goto error;
             }
             for (b = bservinfo; b != NULL; b = b->ai_next) {
                 if (bind(s,b->ai_addr,b->ai_addrlen) != -1) {
@@ -306,7 +306,7 @@ static int anetTcpGenericConnect(char *err, char *addr, int port,
             freeaddrinfo(bservinfo);
             if (!bound) {
                 anetSetError(err, "bind: %s", strerror(errno));
-                goto end;
+                goto error;
             }
         }
         if (connect(s,p->ai_addr,p->ai_addrlen) == -1) {