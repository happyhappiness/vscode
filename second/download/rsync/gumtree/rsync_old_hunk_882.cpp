static int total_false_alarms;
static int total_hash_hits;
static int total_matches;

extern struct stats stats;

#define TABLESIZE (1<<16)

static int32 *hash_table;

#define SUM2HASH2(s1,s2) (((s1) + (s2)) & 0xFFFF)
#define SUM2HASH(sum) SUM2HASH2((sum)&0xFFFF,(sum)>>16)

static void build_hash_table(struct sum_struct *s)
{
	int32 i;

	if (!hash_table) {
		hash_table = new_array(int32, TABLESIZE);
		if (!hash_table)
			out_of_memory("build_hash_table");
	}

	memset(hash_table, 0xFF, TABLESIZE * sizeof hash_table[0]);

	for (i = 0; i < s->count; i++) {
		uint32 t = SUM2HASH(s->sums[i].sum1);
		s->sums[i].chain = hash_table[t];
		hash_table[t] = i;
	}
}


static OFF_T last_match;

