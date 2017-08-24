(self->NT4) {
      kwsysProcess_List__Delete_NT4(self);
    } else {
      kwsysProcess_List__Delete_Snapshot(self);
    }