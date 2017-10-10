 	walker_free(walker);
 
 	for (i = 0; i < nr_heads; i++)
 		free(targets[i]);
 	free(targets);
 
-	return ret ? error("Fetch failed.") : 0;
+	return ret ? error("fetch failed.") : 0;
 }
 
 static int fetch_git(struct discovery *heads,
 	int nr_heads, struct ref **to_fetch)
 {
 	struct rpc_state rpc;
