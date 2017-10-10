 			if (grep_source_is_binary(gs))
 				return 0; /* Assume unmatch */
 			break;
 		case GREP_BINARY_TEXT:
 			break;
 		default:
-			die("bug: unknown binary handling mode");
+			die("BUG: unknown binary handling mode");
 		}
 	}
 
 	memset(&xecfg, 0, sizeof(xecfg));
 	opt->priv = &xecfg;
 
