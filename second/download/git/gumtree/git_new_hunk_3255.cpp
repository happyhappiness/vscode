#include "url.h"
#include "submodule.h"
#include "string-list.h"
#include "sha1-array.h"
#include "sigchain.h"

static void set_upstreams(struct transport *transport, struct ref *refs,
	int pretend)
{
	struct ref *ref;
	for (ref = refs; ref; ref = ref->next) {
		const char *localname;
