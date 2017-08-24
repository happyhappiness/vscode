{
      writeWithIndent("[");
      indent();
      bool hasChildValue = !childValues_.empty();
      unsigned index = 0;
      for (;;) {
        const Value& childValue = value[index];
        writeCommentBeforeValue(childValue);
        if (hasChildValue)
          writeWithIndent(childValues_[index]);
        else {
          writeIndent();
          writeValue(childValue);
        }
        if (++index == size) {
          writeCommentAfterValueOnSameLine(childValue);
          break;
        }
        document_ += ',';
        writeCommentAfterValueOnSameLine(childValue);
      }
      unindent();
      writeWithIndent("]");
    }