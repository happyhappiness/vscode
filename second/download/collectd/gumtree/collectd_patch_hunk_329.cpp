 
 	IPT_MATCH_ITERATE(e, print_match);
 
 	t = GET_TARGET(e);
 	printf("Target name: `%s' [%u]\n", t->u.user.name, t->u.target_size);
 	if (strcmp(t->u.user.name, STANDARD_TARGET) == 0) {
-		int pos = *(int *)t->data;
+		const unsigned char *data = t->data;
+		int pos = *(const int *)data;
 		if (pos < 0)
 			printf("verdict=%s\n",
 			       pos == -NF_ACCEPT-1 ? "NF_ACCEPT"
 			       : pos == -NF_DROP-1 ? "NF_DROP"
 			       : pos == -NF_QUEUE-1 ? "NF_QUEUE"
 			       : pos == RETURN ? "RETURN"
