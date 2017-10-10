 #include "dir.h"
 #include "utf8.h"
 #include "submodule.h"
 #include "submodule-config.h"
 #include "string-list.h"
 #include "run-command.h"
+#include "remote.h"
+#include "refs.h"
+#include "connect.h"
+
+static char *get_default_remote(void)
+{
+	char *dest = NULL, *ret;
+	unsigned char sha1[20];
+	struct strbuf sb = STRBUF_INIT;
+	const char *refname = resolve_ref_unsafe("HEAD", 0, sha1, NULL);
+
+	if (!refname)
+		die(_("No such ref: %s"), "HEAD");
+
+	/* detached HEAD */
+	if (!strcmp(refname, "HEAD"))
+		return xstrdup("origin");
+
+	if (!skip_prefix(refname, "refs/heads/", &refname))
+		die(_("Expecting a full ref name, got %s"), refname);
+
+	strbuf_addf(&sb, "branch.%s.remote", refname);
+	if (git_config_get_string(sb.buf, &dest))
+		ret = xstrdup("origin");
+	else
+		ret = dest;
+
+	strbuf_release(&sb);
+	return ret;
+}
+
+static int starts_with_dot_slash(const char *str)
+{
+	return str[0] == '.' && is_dir_sep(str[1]);
+}
+
+static int starts_with_dot_dot_slash(const char *str)
+{
+	return str[0] == '.' && str[1] == '.' && is_dir_sep(str[2]);
+}
+
+/*
+ * Returns 1 if it was the last chop before ':'.
+ */
+static int chop_last_dir(char **remoteurl, int is_relative)
+{
+	char *rfind = find_last_dir_sep(*remoteurl);
+	if (rfind) {
+		*rfind = '\0';
+		return 0;
+	}
+
+	rfind = strrchr(*remoteurl, ':');
+	if (rfind) {
+		*rfind = '\0';
+		return 1;
+	}
+
+	if (is_relative || !strcmp(".", *remoteurl))
+		die(_("cannot strip one component off url '%s'"),
+			*remoteurl);
+
+	free(*remoteurl);
+	*remoteurl = xstrdup(".");
+	return 0;
+}
+
+/*
+ * The `url` argument is the URL that navigates to the submodule origin
+ * repo. When relative, this URL is relative to the superproject origin
+ * URL repo. The `up_path` argument, if specified, is the relative
+ * path that navigates from the submodule working tree to the superproject
+ * working tree. Returns the origin URL of the submodule.
+ *
+ * Return either an absolute URL or filesystem path (if the superproject
+ * origin URL is an absolute URL or filesystem path, respectively) or a
+ * relative file system path (if the superproject origin URL is a relative
+ * file system path).
+ *
+ * When the output is a relative file system path, the path is either
+ * relative to the submodule working tree, if up_path is specified, or to
+ * the superproject working tree otherwise.
+ *
+ * NEEDSWORK: This works incorrectly on the domain and protocol part.
+ * remote_url      url              outcome          expectation
+ * http://a.com/b  ../c             http://a.com/c   as is
+ * http://a.com/b  ../../c          http://c         error out
+ * http://a.com/b  ../../../c       http:/c          error out
+ * http://a.com/b  ../../../../c    http:c           error out
+ * http://a.com/b  ../../../../../c    .:c           error out
+ * NEEDSWORK: Given how chop_last_dir() works, this function is broken
+ * when a local part has a colon in its path component, too.
+ */
+static char *relative_url(const char *remote_url,
+				const char *url,
+				const char *up_path)
+{
+	int is_relative = 0;
+	int colonsep = 0;
+	char *out;
+	char *remoteurl = xstrdup(remote_url);
+	struct strbuf sb = STRBUF_INIT;
+	size_t len = strlen(remoteurl);
+
+	if (is_dir_sep(remoteurl[len]))
+		remoteurl[len] = '\0';
+
+	if (!url_is_local_not_ssh(remoteurl) || is_absolute_path(remoteurl))
+		is_relative = 0;
+	else {
+		is_relative = 1;
+		/*
+		 * Prepend a './' to ensure all relative
+		 * remoteurls start with './' or '../'
+		 */
+		if (!starts_with_dot_slash(remoteurl) &&
+		    !starts_with_dot_dot_slash(remoteurl)) {
+			strbuf_reset(&sb);
+			strbuf_addf(&sb, "./%s", remoteurl);
+			free(remoteurl);
+			remoteurl = strbuf_detach(&sb, NULL);
+		}
+	}
+	/*
+	 * When the url starts with '../', remove that and the
+	 * last directory in remoteurl.
+	 */
+	while (url) {
+		if (starts_with_dot_dot_slash(url)) {
+			url += 3;
+			colonsep |= chop_last_dir(&remoteurl, is_relative);
+		} else if (starts_with_dot_slash(url))
+			url += 2;
+		else
+			break;
+	}
+	strbuf_reset(&sb);
+	strbuf_addf(&sb, "%s%s%s", remoteurl, colonsep ? ":" : "/", url);
+	free(remoteurl);
+
+	if (starts_with_dot_slash(sb.buf))
+		out = xstrdup(sb.buf + 2);
+	else
+		out = xstrdup(sb.buf);
+	strbuf_reset(&sb);
+
+	if (!up_path || !is_relative)
+		return out;
+
+	strbuf_addf(&sb, "%s%s", up_path, out);
+	free(out);
+	return strbuf_detach(&sb, NULL);
+}
+
+static int resolve_relative_url(int argc, const char **argv, const char *prefix)
+{
+	char *remoteurl = NULL;
+	char *remote = get_default_remote();
+	const char *up_path = NULL;
+	char *res;
+	const char *url;
+	struct strbuf sb = STRBUF_INIT;
+
+	if (argc != 2 && argc != 3)
+		die("resolve-relative-url only accepts one or two arguments");
+
+	url = argv[1];
+	strbuf_addf(&sb, "remote.%s.url", remote);
+	free(remote);
+
+	if (git_config_get_string(sb.buf, &remoteurl))
+		/* the repository is its own authoritative upstream */
+		remoteurl = xgetcwd();
+
+	if (argc == 3)
+		up_path = argv[2];
+
+	res = relative_url(remoteurl, url, up_path);
+	puts(res);
+	free(res);
+	free(remoteurl);
+	return 0;
+}
+
+static int resolve_relative_url_test(int argc, const char **argv, const char *prefix)
+{
+	char *remoteurl, *res;
+	const char *up_path, *url;
+
+	if (argc != 4)
+		die("resolve-relative-url-test only accepts three arguments: <up_path> <remoteurl> <url>");
+
+	up_path = argv[1];
+	remoteurl = xstrdup(argv[2]);
+	url = argv[3];
+
+	if (!strcmp(up_path, "(null)"))
+		up_path = NULL;
+
+	res = relative_url(remoteurl, url, up_path);
+	puts(res);
+	free(res);
+	free(remoteurl);
+	return 0;
+}
 
 struct module_list {
 	const struct cache_entry **entries;
 	int alloc, nr;
 };
 #define MODULE_LIST_INIT { NULL, 0, 0 }
