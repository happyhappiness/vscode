	}
	return 0;
}


/**********************************************************************
 * Chain index (cache utility) functions
 **********************************************************************
 * The chain index is an array with pointers into the chain list, with
 * CHAIN_INDEX_BUCKET_LEN spacing.  This facilitates the ability to
 * speedup chain list searching, by find a more optimal starting
 * points when searching the linked list.
 *
 * The starting point can be found fast by using a binary search of
 * the chain index. Thus, reducing the previous search complexity of
 * O(n) to O(log(n/k) + k) where k is CHAIN_INDEX_BUCKET_LEN.
 *
 * A nice property of the chain index, is that the "bucket" list
 * length is max CHAIN_INDEX_BUCKET_LEN (when just build, inserts will
 * change this). Oppose to hashing, where the "bucket" list length can
 * vary a lot.
 */
#ifndef CHAIN_INDEX_BUCKET_LEN
#define CHAIN_INDEX_BUCKET_LEN 40
#endif

/* Another nice property of the chain index is that inserting/creating
 * chains in chain list don't change the correctness of the chain
 * index, it only causes longer lists in the buckets.
 *
 * To mitigate the performance penalty of longer bucket lists and the
 * penalty of rebuilding, the chain index is rebuild only when
 * CHAIN_INDEX_INSERT_MAX chains has been added.
 */
#ifndef CHAIN_INDEX_INSERT_MAX
#define CHAIN_INDEX_INSERT_MAX 355
#endif

static inline unsigned int iptcc_is_builtin(struct chain_head *c);


/* Use binary search in the chain index array, to find a chain_head
 * pointer closest to the place of the searched name element.
 *
 * Notes that, binary search (obviously) requires that the chain list
 * is sorted by name.
 */
static struct list_head *
iptcc_bsearch_chain_index(const char *name, unsigned int *idx, TC_HANDLE_T handle)
{
	unsigned int pos, end;
	int res;

	struct list_head *list_pos;
	list_pos=&handle->chains;

	/* Check for empty array, e.g. no user defined chains */
	if (handle->chain_index_sz == 0) {
		debug("WARNING: handle->chain_index_sz == 0\n");
		return list_pos;
	}

	/* Init */
	end = handle->chain_index_sz;
	pos = end / 2;

	debug("bsearch Find chain:%s (pos:%d end:%d)\n", name, pos, end);

	/* Loop */
 loop:
	if (!handle->chain_index[pos]) {
		fprintf(stderr, "ERROR: NULL pointer chain_index[%d]\n", pos);
		return &handle->chains; /* Be safe, return orig start pos */
	}

	res = strcmp(name, handle->chain_index[pos]->name);
	list_pos = &handle->chain_index[pos]->list;
	*idx = pos;

	debug("bsearch Index[%d] name:%s res:%d ",
	      pos, handle->chain_index[pos]->name, res);

	if (res == 0) { /* Found element, by direct hit */
		debug("[found] Direct hit pos:%d end:%d\n", pos, end);
		return list_pos;
	} else if (res < 0) { /* Too far, jump back */
		end = pos;
		pos = pos / 2;

		/* Exit case: First element of array */
		if (end == 0) {
			debug("[found] Reached first array elem (end%d)\n",end);
			return list_pos;
		}
		debug("jump back to pos:%d (end:%d)\n", pos, end);
		goto loop;
	} else if (res > 0 ){ /* Not far enough, jump forward */

		/* Exit case: Last element of array */
		if (pos == handle->chain_index_sz-1) {
			debug("[found] Last array elem (end:%d)\n", end);
			return list_pos;
		}

		/* Exit case: Next index less, thus elem in this list section */
		res = strcmp(name, handle->chain_index[pos+1]->name);
		if (res < 0) {
			debug("[found] closest list (end:%d)\n", end);
			return list_pos;
		}

		pos = (pos+end)/2;
		debug("jump forward to pos:%d (end:%d)\n", pos, end);
		goto loop;
	}

	return list_pos;
}

#ifdef DEBUG
/* Trivial linear search of chain index. Function used for verifying
   the output of bsearch function */
static struct list_head *
iptcc_linearly_search_chain_index(const char *name, TC_HANDLE_T handle)
{
	unsigned int i=0;
	int res=0;

	struct list_head *list_pos;
	list_pos = &handle->chains;

	if (handle->chain_index_sz)
		list_pos = &handle->chain_index[0]->list;

	/* Linearly walk of chain index array */

	for (i=0; i < handle->chain_index_sz; i++) {
		if (handle->chain_index[i]) {
			res = strcmp(handle->chain_index[i]->name, name);
			if (res > 0)
				break; // One step too far
			list_pos = &handle->chain_index[i]->list;
			if (res == 0)
				break; // Direct hit
		}
	}

	return list_pos;
}
#endif

