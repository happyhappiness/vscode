                concurrency = atoi(optarg);
                break;
            case 'b':
                windowsize = atoi(optarg);
                break;
            case 'i':
                if (method != NO_METH)
                    err("Cannot mix HEAD with other methods\n");
                method = HEAD;
                break;
            case 'g':
                gnuplot = strdup(optarg);
                break;
            case 'd':
                percentile = 0;
