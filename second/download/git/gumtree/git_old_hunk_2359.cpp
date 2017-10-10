#include "credential.h"
#include "string-list.h"
#include "parse-options.h"

static struct lock_file credential_lock;

static void parse_credential_file(const char *fn,
				  struct credential *c,
				  void (*match_cb)(struct credential *),
				  void (*other_cb)(struct strbuf *))
{
	FILE *fh;
	struct strbuf line = STRBUF_INIT;
	struct credential entry = CREDENTIAL_INIT;

	fh = fopen(fn, "r");
	if (!fh) {
		if (errno != ENOENT)
			die_errno("unable to open %s", fn);
		return;
	}

	while (strbuf_getline(&line, fh, '\n') != EOF) {
		credential_from_url(&entry, line.buf);
		if (entry.username && entry.password &&
		    credential_match(c, &entry)) {
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
}

static void print_entry(struct credential *c)
{
	printf("username=%s\n", c->username);
	printf("password=%s\n", c->password);
