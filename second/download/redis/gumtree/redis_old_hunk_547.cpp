            } else {
                /* Likely the command name, stop here. */
                break;
            }
        }
    }
    return i;
}

static sds readArgFromStdin(void) {
    char buf[1024];
    sds arg = sdsempty();
