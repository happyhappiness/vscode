{
            /* This is the end of the last line, copy the last line to the
               start of the buffer and zero terminate, for old times sake */
            size_t n = ptr - pp->linestart_resp;
            memmove(buf, pp->linestart_resp, n);
            buf[n]=0; /* zero terminate */
            keepon=FALSE;
            pp->linestart_resp = ptr+1; /* advance pointer */
            i++; /* skip this before getting out */

            *size = pp->nread_resp; /* size of the response */
            pp->nread_resp = 0; /* restart */
            break;
          }