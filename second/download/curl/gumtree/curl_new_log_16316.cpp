fputs(
"              lines and lines starting with '#' are comments and ignored; each\n"
"              header can be folded by splitting between two words and starting\n"
"              the continuation line with a  space;  embedded  carriage-returns\n"
"              and  trailing  spaces  are  stripped.   Here  is an example of a\n"
"              header file contents:\n"
"\n"
"                # This file contain two headers.\n"
"                X-header-1: this is a header\n"
"\n"
"                # The following header is folded.\n"
, stdout);