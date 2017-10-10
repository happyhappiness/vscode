printf("%s%c%d %d %d\n",
	       hex,
	       ent->guilty ? ' ' : '*', /* purely for debugging */
	       ent->s_lno + 1,
	       ent->lno + 1,
	       ent->num_lines);