#include "cache_cf.h"
#include "ConfigParser.h"
#include "Debug.h"
#include "fatal.h"
#include "globals.h"

void
ConfigParser::destruct()
{
    shutting_down = 1;
    fatalf("Bungled %s line %d: %s",
           cfg_filename, config_lineno, config_input_line);
}

char *
ConfigParser::strtokFile(void)
{
    static int fromFile = 0;
    static FILE *wordFile = NULL;

    char *t, *fn;
    LOCAL_ARRAY(char, buf, CONFIG_LINE_LIMIT);

    do {

        if (!fromFile) {
            t = (strtok(NULL, w_space));

            if (!t || *t == '#') {
