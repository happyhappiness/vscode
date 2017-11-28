            break;

        case DIGEST_READ_NONE:
            break;

        case DIGEST_READ_DONE:
            goto finish;
            break;

        default:
            fatal("Bad digest transfer mode!\n");
        }

        if (retsize < 0)
            goto finish;

        /*
         * The returned size indicates how much of the buffer was read -
         * so move the remainder of the buffer to the beginning
         * and update the bufofs / bufsize
         */
