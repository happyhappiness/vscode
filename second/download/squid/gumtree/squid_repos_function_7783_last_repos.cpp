void
RFCNB_Print_Pkt(FILE * fd, char *dirn, struct RFCNB_Pkt *pkt, int len)
{
    char lname[17];

    /* We assume that the first fragment is the RFCNB Header  */
    /* We should loop through the fragments printing them out */

    fprintf(fd, "RFCNB Pkt %s:", dirn);

    switch (RFCNB_Pkt_Type(pkt->data)) {

    case RFCNB_SESSION_MESSAGE:

        fprintf(fd, "SESSION MESSAGE: Length = %i\n", RFCNB_Pkt_Len(pkt->data));
        RFCNB_Print_Hex(fd, pkt, RFCNB_Pkt_Hdr_Len,
#ifdef RFCNB_PRINT_DATA
                        RFCNB_Pkt_Len(pkt->data) - RFCNB_Pkt_Hdr_Len);
#else
                        40);
#endif

        if (Prot_Print_Routine) {       /* Print the rest of the packet */

            Prot_Print_Routine(fd, strcmp(dirn, "sent"), pkt, RFCNB_Pkt_Hdr_Len,
                               RFCNB_Pkt_Len(pkt->data) - RFCNB_Pkt_Hdr_Len);

        }
        break;

    case RFCNB_SESSION_REQUEST:

        fprintf(fd, "SESSION REQUEST: Length = %i\n",
                RFCNB_Pkt_Len(pkt->data));
        RFCNB_NBName_To_AName((char *) (pkt->data + RFCNB_Pkt_Called_Offset), lname);
        fprintf(fd, "  Called Name: %s\n", lname);
        RFCNB_NBName_To_AName((char *) (pkt->data + RFCNB_Pkt_Calling_Offset), lname);
        fprintf(fd, "  Calling Name: %s\n", lname);

        break;

    case RFCNB_SESSION_ACK:

        fprintf(fd, "RFCNB SESSION ACK: Length = %i\n",
                RFCNB_Pkt_Len(pkt->data));

        break;

    case RFCNB_SESSION_REJ:
        fprintf(fd, "RFCNB SESSION REJECT: Length = %i\n",
                RFCNB_Pkt_Len(pkt->data));

        if (RFCNB_Pkt_Len(pkt->data) < 1) {
            fprintf(fd, "   Protocol Error, short Reject packet!\n");
        } else {
            fprintf(fd, "   Error = %x\n", CVAL(pkt->data, RFCNB_Pkt_Error_Offset));
        }

        break;

    case RFCNB_SESSION_RETARGET:

        fprintf(fd, "RFCNB SESSION RETARGET: Length = %i\n",
                RFCNB_Pkt_Len(pkt->data));

        /* Print out the IP address etc and the port? */

        break;

    case RFCNB_SESSION_KEEP_ALIVE:

        fprintf(fd, "RFCNB SESSION KEEP ALIVE: Length = %i\n",
                RFCNB_Pkt_Len(pkt->data));
        break;

    default:

        break;
    }