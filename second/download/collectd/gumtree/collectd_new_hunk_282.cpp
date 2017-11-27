#endif
	case DLT_NULL:
	    status = handle_null (pkt, hdr->caplen);
	    break;

	default:
	    ERROR ("handle_pcap: unsupported data link type %d\n",
		    pcap_datalink(pcap_obj));
	    status = 0;
	    break;
    } /* switch (pcap_datalink(pcap_obj)) */

    if (0 == status)
