            break;

        case DIGEST_READ_NONE:
            break;

        case DIGEST_READ_DONE:
            return;
            break;

        default:
            fatal("Bad digest transfer mode!\n");
        }

        if (retsize < 0)
            return;

        /*
         * The returned size indicates how much of the buffer was read -
         * so move the remainder of the buffer to the beginning
         * and update the bufofs / bufsize
         */
