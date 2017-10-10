 		break;
 	case TRAILER_IF_MISSING:
 		if (set_if_missing(conf, value))
 			warning(_("unknown value '%s' for key '%s'"), value, conf_key);
 		break;
 	default:
-		die("internal bug in trailer.c");
+		die("BUG: trailer.c: unhandled type %d", type);
 	}
 	return 0;
 }
 
 static int parse_trailer(struct strbuf *tok, struct strbuf *val, const char *trailer)
 {
