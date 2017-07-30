; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_disk_posix.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive_vtable = type { i32 (%struct.archive*)*, i32 (%struct.archive*)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)*, i8* (%struct.archive*, i32)* }
%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque
%struct.archive_entry = type opaque
%struct.stat = type { i64, i64, i64, i32, i32, i32, i32, i64, i64, i64, i64, %struct.timespec, %struct.timespec, %struct.timespec, [3 x i64] }
%struct.timespec = type { i64, i64 }
%struct.archive_read_disk = type { %struct.archive, %struct.archive_entry*, i8, i8, %struct.tree*, i32 (%struct.tree*, i8*, i32)*, i32 (%struct.tree*)*, i32 (%struct.tree*)*, i32, i8* (i8*, i64)*, void (i8*)*, i8*, i8* (i8*, i64)*, void (i8*)*, i8*, i32 (%struct.archive*, i8*, %struct.archive_entry*)*, i8*, %struct.archive*, void (%struct.archive*, i8*, %struct.archive_entry*)*, i8* }
%struct.tree = type { %struct.tree_entry*, %struct.tree_entry*, %struct.__dirstream*, %struct.dirent*, %struct.dirent*, i64, i32, i32, i32, %struct.archive_string, i8*, i64, i32, i32, i32, i32, i32, %struct.stat, %struct.stat, i32, i32, %struct.restore_time, %struct.entry_sparse*, %struct.entry_sparse*, i32, i32, i8, i8, %struct.filesystem*, %struct.filesystem*, i32, i32, i32, i32, i32, i32, i64, i64, i8*, i64 }
%struct.tree_entry = type { i32, %struct.tree_entry*, %struct.tree_entry*, %struct.archive_string, i64, i64, i64, i32, i32, i32, %struct.restore_time }
%struct.__dirstream = type opaque
%struct.dirent = type { i64, i64, i16, i8, [256 x i8] }
%struct.restore_time = type { i8*, i64, i64, i64, i64, i32, i32 }
%struct.entry_sparse = type { i64, i64 }
%struct.filesystem = type { i64, i32, i32, i32, i64, i64, i64, i64, i64, i8*, i8*, i64 }
%struct.timeval = type { i64, i64 }
%struct.statfs = type { i64, i64, i64, i64, i64, i64, i64, %struct.__fsid_t, i64, i64, i64, [4 x i64] }
%struct.__fsid_t = type { [2 x i32] }
%struct.statvfs = type { i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, [6 x i32] }

@.str = private unnamed_addr constant [24 x i8] c"archive_read_disk_gname\00", align 1
@.str.1 = private unnamed_addr constant [24 x i8] c"archive_read_disk_uname\00", align 1
@.str.2 = private unnamed_addr constant [35 x i8] c"archive_read_disk_set_gname_lookup\00", align 1
@.str.3 = private unnamed_addr constant [35 x i8] c"archive_read_disk_set_uname_lookup\00", align 1
@.str.4 = private unnamed_addr constant [38 x i8] c"archive_read_disk_set_symlink_logical\00", align 1
@.str.5 = private unnamed_addr constant [39 x i8] c"archive_read_disk_set_symlink_physical\00", align 1
@.str.6 = private unnamed_addr constant [37 x i8] c"archive_read_disk_set_symlink_hybrid\00", align 1
@.str.7 = private unnamed_addr constant [32 x i8] c"archive_read_disk_restore_atime\00", align 1
@.str.8 = private unnamed_addr constant [31 x i8] c"archive_read_disk_honor_nodump\00", align 1
@.str.9 = private unnamed_addr constant [31 x i8] c"archive_read_disk_set_matching\00", align 1
@.str.10 = private unnamed_addr constant [47 x i8] c"archive_read_disk_set_metadata_filter_callback\00", align 1
@.str.11 = private unnamed_addr constant [30 x i8] c"archive_read_disk_can_descend\00", align 1
@.str.12 = private unnamed_addr constant [26 x i8] c"archive_read_disk_descend\00", align 1
@.str.13 = private unnamed_addr constant [23 x i8] c"archive_read_disk_open\00", align 1
@.str.14 = private unnamed_addr constant [25 x i8] c"archive_read_disk_open_w\00", align 1
@.str.15 = private unnamed_addr constant [22 x i8] c"Can't allocate memory\00", align 1
@.str.16 = private unnamed_addr constant [38 x i8] c"Can't convert a path to a char string\00", align 1
@.str.17 = private unnamed_addr constant [37 x i8] c"archive_read_disk_current_filesystem\00", align 1
@archive_read_disk_vtable.av = internal global %struct.archive_vtable zeroinitializer, align 8
@archive_read_disk_vtable.inited = internal global i32 0, align 4
@.str.18 = private unnamed_addr constant [18 x i8] c"archive_read_free\00", align 1
@.str.19 = private unnamed_addr constant [19 x i8] c"archive_read_close\00", align 1
@.str.20 = private unnamed_addr constant [24 x i8] c"archive_read_data_block\00", align 1
@.str.21 = private unnamed_addr constant [17 x i8] c"Couldn't open %s\00", align 1
@.str.22 = private unnamed_addr constant [11 x i8] c"Seek error\00", align 1
@.str.23 = private unnamed_addr constant [11 x i8] c"Read error\00", align 1
@.str.24 = private unnamed_addr constant [25 x i8] c"Couldn't allocate memory\00", align 1
@.str.25 = private unnamed_addr constant [26 x i8] c"archive_read_next_header2\00", align 1
@.str.26 = private unnamed_addr constant [49 x i8] c"%s: Unable to continue traversing directory tree\00", align 1
@.str.27 = private unnamed_addr constant [29 x i8] c"%s: Couldn't visit directory\00", align 1
@.str.28 = private unnamed_addr constant [16 x i8] c"%s: Cannot stat\00", align 1
@.str.29 = private unnamed_addr constant [12 x i8] c"Failed : %s\00", align 1
@tree_dup.can_dupfd_cloexec = internal global i32 1, align 4
@.str.30 = private unnamed_addr constant [3 x i8] c"..\00", align 1
@.str.31 = private unnamed_addr constant [24 x i8] c"Can't allocate tar data\00", align 1
@.str.32 = private unnamed_addr constant [14 x i8] c"openat failed\00", align 1
@.str.33 = private unnamed_addr constant [14 x i8] c"statfs failed\00", align 1
@tree_current_is_symblic_link_target.lst = internal global %struct.stat* null, align 8
@tree_current_is_symblic_link_target.st = internal global %struct.stat* null, align 8
@.str.34 = private unnamed_addr constant [20 x i8] c"Can't allocate data\00", align 1
@.str.35 = private unnamed_addr constant [2 x i8] c".\00", align 1

; Function Attrs: nounwind uwtable
define i8* @archive_read_disk_gname(%struct.archive* %_a, i64 %gid) #0 !dbg !334 {
entry:
  %retval = alloca i8*, align 8
  %_a.addr = alloca %struct.archive*, align 8
  %gid.addr = alloca i64, align 8
  %a = alloca %struct.archive_read_disk*, align 8
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !459, metadata !460), !dbg !461
  store i64 %gid, i64* %gid.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %gid.addr, metadata !462, metadata !460), !dbg !463
  call void @llvm.dbg.declare(metadata %struct.archive_read_disk** %a, metadata !464, metadata !460), !dbg !465
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !466
  %1 = bitcast %struct.archive* %0 to %struct.archive_read_disk*, !dbg !467
  store %struct.archive_read_disk* %1, %struct.archive_read_disk** %a, align 8, !dbg !465
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !468
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 195932357, i32 32767, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str, i32 0, i32 0)), !dbg !470
  %cmp = icmp ne i32 0, %call, !dbg !471
  br i1 %cmp, label %if.then, label %if.end, !dbg !472

if.then:                                          ; preds = %entry
  store i8* null, i8** %retval, align 8, !dbg !473
  br label %return, !dbg !473

if.end:                                           ; preds = %entry
  %3 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !474
  %lookup_gname = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %3, i32 0, i32 9, !dbg !476
  %4 = load i8* (i8*, i64)*, i8* (i8*, i64)** %lookup_gname, align 8, !dbg !476
  %cmp1 = icmp eq i8* (i8*, i64)* %4, null, !dbg !477
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !478

if.then2:                                         ; preds = %if.end
  store i8* null, i8** %retval, align 8, !dbg !479
  br label %return, !dbg !479

if.end3:                                          ; preds = %if.end
  %5 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !480
  %lookup_gname4 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %5, i32 0, i32 9, !dbg !481
  %6 = load i8* (i8*, i64)*, i8* (i8*, i64)** %lookup_gname4, align 8, !dbg !481
  %7 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !482
  %lookup_gname_data = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %7, i32 0, i32 11, !dbg !483
  %8 = load i8*, i8** %lookup_gname_data, align 8, !dbg !483
  %9 = load i64, i64* %gid.addr, align 8, !dbg !484
  %call5 = call i8* %6(i8* %8, i64 %9), !dbg !485
  store i8* %call5, i8** %retval, align 8, !dbg !486
  br label %return, !dbg !486

return:                                           ; preds = %if.end3, %if.then2, %if.then
  %10 = load i8*, i8** %retval, align 8, !dbg !487
  ret i8* %10, !dbg !487
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @__archive_check_magic(%struct.archive*, i32, i32, i8*) #2

; Function Attrs: nounwind uwtable
define i8* @archive_read_disk_uname(%struct.archive* %_a, i64 %uid) #0 !dbg !338 {
entry:
  %retval = alloca i8*, align 8
  %_a.addr = alloca %struct.archive*, align 8
  %uid.addr = alloca i64, align 8
  %a = alloca %struct.archive_read_disk*, align 8
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !488, metadata !460), !dbg !489
  store i64 %uid, i64* %uid.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %uid.addr, metadata !490, metadata !460), !dbg !491
  call void @llvm.dbg.declare(metadata %struct.archive_read_disk** %a, metadata !492, metadata !460), !dbg !493
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !494
  %1 = bitcast %struct.archive* %0 to %struct.archive_read_disk*, !dbg !495
  store %struct.archive_read_disk* %1, %struct.archive_read_disk** %a, align 8, !dbg !493
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !496
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 195932357, i32 32767, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.1, i32 0, i32 0)), !dbg !498
  %cmp = icmp ne i32 0, %call, !dbg !499
  br i1 %cmp, label %if.then, label %if.end, !dbg !500

if.then:                                          ; preds = %entry
  store i8* null, i8** %retval, align 8, !dbg !501
  br label %return, !dbg !501

if.end:                                           ; preds = %entry
  %3 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !502
  %lookup_uname = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %3, i32 0, i32 12, !dbg !504
  %4 = load i8* (i8*, i64)*, i8* (i8*, i64)** %lookup_uname, align 8, !dbg !504
  %cmp1 = icmp eq i8* (i8*, i64)* %4, null, !dbg !505
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !506

if.then2:                                         ; preds = %if.end
  store i8* null, i8** %retval, align 8, !dbg !507
  br label %return, !dbg !507

if.end3:                                          ; preds = %if.end
  %5 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !508
  %lookup_uname4 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %5, i32 0, i32 12, !dbg !509
  %6 = load i8* (i8*, i64)*, i8* (i8*, i64)** %lookup_uname4, align 8, !dbg !509
  %7 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !510
  %lookup_uname_data = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %7, i32 0, i32 14, !dbg !511
  %8 = load i8*, i8** %lookup_uname_data, align 8, !dbg !511
  %9 = load i64, i64* %uid.addr, align 8, !dbg !512
  %call5 = call i8* %6(i8* %8, i64 %9), !dbg !513
  store i8* %call5, i8** %retval, align 8, !dbg !514
  br label %return, !dbg !514

return:                                           ; preds = %if.end3, %if.then2, %if.then
  %10 = load i8*, i8** %retval, align 8, !dbg !515
  ret i8* %10, !dbg !515
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_disk_set_gname_lookup(%struct.archive* %_a, i8* %private_data, i8* (i8*, i64)* %lookup_gname, void (i8*)* %cleanup_gname) #0 !dbg !339 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %private_data.addr = alloca i8*, align 8
  %lookup_gname.addr = alloca i8* (i8*, i64)*, align 8
  %cleanup_gname.addr = alloca void (i8*)*, align 8
  %a = alloca %struct.archive_read_disk*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !516, metadata !460), !dbg !517
  store i8* %private_data, i8** %private_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %private_data.addr, metadata !518, metadata !460), !dbg !519
  store i8* (i8*, i64)* %lookup_gname, i8* (i8*, i64)** %lookup_gname.addr, align 8
  call void @llvm.dbg.declare(metadata i8* (i8*, i64)** %lookup_gname.addr, metadata !520, metadata !460), !dbg !521
  store void (i8*)* %cleanup_gname, void (i8*)** %cleanup_gname.addr, align 8
  call void @llvm.dbg.declare(metadata void (i8*)** %cleanup_gname.addr, metadata !522, metadata !460), !dbg !523
  call void @llvm.dbg.declare(metadata %struct.archive_read_disk** %a, metadata !524, metadata !460), !dbg !525
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !526
  %1 = bitcast %struct.archive* %0 to %struct.archive_read_disk*, !dbg !527
  store %struct.archive_read_disk* %1, %struct.archive_read_disk** %a, align 8, !dbg !525
  br label %do.body, !dbg !528

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !529, metadata !460), !dbg !531
  %2 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !532
  %archive = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %2, i32 0, i32 0, !dbg !532
  %call = call i32 @__archive_check_magic(%struct.archive* %archive, i32 195932357, i32 32767, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.2, i32 0, i32 0)), !dbg !532
  store i32 %call, i32* %magic_test, align 4, !dbg !532
  %3 = load i32, i32* %magic_test, align 4, !dbg !532
  %cmp = icmp eq i32 %3, -30, !dbg !532
  br i1 %cmp, label %if.then, label %if.end, !dbg !532

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !534
  br label %return, !dbg !534

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !537

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !539
  %cleanup_gname1 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %4, i32 0, i32 10, !dbg !541
  %5 = load void (i8*)*, void (i8*)** %cleanup_gname1, align 8, !dbg !541
  %cmp2 = icmp ne void (i8*)* %5, null, !dbg !542
  br i1 %cmp2, label %land.lhs.true, label %if.end7, !dbg !543

land.lhs.true:                                    ; preds = %do.end
  %6 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !544
  %lookup_gname_data = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %6, i32 0, i32 11, !dbg !546
  %7 = load i8*, i8** %lookup_gname_data, align 8, !dbg !546
  %cmp3 = icmp ne i8* %7, null, !dbg !547
  br i1 %cmp3, label %if.then4, label %if.end7, !dbg !548

if.then4:                                         ; preds = %land.lhs.true
  %8 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !549
  %cleanup_gname5 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %8, i32 0, i32 10, !dbg !550
  %9 = load void (i8*)*, void (i8*)** %cleanup_gname5, align 8, !dbg !550
  %10 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !551
  %lookup_gname_data6 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %10, i32 0, i32 11, !dbg !552
  %11 = load i8*, i8** %lookup_gname_data6, align 8, !dbg !552
  call void %9(i8* %11), !dbg !553
  br label %if.end7, !dbg !553

if.end7:                                          ; preds = %if.then4, %land.lhs.true, %do.end
  %12 = load i8* (i8*, i64)*, i8* (i8*, i64)** %lookup_gname.addr, align 8, !dbg !554
  %13 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !555
  %lookup_gname8 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %13, i32 0, i32 9, !dbg !556
  store i8* (i8*, i64)* %12, i8* (i8*, i64)** %lookup_gname8, align 8, !dbg !557
  %14 = load void (i8*)*, void (i8*)** %cleanup_gname.addr, align 8, !dbg !558
  %15 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !559
  %cleanup_gname9 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %15, i32 0, i32 10, !dbg !560
  store void (i8*)* %14, void (i8*)** %cleanup_gname9, align 8, !dbg !561
  %16 = load i8*, i8** %private_data.addr, align 8, !dbg !562
  %17 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !563
  %lookup_gname_data10 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %17, i32 0, i32 11, !dbg !564
  store i8* %16, i8** %lookup_gname_data10, align 8, !dbg !565
  store i32 0, i32* %retval, align 4, !dbg !566
  br label %return, !dbg !566

return:                                           ; preds = %if.end7, %if.then
  %18 = load i32, i32* %retval, align 4, !dbg !567
  ret i32 %18, !dbg !567
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_disk_set_uname_lookup(%struct.archive* %_a, i8* %private_data, i8* (i8*, i64)* %lookup_uname, void (i8*)* %cleanup_uname) #0 !dbg !342 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %private_data.addr = alloca i8*, align 8
  %lookup_uname.addr = alloca i8* (i8*, i64)*, align 8
  %cleanup_uname.addr = alloca void (i8*)*, align 8
  %a = alloca %struct.archive_read_disk*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !568, metadata !460), !dbg !569
  store i8* %private_data, i8** %private_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %private_data.addr, metadata !570, metadata !460), !dbg !571
  store i8* (i8*, i64)* %lookup_uname, i8* (i8*, i64)** %lookup_uname.addr, align 8
  call void @llvm.dbg.declare(metadata i8* (i8*, i64)** %lookup_uname.addr, metadata !572, metadata !460), !dbg !573
  store void (i8*)* %cleanup_uname, void (i8*)** %cleanup_uname.addr, align 8
  call void @llvm.dbg.declare(metadata void (i8*)** %cleanup_uname.addr, metadata !574, metadata !460), !dbg !575
  call void @llvm.dbg.declare(metadata %struct.archive_read_disk** %a, metadata !576, metadata !460), !dbg !577
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !578
  %1 = bitcast %struct.archive* %0 to %struct.archive_read_disk*, !dbg !579
  store %struct.archive_read_disk* %1, %struct.archive_read_disk** %a, align 8, !dbg !577
  br label %do.body, !dbg !580

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !581, metadata !460), !dbg !583
  %2 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !584
  %archive = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %2, i32 0, i32 0, !dbg !584
  %call = call i32 @__archive_check_magic(%struct.archive* %archive, i32 195932357, i32 32767, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.3, i32 0, i32 0)), !dbg !584
  store i32 %call, i32* %magic_test, align 4, !dbg !584
  %3 = load i32, i32* %magic_test, align 4, !dbg !584
  %cmp = icmp eq i32 %3, -30, !dbg !584
  br i1 %cmp, label %if.then, label %if.end, !dbg !584

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !586
  br label %return, !dbg !586

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !589

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !591
  %cleanup_uname1 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %4, i32 0, i32 13, !dbg !593
  %5 = load void (i8*)*, void (i8*)** %cleanup_uname1, align 8, !dbg !593
  %cmp2 = icmp ne void (i8*)* %5, null, !dbg !594
  br i1 %cmp2, label %land.lhs.true, label %if.end7, !dbg !595

land.lhs.true:                                    ; preds = %do.end
  %6 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !596
  %lookup_uname_data = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %6, i32 0, i32 14, !dbg !598
  %7 = load i8*, i8** %lookup_uname_data, align 8, !dbg !598
  %cmp3 = icmp ne i8* %7, null, !dbg !599
  br i1 %cmp3, label %if.then4, label %if.end7, !dbg !600

if.then4:                                         ; preds = %land.lhs.true
  %8 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !601
  %cleanup_uname5 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %8, i32 0, i32 13, !dbg !602
  %9 = load void (i8*)*, void (i8*)** %cleanup_uname5, align 8, !dbg !602
  %10 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !603
  %lookup_uname_data6 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %10, i32 0, i32 14, !dbg !604
  %11 = load i8*, i8** %lookup_uname_data6, align 8, !dbg !604
  call void %9(i8* %11), !dbg !605
  br label %if.end7, !dbg !605

if.end7:                                          ; preds = %if.then4, %land.lhs.true, %do.end
  %12 = load i8* (i8*, i64)*, i8* (i8*, i64)** %lookup_uname.addr, align 8, !dbg !606
  %13 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !607
  %lookup_uname8 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %13, i32 0, i32 12, !dbg !608
  store i8* (i8*, i64)* %12, i8* (i8*, i64)** %lookup_uname8, align 8, !dbg !609
  %14 = load void (i8*)*, void (i8*)** %cleanup_uname.addr, align 8, !dbg !610
  %15 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !611
  %cleanup_uname9 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %15, i32 0, i32 13, !dbg !612
  store void (i8*)* %14, void (i8*)** %cleanup_uname9, align 8, !dbg !613
  %16 = load i8*, i8** %private_data.addr, align 8, !dbg !614
  %17 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !615
  %lookup_uname_data10 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %17, i32 0, i32 14, !dbg !616
  store i8* %16, i8** %lookup_uname_data10, align 8, !dbg !617
  store i32 0, i32* %retval, align 4, !dbg !618
  br label %return, !dbg !618

return:                                           ; preds = %if.end7, %if.then
  %18 = load i32, i32* %retval, align 4, !dbg !619
  ret i32 %18, !dbg !619
}

; Function Attrs: nounwind uwtable
define %struct.archive* @archive_read_disk_new() #0 !dbg !343 {
entry:
  %retval = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_read_disk*, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_disk** %a, metadata !620, metadata !460), !dbg !621
  %call = call noalias i8* @calloc(i64 1, i64 304) #6, !dbg !622
  %0 = bitcast i8* %call to %struct.archive_read_disk*, !dbg !623
  store %struct.archive_read_disk* %0, %struct.archive_read_disk** %a, align 8, !dbg !624
  %1 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !625
  %cmp = icmp eq %struct.archive_read_disk* %1, null, !dbg !627
  br i1 %cmp, label %if.then, label %if.end, !dbg !628

if.then:                                          ; preds = %entry
  store %struct.archive* null, %struct.archive** %retval, align 8, !dbg !629
  br label %return, !dbg !629

if.end:                                           ; preds = %entry
  %2 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !630
  %archive = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %2, i32 0, i32 0, !dbg !631
  %magic = getelementptr inbounds %struct.archive, %struct.archive* %archive, i32 0, i32 0, !dbg !632
  store i32 195932357, i32* %magic, align 8, !dbg !633
  %3 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !634
  %archive1 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %3, i32 0, i32 0, !dbg !635
  %state = getelementptr inbounds %struct.archive, %struct.archive* %archive1, i32 0, i32 1, !dbg !636
  store i32 1, i32* %state, align 4, !dbg !637
  %call2 = call %struct.archive_vtable* @archive_read_disk_vtable(), !dbg !638
  %4 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !639
  %archive3 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %4, i32 0, i32 0, !dbg !640
  %vtable = getelementptr inbounds %struct.archive, %struct.archive* %archive3, i32 0, i32 2, !dbg !641
  store %struct.archive_vtable* %call2, %struct.archive_vtable** %vtable, align 8, !dbg !642
  %5 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !643
  %archive4 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %5, i32 0, i32 0, !dbg !644
  %call5 = call %struct.archive_entry* @archive_entry_new2(%struct.archive* %archive4), !dbg !645
  %6 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !646
  %entry6 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %6, i32 0, i32 1, !dbg !647
  store %struct.archive_entry* %call5, %struct.archive_entry** %entry6, align 8, !dbg !648
  %7 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !649
  %lookup_uname = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %7, i32 0, i32 12, !dbg !650
  store i8* (i8*, i64)* @trivial_lookup_uname, i8* (i8*, i64)** %lookup_uname, align 8, !dbg !651
  %8 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !652
  %lookup_gname = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %8, i32 0, i32 9, !dbg !653
  store i8* (i8*, i64)* @trivial_lookup_gname, i8* (i8*, i64)** %lookup_gname, align 8, !dbg !654
  %9 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !655
  %flags = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %9, i32 0, i32 8, !dbg !656
  store i32 4, i32* %flags, align 8, !dbg !657
  %10 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !658
  %open_on_current_dir = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %10, i32 0, i32 5, !dbg !659
  store i32 (%struct.tree*, i8*, i32)* @open_on_current_dir, i32 (%struct.tree*, i8*, i32)** %open_on_current_dir, align 8, !dbg !660
  %11 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !661
  %tree_current_dir_fd = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %11, i32 0, i32 6, !dbg !662
  store i32 (%struct.tree*)* @tree_current_dir_fd, i32 (%struct.tree*)** %tree_current_dir_fd, align 8, !dbg !663
  %12 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !664
  %tree_enter_working_dir = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %12, i32 0, i32 7, !dbg !665
  store i32 (%struct.tree*)* @tree_enter_working_dir, i32 (%struct.tree*)** %tree_enter_working_dir, align 8, !dbg !666
  %13 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !667
  %archive7 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %13, i32 0, i32 0, !dbg !668
  store %struct.archive* %archive7, %struct.archive** %retval, align 8, !dbg !669
  br label %return, !dbg !669

return:                                           ; preds = %if.end, %if.then
  %14 = load %struct.archive*, %struct.archive** %retval, align 8, !dbg !670
  ret %struct.archive* %14, !dbg !670
}

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #3

; Function Attrs: nounwind uwtable
define internal %struct.archive_vtable* @archive_read_disk_vtable() #0 !dbg !371 {
entry:
  %0 = load i32, i32* @archive_read_disk_vtable.inited, align 4, !dbg !671
  %tobool = icmp ne i32 %0, 0, !dbg !671
  br i1 %tobool, label %if.end, label %if.then, !dbg !673

if.then:                                          ; preds = %entry
  store i32 (%struct.archive*)* @_archive_read_free, i32 (%struct.archive*)** getelementptr inbounds (%struct.archive_vtable, %struct.archive_vtable* @archive_read_disk_vtable.av, i32 0, i32 1), align 8, !dbg !674
  store i32 (%struct.archive*)* @_archive_read_close, i32 (%struct.archive*)** getelementptr inbounds (%struct.archive_vtable, %struct.archive_vtable* @archive_read_disk_vtable.av, i32 0, i32 0), align 8, !dbg !676
  store i32 (%struct.archive*, i8**, i64*, i64*)* @_archive_read_data_block, i32 (%struct.archive*, i8**, i64*, i64*)** getelementptr inbounds (%struct.archive_vtable, %struct.archive_vtable* @archive_read_disk_vtable.av, i32 0, i32 8), align 8, !dbg !677
  store i32 (%struct.archive*, %struct.archive_entry**)* @_archive_read_next_header, i32 (%struct.archive*, %struct.archive_entry**)** getelementptr inbounds (%struct.archive_vtable, %struct.archive_vtable* @archive_read_disk_vtable.av, i32 0, i32 6), align 8, !dbg !678
  store i32 (%struct.archive*, %struct.archive_entry*)* @_archive_read_next_header2, i32 (%struct.archive*, %struct.archive_entry*)** getelementptr inbounds (%struct.archive_vtable, %struct.archive_vtable* @archive_read_disk_vtable.av, i32 0, i32 7), align 8, !dbg !679
  store i32 1, i32* @archive_read_disk_vtable.inited, align 4, !dbg !680
  br label %if.end, !dbg !681

if.end:                                           ; preds = %if.then, %entry
  ret %struct.archive_vtable* @archive_read_disk_vtable.av, !dbg !682
}

declare %struct.archive_entry* @archive_entry_new2(%struct.archive*) #2

; Function Attrs: nounwind uwtable
define internal i8* @trivial_lookup_uname(i8* %private_data, i64 %uid) #0 !dbg !433 {
entry:
  %private_data.addr = alloca i8*, align 8
  %uid.addr = alloca i64, align 8
  store i8* %private_data, i8** %private_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %private_data.addr, metadata !683, metadata !460), !dbg !684
  store i64 %uid, i64* %uid.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %uid.addr, metadata !685, metadata !460), !dbg !686
  %0 = load i8*, i8** %private_data.addr, align 8, !dbg !687
  %1 = load i64, i64* %uid.addr, align 8, !dbg !688
  ret i8* null, !dbg !689
}

; Function Attrs: nounwind uwtable
define internal i8* @trivial_lookup_gname(i8* %private_data, i64 %gid) #0 !dbg !432 {
entry:
  %private_data.addr = alloca i8*, align 8
  %gid.addr = alloca i64, align 8
  store i8* %private_data, i8** %private_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %private_data.addr, metadata !690, metadata !460), !dbg !691
  store i64 %gid, i64* %gid.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %gid.addr, metadata !692, metadata !460), !dbg !693
  %0 = load i8*, i8** %private_data.addr, align 8, !dbg !694
  %1 = load i64, i64* %gid.addr, align 8, !dbg !695
  ret i8* null, !dbg !696
}

; Function Attrs: nounwind uwtable
define internal i32 @open_on_current_dir(%struct.tree* %t, i8* %path, i32 %flags) #0 !dbg !441 {
entry:
  %t.addr = alloca %struct.tree*, align 8
  %path.addr = alloca i8*, align 8
  %flags.addr = alloca i32, align 4
  store %struct.tree* %t, %struct.tree** %t.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tree** %t.addr, metadata !697, metadata !460), !dbg !698
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !699, metadata !460), !dbg !700
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !701, metadata !460), !dbg !702
  %0 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !703
  %call = call i32 @tree_current_dir_fd(%struct.tree* %0), !dbg !704
  %1 = load i8*, i8** %path.addr, align 8, !dbg !705
  %2 = load i32, i32* %flags.addr, align 4, !dbg !706
  %call1 = call i32 (i32, i8*, i32, ...) @openat(i32 %call, i8* %1, i32 %2), !dbg !707
  ret i32 %call1, !dbg !709
}

; Function Attrs: nounwind uwtable
define internal i32 @tree_current_dir_fd(%struct.tree* %t) #0 !dbg !446 {
entry:
  %t.addr = alloca %struct.tree*, align 8
  store %struct.tree* %t, %struct.tree** %t.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tree** %t.addr, metadata !710, metadata !460), !dbg !711
  %0 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !712
  %working_dir_fd = getelementptr inbounds %struct.tree, %struct.tree* %0, i32 0, i32 16, !dbg !713
  %1 = load i32, i32* %working_dir_fd, align 8, !dbg !713
  ret i32 %1, !dbg !714
}

; Function Attrs: nounwind uwtable
define internal i32 @tree_enter_working_dir(%struct.tree* %t) #0 !dbg !445 {
entry:
  %t.addr = alloca %struct.tree*, align 8
  %r = alloca i32, align 4
  store %struct.tree* %t, %struct.tree** %t.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tree** %t.addr, metadata !715, metadata !460), !dbg !716
  call void @llvm.dbg.declare(metadata i32* %r, metadata !717, metadata !460), !dbg !718
  store i32 0, i32* %r, align 4, !dbg !718
  %0 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !719
  %depth = getelementptr inbounds %struct.tree, %struct.tree* %0, i32 0, i32 12, !dbg !721
  %1 = load i32, i32* %depth, align 8, !dbg !721
  %cmp = icmp sgt i32 %1, 0, !dbg !722
  br i1 %cmp, label %land.lhs.true, label %if.end7, !dbg !723

land.lhs.true:                                    ; preds = %entry
  %2 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !724
  %flags = getelementptr inbounds %struct.tree, %struct.tree* %2, i32 0, i32 6, !dbg !726
  %3 = load i32, i32* %flags, align 8, !dbg !726
  %and = and i32 %3, 64, !dbg !727
  %cmp1 = icmp eq i32 %and, 0, !dbg !728
  br i1 %cmp1, label %if.then, label %if.end7, !dbg !729

if.then:                                          ; preds = %land.lhs.true
  %4 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !730
  %working_dir_fd = getelementptr inbounds %struct.tree, %struct.tree* %4, i32 0, i32 16, !dbg !732
  %5 = load i32, i32* %working_dir_fd, align 8, !dbg !732
  %call = call i32 @fchdir(i32 %5) #6, !dbg !733
  store i32 %call, i32* %r, align 4, !dbg !734
  %6 = load i32, i32* %r, align 4, !dbg !735
  %cmp2 = icmp eq i32 %6, 0, !dbg !737
  br i1 %cmp2, label %if.then3, label %if.end, !dbg !738

if.then3:                                         ; preds = %if.then
  %7 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !739
  %flags4 = getelementptr inbounds %struct.tree, %struct.tree* %7, i32 0, i32 6, !dbg !741
  %8 = load i32, i32* %flags4, align 8, !dbg !742
  %and5 = and i32 %8, -257, !dbg !742
  store i32 %and5, i32* %flags4, align 8, !dbg !742
  %9 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !743
  %flags6 = getelementptr inbounds %struct.tree, %struct.tree* %9, i32 0, i32 6, !dbg !744
  %10 = load i32, i32* %flags6, align 8, !dbg !745
  %or = or i32 %10, 64, !dbg !745
  store i32 %or, i32* %flags6, align 8, !dbg !745
  br label %if.end, !dbg !746

if.end:                                           ; preds = %if.then3, %if.then
  br label %if.end7, !dbg !747

if.end7:                                          ; preds = %if.end, %land.lhs.true, %entry
  %11 = load i32, i32* %r, align 4, !dbg !748
  ret i32 %11, !dbg !749
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_disk_set_symlink_logical(%struct.archive* %_a) #0 !dbg !346 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_read_disk*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !750, metadata !460), !dbg !751
  call void @llvm.dbg.declare(metadata %struct.archive_read_disk** %a, metadata !752, metadata !460), !dbg !753
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !754
  %1 = bitcast %struct.archive* %0 to %struct.archive_read_disk*, !dbg !755
  store %struct.archive_read_disk* %1, %struct.archive_read_disk** %a, align 8, !dbg !753
  br label %do.body, !dbg !756

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !757, metadata !460), !dbg !759
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !760
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 195932357, i32 32767, i8* getelementptr inbounds ([38 x i8], [38 x i8]* @.str.4, i32 0, i32 0)), !dbg !760
  store i32 %call, i32* %magic_test, align 4, !dbg !760
  %3 = load i32, i32* %magic_test, align 4, !dbg !760
  %cmp = icmp eq i32 %3, -30, !dbg !760
  br i1 %cmp, label %if.then, label %if.end, !dbg !760

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !762
  br label %return, !dbg !762

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !765

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !767
  call void @setup_symlink_mode(%struct.archive_read_disk* %4, i8 signext 76, i32 1), !dbg !768
  store i32 0, i32* %retval, align 4, !dbg !769
  br label %return, !dbg !769

return:                                           ; preds = %do.end, %if.then
  %5 = load i32, i32* %retval, align 4, !dbg !770
  ret i32 %5, !dbg !770
}

; Function Attrs: nounwind uwtable
define internal void @setup_symlink_mode(%struct.archive_read_disk* %a, i8 signext %symlink_mode, i32 %follow_symlinks) #0 !dbg !429 {
entry:
  %a.addr = alloca %struct.archive_read_disk*, align 8
  %symlink_mode.addr = alloca i8, align 1
  %follow_symlinks.addr = alloca i32, align 4
  store %struct.archive_read_disk* %a, %struct.archive_read_disk** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_disk** %a.addr, metadata !771, metadata !460), !dbg !772
  store i8 %symlink_mode, i8* %symlink_mode.addr, align 1
  call void @llvm.dbg.declare(metadata i8* %symlink_mode.addr, metadata !773, metadata !460), !dbg !774
  store i32 %follow_symlinks, i32* %follow_symlinks.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %follow_symlinks.addr, metadata !775, metadata !460), !dbg !776
  %0 = load i8, i8* %symlink_mode.addr, align 1, !dbg !777
  %1 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !778
  %symlink_mode1 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %1, i32 0, i32 2, !dbg !779
  store i8 %0, i8* %symlink_mode1, align 8, !dbg !780
  %2 = load i32, i32* %follow_symlinks.addr, align 4, !dbg !781
  %conv = trunc i32 %2 to i8, !dbg !781
  %3 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !782
  %follow_symlinks2 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %3, i32 0, i32 3, !dbg !783
  store i8 %conv, i8* %follow_symlinks2, align 1, !dbg !784
  %4 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !785
  %tree = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %4, i32 0, i32 4, !dbg !787
  %5 = load %struct.tree*, %struct.tree** %tree, align 8, !dbg !787
  %cmp = icmp ne %struct.tree* %5, null, !dbg !788
  br i1 %cmp, label %if.then, label %if.end, !dbg !789

if.then:                                          ; preds = %entry
  %6 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !790
  %symlink_mode4 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %6, i32 0, i32 2, !dbg !792
  %7 = load i8, i8* %symlink_mode4, align 8, !dbg !792
  %8 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !793
  %tree5 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %8, i32 0, i32 4, !dbg !794
  %9 = load %struct.tree*, %struct.tree** %tree5, align 8, !dbg !794
  %initial_symlink_mode = getelementptr inbounds %struct.tree, %struct.tree* %9, i32 0, i32 26, !dbg !795
  store i8 %7, i8* %initial_symlink_mode, align 8, !dbg !796
  %10 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !797
  %symlink_mode6 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %10, i32 0, i32 2, !dbg !798
  %11 = load i8, i8* %symlink_mode6, align 8, !dbg !798
  %12 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !799
  %tree7 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %12, i32 0, i32 4, !dbg !800
  %13 = load %struct.tree*, %struct.tree** %tree7, align 8, !dbg !800
  %symlink_mode8 = getelementptr inbounds %struct.tree, %struct.tree* %13, i32 0, i32 27, !dbg !801
  store i8 %11, i8* %symlink_mode8, align 1, !dbg !802
  br label %if.end, !dbg !803

if.end:                                           ; preds = %if.then, %entry
  ret void, !dbg !804
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_disk_set_symlink_physical(%struct.archive* %_a) #0 !dbg !347 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_read_disk*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !805, metadata !460), !dbg !806
  call void @llvm.dbg.declare(metadata %struct.archive_read_disk** %a, metadata !807, metadata !460), !dbg !808
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !809
  %1 = bitcast %struct.archive* %0 to %struct.archive_read_disk*, !dbg !810
  store %struct.archive_read_disk* %1, %struct.archive_read_disk** %a, align 8, !dbg !808
  br label %do.body, !dbg !811

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !812, metadata !460), !dbg !814
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !815
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 195932357, i32 32767, i8* getelementptr inbounds ([39 x i8], [39 x i8]* @.str.5, i32 0, i32 0)), !dbg !815
  store i32 %call, i32* %magic_test, align 4, !dbg !815
  %3 = load i32, i32* %magic_test, align 4, !dbg !815
  %cmp = icmp eq i32 %3, -30, !dbg !815
  br i1 %cmp, label %if.then, label %if.end, !dbg !815

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !817
  br label %return, !dbg !817

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !820

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !822
  call void @setup_symlink_mode(%struct.archive_read_disk* %4, i8 signext 80, i32 0), !dbg !823
  store i32 0, i32* %retval, align 4, !dbg !824
  br label %return, !dbg !824

return:                                           ; preds = %do.end, %if.then
  %5 = load i32, i32* %retval, align 4, !dbg !825
  ret i32 %5, !dbg !825
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_disk_set_symlink_hybrid(%struct.archive* %_a) #0 !dbg !348 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_read_disk*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !826, metadata !460), !dbg !827
  call void @llvm.dbg.declare(metadata %struct.archive_read_disk** %a, metadata !828, metadata !460), !dbg !829
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !830
  %1 = bitcast %struct.archive* %0 to %struct.archive_read_disk*, !dbg !831
  store %struct.archive_read_disk* %1, %struct.archive_read_disk** %a, align 8, !dbg !829
  br label %do.body, !dbg !832

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !833, metadata !460), !dbg !835
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !836
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 195932357, i32 32767, i8* getelementptr inbounds ([37 x i8], [37 x i8]* @.str.6, i32 0, i32 0)), !dbg !836
  store i32 %call, i32* %magic_test, align 4, !dbg !836
  %3 = load i32, i32* %magic_test, align 4, !dbg !836
  %cmp = icmp eq i32 %3, -30, !dbg !836
  br i1 %cmp, label %if.then, label %if.end, !dbg !836

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !838
  br label %return, !dbg !838

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !841

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !843
  call void @setup_symlink_mode(%struct.archive_read_disk* %4, i8 signext 72, i32 1), !dbg !844
  store i32 0, i32* %retval, align 4, !dbg !845
  br label %return, !dbg !845

return:                                           ; preds = %do.end, %if.then
  %5 = load i32, i32* %retval, align 4, !dbg !846
  ret i32 %5, !dbg !846
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_disk_set_atime_restored(%struct.archive* %_a) #0 !dbg !349 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_read_disk*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !847, metadata !460), !dbg !848
  call void @llvm.dbg.declare(metadata %struct.archive_read_disk** %a, metadata !849, metadata !460), !dbg !850
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !851
  %1 = bitcast %struct.archive* %0 to %struct.archive_read_disk*, !dbg !852
  store %struct.archive_read_disk* %1, %struct.archive_read_disk** %a, align 8, !dbg !850
  br label %do.body, !dbg !853

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !854, metadata !460), !dbg !856
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !857
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 195932357, i32 32767, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.7, i32 0, i32 0)), !dbg !857
  store i32 %call, i32* %magic_test, align 4, !dbg !857
  %3 = load i32, i32* %magic_test, align 4, !dbg !857
  %cmp = icmp eq i32 %3, -30, !dbg !857
  br i1 %cmp, label %if.then, label %if.end, !dbg !857

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !859
  br label %return, !dbg !859

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !862

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !864
  %flags = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %4, i32 0, i32 8, !dbg !865
  %5 = load i32, i32* %flags, align 8, !dbg !866
  %or = or i32 %5, 1, !dbg !866
  store i32 %or, i32* %flags, align 8, !dbg !866
  %6 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !867
  %tree = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %6, i32 0, i32 4, !dbg !869
  %7 = load %struct.tree*, %struct.tree** %tree, align 8, !dbg !869
  %cmp1 = icmp ne %struct.tree* %7, null, !dbg !870
  br i1 %cmp1, label %if.then2, label %if.end6, !dbg !871

if.then2:                                         ; preds = %do.end
  %8 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !872
  %tree3 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %8, i32 0, i32 4, !dbg !873
  %9 = load %struct.tree*, %struct.tree** %tree3, align 8, !dbg !873
  %flags4 = getelementptr inbounds %struct.tree, %struct.tree* %9, i32 0, i32 6, !dbg !874
  %10 = load i32, i32* %flags4, align 8, !dbg !875
  %or5 = or i32 %10, 128, !dbg !875
  store i32 %or5, i32* %flags4, align 8, !dbg !875
  br label %if.end6, !dbg !872

if.end6:                                          ; preds = %if.then2, %do.end
  store i32 0, i32* %retval, align 4, !dbg !876
  br label %return, !dbg !876

return:                                           ; preds = %if.end6, %if.then
  %11 = load i32, i32* %retval, align 4, !dbg !877
  ret i32 %11, !dbg !877
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_disk_set_behavior(%struct.archive* %_a, i32 %flags) #0 !dbg !350 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %flags.addr = alloca i32, align 4
  %a = alloca %struct.archive_read_disk*, align 8
  %r = alloca i32, align 4
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !878, metadata !460), !dbg !879
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !880, metadata !460), !dbg !881
  call void @llvm.dbg.declare(metadata %struct.archive_read_disk** %a, metadata !882, metadata !460), !dbg !883
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !884
  %1 = bitcast %struct.archive* %0 to %struct.archive_read_disk*, !dbg !885
  store %struct.archive_read_disk* %1, %struct.archive_read_disk** %a, align 8, !dbg !883
  call void @llvm.dbg.declare(metadata i32* %r, metadata !886, metadata !460), !dbg !887
  store i32 0, i32* %r, align 4, !dbg !887
  br label %do.body, !dbg !888

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !889, metadata !460), !dbg !891
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !892
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 195932357, i32 32767, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.8, i32 0, i32 0)), !dbg !892
  store i32 %call, i32* %magic_test, align 4, !dbg !892
  %3 = load i32, i32* %magic_test, align 4, !dbg !892
  %cmp = icmp eq i32 %3, -30, !dbg !892
  br i1 %cmp, label %if.then, label %if.end, !dbg !892

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !894
  br label %return, !dbg !894

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !897

do.end:                                           ; preds = %if.end
  %4 = load i32, i32* %flags.addr, align 4, !dbg !899
  %5 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !900
  %flags1 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %5, i32 0, i32 8, !dbg !901
  store i32 %4, i32* %flags1, align 8, !dbg !902
  %6 = load i32, i32* %flags.addr, align 4, !dbg !903
  %and = and i32 %6, 1, !dbg !905
  %tobool = icmp ne i32 %and, 0, !dbg !905
  br i1 %tobool, label %if.then2, label %if.else, !dbg !906

if.then2:                                         ; preds = %do.end
  %7 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !907
  %call3 = call i32 @archive_read_disk_set_atime_restored(%struct.archive* %7), !dbg !908
  store i32 %call3, i32* %r, align 4, !dbg !909
  br label %if.end10, !dbg !910

if.else:                                          ; preds = %do.end
  %8 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !911
  %tree = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %8, i32 0, i32 4, !dbg !914
  %9 = load %struct.tree*, %struct.tree** %tree, align 8, !dbg !914
  %cmp4 = icmp ne %struct.tree* %9, null, !dbg !915
  br i1 %cmp4, label %if.then5, label %if.end9, !dbg !916

if.then5:                                         ; preds = %if.else
  %10 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !917
  %tree6 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %10, i32 0, i32 4, !dbg !918
  %11 = load %struct.tree*, %struct.tree** %tree6, align 8, !dbg !918
  %flags7 = getelementptr inbounds %struct.tree, %struct.tree* %11, i32 0, i32 6, !dbg !919
  %12 = load i32, i32* %flags7, align 8, !dbg !920
  %and8 = and i32 %12, -129, !dbg !920
  store i32 %and8, i32* %flags7, align 8, !dbg !920
  br label %if.end9, !dbg !917

if.end9:                                          ; preds = %if.then5, %if.else
  br label %if.end10

if.end10:                                         ; preds = %if.end9, %if.then2
  %13 = load i32, i32* %r, align 4, !dbg !921
  store i32 %13, i32* %retval, align 4, !dbg !922
  br label %return, !dbg !922

return:                                           ; preds = %if.end10, %if.then
  %14 = load i32, i32* %retval, align 4, !dbg !923
  ret i32 %14, !dbg !923
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_disk_set_matching(%struct.archive* %_a, %struct.archive* %_ma, void (%struct.archive*, i8*, %struct.archive_entry*)* %_excluded_func, i8* %_client_data) #0 !dbg !351 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %_ma.addr = alloca %struct.archive*, align 8
  %_excluded_func.addr = alloca void (%struct.archive*, i8*, %struct.archive_entry*)*, align 8
  %_client_data.addr = alloca i8*, align 8
  %a = alloca %struct.archive_read_disk*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !924, metadata !460), !dbg !925
  store %struct.archive* %_ma, %struct.archive** %_ma.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_ma.addr, metadata !926, metadata !460), !dbg !927
  store void (%struct.archive*, i8*, %struct.archive_entry*)* %_excluded_func, void (%struct.archive*, i8*, %struct.archive_entry*)** %_excluded_func.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.archive*, i8*, %struct.archive_entry*)** %_excluded_func.addr, metadata !928, metadata !460), !dbg !929
  store i8* %_client_data, i8** %_client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %_client_data.addr, metadata !930, metadata !460), !dbg !931
  call void @llvm.dbg.declare(metadata %struct.archive_read_disk** %a, metadata !932, metadata !460), !dbg !933
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !934
  %1 = bitcast %struct.archive* %0 to %struct.archive_read_disk*, !dbg !935
  store %struct.archive_read_disk* %1, %struct.archive_read_disk** %a, align 8, !dbg !933
  br label %do.body, !dbg !936

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !937, metadata !460), !dbg !939
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !940
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 195932357, i32 32767, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.9, i32 0, i32 0)), !dbg !940
  store i32 %call, i32* %magic_test, align 4, !dbg !940
  %3 = load i32, i32* %magic_test, align 4, !dbg !940
  %cmp = icmp eq i32 %3, -30, !dbg !940
  br i1 %cmp, label %if.then, label %if.end, !dbg !940

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !942
  br label %return, !dbg !942

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !945

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive*, %struct.archive** %_ma.addr, align 8, !dbg !947
  %5 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !948
  %matching = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %5, i32 0, i32 17, !dbg !949
  store %struct.archive* %4, %struct.archive** %matching, align 8, !dbg !950
  %6 = load void (%struct.archive*, i8*, %struct.archive_entry*)*, void (%struct.archive*, i8*, %struct.archive_entry*)** %_excluded_func.addr, align 8, !dbg !951
  %7 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !952
  %excluded_cb_func = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %7, i32 0, i32 18, !dbg !953
  store void (%struct.archive*, i8*, %struct.archive_entry*)* %6, void (%struct.archive*, i8*, %struct.archive_entry*)** %excluded_cb_func, align 8, !dbg !954
  %8 = load i8*, i8** %_client_data.addr, align 8, !dbg !955
  %9 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !956
  %excluded_cb_data = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %9, i32 0, i32 19, !dbg !957
  store i8* %8, i8** %excluded_cb_data, align 8, !dbg !958
  store i32 0, i32* %retval, align 4, !dbg !959
  br label %return, !dbg !959

return:                                           ; preds = %do.end, %if.then
  %10 = load i32, i32* %retval, align 4, !dbg !960
  ret i32 %10, !dbg !960
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_disk_set_metadata_filter_callback(%struct.archive* %_a, i32 (%struct.archive*, i8*, %struct.archive_entry*)* %_metadata_filter_func, i8* %_client_data) #0 !dbg !354 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %_metadata_filter_func.addr = alloca i32 (%struct.archive*, i8*, %struct.archive_entry*)*, align 8
  %_client_data.addr = alloca i8*, align 8
  %a = alloca %struct.archive_read_disk*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !961, metadata !460), !dbg !962
  store i32 (%struct.archive*, i8*, %struct.archive_entry*)* %_metadata_filter_func, i32 (%struct.archive*, i8*, %struct.archive_entry*)** %_metadata_filter_func.addr, align 8
  call void @llvm.dbg.declare(metadata i32 (%struct.archive*, i8*, %struct.archive_entry*)** %_metadata_filter_func.addr, metadata !963, metadata !460), !dbg !964
  store i8* %_client_data, i8** %_client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %_client_data.addr, metadata !965, metadata !460), !dbg !966
  call void @llvm.dbg.declare(metadata %struct.archive_read_disk** %a, metadata !967, metadata !460), !dbg !968
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !969
  %1 = bitcast %struct.archive* %0 to %struct.archive_read_disk*, !dbg !970
  store %struct.archive_read_disk* %1, %struct.archive_read_disk** %a, align 8, !dbg !968
  br label %do.body, !dbg !971

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !972, metadata !460), !dbg !974
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !975
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 195932357, i32 32767, i8* getelementptr inbounds ([47 x i8], [47 x i8]* @.str.10, i32 0, i32 0)), !dbg !975
  store i32 %call, i32* %magic_test, align 4, !dbg !975
  %3 = load i32, i32* %magic_test, align 4, !dbg !975
  %cmp = icmp eq i32 %3, -30, !dbg !975
  br i1 %cmp, label %if.then, label %if.end, !dbg !975

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !977
  br label %return, !dbg !977

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !980

do.end:                                           ; preds = %if.end
  %4 = load i32 (%struct.archive*, i8*, %struct.archive_entry*)*, i32 (%struct.archive*, i8*, %struct.archive_entry*)** %_metadata_filter_func.addr, align 8, !dbg !982
  %5 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !983
  %metadata_filter_func = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %5, i32 0, i32 15, !dbg !984
  store i32 (%struct.archive*, i8*, %struct.archive_entry*)* %4, i32 (%struct.archive*, i8*, %struct.archive_entry*)** %metadata_filter_func, align 8, !dbg !985
  %6 = load i8*, i8** %_client_data.addr, align 8, !dbg !986
  %7 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !987
  %metadata_filter_data = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %7, i32 0, i32 16, !dbg !988
  store i8* %6, i8** %metadata_filter_data, align 8, !dbg !989
  store i32 0, i32* %retval, align 4, !dbg !990
  br label %return, !dbg !990

return:                                           ; preds = %do.end, %if.then
  %8 = load i32, i32* %retval, align 4, !dbg !991
  ret i32 %8, !dbg !991
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_disk_can_descend(%struct.archive* %_a) #0 !dbg !357 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_read_disk*, align 8
  %t = alloca %struct.tree*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !992, metadata !460), !dbg !993
  call void @llvm.dbg.declare(metadata %struct.archive_read_disk** %a, metadata !994, metadata !460), !dbg !995
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !996
  %1 = bitcast %struct.archive* %0 to %struct.archive_read_disk*, !dbg !997
  store %struct.archive_read_disk* %1, %struct.archive_read_disk** %a, align 8, !dbg !995
  call void @llvm.dbg.declare(metadata %struct.tree** %t, metadata !998, metadata !460), !dbg !999
  %2 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1000
  %tree = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %2, i32 0, i32 4, !dbg !1001
  %3 = load %struct.tree*, %struct.tree** %tree, align 8, !dbg !1001
  store %struct.tree* %3, %struct.tree** %t, align 8, !dbg !999
  br label %do.body, !dbg !1002

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !1003, metadata !460), !dbg !1005
  %4 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1006
  %call = call i32 @__archive_check_magic(%struct.archive* %4, i32 195932357, i32 6, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.11, i32 0, i32 0)), !dbg !1006
  store i32 %call, i32* %magic_test, align 4, !dbg !1006
  %5 = load i32, i32* %magic_test, align 4, !dbg !1006
  %cmp = icmp eq i32 %5, -30, !dbg !1006
  br i1 %cmp, label %if.then, label %if.end, !dbg !1006

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !1008
  br label %return, !dbg !1008

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !1011

do.end:                                           ; preds = %if.end
  %6 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1013
  %visit_type = getelementptr inbounds %struct.tree, %struct.tree* %6, i32 0, i32 7, !dbg !1014
  %7 = load i32, i32* %visit_type, align 4, !dbg !1014
  %cmp1 = icmp eq i32 %7, 1, !dbg !1015
  br i1 %cmp1, label %land.rhs, label %land.end, !dbg !1016

land.rhs:                                         ; preds = %do.end
  %8 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1017
  %descend = getelementptr inbounds %struct.tree, %struct.tree* %8, i32 0, i32 19, !dbg !1019
  %9 = load i32, i32* %descend, align 8, !dbg !1019
  %tobool = icmp ne i32 %9, 0, !dbg !1020
  br label %land.end

land.end:                                         ; preds = %land.rhs, %do.end
  %10 = phi i1 [ false, %do.end ], [ %tobool, %land.rhs ]
  %land.ext = zext i1 %10 to i32, !dbg !1021
  store i32 %land.ext, i32* %retval, align 4, !dbg !1023
  br label %return, !dbg !1023

return:                                           ; preds = %land.end, %if.then
  %11 = load i32, i32* %retval, align 4, !dbg !1024
  ret i32 %11, !dbg !1024
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_disk_descend(%struct.archive* %_a) #0 !dbg !358 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_read_disk*, align 8
  %t = alloca %struct.tree*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !1025, metadata !460), !dbg !1026
  call void @llvm.dbg.declare(metadata %struct.archive_read_disk** %a, metadata !1027, metadata !460), !dbg !1028
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1029
  %1 = bitcast %struct.archive* %0 to %struct.archive_read_disk*, !dbg !1030
  store %struct.archive_read_disk* %1, %struct.archive_read_disk** %a, align 8, !dbg !1028
  call void @llvm.dbg.declare(metadata %struct.tree** %t, metadata !1031, metadata !460), !dbg !1032
  %2 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1033
  %tree = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %2, i32 0, i32 4, !dbg !1034
  %3 = load %struct.tree*, %struct.tree** %tree, align 8, !dbg !1034
  store %struct.tree* %3, %struct.tree** %t, align 8, !dbg !1032
  br label %do.body, !dbg !1035

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !1036, metadata !460), !dbg !1038
  %4 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1039
  %call = call i32 @__archive_check_magic(%struct.archive* %4, i32 195932357, i32 6, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.12, i32 0, i32 0)), !dbg !1039
  store i32 %call, i32* %magic_test, align 4, !dbg !1039
  %5 = load i32, i32* %magic_test, align 4, !dbg !1039
  %cmp = icmp eq i32 %5, -30, !dbg !1039
  br i1 %cmp, label %if.then, label %if.end, !dbg !1039

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !1041
  br label %return, !dbg !1041

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !1044

do.end:                                           ; preds = %if.end
  %6 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1046
  %visit_type = getelementptr inbounds %struct.tree, %struct.tree* %6, i32 0, i32 7, !dbg !1048
  %7 = load i32, i32* %visit_type, align 4, !dbg !1048
  %cmp1 = icmp ne i32 %7, 1, !dbg !1049
  br i1 %cmp1, label %if.then2, label %lor.lhs.false, !dbg !1050

lor.lhs.false:                                    ; preds = %do.end
  %8 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1051
  %descend = getelementptr inbounds %struct.tree, %struct.tree* %8, i32 0, i32 19, !dbg !1053
  %9 = load i32, i32* %descend, align 8, !dbg !1053
  %tobool = icmp ne i32 %9, 0, !dbg !1051
  br i1 %tobool, label %if.end3, label %if.then2, !dbg !1054

if.then2:                                         ; preds = %lor.lhs.false, %do.end
  store i32 0, i32* %retval, align 4, !dbg !1055
  br label %return, !dbg !1055

if.end3:                                          ; preds = %lor.lhs.false
  %10 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1056
  %call4 = call i32 @tree_current_is_physical_dir(%struct.tree* %10), !dbg !1058
  %tobool5 = icmp ne i32 %call4, 0, !dbg !1058
  br i1 %tobool5, label %if.then6, label %if.else, !dbg !1059

if.then6:                                         ; preds = %if.end3
  %11 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1060
  %12 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1062
  %basename = getelementptr inbounds %struct.tree, %struct.tree* %12, i32 0, i32 10, !dbg !1063
  %13 = load i8*, i8** %basename, align 8, !dbg !1063
  %14 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1064
  %current_filesystem_id = getelementptr inbounds %struct.tree, %struct.tree* %14, i32 0, i32 31, !dbg !1065
  %15 = load i32, i32* %current_filesystem_id, align 4, !dbg !1065
  %16 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1066
  %lst = getelementptr inbounds %struct.tree, %struct.tree* %16, i32 0, i32 17, !dbg !1067
  %st_dev = getelementptr inbounds %struct.stat, %struct.stat* %lst, i32 0, i32 0, !dbg !1068
  %17 = load i64, i64* %st_dev, align 8, !dbg !1068
  %18 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1069
  %lst7 = getelementptr inbounds %struct.tree, %struct.tree* %18, i32 0, i32 17, !dbg !1070
  %st_ino = getelementptr inbounds %struct.stat, %struct.stat* %lst7, i32 0, i32 1, !dbg !1071
  %19 = load i64, i64* %st_ino, align 8, !dbg !1071
  %20 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1072
  %restore_time = getelementptr inbounds %struct.tree, %struct.tree* %20, i32 0, i32 21, !dbg !1073
  call void @tree_push(%struct.tree* %11, i8* %13, i32 %15, i64 %17, i64 %19, %struct.restore_time* %restore_time), !dbg !1074
  %21 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1075
  %stack = getelementptr inbounds %struct.tree, %struct.tree* %21, i32 0, i32 0, !dbg !1076
  %22 = load %struct.tree_entry*, %struct.tree_entry** %stack, align 8, !dbg !1076
  %flags = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %22, i32 0, i32 7, !dbg !1077
  %23 = load i32, i32* %flags, align 8, !dbg !1078
  %or = or i32 %23, 1, !dbg !1078
  store i32 %or, i32* %flags, align 8, !dbg !1078
  br label %if.end21, !dbg !1079

if.else:                                          ; preds = %if.end3
  %24 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1080
  %call8 = call i32 @tree_current_is_dir(%struct.tree* %24), !dbg !1083
  %tobool9 = icmp ne i32 %call8, 0, !dbg !1083
  br i1 %tobool9, label %if.then10, label %if.end20, !dbg !1083

if.then10:                                        ; preds = %if.else
  %25 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1084
  %26 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1086
  %basename11 = getelementptr inbounds %struct.tree, %struct.tree* %26, i32 0, i32 10, !dbg !1087
  %27 = load i8*, i8** %basename11, align 8, !dbg !1087
  %28 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1088
  %current_filesystem_id12 = getelementptr inbounds %struct.tree, %struct.tree* %28, i32 0, i32 31, !dbg !1089
  %29 = load i32, i32* %current_filesystem_id12, align 4, !dbg !1089
  %30 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1090
  %st = getelementptr inbounds %struct.tree, %struct.tree* %30, i32 0, i32 18, !dbg !1091
  %st_dev13 = getelementptr inbounds %struct.stat, %struct.stat* %st, i32 0, i32 0, !dbg !1092
  %31 = load i64, i64* %st_dev13, align 8, !dbg !1092
  %32 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1093
  %st14 = getelementptr inbounds %struct.tree, %struct.tree* %32, i32 0, i32 18, !dbg !1094
  %st_ino15 = getelementptr inbounds %struct.stat, %struct.stat* %st14, i32 0, i32 1, !dbg !1095
  %33 = load i64, i64* %st_ino15, align 8, !dbg !1095
  %34 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1096
  %restore_time16 = getelementptr inbounds %struct.tree, %struct.tree* %34, i32 0, i32 21, !dbg !1097
  call void @tree_push(%struct.tree* %25, i8* %27, i32 %29, i64 %31, i64 %33, %struct.restore_time* %restore_time16), !dbg !1098
  %35 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1099
  %stack17 = getelementptr inbounds %struct.tree, %struct.tree* %35, i32 0, i32 0, !dbg !1100
  %36 = load %struct.tree_entry*, %struct.tree_entry** %stack17, align 8, !dbg !1100
  %flags18 = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %36, i32 0, i32 7, !dbg !1101
  %37 = load i32, i32* %flags18, align 8, !dbg !1102
  %or19 = or i32 %37, 2, !dbg !1102
  store i32 %or19, i32* %flags18, align 8, !dbg !1102
  br label %if.end20, !dbg !1103

if.end20:                                         ; preds = %if.then10, %if.else
  br label %if.end21

if.end21:                                         ; preds = %if.end20, %if.then6
  %38 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1104
  %descend22 = getelementptr inbounds %struct.tree, %struct.tree* %38, i32 0, i32 19, !dbg !1105
  store i32 0, i32* %descend22, align 8, !dbg !1106
  store i32 0, i32* %retval, align 4, !dbg !1107
  br label %return, !dbg !1107

return:                                           ; preds = %if.end21, %if.then2, %if.then
  %39 = load i32, i32* %retval, align 4, !dbg !1108
  ret i32 %39, !dbg !1108
}

; Function Attrs: nounwind uwtable
define internal i32 @tree_current_is_physical_dir(%struct.tree* %t) #0 !dbg !448 {
entry:
  %retval = alloca i32, align 4
  %t.addr = alloca %struct.tree*, align 8
  %st = alloca %struct.stat*, align 8
  store %struct.tree* %t, %struct.tree** %t.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tree** %t.addr, metadata !1109, metadata !460), !dbg !1110
  call void @llvm.dbg.declare(metadata %struct.stat** %st, metadata !1111, metadata !460), !dbg !1112
  %0 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !1113
  %flags = getelementptr inbounds %struct.tree, %struct.tree* %0, i32 0, i32 6, !dbg !1115
  %1 = load i32, i32* %flags, align 8, !dbg !1115
  %and = and i32 %1, 16, !dbg !1116
  %tobool = icmp ne i32 %and, 0, !dbg !1116
  br i1 %tobool, label %if.then, label %if.end6, !dbg !1117

if.then:                                          ; preds = %entry
  %2 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !1118
  %call = call %struct.stat* @tree_current_stat(%struct.tree* %2), !dbg !1120
  store %struct.stat* %call, %struct.stat** %st, align 8, !dbg !1121
  %3 = load %struct.stat*, %struct.stat** %st, align 8, !dbg !1122
  %cmp = icmp eq %struct.stat* %3, null, !dbg !1124
  br i1 %cmp, label %if.then1, label %if.end, !dbg !1125

if.then1:                                         ; preds = %if.then
  store i32 0, i32* %retval, align 4, !dbg !1126
  br label %return, !dbg !1126

if.end:                                           ; preds = %if.then
  %4 = load %struct.stat*, %struct.stat** %st, align 8, !dbg !1127
  %st_mode = getelementptr inbounds %struct.stat, %struct.stat* %4, i32 0, i32 3, !dbg !1127
  %5 = load i32, i32* %st_mode, align 8, !dbg !1127
  %and2 = and i32 %5, 61440, !dbg !1127
  %cmp3 = icmp eq i32 %and2, 16384, !dbg !1127
  br i1 %cmp3, label %if.end5, label %if.then4, !dbg !1129

if.then4:                                         ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !1130
  br label %return, !dbg !1130

if.end5:                                          ; preds = %if.end
  br label %if.end6, !dbg !1131

if.end6:                                          ; preds = %if.end5, %entry
  %6 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !1132
  %call7 = call %struct.stat* @tree_current_lstat(%struct.tree* %6), !dbg !1133
  store %struct.stat* %call7, %struct.stat** %st, align 8, !dbg !1134
  %7 = load %struct.stat*, %struct.stat** %st, align 8, !dbg !1135
  %cmp8 = icmp eq %struct.stat* %7, null, !dbg !1137
  br i1 %cmp8, label %if.then9, label %if.end10, !dbg !1138

if.then9:                                         ; preds = %if.end6
  store i32 0, i32* %retval, align 4, !dbg !1139
  br label %return, !dbg !1139

if.end10:                                         ; preds = %if.end6
  %8 = load %struct.stat*, %struct.stat** %st, align 8, !dbg !1140
  %st_mode11 = getelementptr inbounds %struct.stat, %struct.stat* %8, i32 0, i32 3, !dbg !1140
  %9 = load i32, i32* %st_mode11, align 8, !dbg !1140
  %and12 = and i32 %9, 61440, !dbg !1140
  %cmp13 = icmp eq i32 %and12, 16384, !dbg !1140
  %conv = zext i1 %cmp13 to i32, !dbg !1140
  store i32 %conv, i32* %retval, align 4, !dbg !1141
  br label %return, !dbg !1141

return:                                           ; preds = %if.end10, %if.then9, %if.then4, %if.then1
  %10 = load i32, i32* %retval, align 4, !dbg !1142
  ret i32 %10, !dbg !1142
}

; Function Attrs: nounwind uwtable
define internal void @tree_push(%struct.tree* %t, i8* %path, i32 %filesystem_id, i64 %dev, i64 %ino, %struct.restore_time* %rt) #0 !dbg !442 {
entry:
  %t.addr = alloca %struct.tree*, align 8
  %path.addr = alloca i8*, align 8
  %filesystem_id.addr = alloca i32, align 4
  %dev.addr = alloca i64, align 8
  %ino.addr = alloca i64, align 8
  %rt.addr = alloca %struct.restore_time*, align 8
  %te = alloca %struct.tree_entry*, align 8
  store %struct.tree* %t, %struct.tree** %t.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tree** %t.addr, metadata !1143, metadata !460), !dbg !1144
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !1145, metadata !460), !dbg !1146
  store i32 %filesystem_id, i32* %filesystem_id.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %filesystem_id.addr, metadata !1147, metadata !460), !dbg !1148
  store i64 %dev, i64* %dev.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %dev.addr, metadata !1149, metadata !460), !dbg !1150
  store i64 %ino, i64* %ino.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %ino.addr, metadata !1151, metadata !460), !dbg !1152
  store %struct.restore_time* %rt, %struct.restore_time** %rt.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.restore_time** %rt.addr, metadata !1153, metadata !460), !dbg !1154
  call void @llvm.dbg.declare(metadata %struct.tree_entry** %te, metadata !1155, metadata !460), !dbg !1156
  %call = call noalias i8* @calloc(i64 1, i64 136) #6, !dbg !1157
  %0 = bitcast i8* %call to %struct.tree_entry*, !dbg !1157
  store %struct.tree_entry* %0, %struct.tree_entry** %te, align 8, !dbg !1158
  %1 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !1159
  %stack = getelementptr inbounds %struct.tree, %struct.tree* %1, i32 0, i32 0, !dbg !1160
  %2 = load %struct.tree_entry*, %struct.tree_entry** %stack, align 8, !dbg !1160
  %3 = load %struct.tree_entry*, %struct.tree_entry** %te, align 8, !dbg !1161
  %next = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %3, i32 0, i32 1, !dbg !1162
  store %struct.tree_entry* %2, %struct.tree_entry** %next, align 8, !dbg !1163
  %4 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !1164
  %current = getelementptr inbounds %struct.tree, %struct.tree* %4, i32 0, i32 1, !dbg !1165
  %5 = load %struct.tree_entry*, %struct.tree_entry** %current, align 8, !dbg !1165
  %6 = load %struct.tree_entry*, %struct.tree_entry** %te, align 8, !dbg !1166
  %parent = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %6, i32 0, i32 2, !dbg !1167
  store %struct.tree_entry* %5, %struct.tree_entry** %parent, align 8, !dbg !1168
  %7 = load %struct.tree_entry*, %struct.tree_entry** %te, align 8, !dbg !1169
  %parent1 = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %7, i32 0, i32 2, !dbg !1171
  %8 = load %struct.tree_entry*, %struct.tree_entry** %parent1, align 8, !dbg !1171
  %tobool = icmp ne %struct.tree_entry* %8, null, !dbg !1169
  br i1 %tobool, label %if.then, label %if.end, !dbg !1172

if.then:                                          ; preds = %entry
  %9 = load %struct.tree_entry*, %struct.tree_entry** %te, align 8, !dbg !1173
  %parent2 = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %9, i32 0, i32 2, !dbg !1174
  %10 = load %struct.tree_entry*, %struct.tree_entry** %parent2, align 8, !dbg !1174
  %depth = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %10, i32 0, i32 0, !dbg !1175
  %11 = load i32, i32* %depth, align 8, !dbg !1175
  %add = add nsw i32 %11, 1, !dbg !1176
  %12 = load %struct.tree_entry*, %struct.tree_entry** %te, align 8, !dbg !1177
  %depth3 = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %12, i32 0, i32 0, !dbg !1178
  store i32 %add, i32* %depth3, align 8, !dbg !1179
  br label %if.end, !dbg !1177

if.end:                                           ; preds = %if.then, %entry
  %13 = load %struct.tree_entry*, %struct.tree_entry** %te, align 8, !dbg !1180
  %14 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !1181
  %stack4 = getelementptr inbounds %struct.tree, %struct.tree* %14, i32 0, i32 0, !dbg !1182
  store %struct.tree_entry* %13, %struct.tree_entry** %stack4, align 8, !dbg !1183
  br label %do.body, !dbg !1184

do.body:                                          ; preds = %if.end
  %15 = load %struct.tree_entry*, %struct.tree_entry** %te, align 8, !dbg !1185
  %name = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %15, i32 0, i32 3, !dbg !1185
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %name, i32 0, i32 0, !dbg !1185
  store i8* null, i8** %s, align 8, !dbg !1185
  %16 = load %struct.tree_entry*, %struct.tree_entry** %te, align 8, !dbg !1185
  %name5 = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %16, i32 0, i32 3, !dbg !1185
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %name5, i32 0, i32 1, !dbg !1185
  store i64 0, i64* %length, align 8, !dbg !1185
  %17 = load %struct.tree_entry*, %struct.tree_entry** %te, align 8, !dbg !1185
  %name6 = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %17, i32 0, i32 3, !dbg !1185
  %buffer_length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %name6, i32 0, i32 2, !dbg !1185
  store i64 0, i64* %buffer_length, align 8, !dbg !1185
  br label %do.end, !dbg !1185

do.end:                                           ; preds = %do.body
  %18 = load %struct.tree_entry*, %struct.tree_entry** %te, align 8, !dbg !1188
  %symlink_parent_fd = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %18, i32 0, i32 9, !dbg !1189
  store i32 -1, i32* %symlink_parent_fd, align 8, !dbg !1190
  %19 = load %struct.tree_entry*, %struct.tree_entry** %te, align 8, !dbg !1191
  %name7 = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %19, i32 0, i32 3, !dbg !1191
  %length8 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %name7, i32 0, i32 1, !dbg !1191
  store i64 0, i64* %length8, align 8, !dbg !1191
  %20 = load %struct.tree_entry*, %struct.tree_entry** %te, align 8, !dbg !1191
  %name9 = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %20, i32 0, i32 3, !dbg !1191
  %21 = load i8*, i8** %path.addr, align 8, !dbg !1191
  %22 = load i8*, i8** %path.addr, align 8, !dbg !1191
  %cmp = icmp eq i8* %22, null, !dbg !1191
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !1191

cond.true:                                        ; preds = %do.end
  br label %cond.end, !dbg !1192

cond.false:                                       ; preds = %do.end
  %23 = load i8*, i8** %path.addr, align 8, !dbg !1194
  %call10 = call i64 @strlen(i8* %23) #7, !dbg !1194
  br label %cond.end, !dbg !1194

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ 0, %cond.true ], [ %call10, %cond.false ], !dbg !1196
  %call11 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %name9, i8* %21, i64 %cond), !dbg !1196
  %24 = load %struct.tree_entry*, %struct.tree_entry** %te, align 8, !dbg !1198
  %flags = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %24, i32 0, i32 7, !dbg !1199
  store i32 56, i32* %flags, align 8, !dbg !1200
  %25 = load i32, i32* %filesystem_id.addr, align 4, !dbg !1201
  %26 = load %struct.tree_entry*, %struct.tree_entry** %te, align 8, !dbg !1202
  %filesystem_id12 = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %26, i32 0, i32 8, !dbg !1203
  store i32 %25, i32* %filesystem_id12, align 4, !dbg !1204
  %27 = load i64, i64* %dev.addr, align 8, !dbg !1205
  %28 = load %struct.tree_entry*, %struct.tree_entry** %te, align 8, !dbg !1206
  %dev13 = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %28, i32 0, i32 5, !dbg !1207
  store i64 %27, i64* %dev13, align 8, !dbg !1208
  %29 = load i64, i64* %ino.addr, align 8, !dbg !1209
  %30 = load %struct.tree_entry*, %struct.tree_entry** %te, align 8, !dbg !1210
  %ino14 = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %30, i32 0, i32 6, !dbg !1211
  store i64 %29, i64* %ino14, align 8, !dbg !1212
  %31 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !1213
  %dirname_length = getelementptr inbounds %struct.tree, %struct.tree* %31, i32 0, i32 11, !dbg !1214
  %32 = load i64, i64* %dirname_length, align 8, !dbg !1214
  %33 = load %struct.tree_entry*, %struct.tree_entry** %te, align 8, !dbg !1215
  %dirname_length15 = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %33, i32 0, i32 4, !dbg !1216
  store i64 %32, i64* %dirname_length15, align 8, !dbg !1217
  %34 = load %struct.tree_entry*, %struct.tree_entry** %te, align 8, !dbg !1218
  %name16 = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %34, i32 0, i32 3, !dbg !1219
  %s17 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %name16, i32 0, i32 0, !dbg !1220
  %35 = load i8*, i8** %s17, align 8, !dbg !1220
  %36 = load %struct.tree_entry*, %struct.tree_entry** %te, align 8, !dbg !1221
  %restore_time = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %36, i32 0, i32 10, !dbg !1222
  %name18 = getelementptr inbounds %struct.restore_time, %struct.restore_time* %restore_time, i32 0, i32 0, !dbg !1223
  store i8* %35, i8** %name18, align 8, !dbg !1224
  %37 = load %struct.restore_time*, %struct.restore_time** %rt.addr, align 8, !dbg !1225
  %cmp19 = icmp ne %struct.restore_time* %37, null, !dbg !1227
  br i1 %cmp19, label %if.then20, label %if.end33, !dbg !1228

if.then20:                                        ; preds = %cond.end
  %38 = load %struct.restore_time*, %struct.restore_time** %rt.addr, align 8, !dbg !1229
  %mtime = getelementptr inbounds %struct.restore_time, %struct.restore_time* %38, i32 0, i32 1, !dbg !1231
  %39 = load i64, i64* %mtime, align 8, !dbg !1231
  %40 = load %struct.tree_entry*, %struct.tree_entry** %te, align 8, !dbg !1232
  %restore_time21 = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %40, i32 0, i32 10, !dbg !1233
  %mtime22 = getelementptr inbounds %struct.restore_time, %struct.restore_time* %restore_time21, i32 0, i32 1, !dbg !1234
  store i64 %39, i64* %mtime22, align 8, !dbg !1235
  %41 = load %struct.restore_time*, %struct.restore_time** %rt.addr, align 8, !dbg !1236
  %mtime_nsec = getelementptr inbounds %struct.restore_time, %struct.restore_time* %41, i32 0, i32 2, !dbg !1237
  %42 = load i64, i64* %mtime_nsec, align 8, !dbg !1237
  %43 = load %struct.tree_entry*, %struct.tree_entry** %te, align 8, !dbg !1238
  %restore_time23 = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %43, i32 0, i32 10, !dbg !1239
  %mtime_nsec24 = getelementptr inbounds %struct.restore_time, %struct.restore_time* %restore_time23, i32 0, i32 2, !dbg !1240
  store i64 %42, i64* %mtime_nsec24, align 8, !dbg !1241
  %44 = load %struct.restore_time*, %struct.restore_time** %rt.addr, align 8, !dbg !1242
  %atime = getelementptr inbounds %struct.restore_time, %struct.restore_time* %44, i32 0, i32 3, !dbg !1243
  %45 = load i64, i64* %atime, align 8, !dbg !1243
  %46 = load %struct.tree_entry*, %struct.tree_entry** %te, align 8, !dbg !1244
  %restore_time25 = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %46, i32 0, i32 10, !dbg !1245
  %atime26 = getelementptr inbounds %struct.restore_time, %struct.restore_time* %restore_time25, i32 0, i32 3, !dbg !1246
  store i64 %45, i64* %atime26, align 8, !dbg !1247
  %47 = load %struct.restore_time*, %struct.restore_time** %rt.addr, align 8, !dbg !1248
  %atime_nsec = getelementptr inbounds %struct.restore_time, %struct.restore_time* %47, i32 0, i32 4, !dbg !1249
  %48 = load i64, i64* %atime_nsec, align 8, !dbg !1249
  %49 = load %struct.tree_entry*, %struct.tree_entry** %te, align 8, !dbg !1250
  %restore_time27 = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %49, i32 0, i32 10, !dbg !1251
  %atime_nsec28 = getelementptr inbounds %struct.restore_time, %struct.restore_time* %restore_time27, i32 0, i32 4, !dbg !1252
  store i64 %48, i64* %atime_nsec28, align 8, !dbg !1253
  %50 = load %struct.restore_time*, %struct.restore_time** %rt.addr, align 8, !dbg !1254
  %filetype = getelementptr inbounds %struct.restore_time, %struct.restore_time* %50, i32 0, i32 5, !dbg !1255
  %51 = load i32, i32* %filetype, align 8, !dbg !1255
  %52 = load %struct.tree_entry*, %struct.tree_entry** %te, align 8, !dbg !1256
  %restore_time29 = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %52, i32 0, i32 10, !dbg !1257
  %filetype30 = getelementptr inbounds %struct.restore_time, %struct.restore_time* %restore_time29, i32 0, i32 5, !dbg !1258
  store i32 %51, i32* %filetype30, align 8, !dbg !1259
  %53 = load %struct.restore_time*, %struct.restore_time** %rt.addr, align 8, !dbg !1260
  %noatime = getelementptr inbounds %struct.restore_time, %struct.restore_time* %53, i32 0, i32 6, !dbg !1261
  %54 = load i32, i32* %noatime, align 4, !dbg !1261
  %55 = load %struct.tree_entry*, %struct.tree_entry** %te, align 8, !dbg !1262
  %restore_time31 = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %55, i32 0, i32 10, !dbg !1263
  %noatime32 = getelementptr inbounds %struct.restore_time, %struct.restore_time* %restore_time31, i32 0, i32 6, !dbg !1264
  store i32 %54, i32* %noatime32, align 4, !dbg !1265
  br label %if.end33, !dbg !1266

if.end33:                                         ; preds = %if.then20, %cond.end
  ret void, !dbg !1267
}

; Function Attrs: nounwind uwtable
define internal i32 @tree_current_is_dir(%struct.tree* %t) #0 !dbg !447 {
entry:
  %retval = alloca i32, align 4
  %t.addr = alloca %struct.tree*, align 8
  %st = alloca %struct.stat*, align 8
  store %struct.tree* %t, %struct.tree** %t.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tree** %t.addr, metadata !1268, metadata !460), !dbg !1269
  call void @llvm.dbg.declare(metadata %struct.stat** %st, metadata !1270, metadata !460), !dbg !1271
  %0 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !1272
  %flags = getelementptr inbounds %struct.tree, %struct.tree* %0, i32 0, i32 6, !dbg !1274
  %1 = load i32, i32* %flags, align 8, !dbg !1274
  %and = and i32 %1, 32, !dbg !1275
  %tobool = icmp ne i32 %and, 0, !dbg !1275
  br i1 %tobool, label %if.then, label %if.end11, !dbg !1276

if.then:                                          ; preds = %entry
  %2 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !1277
  %call = call %struct.stat* @tree_current_lstat(%struct.tree* %2), !dbg !1279
  store %struct.stat* %call, %struct.stat** %st, align 8, !dbg !1280
  %3 = load %struct.stat*, %struct.stat** %st, align 8, !dbg !1281
  %cmp = icmp eq %struct.stat* %3, null, !dbg !1283
  br i1 %cmp, label %if.then1, label %if.end, !dbg !1284

if.then1:                                         ; preds = %if.then
  store i32 0, i32* %retval, align 4, !dbg !1285
  br label %return, !dbg !1285

if.end:                                           ; preds = %if.then
  %4 = load %struct.stat*, %struct.stat** %st, align 8, !dbg !1286
  %st_mode = getelementptr inbounds %struct.stat, %struct.stat* %4, i32 0, i32 3, !dbg !1286
  %5 = load i32, i32* %st_mode, align 8, !dbg !1286
  %and2 = and i32 %5, 61440, !dbg !1286
  %cmp3 = icmp eq i32 %and2, 16384, !dbg !1286
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !1288

if.then4:                                         ; preds = %if.end
  store i32 1, i32* %retval, align 4, !dbg !1289
  br label %return, !dbg !1289

if.end5:                                          ; preds = %if.end
  %6 = load %struct.stat*, %struct.stat** %st, align 8, !dbg !1290
  %st_mode6 = getelementptr inbounds %struct.stat, %struct.stat* %6, i32 0, i32 3, !dbg !1290
  %7 = load i32, i32* %st_mode6, align 8, !dbg !1290
  %and7 = and i32 %7, 61440, !dbg !1290
  %cmp8 = icmp eq i32 %and7, 40960, !dbg !1290
  br i1 %cmp8, label %if.end10, label %if.then9, !dbg !1292

if.then9:                                         ; preds = %if.end5
  store i32 0, i32* %retval, align 4, !dbg !1293
  br label %return, !dbg !1293

if.end10:                                         ; preds = %if.end5
  br label %if.end11, !dbg !1294

if.end11:                                         ; preds = %if.end10, %entry
  %8 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !1295
  %call12 = call %struct.stat* @tree_current_stat(%struct.tree* %8), !dbg !1296
  store %struct.stat* %call12, %struct.stat** %st, align 8, !dbg !1297
  %9 = load %struct.stat*, %struct.stat** %st, align 8, !dbg !1298
  %cmp13 = icmp eq %struct.stat* %9, null, !dbg !1300
  br i1 %cmp13, label %if.then14, label %if.end15, !dbg !1301

if.then14:                                        ; preds = %if.end11
  store i32 0, i32* %retval, align 4, !dbg !1302
  br label %return, !dbg !1302

if.end15:                                         ; preds = %if.end11
  %10 = load %struct.stat*, %struct.stat** %st, align 8, !dbg !1303
  %st_mode16 = getelementptr inbounds %struct.stat, %struct.stat* %10, i32 0, i32 3, !dbg !1303
  %11 = load i32, i32* %st_mode16, align 8, !dbg !1303
  %and17 = and i32 %11, 61440, !dbg !1303
  %cmp18 = icmp eq i32 %and17, 16384, !dbg !1303
  %conv = zext i1 %cmp18 to i32, !dbg !1303
  store i32 %conv, i32* %retval, align 4, !dbg !1304
  br label %return, !dbg !1304

return:                                           ; preds = %if.end15, %if.then14, %if.then9, %if.then4, %if.then1
  %12 = load i32, i32* %retval, align 4, !dbg !1305
  ret i32 %12, !dbg !1305
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_disk_open(%struct.archive* %_a, i8* %pathname) #0 !dbg !359 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %pathname.addr = alloca i8*, align 8
  %a = alloca %struct.archive_read_disk*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !1306, metadata !460), !dbg !1307
  store i8* %pathname, i8** %pathname.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %pathname.addr, metadata !1308, metadata !460), !dbg !1309
  call void @llvm.dbg.declare(metadata %struct.archive_read_disk** %a, metadata !1310, metadata !460), !dbg !1311
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1312
  %1 = bitcast %struct.archive* %0 to %struct.archive_read_disk*, !dbg !1313
  store %struct.archive_read_disk* %1, %struct.archive_read_disk** %a, align 8, !dbg !1311
  br label %do.body, !dbg !1314

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !1315, metadata !460), !dbg !1317
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1318
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 195932357, i32 33, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.13, i32 0, i32 0)), !dbg !1318
  store i32 %call, i32* %magic_test, align 4, !dbg !1318
  %3 = load i32, i32* %magic_test, align 4, !dbg !1318
  %cmp = icmp eq i32 %3, -30, !dbg !1318
  br i1 %cmp, label %if.then, label %if.end, !dbg !1318

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !1320
  br label %return, !dbg !1320

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !1323

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1325
  %archive = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %4, i32 0, i32 0, !dbg !1326
  call void @archive_clear_error(%struct.archive* %archive), !dbg !1327
  %5 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1328
  %6 = load i8*, i8** %pathname.addr, align 8, !dbg !1329
  %call1 = call i32 @_archive_read_disk_open(%struct.archive* %5, i8* %6), !dbg !1330
  store i32 %call1, i32* %retval, align 4, !dbg !1331
  br label %return, !dbg !1331

return:                                           ; preds = %do.end, %if.then
  %7 = load i32, i32* %retval, align 4, !dbg !1332
  ret i32 %7, !dbg !1332
}

declare void @archive_clear_error(%struct.archive*) #2

; Function Attrs: nounwind uwtable
define internal i32 @_archive_read_disk_open(%struct.archive* %_a, i8* %pathname) #0 !dbg !434 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %pathname.addr = alloca i8*, align 8
  %a = alloca %struct.archive_read_disk*, align 8
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !1333, metadata !460), !dbg !1334
  store i8* %pathname, i8** %pathname.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %pathname.addr, metadata !1335, metadata !460), !dbg !1336
  call void @llvm.dbg.declare(metadata %struct.archive_read_disk** %a, metadata !1337, metadata !460), !dbg !1338
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1339
  %1 = bitcast %struct.archive* %0 to %struct.archive_read_disk*, !dbg !1340
  store %struct.archive_read_disk* %1, %struct.archive_read_disk** %a, align 8, !dbg !1338
  %2 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1341
  %tree = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %2, i32 0, i32 4, !dbg !1343
  %3 = load %struct.tree*, %struct.tree** %tree, align 8, !dbg !1343
  %cmp = icmp ne %struct.tree* %3, null, !dbg !1344
  br i1 %cmp, label %if.then, label %if.else, !dbg !1345

if.then:                                          ; preds = %entry
  %4 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1346
  %tree1 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %4, i32 0, i32 4, !dbg !1347
  %5 = load %struct.tree*, %struct.tree** %tree1, align 8, !dbg !1347
  %6 = load i8*, i8** %pathname.addr, align 8, !dbg !1348
  %7 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1349
  %flags = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %7, i32 0, i32 8, !dbg !1350
  %8 = load i32, i32* %flags, align 8, !dbg !1350
  %and = and i32 %8, 1, !dbg !1351
  %call = call %struct.tree* @tree_reopen(%struct.tree* %5, i8* %6, i32 %and), !dbg !1352
  %9 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1353
  %tree2 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %9, i32 0, i32 4, !dbg !1354
  store %struct.tree* %call, %struct.tree** %tree2, align 8, !dbg !1355
  br label %if.end, !dbg !1353

if.else:                                          ; preds = %entry
  %10 = load i8*, i8** %pathname.addr, align 8, !dbg !1356
  %11 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1357
  %symlink_mode = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %11, i32 0, i32 2, !dbg !1358
  %12 = load i8, i8* %symlink_mode, align 8, !dbg !1358
  %conv = sext i8 %12 to i32, !dbg !1357
  %13 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1359
  %flags3 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %13, i32 0, i32 8, !dbg !1360
  %14 = load i32, i32* %flags3, align 8, !dbg !1360
  %and4 = and i32 %14, 1, !dbg !1361
  %call5 = call %struct.tree* @tree_open(i8* %10, i32 %conv, i32 %and4), !dbg !1362
  %15 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1363
  %tree6 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %15, i32 0, i32 4, !dbg !1364
  store %struct.tree* %call5, %struct.tree** %tree6, align 8, !dbg !1365
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %16 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1366
  %tree7 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %16, i32 0, i32 4, !dbg !1368
  %17 = load %struct.tree*, %struct.tree** %tree7, align 8, !dbg !1368
  %cmp8 = icmp eq %struct.tree* %17, null, !dbg !1369
  br i1 %cmp8, label %if.then10, label %if.end12, !dbg !1370

if.then10:                                        ; preds = %if.end
  %18 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1371
  %archive = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %18, i32 0, i32 0, !dbg !1373
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.31, i32 0, i32 0)), !dbg !1374
  %19 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1375
  %archive11 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %19, i32 0, i32 0, !dbg !1376
  %state = getelementptr inbounds %struct.archive, %struct.archive* %archive11, i32 0, i32 1, !dbg !1377
  store i32 32768, i32* %state, align 4, !dbg !1378
  store i32 -30, i32* %retval, align 4, !dbg !1379
  br label %return, !dbg !1379

if.end12:                                         ; preds = %if.end
  %20 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1380
  %archive13 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %20, i32 0, i32 0, !dbg !1381
  %state14 = getelementptr inbounds %struct.archive, %struct.archive* %archive13, i32 0, i32 1, !dbg !1382
  store i32 2, i32* %state14, align 4, !dbg !1383
  store i32 0, i32* %retval, align 4, !dbg !1384
  br label %return, !dbg !1384

return:                                           ; preds = %if.end12, %if.then10
  %21 = load i32, i32* %retval, align 4, !dbg !1385
  ret i32 %21, !dbg !1385
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_disk_open_w(%struct.archive* %_a, i32* %pathname) #0 !dbg !362 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %pathname.addr = alloca i32*, align 8
  %a = alloca %struct.archive_read_disk*, align 8
  %path = alloca %struct.archive_string, align 8
  %ret = alloca i32, align 4
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !1386, metadata !460), !dbg !1387
  store i32* %pathname, i32** %pathname.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %pathname.addr, metadata !1388, metadata !460), !dbg !1389
  call void @llvm.dbg.declare(metadata %struct.archive_read_disk** %a, metadata !1390, metadata !460), !dbg !1391
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1392
  %1 = bitcast %struct.archive* %0 to %struct.archive_read_disk*, !dbg !1393
  store %struct.archive_read_disk* %1, %struct.archive_read_disk** %a, align 8, !dbg !1391
  call void @llvm.dbg.declare(metadata %struct.archive_string* %path, metadata !1394, metadata !460), !dbg !1395
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !1396, metadata !460), !dbg !1397
  br label %do.body, !dbg !1398

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !1399, metadata !460), !dbg !1401
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1402
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 195932357, i32 33, i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.14, i32 0, i32 0)), !dbg !1402
  store i32 %call, i32* %magic_test, align 4, !dbg !1402
  %3 = load i32, i32* %magic_test, align 4, !dbg !1402
  %cmp = icmp eq i32 %3, -30, !dbg !1402
  br i1 %cmp, label %if.then, label %if.end, !dbg !1402

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !1404
  br label %return, !dbg !1404

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !1407

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1409
  %archive = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %4, i32 0, i32 0, !dbg !1410
  call void @archive_clear_error(%struct.archive* %archive), !dbg !1411
  br label %do.body1, !dbg !1412

do.body1:                                         ; preds = %do.end
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %path, i32 0, i32 0, !dbg !1413
  store i8* null, i8** %s, align 8, !dbg !1413
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %path, i32 0, i32 1, !dbg !1413
  store i64 0, i64* %length, align 8, !dbg !1413
  %buffer_length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %path, i32 0, i32 2, !dbg !1413
  store i64 0, i64* %buffer_length, align 8, !dbg !1413
  br label %do.end2, !dbg !1413

do.end2:                                          ; preds = %do.body1
  %5 = load i32*, i32** %pathname.addr, align 8, !dbg !1416
  %6 = load i32*, i32** %pathname.addr, align 8, !dbg !1418
  %call3 = call i64 @wcslen(i32* %6) #7, !dbg !1419
  %call4 = call i32 @archive_string_append_from_wcs(%struct.archive_string* %path, i32* %5, i64 %call3), !dbg !1420
  %cmp5 = icmp ne i32 %call4, 0, !dbg !1421
  br i1 %cmp5, label %if.then6, label %if.else14, !dbg !1422

if.then6:                                         ; preds = %do.end2
  %call7 = call i32* @__errno_location() #1, !dbg !1423
  %7 = load i32, i32* %call7, align 4, !dbg !1423
  %cmp8 = icmp eq i32 %7, 12, !dbg !1426
  br i1 %cmp8, label %if.then9, label %if.else, !dbg !1427

if.then9:                                         ; preds = %if.then6
  %8 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1428
  %archive10 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %8, i32 0, i32 0, !dbg !1429
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive10, i32 12, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.15, i32 0, i32 0)), !dbg !1430
  br label %if.end12, !dbg !1430

if.else:                                          ; preds = %if.then6
  %9 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1431
  %archive11 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %9, i32 0, i32 0, !dbg !1432
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive11, i32 -1, i8* getelementptr inbounds ([38 x i8], [38 x i8]* @.str.16, i32 0, i32 0)), !dbg !1433
  br label %if.end12

if.end12:                                         ; preds = %if.else, %if.then9
  %10 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1434
  %archive13 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %10, i32 0, i32 0, !dbg !1435
  %state = getelementptr inbounds %struct.archive, %struct.archive* %archive13, i32 0, i32 1, !dbg !1436
  store i32 32768, i32* %state, align 4, !dbg !1437
  store i32 -30, i32* %ret, align 4, !dbg !1438
  br label %if.end17, !dbg !1439

if.else14:                                        ; preds = %do.end2
  %11 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1440
  %s15 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %path, i32 0, i32 0, !dbg !1441
  %12 = load i8*, i8** %s15, align 8, !dbg !1441
  %call16 = call i32 @_archive_read_disk_open(%struct.archive* %11, i8* %12), !dbg !1442
  store i32 %call16, i32* %ret, align 4, !dbg !1443
  br label %if.end17

if.end17:                                         ; preds = %if.else14, %if.end12
  call void @archive_string_free(%struct.archive_string* %path), !dbg !1444
  %13 = load i32, i32* %ret, align 4, !dbg !1445
  store i32 %13, i32* %retval, align 4, !dbg !1446
  br label %return, !dbg !1446

return:                                           ; preds = %if.end17, %if.then
  %14 = load i32, i32* %retval, align 4, !dbg !1447
  ret i32 %14, !dbg !1447
}

declare i32 @archive_string_append_from_wcs(%struct.archive_string*, i32*, i64) #2

; Function Attrs: nounwind readonly
declare i64 @wcslen(i32*) #4

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #5

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

declare void @archive_string_free(%struct.archive_string*) #2

; Function Attrs: nounwind uwtable
define i32 @archive_read_disk_current_filesystem(%struct.archive* %_a) #0 !dbg !368 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_read_disk*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !1448, metadata !460), !dbg !1449
  call void @llvm.dbg.declare(metadata %struct.archive_read_disk** %a, metadata !1450, metadata !460), !dbg !1451
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1452
  %1 = bitcast %struct.archive* %0 to %struct.archive_read_disk*, !dbg !1453
  store %struct.archive_read_disk* %1, %struct.archive_read_disk** %a, align 8, !dbg !1451
  br label %do.body, !dbg !1454

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !1455, metadata !460), !dbg !1457
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1458
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 195932357, i32 4, i8* getelementptr inbounds ([37 x i8], [37 x i8]* @.str.17, i32 0, i32 0)), !dbg !1458
  store i32 %call, i32* %magic_test, align 4, !dbg !1458
  %3 = load i32, i32* %magic_test, align 4, !dbg !1458
  %cmp = icmp eq i32 %3, -30, !dbg !1458
  br i1 %cmp, label %if.then, label %if.end, !dbg !1458

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !1460
  br label %return, !dbg !1460

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !1463

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1465
  %tree = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %4, i32 0, i32 4, !dbg !1466
  %5 = load %struct.tree*, %struct.tree** %tree, align 8, !dbg !1466
  %current_filesystem_id = getelementptr inbounds %struct.tree, %struct.tree* %5, i32 0, i32 31, !dbg !1467
  %6 = load i32, i32* %current_filesystem_id, align 4, !dbg !1467
  store i32 %6, i32* %retval, align 4, !dbg !1468
  br label %return, !dbg !1468

return:                                           ; preds = %do.end, %if.then
  %7 = load i32, i32* %retval, align 4, !dbg !1469
  ret i32 %7, !dbg !1469
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_disk_current_filesystem_is_synthetic(%struct.archive* %_a) #0 !dbg !369 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_read_disk*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !1470, metadata !460), !dbg !1471
  call void @llvm.dbg.declare(metadata %struct.archive_read_disk** %a, metadata !1472, metadata !460), !dbg !1473
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1474
  %1 = bitcast %struct.archive* %0 to %struct.archive_read_disk*, !dbg !1475
  store %struct.archive_read_disk* %1, %struct.archive_read_disk** %a, align 8, !dbg !1473
  br label %do.body, !dbg !1476

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !1477, metadata !460), !dbg !1479
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1480
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 195932357, i32 4, i8* getelementptr inbounds ([37 x i8], [37 x i8]* @.str.17, i32 0, i32 0)), !dbg !1480
  store i32 %call, i32* %magic_test, align 4, !dbg !1480
  %3 = load i32, i32* %magic_test, align 4, !dbg !1480
  %cmp = icmp eq i32 %3, -30, !dbg !1480
  br i1 %cmp, label %if.then, label %if.end, !dbg !1480

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !1482
  br label %return, !dbg !1482

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !1485

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1487
  %tree = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %4, i32 0, i32 4, !dbg !1488
  %5 = load %struct.tree*, %struct.tree** %tree, align 8, !dbg !1488
  %current_filesystem = getelementptr inbounds %struct.tree, %struct.tree* %5, i32 0, i32 28, !dbg !1489
  %6 = load %struct.filesystem*, %struct.filesystem** %current_filesystem, align 8, !dbg !1489
  %synthetic = getelementptr inbounds %struct.filesystem, %struct.filesystem* %6, i32 0, i32 1, !dbg !1490
  %7 = load i32, i32* %synthetic, align 8, !dbg !1490
  store i32 %7, i32* %retval, align 4, !dbg !1491
  br label %return, !dbg !1491

return:                                           ; preds = %do.end, %if.then
  %8 = load i32, i32* %retval, align 4, !dbg !1492
  ret i32 %8, !dbg !1492
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_disk_current_filesystem_is_remote(%struct.archive* %_a) #0 !dbg !370 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_read_disk*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !1493, metadata !460), !dbg !1494
  call void @llvm.dbg.declare(metadata %struct.archive_read_disk** %a, metadata !1495, metadata !460), !dbg !1496
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1497
  %1 = bitcast %struct.archive* %0 to %struct.archive_read_disk*, !dbg !1498
  store %struct.archive_read_disk* %1, %struct.archive_read_disk** %a, align 8, !dbg !1496
  br label %do.body, !dbg !1499

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !1500, metadata !460), !dbg !1502
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1503
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 195932357, i32 4, i8* getelementptr inbounds ([37 x i8], [37 x i8]* @.str.17, i32 0, i32 0)), !dbg !1503
  store i32 %call, i32* %magic_test, align 4, !dbg !1503
  %3 = load i32, i32* %magic_test, align 4, !dbg !1503
  %cmp = icmp eq i32 %3, -30, !dbg !1503
  br i1 %cmp, label %if.then, label %if.end, !dbg !1503

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !1505
  br label %return, !dbg !1505

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !1508

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1510
  %tree = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %4, i32 0, i32 4, !dbg !1511
  %5 = load %struct.tree*, %struct.tree** %tree, align 8, !dbg !1511
  %current_filesystem = getelementptr inbounds %struct.tree, %struct.tree* %5, i32 0, i32 28, !dbg !1512
  %6 = load %struct.filesystem*, %struct.filesystem** %current_filesystem, align 8, !dbg !1512
  %remote = getelementptr inbounds %struct.filesystem, %struct.filesystem* %6, i32 0, i32 2, !dbg !1513
  %7 = load i32, i32* %remote, align 4, !dbg !1513
  store i32 %7, i32* %retval, align 4, !dbg !1514
  br label %return, !dbg !1514

return:                                           ; preds = %do.end, %if.then
  %8 = load i32, i32* %retval, align 4, !dbg !1515
  ret i32 %8, !dbg !1515
}

; Function Attrs: nounwind uwtable
define internal i32 @_archive_read_free(%struct.archive* %_a) #0 !dbg !374 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_read_disk*, align 8
  %r = alloca i32, align 4
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !1516, metadata !460), !dbg !1517
  call void @llvm.dbg.declare(metadata %struct.archive_read_disk** %a, metadata !1518, metadata !460), !dbg !1519
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1520
  %1 = bitcast %struct.archive* %0 to %struct.archive_read_disk*, !dbg !1521
  store %struct.archive_read_disk* %1, %struct.archive_read_disk** %a, align 8, !dbg !1519
  call void @llvm.dbg.declare(metadata i32* %r, metadata !1522, metadata !460), !dbg !1523
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1524
  %cmp = icmp eq %struct.archive* %2, null, !dbg !1526
  br i1 %cmp, label %if.then, label %if.end, !dbg !1527

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !1528
  br label %return, !dbg !1528

if.end:                                           ; preds = %entry
  br label %do.body, !dbg !1529

do.body:                                          ; preds = %if.end
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !1530, metadata !460), !dbg !1532
  %3 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1533
  %call = call i32 @__archive_check_magic(%struct.archive* %3, i32 195932357, i32 65535, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.18, i32 0, i32 0)), !dbg !1533
  store i32 %call, i32* %magic_test, align 4, !dbg !1533
  %4 = load i32, i32* %magic_test, align 4, !dbg !1533
  %cmp1 = icmp eq i32 %4, -30, !dbg !1533
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !1533

if.then2:                                         ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !1535
  br label %return, !dbg !1535

if.end3:                                          ; preds = %do.body
  br label %do.end, !dbg !1538

do.end:                                           ; preds = %if.end3
  %5 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1540
  %archive = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %5, i32 0, i32 0, !dbg !1542
  %state = getelementptr inbounds %struct.archive, %struct.archive* %archive, i32 0, i32 1, !dbg !1543
  %6 = load i32, i32* %state, align 4, !dbg !1543
  %cmp4 = icmp ne i32 %6, 32, !dbg !1544
  br i1 %cmp4, label %if.then5, label %if.else, !dbg !1545

if.then5:                                         ; preds = %do.end
  %7 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1546
  %archive6 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %7, i32 0, i32 0, !dbg !1547
  %call7 = call i32 @_archive_read_close(%struct.archive* %archive6), !dbg !1548
  store i32 %call7, i32* %r, align 4, !dbg !1549
  br label %if.end8, !dbg !1550

if.else:                                          ; preds = %do.end
  store i32 0, i32* %r, align 4, !dbg !1551
  br label %if.end8

if.end8:                                          ; preds = %if.else, %if.then5
  %8 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1552
  %tree = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %8, i32 0, i32 4, !dbg !1553
  %9 = load %struct.tree*, %struct.tree** %tree, align 8, !dbg !1553
  call void @tree_free(%struct.tree* %9), !dbg !1554
  %10 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1555
  %cleanup_gname = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %10, i32 0, i32 10, !dbg !1557
  %11 = load void (i8*)*, void (i8*)** %cleanup_gname, align 8, !dbg !1557
  %cmp9 = icmp ne void (i8*)* %11, null, !dbg !1558
  br i1 %cmp9, label %land.lhs.true, label %if.end14, !dbg !1559

land.lhs.true:                                    ; preds = %if.end8
  %12 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1560
  %lookup_gname_data = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %12, i32 0, i32 11, !dbg !1562
  %13 = load i8*, i8** %lookup_gname_data, align 8, !dbg !1562
  %cmp10 = icmp ne i8* %13, null, !dbg !1563
  br i1 %cmp10, label %if.then11, label %if.end14, !dbg !1564

if.then11:                                        ; preds = %land.lhs.true
  %14 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1565
  %cleanup_gname12 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %14, i32 0, i32 10, !dbg !1566
  %15 = load void (i8*)*, void (i8*)** %cleanup_gname12, align 8, !dbg !1566
  %16 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1567
  %lookup_gname_data13 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %16, i32 0, i32 11, !dbg !1568
  %17 = load i8*, i8** %lookup_gname_data13, align 8, !dbg !1568
  call void %15(i8* %17), !dbg !1569
  br label %if.end14, !dbg !1569

if.end14:                                         ; preds = %if.then11, %land.lhs.true, %if.end8
  %18 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1570
  %cleanup_uname = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %18, i32 0, i32 13, !dbg !1572
  %19 = load void (i8*)*, void (i8*)** %cleanup_uname, align 8, !dbg !1572
  %cmp15 = icmp ne void (i8*)* %19, null, !dbg !1573
  br i1 %cmp15, label %land.lhs.true16, label %if.end21, !dbg !1574

land.lhs.true16:                                  ; preds = %if.end14
  %20 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1575
  %lookup_uname_data = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %20, i32 0, i32 14, !dbg !1577
  %21 = load i8*, i8** %lookup_uname_data, align 8, !dbg !1577
  %cmp17 = icmp ne i8* %21, null, !dbg !1578
  br i1 %cmp17, label %if.then18, label %if.end21, !dbg !1579

if.then18:                                        ; preds = %land.lhs.true16
  %22 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1580
  %cleanup_uname19 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %22, i32 0, i32 13, !dbg !1581
  %23 = load void (i8*)*, void (i8*)** %cleanup_uname19, align 8, !dbg !1581
  %24 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1582
  %lookup_uname_data20 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %24, i32 0, i32 14, !dbg !1583
  %25 = load i8*, i8** %lookup_uname_data20, align 8, !dbg !1583
  call void %23(i8* %25), !dbg !1584
  br label %if.end21, !dbg !1584

if.end21:                                         ; preds = %if.then18, %land.lhs.true16, %if.end14
  %26 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1585
  %archive22 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %26, i32 0, i32 0, !dbg !1586
  %error_string = getelementptr inbounds %struct.archive, %struct.archive* %archive22, i32 0, i32 10, !dbg !1587
  call void @archive_string_free(%struct.archive_string* %error_string), !dbg !1588
  %27 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1589
  %entry23 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %27, i32 0, i32 1, !dbg !1590
  %28 = load %struct.archive_entry*, %struct.archive_entry** %entry23, align 8, !dbg !1590
  call void @archive_entry_free(%struct.archive_entry* %28), !dbg !1591
  %29 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1592
  %archive24 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %29, i32 0, i32 0, !dbg !1593
  %magic = getelementptr inbounds %struct.archive, %struct.archive* %archive24, i32 0, i32 0, !dbg !1594
  store i32 0, i32* %magic, align 8, !dbg !1595
  %30 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1596
  %archive25 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %30, i32 0, i32 0, !dbg !1597
  %call26 = call i32 @__archive_clean(%struct.archive* %archive25), !dbg !1598
  %31 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1599
  %32 = bitcast %struct.archive_read_disk* %31 to i8*, !dbg !1599
  call void @free(i8* %32) #6, !dbg !1600
  %33 = load i32, i32* %r, align 4, !dbg !1601
  store i32 %33, i32* %retval, align 4, !dbg !1602
  br label %return, !dbg !1602

return:                                           ; preds = %if.end21, %if.then2, %if.then
  %34 = load i32, i32* %retval, align 4, !dbg !1603
  ret i32 %34, !dbg !1603
}

; Function Attrs: nounwind uwtable
define internal i32 @_archive_read_close(%struct.archive* %_a) #0 !dbg !378 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_read_disk*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !1604, metadata !460), !dbg !1605
  call void @llvm.dbg.declare(metadata %struct.archive_read_disk** %a, metadata !1606, metadata !460), !dbg !1607
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1608
  %1 = bitcast %struct.archive* %0 to %struct.archive_read_disk*, !dbg !1609
  store %struct.archive_read_disk* %1, %struct.archive_read_disk** %a, align 8, !dbg !1607
  br label %do.body, !dbg !1610

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !1611, metadata !460), !dbg !1613
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1614
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 195932357, i32 65535, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.19, i32 0, i32 0)), !dbg !1614
  store i32 %call, i32* %magic_test, align 4, !dbg !1614
  %3 = load i32, i32* %magic_test, align 4, !dbg !1614
  %cmp = icmp eq i32 %3, -30, !dbg !1614
  br i1 %cmp, label %if.then, label %if.end, !dbg !1614

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !1616
  br label %return, !dbg !1616

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !1619

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1621
  %archive = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %4, i32 0, i32 0, !dbg !1623
  %state = getelementptr inbounds %struct.archive, %struct.archive* %archive, i32 0, i32 1, !dbg !1624
  %5 = load i32, i32* %state, align 4, !dbg !1624
  %cmp1 = icmp ne i32 %5, 32768, !dbg !1625
  br i1 %cmp1, label %if.then2, label %if.end5, !dbg !1626

if.then2:                                         ; preds = %do.end
  %6 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1627
  %archive3 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %6, i32 0, i32 0, !dbg !1628
  %state4 = getelementptr inbounds %struct.archive, %struct.archive* %archive3, i32 0, i32 1, !dbg !1629
  store i32 32, i32* %state4, align 4, !dbg !1630
  br label %if.end5, !dbg !1627

if.end5:                                          ; preds = %if.then2, %do.end
  %7 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1631
  %tree = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %7, i32 0, i32 4, !dbg !1632
  %8 = load %struct.tree*, %struct.tree** %tree, align 8, !dbg !1632
  call void @tree_close(%struct.tree* %8), !dbg !1633
  store i32 0, i32* %retval, align 4, !dbg !1634
  br label %return, !dbg !1634

return:                                           ; preds = %if.end5, %if.then
  %9 = load i32, i32* %retval, align 4, !dbg !1635
  ret i32 %9, !dbg !1635
}

; Function Attrs: nounwind uwtable
define internal i32 @_archive_read_data_block(%struct.archive* %_a, i8** %buff, i64* %size, i64* %offset) #0 !dbg !385 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %buff.addr = alloca i8**, align 8
  %size.addr = alloca i64*, align 8
  %offset.addr = alloca i64*, align 8
  %a = alloca %struct.archive_read_disk*, align 8
  %t = alloca %struct.tree*, align 8
  %r = alloca i32, align 4
  %bytes = alloca i64, align 8
  %buffbytes = alloca i64, align 8
  %empty_sparse_region = alloca i32, align 4
  %magic_test = alloca i32, align 4
  %flags = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !1636, metadata !460), !dbg !1637
  store i8** %buff, i8*** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %buff.addr, metadata !1638, metadata !460), !dbg !1639
  store i64* %size, i64** %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %size.addr, metadata !1640, metadata !460), !dbg !1641
  store i64* %offset, i64** %offset.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %offset.addr, metadata !1642, metadata !460), !dbg !1643
  call void @llvm.dbg.declare(metadata %struct.archive_read_disk** %a, metadata !1644, metadata !460), !dbg !1645
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1646
  %1 = bitcast %struct.archive* %0 to %struct.archive_read_disk*, !dbg !1647
  store %struct.archive_read_disk* %1, %struct.archive_read_disk** %a, align 8, !dbg !1645
  call void @llvm.dbg.declare(metadata %struct.tree** %t, metadata !1648, metadata !460), !dbg !1649
  %2 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1650
  %tree = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %2, i32 0, i32 4, !dbg !1651
  %3 = load %struct.tree*, %struct.tree** %tree, align 8, !dbg !1651
  store %struct.tree* %3, %struct.tree** %t, align 8, !dbg !1649
  call void @llvm.dbg.declare(metadata i32* %r, metadata !1652, metadata !460), !dbg !1653
  call void @llvm.dbg.declare(metadata i64* %bytes, metadata !1654, metadata !460), !dbg !1655
  call void @llvm.dbg.declare(metadata i64* %buffbytes, metadata !1656, metadata !460), !dbg !1657
  call void @llvm.dbg.declare(metadata i32* %empty_sparse_region, metadata !1658, metadata !460), !dbg !1659
  store i32 0, i32* %empty_sparse_region, align 4, !dbg !1659
  br label %do.body, !dbg !1660

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !1661, metadata !460), !dbg !1663
  %4 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1664
  %call = call i32 @__archive_check_magic(%struct.archive* %4, i32 195932357, i32 4, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.20, i32 0, i32 0)), !dbg !1664
  store i32 %call, i32* %magic_test, align 4, !dbg !1664
  %5 = load i32, i32* %magic_test, align 4, !dbg !1664
  %cmp = icmp eq i32 %5, -30, !dbg !1664
  br i1 %cmp, label %if.then, label %if.end, !dbg !1664

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !1666
  br label %return, !dbg !1666

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !1669

do.end:                                           ; preds = %if.end
  %6 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1671
  %entry_eof = getelementptr inbounds %struct.tree, %struct.tree* %6, i32 0, i32 35, !dbg !1673
  %7 = load i32, i32* %entry_eof, align 4, !dbg !1673
  %tobool = icmp ne i32 %7, 0, !dbg !1671
  br i1 %tobool, label %if.then2, label %lor.lhs.false, !dbg !1674

lor.lhs.false:                                    ; preds = %do.end
  %8 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1675
  %entry_remaining_bytes = getelementptr inbounds %struct.tree, %struct.tree* %8, i32 0, i32 36, !dbg !1677
  %9 = load i64, i64* %entry_remaining_bytes, align 8, !dbg !1677
  %cmp1 = icmp sle i64 %9, 0, !dbg !1678
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !1679

if.then2:                                         ; preds = %lor.lhs.false, %do.end
  store i32 1, i32* %r, align 4, !dbg !1680
  br label %abort_read_data, !dbg !1682

if.end3:                                          ; preds = %lor.lhs.false
  %10 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1683
  %entry_fd = getelementptr inbounds %struct.tree, %struct.tree* %10, i32 0, i32 34, !dbg !1685
  %11 = load i32, i32* %entry_fd, align 8, !dbg !1685
  %cmp4 = icmp slt i32 %11, 0, !dbg !1686
  br i1 %cmp4, label %if.then5, label %if.end40, !dbg !1687

if.then5:                                         ; preds = %if.end3
  call void @llvm.dbg.declare(metadata i32* %flags, metadata !1688, metadata !460), !dbg !1690
  store i32 524288, i32* %flags, align 4, !dbg !1690
  %12 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1691
  %flags6 = getelementptr inbounds %struct.tree, %struct.tree* %12, i32 0, i32 6, !dbg !1693
  %13 = load i32, i32* %flags6, align 8, !dbg !1693
  %and = and i32 %13, 128, !dbg !1694
  %cmp7 = icmp ne i32 %and, 0, !dbg !1695
  br i1 %cmp7, label %land.lhs.true, label %if.end10, !dbg !1696

land.lhs.true:                                    ; preds = %if.then5
  %14 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1697
  %restore_time = getelementptr inbounds %struct.tree, %struct.tree* %14, i32 0, i32 21, !dbg !1698
  %noatime = getelementptr inbounds %struct.restore_time, %struct.restore_time* %restore_time, i32 0, i32 6, !dbg !1699
  %15 = load i32, i32* %noatime, align 4, !dbg !1699
  %cmp8 = icmp eq i32 %15, 0, !dbg !1700
  br i1 %cmp8, label %if.then9, label %if.end10, !dbg !1701

if.then9:                                         ; preds = %land.lhs.true
  %16 = load i32, i32* %flags, align 4, !dbg !1703
  %or = or i32 %16, 262144, !dbg !1703
  store i32 %or, i32* %flags, align 4, !dbg !1703
  br label %if.end10, !dbg !1704

if.end10:                                         ; preds = %if.then9, %land.lhs.true, %if.then5
  br label %do.body11, !dbg !1705

do.body11:                                        ; preds = %if.end10
  %17 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1706
  %18 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1708
  %call12 = call i8* @tree_current_access_path(%struct.tree* %18), !dbg !1709
  %19 = load i32, i32* %flags, align 4, !dbg !1710
  %call13 = call i32 @open_on_current_dir(%struct.tree* %17, i8* %call12, i32 %19), !dbg !1711
  %20 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1712
  %entry_fd14 = getelementptr inbounds %struct.tree, %struct.tree* %20, i32 0, i32 34, !dbg !1713
  store i32 %call13, i32* %entry_fd14, align 8, !dbg !1714
  %21 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1715
  %entry_fd15 = getelementptr inbounds %struct.tree, %struct.tree* %21, i32 0, i32 34, !dbg !1716
  %22 = load i32, i32* %entry_fd15, align 8, !dbg !1716
  call void @__archive_ensure_cloexec_flag(i32 %22), !dbg !1717
  %23 = load i32, i32* %flags, align 4, !dbg !1718
  %and16 = and i32 %23, 262144, !dbg !1720
  %tobool17 = icmp ne i32 %and16, 0, !dbg !1720
  br i1 %tobool17, label %if.then18, label %if.end30, !dbg !1721

if.then18:                                        ; preds = %do.body11
  %24 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1722
  %entry_fd19 = getelementptr inbounds %struct.tree, %struct.tree* %24, i32 0, i32 34, !dbg !1725
  %25 = load i32, i32* %entry_fd19, align 8, !dbg !1725
  %cmp20 = icmp sge i32 %25, 0, !dbg !1726
  br i1 %cmp20, label %if.then21, label %if.else, !dbg !1727

if.then21:                                        ; preds = %if.then18
  %26 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1728
  %restore_time22 = getelementptr inbounds %struct.tree, %struct.tree* %26, i32 0, i32 21, !dbg !1729
  %noatime23 = getelementptr inbounds %struct.restore_time, %struct.restore_time* %restore_time22, i32 0, i32 6, !dbg !1730
  store i32 1, i32* %noatime23, align 4, !dbg !1731
  br label %if.end29, !dbg !1728

if.else:                                          ; preds = %if.then18
  %call24 = call i32* @__errno_location() #1, !dbg !1732
  %27 = load i32, i32* %call24, align 4, !dbg !1732
  %cmp25 = icmp eq i32 %27, 1, !dbg !1734
  br i1 %cmp25, label %if.then26, label %if.end28, !dbg !1735

if.then26:                                        ; preds = %if.else
  %28 = load i32, i32* %flags, align 4, !dbg !1736
  %and27 = and i32 %28, -262145, !dbg !1736
  store i32 %and27, i32* %flags, align 4, !dbg !1736
  br label %do.end31, !dbg !1738

if.end28:                                         ; preds = %if.else
  br label %if.end29

if.end29:                                         ; preds = %if.end28, %if.then21
  br label %if.end30, !dbg !1739

if.end30:                                         ; preds = %if.end29, %do.body11
  br label %do.end31, !dbg !1740

do.end31:                                         ; preds = %if.then26, %if.end30
  %29 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1741
  %entry_fd32 = getelementptr inbounds %struct.tree, %struct.tree* %29, i32 0, i32 34, !dbg !1743
  %30 = load i32, i32* %entry_fd32, align 8, !dbg !1743
  %cmp33 = icmp slt i32 %30, 0, !dbg !1744
  br i1 %cmp33, label %if.then34, label %if.end38, !dbg !1745

if.then34:                                        ; preds = %do.end31
  %31 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1746
  %archive = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %31, i32 0, i32 0, !dbg !1748
  %call35 = call i32* @__errno_location() #1, !dbg !1749
  %32 = load i32, i32* %call35, align 4, !dbg !1749
  %33 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1750
  %call36 = call i8* @tree_current_path(%struct.tree* %33), !dbg !1751
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 %32, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.21, i32 0, i32 0), i8* %call36), !dbg !1752
  store i32 -25, i32* %r, align 4, !dbg !1753
  %34 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1754
  %call37 = call i32 @tree_enter_initial_dir(%struct.tree* %34), !dbg !1755
  br label %abort_read_data, !dbg !1756

if.end38:                                         ; preds = %do.end31
  %35 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1757
  %call39 = call i32 @tree_enter_initial_dir(%struct.tree* %35), !dbg !1758
  br label %if.end40, !dbg !1759

if.end40:                                         ; preds = %if.end38, %if.end3
  %36 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1760
  %current_filesystem = getelementptr inbounds %struct.tree, %struct.tree* %36, i32 0, i32 28, !dbg !1762
  %37 = load %struct.filesystem*, %struct.filesystem** %current_filesystem, align 8, !dbg !1762
  %allocation_ptr = getelementptr inbounds %struct.filesystem, %struct.filesystem* %37, i32 0, i32 9, !dbg !1763
  %38 = load i8*, i8** %allocation_ptr, align 8, !dbg !1763
  %cmp41 = icmp eq i8* %38, null, !dbg !1764
  br i1 %cmp41, label %if.then42, label %if.end48, !dbg !1765

if.then42:                                        ; preds = %if.end40
  %39 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1766
  %call43 = call i32 @setup_suitable_read_buffer(%struct.archive_read_disk* %39), !dbg !1768
  store i32 %call43, i32* %r, align 4, !dbg !1769
  %40 = load i32, i32* %r, align 4, !dbg !1770
  %cmp44 = icmp ne i32 %40, 0, !dbg !1772
  br i1 %cmp44, label %if.then45, label %if.end47, !dbg !1773

if.then45:                                        ; preds = %if.then42
  %41 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1774
  %archive46 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %41, i32 0, i32 0, !dbg !1776
  %state = getelementptr inbounds %struct.archive, %struct.archive* %archive46, i32 0, i32 1, !dbg !1777
  store i32 32768, i32* %state, align 4, !dbg !1778
  br label %abort_read_data, !dbg !1779

if.end47:                                         ; preds = %if.then42
  br label %if.end48, !dbg !1780

if.end48:                                         ; preds = %if.end47, %if.end40
  %42 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1781
  %current_filesystem49 = getelementptr inbounds %struct.tree, %struct.tree* %42, i32 0, i32 28, !dbg !1782
  %43 = load %struct.filesystem*, %struct.filesystem** %current_filesystem49, align 8, !dbg !1782
  %buff50 = getelementptr inbounds %struct.filesystem, %struct.filesystem* %43, i32 0, i32 10, !dbg !1783
  %44 = load i8*, i8** %buff50, align 8, !dbg !1783
  %45 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1784
  %entry_buff = getelementptr inbounds %struct.tree, %struct.tree* %45, i32 0, i32 38, !dbg !1785
  store i8* %44, i8** %entry_buff, align 8, !dbg !1786
  %46 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1787
  %current_filesystem51 = getelementptr inbounds %struct.tree, %struct.tree* %46, i32 0, i32 28, !dbg !1788
  %47 = load %struct.filesystem*, %struct.filesystem** %current_filesystem51, align 8, !dbg !1788
  %buff_size = getelementptr inbounds %struct.filesystem, %struct.filesystem* %47, i32 0, i32 11, !dbg !1789
  %48 = load i64, i64* %buff_size, align 8, !dbg !1789
  %49 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1790
  %entry_buff_size = getelementptr inbounds %struct.tree, %struct.tree* %49, i32 0, i32 39, !dbg !1791
  store i64 %48, i64* %entry_buff_size, align 8, !dbg !1792
  %50 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1793
  %entry_buff_size52 = getelementptr inbounds %struct.tree, %struct.tree* %50, i32 0, i32 39, !dbg !1794
  %51 = load i64, i64* %entry_buff_size52, align 8, !dbg !1794
  store i64 %51, i64* %buffbytes, align 8, !dbg !1795
  %52 = load i64, i64* %buffbytes, align 8, !dbg !1796
  %53 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1798
  %current_sparse = getelementptr inbounds %struct.tree, %struct.tree* %53, i32 0, i32 23, !dbg !1799
  %54 = load %struct.entry_sparse*, %struct.entry_sparse** %current_sparse, align 8, !dbg !1799
  %length = getelementptr inbounds %struct.entry_sparse, %struct.entry_sparse* %54, i32 0, i32 0, !dbg !1800
  %55 = load i64, i64* %length, align 8, !dbg !1800
  %cmp53 = icmp sgt i64 %52, %55, !dbg !1801
  br i1 %cmp53, label %if.then54, label %if.end57, !dbg !1802

if.then54:                                        ; preds = %if.end48
  %56 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1803
  %current_sparse55 = getelementptr inbounds %struct.tree, %struct.tree* %56, i32 0, i32 23, !dbg !1804
  %57 = load %struct.entry_sparse*, %struct.entry_sparse** %current_sparse55, align 8, !dbg !1804
  %length56 = getelementptr inbounds %struct.entry_sparse, %struct.entry_sparse* %57, i32 0, i32 0, !dbg !1805
  %58 = load i64, i64* %length56, align 8, !dbg !1805
  store i64 %58, i64* %buffbytes, align 8, !dbg !1806
  br label %if.end57, !dbg !1807

if.end57:                                         ; preds = %if.then54, %if.end48
  %59 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1808
  %current_sparse58 = getelementptr inbounds %struct.tree, %struct.tree* %59, i32 0, i32 23, !dbg !1810
  %60 = load %struct.entry_sparse*, %struct.entry_sparse** %current_sparse58, align 8, !dbg !1810
  %length59 = getelementptr inbounds %struct.entry_sparse, %struct.entry_sparse* %60, i32 0, i32 0, !dbg !1811
  %61 = load i64, i64* %length59, align 8, !dbg !1811
  %cmp60 = icmp eq i64 %61, 0, !dbg !1812
  br i1 %cmp60, label %if.then61, label %if.end62, !dbg !1813

if.then61:                                        ; preds = %if.end57
  store i32 1, i32* %empty_sparse_region, align 4, !dbg !1814
  br label %if.end62, !dbg !1815

if.end62:                                         ; preds = %if.then61, %if.end57
  %62 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1816
  %current_sparse63 = getelementptr inbounds %struct.tree, %struct.tree* %62, i32 0, i32 23, !dbg !1818
  %63 = load %struct.entry_sparse*, %struct.entry_sparse** %current_sparse63, align 8, !dbg !1818
  %offset64 = getelementptr inbounds %struct.entry_sparse, %struct.entry_sparse* %63, i32 0, i32 1, !dbg !1819
  %64 = load i64, i64* %offset64, align 8, !dbg !1819
  %65 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1820
  %entry_total = getelementptr inbounds %struct.tree, %struct.tree* %65, i32 0, i32 37, !dbg !1821
  %66 = load i64, i64* %entry_total, align 8, !dbg !1821
  %cmp65 = icmp sgt i64 %64, %66, !dbg !1822
  br i1 %cmp65, label %if.then66, label %if.end84, !dbg !1823

if.then66:                                        ; preds = %if.end62
  %67 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1824
  %entry_fd67 = getelementptr inbounds %struct.tree, %struct.tree* %67, i32 0, i32 34, !dbg !1827
  %68 = load i32, i32* %entry_fd67, align 8, !dbg !1827
  %69 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1828
  %current_sparse68 = getelementptr inbounds %struct.tree, %struct.tree* %69, i32 0, i32 23, !dbg !1829
  %70 = load %struct.entry_sparse*, %struct.entry_sparse** %current_sparse68, align 8, !dbg !1829
  %offset69 = getelementptr inbounds %struct.entry_sparse, %struct.entry_sparse* %70, i32 0, i32 1, !dbg !1830
  %71 = load i64, i64* %offset69, align 8, !dbg !1830
  %call70 = call i64 @lseek(i32 %68, i64 %71, i32 0) #6, !dbg !1831
  %cmp71 = icmp slt i64 %call70, 0, !dbg !1832
  br i1 %cmp71, label %if.then72, label %if.end77, !dbg !1833

if.then72:                                        ; preds = %if.then66
  %72 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1834
  %archive73 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %72, i32 0, i32 0, !dbg !1836
  %call74 = call i32* @__errno_location() #1, !dbg !1837
  %73 = load i32, i32* %call74, align 4, !dbg !1837
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive73, i32 %73, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.22, i32 0, i32 0)), !dbg !1838
  store i32 -30, i32* %r, align 4, !dbg !1840
  %74 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1841
  %archive75 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %74, i32 0, i32 0, !dbg !1842
  %state76 = getelementptr inbounds %struct.archive, %struct.archive* %archive75, i32 0, i32 1, !dbg !1843
  store i32 32768, i32* %state76, align 4, !dbg !1844
  br label %abort_read_data, !dbg !1845

if.end77:                                         ; preds = %if.then66
  %75 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1846
  %current_sparse78 = getelementptr inbounds %struct.tree, %struct.tree* %75, i32 0, i32 23, !dbg !1847
  %76 = load %struct.entry_sparse*, %struct.entry_sparse** %current_sparse78, align 8, !dbg !1847
  %offset79 = getelementptr inbounds %struct.entry_sparse, %struct.entry_sparse* %76, i32 0, i32 1, !dbg !1848
  %77 = load i64, i64* %offset79, align 8, !dbg !1848
  %78 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1849
  %entry_total80 = getelementptr inbounds %struct.tree, %struct.tree* %78, i32 0, i32 37, !dbg !1850
  %79 = load i64, i64* %entry_total80, align 8, !dbg !1850
  %sub = sub nsw i64 %77, %79, !dbg !1851
  store i64 %sub, i64* %bytes, align 8, !dbg !1852
  %80 = load i64, i64* %bytes, align 8, !dbg !1853
  %81 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1854
  %entry_remaining_bytes81 = getelementptr inbounds %struct.tree, %struct.tree* %81, i32 0, i32 36, !dbg !1855
  %82 = load i64, i64* %entry_remaining_bytes81, align 8, !dbg !1856
  %sub82 = sub nsw i64 %82, %80, !dbg !1856
  store i64 %sub82, i64* %entry_remaining_bytes81, align 8, !dbg !1856
  %83 = load i64, i64* %bytes, align 8, !dbg !1857
  %84 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1858
  %entry_total83 = getelementptr inbounds %struct.tree, %struct.tree* %84, i32 0, i32 37, !dbg !1859
  %85 = load i64, i64* %entry_total83, align 8, !dbg !1860
  %add = add nsw i64 %85, %83, !dbg !1860
  store i64 %add, i64* %entry_total83, align 8, !dbg !1860
  br label %if.end84, !dbg !1861

if.end84:                                         ; preds = %if.end77, %if.end62
  %86 = load i64, i64* %buffbytes, align 8, !dbg !1862
  %cmp85 = icmp ugt i64 %86, 0, !dbg !1864
  br i1 %cmp85, label %if.then86, label %if.else97, !dbg !1865

if.then86:                                        ; preds = %if.end84
  %87 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1866
  %entry_fd87 = getelementptr inbounds %struct.tree, %struct.tree* %87, i32 0, i32 34, !dbg !1868
  %88 = load i32, i32* %entry_fd87, align 8, !dbg !1868
  %89 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1869
  %entry_buff88 = getelementptr inbounds %struct.tree, %struct.tree* %89, i32 0, i32 38, !dbg !1870
  %90 = load i8*, i8** %entry_buff88, align 8, !dbg !1870
  %91 = load i64, i64* %buffbytes, align 8, !dbg !1871
  %call89 = call i64 @read(i32 %88, i8* %90, i64 %91), !dbg !1872
  store i64 %call89, i64* %bytes, align 8, !dbg !1873
  %92 = load i64, i64* %bytes, align 8, !dbg !1874
  %cmp90 = icmp slt i64 %92, 0, !dbg !1876
  br i1 %cmp90, label %if.then91, label %if.end96, !dbg !1877

if.then91:                                        ; preds = %if.then86
  %93 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1878
  %archive92 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %93, i32 0, i32 0, !dbg !1880
  %call93 = call i32* @__errno_location() #1, !dbg !1881
  %94 = load i32, i32* %call93, align 4, !dbg !1881
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive92, i32 %94, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.23, i32 0, i32 0)), !dbg !1882
  store i32 -30, i32* %r, align 4, !dbg !1884
  %95 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !1885
  %archive94 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %95, i32 0, i32 0, !dbg !1886
  %state95 = getelementptr inbounds %struct.archive, %struct.archive* %archive94, i32 0, i32 1, !dbg !1887
  store i32 32768, i32* %state95, align 4, !dbg !1888
  br label %abort_read_data, !dbg !1889

if.end96:                                         ; preds = %if.then86
  br label %if.end98, !dbg !1890

if.else97:                                        ; preds = %if.end84
  store i64 0, i64* %bytes, align 8, !dbg !1891
  br label %if.end98

if.end98:                                         ; preds = %if.else97, %if.end96
  %96 = load i64, i64* %bytes, align 8, !dbg !1892
  %cmp99 = icmp eq i64 %96, 0, !dbg !1894
  br i1 %cmp99, label %land.lhs.true100, label %if.end104, !dbg !1895

land.lhs.true100:                                 ; preds = %if.end98
  %97 = load i32, i32* %empty_sparse_region, align 4, !dbg !1896
  %tobool101 = icmp ne i32 %97, 0, !dbg !1896
  br i1 %tobool101, label %if.end104, label %if.then102, !dbg !1898

if.then102:                                       ; preds = %land.lhs.true100
  %98 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1899
  %entry_eof103 = getelementptr inbounds %struct.tree, %struct.tree* %98, i32 0, i32 35, !dbg !1901
  store i32 1, i32* %entry_eof103, align 4, !dbg !1902
  store i32 1, i32* %r, align 4, !dbg !1903
  br label %abort_read_data, !dbg !1904

if.end104:                                        ; preds = %land.lhs.true100, %if.end98
  %99 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1905
  %entry_buff105 = getelementptr inbounds %struct.tree, %struct.tree* %99, i32 0, i32 38, !dbg !1906
  %100 = load i8*, i8** %entry_buff105, align 8, !dbg !1906
  %101 = load i8**, i8*** %buff.addr, align 8, !dbg !1907
  store i8* %100, i8** %101, align 8, !dbg !1908
  %102 = load i64, i64* %bytes, align 8, !dbg !1909
  %103 = load i64*, i64** %size.addr, align 8, !dbg !1910
  store i64 %102, i64* %103, align 8, !dbg !1911
  %104 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1912
  %entry_total106 = getelementptr inbounds %struct.tree, %struct.tree* %104, i32 0, i32 37, !dbg !1913
  %105 = load i64, i64* %entry_total106, align 8, !dbg !1913
  %106 = load i64*, i64** %offset.addr, align 8, !dbg !1914
  store i64 %105, i64* %106, align 8, !dbg !1915
  %107 = load i64, i64* %bytes, align 8, !dbg !1916
  %108 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1917
  %entry_total107 = getelementptr inbounds %struct.tree, %struct.tree* %108, i32 0, i32 37, !dbg !1918
  %109 = load i64, i64* %entry_total107, align 8, !dbg !1919
  %add108 = add nsw i64 %109, %107, !dbg !1919
  store i64 %add108, i64* %entry_total107, align 8, !dbg !1919
  %110 = load i64, i64* %bytes, align 8, !dbg !1920
  %111 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1921
  %entry_remaining_bytes109 = getelementptr inbounds %struct.tree, %struct.tree* %111, i32 0, i32 36, !dbg !1922
  %112 = load i64, i64* %entry_remaining_bytes109, align 8, !dbg !1923
  %sub110 = sub nsw i64 %112, %110, !dbg !1923
  store i64 %sub110, i64* %entry_remaining_bytes109, align 8, !dbg !1923
  %113 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1924
  %entry_remaining_bytes111 = getelementptr inbounds %struct.tree, %struct.tree* %113, i32 0, i32 36, !dbg !1926
  %114 = load i64, i64* %entry_remaining_bytes111, align 8, !dbg !1926
  %cmp112 = icmp eq i64 %114, 0, !dbg !1927
  br i1 %cmp112, label %if.then113, label %if.end119, !dbg !1928

if.then113:                                       ; preds = %if.end104
  %115 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1929
  %entry_fd114 = getelementptr inbounds %struct.tree, %struct.tree* %115, i32 0, i32 34, !dbg !1931
  %116 = load i32, i32* %entry_fd114, align 8, !dbg !1931
  %117 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1932
  %118 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1933
  %restore_time115 = getelementptr inbounds %struct.tree, %struct.tree* %118, i32 0, i32 21, !dbg !1934
  %call116 = call i32 @close_and_restore_time(i32 %116, %struct.tree* %117, %struct.restore_time* %restore_time115), !dbg !1935
  %119 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1936
  %entry_fd117 = getelementptr inbounds %struct.tree, %struct.tree* %119, i32 0, i32 34, !dbg !1937
  store i32 -1, i32* %entry_fd117, align 8, !dbg !1938
  %120 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1939
  %entry_eof118 = getelementptr inbounds %struct.tree, %struct.tree* %120, i32 0, i32 35, !dbg !1940
  store i32 1, i32* %entry_eof118, align 4, !dbg !1941
  br label %if.end119, !dbg !1942

if.end119:                                        ; preds = %if.then113, %if.end104
  %121 = load i64, i64* %bytes, align 8, !dbg !1943
  %122 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1944
  %current_sparse120 = getelementptr inbounds %struct.tree, %struct.tree* %122, i32 0, i32 23, !dbg !1945
  %123 = load %struct.entry_sparse*, %struct.entry_sparse** %current_sparse120, align 8, !dbg !1945
  %offset121 = getelementptr inbounds %struct.entry_sparse, %struct.entry_sparse* %123, i32 0, i32 1, !dbg !1946
  %124 = load i64, i64* %offset121, align 8, !dbg !1947
  %add122 = add nsw i64 %124, %121, !dbg !1947
  store i64 %add122, i64* %offset121, align 8, !dbg !1947
  %125 = load i64, i64* %bytes, align 8, !dbg !1948
  %126 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1949
  %current_sparse123 = getelementptr inbounds %struct.tree, %struct.tree* %126, i32 0, i32 23, !dbg !1950
  %127 = load %struct.entry_sparse*, %struct.entry_sparse** %current_sparse123, align 8, !dbg !1950
  %length124 = getelementptr inbounds %struct.entry_sparse, %struct.entry_sparse* %127, i32 0, i32 0, !dbg !1951
  %128 = load i64, i64* %length124, align 8, !dbg !1952
  %sub125 = sub nsw i64 %128, %125, !dbg !1952
  store i64 %sub125, i64* %length124, align 8, !dbg !1952
  %129 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1953
  %current_sparse126 = getelementptr inbounds %struct.tree, %struct.tree* %129, i32 0, i32 23, !dbg !1955
  %130 = load %struct.entry_sparse*, %struct.entry_sparse** %current_sparse126, align 8, !dbg !1955
  %length127 = getelementptr inbounds %struct.entry_sparse, %struct.entry_sparse* %130, i32 0, i32 0, !dbg !1956
  %131 = load i64, i64* %length127, align 8, !dbg !1956
  %cmp128 = icmp eq i64 %131, 0, !dbg !1957
  br i1 %cmp128, label %land.lhs.true129, label %if.end134, !dbg !1958

land.lhs.true129:                                 ; preds = %if.end119
  %132 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1959
  %entry_eof130 = getelementptr inbounds %struct.tree, %struct.tree* %132, i32 0, i32 35, !dbg !1961
  %133 = load i32, i32* %entry_eof130, align 4, !dbg !1961
  %tobool131 = icmp ne i32 %133, 0, !dbg !1959
  br i1 %tobool131, label %if.end134, label %if.then132, !dbg !1962

if.then132:                                       ; preds = %land.lhs.true129
  %134 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1963
  %current_sparse133 = getelementptr inbounds %struct.tree, %struct.tree* %134, i32 0, i32 23, !dbg !1964
  %135 = load %struct.entry_sparse*, %struct.entry_sparse** %current_sparse133, align 8, !dbg !1965
  %incdec.ptr = getelementptr inbounds %struct.entry_sparse, %struct.entry_sparse* %135, i32 1, !dbg !1965
  store %struct.entry_sparse* %incdec.ptr, %struct.entry_sparse** %current_sparse133, align 8, !dbg !1965
  br label %if.end134, !dbg !1963

if.end134:                                        ; preds = %if.then132, %land.lhs.true129, %if.end119
  store i32 0, i32* %retval, align 4, !dbg !1966
  br label %return, !dbg !1966

abort_read_data:                                  ; preds = %if.then102, %if.then91, %if.then72, %if.then45, %if.then34, %if.then2
  %136 = load i8**, i8*** %buff.addr, align 8, !dbg !1967
  store i8* null, i8** %136, align 8, !dbg !1968
  %137 = load i64*, i64** %size.addr, align 8, !dbg !1969
  store i64 0, i64* %137, align 8, !dbg !1970
  %138 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1971
  %entry_total135 = getelementptr inbounds %struct.tree, %struct.tree* %138, i32 0, i32 37, !dbg !1972
  %139 = load i64, i64* %entry_total135, align 8, !dbg !1972
  %140 = load i64*, i64** %offset.addr, align 8, !dbg !1973
  store i64 %139, i64* %140, align 8, !dbg !1974
  %141 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1975
  %entry_fd136 = getelementptr inbounds %struct.tree, %struct.tree* %141, i32 0, i32 34, !dbg !1977
  %142 = load i32, i32* %entry_fd136, align 8, !dbg !1977
  %cmp137 = icmp sge i32 %142, 0, !dbg !1978
  br i1 %cmp137, label %if.then138, label %if.end143, !dbg !1979

if.then138:                                       ; preds = %abort_read_data
  %143 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1980
  %entry_fd139 = getelementptr inbounds %struct.tree, %struct.tree* %143, i32 0, i32 34, !dbg !1982
  %144 = load i32, i32* %entry_fd139, align 8, !dbg !1982
  %145 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1983
  %146 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1984
  %restore_time140 = getelementptr inbounds %struct.tree, %struct.tree* %146, i32 0, i32 21, !dbg !1985
  %call141 = call i32 @close_and_restore_time(i32 %144, %struct.tree* %145, %struct.restore_time* %restore_time140), !dbg !1986
  %147 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !1987
  %entry_fd142 = getelementptr inbounds %struct.tree, %struct.tree* %147, i32 0, i32 34, !dbg !1988
  store i32 -1, i32* %entry_fd142, align 8, !dbg !1989
  br label %if.end143, !dbg !1990

if.end143:                                        ; preds = %if.then138, %abort_read_data
  %148 = load i32, i32* %r, align 4, !dbg !1991
  store i32 %148, i32* %retval, align 4, !dbg !1992
  br label %return, !dbg !1992

return:                                           ; preds = %if.end143, %if.end134, %if.then
  %149 = load i32, i32* %retval, align 4, !dbg !1993
  ret i32 %149, !dbg !1993
}

; Function Attrs: nounwind uwtable
define internal i32 @_archive_read_next_header(%struct.archive* %_a, %struct.archive_entry** %entryp) #0 !dbg !394 {
entry:
  %_a.addr = alloca %struct.archive*, align 8
  %entryp.addr = alloca %struct.archive_entry**, align 8
  %ret = alloca i32, align 4
  %a = alloca %struct.archive_read_disk*, align 8
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !1994, metadata !460), !dbg !1995
  store %struct.archive_entry** %entryp, %struct.archive_entry*** %entryp.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry*** %entryp.addr, metadata !1996, metadata !460), !dbg !1997
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !1998, metadata !460), !dbg !1999
  call void @llvm.dbg.declare(metadata %struct.archive_read_disk** %a, metadata !2000, metadata !460), !dbg !2001
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !2002
  %1 = bitcast %struct.archive* %0 to %struct.archive_read_disk*, !dbg !2003
  store %struct.archive_read_disk* %1, %struct.archive_read_disk** %a, align 8, !dbg !2001
  %2 = load %struct.archive_entry**, %struct.archive_entry*** %entryp.addr, align 8, !dbg !2004
  store %struct.archive_entry* null, %struct.archive_entry** %2, align 8, !dbg !2005
  %3 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !2006
  %4 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !2007
  %entry1 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %4, i32 0, i32 1, !dbg !2008
  %5 = load %struct.archive_entry*, %struct.archive_entry** %entry1, align 8, !dbg !2008
  %call = call i32 @_archive_read_next_header2(%struct.archive* %3, %struct.archive_entry* %5), !dbg !2009
  store i32 %call, i32* %ret, align 4, !dbg !2010
  %6 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !2011
  %entry2 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %6, i32 0, i32 1, !dbg !2012
  %7 = load %struct.archive_entry*, %struct.archive_entry** %entry2, align 8, !dbg !2012
  %8 = load %struct.archive_entry**, %struct.archive_entry*** %entryp.addr, align 8, !dbg !2013
  store %struct.archive_entry* %7, %struct.archive_entry** %8, align 8, !dbg !2014
  %9 = load i32, i32* %ret, align 4, !dbg !2015
  ret i32 %9, !dbg !2016
}

; Function Attrs: nounwind uwtable
define internal i32 @_archive_read_next_header2(%struct.archive* %_a, %struct.archive_entry* %entry1) #0 !dbg !395 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %a = alloca %struct.archive_read_disk*, align 8
  %t = alloca %struct.tree*, align 8
  %r = alloca i32, align 4
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !2017, metadata !460), !dbg !2018
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2019, metadata !460), !dbg !2020
  call void @llvm.dbg.declare(metadata %struct.archive_read_disk** %a, metadata !2021, metadata !460), !dbg !2022
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !2023
  %1 = bitcast %struct.archive* %0 to %struct.archive_read_disk*, !dbg !2024
  store %struct.archive_read_disk* %1, %struct.archive_read_disk** %a, align 8, !dbg !2022
  call void @llvm.dbg.declare(metadata %struct.tree** %t, metadata !2025, metadata !460), !dbg !2026
  call void @llvm.dbg.declare(metadata i32* %r, metadata !2027, metadata !460), !dbg !2028
  br label %do.body, !dbg !2029

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !2030, metadata !460), !dbg !2032
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !2033
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 195932357, i32 6, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.25, i32 0, i32 0)), !dbg !2033
  store i32 %call, i32* %magic_test, align 4, !dbg !2033
  %3 = load i32, i32* %magic_test, align 4, !dbg !2033
  %cmp = icmp eq i32 %3, -30, !dbg !2033
  br i1 %cmp, label %if.then, label %if.end, !dbg !2033

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !2035
  br label %return, !dbg !2035

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !2038

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !2040
  %tree = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %4, i32 0, i32 4, !dbg !2041
  %5 = load %struct.tree*, %struct.tree** %tree, align 8, !dbg !2041
  store %struct.tree* %5, %struct.tree** %t, align 8, !dbg !2042
  %6 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !2043
  %entry_fd = getelementptr inbounds %struct.tree, %struct.tree* %6, i32 0, i32 34, !dbg !2045
  %7 = load i32, i32* %entry_fd, align 8, !dbg !2045
  %cmp2 = icmp sge i32 %7, 0, !dbg !2046
  br i1 %cmp2, label %if.then3, label %if.end7, !dbg !2047

if.then3:                                         ; preds = %do.end
  %8 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !2048
  %entry_fd4 = getelementptr inbounds %struct.tree, %struct.tree* %8, i32 0, i32 34, !dbg !2050
  %9 = load i32, i32* %entry_fd4, align 8, !dbg !2050
  %10 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !2051
  %11 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !2052
  %restore_time = getelementptr inbounds %struct.tree, %struct.tree* %11, i32 0, i32 21, !dbg !2053
  %call5 = call i32 @close_and_restore_time(i32 %9, %struct.tree* %10, %struct.restore_time* %restore_time), !dbg !2054
  %12 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !2055
  %entry_fd6 = getelementptr inbounds %struct.tree, %struct.tree* %12, i32 0, i32 34, !dbg !2056
  store i32 -1, i32* %entry_fd6, align 8, !dbg !2057
  br label %if.end7, !dbg !2058

if.end7:                                          ; preds = %if.then3, %do.end
  br label %for.cond, !dbg !2059

for.cond:                                         ; preds = %if.then17, %if.end7
  %13 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !2060
  %14 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !2064
  %15 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2065
  %call8 = call i32 @next_entry(%struct.archive_read_disk* %13, %struct.tree* %14, %struct.archive_entry* %15), !dbg !2066
  store i32 %call8, i32* %r, align 4, !dbg !2067
  %16 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !2068
  %entry_fd9 = getelementptr inbounds %struct.tree, %struct.tree* %16, i32 0, i32 34, !dbg !2070
  %17 = load i32, i32* %entry_fd9, align 8, !dbg !2070
  %cmp10 = icmp sge i32 %17, 0, !dbg !2071
  br i1 %cmp10, label %if.then11, label %if.end15, !dbg !2072

if.then11:                                        ; preds = %for.cond
  %18 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !2073
  %entry_fd12 = getelementptr inbounds %struct.tree, %struct.tree* %18, i32 0, i32 34, !dbg !2075
  %19 = load i32, i32* %entry_fd12, align 8, !dbg !2075
  %call13 = call i32 @close(i32 %19), !dbg !2076
  %20 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !2077
  %entry_fd14 = getelementptr inbounds %struct.tree, %struct.tree* %20, i32 0, i32 34, !dbg !2078
  store i32 -1, i32* %entry_fd14, align 8, !dbg !2079
  br label %if.end15, !dbg !2080

if.end15:                                         ; preds = %if.then11, %for.cond
  %21 = load i32, i32* %r, align 4, !dbg !2081
  %cmp16 = icmp eq i32 %21, -10, !dbg !2083
  br i1 %cmp16, label %if.then17, label %if.end19, !dbg !2084

if.then17:                                        ; preds = %if.end15
  %22 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2085
  %call18 = call %struct.archive_entry* @archive_entry_clear(%struct.archive_entry* %22), !dbg !2087
  br label %for.cond, !dbg !2088

if.end19:                                         ; preds = %if.end15
  br label %for.end, !dbg !2089

for.end:                                          ; preds = %if.end19
  %23 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !2090
  %call20 = call i32 @tree_enter_initial_dir(%struct.tree* %23), !dbg !2091
  %24 = load i32, i32* %r, align 4, !dbg !2092
  switch i32 %24, label %sw.epilog [
    i32 1, label %sw.bb
    i32 0, label %sw.bb21
    i32 -20, label %sw.bb21
    i32 -10, label %sw.bb40
    i32 -30, label %sw.bb41
  ], !dbg !2093

sw.bb:                                            ; preds = %for.end
  %25 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !2094
  %archive = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %25, i32 0, i32 0, !dbg !2096
  %state = getelementptr inbounds %struct.archive, %struct.archive* %archive, i32 0, i32 1, !dbg !2097
  store i32 16, i32* %state, align 4, !dbg !2098
  br label %sw.epilog, !dbg !2099

sw.bb21:                                          ; preds = %for.end, %for.end
  %26 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2100
  %27 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !2101
  %call22 = call i8* @tree_current_path(%struct.tree* %27), !dbg !2102
  call void @archive_entry_copy_sourcepath(%struct.archive_entry* %26, i8* %call22), !dbg !2103
  %28 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !2105
  %entry_total = getelementptr inbounds %struct.tree, %struct.tree* %28, i32 0, i32 37, !dbg !2106
  store i64 0, i64* %entry_total, align 8, !dbg !2107
  %29 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2108
  %call23 = call i32 @archive_entry_filetype(%struct.archive_entry* %29), !dbg !2110
  %cmp24 = icmp eq i32 %call23, 32768, !dbg !2111
  br i1 %cmp24, label %if.then25, label %if.else, !dbg !2112

if.then25:                                        ; preds = %sw.bb21
  %30 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2113
  %call26 = call i32 @archive_entry_nlink(%struct.archive_entry* %30), !dbg !2115
  %31 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !2116
  %nlink = getelementptr inbounds %struct.tree, %struct.tree* %31, i32 0, i32 20, !dbg !2117
  store i32 %call26, i32* %nlink, align 4, !dbg !2118
  %32 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2119
  %call27 = call i64 @archive_entry_size(%struct.archive_entry* %32), !dbg !2120
  %33 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !2121
  %entry_remaining_bytes = getelementptr inbounds %struct.tree, %struct.tree* %33, i32 0, i32 36, !dbg !2122
  store i64 %call27, i64* %entry_remaining_bytes, align 8, !dbg !2123
  %34 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !2124
  %entry_remaining_bytes28 = getelementptr inbounds %struct.tree, %struct.tree* %34, i32 0, i32 36, !dbg !2125
  %35 = load i64, i64* %entry_remaining_bytes28, align 8, !dbg !2125
  %cmp29 = icmp eq i64 %35, 0, !dbg !2126
  %cond = select i1 %cmp29, i32 1, i32 0, !dbg !2127
  %36 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !2128
  %entry_eof = getelementptr inbounds %struct.tree, %struct.tree* %36, i32 0, i32 35, !dbg !2129
  store i32 %cond, i32* %entry_eof, align 4, !dbg !2130
  %37 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !2131
  %entry_eof30 = getelementptr inbounds %struct.tree, %struct.tree* %37, i32 0, i32 35, !dbg !2133
  %38 = load i32, i32* %entry_eof30, align 4, !dbg !2133
  %tobool = icmp ne i32 %38, 0, !dbg !2131
  br i1 %tobool, label %if.end34, label %land.lhs.true, !dbg !2134

land.lhs.true:                                    ; preds = %if.then25
  %39 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !2135
  %40 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2136
  %call31 = call i32 @setup_sparse(%struct.archive_read_disk* %39, %struct.archive_entry* %40), !dbg !2137
  %cmp32 = icmp ne i32 %call31, 0, !dbg !2138
  br i1 %cmp32, label %if.then33, label %if.end34, !dbg !2139

if.then33:                                        ; preds = %land.lhs.true
  store i32 -30, i32* %retval, align 4, !dbg !2141
  br label %return, !dbg !2141

if.end34:                                         ; preds = %land.lhs.true, %if.then25
  br label %if.end37, !dbg !2142

if.else:                                          ; preds = %sw.bb21
  %41 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !2143
  %entry_remaining_bytes35 = getelementptr inbounds %struct.tree, %struct.tree* %41, i32 0, i32 36, !dbg !2145
  store i64 0, i64* %entry_remaining_bytes35, align 8, !dbg !2146
  %42 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !2147
  %entry_eof36 = getelementptr inbounds %struct.tree, %struct.tree* %42, i32 0, i32 35, !dbg !2148
  store i32 1, i32* %entry_eof36, align 4, !dbg !2149
  br label %if.end37

if.end37:                                         ; preds = %if.else, %if.end34
  %43 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !2150
  %archive38 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %43, i32 0, i32 0, !dbg !2151
  %state39 = getelementptr inbounds %struct.archive, %struct.archive* %archive38, i32 0, i32 1, !dbg !2152
  store i32 4, i32* %state39, align 4, !dbg !2153
  br label %sw.epilog, !dbg !2154

sw.bb40:                                          ; preds = %for.end
  br label %sw.epilog, !dbg !2155

sw.bb41:                                          ; preds = %for.end
  %44 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !2156
  %archive42 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %44, i32 0, i32 0, !dbg !2157
  %state43 = getelementptr inbounds %struct.archive, %struct.archive* %archive42, i32 0, i32 1, !dbg !2158
  store i32 32768, i32* %state43, align 4, !dbg !2159
  br label %sw.epilog, !dbg !2160

sw.epilog:                                        ; preds = %for.end, %sw.bb41, %sw.bb40, %if.end37, %sw.bb
  %45 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a, align 8, !dbg !2161
  %archive44 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %45, i32 0, i32 0, !dbg !2162
  call void @__archive_reset_read_data(%struct.archive* %archive44), !dbg !2163
  %46 = load i32, i32* %r, align 4, !dbg !2164
  store i32 %46, i32* %retval, align 4, !dbg !2165
  br label %return, !dbg !2165

return:                                           ; preds = %sw.epilog, %if.then33, %if.then
  %47 = load i32, i32* %retval, align 4, !dbg !2166
  ret i32 %47, !dbg !2166
}

; Function Attrs: nounwind uwtable
define internal void @tree_free(%struct.tree* %t) #0 !dbg !375 {
entry:
  %t.addr = alloca %struct.tree*, align 8
  %i = alloca i32, align 4
  store %struct.tree* %t, %struct.tree** %t.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tree** %t.addr, metadata !2167, metadata !460), !dbg !2168
  call void @llvm.dbg.declare(metadata i32* %i, metadata !2169, metadata !460), !dbg !2170
  %0 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2171
  %cmp = icmp eq %struct.tree* %0, null, !dbg !2173
  br i1 %cmp, label %if.then, label %if.end, !dbg !2174

if.then:                                          ; preds = %entry
  br label %return, !dbg !2175

if.end:                                           ; preds = %entry
  %1 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2176
  %path = getelementptr inbounds %struct.tree, %struct.tree* %1, i32 0, i32 9, !dbg !2177
  call void @archive_string_free(%struct.archive_string* %path), !dbg !2178
  %2 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2179
  %dirent = getelementptr inbounds %struct.tree, %struct.tree* %2, i32 0, i32 4, !dbg !2180
  %3 = load %struct.dirent*, %struct.dirent** %dirent, align 8, !dbg !2180
  %4 = bitcast %struct.dirent* %3 to i8*, !dbg !2179
  call void @free(i8* %4) #6, !dbg !2181
  %5 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2182
  %sparse_list = getelementptr inbounds %struct.tree, %struct.tree* %5, i32 0, i32 22, !dbg !2183
  %6 = load %struct.entry_sparse*, %struct.entry_sparse** %sparse_list, align 8, !dbg !2183
  %7 = bitcast %struct.entry_sparse* %6 to i8*, !dbg !2182
  call void @free(i8* %7) #6, !dbg !2184
  store i32 0, i32* %i, align 4, !dbg !2185
  br label %for.cond, !dbg !2187

for.cond:                                         ; preds = %for.inc, %if.end
  %8 = load i32, i32* %i, align 4, !dbg !2188
  %9 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2191
  %max_filesystem_id = getelementptr inbounds %struct.tree, %struct.tree* %9, i32 0, i32 32, !dbg !2192
  %10 = load i32, i32* %max_filesystem_id, align 8, !dbg !2192
  %cmp1 = icmp slt i32 %8, %10, !dbg !2193
  br i1 %cmp1, label %for.body, label %for.end, !dbg !2194

for.body:                                         ; preds = %for.cond
  %11 = load i32, i32* %i, align 4, !dbg !2195
  %idxprom = sext i32 %11 to i64, !dbg !2196
  %12 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2196
  %filesystem_table = getelementptr inbounds %struct.tree, %struct.tree* %12, i32 0, i32 29, !dbg !2197
  %13 = load %struct.filesystem*, %struct.filesystem** %filesystem_table, align 8, !dbg !2197
  %arrayidx = getelementptr inbounds %struct.filesystem, %struct.filesystem* %13, i64 %idxprom, !dbg !2196
  %allocation_ptr = getelementptr inbounds %struct.filesystem, %struct.filesystem* %arrayidx, i32 0, i32 9, !dbg !2198
  %14 = load i8*, i8** %allocation_ptr, align 8, !dbg !2198
  call void @free(i8* %14) #6, !dbg !2199
  br label %for.inc, !dbg !2199

for.inc:                                          ; preds = %for.body
  %15 = load i32, i32* %i, align 4, !dbg !2200
  %inc = add nsw i32 %15, 1, !dbg !2200
  store i32 %inc, i32* %i, align 4, !dbg !2200
  br label %for.cond, !dbg !2202

for.end:                                          ; preds = %for.cond
  %16 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2203
  %filesystem_table2 = getelementptr inbounds %struct.tree, %struct.tree* %16, i32 0, i32 29, !dbg !2204
  %17 = load %struct.filesystem*, %struct.filesystem** %filesystem_table2, align 8, !dbg !2204
  %18 = bitcast %struct.filesystem* %17 to i8*, !dbg !2203
  call void @free(i8* %18) #6, !dbg !2205
  %19 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2206
  %20 = bitcast %struct.tree* %19 to i8*, !dbg !2206
  call void @free(i8* %20) #6, !dbg !2207
  br label %return, !dbg !2208

return:                                           ; preds = %for.end, %if.then
  ret void, !dbg !2209
}

declare void @archive_entry_free(%struct.archive_entry*) #2

declare i32 @__archive_clean(%struct.archive*) #2

; Function Attrs: nounwind
declare void @free(i8*) #3

; Function Attrs: nounwind uwtable
define internal void @tree_close(%struct.tree* %t) #0 !dbg !379 {
entry:
  %t.addr = alloca %struct.tree*, align 8
  store %struct.tree* %t, %struct.tree** %t.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tree** %t.addr, metadata !2211, metadata !460), !dbg !2212
  %0 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2213
  %cmp = icmp eq %struct.tree* %0, null, !dbg !2215
  br i1 %cmp, label %if.then, label %if.end, !dbg !2216

if.then:                                          ; preds = %entry
  br label %if.end29, !dbg !2217

if.end:                                           ; preds = %entry
  %1 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2218
  %entry_fd = getelementptr inbounds %struct.tree, %struct.tree* %1, i32 0, i32 34, !dbg !2220
  %2 = load i32, i32* %entry_fd, align 8, !dbg !2220
  %cmp1 = icmp sge i32 %2, 0, !dbg !2221
  br i1 %cmp1, label %if.then2, label %if.end5, !dbg !2222

if.then2:                                         ; preds = %if.end
  %3 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2223
  %entry_fd3 = getelementptr inbounds %struct.tree, %struct.tree* %3, i32 0, i32 34, !dbg !2225
  %4 = load i32, i32* %entry_fd3, align 8, !dbg !2225
  %5 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2226
  %6 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2227
  %restore_time = getelementptr inbounds %struct.tree, %struct.tree* %6, i32 0, i32 21, !dbg !2228
  %call = call i32 @close_and_restore_time(i32 %4, %struct.tree* %5, %struct.restore_time* %restore_time), !dbg !2229
  %7 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2230
  %entry_fd4 = getelementptr inbounds %struct.tree, %struct.tree* %7, i32 0, i32 34, !dbg !2231
  store i32 -1, i32* %entry_fd4, align 8, !dbg !2232
  br label %if.end5, !dbg !2233

if.end5:                                          ; preds = %if.then2, %if.end
  %8 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2234
  %d = getelementptr inbounds %struct.tree, %struct.tree* %8, i32 0, i32 2, !dbg !2236
  %9 = load %struct.__dirstream*, %struct.__dirstream** %d, align 8, !dbg !2236
  %cmp6 = icmp ne %struct.__dirstream* %9, null, !dbg !2237
  br i1 %cmp6, label %if.then7, label %if.end11, !dbg !2238

if.then7:                                         ; preds = %if.end5
  %10 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2239
  %d8 = getelementptr inbounds %struct.tree, %struct.tree* %10, i32 0, i32 2, !dbg !2241
  %11 = load %struct.__dirstream*, %struct.__dirstream** %d8, align 8, !dbg !2241
  %call9 = call i32 @closedir(%struct.__dirstream* %11), !dbg !2242
  %12 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2243
  %d10 = getelementptr inbounds %struct.tree, %struct.tree* %12, i32 0, i32 2, !dbg !2244
  store %struct.__dirstream* null, %struct.__dirstream** %d10, align 8, !dbg !2245
  br label %if.end11, !dbg !2246

if.end11:                                         ; preds = %if.then7, %if.end5
  br label %while.cond, !dbg !2247

while.cond:                                       ; preds = %if.end17, %if.end11
  %13 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2248
  %stack = getelementptr inbounds %struct.tree, %struct.tree* %13, i32 0, i32 0, !dbg !2250
  %14 = load %struct.tree_entry*, %struct.tree_entry** %stack, align 8, !dbg !2250
  %cmp12 = icmp ne %struct.tree_entry* %14, null, !dbg !2251
  br i1 %cmp12, label %while.body, label %while.end, !dbg !2252

while.body:                                       ; preds = %while.cond
  %15 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2253
  %stack13 = getelementptr inbounds %struct.tree, %struct.tree* %15, i32 0, i32 0, !dbg !2256
  %16 = load %struct.tree_entry*, %struct.tree_entry** %stack13, align 8, !dbg !2256
  %flags = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %16, i32 0, i32 7, !dbg !2257
  %17 = load i32, i32* %flags, align 8, !dbg !2257
  %and = and i32 %17, 2, !dbg !2258
  %tobool = icmp ne i32 %and, 0, !dbg !2258
  br i1 %tobool, label %if.then14, label %if.end17, !dbg !2259

if.then14:                                        ; preds = %while.body
  %18 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2260
  %stack15 = getelementptr inbounds %struct.tree, %struct.tree* %18, i32 0, i32 0, !dbg !2261
  %19 = load %struct.tree_entry*, %struct.tree_entry** %stack15, align 8, !dbg !2261
  %symlink_parent_fd = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %19, i32 0, i32 9, !dbg !2262
  %20 = load i32, i32* %symlink_parent_fd, align 8, !dbg !2262
  %call16 = call i32 @close(i32 %20), !dbg !2263
  br label %if.end17, !dbg !2263

if.end17:                                         ; preds = %if.then14, %while.body
  %21 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2264
  call void @tree_pop(%struct.tree* %21), !dbg !2265
  br label %while.cond, !dbg !2266

while.end:                                        ; preds = %while.cond
  %22 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2268
  %working_dir_fd = getelementptr inbounds %struct.tree, %struct.tree* %22, i32 0, i32 16, !dbg !2270
  %23 = load i32, i32* %working_dir_fd, align 8, !dbg !2270
  %cmp18 = icmp sge i32 %23, 0, !dbg !2271
  br i1 %cmp18, label %if.then19, label %if.end23, !dbg !2272

if.then19:                                        ; preds = %while.end
  %24 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2273
  %working_dir_fd20 = getelementptr inbounds %struct.tree, %struct.tree* %24, i32 0, i32 16, !dbg !2275
  %25 = load i32, i32* %working_dir_fd20, align 8, !dbg !2275
  %call21 = call i32 @close(i32 %25), !dbg !2276
  %26 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2277
  %working_dir_fd22 = getelementptr inbounds %struct.tree, %struct.tree* %26, i32 0, i32 16, !dbg !2278
  store i32 -1, i32* %working_dir_fd22, align 8, !dbg !2279
  br label %if.end23, !dbg !2280

if.end23:                                         ; preds = %if.then19, %while.end
  %27 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2281
  %initial_dir_fd = getelementptr inbounds %struct.tree, %struct.tree* %27, i32 0, i32 15, !dbg !2283
  %28 = load i32, i32* %initial_dir_fd, align 4, !dbg !2283
  %cmp24 = icmp sge i32 %28, 0, !dbg !2284
  br i1 %cmp24, label %if.then25, label %if.end29, !dbg !2285

if.then25:                                        ; preds = %if.end23
  %29 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2286
  %initial_dir_fd26 = getelementptr inbounds %struct.tree, %struct.tree* %29, i32 0, i32 15, !dbg !2288
  %30 = load i32, i32* %initial_dir_fd26, align 4, !dbg !2288
  %call27 = call i32 @close(i32 %30), !dbg !2289
  %31 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2290
  %initial_dir_fd28 = getelementptr inbounds %struct.tree, %struct.tree* %31, i32 0, i32 15, !dbg !2291
  store i32 -1, i32* %initial_dir_fd28, align 4, !dbg !2292
  br label %if.end29, !dbg !2293

if.end29:                                         ; preds = %if.then, %if.then25, %if.end23
  ret void, !dbg !2294
}

; Function Attrs: nounwind uwtable
define internal i32 @close_and_restore_time(i32 %fd, %struct.tree* %t, %struct.restore_time* %rt) #0 !dbg !380 {
entry:
  %retval = alloca i32, align 4
  %fd.addr = alloca i32, align 4
  %t.addr = alloca %struct.tree*, align 8
  %rt.addr = alloca %struct.restore_time*, align 8
  %timespecs = alloca [2 x %struct.timespec], align 16
  %times = alloca [2 x %struct.timeval], align 16
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !2295, metadata !460), !dbg !2296
  store %struct.tree* %t, %struct.tree** %t.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tree** %t.addr, metadata !2297, metadata !460), !dbg !2298
  store %struct.restore_time* %rt, %struct.restore_time** %rt.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.restore_time** %rt.addr, metadata !2299, metadata !460), !dbg !2300
  call void @llvm.dbg.declare(metadata [2 x %struct.timespec]* %timespecs, metadata !2301, metadata !460), !dbg !2305
  call void @llvm.dbg.declare(metadata [2 x %struct.timeval]* %times, metadata !2306, metadata !460), !dbg !2314
  %0 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2315
  %flags = getelementptr inbounds %struct.tree, %struct.tree* %0, i32 0, i32 6, !dbg !2317
  %1 = load i32, i32* %flags, align 8, !dbg !2317
  %and = and i32 %1, 128, !dbg !2318
  %cmp = icmp eq i32 %and, 0, !dbg !2319
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !2320

lor.lhs.false:                                    ; preds = %entry
  %2 = load %struct.restore_time*, %struct.restore_time** %rt.addr, align 8, !dbg !2321
  %noatime = getelementptr inbounds %struct.restore_time, %struct.restore_time* %2, i32 0, i32 6, !dbg !2323
  %3 = load i32, i32* %noatime, align 4, !dbg !2323
  %tobool = icmp ne i32 %3, 0, !dbg !2321
  br i1 %tobool, label %if.then, label %if.end, !dbg !2324

if.then:                                          ; preds = %lor.lhs.false, %entry
  %4 = load i32, i32* %fd.addr, align 4, !dbg !2325
  %cmp1 = icmp sge i32 %4, 0, !dbg !2328
  br i1 %cmp1, label %if.then2, label %if.else, !dbg !2329

if.then2:                                         ; preds = %if.then
  %5 = load i32, i32* %fd.addr, align 4, !dbg !2330
  %call = call i32 @close(i32 %5), !dbg !2331
  store i32 %call, i32* %retval, align 4, !dbg !2332
  br label %return, !dbg !2332

if.else:                                          ; preds = %if.then
  store i32 0, i32* %retval, align 4, !dbg !2333
  br label %return, !dbg !2333

if.end:                                           ; preds = %lor.lhs.false
  %6 = load %struct.restore_time*, %struct.restore_time** %rt.addr, align 8, !dbg !2334
  %mtime = getelementptr inbounds %struct.restore_time, %struct.restore_time* %6, i32 0, i32 1, !dbg !2335
  %7 = load i64, i64* %mtime, align 8, !dbg !2335
  %arrayidx = getelementptr inbounds [2 x %struct.timespec], [2 x %struct.timespec]* %timespecs, i64 0, i64 1, !dbg !2336
  %tv_sec = getelementptr inbounds %struct.timespec, %struct.timespec* %arrayidx, i32 0, i32 0, !dbg !2337
  store i64 %7, i64* %tv_sec, align 16, !dbg !2338
  %8 = load %struct.restore_time*, %struct.restore_time** %rt.addr, align 8, !dbg !2339
  %mtime_nsec = getelementptr inbounds %struct.restore_time, %struct.restore_time* %8, i32 0, i32 2, !dbg !2340
  %9 = load i64, i64* %mtime_nsec, align 8, !dbg !2340
  %arrayidx3 = getelementptr inbounds [2 x %struct.timespec], [2 x %struct.timespec]* %timespecs, i64 0, i64 1, !dbg !2341
  %tv_nsec = getelementptr inbounds %struct.timespec, %struct.timespec* %arrayidx3, i32 0, i32 1, !dbg !2342
  store i64 %9, i64* %tv_nsec, align 8, !dbg !2343
  %10 = load %struct.restore_time*, %struct.restore_time** %rt.addr, align 8, !dbg !2344
  %atime = getelementptr inbounds %struct.restore_time, %struct.restore_time* %10, i32 0, i32 3, !dbg !2345
  %11 = load i64, i64* %atime, align 8, !dbg !2345
  %arrayidx4 = getelementptr inbounds [2 x %struct.timespec], [2 x %struct.timespec]* %timespecs, i64 0, i64 0, !dbg !2346
  %tv_sec5 = getelementptr inbounds %struct.timespec, %struct.timespec* %arrayidx4, i32 0, i32 0, !dbg !2347
  store i64 %11, i64* %tv_sec5, align 16, !dbg !2348
  %12 = load %struct.restore_time*, %struct.restore_time** %rt.addr, align 8, !dbg !2349
  %atime_nsec = getelementptr inbounds %struct.restore_time, %struct.restore_time* %12, i32 0, i32 4, !dbg !2350
  %13 = load i64, i64* %atime_nsec, align 8, !dbg !2350
  %arrayidx6 = getelementptr inbounds [2 x %struct.timespec], [2 x %struct.timespec]* %timespecs, i64 0, i64 0, !dbg !2351
  %tv_nsec7 = getelementptr inbounds %struct.timespec, %struct.timespec* %arrayidx6, i32 0, i32 1, !dbg !2352
  store i64 %13, i64* %tv_nsec7, align 8, !dbg !2353
  %14 = load i32, i32* %fd.addr, align 4, !dbg !2354
  %arraydecay = getelementptr inbounds [2 x %struct.timespec], [2 x %struct.timespec]* %timespecs, i32 0, i32 0, !dbg !2356
  %call8 = call i32 @futimens(i32 %14, %struct.timespec* %arraydecay) #6, !dbg !2357
  %cmp9 = icmp eq i32 %call8, 0, !dbg !2358
  br i1 %cmp9, label %if.then10, label %if.end12, !dbg !2359

if.then10:                                        ; preds = %if.end
  %15 = load i32, i32* %fd.addr, align 4, !dbg !2360
  %call11 = call i32 @close(i32 %15), !dbg !2361
  store i32 %call11, i32* %retval, align 4, !dbg !2362
  br label %return, !dbg !2362

if.end12:                                         ; preds = %if.end
  %16 = load %struct.restore_time*, %struct.restore_time** %rt.addr, align 8, !dbg !2363
  %mtime13 = getelementptr inbounds %struct.restore_time, %struct.restore_time* %16, i32 0, i32 1, !dbg !2364
  %17 = load i64, i64* %mtime13, align 8, !dbg !2364
  %arrayidx14 = getelementptr inbounds [2 x %struct.timeval], [2 x %struct.timeval]* %times, i64 0, i64 1, !dbg !2365
  %tv_sec15 = getelementptr inbounds %struct.timeval, %struct.timeval* %arrayidx14, i32 0, i32 0, !dbg !2366
  store i64 %17, i64* %tv_sec15, align 16, !dbg !2367
  %18 = load %struct.restore_time*, %struct.restore_time** %rt.addr, align 8, !dbg !2368
  %mtime_nsec16 = getelementptr inbounds %struct.restore_time, %struct.restore_time* %18, i32 0, i32 2, !dbg !2369
  %19 = load i64, i64* %mtime_nsec16, align 8, !dbg !2369
  %div = sdiv i64 %19, 1000, !dbg !2370
  %arrayidx17 = getelementptr inbounds [2 x %struct.timeval], [2 x %struct.timeval]* %times, i64 0, i64 1, !dbg !2371
  %tv_usec = getelementptr inbounds %struct.timeval, %struct.timeval* %arrayidx17, i32 0, i32 1, !dbg !2372
  store i64 %div, i64* %tv_usec, align 8, !dbg !2373
  %20 = load %struct.restore_time*, %struct.restore_time** %rt.addr, align 8, !dbg !2374
  %atime18 = getelementptr inbounds %struct.restore_time, %struct.restore_time* %20, i32 0, i32 3, !dbg !2375
  %21 = load i64, i64* %atime18, align 8, !dbg !2375
  %arrayidx19 = getelementptr inbounds [2 x %struct.timeval], [2 x %struct.timeval]* %times, i64 0, i64 0, !dbg !2376
  %tv_sec20 = getelementptr inbounds %struct.timeval, %struct.timeval* %arrayidx19, i32 0, i32 0, !dbg !2377
  store i64 %21, i64* %tv_sec20, align 16, !dbg !2378
  %22 = load %struct.restore_time*, %struct.restore_time** %rt.addr, align 8, !dbg !2379
  %atime_nsec21 = getelementptr inbounds %struct.restore_time, %struct.restore_time* %22, i32 0, i32 4, !dbg !2380
  %23 = load i64, i64* %atime_nsec21, align 8, !dbg !2380
  %div22 = sdiv i64 %23, 1000, !dbg !2381
  %arrayidx23 = getelementptr inbounds [2 x %struct.timeval], [2 x %struct.timeval]* %times, i64 0, i64 0, !dbg !2382
  %tv_usec24 = getelementptr inbounds %struct.timeval, %struct.timeval* %arrayidx23, i32 0, i32 1, !dbg !2383
  store i64 %div22, i64* %tv_usec24, align 8, !dbg !2384
  %24 = load i32, i32* %fd.addr, align 4, !dbg !2385
  %call25 = call i32 @close(i32 %24), !dbg !2386
  %25 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2387
  %call26 = call i32 @tree_current_dir_fd(%struct.tree* %25), !dbg !2389
  %26 = load %struct.restore_time*, %struct.restore_time** %rt.addr, align 8, !dbg !2390
  %name = getelementptr inbounds %struct.restore_time, %struct.restore_time* %26, i32 0, i32 0, !dbg !2391
  %27 = load i8*, i8** %name, align 8, !dbg !2391
  %arraydecay27 = getelementptr inbounds [2 x %struct.timeval], [2 x %struct.timeval]* %times, i32 0, i32 0, !dbg !2392
  %call28 = call i32 @futimesat(i32 %call26, i8* %27, %struct.timeval* %arraydecay27) #6, !dbg !2393
  %cmp29 = icmp eq i32 %call28, 0, !dbg !2395
  br i1 %cmp29, label %if.then30, label %if.end31, !dbg !2396

if.then30:                                        ; preds = %if.end12
  store i32 0, i32* %retval, align 4, !dbg !2397
  br label %return, !dbg !2397

if.end31:                                         ; preds = %if.end12
  %28 = load %struct.restore_time*, %struct.restore_time** %rt.addr, align 8, !dbg !2398
  %name32 = getelementptr inbounds %struct.restore_time, %struct.restore_time* %28, i32 0, i32 0, !dbg !2400
  %29 = load i8*, i8** %name32, align 8, !dbg !2400
  %arraydecay33 = getelementptr inbounds [2 x %struct.timeval], [2 x %struct.timeval]* %times, i32 0, i32 0, !dbg !2401
  %call34 = call i32 @lutimes(i8* %29, %struct.timeval* %arraydecay33) #6, !dbg !2402
  %cmp35 = icmp ne i32 %call34, 0, !dbg !2403
  br i1 %cmp35, label %if.then36, label %if.end37, !dbg !2404

if.then36:                                        ; preds = %if.end31
  store i32 -1, i32* %retval, align 4, !dbg !2405
  br label %return, !dbg !2405

if.end37:                                         ; preds = %if.end31
  store i32 0, i32* %retval, align 4, !dbg !2406
  br label %return, !dbg !2406

return:                                           ; preds = %if.end37, %if.then36, %if.then30, %if.then10, %if.else, %if.then2
  %30 = load i32, i32* %retval, align 4, !dbg !2407
  ret i32 %30, !dbg !2407
}

declare i32 @closedir(%struct.__dirstream*) #2

declare i32 @close(i32) #2

; Function Attrs: nounwind uwtable
define internal void @tree_pop(%struct.tree* %t) #0 !dbg !384 {
entry:
  %t.addr = alloca %struct.tree*, align 8
  %te = alloca %struct.tree_entry*, align 8
  store %struct.tree* %t, %struct.tree** %t.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tree** %t.addr, metadata !2408, metadata !460), !dbg !2409
  call void @llvm.dbg.declare(metadata %struct.tree_entry** %te, metadata !2410, metadata !460), !dbg !2411
  %0 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2412
  %dirname_length = getelementptr inbounds %struct.tree, %struct.tree* %0, i32 0, i32 11, !dbg !2413
  %1 = load i64, i64* %dirname_length, align 8, !dbg !2413
  %2 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2414
  %path = getelementptr inbounds %struct.tree, %struct.tree* %2, i32 0, i32 9, !dbg !2415
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %path, i32 0, i32 0, !dbg !2416
  %3 = load i8*, i8** %s, align 8, !dbg !2416
  %arrayidx = getelementptr inbounds i8, i8* %3, i64 %1, !dbg !2414
  store i8 0, i8* %arrayidx, align 1, !dbg !2417
  %4 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2418
  %dirname_length1 = getelementptr inbounds %struct.tree, %struct.tree* %4, i32 0, i32 11, !dbg !2419
  %5 = load i64, i64* %dirname_length1, align 8, !dbg !2419
  %6 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2420
  %path2 = getelementptr inbounds %struct.tree, %struct.tree* %6, i32 0, i32 9, !dbg !2421
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %path2, i32 0, i32 1, !dbg !2422
  store i64 %5, i64* %length, align 8, !dbg !2423
  %7 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2424
  %stack = getelementptr inbounds %struct.tree, %struct.tree* %7, i32 0, i32 0, !dbg !2426
  %8 = load %struct.tree_entry*, %struct.tree_entry** %stack, align 8, !dbg !2426
  %9 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2427
  %current = getelementptr inbounds %struct.tree, %struct.tree* %9, i32 0, i32 1, !dbg !2428
  %10 = load %struct.tree_entry*, %struct.tree_entry** %current, align 8, !dbg !2428
  %cmp = icmp eq %struct.tree_entry* %8, %10, !dbg !2429
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !2430

land.lhs.true:                                    ; preds = %entry
  %11 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2431
  %current3 = getelementptr inbounds %struct.tree, %struct.tree* %11, i32 0, i32 1, !dbg !2433
  %12 = load %struct.tree_entry*, %struct.tree_entry** %current3, align 8, !dbg !2433
  %cmp4 = icmp ne %struct.tree_entry* %12, null, !dbg !2434
  br i1 %cmp4, label %if.then, label %if.end, !dbg !2435

if.then:                                          ; preds = %land.lhs.true
  %13 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2436
  %current5 = getelementptr inbounds %struct.tree, %struct.tree* %13, i32 0, i32 1, !dbg !2437
  %14 = load %struct.tree_entry*, %struct.tree_entry** %current5, align 8, !dbg !2437
  %parent = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %14, i32 0, i32 2, !dbg !2438
  %15 = load %struct.tree_entry*, %struct.tree_entry** %parent, align 8, !dbg !2438
  %16 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2439
  %current6 = getelementptr inbounds %struct.tree, %struct.tree* %16, i32 0, i32 1, !dbg !2440
  store %struct.tree_entry* %15, %struct.tree_entry** %current6, align 8, !dbg !2441
  br label %if.end, !dbg !2439

if.end:                                           ; preds = %if.then, %land.lhs.true, %entry
  %17 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2442
  %stack7 = getelementptr inbounds %struct.tree, %struct.tree* %17, i32 0, i32 0, !dbg !2443
  %18 = load %struct.tree_entry*, %struct.tree_entry** %stack7, align 8, !dbg !2443
  store %struct.tree_entry* %18, %struct.tree_entry** %te, align 8, !dbg !2444
  %19 = load %struct.tree_entry*, %struct.tree_entry** %te, align 8, !dbg !2445
  %next = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %19, i32 0, i32 1, !dbg !2446
  %20 = load %struct.tree_entry*, %struct.tree_entry** %next, align 8, !dbg !2446
  %21 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2447
  %stack8 = getelementptr inbounds %struct.tree, %struct.tree* %21, i32 0, i32 0, !dbg !2448
  store %struct.tree_entry* %20, %struct.tree_entry** %stack8, align 8, !dbg !2449
  %22 = load %struct.tree_entry*, %struct.tree_entry** %te, align 8, !dbg !2450
  %dirname_length9 = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %22, i32 0, i32 4, !dbg !2451
  %23 = load i64, i64* %dirname_length9, align 8, !dbg !2451
  %24 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2452
  %dirname_length10 = getelementptr inbounds %struct.tree, %struct.tree* %24, i32 0, i32 11, !dbg !2453
  store i64 %23, i64* %dirname_length10, align 8, !dbg !2454
  %25 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2455
  %path11 = getelementptr inbounds %struct.tree, %struct.tree* %25, i32 0, i32 9, !dbg !2456
  %s12 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %path11, i32 0, i32 0, !dbg !2457
  %26 = load i8*, i8** %s12, align 8, !dbg !2457
  %27 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2458
  %dirname_length13 = getelementptr inbounds %struct.tree, %struct.tree* %27, i32 0, i32 11, !dbg !2459
  %28 = load i64, i64* %dirname_length13, align 8, !dbg !2459
  %add.ptr = getelementptr inbounds i8, i8* %26, i64 %28, !dbg !2460
  %29 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2461
  %basename = getelementptr inbounds %struct.tree, %struct.tree* %29, i32 0, i32 10, !dbg !2462
  store i8* %add.ptr, i8** %basename, align 8, !dbg !2463
  br label %while.cond, !dbg !2464

while.cond:                                       ; preds = %while.body, %if.end
  %30 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2465
  %basename14 = getelementptr inbounds %struct.tree, %struct.tree* %30, i32 0, i32 10, !dbg !2467
  %31 = load i8*, i8** %basename14, align 8, !dbg !2467
  %arrayidx15 = getelementptr inbounds i8, i8* %31, i64 0, !dbg !2465
  %32 = load i8, i8* %arrayidx15, align 1, !dbg !2465
  %conv = sext i8 %32 to i32, !dbg !2465
  %cmp16 = icmp eq i32 %conv, 47, !dbg !2468
  br i1 %cmp16, label %while.body, label %while.end, !dbg !2469

while.body:                                       ; preds = %while.cond
  %33 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2470
  %basename18 = getelementptr inbounds %struct.tree, %struct.tree* %33, i32 0, i32 10, !dbg !2471
  %34 = load i8*, i8** %basename18, align 8, !dbg !2472
  %incdec.ptr = getelementptr inbounds i8, i8* %34, i32 1, !dbg !2472
  store i8* %incdec.ptr, i8** %basename18, align 8, !dbg !2472
  br label %while.cond, !dbg !2473

while.end:                                        ; preds = %while.cond
  %35 = load %struct.tree_entry*, %struct.tree_entry** %te, align 8, !dbg !2475
  %name = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %35, i32 0, i32 3, !dbg !2476
  call void @archive_string_free(%struct.archive_string* %name), !dbg !2477
  %36 = load %struct.tree_entry*, %struct.tree_entry** %te, align 8, !dbg !2478
  %37 = bitcast %struct.tree_entry* %36 to i8*, !dbg !2478
  call void @free(i8* %37) #6, !dbg !2479
  ret void, !dbg !2480
}

; Function Attrs: nounwind
declare i32 @futimens(i32, %struct.timespec*) #3

; Function Attrs: nounwind
declare i32 @futimesat(i32, i8*, %struct.timeval*) #3

; Function Attrs: nounwind
declare i32 @lutimes(i8*, %struct.timeval*) #3

; Function Attrs: nounwind uwtable
define internal i8* @tree_current_access_path(%struct.tree* %t) #0 !dbg !386 {
entry:
  %t.addr = alloca %struct.tree*, align 8
  store %struct.tree* %t, %struct.tree** %t.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tree** %t.addr, metadata !2481, metadata !460), !dbg !2482
  %0 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2483
  %basename = getelementptr inbounds %struct.tree, %struct.tree* %0, i32 0, i32 10, !dbg !2484
  %1 = load i8*, i8** %basename, align 8, !dbg !2484
  ret i8* %1, !dbg !2485
}

declare void @__archive_ensure_cloexec_flag(i32) #2

; Function Attrs: nounwind uwtable
define internal i8* @tree_current_path(%struct.tree* %t) #0 !dbg !389 {
entry:
  %t.addr = alloca %struct.tree*, align 8
  store %struct.tree* %t, %struct.tree** %t.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tree** %t.addr, metadata !2486, metadata !460), !dbg !2487
  %0 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2488
  %path = getelementptr inbounds %struct.tree, %struct.tree* %0, i32 0, i32 9, !dbg !2489
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %path, i32 0, i32 0, !dbg !2490
  %1 = load i8*, i8** %s, align 8, !dbg !2490
  ret i8* %1, !dbg !2491
}

; Function Attrs: nounwind uwtable
define internal i32 @tree_enter_initial_dir(%struct.tree* %t) #0 !dbg !390 {
entry:
  %t.addr = alloca %struct.tree*, align 8
  %r = alloca i32, align 4
  store %struct.tree* %t, %struct.tree** %t.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tree** %t.addr, metadata !2492, metadata !460), !dbg !2493
  call void @llvm.dbg.declare(metadata i32* %r, metadata !2494, metadata !460), !dbg !2495
  store i32 0, i32* %r, align 4, !dbg !2495
  %0 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2496
  %flags = getelementptr inbounds %struct.tree, %struct.tree* %0, i32 0, i32 6, !dbg !2498
  %1 = load i32, i32* %flags, align 8, !dbg !2498
  %and = and i32 %1, 256, !dbg !2499
  %cmp = icmp eq i32 %and, 0, !dbg !2500
  br i1 %cmp, label %if.then, label %if.end6, !dbg !2501

if.then:                                          ; preds = %entry
  %2 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2502
  %initial_dir_fd = getelementptr inbounds %struct.tree, %struct.tree* %2, i32 0, i32 15, !dbg !2504
  %3 = load i32, i32* %initial_dir_fd, align 4, !dbg !2504
  %call = call i32 @fchdir(i32 %3) #6, !dbg !2505
  store i32 %call, i32* %r, align 4, !dbg !2506
  %4 = load i32, i32* %r, align 4, !dbg !2507
  %cmp1 = icmp eq i32 %4, 0, !dbg !2509
  br i1 %cmp1, label %if.then2, label %if.end, !dbg !2510

if.then2:                                         ; preds = %if.then
  %5 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2511
  %flags3 = getelementptr inbounds %struct.tree, %struct.tree* %5, i32 0, i32 6, !dbg !2513
  %6 = load i32, i32* %flags3, align 8, !dbg !2514
  %and4 = and i32 %6, -65, !dbg !2514
  store i32 %and4, i32* %flags3, align 8, !dbg !2514
  %7 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2515
  %flags5 = getelementptr inbounds %struct.tree, %struct.tree* %7, i32 0, i32 6, !dbg !2516
  %8 = load i32, i32* %flags5, align 8, !dbg !2517
  %or = or i32 %8, 256, !dbg !2517
  store i32 %or, i32* %flags5, align 8, !dbg !2517
  br label %if.end, !dbg !2518

if.end:                                           ; preds = %if.then2, %if.then
  br label %if.end6, !dbg !2519

if.end6:                                          ; preds = %if.end, %entry
  %9 = load i32, i32* %r, align 4, !dbg !2520
  ret i32 %9, !dbg !2521
}

; Function Attrs: nounwind uwtable
define internal i32 @setup_suitable_read_buffer(%struct.archive_read_disk* %a) #0 !dbg !391 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read_disk*, align 8
  %t = alloca %struct.tree*, align 8
  %cf = alloca %struct.filesystem*, align 8
  %asize = alloca i64, align 8
  %s = alloca i64, align 8
  %xfer_align = alloca i64, align 8
  %incr = alloca i64, align 8
  store %struct.archive_read_disk* %a, %struct.archive_read_disk** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_disk** %a.addr, metadata !2522, metadata !460), !dbg !2523
  call void @llvm.dbg.declare(metadata %struct.tree** %t, metadata !2524, metadata !460), !dbg !2525
  %0 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !2526
  %tree = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %0, i32 0, i32 4, !dbg !2527
  %1 = load %struct.tree*, %struct.tree** %tree, align 8, !dbg !2527
  store %struct.tree* %1, %struct.tree** %t, align 8, !dbg !2525
  call void @llvm.dbg.declare(metadata %struct.filesystem** %cf, metadata !2528, metadata !460), !dbg !2529
  %2 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !2530
  %current_filesystem = getelementptr inbounds %struct.tree, %struct.tree* %2, i32 0, i32 28, !dbg !2531
  %3 = load %struct.filesystem*, %struct.filesystem** %current_filesystem, align 8, !dbg !2531
  store %struct.filesystem* %3, %struct.filesystem** %cf, align 8, !dbg !2529
  call void @llvm.dbg.declare(metadata i64* %asize, metadata !2532, metadata !460), !dbg !2533
  call void @llvm.dbg.declare(metadata i64* %s, metadata !2534, metadata !460), !dbg !2535
  %4 = load %struct.filesystem*, %struct.filesystem** %cf, align 8, !dbg !2536
  %allocation_ptr = getelementptr inbounds %struct.filesystem, %struct.filesystem* %4, i32 0, i32 9, !dbg !2538
  %5 = load i8*, i8** %allocation_ptr, align 8, !dbg !2538
  %cmp = icmp eq i8* %5, null, !dbg !2539
  br i1 %cmp, label %if.then, label %if.end31, !dbg !2540

if.then:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i64* %xfer_align, metadata !2541, metadata !460), !dbg !2543
  %6 = load %struct.filesystem*, %struct.filesystem** %cf, align 8, !dbg !2544
  %xfer_align1 = getelementptr inbounds %struct.filesystem, %struct.filesystem* %6, i32 0, i32 8, !dbg !2545
  %7 = load i64, i64* %xfer_align1, align 8, !dbg !2545
  %cmp2 = icmp eq i64 %7, -1, !dbg !2546
  br i1 %cmp2, label %cond.true, label %cond.false, !dbg !2547

cond.true:                                        ; preds = %if.then
  br label %cond.end, !dbg !2548

cond.false:                                       ; preds = %if.then
  %8 = load %struct.filesystem*, %struct.filesystem** %cf, align 8, !dbg !2550
  %xfer_align3 = getelementptr inbounds %struct.filesystem, %struct.filesystem* %8, i32 0, i32 8, !dbg !2552
  %9 = load i64, i64* %xfer_align3, align 8, !dbg !2552
  br label %cond.end, !dbg !2553

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ 4096, %cond.true ], [ %9, %cond.false ], !dbg !2554
  store i64 %cond, i64* %xfer_align, align 8, !dbg !2556
  %10 = load %struct.filesystem*, %struct.filesystem** %cf, align 8, !dbg !2557
  %max_xfer_size = getelementptr inbounds %struct.filesystem, %struct.filesystem* %10, i32 0, i32 6, !dbg !2559
  %11 = load i64, i64* %max_xfer_size, align 8, !dbg !2559
  %cmp4 = icmp ne i64 %11, -1, !dbg !2560
  br i1 %cmp4, label %if.then5, label %if.else, !dbg !2561

if.then5:                                         ; preds = %cond.end
  %12 = load %struct.filesystem*, %struct.filesystem** %cf, align 8, !dbg !2562
  %max_xfer_size6 = getelementptr inbounds %struct.filesystem, %struct.filesystem* %12, i32 0, i32 6, !dbg !2563
  %13 = load i64, i64* %max_xfer_size6, align 8, !dbg !2563
  %14 = load i64, i64* %xfer_align, align 8, !dbg !2564
  %add = add nsw i64 %13, %14, !dbg !2565
  store i64 %add, i64* %asize, align 8, !dbg !2566
  br label %if.end18, !dbg !2567

if.else:                                          ; preds = %cond.end
  call void @llvm.dbg.declare(metadata i64* %incr, metadata !2568, metadata !460), !dbg !2570
  %15 = load %struct.filesystem*, %struct.filesystem** %cf, align 8, !dbg !2571
  %incr_xfer_size = getelementptr inbounds %struct.filesystem, %struct.filesystem* %15, i32 0, i32 5, !dbg !2572
  %16 = load i64, i64* %incr_xfer_size, align 8, !dbg !2572
  store i64 %16, i64* %incr, align 8, !dbg !2570
  %17 = load i64, i64* %incr, align 8, !dbg !2573
  %cmp7 = icmp slt i64 %17, 0, !dbg !2575
  br i1 %cmp7, label %if.then8, label %if.end, !dbg !2576

if.then8:                                         ; preds = %if.else
  %18 = load %struct.filesystem*, %struct.filesystem** %cf, align 8, !dbg !2577
  %min_xfer_size = getelementptr inbounds %struct.filesystem, %struct.filesystem* %18, i32 0, i32 7, !dbg !2578
  %19 = load i64, i64* %min_xfer_size, align 8, !dbg !2578
  store i64 %19, i64* %incr, align 8, !dbg !2579
  br label %if.end, !dbg !2580

if.end:                                           ; preds = %if.then8, %if.else
  %20 = load %struct.filesystem*, %struct.filesystem** %cf, align 8, !dbg !2581
  %min_xfer_size9 = getelementptr inbounds %struct.filesystem, %struct.filesystem* %20, i32 0, i32 7, !dbg !2583
  %21 = load i64, i64* %min_xfer_size9, align 8, !dbg !2583
  %cmp10 = icmp slt i64 %21, 0, !dbg !2584
  br i1 %cmp10, label %if.then11, label %if.else12, !dbg !2585

if.then11:                                        ; preds = %if.end
  %22 = load i64, i64* %xfer_align, align 8, !dbg !2586
  store i64 %22, i64* %incr, align 8, !dbg !2588
  %23 = load i64, i64* %xfer_align, align 8, !dbg !2589
  store i64 %23, i64* %asize, align 8, !dbg !2590
  br label %if.end14, !dbg !2591

if.else12:                                        ; preds = %if.end
  %24 = load %struct.filesystem*, %struct.filesystem** %cf, align 8, !dbg !2592
  %min_xfer_size13 = getelementptr inbounds %struct.filesystem, %struct.filesystem* %24, i32 0, i32 7, !dbg !2593
  %25 = load i64, i64* %min_xfer_size13, align 8, !dbg !2593
  store i64 %25, i64* %asize, align 8, !dbg !2594
  br label %if.end14

if.end14:                                         ; preds = %if.else12, %if.then11
  br label %while.cond, !dbg !2595

while.cond:                                       ; preds = %while.body, %if.end14
  %26 = load i64, i64* %asize, align 8, !dbg !2596
  %cmp15 = icmp ult i64 %26, 65536, !dbg !2598
  br i1 %cmp15, label %while.body, label %while.end, !dbg !2599

while.body:                                       ; preds = %while.cond
  %27 = load i64, i64* %incr, align 8, !dbg !2600
  %28 = load i64, i64* %asize, align 8, !dbg !2601
  %add16 = add i64 %28, %27, !dbg !2601
  store i64 %add16, i64* %asize, align 8, !dbg !2601
  br label %while.cond, !dbg !2602

while.end:                                        ; preds = %while.cond
  %29 = load i64, i64* %xfer_align, align 8, !dbg !2604
  %30 = load i64, i64* %asize, align 8, !dbg !2605
  %add17 = add i64 %30, %29, !dbg !2605
  store i64 %add17, i64* %asize, align 8, !dbg !2605
  br label %if.end18

if.end18:                                         ; preds = %while.end, %if.then5
  %31 = load i64, i64* %asize, align 8, !dbg !2606
  %call = call noalias i8* @malloc(i64 %31) #6, !dbg !2607
  %32 = load %struct.filesystem*, %struct.filesystem** %cf, align 8, !dbg !2608
  %allocation_ptr19 = getelementptr inbounds %struct.filesystem, %struct.filesystem* %32, i32 0, i32 9, !dbg !2609
  store i8* %call, i8** %allocation_ptr19, align 8, !dbg !2610
  %33 = load %struct.filesystem*, %struct.filesystem** %cf, align 8, !dbg !2611
  %allocation_ptr20 = getelementptr inbounds %struct.filesystem, %struct.filesystem* %33, i32 0, i32 9, !dbg !2613
  %34 = load i8*, i8** %allocation_ptr20, align 8, !dbg !2613
  %cmp21 = icmp eq i8* %34, null, !dbg !2614
  br i1 %cmp21, label %if.then22, label %if.end24, !dbg !2615

if.then22:                                        ; preds = %if.end18
  %35 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !2616
  %archive = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %35, i32 0, i32 0, !dbg !2618
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.24, i32 0, i32 0)), !dbg !2619
  %36 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !2620
  %archive23 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %36, i32 0, i32 0, !dbg !2621
  %state = getelementptr inbounds %struct.archive, %struct.archive* %archive23, i32 0, i32 1, !dbg !2622
  store i32 32768, i32* %state, align 4, !dbg !2623
  store i32 -30, i32* %retval, align 4, !dbg !2624
  br label %return, !dbg !2624

if.end24:                                         ; preds = %if.end18
  %37 = load %struct.filesystem*, %struct.filesystem** %cf, align 8, !dbg !2625
  %allocation_ptr25 = getelementptr inbounds %struct.filesystem, %struct.filesystem* %37, i32 0, i32 9, !dbg !2626
  %38 = load i8*, i8** %allocation_ptr25, align 8, !dbg !2626
  %39 = ptrtoint i8* %38 to i64, !dbg !2627
  store i64 %39, i64* %s, align 8, !dbg !2628
  %40 = load i64, i64* %xfer_align, align 8, !dbg !2629
  %41 = load i64, i64* %s, align 8, !dbg !2630
  %rem = urem i64 %41, %40, !dbg !2630
  store i64 %rem, i64* %s, align 8, !dbg !2630
  %42 = load i64, i64* %s, align 8, !dbg !2631
  %cmp26 = icmp ugt i64 %42, 0, !dbg !2633
  br i1 %cmp26, label %if.then27, label %if.end28, !dbg !2634

if.then27:                                        ; preds = %if.end24
  %43 = load i64, i64* %xfer_align, align 8, !dbg !2635
  %44 = load i64, i64* %s, align 8, !dbg !2636
  %sub = sub i64 %43, %44, !dbg !2637
  store i64 %sub, i64* %s, align 8, !dbg !2638
  br label %if.end28, !dbg !2639

if.end28:                                         ; preds = %if.then27, %if.end24
  %45 = load %struct.filesystem*, %struct.filesystem** %cf, align 8, !dbg !2640
  %allocation_ptr29 = getelementptr inbounds %struct.filesystem, %struct.filesystem* %45, i32 0, i32 9, !dbg !2641
  %46 = load i8*, i8** %allocation_ptr29, align 8, !dbg !2641
  %47 = load i64, i64* %s, align 8, !dbg !2642
  %add.ptr = getelementptr inbounds i8, i8* %46, i64 %47, !dbg !2643
  %48 = load %struct.filesystem*, %struct.filesystem** %cf, align 8, !dbg !2644
  %buff = getelementptr inbounds %struct.filesystem, %struct.filesystem* %48, i32 0, i32 10, !dbg !2645
  store i8* %add.ptr, i8** %buff, align 8, !dbg !2646
  %49 = load i64, i64* %asize, align 8, !dbg !2647
  %50 = load i64, i64* %xfer_align, align 8, !dbg !2648
  %sub30 = sub i64 %49, %50, !dbg !2649
  %51 = load %struct.filesystem*, %struct.filesystem** %cf, align 8, !dbg !2650
  %buff_size = getelementptr inbounds %struct.filesystem, %struct.filesystem* %51, i32 0, i32 11, !dbg !2651
  store i64 %sub30, i64* %buff_size, align 8, !dbg !2652
  br label %if.end31, !dbg !2653

if.end31:                                         ; preds = %if.end28, %entry
  store i32 0, i32* %retval, align 4, !dbg !2654
  br label %return, !dbg !2654

return:                                           ; preds = %if.end31, %if.then22
  %52 = load i32, i32* %retval, align 4, !dbg !2655
  ret i32 %52, !dbg !2655
}

; Function Attrs: nounwind
declare i64 @lseek(i32, i64, i32) #3

declare i64 @read(i32, i8*, i64) #2

; Function Attrs: nounwind
declare i32 @fchdir(i32) #3

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #3

; Function Attrs: nounwind uwtable
define internal i32 @next_entry(%struct.archive_read_disk* %a, %struct.tree* %t, %struct.archive_entry* %entry1) #0 !dbg !396 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read_disk*, align 8
  %t.addr = alloca %struct.tree*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %st = alloca %struct.stat*, align 8
  %lst = alloca %struct.stat*, align 8
  %name = alloca i8*, align 8
  %descend = alloca i32, align 4
  %r = alloca i32, align 4
  %stflags = alloca i32, align 4
  store %struct.archive_read_disk* %a, %struct.archive_read_disk** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_disk** %a.addr, metadata !2656, metadata !460), !dbg !2657
  store %struct.tree* %t, %struct.tree** %t.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tree** %t.addr, metadata !2658, metadata !460), !dbg !2659
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2660, metadata !460), !dbg !2661
  call void @llvm.dbg.declare(metadata %struct.stat** %st, metadata !2662, metadata !460), !dbg !2663
  call void @llvm.dbg.declare(metadata %struct.stat** %lst, metadata !2664, metadata !460), !dbg !2665
  call void @llvm.dbg.declare(metadata i8** %name, metadata !2666, metadata !460), !dbg !2667
  call void @llvm.dbg.declare(metadata i32* %descend, metadata !2668, metadata !460), !dbg !2669
  call void @llvm.dbg.declare(metadata i32* %r, metadata !2670, metadata !460), !dbg !2671
  store %struct.stat* null, %struct.stat** %st, align 8, !dbg !2672
  store %struct.stat* null, %struct.stat** %lst, align 8, !dbg !2673
  %0 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2674
  %descend2 = getelementptr inbounds %struct.tree, %struct.tree* %0, i32 0, i32 19, !dbg !2675
  store i32 0, i32* %descend2, align 8, !dbg !2676
  br label %do.body, !dbg !2677

do.body:                                          ; preds = %do.cond, %entry
  %1 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2678
  %call = call i32 @tree_next(%struct.tree* %1), !dbg !2680
  switch i32 %call, label %sw.epilog [
    i32 -2, label %sw.bb
    i32 -1, label %sw.bb6
    i32 0, label %sw.bb10
    i32 2, label %sw.bb12
    i32 3, label %sw.bb12
    i32 1, label %sw.bb13
  ], !dbg !2681

sw.bb:                                            ; preds = %do.body
  %2 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !2682
  %archive = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %2, i32 0, i32 0, !dbg !2684
  %3 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2685
  %tree_errno = getelementptr inbounds %struct.tree, %struct.tree* %3, i32 0, i32 8, !dbg !2686
  %4 = load i32, i32* %tree_errno, align 8, !dbg !2686
  %5 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2687
  %call3 = call i8* @tree_current_path(%struct.tree* %5), !dbg !2688
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 %4, i8* getelementptr inbounds ([49 x i8], [49 x i8]* @.str.26, i32 0, i32 0), i8* %call3), !dbg !2689
  %6 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !2690
  %archive4 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %6, i32 0, i32 0, !dbg !2691
  %state = getelementptr inbounds %struct.archive, %struct.archive* %archive4, i32 0, i32 1, !dbg !2692
  store i32 32768, i32* %state, align 4, !dbg !2693
  %7 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2694
  %call5 = call i32 @tree_enter_initial_dir(%struct.tree* %7), !dbg !2695
  store i32 -30, i32* %retval, align 4, !dbg !2696
  br label %return, !dbg !2696

sw.bb6:                                           ; preds = %do.body
  %8 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !2697
  %archive7 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %8, i32 0, i32 0, !dbg !2698
  %9 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2699
  %call8 = call i8* @tree_current_path(%struct.tree* %9), !dbg !2700
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive7, i32 -1, i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.27, i32 0, i32 0), i8* %call8), !dbg !2701
  %10 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2702
  %call9 = call i32 @tree_enter_initial_dir(%struct.tree* %10), !dbg !2703
  store i32 -25, i32* %retval, align 4, !dbg !2704
  br label %return, !dbg !2704

sw.bb10:                                          ; preds = %do.body
  %11 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2705
  %call11 = call i32 @tree_enter_initial_dir(%struct.tree* %11), !dbg !2706
  store i32 1, i32* %retval, align 4, !dbg !2707
  br label %return, !dbg !2707

sw.bb12:                                          ; preds = %do.body, %do.body
  br label %sw.epilog, !dbg !2708

sw.bb13:                                          ; preds = %do.body
  %12 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2709
  %call14 = call %struct.stat* @tree_current_lstat(%struct.tree* %12), !dbg !2710
  store %struct.stat* %call14, %struct.stat** %lst, align 8, !dbg !2711
  %13 = load %struct.stat*, %struct.stat** %lst, align 8, !dbg !2712
  %cmp = icmp eq %struct.stat* %13, null, !dbg !2714
  br i1 %cmp, label %if.then, label %if.end, !dbg !2715

if.then:                                          ; preds = %sw.bb13
  %14 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !2716
  %archive15 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %14, i32 0, i32 0, !dbg !2718
  %call16 = call i32* @__errno_location() #1, !dbg !2719
  %15 = load i32, i32* %call16, align 4, !dbg !2719
  %16 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2720
  %call17 = call i8* @tree_current_path(%struct.tree* %16), !dbg !2721
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive15, i32 %15, i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.28, i32 0, i32 0), i8* %call17), !dbg !2722
  %17 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2723
  %call18 = call i32 @tree_enter_initial_dir(%struct.tree* %17), !dbg !2724
  store i32 -25, i32* %retval, align 4, !dbg !2725
  br label %return, !dbg !2725

if.end:                                           ; preds = %sw.bb13
  br label %sw.epilog, !dbg !2726

sw.epilog:                                        ; preds = %do.body, %if.end, %sw.bb12
  br label %do.cond, !dbg !2727

do.cond:                                          ; preds = %sw.epilog
  %18 = load %struct.stat*, %struct.stat** %lst, align 8, !dbg !2728
  %cmp19 = icmp eq %struct.stat* %18, null, !dbg !2730
  br i1 %cmp19, label %do.body, label %do.end, !dbg !2731

do.end:                                           ; preds = %do.cond
  %19 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2732
  %20 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2733
  %call20 = call i8* @tree_current_path(%struct.tree* %20), !dbg !2734
  call void @archive_entry_copy_pathname(%struct.archive_entry* %19, i8* %call20), !dbg !2735
  %21 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !2736
  %matching = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %21, i32 0, i32 17, !dbg !2738
  %22 = load %struct.archive*, %struct.archive** %matching, align 8, !dbg !2738
  %tobool = icmp ne %struct.archive* %22, null, !dbg !2736
  br i1 %tobool, label %if.then21, label %if.end39, !dbg !2739

if.then21:                                        ; preds = %do.end
  %23 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !2740
  %matching22 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %23, i32 0, i32 17, !dbg !2742
  %24 = load %struct.archive*, %struct.archive** %matching22, align 8, !dbg !2742
  %25 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2743
  %call23 = call i32 @archive_match_path_excluded(%struct.archive* %24, %struct.archive_entry* %25), !dbg !2744
  store i32 %call23, i32* %r, align 4, !dbg !2745
  %26 = load i32, i32* %r, align 4, !dbg !2746
  %cmp24 = icmp slt i32 %26, 0, !dbg !2748
  br i1 %cmp24, label %if.then25, label %if.end30, !dbg !2749

if.then25:                                        ; preds = %if.then21
  %27 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !2750
  %archive26 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %27, i32 0, i32 0, !dbg !2752
  %call27 = call i32* @__errno_location() #1, !dbg !2753
  %28 = load i32, i32* %call27, align 4, !dbg !2753
  %29 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !2754
  %matching28 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %29, i32 0, i32 17, !dbg !2755
  %30 = load %struct.archive*, %struct.archive** %matching28, align 8, !dbg !2755
  %call29 = call i8* @archive_error_string(%struct.archive* %30), !dbg !2756
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive26, i32 %28, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.29, i32 0, i32 0), i8* %call29), !dbg !2757
  %31 = load i32, i32* %r, align 4, !dbg !2758
  store i32 %31, i32* %retval, align 4, !dbg !2759
  br label %return, !dbg !2759

if.end30:                                         ; preds = %if.then21
  %32 = load i32, i32* %r, align 4, !dbg !2760
  %tobool31 = icmp ne i32 %32, 0, !dbg !2760
  br i1 %tobool31, label %if.then32, label %if.end38, !dbg !2762

if.then32:                                        ; preds = %if.end30
  %33 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !2763
  %excluded_cb_func = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %33, i32 0, i32 18, !dbg !2766
  %34 = load void (%struct.archive*, i8*, %struct.archive_entry*)*, void (%struct.archive*, i8*, %struct.archive_entry*)** %excluded_cb_func, align 8, !dbg !2766
  %tobool33 = icmp ne void (%struct.archive*, i8*, %struct.archive_entry*)* %34, null, !dbg !2763
  br i1 %tobool33, label %if.then34, label %if.end37, !dbg !2767

if.then34:                                        ; preds = %if.then32
  %35 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !2768
  %excluded_cb_func35 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %35, i32 0, i32 18, !dbg !2769
  %36 = load void (%struct.archive*, i8*, %struct.archive_entry*)*, void (%struct.archive*, i8*, %struct.archive_entry*)** %excluded_cb_func35, align 8, !dbg !2769
  %37 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !2770
  %archive36 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %37, i32 0, i32 0, !dbg !2771
  %38 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !2772
  %excluded_cb_data = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %38, i32 0, i32 19, !dbg !2773
  %39 = load i8*, i8** %excluded_cb_data, align 8, !dbg !2773
  %40 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2774
  call void %36(%struct.archive* %archive36, i8* %39, %struct.archive_entry* %40), !dbg !2768
  br label %if.end37, !dbg !2768

if.end37:                                         ; preds = %if.then34, %if.then32
  store i32 -10, i32* %retval, align 4, !dbg !2775
  br label %return, !dbg !2775

if.end38:                                         ; preds = %if.end30
  br label %if.end39, !dbg !2776

if.end39:                                         ; preds = %if.end38, %do.end
  %41 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2777
  %symlink_mode = getelementptr inbounds %struct.tree, %struct.tree* %41, i32 0, i32 27, !dbg !2778
  %42 = load i8, i8* %symlink_mode, align 1, !dbg !2778
  %conv = sext i8 %42 to i32, !dbg !2777
  switch i32 %conv, label %sw.default [
    i32 72, label %sw.bb40
    i32 76, label %sw.bb42
  ], !dbg !2779

sw.bb40:                                          ; preds = %if.end39
  %43 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2780
  %symlink_mode41 = getelementptr inbounds %struct.tree, %struct.tree* %43, i32 0, i32 27, !dbg !2782
  store i8 80, i8* %symlink_mode41, align 1, !dbg !2783
  br label %sw.bb42, !dbg !2780

sw.bb42:                                          ; preds = %if.end39, %sw.bb40
  %44 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2784
  %call43 = call i32 @tree_current_is_dir(%struct.tree* %44), !dbg !2785
  store i32 %call43, i32* %descend, align 4, !dbg !2786
  %45 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !2787
  %symlink_mode44 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %45, i32 0, i32 2, !dbg !2788
  store i8 76, i8* %symlink_mode44, align 8, !dbg !2789
  %46 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !2790
  %follow_symlinks = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %46, i32 0, i32 3, !dbg !2791
  store i8 1, i8* %follow_symlinks, align 1, !dbg !2792
  %47 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2793
  %call45 = call %struct.stat* @tree_current_stat(%struct.tree* %47), !dbg !2794
  store %struct.stat* %call45, %struct.stat** %st, align 8, !dbg !2795
  %48 = load %struct.stat*, %struct.stat** %st, align 8, !dbg !2796
  %cmp46 = icmp ne %struct.stat* %48, null, !dbg !2798
  br i1 %cmp46, label %land.lhs.true, label %if.end51, !dbg !2799

land.lhs.true:                                    ; preds = %sw.bb42
  %49 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2800
  %50 = load %struct.stat*, %struct.stat** %st, align 8, !dbg !2802
  %call48 = call i32 @tree_target_is_same_as_parent(%struct.tree* %49, %struct.stat* %50), !dbg !2803
  %tobool49 = icmp ne i32 %call48, 0, !dbg !2803
  br i1 %tobool49, label %if.end51, label %if.then50, !dbg !2804

if.then50:                                        ; preds = %land.lhs.true
  br label %sw.epilog55, !dbg !2805

if.end51:                                         ; preds = %land.lhs.true, %sw.bb42
  br label %sw.default, !dbg !2806

sw.default:                                       ; preds = %if.end39, %if.end51
  %51 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2808
  %call52 = call i32 @tree_current_is_physical_dir(%struct.tree* %51), !dbg !2809
  store i32 %call52, i32* %descend, align 4, !dbg !2810
  %52 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !2811
  %symlink_mode53 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %52, i32 0, i32 2, !dbg !2812
  store i8 80, i8* %symlink_mode53, align 8, !dbg !2813
  %53 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !2814
  %follow_symlinks54 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %53, i32 0, i32 3, !dbg !2815
  store i8 0, i8* %follow_symlinks54, align 1, !dbg !2816
  %54 = load %struct.stat*, %struct.stat** %lst, align 8, !dbg !2817
  store %struct.stat* %54, %struct.stat** %st, align 8, !dbg !2818
  br label %sw.epilog55, !dbg !2819

sw.epilog55:                                      ; preds = %sw.default, %if.then50
  %55 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !2820
  %56 = load %struct.stat*, %struct.stat** %st, align 8, !dbg !2822
  %st_dev = getelementptr inbounds %struct.stat, %struct.stat* %56, i32 0, i32 0, !dbg !2823
  %57 = load i64, i64* %st_dev, align 8, !dbg !2823
  %call56 = call i32 @update_current_filesystem(%struct.archive_read_disk* %55, i64 %57), !dbg !2824
  %cmp57 = icmp ne i32 %call56, 0, !dbg !2825
  br i1 %cmp57, label %if.then59, label %if.end63, !dbg !2826

if.then59:                                        ; preds = %sw.epilog55
  %58 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !2827
  %archive60 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %58, i32 0, i32 0, !dbg !2829
  %state61 = getelementptr inbounds %struct.archive, %struct.archive* %archive60, i32 0, i32 1, !dbg !2830
  store i32 32768, i32* %state61, align 4, !dbg !2831
  %59 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2832
  %call62 = call i32 @tree_enter_initial_dir(%struct.tree* %59), !dbg !2833
  store i32 -30, i32* %retval, align 4, !dbg !2834
  br label %return, !dbg !2834

if.end63:                                         ; preds = %sw.epilog55
  %60 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2835
  %initial_filesystem_id = getelementptr inbounds %struct.tree, %struct.tree* %60, i32 0, i32 30, !dbg !2837
  %61 = load i32, i32* %initial_filesystem_id, align 8, !dbg !2837
  %cmp64 = icmp eq i32 %61, -1, !dbg !2838
  br i1 %cmp64, label %if.then66, label %if.end68, !dbg !2839

if.then66:                                        ; preds = %if.end63
  %62 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2840
  %current_filesystem_id = getelementptr inbounds %struct.tree, %struct.tree* %62, i32 0, i32 31, !dbg !2841
  %63 = load i32, i32* %current_filesystem_id, align 4, !dbg !2841
  %64 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2842
  %initial_filesystem_id67 = getelementptr inbounds %struct.tree, %struct.tree* %64, i32 0, i32 30, !dbg !2843
  store i32 %63, i32* %initial_filesystem_id67, align 8, !dbg !2844
  br label %if.end68, !dbg !2842

if.end68:                                         ; preds = %if.then66, %if.end63
  %65 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !2845
  %flags = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %65, i32 0, i32 8, !dbg !2847
  %66 = load i32, i32* %flags, align 8, !dbg !2847
  %and = and i32 %66, 8, !dbg !2848
  %tobool69 = icmp ne i32 %and, 0, !dbg !2848
  br i1 %tobool69, label %if.then70, label %if.end77, !dbg !2849

if.then70:                                        ; preds = %if.end68
  %67 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2850
  %initial_filesystem_id71 = getelementptr inbounds %struct.tree, %struct.tree* %67, i32 0, i32 30, !dbg !2853
  %68 = load i32, i32* %initial_filesystem_id71, align 8, !dbg !2853
  %69 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2854
  %current_filesystem_id72 = getelementptr inbounds %struct.tree, %struct.tree* %69, i32 0, i32 31, !dbg !2855
  %70 = load i32, i32* %current_filesystem_id72, align 4, !dbg !2855
  %cmp73 = icmp ne i32 %68, %70, !dbg !2856
  br i1 %cmp73, label %if.then75, label %if.end76, !dbg !2857

if.then75:                                        ; preds = %if.then70
  store i32 0, i32* %descend, align 4, !dbg !2858
  br label %if.end76, !dbg !2859

if.end76:                                         ; preds = %if.then75, %if.then70
  br label %if.end77, !dbg !2860

if.end77:                                         ; preds = %if.end76, %if.end68
  %71 = load i32, i32* %descend, align 4, !dbg !2861
  %72 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2862
  %descend78 = getelementptr inbounds %struct.tree, %struct.tree* %72, i32 0, i32 19, !dbg !2863
  store i32 %71, i32* %descend78, align 8, !dbg !2864
  %73 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !2865
  %flags79 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %73, i32 0, i32 8, !dbg !2867
  %74 = load i32, i32* %flags79, align 8, !dbg !2867
  %and80 = and i32 %74, 2, !dbg !2868
  %tobool81 = icmp ne i32 %and80, 0, !dbg !2868
  br i1 %tobool81, label %if.then82, label %if.end110, !dbg !2869

if.then82:                                        ; preds = %if.end77
  %75 = load %struct.stat*, %struct.stat** %st, align 8, !dbg !2870
  %st_mode = getelementptr inbounds %struct.stat, %struct.stat* %75, i32 0, i32 3, !dbg !2870
  %76 = load i32, i32* %st_mode, align 8, !dbg !2870
  %and83 = and i32 %76, 61440, !dbg !2870
  %cmp84 = icmp eq i32 %and83, 32768, !dbg !2870
  br i1 %cmp84, label %if.then90, label %lor.lhs.false, !dbg !2873

lor.lhs.false:                                    ; preds = %if.then82
  %77 = load %struct.stat*, %struct.stat** %st, align 8, !dbg !2874
  %st_mode86 = getelementptr inbounds %struct.stat, %struct.stat* %77, i32 0, i32 3, !dbg !2874
  %78 = load i32, i32* %st_mode86, align 8, !dbg !2874
  %and87 = and i32 %78, 61440, !dbg !2874
  %cmp88 = icmp eq i32 %and87, 16384, !dbg !2874
  br i1 %cmp88, label %if.then90, label %if.end109, !dbg !2876

if.then90:                                        ; preds = %lor.lhs.false, %if.then82
  call void @llvm.dbg.declare(metadata i32* %stflags, metadata !2877, metadata !460), !dbg !2879
  %79 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2880
  %80 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2881
  %call91 = call i8* @tree_current_access_path(%struct.tree* %80), !dbg !2882
  %call92 = call i32 @open_on_current_dir(%struct.tree* %79, i8* %call91, i32 526336), !dbg !2883
  %81 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2884
  %entry_fd = getelementptr inbounds %struct.tree, %struct.tree* %81, i32 0, i32 34, !dbg !2885
  store i32 %call92, i32* %entry_fd, align 8, !dbg !2886
  %82 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2887
  %entry_fd93 = getelementptr inbounds %struct.tree, %struct.tree* %82, i32 0, i32 34, !dbg !2888
  %83 = load i32, i32* %entry_fd93, align 8, !dbg !2888
  call void @__archive_ensure_cloexec_flag(i32 %83), !dbg !2889
  %84 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2890
  %entry_fd94 = getelementptr inbounds %struct.tree, %struct.tree* %84, i32 0, i32 34, !dbg !2892
  %85 = load i32, i32* %entry_fd94, align 8, !dbg !2892
  %cmp95 = icmp sge i32 %85, 0, !dbg !2893
  br i1 %cmp95, label %if.then97, label %if.end108, !dbg !2894

if.then97:                                        ; preds = %if.then90
  %86 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2895
  %entry_fd98 = getelementptr inbounds %struct.tree, %struct.tree* %86, i32 0, i32 34, !dbg !2897
  %87 = load i32, i32* %entry_fd98, align 8, !dbg !2897
  %call99 = call i32 (i32, i64, ...) @ioctl(i32 %87, i64 2148034049, i32* %stflags) #6, !dbg !2898
  store i32 %call99, i32* %r, align 4, !dbg !2899
  %88 = load i32, i32* %r, align 4, !dbg !2900
  %cmp100 = icmp eq i32 %88, 0, !dbg !2902
  br i1 %cmp100, label %land.lhs.true102, label %if.end107, !dbg !2903

land.lhs.true102:                                 ; preds = %if.then97
  %89 = load i32, i32* %stflags, align 4, !dbg !2904
  %and103 = and i32 %89, 64, !dbg !2906
  %cmp104 = icmp ne i32 %and103, 0, !dbg !2907
  br i1 %cmp104, label %if.then106, label %if.end107, !dbg !2908

if.then106:                                       ; preds = %land.lhs.true102
  store i32 -10, i32* %retval, align 4, !dbg !2909
  br label %return, !dbg !2909

if.end107:                                        ; preds = %land.lhs.true102, %if.then97
  br label %if.end108, !dbg !2910

if.end108:                                        ; preds = %if.end107, %if.then90
  br label %if.end109, !dbg !2911

if.end109:                                        ; preds = %if.end108, %lor.lhs.false
  br label %if.end110, !dbg !2912

if.end110:                                        ; preds = %if.end109, %if.end77
  %90 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2913
  %91 = load %struct.stat*, %struct.stat** %st, align 8, !dbg !2914
  call void @archive_entry_copy_stat(%struct.archive_entry* %90, %struct.stat* %91), !dbg !2915
  %92 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2916
  %call111 = call i64 @archive_entry_mtime(%struct.archive_entry* %92), !dbg !2917
  %93 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2918
  %restore_time = getelementptr inbounds %struct.tree, %struct.tree* %93, i32 0, i32 21, !dbg !2919
  %mtime = getelementptr inbounds %struct.restore_time, %struct.restore_time* %restore_time, i32 0, i32 1, !dbg !2920
  store i64 %call111, i64* %mtime, align 8, !dbg !2921
  %94 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2922
  %call112 = call i64 @archive_entry_mtime_nsec(%struct.archive_entry* %94), !dbg !2923
  %95 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2924
  %restore_time113 = getelementptr inbounds %struct.tree, %struct.tree* %95, i32 0, i32 21, !dbg !2925
  %mtime_nsec = getelementptr inbounds %struct.restore_time, %struct.restore_time* %restore_time113, i32 0, i32 2, !dbg !2926
  store i64 %call112, i64* %mtime_nsec, align 8, !dbg !2927
  %96 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2928
  %call114 = call i64 @archive_entry_atime(%struct.archive_entry* %96), !dbg !2929
  %97 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2930
  %restore_time115 = getelementptr inbounds %struct.tree, %struct.tree* %97, i32 0, i32 21, !dbg !2931
  %atime = getelementptr inbounds %struct.restore_time, %struct.restore_time* %restore_time115, i32 0, i32 3, !dbg !2932
  store i64 %call114, i64* %atime, align 8, !dbg !2933
  %98 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2934
  %call116 = call i64 @archive_entry_atime_nsec(%struct.archive_entry* %98), !dbg !2935
  %99 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2936
  %restore_time117 = getelementptr inbounds %struct.tree, %struct.tree* %99, i32 0, i32 21, !dbg !2937
  %atime_nsec = getelementptr inbounds %struct.restore_time, %struct.restore_time* %restore_time117, i32 0, i32 4, !dbg !2938
  store i64 %call116, i64* %atime_nsec, align 8, !dbg !2939
  %100 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2940
  %call118 = call i32 @archive_entry_filetype(%struct.archive_entry* %100), !dbg !2941
  %101 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2942
  %restore_time119 = getelementptr inbounds %struct.tree, %struct.tree* %101, i32 0, i32 21, !dbg !2943
  %filetype = getelementptr inbounds %struct.restore_time, %struct.restore_time* %restore_time119, i32 0, i32 5, !dbg !2944
  store i32 %call118, i32* %filetype, align 8, !dbg !2945
  %102 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2946
  %current_filesystem = getelementptr inbounds %struct.tree, %struct.tree* %102, i32 0, i32 28, !dbg !2947
  %103 = load %struct.filesystem*, %struct.filesystem** %current_filesystem, align 8, !dbg !2947
  %noatime = getelementptr inbounds %struct.filesystem, %struct.filesystem* %103, i32 0, i32 3, !dbg !2948
  %104 = load i32, i32* %noatime, align 8, !dbg !2948
  %105 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !2949
  %restore_time120 = getelementptr inbounds %struct.tree, %struct.tree* %105, i32 0, i32 21, !dbg !2950
  %noatime121 = getelementptr inbounds %struct.restore_time, %struct.restore_time* %restore_time120, i32 0, i32 6, !dbg !2951
  store i32 %104, i32* %noatime121, align 4, !dbg !2952
  %106 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !2953
  %matching122 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %106, i32 0, i32 17, !dbg !2955
  %107 = load %struct.archive*, %struct.archive** %matching122, align 8, !dbg !2955
  %tobool123 = icmp ne %struct.archive* %107, null, !dbg !2953
  br i1 %tobool123, label %if.then124, label %if.end145, !dbg !2956

if.then124:                                       ; preds = %if.end110
  %108 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !2957
  %matching125 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %108, i32 0, i32 17, !dbg !2959
  %109 = load %struct.archive*, %struct.archive** %matching125, align 8, !dbg !2959
  %110 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2960
  %call126 = call i32 @archive_match_time_excluded(%struct.archive* %109, %struct.archive_entry* %110), !dbg !2961
  store i32 %call126, i32* %r, align 4, !dbg !2962
  %111 = load i32, i32* %r, align 4, !dbg !2963
  %cmp127 = icmp slt i32 %111, 0, !dbg !2965
  br i1 %cmp127, label %if.then129, label %if.end134, !dbg !2966

if.then129:                                       ; preds = %if.then124
  %112 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !2967
  %archive130 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %112, i32 0, i32 0, !dbg !2969
  %call131 = call i32* @__errno_location() #1, !dbg !2970
  %113 = load i32, i32* %call131, align 4, !dbg !2970
  %114 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !2971
  %matching132 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %114, i32 0, i32 17, !dbg !2972
  %115 = load %struct.archive*, %struct.archive** %matching132, align 8, !dbg !2972
  %call133 = call i8* @archive_error_string(%struct.archive* %115), !dbg !2973
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive130, i32 %113, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.29, i32 0, i32 0), i8* %call133), !dbg !2974
  %116 = load i32, i32* %r, align 4, !dbg !2975
  store i32 %116, i32* %retval, align 4, !dbg !2976
  br label %return, !dbg !2976

if.end134:                                        ; preds = %if.then124
  %117 = load i32, i32* %r, align 4, !dbg !2977
  %tobool135 = icmp ne i32 %117, 0, !dbg !2977
  br i1 %tobool135, label %if.then136, label %if.end144, !dbg !2979

if.then136:                                       ; preds = %if.end134
  %118 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !2980
  %excluded_cb_func137 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %118, i32 0, i32 18, !dbg !2983
  %119 = load void (%struct.archive*, i8*, %struct.archive_entry*)*, void (%struct.archive*, i8*, %struct.archive_entry*)** %excluded_cb_func137, align 8, !dbg !2983
  %tobool138 = icmp ne void (%struct.archive*, i8*, %struct.archive_entry*)* %119, null, !dbg !2980
  br i1 %tobool138, label %if.then139, label %if.end143, !dbg !2984

if.then139:                                       ; preds = %if.then136
  %120 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !2985
  %excluded_cb_func140 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %120, i32 0, i32 18, !dbg !2986
  %121 = load void (%struct.archive*, i8*, %struct.archive_entry*)*, void (%struct.archive*, i8*, %struct.archive_entry*)** %excluded_cb_func140, align 8, !dbg !2986
  %122 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !2987
  %archive141 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %122, i32 0, i32 0, !dbg !2988
  %123 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !2989
  %excluded_cb_data142 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %123, i32 0, i32 19, !dbg !2990
  %124 = load i8*, i8** %excluded_cb_data142, align 8, !dbg !2990
  %125 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2991
  call void %121(%struct.archive* %archive141, i8* %124, %struct.archive_entry* %125), !dbg !2985
  br label %if.end143, !dbg !2985

if.end143:                                        ; preds = %if.then139, %if.then136
  store i32 -10, i32* %retval, align 4, !dbg !2992
  br label %return, !dbg !2992

if.end144:                                        ; preds = %if.end134
  br label %if.end145, !dbg !2993

if.end145:                                        ; preds = %if.end144, %if.end110
  %126 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !2994
  %archive146 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %126, i32 0, i32 0, !dbg !2995
  %127 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2996
  %call147 = call i64 @archive_entry_uid(%struct.archive_entry* %127), !dbg !2997
  %call148 = call i8* @archive_read_disk_uname(%struct.archive* %archive146, i64 %call147), !dbg !2998
  store i8* %call148, i8** %name, align 8, !dbg !2999
  %128 = load i8*, i8** %name, align 8, !dbg !3000
  %cmp149 = icmp ne i8* %128, null, !dbg !3002
  br i1 %cmp149, label %if.then151, label %if.end152, !dbg !3003

if.then151:                                       ; preds = %if.end145
  %129 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3004
  %130 = load i8*, i8** %name, align 8, !dbg !3005
  call void @archive_entry_copy_uname(%struct.archive_entry* %129, i8* %130), !dbg !3006
  br label %if.end152, !dbg !3006

if.end152:                                        ; preds = %if.then151, %if.end145
  %131 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !3007
  %archive153 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %131, i32 0, i32 0, !dbg !3008
  %132 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3009
  %call154 = call i64 @archive_entry_gid(%struct.archive_entry* %132), !dbg !3010
  %call155 = call i8* @archive_read_disk_gname(%struct.archive* %archive153, i64 %call154), !dbg !3011
  store i8* %call155, i8** %name, align 8, !dbg !3012
  %133 = load i8*, i8** %name, align 8, !dbg !3013
  %cmp156 = icmp ne i8* %133, null, !dbg !3015
  br i1 %cmp156, label %if.then158, label %if.end159, !dbg !3016

if.then158:                                       ; preds = %if.end152
  %134 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3017
  %135 = load i8*, i8** %name, align 8, !dbg !3018
  call void @archive_entry_copy_gname(%struct.archive_entry* %134, i8* %135), !dbg !3019
  br label %if.end159, !dbg !3019

if.end159:                                        ; preds = %if.then158, %if.end152
  %136 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !3020
  %matching160 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %136, i32 0, i32 17, !dbg !3022
  %137 = load %struct.archive*, %struct.archive** %matching160, align 8, !dbg !3022
  %tobool161 = icmp ne %struct.archive* %137, null, !dbg !3020
  br i1 %tobool161, label %if.then162, label %if.end183, !dbg !3023

if.then162:                                       ; preds = %if.end159
  %138 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !3024
  %matching163 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %138, i32 0, i32 17, !dbg !3026
  %139 = load %struct.archive*, %struct.archive** %matching163, align 8, !dbg !3026
  %140 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3027
  %call164 = call i32 @archive_match_owner_excluded(%struct.archive* %139, %struct.archive_entry* %140), !dbg !3028
  store i32 %call164, i32* %r, align 4, !dbg !3029
  %141 = load i32, i32* %r, align 4, !dbg !3030
  %cmp165 = icmp slt i32 %141, 0, !dbg !3032
  br i1 %cmp165, label %if.then167, label %if.end172, !dbg !3033

if.then167:                                       ; preds = %if.then162
  %142 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !3034
  %archive168 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %142, i32 0, i32 0, !dbg !3036
  %call169 = call i32* @__errno_location() #1, !dbg !3037
  %143 = load i32, i32* %call169, align 4, !dbg !3037
  %144 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !3038
  %matching170 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %144, i32 0, i32 17, !dbg !3039
  %145 = load %struct.archive*, %struct.archive** %matching170, align 8, !dbg !3039
  %call171 = call i8* @archive_error_string(%struct.archive* %145), !dbg !3040
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive168, i32 %143, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.29, i32 0, i32 0), i8* %call171), !dbg !3041
  %146 = load i32, i32* %r, align 4, !dbg !3042
  store i32 %146, i32* %retval, align 4, !dbg !3043
  br label %return, !dbg !3043

if.end172:                                        ; preds = %if.then162
  %147 = load i32, i32* %r, align 4, !dbg !3044
  %tobool173 = icmp ne i32 %147, 0, !dbg !3044
  br i1 %tobool173, label %if.then174, label %if.end182, !dbg !3046

if.then174:                                       ; preds = %if.end172
  %148 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !3047
  %excluded_cb_func175 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %148, i32 0, i32 18, !dbg !3050
  %149 = load void (%struct.archive*, i8*, %struct.archive_entry*)*, void (%struct.archive*, i8*, %struct.archive_entry*)** %excluded_cb_func175, align 8, !dbg !3050
  %tobool176 = icmp ne void (%struct.archive*, i8*, %struct.archive_entry*)* %149, null, !dbg !3047
  br i1 %tobool176, label %if.then177, label %if.end181, !dbg !3051

if.then177:                                       ; preds = %if.then174
  %150 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !3052
  %excluded_cb_func178 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %150, i32 0, i32 18, !dbg !3053
  %151 = load void (%struct.archive*, i8*, %struct.archive_entry*)*, void (%struct.archive*, i8*, %struct.archive_entry*)** %excluded_cb_func178, align 8, !dbg !3053
  %152 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !3054
  %archive179 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %152, i32 0, i32 0, !dbg !3055
  %153 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !3056
  %excluded_cb_data180 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %153, i32 0, i32 19, !dbg !3057
  %154 = load i8*, i8** %excluded_cb_data180, align 8, !dbg !3057
  %155 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3058
  call void %151(%struct.archive* %archive179, i8* %154, %struct.archive_entry* %155), !dbg !3052
  br label %if.end181, !dbg !3052

if.end181:                                        ; preds = %if.then177, %if.then174
  store i32 -10, i32* %retval, align 4, !dbg !3059
  br label %return, !dbg !3059

if.end182:                                        ; preds = %if.end172
  br label %if.end183, !dbg !3060

if.end183:                                        ; preds = %if.end182, %if.end159
  %156 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !3061
  %metadata_filter_func = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %156, i32 0, i32 15, !dbg !3063
  %157 = load i32 (%struct.archive*, i8*, %struct.archive_entry*)*, i32 (%struct.archive*, i8*, %struct.archive_entry*)** %metadata_filter_func, align 8, !dbg !3063
  %tobool184 = icmp ne i32 (%struct.archive*, i8*, %struct.archive_entry*)* %157, null, !dbg !3061
  br i1 %tobool184, label %if.then185, label %if.end192, !dbg !3064

if.then185:                                       ; preds = %if.end183
  %158 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !3065
  %metadata_filter_func186 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %158, i32 0, i32 15, !dbg !3068
  %159 = load i32 (%struct.archive*, i8*, %struct.archive_entry*)*, i32 (%struct.archive*, i8*, %struct.archive_entry*)** %metadata_filter_func186, align 8, !dbg !3068
  %160 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !3069
  %archive187 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %160, i32 0, i32 0, !dbg !3070
  %161 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !3071
  %metadata_filter_data = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %161, i32 0, i32 16, !dbg !3072
  %162 = load i8*, i8** %metadata_filter_data, align 8, !dbg !3072
  %163 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3073
  %call188 = call i32 %159(%struct.archive* %archive187, i8* %162, %struct.archive_entry* %163), !dbg !3065
  %tobool189 = icmp ne i32 %call188, 0, !dbg !3065
  br i1 %tobool189, label %if.end191, label %if.then190, !dbg !3074

if.then190:                                       ; preds = %if.then185
  store i32 -10, i32* %retval, align 4, !dbg !3075
  br label %return, !dbg !3075

if.end191:                                        ; preds = %if.then185
  br label %if.end192, !dbg !3076

if.end192:                                        ; preds = %if.end191, %if.end183
  %164 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3077
  %165 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3078
  %call193 = call i8* @tree_current_access_path(%struct.tree* %165), !dbg !3079
  call void @archive_entry_copy_sourcepath(%struct.archive_entry* %164, i8* %call193), !dbg !3080
  %166 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !3081
  %archive194 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %166, i32 0, i32 0, !dbg !3082
  %167 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3083
  %168 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3084
  %entry_fd195 = getelementptr inbounds %struct.tree, %struct.tree* %168, i32 0, i32 34, !dbg !3085
  %169 = load i32, i32* %entry_fd195, align 8, !dbg !3085
  %170 = load %struct.stat*, %struct.stat** %st, align 8, !dbg !3086
  %call196 = call i32 @archive_read_disk_entry_from_file(%struct.archive* %archive194, %struct.archive_entry* %167, i32 %169, %struct.stat* %170), !dbg !3087
  store i32 %call196, i32* %r, align 4, !dbg !3088
  %171 = load i32, i32* %r, align 4, !dbg !3089
  store i32 %171, i32* %retval, align 4, !dbg !3090
  br label %return, !dbg !3090

return:                                           ; preds = %if.end192, %if.then190, %if.end181, %if.then167, %if.end143, %if.then129, %if.then106, %if.then59, %if.end37, %if.then25, %if.then, %sw.bb10, %sw.bb6, %sw.bb
  %172 = load i32, i32* %retval, align 4, !dbg !3091
  ret i32 %172, !dbg !3091
}

declare %struct.archive_entry* @archive_entry_clear(%struct.archive_entry*) #2

declare void @archive_entry_copy_sourcepath(%struct.archive_entry*, i8*) #2

declare i32 @archive_entry_filetype(%struct.archive_entry*) #2

declare i32 @archive_entry_nlink(%struct.archive_entry*) #2

declare i64 @archive_entry_size(%struct.archive_entry*) #2

; Function Attrs: nounwind uwtable
define internal i32 @setup_sparse(%struct.archive_read_disk* %a, %struct.archive_entry* %entry1) #0 !dbg !426 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read_disk*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %t = alloca %struct.tree*, align 8
  %length = alloca i64, align 8
  %offset = alloca i64, align 8
  %i = alloca i32, align 4
  store %struct.archive_read_disk* %a, %struct.archive_read_disk** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_disk** %a.addr, metadata !3092, metadata !460), !dbg !3093
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3094, metadata !460), !dbg !3095
  call void @llvm.dbg.declare(metadata %struct.tree** %t, metadata !3096, metadata !460), !dbg !3097
  %0 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !3098
  %tree = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %0, i32 0, i32 4, !dbg !3099
  %1 = load %struct.tree*, %struct.tree** %tree, align 8, !dbg !3099
  store %struct.tree* %1, %struct.tree** %t, align 8, !dbg !3097
  call void @llvm.dbg.declare(metadata i64* %length, metadata !3100, metadata !460), !dbg !3101
  call void @llvm.dbg.declare(metadata i64* %offset, metadata !3102, metadata !460), !dbg !3103
  call void @llvm.dbg.declare(metadata i32* %i, metadata !3104, metadata !460), !dbg !3105
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3106
  %call = call i32 @archive_entry_sparse_reset(%struct.archive_entry* %2), !dbg !3107
  %3 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !3108
  %sparse_count = getelementptr inbounds %struct.tree, %struct.tree* %3, i32 0, i32 24, !dbg !3109
  store i32 %call, i32* %sparse_count, align 8, !dbg !3110
  %4 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !3111
  %sparse_count2 = getelementptr inbounds %struct.tree, %struct.tree* %4, i32 0, i32 24, !dbg !3113
  %5 = load i32, i32* %sparse_count2, align 8, !dbg !3113
  %add = add nsw i32 %5, 1, !dbg !3114
  %6 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !3115
  %sparse_list_size = getelementptr inbounds %struct.tree, %struct.tree* %6, i32 0, i32 25, !dbg !3116
  %7 = load i32, i32* %sparse_list_size, align 4, !dbg !3116
  %cmp = icmp sgt i32 %add, %7, !dbg !3117
  br i1 %cmp, label %if.then, label %if.end15, !dbg !3118

if.then:                                          ; preds = %entry
  %8 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !3119
  %sparse_list = getelementptr inbounds %struct.tree, %struct.tree* %8, i32 0, i32 22, !dbg !3121
  %9 = load %struct.entry_sparse*, %struct.entry_sparse** %sparse_list, align 8, !dbg !3121
  %10 = bitcast %struct.entry_sparse* %9 to i8*, !dbg !3119
  call void @free(i8* %10) #6, !dbg !3122
  %11 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !3123
  %sparse_count3 = getelementptr inbounds %struct.tree, %struct.tree* %11, i32 0, i32 24, !dbg !3124
  %12 = load i32, i32* %sparse_count3, align 8, !dbg !3124
  %add4 = add nsw i32 %12, 1, !dbg !3125
  %13 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !3126
  %sparse_list_size5 = getelementptr inbounds %struct.tree, %struct.tree* %13, i32 0, i32 25, !dbg !3127
  store i32 %add4, i32* %sparse_list_size5, align 4, !dbg !3128
  %14 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !3129
  %sparse_list_size6 = getelementptr inbounds %struct.tree, %struct.tree* %14, i32 0, i32 25, !dbg !3130
  %15 = load i32, i32* %sparse_list_size6, align 4, !dbg !3130
  %conv = sext i32 %15 to i64, !dbg !3129
  %mul = mul i64 16, %conv, !dbg !3131
  %call7 = call noalias i8* @malloc(i64 %mul) #6, !dbg !3132
  %16 = bitcast i8* %call7 to %struct.entry_sparse*, !dbg !3132
  %17 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !3133
  %sparse_list8 = getelementptr inbounds %struct.tree, %struct.tree* %17, i32 0, i32 22, !dbg !3134
  store %struct.entry_sparse* %16, %struct.entry_sparse** %sparse_list8, align 8, !dbg !3135
  %18 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !3136
  %sparse_list9 = getelementptr inbounds %struct.tree, %struct.tree* %18, i32 0, i32 22, !dbg !3138
  %19 = load %struct.entry_sparse*, %struct.entry_sparse** %sparse_list9, align 8, !dbg !3138
  %cmp10 = icmp eq %struct.entry_sparse* %19, null, !dbg !3139
  br i1 %cmp10, label %if.then12, label %if.end, !dbg !3140

if.then12:                                        ; preds = %if.then
  %20 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !3141
  %sparse_list_size13 = getelementptr inbounds %struct.tree, %struct.tree* %20, i32 0, i32 25, !dbg !3143
  store i32 0, i32* %sparse_list_size13, align 4, !dbg !3144
  %21 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !3145
  %archive = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %21, i32 0, i32 0, !dbg !3146
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.34, i32 0, i32 0)), !dbg !3147
  %22 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !3148
  %archive14 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %22, i32 0, i32 0, !dbg !3149
  %state = getelementptr inbounds %struct.archive, %struct.archive* %archive14, i32 0, i32 1, !dbg !3150
  store i32 32768, i32* %state, align 4, !dbg !3151
  store i32 -30, i32* %retval, align 4, !dbg !3152
  br label %return, !dbg !3152

if.end:                                           ; preds = %if.then
  br label %if.end15, !dbg !3153

if.end15:                                         ; preds = %if.end, %entry
  store i32 0, i32* %i, align 4, !dbg !3154
  br label %for.cond, !dbg !3156

for.cond:                                         ; preds = %for.inc, %if.end15
  %23 = load i32, i32* %i, align 4, !dbg !3157
  %24 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !3160
  %sparse_count16 = getelementptr inbounds %struct.tree, %struct.tree* %24, i32 0, i32 24, !dbg !3161
  %25 = load i32, i32* %sparse_count16, align 8, !dbg !3161
  %cmp17 = icmp slt i32 %23, %25, !dbg !3162
  br i1 %cmp17, label %for.body, label %for.end, !dbg !3163

for.body:                                         ; preds = %for.cond
  %26 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3164
  %call19 = call i32 @archive_entry_sparse_next(%struct.archive_entry* %26, i64* %offset, i64* %length), !dbg !3166
  %27 = load i64, i64* %offset, align 8, !dbg !3167
  %28 = load i32, i32* %i, align 4, !dbg !3168
  %idxprom = sext i32 %28 to i64, !dbg !3169
  %29 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !3169
  %sparse_list20 = getelementptr inbounds %struct.tree, %struct.tree* %29, i32 0, i32 22, !dbg !3170
  %30 = load %struct.entry_sparse*, %struct.entry_sparse** %sparse_list20, align 8, !dbg !3170
  %arrayidx = getelementptr inbounds %struct.entry_sparse, %struct.entry_sparse* %30, i64 %idxprom, !dbg !3169
  %offset21 = getelementptr inbounds %struct.entry_sparse, %struct.entry_sparse* %arrayidx, i32 0, i32 1, !dbg !3171
  store i64 %27, i64* %offset21, align 8, !dbg !3172
  %31 = load i64, i64* %length, align 8, !dbg !3173
  %32 = load i32, i32* %i, align 4, !dbg !3174
  %idxprom22 = sext i32 %32 to i64, !dbg !3175
  %33 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !3175
  %sparse_list23 = getelementptr inbounds %struct.tree, %struct.tree* %33, i32 0, i32 22, !dbg !3176
  %34 = load %struct.entry_sparse*, %struct.entry_sparse** %sparse_list23, align 8, !dbg !3176
  %arrayidx24 = getelementptr inbounds %struct.entry_sparse, %struct.entry_sparse* %34, i64 %idxprom22, !dbg !3175
  %length25 = getelementptr inbounds %struct.entry_sparse, %struct.entry_sparse* %arrayidx24, i32 0, i32 0, !dbg !3177
  store i64 %31, i64* %length25, align 8, !dbg !3178
  br label %for.inc, !dbg !3179

for.inc:                                          ; preds = %for.body
  %35 = load i32, i32* %i, align 4, !dbg !3180
  %inc = add nsw i32 %35, 1, !dbg !3180
  store i32 %inc, i32* %i, align 4, !dbg !3180
  br label %for.cond, !dbg !3182

for.end:                                          ; preds = %for.cond
  %36 = load i32, i32* %i, align 4, !dbg !3183
  %cmp26 = icmp eq i32 %36, 0, !dbg !3185
  br i1 %cmp26, label %if.then28, label %if.else, !dbg !3186

if.then28:                                        ; preds = %for.end
  %37 = load i32, i32* %i, align 4, !dbg !3187
  %idxprom29 = sext i32 %37 to i64, !dbg !3189
  %38 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !3189
  %sparse_list30 = getelementptr inbounds %struct.tree, %struct.tree* %38, i32 0, i32 22, !dbg !3190
  %39 = load %struct.entry_sparse*, %struct.entry_sparse** %sparse_list30, align 8, !dbg !3190
  %arrayidx31 = getelementptr inbounds %struct.entry_sparse, %struct.entry_sparse* %39, i64 %idxprom29, !dbg !3189
  %offset32 = getelementptr inbounds %struct.entry_sparse, %struct.entry_sparse* %arrayidx31, i32 0, i32 1, !dbg !3191
  store i64 0, i64* %offset32, align 8, !dbg !3192
  %40 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3193
  %call33 = call i64 @archive_entry_size(%struct.archive_entry* %40), !dbg !3194
  %41 = load i32, i32* %i, align 4, !dbg !3195
  %idxprom34 = sext i32 %41 to i64, !dbg !3196
  %42 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !3196
  %sparse_list35 = getelementptr inbounds %struct.tree, %struct.tree* %42, i32 0, i32 22, !dbg !3197
  %43 = load %struct.entry_sparse*, %struct.entry_sparse** %sparse_list35, align 8, !dbg !3197
  %arrayidx36 = getelementptr inbounds %struct.entry_sparse, %struct.entry_sparse* %43, i64 %idxprom34, !dbg !3196
  %length37 = getelementptr inbounds %struct.entry_sparse, %struct.entry_sparse* %arrayidx36, i32 0, i32 0, !dbg !3198
  store i64 %call33, i64* %length37, align 8, !dbg !3199
  br label %if.end47, !dbg !3200

if.else:                                          ; preds = %for.end
  %44 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3201
  %call38 = call i64 @archive_entry_size(%struct.archive_entry* %44), !dbg !3203
  %45 = load i32, i32* %i, align 4, !dbg !3204
  %idxprom39 = sext i32 %45 to i64, !dbg !3205
  %46 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !3205
  %sparse_list40 = getelementptr inbounds %struct.tree, %struct.tree* %46, i32 0, i32 22, !dbg !3206
  %47 = load %struct.entry_sparse*, %struct.entry_sparse** %sparse_list40, align 8, !dbg !3206
  %arrayidx41 = getelementptr inbounds %struct.entry_sparse, %struct.entry_sparse* %47, i64 %idxprom39, !dbg !3205
  %offset42 = getelementptr inbounds %struct.entry_sparse, %struct.entry_sparse* %arrayidx41, i32 0, i32 1, !dbg !3207
  store i64 %call38, i64* %offset42, align 8, !dbg !3208
  %48 = load i32, i32* %i, align 4, !dbg !3209
  %idxprom43 = sext i32 %48 to i64, !dbg !3210
  %49 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !3210
  %sparse_list44 = getelementptr inbounds %struct.tree, %struct.tree* %49, i32 0, i32 22, !dbg !3211
  %50 = load %struct.entry_sparse*, %struct.entry_sparse** %sparse_list44, align 8, !dbg !3211
  %arrayidx45 = getelementptr inbounds %struct.entry_sparse, %struct.entry_sparse* %50, i64 %idxprom43, !dbg !3210
  %length46 = getelementptr inbounds %struct.entry_sparse, %struct.entry_sparse* %arrayidx45, i32 0, i32 0, !dbg !3212
  store i64 0, i64* %length46, align 8, !dbg !3213
  br label %if.end47

if.end47:                                         ; preds = %if.else, %if.then28
  %51 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !3214
  %sparse_list48 = getelementptr inbounds %struct.tree, %struct.tree* %51, i32 0, i32 22, !dbg !3215
  %52 = load %struct.entry_sparse*, %struct.entry_sparse** %sparse_list48, align 8, !dbg !3215
  %53 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !3216
  %current_sparse = getelementptr inbounds %struct.tree, %struct.tree* %53, i32 0, i32 23, !dbg !3217
  store %struct.entry_sparse* %52, %struct.entry_sparse** %current_sparse, align 8, !dbg !3218
  store i32 0, i32* %retval, align 4, !dbg !3219
  br label %return, !dbg !3219

return:                                           ; preds = %if.end47, %if.then12
  %54 = load i32, i32* %retval, align 4, !dbg !3220
  ret i32 %54, !dbg !3220
}

declare void @__archive_reset_read_data(%struct.archive*) #2

; Function Attrs: nounwind uwtable
define internal i32 @tree_next(%struct.tree* %t) #0 !dbg !399 {
entry:
  %retval = alloca i32, align 4
  %t.addr = alloca %struct.tree*, align 8
  %r = alloca i32, align 4
  store %struct.tree* %t, %struct.tree** %t.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tree** %t.addr, metadata !3221, metadata !460), !dbg !3222
  call void @llvm.dbg.declare(metadata i32* %r, metadata !3223, metadata !460), !dbg !3224
  br label %while.cond, !dbg !3225

while.cond:                                       ; preds = %if.end69, %if.then49, %if.then3, %entry
  %0 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3226
  %stack = getelementptr inbounds %struct.tree, %struct.tree* %0, i32 0, i32 0, !dbg !3228
  %1 = load %struct.tree_entry*, %struct.tree_entry** %stack, align 8, !dbg !3228
  %cmp = icmp ne %struct.tree_entry* %1, null, !dbg !3229
  br i1 %cmp, label %while.body, label %while.end, !dbg !3230

while.body:                                       ; preds = %while.cond
  %2 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3231
  %d = getelementptr inbounds %struct.tree, %struct.tree* %2, i32 0, i32 2, !dbg !3234
  %3 = load %struct.__dirstream*, %struct.__dirstream** %d, align 8, !dbg !3234
  %cmp1 = icmp ne %struct.__dirstream* %3, null, !dbg !3235
  br i1 %cmp1, label %if.then, label %if.end4, !dbg !3236

if.then:                                          ; preds = %while.body
  %4 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3237
  %call = call i32 @tree_dir_next_posix(%struct.tree* %4), !dbg !3239
  store i32 %call, i32* %r, align 4, !dbg !3240
  %5 = load i32, i32* %r, align 4, !dbg !3241
  %cmp2 = icmp eq i32 %5, 0, !dbg !3243
  br i1 %cmp2, label %if.then3, label %if.end, !dbg !3244

if.then3:                                         ; preds = %if.then
  br label %while.cond, !dbg !3245

if.end:                                           ; preds = %if.then
  %6 = load i32, i32* %r, align 4, !dbg !3246
  store i32 %6, i32* %retval, align 4, !dbg !3247
  br label %return, !dbg !3247

if.end4:                                          ; preds = %while.body
  %7 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3248
  %stack5 = getelementptr inbounds %struct.tree, %struct.tree* %7, i32 0, i32 0, !dbg !3250
  %8 = load %struct.tree_entry*, %struct.tree_entry** %stack5, align 8, !dbg !3250
  %flags = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %8, i32 0, i32 7, !dbg !3251
  %9 = load i32, i32* %flags, align 8, !dbg !3251
  %and = and i32 %9, 4, !dbg !3252
  %tobool = icmp ne i32 %and, 0, !dbg !3252
  br i1 %tobool, label %if.then6, label %if.else, !dbg !3253

if.then6:                                         ; preds = %if.end4
  %10 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3254
  %stack7 = getelementptr inbounds %struct.tree, %struct.tree* %10, i32 0, i32 0, !dbg !3256
  %11 = load %struct.tree_entry*, %struct.tree_entry** %stack7, align 8, !dbg !3256
  %12 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3257
  %current = getelementptr inbounds %struct.tree, %struct.tree* %12, i32 0, i32 1, !dbg !3258
  store %struct.tree_entry* %11, %struct.tree_entry** %current, align 8, !dbg !3259
  %13 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3260
  %14 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3261
  %stack8 = getelementptr inbounds %struct.tree, %struct.tree* %14, i32 0, i32 0, !dbg !3262
  %15 = load %struct.tree_entry*, %struct.tree_entry** %stack8, align 8, !dbg !3262
  %name = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %15, i32 0, i32 3, !dbg !3263
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %name, i32 0, i32 0, !dbg !3264
  %16 = load i8*, i8** %s, align 8, !dbg !3264
  %17 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3265
  %stack9 = getelementptr inbounds %struct.tree, %struct.tree* %17, i32 0, i32 0, !dbg !3265
  %18 = load %struct.tree_entry*, %struct.tree_entry** %stack9, align 8, !dbg !3265
  %name10 = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %18, i32 0, i32 3, !dbg !3265
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %name10, i32 0, i32 1, !dbg !3265
  %19 = load i64, i64* %length, align 8, !dbg !3265
  call void @tree_append(%struct.tree* %13, i8* %16, i64 %19), !dbg !3266
  %20 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3267
  %stack11 = getelementptr inbounds %struct.tree, %struct.tree* %20, i32 0, i32 0, !dbg !3268
  %21 = load %struct.tree_entry*, %struct.tree_entry** %stack11, align 8, !dbg !3268
  %flags12 = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %21, i32 0, i32 7, !dbg !3269
  %22 = load i32, i32* %flags12, align 8, !dbg !3270
  %and13 = and i32 %22, -5, !dbg !3270
  store i32 %and13, i32* %flags12, align 8, !dbg !3270
  %23 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3271
  %visit_type = getelementptr inbounds %struct.tree, %struct.tree* %23, i32 0, i32 7, !dbg !3272
  store i32 1, i32* %visit_type, align 4, !dbg !3273
  store i32 1, i32* %retval, align 4, !dbg !3274
  br label %return, !dbg !3274

if.else:                                          ; preds = %if.end4
  %24 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3275
  %stack14 = getelementptr inbounds %struct.tree, %struct.tree* %24, i32 0, i32 0, !dbg !3277
  %25 = load %struct.tree_entry*, %struct.tree_entry** %stack14, align 8, !dbg !3277
  %flags15 = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %25, i32 0, i32 7, !dbg !3278
  %26 = load i32, i32* %flags15, align 8, !dbg !3278
  %and16 = and i32 %26, 8, !dbg !3279
  %tobool17 = icmp ne i32 %and16, 0, !dbg !3279
  br i1 %tobool17, label %if.then18, label %if.else38, !dbg !3280

if.then18:                                        ; preds = %if.else
  %27 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3281
  %stack19 = getelementptr inbounds %struct.tree, %struct.tree* %27, i32 0, i32 0, !dbg !3283
  %28 = load %struct.tree_entry*, %struct.tree_entry** %stack19, align 8, !dbg !3283
  %29 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3284
  %current20 = getelementptr inbounds %struct.tree, %struct.tree* %29, i32 0, i32 1, !dbg !3285
  store %struct.tree_entry* %28, %struct.tree_entry** %current20, align 8, !dbg !3286
  %30 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3287
  %31 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3288
  %stack21 = getelementptr inbounds %struct.tree, %struct.tree* %31, i32 0, i32 0, !dbg !3289
  %32 = load %struct.tree_entry*, %struct.tree_entry** %stack21, align 8, !dbg !3289
  %name22 = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %32, i32 0, i32 3, !dbg !3290
  %s23 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %name22, i32 0, i32 0, !dbg !3291
  %33 = load i8*, i8** %s23, align 8, !dbg !3291
  %34 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3292
  %stack24 = getelementptr inbounds %struct.tree, %struct.tree* %34, i32 0, i32 0, !dbg !3292
  %35 = load %struct.tree_entry*, %struct.tree_entry** %stack24, align 8, !dbg !3292
  %name25 = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %35, i32 0, i32 3, !dbg !3292
  %length26 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %name25, i32 0, i32 1, !dbg !3292
  %36 = load i64, i64* %length26, align 8, !dbg !3292
  call void @tree_append(%struct.tree* %30, i8* %33, i64 %36), !dbg !3293
  %37 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3294
  %stack27 = getelementptr inbounds %struct.tree, %struct.tree* %37, i32 0, i32 0, !dbg !3295
  %38 = load %struct.tree_entry*, %struct.tree_entry** %stack27, align 8, !dbg !3295
  %flags28 = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %38, i32 0, i32 7, !dbg !3296
  %39 = load i32, i32* %flags28, align 8, !dbg !3297
  %and29 = and i32 %39, -9, !dbg !3297
  store i32 %and29, i32* %flags28, align 8, !dbg !3297
  %40 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3298
  %call30 = call i32 @tree_descent(%struct.tree* %40), !dbg !3299
  store i32 %call30, i32* %r, align 4, !dbg !3300
  %41 = load i32, i32* %r, align 4, !dbg !3301
  %cmp31 = icmp ne i32 %41, 0, !dbg !3303
  br i1 %cmp31, label %if.then32, label %if.else34, !dbg !3304

if.then32:                                        ; preds = %if.then18
  %42 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3305
  call void @tree_pop(%struct.tree* %42), !dbg !3307
  %43 = load i32, i32* %r, align 4, !dbg !3308
  %44 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3309
  %visit_type33 = getelementptr inbounds %struct.tree, %struct.tree* %44, i32 0, i32 7, !dbg !3310
  store i32 %43, i32* %visit_type33, align 4, !dbg !3311
  br label %if.end36, !dbg !3312

if.else34:                                        ; preds = %if.then18
  %45 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3313
  %visit_type35 = getelementptr inbounds %struct.tree, %struct.tree* %45, i32 0, i32 7, !dbg !3314
  store i32 2, i32* %visit_type35, align 4, !dbg !3315
  br label %if.end36

if.end36:                                         ; preds = %if.else34, %if.then32
  %46 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3316
  %visit_type37 = getelementptr inbounds %struct.tree, %struct.tree* %46, i32 0, i32 7, !dbg !3317
  %47 = load i32, i32* %visit_type37, align 4, !dbg !3317
  store i32 %47, i32* %retval, align 4, !dbg !3318
  br label %return, !dbg !3318

if.else38:                                        ; preds = %if.else
  %48 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3319
  %stack39 = getelementptr inbounds %struct.tree, %struct.tree* %48, i32 0, i32 0, !dbg !3321
  %49 = load %struct.tree_entry*, %struct.tree_entry** %stack39, align 8, !dbg !3321
  %flags40 = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %49, i32 0, i32 7, !dbg !3322
  %50 = load i32, i32* %flags40, align 8, !dbg !3322
  %and41 = and i32 %50, 16, !dbg !3323
  %tobool42 = icmp ne i32 %and41, 0, !dbg !3323
  br i1 %tobool42, label %if.then43, label %if.else51, !dbg !3324

if.then43:                                        ; preds = %if.else38
  %51 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3325
  %stack44 = getelementptr inbounds %struct.tree, %struct.tree* %51, i32 0, i32 0, !dbg !3327
  %52 = load %struct.tree_entry*, %struct.tree_entry** %stack44, align 8, !dbg !3327
  %flags45 = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %52, i32 0, i32 7, !dbg !3328
  %53 = load i32, i32* %flags45, align 8, !dbg !3329
  %and46 = and i32 %53, -17, !dbg !3329
  store i32 %and46, i32* %flags45, align 8, !dbg !3329
  %54 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3330
  %call47 = call i32 @tree_dir_next_posix(%struct.tree* %54), !dbg !3331
  store i32 %call47, i32* %r, align 4, !dbg !3332
  %55 = load i32, i32* %r, align 4, !dbg !3333
  %cmp48 = icmp eq i32 %55, 0, !dbg !3335
  br i1 %cmp48, label %if.then49, label %if.end50, !dbg !3336

if.then49:                                        ; preds = %if.then43
  br label %while.cond, !dbg !3337

if.end50:                                         ; preds = %if.then43
  %56 = load i32, i32* %r, align 4, !dbg !3338
  store i32 %56, i32* %retval, align 4, !dbg !3339
  br label %return, !dbg !3339

if.else51:                                        ; preds = %if.else38
  %57 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3340
  %stack52 = getelementptr inbounds %struct.tree, %struct.tree* %57, i32 0, i32 0, !dbg !3342
  %58 = load %struct.tree_entry*, %struct.tree_entry** %stack52, align 8, !dbg !3342
  %flags53 = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %58, i32 0, i32 7, !dbg !3343
  %59 = load i32, i32* %flags53, align 8, !dbg !3343
  %and54 = and i32 %59, 32, !dbg !3344
  %tobool55 = icmp ne i32 %and54, 0, !dbg !3344
  br i1 %tobool55, label %if.then56, label %if.else61, !dbg !3345

if.then56:                                        ; preds = %if.else51
  %60 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3346
  %call57 = call i32 @tree_ascend(%struct.tree* %60), !dbg !3348
  store i32 %call57, i32* %r, align 4, !dbg !3349
  %61 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3350
  call void @tree_pop(%struct.tree* %61), !dbg !3351
  %62 = load i32, i32* %r, align 4, !dbg !3352
  %cmp58 = icmp ne i32 %62, 0, !dbg !3353
  br i1 %cmp58, label %cond.true, label %cond.false, !dbg !3352

cond.true:                                        ; preds = %if.then56
  %63 = load i32, i32* %r, align 4, !dbg !3354
  br label %cond.end, !dbg !3356

cond.false:                                       ; preds = %if.then56
  br label %cond.end, !dbg !3357

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ %63, %cond.true ], [ 3, %cond.false ], !dbg !3359
  %64 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3361
  %visit_type59 = getelementptr inbounds %struct.tree, %struct.tree* %64, i32 0, i32 7, !dbg !3362
  store i32 %cond, i32* %visit_type59, align 4, !dbg !3363
  %65 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3364
  %visit_type60 = getelementptr inbounds %struct.tree, %struct.tree* %65, i32 0, i32 7, !dbg !3365
  %66 = load i32, i32* %visit_type60, align 4, !dbg !3365
  store i32 %66, i32* %retval, align 4, !dbg !3366
  br label %return, !dbg !3366

if.else61:                                        ; preds = %if.else51
  %67 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3367
  call void @tree_pop(%struct.tree* %67), !dbg !3369
  %68 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3370
  %flags62 = getelementptr inbounds %struct.tree, %struct.tree* %68, i32 0, i32 6, !dbg !3371
  %69 = load i32, i32* %flags62, align 8, !dbg !3372
  %and63 = and i32 %69, -33, !dbg !3372
  store i32 %and63, i32* %flags62, align 8, !dbg !3372
  %70 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3373
  %flags64 = getelementptr inbounds %struct.tree, %struct.tree* %70, i32 0, i32 6, !dbg !3374
  %71 = load i32, i32* %flags64, align 8, !dbg !3375
  %and65 = and i32 %71, -17, !dbg !3375
  store i32 %and65, i32* %flags64, align 8, !dbg !3375
  br label %if.end66

if.end66:                                         ; preds = %if.else61
  br label %if.end67

if.end67:                                         ; preds = %if.end66
  br label %if.end68

if.end68:                                         ; preds = %if.end67
  br label %if.end69

if.end69:                                         ; preds = %if.end68
  br label %while.cond, !dbg !3376

while.end:                                        ; preds = %while.cond
  %72 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3378
  %visit_type70 = getelementptr inbounds %struct.tree, %struct.tree* %72, i32 0, i32 7, !dbg !3379
  store i32 0, i32* %visit_type70, align 4, !dbg !3380
  store i32 0, i32* %retval, align 4, !dbg !3381
  br label %return, !dbg !3381

return:                                           ; preds = %while.end, %cond.end, %if.end50, %if.end36, %if.then6, %if.end
  %73 = load i32, i32* %retval, align 4, !dbg !3382
  ret i32 %73, !dbg !3382
}

; Function Attrs: nounwind uwtable
define internal %struct.stat* @tree_current_lstat(%struct.tree* %t) #0 !dbg !409 {
entry:
  %retval = alloca %struct.stat*, align 8
  %t.addr = alloca %struct.tree*, align 8
  store %struct.tree* %t, %struct.tree** %t.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tree** %t.addr, metadata !3383, metadata !460), !dbg !3384
  %0 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3385
  %flags = getelementptr inbounds %struct.tree, %struct.tree* %0, i32 0, i32 6, !dbg !3387
  %1 = load i32, i32* %flags, align 8, !dbg !3387
  %and = and i32 %1, 32, !dbg !3388
  %tobool = icmp ne i32 %and, 0, !dbg !3388
  br i1 %tobool, label %if.end5, label %if.then, !dbg !3389

if.then:                                          ; preds = %entry
  %2 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3390
  %call = call i32 @tree_current_dir_fd(%struct.tree* %2), !dbg !3393
  %3 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3394
  %call1 = call i8* @tree_current_access_path(%struct.tree* %3), !dbg !3395
  %4 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3396
  %lst = getelementptr inbounds %struct.tree, %struct.tree* %4, i32 0, i32 17, !dbg !3397
  %call2 = call i32 @fstatat(i32 %call, i8* %call1, %struct.stat* %lst, i32 256) #6, !dbg !3398
  %cmp = icmp ne i32 %call2, 0, !dbg !3399
  br i1 %cmp, label %if.then3, label %if.end, !dbg !3400

if.then3:                                         ; preds = %if.then
  store %struct.stat* null, %struct.stat** %retval, align 8, !dbg !3401
  br label %return, !dbg !3401

if.end:                                           ; preds = %if.then
  %5 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3402
  %flags4 = getelementptr inbounds %struct.tree, %struct.tree* %5, i32 0, i32 6, !dbg !3403
  %6 = load i32, i32* %flags4, align 8, !dbg !3404
  %or = or i32 %6, 32, !dbg !3404
  store i32 %or, i32* %flags4, align 8, !dbg !3404
  br label %if.end5, !dbg !3405

if.end5:                                          ; preds = %if.end, %entry
  %7 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3406
  %lst6 = getelementptr inbounds %struct.tree, %struct.tree* %7, i32 0, i32 17, !dbg !3407
  store %struct.stat* %lst6, %struct.stat** %retval, align 8, !dbg !3408
  br label %return, !dbg !3408

return:                                           ; preds = %if.end5, %if.then3
  %8 = load %struct.stat*, %struct.stat** %retval, align 8, !dbg !3409
  ret %struct.stat* %8, !dbg !3409
}

declare void @archive_entry_copy_pathname(%struct.archive_entry*, i8*) #2

declare i32 @archive_match_path_excluded(%struct.archive*, %struct.archive_entry*) #2

declare i8* @archive_error_string(%struct.archive*) #2

; Function Attrs: nounwind uwtable
define internal %struct.stat* @tree_current_stat(%struct.tree* %t) #0 !dbg !414 {
entry:
  %retval = alloca %struct.stat*, align 8
  %t.addr = alloca %struct.tree*, align 8
  store %struct.tree* %t, %struct.tree** %t.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tree** %t.addr, metadata !3410, metadata !460), !dbg !3411
  %0 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3412
  %flags = getelementptr inbounds %struct.tree, %struct.tree* %0, i32 0, i32 6, !dbg !3414
  %1 = load i32, i32* %flags, align 8, !dbg !3414
  %and = and i32 %1, 16, !dbg !3415
  %tobool = icmp ne i32 %and, 0, !dbg !3415
  br i1 %tobool, label %if.end5, label %if.then, !dbg !3416

if.then:                                          ; preds = %entry
  %2 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3417
  %call = call i32 @tree_current_dir_fd(%struct.tree* %2), !dbg !3420
  %3 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3421
  %call1 = call i8* @tree_current_access_path(%struct.tree* %3), !dbg !3422
  %4 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3423
  %st = getelementptr inbounds %struct.tree, %struct.tree* %4, i32 0, i32 18, !dbg !3424
  %call2 = call i32 @fstatat(i32 %call, i8* %call1, %struct.stat* %st, i32 0) #6, !dbg !3425
  %cmp = icmp ne i32 %call2, 0, !dbg !3426
  br i1 %cmp, label %if.then3, label %if.end, !dbg !3427

if.then3:                                         ; preds = %if.then
  store %struct.stat* null, %struct.stat** %retval, align 8, !dbg !3428
  br label %return, !dbg !3428

if.end:                                           ; preds = %if.then
  %5 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3429
  %flags4 = getelementptr inbounds %struct.tree, %struct.tree* %5, i32 0, i32 6, !dbg !3430
  %6 = load i32, i32* %flags4, align 8, !dbg !3431
  %or = or i32 %6, 16, !dbg !3431
  store i32 %or, i32* %flags4, align 8, !dbg !3431
  br label %if.end5, !dbg !3432

if.end5:                                          ; preds = %if.end, %entry
  %7 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3433
  %st6 = getelementptr inbounds %struct.tree, %struct.tree* %7, i32 0, i32 18, !dbg !3434
  store %struct.stat* %st6, %struct.stat** %retval, align 8, !dbg !3435
  br label %return, !dbg !3435

return:                                           ; preds = %if.end5, %if.then3
  %8 = load %struct.stat*, %struct.stat** %retval, align 8, !dbg !3436
  ret %struct.stat* %8, !dbg !3436
}

; Function Attrs: nounwind uwtable
define internal i32 @tree_target_is_same_as_parent(%struct.tree* %t, %struct.stat* %st) #0 !dbg !415 {
entry:
  %retval = alloca i32, align 4
  %t.addr = alloca %struct.tree*, align 8
  %st.addr = alloca %struct.stat*, align 8
  %te = alloca %struct.tree_entry*, align 8
  store %struct.tree* %t, %struct.tree** %t.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tree** %t.addr, metadata !3437, metadata !460), !dbg !3438
  store %struct.stat* %st, %struct.stat** %st.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.stat** %st.addr, metadata !3439, metadata !460), !dbg !3440
  call void @llvm.dbg.declare(metadata %struct.tree_entry** %te, metadata !3441, metadata !460), !dbg !3442
  %0 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3443
  %current = getelementptr inbounds %struct.tree, %struct.tree* %0, i32 0, i32 1, !dbg !3445
  %1 = load %struct.tree_entry*, %struct.tree_entry** %current, align 8, !dbg !3445
  %parent = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %1, i32 0, i32 2, !dbg !3446
  %2 = load %struct.tree_entry*, %struct.tree_entry** %parent, align 8, !dbg !3446
  store %struct.tree_entry* %2, %struct.tree_entry** %te, align 8, !dbg !3447
  br label %for.cond, !dbg !3448

for.cond:                                         ; preds = %for.inc, %entry
  %3 = load %struct.tree_entry*, %struct.tree_entry** %te, align 8, !dbg !3449
  %cmp = icmp ne %struct.tree_entry* %3, null, !dbg !3452
  br i1 %cmp, label %for.body, label %for.end, !dbg !3453

for.body:                                         ; preds = %for.cond
  %4 = load %struct.tree_entry*, %struct.tree_entry** %te, align 8, !dbg !3454
  %dev = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %4, i32 0, i32 5, !dbg !3457
  %5 = load i64, i64* %dev, align 8, !dbg !3457
  %6 = load %struct.stat*, %struct.stat** %st.addr, align 8, !dbg !3458
  %st_dev = getelementptr inbounds %struct.stat, %struct.stat* %6, i32 0, i32 0, !dbg !3459
  %7 = load i64, i64* %st_dev, align 8, !dbg !3459
  %cmp1 = icmp eq i64 %5, %7, !dbg !3460
  br i1 %cmp1, label %land.lhs.true, label %if.end, !dbg !3461

land.lhs.true:                                    ; preds = %for.body
  %8 = load %struct.tree_entry*, %struct.tree_entry** %te, align 8, !dbg !3462
  %ino = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %8, i32 0, i32 6, !dbg !3463
  %9 = load i64, i64* %ino, align 8, !dbg !3463
  %10 = load %struct.stat*, %struct.stat** %st.addr, align 8, !dbg !3464
  %st_ino = getelementptr inbounds %struct.stat, %struct.stat* %10, i32 0, i32 1, !dbg !3465
  %11 = load i64, i64* %st_ino, align 8, !dbg !3465
  %cmp2 = icmp eq i64 %9, %11, !dbg !3466
  br i1 %cmp2, label %if.then, label %if.end, !dbg !3467

if.then:                                          ; preds = %land.lhs.true
  store i32 1, i32* %retval, align 4, !dbg !3469
  br label %return, !dbg !3469

if.end:                                           ; preds = %land.lhs.true, %for.body
  br label %for.inc, !dbg !3470

for.inc:                                          ; preds = %if.end
  %12 = load %struct.tree_entry*, %struct.tree_entry** %te, align 8, !dbg !3471
  %parent3 = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %12, i32 0, i32 2, !dbg !3473
  %13 = load %struct.tree_entry*, %struct.tree_entry** %parent3, align 8, !dbg !3473
  store %struct.tree_entry* %13, %struct.tree_entry** %te, align 8, !dbg !3474
  br label %for.cond, !dbg !3475

for.end:                                          ; preds = %for.cond
  store i32 0, i32* %retval, align 4, !dbg !3476
  br label %return, !dbg !3476

return:                                           ; preds = %for.end, %if.then
  %14 = load i32, i32* %retval, align 4, !dbg !3477
  ret i32 %14, !dbg !3477
}

; Function Attrs: nounwind uwtable
define internal i32 @update_current_filesystem(%struct.archive_read_disk* %a, i64 %dev) #0 !dbg !418 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read_disk*, align 8
  %dev.addr = alloca i64, align 8
  %t = alloca %struct.tree*, align 8
  %i = alloca i32, align 4
  %fid = alloca i32, align 4
  %s = alloca i64, align 8
  %p = alloca i8*, align 8
  store %struct.archive_read_disk* %a, %struct.archive_read_disk** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_disk** %a.addr, metadata !3478, metadata !460), !dbg !3479
  store i64 %dev, i64* %dev.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %dev.addr, metadata !3480, metadata !460), !dbg !3481
  call void @llvm.dbg.declare(metadata %struct.tree** %t, metadata !3482, metadata !460), !dbg !3483
  %0 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !3484
  %tree = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %0, i32 0, i32 4, !dbg !3485
  %1 = load %struct.tree*, %struct.tree** %tree, align 8, !dbg !3485
  store %struct.tree* %1, %struct.tree** %t, align 8, !dbg !3483
  call void @llvm.dbg.declare(metadata i32* %i, metadata !3486, metadata !460), !dbg !3487
  call void @llvm.dbg.declare(metadata i32* %fid, metadata !3488, metadata !460), !dbg !3489
  %2 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !3490
  %current_filesystem = getelementptr inbounds %struct.tree, %struct.tree* %2, i32 0, i32 28, !dbg !3492
  %3 = load %struct.filesystem*, %struct.filesystem** %current_filesystem, align 8, !dbg !3492
  %cmp = icmp ne %struct.filesystem* %3, null, !dbg !3493
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !3494

land.lhs.true:                                    ; preds = %entry
  %4 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !3495
  %current_filesystem1 = getelementptr inbounds %struct.tree, %struct.tree* %4, i32 0, i32 28, !dbg !3496
  %5 = load %struct.filesystem*, %struct.filesystem** %current_filesystem1, align 8, !dbg !3496
  %dev2 = getelementptr inbounds %struct.filesystem, %struct.filesystem* %5, i32 0, i32 0, !dbg !3497
  %6 = load i64, i64* %dev2, align 8, !dbg !3497
  %7 = load i64, i64* %dev.addr, align 8, !dbg !3498
  %cmp3 = icmp eq i64 %6, %7, !dbg !3499
  br i1 %cmp3, label %if.then, label %if.end, !dbg !3500

if.then:                                          ; preds = %land.lhs.true
  store i32 0, i32* %retval, align 4, !dbg !3502
  br label %return, !dbg !3502

if.end:                                           ; preds = %land.lhs.true, %entry
  store i32 0, i32* %i, align 4, !dbg !3503
  br label %for.cond, !dbg !3505

for.cond:                                         ; preds = %for.inc, %if.end
  %8 = load i32, i32* %i, align 4, !dbg !3506
  %9 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !3509
  %max_filesystem_id = getelementptr inbounds %struct.tree, %struct.tree* %9, i32 0, i32 32, !dbg !3510
  %10 = load i32, i32* %max_filesystem_id, align 8, !dbg !3510
  %cmp4 = icmp slt i32 %8, %10, !dbg !3511
  br i1 %cmp4, label %for.body, label %for.end, !dbg !3512

for.body:                                         ; preds = %for.cond
  %11 = load i32, i32* %i, align 4, !dbg !3513
  %idxprom = sext i32 %11 to i64, !dbg !3516
  %12 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !3516
  %filesystem_table = getelementptr inbounds %struct.tree, %struct.tree* %12, i32 0, i32 29, !dbg !3517
  %13 = load %struct.filesystem*, %struct.filesystem** %filesystem_table, align 8, !dbg !3517
  %arrayidx = getelementptr inbounds %struct.filesystem, %struct.filesystem* %13, i64 %idxprom, !dbg !3516
  %dev5 = getelementptr inbounds %struct.filesystem, %struct.filesystem* %arrayidx, i32 0, i32 0, !dbg !3518
  %14 = load i64, i64* %dev5, align 8, !dbg !3518
  %15 = load i64, i64* %dev.addr, align 8, !dbg !3519
  %cmp6 = icmp eq i64 %14, %15, !dbg !3520
  br i1 %cmp6, label %if.then7, label %if.end12, !dbg !3521

if.then7:                                         ; preds = %for.body
  %16 = load i32, i32* %i, align 4, !dbg !3522
  %17 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !3524
  %current_filesystem_id = getelementptr inbounds %struct.tree, %struct.tree* %17, i32 0, i32 31, !dbg !3525
  store i32 %16, i32* %current_filesystem_id, align 4, !dbg !3526
  %18 = load i32, i32* %i, align 4, !dbg !3527
  %idxprom8 = sext i32 %18 to i64, !dbg !3528
  %19 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !3528
  %filesystem_table9 = getelementptr inbounds %struct.tree, %struct.tree* %19, i32 0, i32 29, !dbg !3529
  %20 = load %struct.filesystem*, %struct.filesystem** %filesystem_table9, align 8, !dbg !3529
  %arrayidx10 = getelementptr inbounds %struct.filesystem, %struct.filesystem* %20, i64 %idxprom8, !dbg !3528
  %21 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !3530
  %current_filesystem11 = getelementptr inbounds %struct.tree, %struct.tree* %21, i32 0, i32 28, !dbg !3531
  store %struct.filesystem* %arrayidx10, %struct.filesystem** %current_filesystem11, align 8, !dbg !3532
  store i32 0, i32* %retval, align 4, !dbg !3533
  br label %return, !dbg !3533

if.end12:                                         ; preds = %for.body
  br label %for.inc, !dbg !3534

for.inc:                                          ; preds = %if.end12
  %22 = load i32, i32* %i, align 4, !dbg !3535
  %inc = add nsw i32 %22, 1, !dbg !3535
  store i32 %inc, i32* %i, align 4, !dbg !3535
  br label %for.cond, !dbg !3537

for.end:                                          ; preds = %for.cond
  %23 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !3538
  %max_filesystem_id13 = getelementptr inbounds %struct.tree, %struct.tree* %23, i32 0, i32 32, !dbg !3539
  %24 = load i32, i32* %max_filesystem_id13, align 8, !dbg !3540
  %inc14 = add nsw i32 %24, 1, !dbg !3540
  store i32 %inc14, i32* %max_filesystem_id13, align 8, !dbg !3540
  store i32 %24, i32* %fid, align 4, !dbg !3541
  %25 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !3542
  %max_filesystem_id15 = getelementptr inbounds %struct.tree, %struct.tree* %25, i32 0, i32 32, !dbg !3544
  %26 = load i32, i32* %max_filesystem_id15, align 8, !dbg !3544
  %27 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !3545
  %allocated_filesystem = getelementptr inbounds %struct.tree, %struct.tree* %27, i32 0, i32 33, !dbg !3546
  %28 = load i32, i32* %allocated_filesystem, align 4, !dbg !3546
  %cmp16 = icmp sgt i32 %26, %28, !dbg !3547
  br i1 %cmp16, label %if.then17, label %if.end28, !dbg !3548

if.then17:                                        ; preds = %for.end
  call void @llvm.dbg.declare(metadata i64* %s, metadata !3549, metadata !460), !dbg !3551
  call void @llvm.dbg.declare(metadata i8** %p, metadata !3552, metadata !460), !dbg !3553
  %29 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !3554
  %max_filesystem_id18 = getelementptr inbounds %struct.tree, %struct.tree* %29, i32 0, i32 32, !dbg !3555
  %30 = load i32, i32* %max_filesystem_id18, align 8, !dbg !3555
  %mul = mul nsw i32 %30, 2, !dbg !3556
  %conv = sext i32 %mul to i64, !dbg !3554
  store i64 %conv, i64* %s, align 8, !dbg !3557
  %31 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !3558
  %filesystem_table19 = getelementptr inbounds %struct.tree, %struct.tree* %31, i32 0, i32 29, !dbg !3559
  %32 = load %struct.filesystem*, %struct.filesystem** %filesystem_table19, align 8, !dbg !3559
  %33 = bitcast %struct.filesystem* %32 to i8*, !dbg !3558
  %34 = load i64, i64* %s, align 8, !dbg !3560
  %mul20 = mul i64 %34, 88, !dbg !3561
  %call = call i8* @realloc(i8* %33, i64 %mul20) #6, !dbg !3562
  store i8* %call, i8** %p, align 8, !dbg !3563
  %35 = load i8*, i8** %p, align 8, !dbg !3564
  %cmp21 = icmp eq i8* %35, null, !dbg !3566
  br i1 %cmp21, label %if.then23, label %if.end24, !dbg !3567

if.then23:                                        ; preds = %if.then17
  %36 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !3568
  %archive = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %36, i32 0, i32 0, !dbg !3570
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.31, i32 0, i32 0)), !dbg !3571
  store i32 -30, i32* %retval, align 4, !dbg !3572
  br label %return, !dbg !3572

if.end24:                                         ; preds = %if.then17
  %37 = load i8*, i8** %p, align 8, !dbg !3573
  %38 = bitcast i8* %37 to %struct.filesystem*, !dbg !3574
  %39 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !3575
  %filesystem_table25 = getelementptr inbounds %struct.tree, %struct.tree* %39, i32 0, i32 29, !dbg !3576
  store %struct.filesystem* %38, %struct.filesystem** %filesystem_table25, align 8, !dbg !3577
  %40 = load i64, i64* %s, align 8, !dbg !3578
  %conv26 = trunc i64 %40 to i32, !dbg !3578
  %41 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !3579
  %allocated_filesystem27 = getelementptr inbounds %struct.tree, %struct.tree* %41, i32 0, i32 33, !dbg !3580
  store i32 %conv26, i32* %allocated_filesystem27, align 4, !dbg !3581
  br label %if.end28, !dbg !3582

if.end28:                                         ; preds = %if.end24, %for.end
  %42 = load i32, i32* %fid, align 4, !dbg !3583
  %43 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !3584
  %current_filesystem_id29 = getelementptr inbounds %struct.tree, %struct.tree* %43, i32 0, i32 31, !dbg !3585
  store i32 %42, i32* %current_filesystem_id29, align 4, !dbg !3586
  %44 = load i32, i32* %fid, align 4, !dbg !3587
  %idxprom30 = sext i32 %44 to i64, !dbg !3588
  %45 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !3588
  %filesystem_table31 = getelementptr inbounds %struct.tree, %struct.tree* %45, i32 0, i32 29, !dbg !3589
  %46 = load %struct.filesystem*, %struct.filesystem** %filesystem_table31, align 8, !dbg !3589
  %arrayidx32 = getelementptr inbounds %struct.filesystem, %struct.filesystem* %46, i64 %idxprom30, !dbg !3588
  %47 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !3590
  %current_filesystem33 = getelementptr inbounds %struct.tree, %struct.tree* %47, i32 0, i32 28, !dbg !3591
  store %struct.filesystem* %arrayidx32, %struct.filesystem** %current_filesystem33, align 8, !dbg !3592
  %48 = load i64, i64* %dev.addr, align 8, !dbg !3593
  %49 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !3594
  %current_filesystem34 = getelementptr inbounds %struct.tree, %struct.tree* %49, i32 0, i32 28, !dbg !3595
  %50 = load %struct.filesystem*, %struct.filesystem** %current_filesystem34, align 8, !dbg !3595
  %dev35 = getelementptr inbounds %struct.filesystem, %struct.filesystem* %50, i32 0, i32 0, !dbg !3596
  store i64 %48, i64* %dev35, align 8, !dbg !3597
  %51 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !3598
  %current_filesystem36 = getelementptr inbounds %struct.tree, %struct.tree* %51, i32 0, i32 28, !dbg !3599
  %52 = load %struct.filesystem*, %struct.filesystem** %current_filesystem36, align 8, !dbg !3599
  %allocation_ptr = getelementptr inbounds %struct.filesystem, %struct.filesystem* %52, i32 0, i32 9, !dbg !3600
  store i8* null, i8** %allocation_ptr, align 8, !dbg !3601
  %53 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !3602
  %current_filesystem37 = getelementptr inbounds %struct.tree, %struct.tree* %53, i32 0, i32 28, !dbg !3603
  %54 = load %struct.filesystem*, %struct.filesystem** %current_filesystem37, align 8, !dbg !3603
  %buff = getelementptr inbounds %struct.filesystem, %struct.filesystem* %54, i32 0, i32 10, !dbg !3604
  store i8* null, i8** %buff, align 8, !dbg !3605
  %55 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !3606
  %call38 = call i32 @setup_current_filesystem(%struct.archive_read_disk* %55), !dbg !3607
  store i32 %call38, i32* %retval, align 4, !dbg !3608
  br label %return, !dbg !3608

return:                                           ; preds = %if.end28, %if.then23, %if.then7, %if.then
  %56 = load i32, i32* %retval, align 4, !dbg !3609
  ret i32 %56, !dbg !3609
}

; Function Attrs: nounwind
declare i32 @ioctl(i32, i64, ...) #3

declare void @archive_entry_copy_stat(%struct.archive_entry*, %struct.stat*) #2

declare i64 @archive_entry_mtime(%struct.archive_entry*) #2

declare i64 @archive_entry_mtime_nsec(%struct.archive_entry*) #2

declare i64 @archive_entry_atime(%struct.archive_entry*) #2

declare i64 @archive_entry_atime_nsec(%struct.archive_entry*) #2

declare i32 @archive_match_time_excluded(%struct.archive*, %struct.archive_entry*) #2

declare i64 @archive_entry_uid(%struct.archive_entry*) #2

declare void @archive_entry_copy_uname(%struct.archive_entry*, i8*) #2

declare i64 @archive_entry_gid(%struct.archive_entry*) #2

declare void @archive_entry_copy_gname(%struct.archive_entry*, i8*) #2

declare i32 @archive_match_owner_excluded(%struct.archive*, %struct.archive_entry*) #2

declare i32 @archive_read_disk_entry_from_file(%struct.archive*, %struct.archive_entry*, i32, %struct.stat*) #2

; Function Attrs: nounwind uwtable
define internal i32 @tree_dir_next_posix(%struct.tree* %t) #0 !dbg !400 {
entry:
  %retval = alloca i32, align 4
  %t.addr = alloca %struct.tree*, align 8
  %r = alloca i32, align 4
  %name = alloca i8*, align 8
  %namelen = alloca i64, align 8
  %dirent_size = alloca i64, align 8
  store %struct.tree* %t, %struct.tree** %t.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tree** %t.addr, metadata !3610, metadata !460), !dbg !3611
  call void @llvm.dbg.declare(metadata i32* %r, metadata !3612, metadata !460), !dbg !3613
  call void @llvm.dbg.declare(metadata i8** %name, metadata !3614, metadata !460), !dbg !3615
  call void @llvm.dbg.declare(metadata i64* %namelen, metadata !3616, metadata !460), !dbg !3617
  %0 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3618
  %d = getelementptr inbounds %struct.tree, %struct.tree* %0, i32 0, i32 2, !dbg !3620
  %1 = load %struct.__dirstream*, %struct.__dirstream** %d, align 8, !dbg !3620
  %cmp = icmp eq %struct.__dirstream* %1, null, !dbg !3621
  br i1 %cmp, label %if.then, label %if.end30, !dbg !3622

if.then:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i64* %dirent_size, metadata !3623, metadata !460), !dbg !3625
  %2 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3626
  %working_dir_fd = getelementptr inbounds %struct.tree, %struct.tree* %2, i32 0, i32 16, !dbg !3627
  %3 = load i32, i32* %working_dir_fd, align 8, !dbg !3627
  %call = call i32 @tree_dup(i32 %3), !dbg !3628
  %call1 = call %struct.__dirstream* @fdopendir(i32 %call), !dbg !3629
  %4 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3631
  %d2 = getelementptr inbounds %struct.tree, %struct.tree* %4, i32 0, i32 2, !dbg !3632
  store %struct.__dirstream* %call1, %struct.__dirstream** %d2, align 8, !dbg !3633
  %5 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3634
  %d3 = getelementptr inbounds %struct.tree, %struct.tree* %5, i32 0, i32 2, !dbg !3636
  %6 = load %struct.__dirstream*, %struct.__dirstream** %d3, align 8, !dbg !3636
  %cmp4 = icmp eq %struct.__dirstream* %6, null, !dbg !3637
  br i1 %cmp4, label %if.then5, label %if.end, !dbg !3638

if.then5:                                         ; preds = %if.then
  %7 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3639
  %call6 = call i32 @tree_ascend(%struct.tree* %7), !dbg !3641
  store i32 %call6, i32* %r, align 4, !dbg !3642
  %8 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3643
  call void @tree_pop(%struct.tree* %8), !dbg !3644
  %call7 = call i32* @__errno_location() #1, !dbg !3645
  %9 = load i32, i32* %call7, align 4, !dbg !3645
  %10 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3646
  %tree_errno = getelementptr inbounds %struct.tree, %struct.tree* %10, i32 0, i32 8, !dbg !3647
  store i32 %9, i32* %tree_errno, align 8, !dbg !3648
  %11 = load i32, i32* %r, align 4, !dbg !3649
  %cmp8 = icmp ne i32 %11, 0, !dbg !3650
  br i1 %cmp8, label %cond.true, label %cond.false, !dbg !3649

cond.true:                                        ; preds = %if.then5
  %12 = load i32, i32* %r, align 4, !dbg !3651
  br label %cond.end, !dbg !3653

cond.false:                                       ; preds = %if.then5
  br label %cond.end, !dbg !3654

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ %12, %cond.true ], [ -1, %cond.false ], !dbg !3656
  %13 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3658
  %visit_type = getelementptr inbounds %struct.tree, %struct.tree* %13, i32 0, i32 7, !dbg !3659
  store i32 %cond, i32* %visit_type, align 4, !dbg !3660
  %14 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3661
  %visit_type9 = getelementptr inbounds %struct.tree, %struct.tree* %14, i32 0, i32 7, !dbg !3662
  %15 = load i32, i32* %visit_type9, align 4, !dbg !3662
  store i32 %15, i32* %retval, align 4, !dbg !3663
  br label %return, !dbg !3663

if.end:                                           ; preds = %if.then
  %16 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3664
  %current = getelementptr inbounds %struct.tree, %struct.tree* %16, i32 0, i32 1, !dbg !3665
  %17 = load %struct.tree_entry*, %struct.tree_entry** %current, align 8, !dbg !3665
  %filesystem_id = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %17, i32 0, i32 8, !dbg !3666
  %18 = load i32, i32* %filesystem_id, align 4, !dbg !3666
  %idxprom = sext i32 %18 to i64, !dbg !3667
  %19 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3667
  %filesystem_table = getelementptr inbounds %struct.tree, %struct.tree* %19, i32 0, i32 29, !dbg !3668
  %20 = load %struct.filesystem*, %struct.filesystem** %filesystem_table, align 8, !dbg !3668
  %arrayidx = getelementptr inbounds %struct.filesystem, %struct.filesystem* %20, i64 %idxprom, !dbg !3667
  %name_max = getelementptr inbounds %struct.filesystem, %struct.filesystem* %arrayidx, i32 0, i32 4, !dbg !3669
  %21 = load i64, i64* %name_max, align 8, !dbg !3669
  %add = add i64 19, %21, !dbg !3670
  %add10 = add i64 %add, 1, !dbg !3671
  store i64 %add10, i64* %dirent_size, align 8, !dbg !3672
  %22 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3673
  %dirent = getelementptr inbounds %struct.tree, %struct.tree* %22, i32 0, i32 4, !dbg !3675
  %23 = load %struct.dirent*, %struct.dirent** %dirent, align 8, !dbg !3675
  %cmp11 = icmp eq %struct.dirent* %23, null, !dbg !3676
  br i1 %cmp11, label %if.then13, label %lor.lhs.false, !dbg !3677

lor.lhs.false:                                    ; preds = %if.end
  %24 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3678
  %dirent_allocated = getelementptr inbounds %struct.tree, %struct.tree* %24, i32 0, i32 5, !dbg !3680
  %25 = load i64, i64* %dirent_allocated, align 8, !dbg !3680
  %26 = load i64, i64* %dirent_size, align 8, !dbg !3681
  %cmp12 = icmp ult i64 %25, %26, !dbg !3682
  br i1 %cmp12, label %if.then13, label %if.end29, !dbg !3683

if.then13:                                        ; preds = %lor.lhs.false, %if.end
  %27 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3684
  %dirent14 = getelementptr inbounds %struct.tree, %struct.tree* %27, i32 0, i32 4, !dbg !3686
  %28 = load %struct.dirent*, %struct.dirent** %dirent14, align 8, !dbg !3686
  %29 = bitcast %struct.dirent* %28 to i8*, !dbg !3684
  call void @free(i8* %29) #6, !dbg !3687
  %30 = load i64, i64* %dirent_size, align 8, !dbg !3688
  %call15 = call noalias i8* @malloc(i64 %30) #6, !dbg !3689
  %31 = bitcast i8* %call15 to %struct.dirent*, !dbg !3689
  %32 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3690
  %dirent16 = getelementptr inbounds %struct.tree, %struct.tree* %32, i32 0, i32 4, !dbg !3691
  store %struct.dirent* %31, %struct.dirent** %dirent16, align 8, !dbg !3692
  %33 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3693
  %dirent17 = getelementptr inbounds %struct.tree, %struct.tree* %33, i32 0, i32 4, !dbg !3695
  %34 = load %struct.dirent*, %struct.dirent** %dirent17, align 8, !dbg !3695
  %cmp18 = icmp eq %struct.dirent* %34, null, !dbg !3696
  br i1 %cmp18, label %if.then19, label %if.end27, !dbg !3697

if.then19:                                        ; preds = %if.then13
  %35 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3698
  %d20 = getelementptr inbounds %struct.tree, %struct.tree* %35, i32 0, i32 2, !dbg !3700
  %36 = load %struct.__dirstream*, %struct.__dirstream** %d20, align 8, !dbg !3700
  %call21 = call i32 @closedir(%struct.__dirstream* %36), !dbg !3701
  %37 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3702
  %d22 = getelementptr inbounds %struct.tree, %struct.tree* %37, i32 0, i32 2, !dbg !3703
  store %struct.__dirstream* null, %struct.__dirstream** %d22, align 8, !dbg !3704
  %38 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3705
  %call23 = call i32 @tree_ascend(%struct.tree* %38), !dbg !3706
  %39 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3707
  call void @tree_pop(%struct.tree* %39), !dbg !3708
  %40 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3709
  %tree_errno24 = getelementptr inbounds %struct.tree, %struct.tree* %40, i32 0, i32 8, !dbg !3710
  store i32 12, i32* %tree_errno24, align 8, !dbg !3711
  %41 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3712
  %visit_type25 = getelementptr inbounds %struct.tree, %struct.tree* %41, i32 0, i32 7, !dbg !3713
  store i32 -1, i32* %visit_type25, align 4, !dbg !3714
  %42 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3715
  %visit_type26 = getelementptr inbounds %struct.tree, %struct.tree* %42, i32 0, i32 7, !dbg !3716
  %43 = load i32, i32* %visit_type26, align 4, !dbg !3716
  store i32 %43, i32* %retval, align 4, !dbg !3717
  br label %return, !dbg !3717

if.end27:                                         ; preds = %if.then13
  %44 = load i64, i64* %dirent_size, align 8, !dbg !3718
  %45 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3719
  %dirent_allocated28 = getelementptr inbounds %struct.tree, %struct.tree* %45, i32 0, i32 5, !dbg !3720
  store i64 %44, i64* %dirent_allocated28, align 8, !dbg !3721
  br label %if.end29, !dbg !3722

if.end29:                                         ; preds = %if.end27, %lor.lhs.false
  br label %if.end30, !dbg !3723

if.end30:                                         ; preds = %if.end29, %entry
  br label %for.cond, !dbg !3724

for.cond:                                         ; preds = %if.then79, %if.then63, %if.end30
  %call31 = call i32* @__errno_location() #1, !dbg !3725
  store i32 0, i32* %call31, align 4, !dbg !3729
  %46 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3730
  %d32 = getelementptr inbounds %struct.tree, %struct.tree* %46, i32 0, i32 2, !dbg !3731
  %47 = load %struct.__dirstream*, %struct.__dirstream** %d32, align 8, !dbg !3731
  %48 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3732
  %dirent33 = getelementptr inbounds %struct.tree, %struct.tree* %48, i32 0, i32 4, !dbg !3733
  %49 = load %struct.dirent*, %struct.dirent** %dirent33, align 8, !dbg !3733
  %50 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3734
  %de = getelementptr inbounds %struct.tree, %struct.tree* %50, i32 0, i32 3, !dbg !3735
  %call34 = call i32 @readdir_r(%struct.__dirstream* %47, %struct.dirent* %49, %struct.dirent** %de), !dbg !3736
  store i32 %call34, i32* %r, align 4, !dbg !3737
  %51 = load i32, i32* %r, align 4, !dbg !3738
  %cmp35 = icmp ne i32 %51, 0, !dbg !3740
  br i1 %cmp35, label %if.then39, label %lor.lhs.false36, !dbg !3741

lor.lhs.false36:                                  ; preds = %for.cond
  %52 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3742
  %de37 = getelementptr inbounds %struct.tree, %struct.tree* %52, i32 0, i32 3, !dbg !3744
  %53 = load %struct.dirent*, %struct.dirent** %de37, align 8, !dbg !3744
  %cmp38 = icmp eq %struct.dirent* %53, null, !dbg !3745
  br i1 %cmp38, label %if.then39, label %if.end48, !dbg !3746

if.then39:                                        ; preds = %lor.lhs.false36, %for.cond
  %54 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3747
  %d40 = getelementptr inbounds %struct.tree, %struct.tree* %54, i32 0, i32 2, !dbg !3749
  %55 = load %struct.__dirstream*, %struct.__dirstream** %d40, align 8, !dbg !3749
  %call41 = call i32 @closedir(%struct.__dirstream* %55), !dbg !3750
  %56 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3751
  %d42 = getelementptr inbounds %struct.tree, %struct.tree* %56, i32 0, i32 2, !dbg !3752
  store %struct.__dirstream* null, %struct.__dirstream** %d42, align 8, !dbg !3753
  %57 = load i32, i32* %r, align 4, !dbg !3754
  %cmp43 = icmp ne i32 %57, 0, !dbg !3756
  br i1 %cmp43, label %if.then44, label %if.else, !dbg !3757

if.then44:                                        ; preds = %if.then39
  %58 = load i32, i32* %r, align 4, !dbg !3758
  %59 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3760
  %tree_errno45 = getelementptr inbounds %struct.tree, %struct.tree* %59, i32 0, i32 8, !dbg !3761
  store i32 %58, i32* %tree_errno45, align 8, !dbg !3762
  %60 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3763
  %visit_type46 = getelementptr inbounds %struct.tree, %struct.tree* %60, i32 0, i32 7, !dbg !3764
  store i32 -1, i32* %visit_type46, align 4, !dbg !3765
  %61 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3766
  %visit_type47 = getelementptr inbounds %struct.tree, %struct.tree* %61, i32 0, i32 7, !dbg !3767
  %62 = load i32, i32* %visit_type47, align 4, !dbg !3767
  store i32 %62, i32* %retval, align 4, !dbg !3768
  br label %return, !dbg !3768

if.else:                                          ; preds = %if.then39
  store i32 0, i32* %retval, align 4, !dbg !3769
  br label %return, !dbg !3769

if.end48:                                         ; preds = %lor.lhs.false36
  %63 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3770
  %de49 = getelementptr inbounds %struct.tree, %struct.tree* %63, i32 0, i32 3, !dbg !3771
  %64 = load %struct.dirent*, %struct.dirent** %de49, align 8, !dbg !3771
  %d_name = getelementptr inbounds %struct.dirent, %struct.dirent* %64, i32 0, i32 4, !dbg !3772
  %arraydecay = getelementptr inbounds [256 x i8], [256 x i8]* %d_name, i32 0, i32 0, !dbg !3770
  store i8* %arraydecay, i8** %name, align 8, !dbg !3773
  %65 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3774
  %de50 = getelementptr inbounds %struct.tree, %struct.tree* %65, i32 0, i32 3, !dbg !3774
  %66 = load %struct.dirent*, %struct.dirent** %de50, align 8, !dbg !3774
  %d_name51 = getelementptr inbounds %struct.dirent, %struct.dirent* %66, i32 0, i32 4, !dbg !3774
  %arraydecay52 = getelementptr inbounds [256 x i8], [256 x i8]* %d_name51, i32 0, i32 0, !dbg !3774
  %call53 = call i64 @strlen(i8* %arraydecay52) #7, !dbg !3774
  store i64 %call53, i64* %namelen, align 8, !dbg !3775
  %67 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3776
  %flags = getelementptr inbounds %struct.tree, %struct.tree* %67, i32 0, i32 6, !dbg !3777
  %68 = load i32, i32* %flags, align 8, !dbg !3778
  %and = and i32 %68, -33, !dbg !3778
  store i32 %and, i32* %flags, align 8, !dbg !3778
  %69 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3779
  %flags54 = getelementptr inbounds %struct.tree, %struct.tree* %69, i32 0, i32 6, !dbg !3780
  %70 = load i32, i32* %flags54, align 8, !dbg !3781
  %and55 = and i32 %70, -17, !dbg !3781
  store i32 %and55, i32* %flags54, align 8, !dbg !3781
  %71 = load i8*, i8** %name, align 8, !dbg !3782
  %arrayidx56 = getelementptr inbounds i8, i8* %71, i64 0, !dbg !3782
  %72 = load i8, i8* %arrayidx56, align 1, !dbg !3782
  %conv = sext i8 %72 to i32, !dbg !3782
  %cmp57 = icmp eq i32 %conv, 46, !dbg !3784
  br i1 %cmp57, label %land.lhs.true, label %if.end64, !dbg !3785

land.lhs.true:                                    ; preds = %if.end48
  %73 = load i8*, i8** %name, align 8, !dbg !3786
  %arrayidx59 = getelementptr inbounds i8, i8* %73, i64 1, !dbg !3786
  %74 = load i8, i8* %arrayidx59, align 1, !dbg !3786
  %conv60 = sext i8 %74 to i32, !dbg !3786
  %cmp61 = icmp eq i32 %conv60, 0, !dbg !3788
  br i1 %cmp61, label %if.then63, label %if.end64, !dbg !3789

if.then63:                                        ; preds = %land.lhs.true
  br label %for.cond, !dbg !3790

if.end64:                                         ; preds = %land.lhs.true, %if.end48
  %75 = load i8*, i8** %name, align 8, !dbg !3791
  %arrayidx65 = getelementptr inbounds i8, i8* %75, i64 0, !dbg !3791
  %76 = load i8, i8* %arrayidx65, align 1, !dbg !3791
  %conv66 = sext i8 %76 to i32, !dbg !3791
  %cmp67 = icmp eq i32 %conv66, 46, !dbg !3793
  br i1 %cmp67, label %land.lhs.true69, label %if.end80, !dbg !3794

land.lhs.true69:                                  ; preds = %if.end64
  %77 = load i8*, i8** %name, align 8, !dbg !3795
  %arrayidx70 = getelementptr inbounds i8, i8* %77, i64 1, !dbg !3795
  %78 = load i8, i8* %arrayidx70, align 1, !dbg !3795
  %conv71 = sext i8 %78 to i32, !dbg !3795
  %cmp72 = icmp eq i32 %conv71, 46, !dbg !3797
  br i1 %cmp72, label %land.lhs.true74, label %if.end80, !dbg !3798

land.lhs.true74:                                  ; preds = %land.lhs.true69
  %79 = load i8*, i8** %name, align 8, !dbg !3799
  %arrayidx75 = getelementptr inbounds i8, i8* %79, i64 2, !dbg !3799
  %80 = load i8, i8* %arrayidx75, align 1, !dbg !3799
  %conv76 = sext i8 %80 to i32, !dbg !3799
  %cmp77 = icmp eq i32 %conv76, 0, !dbg !3801
  br i1 %cmp77, label %if.then79, label %if.end80, !dbg !3802

if.then79:                                        ; preds = %land.lhs.true74
  br label %for.cond, !dbg !3803

if.end80:                                         ; preds = %land.lhs.true74, %land.lhs.true69, %if.end64
  %81 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3804
  %82 = load i8*, i8** %name, align 8, !dbg !3805
  %83 = load i64, i64* %namelen, align 8, !dbg !3806
  call void @tree_append(%struct.tree* %81, i8* %82, i64 %83), !dbg !3807
  %84 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3808
  %visit_type81 = getelementptr inbounds %struct.tree, %struct.tree* %84, i32 0, i32 7, !dbg !3809
  store i32 1, i32* %visit_type81, align 4, !dbg !3810
  store i32 1, i32* %retval, align 4, !dbg !3811
  br label %return, !dbg !3811

return:                                           ; preds = %if.end80, %if.else, %if.then44, %if.then19, %cond.end
  %85 = load i32, i32* %retval, align 4, !dbg !3812
  ret i32 %85, !dbg !3812
}

; Function Attrs: nounwind uwtable
define internal void @tree_append(%struct.tree* %t, i8* %name, i64 %name_length) #0 !dbg !404 {
entry:
  %t.addr = alloca %struct.tree*, align 8
  %name.addr = alloca i8*, align 8
  %name_length.addr = alloca i64, align 8
  %size_needed = alloca i64, align 8
  store %struct.tree* %t, %struct.tree** %t.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tree** %t.addr, metadata !3813, metadata !460), !dbg !3814
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !3815, metadata !460), !dbg !3816
  store i64 %name_length, i64* %name_length.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %name_length.addr, metadata !3817, metadata !460), !dbg !3818
  call void @llvm.dbg.declare(metadata i64* %size_needed, metadata !3819, metadata !460), !dbg !3820
  %0 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3821
  %dirname_length = getelementptr inbounds %struct.tree, %struct.tree* %0, i32 0, i32 11, !dbg !3822
  %1 = load i64, i64* %dirname_length, align 8, !dbg !3822
  %2 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3823
  %path = getelementptr inbounds %struct.tree, %struct.tree* %2, i32 0, i32 9, !dbg !3824
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %path, i32 0, i32 0, !dbg !3825
  %3 = load i8*, i8** %s, align 8, !dbg !3825
  %arrayidx = getelementptr inbounds i8, i8* %3, i64 %1, !dbg !3823
  store i8 0, i8* %arrayidx, align 1, !dbg !3826
  %4 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3827
  %dirname_length1 = getelementptr inbounds %struct.tree, %struct.tree* %4, i32 0, i32 11, !dbg !3828
  %5 = load i64, i64* %dirname_length1, align 8, !dbg !3828
  %6 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3829
  %path2 = getelementptr inbounds %struct.tree, %struct.tree* %6, i32 0, i32 9, !dbg !3830
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %path2, i32 0, i32 1, !dbg !3831
  store i64 %5, i64* %length, align 8, !dbg !3832
  br label %while.cond, !dbg !3833

while.cond:                                       ; preds = %while.body, %entry
  %7 = load i64, i64* %name_length.addr, align 8, !dbg !3834
  %cmp = icmp ugt i64 %7, 1, !dbg !3836
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !3837

land.rhs:                                         ; preds = %while.cond
  %8 = load i64, i64* %name_length.addr, align 8, !dbg !3838
  %sub = sub i64 %8, 1, !dbg !3840
  %9 = load i8*, i8** %name.addr, align 8, !dbg !3841
  %arrayidx3 = getelementptr inbounds i8, i8* %9, i64 %sub, !dbg !3841
  %10 = load i8, i8* %arrayidx3, align 1, !dbg !3841
  %conv = sext i8 %10 to i32, !dbg !3841
  %cmp4 = icmp eq i32 %conv, 47, !dbg !3842
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond
  %11 = phi i1 [ false, %while.cond ], [ %cmp4, %land.rhs ]
  br i1 %11, label %while.body, label %while.end, !dbg !3843

while.body:                                       ; preds = %land.end
  %12 = load i64, i64* %name_length.addr, align 8, !dbg !3845
  %dec = add i64 %12, -1, !dbg !3845
  store i64 %dec, i64* %name_length.addr, align 8, !dbg !3845
  br label %while.cond, !dbg !3846

while.end:                                        ; preds = %land.end
  %13 = load i64, i64* %name_length.addr, align 8, !dbg !3848
  %14 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3849
  %dirname_length6 = getelementptr inbounds %struct.tree, %struct.tree* %14, i32 0, i32 11, !dbg !3850
  %15 = load i64, i64* %dirname_length6, align 8, !dbg !3850
  %add = add i64 %13, %15, !dbg !3851
  %add7 = add i64 %add, 2, !dbg !3852
  store i64 %add7, i64* %size_needed, align 8, !dbg !3853
  %16 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3854
  %path8 = getelementptr inbounds %struct.tree, %struct.tree* %16, i32 0, i32 9, !dbg !3855
  %17 = load i64, i64* %size_needed, align 8, !dbg !3856
  %call = call %struct.archive_string* @archive_string_ensure(%struct.archive_string* %path8, i64 %17), !dbg !3857
  %18 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3858
  %dirname_length9 = getelementptr inbounds %struct.tree, %struct.tree* %18, i32 0, i32 11, !dbg !3860
  %19 = load i64, i64* %dirname_length9, align 8, !dbg !3860
  %cmp10 = icmp ugt i64 %19, 0, !dbg !3861
  br i1 %cmp10, label %land.lhs.true, label %if.end, !dbg !3862

land.lhs.true:                                    ; preds = %while.end
  %20 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3863
  %path12 = getelementptr inbounds %struct.tree, %struct.tree* %20, i32 0, i32 9, !dbg !3863
  %length13 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %path12, i32 0, i32 1, !dbg !3863
  %21 = load i64, i64* %length13, align 8, !dbg !3863
  %sub14 = sub i64 %21, 1, !dbg !3865
  %22 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3866
  %path15 = getelementptr inbounds %struct.tree, %struct.tree* %22, i32 0, i32 9, !dbg !3867
  %s16 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %path15, i32 0, i32 0, !dbg !3868
  %23 = load i8*, i8** %s16, align 8, !dbg !3868
  %arrayidx17 = getelementptr inbounds i8, i8* %23, i64 %sub14, !dbg !3866
  %24 = load i8, i8* %arrayidx17, align 1, !dbg !3866
  %conv18 = sext i8 %24 to i32, !dbg !3866
  %cmp19 = icmp ne i32 %conv18, 47, !dbg !3869
  br i1 %cmp19, label %if.then, label %if.end, !dbg !3870

if.then:                                          ; preds = %land.lhs.true
  %25 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3871
  %path21 = getelementptr inbounds %struct.tree, %struct.tree* %25, i32 0, i32 9, !dbg !3872
  %call22 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %path21, i8 signext 47), !dbg !3873
  br label %if.end, !dbg !3873

if.end:                                           ; preds = %if.then, %land.lhs.true, %while.end
  %26 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3874
  %path23 = getelementptr inbounds %struct.tree, %struct.tree* %26, i32 0, i32 9, !dbg !3875
  %s24 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %path23, i32 0, i32 0, !dbg !3876
  %27 = load i8*, i8** %s24, align 8, !dbg !3876
  %28 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3877
  %path25 = getelementptr inbounds %struct.tree, %struct.tree* %28, i32 0, i32 9, !dbg !3877
  %length26 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %path25, i32 0, i32 1, !dbg !3877
  %29 = load i64, i64* %length26, align 8, !dbg !3877
  %add.ptr = getelementptr inbounds i8, i8* %27, i64 %29, !dbg !3878
  %30 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3879
  %basename = getelementptr inbounds %struct.tree, %struct.tree* %30, i32 0, i32 10, !dbg !3880
  store i8* %add.ptr, i8** %basename, align 8, !dbg !3881
  %31 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3882
  %path27 = getelementptr inbounds %struct.tree, %struct.tree* %31, i32 0, i32 9, !dbg !3883
  %32 = load i8*, i8** %name.addr, align 8, !dbg !3884
  %33 = load i64, i64* %name_length.addr, align 8, !dbg !3885
  %call28 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %path27, i8* %32, i64 %33), !dbg !3886
  %34 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3887
  %basename29 = getelementptr inbounds %struct.tree, %struct.tree* %34, i32 0, i32 10, !dbg !3888
  %35 = load i8*, i8** %basename29, align 8, !dbg !3888
  %36 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3889
  %restore_time = getelementptr inbounds %struct.tree, %struct.tree* %36, i32 0, i32 21, !dbg !3890
  %name30 = getelementptr inbounds %struct.restore_time, %struct.restore_time* %restore_time, i32 0, i32 0, !dbg !3891
  store i8* %35, i8** %name30, align 8, !dbg !3892
  ret void, !dbg !3893
}

; Function Attrs: nounwind uwtable
define internal i32 @tree_descent(%struct.tree* %t) #0 !dbg !407 {
entry:
  %t.addr = alloca %struct.tree*, align 8
  %flag = alloca i32, align 4
  %new_fd = alloca i32, align 4
  %r = alloca i32, align 4
  store %struct.tree* %t, %struct.tree** %t.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tree** %t.addr, metadata !3894, metadata !460), !dbg !3895
  call void @llvm.dbg.declare(metadata i32* %flag, metadata !3896, metadata !460), !dbg !3897
  call void @llvm.dbg.declare(metadata i32* %new_fd, metadata !3898, metadata !460), !dbg !3899
  call void @llvm.dbg.declare(metadata i32* %r, metadata !3900, metadata !460), !dbg !3901
  store i32 0, i32* %r, align 4, !dbg !3901
  %0 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3902
  %path = getelementptr inbounds %struct.tree, %struct.tree* %0, i32 0, i32 9, !dbg !3902
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %path, i32 0, i32 1, !dbg !3902
  %1 = load i64, i64* %length, align 8, !dbg !3902
  %2 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3903
  %dirname_length = getelementptr inbounds %struct.tree, %struct.tree* %2, i32 0, i32 11, !dbg !3904
  store i64 %1, i64* %dirname_length, align 8, !dbg !3905
  store i32 524288, i32* %flag, align 4, !dbg !3906
  %3 = load i32, i32* %flag, align 4, !dbg !3907
  %or = or i32 %3, 65536, !dbg !3907
  store i32 %or, i32* %flag, align 4, !dbg !3907
  %4 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3908
  %5 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3909
  %stack = getelementptr inbounds %struct.tree, %struct.tree* %5, i32 0, i32 0, !dbg !3910
  %6 = load %struct.tree_entry*, %struct.tree_entry** %stack, align 8, !dbg !3910
  %name = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %6, i32 0, i32 3, !dbg !3911
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %name, i32 0, i32 0, !dbg !3912
  %7 = load i8*, i8** %s, align 8, !dbg !3912
  %8 = load i32, i32* %flag, align 4, !dbg !3913
  %call = call i32 @open_on_current_dir(%struct.tree* %4, i8* %7, i32 %8), !dbg !3914
  store i32 %call, i32* %new_fd, align 4, !dbg !3915
  %9 = load i32, i32* %new_fd, align 4, !dbg !3916
  call void @__archive_ensure_cloexec_flag(i32 %9), !dbg !3917
  %10 = load i32, i32* %new_fd, align 4, !dbg !3918
  %cmp = icmp slt i32 %10, 0, !dbg !3920
  br i1 %cmp, label %if.then, label %if.else, !dbg !3921

if.then:                                          ; preds = %entry
  %call1 = call i32* @__errno_location() #1, !dbg !3922
  %11 = load i32, i32* %call1, align 4, !dbg !3922
  %12 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3924
  %tree_errno = getelementptr inbounds %struct.tree, %struct.tree* %12, i32 0, i32 8, !dbg !3925
  store i32 %11, i32* %tree_errno, align 8, !dbg !3926
  store i32 -1, i32* %r, align 4, !dbg !3927
  br label %if.end18, !dbg !3928

if.else:                                          ; preds = %entry
  %13 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3929
  %depth = getelementptr inbounds %struct.tree, %struct.tree* %13, i32 0, i32 12, !dbg !3931
  %14 = load i32, i32* %depth, align 8, !dbg !3932
  %inc = add nsw i32 %14, 1, !dbg !3932
  store i32 %inc, i32* %depth, align 8, !dbg !3932
  %15 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3933
  %stack2 = getelementptr inbounds %struct.tree, %struct.tree* %15, i32 0, i32 0, !dbg !3935
  %16 = load %struct.tree_entry*, %struct.tree_entry** %stack2, align 8, !dbg !3935
  %flags = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %16, i32 0, i32 7, !dbg !3936
  %17 = load i32, i32* %flags, align 8, !dbg !3936
  %and = and i32 %17, 2, !dbg !3937
  %tobool = icmp ne i32 %and, 0, !dbg !3937
  br i1 %tobool, label %if.then3, label %if.else11, !dbg !3938

if.then3:                                         ; preds = %if.else
  %18 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3939
  %working_dir_fd = getelementptr inbounds %struct.tree, %struct.tree* %18, i32 0, i32 16, !dbg !3941
  %19 = load i32, i32* %working_dir_fd, align 8, !dbg !3941
  %20 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3942
  %stack4 = getelementptr inbounds %struct.tree, %struct.tree* %20, i32 0, i32 0, !dbg !3943
  %21 = load %struct.tree_entry*, %struct.tree_entry** %stack4, align 8, !dbg !3943
  %symlink_parent_fd = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %21, i32 0, i32 9, !dbg !3944
  store i32 %19, i32* %symlink_parent_fd, align 8, !dbg !3945
  %22 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3946
  %openCount = getelementptr inbounds %struct.tree, %struct.tree* %22, i32 0, i32 13, !dbg !3947
  %23 = load i32, i32* %openCount, align 4, !dbg !3948
  %inc5 = add nsw i32 %23, 1, !dbg !3948
  store i32 %inc5, i32* %openCount, align 4, !dbg !3948
  %24 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3949
  %openCount6 = getelementptr inbounds %struct.tree, %struct.tree* %24, i32 0, i32 13, !dbg !3951
  %25 = load i32, i32* %openCount6, align 4, !dbg !3951
  %26 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3952
  %maxOpenCount = getelementptr inbounds %struct.tree, %struct.tree* %26, i32 0, i32 14, !dbg !3953
  %27 = load i32, i32* %maxOpenCount, align 8, !dbg !3953
  %cmp7 = icmp sgt i32 %25, %27, !dbg !3954
  br i1 %cmp7, label %if.then8, label %if.end, !dbg !3955

if.then8:                                         ; preds = %if.then3
  %28 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3956
  %openCount9 = getelementptr inbounds %struct.tree, %struct.tree* %28, i32 0, i32 13, !dbg !3957
  %29 = load i32, i32* %openCount9, align 4, !dbg !3957
  %30 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3958
  %maxOpenCount10 = getelementptr inbounds %struct.tree, %struct.tree* %30, i32 0, i32 14, !dbg !3959
  store i32 %29, i32* %maxOpenCount10, align 8, !dbg !3960
  br label %if.end, !dbg !3958

if.end:                                           ; preds = %if.then8, %if.then3
  br label %if.end14, !dbg !3961

if.else11:                                        ; preds = %if.else
  %31 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3962
  %working_dir_fd12 = getelementptr inbounds %struct.tree, %struct.tree* %31, i32 0, i32 16, !dbg !3963
  %32 = load i32, i32* %working_dir_fd12, align 8, !dbg !3963
  %call13 = call i32 @close(i32 %32), !dbg !3964
  br label %if.end14

if.end14:                                         ; preds = %if.else11, %if.end
  %33 = load i32, i32* %new_fd, align 4, !dbg !3965
  %34 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3966
  %working_dir_fd15 = getelementptr inbounds %struct.tree, %struct.tree* %34, i32 0, i32 16, !dbg !3967
  store i32 %33, i32* %working_dir_fd15, align 8, !dbg !3968
  %35 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3969
  %flags16 = getelementptr inbounds %struct.tree, %struct.tree* %35, i32 0, i32 6, !dbg !3970
  %36 = load i32, i32* %flags16, align 8, !dbg !3971
  %and17 = and i32 %36, -65, !dbg !3971
  store i32 %and17, i32* %flags16, align 8, !dbg !3971
  br label %if.end18

if.end18:                                         ; preds = %if.end14, %if.then
  %37 = load i32, i32* %r, align 4, !dbg !3972
  ret i32 %37, !dbg !3973
}

; Function Attrs: nounwind uwtable
define internal i32 @tree_ascend(%struct.tree* %t) #0 !dbg !408 {
entry:
  %t.addr = alloca %struct.tree*, align 8
  %te = alloca %struct.tree_entry*, align 8
  %new_fd = alloca i32, align 4
  %r = alloca i32, align 4
  %prev_dir_fd = alloca i32, align 4
  store %struct.tree* %t, %struct.tree** %t.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tree** %t.addr, metadata !3974, metadata !460), !dbg !3975
  call void @llvm.dbg.declare(metadata %struct.tree_entry** %te, metadata !3976, metadata !460), !dbg !3977
  call void @llvm.dbg.declare(metadata i32* %new_fd, metadata !3978, metadata !460), !dbg !3979
  call void @llvm.dbg.declare(metadata i32* %r, metadata !3980, metadata !460), !dbg !3981
  store i32 0, i32* %r, align 4, !dbg !3981
  call void @llvm.dbg.declare(metadata i32* %prev_dir_fd, metadata !3982, metadata !460), !dbg !3983
  %0 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3984
  %stack = getelementptr inbounds %struct.tree, %struct.tree* %0, i32 0, i32 0, !dbg !3985
  %1 = load %struct.tree_entry*, %struct.tree_entry** %stack, align 8, !dbg !3985
  store %struct.tree_entry* %1, %struct.tree_entry** %te, align 8, !dbg !3986
  %2 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3987
  %working_dir_fd = getelementptr inbounds %struct.tree, %struct.tree* %2, i32 0, i32 16, !dbg !3988
  %3 = load i32, i32* %working_dir_fd, align 8, !dbg !3988
  store i32 %3, i32* %prev_dir_fd, align 4, !dbg !3989
  %4 = load %struct.tree_entry*, %struct.tree_entry** %te, align 8, !dbg !3990
  %flags = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %4, i32 0, i32 7, !dbg !3992
  %5 = load i32, i32* %flags, align 8, !dbg !3992
  %and = and i32 %5, 2, !dbg !3993
  %tobool = icmp ne i32 %and, 0, !dbg !3993
  br i1 %tobool, label %if.then, label %if.else, !dbg !3994

if.then:                                          ; preds = %entry
  %6 = load %struct.tree_entry*, %struct.tree_entry** %te, align 8, !dbg !3995
  %symlink_parent_fd = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %6, i32 0, i32 9, !dbg !3996
  %7 = load i32, i32* %symlink_parent_fd, align 8, !dbg !3996
  store i32 %7, i32* %new_fd, align 4, !dbg !3997
  br label %if.end, !dbg !3998

if.else:                                          ; preds = %entry
  %8 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !3999
  %call = call i32 @open_on_current_dir(%struct.tree* %8, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.30, i32 0, i32 0), i32 524288), !dbg !4001
  store i32 %call, i32* %new_fd, align 4, !dbg !4002
  %9 = load i32, i32* %new_fd, align 4, !dbg !4003
  call void @__archive_ensure_cloexec_flag(i32 %9), !dbg !4004
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %10 = load i32, i32* %new_fd, align 4, !dbg !4005
  %cmp = icmp slt i32 %10, 0, !dbg !4007
  br i1 %cmp, label %if.then1, label %if.else3, !dbg !4008

if.then1:                                         ; preds = %if.end
  %call2 = call i32* @__errno_location() #1, !dbg !4009
  %11 = load i32, i32* %call2, align 4, !dbg !4009
  %12 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4011
  %tree_errno = getelementptr inbounds %struct.tree, %struct.tree* %12, i32 0, i32 8, !dbg !4012
  store i32 %11, i32* %tree_errno, align 8, !dbg !4013
  store i32 -2, i32* %r, align 4, !dbg !4014
  br label %if.end15, !dbg !4015

if.else3:                                         ; preds = %if.end
  %13 = load i32, i32* %new_fd, align 4, !dbg !4016
  %14 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4018
  %working_dir_fd4 = getelementptr inbounds %struct.tree, %struct.tree* %14, i32 0, i32 16, !dbg !4019
  store i32 %13, i32* %working_dir_fd4, align 8, !dbg !4020
  %15 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4021
  %flags5 = getelementptr inbounds %struct.tree, %struct.tree* %15, i32 0, i32 6, !dbg !4022
  %16 = load i32, i32* %flags5, align 8, !dbg !4023
  %and6 = and i32 %16, -65, !dbg !4023
  store i32 %and6, i32* %flags5, align 8, !dbg !4023
  %17 = load i32, i32* %prev_dir_fd, align 4, !dbg !4024
  %18 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4025
  %19 = load %struct.tree_entry*, %struct.tree_entry** %te, align 8, !dbg !4026
  %restore_time = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %19, i32 0, i32 10, !dbg !4027
  %call7 = call i32 @close_and_restore_time(i32 %17, %struct.tree* %18, %struct.restore_time* %restore_time), !dbg !4028
  %20 = load %struct.tree_entry*, %struct.tree_entry** %te, align 8, !dbg !4029
  %flags8 = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %20, i32 0, i32 7, !dbg !4031
  %21 = load i32, i32* %flags8, align 8, !dbg !4031
  %and9 = and i32 %21, 2, !dbg !4032
  %tobool10 = icmp ne i32 %and9, 0, !dbg !4032
  br i1 %tobool10, label %if.then11, label %if.end13, !dbg !4033

if.then11:                                        ; preds = %if.else3
  %22 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4034
  %openCount = getelementptr inbounds %struct.tree, %struct.tree* %22, i32 0, i32 13, !dbg !4036
  %23 = load i32, i32* %openCount, align 4, !dbg !4037
  %dec = add nsw i32 %23, -1, !dbg !4037
  store i32 %dec, i32* %openCount, align 4, !dbg !4037
  %24 = load %struct.tree_entry*, %struct.tree_entry** %te, align 8, !dbg !4038
  %symlink_parent_fd12 = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %24, i32 0, i32 9, !dbg !4039
  store i32 -1, i32* %symlink_parent_fd12, align 8, !dbg !4040
  br label %if.end13, !dbg !4041

if.end13:                                         ; preds = %if.then11, %if.else3
  %25 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4042
  %depth = getelementptr inbounds %struct.tree, %struct.tree* %25, i32 0, i32 12, !dbg !4043
  %26 = load i32, i32* %depth, align 8, !dbg !4044
  %dec14 = add nsw i32 %26, -1, !dbg !4044
  store i32 %dec14, i32* %depth, align 8, !dbg !4044
  br label %if.end15

if.end15:                                         ; preds = %if.end13, %if.then1
  %27 = load i32, i32* %r, align 4, !dbg !4045
  ret i32 %27, !dbg !4046
}

declare %struct.__dirstream* @fdopendir(i32) #2

; Function Attrs: nounwind uwtable
define internal i32 @tree_dup(i32 %fd) #0 !dbg !401 {
entry:
  %retval = alloca i32, align 4
  %fd.addr = alloca i32, align 4
  %new_fd = alloca i32, align 4
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !4047, metadata !460), !dbg !4048
  call void @llvm.dbg.declare(metadata i32* %new_fd, metadata !4049, metadata !460), !dbg !4050
  %0 = load volatile i32, i32* @tree_dup.can_dupfd_cloexec, align 4, !dbg !4051
  %tobool = icmp ne i32 %0, 0, !dbg !4051
  br i1 %tobool, label %if.then, label %if.end2, !dbg !4053

if.then:                                          ; preds = %entry
  %1 = load i32, i32* %fd.addr, align 4, !dbg !4054
  %call = call i32 (i32, i32, ...) @fcntl(i32 %1, i32 1030, i32 0), !dbg !4056
  store i32 %call, i32* %new_fd, align 4, !dbg !4057
  %2 = load i32, i32* %new_fd, align 4, !dbg !4058
  %cmp = icmp ne i32 %2, -1, !dbg !4060
  br i1 %cmp, label %if.then1, label %if.end, !dbg !4061

if.then1:                                         ; preds = %if.then
  %3 = load i32, i32* %new_fd, align 4, !dbg !4062
  store i32 %3, i32* %retval, align 4, !dbg !4063
  br label %return, !dbg !4063

if.end:                                           ; preds = %if.then
  store volatile i32 0, i32* @tree_dup.can_dupfd_cloexec, align 4, !dbg !4064
  br label %if.end2, !dbg !4065

if.end2:                                          ; preds = %if.end, %entry
  %4 = load i32, i32* %fd.addr, align 4, !dbg !4066
  %call3 = call i32 @dup(i32 %4) #6, !dbg !4067
  store i32 %call3, i32* %new_fd, align 4, !dbg !4068
  %5 = load i32, i32* %new_fd, align 4, !dbg !4069
  call void @__archive_ensure_cloexec_flag(i32 %5), !dbg !4070
  %6 = load i32, i32* %new_fd, align 4, !dbg !4071
  store i32 %6, i32* %retval, align 4, !dbg !4072
  br label %return, !dbg !4072

return:                                           ; preds = %if.end2, %if.then1
  %7 = load i32, i32* %retval, align 4, !dbg !4073
  ret i32 %7, !dbg !4073
}

declare i32 @readdir_r(%struct.__dirstream*, %struct.dirent*, %struct.dirent**) #2

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #4

declare i32 @fcntl(i32, i32, ...) #2

; Function Attrs: nounwind
declare i32 @dup(i32) #3

declare %struct.archive_string* @archive_string_ensure(%struct.archive_string*, i64) #2

declare %struct.archive_string* @archive_strappend_char(%struct.archive_string*, i8 signext) #2

declare %struct.archive_string* @archive_strncat(%struct.archive_string*, i8*, i64) #2

; Function Attrs: nounwind
declare i32 @fstatat(i32, i8*, %struct.stat*, i32) #3

; Function Attrs: nounwind
declare i8* @realloc(i8*, i64) #3

; Function Attrs: nounwind uwtable
define internal i32 @setup_current_filesystem(%struct.archive_read_disk* %a) #0 !dbg !421 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read_disk*, align 8
  %t = alloca %struct.tree*, align 8
  %sfs = alloca %struct.statfs, align 8
  %svfs = alloca %struct.statvfs, align 8
  %r = alloca i32, align 4
  %vr = alloca i32, align 4
  %xr = alloca i32, align 4
  %fd = alloca i32, align 4
  store %struct.archive_read_disk* %a, %struct.archive_read_disk** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_disk** %a.addr, metadata !4074, metadata !460), !dbg !4075
  call void @llvm.dbg.declare(metadata %struct.tree** %t, metadata !4076, metadata !460), !dbg !4077
  %0 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !4078
  %tree = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %0, i32 0, i32 4, !dbg !4079
  %1 = load %struct.tree*, %struct.tree** %tree, align 8, !dbg !4079
  store %struct.tree* %1, %struct.tree** %t, align 8, !dbg !4077
  call void @llvm.dbg.declare(metadata %struct.statfs* %sfs, metadata !4080, metadata !460), !dbg !4107
  call void @llvm.dbg.declare(metadata %struct.statvfs* %svfs, metadata !4108, metadata !460), !dbg !4126
  call void @llvm.dbg.declare(metadata i32* %r, metadata !4127, metadata !460), !dbg !4128
  call void @llvm.dbg.declare(metadata i32* %vr, metadata !4129, metadata !460), !dbg !4130
  store i32 0, i32* %vr, align 4, !dbg !4130
  call void @llvm.dbg.declare(metadata i32* %xr, metadata !4131, metadata !460), !dbg !4132
  store i32 0, i32* %xr, align 4, !dbg !4132
  %2 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !4133
  %call = call i32 @tree_current_is_symblic_link_target(%struct.tree* %2), !dbg !4135
  %tobool = icmp ne i32 %call, 0, !dbg !4135
  br i1 %tobool, label %if.then, label %if.else, !dbg !4136

if.then:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %fd, metadata !4137, metadata !460), !dbg !4139
  %3 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !4140
  %call1 = call i32 @tree_current_dir_fd(%struct.tree* %3), !dbg !4141
  %4 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !4142
  %call2 = call i8* @tree_current_access_path(%struct.tree* %4), !dbg !4143
  %call3 = call i32 (i32, i8*, i32, ...) @openat(i32 %call1, i8* %call2, i32 524288), !dbg !4144
  store i32 %call3, i32* %fd, align 4, !dbg !4139
  %5 = load i32, i32* %fd, align 4, !dbg !4145
  call void @__archive_ensure_cloexec_flag(i32 %5), !dbg !4146
  %6 = load i32, i32* %fd, align 4, !dbg !4147
  %cmp = icmp slt i32 %6, 0, !dbg !4149
  br i1 %cmp, label %if.then4, label %if.end, !dbg !4150

if.then4:                                         ; preds = %if.then
  %7 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !4151
  %archive = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %7, i32 0, i32 0, !dbg !4153
  %call5 = call i32* @__errno_location() #1, !dbg !4154
  %8 = load i32, i32* %call5, align 4, !dbg !4154
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 %8, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.32, i32 0, i32 0)), !dbg !4155
  store i32 -25, i32* %retval, align 4, !dbg !4157
  br label %return, !dbg !4157

if.end:                                           ; preds = %if.then
  %9 = load i32, i32* %fd, align 4, !dbg !4158
  %call6 = call i32 @fstatvfs(i32 %9, %struct.statvfs* %svfs) #6, !dbg !4159
  store i32 %call6, i32* %vr, align 4, !dbg !4160
  %10 = load i32, i32* %fd, align 4, !dbg !4161
  %call7 = call i32 @fstatfs(i32 %10, %struct.statfs* %sfs) #6, !dbg !4162
  store i32 %call7, i32* %r, align 4, !dbg !4163
  %11 = load i32, i32* %r, align 4, !dbg !4164
  %cmp8 = icmp eq i32 %11, 0, !dbg !4166
  br i1 %cmp8, label %if.then9, label %if.end11, !dbg !4167

if.then9:                                         ; preds = %if.end
  %12 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !4168
  %13 = load i32, i32* %fd, align 4, !dbg !4169
  %call10 = call i32 @get_xfer_size(%struct.tree* %12, i32 %13, i8* null), !dbg !4170
  store i32 %call10, i32* %xr, align 4, !dbg !4171
  br label %if.end11, !dbg !4172

if.end11:                                         ; preds = %if.then9, %if.end
  %14 = load i32, i32* %fd, align 4, !dbg !4173
  %call12 = call i32 @close(i32 %14), !dbg !4174
  br label %if.end22, !dbg !4175

if.else:                                          ; preds = %entry
  %15 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !4176
  %call13 = call i32 @tree_current_dir_fd(%struct.tree* %15), !dbg !4178
  %call14 = call i32 @fstatvfs(i32 %call13, %struct.statvfs* %svfs) #6, !dbg !4179
  store i32 %call14, i32* %vr, align 4, !dbg !4181
  %16 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !4182
  %call15 = call i32 @tree_current_dir_fd(%struct.tree* %16), !dbg !4183
  %call16 = call i32 @fstatfs(i32 %call15, %struct.statfs* %sfs) #6, !dbg !4184
  store i32 %call16, i32* %r, align 4, !dbg !4185
  %17 = load i32, i32* %r, align 4, !dbg !4186
  %cmp17 = icmp eq i32 %17, 0, !dbg !4188
  br i1 %cmp17, label %if.then18, label %if.end21, !dbg !4189

if.then18:                                        ; preds = %if.else
  %18 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !4190
  %19 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !4191
  %call19 = call i32 @tree_current_dir_fd(%struct.tree* %19), !dbg !4192
  %call20 = call i32 @get_xfer_size(%struct.tree* %18, i32 %call19, i8* null), !dbg !4193
  store i32 %call20, i32* %xr, align 4, !dbg !4195
  br label %if.end21, !dbg !4196

if.end21:                                         ; preds = %if.then18, %if.else
  br label %if.end22

if.end22:                                         ; preds = %if.end21, %if.end11
  %20 = load i32, i32* %r, align 4, !dbg !4197
  %cmp23 = icmp eq i32 %20, -1, !dbg !4199
  br i1 %cmp23, label %if.then27, label %lor.lhs.false, !dbg !4200

lor.lhs.false:                                    ; preds = %if.end22
  %21 = load i32, i32* %xr, align 4, !dbg !4201
  %cmp24 = icmp eq i32 %21, -1, !dbg !4203
  br i1 %cmp24, label %if.then27, label %lor.lhs.false25, !dbg !4204

lor.lhs.false25:                                  ; preds = %lor.lhs.false
  %22 = load i32, i32* %vr, align 4, !dbg !4205
  %cmp26 = icmp eq i32 %22, -1, !dbg !4207
  br i1 %cmp26, label %if.then27, label %if.else31, !dbg !4208

if.then27:                                        ; preds = %lor.lhs.false25, %lor.lhs.false, %if.end22
  %23 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !4209
  %current_filesystem = getelementptr inbounds %struct.tree, %struct.tree* %23, i32 0, i32 28, !dbg !4211
  %24 = load %struct.filesystem*, %struct.filesystem** %current_filesystem, align 8, !dbg !4211
  %synthetic = getelementptr inbounds %struct.filesystem, %struct.filesystem* %24, i32 0, i32 1, !dbg !4212
  store i32 -1, i32* %synthetic, align 8, !dbg !4213
  %25 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !4214
  %current_filesystem28 = getelementptr inbounds %struct.tree, %struct.tree* %25, i32 0, i32 28, !dbg !4215
  %26 = load %struct.filesystem*, %struct.filesystem** %current_filesystem28, align 8, !dbg !4215
  %remote = getelementptr inbounds %struct.filesystem, %struct.filesystem* %26, i32 0, i32 2, !dbg !4216
  store i32 -1, i32* %remote, align 4, !dbg !4217
  %27 = load %struct.archive_read_disk*, %struct.archive_read_disk** %a.addr, align 8, !dbg !4218
  %archive29 = getelementptr inbounds %struct.archive_read_disk, %struct.archive_read_disk* %27, i32 0, i32 0, !dbg !4219
  %call30 = call i32* @__errno_location() #1, !dbg !4220
  %28 = load i32, i32* %call30, align 4, !dbg !4220
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive29, i32 %28, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.33, i32 0, i32 0)), !dbg !4221
  store i32 -25, i32* %retval, align 4, !dbg !4223
  br label %return, !dbg !4223

if.else31:                                        ; preds = %lor.lhs.false25
  %29 = load i32, i32* %xr, align 4, !dbg !4224
  %cmp32 = icmp eq i32 %29, 1, !dbg !4226
  br i1 %cmp32, label %if.then33, label %if.end39, !dbg !4227

if.then33:                                        ; preds = %if.else31
  %f_frsize = getelementptr inbounds %struct.statvfs, %struct.statvfs* %svfs, i32 0, i32 1, !dbg !4228
  %30 = load i64, i64* %f_frsize, align 8, !dbg !4228
  %31 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !4230
  %current_filesystem34 = getelementptr inbounds %struct.tree, %struct.tree* %31, i32 0, i32 28, !dbg !4231
  %32 = load %struct.filesystem*, %struct.filesystem** %current_filesystem34, align 8, !dbg !4231
  %xfer_align = getelementptr inbounds %struct.filesystem, %struct.filesystem* %32, i32 0, i32 8, !dbg !4232
  store i64 %30, i64* %xfer_align, align 8, !dbg !4233
  %33 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !4234
  %current_filesystem35 = getelementptr inbounds %struct.tree, %struct.tree* %33, i32 0, i32 28, !dbg !4235
  %34 = load %struct.filesystem*, %struct.filesystem** %current_filesystem35, align 8, !dbg !4235
  %max_xfer_size = getelementptr inbounds %struct.filesystem, %struct.filesystem* %34, i32 0, i32 6, !dbg !4236
  store i64 -1, i64* %max_xfer_size, align 8, !dbg !4237
  %f_bsize = getelementptr inbounds %struct.statvfs, %struct.statvfs* %svfs, i32 0, i32 0, !dbg !4238
  %35 = load i64, i64* %f_bsize, align 8, !dbg !4238
  %36 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !4239
  %current_filesystem36 = getelementptr inbounds %struct.tree, %struct.tree* %36, i32 0, i32 28, !dbg !4240
  %37 = load %struct.filesystem*, %struct.filesystem** %current_filesystem36, align 8, !dbg !4240
  %min_xfer_size = getelementptr inbounds %struct.filesystem, %struct.filesystem* %37, i32 0, i32 7, !dbg !4241
  store i64 %35, i64* %min_xfer_size, align 8, !dbg !4242
  %f_bsize37 = getelementptr inbounds %struct.statvfs, %struct.statvfs* %svfs, i32 0, i32 0, !dbg !4243
  %38 = load i64, i64* %f_bsize37, align 8, !dbg !4243
  %39 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !4244
  %current_filesystem38 = getelementptr inbounds %struct.tree, %struct.tree* %39, i32 0, i32 28, !dbg !4245
  %40 = load %struct.filesystem*, %struct.filesystem** %current_filesystem38, align 8, !dbg !4245
  %incr_xfer_size = getelementptr inbounds %struct.filesystem, %struct.filesystem* %40, i32 0, i32 5, !dbg !4246
  store i64 %38, i64* %incr_xfer_size, align 8, !dbg !4247
  br label %if.end39, !dbg !4248

if.end39:                                         ; preds = %if.then33, %if.else31
  br label %if.end40

if.end40:                                         ; preds = %if.end39
  %f_type = getelementptr inbounds %struct.statfs, %struct.statfs* %sfs, i32 0, i32 0, !dbg !4249
  %41 = load i64, i64* %f_type, align 8, !dbg !4249
  switch i64 %41, label %sw.default [
    i64 1397113167, label %sw.bb
    i64 4283649346, label %sw.bb
    i64 1937076805, label %sw.bb
    i64 22092, label %sw.bb
    i64 26985, label %sw.bb
    i64 20859, label %sw.bb
    i64 4979, label %sw.bb45
    i64 40864, label %sw.bb45
    i64 40866, label %sw.bb45
  ], !dbg !4250

sw.bb:                                            ; preds = %if.end40, %if.end40, %if.end40, %if.end40, %if.end40, %if.end40
  %42 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !4251
  %current_filesystem41 = getelementptr inbounds %struct.tree, %struct.tree* %42, i32 0, i32 28, !dbg !4253
  %43 = load %struct.filesystem*, %struct.filesystem** %current_filesystem41, align 8, !dbg !4253
  %remote42 = getelementptr inbounds %struct.filesystem, %struct.filesystem* %43, i32 0, i32 2, !dbg !4254
  store i32 1, i32* %remote42, align 4, !dbg !4255
  %44 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !4256
  %current_filesystem43 = getelementptr inbounds %struct.tree, %struct.tree* %44, i32 0, i32 28, !dbg !4257
  %45 = load %struct.filesystem*, %struct.filesystem** %current_filesystem43, align 8, !dbg !4257
  %synthetic44 = getelementptr inbounds %struct.filesystem, %struct.filesystem* %45, i32 0, i32 1, !dbg !4258
  store i32 0, i32* %synthetic44, align 8, !dbg !4259
  br label %sw.epilog, !dbg !4260

sw.bb45:                                          ; preds = %if.end40, %if.end40, %if.end40
  %46 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !4261
  %current_filesystem46 = getelementptr inbounds %struct.tree, %struct.tree* %46, i32 0, i32 28, !dbg !4262
  %47 = load %struct.filesystem*, %struct.filesystem** %current_filesystem46, align 8, !dbg !4262
  %remote47 = getelementptr inbounds %struct.filesystem, %struct.filesystem* %47, i32 0, i32 2, !dbg !4263
  store i32 0, i32* %remote47, align 4, !dbg !4264
  %48 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !4265
  %current_filesystem48 = getelementptr inbounds %struct.tree, %struct.tree* %48, i32 0, i32 28, !dbg !4266
  %49 = load %struct.filesystem*, %struct.filesystem** %current_filesystem48, align 8, !dbg !4266
  %synthetic49 = getelementptr inbounds %struct.filesystem, %struct.filesystem* %49, i32 0, i32 1, !dbg !4267
  store i32 1, i32* %synthetic49, align 8, !dbg !4268
  br label %sw.epilog, !dbg !4269

sw.default:                                       ; preds = %if.end40
  %50 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !4270
  %current_filesystem50 = getelementptr inbounds %struct.tree, %struct.tree* %50, i32 0, i32 28, !dbg !4271
  %51 = load %struct.filesystem*, %struct.filesystem** %current_filesystem50, align 8, !dbg !4271
  %remote51 = getelementptr inbounds %struct.filesystem, %struct.filesystem* %51, i32 0, i32 2, !dbg !4272
  store i32 0, i32* %remote51, align 4, !dbg !4273
  %52 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !4274
  %current_filesystem52 = getelementptr inbounds %struct.tree, %struct.tree* %52, i32 0, i32 28, !dbg !4275
  %53 = load %struct.filesystem*, %struct.filesystem** %current_filesystem52, align 8, !dbg !4275
  %synthetic53 = getelementptr inbounds %struct.filesystem, %struct.filesystem* %53, i32 0, i32 1, !dbg !4276
  store i32 0, i32* %synthetic53, align 8, !dbg !4277
  br label %sw.epilog, !dbg !4278

sw.epilog:                                        ; preds = %sw.default, %sw.bb45, %sw.bb
  %f_flag = getelementptr inbounds %struct.statvfs, %struct.statvfs* %svfs, i32 0, i32 9, !dbg !4279
  %54 = load i64, i64* %f_flag, align 8, !dbg !4279
  %and = and i64 %54, 1024, !dbg !4281
  %tobool54 = icmp ne i64 %and, 0, !dbg !4281
  br i1 %tobool54, label %if.then55, label %if.else57, !dbg !4282

if.then55:                                        ; preds = %sw.epilog
  %55 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !4283
  %current_filesystem56 = getelementptr inbounds %struct.tree, %struct.tree* %55, i32 0, i32 28, !dbg !4284
  %56 = load %struct.filesystem*, %struct.filesystem** %current_filesystem56, align 8, !dbg !4284
  %noatime = getelementptr inbounds %struct.filesystem, %struct.filesystem* %56, i32 0, i32 3, !dbg !4285
  store i32 1, i32* %noatime, align 8, !dbg !4286
  br label %if.end60, !dbg !4283

if.else57:                                        ; preds = %sw.epilog
  %57 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !4287
  %current_filesystem58 = getelementptr inbounds %struct.tree, %struct.tree* %57, i32 0, i32 28, !dbg !4288
  %58 = load %struct.filesystem*, %struct.filesystem** %current_filesystem58, align 8, !dbg !4288
  %noatime59 = getelementptr inbounds %struct.filesystem, %struct.filesystem* %58, i32 0, i32 3, !dbg !4289
  store i32 0, i32* %noatime59, align 8, !dbg !4290
  br label %if.end60

if.end60:                                         ; preds = %if.else57, %if.then55
  %f_namelen = getelementptr inbounds %struct.statfs, %struct.statfs* %sfs, i32 0, i32 8, !dbg !4291
  %59 = load i64, i64* %f_namelen, align 8, !dbg !4291
  %60 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !4292
  %current_filesystem61 = getelementptr inbounds %struct.tree, %struct.tree* %60, i32 0, i32 28, !dbg !4293
  %61 = load %struct.filesystem*, %struct.filesystem** %current_filesystem61, align 8, !dbg !4293
  %name_max = getelementptr inbounds %struct.filesystem, %struct.filesystem* %61, i32 0, i32 4, !dbg !4294
  store i64 %59, i64* %name_max, align 8, !dbg !4295
  store i32 0, i32* %retval, align 4, !dbg !4296
  br label %return, !dbg !4296

return:                                           ; preds = %if.end60, %if.then27, %if.then4
  %62 = load i32, i32* %retval, align 4, !dbg !4297
  ret i32 %62, !dbg !4297
}

; Function Attrs: nounwind uwtable
define internal i32 @tree_current_is_symblic_link_target(%struct.tree* %t) #0 !dbg !422 {
entry:
  %t.addr = alloca %struct.tree*, align 8
  store %struct.tree* %t, %struct.tree** %t.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tree** %t.addr, metadata !4298, metadata !460), !dbg !4299
  %0 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4300
  %call = call %struct.stat* @tree_current_lstat(%struct.tree* %0), !dbg !4301
  store %struct.stat* %call, %struct.stat** @tree_current_is_symblic_link_target.lst, align 8, !dbg !4302
  %1 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4303
  %call1 = call %struct.stat* @tree_current_stat(%struct.tree* %1), !dbg !4304
  store %struct.stat* %call1, %struct.stat** @tree_current_is_symblic_link_target.st, align 8, !dbg !4305
  %2 = load %struct.stat*, %struct.stat** @tree_current_is_symblic_link_target.st, align 8, !dbg !4306
  %cmp = icmp ne %struct.stat* %2, null, !dbg !4307
  br i1 %cmp, label %land.lhs.true, label %land.end, !dbg !4308

land.lhs.true:                                    ; preds = %entry
  %3 = load %struct.stat*, %struct.stat** @tree_current_is_symblic_link_target.lst, align 8, !dbg !4309
  %cmp2 = icmp ne %struct.stat* %3, null, !dbg !4311
  br i1 %cmp2, label %land.lhs.true3, label %land.end, !dbg !4312

land.lhs.true3:                                   ; preds = %land.lhs.true
  %4 = load %struct.stat*, %struct.stat** @tree_current_is_symblic_link_target.st, align 8, !dbg !4313
  %st_dev = getelementptr inbounds %struct.stat, %struct.stat* %4, i32 0, i32 0, !dbg !4314
  %5 = load i64, i64* %st_dev, align 8, !dbg !4314
  %6 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4315
  %current_filesystem = getelementptr inbounds %struct.tree, %struct.tree* %6, i32 0, i32 28, !dbg !4316
  %7 = load %struct.filesystem*, %struct.filesystem** %current_filesystem, align 8, !dbg !4316
  %dev = getelementptr inbounds %struct.filesystem, %struct.filesystem* %7, i32 0, i32 0, !dbg !4317
  %8 = load i64, i64* %dev, align 8, !dbg !4317
  %cmp4 = icmp eq i64 %5, %8, !dbg !4318
  br i1 %cmp4, label %land.rhs, label %land.end, !dbg !4319

land.rhs:                                         ; preds = %land.lhs.true3
  %9 = load %struct.stat*, %struct.stat** @tree_current_is_symblic_link_target.st, align 8, !dbg !4320
  %st_dev5 = getelementptr inbounds %struct.stat, %struct.stat* %9, i32 0, i32 0, !dbg !4321
  %10 = load i64, i64* %st_dev5, align 8, !dbg !4321
  %11 = load %struct.stat*, %struct.stat** @tree_current_is_symblic_link_target.lst, align 8, !dbg !4322
  %st_dev6 = getelementptr inbounds %struct.stat, %struct.stat* %11, i32 0, i32 0, !dbg !4323
  %12 = load i64, i64* %st_dev6, align 8, !dbg !4323
  %cmp7 = icmp ne i64 %10, %12, !dbg !4324
  br label %land.end

land.end:                                         ; preds = %land.rhs, %land.lhs.true3, %land.lhs.true, %entry
  %13 = phi i1 [ false, %land.lhs.true3 ], [ false, %land.lhs.true ], [ false, %entry ], [ %cmp7, %land.rhs ]
  %land.ext = zext i1 %13 to i32, !dbg !4325
  ret i32 %land.ext, !dbg !4326
}

declare i32 @openat(i32, i8*, i32, ...) #2

; Function Attrs: nounwind
declare i32 @fstatvfs(i32, %struct.statvfs*) #3

; Function Attrs: nounwind
declare i32 @fstatfs(i32, %struct.statfs*) #3

; Function Attrs: nounwind uwtable
define internal i32 @get_xfer_size(%struct.tree* %t, i32 %fd, i8* %path) #0 !dbg !423 {
entry:
  %retval = alloca i32, align 4
  %t.addr = alloca %struct.tree*, align 8
  %fd.addr = alloca i32, align 4
  %path.addr = alloca i8*, align 8
  store %struct.tree* %t, %struct.tree** %t.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tree** %t.addr, metadata !4328, metadata !460), !dbg !4329
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !4330, metadata !460), !dbg !4331
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !4332, metadata !460), !dbg !4333
  %0 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4334
  %current_filesystem = getelementptr inbounds %struct.tree, %struct.tree* %0, i32 0, i32 28, !dbg !4335
  %1 = load %struct.filesystem*, %struct.filesystem** %current_filesystem, align 8, !dbg !4335
  %xfer_align = getelementptr inbounds %struct.filesystem, %struct.filesystem* %1, i32 0, i32 8, !dbg !4336
  store i64 -1, i64* %xfer_align, align 8, !dbg !4337
  %call = call i32* @__errno_location() #1, !dbg !4338
  store i32 0, i32* %call, align 4, !dbg !4339
  %2 = load i32, i32* %fd.addr, align 4, !dbg !4340
  %cmp = icmp sge i32 %2, 0, !dbg !4342
  br i1 %cmp, label %if.then, label %if.else, !dbg !4343

if.then:                                          ; preds = %entry
  %3 = load i32, i32* %fd.addr, align 4, !dbg !4344
  %call1 = call i64 @fpathconf(i32 %3, i32 14) #6, !dbg !4346
  %4 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4347
  %current_filesystem2 = getelementptr inbounds %struct.tree, %struct.tree* %4, i32 0, i32 28, !dbg !4348
  %5 = load %struct.filesystem*, %struct.filesystem** %current_filesystem2, align 8, !dbg !4348
  %incr_xfer_size = getelementptr inbounds %struct.filesystem, %struct.filesystem* %5, i32 0, i32 5, !dbg !4349
  store i64 %call1, i64* %incr_xfer_size, align 8, !dbg !4350
  %6 = load i32, i32* %fd.addr, align 4, !dbg !4351
  %call3 = call i64 @fpathconf(i32 %6, i32 15) #6, !dbg !4352
  %7 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4353
  %current_filesystem4 = getelementptr inbounds %struct.tree, %struct.tree* %7, i32 0, i32 28, !dbg !4354
  %8 = load %struct.filesystem*, %struct.filesystem** %current_filesystem4, align 8, !dbg !4354
  %max_xfer_size = getelementptr inbounds %struct.filesystem, %struct.filesystem* %8, i32 0, i32 6, !dbg !4355
  store i64 %call3, i64* %max_xfer_size, align 8, !dbg !4356
  %9 = load i32, i32* %fd.addr, align 4, !dbg !4357
  %call5 = call i64 @fpathconf(i32 %9, i32 16) #6, !dbg !4358
  %10 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4359
  %current_filesystem6 = getelementptr inbounds %struct.tree, %struct.tree* %10, i32 0, i32 28, !dbg !4360
  %11 = load %struct.filesystem*, %struct.filesystem** %current_filesystem6, align 8, !dbg !4360
  %min_xfer_size = getelementptr inbounds %struct.filesystem, %struct.filesystem* %11, i32 0, i32 7, !dbg !4361
  store i64 %call5, i64* %min_xfer_size, align 8, !dbg !4362
  %12 = load i32, i32* %fd.addr, align 4, !dbg !4363
  %call7 = call i64 @fpathconf(i32 %12, i32 17) #6, !dbg !4364
  %13 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4365
  %current_filesystem8 = getelementptr inbounds %struct.tree, %struct.tree* %13, i32 0, i32 28, !dbg !4366
  %14 = load %struct.filesystem*, %struct.filesystem** %current_filesystem8, align 8, !dbg !4366
  %xfer_align9 = getelementptr inbounds %struct.filesystem, %struct.filesystem* %14, i32 0, i32 8, !dbg !4367
  store i64 %call7, i64* %xfer_align9, align 8, !dbg !4368
  br label %if.end24, !dbg !4369

if.else:                                          ; preds = %entry
  %15 = load i8*, i8** %path.addr, align 8, !dbg !4370
  %cmp10 = icmp ne i8* %15, null, !dbg !4373
  br i1 %cmp10, label %if.then11, label %if.end, !dbg !4370

if.then11:                                        ; preds = %if.else
  %16 = load i8*, i8** %path.addr, align 8, !dbg !4374
  %call12 = call i64 @pathconf(i8* %16, i32 14) #6, !dbg !4376
  %17 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4377
  %current_filesystem13 = getelementptr inbounds %struct.tree, %struct.tree* %17, i32 0, i32 28, !dbg !4378
  %18 = load %struct.filesystem*, %struct.filesystem** %current_filesystem13, align 8, !dbg !4378
  %incr_xfer_size14 = getelementptr inbounds %struct.filesystem, %struct.filesystem* %18, i32 0, i32 5, !dbg !4379
  store i64 %call12, i64* %incr_xfer_size14, align 8, !dbg !4380
  %19 = load i8*, i8** %path.addr, align 8, !dbg !4381
  %call15 = call i64 @pathconf(i8* %19, i32 15) #6, !dbg !4382
  %20 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4383
  %current_filesystem16 = getelementptr inbounds %struct.tree, %struct.tree* %20, i32 0, i32 28, !dbg !4384
  %21 = load %struct.filesystem*, %struct.filesystem** %current_filesystem16, align 8, !dbg !4384
  %max_xfer_size17 = getelementptr inbounds %struct.filesystem, %struct.filesystem* %21, i32 0, i32 6, !dbg !4385
  store i64 %call15, i64* %max_xfer_size17, align 8, !dbg !4386
  %22 = load i8*, i8** %path.addr, align 8, !dbg !4387
  %call18 = call i64 @pathconf(i8* %22, i32 16) #6, !dbg !4388
  %23 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4389
  %current_filesystem19 = getelementptr inbounds %struct.tree, %struct.tree* %23, i32 0, i32 28, !dbg !4390
  %24 = load %struct.filesystem*, %struct.filesystem** %current_filesystem19, align 8, !dbg !4390
  %min_xfer_size20 = getelementptr inbounds %struct.filesystem, %struct.filesystem* %24, i32 0, i32 7, !dbg !4391
  store i64 %call18, i64* %min_xfer_size20, align 8, !dbg !4392
  %25 = load i8*, i8** %path.addr, align 8, !dbg !4393
  %call21 = call i64 @pathconf(i8* %25, i32 17) #6, !dbg !4394
  %26 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4395
  %current_filesystem22 = getelementptr inbounds %struct.tree, %struct.tree* %26, i32 0, i32 28, !dbg !4396
  %27 = load %struct.filesystem*, %struct.filesystem** %current_filesystem22, align 8, !dbg !4396
  %xfer_align23 = getelementptr inbounds %struct.filesystem, %struct.filesystem* %27, i32 0, i32 8, !dbg !4397
  store i64 %call21, i64* %xfer_align23, align 8, !dbg !4398
  br label %if.end, !dbg !4399

if.end:                                           ; preds = %if.then11, %if.else
  br label %if.end24

if.end24:                                         ; preds = %if.end, %if.then
  %28 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4400
  %current_filesystem25 = getelementptr inbounds %struct.tree, %struct.tree* %28, i32 0, i32 28, !dbg !4402
  %29 = load %struct.filesystem*, %struct.filesystem** %current_filesystem25, align 8, !dbg !4402
  %xfer_align26 = getelementptr inbounds %struct.filesystem, %struct.filesystem* %29, i32 0, i32 8, !dbg !4403
  %30 = load i64, i64* %xfer_align26, align 8, !dbg !4403
  %cmp27 = icmp eq i64 %30, -1, !dbg !4404
  br i1 %cmp27, label %if.then28, label %if.else31, !dbg !4405

if.then28:                                        ; preds = %if.end24
  %call29 = call i32* @__errno_location() #1, !dbg !4406
  %31 = load i32, i32* %call29, align 4, !dbg !4406
  %cmp30 = icmp eq i32 %31, 22, !dbg !4407
  %cond = select i1 %cmp30, i32 1, i32 -1, !dbg !4408
  store i32 %cond, i32* %retval, align 4, !dbg !4409
  br label %return, !dbg !4409

if.else31:                                        ; preds = %if.end24
  store i32 0, i32* %retval, align 4, !dbg !4410
  br label %return, !dbg !4410

return:                                           ; preds = %if.else31, %if.then28
  %32 = load i32, i32* %retval, align 4, !dbg !4411
  ret i32 %32, !dbg !4411
}

; Function Attrs: nounwind
declare i64 @fpathconf(i32, i32) #3

; Function Attrs: nounwind
declare i64 @pathconf(i8*, i32) #3

declare i32 @archive_entry_sparse_reset(%struct.archive_entry*) #2

declare i32 @archive_entry_sparse_next(%struct.archive_entry*, i64*, i64*) #2

; Function Attrs: nounwind uwtable
define internal %struct.tree* @tree_reopen(%struct.tree* %t, i8* %path, i32 %restore_time) #0 !dbg !435 {
entry:
  %t.addr = alloca %struct.tree*, align 8
  %path.addr = alloca i8*, align 8
  %restore_time.addr = alloca i32, align 4
  store %struct.tree* %t, %struct.tree** %t.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tree** %t.addr, metadata !4412, metadata !460), !dbg !4413
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !4414, metadata !460), !dbg !4415
  store i32 %restore_time, i32* %restore_time.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %restore_time.addr, metadata !4416, metadata !460), !dbg !4417
  %0 = load i32, i32* %restore_time.addr, align 4, !dbg !4418
  %cmp = icmp ne i32 %0, 0, !dbg !4419
  %cond = select i1 %cmp, i32 128, i32 0, !dbg !4420
  %1 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4421
  %flags = getelementptr inbounds %struct.tree, %struct.tree* %1, i32 0, i32 6, !dbg !4422
  store i32 %cond, i32* %flags, align 8, !dbg !4423
  %2 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4424
  %flags1 = getelementptr inbounds %struct.tree, %struct.tree* %2, i32 0, i32 6, !dbg !4425
  %3 = load i32, i32* %flags1, align 8, !dbg !4426
  %or = or i32 %3, 256, !dbg !4426
  store i32 %or, i32* %flags1, align 8, !dbg !4426
  %4 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4427
  %visit_type = getelementptr inbounds %struct.tree, %struct.tree* %4, i32 0, i32 7, !dbg !4428
  store i32 0, i32* %visit_type, align 4, !dbg !4429
  %5 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4430
  %tree_errno = getelementptr inbounds %struct.tree, %struct.tree* %5, i32 0, i32 8, !dbg !4431
  store i32 0, i32* %tree_errno, align 8, !dbg !4432
  %6 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4433
  %dirname_length = getelementptr inbounds %struct.tree, %struct.tree* %6, i32 0, i32 11, !dbg !4434
  store i64 0, i64* %dirname_length, align 8, !dbg !4435
  %7 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4436
  %depth = getelementptr inbounds %struct.tree, %struct.tree* %7, i32 0, i32 12, !dbg !4437
  store i32 0, i32* %depth, align 8, !dbg !4438
  %8 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4439
  %descend = getelementptr inbounds %struct.tree, %struct.tree* %8, i32 0, i32 19, !dbg !4440
  store i32 0, i32* %descend, align 8, !dbg !4441
  %9 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4442
  %current = getelementptr inbounds %struct.tree, %struct.tree* %9, i32 0, i32 1, !dbg !4443
  store %struct.tree_entry* null, %struct.tree_entry** %current, align 8, !dbg !4444
  %10 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4445
  %d = getelementptr inbounds %struct.tree, %struct.tree* %10, i32 0, i32 2, !dbg !4446
  store %struct.__dirstream* null, %struct.__dirstream** %d, align 8, !dbg !4447
  %11 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4448
  %initial_symlink_mode = getelementptr inbounds %struct.tree, %struct.tree* %11, i32 0, i32 26, !dbg !4449
  %12 = load i8, i8* %initial_symlink_mode, align 8, !dbg !4449
  %13 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4450
  %symlink_mode = getelementptr inbounds %struct.tree, %struct.tree* %13, i32 0, i32 27, !dbg !4451
  store i8 %12, i8* %symlink_mode, align 1, !dbg !4452
  %14 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4453
  %path2 = getelementptr inbounds %struct.tree, %struct.tree* %14, i32 0, i32 9, !dbg !4453
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %path2, i32 0, i32 1, !dbg !4453
  store i64 0, i64* %length, align 8, !dbg !4453
  %15 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4454
  %entry_fd = getelementptr inbounds %struct.tree, %struct.tree* %15, i32 0, i32 34, !dbg !4455
  store i32 -1, i32* %entry_fd, align 8, !dbg !4456
  %16 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4457
  %entry_eof = getelementptr inbounds %struct.tree, %struct.tree* %16, i32 0, i32 35, !dbg !4458
  store i32 0, i32* %entry_eof, align 4, !dbg !4459
  %17 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4460
  %entry_remaining_bytes = getelementptr inbounds %struct.tree, %struct.tree* %17, i32 0, i32 36, !dbg !4461
  store i64 0, i64* %entry_remaining_bytes, align 8, !dbg !4462
  %18 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4463
  %initial_filesystem_id = getelementptr inbounds %struct.tree, %struct.tree* %18, i32 0, i32 30, !dbg !4464
  store i32 -1, i32* %initial_filesystem_id, align 8, !dbg !4465
  %19 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4466
  %20 = load i8*, i8** %path.addr, align 8, !dbg !4467
  call void @tree_push(%struct.tree* %19, i8* %20, i32 0, i64 0, i64 0, %struct.restore_time* null), !dbg !4468
  %21 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4469
  %stack = getelementptr inbounds %struct.tree, %struct.tree* %21, i32 0, i32 0, !dbg !4470
  %22 = load %struct.tree_entry*, %struct.tree_entry** %stack, align 8, !dbg !4470
  %flags3 = getelementptr inbounds %struct.tree_entry, %struct.tree_entry* %22, i32 0, i32 7, !dbg !4471
  store i32 4, i32* %flags3, align 8, !dbg !4472
  %23 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4473
  %openCount = getelementptr inbounds %struct.tree, %struct.tree* %23, i32 0, i32 13, !dbg !4474
  store i32 1, i32* %openCount, align 4, !dbg !4475
  %24 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4476
  %maxOpenCount = getelementptr inbounds %struct.tree, %struct.tree* %24, i32 0, i32 14, !dbg !4477
  store i32 1, i32* %maxOpenCount, align 8, !dbg !4478
  %call = call i32 (i8*, i32, ...) @open(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.35, i32 0, i32 0), i32 524288), !dbg !4479
  %25 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4480
  %initial_dir_fd = getelementptr inbounds %struct.tree, %struct.tree* %25, i32 0, i32 15, !dbg !4481
  store i32 %call, i32* %initial_dir_fd, align 4, !dbg !4482
  %26 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4483
  %initial_dir_fd4 = getelementptr inbounds %struct.tree, %struct.tree* %26, i32 0, i32 15, !dbg !4484
  %27 = load i32, i32* %initial_dir_fd4, align 4, !dbg !4484
  call void @__archive_ensure_cloexec_flag(i32 %27), !dbg !4485
  %28 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4486
  %initial_dir_fd5 = getelementptr inbounds %struct.tree, %struct.tree* %28, i32 0, i32 15, !dbg !4487
  %29 = load i32, i32* %initial_dir_fd5, align 4, !dbg !4487
  %call6 = call i32 @tree_dup(i32 %29), !dbg !4488
  %30 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4489
  %working_dir_fd = getelementptr inbounds %struct.tree, %struct.tree* %30, i32 0, i32 16, !dbg !4490
  store i32 %call6, i32* %working_dir_fd, align 8, !dbg !4491
  %31 = load %struct.tree*, %struct.tree** %t.addr, align 8, !dbg !4492
  ret %struct.tree* %31, !dbg !4493
}

; Function Attrs: nounwind uwtable
define internal %struct.tree* @tree_open(i8* %path, i32 %symlink_mode, i32 %restore_time) #0 !dbg !438 {
entry:
  %retval = alloca %struct.tree*, align 8
  %path.addr = alloca i8*, align 8
  %symlink_mode.addr = alloca i32, align 4
  %restore_time.addr = alloca i32, align 4
  %t = alloca %struct.tree*, align 8
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !4494, metadata !460), !dbg !4495
  store i32 %symlink_mode, i32* %symlink_mode.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %symlink_mode.addr, metadata !4496, metadata !460), !dbg !4497
  store i32 %restore_time, i32* %restore_time.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %restore_time.addr, metadata !4498, metadata !460), !dbg !4499
  call void @llvm.dbg.declare(metadata %struct.tree** %t, metadata !4500, metadata !460), !dbg !4501
  %call = call noalias i8* @calloc(i64 1, i64 576) #6, !dbg !4502
  %0 = bitcast i8* %call to %struct.tree*, !dbg !4502
  store %struct.tree* %0, %struct.tree** %t, align 8, !dbg !4504
  %cmp = icmp eq %struct.tree* %0, null, !dbg !4505
  br i1 %cmp, label %if.then, label %if.end, !dbg !4506

if.then:                                          ; preds = %entry
  store %struct.tree* null, %struct.tree** %retval, align 8, !dbg !4507
  br label %return, !dbg !4507

if.end:                                           ; preds = %entry
  br label %do.body, !dbg !4508

do.body:                                          ; preds = %if.end
  %1 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !4509
  %path1 = getelementptr inbounds %struct.tree, %struct.tree* %1, i32 0, i32 9, !dbg !4509
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %path1, i32 0, i32 0, !dbg !4509
  store i8* null, i8** %s, align 8, !dbg !4509
  %2 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !4509
  %path2 = getelementptr inbounds %struct.tree, %struct.tree* %2, i32 0, i32 9, !dbg !4509
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %path2, i32 0, i32 1, !dbg !4509
  store i64 0, i64* %length, align 8, !dbg !4509
  %3 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !4509
  %path3 = getelementptr inbounds %struct.tree, %struct.tree* %3, i32 0, i32 9, !dbg !4509
  %buffer_length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %path3, i32 0, i32 2, !dbg !4509
  store i64 0, i64* %buffer_length, align 8, !dbg !4509
  br label %do.end, !dbg !4509

do.end:                                           ; preds = %do.body
  %4 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !4512
  %path4 = getelementptr inbounds %struct.tree, %struct.tree* %4, i32 0, i32 9, !dbg !4513
  %call5 = call %struct.archive_string* @archive_string_ensure(%struct.archive_string* %path4, i64 31), !dbg !4514
  %5 = load i32, i32* %symlink_mode.addr, align 4, !dbg !4515
  %conv = trunc i32 %5 to i8, !dbg !4515
  %6 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !4516
  %initial_symlink_mode = getelementptr inbounds %struct.tree, %struct.tree* %6, i32 0, i32 26, !dbg !4517
  store i8 %conv, i8* %initial_symlink_mode, align 8, !dbg !4518
  %7 = load %struct.tree*, %struct.tree** %t, align 8, !dbg !4519
  %8 = load i8*, i8** %path.addr, align 8, !dbg !4520
  %9 = load i32, i32* %restore_time.addr, align 4, !dbg !4521
  %call6 = call %struct.tree* @tree_reopen(%struct.tree* %7, i8* %8, i32 %9), !dbg !4522
  store %struct.tree* %call6, %struct.tree** %retval, align 8, !dbg !4523
  br label %return, !dbg !4523

return:                                           ; preds = %do.end, %if.then
  %10 = load %struct.tree*, %struct.tree** %retval, align 8, !dbg !4524
  ret %struct.tree* %10, !dbg !4524
}

declare i32 @open(i8*, i32, ...) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind }
attributes #7 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!456, !457}
!llvm.ident = !{!458}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !42, subprograms: !333, globals: !449)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_disk_posix.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{!3, !18}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 80, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/statvfs.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!5 = !{!6, !7, !8, !9, !10, !11, !12, !13, !14, !15, !16, !17}
!6 = !DIEnumerator(name: "ST_RDONLY", value: 1)
!7 = !DIEnumerator(name: "ST_NOSUID", value: 2)
!8 = !DIEnumerator(name: "ST_NODEV", value: 4)
!9 = !DIEnumerator(name: "ST_NOEXEC", value: 8)
!10 = !DIEnumerator(name: "ST_SYNCHRONOUS", value: 16)
!11 = !DIEnumerator(name: "ST_MANDLOCK", value: 64)
!12 = !DIEnumerator(name: "ST_WRITE", value: 128)
!13 = !DIEnumerator(name: "ST_APPEND", value: 256)
!14 = !DIEnumerator(name: "ST_IMMUTABLE", value: 512)
!15 = !DIEnumerator(name: "ST_NOATIME", value: 1024)
!16 = !DIEnumerator(name: "ST_NODIRATIME", value: 2048)
!17 = !DIEnumerator(name: "ST_RELATIME", value: 4096)
!18 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !19, line: 24, size: 32, align: 32, elements: !20)
!19 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/confname.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!20 = !{!21, !22, !23, !24, !25, !26, !27, !28, !29, !30, !31, !32, !33, !34, !35, !36, !37, !38, !39, !40, !41}
!21 = !DIEnumerator(name: "_PC_LINK_MAX", value: 0)
!22 = !DIEnumerator(name: "_PC_MAX_CANON", value: 1)
!23 = !DIEnumerator(name: "_PC_MAX_INPUT", value: 2)
!24 = !DIEnumerator(name: "_PC_NAME_MAX", value: 3)
!25 = !DIEnumerator(name: "_PC_PATH_MAX", value: 4)
!26 = !DIEnumerator(name: "_PC_PIPE_BUF", value: 5)
!27 = !DIEnumerator(name: "_PC_CHOWN_RESTRICTED", value: 6)
!28 = !DIEnumerator(name: "_PC_NO_TRUNC", value: 7)
!29 = !DIEnumerator(name: "_PC_VDISABLE", value: 8)
!30 = !DIEnumerator(name: "_PC_SYNC_IO", value: 9)
!31 = !DIEnumerator(name: "_PC_ASYNC_IO", value: 10)
!32 = !DIEnumerator(name: "_PC_PRIO_IO", value: 11)
!33 = !DIEnumerator(name: "_PC_SOCK_MAXBUF", value: 12)
!34 = !DIEnumerator(name: "_PC_FILESIZEBITS", value: 13)
!35 = !DIEnumerator(name: "_PC_REC_INCR_XFER_SIZE", value: 14)
!36 = !DIEnumerator(name: "_PC_REC_MAX_XFER_SIZE", value: 15)
!37 = !DIEnumerator(name: "_PC_REC_MIN_XFER_SIZE", value: 16)
!38 = !DIEnumerator(name: "_PC_REC_XFER_ALIGN", value: 17)
!39 = !DIEnumerator(name: "_PC_ALLOC_SIZE_MIN", value: 18)
!40 = !DIEnumerator(name: "_PC_SYMLINK_MAX", value: 19)
!41 = !DIEnumerator(name: "_PC_2_SYMLINKS", value: 20)
!42 = !{!43, !311, !91, !331, !332, !182, !270}
!43 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !44, size: 64, align: 64)
!44 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_disk", file: !45, line: 39, size: 2432, align: 64, elements: !46)
!45 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_disk_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!46 = !{!47, !149, !150, !151, !152, !297, !301, !305, !306, !307, !312, !316, !317, !318, !319, !320, !324, !325, !326, !330}
!47 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !44, file: !45, line: 40, baseType: !48, size: 1280, align: 64)
!48 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !49, line: 89, size: 1280, align: 64, elements: !50)
!49 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!50 = !{!51, !53, !54, !122, !123, !124, !125, !126, !127, !128, !129, !137, !138, !139, !140, !143, !144, !145, !146, !147, !148}
!51 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !48, file: !49, line: 96, baseType: !52, size: 32, align: 32)
!52 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!53 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !48, file: !49, line: 97, baseType: !52, size: 32, align: 32, offset: 32)
!54 = !DIDerivedType(tag: DW_TAG_member, name: "vtable", scope: !48, file: !49, line: 103, baseType: !55, size: 64, align: 64, offset: 64)
!55 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !56, size: 64, align: 64)
!56 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_vtable", file: !49, line: 63, size: 832, align: 64, elements: !57)
!57 = !{!58, !64, !65, !72, !73, !87, !93, !98, !99, !106, !107, !111, !115}
!58 = !DIDerivedType(tag: DW_TAG_member, name: "archive_close", scope: !56, file: !49, line: 64, baseType: !59, size: 64, align: 64)
!59 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !60, size: 64, align: 64)
!60 = !DISubroutineType(types: !61)
!61 = !{!62, !63}
!62 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!63 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !48, size: 64, align: 64)
!64 = !DIDerivedType(tag: DW_TAG_member, name: "archive_free", scope: !56, file: !49, line: 65, baseType: !59, size: 64, align: 64, offset: 64)
!65 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_header", scope: !56, file: !49, line: 66, baseType: !66, size: 64, align: 64, offset: 128)
!66 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !67, size: 64, align: 64)
!67 = !DISubroutineType(types: !68)
!68 = !{!62, !63, !69}
!69 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !70, size: 64, align: 64)
!70 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_entry", file: !71, line: 180, flags: DIFlagFwdDecl)
!71 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!72 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_finish_entry", scope: !56, file: !49, line: 68, baseType: !59, size: 64, align: 64, offset: 192)
!73 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data", scope: !56, file: !49, line: 69, baseType: !74, size: 64, align: 64, offset: 256)
!74 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !75, size: 64, align: 64)
!75 = !DISubroutineType(types: !76)
!76 = !{!77, !63, !82, !84}
!77 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !78, line: 109, baseType: !79)
!78 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!79 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !80, line: 172, baseType: !81)
!80 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!81 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!82 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !83, size: 64, align: 64)
!83 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!84 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !85, line: 62, baseType: !86)
!85 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!86 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data_block", scope: !56, file: !49, line: 71, baseType: !88, size: 64, align: 64, offset: 320)
!88 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !89, size: 64, align: 64)
!89 = !DISubroutineType(types: !90)
!90 = !{!77, !63, !82, !84, !91}
!91 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !92, line: 40, baseType: !81)
!92 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!93 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header", scope: !56, file: !49, line: 74, baseType: !94, size: 64, align: 64, offset: 384)
!94 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !95, size: 64, align: 64)
!95 = !DISubroutineType(types: !96)
!96 = !{!62, !63, !97}
!97 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !69, size: 64, align: 64)
!98 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header2", scope: !56, file: !49, line: 76, baseType: !66, size: 64, align: 64, offset: 448)
!99 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_data_block", scope: !56, file: !49, line: 78, baseType: !100, size: 64, align: 64, offset: 512)
!100 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !101, size: 64, align: 64)
!101 = !DISubroutineType(types: !102)
!102 = !{!62, !63, !103, !104, !105}
!103 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !82, size: 64, align: 64)
!104 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !84, size: 64, align: 64)
!105 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !91, size: 64, align: 64)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_count", scope: !56, file: !49, line: 81, baseType: !59, size: 64, align: 64, offset: 576)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_bytes", scope: !56, file: !49, line: 82, baseType: !108, size: 64, align: 64, offset: 640)
!108 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !109, size: 64, align: 64)
!109 = !DISubroutineType(types: !110)
!110 = !{!91, !63, !62}
!111 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_code", scope: !56, file: !49, line: 83, baseType: !112, size: 64, align: 64, offset: 704)
!112 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !113, size: 64, align: 64)
!113 = !DISubroutineType(types: !114)
!114 = !{!62, !63, !62}
!115 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_name", scope: !56, file: !49, line: 84, baseType: !116, size: 64, align: 64, offset: 768)
!116 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !117, size: 64, align: 64)
!117 = !DISubroutineType(types: !118)
!118 = !{!119, !63, !62}
!119 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !120, size: 64, align: 64)
!120 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !121)
!121 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!122 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format", scope: !48, file: !49, line: 105, baseType: !62, size: 32, align: 32, offset: 128)
!123 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format_name", scope: !48, file: !49, line: 106, baseType: !119, size: 64, align: 64, offset: 192)
!124 = !DIDerivedType(tag: DW_TAG_member, name: "compression_code", scope: !48, file: !49, line: 108, baseType: !62, size: 32, align: 32, offset: 256)
!125 = !DIDerivedType(tag: DW_TAG_member, name: "compression_name", scope: !48, file: !49, line: 109, baseType: !119, size: 64, align: 64, offset: 320)
!126 = !DIDerivedType(tag: DW_TAG_member, name: "file_count", scope: !48, file: !49, line: 112, baseType: !62, size: 32, align: 32, offset: 384)
!127 = !DIDerivedType(tag: DW_TAG_member, name: "archive_error_number", scope: !48, file: !49, line: 114, baseType: !62, size: 32, align: 32, offset: 416)
!128 = !DIDerivedType(tag: DW_TAG_member, name: "error", scope: !48, file: !49, line: 115, baseType: !119, size: 64, align: 64, offset: 448)
!129 = !DIDerivedType(tag: DW_TAG_member, name: "error_string", scope: !48, file: !49, line: 116, baseType: !130, size: 192, align: 64, offset: 512)
!130 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string", file: !131, line: 58, size: 192, align: 64, elements: !132)
!131 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_string.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!132 = !{!133, !135, !136}
!133 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !130, file: !131, line: 59, baseType: !134, size: 64, align: 64)
!134 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !121, size: 64, align: 64)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !130, file: !131, line: 60, baseType: !84, size: 64, align: 64, offset: 64)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !130, file: !131, line: 61, baseType: !84, size: 64, align: 64, offset: 128)
!137 = !DIDerivedType(tag: DW_TAG_member, name: "current_code", scope: !48, file: !49, line: 118, baseType: !134, size: 64, align: 64, offset: 704)
!138 = !DIDerivedType(tag: DW_TAG_member, name: "current_codepage", scope: !48, file: !49, line: 119, baseType: !52, size: 32, align: 32, offset: 768)
!139 = !DIDerivedType(tag: DW_TAG_member, name: "current_oemcp", scope: !48, file: !49, line: 120, baseType: !52, size: 32, align: 32, offset: 800)
!140 = !DIDerivedType(tag: DW_TAG_member, name: "sconv", scope: !48, file: !49, line: 121, baseType: !141, size: 64, align: 64, offset: 832)
!141 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !142, size: 64, align: 64)
!142 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string_conv", file: !131, line: 70, flags: DIFlagFwdDecl)
!143 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_block", scope: !48, file: !49, line: 127, baseType: !119, size: 64, align: 64, offset: 896)
!144 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_offset", scope: !48, file: !49, line: 128, baseType: !91, size: 64, align: 64, offset: 960)
!145 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_output_offset", scope: !48, file: !49, line: 129, baseType: !91, size: 64, align: 64, offset: 1024)
!146 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_remaining", scope: !48, file: !49, line: 130, baseType: !84, size: 64, align: 64, offset: 1088)
!147 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_is_posix_read", scope: !48, file: !49, line: 137, baseType: !121, size: 8, align: 8, offset: 1152)
!148 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_requested", scope: !48, file: !49, line: 138, baseType: !84, size: 64, align: 64, offset: 1216)
!149 = !DIDerivedType(tag: DW_TAG_member, name: "entry", scope: !44, file: !45, line: 43, baseType: !69, size: 64, align: 64, offset: 1280)
!150 = !DIDerivedType(tag: DW_TAG_member, name: "symlink_mode", scope: !44, file: !45, line: 51, baseType: !121, size: 8, align: 8, offset: 1344)
!151 = !DIDerivedType(tag: DW_TAG_member, name: "follow_symlinks", scope: !44, file: !45, line: 58, baseType: !121, size: 8, align: 8, offset: 1352)
!152 = !DIDerivedType(tag: DW_TAG_member, name: "tree", scope: !44, file: !45, line: 61, baseType: !153, size: 64, align: 64, offset: 1408)
!153 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !154, size: 64, align: 64)
!154 = !DICompositeType(tag: DW_TAG_structure_type, name: "tree", file: !1, line: 197, size: 4608, align: 64, elements: !155)
!155 = !{!156, !185, !186, !191, !208, !209, !210, !211, !212, !213, !214, !215, !216, !217, !218, !219, !220, !221, !254, !255, !256, !257, !258, !264, !265, !266, !267, !268, !269, !286, !287, !288, !289, !290, !291, !292, !293, !294, !295, !296}
!156 = !DIDerivedType(tag: DW_TAG_member, name: "stack", scope: !154, file: !1, line: 198, baseType: !157, size: 64, align: 64)
!157 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !158, size: 64, align: 64)
!158 = !DICompositeType(tag: DW_TAG_structure_type, name: "tree_entry", file: !1, line: 147, size: 1088, align: 64, elements: !159)
!159 = !{!160, !161, !162, !163, !164, !165, !166, !167, !168, !169, !170}
!160 = !DIDerivedType(tag: DW_TAG_member, name: "depth", scope: !158, file: !1, line: 148, baseType: !62, size: 32, align: 32)
!161 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !158, file: !1, line: 149, baseType: !157, size: 64, align: 64, offset: 64)
!162 = !DIDerivedType(tag: DW_TAG_member, name: "parent", scope: !158, file: !1, line: 150, baseType: !157, size: 64, align: 64, offset: 128)
!163 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !158, file: !1, line: 151, baseType: !130, size: 192, align: 64, offset: 192)
!164 = !DIDerivedType(tag: DW_TAG_member, name: "dirname_length", scope: !158, file: !1, line: 152, baseType: !84, size: 64, align: 64, offset: 384)
!165 = !DIDerivedType(tag: DW_TAG_member, name: "dev", scope: !158, file: !1, line: 153, baseType: !91, size: 64, align: 64, offset: 448)
!166 = !DIDerivedType(tag: DW_TAG_member, name: "ino", scope: !158, file: !1, line: 154, baseType: !91, size: 64, align: 64, offset: 512)
!167 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !158, file: !1, line: 155, baseType: !62, size: 32, align: 32, offset: 576)
!168 = !DIDerivedType(tag: DW_TAG_member, name: "filesystem_id", scope: !158, file: !1, line: 156, baseType: !62, size: 32, align: 32, offset: 608)
!169 = !DIDerivedType(tag: DW_TAG_member, name: "symlink_parent_fd", scope: !158, file: !1, line: 158, baseType: !62, size: 32, align: 32, offset: 640)
!170 = !DIDerivedType(tag: DW_TAG_member, name: "restore_time", scope: !158, file: !1, line: 160, baseType: !171, size: 384, align: 64, offset: 704)
!171 = !DICompositeType(tag: DW_TAG_structure_type, name: "restore_time", file: !1, line: 137, size: 384, align: 64, elements: !172)
!172 = !{!173, !174, !178, !179, !180, !181, !184}
!173 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !171, file: !1, line: 138, baseType: !119, size: 64, align: 64)
!174 = !DIDerivedType(tag: DW_TAG_member, name: "mtime", scope: !171, file: !1, line: 139, baseType: !175, size: 64, align: 64, offset: 64)
!175 = !DIDerivedType(tag: DW_TAG_typedef, name: "time_t", file: !176, line: 75, baseType: !177)
!176 = !DIFile(filename: "/usr/include/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!177 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !80, line: 139, baseType: !81)
!178 = !DIDerivedType(tag: DW_TAG_member, name: "mtime_nsec", scope: !171, file: !1, line: 140, baseType: !81, size: 64, align: 64, offset: 128)
!179 = !DIDerivedType(tag: DW_TAG_member, name: "atime", scope: !171, file: !1, line: 141, baseType: !175, size: 64, align: 64, offset: 192)
!180 = !DIDerivedType(tag: DW_TAG_member, name: "atime_nsec", scope: !171, file: !1, line: 142, baseType: !81, size: 64, align: 64, offset: 256)
!181 = !DIDerivedType(tag: DW_TAG_member, name: "filetype", scope: !171, file: !1, line: 143, baseType: !182, size: 32, align: 32, offset: 320)
!182 = !DIDerivedType(tag: DW_TAG_typedef, name: "mode_t", file: !78, line: 70, baseType: !183)
!183 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !80, line: 129, baseType: !52)
!184 = !DIDerivedType(tag: DW_TAG_member, name: "noatime", scope: !171, file: !1, line: 144, baseType: !62, size: 32, align: 32, offset: 352)
!185 = !DIDerivedType(tag: DW_TAG_member, name: "current", scope: !154, file: !1, line: 199, baseType: !157, size: 64, align: 64, offset: 64)
!186 = !DIDerivedType(tag: DW_TAG_member, name: "d", scope: !154, file: !1, line: 200, baseType: !187, size: 64, align: 64, offset: 128)
!187 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !188, size: 64, align: 64)
!188 = !DIDerivedType(tag: DW_TAG_typedef, name: "DIR", file: !189, line: 127, baseType: !190)
!189 = !DIFile(filename: "/usr/include/dirent.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!190 = !DICompositeType(tag: DW_TAG_structure_type, name: "__dirstream", file: !189, line: 127, flags: DIFlagFwdDecl)
!191 = !DIDerivedType(tag: DW_TAG_member, name: "de", scope: !154, file: !1, line: 202, baseType: !192, size: 64, align: 64, offset: 192)
!192 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !193, size: 64, align: 64)
!193 = !DICompositeType(tag: DW_TAG_structure_type, name: "dirent", file: !194, line: 22, size: 2240, align: 64, elements: !195)
!194 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/dirent.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!195 = !{!196, !198, !200, !202, !204}
!196 = !DIDerivedType(tag: DW_TAG_member, name: "d_ino", scope: !193, file: !194, line: 25, baseType: !197, size: 64, align: 64)
!197 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ino_t", file: !80, line: 127, baseType: !86)
!198 = !DIDerivedType(tag: DW_TAG_member, name: "d_off", scope: !193, file: !194, line: 26, baseType: !199, size: 64, align: 64, offset: 64)
!199 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off_t", file: !80, line: 131, baseType: !81)
!200 = !DIDerivedType(tag: DW_TAG_member, name: "d_reclen", scope: !193, file: !194, line: 31, baseType: !201, size: 16, align: 16, offset: 128)
!201 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!202 = !DIDerivedType(tag: DW_TAG_member, name: "d_type", scope: !193, file: !194, line: 32, baseType: !203, size: 8, align: 8, offset: 144)
!203 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!204 = !DIDerivedType(tag: DW_TAG_member, name: "d_name", scope: !193, file: !194, line: 33, baseType: !205, size: 2048, align: 8, offset: 152)
!205 = !DICompositeType(tag: DW_TAG_array_type, baseType: !121, size: 2048, align: 8, elements: !206)
!206 = !{!207}
!207 = !DISubrange(count: 256)
!208 = !DIDerivedType(tag: DW_TAG_member, name: "dirent", scope: !154, file: !1, line: 204, baseType: !192, size: 64, align: 64, offset: 256)
!209 = !DIDerivedType(tag: DW_TAG_member, name: "dirent_allocated", scope: !154, file: !1, line: 205, baseType: !84, size: 64, align: 64, offset: 320)
!210 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !154, file: !1, line: 207, baseType: !62, size: 32, align: 32, offset: 384)
!211 = !DIDerivedType(tag: DW_TAG_member, name: "visit_type", scope: !154, file: !1, line: 208, baseType: !62, size: 32, align: 32, offset: 416)
!212 = !DIDerivedType(tag: DW_TAG_member, name: "tree_errno", scope: !154, file: !1, line: 210, baseType: !62, size: 32, align: 32, offset: 448)
!213 = !DIDerivedType(tag: DW_TAG_member, name: "path", scope: !154, file: !1, line: 213, baseType: !130, size: 192, align: 64, offset: 512)
!214 = !DIDerivedType(tag: DW_TAG_member, name: "basename", scope: !154, file: !1, line: 216, baseType: !119, size: 64, align: 64, offset: 704)
!215 = !DIDerivedType(tag: DW_TAG_member, name: "dirname_length", scope: !154, file: !1, line: 218, baseType: !84, size: 64, align: 64, offset: 768)
!216 = !DIDerivedType(tag: DW_TAG_member, name: "depth", scope: !154, file: !1, line: 220, baseType: !62, size: 32, align: 32, offset: 832)
!217 = !DIDerivedType(tag: DW_TAG_member, name: "openCount", scope: !154, file: !1, line: 221, baseType: !62, size: 32, align: 32, offset: 864)
!218 = !DIDerivedType(tag: DW_TAG_member, name: "maxOpenCount", scope: !154, file: !1, line: 222, baseType: !62, size: 32, align: 32, offset: 896)
!219 = !DIDerivedType(tag: DW_TAG_member, name: "initial_dir_fd", scope: !154, file: !1, line: 223, baseType: !62, size: 32, align: 32, offset: 928)
!220 = !DIDerivedType(tag: DW_TAG_member, name: "working_dir_fd", scope: !154, file: !1, line: 224, baseType: !62, size: 32, align: 32, offset: 960)
!221 = !DIDerivedType(tag: DW_TAG_member, name: "lst", scope: !154, file: !1, line: 226, baseType: !222, size: 1152, align: 64, offset: 1024)
!222 = !DICompositeType(tag: DW_TAG_structure_type, name: "stat", file: !223, line: 46, size: 1152, align: 64, elements: !224)
!223 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/stat.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!224 = !{!225, !227, !228, !230, !231, !233, !235, !236, !237, !238, !240, !242, !248, !249, !250}
!225 = !DIDerivedType(tag: DW_TAG_member, name: "st_dev", scope: !222, file: !223, line: 48, baseType: !226, size: 64, align: 64)
!226 = !DIDerivedType(tag: DW_TAG_typedef, name: "__dev_t", file: !80, line: 124, baseType: !86)
!227 = !DIDerivedType(tag: DW_TAG_member, name: "st_ino", scope: !222, file: !223, line: 53, baseType: !197, size: 64, align: 64, offset: 64)
!228 = !DIDerivedType(tag: DW_TAG_member, name: "st_nlink", scope: !222, file: !223, line: 61, baseType: !229, size: 64, align: 64, offset: 128)
!229 = !DIDerivedType(tag: DW_TAG_typedef, name: "__nlink_t", file: !80, line: 130, baseType: !86)
!230 = !DIDerivedType(tag: DW_TAG_member, name: "st_mode", scope: !222, file: !223, line: 62, baseType: !183, size: 32, align: 32, offset: 192)
!231 = !DIDerivedType(tag: DW_TAG_member, name: "st_uid", scope: !222, file: !223, line: 64, baseType: !232, size: 32, align: 32, offset: 224)
!232 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uid_t", file: !80, line: 125, baseType: !52)
!233 = !DIDerivedType(tag: DW_TAG_member, name: "st_gid", scope: !222, file: !223, line: 65, baseType: !234, size: 32, align: 32, offset: 256)
!234 = !DIDerivedType(tag: DW_TAG_typedef, name: "__gid_t", file: !80, line: 126, baseType: !52)
!235 = !DIDerivedType(tag: DW_TAG_member, name: "__pad0", scope: !222, file: !223, line: 67, baseType: !62, size: 32, align: 32, offset: 288)
!236 = !DIDerivedType(tag: DW_TAG_member, name: "st_rdev", scope: !222, file: !223, line: 69, baseType: !226, size: 64, align: 64, offset: 320)
!237 = !DIDerivedType(tag: DW_TAG_member, name: "st_size", scope: !222, file: !223, line: 74, baseType: !199, size: 64, align: 64, offset: 384)
!238 = !DIDerivedType(tag: DW_TAG_member, name: "st_blksize", scope: !222, file: !223, line: 78, baseType: !239, size: 64, align: 64, offset: 448)
!239 = !DIDerivedType(tag: DW_TAG_typedef, name: "__blksize_t", file: !80, line: 153, baseType: !81)
!240 = !DIDerivedType(tag: DW_TAG_member, name: "st_blocks", scope: !222, file: !223, line: 80, baseType: !241, size: 64, align: 64, offset: 512)
!241 = !DIDerivedType(tag: DW_TAG_typedef, name: "__blkcnt_t", file: !80, line: 158, baseType: !81)
!242 = !DIDerivedType(tag: DW_TAG_member, name: "st_atim", scope: !222, file: !223, line: 91, baseType: !243, size: 128, align: 64, offset: 576)
!243 = !DICompositeType(tag: DW_TAG_structure_type, name: "timespec", file: !176, line: 120, size: 128, align: 64, elements: !244)
!244 = !{!245, !246}
!245 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !243, file: !176, line: 122, baseType: !177, size: 64, align: 64)
!246 = !DIDerivedType(tag: DW_TAG_member, name: "tv_nsec", scope: !243, file: !176, line: 123, baseType: !247, size: 64, align: 64, offset: 64)
!247 = !DIDerivedType(tag: DW_TAG_typedef, name: "__syscall_slong_t", file: !80, line: 175, baseType: !81)
!248 = !DIDerivedType(tag: DW_TAG_member, name: "st_mtim", scope: !222, file: !223, line: 92, baseType: !243, size: 128, align: 64, offset: 704)
!249 = !DIDerivedType(tag: DW_TAG_member, name: "st_ctim", scope: !222, file: !223, line: 93, baseType: !243, size: 128, align: 64, offset: 832)
!250 = !DIDerivedType(tag: DW_TAG_member, name: "__glibc_reserved", scope: !222, file: !223, line: 106, baseType: !251, size: 192, align: 64, offset: 960)
!251 = !DICompositeType(tag: DW_TAG_array_type, baseType: !247, size: 192, align: 64, elements: !252)
!252 = !{!253}
!253 = !DISubrange(count: 3)
!254 = !DIDerivedType(tag: DW_TAG_member, name: "st", scope: !154, file: !1, line: 227, baseType: !222, size: 1152, align: 64, offset: 2176)
!255 = !DIDerivedType(tag: DW_TAG_member, name: "descend", scope: !154, file: !1, line: 228, baseType: !62, size: 32, align: 32, offset: 3328)
!256 = !DIDerivedType(tag: DW_TAG_member, name: "nlink", scope: !154, file: !1, line: 229, baseType: !62, size: 32, align: 32, offset: 3360)
!257 = !DIDerivedType(tag: DW_TAG_member, name: "restore_time", scope: !154, file: !1, line: 231, baseType: !171, size: 384, align: 64, offset: 3392)
!258 = !DIDerivedType(tag: DW_TAG_member, name: "sparse_list", scope: !154, file: !1, line: 236, baseType: !259, size: 64, align: 64, offset: 3776)
!259 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !260, size: 64, align: 64)
!260 = !DICompositeType(tag: DW_TAG_structure_type, name: "entry_sparse", file: !1, line: 233, size: 128, align: 64, elements: !261)
!261 = !{!262, !263}
!262 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !260, file: !1, line: 234, baseType: !91, size: 64, align: 64)
!263 = !DIDerivedType(tag: DW_TAG_member, name: "offset", scope: !260, file: !1, line: 235, baseType: !91, size: 64, align: 64, offset: 64)
!264 = !DIDerivedType(tag: DW_TAG_member, name: "current_sparse", scope: !154, file: !1, line: 236, baseType: !259, size: 64, align: 64, offset: 3840)
!265 = !DIDerivedType(tag: DW_TAG_member, name: "sparse_count", scope: !154, file: !1, line: 237, baseType: !62, size: 32, align: 32, offset: 3904)
!266 = !DIDerivedType(tag: DW_TAG_member, name: "sparse_list_size", scope: !154, file: !1, line: 238, baseType: !62, size: 32, align: 32, offset: 3936)
!267 = !DIDerivedType(tag: DW_TAG_member, name: "initial_symlink_mode", scope: !154, file: !1, line: 240, baseType: !121, size: 8, align: 8, offset: 3968)
!268 = !DIDerivedType(tag: DW_TAG_member, name: "symlink_mode", scope: !154, file: !1, line: 241, baseType: !121, size: 8, align: 8, offset: 3976)
!269 = !DIDerivedType(tag: DW_TAG_member, name: "current_filesystem", scope: !154, file: !1, line: 242, baseType: !270, size: 64, align: 64, offset: 4032)
!270 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !271, size: 64, align: 64)
!271 = !DICompositeType(tag: DW_TAG_structure_type, name: "filesystem", file: !1, line: 163, size: 704, align: 64, elements: !272)
!272 = !{!273, !274, !275, !276, !277, !278, !279, !280, !281, !282, !284, !285}
!273 = !DIDerivedType(tag: DW_TAG_member, name: "dev", scope: !271, file: !1, line: 164, baseType: !91, size: 64, align: 64)
!274 = !DIDerivedType(tag: DW_TAG_member, name: "synthetic", scope: !271, file: !1, line: 165, baseType: !62, size: 32, align: 32, offset: 64)
!275 = !DIDerivedType(tag: DW_TAG_member, name: "remote", scope: !271, file: !1, line: 166, baseType: !62, size: 32, align: 32, offset: 96)
!276 = !DIDerivedType(tag: DW_TAG_member, name: "noatime", scope: !271, file: !1, line: 167, baseType: !62, size: 32, align: 32, offset: 128)
!277 = !DIDerivedType(tag: DW_TAG_member, name: "name_max", scope: !271, file: !1, line: 169, baseType: !84, size: 64, align: 64, offset: 192)
!278 = !DIDerivedType(tag: DW_TAG_member, name: "incr_xfer_size", scope: !271, file: !1, line: 171, baseType: !81, size: 64, align: 64, offset: 256)
!279 = !DIDerivedType(tag: DW_TAG_member, name: "max_xfer_size", scope: !271, file: !1, line: 172, baseType: !81, size: 64, align: 64, offset: 320)
!280 = !DIDerivedType(tag: DW_TAG_member, name: "min_xfer_size", scope: !271, file: !1, line: 173, baseType: !81, size: 64, align: 64, offset: 384)
!281 = !DIDerivedType(tag: DW_TAG_member, name: "xfer_align", scope: !271, file: !1, line: 174, baseType: !81, size: 64, align: 64, offset: 448)
!282 = !DIDerivedType(tag: DW_TAG_member, name: "allocation_ptr", scope: !271, file: !1, line: 180, baseType: !283, size: 64, align: 64, offset: 512)
!283 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !203, size: 64, align: 64)
!284 = !DIDerivedType(tag: DW_TAG_member, name: "buff", scope: !271, file: !1, line: 182, baseType: !283, size: 64, align: 64, offset: 576)
!285 = !DIDerivedType(tag: DW_TAG_member, name: "buff_size", scope: !271, file: !1, line: 183, baseType: !84, size: 64, align: 64, offset: 640)
!286 = !DIDerivedType(tag: DW_TAG_member, name: "filesystem_table", scope: !154, file: !1, line: 243, baseType: !270, size: 64, align: 64, offset: 4096)
!287 = !DIDerivedType(tag: DW_TAG_member, name: "initial_filesystem_id", scope: !154, file: !1, line: 244, baseType: !62, size: 32, align: 32, offset: 4160)
!288 = !DIDerivedType(tag: DW_TAG_member, name: "current_filesystem_id", scope: !154, file: !1, line: 245, baseType: !62, size: 32, align: 32, offset: 4192)
!289 = !DIDerivedType(tag: DW_TAG_member, name: "max_filesystem_id", scope: !154, file: !1, line: 246, baseType: !62, size: 32, align: 32, offset: 4224)
!290 = !DIDerivedType(tag: DW_TAG_member, name: "allocated_filesystem", scope: !154, file: !1, line: 247, baseType: !62, size: 32, align: 32, offset: 4256)
!291 = !DIDerivedType(tag: DW_TAG_member, name: "entry_fd", scope: !154, file: !1, line: 249, baseType: !62, size: 32, align: 32, offset: 4288)
!292 = !DIDerivedType(tag: DW_TAG_member, name: "entry_eof", scope: !154, file: !1, line: 250, baseType: !62, size: 32, align: 32, offset: 4320)
!293 = !DIDerivedType(tag: DW_TAG_member, name: "entry_remaining_bytes", scope: !154, file: !1, line: 251, baseType: !91, size: 64, align: 64, offset: 4352)
!294 = !DIDerivedType(tag: DW_TAG_member, name: "entry_total", scope: !154, file: !1, line: 252, baseType: !91, size: 64, align: 64, offset: 4416)
!295 = !DIDerivedType(tag: DW_TAG_member, name: "entry_buff", scope: !154, file: !1, line: 253, baseType: !283, size: 64, align: 64, offset: 4480)
!296 = !DIDerivedType(tag: DW_TAG_member, name: "entry_buff_size", scope: !154, file: !1, line: 254, baseType: !84, size: 64, align: 64, offset: 4544)
!297 = !DIDerivedType(tag: DW_TAG_member, name: "open_on_current_dir", scope: !44, file: !45, line: 62, baseType: !298, size: 64, align: 64, offset: 1472)
!298 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !299, size: 64, align: 64)
!299 = !DISubroutineType(types: !300)
!300 = !{!62, !153, !119, !62}
!301 = !DIDerivedType(tag: DW_TAG_member, name: "tree_current_dir_fd", scope: !44, file: !45, line: 63, baseType: !302, size: 64, align: 64, offset: 1536)
!302 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !303, size: 64, align: 64)
!303 = !DISubroutineType(types: !304)
!304 = !{!62, !153}
!305 = !DIDerivedType(tag: DW_TAG_member, name: "tree_enter_working_dir", scope: !44, file: !45, line: 64, baseType: !302, size: 64, align: 64, offset: 1600)
!306 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !44, file: !45, line: 67, baseType: !62, size: 32, align: 32, offset: 1664)
!307 = !DIDerivedType(tag: DW_TAG_member, name: "lookup_gname", scope: !44, file: !45, line: 69, baseType: !308, size: 64, align: 64, offset: 1728)
!308 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !309, size: 64, align: 64)
!309 = !DISubroutineType(types: !310)
!310 = !{!119, !311, !91}
!311 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!312 = !DIDerivedType(tag: DW_TAG_member, name: "cleanup_gname", scope: !44, file: !45, line: 70, baseType: !313, size: 64, align: 64, offset: 1792)
!313 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !314, size: 64, align: 64)
!314 = !DISubroutineType(types: !315)
!315 = !{null, !311}
!316 = !DIDerivedType(tag: DW_TAG_member, name: "lookup_gname_data", scope: !44, file: !45, line: 71, baseType: !311, size: 64, align: 64, offset: 1856)
!317 = !DIDerivedType(tag: DW_TAG_member, name: "lookup_uname", scope: !44, file: !45, line: 72, baseType: !308, size: 64, align: 64, offset: 1920)
!318 = !DIDerivedType(tag: DW_TAG_member, name: "cleanup_uname", scope: !44, file: !45, line: 73, baseType: !313, size: 64, align: 64, offset: 1984)
!319 = !DIDerivedType(tag: DW_TAG_member, name: "lookup_uname_data", scope: !44, file: !45, line: 74, baseType: !311, size: 64, align: 64, offset: 2048)
!320 = !DIDerivedType(tag: DW_TAG_member, name: "metadata_filter_func", scope: !44, file: !45, line: 76, baseType: !321, size: 64, align: 64, offset: 2112)
!321 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !322, size: 64, align: 64)
!322 = !DISubroutineType(types: !323)
!323 = !{!62, !63, !311, !69}
!324 = !DIDerivedType(tag: DW_TAG_member, name: "metadata_filter_data", scope: !44, file: !45, line: 78, baseType: !311, size: 64, align: 64, offset: 2176)
!325 = !DIDerivedType(tag: DW_TAG_member, name: "matching", scope: !44, file: !45, line: 81, baseType: !63, size: 64, align: 64, offset: 2240)
!326 = !DIDerivedType(tag: DW_TAG_member, name: "excluded_cb_func", scope: !44, file: !45, line: 84, baseType: !327, size: 64, align: 64, offset: 2304)
!327 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !328, size: 64, align: 64)
!328 = !DISubroutineType(types: !329)
!329 = !{null, !63, !311, !69}
!330 = !DIDerivedType(tag: DW_TAG_member, name: "excluded_cb_data", scope: !44, file: !45, line: 86, baseType: !311, size: 64, align: 64, offset: 2368)
!331 = !DIDerivedType(tag: DW_TAG_typedef, name: "off_t", file: !78, line: 86, baseType: !199)
!332 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !92, line: 122, baseType: !86)
!333 = !{!334, !338, !339, !342, !343, !346, !347, !348, !349, !350, !351, !354, !357, !358, !359, !362, !368, !369, !370, !371, !374, !375, !378, !379, !380, !384, !385, !386, !389, !390, !391, !394, !395, !396, !399, !400, !401, !404, !407, !408, !409, !414, !415, !418, !421, !422, !423, !426, !429, !432, !433, !434, !435, !438, !441, !442, !445, !446, !447, !448}
!334 = distinct !DISubprogram(name: "archive_read_disk_gname", scope: !1, file: !1, line: 390, type: !335, isLocal: false, isDefinition: true, scopeLine: 391, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!335 = !DISubroutineType(types: !336)
!336 = !{!119, !63, !91}
!337 = !{}
!338 = distinct !DISubprogram(name: "archive_read_disk_uname", scope: !1, file: !1, line: 402, type: !335, isLocal: false, isDefinition: true, scopeLine: 403, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!339 = distinct !DISubprogram(name: "archive_read_disk_set_gname_lookup", scope: !1, file: !1, line: 414, type: !340, isLocal: false, isDefinition: true, scopeLine: 418, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!340 = !DISubroutineType(types: !341)
!341 = !{!62, !63, !311, !308, !313}
!342 = distinct !DISubprogram(name: "archive_read_disk_set_uname_lookup", scope: !1, file: !1, line: 433, type: !340, isLocal: false, isDefinition: true, scopeLine: 437, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!343 = distinct !DISubprogram(name: "archive_read_disk_new", scope: !1, file: !1, line: 455, type: !344, isLocal: false, isDefinition: true, scopeLine: 456, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!344 = !DISubroutineType(types: !345)
!345 = !{!63}
!346 = distinct !DISubprogram(name: "archive_read_disk_set_symlink_logical", scope: !1, file: !1, line: 533, type: !60, isLocal: false, isDefinition: true, scopeLine: 534, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!347 = distinct !DISubprogram(name: "archive_read_disk_set_symlink_physical", scope: !1, file: !1, line: 543, type: !60, isLocal: false, isDefinition: true, scopeLine: 544, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!348 = distinct !DISubprogram(name: "archive_read_disk_set_symlink_hybrid", scope: !1, file: !1, line: 553, type: !60, isLocal: false, isDefinition: true, scopeLine: 554, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!349 = distinct !DISubprogram(name: "archive_read_disk_set_atime_restored", scope: !1, file: !1, line: 563, type: !60, isLocal: false, isDefinition: true, scopeLine: 564, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!350 = distinct !DISubprogram(name: "archive_read_disk_set_behavior", scope: !1, file: !1, line: 583, type: !113, isLocal: false, isDefinition: true, scopeLine: 584, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!351 = distinct !DISubprogram(name: "archive_read_disk_set_matching", scope: !1, file: !1, line: 1211, type: !352, isLocal: false, isDefinition: true, scopeLine: 1214, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!352 = !DISubroutineType(types: !353)
!353 = !{!62, !63, !63, !327, !311}
!354 = distinct !DISubprogram(name: "archive_read_disk_set_metadata_filter_callback", scope: !1, file: !1, line: 1225, type: !355, isLocal: false, isDefinition: true, scopeLine: 1228, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!355 = !DISubroutineType(types: !356)
!356 = !{!62, !63, !321, !311}
!357 = distinct !DISubprogram(name: "archive_read_disk_can_descend", scope: !1, file: !1, line: 1240, type: !60, isLocal: false, isDefinition: true, scopeLine: 1241, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!358 = distinct !DISubprogram(name: "archive_read_disk_descend", scope: !1, file: !1, line: 1257, type: !60, isLocal: false, isDefinition: true, scopeLine: 1258, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!359 = distinct !DISubprogram(name: "archive_read_disk_open", scope: !1, file: !1, line: 1283, type: !360, isLocal: false, isDefinition: true, scopeLine: 1284, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!360 = !DISubroutineType(types: !361)
!361 = !{!62, !63, !119}
!362 = distinct !DISubprogram(name: "archive_read_disk_open_w", scope: !1, file: !1, line: 1296, type: !363, isLocal: false, isDefinition: true, scopeLine: 1297, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!363 = !DISubroutineType(types: !364)
!364 = !{!62, !63, !365}
!365 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !366, size: 64, align: 64)
!366 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !367)
!367 = !DIDerivedType(tag: DW_TAG_typedef, name: "wchar_t", file: !85, line: 90, baseType: !62)
!368 = distinct !DISubprogram(name: "archive_read_disk_current_filesystem", scope: !1, file: !1, line: 1353, type: !60, isLocal: false, isDefinition: true, scopeLine: 1354, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!369 = distinct !DISubprogram(name: "archive_read_disk_current_filesystem_is_synthetic", scope: !1, file: !1, line: 1417, type: !60, isLocal: false, isDefinition: true, scopeLine: 1418, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!370 = distinct !DISubprogram(name: "archive_read_disk_current_filesystem_is_remote", scope: !1, file: !1, line: 1432, type: !60, isLocal: false, isDefinition: true, scopeLine: 1433, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!371 = distinct !DISubprogram(name: "archive_read_disk_vtable", scope: !1, file: !1, line: 373, type: !372, isLocal: true, isDefinition: true, scopeLine: 374, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!372 = !DISubroutineType(types: !373)
!373 = !{!55}
!374 = distinct !DISubprogram(name: "_archive_read_free", scope: !1, file: !1, line: 476, type: !60, isLocal: true, isDefinition: true, scopeLine: 477, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!375 = distinct !DISubprogram(name: "tree_free", scope: !1, file: !1, line: 2644, type: !376, isLocal: true, isDefinition: true, scopeLine: 2645, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!376 = !DISubroutineType(types: !377)
!377 = !{null, !153}
!378 = distinct !DISubprogram(name: "_archive_read_close", scope: !1, file: !1, line: 505, type: !60, isLocal: true, isDefinition: true, scopeLine: 506, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!379 = distinct !DISubprogram(name: "tree_close", scope: !1, file: !1, line: 2610, type: !376, isLocal: true, isDefinition: true, scopeLine: 2611, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!380 = distinct !DISubprogram(name: "close_and_restore_time", scope: !1, file: !1, line: 1958, type: !381, isLocal: true, isDefinition: true, scopeLine: 1959, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!381 = !DISubroutineType(types: !382)
!382 = !{!62, !62, !153, !383}
!383 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !171, size: 64, align: 64)
!384 = distinct !DISubprogram(name: "tree_pop", scope: !1, file: !1, line: 2270, type: !376, isLocal: true, isDefinition: true, scopeLine: 2271, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!385 = distinct !DISubprogram(name: "_archive_read_data_block", scope: !1, file: !1, line: 690, type: !101, isLocal: true, isDefinition: true, scopeLine: 692, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!386 = distinct !DISubprogram(name: "tree_current_access_path", scope: !1, file: !1, line: 2592, type: !387, isLocal: true, isDefinition: true, scopeLine: 2593, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!387 = !DISubroutineType(types: !388)
!388 = !{!119, !153}
!389 = distinct !DISubprogram(name: "tree_current_path", scope: !1, file: !1, line: 2601, type: !387, isLocal: true, isDefinition: true, scopeLine: 2602, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!390 = distinct !DISubprogram(name: "tree_enter_initial_dir", scope: !1, file: !1, line: 2223, type: !303, isLocal: true, isDefinition: true, scopeLine: 2224, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!391 = distinct !DISubprogram(name: "setup_suitable_read_buffer", scope: !1, file: !1, line: 628, type: !392, isLocal: true, isDefinition: true, scopeLine: 629, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!392 = !DISubroutineType(types: !393)
!393 = !{!62, !43}
!394 = distinct !DISubprogram(name: "_archive_read_next_header", scope: !1, file: !1, line: 1090, type: !95, isLocal: true, isDefinition: true, scopeLine: 1091, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!395 = distinct !DISubprogram(name: "_archive_read_next_header2", scope: !1, file: !1, line: 1101, type: !67, isLocal: true, isDefinition: true, scopeLine: 1102, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!396 = distinct !DISubprogram(name: "next_entry", scope: !1, file: !1, line: 853, type: !397, isLocal: true, isDefinition: true, scopeLine: 855, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!397 = !DISubroutineType(types: !398)
!398 = !{!62, !43, !153, !69}
!399 = distinct !DISubprogram(name: "tree_next", scope: !1, file: !1, line: 2292, type: !303, isLocal: true, isDefinition: true, scopeLine: 2293, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!400 = distinct !DISubprogram(name: "tree_dir_next_posix", scope: !1, file: !1, line: 2350, type: !303, isLocal: true, isDefinition: true, scopeLine: 2351, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!401 = distinct !DISubprogram(name: "tree_dup", scope: !1, file: !1, line: 2026, type: !402, isLocal: true, isDefinition: true, scopeLine: 2027, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!402 = !DISubroutineType(types: !403)
!403 = !{!62, !62}
!404 = distinct !DISubprogram(name: "tree_append", scope: !1, file: !1, line: 2085, type: !405, isLocal: true, isDefinition: true, scopeLine: 2086, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!405 = !DISubroutineType(types: !406)
!406 = !{null, !153, !119, !84}
!407 = distinct !DISubprogram(name: "tree_descent", scope: !1, file: !1, line: 2152, type: !303, isLocal: true, isDefinition: true, scopeLine: 2153, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!408 = distinct !DISubprogram(name: "tree_ascend", scope: !1, file: !1, line: 2187, type: !303, isLocal: true, isDefinition: true, scopeLine: 2188, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!409 = distinct !DISubprogram(name: "tree_current_lstat", scope: !1, file: !1, line: 2465, type: !410, isLocal: true, isDefinition: true, scopeLine: 2466, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!410 = !DISubroutineType(types: !411)
!411 = !{!412, !153}
!412 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !413, size: 64, align: 64)
!413 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !222)
!414 = distinct !DISubprogram(name: "tree_current_stat", scope: !1, file: !1, line: 2444, type: !410, isLocal: true, isDefinition: true, scopeLine: 2445, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!415 = distinct !DISubprogram(name: "tree_target_is_same_as_parent", scope: !1, file: !1, line: 2560, type: !416, isLocal: true, isDefinition: true, scopeLine: 2561, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!416 = !DISubroutineType(types: !417)
!417 = !{!62, !153, !412}
!418 = distinct !DISubprogram(name: "update_current_filesystem", scope: !1, file: !1, line: 1364, type: !419, isLocal: true, isDefinition: true, scopeLine: 1365, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!419 = !DISubroutineType(types: !420)
!420 = !{!62, !43, !91}
!421 = distinct !DISubprogram(name: "setup_current_filesystem", scope: !1, file: !1, line: 1695, type: !392, isLocal: true, isDefinition: true, scopeLine: 1696, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!422 = distinct !DISubprogram(name: "tree_current_is_symblic_link_target", scope: !1, file: !1, line: 2577, type: !303, isLocal: true, isDefinition: true, scopeLine: 2578, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!423 = distinct !DISubprogram(name: "get_xfer_size", scope: !1, file: !1, line: 1445, type: !424, isLocal: true, isDefinition: true, scopeLine: 1446, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!424 = !DISubroutineType(types: !425)
!425 = !{!62, !153, !62, !119}
!426 = distinct !DISubprogram(name: "setup_sparse", scope: !1, file: !1, line: 1173, type: !427, isLocal: true, isDefinition: true, scopeLine: 1174, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!427 = !DISubroutineType(types: !428)
!428 = !{!62, !43, !69}
!429 = distinct !DISubprogram(name: "setup_symlink_mode", scope: !1, file: !1, line: 521, type: !430, isLocal: true, isDefinition: true, scopeLine: 523, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!430 = !DISubroutineType(types: !431)
!431 = !{null, !43, !121, !62}
!432 = distinct !DISubprogram(name: "trivial_lookup_gname", scope: !1, file: !1, line: 608, type: !309, isLocal: true, isDefinition: true, scopeLine: 609, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!433 = distinct !DISubprogram(name: "trivial_lookup_uname", scope: !1, file: !1, line: 616, type: !309, isLocal: true, isDefinition: true, scopeLine: 617, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!434 = distinct !DISubprogram(name: "_archive_read_disk_open", scope: !1, file: !1, line: 1327, type: !360, isLocal: true, isDefinition: true, scopeLine: 1328, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!435 = distinct !DISubprogram(name: "tree_reopen", scope: !1, file: !1, line: 2123, type: !436, isLocal: true, isDefinition: true, scopeLine: 2124, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!436 = !DISubroutineType(types: !437)
!437 = !{!153, !153, !119, !62}
!438 = distinct !DISubprogram(name: "tree_open", scope: !1, file: !1, line: 2110, type: !439, isLocal: true, isDefinition: true, scopeLine: 2111, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!439 = !DISubroutineType(types: !440)
!440 = !{!153, !119, !62, !62}
!441 = distinct !DISubprogram(name: "open_on_current_dir", scope: !1, file: !1, line: 2014, type: !299, isLocal: true, isDefinition: true, scopeLine: 2015, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!442 = distinct !DISubprogram(name: "tree_push", scope: !1, file: !1, line: 2051, type: !443, isLocal: true, isDefinition: true, scopeLine: 2053, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!443 = !DISubroutineType(types: !444)
!444 = !{null, !153, !119, !62, !91, !91, !383}
!445 = distinct !DISubprogram(name: "tree_enter_working_dir", scope: !1, file: !1, line: 2241, type: !303, isLocal: true, isDefinition: true, scopeLine: 2242, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!446 = distinct !DISubprogram(name: "tree_current_dir_fd", scope: !1, file: !1, line: 2261, type: !303, isLocal: true, isDefinition: true, scopeLine: 2262, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!447 = distinct !DISubprogram(name: "tree_current_is_dir", scope: !1, file: !1, line: 2487, type: !303, isLocal: true, isDefinition: true, scopeLine: 2488, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!448 = distinct !DISubprogram(name: "tree_current_is_physical_dir", scope: !1, file: !1, line: 2525, type: !303, isLocal: true, isDefinition: true, scopeLine: 2526, flags: DIFlagPrototyped, isOptimized: false, variables: !337)
!449 = !{!450, !451, !452, !454, !455}
!450 = !DIGlobalVariable(name: "av", scope: !371, file: !1, line: 375, type: !56, isLocal: true, isDefinition: true, variable: %struct.archive_vtable* @archive_read_disk_vtable.av)
!451 = !DIGlobalVariable(name: "inited", scope: !371, file: !1, line: 376, type: !62, isLocal: true, isDefinition: true, variable: i32* @archive_read_disk_vtable.inited)
!452 = !DIGlobalVariable(name: "can_dupfd_cloexec", scope: !401, file: !1, line: 2030, type: !453, isLocal: true, isDefinition: true, variable: i32* @tree_dup.can_dupfd_cloexec)
!453 = !DIDerivedType(tag: DW_TAG_volatile_type, baseType: !62)
!454 = !DIGlobalVariable(name: "lst", scope: !422, file: !1, line: 2579, type: !412, isLocal: true, isDefinition: true, variable: %struct.stat** @tree_current_is_symblic_link_target.lst)
!455 = !DIGlobalVariable(name: "st", scope: !422, file: !1, line: 2579, type: !412, isLocal: true, isDefinition: true, variable: %struct.stat** @tree_current_is_symblic_link_target.st)
!456 = !{i32 2, !"Dwarf Version", i32 4}
!457 = !{i32 2, !"Debug Info Version", i32 3}
!458 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!459 = !DILocalVariable(name: "_a", arg: 1, scope: !334, file: !1, line: 390, type: !63)
!460 = !DIExpression()
!461 = !DILocation(line: 390, column: 41, scope: !334)
!462 = !DILocalVariable(name: "gid", arg: 2, scope: !334, file: !1, line: 390, type: !91)
!463 = !DILocation(line: 390, column: 53, scope: !334)
!464 = !DILocalVariable(name: "a", scope: !334, file: !1, line: 392, type: !43)
!465 = !DILocation(line: 392, column: 28, scope: !334)
!466 = !DILocation(line: 392, column: 60, scope: !334)
!467 = !DILocation(line: 392, column: 32, scope: !334)
!468 = !DILocation(line: 393, column: 42, scope: !469)
!469 = distinct !DILexicalBlock(scope: !334, file: !1, line: 393, column: 6)
!470 = !DILocation(line: 393, column: 20, scope: !469)
!471 = !DILocation(line: 393, column: 17, scope: !469)
!472 = !DILocation(line: 393, column: 6, scope: !334)
!473 = !DILocation(line: 395, column: 3, scope: !469)
!474 = !DILocation(line: 396, column: 6, scope: !475)
!475 = distinct !DILexicalBlock(scope: !334, file: !1, line: 396, column: 6)
!476 = !DILocation(line: 396, column: 9, scope: !475)
!477 = !DILocation(line: 396, column: 22, scope: !475)
!478 = !DILocation(line: 396, column: 6, scope: !334)
!479 = !DILocation(line: 397, column: 3, scope: !475)
!480 = !DILocation(line: 398, column: 12, scope: !334)
!481 = !DILocation(line: 398, column: 15, scope: !334)
!482 = !DILocation(line: 398, column: 29, scope: !334)
!483 = !DILocation(line: 398, column: 32, scope: !334)
!484 = !DILocation(line: 398, column: 51, scope: !334)
!485 = !DILocation(line: 398, column: 10, scope: !334)
!486 = !DILocation(line: 398, column: 2, scope: !334)
!487 = !DILocation(line: 399, column: 1, scope: !334)
!488 = !DILocalVariable(name: "_a", arg: 1, scope: !338, file: !1, line: 402, type: !63)
!489 = !DILocation(line: 402, column: 41, scope: !338)
!490 = !DILocalVariable(name: "uid", arg: 2, scope: !338, file: !1, line: 402, type: !91)
!491 = !DILocation(line: 402, column: 53, scope: !338)
!492 = !DILocalVariable(name: "a", scope: !338, file: !1, line: 404, type: !43)
!493 = !DILocation(line: 404, column: 28, scope: !338)
!494 = !DILocation(line: 404, column: 60, scope: !338)
!495 = !DILocation(line: 404, column: 32, scope: !338)
!496 = !DILocation(line: 405, column: 42, scope: !497)
!497 = distinct !DILexicalBlock(scope: !338, file: !1, line: 405, column: 6)
!498 = !DILocation(line: 405, column: 20, scope: !497)
!499 = !DILocation(line: 405, column: 17, scope: !497)
!500 = !DILocation(line: 405, column: 6, scope: !338)
!501 = !DILocation(line: 407, column: 3, scope: !497)
!502 = !DILocation(line: 408, column: 6, scope: !503)
!503 = distinct !DILexicalBlock(scope: !338, file: !1, line: 408, column: 6)
!504 = !DILocation(line: 408, column: 9, scope: !503)
!505 = !DILocation(line: 408, column: 22, scope: !503)
!506 = !DILocation(line: 408, column: 6, scope: !338)
!507 = !DILocation(line: 409, column: 3, scope: !503)
!508 = !DILocation(line: 410, column: 12, scope: !338)
!509 = !DILocation(line: 410, column: 15, scope: !338)
!510 = !DILocation(line: 410, column: 29, scope: !338)
!511 = !DILocation(line: 410, column: 32, scope: !338)
!512 = !DILocation(line: 410, column: 51, scope: !338)
!513 = !DILocation(line: 410, column: 10, scope: !338)
!514 = !DILocation(line: 410, column: 2, scope: !338)
!515 = !DILocation(line: 411, column: 1, scope: !338)
!516 = !DILocalVariable(name: "_a", arg: 1, scope: !339, file: !1, line: 414, type: !63)
!517 = !DILocation(line: 414, column: 52, scope: !339)
!518 = !DILocalVariable(name: "private_data", arg: 2, scope: !339, file: !1, line: 415, type: !311)
!519 = !DILocation(line: 415, column: 11, scope: !339)
!520 = !DILocalVariable(name: "lookup_gname", arg: 3, scope: !339, file: !1, line: 416, type: !308)
!521 = !DILocation(line: 416, column: 20, scope: !339)
!522 = !DILocalVariable(name: "cleanup_gname", arg: 4, scope: !339, file: !1, line: 417, type: !313)
!523 = !DILocation(line: 417, column: 12, scope: !339)
!524 = !DILocalVariable(name: "a", scope: !339, file: !1, line: 419, type: !43)
!525 = !DILocation(line: 419, column: 28, scope: !339)
!526 = !DILocation(line: 419, column: 60, scope: !339)
!527 = !DILocation(line: 419, column: 32, scope: !339)
!528 = !DILocation(line: 420, column: 2, scope: !339)
!529 = !DILocalVariable(name: "magic_test", scope: !530, file: !1, line: 420, type: !62)
!530 = distinct !DILexicalBlock(scope: !339, file: !1, line: 420, column: 2)
!531 = !DILocation(line: 420, column: 2, scope: !530)
!532 = !DILocation(line: 420, column: 2, scope: !533)
!533 = !DILexicalBlockFile(scope: !530, file: !1, discriminator: 1)
!534 = !DILocation(line: 420, column: 2, scope: !535)
!535 = !DILexicalBlockFile(scope: !536, file: !1, discriminator: 2)
!536 = distinct !DILexicalBlock(scope: !530, file: !1, line: 420, column: 2)
!537 = !DILocation(line: 420, column: 2, scope: !538)
!538 = !DILexicalBlockFile(scope: !530, file: !1, discriminator: 3)
!539 = !DILocation(line: 423, column: 6, scope: !540)
!540 = distinct !DILexicalBlock(scope: !339, file: !1, line: 423, column: 6)
!541 = !DILocation(line: 423, column: 9, scope: !540)
!542 = !DILocation(line: 423, column: 23, scope: !540)
!543 = !DILocation(line: 423, column: 31, scope: !540)
!544 = !DILocation(line: 423, column: 34, scope: !545)
!545 = !DILexicalBlockFile(scope: !540, file: !1, discriminator: 1)
!546 = !DILocation(line: 423, column: 37, scope: !545)
!547 = !DILocation(line: 423, column: 55, scope: !545)
!548 = !DILocation(line: 423, column: 6, scope: !545)
!549 = !DILocation(line: 424, column: 4, scope: !540)
!550 = !DILocation(line: 424, column: 7, scope: !540)
!551 = !DILocation(line: 424, column: 22, scope: !540)
!552 = !DILocation(line: 424, column: 25, scope: !540)
!553 = !DILocation(line: 424, column: 3, scope: !540)
!554 = !DILocation(line: 426, column: 20, scope: !339)
!555 = !DILocation(line: 426, column: 2, scope: !339)
!556 = !DILocation(line: 426, column: 5, scope: !339)
!557 = !DILocation(line: 426, column: 18, scope: !339)
!558 = !DILocation(line: 427, column: 21, scope: !339)
!559 = !DILocation(line: 427, column: 2, scope: !339)
!560 = !DILocation(line: 427, column: 5, scope: !339)
!561 = !DILocation(line: 427, column: 19, scope: !339)
!562 = !DILocation(line: 428, column: 25, scope: !339)
!563 = !DILocation(line: 428, column: 2, scope: !339)
!564 = !DILocation(line: 428, column: 5, scope: !339)
!565 = !DILocation(line: 428, column: 23, scope: !339)
!566 = !DILocation(line: 429, column: 2, scope: !339)
!567 = !DILocation(line: 430, column: 1, scope: !339)
!568 = !DILocalVariable(name: "_a", arg: 1, scope: !342, file: !1, line: 433, type: !63)
!569 = !DILocation(line: 433, column: 52, scope: !342)
!570 = !DILocalVariable(name: "private_data", arg: 2, scope: !342, file: !1, line: 434, type: !311)
!571 = !DILocation(line: 434, column: 11, scope: !342)
!572 = !DILocalVariable(name: "lookup_uname", arg: 3, scope: !342, file: !1, line: 435, type: !308)
!573 = !DILocation(line: 435, column: 20, scope: !342)
!574 = !DILocalVariable(name: "cleanup_uname", arg: 4, scope: !342, file: !1, line: 436, type: !313)
!575 = !DILocation(line: 436, column: 12, scope: !342)
!576 = !DILocalVariable(name: "a", scope: !342, file: !1, line: 438, type: !43)
!577 = !DILocation(line: 438, column: 28, scope: !342)
!578 = !DILocation(line: 438, column: 60, scope: !342)
!579 = !DILocation(line: 438, column: 32, scope: !342)
!580 = !DILocation(line: 439, column: 2, scope: !342)
!581 = !DILocalVariable(name: "magic_test", scope: !582, file: !1, line: 439, type: !62)
!582 = distinct !DILexicalBlock(scope: !342, file: !1, line: 439, column: 2)
!583 = !DILocation(line: 439, column: 2, scope: !582)
!584 = !DILocation(line: 439, column: 2, scope: !585)
!585 = !DILexicalBlockFile(scope: !582, file: !1, discriminator: 1)
!586 = !DILocation(line: 439, column: 2, scope: !587)
!587 = !DILexicalBlockFile(scope: !588, file: !1, discriminator: 2)
!588 = distinct !DILexicalBlock(scope: !582, file: !1, line: 439, column: 2)
!589 = !DILocation(line: 439, column: 2, scope: !590)
!590 = !DILexicalBlockFile(scope: !582, file: !1, discriminator: 3)
!591 = !DILocation(line: 442, column: 6, scope: !592)
!592 = distinct !DILexicalBlock(scope: !342, file: !1, line: 442, column: 6)
!593 = !DILocation(line: 442, column: 9, scope: !592)
!594 = !DILocation(line: 442, column: 23, scope: !592)
!595 = !DILocation(line: 442, column: 31, scope: !592)
!596 = !DILocation(line: 442, column: 34, scope: !597)
!597 = !DILexicalBlockFile(scope: !592, file: !1, discriminator: 1)
!598 = !DILocation(line: 442, column: 37, scope: !597)
!599 = !DILocation(line: 442, column: 55, scope: !597)
!600 = !DILocation(line: 442, column: 6, scope: !597)
!601 = !DILocation(line: 443, column: 4, scope: !592)
!602 = !DILocation(line: 443, column: 7, scope: !592)
!603 = !DILocation(line: 443, column: 22, scope: !592)
!604 = !DILocation(line: 443, column: 25, scope: !592)
!605 = !DILocation(line: 443, column: 3, scope: !592)
!606 = !DILocation(line: 445, column: 20, scope: !342)
!607 = !DILocation(line: 445, column: 2, scope: !342)
!608 = !DILocation(line: 445, column: 5, scope: !342)
!609 = !DILocation(line: 445, column: 18, scope: !342)
!610 = !DILocation(line: 446, column: 21, scope: !342)
!611 = !DILocation(line: 446, column: 2, scope: !342)
!612 = !DILocation(line: 446, column: 5, scope: !342)
!613 = !DILocation(line: 446, column: 19, scope: !342)
!614 = !DILocation(line: 447, column: 25, scope: !342)
!615 = !DILocation(line: 447, column: 2, scope: !342)
!616 = !DILocation(line: 447, column: 5, scope: !342)
!617 = !DILocation(line: 447, column: 23, scope: !342)
!618 = !DILocation(line: 448, column: 2, scope: !342)
!619 = !DILocation(line: 449, column: 1, scope: !342)
!620 = !DILocalVariable(name: "a", scope: !343, file: !1, line: 457, type: !43)
!621 = !DILocation(line: 457, column: 28, scope: !343)
!622 = !DILocation(line: 459, column: 34, scope: !343)
!623 = !DILocation(line: 459, column: 6, scope: !343)
!624 = !DILocation(line: 459, column: 4, scope: !343)
!625 = !DILocation(line: 460, column: 6, scope: !626)
!626 = distinct !DILexicalBlock(scope: !343, file: !1, line: 460, column: 6)
!627 = !DILocation(line: 460, column: 8, scope: !626)
!628 = !DILocation(line: 460, column: 6, scope: !343)
!629 = !DILocation(line: 461, column: 3, scope: !626)
!630 = !DILocation(line: 462, column: 2, scope: !343)
!631 = !DILocation(line: 462, column: 5, scope: !343)
!632 = !DILocation(line: 462, column: 13, scope: !343)
!633 = !DILocation(line: 462, column: 19, scope: !343)
!634 = !DILocation(line: 463, column: 2, scope: !343)
!635 = !DILocation(line: 463, column: 5, scope: !343)
!636 = !DILocation(line: 463, column: 13, scope: !343)
!637 = !DILocation(line: 463, column: 19, scope: !343)
!638 = !DILocation(line: 464, column: 22, scope: !343)
!639 = !DILocation(line: 464, column: 2, scope: !343)
!640 = !DILocation(line: 464, column: 5, scope: !343)
!641 = !DILocation(line: 464, column: 13, scope: !343)
!642 = !DILocation(line: 464, column: 20, scope: !343)
!643 = !DILocation(line: 465, column: 33, scope: !343)
!644 = !DILocation(line: 465, column: 36, scope: !343)
!645 = !DILocation(line: 465, column: 13, scope: !343)
!646 = !DILocation(line: 465, column: 2, scope: !343)
!647 = !DILocation(line: 465, column: 5, scope: !343)
!648 = !DILocation(line: 465, column: 11, scope: !343)
!649 = !DILocation(line: 466, column: 2, scope: !343)
!650 = !DILocation(line: 466, column: 5, scope: !343)
!651 = !DILocation(line: 466, column: 18, scope: !343)
!652 = !DILocation(line: 467, column: 2, scope: !343)
!653 = !DILocation(line: 467, column: 5, scope: !343)
!654 = !DILocation(line: 467, column: 18, scope: !343)
!655 = !DILocation(line: 468, column: 2, scope: !343)
!656 = !DILocation(line: 468, column: 5, scope: !343)
!657 = !DILocation(line: 468, column: 11, scope: !343)
!658 = !DILocation(line: 469, column: 2, scope: !343)
!659 = !DILocation(line: 469, column: 5, scope: !343)
!660 = !DILocation(line: 469, column: 25, scope: !343)
!661 = !DILocation(line: 470, column: 2, scope: !343)
!662 = !DILocation(line: 470, column: 5, scope: !343)
!663 = !DILocation(line: 470, column: 25, scope: !343)
!664 = !DILocation(line: 471, column: 2, scope: !343)
!665 = !DILocation(line: 471, column: 5, scope: !343)
!666 = !DILocation(line: 471, column: 28, scope: !343)
!667 = !DILocation(line: 472, column: 11, scope: !343)
!668 = !DILocation(line: 472, column: 14, scope: !343)
!669 = !DILocation(line: 472, column: 2, scope: !343)
!670 = !DILocation(line: 473, column: 1, scope: !343)
!671 = !DILocation(line: 378, column: 7, scope: !672)
!672 = distinct !DILexicalBlock(scope: !371, file: !1, line: 378, column: 6)
!673 = !DILocation(line: 378, column: 6, scope: !371)
!674 = !DILocation(line: 379, column: 19, scope: !675)
!675 = distinct !DILexicalBlock(scope: !672, file: !1, line: 378, column: 15)
!676 = !DILocation(line: 380, column: 20, scope: !675)
!677 = !DILocation(line: 381, column: 30, scope: !675)
!678 = !DILocation(line: 382, column: 31, scope: !675)
!679 = !DILocation(line: 383, column: 32, scope: !675)
!680 = !DILocation(line: 384, column: 10, scope: !675)
!681 = !DILocation(line: 385, column: 2, scope: !675)
!682 = !DILocation(line: 386, column: 2, scope: !371)
!683 = !DILocalVariable(name: "private_data", arg: 1, scope: !433, file: !1, line: 616, type: !311)
!684 = !DILocation(line: 616, column: 28, scope: !433)
!685 = !DILocalVariable(name: "uid", arg: 2, scope: !433, file: !1, line: 616, type: !91)
!686 = !DILocation(line: 616, column: 50, scope: !433)
!687 = !DILocation(line: 618, column: 8, scope: !433)
!688 = !DILocation(line: 619, column: 8, scope: !433)
!689 = !DILocation(line: 620, column: 2, scope: !433)
!690 = !DILocalVariable(name: "private_data", arg: 1, scope: !432, file: !1, line: 608, type: !311)
!691 = !DILocation(line: 608, column: 28, scope: !432)
!692 = !DILocalVariable(name: "gid", arg: 2, scope: !432, file: !1, line: 608, type: !91)
!693 = !DILocation(line: 608, column: 50, scope: !432)
!694 = !DILocation(line: 610, column: 8, scope: !432)
!695 = !DILocation(line: 611, column: 8, scope: !432)
!696 = !DILocation(line: 612, column: 2, scope: !432)
!697 = !DILocalVariable(name: "t", arg: 1, scope: !441, file: !1, line: 2014, type: !153)
!698 = !DILocation(line: 2014, column: 34, scope: !441)
!699 = !DILocalVariable(name: "path", arg: 2, scope: !441, file: !1, line: 2014, type: !119)
!700 = !DILocation(line: 2014, column: 49, scope: !441)
!701 = !DILocalVariable(name: "flags", arg: 3, scope: !441, file: !1, line: 2014, type: !62)
!702 = !DILocation(line: 2014, column: 59, scope: !441)
!703 = !DILocation(line: 2017, column: 37, scope: !441)
!704 = !DILocation(line: 2017, column: 17, scope: !441)
!705 = !DILocation(line: 2017, column: 41, scope: !441)
!706 = !DILocation(line: 2017, column: 47, scope: !441)
!707 = !DILocation(line: 2017, column: 10, scope: !708)
!708 = !DILexicalBlockFile(scope: !441, file: !1, discriminator: 1)
!709 = !DILocation(line: 2017, column: 2, scope: !441)
!710 = !DILocalVariable(name: "t", arg: 1, scope: !446, file: !1, line: 2261, type: !153)
!711 = !DILocation(line: 2261, column: 34, scope: !446)
!712 = !DILocation(line: 2263, column: 10, scope: !446)
!713 = !DILocation(line: 2263, column: 13, scope: !446)
!714 = !DILocation(line: 2263, column: 2, scope: !446)
!715 = !DILocalVariable(name: "t", arg: 1, scope: !445, file: !1, line: 2241, type: !153)
!716 = !DILocation(line: 2241, column: 37, scope: !445)
!717 = !DILocalVariable(name: "r", scope: !445, file: !1, line: 2243, type: !62)
!718 = !DILocation(line: 2243, column: 6, scope: !445)
!719 = !DILocation(line: 2250, column: 6, scope: !720)
!720 = distinct !DILexicalBlock(scope: !445, file: !1, line: 2250, column: 6)
!721 = !DILocation(line: 2250, column: 9, scope: !720)
!722 = !DILocation(line: 2250, column: 15, scope: !720)
!723 = !DILocation(line: 2250, column: 19, scope: !720)
!724 = !DILocation(line: 2250, column: 23, scope: !725)
!725 = !DILexicalBlockFile(scope: !720, file: !1, discriminator: 1)
!726 = !DILocation(line: 2250, column: 26, scope: !725)
!727 = !DILocation(line: 2250, column: 32, scope: !725)
!728 = !DILocation(line: 2250, column: 48, scope: !725)
!729 = !DILocation(line: 2250, column: 6, scope: !725)
!730 = !DILocation(line: 2251, column: 14, scope: !731)
!731 = distinct !DILexicalBlock(scope: !720, file: !1, line: 2250, column: 54)
!732 = !DILocation(line: 2251, column: 17, scope: !731)
!733 = !DILocation(line: 2251, column: 7, scope: !731)
!734 = !DILocation(line: 2251, column: 5, scope: !731)
!735 = !DILocation(line: 2252, column: 7, scope: !736)
!736 = distinct !DILexicalBlock(scope: !731, file: !1, line: 2252, column: 7)
!737 = !DILocation(line: 2252, column: 9, scope: !736)
!738 = !DILocation(line: 2252, column: 7, scope: !731)
!739 = !DILocation(line: 2253, column: 4, scope: !740)
!740 = distinct !DILexicalBlock(scope: !736, file: !1, line: 2252, column: 15)
!741 = !DILocation(line: 2253, column: 7, scope: !740)
!742 = !DILocation(line: 2253, column: 13, scope: !740)
!743 = !DILocation(line: 2254, column: 4, scope: !740)
!744 = !DILocation(line: 2254, column: 7, scope: !740)
!745 = !DILocation(line: 2254, column: 13, scope: !740)
!746 = !DILocation(line: 2255, column: 3, scope: !740)
!747 = !DILocation(line: 2256, column: 2, scope: !731)
!748 = !DILocation(line: 2257, column: 10, scope: !445)
!749 = !DILocation(line: 2257, column: 2, scope: !445)
!750 = !DILocalVariable(name: "_a", arg: 1, scope: !346, file: !1, line: 533, type: !63)
!751 = !DILocation(line: 533, column: 55, scope: !346)
!752 = !DILocalVariable(name: "a", scope: !346, file: !1, line: 535, type: !43)
!753 = !DILocation(line: 535, column: 28, scope: !346)
!754 = !DILocation(line: 535, column: 60, scope: !346)
!755 = !DILocation(line: 535, column: 32, scope: !346)
!756 = !DILocation(line: 536, column: 2, scope: !346)
!757 = !DILocalVariable(name: "magic_test", scope: !758, file: !1, line: 536, type: !62)
!758 = distinct !DILexicalBlock(scope: !346, file: !1, line: 536, column: 2)
!759 = !DILocation(line: 536, column: 2, scope: !758)
!760 = !DILocation(line: 536, column: 2, scope: !761)
!761 = !DILexicalBlockFile(scope: !758, file: !1, discriminator: 1)
!762 = !DILocation(line: 536, column: 2, scope: !763)
!763 = !DILexicalBlockFile(scope: !764, file: !1, discriminator: 2)
!764 = distinct !DILexicalBlock(scope: !758, file: !1, line: 536, column: 2)
!765 = !DILocation(line: 536, column: 2, scope: !766)
!766 = !DILexicalBlockFile(scope: !758, file: !1, discriminator: 3)
!767 = !DILocation(line: 538, column: 21, scope: !346)
!768 = !DILocation(line: 538, column: 2, scope: !346)
!769 = !DILocation(line: 539, column: 2, scope: !346)
!770 = !DILocation(line: 540, column: 1, scope: !346)
!771 = !DILocalVariable(name: "a", arg: 1, scope: !429, file: !1, line: 521, type: !43)
!772 = !DILocation(line: 521, column: 46, scope: !429)
!773 = !DILocalVariable(name: "symlink_mode", arg: 2, scope: !429, file: !1, line: 521, type: !121)
!774 = !DILocation(line: 521, column: 54, scope: !429)
!775 = !DILocalVariable(name: "follow_symlinks", arg: 3, scope: !429, file: !1, line: 522, type: !62)
!776 = !DILocation(line: 522, column: 9, scope: !429)
!777 = !DILocation(line: 524, column: 20, scope: !429)
!778 = !DILocation(line: 524, column: 2, scope: !429)
!779 = !DILocation(line: 524, column: 5, scope: !429)
!780 = !DILocation(line: 524, column: 18, scope: !429)
!781 = !DILocation(line: 525, column: 23, scope: !429)
!782 = !DILocation(line: 525, column: 2, scope: !429)
!783 = !DILocation(line: 525, column: 5, scope: !429)
!784 = !DILocation(line: 525, column: 21, scope: !429)
!785 = !DILocation(line: 526, column: 6, scope: !786)
!786 = distinct !DILexicalBlock(scope: !429, file: !1, line: 526, column: 6)
!787 = !DILocation(line: 526, column: 9, scope: !786)
!788 = !DILocation(line: 526, column: 14, scope: !786)
!789 = !DILocation(line: 526, column: 6, scope: !429)
!790 = !DILocation(line: 527, column: 35, scope: !791)
!791 = distinct !DILexicalBlock(scope: !786, file: !1, line: 526, column: 23)
!792 = !DILocation(line: 527, column: 38, scope: !791)
!793 = !DILocation(line: 527, column: 3, scope: !791)
!794 = !DILocation(line: 527, column: 6, scope: !791)
!795 = !DILocation(line: 527, column: 12, scope: !791)
!796 = !DILocation(line: 527, column: 33, scope: !791)
!797 = !DILocation(line: 528, column: 27, scope: !791)
!798 = !DILocation(line: 528, column: 30, scope: !791)
!799 = !DILocation(line: 528, column: 3, scope: !791)
!800 = !DILocation(line: 528, column: 6, scope: !791)
!801 = !DILocation(line: 528, column: 12, scope: !791)
!802 = !DILocation(line: 528, column: 25, scope: !791)
!803 = !DILocation(line: 529, column: 2, scope: !791)
!804 = !DILocation(line: 530, column: 1, scope: !429)
!805 = !DILocalVariable(name: "_a", arg: 1, scope: !347, file: !1, line: 543, type: !63)
!806 = !DILocation(line: 543, column: 56, scope: !347)
!807 = !DILocalVariable(name: "a", scope: !347, file: !1, line: 545, type: !43)
!808 = !DILocation(line: 545, column: 28, scope: !347)
!809 = !DILocation(line: 545, column: 60, scope: !347)
!810 = !DILocation(line: 545, column: 32, scope: !347)
!811 = !DILocation(line: 546, column: 2, scope: !347)
!812 = !DILocalVariable(name: "magic_test", scope: !813, file: !1, line: 546, type: !62)
!813 = distinct !DILexicalBlock(scope: !347, file: !1, line: 546, column: 2)
!814 = !DILocation(line: 546, column: 2, scope: !813)
!815 = !DILocation(line: 546, column: 2, scope: !816)
!816 = !DILexicalBlockFile(scope: !813, file: !1, discriminator: 1)
!817 = !DILocation(line: 546, column: 2, scope: !818)
!818 = !DILexicalBlockFile(scope: !819, file: !1, discriminator: 2)
!819 = distinct !DILexicalBlock(scope: !813, file: !1, line: 546, column: 2)
!820 = !DILocation(line: 546, column: 2, scope: !821)
!821 = !DILexicalBlockFile(scope: !813, file: !1, discriminator: 3)
!822 = !DILocation(line: 548, column: 21, scope: !347)
!823 = !DILocation(line: 548, column: 2, scope: !347)
!824 = !DILocation(line: 549, column: 2, scope: !347)
!825 = !DILocation(line: 550, column: 1, scope: !347)
!826 = !DILocalVariable(name: "_a", arg: 1, scope: !348, file: !1, line: 553, type: !63)
!827 = !DILocation(line: 553, column: 54, scope: !348)
!828 = !DILocalVariable(name: "a", scope: !348, file: !1, line: 555, type: !43)
!829 = !DILocation(line: 555, column: 28, scope: !348)
!830 = !DILocation(line: 555, column: 60, scope: !348)
!831 = !DILocation(line: 555, column: 32, scope: !348)
!832 = !DILocation(line: 556, column: 2, scope: !348)
!833 = !DILocalVariable(name: "magic_test", scope: !834, file: !1, line: 556, type: !62)
!834 = distinct !DILexicalBlock(scope: !348, file: !1, line: 556, column: 2)
!835 = !DILocation(line: 556, column: 2, scope: !834)
!836 = !DILocation(line: 556, column: 2, scope: !837)
!837 = !DILexicalBlockFile(scope: !834, file: !1, discriminator: 1)
!838 = !DILocation(line: 556, column: 2, scope: !839)
!839 = !DILexicalBlockFile(scope: !840, file: !1, discriminator: 2)
!840 = distinct !DILexicalBlock(scope: !834, file: !1, line: 556, column: 2)
!841 = !DILocation(line: 556, column: 2, scope: !842)
!842 = !DILexicalBlockFile(scope: !834, file: !1, discriminator: 3)
!843 = !DILocation(line: 558, column: 21, scope: !348)
!844 = !DILocation(line: 558, column: 2, scope: !348)
!845 = !DILocation(line: 559, column: 2, scope: !348)
!846 = !DILocation(line: 560, column: 1, scope: !348)
!847 = !DILocalVariable(name: "_a", arg: 1, scope: !349, file: !1, line: 563, type: !63)
!848 = !DILocation(line: 563, column: 54, scope: !349)
!849 = !DILocalVariable(name: "a", scope: !349, file: !1, line: 565, type: !43)
!850 = !DILocation(line: 565, column: 28, scope: !349)
!851 = !DILocation(line: 565, column: 60, scope: !349)
!852 = !DILocation(line: 565, column: 32, scope: !349)
!853 = !DILocation(line: 566, column: 2, scope: !349)
!854 = !DILocalVariable(name: "magic_test", scope: !855, file: !1, line: 566, type: !62)
!855 = distinct !DILexicalBlock(scope: !349, file: !1, line: 566, column: 2)
!856 = !DILocation(line: 566, column: 2, scope: !855)
!857 = !DILocation(line: 566, column: 2, scope: !858)
!858 = !DILexicalBlockFile(scope: !855, file: !1, discriminator: 1)
!859 = !DILocation(line: 566, column: 2, scope: !860)
!860 = !DILexicalBlockFile(scope: !861, file: !1, discriminator: 2)
!861 = distinct !DILexicalBlock(scope: !855, file: !1, line: 566, column: 2)
!862 = !DILocation(line: 566, column: 2, scope: !863)
!863 = !DILexicalBlockFile(scope: !855, file: !1, discriminator: 3)
!864 = !DILocation(line: 569, column: 2, scope: !349)
!865 = !DILocation(line: 569, column: 5, scope: !349)
!866 = !DILocation(line: 569, column: 11, scope: !349)
!867 = !DILocation(line: 570, column: 6, scope: !868)
!868 = distinct !DILexicalBlock(scope: !349, file: !1, line: 570, column: 6)
!869 = !DILocation(line: 570, column: 9, scope: !868)
!870 = !DILocation(line: 570, column: 14, scope: !868)
!871 = !DILocation(line: 570, column: 6, scope: !349)
!872 = !DILocation(line: 571, column: 3, scope: !868)
!873 = !DILocation(line: 571, column: 6, scope: !868)
!874 = !DILocation(line: 571, column: 12, scope: !868)
!875 = !DILocation(line: 571, column: 18, scope: !868)
!876 = !DILocation(line: 572, column: 2, scope: !349)
!877 = !DILocation(line: 580, column: 1, scope: !349)
!878 = !DILocalVariable(name: "_a", arg: 1, scope: !350, file: !1, line: 583, type: !63)
!879 = !DILocation(line: 583, column: 48, scope: !350)
!880 = !DILocalVariable(name: "flags", arg: 2, scope: !350, file: !1, line: 583, type: !62)
!881 = !DILocation(line: 583, column: 56, scope: !350)
!882 = !DILocalVariable(name: "a", scope: !350, file: !1, line: 585, type: !43)
!883 = !DILocation(line: 585, column: 28, scope: !350)
!884 = !DILocation(line: 585, column: 60, scope: !350)
!885 = !DILocation(line: 585, column: 32, scope: !350)
!886 = !DILocalVariable(name: "r", scope: !350, file: !1, line: 586, type: !62)
!887 = !DILocation(line: 586, column: 6, scope: !350)
!888 = !DILocation(line: 588, column: 2, scope: !350)
!889 = !DILocalVariable(name: "magic_test", scope: !890, file: !1, line: 588, type: !62)
!890 = distinct !DILexicalBlock(scope: !350, file: !1, line: 588, column: 2)
!891 = !DILocation(line: 588, column: 2, scope: !890)
!892 = !DILocation(line: 588, column: 2, scope: !893)
!893 = !DILexicalBlockFile(scope: !890, file: !1, discriminator: 1)
!894 = !DILocation(line: 588, column: 2, scope: !895)
!895 = !DILexicalBlockFile(scope: !896, file: !1, discriminator: 2)
!896 = distinct !DILexicalBlock(scope: !890, file: !1, line: 588, column: 2)
!897 = !DILocation(line: 588, column: 2, scope: !898)
!898 = !DILexicalBlockFile(scope: !890, file: !1, discriminator: 3)
!899 = !DILocation(line: 591, column: 13, scope: !350)
!900 = !DILocation(line: 591, column: 2, scope: !350)
!901 = !DILocation(line: 591, column: 5, scope: !350)
!902 = !DILocation(line: 591, column: 11, scope: !350)
!903 = !DILocation(line: 593, column: 6, scope: !904)
!904 = distinct !DILexicalBlock(scope: !350, file: !1, line: 593, column: 6)
!905 = !DILocation(line: 593, column: 12, scope: !904)
!906 = !DILocation(line: 593, column: 6, scope: !350)
!907 = !DILocation(line: 594, column: 44, scope: !904)
!908 = !DILocation(line: 594, column: 7, scope: !904)
!909 = !DILocation(line: 594, column: 5, scope: !904)
!910 = !DILocation(line: 594, column: 3, scope: !904)
!911 = !DILocation(line: 596, column: 7, scope: !912)
!912 = distinct !DILexicalBlock(scope: !913, file: !1, line: 596, column: 7)
!913 = distinct !DILexicalBlock(scope: !904, file: !1, line: 595, column: 7)
!914 = !DILocation(line: 596, column: 10, scope: !912)
!915 = !DILocation(line: 596, column: 15, scope: !912)
!916 = !DILocation(line: 596, column: 7, scope: !913)
!917 = !DILocation(line: 597, column: 4, scope: !912)
!918 = !DILocation(line: 597, column: 7, scope: !912)
!919 = !DILocation(line: 597, column: 13, scope: !912)
!920 = !DILocation(line: 597, column: 19, scope: !912)
!921 = !DILocation(line: 599, column: 10, scope: !350)
!922 = !DILocation(line: 599, column: 2, scope: !350)
!923 = !DILocation(line: 600, column: 1, scope: !350)
!924 = !DILocalVariable(name: "_a", arg: 1, scope: !351, file: !1, line: 1211, type: !63)
!925 = !DILocation(line: 1211, column: 48, scope: !351)
!926 = !DILocalVariable(name: "_ma", arg: 2, scope: !351, file: !1, line: 1211, type: !63)
!927 = !DILocation(line: 1211, column: 68, scope: !351)
!928 = !DILocalVariable(name: "_excluded_func", arg: 3, scope: !351, file: !1, line: 1212, type: !327)
!929 = !DILocation(line: 1212, column: 12, scope: !351)
!930 = !DILocalVariable(name: "_client_data", arg: 4, scope: !351, file: !1, line: 1213, type: !311)
!931 = !DILocation(line: 1213, column: 11, scope: !351)
!932 = !DILocalVariable(name: "a", scope: !351, file: !1, line: 1215, type: !43)
!933 = !DILocation(line: 1215, column: 28, scope: !351)
!934 = !DILocation(line: 1215, column: 60, scope: !351)
!935 = !DILocation(line: 1215, column: 32, scope: !351)
!936 = !DILocation(line: 1216, column: 2, scope: !351)
!937 = !DILocalVariable(name: "magic_test", scope: !938, file: !1, line: 1216, type: !62)
!938 = distinct !DILexicalBlock(scope: !351, file: !1, line: 1216, column: 2)
!939 = !DILocation(line: 1216, column: 2, scope: !938)
!940 = !DILocation(line: 1216, column: 2, scope: !941)
!941 = !DILexicalBlockFile(scope: !938, file: !1, discriminator: 1)
!942 = !DILocation(line: 1216, column: 2, scope: !943)
!943 = !DILexicalBlockFile(scope: !944, file: !1, discriminator: 2)
!944 = distinct !DILexicalBlock(scope: !938, file: !1, line: 1216, column: 2)
!945 = !DILocation(line: 1216, column: 2, scope: !946)
!946 = !DILexicalBlockFile(scope: !938, file: !1, discriminator: 3)
!947 = !DILocation(line: 1218, column: 16, scope: !351)
!948 = !DILocation(line: 1218, column: 2, scope: !351)
!949 = !DILocation(line: 1218, column: 5, scope: !351)
!950 = !DILocation(line: 1218, column: 14, scope: !351)
!951 = !DILocation(line: 1219, column: 24, scope: !351)
!952 = !DILocation(line: 1219, column: 2, scope: !351)
!953 = !DILocation(line: 1219, column: 5, scope: !351)
!954 = !DILocation(line: 1219, column: 22, scope: !351)
!955 = !DILocation(line: 1220, column: 24, scope: !351)
!956 = !DILocation(line: 1220, column: 2, scope: !351)
!957 = !DILocation(line: 1220, column: 5, scope: !351)
!958 = !DILocation(line: 1220, column: 22, scope: !351)
!959 = !DILocation(line: 1221, column: 2, scope: !351)
!960 = !DILocation(line: 1222, column: 1, scope: !351)
!961 = !DILocalVariable(name: "_a", arg: 1, scope: !354, file: !1, line: 1225, type: !63)
!962 = !DILocation(line: 1225, column: 64, scope: !354)
!963 = !DILocalVariable(name: "_metadata_filter_func", arg: 2, scope: !354, file: !1, line: 1226, type: !321)
!964 = !DILocation(line: 1226, column: 11, scope: !354)
!965 = !DILocalVariable(name: "_client_data", arg: 3, scope: !354, file: !1, line: 1227, type: !311)
!966 = !DILocation(line: 1227, column: 36, scope: !354)
!967 = !DILocalVariable(name: "a", scope: !354, file: !1, line: 1229, type: !43)
!968 = !DILocation(line: 1229, column: 28, scope: !354)
!969 = !DILocation(line: 1229, column: 60, scope: !354)
!970 = !DILocation(line: 1229, column: 32, scope: !354)
!971 = !DILocation(line: 1231, column: 2, scope: !354)
!972 = !DILocalVariable(name: "magic_test", scope: !973, file: !1, line: 1231, type: !62)
!973 = distinct !DILexicalBlock(scope: !354, file: !1, line: 1231, column: 2)
!974 = !DILocation(line: 1231, column: 2, scope: !973)
!975 = !DILocation(line: 1231, column: 2, scope: !976)
!976 = !DILexicalBlockFile(scope: !973, file: !1, discriminator: 1)
!977 = !DILocation(line: 1231, column: 2, scope: !978)
!978 = !DILexicalBlockFile(scope: !979, file: !1, discriminator: 2)
!979 = distinct !DILexicalBlock(scope: !973, file: !1, line: 1231, column: 2)
!980 = !DILocation(line: 1231, column: 2, scope: !981)
!981 = !DILexicalBlockFile(scope: !973, file: !1, discriminator: 3)
!982 = !DILocation(line: 1234, column: 28, scope: !354)
!983 = !DILocation(line: 1234, column: 2, scope: !354)
!984 = !DILocation(line: 1234, column: 5, scope: !354)
!985 = !DILocation(line: 1234, column: 26, scope: !354)
!986 = !DILocation(line: 1235, column: 28, scope: !354)
!987 = !DILocation(line: 1235, column: 2, scope: !354)
!988 = !DILocation(line: 1235, column: 5, scope: !354)
!989 = !DILocation(line: 1235, column: 26, scope: !354)
!990 = !DILocation(line: 1236, column: 2, scope: !354)
!991 = !DILocation(line: 1237, column: 1, scope: !354)
!992 = !DILocalVariable(name: "_a", arg: 1, scope: !357, file: !1, line: 1240, type: !63)
!993 = !DILocation(line: 1240, column: 47, scope: !357)
!994 = !DILocalVariable(name: "a", scope: !357, file: !1, line: 1242, type: !43)
!995 = !DILocation(line: 1242, column: 28, scope: !357)
!996 = !DILocation(line: 1242, column: 60, scope: !357)
!997 = !DILocation(line: 1242, column: 32, scope: !357)
!998 = !DILocalVariable(name: "t", scope: !357, file: !1, line: 1243, type: !153)
!999 = !DILocation(line: 1243, column: 15, scope: !357)
!1000 = !DILocation(line: 1243, column: 19, scope: !357)
!1001 = !DILocation(line: 1243, column: 22, scope: !357)
!1002 = !DILocation(line: 1245, column: 2, scope: !357)
!1003 = !DILocalVariable(name: "magic_test", scope: !1004, file: !1, line: 1245, type: !62)
!1004 = distinct !DILexicalBlock(scope: !357, file: !1, line: 1245, column: 2)
!1005 = !DILocation(line: 1245, column: 2, scope: !1004)
!1006 = !DILocation(line: 1245, column: 2, scope: !1007)
!1007 = !DILexicalBlockFile(scope: !1004, file: !1, discriminator: 1)
!1008 = !DILocation(line: 1245, column: 2, scope: !1009)
!1009 = !DILexicalBlockFile(scope: !1010, file: !1, discriminator: 2)
!1010 = distinct !DILexicalBlock(scope: !1004, file: !1, line: 1245, column: 2)
!1011 = !DILocation(line: 1245, column: 2, scope: !1012)
!1012 = !DILexicalBlockFile(scope: !1004, file: !1, discriminator: 3)
!1013 = !DILocation(line: 1249, column: 10, scope: !357)
!1014 = !DILocation(line: 1249, column: 13, scope: !357)
!1015 = !DILocation(line: 1249, column: 24, scope: !357)
!1016 = !DILocation(line: 1249, column: 40, scope: !357)
!1017 = !DILocation(line: 1249, column: 43, scope: !1018)
!1018 = !DILexicalBlockFile(scope: !357, file: !1, discriminator: 1)
!1019 = !DILocation(line: 1249, column: 46, scope: !1018)
!1020 = !DILocation(line: 1249, column: 40, scope: !1018)
!1021 = !DILocation(line: 1249, column: 40, scope: !1022)
!1022 = !DILexicalBlockFile(scope: !357, file: !1, discriminator: 2)
!1023 = !DILocation(line: 1249, column: 2, scope: !1022)
!1024 = !DILocation(line: 1250, column: 1, scope: !357)
!1025 = !DILocalVariable(name: "_a", arg: 1, scope: !358, file: !1, line: 1257, type: !63)
!1026 = !DILocation(line: 1257, column: 43, scope: !358)
!1027 = !DILocalVariable(name: "a", scope: !358, file: !1, line: 1259, type: !43)
!1028 = !DILocation(line: 1259, column: 28, scope: !358)
!1029 = !DILocation(line: 1259, column: 60, scope: !358)
!1030 = !DILocation(line: 1259, column: 32, scope: !358)
!1031 = !DILocalVariable(name: "t", scope: !358, file: !1, line: 1260, type: !153)
!1032 = !DILocation(line: 1260, column: 15, scope: !358)
!1033 = !DILocation(line: 1260, column: 19, scope: !358)
!1034 = !DILocation(line: 1260, column: 22, scope: !358)
!1035 = !DILocation(line: 1262, column: 2, scope: !358)
!1036 = !DILocalVariable(name: "magic_test", scope: !1037, file: !1, line: 1262, type: !62)
!1037 = distinct !DILexicalBlock(scope: !358, file: !1, line: 1262, column: 2)
!1038 = !DILocation(line: 1262, column: 2, scope: !1037)
!1039 = !DILocation(line: 1262, column: 2, scope: !1040)
!1040 = !DILexicalBlockFile(scope: !1037, file: !1, discriminator: 1)
!1041 = !DILocation(line: 1262, column: 2, scope: !1042)
!1042 = !DILexicalBlockFile(scope: !1043, file: !1, discriminator: 2)
!1043 = distinct !DILexicalBlock(scope: !1037, file: !1, line: 1262, column: 2)
!1044 = !DILocation(line: 1262, column: 2, scope: !1045)
!1045 = !DILexicalBlockFile(scope: !1037, file: !1, discriminator: 3)
!1046 = !DILocation(line: 1266, column: 6, scope: !1047)
!1047 = distinct !DILexicalBlock(scope: !358, file: !1, line: 1266, column: 6)
!1048 = !DILocation(line: 1266, column: 9, scope: !1047)
!1049 = !DILocation(line: 1266, column: 20, scope: !1047)
!1050 = !DILocation(line: 1266, column: 36, scope: !1047)
!1051 = !DILocation(line: 1266, column: 40, scope: !1052)
!1052 = !DILexicalBlockFile(scope: !1047, file: !1, discriminator: 1)
!1053 = !DILocation(line: 1266, column: 43, scope: !1052)
!1054 = !DILocation(line: 1266, column: 6, scope: !1052)
!1055 = !DILocation(line: 1267, column: 3, scope: !1047)
!1056 = !DILocation(line: 1269, column: 35, scope: !1057)
!1057 = distinct !DILexicalBlock(scope: !358, file: !1, line: 1269, column: 6)
!1058 = !DILocation(line: 1269, column: 6, scope: !1057)
!1059 = !DILocation(line: 1269, column: 6, scope: !358)
!1060 = !DILocation(line: 1270, column: 13, scope: !1061)
!1061 = distinct !DILexicalBlock(scope: !1057, file: !1, line: 1269, column: 39)
!1062 = !DILocation(line: 1270, column: 16, scope: !1061)
!1063 = !DILocation(line: 1270, column: 19, scope: !1061)
!1064 = !DILocation(line: 1270, column: 29, scope: !1061)
!1065 = !DILocation(line: 1270, column: 32, scope: !1061)
!1066 = !DILocation(line: 1271, column: 7, scope: !1061)
!1067 = !DILocation(line: 1271, column: 10, scope: !1061)
!1068 = !DILocation(line: 1271, column: 14, scope: !1061)
!1069 = !DILocation(line: 1271, column: 22, scope: !1061)
!1070 = !DILocation(line: 1271, column: 25, scope: !1061)
!1071 = !DILocation(line: 1271, column: 29, scope: !1061)
!1072 = !DILocation(line: 1271, column: 38, scope: !1061)
!1073 = !DILocation(line: 1271, column: 41, scope: !1061)
!1074 = !DILocation(line: 1270, column: 3, scope: !1061)
!1075 = !DILocation(line: 1272, column: 3, scope: !1061)
!1076 = !DILocation(line: 1272, column: 6, scope: !1061)
!1077 = !DILocation(line: 1272, column: 13, scope: !1061)
!1078 = !DILocation(line: 1272, column: 19, scope: !1061)
!1079 = !DILocation(line: 1273, column: 2, scope: !1061)
!1080 = !DILocation(line: 1273, column: 33, scope: !1081)
!1081 = !DILexicalBlockFile(scope: !1082, file: !1, discriminator: 1)
!1082 = distinct !DILexicalBlock(scope: !1057, file: !1, line: 1273, column: 13)
!1083 = !DILocation(line: 1273, column: 13, scope: !1081)
!1084 = !DILocation(line: 1274, column: 13, scope: !1085)
!1085 = distinct !DILexicalBlock(scope: !1082, file: !1, line: 1273, column: 37)
!1086 = !DILocation(line: 1274, column: 16, scope: !1085)
!1087 = !DILocation(line: 1274, column: 19, scope: !1085)
!1088 = !DILocation(line: 1274, column: 29, scope: !1085)
!1089 = !DILocation(line: 1274, column: 32, scope: !1085)
!1090 = !DILocation(line: 1275, column: 7, scope: !1085)
!1091 = !DILocation(line: 1275, column: 10, scope: !1085)
!1092 = !DILocation(line: 1275, column: 13, scope: !1085)
!1093 = !DILocation(line: 1275, column: 21, scope: !1085)
!1094 = !DILocation(line: 1275, column: 24, scope: !1085)
!1095 = !DILocation(line: 1275, column: 27, scope: !1085)
!1096 = !DILocation(line: 1275, column: 36, scope: !1085)
!1097 = !DILocation(line: 1275, column: 39, scope: !1085)
!1098 = !DILocation(line: 1274, column: 3, scope: !1085)
!1099 = !DILocation(line: 1276, column: 3, scope: !1085)
!1100 = !DILocation(line: 1276, column: 6, scope: !1085)
!1101 = !DILocation(line: 1276, column: 13, scope: !1085)
!1102 = !DILocation(line: 1276, column: 19, scope: !1085)
!1103 = !DILocation(line: 1277, column: 2, scope: !1085)
!1104 = !DILocation(line: 1278, column: 2, scope: !358)
!1105 = !DILocation(line: 1278, column: 5, scope: !358)
!1106 = !DILocation(line: 1278, column: 13, scope: !358)
!1107 = !DILocation(line: 1279, column: 2, scope: !358)
!1108 = !DILocation(line: 1280, column: 1, scope: !358)
!1109 = !DILocalVariable(name: "t", arg: 1, scope: !448, file: !1, line: 2525, type: !153)
!1110 = !DILocation(line: 2525, column: 43, scope: !448)
!1111 = !DILocalVariable(name: "st", scope: !448, file: !1, line: 2527, type: !412)
!1112 = !DILocation(line: 2527, column: 21, scope: !448)
!1113 = !DILocation(line: 2533, column: 6, scope: !1114)
!1114 = distinct !DILexicalBlock(scope: !448, file: !1, line: 2533, column: 6)
!1115 = !DILocation(line: 2533, column: 9, scope: !1114)
!1116 = !DILocation(line: 2533, column: 15, scope: !1114)
!1117 = !DILocation(line: 2533, column: 6, scope: !448)
!1118 = !DILocation(line: 2534, column: 26, scope: !1119)
!1119 = distinct !DILexicalBlock(scope: !1114, file: !1, line: 2533, column: 26)
!1120 = !DILocation(line: 2534, column: 8, scope: !1119)
!1121 = !DILocation(line: 2534, column: 6, scope: !1119)
!1122 = !DILocation(line: 2535, column: 7, scope: !1123)
!1123 = distinct !DILexicalBlock(scope: !1119, file: !1, line: 2535, column: 7)
!1124 = !DILocation(line: 2535, column: 10, scope: !1123)
!1125 = !DILocation(line: 2535, column: 7, scope: !1119)
!1126 = !DILocation(line: 2536, column: 4, scope: !1123)
!1127 = !DILocation(line: 2537, column: 8, scope: !1128)
!1128 = distinct !DILexicalBlock(scope: !1119, file: !1, line: 2537, column: 7)
!1129 = !DILocation(line: 2537, column: 7, scope: !1119)
!1130 = !DILocation(line: 2538, column: 4, scope: !1128)
!1131 = !DILocation(line: 2539, column: 2, scope: !1119)
!1132 = !DILocation(line: 2548, column: 26, scope: !448)
!1133 = !DILocation(line: 2548, column: 7, scope: !448)
!1134 = !DILocation(line: 2548, column: 5, scope: !448)
!1135 = !DILocation(line: 2550, column: 6, scope: !1136)
!1136 = distinct !DILexicalBlock(scope: !448, file: !1, line: 2550, column: 6)
!1137 = !DILocation(line: 2550, column: 9, scope: !1136)
!1138 = !DILocation(line: 2550, column: 6, scope: !448)
!1139 = !DILocation(line: 2551, column: 3, scope: !1136)
!1140 = !DILocation(line: 2553, column: 10, scope: !448)
!1141 = !DILocation(line: 2553, column: 2, scope: !448)
!1142 = !DILocation(line: 2554, column: 1, scope: !448)
!1143 = !DILocalVariable(name: "t", arg: 1, scope: !442, file: !1, line: 2051, type: !153)
!1144 = !DILocation(line: 2051, column: 24, scope: !442)
!1145 = !DILocalVariable(name: "path", arg: 2, scope: !442, file: !1, line: 2051, type: !119)
!1146 = !DILocation(line: 2051, column: 39, scope: !442)
!1147 = !DILocalVariable(name: "filesystem_id", arg: 3, scope: !442, file: !1, line: 2051, type: !62)
!1148 = !DILocation(line: 2051, column: 49, scope: !442)
!1149 = !DILocalVariable(name: "dev", arg: 4, scope: !442, file: !1, line: 2052, type: !91)
!1150 = !DILocation(line: 2052, column: 13, scope: !442)
!1151 = !DILocalVariable(name: "ino", arg: 5, scope: !442, file: !1, line: 2052, type: !91)
!1152 = !DILocation(line: 2052, column: 26, scope: !442)
!1153 = !DILocalVariable(name: "rt", arg: 6, scope: !442, file: !1, line: 2052, type: !383)
!1154 = !DILocation(line: 2052, column: 52, scope: !442)
!1155 = !DILocalVariable(name: "te", scope: !442, file: !1, line: 2054, type: !157)
!1156 = !DILocation(line: 2054, column: 21, scope: !442)
!1157 = !DILocation(line: 2056, column: 7, scope: !442)
!1158 = !DILocation(line: 2056, column: 5, scope: !442)
!1159 = !DILocation(line: 2057, column: 13, scope: !442)
!1160 = !DILocation(line: 2057, column: 16, scope: !442)
!1161 = !DILocation(line: 2057, column: 2, scope: !442)
!1162 = !DILocation(line: 2057, column: 6, scope: !442)
!1163 = !DILocation(line: 2057, column: 11, scope: !442)
!1164 = !DILocation(line: 2058, column: 15, scope: !442)
!1165 = !DILocation(line: 2058, column: 18, scope: !442)
!1166 = !DILocation(line: 2058, column: 2, scope: !442)
!1167 = !DILocation(line: 2058, column: 6, scope: !442)
!1168 = !DILocation(line: 2058, column: 13, scope: !442)
!1169 = !DILocation(line: 2059, column: 6, scope: !1170)
!1170 = distinct !DILexicalBlock(scope: !442, file: !1, line: 2059, column: 6)
!1171 = !DILocation(line: 2059, column: 10, scope: !1170)
!1172 = !DILocation(line: 2059, column: 6, scope: !442)
!1173 = !DILocation(line: 2060, column: 15, scope: !1170)
!1174 = !DILocation(line: 2060, column: 19, scope: !1170)
!1175 = !DILocation(line: 2060, column: 27, scope: !1170)
!1176 = !DILocation(line: 2060, column: 33, scope: !1170)
!1177 = !DILocation(line: 2060, column: 3, scope: !1170)
!1178 = !DILocation(line: 2060, column: 7, scope: !1170)
!1179 = !DILocation(line: 2060, column: 13, scope: !1170)
!1180 = !DILocation(line: 2061, column: 13, scope: !442)
!1181 = !DILocation(line: 2061, column: 2, scope: !442)
!1182 = !DILocation(line: 2061, column: 5, scope: !442)
!1183 = !DILocation(line: 2061, column: 11, scope: !442)
!1184 = !DILocation(line: 2062, column: 2, scope: !442)
!1185 = !DILocation(line: 2062, column: 2, scope: !1186)
!1186 = !DILexicalBlockFile(scope: !1187, file: !1, discriminator: 1)
!1187 = distinct !DILexicalBlock(scope: !442, file: !1, line: 2062, column: 2)
!1188 = !DILocation(line: 2063, column: 2, scope: !442)
!1189 = !DILocation(line: 2063, column: 6, scope: !442)
!1190 = !DILocation(line: 2063, column: 24, scope: !442)
!1191 = !DILocation(line: 2064, column: 2, scope: !442)
!1192 = !DILocation(line: 2064, column: 2, scope: !1193)
!1193 = !DILexicalBlockFile(scope: !442, file: !1, discriminator: 1)
!1194 = !DILocation(line: 2064, column: 2, scope: !1195)
!1195 = !DILexicalBlockFile(scope: !442, file: !1, discriminator: 2)
!1196 = !DILocation(line: 2064, column: 2, scope: !1197)
!1197 = !DILexicalBlockFile(scope: !442, file: !1, discriminator: 3)
!1198 = !DILocation(line: 2065, column: 2, scope: !442)
!1199 = !DILocation(line: 2065, column: 6, scope: !442)
!1200 = !DILocation(line: 2065, column: 12, scope: !442)
!1201 = !DILocation(line: 2066, column: 22, scope: !442)
!1202 = !DILocation(line: 2066, column: 2, scope: !442)
!1203 = !DILocation(line: 2066, column: 6, scope: !442)
!1204 = !DILocation(line: 2066, column: 20, scope: !442)
!1205 = !DILocation(line: 2067, column: 12, scope: !442)
!1206 = !DILocation(line: 2067, column: 2, scope: !442)
!1207 = !DILocation(line: 2067, column: 6, scope: !442)
!1208 = !DILocation(line: 2067, column: 10, scope: !442)
!1209 = !DILocation(line: 2068, column: 12, scope: !442)
!1210 = !DILocation(line: 2068, column: 2, scope: !442)
!1211 = !DILocation(line: 2068, column: 6, scope: !442)
!1212 = !DILocation(line: 2068, column: 10, scope: !442)
!1213 = !DILocation(line: 2069, column: 23, scope: !442)
!1214 = !DILocation(line: 2069, column: 26, scope: !442)
!1215 = !DILocation(line: 2069, column: 2, scope: !442)
!1216 = !DILocation(line: 2069, column: 6, scope: !442)
!1217 = !DILocation(line: 2069, column: 21, scope: !442)
!1218 = !DILocation(line: 2070, column: 26, scope: !442)
!1219 = !DILocation(line: 2070, column: 30, scope: !442)
!1220 = !DILocation(line: 2070, column: 35, scope: !442)
!1221 = !DILocation(line: 2070, column: 2, scope: !442)
!1222 = !DILocation(line: 2070, column: 6, scope: !442)
!1223 = !DILocation(line: 2070, column: 19, scope: !442)
!1224 = !DILocation(line: 2070, column: 24, scope: !442)
!1225 = !DILocation(line: 2071, column: 6, scope: !1226)
!1226 = distinct !DILexicalBlock(scope: !442, file: !1, line: 2071, column: 6)
!1227 = !DILocation(line: 2071, column: 9, scope: !1226)
!1228 = !DILocation(line: 2071, column: 6, scope: !442)
!1229 = !DILocation(line: 2072, column: 28, scope: !1230)
!1230 = distinct !DILexicalBlock(scope: !1226, file: !1, line: 2071, column: 18)
!1231 = !DILocation(line: 2072, column: 32, scope: !1230)
!1232 = !DILocation(line: 2072, column: 3, scope: !1230)
!1233 = !DILocation(line: 2072, column: 7, scope: !1230)
!1234 = !DILocation(line: 2072, column: 20, scope: !1230)
!1235 = !DILocation(line: 2072, column: 26, scope: !1230)
!1236 = !DILocation(line: 2073, column: 33, scope: !1230)
!1237 = !DILocation(line: 2073, column: 37, scope: !1230)
!1238 = !DILocation(line: 2073, column: 3, scope: !1230)
!1239 = !DILocation(line: 2073, column: 7, scope: !1230)
!1240 = !DILocation(line: 2073, column: 20, scope: !1230)
!1241 = !DILocation(line: 2073, column: 31, scope: !1230)
!1242 = !DILocation(line: 2074, column: 28, scope: !1230)
!1243 = !DILocation(line: 2074, column: 32, scope: !1230)
!1244 = !DILocation(line: 2074, column: 3, scope: !1230)
!1245 = !DILocation(line: 2074, column: 7, scope: !1230)
!1246 = !DILocation(line: 2074, column: 20, scope: !1230)
!1247 = !DILocation(line: 2074, column: 26, scope: !1230)
!1248 = !DILocation(line: 2075, column: 33, scope: !1230)
!1249 = !DILocation(line: 2075, column: 37, scope: !1230)
!1250 = !DILocation(line: 2075, column: 3, scope: !1230)
!1251 = !DILocation(line: 2075, column: 7, scope: !1230)
!1252 = !DILocation(line: 2075, column: 20, scope: !1230)
!1253 = !DILocation(line: 2075, column: 31, scope: !1230)
!1254 = !DILocation(line: 2076, column: 31, scope: !1230)
!1255 = !DILocation(line: 2076, column: 35, scope: !1230)
!1256 = !DILocation(line: 2076, column: 3, scope: !1230)
!1257 = !DILocation(line: 2076, column: 7, scope: !1230)
!1258 = !DILocation(line: 2076, column: 20, scope: !1230)
!1259 = !DILocation(line: 2076, column: 29, scope: !1230)
!1260 = !DILocation(line: 2077, column: 30, scope: !1230)
!1261 = !DILocation(line: 2077, column: 34, scope: !1230)
!1262 = !DILocation(line: 2077, column: 3, scope: !1230)
!1263 = !DILocation(line: 2077, column: 7, scope: !1230)
!1264 = !DILocation(line: 2077, column: 20, scope: !1230)
!1265 = !DILocation(line: 2077, column: 28, scope: !1230)
!1266 = !DILocation(line: 2078, column: 2, scope: !1230)
!1267 = !DILocation(line: 2079, column: 1, scope: !442)
!1268 = !DILocalVariable(name: "t", arg: 1, scope: !447, file: !1, line: 2487, type: !153)
!1269 = !DILocation(line: 2487, column: 34, scope: !447)
!1270 = !DILocalVariable(name: "st", scope: !447, file: !1, line: 2489, type: !412)
!1271 = !DILocation(line: 2489, column: 21, scope: !447)
!1272 = !DILocation(line: 2494, column: 6, scope: !1273)
!1273 = distinct !DILexicalBlock(scope: !447, file: !1, line: 2494, column: 6)
!1274 = !DILocation(line: 2494, column: 9, scope: !1273)
!1275 = !DILocation(line: 2494, column: 15, scope: !1273)
!1276 = !DILocation(line: 2494, column: 6, scope: !447)
!1277 = !DILocation(line: 2496, column: 27, scope: !1278)
!1278 = distinct !DILexicalBlock(scope: !1273, file: !1, line: 2494, column: 27)
!1279 = !DILocation(line: 2496, column: 8, scope: !1278)
!1280 = !DILocation(line: 2496, column: 6, scope: !1278)
!1281 = !DILocation(line: 2497, column: 7, scope: !1282)
!1282 = distinct !DILexicalBlock(scope: !1278, file: !1, line: 2497, column: 7)
!1283 = !DILocation(line: 2497, column: 10, scope: !1282)
!1284 = !DILocation(line: 2497, column: 7, scope: !1278)
!1285 = !DILocation(line: 2498, column: 4, scope: !1282)
!1286 = !DILocation(line: 2499, column: 7, scope: !1287)
!1287 = distinct !DILexicalBlock(scope: !1278, file: !1, line: 2499, column: 7)
!1288 = !DILocation(line: 2499, column: 7, scope: !1278)
!1289 = !DILocation(line: 2500, column: 4, scope: !1287)
!1290 = !DILocation(line: 2503, column: 8, scope: !1291)
!1291 = distinct !DILexicalBlock(scope: !1278, file: !1, line: 2503, column: 7)
!1292 = !DILocation(line: 2503, column: 7, scope: !1278)
!1293 = !DILocation(line: 2504, column: 4, scope: !1291)
!1294 = !DILocation(line: 2509, column: 2, scope: !1278)
!1295 = !DILocation(line: 2511, column: 25, scope: !447)
!1296 = !DILocation(line: 2511, column: 7, scope: !447)
!1297 = !DILocation(line: 2511, column: 5, scope: !447)
!1298 = !DILocation(line: 2513, column: 6, scope: !1299)
!1299 = distinct !DILexicalBlock(scope: !447, file: !1, line: 2513, column: 6)
!1300 = !DILocation(line: 2513, column: 9, scope: !1299)
!1301 = !DILocation(line: 2513, column: 6, scope: !447)
!1302 = !DILocation(line: 2514, column: 3, scope: !1299)
!1303 = !DILocation(line: 2516, column: 10, scope: !447)
!1304 = !DILocation(line: 2516, column: 2, scope: !447)
!1305 = !DILocation(line: 2517, column: 1, scope: !447)
!1306 = !DILocalVariable(name: "_a", arg: 1, scope: !359, file: !1, line: 1283, type: !63)
!1307 = !DILocation(line: 1283, column: 40, scope: !359)
!1308 = !DILocalVariable(name: "pathname", arg: 2, scope: !359, file: !1, line: 1283, type: !119)
!1309 = !DILocation(line: 1283, column: 56, scope: !359)
!1310 = !DILocalVariable(name: "a", scope: !359, file: !1, line: 1285, type: !43)
!1311 = !DILocation(line: 1285, column: 28, scope: !359)
!1312 = !DILocation(line: 1285, column: 60, scope: !359)
!1313 = !DILocation(line: 1285, column: 32, scope: !359)
!1314 = !DILocation(line: 1287, column: 2, scope: !359)
!1315 = !DILocalVariable(name: "magic_test", scope: !1316, file: !1, line: 1287, type: !62)
!1316 = distinct !DILexicalBlock(scope: !359, file: !1, line: 1287, column: 2)
!1317 = !DILocation(line: 1287, column: 2, scope: !1316)
!1318 = !DILocation(line: 1287, column: 2, scope: !1319)
!1319 = !DILexicalBlockFile(scope: !1316, file: !1, discriminator: 1)
!1320 = !DILocation(line: 1287, column: 2, scope: !1321)
!1321 = !DILexicalBlockFile(scope: !1322, file: !1, discriminator: 2)
!1322 = distinct !DILexicalBlock(scope: !1316, file: !1, line: 1287, column: 2)
!1323 = !DILocation(line: 1287, column: 2, scope: !1324)
!1324 = !DILexicalBlockFile(scope: !1316, file: !1, discriminator: 3)
!1325 = !DILocation(line: 1290, column: 23, scope: !359)
!1326 = !DILocation(line: 1290, column: 26, scope: !359)
!1327 = !DILocation(line: 1290, column: 2, scope: !359)
!1328 = !DILocation(line: 1292, column: 34, scope: !359)
!1329 = !DILocation(line: 1292, column: 38, scope: !359)
!1330 = !DILocation(line: 1292, column: 10, scope: !359)
!1331 = !DILocation(line: 1292, column: 2, scope: !359)
!1332 = !DILocation(line: 1293, column: 1, scope: !359)
!1333 = !DILocalVariable(name: "_a", arg: 1, scope: !434, file: !1, line: 1327, type: !63)
!1334 = !DILocation(line: 1327, column: 41, scope: !434)
!1335 = !DILocalVariable(name: "pathname", arg: 2, scope: !434, file: !1, line: 1327, type: !119)
!1336 = !DILocation(line: 1327, column: 57, scope: !434)
!1337 = !DILocalVariable(name: "a", scope: !434, file: !1, line: 1329, type: !43)
!1338 = !DILocation(line: 1329, column: 28, scope: !434)
!1339 = !DILocation(line: 1329, column: 60, scope: !434)
!1340 = !DILocation(line: 1329, column: 32, scope: !434)
!1341 = !DILocation(line: 1331, column: 6, scope: !1342)
!1342 = distinct !DILexicalBlock(scope: !434, file: !1, line: 1331, column: 6)
!1343 = !DILocation(line: 1331, column: 9, scope: !1342)
!1344 = !DILocation(line: 1331, column: 14, scope: !1342)
!1345 = !DILocation(line: 1331, column: 6, scope: !434)
!1346 = !DILocation(line: 1332, column: 25, scope: !1342)
!1347 = !DILocation(line: 1332, column: 28, scope: !1342)
!1348 = !DILocation(line: 1332, column: 34, scope: !1342)
!1349 = !DILocation(line: 1333, column: 7, scope: !1342)
!1350 = !DILocation(line: 1333, column: 10, scope: !1342)
!1351 = !DILocation(line: 1333, column: 16, scope: !1342)
!1352 = !DILocation(line: 1332, column: 13, scope: !1342)
!1353 = !DILocation(line: 1332, column: 3, scope: !1342)
!1354 = !DILocation(line: 1332, column: 6, scope: !1342)
!1355 = !DILocation(line: 1332, column: 11, scope: !1342)
!1356 = !DILocation(line: 1335, column: 23, scope: !1342)
!1357 = !DILocation(line: 1335, column: 33, scope: !1342)
!1358 = !DILocation(line: 1335, column: 36, scope: !1342)
!1359 = !DILocation(line: 1336, column: 7, scope: !1342)
!1360 = !DILocation(line: 1336, column: 10, scope: !1342)
!1361 = !DILocation(line: 1336, column: 16, scope: !1342)
!1362 = !DILocation(line: 1335, column: 13, scope: !1342)
!1363 = !DILocation(line: 1335, column: 3, scope: !1342)
!1364 = !DILocation(line: 1335, column: 6, scope: !1342)
!1365 = !DILocation(line: 1335, column: 11, scope: !1342)
!1366 = !DILocation(line: 1337, column: 6, scope: !1367)
!1367 = distinct !DILexicalBlock(scope: !434, file: !1, line: 1337, column: 6)
!1368 = !DILocation(line: 1337, column: 9, scope: !1367)
!1369 = !DILocation(line: 1337, column: 14, scope: !1367)
!1370 = !DILocation(line: 1337, column: 6, scope: !434)
!1371 = !DILocation(line: 1338, column: 22, scope: !1372)
!1372 = distinct !DILexicalBlock(scope: !1367, file: !1, line: 1337, column: 23)
!1373 = !DILocation(line: 1338, column: 25, scope: !1372)
!1374 = !DILocation(line: 1338, column: 3, scope: !1372)
!1375 = !DILocation(line: 1340, column: 3, scope: !1372)
!1376 = !DILocation(line: 1340, column: 6, scope: !1372)
!1377 = !DILocation(line: 1340, column: 14, scope: !1372)
!1378 = !DILocation(line: 1340, column: 20, scope: !1372)
!1379 = !DILocation(line: 1341, column: 3, scope: !1372)
!1380 = !DILocation(line: 1343, column: 2, scope: !434)
!1381 = !DILocation(line: 1343, column: 5, scope: !434)
!1382 = !DILocation(line: 1343, column: 13, scope: !434)
!1383 = !DILocation(line: 1343, column: 19, scope: !434)
!1384 = !DILocation(line: 1345, column: 2, scope: !434)
!1385 = !DILocation(line: 1346, column: 1, scope: !434)
!1386 = !DILocalVariable(name: "_a", arg: 1, scope: !362, file: !1, line: 1296, type: !63)
!1387 = !DILocation(line: 1296, column: 42, scope: !362)
!1388 = !DILocalVariable(name: "pathname", arg: 2, scope: !362, file: !1, line: 1296, type: !365)
!1389 = !DILocation(line: 1296, column: 61, scope: !362)
!1390 = !DILocalVariable(name: "a", scope: !362, file: !1, line: 1298, type: !43)
!1391 = !DILocation(line: 1298, column: 28, scope: !362)
!1392 = !DILocation(line: 1298, column: 60, scope: !362)
!1393 = !DILocation(line: 1298, column: 32, scope: !362)
!1394 = !DILocalVariable(name: "path", scope: !362, file: !1, line: 1299, type: !130)
!1395 = !DILocation(line: 1299, column: 24, scope: !362)
!1396 = !DILocalVariable(name: "ret", scope: !362, file: !1, line: 1300, type: !62)
!1397 = !DILocation(line: 1300, column: 6, scope: !362)
!1398 = !DILocation(line: 1302, column: 2, scope: !362)
!1399 = !DILocalVariable(name: "magic_test", scope: !1400, file: !1, line: 1302, type: !62)
!1400 = distinct !DILexicalBlock(scope: !362, file: !1, line: 1302, column: 2)
!1401 = !DILocation(line: 1302, column: 2, scope: !1400)
!1402 = !DILocation(line: 1302, column: 2, scope: !1403)
!1403 = !DILexicalBlockFile(scope: !1400, file: !1, discriminator: 1)
!1404 = !DILocation(line: 1302, column: 2, scope: !1405)
!1405 = !DILexicalBlockFile(scope: !1406, file: !1, discriminator: 2)
!1406 = distinct !DILexicalBlock(scope: !1400, file: !1, line: 1302, column: 2)
!1407 = !DILocation(line: 1302, column: 2, scope: !1408)
!1408 = !DILexicalBlockFile(scope: !1400, file: !1, discriminator: 3)
!1409 = !DILocation(line: 1305, column: 23, scope: !362)
!1410 = !DILocation(line: 1305, column: 26, scope: !362)
!1411 = !DILocation(line: 1305, column: 2, scope: !362)
!1412 = !DILocation(line: 1308, column: 2, scope: !362)
!1413 = !DILocation(line: 1308, column: 2, scope: !1414)
!1414 = !DILexicalBlockFile(scope: !1415, file: !1, discriminator: 1)
!1415 = distinct !DILexicalBlock(scope: !362, file: !1, line: 1308, column: 2)
!1416 = !DILocation(line: 1309, column: 44, scope: !1417)
!1417 = distinct !DILexicalBlock(scope: !362, file: !1, line: 1309, column: 6)
!1418 = !DILocation(line: 1310, column: 13, scope: !1417)
!1419 = !DILocation(line: 1310, column: 6, scope: !1417)
!1420 = !DILocation(line: 1309, column: 6, scope: !1417)
!1421 = !DILocation(line: 1310, column: 24, scope: !1417)
!1422 = !DILocation(line: 1309, column: 6, scope: !362)
!1423 = !DILocation(line: 1311, column: 7, scope: !1424)
!1424 = distinct !DILexicalBlock(scope: !1425, file: !1, line: 1311, column: 7)
!1425 = distinct !DILexicalBlock(scope: !1417, file: !1, line: 1310, column: 30)
!1426 = !DILocation(line: 1311, column: 13, scope: !1424)
!1427 = !DILocation(line: 1311, column: 7, scope: !1425)
!1428 = !DILocation(line: 1312, column: 23, scope: !1424)
!1429 = !DILocation(line: 1312, column: 26, scope: !1424)
!1430 = !DILocation(line: 1312, column: 4, scope: !1424)
!1431 = !DILocation(line: 1315, column: 23, scope: !1424)
!1432 = !DILocation(line: 1315, column: 26, scope: !1424)
!1433 = !DILocation(line: 1315, column: 4, scope: !1424)
!1434 = !DILocation(line: 1317, column: 3, scope: !1425)
!1435 = !DILocation(line: 1317, column: 6, scope: !1425)
!1436 = !DILocation(line: 1317, column: 14, scope: !1425)
!1437 = !DILocation(line: 1317, column: 20, scope: !1425)
!1438 = !DILocation(line: 1318, column: 7, scope: !1425)
!1439 = !DILocation(line: 1319, column: 2, scope: !1425)
!1440 = !DILocation(line: 1320, column: 33, scope: !1417)
!1441 = !DILocation(line: 1320, column: 42, scope: !1417)
!1442 = !DILocation(line: 1320, column: 9, scope: !1417)
!1443 = !DILocation(line: 1320, column: 7, scope: !1417)
!1444 = !DILocation(line: 1322, column: 2, scope: !362)
!1445 = !DILocation(line: 1323, column: 10, scope: !362)
!1446 = !DILocation(line: 1323, column: 2, scope: !362)
!1447 = !DILocation(line: 1324, column: 1, scope: !362)
!1448 = !DILocalVariable(name: "_a", arg: 1, scope: !368, file: !1, line: 1353, type: !63)
!1449 = !DILocation(line: 1353, column: 54, scope: !368)
!1450 = !DILocalVariable(name: "a", scope: !368, file: !1, line: 1355, type: !43)
!1451 = !DILocation(line: 1355, column: 28, scope: !368)
!1452 = !DILocation(line: 1355, column: 60, scope: !368)
!1453 = !DILocation(line: 1355, column: 32, scope: !368)
!1454 = !DILocation(line: 1357, column: 2, scope: !368)
!1455 = !DILocalVariable(name: "magic_test", scope: !1456, file: !1, line: 1357, type: !62)
!1456 = distinct !DILexicalBlock(scope: !368, file: !1, line: 1357, column: 2)
!1457 = !DILocation(line: 1357, column: 2, scope: !1456)
!1458 = !DILocation(line: 1357, column: 2, scope: !1459)
!1459 = !DILexicalBlockFile(scope: !1456, file: !1, discriminator: 1)
!1460 = !DILocation(line: 1357, column: 2, scope: !1461)
!1461 = !DILexicalBlockFile(scope: !1462, file: !1, discriminator: 2)
!1462 = distinct !DILexicalBlock(scope: !1456, file: !1, line: 1357, column: 2)
!1463 = !DILocation(line: 1357, column: 2, scope: !1464)
!1464 = !DILexicalBlockFile(scope: !1456, file: !1, discriminator: 3)
!1465 = !DILocation(line: 1360, column: 10, scope: !368)
!1466 = !DILocation(line: 1360, column: 13, scope: !368)
!1467 = !DILocation(line: 1360, column: 19, scope: !368)
!1468 = !DILocation(line: 1360, column: 2, scope: !368)
!1469 = !DILocation(line: 1361, column: 1, scope: !368)
!1470 = !DILocalVariable(name: "_a", arg: 1, scope: !369, file: !1, line: 1417, type: !63)
!1471 = !DILocation(line: 1417, column: 67, scope: !369)
!1472 = !DILocalVariable(name: "a", scope: !369, file: !1, line: 1419, type: !43)
!1473 = !DILocation(line: 1419, column: 28, scope: !369)
!1474 = !DILocation(line: 1419, column: 60, scope: !369)
!1475 = !DILocation(line: 1419, column: 32, scope: !369)
!1476 = !DILocation(line: 1421, column: 2, scope: !369)
!1477 = !DILocalVariable(name: "magic_test", scope: !1478, file: !1, line: 1421, type: !62)
!1478 = distinct !DILexicalBlock(scope: !369, file: !1, line: 1421, column: 2)
!1479 = !DILocation(line: 1421, column: 2, scope: !1478)
!1480 = !DILocation(line: 1421, column: 2, scope: !1481)
!1481 = !DILexicalBlockFile(scope: !1478, file: !1, discriminator: 1)
!1482 = !DILocation(line: 1421, column: 2, scope: !1483)
!1483 = !DILexicalBlockFile(scope: !1484, file: !1, discriminator: 2)
!1484 = distinct !DILexicalBlock(scope: !1478, file: !1, line: 1421, column: 2)
!1485 = !DILocation(line: 1421, column: 2, scope: !1486)
!1486 = !DILexicalBlockFile(scope: !1478, file: !1, discriminator: 3)
!1487 = !DILocation(line: 1424, column: 10, scope: !369)
!1488 = !DILocation(line: 1424, column: 13, scope: !369)
!1489 = !DILocation(line: 1424, column: 19, scope: !369)
!1490 = !DILocation(line: 1424, column: 39, scope: !369)
!1491 = !DILocation(line: 1424, column: 2, scope: !369)
!1492 = !DILocation(line: 1425, column: 1, scope: !369)
!1493 = !DILocalVariable(name: "_a", arg: 1, scope: !370, file: !1, line: 1432, type: !63)
!1494 = !DILocation(line: 1432, column: 64, scope: !370)
!1495 = !DILocalVariable(name: "a", scope: !370, file: !1, line: 1434, type: !43)
!1496 = !DILocation(line: 1434, column: 28, scope: !370)
!1497 = !DILocation(line: 1434, column: 60, scope: !370)
!1498 = !DILocation(line: 1434, column: 32, scope: !370)
!1499 = !DILocation(line: 1436, column: 2, scope: !370)
!1500 = !DILocalVariable(name: "magic_test", scope: !1501, file: !1, line: 1436, type: !62)
!1501 = distinct !DILexicalBlock(scope: !370, file: !1, line: 1436, column: 2)
!1502 = !DILocation(line: 1436, column: 2, scope: !1501)
!1503 = !DILocation(line: 1436, column: 2, scope: !1504)
!1504 = !DILexicalBlockFile(scope: !1501, file: !1, discriminator: 1)
!1505 = !DILocation(line: 1436, column: 2, scope: !1506)
!1506 = !DILexicalBlockFile(scope: !1507, file: !1, discriminator: 2)
!1507 = distinct !DILexicalBlock(scope: !1501, file: !1, line: 1436, column: 2)
!1508 = !DILocation(line: 1436, column: 2, scope: !1509)
!1509 = !DILexicalBlockFile(scope: !1501, file: !1, discriminator: 3)
!1510 = !DILocation(line: 1439, column: 10, scope: !370)
!1511 = !DILocation(line: 1439, column: 13, scope: !370)
!1512 = !DILocation(line: 1439, column: 19, scope: !370)
!1513 = !DILocation(line: 1439, column: 39, scope: !370)
!1514 = !DILocation(line: 1439, column: 2, scope: !370)
!1515 = !DILocation(line: 1440, column: 1, scope: !370)
!1516 = !DILocalVariable(name: "_a", arg: 1, scope: !374, file: !1, line: 476, type: !63)
!1517 = !DILocation(line: 476, column: 36, scope: !374)
!1518 = !DILocalVariable(name: "a", scope: !374, file: !1, line: 478, type: !43)
!1519 = !DILocation(line: 478, column: 28, scope: !374)
!1520 = !DILocation(line: 478, column: 60, scope: !374)
!1521 = !DILocation(line: 478, column: 32, scope: !374)
!1522 = !DILocalVariable(name: "r", scope: !374, file: !1, line: 479, type: !62)
!1523 = !DILocation(line: 479, column: 6, scope: !374)
!1524 = !DILocation(line: 481, column: 6, scope: !1525)
!1525 = distinct !DILexicalBlock(scope: !374, file: !1, line: 481, column: 6)
!1526 = !DILocation(line: 481, column: 9, scope: !1525)
!1527 = !DILocation(line: 481, column: 6, scope: !374)
!1528 = !DILocation(line: 482, column: 3, scope: !1525)
!1529 = !DILocation(line: 483, column: 2, scope: !374)
!1530 = !DILocalVariable(name: "magic_test", scope: !1531, file: !1, line: 483, type: !62)
!1531 = distinct !DILexicalBlock(scope: !374, file: !1, line: 483, column: 2)
!1532 = !DILocation(line: 483, column: 2, scope: !1531)
!1533 = !DILocation(line: 483, column: 2, scope: !1534)
!1534 = !DILexicalBlockFile(scope: !1531, file: !1, discriminator: 1)
!1535 = !DILocation(line: 483, column: 2, scope: !1536)
!1536 = !DILexicalBlockFile(scope: !1537, file: !1, discriminator: 2)
!1537 = distinct !DILexicalBlock(scope: !1531, file: !1, line: 483, column: 2)
!1538 = !DILocation(line: 483, column: 2, scope: !1539)
!1539 = !DILexicalBlockFile(scope: !1531, file: !1, discriminator: 3)
!1540 = !DILocation(line: 486, column: 6, scope: !1541)
!1541 = distinct !DILexicalBlock(scope: !374, file: !1, line: 486, column: 6)
!1542 = !DILocation(line: 486, column: 9, scope: !1541)
!1543 = !DILocation(line: 486, column: 17, scope: !1541)
!1544 = !DILocation(line: 486, column: 23, scope: !1541)
!1545 = !DILocation(line: 486, column: 6, scope: !374)
!1546 = !DILocation(line: 487, column: 28, scope: !1541)
!1547 = !DILocation(line: 487, column: 31, scope: !1541)
!1548 = !DILocation(line: 487, column: 7, scope: !1541)
!1549 = !DILocation(line: 487, column: 5, scope: !1541)
!1550 = !DILocation(line: 487, column: 3, scope: !1541)
!1551 = !DILocation(line: 489, column: 5, scope: !1541)
!1552 = !DILocation(line: 491, column: 12, scope: !374)
!1553 = !DILocation(line: 491, column: 15, scope: !374)
!1554 = !DILocation(line: 491, column: 2, scope: !374)
!1555 = !DILocation(line: 492, column: 6, scope: !1556)
!1556 = distinct !DILexicalBlock(scope: !374, file: !1, line: 492, column: 6)
!1557 = !DILocation(line: 492, column: 9, scope: !1556)
!1558 = !DILocation(line: 492, column: 23, scope: !1556)
!1559 = !DILocation(line: 492, column: 31, scope: !1556)
!1560 = !DILocation(line: 492, column: 34, scope: !1561)
!1561 = !DILexicalBlockFile(scope: !1556, file: !1, discriminator: 1)
!1562 = !DILocation(line: 492, column: 37, scope: !1561)
!1563 = !DILocation(line: 492, column: 55, scope: !1561)
!1564 = !DILocation(line: 492, column: 6, scope: !1561)
!1565 = !DILocation(line: 493, column: 4, scope: !1556)
!1566 = !DILocation(line: 493, column: 7, scope: !1556)
!1567 = !DILocation(line: 493, column: 22, scope: !1556)
!1568 = !DILocation(line: 493, column: 25, scope: !1556)
!1569 = !DILocation(line: 493, column: 3, scope: !1556)
!1570 = !DILocation(line: 494, column: 6, scope: !1571)
!1571 = distinct !DILexicalBlock(scope: !374, file: !1, line: 494, column: 6)
!1572 = !DILocation(line: 494, column: 9, scope: !1571)
!1573 = !DILocation(line: 494, column: 23, scope: !1571)
!1574 = !DILocation(line: 494, column: 31, scope: !1571)
!1575 = !DILocation(line: 494, column: 34, scope: !1576)
!1576 = !DILexicalBlockFile(scope: !1571, file: !1, discriminator: 1)
!1577 = !DILocation(line: 494, column: 37, scope: !1576)
!1578 = !DILocation(line: 494, column: 55, scope: !1576)
!1579 = !DILocation(line: 494, column: 6, scope: !1576)
!1580 = !DILocation(line: 495, column: 4, scope: !1571)
!1581 = !DILocation(line: 495, column: 7, scope: !1571)
!1582 = !DILocation(line: 495, column: 22, scope: !1571)
!1583 = !DILocation(line: 495, column: 25, scope: !1571)
!1584 = !DILocation(line: 495, column: 3, scope: !1571)
!1585 = !DILocation(line: 496, column: 23, scope: !374)
!1586 = !DILocation(line: 496, column: 26, scope: !374)
!1587 = !DILocation(line: 496, column: 34, scope: !374)
!1588 = !DILocation(line: 496, column: 2, scope: !374)
!1589 = !DILocation(line: 497, column: 21, scope: !374)
!1590 = !DILocation(line: 497, column: 24, scope: !374)
!1591 = !DILocation(line: 497, column: 2, scope: !374)
!1592 = !DILocation(line: 498, column: 2, scope: !374)
!1593 = !DILocation(line: 498, column: 5, scope: !374)
!1594 = !DILocation(line: 498, column: 13, scope: !374)
!1595 = !DILocation(line: 498, column: 19, scope: !374)
!1596 = !DILocation(line: 499, column: 19, scope: !374)
!1597 = !DILocation(line: 499, column: 22, scope: !374)
!1598 = !DILocation(line: 499, column: 2, scope: !374)
!1599 = !DILocation(line: 500, column: 7, scope: !374)
!1600 = !DILocation(line: 500, column: 2, scope: !374)
!1601 = !DILocation(line: 501, column: 10, scope: !374)
!1602 = !DILocation(line: 501, column: 2, scope: !374)
!1603 = !DILocation(line: 502, column: 1, scope: !374)
!1604 = !DILocalVariable(name: "_a", arg: 1, scope: !378, file: !1, line: 505, type: !63)
!1605 = !DILocation(line: 505, column: 37, scope: !378)
!1606 = !DILocalVariable(name: "a", scope: !378, file: !1, line: 507, type: !43)
!1607 = !DILocation(line: 507, column: 28, scope: !378)
!1608 = !DILocation(line: 507, column: 60, scope: !378)
!1609 = !DILocation(line: 507, column: 32, scope: !378)
!1610 = !DILocation(line: 509, column: 2, scope: !378)
!1611 = !DILocalVariable(name: "magic_test", scope: !1612, file: !1, line: 509, type: !62)
!1612 = distinct !DILexicalBlock(scope: !378, file: !1, line: 509, column: 2)
!1613 = !DILocation(line: 509, column: 2, scope: !1612)
!1614 = !DILocation(line: 509, column: 2, scope: !1615)
!1615 = !DILexicalBlockFile(scope: !1612, file: !1, discriminator: 1)
!1616 = !DILocation(line: 509, column: 2, scope: !1617)
!1617 = !DILexicalBlockFile(scope: !1618, file: !1, discriminator: 2)
!1618 = distinct !DILexicalBlock(scope: !1612, file: !1, line: 509, column: 2)
!1619 = !DILocation(line: 509, column: 2, scope: !1620)
!1620 = !DILexicalBlockFile(scope: !1612, file: !1, discriminator: 3)
!1621 = !DILocation(line: 512, column: 6, scope: !1622)
!1622 = distinct !DILexicalBlock(scope: !378, file: !1, line: 512, column: 6)
!1623 = !DILocation(line: 512, column: 9, scope: !1622)
!1624 = !DILocation(line: 512, column: 17, scope: !1622)
!1625 = !DILocation(line: 512, column: 23, scope: !1622)
!1626 = !DILocation(line: 512, column: 6, scope: !378)
!1627 = !DILocation(line: 513, column: 3, scope: !1622)
!1628 = !DILocation(line: 513, column: 6, scope: !1622)
!1629 = !DILocation(line: 513, column: 14, scope: !1622)
!1630 = !DILocation(line: 513, column: 20, scope: !1622)
!1631 = !DILocation(line: 515, column: 13, scope: !378)
!1632 = !DILocation(line: 515, column: 16, scope: !378)
!1633 = !DILocation(line: 515, column: 2, scope: !378)
!1634 = !DILocation(line: 517, column: 2, scope: !378)
!1635 = !DILocation(line: 518, column: 1, scope: !378)
!1636 = !DILocalVariable(name: "_a", arg: 1, scope: !385, file: !1, line: 690, type: !63)
!1637 = !DILocation(line: 690, column: 42, scope: !385)
!1638 = !DILocalVariable(name: "buff", arg: 2, scope: !385, file: !1, line: 690, type: !103)
!1639 = !DILocation(line: 690, column: 59, scope: !385)
!1640 = !DILocalVariable(name: "size", arg: 3, scope: !385, file: !1, line: 691, type: !104)
!1641 = !DILocation(line: 691, column: 13, scope: !385)
!1642 = !DILocalVariable(name: "offset", arg: 4, scope: !385, file: !1, line: 691, type: !105)
!1643 = !DILocation(line: 691, column: 28, scope: !385)
!1644 = !DILocalVariable(name: "a", scope: !385, file: !1, line: 693, type: !43)
!1645 = !DILocation(line: 693, column: 28, scope: !385)
!1646 = !DILocation(line: 693, column: 60, scope: !385)
!1647 = !DILocation(line: 693, column: 32, scope: !385)
!1648 = !DILocalVariable(name: "t", scope: !385, file: !1, line: 694, type: !153)
!1649 = !DILocation(line: 694, column: 15, scope: !385)
!1650 = !DILocation(line: 694, column: 19, scope: !385)
!1651 = !DILocation(line: 694, column: 22, scope: !385)
!1652 = !DILocalVariable(name: "r", scope: !385, file: !1, line: 695, type: !62)
!1653 = !DILocation(line: 695, column: 6, scope: !385)
!1654 = !DILocalVariable(name: "bytes", scope: !385, file: !1, line: 696, type: !77)
!1655 = !DILocation(line: 696, column: 10, scope: !385)
!1656 = !DILocalVariable(name: "buffbytes", scope: !385, file: !1, line: 697, type: !84)
!1657 = !DILocation(line: 697, column: 9, scope: !385)
!1658 = !DILocalVariable(name: "empty_sparse_region", scope: !385, file: !1, line: 698, type: !62)
!1659 = !DILocation(line: 698, column: 6, scope: !385)
!1660 = !DILocation(line: 700, column: 2, scope: !385)
!1661 = !DILocalVariable(name: "magic_test", scope: !1662, file: !1, line: 700, type: !62)
!1662 = distinct !DILexicalBlock(scope: !385, file: !1, line: 700, column: 2)
!1663 = !DILocation(line: 700, column: 2, scope: !1662)
!1664 = !DILocation(line: 700, column: 2, scope: !1665)
!1665 = !DILexicalBlockFile(scope: !1662, file: !1, discriminator: 1)
!1666 = !DILocation(line: 700, column: 2, scope: !1667)
!1667 = !DILexicalBlockFile(scope: !1668, file: !1, discriminator: 2)
!1668 = distinct !DILexicalBlock(scope: !1662, file: !1, line: 700, column: 2)
!1669 = !DILocation(line: 700, column: 2, scope: !1670)
!1670 = !DILexicalBlockFile(scope: !1662, file: !1, discriminator: 3)
!1671 = !DILocation(line: 703, column: 6, scope: !1672)
!1672 = distinct !DILexicalBlock(scope: !385, file: !1, line: 703, column: 6)
!1673 = !DILocation(line: 703, column: 9, scope: !1672)
!1674 = !DILocation(line: 703, column: 19, scope: !1672)
!1675 = !DILocation(line: 703, column: 22, scope: !1676)
!1676 = !DILexicalBlockFile(scope: !1672, file: !1, discriminator: 1)
!1677 = !DILocation(line: 703, column: 25, scope: !1676)
!1678 = !DILocation(line: 703, column: 47, scope: !1676)
!1679 = !DILocation(line: 703, column: 6, scope: !1676)
!1680 = !DILocation(line: 704, column: 5, scope: !1681)
!1681 = distinct !DILexicalBlock(scope: !1672, file: !1, line: 703, column: 53)
!1682 = !DILocation(line: 705, column: 3, scope: !1681)
!1683 = !DILocation(line: 711, column: 6, scope: !1684)
!1684 = distinct !DILexicalBlock(scope: !385, file: !1, line: 711, column: 6)
!1685 = !DILocation(line: 711, column: 9, scope: !1684)
!1686 = !DILocation(line: 711, column: 18, scope: !1684)
!1687 = !DILocation(line: 711, column: 6, scope: !385)
!1688 = !DILocalVariable(name: "flags", scope: !1689, file: !1, line: 712, type: !62)
!1689 = distinct !DILexicalBlock(scope: !1684, file: !1, line: 711, column: 23)
!1690 = !DILocation(line: 712, column: 7, scope: !1689)
!1691 = !DILocation(line: 728, column: 8, scope: !1692)
!1692 = distinct !DILexicalBlock(scope: !1689, file: !1, line: 728, column: 7)
!1693 = !DILocation(line: 728, column: 11, scope: !1692)
!1694 = !DILocation(line: 728, column: 17, scope: !1692)
!1695 = !DILocation(line: 728, column: 38, scope: !1692)
!1696 = !DILocation(line: 728, column: 43, scope: !1692)
!1697 = !DILocation(line: 729, column: 7, scope: !1692)
!1698 = !DILocation(line: 729, column: 10, scope: !1692)
!1699 = !DILocation(line: 729, column: 23, scope: !1692)
!1700 = !DILocation(line: 729, column: 31, scope: !1692)
!1701 = !DILocation(line: 728, column: 7, scope: !1702)
!1702 = !DILexicalBlockFile(scope: !1689, file: !1, discriminator: 1)
!1703 = !DILocation(line: 730, column: 10, scope: !1692)
!1704 = !DILocation(line: 730, column: 4, scope: !1692)
!1705 = !DILocation(line: 731, column: 3, scope: !1689)
!1706 = !DILocation(line: 733, column: 38, scope: !1707)
!1707 = distinct !DILexicalBlock(scope: !1689, file: !1, line: 731, column: 6)
!1708 = !DILocation(line: 734, column: 33, scope: !1707)
!1709 = !DILocation(line: 734, column: 8, scope: !1707)
!1710 = !DILocation(line: 734, column: 37, scope: !1707)
!1711 = !DILocation(line: 733, column: 18, scope: !1707)
!1712 = !DILocation(line: 733, column: 4, scope: !1707)
!1713 = !DILocation(line: 733, column: 7, scope: !1707)
!1714 = !DILocation(line: 733, column: 16, scope: !1707)
!1715 = !DILocation(line: 735, column: 34, scope: !1707)
!1716 = !DILocation(line: 735, column: 37, scope: !1707)
!1717 = !DILocation(line: 735, column: 4, scope: !1707)
!1718 = !DILocation(line: 743, column: 8, scope: !1719)
!1719 = distinct !DILexicalBlock(scope: !1707, file: !1, line: 743, column: 8)
!1720 = !DILocation(line: 743, column: 14, scope: !1719)
!1721 = !DILocation(line: 743, column: 8, scope: !1707)
!1722 = !DILocation(line: 744, column: 9, scope: !1723)
!1723 = distinct !DILexicalBlock(scope: !1724, file: !1, line: 744, column: 9)
!1724 = distinct !DILexicalBlock(scope: !1719, file: !1, line: 743, column: 27)
!1725 = !DILocation(line: 744, column: 12, scope: !1723)
!1726 = !DILocation(line: 744, column: 21, scope: !1723)
!1727 = !DILocation(line: 744, column: 9, scope: !1724)
!1728 = !DILocation(line: 745, column: 6, scope: !1723)
!1729 = !DILocation(line: 745, column: 9, scope: !1723)
!1730 = !DILocation(line: 745, column: 22, scope: !1723)
!1731 = !DILocation(line: 745, column: 30, scope: !1723)
!1732 = !DILocation(line: 746, column: 14, scope: !1733)
!1733 = distinct !DILexicalBlock(scope: !1723, file: !1, line: 746, column: 14)
!1734 = !DILocation(line: 746, column: 20, scope: !1733)
!1735 = !DILocation(line: 746, column: 14, scope: !1723)
!1736 = !DILocation(line: 747, column: 12, scope: !1737)
!1737 = distinct !DILexicalBlock(scope: !1733, file: !1, line: 746, column: 30)
!1738 = !DILocation(line: 748, column: 6, scope: !1737)
!1739 = !DILocation(line: 750, column: 4, scope: !1724)
!1740 = !DILocation(line: 751, column: 3, scope: !1707)
!1741 = !DILocation(line: 753, column: 7, scope: !1742)
!1742 = distinct !DILexicalBlock(scope: !1689, file: !1, line: 753, column: 7)
!1743 = !DILocation(line: 753, column: 10, scope: !1742)
!1744 = !DILocation(line: 753, column: 19, scope: !1742)
!1745 = !DILocation(line: 753, column: 7, scope: !1689)
!1746 = !DILocation(line: 754, column: 23, scope: !1747)
!1747 = distinct !DILexicalBlock(scope: !1742, file: !1, line: 753, column: 24)
!1748 = !DILocation(line: 754, column: 26, scope: !1747)
!1749 = !DILocation(line: 754, column: 35, scope: !1747)
!1750 = !DILocation(line: 755, column: 46, scope: !1747)
!1751 = !DILocation(line: 755, column: 28, scope: !1747)
!1752 = !DILocation(line: 754, column: 4, scope: !1747)
!1753 = !DILocation(line: 756, column: 6, scope: !1747)
!1754 = !DILocation(line: 757, column: 27, scope: !1747)
!1755 = !DILocation(line: 757, column: 4, scope: !1747)
!1756 = !DILocation(line: 758, column: 4, scope: !1747)
!1757 = !DILocation(line: 760, column: 26, scope: !1689)
!1758 = !DILocation(line: 760, column: 3, scope: !1689)
!1759 = !DILocation(line: 761, column: 2, scope: !1689)
!1760 = !DILocation(line: 766, column: 6, scope: !1761)
!1761 = distinct !DILexicalBlock(scope: !385, file: !1, line: 766, column: 6)
!1762 = !DILocation(line: 766, column: 9, scope: !1761)
!1763 = !DILocation(line: 766, column: 29, scope: !1761)
!1764 = !DILocation(line: 766, column: 44, scope: !1761)
!1765 = !DILocation(line: 766, column: 6, scope: !385)
!1766 = !DILocation(line: 767, column: 34, scope: !1767)
!1767 = distinct !DILexicalBlock(scope: !1761, file: !1, line: 766, column: 53)
!1768 = !DILocation(line: 767, column: 7, scope: !1767)
!1769 = !DILocation(line: 767, column: 5, scope: !1767)
!1770 = !DILocation(line: 768, column: 7, scope: !1771)
!1771 = distinct !DILexicalBlock(scope: !1767, file: !1, line: 768, column: 7)
!1772 = !DILocation(line: 768, column: 9, scope: !1771)
!1773 = !DILocation(line: 768, column: 7, scope: !1767)
!1774 = !DILocation(line: 769, column: 4, scope: !1775)
!1775 = distinct !DILexicalBlock(scope: !1771, file: !1, line: 768, column: 24)
!1776 = !DILocation(line: 769, column: 7, scope: !1775)
!1777 = !DILocation(line: 769, column: 15, scope: !1775)
!1778 = !DILocation(line: 769, column: 21, scope: !1775)
!1779 = !DILocation(line: 770, column: 4, scope: !1775)
!1780 = !DILocation(line: 772, column: 2, scope: !1767)
!1781 = !DILocation(line: 773, column: 18, scope: !385)
!1782 = !DILocation(line: 773, column: 21, scope: !385)
!1783 = !DILocation(line: 773, column: 41, scope: !385)
!1784 = !DILocation(line: 773, column: 2, scope: !385)
!1785 = !DILocation(line: 773, column: 5, scope: !385)
!1786 = !DILocation(line: 773, column: 16, scope: !385)
!1787 = !DILocation(line: 774, column: 23, scope: !385)
!1788 = !DILocation(line: 774, column: 26, scope: !385)
!1789 = !DILocation(line: 774, column: 46, scope: !385)
!1790 = !DILocation(line: 774, column: 2, scope: !385)
!1791 = !DILocation(line: 774, column: 5, scope: !385)
!1792 = !DILocation(line: 774, column: 21, scope: !385)
!1793 = !DILocation(line: 776, column: 14, scope: !385)
!1794 = !DILocation(line: 776, column: 17, scope: !385)
!1795 = !DILocation(line: 776, column: 12, scope: !385)
!1796 = !DILocation(line: 777, column: 15, scope: !1797)
!1797 = distinct !DILexicalBlock(scope: !385, file: !1, line: 777, column: 6)
!1798 = !DILocation(line: 777, column: 27, scope: !1797)
!1799 = !DILocation(line: 777, column: 30, scope: !1797)
!1800 = !DILocation(line: 777, column: 46, scope: !1797)
!1801 = !DILocation(line: 777, column: 25, scope: !1797)
!1802 = !DILocation(line: 777, column: 6, scope: !385)
!1803 = !DILocation(line: 778, column: 15, scope: !1797)
!1804 = !DILocation(line: 778, column: 18, scope: !1797)
!1805 = !DILocation(line: 778, column: 34, scope: !1797)
!1806 = !DILocation(line: 778, column: 13, scope: !1797)
!1807 = !DILocation(line: 778, column: 3, scope: !1797)
!1808 = !DILocation(line: 780, column: 6, scope: !1809)
!1809 = distinct !DILexicalBlock(scope: !385, file: !1, line: 780, column: 6)
!1810 = !DILocation(line: 780, column: 9, scope: !1809)
!1811 = !DILocation(line: 780, column: 25, scope: !1809)
!1812 = !DILocation(line: 780, column: 32, scope: !1809)
!1813 = !DILocation(line: 780, column: 6, scope: !385)
!1814 = !DILocation(line: 781, column: 23, scope: !1809)
!1815 = !DILocation(line: 781, column: 3, scope: !1809)
!1816 = !DILocation(line: 787, column: 6, scope: !1817)
!1817 = distinct !DILexicalBlock(scope: !385, file: !1, line: 787, column: 6)
!1818 = !DILocation(line: 787, column: 9, scope: !1817)
!1819 = !DILocation(line: 787, column: 25, scope: !1817)
!1820 = !DILocation(line: 787, column: 34, scope: !1817)
!1821 = !DILocation(line: 787, column: 37, scope: !1817)
!1822 = !DILocation(line: 787, column: 32, scope: !1817)
!1823 = !DILocation(line: 787, column: 6, scope: !385)
!1824 = !DILocation(line: 788, column: 13, scope: !1825)
!1825 = distinct !DILexicalBlock(scope: !1826, file: !1, line: 788, column: 7)
!1826 = distinct !DILexicalBlock(scope: !1817, file: !1, line: 787, column: 50)
!1827 = !DILocation(line: 788, column: 16, scope: !1825)
!1828 = !DILocation(line: 789, column: 14, scope: !1825)
!1829 = !DILocation(line: 789, column: 17, scope: !1825)
!1830 = !DILocation(line: 789, column: 33, scope: !1825)
!1831 = !DILocation(line: 788, column: 7, scope: !1825)
!1832 = !DILocation(line: 789, column: 51, scope: !1825)
!1833 = !DILocation(line: 788, column: 7, scope: !1826)
!1834 = !DILocation(line: 790, column: 23, scope: !1835)
!1835 = distinct !DILexicalBlock(scope: !1825, file: !1, line: 789, column: 56)
!1836 = !DILocation(line: 790, column: 26, scope: !1835)
!1837 = !DILocation(line: 790, column: 35, scope: !1835)
!1838 = !DILocation(line: 790, column: 4, scope: !1839)
!1839 = !DILexicalBlockFile(scope: !1835, file: !1, discriminator: 1)
!1840 = !DILocation(line: 791, column: 6, scope: !1835)
!1841 = !DILocation(line: 792, column: 4, scope: !1835)
!1842 = !DILocation(line: 792, column: 7, scope: !1835)
!1843 = !DILocation(line: 792, column: 15, scope: !1835)
!1844 = !DILocation(line: 792, column: 21, scope: !1835)
!1845 = !DILocation(line: 793, column: 4, scope: !1835)
!1846 = !DILocation(line: 795, column: 11, scope: !1826)
!1847 = !DILocation(line: 795, column: 14, scope: !1826)
!1848 = !DILocation(line: 795, column: 30, scope: !1826)
!1849 = !DILocation(line: 795, column: 39, scope: !1826)
!1850 = !DILocation(line: 795, column: 42, scope: !1826)
!1851 = !DILocation(line: 795, column: 37, scope: !1826)
!1852 = !DILocation(line: 795, column: 9, scope: !1826)
!1853 = !DILocation(line: 796, column: 31, scope: !1826)
!1854 = !DILocation(line: 796, column: 3, scope: !1826)
!1855 = !DILocation(line: 796, column: 6, scope: !1826)
!1856 = !DILocation(line: 796, column: 28, scope: !1826)
!1857 = !DILocation(line: 797, column: 21, scope: !1826)
!1858 = !DILocation(line: 797, column: 3, scope: !1826)
!1859 = !DILocation(line: 797, column: 6, scope: !1826)
!1860 = !DILocation(line: 797, column: 18, scope: !1826)
!1861 = !DILocation(line: 798, column: 2, scope: !1826)
!1862 = !DILocation(line: 803, column: 6, scope: !1863)
!1863 = distinct !DILexicalBlock(scope: !385, file: !1, line: 803, column: 6)
!1864 = !DILocation(line: 803, column: 16, scope: !1863)
!1865 = !DILocation(line: 803, column: 6, scope: !385)
!1866 = !DILocation(line: 804, column: 16, scope: !1867)
!1867 = distinct !DILexicalBlock(scope: !1863, file: !1, line: 803, column: 21)
!1868 = !DILocation(line: 804, column: 19, scope: !1867)
!1869 = !DILocation(line: 804, column: 29, scope: !1867)
!1870 = !DILocation(line: 804, column: 32, scope: !1867)
!1871 = !DILocation(line: 804, column: 44, scope: !1867)
!1872 = !DILocation(line: 804, column: 11, scope: !1867)
!1873 = !DILocation(line: 804, column: 9, scope: !1867)
!1874 = !DILocation(line: 805, column: 7, scope: !1875)
!1875 = distinct !DILexicalBlock(scope: !1867, file: !1, line: 805, column: 7)
!1876 = !DILocation(line: 805, column: 13, scope: !1875)
!1877 = !DILocation(line: 805, column: 7, scope: !1867)
!1878 = !DILocation(line: 806, column: 23, scope: !1879)
!1879 = distinct !DILexicalBlock(scope: !1875, file: !1, line: 805, column: 18)
!1880 = !DILocation(line: 806, column: 26, scope: !1879)
!1881 = !DILocation(line: 806, column: 35, scope: !1879)
!1882 = !DILocation(line: 806, column: 4, scope: !1883)
!1883 = !DILexicalBlockFile(scope: !1879, file: !1, discriminator: 1)
!1884 = !DILocation(line: 807, column: 6, scope: !1879)
!1885 = !DILocation(line: 808, column: 4, scope: !1879)
!1886 = !DILocation(line: 808, column: 7, scope: !1879)
!1887 = !DILocation(line: 808, column: 15, scope: !1879)
!1888 = !DILocation(line: 808, column: 21, scope: !1879)
!1889 = !DILocation(line: 809, column: 4, scope: !1879)
!1890 = !DILocation(line: 811, column: 2, scope: !1867)
!1891 = !DILocation(line: 812, column: 9, scope: !1863)
!1892 = !DILocation(line: 817, column: 6, scope: !1893)
!1893 = distinct !DILexicalBlock(scope: !385, file: !1, line: 817, column: 6)
!1894 = !DILocation(line: 817, column: 12, scope: !1893)
!1895 = !DILocation(line: 817, column: 17, scope: !1893)
!1896 = !DILocation(line: 817, column: 21, scope: !1897)
!1897 = !DILexicalBlockFile(scope: !1893, file: !1, discriminator: 1)
!1898 = !DILocation(line: 817, column: 6, scope: !1897)
!1899 = !DILocation(line: 819, column: 3, scope: !1900)
!1900 = distinct !DILexicalBlock(scope: !1893, file: !1, line: 817, column: 42)
!1901 = !DILocation(line: 819, column: 6, scope: !1900)
!1902 = !DILocation(line: 819, column: 16, scope: !1900)
!1903 = !DILocation(line: 820, column: 5, scope: !1900)
!1904 = !DILocation(line: 821, column: 3, scope: !1900)
!1905 = !DILocation(line: 823, column: 10, scope: !385)
!1906 = !DILocation(line: 823, column: 13, scope: !385)
!1907 = !DILocation(line: 823, column: 3, scope: !385)
!1908 = !DILocation(line: 823, column: 8, scope: !385)
!1909 = !DILocation(line: 824, column: 10, scope: !385)
!1910 = !DILocation(line: 824, column: 3, scope: !385)
!1911 = !DILocation(line: 824, column: 8, scope: !385)
!1912 = !DILocation(line: 825, column: 12, scope: !385)
!1913 = !DILocation(line: 825, column: 15, scope: !385)
!1914 = !DILocation(line: 825, column: 3, scope: !385)
!1915 = !DILocation(line: 825, column: 10, scope: !385)
!1916 = !DILocation(line: 826, column: 20, scope: !385)
!1917 = !DILocation(line: 826, column: 2, scope: !385)
!1918 = !DILocation(line: 826, column: 5, scope: !385)
!1919 = !DILocation(line: 826, column: 17, scope: !385)
!1920 = !DILocation(line: 827, column: 30, scope: !385)
!1921 = !DILocation(line: 827, column: 2, scope: !385)
!1922 = !DILocation(line: 827, column: 5, scope: !385)
!1923 = !DILocation(line: 827, column: 27, scope: !385)
!1924 = !DILocation(line: 828, column: 6, scope: !1925)
!1925 = distinct !DILexicalBlock(scope: !385, file: !1, line: 828, column: 6)
!1926 = !DILocation(line: 828, column: 9, scope: !1925)
!1927 = !DILocation(line: 828, column: 31, scope: !1925)
!1928 = !DILocation(line: 828, column: 6, scope: !385)
!1929 = !DILocation(line: 830, column: 26, scope: !1930)
!1930 = distinct !DILexicalBlock(scope: !1925, file: !1, line: 828, column: 37)
!1931 = !DILocation(line: 830, column: 29, scope: !1930)
!1932 = !DILocation(line: 830, column: 39, scope: !1930)
!1933 = !DILocation(line: 830, column: 43, scope: !1930)
!1934 = !DILocation(line: 830, column: 46, scope: !1930)
!1935 = !DILocation(line: 830, column: 3, scope: !1930)
!1936 = !DILocation(line: 831, column: 3, scope: !1930)
!1937 = !DILocation(line: 831, column: 6, scope: !1930)
!1938 = !DILocation(line: 831, column: 15, scope: !1930)
!1939 = !DILocation(line: 832, column: 3, scope: !1930)
!1940 = !DILocation(line: 832, column: 6, scope: !1930)
!1941 = !DILocation(line: 832, column: 16, scope: !1930)
!1942 = !DILocation(line: 833, column: 2, scope: !1930)
!1943 = !DILocation(line: 834, column: 31, scope: !385)
!1944 = !DILocation(line: 834, column: 2, scope: !385)
!1945 = !DILocation(line: 834, column: 5, scope: !385)
!1946 = !DILocation(line: 834, column: 21, scope: !385)
!1947 = !DILocation(line: 834, column: 28, scope: !385)
!1948 = !DILocation(line: 835, column: 31, scope: !385)
!1949 = !DILocation(line: 835, column: 2, scope: !385)
!1950 = !DILocation(line: 835, column: 5, scope: !385)
!1951 = !DILocation(line: 835, column: 21, scope: !385)
!1952 = !DILocation(line: 835, column: 28, scope: !385)
!1953 = !DILocation(line: 836, column: 6, scope: !1954)
!1954 = distinct !DILexicalBlock(scope: !385, file: !1, line: 836, column: 6)
!1955 = !DILocation(line: 836, column: 9, scope: !1954)
!1956 = !DILocation(line: 836, column: 25, scope: !1954)
!1957 = !DILocation(line: 836, column: 32, scope: !1954)
!1958 = !DILocation(line: 836, column: 37, scope: !1954)
!1959 = !DILocation(line: 836, column: 41, scope: !1960)
!1960 = !DILexicalBlockFile(scope: !1954, file: !1, discriminator: 1)
!1961 = !DILocation(line: 836, column: 44, scope: !1960)
!1962 = !DILocation(line: 836, column: 6, scope: !1960)
!1963 = !DILocation(line: 837, column: 3, scope: !1954)
!1964 = !DILocation(line: 837, column: 6, scope: !1954)
!1965 = !DILocation(line: 837, column: 20, scope: !1954)
!1966 = !DILocation(line: 838, column: 2, scope: !385)
!1967 = !DILocation(line: 841, column: 3, scope: !385)
!1968 = !DILocation(line: 841, column: 8, scope: !385)
!1969 = !DILocation(line: 842, column: 3, scope: !385)
!1970 = !DILocation(line: 842, column: 8, scope: !385)
!1971 = !DILocation(line: 843, column: 12, scope: !385)
!1972 = !DILocation(line: 843, column: 15, scope: !385)
!1973 = !DILocation(line: 843, column: 3, scope: !385)
!1974 = !DILocation(line: 843, column: 10, scope: !385)
!1975 = !DILocation(line: 844, column: 6, scope: !1976)
!1976 = distinct !DILexicalBlock(scope: !385, file: !1, line: 844, column: 6)
!1977 = !DILocation(line: 844, column: 9, scope: !1976)
!1978 = !DILocation(line: 844, column: 18, scope: !1976)
!1979 = !DILocation(line: 844, column: 6, scope: !385)
!1980 = !DILocation(line: 846, column: 26, scope: !1981)
!1981 = distinct !DILexicalBlock(scope: !1976, file: !1, line: 844, column: 24)
!1982 = !DILocation(line: 846, column: 29, scope: !1981)
!1983 = !DILocation(line: 846, column: 39, scope: !1981)
!1984 = !DILocation(line: 846, column: 43, scope: !1981)
!1985 = !DILocation(line: 846, column: 46, scope: !1981)
!1986 = !DILocation(line: 846, column: 3, scope: !1981)
!1987 = !DILocation(line: 847, column: 3, scope: !1981)
!1988 = !DILocation(line: 847, column: 6, scope: !1981)
!1989 = !DILocation(line: 847, column: 15, scope: !1981)
!1990 = !DILocation(line: 848, column: 2, scope: !1981)
!1991 = !DILocation(line: 849, column: 10, scope: !385)
!1992 = !DILocation(line: 849, column: 2, scope: !385)
!1993 = !DILocation(line: 850, column: 1, scope: !385)
!1994 = !DILocalVariable(name: "_a", arg: 1, scope: !394, file: !1, line: 1090, type: !63)
!1995 = !DILocation(line: 1090, column: 43, scope: !394)
!1996 = !DILocalVariable(name: "entryp", arg: 2, scope: !394, file: !1, line: 1090, type: !97)
!1997 = !DILocation(line: 1090, column: 70, scope: !394)
!1998 = !DILocalVariable(name: "ret", scope: !394, file: !1, line: 1092, type: !62)
!1999 = !DILocation(line: 1092, column: 6, scope: !394)
!2000 = !DILocalVariable(name: "a", scope: !394, file: !1, line: 1093, type: !43)
!2001 = !DILocation(line: 1093, column: 28, scope: !394)
!2002 = !DILocation(line: 1093, column: 60, scope: !394)
!2003 = !DILocation(line: 1093, column: 32, scope: !394)
!2004 = !DILocation(line: 1094, column: 3, scope: !394)
!2005 = !DILocation(line: 1094, column: 10, scope: !394)
!2006 = !DILocation(line: 1095, column: 35, scope: !394)
!2007 = !DILocation(line: 1095, column: 39, scope: !394)
!2008 = !DILocation(line: 1095, column: 42, scope: !394)
!2009 = !DILocation(line: 1095, column: 8, scope: !394)
!2010 = !DILocation(line: 1095, column: 6, scope: !394)
!2011 = !DILocation(line: 1096, column: 12, scope: !394)
!2012 = !DILocation(line: 1096, column: 15, scope: !394)
!2013 = !DILocation(line: 1096, column: 3, scope: !394)
!2014 = !DILocation(line: 1096, column: 10, scope: !394)
!2015 = !DILocation(line: 1097, column: 9, scope: !394)
!2016 = !DILocation(line: 1097, column: 2, scope: !394)
!2017 = !DILocalVariable(name: "_a", arg: 1, scope: !395, file: !1, line: 1101, type: !63)
!2018 = !DILocation(line: 1101, column: 44, scope: !395)
!2019 = !DILocalVariable(name: "entry", arg: 2, scope: !395, file: !1, line: 1101, type: !69)
!2020 = !DILocation(line: 1101, column: 70, scope: !395)
!2021 = !DILocalVariable(name: "a", scope: !395, file: !1, line: 1103, type: !43)
!2022 = !DILocation(line: 1103, column: 28, scope: !395)
!2023 = !DILocation(line: 1103, column: 60, scope: !395)
!2024 = !DILocation(line: 1103, column: 32, scope: !395)
!2025 = !DILocalVariable(name: "t", scope: !395, file: !1, line: 1104, type: !153)
!2026 = !DILocation(line: 1104, column: 15, scope: !395)
!2027 = !DILocalVariable(name: "r", scope: !395, file: !1, line: 1105, type: !62)
!2028 = !DILocation(line: 1105, column: 6, scope: !395)
!2029 = !DILocation(line: 1107, column: 2, scope: !395)
!2030 = !DILocalVariable(name: "magic_test", scope: !2031, file: !1, line: 1107, type: !62)
!2031 = distinct !DILexicalBlock(scope: !395, file: !1, line: 1107, column: 2)
!2032 = !DILocation(line: 1107, column: 2, scope: !2031)
!2033 = !DILocation(line: 1107, column: 2, scope: !2034)
!2034 = !DILexicalBlockFile(scope: !2031, file: !1, discriminator: 1)
!2035 = !DILocation(line: 1107, column: 2, scope: !2036)
!2036 = !DILexicalBlockFile(scope: !2037, file: !1, discriminator: 2)
!2037 = distinct !DILexicalBlock(scope: !2031, file: !1, line: 1107, column: 2)
!2038 = !DILocation(line: 1107, column: 2, scope: !2039)
!2039 = !DILexicalBlockFile(scope: !2031, file: !1, discriminator: 3)
!2040 = !DILocation(line: 1111, column: 6, scope: !395)
!2041 = !DILocation(line: 1111, column: 9, scope: !395)
!2042 = !DILocation(line: 1111, column: 4, scope: !395)
!2043 = !DILocation(line: 1112, column: 6, scope: !2044)
!2044 = distinct !DILexicalBlock(scope: !395, file: !1, line: 1112, column: 6)
!2045 = !DILocation(line: 1112, column: 9, scope: !2044)
!2046 = !DILocation(line: 1112, column: 18, scope: !2044)
!2047 = !DILocation(line: 1112, column: 6, scope: !395)
!2048 = !DILocation(line: 1113, column: 26, scope: !2049)
!2049 = distinct !DILexicalBlock(scope: !2044, file: !1, line: 1112, column: 24)
!2050 = !DILocation(line: 1113, column: 29, scope: !2049)
!2051 = !DILocation(line: 1113, column: 39, scope: !2049)
!2052 = !DILocation(line: 1113, column: 43, scope: !2049)
!2053 = !DILocation(line: 1113, column: 46, scope: !2049)
!2054 = !DILocation(line: 1113, column: 3, scope: !2049)
!2055 = !DILocation(line: 1114, column: 3, scope: !2049)
!2056 = !DILocation(line: 1114, column: 6, scope: !2049)
!2057 = !DILocation(line: 1114, column: 15, scope: !2049)
!2058 = !DILocation(line: 1115, column: 2, scope: !2049)
!2059 = !DILocation(line: 1117, column: 2, scope: !395)
!2060 = !DILocation(line: 1118, column: 18, scope: !2061)
!2061 = distinct !DILexicalBlock(scope: !2062, file: !1, line: 1117, column: 11)
!2062 = distinct !DILexicalBlock(scope: !2063, file: !1, line: 1117, column: 2)
!2063 = distinct !DILexicalBlock(scope: !395, file: !1, line: 1117, column: 2)
!2064 = !DILocation(line: 1118, column: 21, scope: !2061)
!2065 = !DILocation(line: 1118, column: 24, scope: !2061)
!2066 = !DILocation(line: 1118, column: 7, scope: !2061)
!2067 = !DILocation(line: 1118, column: 5, scope: !2061)
!2068 = !DILocation(line: 1119, column: 7, scope: !2069)
!2069 = distinct !DILexicalBlock(scope: !2061, file: !1, line: 1119, column: 7)
!2070 = !DILocation(line: 1119, column: 10, scope: !2069)
!2071 = !DILocation(line: 1119, column: 19, scope: !2069)
!2072 = !DILocation(line: 1119, column: 7, scope: !2061)
!2073 = !DILocation(line: 1120, column: 10, scope: !2074)
!2074 = distinct !DILexicalBlock(scope: !2069, file: !1, line: 1119, column: 25)
!2075 = !DILocation(line: 1120, column: 13, scope: !2074)
!2076 = !DILocation(line: 1120, column: 4, scope: !2074)
!2077 = !DILocation(line: 1121, column: 4, scope: !2074)
!2078 = !DILocation(line: 1121, column: 7, scope: !2074)
!2079 = !DILocation(line: 1121, column: 16, scope: !2074)
!2080 = !DILocation(line: 1122, column: 3, scope: !2074)
!2081 = !DILocation(line: 1124, column: 7, scope: !2082)
!2082 = distinct !DILexicalBlock(scope: !2061, file: !1, line: 1124, column: 7)
!2083 = !DILocation(line: 1124, column: 9, scope: !2082)
!2084 = !DILocation(line: 1124, column: 7, scope: !2061)
!2085 = !DILocation(line: 1125, column: 24, scope: !2086)
!2086 = distinct !DILexicalBlock(scope: !2082, file: !1, line: 1124, column: 27)
!2087 = !DILocation(line: 1125, column: 4, scope: !2086)
!2088 = !DILocation(line: 1126, column: 4, scope: !2086)
!2089 = !DILocation(line: 1128, column: 3, scope: !2061)
!2090 = !DILocation(line: 1132, column: 25, scope: !395)
!2091 = !DILocation(line: 1132, column: 2, scope: !395)
!2092 = !DILocation(line: 1139, column: 10, scope: !395)
!2093 = !DILocation(line: 1139, column: 2, scope: !395)
!2094 = !DILocation(line: 1141, column: 3, scope: !2095)
!2095 = distinct !DILexicalBlock(scope: !395, file: !1, line: 1139, column: 13)
!2096 = !DILocation(line: 1141, column: 6, scope: !2095)
!2097 = !DILocation(line: 1141, column: 14, scope: !2095)
!2098 = !DILocation(line: 1141, column: 20, scope: !2095)
!2099 = !DILocation(line: 1142, column: 3, scope: !2095)
!2100 = !DILocation(line: 1146, column: 33, scope: !2095)
!2101 = !DILocation(line: 1146, column: 58, scope: !2095)
!2102 = !DILocation(line: 1146, column: 40, scope: !2095)
!2103 = !DILocation(line: 1146, column: 3, scope: !2104)
!2104 = !DILexicalBlockFile(scope: !2095, file: !1, discriminator: 1)
!2105 = !DILocation(line: 1147, column: 3, scope: !2095)
!2106 = !DILocation(line: 1147, column: 6, scope: !2095)
!2107 = !DILocation(line: 1147, column: 18, scope: !2095)
!2108 = !DILocation(line: 1148, column: 30, scope: !2109)
!2109 = distinct !DILexicalBlock(scope: !2095, file: !1, line: 1148, column: 7)
!2110 = !DILocation(line: 1148, column: 7, scope: !2109)
!2111 = !DILocation(line: 1148, column: 37, scope: !2109)
!2112 = !DILocation(line: 1148, column: 7, scope: !2095)
!2113 = !DILocation(line: 1149, column: 35, scope: !2114)
!2114 = distinct !DILexicalBlock(scope: !2109, file: !1, line: 1148, column: 50)
!2115 = !DILocation(line: 1149, column: 15, scope: !2114)
!2116 = !DILocation(line: 1149, column: 4, scope: !2114)
!2117 = !DILocation(line: 1149, column: 7, scope: !2114)
!2118 = !DILocation(line: 1149, column: 13, scope: !2114)
!2119 = !DILocation(line: 1150, column: 50, scope: !2114)
!2120 = !DILocation(line: 1150, column: 31, scope: !2114)
!2121 = !DILocation(line: 1150, column: 4, scope: !2114)
!2122 = !DILocation(line: 1150, column: 7, scope: !2114)
!2123 = !DILocation(line: 1150, column: 29, scope: !2114)
!2124 = !DILocation(line: 1151, column: 20, scope: !2114)
!2125 = !DILocation(line: 1151, column: 23, scope: !2114)
!2126 = !DILocation(line: 1151, column: 45, scope: !2114)
!2127 = !DILocation(line: 1151, column: 19, scope: !2114)
!2128 = !DILocation(line: 1151, column: 4, scope: !2114)
!2129 = !DILocation(line: 1151, column: 7, scope: !2114)
!2130 = !DILocation(line: 1151, column: 17, scope: !2114)
!2131 = !DILocation(line: 1152, column: 9, scope: !2132)
!2132 = distinct !DILexicalBlock(scope: !2114, file: !1, line: 1152, column: 8)
!2133 = !DILocation(line: 1152, column: 12, scope: !2132)
!2134 = !DILocation(line: 1152, column: 22, scope: !2132)
!2135 = !DILocation(line: 1153, column: 21, scope: !2132)
!2136 = !DILocation(line: 1153, column: 24, scope: !2132)
!2137 = !DILocation(line: 1153, column: 8, scope: !2132)
!2138 = !DILocation(line: 1153, column: 31, scope: !2132)
!2139 = !DILocation(line: 1152, column: 8, scope: !2140)
!2140 = !DILexicalBlockFile(scope: !2114, file: !1, discriminator: 1)
!2141 = !DILocation(line: 1154, column: 5, scope: !2132)
!2142 = !DILocation(line: 1155, column: 3, scope: !2114)
!2143 = !DILocation(line: 1156, column: 4, scope: !2144)
!2144 = distinct !DILexicalBlock(scope: !2109, file: !1, line: 1155, column: 10)
!2145 = !DILocation(line: 1156, column: 7, scope: !2144)
!2146 = !DILocation(line: 1156, column: 29, scope: !2144)
!2147 = !DILocation(line: 1157, column: 4, scope: !2144)
!2148 = !DILocation(line: 1157, column: 7, scope: !2144)
!2149 = !DILocation(line: 1157, column: 17, scope: !2144)
!2150 = !DILocation(line: 1159, column: 3, scope: !2095)
!2151 = !DILocation(line: 1159, column: 6, scope: !2095)
!2152 = !DILocation(line: 1159, column: 14, scope: !2095)
!2153 = !DILocation(line: 1159, column: 20, scope: !2095)
!2154 = !DILocation(line: 1160, column: 3, scope: !2095)
!2155 = !DILocation(line: 1162, column: 3, scope: !2095)
!2156 = !DILocation(line: 1164, column: 3, scope: !2095)
!2157 = !DILocation(line: 1164, column: 6, scope: !2095)
!2158 = !DILocation(line: 1164, column: 14, scope: !2095)
!2159 = !DILocation(line: 1164, column: 20, scope: !2095)
!2160 = !DILocation(line: 1165, column: 3, scope: !2095)
!2161 = !DILocation(line: 1168, column: 29, scope: !395)
!2162 = !DILocation(line: 1168, column: 32, scope: !395)
!2163 = !DILocation(line: 1168, column: 2, scope: !395)
!2164 = !DILocation(line: 1169, column: 10, scope: !395)
!2165 = !DILocation(line: 1169, column: 2, scope: !395)
!2166 = !DILocation(line: 1170, column: 1, scope: !395)
!2167 = !DILocalVariable(name: "t", arg: 1, scope: !375, file: !1, line: 2644, type: !153)
!2168 = !DILocation(line: 2644, column: 24, scope: !375)
!2169 = !DILocalVariable(name: "i", scope: !375, file: !1, line: 2646, type: !62)
!2170 = !DILocation(line: 2646, column: 6, scope: !375)
!2171 = !DILocation(line: 2648, column: 6, scope: !2172)
!2172 = distinct !DILexicalBlock(scope: !375, file: !1, line: 2648, column: 6)
!2173 = !DILocation(line: 2648, column: 8, scope: !2172)
!2174 = !DILocation(line: 2648, column: 6, scope: !375)
!2175 = !DILocation(line: 2649, column: 3, scope: !2172)
!2176 = !DILocation(line: 2650, column: 23, scope: !375)
!2177 = !DILocation(line: 2650, column: 26, scope: !375)
!2178 = !DILocation(line: 2650, column: 2, scope: !375)
!2179 = !DILocation(line: 2652, column: 7, scope: !375)
!2180 = !DILocation(line: 2652, column: 10, scope: !375)
!2181 = !DILocation(line: 2652, column: 2, scope: !375)
!2182 = !DILocation(line: 2654, column: 7, scope: !375)
!2183 = !DILocation(line: 2654, column: 10, scope: !375)
!2184 = !DILocation(line: 2654, column: 2, scope: !375)
!2185 = !DILocation(line: 2655, column: 9, scope: !2186)
!2186 = distinct !DILexicalBlock(scope: !375, file: !1, line: 2655, column: 2)
!2187 = !DILocation(line: 2655, column: 7, scope: !2186)
!2188 = !DILocation(line: 2655, column: 14, scope: !2189)
!2189 = !DILexicalBlockFile(scope: !2190, file: !1, discriminator: 1)
!2190 = distinct !DILexicalBlock(scope: !2186, file: !1, line: 2655, column: 2)
!2191 = !DILocation(line: 2655, column: 18, scope: !2189)
!2192 = !DILocation(line: 2655, column: 21, scope: !2189)
!2193 = !DILocation(line: 2655, column: 16, scope: !2189)
!2194 = !DILocation(line: 2655, column: 2, scope: !2189)
!2195 = !DILocation(line: 2656, column: 28, scope: !2190)
!2196 = !DILocation(line: 2656, column: 8, scope: !2190)
!2197 = !DILocation(line: 2656, column: 11, scope: !2190)
!2198 = !DILocation(line: 2656, column: 31, scope: !2190)
!2199 = !DILocation(line: 2656, column: 3, scope: !2190)
!2200 = !DILocation(line: 2655, column: 41, scope: !2201)
!2201 = !DILexicalBlockFile(scope: !2190, file: !1, discriminator: 2)
!2202 = !DILocation(line: 2655, column: 2, scope: !2201)
!2203 = !DILocation(line: 2657, column: 7, scope: !375)
!2204 = !DILocation(line: 2657, column: 10, scope: !375)
!2205 = !DILocation(line: 2657, column: 2, scope: !375)
!2206 = !DILocation(line: 2658, column: 7, scope: !375)
!2207 = !DILocation(line: 2658, column: 2, scope: !375)
!2208 = !DILocation(line: 2659, column: 1, scope: !375)
!2209 = !DILocation(line: 2659, column: 1, scope: !2210)
!2210 = !DILexicalBlockFile(scope: !375, file: !1, discriminator: 1)
!2211 = !DILocalVariable(name: "t", arg: 1, scope: !379, file: !1, line: 2610, type: !153)
!2212 = !DILocation(line: 2610, column: 25, scope: !379)
!2213 = !DILocation(line: 2613, column: 6, scope: !2214)
!2214 = distinct !DILexicalBlock(scope: !379, file: !1, line: 2613, column: 6)
!2215 = !DILocation(line: 2613, column: 8, scope: !2214)
!2216 = !DILocation(line: 2613, column: 6, scope: !379)
!2217 = !DILocation(line: 2614, column: 3, scope: !2214)
!2218 = !DILocation(line: 2615, column: 6, scope: !2219)
!2219 = distinct !DILexicalBlock(scope: !379, file: !1, line: 2615, column: 6)
!2220 = !DILocation(line: 2615, column: 9, scope: !2219)
!2221 = !DILocation(line: 2615, column: 18, scope: !2219)
!2222 = !DILocation(line: 2615, column: 6, scope: !379)
!2223 = !DILocation(line: 2616, column: 26, scope: !2224)
!2224 = distinct !DILexicalBlock(scope: !2219, file: !1, line: 2615, column: 24)
!2225 = !DILocation(line: 2616, column: 29, scope: !2224)
!2226 = !DILocation(line: 2616, column: 39, scope: !2224)
!2227 = !DILocation(line: 2616, column: 43, scope: !2224)
!2228 = !DILocation(line: 2616, column: 46, scope: !2224)
!2229 = !DILocation(line: 2616, column: 3, scope: !2224)
!2230 = !DILocation(line: 2617, column: 3, scope: !2224)
!2231 = !DILocation(line: 2617, column: 6, scope: !2224)
!2232 = !DILocation(line: 2617, column: 15, scope: !2224)
!2233 = !DILocation(line: 2618, column: 2, scope: !2224)
!2234 = !DILocation(line: 2620, column: 6, scope: !2235)
!2235 = distinct !DILexicalBlock(scope: !379, file: !1, line: 2620, column: 6)
!2236 = !DILocation(line: 2620, column: 9, scope: !2235)
!2237 = !DILocation(line: 2620, column: 11, scope: !2235)
!2238 = !DILocation(line: 2620, column: 6, scope: !379)
!2239 = !DILocation(line: 2621, column: 12, scope: !2240)
!2240 = distinct !DILexicalBlock(scope: !2235, file: !1, line: 2620, column: 34)
!2241 = !DILocation(line: 2621, column: 15, scope: !2240)
!2242 = !DILocation(line: 2621, column: 3, scope: !2240)
!2243 = !DILocation(line: 2622, column: 3, scope: !2240)
!2244 = !DILocation(line: 2622, column: 6, scope: !2240)
!2245 = !DILocation(line: 2622, column: 8, scope: !2240)
!2246 = !DILocation(line: 2623, column: 2, scope: !2240)
!2247 = !DILocation(line: 2625, column: 2, scope: !379)
!2248 = !DILocation(line: 2625, column: 9, scope: !2249)
!2249 = !DILexicalBlockFile(scope: !379, file: !1, discriminator: 1)
!2250 = !DILocation(line: 2625, column: 12, scope: !2249)
!2251 = !DILocation(line: 2625, column: 18, scope: !2249)
!2252 = !DILocation(line: 2625, column: 2, scope: !2249)
!2253 = !DILocation(line: 2626, column: 7, scope: !2254)
!2254 = distinct !DILexicalBlock(scope: !2255, file: !1, line: 2626, column: 7)
!2255 = distinct !DILexicalBlock(scope: !379, file: !1, line: 2625, column: 27)
!2256 = !DILocation(line: 2626, column: 10, scope: !2254)
!2257 = !DILocation(line: 2626, column: 17, scope: !2254)
!2258 = !DILocation(line: 2626, column: 23, scope: !2254)
!2259 = !DILocation(line: 2626, column: 7, scope: !2255)
!2260 = !DILocation(line: 2627, column: 10, scope: !2254)
!2261 = !DILocation(line: 2627, column: 13, scope: !2254)
!2262 = !DILocation(line: 2627, column: 20, scope: !2254)
!2263 = !DILocation(line: 2627, column: 4, scope: !2254)
!2264 = !DILocation(line: 2628, column: 12, scope: !2255)
!2265 = !DILocation(line: 2628, column: 3, scope: !2255)
!2266 = !DILocation(line: 2625, column: 2, scope: !2267)
!2267 = !DILexicalBlockFile(scope: !379, file: !1, discriminator: 2)
!2268 = !DILocation(line: 2630, column: 6, scope: !2269)
!2269 = distinct !DILexicalBlock(scope: !379, file: !1, line: 2630, column: 6)
!2270 = !DILocation(line: 2630, column: 9, scope: !2269)
!2271 = !DILocation(line: 2630, column: 24, scope: !2269)
!2272 = !DILocation(line: 2630, column: 6, scope: !379)
!2273 = !DILocation(line: 2631, column: 9, scope: !2274)
!2274 = distinct !DILexicalBlock(scope: !2269, file: !1, line: 2630, column: 30)
!2275 = !DILocation(line: 2631, column: 12, scope: !2274)
!2276 = !DILocation(line: 2631, column: 3, scope: !2274)
!2277 = !DILocation(line: 2632, column: 3, scope: !2274)
!2278 = !DILocation(line: 2632, column: 6, scope: !2274)
!2279 = !DILocation(line: 2632, column: 21, scope: !2274)
!2280 = !DILocation(line: 2633, column: 2, scope: !2274)
!2281 = !DILocation(line: 2634, column: 6, scope: !2282)
!2282 = distinct !DILexicalBlock(scope: !379, file: !1, line: 2634, column: 6)
!2283 = !DILocation(line: 2634, column: 9, scope: !2282)
!2284 = !DILocation(line: 2634, column: 24, scope: !2282)
!2285 = !DILocation(line: 2634, column: 6, scope: !379)
!2286 = !DILocation(line: 2635, column: 9, scope: !2287)
!2287 = distinct !DILexicalBlock(scope: !2282, file: !1, line: 2634, column: 30)
!2288 = !DILocation(line: 2635, column: 12, scope: !2287)
!2289 = !DILocation(line: 2635, column: 3, scope: !2287)
!2290 = !DILocation(line: 2636, column: 3, scope: !2287)
!2291 = !DILocation(line: 2636, column: 6, scope: !2287)
!2292 = !DILocation(line: 2636, column: 21, scope: !2287)
!2293 = !DILocation(line: 2637, column: 2, scope: !2287)
!2294 = !DILocation(line: 2638, column: 1, scope: !379)
!2295 = !DILocalVariable(name: "fd", arg: 1, scope: !380, file: !1, line: 1958, type: !62)
!2296 = !DILocation(line: 1958, column: 28, scope: !380)
!2297 = !DILocalVariable(name: "t", arg: 2, scope: !380, file: !1, line: 1958, type: !153)
!2298 = !DILocation(line: 1958, column: 45, scope: !380)
!2299 = !DILocalVariable(name: "rt", arg: 3, scope: !380, file: !1, line: 1958, type: !383)
!2300 = !DILocation(line: 1958, column: 69, scope: !380)
!2301 = !DILocalVariable(name: "timespecs", scope: !380, file: !1, line: 1966, type: !2302)
!2302 = !DICompositeType(tag: DW_TAG_array_type, baseType: !243, size: 256, align: 64, elements: !2303)
!2303 = !{!2304}
!2304 = !DISubrange(count: 2)
!2305 = !DILocation(line: 1966, column: 18, scope: !380)
!2306 = !DILocalVariable(name: "times", scope: !380, file: !1, line: 1968, type: !2307)
!2307 = !DICompositeType(tag: DW_TAG_array_type, baseType: !2308, size: 256, align: 64, elements: !2303)
!2308 = !DICompositeType(tag: DW_TAG_structure_type, name: "timeval", file: !2309, line: 30, size: 128, align: 64, elements: !2310)
!2309 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2310 = !{!2311, !2312}
!2311 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !2308, file: !2309, line: 32, baseType: !177, size: 64, align: 64)
!2312 = !DIDerivedType(tag: DW_TAG_member, name: "tv_usec", scope: !2308, file: !2309, line: 33, baseType: !2313, size: 64, align: 64, offset: 64)
!2313 = !DIDerivedType(tag: DW_TAG_typedef, name: "__suseconds_t", file: !80, line: 141, baseType: !81)
!2314 = !DILocation(line: 1968, column: 17, scope: !380)
!2315 = !DILocation(line: 1970, column: 7, scope: !2316)
!2316 = distinct !DILexicalBlock(scope: !380, file: !1, line: 1970, column: 6)
!2317 = !DILocation(line: 1970, column: 10, scope: !2316)
!2318 = !DILocation(line: 1970, column: 16, scope: !2316)
!2319 = !DILocation(line: 1970, column: 37, scope: !2316)
!2320 = !DILocation(line: 1970, column: 42, scope: !2316)
!2321 = !DILocation(line: 1970, column: 45, scope: !2322)
!2322 = !DILexicalBlockFile(scope: !2316, file: !1, discriminator: 1)
!2323 = !DILocation(line: 1970, column: 49, scope: !2322)
!2324 = !DILocation(line: 1970, column: 6, scope: !2322)
!2325 = !DILocation(line: 1971, column: 7, scope: !2326)
!2326 = distinct !DILexicalBlock(scope: !2327, file: !1, line: 1971, column: 7)
!2327 = distinct !DILexicalBlock(scope: !2316, file: !1, line: 1970, column: 58)
!2328 = !DILocation(line: 1971, column: 10, scope: !2326)
!2329 = !DILocation(line: 1971, column: 7, scope: !2327)
!2330 = !DILocation(line: 1972, column: 18, scope: !2326)
!2331 = !DILocation(line: 1972, column: 12, scope: !2326)
!2332 = !DILocation(line: 1972, column: 4, scope: !2326)
!2333 = !DILocation(line: 1974, column: 4, scope: !2326)
!2334 = !DILocation(line: 1978, column: 24, scope: !380)
!2335 = !DILocation(line: 1978, column: 28, scope: !380)
!2336 = !DILocation(line: 1978, column: 2, scope: !380)
!2337 = !DILocation(line: 1978, column: 15, scope: !380)
!2338 = !DILocation(line: 1978, column: 22, scope: !380)
!2339 = !DILocation(line: 1979, column: 25, scope: !380)
!2340 = !DILocation(line: 1979, column: 29, scope: !380)
!2341 = !DILocation(line: 1979, column: 2, scope: !380)
!2342 = !DILocation(line: 1979, column: 15, scope: !380)
!2343 = !DILocation(line: 1979, column: 23, scope: !380)
!2344 = !DILocation(line: 1981, column: 24, scope: !380)
!2345 = !DILocation(line: 1981, column: 28, scope: !380)
!2346 = !DILocation(line: 1981, column: 2, scope: !380)
!2347 = !DILocation(line: 1981, column: 15, scope: !380)
!2348 = !DILocation(line: 1981, column: 22, scope: !380)
!2349 = !DILocation(line: 1982, column: 25, scope: !380)
!2350 = !DILocation(line: 1982, column: 29, scope: !380)
!2351 = !DILocation(line: 1982, column: 2, scope: !380)
!2352 = !DILocation(line: 1982, column: 15, scope: !380)
!2353 = !DILocation(line: 1982, column: 23, scope: !380)
!2354 = !DILocation(line: 1984, column: 15, scope: !2355)
!2355 = distinct !DILexicalBlock(scope: !380, file: !1, line: 1984, column: 6)
!2356 = !DILocation(line: 1984, column: 19, scope: !2355)
!2357 = !DILocation(line: 1984, column: 6, scope: !2355)
!2358 = !DILocation(line: 1984, column: 30, scope: !2355)
!2359 = !DILocation(line: 1984, column: 6, scope: !380)
!2360 = !DILocation(line: 1985, column: 17, scope: !2355)
!2361 = !DILocation(line: 1985, column: 11, scope: !2355)
!2362 = !DILocation(line: 1985, column: 3, scope: !2355)
!2363 = !DILocation(line: 1988, column: 20, scope: !380)
!2364 = !DILocation(line: 1988, column: 24, scope: !380)
!2365 = !DILocation(line: 1988, column: 2, scope: !380)
!2366 = !DILocation(line: 1988, column: 11, scope: !380)
!2367 = !DILocation(line: 1988, column: 18, scope: !380)
!2368 = !DILocation(line: 1989, column: 21, scope: !380)
!2369 = !DILocation(line: 1989, column: 25, scope: !380)
!2370 = !DILocation(line: 1989, column: 36, scope: !380)
!2371 = !DILocation(line: 1989, column: 2, scope: !380)
!2372 = !DILocation(line: 1989, column: 11, scope: !380)
!2373 = !DILocation(line: 1989, column: 19, scope: !380)
!2374 = !DILocation(line: 1991, column: 20, scope: !380)
!2375 = !DILocation(line: 1991, column: 24, scope: !380)
!2376 = !DILocation(line: 1991, column: 2, scope: !380)
!2377 = !DILocation(line: 1991, column: 11, scope: !380)
!2378 = !DILocation(line: 1991, column: 18, scope: !380)
!2379 = !DILocation(line: 1992, column: 21, scope: !380)
!2380 = !DILocation(line: 1992, column: 25, scope: !380)
!2381 = !DILocation(line: 1992, column: 36, scope: !380)
!2382 = !DILocation(line: 1992, column: 2, scope: !380)
!2383 = !DILocation(line: 1992, column: 11, scope: !380)
!2384 = !DILocation(line: 1992, column: 19, scope: !380)
!2385 = !DILocation(line: 1998, column: 8, scope: !380)
!2386 = !DILocation(line: 1998, column: 2, scope: !380)
!2387 = !DILocation(line: 2000, column: 36, scope: !2388)
!2388 = distinct !DILexicalBlock(scope: !380, file: !1, line: 2000, column: 6)
!2389 = !DILocation(line: 2000, column: 16, scope: !2388)
!2390 = !DILocation(line: 2000, column: 40, scope: !2388)
!2391 = !DILocation(line: 2000, column: 44, scope: !2388)
!2392 = !DILocation(line: 2000, column: 50, scope: !2388)
!2393 = !DILocation(line: 2000, column: 6, scope: !2394)
!2394 = !DILexicalBlockFile(scope: !2388, file: !1, discriminator: 1)
!2395 = !DILocation(line: 2000, column: 57, scope: !2388)
!2396 = !DILocation(line: 2000, column: 6, scope: !380)
!2397 = !DILocation(line: 2001, column: 3, scope: !2388)
!2398 = !DILocation(line: 2004, column: 14, scope: !2399)
!2399 = distinct !DILexicalBlock(scope: !380, file: !1, line: 2004, column: 6)
!2400 = !DILocation(line: 2004, column: 18, scope: !2399)
!2401 = !DILocation(line: 2004, column: 24, scope: !2399)
!2402 = !DILocation(line: 2004, column: 6, scope: !2399)
!2403 = !DILocation(line: 2004, column: 31, scope: !2399)
!2404 = !DILocation(line: 2004, column: 6, scope: !380)
!2405 = !DILocation(line: 2008, column: 3, scope: !2399)
!2406 = !DILocation(line: 2010, column: 2, scope: !380)
!2407 = !DILocation(line: 2011, column: 1, scope: !380)
!2408 = !DILocalVariable(name: "t", arg: 1, scope: !384, file: !1, line: 2270, type: !153)
!2409 = !DILocation(line: 2270, column: 23, scope: !384)
!2410 = !DILocalVariable(name: "te", scope: !384, file: !1, line: 2272, type: !157)
!2411 = !DILocation(line: 2272, column: 21, scope: !384)
!2412 = !DILocation(line: 2274, column: 12, scope: !384)
!2413 = !DILocation(line: 2274, column: 15, scope: !384)
!2414 = !DILocation(line: 2274, column: 2, scope: !384)
!2415 = !DILocation(line: 2274, column: 5, scope: !384)
!2416 = !DILocation(line: 2274, column: 10, scope: !384)
!2417 = !DILocation(line: 2274, column: 31, scope: !384)
!2418 = !DILocation(line: 2275, column: 19, scope: !384)
!2419 = !DILocation(line: 2275, column: 22, scope: !384)
!2420 = !DILocation(line: 2275, column: 2, scope: !384)
!2421 = !DILocation(line: 2275, column: 5, scope: !384)
!2422 = !DILocation(line: 2275, column: 10, scope: !384)
!2423 = !DILocation(line: 2275, column: 17, scope: !384)
!2424 = !DILocation(line: 2276, column: 6, scope: !2425)
!2425 = distinct !DILexicalBlock(scope: !384, file: !1, line: 2276, column: 6)
!2426 = !DILocation(line: 2276, column: 9, scope: !2425)
!2427 = !DILocation(line: 2276, column: 18, scope: !2425)
!2428 = !DILocation(line: 2276, column: 21, scope: !2425)
!2429 = !DILocation(line: 2276, column: 15, scope: !2425)
!2430 = !DILocation(line: 2276, column: 29, scope: !2425)
!2431 = !DILocation(line: 2276, column: 32, scope: !2432)
!2432 = !DILexicalBlockFile(scope: !2425, file: !1, discriminator: 1)
!2433 = !DILocation(line: 2276, column: 35, scope: !2432)
!2434 = !DILocation(line: 2276, column: 43, scope: !2432)
!2435 = !DILocation(line: 2276, column: 6, scope: !2432)
!2436 = !DILocation(line: 2277, column: 16, scope: !2425)
!2437 = !DILocation(line: 2277, column: 19, scope: !2425)
!2438 = !DILocation(line: 2277, column: 28, scope: !2425)
!2439 = !DILocation(line: 2277, column: 3, scope: !2425)
!2440 = !DILocation(line: 2277, column: 6, scope: !2425)
!2441 = !DILocation(line: 2277, column: 14, scope: !2425)
!2442 = !DILocation(line: 2278, column: 7, scope: !384)
!2443 = !DILocation(line: 2278, column: 10, scope: !384)
!2444 = !DILocation(line: 2278, column: 5, scope: !384)
!2445 = !DILocation(line: 2279, column: 13, scope: !384)
!2446 = !DILocation(line: 2279, column: 17, scope: !384)
!2447 = !DILocation(line: 2279, column: 2, scope: !384)
!2448 = !DILocation(line: 2279, column: 5, scope: !384)
!2449 = !DILocation(line: 2279, column: 11, scope: !384)
!2450 = !DILocation(line: 2280, column: 22, scope: !384)
!2451 = !DILocation(line: 2280, column: 26, scope: !384)
!2452 = !DILocation(line: 2280, column: 2, scope: !384)
!2453 = !DILocation(line: 2280, column: 5, scope: !384)
!2454 = !DILocation(line: 2280, column: 20, scope: !384)
!2455 = !DILocation(line: 2281, column: 16, scope: !384)
!2456 = !DILocation(line: 2281, column: 19, scope: !384)
!2457 = !DILocation(line: 2281, column: 24, scope: !384)
!2458 = !DILocation(line: 2281, column: 28, scope: !384)
!2459 = !DILocation(line: 2281, column: 31, scope: !384)
!2460 = !DILocation(line: 2281, column: 26, scope: !384)
!2461 = !DILocation(line: 2281, column: 2, scope: !384)
!2462 = !DILocation(line: 2281, column: 5, scope: !384)
!2463 = !DILocation(line: 2281, column: 14, scope: !384)
!2464 = !DILocation(line: 2282, column: 2, scope: !384)
!2465 = !DILocation(line: 2282, column: 9, scope: !2466)
!2466 = !DILexicalBlockFile(scope: !384, file: !1, discriminator: 1)
!2467 = !DILocation(line: 2282, column: 12, scope: !2466)
!2468 = !DILocation(line: 2282, column: 24, scope: !2466)
!2469 = !DILocation(line: 2282, column: 2, scope: !2466)
!2470 = !DILocation(line: 2283, column: 3, scope: !384)
!2471 = !DILocation(line: 2283, column: 6, scope: !384)
!2472 = !DILocation(line: 2283, column: 14, scope: !384)
!2473 = !DILocation(line: 2282, column: 2, scope: !2474)
!2474 = !DILexicalBlockFile(scope: !384, file: !1, discriminator: 2)
!2475 = !DILocation(line: 2284, column: 23, scope: !384)
!2476 = !DILocation(line: 2284, column: 27, scope: !384)
!2477 = !DILocation(line: 2284, column: 2, scope: !384)
!2478 = !DILocation(line: 2285, column: 7, scope: !384)
!2479 = !DILocation(line: 2285, column: 2, scope: !384)
!2480 = !DILocation(line: 2286, column: 1, scope: !384)
!2481 = !DILocalVariable(name: "t", arg: 1, scope: !386, file: !1, line: 2592, type: !153)
!2482 = !DILocation(line: 2592, column: 39, scope: !386)
!2483 = !DILocation(line: 2594, column: 10, scope: !386)
!2484 = !DILocation(line: 2594, column: 13, scope: !386)
!2485 = !DILocation(line: 2594, column: 2, scope: !386)
!2486 = !DILocalVariable(name: "t", arg: 1, scope: !389, file: !1, line: 2601, type: !153)
!2487 = !DILocation(line: 2601, column: 32, scope: !389)
!2488 = !DILocation(line: 2603, column: 10, scope: !389)
!2489 = !DILocation(line: 2603, column: 13, scope: !389)
!2490 = !DILocation(line: 2603, column: 18, scope: !389)
!2491 = !DILocation(line: 2603, column: 2, scope: !389)
!2492 = !DILocalVariable(name: "t", arg: 1, scope: !390, file: !1, line: 2223, type: !153)
!2493 = !DILocation(line: 2223, column: 37, scope: !390)
!2494 = !DILocalVariable(name: "r", scope: !390, file: !1, line: 2225, type: !62)
!2495 = !DILocation(line: 2225, column: 6, scope: !390)
!2496 = !DILocation(line: 2227, column: 7, scope: !2497)
!2497 = distinct !DILexicalBlock(scope: !390, file: !1, line: 2227, column: 6)
!2498 = !DILocation(line: 2227, column: 10, scope: !2497)
!2499 = !DILocation(line: 2227, column: 16, scope: !2497)
!2500 = !DILocation(line: 2227, column: 32, scope: !2497)
!2501 = !DILocation(line: 2227, column: 6, scope: !390)
!2502 = !DILocation(line: 2228, column: 14, scope: !2503)
!2503 = distinct !DILexicalBlock(scope: !2497, file: !1, line: 2227, column: 38)
!2504 = !DILocation(line: 2228, column: 17, scope: !2503)
!2505 = !DILocation(line: 2228, column: 7, scope: !2503)
!2506 = !DILocation(line: 2228, column: 5, scope: !2503)
!2507 = !DILocation(line: 2229, column: 7, scope: !2508)
!2508 = distinct !DILexicalBlock(scope: !2503, file: !1, line: 2229, column: 7)
!2509 = !DILocation(line: 2229, column: 9, scope: !2508)
!2510 = !DILocation(line: 2229, column: 7, scope: !2503)
!2511 = !DILocation(line: 2230, column: 4, scope: !2512)
!2512 = distinct !DILexicalBlock(scope: !2508, file: !1, line: 2229, column: 15)
!2513 = !DILocation(line: 2230, column: 7, scope: !2512)
!2514 = !DILocation(line: 2230, column: 13, scope: !2512)
!2515 = !DILocation(line: 2231, column: 4, scope: !2512)
!2516 = !DILocation(line: 2231, column: 7, scope: !2512)
!2517 = !DILocation(line: 2231, column: 13, scope: !2512)
!2518 = !DILocation(line: 2232, column: 3, scope: !2512)
!2519 = !DILocation(line: 2233, column: 2, scope: !2503)
!2520 = !DILocation(line: 2234, column: 10, scope: !390)
!2521 = !DILocation(line: 2234, column: 2, scope: !390)
!2522 = !DILocalVariable(name: "a", arg: 1, scope: !391, file: !1, line: 628, type: !43)
!2523 = !DILocation(line: 628, column: 54, scope: !391)
!2524 = !DILocalVariable(name: "t", scope: !391, file: !1, line: 630, type: !153)
!2525 = !DILocation(line: 630, column: 15, scope: !391)
!2526 = !DILocation(line: 630, column: 19, scope: !391)
!2527 = !DILocation(line: 630, column: 22, scope: !391)
!2528 = !DILocalVariable(name: "cf", scope: !391, file: !1, line: 631, type: !270)
!2529 = !DILocation(line: 631, column: 21, scope: !391)
!2530 = !DILocation(line: 631, column: 26, scope: !391)
!2531 = !DILocation(line: 631, column: 29, scope: !391)
!2532 = !DILocalVariable(name: "asize", scope: !391, file: !1, line: 632, type: !84)
!2533 = !DILocation(line: 632, column: 9, scope: !391)
!2534 = !DILocalVariable(name: "s", scope: !391, file: !1, line: 633, type: !84)
!2535 = !DILocation(line: 633, column: 9, scope: !391)
!2536 = !DILocation(line: 635, column: 6, scope: !2537)
!2537 = distinct !DILexicalBlock(scope: !391, file: !1, line: 635, column: 6)
!2538 = !DILocation(line: 635, column: 10, scope: !2537)
!2539 = !DILocation(line: 635, column: 25, scope: !2537)
!2540 = !DILocation(line: 635, column: 6, scope: !391)
!2541 = !DILocalVariable(name: "xfer_align", scope: !2542, file: !1, line: 639, type: !81)
!2542 = distinct !DILexicalBlock(scope: !2537, file: !1, line: 635, column: 34)
!2543 = !DILocation(line: 639, column: 8, scope: !2542)
!2544 = !DILocation(line: 639, column: 22, scope: !2542)
!2545 = !DILocation(line: 639, column: 26, scope: !2542)
!2546 = !DILocation(line: 639, column: 37, scope: !2542)
!2547 = !DILocation(line: 639, column: 21, scope: !2542)
!2548 = !DILocation(line: 639, column: 21, scope: !2549)
!2549 = !DILexicalBlockFile(scope: !2542, file: !1, discriminator: 1)
!2550 = !DILocation(line: 639, column: 49, scope: !2551)
!2551 = !DILexicalBlockFile(scope: !2542, file: !1, discriminator: 2)
!2552 = !DILocation(line: 639, column: 53, scope: !2551)
!2553 = !DILocation(line: 639, column: 21, scope: !2551)
!2554 = !DILocation(line: 639, column: 21, scope: !2555)
!2555 = !DILexicalBlockFile(scope: !2542, file: !1, discriminator: 3)
!2556 = !DILocation(line: 639, column: 8, scope: !2555)
!2557 = !DILocation(line: 641, column: 7, scope: !2558)
!2558 = distinct !DILexicalBlock(scope: !2542, file: !1, line: 641, column: 7)
!2559 = !DILocation(line: 641, column: 11, scope: !2558)
!2560 = !DILocation(line: 641, column: 25, scope: !2558)
!2561 = !DILocation(line: 641, column: 7, scope: !2542)
!2562 = !DILocation(line: 642, column: 12, scope: !2558)
!2563 = !DILocation(line: 642, column: 16, scope: !2558)
!2564 = !DILocation(line: 642, column: 32, scope: !2558)
!2565 = !DILocation(line: 642, column: 30, scope: !2558)
!2566 = !DILocation(line: 642, column: 10, scope: !2558)
!2567 = !DILocation(line: 642, column: 4, scope: !2558)
!2568 = !DILocalVariable(name: "incr", scope: !2569, file: !1, line: 644, type: !81)
!2569 = distinct !DILexicalBlock(scope: !2558, file: !1, line: 643, column: 8)
!2570 = !DILocation(line: 644, column: 9, scope: !2569)
!2571 = !DILocation(line: 644, column: 16, scope: !2569)
!2572 = !DILocation(line: 644, column: 20, scope: !2569)
!2573 = !DILocation(line: 647, column: 8, scope: !2574)
!2574 = distinct !DILexicalBlock(scope: !2569, file: !1, line: 647, column: 8)
!2575 = !DILocation(line: 647, column: 13, scope: !2574)
!2576 = !DILocation(line: 647, column: 8, scope: !2569)
!2577 = !DILocation(line: 648, column: 12, scope: !2574)
!2578 = !DILocation(line: 648, column: 16, scope: !2574)
!2579 = !DILocation(line: 648, column: 10, scope: !2574)
!2580 = !DILocation(line: 648, column: 5, scope: !2574)
!2581 = !DILocation(line: 649, column: 8, scope: !2582)
!2582 = distinct !DILexicalBlock(scope: !2569, file: !1, line: 649, column: 8)
!2583 = !DILocation(line: 649, column: 12, scope: !2582)
!2584 = !DILocation(line: 649, column: 26, scope: !2582)
!2585 = !DILocation(line: 649, column: 8, scope: !2569)
!2586 = !DILocation(line: 650, column: 12, scope: !2587)
!2587 = distinct !DILexicalBlock(scope: !2582, file: !1, line: 649, column: 31)
!2588 = !DILocation(line: 650, column: 10, scope: !2587)
!2589 = !DILocation(line: 651, column: 13, scope: !2587)
!2590 = !DILocation(line: 651, column: 11, scope: !2587)
!2591 = !DILocation(line: 652, column: 4, scope: !2587)
!2592 = !DILocation(line: 653, column: 13, scope: !2582)
!2593 = !DILocation(line: 653, column: 17, scope: !2582)
!2594 = !DILocation(line: 653, column: 11, scope: !2582)
!2595 = !DILocation(line: 657, column: 4, scope: !2569)
!2596 = !DILocation(line: 657, column: 11, scope: !2597)
!2597 = !DILexicalBlockFile(scope: !2569, file: !1, discriminator: 1)
!2598 = !DILocation(line: 657, column: 17, scope: !2597)
!2599 = !DILocation(line: 657, column: 4, scope: !2597)
!2600 = !DILocation(line: 658, column: 14, scope: !2569)
!2601 = !DILocation(line: 658, column: 11, scope: !2569)
!2602 = !DILocation(line: 657, column: 4, scope: !2603)
!2603 = !DILexicalBlockFile(scope: !2569, file: !1, discriminator: 2)
!2604 = !DILocation(line: 661, column: 13, scope: !2569)
!2605 = !DILocation(line: 661, column: 10, scope: !2569)
!2606 = !DILocation(line: 663, column: 31, scope: !2542)
!2607 = !DILocation(line: 663, column: 24, scope: !2542)
!2608 = !DILocation(line: 663, column: 3, scope: !2542)
!2609 = !DILocation(line: 663, column: 7, scope: !2542)
!2610 = !DILocation(line: 663, column: 22, scope: !2542)
!2611 = !DILocation(line: 664, column: 7, scope: !2612)
!2612 = distinct !DILexicalBlock(scope: !2542, file: !1, line: 664, column: 7)
!2613 = !DILocation(line: 664, column: 11, scope: !2612)
!2614 = !DILocation(line: 664, column: 26, scope: !2612)
!2615 = !DILocation(line: 664, column: 7, scope: !2542)
!2616 = !DILocation(line: 665, column: 23, scope: !2617)
!2617 = distinct !DILexicalBlock(scope: !2612, file: !1, line: 664, column: 35)
!2618 = !DILocation(line: 665, column: 26, scope: !2617)
!2619 = !DILocation(line: 665, column: 4, scope: !2617)
!2620 = !DILocation(line: 667, column: 4, scope: !2617)
!2621 = !DILocation(line: 667, column: 7, scope: !2617)
!2622 = !DILocation(line: 667, column: 15, scope: !2617)
!2623 = !DILocation(line: 667, column: 21, scope: !2617)
!2624 = !DILocation(line: 668, column: 4, scope: !2617)
!2625 = !DILocation(line: 674, column: 18, scope: !2542)
!2626 = !DILocation(line: 674, column: 22, scope: !2542)
!2627 = !DILocation(line: 674, column: 7, scope: !2542)
!2628 = !DILocation(line: 674, column: 5, scope: !2542)
!2629 = !DILocation(line: 675, column: 8, scope: !2542)
!2630 = !DILocation(line: 675, column: 5, scope: !2542)
!2631 = !DILocation(line: 676, column: 7, scope: !2632)
!2632 = distinct !DILexicalBlock(scope: !2542, file: !1, line: 676, column: 7)
!2633 = !DILocation(line: 676, column: 9, scope: !2632)
!2634 = !DILocation(line: 676, column: 7, scope: !2542)
!2635 = !DILocation(line: 677, column: 8, scope: !2632)
!2636 = !DILocation(line: 677, column: 21, scope: !2632)
!2637 = !DILocation(line: 677, column: 19, scope: !2632)
!2638 = !DILocation(line: 677, column: 6, scope: !2632)
!2639 = !DILocation(line: 677, column: 4, scope: !2632)
!2640 = !DILocation(line: 683, column: 14, scope: !2542)
!2641 = !DILocation(line: 683, column: 18, scope: !2542)
!2642 = !DILocation(line: 683, column: 35, scope: !2542)
!2643 = !DILocation(line: 683, column: 33, scope: !2542)
!2644 = !DILocation(line: 683, column: 3, scope: !2542)
!2645 = !DILocation(line: 683, column: 7, scope: !2542)
!2646 = !DILocation(line: 683, column: 12, scope: !2542)
!2647 = !DILocation(line: 684, column: 19, scope: !2542)
!2648 = !DILocation(line: 684, column: 27, scope: !2542)
!2649 = !DILocation(line: 684, column: 25, scope: !2542)
!2650 = !DILocation(line: 684, column: 3, scope: !2542)
!2651 = !DILocation(line: 684, column: 7, scope: !2542)
!2652 = !DILocation(line: 684, column: 17, scope: !2542)
!2653 = !DILocation(line: 685, column: 2, scope: !2542)
!2654 = !DILocation(line: 686, column: 2, scope: !391)
!2655 = !DILocation(line: 687, column: 1, scope: !391)
!2656 = !DILocalVariable(name: "a", arg: 1, scope: !396, file: !1, line: 853, type: !43)
!2657 = !DILocation(line: 853, column: 38, scope: !396)
!2658 = !DILocalVariable(name: "t", arg: 2, scope: !396, file: !1, line: 853, type: !153)
!2659 = !DILocation(line: 853, column: 54, scope: !396)
!2660 = !DILocalVariable(name: "entry", arg: 3, scope: !396, file: !1, line: 854, type: !69)
!2661 = !DILocation(line: 854, column: 27, scope: !396)
!2662 = !DILocalVariable(name: "st", scope: !396, file: !1, line: 856, type: !412)
!2663 = !DILocation(line: 856, column: 21, scope: !396)
!2664 = !DILocalVariable(name: "lst", scope: !396, file: !1, line: 857, type: !412)
!2665 = !DILocation(line: 857, column: 21, scope: !396)
!2666 = !DILocalVariable(name: "name", scope: !396, file: !1, line: 858, type: !119)
!2667 = !DILocation(line: 858, column: 14, scope: !396)
!2668 = !DILocalVariable(name: "descend", scope: !396, file: !1, line: 859, type: !62)
!2669 = !DILocation(line: 859, column: 6, scope: !396)
!2670 = !DILocalVariable(name: "r", scope: !396, file: !1, line: 859, type: !62)
!2671 = !DILocation(line: 859, column: 15, scope: !396)
!2672 = !DILocation(line: 861, column: 5, scope: !396)
!2673 = !DILocation(line: 862, column: 6, scope: !396)
!2674 = !DILocation(line: 863, column: 2, scope: !396)
!2675 = !DILocation(line: 863, column: 5, scope: !396)
!2676 = !DILocation(line: 863, column: 13, scope: !396)
!2677 = !DILocation(line: 864, column: 2, scope: !396)
!2678 = !DILocation(line: 865, column: 21, scope: !2679)
!2679 = distinct !DILexicalBlock(scope: !396, file: !1, line: 864, column: 5)
!2680 = !DILocation(line: 865, column: 11, scope: !2679)
!2681 = !DILocation(line: 865, column: 3, scope: !2679)
!2682 = !DILocation(line: 867, column: 23, scope: !2683)
!2683 = distinct !DILexicalBlock(scope: !2679, file: !1, line: 865, column: 25)
!2684 = !DILocation(line: 867, column: 26, scope: !2683)
!2685 = !DILocation(line: 867, column: 35, scope: !2683)
!2686 = !DILocation(line: 867, column: 38, scope: !2683)
!2687 = !DILocation(line: 869, column: 26, scope: !2683)
!2688 = !DILocation(line: 869, column: 8, scope: !2683)
!2689 = !DILocation(line: 867, column: 4, scope: !2683)
!2690 = !DILocation(line: 870, column: 4, scope: !2683)
!2691 = !DILocation(line: 870, column: 7, scope: !2683)
!2692 = !DILocation(line: 870, column: 15, scope: !2683)
!2693 = !DILocation(line: 870, column: 21, scope: !2683)
!2694 = !DILocation(line: 871, column: 27, scope: !2683)
!2695 = !DILocation(line: 871, column: 4, scope: !2683)
!2696 = !DILocation(line: 872, column: 4, scope: !2683)
!2697 = !DILocation(line: 874, column: 23, scope: !2683)
!2698 = !DILocation(line: 874, column: 26, scope: !2683)
!2699 = !DILocation(line: 876, column: 26, scope: !2683)
!2700 = !DILocation(line: 876, column: 8, scope: !2683)
!2701 = !DILocation(line: 874, column: 4, scope: !2683)
!2702 = !DILocation(line: 877, column: 27, scope: !2683)
!2703 = !DILocation(line: 877, column: 4, scope: !2683)
!2704 = !DILocation(line: 878, column: 4, scope: !2683)
!2705 = !DILocation(line: 880, column: 27, scope: !2683)
!2706 = !DILocation(line: 880, column: 4, scope: !2683)
!2707 = !DILocation(line: 881, column: 4, scope: !2683)
!2708 = !DILocation(line: 884, column: 4, scope: !2683)
!2709 = !DILocation(line: 886, column: 29, scope: !2683)
!2710 = !DILocation(line: 886, column: 10, scope: !2683)
!2711 = !DILocation(line: 886, column: 8, scope: !2683)
!2712 = !DILocation(line: 887, column: 8, scope: !2713)
!2713 = distinct !DILexicalBlock(scope: !2683, file: !1, line: 887, column: 8)
!2714 = !DILocation(line: 887, column: 12, scope: !2713)
!2715 = !DILocation(line: 887, column: 8, scope: !2683)
!2716 = !DILocation(line: 888, column: 24, scope: !2717)
!2717 = distinct !DILexicalBlock(scope: !2713, file: !1, line: 887, column: 21)
!2718 = !DILocation(line: 888, column: 27, scope: !2717)
!2719 = !DILocation(line: 888, column: 36, scope: !2717)
!2720 = !DILocation(line: 890, column: 27, scope: !2717)
!2721 = !DILocation(line: 890, column: 9, scope: !2717)
!2722 = !DILocation(line: 888, column: 5, scope: !2717)
!2723 = !DILocation(line: 891, column: 28, scope: !2717)
!2724 = !DILocation(line: 891, column: 5, scope: !2717)
!2725 = !DILocation(line: 892, column: 5, scope: !2717)
!2726 = !DILocation(line: 894, column: 4, scope: !2683)
!2727 = !DILocation(line: 896, column: 2, scope: !2679)
!2728 = !DILocation(line: 896, column: 11, scope: !2729)
!2729 = !DILexicalBlockFile(scope: !396, file: !1, discriminator: 1)
!2730 = !DILocation(line: 896, column: 15, scope: !2729)
!2731 = !DILocation(line: 896, column: 2, scope: !2729)
!2732 = !DILocation(line: 911, column: 30, scope: !396)
!2733 = !DILocation(line: 911, column: 55, scope: !396)
!2734 = !DILocation(line: 911, column: 37, scope: !396)
!2735 = !DILocation(line: 911, column: 2, scope: !2729)
!2736 = !DILocation(line: 915, column: 6, scope: !2737)
!2737 = distinct !DILexicalBlock(scope: !396, file: !1, line: 915, column: 6)
!2738 = !DILocation(line: 915, column: 9, scope: !2737)
!2739 = !DILocation(line: 915, column: 6, scope: !396)
!2740 = !DILocation(line: 916, column: 35, scope: !2741)
!2741 = distinct !DILexicalBlock(scope: !2737, file: !1, line: 915, column: 19)
!2742 = !DILocation(line: 916, column: 38, scope: !2741)
!2743 = !DILocation(line: 916, column: 48, scope: !2741)
!2744 = !DILocation(line: 916, column: 7, scope: !2741)
!2745 = !DILocation(line: 916, column: 5, scope: !2741)
!2746 = !DILocation(line: 917, column: 7, scope: !2747)
!2747 = distinct !DILexicalBlock(scope: !2741, file: !1, line: 917, column: 7)
!2748 = !DILocation(line: 917, column: 9, scope: !2747)
!2749 = !DILocation(line: 917, column: 7, scope: !2741)
!2750 = !DILocation(line: 918, column: 24, scope: !2751)
!2751 = distinct !DILexicalBlock(scope: !2747, file: !1, line: 917, column: 14)
!2752 = !DILocation(line: 918, column: 27, scope: !2751)
!2753 = !DILocation(line: 918, column: 37, scope: !2751)
!2754 = !DILocation(line: 919, column: 44, scope: !2751)
!2755 = !DILocation(line: 919, column: 47, scope: !2751)
!2756 = !DILocation(line: 919, column: 23, scope: !2751)
!2757 = !DILocation(line: 918, column: 4, scope: !2751)
!2758 = !DILocation(line: 920, column: 12, scope: !2751)
!2759 = !DILocation(line: 920, column: 4, scope: !2751)
!2760 = !DILocation(line: 922, column: 7, scope: !2761)
!2761 = distinct !DILexicalBlock(scope: !2741, file: !1, line: 922, column: 7)
!2762 = !DILocation(line: 922, column: 7, scope: !2741)
!2763 = !DILocation(line: 923, column: 8, scope: !2764)
!2764 = distinct !DILexicalBlock(scope: !2765, file: !1, line: 923, column: 8)
!2765 = distinct !DILexicalBlock(scope: !2761, file: !1, line: 922, column: 10)
!2766 = !DILocation(line: 923, column: 11, scope: !2764)
!2767 = !DILocation(line: 923, column: 8, scope: !2765)
!2768 = !DILocation(line: 924, column: 5, scope: !2764)
!2769 = !DILocation(line: 924, column: 8, scope: !2764)
!2770 = !DILocation(line: 924, column: 27, scope: !2764)
!2771 = !DILocation(line: 924, column: 30, scope: !2764)
!2772 = !DILocation(line: 925, column: 9, scope: !2764)
!2773 = !DILocation(line: 925, column: 12, scope: !2764)
!2774 = !DILocation(line: 925, column: 30, scope: !2764)
!2775 = !DILocation(line: 926, column: 4, scope: !2765)
!2776 = !DILocation(line: 928, column: 2, scope: !2741)
!2777 = !DILocation(line: 933, column: 9, scope: !396)
!2778 = !DILocation(line: 933, column: 12, scope: !396)
!2779 = !DILocation(line: 933, column: 2, scope: !396)
!2780 = !DILocation(line: 936, column: 3, scope: !2781)
!2781 = distinct !DILexicalBlock(scope: !396, file: !1, line: 933, column: 26)
!2782 = !DILocation(line: 936, column: 6, scope: !2781)
!2783 = !DILocation(line: 936, column: 19, scope: !2781)
!2784 = !DILocation(line: 941, column: 33, scope: !2781)
!2785 = !DILocation(line: 941, column: 13, scope: !2781)
!2786 = !DILocation(line: 941, column: 11, scope: !2781)
!2787 = !DILocation(line: 943, column: 3, scope: !2781)
!2788 = !DILocation(line: 943, column: 6, scope: !2781)
!2789 = !DILocation(line: 943, column: 19, scope: !2781)
!2790 = !DILocation(line: 944, column: 3, scope: !2781)
!2791 = !DILocation(line: 944, column: 6, scope: !2781)
!2792 = !DILocation(line: 944, column: 22, scope: !2781)
!2793 = !DILocation(line: 946, column: 26, scope: !2781)
!2794 = !DILocation(line: 946, column: 8, scope: !2781)
!2795 = !DILocation(line: 946, column: 6, scope: !2781)
!2796 = !DILocation(line: 947, column: 7, scope: !2797)
!2797 = distinct !DILexicalBlock(scope: !2781, file: !1, line: 947, column: 7)
!2798 = !DILocation(line: 947, column: 10, scope: !2797)
!2799 = !DILocation(line: 947, column: 18, scope: !2797)
!2800 = !DILocation(line: 947, column: 52, scope: !2801)
!2801 = !DILexicalBlockFile(scope: !2797, file: !1, discriminator: 1)
!2802 = !DILocation(line: 947, column: 55, scope: !2801)
!2803 = !DILocation(line: 947, column: 22, scope: !2801)
!2804 = !DILocation(line: 947, column: 7, scope: !2801)
!2805 = !DILocation(line: 948, column: 4, scope: !2797)
!2806 = !DILocation(line: 947, column: 57, scope: !2807)
!2807 = !DILexicalBlockFile(scope: !2797, file: !1, discriminator: 2)
!2808 = !DILocation(line: 954, column: 42, scope: !2781)
!2809 = !DILocation(line: 954, column: 13, scope: !2781)
!2810 = !DILocation(line: 954, column: 11, scope: !2781)
!2811 = !DILocation(line: 956, column: 3, scope: !2781)
!2812 = !DILocation(line: 956, column: 6, scope: !2781)
!2813 = !DILocation(line: 956, column: 19, scope: !2781)
!2814 = !DILocation(line: 957, column: 3, scope: !2781)
!2815 = !DILocation(line: 957, column: 6, scope: !2781)
!2816 = !DILocation(line: 957, column: 22, scope: !2781)
!2817 = !DILocation(line: 959, column: 8, scope: !2781)
!2818 = !DILocation(line: 959, column: 6, scope: !2781)
!2819 = !DILocation(line: 960, column: 3, scope: !2781)
!2820 = !DILocation(line: 963, column: 32, scope: !2821)
!2821 = distinct !DILexicalBlock(scope: !396, file: !1, line: 963, column: 6)
!2822 = !DILocation(line: 963, column: 35, scope: !2821)
!2823 = !DILocation(line: 963, column: 39, scope: !2821)
!2824 = !DILocation(line: 963, column: 6, scope: !2821)
!2825 = !DILocation(line: 963, column: 47, scope: !2821)
!2826 = !DILocation(line: 963, column: 6, scope: !396)
!2827 = !DILocation(line: 964, column: 3, scope: !2828)
!2828 = distinct !DILexicalBlock(scope: !2821, file: !1, line: 963, column: 62)
!2829 = !DILocation(line: 964, column: 6, scope: !2828)
!2830 = !DILocation(line: 964, column: 14, scope: !2828)
!2831 = !DILocation(line: 964, column: 20, scope: !2828)
!2832 = !DILocation(line: 965, column: 26, scope: !2828)
!2833 = !DILocation(line: 965, column: 3, scope: !2828)
!2834 = !DILocation(line: 966, column: 3, scope: !2828)
!2835 = !DILocation(line: 968, column: 6, scope: !2836)
!2836 = distinct !DILexicalBlock(scope: !396, file: !1, line: 968, column: 6)
!2837 = !DILocation(line: 968, column: 9, scope: !2836)
!2838 = !DILocation(line: 968, column: 31, scope: !2836)
!2839 = !DILocation(line: 968, column: 6, scope: !396)
!2840 = !DILocation(line: 969, column: 30, scope: !2836)
!2841 = !DILocation(line: 969, column: 33, scope: !2836)
!2842 = !DILocation(line: 969, column: 3, scope: !2836)
!2843 = !DILocation(line: 969, column: 6, scope: !2836)
!2844 = !DILocation(line: 969, column: 28, scope: !2836)
!2845 = !DILocation(line: 970, column: 6, scope: !2846)
!2846 = distinct !DILexicalBlock(scope: !396, file: !1, line: 970, column: 6)
!2847 = !DILocation(line: 970, column: 9, scope: !2846)
!2848 = !DILocation(line: 970, column: 15, scope: !2846)
!2849 = !DILocation(line: 970, column: 6, scope: !396)
!2850 = !DILocation(line: 971, column: 7, scope: !2851)
!2851 = distinct !DILexicalBlock(scope: !2852, file: !1, line: 971, column: 7)
!2852 = distinct !DILexicalBlock(scope: !2846, file: !1, line: 970, column: 54)
!2853 = !DILocation(line: 971, column: 10, scope: !2851)
!2854 = !DILocation(line: 971, column: 35, scope: !2851)
!2855 = !DILocation(line: 971, column: 38, scope: !2851)
!2856 = !DILocation(line: 971, column: 32, scope: !2851)
!2857 = !DILocation(line: 971, column: 7, scope: !2852)
!2858 = !DILocation(line: 972, column: 12, scope: !2851)
!2859 = !DILocation(line: 972, column: 4, scope: !2851)
!2860 = !DILocation(line: 973, column: 2, scope: !2852)
!2861 = !DILocation(line: 974, column: 15, scope: !396)
!2862 = !DILocation(line: 974, column: 2, scope: !396)
!2863 = !DILocation(line: 974, column: 5, scope: !396)
!2864 = !DILocation(line: 974, column: 13, scope: !396)
!2865 = !DILocation(line: 980, column: 6, scope: !2866)
!2866 = distinct !DILexicalBlock(scope: !396, file: !1, line: 980, column: 6)
!2867 = !DILocation(line: 980, column: 9, scope: !2866)
!2868 = !DILocation(line: 980, column: 15, scope: !2866)
!2869 = !DILocation(line: 980, column: 6, scope: !396)
!2870 = !DILocation(line: 988, column: 7, scope: !2871)
!2871 = distinct !DILexicalBlock(scope: !2872, file: !1, line: 988, column: 7)
!2872 = distinct !DILexicalBlock(scope: !2866, file: !1, line: 980, column: 48)
!2873 = !DILocation(line: 988, column: 28, scope: !2871)
!2874 = !DILocation(line: 988, column: 31, scope: !2875)
!2875 = !DILexicalBlockFile(scope: !2871, file: !1, discriminator: 1)
!2876 = !DILocation(line: 988, column: 7, scope: !2875)
!2877 = !DILocalVariable(name: "stflags", scope: !2878, file: !1, line: 989, type: !62)
!2878 = distinct !DILexicalBlock(scope: !2871, file: !1, line: 988, column: 53)
!2879 = !DILocation(line: 989, column: 8, scope: !2878)
!2880 = !DILocation(line: 991, column: 38, scope: !2878)
!2881 = !DILocation(line: 992, column: 33, scope: !2878)
!2882 = !DILocation(line: 992, column: 8, scope: !2878)
!2883 = !DILocation(line: 991, column: 18, scope: !2878)
!2884 = !DILocation(line: 991, column: 4, scope: !2878)
!2885 = !DILocation(line: 991, column: 7, scope: !2878)
!2886 = !DILocation(line: 991, column: 16, scope: !2878)
!2887 = !DILocation(line: 994, column: 34, scope: !2878)
!2888 = !DILocation(line: 994, column: 37, scope: !2878)
!2889 = !DILocation(line: 994, column: 4, scope: !2878)
!2890 = !DILocation(line: 995, column: 8, scope: !2891)
!2891 = distinct !DILexicalBlock(scope: !2878, file: !1, line: 995, column: 8)
!2892 = !DILocation(line: 995, column: 11, scope: !2891)
!2893 = !DILocation(line: 995, column: 20, scope: !2891)
!2894 = !DILocation(line: 995, column: 8, scope: !2878)
!2895 = !DILocation(line: 996, column: 15, scope: !2896)
!2896 = distinct !DILexicalBlock(scope: !2891, file: !1, line: 995, column: 26)
!2897 = !DILocation(line: 996, column: 18, scope: !2896)
!2898 = !DILocation(line: 996, column: 9, scope: !2896)
!2899 = !DILocation(line: 996, column: 7, scope: !2896)
!2900 = !DILocation(line: 1004, column: 9, scope: !2901)
!2901 = distinct !DILexicalBlock(scope: !2896, file: !1, line: 1004, column: 9)
!2902 = !DILocation(line: 1004, column: 11, scope: !2901)
!2903 = !DILocation(line: 1004, column: 16, scope: !2901)
!2904 = !DILocation(line: 1004, column: 20, scope: !2905)
!2905 = !DILexicalBlockFile(scope: !2901, file: !1, discriminator: 1)
!2906 = !DILocation(line: 1004, column: 28, scope: !2905)
!2907 = !DILocation(line: 1004, column: 44, scope: !2905)
!2908 = !DILocation(line: 1004, column: 9, scope: !2905)
!2909 = !DILocation(line: 1008, column: 6, scope: !2901)
!2910 = !DILocation(line: 1009, column: 4, scope: !2896)
!2911 = !DILocation(line: 1010, column: 3, scope: !2878)
!2912 = !DILocation(line: 1012, column: 2, scope: !2872)
!2913 = !DILocation(line: 1014, column: 26, scope: !396)
!2914 = !DILocation(line: 1014, column: 33, scope: !396)
!2915 = !DILocation(line: 1014, column: 2, scope: !396)
!2916 = !DILocation(line: 1019, column: 46, scope: !396)
!2917 = !DILocation(line: 1019, column: 26, scope: !396)
!2918 = !DILocation(line: 1019, column: 2, scope: !396)
!2919 = !DILocation(line: 1019, column: 5, scope: !396)
!2920 = !DILocation(line: 1019, column: 18, scope: !396)
!2921 = !DILocation(line: 1019, column: 24, scope: !396)
!2922 = !DILocation(line: 1020, column: 56, scope: !396)
!2923 = !DILocation(line: 1020, column: 31, scope: !396)
!2924 = !DILocation(line: 1020, column: 2, scope: !396)
!2925 = !DILocation(line: 1020, column: 5, scope: !396)
!2926 = !DILocation(line: 1020, column: 18, scope: !396)
!2927 = !DILocation(line: 1020, column: 29, scope: !396)
!2928 = !DILocation(line: 1021, column: 46, scope: !396)
!2929 = !DILocation(line: 1021, column: 26, scope: !396)
!2930 = !DILocation(line: 1021, column: 2, scope: !396)
!2931 = !DILocation(line: 1021, column: 5, scope: !396)
!2932 = !DILocation(line: 1021, column: 18, scope: !396)
!2933 = !DILocation(line: 1021, column: 24, scope: !396)
!2934 = !DILocation(line: 1022, column: 56, scope: !396)
!2935 = !DILocation(line: 1022, column: 31, scope: !396)
!2936 = !DILocation(line: 1022, column: 2, scope: !396)
!2937 = !DILocation(line: 1022, column: 5, scope: !396)
!2938 = !DILocation(line: 1022, column: 18, scope: !396)
!2939 = !DILocation(line: 1022, column: 29, scope: !396)
!2940 = !DILocation(line: 1023, column: 52, scope: !396)
!2941 = !DILocation(line: 1023, column: 29, scope: !396)
!2942 = !DILocation(line: 1023, column: 2, scope: !396)
!2943 = !DILocation(line: 1023, column: 5, scope: !396)
!2944 = !DILocation(line: 1023, column: 18, scope: !396)
!2945 = !DILocation(line: 1023, column: 27, scope: !396)
!2946 = !DILocation(line: 1024, column: 28, scope: !396)
!2947 = !DILocation(line: 1024, column: 31, scope: !396)
!2948 = !DILocation(line: 1024, column: 51, scope: !396)
!2949 = !DILocation(line: 1024, column: 2, scope: !396)
!2950 = !DILocation(line: 1024, column: 5, scope: !396)
!2951 = !DILocation(line: 1024, column: 18, scope: !396)
!2952 = !DILocation(line: 1024, column: 26, scope: !396)
!2953 = !DILocation(line: 1029, column: 6, scope: !2954)
!2954 = distinct !DILexicalBlock(scope: !396, file: !1, line: 1029, column: 6)
!2955 = !DILocation(line: 1029, column: 9, scope: !2954)
!2956 = !DILocation(line: 1029, column: 6, scope: !396)
!2957 = !DILocation(line: 1030, column: 35, scope: !2958)
!2958 = distinct !DILexicalBlock(scope: !2954, file: !1, line: 1029, column: 19)
!2959 = !DILocation(line: 1030, column: 38, scope: !2958)
!2960 = !DILocation(line: 1030, column: 48, scope: !2958)
!2961 = !DILocation(line: 1030, column: 7, scope: !2958)
!2962 = !DILocation(line: 1030, column: 5, scope: !2958)
!2963 = !DILocation(line: 1031, column: 7, scope: !2964)
!2964 = distinct !DILexicalBlock(scope: !2958, file: !1, line: 1031, column: 7)
!2965 = !DILocation(line: 1031, column: 9, scope: !2964)
!2966 = !DILocation(line: 1031, column: 7, scope: !2958)
!2967 = !DILocation(line: 1032, column: 24, scope: !2968)
!2968 = distinct !DILexicalBlock(scope: !2964, file: !1, line: 1031, column: 14)
!2969 = !DILocation(line: 1032, column: 27, scope: !2968)
!2970 = !DILocation(line: 1032, column: 37, scope: !2968)
!2971 = !DILocation(line: 1033, column: 44, scope: !2968)
!2972 = !DILocation(line: 1033, column: 47, scope: !2968)
!2973 = !DILocation(line: 1033, column: 23, scope: !2968)
!2974 = !DILocation(line: 1032, column: 4, scope: !2968)
!2975 = !DILocation(line: 1034, column: 12, scope: !2968)
!2976 = !DILocation(line: 1034, column: 4, scope: !2968)
!2977 = !DILocation(line: 1036, column: 7, scope: !2978)
!2978 = distinct !DILexicalBlock(scope: !2958, file: !1, line: 1036, column: 7)
!2979 = !DILocation(line: 1036, column: 7, scope: !2958)
!2980 = !DILocation(line: 1037, column: 8, scope: !2981)
!2981 = distinct !DILexicalBlock(scope: !2982, file: !1, line: 1037, column: 8)
!2982 = distinct !DILexicalBlock(scope: !2978, file: !1, line: 1036, column: 10)
!2983 = !DILocation(line: 1037, column: 11, scope: !2981)
!2984 = !DILocation(line: 1037, column: 8, scope: !2982)
!2985 = !DILocation(line: 1038, column: 5, scope: !2981)
!2986 = !DILocation(line: 1038, column: 8, scope: !2981)
!2987 = !DILocation(line: 1038, column: 27, scope: !2981)
!2988 = !DILocation(line: 1038, column: 30, scope: !2981)
!2989 = !DILocation(line: 1039, column: 9, scope: !2981)
!2990 = !DILocation(line: 1039, column: 12, scope: !2981)
!2991 = !DILocation(line: 1039, column: 30, scope: !2981)
!2992 = !DILocation(line: 1040, column: 4, scope: !2982)
!2993 = !DILocation(line: 1042, column: 2, scope: !2958)
!2994 = !DILocation(line: 1045, column: 35, scope: !396)
!2995 = !DILocation(line: 1045, column: 38, scope: !396)
!2996 = !DILocation(line: 1045, column: 66, scope: !396)
!2997 = !DILocation(line: 1045, column: 48, scope: !396)
!2998 = !DILocation(line: 1045, column: 9, scope: !2729)
!2999 = !DILocation(line: 1045, column: 7, scope: !396)
!3000 = !DILocation(line: 1046, column: 6, scope: !3001)
!3001 = distinct !DILexicalBlock(scope: !396, file: !1, line: 1046, column: 6)
!3002 = !DILocation(line: 1046, column: 11, scope: !3001)
!3003 = !DILocation(line: 1046, column: 6, scope: !396)
!3004 = !DILocation(line: 1047, column: 28, scope: !3001)
!3005 = !DILocation(line: 1047, column: 35, scope: !3001)
!3006 = !DILocation(line: 1047, column: 3, scope: !3001)
!3007 = !DILocation(line: 1048, column: 35, scope: !396)
!3008 = !DILocation(line: 1048, column: 38, scope: !396)
!3009 = !DILocation(line: 1048, column: 66, scope: !396)
!3010 = !DILocation(line: 1048, column: 48, scope: !396)
!3011 = !DILocation(line: 1048, column: 9, scope: !2729)
!3012 = !DILocation(line: 1048, column: 7, scope: !396)
!3013 = !DILocation(line: 1049, column: 6, scope: !3014)
!3014 = distinct !DILexicalBlock(scope: !396, file: !1, line: 1049, column: 6)
!3015 = !DILocation(line: 1049, column: 11, scope: !3014)
!3016 = !DILocation(line: 1049, column: 6, scope: !396)
!3017 = !DILocation(line: 1050, column: 28, scope: !3014)
!3018 = !DILocation(line: 1050, column: 35, scope: !3014)
!3019 = !DILocation(line: 1050, column: 3, scope: !3014)
!3020 = !DILocation(line: 1055, column: 6, scope: !3021)
!3021 = distinct !DILexicalBlock(scope: !396, file: !1, line: 1055, column: 6)
!3022 = !DILocation(line: 1055, column: 9, scope: !3021)
!3023 = !DILocation(line: 1055, column: 6, scope: !396)
!3024 = !DILocation(line: 1056, column: 36, scope: !3025)
!3025 = distinct !DILexicalBlock(scope: !3021, file: !1, line: 1055, column: 19)
!3026 = !DILocation(line: 1056, column: 39, scope: !3025)
!3027 = !DILocation(line: 1056, column: 49, scope: !3025)
!3028 = !DILocation(line: 1056, column: 7, scope: !3025)
!3029 = !DILocation(line: 1056, column: 5, scope: !3025)
!3030 = !DILocation(line: 1057, column: 7, scope: !3031)
!3031 = distinct !DILexicalBlock(scope: !3025, file: !1, line: 1057, column: 7)
!3032 = !DILocation(line: 1057, column: 9, scope: !3031)
!3033 = !DILocation(line: 1057, column: 7, scope: !3025)
!3034 = !DILocation(line: 1058, column: 24, scope: !3035)
!3035 = distinct !DILexicalBlock(scope: !3031, file: !1, line: 1057, column: 14)
!3036 = !DILocation(line: 1058, column: 27, scope: !3035)
!3037 = !DILocation(line: 1058, column: 37, scope: !3035)
!3038 = !DILocation(line: 1059, column: 44, scope: !3035)
!3039 = !DILocation(line: 1059, column: 47, scope: !3035)
!3040 = !DILocation(line: 1059, column: 23, scope: !3035)
!3041 = !DILocation(line: 1058, column: 4, scope: !3035)
!3042 = !DILocation(line: 1060, column: 12, scope: !3035)
!3043 = !DILocation(line: 1060, column: 4, scope: !3035)
!3044 = !DILocation(line: 1062, column: 7, scope: !3045)
!3045 = distinct !DILexicalBlock(scope: !3025, file: !1, line: 1062, column: 7)
!3046 = !DILocation(line: 1062, column: 7, scope: !3025)
!3047 = !DILocation(line: 1063, column: 8, scope: !3048)
!3048 = distinct !DILexicalBlock(scope: !3049, file: !1, line: 1063, column: 8)
!3049 = distinct !DILexicalBlock(scope: !3045, file: !1, line: 1062, column: 10)
!3050 = !DILocation(line: 1063, column: 11, scope: !3048)
!3051 = !DILocation(line: 1063, column: 8, scope: !3049)
!3052 = !DILocation(line: 1064, column: 5, scope: !3048)
!3053 = !DILocation(line: 1064, column: 8, scope: !3048)
!3054 = !DILocation(line: 1064, column: 27, scope: !3048)
!3055 = !DILocation(line: 1064, column: 30, scope: !3048)
!3056 = !DILocation(line: 1065, column: 9, scope: !3048)
!3057 = !DILocation(line: 1065, column: 12, scope: !3048)
!3058 = !DILocation(line: 1065, column: 30, scope: !3048)
!3059 = !DILocation(line: 1066, column: 4, scope: !3049)
!3060 = !DILocation(line: 1068, column: 2, scope: !3025)
!3061 = !DILocation(line: 1073, column: 6, scope: !3062)
!3062 = distinct !DILexicalBlock(scope: !396, file: !1, line: 1073, column: 6)
!3063 = !DILocation(line: 1073, column: 9, scope: !3062)
!3064 = !DILocation(line: 1073, column: 6, scope: !396)
!3065 = !DILocation(line: 1074, column: 8, scope: !3066)
!3066 = distinct !DILexicalBlock(scope: !3067, file: !1, line: 1074, column: 7)
!3067 = distinct !DILexicalBlock(scope: !3062, file: !1, line: 1073, column: 31)
!3068 = !DILocation(line: 1074, column: 11, scope: !3066)
!3069 = !DILocation(line: 1074, column: 34, scope: !3066)
!3070 = !DILocation(line: 1074, column: 37, scope: !3066)
!3071 = !DILocation(line: 1075, column: 7, scope: !3066)
!3072 = !DILocation(line: 1075, column: 10, scope: !3066)
!3073 = !DILocation(line: 1075, column: 32, scope: !3066)
!3074 = !DILocation(line: 1074, column: 7, scope: !3067)
!3075 = !DILocation(line: 1076, column: 4, scope: !3066)
!3076 = !DILocation(line: 1077, column: 2, scope: !3067)
!3077 = !DILocation(line: 1082, column: 32, scope: !396)
!3078 = !DILocation(line: 1082, column: 64, scope: !396)
!3079 = !DILocation(line: 1082, column: 39, scope: !396)
!3080 = !DILocation(line: 1082, column: 2, scope: !2729)
!3081 = !DILocation(line: 1083, column: 42, scope: !396)
!3082 = !DILocation(line: 1083, column: 45, scope: !396)
!3083 = !DILocation(line: 1083, column: 55, scope: !396)
!3084 = !DILocation(line: 1084, column: 3, scope: !396)
!3085 = !DILocation(line: 1084, column: 6, scope: !396)
!3086 = !DILocation(line: 1084, column: 16, scope: !396)
!3087 = !DILocation(line: 1083, column: 6, scope: !396)
!3088 = !DILocation(line: 1083, column: 4, scope: !396)
!3089 = !DILocation(line: 1086, column: 10, scope: !396)
!3090 = !DILocation(line: 1086, column: 2, scope: !396)
!3091 = !DILocation(line: 1087, column: 1, scope: !396)
!3092 = !DILocalVariable(name: "a", arg: 1, scope: !426, file: !1, line: 1173, type: !43)
!3093 = !DILocation(line: 1173, column: 40, scope: !426)
!3094 = !DILocalVariable(name: "entry", arg: 2, scope: !426, file: !1, line: 1173, type: !69)
!3095 = !DILocation(line: 1173, column: 65, scope: !426)
!3096 = !DILocalVariable(name: "t", scope: !426, file: !1, line: 1175, type: !153)
!3097 = !DILocation(line: 1175, column: 15, scope: !426)
!3098 = !DILocation(line: 1175, column: 19, scope: !426)
!3099 = !DILocation(line: 1175, column: 22, scope: !426)
!3100 = !DILocalVariable(name: "length", scope: !426, file: !1, line: 1176, type: !91)
!3101 = !DILocation(line: 1176, column: 10, scope: !426)
!3102 = !DILocalVariable(name: "offset", scope: !426, file: !1, line: 1176, type: !91)
!3103 = !DILocation(line: 1176, column: 18, scope: !426)
!3104 = !DILocalVariable(name: "i", scope: !426, file: !1, line: 1177, type: !62)
!3105 = !DILocation(line: 1177, column: 6, scope: !426)
!3106 = !DILocation(line: 1179, column: 47, scope: !426)
!3107 = !DILocation(line: 1179, column: 20, scope: !426)
!3108 = !DILocation(line: 1179, column: 2, scope: !426)
!3109 = !DILocation(line: 1179, column: 5, scope: !426)
!3110 = !DILocation(line: 1179, column: 18, scope: !426)
!3111 = !DILocation(line: 1180, column: 6, scope: !3112)
!3112 = distinct !DILexicalBlock(scope: !426, file: !1, line: 1180, column: 6)
!3113 = !DILocation(line: 1180, column: 9, scope: !3112)
!3114 = !DILocation(line: 1180, column: 21, scope: !3112)
!3115 = !DILocation(line: 1180, column: 26, scope: !3112)
!3116 = !DILocation(line: 1180, column: 29, scope: !3112)
!3117 = !DILocation(line: 1180, column: 24, scope: !3112)
!3118 = !DILocation(line: 1180, column: 6, scope: !426)
!3119 = !DILocation(line: 1181, column: 8, scope: !3120)
!3120 = distinct !DILexicalBlock(scope: !3112, file: !1, line: 1180, column: 47)
!3121 = !DILocation(line: 1181, column: 11, scope: !3120)
!3122 = !DILocation(line: 1181, column: 3, scope: !3120)
!3123 = !DILocation(line: 1182, column: 25, scope: !3120)
!3124 = !DILocation(line: 1182, column: 28, scope: !3120)
!3125 = !DILocation(line: 1182, column: 41, scope: !3120)
!3126 = !DILocation(line: 1182, column: 3, scope: !3120)
!3127 = !DILocation(line: 1182, column: 6, scope: !3120)
!3128 = !DILocation(line: 1182, column: 23, scope: !3120)
!3129 = !DILocation(line: 1184, column: 7, scope: !3120)
!3130 = !DILocation(line: 1184, column: 10, scope: !3120)
!3131 = !DILocation(line: 1183, column: 53, scope: !3120)
!3132 = !DILocation(line: 1183, column: 20, scope: !3120)
!3133 = !DILocation(line: 1183, column: 3, scope: !3120)
!3134 = !DILocation(line: 1183, column: 6, scope: !3120)
!3135 = !DILocation(line: 1183, column: 18, scope: !3120)
!3136 = !DILocation(line: 1185, column: 7, scope: !3137)
!3137 = distinct !DILexicalBlock(scope: !3120, file: !1, line: 1185, column: 7)
!3138 = !DILocation(line: 1185, column: 10, scope: !3137)
!3139 = !DILocation(line: 1185, column: 22, scope: !3137)
!3140 = !DILocation(line: 1185, column: 7, scope: !3120)
!3141 = !DILocation(line: 1186, column: 4, scope: !3142)
!3142 = distinct !DILexicalBlock(scope: !3137, file: !1, line: 1185, column: 31)
!3143 = !DILocation(line: 1186, column: 7, scope: !3142)
!3144 = !DILocation(line: 1186, column: 24, scope: !3142)
!3145 = !DILocation(line: 1187, column: 23, scope: !3142)
!3146 = !DILocation(line: 1187, column: 26, scope: !3142)
!3147 = !DILocation(line: 1187, column: 4, scope: !3142)
!3148 = !DILocation(line: 1189, column: 4, scope: !3142)
!3149 = !DILocation(line: 1189, column: 7, scope: !3142)
!3150 = !DILocation(line: 1189, column: 15, scope: !3142)
!3151 = !DILocation(line: 1189, column: 21, scope: !3142)
!3152 = !DILocation(line: 1190, column: 4, scope: !3142)
!3153 = !DILocation(line: 1192, column: 2, scope: !3120)
!3154 = !DILocation(line: 1193, column: 9, scope: !3155)
!3155 = distinct !DILexicalBlock(scope: !426, file: !1, line: 1193, column: 2)
!3156 = !DILocation(line: 1193, column: 7, scope: !3155)
!3157 = !DILocation(line: 1193, column: 14, scope: !3158)
!3158 = !DILexicalBlockFile(scope: !3159, file: !1, discriminator: 1)
!3159 = distinct !DILexicalBlock(scope: !3155, file: !1, line: 1193, column: 2)
!3160 = !DILocation(line: 1193, column: 18, scope: !3158)
!3161 = !DILocation(line: 1193, column: 21, scope: !3158)
!3162 = !DILocation(line: 1193, column: 16, scope: !3158)
!3163 = !DILocation(line: 1193, column: 2, scope: !3158)
!3164 = !DILocation(line: 1194, column: 29, scope: !3165)
!3165 = distinct !DILexicalBlock(scope: !3159, file: !1, line: 1193, column: 40)
!3166 = !DILocation(line: 1194, column: 3, scope: !3165)
!3167 = !DILocation(line: 1195, column: 30, scope: !3165)
!3168 = !DILocation(line: 1195, column: 18, scope: !3165)
!3169 = !DILocation(line: 1195, column: 3, scope: !3165)
!3170 = !DILocation(line: 1195, column: 6, scope: !3165)
!3171 = !DILocation(line: 1195, column: 21, scope: !3165)
!3172 = !DILocation(line: 1195, column: 28, scope: !3165)
!3173 = !DILocation(line: 1196, column: 30, scope: !3165)
!3174 = !DILocation(line: 1196, column: 18, scope: !3165)
!3175 = !DILocation(line: 1196, column: 3, scope: !3165)
!3176 = !DILocation(line: 1196, column: 6, scope: !3165)
!3177 = !DILocation(line: 1196, column: 21, scope: !3165)
!3178 = !DILocation(line: 1196, column: 28, scope: !3165)
!3179 = !DILocation(line: 1197, column: 2, scope: !3165)
!3180 = !DILocation(line: 1193, column: 36, scope: !3181)
!3181 = !DILexicalBlockFile(scope: !3159, file: !1, discriminator: 2)
!3182 = !DILocation(line: 1193, column: 2, scope: !3181)
!3183 = !DILocation(line: 1198, column: 6, scope: !3184)
!3184 = distinct !DILexicalBlock(scope: !426, file: !1, line: 1198, column: 6)
!3185 = !DILocation(line: 1198, column: 8, scope: !3184)
!3186 = !DILocation(line: 1198, column: 6, scope: !426)
!3187 = !DILocation(line: 1199, column: 18, scope: !3188)
!3188 = distinct !DILexicalBlock(scope: !3184, file: !1, line: 1198, column: 14)
!3189 = !DILocation(line: 1199, column: 3, scope: !3188)
!3190 = !DILocation(line: 1199, column: 6, scope: !3188)
!3191 = !DILocation(line: 1199, column: 21, scope: !3188)
!3192 = !DILocation(line: 1199, column: 28, scope: !3188)
!3193 = !DILocation(line: 1200, column: 49, scope: !3188)
!3194 = !DILocation(line: 1200, column: 30, scope: !3188)
!3195 = !DILocation(line: 1200, column: 18, scope: !3188)
!3196 = !DILocation(line: 1200, column: 3, scope: !3188)
!3197 = !DILocation(line: 1200, column: 6, scope: !3188)
!3198 = !DILocation(line: 1200, column: 21, scope: !3188)
!3199 = !DILocation(line: 1200, column: 28, scope: !3188)
!3200 = !DILocation(line: 1201, column: 2, scope: !3188)
!3201 = !DILocation(line: 1202, column: 49, scope: !3202)
!3202 = distinct !DILexicalBlock(scope: !3184, file: !1, line: 1201, column: 9)
!3203 = !DILocation(line: 1202, column: 30, scope: !3202)
!3204 = !DILocation(line: 1202, column: 18, scope: !3202)
!3205 = !DILocation(line: 1202, column: 3, scope: !3202)
!3206 = !DILocation(line: 1202, column: 6, scope: !3202)
!3207 = !DILocation(line: 1202, column: 21, scope: !3202)
!3208 = !DILocation(line: 1202, column: 28, scope: !3202)
!3209 = !DILocation(line: 1203, column: 18, scope: !3202)
!3210 = !DILocation(line: 1203, column: 3, scope: !3202)
!3211 = !DILocation(line: 1203, column: 6, scope: !3202)
!3212 = !DILocation(line: 1203, column: 21, scope: !3202)
!3213 = !DILocation(line: 1203, column: 28, scope: !3202)
!3214 = !DILocation(line: 1205, column: 22, scope: !426)
!3215 = !DILocation(line: 1205, column: 25, scope: !426)
!3216 = !DILocation(line: 1205, column: 2, scope: !426)
!3217 = !DILocation(line: 1205, column: 5, scope: !426)
!3218 = !DILocation(line: 1205, column: 20, scope: !426)
!3219 = !DILocation(line: 1207, column: 2, scope: !426)
!3220 = !DILocation(line: 1208, column: 1, scope: !426)
!3221 = !DILocalVariable(name: "t", arg: 1, scope: !399, file: !1, line: 2292, type: !153)
!3222 = !DILocation(line: 2292, column: 24, scope: !399)
!3223 = !DILocalVariable(name: "r", scope: !399, file: !1, line: 2294, type: !62)
!3224 = !DILocation(line: 2294, column: 6, scope: !399)
!3225 = !DILocation(line: 2296, column: 2, scope: !399)
!3226 = !DILocation(line: 2296, column: 9, scope: !3227)
!3227 = !DILexicalBlockFile(scope: !399, file: !1, discriminator: 1)
!3228 = !DILocation(line: 2296, column: 12, scope: !3227)
!3229 = !DILocation(line: 2296, column: 18, scope: !3227)
!3230 = !DILocation(line: 2296, column: 2, scope: !3227)
!3231 = !DILocation(line: 2298, column: 7, scope: !3232)
!3232 = distinct !DILexicalBlock(scope: !3233, file: !1, line: 2298, column: 7)
!3233 = distinct !DILexicalBlock(scope: !399, file: !1, line: 2296, column: 27)
!3234 = !DILocation(line: 2298, column: 10, scope: !3232)
!3235 = !DILocation(line: 2298, column: 12, scope: !3232)
!3236 = !DILocation(line: 2298, column: 7, scope: !3233)
!3237 = !DILocation(line: 2299, column: 28, scope: !3238)
!3238 = distinct !DILexicalBlock(scope: !3232, file: !1, line: 2298, column: 35)
!3239 = !DILocation(line: 2299, column: 8, scope: !3238)
!3240 = !DILocation(line: 2299, column: 6, scope: !3238)
!3241 = !DILocation(line: 2300, column: 8, scope: !3242)
!3242 = distinct !DILexicalBlock(scope: !3238, file: !1, line: 2300, column: 8)
!3243 = !DILocation(line: 2300, column: 10, scope: !3242)
!3244 = !DILocation(line: 2300, column: 8, scope: !3238)
!3245 = !DILocation(line: 2301, column: 5, scope: !3242)
!3246 = !DILocation(line: 2302, column: 12, scope: !3238)
!3247 = !DILocation(line: 2302, column: 4, scope: !3238)
!3248 = !DILocation(line: 2305, column: 7, scope: !3249)
!3249 = distinct !DILexicalBlock(scope: !3233, file: !1, line: 2305, column: 7)
!3250 = !DILocation(line: 2305, column: 10, scope: !3249)
!3251 = !DILocation(line: 2305, column: 17, scope: !3249)
!3252 = !DILocation(line: 2305, column: 23, scope: !3249)
!3253 = !DILocation(line: 2305, column: 7, scope: !3233)
!3254 = !DILocation(line: 2307, column: 17, scope: !3255)
!3255 = distinct !DILexicalBlock(scope: !3249, file: !1, line: 2305, column: 42)
!3256 = !DILocation(line: 2307, column: 20, scope: !3255)
!3257 = !DILocation(line: 2307, column: 4, scope: !3255)
!3258 = !DILocation(line: 2307, column: 7, scope: !3255)
!3259 = !DILocation(line: 2307, column: 15, scope: !3255)
!3260 = !DILocation(line: 2308, column: 16, scope: !3255)
!3261 = !DILocation(line: 2308, column: 19, scope: !3255)
!3262 = !DILocation(line: 2308, column: 22, scope: !3255)
!3263 = !DILocation(line: 2308, column: 29, scope: !3255)
!3264 = !DILocation(line: 2308, column: 34, scope: !3255)
!3265 = !DILocation(line: 2309, column: 8, scope: !3255)
!3266 = !DILocation(line: 2308, column: 4, scope: !3255)
!3267 = !DILocation(line: 2312, column: 4, scope: !3255)
!3268 = !DILocation(line: 2312, column: 7, scope: !3255)
!3269 = !DILocation(line: 2312, column: 14, scope: !3255)
!3270 = !DILocation(line: 2312, column: 20, scope: !3255)
!3271 = !DILocation(line: 2313, column: 12, scope: !3255)
!3272 = !DILocation(line: 2313, column: 15, scope: !3255)
!3273 = !DILocation(line: 2313, column: 26, scope: !3255)
!3274 = !DILocation(line: 2313, column: 4, scope: !3255)
!3275 = !DILocation(line: 2314, column: 14, scope: !3276)
!3276 = distinct !DILexicalBlock(scope: !3249, file: !1, line: 2314, column: 14)
!3277 = !DILocation(line: 2314, column: 17, scope: !3276)
!3278 = !DILocation(line: 2314, column: 24, scope: !3276)
!3279 = !DILocation(line: 2314, column: 30, scope: !3276)
!3280 = !DILocation(line: 2314, column: 14, scope: !3249)
!3281 = !DILocation(line: 2316, column: 17, scope: !3282)
!3282 = distinct !DILexicalBlock(scope: !3276, file: !1, line: 2314, column: 46)
!3283 = !DILocation(line: 2316, column: 20, scope: !3282)
!3284 = !DILocation(line: 2316, column: 4, scope: !3282)
!3285 = !DILocation(line: 2316, column: 7, scope: !3282)
!3286 = !DILocation(line: 2316, column: 15, scope: !3282)
!3287 = !DILocation(line: 2317, column: 16, scope: !3282)
!3288 = !DILocation(line: 2317, column: 19, scope: !3282)
!3289 = !DILocation(line: 2317, column: 22, scope: !3282)
!3290 = !DILocation(line: 2317, column: 29, scope: !3282)
!3291 = !DILocation(line: 2317, column: 34, scope: !3282)
!3292 = !DILocation(line: 2318, column: 8, scope: !3282)
!3293 = !DILocation(line: 2317, column: 4, scope: !3282)
!3294 = !DILocation(line: 2319, column: 4, scope: !3282)
!3295 = !DILocation(line: 2319, column: 7, scope: !3282)
!3296 = !DILocation(line: 2319, column: 14, scope: !3282)
!3297 = !DILocation(line: 2319, column: 20, scope: !3282)
!3298 = !DILocation(line: 2320, column: 21, scope: !3282)
!3299 = !DILocation(line: 2320, column: 8, scope: !3282)
!3300 = !DILocation(line: 2320, column: 6, scope: !3282)
!3301 = !DILocation(line: 2321, column: 8, scope: !3302)
!3302 = distinct !DILexicalBlock(scope: !3282, file: !1, line: 2321, column: 8)
!3303 = !DILocation(line: 2321, column: 10, scope: !3302)
!3304 = !DILocation(line: 2321, column: 8, scope: !3282)
!3305 = !DILocation(line: 2322, column: 14, scope: !3306)
!3306 = distinct !DILexicalBlock(scope: !3302, file: !1, line: 2321, column: 16)
!3307 = !DILocation(line: 2322, column: 5, scope: !3306)
!3308 = !DILocation(line: 2323, column: 21, scope: !3306)
!3309 = !DILocation(line: 2323, column: 5, scope: !3306)
!3310 = !DILocation(line: 2323, column: 8, scope: !3306)
!3311 = !DILocation(line: 2323, column: 19, scope: !3306)
!3312 = !DILocation(line: 2324, column: 4, scope: !3306)
!3313 = !DILocation(line: 2325, column: 5, scope: !3302)
!3314 = !DILocation(line: 2325, column: 8, scope: !3302)
!3315 = !DILocation(line: 2325, column: 19, scope: !3302)
!3316 = !DILocation(line: 2326, column: 12, scope: !3282)
!3317 = !DILocation(line: 2326, column: 15, scope: !3282)
!3318 = !DILocation(line: 2326, column: 4, scope: !3282)
!3319 = !DILocation(line: 2327, column: 14, scope: !3320)
!3320 = distinct !DILexicalBlock(scope: !3276, file: !1, line: 2327, column: 14)
!3321 = !DILocation(line: 2327, column: 17, scope: !3320)
!3322 = !DILocation(line: 2327, column: 24, scope: !3320)
!3323 = !DILocation(line: 2327, column: 30, scope: !3320)
!3324 = !DILocation(line: 2327, column: 14, scope: !3276)
!3325 = !DILocation(line: 2328, column: 4, scope: !3326)
!3326 = distinct !DILexicalBlock(scope: !3320, file: !1, line: 2327, column: 43)
!3327 = !DILocation(line: 2328, column: 7, scope: !3326)
!3328 = !DILocation(line: 2328, column: 14, scope: !3326)
!3329 = !DILocation(line: 2328, column: 20, scope: !3326)
!3330 = !DILocation(line: 2329, column: 28, scope: !3326)
!3331 = !DILocation(line: 2329, column: 8, scope: !3326)
!3332 = !DILocation(line: 2329, column: 6, scope: !3326)
!3333 = !DILocation(line: 2330, column: 8, scope: !3334)
!3334 = distinct !DILexicalBlock(scope: !3326, file: !1, line: 2330, column: 8)
!3335 = !DILocation(line: 2330, column: 10, scope: !3334)
!3336 = !DILocation(line: 2330, column: 8, scope: !3326)
!3337 = !DILocation(line: 2331, column: 5, scope: !3334)
!3338 = !DILocation(line: 2332, column: 12, scope: !3326)
!3339 = !DILocation(line: 2332, column: 4, scope: !3326)
!3340 = !DILocation(line: 2333, column: 14, scope: !3341)
!3341 = distinct !DILexicalBlock(scope: !3320, file: !1, line: 2333, column: 14)
!3342 = !DILocation(line: 2333, column: 17, scope: !3341)
!3343 = !DILocation(line: 2333, column: 24, scope: !3341)
!3344 = !DILocation(line: 2333, column: 30, scope: !3341)
!3345 = !DILocation(line: 2333, column: 14, scope: !3320)
!3346 = !DILocation(line: 2335, column: 20, scope: !3347)
!3347 = distinct !DILexicalBlock(scope: !3341, file: !1, line: 2333, column: 45)
!3348 = !DILocation(line: 2335, column: 8, scope: !3347)
!3349 = !DILocation(line: 2335, column: 6, scope: !3347)
!3350 = !DILocation(line: 2336, column: 13, scope: !3347)
!3351 = !DILocation(line: 2336, column: 4, scope: !3347)
!3352 = !DILocation(line: 2337, column: 20, scope: !3347)
!3353 = !DILocation(line: 2337, column: 22, scope: !3347)
!3354 = !DILocation(line: 2337, column: 29, scope: !3355)
!3355 = !DILexicalBlockFile(scope: !3347, file: !1, discriminator: 1)
!3356 = !DILocation(line: 2337, column: 20, scope: !3355)
!3357 = !DILocation(line: 2337, column: 20, scope: !3358)
!3358 = !DILexicalBlockFile(scope: !3347, file: !1, discriminator: 2)
!3359 = !DILocation(line: 2337, column: 20, scope: !3360)
!3360 = !DILexicalBlockFile(scope: !3347, file: !1, discriminator: 3)
!3361 = !DILocation(line: 2337, column: 4, scope: !3360)
!3362 = !DILocation(line: 2337, column: 7, scope: !3360)
!3363 = !DILocation(line: 2337, column: 18, scope: !3360)
!3364 = !DILocation(line: 2338, column: 12, scope: !3347)
!3365 = !DILocation(line: 2338, column: 15, scope: !3347)
!3366 = !DILocation(line: 2338, column: 4, scope: !3347)
!3367 = !DILocation(line: 2341, column: 13, scope: !3368)
!3368 = distinct !DILexicalBlock(scope: !3341, file: !1, line: 2339, column: 10)
!3369 = !DILocation(line: 2341, column: 4, scope: !3368)
!3370 = !DILocation(line: 2342, column: 4, scope: !3368)
!3371 = !DILocation(line: 2342, column: 7, scope: !3368)
!3372 = !DILocation(line: 2342, column: 13, scope: !3368)
!3373 = !DILocation(line: 2343, column: 4, scope: !3368)
!3374 = !DILocation(line: 2343, column: 7, scope: !3368)
!3375 = !DILocation(line: 2343, column: 13, scope: !3368)
!3376 = !DILocation(line: 2296, column: 2, scope: !3377)
!3377 = !DILexicalBlockFile(scope: !399, file: !1, discriminator: 2)
!3378 = !DILocation(line: 2346, column: 10, scope: !399)
!3379 = !DILocation(line: 2346, column: 13, scope: !399)
!3380 = !DILocation(line: 2346, column: 24, scope: !399)
!3381 = !DILocation(line: 2346, column: 2, scope: !399)
!3382 = !DILocation(line: 2347, column: 1, scope: !399)
!3383 = !DILocalVariable(name: "t", arg: 1, scope: !409, file: !1, line: 2465, type: !153)
!3384 = !DILocation(line: 2465, column: 33, scope: !409)
!3385 = !DILocation(line: 2467, column: 8, scope: !3386)
!3386 = distinct !DILexicalBlock(scope: !409, file: !1, line: 2467, column: 6)
!3387 = !DILocation(line: 2467, column: 11, scope: !3386)
!3388 = !DILocation(line: 2467, column: 17, scope: !3386)
!3389 = !DILocation(line: 2467, column: 6, scope: !409)
!3390 = !DILocation(line: 2469, column: 35, scope: !3391)
!3391 = distinct !DILexicalBlock(scope: !3392, file: !1, line: 2469, column: 7)
!3392 = distinct !DILexicalBlock(scope: !3386, file: !1, line: 2467, column: 30)
!3393 = !DILocation(line: 2469, column: 15, scope: !3391)
!3394 = !DILocation(line: 2470, column: 32, scope: !3391)
!3395 = !DILocation(line: 2470, column: 7, scope: !3391)
!3396 = !DILocation(line: 2470, column: 37, scope: !3391)
!3397 = !DILocation(line: 2470, column: 40, scope: !3391)
!3398 = !DILocation(line: 2469, column: 7, scope: !3391)
!3399 = !DILocation(line: 2471, column: 28, scope: !3391)
!3400 = !DILocation(line: 2469, column: 7, scope: !3392)
!3401 = !DILocation(line: 2477, column: 4, scope: !3391)
!3402 = !DILocation(line: 2478, column: 3, scope: !3392)
!3403 = !DILocation(line: 2478, column: 6, scope: !3392)
!3404 = !DILocation(line: 2478, column: 12, scope: !3392)
!3405 = !DILocation(line: 2479, column: 2, scope: !3392)
!3406 = !DILocation(line: 2480, column: 11, scope: !409)
!3407 = !DILocation(line: 2480, column: 14, scope: !409)
!3408 = !DILocation(line: 2480, column: 2, scope: !409)
!3409 = !DILocation(line: 2481, column: 1, scope: !409)
!3410 = !DILocalVariable(name: "t", arg: 1, scope: !414, file: !1, line: 2444, type: !153)
!3411 = !DILocation(line: 2444, column: 32, scope: !414)
!3412 = !DILocation(line: 2446, column: 8, scope: !3413)
!3413 = distinct !DILexicalBlock(scope: !414, file: !1, line: 2446, column: 6)
!3414 = !DILocation(line: 2446, column: 11, scope: !3413)
!3415 = !DILocation(line: 2446, column: 17, scope: !3413)
!3416 = !DILocation(line: 2446, column: 6, scope: !414)
!3417 = !DILocation(line: 2448, column: 35, scope: !3418)
!3418 = distinct !DILexicalBlock(scope: !3419, file: !1, line: 2448, column: 7)
!3419 = distinct !DILexicalBlock(scope: !3413, file: !1, line: 2446, column: 29)
!3420 = !DILocation(line: 2448, column: 15, scope: !3418)
!3421 = !DILocation(line: 2449, column: 32, scope: !3418)
!3422 = !DILocation(line: 2449, column: 7, scope: !3418)
!3423 = !DILocation(line: 2449, column: 37, scope: !3418)
!3424 = !DILocation(line: 2449, column: 40, scope: !3418)
!3425 = !DILocation(line: 2448, column: 7, scope: !3418)
!3426 = !DILocation(line: 2449, column: 47, scope: !3418)
!3427 = !DILocation(line: 2448, column: 7, scope: !3419)
!3428 = !DILocation(line: 2455, column: 4, scope: !3418)
!3429 = !DILocation(line: 2456, column: 3, scope: !3419)
!3430 = !DILocation(line: 2456, column: 6, scope: !3419)
!3431 = !DILocation(line: 2456, column: 12, scope: !3419)
!3432 = !DILocation(line: 2457, column: 2, scope: !3419)
!3433 = !DILocation(line: 2458, column: 11, scope: !414)
!3434 = !DILocation(line: 2458, column: 14, scope: !414)
!3435 = !DILocation(line: 2458, column: 2, scope: !414)
!3436 = !DILocation(line: 2459, column: 1, scope: !414)
!3437 = !DILocalVariable(name: "t", arg: 1, scope: !415, file: !1, line: 2560, type: !153)
!3438 = !DILocation(line: 2560, column: 44, scope: !415)
!3439 = !DILocalVariable(name: "st", arg: 2, scope: !415, file: !1, line: 2560, type: !412)
!3440 = !DILocation(line: 2560, column: 66, scope: !415)
!3441 = !DILocalVariable(name: "te", scope: !415, file: !1, line: 2562, type: !157)
!3442 = !DILocation(line: 2562, column: 21, scope: !415)
!3443 = !DILocation(line: 2564, column: 12, scope: !3444)
!3444 = distinct !DILexicalBlock(scope: !415, file: !1, line: 2564, column: 2)
!3445 = !DILocation(line: 2564, column: 15, scope: !3444)
!3446 = !DILocation(line: 2564, column: 24, scope: !3444)
!3447 = !DILocation(line: 2564, column: 10, scope: !3444)
!3448 = !DILocation(line: 2564, column: 7, scope: !3444)
!3449 = !DILocation(line: 2564, column: 32, scope: !3450)
!3450 = !DILexicalBlockFile(scope: !3451, file: !1, discriminator: 1)
!3451 = distinct !DILexicalBlock(scope: !3444, file: !1, line: 2564, column: 2)
!3452 = !DILocation(line: 2564, column: 35, scope: !3450)
!3453 = !DILocation(line: 2564, column: 2, scope: !3450)
!3454 = !DILocation(line: 2565, column: 7, scope: !3455)
!3455 = distinct !DILexicalBlock(scope: !3456, file: !1, line: 2565, column: 7)
!3456 = distinct !DILexicalBlock(scope: !3451, file: !1, line: 2564, column: 61)
!3457 = !DILocation(line: 2565, column: 11, scope: !3455)
!3458 = !DILocation(line: 2565, column: 27, scope: !3455)
!3459 = !DILocation(line: 2565, column: 31, scope: !3455)
!3460 = !DILocation(line: 2565, column: 15, scope: !3455)
!3461 = !DILocation(line: 2565, column: 38, scope: !3455)
!3462 = !DILocation(line: 2566, column: 7, scope: !3455)
!3463 = !DILocation(line: 2566, column: 11, scope: !3455)
!3464 = !DILocation(line: 2566, column: 27, scope: !3455)
!3465 = !DILocation(line: 2566, column: 31, scope: !3455)
!3466 = !DILocation(line: 2566, column: 15, scope: !3455)
!3467 = !DILocation(line: 2565, column: 7, scope: !3468)
!3468 = !DILexicalBlockFile(scope: !3456, file: !1, discriminator: 1)
!3469 = !DILocation(line: 2567, column: 4, scope: !3455)
!3470 = !DILocation(line: 2568, column: 2, scope: !3456)
!3471 = !DILocation(line: 2564, column: 49, scope: !3472)
!3472 = !DILexicalBlockFile(scope: !3451, file: !1, discriminator: 2)
!3473 = !DILocation(line: 2564, column: 53, scope: !3472)
!3474 = !DILocation(line: 2564, column: 47, scope: !3472)
!3475 = !DILocation(line: 2564, column: 2, scope: !3472)
!3476 = !DILocation(line: 2569, column: 2, scope: !415)
!3477 = !DILocation(line: 2570, column: 1, scope: !415)
!3478 = !DILocalVariable(name: "a", arg: 1, scope: !418, file: !1, line: 1364, type: !43)
!3479 = !DILocation(line: 1364, column: 53, scope: !418)
!3480 = !DILocalVariable(name: "dev", arg: 2, scope: !418, file: !1, line: 1364, type: !91)
!3481 = !DILocation(line: 1364, column: 64, scope: !418)
!3482 = !DILocalVariable(name: "t", scope: !418, file: !1, line: 1366, type: !153)
!3483 = !DILocation(line: 1366, column: 15, scope: !418)
!3484 = !DILocation(line: 1366, column: 19, scope: !418)
!3485 = !DILocation(line: 1366, column: 22, scope: !418)
!3486 = !DILocalVariable(name: "i", scope: !418, file: !1, line: 1367, type: !62)
!3487 = !DILocation(line: 1367, column: 6, scope: !418)
!3488 = !DILocalVariable(name: "fid", scope: !418, file: !1, line: 1367, type: !62)
!3489 = !DILocation(line: 1367, column: 9, scope: !418)
!3490 = !DILocation(line: 1369, column: 6, scope: !3491)
!3491 = distinct !DILexicalBlock(scope: !418, file: !1, line: 1369, column: 6)
!3492 = !DILocation(line: 1369, column: 9, scope: !3491)
!3493 = !DILocation(line: 1369, column: 28, scope: !3491)
!3494 = !DILocation(line: 1369, column: 36, scope: !3491)
!3495 = !DILocation(line: 1370, column: 6, scope: !3491)
!3496 = !DILocation(line: 1370, column: 9, scope: !3491)
!3497 = !DILocation(line: 1370, column: 29, scope: !3491)
!3498 = !DILocation(line: 1370, column: 36, scope: !3491)
!3499 = !DILocation(line: 1370, column: 33, scope: !3491)
!3500 = !DILocation(line: 1369, column: 6, scope: !3501)
!3501 = !DILexicalBlockFile(scope: !418, file: !1, discriminator: 1)
!3502 = !DILocation(line: 1371, column: 3, scope: !3491)
!3503 = !DILocation(line: 1373, column: 9, scope: !3504)
!3504 = distinct !DILexicalBlock(scope: !418, file: !1, line: 1373, column: 2)
!3505 = !DILocation(line: 1373, column: 7, scope: !3504)
!3506 = !DILocation(line: 1373, column: 14, scope: !3507)
!3507 = !DILexicalBlockFile(scope: !3508, file: !1, discriminator: 1)
!3508 = distinct !DILexicalBlock(scope: !3504, file: !1, line: 1373, column: 2)
!3509 = !DILocation(line: 1373, column: 18, scope: !3507)
!3510 = !DILocation(line: 1373, column: 21, scope: !3507)
!3511 = !DILocation(line: 1373, column: 16, scope: !3507)
!3512 = !DILocation(line: 1373, column: 2, scope: !3507)
!3513 = !DILocation(line: 1374, column: 27, scope: !3514)
!3514 = distinct !DILexicalBlock(scope: !3515, file: !1, line: 1374, column: 7)
!3515 = distinct !DILexicalBlock(scope: !3508, file: !1, line: 1373, column: 45)
!3516 = !DILocation(line: 1374, column: 7, scope: !3514)
!3517 = !DILocation(line: 1374, column: 10, scope: !3514)
!3518 = !DILocation(line: 1374, column: 30, scope: !3514)
!3519 = !DILocation(line: 1374, column: 37, scope: !3514)
!3520 = !DILocation(line: 1374, column: 34, scope: !3514)
!3521 = !DILocation(line: 1374, column: 7, scope: !3515)
!3522 = !DILocation(line: 1376, column: 31, scope: !3523)
!3523 = distinct !DILexicalBlock(scope: !3514, file: !1, line: 1374, column: 42)
!3524 = !DILocation(line: 1376, column: 4, scope: !3523)
!3525 = !DILocation(line: 1376, column: 7, scope: !3523)
!3526 = !DILocation(line: 1376, column: 29, scope: !3523)
!3527 = !DILocation(line: 1377, column: 50, scope: !3523)
!3528 = !DILocation(line: 1377, column: 30, scope: !3523)
!3529 = !DILocation(line: 1377, column: 33, scope: !3523)
!3530 = !DILocation(line: 1377, column: 4, scope: !3523)
!3531 = !DILocation(line: 1377, column: 7, scope: !3523)
!3532 = !DILocation(line: 1377, column: 26, scope: !3523)
!3533 = !DILocation(line: 1378, column: 4, scope: !3523)
!3534 = !DILocation(line: 1380, column: 2, scope: !3515)
!3535 = !DILocation(line: 1373, column: 41, scope: !3536)
!3536 = !DILexicalBlockFile(scope: !3508, file: !1, discriminator: 2)
!3537 = !DILocation(line: 1373, column: 2, scope: !3536)
!3538 = !DILocation(line: 1385, column: 8, scope: !418)
!3539 = !DILocation(line: 1385, column: 11, scope: !418)
!3540 = !DILocation(line: 1385, column: 28, scope: !418)
!3541 = !DILocation(line: 1385, column: 6, scope: !418)
!3542 = !DILocation(line: 1386, column: 6, scope: !3543)
!3543 = distinct !DILexicalBlock(scope: !418, file: !1, line: 1386, column: 6)
!3544 = !DILocation(line: 1386, column: 9, scope: !3543)
!3545 = !DILocation(line: 1386, column: 29, scope: !3543)
!3546 = !DILocation(line: 1386, column: 32, scope: !3543)
!3547 = !DILocation(line: 1386, column: 27, scope: !3543)
!3548 = !DILocation(line: 1386, column: 6, scope: !418)
!3549 = !DILocalVariable(name: "s", scope: !3550, file: !1, line: 1387, type: !84)
!3550 = distinct !DILexicalBlock(scope: !3543, file: !1, line: 1386, column: 54)
!3551 = !DILocation(line: 1387, column: 10, scope: !3550)
!3552 = !DILocalVariable(name: "p", scope: !3550, file: !1, line: 1388, type: !311)
!3553 = !DILocation(line: 1388, column: 9, scope: !3550)
!3554 = !DILocation(line: 1390, column: 7, scope: !3550)
!3555 = !DILocation(line: 1390, column: 10, scope: !3550)
!3556 = !DILocation(line: 1390, column: 28, scope: !3550)
!3557 = !DILocation(line: 1390, column: 5, scope: !3550)
!3558 = !DILocation(line: 1391, column: 15, scope: !3550)
!3559 = !DILocation(line: 1391, column: 18, scope: !3550)
!3560 = !DILocation(line: 1392, column: 11, scope: !3550)
!3561 = !DILocation(line: 1392, column: 13, scope: !3550)
!3562 = !DILocation(line: 1391, column: 7, scope: !3550)
!3563 = !DILocation(line: 1391, column: 5, scope: !3550)
!3564 = !DILocation(line: 1393, column: 7, scope: !3565)
!3565 = distinct !DILexicalBlock(scope: !3550, file: !1, line: 1393, column: 7)
!3566 = !DILocation(line: 1393, column: 9, scope: !3565)
!3567 = !DILocation(line: 1393, column: 7, scope: !3550)
!3568 = !DILocation(line: 1394, column: 23, scope: !3569)
!3569 = distinct !DILexicalBlock(scope: !3565, file: !1, line: 1393, column: 18)
!3570 = !DILocation(line: 1394, column: 26, scope: !3569)
!3571 = !DILocation(line: 1394, column: 4, scope: !3569)
!3572 = !DILocation(line: 1396, column: 4, scope: !3569)
!3573 = !DILocation(line: 1398, column: 46, scope: !3550)
!3574 = !DILocation(line: 1398, column: 25, scope: !3550)
!3575 = !DILocation(line: 1398, column: 3, scope: !3550)
!3576 = !DILocation(line: 1398, column: 6, scope: !3550)
!3577 = !DILocation(line: 1398, column: 23, scope: !3550)
!3578 = !DILocation(line: 1399, column: 29, scope: !3550)
!3579 = !DILocation(line: 1399, column: 3, scope: !3550)
!3580 = !DILocation(line: 1399, column: 6, scope: !3550)
!3581 = !DILocation(line: 1399, column: 27, scope: !3550)
!3582 = !DILocation(line: 1400, column: 2, scope: !3550)
!3583 = !DILocation(line: 1401, column: 29, scope: !418)
!3584 = !DILocation(line: 1401, column: 2, scope: !418)
!3585 = !DILocation(line: 1401, column: 5, scope: !418)
!3586 = !DILocation(line: 1401, column: 27, scope: !418)
!3587 = !DILocation(line: 1402, column: 48, scope: !418)
!3588 = !DILocation(line: 1402, column: 28, scope: !418)
!3589 = !DILocation(line: 1402, column: 31, scope: !418)
!3590 = !DILocation(line: 1402, column: 2, scope: !418)
!3591 = !DILocation(line: 1402, column: 5, scope: !418)
!3592 = !DILocation(line: 1402, column: 24, scope: !418)
!3593 = !DILocation(line: 1403, column: 31, scope: !418)
!3594 = !DILocation(line: 1403, column: 2, scope: !418)
!3595 = !DILocation(line: 1403, column: 5, scope: !418)
!3596 = !DILocation(line: 1403, column: 25, scope: !418)
!3597 = !DILocation(line: 1403, column: 29, scope: !418)
!3598 = !DILocation(line: 1404, column: 2, scope: !418)
!3599 = !DILocation(line: 1404, column: 5, scope: !418)
!3600 = !DILocation(line: 1404, column: 25, scope: !418)
!3601 = !DILocation(line: 1404, column: 40, scope: !418)
!3602 = !DILocation(line: 1405, column: 2, scope: !418)
!3603 = !DILocation(line: 1405, column: 5, scope: !418)
!3604 = !DILocation(line: 1405, column: 25, scope: !418)
!3605 = !DILocation(line: 1405, column: 30, scope: !418)
!3606 = !DILocation(line: 1409, column: 35, scope: !418)
!3607 = !DILocation(line: 1409, column: 10, scope: !418)
!3608 = !DILocation(line: 1409, column: 2, scope: !418)
!3609 = !DILocation(line: 1410, column: 1, scope: !418)
!3610 = !DILocalVariable(name: "t", arg: 1, scope: !400, file: !1, line: 2350, type: !153)
!3611 = !DILocation(line: 2350, column: 34, scope: !400)
!3612 = !DILocalVariable(name: "r", scope: !400, file: !1, line: 2352, type: !62)
!3613 = !DILocation(line: 2352, column: 6, scope: !400)
!3614 = !DILocalVariable(name: "name", scope: !400, file: !1, line: 2353, type: !119)
!3615 = !DILocation(line: 2353, column: 14, scope: !400)
!3616 = !DILocalVariable(name: "namelen", scope: !400, file: !1, line: 2354, type: !84)
!3617 = !DILocation(line: 2354, column: 9, scope: !400)
!3618 = !DILocation(line: 2356, column: 6, scope: !3619)
!3619 = distinct !DILexicalBlock(scope: !400, file: !1, line: 2356, column: 6)
!3620 = !DILocation(line: 2356, column: 9, scope: !3619)
!3621 = !DILocation(line: 2356, column: 11, scope: !3619)
!3622 = !DILocation(line: 2356, column: 6, scope: !400)
!3623 = !DILocalVariable(name: "dirent_size", scope: !3624, file: !1, line: 2358, type: !84)
!3624 = distinct !DILexicalBlock(scope: !3619, file: !1, line: 2356, column: 20)
!3625 = !DILocation(line: 2358, column: 10, scope: !3624)
!3626 = !DILocation(line: 2362, column: 29, scope: !3624)
!3627 = !DILocation(line: 2362, column: 32, scope: !3624)
!3628 = !DILocation(line: 2362, column: 20, scope: !3624)
!3629 = !DILocation(line: 2362, column: 10, scope: !3630)
!3630 = !DILexicalBlockFile(scope: !3624, file: !1, discriminator: 1)
!3631 = !DILocation(line: 2362, column: 3, scope: !3624)
!3632 = !DILocation(line: 2362, column: 6, scope: !3624)
!3633 = !DILocation(line: 2362, column: 8, scope: !3624)
!3634 = !DILocation(line: 2371, column: 7, scope: !3635)
!3635 = distinct !DILexicalBlock(scope: !3624, file: !1, line: 2371, column: 7)
!3636 = !DILocation(line: 2371, column: 10, scope: !3635)
!3637 = !DILocation(line: 2371, column: 12, scope: !3635)
!3638 = !DILocation(line: 2371, column: 7, scope: !3624)
!3639 = !DILocation(line: 2372, column: 20, scope: !3640)
!3640 = distinct !DILexicalBlock(scope: !3635, file: !1, line: 2371, column: 21)
!3641 = !DILocation(line: 2372, column: 8, scope: !3640)
!3642 = !DILocation(line: 2372, column: 6, scope: !3640)
!3643 = !DILocation(line: 2373, column: 13, scope: !3640)
!3644 = !DILocation(line: 2373, column: 4, scope: !3640)
!3645 = !DILocation(line: 2374, column: 20, scope: !3640)
!3646 = !DILocation(line: 2374, column: 4, scope: !3640)
!3647 = !DILocation(line: 2374, column: 7, scope: !3640)
!3648 = !DILocation(line: 2374, column: 18, scope: !3640)
!3649 = !DILocation(line: 2375, column: 20, scope: !3640)
!3650 = !DILocation(line: 2375, column: 22, scope: !3640)
!3651 = !DILocation(line: 2375, column: 29, scope: !3652)
!3652 = !DILexicalBlockFile(scope: !3640, file: !1, discriminator: 1)
!3653 = !DILocation(line: 2375, column: 20, scope: !3652)
!3654 = !DILocation(line: 2375, column: 20, scope: !3655)
!3655 = !DILexicalBlockFile(scope: !3640, file: !1, discriminator: 2)
!3656 = !DILocation(line: 2375, column: 20, scope: !3657)
!3657 = !DILexicalBlockFile(scope: !3640, file: !1, discriminator: 3)
!3658 = !DILocation(line: 2375, column: 4, scope: !3657)
!3659 = !DILocation(line: 2375, column: 7, scope: !3657)
!3660 = !DILocation(line: 2375, column: 18, scope: !3657)
!3661 = !DILocation(line: 2376, column: 12, scope: !3640)
!3662 = !DILocation(line: 2376, column: 15, scope: !3640)
!3663 = !DILocation(line: 2376, column: 4, scope: !3640)
!3664 = !DILocation(line: 2380, column: 25, scope: !3624)
!3665 = !DILocation(line: 2380, column: 28, scope: !3624)
!3666 = !DILocation(line: 2380, column: 37, scope: !3624)
!3667 = !DILocation(line: 2380, column: 5, scope: !3624)
!3668 = !DILocation(line: 2380, column: 8, scope: !3624)
!3669 = !DILocation(line: 2380, column: 52, scope: !3624)
!3670 = !DILocation(line: 2379, column: 49, scope: !3624)
!3671 = !DILocation(line: 2380, column: 61, scope: !3624)
!3672 = !DILocation(line: 2379, column: 15, scope: !3624)
!3673 = !DILocation(line: 2381, column: 7, scope: !3674)
!3674 = distinct !DILexicalBlock(scope: !3624, file: !1, line: 2381, column: 7)
!3675 = !DILocation(line: 2381, column: 10, scope: !3674)
!3676 = !DILocation(line: 2381, column: 17, scope: !3674)
!3677 = !DILocation(line: 2381, column: 25, scope: !3674)
!3678 = !DILocation(line: 2381, column: 28, scope: !3679)
!3679 = !DILexicalBlockFile(scope: !3674, file: !1, discriminator: 1)
!3680 = !DILocation(line: 2381, column: 31, scope: !3679)
!3681 = !DILocation(line: 2381, column: 50, scope: !3679)
!3682 = !DILocation(line: 2381, column: 48, scope: !3679)
!3683 = !DILocation(line: 2381, column: 7, scope: !3679)
!3684 = !DILocation(line: 2382, column: 9, scope: !3685)
!3685 = distinct !DILexicalBlock(scope: !3674, file: !1, line: 2381, column: 63)
!3686 = !DILocation(line: 2382, column: 12, scope: !3685)
!3687 = !DILocation(line: 2382, column: 4, scope: !3685)
!3688 = !DILocation(line: 2383, column: 23, scope: !3685)
!3689 = !DILocation(line: 2383, column: 16, scope: !3685)
!3690 = !DILocation(line: 2383, column: 4, scope: !3685)
!3691 = !DILocation(line: 2383, column: 7, scope: !3685)
!3692 = !DILocation(line: 2383, column: 14, scope: !3685)
!3693 = !DILocation(line: 2384, column: 8, scope: !3694)
!3694 = distinct !DILexicalBlock(scope: !3685, file: !1, line: 2384, column: 8)
!3695 = !DILocation(line: 2384, column: 11, scope: !3694)
!3696 = !DILocation(line: 2384, column: 18, scope: !3694)
!3697 = !DILocation(line: 2384, column: 8, scope: !3685)
!3698 = !DILocation(line: 2385, column: 14, scope: !3699)
!3699 = distinct !DILexicalBlock(scope: !3694, file: !1, line: 2384, column: 27)
!3700 = !DILocation(line: 2385, column: 17, scope: !3699)
!3701 = !DILocation(line: 2385, column: 5, scope: !3699)
!3702 = !DILocation(line: 2386, column: 5, scope: !3699)
!3703 = !DILocation(line: 2386, column: 8, scope: !3699)
!3704 = !DILocation(line: 2386, column: 10, scope: !3699)
!3705 = !DILocation(line: 2387, column: 23, scope: !3699)
!3706 = !DILocation(line: 2387, column: 11, scope: !3699)
!3707 = !DILocation(line: 2388, column: 14, scope: !3699)
!3708 = !DILocation(line: 2388, column: 5, scope: !3699)
!3709 = !DILocation(line: 2389, column: 5, scope: !3699)
!3710 = !DILocation(line: 2389, column: 8, scope: !3699)
!3711 = !DILocation(line: 2389, column: 19, scope: !3699)
!3712 = !DILocation(line: 2390, column: 5, scope: !3699)
!3713 = !DILocation(line: 2390, column: 8, scope: !3699)
!3714 = !DILocation(line: 2390, column: 19, scope: !3699)
!3715 = !DILocation(line: 2391, column: 13, scope: !3699)
!3716 = !DILocation(line: 2391, column: 16, scope: !3699)
!3717 = !DILocation(line: 2391, column: 5, scope: !3699)
!3718 = !DILocation(line: 2393, column: 26, scope: !3685)
!3719 = !DILocation(line: 2393, column: 4, scope: !3685)
!3720 = !DILocation(line: 2393, column: 7, scope: !3685)
!3721 = !DILocation(line: 2393, column: 24, scope: !3685)
!3722 = !DILocation(line: 2394, column: 3, scope: !3685)
!3723 = !DILocation(line: 2396, column: 2, scope: !3624)
!3724 = !DILocation(line: 2397, column: 2, scope: !400)
!3725 = !DILocation(line: 2398, column: 3, scope: !3726)
!3726 = distinct !DILexicalBlock(scope: !3727, file: !1, line: 2397, column: 11)
!3727 = distinct !DILexicalBlock(scope: !3728, file: !1, line: 2397, column: 2)
!3728 = distinct !DILexicalBlock(scope: !400, file: !1, line: 2397, column: 2)
!3729 = !DILocation(line: 2398, column: 9, scope: !3726)
!3730 = !DILocation(line: 2400, column: 17, scope: !3726)
!3731 = !DILocation(line: 2400, column: 20, scope: !3726)
!3732 = !DILocation(line: 2400, column: 23, scope: !3726)
!3733 = !DILocation(line: 2400, column: 26, scope: !3726)
!3734 = !DILocation(line: 2400, column: 35, scope: !3726)
!3735 = !DILocation(line: 2400, column: 38, scope: !3726)
!3736 = !DILocation(line: 2400, column: 7, scope: !3726)
!3737 = !DILocation(line: 2400, column: 5, scope: !3726)
!3738 = !DILocation(line: 2411, column: 7, scope: !3739)
!3739 = distinct !DILexicalBlock(scope: !3726, file: !1, line: 2411, column: 7)
!3740 = !DILocation(line: 2411, column: 9, scope: !3739)
!3741 = !DILocation(line: 2411, column: 14, scope: !3739)
!3742 = !DILocation(line: 2411, column: 17, scope: !3743)
!3743 = !DILexicalBlockFile(scope: !3739, file: !1, discriminator: 1)
!3744 = !DILocation(line: 2411, column: 20, scope: !3743)
!3745 = !DILocation(line: 2411, column: 23, scope: !3743)
!3746 = !DILocation(line: 2411, column: 7, scope: !3743)
!3747 = !DILocation(line: 2417, column: 13, scope: !3748)
!3748 = distinct !DILexicalBlock(scope: !3739, file: !1, line: 2411, column: 32)
!3749 = !DILocation(line: 2417, column: 16, scope: !3748)
!3750 = !DILocation(line: 2417, column: 4, scope: !3748)
!3751 = !DILocation(line: 2418, column: 4, scope: !3748)
!3752 = !DILocation(line: 2418, column: 7, scope: !3748)
!3753 = !DILocation(line: 2418, column: 9, scope: !3748)
!3754 = !DILocation(line: 2419, column: 8, scope: !3755)
!3755 = distinct !DILexicalBlock(scope: !3748, file: !1, line: 2419, column: 8)
!3756 = !DILocation(line: 2419, column: 10, scope: !3755)
!3757 = !DILocation(line: 2419, column: 8, scope: !3748)
!3758 = !DILocation(line: 2420, column: 21, scope: !3759)
!3759 = distinct !DILexicalBlock(scope: !3755, file: !1, line: 2419, column: 16)
!3760 = !DILocation(line: 2420, column: 5, scope: !3759)
!3761 = !DILocation(line: 2420, column: 8, scope: !3759)
!3762 = !DILocation(line: 2420, column: 19, scope: !3759)
!3763 = !DILocation(line: 2421, column: 5, scope: !3759)
!3764 = !DILocation(line: 2421, column: 8, scope: !3759)
!3765 = !DILocation(line: 2421, column: 19, scope: !3759)
!3766 = !DILocation(line: 2422, column: 13, scope: !3759)
!3767 = !DILocation(line: 2422, column: 16, scope: !3759)
!3768 = !DILocation(line: 2422, column: 5, scope: !3759)
!3769 = !DILocation(line: 2424, column: 5, scope: !3755)
!3770 = !DILocation(line: 2426, column: 10, scope: !3726)
!3771 = !DILocation(line: 2426, column: 13, scope: !3726)
!3772 = !DILocation(line: 2426, column: 17, scope: !3726)
!3773 = !DILocation(line: 2426, column: 8, scope: !3726)
!3774 = !DILocation(line: 2427, column: 13, scope: !3726)
!3775 = !DILocation(line: 2427, column: 11, scope: !3726)
!3776 = !DILocation(line: 2428, column: 3, scope: !3726)
!3777 = !DILocation(line: 2428, column: 6, scope: !3726)
!3778 = !DILocation(line: 2428, column: 12, scope: !3726)
!3779 = !DILocation(line: 2429, column: 3, scope: !3726)
!3780 = !DILocation(line: 2429, column: 6, scope: !3726)
!3781 = !DILocation(line: 2429, column: 12, scope: !3726)
!3782 = !DILocation(line: 2430, column: 7, scope: !3783)
!3783 = distinct !DILexicalBlock(scope: !3726, file: !1, line: 2430, column: 7)
!3784 = !DILocation(line: 2430, column: 15, scope: !3783)
!3785 = !DILocation(line: 2430, column: 22, scope: !3783)
!3786 = !DILocation(line: 2430, column: 25, scope: !3787)
!3787 = !DILexicalBlockFile(scope: !3783, file: !1, discriminator: 1)
!3788 = !DILocation(line: 2430, column: 33, scope: !3787)
!3789 = !DILocation(line: 2430, column: 7, scope: !3787)
!3790 = !DILocation(line: 2431, column: 4, scope: !3783)
!3791 = !DILocation(line: 2432, column: 7, scope: !3792)
!3792 = distinct !DILexicalBlock(scope: !3726, file: !1, line: 2432, column: 7)
!3793 = !DILocation(line: 2432, column: 15, scope: !3792)
!3794 = !DILocation(line: 2432, column: 22, scope: !3792)
!3795 = !DILocation(line: 2432, column: 25, scope: !3796)
!3796 = !DILexicalBlockFile(scope: !3792, file: !1, discriminator: 1)
!3797 = !DILocation(line: 2432, column: 33, scope: !3796)
!3798 = !DILocation(line: 2432, column: 40, scope: !3796)
!3799 = !DILocation(line: 2432, column: 43, scope: !3800)
!3800 = !DILexicalBlockFile(scope: !3792, file: !1, discriminator: 2)
!3801 = !DILocation(line: 2432, column: 51, scope: !3800)
!3802 = !DILocation(line: 2432, column: 7, scope: !3800)
!3803 = !DILocation(line: 2433, column: 4, scope: !3792)
!3804 = !DILocation(line: 2434, column: 15, scope: !3726)
!3805 = !DILocation(line: 2434, column: 18, scope: !3726)
!3806 = !DILocation(line: 2434, column: 24, scope: !3726)
!3807 = !DILocation(line: 2434, column: 3, scope: !3726)
!3808 = !DILocation(line: 2435, column: 11, scope: !3726)
!3809 = !DILocation(line: 2435, column: 14, scope: !3726)
!3810 = !DILocation(line: 2435, column: 25, scope: !3726)
!3811 = !DILocation(line: 2435, column: 3, scope: !3726)
!3812 = !DILocation(line: 2437, column: 1, scope: !400)
!3813 = !DILocalVariable(name: "t", arg: 1, scope: !404, file: !1, line: 2085, type: !153)
!3814 = !DILocation(line: 2085, column: 26, scope: !404)
!3815 = !DILocalVariable(name: "name", arg: 2, scope: !404, file: !1, line: 2085, type: !119)
!3816 = !DILocation(line: 2085, column: 41, scope: !404)
!3817 = !DILocalVariable(name: "name_length", arg: 3, scope: !404, file: !1, line: 2085, type: !84)
!3818 = !DILocation(line: 2085, column: 54, scope: !404)
!3819 = !DILocalVariable(name: "size_needed", scope: !404, file: !1, line: 2087, type: !84)
!3820 = !DILocation(line: 2087, column: 9, scope: !404)
!3821 = !DILocation(line: 2089, column: 12, scope: !404)
!3822 = !DILocation(line: 2089, column: 15, scope: !404)
!3823 = !DILocation(line: 2089, column: 2, scope: !404)
!3824 = !DILocation(line: 2089, column: 5, scope: !404)
!3825 = !DILocation(line: 2089, column: 10, scope: !404)
!3826 = !DILocation(line: 2089, column: 31, scope: !404)
!3827 = !DILocation(line: 2090, column: 19, scope: !404)
!3828 = !DILocation(line: 2090, column: 22, scope: !404)
!3829 = !DILocation(line: 2090, column: 2, scope: !404)
!3830 = !DILocation(line: 2090, column: 5, scope: !404)
!3831 = !DILocation(line: 2090, column: 10, scope: !404)
!3832 = !DILocation(line: 2090, column: 17, scope: !404)
!3833 = !DILocation(line: 2092, column: 2, scope: !404)
!3834 = !DILocation(line: 2092, column: 9, scope: !3835)
!3835 = !DILexicalBlockFile(scope: !404, file: !1, discriminator: 1)
!3836 = !DILocation(line: 2092, column: 21, scope: !3835)
!3837 = !DILocation(line: 2092, column: 25, scope: !3835)
!3838 = !DILocation(line: 2092, column: 33, scope: !3839)
!3839 = !DILexicalBlockFile(scope: !404, file: !1, discriminator: 2)
!3840 = !DILocation(line: 2092, column: 45, scope: !3839)
!3841 = !DILocation(line: 2092, column: 28, scope: !3839)
!3842 = !DILocation(line: 2092, column: 50, scope: !3839)
!3843 = !DILocation(line: 2092, column: 2, scope: !3844)
!3844 = !DILexicalBlockFile(scope: !404, file: !1, discriminator: 3)
!3845 = !DILocation(line: 2093, column: 14, scope: !404)
!3846 = !DILocation(line: 2092, column: 2, scope: !3847)
!3847 = !DILexicalBlockFile(scope: !404, file: !1, discriminator: 4)
!3848 = !DILocation(line: 2096, column: 16, scope: !404)
!3849 = !DILocation(line: 2096, column: 30, scope: !404)
!3850 = !DILocation(line: 2096, column: 33, scope: !404)
!3851 = !DILocation(line: 2096, column: 28, scope: !404)
!3852 = !DILocation(line: 2096, column: 48, scope: !404)
!3853 = !DILocation(line: 2096, column: 14, scope: !404)
!3854 = !DILocation(line: 2097, column: 25, scope: !404)
!3855 = !DILocation(line: 2097, column: 28, scope: !404)
!3856 = !DILocation(line: 2097, column: 34, scope: !404)
!3857 = !DILocation(line: 2097, column: 2, scope: !404)
!3858 = !DILocation(line: 2099, column: 6, scope: !3859)
!3859 = distinct !DILexicalBlock(scope: !404, file: !1, line: 2099, column: 6)
!3860 = !DILocation(line: 2099, column: 9, scope: !3859)
!3861 = !DILocation(line: 2099, column: 24, scope: !3859)
!3862 = !DILocation(line: 2099, column: 28, scope: !3859)
!3863 = !DILocation(line: 2099, column: 41, scope: !3864)
!3864 = !DILexicalBlockFile(scope: !3859, file: !1, discriminator: 1)
!3865 = !DILocation(line: 2099, column: 65, scope: !3864)
!3866 = !DILocation(line: 2099, column: 31, scope: !3864)
!3867 = !DILocation(line: 2099, column: 34, scope: !3864)
!3868 = !DILocation(line: 2099, column: 39, scope: !3864)
!3869 = !DILocation(line: 2099, column: 69, scope: !3864)
!3870 = !DILocation(line: 2099, column: 6, scope: !3864)
!3871 = !DILocation(line: 2100, column: 27, scope: !3859)
!3872 = !DILocation(line: 2100, column: 30, scope: !3859)
!3873 = !DILocation(line: 2100, column: 3, scope: !3859)
!3874 = !DILocation(line: 2101, column: 16, scope: !404)
!3875 = !DILocation(line: 2101, column: 19, scope: !404)
!3876 = !DILocation(line: 2101, column: 24, scope: !404)
!3877 = !DILocation(line: 2101, column: 28, scope: !404)
!3878 = !DILocation(line: 2101, column: 26, scope: !404)
!3879 = !DILocation(line: 2101, column: 2, scope: !404)
!3880 = !DILocation(line: 2101, column: 5, scope: !404)
!3881 = !DILocation(line: 2101, column: 14, scope: !404)
!3882 = !DILocation(line: 2102, column: 19, scope: !404)
!3883 = !DILocation(line: 2102, column: 22, scope: !404)
!3884 = !DILocation(line: 2102, column: 28, scope: !404)
!3885 = !DILocation(line: 2102, column: 34, scope: !404)
!3886 = !DILocation(line: 2102, column: 2, scope: !404)
!3887 = !DILocation(line: 2103, column: 25, scope: !404)
!3888 = !DILocation(line: 2103, column: 28, scope: !404)
!3889 = !DILocation(line: 2103, column: 2, scope: !404)
!3890 = !DILocation(line: 2103, column: 5, scope: !404)
!3891 = !DILocation(line: 2103, column: 18, scope: !404)
!3892 = !DILocation(line: 2103, column: 23, scope: !404)
!3893 = !DILocation(line: 2104, column: 1, scope: !404)
!3894 = !DILocalVariable(name: "t", arg: 1, scope: !407, file: !1, line: 2152, type: !153)
!3895 = !DILocation(line: 2152, column: 27, scope: !407)
!3896 = !DILocalVariable(name: "flag", scope: !407, file: !1, line: 2154, type: !62)
!3897 = !DILocation(line: 2154, column: 6, scope: !407)
!3898 = !DILocalVariable(name: "new_fd", scope: !407, file: !1, line: 2154, type: !62)
!3899 = !DILocation(line: 2154, column: 12, scope: !407)
!3900 = !DILocalVariable(name: "r", scope: !407, file: !1, line: 2154, type: !62)
!3901 = !DILocation(line: 2154, column: 20, scope: !407)
!3902 = !DILocation(line: 2156, column: 22, scope: !407)
!3903 = !DILocation(line: 2156, column: 2, scope: !407)
!3904 = !DILocation(line: 2156, column: 5, scope: !407)
!3905 = !DILocation(line: 2156, column: 20, scope: !407)
!3906 = !DILocation(line: 2157, column: 7, scope: !407)
!3907 = !DILocation(line: 2159, column: 7, scope: !407)
!3908 = !DILocation(line: 2161, column: 31, scope: !407)
!3909 = !DILocation(line: 2161, column: 34, scope: !407)
!3910 = !DILocation(line: 2161, column: 37, scope: !407)
!3911 = !DILocation(line: 2161, column: 44, scope: !407)
!3912 = !DILocation(line: 2161, column: 49, scope: !407)
!3913 = !DILocation(line: 2161, column: 52, scope: !407)
!3914 = !DILocation(line: 2161, column: 11, scope: !407)
!3915 = !DILocation(line: 2161, column: 9, scope: !407)
!3916 = !DILocation(line: 2162, column: 32, scope: !407)
!3917 = !DILocation(line: 2162, column: 2, scope: !407)
!3918 = !DILocation(line: 2163, column: 6, scope: !3919)
!3919 = distinct !DILexicalBlock(scope: !407, file: !1, line: 2163, column: 6)
!3920 = !DILocation(line: 2163, column: 13, scope: !3919)
!3921 = !DILocation(line: 2163, column: 6, scope: !407)
!3922 = !DILocation(line: 2164, column: 19, scope: !3923)
!3923 = distinct !DILexicalBlock(scope: !3919, file: !1, line: 2163, column: 18)
!3924 = !DILocation(line: 2164, column: 3, scope: !3923)
!3925 = !DILocation(line: 2164, column: 6, scope: !3923)
!3926 = !DILocation(line: 2164, column: 17, scope: !3923)
!3927 = !DILocation(line: 2165, column: 5, scope: !3923)
!3928 = !DILocation(line: 2166, column: 2, scope: !3923)
!3929 = !DILocation(line: 2167, column: 3, scope: !3930)
!3930 = distinct !DILexicalBlock(scope: !3919, file: !1, line: 2166, column: 9)
!3931 = !DILocation(line: 2167, column: 6, scope: !3930)
!3932 = !DILocation(line: 2167, column: 11, scope: !3930)
!3933 = !DILocation(line: 2169, column: 7, scope: !3934)
!3934 = distinct !DILexicalBlock(scope: !3930, file: !1, line: 2169, column: 7)
!3935 = !DILocation(line: 2169, column: 10, scope: !3934)
!3936 = !DILocation(line: 2169, column: 17, scope: !3934)
!3937 = !DILocation(line: 2169, column: 23, scope: !3934)
!3938 = !DILocation(line: 2169, column: 7, scope: !3930)
!3939 = !DILocation(line: 2170, column: 34, scope: !3940)
!3940 = distinct !DILexicalBlock(scope: !3934, file: !1, line: 2169, column: 36)
!3941 = !DILocation(line: 2170, column: 37, scope: !3940)
!3942 = !DILocation(line: 2170, column: 4, scope: !3940)
!3943 = !DILocation(line: 2170, column: 7, scope: !3940)
!3944 = !DILocation(line: 2170, column: 14, scope: !3940)
!3945 = !DILocation(line: 2170, column: 32, scope: !3940)
!3946 = !DILocation(line: 2171, column: 4, scope: !3940)
!3947 = !DILocation(line: 2171, column: 7, scope: !3940)
!3948 = !DILocation(line: 2171, column: 16, scope: !3940)
!3949 = !DILocation(line: 2172, column: 8, scope: !3950)
!3950 = distinct !DILexicalBlock(scope: !3940, file: !1, line: 2172, column: 8)
!3951 = !DILocation(line: 2172, column: 11, scope: !3950)
!3952 = !DILocation(line: 2172, column: 23, scope: !3950)
!3953 = !DILocation(line: 2172, column: 26, scope: !3950)
!3954 = !DILocation(line: 2172, column: 21, scope: !3950)
!3955 = !DILocation(line: 2172, column: 8, scope: !3940)
!3956 = !DILocation(line: 2173, column: 23, scope: !3950)
!3957 = !DILocation(line: 2173, column: 26, scope: !3950)
!3958 = !DILocation(line: 2173, column: 5, scope: !3950)
!3959 = !DILocation(line: 2173, column: 8, scope: !3950)
!3960 = !DILocation(line: 2173, column: 21, scope: !3950)
!3961 = !DILocation(line: 2174, column: 3, scope: !3940)
!3962 = !DILocation(line: 2175, column: 10, scope: !3934)
!3963 = !DILocation(line: 2175, column: 13, scope: !3934)
!3964 = !DILocation(line: 2175, column: 4, scope: !3934)
!3965 = !DILocation(line: 2177, column: 23, scope: !3930)
!3966 = !DILocation(line: 2177, column: 3, scope: !3930)
!3967 = !DILocation(line: 2177, column: 6, scope: !3930)
!3968 = !DILocation(line: 2177, column: 21, scope: !3930)
!3969 = !DILocation(line: 2178, column: 3, scope: !3930)
!3970 = !DILocation(line: 2178, column: 6, scope: !3930)
!3971 = !DILocation(line: 2178, column: 12, scope: !3930)
!3972 = !DILocation(line: 2180, column: 10, scope: !407)
!3973 = !DILocation(line: 2180, column: 2, scope: !407)
!3974 = !DILocalVariable(name: "t", arg: 1, scope: !408, file: !1, line: 2187, type: !153)
!3975 = !DILocation(line: 2187, column: 26, scope: !408)
!3976 = !DILocalVariable(name: "te", scope: !408, file: !1, line: 2189, type: !157)
!3977 = !DILocation(line: 2189, column: 21, scope: !408)
!3978 = !DILocalVariable(name: "new_fd", scope: !408, file: !1, line: 2190, type: !62)
!3979 = !DILocation(line: 2190, column: 6, scope: !408)
!3980 = !DILocalVariable(name: "r", scope: !408, file: !1, line: 2190, type: !62)
!3981 = !DILocation(line: 2190, column: 14, scope: !408)
!3982 = !DILocalVariable(name: "prev_dir_fd", scope: !408, file: !1, line: 2190, type: !62)
!3983 = !DILocation(line: 2190, column: 21, scope: !408)
!3984 = !DILocation(line: 2192, column: 7, scope: !408)
!3985 = !DILocation(line: 2192, column: 10, scope: !408)
!3986 = !DILocation(line: 2192, column: 5, scope: !408)
!3987 = !DILocation(line: 2193, column: 16, scope: !408)
!3988 = !DILocation(line: 2193, column: 19, scope: !408)
!3989 = !DILocation(line: 2193, column: 14, scope: !408)
!3990 = !DILocation(line: 2194, column: 6, scope: !3991)
!3991 = distinct !DILexicalBlock(scope: !408, file: !1, line: 2194, column: 6)
!3992 = !DILocation(line: 2194, column: 10, scope: !3991)
!3993 = !DILocation(line: 2194, column: 16, scope: !3991)
!3994 = !DILocation(line: 2194, column: 6, scope: !408)
!3995 = !DILocation(line: 2195, column: 12, scope: !3991)
!3996 = !DILocation(line: 2195, column: 16, scope: !3991)
!3997 = !DILocation(line: 2195, column: 10, scope: !3991)
!3998 = !DILocation(line: 2195, column: 3, scope: !3991)
!3999 = !DILocation(line: 2197, column: 32, scope: !4000)
!4000 = distinct !DILexicalBlock(scope: !3991, file: !1, line: 2196, column: 7)
!4001 = !DILocation(line: 2197, column: 12, scope: !4000)
!4002 = !DILocation(line: 2197, column: 10, scope: !4000)
!4003 = !DILocation(line: 2198, column: 33, scope: !4000)
!4004 = !DILocation(line: 2198, column: 3, scope: !4000)
!4005 = !DILocation(line: 2200, column: 6, scope: !4006)
!4006 = distinct !DILexicalBlock(scope: !408, file: !1, line: 2200, column: 6)
!4007 = !DILocation(line: 2200, column: 13, scope: !4006)
!4008 = !DILocation(line: 2200, column: 6, scope: !408)
!4009 = !DILocation(line: 2201, column: 19, scope: !4010)
!4010 = distinct !DILexicalBlock(scope: !4006, file: !1, line: 2200, column: 18)
!4011 = !DILocation(line: 2201, column: 3, scope: !4010)
!4012 = !DILocation(line: 2201, column: 6, scope: !4010)
!4013 = !DILocation(line: 2201, column: 17, scope: !4010)
!4014 = !DILocation(line: 2202, column: 5, scope: !4010)
!4015 = !DILocation(line: 2203, column: 2, scope: !4010)
!4016 = !DILocation(line: 2205, column: 23, scope: !4017)
!4017 = distinct !DILexicalBlock(scope: !4006, file: !1, line: 2203, column: 9)
!4018 = !DILocation(line: 2205, column: 3, scope: !4017)
!4019 = !DILocation(line: 2205, column: 6, scope: !4017)
!4020 = !DILocation(line: 2205, column: 21, scope: !4017)
!4021 = !DILocation(line: 2206, column: 3, scope: !4017)
!4022 = !DILocation(line: 2206, column: 6, scope: !4017)
!4023 = !DILocation(line: 2206, column: 12, scope: !4017)
!4024 = !DILocation(line: 2209, column: 26, scope: !4017)
!4025 = !DILocation(line: 2209, column: 39, scope: !4017)
!4026 = !DILocation(line: 2209, column: 43, scope: !4017)
!4027 = !DILocation(line: 2209, column: 47, scope: !4017)
!4028 = !DILocation(line: 2209, column: 3, scope: !4017)
!4029 = !DILocation(line: 2210, column: 7, scope: !4030)
!4030 = distinct !DILexicalBlock(scope: !4017, file: !1, line: 2210, column: 7)
!4031 = !DILocation(line: 2210, column: 11, scope: !4030)
!4032 = !DILocation(line: 2210, column: 17, scope: !4030)
!4033 = !DILocation(line: 2210, column: 7, scope: !4017)
!4034 = !DILocation(line: 2211, column: 4, scope: !4035)
!4035 = distinct !DILexicalBlock(scope: !4030, file: !1, line: 2210, column: 30)
!4036 = !DILocation(line: 2211, column: 7, scope: !4035)
!4037 = !DILocation(line: 2211, column: 16, scope: !4035)
!4038 = !DILocation(line: 2212, column: 4, scope: !4035)
!4039 = !DILocation(line: 2212, column: 8, scope: !4035)
!4040 = !DILocation(line: 2212, column: 26, scope: !4035)
!4041 = !DILocation(line: 2213, column: 3, scope: !4035)
!4042 = !DILocation(line: 2214, column: 3, scope: !4017)
!4043 = !DILocation(line: 2214, column: 6, scope: !4017)
!4044 = !DILocation(line: 2214, column: 11, scope: !4017)
!4045 = !DILocation(line: 2216, column: 10, scope: !408)
!4046 = !DILocation(line: 2216, column: 2, scope: !408)
!4047 = !DILocalVariable(name: "fd", arg: 1, scope: !401, file: !1, line: 2026, type: !62)
!4048 = !DILocation(line: 2026, column: 14, scope: !401)
!4049 = !DILocalVariable(name: "new_fd", scope: !401, file: !1, line: 2028, type: !62)
!4050 = !DILocation(line: 2028, column: 6, scope: !401)
!4051 = !DILocation(line: 2032, column: 6, scope: !4052)
!4052 = distinct !DILexicalBlock(scope: !401, file: !1, line: 2032, column: 6)
!4053 = !DILocation(line: 2032, column: 6, scope: !401)
!4054 = !DILocation(line: 2033, column: 18, scope: !4055)
!4055 = distinct !DILexicalBlock(scope: !4052, file: !1, line: 2032, column: 25)
!4056 = !DILocation(line: 2033, column: 12, scope: !4055)
!4057 = !DILocation(line: 2033, column: 10, scope: !4055)
!4058 = !DILocation(line: 2034, column: 7, scope: !4059)
!4059 = distinct !DILexicalBlock(scope: !4055, file: !1, line: 2034, column: 7)
!4060 = !DILocation(line: 2034, column: 14, scope: !4059)
!4061 = !DILocation(line: 2034, column: 7, scope: !4055)
!4062 = !DILocation(line: 2035, column: 12, scope: !4059)
!4063 = !DILocation(line: 2035, column: 4, scope: !4059)
!4064 = !DILocation(line: 2039, column: 21, scope: !4055)
!4065 = !DILocation(line: 2040, column: 2, scope: !4055)
!4066 = !DILocation(line: 2042, column: 15, scope: !401)
!4067 = !DILocation(line: 2042, column: 11, scope: !401)
!4068 = !DILocation(line: 2042, column: 9, scope: !401)
!4069 = !DILocation(line: 2043, column: 32, scope: !401)
!4070 = !DILocation(line: 2043, column: 2, scope: !401)
!4071 = !DILocation(line: 2044, column: 10, scope: !401)
!4072 = !DILocation(line: 2044, column: 2, scope: !401)
!4073 = !DILocation(line: 2045, column: 1, scope: !401)
!4074 = !DILocalVariable(name: "a", arg: 1, scope: !421, file: !1, line: 1695, type: !43)
!4075 = !DILocation(line: 1695, column: 52, scope: !421)
!4076 = !DILocalVariable(name: "t", scope: !421, file: !1, line: 1697, type: !153)
!4077 = !DILocation(line: 1697, column: 15, scope: !421)
!4078 = !DILocation(line: 1697, column: 19, scope: !421)
!4079 = !DILocation(line: 1697, column: 22, scope: !421)
!4080 = !DILocalVariable(name: "sfs", scope: !421, file: !1, line: 1698, type: !4081)
!4081 = !DICompositeType(tag: DW_TAG_structure_type, name: "statfs", file: !4082, line: 24, size: 960, align: 64, elements: !4083)
!4082 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/statfs.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!4083 = !{!4084, !4086, !4087, !4089, !4090, !4091, !4093, !4094, !4100, !4101, !4102, !4103}
!4084 = !DIDerivedType(tag: DW_TAG_member, name: "f_type", scope: !4081, file: !4082, line: 26, baseType: !4085, size: 64, align: 64)
!4085 = !DIDerivedType(tag: DW_TAG_typedef, name: "__fsword_t", file: !80, line: 170, baseType: !81)
!4086 = !DIDerivedType(tag: DW_TAG_member, name: "f_bsize", scope: !4081, file: !4082, line: 27, baseType: !4085, size: 64, align: 64, offset: 64)
!4087 = !DIDerivedType(tag: DW_TAG_member, name: "f_blocks", scope: !4081, file: !4082, line: 29, baseType: !4088, size: 64, align: 64, offset: 128)
!4088 = !DIDerivedType(tag: DW_TAG_typedef, name: "__fsblkcnt_t", file: !80, line: 162, baseType: !86)
!4089 = !DIDerivedType(tag: DW_TAG_member, name: "f_bfree", scope: !4081, file: !4082, line: 30, baseType: !4088, size: 64, align: 64, offset: 192)
!4090 = !DIDerivedType(tag: DW_TAG_member, name: "f_bavail", scope: !4081, file: !4082, line: 31, baseType: !4088, size: 64, align: 64, offset: 256)
!4091 = !DIDerivedType(tag: DW_TAG_member, name: "f_files", scope: !4081, file: !4082, line: 32, baseType: !4092, size: 64, align: 64, offset: 320)
!4092 = !DIDerivedType(tag: DW_TAG_typedef, name: "__fsfilcnt_t", file: !80, line: 166, baseType: !86)
!4093 = !DIDerivedType(tag: DW_TAG_member, name: "f_ffree", scope: !4081, file: !4082, line: 33, baseType: !4092, size: 64, align: 64, offset: 384)
!4094 = !DIDerivedType(tag: DW_TAG_member, name: "f_fsid", scope: !4081, file: !4082, line: 41, baseType: !4095, size: 64, align: 32, offset: 448)
!4095 = !DIDerivedType(tag: DW_TAG_typedef, name: "__fsid_t", file: !80, line: 134, baseType: !4096)
!4096 = !DICompositeType(tag: DW_TAG_structure_type, file: !80, line: 134, size: 64, align: 32, elements: !4097)
!4097 = !{!4098}
!4098 = !DIDerivedType(tag: DW_TAG_member, name: "__val", scope: !4096, file: !80, line: 134, baseType: !4099, size: 64, align: 32)
!4099 = !DICompositeType(tag: DW_TAG_array_type, baseType: !62, size: 64, align: 32, elements: !2303)
!4100 = !DIDerivedType(tag: DW_TAG_member, name: "f_namelen", scope: !4081, file: !4082, line: 42, baseType: !4085, size: 64, align: 64, offset: 512)
!4101 = !DIDerivedType(tag: DW_TAG_member, name: "f_frsize", scope: !4081, file: !4082, line: 43, baseType: !4085, size: 64, align: 64, offset: 576)
!4102 = !DIDerivedType(tag: DW_TAG_member, name: "f_flags", scope: !4081, file: !4082, line: 44, baseType: !4085, size: 64, align: 64, offset: 640)
!4103 = !DIDerivedType(tag: DW_TAG_member, name: "f_spare", scope: !4081, file: !4082, line: 45, baseType: !4104, size: 256, align: 64, offset: 704)
!4104 = !DICompositeType(tag: DW_TAG_array_type, baseType: !4085, size: 256, align: 64, elements: !4105)
!4105 = !{!4106}
!4106 = !DISubrange(count: 4)
!4107 = !DILocation(line: 1698, column: 16, scope: !421)
!4108 = !DILocalVariable(name: "svfs", scope: !421, file: !1, line: 1700, type: !4109)
!4109 = !DICompositeType(tag: DW_TAG_structure_type, name: "statvfs", file: !4, line: 29, size: 896, align: 64, elements: !4110)
!4110 = !{!4111, !4112, !4113, !4114, !4115, !4116, !4117, !4118, !4119, !4120, !4121, !4122}
!4111 = !DIDerivedType(tag: DW_TAG_member, name: "f_bsize", scope: !4109, file: !4, line: 31, baseType: !86, size: 64, align: 64)
!4112 = !DIDerivedType(tag: DW_TAG_member, name: "f_frsize", scope: !4109, file: !4, line: 32, baseType: !86, size: 64, align: 64, offset: 64)
!4113 = !DIDerivedType(tag: DW_TAG_member, name: "f_blocks", scope: !4109, file: !4, line: 34, baseType: !4088, size: 64, align: 64, offset: 128)
!4114 = !DIDerivedType(tag: DW_TAG_member, name: "f_bfree", scope: !4109, file: !4, line: 35, baseType: !4088, size: 64, align: 64, offset: 192)
!4115 = !DIDerivedType(tag: DW_TAG_member, name: "f_bavail", scope: !4109, file: !4, line: 36, baseType: !4088, size: 64, align: 64, offset: 256)
!4116 = !DIDerivedType(tag: DW_TAG_member, name: "f_files", scope: !4109, file: !4, line: 37, baseType: !4092, size: 64, align: 64, offset: 320)
!4117 = !DIDerivedType(tag: DW_TAG_member, name: "f_ffree", scope: !4109, file: !4, line: 38, baseType: !4092, size: 64, align: 64, offset: 384)
!4118 = !DIDerivedType(tag: DW_TAG_member, name: "f_favail", scope: !4109, file: !4, line: 39, baseType: !4092, size: 64, align: 64, offset: 448)
!4119 = !DIDerivedType(tag: DW_TAG_member, name: "f_fsid", scope: !4109, file: !4, line: 48, baseType: !86, size: 64, align: 64, offset: 512)
!4120 = !DIDerivedType(tag: DW_TAG_member, name: "f_flag", scope: !4109, file: !4, line: 52, baseType: !86, size: 64, align: 64, offset: 576)
!4121 = !DIDerivedType(tag: DW_TAG_member, name: "f_namemax", scope: !4109, file: !4, line: 53, baseType: !86, size: 64, align: 64, offset: 640)
!4122 = !DIDerivedType(tag: DW_TAG_member, name: "__f_spare", scope: !4109, file: !4, line: 54, baseType: !4123, size: 192, align: 32, offset: 704)
!4123 = !DICompositeType(tag: DW_TAG_array_type, baseType: !62, size: 192, align: 32, elements: !4124)
!4124 = !{!4125}
!4125 = !DISubrange(count: 6)
!4126 = !DILocation(line: 1700, column: 17, scope: !421)
!4127 = !DILocalVariable(name: "r", scope: !421, file: !1, line: 1702, type: !62)
!4128 = !DILocation(line: 1702, column: 6, scope: !421)
!4129 = !DILocalVariable(name: "vr", scope: !421, file: !1, line: 1702, type: !62)
!4130 = !DILocation(line: 1702, column: 9, scope: !421)
!4131 = !DILocalVariable(name: "xr", scope: !421, file: !1, line: 1702, type: !62)
!4132 = !DILocation(line: 1702, column: 17, scope: !421)
!4133 = !DILocation(line: 1704, column: 42, scope: !4134)
!4134 = distinct !DILexicalBlock(scope: !421, file: !1, line: 1704, column: 6)
!4135 = !DILocation(line: 1704, column: 6, scope: !4134)
!4136 = !DILocation(line: 1704, column: 6, scope: !421)
!4137 = !DILocalVariable(name: "fd", scope: !4138, file: !1, line: 1710, type: !62)
!4138 = distinct !DILexicalBlock(scope: !4134, file: !1, line: 1704, column: 46)
!4139 = !DILocation(line: 1710, column: 7, scope: !4138)
!4140 = !DILocation(line: 1710, column: 39, scope: !4138)
!4141 = !DILocation(line: 1710, column: 19, scope: !4138)
!4142 = !DILocation(line: 1711, column: 32, scope: !4138)
!4143 = !DILocation(line: 1711, column: 7, scope: !4138)
!4144 = !DILocation(line: 1710, column: 12, scope: !4138)
!4145 = !DILocation(line: 1712, column: 33, scope: !4138)
!4146 = !DILocation(line: 1712, column: 3, scope: !4138)
!4147 = !DILocation(line: 1713, column: 7, scope: !4148)
!4148 = distinct !DILexicalBlock(scope: !4138, file: !1, line: 1713, column: 7)
!4149 = !DILocation(line: 1713, column: 10, scope: !4148)
!4150 = !DILocation(line: 1713, column: 7, scope: !4138)
!4151 = !DILocation(line: 1714, column: 23, scope: !4152)
!4152 = distinct !DILexicalBlock(scope: !4148, file: !1, line: 1713, column: 15)
!4153 = !DILocation(line: 1714, column: 26, scope: !4152)
!4154 = !DILocation(line: 1714, column: 35, scope: !4152)
!4155 = !DILocation(line: 1714, column: 4, scope: !4156)
!4156 = !DILexicalBlockFile(scope: !4152, file: !1, discriminator: 1)
!4157 = !DILocation(line: 1716, column: 4, scope: !4152)
!4158 = !DILocation(line: 1719, column: 17, scope: !4138)
!4159 = !DILocation(line: 1719, column: 8, scope: !4138)
!4160 = !DILocation(line: 1719, column: 6, scope: !4138)
!4161 = !DILocation(line: 1721, column: 15, scope: !4138)
!4162 = !DILocation(line: 1721, column: 7, scope: !4138)
!4163 = !DILocation(line: 1721, column: 5, scope: !4138)
!4164 = !DILocation(line: 1722, column: 7, scope: !4165)
!4165 = distinct !DILexicalBlock(scope: !4138, file: !1, line: 1722, column: 7)
!4166 = !DILocation(line: 1722, column: 9, scope: !4165)
!4167 = !DILocation(line: 1722, column: 7, scope: !4138)
!4168 = !DILocation(line: 1723, column: 23, scope: !4165)
!4169 = !DILocation(line: 1723, column: 26, scope: !4165)
!4170 = !DILocation(line: 1723, column: 9, scope: !4165)
!4171 = !DILocation(line: 1723, column: 7, scope: !4165)
!4172 = !DILocation(line: 1723, column: 4, scope: !4165)
!4173 = !DILocation(line: 1724, column: 9, scope: !4138)
!4174 = !DILocation(line: 1724, column: 3, scope: !4138)
!4175 = !DILocation(line: 1737, column: 2, scope: !4138)
!4176 = !DILocation(line: 1740, column: 37, scope: !4177)
!4177 = distinct !DILexicalBlock(scope: !4134, file: !1, line: 1737, column: 9)
!4178 = !DILocation(line: 1740, column: 17, scope: !4177)
!4179 = !DILocation(line: 1740, column: 8, scope: !4180)
!4180 = !DILexicalBlockFile(scope: !4177, file: !1, discriminator: 1)
!4181 = !DILocation(line: 1740, column: 6, scope: !4177)
!4182 = !DILocation(line: 1742, column: 35, scope: !4177)
!4183 = !DILocation(line: 1742, column: 15, scope: !4177)
!4184 = !DILocation(line: 1742, column: 7, scope: !4180)
!4185 = !DILocation(line: 1742, column: 5, scope: !4177)
!4186 = !DILocation(line: 1743, column: 7, scope: !4187)
!4187 = distinct !DILexicalBlock(scope: !4177, file: !1, line: 1743, column: 7)
!4188 = !DILocation(line: 1743, column: 9, scope: !4187)
!4189 = !DILocation(line: 1743, column: 7, scope: !4177)
!4190 = !DILocation(line: 1744, column: 23, scope: !4187)
!4191 = !DILocation(line: 1744, column: 46, scope: !4187)
!4192 = !DILocation(line: 1744, column: 26, scope: !4187)
!4193 = !DILocation(line: 1744, column: 9, scope: !4194)
!4194 = !DILexicalBlockFile(scope: !4187, file: !1, discriminator: 1)
!4195 = !DILocation(line: 1744, column: 7, scope: !4187)
!4196 = !DILocation(line: 1744, column: 4, scope: !4187)
!4197 = !DILocation(line: 1758, column: 6, scope: !4198)
!4198 = distinct !DILexicalBlock(scope: !421, file: !1, line: 1758, column: 6)
!4199 = !DILocation(line: 1758, column: 8, scope: !4198)
!4200 = !DILocation(line: 1758, column: 14, scope: !4198)
!4201 = !DILocation(line: 1758, column: 17, scope: !4202)
!4202 = !DILexicalBlockFile(scope: !4198, file: !1, discriminator: 1)
!4203 = !DILocation(line: 1758, column: 20, scope: !4202)
!4204 = !DILocation(line: 1758, column: 26, scope: !4202)
!4205 = !DILocation(line: 1758, column: 29, scope: !4206)
!4206 = !DILexicalBlockFile(scope: !4198, file: !1, discriminator: 2)
!4207 = !DILocation(line: 1758, column: 32, scope: !4206)
!4208 = !DILocation(line: 1758, column: 6, scope: !4206)
!4209 = !DILocation(line: 1759, column: 3, scope: !4210)
!4210 = distinct !DILexicalBlock(scope: !4198, file: !1, line: 1758, column: 39)
!4211 = !DILocation(line: 1759, column: 6, scope: !4210)
!4212 = !DILocation(line: 1759, column: 26, scope: !4210)
!4213 = !DILocation(line: 1759, column: 36, scope: !4210)
!4214 = !DILocation(line: 1760, column: 3, scope: !4210)
!4215 = !DILocation(line: 1760, column: 6, scope: !4210)
!4216 = !DILocation(line: 1760, column: 26, scope: !4210)
!4217 = !DILocation(line: 1760, column: 33, scope: !4210)
!4218 = !DILocation(line: 1761, column: 22, scope: !4210)
!4219 = !DILocation(line: 1761, column: 25, scope: !4210)
!4220 = !DILocation(line: 1761, column: 34, scope: !4210)
!4221 = !DILocation(line: 1761, column: 3, scope: !4222)
!4222 = !DILexicalBlockFile(scope: !4210, file: !1, discriminator: 1)
!4223 = !DILocation(line: 1762, column: 3, scope: !4210)
!4224 = !DILocation(line: 1763, column: 13, scope: !4225)
!4225 = distinct !DILexicalBlock(scope: !4198, file: !1, line: 1763, column: 13)
!4226 = !DILocation(line: 1763, column: 16, scope: !4225)
!4227 = !DILocation(line: 1763, column: 13, scope: !4198)
!4228 = !DILocation(line: 1766, column: 44, scope: !4229)
!4229 = distinct !DILexicalBlock(scope: !4225, file: !1, line: 1763, column: 22)
!4230 = !DILocation(line: 1766, column: 3, scope: !4229)
!4231 = !DILocation(line: 1766, column: 6, scope: !4229)
!4232 = !DILocation(line: 1766, column: 26, scope: !4229)
!4233 = !DILocation(line: 1766, column: 37, scope: !4229)
!4234 = !DILocation(line: 1767, column: 3, scope: !4229)
!4235 = !DILocation(line: 1767, column: 6, scope: !4229)
!4236 = !DILocation(line: 1767, column: 26, scope: !4229)
!4237 = !DILocation(line: 1767, column: 40, scope: !4229)
!4238 = !DILocation(line: 1768, column: 47, scope: !4229)
!4239 = !DILocation(line: 1768, column: 3, scope: !4229)
!4240 = !DILocation(line: 1768, column: 6, scope: !4229)
!4241 = !DILocation(line: 1768, column: 26, scope: !4229)
!4242 = !DILocation(line: 1768, column: 40, scope: !4229)
!4243 = !DILocation(line: 1769, column: 48, scope: !4229)
!4244 = !DILocation(line: 1769, column: 3, scope: !4229)
!4245 = !DILocation(line: 1769, column: 6, scope: !4229)
!4246 = !DILocation(line: 1769, column: 26, scope: !4229)
!4247 = !DILocation(line: 1769, column: 41, scope: !4229)
!4248 = !DILocation(line: 1776, column: 2, scope: !4229)
!4249 = !DILocation(line: 1777, column: 14, scope: !421)
!4250 = !DILocation(line: 1777, column: 2, scope: !421)
!4251 = !DILocation(line: 1784, column: 3, scope: !4252)
!4252 = distinct !DILexicalBlock(scope: !421, file: !1, line: 1777, column: 22)
!4253 = !DILocation(line: 1784, column: 6, scope: !4252)
!4254 = !DILocation(line: 1784, column: 26, scope: !4252)
!4255 = !DILocation(line: 1784, column: 33, scope: !4252)
!4256 = !DILocation(line: 1785, column: 3, scope: !4252)
!4257 = !DILocation(line: 1785, column: 6, scope: !4252)
!4258 = !DILocation(line: 1785, column: 26, scope: !4252)
!4259 = !DILocation(line: 1785, column: 36, scope: !4252)
!4260 = !DILocation(line: 1786, column: 3, scope: !4252)
!4261 = !DILocation(line: 1790, column: 3, scope: !4252)
!4262 = !DILocation(line: 1790, column: 6, scope: !4252)
!4263 = !DILocation(line: 1790, column: 26, scope: !4252)
!4264 = !DILocation(line: 1790, column: 33, scope: !4252)
!4265 = !DILocation(line: 1791, column: 3, scope: !4252)
!4266 = !DILocation(line: 1791, column: 6, scope: !4252)
!4267 = !DILocation(line: 1791, column: 26, scope: !4252)
!4268 = !DILocation(line: 1791, column: 36, scope: !4252)
!4269 = !DILocation(line: 1792, column: 3, scope: !4252)
!4270 = !DILocation(line: 1794, column: 3, scope: !4252)
!4271 = !DILocation(line: 1794, column: 6, scope: !4252)
!4272 = !DILocation(line: 1794, column: 26, scope: !4252)
!4273 = !DILocation(line: 1794, column: 33, scope: !4252)
!4274 = !DILocation(line: 1795, column: 3, scope: !4252)
!4275 = !DILocation(line: 1795, column: 6, scope: !4252)
!4276 = !DILocation(line: 1795, column: 26, scope: !4252)
!4277 = !DILocation(line: 1795, column: 36, scope: !4252)
!4278 = !DILocation(line: 1796, column: 3, scope: !4252)
!4279 = !DILocation(line: 1801, column: 11, scope: !4280)
!4280 = distinct !DILexicalBlock(scope: !421, file: !1, line: 1801, column: 6)
!4281 = !DILocation(line: 1801, column: 18, scope: !4280)
!4282 = !DILocation(line: 1801, column: 6, scope: !421)
!4283 = !DILocation(line: 1805, column: 3, scope: !4280)
!4284 = !DILocation(line: 1805, column: 6, scope: !4280)
!4285 = !DILocation(line: 1805, column: 26, scope: !4280)
!4286 = !DILocation(line: 1805, column: 34, scope: !4280)
!4287 = !DILocation(line: 1808, column: 3, scope: !4280)
!4288 = !DILocation(line: 1808, column: 6, scope: !4280)
!4289 = !DILocation(line: 1808, column: 26, scope: !4280)
!4290 = !DILocation(line: 1808, column: 34, scope: !4280)
!4291 = !DILocation(line: 1812, column: 40, scope: !421)
!4292 = !DILocation(line: 1812, column: 2, scope: !421)
!4293 = !DILocation(line: 1812, column: 5, scope: !421)
!4294 = !DILocation(line: 1812, column: 25, scope: !421)
!4295 = !DILocation(line: 1812, column: 34, scope: !421)
!4296 = !DILocation(line: 1814, column: 2, scope: !421)
!4297 = !DILocation(line: 1815, column: 1, scope: !421)
!4298 = !DILocalVariable(name: "t", arg: 1, scope: !422, file: !1, line: 2577, type: !153)
!4299 = !DILocation(line: 2577, column: 50, scope: !422)
!4300 = !DILocation(line: 2581, column: 27, scope: !422)
!4301 = !DILocation(line: 2581, column: 8, scope: !422)
!4302 = !DILocation(line: 2581, column: 6, scope: !422)
!4303 = !DILocation(line: 2582, column: 25, scope: !422)
!4304 = !DILocation(line: 2582, column: 7, scope: !422)
!4305 = !DILocation(line: 2582, column: 5, scope: !422)
!4306 = !DILocation(line: 2583, column: 10, scope: !422)
!4307 = !DILocation(line: 2583, column: 13, scope: !422)
!4308 = !DILocation(line: 2583, column: 21, scope: !422)
!4309 = !DILocation(line: 2583, column: 24, scope: !4310)
!4310 = !DILexicalBlockFile(scope: !422, file: !1, discriminator: 1)
!4311 = !DILocation(line: 2583, column: 28, scope: !4310)
!4312 = !DILocation(line: 2583, column: 36, scope: !4310)
!4313 = !DILocation(line: 2584, column: 15, scope: !422)
!4314 = !DILocation(line: 2584, column: 19, scope: !422)
!4315 = !DILocation(line: 2584, column: 29, scope: !422)
!4316 = !DILocation(line: 2584, column: 32, scope: !422)
!4317 = !DILocation(line: 2584, column: 52, scope: !422)
!4318 = !DILocation(line: 2584, column: 26, scope: !422)
!4319 = !DILocation(line: 2584, column: 56, scope: !422)
!4320 = !DILocation(line: 2585, column: 6, scope: !422)
!4321 = !DILocation(line: 2585, column: 10, scope: !422)
!4322 = !DILocation(line: 2585, column: 20, scope: !422)
!4323 = !DILocation(line: 2585, column: 25, scope: !422)
!4324 = !DILocation(line: 2585, column: 17, scope: !422)
!4325 = !DILocation(line: 2584, column: 56, scope: !4310)
!4326 = !DILocation(line: 2583, column: 2, scope: !4327)
!4327 = !DILexicalBlockFile(scope: !422, file: !1, discriminator: 2)
!4328 = !DILocalVariable(name: "t", arg: 1, scope: !423, file: !1, line: 1445, type: !153)
!4329 = !DILocation(line: 1445, column: 28, scope: !423)
!4330 = !DILocalVariable(name: "fd", arg: 2, scope: !423, file: !1, line: 1445, type: !62)
!4331 = !DILocation(line: 1445, column: 35, scope: !423)
!4332 = !DILocalVariable(name: "path", arg: 3, scope: !423, file: !1, line: 1445, type: !119)
!4333 = !DILocation(line: 1445, column: 51, scope: !423)
!4334 = !DILocation(line: 1447, column: 2, scope: !423)
!4335 = !DILocation(line: 1447, column: 5, scope: !423)
!4336 = !DILocation(line: 1447, column: 25, scope: !423)
!4337 = !DILocation(line: 1447, column: 36, scope: !423)
!4338 = !DILocation(line: 1448, column: 2, scope: !423)
!4339 = !DILocation(line: 1448, column: 8, scope: !423)
!4340 = !DILocation(line: 1449, column: 6, scope: !4341)
!4341 = distinct !DILexicalBlock(scope: !423, file: !1, line: 1449, column: 6)
!4342 = !DILocation(line: 1449, column: 9, scope: !4341)
!4343 = !DILocation(line: 1449, column: 6, scope: !423)
!4344 = !DILocation(line: 1451, column: 17, scope: !4345)
!4345 = distinct !DILexicalBlock(scope: !4341, file: !1, line: 1449, column: 15)
!4346 = !DILocation(line: 1451, column: 7, scope: !4345)
!4347 = !DILocation(line: 1450, column: 3, scope: !4345)
!4348 = !DILocation(line: 1450, column: 6, scope: !4345)
!4349 = !DILocation(line: 1450, column: 26, scope: !4345)
!4350 = !DILocation(line: 1450, column: 41, scope: !4345)
!4351 = !DILocation(line: 1453, column: 17, scope: !4345)
!4352 = !DILocation(line: 1453, column: 7, scope: !4345)
!4353 = !DILocation(line: 1452, column: 3, scope: !4345)
!4354 = !DILocation(line: 1452, column: 6, scope: !4345)
!4355 = !DILocation(line: 1452, column: 26, scope: !4345)
!4356 = !DILocation(line: 1452, column: 40, scope: !4345)
!4357 = !DILocation(line: 1455, column: 17, scope: !4345)
!4358 = !DILocation(line: 1455, column: 7, scope: !4345)
!4359 = !DILocation(line: 1454, column: 3, scope: !4345)
!4360 = !DILocation(line: 1454, column: 6, scope: !4345)
!4361 = !DILocation(line: 1454, column: 26, scope: !4345)
!4362 = !DILocation(line: 1454, column: 40, scope: !4345)
!4363 = !DILocation(line: 1457, column: 17, scope: !4345)
!4364 = !DILocation(line: 1457, column: 7, scope: !4345)
!4365 = !DILocation(line: 1456, column: 3, scope: !4345)
!4366 = !DILocation(line: 1456, column: 6, scope: !4345)
!4367 = !DILocation(line: 1456, column: 26, scope: !4345)
!4368 = !DILocation(line: 1456, column: 37, scope: !4345)
!4369 = !DILocation(line: 1458, column: 2, scope: !4345)
!4370 = !DILocation(line: 1458, column: 13, scope: !4371)
!4371 = !DILexicalBlockFile(scope: !4372, file: !1, discriminator: 1)
!4372 = distinct !DILexicalBlock(scope: !4341, file: !1, line: 1458, column: 13)
!4373 = !DILocation(line: 1458, column: 18, scope: !4371)
!4374 = !DILocation(line: 1460, column: 16, scope: !4375)
!4375 = distinct !DILexicalBlock(scope: !4372, file: !1, line: 1458, column: 27)
!4376 = !DILocation(line: 1460, column: 7, scope: !4375)
!4377 = !DILocation(line: 1459, column: 3, scope: !4375)
!4378 = !DILocation(line: 1459, column: 6, scope: !4375)
!4379 = !DILocation(line: 1459, column: 26, scope: !4375)
!4380 = !DILocation(line: 1459, column: 41, scope: !4375)
!4381 = !DILocation(line: 1462, column: 16, scope: !4375)
!4382 = !DILocation(line: 1462, column: 7, scope: !4375)
!4383 = !DILocation(line: 1461, column: 3, scope: !4375)
!4384 = !DILocation(line: 1461, column: 6, scope: !4375)
!4385 = !DILocation(line: 1461, column: 26, scope: !4375)
!4386 = !DILocation(line: 1461, column: 40, scope: !4375)
!4387 = !DILocation(line: 1464, column: 16, scope: !4375)
!4388 = !DILocation(line: 1464, column: 7, scope: !4375)
!4389 = !DILocation(line: 1463, column: 3, scope: !4375)
!4390 = !DILocation(line: 1463, column: 6, scope: !4375)
!4391 = !DILocation(line: 1463, column: 26, scope: !4375)
!4392 = !DILocation(line: 1463, column: 40, scope: !4375)
!4393 = !DILocation(line: 1466, column: 16, scope: !4375)
!4394 = !DILocation(line: 1466, column: 7, scope: !4375)
!4395 = !DILocation(line: 1465, column: 3, scope: !4375)
!4396 = !DILocation(line: 1465, column: 6, scope: !4375)
!4397 = !DILocation(line: 1465, column: 26, scope: !4375)
!4398 = !DILocation(line: 1465, column: 37, scope: !4375)
!4399 = !DILocation(line: 1467, column: 2, scope: !4375)
!4400 = !DILocation(line: 1469, column: 6, scope: !4401)
!4401 = distinct !DILexicalBlock(scope: !423, file: !1, line: 1469, column: 6)
!4402 = !DILocation(line: 1469, column: 9, scope: !4401)
!4403 = !DILocation(line: 1469, column: 29, scope: !4401)
!4404 = !DILocation(line: 1469, column: 40, scope: !4401)
!4405 = !DILocation(line: 1469, column: 6, scope: !423)
!4406 = !DILocation(line: 1470, column: 12, scope: !4401)
!4407 = !DILocation(line: 1470, column: 18, scope: !4401)
!4408 = !DILocation(line: 1470, column: 11, scope: !4401)
!4409 = !DILocation(line: 1470, column: 3, scope: !4401)
!4410 = !DILocation(line: 1472, column: 3, scope: !4401)
!4411 = !DILocation(line: 1473, column: 1, scope: !423)
!4412 = !DILocalVariable(name: "t", arg: 1, scope: !435, file: !1, line: 2123, type: !153)
!4413 = !DILocation(line: 2123, column: 26, scope: !435)
!4414 = !DILocalVariable(name: "path", arg: 2, scope: !435, file: !1, line: 2123, type: !119)
!4415 = !DILocation(line: 2123, column: 41, scope: !435)
!4416 = !DILocalVariable(name: "restore_time", arg: 3, scope: !435, file: !1, line: 2123, type: !62)
!4417 = !DILocation(line: 2123, column: 51, scope: !435)
!4418 = !DILocation(line: 2125, column: 14, scope: !435)
!4419 = !DILocation(line: 2125, column: 27, scope: !435)
!4420 = !DILocation(line: 2125, column: 13, scope: !435)
!4421 = !DILocation(line: 2125, column: 2, scope: !435)
!4422 = !DILocation(line: 2125, column: 5, scope: !435)
!4423 = !DILocation(line: 2125, column: 11, scope: !435)
!4424 = !DILocation(line: 2126, column: 2, scope: !435)
!4425 = !DILocation(line: 2126, column: 5, scope: !435)
!4426 = !DILocation(line: 2126, column: 11, scope: !435)
!4427 = !DILocation(line: 2127, column: 2, scope: !435)
!4428 = !DILocation(line: 2127, column: 5, scope: !435)
!4429 = !DILocation(line: 2127, column: 16, scope: !435)
!4430 = !DILocation(line: 2128, column: 2, scope: !435)
!4431 = !DILocation(line: 2128, column: 5, scope: !435)
!4432 = !DILocation(line: 2128, column: 16, scope: !435)
!4433 = !DILocation(line: 2129, column: 2, scope: !435)
!4434 = !DILocation(line: 2129, column: 5, scope: !435)
!4435 = !DILocation(line: 2129, column: 20, scope: !435)
!4436 = !DILocation(line: 2130, column: 2, scope: !435)
!4437 = !DILocation(line: 2130, column: 5, scope: !435)
!4438 = !DILocation(line: 2130, column: 11, scope: !435)
!4439 = !DILocation(line: 2131, column: 2, scope: !435)
!4440 = !DILocation(line: 2131, column: 5, scope: !435)
!4441 = !DILocation(line: 2131, column: 13, scope: !435)
!4442 = !DILocation(line: 2132, column: 2, scope: !435)
!4443 = !DILocation(line: 2132, column: 5, scope: !435)
!4444 = !DILocation(line: 2132, column: 13, scope: !435)
!4445 = !DILocation(line: 2133, column: 2, scope: !435)
!4446 = !DILocation(line: 2133, column: 5, scope: !435)
!4447 = !DILocation(line: 2133, column: 7, scope: !435)
!4448 = !DILocation(line: 2134, column: 20, scope: !435)
!4449 = !DILocation(line: 2134, column: 23, scope: !435)
!4450 = !DILocation(line: 2134, column: 2, scope: !435)
!4451 = !DILocation(line: 2134, column: 5, scope: !435)
!4452 = !DILocation(line: 2134, column: 18, scope: !435)
!4453 = !DILocation(line: 2135, column: 2, scope: !435)
!4454 = !DILocation(line: 2136, column: 2, scope: !435)
!4455 = !DILocation(line: 2136, column: 5, scope: !435)
!4456 = !DILocation(line: 2136, column: 14, scope: !435)
!4457 = !DILocation(line: 2137, column: 2, scope: !435)
!4458 = !DILocation(line: 2137, column: 5, scope: !435)
!4459 = !DILocation(line: 2137, column: 15, scope: !435)
!4460 = !DILocation(line: 2138, column: 2, scope: !435)
!4461 = !DILocation(line: 2138, column: 5, scope: !435)
!4462 = !DILocation(line: 2138, column: 27, scope: !435)
!4463 = !DILocation(line: 2139, column: 2, scope: !435)
!4464 = !DILocation(line: 2139, column: 5, scope: !435)
!4465 = !DILocation(line: 2139, column: 27, scope: !435)
!4466 = !DILocation(line: 2142, column: 12, scope: !435)
!4467 = !DILocation(line: 2142, column: 15, scope: !435)
!4468 = !DILocation(line: 2142, column: 2, scope: !435)
!4469 = !DILocation(line: 2143, column: 2, scope: !435)
!4470 = !DILocation(line: 2143, column: 5, scope: !435)
!4471 = !DILocation(line: 2143, column: 12, scope: !435)
!4472 = !DILocation(line: 2143, column: 18, scope: !435)
!4473 = !DILocation(line: 2144, column: 20, scope: !435)
!4474 = !DILocation(line: 2144, column: 23, scope: !435)
!4475 = !DILocation(line: 2144, column: 33, scope: !435)
!4476 = !DILocation(line: 2144, column: 2, scope: !435)
!4477 = !DILocation(line: 2144, column: 5, scope: !435)
!4478 = !DILocation(line: 2144, column: 18, scope: !435)
!4479 = !DILocation(line: 2145, column: 22, scope: !435)
!4480 = !DILocation(line: 2145, column: 2, scope: !435)
!4481 = !DILocation(line: 2145, column: 5, scope: !435)
!4482 = !DILocation(line: 2145, column: 20, scope: !435)
!4483 = !DILocation(line: 2146, column: 32, scope: !435)
!4484 = !DILocation(line: 2146, column: 35, scope: !435)
!4485 = !DILocation(line: 2146, column: 2, scope: !435)
!4486 = !DILocation(line: 2147, column: 31, scope: !435)
!4487 = !DILocation(line: 2147, column: 34, scope: !435)
!4488 = !DILocation(line: 2147, column: 22, scope: !435)
!4489 = !DILocation(line: 2147, column: 2, scope: !435)
!4490 = !DILocation(line: 2147, column: 5, scope: !435)
!4491 = !DILocation(line: 2147, column: 20, scope: !435)
!4492 = !DILocation(line: 2148, column: 10, scope: !435)
!4493 = !DILocation(line: 2148, column: 2, scope: !435)
!4494 = !DILocalVariable(name: "path", arg: 1, scope: !438, file: !1, line: 2110, type: !119)
!4495 = !DILocation(line: 2110, column: 23, scope: !438)
!4496 = !DILocalVariable(name: "symlink_mode", arg: 2, scope: !438, file: !1, line: 2110, type: !62)
!4497 = !DILocation(line: 2110, column: 33, scope: !438)
!4498 = !DILocalVariable(name: "restore_time", arg: 3, scope: !438, file: !1, line: 2110, type: !62)
!4499 = !DILocation(line: 2110, column: 51, scope: !438)
!4500 = !DILocalVariable(name: "t", scope: !438, file: !1, line: 2112, type: !153)
!4501 = !DILocation(line: 2112, column: 15, scope: !438)
!4502 = !DILocation(line: 2114, column: 11, scope: !4503)
!4503 = distinct !DILexicalBlock(scope: !438, file: !1, line: 2114, column: 6)
!4504 = !DILocation(line: 2114, column: 9, scope: !4503)
!4505 = !DILocation(line: 2114, column: 34, scope: !4503)
!4506 = !DILocation(line: 2114, column: 6, scope: !438)
!4507 = !DILocation(line: 2115, column: 3, scope: !4503)
!4508 = !DILocation(line: 2116, column: 2, scope: !438)
!4509 = !DILocation(line: 2116, column: 2, scope: !4510)
!4510 = !DILexicalBlockFile(scope: !4511, file: !1, discriminator: 1)
!4511 = distinct !DILexicalBlock(scope: !438, file: !1, line: 2116, column: 2)
!4512 = !DILocation(line: 2117, column: 25, scope: !438)
!4513 = !DILocation(line: 2117, column: 28, scope: !438)
!4514 = !DILocation(line: 2117, column: 2, scope: !438)
!4515 = !DILocation(line: 2118, column: 28, scope: !438)
!4516 = !DILocation(line: 2118, column: 2, scope: !438)
!4517 = !DILocation(line: 2118, column: 5, scope: !438)
!4518 = !DILocation(line: 2118, column: 26, scope: !438)
!4519 = !DILocation(line: 2119, column: 22, scope: !438)
!4520 = !DILocation(line: 2119, column: 25, scope: !438)
!4521 = !DILocation(line: 2119, column: 31, scope: !438)
!4522 = !DILocation(line: 2119, column: 10, scope: !438)
!4523 = !DILocation(line: 2119, column: 2, scope: !438)
!4524 = !DILocation(line: 2120, column: 1, scope: !438)
