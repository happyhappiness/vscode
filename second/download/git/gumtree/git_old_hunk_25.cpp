				struct tree *item = (struct tree *) obj;
				item->buffer = NULL;
				obj->parsed = 0;
			}
			if (obj->type == OBJ_COMMIT) {
				struct commit *commit = (struct commit *) obj;
				commit->buffer = NULL;
			}
			obj->flags |= FLAG_CHECKED;
		}
		read_unlock();
	}