static int iptcc_chain_index_alloc(TC_HANDLE_T h)
{
	unsigned int list_length = CHAIN_INDEX_BUCKET_LEN;
	unsigned int array_elems;
	unsigned int array_mem;

	/* Allocate memory for the chain index array */
	array_elems = (h->num_chains / list_length) +
                      (h->num_chains % list_length ? 1 : 0);
	array_mem   = sizeof(h->chain_index) * array_elems;

	debug("Alloc Chain index, elems:%d mem:%d bytes\n",
	      array_elems, array_mem);

	h->chain_index = malloc(array_mem);
	if (!h->chain_index) {
		h->chain_index_sz = 0;
		return -ENOMEM;
	}
	memset(h->chain_index, 0, array_mem);
	h->chain_index_sz = array_elems;

	return 1;
}

static void iptcc_chain_index_free(TC_HANDLE_T h)
{
	h->chain_index_sz = 0;
	free(h->chain_index);
}


#ifdef DEBUG
static void iptcc_chain_index_dump(TC_HANDLE_T h)
{
	unsigned int i = 0;

	/* Dump: contents of chain index array */
	for (i=0; i < h->chain_index_sz; i++) {
		if (h->chain_index[i]) {
			fprintf(stderr, "Chain index[%d].name: %s\n",
				i, h->chain_index[i]->name);
		}
	}
}
#endif

/* Build the chain index */
static int iptcc_chain_index_build(TC_HANDLE_T h)
{
	unsigned int list_length = CHAIN_INDEX_BUCKET_LEN;
	unsigned int chains = 0;
	unsigned int cindex = 0;
	struct chain_head *c;

	/* Build up the chain index array here */
	debug("Building chain index\n");

	debug("Number of user defined chains:%d bucket_sz:%d array_sz:%d\n",
		h->num_chains, list_length, h->chain_index_sz);

	if (h->chain_index_sz == 0)
		return 0;

	list_for_each_entry(c, &h->chains, list) {

		/* Issue: The index array needs to start after the
		 * builtin chains, as they are not sorted */
		if (!iptcc_is_builtin(c)) {
			cindex=chains / list_length;

			/* Safe guard, break out on array limit, this
			 * is useful if chains are added and array is
			 * rebuild, without realloc of memory. */
			if (cindex >= h->chain_index_sz)
				break;

			if ((chains % list_length)== 0) {
				debug("\nIndex[%d] Chains:", cindex);
				h->chain_index[cindex] = c;
			}
			chains++;
		}
		debug("%s, ", c->name);
	}
	debug("\n");

	return 1;
}

static int iptcc_chain_index_rebuild(TC_HANDLE_T h)
{
	debug("REBUILD chain index array\n");
	iptcc_chain_index_free(h);
	if ((iptcc_chain_index_alloc(h)) < 0)
		return -ENOMEM;
	iptcc_chain_index_build(h);
	return 1;
}

/* Delete chain (pointer) from index array.  Removing an element from
 * the chain list only affects the chain index array, if the chain
 * index points-to/uses that list pointer.
 *
 * There are different strategies, the simple and safe is to rebuild
 * the chain index every time.  The more advanced is to update the
 * array index to point to the next element, but that requires some
 * house keeping and boundry checks.  The advanced is implemented, as
 * the simple approach behaves badly when all chains are deleted
 * because list_for_each processing will always hit the first chain
 * index, thus causing a rebuild for every chain.
 */
static int iptcc_chain_index_delete_chain(struct chain_head *c, TC_HANDLE_T h)
{
	struct list_head *index_ptr, *index_ptr2, *next;
	struct chain_head *c2;
	unsigned int idx, idx2;

	index_ptr = iptcc_bsearch_chain_index(c->name, &idx, h);

	debug("Del chain[%s] c->list:%p index_ptr:%p\n",
	      c->name, &c->list, index_ptr);

	/* Save the next pointer */
	next = c->list.next;
	list_del(&c->list);

	if (index_ptr == &c->list) { /* Chain used as index ptr */

		/* See if its possible to avoid a rebuild, by shifting
		 * to next pointer.  Its possible if the next pointer
		 * is located in the same index bucket.
		 */
		c2         = list_entry(next, struct chain_head, list);
		index_ptr2 = iptcc_bsearch_chain_index(c2->name, &idx2, h);
		if (idx != idx2) {
			/* Rebuild needed */
			return iptcc_chain_index_rebuild(h);
		} else {
			/* Avoiding rebuild */
			debug("Update cindex[%d] with next ptr name:[%s]\n",
			      idx, c2->name);
			h->chain_index[idx]=c2;
			return 0;
		}
	}
	return 0;
}


/**********************************************************************
 * iptc cache utility functions (iptcc_*)
 **********************************************************************/

/* Is the given chain builtin (1) or user-defined (0) */
static inline unsigned int iptcc_is_builtin(struct chain_head *c)
{
	return (c->hooknum ? 1 : 0);
}

/* Get a specific rule within a chain */
static struct rule_head *iptcc_get_rule_num(struct chain_head *c,
