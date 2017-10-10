#include "credential.h"
#include "string-list.h"
#include "parse-options.h"

static struct lock_file credential_lock;

static int parse_credential_file(const char *fn,
				  struct credential *c,
				  void (*match_cb)(struct credential *),
				  void (*other_cb)(struct strbuf *))
{
	FILE *fh;
	struct strbuf line = STRBUF_INIT;
	struct credential entry = CREDENTIAL_INIT;
	int found_credential = 0;

	fh = fopen(fn, "r");
	if (!fh) {
		if (errno != ENOENT && errno != EACCES)
			die_errno("unable to open %s", fn);
		return found_credential;
	}

	while (strbuf_getline(&line, fh, '\n') != EOF) {
		credential_from_url(&entry, line.buf);
		if (entry.username && entry.password &&
		    credential_match(c, &entry)) {
			found_credential = 1;
			if (match_cb) {
				match_cb(&entry);
				break;
			}
		}
		else if (other_cb)
			other_cb(&line);
	}

	credential_clear(&entry);
	strbuf_release(&line);
	fclose(fh);
	return found_credential;
}

static void print_entry(struct credential *c)
{
	printf("username=%s\n", c->username);
	printf("password=%s\n", c->password);
