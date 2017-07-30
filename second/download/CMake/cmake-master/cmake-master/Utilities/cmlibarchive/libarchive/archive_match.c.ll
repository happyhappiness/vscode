; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_match.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive_rb_tree_ops = type { i32 (%struct.archive_rb_node*, %struct.archive_rb_node*)*, i32 (%struct.archive_rb_node*, i8*)* }
%struct.archive_rb_node = type { [2 x %struct.archive_rb_node*], i64 }
%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { i32 (%struct.archive*)*, i32 (%struct.archive*)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)*, i8* (%struct.archive*, i32)* }
%struct.archive_entry = type opaque
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque
%struct.archive_match = type { %struct.archive, i32, %struct.match_list, %struct.match_list, i64, i32, i64, i64, i32, i64, i64, i32, i64, i64, i32, i64, i64, %struct.archive_rb_tree, %struct.entry_list, %struct.id_array, %struct.id_array, %struct.match_list, %struct.match_list }
%struct.archive_rb_tree = type { %struct.archive_rb_node*, %struct.archive_rb_tree_ops* }
%struct.entry_list = type { %struct.match_file*, %struct.match_file**, i32 }
%struct.match_file = type { %struct.archive_rb_node, %struct.match_file*, %struct.archive_mstring, i32, i64, i64, i64, i64 }
%struct.archive_mstring = type { %struct.archive_string, %struct.archive_string, %struct.archive_wstring, %struct.archive_string, i32 }
%struct.archive_wstring = type { i32*, i64, i64 }
%struct.id_array = type { i64, i64, i64* }
%struct.match_list = type { %struct.match*, %struct.match**, i32, i32, %struct.match*, i32 }
%struct.match = type { %struct.match*, i32, %struct.archive_mstring }
%struct.stat = type { i64, i64, i64, i32, i32, i32, i32, i64, i64, i64, i64, %struct.timespec, %struct.timespec, %struct.timespec, [3 x i64] }
%struct.timespec = type { i64, i64 }

@rb_ops_mbs = internal constant %struct.archive_rb_tree_ops { i32 (%struct.archive_rb_node*, %struct.archive_rb_node*)* @cmp_node_mbs, i32 (%struct.archive_rb_node*, i8*)* @cmp_key_mbs }, align 8
@.str = private unnamed_addr constant [19 x i8] c"archive_match_free\00", align 1
@.str.1 = private unnamed_addr constant [26 x i8] c"archive_match_excluded_ae\00", align 1
@.str.2 = private unnamed_addr constant [14 x i8] c"entry is NULL\00", align 1
@.str.3 = private unnamed_addr constant [30 x i8] c"archive_match_exclude_pattern\00", align 1
@.str.4 = private unnamed_addr constant [17 x i8] c"pattern is empty\00", align 1
@.str.5 = private unnamed_addr constant [32 x i8] c"archive_match_exclude_pattern_w\00", align 1
@.str.6 = private unnamed_addr constant [40 x i8] c"archive_match_exclude_pattern_from_file\00", align 1
@.str.7 = private unnamed_addr constant [42 x i8] c"archive_match_exclude_pattern_from_file_w\00", align 1
@.str.8 = private unnamed_addr constant [30 x i8] c"archive_match_include_pattern\00", align 1
@.str.9 = private unnamed_addr constant [32 x i8] c"archive_match_include_pattern_w\00", align 1
@.str.10 = private unnamed_addr constant [40 x i8] c"archive_match_include_pattern_from_file\00", align 1
@.str.11 = private unnamed_addr constant [42 x i8] c"archive_match_include_pattern_from_file_w\00", align 1
@.str.12 = private unnamed_addr constant [28 x i8] c"archive_match_path_excluded\00", align 1
@.str.13 = private unnamed_addr constant [35 x i8] c"archive_match_unmatched_inclusions\00", align 1
@.str.14 = private unnamed_addr constant [40 x i8] c"archive_match_unmatched_inclusions_next\00", align 1
@.str.15 = private unnamed_addr constant [42 x i8] c"archive_match_unmatched_inclusions_next_w\00", align 1
@.str.16 = private unnamed_addr constant [27 x i8] c"archive_match_include_time\00", align 1
@.str.17 = private unnamed_addr constant [27 x i8] c"archive_match_include_date\00", align 1
@.str.18 = private unnamed_addr constant [29 x i8] c"archive_match_include_date_w\00", align 1
@.str.19 = private unnamed_addr constant [32 x i8] c"archive_match_include_file_time\00", align 1
@.str.20 = private unnamed_addr constant [34 x i8] c"archive_match_include_file_time_w\00", align 1
@.str.21 = private unnamed_addr constant [33 x i8] c"archive_match_time_include_entry\00", align 1
@.str.22 = private unnamed_addr constant [28 x i8] c"archive_match_exclude_entry\00", align 1
@.str.23 = private unnamed_addr constant [31 x i8] c"archive_match_time_excluded_ae\00", align 1
@.str.24 = private unnamed_addr constant [26 x i8] c"archive_match_include_uid\00", align 1
@.str.25 = private unnamed_addr constant [26 x i8] c"archive_match_include_gid\00", align 1
@.str.26 = private unnamed_addr constant [28 x i8] c"archive_match_include_uname\00", align 1
@.str.27 = private unnamed_addr constant [30 x i8] c"archive_match_include_uname_w\00", align 1
@.str.28 = private unnamed_addr constant [28 x i8] c"archive_match_include_gname\00", align 1
@.str.29 = private unnamed_addr constant [30 x i8] c"archive_match_include_gname_w\00", align 1
@.str.30 = private unnamed_addr constant [29 x i8] c"archive_match_id_excluded_ae\00", align 1
@.str.31 = private unnamed_addr constant [10 x i8] c"No memory\00", align 1
@.str.32 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.33 = private unnamed_addr constant [1 x i32] zeroinitializer, align 4
@.str.34 = private unnamed_addr constant [18 x i8] c"Invalid time flag\00", align 1
@.str.35 = private unnamed_addr constant [13 x i8] c"No time flag\00", align 1
@.str.36 = private unnamed_addr constant [24 x i8] c"Invalid comparison flag\00", align 1
@.str.37 = private unnamed_addr constant [19 x i8] c"No comparison flag\00", align 1
@.str.38 = private unnamed_addr constant [14 x i8] c"date is empty\00", align 1
@.str.39 = private unnamed_addr constant [20 x i8] c"invalid date string\00", align 1
@.str.40 = private unnamed_addr constant [29 x i8] c"Failed to convert WCS to MBS\00", align 1
@.str.41 = private unnamed_addr constant [18 x i8] c"pathname is empty\00", align 1
@.str.42 = private unnamed_addr constant [17 x i8] c"Failed to stat()\00", align 1
@rb_ops_wcs = internal constant %struct.archive_rb_tree_ops { i32 (%struct.archive_rb_node*, %struct.archive_rb_node*)* @cmp_node_wcs, i32 (%struct.archive_rb_node*, i8*)* @cmp_key_wcs }, align 8
@.str.43 = private unnamed_addr constant [17 x i8] c"pathname is NULL\00", align 1

; Function Attrs: nounwind uwtable
define %struct.archive* @archive_match_new() #0 !dbg !221 {
entry:
  %retval = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_match*, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a, metadata !393, metadata !394), !dbg !395
  %call = call noalias i8* @calloc(i64 1, i64 520) #7, !dbg !396
  %0 = bitcast i8* %call to %struct.archive_match*, !dbg !397
  store %struct.archive_match* %0, %struct.archive_match** %a, align 8, !dbg !398
  %1 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !399
  %cmp = icmp eq %struct.archive_match* %1, null, !dbg !401
  br i1 %cmp, label %if.then, label %if.end, !dbg !402

if.then:                                          ; preds = %entry
  store %struct.archive* null, %struct.archive** %retval, align 8, !dbg !403
  br label %return, !dbg !403

if.end:                                           ; preds = %entry
  %2 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !404
  %archive = getelementptr inbounds %struct.archive_match, %struct.archive_match* %2, i32 0, i32 0, !dbg !405
  %magic = getelementptr inbounds %struct.archive, %struct.archive* %archive, i32 0, i32 0, !dbg !406
  store i32 212668873, i32* %magic, align 8, !dbg !407
  %3 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !408
  %archive1 = getelementptr inbounds %struct.archive_match, %struct.archive_match* %3, i32 0, i32 0, !dbg !409
  %state = getelementptr inbounds %struct.archive, %struct.archive* %archive1, i32 0, i32 1, !dbg !410
  store i32 1, i32* %state, align 4, !dbg !411
  %4 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !412
  %inclusions = getelementptr inbounds %struct.archive_match, %struct.archive_match* %4, i32 0, i32 3, !dbg !413
  call void @match_list_init(%struct.match_list* %inclusions), !dbg !414
  %5 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !415
  %exclusions = getelementptr inbounds %struct.archive_match, %struct.archive_match* %5, i32 0, i32 2, !dbg !416
  call void @match_list_init(%struct.match_list* %exclusions), !dbg !417
  %6 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !418
  %exclusion_tree = getelementptr inbounds %struct.archive_match, %struct.archive_match* %6, i32 0, i32 17, !dbg !419
  call void @__archive_rb_tree_init(%struct.archive_rb_tree* %exclusion_tree, %struct.archive_rb_tree_ops* @rb_ops_mbs), !dbg !420
  %7 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !421
  %exclusion_entry_list = getelementptr inbounds %struct.archive_match, %struct.archive_match* %7, i32 0, i32 18, !dbg !422
  call void @entry_list_init(%struct.entry_list* %exclusion_entry_list), !dbg !423
  %8 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !424
  %inclusion_unames = getelementptr inbounds %struct.archive_match, %struct.archive_match* %8, i32 0, i32 21, !dbg !425
  call void @match_list_init(%struct.match_list* %inclusion_unames), !dbg !426
  %9 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !427
  %inclusion_gnames = getelementptr inbounds %struct.archive_match, %struct.archive_match* %9, i32 0, i32 22, !dbg !428
  call void @match_list_init(%struct.match_list* %inclusion_gnames), !dbg !429
  %10 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !430
  %now = getelementptr inbounds %struct.archive_match, %struct.archive_match* %10, i32 0, i32 4, !dbg !431
  %call2 = call i64 @time(i64* %now) #7, !dbg !432
  %11 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !433
  %archive3 = getelementptr inbounds %struct.archive_match, %struct.archive_match* %11, i32 0, i32 0, !dbg !434
  store %struct.archive* %archive3, %struct.archive** %retval, align 8, !dbg !435
  br label %return, !dbg !435

return:                                           ; preds = %if.end, %if.then
  %12 = load %struct.archive*, %struct.archive** %retval, align 8, !dbg !436
  ret %struct.archive* %12, !dbg !436
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #2

; Function Attrs: nounwind uwtable
define internal void @match_list_init(%struct.match_list* %list) #0 !dbg !301 {
entry:
  %list.addr = alloca %struct.match_list*, align 8
  store %struct.match_list* %list, %struct.match_list** %list.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.match_list** %list.addr, metadata !437, metadata !394), !dbg !438
  %0 = load %struct.match_list*, %struct.match_list** %list.addr, align 8, !dbg !439
  %first = getelementptr inbounds %struct.match_list, %struct.match_list* %0, i32 0, i32 0, !dbg !440
  store %struct.match* null, %struct.match** %first, align 8, !dbg !441
  %1 = load %struct.match_list*, %struct.match_list** %list.addr, align 8, !dbg !442
  %first1 = getelementptr inbounds %struct.match_list, %struct.match_list* %1, i32 0, i32 0, !dbg !443
  %2 = load %struct.match_list*, %struct.match_list** %list.addr, align 8, !dbg !444
  %last = getelementptr inbounds %struct.match_list, %struct.match_list* %2, i32 0, i32 1, !dbg !445
  store %struct.match** %first1, %struct.match*** %last, align 8, !dbg !446
  %3 = load %struct.match_list*, %struct.match_list** %list.addr, align 8, !dbg !447
  %count = getelementptr inbounds %struct.match_list, %struct.match_list* %3, i32 0, i32 2, !dbg !448
  store i32 0, i32* %count, align 8, !dbg !449
  ret void, !dbg !450
}

declare void @__archive_rb_tree_init(%struct.archive_rb_tree*, %struct.archive_rb_tree_ops*) #3

; Function Attrs: nounwind uwtable
define internal void @entry_list_init(%struct.entry_list* %list) #0 !dbg !359 {
entry:
  %list.addr = alloca %struct.entry_list*, align 8
  store %struct.entry_list* %list, %struct.entry_list** %list.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.entry_list** %list.addr, metadata !451, metadata !394), !dbg !452
  %0 = load %struct.entry_list*, %struct.entry_list** %list.addr, align 8, !dbg !453
  %first = getelementptr inbounds %struct.entry_list, %struct.entry_list* %0, i32 0, i32 0, !dbg !454
  store %struct.match_file* null, %struct.match_file** %first, align 8, !dbg !455
  %1 = load %struct.entry_list*, %struct.entry_list** %list.addr, align 8, !dbg !456
  %first1 = getelementptr inbounds %struct.entry_list, %struct.entry_list* %1, i32 0, i32 0, !dbg !457
  %2 = load %struct.entry_list*, %struct.entry_list** %list.addr, align 8, !dbg !458
  %last = getelementptr inbounds %struct.entry_list, %struct.entry_list* %2, i32 0, i32 1, !dbg !459
  store %struct.match_file** %first1, %struct.match_file*** %last, align 8, !dbg !460
  %3 = load %struct.entry_list*, %struct.entry_list** %list.addr, align 8, !dbg !461
  %count = getelementptr inbounds %struct.entry_list, %struct.entry_list* %3, i32 0, i32 2, !dbg !462
  store i32 0, i32* %count, align 8, !dbg !463
  ret void, !dbg !464
}

; Function Attrs: nounwind
declare i64 @time(i64*) #2

; Function Attrs: nounwind uwtable
define i32 @archive_match_free(%struct.archive* %_a) #0 !dbg !224 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_match*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !465, metadata !394), !dbg !466
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a, metadata !467, metadata !394), !dbg !468
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !469
  %cmp = icmp eq %struct.archive* %0, null, !dbg !471
  br i1 %cmp, label %if.then, label %if.end, !dbg !472

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !473
  br label %return, !dbg !473

if.end:                                           ; preds = %entry
  br label %do.body, !dbg !474

do.body:                                          ; preds = %if.end
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !475, metadata !394), !dbg !477
  %1 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !478
  %call = call i32 @__archive_check_magic(%struct.archive* %1, i32 212668873, i32 65535, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str, i32 0, i32 0)), !dbg !478
  store i32 %call, i32* %magic_test, align 4, !dbg !478
  %2 = load i32, i32* %magic_test, align 4, !dbg !478
  %cmp1 = icmp eq i32 %2, -30, !dbg !478
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !478

if.then2:                                         ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !480
  br label %return, !dbg !480

if.end3:                                          ; preds = %do.body
  br label %do.end, !dbg !483

do.end:                                           ; preds = %if.end3
  %3 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !485
  %4 = bitcast %struct.archive* %3 to %struct.archive_match*, !dbg !486
  store %struct.archive_match* %4, %struct.archive_match** %a, align 8, !dbg !487
  %5 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !488
  %inclusions = getelementptr inbounds %struct.archive_match, %struct.archive_match* %5, i32 0, i32 3, !dbg !489
  call void @match_list_free(%struct.match_list* %inclusions), !dbg !490
  %6 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !491
  %exclusions = getelementptr inbounds %struct.archive_match, %struct.archive_match* %6, i32 0, i32 2, !dbg !492
  call void @match_list_free(%struct.match_list* %exclusions), !dbg !493
  %7 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !494
  %exclusion_entry_list = getelementptr inbounds %struct.archive_match, %struct.archive_match* %7, i32 0, i32 18, !dbg !495
  call void @entry_list_free(%struct.entry_list* %exclusion_entry_list), !dbg !496
  %8 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !497
  %inclusion_uids = getelementptr inbounds %struct.archive_match, %struct.archive_match* %8, i32 0, i32 19, !dbg !498
  %ids = getelementptr inbounds %struct.id_array, %struct.id_array* %inclusion_uids, i32 0, i32 2, !dbg !499
  %9 = load i64*, i64** %ids, align 8, !dbg !499
  %10 = bitcast i64* %9 to i8*, !dbg !497
  call void @free(i8* %10) #7, !dbg !500
  %11 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !501
  %inclusion_gids = getelementptr inbounds %struct.archive_match, %struct.archive_match* %11, i32 0, i32 20, !dbg !502
  %ids4 = getelementptr inbounds %struct.id_array, %struct.id_array* %inclusion_gids, i32 0, i32 2, !dbg !503
  %12 = load i64*, i64** %ids4, align 8, !dbg !503
  %13 = bitcast i64* %12 to i8*, !dbg !501
  call void @free(i8* %13) #7, !dbg !504
  %14 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !505
  %inclusion_unames = getelementptr inbounds %struct.archive_match, %struct.archive_match* %14, i32 0, i32 21, !dbg !506
  call void @match_list_free(%struct.match_list* %inclusion_unames), !dbg !507
  %15 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !508
  %inclusion_gnames = getelementptr inbounds %struct.archive_match, %struct.archive_match* %15, i32 0, i32 22, !dbg !509
  call void @match_list_free(%struct.match_list* %inclusion_gnames), !dbg !510
  %16 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !511
  %17 = bitcast %struct.archive_match* %16 to i8*, !dbg !511
  call void @free(i8* %17) #7, !dbg !512
  store i32 0, i32* %retval, align 4, !dbg !513
  br label %return, !dbg !513

return:                                           ; preds = %do.end, %if.then2, %if.then
  %18 = load i32, i32* %retval, align 4, !dbg !514
  ret i32 %18, !dbg !514
}

declare i32 @__archive_check_magic(%struct.archive*, i32, i32, i8*) #3

; Function Attrs: nounwind uwtable
define internal void @match_list_free(%struct.match_list* %list) #0 !dbg !304 {
entry:
  %list.addr = alloca %struct.match_list*, align 8
  %p = alloca %struct.match*, align 8
  %q = alloca %struct.match*, align 8
  store %struct.match_list* %list, %struct.match_list** %list.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.match_list** %list.addr, metadata !515, metadata !394), !dbg !516
  call void @llvm.dbg.declare(metadata %struct.match** %p, metadata !517, metadata !394), !dbg !518
  call void @llvm.dbg.declare(metadata %struct.match** %q, metadata !519, metadata !394), !dbg !520
  %0 = load %struct.match_list*, %struct.match_list** %list.addr, align 8, !dbg !521
  %first = getelementptr inbounds %struct.match_list, %struct.match_list* %0, i32 0, i32 0, !dbg !523
  %1 = load %struct.match*, %struct.match** %first, align 8, !dbg !523
  store %struct.match* %1, %struct.match** %p, align 8, !dbg !524
  br label %for.cond, !dbg !525

for.cond:                                         ; preds = %for.body, %entry
  %2 = load %struct.match*, %struct.match** %p, align 8, !dbg !526
  %cmp = icmp ne %struct.match* %2, null, !dbg !529
  br i1 %cmp, label %for.body, label %for.end, !dbg !530

for.body:                                         ; preds = %for.cond
  %3 = load %struct.match*, %struct.match** %p, align 8, !dbg !531
  store %struct.match* %3, %struct.match** %q, align 8, !dbg !533
  %4 = load %struct.match*, %struct.match** %p, align 8, !dbg !534
  %next = getelementptr inbounds %struct.match, %struct.match* %4, i32 0, i32 0, !dbg !535
  %5 = load %struct.match*, %struct.match** %next, align 8, !dbg !535
  store %struct.match* %5, %struct.match** %p, align 8, !dbg !536
  %6 = load %struct.match*, %struct.match** %q, align 8, !dbg !537
  %pattern = getelementptr inbounds %struct.match, %struct.match* %6, i32 0, i32 2, !dbg !538
  call void @archive_mstring_clean(%struct.archive_mstring* %pattern), !dbg !539
  %7 = load %struct.match*, %struct.match** %q, align 8, !dbg !540
  %8 = bitcast %struct.match* %7 to i8*, !dbg !540
  call void @free(i8* %8) #7, !dbg !541
  br label %for.cond, !dbg !542

for.end:                                          ; preds = %for.cond
  ret void, !dbg !544
}

; Function Attrs: nounwind uwtable
define internal void @entry_list_free(%struct.entry_list* %list) #0 !dbg !363 {
entry:
  %list.addr = alloca %struct.entry_list*, align 8
  %p = alloca %struct.match_file*, align 8
  %q = alloca %struct.match_file*, align 8
  store %struct.entry_list* %list, %struct.entry_list** %list.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.entry_list** %list.addr, metadata !545, metadata !394), !dbg !546
  call void @llvm.dbg.declare(metadata %struct.match_file** %p, metadata !547, metadata !394), !dbg !548
  call void @llvm.dbg.declare(metadata %struct.match_file** %q, metadata !549, metadata !394), !dbg !550
  %0 = load %struct.entry_list*, %struct.entry_list** %list.addr, align 8, !dbg !551
  %first = getelementptr inbounds %struct.entry_list, %struct.entry_list* %0, i32 0, i32 0, !dbg !553
  %1 = load %struct.match_file*, %struct.match_file** %first, align 8, !dbg !553
  store %struct.match_file* %1, %struct.match_file** %p, align 8, !dbg !554
  br label %for.cond, !dbg !555

for.cond:                                         ; preds = %for.body, %entry
  %2 = load %struct.match_file*, %struct.match_file** %p, align 8, !dbg !556
  %cmp = icmp ne %struct.match_file* %2, null, !dbg !559
  br i1 %cmp, label %for.body, label %for.end, !dbg !560

for.body:                                         ; preds = %for.cond
  %3 = load %struct.match_file*, %struct.match_file** %p, align 8, !dbg !561
  store %struct.match_file* %3, %struct.match_file** %q, align 8, !dbg !563
  %4 = load %struct.match_file*, %struct.match_file** %p, align 8, !dbg !564
  %next = getelementptr inbounds %struct.match_file, %struct.match_file* %4, i32 0, i32 1, !dbg !565
  %5 = load %struct.match_file*, %struct.match_file** %next, align 8, !dbg !565
  store %struct.match_file* %5, %struct.match_file** %p, align 8, !dbg !566
  %6 = load %struct.match_file*, %struct.match_file** %q, align 8, !dbg !567
  %pathname = getelementptr inbounds %struct.match_file, %struct.match_file* %6, i32 0, i32 2, !dbg !568
  call void @archive_mstring_clean(%struct.archive_mstring* %pathname), !dbg !569
  %7 = load %struct.match_file*, %struct.match_file** %q, align 8, !dbg !570
  %8 = bitcast %struct.match_file* %7 to i8*, !dbg !570
  call void @free(i8* %8) #7, !dbg !571
  br label %for.cond, !dbg !572

for.end:                                          ; preds = %for.cond
  ret void, !dbg !574
}

; Function Attrs: nounwind
declare void @free(i8*) #2

; Function Attrs: nounwind uwtable
define i32 @archive_match_excluded(%struct.archive* %_a, %struct.archive_entry* %entry1) #0 !dbg !225 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %a = alloca %struct.archive_match*, align 8
  %r = alloca i32, align 4
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !575, metadata !394), !dbg !576
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !577, metadata !394), !dbg !578
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a, metadata !579, metadata !394), !dbg !580
  call void @llvm.dbg.declare(metadata i32* %r, metadata !581, metadata !394), !dbg !582
  br label %do.body, !dbg !583

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !584, metadata !394), !dbg !586
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !587
  %call = call i32 @__archive_check_magic(%struct.archive* %0, i32 212668873, i32 1, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.1, i32 0, i32 0)), !dbg !587
  store i32 %call, i32* %magic_test, align 4, !dbg !587
  %1 = load i32, i32* %magic_test, align 4, !dbg !587
  %cmp = icmp eq i32 %1, -30, !dbg !587
  br i1 %cmp, label %if.then, label %if.end, !dbg !587

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !589
  br label %return, !dbg !589

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !592

do.end:                                           ; preds = %if.end
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !594
  %3 = bitcast %struct.archive* %2 to %struct.archive_match*, !dbg !595
  store %struct.archive_match* %3, %struct.archive_match** %a, align 8, !dbg !596
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !597
  %cmp2 = icmp eq %struct.archive_entry* %4, null, !dbg !599
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !600

if.then3:                                         ; preds = %do.end
  %5 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !601
  %archive = getelementptr inbounds %struct.archive_match, %struct.archive_match* %5, i32 0, i32 0, !dbg !603
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 22, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.2, i32 0, i32 0)), !dbg !604
  store i32 -25, i32* %retval, align 4, !dbg !605
  br label %return, !dbg !605

if.end4:                                          ; preds = %do.end
  store i32 0, i32* %r, align 4, !dbg !606
  %6 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !607
  %setflag = getelementptr inbounds %struct.archive_match, %struct.archive_match* %6, i32 0, i32 1, !dbg !609
  %7 = load i32, i32* %setflag, align 8, !dbg !609
  %and = and i32 %7, 1, !dbg !610
  %tobool = icmp ne i32 %and, 0, !dbg !610
  br i1 %tobool, label %if.then5, label %if.end11, !dbg !611

if.then5:                                         ; preds = %if.end4
  %8 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !612
  %9 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !614
  %call6 = call i8* @archive_entry_pathname(%struct.archive_entry* %9), !dbg !615
  %call7 = call i32 @path_excluded(%struct.archive_match* %8, i32 1, i8* %call6), !dbg !616
  store i32 %call7, i32* %r, align 4, !dbg !618
  %10 = load i32, i32* %r, align 4, !dbg !619
  %cmp8 = icmp ne i32 %10, 0, !dbg !621
  br i1 %cmp8, label %if.then9, label %if.end10, !dbg !622

if.then9:                                         ; preds = %if.then5
  %11 = load i32, i32* %r, align 4, !dbg !623
  store i32 %11, i32* %retval, align 4, !dbg !624
  br label %return, !dbg !624

if.end10:                                         ; preds = %if.then5
  br label %if.end11, !dbg !625

if.end11:                                         ; preds = %if.end10, %if.end4
  %12 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !626
  %setflag12 = getelementptr inbounds %struct.archive_match, %struct.archive_match* %12, i32 0, i32 1, !dbg !628
  %13 = load i32, i32* %setflag12, align 8, !dbg !628
  %and13 = and i32 %13, 2, !dbg !629
  %tobool14 = icmp ne i32 %and13, 0, !dbg !629
  br i1 %tobool14, label %if.then15, label %if.end20, !dbg !630

if.then15:                                        ; preds = %if.end11
  %14 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !631
  %15 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !633
  %call16 = call i32 @time_excluded(%struct.archive_match* %14, %struct.archive_entry* %15), !dbg !634
  store i32 %call16, i32* %r, align 4, !dbg !635
  %16 = load i32, i32* %r, align 4, !dbg !636
  %cmp17 = icmp ne i32 %16, 0, !dbg !638
  br i1 %cmp17, label %if.then18, label %if.end19, !dbg !639

if.then18:                                        ; preds = %if.then15
  %17 = load i32, i32* %r, align 4, !dbg !640
  store i32 %17, i32* %retval, align 4, !dbg !641
  br label %return, !dbg !641

if.end19:                                         ; preds = %if.then15
  br label %if.end20, !dbg !642

if.end20:                                         ; preds = %if.end19, %if.end11
  %18 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !643
  %setflag21 = getelementptr inbounds %struct.archive_match, %struct.archive_match* %18, i32 0, i32 1, !dbg !645
  %19 = load i32, i32* %setflag21, align 8, !dbg !645
  %and22 = and i32 %19, 4, !dbg !646
  %tobool23 = icmp ne i32 %and22, 0, !dbg !646
  br i1 %tobool23, label %if.then24, label %if.end26, !dbg !647

if.then24:                                        ; preds = %if.end20
  %20 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !648
  %21 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !649
  %call25 = call i32 @owner_excluded(%struct.archive_match* %20, %struct.archive_entry* %21), !dbg !650
  store i32 %call25, i32* %r, align 4, !dbg !651
  br label %if.end26, !dbg !652

if.end26:                                         ; preds = %if.then24, %if.end20
  %22 = load i32, i32* %r, align 4, !dbg !653
  store i32 %22, i32* %retval, align 4, !dbg !654
  br label %return, !dbg !654

return:                                           ; preds = %if.end26, %if.then18, %if.then9, %if.then3, %if.then
  %23 = load i32, i32* %retval, align 4, !dbg !655
  ret i32 %23, !dbg !655
}

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #3

; Function Attrs: nounwind uwtable
define internal i32 @path_excluded(%struct.archive_match* %a, i32 %mbs, i8* %pathname) #0 !dbg !294 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_match*, align 8
  %mbs.addr = alloca i32, align 4
  %pathname.addr = alloca i8*, align 8
  %match = alloca %struct.match*, align 8
  %matched = alloca %struct.match*, align 8
  %r = alloca i32, align 4
  store %struct.archive_match* %a, %struct.archive_match** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a.addr, metadata !656, metadata !394), !dbg !657
  store i32 %mbs, i32* %mbs.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %mbs.addr, metadata !658, metadata !394), !dbg !659
  store i8* %pathname, i8** %pathname.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %pathname.addr, metadata !660, metadata !394), !dbg !661
  call void @llvm.dbg.declare(metadata %struct.match** %match, metadata !662, metadata !394), !dbg !663
  call void @llvm.dbg.declare(metadata %struct.match** %matched, metadata !664, metadata !394), !dbg !665
  call void @llvm.dbg.declare(metadata i32* %r, metadata !666, metadata !394), !dbg !667
  %0 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !668
  %cmp = icmp eq %struct.archive_match* %0, null, !dbg !670
  br i1 %cmp, label %if.then, label %if.end, !dbg !671

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !672
  br label %return, !dbg !672

if.end:                                           ; preds = %entry
  store %struct.match* null, %struct.match** %matched, align 8, !dbg !673
  %1 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !674
  %inclusions = getelementptr inbounds %struct.archive_match, %struct.archive_match* %1, i32 0, i32 3, !dbg !676
  %first = getelementptr inbounds %struct.match_list, %struct.match_list* %inclusions, i32 0, i32 0, !dbg !677
  %2 = load %struct.match*, %struct.match** %first, align 8, !dbg !677
  store %struct.match* %2, %struct.match** %match, align 8, !dbg !678
  br label %for.cond, !dbg !679

for.cond:                                         ; preds = %for.inc, %if.end
  %3 = load %struct.match*, %struct.match** %match, align 8, !dbg !680
  %cmp1 = icmp ne %struct.match* %3, null, !dbg !683
  br i1 %cmp1, label %for.body, label %for.end, !dbg !684

for.body:                                         ; preds = %for.cond
  %4 = load %struct.match*, %struct.match** %match, align 8, !dbg !685
  %matches = getelementptr inbounds %struct.match, %struct.match* %4, i32 0, i32 1, !dbg !688
  %5 = load i32, i32* %matches, align 8, !dbg !688
  %cmp2 = icmp eq i32 %5, 0, !dbg !689
  br i1 %cmp2, label %land.lhs.true, label %if.end10, !dbg !690

land.lhs.true:                                    ; preds = %for.body
  %6 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !691
  %7 = load %struct.match*, %struct.match** %match, align 8, !dbg !692
  %8 = load i32, i32* %mbs.addr, align 4, !dbg !693
  %9 = load i8*, i8** %pathname.addr, align 8, !dbg !694
  %call = call i32 @match_path_inclusion(%struct.archive_match* %6, %struct.match* %7, i32 %8, i8* %9), !dbg !695
  store i32 %call, i32* %r, align 4, !dbg !696
  %cmp3 = icmp ne i32 %call, 0, !dbg !697
  br i1 %cmp3, label %if.then4, label %if.end10, !dbg !698

if.then4:                                         ; preds = %land.lhs.true
  %10 = load i32, i32* %r, align 4, !dbg !700
  %cmp5 = icmp slt i32 %10, 0, !dbg !703
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !704

if.then6:                                         ; preds = %if.then4
  %11 = load i32, i32* %r, align 4, !dbg !705
  store i32 %11, i32* %retval, align 4, !dbg !706
  br label %return, !dbg !706

if.end7:                                          ; preds = %if.then4
  %12 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !707
  %inclusions8 = getelementptr inbounds %struct.archive_match, %struct.archive_match* %12, i32 0, i32 3, !dbg !708
  %unmatched_count = getelementptr inbounds %struct.match_list, %struct.match_list* %inclusions8, i32 0, i32 3, !dbg !709
  %13 = load i32, i32* %unmatched_count, align 4, !dbg !710
  %dec = add nsw i32 %13, -1, !dbg !710
  store i32 %dec, i32* %unmatched_count, align 4, !dbg !710
  %14 = load %struct.match*, %struct.match** %match, align 8, !dbg !711
  %matches9 = getelementptr inbounds %struct.match, %struct.match* %14, i32 0, i32 1, !dbg !712
  %15 = load i32, i32* %matches9, align 8, !dbg !713
  %inc = add nsw i32 %15, 1, !dbg !713
  store i32 %inc, i32* %matches9, align 8, !dbg !713
  %16 = load %struct.match*, %struct.match** %match, align 8, !dbg !714
  store %struct.match* %16, %struct.match** %matched, align 8, !dbg !715
  br label %if.end10, !dbg !716

if.end10:                                         ; preds = %if.end7, %land.lhs.true, %for.body
  br label %for.inc, !dbg !717

for.inc:                                          ; preds = %if.end10
  %17 = load %struct.match*, %struct.match** %match, align 8, !dbg !718
  %next = getelementptr inbounds %struct.match, %struct.match* %17, i32 0, i32 0, !dbg !719
  %18 = load %struct.match*, %struct.match** %next, align 8, !dbg !719
  store %struct.match* %18, %struct.match** %match, align 8, !dbg !720
  br label %for.cond, !dbg !721

for.end:                                          ; preds = %for.cond
  %19 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !723
  %exclusions = getelementptr inbounds %struct.archive_match, %struct.archive_match* %19, i32 0, i32 2, !dbg !725
  %first11 = getelementptr inbounds %struct.match_list, %struct.match_list* %exclusions, i32 0, i32 0, !dbg !726
  %20 = load %struct.match*, %struct.match** %first11, align 8, !dbg !726
  store %struct.match* %20, %struct.match** %match, align 8, !dbg !727
  br label %for.cond12, !dbg !728

for.cond12:                                       ; preds = %for.inc18, %for.end
  %21 = load %struct.match*, %struct.match** %match, align 8, !dbg !729
  %cmp13 = icmp ne %struct.match* %21, null, !dbg !732
  br i1 %cmp13, label %for.body14, label %for.end20, !dbg !733

for.body14:                                       ; preds = %for.cond12
  %22 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !734
  %23 = load %struct.match*, %struct.match** %match, align 8, !dbg !736
  %24 = load i32, i32* %mbs.addr, align 4, !dbg !737
  %25 = load i8*, i8** %pathname.addr, align 8, !dbg !738
  %call15 = call i32 @match_path_exclusion(%struct.archive_match* %22, %struct.match* %23, i32 %24, i8* %25), !dbg !739
  store i32 %call15, i32* %r, align 4, !dbg !740
  %26 = load i32, i32* %r, align 4, !dbg !741
  %tobool = icmp ne i32 %26, 0, !dbg !741
  br i1 %tobool, label %if.then16, label %if.end17, !dbg !743

if.then16:                                        ; preds = %for.body14
  %27 = load i32, i32* %r, align 4, !dbg !744
  store i32 %27, i32* %retval, align 4, !dbg !745
  br label %return, !dbg !745

if.end17:                                         ; preds = %for.body14
  br label %for.inc18, !dbg !746

for.inc18:                                        ; preds = %if.end17
  %28 = load %struct.match*, %struct.match** %match, align 8, !dbg !747
  %next19 = getelementptr inbounds %struct.match, %struct.match* %28, i32 0, i32 0, !dbg !748
  %29 = load %struct.match*, %struct.match** %next19, align 8, !dbg !748
  store %struct.match* %29, %struct.match** %match, align 8, !dbg !749
  br label %for.cond12, !dbg !750

for.end20:                                        ; preds = %for.cond12
  %30 = load %struct.match*, %struct.match** %matched, align 8, !dbg !752
  %cmp21 = icmp ne %struct.match* %30, null, !dbg !754
  br i1 %cmp21, label %if.then22, label %if.end23, !dbg !755

if.then22:                                        ; preds = %for.end20
  store i32 0, i32* %retval, align 4, !dbg !756
  br label %return, !dbg !756

if.end23:                                         ; preds = %for.end20
  %31 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !757
  %inclusions24 = getelementptr inbounds %struct.archive_match, %struct.archive_match* %31, i32 0, i32 3, !dbg !759
  %first25 = getelementptr inbounds %struct.match_list, %struct.match_list* %inclusions24, i32 0, i32 0, !dbg !760
  %32 = load %struct.match*, %struct.match** %first25, align 8, !dbg !760
  store %struct.match* %32, %struct.match** %match, align 8, !dbg !761
  br label %for.cond26, !dbg !762

for.cond26:                                       ; preds = %for.inc41, %if.end23
  %33 = load %struct.match*, %struct.match** %match, align 8, !dbg !763
  %cmp27 = icmp ne %struct.match* %33, null, !dbg !766
  br i1 %cmp27, label %for.body28, label %for.end43, !dbg !767

for.body28:                                       ; preds = %for.cond26
  %34 = load %struct.match*, %struct.match** %match, align 8, !dbg !768
  %matches29 = getelementptr inbounds %struct.match, %struct.match* %34, i32 0, i32 1, !dbg !771
  %35 = load i32, i32* %matches29, align 8, !dbg !771
  %cmp30 = icmp sgt i32 %35, 0, !dbg !772
  br i1 %cmp30, label %land.lhs.true31, label %if.end40, !dbg !773

land.lhs.true31:                                  ; preds = %for.body28
  %36 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !774
  %37 = load %struct.match*, %struct.match** %match, align 8, !dbg !775
  %38 = load i32, i32* %mbs.addr, align 4, !dbg !776
  %39 = load i8*, i8** %pathname.addr, align 8, !dbg !777
  %call32 = call i32 @match_path_inclusion(%struct.archive_match* %36, %struct.match* %37, i32 %38, i8* %39), !dbg !778
  store i32 %call32, i32* %r, align 4, !dbg !779
  %cmp33 = icmp ne i32 %call32, 0, !dbg !780
  br i1 %cmp33, label %if.then34, label %if.end40, !dbg !781

if.then34:                                        ; preds = %land.lhs.true31
  %40 = load i32, i32* %r, align 4, !dbg !783
  %cmp35 = icmp slt i32 %40, 0, !dbg !786
  br i1 %cmp35, label %if.then36, label %if.end37, !dbg !787

if.then36:                                        ; preds = %if.then34
  %41 = load i32, i32* %r, align 4, !dbg !788
  store i32 %41, i32* %retval, align 4, !dbg !789
  br label %return, !dbg !789

if.end37:                                         ; preds = %if.then34
  %42 = load %struct.match*, %struct.match** %match, align 8, !dbg !790
  %matches38 = getelementptr inbounds %struct.match, %struct.match* %42, i32 0, i32 1, !dbg !791
  %43 = load i32, i32* %matches38, align 8, !dbg !792
  %inc39 = add nsw i32 %43, 1, !dbg !792
  store i32 %inc39, i32* %matches38, align 8, !dbg !792
  store i32 0, i32* %retval, align 4, !dbg !793
  br label %return, !dbg !793

if.end40:                                         ; preds = %land.lhs.true31, %for.body28
  br label %for.inc41, !dbg !794

for.inc41:                                        ; preds = %if.end40
  %44 = load %struct.match*, %struct.match** %match, align 8, !dbg !795
  %next42 = getelementptr inbounds %struct.match, %struct.match* %44, i32 0, i32 0, !dbg !796
  %45 = load %struct.match*, %struct.match** %next42, align 8, !dbg !796
  store %struct.match* %45, %struct.match** %match, align 8, !dbg !797
  br label %for.cond26, !dbg !798

for.end43:                                        ; preds = %for.cond26
  %46 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !800
  %inclusions44 = getelementptr inbounds %struct.archive_match, %struct.archive_match* %46, i32 0, i32 3, !dbg !802
  %first45 = getelementptr inbounds %struct.match_list, %struct.match_list* %inclusions44, i32 0, i32 0, !dbg !803
  %47 = load %struct.match*, %struct.match** %first45, align 8, !dbg !803
  %cmp46 = icmp ne %struct.match* %47, null, !dbg !804
  br i1 %cmp46, label %if.then47, label %if.end48, !dbg !805

if.then47:                                        ; preds = %for.end43
  store i32 1, i32* %retval, align 4, !dbg !806
  br label %return, !dbg !806

if.end48:                                         ; preds = %for.end43
  store i32 0, i32* %retval, align 4, !dbg !807
  br label %return, !dbg !807

return:                                           ; preds = %if.end48, %if.then47, %if.end37, %if.then36, %if.then22, %if.then16, %if.then6, %if.then
  %48 = load i32, i32* %retval, align 4, !dbg !808
  ret i32 %48, !dbg !808
}

declare i8* @archive_entry_pathname(%struct.archive_entry*) #3

; Function Attrs: nounwind uwtable
define internal i32 @time_excluded(%struct.archive_match* %a, %struct.archive_entry* %entry1) #0 !dbg !372 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_match*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %f = alloca %struct.match_file*, align 8
  %pathname = alloca i8*, align 8
  %sec = alloca i64, align 8
  %nsec = alloca i64, align 8
  store %struct.archive_match* %a, %struct.archive_match** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a.addr, metadata !809, metadata !394), !dbg !810
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !811, metadata !394), !dbg !812
  call void @llvm.dbg.declare(metadata %struct.match_file** %f, metadata !813, metadata !394), !dbg !814
  call void @llvm.dbg.declare(metadata i8** %pathname, metadata !815, metadata !394), !dbg !816
  call void @llvm.dbg.declare(metadata i64* %sec, metadata !817, metadata !394), !dbg !818
  call void @llvm.dbg.declare(metadata i64* %nsec, metadata !819, metadata !394), !dbg !820
  %0 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !821
  %newer_ctime_filter = getelementptr inbounds %struct.archive_match, %struct.archive_match* %0, i32 0, i32 8, !dbg !823
  %1 = load i32, i32* %newer_ctime_filter, align 8, !dbg !823
  %tobool = icmp ne i32 %1, 0, !dbg !821
  br i1 %tobool, label %if.then, label %if.end28, !dbg !824

if.then:                                          ; preds = %entry
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !825
  %call = call i32 @archive_entry_ctime_is_set(%struct.archive_entry* %2), !dbg !828
  %tobool2 = icmp ne i32 %call, 0, !dbg !828
  br i1 %tobool2, label %if.then3, label %if.else, !dbg !829

if.then3:                                         ; preds = %if.then
  %3 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !830
  %call4 = call i64 @archive_entry_ctime(%struct.archive_entry* %3), !dbg !831
  store i64 %call4, i64* %sec, align 8, !dbg !832
  br label %if.end, !dbg !833

if.else:                                          ; preds = %if.then
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !834
  %call5 = call i64 @archive_entry_mtime(%struct.archive_entry* %4), !dbg !835
  store i64 %call5, i64* %sec, align 8, !dbg !836
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then3
  %5 = load i64, i64* %sec, align 8, !dbg !837
  %6 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !839
  %newer_ctime_sec = getelementptr inbounds %struct.archive_match, %struct.archive_match* %6, i32 0, i32 9, !dbg !840
  %7 = load i64, i64* %newer_ctime_sec, align 8, !dbg !840
  %cmp = icmp slt i64 %5, %7, !dbg !841
  br i1 %cmp, label %if.then6, label %if.end7, !dbg !842

if.then6:                                         ; preds = %if.end
  store i32 1, i32* %retval, align 4, !dbg !843
  br label %return, !dbg !843

if.end7:                                          ; preds = %if.end
  %8 = load i64, i64* %sec, align 8, !dbg !844
  %9 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !846
  %newer_ctime_sec8 = getelementptr inbounds %struct.archive_match, %struct.archive_match* %9, i32 0, i32 9, !dbg !847
  %10 = load i64, i64* %newer_ctime_sec8, align 8, !dbg !847
  %cmp9 = icmp eq i64 %8, %10, !dbg !848
  br i1 %cmp9, label %if.then10, label %if.end27, !dbg !849

if.then10:                                        ; preds = %if.end7
  %11 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !850
  %call11 = call i32 @archive_entry_ctime_is_set(%struct.archive_entry* %11), !dbg !853
  %tobool12 = icmp ne i32 %call11, 0, !dbg !853
  br i1 %tobool12, label %if.then13, label %if.else15, !dbg !854

if.then13:                                        ; preds = %if.then10
  %12 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !855
  %call14 = call i64 @archive_entry_ctime_nsec(%struct.archive_entry* %12), !dbg !856
  store i64 %call14, i64* %nsec, align 8, !dbg !857
  br label %if.end17, !dbg !858

if.else15:                                        ; preds = %if.then10
  %13 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !859
  %call16 = call i64 @archive_entry_mtime_nsec(%struct.archive_entry* %13), !dbg !860
  store i64 %call16, i64* %nsec, align 8, !dbg !861
  br label %if.end17

if.end17:                                         ; preds = %if.else15, %if.then13
  %14 = load i64, i64* %nsec, align 8, !dbg !862
  %15 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !864
  %newer_ctime_nsec = getelementptr inbounds %struct.archive_match, %struct.archive_match* %15, i32 0, i32 10, !dbg !865
  %16 = load i64, i64* %newer_ctime_nsec, align 8, !dbg !865
  %cmp18 = icmp slt i64 %14, %16, !dbg !866
  br i1 %cmp18, label %if.then19, label %if.end20, !dbg !867

if.then19:                                        ; preds = %if.end17
  store i32 1, i32* %retval, align 4, !dbg !868
  br label %return, !dbg !868

if.end20:                                         ; preds = %if.end17
  %17 = load i64, i64* %nsec, align 8, !dbg !869
  %18 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !871
  %newer_ctime_nsec21 = getelementptr inbounds %struct.archive_match, %struct.archive_match* %18, i32 0, i32 10, !dbg !872
  %19 = load i64, i64* %newer_ctime_nsec21, align 8, !dbg !872
  %cmp22 = icmp eq i64 %17, %19, !dbg !873
  br i1 %cmp22, label %land.lhs.true, label %if.end26, !dbg !874

land.lhs.true:                                    ; preds = %if.end20
  %20 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !875
  %newer_ctime_filter23 = getelementptr inbounds %struct.archive_match, %struct.archive_match* %20, i32 0, i32 8, !dbg !876
  %21 = load i32, i32* %newer_ctime_filter23, align 8, !dbg !876
  %and = and i32 %21, 16, !dbg !877
  %cmp24 = icmp eq i32 %and, 0, !dbg !878
  br i1 %cmp24, label %if.then25, label %if.end26, !dbg !879

if.then25:                                        ; preds = %land.lhs.true
  store i32 1, i32* %retval, align 4, !dbg !881
  br label %return, !dbg !881

if.end26:                                         ; preds = %land.lhs.true, %if.end20
  br label %if.end27, !dbg !882

if.end27:                                         ; preds = %if.end26, %if.end7
  br label %if.end28, !dbg !883

if.end28:                                         ; preds = %if.end27, %entry
  %22 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !884
  %older_ctime_filter = getelementptr inbounds %struct.archive_match, %struct.archive_match* %22, i32 0, i32 14, !dbg !886
  %23 = load i32, i32* %older_ctime_filter, align 8, !dbg !886
  %tobool29 = icmp ne i32 %23, 0, !dbg !884
  br i1 %tobool29, label %if.then30, label %if.end63, !dbg !887

if.then30:                                        ; preds = %if.end28
  %24 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !888
  %call31 = call i32 @archive_entry_ctime_is_set(%struct.archive_entry* %24), !dbg !891
  %tobool32 = icmp ne i32 %call31, 0, !dbg !891
  br i1 %tobool32, label %if.then33, label %if.else35, !dbg !892

if.then33:                                        ; preds = %if.then30
  %25 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !893
  %call34 = call i64 @archive_entry_ctime(%struct.archive_entry* %25), !dbg !894
  store i64 %call34, i64* %sec, align 8, !dbg !895
  br label %if.end37, !dbg !896

if.else35:                                        ; preds = %if.then30
  %26 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !897
  %call36 = call i64 @archive_entry_mtime(%struct.archive_entry* %26), !dbg !898
  store i64 %call36, i64* %sec, align 8, !dbg !899
  br label %if.end37

if.end37:                                         ; preds = %if.else35, %if.then33
  %27 = load i64, i64* %sec, align 8, !dbg !900
  %28 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !902
  %older_ctime_sec = getelementptr inbounds %struct.archive_match, %struct.archive_match* %28, i32 0, i32 15, !dbg !903
  %29 = load i64, i64* %older_ctime_sec, align 8, !dbg !903
  %cmp38 = icmp sgt i64 %27, %29, !dbg !904
  br i1 %cmp38, label %if.then39, label %if.end40, !dbg !905

if.then39:                                        ; preds = %if.end37
  store i32 1, i32* %retval, align 4, !dbg !906
  br label %return, !dbg !906

if.end40:                                         ; preds = %if.end37
  %30 = load i64, i64* %sec, align 8, !dbg !907
  %31 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !909
  %older_ctime_sec41 = getelementptr inbounds %struct.archive_match, %struct.archive_match* %31, i32 0, i32 15, !dbg !910
  %32 = load i64, i64* %older_ctime_sec41, align 8, !dbg !910
  %cmp42 = icmp eq i64 %30, %32, !dbg !911
  br i1 %cmp42, label %if.then43, label %if.end62, !dbg !912

if.then43:                                        ; preds = %if.end40
  %33 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !913
  %call44 = call i32 @archive_entry_ctime_is_set(%struct.archive_entry* %33), !dbg !916
  %tobool45 = icmp ne i32 %call44, 0, !dbg !916
  br i1 %tobool45, label %if.then46, label %if.else48, !dbg !917

if.then46:                                        ; preds = %if.then43
  %34 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !918
  %call47 = call i64 @archive_entry_ctime_nsec(%struct.archive_entry* %34), !dbg !919
  store i64 %call47, i64* %nsec, align 8, !dbg !920
  br label %if.end50, !dbg !921

if.else48:                                        ; preds = %if.then43
  %35 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !922
  %call49 = call i64 @archive_entry_mtime_nsec(%struct.archive_entry* %35), !dbg !923
  store i64 %call49, i64* %nsec, align 8, !dbg !924
  br label %if.end50

if.end50:                                         ; preds = %if.else48, %if.then46
  %36 = load i64, i64* %nsec, align 8, !dbg !925
  %37 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !927
  %older_ctime_nsec = getelementptr inbounds %struct.archive_match, %struct.archive_match* %37, i32 0, i32 16, !dbg !928
  %38 = load i64, i64* %older_ctime_nsec, align 8, !dbg !928
  %cmp51 = icmp sgt i64 %36, %38, !dbg !929
  br i1 %cmp51, label %if.then52, label %if.end53, !dbg !930

if.then52:                                        ; preds = %if.end50
  store i32 1, i32* %retval, align 4, !dbg !931
  br label %return, !dbg !931

if.end53:                                         ; preds = %if.end50
  %39 = load i64, i64* %nsec, align 8, !dbg !932
  %40 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !934
  %older_ctime_nsec54 = getelementptr inbounds %struct.archive_match, %struct.archive_match* %40, i32 0, i32 16, !dbg !935
  %41 = load i64, i64* %older_ctime_nsec54, align 8, !dbg !935
  %cmp55 = icmp eq i64 %39, %41, !dbg !936
  br i1 %cmp55, label %land.lhs.true56, label %if.end61, !dbg !937

land.lhs.true56:                                  ; preds = %if.end53
  %42 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !938
  %older_ctime_filter57 = getelementptr inbounds %struct.archive_match, %struct.archive_match* %42, i32 0, i32 14, !dbg !939
  %43 = load i32, i32* %older_ctime_filter57, align 8, !dbg !939
  %and58 = and i32 %43, 16, !dbg !940
  %cmp59 = icmp eq i32 %and58, 0, !dbg !941
  br i1 %cmp59, label %if.then60, label %if.end61, !dbg !942

if.then60:                                        ; preds = %land.lhs.true56
  store i32 1, i32* %retval, align 4, !dbg !944
  br label %return, !dbg !944

if.end61:                                         ; preds = %land.lhs.true56, %if.end53
  br label %if.end62, !dbg !945

if.end62:                                         ; preds = %if.end61, %if.end40
  br label %if.end63, !dbg !946

if.end63:                                         ; preds = %if.end62, %if.end28
  %44 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !947
  %newer_mtime_filter = getelementptr inbounds %struct.archive_match, %struct.archive_match* %44, i32 0, i32 5, !dbg !949
  %45 = load i32, i32* %newer_mtime_filter, align 8, !dbg !949
  %tobool64 = icmp ne i32 %45, 0, !dbg !947
  br i1 %tobool64, label %if.then65, label %if.end86, !dbg !950

if.then65:                                        ; preds = %if.end63
  %46 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !951
  %call66 = call i64 @archive_entry_mtime(%struct.archive_entry* %46), !dbg !953
  store i64 %call66, i64* %sec, align 8, !dbg !954
  %47 = load i64, i64* %sec, align 8, !dbg !955
  %48 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !957
  %newer_mtime_sec = getelementptr inbounds %struct.archive_match, %struct.archive_match* %48, i32 0, i32 6, !dbg !958
  %49 = load i64, i64* %newer_mtime_sec, align 8, !dbg !958
  %cmp67 = icmp slt i64 %47, %49, !dbg !959
  br i1 %cmp67, label %if.then68, label %if.end69, !dbg !960

if.then68:                                        ; preds = %if.then65
  store i32 1, i32* %retval, align 4, !dbg !961
  br label %return, !dbg !961

if.end69:                                         ; preds = %if.then65
  %50 = load i64, i64* %sec, align 8, !dbg !962
  %51 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !964
  %newer_mtime_sec70 = getelementptr inbounds %struct.archive_match, %struct.archive_match* %51, i32 0, i32 6, !dbg !965
  %52 = load i64, i64* %newer_mtime_sec70, align 8, !dbg !965
  %cmp71 = icmp eq i64 %50, %52, !dbg !966
  br i1 %cmp71, label %if.then72, label %if.end85, !dbg !967

if.then72:                                        ; preds = %if.end69
  %53 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !968
  %call73 = call i64 @archive_entry_mtime_nsec(%struct.archive_entry* %53), !dbg !970
  store i64 %call73, i64* %nsec, align 8, !dbg !971
  %54 = load i64, i64* %nsec, align 8, !dbg !972
  %55 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !974
  %newer_mtime_nsec = getelementptr inbounds %struct.archive_match, %struct.archive_match* %55, i32 0, i32 7, !dbg !975
  %56 = load i64, i64* %newer_mtime_nsec, align 8, !dbg !975
  %cmp74 = icmp slt i64 %54, %56, !dbg !976
  br i1 %cmp74, label %if.then75, label %if.end76, !dbg !977

if.then75:                                        ; preds = %if.then72
  store i32 1, i32* %retval, align 4, !dbg !978
  br label %return, !dbg !978

if.end76:                                         ; preds = %if.then72
  %57 = load i64, i64* %nsec, align 8, !dbg !979
  %58 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !981
  %newer_mtime_nsec77 = getelementptr inbounds %struct.archive_match, %struct.archive_match* %58, i32 0, i32 7, !dbg !982
  %59 = load i64, i64* %newer_mtime_nsec77, align 8, !dbg !982
  %cmp78 = icmp eq i64 %57, %59, !dbg !983
  br i1 %cmp78, label %land.lhs.true79, label %if.end84, !dbg !984

land.lhs.true79:                                  ; preds = %if.end76
  %60 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !985
  %newer_mtime_filter80 = getelementptr inbounds %struct.archive_match, %struct.archive_match* %60, i32 0, i32 5, !dbg !986
  %61 = load i32, i32* %newer_mtime_filter80, align 8, !dbg !986
  %and81 = and i32 %61, 16, !dbg !987
  %cmp82 = icmp eq i32 %and81, 0, !dbg !988
  br i1 %cmp82, label %if.then83, label %if.end84, !dbg !989

if.then83:                                        ; preds = %land.lhs.true79
  store i32 1, i32* %retval, align 4, !dbg !991
  br label %return, !dbg !991

if.end84:                                         ; preds = %land.lhs.true79, %if.end76
  br label %if.end85, !dbg !992

if.end85:                                         ; preds = %if.end84, %if.end69
  br label %if.end86, !dbg !993

if.end86:                                         ; preds = %if.end85, %if.end63
  %62 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !994
  %older_mtime_filter = getelementptr inbounds %struct.archive_match, %struct.archive_match* %62, i32 0, i32 11, !dbg !996
  %63 = load i32, i32* %older_mtime_filter, align 8, !dbg !996
  %tobool87 = icmp ne i32 %63, 0, !dbg !994
  br i1 %tobool87, label %if.then88, label %if.end109, !dbg !997

if.then88:                                        ; preds = %if.end86
  %64 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !998
  %call89 = call i64 @archive_entry_mtime(%struct.archive_entry* %64), !dbg !1000
  store i64 %call89, i64* %sec, align 8, !dbg !1001
  %65 = load i64, i64* %sec, align 8, !dbg !1002
  %66 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !1004
  %older_mtime_sec = getelementptr inbounds %struct.archive_match, %struct.archive_match* %66, i32 0, i32 12, !dbg !1005
  %67 = load i64, i64* %older_mtime_sec, align 8, !dbg !1005
  %cmp90 = icmp sgt i64 %65, %67, !dbg !1006
  br i1 %cmp90, label %if.then91, label %if.end92, !dbg !1007

if.then91:                                        ; preds = %if.then88
  store i32 1, i32* %retval, align 4, !dbg !1008
  br label %return, !dbg !1008

if.end92:                                         ; preds = %if.then88
  %68 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1009
  %call93 = call i64 @archive_entry_mtime_nsec(%struct.archive_entry* %68), !dbg !1010
  store i64 %call93, i64* %nsec, align 8, !dbg !1011
  %69 = load i64, i64* %sec, align 8, !dbg !1012
  %70 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !1014
  %older_mtime_sec94 = getelementptr inbounds %struct.archive_match, %struct.archive_match* %70, i32 0, i32 12, !dbg !1015
  %71 = load i64, i64* %older_mtime_sec94, align 8, !dbg !1015
  %cmp95 = icmp eq i64 %69, %71, !dbg !1016
  br i1 %cmp95, label %if.then96, label %if.end108, !dbg !1017

if.then96:                                        ; preds = %if.end92
  %72 = load i64, i64* %nsec, align 8, !dbg !1018
  %73 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !1021
  %older_mtime_nsec = getelementptr inbounds %struct.archive_match, %struct.archive_match* %73, i32 0, i32 13, !dbg !1022
  %74 = load i64, i64* %older_mtime_nsec, align 8, !dbg !1022
  %cmp97 = icmp sgt i64 %72, %74, !dbg !1023
  br i1 %cmp97, label %if.then98, label %if.end99, !dbg !1024

if.then98:                                        ; preds = %if.then96
  store i32 1, i32* %retval, align 4, !dbg !1025
  br label %return, !dbg !1025

if.end99:                                         ; preds = %if.then96
  %75 = load i64, i64* %nsec, align 8, !dbg !1026
  %76 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !1028
  %older_mtime_nsec100 = getelementptr inbounds %struct.archive_match, %struct.archive_match* %76, i32 0, i32 13, !dbg !1029
  %77 = load i64, i64* %older_mtime_nsec100, align 8, !dbg !1029
  %cmp101 = icmp eq i64 %75, %77, !dbg !1030
  br i1 %cmp101, label %land.lhs.true102, label %if.end107, !dbg !1031

land.lhs.true102:                                 ; preds = %if.end99
  %78 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !1032
  %older_mtime_filter103 = getelementptr inbounds %struct.archive_match, %struct.archive_match* %78, i32 0, i32 11, !dbg !1033
  %79 = load i32, i32* %older_mtime_filter103, align 8, !dbg !1033
  %and104 = and i32 %79, 16, !dbg !1034
  %cmp105 = icmp eq i32 %and104, 0, !dbg !1035
  br i1 %cmp105, label %if.then106, label %if.end107, !dbg !1036

if.then106:                                       ; preds = %land.lhs.true102
  store i32 1, i32* %retval, align 4, !dbg !1038
  br label %return, !dbg !1038

if.end107:                                        ; preds = %land.lhs.true102, %if.end99
  br label %if.end108, !dbg !1039

if.end108:                                        ; preds = %if.end107, %if.end92
  br label %if.end109, !dbg !1040

if.end109:                                        ; preds = %if.end108, %if.end86
  %80 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !1041
  %exclusion_entry_list = getelementptr inbounds %struct.archive_match, %struct.archive_match* %80, i32 0, i32 18, !dbg !1043
  %count = getelementptr inbounds %struct.entry_list, %struct.entry_list* %exclusion_entry_list, i32 0, i32 2, !dbg !1044
  %81 = load i32, i32* %count, align 8, !dbg !1044
  %cmp110 = icmp eq i32 %81, 0, !dbg !1045
  br i1 %cmp110, label %if.then111, label %if.end112, !dbg !1046

if.then111:                                       ; preds = %if.end109
  store i32 0, i32* %retval, align 4, !dbg !1047
  br label %return, !dbg !1047

if.end112:                                        ; preds = %if.end109
  %82 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1048
  %call113 = call i8* @archive_entry_pathname(%struct.archive_entry* %82), !dbg !1049
  store i8* %call113, i8** %pathname, align 8, !dbg !1050
  %83 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !1051
  %exclusion_tree = getelementptr inbounds %struct.archive_match, %struct.archive_match* %83, i32 0, i32 17, !dbg !1052
  %rbt_ops = getelementptr inbounds %struct.archive_rb_tree, %struct.archive_rb_tree* %exclusion_tree, i32 0, i32 1, !dbg !1053
  store %struct.archive_rb_tree_ops* @rb_ops_mbs, %struct.archive_rb_tree_ops** %rbt_ops, align 8, !dbg !1054
  %84 = load i8*, i8** %pathname, align 8, !dbg !1055
  %cmp114 = icmp eq i8* %84, null, !dbg !1057
  br i1 %cmp114, label %if.then115, label %if.end116, !dbg !1058

if.then115:                                       ; preds = %if.end112
  store i32 0, i32* %retval, align 4, !dbg !1059
  br label %return, !dbg !1059

if.end116:                                        ; preds = %if.end112
  %85 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !1060
  %exclusion_tree117 = getelementptr inbounds %struct.archive_match, %struct.archive_match* %85, i32 0, i32 17, !dbg !1061
  %86 = load i8*, i8** %pathname, align 8, !dbg !1062
  %call118 = call %struct.archive_rb_node* @__archive_rb_tree_find_node(%struct.archive_rb_tree* %exclusion_tree117, i8* %86), !dbg !1063
  %87 = bitcast %struct.archive_rb_node* %call118 to %struct.match_file*, !dbg !1064
  store %struct.match_file* %87, %struct.match_file** %f, align 8, !dbg !1065
  %88 = load %struct.match_file*, %struct.match_file** %f, align 8, !dbg !1066
  %cmp119 = icmp eq %struct.match_file* %88, null, !dbg !1068
  br i1 %cmp119, label %if.then120, label %if.end121, !dbg !1069

if.then120:                                       ; preds = %if.end116
  store i32 0, i32* %retval, align 4, !dbg !1070
  br label %return, !dbg !1070

if.end121:                                        ; preds = %if.end116
  %89 = load %struct.match_file*, %struct.match_file** %f, align 8, !dbg !1071
  %flag = getelementptr inbounds %struct.match_file, %struct.match_file* %89, i32 0, i32 3, !dbg !1073
  %90 = load i32, i32* %flag, align 8, !dbg !1073
  %and122 = and i32 %90, 512, !dbg !1074
  %tobool123 = icmp ne i32 %and122, 0, !dbg !1074
  br i1 %tobool123, label %if.then124, label %if.end170, !dbg !1075

if.then124:                                       ; preds = %if.end121
  %91 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1076
  %call125 = call i64 @archive_entry_ctime(%struct.archive_entry* %91), !dbg !1078
  store i64 %call125, i64* %sec, align 8, !dbg !1079
  %92 = load %struct.match_file*, %struct.match_file** %f, align 8, !dbg !1080
  %ctime_sec = getelementptr inbounds %struct.match_file, %struct.match_file* %92, i32 0, i32 6, !dbg !1082
  %93 = load i64, i64* %ctime_sec, align 8, !dbg !1082
  %94 = load i64, i64* %sec, align 8, !dbg !1083
  %cmp126 = icmp sgt i64 %93, %94, !dbg !1084
  br i1 %cmp126, label %if.then127, label %if.else133, !dbg !1085

if.then127:                                       ; preds = %if.then124
  %95 = load %struct.match_file*, %struct.match_file** %f, align 8, !dbg !1086
  %flag128 = getelementptr inbounds %struct.match_file, %struct.match_file* %95, i32 0, i32 3, !dbg !1089
  %96 = load i32, i32* %flag128, align 8, !dbg !1089
  %and129 = and i32 %96, 2, !dbg !1090
  %tobool130 = icmp ne i32 %and129, 0, !dbg !1090
  br i1 %tobool130, label %if.then131, label %if.end132, !dbg !1091

if.then131:                                       ; preds = %if.then127
  store i32 1, i32* %retval, align 4, !dbg !1092
  br label %return, !dbg !1092

if.end132:                                        ; preds = %if.then127
  br label %if.end169, !dbg !1093

if.else133:                                       ; preds = %if.then124
  %97 = load %struct.match_file*, %struct.match_file** %f, align 8, !dbg !1094
  %ctime_sec134 = getelementptr inbounds %struct.match_file, %struct.match_file* %97, i32 0, i32 6, !dbg !1097
  %98 = load i64, i64* %ctime_sec134, align 8, !dbg !1097
  %99 = load i64, i64* %sec, align 8, !dbg !1098
  %cmp135 = icmp slt i64 %98, %99, !dbg !1099
  br i1 %cmp135, label %if.then136, label %if.else142, !dbg !1094

if.then136:                                       ; preds = %if.else133
  %100 = load %struct.match_file*, %struct.match_file** %f, align 8, !dbg !1100
  %flag137 = getelementptr inbounds %struct.match_file, %struct.match_file* %100, i32 0, i32 3, !dbg !1103
  %101 = load i32, i32* %flag137, align 8, !dbg !1103
  %and138 = and i32 %101, 1, !dbg !1104
  %tobool139 = icmp ne i32 %and138, 0, !dbg !1104
  br i1 %tobool139, label %if.then140, label %if.end141, !dbg !1105

if.then140:                                       ; preds = %if.then136
  store i32 1, i32* %retval, align 4, !dbg !1106
  br label %return, !dbg !1106

if.end141:                                        ; preds = %if.then136
  br label %if.end168, !dbg !1107

if.else142:                                       ; preds = %if.else133
  %102 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1108
  %call143 = call i64 @archive_entry_ctime_nsec(%struct.archive_entry* %102), !dbg !1110
  store i64 %call143, i64* %nsec, align 8, !dbg !1111
  %103 = load %struct.match_file*, %struct.match_file** %f, align 8, !dbg !1112
  %ctime_nsec = getelementptr inbounds %struct.match_file, %struct.match_file* %103, i32 0, i32 7, !dbg !1114
  %104 = load i64, i64* %ctime_nsec, align 8, !dbg !1114
  %105 = load i64, i64* %nsec, align 8, !dbg !1115
  %cmp144 = icmp sgt i64 %104, %105, !dbg !1116
  br i1 %cmp144, label %if.then145, label %if.else151, !dbg !1117

if.then145:                                       ; preds = %if.else142
  %106 = load %struct.match_file*, %struct.match_file** %f, align 8, !dbg !1118
  %flag146 = getelementptr inbounds %struct.match_file, %struct.match_file* %106, i32 0, i32 3, !dbg !1121
  %107 = load i32, i32* %flag146, align 8, !dbg !1121
  %and147 = and i32 %107, 2, !dbg !1122
  %tobool148 = icmp ne i32 %and147, 0, !dbg !1122
  br i1 %tobool148, label %if.then149, label %if.end150, !dbg !1123

if.then149:                                       ; preds = %if.then145
  store i32 1, i32* %retval, align 4, !dbg !1124
  br label %return, !dbg !1124

if.end150:                                        ; preds = %if.then145
  br label %if.end167, !dbg !1125

if.else151:                                       ; preds = %if.else142
  %108 = load %struct.match_file*, %struct.match_file** %f, align 8, !dbg !1126
  %ctime_nsec152 = getelementptr inbounds %struct.match_file, %struct.match_file* %108, i32 0, i32 7, !dbg !1129
  %109 = load i64, i64* %ctime_nsec152, align 8, !dbg !1129
  %110 = load i64, i64* %nsec, align 8, !dbg !1130
  %cmp153 = icmp slt i64 %109, %110, !dbg !1131
  br i1 %cmp153, label %if.then154, label %if.else160, !dbg !1126

if.then154:                                       ; preds = %if.else151
  %111 = load %struct.match_file*, %struct.match_file** %f, align 8, !dbg !1132
  %flag155 = getelementptr inbounds %struct.match_file, %struct.match_file* %111, i32 0, i32 3, !dbg !1135
  %112 = load i32, i32* %flag155, align 8, !dbg !1135
  %and156 = and i32 %112, 1, !dbg !1136
  %tobool157 = icmp ne i32 %and156, 0, !dbg !1136
  br i1 %tobool157, label %if.then158, label %if.end159, !dbg !1137

if.then158:                                       ; preds = %if.then154
  store i32 1, i32* %retval, align 4, !dbg !1138
  br label %return, !dbg !1138

if.end159:                                        ; preds = %if.then154
  br label %if.end166, !dbg !1139

if.else160:                                       ; preds = %if.else151
  %113 = load %struct.match_file*, %struct.match_file** %f, align 8, !dbg !1140
  %flag161 = getelementptr inbounds %struct.match_file, %struct.match_file* %113, i32 0, i32 3, !dbg !1143
  %114 = load i32, i32* %flag161, align 8, !dbg !1143
  %and162 = and i32 %114, 16, !dbg !1144
  %tobool163 = icmp ne i32 %and162, 0, !dbg !1144
  br i1 %tobool163, label %if.then164, label %if.end165, !dbg !1140

if.then164:                                       ; preds = %if.else160
  store i32 1, i32* %retval, align 4, !dbg !1145
  br label %return, !dbg !1145

if.end165:                                        ; preds = %if.else160
  br label %if.end166

if.end166:                                        ; preds = %if.end165, %if.end159
  br label %if.end167

if.end167:                                        ; preds = %if.end166, %if.end150
  br label %if.end168

if.end168:                                        ; preds = %if.end167, %if.end141
  br label %if.end169

if.end169:                                        ; preds = %if.end168, %if.end132
  br label %if.end170, !dbg !1146

if.end170:                                        ; preds = %if.end169, %if.end121
  %115 = load %struct.match_file*, %struct.match_file** %f, align 8, !dbg !1147
  %flag171 = getelementptr inbounds %struct.match_file, %struct.match_file* %115, i32 0, i32 3, !dbg !1149
  %116 = load i32, i32* %flag171, align 8, !dbg !1149
  %and172 = and i32 %116, 256, !dbg !1150
  %tobool173 = icmp ne i32 %and172, 0, !dbg !1150
  br i1 %tobool173, label %if.then174, label %if.end220, !dbg !1151

if.then174:                                       ; preds = %if.end170
  %117 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1152
  %call175 = call i64 @archive_entry_mtime(%struct.archive_entry* %117), !dbg !1154
  store i64 %call175, i64* %sec, align 8, !dbg !1155
  %118 = load %struct.match_file*, %struct.match_file** %f, align 8, !dbg !1156
  %mtime_sec = getelementptr inbounds %struct.match_file, %struct.match_file* %118, i32 0, i32 4, !dbg !1158
  %119 = load i64, i64* %mtime_sec, align 8, !dbg !1158
  %120 = load i64, i64* %sec, align 8, !dbg !1159
  %cmp176 = icmp sgt i64 %119, %120, !dbg !1160
  br i1 %cmp176, label %if.then177, label %if.else183, !dbg !1161

if.then177:                                       ; preds = %if.then174
  %121 = load %struct.match_file*, %struct.match_file** %f, align 8, !dbg !1162
  %flag178 = getelementptr inbounds %struct.match_file, %struct.match_file* %121, i32 0, i32 3, !dbg !1165
  %122 = load i32, i32* %flag178, align 8, !dbg !1165
  %and179 = and i32 %122, 2, !dbg !1166
  %tobool180 = icmp ne i32 %and179, 0, !dbg !1166
  br i1 %tobool180, label %if.then181, label %if.end182, !dbg !1167

if.then181:                                       ; preds = %if.then177
  store i32 1, i32* %retval, align 4, !dbg !1168
  br label %return, !dbg !1168

if.end182:                                        ; preds = %if.then177
  br label %if.end219, !dbg !1169

if.else183:                                       ; preds = %if.then174
  %123 = load %struct.match_file*, %struct.match_file** %f, align 8, !dbg !1170
  %mtime_sec184 = getelementptr inbounds %struct.match_file, %struct.match_file* %123, i32 0, i32 4, !dbg !1173
  %124 = load i64, i64* %mtime_sec184, align 8, !dbg !1173
  %125 = load i64, i64* %sec, align 8, !dbg !1174
  %cmp185 = icmp slt i64 %124, %125, !dbg !1175
  br i1 %cmp185, label %if.then186, label %if.else192, !dbg !1170

if.then186:                                       ; preds = %if.else183
  %126 = load %struct.match_file*, %struct.match_file** %f, align 8, !dbg !1176
  %flag187 = getelementptr inbounds %struct.match_file, %struct.match_file* %126, i32 0, i32 3, !dbg !1179
  %127 = load i32, i32* %flag187, align 8, !dbg !1179
  %and188 = and i32 %127, 1, !dbg !1180
  %tobool189 = icmp ne i32 %and188, 0, !dbg !1180
  br i1 %tobool189, label %if.then190, label %if.end191, !dbg !1181

if.then190:                                       ; preds = %if.then186
  store i32 1, i32* %retval, align 4, !dbg !1182
  br label %return, !dbg !1182

if.end191:                                        ; preds = %if.then186
  br label %if.end218, !dbg !1183

if.else192:                                       ; preds = %if.else183
  %128 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1184
  %call193 = call i64 @archive_entry_mtime_nsec(%struct.archive_entry* %128), !dbg !1186
  store i64 %call193, i64* %nsec, align 8, !dbg !1187
  %129 = load %struct.match_file*, %struct.match_file** %f, align 8, !dbg !1188
  %mtime_nsec = getelementptr inbounds %struct.match_file, %struct.match_file* %129, i32 0, i32 5, !dbg !1190
  %130 = load i64, i64* %mtime_nsec, align 8, !dbg !1190
  %131 = load i64, i64* %nsec, align 8, !dbg !1191
  %cmp194 = icmp sgt i64 %130, %131, !dbg !1192
  br i1 %cmp194, label %if.then195, label %if.else201, !dbg !1193

if.then195:                                       ; preds = %if.else192
  %132 = load %struct.match_file*, %struct.match_file** %f, align 8, !dbg !1194
  %flag196 = getelementptr inbounds %struct.match_file, %struct.match_file* %132, i32 0, i32 3, !dbg !1197
  %133 = load i32, i32* %flag196, align 8, !dbg !1197
  %and197 = and i32 %133, 2, !dbg !1198
  %tobool198 = icmp ne i32 %and197, 0, !dbg !1198
  br i1 %tobool198, label %if.then199, label %if.end200, !dbg !1199

if.then199:                                       ; preds = %if.then195
  store i32 1, i32* %retval, align 4, !dbg !1200
  br label %return, !dbg !1200

if.end200:                                        ; preds = %if.then195
  br label %if.end217, !dbg !1201

if.else201:                                       ; preds = %if.else192
  %134 = load %struct.match_file*, %struct.match_file** %f, align 8, !dbg !1202
  %mtime_nsec202 = getelementptr inbounds %struct.match_file, %struct.match_file* %134, i32 0, i32 5, !dbg !1205
  %135 = load i64, i64* %mtime_nsec202, align 8, !dbg !1205
  %136 = load i64, i64* %nsec, align 8, !dbg !1206
  %cmp203 = icmp slt i64 %135, %136, !dbg !1207
  br i1 %cmp203, label %if.then204, label %if.else210, !dbg !1202

if.then204:                                       ; preds = %if.else201
  %137 = load %struct.match_file*, %struct.match_file** %f, align 8, !dbg !1208
  %flag205 = getelementptr inbounds %struct.match_file, %struct.match_file* %137, i32 0, i32 3, !dbg !1211
  %138 = load i32, i32* %flag205, align 8, !dbg !1211
  %and206 = and i32 %138, 1, !dbg !1212
  %tobool207 = icmp ne i32 %and206, 0, !dbg !1212
  br i1 %tobool207, label %if.then208, label %if.end209, !dbg !1213

if.then208:                                       ; preds = %if.then204
  store i32 1, i32* %retval, align 4, !dbg !1214
  br label %return, !dbg !1214

if.end209:                                        ; preds = %if.then204
  br label %if.end216, !dbg !1215

if.else210:                                       ; preds = %if.else201
  %139 = load %struct.match_file*, %struct.match_file** %f, align 8, !dbg !1216
  %flag211 = getelementptr inbounds %struct.match_file, %struct.match_file* %139, i32 0, i32 3, !dbg !1219
  %140 = load i32, i32* %flag211, align 8, !dbg !1219
  %and212 = and i32 %140, 16, !dbg !1220
  %tobool213 = icmp ne i32 %and212, 0, !dbg !1220
  br i1 %tobool213, label %if.then214, label %if.end215, !dbg !1216

if.then214:                                       ; preds = %if.else210
  store i32 1, i32* %retval, align 4, !dbg !1221
  br label %return, !dbg !1221

if.end215:                                        ; preds = %if.else210
  br label %if.end216

if.end216:                                        ; preds = %if.end215, %if.end209
  br label %if.end217

if.end217:                                        ; preds = %if.end216, %if.end200
  br label %if.end218

if.end218:                                        ; preds = %if.end217, %if.end191
  br label %if.end219

if.end219:                                        ; preds = %if.end218, %if.end182
  br label %if.end220, !dbg !1222

if.end220:                                        ; preds = %if.end219, %if.end170
  store i32 0, i32* %retval, align 4, !dbg !1223
  br label %return, !dbg !1223

return:                                           ; preds = %if.end220, %if.then214, %if.then208, %if.then199, %if.then190, %if.then181, %if.then164, %if.then158, %if.then149, %if.then140, %if.then131, %if.then120, %if.then115, %if.then111, %if.then106, %if.then98, %if.then91, %if.then83, %if.then75, %if.then68, %if.then60, %if.then52, %if.then39, %if.then25, %if.then19, %if.then6
  %141 = load i32, i32* %retval, align 4, !dbg !1224
  ret i32 %141, !dbg !1224
}

; Function Attrs: nounwind uwtable
define internal i32 @owner_excluded(%struct.archive_match* %a, %struct.archive_entry* %entry1) #0 !dbg !382 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_match*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %r = alloca i32, align 4
  store %struct.archive_match* %a, %struct.archive_match** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a.addr, metadata !1225, metadata !394), !dbg !1226
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1227, metadata !394), !dbg !1228
  call void @llvm.dbg.declare(metadata i32* %r, metadata !1229, metadata !394), !dbg !1230
  %0 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !1231
  %inclusion_uids = getelementptr inbounds %struct.archive_match, %struct.archive_match* %0, i32 0, i32 19, !dbg !1233
  %count = getelementptr inbounds %struct.id_array, %struct.id_array* %inclusion_uids, i32 0, i32 1, !dbg !1234
  %1 = load i64, i64* %count, align 8, !dbg !1234
  %tobool = icmp ne i64 %1, 0, !dbg !1231
  br i1 %tobool, label %if.then, label %if.end6, !dbg !1235

if.then:                                          ; preds = %entry
  %2 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !1236
  %inclusion_uids2 = getelementptr inbounds %struct.archive_match, %struct.archive_match* %2, i32 0, i32 19, !dbg !1239
  %3 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1240
  %call = call i64 @archive_entry_uid(%struct.archive_entry* %3), !dbg !1241
  %call3 = call i32 @match_owner_id(%struct.id_array* %inclusion_uids2, i64 %call), !dbg !1242
  %tobool4 = icmp ne i32 %call3, 0, !dbg !1242
  br i1 %tobool4, label %if.end, label %if.then5, !dbg !1243

if.then5:                                         ; preds = %if.then
  store i32 1, i32* %retval, align 4, !dbg !1244
  br label %return, !dbg !1244

if.end:                                           ; preds = %if.then
  br label %if.end6, !dbg !1245

if.end6:                                          ; preds = %if.end, %entry
  %4 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !1246
  %inclusion_gids = getelementptr inbounds %struct.archive_match, %struct.archive_match* %4, i32 0, i32 20, !dbg !1248
  %count7 = getelementptr inbounds %struct.id_array, %struct.id_array* %inclusion_gids, i32 0, i32 1, !dbg !1249
  %5 = load i64, i64* %count7, align 8, !dbg !1249
  %tobool8 = icmp ne i64 %5, 0, !dbg !1246
  br i1 %tobool8, label %if.then9, label %if.end16, !dbg !1250

if.then9:                                         ; preds = %if.end6
  %6 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !1251
  %inclusion_gids10 = getelementptr inbounds %struct.archive_match, %struct.archive_match* %6, i32 0, i32 20, !dbg !1254
  %7 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1255
  %call11 = call i64 @archive_entry_gid(%struct.archive_entry* %7), !dbg !1256
  %call12 = call i32 @match_owner_id(%struct.id_array* %inclusion_gids10, i64 %call11), !dbg !1257
  %tobool13 = icmp ne i32 %call12, 0, !dbg !1257
  br i1 %tobool13, label %if.end15, label %if.then14, !dbg !1258

if.then14:                                        ; preds = %if.then9
  store i32 1, i32* %retval, align 4, !dbg !1259
  br label %return, !dbg !1259

if.end15:                                         ; preds = %if.then9
  br label %if.end16, !dbg !1260

if.end16:                                         ; preds = %if.end15, %if.end6
  %8 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !1261
  %inclusion_unames = getelementptr inbounds %struct.archive_match, %struct.archive_match* %8, i32 0, i32 21, !dbg !1263
  %count17 = getelementptr inbounds %struct.match_list, %struct.match_list* %inclusion_unames, i32 0, i32 2, !dbg !1264
  %9 = load i32, i32* %count17, align 8, !dbg !1264
  %tobool18 = icmp ne i32 %9, 0, !dbg !1261
  br i1 %tobool18, label %if.then19, label %if.end28, !dbg !1265

if.then19:                                        ; preds = %if.end16
  %10 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !1266
  %11 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !1268
  %inclusion_unames20 = getelementptr inbounds %struct.archive_match, %struct.archive_match* %11, i32 0, i32 21, !dbg !1269
  %12 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1270
  %call21 = call i8* @archive_entry_uname(%struct.archive_entry* %12), !dbg !1271
  %call22 = call i32 @match_owner_name_mbs(%struct.archive_match* %10, %struct.match_list* %inclusion_unames20, i8* %call21), !dbg !1272
  store i32 %call22, i32* %r, align 4, !dbg !1273
  %13 = load i32, i32* %r, align 4, !dbg !1274
  %tobool23 = icmp ne i32 %13, 0, !dbg !1274
  br i1 %tobool23, label %if.else, label %if.then24, !dbg !1276

if.then24:                                        ; preds = %if.then19
  store i32 1, i32* %retval, align 4, !dbg !1277
  br label %return, !dbg !1277

if.else:                                          ; preds = %if.then19
  %14 = load i32, i32* %r, align 4, !dbg !1278
  %cmp = icmp slt i32 %14, 0, !dbg !1280
  br i1 %cmp, label %if.then25, label %if.end26, !dbg !1281

if.then25:                                        ; preds = %if.else
  %15 = load i32, i32* %r, align 4, !dbg !1282
  store i32 %15, i32* %retval, align 4, !dbg !1283
  br label %return, !dbg !1283

if.end26:                                         ; preds = %if.else
  br label %if.end27

if.end27:                                         ; preds = %if.end26
  br label %if.end28, !dbg !1284

if.end28:                                         ; preds = %if.end27, %if.end16
  %16 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !1285
  %inclusion_gnames = getelementptr inbounds %struct.archive_match, %struct.archive_match* %16, i32 0, i32 22, !dbg !1287
  %count29 = getelementptr inbounds %struct.match_list, %struct.match_list* %inclusion_gnames, i32 0, i32 2, !dbg !1288
  %17 = load i32, i32* %count29, align 8, !dbg !1288
  %tobool30 = icmp ne i32 %17, 0, !dbg !1285
  br i1 %tobool30, label %if.then31, label %if.end42, !dbg !1289

if.then31:                                        ; preds = %if.end28
  %18 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !1290
  %19 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !1292
  %inclusion_gnames32 = getelementptr inbounds %struct.archive_match, %struct.archive_match* %19, i32 0, i32 22, !dbg !1293
  %20 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1294
  %call33 = call i8* @archive_entry_gname(%struct.archive_entry* %20), !dbg !1295
  %call34 = call i32 @match_owner_name_mbs(%struct.archive_match* %18, %struct.match_list* %inclusion_gnames32, i8* %call33), !dbg !1296
  store i32 %call34, i32* %r, align 4, !dbg !1297
  %21 = load i32, i32* %r, align 4, !dbg !1298
  %tobool35 = icmp ne i32 %21, 0, !dbg !1298
  br i1 %tobool35, label %if.else37, label %if.then36, !dbg !1300

if.then36:                                        ; preds = %if.then31
  store i32 1, i32* %retval, align 4, !dbg !1301
  br label %return, !dbg !1301

if.else37:                                        ; preds = %if.then31
  %22 = load i32, i32* %r, align 4, !dbg !1302
  %cmp38 = icmp slt i32 %22, 0, !dbg !1304
  br i1 %cmp38, label %if.then39, label %if.end40, !dbg !1305

if.then39:                                        ; preds = %if.else37
  %23 = load i32, i32* %r, align 4, !dbg !1306
  store i32 %23, i32* %retval, align 4, !dbg !1307
  br label %return, !dbg !1307

if.end40:                                         ; preds = %if.else37
  br label %if.end41

if.end41:                                         ; preds = %if.end40
  br label %if.end42, !dbg !1308

if.end42:                                         ; preds = %if.end41, %if.end28
  store i32 0, i32* %retval, align 4, !dbg !1309
  br label %return, !dbg !1309

return:                                           ; preds = %if.end42, %if.then39, %if.then36, %if.then25, %if.then24, %if.then14, %if.then5
  %24 = load i32, i32* %retval, align 4, !dbg !1310
  ret i32 %24, !dbg !1310
}

; Function Attrs: nounwind uwtable
define i32 @archive_match_exclude_pattern(%struct.archive* %_a, i8* %pattern) #0 !dbg !226 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %pattern.addr = alloca i8*, align 8
  %a = alloca %struct.archive_match*, align 8
  %r = alloca i32, align 4
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !1311, metadata !394), !dbg !1312
  store i8* %pattern, i8** %pattern.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %pattern.addr, metadata !1313, metadata !394), !dbg !1314
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a, metadata !1315, metadata !394), !dbg !1316
  call void @llvm.dbg.declare(metadata i32* %r, metadata !1317, metadata !394), !dbg !1318
  br label %do.body, !dbg !1319

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !1320, metadata !394), !dbg !1322
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1323
  %call = call i32 @__archive_check_magic(%struct.archive* %0, i32 212668873, i32 1, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.3, i32 0, i32 0)), !dbg !1323
  store i32 %call, i32* %magic_test, align 4, !dbg !1323
  %1 = load i32, i32* %magic_test, align 4, !dbg !1323
  %cmp = icmp eq i32 %1, -30, !dbg !1323
  br i1 %cmp, label %if.then, label %if.end, !dbg !1323

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !1325
  br label %return, !dbg !1325

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !1328

do.end:                                           ; preds = %if.end
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1330
  %3 = bitcast %struct.archive* %2 to %struct.archive_match*, !dbg !1331
  store %struct.archive_match* %3, %struct.archive_match** %a, align 8, !dbg !1332
  %4 = load i8*, i8** %pattern.addr, align 8, !dbg !1333
  %cmp1 = icmp eq i8* %4, null, !dbg !1335
  br i1 %cmp1, label %if.then4, label %lor.lhs.false, !dbg !1336

lor.lhs.false:                                    ; preds = %do.end
  %5 = load i8*, i8** %pattern.addr, align 8, !dbg !1337
  %6 = load i8, i8* %5, align 1, !dbg !1339
  %conv = sext i8 %6 to i32, !dbg !1339
  %cmp2 = icmp eq i32 %conv, 0, !dbg !1340
  br i1 %cmp2, label %if.then4, label %if.end5, !dbg !1341

if.then4:                                         ; preds = %lor.lhs.false, %do.end
  %7 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !1342
  %archive = getelementptr inbounds %struct.archive_match, %struct.archive_match* %7, i32 0, i32 0, !dbg !1344
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 22, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.4, i32 0, i32 0)), !dbg !1345
  store i32 -25, i32* %retval, align 4, !dbg !1346
  br label %return, !dbg !1346

if.end5:                                          ; preds = %lor.lhs.false
  %8 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !1347
  %9 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !1349
  %exclusions = getelementptr inbounds %struct.archive_match, %struct.archive_match* %9, i32 0, i32 2, !dbg !1350
  %10 = load i8*, i8** %pattern.addr, align 8, !dbg !1351
  %call6 = call i32 @add_pattern_mbs(%struct.archive_match* %8, %struct.match_list* %exclusions, i8* %10), !dbg !1352
  store i32 %call6, i32* %r, align 4, !dbg !1353
  %cmp7 = icmp ne i32 %call6, 0, !dbg !1354
  br i1 %cmp7, label %if.then9, label %if.end10, !dbg !1355

if.then9:                                         ; preds = %if.end5
  %11 = load i32, i32* %r, align 4, !dbg !1356
  store i32 %11, i32* %retval, align 4, !dbg !1357
  br label %return, !dbg !1357

if.end10:                                         ; preds = %if.end5
  store i32 0, i32* %retval, align 4, !dbg !1358
  br label %return, !dbg !1358

return:                                           ; preds = %if.end10, %if.then9, %if.then4, %if.then
  %12 = load i32, i32* %retval, align 4, !dbg !1359
  ret i32 %12, !dbg !1359
}

; Function Attrs: nounwind uwtable
define internal i32 @add_pattern_mbs(%struct.archive_match* %a, %struct.match_list* %list, i8* %pattern) #0 !dbg !278 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_match*, align 8
  %list.addr = alloca %struct.match_list*, align 8
  %pattern.addr = alloca i8*, align 8
  %match = alloca %struct.match*, align 8
  %len = alloca i64, align 8
  store %struct.archive_match* %a, %struct.archive_match** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a.addr, metadata !1360, metadata !394), !dbg !1361
  store %struct.match_list* %list, %struct.match_list** %list.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.match_list** %list.addr, metadata !1362, metadata !394), !dbg !1363
  store i8* %pattern, i8** %pattern.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %pattern.addr, metadata !1364, metadata !394), !dbg !1365
  call void @llvm.dbg.declare(metadata %struct.match** %match, metadata !1366, metadata !394), !dbg !1367
  call void @llvm.dbg.declare(metadata i64* %len, metadata !1368, metadata !394), !dbg !1369
  %call = call noalias i8* @calloc(i64 1, i64 120) #7, !dbg !1370
  %0 = bitcast i8* %call to %struct.match*, !dbg !1370
  store %struct.match* %0, %struct.match** %match, align 8, !dbg !1371
  %1 = load %struct.match*, %struct.match** %match, align 8, !dbg !1372
  %cmp = icmp eq %struct.match* %1, null, !dbg !1374
  br i1 %cmp, label %if.then, label %if.end, !dbg !1375

if.then:                                          ; preds = %entry
  %2 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !1376
  %call1 = call i32 @error_nomem(%struct.archive_match* %2), !dbg !1377
  store i32 %call1, i32* %retval, align 4, !dbg !1378
  br label %return, !dbg !1378

if.end:                                           ; preds = %entry
  %3 = load i8*, i8** %pattern.addr, align 8, !dbg !1379
  %call2 = call i64 @strlen(i8* %3) #8, !dbg !1380
  store i64 %call2, i64* %len, align 8, !dbg !1381
  %4 = load i64, i64* %len, align 8, !dbg !1382
  %tobool = icmp ne i64 %4, 0, !dbg !1382
  br i1 %tobool, label %land.lhs.true, label %if.end6, !dbg !1384

land.lhs.true:                                    ; preds = %if.end
  %5 = load i64, i64* %len, align 8, !dbg !1385
  %sub = sub i64 %5, 1, !dbg !1387
  %6 = load i8*, i8** %pattern.addr, align 8, !dbg !1388
  %arrayidx = getelementptr inbounds i8, i8* %6, i64 %sub, !dbg !1388
  %7 = load i8, i8* %arrayidx, align 1, !dbg !1388
  %conv = sext i8 %7 to i32, !dbg !1388
  %cmp3 = icmp eq i32 %conv, 47, !dbg !1389
  br i1 %cmp3, label %if.then5, label %if.end6, !dbg !1390

if.then5:                                         ; preds = %land.lhs.true
  %8 = load i64, i64* %len, align 8, !dbg !1391
  %dec = add i64 %8, -1, !dbg !1391
  store i64 %dec, i64* %len, align 8, !dbg !1391
  br label %if.end6, !dbg !1391

if.end6:                                          ; preds = %if.then5, %land.lhs.true, %if.end
  %9 = load %struct.match*, %struct.match** %match, align 8, !dbg !1392
  %pattern7 = getelementptr inbounds %struct.match, %struct.match* %9, i32 0, i32 2, !dbg !1393
  %10 = load i8*, i8** %pattern.addr, align 8, !dbg !1394
  %11 = load i64, i64* %len, align 8, !dbg !1395
  %call8 = call i32 @archive_mstring_copy_mbs_len(%struct.archive_mstring* %pattern7, i8* %10, i64 %11), !dbg !1396
  %12 = load %struct.match_list*, %struct.match_list** %list.addr, align 8, !dbg !1397
  %13 = load %struct.match*, %struct.match** %match, align 8, !dbg !1398
  call void @match_list_add(%struct.match_list* %12, %struct.match* %13), !dbg !1399
  %14 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !1400
  %setflag = getelementptr inbounds %struct.archive_match, %struct.archive_match* %14, i32 0, i32 1, !dbg !1401
  %15 = load i32, i32* %setflag, align 8, !dbg !1402
  %or = or i32 %15, 1, !dbg !1402
  store i32 %or, i32* %setflag, align 8, !dbg !1402
  store i32 0, i32* %retval, align 4, !dbg !1403
  br label %return, !dbg !1403

return:                                           ; preds = %if.end6, %if.then
  %16 = load i32, i32* %retval, align 4, !dbg !1404
  ret i32 %16, !dbg !1404
}

; Function Attrs: nounwind uwtable
define i32 @archive_match_exclude_pattern_w(%struct.archive* %_a, i32* %pattern) #0 !dbg !229 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %pattern.addr = alloca i32*, align 8
  %a = alloca %struct.archive_match*, align 8
  %r = alloca i32, align 4
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !1405, metadata !394), !dbg !1406
  store i32* %pattern, i32** %pattern.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %pattern.addr, metadata !1407, metadata !394), !dbg !1408
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a, metadata !1409, metadata !394), !dbg !1410
  call void @llvm.dbg.declare(metadata i32* %r, metadata !1411, metadata !394), !dbg !1412
  br label %do.body, !dbg !1413

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !1414, metadata !394), !dbg !1416
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1417
  %call = call i32 @__archive_check_magic(%struct.archive* %0, i32 212668873, i32 1, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.5, i32 0, i32 0)), !dbg !1417
  store i32 %call, i32* %magic_test, align 4, !dbg !1417
  %1 = load i32, i32* %magic_test, align 4, !dbg !1417
  %cmp = icmp eq i32 %1, -30, !dbg !1417
  br i1 %cmp, label %if.then, label %if.end, !dbg !1417

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !1419
  br label %return, !dbg !1419

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !1422

do.end:                                           ; preds = %if.end
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1424
  %3 = bitcast %struct.archive* %2 to %struct.archive_match*, !dbg !1425
  store %struct.archive_match* %3, %struct.archive_match** %a, align 8, !dbg !1426
  %4 = load i32*, i32** %pattern.addr, align 8, !dbg !1427
  %cmp1 = icmp eq i32* %4, null, !dbg !1429
  br i1 %cmp1, label %if.then3, label %lor.lhs.false, !dbg !1430

lor.lhs.false:                                    ; preds = %do.end
  %5 = load i32*, i32** %pattern.addr, align 8, !dbg !1431
  %6 = load i32, i32* %5, align 4, !dbg !1433
  %cmp2 = icmp eq i32 %6, 0, !dbg !1434
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !1435

if.then3:                                         ; preds = %lor.lhs.false, %do.end
  %7 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !1436
  %archive = getelementptr inbounds %struct.archive_match, %struct.archive_match* %7, i32 0, i32 0, !dbg !1438
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 22, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.4, i32 0, i32 0)), !dbg !1439
  store i32 -25, i32* %retval, align 4, !dbg !1440
  br label %return, !dbg !1440

if.end4:                                          ; preds = %lor.lhs.false
  %8 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !1441
  %9 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !1443
  %exclusions = getelementptr inbounds %struct.archive_match, %struct.archive_match* %9, i32 0, i32 2, !dbg !1444
  %10 = load i32*, i32** %pattern.addr, align 8, !dbg !1445
  %call5 = call i32 @add_pattern_wcs(%struct.archive_match* %8, %struct.match_list* %exclusions, i32* %10), !dbg !1446
  store i32 %call5, i32* %r, align 4, !dbg !1447
  %cmp6 = icmp ne i32 %call5, 0, !dbg !1448
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !1449

if.then7:                                         ; preds = %if.end4
  %11 = load i32, i32* %r, align 4, !dbg !1450
  store i32 %11, i32* %retval, align 4, !dbg !1451
  br label %return, !dbg !1451

if.end8:                                          ; preds = %if.end4
  store i32 0, i32* %retval, align 4, !dbg !1452
  br label %return, !dbg !1452

return:                                           ; preds = %if.end8, %if.then7, %if.then3, %if.then
  %12 = load i32, i32* %retval, align 4, !dbg !1453
  ret i32 %12, !dbg !1453
}

; Function Attrs: nounwind uwtable
define internal i32 @add_pattern_wcs(%struct.archive_match* %a, %struct.match_list* %list, i32* %pattern) #0 !dbg !288 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_match*, align 8
  %list.addr = alloca %struct.match_list*, align 8
  %pattern.addr = alloca i32*, align 8
  %match = alloca %struct.match*, align 8
  %len = alloca i64, align 8
  store %struct.archive_match* %a, %struct.archive_match** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a.addr, metadata !1454, metadata !394), !dbg !1455
  store %struct.match_list* %list, %struct.match_list** %list.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.match_list** %list.addr, metadata !1456, metadata !394), !dbg !1457
  store i32* %pattern, i32** %pattern.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %pattern.addr, metadata !1458, metadata !394), !dbg !1459
  call void @llvm.dbg.declare(metadata %struct.match** %match, metadata !1460, metadata !394), !dbg !1461
  call void @llvm.dbg.declare(metadata i64* %len, metadata !1462, metadata !394), !dbg !1463
  %call = call noalias i8* @calloc(i64 1, i64 120) #7, !dbg !1464
  %0 = bitcast i8* %call to %struct.match*, !dbg !1464
  store %struct.match* %0, %struct.match** %match, align 8, !dbg !1465
  %1 = load %struct.match*, %struct.match** %match, align 8, !dbg !1466
  %cmp = icmp eq %struct.match* %1, null, !dbg !1468
  br i1 %cmp, label %if.then, label %if.end, !dbg !1469

if.then:                                          ; preds = %entry
  %2 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !1470
  %call1 = call i32 @error_nomem(%struct.archive_match* %2), !dbg !1471
  store i32 %call1, i32* %retval, align 4, !dbg !1472
  br label %return, !dbg !1472

if.end:                                           ; preds = %entry
  %3 = load i32*, i32** %pattern.addr, align 8, !dbg !1473
  %call2 = call i64 @wcslen(i32* %3) #8, !dbg !1474
  store i64 %call2, i64* %len, align 8, !dbg !1475
  %4 = load i64, i64* %len, align 8, !dbg !1476
  %tobool = icmp ne i64 %4, 0, !dbg !1476
  br i1 %tobool, label %land.lhs.true, label %if.end5, !dbg !1478

land.lhs.true:                                    ; preds = %if.end
  %5 = load i64, i64* %len, align 8, !dbg !1479
  %sub = sub i64 %5, 1, !dbg !1481
  %6 = load i32*, i32** %pattern.addr, align 8, !dbg !1482
  %arrayidx = getelementptr inbounds i32, i32* %6, i64 %sub, !dbg !1482
  %7 = load i32, i32* %arrayidx, align 4, !dbg !1482
  %cmp3 = icmp eq i32 %7, 47, !dbg !1483
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !1484

if.then4:                                         ; preds = %land.lhs.true
  %8 = load i64, i64* %len, align 8, !dbg !1485
  %dec = add i64 %8, -1, !dbg !1485
  store i64 %dec, i64* %len, align 8, !dbg !1485
  br label %if.end5, !dbg !1485

if.end5:                                          ; preds = %if.then4, %land.lhs.true, %if.end
  %9 = load %struct.match*, %struct.match** %match, align 8, !dbg !1486
  %pattern6 = getelementptr inbounds %struct.match, %struct.match* %9, i32 0, i32 2, !dbg !1487
  %10 = load i32*, i32** %pattern.addr, align 8, !dbg !1488
  %11 = load i64, i64* %len, align 8, !dbg !1489
  %call7 = call i32 @archive_mstring_copy_wcs_len(%struct.archive_mstring* %pattern6, i32* %10, i64 %11), !dbg !1490
  %12 = load %struct.match_list*, %struct.match_list** %list.addr, align 8, !dbg !1491
  %13 = load %struct.match*, %struct.match** %match, align 8, !dbg !1492
  call void @match_list_add(%struct.match_list* %12, %struct.match* %13), !dbg !1493
  %14 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !1494
  %setflag = getelementptr inbounds %struct.archive_match, %struct.archive_match* %14, i32 0, i32 1, !dbg !1495
  %15 = load i32, i32* %setflag, align 8, !dbg !1496
  %or = or i32 %15, 1, !dbg !1496
  store i32 %or, i32* %setflag, align 8, !dbg !1496
  store i32 0, i32* %retval, align 4, !dbg !1497
  br label %return, !dbg !1497

return:                                           ; preds = %if.end5, %if.then
  %16 = load i32, i32* %retval, align 4, !dbg !1498
  ret i32 %16, !dbg !1498
}

; Function Attrs: nounwind uwtable
define i32 @archive_match_exclude_pattern_from_file(%struct.archive* %_a, i8* %pathname, i32 %nullSeparator) #0 !dbg !232 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %pathname.addr = alloca i8*, align 8
  %nullSeparator.addr = alloca i32, align 4
  %a = alloca %struct.archive_match*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !1499, metadata !394), !dbg !1500
  store i8* %pathname, i8** %pathname.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %pathname.addr, metadata !1501, metadata !394), !dbg !1502
  store i32 %nullSeparator, i32* %nullSeparator.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %nullSeparator.addr, metadata !1503, metadata !394), !dbg !1504
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a, metadata !1505, metadata !394), !dbg !1506
  br label %do.body, !dbg !1507

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !1508, metadata !394), !dbg !1510
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1511
  %call = call i32 @__archive_check_magic(%struct.archive* %0, i32 212668873, i32 1, i8* getelementptr inbounds ([40 x i8], [40 x i8]* @.str.6, i32 0, i32 0)), !dbg !1511
  store i32 %call, i32* %magic_test, align 4, !dbg !1511
  %1 = load i32, i32* %magic_test, align 4, !dbg !1511
  %cmp = icmp eq i32 %1, -30, !dbg !1511
  br i1 %cmp, label %if.then, label %if.end, !dbg !1511

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !1513
  br label %return, !dbg !1513

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !1516

do.end:                                           ; preds = %if.end
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1518
  %3 = bitcast %struct.archive* %2 to %struct.archive_match*, !dbg !1519
  store %struct.archive_match* %3, %struct.archive_match** %a, align 8, !dbg !1520
  %4 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !1521
  %5 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !1522
  %exclusions = getelementptr inbounds %struct.archive_match, %struct.archive_match* %5, i32 0, i32 2, !dbg !1523
  %6 = load i8*, i8** %pathname.addr, align 8, !dbg !1524
  %7 = load i32, i32* %nullSeparator.addr, align 4, !dbg !1525
  %call1 = call i32 @add_pattern_from_file(%struct.archive_match* %4, %struct.match_list* %exclusions, i32 1, i8* %6, i32 %7), !dbg !1526
  store i32 %call1, i32* %retval, align 4, !dbg !1527
  br label %return, !dbg !1527

return:                                           ; preds = %do.end, %if.then
  %8 = load i32, i32* %retval, align 4, !dbg !1528
  ret i32 %8, !dbg !1528
}

; Function Attrs: nounwind uwtable
define internal i32 @add_pattern_from_file(%struct.archive_match* %a, %struct.match_list* %mlist, i32 %mbs, i8* %pathname, i32 %nullSeparator) #0 !dbg !291 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_match*, align 8
  %mlist.addr = alloca %struct.match_list*, align 8
  %mbs.addr = alloca i32, align 4
  %pathname.addr = alloca i8*, align 8
  %nullSeparator.addr = alloca i32, align 4
  %ar = alloca %struct.archive*, align 8
  %ae = alloca %struct.archive_entry*, align 8
  %as = alloca %struct.archive_string, align 8
  %buff = alloca i8*, align 8
  %size = alloca i64, align 8
  %offset = alloca i64, align 8
  %r = alloca i32, align 4
  %b = alloca i8*, align 8
  %s31 = alloca i8*, align 8
  %length32 = alloca i64, align 8
  %found_separator = alloca i32, align 4
  store %struct.archive_match* %a, %struct.archive_match** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a.addr, metadata !1529, metadata !394), !dbg !1530
  store %struct.match_list* %mlist, %struct.match_list** %mlist.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.match_list** %mlist.addr, metadata !1531, metadata !394), !dbg !1532
  store i32 %mbs, i32* %mbs.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %mbs.addr, metadata !1533, metadata !394), !dbg !1534
  store i8* %pathname, i8** %pathname.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %pathname.addr, metadata !1535, metadata !394), !dbg !1536
  store i32 %nullSeparator, i32* %nullSeparator.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %nullSeparator.addr, metadata !1537, metadata !394), !dbg !1538
  call void @llvm.dbg.declare(metadata %struct.archive** %ar, metadata !1539, metadata !394), !dbg !1540
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %ae, metadata !1541, metadata !394), !dbg !1542
  call void @llvm.dbg.declare(metadata %struct.archive_string* %as, metadata !1543, metadata !394), !dbg !1544
  call void @llvm.dbg.declare(metadata i8** %buff, metadata !1545, metadata !394), !dbg !1546
  call void @llvm.dbg.declare(metadata i64* %size, metadata !1547, metadata !394), !dbg !1548
  call void @llvm.dbg.declare(metadata i64* %offset, metadata !1549, metadata !394), !dbg !1550
  call void @llvm.dbg.declare(metadata i32* %r, metadata !1551, metadata !394), !dbg !1552
  %call = call %struct.archive* @archive_read_new(), !dbg !1553
  store %struct.archive* %call, %struct.archive** %ar, align 8, !dbg !1554
  %0 = load %struct.archive*, %struct.archive** %ar, align 8, !dbg !1555
  %cmp = icmp eq %struct.archive* %0, null, !dbg !1557
  br i1 %cmp, label %if.then, label %if.end, !dbg !1558

if.then:                                          ; preds = %entry
  %1 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !1559
  %archive = getelementptr inbounds %struct.archive_match, %struct.archive_match* %1, i32 0, i32 0, !dbg !1561
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.31, i32 0, i32 0)), !dbg !1562
  store i32 -30, i32* %retval, align 4, !dbg !1563
  br label %return, !dbg !1563

if.end:                                           ; preds = %entry
  %2 = load %struct.archive*, %struct.archive** %ar, align 8, !dbg !1564
  %call1 = call i32 @archive_read_support_format_raw(%struct.archive* %2), !dbg !1565
  store i32 %call1, i32* %r, align 4, !dbg !1566
  %3 = load %struct.archive*, %struct.archive** %ar, align 8, !dbg !1567
  %call2 = call i32 @archive_read_support_format_empty(%struct.archive* %3), !dbg !1568
  store i32 %call2, i32* %r, align 4, !dbg !1569
  %4 = load i32, i32* %r, align 4, !dbg !1570
  %cmp3 = icmp ne i32 %4, 0, !dbg !1572
  br i1 %cmp3, label %if.then4, label %if.end7, !dbg !1573

if.then4:                                         ; preds = %if.end
  %5 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !1574
  %archive5 = getelementptr inbounds %struct.archive_match, %struct.archive_match* %5, i32 0, i32 0, !dbg !1576
  %6 = load %struct.archive*, %struct.archive** %ar, align 8, !dbg !1577
  call void @archive_copy_error(%struct.archive* %archive5, %struct.archive* %6), !dbg !1578
  %7 = load %struct.archive*, %struct.archive** %ar, align 8, !dbg !1579
  %call6 = call i32 @archive_read_free(%struct.archive* %7), !dbg !1580
  %8 = load i32, i32* %r, align 4, !dbg !1581
  store i32 %8, i32* %retval, align 4, !dbg !1582
  br label %return, !dbg !1582

if.end7:                                          ; preds = %if.end
  %9 = load i32, i32* %mbs.addr, align 4, !dbg !1583
  %tobool = icmp ne i32 %9, 0, !dbg !1583
  br i1 %tobool, label %if.then8, label %if.else, !dbg !1585

if.then8:                                         ; preds = %if.end7
  %10 = load %struct.archive*, %struct.archive** %ar, align 8, !dbg !1586
  %11 = load i8*, i8** %pathname.addr, align 8, !dbg !1587
  %call9 = call i32 @archive_read_open_filename(%struct.archive* %10, i8* %11, i64 10240), !dbg !1588
  store i32 %call9, i32* %r, align 4, !dbg !1589
  br label %if.end11, !dbg !1590

if.else:                                          ; preds = %if.end7
  %12 = load %struct.archive*, %struct.archive** %ar, align 8, !dbg !1591
  %13 = load i8*, i8** %pathname.addr, align 8, !dbg !1592
  %14 = bitcast i8* %13 to i32*, !dbg !1592
  %call10 = call i32 @archive_read_open_filename_w(%struct.archive* %12, i32* %14, i64 10240), !dbg !1593
  store i32 %call10, i32* %r, align 4, !dbg !1594
  br label %if.end11

if.end11:                                         ; preds = %if.else, %if.then8
  %15 = load i32, i32* %r, align 4, !dbg !1595
  %cmp12 = icmp ne i32 %15, 0, !dbg !1597
  br i1 %cmp12, label %if.then13, label %if.end16, !dbg !1598

if.then13:                                        ; preds = %if.end11
  %16 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !1599
  %archive14 = getelementptr inbounds %struct.archive_match, %struct.archive_match* %16, i32 0, i32 0, !dbg !1601
  %17 = load %struct.archive*, %struct.archive** %ar, align 8, !dbg !1602
  call void @archive_copy_error(%struct.archive* %archive14, %struct.archive* %17), !dbg !1603
  %18 = load %struct.archive*, %struct.archive** %ar, align 8, !dbg !1604
  %call15 = call i32 @archive_read_free(%struct.archive* %18), !dbg !1605
  %19 = load i32, i32* %r, align 4, !dbg !1606
  store i32 %19, i32* %retval, align 4, !dbg !1607
  br label %return, !dbg !1607

if.end16:                                         ; preds = %if.end11
  %20 = load %struct.archive*, %struct.archive** %ar, align 8, !dbg !1608
  %call17 = call i32 @archive_read_next_header(%struct.archive* %20, %struct.archive_entry** %ae), !dbg !1609
  store i32 %call17, i32* %r, align 4, !dbg !1610
  %21 = load i32, i32* %r, align 4, !dbg !1611
  %cmp18 = icmp ne i32 %21, 0, !dbg !1613
  br i1 %cmp18, label %if.then19, label %if.end25, !dbg !1614

if.then19:                                        ; preds = %if.end16
  %22 = load %struct.archive*, %struct.archive** %ar, align 8, !dbg !1615
  %call20 = call i32 @archive_read_free(%struct.archive* %22), !dbg !1617
  %23 = load i32, i32* %r, align 4, !dbg !1618
  %cmp21 = icmp eq i32 %23, 1, !dbg !1620
  br i1 %cmp21, label %if.then22, label %if.else23, !dbg !1621

if.then22:                                        ; preds = %if.then19
  store i32 0, i32* %retval, align 4, !dbg !1622
  br label %return, !dbg !1622

if.else23:                                        ; preds = %if.then19
  %24 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !1624
  %archive24 = getelementptr inbounds %struct.archive_match, %struct.archive_match* %24, i32 0, i32 0, !dbg !1626
  %25 = load %struct.archive*, %struct.archive** %ar, align 8, !dbg !1627
  call void @archive_copy_error(%struct.archive* %archive24, %struct.archive* %25), !dbg !1628
  %26 = load i32, i32* %r, align 4, !dbg !1629
  store i32 %26, i32* %retval, align 4, !dbg !1630
  br label %return, !dbg !1630

if.end25:                                         ; preds = %if.end16
  br label %do.body, !dbg !1631

do.body:                                          ; preds = %if.end25
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 0, !dbg !1632
  store i8* null, i8** %s, align 8, !dbg !1632
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 1, !dbg !1632
  store i64 0, i64* %length, align 8, !dbg !1632
  %buffer_length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 2, !dbg !1632
  store i64 0, i64* %buffer_length, align 8, !dbg !1632
  br label %do.end, !dbg !1632

do.end:                                           ; preds = %do.body
  br label %while.cond, !dbg !1635

while.cond:                                       ; preds = %while.end71, %do.end
  %27 = load %struct.archive*, %struct.archive** %ar, align 8, !dbg !1636
  %call26 = call i32 @archive_read_data_block(%struct.archive* %27, i8** %buff, i64* %size, i64* %offset), !dbg !1638
  store i32 %call26, i32* %r, align 4, !dbg !1639
  %cmp27 = icmp eq i32 %call26, 0, !dbg !1640
  br i1 %cmp27, label %while.body, label %while.end72, !dbg !1641

while.body:                                       ; preds = %while.cond
  call void @llvm.dbg.declare(metadata i8** %b, metadata !1642, metadata !394), !dbg !1644
  %28 = load i8*, i8** %buff, align 8, !dbg !1645
  store i8* %28, i8** %b, align 8, !dbg !1644
  br label %while.cond28, !dbg !1646

while.cond28:                                     ; preds = %if.end70, %while.body
  %29 = load i64, i64* %size, align 8, !dbg !1647
  %tobool29 = icmp ne i64 %29, 0, !dbg !1649
  br i1 %tobool29, label %while.body30, label %while.end71, !dbg !1649

while.body30:                                     ; preds = %while.cond28
  call void @llvm.dbg.declare(metadata i8** %s31, metadata !1650, metadata !394), !dbg !1652
  %30 = load i8*, i8** %b, align 8, !dbg !1653
  store i8* %30, i8** %s31, align 8, !dbg !1652
  call void @llvm.dbg.declare(metadata i64* %length32, metadata !1654, metadata !394), !dbg !1655
  store i64 0, i64* %length32, align 8, !dbg !1655
  call void @llvm.dbg.declare(metadata i32* %found_separator, metadata !1656, metadata !394), !dbg !1657
  store i32 0, i32* %found_separator, align 4, !dbg !1657
  br label %while.cond33, !dbg !1658

while.cond33:                                     ; preds = %if.end51, %while.body30
  %31 = load i64, i64* %length32, align 8, !dbg !1659
  %32 = load i64, i64* %size, align 8, !dbg !1661
  %cmp34 = icmp ult i64 %31, %32, !dbg !1662
  br i1 %cmp34, label %while.body35, label %while.end, !dbg !1663

while.body35:                                     ; preds = %while.cond33
  %33 = load i32, i32* %nullSeparator.addr, align 4, !dbg !1664
  %tobool36 = icmp ne i32 %33, 0, !dbg !1664
  br i1 %tobool36, label %if.then37, label %if.else42, !dbg !1667

if.then37:                                        ; preds = %while.body35
  %34 = load i8*, i8** %b, align 8, !dbg !1668
  %35 = load i8, i8* %34, align 1, !dbg !1671
  %conv = sext i8 %35 to i32, !dbg !1671
  %cmp38 = icmp eq i32 %conv, 0, !dbg !1672
  br i1 %cmp38, label %if.then40, label %if.end41, !dbg !1673

if.then40:                                        ; preds = %if.then37
  store i32 1, i32* %found_separator, align 4, !dbg !1674
  br label %while.end, !dbg !1676

if.end41:                                         ; preds = %if.then37
  br label %if.end51, !dbg !1677

if.else42:                                        ; preds = %while.body35
  %36 = load i8*, i8** %b, align 8, !dbg !1678
  %37 = load i8, i8* %36, align 1, !dbg !1681
  %conv43 = sext i8 %37 to i32, !dbg !1681
  %cmp44 = icmp eq i32 %conv43, 13, !dbg !1682
  br i1 %cmp44, label %if.then49, label %lor.lhs.false, !dbg !1683

lor.lhs.false:                                    ; preds = %if.else42
  %38 = load i8*, i8** %b, align 8, !dbg !1684
  %39 = load i8, i8* %38, align 1, !dbg !1686
  %conv46 = sext i8 %39 to i32, !dbg !1686
  %cmp47 = icmp eq i32 %conv46, 10, !dbg !1687
  br i1 %cmp47, label %if.then49, label %if.end50, !dbg !1688

if.then49:                                        ; preds = %lor.lhs.false, %if.else42
  store i32 1, i32* %found_separator, align 4, !dbg !1689
  br label %while.end, !dbg !1691

if.end50:                                         ; preds = %lor.lhs.false
  br label %if.end51

if.end51:                                         ; preds = %if.end50, %if.end41
  %40 = load i8*, i8** %b, align 8, !dbg !1692
  %incdec.ptr = getelementptr inbounds i8, i8* %40, i32 1, !dbg !1692
  store i8* %incdec.ptr, i8** %b, align 8, !dbg !1692
  %41 = load i64, i64* %length32, align 8, !dbg !1693
  %inc = add i64 %41, 1, !dbg !1693
  store i64 %inc, i64* %length32, align 8, !dbg !1693
  br label %while.cond33, !dbg !1694

while.end:                                        ; preds = %if.then49, %if.then40, %while.cond33
  %42 = load i32, i32* %found_separator, align 4, !dbg !1696
  %tobool52 = icmp ne i32 %42, 0, !dbg !1696
  br i1 %tobool52, label %if.end55, label %if.then53, !dbg !1698

if.then53:                                        ; preds = %while.end
  %43 = load i8*, i8** %s31, align 8, !dbg !1699
  %44 = load i64, i64* %length32, align 8, !dbg !1701
  %call54 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %as, i8* %43, i64 %44), !dbg !1702
  br label %while.end71, !dbg !1703

if.end55:                                         ; preds = %while.end
  %45 = load i8*, i8** %b, align 8, !dbg !1704
  %incdec.ptr56 = getelementptr inbounds i8, i8* %45, i32 1, !dbg !1704
  store i8* %incdec.ptr56, i8** %b, align 8, !dbg !1704
  %46 = load i64, i64* %length32, align 8, !dbg !1705
  %add = add i64 %46, 1, !dbg !1706
  %47 = load i64, i64* %size, align 8, !dbg !1707
  %sub = sub i64 %47, %add, !dbg !1707
  store i64 %sub, i64* %size, align 8, !dbg !1707
  %48 = load i8*, i8** %s31, align 8, !dbg !1708
  %49 = load i64, i64* %length32, align 8, !dbg !1709
  %call57 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %as, i8* %48, i64 %49), !dbg !1710
  %length58 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 1, !dbg !1711
  %50 = load i64, i64* %length58, align 8, !dbg !1711
  %cmp59 = icmp ugt i64 %50, 0, !dbg !1713
  br i1 %cmp59, label %if.then61, label %if.end70, !dbg !1714

if.then61:                                        ; preds = %if.end55
  %51 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !1715
  %52 = load %struct.match_list*, %struct.match_list** %mlist.addr, align 8, !dbg !1717
  %s62 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 0, !dbg !1718
  %53 = load i8*, i8** %s62, align 8, !dbg !1718
  %call63 = call i32 @add_pattern_mbs(%struct.archive_match* %51, %struct.match_list* %52, i8* %53), !dbg !1719
  store i32 %call63, i32* %r, align 4, !dbg !1720
  %54 = load i32, i32* %r, align 4, !dbg !1721
  %cmp64 = icmp ne i32 %54, 0, !dbg !1723
  br i1 %cmp64, label %if.then66, label %if.end68, !dbg !1724

if.then66:                                        ; preds = %if.then61
  %55 = load %struct.archive*, %struct.archive** %ar, align 8, !dbg !1725
  %call67 = call i32 @archive_read_free(%struct.archive* %55), !dbg !1727
  call void @archive_string_free(%struct.archive_string* %as), !dbg !1728
  %56 = load i32, i32* %r, align 4, !dbg !1729
  store i32 %56, i32* %retval, align 4, !dbg !1730
  br label %return, !dbg !1730

if.end68:                                         ; preds = %if.then61
  %length69 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 1, !dbg !1731
  store i64 0, i64* %length69, align 8, !dbg !1731
  br label %if.end70, !dbg !1732

if.end70:                                         ; preds = %if.end68, %if.end55
  br label %while.cond28, !dbg !1733

while.end71:                                      ; preds = %if.then53, %while.cond28
  br label %while.cond, !dbg !1735

while.end72:                                      ; preds = %while.cond
  %57 = load i32, i32* %r, align 4, !dbg !1737
  %cmp73 = icmp slt i32 %57, 0, !dbg !1739
  br i1 %cmp73, label %if.then75, label %if.end78, !dbg !1740

if.then75:                                        ; preds = %while.end72
  %58 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !1741
  %archive76 = getelementptr inbounds %struct.archive_match, %struct.archive_match* %58, i32 0, i32 0, !dbg !1743
  %59 = load %struct.archive*, %struct.archive** %ar, align 8, !dbg !1744
  call void @archive_copy_error(%struct.archive* %archive76, %struct.archive* %59), !dbg !1745
  %60 = load %struct.archive*, %struct.archive** %ar, align 8, !dbg !1746
  %call77 = call i32 @archive_read_free(%struct.archive* %60), !dbg !1747
  call void @archive_string_free(%struct.archive_string* %as), !dbg !1748
  %61 = load i32, i32* %r, align 4, !dbg !1749
  store i32 %61, i32* %retval, align 4, !dbg !1750
  br label %return, !dbg !1750

if.end78:                                         ; preds = %while.end72
  %62 = load i32, i32* %r, align 4, !dbg !1751
  %cmp79 = icmp eq i32 %62, 1, !dbg !1753
  br i1 %cmp79, label %land.lhs.true, label %if.end92, !dbg !1754

land.lhs.true:                                    ; preds = %if.end78
  %length81 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 1, !dbg !1755
  %63 = load i64, i64* %length81, align 8, !dbg !1755
  %cmp82 = icmp ugt i64 %63, 0, !dbg !1757
  br i1 %cmp82, label %if.then84, label %if.end92, !dbg !1758

if.then84:                                        ; preds = %land.lhs.true
  %64 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !1759
  %65 = load %struct.match_list*, %struct.match_list** %mlist.addr, align 8, !dbg !1761
  %s85 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 0, !dbg !1762
  %66 = load i8*, i8** %s85, align 8, !dbg !1762
  %call86 = call i32 @add_pattern_mbs(%struct.archive_match* %64, %struct.match_list* %65, i8* %66), !dbg !1763
  store i32 %call86, i32* %r, align 4, !dbg !1764
  %67 = load i32, i32* %r, align 4, !dbg !1765
  %cmp87 = icmp ne i32 %67, 0, !dbg !1767
  br i1 %cmp87, label %if.then89, label %if.end91, !dbg !1768

if.then89:                                        ; preds = %if.then84
  %68 = load %struct.archive*, %struct.archive** %ar, align 8, !dbg !1769
  %call90 = call i32 @archive_read_free(%struct.archive* %68), !dbg !1771
  call void @archive_string_free(%struct.archive_string* %as), !dbg !1772
  %69 = load i32, i32* %r, align 4, !dbg !1773
  store i32 %69, i32* %retval, align 4, !dbg !1774
  br label %return, !dbg !1774

if.end91:                                         ; preds = %if.then84
  br label %if.end92, !dbg !1775

if.end92:                                         ; preds = %if.end91, %land.lhs.true, %if.end78
  %70 = load %struct.archive*, %struct.archive** %ar, align 8, !dbg !1776
  %call93 = call i32 @archive_read_free(%struct.archive* %70), !dbg !1777
  call void @archive_string_free(%struct.archive_string* %as), !dbg !1778
  store i32 0, i32* %retval, align 4, !dbg !1779
  br label %return, !dbg !1779

return:                                           ; preds = %if.end92, %if.then89, %if.then75, %if.then66, %if.else23, %if.then22, %if.then13, %if.then4, %if.then
  %71 = load i32, i32* %retval, align 4, !dbg !1780
  ret i32 %71, !dbg !1780
}

; Function Attrs: nounwind uwtable
define i32 @archive_match_exclude_pattern_from_file_w(%struct.archive* %_a, i32* %pathname, i32 %nullSeparator) #0 !dbg !235 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %pathname.addr = alloca i32*, align 8
  %nullSeparator.addr = alloca i32, align 4
  %a = alloca %struct.archive_match*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !1781, metadata !394), !dbg !1782
  store i32* %pathname, i32** %pathname.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %pathname.addr, metadata !1783, metadata !394), !dbg !1784
  store i32 %nullSeparator, i32* %nullSeparator.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %nullSeparator.addr, metadata !1785, metadata !394), !dbg !1786
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a, metadata !1787, metadata !394), !dbg !1788
  br label %do.body, !dbg !1789

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !1790, metadata !394), !dbg !1792
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1793
  %call = call i32 @__archive_check_magic(%struct.archive* %0, i32 212668873, i32 1, i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.7, i32 0, i32 0)), !dbg !1793
  store i32 %call, i32* %magic_test, align 4, !dbg !1793
  %1 = load i32, i32* %magic_test, align 4, !dbg !1793
  %cmp = icmp eq i32 %1, -30, !dbg !1793
  br i1 %cmp, label %if.then, label %if.end, !dbg !1793

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !1795
  br label %return, !dbg !1795

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !1798

do.end:                                           ; preds = %if.end
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1800
  %3 = bitcast %struct.archive* %2 to %struct.archive_match*, !dbg !1801
  store %struct.archive_match* %3, %struct.archive_match** %a, align 8, !dbg !1802
  %4 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !1803
  %5 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !1804
  %exclusions = getelementptr inbounds %struct.archive_match, %struct.archive_match* %5, i32 0, i32 2, !dbg !1805
  %6 = load i32*, i32** %pathname.addr, align 8, !dbg !1806
  %7 = bitcast i32* %6 to i8*, !dbg !1806
  %8 = load i32, i32* %nullSeparator.addr, align 4, !dbg !1807
  %call1 = call i32 @add_pattern_from_file(%struct.archive_match* %4, %struct.match_list* %exclusions, i32 0, i8* %7, i32 %8), !dbg !1808
  store i32 %call1, i32* %retval, align 4, !dbg !1809
  br label %return, !dbg !1809

return:                                           ; preds = %do.end, %if.then
  %9 = load i32, i32* %retval, align 4, !dbg !1810
  ret i32 %9, !dbg !1810
}

; Function Attrs: nounwind uwtable
define i32 @archive_match_include_pattern(%struct.archive* %_a, i8* %pattern) #0 !dbg !238 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %pattern.addr = alloca i8*, align 8
  %a = alloca %struct.archive_match*, align 8
  %r = alloca i32, align 4
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !1811, metadata !394), !dbg !1812
  store i8* %pattern, i8** %pattern.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %pattern.addr, metadata !1813, metadata !394), !dbg !1814
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a, metadata !1815, metadata !394), !dbg !1816
  call void @llvm.dbg.declare(metadata i32* %r, metadata !1817, metadata !394), !dbg !1818
  br label %do.body, !dbg !1819

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !1820, metadata !394), !dbg !1822
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1823
  %call = call i32 @__archive_check_magic(%struct.archive* %0, i32 212668873, i32 1, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.8, i32 0, i32 0)), !dbg !1823
  store i32 %call, i32* %magic_test, align 4, !dbg !1823
  %1 = load i32, i32* %magic_test, align 4, !dbg !1823
  %cmp = icmp eq i32 %1, -30, !dbg !1823
  br i1 %cmp, label %if.then, label %if.end, !dbg !1823

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !1825
  br label %return, !dbg !1825

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !1828

do.end:                                           ; preds = %if.end
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1830
  %3 = bitcast %struct.archive* %2 to %struct.archive_match*, !dbg !1831
  store %struct.archive_match* %3, %struct.archive_match** %a, align 8, !dbg !1832
  %4 = load i8*, i8** %pattern.addr, align 8, !dbg !1833
  %cmp1 = icmp eq i8* %4, null, !dbg !1835
  br i1 %cmp1, label %if.then4, label %lor.lhs.false, !dbg !1836

lor.lhs.false:                                    ; preds = %do.end
  %5 = load i8*, i8** %pattern.addr, align 8, !dbg !1837
  %6 = load i8, i8* %5, align 1, !dbg !1839
  %conv = sext i8 %6 to i32, !dbg !1839
  %cmp2 = icmp eq i32 %conv, 0, !dbg !1840
  br i1 %cmp2, label %if.then4, label %if.end5, !dbg !1841

if.then4:                                         ; preds = %lor.lhs.false, %do.end
  %7 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !1842
  %archive = getelementptr inbounds %struct.archive_match, %struct.archive_match* %7, i32 0, i32 0, !dbg !1844
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 22, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.4, i32 0, i32 0)), !dbg !1845
  store i32 -25, i32* %retval, align 4, !dbg !1846
  br label %return, !dbg !1846

if.end5:                                          ; preds = %lor.lhs.false
  %8 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !1847
  %9 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !1849
  %inclusions = getelementptr inbounds %struct.archive_match, %struct.archive_match* %9, i32 0, i32 3, !dbg !1850
  %10 = load i8*, i8** %pattern.addr, align 8, !dbg !1851
  %call6 = call i32 @add_pattern_mbs(%struct.archive_match* %8, %struct.match_list* %inclusions, i8* %10), !dbg !1852
  store i32 %call6, i32* %r, align 4, !dbg !1853
  %cmp7 = icmp ne i32 %call6, 0, !dbg !1854
  br i1 %cmp7, label %if.then9, label %if.end10, !dbg !1855

if.then9:                                         ; preds = %if.end5
  %11 = load i32, i32* %r, align 4, !dbg !1856
  store i32 %11, i32* %retval, align 4, !dbg !1857
  br label %return, !dbg !1857

if.end10:                                         ; preds = %if.end5
  store i32 0, i32* %retval, align 4, !dbg !1858
  br label %return, !dbg !1858

return:                                           ; preds = %if.end10, %if.then9, %if.then4, %if.then
  %12 = load i32, i32* %retval, align 4, !dbg !1859
  ret i32 %12, !dbg !1859
}

; Function Attrs: nounwind uwtable
define i32 @archive_match_include_pattern_w(%struct.archive* %_a, i32* %pattern) #0 !dbg !239 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %pattern.addr = alloca i32*, align 8
  %a = alloca %struct.archive_match*, align 8
  %r = alloca i32, align 4
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !1860, metadata !394), !dbg !1861
  store i32* %pattern, i32** %pattern.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %pattern.addr, metadata !1862, metadata !394), !dbg !1863
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a, metadata !1864, metadata !394), !dbg !1865
  call void @llvm.dbg.declare(metadata i32* %r, metadata !1866, metadata !394), !dbg !1867
  br label %do.body, !dbg !1868

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !1869, metadata !394), !dbg !1871
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1872
  %call = call i32 @__archive_check_magic(%struct.archive* %0, i32 212668873, i32 1, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.9, i32 0, i32 0)), !dbg !1872
  store i32 %call, i32* %magic_test, align 4, !dbg !1872
  %1 = load i32, i32* %magic_test, align 4, !dbg !1872
  %cmp = icmp eq i32 %1, -30, !dbg !1872
  br i1 %cmp, label %if.then, label %if.end, !dbg !1872

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !1874
  br label %return, !dbg !1874

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !1877

do.end:                                           ; preds = %if.end
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1879
  %3 = bitcast %struct.archive* %2 to %struct.archive_match*, !dbg !1880
  store %struct.archive_match* %3, %struct.archive_match** %a, align 8, !dbg !1881
  %4 = load i32*, i32** %pattern.addr, align 8, !dbg !1882
  %cmp1 = icmp eq i32* %4, null, !dbg !1884
  br i1 %cmp1, label %if.then3, label %lor.lhs.false, !dbg !1885

lor.lhs.false:                                    ; preds = %do.end
  %5 = load i32*, i32** %pattern.addr, align 8, !dbg !1886
  %6 = load i32, i32* %5, align 4, !dbg !1888
  %cmp2 = icmp eq i32 %6, 0, !dbg !1889
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !1890

if.then3:                                         ; preds = %lor.lhs.false, %do.end
  %7 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !1891
  %archive = getelementptr inbounds %struct.archive_match, %struct.archive_match* %7, i32 0, i32 0, !dbg !1893
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 22, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.4, i32 0, i32 0)), !dbg !1894
  store i32 -25, i32* %retval, align 4, !dbg !1895
  br label %return, !dbg !1895

if.end4:                                          ; preds = %lor.lhs.false
  %8 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !1896
  %9 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !1898
  %inclusions = getelementptr inbounds %struct.archive_match, %struct.archive_match* %9, i32 0, i32 3, !dbg !1899
  %10 = load i32*, i32** %pattern.addr, align 8, !dbg !1900
  %call5 = call i32 @add_pattern_wcs(%struct.archive_match* %8, %struct.match_list* %inclusions, i32* %10), !dbg !1901
  store i32 %call5, i32* %r, align 4, !dbg !1902
  %cmp6 = icmp ne i32 %call5, 0, !dbg !1903
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !1904

if.then7:                                         ; preds = %if.end4
  %11 = load i32, i32* %r, align 4, !dbg !1905
  store i32 %11, i32* %retval, align 4, !dbg !1906
  br label %return, !dbg !1906

if.end8:                                          ; preds = %if.end4
  store i32 0, i32* %retval, align 4, !dbg !1907
  br label %return, !dbg !1907

return:                                           ; preds = %if.end8, %if.then7, %if.then3, %if.then
  %12 = load i32, i32* %retval, align 4, !dbg !1908
  ret i32 %12, !dbg !1908
}

; Function Attrs: nounwind uwtable
define i32 @archive_match_include_pattern_from_file(%struct.archive* %_a, i8* %pathname, i32 %nullSeparator) #0 !dbg !240 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %pathname.addr = alloca i8*, align 8
  %nullSeparator.addr = alloca i32, align 4
  %a = alloca %struct.archive_match*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !1909, metadata !394), !dbg !1910
  store i8* %pathname, i8** %pathname.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %pathname.addr, metadata !1911, metadata !394), !dbg !1912
  store i32 %nullSeparator, i32* %nullSeparator.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %nullSeparator.addr, metadata !1913, metadata !394), !dbg !1914
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a, metadata !1915, metadata !394), !dbg !1916
  br label %do.body, !dbg !1917

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !1918, metadata !394), !dbg !1920
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1921
  %call = call i32 @__archive_check_magic(%struct.archive* %0, i32 212668873, i32 1, i8* getelementptr inbounds ([40 x i8], [40 x i8]* @.str.10, i32 0, i32 0)), !dbg !1921
  store i32 %call, i32* %magic_test, align 4, !dbg !1921
  %1 = load i32, i32* %magic_test, align 4, !dbg !1921
  %cmp = icmp eq i32 %1, -30, !dbg !1921
  br i1 %cmp, label %if.then, label %if.end, !dbg !1921

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !1923
  br label %return, !dbg !1923

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !1926

do.end:                                           ; preds = %if.end
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1928
  %3 = bitcast %struct.archive* %2 to %struct.archive_match*, !dbg !1929
  store %struct.archive_match* %3, %struct.archive_match** %a, align 8, !dbg !1930
  %4 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !1931
  %5 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !1932
  %inclusions = getelementptr inbounds %struct.archive_match, %struct.archive_match* %5, i32 0, i32 3, !dbg !1933
  %6 = load i8*, i8** %pathname.addr, align 8, !dbg !1934
  %7 = load i32, i32* %nullSeparator.addr, align 4, !dbg !1935
  %call1 = call i32 @add_pattern_from_file(%struct.archive_match* %4, %struct.match_list* %inclusions, i32 1, i8* %6, i32 %7), !dbg !1936
  store i32 %call1, i32* %retval, align 4, !dbg !1937
  br label %return, !dbg !1937

return:                                           ; preds = %do.end, %if.then
  %8 = load i32, i32* %retval, align 4, !dbg !1938
  ret i32 %8, !dbg !1938
}

; Function Attrs: nounwind uwtable
define i32 @archive_match_include_pattern_from_file_w(%struct.archive* %_a, i32* %pathname, i32 %nullSeparator) #0 !dbg !241 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %pathname.addr = alloca i32*, align 8
  %nullSeparator.addr = alloca i32, align 4
  %a = alloca %struct.archive_match*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !1939, metadata !394), !dbg !1940
  store i32* %pathname, i32** %pathname.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %pathname.addr, metadata !1941, metadata !394), !dbg !1942
  store i32 %nullSeparator, i32* %nullSeparator.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %nullSeparator.addr, metadata !1943, metadata !394), !dbg !1944
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a, metadata !1945, metadata !394), !dbg !1946
  br label %do.body, !dbg !1947

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !1948, metadata !394), !dbg !1950
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1951
  %call = call i32 @__archive_check_magic(%struct.archive* %0, i32 212668873, i32 1, i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.11, i32 0, i32 0)), !dbg !1951
  store i32 %call, i32* %magic_test, align 4, !dbg !1951
  %1 = load i32, i32* %magic_test, align 4, !dbg !1951
  %cmp = icmp eq i32 %1, -30, !dbg !1951
  br i1 %cmp, label %if.then, label %if.end, !dbg !1951

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !1953
  br label %return, !dbg !1953

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !1956

do.end:                                           ; preds = %if.end
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1958
  %3 = bitcast %struct.archive* %2 to %struct.archive_match*, !dbg !1959
  store %struct.archive_match* %3, %struct.archive_match** %a, align 8, !dbg !1960
  %4 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !1961
  %5 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !1962
  %inclusions = getelementptr inbounds %struct.archive_match, %struct.archive_match* %5, i32 0, i32 3, !dbg !1963
  %6 = load i32*, i32** %pathname.addr, align 8, !dbg !1964
  %7 = bitcast i32* %6 to i8*, !dbg !1964
  %8 = load i32, i32* %nullSeparator.addr, align 4, !dbg !1965
  %call1 = call i32 @add_pattern_from_file(%struct.archive_match* %4, %struct.match_list* %inclusions, i32 0, i8* %7, i32 %8), !dbg !1966
  store i32 %call1, i32* %retval, align 4, !dbg !1967
  br label %return, !dbg !1967

return:                                           ; preds = %do.end, %if.then
  %9 = load i32, i32* %retval, align 4, !dbg !1968
  ret i32 %9, !dbg !1968
}

; Function Attrs: nounwind uwtable
define i32 @archive_match_path_excluded(%struct.archive* %_a, %struct.archive_entry* %entry1) #0 !dbg !242 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %a = alloca %struct.archive_match*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !1969, metadata !394), !dbg !1970
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1971, metadata !394), !dbg !1972
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a, metadata !1973, metadata !394), !dbg !1974
  br label %do.body, !dbg !1975

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !1976, metadata !394), !dbg !1978
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1979
  %call = call i32 @__archive_check_magic(%struct.archive* %0, i32 212668873, i32 1, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.12, i32 0, i32 0)), !dbg !1979
  store i32 %call, i32* %magic_test, align 4, !dbg !1979
  %1 = load i32, i32* %magic_test, align 4, !dbg !1979
  %cmp = icmp eq i32 %1, -30, !dbg !1979
  br i1 %cmp, label %if.then, label %if.end, !dbg !1979

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !1981
  br label %return, !dbg !1981

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !1984

do.end:                                           ; preds = %if.end
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1986
  %3 = bitcast %struct.archive* %2 to %struct.archive_match*, !dbg !1987
  store %struct.archive_match* %3, %struct.archive_match** %a, align 8, !dbg !1988
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1989
  %cmp2 = icmp eq %struct.archive_entry* %4, null, !dbg !1991
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !1992

if.then3:                                         ; preds = %do.end
  %5 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !1993
  %archive = getelementptr inbounds %struct.archive_match, %struct.archive_match* %5, i32 0, i32 0, !dbg !1995
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 22, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.2, i32 0, i32 0)), !dbg !1996
  store i32 -25, i32* %retval, align 4, !dbg !1997
  br label %return, !dbg !1997

if.end4:                                          ; preds = %do.end
  %6 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !1998
  %setflag = getelementptr inbounds %struct.archive_match, %struct.archive_match* %6, i32 0, i32 1, !dbg !2000
  %7 = load i32, i32* %setflag, align 8, !dbg !2000
  %and = and i32 %7, 1, !dbg !2001
  %cmp5 = icmp eq i32 %and, 0, !dbg !2002
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !2003

if.then6:                                         ; preds = %if.end4
  store i32 0, i32* %retval, align 4, !dbg !2004
  br label %return, !dbg !2004

if.end7:                                          ; preds = %if.end4
  %8 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !2005
  %9 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2006
  %call8 = call i8* @archive_entry_pathname(%struct.archive_entry* %9), !dbg !2007
  %call9 = call i32 @path_excluded(%struct.archive_match* %8, i32 1, i8* %call8), !dbg !2008
  store i32 %call9, i32* %retval, align 4, !dbg !2010
  br label %return, !dbg !2010

return:                                           ; preds = %if.end7, %if.then6, %if.then3, %if.then
  %10 = load i32, i32* %retval, align 4, !dbg !2011
  ret i32 %10, !dbg !2011
}

; Function Attrs: nounwind uwtable
define i32 @archive_match_path_unmatched_inclusions(%struct.archive* %_a) #0 !dbg !243 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_match*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !2012, metadata !394), !dbg !2013
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a, metadata !2014, metadata !394), !dbg !2015
  br label %do.body, !dbg !2016

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !2017, metadata !394), !dbg !2019
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !2020
  %call = call i32 @__archive_check_magic(%struct.archive* %0, i32 212668873, i32 1, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.13, i32 0, i32 0)), !dbg !2020
  store i32 %call, i32* %magic_test, align 4, !dbg !2020
  %1 = load i32, i32* %magic_test, align 4, !dbg !2020
  %cmp = icmp eq i32 %1, -30, !dbg !2020
  br i1 %cmp, label %if.then, label %if.end, !dbg !2020

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !2022
  br label %return, !dbg !2022

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !2025

do.end:                                           ; preds = %if.end
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !2027
  %3 = bitcast %struct.archive* %2 to %struct.archive_match*, !dbg !2028
  store %struct.archive_match* %3, %struct.archive_match** %a, align 8, !dbg !2029
  %4 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !2030
  %inclusions = getelementptr inbounds %struct.archive_match, %struct.archive_match* %4, i32 0, i32 3, !dbg !2031
  %unmatched_count = getelementptr inbounds %struct.match_list, %struct.match_list* %inclusions, i32 0, i32 3, !dbg !2032
  %5 = load i32, i32* %unmatched_count, align 4, !dbg !2032
  store i32 %5, i32* %retval, align 4, !dbg !2033
  br label %return, !dbg !2033

return:                                           ; preds = %do.end, %if.then
  %6 = load i32, i32* %retval, align 4, !dbg !2034
  ret i32 %6, !dbg !2034
}

; Function Attrs: nounwind uwtable
define i32 @archive_match_path_unmatched_inclusions_next(%struct.archive* %_a, i8** %_p) #0 !dbg !244 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %_p.addr = alloca i8**, align 8
  %a = alloca %struct.archive_match*, align 8
  %v = alloca i8*, align 8
  %r = alloca i32, align 4
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !2035, metadata !394), !dbg !2036
  store i8** %_p, i8*** %_p.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %_p.addr, metadata !2037, metadata !394), !dbg !2038
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a, metadata !2039, metadata !394), !dbg !2040
  call void @llvm.dbg.declare(metadata i8** %v, metadata !2041, metadata !394), !dbg !2042
  call void @llvm.dbg.declare(metadata i32* %r, metadata !2043, metadata !394), !dbg !2044
  br label %do.body, !dbg !2045

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !2046, metadata !394), !dbg !2048
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !2049
  %call = call i32 @__archive_check_magic(%struct.archive* %0, i32 212668873, i32 1, i8* getelementptr inbounds ([40 x i8], [40 x i8]* @.str.14, i32 0, i32 0)), !dbg !2049
  store i32 %call, i32* %magic_test, align 4, !dbg !2049
  %1 = load i32, i32* %magic_test, align 4, !dbg !2049
  %cmp = icmp eq i32 %1, -30, !dbg !2049
  br i1 %cmp, label %if.then, label %if.end, !dbg !2049

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !2051
  br label %return, !dbg !2051

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !2054

do.end:                                           ; preds = %if.end
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !2056
  %3 = bitcast %struct.archive* %2 to %struct.archive_match*, !dbg !2057
  store %struct.archive_match* %3, %struct.archive_match** %a, align 8, !dbg !2058
  %4 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !2059
  %5 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !2060
  %inclusions = getelementptr inbounds %struct.archive_match, %struct.archive_match* %5, i32 0, i32 3, !dbg !2061
  %call1 = call i32 @match_list_unmatched_inclusions_next(%struct.archive_match* %4, %struct.match_list* %inclusions, i32 1, i8** %v), !dbg !2062
  store i32 %call1, i32* %r, align 4, !dbg !2063
  %6 = load i8*, i8** %v, align 8, !dbg !2064
  %7 = load i8**, i8*** %_p.addr, align 8, !dbg !2065
  store i8* %6, i8** %7, align 8, !dbg !2066
  %8 = load i32, i32* %r, align 4, !dbg !2067
  store i32 %8, i32* %retval, align 4, !dbg !2068
  br label %return, !dbg !2068

return:                                           ; preds = %do.end, %if.then
  %9 = load i32, i32* %retval, align 4, !dbg !2069
  ret i32 %9, !dbg !2069
}

; Function Attrs: nounwind uwtable
define internal i32 @match_list_unmatched_inclusions_next(%struct.archive_match* %a, %struct.match_list* %list, i32 %mbs, i8** %vp) #0 !dbg !305 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_match*, align 8
  %list.addr = alloca %struct.match_list*, align 8
  %mbs.addr = alloca i32, align 4
  %vp.addr = alloca i8**, align 8
  %m = alloca %struct.match*, align 8
  %r = alloca i32, align 4
  %p = alloca i8*, align 8
  %p24 = alloca i32*, align 8
  store %struct.archive_match* %a, %struct.archive_match** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a.addr, metadata !2070, metadata !394), !dbg !2071
  store %struct.match_list* %list, %struct.match_list** %list.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.match_list** %list.addr, metadata !2072, metadata !394), !dbg !2073
  store i32 %mbs, i32* %mbs.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %mbs.addr, metadata !2074, metadata !394), !dbg !2075
  store i8** %vp, i8*** %vp.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %vp.addr, metadata !2076, metadata !394), !dbg !2077
  call void @llvm.dbg.declare(metadata %struct.match** %m, metadata !2078, metadata !394), !dbg !2079
  %0 = load i8**, i8*** %vp.addr, align 8, !dbg !2080
  store i8* null, i8** %0, align 8, !dbg !2081
  %1 = load %struct.match_list*, %struct.match_list** %list.addr, align 8, !dbg !2082
  %unmatched_eof = getelementptr inbounds %struct.match_list, %struct.match_list* %1, i32 0, i32 5, !dbg !2084
  %2 = load i32, i32* %unmatched_eof, align 8, !dbg !2084
  %tobool = icmp ne i32 %2, 0, !dbg !2082
  br i1 %tobool, label %if.then, label %if.end, !dbg !2085

if.then:                                          ; preds = %entry
  %3 = load %struct.match_list*, %struct.match_list** %list.addr, align 8, !dbg !2086
  %unmatched_eof1 = getelementptr inbounds %struct.match_list, %struct.match_list* %3, i32 0, i32 5, !dbg !2088
  store i32 0, i32* %unmatched_eof1, align 8, !dbg !2089
  store i32 1, i32* %retval, align 4, !dbg !2090
  br label %return, !dbg !2090

if.end:                                           ; preds = %entry
  %4 = load %struct.match_list*, %struct.match_list** %list.addr, align 8, !dbg !2091
  %unmatched_next = getelementptr inbounds %struct.match_list, %struct.match_list* %4, i32 0, i32 4, !dbg !2093
  %5 = load %struct.match*, %struct.match** %unmatched_next, align 8, !dbg !2093
  %cmp = icmp eq %struct.match* %5, null, !dbg !2094
  br i1 %cmp, label %if.then2, label %if.end7, !dbg !2095

if.then2:                                         ; preds = %if.end
  %6 = load %struct.match_list*, %struct.match_list** %list.addr, align 8, !dbg !2096
  %unmatched_count = getelementptr inbounds %struct.match_list, %struct.match_list* %6, i32 0, i32 3, !dbg !2099
  %7 = load i32, i32* %unmatched_count, align 4, !dbg !2099
  %cmp3 = icmp eq i32 %7, 0, !dbg !2100
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !2101

if.then4:                                         ; preds = %if.then2
  store i32 1, i32* %retval, align 4, !dbg !2102
  br label %return, !dbg !2102

if.end5:                                          ; preds = %if.then2
  %8 = load %struct.match_list*, %struct.match_list** %list.addr, align 8, !dbg !2103
  %first = getelementptr inbounds %struct.match_list, %struct.match_list* %8, i32 0, i32 0, !dbg !2104
  %9 = load %struct.match*, %struct.match** %first, align 8, !dbg !2104
  %10 = load %struct.match_list*, %struct.match_list** %list.addr, align 8, !dbg !2105
  %unmatched_next6 = getelementptr inbounds %struct.match_list, %struct.match_list* %10, i32 0, i32 4, !dbg !2106
  store %struct.match* %9, %struct.match** %unmatched_next6, align 8, !dbg !2107
  br label %if.end7, !dbg !2108

if.end7:                                          ; preds = %if.end5, %if.end
  %11 = load %struct.match_list*, %struct.match_list** %list.addr, align 8, !dbg !2109
  %unmatched_next8 = getelementptr inbounds %struct.match_list, %struct.match_list* %11, i32 0, i32 4, !dbg !2111
  %12 = load %struct.match*, %struct.match** %unmatched_next8, align 8, !dbg !2111
  store %struct.match* %12, %struct.match** %m, align 8, !dbg !2112
  br label %for.cond, !dbg !2113

for.cond:                                         ; preds = %for.inc, %if.end7
  %13 = load %struct.match*, %struct.match** %m, align 8, !dbg !2114
  %cmp9 = icmp ne %struct.match* %13, null, !dbg !2117
  br i1 %cmp9, label %for.body, label %for.end, !dbg !2118

for.body:                                         ; preds = %for.cond
  call void @llvm.dbg.declare(metadata i32* %r, metadata !2119, metadata !394), !dbg !2121
  %14 = load %struct.match*, %struct.match** %m, align 8, !dbg !2122
  %matches = getelementptr inbounds %struct.match, %struct.match* %14, i32 0, i32 1, !dbg !2124
  %15 = load i32, i32* %matches, align 8, !dbg !2124
  %tobool10 = icmp ne i32 %15, 0, !dbg !2122
  br i1 %tobool10, label %if.then11, label %if.end12, !dbg !2125

if.then11:                                        ; preds = %for.body
  br label %for.inc, !dbg !2126

if.end12:                                         ; preds = %for.body
  %16 = load i32, i32* %mbs.addr, align 4, !dbg !2127
  %tobool13 = icmp ne i32 %16, 0, !dbg !2127
  br i1 %tobool13, label %if.then14, label %if.else, !dbg !2129

if.then14:                                        ; preds = %if.end12
  call void @llvm.dbg.declare(metadata i8** %p, metadata !2130, metadata !394), !dbg !2132
  %17 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2133
  %archive = getelementptr inbounds %struct.archive_match, %struct.archive_match* %17, i32 0, i32 0, !dbg !2134
  %18 = load %struct.match*, %struct.match** %m, align 8, !dbg !2135
  %pattern = getelementptr inbounds %struct.match, %struct.match* %18, i32 0, i32 2, !dbg !2136
  %call = call i32 @archive_mstring_get_mbs(%struct.archive* %archive, %struct.archive_mstring* %pattern, i8** %p), !dbg !2137
  store i32 %call, i32* %r, align 4, !dbg !2138
  %19 = load i32, i32* %r, align 4, !dbg !2139
  %cmp15 = icmp slt i32 %19, 0, !dbg !2141
  br i1 %cmp15, label %land.lhs.true, label %if.end20, !dbg !2142

land.lhs.true:                                    ; preds = %if.then14
  %call16 = call i32* @__errno_location() #1, !dbg !2143
  %20 = load i32, i32* %call16, align 4, !dbg !2143
  %cmp17 = icmp eq i32 %20, 12, !dbg !2145
  br i1 %cmp17, label %if.then18, label %if.end20, !dbg !2146

if.then18:                                        ; preds = %land.lhs.true
  %21 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2147
  %call19 = call i32 @error_nomem(%struct.archive_match* %21), !dbg !2148
  store i32 %call19, i32* %retval, align 4, !dbg !2149
  br label %return, !dbg !2149

if.end20:                                         ; preds = %land.lhs.true, %if.then14
  %22 = load i8*, i8** %p, align 8, !dbg !2150
  %cmp21 = icmp eq i8* %22, null, !dbg !2152
  br i1 %cmp21, label %if.then22, label %if.end23, !dbg !2153

if.then22:                                        ; preds = %if.end20
  store i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.32, i32 0, i32 0), i8** %p, align 8, !dbg !2154
  br label %if.end23, !dbg !2155

if.end23:                                         ; preds = %if.then22, %if.end20
  %23 = load i8*, i8** %p, align 8, !dbg !2156
  %24 = load i8**, i8*** %vp.addr, align 8, !dbg !2157
  store i8* %23, i8** %24, align 8, !dbg !2158
  br label %if.end38, !dbg !2159

if.else:                                          ; preds = %if.end12
  call void @llvm.dbg.declare(metadata i32** %p24, metadata !2160, metadata !394), !dbg !2162
  %25 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2163
  %archive25 = getelementptr inbounds %struct.archive_match, %struct.archive_match* %25, i32 0, i32 0, !dbg !2164
  %26 = load %struct.match*, %struct.match** %m, align 8, !dbg !2165
  %pattern26 = getelementptr inbounds %struct.match, %struct.match* %26, i32 0, i32 2, !dbg !2166
  %call27 = call i32 @archive_mstring_get_wcs(%struct.archive* %archive25, %struct.archive_mstring* %pattern26, i32** %p24), !dbg !2167
  store i32 %call27, i32* %r, align 4, !dbg !2168
  %27 = load i32, i32* %r, align 4, !dbg !2169
  %cmp28 = icmp slt i32 %27, 0, !dbg !2171
  br i1 %cmp28, label %land.lhs.true29, label %if.end34, !dbg !2172

land.lhs.true29:                                  ; preds = %if.else
  %call30 = call i32* @__errno_location() #1, !dbg !2173
  %28 = load i32, i32* %call30, align 4, !dbg !2173
  %cmp31 = icmp eq i32 %28, 12, !dbg !2175
  br i1 %cmp31, label %if.then32, label %if.end34, !dbg !2176

if.then32:                                        ; preds = %land.lhs.true29
  %29 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2177
  %call33 = call i32 @error_nomem(%struct.archive_match* %29), !dbg !2178
  store i32 %call33, i32* %retval, align 4, !dbg !2179
  br label %return, !dbg !2179

if.end34:                                         ; preds = %land.lhs.true29, %if.else
  %30 = load i32*, i32** %p24, align 8, !dbg !2180
  %cmp35 = icmp eq i32* %30, null, !dbg !2182
  br i1 %cmp35, label %if.then36, label %if.end37, !dbg !2183

if.then36:                                        ; preds = %if.end34
  store i32* getelementptr inbounds ([1 x i32], [1 x i32]* @.str.33, i32 0, i32 0), i32** %p24, align 8, !dbg !2184
  br label %if.end37, !dbg !2185

if.end37:                                         ; preds = %if.then36, %if.end34
  %31 = load i32*, i32** %p24, align 8, !dbg !2186
  %32 = bitcast i32* %31 to i8*, !dbg !2186
  %33 = load i8**, i8*** %vp.addr, align 8, !dbg !2187
  store i8* %32, i8** %33, align 8, !dbg !2188
  br label %if.end38

if.end38:                                         ; preds = %if.end37, %if.end23
  %34 = load %struct.match*, %struct.match** %m, align 8, !dbg !2189
  %next = getelementptr inbounds %struct.match, %struct.match* %34, i32 0, i32 0, !dbg !2190
  %35 = load %struct.match*, %struct.match** %next, align 8, !dbg !2190
  %36 = load %struct.match_list*, %struct.match_list** %list.addr, align 8, !dbg !2191
  %unmatched_next39 = getelementptr inbounds %struct.match_list, %struct.match_list* %36, i32 0, i32 4, !dbg !2192
  store %struct.match* %35, %struct.match** %unmatched_next39, align 8, !dbg !2193
  %37 = load %struct.match_list*, %struct.match_list** %list.addr, align 8, !dbg !2194
  %unmatched_next40 = getelementptr inbounds %struct.match_list, %struct.match_list* %37, i32 0, i32 4, !dbg !2196
  %38 = load %struct.match*, %struct.match** %unmatched_next40, align 8, !dbg !2196
  %cmp41 = icmp eq %struct.match* %38, null, !dbg !2197
  br i1 %cmp41, label %if.then42, label %if.end44, !dbg !2198

if.then42:                                        ; preds = %if.end38
  %39 = load %struct.match_list*, %struct.match_list** %list.addr, align 8, !dbg !2199
  %unmatched_eof43 = getelementptr inbounds %struct.match_list, %struct.match_list* %39, i32 0, i32 5, !dbg !2200
  store i32 1, i32* %unmatched_eof43, align 8, !dbg !2201
  br label %if.end44, !dbg !2199

if.end44:                                         ; preds = %if.then42, %if.end38
  store i32 0, i32* %retval, align 4, !dbg !2202
  br label %return, !dbg !2202

for.inc:                                          ; preds = %if.then11
  %40 = load %struct.match*, %struct.match** %m, align 8, !dbg !2203
  %next45 = getelementptr inbounds %struct.match, %struct.match* %40, i32 0, i32 0, !dbg !2205
  %41 = load %struct.match*, %struct.match** %next45, align 8, !dbg !2205
  store %struct.match* %41, %struct.match** %m, align 8, !dbg !2206
  br label %for.cond, !dbg !2207

for.end:                                          ; preds = %for.cond
  %42 = load %struct.match_list*, %struct.match_list** %list.addr, align 8, !dbg !2208
  %unmatched_next46 = getelementptr inbounds %struct.match_list, %struct.match_list* %42, i32 0, i32 4, !dbg !2209
  store %struct.match* null, %struct.match** %unmatched_next46, align 8, !dbg !2210
  store i32 1, i32* %retval, align 4, !dbg !2211
  br label %return, !dbg !2211

return:                                           ; preds = %for.end, %if.end44, %if.then32, %if.then18, %if.then4, %if.then
  %43 = load i32, i32* %retval, align 4, !dbg !2212
  ret i32 %43, !dbg !2212
}

; Function Attrs: nounwind uwtable
define i32 @archive_match_path_unmatched_inclusions_next_w(%struct.archive* %_a, i32** %_p) #0 !dbg !248 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %_p.addr = alloca i32**, align 8
  %a = alloca %struct.archive_match*, align 8
  %v = alloca i8*, align 8
  %r = alloca i32, align 4
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !2213, metadata !394), !dbg !2214
  store i32** %_p, i32*** %_p.addr, align 8
  call void @llvm.dbg.declare(metadata i32*** %_p.addr, metadata !2215, metadata !394), !dbg !2216
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a, metadata !2217, metadata !394), !dbg !2218
  call void @llvm.dbg.declare(metadata i8** %v, metadata !2219, metadata !394), !dbg !2220
  call void @llvm.dbg.declare(metadata i32* %r, metadata !2221, metadata !394), !dbg !2222
  br label %do.body, !dbg !2223

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !2224, metadata !394), !dbg !2226
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !2227
  %call = call i32 @__archive_check_magic(%struct.archive* %0, i32 212668873, i32 1, i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.15, i32 0, i32 0)), !dbg !2227
  store i32 %call, i32* %magic_test, align 4, !dbg !2227
  %1 = load i32, i32* %magic_test, align 4, !dbg !2227
  %cmp = icmp eq i32 %1, -30, !dbg !2227
  br i1 %cmp, label %if.then, label %if.end, !dbg !2227

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !2229
  br label %return, !dbg !2229

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !2232

do.end:                                           ; preds = %if.end
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !2234
  %3 = bitcast %struct.archive* %2 to %struct.archive_match*, !dbg !2235
  store %struct.archive_match* %3, %struct.archive_match** %a, align 8, !dbg !2236
  %4 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !2237
  %5 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !2238
  %inclusions = getelementptr inbounds %struct.archive_match, %struct.archive_match* %5, i32 0, i32 3, !dbg !2239
  %call1 = call i32 @match_list_unmatched_inclusions_next(%struct.archive_match* %4, %struct.match_list* %inclusions, i32 0, i8** %v), !dbg !2240
  store i32 %call1, i32* %r, align 4, !dbg !2241
  %6 = load i8*, i8** %v, align 8, !dbg !2242
  %7 = bitcast i8* %6 to i32*, !dbg !2243
  %8 = load i32**, i32*** %_p.addr, align 8, !dbg !2244
  store i32* %7, i32** %8, align 8, !dbg !2245
  %9 = load i32, i32* %r, align 4, !dbg !2246
  store i32 %9, i32* %retval, align 4, !dbg !2247
  br label %return, !dbg !2247

return:                                           ; preds = %do.end, %if.then
  %10 = load i32, i32* %retval, align 4, !dbg !2248
  ret i32 %10, !dbg !2248
}

; Function Attrs: nounwind uwtable
define i32 @archive_match_include_time(%struct.archive* %_a, i32 %flag, i64 %sec, i64 %nsec) #0 !dbg !252 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %flag.addr = alloca i32, align 4
  %sec.addr = alloca i64, align 8
  %nsec.addr = alloca i64, align 8
  %r = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !2249, metadata !394), !dbg !2250
  store i32 %flag, i32* %flag.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flag.addr, metadata !2251, metadata !394), !dbg !2252
  store i64 %sec, i64* %sec.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %sec.addr, metadata !2253, metadata !394), !dbg !2254
  store i64 %nsec, i64* %nsec.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %nsec.addr, metadata !2255, metadata !394), !dbg !2256
  call void @llvm.dbg.declare(metadata i32* %r, metadata !2257, metadata !394), !dbg !2258
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !2259
  %1 = load i32, i32* %flag.addr, align 4, !dbg !2260
  %call = call i32 @validate_time_flag(%struct.archive* %0, i32 %1, i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.16, i32 0, i32 0)), !dbg !2261
  store i32 %call, i32* %r, align 4, !dbg !2262
  %2 = load i32, i32* %r, align 4, !dbg !2263
  %cmp = icmp ne i32 %2, 0, !dbg !2265
  br i1 %cmp, label %if.then, label %if.end, !dbg !2266

if.then:                                          ; preds = %entry
  %3 = load i32, i32* %r, align 4, !dbg !2267
  store i32 %3, i32* %retval, align 4, !dbg !2268
  br label %return, !dbg !2268

if.end:                                           ; preds = %entry
  %4 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !2269
  %5 = bitcast %struct.archive* %4 to %struct.archive_match*, !dbg !2270
  %6 = load i32, i32* %flag.addr, align 4, !dbg !2271
  %7 = load i64, i64* %sec.addr, align 8, !dbg !2272
  %8 = load i64, i64* %nsec.addr, align 8, !dbg !2273
  %9 = load i64, i64* %sec.addr, align 8, !dbg !2274
  %10 = load i64, i64* %nsec.addr, align 8, !dbg !2275
  %call1 = call i32 @set_timefilter(%struct.archive_match* %5, i32 %6, i64 %7, i64 %8, i64 %9, i64 %10), !dbg !2276
  store i32 %call1, i32* %retval, align 4, !dbg !2277
  br label %return, !dbg !2277

return:                                           ; preds = %if.end, %if.then
  %11 = load i32, i32* %retval, align 4, !dbg !2278
  ret i32 %11, !dbg !2278
}

; Function Attrs: nounwind uwtable
define internal i32 @validate_time_flag(%struct.archive* %_a, i32 %flag, i8* %_fn) #0 !dbg !308 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %flag.addr = alloca i32, align 4
  %_fn.addr = alloca i8*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !2279, metadata !394), !dbg !2280
  store i32 %flag, i32* %flag.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flag.addr, metadata !2281, metadata !394), !dbg !2282
  store i8* %_fn, i8** %_fn.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %_fn.addr, metadata !2283, metadata !394), !dbg !2284
  br label %do.body, !dbg !2285

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !2286, metadata !394), !dbg !2288
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !2289
  %1 = load i8*, i8** %_fn.addr, align 8, !dbg !2289
  %call = call i32 @__archive_check_magic(%struct.archive* %0, i32 212668873, i32 1, i8* %1), !dbg !2289
  store i32 %call, i32* %magic_test, align 4, !dbg !2289
  %2 = load i32, i32* %magic_test, align 4, !dbg !2289
  %cmp = icmp eq i32 %2, -30, !dbg !2289
  br i1 %cmp, label %if.then, label %if.end, !dbg !2289

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !2291
  br label %return, !dbg !2291

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !2294

do.end:                                           ; preds = %if.end
  %3 = load i32, i32* %flag.addr, align 4, !dbg !2296
  %and = and i32 %3, 64512, !dbg !2298
  %tobool = icmp ne i32 %and, 0, !dbg !2298
  br i1 %tobool, label %if.then1, label %if.end2, !dbg !2299

if.then1:                                         ; preds = %do.end
  %4 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !2300
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %4, i32 22, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.34, i32 0, i32 0)), !dbg !2302
  store i32 -25, i32* %retval, align 4, !dbg !2303
  br label %return, !dbg !2303

if.end2:                                          ; preds = %do.end
  %5 = load i32, i32* %flag.addr, align 4, !dbg !2304
  %and3 = and i32 %5, 768, !dbg !2306
  %cmp4 = icmp eq i32 %and3, 0, !dbg !2307
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !2308

if.then5:                                         ; preds = %if.end2
  %6 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !2309
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %6, i32 22, i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.35, i32 0, i32 0)), !dbg !2311
  store i32 -25, i32* %retval, align 4, !dbg !2312
  br label %return, !dbg !2312

if.end6:                                          ; preds = %if.end2
  %7 = load i32, i32* %flag.addr, align 4, !dbg !2313
  %and7 = and i32 %7, 236, !dbg !2315
  %tobool8 = icmp ne i32 %and7, 0, !dbg !2315
  br i1 %tobool8, label %if.then9, label %if.end10, !dbg !2316

if.then9:                                         ; preds = %if.end6
  %8 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !2317
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %8, i32 22, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.36, i32 0, i32 0)), !dbg !2319
  store i32 -25, i32* %retval, align 4, !dbg !2320
  br label %return, !dbg !2320

if.end10:                                         ; preds = %if.end6
  %9 = load i32, i32* %flag.addr, align 4, !dbg !2321
  %and11 = and i32 %9, 19, !dbg !2323
  %cmp12 = icmp eq i32 %and11, 0, !dbg !2324
  br i1 %cmp12, label %if.then13, label %if.end14, !dbg !2325

if.then13:                                        ; preds = %if.end10
  %10 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !2326
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %10, i32 22, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.37, i32 0, i32 0)), !dbg !2328
  store i32 -25, i32* %retval, align 4, !dbg !2329
  br label %return, !dbg !2329

if.end14:                                         ; preds = %if.end10
  store i32 0, i32* %retval, align 4, !dbg !2330
  br label %return, !dbg !2330

return:                                           ; preds = %if.end14, %if.then13, %if.then9, %if.then5, %if.then1, %if.then
  %11 = load i32, i32* %retval, align 4, !dbg !2331
  ret i32 %11, !dbg !2331
}

; Function Attrs: nounwind uwtable
define internal i32 @set_timefilter(%struct.archive_match* %a, i32 %timetype, i64 %mtime_sec, i64 %mtime_nsec, i64 %ctime_sec, i64 %ctime_nsec) #0 !dbg !309 {
entry:
  %a.addr = alloca %struct.archive_match*, align 8
  %timetype.addr = alloca i32, align 4
  %mtime_sec.addr = alloca i64, align 8
  %mtime_nsec.addr = alloca i64, align 8
  %ctime_sec.addr = alloca i64, align 8
  %ctime_nsec.addr = alloca i64, align 8
  store %struct.archive_match* %a, %struct.archive_match** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a.addr, metadata !2332, metadata !394), !dbg !2333
  store i32 %timetype, i32* %timetype.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %timetype.addr, metadata !2334, metadata !394), !dbg !2335
  store i64 %mtime_sec, i64* %mtime_sec.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %mtime_sec.addr, metadata !2336, metadata !394), !dbg !2337
  store i64 %mtime_nsec, i64* %mtime_nsec.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %mtime_nsec.addr, metadata !2338, metadata !394), !dbg !2339
  store i64 %ctime_sec, i64* %ctime_sec.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %ctime_sec.addr, metadata !2340, metadata !394), !dbg !2341
  store i64 %ctime_nsec, i64* %ctime_nsec.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %ctime_nsec.addr, metadata !2342, metadata !394), !dbg !2343
  %0 = load i32, i32* %timetype.addr, align 4, !dbg !2344
  %and = and i32 %0, 256, !dbg !2346
  %tobool = icmp ne i32 %and, 0, !dbg !2346
  br i1 %tobool, label %if.then, label %if.end14, !dbg !2347

if.then:                                          ; preds = %entry
  %1 = load i32, i32* %timetype.addr, align 4, !dbg !2348
  %and1 = and i32 %1, 1, !dbg !2351
  %tobool2 = icmp ne i32 %and1, 0, !dbg !2351
  br i1 %tobool2, label %if.then4, label %lor.lhs.false, !dbg !2352

lor.lhs.false:                                    ; preds = %if.then
  %2 = load i32, i32* %timetype.addr, align 4, !dbg !2353
  %and3 = and i32 %2, 19, !dbg !2353
  %cmp = icmp eq i32 %and3, 16, !dbg !2353
  br i1 %cmp, label %if.then4, label %if.end, !dbg !2355

if.then4:                                         ; preds = %lor.lhs.false, %if.then
  %3 = load i32, i32* %timetype.addr, align 4, !dbg !2356
  %4 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2358
  %newer_mtime_filter = getelementptr inbounds %struct.archive_match, %struct.archive_match* %4, i32 0, i32 5, !dbg !2359
  store i32 %3, i32* %newer_mtime_filter, align 8, !dbg !2360
  %5 = load i64, i64* %mtime_sec.addr, align 8, !dbg !2361
  %6 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2362
  %newer_mtime_sec = getelementptr inbounds %struct.archive_match, %struct.archive_match* %6, i32 0, i32 6, !dbg !2363
  store i64 %5, i64* %newer_mtime_sec, align 8, !dbg !2364
  %7 = load i64, i64* %mtime_nsec.addr, align 8, !dbg !2365
  %8 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2366
  %newer_mtime_nsec = getelementptr inbounds %struct.archive_match, %struct.archive_match* %8, i32 0, i32 7, !dbg !2367
  store i64 %7, i64* %newer_mtime_nsec, align 8, !dbg !2368
  %9 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2369
  %setflag = getelementptr inbounds %struct.archive_match, %struct.archive_match* %9, i32 0, i32 1, !dbg !2370
  %10 = load i32, i32* %setflag, align 8, !dbg !2371
  %or = or i32 %10, 2, !dbg !2371
  store i32 %or, i32* %setflag, align 8, !dbg !2371
  br label %if.end, !dbg !2372

if.end:                                           ; preds = %if.then4, %lor.lhs.false
  %11 = load i32, i32* %timetype.addr, align 4, !dbg !2373
  %and5 = and i32 %11, 2, !dbg !2375
  %tobool6 = icmp ne i32 %and5, 0, !dbg !2375
  br i1 %tobool6, label %if.then10, label %lor.lhs.false7, !dbg !2376

lor.lhs.false7:                                   ; preds = %if.end
  %12 = load i32, i32* %timetype.addr, align 4, !dbg !2377
  %and8 = and i32 %12, 19, !dbg !2377
  %cmp9 = icmp eq i32 %and8, 16, !dbg !2377
  br i1 %cmp9, label %if.then10, label %if.end13, !dbg !2379

if.then10:                                        ; preds = %lor.lhs.false7, %if.end
  %13 = load i32, i32* %timetype.addr, align 4, !dbg !2380
  %14 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2382
  %older_mtime_filter = getelementptr inbounds %struct.archive_match, %struct.archive_match* %14, i32 0, i32 11, !dbg !2383
  store i32 %13, i32* %older_mtime_filter, align 8, !dbg !2384
  %15 = load i64, i64* %mtime_sec.addr, align 8, !dbg !2385
  %16 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2386
  %older_mtime_sec = getelementptr inbounds %struct.archive_match, %struct.archive_match* %16, i32 0, i32 12, !dbg !2387
  store i64 %15, i64* %older_mtime_sec, align 8, !dbg !2388
  %17 = load i64, i64* %mtime_nsec.addr, align 8, !dbg !2389
  %18 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2390
  %older_mtime_nsec = getelementptr inbounds %struct.archive_match, %struct.archive_match* %18, i32 0, i32 13, !dbg !2391
  store i64 %17, i64* %older_mtime_nsec, align 8, !dbg !2392
  %19 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2393
  %setflag11 = getelementptr inbounds %struct.archive_match, %struct.archive_match* %19, i32 0, i32 1, !dbg !2394
  %20 = load i32, i32* %setflag11, align 8, !dbg !2395
  %or12 = or i32 %20, 2, !dbg !2395
  store i32 %or12, i32* %setflag11, align 8, !dbg !2395
  br label %if.end13, !dbg !2396

if.end13:                                         ; preds = %if.then10, %lor.lhs.false7
  br label %if.end14, !dbg !2397

if.end14:                                         ; preds = %if.end13, %entry
  %21 = load i32, i32* %timetype.addr, align 4, !dbg !2398
  %and15 = and i32 %21, 512, !dbg !2400
  %tobool16 = icmp ne i32 %and15, 0, !dbg !2400
  br i1 %tobool16, label %if.then17, label %if.end36, !dbg !2401

if.then17:                                        ; preds = %if.end14
  %22 = load i32, i32* %timetype.addr, align 4, !dbg !2402
  %and18 = and i32 %22, 1, !dbg !2405
  %tobool19 = icmp ne i32 %and18, 0, !dbg !2405
  br i1 %tobool19, label %if.then23, label %lor.lhs.false20, !dbg !2406

lor.lhs.false20:                                  ; preds = %if.then17
  %23 = load i32, i32* %timetype.addr, align 4, !dbg !2407
  %and21 = and i32 %23, 19, !dbg !2407
  %cmp22 = icmp eq i32 %and21, 16, !dbg !2407
  br i1 %cmp22, label %if.then23, label %if.end26, !dbg !2409

if.then23:                                        ; preds = %lor.lhs.false20, %if.then17
  %24 = load i32, i32* %timetype.addr, align 4, !dbg !2410
  %25 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2412
  %newer_ctime_filter = getelementptr inbounds %struct.archive_match, %struct.archive_match* %25, i32 0, i32 8, !dbg !2413
  store i32 %24, i32* %newer_ctime_filter, align 8, !dbg !2414
  %26 = load i64, i64* %ctime_sec.addr, align 8, !dbg !2415
  %27 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2416
  %newer_ctime_sec = getelementptr inbounds %struct.archive_match, %struct.archive_match* %27, i32 0, i32 9, !dbg !2417
  store i64 %26, i64* %newer_ctime_sec, align 8, !dbg !2418
  %28 = load i64, i64* %ctime_nsec.addr, align 8, !dbg !2419
  %29 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2420
  %newer_ctime_nsec = getelementptr inbounds %struct.archive_match, %struct.archive_match* %29, i32 0, i32 10, !dbg !2421
  store i64 %28, i64* %newer_ctime_nsec, align 8, !dbg !2422
  %30 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2423
  %setflag24 = getelementptr inbounds %struct.archive_match, %struct.archive_match* %30, i32 0, i32 1, !dbg !2424
  %31 = load i32, i32* %setflag24, align 8, !dbg !2425
  %or25 = or i32 %31, 2, !dbg !2425
  store i32 %or25, i32* %setflag24, align 8, !dbg !2425
  br label %if.end26, !dbg !2426

if.end26:                                         ; preds = %if.then23, %lor.lhs.false20
  %32 = load i32, i32* %timetype.addr, align 4, !dbg !2427
  %and27 = and i32 %32, 2, !dbg !2429
  %tobool28 = icmp ne i32 %and27, 0, !dbg !2429
  br i1 %tobool28, label %if.then32, label %lor.lhs.false29, !dbg !2430

lor.lhs.false29:                                  ; preds = %if.end26
  %33 = load i32, i32* %timetype.addr, align 4, !dbg !2431
  %and30 = and i32 %33, 19, !dbg !2431
  %cmp31 = icmp eq i32 %and30, 16, !dbg !2431
  br i1 %cmp31, label %if.then32, label %if.end35, !dbg !2433

if.then32:                                        ; preds = %lor.lhs.false29, %if.end26
  %34 = load i32, i32* %timetype.addr, align 4, !dbg !2434
  %35 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2436
  %older_ctime_filter = getelementptr inbounds %struct.archive_match, %struct.archive_match* %35, i32 0, i32 14, !dbg !2437
  store i32 %34, i32* %older_ctime_filter, align 8, !dbg !2438
  %36 = load i64, i64* %ctime_sec.addr, align 8, !dbg !2439
  %37 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2440
  %older_ctime_sec = getelementptr inbounds %struct.archive_match, %struct.archive_match* %37, i32 0, i32 15, !dbg !2441
  store i64 %36, i64* %older_ctime_sec, align 8, !dbg !2442
  %38 = load i64, i64* %ctime_nsec.addr, align 8, !dbg !2443
  %39 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2444
  %older_ctime_nsec = getelementptr inbounds %struct.archive_match, %struct.archive_match* %39, i32 0, i32 16, !dbg !2445
  store i64 %38, i64* %older_ctime_nsec, align 8, !dbg !2446
  %40 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2447
  %setflag33 = getelementptr inbounds %struct.archive_match, %struct.archive_match* %40, i32 0, i32 1, !dbg !2448
  %41 = load i32, i32* %setflag33, align 8, !dbg !2449
  %or34 = or i32 %41, 2, !dbg !2449
  store i32 %or34, i32* %setflag33, align 8, !dbg !2449
  br label %if.end35, !dbg !2450

if.end35:                                         ; preds = %if.then32, %lor.lhs.false29
  br label %if.end36, !dbg !2451

if.end36:                                         ; preds = %if.end35, %if.end14
  ret i32 0, !dbg !2452
}

; Function Attrs: nounwind uwtable
define i32 @archive_match_include_date(%struct.archive* %_a, i32 %flag, i8* %datestr) #0 !dbg !255 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %flag.addr = alloca i32, align 4
  %datestr.addr = alloca i8*, align 8
  %r = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !2453, metadata !394), !dbg !2454
  store i32 %flag, i32* %flag.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flag.addr, metadata !2455, metadata !394), !dbg !2456
  store i8* %datestr, i8** %datestr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %datestr.addr, metadata !2457, metadata !394), !dbg !2458
  call void @llvm.dbg.declare(metadata i32* %r, metadata !2459, metadata !394), !dbg !2460
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !2461
  %1 = load i32, i32* %flag.addr, align 4, !dbg !2462
  %call = call i32 @validate_time_flag(%struct.archive* %0, i32 %1, i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.17, i32 0, i32 0)), !dbg !2463
  store i32 %call, i32* %r, align 4, !dbg !2464
  %2 = load i32, i32* %r, align 4, !dbg !2465
  %cmp = icmp ne i32 %2, 0, !dbg !2467
  br i1 %cmp, label %if.then, label %if.end, !dbg !2468

if.then:                                          ; preds = %entry
  %3 = load i32, i32* %r, align 4, !dbg !2469
  store i32 %3, i32* %retval, align 4, !dbg !2470
  br label %return, !dbg !2470

if.end:                                           ; preds = %entry
  %4 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !2471
  %5 = bitcast %struct.archive* %4 to %struct.archive_match*, !dbg !2472
  %6 = load i32, i32* %flag.addr, align 4, !dbg !2473
  %7 = load i8*, i8** %datestr.addr, align 8, !dbg !2474
  %call1 = call i32 @set_timefilter_date(%struct.archive_match* %5, i32 %6, i8* %7), !dbg !2475
  store i32 %call1, i32* %retval, align 4, !dbg !2476
  br label %return, !dbg !2476

return:                                           ; preds = %if.end, %if.then
  %8 = load i32, i32* %retval, align 4, !dbg !2477
  ret i32 %8, !dbg !2477
}

; Function Attrs: nounwind uwtable
define internal i32 @set_timefilter_date(%struct.archive_match* %a, i32 %timetype, i8* %datestr) #0 !dbg !312 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_match*, align 8
  %timetype.addr = alloca i32, align 4
  %datestr.addr = alloca i8*, align 8
  %t = alloca i64, align 8
  store %struct.archive_match* %a, %struct.archive_match** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a.addr, metadata !2478, metadata !394), !dbg !2479
  store i32 %timetype, i32* %timetype.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %timetype.addr, metadata !2480, metadata !394), !dbg !2481
  store i8* %datestr, i8** %datestr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %datestr.addr, metadata !2482, metadata !394), !dbg !2483
  call void @llvm.dbg.declare(metadata i64* %t, metadata !2484, metadata !394), !dbg !2485
  %0 = load i8*, i8** %datestr.addr, align 8, !dbg !2486
  %cmp = icmp eq i8* %0, null, !dbg !2488
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !2489

lor.lhs.false:                                    ; preds = %entry
  %1 = load i8*, i8** %datestr.addr, align 8, !dbg !2490
  %2 = load i8, i8* %1, align 1, !dbg !2492
  %conv = sext i8 %2 to i32, !dbg !2492
  %cmp1 = icmp eq i32 %conv, 0, !dbg !2493
  br i1 %cmp1, label %if.then, label %if.end, !dbg !2494

if.then:                                          ; preds = %lor.lhs.false, %entry
  %3 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2495
  %archive = getelementptr inbounds %struct.archive_match, %struct.archive_match* %3, i32 0, i32 0, !dbg !2497
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 22, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.38, i32 0, i32 0)), !dbg !2498
  store i32 -25, i32* %retval, align 4, !dbg !2499
  br label %return, !dbg !2499

if.end:                                           ; preds = %lor.lhs.false
  %4 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2500
  %now = getelementptr inbounds %struct.archive_match, %struct.archive_match* %4, i32 0, i32 4, !dbg !2501
  %5 = load i64, i64* %now, align 8, !dbg !2501
  %6 = load i8*, i8** %datestr.addr, align 8, !dbg !2502
  %call = call i64 @__archive_get_date(i64 %5, i8* %6), !dbg !2503
  store i64 %call, i64* %t, align 8, !dbg !2504
  %7 = load i64, i64* %t, align 8, !dbg !2505
  %cmp3 = icmp eq i64 %7, -1, !dbg !2507
  br i1 %cmp3, label %if.then5, label %if.end7, !dbg !2508

if.then5:                                         ; preds = %if.end
  %8 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2509
  %archive6 = getelementptr inbounds %struct.archive_match, %struct.archive_match* %8, i32 0, i32 0, !dbg !2511
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive6, i32 22, i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.39, i32 0, i32 0)), !dbg !2512
  store i32 -25, i32* %retval, align 4, !dbg !2513
  br label %return, !dbg !2513

if.end7:                                          ; preds = %if.end
  %9 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2514
  %10 = load i32, i32* %timetype.addr, align 4, !dbg !2515
  %11 = load i64, i64* %t, align 8, !dbg !2516
  %12 = load i64, i64* %t, align 8, !dbg !2517
  %call8 = call i32 @set_timefilter(%struct.archive_match* %9, i32 %10, i64 %11, i64 0, i64 %12, i64 0), !dbg !2518
  store i32 %call8, i32* %retval, align 4, !dbg !2519
  br label %return, !dbg !2519

return:                                           ; preds = %if.end7, %if.then5, %if.then
  %13 = load i32, i32* %retval, align 4, !dbg !2520
  ret i32 %13, !dbg !2520
}

; Function Attrs: nounwind uwtable
define i32 @archive_match_include_date_w(%struct.archive* %_a, i32 %flag, i32* %datestr) #0 !dbg !258 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %flag.addr = alloca i32, align 4
  %datestr.addr = alloca i32*, align 8
  %r = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !2521, metadata !394), !dbg !2522
  store i32 %flag, i32* %flag.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flag.addr, metadata !2523, metadata !394), !dbg !2524
  store i32* %datestr, i32** %datestr.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %datestr.addr, metadata !2525, metadata !394), !dbg !2526
  call void @llvm.dbg.declare(metadata i32* %r, metadata !2527, metadata !394), !dbg !2528
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !2529
  %1 = load i32, i32* %flag.addr, align 4, !dbg !2530
  %call = call i32 @validate_time_flag(%struct.archive* %0, i32 %1, i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.18, i32 0, i32 0)), !dbg !2531
  store i32 %call, i32* %r, align 4, !dbg !2532
  %2 = load i32, i32* %r, align 4, !dbg !2533
  %cmp = icmp ne i32 %2, 0, !dbg !2535
  br i1 %cmp, label %if.then, label %if.end, !dbg !2536

if.then:                                          ; preds = %entry
  %3 = load i32, i32* %r, align 4, !dbg !2537
  store i32 %3, i32* %retval, align 4, !dbg !2538
  br label %return, !dbg !2538

if.end:                                           ; preds = %entry
  %4 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !2539
  %5 = bitcast %struct.archive* %4 to %struct.archive_match*, !dbg !2540
  %6 = load i32, i32* %flag.addr, align 4, !dbg !2541
  %7 = load i32*, i32** %datestr.addr, align 8, !dbg !2542
  %call1 = call i32 @set_timefilter_date_w(%struct.archive_match* %5, i32 %6, i32* %7), !dbg !2543
  store i32 %call1, i32* %retval, align 4, !dbg !2544
  br label %return, !dbg !2544

return:                                           ; preds = %if.end, %if.then
  %8 = load i32, i32* %retval, align 4, !dbg !2545
  ret i32 %8, !dbg !2545
}

; Function Attrs: nounwind uwtable
define internal i32 @set_timefilter_date_w(%struct.archive_match* %a, i32 %timetype, i32* %datestr) #0 !dbg !315 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_match*, align 8
  %timetype.addr = alloca i32, align 4
  %datestr.addr = alloca i32*, align 8
  %as = alloca %struct.archive_string, align 8
  %t = alloca i64, align 8
  store %struct.archive_match* %a, %struct.archive_match** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a.addr, metadata !2546, metadata !394), !dbg !2547
  store i32 %timetype, i32* %timetype.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %timetype.addr, metadata !2548, metadata !394), !dbg !2549
  store i32* %datestr, i32** %datestr.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %datestr.addr, metadata !2550, metadata !394), !dbg !2551
  call void @llvm.dbg.declare(metadata %struct.archive_string* %as, metadata !2552, metadata !394), !dbg !2553
  call void @llvm.dbg.declare(metadata i64* %t, metadata !2554, metadata !394), !dbg !2555
  %0 = load i32*, i32** %datestr.addr, align 8, !dbg !2556
  %cmp = icmp eq i32* %0, null, !dbg !2558
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !2559

lor.lhs.false:                                    ; preds = %entry
  %1 = load i32*, i32** %datestr.addr, align 8, !dbg !2560
  %2 = load i32, i32* %1, align 4, !dbg !2562
  %cmp1 = icmp eq i32 %2, 0, !dbg !2563
  br i1 %cmp1, label %if.then, label %if.end, !dbg !2564

if.then:                                          ; preds = %lor.lhs.false, %entry
  %3 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2565
  %archive = getelementptr inbounds %struct.archive_match, %struct.archive_match* %3, i32 0, i32 0, !dbg !2567
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 22, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.38, i32 0, i32 0)), !dbg !2568
  store i32 -25, i32* %retval, align 4, !dbg !2569
  br label %return, !dbg !2569

if.end:                                           ; preds = %lor.lhs.false
  br label %do.body, !dbg !2570

do.body:                                          ; preds = %if.end
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 0, !dbg !2571
  store i8* null, i8** %s, align 8, !dbg !2571
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 1, !dbg !2571
  store i64 0, i64* %length, align 8, !dbg !2571
  %buffer_length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 2, !dbg !2571
  store i64 0, i64* %buffer_length, align 8, !dbg !2571
  br label %do.end, !dbg !2571

do.end:                                           ; preds = %do.body
  %4 = load i32*, i32** %datestr.addr, align 8, !dbg !2574
  %5 = load i32*, i32** %datestr.addr, align 8, !dbg !2576
  %call = call i64 @wcslen(i32* %5) #8, !dbg !2577
  %call2 = call i32 @archive_string_append_from_wcs(%struct.archive_string* %as, i32* %4, i64 %call), !dbg !2578
  %cmp3 = icmp slt i32 %call2, 0, !dbg !2580
  br i1 %cmp3, label %if.then4, label %if.end11, !dbg !2581

if.then4:                                         ; preds = %do.end
  call void @archive_string_free(%struct.archive_string* %as), !dbg !2582
  %call5 = call i32* @__errno_location() #1, !dbg !2584
  %6 = load i32, i32* %call5, align 4, !dbg !2584
  %cmp6 = icmp eq i32 %6, 12, !dbg !2586
  br i1 %cmp6, label %if.then7, label %if.end9, !dbg !2587

if.then7:                                         ; preds = %if.then4
  %7 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2588
  %call8 = call i32 @error_nomem(%struct.archive_match* %7), !dbg !2589
  store i32 %call8, i32* %retval, align 4, !dbg !2590
  br label %return, !dbg !2590

if.end9:                                          ; preds = %if.then4
  %8 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2591
  %archive10 = getelementptr inbounds %struct.archive_match, %struct.archive_match* %8, i32 0, i32 0, !dbg !2592
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive10, i32 -1, i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.40, i32 0, i32 0)), !dbg !2593
  store i32 -25, i32* %retval, align 4, !dbg !2594
  br label %return, !dbg !2594

if.end11:                                         ; preds = %do.end
  %9 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2595
  %now = getelementptr inbounds %struct.archive_match, %struct.archive_match* %9, i32 0, i32 4, !dbg !2596
  %10 = load i64, i64* %now, align 8, !dbg !2596
  %s12 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 0, !dbg !2597
  %11 = load i8*, i8** %s12, align 8, !dbg !2597
  %call13 = call i64 @__archive_get_date(i64 %10, i8* %11), !dbg !2598
  store i64 %call13, i64* %t, align 8, !dbg !2599
  call void @archive_string_free(%struct.archive_string* %as), !dbg !2600
  %12 = load i64, i64* %t, align 8, !dbg !2601
  %cmp14 = icmp eq i64 %12, -1, !dbg !2603
  br i1 %cmp14, label %if.then15, label %if.end17, !dbg !2604

if.then15:                                        ; preds = %if.end11
  %13 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2605
  %archive16 = getelementptr inbounds %struct.archive_match, %struct.archive_match* %13, i32 0, i32 0, !dbg !2607
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive16, i32 22, i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.39, i32 0, i32 0)), !dbg !2608
  store i32 -25, i32* %retval, align 4, !dbg !2609
  br label %return, !dbg !2609

if.end17:                                         ; preds = %if.end11
  %14 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2610
  %15 = load i32, i32* %timetype.addr, align 4, !dbg !2611
  %16 = load i64, i64* %t, align 8, !dbg !2612
  %17 = load i64, i64* %t, align 8, !dbg !2613
  %call18 = call i32 @set_timefilter(%struct.archive_match* %14, i32 %15, i64 %16, i64 0, i64 %17, i64 0), !dbg !2614
  store i32 %call18, i32* %retval, align 4, !dbg !2615
  br label %return, !dbg !2615

return:                                           ; preds = %if.end17, %if.then15, %if.end9, %if.then7, %if.then
  %18 = load i32, i32* %retval, align 4, !dbg !2616
  ret i32 %18, !dbg !2616
}

; Function Attrs: nounwind uwtable
define i32 @archive_match_include_file_time(%struct.archive* %_a, i32 %flag, i8* %pathname) #0 !dbg !261 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %flag.addr = alloca i32, align 4
  %pathname.addr = alloca i8*, align 8
  %r = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !2617, metadata !394), !dbg !2618
  store i32 %flag, i32* %flag.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flag.addr, metadata !2619, metadata !394), !dbg !2620
  store i8* %pathname, i8** %pathname.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %pathname.addr, metadata !2621, metadata !394), !dbg !2622
  call void @llvm.dbg.declare(metadata i32* %r, metadata !2623, metadata !394), !dbg !2624
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !2625
  %1 = load i32, i32* %flag.addr, align 4, !dbg !2626
  %call = call i32 @validate_time_flag(%struct.archive* %0, i32 %1, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.19, i32 0, i32 0)), !dbg !2627
  store i32 %call, i32* %r, align 4, !dbg !2628
  %2 = load i32, i32* %r, align 4, !dbg !2629
  %cmp = icmp ne i32 %2, 0, !dbg !2631
  br i1 %cmp, label %if.then, label %if.end, !dbg !2632

if.then:                                          ; preds = %entry
  %3 = load i32, i32* %r, align 4, !dbg !2633
  store i32 %3, i32* %retval, align 4, !dbg !2634
  br label %return, !dbg !2634

if.end:                                           ; preds = %entry
  %4 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !2635
  %5 = bitcast %struct.archive* %4 to %struct.archive_match*, !dbg !2636
  %6 = load i32, i32* %flag.addr, align 4, !dbg !2637
  %7 = load i8*, i8** %pathname.addr, align 8, !dbg !2638
  %call1 = call i32 @set_timefilter_pathname_mbs(%struct.archive_match* %5, i32 %6, i8* %7), !dbg !2639
  store i32 %call1, i32* %retval, align 4, !dbg !2640
  br label %return, !dbg !2640

return:                                           ; preds = %if.end, %if.then
  %8 = load i32, i32* %retval, align 4, !dbg !2641
  ret i32 %8, !dbg !2641
}

; Function Attrs: nounwind uwtable
define internal i32 @set_timefilter_pathname_mbs(%struct.archive_match* %a, i32 %timetype, i8* %path) #0 !dbg !318 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_match*, align 8
  %timetype.addr = alloca i32, align 4
  %path.addr = alloca i8*, align 8
  %st = alloca %struct.stat, align 8
  store %struct.archive_match* %a, %struct.archive_match** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a.addr, metadata !2642, metadata !394), !dbg !2643
  store i32 %timetype, i32* %timetype.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %timetype.addr, metadata !2644, metadata !394), !dbg !2645
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !2646, metadata !394), !dbg !2647
  call void @llvm.dbg.declare(metadata %struct.stat* %st, metadata !2648, metadata !394), !dbg !2649
  %0 = load i8*, i8** %path.addr, align 8, !dbg !2650
  %cmp = icmp eq i8* %0, null, !dbg !2652
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !2653

lor.lhs.false:                                    ; preds = %entry
  %1 = load i8*, i8** %path.addr, align 8, !dbg !2654
  %2 = load i8, i8* %1, align 1, !dbg !2656
  %conv = sext i8 %2 to i32, !dbg !2656
  %cmp1 = icmp eq i32 %conv, 0, !dbg !2657
  br i1 %cmp1, label %if.then, label %if.end, !dbg !2658

if.then:                                          ; preds = %lor.lhs.false, %entry
  %3 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2659
  %archive = getelementptr inbounds %struct.archive_match, %struct.archive_match* %3, i32 0, i32 0, !dbg !2661
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 22, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.41, i32 0, i32 0)), !dbg !2662
  store i32 -25, i32* %retval, align 4, !dbg !2663
  br label %return, !dbg !2663

if.end:                                           ; preds = %lor.lhs.false
  %4 = load i8*, i8** %path.addr, align 8, !dbg !2664
  %call = call i32 @stat(i8* %4, %struct.stat* %st) #7, !dbg !2666
  %cmp3 = icmp ne i32 %call, 0, !dbg !2667
  br i1 %cmp3, label %if.then5, label %if.end8, !dbg !2668

if.then5:                                         ; preds = %if.end
  %5 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2669
  %archive6 = getelementptr inbounds %struct.archive_match, %struct.archive_match* %5, i32 0, i32 0, !dbg !2671
  %call7 = call i32* @__errno_location() #1, !dbg !2672
  %6 = load i32, i32* %call7, align 4, !dbg !2672
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive6, i32 %6, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.42, i32 0, i32 0)), !dbg !2673
  store i32 -25, i32* %retval, align 4, !dbg !2675
  br label %return, !dbg !2675

if.end8:                                          ; preds = %if.end
  %7 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2676
  %8 = load i32, i32* %timetype.addr, align 4, !dbg !2677
  %call9 = call i32 @set_timefilter_stat(%struct.archive_match* %7, i32 %8, %struct.stat* %st), !dbg !2678
  store i32 %call9, i32* %retval, align 4, !dbg !2679
  br label %return, !dbg !2679

return:                                           ; preds = %if.end8, %if.then5, %if.then
  %9 = load i32, i32* %retval, align 4, !dbg !2680
  ret i32 %9, !dbg !2680
}

; Function Attrs: nounwind uwtable
define i32 @archive_match_include_file_time_w(%struct.archive* %_a, i32 %flag, i32* %pathname) #0 !dbg !262 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %flag.addr = alloca i32, align 4
  %pathname.addr = alloca i32*, align 8
  %r = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !2681, metadata !394), !dbg !2682
  store i32 %flag, i32* %flag.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flag.addr, metadata !2683, metadata !394), !dbg !2684
  store i32* %pathname, i32** %pathname.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %pathname.addr, metadata !2685, metadata !394), !dbg !2686
  call void @llvm.dbg.declare(metadata i32* %r, metadata !2687, metadata !394), !dbg !2688
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !2689
  %1 = load i32, i32* %flag.addr, align 4, !dbg !2690
  %call = call i32 @validate_time_flag(%struct.archive* %0, i32 %1, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.20, i32 0, i32 0)), !dbg !2691
  store i32 %call, i32* %r, align 4, !dbg !2692
  %2 = load i32, i32* %r, align 4, !dbg !2693
  %cmp = icmp ne i32 %2, 0, !dbg !2695
  br i1 %cmp, label %if.then, label %if.end, !dbg !2696

if.then:                                          ; preds = %entry
  %3 = load i32, i32* %r, align 4, !dbg !2697
  store i32 %3, i32* %retval, align 4, !dbg !2698
  br label %return, !dbg !2698

if.end:                                           ; preds = %entry
  %4 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !2699
  %5 = bitcast %struct.archive* %4 to %struct.archive_match*, !dbg !2700
  %6 = load i32, i32* %flag.addr, align 4, !dbg !2701
  %7 = load i32*, i32** %pathname.addr, align 8, !dbg !2702
  %call1 = call i32 @set_timefilter_pathname_wcs(%struct.archive_match* %5, i32 %6, i32* %7), !dbg !2703
  store i32 %call1, i32* %retval, align 4, !dbg !2704
  br label %return, !dbg !2704

return:                                           ; preds = %if.end, %if.then
  %8 = load i32, i32* %retval, align 4, !dbg !2705
  ret i32 %8, !dbg !2705
}

; Function Attrs: nounwind uwtable
define internal i32 @set_timefilter_pathname_wcs(%struct.archive_match* %a, i32 %timetype, i32* %path) #0 !dbg !358 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_match*, align 8
  %timetype.addr = alloca i32, align 4
  %path.addr = alloca i32*, align 8
  %as = alloca %struct.archive_string, align 8
  %r = alloca i32, align 4
  store %struct.archive_match* %a, %struct.archive_match** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a.addr, metadata !2706, metadata !394), !dbg !2707
  store i32 %timetype, i32* %timetype.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %timetype.addr, metadata !2708, metadata !394), !dbg !2709
  store i32* %path, i32** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %path.addr, metadata !2710, metadata !394), !dbg !2711
  call void @llvm.dbg.declare(metadata %struct.archive_string* %as, metadata !2712, metadata !394), !dbg !2713
  call void @llvm.dbg.declare(metadata i32* %r, metadata !2714, metadata !394), !dbg !2715
  %0 = load i32*, i32** %path.addr, align 8, !dbg !2716
  %cmp = icmp eq i32* %0, null, !dbg !2718
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !2719

lor.lhs.false:                                    ; preds = %entry
  %1 = load i32*, i32** %path.addr, align 8, !dbg !2720
  %2 = load i32, i32* %1, align 4, !dbg !2722
  %cmp1 = icmp eq i32 %2, 0, !dbg !2723
  br i1 %cmp1, label %if.then, label %if.end, !dbg !2724

if.then:                                          ; preds = %lor.lhs.false, %entry
  %3 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2725
  %archive = getelementptr inbounds %struct.archive_match, %struct.archive_match* %3, i32 0, i32 0, !dbg !2727
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 22, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.41, i32 0, i32 0)), !dbg !2728
  store i32 -25, i32* %retval, align 4, !dbg !2729
  br label %return, !dbg !2729

if.end:                                           ; preds = %lor.lhs.false
  br label %do.body, !dbg !2730

do.body:                                          ; preds = %if.end
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 0, !dbg !2731
  store i8* null, i8** %s, align 8, !dbg !2731
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 1, !dbg !2731
  store i64 0, i64* %length, align 8, !dbg !2731
  %buffer_length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 2, !dbg !2731
  store i64 0, i64* %buffer_length, align 8, !dbg !2731
  br label %do.end, !dbg !2731

do.end:                                           ; preds = %do.body
  %4 = load i32*, i32** %path.addr, align 8, !dbg !2734
  %5 = load i32*, i32** %path.addr, align 8, !dbg !2736
  %call = call i64 @wcslen(i32* %5) #8, !dbg !2737
  %call2 = call i32 @archive_string_append_from_wcs(%struct.archive_string* %as, i32* %4, i64 %call), !dbg !2738
  %cmp3 = icmp slt i32 %call2, 0, !dbg !2740
  br i1 %cmp3, label %if.then4, label %if.end11, !dbg !2741

if.then4:                                         ; preds = %do.end
  call void @archive_string_free(%struct.archive_string* %as), !dbg !2742
  %call5 = call i32* @__errno_location() #1, !dbg !2744
  %6 = load i32, i32* %call5, align 4, !dbg !2744
  %cmp6 = icmp eq i32 %6, 12, !dbg !2746
  br i1 %cmp6, label %if.then7, label %if.end9, !dbg !2747

if.then7:                                         ; preds = %if.then4
  %7 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2748
  %call8 = call i32 @error_nomem(%struct.archive_match* %7), !dbg !2749
  store i32 %call8, i32* %retval, align 4, !dbg !2750
  br label %return, !dbg !2750

if.end9:                                          ; preds = %if.then4
  %8 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2751
  %archive10 = getelementptr inbounds %struct.archive_match, %struct.archive_match* %8, i32 0, i32 0, !dbg !2752
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive10, i32 -1, i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.40, i32 0, i32 0)), !dbg !2753
  store i32 -25, i32* %retval, align 4, !dbg !2754
  br label %return, !dbg !2754

if.end11:                                         ; preds = %do.end
  %9 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2755
  %10 = load i32, i32* %timetype.addr, align 4, !dbg !2756
  %s12 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 0, !dbg !2757
  %11 = load i8*, i8** %s12, align 8, !dbg !2757
  %call13 = call i32 @set_timefilter_pathname_mbs(%struct.archive_match* %9, i32 %10, i8* %11), !dbg !2758
  store i32 %call13, i32* %r, align 4, !dbg !2759
  call void @archive_string_free(%struct.archive_string* %as), !dbg !2760
  %12 = load i32, i32* %r, align 4, !dbg !2761
  store i32 %12, i32* %retval, align 4, !dbg !2762
  br label %return, !dbg !2762

return:                                           ; preds = %if.end11, %if.end9, %if.then7, %if.then
  %13 = load i32, i32* %retval, align 4, !dbg !2763
  ret i32 %13, !dbg !2763
}

; Function Attrs: nounwind uwtable
define i32 @archive_match_exclude_entry(%struct.archive* %_a, i32 %flag, %struct.archive_entry* %entry1) #0 !dbg !263 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %flag.addr = alloca i32, align 4
  %entry.addr = alloca %struct.archive_entry*, align 8
  %a = alloca %struct.archive_match*, align 8
  %r = alloca i32, align 4
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !2764, metadata !394), !dbg !2765
  store i32 %flag, i32* %flag.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flag.addr, metadata !2766, metadata !394), !dbg !2767
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2768, metadata !394), !dbg !2769
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a, metadata !2770, metadata !394), !dbg !2771
  call void @llvm.dbg.declare(metadata i32* %r, metadata !2772, metadata !394), !dbg !2773
  br label %do.body, !dbg !2774

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !2775, metadata !394), !dbg !2777
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !2778
  %call = call i32 @__archive_check_magic(%struct.archive* %0, i32 212668873, i32 1, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.21, i32 0, i32 0)), !dbg !2778
  store i32 %call, i32* %magic_test, align 4, !dbg !2778
  %1 = load i32, i32* %magic_test, align 4, !dbg !2778
  %cmp = icmp eq i32 %1, -30, !dbg !2778
  br i1 %cmp, label %if.then, label %if.end, !dbg !2778

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !2780
  br label %return, !dbg !2780

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !2783

do.end:                                           ; preds = %if.end
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !2785
  %3 = bitcast %struct.archive* %2 to %struct.archive_match*, !dbg !2786
  store %struct.archive_match* %3, %struct.archive_match** %a, align 8, !dbg !2787
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2788
  %cmp2 = icmp eq %struct.archive_entry* %4, null, !dbg !2790
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !2791

if.then3:                                         ; preds = %do.end
  %5 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !2792
  %archive = getelementptr inbounds %struct.archive_match, %struct.archive_match* %5, i32 0, i32 0, !dbg !2794
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 22, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.2, i32 0, i32 0)), !dbg !2795
  store i32 -25, i32* %retval, align 4, !dbg !2796
  br label %return, !dbg !2796

if.end4:                                          ; preds = %do.end
  %6 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !2797
  %7 = load i32, i32* %flag.addr, align 4, !dbg !2798
  %call5 = call i32 @validate_time_flag(%struct.archive* %6, i32 %7, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.22, i32 0, i32 0)), !dbg !2799
  store i32 %call5, i32* %r, align 4, !dbg !2800
  %8 = load i32, i32* %r, align 4, !dbg !2801
  %cmp6 = icmp ne i32 %8, 0, !dbg !2803
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !2804

if.then7:                                         ; preds = %if.end4
  %9 = load i32, i32* %r, align 4, !dbg !2805
  store i32 %9, i32* %retval, align 4, !dbg !2806
  br label %return, !dbg !2806

if.end8:                                          ; preds = %if.end4
  %10 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !2807
  %11 = load i32, i32* %flag.addr, align 4, !dbg !2808
  %12 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2809
  %call9 = call i32 @add_entry(%struct.archive_match* %10, i32 %11, %struct.archive_entry* %12), !dbg !2810
  store i32 %call9, i32* %retval, align 4, !dbg !2811
  br label %return, !dbg !2811

return:                                           ; preds = %if.end8, %if.then7, %if.then3, %if.then
  %13 = load i32, i32* %retval, align 4, !dbg !2812
  ret i32 %13, !dbg !2812
}

; Function Attrs: nounwind uwtable
define internal i32 @add_entry(%struct.archive_match* %a, i32 %flag, %struct.archive_entry* %entry1) #0 !dbg !364 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_match*, align 8
  %flag.addr = alloca i32, align 4
  %entry.addr = alloca %struct.archive_entry*, align 8
  %f = alloca %struct.match_file*, align 8
  %pathname = alloca i8*, align 8
  %r = alloca i32, align 4
  %f2 = alloca %struct.match_file*, align 8
  store %struct.archive_match* %a, %struct.archive_match** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a.addr, metadata !2813, metadata !394), !dbg !2814
  store i32 %flag, i32* %flag.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flag.addr, metadata !2815, metadata !394), !dbg !2816
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2817, metadata !394), !dbg !2818
  call void @llvm.dbg.declare(metadata %struct.match_file** %f, metadata !2819, metadata !394), !dbg !2820
  call void @llvm.dbg.declare(metadata i8** %pathname, metadata !2821, metadata !394), !dbg !2822
  call void @llvm.dbg.declare(metadata i32* %r, metadata !2823, metadata !394), !dbg !2824
  %call = call noalias i8* @calloc(i64 1, i64 176) #7, !dbg !2825
  %0 = bitcast i8* %call to %struct.match_file*, !dbg !2825
  store %struct.match_file* %0, %struct.match_file** %f, align 8, !dbg !2826
  %1 = load %struct.match_file*, %struct.match_file** %f, align 8, !dbg !2827
  %cmp = icmp eq %struct.match_file* %1, null, !dbg !2829
  br i1 %cmp, label %if.then, label %if.end, !dbg !2830

if.then:                                          ; preds = %entry
  %2 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2831
  %call2 = call i32 @error_nomem(%struct.archive_match* %2), !dbg !2832
  store i32 %call2, i32* %retval, align 4, !dbg !2833
  br label %return, !dbg !2833

if.end:                                           ; preds = %entry
  %3 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2834
  %call3 = call i8* @archive_entry_pathname(%struct.archive_entry* %3), !dbg !2835
  store i8* %call3, i8** %pathname, align 8, !dbg !2836
  %4 = load i8*, i8** %pathname, align 8, !dbg !2837
  %cmp4 = icmp eq i8* %4, null, !dbg !2839
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !2840

if.then5:                                         ; preds = %if.end
  %5 = load %struct.match_file*, %struct.match_file** %f, align 8, !dbg !2841
  %6 = bitcast %struct.match_file* %5 to i8*, !dbg !2841
  call void @free(i8* %6) #7, !dbg !2843
  %7 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2844
  %archive = getelementptr inbounds %struct.archive_match, %struct.archive_match* %7, i32 0, i32 0, !dbg !2845
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 22, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.43, i32 0, i32 0)), !dbg !2846
  store i32 -25, i32* %retval, align 4, !dbg !2847
  br label %return, !dbg !2847

if.end6:                                          ; preds = %if.end
  %8 = load %struct.match_file*, %struct.match_file** %f, align 8, !dbg !2848
  %pathname7 = getelementptr inbounds %struct.match_file, %struct.match_file* %8, i32 0, i32 2, !dbg !2849
  %9 = load i8*, i8** %pathname, align 8, !dbg !2850
  %call8 = call i32 @archive_mstring_copy_mbs(%struct.archive_mstring* %pathname7, i8* %9), !dbg !2851
  %10 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2852
  %exclusion_tree = getelementptr inbounds %struct.archive_match, %struct.archive_match* %10, i32 0, i32 17, !dbg !2853
  %rbt_ops = getelementptr inbounds %struct.archive_rb_tree, %struct.archive_rb_tree* %exclusion_tree, i32 0, i32 1, !dbg !2854
  store %struct.archive_rb_tree_ops* @rb_ops_mbs, %struct.archive_rb_tree_ops** %rbt_ops, align 8, !dbg !2855
  %11 = load i32, i32* %flag.addr, align 4, !dbg !2856
  %12 = load %struct.match_file*, %struct.match_file** %f, align 8, !dbg !2857
  %flag9 = getelementptr inbounds %struct.match_file, %struct.match_file* %12, i32 0, i32 3, !dbg !2858
  store i32 %11, i32* %flag9, align 8, !dbg !2859
  %13 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2860
  %call10 = call i64 @archive_entry_mtime(%struct.archive_entry* %13), !dbg !2861
  %14 = load %struct.match_file*, %struct.match_file** %f, align 8, !dbg !2862
  %mtime_sec = getelementptr inbounds %struct.match_file, %struct.match_file* %14, i32 0, i32 4, !dbg !2863
  store i64 %call10, i64* %mtime_sec, align 8, !dbg !2864
  %15 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2865
  %call11 = call i64 @archive_entry_mtime_nsec(%struct.archive_entry* %15), !dbg !2866
  %16 = load %struct.match_file*, %struct.match_file** %f, align 8, !dbg !2867
  %mtime_nsec = getelementptr inbounds %struct.match_file, %struct.match_file* %16, i32 0, i32 5, !dbg !2868
  store i64 %call11, i64* %mtime_nsec, align 8, !dbg !2869
  %17 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2870
  %call12 = call i64 @archive_entry_ctime(%struct.archive_entry* %17), !dbg !2871
  %18 = load %struct.match_file*, %struct.match_file** %f, align 8, !dbg !2872
  %ctime_sec = getelementptr inbounds %struct.match_file, %struct.match_file* %18, i32 0, i32 6, !dbg !2873
  store i64 %call12, i64* %ctime_sec, align 8, !dbg !2874
  %19 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2875
  %call13 = call i64 @archive_entry_ctime_nsec(%struct.archive_entry* %19), !dbg !2876
  %20 = load %struct.match_file*, %struct.match_file** %f, align 8, !dbg !2877
  %ctime_nsec = getelementptr inbounds %struct.match_file, %struct.match_file* %20, i32 0, i32 7, !dbg !2878
  store i64 %call13, i64* %ctime_nsec, align 8, !dbg !2879
  %21 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2880
  %exclusion_tree14 = getelementptr inbounds %struct.archive_match, %struct.archive_match* %21, i32 0, i32 17, !dbg !2881
  %22 = load %struct.match_file*, %struct.match_file** %f, align 8, !dbg !2882
  %node = getelementptr inbounds %struct.match_file, %struct.match_file* %22, i32 0, i32 0, !dbg !2883
  %call15 = call i32 @__archive_rb_tree_insert_node(%struct.archive_rb_tree* %exclusion_tree14, %struct.archive_rb_node* %node), !dbg !2884
  store i32 %call15, i32* %r, align 4, !dbg !2885
  %23 = load i32, i32* %r, align 4, !dbg !2886
  %tobool = icmp ne i32 %23, 0, !dbg !2886
  br i1 %tobool, label %if.end33, label %if.then16, !dbg !2888

if.then16:                                        ; preds = %if.end6
  call void @llvm.dbg.declare(metadata %struct.match_file** %f2, metadata !2889, metadata !394), !dbg !2891
  %24 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2892
  %exclusion_tree17 = getelementptr inbounds %struct.archive_match, %struct.archive_match* %24, i32 0, i32 17, !dbg !2893
  %25 = load i8*, i8** %pathname, align 8, !dbg !2894
  %call18 = call %struct.archive_rb_node* @__archive_rb_tree_find_node(%struct.archive_rb_tree* %exclusion_tree17, i8* %25), !dbg !2895
  %26 = bitcast %struct.archive_rb_node* %call18 to %struct.match_file*, !dbg !2896
  store %struct.match_file* %26, %struct.match_file** %f2, align 8, !dbg !2897
  %27 = load %struct.match_file*, %struct.match_file** %f2, align 8, !dbg !2898
  %cmp19 = icmp ne %struct.match_file* %27, null, !dbg !2900
  br i1 %cmp19, label %if.then20, label %if.end31, !dbg !2901

if.then20:                                        ; preds = %if.then16
  %28 = load %struct.match_file*, %struct.match_file** %f, align 8, !dbg !2902
  %flag21 = getelementptr inbounds %struct.match_file, %struct.match_file* %28, i32 0, i32 3, !dbg !2904
  %29 = load i32, i32* %flag21, align 8, !dbg !2904
  %30 = load %struct.match_file*, %struct.match_file** %f2, align 8, !dbg !2905
  %flag22 = getelementptr inbounds %struct.match_file, %struct.match_file* %30, i32 0, i32 3, !dbg !2906
  store i32 %29, i32* %flag22, align 8, !dbg !2907
  %31 = load %struct.match_file*, %struct.match_file** %f, align 8, !dbg !2908
  %mtime_sec23 = getelementptr inbounds %struct.match_file, %struct.match_file* %31, i32 0, i32 4, !dbg !2909
  %32 = load i64, i64* %mtime_sec23, align 8, !dbg !2909
  %33 = load %struct.match_file*, %struct.match_file** %f2, align 8, !dbg !2910
  %mtime_sec24 = getelementptr inbounds %struct.match_file, %struct.match_file* %33, i32 0, i32 4, !dbg !2911
  store i64 %32, i64* %mtime_sec24, align 8, !dbg !2912
  %34 = load %struct.match_file*, %struct.match_file** %f, align 8, !dbg !2913
  %mtime_nsec25 = getelementptr inbounds %struct.match_file, %struct.match_file* %34, i32 0, i32 5, !dbg !2914
  %35 = load i64, i64* %mtime_nsec25, align 8, !dbg !2914
  %36 = load %struct.match_file*, %struct.match_file** %f2, align 8, !dbg !2915
  %mtime_nsec26 = getelementptr inbounds %struct.match_file, %struct.match_file* %36, i32 0, i32 5, !dbg !2916
  store i64 %35, i64* %mtime_nsec26, align 8, !dbg !2917
  %37 = load %struct.match_file*, %struct.match_file** %f, align 8, !dbg !2918
  %ctime_sec27 = getelementptr inbounds %struct.match_file, %struct.match_file* %37, i32 0, i32 6, !dbg !2919
  %38 = load i64, i64* %ctime_sec27, align 8, !dbg !2919
  %39 = load %struct.match_file*, %struct.match_file** %f2, align 8, !dbg !2920
  %ctime_sec28 = getelementptr inbounds %struct.match_file, %struct.match_file* %39, i32 0, i32 6, !dbg !2921
  store i64 %38, i64* %ctime_sec28, align 8, !dbg !2922
  %40 = load %struct.match_file*, %struct.match_file** %f, align 8, !dbg !2923
  %ctime_nsec29 = getelementptr inbounds %struct.match_file, %struct.match_file* %40, i32 0, i32 7, !dbg !2924
  %41 = load i64, i64* %ctime_nsec29, align 8, !dbg !2924
  %42 = load %struct.match_file*, %struct.match_file** %f2, align 8, !dbg !2925
  %ctime_nsec30 = getelementptr inbounds %struct.match_file, %struct.match_file* %42, i32 0, i32 7, !dbg !2926
  store i64 %41, i64* %ctime_nsec30, align 8, !dbg !2927
  br label %if.end31, !dbg !2928

if.end31:                                         ; preds = %if.then20, %if.then16
  %43 = load %struct.match_file*, %struct.match_file** %f, align 8, !dbg !2929
  %pathname32 = getelementptr inbounds %struct.match_file, %struct.match_file* %43, i32 0, i32 2, !dbg !2930
  call void @archive_mstring_clean(%struct.archive_mstring* %pathname32), !dbg !2931
  %44 = load %struct.match_file*, %struct.match_file** %f, align 8, !dbg !2932
  %45 = bitcast %struct.match_file* %44 to i8*, !dbg !2932
  call void @free(i8* %45) #7, !dbg !2933
  store i32 0, i32* %retval, align 4, !dbg !2934
  br label %return, !dbg !2934

if.end33:                                         ; preds = %if.end6
  %46 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2935
  %exclusion_entry_list = getelementptr inbounds %struct.archive_match, %struct.archive_match* %46, i32 0, i32 18, !dbg !2936
  %47 = load %struct.match_file*, %struct.match_file** %f, align 8, !dbg !2937
  call void @entry_list_add(%struct.entry_list* %exclusion_entry_list, %struct.match_file* %47), !dbg !2938
  %48 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !2939
  %setflag = getelementptr inbounds %struct.archive_match, %struct.archive_match* %48, i32 0, i32 1, !dbg !2940
  %49 = load i32, i32* %setflag, align 8, !dbg !2941
  %or = or i32 %49, 2, !dbg !2941
  store i32 %or, i32* %setflag, align 8, !dbg !2941
  store i32 0, i32* %retval, align 4, !dbg !2942
  br label %return, !dbg !2942

return:                                           ; preds = %if.end33, %if.end31, %if.then5, %if.then
  %50 = load i32, i32* %retval, align 4, !dbg !2943
  ret i32 %50, !dbg !2943
}

; Function Attrs: nounwind uwtable
define i32 @archive_match_time_excluded(%struct.archive* %_a, %struct.archive_entry* %entry1) #0 !dbg !266 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %a = alloca %struct.archive_match*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !2944, metadata !394), !dbg !2945
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2946, metadata !394), !dbg !2947
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a, metadata !2948, metadata !394), !dbg !2949
  br label %do.body, !dbg !2950

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !2951, metadata !394), !dbg !2953
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !2954
  %call = call i32 @__archive_check_magic(%struct.archive* %0, i32 212668873, i32 1, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.23, i32 0, i32 0)), !dbg !2954
  store i32 %call, i32* %magic_test, align 4, !dbg !2954
  %1 = load i32, i32* %magic_test, align 4, !dbg !2954
  %cmp = icmp eq i32 %1, -30, !dbg !2954
  br i1 %cmp, label %if.then, label %if.end, !dbg !2954

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !2956
  br label %return, !dbg !2956

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !2959

do.end:                                           ; preds = %if.end
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !2961
  %3 = bitcast %struct.archive* %2 to %struct.archive_match*, !dbg !2962
  store %struct.archive_match* %3, %struct.archive_match** %a, align 8, !dbg !2963
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2964
  %cmp2 = icmp eq %struct.archive_entry* %4, null, !dbg !2966
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !2967

if.then3:                                         ; preds = %do.end
  %5 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !2968
  %archive = getelementptr inbounds %struct.archive_match, %struct.archive_match* %5, i32 0, i32 0, !dbg !2970
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 22, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.2, i32 0, i32 0)), !dbg !2971
  store i32 -25, i32* %retval, align 4, !dbg !2972
  br label %return, !dbg !2972

if.end4:                                          ; preds = %do.end
  %6 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !2973
  %setflag = getelementptr inbounds %struct.archive_match, %struct.archive_match* %6, i32 0, i32 1, !dbg !2975
  %7 = load i32, i32* %setflag, align 8, !dbg !2975
  %and = and i32 %7, 2, !dbg !2976
  %cmp5 = icmp eq i32 %and, 0, !dbg !2977
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !2978

if.then6:                                         ; preds = %if.end4
  store i32 0, i32* %retval, align 4, !dbg !2979
  br label %return, !dbg !2979

if.end7:                                          ; preds = %if.end4
  %8 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !2980
  %9 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2981
  %call8 = call i32 @time_excluded(%struct.archive_match* %8, %struct.archive_entry* %9), !dbg !2982
  store i32 %call8, i32* %retval, align 4, !dbg !2983
  br label %return, !dbg !2983

return:                                           ; preds = %if.end7, %if.then6, %if.then3, %if.then
  %10 = load i32, i32* %retval, align 4, !dbg !2984
  ret i32 %10, !dbg !2984
}

; Function Attrs: nounwind uwtable
define i32 @archive_match_include_uid(%struct.archive* %_a, i64 %uid) #0 !dbg !267 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %uid.addr = alloca i64, align 8
  %a = alloca %struct.archive_match*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !2985, metadata !394), !dbg !2986
  store i64 %uid, i64* %uid.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %uid.addr, metadata !2987, metadata !394), !dbg !2988
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a, metadata !2989, metadata !394), !dbg !2990
  br label %do.body, !dbg !2991

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !2992, metadata !394), !dbg !2994
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !2995
  %call = call i32 @__archive_check_magic(%struct.archive* %0, i32 212668873, i32 1, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.24, i32 0, i32 0)), !dbg !2995
  store i32 %call, i32* %magic_test, align 4, !dbg !2995
  %1 = load i32, i32* %magic_test, align 4, !dbg !2995
  %cmp = icmp eq i32 %1, -30, !dbg !2995
  br i1 %cmp, label %if.then, label %if.end, !dbg !2995

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !2997
  br label %return, !dbg !2997

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !3000

do.end:                                           ; preds = %if.end
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !3002
  %3 = bitcast %struct.archive* %2 to %struct.archive_match*, !dbg !3003
  store %struct.archive_match* %3, %struct.archive_match** %a, align 8, !dbg !3004
  %4 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !3005
  %5 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !3006
  %inclusion_uids = getelementptr inbounds %struct.archive_match, %struct.archive_match* %5, i32 0, i32 19, !dbg !3007
  %6 = load i64, i64* %uid.addr, align 8, !dbg !3008
  %call1 = call i32 @add_owner_id(%struct.archive_match* %4, %struct.id_array* %inclusion_uids, i64 %6), !dbg !3009
  store i32 %call1, i32* %retval, align 4, !dbg !3010
  br label %return, !dbg !3010

return:                                           ; preds = %do.end, %if.then
  %7 = load i32, i32* %retval, align 4, !dbg !3011
  ret i32 %7, !dbg !3011
}

; Function Attrs: nounwind uwtable
define internal i32 @add_owner_id(%struct.archive_match* %a, %struct.id_array* %ids, i64 %id) #0 !dbg !375 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_match*, align 8
  %ids.addr = alloca %struct.id_array*, align 8
  %id.addr = alloca i64, align 8
  %i = alloca i32, align 4
  %p = alloca i8*, align 8
  store %struct.archive_match* %a, %struct.archive_match** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a.addr, metadata !3012, metadata !394), !dbg !3013
  store %struct.id_array* %ids, %struct.id_array** %ids.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.id_array** %ids.addr, metadata !3014, metadata !394), !dbg !3015
  store i64 %id, i64* %id.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %id.addr, metadata !3016, metadata !394), !dbg !3017
  call void @llvm.dbg.declare(metadata i32* %i, metadata !3018, metadata !394), !dbg !3019
  %0 = load %struct.id_array*, %struct.id_array** %ids.addr, align 8, !dbg !3020
  %count = getelementptr inbounds %struct.id_array, %struct.id_array* %0, i32 0, i32 1, !dbg !3022
  %1 = load i64, i64* %count, align 8, !dbg !3022
  %add = add i64 %1, 1, !dbg !3023
  %2 = load %struct.id_array*, %struct.id_array** %ids.addr, align 8, !dbg !3024
  %size = getelementptr inbounds %struct.id_array, %struct.id_array* %2, i32 0, i32 0, !dbg !3025
  %3 = load i64, i64* %size, align 8, !dbg !3025
  %cmp = icmp uge i64 %add, %3, !dbg !3026
  br i1 %cmp, label %if.then, label %if.end14, !dbg !3027

if.then:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i8** %p, metadata !3028, metadata !394), !dbg !3030
  %4 = load %struct.id_array*, %struct.id_array** %ids.addr, align 8, !dbg !3031
  %size1 = getelementptr inbounds %struct.id_array, %struct.id_array* %4, i32 0, i32 0, !dbg !3033
  %5 = load i64, i64* %size1, align 8, !dbg !3033
  %cmp2 = icmp eq i64 %5, 0, !dbg !3034
  br i1 %cmp2, label %if.then3, label %if.else, !dbg !3035

if.then3:                                         ; preds = %if.then
  %6 = load %struct.id_array*, %struct.id_array** %ids.addr, align 8, !dbg !3036
  %size4 = getelementptr inbounds %struct.id_array, %struct.id_array* %6, i32 0, i32 0, !dbg !3037
  store i64 8, i64* %size4, align 8, !dbg !3038
  br label %if.end, !dbg !3036

if.else:                                          ; preds = %if.then
  %7 = load %struct.id_array*, %struct.id_array** %ids.addr, align 8, !dbg !3039
  %size5 = getelementptr inbounds %struct.id_array, %struct.id_array* %7, i32 0, i32 0, !dbg !3040
  %8 = load i64, i64* %size5, align 8, !dbg !3041
  %mul = mul i64 %8, 2, !dbg !3041
  store i64 %mul, i64* %size5, align 8, !dbg !3041
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then3
  %9 = load %struct.id_array*, %struct.id_array** %ids.addr, align 8, !dbg !3042
  %ids6 = getelementptr inbounds %struct.id_array, %struct.id_array* %9, i32 0, i32 2, !dbg !3043
  %10 = load i64*, i64** %ids6, align 8, !dbg !3043
  %11 = bitcast i64* %10 to i8*, !dbg !3042
  %12 = load %struct.id_array*, %struct.id_array** %ids.addr, align 8, !dbg !3044
  %size7 = getelementptr inbounds %struct.id_array, %struct.id_array* %12, i32 0, i32 0, !dbg !3045
  %13 = load i64, i64* %size7, align 8, !dbg !3045
  %mul8 = mul i64 8, %13, !dbg !3046
  %call = call i8* @realloc(i8* %11, i64 %mul8) #7, !dbg !3047
  store i8* %call, i8** %p, align 8, !dbg !3048
  %14 = load i8*, i8** %p, align 8, !dbg !3049
  %cmp9 = icmp eq i8* %14, null, !dbg !3051
  br i1 %cmp9, label %if.then10, label %if.end12, !dbg !3052

if.then10:                                        ; preds = %if.end
  %15 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !3053
  %call11 = call i32 @error_nomem(%struct.archive_match* %15), !dbg !3054
  store i32 %call11, i32* %retval, align 4, !dbg !3055
  br label %return, !dbg !3055

if.end12:                                         ; preds = %if.end
  %16 = load i8*, i8** %p, align 8, !dbg !3056
  %17 = bitcast i8* %16 to i64*, !dbg !3057
  %18 = load %struct.id_array*, %struct.id_array** %ids.addr, align 8, !dbg !3058
  %ids13 = getelementptr inbounds %struct.id_array, %struct.id_array* %18, i32 0, i32 2, !dbg !3059
  store i64* %17, i64** %ids13, align 8, !dbg !3060
  br label %if.end14, !dbg !3061

if.end14:                                         ; preds = %if.end12, %entry
  store i32 0, i32* %i, align 4, !dbg !3062
  br label %for.cond, !dbg !3064

for.cond:                                         ; preds = %for.inc, %if.end14
  %19 = load i32, i32* %i, align 4, !dbg !3065
  %conv = zext i32 %19 to i64, !dbg !3065
  %20 = load %struct.id_array*, %struct.id_array** %ids.addr, align 8, !dbg !3068
  %count15 = getelementptr inbounds %struct.id_array, %struct.id_array* %20, i32 0, i32 1, !dbg !3069
  %21 = load i64, i64* %count15, align 8, !dbg !3069
  %cmp16 = icmp ult i64 %conv, %21, !dbg !3070
  br i1 %cmp16, label %for.body, label %for.end, !dbg !3071

for.body:                                         ; preds = %for.cond
  %22 = load i32, i32* %i, align 4, !dbg !3072
  %idxprom = zext i32 %22 to i64, !dbg !3075
  %23 = load %struct.id_array*, %struct.id_array** %ids.addr, align 8, !dbg !3075
  %ids18 = getelementptr inbounds %struct.id_array, %struct.id_array* %23, i32 0, i32 2, !dbg !3076
  %24 = load i64*, i64** %ids18, align 8, !dbg !3076
  %arrayidx = getelementptr inbounds i64, i64* %24, i64 %idxprom, !dbg !3075
  %25 = load i64, i64* %arrayidx, align 8, !dbg !3075
  %26 = load i64, i64* %id.addr, align 8, !dbg !3077
  %cmp19 = icmp sge i64 %25, %26, !dbg !3078
  br i1 %cmp19, label %if.then21, label %if.end22, !dbg !3079

if.then21:                                        ; preds = %for.body
  br label %for.end, !dbg !3080

if.end22:                                         ; preds = %for.body
  br label %for.inc, !dbg !3081

for.inc:                                          ; preds = %if.end22
  %27 = load i32, i32* %i, align 4, !dbg !3082
  %inc = add i32 %27, 1, !dbg !3082
  store i32 %inc, i32* %i, align 4, !dbg !3082
  br label %for.cond, !dbg !3084

for.end:                                          ; preds = %if.then21, %for.cond
  %28 = load i32, i32* %i, align 4, !dbg !3085
  %conv23 = zext i32 %28 to i64, !dbg !3085
  %29 = load %struct.id_array*, %struct.id_array** %ids.addr, align 8, !dbg !3087
  %count24 = getelementptr inbounds %struct.id_array, %struct.id_array* %29, i32 0, i32 1, !dbg !3088
  %30 = load i64, i64* %count24, align 8, !dbg !3088
  %cmp25 = icmp eq i64 %conv23, %30, !dbg !3089
  br i1 %cmp25, label %if.then27, label %if.else32, !dbg !3090

if.then27:                                        ; preds = %for.end
  %31 = load i64, i64* %id.addr, align 8, !dbg !3091
  %32 = load %struct.id_array*, %struct.id_array** %ids.addr, align 8, !dbg !3092
  %count28 = getelementptr inbounds %struct.id_array, %struct.id_array* %32, i32 0, i32 1, !dbg !3093
  %33 = load i64, i64* %count28, align 8, !dbg !3094
  %inc29 = add i64 %33, 1, !dbg !3094
  store i64 %inc29, i64* %count28, align 8, !dbg !3094
  %34 = load %struct.id_array*, %struct.id_array** %ids.addr, align 8, !dbg !3095
  %ids30 = getelementptr inbounds %struct.id_array, %struct.id_array* %34, i32 0, i32 2, !dbg !3096
  %35 = load i64*, i64** %ids30, align 8, !dbg !3096
  %arrayidx31 = getelementptr inbounds i64, i64* %35, i64 %33, !dbg !3095
  store i64 %31, i64* %arrayidx31, align 8, !dbg !3097
  br label %if.end55, !dbg !3095

if.else32:                                        ; preds = %for.end
  %36 = load i32, i32* %i, align 4, !dbg !3098
  %idxprom33 = zext i32 %36 to i64, !dbg !3100
  %37 = load %struct.id_array*, %struct.id_array** %ids.addr, align 8, !dbg !3100
  %ids34 = getelementptr inbounds %struct.id_array, %struct.id_array* %37, i32 0, i32 2, !dbg !3101
  %38 = load i64*, i64** %ids34, align 8, !dbg !3101
  %arrayidx35 = getelementptr inbounds i64, i64* %38, i64 %idxprom33, !dbg !3100
  %39 = load i64, i64* %arrayidx35, align 8, !dbg !3100
  %40 = load i64, i64* %id.addr, align 8, !dbg !3102
  %cmp36 = icmp ne i64 %39, %40, !dbg !3103
  br i1 %cmp36, label %if.then38, label %if.end54, !dbg !3104

if.then38:                                        ; preds = %if.else32
  %41 = load i32, i32* %i, align 4, !dbg !3105
  %add39 = add i32 %41, 1, !dbg !3107
  %idxprom40 = zext i32 %add39 to i64, !dbg !3108
  %42 = load %struct.id_array*, %struct.id_array** %ids.addr, align 8, !dbg !3108
  %ids41 = getelementptr inbounds %struct.id_array, %struct.id_array* %42, i32 0, i32 2, !dbg !3109
  %43 = load i64*, i64** %ids41, align 8, !dbg !3109
  %arrayidx42 = getelementptr inbounds i64, i64* %43, i64 %idxprom40, !dbg !3108
  %44 = bitcast i64* %arrayidx42 to i8*, !dbg !3110
  %45 = load i32, i32* %i, align 4, !dbg !3111
  %idxprom43 = zext i32 %45 to i64, !dbg !3112
  %46 = load %struct.id_array*, %struct.id_array** %ids.addr, align 8, !dbg !3112
  %ids44 = getelementptr inbounds %struct.id_array, %struct.id_array* %46, i32 0, i32 2, !dbg !3113
  %47 = load i64*, i64** %ids44, align 8, !dbg !3113
  %arrayidx45 = getelementptr inbounds i64, i64* %47, i64 %idxprom43, !dbg !3112
  %48 = bitcast i64* %arrayidx45 to i8*, !dbg !3110
  %49 = load %struct.id_array*, %struct.id_array** %ids.addr, align 8, !dbg !3114
  %count46 = getelementptr inbounds %struct.id_array, %struct.id_array* %49, i32 0, i32 1, !dbg !3115
  %50 = load i64, i64* %count46, align 8, !dbg !3115
  %51 = load i32, i32* %i, align 4, !dbg !3116
  %conv47 = zext i32 %51 to i64, !dbg !3116
  %sub = sub i64 %50, %conv47, !dbg !3117
  %mul48 = mul i64 %sub, 8, !dbg !3118
  call void @llvm.memmove.p0i8.p0i8.i64(i8* %44, i8* %48, i64 %mul48, i32 8, i1 false), !dbg !3110
  %52 = load i64, i64* %id.addr, align 8, !dbg !3119
  %53 = load i32, i32* %i, align 4, !dbg !3120
  %idxprom49 = zext i32 %53 to i64, !dbg !3121
  %54 = load %struct.id_array*, %struct.id_array** %ids.addr, align 8, !dbg !3121
  %ids50 = getelementptr inbounds %struct.id_array, %struct.id_array* %54, i32 0, i32 2, !dbg !3122
  %55 = load i64*, i64** %ids50, align 8, !dbg !3122
  %arrayidx51 = getelementptr inbounds i64, i64* %55, i64 %idxprom49, !dbg !3121
  store i64 %52, i64* %arrayidx51, align 8, !dbg !3123
  %56 = load %struct.id_array*, %struct.id_array** %ids.addr, align 8, !dbg !3124
  %count52 = getelementptr inbounds %struct.id_array, %struct.id_array* %56, i32 0, i32 1, !dbg !3125
  %57 = load i64, i64* %count52, align 8, !dbg !3126
  %inc53 = add i64 %57, 1, !dbg !3126
  store i64 %inc53, i64* %count52, align 8, !dbg !3126
  br label %if.end54, !dbg !3127

if.end54:                                         ; preds = %if.then38, %if.else32
  br label %if.end55

if.end55:                                         ; preds = %if.end54, %if.then27
  %58 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !3128
  %setflag = getelementptr inbounds %struct.archive_match, %struct.archive_match* %58, i32 0, i32 1, !dbg !3129
  %59 = load i32, i32* %setflag, align 8, !dbg !3130
  %or = or i32 %59, 4, !dbg !3130
  store i32 %or, i32* %setflag, align 8, !dbg !3130
  store i32 0, i32* %retval, align 4, !dbg !3131
  br label %return, !dbg !3131

return:                                           ; preds = %if.end55, %if.then10
  %60 = load i32, i32* %retval, align 4, !dbg !3132
  ret i32 %60, !dbg !3132
}

; Function Attrs: nounwind uwtable
define i32 @archive_match_include_gid(%struct.archive* %_a, i64 %gid) #0 !dbg !270 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %gid.addr = alloca i64, align 8
  %a = alloca %struct.archive_match*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !3133, metadata !394), !dbg !3134
  store i64 %gid, i64* %gid.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %gid.addr, metadata !3135, metadata !394), !dbg !3136
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a, metadata !3137, metadata !394), !dbg !3138
  br label %do.body, !dbg !3139

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !3140, metadata !394), !dbg !3142
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !3143
  %call = call i32 @__archive_check_magic(%struct.archive* %0, i32 212668873, i32 1, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.25, i32 0, i32 0)), !dbg !3143
  store i32 %call, i32* %magic_test, align 4, !dbg !3143
  %1 = load i32, i32* %magic_test, align 4, !dbg !3143
  %cmp = icmp eq i32 %1, -30, !dbg !3143
  br i1 %cmp, label %if.then, label %if.end, !dbg !3143

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !3145
  br label %return, !dbg !3145

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !3148

do.end:                                           ; preds = %if.end
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !3150
  %3 = bitcast %struct.archive* %2 to %struct.archive_match*, !dbg !3151
  store %struct.archive_match* %3, %struct.archive_match** %a, align 8, !dbg !3152
  %4 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !3153
  %5 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !3154
  %inclusion_gids = getelementptr inbounds %struct.archive_match, %struct.archive_match* %5, i32 0, i32 20, !dbg !3155
  %6 = load i64, i64* %gid.addr, align 8, !dbg !3156
  %call1 = call i32 @add_owner_id(%struct.archive_match* %4, %struct.id_array* %inclusion_gids, i64 %6), !dbg !3157
  store i32 %call1, i32* %retval, align 4, !dbg !3158
  br label %return, !dbg !3158

return:                                           ; preds = %do.end, %if.then
  %7 = load i32, i32* %retval, align 4, !dbg !3159
  ret i32 %7, !dbg !3159
}

; Function Attrs: nounwind uwtable
define i32 @archive_match_include_uname(%struct.archive* %_a, i8* %uname) #0 !dbg !271 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %uname.addr = alloca i8*, align 8
  %a = alloca %struct.archive_match*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !3160, metadata !394), !dbg !3161
  store i8* %uname, i8** %uname.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %uname.addr, metadata !3162, metadata !394), !dbg !3163
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a, metadata !3164, metadata !394), !dbg !3165
  br label %do.body, !dbg !3166

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !3167, metadata !394), !dbg !3169
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !3170
  %call = call i32 @__archive_check_magic(%struct.archive* %0, i32 212668873, i32 1, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.26, i32 0, i32 0)), !dbg !3170
  store i32 %call, i32* %magic_test, align 4, !dbg !3170
  %1 = load i32, i32* %magic_test, align 4, !dbg !3170
  %cmp = icmp eq i32 %1, -30, !dbg !3170
  br i1 %cmp, label %if.then, label %if.end, !dbg !3170

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !3172
  br label %return, !dbg !3172

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !3175

do.end:                                           ; preds = %if.end
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !3177
  %3 = bitcast %struct.archive* %2 to %struct.archive_match*, !dbg !3178
  store %struct.archive_match* %3, %struct.archive_match** %a, align 8, !dbg !3179
  %4 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !3180
  %5 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !3181
  %inclusion_unames = getelementptr inbounds %struct.archive_match, %struct.archive_match* %5, i32 0, i32 21, !dbg !3182
  %6 = load i8*, i8** %uname.addr, align 8, !dbg !3183
  %call1 = call i32 @add_owner_name(%struct.archive_match* %4, %struct.match_list* %inclusion_unames, i32 1, i8* %6), !dbg !3184
  store i32 %call1, i32* %retval, align 4, !dbg !3185
  br label %return, !dbg !3185

return:                                           ; preds = %do.end, %if.then
  %7 = load i32, i32* %retval, align 4, !dbg !3186
  ret i32 %7, !dbg !3186
}

; Function Attrs: nounwind uwtable
define internal i32 @add_owner_name(%struct.archive_match* %a, %struct.match_list* %list, i32 %mbs, i8* %name) #0 !dbg !379 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_match*, align 8
  %list.addr = alloca %struct.match_list*, align 8
  %mbs.addr = alloca i32, align 4
  %name.addr = alloca i8*, align 8
  %match = alloca %struct.match*, align 8
  store %struct.archive_match* %a, %struct.archive_match** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a.addr, metadata !3187, metadata !394), !dbg !3188
  store %struct.match_list* %list, %struct.match_list** %list.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.match_list** %list.addr, metadata !3189, metadata !394), !dbg !3190
  store i32 %mbs, i32* %mbs.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %mbs.addr, metadata !3191, metadata !394), !dbg !3192
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !3193, metadata !394), !dbg !3194
  call void @llvm.dbg.declare(metadata %struct.match** %match, metadata !3195, metadata !394), !dbg !3196
  %call = call noalias i8* @calloc(i64 1, i64 120) #7, !dbg !3197
  %0 = bitcast i8* %call to %struct.match*, !dbg !3197
  store %struct.match* %0, %struct.match** %match, align 8, !dbg !3198
  %1 = load %struct.match*, %struct.match** %match, align 8, !dbg !3199
  %cmp = icmp eq %struct.match* %1, null, !dbg !3201
  br i1 %cmp, label %if.then, label %if.end, !dbg !3202

if.then:                                          ; preds = %entry
  %2 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !3203
  %call1 = call i32 @error_nomem(%struct.archive_match* %2), !dbg !3204
  store i32 %call1, i32* %retval, align 4, !dbg !3205
  br label %return, !dbg !3205

if.end:                                           ; preds = %entry
  %3 = load i32, i32* %mbs.addr, align 4, !dbg !3206
  %tobool = icmp ne i32 %3, 0, !dbg !3206
  br i1 %tobool, label %if.then2, label %if.else, !dbg !3208

if.then2:                                         ; preds = %if.end
  %4 = load %struct.match*, %struct.match** %match, align 8, !dbg !3209
  %pattern = getelementptr inbounds %struct.match, %struct.match* %4, i32 0, i32 2, !dbg !3210
  %5 = load i8*, i8** %name.addr, align 8, !dbg !3211
  %call3 = call i32 @archive_mstring_copy_mbs(%struct.archive_mstring* %pattern, i8* %5), !dbg !3212
  br label %if.end6, !dbg !3212

if.else:                                          ; preds = %if.end
  %6 = load %struct.match*, %struct.match** %match, align 8, !dbg !3213
  %pattern4 = getelementptr inbounds %struct.match, %struct.match* %6, i32 0, i32 2, !dbg !3214
  %7 = load i8*, i8** %name.addr, align 8, !dbg !3215
  %8 = bitcast i8* %7 to i32*, !dbg !3215
  %call5 = call i32 @archive_mstring_copy_wcs(%struct.archive_mstring* %pattern4, i32* %8), !dbg !3216
  br label %if.end6

if.end6:                                          ; preds = %if.else, %if.then2
  %9 = load %struct.match_list*, %struct.match_list** %list.addr, align 8, !dbg !3217
  %10 = load %struct.match*, %struct.match** %match, align 8, !dbg !3218
  call void @match_list_add(%struct.match_list* %9, %struct.match* %10), !dbg !3219
  %11 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !3220
  %setflag = getelementptr inbounds %struct.archive_match, %struct.archive_match* %11, i32 0, i32 1, !dbg !3221
  %12 = load i32, i32* %setflag, align 8, !dbg !3222
  %or = or i32 %12, 4, !dbg !3222
  store i32 %or, i32* %setflag, align 8, !dbg !3222
  store i32 0, i32* %retval, align 4, !dbg !3223
  br label %return, !dbg !3223

return:                                           ; preds = %if.end6, %if.then
  %13 = load i32, i32* %retval, align 4, !dbg !3224
  ret i32 %13, !dbg !3224
}

; Function Attrs: nounwind uwtable
define i32 @archive_match_include_uname_w(%struct.archive* %_a, i32* %uname) #0 !dbg !272 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %uname.addr = alloca i32*, align 8
  %a = alloca %struct.archive_match*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !3225, metadata !394), !dbg !3226
  store i32* %uname, i32** %uname.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %uname.addr, metadata !3227, metadata !394), !dbg !3228
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a, metadata !3229, metadata !394), !dbg !3230
  br label %do.body, !dbg !3231

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !3232, metadata !394), !dbg !3234
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !3235
  %call = call i32 @__archive_check_magic(%struct.archive* %0, i32 212668873, i32 1, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.27, i32 0, i32 0)), !dbg !3235
  store i32 %call, i32* %magic_test, align 4, !dbg !3235
  %1 = load i32, i32* %magic_test, align 4, !dbg !3235
  %cmp = icmp eq i32 %1, -30, !dbg !3235
  br i1 %cmp, label %if.then, label %if.end, !dbg !3235

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !3237
  br label %return, !dbg !3237

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !3240

do.end:                                           ; preds = %if.end
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !3242
  %3 = bitcast %struct.archive* %2 to %struct.archive_match*, !dbg !3243
  store %struct.archive_match* %3, %struct.archive_match** %a, align 8, !dbg !3244
  %4 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !3245
  %5 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !3246
  %inclusion_unames = getelementptr inbounds %struct.archive_match, %struct.archive_match* %5, i32 0, i32 21, !dbg !3247
  %6 = load i32*, i32** %uname.addr, align 8, !dbg !3248
  %7 = bitcast i32* %6 to i8*, !dbg !3248
  %call1 = call i32 @add_owner_name(%struct.archive_match* %4, %struct.match_list* %inclusion_unames, i32 0, i8* %7), !dbg !3249
  store i32 %call1, i32* %retval, align 4, !dbg !3250
  br label %return, !dbg !3250

return:                                           ; preds = %do.end, %if.then
  %8 = load i32, i32* %retval, align 4, !dbg !3251
  ret i32 %8, !dbg !3251
}

; Function Attrs: nounwind uwtable
define i32 @archive_match_include_gname(%struct.archive* %_a, i8* %gname) #0 !dbg !273 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %gname.addr = alloca i8*, align 8
  %a = alloca %struct.archive_match*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !3252, metadata !394), !dbg !3253
  store i8* %gname, i8** %gname.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %gname.addr, metadata !3254, metadata !394), !dbg !3255
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a, metadata !3256, metadata !394), !dbg !3257
  br label %do.body, !dbg !3258

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !3259, metadata !394), !dbg !3261
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !3262
  %call = call i32 @__archive_check_magic(%struct.archive* %0, i32 212668873, i32 1, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.28, i32 0, i32 0)), !dbg !3262
  store i32 %call, i32* %magic_test, align 4, !dbg !3262
  %1 = load i32, i32* %magic_test, align 4, !dbg !3262
  %cmp = icmp eq i32 %1, -30, !dbg !3262
  br i1 %cmp, label %if.then, label %if.end, !dbg !3262

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !3264
  br label %return, !dbg !3264

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !3267

do.end:                                           ; preds = %if.end
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !3269
  %3 = bitcast %struct.archive* %2 to %struct.archive_match*, !dbg !3270
  store %struct.archive_match* %3, %struct.archive_match** %a, align 8, !dbg !3271
  %4 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !3272
  %5 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !3273
  %inclusion_gnames = getelementptr inbounds %struct.archive_match, %struct.archive_match* %5, i32 0, i32 22, !dbg !3274
  %6 = load i8*, i8** %gname.addr, align 8, !dbg !3275
  %call1 = call i32 @add_owner_name(%struct.archive_match* %4, %struct.match_list* %inclusion_gnames, i32 1, i8* %6), !dbg !3276
  store i32 %call1, i32* %retval, align 4, !dbg !3277
  br label %return, !dbg !3277

return:                                           ; preds = %do.end, %if.then
  %7 = load i32, i32* %retval, align 4, !dbg !3278
  ret i32 %7, !dbg !3278
}

; Function Attrs: nounwind uwtable
define i32 @archive_match_include_gname_w(%struct.archive* %_a, i32* %gname) #0 !dbg !274 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %gname.addr = alloca i32*, align 8
  %a = alloca %struct.archive_match*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !3279, metadata !394), !dbg !3280
  store i32* %gname, i32** %gname.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %gname.addr, metadata !3281, metadata !394), !dbg !3282
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a, metadata !3283, metadata !394), !dbg !3284
  br label %do.body, !dbg !3285

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !3286, metadata !394), !dbg !3288
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !3289
  %call = call i32 @__archive_check_magic(%struct.archive* %0, i32 212668873, i32 1, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.29, i32 0, i32 0)), !dbg !3289
  store i32 %call, i32* %magic_test, align 4, !dbg !3289
  %1 = load i32, i32* %magic_test, align 4, !dbg !3289
  %cmp = icmp eq i32 %1, -30, !dbg !3289
  br i1 %cmp, label %if.then, label %if.end, !dbg !3289

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !3291
  br label %return, !dbg !3291

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !3294

do.end:                                           ; preds = %if.end
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !3296
  %3 = bitcast %struct.archive* %2 to %struct.archive_match*, !dbg !3297
  store %struct.archive_match* %3, %struct.archive_match** %a, align 8, !dbg !3298
  %4 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !3299
  %5 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !3300
  %inclusion_gnames = getelementptr inbounds %struct.archive_match, %struct.archive_match* %5, i32 0, i32 22, !dbg !3301
  %6 = load i32*, i32** %gname.addr, align 8, !dbg !3302
  %7 = bitcast i32* %6 to i8*, !dbg !3302
  %call1 = call i32 @add_owner_name(%struct.archive_match* %4, %struct.match_list* %inclusion_gnames, i32 0, i8* %7), !dbg !3303
  store i32 %call1, i32* %retval, align 4, !dbg !3304
  br label %return, !dbg !3304

return:                                           ; preds = %do.end, %if.then
  %8 = load i32, i32* %retval, align 4, !dbg !3305
  ret i32 %8, !dbg !3305
}

; Function Attrs: nounwind uwtable
define i32 @archive_match_owner_excluded(%struct.archive* %_a, %struct.archive_entry* %entry1) #0 !dbg !275 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %a = alloca %struct.archive_match*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !3306, metadata !394), !dbg !3307
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3308, metadata !394), !dbg !3309
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a, metadata !3310, metadata !394), !dbg !3311
  br label %do.body, !dbg !3312

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !3313, metadata !394), !dbg !3315
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !3316
  %call = call i32 @__archive_check_magic(%struct.archive* %0, i32 212668873, i32 1, i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.30, i32 0, i32 0)), !dbg !3316
  store i32 %call, i32* %magic_test, align 4, !dbg !3316
  %1 = load i32, i32* %magic_test, align 4, !dbg !3316
  %cmp = icmp eq i32 %1, -30, !dbg !3316
  br i1 %cmp, label %if.then, label %if.end, !dbg !3316

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !3318
  br label %return, !dbg !3318

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !3321

do.end:                                           ; preds = %if.end
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !3323
  %3 = bitcast %struct.archive* %2 to %struct.archive_match*, !dbg !3324
  store %struct.archive_match* %3, %struct.archive_match** %a, align 8, !dbg !3325
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3326
  %cmp2 = icmp eq %struct.archive_entry* %4, null, !dbg !3328
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !3329

if.then3:                                         ; preds = %do.end
  %5 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !3330
  %archive = getelementptr inbounds %struct.archive_match, %struct.archive_match* %5, i32 0, i32 0, !dbg !3332
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 22, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.2, i32 0, i32 0)), !dbg !3333
  store i32 -25, i32* %retval, align 4, !dbg !3334
  br label %return, !dbg !3334

if.end4:                                          ; preds = %do.end
  %6 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !3335
  %setflag = getelementptr inbounds %struct.archive_match, %struct.archive_match* %6, i32 0, i32 1, !dbg !3337
  %7 = load i32, i32* %setflag, align 8, !dbg !3337
  %and = and i32 %7, 4, !dbg !3338
  %cmp5 = icmp eq i32 %and, 0, !dbg !3339
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !3340

if.then6:                                         ; preds = %if.end4
  store i32 0, i32* %retval, align 4, !dbg !3341
  br label %return, !dbg !3341

if.end7:                                          ; preds = %if.end4
  %8 = load %struct.archive_match*, %struct.archive_match** %a, align 8, !dbg !3342
  %9 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3343
  %call8 = call i32 @owner_excluded(%struct.archive_match* %8, %struct.archive_entry* %9), !dbg !3344
  store i32 %call8, i32* %retval, align 4, !dbg !3345
  br label %return, !dbg !3345

return:                                           ; preds = %if.end7, %if.then6, %if.then3, %if.then
  %10 = load i32, i32* %retval, align 4, !dbg !3346
  ret i32 %10, !dbg !3346
}

; Function Attrs: nounwind uwtable
define internal i32 @cmp_node_mbs(%struct.archive_rb_node* %n1, %struct.archive_rb_node* %n2) #0 !dbg !276 {
entry:
  %retval = alloca i32, align 4
  %n1.addr = alloca %struct.archive_rb_node*, align 8
  %n2.addr = alloca %struct.archive_rb_node*, align 8
  %f1 = alloca %struct.match_file*, align 8
  %f2 = alloca %struct.match_file*, align 8
  %p1 = alloca i8*, align 8
  %p2 = alloca i8*, align 8
  store %struct.archive_rb_node* %n1, %struct.archive_rb_node** %n1.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %n1.addr, metadata !3347, metadata !394), !dbg !3348
  store %struct.archive_rb_node* %n2, %struct.archive_rb_node** %n2.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %n2.addr, metadata !3349, metadata !394), !dbg !3350
  call void @llvm.dbg.declare(metadata %struct.match_file** %f1, metadata !3351, metadata !394), !dbg !3352
  %0 = load %struct.archive_rb_node*, %struct.archive_rb_node** %n1.addr, align 8, !dbg !3353
  %1 = ptrtoint %struct.archive_rb_node* %0 to i64, !dbg !3354
  %2 = inttoptr i64 %1 to %struct.match_file*, !dbg !3355
  store %struct.match_file* %2, %struct.match_file** %f1, align 8, !dbg !3352
  call void @llvm.dbg.declare(metadata %struct.match_file** %f2, metadata !3356, metadata !394), !dbg !3357
  %3 = load %struct.archive_rb_node*, %struct.archive_rb_node** %n2.addr, align 8, !dbg !3358
  %4 = ptrtoint %struct.archive_rb_node* %3 to i64, !dbg !3359
  %5 = inttoptr i64 %4 to %struct.match_file*, !dbg !3360
  store %struct.match_file* %5, %struct.match_file** %f2, align 8, !dbg !3357
  call void @llvm.dbg.declare(metadata i8** %p1, metadata !3361, metadata !394), !dbg !3362
  call void @llvm.dbg.declare(metadata i8** %p2, metadata !3363, metadata !394), !dbg !3364
  %6 = load %struct.match_file*, %struct.match_file** %f1, align 8, !dbg !3365
  %pathname = getelementptr inbounds %struct.match_file, %struct.match_file* %6, i32 0, i32 2, !dbg !3366
  %call = call i32 @archive_mstring_get_mbs(%struct.archive* null, %struct.archive_mstring* %pathname, i8** %p1), !dbg !3367
  %7 = load %struct.match_file*, %struct.match_file** %f2, align 8, !dbg !3368
  %pathname1 = getelementptr inbounds %struct.match_file, %struct.match_file* %7, i32 0, i32 2, !dbg !3369
  %call2 = call i32 @archive_mstring_get_mbs(%struct.archive* null, %struct.archive_mstring* %pathname1, i8** %p2), !dbg !3370
  %8 = load i8*, i8** %p1, align 8, !dbg !3371
  %cmp = icmp eq i8* %8, null, !dbg !3373
  br i1 %cmp, label %if.then, label %if.end, !dbg !3374

if.then:                                          ; preds = %entry
  store i32 1, i32* %retval, align 4, !dbg !3375
  br label %return, !dbg !3375

if.end:                                           ; preds = %entry
  %9 = load i8*, i8** %p2, align 8, !dbg !3376
  %cmp3 = icmp eq i8* %9, null, !dbg !3378
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !3379

if.then4:                                         ; preds = %if.end
  store i32 -1, i32* %retval, align 4, !dbg !3380
  br label %return, !dbg !3380

if.end5:                                          ; preds = %if.end
  %10 = load i8*, i8** %p1, align 8, !dbg !3381
  %11 = load i8*, i8** %p2, align 8, !dbg !3382
  %call6 = call i32 @strcmp(i8* %10, i8* %11) #8, !dbg !3383
  store i32 %call6, i32* %retval, align 4, !dbg !3384
  br label %return, !dbg !3384

return:                                           ; preds = %if.end5, %if.then4, %if.then
  %12 = load i32, i32* %retval, align 4, !dbg !3385
  ret i32 %12, !dbg !3385
}

; Function Attrs: nounwind uwtable
define internal i32 @cmp_key_mbs(%struct.archive_rb_node* %n, i8* %key) #0 !dbg !277 {
entry:
  %retval = alloca i32, align 4
  %n.addr = alloca %struct.archive_rb_node*, align 8
  %key.addr = alloca i8*, align 8
  %f = alloca %struct.match_file*, align 8
  %p = alloca i8*, align 8
  store %struct.archive_rb_node* %n, %struct.archive_rb_node** %n.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %n.addr, metadata !3386, metadata !394), !dbg !3387
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !3388, metadata !394), !dbg !3389
  call void @llvm.dbg.declare(metadata %struct.match_file** %f, metadata !3390, metadata !394), !dbg !3391
  %0 = load %struct.archive_rb_node*, %struct.archive_rb_node** %n.addr, align 8, !dbg !3392
  %1 = ptrtoint %struct.archive_rb_node* %0 to i64, !dbg !3393
  %2 = inttoptr i64 %1 to %struct.match_file*, !dbg !3394
  store %struct.match_file* %2, %struct.match_file** %f, align 8, !dbg !3391
  call void @llvm.dbg.declare(metadata i8** %p, metadata !3395, metadata !394), !dbg !3396
  %3 = load %struct.match_file*, %struct.match_file** %f, align 8, !dbg !3397
  %pathname = getelementptr inbounds %struct.match_file, %struct.match_file* %3, i32 0, i32 2, !dbg !3398
  %call = call i32 @archive_mstring_get_mbs(%struct.archive* null, %struct.archive_mstring* %pathname, i8** %p), !dbg !3399
  %4 = load i8*, i8** %p, align 8, !dbg !3400
  %cmp = icmp eq i8* %4, null, !dbg !3402
  br i1 %cmp, label %if.then, label %if.end, !dbg !3403

if.then:                                          ; preds = %entry
  store i32 -1, i32* %retval, align 4, !dbg !3404
  br label %return, !dbg !3404

if.end:                                           ; preds = %entry
  %5 = load i8*, i8** %p, align 8, !dbg !3405
  %6 = load i8*, i8** %key.addr, align 8, !dbg !3406
  %call1 = call i32 @strcmp(i8* %5, i8* %6) #8, !dbg !3407
  store i32 %call1, i32* %retval, align 4, !dbg !3408
  br label %return, !dbg !3408

return:                                           ; preds = %if.end, %if.then
  %7 = load i32, i32* %retval, align 4, !dbg !3409
  ret i32 %7, !dbg !3409
}

declare i32 @archive_mstring_get_mbs(%struct.archive*, %struct.archive_mstring*, i8**) #3

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #4

; Function Attrs: nounwind uwtable
define internal i32 @error_nomem(%struct.archive_match* %a) #0 !dbg !282 {
entry:
  %a.addr = alloca %struct.archive_match*, align 8
  store %struct.archive_match* %a, %struct.archive_match** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a.addr, metadata !3410, metadata !394), !dbg !3411
  %0 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !3412
  %archive = getelementptr inbounds %struct.archive_match, %struct.archive_match* %0, i32 0, i32 0, !dbg !3413
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.31, i32 0, i32 0)), !dbg !3414
  %1 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !3415
  %archive1 = getelementptr inbounds %struct.archive_match, %struct.archive_match* %1, i32 0, i32 0, !dbg !3416
  %state = getelementptr inbounds %struct.archive, %struct.archive* %archive1, i32 0, i32 1, !dbg !3417
  store i32 32768, i32* %state, align 4, !dbg !3418
  ret i32 -30, !dbg !3419
}

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #4

declare i32 @archive_mstring_copy_mbs_len(%struct.archive_mstring*, i8*, i64) #3

; Function Attrs: nounwind uwtable
define internal void @match_list_add(%struct.match_list* %list, %struct.match* %m) #0 !dbg !285 {
entry:
  %list.addr = alloca %struct.match_list*, align 8
  %m.addr = alloca %struct.match*, align 8
  store %struct.match_list* %list, %struct.match_list** %list.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.match_list** %list.addr, metadata !3420, metadata !394), !dbg !3421
  store %struct.match* %m, %struct.match** %m.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.match** %m.addr, metadata !3422, metadata !394), !dbg !3423
  %0 = load %struct.match*, %struct.match** %m.addr, align 8, !dbg !3424
  %1 = load %struct.match_list*, %struct.match_list** %list.addr, align 8, !dbg !3425
  %last = getelementptr inbounds %struct.match_list, %struct.match_list* %1, i32 0, i32 1, !dbg !3426
  %2 = load %struct.match**, %struct.match*** %last, align 8, !dbg !3426
  store %struct.match* %0, %struct.match** %2, align 8, !dbg !3427
  %3 = load %struct.match*, %struct.match** %m.addr, align 8, !dbg !3428
  %next = getelementptr inbounds %struct.match, %struct.match* %3, i32 0, i32 0, !dbg !3429
  %4 = load %struct.match_list*, %struct.match_list** %list.addr, align 8, !dbg !3430
  %last1 = getelementptr inbounds %struct.match_list, %struct.match_list* %4, i32 0, i32 1, !dbg !3431
  store %struct.match** %next, %struct.match*** %last1, align 8, !dbg !3432
  %5 = load %struct.match_list*, %struct.match_list** %list.addr, align 8, !dbg !3433
  %count = getelementptr inbounds %struct.match_list, %struct.match_list* %5, i32 0, i32 2, !dbg !3434
  %6 = load i32, i32* %count, align 8, !dbg !3435
  %inc = add nsw i32 %6, 1, !dbg !3435
  store i32 %inc, i32* %count, align 8, !dbg !3435
  %7 = load %struct.match_list*, %struct.match_list** %list.addr, align 8, !dbg !3436
  %unmatched_count = getelementptr inbounds %struct.match_list, %struct.match_list* %7, i32 0, i32 3, !dbg !3437
  %8 = load i32, i32* %unmatched_count, align 4, !dbg !3438
  %inc2 = add nsw i32 %8, 1, !dbg !3438
  store i32 %inc2, i32* %unmatched_count, align 4, !dbg !3438
  ret void, !dbg !3439
}

; Function Attrs: nounwind readonly
declare i64 @wcslen(i32*) #4

declare i32 @archive_mstring_copy_wcs_len(%struct.archive_mstring*, i32*, i64) #3

declare %struct.archive* @archive_read_new() #3

declare i32 @archive_read_support_format_raw(%struct.archive*) #3

declare i32 @archive_read_support_format_empty(%struct.archive*) #3

declare void @archive_copy_error(%struct.archive*, %struct.archive*) #3

declare i32 @archive_read_free(%struct.archive*) #3

declare i32 @archive_read_open_filename(%struct.archive*, i8*, i64) #3

declare i32 @archive_read_open_filename_w(%struct.archive*, i32*, i64) #3

declare i32 @archive_read_next_header(%struct.archive*, %struct.archive_entry**) #3

declare i32 @archive_read_data_block(%struct.archive*, i8**, i64*, i64*) #3

declare %struct.archive_string* @archive_strncat(%struct.archive_string*, i8*, i64) #3

declare void @archive_string_free(%struct.archive_string*) #3

; Function Attrs: nounwind uwtable
define internal i32 @match_path_inclusion(%struct.archive_match* %a, %struct.match* %m, i32 %mbs, i8* %pn) #0 !dbg !297 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_match*, align 8
  %m.addr = alloca %struct.match*, align 8
  %mbs.addr = alloca i32, align 4
  %pn.addr = alloca i8*, align 8
  %flag = alloca i32, align 4
  %r = alloca i32, align 4
  %p = alloca i8*, align 8
  %p3 = alloca i32*, align 8
  store %struct.archive_match* %a, %struct.archive_match** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a.addr, metadata !3440, metadata !394), !dbg !3441
  store %struct.match* %m, %struct.match** %m.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.match** %m.addr, metadata !3442, metadata !394), !dbg !3443
  store i32 %mbs, i32* %mbs.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %mbs.addr, metadata !3444, metadata !394), !dbg !3445
  store i8* %pn, i8** %pn.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %pn.addr, metadata !3446, metadata !394), !dbg !3447
  call void @llvm.dbg.declare(metadata i32* %flag, metadata !3448, metadata !394), !dbg !3449
  store i32 2, i32* %flag, align 4, !dbg !3449
  call void @llvm.dbg.declare(metadata i32* %r, metadata !3450, metadata !394), !dbg !3451
  %0 = load i32, i32* %mbs.addr, align 4, !dbg !3452
  %tobool = icmp ne i32 %0, 0, !dbg !3452
  br i1 %tobool, label %if.then, label %if.else, !dbg !3454

if.then:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i8** %p, metadata !3455, metadata !394), !dbg !3457
  %1 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !3458
  %archive = getelementptr inbounds %struct.archive_match, %struct.archive_match* %1, i32 0, i32 0, !dbg !3459
  %2 = load %struct.match*, %struct.match** %m.addr, align 8, !dbg !3460
  %pattern = getelementptr inbounds %struct.match, %struct.match* %2, i32 0, i32 2, !dbg !3461
  %call = call i32 @archive_mstring_get_mbs(%struct.archive* %archive, %struct.archive_mstring* %pattern, i8** %p), !dbg !3462
  store i32 %call, i32* %r, align 4, !dbg !3463
  %3 = load i32, i32* %r, align 4, !dbg !3464
  %cmp = icmp eq i32 %3, 0, !dbg !3466
  br i1 %cmp, label %if.then1, label %if.end, !dbg !3467

if.then1:                                         ; preds = %if.then
  %4 = load i8*, i8** %p, align 8, !dbg !3468
  %5 = load i8*, i8** %pn.addr, align 8, !dbg !3468
  %6 = load i32, i32* %flag, align 4, !dbg !3468
  %call2 = call i32 @__archive_pathmatch(i8* %4, i8* %5, i32 %6), !dbg !3468
  store i32 %call2, i32* %retval, align 4, !dbg !3469
  br label %return, !dbg !3469

if.end:                                           ; preds = %if.then
  br label %if.end11, !dbg !3470

if.else:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32** %p3, metadata !3471, metadata !394), !dbg !3473
  %7 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !3474
  %archive4 = getelementptr inbounds %struct.archive_match, %struct.archive_match* %7, i32 0, i32 0, !dbg !3475
  %8 = load %struct.match*, %struct.match** %m.addr, align 8, !dbg !3476
  %pattern5 = getelementptr inbounds %struct.match, %struct.match* %8, i32 0, i32 2, !dbg !3477
  %call6 = call i32 @archive_mstring_get_wcs(%struct.archive* %archive4, %struct.archive_mstring* %pattern5, i32** %p3), !dbg !3478
  store i32 %call6, i32* %r, align 4, !dbg !3479
  %9 = load i32, i32* %r, align 4, !dbg !3480
  %cmp7 = icmp eq i32 %9, 0, !dbg !3482
  br i1 %cmp7, label %if.then8, label %if.end10, !dbg !3483

if.then8:                                         ; preds = %if.else
  %10 = load i32*, i32** %p3, align 8, !dbg !3484
  %11 = load i8*, i8** %pn.addr, align 8, !dbg !3484
  %12 = bitcast i8* %11 to i32*, !dbg !3484
  %13 = load i32, i32* %flag, align 4, !dbg !3484
  %call9 = call i32 @__archive_pathmatch_w(i32* %10, i32* %12, i32 %13), !dbg !3484
  store i32 %call9, i32* %retval, align 4, !dbg !3485
  br label %return, !dbg !3485

if.end10:                                         ; preds = %if.else
  br label %if.end11

if.end11:                                         ; preds = %if.end10, %if.end
  %call12 = call i32* @__errno_location() #1, !dbg !3486
  %14 = load i32, i32* %call12, align 4, !dbg !3486
  %cmp13 = icmp eq i32 %14, 12, !dbg !3488
  br i1 %cmp13, label %if.then14, label %if.end16, !dbg !3489

if.then14:                                        ; preds = %if.end11
  %15 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !3490
  %call15 = call i32 @error_nomem(%struct.archive_match* %15), !dbg !3491
  store i32 %call15, i32* %retval, align 4, !dbg !3492
  br label %return, !dbg !3492

if.end16:                                         ; preds = %if.end11
  store i32 0, i32* %retval, align 4, !dbg !3493
  br label %return, !dbg !3493

return:                                           ; preds = %if.end16, %if.then14, %if.then8, %if.then1
  %16 = load i32, i32* %retval, align 4, !dbg !3494
  ret i32 %16, !dbg !3494
}

; Function Attrs: nounwind uwtable
define internal i32 @match_path_exclusion(%struct.archive_match* %a, %struct.match* %m, i32 %mbs, i8* %pn) #0 !dbg !300 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_match*, align 8
  %m.addr = alloca %struct.match*, align 8
  %mbs.addr = alloca i32, align 4
  %pn.addr = alloca i8*, align 8
  %flag = alloca i32, align 4
  %r = alloca i32, align 4
  %p = alloca i8*, align 8
  %p3 = alloca i32*, align 8
  store %struct.archive_match* %a, %struct.archive_match** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a.addr, metadata !3495, metadata !394), !dbg !3496
  store %struct.match* %m, %struct.match** %m.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.match** %m.addr, metadata !3497, metadata !394), !dbg !3498
  store i32 %mbs, i32* %mbs.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %mbs.addr, metadata !3499, metadata !394), !dbg !3500
  store i8* %pn, i8** %pn.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %pn.addr, metadata !3501, metadata !394), !dbg !3502
  call void @llvm.dbg.declare(metadata i32* %flag, metadata !3503, metadata !394), !dbg !3504
  store i32 3, i32* %flag, align 4, !dbg !3504
  call void @llvm.dbg.declare(metadata i32* %r, metadata !3505, metadata !394), !dbg !3506
  %0 = load i32, i32* %mbs.addr, align 4, !dbg !3507
  %tobool = icmp ne i32 %0, 0, !dbg !3507
  br i1 %tobool, label %if.then, label %if.else, !dbg !3509

if.then:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i8** %p, metadata !3510, metadata !394), !dbg !3512
  %1 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !3513
  %archive = getelementptr inbounds %struct.archive_match, %struct.archive_match* %1, i32 0, i32 0, !dbg !3514
  %2 = load %struct.match*, %struct.match** %m.addr, align 8, !dbg !3515
  %pattern = getelementptr inbounds %struct.match, %struct.match* %2, i32 0, i32 2, !dbg !3516
  %call = call i32 @archive_mstring_get_mbs(%struct.archive* %archive, %struct.archive_mstring* %pattern, i8** %p), !dbg !3517
  store i32 %call, i32* %r, align 4, !dbg !3518
  %3 = load i32, i32* %r, align 4, !dbg !3519
  %cmp = icmp eq i32 %3, 0, !dbg !3521
  br i1 %cmp, label %if.then1, label %if.end, !dbg !3522

if.then1:                                         ; preds = %if.then
  %4 = load i8*, i8** %p, align 8, !dbg !3523
  %5 = load i8*, i8** %pn.addr, align 8, !dbg !3523
  %6 = load i32, i32* %flag, align 4, !dbg !3523
  %call2 = call i32 @__archive_pathmatch(i8* %4, i8* %5, i32 %6), !dbg !3523
  store i32 %call2, i32* %retval, align 4, !dbg !3524
  br label %return, !dbg !3524

if.end:                                           ; preds = %if.then
  br label %if.end11, !dbg !3525

if.else:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32** %p3, metadata !3526, metadata !394), !dbg !3528
  %7 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !3529
  %archive4 = getelementptr inbounds %struct.archive_match, %struct.archive_match* %7, i32 0, i32 0, !dbg !3530
  %8 = load %struct.match*, %struct.match** %m.addr, align 8, !dbg !3531
  %pattern5 = getelementptr inbounds %struct.match, %struct.match* %8, i32 0, i32 2, !dbg !3532
  %call6 = call i32 @archive_mstring_get_wcs(%struct.archive* %archive4, %struct.archive_mstring* %pattern5, i32** %p3), !dbg !3533
  store i32 %call6, i32* %r, align 4, !dbg !3534
  %9 = load i32, i32* %r, align 4, !dbg !3535
  %cmp7 = icmp eq i32 %9, 0, !dbg !3537
  br i1 %cmp7, label %if.then8, label %if.end10, !dbg !3538

if.then8:                                         ; preds = %if.else
  %10 = load i32*, i32** %p3, align 8, !dbg !3539
  %11 = load i8*, i8** %pn.addr, align 8, !dbg !3539
  %12 = bitcast i8* %11 to i32*, !dbg !3539
  %13 = load i32, i32* %flag, align 4, !dbg !3539
  %call9 = call i32 @__archive_pathmatch_w(i32* %10, i32* %12, i32 %13), !dbg !3539
  store i32 %call9, i32* %retval, align 4, !dbg !3540
  br label %return, !dbg !3540

if.end10:                                         ; preds = %if.else
  br label %if.end11

if.end11:                                         ; preds = %if.end10, %if.end
  %call12 = call i32* @__errno_location() #1, !dbg !3541
  %14 = load i32, i32* %call12, align 4, !dbg !3541
  %cmp13 = icmp eq i32 %14, 12, !dbg !3543
  br i1 %cmp13, label %if.then14, label %if.end16, !dbg !3544

if.then14:                                        ; preds = %if.end11
  %15 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !3545
  %call15 = call i32 @error_nomem(%struct.archive_match* %15), !dbg !3546
  store i32 %call15, i32* %retval, align 4, !dbg !3547
  br label %return, !dbg !3547

if.end16:                                         ; preds = %if.end11
  store i32 0, i32* %retval, align 4, !dbg !3548
  br label %return, !dbg !3548

return:                                           ; preds = %if.end16, %if.then14, %if.then8, %if.then1
  %16 = load i32, i32* %retval, align 4, !dbg !3549
  ret i32 %16, !dbg !3549
}

declare i32 @__archive_pathmatch(i8*, i8*, i32) #3

declare i32 @archive_mstring_get_wcs(%struct.archive*, %struct.archive_mstring*, i32**) #3

declare i32 @__archive_pathmatch_w(i32*, i32*, i32) #3

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #5

declare void @archive_mstring_clean(%struct.archive_mstring*) #3

declare i64 @__archive_get_date(i64, i8*) #3

declare i32 @archive_string_append_from_wcs(%struct.archive_string*, i32*, i64) #3

; Function Attrs: nounwind
declare i32 @stat(i8*, %struct.stat*) #2

; Function Attrs: nounwind uwtable
define internal i32 @set_timefilter_stat(%struct.archive_match* %a, i32 %timetype, %struct.stat* %st) #0 !dbg !319 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_match*, align 8
  %timetype.addr = alloca i32, align 4
  %st.addr = alloca %struct.stat*, align 8
  %ae = alloca %struct.archive_entry*, align 8
  %ctime_sec = alloca i64, align 8
  %mtime_sec = alloca i64, align 8
  %ctime_ns = alloca i64, align 8
  %mtime_ns = alloca i64, align 8
  store %struct.archive_match* %a, %struct.archive_match** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a.addr, metadata !3550, metadata !394), !dbg !3551
  store i32 %timetype, i32* %timetype.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %timetype.addr, metadata !3552, metadata !394), !dbg !3553
  store %struct.stat* %st, %struct.stat** %st.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.stat** %st.addr, metadata !3554, metadata !394), !dbg !3555
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %ae, metadata !3556, metadata !394), !dbg !3557
  call void @llvm.dbg.declare(metadata i64* %ctime_sec, metadata !3558, metadata !394), !dbg !3559
  call void @llvm.dbg.declare(metadata i64* %mtime_sec, metadata !3560, metadata !394), !dbg !3561
  call void @llvm.dbg.declare(metadata i64* %ctime_ns, metadata !3562, metadata !394), !dbg !3563
  call void @llvm.dbg.declare(metadata i64* %mtime_ns, metadata !3564, metadata !394), !dbg !3565
  %call = call %struct.archive_entry* @archive_entry_new(), !dbg !3566
  store %struct.archive_entry* %call, %struct.archive_entry** %ae, align 8, !dbg !3567
  %0 = load %struct.archive_entry*, %struct.archive_entry** %ae, align 8, !dbg !3568
  %cmp = icmp eq %struct.archive_entry* %0, null, !dbg !3570
  br i1 %cmp, label %if.then, label %if.end, !dbg !3571

if.then:                                          ; preds = %entry
  %1 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !3572
  %call1 = call i32 @error_nomem(%struct.archive_match* %1), !dbg !3573
  store i32 %call1, i32* %retval, align 4, !dbg !3574
  br label %return, !dbg !3574

if.end:                                           ; preds = %entry
  %2 = load %struct.archive_entry*, %struct.archive_entry** %ae, align 8, !dbg !3575
  %3 = load %struct.stat*, %struct.stat** %st.addr, align 8, !dbg !3576
  call void @archive_entry_copy_stat(%struct.archive_entry* %2, %struct.stat* %3), !dbg !3577
  %4 = load %struct.archive_entry*, %struct.archive_entry** %ae, align 8, !dbg !3578
  %call2 = call i64 @archive_entry_ctime(%struct.archive_entry* %4), !dbg !3579
  store i64 %call2, i64* %ctime_sec, align 8, !dbg !3580
  %5 = load %struct.archive_entry*, %struct.archive_entry** %ae, align 8, !dbg !3581
  %call3 = call i64 @archive_entry_ctime_nsec(%struct.archive_entry* %5), !dbg !3582
  store i64 %call3, i64* %ctime_ns, align 8, !dbg !3583
  %6 = load %struct.archive_entry*, %struct.archive_entry** %ae, align 8, !dbg !3584
  %call4 = call i64 @archive_entry_mtime(%struct.archive_entry* %6), !dbg !3585
  store i64 %call4, i64* %mtime_sec, align 8, !dbg !3586
  %7 = load %struct.archive_entry*, %struct.archive_entry** %ae, align 8, !dbg !3587
  %call5 = call i64 @archive_entry_mtime_nsec(%struct.archive_entry* %7), !dbg !3588
  store i64 %call5, i64* %mtime_ns, align 8, !dbg !3589
  %8 = load %struct.archive_entry*, %struct.archive_entry** %ae, align 8, !dbg !3590
  call void @archive_entry_free(%struct.archive_entry* %8), !dbg !3591
  %9 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !3592
  %10 = load i32, i32* %timetype.addr, align 4, !dbg !3593
  %11 = load i64, i64* %mtime_sec, align 8, !dbg !3594
  %12 = load i64, i64* %mtime_ns, align 8, !dbg !3595
  %13 = load i64, i64* %ctime_sec, align 8, !dbg !3596
  %14 = load i64, i64* %ctime_ns, align 8, !dbg !3597
  %call6 = call i32 @set_timefilter(%struct.archive_match* %9, i32 %10, i64 %11, i64 %12, i64 %13, i64 %14), !dbg !3598
  store i32 %call6, i32* %retval, align 4, !dbg !3599
  br label %return, !dbg !3599

return:                                           ; preds = %if.end, %if.then
  %15 = load i32, i32* %retval, align 4, !dbg !3600
  ret i32 %15, !dbg !3600
}

declare %struct.archive_entry* @archive_entry_new() #3

declare void @archive_entry_copy_stat(%struct.archive_entry*, %struct.stat*) #3

declare i64 @archive_entry_ctime(%struct.archive_entry*) #3

declare i64 @archive_entry_ctime_nsec(%struct.archive_entry*) #3

declare i64 @archive_entry_mtime(%struct.archive_entry*) #3

declare i64 @archive_entry_mtime_nsec(%struct.archive_entry*) #3

declare void @archive_entry_free(%struct.archive_entry*) #3

declare i32 @archive_mstring_copy_mbs(%struct.archive_mstring*, i8*) #3

declare i32 @__archive_rb_tree_insert_node(%struct.archive_rb_tree*, %struct.archive_rb_node*) #3

declare %struct.archive_rb_node* @__archive_rb_tree_find_node(%struct.archive_rb_tree*, i8*) #3

; Function Attrs: nounwind uwtable
define internal void @entry_list_add(%struct.entry_list* %list, %struct.match_file* %file) #0 !dbg !369 {
entry:
  %list.addr = alloca %struct.entry_list*, align 8
  %file.addr = alloca %struct.match_file*, align 8
  store %struct.entry_list* %list, %struct.entry_list** %list.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.entry_list** %list.addr, metadata !3601, metadata !394), !dbg !3602
  store %struct.match_file* %file, %struct.match_file** %file.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.match_file** %file.addr, metadata !3603, metadata !394), !dbg !3604
  %0 = load %struct.match_file*, %struct.match_file** %file.addr, align 8, !dbg !3605
  %1 = load %struct.entry_list*, %struct.entry_list** %list.addr, align 8, !dbg !3606
  %last = getelementptr inbounds %struct.entry_list, %struct.entry_list* %1, i32 0, i32 1, !dbg !3607
  %2 = load %struct.match_file**, %struct.match_file*** %last, align 8, !dbg !3607
  store %struct.match_file* %0, %struct.match_file** %2, align 8, !dbg !3608
  %3 = load %struct.match_file*, %struct.match_file** %file.addr, align 8, !dbg !3609
  %next = getelementptr inbounds %struct.match_file, %struct.match_file* %3, i32 0, i32 1, !dbg !3610
  %4 = load %struct.entry_list*, %struct.entry_list** %list.addr, align 8, !dbg !3611
  %last1 = getelementptr inbounds %struct.entry_list, %struct.entry_list* %4, i32 0, i32 1, !dbg !3612
  store %struct.match_file** %next, %struct.match_file*** %last1, align 8, !dbg !3613
  %5 = load %struct.entry_list*, %struct.entry_list** %list.addr, align 8, !dbg !3614
  %count = getelementptr inbounds %struct.entry_list, %struct.entry_list* %5, i32 0, i32 2, !dbg !3615
  %6 = load i32, i32* %count, align 8, !dbg !3616
  %inc = add nsw i32 %6, 1, !dbg !3616
  store i32 %inc, i32* %count, align 8, !dbg !3616
  ret void, !dbg !3617
}

; Function Attrs: nounwind uwtable
define internal i32 @cmp_node_wcs(%struct.archive_rb_node* %n1, %struct.archive_rb_node* %n2) #0 !dbg !367 {
entry:
  %retval = alloca i32, align 4
  %n1.addr = alloca %struct.archive_rb_node*, align 8
  %n2.addr = alloca %struct.archive_rb_node*, align 8
  %f1 = alloca %struct.match_file*, align 8
  %f2 = alloca %struct.match_file*, align 8
  %p1 = alloca i32*, align 8
  %p2 = alloca i32*, align 8
  store %struct.archive_rb_node* %n1, %struct.archive_rb_node** %n1.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %n1.addr, metadata !3618, metadata !394), !dbg !3619
  store %struct.archive_rb_node* %n2, %struct.archive_rb_node** %n2.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %n2.addr, metadata !3620, metadata !394), !dbg !3621
  call void @llvm.dbg.declare(metadata %struct.match_file** %f1, metadata !3622, metadata !394), !dbg !3623
  %0 = load %struct.archive_rb_node*, %struct.archive_rb_node** %n1.addr, align 8, !dbg !3624
  %1 = ptrtoint %struct.archive_rb_node* %0 to i64, !dbg !3625
  %2 = inttoptr i64 %1 to %struct.match_file*, !dbg !3626
  store %struct.match_file* %2, %struct.match_file** %f1, align 8, !dbg !3623
  call void @llvm.dbg.declare(metadata %struct.match_file** %f2, metadata !3627, metadata !394), !dbg !3628
  %3 = load %struct.archive_rb_node*, %struct.archive_rb_node** %n2.addr, align 8, !dbg !3629
  %4 = ptrtoint %struct.archive_rb_node* %3 to i64, !dbg !3630
  %5 = inttoptr i64 %4 to %struct.match_file*, !dbg !3631
  store %struct.match_file* %5, %struct.match_file** %f2, align 8, !dbg !3628
  call void @llvm.dbg.declare(metadata i32** %p1, metadata !3632, metadata !394), !dbg !3633
  call void @llvm.dbg.declare(metadata i32** %p2, metadata !3634, metadata !394), !dbg !3635
  %6 = load %struct.match_file*, %struct.match_file** %f1, align 8, !dbg !3636
  %pathname = getelementptr inbounds %struct.match_file, %struct.match_file* %6, i32 0, i32 2, !dbg !3637
  %call = call i32 @archive_mstring_get_wcs(%struct.archive* null, %struct.archive_mstring* %pathname, i32** %p1), !dbg !3638
  %7 = load %struct.match_file*, %struct.match_file** %f2, align 8, !dbg !3639
  %pathname1 = getelementptr inbounds %struct.match_file, %struct.match_file* %7, i32 0, i32 2, !dbg !3640
  %call2 = call i32 @archive_mstring_get_wcs(%struct.archive* null, %struct.archive_mstring* %pathname1, i32** %p2), !dbg !3641
  %8 = load i32*, i32** %p1, align 8, !dbg !3642
  %cmp = icmp eq i32* %8, null, !dbg !3644
  br i1 %cmp, label %if.then, label %if.end, !dbg !3645

if.then:                                          ; preds = %entry
  store i32 1, i32* %retval, align 4, !dbg !3646
  br label %return, !dbg !3646

if.end:                                           ; preds = %entry
  %9 = load i32*, i32** %p2, align 8, !dbg !3647
  %cmp3 = icmp eq i32* %9, null, !dbg !3649
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !3650

if.then4:                                         ; preds = %if.end
  store i32 -1, i32* %retval, align 4, !dbg !3651
  br label %return, !dbg !3651

if.end5:                                          ; preds = %if.end
  %10 = load i32*, i32** %p1, align 8, !dbg !3652
  %11 = load i32*, i32** %p2, align 8, !dbg !3653
  %call6 = call i32 @wcscmp(i32* %10, i32* %11) #8, !dbg !3654
  store i32 %call6, i32* %retval, align 4, !dbg !3655
  br label %return, !dbg !3655

return:                                           ; preds = %if.end5, %if.then4, %if.then
  %12 = load i32, i32* %retval, align 4, !dbg !3656
  ret i32 %12, !dbg !3656
}

; Function Attrs: nounwind uwtable
define internal i32 @cmp_key_wcs(%struct.archive_rb_node* %n, i8* %key) #0 !dbg !368 {
entry:
  %retval = alloca i32, align 4
  %n.addr = alloca %struct.archive_rb_node*, align 8
  %key.addr = alloca i8*, align 8
  %f = alloca %struct.match_file*, align 8
  %p = alloca i32*, align 8
  store %struct.archive_rb_node* %n, %struct.archive_rb_node** %n.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_rb_node** %n.addr, metadata !3657, metadata !394), !dbg !3658
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !3659, metadata !394), !dbg !3660
  call void @llvm.dbg.declare(metadata %struct.match_file** %f, metadata !3661, metadata !394), !dbg !3662
  %0 = load %struct.archive_rb_node*, %struct.archive_rb_node** %n.addr, align 8, !dbg !3663
  %1 = ptrtoint %struct.archive_rb_node* %0 to i64, !dbg !3664
  %2 = inttoptr i64 %1 to %struct.match_file*, !dbg !3665
  store %struct.match_file* %2, %struct.match_file** %f, align 8, !dbg !3662
  call void @llvm.dbg.declare(metadata i32** %p, metadata !3666, metadata !394), !dbg !3667
  %3 = load %struct.match_file*, %struct.match_file** %f, align 8, !dbg !3668
  %pathname = getelementptr inbounds %struct.match_file, %struct.match_file* %3, i32 0, i32 2, !dbg !3669
  %call = call i32 @archive_mstring_get_wcs(%struct.archive* null, %struct.archive_mstring* %pathname, i32** %p), !dbg !3670
  %4 = load i32*, i32** %p, align 8, !dbg !3671
  %cmp = icmp eq i32* %4, null, !dbg !3673
  br i1 %cmp, label %if.then, label %if.end, !dbg !3674

if.then:                                          ; preds = %entry
  store i32 -1, i32* %retval, align 4, !dbg !3675
  br label %return, !dbg !3675

if.end:                                           ; preds = %entry
  %5 = load i32*, i32** %p, align 8, !dbg !3676
  %6 = load i8*, i8** %key.addr, align 8, !dbg !3677
  %7 = bitcast i8* %6 to i32*, !dbg !3678
  %call1 = call i32 @wcscmp(i32* %5, i32* %7) #8, !dbg !3679
  store i32 %call1, i32* %retval, align 4, !dbg !3680
  br label %return, !dbg !3680

return:                                           ; preds = %if.end, %if.then
  %8 = load i32, i32* %retval, align 4, !dbg !3681
  ret i32 %8, !dbg !3681
}

; Function Attrs: nounwind readonly
declare i32 @wcscmp(i32*, i32*) #4

declare i32 @archive_entry_ctime_is_set(%struct.archive_entry*) #3

; Function Attrs: nounwind
declare i8* @realloc(i8*, i64) #2

; Function Attrs: argmemonly nounwind
declare void @llvm.memmove.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #6

declare i32 @archive_mstring_copy_wcs(%struct.archive_mstring*, i32*) #3

; Function Attrs: nounwind uwtable
define internal i32 @match_owner_id(%struct.id_array* %ids, i64 %id) #0 !dbg !383 {
entry:
  %retval = alloca i32, align 4
  %ids.addr = alloca %struct.id_array*, align 8
  %id.addr = alloca i64, align 8
  %b = alloca i32, align 4
  %m = alloca i32, align 4
  %t = alloca i32, align 4
  store %struct.id_array* %ids, %struct.id_array** %ids.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.id_array** %ids.addr, metadata !3682, metadata !394), !dbg !3683
  store i64 %id, i64* %id.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %id.addr, metadata !3684, metadata !394), !dbg !3685
  call void @llvm.dbg.declare(metadata i32* %b, metadata !3686, metadata !394), !dbg !3687
  call void @llvm.dbg.declare(metadata i32* %m, metadata !3688, metadata !394), !dbg !3689
  call void @llvm.dbg.declare(metadata i32* %t, metadata !3690, metadata !394), !dbg !3691
  store i32 0, i32* %t, align 4, !dbg !3692
  %0 = load %struct.id_array*, %struct.id_array** %ids.addr, align 8, !dbg !3693
  %count = getelementptr inbounds %struct.id_array, %struct.id_array* %0, i32 0, i32 1, !dbg !3694
  %1 = load i64, i64* %count, align 8, !dbg !3694
  %conv = trunc i64 %1 to i32, !dbg !3695
  store i32 %conv, i32* %b, align 4, !dbg !3696
  br label %while.cond, !dbg !3697

while.cond:                                       ; preds = %if.end12, %entry
  %2 = load i32, i32* %t, align 4, !dbg !3698
  %3 = load i32, i32* %b, align 4, !dbg !3700
  %cmp = icmp ult i32 %2, %3, !dbg !3701
  br i1 %cmp, label %while.body, label %while.end, !dbg !3702

while.body:                                       ; preds = %while.cond
  %4 = load i32, i32* %t, align 4, !dbg !3703
  %5 = load i32, i32* %b, align 4, !dbg !3705
  %add = add i32 %4, %5, !dbg !3706
  %shr = lshr i32 %add, 1, !dbg !3707
  store i32 %shr, i32* %m, align 4, !dbg !3708
  %6 = load i32, i32* %m, align 4, !dbg !3709
  %idxprom = zext i32 %6 to i64, !dbg !3711
  %7 = load %struct.id_array*, %struct.id_array** %ids.addr, align 8, !dbg !3711
  %ids2 = getelementptr inbounds %struct.id_array, %struct.id_array* %7, i32 0, i32 2, !dbg !3712
  %8 = load i64*, i64** %ids2, align 8, !dbg !3712
  %arrayidx = getelementptr inbounds i64, i64* %8, i64 %idxprom, !dbg !3711
  %9 = load i64, i64* %arrayidx, align 8, !dbg !3711
  %10 = load i64, i64* %id.addr, align 8, !dbg !3713
  %cmp3 = icmp eq i64 %9, %10, !dbg !3714
  br i1 %cmp3, label %if.then, label %if.end, !dbg !3715

if.then:                                          ; preds = %while.body
  store i32 1, i32* %retval, align 4, !dbg !3716
  br label %return, !dbg !3716

if.end:                                           ; preds = %while.body
  %11 = load i32, i32* %m, align 4, !dbg !3717
  %idxprom5 = zext i32 %11 to i64, !dbg !3719
  %12 = load %struct.id_array*, %struct.id_array** %ids.addr, align 8, !dbg !3719
  %ids6 = getelementptr inbounds %struct.id_array, %struct.id_array* %12, i32 0, i32 2, !dbg !3720
  %13 = load i64*, i64** %ids6, align 8, !dbg !3720
  %arrayidx7 = getelementptr inbounds i64, i64* %13, i64 %idxprom5, !dbg !3719
  %14 = load i64, i64* %arrayidx7, align 8, !dbg !3719
  %15 = load i64, i64* %id.addr, align 8, !dbg !3721
  %cmp8 = icmp slt i64 %14, %15, !dbg !3722
  br i1 %cmp8, label %if.then10, label %if.else, !dbg !3723

if.then10:                                        ; preds = %if.end
  %16 = load i32, i32* %m, align 4, !dbg !3724
  %add11 = add i32 %16, 1, !dbg !3725
  store i32 %add11, i32* %t, align 4, !dbg !3726
  br label %if.end12, !dbg !3727

if.else:                                          ; preds = %if.end
  %17 = load i32, i32* %m, align 4, !dbg !3728
  store i32 %17, i32* %b, align 4, !dbg !3729
  br label %if.end12

if.end12:                                         ; preds = %if.else, %if.then10
  br label %while.cond, !dbg !3730

while.end:                                        ; preds = %while.cond
  store i32 0, i32* %retval, align 4, !dbg !3732
  br label %return, !dbg !3732

return:                                           ; preds = %while.end, %if.then
  %18 = load i32, i32* %retval, align 4, !dbg !3733
  ret i32 %18, !dbg !3733
}

declare i64 @archive_entry_uid(%struct.archive_entry*) #3

declare i64 @archive_entry_gid(%struct.archive_entry*) #3

; Function Attrs: nounwind uwtable
define internal i32 @match_owner_name_mbs(%struct.archive_match* %a, %struct.match_list* %list, i8* %name) #0 !dbg !386 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_match*, align 8
  %list.addr = alloca %struct.match_list*, align 8
  %name.addr = alloca i8*, align 8
  %m = alloca %struct.match*, align 8
  %p = alloca i8*, align 8
  store %struct.archive_match* %a, %struct.archive_match** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_match** %a.addr, metadata !3734, metadata !394), !dbg !3735
  store %struct.match_list* %list, %struct.match_list** %list.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.match_list** %list.addr, metadata !3736, metadata !394), !dbg !3737
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !3738, metadata !394), !dbg !3739
  call void @llvm.dbg.declare(metadata %struct.match** %m, metadata !3740, metadata !394), !dbg !3741
  call void @llvm.dbg.declare(metadata i8** %p, metadata !3742, metadata !394), !dbg !3743
  %0 = load i8*, i8** %name.addr, align 8, !dbg !3744
  %cmp = icmp eq i8* %0, null, !dbg !3746
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !3747

lor.lhs.false:                                    ; preds = %entry
  %1 = load i8*, i8** %name.addr, align 8, !dbg !3748
  %2 = load i8, i8* %1, align 1, !dbg !3750
  %conv = sext i8 %2 to i32, !dbg !3750
  %cmp1 = icmp eq i32 %conv, 0, !dbg !3751
  br i1 %cmp1, label %if.then, label %if.end, !dbg !3752

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 0, i32* %retval, align 4, !dbg !3753
  br label %return, !dbg !3753

if.end:                                           ; preds = %lor.lhs.false
  %3 = load %struct.match_list*, %struct.match_list** %list.addr, align 8, !dbg !3754
  %first = getelementptr inbounds %struct.match_list, %struct.match_list* %3, i32 0, i32 0, !dbg !3756
  %4 = load %struct.match*, %struct.match** %first, align 8, !dbg !3756
  store %struct.match* %4, %struct.match** %m, align 8, !dbg !3757
  br label %for.cond, !dbg !3758

for.cond:                                         ; preds = %for.inc, %if.end
  %5 = load %struct.match*, %struct.match** %m, align 8, !dbg !3759
  %tobool = icmp ne %struct.match* %5, null, !dbg !3762
  br i1 %tobool, label %for.body, label %for.end, !dbg !3762

for.body:                                         ; preds = %for.cond
  %6 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !3763
  %archive = getelementptr inbounds %struct.archive_match, %struct.archive_match* %6, i32 0, i32 0, !dbg !3766
  %7 = load %struct.match*, %struct.match** %m, align 8, !dbg !3767
  %pattern = getelementptr inbounds %struct.match, %struct.match* %7, i32 0, i32 2, !dbg !3768
  %call = call i32 @archive_mstring_get_mbs(%struct.archive* %archive, %struct.archive_mstring* %pattern, i8** %p), !dbg !3769
  %cmp3 = icmp slt i32 %call, 0, !dbg !3770
  br i1 %cmp3, label %land.lhs.true, label %if.end10, !dbg !3771

land.lhs.true:                                    ; preds = %for.body
  %call5 = call i32* @__errno_location() #1, !dbg !3772
  %8 = load i32, i32* %call5, align 4, !dbg !3772
  %cmp6 = icmp eq i32 %8, 12, !dbg !3774
  br i1 %cmp6, label %if.then8, label %if.end10, !dbg !3775

if.then8:                                         ; preds = %land.lhs.true
  %9 = load %struct.archive_match*, %struct.archive_match** %a.addr, align 8, !dbg !3777
  %call9 = call i32 @error_nomem(%struct.archive_match* %9), !dbg !3778
  store i32 %call9, i32* %retval, align 4, !dbg !3779
  br label %return, !dbg !3779

if.end10:                                         ; preds = %land.lhs.true, %for.body
  %10 = load i8*, i8** %p, align 8, !dbg !3780
  %cmp11 = icmp ne i8* %10, null, !dbg !3782
  br i1 %cmp11, label %land.lhs.true13, label %if.end18, !dbg !3783

land.lhs.true13:                                  ; preds = %if.end10
  %11 = load i8*, i8** %p, align 8, !dbg !3784
  %12 = load i8*, i8** %name.addr, align 8, !dbg !3786
  %call14 = call i32 @strcmp(i8* %11, i8* %12) #8, !dbg !3787
  %cmp15 = icmp eq i32 %call14, 0, !dbg !3788
  br i1 %cmp15, label %if.then17, label %if.end18, !dbg !3789

if.then17:                                        ; preds = %land.lhs.true13
  %13 = load %struct.match*, %struct.match** %m, align 8, !dbg !3790
  %matches = getelementptr inbounds %struct.match, %struct.match* %13, i32 0, i32 1, !dbg !3792
  %14 = load i32, i32* %matches, align 8, !dbg !3793
  %inc = add nsw i32 %14, 1, !dbg !3793
  store i32 %inc, i32* %matches, align 8, !dbg !3793
  store i32 1, i32* %retval, align 4, !dbg !3794
  br label %return, !dbg !3794

if.end18:                                         ; preds = %land.lhs.true13, %if.end10
  br label %for.inc, !dbg !3795

for.inc:                                          ; preds = %if.end18
  %15 = load %struct.match*, %struct.match** %m, align 8, !dbg !3796
  %next = getelementptr inbounds %struct.match, %struct.match* %15, i32 0, i32 0, !dbg !3798
  %16 = load %struct.match*, %struct.match** %next, align 8, !dbg !3798
  store %struct.match* %16, %struct.match** %m, align 8, !dbg !3799
  br label %for.cond, !dbg !3800

for.end:                                          ; preds = %for.cond
  store i32 0, i32* %retval, align 4, !dbg !3801
  br label %return, !dbg !3801

return:                                           ; preds = %for.end, %if.then17, %if.then8, %if.then
  %17 = load i32, i32* %retval, align 4, !dbg !3802
  ret i32 %17, !dbg !3802
}

declare i8* @archive_entry_uname(%struct.archive_entry*) #3

declare i8* @archive_entry_gname(%struct.archive_entry*) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { argmemonly nounwind }
attributes #7 = { nounwind }
attributes #8 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!390, !391}
!llvm.ident = !{!392}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !220, globals: !387)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_match.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !217, !79, !218, !194, !170, !142, !65, !12}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !5, size: 64, align: 64)
!5 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_match", file: !1, line: 90, size: 4160, align: 64, elements: !6)
!6 = !{!7, !109, !110, !140, !141, !145, !146, !147, !148, !149, !150, !151, !152, !153, !154, !155, !156, !157, !190, !208, !214, !215, !216}
!7 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !5, file: !1, line: 91, baseType: !8, size: 1280, align: 64)
!8 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !9, line: 89, size: 1280, align: 64, elements: !10)
!9 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!10 = !{!11, !13, !14, !82, !83, !84, !85, !86, !87, !88, !89, !97, !98, !99, !100, !103, !104, !105, !106, !107, !108}
!11 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !8, file: !9, line: 96, baseType: !12, size: 32, align: 32)
!12 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!13 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !8, file: !9, line: 97, baseType: !12, size: 32, align: 32, offset: 32)
!14 = !DIDerivedType(tag: DW_TAG_member, name: "vtable", scope: !8, file: !9, line: 103, baseType: !15, size: 64, align: 64, offset: 64)
!15 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !16, size: 64, align: 64)
!16 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_vtable", file: !9, line: 63, size: 832, align: 64, elements: !17)
!17 = !{!18, !24, !25, !32, !33, !47, !53, !58, !59, !66, !67, !71, !75}
!18 = !DIDerivedType(tag: DW_TAG_member, name: "archive_close", scope: !16, file: !9, line: 64, baseType: !19, size: 64, align: 64)
!19 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !20, size: 64, align: 64)
!20 = !DISubroutineType(types: !21)
!21 = !{!22, !23}
!22 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!23 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !8, size: 64, align: 64)
!24 = !DIDerivedType(tag: DW_TAG_member, name: "archive_free", scope: !16, file: !9, line: 65, baseType: !19, size: 64, align: 64, offset: 64)
!25 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_header", scope: !16, file: !9, line: 66, baseType: !26, size: 64, align: 64, offset: 128)
!26 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !27, size: 64, align: 64)
!27 = !DISubroutineType(types: !28)
!28 = !{!22, !23, !29}
!29 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !30, size: 64, align: 64)
!30 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_entry", file: !31, line: 180, flags: DIFlagFwdDecl)
!31 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!32 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_finish_entry", scope: !16, file: !9, line: 68, baseType: !19, size: 64, align: 64, offset: 192)
!33 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data", scope: !16, file: !9, line: 69, baseType: !34, size: 64, align: 64, offset: 256)
!34 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !35, size: 64, align: 64)
!35 = !DISubroutineType(types: !36)
!36 = !{!37, !23, !42, !44}
!37 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !38, line: 109, baseType: !39)
!38 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!39 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !40, line: 172, baseType: !41)
!40 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!41 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!42 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !43, size: 64, align: 64)
!43 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!44 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !45, line: 62, baseType: !46)
!45 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!46 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!47 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data_block", scope: !16, file: !9, line: 71, baseType: !48, size: 64, align: 64, offset: 320)
!48 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !49, size: 64, align: 64)
!49 = !DISubroutineType(types: !50)
!50 = !{!37, !23, !42, !44, !51}
!51 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !52, line: 40, baseType: !41)
!52 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!53 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header", scope: !16, file: !9, line: 74, baseType: !54, size: 64, align: 64, offset: 384)
!54 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !55, size: 64, align: 64)
!55 = !DISubroutineType(types: !56)
!56 = !{!22, !23, !57}
!57 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !29, size: 64, align: 64)
!58 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header2", scope: !16, file: !9, line: 76, baseType: !26, size: 64, align: 64, offset: 448)
!59 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_data_block", scope: !16, file: !9, line: 78, baseType: !60, size: 64, align: 64, offset: 512)
!60 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !61, size: 64, align: 64)
!61 = !DISubroutineType(types: !62)
!62 = !{!22, !23, !63, !64, !65}
!63 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !42, size: 64, align: 64)
!64 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !44, size: 64, align: 64)
!65 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !51, size: 64, align: 64)
!66 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_count", scope: !16, file: !9, line: 81, baseType: !19, size: 64, align: 64, offset: 576)
!67 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_bytes", scope: !16, file: !9, line: 82, baseType: !68, size: 64, align: 64, offset: 640)
!68 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !69, size: 64, align: 64)
!69 = !DISubroutineType(types: !70)
!70 = !{!51, !23, !22}
!71 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_code", scope: !16, file: !9, line: 83, baseType: !72, size: 64, align: 64, offset: 704)
!72 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !73, size: 64, align: 64)
!73 = !DISubroutineType(types: !74)
!74 = !{!22, !23, !22}
!75 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_name", scope: !16, file: !9, line: 84, baseType: !76, size: 64, align: 64, offset: 768)
!76 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !77, size: 64, align: 64)
!77 = !DISubroutineType(types: !78)
!78 = !{!79, !23, !22}
!79 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !80, size: 64, align: 64)
!80 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !81)
!81 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!82 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format", scope: !8, file: !9, line: 105, baseType: !22, size: 32, align: 32, offset: 128)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format_name", scope: !8, file: !9, line: 106, baseType: !79, size: 64, align: 64, offset: 192)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "compression_code", scope: !8, file: !9, line: 108, baseType: !22, size: 32, align: 32, offset: 256)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "compression_name", scope: !8, file: !9, line: 109, baseType: !79, size: 64, align: 64, offset: 320)
!86 = !DIDerivedType(tag: DW_TAG_member, name: "file_count", scope: !8, file: !9, line: 112, baseType: !22, size: 32, align: 32, offset: 384)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "archive_error_number", scope: !8, file: !9, line: 114, baseType: !22, size: 32, align: 32, offset: 416)
!88 = !DIDerivedType(tag: DW_TAG_member, name: "error", scope: !8, file: !9, line: 115, baseType: !79, size: 64, align: 64, offset: 448)
!89 = !DIDerivedType(tag: DW_TAG_member, name: "error_string", scope: !8, file: !9, line: 116, baseType: !90, size: 192, align: 64, offset: 512)
!90 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string", file: !91, line: 58, size: 192, align: 64, elements: !92)
!91 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_string.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!92 = !{!93, !95, !96}
!93 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !90, file: !91, line: 59, baseType: !94, size: 64, align: 64)
!94 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !81, size: 64, align: 64)
!95 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !90, file: !91, line: 60, baseType: !44, size: 64, align: 64, offset: 64)
!96 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !90, file: !91, line: 61, baseType: !44, size: 64, align: 64, offset: 128)
!97 = !DIDerivedType(tag: DW_TAG_member, name: "current_code", scope: !8, file: !9, line: 118, baseType: !94, size: 64, align: 64, offset: 704)
!98 = !DIDerivedType(tag: DW_TAG_member, name: "current_codepage", scope: !8, file: !9, line: 119, baseType: !12, size: 32, align: 32, offset: 768)
!99 = !DIDerivedType(tag: DW_TAG_member, name: "current_oemcp", scope: !8, file: !9, line: 120, baseType: !12, size: 32, align: 32, offset: 800)
!100 = !DIDerivedType(tag: DW_TAG_member, name: "sconv", scope: !8, file: !9, line: 121, baseType: !101, size: 64, align: 64, offset: 832)
!101 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !102, size: 64, align: 64)
!102 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string_conv", file: !91, line: 70, flags: DIFlagFwdDecl)
!103 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_block", scope: !8, file: !9, line: 127, baseType: !79, size: 64, align: 64, offset: 896)
!104 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_offset", scope: !8, file: !9, line: 128, baseType: !51, size: 64, align: 64, offset: 960)
!105 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_output_offset", scope: !8, file: !9, line: 129, baseType: !51, size: 64, align: 64, offset: 1024)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_remaining", scope: !8, file: !9, line: 130, baseType: !44, size: 64, align: 64, offset: 1088)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_is_posix_read", scope: !8, file: !9, line: 137, baseType: !81, size: 8, align: 8, offset: 1152)
!108 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_requested", scope: !8, file: !9, line: 138, baseType: !44, size: 64, align: 64, offset: 1216)
!109 = !DIDerivedType(tag: DW_TAG_member, name: "setflag", scope: !5, file: !1, line: 94, baseType: !22, size: 32, align: 32, offset: 1280)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "exclusions", scope: !5, file: !1, line: 99, baseType: !111, size: 320, align: 64, offset: 1344)
!111 = !DICompositeType(tag: DW_TAG_structure_type, name: "match_list", file: !1, line: 54, size: 320, align: 64, elements: !112)
!112 = !{!113, !134, !136, !137, !138, !139}
!113 = !DIDerivedType(tag: DW_TAG_member, name: "first", scope: !111, file: !1, line: 55, baseType: !114, size: 64, align: 64)
!114 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !115, size: 64, align: 64)
!115 = !DICompositeType(tag: DW_TAG_structure_type, name: "match", file: !1, line: 48, size: 960, align: 64, elements: !116)
!116 = !{!117, !118, !119}
!117 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !115, file: !1, line: 49, baseType: !114, size: 64, align: 64)
!118 = !DIDerivedType(tag: DW_TAG_member, name: "matches", scope: !115, file: !1, line: 50, baseType: !22, size: 32, align: 32, offset: 64)
!119 = !DIDerivedType(tag: DW_TAG_member, name: "pattern", scope: !115, file: !1, line: 51, baseType: !120, size: 832, align: 64, offset: 128)
!120 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_mstring", file: !91, line: 209, size: 832, align: 64, elements: !121)
!121 = !{!122, !123, !124, !132, !133}
!122 = !DIDerivedType(tag: DW_TAG_member, name: "aes_mbs", scope: !120, file: !91, line: 210, baseType: !90, size: 192, align: 64)
!123 = !DIDerivedType(tag: DW_TAG_member, name: "aes_utf8", scope: !120, file: !91, line: 211, baseType: !90, size: 192, align: 64, offset: 192)
!124 = !DIDerivedType(tag: DW_TAG_member, name: "aes_wcs", scope: !120, file: !91, line: 212, baseType: !125, size: 192, align: 64, offset: 384)
!125 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_wstring", file: !91, line: 64, size: 192, align: 64, elements: !126)
!126 = !{!127, !130, !131}
!127 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !125, file: !91, line: 65, baseType: !128, size: 64, align: 64)
!128 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !129, size: 64, align: 64)
!129 = !DIDerivedType(tag: DW_TAG_typedef, name: "wchar_t", file: !45, line: 90, baseType: !22)
!130 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !125, file: !91, line: 66, baseType: !44, size: 64, align: 64, offset: 64)
!131 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !125, file: !91, line: 67, baseType: !44, size: 64, align: 64, offset: 128)
!132 = !DIDerivedType(tag: DW_TAG_member, name: "aes_mbs_in_locale", scope: !120, file: !91, line: 213, baseType: !90, size: 192, align: 64, offset: 576)
!133 = !DIDerivedType(tag: DW_TAG_member, name: "aes_set", scope: !120, file: !91, line: 218, baseType: !22, size: 32, align: 32, offset: 768)
!134 = !DIDerivedType(tag: DW_TAG_member, name: "last", scope: !111, file: !1, line: 56, baseType: !135, size: 64, align: 64, offset: 64)
!135 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !114, size: 64, align: 64)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "count", scope: !111, file: !1, line: 57, baseType: !22, size: 32, align: 32, offset: 128)
!137 = !DIDerivedType(tag: DW_TAG_member, name: "unmatched_count", scope: !111, file: !1, line: 58, baseType: !22, size: 32, align: 32, offset: 160)
!138 = !DIDerivedType(tag: DW_TAG_member, name: "unmatched_next", scope: !111, file: !1, line: 59, baseType: !114, size: 64, align: 64, offset: 192)
!139 = !DIDerivedType(tag: DW_TAG_member, name: "unmatched_eof", scope: !111, file: !1, line: 60, baseType: !22, size: 32, align: 32, offset: 256)
!140 = !DIDerivedType(tag: DW_TAG_member, name: "inclusions", scope: !5, file: !1, line: 100, baseType: !111, size: 320, align: 64, offset: 1664)
!141 = !DIDerivedType(tag: DW_TAG_member, name: "now", scope: !5, file: !1, line: 105, baseType: !142, size: 64, align: 64, offset: 1984)
!142 = !DIDerivedType(tag: DW_TAG_typedef, name: "time_t", file: !143, line: 75, baseType: !144)
!143 = !DIFile(filename: "/usr/include/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!144 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !40, line: 139, baseType: !41)
!145 = !DIDerivedType(tag: DW_TAG_member, name: "newer_mtime_filter", scope: !5, file: !1, line: 106, baseType: !22, size: 32, align: 32, offset: 2048)
!146 = !DIDerivedType(tag: DW_TAG_member, name: "newer_mtime_sec", scope: !5, file: !1, line: 107, baseType: !142, size: 64, align: 64, offset: 2112)
!147 = !DIDerivedType(tag: DW_TAG_member, name: "newer_mtime_nsec", scope: !5, file: !1, line: 108, baseType: !41, size: 64, align: 64, offset: 2176)
!148 = !DIDerivedType(tag: DW_TAG_member, name: "newer_ctime_filter", scope: !5, file: !1, line: 109, baseType: !22, size: 32, align: 32, offset: 2240)
!149 = !DIDerivedType(tag: DW_TAG_member, name: "newer_ctime_sec", scope: !5, file: !1, line: 110, baseType: !142, size: 64, align: 64, offset: 2304)
!150 = !DIDerivedType(tag: DW_TAG_member, name: "newer_ctime_nsec", scope: !5, file: !1, line: 111, baseType: !41, size: 64, align: 64, offset: 2368)
!151 = !DIDerivedType(tag: DW_TAG_member, name: "older_mtime_filter", scope: !5, file: !1, line: 112, baseType: !22, size: 32, align: 32, offset: 2432)
!152 = !DIDerivedType(tag: DW_TAG_member, name: "older_mtime_sec", scope: !5, file: !1, line: 113, baseType: !142, size: 64, align: 64, offset: 2496)
!153 = !DIDerivedType(tag: DW_TAG_member, name: "older_mtime_nsec", scope: !5, file: !1, line: 114, baseType: !41, size: 64, align: 64, offset: 2560)
!154 = !DIDerivedType(tag: DW_TAG_member, name: "older_ctime_filter", scope: !5, file: !1, line: 115, baseType: !22, size: 32, align: 32, offset: 2624)
!155 = !DIDerivedType(tag: DW_TAG_member, name: "older_ctime_sec", scope: !5, file: !1, line: 116, baseType: !142, size: 64, align: 64, offset: 2688)
!156 = !DIDerivedType(tag: DW_TAG_member, name: "older_ctime_nsec", scope: !5, file: !1, line: 117, baseType: !41, size: 64, align: 64, offset: 2752)
!157 = !DIDerivedType(tag: DW_TAG_member, name: "exclusion_tree", scope: !5, file: !1, line: 121, baseType: !158, size: 128, align: 64, offset: 2816)
!158 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_rb_tree", file: !159, line: 80, size: 128, align: 64, elements: !160)
!159 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_rb.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!160 = !{!161, !171}
!161 = !DIDerivedType(tag: DW_TAG_member, name: "rbt_root", scope: !158, file: !159, line: 81, baseType: !162, size: 64, align: 64)
!162 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !163, size: 64, align: 64)
!163 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_rb_node", file: !159, line: 34, size: 192, align: 64, elements: !164)
!164 = !{!165, !169}
!165 = !DIDerivedType(tag: DW_TAG_member, name: "rb_nodes", scope: !163, file: !159, line: 35, baseType: !166, size: 128, align: 64)
!166 = !DICompositeType(tag: DW_TAG_array_type, baseType: !162, size: 128, align: 64, elements: !167)
!167 = !{!168}
!168 = !DISubrange(count: 2)
!169 = !DIDerivedType(tag: DW_TAG_member, name: "rb_info", scope: !163, file: !159, line: 41, baseType: !170, size: 64, align: 64, offset: 128)
!170 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !52, line: 122, baseType: !46)
!171 = !DIDerivedType(tag: DW_TAG_member, name: "rbt_ops", scope: !158, file: !159, line: 82, baseType: !172, size: 64, align: 64, offset: 64)
!172 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !173, size: 64, align: 64)
!173 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !174)
!174 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_rb_tree_ops", file: !159, line: 75, size: 128, align: 64, elements: !175)
!175 = !{!176, !184}
!176 = !DIDerivedType(tag: DW_TAG_member, name: "rbto_compare_nodes", scope: !174, file: !159, line: 76, baseType: !177, size: 64, align: 64)
!177 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_rbto_compare_nodes_fn", file: !159, line: 70, baseType: !178)
!178 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !179)
!179 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !180, size: 64, align: 64)
!180 = !DISubroutineType(types: !181)
!181 = !{!22, !182, !182}
!182 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !183, size: 64, align: 64)
!183 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !163)
!184 = !DIDerivedType(tag: DW_TAG_member, name: "rbto_compare_key", scope: !174, file: !159, line: 77, baseType: !185, size: 64, align: 64, offset: 64)
!185 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_rbto_compare_key_fn", file: !159, line: 72, baseType: !186)
!186 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !187)
!187 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !188, size: 64, align: 64)
!188 = !DISubroutineType(types: !189)
!189 = !{!22, !182, !42}
!190 = !DIDerivedType(tag: DW_TAG_member, name: "exclusion_entry_list", scope: !5, file: !1, line: 122, baseType: !191, size: 192, align: 64, offset: 2944)
!191 = !DICompositeType(tag: DW_TAG_structure_type, name: "entry_list", file: !1, line: 74, size: 192, align: 64, elements: !192)
!192 = !{!193, !205, !207}
!193 = !DIDerivedType(tag: DW_TAG_member, name: "first", scope: !191, file: !1, line: 75, baseType: !194, size: 64, align: 64)
!194 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !195, size: 64, align: 64)
!195 = !DICompositeType(tag: DW_TAG_structure_type, name: "match_file", file: !1, line: 63, size: 1408, align: 64, elements: !196)
!196 = !{!197, !198, !199, !200, !201, !202, !203, !204}
!197 = !DIDerivedType(tag: DW_TAG_member, name: "node", scope: !195, file: !1, line: 64, baseType: !163, size: 192, align: 64)
!198 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !195, file: !1, line: 65, baseType: !194, size: 64, align: 64, offset: 192)
!199 = !DIDerivedType(tag: DW_TAG_member, name: "pathname", scope: !195, file: !1, line: 66, baseType: !120, size: 832, align: 64, offset: 256)
!200 = !DIDerivedType(tag: DW_TAG_member, name: "flag", scope: !195, file: !1, line: 67, baseType: !22, size: 32, align: 32, offset: 1088)
!201 = !DIDerivedType(tag: DW_TAG_member, name: "mtime_sec", scope: !195, file: !1, line: 68, baseType: !142, size: 64, align: 64, offset: 1152)
!202 = !DIDerivedType(tag: DW_TAG_member, name: "mtime_nsec", scope: !195, file: !1, line: 69, baseType: !41, size: 64, align: 64, offset: 1216)
!203 = !DIDerivedType(tag: DW_TAG_member, name: "ctime_sec", scope: !195, file: !1, line: 70, baseType: !142, size: 64, align: 64, offset: 1280)
!204 = !DIDerivedType(tag: DW_TAG_member, name: "ctime_nsec", scope: !195, file: !1, line: 71, baseType: !41, size: 64, align: 64, offset: 1344)
!205 = !DIDerivedType(tag: DW_TAG_member, name: "last", scope: !191, file: !1, line: 76, baseType: !206, size: 64, align: 64, offset: 64)
!206 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !194, size: 64, align: 64)
!207 = !DIDerivedType(tag: DW_TAG_member, name: "count", scope: !191, file: !1, line: 77, baseType: !22, size: 32, align: 32, offset: 128)
!208 = !DIDerivedType(tag: DW_TAG_member, name: "inclusion_uids", scope: !5, file: !1, line: 127, baseType: !209, size: 192, align: 64, offset: 3136)
!209 = !DICompositeType(tag: DW_TAG_structure_type, name: "id_array", file: !1, line: 80, size: 192, align: 64, elements: !210)
!210 = !{!211, !212, !213}
!211 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !209, file: !1, line: 81, baseType: !44, size: 64, align: 64)
!212 = !DIDerivedType(tag: DW_TAG_member, name: "count", scope: !209, file: !1, line: 82, baseType: !44, size: 64, align: 64, offset: 64)
!213 = !DIDerivedType(tag: DW_TAG_member, name: "ids", scope: !209, file: !1, line: 83, baseType: !65, size: 64, align: 64, offset: 128)
!214 = !DIDerivedType(tag: DW_TAG_member, name: "inclusion_gids", scope: !5, file: !1, line: 128, baseType: !209, size: 192, align: 64, offset: 3328)
!215 = !DIDerivedType(tag: DW_TAG_member, name: "inclusion_unames", scope: !5, file: !1, line: 129, baseType: !111, size: 320, align: 64, offset: 3520)
!216 = !DIDerivedType(tag: DW_TAG_member, name: "inclusion_gnames", scope: !5, file: !1, line: 130, baseType: !111, size: 320, align: 64, offset: 3840)
!217 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!218 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !219, size: 64, align: 64)
!219 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !129)
!220 = !{!221, !224, !225, !226, !229, !232, !235, !238, !239, !240, !241, !242, !243, !244, !248, !252, !255, !258, !261, !262, !263, !266, !267, !270, !271, !272, !273, !274, !275, !276, !277, !278, !282, !285, !288, !291, !294, !297, !300, !301, !304, !305, !308, !309, !312, !315, !318, !319, !358, !359, !363, !364, !367, !368, !369, !372, !375, !379, !382, !383, !386}
!221 = distinct !DISubprogram(name: "archive_match_new", scope: !1, file: !1, line: 217, type: !222, isLocal: false, isDefinition: true, scopeLine: 218, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!222 = !DISubroutineType(types: !223)
!223 = !{!23}
!224 = distinct !DISubprogram(name: "archive_match_free", scope: !1, file: !1, line: 240, type: !20, isLocal: false, isDefinition: true, scopeLine: 241, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!225 = distinct !DISubprogram(name: "archive_match_excluded", scope: !1, file: !1, line: 268, type: !27, isLocal: false, isDefinition: true, scopeLine: 269, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!226 = distinct !DISubprogram(name: "archive_match_exclude_pattern", scope: !1, file: !1, line: 309, type: !227, isLocal: false, isDefinition: true, scopeLine: 310, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!227 = !DISubroutineType(types: !228)
!228 = !{!22, !23, !79}
!229 = distinct !DISubprogram(name: "archive_match_exclude_pattern_w", scope: !1, file: !1, line: 328, type: !230, isLocal: false, isDefinition: true, scopeLine: 329, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!230 = !DISubroutineType(types: !231)
!231 = !{!22, !23, !218}
!232 = distinct !DISubprogram(name: "archive_match_exclude_pattern_from_file", scope: !1, file: !1, line: 347, type: !233, isLocal: false, isDefinition: true, scopeLine: 349, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!233 = !DISubroutineType(types: !234)
!234 = !{!22, !23, !79, !22}
!235 = distinct !DISubprogram(name: "archive_match_exclude_pattern_from_file_w", scope: !1, file: !1, line: 361, type: !236, isLocal: false, isDefinition: true, scopeLine: 363, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!236 = !DISubroutineType(types: !237)
!237 = !{!22, !23, !218, !22}
!238 = distinct !DISubprogram(name: "archive_match_include_pattern", scope: !1, file: !1, line: 375, type: !227, isLocal: false, isDefinition: true, scopeLine: 376, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!239 = distinct !DISubprogram(name: "archive_match_include_pattern_w", scope: !1, file: !1, line: 394, type: !230, isLocal: false, isDefinition: true, scopeLine: 395, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!240 = distinct !DISubprogram(name: "archive_match_include_pattern_from_file", scope: !1, file: !1, line: 413, type: !233, isLocal: false, isDefinition: true, scopeLine: 415, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!241 = distinct !DISubprogram(name: "archive_match_include_pattern_from_file_w", scope: !1, file: !1, line: 427, type: !236, isLocal: false, isDefinition: true, scopeLine: 429, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!242 = distinct !DISubprogram(name: "archive_match_path_excluded", scope: !1, file: !1, line: 448, type: !27, isLocal: false, isDefinition: true, scopeLine: 450, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!243 = distinct !DISubprogram(name: "archive_match_path_unmatched_inclusions", scope: !1, file: !1, line: 477, type: !20, isLocal: false, isDefinition: true, scopeLine: 478, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!244 = distinct !DISubprogram(name: "archive_match_path_unmatched_inclusions_next", scope: !1, file: !1, line: 489, type: !245, isLocal: false, isDefinition: true, scopeLine: 491, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!245 = !DISubroutineType(types: !246)
!246 = !{!22, !23, !247}
!247 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !79, size: 64, align: 64)
!248 = distinct !DISubprogram(name: "archive_match_path_unmatched_inclusions_next_w", scope: !1, file: !1, line: 506, type: !249, isLocal: false, isDefinition: true, scopeLine: 508, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!249 = !DISubroutineType(types: !250)
!250 = !{!22, !23, !251}
!251 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !218, size: 64, align: 64)
!252 = distinct !DISubprogram(name: "archive_match_include_time", scope: !1, file: !1, line: 889, type: !253, isLocal: false, isDefinition: true, scopeLine: 891, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!253 = !DISubroutineType(types: !254)
!254 = !{!22, !23, !22, !142, !41}
!255 = distinct !DISubprogram(name: "archive_match_include_date", scope: !1, file: !1, line: 902, type: !256, isLocal: false, isDefinition: true, scopeLine: 904, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!256 = !DISubroutineType(types: !257)
!257 = !{!22, !23, !22, !79}
!258 = distinct !DISubprogram(name: "archive_match_include_date_w", scope: !1, file: !1, line: 914, type: !259, isLocal: false, isDefinition: true, scopeLine: 916, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!259 = !DISubroutineType(types: !260)
!260 = !{!22, !23, !22, !218}
!261 = distinct !DISubprogram(name: "archive_match_include_file_time", scope: !1, file: !1, line: 927, type: !256, isLocal: false, isDefinition: true, scopeLine: 929, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!262 = distinct !DISubprogram(name: "archive_match_include_file_time_w", scope: !1, file: !1, line: 940, type: !259, isLocal: false, isDefinition: true, scopeLine: 942, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!263 = distinct !DISubprogram(name: "archive_match_exclude_entry", scope: !1, file: !1, line: 953, type: !264, isLocal: false, isDefinition: true, scopeLine: 955, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!264 = !DISubroutineType(types: !265)
!265 = !{!22, !23, !22, !29}
!266 = distinct !DISubprogram(name: "archive_match_time_excluded", scope: !1, file: !1, line: 981, type: !27, isLocal: false, isDefinition: true, scopeLine: 983, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!267 = distinct !DISubprogram(name: "archive_match_include_uid", scope: !1, file: !1, line: 1585, type: !268, isLocal: false, isDefinition: true, scopeLine: 1586, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!268 = !DISubroutineType(types: !269)
!269 = !{!22, !23, !51}
!270 = distinct !DISubprogram(name: "archive_match_include_gid", scope: !1, file: !1, line: 1596, type: !268, isLocal: false, isDefinition: true, scopeLine: 1597, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!271 = distinct !DISubprogram(name: "archive_match_include_uname", scope: !1, file: !1, line: 1607, type: !227, isLocal: false, isDefinition: true, scopeLine: 1608, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!272 = distinct !DISubprogram(name: "archive_match_include_uname_w", scope: !1, file: !1, line: 1618, type: !230, isLocal: false, isDefinition: true, scopeLine: 1619, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!273 = distinct !DISubprogram(name: "archive_match_include_gname", scope: !1, file: !1, line: 1629, type: !227, isLocal: false, isDefinition: true, scopeLine: 1630, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!274 = distinct !DISubprogram(name: "archive_match_include_gname_w", scope: !1, file: !1, line: 1640, type: !230, isLocal: false, isDefinition: true, scopeLine: 1641, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!275 = distinct !DISubprogram(name: "archive_match_owner_excluded", scope: !1, file: !1, line: 1658, type: !27, isLocal: false, isDefinition: true, scopeLine: 1660, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!276 = distinct !DISubprogram(name: "cmp_node_mbs", scope: !1, file: !1, line: 1276, type: !180, isLocal: true, isDefinition: true, scopeLine: 1278, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!277 = distinct !DISubprogram(name: "cmp_key_mbs", scope: !1, file: !1, line: 1293, type: !188, isLocal: true, isDefinition: true, scopeLine: 1294, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!278 = distinct !DISubprogram(name: "add_pattern_mbs", scope: !1, file: !1, line: 526, type: !279, isLocal: true, isDefinition: true, scopeLine: 528, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!279 = !DISubroutineType(types: !280)
!280 = !{!22, !4, !281, !79}
!281 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !111, size: 64, align: 64)
!282 = distinct !DISubprogram(name: "error_nomem", scope: !1, file: !1, line: 206, type: !283, isLocal: true, isDefinition: true, scopeLine: 207, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!283 = !DISubroutineType(types: !284)
!284 = !{!22, !4}
!285 = distinct !DISubprogram(name: "match_list_add", scope: !1, file: !1, line: 826, type: !286, isLocal: true, isDefinition: true, scopeLine: 827, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!286 = !DISubroutineType(types: !287)
!287 = !{null, !281, !114}
!288 = distinct !DISubprogram(name: "add_pattern_wcs", scope: !1, file: !1, line: 546, type: !289, isLocal: true, isDefinition: true, scopeLine: 548, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!289 = !DISubroutineType(types: !290)
!290 = !{!22, !4, !281, !218}
!291 = distinct !DISubprogram(name: "add_pattern_from_file", scope: !1, file: !1, line: 566, type: !292, isLocal: true, isDefinition: true, scopeLine: 568, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!292 = !DISubroutineType(types: !293)
!293 = !{!22, !4, !281, !22, !42, !22}
!294 = distinct !DISubprogram(name: "path_excluded", scope: !1, file: !1, line: 685, type: !295, isLocal: true, isDefinition: true, scopeLine: 686, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!295 = !DISubroutineType(types: !296)
!296 = !{!22, !4, !22, !42}
!297 = distinct !DISubprogram(name: "match_path_inclusion", scope: !1, file: !1, line: 781, type: !298, isLocal: true, isDefinition: true, scopeLine: 783, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!298 = !DISubroutineType(types: !299)
!299 = !{!22, !4, !114, !22, !42}
!300 = distinct !DISubprogram(name: "match_path_exclusion", scope: !1, file: !1, line: 753, type: !298, isLocal: true, isDefinition: true, scopeLine: 755, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!301 = distinct !DISubprogram(name: "match_list_init", scope: !1, file: !1, line: 805, type: !302, isLocal: true, isDefinition: true, scopeLine: 806, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!302 = !DISubroutineType(types: !303)
!303 = !{null, !281}
!304 = distinct !DISubprogram(name: "match_list_free", scope: !1, file: !1, line: 813, type: !302, isLocal: true, isDefinition: true, scopeLine: 814, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!305 = distinct !DISubprogram(name: "match_list_unmatched_inclusions_next", scope: !1, file: !1, line: 835, type: !306, isLocal: true, isDefinition: true, scopeLine: 837, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!306 = !DISubroutineType(types: !307)
!307 = !{!22, !4, !281, !22, !63}
!308 = distinct !DISubprogram(name: "validate_time_flag", scope: !1, file: !1, line: 1003, type: !256, isLocal: true, isDefinition: true, scopeLine: 1004, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!309 = distinct !DISubprogram(name: "set_timefilter", scope: !1, file: !1, line: 1038, type: !310, isLocal: true, isDefinition: true, scopeLine: 1040, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!310 = !DISubroutineType(types: !311)
!311 = !{!22, !4, !22, !142, !41, !142, !41}
!312 = distinct !DISubprogram(name: "set_timefilter_date", scope: !1, file: !1, line: 1073, type: !313, isLocal: true, isDefinition: true, scopeLine: 1074, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!313 = !DISubroutineType(types: !314)
!314 = !{!22, !4, !22, !79}
!315 = distinct !DISubprogram(name: "set_timefilter_date_w", scope: !1, file: !1, line: 1090, type: !316, isLocal: true, isDefinition: true, scopeLine: 1092, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!316 = !DISubroutineType(types: !317)
!317 = !{!22, !4, !22, !218}
!318 = distinct !DISubprogram(name: "set_timefilter_pathname_mbs", scope: !1, file: !1, line: 1226, type: !313, isLocal: true, isDefinition: true, scopeLine: 1228, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!319 = distinct !DISubprogram(name: "set_timefilter_stat", scope: !1, file: !1, line: 1206, type: !320, isLocal: true, isDefinition: true, scopeLine: 1207, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!320 = !DISubroutineType(types: !321)
!321 = !{!22, !4, !22, !322}
!322 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !323, size: 64, align: 64)
!323 = !DICompositeType(tag: DW_TAG_structure_type, name: "stat", file: !324, line: 46, size: 1152, align: 64, elements: !325)
!324 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/stat.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!325 = !{!326, !328, !330, !332, !334, !336, !338, !339, !340, !342, !344, !346, !352, !353, !354}
!326 = !DIDerivedType(tag: DW_TAG_member, name: "st_dev", scope: !323, file: !324, line: 48, baseType: !327, size: 64, align: 64)
!327 = !DIDerivedType(tag: DW_TAG_typedef, name: "__dev_t", file: !40, line: 124, baseType: !46)
!328 = !DIDerivedType(tag: DW_TAG_member, name: "st_ino", scope: !323, file: !324, line: 53, baseType: !329, size: 64, align: 64, offset: 64)
!329 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ino_t", file: !40, line: 127, baseType: !46)
!330 = !DIDerivedType(tag: DW_TAG_member, name: "st_nlink", scope: !323, file: !324, line: 61, baseType: !331, size: 64, align: 64, offset: 128)
!331 = !DIDerivedType(tag: DW_TAG_typedef, name: "__nlink_t", file: !40, line: 130, baseType: !46)
!332 = !DIDerivedType(tag: DW_TAG_member, name: "st_mode", scope: !323, file: !324, line: 62, baseType: !333, size: 32, align: 32, offset: 192)
!333 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !40, line: 129, baseType: !12)
!334 = !DIDerivedType(tag: DW_TAG_member, name: "st_uid", scope: !323, file: !324, line: 64, baseType: !335, size: 32, align: 32, offset: 224)
!335 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uid_t", file: !40, line: 125, baseType: !12)
!336 = !DIDerivedType(tag: DW_TAG_member, name: "st_gid", scope: !323, file: !324, line: 65, baseType: !337, size: 32, align: 32, offset: 256)
!337 = !DIDerivedType(tag: DW_TAG_typedef, name: "__gid_t", file: !40, line: 126, baseType: !12)
!338 = !DIDerivedType(tag: DW_TAG_member, name: "__pad0", scope: !323, file: !324, line: 67, baseType: !22, size: 32, align: 32, offset: 288)
!339 = !DIDerivedType(tag: DW_TAG_member, name: "st_rdev", scope: !323, file: !324, line: 69, baseType: !327, size: 64, align: 64, offset: 320)
!340 = !DIDerivedType(tag: DW_TAG_member, name: "st_size", scope: !323, file: !324, line: 74, baseType: !341, size: 64, align: 64, offset: 384)
!341 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off_t", file: !40, line: 131, baseType: !41)
!342 = !DIDerivedType(tag: DW_TAG_member, name: "st_blksize", scope: !323, file: !324, line: 78, baseType: !343, size: 64, align: 64, offset: 448)
!343 = !DIDerivedType(tag: DW_TAG_typedef, name: "__blksize_t", file: !40, line: 153, baseType: !41)
!344 = !DIDerivedType(tag: DW_TAG_member, name: "st_blocks", scope: !323, file: !324, line: 80, baseType: !345, size: 64, align: 64, offset: 512)
!345 = !DIDerivedType(tag: DW_TAG_typedef, name: "__blkcnt_t", file: !40, line: 158, baseType: !41)
!346 = !DIDerivedType(tag: DW_TAG_member, name: "st_atim", scope: !323, file: !324, line: 91, baseType: !347, size: 128, align: 64, offset: 576)
!347 = !DICompositeType(tag: DW_TAG_structure_type, name: "timespec", file: !143, line: 120, size: 128, align: 64, elements: !348)
!348 = !{!349, !350}
!349 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !347, file: !143, line: 122, baseType: !144, size: 64, align: 64)
!350 = !DIDerivedType(tag: DW_TAG_member, name: "tv_nsec", scope: !347, file: !143, line: 123, baseType: !351, size: 64, align: 64, offset: 64)
!351 = !DIDerivedType(tag: DW_TAG_typedef, name: "__syscall_slong_t", file: !40, line: 175, baseType: !41)
!352 = !DIDerivedType(tag: DW_TAG_member, name: "st_mtim", scope: !323, file: !324, line: 92, baseType: !347, size: 128, align: 64, offset: 704)
!353 = !DIDerivedType(tag: DW_TAG_member, name: "st_ctim", scope: !323, file: !324, line: 93, baseType: !347, size: 128, align: 64, offset: 832)
!354 = !DIDerivedType(tag: DW_TAG_member, name: "__glibc_reserved", scope: !323, file: !324, line: 106, baseType: !355, size: 192, align: 64, offset: 960)
!355 = !DICompositeType(tag: DW_TAG_array_type, baseType: !351, size: 192, align: 64, elements: !356)
!356 = !{!357}
!357 = !DISubrange(count: 3)
!358 = distinct !DISubprogram(name: "set_timefilter_pathname_wcs", scope: !1, file: !1, line: 1243, type: !316, isLocal: true, isDefinition: true, scopeLine: 1245, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!359 = distinct !DISubprogram(name: "entry_list_init", scope: !1, file: !1, line: 1334, type: !360, isLocal: true, isDefinition: true, scopeLine: 1335, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!360 = !DISubroutineType(types: !361)
!361 = !{null, !362}
!362 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !191, size: 64, align: 64)
!363 = distinct !DISubprogram(name: "entry_list_free", scope: !1, file: !1, line: 1342, type: !360, isLocal: true, isDefinition: true, scopeLine: 1343, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!364 = distinct !DISubprogram(name: "add_entry", scope: !1, file: !1, line: 1363, type: !365, isLocal: true, isDefinition: true, scopeLine: 1365, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!365 = !DISubroutineType(types: !366)
!366 = !{!22, !4, !22, !29}
!367 = distinct !DISubprogram(name: "cmp_node_wcs", scope: !1, file: !1, line: 1305, type: !180, isLocal: true, isDefinition: true, scopeLine: 1307, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!368 = distinct !DISubprogram(name: "cmp_key_wcs", scope: !1, file: !1, line: 1322, type: !188, isLocal: true, isDefinition: true, scopeLine: 1323, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!369 = distinct !DISubprogram(name: "entry_list_add", scope: !1, file: !1, line: 1355, type: !370, isLocal: true, isDefinition: true, scopeLine: 1356, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!370 = !DISubroutineType(types: !371)
!371 = !{null, !362, !194}
!372 = distinct !DISubprogram(name: "time_excluded", scope: !1, file: !1, line: 1435, type: !373, isLocal: true, isDefinition: true, scopeLine: 1436, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!373 = !DISubroutineType(types: !374)
!374 = !{!22, !4, !29}
!375 = distinct !DISubprogram(name: "add_owner_id", scope: !1, file: !1, line: 1680, type: !376, isLocal: true, isDefinition: true, scopeLine: 1681, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!376 = !DISubroutineType(types: !377)
!377 = !{!22, !4, !378, !51}
!378 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !209, size: 64, align: 64)
!379 = distinct !DISubprogram(name: "add_owner_name", scope: !1, file: !1, line: 1736, type: !380, isLocal: true, isDefinition: true, scopeLine: 1738, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!380 = !DISubroutineType(types: !381)
!381 = !{!22, !4, !281, !22, !42}
!382 = distinct !DISubprogram(name: "owner_excluded", scope: !1, file: !1, line: 1801, type: !373, isLocal: true, isDefinition: true, scopeLine: 1802, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!383 = distinct !DISubprogram(name: "match_owner_id", scope: !1, file: !1, line: 1717, type: !384, isLocal: true, isDefinition: true, scopeLine: 1718, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!384 = !DISubroutineType(types: !385)
!385 = !{!22, !378, !51}
!386 = distinct !DISubprogram(name: "match_owner_name_mbs", scope: !1, file: !1, line: 1755, type: !279, isLocal: true, isDefinition: true, scopeLine: 1757, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!387 = !{!388, !389}
!388 = !DIGlobalVariable(name: "rb_ops_mbs", scope: !0, file: !1, line: 190, type: !173, isLocal: true, isDefinition: true, variable: %struct.archive_rb_tree_ops* @rb_ops_mbs)
!389 = !DIGlobalVariable(name: "rb_ops_wcs", scope: !0, file: !1, line: 194, type: !173, isLocal: true, isDefinition: true, variable: %struct.archive_rb_tree_ops* @rb_ops_wcs)
!390 = !{i32 2, !"Dwarf Version", i32 4}
!391 = !{i32 2, !"Debug Info Version", i32 3}
!392 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!393 = !DILocalVariable(name: "a", scope: !221, file: !1, line: 219, type: !4)
!394 = !DIExpression()
!395 = !DILocation(line: 219, column: 24, scope: !221)
!396 = !DILocation(line: 221, column: 30, scope: !221)
!397 = !DILocation(line: 221, column: 6, scope: !221)
!398 = !DILocation(line: 221, column: 4, scope: !221)
!399 = !DILocation(line: 222, column: 6, scope: !400)
!400 = distinct !DILexicalBlock(scope: !221, file: !1, line: 222, column: 6)
!401 = !DILocation(line: 222, column: 8, scope: !400)
!402 = !DILocation(line: 222, column: 6, scope: !221)
!403 = !DILocation(line: 223, column: 3, scope: !400)
!404 = !DILocation(line: 224, column: 2, scope: !221)
!405 = !DILocation(line: 224, column: 5, scope: !221)
!406 = !DILocation(line: 224, column: 13, scope: !221)
!407 = !DILocation(line: 224, column: 19, scope: !221)
!408 = !DILocation(line: 225, column: 2, scope: !221)
!409 = !DILocation(line: 225, column: 5, scope: !221)
!410 = !DILocation(line: 225, column: 13, scope: !221)
!411 = !DILocation(line: 225, column: 19, scope: !221)
!412 = !DILocation(line: 226, column: 20, scope: !221)
!413 = !DILocation(line: 226, column: 23, scope: !221)
!414 = !DILocation(line: 226, column: 2, scope: !221)
!415 = !DILocation(line: 227, column: 20, scope: !221)
!416 = !DILocation(line: 227, column: 23, scope: !221)
!417 = !DILocation(line: 227, column: 2, scope: !221)
!418 = !DILocation(line: 228, column: 27, scope: !221)
!419 = !DILocation(line: 228, column: 30, scope: !221)
!420 = !DILocation(line: 228, column: 2, scope: !221)
!421 = !DILocation(line: 229, column: 20, scope: !221)
!422 = !DILocation(line: 229, column: 23, scope: !221)
!423 = !DILocation(line: 229, column: 2, scope: !221)
!424 = !DILocation(line: 230, column: 20, scope: !221)
!425 = !DILocation(line: 230, column: 23, scope: !221)
!426 = !DILocation(line: 230, column: 2, scope: !221)
!427 = !DILocation(line: 231, column: 20, scope: !221)
!428 = !DILocation(line: 231, column: 23, scope: !221)
!429 = !DILocation(line: 231, column: 2, scope: !221)
!430 = !DILocation(line: 232, column: 8, scope: !221)
!431 = !DILocation(line: 232, column: 11, scope: !221)
!432 = !DILocation(line: 232, column: 2, scope: !221)
!433 = !DILocation(line: 233, column: 12, scope: !221)
!434 = !DILocation(line: 233, column: 15, scope: !221)
!435 = !DILocation(line: 233, column: 2, scope: !221)
!436 = !DILocation(line: 234, column: 1, scope: !221)
!437 = !DILocalVariable(name: "list", arg: 1, scope: !301, file: !1, line: 805, type: !281)
!438 = !DILocation(line: 805, column: 36, scope: !301)
!439 = !DILocation(line: 807, column: 2, scope: !301)
!440 = !DILocation(line: 807, column: 8, scope: !301)
!441 = !DILocation(line: 807, column: 14, scope: !301)
!442 = !DILocation(line: 808, column: 17, scope: !301)
!443 = !DILocation(line: 808, column: 23, scope: !301)
!444 = !DILocation(line: 808, column: 2, scope: !301)
!445 = !DILocation(line: 808, column: 8, scope: !301)
!446 = !DILocation(line: 808, column: 13, scope: !301)
!447 = !DILocation(line: 809, column: 2, scope: !301)
!448 = !DILocation(line: 809, column: 8, scope: !301)
!449 = !DILocation(line: 809, column: 14, scope: !301)
!450 = !DILocation(line: 810, column: 1, scope: !301)
!451 = !DILocalVariable(name: "list", arg: 1, scope: !359, file: !1, line: 1334, type: !362)
!452 = !DILocation(line: 1334, column: 36, scope: !359)
!453 = !DILocation(line: 1336, column: 2, scope: !359)
!454 = !DILocation(line: 1336, column: 8, scope: !359)
!455 = !DILocation(line: 1336, column: 14, scope: !359)
!456 = !DILocation(line: 1337, column: 17, scope: !359)
!457 = !DILocation(line: 1337, column: 23, scope: !359)
!458 = !DILocation(line: 1337, column: 2, scope: !359)
!459 = !DILocation(line: 1337, column: 8, scope: !359)
!460 = !DILocation(line: 1337, column: 13, scope: !359)
!461 = !DILocation(line: 1338, column: 2, scope: !359)
!462 = !DILocation(line: 1338, column: 8, scope: !359)
!463 = !DILocation(line: 1338, column: 14, scope: !359)
!464 = !DILocation(line: 1339, column: 1, scope: !359)
!465 = !DILocalVariable(name: "_a", arg: 1, scope: !224, file: !1, line: 240, type: !23)
!466 = !DILocation(line: 240, column: 36, scope: !224)
!467 = !DILocalVariable(name: "a", scope: !224, file: !1, line: 242, type: !4)
!468 = !DILocation(line: 242, column: 24, scope: !224)
!469 = !DILocation(line: 244, column: 6, scope: !470)
!470 = distinct !DILexicalBlock(scope: !224, file: !1, line: 244, column: 6)
!471 = !DILocation(line: 244, column: 9, scope: !470)
!472 = !DILocation(line: 244, column: 6, scope: !224)
!473 = !DILocation(line: 245, column: 3, scope: !470)
!474 = !DILocation(line: 246, column: 2, scope: !224)
!475 = !DILocalVariable(name: "magic_test", scope: !476, file: !1, line: 246, type: !22)
!476 = distinct !DILexicalBlock(scope: !224, file: !1, line: 246, column: 2)
!477 = !DILocation(line: 246, column: 2, scope: !476)
!478 = !DILocation(line: 246, column: 2, scope: !479)
!479 = !DILexicalBlockFile(scope: !476, file: !1, discriminator: 1)
!480 = !DILocation(line: 246, column: 2, scope: !481)
!481 = !DILexicalBlockFile(scope: !482, file: !1, discriminator: 2)
!482 = distinct !DILexicalBlock(scope: !476, file: !1, line: 246, column: 2)
!483 = !DILocation(line: 246, column: 2, scope: !484)
!484 = !DILexicalBlockFile(scope: !476, file: !1, discriminator: 3)
!485 = !DILocation(line: 248, column: 30, scope: !224)
!486 = !DILocation(line: 248, column: 6, scope: !224)
!487 = !DILocation(line: 248, column: 4, scope: !224)
!488 = !DILocation(line: 249, column: 20, scope: !224)
!489 = !DILocation(line: 249, column: 23, scope: !224)
!490 = !DILocation(line: 249, column: 2, scope: !224)
!491 = !DILocation(line: 250, column: 20, scope: !224)
!492 = !DILocation(line: 250, column: 23, scope: !224)
!493 = !DILocation(line: 250, column: 2, scope: !224)
!494 = !DILocation(line: 251, column: 20, scope: !224)
!495 = !DILocation(line: 251, column: 23, scope: !224)
!496 = !DILocation(line: 251, column: 2, scope: !224)
!497 = !DILocation(line: 252, column: 7, scope: !224)
!498 = !DILocation(line: 252, column: 10, scope: !224)
!499 = !DILocation(line: 252, column: 25, scope: !224)
!500 = !DILocation(line: 252, column: 2, scope: !224)
!501 = !DILocation(line: 253, column: 7, scope: !224)
!502 = !DILocation(line: 253, column: 10, scope: !224)
!503 = !DILocation(line: 253, column: 25, scope: !224)
!504 = !DILocation(line: 253, column: 2, scope: !224)
!505 = !DILocation(line: 254, column: 20, scope: !224)
!506 = !DILocation(line: 254, column: 23, scope: !224)
!507 = !DILocation(line: 254, column: 2, scope: !224)
!508 = !DILocation(line: 255, column: 20, scope: !224)
!509 = !DILocation(line: 255, column: 23, scope: !224)
!510 = !DILocation(line: 255, column: 2, scope: !224)
!511 = !DILocation(line: 256, column: 7, scope: !224)
!512 = !DILocation(line: 256, column: 2, scope: !224)
!513 = !DILocation(line: 257, column: 2, scope: !224)
!514 = !DILocation(line: 258, column: 1, scope: !224)
!515 = !DILocalVariable(name: "list", arg: 1, scope: !304, file: !1, line: 813, type: !281)
!516 = !DILocation(line: 813, column: 36, scope: !304)
!517 = !DILocalVariable(name: "p", scope: !304, file: !1, line: 815, type: !114)
!518 = !DILocation(line: 815, column: 16, scope: !304)
!519 = !DILocalVariable(name: "q", scope: !304, file: !1, line: 815, type: !114)
!520 = !DILocation(line: 815, column: 20, scope: !304)
!521 = !DILocation(line: 817, column: 11, scope: !522)
!522 = distinct !DILexicalBlock(scope: !304, file: !1, line: 817, column: 2)
!523 = !DILocation(line: 817, column: 17, scope: !522)
!524 = !DILocation(line: 817, column: 9, scope: !522)
!525 = !DILocation(line: 817, column: 7, scope: !522)
!526 = !DILocation(line: 817, column: 24, scope: !527)
!527 = !DILexicalBlockFile(scope: !528, file: !1, discriminator: 1)
!528 = distinct !DILexicalBlock(scope: !522, file: !1, line: 817, column: 2)
!529 = !DILocation(line: 817, column: 26, scope: !527)
!530 = !DILocation(line: 817, column: 2, scope: !527)
!531 = !DILocation(line: 818, column: 7, scope: !532)
!532 = distinct !DILexicalBlock(scope: !528, file: !1, line: 817, column: 37)
!533 = !DILocation(line: 818, column: 5, scope: !532)
!534 = !DILocation(line: 819, column: 7, scope: !532)
!535 = !DILocation(line: 819, column: 10, scope: !532)
!536 = !DILocation(line: 819, column: 5, scope: !532)
!537 = !DILocation(line: 820, column: 27, scope: !532)
!538 = !DILocation(line: 820, column: 30, scope: !532)
!539 = !DILocation(line: 820, column: 3, scope: !532)
!540 = !DILocation(line: 821, column: 8, scope: !532)
!541 = !DILocation(line: 821, column: 3, scope: !532)
!542 = !DILocation(line: 817, column: 2, scope: !543)
!543 = !DILexicalBlockFile(scope: !528, file: !1, discriminator: 2)
!544 = !DILocation(line: 823, column: 1, scope: !304)
!545 = !DILocalVariable(name: "list", arg: 1, scope: !363, file: !1, line: 1342, type: !362)
!546 = !DILocation(line: 1342, column: 36, scope: !363)
!547 = !DILocalVariable(name: "p", scope: !363, file: !1, line: 1344, type: !194)
!548 = !DILocation(line: 1344, column: 21, scope: !363)
!549 = !DILocalVariable(name: "q", scope: !363, file: !1, line: 1344, type: !194)
!550 = !DILocation(line: 1344, column: 25, scope: !363)
!551 = !DILocation(line: 1346, column: 11, scope: !552)
!552 = distinct !DILexicalBlock(scope: !363, file: !1, line: 1346, column: 2)
!553 = !DILocation(line: 1346, column: 17, scope: !552)
!554 = !DILocation(line: 1346, column: 9, scope: !552)
!555 = !DILocation(line: 1346, column: 7, scope: !552)
!556 = !DILocation(line: 1346, column: 24, scope: !557)
!557 = !DILexicalBlockFile(scope: !558, file: !1, discriminator: 1)
!558 = distinct !DILexicalBlock(scope: !552, file: !1, line: 1346, column: 2)
!559 = !DILocation(line: 1346, column: 26, scope: !557)
!560 = !DILocation(line: 1346, column: 2, scope: !557)
!561 = !DILocation(line: 1347, column: 7, scope: !562)
!562 = distinct !DILexicalBlock(scope: !558, file: !1, line: 1346, column: 37)
!563 = !DILocation(line: 1347, column: 5, scope: !562)
!564 = !DILocation(line: 1348, column: 7, scope: !562)
!565 = !DILocation(line: 1348, column: 10, scope: !562)
!566 = !DILocation(line: 1348, column: 5, scope: !562)
!567 = !DILocation(line: 1349, column: 27, scope: !562)
!568 = !DILocation(line: 1349, column: 30, scope: !562)
!569 = !DILocation(line: 1349, column: 3, scope: !562)
!570 = !DILocation(line: 1350, column: 8, scope: !562)
!571 = !DILocation(line: 1350, column: 3, scope: !562)
!572 = !DILocation(line: 1346, column: 2, scope: !573)
!573 = !DILexicalBlockFile(scope: !558, file: !1, discriminator: 2)
!574 = !DILocation(line: 1352, column: 1, scope: !363)
!575 = !DILocalVariable(name: "_a", arg: 1, scope: !225, file: !1, line: 268, type: !23)
!576 = !DILocation(line: 268, column: 40, scope: !225)
!577 = !DILocalVariable(name: "entry", arg: 2, scope: !225, file: !1, line: 268, type: !29)
!578 = !DILocation(line: 268, column: 66, scope: !225)
!579 = !DILocalVariable(name: "a", scope: !225, file: !1, line: 270, type: !4)
!580 = !DILocation(line: 270, column: 24, scope: !225)
!581 = !DILocalVariable(name: "r", scope: !225, file: !1, line: 271, type: !22)
!582 = !DILocation(line: 271, column: 6, scope: !225)
!583 = !DILocation(line: 273, column: 2, scope: !225)
!584 = !DILocalVariable(name: "magic_test", scope: !585, file: !1, line: 273, type: !22)
!585 = distinct !DILexicalBlock(scope: !225, file: !1, line: 273, column: 2)
!586 = !DILocation(line: 273, column: 2, scope: !585)
!587 = !DILocation(line: 273, column: 2, scope: !588)
!588 = !DILexicalBlockFile(scope: !585, file: !1, discriminator: 1)
!589 = !DILocation(line: 273, column: 2, scope: !590)
!590 = !DILexicalBlockFile(scope: !591, file: !1, discriminator: 2)
!591 = distinct !DILexicalBlock(scope: !585, file: !1, line: 273, column: 2)
!592 = !DILocation(line: 273, column: 2, scope: !593)
!593 = !DILexicalBlockFile(scope: !585, file: !1, discriminator: 3)
!594 = !DILocation(line: 276, column: 30, scope: !225)
!595 = !DILocation(line: 276, column: 6, scope: !225)
!596 = !DILocation(line: 276, column: 4, scope: !225)
!597 = !DILocation(line: 277, column: 6, scope: !598)
!598 = distinct !DILexicalBlock(scope: !225, file: !1, line: 277, column: 6)
!599 = !DILocation(line: 277, column: 12, scope: !598)
!600 = !DILocation(line: 277, column: 6, scope: !225)
!601 = !DILocation(line: 278, column: 23, scope: !602)
!602 = distinct !DILexicalBlock(scope: !598, file: !1, line: 277, column: 21)
!603 = !DILocation(line: 278, column: 26, scope: !602)
!604 = !DILocation(line: 278, column: 3, scope: !602)
!605 = !DILocation(line: 279, column: 3, scope: !602)
!606 = !DILocation(line: 282, column: 4, scope: !225)
!607 = !DILocation(line: 283, column: 6, scope: !608)
!608 = distinct !DILexicalBlock(scope: !225, file: !1, line: 283, column: 6)
!609 = !DILocation(line: 283, column: 9, scope: !608)
!610 = !DILocation(line: 283, column: 17, scope: !608)
!611 = !DILocation(line: 283, column: 6, scope: !225)
!612 = !DILocation(line: 287, column: 21, scope: !613)
!613 = distinct !DILexicalBlock(scope: !608, file: !1, line: 283, column: 35)
!614 = !DILocation(line: 287, column: 50, scope: !613)
!615 = !DILocation(line: 287, column: 27, scope: !613)
!616 = !DILocation(line: 287, column: 7, scope: !617)
!617 = !DILexicalBlockFile(scope: !613, file: !1, discriminator: 1)
!618 = !DILocation(line: 287, column: 5, scope: !613)
!619 = !DILocation(line: 289, column: 7, scope: !620)
!620 = distinct !DILexicalBlock(scope: !613, file: !1, line: 289, column: 7)
!621 = !DILocation(line: 289, column: 9, scope: !620)
!622 = !DILocation(line: 289, column: 7, scope: !613)
!623 = !DILocation(line: 290, column: 12, scope: !620)
!624 = !DILocation(line: 290, column: 4, scope: !620)
!625 = !DILocation(line: 291, column: 2, scope: !613)
!626 = !DILocation(line: 293, column: 6, scope: !627)
!627 = distinct !DILexicalBlock(scope: !225, file: !1, line: 293, column: 6)
!628 = !DILocation(line: 293, column: 9, scope: !627)
!629 = !DILocation(line: 293, column: 17, scope: !627)
!630 = !DILocation(line: 293, column: 6, scope: !225)
!631 = !DILocation(line: 294, column: 21, scope: !632)
!632 = distinct !DILexicalBlock(scope: !627, file: !1, line: 293, column: 32)
!633 = !DILocation(line: 294, column: 24, scope: !632)
!634 = !DILocation(line: 294, column: 7, scope: !632)
!635 = !DILocation(line: 294, column: 5, scope: !632)
!636 = !DILocation(line: 295, column: 7, scope: !637)
!637 = distinct !DILexicalBlock(scope: !632, file: !1, line: 295, column: 7)
!638 = !DILocation(line: 295, column: 9, scope: !637)
!639 = !DILocation(line: 295, column: 7, scope: !632)
!640 = !DILocation(line: 296, column: 12, scope: !637)
!641 = !DILocation(line: 296, column: 4, scope: !637)
!642 = !DILocation(line: 297, column: 2, scope: !632)
!643 = !DILocation(line: 299, column: 6, scope: !644)
!644 = distinct !DILexicalBlock(scope: !225, file: !1, line: 299, column: 6)
!645 = !DILocation(line: 299, column: 9, scope: !644)
!646 = !DILocation(line: 299, column: 17, scope: !644)
!647 = !DILocation(line: 299, column: 6, scope: !225)
!648 = !DILocation(line: 300, column: 22, scope: !644)
!649 = !DILocation(line: 300, column: 25, scope: !644)
!650 = !DILocation(line: 300, column: 7, scope: !644)
!651 = !DILocation(line: 300, column: 5, scope: !644)
!652 = !DILocation(line: 300, column: 3, scope: !644)
!653 = !DILocation(line: 301, column: 10, scope: !225)
!654 = !DILocation(line: 301, column: 2, scope: !225)
!655 = !DILocation(line: 302, column: 1, scope: !225)
!656 = !DILocalVariable(name: "a", arg: 1, scope: !294, file: !1, line: 685, type: !4)
!657 = !DILocation(line: 685, column: 37, scope: !294)
!658 = !DILocalVariable(name: "mbs", arg: 2, scope: !294, file: !1, line: 685, type: !22)
!659 = !DILocation(line: 685, column: 44, scope: !294)
!660 = !DILocalVariable(name: "pathname", arg: 3, scope: !294, file: !1, line: 685, type: !42)
!661 = !DILocation(line: 685, column: 61, scope: !294)
!662 = !DILocalVariable(name: "match", scope: !294, file: !1, line: 687, type: !114)
!663 = !DILocation(line: 687, column: 16, scope: !294)
!664 = !DILocalVariable(name: "matched", scope: !294, file: !1, line: 688, type: !114)
!665 = !DILocation(line: 688, column: 16, scope: !294)
!666 = !DILocalVariable(name: "r", scope: !294, file: !1, line: 689, type: !22)
!667 = !DILocation(line: 689, column: 6, scope: !294)
!668 = !DILocation(line: 691, column: 6, scope: !669)
!669 = distinct !DILexicalBlock(scope: !294, file: !1, line: 691, column: 6)
!670 = !DILocation(line: 691, column: 8, scope: !669)
!671 = !DILocation(line: 691, column: 6, scope: !294)
!672 = !DILocation(line: 692, column: 3, scope: !669)
!673 = !DILocation(line: 699, column: 10, scope: !294)
!674 = !DILocation(line: 700, column: 15, scope: !675)
!675 = distinct !DILexicalBlock(scope: !294, file: !1, line: 700, column: 2)
!676 = !DILocation(line: 700, column: 18, scope: !675)
!677 = !DILocation(line: 700, column: 29, scope: !675)
!678 = !DILocation(line: 700, column: 13, scope: !675)
!679 = !DILocation(line: 700, column: 7, scope: !675)
!680 = !DILocation(line: 700, column: 36, scope: !681)
!681 = !DILexicalBlockFile(scope: !682, file: !1, discriminator: 1)
!682 = distinct !DILexicalBlock(scope: !675, file: !1, line: 700, column: 2)
!683 = !DILocation(line: 700, column: 42, scope: !681)
!684 = !DILocation(line: 700, column: 2, scope: !681)
!685 = !DILocation(line: 702, column: 7, scope: !686)
!686 = distinct !DILexicalBlock(scope: !687, file: !1, line: 702, column: 7)
!687 = distinct !DILexicalBlock(scope: !682, file: !1, line: 701, column: 26)
!688 = !DILocation(line: 702, column: 14, scope: !686)
!689 = !DILocation(line: 702, column: 22, scope: !686)
!690 = !DILocation(line: 702, column: 27, scope: !686)
!691 = !DILocation(line: 703, column: 33, scope: !686)
!692 = !DILocation(line: 703, column: 36, scope: !686)
!693 = !DILocation(line: 703, column: 43, scope: !686)
!694 = !DILocation(line: 703, column: 48, scope: !686)
!695 = !DILocation(line: 703, column: 12, scope: !686)
!696 = !DILocation(line: 703, column: 10, scope: !686)
!697 = !DILocation(line: 703, column: 59, scope: !686)
!698 = !DILocation(line: 702, column: 7, scope: !699)
!699 = !DILexicalBlockFile(scope: !687, file: !1, discriminator: 1)
!700 = !DILocation(line: 704, column: 8, scope: !701)
!701 = distinct !DILexicalBlock(scope: !702, file: !1, line: 704, column: 8)
!702 = distinct !DILexicalBlock(scope: !686, file: !1, line: 703, column: 65)
!703 = !DILocation(line: 704, column: 10, scope: !701)
!704 = !DILocation(line: 704, column: 8, scope: !702)
!705 = !DILocation(line: 705, column: 13, scope: !701)
!706 = !DILocation(line: 705, column: 5, scope: !701)
!707 = !DILocation(line: 706, column: 4, scope: !702)
!708 = !DILocation(line: 706, column: 7, scope: !702)
!709 = !DILocation(line: 706, column: 18, scope: !702)
!710 = !DILocation(line: 706, column: 33, scope: !702)
!711 = !DILocation(line: 707, column: 4, scope: !702)
!712 = !DILocation(line: 707, column: 11, scope: !702)
!713 = !DILocation(line: 707, column: 18, scope: !702)
!714 = !DILocation(line: 708, column: 14, scope: !702)
!715 = !DILocation(line: 708, column: 12, scope: !702)
!716 = !DILocation(line: 709, column: 3, scope: !702)
!717 = !DILocation(line: 710, column: 2, scope: !687)
!718 = !DILocation(line: 701, column: 14, scope: !682)
!719 = !DILocation(line: 701, column: 21, scope: !682)
!720 = !DILocation(line: 701, column: 12, scope: !682)
!721 = !DILocation(line: 700, column: 2, scope: !722)
!722 = !DILexicalBlockFile(scope: !682, file: !1, discriminator: 2)
!723 = !DILocation(line: 713, column: 15, scope: !724)
!724 = distinct !DILexicalBlock(scope: !294, file: !1, line: 713, column: 2)
!725 = !DILocation(line: 713, column: 18, scope: !724)
!726 = !DILocation(line: 713, column: 29, scope: !724)
!727 = !DILocation(line: 713, column: 13, scope: !724)
!728 = !DILocation(line: 713, column: 7, scope: !724)
!729 = !DILocation(line: 713, column: 36, scope: !730)
!730 = !DILexicalBlockFile(scope: !731, file: !1, discriminator: 1)
!731 = distinct !DILexicalBlock(scope: !724, file: !1, line: 713, column: 2)
!732 = !DILocation(line: 713, column: 42, scope: !730)
!733 = !DILocation(line: 713, column: 2, scope: !730)
!734 = !DILocation(line: 715, column: 28, scope: !735)
!735 = distinct !DILexicalBlock(scope: !731, file: !1, line: 714, column: 26)
!736 = !DILocation(line: 715, column: 31, scope: !735)
!737 = !DILocation(line: 715, column: 38, scope: !735)
!738 = !DILocation(line: 715, column: 43, scope: !735)
!739 = !DILocation(line: 715, column: 7, scope: !735)
!740 = !DILocation(line: 715, column: 5, scope: !735)
!741 = !DILocation(line: 716, column: 7, scope: !742)
!742 = distinct !DILexicalBlock(scope: !735, file: !1, line: 716, column: 7)
!743 = !DILocation(line: 716, column: 7, scope: !735)
!744 = !DILocation(line: 717, column: 12, scope: !742)
!745 = !DILocation(line: 717, column: 4, scope: !742)
!746 = !DILocation(line: 718, column: 2, scope: !735)
!747 = !DILocation(line: 714, column: 14, scope: !731)
!748 = !DILocation(line: 714, column: 21, scope: !731)
!749 = !DILocation(line: 714, column: 12, scope: !731)
!750 = !DILocation(line: 713, column: 2, scope: !751)
!751 = !DILexicalBlockFile(scope: !731, file: !1, discriminator: 2)
!752 = !DILocation(line: 722, column: 6, scope: !753)
!753 = distinct !DILexicalBlock(scope: !294, file: !1, line: 722, column: 6)
!754 = !DILocation(line: 722, column: 14, scope: !753)
!755 = !DILocation(line: 722, column: 6, scope: !294)
!756 = !DILocation(line: 723, column: 3, scope: !753)
!757 = !DILocation(line: 727, column: 15, scope: !758)
!758 = distinct !DILexicalBlock(scope: !294, file: !1, line: 727, column: 2)
!759 = !DILocation(line: 727, column: 18, scope: !758)
!760 = !DILocation(line: 727, column: 29, scope: !758)
!761 = !DILocation(line: 727, column: 13, scope: !758)
!762 = !DILocation(line: 727, column: 7, scope: !758)
!763 = !DILocation(line: 727, column: 36, scope: !764)
!764 = !DILexicalBlockFile(scope: !765, file: !1, discriminator: 1)
!765 = distinct !DILexicalBlock(scope: !758, file: !1, line: 727, column: 2)
!766 = !DILocation(line: 727, column: 42, scope: !764)
!767 = !DILocation(line: 727, column: 2, scope: !764)
!768 = !DILocation(line: 730, column: 7, scope: !769)
!769 = distinct !DILexicalBlock(scope: !770, file: !1, line: 730, column: 7)
!770 = distinct !DILexicalBlock(scope: !765, file: !1, line: 728, column: 26)
!771 = !DILocation(line: 730, column: 14, scope: !769)
!772 = !DILocation(line: 730, column: 22, scope: !769)
!773 = !DILocation(line: 730, column: 26, scope: !769)
!774 = !DILocation(line: 731, column: 33, scope: !769)
!775 = !DILocation(line: 731, column: 36, scope: !769)
!776 = !DILocation(line: 731, column: 43, scope: !769)
!777 = !DILocation(line: 731, column: 48, scope: !769)
!778 = !DILocation(line: 731, column: 12, scope: !769)
!779 = !DILocation(line: 731, column: 10, scope: !769)
!780 = !DILocation(line: 731, column: 59, scope: !769)
!781 = !DILocation(line: 730, column: 7, scope: !782)
!782 = !DILexicalBlockFile(scope: !770, file: !1, discriminator: 1)
!783 = !DILocation(line: 732, column: 8, scope: !784)
!784 = distinct !DILexicalBlock(scope: !785, file: !1, line: 732, column: 8)
!785 = distinct !DILexicalBlock(scope: !769, file: !1, line: 731, column: 65)
!786 = !DILocation(line: 732, column: 10, scope: !784)
!787 = !DILocation(line: 732, column: 8, scope: !785)
!788 = !DILocation(line: 733, column: 13, scope: !784)
!789 = !DILocation(line: 733, column: 5, scope: !784)
!790 = !DILocation(line: 734, column: 4, scope: !785)
!791 = !DILocation(line: 734, column: 11, scope: !785)
!792 = !DILocation(line: 734, column: 18, scope: !785)
!793 = !DILocation(line: 735, column: 4, scope: !785)
!794 = !DILocation(line: 737, column: 2, scope: !770)
!795 = !DILocation(line: 728, column: 14, scope: !765)
!796 = !DILocation(line: 728, column: 21, scope: !765)
!797 = !DILocation(line: 728, column: 12, scope: !765)
!798 = !DILocation(line: 727, column: 2, scope: !799)
!799 = !DILexicalBlockFile(scope: !765, file: !1, discriminator: 2)
!800 = !DILocation(line: 740, column: 6, scope: !801)
!801 = distinct !DILexicalBlock(scope: !294, file: !1, line: 740, column: 6)
!802 = !DILocation(line: 740, column: 9, scope: !801)
!803 = !DILocation(line: 740, column: 20, scope: !801)
!804 = !DILocation(line: 740, column: 26, scope: !801)
!805 = !DILocation(line: 740, column: 6, scope: !294)
!806 = !DILocation(line: 741, column: 6, scope: !801)
!807 = !DILocation(line: 744, column: 2, scope: !294)
!808 = !DILocation(line: 745, column: 1, scope: !294)
!809 = !DILocalVariable(name: "a", arg: 1, scope: !372, file: !1, line: 1435, type: !4)
!810 = !DILocation(line: 1435, column: 37, scope: !372)
!811 = !DILocalVariable(name: "entry", arg: 2, scope: !372, file: !1, line: 1435, type: !29)
!812 = !DILocation(line: 1435, column: 62, scope: !372)
!813 = !DILocalVariable(name: "f", scope: !372, file: !1, line: 1437, type: !194)
!814 = !DILocation(line: 1437, column: 21, scope: !372)
!815 = !DILocalVariable(name: "pathname", scope: !372, file: !1, line: 1438, type: !42)
!816 = !DILocation(line: 1438, column: 14, scope: !372)
!817 = !DILocalVariable(name: "sec", scope: !372, file: !1, line: 1439, type: !142)
!818 = !DILocation(line: 1439, column: 9, scope: !372)
!819 = !DILocalVariable(name: "nsec", scope: !372, file: !1, line: 1440, type: !41)
!820 = !DILocation(line: 1440, column: 7, scope: !372)
!821 = !DILocation(line: 1445, column: 6, scope: !822)
!822 = distinct !DILexicalBlock(scope: !372, file: !1, line: 1445, column: 6)
!823 = !DILocation(line: 1445, column: 9, scope: !822)
!824 = !DILocation(line: 1445, column: 6, scope: !372)
!825 = !DILocation(line: 1447, column: 34, scope: !826)
!826 = distinct !DILexicalBlock(scope: !827, file: !1, line: 1447, column: 7)
!827 = distinct !DILexicalBlock(scope: !822, file: !1, line: 1445, column: 29)
!828 = !DILocation(line: 1447, column: 7, scope: !826)
!829 = !DILocation(line: 1447, column: 7, scope: !827)
!830 = !DILocation(line: 1448, column: 30, scope: !826)
!831 = !DILocation(line: 1448, column: 10, scope: !826)
!832 = !DILocation(line: 1448, column: 8, scope: !826)
!833 = !DILocation(line: 1448, column: 4, scope: !826)
!834 = !DILocation(line: 1450, column: 30, scope: !826)
!835 = !DILocation(line: 1450, column: 10, scope: !826)
!836 = !DILocation(line: 1450, column: 8, scope: !826)
!837 = !DILocation(line: 1451, column: 7, scope: !838)
!838 = distinct !DILexicalBlock(scope: !827, file: !1, line: 1451, column: 7)
!839 = !DILocation(line: 1451, column: 13, scope: !838)
!840 = !DILocation(line: 1451, column: 16, scope: !838)
!841 = !DILocation(line: 1451, column: 11, scope: !838)
!842 = !DILocation(line: 1451, column: 7, scope: !827)
!843 = !DILocation(line: 1452, column: 4, scope: !838)
!844 = !DILocation(line: 1453, column: 7, scope: !845)
!845 = distinct !DILexicalBlock(scope: !827, file: !1, line: 1453, column: 7)
!846 = !DILocation(line: 1453, column: 14, scope: !845)
!847 = !DILocation(line: 1453, column: 17, scope: !845)
!848 = !DILocation(line: 1453, column: 11, scope: !845)
!849 = !DILocation(line: 1453, column: 7, scope: !827)
!850 = !DILocation(line: 1454, column: 35, scope: !851)
!851 = distinct !DILexicalBlock(scope: !852, file: !1, line: 1454, column: 8)
!852 = distinct !DILexicalBlock(scope: !845, file: !1, line: 1453, column: 34)
!853 = !DILocation(line: 1454, column: 8, scope: !851)
!854 = !DILocation(line: 1454, column: 8, scope: !852)
!855 = !DILocation(line: 1455, column: 37, scope: !851)
!856 = !DILocation(line: 1455, column: 12, scope: !851)
!857 = !DILocation(line: 1455, column: 10, scope: !851)
!858 = !DILocation(line: 1455, column: 5, scope: !851)
!859 = !DILocation(line: 1457, column: 37, scope: !851)
!860 = !DILocation(line: 1457, column: 12, scope: !851)
!861 = !DILocation(line: 1457, column: 10, scope: !851)
!862 = !DILocation(line: 1458, column: 8, scope: !863)
!863 = distinct !DILexicalBlock(scope: !852, file: !1, line: 1458, column: 8)
!864 = !DILocation(line: 1458, column: 15, scope: !863)
!865 = !DILocation(line: 1458, column: 18, scope: !863)
!866 = !DILocation(line: 1458, column: 13, scope: !863)
!867 = !DILocation(line: 1458, column: 8, scope: !852)
!868 = !DILocation(line: 1459, column: 5, scope: !863)
!869 = !DILocation(line: 1460, column: 8, scope: !870)
!870 = distinct !DILexicalBlock(scope: !852, file: !1, line: 1460, column: 8)
!871 = !DILocation(line: 1460, column: 16, scope: !870)
!872 = !DILocation(line: 1460, column: 19, scope: !870)
!873 = !DILocation(line: 1460, column: 13, scope: !870)
!874 = !DILocation(line: 1460, column: 36, scope: !870)
!875 = !DILocation(line: 1461, column: 9, scope: !870)
!876 = !DILocation(line: 1461, column: 12, scope: !870)
!877 = !DILocation(line: 1461, column: 31, scope: !870)
!878 = !DILocation(line: 1462, column: 10, scope: !870)
!879 = !DILocation(line: 1460, column: 8, scope: !880)
!880 = !DILexicalBlockFile(scope: !852, file: !1, discriminator: 1)
!881 = !DILocation(line: 1463, column: 5, scope: !870)
!882 = !DILocation(line: 1464, column: 3, scope: !852)
!883 = !DILocation(line: 1465, column: 2, scope: !827)
!884 = !DILocation(line: 1466, column: 6, scope: !885)
!885 = distinct !DILexicalBlock(scope: !372, file: !1, line: 1466, column: 6)
!886 = !DILocation(line: 1466, column: 9, scope: !885)
!887 = !DILocation(line: 1466, column: 6, scope: !372)
!888 = !DILocation(line: 1468, column: 34, scope: !889)
!889 = distinct !DILexicalBlock(scope: !890, file: !1, line: 1468, column: 7)
!890 = distinct !DILexicalBlock(scope: !885, file: !1, line: 1466, column: 29)
!891 = !DILocation(line: 1468, column: 7, scope: !889)
!892 = !DILocation(line: 1468, column: 7, scope: !890)
!893 = !DILocation(line: 1469, column: 30, scope: !889)
!894 = !DILocation(line: 1469, column: 10, scope: !889)
!895 = !DILocation(line: 1469, column: 8, scope: !889)
!896 = !DILocation(line: 1469, column: 4, scope: !889)
!897 = !DILocation(line: 1471, column: 30, scope: !889)
!898 = !DILocation(line: 1471, column: 10, scope: !889)
!899 = !DILocation(line: 1471, column: 8, scope: !889)
!900 = !DILocation(line: 1472, column: 7, scope: !901)
!901 = distinct !DILexicalBlock(scope: !890, file: !1, line: 1472, column: 7)
!902 = !DILocation(line: 1472, column: 13, scope: !901)
!903 = !DILocation(line: 1472, column: 16, scope: !901)
!904 = !DILocation(line: 1472, column: 11, scope: !901)
!905 = !DILocation(line: 1472, column: 7, scope: !890)
!906 = !DILocation(line: 1473, column: 4, scope: !901)
!907 = !DILocation(line: 1474, column: 7, scope: !908)
!908 = distinct !DILexicalBlock(scope: !890, file: !1, line: 1474, column: 7)
!909 = !DILocation(line: 1474, column: 14, scope: !908)
!910 = !DILocation(line: 1474, column: 17, scope: !908)
!911 = !DILocation(line: 1474, column: 11, scope: !908)
!912 = !DILocation(line: 1474, column: 7, scope: !890)
!913 = !DILocation(line: 1475, column: 35, scope: !914)
!914 = distinct !DILexicalBlock(scope: !915, file: !1, line: 1475, column: 8)
!915 = distinct !DILexicalBlock(scope: !908, file: !1, line: 1474, column: 34)
!916 = !DILocation(line: 1475, column: 8, scope: !914)
!917 = !DILocation(line: 1475, column: 8, scope: !915)
!918 = !DILocation(line: 1476, column: 37, scope: !914)
!919 = !DILocation(line: 1476, column: 12, scope: !914)
!920 = !DILocation(line: 1476, column: 10, scope: !914)
!921 = !DILocation(line: 1476, column: 5, scope: !914)
!922 = !DILocation(line: 1478, column: 37, scope: !914)
!923 = !DILocation(line: 1478, column: 12, scope: !914)
!924 = !DILocation(line: 1478, column: 10, scope: !914)
!925 = !DILocation(line: 1479, column: 8, scope: !926)
!926 = distinct !DILexicalBlock(scope: !915, file: !1, line: 1479, column: 8)
!927 = !DILocation(line: 1479, column: 15, scope: !926)
!928 = !DILocation(line: 1479, column: 18, scope: !926)
!929 = !DILocation(line: 1479, column: 13, scope: !926)
!930 = !DILocation(line: 1479, column: 8, scope: !915)
!931 = !DILocation(line: 1480, column: 5, scope: !926)
!932 = !DILocation(line: 1481, column: 8, scope: !933)
!933 = distinct !DILexicalBlock(scope: !915, file: !1, line: 1481, column: 8)
!934 = !DILocation(line: 1481, column: 16, scope: !933)
!935 = !DILocation(line: 1481, column: 19, scope: !933)
!936 = !DILocation(line: 1481, column: 13, scope: !933)
!937 = !DILocation(line: 1481, column: 36, scope: !933)
!938 = !DILocation(line: 1482, column: 9, scope: !933)
!939 = !DILocation(line: 1482, column: 12, scope: !933)
!940 = !DILocation(line: 1482, column: 31, scope: !933)
!941 = !DILocation(line: 1483, column: 10, scope: !933)
!942 = !DILocation(line: 1481, column: 8, scope: !943)
!943 = !DILexicalBlockFile(scope: !915, file: !1, discriminator: 1)
!944 = !DILocation(line: 1484, column: 5, scope: !933)
!945 = !DILocation(line: 1485, column: 3, scope: !915)
!946 = !DILocation(line: 1486, column: 2, scope: !890)
!947 = !DILocation(line: 1487, column: 6, scope: !948)
!948 = distinct !DILexicalBlock(scope: !372, file: !1, line: 1487, column: 6)
!949 = !DILocation(line: 1487, column: 9, scope: !948)
!950 = !DILocation(line: 1487, column: 6, scope: !372)
!951 = !DILocation(line: 1488, column: 29, scope: !952)
!952 = distinct !DILexicalBlock(scope: !948, file: !1, line: 1487, column: 29)
!953 = !DILocation(line: 1488, column: 9, scope: !952)
!954 = !DILocation(line: 1488, column: 7, scope: !952)
!955 = !DILocation(line: 1489, column: 7, scope: !956)
!956 = distinct !DILexicalBlock(scope: !952, file: !1, line: 1489, column: 7)
!957 = !DILocation(line: 1489, column: 13, scope: !956)
!958 = !DILocation(line: 1489, column: 16, scope: !956)
!959 = !DILocation(line: 1489, column: 11, scope: !956)
!960 = !DILocation(line: 1489, column: 7, scope: !952)
!961 = !DILocation(line: 1490, column: 4, scope: !956)
!962 = !DILocation(line: 1491, column: 7, scope: !963)
!963 = distinct !DILexicalBlock(scope: !952, file: !1, line: 1491, column: 7)
!964 = !DILocation(line: 1491, column: 14, scope: !963)
!965 = !DILocation(line: 1491, column: 17, scope: !963)
!966 = !DILocation(line: 1491, column: 11, scope: !963)
!967 = !DILocation(line: 1491, column: 7, scope: !952)
!968 = !DILocation(line: 1492, column: 36, scope: !969)
!969 = distinct !DILexicalBlock(scope: !963, file: !1, line: 1491, column: 34)
!970 = !DILocation(line: 1492, column: 11, scope: !969)
!971 = !DILocation(line: 1492, column: 9, scope: !969)
!972 = !DILocation(line: 1493, column: 8, scope: !973)
!973 = distinct !DILexicalBlock(scope: !969, file: !1, line: 1493, column: 8)
!974 = !DILocation(line: 1493, column: 15, scope: !973)
!975 = !DILocation(line: 1493, column: 18, scope: !973)
!976 = !DILocation(line: 1493, column: 13, scope: !973)
!977 = !DILocation(line: 1493, column: 8, scope: !969)
!978 = !DILocation(line: 1494, column: 5, scope: !973)
!979 = !DILocation(line: 1495, column: 8, scope: !980)
!980 = distinct !DILexicalBlock(scope: !969, file: !1, line: 1495, column: 8)
!981 = !DILocation(line: 1495, column: 16, scope: !980)
!982 = !DILocation(line: 1495, column: 19, scope: !980)
!983 = !DILocation(line: 1495, column: 13, scope: !980)
!984 = !DILocation(line: 1495, column: 36, scope: !980)
!985 = !DILocation(line: 1496, column: 9, scope: !980)
!986 = !DILocation(line: 1496, column: 12, scope: !980)
!987 = !DILocation(line: 1496, column: 31, scope: !980)
!988 = !DILocation(line: 1497, column: 11, scope: !980)
!989 = !DILocation(line: 1495, column: 8, scope: !990)
!990 = !DILexicalBlockFile(scope: !969, file: !1, discriminator: 1)
!991 = !DILocation(line: 1498, column: 5, scope: !980)
!992 = !DILocation(line: 1499, column: 3, scope: !969)
!993 = !DILocation(line: 1500, column: 2, scope: !952)
!994 = !DILocation(line: 1501, column: 6, scope: !995)
!995 = distinct !DILexicalBlock(scope: !372, file: !1, line: 1501, column: 6)
!996 = !DILocation(line: 1501, column: 9, scope: !995)
!997 = !DILocation(line: 1501, column: 6, scope: !372)
!998 = !DILocation(line: 1502, column: 29, scope: !999)
!999 = distinct !DILexicalBlock(scope: !995, file: !1, line: 1501, column: 29)
!1000 = !DILocation(line: 1502, column: 9, scope: !999)
!1001 = !DILocation(line: 1502, column: 7, scope: !999)
!1002 = !DILocation(line: 1503, column: 7, scope: !1003)
!1003 = distinct !DILexicalBlock(scope: !999, file: !1, line: 1503, column: 7)
!1004 = !DILocation(line: 1503, column: 13, scope: !1003)
!1005 = !DILocation(line: 1503, column: 16, scope: !1003)
!1006 = !DILocation(line: 1503, column: 11, scope: !1003)
!1007 = !DILocation(line: 1503, column: 7, scope: !999)
!1008 = !DILocation(line: 1504, column: 4, scope: !1003)
!1009 = !DILocation(line: 1505, column: 35, scope: !999)
!1010 = !DILocation(line: 1505, column: 10, scope: !999)
!1011 = !DILocation(line: 1505, column: 8, scope: !999)
!1012 = !DILocation(line: 1506, column: 7, scope: !1013)
!1013 = distinct !DILexicalBlock(scope: !999, file: !1, line: 1506, column: 7)
!1014 = !DILocation(line: 1506, column: 14, scope: !1013)
!1015 = !DILocation(line: 1506, column: 17, scope: !1013)
!1016 = !DILocation(line: 1506, column: 11, scope: !1013)
!1017 = !DILocation(line: 1506, column: 7, scope: !999)
!1018 = !DILocation(line: 1507, column: 8, scope: !1019)
!1019 = distinct !DILexicalBlock(scope: !1020, file: !1, line: 1507, column: 8)
!1020 = distinct !DILexicalBlock(scope: !1013, file: !1, line: 1506, column: 34)
!1021 = !DILocation(line: 1507, column: 15, scope: !1019)
!1022 = !DILocation(line: 1507, column: 18, scope: !1019)
!1023 = !DILocation(line: 1507, column: 13, scope: !1019)
!1024 = !DILocation(line: 1507, column: 8, scope: !1020)
!1025 = !DILocation(line: 1508, column: 5, scope: !1019)
!1026 = !DILocation(line: 1509, column: 8, scope: !1027)
!1027 = distinct !DILexicalBlock(scope: !1020, file: !1, line: 1509, column: 8)
!1028 = !DILocation(line: 1509, column: 16, scope: !1027)
!1029 = !DILocation(line: 1509, column: 19, scope: !1027)
!1030 = !DILocation(line: 1509, column: 13, scope: !1027)
!1031 = !DILocation(line: 1509, column: 36, scope: !1027)
!1032 = !DILocation(line: 1510, column: 9, scope: !1027)
!1033 = !DILocation(line: 1510, column: 12, scope: !1027)
!1034 = !DILocation(line: 1510, column: 31, scope: !1027)
!1035 = !DILocation(line: 1511, column: 11, scope: !1027)
!1036 = !DILocation(line: 1509, column: 8, scope: !1037)
!1037 = !DILexicalBlockFile(scope: !1020, file: !1, discriminator: 1)
!1038 = !DILocation(line: 1512, column: 5, scope: !1027)
!1039 = !DILocation(line: 1513, column: 3, scope: !1020)
!1040 = !DILocation(line: 1514, column: 2, scope: !999)
!1041 = !DILocation(line: 1517, column: 6, scope: !1042)
!1042 = distinct !DILexicalBlock(scope: !372, file: !1, line: 1517, column: 6)
!1043 = !DILocation(line: 1517, column: 9, scope: !1042)
!1044 = !DILocation(line: 1517, column: 30, scope: !1042)
!1045 = !DILocation(line: 1517, column: 36, scope: !1042)
!1046 = !DILocation(line: 1517, column: 6, scope: !372)
!1047 = !DILocation(line: 1518, column: 3, scope: !1042)
!1048 = !DILocation(line: 1525, column: 36, scope: !372)
!1049 = !DILocation(line: 1525, column: 13, scope: !372)
!1050 = !DILocation(line: 1525, column: 11, scope: !372)
!1051 = !DILocation(line: 1526, column: 2, scope: !372)
!1052 = !DILocation(line: 1526, column: 5, scope: !372)
!1053 = !DILocation(line: 1526, column: 20, scope: !372)
!1054 = !DILocation(line: 1526, column: 28, scope: !372)
!1055 = !DILocation(line: 1528, column: 6, scope: !1056)
!1056 = distinct !DILexicalBlock(scope: !372, file: !1, line: 1528, column: 6)
!1057 = !DILocation(line: 1528, column: 15, scope: !1056)
!1058 = !DILocation(line: 1528, column: 6, scope: !372)
!1059 = !DILocation(line: 1529, column: 3, scope: !1056)
!1060 = !DILocation(line: 1532, column: 5, scope: !372)
!1061 = !DILocation(line: 1532, column: 8, scope: !372)
!1062 = !DILocation(line: 1532, column: 25, scope: !372)
!1063 = !DILocation(line: 1531, column: 27, scope: !372)
!1064 = !DILocation(line: 1531, column: 6, scope: !372)
!1065 = !DILocation(line: 1531, column: 4, scope: !372)
!1066 = !DILocation(line: 1534, column: 6, scope: !1067)
!1067 = distinct !DILexicalBlock(scope: !372, file: !1, line: 1534, column: 6)
!1068 = !DILocation(line: 1534, column: 8, scope: !1067)
!1069 = !DILocation(line: 1534, column: 6, scope: !372)
!1070 = !DILocation(line: 1535, column: 3, scope: !1067)
!1071 = !DILocation(line: 1537, column: 6, scope: !1072)
!1072 = distinct !DILexicalBlock(scope: !372, file: !1, line: 1537, column: 6)
!1073 = !DILocation(line: 1537, column: 9, scope: !1072)
!1074 = !DILocation(line: 1537, column: 14, scope: !1072)
!1075 = !DILocation(line: 1537, column: 6, scope: !372)
!1076 = !DILocation(line: 1538, column: 29, scope: !1077)
!1077 = distinct !DILexicalBlock(scope: !1072, file: !1, line: 1537, column: 37)
!1078 = !DILocation(line: 1538, column: 9, scope: !1077)
!1079 = !DILocation(line: 1538, column: 7, scope: !1077)
!1080 = !DILocation(line: 1539, column: 7, scope: !1081)
!1081 = distinct !DILexicalBlock(scope: !1077, file: !1, line: 1539, column: 7)
!1082 = !DILocation(line: 1539, column: 10, scope: !1081)
!1083 = !DILocation(line: 1539, column: 22, scope: !1081)
!1084 = !DILocation(line: 1539, column: 20, scope: !1081)
!1085 = !DILocation(line: 1539, column: 7, scope: !1077)
!1086 = !DILocation(line: 1540, column: 8, scope: !1087)
!1087 = distinct !DILexicalBlock(scope: !1088, file: !1, line: 1540, column: 8)
!1088 = distinct !DILexicalBlock(scope: !1081, file: !1, line: 1539, column: 27)
!1089 = !DILocation(line: 1540, column: 11, scope: !1087)
!1090 = !DILocation(line: 1540, column: 16, scope: !1087)
!1091 = !DILocation(line: 1540, column: 8, scope: !1088)
!1092 = !DILocation(line: 1541, column: 5, scope: !1087)
!1093 = !DILocation(line: 1542, column: 3, scope: !1088)
!1094 = !DILocation(line: 1542, column: 14, scope: !1095)
!1095 = !DILexicalBlockFile(scope: !1096, file: !1, discriminator: 1)
!1096 = distinct !DILexicalBlock(scope: !1081, file: !1, line: 1542, column: 14)
!1097 = !DILocation(line: 1542, column: 17, scope: !1095)
!1098 = !DILocation(line: 1542, column: 29, scope: !1095)
!1099 = !DILocation(line: 1542, column: 27, scope: !1095)
!1100 = !DILocation(line: 1543, column: 8, scope: !1101)
!1101 = distinct !DILexicalBlock(scope: !1102, file: !1, line: 1543, column: 8)
!1102 = distinct !DILexicalBlock(scope: !1096, file: !1, line: 1542, column: 34)
!1103 = !DILocation(line: 1543, column: 11, scope: !1101)
!1104 = !DILocation(line: 1543, column: 16, scope: !1101)
!1105 = !DILocation(line: 1543, column: 8, scope: !1102)
!1106 = !DILocation(line: 1544, column: 5, scope: !1101)
!1107 = !DILocation(line: 1545, column: 3, scope: !1102)
!1108 = !DILocation(line: 1546, column: 36, scope: !1109)
!1109 = distinct !DILexicalBlock(scope: !1096, file: !1, line: 1545, column: 10)
!1110 = !DILocation(line: 1546, column: 11, scope: !1109)
!1111 = !DILocation(line: 1546, column: 9, scope: !1109)
!1112 = !DILocation(line: 1547, column: 8, scope: !1113)
!1113 = distinct !DILexicalBlock(scope: !1109, file: !1, line: 1547, column: 8)
!1114 = !DILocation(line: 1547, column: 11, scope: !1113)
!1115 = !DILocation(line: 1547, column: 24, scope: !1113)
!1116 = !DILocation(line: 1547, column: 22, scope: !1113)
!1117 = !DILocation(line: 1547, column: 8, scope: !1109)
!1118 = !DILocation(line: 1548, column: 9, scope: !1119)
!1119 = distinct !DILexicalBlock(scope: !1120, file: !1, line: 1548, column: 9)
!1120 = distinct !DILexicalBlock(scope: !1113, file: !1, line: 1547, column: 30)
!1121 = !DILocation(line: 1548, column: 12, scope: !1119)
!1122 = !DILocation(line: 1548, column: 17, scope: !1119)
!1123 = !DILocation(line: 1548, column: 9, scope: !1120)
!1124 = !DILocation(line: 1549, column: 6, scope: !1119)
!1125 = !DILocation(line: 1550, column: 4, scope: !1120)
!1126 = !DILocation(line: 1550, column: 15, scope: !1127)
!1127 = !DILexicalBlockFile(scope: !1128, file: !1, discriminator: 1)
!1128 = distinct !DILexicalBlock(scope: !1113, file: !1, line: 1550, column: 15)
!1129 = !DILocation(line: 1550, column: 18, scope: !1127)
!1130 = !DILocation(line: 1550, column: 31, scope: !1127)
!1131 = !DILocation(line: 1550, column: 29, scope: !1127)
!1132 = !DILocation(line: 1551, column: 9, scope: !1133)
!1133 = distinct !DILexicalBlock(scope: !1134, file: !1, line: 1551, column: 9)
!1134 = distinct !DILexicalBlock(scope: !1128, file: !1, line: 1550, column: 37)
!1135 = !DILocation(line: 1551, column: 12, scope: !1133)
!1136 = !DILocation(line: 1551, column: 17, scope: !1133)
!1137 = !DILocation(line: 1551, column: 9, scope: !1134)
!1138 = !DILocation(line: 1552, column: 6, scope: !1133)
!1139 = !DILocation(line: 1553, column: 4, scope: !1134)
!1140 = !DILocation(line: 1553, column: 15, scope: !1141)
!1141 = !DILexicalBlockFile(scope: !1142, file: !1, discriminator: 1)
!1142 = distinct !DILexicalBlock(scope: !1128, file: !1, line: 1553, column: 15)
!1143 = !DILocation(line: 1553, column: 18, scope: !1141)
!1144 = !DILocation(line: 1553, column: 23, scope: !1141)
!1145 = !DILocation(line: 1554, column: 5, scope: !1142)
!1146 = !DILocation(line: 1556, column: 2, scope: !1077)
!1147 = !DILocation(line: 1557, column: 6, scope: !1148)
!1148 = distinct !DILexicalBlock(scope: !372, file: !1, line: 1557, column: 6)
!1149 = !DILocation(line: 1557, column: 9, scope: !1148)
!1150 = !DILocation(line: 1557, column: 14, scope: !1148)
!1151 = !DILocation(line: 1557, column: 6, scope: !372)
!1152 = !DILocation(line: 1558, column: 29, scope: !1153)
!1153 = distinct !DILexicalBlock(scope: !1148, file: !1, line: 1557, column: 37)
!1154 = !DILocation(line: 1558, column: 9, scope: !1153)
!1155 = !DILocation(line: 1558, column: 7, scope: !1153)
!1156 = !DILocation(line: 1559, column: 7, scope: !1157)
!1157 = distinct !DILexicalBlock(scope: !1153, file: !1, line: 1559, column: 7)
!1158 = !DILocation(line: 1559, column: 10, scope: !1157)
!1159 = !DILocation(line: 1559, column: 22, scope: !1157)
!1160 = !DILocation(line: 1559, column: 20, scope: !1157)
!1161 = !DILocation(line: 1559, column: 7, scope: !1153)
!1162 = !DILocation(line: 1560, column: 8, scope: !1163)
!1163 = distinct !DILexicalBlock(scope: !1164, file: !1, line: 1560, column: 8)
!1164 = distinct !DILexicalBlock(scope: !1157, file: !1, line: 1559, column: 27)
!1165 = !DILocation(line: 1560, column: 11, scope: !1163)
!1166 = !DILocation(line: 1560, column: 16, scope: !1163)
!1167 = !DILocation(line: 1560, column: 8, scope: !1164)
!1168 = !DILocation(line: 1561, column: 5, scope: !1163)
!1169 = !DILocation(line: 1562, column: 3, scope: !1164)
!1170 = !DILocation(line: 1562, column: 14, scope: !1171)
!1171 = !DILexicalBlockFile(scope: !1172, file: !1, discriminator: 1)
!1172 = distinct !DILexicalBlock(scope: !1157, file: !1, line: 1562, column: 14)
!1173 = !DILocation(line: 1562, column: 17, scope: !1171)
!1174 = !DILocation(line: 1562, column: 29, scope: !1171)
!1175 = !DILocation(line: 1562, column: 27, scope: !1171)
!1176 = !DILocation(line: 1563, column: 8, scope: !1177)
!1177 = distinct !DILexicalBlock(scope: !1178, file: !1, line: 1563, column: 8)
!1178 = distinct !DILexicalBlock(scope: !1172, file: !1, line: 1562, column: 34)
!1179 = !DILocation(line: 1563, column: 11, scope: !1177)
!1180 = !DILocation(line: 1563, column: 16, scope: !1177)
!1181 = !DILocation(line: 1563, column: 8, scope: !1178)
!1182 = !DILocation(line: 1564, column: 5, scope: !1177)
!1183 = !DILocation(line: 1565, column: 3, scope: !1178)
!1184 = !DILocation(line: 1566, column: 36, scope: !1185)
!1185 = distinct !DILexicalBlock(scope: !1172, file: !1, line: 1565, column: 10)
!1186 = !DILocation(line: 1566, column: 11, scope: !1185)
!1187 = !DILocation(line: 1566, column: 9, scope: !1185)
!1188 = !DILocation(line: 1567, column: 8, scope: !1189)
!1189 = distinct !DILexicalBlock(scope: !1185, file: !1, line: 1567, column: 8)
!1190 = !DILocation(line: 1567, column: 11, scope: !1189)
!1191 = !DILocation(line: 1567, column: 24, scope: !1189)
!1192 = !DILocation(line: 1567, column: 22, scope: !1189)
!1193 = !DILocation(line: 1567, column: 8, scope: !1185)
!1194 = !DILocation(line: 1568, column: 9, scope: !1195)
!1195 = distinct !DILexicalBlock(scope: !1196, file: !1, line: 1568, column: 9)
!1196 = distinct !DILexicalBlock(scope: !1189, file: !1, line: 1567, column: 30)
!1197 = !DILocation(line: 1568, column: 12, scope: !1195)
!1198 = !DILocation(line: 1568, column: 17, scope: !1195)
!1199 = !DILocation(line: 1568, column: 9, scope: !1196)
!1200 = !DILocation(line: 1569, column: 6, scope: !1195)
!1201 = !DILocation(line: 1570, column: 4, scope: !1196)
!1202 = !DILocation(line: 1570, column: 15, scope: !1203)
!1203 = !DILexicalBlockFile(scope: !1204, file: !1, discriminator: 1)
!1204 = distinct !DILexicalBlock(scope: !1189, file: !1, line: 1570, column: 15)
!1205 = !DILocation(line: 1570, column: 18, scope: !1203)
!1206 = !DILocation(line: 1570, column: 31, scope: !1203)
!1207 = !DILocation(line: 1570, column: 29, scope: !1203)
!1208 = !DILocation(line: 1571, column: 9, scope: !1209)
!1209 = distinct !DILexicalBlock(scope: !1210, file: !1, line: 1571, column: 9)
!1210 = distinct !DILexicalBlock(scope: !1204, file: !1, line: 1570, column: 37)
!1211 = !DILocation(line: 1571, column: 12, scope: !1209)
!1212 = !DILocation(line: 1571, column: 17, scope: !1209)
!1213 = !DILocation(line: 1571, column: 9, scope: !1210)
!1214 = !DILocation(line: 1572, column: 6, scope: !1209)
!1215 = !DILocation(line: 1573, column: 4, scope: !1210)
!1216 = !DILocation(line: 1573, column: 15, scope: !1217)
!1217 = !DILexicalBlockFile(scope: !1218, file: !1, discriminator: 1)
!1218 = distinct !DILexicalBlock(scope: !1204, file: !1, line: 1573, column: 15)
!1219 = !DILocation(line: 1573, column: 18, scope: !1217)
!1220 = !DILocation(line: 1573, column: 23, scope: !1217)
!1221 = !DILocation(line: 1574, column: 5, scope: !1218)
!1222 = !DILocation(line: 1576, column: 2, scope: !1153)
!1223 = !DILocation(line: 1577, column: 2, scope: !372)
!1224 = !DILocation(line: 1578, column: 1, scope: !372)
!1225 = !DILocalVariable(name: "a", arg: 1, scope: !382, file: !1, line: 1801, type: !4)
!1226 = !DILocation(line: 1801, column: 38, scope: !382)
!1227 = !DILocalVariable(name: "entry", arg: 2, scope: !382, file: !1, line: 1801, type: !29)
!1228 = !DILocation(line: 1801, column: 63, scope: !382)
!1229 = !DILocalVariable(name: "r", scope: !382, file: !1, line: 1803, type: !22)
!1230 = !DILocation(line: 1803, column: 6, scope: !382)
!1231 = !DILocation(line: 1805, column: 6, scope: !1232)
!1232 = distinct !DILexicalBlock(scope: !382, file: !1, line: 1805, column: 6)
!1233 = !DILocation(line: 1805, column: 9, scope: !1232)
!1234 = !DILocation(line: 1805, column: 24, scope: !1232)
!1235 = !DILocation(line: 1805, column: 6, scope: !382)
!1236 = !DILocation(line: 1806, column: 25, scope: !1237)
!1237 = distinct !DILexicalBlock(scope: !1238, file: !1, line: 1806, column: 7)
!1238 = distinct !DILexicalBlock(scope: !1232, file: !1, line: 1805, column: 31)
!1239 = !DILocation(line: 1806, column: 28, scope: !1237)
!1240 = !DILocation(line: 1807, column: 25, scope: !1237)
!1241 = !DILocation(line: 1807, column: 7, scope: !1237)
!1242 = !DILocation(line: 1806, column: 8, scope: !1237)
!1243 = !DILocation(line: 1806, column: 7, scope: !1238)
!1244 = !DILocation(line: 1808, column: 4, scope: !1237)
!1245 = !DILocation(line: 1809, column: 2, scope: !1238)
!1246 = !DILocation(line: 1811, column: 6, scope: !1247)
!1247 = distinct !DILexicalBlock(scope: !382, file: !1, line: 1811, column: 6)
!1248 = !DILocation(line: 1811, column: 9, scope: !1247)
!1249 = !DILocation(line: 1811, column: 24, scope: !1247)
!1250 = !DILocation(line: 1811, column: 6, scope: !382)
!1251 = !DILocation(line: 1812, column: 25, scope: !1252)
!1252 = distinct !DILexicalBlock(scope: !1253, file: !1, line: 1812, column: 7)
!1253 = distinct !DILexicalBlock(scope: !1247, file: !1, line: 1811, column: 31)
!1254 = !DILocation(line: 1812, column: 28, scope: !1252)
!1255 = !DILocation(line: 1813, column: 25, scope: !1252)
!1256 = !DILocation(line: 1813, column: 7, scope: !1252)
!1257 = !DILocation(line: 1812, column: 8, scope: !1252)
!1258 = !DILocation(line: 1812, column: 7, scope: !1253)
!1259 = !DILocation(line: 1814, column: 4, scope: !1252)
!1260 = !DILocation(line: 1815, column: 2, scope: !1253)
!1261 = !DILocation(line: 1817, column: 6, scope: !1262)
!1262 = distinct !DILexicalBlock(scope: !382, file: !1, line: 1817, column: 6)
!1263 = !DILocation(line: 1817, column: 9, scope: !1262)
!1264 = !DILocation(line: 1817, column: 26, scope: !1262)
!1265 = !DILocation(line: 1817, column: 6, scope: !382)
!1266 = !DILocation(line: 1822, column: 28, scope: !1267)
!1267 = distinct !DILexicalBlock(scope: !1262, file: !1, line: 1817, column: 33)
!1268 = !DILocation(line: 1822, column: 33, scope: !1267)
!1269 = !DILocation(line: 1822, column: 36, scope: !1267)
!1270 = !DILocation(line: 1823, column: 24, scope: !1267)
!1271 = !DILocation(line: 1823, column: 4, scope: !1267)
!1272 = !DILocation(line: 1822, column: 7, scope: !1267)
!1273 = !DILocation(line: 1822, column: 5, scope: !1267)
!1274 = !DILocation(line: 1825, column: 8, scope: !1275)
!1275 = distinct !DILexicalBlock(scope: !1267, file: !1, line: 1825, column: 7)
!1276 = !DILocation(line: 1825, column: 7, scope: !1267)
!1277 = !DILocation(line: 1826, column: 4, scope: !1275)
!1278 = !DILocation(line: 1827, column: 12, scope: !1279)
!1279 = distinct !DILexicalBlock(scope: !1275, file: !1, line: 1827, column: 12)
!1280 = !DILocation(line: 1827, column: 14, scope: !1279)
!1281 = !DILocation(line: 1827, column: 12, scope: !1275)
!1282 = !DILocation(line: 1828, column: 12, scope: !1279)
!1283 = !DILocation(line: 1828, column: 4, scope: !1279)
!1284 = !DILocation(line: 1829, column: 2, scope: !1267)
!1285 = !DILocation(line: 1831, column: 6, scope: !1286)
!1286 = distinct !DILexicalBlock(scope: !382, file: !1, line: 1831, column: 6)
!1287 = !DILocation(line: 1831, column: 9, scope: !1286)
!1288 = !DILocation(line: 1831, column: 26, scope: !1286)
!1289 = !DILocation(line: 1831, column: 6, scope: !382)
!1290 = !DILocation(line: 1836, column: 28, scope: !1291)
!1291 = distinct !DILexicalBlock(scope: !1286, file: !1, line: 1831, column: 33)
!1292 = !DILocation(line: 1836, column: 33, scope: !1291)
!1293 = !DILocation(line: 1836, column: 36, scope: !1291)
!1294 = !DILocation(line: 1837, column: 24, scope: !1291)
!1295 = !DILocation(line: 1837, column: 4, scope: !1291)
!1296 = !DILocation(line: 1836, column: 7, scope: !1291)
!1297 = !DILocation(line: 1836, column: 5, scope: !1291)
!1298 = !DILocation(line: 1839, column: 8, scope: !1299)
!1299 = distinct !DILexicalBlock(scope: !1291, file: !1, line: 1839, column: 7)
!1300 = !DILocation(line: 1839, column: 7, scope: !1291)
!1301 = !DILocation(line: 1840, column: 4, scope: !1299)
!1302 = !DILocation(line: 1841, column: 12, scope: !1303)
!1303 = distinct !DILexicalBlock(scope: !1299, file: !1, line: 1841, column: 12)
!1304 = !DILocation(line: 1841, column: 14, scope: !1303)
!1305 = !DILocation(line: 1841, column: 12, scope: !1299)
!1306 = !DILocation(line: 1842, column: 12, scope: !1303)
!1307 = !DILocation(line: 1842, column: 4, scope: !1303)
!1308 = !DILocation(line: 1843, column: 2, scope: !1291)
!1309 = !DILocation(line: 1844, column: 2, scope: !382)
!1310 = !DILocation(line: 1845, column: 1, scope: !382)
!1311 = !DILocalVariable(name: "_a", arg: 1, scope: !226, file: !1, line: 309, type: !23)
!1312 = !DILocation(line: 309, column: 47, scope: !226)
!1313 = !DILocalVariable(name: "pattern", arg: 2, scope: !226, file: !1, line: 309, type: !79)
!1314 = !DILocation(line: 309, column: 63, scope: !226)
!1315 = !DILocalVariable(name: "a", scope: !226, file: !1, line: 311, type: !4)
!1316 = !DILocation(line: 311, column: 24, scope: !226)
!1317 = !DILocalVariable(name: "r", scope: !226, file: !1, line: 312, type: !22)
!1318 = !DILocation(line: 312, column: 6, scope: !226)
!1319 = !DILocation(line: 314, column: 2, scope: !226)
!1320 = !DILocalVariable(name: "magic_test", scope: !1321, file: !1, line: 314, type: !22)
!1321 = distinct !DILexicalBlock(scope: !226, file: !1, line: 314, column: 2)
!1322 = !DILocation(line: 314, column: 2, scope: !1321)
!1323 = !DILocation(line: 314, column: 2, scope: !1324)
!1324 = !DILexicalBlockFile(scope: !1321, file: !1, discriminator: 1)
!1325 = !DILocation(line: 314, column: 2, scope: !1326)
!1326 = !DILexicalBlockFile(scope: !1327, file: !1, discriminator: 2)
!1327 = distinct !DILexicalBlock(scope: !1321, file: !1, line: 314, column: 2)
!1328 = !DILocation(line: 314, column: 2, scope: !1329)
!1329 = !DILexicalBlockFile(scope: !1321, file: !1, discriminator: 3)
!1330 = !DILocation(line: 316, column: 30, scope: !226)
!1331 = !DILocation(line: 316, column: 6, scope: !226)
!1332 = !DILocation(line: 316, column: 4, scope: !226)
!1333 = !DILocation(line: 318, column: 6, scope: !1334)
!1334 = distinct !DILexicalBlock(scope: !226, file: !1, line: 318, column: 6)
!1335 = !DILocation(line: 318, column: 14, scope: !1334)
!1336 = !DILocation(line: 318, column: 22, scope: !1334)
!1337 = !DILocation(line: 318, column: 26, scope: !1338)
!1338 = !DILexicalBlockFile(scope: !1334, file: !1, discriminator: 1)
!1339 = !DILocation(line: 318, column: 25, scope: !1338)
!1340 = !DILocation(line: 318, column: 34, scope: !1338)
!1341 = !DILocation(line: 318, column: 6, scope: !1338)
!1342 = !DILocation(line: 319, column: 23, scope: !1343)
!1343 = distinct !DILexicalBlock(scope: !1334, file: !1, line: 318, column: 43)
!1344 = !DILocation(line: 319, column: 26, scope: !1343)
!1345 = !DILocation(line: 319, column: 3, scope: !1343)
!1346 = !DILocation(line: 320, column: 3, scope: !1343)
!1347 = !DILocation(line: 322, column: 27, scope: !1348)
!1348 = distinct !DILexicalBlock(scope: !226, file: !1, line: 322, column: 6)
!1349 = !DILocation(line: 322, column: 32, scope: !1348)
!1350 = !DILocation(line: 322, column: 35, scope: !1348)
!1351 = !DILocation(line: 322, column: 48, scope: !1348)
!1352 = !DILocation(line: 322, column: 11, scope: !1348)
!1353 = !DILocation(line: 322, column: 9, scope: !1348)
!1354 = !DILocation(line: 322, column: 58, scope: !1348)
!1355 = !DILocation(line: 322, column: 6, scope: !226)
!1356 = !DILocation(line: 323, column: 11, scope: !1348)
!1357 = !DILocation(line: 323, column: 3, scope: !1348)
!1358 = !DILocation(line: 324, column: 2, scope: !226)
!1359 = !DILocation(line: 325, column: 1, scope: !226)
!1360 = !DILocalVariable(name: "a", arg: 1, scope: !278, file: !1, line: 526, type: !4)
!1361 = !DILocation(line: 526, column: 39, scope: !278)
!1362 = !DILocalVariable(name: "list", arg: 2, scope: !278, file: !1, line: 526, type: !281)
!1363 = !DILocation(line: 526, column: 61, scope: !278)
!1364 = !DILocalVariable(name: "pattern", arg: 3, scope: !278, file: !1, line: 527, type: !79)
!1365 = !DILocation(line: 527, column: 17, scope: !278)
!1366 = !DILocalVariable(name: "match", scope: !278, file: !1, line: 529, type: !114)
!1367 = !DILocation(line: 529, column: 16, scope: !278)
!1368 = !DILocalVariable(name: "len", scope: !278, file: !1, line: 530, type: !44)
!1369 = !DILocation(line: 530, column: 9, scope: !278)
!1370 = !DILocation(line: 532, column: 10, scope: !278)
!1371 = !DILocation(line: 532, column: 8, scope: !278)
!1372 = !DILocation(line: 533, column: 6, scope: !1373)
!1373 = distinct !DILexicalBlock(scope: !278, file: !1, line: 533, column: 6)
!1374 = !DILocation(line: 533, column: 12, scope: !1373)
!1375 = !DILocation(line: 533, column: 6, scope: !278)
!1376 = !DILocation(line: 534, column: 23, scope: !1373)
!1377 = !DILocation(line: 534, column: 11, scope: !1373)
!1378 = !DILocation(line: 534, column: 3, scope: !1373)
!1379 = !DILocation(line: 536, column: 15, scope: !278)
!1380 = !DILocation(line: 536, column: 8, scope: !278)
!1381 = !DILocation(line: 536, column: 6, scope: !278)
!1382 = !DILocation(line: 537, column: 6, scope: !1383)
!1383 = distinct !DILexicalBlock(scope: !278, file: !1, line: 537, column: 6)
!1384 = !DILocation(line: 537, column: 10, scope: !1383)
!1385 = !DILocation(line: 537, column: 21, scope: !1386)
!1386 = !DILexicalBlockFile(scope: !1383, file: !1, discriminator: 1)
!1387 = !DILocation(line: 537, column: 25, scope: !1386)
!1388 = !DILocation(line: 537, column: 13, scope: !1386)
!1389 = !DILocation(line: 537, column: 30, scope: !1386)
!1390 = !DILocation(line: 537, column: 6, scope: !1386)
!1391 = !DILocation(line: 538, column: 3, scope: !1383)
!1392 = !DILocation(line: 539, column: 33, scope: !278)
!1393 = !DILocation(line: 539, column: 40, scope: !278)
!1394 = !DILocation(line: 539, column: 50, scope: !278)
!1395 = !DILocation(line: 539, column: 59, scope: !278)
!1396 = !DILocation(line: 539, column: 2, scope: !278)
!1397 = !DILocation(line: 540, column: 17, scope: !278)
!1398 = !DILocation(line: 540, column: 23, scope: !278)
!1399 = !DILocation(line: 540, column: 2, scope: !278)
!1400 = !DILocation(line: 541, column: 2, scope: !278)
!1401 = !DILocation(line: 541, column: 5, scope: !278)
!1402 = !DILocation(line: 541, column: 13, scope: !278)
!1403 = !DILocation(line: 542, column: 2, scope: !278)
!1404 = !DILocation(line: 543, column: 1, scope: !278)
!1405 = !DILocalVariable(name: "_a", arg: 1, scope: !229, file: !1, line: 328, type: !23)
!1406 = !DILocation(line: 328, column: 49, scope: !229)
!1407 = !DILocalVariable(name: "pattern", arg: 2, scope: !229, file: !1, line: 328, type: !218)
!1408 = !DILocation(line: 328, column: 68, scope: !229)
!1409 = !DILocalVariable(name: "a", scope: !229, file: !1, line: 330, type: !4)
!1410 = !DILocation(line: 330, column: 24, scope: !229)
!1411 = !DILocalVariable(name: "r", scope: !229, file: !1, line: 331, type: !22)
!1412 = !DILocation(line: 331, column: 6, scope: !229)
!1413 = !DILocation(line: 333, column: 2, scope: !229)
!1414 = !DILocalVariable(name: "magic_test", scope: !1415, file: !1, line: 333, type: !22)
!1415 = distinct !DILexicalBlock(scope: !229, file: !1, line: 333, column: 2)
!1416 = !DILocation(line: 333, column: 2, scope: !1415)
!1417 = !DILocation(line: 333, column: 2, scope: !1418)
!1418 = !DILexicalBlockFile(scope: !1415, file: !1, discriminator: 1)
!1419 = !DILocation(line: 333, column: 2, scope: !1420)
!1420 = !DILexicalBlockFile(scope: !1421, file: !1, discriminator: 2)
!1421 = distinct !DILexicalBlock(scope: !1415, file: !1, line: 333, column: 2)
!1422 = !DILocation(line: 333, column: 2, scope: !1423)
!1423 = !DILexicalBlockFile(scope: !1415, file: !1, discriminator: 3)
!1424 = !DILocation(line: 335, column: 30, scope: !229)
!1425 = !DILocation(line: 335, column: 6, scope: !229)
!1426 = !DILocation(line: 335, column: 4, scope: !229)
!1427 = !DILocation(line: 337, column: 6, scope: !1428)
!1428 = distinct !DILexicalBlock(scope: !229, file: !1, line: 337, column: 6)
!1429 = !DILocation(line: 337, column: 14, scope: !1428)
!1430 = !DILocation(line: 337, column: 22, scope: !1428)
!1431 = !DILocation(line: 337, column: 26, scope: !1432)
!1432 = !DILexicalBlockFile(scope: !1428, file: !1, discriminator: 1)
!1433 = !DILocation(line: 337, column: 25, scope: !1432)
!1434 = !DILocation(line: 337, column: 34, scope: !1432)
!1435 = !DILocation(line: 337, column: 6, scope: !1432)
!1436 = !DILocation(line: 338, column: 23, scope: !1437)
!1437 = distinct !DILexicalBlock(scope: !1428, file: !1, line: 337, column: 44)
!1438 = !DILocation(line: 338, column: 26, scope: !1437)
!1439 = !DILocation(line: 338, column: 3, scope: !1437)
!1440 = !DILocation(line: 339, column: 3, scope: !1437)
!1441 = !DILocation(line: 341, column: 27, scope: !1442)
!1442 = distinct !DILexicalBlock(scope: !229, file: !1, line: 341, column: 6)
!1443 = !DILocation(line: 341, column: 32, scope: !1442)
!1444 = !DILocation(line: 341, column: 35, scope: !1442)
!1445 = !DILocation(line: 341, column: 48, scope: !1442)
!1446 = !DILocation(line: 341, column: 11, scope: !1442)
!1447 = !DILocation(line: 341, column: 9, scope: !1442)
!1448 = !DILocation(line: 341, column: 58, scope: !1442)
!1449 = !DILocation(line: 341, column: 6, scope: !229)
!1450 = !DILocation(line: 342, column: 11, scope: !1442)
!1451 = !DILocation(line: 342, column: 3, scope: !1442)
!1452 = !DILocation(line: 343, column: 2, scope: !229)
!1453 = !DILocation(line: 344, column: 1, scope: !229)
!1454 = !DILocalVariable(name: "a", arg: 1, scope: !288, file: !1, line: 546, type: !4)
!1455 = !DILocation(line: 546, column: 39, scope: !288)
!1456 = !DILocalVariable(name: "list", arg: 2, scope: !288, file: !1, line: 546, type: !281)
!1457 = !DILocation(line: 546, column: 61, scope: !288)
!1458 = !DILocalVariable(name: "pattern", arg: 3, scope: !288, file: !1, line: 547, type: !218)
!1459 = !DILocation(line: 547, column: 20, scope: !288)
!1460 = !DILocalVariable(name: "match", scope: !288, file: !1, line: 549, type: !114)
!1461 = !DILocation(line: 549, column: 16, scope: !288)
!1462 = !DILocalVariable(name: "len", scope: !288, file: !1, line: 550, type: !44)
!1463 = !DILocation(line: 550, column: 9, scope: !288)
!1464 = !DILocation(line: 552, column: 10, scope: !288)
!1465 = !DILocation(line: 552, column: 8, scope: !288)
!1466 = !DILocation(line: 553, column: 6, scope: !1467)
!1467 = distinct !DILexicalBlock(scope: !288, file: !1, line: 553, column: 6)
!1468 = !DILocation(line: 553, column: 12, scope: !1467)
!1469 = !DILocation(line: 553, column: 6, scope: !288)
!1470 = !DILocation(line: 554, column: 23, scope: !1467)
!1471 = !DILocation(line: 554, column: 11, scope: !1467)
!1472 = !DILocation(line: 554, column: 3, scope: !1467)
!1473 = !DILocation(line: 556, column: 15, scope: !288)
!1474 = !DILocation(line: 556, column: 8, scope: !288)
!1475 = !DILocation(line: 556, column: 6, scope: !288)
!1476 = !DILocation(line: 557, column: 6, scope: !1477)
!1477 = distinct !DILexicalBlock(scope: !288, file: !1, line: 557, column: 6)
!1478 = !DILocation(line: 557, column: 10, scope: !1477)
!1479 = !DILocation(line: 557, column: 21, scope: !1480)
!1480 = !DILexicalBlockFile(scope: !1477, file: !1, discriminator: 1)
!1481 = !DILocation(line: 557, column: 25, scope: !1480)
!1482 = !DILocation(line: 557, column: 13, scope: !1480)
!1483 = !DILocation(line: 557, column: 30, scope: !1480)
!1484 = !DILocation(line: 557, column: 6, scope: !1480)
!1485 = !DILocation(line: 558, column: 3, scope: !1477)
!1486 = !DILocation(line: 559, column: 33, scope: !288)
!1487 = !DILocation(line: 559, column: 40, scope: !288)
!1488 = !DILocation(line: 559, column: 50, scope: !288)
!1489 = !DILocation(line: 559, column: 59, scope: !288)
!1490 = !DILocation(line: 559, column: 2, scope: !288)
!1491 = !DILocation(line: 560, column: 17, scope: !288)
!1492 = !DILocation(line: 560, column: 23, scope: !288)
!1493 = !DILocation(line: 560, column: 2, scope: !288)
!1494 = !DILocation(line: 561, column: 2, scope: !288)
!1495 = !DILocation(line: 561, column: 5, scope: !288)
!1496 = !DILocation(line: 561, column: 13, scope: !288)
!1497 = !DILocation(line: 562, column: 2, scope: !288)
!1498 = !DILocation(line: 563, column: 1, scope: !288)
!1499 = !DILocalVariable(name: "_a", arg: 1, scope: !232, file: !1, line: 347, type: !23)
!1500 = !DILocation(line: 347, column: 57, scope: !232)
!1501 = !DILocalVariable(name: "pathname", arg: 2, scope: !232, file: !1, line: 348, type: !79)
!1502 = !DILocation(line: 348, column: 17, scope: !232)
!1503 = !DILocalVariable(name: "nullSeparator", arg: 3, scope: !232, file: !1, line: 348, type: !22)
!1504 = !DILocation(line: 348, column: 31, scope: !232)
!1505 = !DILocalVariable(name: "a", scope: !232, file: !1, line: 350, type: !4)
!1506 = !DILocation(line: 350, column: 24, scope: !232)
!1507 = !DILocation(line: 352, column: 2, scope: !232)
!1508 = !DILocalVariable(name: "magic_test", scope: !1509, file: !1, line: 352, type: !22)
!1509 = distinct !DILexicalBlock(scope: !232, file: !1, line: 352, column: 2)
!1510 = !DILocation(line: 352, column: 2, scope: !1509)
!1511 = !DILocation(line: 352, column: 2, scope: !1512)
!1512 = !DILexicalBlockFile(scope: !1509, file: !1, discriminator: 1)
!1513 = !DILocation(line: 352, column: 2, scope: !1514)
!1514 = !DILexicalBlockFile(scope: !1515, file: !1, discriminator: 2)
!1515 = distinct !DILexicalBlock(scope: !1509, file: !1, line: 352, column: 2)
!1516 = !DILocation(line: 352, column: 2, scope: !1517)
!1517 = !DILexicalBlockFile(scope: !1509, file: !1, discriminator: 3)
!1518 = !DILocation(line: 354, column: 30, scope: !232)
!1519 = !DILocation(line: 354, column: 6, scope: !232)
!1520 = !DILocation(line: 354, column: 4, scope: !232)
!1521 = !DILocation(line: 356, column: 31, scope: !232)
!1522 = !DILocation(line: 356, column: 36, scope: !232)
!1523 = !DILocation(line: 356, column: 39, scope: !232)
!1524 = !DILocation(line: 356, column: 55, scope: !232)
!1525 = !DILocation(line: 357, column: 3, scope: !232)
!1526 = !DILocation(line: 356, column: 9, scope: !232)
!1527 = !DILocation(line: 356, column: 2, scope: !232)
!1528 = !DILocation(line: 358, column: 1, scope: !232)
!1529 = !DILocalVariable(name: "a", arg: 1, scope: !291, file: !1, line: 566, type: !4)
!1530 = !DILocation(line: 566, column: 45, scope: !291)
!1531 = !DILocalVariable(name: "mlist", arg: 2, scope: !291, file: !1, line: 566, type: !281)
!1532 = !DILocation(line: 566, column: 67, scope: !291)
!1533 = !DILocalVariable(name: "mbs", arg: 3, scope: !291, file: !1, line: 567, type: !22)
!1534 = !DILocation(line: 567, column: 9, scope: !291)
!1535 = !DILocalVariable(name: "pathname", arg: 4, scope: !291, file: !1, line: 567, type: !42)
!1536 = !DILocation(line: 567, column: 26, scope: !291)
!1537 = !DILocalVariable(name: "nullSeparator", arg: 5, scope: !291, file: !1, line: 567, type: !22)
!1538 = !DILocation(line: 567, column: 40, scope: !291)
!1539 = !DILocalVariable(name: "ar", scope: !291, file: !1, line: 569, type: !23)
!1540 = !DILocation(line: 569, column: 18, scope: !291)
!1541 = !DILocalVariable(name: "ae", scope: !291, file: !1, line: 570, type: !29)
!1542 = !DILocation(line: 570, column: 24, scope: !291)
!1543 = !DILocalVariable(name: "as", scope: !291, file: !1, line: 571, type: !90)
!1544 = !DILocation(line: 571, column: 24, scope: !291)
!1545 = !DILocalVariable(name: "buff", scope: !291, file: !1, line: 572, type: !42)
!1546 = !DILocation(line: 572, column: 14, scope: !291)
!1547 = !DILocalVariable(name: "size", scope: !291, file: !1, line: 573, type: !44)
!1548 = !DILocation(line: 573, column: 9, scope: !291)
!1549 = !DILocalVariable(name: "offset", scope: !291, file: !1, line: 574, type: !51)
!1550 = !DILocation(line: 574, column: 10, scope: !291)
!1551 = !DILocalVariable(name: "r", scope: !291, file: !1, line: 575, type: !22)
!1552 = !DILocation(line: 575, column: 6, scope: !291)
!1553 = !DILocation(line: 577, column: 7, scope: !291)
!1554 = !DILocation(line: 577, column: 5, scope: !291)
!1555 = !DILocation(line: 578, column: 6, scope: !1556)
!1556 = distinct !DILexicalBlock(scope: !291, file: !1, line: 578, column: 6)
!1557 = !DILocation(line: 578, column: 9, scope: !1556)
!1558 = !DILocation(line: 578, column: 6, scope: !291)
!1559 = !DILocation(line: 579, column: 23, scope: !1560)
!1560 = distinct !DILexicalBlock(scope: !1556, file: !1, line: 578, column: 18)
!1561 = !DILocation(line: 579, column: 26, scope: !1560)
!1562 = !DILocation(line: 579, column: 3, scope: !1560)
!1563 = !DILocation(line: 580, column: 3, scope: !1560)
!1564 = !DILocation(line: 582, column: 38, scope: !291)
!1565 = !DILocation(line: 582, column: 6, scope: !291)
!1566 = !DILocation(line: 582, column: 4, scope: !291)
!1567 = !DILocation(line: 583, column: 40, scope: !291)
!1568 = !DILocation(line: 583, column: 6, scope: !291)
!1569 = !DILocation(line: 583, column: 4, scope: !291)
!1570 = !DILocation(line: 584, column: 6, scope: !1571)
!1571 = distinct !DILexicalBlock(scope: !291, file: !1, line: 584, column: 6)
!1572 = !DILocation(line: 584, column: 8, scope: !1571)
!1573 = !DILocation(line: 584, column: 6, scope: !291)
!1574 = !DILocation(line: 585, column: 24, scope: !1575)
!1575 = distinct !DILexicalBlock(scope: !1571, file: !1, line: 584, column: 23)
!1576 = !DILocation(line: 585, column: 27, scope: !1575)
!1577 = !DILocation(line: 585, column: 37, scope: !1575)
!1578 = !DILocation(line: 585, column: 3, scope: !1575)
!1579 = !DILocation(line: 586, column: 21, scope: !1575)
!1580 = !DILocation(line: 586, column: 3, scope: !1575)
!1581 = !DILocation(line: 587, column: 11, scope: !1575)
!1582 = !DILocation(line: 587, column: 3, scope: !1575)
!1583 = !DILocation(line: 589, column: 6, scope: !1584)
!1584 = distinct !DILexicalBlock(scope: !291, file: !1, line: 589, column: 6)
!1585 = !DILocation(line: 589, column: 6, scope: !291)
!1586 = !DILocation(line: 590, column: 34, scope: !1584)
!1587 = !DILocation(line: 590, column: 38, scope: !1584)
!1588 = !DILocation(line: 590, column: 7, scope: !1584)
!1589 = !DILocation(line: 590, column: 5, scope: !1584)
!1590 = !DILocation(line: 590, column: 3, scope: !1584)
!1591 = !DILocation(line: 592, column: 36, scope: !1584)
!1592 = !DILocation(line: 592, column: 40, scope: !1584)
!1593 = !DILocation(line: 592, column: 7, scope: !1584)
!1594 = !DILocation(line: 592, column: 5, scope: !1584)
!1595 = !DILocation(line: 593, column: 6, scope: !1596)
!1596 = distinct !DILexicalBlock(scope: !291, file: !1, line: 593, column: 6)
!1597 = !DILocation(line: 593, column: 8, scope: !1596)
!1598 = !DILocation(line: 593, column: 6, scope: !291)
!1599 = !DILocation(line: 594, column: 24, scope: !1600)
!1600 = distinct !DILexicalBlock(scope: !1596, file: !1, line: 593, column: 23)
!1601 = !DILocation(line: 594, column: 27, scope: !1600)
!1602 = !DILocation(line: 594, column: 37, scope: !1600)
!1603 = !DILocation(line: 594, column: 3, scope: !1600)
!1604 = !DILocation(line: 595, column: 21, scope: !1600)
!1605 = !DILocation(line: 595, column: 3, scope: !1600)
!1606 = !DILocation(line: 596, column: 11, scope: !1600)
!1607 = !DILocation(line: 596, column: 3, scope: !1600)
!1608 = !DILocation(line: 598, column: 31, scope: !291)
!1609 = !DILocation(line: 598, column: 6, scope: !291)
!1610 = !DILocation(line: 598, column: 4, scope: !291)
!1611 = !DILocation(line: 599, column: 6, scope: !1612)
!1612 = distinct !DILexicalBlock(scope: !291, file: !1, line: 599, column: 6)
!1613 = !DILocation(line: 599, column: 8, scope: !1612)
!1614 = !DILocation(line: 599, column: 6, scope: !291)
!1615 = !DILocation(line: 600, column: 21, scope: !1616)
!1616 = distinct !DILexicalBlock(scope: !1612, file: !1, line: 599, column: 23)
!1617 = !DILocation(line: 600, column: 3, scope: !1616)
!1618 = !DILocation(line: 601, column: 7, scope: !1619)
!1619 = distinct !DILexicalBlock(scope: !1616, file: !1, line: 601, column: 7)
!1620 = !DILocation(line: 601, column: 9, scope: !1619)
!1621 = !DILocation(line: 601, column: 7, scope: !1616)
!1622 = !DILocation(line: 602, column: 4, scope: !1623)
!1623 = distinct !DILexicalBlock(scope: !1619, file: !1, line: 601, column: 25)
!1624 = !DILocation(line: 604, column: 25, scope: !1625)
!1625 = distinct !DILexicalBlock(scope: !1619, file: !1, line: 603, column: 10)
!1626 = !DILocation(line: 604, column: 28, scope: !1625)
!1627 = !DILocation(line: 604, column: 38, scope: !1625)
!1628 = !DILocation(line: 604, column: 4, scope: !1625)
!1629 = !DILocation(line: 605, column: 12, scope: !1625)
!1630 = !DILocation(line: 605, column: 4, scope: !1625)
!1631 = !DILocation(line: 609, column: 2, scope: !291)
!1632 = !DILocation(line: 609, column: 2, scope: !1633)
!1633 = !DILexicalBlockFile(scope: !1634, file: !1, discriminator: 1)
!1634 = distinct !DILexicalBlock(scope: !291, file: !1, line: 609, column: 2)
!1635 = !DILocation(line: 611, column: 2, scope: !291)
!1636 = !DILocation(line: 611, column: 38, scope: !1637)
!1637 = !DILexicalBlockFile(scope: !291, file: !1, discriminator: 1)
!1638 = !DILocation(line: 611, column: 14, scope: !1637)
!1639 = !DILocation(line: 611, column: 12, scope: !1637)
!1640 = !DILocation(line: 612, column: 6, scope: !291)
!1641 = !DILocation(line: 611, column: 2, scope: !1637)
!1642 = !DILocalVariable(name: "b", scope: !1643, file: !1, line: 613, type: !79)
!1643 = distinct !DILexicalBlock(scope: !291, file: !1, line: 612, column: 21)
!1644 = !DILocation(line: 613, column: 15, scope: !1643)
!1645 = !DILocation(line: 613, column: 33, scope: !1643)
!1646 = !DILocation(line: 615, column: 3, scope: !1643)
!1647 = !DILocation(line: 615, column: 10, scope: !1648)
!1648 = !DILexicalBlockFile(scope: !1643, file: !1, discriminator: 1)
!1649 = !DILocation(line: 615, column: 3, scope: !1648)
!1650 = !DILocalVariable(name: "s", scope: !1651, file: !1, line: 616, type: !79)
!1651 = distinct !DILexicalBlock(scope: !1643, file: !1, line: 615, column: 16)
!1652 = !DILocation(line: 616, column: 16, scope: !1651)
!1653 = !DILocation(line: 616, column: 34, scope: !1651)
!1654 = !DILocalVariable(name: "length", scope: !1651, file: !1, line: 617, type: !44)
!1655 = !DILocation(line: 617, column: 11, scope: !1651)
!1656 = !DILocalVariable(name: "found_separator", scope: !1651, file: !1, line: 618, type: !22)
!1657 = !DILocation(line: 618, column: 8, scope: !1651)
!1658 = !DILocation(line: 620, column: 4, scope: !1651)
!1659 = !DILocation(line: 620, column: 11, scope: !1660)
!1660 = !DILexicalBlockFile(scope: !1651, file: !1, discriminator: 1)
!1661 = !DILocation(line: 620, column: 20, scope: !1660)
!1662 = !DILocation(line: 620, column: 18, scope: !1660)
!1663 = !DILocation(line: 620, column: 4, scope: !1660)
!1664 = !DILocation(line: 621, column: 9, scope: !1665)
!1665 = distinct !DILexicalBlock(scope: !1666, file: !1, line: 621, column: 9)
!1666 = distinct !DILexicalBlock(scope: !1651, file: !1, line: 620, column: 26)
!1667 = !DILocation(line: 621, column: 9, scope: !1666)
!1668 = !DILocation(line: 622, column: 11, scope: !1669)
!1669 = distinct !DILexicalBlock(scope: !1670, file: !1, line: 622, column: 10)
!1670 = distinct !DILexicalBlock(scope: !1665, file: !1, line: 621, column: 24)
!1671 = !DILocation(line: 622, column: 10, scope: !1669)
!1672 = !DILocation(line: 622, column: 13, scope: !1669)
!1673 = !DILocation(line: 622, column: 10, scope: !1670)
!1674 = !DILocation(line: 623, column: 23, scope: !1675)
!1675 = distinct !DILexicalBlock(scope: !1669, file: !1, line: 622, column: 22)
!1676 = !DILocation(line: 624, column: 7, scope: !1675)
!1677 = !DILocation(line: 626, column: 5, scope: !1670)
!1678 = !DILocation(line: 627, column: 22, scope: !1679)
!1679 = distinct !DILexicalBlock(scope: !1680, file: !1, line: 627, column: 21)
!1680 = distinct !DILexicalBlock(scope: !1665, file: !1, line: 626, column: 12)
!1681 = !DILocation(line: 627, column: 21, scope: !1679)
!1682 = !DILocation(line: 627, column: 24, scope: !1679)
!1683 = !DILocation(line: 627, column: 32, scope: !1679)
!1684 = !DILocation(line: 627, column: 36, scope: !1685)
!1685 = !DILexicalBlockFile(scope: !1679, file: !1, discriminator: 1)
!1686 = !DILocation(line: 627, column: 35, scope: !1685)
!1687 = !DILocation(line: 627, column: 38, scope: !1685)
!1688 = !DILocation(line: 627, column: 21, scope: !1685)
!1689 = !DILocation(line: 628, column: 23, scope: !1690)
!1690 = distinct !DILexicalBlock(scope: !1679, file: !1, line: 627, column: 47)
!1691 = !DILocation(line: 629, column: 7, scope: !1690)
!1692 = !DILocation(line: 632, column: 6, scope: !1666)
!1693 = !DILocation(line: 633, column: 11, scope: !1666)
!1694 = !DILocation(line: 620, column: 4, scope: !1695)
!1695 = !DILexicalBlockFile(scope: !1651, file: !1, discriminator: 2)
!1696 = !DILocation(line: 635, column: 9, scope: !1697)
!1697 = distinct !DILexicalBlock(scope: !1651, file: !1, line: 635, column: 8)
!1698 = !DILocation(line: 635, column: 8, scope: !1651)
!1699 = !DILocation(line: 636, column: 26, scope: !1700)
!1700 = distinct !DILexicalBlock(scope: !1697, file: !1, line: 635, column: 26)
!1701 = !DILocation(line: 636, column: 29, scope: !1700)
!1702 = !DILocation(line: 636, column: 5, scope: !1700)
!1703 = !DILocation(line: 638, column: 5, scope: !1700)
!1704 = !DILocation(line: 640, column: 5, scope: !1651)
!1705 = !DILocation(line: 641, column: 12, scope: !1651)
!1706 = !DILocation(line: 641, column: 19, scope: !1651)
!1707 = !DILocation(line: 641, column: 9, scope: !1651)
!1708 = !DILocation(line: 642, column: 25, scope: !1651)
!1709 = !DILocation(line: 642, column: 28, scope: !1651)
!1710 = !DILocation(line: 642, column: 4, scope: !1651)
!1711 = !DILocation(line: 645, column: 8, scope: !1712)
!1712 = distinct !DILexicalBlock(scope: !1651, file: !1, line: 645, column: 8)
!1713 = !DILocation(line: 645, column: 28, scope: !1712)
!1714 = !DILocation(line: 645, column: 8, scope: !1651)
!1715 = !DILocation(line: 647, column: 25, scope: !1716)
!1716 = distinct !DILexicalBlock(scope: !1712, file: !1, line: 645, column: 33)
!1717 = !DILocation(line: 647, column: 28, scope: !1716)
!1718 = !DILocation(line: 647, column: 38, scope: !1716)
!1719 = !DILocation(line: 647, column: 9, scope: !1716)
!1720 = !DILocation(line: 647, column: 7, scope: !1716)
!1721 = !DILocation(line: 648, column: 9, scope: !1722)
!1722 = distinct !DILexicalBlock(scope: !1716, file: !1, line: 648, column: 9)
!1723 = !DILocation(line: 648, column: 11, scope: !1722)
!1724 = !DILocation(line: 648, column: 9, scope: !1716)
!1725 = !DILocation(line: 649, column: 24, scope: !1726)
!1726 = distinct !DILexicalBlock(scope: !1722, file: !1, line: 648, column: 26)
!1727 = !DILocation(line: 649, column: 6, scope: !1726)
!1728 = !DILocation(line: 650, column: 6, scope: !1726)
!1729 = !DILocation(line: 651, column: 14, scope: !1726)
!1730 = !DILocation(line: 651, column: 6, scope: !1726)
!1731 = !DILocation(line: 653, column: 5, scope: !1716)
!1732 = !DILocation(line: 654, column: 4, scope: !1716)
!1733 = !DILocation(line: 615, column: 3, scope: !1734)
!1734 = !DILexicalBlockFile(scope: !1643, file: !1, discriminator: 2)
!1735 = !DILocation(line: 611, column: 2, scope: !1736)
!1736 = !DILexicalBlockFile(scope: !291, file: !1, discriminator: 2)
!1737 = !DILocation(line: 659, column: 6, scope: !1738)
!1738 = distinct !DILexicalBlock(scope: !291, file: !1, line: 659, column: 6)
!1739 = !DILocation(line: 659, column: 8, scope: !1738)
!1740 = !DILocation(line: 659, column: 6, scope: !291)
!1741 = !DILocation(line: 660, column: 24, scope: !1742)
!1742 = distinct !DILexicalBlock(scope: !1738, file: !1, line: 659, column: 22)
!1743 = !DILocation(line: 660, column: 27, scope: !1742)
!1744 = !DILocation(line: 660, column: 37, scope: !1742)
!1745 = !DILocation(line: 660, column: 3, scope: !1742)
!1746 = !DILocation(line: 661, column: 21, scope: !1742)
!1747 = !DILocation(line: 661, column: 3, scope: !1742)
!1748 = !DILocation(line: 662, column: 3, scope: !1742)
!1749 = !DILocation(line: 663, column: 11, scope: !1742)
!1750 = !DILocation(line: 663, column: 3, scope: !1742)
!1751 = !DILocation(line: 667, column: 6, scope: !1752)
!1752 = distinct !DILexicalBlock(scope: !291, file: !1, line: 667, column: 6)
!1753 = !DILocation(line: 667, column: 8, scope: !1752)
!1754 = !DILocation(line: 667, column: 23, scope: !1752)
!1755 = !DILocation(line: 667, column: 26, scope: !1756)
!1756 = !DILexicalBlockFile(scope: !1752, file: !1, discriminator: 1)
!1757 = !DILocation(line: 667, column: 46, scope: !1756)
!1758 = !DILocation(line: 667, column: 6, scope: !1756)
!1759 = !DILocation(line: 669, column: 23, scope: !1760)
!1760 = distinct !DILexicalBlock(scope: !1752, file: !1, line: 667, column: 51)
!1761 = !DILocation(line: 669, column: 26, scope: !1760)
!1762 = !DILocation(line: 669, column: 36, scope: !1760)
!1763 = !DILocation(line: 669, column: 7, scope: !1760)
!1764 = !DILocation(line: 669, column: 5, scope: !1760)
!1765 = !DILocation(line: 670, column: 7, scope: !1766)
!1766 = distinct !DILexicalBlock(scope: !1760, file: !1, line: 670, column: 7)
!1767 = !DILocation(line: 670, column: 9, scope: !1766)
!1768 = !DILocation(line: 670, column: 7, scope: !1760)
!1769 = !DILocation(line: 671, column: 22, scope: !1770)
!1770 = distinct !DILexicalBlock(scope: !1766, file: !1, line: 670, column: 24)
!1771 = !DILocation(line: 671, column: 4, scope: !1770)
!1772 = !DILocation(line: 672, column: 4, scope: !1770)
!1773 = !DILocation(line: 673, column: 12, scope: !1770)
!1774 = !DILocation(line: 673, column: 4, scope: !1770)
!1775 = !DILocation(line: 675, column: 2, scope: !1760)
!1776 = !DILocation(line: 676, column: 20, scope: !291)
!1777 = !DILocation(line: 676, column: 2, scope: !291)
!1778 = !DILocation(line: 677, column: 2, scope: !291)
!1779 = !DILocation(line: 678, column: 2, scope: !291)
!1780 = !DILocation(line: 679, column: 1, scope: !291)
!1781 = !DILocalVariable(name: "_a", arg: 1, scope: !235, file: !1, line: 361, type: !23)
!1782 = !DILocation(line: 361, column: 59, scope: !235)
!1783 = !DILocalVariable(name: "pathname", arg: 2, scope: !235, file: !1, line: 362, type: !218)
!1784 = !DILocation(line: 362, column: 20, scope: !235)
!1785 = !DILocalVariable(name: "nullSeparator", arg: 3, scope: !235, file: !1, line: 362, type: !22)
!1786 = !DILocation(line: 362, column: 34, scope: !235)
!1787 = !DILocalVariable(name: "a", scope: !235, file: !1, line: 364, type: !4)
!1788 = !DILocation(line: 364, column: 24, scope: !235)
!1789 = !DILocation(line: 366, column: 2, scope: !235)
!1790 = !DILocalVariable(name: "magic_test", scope: !1791, file: !1, line: 366, type: !22)
!1791 = distinct !DILexicalBlock(scope: !235, file: !1, line: 366, column: 2)
!1792 = !DILocation(line: 366, column: 2, scope: !1791)
!1793 = !DILocation(line: 366, column: 2, scope: !1794)
!1794 = !DILexicalBlockFile(scope: !1791, file: !1, discriminator: 1)
!1795 = !DILocation(line: 366, column: 2, scope: !1796)
!1796 = !DILexicalBlockFile(scope: !1797, file: !1, discriminator: 2)
!1797 = distinct !DILexicalBlock(scope: !1791, file: !1, line: 366, column: 2)
!1798 = !DILocation(line: 366, column: 2, scope: !1799)
!1799 = !DILexicalBlockFile(scope: !1791, file: !1, discriminator: 3)
!1800 = !DILocation(line: 368, column: 30, scope: !235)
!1801 = !DILocation(line: 368, column: 6, scope: !235)
!1802 = !DILocation(line: 368, column: 4, scope: !235)
!1803 = !DILocation(line: 370, column: 31, scope: !235)
!1804 = !DILocation(line: 370, column: 36, scope: !235)
!1805 = !DILocation(line: 370, column: 39, scope: !235)
!1806 = !DILocation(line: 370, column: 55, scope: !235)
!1807 = !DILocation(line: 371, column: 3, scope: !235)
!1808 = !DILocation(line: 370, column: 9, scope: !235)
!1809 = !DILocation(line: 370, column: 2, scope: !235)
!1810 = !DILocation(line: 372, column: 1, scope: !235)
!1811 = !DILocalVariable(name: "_a", arg: 1, scope: !238, file: !1, line: 375, type: !23)
!1812 = !DILocation(line: 375, column: 47, scope: !238)
!1813 = !DILocalVariable(name: "pattern", arg: 2, scope: !238, file: !1, line: 375, type: !79)
!1814 = !DILocation(line: 375, column: 63, scope: !238)
!1815 = !DILocalVariable(name: "a", scope: !238, file: !1, line: 377, type: !4)
!1816 = !DILocation(line: 377, column: 24, scope: !238)
!1817 = !DILocalVariable(name: "r", scope: !238, file: !1, line: 378, type: !22)
!1818 = !DILocation(line: 378, column: 6, scope: !238)
!1819 = !DILocation(line: 380, column: 2, scope: !238)
!1820 = !DILocalVariable(name: "magic_test", scope: !1821, file: !1, line: 380, type: !22)
!1821 = distinct !DILexicalBlock(scope: !238, file: !1, line: 380, column: 2)
!1822 = !DILocation(line: 380, column: 2, scope: !1821)
!1823 = !DILocation(line: 380, column: 2, scope: !1824)
!1824 = !DILexicalBlockFile(scope: !1821, file: !1, discriminator: 1)
!1825 = !DILocation(line: 380, column: 2, scope: !1826)
!1826 = !DILexicalBlockFile(scope: !1827, file: !1, discriminator: 2)
!1827 = distinct !DILexicalBlock(scope: !1821, file: !1, line: 380, column: 2)
!1828 = !DILocation(line: 380, column: 2, scope: !1829)
!1829 = !DILexicalBlockFile(scope: !1821, file: !1, discriminator: 3)
!1830 = !DILocation(line: 382, column: 30, scope: !238)
!1831 = !DILocation(line: 382, column: 6, scope: !238)
!1832 = !DILocation(line: 382, column: 4, scope: !238)
!1833 = !DILocation(line: 384, column: 6, scope: !1834)
!1834 = distinct !DILexicalBlock(scope: !238, file: !1, line: 384, column: 6)
!1835 = !DILocation(line: 384, column: 14, scope: !1834)
!1836 = !DILocation(line: 384, column: 22, scope: !1834)
!1837 = !DILocation(line: 384, column: 26, scope: !1838)
!1838 = !DILexicalBlockFile(scope: !1834, file: !1, discriminator: 1)
!1839 = !DILocation(line: 384, column: 25, scope: !1838)
!1840 = !DILocation(line: 384, column: 34, scope: !1838)
!1841 = !DILocation(line: 384, column: 6, scope: !1838)
!1842 = !DILocation(line: 385, column: 23, scope: !1843)
!1843 = distinct !DILexicalBlock(scope: !1834, file: !1, line: 384, column: 43)
!1844 = !DILocation(line: 385, column: 26, scope: !1843)
!1845 = !DILocation(line: 385, column: 3, scope: !1843)
!1846 = !DILocation(line: 386, column: 3, scope: !1843)
!1847 = !DILocation(line: 388, column: 27, scope: !1848)
!1848 = distinct !DILexicalBlock(scope: !238, file: !1, line: 388, column: 6)
!1849 = !DILocation(line: 388, column: 32, scope: !1848)
!1850 = !DILocation(line: 388, column: 35, scope: !1848)
!1851 = !DILocation(line: 388, column: 48, scope: !1848)
!1852 = !DILocation(line: 388, column: 11, scope: !1848)
!1853 = !DILocation(line: 388, column: 9, scope: !1848)
!1854 = !DILocation(line: 388, column: 58, scope: !1848)
!1855 = !DILocation(line: 388, column: 6, scope: !238)
!1856 = !DILocation(line: 389, column: 11, scope: !1848)
!1857 = !DILocation(line: 389, column: 3, scope: !1848)
!1858 = !DILocation(line: 390, column: 2, scope: !238)
!1859 = !DILocation(line: 391, column: 1, scope: !238)
!1860 = !DILocalVariable(name: "_a", arg: 1, scope: !239, file: !1, line: 394, type: !23)
!1861 = !DILocation(line: 394, column: 49, scope: !239)
!1862 = !DILocalVariable(name: "pattern", arg: 2, scope: !239, file: !1, line: 394, type: !218)
!1863 = !DILocation(line: 394, column: 68, scope: !239)
!1864 = !DILocalVariable(name: "a", scope: !239, file: !1, line: 396, type: !4)
!1865 = !DILocation(line: 396, column: 24, scope: !239)
!1866 = !DILocalVariable(name: "r", scope: !239, file: !1, line: 397, type: !22)
!1867 = !DILocation(line: 397, column: 6, scope: !239)
!1868 = !DILocation(line: 399, column: 2, scope: !239)
!1869 = !DILocalVariable(name: "magic_test", scope: !1870, file: !1, line: 399, type: !22)
!1870 = distinct !DILexicalBlock(scope: !239, file: !1, line: 399, column: 2)
!1871 = !DILocation(line: 399, column: 2, scope: !1870)
!1872 = !DILocation(line: 399, column: 2, scope: !1873)
!1873 = !DILexicalBlockFile(scope: !1870, file: !1, discriminator: 1)
!1874 = !DILocation(line: 399, column: 2, scope: !1875)
!1875 = !DILexicalBlockFile(scope: !1876, file: !1, discriminator: 2)
!1876 = distinct !DILexicalBlock(scope: !1870, file: !1, line: 399, column: 2)
!1877 = !DILocation(line: 399, column: 2, scope: !1878)
!1878 = !DILexicalBlockFile(scope: !1870, file: !1, discriminator: 3)
!1879 = !DILocation(line: 401, column: 30, scope: !239)
!1880 = !DILocation(line: 401, column: 6, scope: !239)
!1881 = !DILocation(line: 401, column: 4, scope: !239)
!1882 = !DILocation(line: 403, column: 6, scope: !1883)
!1883 = distinct !DILexicalBlock(scope: !239, file: !1, line: 403, column: 6)
!1884 = !DILocation(line: 403, column: 14, scope: !1883)
!1885 = !DILocation(line: 403, column: 22, scope: !1883)
!1886 = !DILocation(line: 403, column: 26, scope: !1887)
!1887 = !DILexicalBlockFile(scope: !1883, file: !1, discriminator: 1)
!1888 = !DILocation(line: 403, column: 25, scope: !1887)
!1889 = !DILocation(line: 403, column: 34, scope: !1887)
!1890 = !DILocation(line: 403, column: 6, scope: !1887)
!1891 = !DILocation(line: 404, column: 23, scope: !1892)
!1892 = distinct !DILexicalBlock(scope: !1883, file: !1, line: 403, column: 44)
!1893 = !DILocation(line: 404, column: 26, scope: !1892)
!1894 = !DILocation(line: 404, column: 3, scope: !1892)
!1895 = !DILocation(line: 405, column: 3, scope: !1892)
!1896 = !DILocation(line: 407, column: 27, scope: !1897)
!1897 = distinct !DILexicalBlock(scope: !239, file: !1, line: 407, column: 6)
!1898 = !DILocation(line: 407, column: 32, scope: !1897)
!1899 = !DILocation(line: 407, column: 35, scope: !1897)
!1900 = !DILocation(line: 407, column: 48, scope: !1897)
!1901 = !DILocation(line: 407, column: 11, scope: !1897)
!1902 = !DILocation(line: 407, column: 9, scope: !1897)
!1903 = !DILocation(line: 407, column: 58, scope: !1897)
!1904 = !DILocation(line: 407, column: 6, scope: !239)
!1905 = !DILocation(line: 408, column: 11, scope: !1897)
!1906 = !DILocation(line: 408, column: 3, scope: !1897)
!1907 = !DILocation(line: 409, column: 2, scope: !239)
!1908 = !DILocation(line: 410, column: 1, scope: !239)
!1909 = !DILocalVariable(name: "_a", arg: 1, scope: !240, file: !1, line: 413, type: !23)
!1910 = !DILocation(line: 413, column: 57, scope: !240)
!1911 = !DILocalVariable(name: "pathname", arg: 2, scope: !240, file: !1, line: 414, type: !79)
!1912 = !DILocation(line: 414, column: 17, scope: !240)
!1913 = !DILocalVariable(name: "nullSeparator", arg: 3, scope: !240, file: !1, line: 414, type: !22)
!1914 = !DILocation(line: 414, column: 31, scope: !240)
!1915 = !DILocalVariable(name: "a", scope: !240, file: !1, line: 416, type: !4)
!1916 = !DILocation(line: 416, column: 24, scope: !240)
!1917 = !DILocation(line: 418, column: 2, scope: !240)
!1918 = !DILocalVariable(name: "magic_test", scope: !1919, file: !1, line: 418, type: !22)
!1919 = distinct !DILexicalBlock(scope: !240, file: !1, line: 418, column: 2)
!1920 = !DILocation(line: 418, column: 2, scope: !1919)
!1921 = !DILocation(line: 418, column: 2, scope: !1922)
!1922 = !DILexicalBlockFile(scope: !1919, file: !1, discriminator: 1)
!1923 = !DILocation(line: 418, column: 2, scope: !1924)
!1924 = !DILexicalBlockFile(scope: !1925, file: !1, discriminator: 2)
!1925 = distinct !DILexicalBlock(scope: !1919, file: !1, line: 418, column: 2)
!1926 = !DILocation(line: 418, column: 2, scope: !1927)
!1927 = !DILexicalBlockFile(scope: !1919, file: !1, discriminator: 3)
!1928 = !DILocation(line: 420, column: 30, scope: !240)
!1929 = !DILocation(line: 420, column: 6, scope: !240)
!1930 = !DILocation(line: 420, column: 4, scope: !240)
!1931 = !DILocation(line: 422, column: 31, scope: !240)
!1932 = !DILocation(line: 422, column: 36, scope: !240)
!1933 = !DILocation(line: 422, column: 39, scope: !240)
!1934 = !DILocation(line: 422, column: 55, scope: !240)
!1935 = !DILocation(line: 423, column: 3, scope: !240)
!1936 = !DILocation(line: 422, column: 9, scope: !240)
!1937 = !DILocation(line: 422, column: 2, scope: !240)
!1938 = !DILocation(line: 424, column: 1, scope: !240)
!1939 = !DILocalVariable(name: "_a", arg: 1, scope: !241, file: !1, line: 427, type: !23)
!1940 = !DILocation(line: 427, column: 59, scope: !241)
!1941 = !DILocalVariable(name: "pathname", arg: 2, scope: !241, file: !1, line: 428, type: !218)
!1942 = !DILocation(line: 428, column: 20, scope: !241)
!1943 = !DILocalVariable(name: "nullSeparator", arg: 3, scope: !241, file: !1, line: 428, type: !22)
!1944 = !DILocation(line: 428, column: 34, scope: !241)
!1945 = !DILocalVariable(name: "a", scope: !241, file: !1, line: 430, type: !4)
!1946 = !DILocation(line: 430, column: 24, scope: !241)
!1947 = !DILocation(line: 432, column: 2, scope: !241)
!1948 = !DILocalVariable(name: "magic_test", scope: !1949, file: !1, line: 432, type: !22)
!1949 = distinct !DILexicalBlock(scope: !241, file: !1, line: 432, column: 2)
!1950 = !DILocation(line: 432, column: 2, scope: !1949)
!1951 = !DILocation(line: 432, column: 2, scope: !1952)
!1952 = !DILexicalBlockFile(scope: !1949, file: !1, discriminator: 1)
!1953 = !DILocation(line: 432, column: 2, scope: !1954)
!1954 = !DILexicalBlockFile(scope: !1955, file: !1, discriminator: 2)
!1955 = distinct !DILexicalBlock(scope: !1949, file: !1, line: 432, column: 2)
!1956 = !DILocation(line: 432, column: 2, scope: !1957)
!1957 = !DILexicalBlockFile(scope: !1949, file: !1, discriminator: 3)
!1958 = !DILocation(line: 434, column: 30, scope: !241)
!1959 = !DILocation(line: 434, column: 6, scope: !241)
!1960 = !DILocation(line: 434, column: 4, scope: !241)
!1961 = !DILocation(line: 436, column: 31, scope: !241)
!1962 = !DILocation(line: 436, column: 36, scope: !241)
!1963 = !DILocation(line: 436, column: 39, scope: !241)
!1964 = !DILocation(line: 436, column: 55, scope: !241)
!1965 = !DILocation(line: 437, column: 3, scope: !241)
!1966 = !DILocation(line: 436, column: 9, scope: !241)
!1967 = !DILocation(line: 436, column: 2, scope: !241)
!1968 = !DILocation(line: 438, column: 1, scope: !241)
!1969 = !DILocalVariable(name: "_a", arg: 1, scope: !242, file: !1, line: 448, type: !23)
!1970 = !DILocation(line: 448, column: 45, scope: !242)
!1971 = !DILocalVariable(name: "entry", arg: 2, scope: !242, file: !1, line: 449, type: !29)
!1972 = !DILocation(line: 449, column: 27, scope: !242)
!1973 = !DILocalVariable(name: "a", scope: !242, file: !1, line: 451, type: !4)
!1974 = !DILocation(line: 451, column: 24, scope: !242)
!1975 = !DILocation(line: 453, column: 2, scope: !242)
!1976 = !DILocalVariable(name: "magic_test", scope: !1977, file: !1, line: 453, type: !22)
!1977 = distinct !DILexicalBlock(scope: !242, file: !1, line: 453, column: 2)
!1978 = !DILocation(line: 453, column: 2, scope: !1977)
!1979 = !DILocation(line: 453, column: 2, scope: !1980)
!1980 = !DILexicalBlockFile(scope: !1977, file: !1, discriminator: 1)
!1981 = !DILocation(line: 453, column: 2, scope: !1982)
!1982 = !DILexicalBlockFile(scope: !1983, file: !1, discriminator: 2)
!1983 = distinct !DILexicalBlock(scope: !1977, file: !1, line: 453, column: 2)
!1984 = !DILocation(line: 453, column: 2, scope: !1985)
!1985 = !DILexicalBlockFile(scope: !1977, file: !1, discriminator: 3)
!1986 = !DILocation(line: 456, column: 30, scope: !242)
!1987 = !DILocation(line: 456, column: 6, scope: !242)
!1988 = !DILocation(line: 456, column: 4, scope: !242)
!1989 = !DILocation(line: 457, column: 6, scope: !1990)
!1990 = distinct !DILexicalBlock(scope: !242, file: !1, line: 457, column: 6)
!1991 = !DILocation(line: 457, column: 12, scope: !1990)
!1992 = !DILocation(line: 457, column: 6, scope: !242)
!1993 = !DILocation(line: 458, column: 23, scope: !1994)
!1994 = distinct !DILexicalBlock(scope: !1990, file: !1, line: 457, column: 21)
!1995 = !DILocation(line: 458, column: 26, scope: !1994)
!1996 = !DILocation(line: 458, column: 3, scope: !1994)
!1997 = !DILocation(line: 459, column: 3, scope: !1994)
!1998 = !DILocation(line: 464, column: 7, scope: !1999)
!1999 = distinct !DILexicalBlock(scope: !242, file: !1, line: 464, column: 6)
!2000 = !DILocation(line: 464, column: 10, scope: !1999)
!2001 = !DILocation(line: 464, column: 18, scope: !1999)
!2002 = !DILocation(line: 464, column: 36, scope: !1999)
!2003 = !DILocation(line: 464, column: 6, scope: !242)
!2004 = !DILocation(line: 465, column: 3, scope: !1999)
!2005 = !DILocation(line: 469, column: 24, scope: !242)
!2006 = !DILocation(line: 469, column: 53, scope: !242)
!2007 = !DILocation(line: 469, column: 30, scope: !242)
!2008 = !DILocation(line: 469, column: 10, scope: !2009)
!2009 = !DILexicalBlockFile(scope: !242, file: !1, discriminator: 1)
!2010 = !DILocation(line: 469, column: 2, scope: !242)
!2011 = !DILocation(line: 471, column: 1, scope: !242)
!2012 = !DILocalVariable(name: "_a", arg: 1, scope: !243, file: !1, line: 477, type: !23)
!2013 = !DILocation(line: 477, column: 57, scope: !243)
!2014 = !DILocalVariable(name: "a", scope: !243, file: !1, line: 479, type: !4)
!2015 = !DILocation(line: 479, column: 24, scope: !243)
!2016 = !DILocation(line: 481, column: 2, scope: !243)
!2017 = !DILocalVariable(name: "magic_test", scope: !2018, file: !1, line: 481, type: !22)
!2018 = distinct !DILexicalBlock(scope: !243, file: !1, line: 481, column: 2)
!2019 = !DILocation(line: 481, column: 2, scope: !2018)
!2020 = !DILocation(line: 481, column: 2, scope: !2021)
!2021 = !DILexicalBlockFile(scope: !2018, file: !1, discriminator: 1)
!2022 = !DILocation(line: 481, column: 2, scope: !2023)
!2023 = !DILexicalBlockFile(scope: !2024, file: !1, discriminator: 2)
!2024 = distinct !DILexicalBlock(scope: !2018, file: !1, line: 481, column: 2)
!2025 = !DILocation(line: 481, column: 2, scope: !2026)
!2026 = !DILexicalBlockFile(scope: !2018, file: !1, discriminator: 3)
!2027 = !DILocation(line: 483, column: 30, scope: !243)
!2028 = !DILocation(line: 483, column: 6, scope: !243)
!2029 = !DILocation(line: 483, column: 4, scope: !243)
!2030 = !DILocation(line: 485, column: 10, scope: !243)
!2031 = !DILocation(line: 485, column: 13, scope: !243)
!2032 = !DILocation(line: 485, column: 24, scope: !243)
!2033 = !DILocation(line: 485, column: 2, scope: !243)
!2034 = !DILocation(line: 486, column: 1, scope: !243)
!2035 = !DILocalVariable(name: "_a", arg: 1, scope: !244, file: !1, line: 489, type: !23)
!2036 = !DILocation(line: 489, column: 62, scope: !244)
!2037 = !DILocalVariable(name: "_p", arg: 2, scope: !244, file: !1, line: 490, type: !247)
!2038 = !DILocation(line: 490, column: 18, scope: !244)
!2039 = !DILocalVariable(name: "a", scope: !244, file: !1, line: 492, type: !4)
!2040 = !DILocation(line: 492, column: 24, scope: !244)
!2041 = !DILocalVariable(name: "v", scope: !244, file: !1, line: 493, type: !42)
!2042 = !DILocation(line: 493, column: 14, scope: !244)
!2043 = !DILocalVariable(name: "r", scope: !244, file: !1, line: 494, type: !22)
!2044 = !DILocation(line: 494, column: 6, scope: !244)
!2045 = !DILocation(line: 496, column: 2, scope: !244)
!2046 = !DILocalVariable(name: "magic_test", scope: !2047, file: !1, line: 496, type: !22)
!2047 = distinct !DILexicalBlock(scope: !244, file: !1, line: 496, column: 2)
!2048 = !DILocation(line: 496, column: 2, scope: !2047)
!2049 = !DILocation(line: 496, column: 2, scope: !2050)
!2050 = !DILexicalBlockFile(scope: !2047, file: !1, discriminator: 1)
!2051 = !DILocation(line: 496, column: 2, scope: !2052)
!2052 = !DILexicalBlockFile(scope: !2053, file: !1, discriminator: 2)
!2053 = distinct !DILexicalBlock(scope: !2047, file: !1, line: 496, column: 2)
!2054 = !DILocation(line: 496, column: 2, scope: !2055)
!2055 = !DILexicalBlockFile(scope: !2047, file: !1, discriminator: 3)
!2056 = !DILocation(line: 498, column: 30, scope: !244)
!2057 = !DILocation(line: 498, column: 6, scope: !244)
!2058 = !DILocation(line: 498, column: 4, scope: !244)
!2059 = !DILocation(line: 500, column: 43, scope: !244)
!2060 = !DILocation(line: 500, column: 48, scope: !244)
!2061 = !DILocation(line: 500, column: 51, scope: !244)
!2062 = !DILocation(line: 500, column: 6, scope: !244)
!2063 = !DILocation(line: 500, column: 4, scope: !244)
!2064 = !DILocation(line: 501, column: 22, scope: !244)
!2065 = !DILocation(line: 501, column: 3, scope: !244)
!2066 = !DILocation(line: 501, column: 6, scope: !244)
!2067 = !DILocation(line: 502, column: 10, scope: !244)
!2068 = !DILocation(line: 502, column: 2, scope: !244)
!2069 = !DILocation(line: 503, column: 1, scope: !244)
!2070 = !DILocalVariable(name: "a", arg: 1, scope: !305, file: !1, line: 835, type: !4)
!2071 = !DILocation(line: 835, column: 60, scope: !305)
!2072 = !DILocalVariable(name: "list", arg: 2, scope: !305, file: !1, line: 836, type: !281)
!2073 = !DILocation(line: 836, column: 24, scope: !305)
!2074 = !DILocalVariable(name: "mbs", arg: 3, scope: !305, file: !1, line: 836, type: !22)
!2075 = !DILocation(line: 836, column: 34, scope: !305)
!2076 = !DILocalVariable(name: "vp", arg: 4, scope: !305, file: !1, line: 836, type: !63)
!2077 = !DILocation(line: 836, column: 52, scope: !305)
!2078 = !DILocalVariable(name: "m", scope: !305, file: !1, line: 838, type: !114)
!2079 = !DILocation(line: 838, column: 16, scope: !305)
!2080 = !DILocation(line: 840, column: 3, scope: !305)
!2081 = !DILocation(line: 840, column: 6, scope: !305)
!2082 = !DILocation(line: 841, column: 6, scope: !2083)
!2083 = distinct !DILexicalBlock(scope: !305, file: !1, line: 841, column: 6)
!2084 = !DILocation(line: 841, column: 12, scope: !2083)
!2085 = !DILocation(line: 841, column: 6, scope: !305)
!2086 = !DILocation(line: 842, column: 3, scope: !2087)
!2087 = distinct !DILexicalBlock(scope: !2083, file: !1, line: 841, column: 27)
!2088 = !DILocation(line: 842, column: 9, scope: !2087)
!2089 = !DILocation(line: 842, column: 23, scope: !2087)
!2090 = !DILocation(line: 843, column: 3, scope: !2087)
!2091 = !DILocation(line: 845, column: 6, scope: !2092)
!2092 = distinct !DILexicalBlock(scope: !305, file: !1, line: 845, column: 6)
!2093 = !DILocation(line: 845, column: 12, scope: !2092)
!2094 = !DILocation(line: 845, column: 27, scope: !2092)
!2095 = !DILocation(line: 845, column: 6, scope: !305)
!2096 = !DILocation(line: 846, column: 7, scope: !2097)
!2097 = distinct !DILexicalBlock(scope: !2098, file: !1, line: 846, column: 7)
!2098 = distinct !DILexicalBlock(scope: !2092, file: !1, line: 845, column: 36)
!2099 = !DILocation(line: 846, column: 13, scope: !2097)
!2100 = !DILocation(line: 846, column: 29, scope: !2097)
!2101 = !DILocation(line: 846, column: 7, scope: !2098)
!2102 = !DILocation(line: 847, column: 4, scope: !2097)
!2103 = !DILocation(line: 848, column: 26, scope: !2098)
!2104 = !DILocation(line: 848, column: 32, scope: !2098)
!2105 = !DILocation(line: 848, column: 3, scope: !2098)
!2106 = !DILocation(line: 848, column: 9, scope: !2098)
!2107 = !DILocation(line: 848, column: 24, scope: !2098)
!2108 = !DILocation(line: 849, column: 2, scope: !2098)
!2109 = !DILocation(line: 851, column: 11, scope: !2110)
!2110 = distinct !DILexicalBlock(scope: !305, file: !1, line: 851, column: 2)
!2111 = !DILocation(line: 851, column: 17, scope: !2110)
!2112 = !DILocation(line: 851, column: 9, scope: !2110)
!2113 = !DILocation(line: 851, column: 7, scope: !2110)
!2114 = !DILocation(line: 851, column: 33, scope: !2115)
!2115 = !DILexicalBlockFile(scope: !2116, file: !1, discriminator: 1)
!2116 = distinct !DILexicalBlock(scope: !2110, file: !1, line: 851, column: 2)
!2117 = !DILocation(line: 851, column: 35, scope: !2115)
!2118 = !DILocation(line: 851, column: 2, scope: !2115)
!2119 = !DILocalVariable(name: "r", scope: !2120, file: !1, line: 852, type: !22)
!2120 = distinct !DILexicalBlock(scope: !2116, file: !1, line: 851, column: 57)
!2121 = !DILocation(line: 852, column: 7, scope: !2120)
!2122 = !DILocation(line: 854, column: 7, scope: !2123)
!2123 = distinct !DILexicalBlock(scope: !2120, file: !1, line: 854, column: 7)
!2124 = !DILocation(line: 854, column: 10, scope: !2123)
!2125 = !DILocation(line: 854, column: 7, scope: !2120)
!2126 = !DILocation(line: 855, column: 4, scope: !2123)
!2127 = !DILocation(line: 856, column: 7, scope: !2128)
!2128 = distinct !DILexicalBlock(scope: !2120, file: !1, line: 856, column: 7)
!2129 = !DILocation(line: 856, column: 7, scope: !2120)
!2130 = !DILocalVariable(name: "p", scope: !2131, file: !1, line: 857, type: !79)
!2131 = distinct !DILexicalBlock(scope: !2128, file: !1, line: 856, column: 12)
!2132 = !DILocation(line: 857, column: 16, scope: !2131)
!2133 = !DILocation(line: 858, column: 34, scope: !2131)
!2134 = !DILocation(line: 858, column: 37, scope: !2131)
!2135 = !DILocation(line: 859, column: 7, scope: !2131)
!2136 = !DILocation(line: 859, column: 10, scope: !2131)
!2137 = !DILocation(line: 858, column: 8, scope: !2131)
!2138 = !DILocation(line: 858, column: 6, scope: !2131)
!2139 = !DILocation(line: 860, column: 8, scope: !2140)
!2140 = distinct !DILexicalBlock(scope: !2131, file: !1, line: 860, column: 8)
!2141 = !DILocation(line: 860, column: 10, scope: !2140)
!2142 = !DILocation(line: 860, column: 14, scope: !2140)
!2143 = !DILocation(line: 860, column: 17, scope: !2144)
!2144 = !DILexicalBlockFile(scope: !2140, file: !1, discriminator: 1)
!2145 = !DILocation(line: 860, column: 23, scope: !2144)
!2146 = !DILocation(line: 860, column: 8, scope: !2144)
!2147 = !DILocation(line: 861, column: 25, scope: !2140)
!2148 = !DILocation(line: 861, column: 13, scope: !2140)
!2149 = !DILocation(line: 861, column: 5, scope: !2140)
!2150 = !DILocation(line: 862, column: 8, scope: !2151)
!2151 = distinct !DILexicalBlock(scope: !2131, file: !1, line: 862, column: 8)
!2152 = !DILocation(line: 862, column: 10, scope: !2151)
!2153 = !DILocation(line: 862, column: 8, scope: !2131)
!2154 = !DILocation(line: 863, column: 7, scope: !2151)
!2155 = !DILocation(line: 863, column: 5, scope: !2151)
!2156 = !DILocation(line: 864, column: 10, scope: !2131)
!2157 = !DILocation(line: 864, column: 5, scope: !2131)
!2158 = !DILocation(line: 864, column: 8, scope: !2131)
!2159 = !DILocation(line: 865, column: 3, scope: !2131)
!2160 = !DILocalVariable(name: "p", scope: !2161, file: !1, line: 866, type: !218)
!2161 = distinct !DILexicalBlock(scope: !2128, file: !1, line: 865, column: 10)
!2162 = !DILocation(line: 866, column: 19, scope: !2161)
!2163 = !DILocation(line: 867, column: 34, scope: !2161)
!2164 = !DILocation(line: 867, column: 37, scope: !2161)
!2165 = !DILocation(line: 868, column: 7, scope: !2161)
!2166 = !DILocation(line: 868, column: 10, scope: !2161)
!2167 = !DILocation(line: 867, column: 8, scope: !2161)
!2168 = !DILocation(line: 867, column: 6, scope: !2161)
!2169 = !DILocation(line: 869, column: 8, scope: !2170)
!2170 = distinct !DILexicalBlock(scope: !2161, file: !1, line: 869, column: 8)
!2171 = !DILocation(line: 869, column: 10, scope: !2170)
!2172 = !DILocation(line: 869, column: 14, scope: !2170)
!2173 = !DILocation(line: 869, column: 17, scope: !2174)
!2174 = !DILexicalBlockFile(scope: !2170, file: !1, discriminator: 1)
!2175 = !DILocation(line: 869, column: 23, scope: !2174)
!2176 = !DILocation(line: 869, column: 8, scope: !2174)
!2177 = !DILocation(line: 870, column: 25, scope: !2170)
!2178 = !DILocation(line: 870, column: 13, scope: !2170)
!2179 = !DILocation(line: 870, column: 5, scope: !2170)
!2180 = !DILocation(line: 871, column: 8, scope: !2181)
!2181 = distinct !DILexicalBlock(scope: !2161, file: !1, line: 871, column: 8)
!2182 = !DILocation(line: 871, column: 10, scope: !2181)
!2183 = !DILocation(line: 871, column: 8, scope: !2161)
!2184 = !DILocation(line: 872, column: 7, scope: !2181)
!2185 = !DILocation(line: 872, column: 5, scope: !2181)
!2186 = !DILocation(line: 873, column: 10, scope: !2161)
!2187 = !DILocation(line: 873, column: 5, scope: !2161)
!2188 = !DILocation(line: 873, column: 8, scope: !2161)
!2189 = !DILocation(line: 875, column: 26, scope: !2120)
!2190 = !DILocation(line: 875, column: 29, scope: !2120)
!2191 = !DILocation(line: 875, column: 3, scope: !2120)
!2192 = !DILocation(line: 875, column: 9, scope: !2120)
!2193 = !DILocation(line: 875, column: 24, scope: !2120)
!2194 = !DILocation(line: 876, column: 7, scope: !2195)
!2195 = distinct !DILexicalBlock(scope: !2120, file: !1, line: 876, column: 7)
!2196 = !DILocation(line: 876, column: 13, scope: !2195)
!2197 = !DILocation(line: 876, column: 28, scope: !2195)
!2198 = !DILocation(line: 876, column: 7, scope: !2120)
!2199 = !DILocation(line: 878, column: 4, scope: !2195)
!2200 = !DILocation(line: 878, column: 10, scope: !2195)
!2201 = !DILocation(line: 878, column: 24, scope: !2195)
!2202 = !DILocation(line: 879, column: 3, scope: !2120)
!2203 = !DILocation(line: 851, column: 48, scope: !2204)
!2204 = !DILexicalBlockFile(scope: !2116, file: !1, discriminator: 2)
!2205 = !DILocation(line: 851, column: 51, scope: !2204)
!2206 = !DILocation(line: 851, column: 46, scope: !2204)
!2207 = !DILocation(line: 851, column: 2, scope: !2204)
!2208 = !DILocation(line: 881, column: 2, scope: !305)
!2209 = !DILocation(line: 881, column: 8, scope: !305)
!2210 = !DILocation(line: 881, column: 23, scope: !305)
!2211 = !DILocation(line: 882, column: 2, scope: !305)
!2212 = !DILocation(line: 883, column: 1, scope: !305)
!2213 = !DILocalVariable(name: "_a", arg: 1, scope: !248, file: !1, line: 506, type: !23)
!2214 = !DILocation(line: 506, column: 64, scope: !248)
!2215 = !DILocalVariable(name: "_p", arg: 2, scope: !248, file: !1, line: 507, type: !251)
!2216 = !DILocation(line: 507, column: 21, scope: !248)
!2217 = !DILocalVariable(name: "a", scope: !248, file: !1, line: 509, type: !4)
!2218 = !DILocation(line: 509, column: 24, scope: !248)
!2219 = !DILocalVariable(name: "v", scope: !248, file: !1, line: 510, type: !42)
!2220 = !DILocation(line: 510, column: 14, scope: !248)
!2221 = !DILocalVariable(name: "r", scope: !248, file: !1, line: 511, type: !22)
!2222 = !DILocation(line: 511, column: 6, scope: !248)
!2223 = !DILocation(line: 513, column: 2, scope: !248)
!2224 = !DILocalVariable(name: "magic_test", scope: !2225, file: !1, line: 513, type: !22)
!2225 = distinct !DILexicalBlock(scope: !248, file: !1, line: 513, column: 2)
!2226 = !DILocation(line: 513, column: 2, scope: !2225)
!2227 = !DILocation(line: 513, column: 2, scope: !2228)
!2228 = !DILexicalBlockFile(scope: !2225, file: !1, discriminator: 1)
!2229 = !DILocation(line: 513, column: 2, scope: !2230)
!2230 = !DILexicalBlockFile(scope: !2231, file: !1, discriminator: 2)
!2231 = distinct !DILexicalBlock(scope: !2225, file: !1, line: 513, column: 2)
!2232 = !DILocation(line: 513, column: 2, scope: !2233)
!2233 = !DILexicalBlockFile(scope: !2225, file: !1, discriminator: 3)
!2234 = !DILocation(line: 515, column: 30, scope: !248)
!2235 = !DILocation(line: 515, column: 6, scope: !248)
!2236 = !DILocation(line: 515, column: 4, scope: !248)
!2237 = !DILocation(line: 517, column: 43, scope: !248)
!2238 = !DILocation(line: 517, column: 48, scope: !248)
!2239 = !DILocation(line: 517, column: 51, scope: !248)
!2240 = !DILocation(line: 517, column: 6, scope: !248)
!2241 = !DILocation(line: 517, column: 4, scope: !248)
!2242 = !DILocation(line: 518, column: 25, scope: !248)
!2243 = !DILocation(line: 518, column: 8, scope: !248)
!2244 = !DILocation(line: 518, column: 3, scope: !248)
!2245 = !DILocation(line: 518, column: 6, scope: !248)
!2246 = !DILocation(line: 519, column: 10, scope: !248)
!2247 = !DILocation(line: 519, column: 2, scope: !248)
!2248 = !DILocation(line: 520, column: 1, scope: !248)
!2249 = !DILocalVariable(name: "_a", arg: 1, scope: !252, file: !1, line: 889, type: !23)
!2250 = !DILocation(line: 889, column: 44, scope: !252)
!2251 = !DILocalVariable(name: "flag", arg: 2, scope: !252, file: !1, line: 889, type: !22)
!2252 = !DILocation(line: 889, column: 52, scope: !252)
!2253 = !DILocalVariable(name: "sec", arg: 3, scope: !252, file: !1, line: 889, type: !142)
!2254 = !DILocation(line: 889, column: 65, scope: !252)
!2255 = !DILocalVariable(name: "nsec", arg: 4, scope: !252, file: !1, line: 890, type: !41)
!2256 = !DILocation(line: 890, column: 10, scope: !252)
!2257 = !DILocalVariable(name: "r", scope: !252, file: !1, line: 892, type: !22)
!2258 = !DILocation(line: 892, column: 6, scope: !252)
!2259 = !DILocation(line: 894, column: 25, scope: !252)
!2260 = !DILocation(line: 894, column: 29, scope: !252)
!2261 = !DILocation(line: 894, column: 6, scope: !252)
!2262 = !DILocation(line: 894, column: 4, scope: !252)
!2263 = !DILocation(line: 895, column: 6, scope: !2264)
!2264 = distinct !DILexicalBlock(scope: !252, file: !1, line: 895, column: 6)
!2265 = !DILocation(line: 895, column: 8, scope: !2264)
!2266 = !DILocation(line: 895, column: 6, scope: !252)
!2267 = !DILocation(line: 896, column: 11, scope: !2264)
!2268 = !DILocation(line: 896, column: 3, scope: !2264)
!2269 = !DILocation(line: 897, column: 48, scope: !252)
!2270 = !DILocation(line: 897, column: 24, scope: !252)
!2271 = !DILocation(line: 897, column: 52, scope: !252)
!2272 = !DILocation(line: 898, column: 4, scope: !252)
!2273 = !DILocation(line: 898, column: 9, scope: !252)
!2274 = !DILocation(line: 898, column: 15, scope: !252)
!2275 = !DILocation(line: 898, column: 20, scope: !252)
!2276 = !DILocation(line: 897, column: 9, scope: !252)
!2277 = !DILocation(line: 897, column: 2, scope: !252)
!2278 = !DILocation(line: 899, column: 1, scope: !252)
!2279 = !DILocalVariable(name: "_a", arg: 1, scope: !308, file: !1, line: 1003, type: !23)
!2280 = !DILocation(line: 1003, column: 36, scope: !308)
!2281 = !DILocalVariable(name: "flag", arg: 2, scope: !308, file: !1, line: 1003, type: !22)
!2282 = !DILocation(line: 1003, column: 44, scope: !308)
!2283 = !DILocalVariable(name: "_fn", arg: 3, scope: !308, file: !1, line: 1003, type: !79)
!2284 = !DILocation(line: 1003, column: 62, scope: !308)
!2285 = !DILocation(line: 1005, column: 2, scope: !308)
!2286 = !DILocalVariable(name: "magic_test", scope: !2287, file: !1, line: 1005, type: !22)
!2287 = distinct !DILexicalBlock(scope: !308, file: !1, line: 1005, column: 2)
!2288 = !DILocation(line: 1005, column: 2, scope: !2287)
!2289 = !DILocation(line: 1005, column: 2, scope: !2290)
!2290 = !DILexicalBlockFile(scope: !2287, file: !1, discriminator: 1)
!2291 = !DILocation(line: 1005, column: 2, scope: !2292)
!2292 = !DILexicalBlockFile(scope: !2293, file: !1, discriminator: 2)
!2293 = distinct !DILexicalBlock(scope: !2287, file: !1, line: 1005, column: 2)
!2294 = !DILocation(line: 1005, column: 2, scope: !2295)
!2295 = !DILexicalBlockFile(scope: !2287, file: !1, discriminator: 3)
!2296 = !DILocation(line: 1009, column: 6, scope: !2297)
!2297 = distinct !DILexicalBlock(scope: !308, file: !1, line: 1009, column: 6)
!2298 = !DILocation(line: 1009, column: 11, scope: !2297)
!2299 = !DILocation(line: 1009, column: 6, scope: !308)
!2300 = !DILocation(line: 1011, column: 21, scope: !2301)
!2301 = distinct !DILexicalBlock(scope: !2297, file: !1, line: 1010, column: 64)
!2302 = !DILocation(line: 1011, column: 3, scope: !2301)
!2303 = !DILocation(line: 1012, column: 3, scope: !2301)
!2304 = !DILocation(line: 1014, column: 7, scope: !2305)
!2305 = distinct !DILexicalBlock(scope: !308, file: !1, line: 1014, column: 6)
!2306 = !DILocation(line: 1014, column: 12, scope: !2305)
!2307 = !DILocation(line: 1014, column: 59, scope: !2305)
!2308 = !DILocation(line: 1014, column: 6, scope: !308)
!2309 = !DILocation(line: 1015, column: 21, scope: !2310)
!2310 = distinct !DILexicalBlock(scope: !2305, file: !1, line: 1014, column: 65)
!2311 = !DILocation(line: 1015, column: 3, scope: !2310)
!2312 = !DILocation(line: 1016, column: 3, scope: !2310)
!2313 = !DILocation(line: 1020, column: 6, scope: !2314)
!2314 = distinct !DILexicalBlock(scope: !308, file: !1, line: 1020, column: 6)
!2315 = !DILocation(line: 1020, column: 11, scope: !2314)
!2316 = !DILocation(line: 1020, column: 6, scope: !308)
!2317 = !DILocation(line: 1023, column: 21, scope: !2318)
!2318 = distinct !DILexicalBlock(scope: !2314, file: !1, line: 1022, column: 39)
!2319 = !DILocation(line: 1023, column: 3, scope: !2318)
!2320 = !DILocation(line: 1024, column: 3, scope: !2318)
!2321 = !DILocation(line: 1026, column: 7, scope: !2322)
!2322 = distinct !DILexicalBlock(scope: !308, file: !1, line: 1026, column: 6)
!2323 = !DILocation(line: 1026, column: 12, scope: !2322)
!2324 = !DILocation(line: 1027, column: 30, scope: !2322)
!2325 = !DILocation(line: 1026, column: 6, scope: !308)
!2326 = !DILocation(line: 1028, column: 21, scope: !2327)
!2327 = distinct !DILexicalBlock(scope: !2322, file: !1, line: 1027, column: 36)
!2328 = !DILocation(line: 1028, column: 3, scope: !2327)
!2329 = !DILocation(line: 1029, column: 3, scope: !2327)
!2330 = !DILocation(line: 1032, column: 2, scope: !308)
!2331 = !DILocation(line: 1033, column: 1, scope: !308)
!2332 = !DILocalVariable(name: "a", arg: 1, scope: !309, file: !1, line: 1038, type: !4)
!2333 = !DILocation(line: 1038, column: 38, scope: !309)
!2334 = !DILocalVariable(name: "timetype", arg: 2, scope: !309, file: !1, line: 1038, type: !22)
!2335 = !DILocation(line: 1038, column: 45, scope: !309)
!2336 = !DILocalVariable(name: "mtime_sec", arg: 3, scope: !309, file: !1, line: 1039, type: !142)
!2337 = !DILocation(line: 1039, column: 12, scope: !309)
!2338 = !DILocalVariable(name: "mtime_nsec", arg: 4, scope: !309, file: !1, line: 1039, type: !41)
!2339 = !DILocation(line: 1039, column: 28, scope: !309)
!2340 = !DILocalVariable(name: "ctime_sec", arg: 5, scope: !309, file: !1, line: 1039, type: !142)
!2341 = !DILocation(line: 1039, column: 47, scope: !309)
!2342 = !DILocalVariable(name: "ctime_nsec", arg: 6, scope: !309, file: !1, line: 1039, type: !41)
!2343 = !DILocation(line: 1039, column: 63, scope: !309)
!2344 = !DILocation(line: 1041, column: 6, scope: !2345)
!2345 = distinct !DILexicalBlock(scope: !309, file: !1, line: 1041, column: 6)
!2346 = !DILocation(line: 1041, column: 15, scope: !2345)
!2347 = !DILocation(line: 1041, column: 6, scope: !309)
!2348 = !DILocation(line: 1042, column: 8, scope: !2349)
!2349 = distinct !DILexicalBlock(scope: !2350, file: !1, line: 1042, column: 7)
!2350 = distinct !DILexicalBlock(scope: !2345, file: !1, line: 1041, column: 38)
!2351 = !DILocation(line: 1042, column: 17, scope: !2349)
!2352 = !DILocation(line: 1042, column: 40, scope: !2349)
!2353 = !DILocation(line: 1042, column: 43, scope: !2354)
!2354 = !DILexicalBlockFile(scope: !2349, file: !1, discriminator: 1)
!2355 = !DILocation(line: 1042, column: 7, scope: !2354)
!2356 = !DILocation(line: 1043, column: 28, scope: !2357)
!2357 = distinct !DILexicalBlock(scope: !2349, file: !1, line: 1042, column: 65)
!2358 = !DILocation(line: 1043, column: 4, scope: !2357)
!2359 = !DILocation(line: 1043, column: 7, scope: !2357)
!2360 = !DILocation(line: 1043, column: 26, scope: !2357)
!2361 = !DILocation(line: 1044, column: 25, scope: !2357)
!2362 = !DILocation(line: 1044, column: 4, scope: !2357)
!2363 = !DILocation(line: 1044, column: 7, scope: !2357)
!2364 = !DILocation(line: 1044, column: 23, scope: !2357)
!2365 = !DILocation(line: 1045, column: 26, scope: !2357)
!2366 = !DILocation(line: 1045, column: 4, scope: !2357)
!2367 = !DILocation(line: 1045, column: 7, scope: !2357)
!2368 = !DILocation(line: 1045, column: 24, scope: !2357)
!2369 = !DILocation(line: 1046, column: 4, scope: !2357)
!2370 = !DILocation(line: 1046, column: 7, scope: !2357)
!2371 = !DILocation(line: 1046, column: 15, scope: !2357)
!2372 = !DILocation(line: 1047, column: 3, scope: !2357)
!2373 = !DILocation(line: 1048, column: 8, scope: !2374)
!2374 = distinct !DILexicalBlock(scope: !2350, file: !1, line: 1048, column: 7)
!2375 = !DILocation(line: 1048, column: 17, scope: !2374)
!2376 = !DILocation(line: 1048, column: 40, scope: !2374)
!2377 = !DILocation(line: 1048, column: 43, scope: !2378)
!2378 = !DILexicalBlockFile(scope: !2374, file: !1, discriminator: 1)
!2379 = !DILocation(line: 1048, column: 7, scope: !2378)
!2380 = !DILocation(line: 1049, column: 28, scope: !2381)
!2381 = distinct !DILexicalBlock(scope: !2374, file: !1, line: 1048, column: 65)
!2382 = !DILocation(line: 1049, column: 4, scope: !2381)
!2383 = !DILocation(line: 1049, column: 7, scope: !2381)
!2384 = !DILocation(line: 1049, column: 26, scope: !2381)
!2385 = !DILocation(line: 1050, column: 25, scope: !2381)
!2386 = !DILocation(line: 1050, column: 4, scope: !2381)
!2387 = !DILocation(line: 1050, column: 7, scope: !2381)
!2388 = !DILocation(line: 1050, column: 23, scope: !2381)
!2389 = !DILocation(line: 1051, column: 26, scope: !2381)
!2390 = !DILocation(line: 1051, column: 4, scope: !2381)
!2391 = !DILocation(line: 1051, column: 7, scope: !2381)
!2392 = !DILocation(line: 1051, column: 24, scope: !2381)
!2393 = !DILocation(line: 1052, column: 4, scope: !2381)
!2394 = !DILocation(line: 1052, column: 7, scope: !2381)
!2395 = !DILocation(line: 1052, column: 15, scope: !2381)
!2396 = !DILocation(line: 1053, column: 3, scope: !2381)
!2397 = !DILocation(line: 1054, column: 2, scope: !2350)
!2398 = !DILocation(line: 1055, column: 6, scope: !2399)
!2399 = distinct !DILexicalBlock(scope: !309, file: !1, line: 1055, column: 6)
!2400 = !DILocation(line: 1055, column: 15, scope: !2399)
!2401 = !DILocation(line: 1055, column: 6, scope: !309)
!2402 = !DILocation(line: 1056, column: 8, scope: !2403)
!2403 = distinct !DILexicalBlock(scope: !2404, file: !1, line: 1056, column: 7)
!2404 = distinct !DILexicalBlock(scope: !2399, file: !1, line: 1055, column: 38)
!2405 = !DILocation(line: 1056, column: 17, scope: !2403)
!2406 = !DILocation(line: 1056, column: 40, scope: !2403)
!2407 = !DILocation(line: 1056, column: 43, scope: !2408)
!2408 = !DILexicalBlockFile(scope: !2403, file: !1, discriminator: 1)
!2409 = !DILocation(line: 1056, column: 7, scope: !2408)
!2410 = !DILocation(line: 1057, column: 28, scope: !2411)
!2411 = distinct !DILexicalBlock(scope: !2403, file: !1, line: 1056, column: 65)
!2412 = !DILocation(line: 1057, column: 4, scope: !2411)
!2413 = !DILocation(line: 1057, column: 7, scope: !2411)
!2414 = !DILocation(line: 1057, column: 26, scope: !2411)
!2415 = !DILocation(line: 1058, column: 25, scope: !2411)
!2416 = !DILocation(line: 1058, column: 4, scope: !2411)
!2417 = !DILocation(line: 1058, column: 7, scope: !2411)
!2418 = !DILocation(line: 1058, column: 23, scope: !2411)
!2419 = !DILocation(line: 1059, column: 26, scope: !2411)
!2420 = !DILocation(line: 1059, column: 4, scope: !2411)
!2421 = !DILocation(line: 1059, column: 7, scope: !2411)
!2422 = !DILocation(line: 1059, column: 24, scope: !2411)
!2423 = !DILocation(line: 1060, column: 4, scope: !2411)
!2424 = !DILocation(line: 1060, column: 7, scope: !2411)
!2425 = !DILocation(line: 1060, column: 15, scope: !2411)
!2426 = !DILocation(line: 1061, column: 3, scope: !2411)
!2427 = !DILocation(line: 1062, column: 8, scope: !2428)
!2428 = distinct !DILexicalBlock(scope: !2404, file: !1, line: 1062, column: 7)
!2429 = !DILocation(line: 1062, column: 17, scope: !2428)
!2430 = !DILocation(line: 1062, column: 40, scope: !2428)
!2431 = !DILocation(line: 1062, column: 43, scope: !2432)
!2432 = !DILexicalBlockFile(scope: !2428, file: !1, discriminator: 1)
!2433 = !DILocation(line: 1062, column: 7, scope: !2432)
!2434 = !DILocation(line: 1063, column: 28, scope: !2435)
!2435 = distinct !DILexicalBlock(scope: !2428, file: !1, line: 1062, column: 65)
!2436 = !DILocation(line: 1063, column: 4, scope: !2435)
!2437 = !DILocation(line: 1063, column: 7, scope: !2435)
!2438 = !DILocation(line: 1063, column: 26, scope: !2435)
!2439 = !DILocation(line: 1064, column: 25, scope: !2435)
!2440 = !DILocation(line: 1064, column: 4, scope: !2435)
!2441 = !DILocation(line: 1064, column: 7, scope: !2435)
!2442 = !DILocation(line: 1064, column: 23, scope: !2435)
!2443 = !DILocation(line: 1065, column: 26, scope: !2435)
!2444 = !DILocation(line: 1065, column: 4, scope: !2435)
!2445 = !DILocation(line: 1065, column: 7, scope: !2435)
!2446 = !DILocation(line: 1065, column: 24, scope: !2435)
!2447 = !DILocation(line: 1066, column: 4, scope: !2435)
!2448 = !DILocation(line: 1066, column: 7, scope: !2435)
!2449 = !DILocation(line: 1066, column: 15, scope: !2435)
!2450 = !DILocation(line: 1067, column: 3, scope: !2435)
!2451 = !DILocation(line: 1068, column: 2, scope: !2404)
!2452 = !DILocation(line: 1069, column: 2, scope: !309)
!2453 = !DILocalVariable(name: "_a", arg: 1, scope: !255, file: !1, line: 902, type: !23)
!2454 = !DILocation(line: 902, column: 44, scope: !255)
!2455 = !DILocalVariable(name: "flag", arg: 2, scope: !255, file: !1, line: 902, type: !22)
!2456 = !DILocation(line: 902, column: 52, scope: !255)
!2457 = !DILocalVariable(name: "datestr", arg: 3, scope: !255, file: !1, line: 903, type: !79)
!2458 = !DILocation(line: 903, column: 17, scope: !255)
!2459 = !DILocalVariable(name: "r", scope: !255, file: !1, line: 905, type: !22)
!2460 = !DILocation(line: 905, column: 6, scope: !255)
!2461 = !DILocation(line: 907, column: 25, scope: !255)
!2462 = !DILocation(line: 907, column: 29, scope: !255)
!2463 = !DILocation(line: 907, column: 6, scope: !255)
!2464 = !DILocation(line: 907, column: 4, scope: !255)
!2465 = !DILocation(line: 908, column: 6, scope: !2466)
!2466 = distinct !DILexicalBlock(scope: !255, file: !1, line: 908, column: 6)
!2467 = !DILocation(line: 908, column: 8, scope: !2466)
!2468 = !DILocation(line: 908, column: 6, scope: !255)
!2469 = !DILocation(line: 909, column: 11, scope: !2466)
!2470 = !DILocation(line: 909, column: 3, scope: !2466)
!2471 = !DILocation(line: 910, column: 53, scope: !255)
!2472 = !DILocation(line: 910, column: 29, scope: !255)
!2473 = !DILocation(line: 910, column: 57, scope: !255)
!2474 = !DILocation(line: 910, column: 63, scope: !255)
!2475 = !DILocation(line: 910, column: 9, scope: !255)
!2476 = !DILocation(line: 910, column: 2, scope: !255)
!2477 = !DILocation(line: 911, column: 1, scope: !255)
!2478 = !DILocalVariable(name: "a", arg: 1, scope: !312, file: !1, line: 1073, type: !4)
!2479 = !DILocation(line: 1073, column: 43, scope: !312)
!2480 = !DILocalVariable(name: "timetype", arg: 2, scope: !312, file: !1, line: 1073, type: !22)
!2481 = !DILocation(line: 1073, column: 50, scope: !312)
!2482 = !DILocalVariable(name: "datestr", arg: 3, scope: !312, file: !1, line: 1073, type: !79)
!2483 = !DILocation(line: 1073, column: 72, scope: !312)
!2484 = !DILocalVariable(name: "t", scope: !312, file: !1, line: 1075, type: !142)
!2485 = !DILocation(line: 1075, column: 9, scope: !312)
!2486 = !DILocation(line: 1077, column: 6, scope: !2487)
!2487 = distinct !DILexicalBlock(scope: !312, file: !1, line: 1077, column: 6)
!2488 = !DILocation(line: 1077, column: 14, scope: !2487)
!2489 = !DILocation(line: 1077, column: 22, scope: !2487)
!2490 = !DILocation(line: 1077, column: 26, scope: !2491)
!2491 = !DILexicalBlockFile(scope: !2487, file: !1, discriminator: 1)
!2492 = !DILocation(line: 1077, column: 25, scope: !2491)
!2493 = !DILocation(line: 1077, column: 34, scope: !2491)
!2494 = !DILocation(line: 1077, column: 6, scope: !2491)
!2495 = !DILocation(line: 1078, column: 23, scope: !2496)
!2496 = distinct !DILexicalBlock(scope: !2487, file: !1, line: 1077, column: 43)
!2497 = !DILocation(line: 1078, column: 26, scope: !2496)
!2498 = !DILocation(line: 1078, column: 3, scope: !2496)
!2499 = !DILocation(line: 1079, column: 3, scope: !2496)
!2500 = !DILocation(line: 1081, column: 15, scope: !312)
!2501 = !DILocation(line: 1081, column: 18, scope: !312)
!2502 = !DILocation(line: 1081, column: 23, scope: !312)
!2503 = !DILocation(line: 1081, column: 6, scope: !312)
!2504 = !DILocation(line: 1081, column: 4, scope: !312)
!2505 = !DILocation(line: 1082, column: 6, scope: !2506)
!2506 = distinct !DILexicalBlock(scope: !312, file: !1, line: 1082, column: 6)
!2507 = !DILocation(line: 1082, column: 8, scope: !2506)
!2508 = !DILocation(line: 1082, column: 6, scope: !312)
!2509 = !DILocation(line: 1083, column: 23, scope: !2510)
!2510 = distinct !DILexicalBlock(scope: !2506, file: !1, line: 1082, column: 23)
!2511 = !DILocation(line: 1083, column: 26, scope: !2510)
!2512 = !DILocation(line: 1083, column: 3, scope: !2510)
!2513 = !DILocation(line: 1084, column: 3, scope: !2510)
!2514 = !DILocation(line: 1086, column: 24, scope: !312)
!2515 = !DILocation(line: 1086, column: 27, scope: !312)
!2516 = !DILocation(line: 1086, column: 37, scope: !312)
!2517 = !DILocation(line: 1086, column: 43, scope: !312)
!2518 = !DILocation(line: 1086, column: 9, scope: !312)
!2519 = !DILocation(line: 1086, column: 2, scope: !312)
!2520 = !DILocation(line: 1087, column: 1, scope: !312)
!2521 = !DILocalVariable(name: "_a", arg: 1, scope: !258, file: !1, line: 914, type: !23)
!2522 = !DILocation(line: 914, column: 46, scope: !258)
!2523 = !DILocalVariable(name: "flag", arg: 2, scope: !258, file: !1, line: 914, type: !22)
!2524 = !DILocation(line: 914, column: 54, scope: !258)
!2525 = !DILocalVariable(name: "datestr", arg: 3, scope: !258, file: !1, line: 915, type: !218)
!2526 = !DILocation(line: 915, column: 20, scope: !258)
!2527 = !DILocalVariable(name: "r", scope: !258, file: !1, line: 917, type: !22)
!2528 = !DILocation(line: 917, column: 6, scope: !258)
!2529 = !DILocation(line: 919, column: 25, scope: !258)
!2530 = !DILocation(line: 919, column: 29, scope: !258)
!2531 = !DILocation(line: 919, column: 6, scope: !258)
!2532 = !DILocation(line: 919, column: 4, scope: !258)
!2533 = !DILocation(line: 920, column: 6, scope: !2534)
!2534 = distinct !DILexicalBlock(scope: !258, file: !1, line: 920, column: 6)
!2535 = !DILocation(line: 920, column: 8, scope: !2534)
!2536 = !DILocation(line: 920, column: 6, scope: !258)
!2537 = !DILocation(line: 921, column: 11, scope: !2534)
!2538 = !DILocation(line: 921, column: 3, scope: !2534)
!2539 = !DILocation(line: 923, column: 55, scope: !258)
!2540 = !DILocation(line: 923, column: 31, scope: !258)
!2541 = !DILocation(line: 923, column: 59, scope: !258)
!2542 = !DILocation(line: 923, column: 65, scope: !258)
!2543 = !DILocation(line: 923, column: 9, scope: !258)
!2544 = !DILocation(line: 923, column: 2, scope: !258)
!2545 = !DILocation(line: 924, column: 1, scope: !258)
!2546 = !DILocalVariable(name: "a", arg: 1, scope: !315, file: !1, line: 1090, type: !4)
!2547 = !DILocation(line: 1090, column: 45, scope: !315)
!2548 = !DILocalVariable(name: "timetype", arg: 2, scope: !315, file: !1, line: 1090, type: !22)
!2549 = !DILocation(line: 1090, column: 52, scope: !315)
!2550 = !DILocalVariable(name: "datestr", arg: 3, scope: !315, file: !1, line: 1091, type: !218)
!2551 = !DILocation(line: 1091, column: 20, scope: !315)
!2552 = !DILocalVariable(name: "as", scope: !315, file: !1, line: 1093, type: !90)
!2553 = !DILocation(line: 1093, column: 24, scope: !315)
!2554 = !DILocalVariable(name: "t", scope: !315, file: !1, line: 1094, type: !142)
!2555 = !DILocation(line: 1094, column: 9, scope: !315)
!2556 = !DILocation(line: 1096, column: 6, scope: !2557)
!2557 = distinct !DILexicalBlock(scope: !315, file: !1, line: 1096, column: 6)
!2558 = !DILocation(line: 1096, column: 14, scope: !2557)
!2559 = !DILocation(line: 1096, column: 22, scope: !2557)
!2560 = !DILocation(line: 1096, column: 26, scope: !2561)
!2561 = !DILexicalBlockFile(scope: !2557, file: !1, discriminator: 1)
!2562 = !DILocation(line: 1096, column: 25, scope: !2561)
!2563 = !DILocation(line: 1096, column: 34, scope: !2561)
!2564 = !DILocation(line: 1096, column: 6, scope: !2561)
!2565 = !DILocation(line: 1097, column: 23, scope: !2566)
!2566 = distinct !DILexicalBlock(scope: !2557, file: !1, line: 1096, column: 44)
!2567 = !DILocation(line: 1097, column: 26, scope: !2566)
!2568 = !DILocation(line: 1097, column: 3, scope: !2566)
!2569 = !DILocation(line: 1098, column: 3, scope: !2566)
!2570 = !DILocation(line: 1101, column: 2, scope: !315)
!2571 = !DILocation(line: 1101, column: 2, scope: !2572)
!2572 = !DILexicalBlockFile(scope: !2573, file: !1, discriminator: 1)
!2573 = distinct !DILexicalBlock(scope: !315, file: !1, line: 1101, column: 2)
!2574 = !DILocation(line: 1102, column: 42, scope: !2575)
!2575 = distinct !DILexicalBlock(scope: !315, file: !1, line: 1102, column: 6)
!2576 = !DILocation(line: 1102, column: 58, scope: !2575)
!2577 = !DILocation(line: 1102, column: 51, scope: !2575)
!2578 = !DILocation(line: 1102, column: 6, scope: !2579)
!2579 = !DILexicalBlockFile(scope: !2575, file: !1, discriminator: 1)
!2580 = !DILocation(line: 1102, column: 68, scope: !2575)
!2581 = !DILocation(line: 1102, column: 6, scope: !315)
!2582 = !DILocation(line: 1103, column: 3, scope: !2583)
!2583 = distinct !DILexicalBlock(scope: !2575, file: !1, line: 1102, column: 73)
!2584 = !DILocation(line: 1104, column: 7, scope: !2585)
!2585 = distinct !DILexicalBlock(scope: !2583, file: !1, line: 1104, column: 7)
!2586 = !DILocation(line: 1104, column: 13, scope: !2585)
!2587 = !DILocation(line: 1104, column: 7, scope: !2583)
!2588 = !DILocation(line: 1105, column: 24, scope: !2585)
!2589 = !DILocation(line: 1105, column: 12, scope: !2585)
!2590 = !DILocation(line: 1105, column: 4, scope: !2585)
!2591 = !DILocation(line: 1106, column: 23, scope: !2583)
!2592 = !DILocation(line: 1106, column: 26, scope: !2583)
!2593 = !DILocation(line: 1106, column: 3, scope: !2583)
!2594 = !DILocation(line: 1108, column: 3, scope: !2583)
!2595 = !DILocation(line: 1110, column: 15, scope: !315)
!2596 = !DILocation(line: 1110, column: 18, scope: !315)
!2597 = !DILocation(line: 1110, column: 26, scope: !315)
!2598 = !DILocation(line: 1110, column: 6, scope: !315)
!2599 = !DILocation(line: 1110, column: 4, scope: !315)
!2600 = !DILocation(line: 1111, column: 2, scope: !315)
!2601 = !DILocation(line: 1112, column: 6, scope: !2602)
!2602 = distinct !DILexicalBlock(scope: !315, file: !1, line: 1112, column: 6)
!2603 = !DILocation(line: 1112, column: 8, scope: !2602)
!2604 = !DILocation(line: 1112, column: 6, scope: !315)
!2605 = !DILocation(line: 1113, column: 23, scope: !2606)
!2606 = distinct !DILexicalBlock(scope: !2602, file: !1, line: 1112, column: 23)
!2607 = !DILocation(line: 1113, column: 26, scope: !2606)
!2608 = !DILocation(line: 1113, column: 3, scope: !2606)
!2609 = !DILocation(line: 1114, column: 3, scope: !2606)
!2610 = !DILocation(line: 1116, column: 24, scope: !315)
!2611 = !DILocation(line: 1116, column: 27, scope: !315)
!2612 = !DILocation(line: 1116, column: 37, scope: !315)
!2613 = !DILocation(line: 1116, column: 43, scope: !315)
!2614 = !DILocation(line: 1116, column: 9, scope: !315)
!2615 = !DILocation(line: 1116, column: 2, scope: !315)
!2616 = !DILocation(line: 1117, column: 1, scope: !315)
!2617 = !DILocalVariable(name: "_a", arg: 1, scope: !261, file: !1, line: 927, type: !23)
!2618 = !DILocation(line: 927, column: 49, scope: !261)
!2619 = !DILocalVariable(name: "flag", arg: 2, scope: !261, file: !1, line: 927, type: !22)
!2620 = !DILocation(line: 927, column: 57, scope: !261)
!2621 = !DILocalVariable(name: "pathname", arg: 3, scope: !261, file: !1, line: 928, type: !79)
!2622 = !DILocation(line: 928, column: 17, scope: !261)
!2623 = !DILocalVariable(name: "r", scope: !261, file: !1, line: 930, type: !22)
!2624 = !DILocation(line: 930, column: 6, scope: !261)
!2625 = !DILocation(line: 932, column: 25, scope: !261)
!2626 = !DILocation(line: 932, column: 29, scope: !261)
!2627 = !DILocation(line: 932, column: 6, scope: !261)
!2628 = !DILocation(line: 932, column: 4, scope: !261)
!2629 = !DILocation(line: 933, column: 6, scope: !2630)
!2630 = distinct !DILexicalBlock(scope: !261, file: !1, line: 933, column: 6)
!2631 = !DILocation(line: 933, column: 8, scope: !2630)
!2632 = !DILocation(line: 933, column: 6, scope: !261)
!2633 = !DILocation(line: 934, column: 11, scope: !2630)
!2634 = !DILocation(line: 934, column: 3, scope: !2630)
!2635 = !DILocation(line: 935, column: 61, scope: !261)
!2636 = !DILocation(line: 935, column: 37, scope: !261)
!2637 = !DILocation(line: 936, column: 4, scope: !261)
!2638 = !DILocation(line: 936, column: 10, scope: !261)
!2639 = !DILocation(line: 935, column: 9, scope: !261)
!2640 = !DILocation(line: 935, column: 2, scope: !261)
!2641 = !DILocation(line: 937, column: 1, scope: !261)
!2642 = !DILocalVariable(name: "a", arg: 1, scope: !318, file: !1, line: 1226, type: !4)
!2643 = !DILocation(line: 1226, column: 51, scope: !318)
!2644 = !DILocalVariable(name: "timetype", arg: 2, scope: !318, file: !1, line: 1226, type: !22)
!2645 = !DILocation(line: 1226, column: 58, scope: !318)
!2646 = !DILocalVariable(name: "path", arg: 3, scope: !318, file: !1, line: 1227, type: !79)
!2647 = !DILocation(line: 1227, column: 17, scope: !318)
!2648 = !DILocalVariable(name: "st", scope: !318, file: !1, line: 1229, type: !323)
!2649 = !DILocation(line: 1229, column: 14, scope: !318)
!2650 = !DILocation(line: 1231, column: 6, scope: !2651)
!2651 = distinct !DILexicalBlock(scope: !318, file: !1, line: 1231, column: 6)
!2652 = !DILocation(line: 1231, column: 11, scope: !2651)
!2653 = !DILocation(line: 1231, column: 19, scope: !2651)
!2654 = !DILocation(line: 1231, column: 23, scope: !2655)
!2655 = !DILexicalBlockFile(scope: !2651, file: !1, discriminator: 1)
!2656 = !DILocation(line: 1231, column: 22, scope: !2655)
!2657 = !DILocation(line: 1231, column: 28, scope: !2655)
!2658 = !DILocation(line: 1231, column: 6, scope: !2655)
!2659 = !DILocation(line: 1232, column: 23, scope: !2660)
!2660 = distinct !DILexicalBlock(scope: !2651, file: !1, line: 1231, column: 37)
!2661 = !DILocation(line: 1232, column: 26, scope: !2660)
!2662 = !DILocation(line: 1232, column: 3, scope: !2660)
!2663 = !DILocation(line: 1233, column: 3, scope: !2660)
!2664 = !DILocation(line: 1235, column: 11, scope: !2665)
!2665 = distinct !DILexicalBlock(scope: !318, file: !1, line: 1235, column: 6)
!2666 = !DILocation(line: 1235, column: 6, scope: !2665)
!2667 = !DILocation(line: 1235, column: 22, scope: !2665)
!2668 = !DILocation(line: 1235, column: 6, scope: !318)
!2669 = !DILocation(line: 1236, column: 23, scope: !2670)
!2670 = distinct !DILexicalBlock(scope: !2665, file: !1, line: 1235, column: 28)
!2671 = !DILocation(line: 1236, column: 26, scope: !2670)
!2672 = !DILocation(line: 1236, column: 36, scope: !2670)
!2673 = !DILocation(line: 1236, column: 3, scope: !2674)
!2674 = !DILexicalBlockFile(scope: !2670, file: !1, discriminator: 1)
!2675 = !DILocation(line: 1237, column: 3, scope: !2670)
!2676 = !DILocation(line: 1239, column: 30, scope: !318)
!2677 = !DILocation(line: 1239, column: 33, scope: !318)
!2678 = !DILocation(line: 1239, column: 10, scope: !318)
!2679 = !DILocation(line: 1239, column: 2, scope: !318)
!2680 = !DILocation(line: 1240, column: 1, scope: !318)
!2681 = !DILocalVariable(name: "_a", arg: 1, scope: !262, file: !1, line: 940, type: !23)
!2682 = !DILocation(line: 940, column: 51, scope: !262)
!2683 = !DILocalVariable(name: "flag", arg: 2, scope: !262, file: !1, line: 940, type: !22)
!2684 = !DILocation(line: 940, column: 59, scope: !262)
!2685 = !DILocalVariable(name: "pathname", arg: 3, scope: !262, file: !1, line: 941, type: !218)
!2686 = !DILocation(line: 941, column: 20, scope: !262)
!2687 = !DILocalVariable(name: "r", scope: !262, file: !1, line: 943, type: !22)
!2688 = !DILocation(line: 943, column: 6, scope: !262)
!2689 = !DILocation(line: 945, column: 25, scope: !262)
!2690 = !DILocation(line: 945, column: 29, scope: !262)
!2691 = !DILocation(line: 945, column: 6, scope: !262)
!2692 = !DILocation(line: 945, column: 4, scope: !262)
!2693 = !DILocation(line: 946, column: 6, scope: !2694)
!2694 = distinct !DILexicalBlock(scope: !262, file: !1, line: 946, column: 6)
!2695 = !DILocation(line: 946, column: 8, scope: !2694)
!2696 = !DILocation(line: 946, column: 6, scope: !262)
!2697 = !DILocation(line: 947, column: 11, scope: !2694)
!2698 = !DILocation(line: 947, column: 3, scope: !2694)
!2699 = !DILocation(line: 948, column: 61, scope: !262)
!2700 = !DILocation(line: 948, column: 37, scope: !262)
!2701 = !DILocation(line: 949, column: 4, scope: !262)
!2702 = !DILocation(line: 949, column: 10, scope: !262)
!2703 = !DILocation(line: 948, column: 9, scope: !262)
!2704 = !DILocation(line: 948, column: 2, scope: !262)
!2705 = !DILocation(line: 950, column: 1, scope: !262)
!2706 = !DILocalVariable(name: "a", arg: 1, scope: !358, file: !1, line: 1243, type: !4)
!2707 = !DILocation(line: 1243, column: 51, scope: !358)
!2708 = !DILocalVariable(name: "timetype", arg: 2, scope: !358, file: !1, line: 1243, type: !22)
!2709 = !DILocation(line: 1243, column: 58, scope: !358)
!2710 = !DILocalVariable(name: "path", arg: 3, scope: !358, file: !1, line: 1244, type: !218)
!2711 = !DILocation(line: 1244, column: 20, scope: !358)
!2712 = !DILocalVariable(name: "as", scope: !358, file: !1, line: 1246, type: !90)
!2713 = !DILocation(line: 1246, column: 24, scope: !358)
!2714 = !DILocalVariable(name: "r", scope: !358, file: !1, line: 1247, type: !22)
!2715 = !DILocation(line: 1247, column: 6, scope: !358)
!2716 = !DILocation(line: 1249, column: 6, scope: !2717)
!2717 = distinct !DILexicalBlock(scope: !358, file: !1, line: 1249, column: 6)
!2718 = !DILocation(line: 1249, column: 11, scope: !2717)
!2719 = !DILocation(line: 1249, column: 19, scope: !2717)
!2720 = !DILocation(line: 1249, column: 23, scope: !2721)
!2721 = !DILexicalBlockFile(scope: !2717, file: !1, discriminator: 1)
!2722 = !DILocation(line: 1249, column: 22, scope: !2721)
!2723 = !DILocation(line: 1249, column: 28, scope: !2721)
!2724 = !DILocation(line: 1249, column: 6, scope: !2721)
!2725 = !DILocation(line: 1250, column: 23, scope: !2726)
!2726 = distinct !DILexicalBlock(scope: !2717, file: !1, line: 1249, column: 38)
!2727 = !DILocation(line: 1250, column: 26, scope: !2726)
!2728 = !DILocation(line: 1250, column: 3, scope: !2726)
!2729 = !DILocation(line: 1251, column: 3, scope: !2726)
!2730 = !DILocation(line: 1255, column: 2, scope: !358)
!2731 = !DILocation(line: 1255, column: 2, scope: !2732)
!2732 = !DILexicalBlockFile(scope: !2733, file: !1, discriminator: 1)
!2733 = distinct !DILexicalBlock(scope: !358, file: !1, line: 1255, column: 2)
!2734 = !DILocation(line: 1256, column: 42, scope: !2735)
!2735 = distinct !DILexicalBlock(scope: !358, file: !1, line: 1256, column: 6)
!2736 = !DILocation(line: 1256, column: 55, scope: !2735)
!2737 = !DILocation(line: 1256, column: 48, scope: !2735)
!2738 = !DILocation(line: 1256, column: 6, scope: !2739)
!2739 = !DILexicalBlockFile(scope: !2735, file: !1, discriminator: 1)
!2740 = !DILocation(line: 1256, column: 62, scope: !2735)
!2741 = !DILocation(line: 1256, column: 6, scope: !358)
!2742 = !DILocation(line: 1257, column: 3, scope: !2743)
!2743 = distinct !DILexicalBlock(scope: !2735, file: !1, line: 1256, column: 67)
!2744 = !DILocation(line: 1258, column: 7, scope: !2745)
!2745 = distinct !DILexicalBlock(scope: !2743, file: !1, line: 1258, column: 7)
!2746 = !DILocation(line: 1258, column: 13, scope: !2745)
!2747 = !DILocation(line: 1258, column: 7, scope: !2743)
!2748 = !DILocation(line: 1259, column: 24, scope: !2745)
!2749 = !DILocation(line: 1259, column: 12, scope: !2745)
!2750 = !DILocation(line: 1259, column: 4, scope: !2745)
!2751 = !DILocation(line: 1260, column: 23, scope: !2743)
!2752 = !DILocation(line: 1260, column: 26, scope: !2743)
!2753 = !DILocation(line: 1260, column: 3, scope: !2743)
!2754 = !DILocation(line: 1262, column: 3, scope: !2743)
!2755 = !DILocation(line: 1265, column: 34, scope: !358)
!2756 = !DILocation(line: 1265, column: 37, scope: !358)
!2757 = !DILocation(line: 1265, column: 50, scope: !358)
!2758 = !DILocation(line: 1265, column: 6, scope: !358)
!2759 = !DILocation(line: 1265, column: 4, scope: !358)
!2760 = !DILocation(line: 1266, column: 2, scope: !358)
!2761 = !DILocation(line: 1268, column: 10, scope: !358)
!2762 = !DILocation(line: 1268, column: 2, scope: !358)
!2763 = !DILocation(line: 1269, column: 1, scope: !358)
!2764 = !DILocalVariable(name: "_a", arg: 1, scope: !263, file: !1, line: 953, type: !23)
!2765 = !DILocation(line: 953, column: 45, scope: !263)
!2766 = !DILocalVariable(name: "flag", arg: 2, scope: !263, file: !1, line: 953, type: !22)
!2767 = !DILocation(line: 953, column: 53, scope: !263)
!2768 = !DILocalVariable(name: "entry", arg: 3, scope: !263, file: !1, line: 954, type: !29)
!2769 = !DILocation(line: 954, column: 27, scope: !263)
!2770 = !DILocalVariable(name: "a", scope: !263, file: !1, line: 956, type: !4)
!2771 = !DILocation(line: 956, column: 24, scope: !263)
!2772 = !DILocalVariable(name: "r", scope: !263, file: !1, line: 957, type: !22)
!2773 = !DILocation(line: 957, column: 6, scope: !263)
!2774 = !DILocation(line: 959, column: 2, scope: !263)
!2775 = !DILocalVariable(name: "magic_test", scope: !2776, file: !1, line: 959, type: !22)
!2776 = distinct !DILexicalBlock(scope: !263, file: !1, line: 959, column: 2)
!2777 = !DILocation(line: 959, column: 2, scope: !2776)
!2778 = !DILocation(line: 959, column: 2, scope: !2779)
!2779 = !DILexicalBlockFile(scope: !2776, file: !1, discriminator: 1)
!2780 = !DILocation(line: 959, column: 2, scope: !2781)
!2781 = !DILexicalBlockFile(scope: !2782, file: !1, discriminator: 2)
!2782 = distinct !DILexicalBlock(scope: !2776, file: !1, line: 959, column: 2)
!2783 = !DILocation(line: 959, column: 2, scope: !2784)
!2784 = !DILexicalBlockFile(scope: !2776, file: !1, discriminator: 3)
!2785 = !DILocation(line: 961, column: 30, scope: !263)
!2786 = !DILocation(line: 961, column: 6, scope: !263)
!2787 = !DILocation(line: 961, column: 4, scope: !263)
!2788 = !DILocation(line: 963, column: 6, scope: !2789)
!2789 = distinct !DILexicalBlock(scope: !263, file: !1, line: 963, column: 6)
!2790 = !DILocation(line: 963, column: 12, scope: !2789)
!2791 = !DILocation(line: 963, column: 6, scope: !263)
!2792 = !DILocation(line: 964, column: 23, scope: !2793)
!2793 = distinct !DILexicalBlock(scope: !2789, file: !1, line: 963, column: 21)
!2794 = !DILocation(line: 964, column: 26, scope: !2793)
!2795 = !DILocation(line: 964, column: 3, scope: !2793)
!2796 = !DILocation(line: 965, column: 3, scope: !2793)
!2797 = !DILocation(line: 967, column: 25, scope: !263)
!2798 = !DILocation(line: 967, column: 29, scope: !263)
!2799 = !DILocation(line: 967, column: 6, scope: !263)
!2800 = !DILocation(line: 967, column: 4, scope: !263)
!2801 = !DILocation(line: 968, column: 6, scope: !2802)
!2802 = distinct !DILexicalBlock(scope: !263, file: !1, line: 968, column: 6)
!2803 = !DILocation(line: 968, column: 8, scope: !2802)
!2804 = !DILocation(line: 968, column: 6, scope: !263)
!2805 = !DILocation(line: 969, column: 11, scope: !2802)
!2806 = !DILocation(line: 969, column: 3, scope: !2802)
!2807 = !DILocation(line: 970, column: 20, scope: !263)
!2808 = !DILocation(line: 970, column: 23, scope: !263)
!2809 = !DILocation(line: 970, column: 29, scope: !263)
!2810 = !DILocation(line: 970, column: 10, scope: !263)
!2811 = !DILocation(line: 970, column: 2, scope: !263)
!2812 = !DILocation(line: 971, column: 1, scope: !263)
!2813 = !DILocalVariable(name: "a", arg: 1, scope: !364, file: !1, line: 1363, type: !4)
!2814 = !DILocation(line: 1363, column: 33, scope: !364)
!2815 = !DILocalVariable(name: "flag", arg: 2, scope: !364, file: !1, line: 1363, type: !22)
!2816 = !DILocation(line: 1363, column: 40, scope: !364)
!2817 = !DILocalVariable(name: "entry", arg: 3, scope: !364, file: !1, line: 1364, type: !29)
!2818 = !DILocation(line: 1364, column: 27, scope: !364)
!2819 = !DILocalVariable(name: "f", scope: !364, file: !1, line: 1366, type: !194)
!2820 = !DILocation(line: 1366, column: 21, scope: !364)
!2821 = !DILocalVariable(name: "pathname", scope: !364, file: !1, line: 1367, type: !42)
!2822 = !DILocation(line: 1367, column: 14, scope: !364)
!2823 = !DILocalVariable(name: "r", scope: !364, file: !1, line: 1368, type: !22)
!2824 = !DILocation(line: 1368, column: 6, scope: !364)
!2825 = !DILocation(line: 1370, column: 6, scope: !364)
!2826 = !DILocation(line: 1370, column: 4, scope: !364)
!2827 = !DILocation(line: 1371, column: 6, scope: !2828)
!2828 = distinct !DILexicalBlock(scope: !364, file: !1, line: 1371, column: 6)
!2829 = !DILocation(line: 1371, column: 8, scope: !2828)
!2830 = !DILocation(line: 1371, column: 6, scope: !364)
!2831 = !DILocation(line: 1372, column: 23, scope: !2828)
!2832 = !DILocation(line: 1372, column: 11, scope: !2828)
!2833 = !DILocation(line: 1372, column: 3, scope: !2828)
!2834 = !DILocation(line: 1385, column: 36, scope: !364)
!2835 = !DILocation(line: 1385, column: 13, scope: !364)
!2836 = !DILocation(line: 1385, column: 11, scope: !364)
!2837 = !DILocation(line: 1386, column: 6, scope: !2838)
!2838 = distinct !DILexicalBlock(scope: !364, file: !1, line: 1386, column: 6)
!2839 = !DILocation(line: 1386, column: 15, scope: !2838)
!2840 = !DILocation(line: 1386, column: 6, scope: !364)
!2841 = !DILocation(line: 1387, column: 8, scope: !2842)
!2842 = distinct !DILexicalBlock(scope: !2838, file: !1, line: 1386, column: 24)
!2843 = !DILocation(line: 1387, column: 3, scope: !2842)
!2844 = !DILocation(line: 1388, column: 23, scope: !2842)
!2845 = !DILocation(line: 1388, column: 26, scope: !2842)
!2846 = !DILocation(line: 1388, column: 3, scope: !2842)
!2847 = !DILocation(line: 1389, column: 3, scope: !2842)
!2848 = !DILocation(line: 1391, column: 29, scope: !364)
!2849 = !DILocation(line: 1391, column: 32, scope: !364)
!2850 = !DILocation(line: 1391, column: 43, scope: !364)
!2851 = !DILocation(line: 1391, column: 2, scope: !364)
!2852 = !DILocation(line: 1392, column: 2, scope: !364)
!2853 = !DILocation(line: 1392, column: 5, scope: !364)
!2854 = !DILocation(line: 1392, column: 20, scope: !364)
!2855 = !DILocation(line: 1392, column: 28, scope: !364)
!2856 = !DILocation(line: 1394, column: 12, scope: !364)
!2857 = !DILocation(line: 1394, column: 2, scope: !364)
!2858 = !DILocation(line: 1394, column: 5, scope: !364)
!2859 = !DILocation(line: 1394, column: 10, scope: !364)
!2860 = !DILocation(line: 1395, column: 37, scope: !364)
!2861 = !DILocation(line: 1395, column: 17, scope: !364)
!2862 = !DILocation(line: 1395, column: 2, scope: !364)
!2863 = !DILocation(line: 1395, column: 5, scope: !364)
!2864 = !DILocation(line: 1395, column: 15, scope: !364)
!2865 = !DILocation(line: 1396, column: 43, scope: !364)
!2866 = !DILocation(line: 1396, column: 18, scope: !364)
!2867 = !DILocation(line: 1396, column: 2, scope: !364)
!2868 = !DILocation(line: 1396, column: 5, scope: !364)
!2869 = !DILocation(line: 1396, column: 16, scope: !364)
!2870 = !DILocation(line: 1397, column: 37, scope: !364)
!2871 = !DILocation(line: 1397, column: 17, scope: !364)
!2872 = !DILocation(line: 1397, column: 2, scope: !364)
!2873 = !DILocation(line: 1397, column: 5, scope: !364)
!2874 = !DILocation(line: 1397, column: 15, scope: !364)
!2875 = !DILocation(line: 1398, column: 43, scope: !364)
!2876 = !DILocation(line: 1398, column: 18, scope: !364)
!2877 = !DILocation(line: 1398, column: 2, scope: !364)
!2878 = !DILocation(line: 1398, column: 5, scope: !364)
!2879 = !DILocation(line: 1398, column: 16, scope: !364)
!2880 = !DILocation(line: 1399, column: 38, scope: !364)
!2881 = !DILocation(line: 1399, column: 41, scope: !364)
!2882 = !DILocation(line: 1399, column: 60, scope: !364)
!2883 = !DILocation(line: 1399, column: 63, scope: !364)
!2884 = !DILocation(line: 1399, column: 6, scope: !364)
!2885 = !DILocation(line: 1399, column: 4, scope: !364)
!2886 = !DILocation(line: 1400, column: 7, scope: !2887)
!2887 = distinct !DILexicalBlock(scope: !364, file: !1, line: 1400, column: 6)
!2888 = !DILocation(line: 1400, column: 6, scope: !364)
!2889 = !DILocalVariable(name: "f2", scope: !2890, file: !1, line: 1401, type: !194)
!2890 = distinct !DILexicalBlock(scope: !2887, file: !1, line: 1400, column: 10)
!2891 = !DILocation(line: 1401, column: 22, scope: !2890)
!2892 = !DILocation(line: 1405, column: 6, scope: !2890)
!2893 = !DILocation(line: 1405, column: 9, scope: !2890)
!2894 = !DILocation(line: 1405, column: 26, scope: !2890)
!2895 = !DILocation(line: 1404, column: 29, scope: !2890)
!2896 = !DILocation(line: 1404, column: 8, scope: !2890)
!2897 = !DILocation(line: 1404, column: 6, scope: !2890)
!2898 = !DILocation(line: 1414, column: 7, scope: !2899)
!2899 = distinct !DILexicalBlock(scope: !2890, file: !1, line: 1414, column: 7)
!2900 = !DILocation(line: 1414, column: 10, scope: !2899)
!2901 = !DILocation(line: 1414, column: 7, scope: !2890)
!2902 = !DILocation(line: 1415, column: 15, scope: !2903)
!2903 = distinct !DILexicalBlock(scope: !2899, file: !1, line: 1414, column: 19)
!2904 = !DILocation(line: 1415, column: 18, scope: !2903)
!2905 = !DILocation(line: 1415, column: 4, scope: !2903)
!2906 = !DILocation(line: 1415, column: 8, scope: !2903)
!2907 = !DILocation(line: 1415, column: 13, scope: !2903)
!2908 = !DILocation(line: 1416, column: 20, scope: !2903)
!2909 = !DILocation(line: 1416, column: 23, scope: !2903)
!2910 = !DILocation(line: 1416, column: 4, scope: !2903)
!2911 = !DILocation(line: 1416, column: 8, scope: !2903)
!2912 = !DILocation(line: 1416, column: 18, scope: !2903)
!2913 = !DILocation(line: 1417, column: 21, scope: !2903)
!2914 = !DILocation(line: 1417, column: 24, scope: !2903)
!2915 = !DILocation(line: 1417, column: 4, scope: !2903)
!2916 = !DILocation(line: 1417, column: 8, scope: !2903)
!2917 = !DILocation(line: 1417, column: 19, scope: !2903)
!2918 = !DILocation(line: 1418, column: 20, scope: !2903)
!2919 = !DILocation(line: 1418, column: 23, scope: !2903)
!2920 = !DILocation(line: 1418, column: 4, scope: !2903)
!2921 = !DILocation(line: 1418, column: 8, scope: !2903)
!2922 = !DILocation(line: 1418, column: 18, scope: !2903)
!2923 = !DILocation(line: 1419, column: 21, scope: !2903)
!2924 = !DILocation(line: 1419, column: 24, scope: !2903)
!2925 = !DILocation(line: 1419, column: 4, scope: !2903)
!2926 = !DILocation(line: 1419, column: 8, scope: !2903)
!2927 = !DILocation(line: 1419, column: 19, scope: !2903)
!2928 = !DILocation(line: 1420, column: 3, scope: !2903)
!2929 = !DILocation(line: 1422, column: 27, scope: !2890)
!2930 = !DILocation(line: 1422, column: 30, scope: !2890)
!2931 = !DILocation(line: 1422, column: 3, scope: !2890)
!2932 = !DILocation(line: 1423, column: 8, scope: !2890)
!2933 = !DILocation(line: 1423, column: 3, scope: !2890)
!2934 = !DILocation(line: 1424, column: 3, scope: !2890)
!2935 = !DILocation(line: 1426, column: 19, scope: !364)
!2936 = !DILocation(line: 1426, column: 22, scope: !364)
!2937 = !DILocation(line: 1426, column: 45, scope: !364)
!2938 = !DILocation(line: 1426, column: 2, scope: !364)
!2939 = !DILocation(line: 1427, column: 2, scope: !364)
!2940 = !DILocation(line: 1427, column: 5, scope: !364)
!2941 = !DILocation(line: 1427, column: 13, scope: !364)
!2942 = !DILocation(line: 1428, column: 2, scope: !364)
!2943 = !DILocation(line: 1429, column: 1, scope: !364)
!2944 = !DILocalVariable(name: "_a", arg: 1, scope: !266, file: !1, line: 981, type: !23)
!2945 = !DILocation(line: 981, column: 45, scope: !266)
!2946 = !DILocalVariable(name: "entry", arg: 2, scope: !266, file: !1, line: 982, type: !29)
!2947 = !DILocation(line: 982, column: 27, scope: !266)
!2948 = !DILocalVariable(name: "a", scope: !266, file: !1, line: 984, type: !4)
!2949 = !DILocation(line: 984, column: 24, scope: !266)
!2950 = !DILocation(line: 986, column: 2, scope: !266)
!2951 = !DILocalVariable(name: "magic_test", scope: !2952, file: !1, line: 986, type: !22)
!2952 = distinct !DILexicalBlock(scope: !266, file: !1, line: 986, column: 2)
!2953 = !DILocation(line: 986, column: 2, scope: !2952)
!2954 = !DILocation(line: 986, column: 2, scope: !2955)
!2955 = !DILexicalBlockFile(scope: !2952, file: !1, discriminator: 1)
!2956 = !DILocation(line: 986, column: 2, scope: !2957)
!2957 = !DILexicalBlockFile(scope: !2958, file: !1, discriminator: 2)
!2958 = distinct !DILexicalBlock(scope: !2952, file: !1, line: 986, column: 2)
!2959 = !DILocation(line: 986, column: 2, scope: !2960)
!2960 = !DILexicalBlockFile(scope: !2952, file: !1, discriminator: 3)
!2961 = !DILocation(line: 989, column: 30, scope: !266)
!2962 = !DILocation(line: 989, column: 6, scope: !266)
!2963 = !DILocation(line: 989, column: 4, scope: !266)
!2964 = !DILocation(line: 990, column: 6, scope: !2965)
!2965 = distinct !DILexicalBlock(scope: !266, file: !1, line: 990, column: 6)
!2966 = !DILocation(line: 990, column: 12, scope: !2965)
!2967 = !DILocation(line: 990, column: 6, scope: !266)
!2968 = !DILocation(line: 991, column: 23, scope: !2969)
!2969 = distinct !DILexicalBlock(scope: !2965, file: !1, line: 990, column: 21)
!2970 = !DILocation(line: 991, column: 26, scope: !2969)
!2971 = !DILocation(line: 991, column: 3, scope: !2969)
!2972 = !DILocation(line: 992, column: 3, scope: !2969)
!2973 = !DILocation(line: 997, column: 7, scope: !2974)
!2974 = distinct !DILexicalBlock(scope: !266, file: !1, line: 997, column: 6)
!2975 = !DILocation(line: 997, column: 10, scope: !2974)
!2976 = !DILocation(line: 997, column: 18, scope: !2974)
!2977 = !DILocation(line: 997, column: 33, scope: !2974)
!2978 = !DILocation(line: 997, column: 6, scope: !266)
!2979 = !DILocation(line: 998, column: 3, scope: !2974)
!2980 = !DILocation(line: 999, column: 24, scope: !266)
!2981 = !DILocation(line: 999, column: 27, scope: !266)
!2982 = !DILocation(line: 999, column: 10, scope: !266)
!2983 = !DILocation(line: 999, column: 2, scope: !266)
!2984 = !DILocation(line: 1000, column: 1, scope: !266)
!2985 = !DILocalVariable(name: "_a", arg: 1, scope: !267, file: !1, line: 1585, type: !23)
!2986 = !DILocation(line: 1585, column: 43, scope: !267)
!2987 = !DILocalVariable(name: "uid", arg: 2, scope: !267, file: !1, line: 1585, type: !51)
!2988 = !DILocation(line: 1585, column: 55, scope: !267)
!2989 = !DILocalVariable(name: "a", scope: !267, file: !1, line: 1587, type: !4)
!2990 = !DILocation(line: 1587, column: 24, scope: !267)
!2991 = !DILocation(line: 1589, column: 2, scope: !267)
!2992 = !DILocalVariable(name: "magic_test", scope: !2993, file: !1, line: 1589, type: !22)
!2993 = distinct !DILexicalBlock(scope: !267, file: !1, line: 1589, column: 2)
!2994 = !DILocation(line: 1589, column: 2, scope: !2993)
!2995 = !DILocation(line: 1589, column: 2, scope: !2996)
!2996 = !DILexicalBlockFile(scope: !2993, file: !1, discriminator: 1)
!2997 = !DILocation(line: 1589, column: 2, scope: !2998)
!2998 = !DILexicalBlockFile(scope: !2999, file: !1, discriminator: 2)
!2999 = distinct !DILexicalBlock(scope: !2993, file: !1, line: 1589, column: 2)
!3000 = !DILocation(line: 1589, column: 2, scope: !3001)
!3001 = !DILexicalBlockFile(scope: !2993, file: !1, discriminator: 3)
!3002 = !DILocation(line: 1591, column: 30, scope: !267)
!3003 = !DILocation(line: 1591, column: 6, scope: !267)
!3004 = !DILocation(line: 1591, column: 4, scope: !267)
!3005 = !DILocation(line: 1592, column: 23, scope: !267)
!3006 = !DILocation(line: 1592, column: 28, scope: !267)
!3007 = !DILocation(line: 1592, column: 31, scope: !267)
!3008 = !DILocation(line: 1592, column: 48, scope: !267)
!3009 = !DILocation(line: 1592, column: 10, scope: !267)
!3010 = !DILocation(line: 1592, column: 2, scope: !267)
!3011 = !DILocation(line: 1593, column: 1, scope: !267)
!3012 = !DILocalVariable(name: "a", arg: 1, scope: !375, file: !1, line: 1680, type: !4)
!3013 = !DILocation(line: 1680, column: 36, scope: !375)
!3014 = !DILocalVariable(name: "ids", arg: 2, scope: !375, file: !1, line: 1680, type: !378)
!3015 = !DILocation(line: 1680, column: 56, scope: !375)
!3016 = !DILocalVariable(name: "id", arg: 3, scope: !375, file: !1, line: 1680, type: !51)
!3017 = !DILocation(line: 1680, column: 69, scope: !375)
!3018 = !DILocalVariable(name: "i", scope: !375, file: !1, line: 1682, type: !12)
!3019 = !DILocation(line: 1682, column: 11, scope: !375)
!3020 = !DILocation(line: 1684, column: 6, scope: !3021)
!3021 = distinct !DILexicalBlock(scope: !375, file: !1, line: 1684, column: 6)
!3022 = !DILocation(line: 1684, column: 11, scope: !3021)
!3023 = !DILocation(line: 1684, column: 17, scope: !3021)
!3024 = !DILocation(line: 1684, column: 24, scope: !3021)
!3025 = !DILocation(line: 1684, column: 29, scope: !3021)
!3026 = !DILocation(line: 1684, column: 21, scope: !3021)
!3027 = !DILocation(line: 1684, column: 6, scope: !375)
!3028 = !DILocalVariable(name: "p", scope: !3029, file: !1, line: 1685, type: !217)
!3029 = distinct !DILexicalBlock(scope: !3021, file: !1, line: 1684, column: 35)
!3030 = !DILocation(line: 1685, column: 9, scope: !3029)
!3031 = !DILocation(line: 1687, column: 7, scope: !3032)
!3032 = distinct !DILexicalBlock(scope: !3029, file: !1, line: 1687, column: 7)
!3033 = !DILocation(line: 1687, column: 12, scope: !3032)
!3034 = !DILocation(line: 1687, column: 17, scope: !3032)
!3035 = !DILocation(line: 1687, column: 7, scope: !3029)
!3036 = !DILocation(line: 1688, column: 4, scope: !3032)
!3037 = !DILocation(line: 1688, column: 9, scope: !3032)
!3038 = !DILocation(line: 1688, column: 14, scope: !3032)
!3039 = !DILocation(line: 1690, column: 4, scope: !3032)
!3040 = !DILocation(line: 1690, column: 9, scope: !3032)
!3041 = !DILocation(line: 1690, column: 14, scope: !3032)
!3042 = !DILocation(line: 1691, column: 15, scope: !3029)
!3043 = !DILocation(line: 1691, column: 20, scope: !3029)
!3044 = !DILocation(line: 1691, column: 45, scope: !3029)
!3045 = !DILocation(line: 1691, column: 50, scope: !3029)
!3046 = !DILocation(line: 1691, column: 43, scope: !3029)
!3047 = !DILocation(line: 1691, column: 7, scope: !3029)
!3048 = !DILocation(line: 1691, column: 5, scope: !3029)
!3049 = !DILocation(line: 1692, column: 7, scope: !3050)
!3050 = distinct !DILexicalBlock(scope: !3029, file: !1, line: 1692, column: 7)
!3051 = !DILocation(line: 1692, column: 9, scope: !3050)
!3052 = !DILocation(line: 1692, column: 7, scope: !3029)
!3053 = !DILocation(line: 1693, column: 24, scope: !3050)
!3054 = !DILocation(line: 1693, column: 12, scope: !3050)
!3055 = !DILocation(line: 1693, column: 4, scope: !3050)
!3056 = !DILocation(line: 1694, column: 25, scope: !3029)
!3057 = !DILocation(line: 1694, column: 14, scope: !3029)
!3058 = !DILocation(line: 1694, column: 3, scope: !3029)
!3059 = !DILocation(line: 1694, column: 8, scope: !3029)
!3060 = !DILocation(line: 1694, column: 12, scope: !3029)
!3061 = !DILocation(line: 1695, column: 2, scope: !3029)
!3062 = !DILocation(line: 1698, column: 9, scope: !3063)
!3063 = distinct !DILexicalBlock(scope: !375, file: !1, line: 1698, column: 2)
!3064 = !DILocation(line: 1698, column: 7, scope: !3063)
!3065 = !DILocation(line: 1698, column: 14, scope: !3066)
!3066 = !DILexicalBlockFile(scope: !3067, file: !1, discriminator: 1)
!3067 = distinct !DILexicalBlock(scope: !3063, file: !1, line: 1698, column: 2)
!3068 = !DILocation(line: 1698, column: 18, scope: !3066)
!3069 = !DILocation(line: 1698, column: 23, scope: !3066)
!3070 = !DILocation(line: 1698, column: 16, scope: !3066)
!3071 = !DILocation(line: 1698, column: 2, scope: !3066)
!3072 = !DILocation(line: 1699, column: 16, scope: !3073)
!3073 = distinct !DILexicalBlock(scope: !3074, file: !1, line: 1699, column: 7)
!3074 = distinct !DILexicalBlock(scope: !3067, file: !1, line: 1698, column: 35)
!3075 = !DILocation(line: 1699, column: 7, scope: !3073)
!3076 = !DILocation(line: 1699, column: 12, scope: !3073)
!3077 = !DILocation(line: 1699, column: 22, scope: !3073)
!3078 = !DILocation(line: 1699, column: 19, scope: !3073)
!3079 = !DILocation(line: 1699, column: 7, scope: !3074)
!3080 = !DILocation(line: 1700, column: 4, scope: !3073)
!3081 = !DILocation(line: 1701, column: 2, scope: !3074)
!3082 = !DILocation(line: 1698, column: 31, scope: !3083)
!3083 = !DILexicalBlockFile(scope: !3067, file: !1, discriminator: 2)
!3084 = !DILocation(line: 1698, column: 2, scope: !3083)
!3085 = !DILocation(line: 1704, column: 6, scope: !3086)
!3086 = distinct !DILexicalBlock(scope: !375, file: !1, line: 1704, column: 6)
!3087 = !DILocation(line: 1704, column: 11, scope: !3086)
!3088 = !DILocation(line: 1704, column: 16, scope: !3086)
!3089 = !DILocation(line: 1704, column: 8, scope: !3086)
!3090 = !DILocation(line: 1704, column: 6, scope: !375)
!3091 = !DILocation(line: 1705, column: 28, scope: !3086)
!3092 = !DILocation(line: 1705, column: 12, scope: !3086)
!3093 = !DILocation(line: 1705, column: 17, scope: !3086)
!3094 = !DILocation(line: 1705, column: 22, scope: !3086)
!3095 = !DILocation(line: 1705, column: 3, scope: !3086)
!3096 = !DILocation(line: 1705, column: 8, scope: !3086)
!3097 = !DILocation(line: 1705, column: 26, scope: !3086)
!3098 = !DILocation(line: 1706, column: 20, scope: !3099)
!3099 = distinct !DILexicalBlock(scope: !3086, file: !1, line: 1706, column: 11)
!3100 = !DILocation(line: 1706, column: 11, scope: !3099)
!3101 = !DILocation(line: 1706, column: 16, scope: !3099)
!3102 = !DILocation(line: 1706, column: 26, scope: !3099)
!3103 = !DILocation(line: 1706, column: 23, scope: !3099)
!3104 = !DILocation(line: 1706, column: 11, scope: !3086)
!3105 = !DILocation(line: 1707, column: 22, scope: !3106)
!3106 = distinct !DILexicalBlock(scope: !3099, file: !1, line: 1706, column: 30)
!3107 = !DILocation(line: 1707, column: 23, scope: !3106)
!3108 = !DILocation(line: 1707, column: 13, scope: !3106)
!3109 = !DILocation(line: 1707, column: 18, scope: !3106)
!3110 = !DILocation(line: 1707, column: 3, scope: !3106)
!3111 = !DILocation(line: 1707, column: 40, scope: !3106)
!3112 = !DILocation(line: 1707, column: 31, scope: !3106)
!3113 = !DILocation(line: 1707, column: 36, scope: !3106)
!3114 = !DILocation(line: 1708, column: 8, scope: !3106)
!3115 = !DILocation(line: 1708, column: 13, scope: !3106)
!3116 = !DILocation(line: 1708, column: 21, scope: !3106)
!3117 = !DILocation(line: 1708, column: 19, scope: !3106)
!3118 = !DILocation(line: 1708, column: 24, scope: !3106)
!3119 = !DILocation(line: 1709, column: 17, scope: !3106)
!3120 = !DILocation(line: 1709, column: 12, scope: !3106)
!3121 = !DILocation(line: 1709, column: 3, scope: !3106)
!3122 = !DILocation(line: 1709, column: 8, scope: !3106)
!3123 = !DILocation(line: 1709, column: 15, scope: !3106)
!3124 = !DILocation(line: 1710, column: 3, scope: !3106)
!3125 = !DILocation(line: 1710, column: 8, scope: !3106)
!3126 = !DILocation(line: 1710, column: 13, scope: !3106)
!3127 = !DILocation(line: 1711, column: 2, scope: !3106)
!3128 = !DILocation(line: 1712, column: 2, scope: !375)
!3129 = !DILocation(line: 1712, column: 5, scope: !375)
!3130 = !DILocation(line: 1712, column: 13, scope: !375)
!3131 = !DILocation(line: 1713, column: 2, scope: !375)
!3132 = !DILocation(line: 1714, column: 1, scope: !375)
!3133 = !DILocalVariable(name: "_a", arg: 1, scope: !270, file: !1, line: 1596, type: !23)
!3134 = !DILocation(line: 1596, column: 43, scope: !270)
!3135 = !DILocalVariable(name: "gid", arg: 2, scope: !270, file: !1, line: 1596, type: !51)
!3136 = !DILocation(line: 1596, column: 55, scope: !270)
!3137 = !DILocalVariable(name: "a", scope: !270, file: !1, line: 1598, type: !4)
!3138 = !DILocation(line: 1598, column: 24, scope: !270)
!3139 = !DILocation(line: 1600, column: 2, scope: !270)
!3140 = !DILocalVariable(name: "magic_test", scope: !3141, file: !1, line: 1600, type: !22)
!3141 = distinct !DILexicalBlock(scope: !270, file: !1, line: 1600, column: 2)
!3142 = !DILocation(line: 1600, column: 2, scope: !3141)
!3143 = !DILocation(line: 1600, column: 2, scope: !3144)
!3144 = !DILexicalBlockFile(scope: !3141, file: !1, discriminator: 1)
!3145 = !DILocation(line: 1600, column: 2, scope: !3146)
!3146 = !DILexicalBlockFile(scope: !3147, file: !1, discriminator: 2)
!3147 = distinct !DILexicalBlock(scope: !3141, file: !1, line: 1600, column: 2)
!3148 = !DILocation(line: 1600, column: 2, scope: !3149)
!3149 = !DILexicalBlockFile(scope: !3141, file: !1, discriminator: 3)
!3150 = !DILocation(line: 1602, column: 30, scope: !270)
!3151 = !DILocation(line: 1602, column: 6, scope: !270)
!3152 = !DILocation(line: 1602, column: 4, scope: !270)
!3153 = !DILocation(line: 1603, column: 23, scope: !270)
!3154 = !DILocation(line: 1603, column: 28, scope: !270)
!3155 = !DILocation(line: 1603, column: 31, scope: !270)
!3156 = !DILocation(line: 1603, column: 48, scope: !270)
!3157 = !DILocation(line: 1603, column: 10, scope: !270)
!3158 = !DILocation(line: 1603, column: 2, scope: !270)
!3159 = !DILocation(line: 1604, column: 1, scope: !270)
!3160 = !DILocalVariable(name: "_a", arg: 1, scope: !271, file: !1, line: 1607, type: !23)
!3161 = !DILocation(line: 1607, column: 45, scope: !271)
!3162 = !DILocalVariable(name: "uname", arg: 2, scope: !271, file: !1, line: 1607, type: !79)
!3163 = !DILocation(line: 1607, column: 61, scope: !271)
!3164 = !DILocalVariable(name: "a", scope: !271, file: !1, line: 1609, type: !4)
!3165 = !DILocation(line: 1609, column: 24, scope: !271)
!3166 = !DILocation(line: 1611, column: 2, scope: !271)
!3167 = !DILocalVariable(name: "magic_test", scope: !3168, file: !1, line: 1611, type: !22)
!3168 = distinct !DILexicalBlock(scope: !271, file: !1, line: 1611, column: 2)
!3169 = !DILocation(line: 1611, column: 2, scope: !3168)
!3170 = !DILocation(line: 1611, column: 2, scope: !3171)
!3171 = !DILexicalBlockFile(scope: !3168, file: !1, discriminator: 1)
!3172 = !DILocation(line: 1611, column: 2, scope: !3173)
!3173 = !DILexicalBlockFile(scope: !3174, file: !1, discriminator: 2)
!3174 = distinct !DILexicalBlock(scope: !3168, file: !1, line: 1611, column: 2)
!3175 = !DILocation(line: 1611, column: 2, scope: !3176)
!3176 = !DILexicalBlockFile(scope: !3168, file: !1, discriminator: 3)
!3177 = !DILocation(line: 1613, column: 30, scope: !271)
!3178 = !DILocation(line: 1613, column: 6, scope: !271)
!3179 = !DILocation(line: 1613, column: 4, scope: !271)
!3180 = !DILocation(line: 1614, column: 25, scope: !271)
!3181 = !DILocation(line: 1614, column: 30, scope: !271)
!3182 = !DILocation(line: 1614, column: 33, scope: !271)
!3183 = !DILocation(line: 1614, column: 55, scope: !271)
!3184 = !DILocation(line: 1614, column: 10, scope: !271)
!3185 = !DILocation(line: 1614, column: 2, scope: !271)
!3186 = !DILocation(line: 1615, column: 1, scope: !271)
!3187 = !DILocalVariable(name: "a", arg: 1, scope: !379, file: !1, line: 1736, type: !4)
!3188 = !DILocation(line: 1736, column: 38, scope: !379)
!3189 = !DILocalVariable(name: "list", arg: 2, scope: !379, file: !1, line: 1736, type: !281)
!3190 = !DILocation(line: 1736, column: 60, scope: !379)
!3191 = !DILocalVariable(name: "mbs", arg: 3, scope: !379, file: !1, line: 1737, type: !22)
!3192 = !DILocation(line: 1737, column: 9, scope: !379)
!3193 = !DILocalVariable(name: "name", arg: 4, scope: !379, file: !1, line: 1737, type: !42)
!3194 = !DILocation(line: 1737, column: 26, scope: !379)
!3195 = !DILocalVariable(name: "match", scope: !379, file: !1, line: 1739, type: !114)
!3196 = !DILocation(line: 1739, column: 16, scope: !379)
!3197 = !DILocation(line: 1741, column: 10, scope: !379)
!3198 = !DILocation(line: 1741, column: 8, scope: !379)
!3199 = !DILocation(line: 1742, column: 6, scope: !3200)
!3200 = distinct !DILexicalBlock(scope: !379, file: !1, line: 1742, column: 6)
!3201 = !DILocation(line: 1742, column: 12, scope: !3200)
!3202 = !DILocation(line: 1742, column: 6, scope: !379)
!3203 = !DILocation(line: 1743, column: 23, scope: !3200)
!3204 = !DILocation(line: 1743, column: 11, scope: !3200)
!3205 = !DILocation(line: 1743, column: 3, scope: !3200)
!3206 = !DILocation(line: 1744, column: 6, scope: !3207)
!3207 = distinct !DILexicalBlock(scope: !379, file: !1, line: 1744, column: 6)
!3208 = !DILocation(line: 1744, column: 6, scope: !379)
!3209 = !DILocation(line: 1745, column: 30, scope: !3207)
!3210 = !DILocation(line: 1745, column: 37, scope: !3207)
!3211 = !DILocation(line: 1745, column: 47, scope: !3207)
!3212 = !DILocation(line: 1745, column: 3, scope: !3207)
!3213 = !DILocation(line: 1747, column: 30, scope: !3207)
!3214 = !DILocation(line: 1747, column: 37, scope: !3207)
!3215 = !DILocation(line: 1747, column: 47, scope: !3207)
!3216 = !DILocation(line: 1747, column: 3, scope: !3207)
!3217 = !DILocation(line: 1748, column: 17, scope: !379)
!3218 = !DILocation(line: 1748, column: 23, scope: !379)
!3219 = !DILocation(line: 1748, column: 2, scope: !379)
!3220 = !DILocation(line: 1749, column: 2, scope: !379)
!3221 = !DILocation(line: 1749, column: 5, scope: !379)
!3222 = !DILocation(line: 1749, column: 13, scope: !379)
!3223 = !DILocation(line: 1750, column: 2, scope: !379)
!3224 = !DILocation(line: 1751, column: 1, scope: !379)
!3225 = !DILocalVariable(name: "_a", arg: 1, scope: !272, file: !1, line: 1618, type: !23)
!3226 = !DILocation(line: 1618, column: 47, scope: !272)
!3227 = !DILocalVariable(name: "uname", arg: 2, scope: !272, file: !1, line: 1618, type: !218)
!3228 = !DILocation(line: 1618, column: 66, scope: !272)
!3229 = !DILocalVariable(name: "a", scope: !272, file: !1, line: 1620, type: !4)
!3230 = !DILocation(line: 1620, column: 24, scope: !272)
!3231 = !DILocation(line: 1622, column: 2, scope: !272)
!3232 = !DILocalVariable(name: "magic_test", scope: !3233, file: !1, line: 1622, type: !22)
!3233 = distinct !DILexicalBlock(scope: !272, file: !1, line: 1622, column: 2)
!3234 = !DILocation(line: 1622, column: 2, scope: !3233)
!3235 = !DILocation(line: 1622, column: 2, scope: !3236)
!3236 = !DILexicalBlockFile(scope: !3233, file: !1, discriminator: 1)
!3237 = !DILocation(line: 1622, column: 2, scope: !3238)
!3238 = !DILexicalBlockFile(scope: !3239, file: !1, discriminator: 2)
!3239 = distinct !DILexicalBlock(scope: !3233, file: !1, line: 1622, column: 2)
!3240 = !DILocation(line: 1622, column: 2, scope: !3241)
!3241 = !DILexicalBlockFile(scope: !3233, file: !1, discriminator: 3)
!3242 = !DILocation(line: 1624, column: 30, scope: !272)
!3243 = !DILocation(line: 1624, column: 6, scope: !272)
!3244 = !DILocation(line: 1624, column: 4, scope: !272)
!3245 = !DILocation(line: 1625, column: 25, scope: !272)
!3246 = !DILocation(line: 1625, column: 30, scope: !272)
!3247 = !DILocation(line: 1625, column: 33, scope: !272)
!3248 = !DILocation(line: 1625, column: 55, scope: !272)
!3249 = !DILocation(line: 1625, column: 10, scope: !272)
!3250 = !DILocation(line: 1625, column: 2, scope: !272)
!3251 = !DILocation(line: 1626, column: 1, scope: !272)
!3252 = !DILocalVariable(name: "_a", arg: 1, scope: !273, file: !1, line: 1629, type: !23)
!3253 = !DILocation(line: 1629, column: 45, scope: !273)
!3254 = !DILocalVariable(name: "gname", arg: 2, scope: !273, file: !1, line: 1629, type: !79)
!3255 = !DILocation(line: 1629, column: 61, scope: !273)
!3256 = !DILocalVariable(name: "a", scope: !273, file: !1, line: 1631, type: !4)
!3257 = !DILocation(line: 1631, column: 24, scope: !273)
!3258 = !DILocation(line: 1633, column: 2, scope: !273)
!3259 = !DILocalVariable(name: "magic_test", scope: !3260, file: !1, line: 1633, type: !22)
!3260 = distinct !DILexicalBlock(scope: !273, file: !1, line: 1633, column: 2)
!3261 = !DILocation(line: 1633, column: 2, scope: !3260)
!3262 = !DILocation(line: 1633, column: 2, scope: !3263)
!3263 = !DILexicalBlockFile(scope: !3260, file: !1, discriminator: 1)
!3264 = !DILocation(line: 1633, column: 2, scope: !3265)
!3265 = !DILexicalBlockFile(scope: !3266, file: !1, discriminator: 2)
!3266 = distinct !DILexicalBlock(scope: !3260, file: !1, line: 1633, column: 2)
!3267 = !DILocation(line: 1633, column: 2, scope: !3268)
!3268 = !DILexicalBlockFile(scope: !3260, file: !1, discriminator: 3)
!3269 = !DILocation(line: 1635, column: 30, scope: !273)
!3270 = !DILocation(line: 1635, column: 6, scope: !273)
!3271 = !DILocation(line: 1635, column: 4, scope: !273)
!3272 = !DILocation(line: 1636, column: 25, scope: !273)
!3273 = !DILocation(line: 1636, column: 30, scope: !273)
!3274 = !DILocation(line: 1636, column: 33, scope: !273)
!3275 = !DILocation(line: 1636, column: 55, scope: !273)
!3276 = !DILocation(line: 1636, column: 10, scope: !273)
!3277 = !DILocation(line: 1636, column: 2, scope: !273)
!3278 = !DILocation(line: 1637, column: 1, scope: !273)
!3279 = !DILocalVariable(name: "_a", arg: 1, scope: !274, file: !1, line: 1640, type: !23)
!3280 = !DILocation(line: 1640, column: 47, scope: !274)
!3281 = !DILocalVariable(name: "gname", arg: 2, scope: !274, file: !1, line: 1640, type: !218)
!3282 = !DILocation(line: 1640, column: 66, scope: !274)
!3283 = !DILocalVariable(name: "a", scope: !274, file: !1, line: 1642, type: !4)
!3284 = !DILocation(line: 1642, column: 24, scope: !274)
!3285 = !DILocation(line: 1644, column: 2, scope: !274)
!3286 = !DILocalVariable(name: "magic_test", scope: !3287, file: !1, line: 1644, type: !22)
!3287 = distinct !DILexicalBlock(scope: !274, file: !1, line: 1644, column: 2)
!3288 = !DILocation(line: 1644, column: 2, scope: !3287)
!3289 = !DILocation(line: 1644, column: 2, scope: !3290)
!3290 = !DILexicalBlockFile(scope: !3287, file: !1, discriminator: 1)
!3291 = !DILocation(line: 1644, column: 2, scope: !3292)
!3292 = !DILexicalBlockFile(scope: !3293, file: !1, discriminator: 2)
!3293 = distinct !DILexicalBlock(scope: !3287, file: !1, line: 1644, column: 2)
!3294 = !DILocation(line: 1644, column: 2, scope: !3295)
!3295 = !DILexicalBlockFile(scope: !3287, file: !1, discriminator: 3)
!3296 = !DILocation(line: 1646, column: 30, scope: !274)
!3297 = !DILocation(line: 1646, column: 6, scope: !274)
!3298 = !DILocation(line: 1646, column: 4, scope: !274)
!3299 = !DILocation(line: 1647, column: 25, scope: !274)
!3300 = !DILocation(line: 1647, column: 30, scope: !274)
!3301 = !DILocation(line: 1647, column: 33, scope: !274)
!3302 = !DILocation(line: 1647, column: 55, scope: !274)
!3303 = !DILocation(line: 1647, column: 10, scope: !274)
!3304 = !DILocation(line: 1647, column: 2, scope: !274)
!3305 = !DILocation(line: 1648, column: 1, scope: !274)
!3306 = !DILocalVariable(name: "_a", arg: 1, scope: !275, file: !1, line: 1658, type: !23)
!3307 = !DILocation(line: 1658, column: 46, scope: !275)
!3308 = !DILocalVariable(name: "entry", arg: 2, scope: !275, file: !1, line: 1659, type: !29)
!3309 = !DILocation(line: 1659, column: 27, scope: !275)
!3310 = !DILocalVariable(name: "a", scope: !275, file: !1, line: 1661, type: !4)
!3311 = !DILocation(line: 1661, column: 24, scope: !275)
!3312 = !DILocation(line: 1663, column: 2, scope: !275)
!3313 = !DILocalVariable(name: "magic_test", scope: !3314, file: !1, line: 1663, type: !22)
!3314 = distinct !DILexicalBlock(scope: !275, file: !1, line: 1663, column: 2)
!3315 = !DILocation(line: 1663, column: 2, scope: !3314)
!3316 = !DILocation(line: 1663, column: 2, scope: !3317)
!3317 = !DILexicalBlockFile(scope: !3314, file: !1, discriminator: 1)
!3318 = !DILocation(line: 1663, column: 2, scope: !3319)
!3319 = !DILexicalBlockFile(scope: !3320, file: !1, discriminator: 2)
!3320 = distinct !DILexicalBlock(scope: !3314, file: !1, line: 1663, column: 2)
!3321 = !DILocation(line: 1663, column: 2, scope: !3322)
!3322 = !DILexicalBlockFile(scope: !3314, file: !1, discriminator: 3)
!3323 = !DILocation(line: 1666, column: 30, scope: !275)
!3324 = !DILocation(line: 1666, column: 6, scope: !275)
!3325 = !DILocation(line: 1666, column: 4, scope: !275)
!3326 = !DILocation(line: 1667, column: 6, scope: !3327)
!3327 = distinct !DILexicalBlock(scope: !275, file: !1, line: 1667, column: 6)
!3328 = !DILocation(line: 1667, column: 12, scope: !3327)
!3329 = !DILocation(line: 1667, column: 6, scope: !275)
!3330 = !DILocation(line: 1668, column: 23, scope: !3331)
!3331 = distinct !DILexicalBlock(scope: !3327, file: !1, line: 1667, column: 21)
!3332 = !DILocation(line: 1668, column: 26, scope: !3331)
!3333 = !DILocation(line: 1668, column: 3, scope: !3331)
!3334 = !DILocation(line: 1669, column: 3, scope: !3331)
!3335 = !DILocation(line: 1674, column: 7, scope: !3336)
!3336 = distinct !DILexicalBlock(scope: !275, file: !1, line: 1674, column: 6)
!3337 = !DILocation(line: 1674, column: 10, scope: !3336)
!3338 = !DILocation(line: 1674, column: 18, scope: !3336)
!3339 = !DILocation(line: 1674, column: 31, scope: !3336)
!3340 = !DILocation(line: 1674, column: 6, scope: !275)
!3341 = !DILocation(line: 1675, column: 3, scope: !3336)
!3342 = !DILocation(line: 1676, column: 25, scope: !275)
!3343 = !DILocation(line: 1676, column: 28, scope: !275)
!3344 = !DILocation(line: 1676, column: 10, scope: !275)
!3345 = !DILocation(line: 1676, column: 2, scope: !275)
!3346 = !DILocation(line: 1677, column: 1, scope: !275)
!3347 = !DILocalVariable(name: "n1", arg: 1, scope: !276, file: !1, line: 1276, type: !182)
!3348 = !DILocation(line: 1276, column: 44, scope: !276)
!3349 = !DILocalVariable(name: "n2", arg: 2, scope: !276, file: !1, line: 1277, type: !182)
!3350 = !DILocation(line: 1277, column: 35, scope: !276)
!3351 = !DILocalVariable(name: "f1", scope: !276, file: !1, line: 1279, type: !194)
!3352 = !DILocation(line: 1279, column: 21, scope: !276)
!3353 = !DILocation(line: 1279, column: 58, scope: !276)
!3354 = !DILocation(line: 1279, column: 47, scope: !276)
!3355 = !DILocation(line: 1279, column: 26, scope: !276)
!3356 = !DILocalVariable(name: "f2", scope: !276, file: !1, line: 1280, type: !194)
!3357 = !DILocation(line: 1280, column: 21, scope: !276)
!3358 = !DILocation(line: 1280, column: 58, scope: !276)
!3359 = !DILocation(line: 1280, column: 47, scope: !276)
!3360 = !DILocation(line: 1280, column: 26, scope: !276)
!3361 = !DILocalVariable(name: "p1", scope: !276, file: !1, line: 1281, type: !79)
!3362 = !DILocation(line: 1281, column: 14, scope: !276)
!3363 = !DILocalVariable(name: "p2", scope: !276, file: !1, line: 1281, type: !79)
!3364 = !DILocation(line: 1281, column: 19, scope: !276)
!3365 = !DILocation(line: 1283, column: 34, scope: !276)
!3366 = !DILocation(line: 1283, column: 38, scope: !276)
!3367 = !DILocation(line: 1283, column: 2, scope: !276)
!3368 = !DILocation(line: 1284, column: 34, scope: !276)
!3369 = !DILocation(line: 1284, column: 38, scope: !276)
!3370 = !DILocation(line: 1284, column: 2, scope: !276)
!3371 = !DILocation(line: 1285, column: 6, scope: !3372)
!3372 = distinct !DILexicalBlock(scope: !276, file: !1, line: 1285, column: 6)
!3373 = !DILocation(line: 1285, column: 9, scope: !3372)
!3374 = !DILocation(line: 1285, column: 6, scope: !276)
!3375 = !DILocation(line: 1286, column: 3, scope: !3372)
!3376 = !DILocation(line: 1287, column: 6, scope: !3377)
!3377 = distinct !DILexicalBlock(scope: !276, file: !1, line: 1287, column: 6)
!3378 = !DILocation(line: 1287, column: 9, scope: !3377)
!3379 = !DILocation(line: 1287, column: 6, scope: !276)
!3380 = !DILocation(line: 1288, column: 3, scope: !3377)
!3381 = !DILocation(line: 1289, column: 17, scope: !276)
!3382 = !DILocation(line: 1289, column: 21, scope: !276)
!3383 = !DILocation(line: 1289, column: 10, scope: !276)
!3384 = !DILocation(line: 1289, column: 2, scope: !276)
!3385 = !DILocation(line: 1290, column: 1, scope: !276)
!3386 = !DILocalVariable(name: "n", arg: 1, scope: !277, file: !1, line: 1293, type: !182)
!3387 = !DILocation(line: 1293, column: 43, scope: !277)
!3388 = !DILocalVariable(name: "key", arg: 2, scope: !277, file: !1, line: 1293, type: !42)
!3389 = !DILocation(line: 1293, column: 58, scope: !277)
!3390 = !DILocalVariable(name: "f", scope: !277, file: !1, line: 1295, type: !194)
!3391 = !DILocation(line: 1295, column: 21, scope: !277)
!3392 = !DILocation(line: 1295, column: 57, scope: !277)
!3393 = !DILocation(line: 1295, column: 46, scope: !277)
!3394 = !DILocation(line: 1295, column: 25, scope: !277)
!3395 = !DILocalVariable(name: "p", scope: !277, file: !1, line: 1296, type: !79)
!3396 = !DILocation(line: 1296, column: 14, scope: !277)
!3397 = !DILocation(line: 1298, column: 34, scope: !277)
!3398 = !DILocation(line: 1298, column: 37, scope: !277)
!3399 = !DILocation(line: 1298, column: 2, scope: !277)
!3400 = !DILocation(line: 1299, column: 6, scope: !3401)
!3401 = distinct !DILexicalBlock(scope: !277, file: !1, line: 1299, column: 6)
!3402 = !DILocation(line: 1299, column: 8, scope: !3401)
!3403 = !DILocation(line: 1299, column: 6, scope: !277)
!3404 = !DILocation(line: 1300, column: 3, scope: !3401)
!3405 = !DILocation(line: 1301, column: 17, scope: !277)
!3406 = !DILocation(line: 1301, column: 34, scope: !277)
!3407 = !DILocation(line: 1301, column: 10, scope: !277)
!3408 = !DILocation(line: 1301, column: 2, scope: !277)
!3409 = !DILocation(line: 1302, column: 1, scope: !277)
!3410 = !DILocalVariable(name: "a", arg: 1, scope: !282, file: !1, line: 206, type: !4)
!3411 = !DILocation(line: 206, column: 35, scope: !282)
!3412 = !DILocation(line: 208, column: 22, scope: !282)
!3413 = !DILocation(line: 208, column: 25, scope: !282)
!3414 = !DILocation(line: 208, column: 2, scope: !282)
!3415 = !DILocation(line: 209, column: 2, scope: !282)
!3416 = !DILocation(line: 209, column: 5, scope: !282)
!3417 = !DILocation(line: 209, column: 13, scope: !282)
!3418 = !DILocation(line: 209, column: 19, scope: !282)
!3419 = !DILocation(line: 210, column: 2, scope: !282)
!3420 = !DILocalVariable(name: "list", arg: 1, scope: !285, file: !1, line: 826, type: !281)
!3421 = !DILocation(line: 826, column: 35, scope: !285)
!3422 = !DILocalVariable(name: "m", arg: 2, scope: !285, file: !1, line: 826, type: !114)
!3423 = !DILocation(line: 826, column: 55, scope: !285)
!3424 = !DILocation(line: 828, column: 16, scope: !285)
!3425 = !DILocation(line: 828, column: 3, scope: !285)
!3426 = !DILocation(line: 828, column: 9, scope: !285)
!3427 = !DILocation(line: 828, column: 14, scope: !285)
!3428 = !DILocation(line: 829, column: 17, scope: !285)
!3429 = !DILocation(line: 829, column: 20, scope: !285)
!3430 = !DILocation(line: 829, column: 2, scope: !285)
!3431 = !DILocation(line: 829, column: 8, scope: !285)
!3432 = !DILocation(line: 829, column: 13, scope: !285)
!3433 = !DILocation(line: 830, column: 2, scope: !285)
!3434 = !DILocation(line: 830, column: 8, scope: !285)
!3435 = !DILocation(line: 830, column: 13, scope: !285)
!3436 = !DILocation(line: 831, column: 2, scope: !285)
!3437 = !DILocation(line: 831, column: 8, scope: !285)
!3438 = !DILocation(line: 831, column: 23, scope: !285)
!3439 = !DILocation(line: 832, column: 1, scope: !285)
!3440 = !DILocalVariable(name: "a", arg: 1, scope: !297, file: !1, line: 781, type: !4)
!3441 = !DILocation(line: 781, column: 44, scope: !297)
!3442 = !DILocalVariable(name: "m", arg: 2, scope: !297, file: !1, line: 781, type: !114)
!3443 = !DILocation(line: 781, column: 61, scope: !297)
!3444 = !DILocalVariable(name: "mbs", arg: 3, scope: !297, file: !1, line: 782, type: !22)
!3445 = !DILocation(line: 782, column: 9, scope: !297)
!3446 = !DILocalVariable(name: "pn", arg: 4, scope: !297, file: !1, line: 782, type: !42)
!3447 = !DILocation(line: 782, column: 26, scope: !297)
!3448 = !DILocalVariable(name: "flag", scope: !297, file: !1, line: 784, type: !22)
!3449 = !DILocation(line: 784, column: 6, scope: !297)
!3450 = !DILocalVariable(name: "r", scope: !297, file: !1, line: 785, type: !22)
!3451 = !DILocation(line: 785, column: 6, scope: !297)
!3452 = !DILocation(line: 787, column: 6, scope: !3453)
!3453 = distinct !DILexicalBlock(scope: !297, file: !1, line: 787, column: 6)
!3454 = !DILocation(line: 787, column: 6, scope: !297)
!3455 = !DILocalVariable(name: "p", scope: !3456, file: !1, line: 788, type: !79)
!3456 = distinct !DILexicalBlock(scope: !3453, file: !1, line: 787, column: 11)
!3457 = !DILocation(line: 788, column: 15, scope: !3456)
!3458 = !DILocation(line: 789, column: 33, scope: !3456)
!3459 = !DILocation(line: 789, column: 36, scope: !3456)
!3460 = !DILocation(line: 789, column: 48, scope: !3456)
!3461 = !DILocation(line: 789, column: 51, scope: !3456)
!3462 = !DILocation(line: 789, column: 7, scope: !3456)
!3463 = !DILocation(line: 789, column: 5, scope: !3456)
!3464 = !DILocation(line: 790, column: 7, scope: !3465)
!3465 = distinct !DILexicalBlock(scope: !3456, file: !1, line: 790, column: 7)
!3466 = !DILocation(line: 790, column: 9, scope: !3465)
!3467 = !DILocation(line: 790, column: 7, scope: !3456)
!3468 = !DILocation(line: 791, column: 12, scope: !3465)
!3469 = !DILocation(line: 791, column: 4, scope: !3465)
!3470 = !DILocation(line: 792, column: 2, scope: !3456)
!3471 = !DILocalVariable(name: "p", scope: !3472, file: !1, line: 793, type: !218)
!3472 = distinct !DILexicalBlock(scope: !3453, file: !1, line: 792, column: 9)
!3473 = !DILocation(line: 793, column: 18, scope: !3472)
!3474 = !DILocation(line: 794, column: 33, scope: !3472)
!3475 = !DILocation(line: 794, column: 36, scope: !3472)
!3476 = !DILocation(line: 794, column: 48, scope: !3472)
!3477 = !DILocation(line: 794, column: 51, scope: !3472)
!3478 = !DILocation(line: 794, column: 7, scope: !3472)
!3479 = !DILocation(line: 794, column: 5, scope: !3472)
!3480 = !DILocation(line: 795, column: 7, scope: !3481)
!3481 = distinct !DILexicalBlock(scope: !3472, file: !1, line: 795, column: 7)
!3482 = !DILocation(line: 795, column: 9, scope: !3481)
!3483 = !DILocation(line: 795, column: 7, scope: !3472)
!3484 = !DILocation(line: 796, column: 12, scope: !3481)
!3485 = !DILocation(line: 796, column: 4, scope: !3481)
!3486 = !DILocation(line: 799, column: 6, scope: !3487)
!3487 = distinct !DILexicalBlock(scope: !297, file: !1, line: 799, column: 6)
!3488 = !DILocation(line: 799, column: 12, scope: !3487)
!3489 = !DILocation(line: 799, column: 6, scope: !297)
!3490 = !DILocation(line: 800, column: 23, scope: !3487)
!3491 = !DILocation(line: 800, column: 11, scope: !3487)
!3492 = !DILocation(line: 800, column: 3, scope: !3487)
!3493 = !DILocation(line: 801, column: 2, scope: !297)
!3494 = !DILocation(line: 802, column: 1, scope: !297)
!3495 = !DILocalVariable(name: "a", arg: 1, scope: !300, file: !1, line: 753, type: !4)
!3496 = !DILocation(line: 753, column: 44, scope: !300)
!3497 = !DILocalVariable(name: "m", arg: 2, scope: !300, file: !1, line: 753, type: !114)
!3498 = !DILocation(line: 753, column: 61, scope: !300)
!3499 = !DILocalVariable(name: "mbs", arg: 3, scope: !300, file: !1, line: 754, type: !22)
!3500 = !DILocation(line: 754, column: 9, scope: !300)
!3501 = !DILocalVariable(name: "pn", arg: 4, scope: !300, file: !1, line: 754, type: !42)
!3502 = !DILocation(line: 754, column: 26, scope: !300)
!3503 = !DILocalVariable(name: "flag", scope: !300, file: !1, line: 756, type: !22)
!3504 = !DILocation(line: 756, column: 6, scope: !300)
!3505 = !DILocalVariable(name: "r", scope: !300, file: !1, line: 757, type: !22)
!3506 = !DILocation(line: 757, column: 6, scope: !300)
!3507 = !DILocation(line: 759, column: 6, scope: !3508)
!3508 = distinct !DILexicalBlock(scope: !300, file: !1, line: 759, column: 6)
!3509 = !DILocation(line: 759, column: 6, scope: !300)
!3510 = !DILocalVariable(name: "p", scope: !3511, file: !1, line: 760, type: !79)
!3511 = distinct !DILexicalBlock(scope: !3508, file: !1, line: 759, column: 11)
!3512 = !DILocation(line: 760, column: 15, scope: !3511)
!3513 = !DILocation(line: 761, column: 33, scope: !3511)
!3514 = !DILocation(line: 761, column: 36, scope: !3511)
!3515 = !DILocation(line: 761, column: 48, scope: !3511)
!3516 = !DILocation(line: 761, column: 51, scope: !3511)
!3517 = !DILocation(line: 761, column: 7, scope: !3511)
!3518 = !DILocation(line: 761, column: 5, scope: !3511)
!3519 = !DILocation(line: 762, column: 7, scope: !3520)
!3520 = distinct !DILexicalBlock(scope: !3511, file: !1, line: 762, column: 7)
!3521 = !DILocation(line: 762, column: 9, scope: !3520)
!3522 = !DILocation(line: 762, column: 7, scope: !3511)
!3523 = !DILocation(line: 763, column: 12, scope: !3520)
!3524 = !DILocation(line: 763, column: 4, scope: !3520)
!3525 = !DILocation(line: 764, column: 2, scope: !3511)
!3526 = !DILocalVariable(name: "p", scope: !3527, file: !1, line: 765, type: !218)
!3527 = distinct !DILexicalBlock(scope: !3508, file: !1, line: 764, column: 9)
!3528 = !DILocation(line: 765, column: 18, scope: !3527)
!3529 = !DILocation(line: 766, column: 33, scope: !3527)
!3530 = !DILocation(line: 766, column: 36, scope: !3527)
!3531 = !DILocation(line: 766, column: 48, scope: !3527)
!3532 = !DILocation(line: 766, column: 51, scope: !3527)
!3533 = !DILocation(line: 766, column: 7, scope: !3527)
!3534 = !DILocation(line: 766, column: 5, scope: !3527)
!3535 = !DILocation(line: 767, column: 7, scope: !3536)
!3536 = distinct !DILexicalBlock(scope: !3527, file: !1, line: 767, column: 7)
!3537 = !DILocation(line: 767, column: 9, scope: !3536)
!3538 = !DILocation(line: 767, column: 7, scope: !3527)
!3539 = !DILocation(line: 768, column: 12, scope: !3536)
!3540 = !DILocation(line: 768, column: 4, scope: !3536)
!3541 = !DILocation(line: 771, column: 6, scope: !3542)
!3542 = distinct !DILexicalBlock(scope: !300, file: !1, line: 771, column: 6)
!3543 = !DILocation(line: 771, column: 12, scope: !3542)
!3544 = !DILocation(line: 771, column: 6, scope: !300)
!3545 = !DILocation(line: 772, column: 23, scope: !3542)
!3546 = !DILocation(line: 772, column: 11, scope: !3542)
!3547 = !DILocation(line: 772, column: 3, scope: !3542)
!3548 = !DILocation(line: 773, column: 2, scope: !300)
!3549 = !DILocation(line: 774, column: 1, scope: !300)
!3550 = !DILocalVariable(name: "a", arg: 1, scope: !319, file: !1, line: 1206, type: !4)
!3551 = !DILocation(line: 1206, column: 43, scope: !319)
!3552 = !DILocalVariable(name: "timetype", arg: 2, scope: !319, file: !1, line: 1206, type: !22)
!3553 = !DILocation(line: 1206, column: 50, scope: !319)
!3554 = !DILocalVariable(name: "st", arg: 3, scope: !319, file: !1, line: 1206, type: !322)
!3555 = !DILocation(line: 1206, column: 73, scope: !319)
!3556 = !DILocalVariable(name: "ae", scope: !319, file: !1, line: 1208, type: !29)
!3557 = !DILocation(line: 1208, column: 24, scope: !319)
!3558 = !DILocalVariable(name: "ctime_sec", scope: !319, file: !1, line: 1209, type: !142)
!3559 = !DILocation(line: 1209, column: 9, scope: !319)
!3560 = !DILocalVariable(name: "mtime_sec", scope: !319, file: !1, line: 1209, type: !142)
!3561 = !DILocation(line: 1209, column: 20, scope: !319)
!3562 = !DILocalVariable(name: "ctime_ns", scope: !319, file: !1, line: 1210, type: !41)
!3563 = !DILocation(line: 1210, column: 7, scope: !319)
!3564 = !DILocalVariable(name: "mtime_ns", scope: !319, file: !1, line: 1210, type: !41)
!3565 = !DILocation(line: 1210, column: 17, scope: !319)
!3566 = !DILocation(line: 1212, column: 7, scope: !319)
!3567 = !DILocation(line: 1212, column: 5, scope: !319)
!3568 = !DILocation(line: 1213, column: 6, scope: !3569)
!3569 = distinct !DILexicalBlock(scope: !319, file: !1, line: 1213, column: 6)
!3570 = !DILocation(line: 1213, column: 9, scope: !3569)
!3571 = !DILocation(line: 1213, column: 6, scope: !319)
!3572 = !DILocation(line: 1214, column: 23, scope: !3569)
!3573 = !DILocation(line: 1214, column: 11, scope: !3569)
!3574 = !DILocation(line: 1214, column: 3, scope: !3569)
!3575 = !DILocation(line: 1215, column: 26, scope: !319)
!3576 = !DILocation(line: 1215, column: 30, scope: !319)
!3577 = !DILocation(line: 1215, column: 2, scope: !319)
!3578 = !DILocation(line: 1216, column: 34, scope: !319)
!3579 = !DILocation(line: 1216, column: 14, scope: !319)
!3580 = !DILocation(line: 1216, column: 12, scope: !319)
!3581 = !DILocation(line: 1217, column: 38, scope: !319)
!3582 = !DILocation(line: 1217, column: 13, scope: !319)
!3583 = !DILocation(line: 1217, column: 11, scope: !319)
!3584 = !DILocation(line: 1218, column: 34, scope: !319)
!3585 = !DILocation(line: 1218, column: 14, scope: !319)
!3586 = !DILocation(line: 1218, column: 12, scope: !319)
!3587 = !DILocation(line: 1219, column: 38, scope: !319)
!3588 = !DILocation(line: 1219, column: 13, scope: !319)
!3589 = !DILocation(line: 1219, column: 11, scope: !319)
!3590 = !DILocation(line: 1220, column: 21, scope: !319)
!3591 = !DILocation(line: 1220, column: 2, scope: !319)
!3592 = !DILocation(line: 1221, column: 24, scope: !319)
!3593 = !DILocation(line: 1221, column: 27, scope: !319)
!3594 = !DILocation(line: 1221, column: 37, scope: !319)
!3595 = !DILocation(line: 1221, column: 48, scope: !319)
!3596 = !DILocation(line: 1222, column: 4, scope: !319)
!3597 = !DILocation(line: 1222, column: 15, scope: !319)
!3598 = !DILocation(line: 1221, column: 9, scope: !319)
!3599 = !DILocation(line: 1221, column: 2, scope: !319)
!3600 = !DILocation(line: 1223, column: 1, scope: !319)
!3601 = !DILocalVariable(name: "list", arg: 1, scope: !369, file: !1, line: 1355, type: !362)
!3602 = !DILocation(line: 1355, column: 35, scope: !369)
!3603 = !DILocalVariable(name: "file", arg: 2, scope: !369, file: !1, line: 1355, type: !194)
!3604 = !DILocation(line: 1355, column: 60, scope: !369)
!3605 = !DILocation(line: 1357, column: 16, scope: !369)
!3606 = !DILocation(line: 1357, column: 3, scope: !369)
!3607 = !DILocation(line: 1357, column: 9, scope: !369)
!3608 = !DILocation(line: 1357, column: 14, scope: !369)
!3609 = !DILocation(line: 1358, column: 17, scope: !369)
!3610 = !DILocation(line: 1358, column: 23, scope: !369)
!3611 = !DILocation(line: 1358, column: 2, scope: !369)
!3612 = !DILocation(line: 1358, column: 8, scope: !369)
!3613 = !DILocation(line: 1358, column: 13, scope: !369)
!3614 = !DILocation(line: 1359, column: 2, scope: !369)
!3615 = !DILocation(line: 1359, column: 8, scope: !369)
!3616 = !DILocation(line: 1359, column: 13, scope: !369)
!3617 = !DILocation(line: 1360, column: 1, scope: !369)
!3618 = !DILocalVariable(name: "n1", arg: 1, scope: !367, file: !1, line: 1305, type: !182)
!3619 = !DILocation(line: 1305, column: 44, scope: !367)
!3620 = !DILocalVariable(name: "n2", arg: 2, scope: !367, file: !1, line: 1306, type: !182)
!3621 = !DILocation(line: 1306, column: 35, scope: !367)
!3622 = !DILocalVariable(name: "f1", scope: !367, file: !1, line: 1308, type: !194)
!3623 = !DILocation(line: 1308, column: 21, scope: !367)
!3624 = !DILocation(line: 1308, column: 58, scope: !367)
!3625 = !DILocation(line: 1308, column: 47, scope: !367)
!3626 = !DILocation(line: 1308, column: 26, scope: !367)
!3627 = !DILocalVariable(name: "f2", scope: !367, file: !1, line: 1309, type: !194)
!3628 = !DILocation(line: 1309, column: 21, scope: !367)
!3629 = !DILocation(line: 1309, column: 58, scope: !367)
!3630 = !DILocation(line: 1309, column: 47, scope: !367)
!3631 = !DILocation(line: 1309, column: 26, scope: !367)
!3632 = !DILocalVariable(name: "p1", scope: !367, file: !1, line: 1310, type: !218)
!3633 = !DILocation(line: 1310, column: 17, scope: !367)
!3634 = !DILocalVariable(name: "p2", scope: !367, file: !1, line: 1310, type: !218)
!3635 = !DILocation(line: 1310, column: 22, scope: !367)
!3636 = !DILocation(line: 1312, column: 34, scope: !367)
!3637 = !DILocation(line: 1312, column: 38, scope: !367)
!3638 = !DILocation(line: 1312, column: 2, scope: !367)
!3639 = !DILocation(line: 1313, column: 34, scope: !367)
!3640 = !DILocation(line: 1313, column: 38, scope: !367)
!3641 = !DILocation(line: 1313, column: 2, scope: !367)
!3642 = !DILocation(line: 1314, column: 6, scope: !3643)
!3643 = distinct !DILexicalBlock(scope: !367, file: !1, line: 1314, column: 6)
!3644 = !DILocation(line: 1314, column: 9, scope: !3643)
!3645 = !DILocation(line: 1314, column: 6, scope: !367)
!3646 = !DILocation(line: 1315, column: 3, scope: !3643)
!3647 = !DILocation(line: 1316, column: 6, scope: !3648)
!3648 = distinct !DILexicalBlock(scope: !367, file: !1, line: 1316, column: 6)
!3649 = !DILocation(line: 1316, column: 9, scope: !3648)
!3650 = !DILocation(line: 1316, column: 6, scope: !367)
!3651 = !DILocation(line: 1317, column: 3, scope: !3648)
!3652 = !DILocation(line: 1318, column: 17, scope: !367)
!3653 = !DILocation(line: 1318, column: 21, scope: !367)
!3654 = !DILocation(line: 1318, column: 10, scope: !367)
!3655 = !DILocation(line: 1318, column: 2, scope: !367)
!3656 = !DILocation(line: 1319, column: 1, scope: !367)
!3657 = !DILocalVariable(name: "n", arg: 1, scope: !368, file: !1, line: 1322, type: !182)
!3658 = !DILocation(line: 1322, column: 43, scope: !368)
!3659 = !DILocalVariable(name: "key", arg: 2, scope: !368, file: !1, line: 1322, type: !42)
!3660 = !DILocation(line: 1322, column: 58, scope: !368)
!3661 = !DILocalVariable(name: "f", scope: !368, file: !1, line: 1324, type: !194)
!3662 = !DILocation(line: 1324, column: 21, scope: !368)
!3663 = !DILocation(line: 1324, column: 57, scope: !368)
!3664 = !DILocation(line: 1324, column: 46, scope: !368)
!3665 = !DILocation(line: 1324, column: 25, scope: !368)
!3666 = !DILocalVariable(name: "p", scope: !368, file: !1, line: 1325, type: !218)
!3667 = !DILocation(line: 1325, column: 17, scope: !368)
!3668 = !DILocation(line: 1327, column: 34, scope: !368)
!3669 = !DILocation(line: 1327, column: 37, scope: !368)
!3670 = !DILocation(line: 1327, column: 2, scope: !368)
!3671 = !DILocation(line: 1328, column: 6, scope: !3672)
!3672 = distinct !DILexicalBlock(scope: !368, file: !1, line: 1328, column: 6)
!3673 = !DILocation(line: 1328, column: 8, scope: !3672)
!3674 = !DILocation(line: 1328, column: 6, scope: !368)
!3675 = !DILocation(line: 1329, column: 3, scope: !3672)
!3676 = !DILocation(line: 1330, column: 17, scope: !368)
!3677 = !DILocation(line: 1330, column: 37, scope: !368)
!3678 = !DILocation(line: 1330, column: 20, scope: !368)
!3679 = !DILocation(line: 1330, column: 10, scope: !368)
!3680 = !DILocation(line: 1330, column: 2, scope: !368)
!3681 = !DILocation(line: 1331, column: 1, scope: !368)
!3682 = !DILocalVariable(name: "ids", arg: 1, scope: !383, file: !1, line: 1717, type: !378)
!3683 = !DILocation(line: 1717, column: 33, scope: !383)
!3684 = !DILocalVariable(name: "id", arg: 2, scope: !383, file: !1, line: 1717, type: !51)
!3685 = !DILocation(line: 1717, column: 46, scope: !383)
!3686 = !DILocalVariable(name: "b", scope: !383, file: !1, line: 1719, type: !12)
!3687 = !DILocation(line: 1719, column: 11, scope: !383)
!3688 = !DILocalVariable(name: "m", scope: !383, file: !1, line: 1719, type: !12)
!3689 = !DILocation(line: 1719, column: 14, scope: !383)
!3690 = !DILocalVariable(name: "t", scope: !383, file: !1, line: 1719, type: !12)
!3691 = !DILocation(line: 1719, column: 17, scope: !383)
!3692 = !DILocation(line: 1721, column: 4, scope: !383)
!3693 = !DILocation(line: 1722, column: 16, scope: !383)
!3694 = !DILocation(line: 1722, column: 21, scope: !383)
!3695 = !DILocation(line: 1722, column: 6, scope: !383)
!3696 = !DILocation(line: 1722, column: 4, scope: !383)
!3697 = !DILocation(line: 1723, column: 2, scope: !383)
!3698 = !DILocation(line: 1723, column: 9, scope: !3699)
!3699 = !DILexicalBlockFile(scope: !383, file: !1, discriminator: 1)
!3700 = !DILocation(line: 1723, column: 13, scope: !3699)
!3701 = !DILocation(line: 1723, column: 11, scope: !3699)
!3702 = !DILocation(line: 1723, column: 2, scope: !3699)
!3703 = !DILocation(line: 1724, column: 8, scope: !3704)
!3704 = distinct !DILexicalBlock(scope: !383, file: !1, line: 1723, column: 16)
!3705 = !DILocation(line: 1724, column: 12, scope: !3704)
!3706 = !DILocation(line: 1724, column: 10, scope: !3704)
!3707 = !DILocation(line: 1724, column: 14, scope: !3704)
!3708 = !DILocation(line: 1724, column: 5, scope: !3704)
!3709 = !DILocation(line: 1725, column: 16, scope: !3710)
!3710 = distinct !DILexicalBlock(scope: !3704, file: !1, line: 1725, column: 7)
!3711 = !DILocation(line: 1725, column: 7, scope: !3710)
!3712 = !DILocation(line: 1725, column: 12, scope: !3710)
!3713 = !DILocation(line: 1725, column: 22, scope: !3710)
!3714 = !DILocation(line: 1725, column: 19, scope: !3710)
!3715 = !DILocation(line: 1725, column: 7, scope: !3704)
!3716 = !DILocation(line: 1726, column: 4, scope: !3710)
!3717 = !DILocation(line: 1727, column: 16, scope: !3718)
!3718 = distinct !DILexicalBlock(scope: !3704, file: !1, line: 1727, column: 7)
!3719 = !DILocation(line: 1727, column: 7, scope: !3718)
!3720 = !DILocation(line: 1727, column: 12, scope: !3718)
!3721 = !DILocation(line: 1727, column: 21, scope: !3718)
!3722 = !DILocation(line: 1727, column: 19, scope: !3718)
!3723 = !DILocation(line: 1727, column: 7, scope: !3704)
!3724 = !DILocation(line: 1728, column: 8, scope: !3718)
!3725 = !DILocation(line: 1728, column: 10, scope: !3718)
!3726 = !DILocation(line: 1728, column: 6, scope: !3718)
!3727 = !DILocation(line: 1728, column: 4, scope: !3718)
!3728 = !DILocation(line: 1730, column: 8, scope: !3718)
!3729 = !DILocation(line: 1730, column: 6, scope: !3718)
!3730 = !DILocation(line: 1723, column: 2, scope: !3731)
!3731 = !DILexicalBlockFile(scope: !383, file: !1, discriminator: 2)
!3732 = !DILocation(line: 1732, column: 2, scope: !383)
!3733 = !DILocation(line: 1733, column: 1, scope: !383)
!3734 = !DILocalVariable(name: "a", arg: 1, scope: !386, file: !1, line: 1755, type: !4)
!3735 = !DILocation(line: 1755, column: 44, scope: !386)
!3736 = !DILocalVariable(name: "list", arg: 2, scope: !386, file: !1, line: 1755, type: !281)
!3737 = !DILocation(line: 1755, column: 66, scope: !386)
!3738 = !DILocalVariable(name: "name", arg: 3, scope: !386, file: !1, line: 1756, type: !79)
!3739 = !DILocation(line: 1756, column: 17, scope: !386)
!3740 = !DILocalVariable(name: "m", scope: !386, file: !1, line: 1758, type: !114)
!3741 = !DILocation(line: 1758, column: 16, scope: !386)
!3742 = !DILocalVariable(name: "p", scope: !386, file: !1, line: 1759, type: !79)
!3743 = !DILocation(line: 1759, column: 14, scope: !386)
!3744 = !DILocation(line: 1761, column: 6, scope: !3745)
!3745 = distinct !DILexicalBlock(scope: !386, file: !1, line: 1761, column: 6)
!3746 = !DILocation(line: 1761, column: 11, scope: !3745)
!3747 = !DILocation(line: 1761, column: 19, scope: !3745)
!3748 = !DILocation(line: 1761, column: 23, scope: !3749)
!3749 = !DILexicalBlockFile(scope: !3745, file: !1, discriminator: 1)
!3750 = !DILocation(line: 1761, column: 22, scope: !3749)
!3751 = !DILocation(line: 1761, column: 28, scope: !3749)
!3752 = !DILocation(line: 1761, column: 6, scope: !3749)
!3753 = !DILocation(line: 1762, column: 3, scope: !3745)
!3754 = !DILocation(line: 1763, column: 11, scope: !3755)
!3755 = distinct !DILexicalBlock(scope: !386, file: !1, line: 1763, column: 2)
!3756 = !DILocation(line: 1763, column: 17, scope: !3755)
!3757 = !DILocation(line: 1763, column: 9, scope: !3755)
!3758 = !DILocation(line: 1763, column: 7, scope: !3755)
!3759 = !DILocation(line: 1763, column: 24, scope: !3760)
!3760 = !DILexicalBlockFile(scope: !3761, file: !1, discriminator: 1)
!3761 = distinct !DILexicalBlock(scope: !3755, file: !1, line: 1763, column: 2)
!3762 = !DILocation(line: 1763, column: 2, scope: !3760)
!3763 = !DILocation(line: 1764, column: 33, scope: !3764)
!3764 = distinct !DILexicalBlock(scope: !3765, file: !1, line: 1764, column: 7)
!3765 = distinct !DILexicalBlock(scope: !3761, file: !1, line: 1763, column: 40)
!3766 = !DILocation(line: 1764, column: 36, scope: !3764)
!3767 = !DILocation(line: 1764, column: 48, scope: !3764)
!3768 = !DILocation(line: 1764, column: 51, scope: !3764)
!3769 = !DILocation(line: 1764, column: 7, scope: !3764)
!3770 = !DILocation(line: 1765, column: 7, scope: !3764)
!3771 = !DILocation(line: 1765, column: 11, scope: !3764)
!3772 = !DILocation(line: 1765, column: 14, scope: !3773)
!3773 = !DILexicalBlockFile(scope: !3764, file: !1, discriminator: 1)
!3774 = !DILocation(line: 1765, column: 20, scope: !3773)
!3775 = !DILocation(line: 1764, column: 7, scope: !3776)
!3776 = !DILexicalBlockFile(scope: !3765, file: !1, discriminator: 1)
!3777 = !DILocation(line: 1766, column: 24, scope: !3764)
!3778 = !DILocation(line: 1766, column: 12, scope: !3764)
!3779 = !DILocation(line: 1766, column: 4, scope: !3764)
!3780 = !DILocation(line: 1767, column: 7, scope: !3781)
!3781 = distinct !DILexicalBlock(scope: !3765, file: !1, line: 1767, column: 7)
!3782 = !DILocation(line: 1767, column: 9, scope: !3781)
!3783 = !DILocation(line: 1767, column: 17, scope: !3781)
!3784 = !DILocation(line: 1767, column: 27, scope: !3785)
!3785 = !DILexicalBlockFile(scope: !3781, file: !1, discriminator: 1)
!3786 = !DILocation(line: 1767, column: 30, scope: !3785)
!3787 = !DILocation(line: 1767, column: 20, scope: !3785)
!3788 = !DILocation(line: 1767, column: 36, scope: !3785)
!3789 = !DILocation(line: 1767, column: 7, scope: !3785)
!3790 = !DILocation(line: 1768, column: 4, scope: !3791)
!3791 = distinct !DILexicalBlock(scope: !3781, file: !1, line: 1767, column: 42)
!3792 = !DILocation(line: 1768, column: 7, scope: !3791)
!3793 = !DILocation(line: 1768, column: 14, scope: !3791)
!3794 = !DILocation(line: 1769, column: 4, scope: !3791)
!3795 = !DILocation(line: 1771, column: 2, scope: !3765)
!3796 = !DILocation(line: 1763, column: 31, scope: !3797)
!3797 = !DILexicalBlockFile(scope: !3761, file: !1, discriminator: 2)
!3798 = !DILocation(line: 1763, column: 34, scope: !3797)
!3799 = !DILocation(line: 1763, column: 29, scope: !3797)
!3800 = !DILocation(line: 1763, column: 2, scope: !3797)
!3801 = !DILocation(line: 1772, column: 2, scope: !386)
!3802 = !DILocation(line: 1773, column: 1, scope: !386)
