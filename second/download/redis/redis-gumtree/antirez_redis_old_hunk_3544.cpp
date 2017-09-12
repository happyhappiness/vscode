                    if (i == lc.len) beep();
                    break;
                case 27: /* escape */
                    stop = 1;
                    break;
                default:
                    /* update buffer and return */
                    if (i < lc.len) {
                        nwritten = snprintf(buf,buflen,"%s",lc.cvec[i]);
                        *len = *pos = nwritten;
