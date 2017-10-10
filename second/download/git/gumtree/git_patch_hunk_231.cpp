 			printf("option\n");
 			printf("push\n");
 			printf("check-connectivity\n");
 			printf("\n");
 			fflush(stdout);
 		} else {
-			fprintf(stderr, "Unknown command '%s'\n", buf.buf);
+			error("remote-curl: unknown command '%s' from git", buf.buf);
 			return 1;
 		}
 		strbuf_reset(&buf);
 	} while (1);
 
 	http_cleanup();
