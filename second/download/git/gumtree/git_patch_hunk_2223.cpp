 				bad_object(obj->idx.offset, _("offset value overflow for delta base object"));
 			p = fill(1);
 			c = *p;
 			use(1);
 			base_offset = (base_offset << 7) + (c & 127);
 		}
-		delta_base->offset = obj->idx.offset - base_offset;
-		if (delta_base->offset <= 0 || delta_base->offset >= obj->idx.offset)
+		*ofs_offset = obj->idx.offset - base_offset;
+		if (*ofs_offset <= 0 || *ofs_offset >= obj->idx.offset)
 			bad_object(obj->idx.offset, _("delta base offset is out of bound"));
 		break;
 	case OBJ_COMMIT:
 	case OBJ_TREE:
 	case OBJ_BLOB:
 	case OBJ_TAG:
