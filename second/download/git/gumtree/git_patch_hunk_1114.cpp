 
 	if (rule & WS_TAB_IN_INDENT && rule & WS_INDENT_WITH_NON_TAB)
 		die("cannot enforce both tab-in-indent and indent-with-non-tab");
 	return rule;
 }
 
-static void setup_whitespace_attr_check(struct git_attr_check *check)
-{
-	static struct git_attr *attr_whitespace;
-
-	if (!attr_whitespace)
-		attr_whitespace = git_attr("whitespace");
-	check[0].attr = attr_whitespace;
-}
-
 unsigned whitespace_rule(const char *pathname)
 {
-	struct git_attr_check attr_whitespace_rule;
+	static struct attr_check *attr_whitespace_rule;
+
+	if (!attr_whitespace_rule)
+		attr_whitespace_rule = attr_check_initl("whitespace", NULL);
 
-	setup_whitespace_attr_check(&attr_whitespace_rule);
-	if (!git_check_attr(pathname, 1, &attr_whitespace_rule)) {
+	if (!git_check_attr(pathname, attr_whitespace_rule)) {
 		const char *value;
 
-		value = attr_whitespace_rule.value;
+		value = attr_whitespace_rule->items[0].value;
 		if (ATTR_TRUE(value)) {
 			/* true (whitespace) */
 			unsigned all_rule = ws_tab_width(whitespace_rule_cfg);
 			int i;
 			for (i = 0; i < ARRAY_SIZE(whitespace_rule_names); i++)
 				if (!whitespace_rule_names[i].loosens_error &&
