 	stop_progress(&progress_state);
 	if (written != nr_result)
 		die("wrote %"PRIu32" objects while expecting %"PRIu32,
 			written, nr_result);
 }
 
-static void setup_delta_attr_check(struct git_attr_check *check)
-{
-	static struct git_attr *attr_delta;
-
-	if (!attr_delta)
-		attr_delta = git_attr("delta");
-
-	check[0].attr = attr_delta;
-}
-
 static int no_try_delta(const char *path)
 {
-	struct git_attr_check check[1];
+	static struct attr_check *check;
 
-	setup_delta_attr_check(check);
-	if (git_check_attr(path, ARRAY_SIZE(check), check))
+	if (!check)
+		check = attr_check_initl("delta", NULL);
+	if (git_check_attr(path, check))
 		return 0;
-	if (ATTR_FALSE(check->value))
+	if (ATTR_FALSE(check->items[0].value))
 		return 1;
 	return 0;
 }
 
 /*
  * When adding an object, check whether we have already added it
