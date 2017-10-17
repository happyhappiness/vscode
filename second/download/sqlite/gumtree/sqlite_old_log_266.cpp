sqlite3_mprintf(
    "ALTER TABLE %Q.'%q_content'  RENAME TO '%q_content';"
    "ALTER TABLE %Q.'%q_segments' RENAME TO '%q_segments';"
    "ALTER TABLE %Q.'%q_segdir'   RENAME TO '%q_segdir';"
    , p->zDb, p->zName, zName 
    , p->zDb, p->zName, zName 
    , p->zDb, p->zName, zName
  );