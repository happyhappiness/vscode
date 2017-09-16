	states fresh;		/* states for a fresh start */

	states tmp;		/* temporary */

	states empty;		/* empty set of states */

};



#include "engine.ih"



#ifdef REDEBUG

#define	SP(t, s, c)	print(m, t, s, c, stdout)

#define	AT(t, p1, p2, s1, s2)	at(m, t, p1, p2, s1, s2)

#define	NOTE(str)	{ if (m->eflags&REG_TRACE) printf("=%s\n", (str)); }

#else

