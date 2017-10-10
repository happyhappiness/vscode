 	"Note: checking out '%s'.\n\n"
 	"You are in 'detached HEAD' state. You can look around, make experimental\n"
 	"changes and commit them, and you can discard any commits you make in this\n"
 	"state without impacting any branches by performing another checkout.\n\n"
 	"If you want to create a new branch to retain commits you create, you may\n"
 	"do so (now or later) by using -b with the checkout command again. Example:\n\n"
-	"  git checkout -b new_branch_name\n\n";
+	"  git checkout -b <new-branch-name>\n\n";
 
 	fprintf(stderr, fmt, new_name);
 }
