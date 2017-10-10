 					break;
 				if (!isspace(ch))
 				    comment_end = i;
 			}
 			if (comment_end)
 				printf("%s%s %s%s", c_reset,
-						    c_plain, c_reset,
+						    c_context, c_reset,
 						    c_func);
 			for (i = 0; i < comment_end; i++)
 				putchar(hunk_comment[i]);
 		}
 
 		printf("%s\n", c_reset);
