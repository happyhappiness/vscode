                     prev_addr = aiptr;
                 }
 
                 /* annoying inet_ntop breaks the nice code by requiring the in*_addr */
                 switch (aiptr->ai_family) {
                 case AF_INET:
-                    xinet_ntop(aiptr->ai_family, &((struct sockaddr_in*)aiptr->ai_addr)->sin_addr, ntoabuf, sizeof(ntoabuf));
+                    inet_ntop(aiptr->ai_family, &((struct sockaddr_in*)aiptr->ai_addr)->sin_addr, ntoabuf, sizeof(ntoabuf));
                     break;
                 case AF_INET6:
-                    xinet_ntop(aiptr->ai_family, &((struct sockaddr_in6*)aiptr->ai_addr)->sin6_addr, ntoabuf, sizeof(ntoabuf));
+                    inet_ntop(aiptr->ai_family, &((struct sockaddr_in6*)aiptr->ai_addr)->sin6_addr, ntoabuf, sizeof(ntoabuf));
                     break;
                 default:
                     aiptr = aiptr->ai_next;
                     continue;
                 }
                 printf(" %s", ntoabuf);
-                i++;
+                ++i;
                 aiptr = aiptr->ai_next;
             }
 
             prev_addr=NULL;
             printf("\n");
         }
