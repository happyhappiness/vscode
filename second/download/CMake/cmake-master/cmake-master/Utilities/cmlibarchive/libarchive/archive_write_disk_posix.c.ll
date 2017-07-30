; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_disk_posix.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive_vtable = type { i32 (%struct.archive*)*, i32 (%struct.archive*)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i32)*, {}*, i8* (%struct.archive*, i32)* }
%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque
%struct.archive_entry = type opaque
%struct.archive_write_disk = type { %struct.archive, i32, %struct.fixup_entry*, %struct.fixup_entry*, i64, i32, i64, i64, i64, i64 (i8*, i8*, i64)*, void (i8*)*, i8*, i64 (i8*, i8*, i64)*, void (i8*)*, i8*, %struct.archive_string, %struct.stat, %struct.stat*, %struct.archive_entry*, i8*, %struct.archive_string, i32, i32, i32, i32, i64, i64, i64, i64, i32, i32, i64, i64, i32, i8*, i32, i8*, i64, i32, i32*, i8*, i64, i64, i32, i32, i8*, i64, i64, %struct.z_stream_s, i32, i32 }
%struct.fixup_entry = type { %struct.fixup_entry*, %struct.archive_acl, i32, i64, i64, i64, i64, i64, i64, i64, i64, i64, i64, i8*, i32, i8* }
%struct.archive_acl = type { i32, %struct.archive_acl_entry*, %struct.archive_acl_entry*, i32, i32*, i8*, i32 }
%struct.archive_acl_entry = type { %struct.archive_acl_entry*, i32, i32, i32, i32, %struct.archive_mstring }
%struct.archive_mstring = type { %struct.archive_string, %struct.archive_string, %struct.archive_wstring, %struct.archive_string, i32 }
%struct.archive_wstring = type { i32*, i64, i64 }
%struct.stat = type { i64, i64, i64, i32, i32, i32, i32, i64, i64, i64, i64, %struct.timespec, %struct.timespec, %struct.timespec, [3 x i64] }
%struct.timespec = type { i64, i64 }
%struct.z_stream_s = type { i8*, i32, i64, i8*, i32, i64, i8*, %struct.internal_state*, i8* (i8*, i32, i32)*, void (i8*, i8*)*, i8*, i32, i64, i64 }
%struct.internal_state = type { i32 }

@.str = private unnamed_addr constant [33 x i8] c"archive_write_disk_set_skip_file\00", align 1
@.str.1 = private unnamed_addr constant [36 x i8] c"archive_write_disk_set_group_lookup\00", align 1
@.str.2 = private unnamed_addr constant [35 x i8] c"archive_write_disk_set_user_lookup\00", align 1
@.str.3 = private unnamed_addr constant [23 x i8] c"archive_write_disk_gid\00", align 1
@.str.4 = private unnamed_addr constant [23 x i8] c"archive_write_disk_uid\00", align 1
@archive_write_disk_vtable.av = internal global %struct.archive_vtable zeroinitializer, align 8
@archive_write_disk_vtable.inited = internal global i32 0, align 4
@.str.5 = private unnamed_addr constant [25 x i8] c"archive_write_disk_close\00", align 1
@.str.6 = private unnamed_addr constant [19 x i8] c"Can't restore time\00", align 1
@.str.7 = private unnamed_addr constant [25 x i8] c"Failed to set file flags\00", align 1
@.str.8 = private unnamed_addr constant [24 x i8] c"archive_write_disk_free\00", align 1
@.str.9 = private unnamed_addr constant [26 x i8] c"archive_write_disk_header\00", align 1
@.str.10 = private unnamed_addr constant [16 x i8] c"chdir() failure\00", align 1
@.str.11 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@.str.12 = private unnamed_addr constant [15 x i8] c"Invalid empty \00", align 1
@.str.13 = private unnamed_addr constant [9 x i8] c"pathname\00", align 1
@.str.14 = private unnamed_addr constant [9 x i8] c"Path is \00", align 1
@.str.15 = private unnamed_addr constant [9 x i8] c"absolute\00", align 1
@.str.16 = private unnamed_addr constant [15 x i8] c"Path contains \00", align 1
@.str.17 = private unnamed_addr constant [5 x i8] c"'..'\00", align 1
@.str.18 = private unnamed_addr constant [2 x i8] c".\00", align 1
@.str.19 = private unnamed_addr constant [18 x i8] c"Could not stat %s\00", align 1
@.str.20 = private unnamed_addr constant [19 x i8] c"Could not chdir %s\00", align 1
@.str.21 = private unnamed_addr constant [28 x i8] c"Could not remove symlink %s\00", align 1
@.str.22 = private unnamed_addr constant [37 x i8] c"Cannot remove intervening symlink %s\00", align 1
@.str.23 = private unnamed_addr constant [34 x i8] c"Cannot extract through symlink %s\00", align 1
@.str.24 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.25 = private unnamed_addr constant [28 x i8] c"Can't create directory '%s'\00", align 1
@.str.26 = private unnamed_addr constant [64 x i8] c"Can't create directory '%s': Conflicting file cannot be removed\00", align 1
@.str.27 = private unnamed_addr constant [26 x i8] c"Can't test directory '%s'\00", align 1
@.str.28 = private unnamed_addr constant [26 x i8] c"Failed to create dir '%s'\00", align 1
@.str.29 = private unnamed_addr constant [34 x i8] c"Can't allocate memory for a fixup\00", align 1
@.str.30 = private unnamed_addr constant [17 x i8] c"Could not unlink\00", align 1
@.str.31 = private unnamed_addr constant [38 x i8] c"Hard-link target '%s' does not exist.\00", align 1
@.str.32 = private unnamed_addr constant [34 x i8] c"Can't remove already-existing dir\00", align 1
@.str.33 = private unnamed_addr constant [27 x i8] c"Can't stat existing object\00", align 1
@.str.34 = private unnamed_addr constant [30 x i8] c"Refusing to overwrite archive\00", align 1
@.str.35 = private unnamed_addr constant [37 x i8] c"Can't unlink already-existing object\00", align 1
@.str.36 = private unnamed_addr constant [52 x i8] c"Can't replace existing directory with non-directory\00", align 1
@.str.37 = private unnamed_addr constant [18 x i8] c"Can't create '%s'\00", align 1
@.str.38 = private unnamed_addr constant [27 x i8] c"archive_write_finish_entry\00", align 1
@.str.39 = private unnamed_addr constant [32 x i8] c"File size could not be restored\00", align 1
@.str.40 = private unnamed_addr constant [12 x i8] c"Seek failed\00", align 1
@.str.41 = private unnamed_addr constant [29 x i8] c"Write to restore size failed\00", align 1
@.str.42 = private unnamed_addr constant [19 x i8] c"Couldn't stat file\00", align 1
@.str.43 = private unnamed_addr constant [18 x i8] c"Can't set UID=%jd\00", align 1
@.str.44 = private unnamed_addr constant [36 x i8] c"Can't set user=%jd/group=%jd for %s\00", align 1
@.str.45 = private unnamed_addr constant [23 x i8] c"Can't restore SGID bit\00", align 1
@.str.46 = private unnamed_addr constant [23 x i8] c"Can't restore SUID bit\00", align 1
@.str.47 = private unnamed_addr constant [21 x i8] c"Can't make file SUID\00", align 1
@.str.48 = private unnamed_addr constant [29 x i8] c"Can't set permissions to 0%o\00", align 1
@set_xattrs.warning_done = internal global i32 0, align 4
@.str.49 = private unnamed_addr constant [50 x i8] c"Cannot restore extended attributes on this system\00", align 1
@.str.50 = private unnamed_addr constant [19 x i8] c"archive_write_data\00", align 1
@.str.51 = private unnamed_addr constant [34 x i8] c"Attempt to write to an empty file\00", align 1
@.str.52 = private unnamed_addr constant [13 x i8] c"Write failed\00", align 1
@.str.53 = private unnamed_addr constant [25 x i8] c"archive_write_data_block\00", align 1
@.str.54 = private unnamed_addr constant [44 x i8] c"Too much data: Truncating file at %ju bytes\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_write_disk_set_options(%struct.archive* %_a, i32 %flags) #0 !dbg !305 {
entry:
  %_a.addr = alloca %struct.archive*, align 8
  %flags.addr = alloca i32, align 4
  %a = alloca %struct.archive_write_disk*, align 8
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !398, metadata !399), !dbg !400
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !401, metadata !399), !dbg !402
  call void @llvm.dbg.declare(metadata %struct.archive_write_disk** %a, metadata !403, metadata !399), !dbg !404
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !405
  %1 = bitcast %struct.archive* %0 to %struct.archive_write_disk*, !dbg !406
  store %struct.archive_write_disk* %1, %struct.archive_write_disk** %a, align 8, !dbg !404
  %2 = load i32, i32* %flags.addr, align 4, !dbg !407
  %3 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !408
  %flags1 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %3, i32 0, i32 23, !dbg !409
  store i32 %2, i32* %flags1, align 8, !dbg !410
  ret i32 0, !dbg !411
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define i32 @archive_write_disk_set_skip_file(%struct.archive* %_a, i64 %d, i64 %i) #0 !dbg !306 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %d.addr = alloca i64, align 8
  %i.addr = alloca i64, align 8
  %a = alloca %struct.archive_write_disk*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !412, metadata !399), !dbg !413
  store i64 %d, i64* %d.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %d.addr, metadata !414, metadata !399), !dbg !415
  store i64 %i, i64* %i.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %i.addr, metadata !416, metadata !399), !dbg !417
  call void @llvm.dbg.declare(metadata %struct.archive_write_disk** %a, metadata !418, metadata !399), !dbg !419
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !420
  %1 = bitcast %struct.archive* %0 to %struct.archive_write_disk*, !dbg !421
  store %struct.archive_write_disk* %1, %struct.archive_write_disk** %a, align 8, !dbg !419
  br label %do.body, !dbg !422

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !423, metadata !399), !dbg !425
  %2 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !426
  %archive = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %2, i32 0, i32 0, !dbg !426
  %call = call i32 @__archive_check_magic(%struct.archive* %archive, i32 -1073631035, i32 32767, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str, i32 0, i32 0)), !dbg !426
  store i32 %call, i32* %magic_test, align 4, !dbg !426
  %3 = load i32, i32* %magic_test, align 4, !dbg !426
  %cmp = icmp eq i32 %3, -30, !dbg !426
  br i1 %cmp, label %if.then, label %if.end, !dbg !426

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !428
  br label %return, !dbg !428

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !431

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !433
  %skip_file_set = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %4, i32 0, i32 5, !dbg !434
  store i32 1, i32* %skip_file_set, align 8, !dbg !435
  %5 = load i64, i64* %d.addr, align 8, !dbg !436
  %6 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !437
  %skip_file_dev = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %6, i32 0, i32 6, !dbg !438
  store i64 %5, i64* %skip_file_dev, align 8, !dbg !439
  %7 = load i64, i64* %i.addr, align 8, !dbg !440
  %8 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !441
  %skip_file_ino = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %8, i32 0, i32 7, !dbg !442
  store i64 %7, i64* %skip_file_ino, align 8, !dbg !443
  store i32 0, i32* %retval, align 4, !dbg !444
  br label %return, !dbg !444

return:                                           ; preds = %do.end, %if.then
  %9 = load i32, i32* %retval, align 4, !dbg !445
  ret i32 %9, !dbg !445
}

declare i32 @__archive_check_magic(%struct.archive*, i32, i32, i8*) #2

; Function Attrs: nounwind uwtable
define i32 @archive_write_disk_set_group_lookup(%struct.archive* %_a, i8* %private_data, i64 (i8*, i8*, i64)* %lookup_gid, void (i8*)* %cleanup_gid) #0 !dbg !309 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %private_data.addr = alloca i8*, align 8
  %lookup_gid.addr = alloca i64 (i8*, i8*, i64)*, align 8
  %cleanup_gid.addr = alloca void (i8*)*, align 8
  %a = alloca %struct.archive_write_disk*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !446, metadata !399), !dbg !447
  store i8* %private_data, i8** %private_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %private_data.addr, metadata !448, metadata !399), !dbg !449
  store i64 (i8*, i8*, i64)* %lookup_gid, i64 (i8*, i8*, i64)** %lookup_gid.addr, align 8
  call void @llvm.dbg.declare(metadata i64 (i8*, i8*, i64)** %lookup_gid.addr, metadata !450, metadata !399), !dbg !451
  store void (i8*)* %cleanup_gid, void (i8*)** %cleanup_gid.addr, align 8
  call void @llvm.dbg.declare(metadata void (i8*)** %cleanup_gid.addr, metadata !452, metadata !399), !dbg !453
  call void @llvm.dbg.declare(metadata %struct.archive_write_disk** %a, metadata !454, metadata !399), !dbg !455
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !456
  %1 = bitcast %struct.archive* %0 to %struct.archive_write_disk*, !dbg !457
  store %struct.archive_write_disk* %1, %struct.archive_write_disk** %a, align 8, !dbg !455
  br label %do.body, !dbg !458

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !459, metadata !399), !dbg !461
  %2 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !462
  %archive = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %2, i32 0, i32 0, !dbg !462
  %call = call i32 @__archive_check_magic(%struct.archive* %archive, i32 -1073631035, i32 32767, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.1, i32 0, i32 0)), !dbg !462
  store i32 %call, i32* %magic_test, align 4, !dbg !462
  %3 = load i32, i32* %magic_test, align 4, !dbg !462
  %cmp = icmp eq i32 %3, -30, !dbg !462
  br i1 %cmp, label %if.then, label %if.end, !dbg !462

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !464
  br label %return, !dbg !464

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !467

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !469
  %cleanup_gid1 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %4, i32 0, i32 10, !dbg !471
  %5 = load void (i8*)*, void (i8*)** %cleanup_gid1, align 8, !dbg !471
  %cmp2 = icmp ne void (i8*)* %5, null, !dbg !472
  br i1 %cmp2, label %land.lhs.true, label %if.end7, !dbg !473

land.lhs.true:                                    ; preds = %do.end
  %6 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !474
  %lookup_gid_data = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %6, i32 0, i32 11, !dbg !476
  %7 = load i8*, i8** %lookup_gid_data, align 8, !dbg !476
  %cmp3 = icmp ne i8* %7, null, !dbg !477
  br i1 %cmp3, label %if.then4, label %if.end7, !dbg !478

if.then4:                                         ; preds = %land.lhs.true
  %8 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !479
  %cleanup_gid5 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %8, i32 0, i32 10, !dbg !480
  %9 = load void (i8*)*, void (i8*)** %cleanup_gid5, align 8, !dbg !480
  %10 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !481
  %lookup_gid_data6 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %10, i32 0, i32 11, !dbg !482
  %11 = load i8*, i8** %lookup_gid_data6, align 8, !dbg !482
  call void %9(i8* %11), !dbg !483
  br label %if.end7, !dbg !483

if.end7:                                          ; preds = %if.then4, %land.lhs.true, %do.end
  %12 = load i64 (i8*, i8*, i64)*, i64 (i8*, i8*, i64)** %lookup_gid.addr, align 8, !dbg !484
  %13 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !485
  %lookup_gid8 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %13, i32 0, i32 9, !dbg !486
  store i64 (i8*, i8*, i64)* %12, i64 (i8*, i8*, i64)** %lookup_gid8, align 8, !dbg !487
  %14 = load void (i8*)*, void (i8*)** %cleanup_gid.addr, align 8, !dbg !488
  %15 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !489
  %cleanup_gid9 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %15, i32 0, i32 10, !dbg !490
  store void (i8*)* %14, void (i8*)** %cleanup_gid9, align 8, !dbg !491
  %16 = load i8*, i8** %private_data.addr, align 8, !dbg !492
  %17 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !493
  %lookup_gid_data10 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %17, i32 0, i32 11, !dbg !494
  store i8* %16, i8** %lookup_gid_data10, align 8, !dbg !495
  store i32 0, i32* %retval, align 4, !dbg !496
  br label %return, !dbg !496

return:                                           ; preds = %if.end7, %if.then
  %18 = load i32, i32* %retval, align 4, !dbg !497
  ret i32 %18, !dbg !497
}

; Function Attrs: nounwind uwtable
define i32 @archive_write_disk_set_user_lookup(%struct.archive* %_a, i8* %private_data, i64 (i8*, i8*, i64)* %lookup_uid, void (i8*)* %cleanup_uid) #0 !dbg !312 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %private_data.addr = alloca i8*, align 8
  %lookup_uid.addr = alloca i64 (i8*, i8*, i64)*, align 8
  %cleanup_uid.addr = alloca void (i8*)*, align 8
  %a = alloca %struct.archive_write_disk*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !498, metadata !399), !dbg !499
  store i8* %private_data, i8** %private_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %private_data.addr, metadata !500, metadata !399), !dbg !501
  store i64 (i8*, i8*, i64)* %lookup_uid, i64 (i8*, i8*, i64)** %lookup_uid.addr, align 8
  call void @llvm.dbg.declare(metadata i64 (i8*, i8*, i64)** %lookup_uid.addr, metadata !502, metadata !399), !dbg !503
  store void (i8*)* %cleanup_uid, void (i8*)** %cleanup_uid.addr, align 8
  call void @llvm.dbg.declare(metadata void (i8*)** %cleanup_uid.addr, metadata !504, metadata !399), !dbg !505
  call void @llvm.dbg.declare(metadata %struct.archive_write_disk** %a, metadata !506, metadata !399), !dbg !507
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !508
  %1 = bitcast %struct.archive* %0 to %struct.archive_write_disk*, !dbg !509
  store %struct.archive_write_disk* %1, %struct.archive_write_disk** %a, align 8, !dbg !507
  br label %do.body, !dbg !510

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !511, metadata !399), !dbg !513
  %2 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !514
  %archive = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %2, i32 0, i32 0, !dbg !514
  %call = call i32 @__archive_check_magic(%struct.archive* %archive, i32 -1073631035, i32 32767, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.2, i32 0, i32 0)), !dbg !514
  store i32 %call, i32* %magic_test, align 4, !dbg !514
  %3 = load i32, i32* %magic_test, align 4, !dbg !514
  %cmp = icmp eq i32 %3, -30, !dbg !514
  br i1 %cmp, label %if.then, label %if.end, !dbg !514

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !516
  br label %return, !dbg !516

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !519

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !521
  %cleanup_uid1 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %4, i32 0, i32 13, !dbg !523
  %5 = load void (i8*)*, void (i8*)** %cleanup_uid1, align 8, !dbg !523
  %cmp2 = icmp ne void (i8*)* %5, null, !dbg !524
  br i1 %cmp2, label %land.lhs.true, label %if.end7, !dbg !525

land.lhs.true:                                    ; preds = %do.end
  %6 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !526
  %lookup_uid_data = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %6, i32 0, i32 14, !dbg !528
  %7 = load i8*, i8** %lookup_uid_data, align 8, !dbg !528
  %cmp3 = icmp ne i8* %7, null, !dbg !529
  br i1 %cmp3, label %if.then4, label %if.end7, !dbg !530

if.then4:                                         ; preds = %land.lhs.true
  %8 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !531
  %cleanup_uid5 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %8, i32 0, i32 13, !dbg !532
  %9 = load void (i8*)*, void (i8*)** %cleanup_uid5, align 8, !dbg !532
  %10 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !533
  %lookup_uid_data6 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %10, i32 0, i32 14, !dbg !534
  %11 = load i8*, i8** %lookup_uid_data6, align 8, !dbg !534
  call void %9(i8* %11), !dbg !535
  br label %if.end7, !dbg !535

if.end7:                                          ; preds = %if.then4, %land.lhs.true, %do.end
  %12 = load i64 (i8*, i8*, i64)*, i64 (i8*, i8*, i64)** %lookup_uid.addr, align 8, !dbg !536
  %13 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !537
  %lookup_uid8 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %13, i32 0, i32 12, !dbg !538
  store i64 (i8*, i8*, i64)* %12, i64 (i8*, i8*, i64)** %lookup_uid8, align 8, !dbg !539
  %14 = load void (i8*)*, void (i8*)** %cleanup_uid.addr, align 8, !dbg !540
  %15 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !541
  %cleanup_uid9 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %15, i32 0, i32 13, !dbg !542
  store void (i8*)* %14, void (i8*)** %cleanup_uid9, align 8, !dbg !543
  %16 = load i8*, i8** %private_data.addr, align 8, !dbg !544
  %17 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !545
  %lookup_uid_data10 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %17, i32 0, i32 14, !dbg !546
  store i8* %16, i8** %lookup_uid_data10, align 8, !dbg !547
  store i32 0, i32* %retval, align 4, !dbg !548
  br label %return, !dbg !548

return:                                           ; preds = %if.end7, %if.then
  %18 = load i32, i32* %retval, align 4, !dbg !549
  ret i32 %18, !dbg !549
}

; Function Attrs: nounwind uwtable
define i64 @archive_write_disk_gid(%struct.archive* %_a, i8* %name, i64 %id) #0 !dbg !313 {
entry:
  %retval = alloca i64, align 8
  %_a.addr = alloca %struct.archive*, align 8
  %name.addr = alloca i8*, align 8
  %id.addr = alloca i64, align 8
  %a = alloca %struct.archive_write_disk*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !550, metadata !399), !dbg !551
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !552, metadata !399), !dbg !553
  store i64 %id, i64* %id.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %id.addr, metadata !554, metadata !399), !dbg !555
  call void @llvm.dbg.declare(metadata %struct.archive_write_disk** %a, metadata !556, metadata !399), !dbg !557
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !558
  %1 = bitcast %struct.archive* %0 to %struct.archive_write_disk*, !dbg !559
  store %struct.archive_write_disk* %1, %struct.archive_write_disk** %a, align 8, !dbg !557
  br label %do.body, !dbg !560

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !561, metadata !399), !dbg !563
  %2 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !564
  %archive = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %2, i32 0, i32 0, !dbg !564
  %call = call i32 @__archive_check_magic(%struct.archive* %archive, i32 -1073631035, i32 32767, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.3, i32 0, i32 0)), !dbg !564
  store i32 %call, i32* %magic_test, align 4, !dbg !564
  %3 = load i32, i32* %magic_test, align 4, !dbg !564
  %cmp = icmp eq i32 %3, -30, !dbg !564
  br i1 %cmp, label %if.then, label %if.end, !dbg !564

if.then:                                          ; preds = %do.body
  store i64 -30, i64* %retval, align 8, !dbg !566
  br label %return, !dbg !566

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !569

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !571
  %lookup_gid = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %4, i32 0, i32 9, !dbg !573
  %5 = load i64 (i8*, i8*, i64)*, i64 (i8*, i8*, i64)** %lookup_gid, align 8, !dbg !573
  %tobool = icmp ne i64 (i8*, i8*, i64)* %5, null, !dbg !571
  br i1 %tobool, label %if.then1, label %if.end4, !dbg !574

if.then1:                                         ; preds = %do.end
  %6 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !575
  %lookup_gid2 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %6, i32 0, i32 9, !dbg !576
  %7 = load i64 (i8*, i8*, i64)*, i64 (i8*, i8*, i64)** %lookup_gid2, align 8, !dbg !576
  %8 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !577
  %lookup_gid_data = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %8, i32 0, i32 11, !dbg !578
  %9 = load i8*, i8** %lookup_gid_data, align 8, !dbg !578
  %10 = load i8*, i8** %name.addr, align 8, !dbg !579
  %11 = load i64, i64* %id.addr, align 8, !dbg !580
  %call3 = call i64 %7(i8* %9, i8* %10, i64 %11), !dbg !581
  store i64 %call3, i64* %retval, align 8, !dbg !582
  br label %return, !dbg !582

if.end4:                                          ; preds = %do.end
  %12 = load i64, i64* %id.addr, align 8, !dbg !583
  store i64 %12, i64* %retval, align 8, !dbg !584
  br label %return, !dbg !584

return:                                           ; preds = %if.end4, %if.then1, %if.then
  %13 = load i64, i64* %retval, align 8, !dbg !585
  ret i64 %13, !dbg !585
}

; Function Attrs: nounwind uwtable
define i64 @archive_write_disk_uid(%struct.archive* %_a, i8* %name, i64 %id) #0 !dbg !317 {
entry:
  %retval = alloca i64, align 8
  %_a.addr = alloca %struct.archive*, align 8
  %name.addr = alloca i8*, align 8
  %id.addr = alloca i64, align 8
  %a = alloca %struct.archive_write_disk*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !586, metadata !399), !dbg !587
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !588, metadata !399), !dbg !589
  store i64 %id, i64* %id.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %id.addr, metadata !590, metadata !399), !dbg !591
  call void @llvm.dbg.declare(metadata %struct.archive_write_disk** %a, metadata !592, metadata !399), !dbg !593
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !594
  %1 = bitcast %struct.archive* %0 to %struct.archive_write_disk*, !dbg !595
  store %struct.archive_write_disk* %1, %struct.archive_write_disk** %a, align 8, !dbg !593
  br label %do.body, !dbg !596

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !597, metadata !399), !dbg !599
  %2 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !600
  %archive = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %2, i32 0, i32 0, !dbg !600
  %call = call i32 @__archive_check_magic(%struct.archive* %archive, i32 -1073631035, i32 32767, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.4, i32 0, i32 0)), !dbg !600
  store i32 %call, i32* %magic_test, align 4, !dbg !600
  %3 = load i32, i32* %magic_test, align 4, !dbg !600
  %cmp = icmp eq i32 %3, -30, !dbg !600
  br i1 %cmp, label %if.then, label %if.end, !dbg !600

if.then:                                          ; preds = %do.body
  store i64 -30, i64* %retval, align 8, !dbg !602
  br label %return, !dbg !602

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !605

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !607
  %lookup_uid = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %4, i32 0, i32 12, !dbg !609
  %5 = load i64 (i8*, i8*, i64)*, i64 (i8*, i8*, i64)** %lookup_uid, align 8, !dbg !609
  %tobool = icmp ne i64 (i8*, i8*, i64)* %5, null, !dbg !607
  br i1 %tobool, label %if.then1, label %if.end4, !dbg !610

if.then1:                                         ; preds = %do.end
  %6 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !611
  %lookup_uid2 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %6, i32 0, i32 12, !dbg !612
  %7 = load i64 (i8*, i8*, i64)*, i64 (i8*, i8*, i64)** %lookup_uid2, align 8, !dbg !612
  %8 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !613
  %lookup_uid_data = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %8, i32 0, i32 14, !dbg !614
  %9 = load i8*, i8** %lookup_uid_data, align 8, !dbg !614
  %10 = load i8*, i8** %name.addr, align 8, !dbg !615
  %11 = load i64, i64* %id.addr, align 8, !dbg !616
  %call3 = call i64 %7(i8* %9, i8* %10, i64 %11), !dbg !617
  store i64 %call3, i64* %retval, align 8, !dbg !618
  br label %return, !dbg !618

if.end4:                                          ; preds = %do.end
  %12 = load i64, i64* %id.addr, align 8, !dbg !619
  store i64 %12, i64* %retval, align 8, !dbg !620
  br label %return, !dbg !620

return:                                           ; preds = %if.end4, %if.then1, %if.then
  %13 = load i64, i64* %retval, align 8, !dbg !621
  ret i64 %13, !dbg !621
}

; Function Attrs: nounwind uwtable
define %struct.archive* @archive_write_disk_new() #0 !dbg !318 {
entry:
  %retval = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_write_disk*, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_disk** %a, metadata !622, metadata !399), !dbg !623
  %call = call noalias i8* @calloc(i64 1, i64 792) #7, !dbg !624
  %0 = bitcast i8* %call to %struct.archive_write_disk*, !dbg !625
  store %struct.archive_write_disk* %0, %struct.archive_write_disk** %a, align 8, !dbg !626
  %1 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !627
  %cmp = icmp eq %struct.archive_write_disk* %1, null, !dbg !629
  br i1 %cmp, label %if.then, label %if.end, !dbg !630

if.then:                                          ; preds = %entry
  store %struct.archive* null, %struct.archive** %retval, align 8, !dbg !631
  br label %return, !dbg !631

if.end:                                           ; preds = %entry
  %2 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !632
  %archive = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %2, i32 0, i32 0, !dbg !633
  %magic = getelementptr inbounds %struct.archive, %struct.archive* %archive, i32 0, i32 0, !dbg !634
  store i32 -1073631035, i32* %magic, align 8, !dbg !635
  %3 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !636
  %archive1 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %3, i32 0, i32 0, !dbg !637
  %state = getelementptr inbounds %struct.archive, %struct.archive* %archive1, i32 0, i32 1, !dbg !638
  store i32 2, i32* %state, align 4, !dbg !639
  %call2 = call %struct.archive_vtable* @archive_write_disk_vtable(), !dbg !640
  %4 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !641
  %archive3 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %4, i32 0, i32 0, !dbg !642
  %vtable = getelementptr inbounds %struct.archive, %struct.archive* %archive3, i32 0, i32 2, !dbg !643
  store %struct.archive_vtable* %call2, %struct.archive_vtable** %vtable, align 8, !dbg !644
  %call4 = call i64 @time(i64* null) #7, !dbg !645
  %5 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !646
  %start_time = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %5, i32 0, i32 8, !dbg !647
  store i64 %call4, i64* %start_time, align 8, !dbg !648
  %call5 = call i32 @umask(i32 0) #7, !dbg !649
  %6 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !650
  %user_umask = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %6, i32 0, i32 1, !dbg !651
  store i32 %call5, i32* %user_umask, align 8, !dbg !652
  %call6 = call i32 @umask(i32 %call5) #7, !dbg !653
  %call7 = call i32 @geteuid() #7, !dbg !655
  %conv = zext i32 %call7 to i64, !dbg !655
  %7 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !656
  %user_uid = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %7, i32 0, i32 4, !dbg !657
  store i64 %conv, i64* %user_uid, align 8, !dbg !658
  %8 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !659
  %path_safe = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %8, i32 0, i32 15, !dbg !661
  %call8 = call %struct.archive_string* @archive_string_ensure(%struct.archive_string* %path_safe, i64 512), !dbg !662
  %cmp9 = icmp eq %struct.archive_string* %call8, null, !dbg !663
  br i1 %cmp9, label %if.then11, label %if.end12, !dbg !664

if.then11:                                        ; preds = %if.end
  %9 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !665
  %10 = bitcast %struct.archive_write_disk* %9 to i8*, !dbg !665
  call void @free(i8* %10) #7, !dbg !667
  store %struct.archive* null, %struct.archive** %retval, align 8, !dbg !668
  br label %return, !dbg !668

if.end12:                                         ; preds = %if.end
  %11 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !669
  %decmpfs_compression_level = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %11, i32 0, i32 50, !dbg !670
  store i32 5, i32* %decmpfs_compression_level, align 4, !dbg !671
  %12 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !672
  %archive13 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %12, i32 0, i32 0, !dbg !673
  store %struct.archive* %archive13, %struct.archive** %retval, align 8, !dbg !674
  br label %return, !dbg !674

return:                                           ; preds = %if.end12, %if.then11, %if.then
  %13 = load %struct.archive*, %struct.archive** %retval, align 8, !dbg !675
  ret %struct.archive* %13, !dbg !675
}

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #3

; Function Attrs: nounwind uwtable
define internal %struct.archive_vtable* @archive_write_disk_vtable() #0 !dbg !321 {
entry:
  %0 = load i32, i32* @archive_write_disk_vtable.inited, align 4, !dbg !676
  %tobool = icmp ne i32 %0, 0, !dbg !676
  br i1 %tobool, label %if.end, label %if.then, !dbg !678

if.then:                                          ; preds = %entry
  store i32 (%struct.archive*)* @_archive_write_disk_close, i32 (%struct.archive*)** getelementptr inbounds (%struct.archive_vtable, %struct.archive_vtable* @archive_write_disk_vtable.av, i32 0, i32 0), align 8, !dbg !679
  store i64 (%struct.archive*, i32)* @_archive_write_disk_filter_bytes, i64 (%struct.archive*, i32)** getelementptr inbounds (%struct.archive_vtable, %struct.archive_vtable* @archive_write_disk_vtable.av, i32 0, i32 10), align 8, !dbg !681
  store i32 (%struct.archive*)* @_archive_write_disk_free, i32 (%struct.archive*)** getelementptr inbounds (%struct.archive_vtable, %struct.archive_vtable* @archive_write_disk_vtable.av, i32 0, i32 1), align 8, !dbg !682
  store i32 (%struct.archive*, %struct.archive_entry*)* @_archive_write_disk_header, i32 (%struct.archive*, %struct.archive_entry*)** getelementptr inbounds (%struct.archive_vtable, %struct.archive_vtable* @archive_write_disk_vtable.av, i32 0, i32 2), align 8, !dbg !683
  store i32 (%struct.archive*)* @_archive_write_disk_finish_entry, i32 (%struct.archive*)** getelementptr inbounds (%struct.archive_vtable, %struct.archive_vtable* @archive_write_disk_vtable.av, i32 0, i32 3), align 8, !dbg !684
  store i64 (%struct.archive*, i8*, i64)* @_archive_write_disk_data, i64 (%struct.archive*, i8*, i64)** getelementptr inbounds (%struct.archive_vtable, %struct.archive_vtable* @archive_write_disk_vtable.av, i32 0, i32 4), align 8, !dbg !685
  store i64 (%struct.archive*, i8*, i64, i64)* @_archive_write_disk_data_block, i64 (%struct.archive*, i8*, i64, i64)** getelementptr inbounds (%struct.archive_vtable, %struct.archive_vtable* @archive_write_disk_vtable.av, i32 0, i32 5), align 8, !dbg !686
  store i32 1, i32* @archive_write_disk_vtable.inited, align 4, !dbg !687
  br label %if.end, !dbg !688

if.end:                                           ; preds = %if.then, %entry
  ret %struct.archive_vtable* @archive_write_disk_vtable.av, !dbg !689
}

; Function Attrs: nounwind
declare i64 @time(i64*) #3

; Function Attrs: nounwind
declare i32 @umask(i32) #3

; Function Attrs: nounwind
declare i32 @geteuid() #3

declare %struct.archive_string* @archive_string_ensure(%struct.archive_string*, i64) #2

; Function Attrs: nounwind
declare void @free(i8*) #3

; Function Attrs: nounwind uwtable
define internal i32 @_archive_write_disk_close(%struct.archive* %_a) #0 !dbg !324 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_write_disk*, align 8
  %next = alloca %struct.fixup_entry*, align 8
  %p = alloca %struct.fixup_entry*, align 8
  %ret = alloca i32, align 4
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !690, metadata !399), !dbg !691
  call void @llvm.dbg.declare(metadata %struct.archive_write_disk** %a, metadata !692, metadata !399), !dbg !693
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !694
  %1 = bitcast %struct.archive* %0 to %struct.archive_write_disk*, !dbg !695
  store %struct.archive_write_disk* %1, %struct.archive_write_disk** %a, align 8, !dbg !693
  call void @llvm.dbg.declare(metadata %struct.fixup_entry** %next, metadata !696, metadata !399), !dbg !697
  call void @llvm.dbg.declare(metadata %struct.fixup_entry** %p, metadata !698, metadata !399), !dbg !699
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !700, metadata !399), !dbg !701
  br label %do.body, !dbg !702

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !703, metadata !399), !dbg !705
  %2 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !706
  %archive = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %2, i32 0, i32 0, !dbg !706
  %call = call i32 @__archive_check_magic(%struct.archive* %archive, i32 -1073631035, i32 6, i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.5, i32 0, i32 0)), !dbg !706
  store i32 %call, i32* %magic_test, align 4, !dbg !706
  %3 = load i32, i32* %magic_test, align 4, !dbg !706
  %cmp = icmp eq i32 %3, -30, !dbg !706
  br i1 %cmp, label %if.then, label %if.end, !dbg !706

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !708
  br label %return, !dbg !708

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !711

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !713
  %archive1 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %4, i32 0, i32 0, !dbg !714
  %call2 = call i32 @_archive_write_disk_finish_entry(%struct.archive* %archive1), !dbg !715
  store i32 %call2, i32* %ret, align 4, !dbg !716
  %5 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !717
  %fixup_list = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %5, i32 0, i32 2, !dbg !718
  %6 = load %struct.fixup_entry*, %struct.fixup_entry** %fixup_list, align 8, !dbg !718
  %call3 = call %struct.fixup_entry* @sort_dir_list(%struct.fixup_entry* %6), !dbg !719
  store %struct.fixup_entry* %call3, %struct.fixup_entry** %p, align 8, !dbg !720
  br label %while.cond, !dbg !721

while.cond:                                       ; preds = %if.end38, %do.end
  %7 = load %struct.fixup_entry*, %struct.fixup_entry** %p, align 8, !dbg !722
  %cmp4 = icmp ne %struct.fixup_entry* %7, null, !dbg !724
  br i1 %cmp4, label %while.body, label %while.end, !dbg !725

while.body:                                       ; preds = %while.cond
  %8 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !726
  %pst = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %8, i32 0, i32 17, !dbg !728
  store %struct.stat* null, %struct.stat** %pst, align 8, !dbg !729
  %9 = load %struct.fixup_entry*, %struct.fixup_entry** %p, align 8, !dbg !730
  %fixup = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %9, i32 0, i32 14, !dbg !732
  %10 = load i32, i32* %fixup, align 8, !dbg !732
  %and = and i32 %10, 4, !dbg !733
  %tobool = icmp ne i32 %and, 0, !dbg !733
  br i1 %tobool, label %if.then5, label %if.end7, !dbg !734

if.then5:                                         ; preds = %while.body
  %11 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !735
  %12 = load %struct.fixup_entry*, %struct.fixup_entry** %p, align 8, !dbg !737
  %mode = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %12, i32 0, i32 2, !dbg !738
  %13 = load i32, i32* %mode, align 8, !dbg !738
  %14 = load %struct.fixup_entry*, %struct.fixup_entry** %p, align 8, !dbg !739
  %name = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %14, i32 0, i32 15, !dbg !740
  %15 = load i8*, i8** %name, align 8, !dbg !740
  %16 = load %struct.fixup_entry*, %struct.fixup_entry** %p, align 8, !dbg !741
  %atime = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %16, i32 0, i32 3, !dbg !742
  %17 = load i64, i64* %atime, align 8, !dbg !742
  %18 = load %struct.fixup_entry*, %struct.fixup_entry** %p, align 8, !dbg !743
  %atime_nanos = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %18, i32 0, i32 7, !dbg !744
  %19 = load i64, i64* %atime_nanos, align 8, !dbg !744
  %20 = load %struct.fixup_entry*, %struct.fixup_entry** %p, align 8, !dbg !745
  %birthtime = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %20, i32 0, i32 4, !dbg !746
  %21 = load i64, i64* %birthtime, align 8, !dbg !746
  %22 = load %struct.fixup_entry*, %struct.fixup_entry** %p, align 8, !dbg !747
  %birthtime_nanos = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %22, i32 0, i32 8, !dbg !748
  %23 = load i64, i64* %birthtime_nanos, align 8, !dbg !748
  %24 = load %struct.fixup_entry*, %struct.fixup_entry** %p, align 8, !dbg !749
  %mtime = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %24, i32 0, i32 5, !dbg !750
  %25 = load i64, i64* %mtime, align 8, !dbg !750
  %26 = load %struct.fixup_entry*, %struct.fixup_entry** %p, align 8, !dbg !751
  %mtime_nanos = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %26, i32 0, i32 9, !dbg !752
  %27 = load i64, i64* %mtime_nanos, align 8, !dbg !752
  %28 = load %struct.fixup_entry*, %struct.fixup_entry** %p, align 8, !dbg !753
  %ctime = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %28, i32 0, i32 6, !dbg !754
  %29 = load i64, i64* %ctime, align 8, !dbg !754
  %30 = load %struct.fixup_entry*, %struct.fixup_entry** %p, align 8, !dbg !755
  %ctime_nanos = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %30, i32 0, i32 10, !dbg !756
  %31 = load i64, i64* %ctime_nanos, align 8, !dbg !756
  %call6 = call i32 @set_times(%struct.archive_write_disk* %11, i32 -1, i32 %13, i8* %15, i64 %17, i64 %19, i64 %21, i64 %23, i64 %25, i64 %27, i64 %29, i64 %31), !dbg !757
  br label %if.end7, !dbg !758

if.end7:                                          ; preds = %if.then5, %while.body
  %32 = load %struct.fixup_entry*, %struct.fixup_entry** %p, align 8, !dbg !759
  %fixup8 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %32, i32 0, i32 14, !dbg !761
  %33 = load i32, i32* %fixup8, align 8, !dbg !761
  %and9 = and i32 %33, 536870912, !dbg !762
  %tobool10 = icmp ne i32 %and9, 0, !dbg !762
  br i1 %tobool10, label %if.then11, label %if.end15, !dbg !763

if.then11:                                        ; preds = %if.end7
  %34 = load %struct.fixup_entry*, %struct.fixup_entry** %p, align 8, !dbg !764
  %name12 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %34, i32 0, i32 15, !dbg !765
  %35 = load i8*, i8** %name12, align 8, !dbg !765
  %36 = load %struct.fixup_entry*, %struct.fixup_entry** %p, align 8, !dbg !766
  %mode13 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %36, i32 0, i32 2, !dbg !767
  %37 = load i32, i32* %mode13, align 8, !dbg !767
  %call14 = call i32 @chmod(i8* %35, i32 %37) #7, !dbg !768
  br label %if.end15, !dbg !768

if.end15:                                         ; preds = %if.then11, %if.end7
  %38 = load %struct.fixup_entry*, %struct.fixup_entry** %p, align 8, !dbg !769
  %fixup16 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %38, i32 0, i32 14, !dbg !771
  %39 = load i32, i32* %fixup16, align 8, !dbg !771
  %and17 = and i32 %39, 32, !dbg !772
  %tobool18 = icmp ne i32 %and17, 0, !dbg !772
  br i1 %tobool18, label %if.then19, label %if.end23, !dbg !773

if.then19:                                        ; preds = %if.end15
  %40 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !774
  %archive20 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %40, i32 0, i32 0, !dbg !775
  %41 = load %struct.fixup_entry*, %struct.fixup_entry** %p, align 8, !dbg !776
  %name21 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %41, i32 0, i32 15, !dbg !777
  %42 = load i8*, i8** %name21, align 8, !dbg !777
  %43 = load %struct.fixup_entry*, %struct.fixup_entry** %p, align 8, !dbg !778
  %acl = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %43, i32 0, i32 1, !dbg !779
  %call22 = call i32 @archive_write_disk_set_acls(%struct.archive* %archive20, i32 -1, i8* %42, %struct.archive_acl* %acl), !dbg !780
  br label %if.end23, !dbg !780

if.end23:                                         ; preds = %if.then19, %if.end15
  %44 = load %struct.fixup_entry*, %struct.fixup_entry** %p, align 8, !dbg !781
  %fixup24 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %44, i32 0, i32 14, !dbg !783
  %45 = load i32, i32* %fixup24, align 8, !dbg !783
  %and25 = and i32 %45, 64, !dbg !784
  %tobool26 = icmp ne i32 %and25, 0, !dbg !784
  br i1 %tobool26, label %if.then27, label %if.end31, !dbg !785

if.then27:                                        ; preds = %if.end23
  %46 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !786
  %47 = load %struct.fixup_entry*, %struct.fixup_entry** %p, align 8, !dbg !787
  %name28 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %47, i32 0, i32 15, !dbg !788
  %48 = load i8*, i8** %name28, align 8, !dbg !788
  %49 = load %struct.fixup_entry*, %struct.fixup_entry** %p, align 8, !dbg !789
  %mode29 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %49, i32 0, i32 2, !dbg !790
  %50 = load i32, i32* %mode29, align 8, !dbg !790
  %51 = load %struct.fixup_entry*, %struct.fixup_entry** %p, align 8, !dbg !791
  %fflags_set = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %51, i32 0, i32 11, !dbg !792
  %52 = load i64, i64* %fflags_set, align 8, !dbg !792
  %call30 = call i32 @set_fflags_platform(%struct.archive_write_disk* %46, i32 -1, i8* %48, i32 %50, i64 %52, i64 0), !dbg !793
  br label %if.end31, !dbg !793

if.end31:                                         ; preds = %if.then27, %if.end23
  %53 = load %struct.fixup_entry*, %struct.fixup_entry** %p, align 8, !dbg !794
  %fixup32 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %53, i32 0, i32 14, !dbg !796
  %54 = load i32, i32* %fixup32, align 8, !dbg !796
  %and33 = and i32 %54, 8192, !dbg !797
  %tobool34 = icmp ne i32 %and33, 0, !dbg !797
  br i1 %tobool34, label %if.then35, label %if.end38, !dbg !798

if.then35:                                        ; preds = %if.end31
  %55 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !799
  %56 = load %struct.fixup_entry*, %struct.fixup_entry** %p, align 8, !dbg !800
  %name36 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %56, i32 0, i32 15, !dbg !801
  %57 = load i8*, i8** %name36, align 8, !dbg !801
  %58 = load %struct.fixup_entry*, %struct.fixup_entry** %p, align 8, !dbg !802
  %mac_metadata = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %58, i32 0, i32 13, !dbg !803
  %59 = load i8*, i8** %mac_metadata, align 8, !dbg !803
  %60 = load %struct.fixup_entry*, %struct.fixup_entry** %p, align 8, !dbg !804
  %mac_metadata_size = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %60, i32 0, i32 12, !dbg !805
  %61 = load i64, i64* %mac_metadata_size, align 8, !dbg !805
  %call37 = call i32 @set_mac_metadata(%struct.archive_write_disk* %55, i8* %57, i8* %59, i64 %61), !dbg !806
  br label %if.end38, !dbg !806

if.end38:                                         ; preds = %if.then35, %if.end31
  %62 = load %struct.fixup_entry*, %struct.fixup_entry** %p, align 8, !dbg !807
  %next39 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %62, i32 0, i32 0, !dbg !808
  %63 = load %struct.fixup_entry*, %struct.fixup_entry** %next39, align 8, !dbg !808
  store %struct.fixup_entry* %63, %struct.fixup_entry** %next, align 8, !dbg !809
  %64 = load %struct.fixup_entry*, %struct.fixup_entry** %p, align 8, !dbg !810
  %acl40 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %64, i32 0, i32 1, !dbg !811
  call void @archive_acl_clear(%struct.archive_acl* %acl40), !dbg !812
  %65 = load %struct.fixup_entry*, %struct.fixup_entry** %p, align 8, !dbg !813
  %mac_metadata41 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %65, i32 0, i32 13, !dbg !814
  %66 = load i8*, i8** %mac_metadata41, align 8, !dbg !814
  call void @free(i8* %66) #7, !dbg !815
  %67 = load %struct.fixup_entry*, %struct.fixup_entry** %p, align 8, !dbg !816
  %name42 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %67, i32 0, i32 15, !dbg !817
  %68 = load i8*, i8** %name42, align 8, !dbg !817
  call void @free(i8* %68) #7, !dbg !818
  %69 = load %struct.fixup_entry*, %struct.fixup_entry** %p, align 8, !dbg !819
  %70 = bitcast %struct.fixup_entry* %69 to i8*, !dbg !819
  call void @free(i8* %70) #7, !dbg !820
  %71 = load %struct.fixup_entry*, %struct.fixup_entry** %next, align 8, !dbg !821
  store %struct.fixup_entry* %71, %struct.fixup_entry** %p, align 8, !dbg !822
  br label %while.cond, !dbg !823

while.end:                                        ; preds = %while.cond
  %72 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !825
  %fixup_list43 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %72, i32 0, i32 2, !dbg !826
  store %struct.fixup_entry* null, %struct.fixup_entry** %fixup_list43, align 8, !dbg !827
  %73 = load i32, i32* %ret, align 4, !dbg !828
  store i32 %73, i32* %retval, align 4, !dbg !829
  br label %return, !dbg !829

return:                                           ; preds = %while.end, %if.then
  %74 = load i32, i32* %retval, align 4, !dbg !830
  ret i32 %74, !dbg !830
}

; Function Attrs: nounwind uwtable
define internal i64 @_archive_write_disk_filter_bytes(%struct.archive* %_a, i32 %n) #0 !dbg !340 {
entry:
  %retval = alloca i64, align 8
  %_a.addr = alloca %struct.archive*, align 8
  %n.addr = alloca i32, align 4
  %a = alloca %struct.archive_write_disk*, align 8
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !831, metadata !399), !dbg !832
  store i32 %n, i32* %n.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %n.addr, metadata !833, metadata !399), !dbg !834
  call void @llvm.dbg.declare(metadata %struct.archive_write_disk** %a, metadata !835, metadata !399), !dbg !836
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !837
  %1 = bitcast %struct.archive* %0 to %struct.archive_write_disk*, !dbg !838
  store %struct.archive_write_disk* %1, %struct.archive_write_disk** %a, align 8, !dbg !836
  %2 = load i32, i32* %n.addr, align 4, !dbg !839
  %3 = load i32, i32* %n.addr, align 4, !dbg !840
  %cmp = icmp eq i32 %3, -1, !dbg !842
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !843

lor.lhs.false:                                    ; preds = %entry
  %4 = load i32, i32* %n.addr, align 4, !dbg !844
  %cmp1 = icmp eq i32 %4, 0, !dbg !846
  br i1 %cmp1, label %if.then, label %if.end, !dbg !847

if.then:                                          ; preds = %lor.lhs.false, %entry
  %5 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !848
  %total_bytes_written = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %5, i32 0, i32 27, !dbg !849
  %6 = load i64, i64* %total_bytes_written, align 8, !dbg !849
  store i64 %6, i64* %retval, align 8, !dbg !850
  br label %return, !dbg !850

if.end:                                           ; preds = %lor.lhs.false
  store i64 -1, i64* %retval, align 8, !dbg !851
  br label %return, !dbg !851

return:                                           ; preds = %if.end, %if.then
  %7 = load i64, i64* %retval, align 8, !dbg !852
  ret i64 %7, !dbg !852
}

; Function Attrs: nounwind uwtable
define internal i32 @_archive_write_disk_free(%struct.archive* %_a) #0 !dbg !341 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_write_disk*, align 8
  %ret = alloca i32, align 4
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !853, metadata !399), !dbg !854
  call void @llvm.dbg.declare(metadata %struct.archive_write_disk** %a, metadata !855, metadata !399), !dbg !856
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !857, metadata !399), !dbg !858
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !859
  %cmp = icmp eq %struct.archive* %0, null, !dbg !861
  br i1 %cmp, label %if.then, label %if.end, !dbg !862

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !863
  br label %return, !dbg !863

if.end:                                           ; preds = %entry
  br label %do.body, !dbg !864

do.body:                                          ; preds = %if.end
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !865, metadata !399), !dbg !867
  %1 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !868
  %call = call i32 @__archive_check_magic(%struct.archive* %1, i32 -1073631035, i32 65535, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.8, i32 0, i32 0)), !dbg !868
  store i32 %call, i32* %magic_test, align 4, !dbg !868
  %2 = load i32, i32* %magic_test, align 4, !dbg !868
  %cmp1 = icmp eq i32 %2, -30, !dbg !868
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !868

if.then2:                                         ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !870
  br label %return, !dbg !870

if.end3:                                          ; preds = %do.body
  br label %do.end, !dbg !873

do.end:                                           ; preds = %if.end3
  %3 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !875
  %4 = bitcast %struct.archive* %3 to %struct.archive_write_disk*, !dbg !876
  store %struct.archive_write_disk* %4, %struct.archive_write_disk** %a, align 8, !dbg !877
  %5 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !878
  %archive = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %5, i32 0, i32 0, !dbg !879
  %call4 = call i32 @_archive_write_disk_close(%struct.archive* %archive), !dbg !880
  store i32 %call4, i32* %ret, align 4, !dbg !881
  %6 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !882
  %archive5 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %6, i32 0, i32 0, !dbg !883
  %call6 = call i32 @archive_write_disk_set_group_lookup(%struct.archive* %archive5, i8* null, i64 (i8*, i8*, i64)* null, void (i8*)* null), !dbg !884
  %7 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !885
  %archive7 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %7, i32 0, i32 0, !dbg !886
  %call8 = call i32 @archive_write_disk_set_user_lookup(%struct.archive* %archive7, i8* null, i64 (i8*, i8*, i64)* null, void (i8*)* null), !dbg !887
  %8 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !888
  %entry9 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %8, i32 0, i32 18, !dbg !890
  %9 = load %struct.archive_entry*, %struct.archive_entry** %entry9, align 8, !dbg !890
  %tobool = icmp ne %struct.archive_entry* %9, null, !dbg !888
  br i1 %tobool, label %if.then10, label %if.end12, !dbg !891

if.then10:                                        ; preds = %do.end
  %10 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !892
  %entry11 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %10, i32 0, i32 18, !dbg !893
  %11 = load %struct.archive_entry*, %struct.archive_entry** %entry11, align 8, !dbg !893
  call void @archive_entry_free(%struct.archive_entry* %11), !dbg !894
  br label %if.end12, !dbg !894

if.end12:                                         ; preds = %if.then10, %do.end
  %12 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !895
  %_name_data = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %12, i32 0, i32 20, !dbg !896
  call void @archive_string_free(%struct.archive_string* %_name_data), !dbg !897
  %13 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !898
  %archive13 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %13, i32 0, i32 0, !dbg !899
  %error_string = getelementptr inbounds %struct.archive, %struct.archive* %archive13, i32 0, i32 10, !dbg !900
  call void @archive_string_free(%struct.archive_string* %error_string), !dbg !901
  %14 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !902
  %path_safe = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %14, i32 0, i32 15, !dbg !903
  call void @archive_string_free(%struct.archive_string* %path_safe), !dbg !904
  %15 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !905
  %archive14 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %15, i32 0, i32 0, !dbg !906
  %magic = getelementptr inbounds %struct.archive, %struct.archive* %archive14, i32 0, i32 0, !dbg !907
  store i32 0, i32* %magic, align 8, !dbg !908
  %16 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !909
  %archive15 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %16, i32 0, i32 0, !dbg !910
  %call16 = call i32 @__archive_clean(%struct.archive* %archive15), !dbg !911
  %17 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !912
  %decmpfs_header_p = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %17, i32 0, i32 34, !dbg !913
  %18 = load i8*, i8** %decmpfs_header_p, align 8, !dbg !913
  call void @free(i8* %18) #7, !dbg !914
  %19 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !915
  %resource_fork = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %19, i32 0, i32 36, !dbg !916
  %20 = load i8*, i8** %resource_fork, align 8, !dbg !916
  call void @free(i8* %20) #7, !dbg !917
  %21 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !918
  %compressed_buffer = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %21, i32 0, i32 40, !dbg !919
  %22 = load i8*, i8** %compressed_buffer, align 8, !dbg !919
  call void @free(i8* %22) #7, !dbg !920
  %23 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !921
  %uncompressed_buffer = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %23, i32 0, i32 45, !dbg !922
  %24 = load i8*, i8** %uncompressed_buffer, align 8, !dbg !922
  call void @free(i8* %24) #7, !dbg !923
  %25 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !924
  %26 = bitcast %struct.archive_write_disk* %25 to i8*, !dbg !924
  call void @free(i8* %26) #7, !dbg !925
  %27 = load i32, i32* %ret, align 4, !dbg !926
  store i32 %27, i32* %retval, align 4, !dbg !927
  br label %return, !dbg !927

return:                                           ; preds = %if.end12, %if.then2, %if.then
  %28 = load i32, i32* %retval, align 4, !dbg !928
  ret i32 %28, !dbg !928
}

; Function Attrs: nounwind uwtable
define internal i32 @_archive_write_disk_header(%struct.archive* %_a, %struct.archive_entry* %entry1) #0 !dbg !342 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %a = alloca %struct.archive_write_disk*, align 8
  %fe = alloca %struct.fixup_entry*, align 8
  %ret = alloca i32, align 4
  %r = alloca i32, align 4
  %magic_test = alloca i32, align 4
  %metadata = alloca i8*, align 8
  %metadata_size = alloca i64, align 8
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !929, metadata !399), !dbg !930
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !931, metadata !399), !dbg !932
  call void @llvm.dbg.declare(metadata %struct.archive_write_disk** %a, metadata !933, metadata !399), !dbg !934
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !935
  %1 = bitcast %struct.archive* %0 to %struct.archive_write_disk*, !dbg !936
  store %struct.archive_write_disk* %1, %struct.archive_write_disk** %a, align 8, !dbg !934
  call void @llvm.dbg.declare(metadata %struct.fixup_entry** %fe, metadata !937, metadata !399), !dbg !938
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !939, metadata !399), !dbg !940
  call void @llvm.dbg.declare(metadata i32* %r, metadata !941, metadata !399), !dbg !942
  br label %do.body, !dbg !943

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !944, metadata !399), !dbg !946
  %2 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !947
  %archive = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %2, i32 0, i32 0, !dbg !947
  %call = call i32 @__archive_check_magic(%struct.archive* %archive, i32 -1073631035, i32 6, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.9, i32 0, i32 0)), !dbg !947
  store i32 %call, i32* %magic_test, align 4, !dbg !947
  %3 = load i32, i32* %magic_test, align 4, !dbg !947
  %cmp = icmp eq i32 %3, -30, !dbg !947
  br i1 %cmp, label %if.then, label %if.end, !dbg !947

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !949
  br label %return, !dbg !949

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !952

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !954
  %archive2 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %4, i32 0, i32 0, !dbg !955
  call void @archive_clear_error(%struct.archive* %archive2), !dbg !956
  %5 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !957
  %archive3 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %5, i32 0, i32 0, !dbg !959
  %state = getelementptr inbounds %struct.archive, %struct.archive* %archive3, i32 0, i32 1, !dbg !960
  %6 = load i32, i32* %state, align 4, !dbg !960
  %and = and i32 %6, 4, !dbg !961
  %tobool = icmp ne i32 %and, 0, !dbg !961
  br i1 %tobool, label %if.then4, label %if.end10, !dbg !962

if.then4:                                         ; preds = %do.end
  %7 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !963
  %archive5 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %7, i32 0, i32 0, !dbg !965
  %call6 = call i32 @_archive_write_disk_finish_entry(%struct.archive* %archive5), !dbg !966
  store i32 %call6, i32* %r, align 4, !dbg !967
  %8 = load i32, i32* %r, align 4, !dbg !968
  %cmp7 = icmp eq i32 %8, -30, !dbg !970
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !971

if.then8:                                         ; preds = %if.then4
  %9 = load i32, i32* %r, align 4, !dbg !972
  store i32 %9, i32* %retval, align 4, !dbg !973
  br label %return, !dbg !973

if.end9:                                          ; preds = %if.then4
  br label %if.end10, !dbg !974

if.end10:                                         ; preds = %if.end9, %do.end
  %10 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !975
  %pst = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %10, i32 0, i32 17, !dbg !976
  store %struct.stat* null, %struct.stat** %pst, align 8, !dbg !977
  %11 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !978
  %current_fixup = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %11, i32 0, i32 3, !dbg !979
  store %struct.fixup_entry* null, %struct.fixup_entry** %current_fixup, align 8, !dbg !980
  %12 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !981
  %deferred = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %12, i32 0, i32 22, !dbg !982
  store i32 0, i32* %deferred, align 4, !dbg !983
  %13 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !984
  %entry11 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %13, i32 0, i32 18, !dbg !986
  %14 = load %struct.archive_entry*, %struct.archive_entry** %entry11, align 8, !dbg !986
  %tobool12 = icmp ne %struct.archive_entry* %14, null, !dbg !984
  br i1 %tobool12, label %if.then13, label %if.end16, !dbg !987

if.then13:                                        ; preds = %if.end10
  %15 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !988
  %entry14 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %15, i32 0, i32 18, !dbg !990
  %16 = load %struct.archive_entry*, %struct.archive_entry** %entry14, align 8, !dbg !990
  call void @archive_entry_free(%struct.archive_entry* %16), !dbg !991
  %17 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !992
  %entry15 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %17, i32 0, i32 18, !dbg !993
  store %struct.archive_entry* null, %struct.archive_entry** %entry15, align 8, !dbg !994
  br label %if.end16, !dbg !995

if.end16:                                         ; preds = %if.then13, %if.end10
  %18 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !996
  %call17 = call %struct.archive_entry* @archive_entry_clone(%struct.archive_entry* %18), !dbg !997
  %19 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !998
  %entry18 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %19, i32 0, i32 18, !dbg !999
  store %struct.archive_entry* %call17, %struct.archive_entry** %entry18, align 8, !dbg !1000
  %20 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1001
  %fd = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %20, i32 0, i32 24, !dbg !1002
  store i32 -1, i32* %fd, align 4, !dbg !1003
  %21 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1004
  %fd_offset = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %21, i32 0, i32 26, !dbg !1005
  store i64 0, i64* %fd_offset, align 8, !dbg !1006
  %22 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1007
  %offset = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %22, i32 0, i32 25, !dbg !1008
  store i64 0, i64* %offset, align 8, !dbg !1009
  %23 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1010
  %restore_pwd = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %23, i32 0, i32 29, !dbg !1011
  store i32 -1, i32* %restore_pwd, align 8, !dbg !1012
  %24 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1013
  %user_uid = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %24, i32 0, i32 4, !dbg !1014
  %25 = load i64, i64* %user_uid, align 8, !dbg !1014
  %26 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1015
  %uid = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %26, i32 0, i32 31, !dbg !1016
  store i64 %25, i64* %uid, align 8, !dbg !1017
  %27 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1018
  %entry19 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %27, i32 0, i32 18, !dbg !1019
  %28 = load %struct.archive_entry*, %struct.archive_entry** %entry19, align 8, !dbg !1019
  %call20 = call i32 @archive_entry_mode(%struct.archive_entry* %28), !dbg !1020
  %29 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1021
  %mode = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %29, i32 0, i32 30, !dbg !1022
  store i32 %call20, i32* %mode, align 4, !dbg !1023
  %30 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1024
  %entry21 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %30, i32 0, i32 18, !dbg !1026
  %31 = load %struct.archive_entry*, %struct.archive_entry** %entry21, align 8, !dbg !1026
  %call22 = call i32 @archive_entry_size_is_set(%struct.archive_entry* %31), !dbg !1027
  %tobool23 = icmp ne i32 %call22, 0, !dbg !1027
  br i1 %tobool23, label %if.then24, label %if.else, !dbg !1028

if.then24:                                        ; preds = %if.end16
  %32 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1029
  %entry25 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %32, i32 0, i32 18, !dbg !1030
  %33 = load %struct.archive_entry*, %struct.archive_entry** %entry25, align 8, !dbg !1030
  %call26 = call i64 @archive_entry_size(%struct.archive_entry* %33), !dbg !1031
  %34 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1032
  %filesize = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %34, i32 0, i32 28, !dbg !1033
  store i64 %call26, i64* %filesize, align 8, !dbg !1034
  br label %if.end28, !dbg !1032

if.else:                                          ; preds = %if.end16
  %35 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1035
  %filesize27 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %35, i32 0, i32 28, !dbg !1036
  store i64 -1, i64* %filesize27, align 8, !dbg !1037
  br label %if.end28

if.end28:                                         ; preds = %if.else, %if.then24
  %36 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1038
  %_name_data = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %36, i32 0, i32 20, !dbg !1038
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %_name_data, i32 0, i32 1, !dbg !1038
  store i64 0, i64* %length, align 8, !dbg !1038
  %37 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1038
  %_name_data29 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %37, i32 0, i32 20, !dbg !1038
  %38 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1038
  %entry30 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %38, i32 0, i32 18, !dbg !1038
  %39 = load %struct.archive_entry*, %struct.archive_entry** %entry30, align 8, !dbg !1038
  %call31 = call i8* @archive_entry_pathname(%struct.archive_entry* %39), !dbg !1038
  %40 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1038
  %entry32 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %40, i32 0, i32 18, !dbg !1038
  %41 = load %struct.archive_entry*, %struct.archive_entry** %entry32, align 8, !dbg !1038
  %call33 = call i8* @archive_entry_pathname(%struct.archive_entry* %41), !dbg !1039
  %cmp34 = icmp eq i8* %call33, null, !dbg !1038
  br i1 %cmp34, label %cond.true, label %cond.false, !dbg !1038

cond.true:                                        ; preds = %if.end28
  br label %cond.end, !dbg !1041

cond.false:                                       ; preds = %if.end28
  %42 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1043
  %entry35 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %42, i32 0, i32 18, !dbg !1043
  %43 = load %struct.archive_entry*, %struct.archive_entry** %entry35, align 8, !dbg !1043
  %call36 = call i8* @archive_entry_pathname(%struct.archive_entry* %43), !dbg !1043
  %call37 = call i64 @strlen(i8* %call36) #8, !dbg !1045
  br label %cond.end, !dbg !1043

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ 0, %cond.true ], [ %call37, %cond.false ], !dbg !1047
  %call38 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %_name_data29, i8* %call31, i64 %cond), !dbg !1047
  %44 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1049
  %_name_data39 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %44, i32 0, i32 20, !dbg !1050
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %_name_data39, i32 0, i32 0, !dbg !1051
  %45 = load i8*, i8** %s, align 8, !dbg !1051
  %46 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1052
  %name = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %46, i32 0, i32 19, !dbg !1053
  store i8* %45, i8** %name, align 8, !dbg !1054
  %47 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1055
  %archive40 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %47, i32 0, i32 0, !dbg !1056
  call void @archive_clear_error(%struct.archive* %archive40), !dbg !1057
  %48 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1058
  %call41 = call i32 @cleanup_pathname(%struct.archive_write_disk* %48), !dbg !1059
  store i32 %call41, i32* %ret, align 4, !dbg !1060
  %49 = load i32, i32* %ret, align 4, !dbg !1061
  %cmp42 = icmp ne i32 %49, 0, !dbg !1063
  br i1 %cmp42, label %if.then43, label %if.end44, !dbg !1064

if.then43:                                        ; preds = %cond.end
  %50 = load i32, i32* %ret, align 4, !dbg !1065
  store i32 %50, i32* %retval, align 4, !dbg !1066
  br label %return, !dbg !1066

if.end44:                                         ; preds = %cond.end
  %call45 = call i32 @umask(i32 0) #7, !dbg !1067
  %51 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1068
  %user_umask = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %51, i32 0, i32 1, !dbg !1069
  store i32 %call45, i32* %user_umask, align 8, !dbg !1070
  %call46 = call i32 @umask(i32 %call45) #7, !dbg !1071
  %52 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1072
  %todo = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %52, i32 0, i32 21, !dbg !1073
  store i32 536870912, i32* %todo, align 8, !dbg !1074
  %53 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1075
  %flags = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %53, i32 0, i32 23, !dbg !1077
  %54 = load i32, i32* %flags, align 8, !dbg !1077
  %and47 = and i32 %54, 2, !dbg !1078
  %tobool48 = icmp ne i32 %and47, 0, !dbg !1078
  br i1 %tobool48, label %if.then49, label %if.else65, !dbg !1079

if.then49:                                        ; preds = %if.end44
  %55 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1080
  %todo50 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %55, i32 0, i32 21, !dbg !1082
  %56 = load i32, i32* %todo50, align 8, !dbg !1083
  %or = or i32 %56, 1073741824, !dbg !1083
  store i32 %or, i32* %todo50, align 8, !dbg !1083
  %57 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1084
  %mode51 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %57, i32 0, i32 30, !dbg !1086
  %58 = load i32, i32* %mode51, align 4, !dbg !1086
  %and52 = and i32 %58, 1024, !dbg !1087
  %tobool53 = icmp ne i32 %and52, 0, !dbg !1087
  br i1 %tobool53, label %if.then54, label %if.end57, !dbg !1088

if.then54:                                        ; preds = %if.then49
  %59 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1089
  %todo55 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %59, i32 0, i32 21, !dbg !1090
  %60 = load i32, i32* %todo55, align 8, !dbg !1091
  %or56 = or i32 %60, 100663296, !dbg !1091
  store i32 %or56, i32* %todo55, align 8, !dbg !1091
  br label %if.end57, !dbg !1089

if.end57:                                         ; preds = %if.then54, %if.then49
  %61 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1092
  %mode58 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %61, i32 0, i32 30, !dbg !1094
  %62 = load i32, i32* %mode58, align 4, !dbg !1094
  %and59 = and i32 %62, 2048, !dbg !1095
  %tobool60 = icmp ne i32 %and59, 0, !dbg !1095
  br i1 %tobool60, label %if.then61, label %if.end64, !dbg !1096

if.then61:                                        ; preds = %if.end57
  %63 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1097
  %todo62 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %63, i32 0, i32 21, !dbg !1098
  %64 = load i32, i32* %todo62, align 8, !dbg !1099
  %or63 = or i32 %64, 402653184, !dbg !1099
  store i32 %or63, i32* %todo62, align 8, !dbg !1099
  br label %if.end64, !dbg !1097

if.end64:                                         ; preds = %if.then61, %if.end57
  br label %if.end75, !dbg !1100

if.else65:                                        ; preds = %if.end44
  %65 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1101
  %mode66 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %65, i32 0, i32 30, !dbg !1103
  %66 = load i32, i32* %mode66, align 4, !dbg !1104
  %and67 = and i32 %66, -2049, !dbg !1104
  store i32 %and67, i32* %mode66, align 4, !dbg !1104
  %67 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1105
  %mode68 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %67, i32 0, i32 30, !dbg !1106
  %68 = load i32, i32* %mode68, align 4, !dbg !1107
  %and69 = and i32 %68, -1025, !dbg !1107
  store i32 %and69, i32* %mode68, align 4, !dbg !1107
  %69 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1108
  %mode70 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %69, i32 0, i32 30, !dbg !1109
  %70 = load i32, i32* %mode70, align 4, !dbg !1110
  %and71 = and i32 %70, -513, !dbg !1110
  store i32 %and71, i32* %mode70, align 4, !dbg !1110
  %71 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1111
  %user_umask72 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %71, i32 0, i32 1, !dbg !1112
  %72 = load i32, i32* %user_umask72, align 8, !dbg !1112
  %neg = xor i32 %72, -1, !dbg !1113
  %73 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1114
  %mode73 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %73, i32 0, i32 30, !dbg !1115
  %74 = load i32, i32* %mode73, align 4, !dbg !1116
  %and74 = and i32 %74, %neg, !dbg !1116
  store i32 %and74, i32* %mode73, align 4, !dbg !1116
  br label %if.end75

if.end75:                                         ; preds = %if.else65, %if.end64
  %75 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1117
  %flags76 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %75, i32 0, i32 23, !dbg !1119
  %76 = load i32, i32* %flags76, align 8, !dbg !1119
  %and77 = and i32 %76, 1, !dbg !1120
  %tobool78 = icmp ne i32 %and77, 0, !dbg !1120
  br i1 %tobool78, label %if.then79, label %if.end82, !dbg !1121

if.then79:                                        ; preds = %if.end75
  %77 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1122
  %todo80 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %77, i32 0, i32 21, !dbg !1123
  %78 = load i32, i32* %todo80, align 8, !dbg !1124
  %or81 = or i32 %78, 1, !dbg !1124
  store i32 %or81, i32* %todo80, align 8, !dbg !1124
  br label %if.end82, !dbg !1122

if.end82:                                         ; preds = %if.then79, %if.end75
  %79 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1125
  %flags83 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %79, i32 0, i32 23, !dbg !1127
  %80 = load i32, i32* %flags83, align 8, !dbg !1127
  %and84 = and i32 %80, 4, !dbg !1128
  %tobool85 = icmp ne i32 %and84, 0, !dbg !1128
  br i1 %tobool85, label %if.then86, label %if.end89, !dbg !1129

if.then86:                                        ; preds = %if.end82
  %81 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1130
  %todo87 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %81, i32 0, i32 21, !dbg !1131
  %82 = load i32, i32* %todo87, align 8, !dbg !1132
  %or88 = or i32 %82, 4, !dbg !1132
  store i32 %or88, i32* %todo87, align 8, !dbg !1132
  br label %if.end89, !dbg !1130

if.end89:                                         ; preds = %if.then86, %if.end82
  %83 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1133
  %flags90 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %83, i32 0, i32 23, !dbg !1135
  %84 = load i32, i32* %flags90, align 8, !dbg !1135
  %and91 = and i32 %84, 32, !dbg !1136
  %tobool92 = icmp ne i32 %and91, 0, !dbg !1136
  br i1 %tobool92, label %if.then93, label %if.end104, !dbg !1137

if.then93:                                        ; preds = %if.end89
  %85 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1138
  %entry94 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %85, i32 0, i32 18, !dbg !1141
  %86 = load %struct.archive_entry*, %struct.archive_entry** %entry94, align 8, !dbg !1141
  %call95 = call i32 @archive_entry_filetype(%struct.archive_entry* %86), !dbg !1142
  %cmp96 = icmp eq i32 %call95, 16384, !dbg !1143
  br i1 %cmp96, label %if.then97, label %if.else100, !dbg !1144

if.then97:                                        ; preds = %if.then93
  %87 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1145
  %deferred98 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %87, i32 0, i32 22, !dbg !1146
  %88 = load i32, i32* %deferred98, align 4, !dbg !1147
  %or99 = or i32 %88, 32, !dbg !1147
  store i32 %or99, i32* %deferred98, align 4, !dbg !1147
  br label %if.end103, !dbg !1145

if.else100:                                       ; preds = %if.then93
  %89 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1148
  %todo101 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %89, i32 0, i32 21, !dbg !1149
  %90 = load i32, i32* %todo101, align 8, !dbg !1150
  %or102 = or i32 %90, 32, !dbg !1150
  store i32 %or102, i32* %todo101, align 8, !dbg !1150
  br label %if.end103

if.end103:                                        ; preds = %if.else100, %if.then97
  br label %if.end104, !dbg !1151

if.end104:                                        ; preds = %if.end103, %if.end89
  %91 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1152
  %flags105 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %91, i32 0, i32 23, !dbg !1154
  %92 = load i32, i32* %flags105, align 8, !dbg !1154
  %and106 = and i32 %92, 8192, !dbg !1155
  %tobool107 = icmp ne i32 %and106, 0, !dbg !1155
  br i1 %tobool107, label %if.then108, label %if.end119, !dbg !1156

if.then108:                                       ; preds = %if.end104
  %93 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1157
  %entry109 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %93, i32 0, i32 18, !dbg !1160
  %94 = load %struct.archive_entry*, %struct.archive_entry** %entry109, align 8, !dbg !1160
  %call110 = call i32 @archive_entry_filetype(%struct.archive_entry* %94), !dbg !1161
  %cmp111 = icmp eq i32 %call110, 16384, !dbg !1162
  br i1 %cmp111, label %if.then112, label %if.else115, !dbg !1163

if.then112:                                       ; preds = %if.then108
  %95 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1164
  %deferred113 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %95, i32 0, i32 22, !dbg !1165
  %96 = load i32, i32* %deferred113, align 4, !dbg !1166
  %or114 = or i32 %96, 8192, !dbg !1166
  store i32 %or114, i32* %deferred113, align 4, !dbg !1166
  br label %if.end118, !dbg !1164

if.else115:                                       ; preds = %if.then108
  %97 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1167
  %todo116 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %97, i32 0, i32 21, !dbg !1168
  %98 = load i32, i32* %todo116, align 8, !dbg !1169
  %or117 = or i32 %98, 8192, !dbg !1169
  store i32 %or117, i32* %todo116, align 8, !dbg !1169
  br label %if.end118

if.end118:                                        ; preds = %if.else115, %if.then112
  br label %if.end119, !dbg !1170

if.end119:                                        ; preds = %if.end118, %if.end104
  %99 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1171
  %flags120 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %99, i32 0, i32 23, !dbg !1173
  %100 = load i32, i32* %flags120, align 8, !dbg !1173
  %and121 = and i32 %100, 128, !dbg !1174
  %tobool122 = icmp ne i32 %and121, 0, !dbg !1174
  br i1 %tobool122, label %if.then123, label %if.end126, !dbg !1175

if.then123:                                       ; preds = %if.end119
  %101 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1176
  %todo124 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %101, i32 0, i32 21, !dbg !1177
  %102 = load i32, i32* %todo124, align 8, !dbg !1178
  %or125 = or i32 %102, 128, !dbg !1178
  store i32 %or125, i32* %todo124, align 8, !dbg !1178
  br label %if.end126, !dbg !1176

if.end126:                                        ; preds = %if.then123, %if.end119
  %103 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1179
  %flags127 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %103, i32 0, i32 23, !dbg !1181
  %104 = load i32, i32* %flags127, align 8, !dbg !1181
  %and128 = and i32 %104, 64, !dbg !1182
  %tobool129 = icmp ne i32 %and128, 0, !dbg !1182
  br i1 %tobool129, label %if.then130, label %if.end133, !dbg !1183

if.then130:                                       ; preds = %if.end126
  %105 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1184
  %todo131 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %105, i32 0, i32 21, !dbg !1185
  %106 = load i32, i32* %todo131, align 8, !dbg !1186
  %or132 = or i32 %106, 64, !dbg !1186
  store i32 %or132, i32* %todo131, align 8, !dbg !1186
  br label %if.end133, !dbg !1184

if.end133:                                        ; preds = %if.then130, %if.end126
  %107 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1187
  %flags134 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %107, i32 0, i32 23, !dbg !1189
  %108 = load i32, i32* %flags134, align 8, !dbg !1189
  %and135 = and i32 %108, 256, !dbg !1190
  %tobool136 = icmp ne i32 %and135, 0, !dbg !1190
  br i1 %tobool136, label %if.then137, label %if.end142, !dbg !1191

if.then137:                                       ; preds = %if.end133
  %109 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1192
  %call138 = call i32 @check_symlinks(%struct.archive_write_disk* %109), !dbg !1194
  store i32 %call138, i32* %ret, align 4, !dbg !1195
  %110 = load i32, i32* %ret, align 4, !dbg !1196
  %cmp139 = icmp ne i32 %110, 0, !dbg !1198
  br i1 %cmp139, label %if.then140, label %if.end141, !dbg !1199

if.then140:                                       ; preds = %if.then137
  %111 = load i32, i32* %ret, align 4, !dbg !1200
  store i32 %111, i32* %retval, align 4, !dbg !1201
  br label %return, !dbg !1201

if.end141:                                        ; preds = %if.then137
  br label %if.end142, !dbg !1202

if.end142:                                        ; preds = %if.end141, %if.end133
  %112 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1203
  call void @edit_deep_directories(%struct.archive_write_disk* %112), !dbg !1204
  %113 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1205
  %call143 = call i32 @restore_entry(%struct.archive_write_disk* %113), !dbg !1206
  store i32 %call143, i32* %ret, align 4, !dbg !1207
  %114 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1208
  %restore_pwd144 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %114, i32 0, i32 29, !dbg !1210
  %115 = load i32, i32* %restore_pwd144, align 8, !dbg !1210
  %cmp145 = icmp sge i32 %115, 0, !dbg !1211
  br i1 %cmp145, label %if.then146, label %if.end157, !dbg !1212

if.then146:                                       ; preds = %if.end142
  %116 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1213
  %restore_pwd147 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %116, i32 0, i32 29, !dbg !1215
  %117 = load i32, i32* %restore_pwd147, align 8, !dbg !1215
  %call148 = call i32 @fchdir(i32 %117) #7, !dbg !1216
  store i32 %call148, i32* %r, align 4, !dbg !1217
  %118 = load i32, i32* %r, align 4, !dbg !1218
  %cmp149 = icmp ne i32 %118, 0, !dbg !1220
  br i1 %cmp149, label %if.then150, label %if.end153, !dbg !1221

if.then150:                                       ; preds = %if.then146
  %119 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1222
  %archive151 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %119, i32 0, i32 0, !dbg !1224
  %call152 = call i32* @__errno_location() #1, !dbg !1225
  %120 = load i32, i32* %call152, align 4, !dbg !1225
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive151, i32 %120, i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.10, i32 0, i32 0)), !dbg !1226
  store i32 -30, i32* %ret, align 4, !dbg !1228
  br label %if.end153, !dbg !1229

if.end153:                                        ; preds = %if.then150, %if.then146
  %121 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1230
  %restore_pwd154 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %121, i32 0, i32 29, !dbg !1231
  %122 = load i32, i32* %restore_pwd154, align 8, !dbg !1231
  %call155 = call i32 @close(i32 %122), !dbg !1232
  %123 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1233
  %restore_pwd156 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %123, i32 0, i32 29, !dbg !1234
  store i32 -1, i32* %restore_pwd156, align 8, !dbg !1235
  br label %if.end157, !dbg !1236

if.end157:                                        ; preds = %if.end153, %if.end142
  %124 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1237
  %deferred158 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %124, i32 0, i32 22, !dbg !1239
  %125 = load i32, i32* %deferred158, align 4, !dbg !1239
  %and159 = and i32 %125, 872415232, !dbg !1240
  %tobool160 = icmp ne i32 %and159, 0, !dbg !1240
  br i1 %tobool160, label %if.then161, label %if.end170, !dbg !1241

if.then161:                                       ; preds = %if.end157
  %126 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1242
  %127 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1244
  %call162 = call i8* @archive_entry_pathname(%struct.archive_entry* %127), !dbg !1245
  %call163 = call %struct.fixup_entry* @current_fixup(%struct.archive_write_disk* %126, i8* %call162), !dbg !1246
  store %struct.fixup_entry* %call163, %struct.fixup_entry** %fe, align 8, !dbg !1248
  %128 = load %struct.fixup_entry*, %struct.fixup_entry** %fe, align 8, !dbg !1249
  %cmp164 = icmp eq %struct.fixup_entry* %128, null, !dbg !1251
  br i1 %cmp164, label %if.then165, label %if.end166, !dbg !1252

if.then165:                                       ; preds = %if.then161
  store i32 -30, i32* %retval, align 4, !dbg !1253
  br label %return, !dbg !1253

if.end166:                                        ; preds = %if.then161
  %129 = load %struct.fixup_entry*, %struct.fixup_entry** %fe, align 8, !dbg !1254
  %fixup = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %129, i32 0, i32 14, !dbg !1255
  %130 = load i32, i32* %fixup, align 8, !dbg !1256
  %or167 = or i32 %130, 536870912, !dbg !1256
  store i32 %or167, i32* %fixup, align 8, !dbg !1256
  %131 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1257
  %mode168 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %131, i32 0, i32 30, !dbg !1258
  %132 = load i32, i32* %mode168, align 4, !dbg !1258
  %133 = load %struct.fixup_entry*, %struct.fixup_entry** %fe, align 8, !dbg !1259
  %mode169 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %133, i32 0, i32 2, !dbg !1260
  store i32 %132, i32* %mode169, align 8, !dbg !1261
  br label %if.end170, !dbg !1262

if.end170:                                        ; preds = %if.end166, %if.end157
  %134 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1263
  %deferred171 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %134, i32 0, i32 22, !dbg !1265
  %135 = load i32, i32* %deferred171, align 4, !dbg !1265
  %and172 = and i32 %135, 4, !dbg !1266
  %tobool173 = icmp ne i32 %and172, 0, !dbg !1266
  br i1 %tobool173, label %land.lhs.true, label %if.end218, !dbg !1267

land.lhs.true:                                    ; preds = %if.end170
  %136 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1268
  %call174 = call i32 @archive_entry_mtime_is_set(%struct.archive_entry* %136), !dbg !1270
  %tobool175 = icmp ne i32 %call174, 0, !dbg !1270
  br i1 %tobool175, label %if.then178, label %lor.lhs.false, !dbg !1271

lor.lhs.false:                                    ; preds = %land.lhs.true
  %137 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1272
  %call176 = call i32 @archive_entry_atime_is_set(%struct.archive_entry* %137), !dbg !1273
  %tobool177 = icmp ne i32 %call176, 0, !dbg !1273
  br i1 %tobool177, label %if.then178, label %if.end218, !dbg !1274

if.then178:                                       ; preds = %lor.lhs.false, %land.lhs.true
  %138 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1275
  %139 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1277
  %call179 = call i8* @archive_entry_pathname(%struct.archive_entry* %139), !dbg !1278
  %call180 = call %struct.fixup_entry* @current_fixup(%struct.archive_write_disk* %138, i8* %call179), !dbg !1279
  store %struct.fixup_entry* %call180, %struct.fixup_entry** %fe, align 8, !dbg !1281
  %140 = load %struct.fixup_entry*, %struct.fixup_entry** %fe, align 8, !dbg !1282
  %cmp181 = icmp eq %struct.fixup_entry* %140, null, !dbg !1284
  br i1 %cmp181, label %if.then182, label %if.end183, !dbg !1285

if.then182:                                       ; preds = %if.then178
  store i32 -30, i32* %retval, align 4, !dbg !1286
  br label %return, !dbg !1286

if.end183:                                        ; preds = %if.then178
  %141 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1287
  %mode184 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %141, i32 0, i32 30, !dbg !1288
  %142 = load i32, i32* %mode184, align 4, !dbg !1288
  %143 = load %struct.fixup_entry*, %struct.fixup_entry** %fe, align 8, !dbg !1289
  %mode185 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %143, i32 0, i32 2, !dbg !1290
  store i32 %142, i32* %mode185, align 8, !dbg !1291
  %144 = load %struct.fixup_entry*, %struct.fixup_entry** %fe, align 8, !dbg !1292
  %fixup186 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %144, i32 0, i32 14, !dbg !1293
  %145 = load i32, i32* %fixup186, align 8, !dbg !1294
  %or187 = or i32 %145, 4, !dbg !1294
  store i32 %or187, i32* %fixup186, align 8, !dbg !1294
  %146 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1295
  %call188 = call i32 @archive_entry_atime_is_set(%struct.archive_entry* %146), !dbg !1297
  %tobool189 = icmp ne i32 %call188, 0, !dbg !1297
  br i1 %tobool189, label %if.then190, label %if.else193, !dbg !1298

if.then190:                                       ; preds = %if.end183
  %147 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1299
  %call191 = call i64 @archive_entry_atime(%struct.archive_entry* %147), !dbg !1301
  %148 = load %struct.fixup_entry*, %struct.fixup_entry** %fe, align 8, !dbg !1302
  %atime = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %148, i32 0, i32 3, !dbg !1303
  store i64 %call191, i64* %atime, align 8, !dbg !1304
  %149 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1305
  %call192 = call i64 @archive_entry_atime_nsec(%struct.archive_entry* %149), !dbg !1306
  %150 = load %struct.fixup_entry*, %struct.fixup_entry** %fe, align 8, !dbg !1307
  %atime_nanos = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %150, i32 0, i32 7, !dbg !1308
  store i64 %call192, i64* %atime_nanos, align 8, !dbg !1309
  br label %if.end196, !dbg !1310

if.else193:                                       ; preds = %if.end183
  %151 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1311
  %start_time = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %151, i32 0, i32 8, !dbg !1313
  %152 = load i64, i64* %start_time, align 8, !dbg !1313
  %153 = load %struct.fixup_entry*, %struct.fixup_entry** %fe, align 8, !dbg !1314
  %atime194 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %153, i32 0, i32 3, !dbg !1315
  store i64 %152, i64* %atime194, align 8, !dbg !1316
  %154 = load %struct.fixup_entry*, %struct.fixup_entry** %fe, align 8, !dbg !1317
  %atime_nanos195 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %154, i32 0, i32 7, !dbg !1318
  store i64 0, i64* %atime_nanos195, align 8, !dbg !1319
  br label %if.end196

if.end196:                                        ; preds = %if.else193, %if.then190
  %155 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1320
  %call197 = call i32 @archive_entry_mtime_is_set(%struct.archive_entry* %155), !dbg !1322
  %tobool198 = icmp ne i32 %call197, 0, !dbg !1322
  br i1 %tobool198, label %if.then199, label %if.else202, !dbg !1323

if.then199:                                       ; preds = %if.end196
  %156 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1324
  %call200 = call i64 @archive_entry_mtime(%struct.archive_entry* %156), !dbg !1326
  %157 = load %struct.fixup_entry*, %struct.fixup_entry** %fe, align 8, !dbg !1327
  %mtime = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %157, i32 0, i32 5, !dbg !1328
  store i64 %call200, i64* %mtime, align 8, !dbg !1329
  %158 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1330
  %call201 = call i64 @archive_entry_mtime_nsec(%struct.archive_entry* %158), !dbg !1331
  %159 = load %struct.fixup_entry*, %struct.fixup_entry** %fe, align 8, !dbg !1332
  %mtime_nanos = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %159, i32 0, i32 9, !dbg !1333
  store i64 %call201, i64* %mtime_nanos, align 8, !dbg !1334
  br label %if.end206, !dbg !1335

if.else202:                                       ; preds = %if.end196
  %160 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1336
  %start_time203 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %160, i32 0, i32 8, !dbg !1338
  %161 = load i64, i64* %start_time203, align 8, !dbg !1338
  %162 = load %struct.fixup_entry*, %struct.fixup_entry** %fe, align 8, !dbg !1339
  %mtime204 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %162, i32 0, i32 5, !dbg !1340
  store i64 %161, i64* %mtime204, align 8, !dbg !1341
  %163 = load %struct.fixup_entry*, %struct.fixup_entry** %fe, align 8, !dbg !1342
  %mtime_nanos205 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %163, i32 0, i32 9, !dbg !1343
  store i64 0, i64* %mtime_nanos205, align 8, !dbg !1344
  br label %if.end206

if.end206:                                        ; preds = %if.else202, %if.then199
  %164 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1345
  %call207 = call i32 @archive_entry_birthtime_is_set(%struct.archive_entry* %164), !dbg !1347
  %tobool208 = icmp ne i32 %call207, 0, !dbg !1347
  br i1 %tobool208, label %if.then209, label %if.else212, !dbg !1348

if.then209:                                       ; preds = %if.end206
  %165 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1349
  %call210 = call i64 @archive_entry_birthtime(%struct.archive_entry* %165), !dbg !1351
  %166 = load %struct.fixup_entry*, %struct.fixup_entry** %fe, align 8, !dbg !1352
  %birthtime = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %166, i32 0, i32 4, !dbg !1353
  store i64 %call210, i64* %birthtime, align 8, !dbg !1354
  %167 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1355
  %call211 = call i64 @archive_entry_birthtime_nsec(%struct.archive_entry* %167), !dbg !1356
  %168 = load %struct.fixup_entry*, %struct.fixup_entry** %fe, align 8, !dbg !1357
  %birthtime_nanos = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %168, i32 0, i32 8, !dbg !1358
  store i64 %call211, i64* %birthtime_nanos, align 8, !dbg !1359
  br label %if.end217, !dbg !1360

if.else212:                                       ; preds = %if.end206
  %169 = load %struct.fixup_entry*, %struct.fixup_entry** %fe, align 8, !dbg !1361
  %mtime213 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %169, i32 0, i32 5, !dbg !1363
  %170 = load i64, i64* %mtime213, align 8, !dbg !1363
  %171 = load %struct.fixup_entry*, %struct.fixup_entry** %fe, align 8, !dbg !1364
  %birthtime214 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %171, i32 0, i32 4, !dbg !1365
  store i64 %170, i64* %birthtime214, align 8, !dbg !1366
  %172 = load %struct.fixup_entry*, %struct.fixup_entry** %fe, align 8, !dbg !1367
  %mtime_nanos215 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %172, i32 0, i32 9, !dbg !1368
  %173 = load i64, i64* %mtime_nanos215, align 8, !dbg !1368
  %174 = load %struct.fixup_entry*, %struct.fixup_entry** %fe, align 8, !dbg !1369
  %birthtime_nanos216 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %174, i32 0, i32 8, !dbg !1370
  store i64 %173, i64* %birthtime_nanos216, align 8, !dbg !1371
  br label %if.end217

if.end217:                                        ; preds = %if.else212, %if.then209
  br label %if.end218, !dbg !1372

if.end218:                                        ; preds = %if.end217, %lor.lhs.false, %if.end170
  %175 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1373
  %deferred219 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %175, i32 0, i32 22, !dbg !1375
  %176 = load i32, i32* %deferred219, align 4, !dbg !1375
  %and220 = and i32 %176, 32, !dbg !1376
  %tobool221 = icmp ne i32 %and220, 0, !dbg !1376
  br i1 %tobool221, label %if.then222, label %if.end231, !dbg !1377

if.then222:                                       ; preds = %if.end218
  %177 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1378
  %178 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1380
  %call223 = call i8* @archive_entry_pathname(%struct.archive_entry* %178), !dbg !1381
  %call224 = call %struct.fixup_entry* @current_fixup(%struct.archive_write_disk* %177, i8* %call223), !dbg !1382
  store %struct.fixup_entry* %call224, %struct.fixup_entry** %fe, align 8, !dbg !1384
  %179 = load %struct.fixup_entry*, %struct.fixup_entry** %fe, align 8, !dbg !1385
  %cmp225 = icmp eq %struct.fixup_entry* %179, null, !dbg !1387
  br i1 %cmp225, label %if.then226, label %if.end227, !dbg !1388

if.then226:                                       ; preds = %if.then222
  store i32 -30, i32* %retval, align 4, !dbg !1389
  br label %return, !dbg !1389

if.end227:                                        ; preds = %if.then222
  %180 = load %struct.fixup_entry*, %struct.fixup_entry** %fe, align 8, !dbg !1390
  %fixup228 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %180, i32 0, i32 14, !dbg !1391
  %181 = load i32, i32* %fixup228, align 8, !dbg !1392
  %or229 = or i32 %181, 32, !dbg !1392
  store i32 %or229, i32* %fixup228, align 8, !dbg !1392
  %182 = load %struct.fixup_entry*, %struct.fixup_entry** %fe, align 8, !dbg !1393
  %acl = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %182, i32 0, i32 1, !dbg !1394
  %183 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1395
  %call230 = call %struct.archive_acl* @archive_entry_acl(%struct.archive_entry* %183), !dbg !1396
  call void @archive_acl_copy(%struct.archive_acl* %acl, %struct.archive_acl* %call230), !dbg !1397
  br label %if.end231, !dbg !1398

if.end231:                                        ; preds = %if.end227, %if.end218
  %184 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1399
  %deferred232 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %184, i32 0, i32 22, !dbg !1401
  %185 = load i32, i32* %deferred232, align 4, !dbg !1401
  %and233 = and i32 %185, 8192, !dbg !1402
  %tobool234 = icmp ne i32 %and233, 0, !dbg !1402
  br i1 %tobool234, label %if.then235, label %if.end256, !dbg !1403

if.then235:                                       ; preds = %if.end231
  call void @llvm.dbg.declare(metadata i8** %metadata, metadata !1404, metadata !399), !dbg !1406
  call void @llvm.dbg.declare(metadata i64* %metadata_size, metadata !1407, metadata !399), !dbg !1408
  %186 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1409
  %entry236 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %186, i32 0, i32 18, !dbg !1410
  %187 = load %struct.archive_entry*, %struct.archive_entry** %entry236, align 8, !dbg !1410
  %call237 = call i8* @archive_entry_mac_metadata(%struct.archive_entry* %187, i64* %metadata_size), !dbg !1411
  store i8* %call237, i8** %metadata, align 8, !dbg !1412
  %188 = load i8*, i8** %metadata, align 8, !dbg !1413
  %cmp238 = icmp ne i8* %188, null, !dbg !1415
  br i1 %cmp238, label %land.lhs.true239, label %if.end255, !dbg !1416

land.lhs.true239:                                 ; preds = %if.then235
  %189 = load i64, i64* %metadata_size, align 8, !dbg !1417
  %cmp240 = icmp ugt i64 %189, 0, !dbg !1419
  br i1 %cmp240, label %if.then241, label %if.end255, !dbg !1420

if.then241:                                       ; preds = %land.lhs.true239
  %190 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1421
  %191 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1423
  %call242 = call i8* @archive_entry_pathname(%struct.archive_entry* %191), !dbg !1424
  %call243 = call %struct.fixup_entry* @current_fixup(%struct.archive_write_disk* %190, i8* %call242), !dbg !1425
  store %struct.fixup_entry* %call243, %struct.fixup_entry** %fe, align 8, !dbg !1427
  %192 = load %struct.fixup_entry*, %struct.fixup_entry** %fe, align 8, !dbg !1428
  %cmp244 = icmp eq %struct.fixup_entry* %192, null, !dbg !1430
  br i1 %cmp244, label %if.then245, label %if.end246, !dbg !1431

if.then245:                                       ; preds = %if.then241
  store i32 -30, i32* %retval, align 4, !dbg !1432
  br label %return, !dbg !1432

if.end246:                                        ; preds = %if.then241
  %193 = load i64, i64* %metadata_size, align 8, !dbg !1433
  %call247 = call noalias i8* @malloc(i64 %193) #7, !dbg !1434
  %194 = load %struct.fixup_entry*, %struct.fixup_entry** %fe, align 8, !dbg !1435
  %mac_metadata = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %194, i32 0, i32 13, !dbg !1436
  store i8* %call247, i8** %mac_metadata, align 8, !dbg !1437
  %195 = load %struct.fixup_entry*, %struct.fixup_entry** %fe, align 8, !dbg !1438
  %mac_metadata248 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %195, i32 0, i32 13, !dbg !1440
  %196 = load i8*, i8** %mac_metadata248, align 8, !dbg !1440
  %cmp249 = icmp ne i8* %196, null, !dbg !1441
  br i1 %cmp249, label %if.then250, label %if.end254, !dbg !1442

if.then250:                                       ; preds = %if.end246
  %197 = load %struct.fixup_entry*, %struct.fixup_entry** %fe, align 8, !dbg !1443
  %mac_metadata251 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %197, i32 0, i32 13, !dbg !1445
  %198 = load i8*, i8** %mac_metadata251, align 8, !dbg !1445
  %199 = load i8*, i8** %metadata, align 8, !dbg !1446
  %200 = load i64, i64* %metadata_size, align 8, !dbg !1447
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %198, i8* %199, i64 %200, i32 1, i1 false), !dbg !1448
  %201 = load i64, i64* %metadata_size, align 8, !dbg !1449
  %202 = load %struct.fixup_entry*, %struct.fixup_entry** %fe, align 8, !dbg !1450
  %mac_metadata_size = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %202, i32 0, i32 12, !dbg !1451
  store i64 %201, i64* %mac_metadata_size, align 8, !dbg !1452
  %203 = load %struct.fixup_entry*, %struct.fixup_entry** %fe, align 8, !dbg !1453
  %fixup252 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %203, i32 0, i32 14, !dbg !1454
  %204 = load i32, i32* %fixup252, align 8, !dbg !1455
  %or253 = or i32 %204, 8192, !dbg !1455
  store i32 %or253, i32* %fixup252, align 8, !dbg !1455
  br label %if.end254, !dbg !1456

if.end254:                                        ; preds = %if.then250, %if.end246
  br label %if.end255, !dbg !1457

if.end255:                                        ; preds = %if.end254, %land.lhs.true239, %if.then235
  br label %if.end256, !dbg !1458

if.end256:                                        ; preds = %if.end255, %if.end231
  %205 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1459
  %deferred257 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %205, i32 0, i32 22, !dbg !1461
  %206 = load i32, i32* %deferred257, align 4, !dbg !1461
  %and258 = and i32 %206, 64, !dbg !1462
  %tobool259 = icmp ne i32 %and258, 0, !dbg !1462
  br i1 %tobool259, label %if.then260, label %if.end268, !dbg !1463

if.then260:                                       ; preds = %if.end256
  %207 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1464
  %208 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1466
  %call261 = call i8* @archive_entry_pathname(%struct.archive_entry* %208), !dbg !1467
  %call262 = call %struct.fixup_entry* @current_fixup(%struct.archive_write_disk* %207, i8* %call261), !dbg !1468
  store %struct.fixup_entry* %call262, %struct.fixup_entry** %fe, align 8, !dbg !1470
  %209 = load %struct.fixup_entry*, %struct.fixup_entry** %fe, align 8, !dbg !1471
  %cmp263 = icmp eq %struct.fixup_entry* %209, null, !dbg !1473
  br i1 %cmp263, label %if.then264, label %if.end265, !dbg !1474

if.then264:                                       ; preds = %if.then260
  store i32 -30, i32* %retval, align 4, !dbg !1475
  br label %return, !dbg !1475

if.end265:                                        ; preds = %if.then260
  %210 = load %struct.fixup_entry*, %struct.fixup_entry** %fe, align 8, !dbg !1476
  %fixup266 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %210, i32 0, i32 14, !dbg !1477
  %211 = load i32, i32* %fixup266, align 8, !dbg !1478
  %or267 = or i32 %211, 64, !dbg !1478
  store i32 %or267, i32* %fixup266, align 8, !dbg !1478
  br label %if.end268, !dbg !1479

if.end268:                                        ; preds = %if.end265, %if.end256
  %212 = load i32, i32* %ret, align 4, !dbg !1480
  %cmp269 = icmp sge i32 %212, -20, !dbg !1482
  br i1 %cmp269, label %if.then270, label %if.end273, !dbg !1483

if.then270:                                       ; preds = %if.end268
  %213 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1484
  %archive271 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %213, i32 0, i32 0, !dbg !1485
  %state272 = getelementptr inbounds %struct.archive, %struct.archive* %archive271, i32 0, i32 1, !dbg !1486
  store i32 4, i32* %state272, align 4, !dbg !1487
  br label %if.end273, !dbg !1484

if.end273:                                        ; preds = %if.then270, %if.end268
  %214 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1488
  %fd274 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %214, i32 0, i32 24, !dbg !1490
  %215 = load i32, i32* %fd274, align 4, !dbg !1490
  %cmp275 = icmp slt i32 %215, 0, !dbg !1491
  br i1 %cmp275, label %if.then276, label %if.end278, !dbg !1492

if.then276:                                       ; preds = %if.end273
  %216 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1493
  call void @archive_entry_set_size(%struct.archive_entry* %216, i64 0), !dbg !1495
  %217 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1496
  %filesize277 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %217, i32 0, i32 28, !dbg !1497
  store i64 0, i64* %filesize277, align 8, !dbg !1498
  br label %if.end278, !dbg !1499

if.end278:                                        ; preds = %if.then276, %if.end273
  %218 = load i32, i32* %ret, align 4, !dbg !1500
  store i32 %218, i32* %retval, align 4, !dbg !1501
  br label %return, !dbg !1501

return:                                           ; preds = %if.end278, %if.then264, %if.then245, %if.then226, %if.then182, %if.then165, %if.then140, %if.then43, %if.then8, %if.then
  %219 = load i32, i32* %retval, align 4, !dbg !1502
  ret i32 %219, !dbg !1502
}

; Function Attrs: nounwind uwtable
define internal i32 @_archive_write_disk_finish_entry(%struct.archive* %_a) #0 !dbg !373 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_write_disk*, align 8
  %ret = alloca i32, align 4
  %magic_test = alloca i32, align 4
  %nul = alloca i8, align 1
  %r2 = alloca i32, align 4
  %r288 = alloca i32, align 4
  %r298 = alloca i32, align 4
  %r2108 = alloca i32, align 4
  %r2118 = alloca i32, align 4
  %r2128 = alloca i32, align 4
  %metadata = alloca i8*, align 8
  %metadata_size = alloca i64, align 8
  %r2144 = alloca i32, align 4
  %r2157 = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !1503, metadata !399), !dbg !1504
  call void @llvm.dbg.declare(metadata %struct.archive_write_disk** %a, metadata !1505, metadata !399), !dbg !1506
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1507
  %1 = bitcast %struct.archive* %0 to %struct.archive_write_disk*, !dbg !1508
  store %struct.archive_write_disk* %1, %struct.archive_write_disk** %a, align 8, !dbg !1506
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !1509, metadata !399), !dbg !1510
  store i32 0, i32* %ret, align 4, !dbg !1510
  br label %do.body, !dbg !1511

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !1512, metadata !399), !dbg !1514
  %2 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1515
  %archive = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %2, i32 0, i32 0, !dbg !1515
  %call = call i32 @__archive_check_magic(%struct.archive* %archive, i32 -1073631035, i32 6, i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.38, i32 0, i32 0)), !dbg !1515
  store i32 %call, i32* %magic_test, align 4, !dbg !1515
  %3 = load i32, i32* %magic_test, align 4, !dbg !1515
  %cmp = icmp eq i32 %3, -30, !dbg !1515
  br i1 %cmp, label %if.then, label %if.end, !dbg !1515

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !1517
  br label %return, !dbg !1517

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !1520

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1522
  %archive1 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %4, i32 0, i32 0, !dbg !1524
  %state = getelementptr inbounds %struct.archive, %struct.archive* %archive1, i32 0, i32 1, !dbg !1525
  %5 = load i32, i32* %state, align 4, !dbg !1525
  %and = and i32 %5, 2, !dbg !1526
  %tobool = icmp ne i32 %and, 0, !dbg !1526
  br i1 %tobool, label %if.then2, label %if.end3, !dbg !1527

if.then2:                                         ; preds = %do.end
  store i32 0, i32* %retval, align 4, !dbg !1528
  br label %return, !dbg !1528

if.end3:                                          ; preds = %do.end
  %6 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1529
  %archive4 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %6, i32 0, i32 0, !dbg !1530
  call void @archive_clear_error(%struct.archive* %archive4), !dbg !1531
  %7 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1532
  %fd = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %7, i32 0, i32 24, !dbg !1534
  %8 = load i32, i32* %fd, align 4, !dbg !1534
  %cmp5 = icmp slt i32 %8, 0, !dbg !1535
  br i1 %cmp5, label %if.then6, label %if.else, !dbg !1536

if.then6:                                         ; preds = %if.end3
  br label %if.end50, !dbg !1537

if.else:                                          ; preds = %if.end3
  %9 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1539
  %filesize = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %9, i32 0, i32 28, !dbg !1542
  %10 = load i64, i64* %filesize, align 8, !dbg !1542
  %cmp7 = icmp slt i64 %10, 0, !dbg !1543
  br i1 %cmp7, label %if.then8, label %if.else9, !dbg !1539

if.then8:                                         ; preds = %if.else
  br label %if.end49, !dbg !1544

if.else9:                                         ; preds = %if.else
  %11 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1546
  %fd_offset = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %11, i32 0, i32 26, !dbg !1549
  %12 = load i64, i64* %fd_offset, align 8, !dbg !1549
  %13 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1550
  %filesize10 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %13, i32 0, i32 28, !dbg !1551
  %14 = load i64, i64* %filesize10, align 8, !dbg !1551
  %cmp11 = icmp eq i64 %12, %14, !dbg !1552
  br i1 %cmp11, label %if.then12, label %if.else13, !dbg !1546

if.then12:                                        ; preds = %if.else9
  br label %if.end48, !dbg !1553

if.else13:                                        ; preds = %if.else9
  %15 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1555
  %fd14 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %15, i32 0, i32 24, !dbg !1558
  %16 = load i32, i32* %fd14, align 4, !dbg !1558
  %17 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1559
  %filesize15 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %17, i32 0, i32 28, !dbg !1560
  %18 = load i64, i64* %filesize15, align 8, !dbg !1560
  %call16 = call i32 @ftruncate(i32 %16, i64 %18) #7, !dbg !1561
  %cmp17 = icmp eq i32 %call16, -1, !dbg !1562
  br i1 %cmp17, label %land.lhs.true, label %if.end23, !dbg !1563

land.lhs.true:                                    ; preds = %if.else13
  %19 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1564
  %filesize18 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %19, i32 0, i32 28, !dbg !1565
  %20 = load i64, i64* %filesize18, align 8, !dbg !1565
  %cmp19 = icmp eq i64 %20, 0, !dbg !1566
  br i1 %cmp19, label %if.then20, label %if.end23, !dbg !1567

if.then20:                                        ; preds = %land.lhs.true
  %21 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1569
  %archive21 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %21, i32 0, i32 0, !dbg !1571
  %call22 = call i32* @__errno_location() #1, !dbg !1572
  %22 = load i32, i32* %call22, align 4, !dbg !1572
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive21, i32 %22, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.39, i32 0, i32 0)), !dbg !1573
  store i32 -25, i32* %retval, align 4, !dbg !1575
  br label %return, !dbg !1575

if.end23:                                         ; preds = %land.lhs.true, %if.else13
  %23 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1576
  %pst = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %23, i32 0, i32 17, !dbg !1577
  store %struct.stat* null, %struct.stat** %pst, align 8, !dbg !1578
  %24 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1579
  %call24 = call i32 @lazy_stat(%struct.archive_write_disk* %24), !dbg !1581
  store i32 %call24, i32* %ret, align 4, !dbg !1582
  %cmp25 = icmp ne i32 %call24, 0, !dbg !1583
  br i1 %cmp25, label %if.then26, label %if.end27, !dbg !1584

if.then26:                                        ; preds = %if.end23
  %25 = load i32, i32* %ret, align 4, !dbg !1585
  store i32 %25, i32* %retval, align 4, !dbg !1586
  br label %return, !dbg !1586

if.end27:                                         ; preds = %if.end23
  %26 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1587
  %st = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %26, i32 0, i32 16, !dbg !1589
  %st_size = getelementptr inbounds %struct.stat, %struct.stat* %st, i32 0, i32 8, !dbg !1590
  %27 = load i64, i64* %st_size, align 8, !dbg !1590
  %28 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1591
  %filesize28 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %28, i32 0, i32 28, !dbg !1592
  %29 = load i64, i64* %filesize28, align 8, !dbg !1592
  %cmp29 = icmp slt i64 %27, %29, !dbg !1593
  br i1 %cmp29, label %if.then30, label %if.end47, !dbg !1594

if.then30:                                        ; preds = %if.end27
  call void @llvm.dbg.declare(metadata i8* %nul, metadata !1595, metadata !399), !dbg !1597
  store i8 0, i8* %nul, align 1, !dbg !1597
  %30 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1598
  %fd31 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %30, i32 0, i32 24, !dbg !1600
  %31 = load i32, i32* %fd31, align 4, !dbg !1600
  %32 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1601
  %filesize32 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %32, i32 0, i32 28, !dbg !1602
  %33 = load i64, i64* %filesize32, align 8, !dbg !1602
  %sub = sub nsw i64 %33, 1, !dbg !1603
  %call33 = call i64 @lseek(i32 %31, i64 %sub, i32 0) #7, !dbg !1604
  %cmp34 = icmp slt i64 %call33, 0, !dbg !1605
  br i1 %cmp34, label %if.then35, label %if.end38, !dbg !1606

if.then35:                                        ; preds = %if.then30
  %34 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1607
  %archive36 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %34, i32 0, i32 0, !dbg !1609
  %call37 = call i32* @__errno_location() #1, !dbg !1610
  %35 = load i32, i32* %call37, align 4, !dbg !1610
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive36, i32 %35, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.40, i32 0, i32 0)), !dbg !1611
  store i32 -30, i32* %retval, align 4, !dbg !1613
  br label %return, !dbg !1613

if.end38:                                         ; preds = %if.then30
  %36 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1614
  %fd39 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %36, i32 0, i32 24, !dbg !1616
  %37 = load i32, i32* %fd39, align 4, !dbg !1616
  %call40 = call i64 @write(i32 %37, i8* %nul, i64 1), !dbg !1617
  %cmp41 = icmp slt i64 %call40, 0, !dbg !1618
  br i1 %cmp41, label %if.then42, label %if.end45, !dbg !1619

if.then42:                                        ; preds = %if.end38
  %38 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1620
  %archive43 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %38, i32 0, i32 0, !dbg !1622
  %call44 = call i32* @__errno_location() #1, !dbg !1623
  %39 = load i32, i32* %call44, align 4, !dbg !1623
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive43, i32 %39, i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.41, i32 0, i32 0)), !dbg !1624
  store i32 -30, i32* %retval, align 4, !dbg !1626
  br label %return, !dbg !1626

if.end45:                                         ; preds = %if.end38
  %40 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1627
  %pst46 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %40, i32 0, i32 17, !dbg !1628
  store %struct.stat* null, %struct.stat** %pst46, align 8, !dbg !1629
  br label %if.end47, !dbg !1630

if.end47:                                         ; preds = %if.end45, %if.end27
  br label %if.end48

if.end48:                                         ; preds = %if.end47, %if.then12
  br label %if.end49

if.end49:                                         ; preds = %if.end48, %if.then8
  br label %if.end50

if.end50:                                         ; preds = %if.end49, %if.then6
  %41 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1631
  %todo = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %41, i32 0, i32 21, !dbg !1633
  %42 = load i32, i32* %todo, align 8, !dbg !1633
  %and51 = and i32 %42, 16777216, !dbg !1634
  %tobool52 = icmp ne i32 %and51, 0, !dbg !1634
  br i1 %tobool52, label %if.then53, label %if.end61, !dbg !1635

if.then53:                                        ; preds = %if.end50
  call void @llvm.dbg.declare(metadata i32* %r2, metadata !1636, metadata !399), !dbg !1638
  %43 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1639
  %44 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1640
  %name = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %44, i32 0, i32 19, !dbg !1641
  %45 = load i8*, i8** %name, align 8, !dbg !1641
  %call54 = call i32 @fixup_appledouble(%struct.archive_write_disk* %43, i8* %45), !dbg !1642
  store i32 %call54, i32* %r2, align 4, !dbg !1638
  %46 = load i32, i32* %r2, align 4, !dbg !1643
  %cmp55 = icmp eq i32 %46, 1, !dbg !1645
  br i1 %cmp55, label %if.then56, label %if.end57, !dbg !1646

if.then56:                                        ; preds = %if.then53
  br label %finish_metadata, !dbg !1647

if.end57:                                         ; preds = %if.then53
  %47 = load i32, i32* %r2, align 4, !dbg !1649
  %48 = load i32, i32* %ret, align 4, !dbg !1651
  %cmp58 = icmp slt i32 %47, %48, !dbg !1652
  br i1 %cmp58, label %if.then59, label %if.end60, !dbg !1653

if.then59:                                        ; preds = %if.end57
  %49 = load i32, i32* %r2, align 4, !dbg !1654
  store i32 %49, i32* %ret, align 4, !dbg !1656
  br label %if.end60, !dbg !1657

if.end60:                                         ; preds = %if.then59, %if.end57
  br label %if.end61, !dbg !1658

if.end61:                                         ; preds = %if.end60, %if.end50
  %50 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1659
  %todo62 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %50, i32 0, i32 21, !dbg !1661
  %51 = load i32, i32* %todo62, align 8, !dbg !1661
  %and63 = and i32 %51, 335544321, !dbg !1662
  %tobool64 = icmp ne i32 %and63, 0, !dbg !1662
  br i1 %tobool64, label %if.then65, label %if.end72, !dbg !1663

if.then65:                                        ; preds = %if.end61
  %52 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1664
  %archive66 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %52, i32 0, i32 0, !dbg !1666
  %53 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1667
  %entry67 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %53, i32 0, i32 18, !dbg !1668
  %54 = load %struct.archive_entry*, %struct.archive_entry** %entry67, align 8, !dbg !1668
  %call68 = call i8* @archive_entry_uname(%struct.archive_entry* %54), !dbg !1669
  %55 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1670
  %entry69 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %55, i32 0, i32 18, !dbg !1671
  %56 = load %struct.archive_entry*, %struct.archive_entry** %entry69, align 8, !dbg !1671
  %call70 = call i64 @archive_entry_uid(%struct.archive_entry* %56), !dbg !1672
  %call71 = call i64 @archive_write_disk_uid(%struct.archive* %archive66, i8* %call68, i64 %call70), !dbg !1673
  %57 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1674
  %uid = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %57, i32 0, i32 31, !dbg !1675
  store i64 %call71, i64* %uid, align 8, !dbg !1676
  br label %if.end72, !dbg !1677

if.end72:                                         ; preds = %if.then65, %if.end61
  %58 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1678
  %todo73 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %58, i32 0, i32 21, !dbg !1680
  %59 = load i32, i32* %todo73, align 8, !dbg !1680
  %and74 = and i32 %59, 335544321, !dbg !1681
  %tobool75 = icmp ne i32 %and74, 0, !dbg !1681
  br i1 %tobool75, label %if.then76, label %if.end83, !dbg !1682

if.then76:                                        ; preds = %if.end72
  %60 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1683
  %archive77 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %60, i32 0, i32 0, !dbg !1685
  %61 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1686
  %entry78 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %61, i32 0, i32 18, !dbg !1687
  %62 = load %struct.archive_entry*, %struct.archive_entry** %entry78, align 8, !dbg !1687
  %call79 = call i8* @archive_entry_gname(%struct.archive_entry* %62), !dbg !1688
  %63 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1689
  %entry80 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %63, i32 0, i32 18, !dbg !1690
  %64 = load %struct.archive_entry*, %struct.archive_entry** %entry80, align 8, !dbg !1690
  %call81 = call i64 @archive_entry_gid(%struct.archive_entry* %64), !dbg !1691
  %call82 = call i64 @archive_write_disk_gid(%struct.archive* %archive77, i8* %call79, i64 %call81), !dbg !1692
  %65 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1693
  %gid = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %65, i32 0, i32 32, !dbg !1694
  store i64 %call82, i64* %gid, align 8, !dbg !1695
  br label %if.end83, !dbg !1696

if.end83:                                         ; preds = %if.then76, %if.end72
  %66 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1697
  %todo84 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %66, i32 0, i32 21, !dbg !1699
  %67 = load i32, i32* %todo84, align 8, !dbg !1699
  %and85 = and i32 %67, 1, !dbg !1700
  %tobool86 = icmp ne i32 %and85, 0, !dbg !1700
  br i1 %tobool86, label %if.then87, label %if.end93, !dbg !1701

if.then87:                                        ; preds = %if.end83
  call void @llvm.dbg.declare(metadata i32* %r288, metadata !1702, metadata !399), !dbg !1704
  %68 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1705
  %call89 = call i32 @set_ownership(%struct.archive_write_disk* %68), !dbg !1706
  store i32 %call89, i32* %r288, align 4, !dbg !1704
  %69 = load i32, i32* %r288, align 4, !dbg !1707
  %70 = load i32, i32* %ret, align 4, !dbg !1709
  %cmp90 = icmp slt i32 %69, %70, !dbg !1710
  br i1 %cmp90, label %if.then91, label %if.end92, !dbg !1711

if.then91:                                        ; preds = %if.then87
  %71 = load i32, i32* %r288, align 4, !dbg !1712
  store i32 %71, i32* %ret, align 4, !dbg !1714
  br label %if.end92, !dbg !1715

if.end92:                                         ; preds = %if.then91, %if.then87
  br label %if.end93, !dbg !1716

if.end93:                                         ; preds = %if.end92, %if.end83
  %72 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1717
  %todo94 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %72, i32 0, i32 21, !dbg !1719
  %73 = load i32, i32* %todo94, align 8, !dbg !1719
  %and95 = and i32 %73, 872415232, !dbg !1720
  %tobool96 = icmp ne i32 %and95, 0, !dbg !1720
  br i1 %tobool96, label %if.then97, label %if.end103, !dbg !1721

if.then97:                                        ; preds = %if.end93
  call void @llvm.dbg.declare(metadata i32* %r298, metadata !1722, metadata !399), !dbg !1724
  %74 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1725
  %75 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1726
  %mode = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %75, i32 0, i32 30, !dbg !1727
  %76 = load i32, i32* %mode, align 4, !dbg !1727
  %call99 = call i32 @set_mode(%struct.archive_write_disk* %74, i32 %76), !dbg !1728
  store i32 %call99, i32* %r298, align 4, !dbg !1724
  %77 = load i32, i32* %r298, align 4, !dbg !1729
  %78 = load i32, i32* %ret, align 4, !dbg !1731
  %cmp100 = icmp slt i32 %77, %78, !dbg !1732
  br i1 %cmp100, label %if.then101, label %if.end102, !dbg !1733

if.then101:                                       ; preds = %if.then97
  %79 = load i32, i32* %r298, align 4, !dbg !1734
  store i32 %79, i32* %ret, align 4, !dbg !1736
  br label %if.end102, !dbg !1737

if.end102:                                        ; preds = %if.then101, %if.then97
  br label %if.end103, !dbg !1738

if.end103:                                        ; preds = %if.end102, %if.end93
  %80 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1739
  %todo104 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %80, i32 0, i32 21, !dbg !1741
  %81 = load i32, i32* %todo104, align 8, !dbg !1741
  %and105 = and i32 %81, 128, !dbg !1742
  %tobool106 = icmp ne i32 %and105, 0, !dbg !1742
  br i1 %tobool106, label %if.then107, label %if.end113, !dbg !1743

if.then107:                                       ; preds = %if.end103
  call void @llvm.dbg.declare(metadata i32* %r2108, metadata !1744, metadata !399), !dbg !1746
  %82 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1747
  %call109 = call i32 @set_xattrs(%struct.archive_write_disk* %82), !dbg !1748
  store i32 %call109, i32* %r2108, align 4, !dbg !1746
  %83 = load i32, i32* %r2108, align 4, !dbg !1749
  %84 = load i32, i32* %ret, align 4, !dbg !1751
  %cmp110 = icmp slt i32 %83, %84, !dbg !1752
  br i1 %cmp110, label %if.then111, label %if.end112, !dbg !1753

if.then111:                                       ; preds = %if.then107
  %85 = load i32, i32* %r2108, align 4, !dbg !1754
  store i32 %85, i32* %ret, align 4, !dbg !1756
  br label %if.end112, !dbg !1757

if.end112:                                        ; preds = %if.then111, %if.then107
  br label %if.end113, !dbg !1758

if.end113:                                        ; preds = %if.end112, %if.end103
  %86 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1759
  %todo114 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %86, i32 0, i32 21, !dbg !1761
  %87 = load i32, i32* %todo114, align 8, !dbg !1761
  %and115 = and i32 %87, 64, !dbg !1762
  %tobool116 = icmp ne i32 %and115, 0, !dbg !1762
  br i1 %tobool116, label %if.then117, label %if.end123, !dbg !1763

if.then117:                                       ; preds = %if.end113
  call void @llvm.dbg.declare(metadata i32* %r2118, metadata !1764, metadata !399), !dbg !1766
  %88 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1767
  %call119 = call i32 @set_fflags(%struct.archive_write_disk* %88), !dbg !1768
  store i32 %call119, i32* %r2118, align 4, !dbg !1766
  %89 = load i32, i32* %r2118, align 4, !dbg !1769
  %90 = load i32, i32* %ret, align 4, !dbg !1771
  %cmp120 = icmp slt i32 %89, %90, !dbg !1772
  br i1 %cmp120, label %if.then121, label %if.end122, !dbg !1773

if.then121:                                       ; preds = %if.then117
  %91 = load i32, i32* %r2118, align 4, !dbg !1774
  store i32 %91, i32* %ret, align 4, !dbg !1776
  br label %if.end122, !dbg !1777

if.end122:                                        ; preds = %if.then121, %if.then117
  br label %if.end123, !dbg !1778

if.end123:                                        ; preds = %if.end122, %if.end113
  %92 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1779
  %todo124 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %92, i32 0, i32 21, !dbg !1781
  %93 = load i32, i32* %todo124, align 8, !dbg !1781
  %and125 = and i32 %93, 4, !dbg !1782
  %tobool126 = icmp ne i32 %and125, 0, !dbg !1782
  br i1 %tobool126, label %if.then127, label %if.end133, !dbg !1783

if.then127:                                       ; preds = %if.end123
  call void @llvm.dbg.declare(metadata i32* %r2128, metadata !1784, metadata !399), !dbg !1786
  %94 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1787
  %call129 = call i32 @set_times_from_entry(%struct.archive_write_disk* %94), !dbg !1788
  store i32 %call129, i32* %r2128, align 4, !dbg !1786
  %95 = load i32, i32* %r2128, align 4, !dbg !1789
  %96 = load i32, i32* %ret, align 4, !dbg !1791
  %cmp130 = icmp slt i32 %95, %96, !dbg !1792
  br i1 %cmp130, label %if.then131, label %if.end132, !dbg !1793

if.then131:                                       ; preds = %if.then127
  %97 = load i32, i32* %r2128, align 4, !dbg !1794
  store i32 %97, i32* %ret, align 4, !dbg !1796
  br label %if.end132, !dbg !1797

if.end132:                                        ; preds = %if.then131, %if.then127
  br label %if.end133, !dbg !1798

if.end133:                                        ; preds = %if.end132, %if.end123
  %98 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1799
  %todo134 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %98, i32 0, i32 21, !dbg !1801
  %99 = load i32, i32* %todo134, align 8, !dbg !1801
  %and135 = and i32 %99, 8192, !dbg !1802
  %tobool136 = icmp ne i32 %and135, 0, !dbg !1802
  br i1 %tobool136, label %if.then137, label %if.end152, !dbg !1803

if.then137:                                       ; preds = %if.end133
  call void @llvm.dbg.declare(metadata i8** %metadata, metadata !1804, metadata !399), !dbg !1806
  call void @llvm.dbg.declare(metadata i64* %metadata_size, metadata !1807, metadata !399), !dbg !1808
  %100 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1809
  %entry138 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %100, i32 0, i32 18, !dbg !1810
  %101 = load %struct.archive_entry*, %struct.archive_entry** %entry138, align 8, !dbg !1810
  %call139 = call i8* @archive_entry_mac_metadata(%struct.archive_entry* %101, i64* %metadata_size), !dbg !1811
  store i8* %call139, i8** %metadata, align 8, !dbg !1812
  %102 = load i8*, i8** %metadata, align 8, !dbg !1813
  %cmp140 = icmp ne i8* %102, null, !dbg !1815
  br i1 %cmp140, label %land.lhs.true141, label %if.end151, !dbg !1816

land.lhs.true141:                                 ; preds = %if.then137
  %103 = load i64, i64* %metadata_size, align 8, !dbg !1817
  %cmp142 = icmp ugt i64 %103, 0, !dbg !1819
  br i1 %cmp142, label %if.then143, label %if.end151, !dbg !1820

if.then143:                                       ; preds = %land.lhs.true141
  call void @llvm.dbg.declare(metadata i32* %r2144, metadata !1821, metadata !399), !dbg !1823
  %104 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1824
  %105 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1825
  %entry145 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %105, i32 0, i32 18, !dbg !1826
  %106 = load %struct.archive_entry*, %struct.archive_entry** %entry145, align 8, !dbg !1826
  %call146 = call i8* @archive_entry_pathname(%struct.archive_entry* %106), !dbg !1827
  %107 = load i8*, i8** %metadata, align 8, !dbg !1828
  %108 = load i64, i64* %metadata_size, align 8, !dbg !1829
  %call147 = call i32 @set_mac_metadata(%struct.archive_write_disk* %104, i8* %call146, i8* %107, i64 %108), !dbg !1830
  store i32 %call147, i32* %r2144, align 4, !dbg !1823
  %109 = load i32, i32* %r2144, align 4, !dbg !1832
  %110 = load i32, i32* %ret, align 4, !dbg !1834
  %cmp148 = icmp slt i32 %109, %110, !dbg !1835
  br i1 %cmp148, label %if.then149, label %if.end150, !dbg !1836

if.then149:                                       ; preds = %if.then143
  %111 = load i32, i32* %r2144, align 4, !dbg !1837
  store i32 %111, i32* %ret, align 4, !dbg !1839
  br label %if.end150, !dbg !1840

if.end150:                                        ; preds = %if.then149, %if.then143
  br label %if.end151, !dbg !1841

if.end151:                                        ; preds = %if.end150, %land.lhs.true141, %if.then137
  br label %if.end152, !dbg !1842

if.end152:                                        ; preds = %if.end151, %if.end133
  %112 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1843
  %todo153 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %112, i32 0, i32 21, !dbg !1845
  %113 = load i32, i32* %todo153, align 8, !dbg !1845
  %and154 = and i32 %113, 32, !dbg !1846
  %tobool155 = icmp ne i32 %and154, 0, !dbg !1846
  br i1 %tobool155, label %if.then156, label %if.end168, !dbg !1847

if.then156:                                       ; preds = %if.end152
  call void @llvm.dbg.declare(metadata i32* %r2157, metadata !1848, metadata !399), !dbg !1850
  %114 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1851
  %archive158 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %114, i32 0, i32 0, !dbg !1852
  %115 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1853
  %fd159 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %115, i32 0, i32 24, !dbg !1854
  %116 = load i32, i32* %fd159, align 4, !dbg !1854
  %117 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1855
  %entry160 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %117, i32 0, i32 18, !dbg !1856
  %118 = load %struct.archive_entry*, %struct.archive_entry** %entry160, align 8, !dbg !1856
  %call161 = call i8* @archive_entry_pathname(%struct.archive_entry* %118), !dbg !1857
  %119 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1858
  %entry162 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %119, i32 0, i32 18, !dbg !1859
  %120 = load %struct.archive_entry*, %struct.archive_entry** %entry162, align 8, !dbg !1859
  %call163 = call %struct.archive_acl* @archive_entry_acl(%struct.archive_entry* %120), !dbg !1860
  %call164 = call i32 @archive_write_disk_set_acls(%struct.archive* %archive158, i32 %116, i8* %call161, %struct.archive_acl* %call163), !dbg !1861
  store i32 %call164, i32* %r2157, align 4, !dbg !1862
  %121 = load i32, i32* %r2157, align 4, !dbg !1863
  %122 = load i32, i32* %ret, align 4, !dbg !1865
  %cmp165 = icmp slt i32 %121, %122, !dbg !1866
  br i1 %cmp165, label %if.then166, label %if.end167, !dbg !1867

if.then166:                                       ; preds = %if.then156
  %123 = load i32, i32* %r2157, align 4, !dbg !1868
  store i32 %123, i32* %ret, align 4, !dbg !1870
  br label %if.end167, !dbg !1871

if.end167:                                        ; preds = %if.then166, %if.then156
  br label %if.end168, !dbg !1872

if.end168:                                        ; preds = %if.end167, %if.end152
  br label %finish_metadata, !dbg !1873

finish_metadata:                                  ; preds = %if.end168, %if.then56
  %124 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1875
  %fd169 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %124, i32 0, i32 24, !dbg !1877
  %125 = load i32, i32* %fd169, align 4, !dbg !1877
  %cmp170 = icmp sge i32 %125, 0, !dbg !1878
  br i1 %cmp170, label %if.then171, label %if.end175, !dbg !1879

if.then171:                                       ; preds = %finish_metadata
  %126 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1880
  %fd172 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %126, i32 0, i32 24, !dbg !1882
  %127 = load i32, i32* %fd172, align 4, !dbg !1882
  %call173 = call i32 @close(i32 %127), !dbg !1883
  %128 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1884
  %fd174 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %128, i32 0, i32 24, !dbg !1885
  store i32 -1, i32* %fd174, align 4, !dbg !1886
  br label %if.end175, !dbg !1887

if.end175:                                        ; preds = %if.then171, %finish_metadata
  %129 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1888
  %entry176 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %129, i32 0, i32 18, !dbg !1890
  %130 = load %struct.archive_entry*, %struct.archive_entry** %entry176, align 8, !dbg !1890
  %tobool177 = icmp ne %struct.archive_entry* %130, null, !dbg !1888
  br i1 %tobool177, label %if.then178, label %if.end181, !dbg !1891

if.then178:                                       ; preds = %if.end175
  %131 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1892
  %entry179 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %131, i32 0, i32 18, !dbg !1894
  %132 = load %struct.archive_entry*, %struct.archive_entry** %entry179, align 8, !dbg !1894
  call void @archive_entry_free(%struct.archive_entry* %132), !dbg !1895
  %133 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1896
  %entry180 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %133, i32 0, i32 18, !dbg !1897
  store %struct.archive_entry* null, %struct.archive_entry** %entry180, align 8, !dbg !1898
  br label %if.end181, !dbg !1899

if.end181:                                        ; preds = %if.then178, %if.end175
  %134 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1900
  %archive182 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %134, i32 0, i32 0, !dbg !1901
  %state183 = getelementptr inbounds %struct.archive, %struct.archive* %archive182, i32 0, i32 1, !dbg !1902
  store i32 2, i32* %state183, align 4, !dbg !1903
  %135 = load i32, i32* %ret, align 4, !dbg !1904
  store i32 %135, i32* %retval, align 4, !dbg !1905
  br label %return, !dbg !1905

return:                                           ; preds = %if.end181, %if.then42, %if.then35, %if.then26, %if.then20, %if.then2, %if.then
  %136 = load i32, i32* %retval, align 4, !dbg !1906
  ret i32 %136, !dbg !1906
}

; Function Attrs: nounwind uwtable
define internal i64 @_archive_write_disk_data(%struct.archive* %_a, i8* %buff, i64 %size) #0 !dbg !385 {
entry:
  %retval = alloca i64, align 8
  %_a.addr = alloca %struct.archive*, align 8
  %buff.addr = alloca i8*, align 8
  %size.addr = alloca i64, align 8
  %a = alloca %struct.archive_write_disk*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !1907, metadata !399), !dbg !1908
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !1909, metadata !399), !dbg !1910
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !1911, metadata !399), !dbg !1912
  call void @llvm.dbg.declare(metadata %struct.archive_write_disk** %a, metadata !1913, metadata !399), !dbg !1914
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1915
  %1 = bitcast %struct.archive* %0 to %struct.archive_write_disk*, !dbg !1916
  store %struct.archive_write_disk* %1, %struct.archive_write_disk** %a, align 8, !dbg !1914
  br label %do.body, !dbg !1917

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !1918, metadata !399), !dbg !1920
  %2 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1921
  %archive = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %2, i32 0, i32 0, !dbg !1921
  %call = call i32 @__archive_check_magic(%struct.archive* %archive, i32 -1073631035, i32 4, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.50, i32 0, i32 0)), !dbg !1921
  store i32 %call, i32* %magic_test, align 4, !dbg !1921
  %3 = load i32, i32* %magic_test, align 4, !dbg !1921
  %cmp = icmp eq i32 %3, -30, !dbg !1921
  br i1 %cmp, label %if.then, label %if.end, !dbg !1921

if.then:                                          ; preds = %do.body
  store i64 -30, i64* %retval, align 8, !dbg !1923
  br label %return, !dbg !1923

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !1926

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1928
  %todo = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %4, i32 0, i32 21, !dbg !1930
  %5 = load i32, i32* %todo, align 8, !dbg !1930
  %and = and i32 %5, 32768, !dbg !1931
  %tobool = icmp ne i32 %and, 0, !dbg !1931
  br i1 %tobool, label %if.then1, label %if.end3, !dbg !1932

if.then1:                                         ; preds = %do.end
  %6 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1933
  %7 = load i8*, i8** %buff.addr, align 8, !dbg !1934
  %8 = load i64, i64* %size.addr, align 8, !dbg !1935
  %call2 = call i64 @hfs_write_data_block(%struct.archive_write_disk* %6, i8* %7, i64 %8), !dbg !1936
  store i64 %call2, i64* %retval, align 8, !dbg !1937
  br label %return, !dbg !1937

if.end3:                                          ; preds = %do.end
  %9 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1938
  %10 = load i8*, i8** %buff.addr, align 8, !dbg !1939
  %11 = load i64, i64* %size.addr, align 8, !dbg !1940
  %call4 = call i64 @write_data_block(%struct.archive_write_disk* %9, i8* %10, i64 %11), !dbg !1941
  store i64 %call4, i64* %retval, align 8, !dbg !1942
  br label %return, !dbg !1942

return:                                           ; preds = %if.end3, %if.then1, %if.then
  %12 = load i64, i64* %retval, align 8, !dbg !1943
  ret i64 %12, !dbg !1943
}

; Function Attrs: nounwind uwtable
define internal i64 @_archive_write_disk_data_block(%struct.archive* %_a, i8* %buff, i64 %size, i64 %offset) #0 !dbg !390 {
entry:
  %retval = alloca i64, align 8
  %_a.addr = alloca %struct.archive*, align 8
  %buff.addr = alloca i8*, align 8
  %size.addr = alloca i64, align 8
  %offset.addr = alloca i64, align 8
  %a = alloca %struct.archive_write_disk*, align 8
  %r = alloca i64, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !1944, metadata !399), !dbg !1945
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !1946, metadata !399), !dbg !1947
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !1948, metadata !399), !dbg !1949
  store i64 %offset, i64* %offset.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %offset.addr, metadata !1950, metadata !399), !dbg !1951
  call void @llvm.dbg.declare(metadata %struct.archive_write_disk** %a, metadata !1952, metadata !399), !dbg !1953
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !1954
  %1 = bitcast %struct.archive* %0 to %struct.archive_write_disk*, !dbg !1955
  store %struct.archive_write_disk* %1, %struct.archive_write_disk** %a, align 8, !dbg !1953
  call void @llvm.dbg.declare(metadata i64* %r, metadata !1956, metadata !399), !dbg !1957
  br label %do.body, !dbg !1958

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !1959, metadata !399), !dbg !1961
  %2 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1962
  %archive = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %2, i32 0, i32 0, !dbg !1962
  %call = call i32 @__archive_check_magic(%struct.archive* %archive, i32 -1073631035, i32 4, i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.53, i32 0, i32 0)), !dbg !1962
  store i32 %call, i32* %magic_test, align 4, !dbg !1962
  %3 = load i32, i32* %magic_test, align 4, !dbg !1962
  %cmp = icmp eq i32 %3, -30, !dbg !1962
  br i1 %cmp, label %if.then, label %if.end, !dbg !1962

if.then:                                          ; preds = %do.body
  store i64 -30, i64* %retval, align 8, !dbg !1964
  br label %return, !dbg !1964

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !1967

do.end:                                           ; preds = %if.end
  %4 = load i64, i64* %offset.addr, align 8, !dbg !1969
  %5 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1970
  %offset1 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %5, i32 0, i32 25, !dbg !1971
  store i64 %4, i64* %offset1, align 8, !dbg !1972
  %6 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1973
  %todo = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %6, i32 0, i32 21, !dbg !1975
  %7 = load i32, i32* %todo, align 8, !dbg !1975
  %and = and i32 %7, 32768, !dbg !1976
  %tobool = icmp ne i32 %and, 0, !dbg !1976
  br i1 %tobool, label %if.then2, label %if.else, !dbg !1977

if.then2:                                         ; preds = %do.end
  %8 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1978
  %9 = load i8*, i8** %buff.addr, align 8, !dbg !1979
  %10 = load i64, i64* %size.addr, align 8, !dbg !1980
  %call3 = call i64 @hfs_write_data_block(%struct.archive_write_disk* %8, i8* %9, i64 %10), !dbg !1981
  store i64 %call3, i64* %r, align 8, !dbg !1982
  br label %if.end5, !dbg !1983

if.else:                                          ; preds = %do.end
  %11 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !1984
  %12 = load i8*, i8** %buff.addr, align 8, !dbg !1985
  %13 = load i64, i64* %size.addr, align 8, !dbg !1986
  %call4 = call i64 @write_data_block(%struct.archive_write_disk* %11, i8* %12, i64 %13), !dbg !1987
  store i64 %call4, i64* %r, align 8, !dbg !1988
  br label %if.end5

if.end5:                                          ; preds = %if.else, %if.then2
  %14 = load i64, i64* %r, align 8, !dbg !1989
  %cmp6 = icmp slt i64 %14, 0, !dbg !1991
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !1992

if.then7:                                         ; preds = %if.end5
  %15 = load i64, i64* %r, align 8, !dbg !1993
  store i64 %15, i64* %retval, align 8, !dbg !1994
  br label %return, !dbg !1994

if.end8:                                          ; preds = %if.end5
  %16 = load i64, i64* %r, align 8, !dbg !1995
  %17 = load i64, i64* %size.addr, align 8, !dbg !1997
  %cmp9 = icmp ult i64 %16, %17, !dbg !1998
  br i1 %cmp9, label %if.then10, label %if.end12, !dbg !1999

if.then10:                                        ; preds = %if.end8
  %18 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !2000
  %archive11 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %18, i32 0, i32 0, !dbg !2002
  %19 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a, align 8, !dbg !2003
  %filesize = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %19, i32 0, i32 28, !dbg !2004
  %20 = load i64, i64* %filesize, align 8, !dbg !2004
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive11, i32 0, i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.54, i32 0, i32 0), i64 %20), !dbg !2005
  store i64 -20, i64* %retval, align 8, !dbg !2006
  br label %return, !dbg !2006

if.end12:                                         ; preds = %if.end8
  store i64 0, i64* %retval, align 8, !dbg !2007
  br label %return, !dbg !2007

return:                                           ; preds = %if.end12, %if.then10, %if.then7, %if.then
  %21 = load i64, i64* %retval, align 8, !dbg !2008
  ret i64 %21, !dbg !2008
}

; Function Attrs: nounwind uwtable
define internal %struct.fixup_entry* @sort_dir_list(%struct.fixup_entry* %p) #0 !dbg !325 {
entry:
  %retval = alloca %struct.fixup_entry*, align 8
  %p.addr = alloca %struct.fixup_entry*, align 8
  %a = alloca %struct.fixup_entry*, align 8
  %b = alloca %struct.fixup_entry*, align 8
  %t = alloca %struct.fixup_entry*, align 8
  store %struct.fixup_entry* %p, %struct.fixup_entry** %p.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.fixup_entry** %p.addr, metadata !2009, metadata !399), !dbg !2010
  call void @llvm.dbg.declare(metadata %struct.fixup_entry** %a, metadata !2011, metadata !399), !dbg !2012
  call void @llvm.dbg.declare(metadata %struct.fixup_entry** %b, metadata !2013, metadata !399), !dbg !2014
  call void @llvm.dbg.declare(metadata %struct.fixup_entry** %t, metadata !2015, metadata !399), !dbg !2016
  %0 = load %struct.fixup_entry*, %struct.fixup_entry** %p.addr, align 8, !dbg !2017
  %cmp = icmp eq %struct.fixup_entry* %0, null, !dbg !2019
  br i1 %cmp, label %if.then, label %if.end, !dbg !2020

if.then:                                          ; preds = %entry
  store %struct.fixup_entry* null, %struct.fixup_entry** %retval, align 8, !dbg !2021
  br label %return, !dbg !2021

if.end:                                           ; preds = %entry
  %1 = load %struct.fixup_entry*, %struct.fixup_entry** %p.addr, align 8, !dbg !2022
  %next = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %1, i32 0, i32 0, !dbg !2024
  %2 = load %struct.fixup_entry*, %struct.fixup_entry** %next, align 8, !dbg !2024
  %cmp1 = icmp eq %struct.fixup_entry* %2, null, !dbg !2025
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !2026

if.then2:                                         ; preds = %if.end
  %3 = load %struct.fixup_entry*, %struct.fixup_entry** %p.addr, align 8, !dbg !2027
  store %struct.fixup_entry* %3, %struct.fixup_entry** %retval, align 8, !dbg !2028
  br label %return, !dbg !2028

if.end3:                                          ; preds = %if.end
  %4 = load %struct.fixup_entry*, %struct.fixup_entry** %p.addr, align 8, !dbg !2029
  store %struct.fixup_entry* %4, %struct.fixup_entry** %t, align 8, !dbg !2030
  %5 = load %struct.fixup_entry*, %struct.fixup_entry** %p.addr, align 8, !dbg !2031
  %next4 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %5, i32 0, i32 0, !dbg !2032
  %6 = load %struct.fixup_entry*, %struct.fixup_entry** %next4, align 8, !dbg !2032
  %next5 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %6, i32 0, i32 0, !dbg !2033
  %7 = load %struct.fixup_entry*, %struct.fixup_entry** %next5, align 8, !dbg !2033
  store %struct.fixup_entry* %7, %struct.fixup_entry** %a, align 8, !dbg !2034
  br label %while.cond, !dbg !2035

while.cond:                                       ; preds = %if.end11, %if.end3
  %8 = load %struct.fixup_entry*, %struct.fixup_entry** %a, align 8, !dbg !2036
  %cmp6 = icmp ne %struct.fixup_entry* %8, null, !dbg !2038
  br i1 %cmp6, label %while.body, label %while.end, !dbg !2039

while.body:                                       ; preds = %while.cond
  %9 = load %struct.fixup_entry*, %struct.fixup_entry** %a, align 8, !dbg !2040
  %next7 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %9, i32 0, i32 0, !dbg !2042
  %10 = load %struct.fixup_entry*, %struct.fixup_entry** %next7, align 8, !dbg !2042
  store %struct.fixup_entry* %10, %struct.fixup_entry** %a, align 8, !dbg !2043
  %11 = load %struct.fixup_entry*, %struct.fixup_entry** %a, align 8, !dbg !2044
  %cmp8 = icmp ne %struct.fixup_entry* %11, null, !dbg !2046
  br i1 %cmp8, label %if.then9, label %if.end11, !dbg !2047

if.then9:                                         ; preds = %while.body
  %12 = load %struct.fixup_entry*, %struct.fixup_entry** %a, align 8, !dbg !2048
  %next10 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %12, i32 0, i32 0, !dbg !2049
  %13 = load %struct.fixup_entry*, %struct.fixup_entry** %next10, align 8, !dbg !2049
  store %struct.fixup_entry* %13, %struct.fixup_entry** %a, align 8, !dbg !2050
  br label %if.end11, !dbg !2051

if.end11:                                         ; preds = %if.then9, %while.body
  %14 = load %struct.fixup_entry*, %struct.fixup_entry** %t, align 8, !dbg !2052
  %next12 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %14, i32 0, i32 0, !dbg !2053
  %15 = load %struct.fixup_entry*, %struct.fixup_entry** %next12, align 8, !dbg !2053
  store %struct.fixup_entry* %15, %struct.fixup_entry** %t, align 8, !dbg !2054
  br label %while.cond, !dbg !2055

while.end:                                        ; preds = %while.cond
  %16 = load %struct.fixup_entry*, %struct.fixup_entry** %t, align 8, !dbg !2057
  %next13 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %16, i32 0, i32 0, !dbg !2058
  %17 = load %struct.fixup_entry*, %struct.fixup_entry** %next13, align 8, !dbg !2058
  store %struct.fixup_entry* %17, %struct.fixup_entry** %b, align 8, !dbg !2059
  %18 = load %struct.fixup_entry*, %struct.fixup_entry** %t, align 8, !dbg !2060
  %next14 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %18, i32 0, i32 0, !dbg !2061
  store %struct.fixup_entry* null, %struct.fixup_entry** %next14, align 8, !dbg !2062
  %19 = load %struct.fixup_entry*, %struct.fixup_entry** %p.addr, align 8, !dbg !2063
  store %struct.fixup_entry* %19, %struct.fixup_entry** %a, align 8, !dbg !2064
  %20 = load %struct.fixup_entry*, %struct.fixup_entry** %a, align 8, !dbg !2065
  %call = call %struct.fixup_entry* @sort_dir_list(%struct.fixup_entry* %20), !dbg !2066
  store %struct.fixup_entry* %call, %struct.fixup_entry** %a, align 8, !dbg !2067
  %21 = load %struct.fixup_entry*, %struct.fixup_entry** %b, align 8, !dbg !2068
  %call15 = call %struct.fixup_entry* @sort_dir_list(%struct.fixup_entry* %21), !dbg !2069
  store %struct.fixup_entry* %call15, %struct.fixup_entry** %b, align 8, !dbg !2070
  %22 = load %struct.fixup_entry*, %struct.fixup_entry** %a, align 8, !dbg !2071
  %name = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %22, i32 0, i32 15, !dbg !2073
  %23 = load i8*, i8** %name, align 8, !dbg !2073
  %24 = load %struct.fixup_entry*, %struct.fixup_entry** %b, align 8, !dbg !2074
  %name16 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %24, i32 0, i32 15, !dbg !2075
  %25 = load i8*, i8** %name16, align 8, !dbg !2075
  %call17 = call i32 @strcmp(i8* %23, i8* %25) #8, !dbg !2076
  %cmp18 = icmp sgt i32 %call17, 0, !dbg !2077
  br i1 %cmp18, label %if.then19, label %if.else, !dbg !2078

if.then19:                                        ; preds = %while.end
  %26 = load %struct.fixup_entry*, %struct.fixup_entry** %a, align 8, !dbg !2079
  store %struct.fixup_entry* %26, %struct.fixup_entry** %p.addr, align 8, !dbg !2081
  store %struct.fixup_entry* %26, %struct.fixup_entry** %t, align 8, !dbg !2082
  %27 = load %struct.fixup_entry*, %struct.fixup_entry** %a, align 8, !dbg !2083
  %next20 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %27, i32 0, i32 0, !dbg !2084
  %28 = load %struct.fixup_entry*, %struct.fixup_entry** %next20, align 8, !dbg !2084
  store %struct.fixup_entry* %28, %struct.fixup_entry** %a, align 8, !dbg !2085
  br label %if.end22, !dbg !2086

if.else:                                          ; preds = %while.end
  %29 = load %struct.fixup_entry*, %struct.fixup_entry** %b, align 8, !dbg !2087
  store %struct.fixup_entry* %29, %struct.fixup_entry** %p.addr, align 8, !dbg !2089
  store %struct.fixup_entry* %29, %struct.fixup_entry** %t, align 8, !dbg !2090
  %30 = load %struct.fixup_entry*, %struct.fixup_entry** %b, align 8, !dbg !2091
  %next21 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %30, i32 0, i32 0, !dbg !2092
  %31 = load %struct.fixup_entry*, %struct.fixup_entry** %next21, align 8, !dbg !2092
  store %struct.fixup_entry* %31, %struct.fixup_entry** %b, align 8, !dbg !2093
  br label %if.end22

if.end22:                                         ; preds = %if.else, %if.then19
  br label %while.cond23, !dbg !2094

while.cond23:                                     ; preds = %if.end37, %if.end22
  %32 = load %struct.fixup_entry*, %struct.fixup_entry** %a, align 8, !dbg !2095
  %cmp24 = icmp ne %struct.fixup_entry* %32, null, !dbg !2096
  br i1 %cmp24, label %land.rhs, label %land.end, !dbg !2097

land.rhs:                                         ; preds = %while.cond23
  %33 = load %struct.fixup_entry*, %struct.fixup_entry** %b, align 8, !dbg !2098
  %cmp25 = icmp ne %struct.fixup_entry* %33, null, !dbg !2099
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond23
  %34 = phi i1 [ false, %while.cond23 ], [ %cmp25, %land.rhs ]
  br i1 %34, label %while.body26, label %while.end39, !dbg !2100

while.body26:                                     ; preds = %land.end
  %35 = load %struct.fixup_entry*, %struct.fixup_entry** %a, align 8, !dbg !2102
  %name27 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %35, i32 0, i32 15, !dbg !2105
  %36 = load i8*, i8** %name27, align 8, !dbg !2105
  %37 = load %struct.fixup_entry*, %struct.fixup_entry** %b, align 8, !dbg !2106
  %name28 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %37, i32 0, i32 15, !dbg !2107
  %38 = load i8*, i8** %name28, align 8, !dbg !2107
  %call29 = call i32 @strcmp(i8* %36, i8* %38) #8, !dbg !2108
  %cmp30 = icmp sgt i32 %call29, 0, !dbg !2109
  br i1 %cmp30, label %if.then31, label %if.else34, !dbg !2110

if.then31:                                        ; preds = %while.body26
  %39 = load %struct.fixup_entry*, %struct.fixup_entry** %a, align 8, !dbg !2111
  %40 = load %struct.fixup_entry*, %struct.fixup_entry** %t, align 8, !dbg !2113
  %next32 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %40, i32 0, i32 0, !dbg !2114
  store %struct.fixup_entry* %39, %struct.fixup_entry** %next32, align 8, !dbg !2115
  %41 = load %struct.fixup_entry*, %struct.fixup_entry** %a, align 8, !dbg !2116
  %next33 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %41, i32 0, i32 0, !dbg !2117
  %42 = load %struct.fixup_entry*, %struct.fixup_entry** %next33, align 8, !dbg !2117
  store %struct.fixup_entry* %42, %struct.fixup_entry** %a, align 8, !dbg !2118
  br label %if.end37, !dbg !2119

if.else34:                                        ; preds = %while.body26
  %43 = load %struct.fixup_entry*, %struct.fixup_entry** %b, align 8, !dbg !2120
  %44 = load %struct.fixup_entry*, %struct.fixup_entry** %t, align 8, !dbg !2122
  %next35 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %44, i32 0, i32 0, !dbg !2123
  store %struct.fixup_entry* %43, %struct.fixup_entry** %next35, align 8, !dbg !2124
  %45 = load %struct.fixup_entry*, %struct.fixup_entry** %b, align 8, !dbg !2125
  %next36 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %45, i32 0, i32 0, !dbg !2126
  %46 = load %struct.fixup_entry*, %struct.fixup_entry** %next36, align 8, !dbg !2126
  store %struct.fixup_entry* %46, %struct.fixup_entry** %b, align 8, !dbg !2127
  br label %if.end37

if.end37:                                         ; preds = %if.else34, %if.then31
  %47 = load %struct.fixup_entry*, %struct.fixup_entry** %t, align 8, !dbg !2128
  %next38 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %47, i32 0, i32 0, !dbg !2129
  %48 = load %struct.fixup_entry*, %struct.fixup_entry** %next38, align 8, !dbg !2129
  store %struct.fixup_entry* %48, %struct.fixup_entry** %t, align 8, !dbg !2130
  br label %while.cond23, !dbg !2131

while.end39:                                      ; preds = %land.end
  %49 = load %struct.fixup_entry*, %struct.fixup_entry** %a, align 8, !dbg !2133
  %cmp40 = icmp ne %struct.fixup_entry* %49, null, !dbg !2135
  br i1 %cmp40, label %if.then41, label %if.end43, !dbg !2136

if.then41:                                        ; preds = %while.end39
  %50 = load %struct.fixup_entry*, %struct.fixup_entry** %a, align 8, !dbg !2137
  %51 = load %struct.fixup_entry*, %struct.fixup_entry** %t, align 8, !dbg !2138
  %next42 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %51, i32 0, i32 0, !dbg !2139
  store %struct.fixup_entry* %50, %struct.fixup_entry** %next42, align 8, !dbg !2140
  br label %if.end43, !dbg !2138

if.end43:                                         ; preds = %if.then41, %while.end39
  %52 = load %struct.fixup_entry*, %struct.fixup_entry** %b, align 8, !dbg !2141
  %cmp44 = icmp ne %struct.fixup_entry* %52, null, !dbg !2143
  br i1 %cmp44, label %if.then45, label %if.end47, !dbg !2144

if.then45:                                        ; preds = %if.end43
  %53 = load %struct.fixup_entry*, %struct.fixup_entry** %b, align 8, !dbg !2145
  %54 = load %struct.fixup_entry*, %struct.fixup_entry** %t, align 8, !dbg !2146
  %next46 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %54, i32 0, i32 0, !dbg !2147
  store %struct.fixup_entry* %53, %struct.fixup_entry** %next46, align 8, !dbg !2148
  br label %if.end47, !dbg !2146

if.end47:                                         ; preds = %if.then45, %if.end43
  %55 = load %struct.fixup_entry*, %struct.fixup_entry** %p.addr, align 8, !dbg !2149
  store %struct.fixup_entry* %55, %struct.fixup_entry** %retval, align 8, !dbg !2150
  br label %return, !dbg !2150

return:                                           ; preds = %if.end47, %if.then2, %if.then
  %56 = load %struct.fixup_entry*, %struct.fixup_entry** %retval, align 8, !dbg !2151
  ret %struct.fixup_entry* %56, !dbg !2151
}

; Function Attrs: nounwind uwtable
define internal i32 @set_times(%struct.archive_write_disk* %a, i32 %fd, i32 %mode, i8* %name, i64 %atime, i64 %atime_nanos, i64 %birthtime, i64 %birthtime_nanos, i64 %mtime, i64 %mtime_nanos, i64 %cctime, i64 %ctime_nanos) #0 !dbg !328 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write_disk*, align 8
  %fd.addr = alloca i32, align 4
  %mode.addr = alloca i32, align 4
  %name.addr = alloca i8*, align 8
  %atime.addr = alloca i64, align 8
  %atime_nanos.addr = alloca i64, align 8
  %birthtime.addr = alloca i64, align 8
  %birthtime_nanos.addr = alloca i64, align 8
  %mtime.addr = alloca i64, align 8
  %mtime_nanos.addr = alloca i64, align 8
  %cctime.addr = alloca i64, align 8
  %ctime_nanos.addr = alloca i64, align 8
  %r1 = alloca i32, align 4
  %r2 = alloca i32, align 4
  store %struct.archive_write_disk* %a, %struct.archive_write_disk** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_disk** %a.addr, metadata !2152, metadata !399), !dbg !2153
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !2154, metadata !399), !dbg !2155
  store i32 %mode, i32* %mode.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %mode.addr, metadata !2156, metadata !399), !dbg !2157
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !2158, metadata !399), !dbg !2159
  store i64 %atime, i64* %atime.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %atime.addr, metadata !2160, metadata !399), !dbg !2161
  store i64 %atime_nanos, i64* %atime_nanos.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %atime_nanos.addr, metadata !2162, metadata !399), !dbg !2163
  store i64 %birthtime, i64* %birthtime.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %birthtime.addr, metadata !2164, metadata !399), !dbg !2165
  store i64 %birthtime_nanos, i64* %birthtime_nanos.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %birthtime_nanos.addr, metadata !2166, metadata !399), !dbg !2167
  store i64 %mtime, i64* %mtime.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %mtime.addr, metadata !2168, metadata !399), !dbg !2169
  store i64 %mtime_nanos, i64* %mtime_nanos.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %mtime_nanos.addr, metadata !2170, metadata !399), !dbg !2171
  store i64 %cctime, i64* %cctime.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %cctime.addr, metadata !2172, metadata !399), !dbg !2173
  store i64 %ctime_nanos, i64* %ctime_nanos.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %ctime_nanos.addr, metadata !2174, metadata !399), !dbg !2175
  call void @llvm.dbg.declare(metadata i32* %r1, metadata !2176, metadata !399), !dbg !2177
  store i32 0, i32* %r1, align 4, !dbg !2177
  call void @llvm.dbg.declare(metadata i32* %r2, metadata !2178, metadata !399), !dbg !2179
  store i32 0, i32* %r2, align 4, !dbg !2179
  %0 = load i64, i64* %cctime.addr, align 8, !dbg !2180
  %1 = load i64, i64* %ctime_nanos.addr, align 8, !dbg !2181
  %2 = load i64, i64* %birthtime.addr, align 8, !dbg !2182
  %3 = load i64, i64* %birthtime_nanos.addr, align 8, !dbg !2183
  %4 = load i32, i32* %fd.addr, align 4, !dbg !2184
  %5 = load i32, i32* %mode.addr, align 4, !dbg !2185
  %6 = load i8*, i8** %name.addr, align 8, !dbg !2186
  %7 = load i64, i64* %atime.addr, align 8, !dbg !2187
  %8 = load i64, i64* %atime_nanos.addr, align 8, !dbg !2188
  %9 = load i64, i64* %mtime.addr, align 8, !dbg !2189
  %10 = load i64, i64* %mtime_nanos.addr, align 8, !dbg !2190
  %call = call i32 @set_time(i32 %4, i32 %5, i8* %6, i64 %7, i64 %8, i64 %9, i64 %10), !dbg !2191
  store i32 %call, i32* %r2, align 4, !dbg !2192
  %11 = load i32, i32* %r1, align 4, !dbg !2193
  %cmp = icmp ne i32 %11, 0, !dbg !2195
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !2196

lor.lhs.false:                                    ; preds = %entry
  %12 = load i32, i32* %r2, align 4, !dbg !2197
  %cmp1 = icmp ne i32 %12, 0, !dbg !2199
  br i1 %cmp1, label %if.then, label %if.end, !dbg !2200

if.then:                                          ; preds = %lor.lhs.false, %entry
  %13 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2201
  %archive = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %13, i32 0, i32 0, !dbg !2203
  %call2 = call i32* @__errno_location() #1, !dbg !2204
  %14 = load i32, i32* %call2, align 4, !dbg !2204
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 %14, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.6, i32 0, i32 0)), !dbg !2205
  store i32 -20, i32* %retval, align 4, !dbg !2207
  br label %return, !dbg !2207

if.end:                                           ; preds = %lor.lhs.false
  store i32 0, i32* %retval, align 4, !dbg !2208
  br label %return, !dbg !2208

return:                                           ; preds = %if.end, %if.then
  %15 = load i32, i32* %retval, align 4, !dbg !2209
  ret i32 %15, !dbg !2209
}

; Function Attrs: nounwind
declare i32 @chmod(i8*, i32) #3

declare i32 @archive_write_disk_set_acls(%struct.archive*, i32, i8*, %struct.archive_acl*) #2

; Function Attrs: nounwind uwtable
define internal i32 @set_fflags_platform(%struct.archive_write_disk* %a, i32 %fd, i8* %name, i32 %mode, i64 %set, i64 %clear) #0 !dbg !334 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write_disk*, align 8
  %fd.addr = alloca i32, align 4
  %name.addr = alloca i8*, align 8
  %mode.addr = alloca i32, align 4
  %set.addr = alloca i64, align 8
  %clear.addr = alloca i64, align 8
  %ret = alloca i32, align 4
  %myfd = alloca i32, align 4
  %newflags = alloca i32, align 4
  %oldflags = alloca i32, align 4
  %sf_mask = alloca i32, align 4
  store %struct.archive_write_disk* %a, %struct.archive_write_disk** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_disk** %a.addr, metadata !2210, metadata !399), !dbg !2211
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !2212, metadata !399), !dbg !2213
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !2214, metadata !399), !dbg !2215
  store i32 %mode, i32* %mode.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %mode.addr, metadata !2216, metadata !399), !dbg !2217
  store i64 %set, i64* %set.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %set.addr, metadata !2218, metadata !399), !dbg !2219
  store i64 %clear, i64* %clear.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %clear.addr, metadata !2220, metadata !399), !dbg !2221
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !2222, metadata !399), !dbg !2223
  call void @llvm.dbg.declare(metadata i32* %myfd, metadata !2224, metadata !399), !dbg !2225
  %0 = load i32, i32* %fd.addr, align 4, !dbg !2226
  store i32 %0, i32* %myfd, align 4, !dbg !2225
  call void @llvm.dbg.declare(metadata i32* %newflags, metadata !2227, metadata !399), !dbg !2228
  call void @llvm.dbg.declare(metadata i32* %oldflags, metadata !2229, metadata !399), !dbg !2230
  call void @llvm.dbg.declare(metadata i32* %sf_mask, metadata !2231, metadata !399), !dbg !2232
  store i32 0, i32* %sf_mask, align 4, !dbg !2232
  %1 = load i64, i64* %set.addr, align 8, !dbg !2233
  %cmp = icmp eq i64 %1, 0, !dbg !2235
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !2236

land.lhs.true:                                    ; preds = %entry
  %2 = load i64, i64* %clear.addr, align 8, !dbg !2237
  %cmp1 = icmp eq i64 %2, 0, !dbg !2239
  br i1 %cmp1, label %if.then, label %if.end, !dbg !2240

if.then:                                          ; preds = %land.lhs.true
  store i32 0, i32* %retval, align 4, !dbg !2241
  br label %return, !dbg !2241

if.end:                                           ; preds = %land.lhs.true, %entry
  %3 = load i32, i32* %mode.addr, align 4, !dbg !2242
  %and = and i32 %3, 61440, !dbg !2242
  %cmp2 = icmp eq i32 %and, 32768, !dbg !2242
  br i1 %cmp2, label %if.end7, label %land.lhs.true3, !dbg !2244

land.lhs.true3:                                   ; preds = %if.end
  %4 = load i32, i32* %mode.addr, align 4, !dbg !2245
  %and4 = and i32 %4, 61440, !dbg !2245
  %cmp5 = icmp eq i32 %and4, 16384, !dbg !2245
  br i1 %cmp5, label %if.end7, label %if.then6, !dbg !2247

if.then6:                                         ; preds = %land.lhs.true3
  store i32 0, i32* %retval, align 4, !dbg !2248
  br label %return, !dbg !2248

if.end7:                                          ; preds = %land.lhs.true3, %if.end
  %5 = load i32, i32* %myfd, align 4, !dbg !2249
  %cmp8 = icmp slt i32 %5, 0, !dbg !2251
  br i1 %cmp8, label %if.then9, label %if.end10, !dbg !2252

if.then9:                                         ; preds = %if.end7
  %6 = load i8*, i8** %name.addr, align 8, !dbg !2253
  %call = call i32 (i8*, i32, ...) @open(i8* %6, i32 526336), !dbg !2255
  store i32 %call, i32* %myfd, align 4, !dbg !2256
  %7 = load i32, i32* %myfd, align 4, !dbg !2257
  call void @__archive_ensure_cloexec_flag(i32 %7), !dbg !2258
  br label %if.end10, !dbg !2259

if.end10:                                         ; preds = %if.then9, %if.end7
  %8 = load i32, i32* %myfd, align 4, !dbg !2260
  %cmp11 = icmp slt i32 %8, 0, !dbg !2262
  br i1 %cmp11, label %if.then12, label %if.end13, !dbg !2263

if.then12:                                        ; preds = %if.end10
  store i32 0, i32* %retval, align 4, !dbg !2264
  br label %return, !dbg !2264

if.end13:                                         ; preds = %if.end10
  %9 = load i32, i32* %sf_mask, align 4, !dbg !2265
  %or = or i32 %9, 16, !dbg !2265
  store i32 %or, i32* %sf_mask, align 4, !dbg !2265
  %10 = load i32, i32* %sf_mask, align 4, !dbg !2266
  %or14 = or i32 %10, 32, !dbg !2266
  store i32 %or14, i32* %sf_mask, align 4, !dbg !2266
  %11 = load i32, i32* %sf_mask, align 4, !dbg !2267
  %or15 = or i32 %11, 16384, !dbg !2267
  store i32 %or15, i32* %sf_mask, align 4, !dbg !2267
  store i32 0, i32* %ret, align 4, !dbg !2268
  %12 = load i32, i32* %myfd, align 4, !dbg !2269
  %call16 = call i32 (i32, i64, ...) @ioctl(i32 %12, i64 2148034049, i32* %oldflags) #7, !dbg !2271
  %cmp17 = icmp slt i32 %call16, 0, !dbg !2272
  br i1 %cmp17, label %if.then18, label %if.end19, !dbg !2273

if.then18:                                        ; preds = %if.end13
  br label %fail, !dbg !2274

if.end19:                                         ; preds = %if.end13
  %13 = load i32, i32* %oldflags, align 4, !dbg !2275
  %conv = sext i32 %13 to i64, !dbg !2275
  %14 = load i64, i64* %clear.addr, align 8, !dbg !2276
  %neg = xor i64 %14, -1, !dbg !2277
  %and20 = and i64 %conv, %neg, !dbg !2278
  %15 = load i64, i64* %set.addr, align 8, !dbg !2279
  %or21 = or i64 %and20, %15, !dbg !2280
  %conv22 = trunc i64 %or21 to i32, !dbg !2281
  store i32 %conv22, i32* %newflags, align 4, !dbg !2282
  %16 = load i32, i32* %myfd, align 4, !dbg !2283
  %call23 = call i32 (i32, i64, ...) @ioctl(i32 %16, i64 1074292226, i32* %newflags) #7, !dbg !2285
  %cmp24 = icmp sge i32 %call23, 0, !dbg !2286
  br i1 %cmp24, label %if.then26, label %if.end27, !dbg !2287

if.then26:                                        ; preds = %if.end19
  br label %cleanup, !dbg !2288

if.end27:                                         ; preds = %if.end19
  %call28 = call i32* @__errno_location() #1, !dbg !2289
  %17 = load i32, i32* %call28, align 4, !dbg !2289
  %cmp29 = icmp ne i32 %17, 1, !dbg !2291
  br i1 %cmp29, label %if.then31, label %if.end32, !dbg !2292

if.then31:                                        ; preds = %if.end27
  br label %fail, !dbg !2293

if.end32:                                         ; preds = %if.end27
  %18 = load i32, i32* %sf_mask, align 4, !dbg !2294
  %neg33 = xor i32 %18, -1, !dbg !2295
  %19 = load i32, i32* %newflags, align 4, !dbg !2296
  %and34 = and i32 %19, %neg33, !dbg !2296
  store i32 %and34, i32* %newflags, align 4, !dbg !2296
  %20 = load i32, i32* %sf_mask, align 4, !dbg !2297
  %21 = load i32, i32* %oldflags, align 4, !dbg !2298
  %and35 = and i32 %21, %20, !dbg !2298
  store i32 %and35, i32* %oldflags, align 4, !dbg !2298
  %22 = load i32, i32* %oldflags, align 4, !dbg !2299
  %23 = load i32, i32* %newflags, align 4, !dbg !2300
  %or36 = or i32 %23, %22, !dbg !2300
  store i32 %or36, i32* %newflags, align 4, !dbg !2300
  %24 = load i32, i32* %myfd, align 4, !dbg !2301
  %call37 = call i32 (i32, i64, ...) @ioctl(i32 %24, i64 1074292226, i32* %newflags) #7, !dbg !2303
  %cmp38 = icmp sge i32 %call37, 0, !dbg !2304
  br i1 %cmp38, label %if.then40, label %if.end41, !dbg !2305

if.then40:                                        ; preds = %if.end32
  br label %cleanup, !dbg !2306

if.end41:                                         ; preds = %if.end32
  br label %fail, !dbg !2307

fail:                                             ; preds = %if.end41, %if.then31, %if.then18
  %25 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2309
  %archive = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %25, i32 0, i32 0, !dbg !2310
  %call42 = call i32* @__errno_location() #1, !dbg !2311
  %26 = load i32, i32* %call42, align 4, !dbg !2311
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 %26, i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.7, i32 0, i32 0)), !dbg !2312
  store i32 -20, i32* %ret, align 4, !dbg !2314
  br label %cleanup, !dbg !2315

cleanup:                                          ; preds = %fail, %if.then40, %if.then26
  %27 = load i32, i32* %fd.addr, align 4, !dbg !2316
  %cmp43 = icmp slt i32 %27, 0, !dbg !2318
  br i1 %cmp43, label %if.then45, label %if.end47, !dbg !2319

if.then45:                                        ; preds = %cleanup
  %28 = load i32, i32* %myfd, align 4, !dbg !2320
  %call46 = call i32 @close(i32 %28), !dbg !2321
  br label %if.end47, !dbg !2321

if.end47:                                         ; preds = %if.then45, %cleanup
  %29 = load i32, i32* %ret, align 4, !dbg !2322
  store i32 %29, i32* %retval, align 4, !dbg !2323
  br label %return, !dbg !2323

return:                                           ; preds = %if.end47, %if.then12, %if.then6, %if.then
  %30 = load i32, i32* %retval, align 4, !dbg !2324
  ret i32 %30, !dbg !2324
}

; Function Attrs: nounwind uwtable
define internal i32 @set_mac_metadata(%struct.archive_write_disk* %a, i8* %pathname, i8* %metadata, i64 %metadata_size) #0 !dbg !337 {
entry:
  %a.addr = alloca %struct.archive_write_disk*, align 8
  %pathname.addr = alloca i8*, align 8
  %metadata.addr = alloca i8*, align 8
  %metadata_size.addr = alloca i64, align 8
  store %struct.archive_write_disk* %a, %struct.archive_write_disk** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_disk** %a.addr, metadata !2325, metadata !399), !dbg !2326
  store i8* %pathname, i8** %pathname.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %pathname.addr, metadata !2327, metadata !399), !dbg !2328
  store i8* %metadata, i8** %metadata.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %metadata.addr, metadata !2329, metadata !399), !dbg !2330
  store i64 %metadata_size, i64* %metadata_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %metadata_size.addr, metadata !2331, metadata !399), !dbg !2332
  %0 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2333
  %1 = load i8*, i8** %pathname.addr, align 8, !dbg !2334
  %2 = load i8*, i8** %metadata.addr, align 8, !dbg !2335
  %3 = load i64, i64* %metadata_size.addr, align 8, !dbg !2336
  ret i32 0, !dbg !2337
}

declare void @archive_acl_clear(%struct.archive_acl*) #2

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #4

; Function Attrs: nounwind uwtable
define internal i32 @set_time(i32 %fd, i32 %mode, i8* %name, i64 %atime, i64 %atime_nsec, i64 %mtime, i64 %mtime_nsec) #0 !dbg !331 {
entry:
  %retval = alloca i32, align 4
  %fd.addr = alloca i32, align 4
  %mode.addr = alloca i32, align 4
  %name.addr = alloca i8*, align 8
  %atime.addr = alloca i64, align 8
  %atime_nsec.addr = alloca i64, align 8
  %mtime.addr = alloca i64, align 8
  %mtime_nsec.addr = alloca i64, align 8
  %ts = alloca [2 x %struct.timespec], align 16
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !2338, metadata !399), !dbg !2339
  store i32 %mode, i32* %mode.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %mode.addr, metadata !2340, metadata !399), !dbg !2341
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !2342, metadata !399), !dbg !2343
  store i64 %atime, i64* %atime.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %atime.addr, metadata !2344, metadata !399), !dbg !2345
  store i64 %atime_nsec, i64* %atime_nsec.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %atime_nsec.addr, metadata !2346, metadata !399), !dbg !2347
  store i64 %mtime, i64* %mtime.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %mtime.addr, metadata !2348, metadata !399), !dbg !2349
  store i64 %mtime_nsec, i64* %mtime_nsec.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %mtime_nsec.addr, metadata !2350, metadata !399), !dbg !2351
  call void @llvm.dbg.declare(metadata [2 x %struct.timespec]* %ts, metadata !2352, metadata !399), !dbg !2356
  %0 = load i32, i32* %mode.addr, align 4, !dbg !2357
  %1 = load i64, i64* %atime.addr, align 8, !dbg !2358
  %arrayidx = getelementptr inbounds [2 x %struct.timespec], [2 x %struct.timespec]* %ts, i64 0, i64 0, !dbg !2359
  %tv_sec = getelementptr inbounds %struct.timespec, %struct.timespec* %arrayidx, i32 0, i32 0, !dbg !2360
  store i64 %1, i64* %tv_sec, align 16, !dbg !2361
  %2 = load i64, i64* %atime_nsec.addr, align 8, !dbg !2362
  %arrayidx1 = getelementptr inbounds [2 x %struct.timespec], [2 x %struct.timespec]* %ts, i64 0, i64 0, !dbg !2363
  %tv_nsec = getelementptr inbounds %struct.timespec, %struct.timespec* %arrayidx1, i32 0, i32 1, !dbg !2364
  store i64 %2, i64* %tv_nsec, align 8, !dbg !2365
  %3 = load i64, i64* %mtime.addr, align 8, !dbg !2366
  %arrayidx2 = getelementptr inbounds [2 x %struct.timespec], [2 x %struct.timespec]* %ts, i64 0, i64 1, !dbg !2367
  %tv_sec3 = getelementptr inbounds %struct.timespec, %struct.timespec* %arrayidx2, i32 0, i32 0, !dbg !2368
  store i64 %3, i64* %tv_sec3, align 16, !dbg !2369
  %4 = load i64, i64* %mtime_nsec.addr, align 8, !dbg !2370
  %arrayidx4 = getelementptr inbounds [2 x %struct.timespec], [2 x %struct.timespec]* %ts, i64 0, i64 1, !dbg !2371
  %tv_nsec5 = getelementptr inbounds %struct.timespec, %struct.timespec* %arrayidx4, i32 0, i32 1, !dbg !2372
  store i64 %4, i64* %tv_nsec5, align 8, !dbg !2373
  %5 = load i32, i32* %fd.addr, align 4, !dbg !2374
  %cmp = icmp sge i32 %5, 0, !dbg !2376
  br i1 %cmp, label %if.then, label %if.end, !dbg !2377

if.then:                                          ; preds = %entry
  %6 = load i32, i32* %fd.addr, align 4, !dbg !2378
  %arraydecay = getelementptr inbounds [2 x %struct.timespec], [2 x %struct.timespec]* %ts, i32 0, i32 0, !dbg !2379
  %call = call i32 @futimens(i32 %6, %struct.timespec* %arraydecay) #7, !dbg !2380
  store i32 %call, i32* %retval, align 4, !dbg !2381
  br label %return, !dbg !2381

if.end:                                           ; preds = %entry
  %7 = load i8*, i8** %name.addr, align 8, !dbg !2382
  %arraydecay6 = getelementptr inbounds [2 x %struct.timespec], [2 x %struct.timespec]* %ts, i32 0, i32 0, !dbg !2383
  %call7 = call i32 @utimensat(i32 -100, i8* %7, %struct.timespec* %arraydecay6, i32 256) #7, !dbg !2384
  store i32 %call7, i32* %retval, align 4, !dbg !2385
  br label %return, !dbg !2385

return:                                           ; preds = %if.end, %if.then
  %8 = load i32, i32* %retval, align 4, !dbg !2386
  ret i32 %8, !dbg !2386
}

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #5

; Function Attrs: nounwind
declare i32 @futimens(i32, %struct.timespec*) #3

; Function Attrs: nounwind
declare i32 @utimensat(i32, i8*, %struct.timespec*, i32) #3

declare i32 @open(i8*, i32, ...) #2

declare void @__archive_ensure_cloexec_flag(i32) #2

; Function Attrs: nounwind
declare i32 @ioctl(i32, i64, ...) #3

declare i32 @close(i32) #2

declare void @archive_entry_free(%struct.archive_entry*) #2

declare void @archive_string_free(%struct.archive_string*) #2

declare i32 @__archive_clean(%struct.archive*) #2

declare void @archive_clear_error(%struct.archive*) #2

declare %struct.archive_entry* @archive_entry_clone(%struct.archive_entry*) #2

declare i32 @archive_entry_mode(%struct.archive_entry*) #2

declare i32 @archive_entry_size_is_set(%struct.archive_entry*) #2

declare i64 @archive_entry_size(%struct.archive_entry*) #2

declare %struct.archive_string* @archive_strncat(%struct.archive_string*, i8*, i64) #2

declare i8* @archive_entry_pathname(%struct.archive_entry*) #2

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #4

; Function Attrs: nounwind uwtable
define internal i32 @cleanup_pathname(%struct.archive_write_disk* %a) #0 !dbg !343 {
entry:
  %a.addr = alloca %struct.archive_write_disk*, align 8
  %error_string = alloca %struct.archive_string, align 8
  %error_number = alloca i32, align 4
  %rc = alloca i32, align 4
  store %struct.archive_write_disk* %a, %struct.archive_write_disk** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_disk** %a.addr, metadata !2387, metadata !399), !dbg !2388
  call void @llvm.dbg.declare(metadata %struct.archive_string* %error_string, metadata !2389, metadata !399), !dbg !2390
  call void @llvm.dbg.declare(metadata i32* %error_number, metadata !2391, metadata !399), !dbg !2392
  call void @llvm.dbg.declare(metadata i32* %rc, metadata !2393, metadata !399), !dbg !2394
  br label %do.body, !dbg !2395

do.body:                                          ; preds = %entry
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %error_string, i32 0, i32 0, !dbg !2396
  store i8* null, i8** %s, align 8, !dbg !2396
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %error_string, i32 0, i32 1, !dbg !2396
  store i64 0, i64* %length, align 8, !dbg !2396
  %buffer_length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %error_string, i32 0, i32 2, !dbg !2396
  store i64 0, i64* %buffer_length, align 8, !dbg !2396
  br label %do.end, !dbg !2396

do.end:                                           ; preds = %do.body
  %0 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2399
  %name = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %0, i32 0, i32 19, !dbg !2400
  %1 = load i8*, i8** %name, align 8, !dbg !2400
  %2 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2401
  %flags = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %2, i32 0, i32 23, !dbg !2402
  %3 = load i32, i32* %flags, align 8, !dbg !2402
  %call = call i32 @cleanup_pathname_fsobj(i8* %1, i32* %error_number, %struct.archive_string* %error_string, i32 %3), !dbg !2403
  store i32 %call, i32* %rc, align 4, !dbg !2404
  %4 = load i32, i32* %rc, align 4, !dbg !2405
  %cmp = icmp ne i32 %4, 0, !dbg !2407
  br i1 %cmp, label %if.then, label %if.end, !dbg !2408

if.then:                                          ; preds = %do.end
  %5 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2409
  %archive = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %5, i32 0, i32 0, !dbg !2411
  %6 = load i32, i32* %error_number, align 4, !dbg !2412
  %s1 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %error_string, i32 0, i32 0, !dbg !2413
  %7 = load i8*, i8** %s1, align 8, !dbg !2413
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 %6, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.11, i32 0, i32 0), i8* %7), !dbg !2414
  br label %if.end, !dbg !2415

if.end:                                           ; preds = %if.then, %do.end
  call void @archive_string_free(%struct.archive_string* %error_string), !dbg !2416
  %8 = load i32, i32* %rc, align 4, !dbg !2417
  ret i32 %8, !dbg !2418
}

declare i32 @archive_entry_filetype(%struct.archive_entry*) #2

; Function Attrs: nounwind uwtable
define internal i32 @check_symlinks(%struct.archive_write_disk* %a) #0 !dbg !354 {
entry:
  %a.addr = alloca %struct.archive_write_disk*, align 8
  %error_string = alloca %struct.archive_string, align 8
  %error_number = alloca i32, align 4
  %rc = alloca i32, align 4
  store %struct.archive_write_disk* %a, %struct.archive_write_disk** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_disk** %a.addr, metadata !2419, metadata !399), !dbg !2420
  call void @llvm.dbg.declare(metadata %struct.archive_string* %error_string, metadata !2421, metadata !399), !dbg !2422
  call void @llvm.dbg.declare(metadata i32* %error_number, metadata !2423, metadata !399), !dbg !2424
  call void @llvm.dbg.declare(metadata i32* %rc, metadata !2425, metadata !399), !dbg !2426
  br label %do.body, !dbg !2427

do.body:                                          ; preds = %entry
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %error_string, i32 0, i32 0, !dbg !2428
  store i8* null, i8** %s, align 8, !dbg !2428
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %error_string, i32 0, i32 1, !dbg !2428
  store i64 0, i64* %length, align 8, !dbg !2428
  %buffer_length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %error_string, i32 0, i32 2, !dbg !2428
  store i64 0, i64* %buffer_length, align 8, !dbg !2428
  br label %do.end, !dbg !2428

do.end:                                           ; preds = %do.body
  %0 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2431
  %name = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %0, i32 0, i32 19, !dbg !2432
  %1 = load i8*, i8** %name, align 8, !dbg !2432
  %2 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2433
  %flags = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %2, i32 0, i32 23, !dbg !2434
  %3 = load i32, i32* %flags, align 8, !dbg !2434
  %call = call i32 @check_symlinks_fsobj(i8* %1, i32* %error_number, %struct.archive_string* %error_string, i32 %3), !dbg !2435
  store i32 %call, i32* %rc, align 4, !dbg !2436
  %4 = load i32, i32* %rc, align 4, !dbg !2437
  %cmp = icmp ne i32 %4, 0, !dbg !2439
  br i1 %cmp, label %if.then, label %if.end, !dbg !2440

if.then:                                          ; preds = %do.end
  %5 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2441
  %archive = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %5, i32 0, i32 0, !dbg !2443
  %6 = load i32, i32* %error_number, align 4, !dbg !2444
  %s1 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %error_string, i32 0, i32 0, !dbg !2445
  %7 = load i8*, i8** %s1, align 8, !dbg !2445
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 %6, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.11, i32 0, i32 0), i8* %7), !dbg !2446
  br label %if.end, !dbg !2447

if.end:                                           ; preds = %if.then, %do.end
  call void @archive_string_free(%struct.archive_string* %error_string), !dbg !2448
  %8 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2449
  %pst = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %8, i32 0, i32 17, !dbg !2450
  store %struct.stat* null, %struct.stat** %pst, align 8, !dbg !2451
  %9 = load i32, i32* %rc, align 4, !dbg !2452
  ret i32 %9, !dbg !2453
}

; Function Attrs: nounwind uwtable
define internal void @edit_deep_directories(%struct.archive_write_disk* %a) #0 !dbg !356 {
entry:
  %a.addr = alloca %struct.archive_write_disk*, align 8
  %ret = alloca i32, align 4
  %tail = alloca i8*, align 8
  store %struct.archive_write_disk* %a, %struct.archive_write_disk** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_disk** %a.addr, metadata !2454, metadata !399), !dbg !2455
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !2456, metadata !399), !dbg !2457
  call void @llvm.dbg.declare(metadata i8** %tail, metadata !2458, metadata !399), !dbg !2459
  %0 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2460
  %name = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %0, i32 0, i32 19, !dbg !2461
  %1 = load i8*, i8** %name, align 8, !dbg !2461
  store i8* %1, i8** %tail, align 8, !dbg !2459
  %2 = load i8*, i8** %tail, align 8, !dbg !2462
  %call = call i64 @strlen(i8* %2) #8, !dbg !2464
  %cmp = icmp ult i64 %call, 4096, !dbg !2465
  br i1 %cmp, label %if.then, label %if.end, !dbg !2466

if.then:                                          ; preds = %entry
  br label %return, !dbg !2467

if.end:                                           ; preds = %entry
  %call1 = call i32 (i8*, i32, ...) @open(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.18, i32 0, i32 0), i32 524288), !dbg !2468
  %3 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2469
  %restore_pwd = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %3, i32 0, i32 29, !dbg !2470
  store i32 %call1, i32* %restore_pwd, align 8, !dbg !2471
  %4 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2472
  %restore_pwd2 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %4, i32 0, i32 29, !dbg !2473
  %5 = load i32, i32* %restore_pwd2, align 8, !dbg !2473
  call void @__archive_ensure_cloexec_flag(i32 %5), !dbg !2474
  %6 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2475
  %restore_pwd3 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %6, i32 0, i32 29, !dbg !2477
  %7 = load i32, i32* %restore_pwd3, align 8, !dbg !2477
  %cmp4 = icmp slt i32 %7, 0, !dbg !2478
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !2479

if.then5:                                         ; preds = %if.end
  br label %return, !dbg !2480

if.end6:                                          ; preds = %if.end
  br label %while.cond, !dbg !2481

while.cond:                                       ; preds = %if.end33, %if.end6
  %8 = load i8*, i8** %tail, align 8, !dbg !2482
  %call7 = call i64 @strlen(i8* %8) #8, !dbg !2484
  %cmp8 = icmp uge i64 %call7, 4096, !dbg !2485
  br i1 %cmp8, label %while.body, label %while.end36, !dbg !2486

while.body:                                       ; preds = %while.cond
  %9 = load i8*, i8** %tail, align 8, !dbg !2487
  %add.ptr = getelementptr inbounds i8, i8* %9, i64 4088, !dbg !2487
  store i8* %add.ptr, i8** %tail, align 8, !dbg !2487
  br label %while.cond9, !dbg !2489

while.cond9:                                      ; preds = %while.body14, %while.body
  %10 = load i8*, i8** %tail, align 8, !dbg !2490
  %11 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2492
  %name10 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %11, i32 0, i32 19, !dbg !2493
  %12 = load i8*, i8** %name10, align 8, !dbg !2493
  %cmp11 = icmp ugt i8* %10, %12, !dbg !2494
  br i1 %cmp11, label %land.rhs, label %land.end, !dbg !2495

land.rhs:                                         ; preds = %while.cond9
  %13 = load i8*, i8** %tail, align 8, !dbg !2496
  %14 = load i8, i8* %13, align 1, !dbg !2498
  %conv = sext i8 %14 to i32, !dbg !2498
  %cmp12 = icmp ne i32 %conv, 47, !dbg !2499
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond9
  %15 = phi i1 [ false, %while.cond9 ], [ %cmp12, %land.rhs ]
  br i1 %15, label %while.body14, label %while.end, !dbg !2500

while.body14:                                     ; preds = %land.end
  %16 = load i8*, i8** %tail, align 8, !dbg !2502
  %incdec.ptr = getelementptr inbounds i8, i8* %16, i32 -1, !dbg !2502
  store i8* %incdec.ptr, i8** %tail, align 8, !dbg !2502
  br label %while.cond9, !dbg !2503

while.end:                                        ; preds = %land.end
  %17 = load i8*, i8** %tail, align 8, !dbg !2505
  %18 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2507
  %name15 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %18, i32 0, i32 19, !dbg !2508
  %19 = load i8*, i8** %name15, align 8, !dbg !2508
  %cmp16 = icmp ule i8* %17, %19, !dbg !2509
  br i1 %cmp16, label %if.then18, label %if.end19, !dbg !2510

if.then18:                                        ; preds = %while.end
  br label %return, !dbg !2511

if.end19:                                         ; preds = %while.end
  %20 = load i8*, i8** %tail, align 8, !dbg !2512
  store i8 0, i8* %20, align 1, !dbg !2513
  %21 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2514
  %22 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2515
  %name20 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %22, i32 0, i32 19, !dbg !2516
  %23 = load i8*, i8** %name20, align 8, !dbg !2516
  %call21 = call i32 @create_dir(%struct.archive_write_disk* %21, i8* %23), !dbg !2517
  store i32 %call21, i32* %ret, align 4, !dbg !2518
  %24 = load i32, i32* %ret, align 4, !dbg !2519
  %cmp22 = icmp eq i32 %24, 0, !dbg !2521
  br i1 %cmp22, label %land.lhs.true, label %if.end29, !dbg !2522

land.lhs.true:                                    ; preds = %if.end19
  %25 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2523
  %name24 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %25, i32 0, i32 19, !dbg !2525
  %26 = load i8*, i8** %name24, align 8, !dbg !2525
  %call25 = call i32 @chdir(i8* %26) #7, !dbg !2526
  %cmp26 = icmp ne i32 %call25, 0, !dbg !2527
  br i1 %cmp26, label %if.then28, label %if.end29, !dbg !2528

if.then28:                                        ; preds = %land.lhs.true
  store i32 -25, i32* %ret, align 4, !dbg !2529
  br label %if.end29, !dbg !2530

if.end29:                                         ; preds = %if.then28, %land.lhs.true, %if.end19
  %27 = load i8*, i8** %tail, align 8, !dbg !2531
  store i8 47, i8* %27, align 1, !dbg !2532
  %28 = load i32, i32* %ret, align 4, !dbg !2533
  %cmp30 = icmp ne i32 %28, 0, !dbg !2535
  br i1 %cmp30, label %if.then32, label %if.end33, !dbg !2536

if.then32:                                        ; preds = %if.end29
  br label %return, !dbg !2537

if.end33:                                         ; preds = %if.end29
  %29 = load i8*, i8** %tail, align 8, !dbg !2538
  %incdec.ptr34 = getelementptr inbounds i8, i8* %29, i32 1, !dbg !2538
  store i8* %incdec.ptr34, i8** %tail, align 8, !dbg !2538
  %30 = load i8*, i8** %tail, align 8, !dbg !2539
  %31 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2540
  %name35 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %31, i32 0, i32 19, !dbg !2541
  store i8* %30, i8** %name35, align 8, !dbg !2542
  br label %while.cond, !dbg !2543

while.end36:                                      ; preds = %while.cond
  br label %return, !dbg !2545

return:                                           ; preds = %while.end36, %if.then32, %if.then18, %if.then5, %if.then
  ret void, !dbg !2546
}

; Function Attrs: nounwind uwtable
define internal i32 @restore_entry(%struct.archive_write_disk* %a) #0 !dbg !365 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write_disk*, align 8
  %ret = alloca i32, align 4
  %en = alloca i32, align 4
  %r = alloca i32, align 4
  store %struct.archive_write_disk* %a, %struct.archive_write_disk** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_disk** %a.addr, metadata !2547, metadata !399), !dbg !2548
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !2549, metadata !399), !dbg !2550
  store i32 0, i32* %ret, align 4, !dbg !2550
  call void @llvm.dbg.declare(metadata i32* %en, metadata !2551, metadata !399), !dbg !2552
  %0 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2553
  %flags = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %0, i32 0, i32 23, !dbg !2555
  %1 = load i32, i32* %flags, align 8, !dbg !2555
  %and = and i32 %1, 16, !dbg !2556
  %tobool = icmp ne i32 %and, 0, !dbg !2556
  br i1 %tobool, label %land.lhs.true, label %if.end23, !dbg !2557

land.lhs.true:                                    ; preds = %entry
  %2 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2558
  %mode = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %2, i32 0, i32 30, !dbg !2558
  %3 = load i32, i32* %mode, align 4, !dbg !2558
  %and1 = and i32 %3, 61440, !dbg !2558
  %cmp = icmp eq i32 %and1, 16384, !dbg !2558
  br i1 %cmp, label %if.end23, label %if.then, !dbg !2560

if.then:                                          ; preds = %land.lhs.true
  %4 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2561
  %flags2 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %4, i32 0, i32 23, !dbg !2564
  %5 = load i32, i32* %flags2, align 8, !dbg !2564
  %and3 = and i32 %5, 131072, !dbg !2565
  %tobool4 = icmp ne i32 %and3, 0, !dbg !2565
  br i1 %tobool4, label %if.then5, label %if.end, !dbg !2566

if.then5:                                         ; preds = %if.then
  %6 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2567
  %call = call i32 @clear_nochange_fflags(%struct.archive_write_disk* %6), !dbg !2568
  br label %if.end, !dbg !2569

if.end:                                           ; preds = %if.then5, %if.then
  %7 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2570
  %name = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %7, i32 0, i32 19, !dbg !2572
  %8 = load i8*, i8** %name, align 8, !dbg !2572
  %call6 = call i32 @unlink(i8* %8) #7, !dbg !2573
  %cmp7 = icmp eq i32 %call6, 0, !dbg !2574
  br i1 %cmp7, label %if.then8, label %if.else, !dbg !2575

if.then8:                                         ; preds = %if.end
  %9 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2576
  %pst = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %9, i32 0, i32 17, !dbg !2578
  store %struct.stat* null, %struct.stat** %pst, align 8, !dbg !2579
  br label %if.end22, !dbg !2580

if.else:                                          ; preds = %if.end
  %call9 = call i32* @__errno_location() #1, !dbg !2581
  %10 = load i32, i32* %call9, align 4, !dbg !2581
  %cmp10 = icmp eq i32 %10, 2, !dbg !2584
  br i1 %cmp10, label %if.then11, label %if.else12, !dbg !2581

if.then11:                                        ; preds = %if.else
  br label %if.end21, !dbg !2585

if.else12:                                        ; preds = %if.else
  %11 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2587
  %name13 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %11, i32 0, i32 19, !dbg !2590
  %12 = load i8*, i8** %name13, align 8, !dbg !2590
  %call14 = call i32 @rmdir(i8* %12) #7, !dbg !2591
  %cmp15 = icmp eq i32 %call14, 0, !dbg !2592
  br i1 %cmp15, label %if.then16, label %if.else18, !dbg !2591

if.then16:                                        ; preds = %if.else12
  %13 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2593
  %pst17 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %13, i32 0, i32 17, !dbg !2595
  store %struct.stat* null, %struct.stat** %pst17, align 8, !dbg !2596
  br label %if.end20, !dbg !2597

if.else18:                                        ; preds = %if.else12
  %14 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2598
  %archive = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %14, i32 0, i32 0, !dbg !2600
  %call19 = call i32* @__errno_location() #1, !dbg !2601
  %15 = load i32, i32* %call19, align 4, !dbg !2601
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 %15, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.30, i32 0, i32 0)), !dbg !2602
  store i32 -25, i32* %retval, align 4, !dbg !2604
  br label %return, !dbg !2604

if.end20:                                         ; preds = %if.then16
  br label %if.end21

if.end21:                                         ; preds = %if.end20, %if.then11
  br label %if.end22

if.end22:                                         ; preds = %if.end21, %if.then8
  br label %if.end23, !dbg !2605

if.end23:                                         ; preds = %if.end22, %land.lhs.true, %entry
  %16 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2606
  %call24 = call i32 @create_filesystem_object(%struct.archive_write_disk* %16), !dbg !2607
  store i32 %call24, i32* %en, align 4, !dbg !2608
  %17 = load i32, i32* %en, align 4, !dbg !2609
  %cmp25 = icmp eq i32 %17, 20, !dbg !2611
  br i1 %cmp25, label %land.lhs.true27, label %lor.lhs.false, !dbg !2612

lor.lhs.false:                                    ; preds = %if.end23
  %18 = load i32, i32* %en, align 4, !dbg !2613
  %cmp26 = icmp eq i32 %18, 2, !dbg !2615
  br i1 %cmp26, label %land.lhs.true27, label %if.end35, !dbg !2616

land.lhs.true27:                                  ; preds = %lor.lhs.false, %if.end23
  %19 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2617
  %flags28 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %19, i32 0, i32 23, !dbg !2618
  %20 = load i32, i32* %flags28, align 8, !dbg !2618
  %and29 = and i32 %20, 1024, !dbg !2619
  %tobool30 = icmp ne i32 %and29, 0, !dbg !2619
  br i1 %tobool30, label %if.end35, label %if.then31, !dbg !2620

if.then31:                                        ; preds = %land.lhs.true27
  %21 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2622
  %22 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2624
  %name32 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %22, i32 0, i32 19, !dbg !2625
  %23 = load i8*, i8** %name32, align 8, !dbg !2625
  %call33 = call i32 @create_parent_dir(%struct.archive_write_disk* %21, i8* %23), !dbg !2626
  %24 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2627
  %call34 = call i32 @create_filesystem_object(%struct.archive_write_disk* %24), !dbg !2628
  store i32 %call34, i32* %en, align 4, !dbg !2629
  br label %if.end35, !dbg !2630

if.end35:                                         ; preds = %if.then31, %land.lhs.true27, %lor.lhs.false
  %25 = load i32, i32* %en, align 4, !dbg !2631
  %cmp36 = icmp eq i32 %25, 2, !dbg !2633
  br i1 %cmp36, label %land.lhs.true37, label %if.end45, !dbg !2634

land.lhs.true37:                                  ; preds = %if.end35
  %26 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2635
  %entry38 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %26, i32 0, i32 18, !dbg !2637
  %27 = load %struct.archive_entry*, %struct.archive_entry** %entry38, align 8, !dbg !2637
  %call39 = call i8* @archive_entry_hardlink(%struct.archive_entry* %27), !dbg !2638
  %cmp40 = icmp ne i8* %call39, null, !dbg !2639
  br i1 %cmp40, label %if.then41, label %if.end45, !dbg !2640

if.then41:                                        ; preds = %land.lhs.true37
  %28 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2641
  %archive42 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %28, i32 0, i32 0, !dbg !2643
  %29 = load i32, i32* %en, align 4, !dbg !2644
  %30 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2645
  %entry43 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %30, i32 0, i32 18, !dbg !2646
  %31 = load %struct.archive_entry*, %struct.archive_entry** %entry43, align 8, !dbg !2646
  %call44 = call i8* @archive_entry_hardlink(%struct.archive_entry* %31), !dbg !2647
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive42, i32 %29, i8* getelementptr inbounds ([38 x i8], [38 x i8]* @.str.31, i32 0, i32 0), i8* %call44), !dbg !2648
  store i32 -25, i32* %retval, align 4, !dbg !2649
  br label %return, !dbg !2649

if.end45:                                         ; preds = %land.lhs.true37, %if.end35
  %32 = load i32, i32* %en, align 4, !dbg !2650
  %cmp46 = icmp eq i32 %32, 21, !dbg !2652
  br i1 %cmp46, label %land.lhs.true49, label %lor.lhs.false47, !dbg !2653

lor.lhs.false47:                                  ; preds = %if.end45
  %33 = load i32, i32* %en, align 4, !dbg !2654
  %cmp48 = icmp eq i32 %33, 17, !dbg !2656
  br i1 %cmp48, label %land.lhs.true49, label %if.end55, !dbg !2657

land.lhs.true49:                                  ; preds = %lor.lhs.false47, %if.end45
  %34 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2658
  %flags50 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %34, i32 0, i32 23, !dbg !2659
  %35 = load i32, i32* %flags50, align 8, !dbg !2659
  %and51 = and i32 %35, 8, !dbg !2660
  %tobool52 = icmp ne i32 %and51, 0, !dbg !2660
  br i1 %tobool52, label %if.then53, label %if.end55, !dbg !2661

if.then53:                                        ; preds = %land.lhs.true49
  %36 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2662
  %entry54 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %36, i32 0, i32 18, !dbg !2664
  %37 = load %struct.archive_entry*, %struct.archive_entry** %entry54, align 8, !dbg !2664
  call void @archive_entry_unset_size(%struct.archive_entry* %37), !dbg !2665
  store i32 0, i32* %retval, align 4, !dbg !2666
  br label %return, !dbg !2666

if.end55:                                         ; preds = %land.lhs.true49, %lor.lhs.false47
  %38 = load i32, i32* %en, align 4, !dbg !2667
  %cmp56 = icmp eq i32 %38, 21, !dbg !2669
  br i1 %cmp56, label %if.then57, label %if.else67, !dbg !2670

if.then57:                                        ; preds = %if.end55
  %39 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2671
  %name58 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %39, i32 0, i32 19, !dbg !2674
  %40 = load i8*, i8** %name58, align 8, !dbg !2674
  %call59 = call i32 @rmdir(i8* %40) #7, !dbg !2675
  %cmp60 = icmp ne i32 %call59, 0, !dbg !2676
  br i1 %cmp60, label %if.then61, label %if.end64, !dbg !2677

if.then61:                                        ; preds = %if.then57
  %41 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2678
  %archive62 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %41, i32 0, i32 0, !dbg !2680
  %call63 = call i32* @__errno_location() #1, !dbg !2681
  %42 = load i32, i32* %call63, align 4, !dbg !2681
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive62, i32 %42, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.32, i32 0, i32 0)), !dbg !2682
  store i32 -25, i32* %retval, align 4, !dbg !2684
  br label %return, !dbg !2684

if.end64:                                         ; preds = %if.then57
  %43 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2685
  %pst65 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %43, i32 0, i32 17, !dbg !2686
  store %struct.stat* null, %struct.stat** %pst65, align 8, !dbg !2687
  %44 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2688
  %call66 = call i32 @create_filesystem_object(%struct.archive_write_disk* %44), !dbg !2689
  store i32 %call66, i32* %en, align 4, !dbg !2690
  br label %if.end172, !dbg !2691

if.else67:                                        ; preds = %if.end55
  %45 = load i32, i32* %en, align 4, !dbg !2692
  %cmp68 = icmp eq i32 %45, 17, !dbg !2695
  br i1 %cmp68, label %if.then69, label %if.end171, !dbg !2692

if.then69:                                        ; preds = %if.else67
  call void @llvm.dbg.declare(metadata i32* %r, metadata !2696, metadata !399), !dbg !2698
  store i32 0, i32* %r, align 4, !dbg !2698
  %46 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2699
  %mode70 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %46, i32 0, i32 30, !dbg !2699
  %47 = load i32, i32* %mode70, align 4, !dbg !2699
  %and71 = and i32 %47, 61440, !dbg !2699
  %cmp72 = icmp eq i32 %and71, 16384, !dbg !2699
  br i1 %cmp72, label %if.then73, label %if.end76, !dbg !2701

if.then73:                                        ; preds = %if.then69
  %48 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2702
  %name74 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %48, i32 0, i32 19, !dbg !2703
  %49 = load i8*, i8** %name74, align 8, !dbg !2703
  %50 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2704
  %st = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %50, i32 0, i32 16, !dbg !2705
  %call75 = call i32 @stat(i8* %49, %struct.stat* %st) #7, !dbg !2706
  store i32 %call75, i32* %r, align 4, !dbg !2707
  br label %if.end76, !dbg !2708

if.end76:                                         ; preds = %if.then73, %if.then69
  %51 = load i32, i32* %r, align 4, !dbg !2709
  %cmp77 = icmp ne i32 %51, 0, !dbg !2711
  br i1 %cmp77, label %if.then82, label %lor.lhs.false78, !dbg !2712

lor.lhs.false78:                                  ; preds = %if.end76
  %52 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2713
  %mode79 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %52, i32 0, i32 30, !dbg !2713
  %53 = load i32, i32* %mode79, align 4, !dbg !2713
  %and80 = and i32 %53, 61440, !dbg !2713
  %cmp81 = icmp eq i32 %and80, 16384, !dbg !2713
  br i1 %cmp81, label %if.end86, label %if.then82, !dbg !2715

if.then82:                                        ; preds = %lor.lhs.false78, %if.end76
  %54 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2716
  %name83 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %54, i32 0, i32 19, !dbg !2717
  %55 = load i8*, i8** %name83, align 8, !dbg !2717
  %56 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2718
  %st84 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %56, i32 0, i32 16, !dbg !2719
  %call85 = call i32 @lstat(i8* %55, %struct.stat* %st84) #7, !dbg !2720
  store i32 %call85, i32* %r, align 4, !dbg !2721
  br label %if.end86, !dbg !2722

if.end86:                                         ; preds = %if.then82, %lor.lhs.false78
  %57 = load i32, i32* %r, align 4, !dbg !2723
  %cmp87 = icmp ne i32 %57, 0, !dbg !2725
  br i1 %cmp87, label %if.then88, label %if.end91, !dbg !2726

if.then88:                                        ; preds = %if.end86
  %58 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2727
  %archive89 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %58, i32 0, i32 0, !dbg !2729
  %call90 = call i32* @__errno_location() #1, !dbg !2730
  %59 = load i32, i32* %call90, align 4, !dbg !2730
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive89, i32 %59, i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.33, i32 0, i32 0)), !dbg !2731
  store i32 -25, i32* %retval, align 4, !dbg !2733
  br label %return, !dbg !2733

if.end91:                                         ; preds = %if.end86
  %60 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2734
  %flags92 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %60, i32 0, i32 23, !dbg !2736
  %61 = load i32, i32* %flags92, align 8, !dbg !2736
  %and93 = and i32 %61, 2048, !dbg !2737
  %tobool94 = icmp ne i32 %and93, 0, !dbg !2737
  br i1 %tobool94, label %land.lhs.true95, label %if.end107, !dbg !2738

land.lhs.true95:                                  ; preds = %if.end91
  %62 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2739
  %st96 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %62, i32 0, i32 16, !dbg !2739
  %st_mode = getelementptr inbounds %struct.stat, %struct.stat* %st96, i32 0, i32 3, !dbg !2739
  %63 = load i32, i32* %st_mode, align 8, !dbg !2739
  %and97 = and i32 %63, 61440, !dbg !2739
  %cmp98 = icmp eq i32 %and97, 16384, !dbg !2739
  br i1 %cmp98, label %if.end107, label %if.then99, !dbg !2741

if.then99:                                        ; preds = %land.lhs.true95
  %64 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2743
  %st100 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %64, i32 0, i32 16, !dbg !2746
  %65 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2747
  %entry101 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %65, i32 0, i32 18, !dbg !2748
  %66 = load %struct.archive_entry*, %struct.archive_entry** %entry101, align 8, !dbg !2748
  %call102 = call i32 @older(%struct.stat* %st100, %struct.archive_entry* %66), !dbg !2749
  %tobool103 = icmp ne i32 %call102, 0, !dbg !2749
  br i1 %tobool103, label %if.end106, label %if.then104, !dbg !2750

if.then104:                                       ; preds = %if.then99
  %67 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2751
  %entry105 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %67, i32 0, i32 18, !dbg !2753
  %68 = load %struct.archive_entry*, %struct.archive_entry** %entry105, align 8, !dbg !2753
  call void @archive_entry_unset_size(%struct.archive_entry* %68), !dbg !2754
  store i32 0, i32* %retval, align 4, !dbg !2755
  br label %return, !dbg !2755

if.end106:                                        ; preds = %if.then99
  br label %if.end107, !dbg !2756

if.end107:                                        ; preds = %if.end106, %land.lhs.true95, %if.end91
  %69 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2757
  %skip_file_set = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %69, i32 0, i32 5, !dbg !2759
  %70 = load i32, i32* %skip_file_set, align 8, !dbg !2759
  %tobool108 = icmp ne i32 %70, 0, !dbg !2757
  br i1 %tobool108, label %land.lhs.true109, label %if.end117, !dbg !2760

land.lhs.true109:                                 ; preds = %if.end107
  %71 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2761
  %st110 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %71, i32 0, i32 16, !dbg !2762
  %st_dev = getelementptr inbounds %struct.stat, %struct.stat* %st110, i32 0, i32 0, !dbg !2763
  %72 = load i64, i64* %st_dev, align 8, !dbg !2763
  %73 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2764
  %skip_file_dev = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %73, i32 0, i32 6, !dbg !2765
  %74 = load i64, i64* %skip_file_dev, align 8, !dbg !2765
  %cmp111 = icmp eq i64 %72, %74, !dbg !2766
  br i1 %cmp111, label %land.lhs.true112, label %if.end117, !dbg !2767

land.lhs.true112:                                 ; preds = %land.lhs.true109
  %75 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2768
  %st113 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %75, i32 0, i32 16, !dbg !2769
  %st_ino = getelementptr inbounds %struct.stat, %struct.stat* %st113, i32 0, i32 1, !dbg !2770
  %76 = load i64, i64* %st_ino, align 8, !dbg !2770
  %77 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2771
  %skip_file_ino = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %77, i32 0, i32 7, !dbg !2772
  %78 = load i64, i64* %skip_file_ino, align 8, !dbg !2772
  %cmp114 = icmp eq i64 %76, %78, !dbg !2773
  br i1 %cmp114, label %if.then115, label %if.end117, !dbg !2774

if.then115:                                       ; preds = %land.lhs.true112
  %79 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2775
  %archive116 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %79, i32 0, i32 0, !dbg !2777
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive116, i32 0, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.34, i32 0, i32 0)), !dbg !2778
  store i32 -25, i32* %retval, align 4, !dbg !2779
  br label %return, !dbg !2779

if.end117:                                        ; preds = %land.lhs.true112, %land.lhs.true109, %if.end107
  %80 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2780
  %st118 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %80, i32 0, i32 16, !dbg !2780
  %st_mode119 = getelementptr inbounds %struct.stat, %struct.stat* %st118, i32 0, i32 3, !dbg !2780
  %81 = load i32, i32* %st_mode119, align 8, !dbg !2780
  %and120 = and i32 %81, 61440, !dbg !2780
  %cmp121 = icmp eq i32 %and120, 16384, !dbg !2780
  br i1 %cmp121, label %if.else138, label %if.then122, !dbg !2782

if.then122:                                       ; preds = %if.end117
  %82 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2783
  %flags123 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %82, i32 0, i32 23, !dbg !2786
  %83 = load i32, i32* %flags123, align 8, !dbg !2786
  %and124 = and i32 %83, 131072, !dbg !2787
  %tobool125 = icmp ne i32 %and124, 0, !dbg !2787
  br i1 %tobool125, label %if.then126, label %if.end128, !dbg !2788

if.then126:                                       ; preds = %if.then122
  %84 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2789
  %call127 = call i32 @clear_nochange_fflags(%struct.archive_write_disk* %84), !dbg !2790
  br label %if.end128, !dbg !2791

if.end128:                                        ; preds = %if.then126, %if.then122
  %85 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2792
  %name129 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %85, i32 0, i32 19, !dbg !2794
  %86 = load i8*, i8** %name129, align 8, !dbg !2794
  %call130 = call i32 @unlink(i8* %86) #7, !dbg !2795
  %cmp131 = icmp ne i32 %call130, 0, !dbg !2796
  br i1 %cmp131, label %if.then132, label %if.end135, !dbg !2797

if.then132:                                       ; preds = %if.end128
  %87 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2798
  %archive133 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %87, i32 0, i32 0, !dbg !2800
  %call134 = call i32* @__errno_location() #1, !dbg !2801
  %88 = load i32, i32* %call134, align 4, !dbg !2801
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive133, i32 %88, i8* getelementptr inbounds ([37 x i8], [37 x i8]* @.str.35, i32 0, i32 0)), !dbg !2802
  store i32 -25, i32* %retval, align 4, !dbg !2804
  br label %return, !dbg !2804

if.end135:                                        ; preds = %if.end128
  %89 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2805
  %pst136 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %89, i32 0, i32 17, !dbg !2806
  store %struct.stat* null, %struct.stat** %pst136, align 8, !dbg !2807
  %90 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2808
  %call137 = call i32 @create_filesystem_object(%struct.archive_write_disk* %90), !dbg !2809
  store i32 %call137, i32* %en, align 4, !dbg !2810
  br label %if.end170, !dbg !2811

if.else138:                                       ; preds = %if.end117
  %91 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2812
  %mode139 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %91, i32 0, i32 30, !dbg !2812
  %92 = load i32, i32* %mode139, align 4, !dbg !2812
  %and140 = and i32 %92, 61440, !dbg !2812
  %cmp141 = icmp eq i32 %and140, 16384, !dbg !2812
  br i1 %cmp141, label %if.else157, label %if.then142, !dbg !2815

if.then142:                                       ; preds = %if.else138
  %93 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2816
  %flags143 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %93, i32 0, i32 23, !dbg !2819
  %94 = load i32, i32* %flags143, align 8, !dbg !2819
  %and144 = and i32 %94, 131072, !dbg !2820
  %tobool145 = icmp ne i32 %and144, 0, !dbg !2820
  br i1 %tobool145, label %if.then146, label %if.end148, !dbg !2821

if.then146:                                       ; preds = %if.then142
  %95 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2822
  %call147 = call i32 @clear_nochange_fflags(%struct.archive_write_disk* %95), !dbg !2823
  br label %if.end148, !dbg !2824

if.end148:                                        ; preds = %if.then146, %if.then142
  %96 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2825
  %name149 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %96, i32 0, i32 19, !dbg !2827
  %97 = load i8*, i8** %name149, align 8, !dbg !2827
  %call150 = call i32 @rmdir(i8* %97) #7, !dbg !2828
  %cmp151 = icmp ne i32 %call150, 0, !dbg !2829
  br i1 %cmp151, label %if.then152, label %if.end155, !dbg !2830

if.then152:                                       ; preds = %if.end148
  %98 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2831
  %archive153 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %98, i32 0, i32 0, !dbg !2833
  %call154 = call i32* @__errno_location() #1, !dbg !2834
  %99 = load i32, i32* %call154, align 4, !dbg !2834
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive153, i32 %99, i8* getelementptr inbounds ([52 x i8], [52 x i8]* @.str.36, i32 0, i32 0)), !dbg !2835
  store i32 -25, i32* %retval, align 4, !dbg !2837
  br label %return, !dbg !2837

if.end155:                                        ; preds = %if.end148
  %100 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2838
  %call156 = call i32 @create_filesystem_object(%struct.archive_write_disk* %100), !dbg !2839
  store i32 %call156, i32* %en, align 4, !dbg !2840
  br label %if.end169, !dbg !2841

if.else157:                                       ; preds = %if.else138
  %101 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2842
  %mode158 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %101, i32 0, i32 30, !dbg !2845
  %102 = load i32, i32* %mode158, align 4, !dbg !2845
  %103 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2846
  %st159 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %103, i32 0, i32 16, !dbg !2847
  %st_mode160 = getelementptr inbounds %struct.stat, %struct.stat* %st159, i32 0, i32 3, !dbg !2848
  %104 = load i32, i32* %st_mode160, align 8, !dbg !2848
  %cmp161 = icmp ne i32 %102, %104, !dbg !2849
  br i1 %cmp161, label %land.lhs.true162, label %if.end168, !dbg !2850

land.lhs.true162:                                 ; preds = %if.else157
  %105 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2851
  %todo = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %105, i32 0, i32 21, !dbg !2853
  %106 = load i32, i32* %todo, align 8, !dbg !2853
  %and163 = and i32 %106, 1073741824, !dbg !2854
  %tobool164 = icmp ne i32 %and163, 0, !dbg !2854
  br i1 %tobool164, label %if.then165, label %if.end168, !dbg !2855

if.then165:                                       ; preds = %land.lhs.true162
  %107 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2857
  %todo166 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %107, i32 0, i32 21, !dbg !2858
  %108 = load i32, i32* %todo166, align 8, !dbg !2858
  %and167 = and i32 %108, 872415232, !dbg !2859
  %109 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2860
  %deferred = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %109, i32 0, i32 22, !dbg !2861
  %110 = load i32, i32* %deferred, align 4, !dbg !2862
  %or = or i32 %110, %and167, !dbg !2862
  store i32 %or, i32* %deferred, align 4, !dbg !2862
  br label %if.end168, !dbg !2860

if.end168:                                        ; preds = %if.then165, %land.lhs.true162, %if.else157
  store i32 0, i32* %en, align 4, !dbg !2863
  br label %if.end169

if.end169:                                        ; preds = %if.end168, %if.end155
  br label %if.end170

if.end170:                                        ; preds = %if.end169, %if.end135
  br label %if.end171, !dbg !2864

if.end171:                                        ; preds = %if.end170, %if.else67
  br label %if.end172

if.end172:                                        ; preds = %if.end171, %if.end64
  %111 = load i32, i32* %en, align 4, !dbg !2865
  %tobool173 = icmp ne i32 %111, 0, !dbg !2865
  br i1 %tobool173, label %if.then174, label %if.end181, !dbg !2867

if.then174:                                       ; preds = %if.end172
  %112 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2868
  %archive175 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %112, i32 0, i32 0, !dbg !2871
  %error = getelementptr inbounds %struct.archive, %struct.archive* %archive175, i32 0, i32 9, !dbg !2872
  %113 = load i8*, i8** %error, align 8, !dbg !2872
  %cmp176 = icmp eq i8* %113, null, !dbg !2873
  br i1 %cmp176, label %if.then177, label %if.end180, !dbg !2874

if.then177:                                       ; preds = %if.then174
  %114 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2875
  %archive178 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %114, i32 0, i32 0, !dbg !2876
  %115 = load i32, i32* %en, align 4, !dbg !2877
  %116 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2878
  %name179 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %116, i32 0, i32 19, !dbg !2879
  %117 = load i8*, i8** %name179, align 8, !dbg !2879
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive178, i32 %115, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.37, i32 0, i32 0), i8* %117), !dbg !2880
  br label %if.end180, !dbg !2880

if.end180:                                        ; preds = %if.then177, %if.then174
  store i32 -25, i32* %retval, align 4, !dbg !2881
  br label %return, !dbg !2881

if.end181:                                        ; preds = %if.end172
  %118 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2882
  %pst182 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %118, i32 0, i32 17, !dbg !2883
  store %struct.stat* null, %struct.stat** %pst182, align 8, !dbg !2884
  %119 = load i32, i32* %ret, align 4, !dbg !2885
  store i32 %119, i32* %retval, align 4, !dbg !2886
  br label %return, !dbg !2886

return:                                           ; preds = %if.end181, %if.end180, %if.then152, %if.then132, %if.then115, %if.then104, %if.then88, %if.then61, %if.then53, %if.then41, %if.else18
  %120 = load i32, i32* %retval, align 4, !dbg !2887
  ret i32 %120, !dbg !2887
}

; Function Attrs: nounwind
declare i32 @fchdir(i32) #3

; Function Attrs: nounwind uwtable
define internal %struct.fixup_entry* @current_fixup(%struct.archive_write_disk* %a, i8* %pathname) #0 !dbg !372 {
entry:
  %a.addr = alloca %struct.archive_write_disk*, align 8
  %pathname.addr = alloca i8*, align 8
  store %struct.archive_write_disk* %a, %struct.archive_write_disk** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_disk** %a.addr, metadata !2888, metadata !399), !dbg !2889
  store i8* %pathname, i8** %pathname.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %pathname.addr, metadata !2890, metadata !399), !dbg !2891
  %0 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2892
  %current_fixup = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %0, i32 0, i32 3, !dbg !2894
  %1 = load %struct.fixup_entry*, %struct.fixup_entry** %current_fixup, align 8, !dbg !2894
  %cmp = icmp eq %struct.fixup_entry* %1, null, !dbg !2895
  br i1 %cmp, label %if.then, label %if.end, !dbg !2896

if.then:                                          ; preds = %entry
  %2 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2897
  %3 = load i8*, i8** %pathname.addr, align 8, !dbg !2898
  %call = call %struct.fixup_entry* @new_fixup(%struct.archive_write_disk* %2, i8* %3), !dbg !2899
  %4 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2900
  %current_fixup1 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %4, i32 0, i32 3, !dbg !2901
  store %struct.fixup_entry* %call, %struct.fixup_entry** %current_fixup1, align 8, !dbg !2902
  br label %if.end, !dbg !2900

if.end:                                           ; preds = %if.then, %entry
  %5 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !2903
  %current_fixup2 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %5, i32 0, i32 3, !dbg !2904
  %6 = load %struct.fixup_entry*, %struct.fixup_entry** %current_fixup2, align 8, !dbg !2904
  ret %struct.fixup_entry* %6, !dbg !2905
}

declare i32 @archive_entry_mtime_is_set(%struct.archive_entry*) #2

declare i32 @archive_entry_atime_is_set(%struct.archive_entry*) #2

declare i64 @archive_entry_atime(%struct.archive_entry*) #2

declare i64 @archive_entry_atime_nsec(%struct.archive_entry*) #2

declare i64 @archive_entry_mtime(%struct.archive_entry*) #2

declare i64 @archive_entry_mtime_nsec(%struct.archive_entry*) #2

declare i32 @archive_entry_birthtime_is_set(%struct.archive_entry*) #2

declare i64 @archive_entry_birthtime(%struct.archive_entry*) #2

declare i64 @archive_entry_birthtime_nsec(%struct.archive_entry*) #2

declare void @archive_acl_copy(%struct.archive_acl*, %struct.archive_acl*) #2

declare %struct.archive_acl* @archive_entry_acl(%struct.archive_entry*) #2

declare i8* @archive_entry_mac_metadata(%struct.archive_entry*, i64*) #2

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #3

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #6

declare void @archive_entry_set_size(%struct.archive_entry*, i64) #2

; Function Attrs: nounwind uwtable
define internal i32 @cleanup_pathname_fsobj(i8* %path, i32* %a_eno, %struct.archive_string* %a_estr, i32 %flags) #0 !dbg !346 {
entry:
  %retval = alloca i32, align 4
  %path.addr = alloca i8*, align 8
  %a_eno.addr = alloca i32*, align 8
  %a_estr.addr = alloca %struct.archive_string*, align 8
  %flags.addr = alloca i32, align 4
  %dest = alloca i8*, align 8
  %src = alloca i8*, align 8
  %separator = alloca i8, align 1
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !2906, metadata !399), !dbg !2907
  store i32* %a_eno, i32** %a_eno.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %a_eno.addr, metadata !2908, metadata !399), !dbg !2909
  store %struct.archive_string* %a_estr, %struct.archive_string** %a_estr.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string** %a_estr.addr, metadata !2910, metadata !399), !dbg !2911
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !2912, metadata !399), !dbg !2913
  call void @llvm.dbg.declare(metadata i8** %dest, metadata !2914, metadata !399), !dbg !2915
  call void @llvm.dbg.declare(metadata i8** %src, metadata !2916, metadata !399), !dbg !2917
  call void @llvm.dbg.declare(metadata i8* %separator, metadata !2918, metadata !399), !dbg !2919
  store i8 0, i8* %separator, align 1, !dbg !2919
  %0 = load i8*, i8** %path.addr, align 8, !dbg !2920
  store i8* %0, i8** %src, align 8, !dbg !2921
  store i8* %0, i8** %dest, align 8, !dbg !2922
  %1 = load i8*, i8** %src, align 8, !dbg !2923
  %2 = load i8, i8* %1, align 1, !dbg !2925
  %conv = sext i8 %2 to i32, !dbg !2925
  %cmp = icmp eq i32 %conv, 0, !dbg !2926
  br i1 %cmp, label %if.then, label %if.end, !dbg !2927

if.then:                                          ; preds = %entry
  %3 = load i32*, i32** %a_eno.addr, align 8, !dbg !2928
  %4 = load %struct.archive_string*, %struct.archive_string** %a_estr.addr, align 8, !dbg !2930
  call void @fsobj_error(i32* %3, %struct.archive_string* %4, i32 -1, i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.12, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.13, i32 0, i32 0)), !dbg !2931
  store i32 -25, i32* %retval, align 4, !dbg !2932
  br label %return, !dbg !2932

if.end:                                           ; preds = %entry
  %5 = load i8*, i8** %src, align 8, !dbg !2933
  %6 = load i8, i8* %5, align 1, !dbg !2935
  %conv2 = sext i8 %6 to i32, !dbg !2935
  %cmp3 = icmp eq i32 %conv2, 47, !dbg !2936
  br i1 %cmp3, label %if.then5, label %if.end8, !dbg !2937

if.then5:                                         ; preds = %if.end
  %7 = load i32, i32* %flags.addr, align 4, !dbg !2938
  %and = and i32 %7, 65536, !dbg !2941
  %tobool = icmp ne i32 %and, 0, !dbg !2941
  br i1 %tobool, label %if.then6, label %if.end7, !dbg !2942

if.then6:                                         ; preds = %if.then5
  %8 = load i32*, i32** %a_eno.addr, align 8, !dbg !2943
  %9 = load %struct.archive_string*, %struct.archive_string** %a_estr.addr, align 8, !dbg !2945
  call void @fsobj_error(i32* %8, %struct.archive_string* %9, i32 -1, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.14, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.15, i32 0, i32 0)), !dbg !2946
  store i32 -25, i32* %retval, align 4, !dbg !2947
  br label %return, !dbg !2947

if.end7:                                          ; preds = %if.then5
  %10 = load i8*, i8** %src, align 8, !dbg !2948
  %incdec.ptr = getelementptr inbounds i8, i8* %10, i32 1, !dbg !2948
  store i8* %incdec.ptr, i8** %src, align 8, !dbg !2948
  %11 = load i8, i8* %10, align 1, !dbg !2949
  store i8 %11, i8* %separator, align 1, !dbg !2950
  br label %if.end8, !dbg !2951

if.end8:                                          ; preds = %if.end7, %if.end
  br label %for.cond, !dbg !2952

for.cond:                                         ; preds = %if.end78, %if.then35, %if.then17, %if.end8
  %12 = load i8*, i8** %src, align 8, !dbg !2953
  %arrayidx = getelementptr inbounds i8, i8* %12, i64 0, !dbg !2953
  %13 = load i8, i8* %arrayidx, align 1, !dbg !2953
  %conv9 = sext i8 %13 to i32, !dbg !2953
  %cmp10 = icmp eq i32 %conv9, 0, !dbg !2958
  br i1 %cmp10, label %if.then12, label %if.else, !dbg !2959

if.then12:                                        ; preds = %for.cond
  br label %for.end, !dbg !2960

if.else:                                          ; preds = %for.cond
  %14 = load i8*, i8** %src, align 8, !dbg !2962
  %arrayidx13 = getelementptr inbounds i8, i8* %14, i64 0, !dbg !2962
  %15 = load i8, i8* %arrayidx13, align 1, !dbg !2962
  %conv14 = sext i8 %15 to i32, !dbg !2962
  %cmp15 = icmp eq i32 %conv14, 47, !dbg !2964
  br i1 %cmp15, label %if.then17, label %if.else19, !dbg !2965

if.then17:                                        ; preds = %if.else
  %16 = load i8*, i8** %src, align 8, !dbg !2966
  %incdec.ptr18 = getelementptr inbounds i8, i8* %16, i32 1, !dbg !2966
  store i8* %incdec.ptr18, i8** %src, align 8, !dbg !2966
  br label %for.cond, !dbg !2968

if.else19:                                        ; preds = %if.else
  %17 = load i8*, i8** %src, align 8, !dbg !2969
  %arrayidx20 = getelementptr inbounds i8, i8* %17, i64 0, !dbg !2969
  %18 = load i8, i8* %arrayidx20, align 1, !dbg !2969
  %conv21 = sext i8 %18 to i32, !dbg !2969
  %cmp22 = icmp eq i32 %conv21, 46, !dbg !2971
  br i1 %cmp22, label %if.then24, label %if.end59, !dbg !2972

if.then24:                                        ; preds = %if.else19
  %19 = load i8*, i8** %src, align 8, !dbg !2973
  %arrayidx25 = getelementptr inbounds i8, i8* %19, i64 1, !dbg !2973
  %20 = load i8, i8* %arrayidx25, align 1, !dbg !2973
  %conv26 = sext i8 %20 to i32, !dbg !2973
  %cmp27 = icmp eq i32 %conv26, 0, !dbg !2976
  br i1 %cmp27, label %if.then29, label %if.else30, !dbg !2977

if.then29:                                        ; preds = %if.then24
  br label %for.end, !dbg !2978

if.else30:                                        ; preds = %if.then24
  %21 = load i8*, i8** %src, align 8, !dbg !2980
  %arrayidx31 = getelementptr inbounds i8, i8* %21, i64 1, !dbg !2980
  %22 = load i8, i8* %arrayidx31, align 1, !dbg !2980
  %conv32 = sext i8 %22 to i32, !dbg !2980
  %cmp33 = icmp eq i32 %conv32, 47, !dbg !2982
  br i1 %cmp33, label %if.then35, label %if.else36, !dbg !2983

if.then35:                                        ; preds = %if.else30
  %23 = load i8*, i8** %src, align 8, !dbg !2984
  %add.ptr = getelementptr inbounds i8, i8* %23, i64 2, !dbg !2984
  store i8* %add.ptr, i8** %src, align 8, !dbg !2984
  br label %for.cond, !dbg !2986

if.else36:                                        ; preds = %if.else30
  %24 = load i8*, i8** %src, align 8, !dbg !2987
  %arrayidx37 = getelementptr inbounds i8, i8* %24, i64 1, !dbg !2987
  %25 = load i8, i8* %arrayidx37, align 1, !dbg !2987
  %conv38 = sext i8 %25 to i32, !dbg !2987
  %cmp39 = icmp eq i32 %conv38, 46, !dbg !2989
  br i1 %cmp39, label %if.then41, label %if.end56, !dbg !2990

if.then41:                                        ; preds = %if.else36
  %26 = load i8*, i8** %src, align 8, !dbg !2991
  %arrayidx42 = getelementptr inbounds i8, i8* %26, i64 2, !dbg !2991
  %27 = load i8, i8* %arrayidx42, align 1, !dbg !2991
  %conv43 = sext i8 %27 to i32, !dbg !2991
  %cmp44 = icmp eq i32 %conv43, 47, !dbg !2994
  br i1 %cmp44, label %if.then50, label %lor.lhs.false, !dbg !2995

lor.lhs.false:                                    ; preds = %if.then41
  %28 = load i8*, i8** %src, align 8, !dbg !2996
  %arrayidx46 = getelementptr inbounds i8, i8* %28, i64 2, !dbg !2996
  %29 = load i8, i8* %arrayidx46, align 1, !dbg !2996
  %conv47 = sext i8 %29 to i32, !dbg !2996
  %cmp48 = icmp eq i32 %conv47, 0, !dbg !2998
  br i1 %cmp48, label %if.then50, label %if.end55, !dbg !2999

if.then50:                                        ; preds = %lor.lhs.false, %if.then41
  %30 = load i32, i32* %flags.addr, align 4, !dbg !3000
  %and51 = and i32 %30, 512, !dbg !3003
  %tobool52 = icmp ne i32 %and51, 0, !dbg !3003
  br i1 %tobool52, label %if.then53, label %if.end54, !dbg !3004

if.then53:                                        ; preds = %if.then50
  %31 = load i32*, i32** %a_eno.addr, align 8, !dbg !3005
  %32 = load %struct.archive_string*, %struct.archive_string** %a_estr.addr, align 8, !dbg !3007
  call void @fsobj_error(i32* %31, %struct.archive_string* %32, i32 -1, i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.16, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.17, i32 0, i32 0)), !dbg !3008
  store i32 -25, i32* %retval, align 4, !dbg !3009
  br label %return, !dbg !3009

if.end54:                                         ; preds = %if.then50
  br label %if.end55, !dbg !3010

if.end55:                                         ; preds = %if.end54, %lor.lhs.false
  br label %if.end56, !dbg !3011

if.end56:                                         ; preds = %if.end55, %if.else36
  br label %if.end57

if.end57:                                         ; preds = %if.end56
  br label %if.end58

if.end58:                                         ; preds = %if.end57
  br label %if.end59, !dbg !3012

if.end59:                                         ; preds = %if.end58, %if.else19
  br label %if.end60

if.end60:                                         ; preds = %if.end59
  br label %if.end61

if.end61:                                         ; preds = %if.end60
  %33 = load i8, i8* %separator, align 1, !dbg !3013
  %tobool62 = icmp ne i8 %33, 0, !dbg !3013
  br i1 %tobool62, label %if.then63, label %if.end65, !dbg !3015

if.then63:                                        ; preds = %if.end61
  %34 = load i8*, i8** %dest, align 8, !dbg !3016
  %incdec.ptr64 = getelementptr inbounds i8, i8* %34, i32 1, !dbg !3016
  store i8* %incdec.ptr64, i8** %dest, align 8, !dbg !3016
  store i8 47, i8* %34, align 1, !dbg !3017
  br label %if.end65, !dbg !3018

if.end65:                                         ; preds = %if.then63, %if.end61
  br label %while.cond, !dbg !3019

while.cond:                                       ; preds = %while.body, %if.end65
  %35 = load i8*, i8** %src, align 8, !dbg !3020
  %36 = load i8, i8* %35, align 1, !dbg !3022
  %conv66 = sext i8 %36 to i32, !dbg !3022
  %cmp67 = icmp ne i32 %conv66, 0, !dbg !3023
  br i1 %cmp67, label %land.rhs, label %land.end, !dbg !3024

land.rhs:                                         ; preds = %while.cond
  %37 = load i8*, i8** %src, align 8, !dbg !3025
  %38 = load i8, i8* %37, align 1, !dbg !3027
  %conv69 = sext i8 %38 to i32, !dbg !3027
  %cmp70 = icmp ne i32 %conv69, 47, !dbg !3028
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond
  %39 = phi i1 [ false, %while.cond ], [ %cmp70, %land.rhs ]
  br i1 %39, label %while.body, label %while.end, !dbg !3029

while.body:                                       ; preds = %land.end
  %40 = load i8*, i8** %src, align 8, !dbg !3031
  %incdec.ptr72 = getelementptr inbounds i8, i8* %40, i32 1, !dbg !3031
  store i8* %incdec.ptr72, i8** %src, align 8, !dbg !3031
  %41 = load i8, i8* %40, align 1, !dbg !3033
  %42 = load i8*, i8** %dest, align 8, !dbg !3034
  %incdec.ptr73 = getelementptr inbounds i8, i8* %42, i32 1, !dbg !3034
  store i8* %incdec.ptr73, i8** %dest, align 8, !dbg !3034
  store i8 %41, i8* %42, align 1, !dbg !3035
  br label %while.cond, !dbg !3036

while.end:                                        ; preds = %land.end
  %43 = load i8*, i8** %src, align 8, !dbg !3038
  %44 = load i8, i8* %43, align 1, !dbg !3040
  %conv74 = sext i8 %44 to i32, !dbg !3040
  %cmp75 = icmp eq i32 %conv74, 0, !dbg !3041
  br i1 %cmp75, label %if.then77, label %if.end78, !dbg !3042

if.then77:                                        ; preds = %while.end
  br label %for.end, !dbg !3043

if.end78:                                         ; preds = %while.end
  %45 = load i8*, i8** %src, align 8, !dbg !3044
  %incdec.ptr79 = getelementptr inbounds i8, i8* %45, i32 1, !dbg !3044
  store i8* %incdec.ptr79, i8** %src, align 8, !dbg !3044
  %46 = load i8, i8* %45, align 1, !dbg !3045
  store i8 %46, i8* %separator, align 1, !dbg !3046
  br label %for.cond, !dbg !3047

for.end:                                          ; preds = %if.then77, %if.then29, %if.then12
  %47 = load i8*, i8** %dest, align 8, !dbg !3049
  %48 = load i8*, i8** %path.addr, align 8, !dbg !3051
  %cmp80 = icmp eq i8* %47, %48, !dbg !3052
  br i1 %cmp80, label %if.then82, label %if.end89, !dbg !3053

if.then82:                                        ; preds = %for.end
  %49 = load i8, i8* %separator, align 1, !dbg !3054
  %tobool83 = icmp ne i8 %49, 0, !dbg !3054
  br i1 %tobool83, label %if.then84, label %if.else86, !dbg !3057

if.then84:                                        ; preds = %if.then82
  %50 = load i8*, i8** %dest, align 8, !dbg !3058
  %incdec.ptr85 = getelementptr inbounds i8, i8* %50, i32 1, !dbg !3058
  store i8* %incdec.ptr85, i8** %dest, align 8, !dbg !3058
  store i8 47, i8* %50, align 1, !dbg !3059
  br label %if.end88, !dbg !3060

if.else86:                                        ; preds = %if.then82
  %51 = load i8*, i8** %dest, align 8, !dbg !3061
  %incdec.ptr87 = getelementptr inbounds i8, i8* %51, i32 1, !dbg !3061
  store i8* %incdec.ptr87, i8** %dest, align 8, !dbg !3061
  store i8 46, i8* %51, align 1, !dbg !3062
  br label %if.end88

if.end88:                                         ; preds = %if.else86, %if.then84
  br label %if.end89, !dbg !3063

if.end89:                                         ; preds = %if.end88, %for.end
  %52 = load i8*, i8** %dest, align 8, !dbg !3064
  store i8 0, i8* %52, align 1, !dbg !3065
  store i32 0, i32* %retval, align 4, !dbg !3066
  br label %return, !dbg !3066

return:                                           ; preds = %if.end89, %if.then53, %if.then6, %if.then
  %53 = load i32, i32* %retval, align 4, !dbg !3067
  ret i32 %53, !dbg !3067
}

; Function Attrs: nounwind uwtable
define internal void @fsobj_error(i32* %a_eno, %struct.archive_string* %a_estr, i32 %err, i8* %errstr, i8* %path) #0 !dbg !351 {
entry:
  %a_eno.addr = alloca i32*, align 8
  %a_estr.addr = alloca %struct.archive_string*, align 8
  %err.addr = alloca i32, align 4
  %errstr.addr = alloca i8*, align 8
  %path.addr = alloca i8*, align 8
  store i32* %a_eno, i32** %a_eno.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %a_eno.addr, metadata !3068, metadata !399), !dbg !3069
  store %struct.archive_string* %a_estr, %struct.archive_string** %a_estr.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string** %a_estr.addr, metadata !3070, metadata !399), !dbg !3071
  store i32 %err, i32* %err.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %err.addr, metadata !3072, metadata !399), !dbg !3073
  store i8* %errstr, i8** %errstr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %errstr.addr, metadata !3074, metadata !399), !dbg !3075
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !3076, metadata !399), !dbg !3077
  %0 = load i32*, i32** %a_eno.addr, align 8, !dbg !3078
  %tobool = icmp ne i32* %0, null, !dbg !3078
  br i1 %tobool, label %if.then, label %if.end, !dbg !3080

if.then:                                          ; preds = %entry
  %1 = load i32, i32* %err.addr, align 4, !dbg !3081
  %2 = load i32*, i32** %a_eno.addr, align 8, !dbg !3082
  store i32 %1, i32* %2, align 4, !dbg !3083
  br label %if.end, !dbg !3084

if.end:                                           ; preds = %if.then, %entry
  %3 = load %struct.archive_string*, %struct.archive_string** %a_estr.addr, align 8, !dbg !3085
  %tobool1 = icmp ne %struct.archive_string* %3, null, !dbg !3085
  br i1 %tobool1, label %if.then2, label %if.end3, !dbg !3087

if.then2:                                         ; preds = %if.end
  %4 = load %struct.archive_string*, %struct.archive_string** %a_estr.addr, align 8, !dbg !3088
  %5 = load i8*, i8** %errstr.addr, align 8, !dbg !3089
  %6 = load i8*, i8** %path.addr, align 8, !dbg !3090
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %4, i8* %5, i8* %6), !dbg !3091
  br label %if.end3, !dbg !3091

if.end3:                                          ; preds = %if.then2, %if.end
  ret void, !dbg !3092
}

declare void @archive_string_sprintf(%struct.archive_string*, i8*, ...) #2

; Function Attrs: nounwind uwtable
define internal i32 @check_symlinks_fsobj(i8* %path, i32* %a_eno, %struct.archive_string* %a_estr, i32 %flags) #0 !dbg !355 {
entry:
  %retval = alloca i32, align 4
  %path.addr = alloca i8*, align 8
  %a_eno.addr = alloca i32*, align 8
  %a_estr.addr = alloca %struct.archive_string*, align 8
  %flags.addr = alloca i32, align 4
  %res = alloca i32, align 4
  %tail = alloca i8*, align 8
  %head = alloca i8*, align 8
  %last = alloca i32, align 4
  %c = alloca i8, align 1
  %r = alloca i32, align 4
  %st = alloca %struct.stat, align 8
  %restore_pwd = alloca i32, align 4
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !3093, metadata !399), !dbg !3094
  store i32* %a_eno, i32** %a_eno.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %a_eno.addr, metadata !3095, metadata !399), !dbg !3096
  store %struct.archive_string* %a_estr, %struct.archive_string** %a_estr.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string** %a_estr.addr, metadata !3097, metadata !399), !dbg !3098
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !3099, metadata !399), !dbg !3100
  call void @llvm.dbg.declare(metadata i32* %res, metadata !3101, metadata !399), !dbg !3102
  store i32 0, i32* %res, align 4, !dbg !3102
  call void @llvm.dbg.declare(metadata i8** %tail, metadata !3103, metadata !399), !dbg !3104
  call void @llvm.dbg.declare(metadata i8** %head, metadata !3105, metadata !399), !dbg !3106
  call void @llvm.dbg.declare(metadata i32* %last, metadata !3107, metadata !399), !dbg !3108
  call void @llvm.dbg.declare(metadata i8* %c, metadata !3109, metadata !399), !dbg !3110
  call void @llvm.dbg.declare(metadata i32* %r, metadata !3111, metadata !399), !dbg !3112
  call void @llvm.dbg.declare(metadata %struct.stat* %st, metadata !3113, metadata !399), !dbg !3114
  call void @llvm.dbg.declare(metadata i32* %restore_pwd, metadata !3115, metadata !399), !dbg !3116
  %0 = load i8*, i8** %path.addr, align 8, !dbg !3117
  %arrayidx = getelementptr inbounds i8, i8* %0, i64 0, !dbg !3117
  %1 = load i8, i8* %arrayidx, align 1, !dbg !3117
  %conv = sext i8 %1 to i32, !dbg !3117
  %cmp = icmp eq i32 %conv, 0, !dbg !3119
  br i1 %cmp, label %if.then, label %if.end, !dbg !3120

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !3121
  br label %return, !dbg !3121

if.end:                                           ; preds = %entry
  %call = call i32 (i8*, i32, ...) @open(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.18, i32 0, i32 0), i32 524288), !dbg !3122
  store i32 %call, i32* %restore_pwd, align 4, !dbg !3123
  %2 = load i32, i32* %restore_pwd, align 4, !dbg !3124
  call void @__archive_ensure_cloexec_flag(i32 %2), !dbg !3125
  %3 = load i32, i32* %restore_pwd, align 4, !dbg !3126
  %cmp2 = icmp slt i32 %3, 0, !dbg !3128
  br i1 %cmp2, label %if.then4, label %if.end5, !dbg !3129

if.then4:                                         ; preds = %if.end
  store i32 -30, i32* %retval, align 4, !dbg !3130
  br label %return, !dbg !3130

if.end5:                                          ; preds = %if.end
  %4 = load i8*, i8** %path.addr, align 8, !dbg !3131
  store i8* %4, i8** %head, align 8, !dbg !3132
  %5 = load i8*, i8** %path.addr, align 8, !dbg !3133
  store i8* %5, i8** %tail, align 8, !dbg !3134
  store i32 0, i32* %last, align 4, !dbg !3135
  %6 = load i8*, i8** %tail, align 8, !dbg !3136
  %7 = load i8*, i8** %path.addr, align 8, !dbg !3138
  %cmp6 = icmp eq i8* %6, %7, !dbg !3139
  br i1 %cmp6, label %land.lhs.true, label %if.end13, !dbg !3140

land.lhs.true:                                    ; preds = %if.end5
  %8 = load i8*, i8** %tail, align 8, !dbg !3141
  %arrayidx8 = getelementptr inbounds i8, i8* %8, i64 0, !dbg !3141
  %9 = load i8, i8* %arrayidx8, align 1, !dbg !3141
  %conv9 = sext i8 %9 to i32, !dbg !3141
  %cmp10 = icmp eq i32 %conv9, 47, !dbg !3143
  br i1 %cmp10, label %if.then12, label %if.end13, !dbg !3144

if.then12:                                        ; preds = %land.lhs.true
  %10 = load i8*, i8** %tail, align 8, !dbg !3145
  %incdec.ptr = getelementptr inbounds i8, i8* %10, i32 1, !dbg !3145
  store i8* %incdec.ptr, i8** %tail, align 8, !dbg !3145
  br label %if.end13, !dbg !3145

if.end13:                                         ; preds = %if.then12, %land.lhs.true, %if.end5
  br label %while.cond, !dbg !3146

while.cond:                                       ; preds = %if.end145, %if.end13
  %11 = load i32, i32* %last, align 4, !dbg !3147
  %tobool = icmp ne i32 %11, 0, !dbg !3149
  %lnot = xor i1 %tobool, true, !dbg !3149
  br i1 %lnot, label %while.body, label %while.end146, !dbg !3150

while.body:                                       ; preds = %while.cond
  br label %while.cond14, !dbg !3151

while.cond14:                                     ; preds = %while.body18, %while.body
  %12 = load i8*, i8** %tail, align 8, !dbg !3153
  %13 = load i8, i8* %12, align 1, !dbg !3155
  %conv15 = sext i8 %13 to i32, !dbg !3155
  %cmp16 = icmp eq i32 %conv15, 47, !dbg !3156
  br i1 %cmp16, label %while.body18, label %while.end, !dbg !3157

while.body18:                                     ; preds = %while.cond14
  %14 = load i8*, i8** %tail, align 8, !dbg !3158
  %incdec.ptr19 = getelementptr inbounds i8, i8* %14, i32 1, !dbg !3158
  store i8* %incdec.ptr19, i8** %tail, align 8, !dbg !3158
  br label %while.cond14, !dbg !3159

while.end:                                        ; preds = %while.cond14
  br label %while.cond20, !dbg !3161

while.cond20:                                     ; preds = %while.body27, %while.end
  %15 = load i8*, i8** %tail, align 8, !dbg !3162
  %16 = load i8, i8* %15, align 1, !dbg !3163
  %conv21 = sext i8 %16 to i32, !dbg !3163
  %cmp22 = icmp ne i32 %conv21, 0, !dbg !3164
  br i1 %cmp22, label %land.rhs, label %land.end, !dbg !3165

land.rhs:                                         ; preds = %while.cond20
  %17 = load i8*, i8** %tail, align 8, !dbg !3166
  %18 = load i8, i8* %17, align 1, !dbg !3167
  %conv24 = sext i8 %18 to i32, !dbg !3167
  %cmp25 = icmp ne i32 %conv24, 47, !dbg !3168
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond20
  %19 = phi i1 [ false, %while.cond20 ], [ %cmp25, %land.rhs ]
  br i1 %19, label %while.body27, label %while.end29, !dbg !3169

while.body27:                                     ; preds = %land.end
  %20 = load i8*, i8** %tail, align 8, !dbg !3171
  %incdec.ptr28 = getelementptr inbounds i8, i8* %20, i32 1, !dbg !3171
  store i8* %incdec.ptr28, i8** %tail, align 8, !dbg !3171
  br label %while.cond20, !dbg !3172

while.end29:                                      ; preds = %land.end
  %21 = load i8*, i8** %tail, align 8, !dbg !3174
  %arrayidx30 = getelementptr inbounds i8, i8* %21, i64 0, !dbg !3174
  %22 = load i8, i8* %arrayidx30, align 1, !dbg !3174
  %conv31 = sext i8 %22 to i32, !dbg !3174
  %cmp32 = icmp eq i32 %conv31, 0, !dbg !3175
  br i1 %cmp32, label %lor.end, label %lor.rhs, !dbg !3176

lor.rhs:                                          ; preds = %while.end29
  %23 = load i8*, i8** %tail, align 8, !dbg !3177
  %arrayidx34 = getelementptr inbounds i8, i8* %23, i64 0, !dbg !3177
  %24 = load i8, i8* %arrayidx34, align 1, !dbg !3177
  %conv35 = sext i8 %24 to i32, !dbg !3177
  %cmp36 = icmp eq i32 %conv35, 47, !dbg !3178
  br i1 %cmp36, label %land.rhs38, label %land.end43, !dbg !3179

land.rhs38:                                       ; preds = %lor.rhs
  %25 = load i8*, i8** %tail, align 8, !dbg !3180
  %arrayidx39 = getelementptr inbounds i8, i8* %25, i64 1, !dbg !3180
  %26 = load i8, i8* %arrayidx39, align 1, !dbg !3180
  %conv40 = sext i8 %26 to i32, !dbg !3180
  %cmp41 = icmp eq i32 %conv40, 0, !dbg !3181
  br label %land.end43

land.end43:                                       ; preds = %land.rhs38, %lor.rhs
  %27 = phi i1 [ false, %lor.rhs ], [ %cmp41, %land.rhs38 ]
  br label %lor.end, !dbg !3182

lor.end:                                          ; preds = %land.end43, %while.end29
  %28 = phi i1 [ true, %while.end29 ], [ %27, %land.end43 ]
  %lor.ext = zext i1 %28 to i32, !dbg !3183
  store i32 %lor.ext, i32* %last, align 4, !dbg !3184
  %29 = load i8*, i8** %tail, align 8, !dbg !3185
  %arrayidx44 = getelementptr inbounds i8, i8* %29, i64 0, !dbg !3185
  %30 = load i8, i8* %arrayidx44, align 1, !dbg !3185
  store i8 %30, i8* %c, align 1, !dbg !3186
  %31 = load i8*, i8** %tail, align 8, !dbg !3187
  %arrayidx45 = getelementptr inbounds i8, i8* %31, i64 0, !dbg !3187
  store i8 0, i8* %arrayidx45, align 1, !dbg !3188
  %32 = load i8*, i8** %head, align 8, !dbg !3189
  %call46 = call i32 @lstat(i8* %32, %struct.stat* %st) #7, !dbg !3190
  store i32 %call46, i32* %r, align 4, !dbg !3191
  %33 = load i32, i32* %r, align 4, !dbg !3192
  %cmp47 = icmp ne i32 %33, 0, !dbg !3194
  br i1 %cmp47, label %if.then49, label %if.else56, !dbg !3195

if.then49:                                        ; preds = %lor.end
  %34 = load i8, i8* %c, align 1, !dbg !3196
  %35 = load i8*, i8** %tail, align 8, !dbg !3198
  %arrayidx50 = getelementptr inbounds i8, i8* %35, i64 0, !dbg !3198
  store i8 %34, i8* %arrayidx50, align 1, !dbg !3199
  %call51 = call i32* @__errno_location() #1, !dbg !3200
  %36 = load i32, i32* %call51, align 4, !dbg !3200
  %cmp52 = icmp eq i32 %36, 2, !dbg !3202
  br i1 %cmp52, label %if.then54, label %if.else, !dbg !3203

if.then54:                                        ; preds = %if.then49
  br label %while.end146, !dbg !3204

if.else:                                          ; preds = %if.then49
  %37 = load i32*, i32** %a_eno.addr, align 8, !dbg !3206
  %38 = load %struct.archive_string*, %struct.archive_string** %a_estr.addr, align 8, !dbg !3208
  %call55 = call i32* @__errno_location() #1, !dbg !3209
  %39 = load i32, i32* %call55, align 4, !dbg !3209
  %40 = load i8*, i8** %path.addr, align 8, !dbg !3210
  call void @fsobj_error(i32* %37, %struct.archive_string* %38, i32 %39, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.19, i32 0, i32 0), i8* %40), !dbg !3211
  store i32 -25, i32* %res, align 4, !dbg !3213
  br label %while.end146, !dbg !3214

if.else56:                                        ; preds = %lor.end
  %st_mode = getelementptr inbounds %struct.stat, %struct.stat* %st, i32 0, i32 3, !dbg !3215
  %41 = load i32, i32* %st_mode, align 8, !dbg !3215
  %and = and i32 %41, 61440, !dbg !3215
  %cmp57 = icmp eq i32 %and, 16384, !dbg !3215
  br i1 %cmp57, label %if.then59, label %if.else70, !dbg !3217

if.then59:                                        ; preds = %if.else56
  %42 = load i32, i32* %last, align 4, !dbg !3218
  %tobool60 = icmp ne i32 %42, 0, !dbg !3218
  br i1 %tobool60, label %if.end69, label %if.then61, !dbg !3221

if.then61:                                        ; preds = %if.then59
  %43 = load i8*, i8** %head, align 8, !dbg !3222
  %call62 = call i32 @chdir(i8* %43) #7, !dbg !3225
  %cmp63 = icmp ne i32 %call62, 0, !dbg !3226
  br i1 %cmp63, label %if.then65, label %if.end68, !dbg !3227

if.then65:                                        ; preds = %if.then61
  %44 = load i8, i8* %c, align 1, !dbg !3228
  %45 = load i8*, i8** %tail, align 8, !dbg !3230
  %arrayidx66 = getelementptr inbounds i8, i8* %45, i64 0, !dbg !3230
  store i8 %44, i8* %arrayidx66, align 1, !dbg !3231
  %46 = load i32*, i32** %a_eno.addr, align 8, !dbg !3232
  %47 = load %struct.archive_string*, %struct.archive_string** %a_estr.addr, align 8, !dbg !3233
  %call67 = call i32* @__errno_location() #1, !dbg !3234
  %48 = load i32, i32* %call67, align 4, !dbg !3234
  %49 = load i8*, i8** %path.addr, align 8, !dbg !3235
  call void @fsobj_error(i32* %46, %struct.archive_string* %47, i32 %48, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.20, i32 0, i32 0), i8* %49), !dbg !3236
  store i32 -30, i32* %res, align 4, !dbg !3238
  br label %while.end146, !dbg !3239

if.end68:                                         ; preds = %if.then61
  %50 = load i8*, i8** %tail, align 8, !dbg !3240
  %add.ptr = getelementptr inbounds i8, i8* %50, i64 1, !dbg !3241
  store i8* %add.ptr, i8** %head, align 8, !dbg !3242
  br label %if.end69, !dbg !3243

if.end69:                                         ; preds = %if.end68, %if.then59
  br label %if.end136, !dbg !3244

if.else70:                                        ; preds = %if.else56
  %st_mode71 = getelementptr inbounds %struct.stat, %struct.stat* %st, i32 0, i32 3, !dbg !3245
  %51 = load i32, i32* %st_mode71, align 8, !dbg !3245
  %and72 = and i32 %51, 61440, !dbg !3245
  %cmp73 = icmp eq i32 %and72, 40960, !dbg !3245
  br i1 %cmp73, label %if.then75, label %if.end135, !dbg !3245

if.then75:                                        ; preds = %if.else70
  %52 = load i32, i32* %last, align 4, !dbg !3248
  %tobool76 = icmp ne i32 %52, 0, !dbg !3248
  br i1 %tobool76, label %if.then77, label %if.else85, !dbg !3251

if.then77:                                        ; preds = %if.then75
  %53 = load i8*, i8** %head, align 8, !dbg !3252
  %call78 = call i32 @unlink(i8* %53) #7, !dbg !3255
  %tobool79 = icmp ne i32 %call78, 0, !dbg !3255
  br i1 %tobool79, label %if.then80, label %if.end83, !dbg !3256

if.then80:                                        ; preds = %if.then77
  %54 = load i8, i8* %c, align 1, !dbg !3257
  %55 = load i8*, i8** %tail, align 8, !dbg !3259
  %arrayidx81 = getelementptr inbounds i8, i8* %55, i64 0, !dbg !3259
  store i8 %54, i8* %arrayidx81, align 1, !dbg !3260
  %56 = load i32*, i32** %a_eno.addr, align 8, !dbg !3261
  %57 = load %struct.archive_string*, %struct.archive_string** %a_estr.addr, align 8, !dbg !3262
  %call82 = call i32* @__errno_location() #1, !dbg !3263
  %58 = load i32, i32* %call82, align 4, !dbg !3263
  %59 = load i8*, i8** %path.addr, align 8, !dbg !3264
  call void @fsobj_error(i32* %56, %struct.archive_string* %57, i32 %58, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.21, i32 0, i32 0), i8* %59), !dbg !3265
  store i32 -25, i32* %res, align 4, !dbg !3267
  br label %while.end146, !dbg !3268

if.end83:                                         ; preds = %if.then77
  %60 = load i8, i8* %c, align 1, !dbg !3269
  %61 = load i8*, i8** %tail, align 8, !dbg !3270
  %arrayidx84 = getelementptr inbounds i8, i8* %61, i64 0, !dbg !3270
  store i8 %60, i8* %arrayidx84, align 1, !dbg !3271
  store i32 0, i32* %res, align 4, !dbg !3272
  br label %while.end146, !dbg !3273

if.else85:                                        ; preds = %if.then75
  %62 = load i32, i32* %flags.addr, align 4, !dbg !3274
  %and86 = and i32 %62, 16, !dbg !3276
  %tobool87 = icmp ne i32 %and86, 0, !dbg !3276
  br i1 %tobool87, label %if.then88, label %if.else96, !dbg !3277

if.then88:                                        ; preds = %if.else85
  %63 = load i8*, i8** %head, align 8, !dbg !3278
  %call89 = call i32 @unlink(i8* %63) #7, !dbg !3281
  %cmp90 = icmp ne i32 %call89, 0, !dbg !3282
  br i1 %cmp90, label %if.then92, label %if.end94, !dbg !3283

if.then92:                                        ; preds = %if.then88
  %64 = load i8, i8* %c, align 1, !dbg !3284
  %65 = load i8*, i8** %tail, align 8, !dbg !3286
  %arrayidx93 = getelementptr inbounds i8, i8* %65, i64 0, !dbg !3286
  store i8 %64, i8* %arrayidx93, align 1, !dbg !3287
  %66 = load i32*, i32** %a_eno.addr, align 8, !dbg !3288
  %67 = load %struct.archive_string*, %struct.archive_string** %a_estr.addr, align 8, !dbg !3289
  %68 = load i8*, i8** %path.addr, align 8, !dbg !3290
  call void @fsobj_error(i32* %66, %struct.archive_string* %67, i32 0, i8* getelementptr inbounds ([37 x i8], [37 x i8]* @.str.22, i32 0, i32 0), i8* %68), !dbg !3291
  store i32 -25, i32* %res, align 4, !dbg !3292
  br label %while.end146, !dbg !3293

if.end94:                                         ; preds = %if.then88
  %69 = load i8, i8* %c, align 1, !dbg !3294
  %70 = load i8*, i8** %tail, align 8, !dbg !3295
  %arrayidx95 = getelementptr inbounds i8, i8* %70, i64 0, !dbg !3295
  store i8 %69, i8* %arrayidx95, align 1, !dbg !3296
  br label %if.end133, !dbg !3297

if.else96:                                        ; preds = %if.else85
  %71 = load i32, i32* %flags.addr, align 4, !dbg !3298
  %and97 = and i32 %71, 256, !dbg !3301
  %cmp98 = icmp eq i32 %and97, 0, !dbg !3302
  br i1 %cmp98, label %if.then100, label %if.else130, !dbg !3303

if.then100:                                       ; preds = %if.else96
  %72 = load i8*, i8** %head, align 8, !dbg !3304
  %call101 = call i32 @stat(i8* %72, %struct.stat* %st) #7, !dbg !3306
  store i32 %call101, i32* %r, align 4, !dbg !3307
  %73 = load i32, i32* %r, align 4, !dbg !3308
  %cmp102 = icmp ne i32 %73, 0, !dbg !3310
  br i1 %cmp102, label %if.then104, label %if.else112, !dbg !3311

if.then104:                                       ; preds = %if.then100
  %74 = load i8, i8* %c, align 1, !dbg !3312
  %75 = load i8*, i8** %tail, align 8, !dbg !3314
  %arrayidx105 = getelementptr inbounds i8, i8* %75, i64 0, !dbg !3314
  store i8 %74, i8* %arrayidx105, align 1, !dbg !3315
  %call106 = call i32* @__errno_location() #1, !dbg !3316
  %76 = load i32, i32* %call106, align 4, !dbg !3316
  %cmp107 = icmp eq i32 %76, 2, !dbg !3318
  br i1 %cmp107, label %if.then109, label %if.else110, !dbg !3319

if.then109:                                       ; preds = %if.then104
  br label %while.end146, !dbg !3320

if.else110:                                       ; preds = %if.then104
  %77 = load i32*, i32** %a_eno.addr, align 8, !dbg !3322
  %78 = load %struct.archive_string*, %struct.archive_string** %a_estr.addr, align 8, !dbg !3324
  %call111 = call i32* @__errno_location() #1, !dbg !3325
  %79 = load i32, i32* %call111, align 4, !dbg !3325
  %80 = load i8*, i8** %path.addr, align 8, !dbg !3326
  call void @fsobj_error(i32* %77, %struct.archive_string* %78, i32 %79, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.19, i32 0, i32 0), i8* %80), !dbg !3327
  store i32 -25, i32* %res, align 4, !dbg !3328
  br label %while.end146, !dbg !3329

if.else112:                                       ; preds = %if.then100
  %st_mode113 = getelementptr inbounds %struct.stat, %struct.stat* %st, i32 0, i32 3, !dbg !3330
  %81 = load i32, i32* %st_mode113, align 8, !dbg !3330
  %and114 = and i32 %81, 61440, !dbg !3330
  %cmp115 = icmp eq i32 %and114, 16384, !dbg !3330
  br i1 %cmp115, label %if.then117, label %if.else126, !dbg !3332

if.then117:                                       ; preds = %if.else112
  %82 = load i8*, i8** %head, align 8, !dbg !3333
  %call118 = call i32 @chdir(i8* %82) #7, !dbg !3336
  %cmp119 = icmp ne i32 %call118, 0, !dbg !3337
  br i1 %cmp119, label %if.then121, label %if.end124, !dbg !3338

if.then121:                                       ; preds = %if.then117
  %83 = load i8, i8* %c, align 1, !dbg !3339
  %84 = load i8*, i8** %tail, align 8, !dbg !3341
  %arrayidx122 = getelementptr inbounds i8, i8* %84, i64 0, !dbg !3341
  store i8 %83, i8* %arrayidx122, align 1, !dbg !3342
  %85 = load i32*, i32** %a_eno.addr, align 8, !dbg !3343
  %86 = load %struct.archive_string*, %struct.archive_string** %a_estr.addr, align 8, !dbg !3344
  %call123 = call i32* @__errno_location() #1, !dbg !3345
  %87 = load i32, i32* %call123, align 4, !dbg !3345
  %88 = load i8*, i8** %path.addr, align 8, !dbg !3346
  call void @fsobj_error(i32* %85, %struct.archive_string* %86, i32 %87, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.20, i32 0, i32 0), i8* %88), !dbg !3347
  store i32 -30, i32* %res, align 4, !dbg !3348
  br label %while.end146, !dbg !3349

if.end124:                                        ; preds = %if.then117
  %89 = load i8*, i8** %tail, align 8, !dbg !3350
  %add.ptr125 = getelementptr inbounds i8, i8* %89, i64 1, !dbg !3351
  store i8* %add.ptr125, i8** %head, align 8, !dbg !3352
  br label %if.end128, !dbg !3353

if.else126:                                       ; preds = %if.else112
  %90 = load i8, i8* %c, align 1, !dbg !3354
  %91 = load i8*, i8** %tail, align 8, !dbg !3356
  %arrayidx127 = getelementptr inbounds i8, i8* %91, i64 0, !dbg !3356
  store i8 %90, i8* %arrayidx127, align 1, !dbg !3357
  %92 = load i32*, i32** %a_eno.addr, align 8, !dbg !3358
  %93 = load %struct.archive_string*, %struct.archive_string** %a_estr.addr, align 8, !dbg !3359
  %94 = load i8*, i8** %path.addr, align 8, !dbg !3360
  call void @fsobj_error(i32* %92, %struct.archive_string* %93, i32 0, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.23, i32 0, i32 0), i8* %94), !dbg !3361
  store i32 -25, i32* %res, align 4, !dbg !3362
  br label %while.end146, !dbg !3363

if.end128:                                        ; preds = %if.end124
  br label %if.end129

if.end129:                                        ; preds = %if.end128
  br label %if.end132, !dbg !3364

if.else130:                                       ; preds = %if.else96
  %95 = load i8, i8* %c, align 1, !dbg !3365
  %96 = load i8*, i8** %tail, align 8, !dbg !3367
  %arrayidx131 = getelementptr inbounds i8, i8* %96, i64 0, !dbg !3367
  store i8 %95, i8* %arrayidx131, align 1, !dbg !3368
  %97 = load i32*, i32** %a_eno.addr, align 8, !dbg !3369
  %98 = load %struct.archive_string*, %struct.archive_string** %a_estr.addr, align 8, !dbg !3370
  %99 = load i8*, i8** %path.addr, align 8, !dbg !3371
  call void @fsobj_error(i32* %97, %struct.archive_string* %98, i32 0, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.23, i32 0, i32 0), i8* %99), !dbg !3372
  store i32 -25, i32* %res, align 4, !dbg !3373
  br label %while.end146, !dbg !3374

if.end132:                                        ; preds = %if.end129
  br label %if.end133

if.end133:                                        ; preds = %if.end132, %if.end94
  br label %if.end134

if.end134:                                        ; preds = %if.end133
  br label %if.end135, !dbg !3375

if.end135:                                        ; preds = %if.end134, %if.else70
  br label %if.end136

if.end136:                                        ; preds = %if.end135, %if.end69
  br label %if.end137

if.end137:                                        ; preds = %if.end136
  %100 = load i8, i8* %c, align 1, !dbg !3376
  %101 = load i8*, i8** %tail, align 8, !dbg !3377
  %arrayidx138 = getelementptr inbounds i8, i8* %101, i64 0, !dbg !3377
  store i8 %100, i8* %arrayidx138, align 1, !dbg !3378
  %102 = load i8*, i8** %tail, align 8, !dbg !3379
  %arrayidx139 = getelementptr inbounds i8, i8* %102, i64 0, !dbg !3379
  %103 = load i8, i8* %arrayidx139, align 1, !dbg !3379
  %conv140 = sext i8 %103 to i32, !dbg !3379
  %cmp141 = icmp ne i32 %conv140, 0, !dbg !3381
  br i1 %cmp141, label %if.then143, label %if.end145, !dbg !3382

if.then143:                                       ; preds = %if.end137
  %104 = load i8*, i8** %tail, align 8, !dbg !3383
  %incdec.ptr144 = getelementptr inbounds i8, i8* %104, i32 1, !dbg !3383
  store i8* %incdec.ptr144, i8** %tail, align 8, !dbg !3383
  br label %if.end145, !dbg !3384

if.end145:                                        ; preds = %if.then143, %if.end137
  br label %while.cond, !dbg !3385

while.end146:                                     ; preds = %if.else130, %if.else126, %if.then121, %if.else110, %if.then109, %if.then92, %if.end83, %if.then80, %if.then65, %if.else, %if.then54, %while.cond
  %105 = load i8, i8* %c, align 1, !dbg !3387
  %106 = load i8*, i8** %tail, align 8, !dbg !3388
  %arrayidx147 = getelementptr inbounds i8, i8* %106, i64 0, !dbg !3388
  store i8 %105, i8* %arrayidx147, align 1, !dbg !3389
  %107 = load i32, i32* %restore_pwd, align 4, !dbg !3390
  %cmp148 = icmp sge i32 %107, 0, !dbg !3392
  br i1 %cmp148, label %if.then150, label %if.end162, !dbg !3393

if.then150:                                       ; preds = %while.end146
  %108 = load i32, i32* %restore_pwd, align 4, !dbg !3394
  %call151 = call i32 @fchdir(i32 %108) #7, !dbg !3396
  store i32 %call151, i32* %r, align 4, !dbg !3397
  %109 = load i32, i32* %r, align 4, !dbg !3398
  %cmp152 = icmp ne i32 %109, 0, !dbg !3400
  br i1 %cmp152, label %if.then154, label %if.end156, !dbg !3401

if.then154:                                       ; preds = %if.then150
  %110 = load i32*, i32** %a_eno.addr, align 8, !dbg !3402
  %111 = load %struct.archive_string*, %struct.archive_string** %a_estr.addr, align 8, !dbg !3404
  %call155 = call i32* @__errno_location() #1, !dbg !3405
  %112 = load i32, i32* %call155, align 4, !dbg !3405
  call void @fsobj_error(i32* %110, %struct.archive_string* %111, i32 %112, i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.10, i32 0, i32 0), i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.24, i32 0, i32 0)), !dbg !3406
  br label %if.end156, !dbg !3408

if.end156:                                        ; preds = %if.then154, %if.then150
  %113 = load i32, i32* %restore_pwd, align 4, !dbg !3409
  %call157 = call i32 @close(i32 %113), !dbg !3410
  store i32 -1, i32* %restore_pwd, align 4, !dbg !3411
  %114 = load i32, i32* %r, align 4, !dbg !3412
  %cmp158 = icmp ne i32 %114, 0, !dbg !3414
  br i1 %cmp158, label %if.then160, label %if.end161, !dbg !3415

if.then160:                                       ; preds = %if.end156
  store i32 -30, i32* %res, align 4, !dbg !3416
  br label %if.end161, !dbg !3418

if.end161:                                        ; preds = %if.then160, %if.end156
  br label %if.end162, !dbg !3419

if.end162:                                        ; preds = %if.end161, %while.end146
  %115 = load i32, i32* %res, align 4, !dbg !3420
  store i32 %115, i32* %retval, align 4, !dbg !3421
  br label %return, !dbg !3421

return:                                           ; preds = %if.end162, %if.then4, %if.then
  %116 = load i32, i32* %retval, align 4, !dbg !3422
  ret i32 %116, !dbg !3422
}

; Function Attrs: nounwind
declare i32 @lstat(i8*, %struct.stat*) #3

; Function Attrs: nounwind
declare i32 @chdir(i8*) #3

; Function Attrs: nounwind
declare i32 @unlink(i8*) #3

; Function Attrs: nounwind
declare i32 @stat(i8*, %struct.stat*) #3

; Function Attrs: nounwind uwtable
define internal i32 @create_dir(%struct.archive_write_disk* %a, i8* %path) #0 !dbg !359 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write_disk*, align 8
  %path.addr = alloca i8*, align 8
  %st = alloca %struct.stat, align 8
  %le = alloca %struct.fixup_entry*, align 8
  %slash = alloca i8*, align 8
  %base = alloca i8*, align 8
  %mode_final = alloca i32, align 4
  %mode = alloca i32, align 4
  %r = alloca i32, align 4
  store %struct.archive_write_disk* %a, %struct.archive_write_disk** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_disk** %a.addr, metadata !3423, metadata !399), !dbg !3424
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !3425, metadata !399), !dbg !3426
  call void @llvm.dbg.declare(metadata %struct.stat* %st, metadata !3427, metadata !399), !dbg !3428
  call void @llvm.dbg.declare(metadata %struct.fixup_entry** %le, metadata !3429, metadata !399), !dbg !3430
  call void @llvm.dbg.declare(metadata i8** %slash, metadata !3431, metadata !399), !dbg !3432
  call void @llvm.dbg.declare(metadata i8** %base, metadata !3433, metadata !399), !dbg !3434
  call void @llvm.dbg.declare(metadata i32* %mode_final, metadata !3435, metadata !399), !dbg !3436
  call void @llvm.dbg.declare(metadata i32* %mode, metadata !3437, metadata !399), !dbg !3438
  call void @llvm.dbg.declare(metadata i32* %r, metadata !3439, metadata !399), !dbg !3440
  %0 = load i8*, i8** %path.addr, align 8, !dbg !3441
  %call = call i8* @strrchr(i8* %0, i32 47) #8, !dbg !3442
  store i8* %call, i8** %slash, align 8, !dbg !3443
  %1 = load i8*, i8** %slash, align 8, !dbg !3444
  %cmp = icmp eq i8* %1, null, !dbg !3446
  br i1 %cmp, label %if.then, label %if.else, !dbg !3447

if.then:                                          ; preds = %entry
  %2 = load i8*, i8** %path.addr, align 8, !dbg !3448
  store i8* %2, i8** %base, align 8, !dbg !3449
  br label %if.end, !dbg !3450

if.else:                                          ; preds = %entry
  %3 = load i8*, i8** %slash, align 8, !dbg !3451
  %add.ptr = getelementptr inbounds i8, i8* %3, i64 1, !dbg !3452
  store i8* %add.ptr, i8** %base, align 8, !dbg !3453
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %4 = load i8*, i8** %base, align 8, !dbg !3454
  %arrayidx = getelementptr inbounds i8, i8* %4, i64 0, !dbg !3454
  %5 = load i8, i8* %arrayidx, align 1, !dbg !3454
  %conv = sext i8 %5 to i32, !dbg !3454
  %cmp1 = icmp eq i32 %conv, 0, !dbg !3456
  br i1 %cmp1, label %if.then26, label %lor.lhs.false, !dbg !3457

lor.lhs.false:                                    ; preds = %if.end
  %6 = load i8*, i8** %base, align 8, !dbg !3458
  %arrayidx3 = getelementptr inbounds i8, i8* %6, i64 0, !dbg !3458
  %7 = load i8, i8* %arrayidx3, align 1, !dbg !3458
  %conv4 = sext i8 %7 to i32, !dbg !3458
  %cmp5 = icmp eq i32 %conv4, 46, !dbg !3459
  br i1 %cmp5, label %land.lhs.true, label %lor.lhs.false11, !dbg !3460

land.lhs.true:                                    ; preds = %lor.lhs.false
  %8 = load i8*, i8** %base, align 8, !dbg !3461
  %arrayidx7 = getelementptr inbounds i8, i8* %8, i64 1, !dbg !3461
  %9 = load i8, i8* %arrayidx7, align 1, !dbg !3461
  %conv8 = sext i8 %9 to i32, !dbg !3461
  %cmp9 = icmp eq i32 %conv8, 0, !dbg !3463
  br i1 %cmp9, label %if.then26, label %lor.lhs.false11, !dbg !3464

lor.lhs.false11:                                  ; preds = %land.lhs.true, %lor.lhs.false
  %10 = load i8*, i8** %base, align 8, !dbg !3465
  %arrayidx12 = getelementptr inbounds i8, i8* %10, i64 0, !dbg !3465
  %11 = load i8, i8* %arrayidx12, align 1, !dbg !3465
  %conv13 = sext i8 %11 to i32, !dbg !3465
  %cmp14 = icmp eq i32 %conv13, 46, !dbg !3466
  br i1 %cmp14, label %land.lhs.true16, label %if.end32, !dbg !3467

land.lhs.true16:                                  ; preds = %lor.lhs.false11
  %12 = load i8*, i8** %base, align 8, !dbg !3468
  %arrayidx17 = getelementptr inbounds i8, i8* %12, i64 1, !dbg !3468
  %13 = load i8, i8* %arrayidx17, align 1, !dbg !3468
  %conv18 = sext i8 %13 to i32, !dbg !3468
  %cmp19 = icmp eq i32 %conv18, 46, !dbg !3469
  br i1 %cmp19, label %land.lhs.true21, label %if.end32, !dbg !3470

land.lhs.true21:                                  ; preds = %land.lhs.true16
  %14 = load i8*, i8** %base, align 8, !dbg !3471
  %arrayidx22 = getelementptr inbounds i8, i8* %14, i64 2, !dbg !3471
  %15 = load i8, i8* %arrayidx22, align 1, !dbg !3471
  %conv23 = sext i8 %15 to i32, !dbg !3471
  %cmp24 = icmp eq i32 %conv23, 0, !dbg !3473
  br i1 %cmp24, label %if.then26, label %if.end32, !dbg !3474

if.then26:                                        ; preds = %land.lhs.true21, %land.lhs.true, %if.end
  %16 = load i8*, i8** %slash, align 8, !dbg !3476
  %cmp27 = icmp ne i8* %16, null, !dbg !3479
  br i1 %cmp27, label %if.then29, label %if.end31, !dbg !3480

if.then29:                                        ; preds = %if.then26
  %17 = load i8*, i8** %slash, align 8, !dbg !3481
  store i8 0, i8* %17, align 1, !dbg !3483
  %18 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3484
  %19 = load i8*, i8** %path.addr, align 8, !dbg !3485
  %call30 = call i32 @create_dir(%struct.archive_write_disk* %18, i8* %19), !dbg !3486
  store i32 %call30, i32* %r, align 4, !dbg !3487
  %20 = load i8*, i8** %slash, align 8, !dbg !3488
  store i8 47, i8* %20, align 1, !dbg !3489
  %21 = load i32, i32* %r, align 4, !dbg !3490
  store i32 %21, i32* %retval, align 4, !dbg !3491
  br label %return, !dbg !3491

if.end31:                                         ; preds = %if.then26
  store i32 0, i32* %retval, align 4, !dbg !3492
  br label %return, !dbg !3492

if.end32:                                         ; preds = %land.lhs.true21, %land.lhs.true16, %lor.lhs.false11
  %22 = load i8*, i8** %path.addr, align 8, !dbg !3493
  %call33 = call i32 @stat(i8* %22, %struct.stat* %st) #7, !dbg !3495
  %cmp34 = icmp eq i32 %call33, 0, !dbg !3496
  br i1 %cmp34, label %if.then36, label %if.else51, !dbg !3497

if.then36:                                        ; preds = %if.end32
  %st_mode = getelementptr inbounds %struct.stat, %struct.stat* %st, i32 0, i32 3, !dbg !3498
  %23 = load i32, i32* %st_mode, align 8, !dbg !3498
  %and = and i32 %23, 61440, !dbg !3498
  %cmp37 = icmp eq i32 %and, 16384, !dbg !3498
  br i1 %cmp37, label %if.then39, label %if.end40, !dbg !3501

if.then39:                                        ; preds = %if.then36
  store i32 0, i32* %retval, align 4, !dbg !3502
  br label %return, !dbg !3502

if.end40:                                         ; preds = %if.then36
  %24 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3503
  %flags = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %24, i32 0, i32 23, !dbg !3505
  %25 = load i32, i32* %flags, align 8, !dbg !3505
  %and41 = and i32 %25, 8, !dbg !3506
  %tobool = icmp ne i32 %and41, 0, !dbg !3506
  br i1 %tobool, label %if.then42, label %if.end43, !dbg !3507

if.then42:                                        ; preds = %if.end40
  %26 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3508
  %archive = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %26, i32 0, i32 0, !dbg !3510
  %27 = load i8*, i8** %path.addr, align 8, !dbg !3511
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 17, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.25, i32 0, i32 0), i8* %27), !dbg !3512
  store i32 -25, i32* %retval, align 4, !dbg !3513
  br label %return, !dbg !3513

if.end43:                                         ; preds = %if.end40
  %28 = load i8*, i8** %path.addr, align 8, !dbg !3514
  %call44 = call i32 @unlink(i8* %28) #7, !dbg !3516
  %cmp45 = icmp ne i32 %call44, 0, !dbg !3517
  br i1 %cmp45, label %if.then47, label %if.end50, !dbg !3518

if.then47:                                        ; preds = %if.end43
  %29 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3519
  %archive48 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %29, i32 0, i32 0, !dbg !3521
  %call49 = call i32* @__errno_location() #1, !dbg !3522
  %30 = load i32, i32* %call49, align 4, !dbg !3522
  %31 = load i8*, i8** %path.addr, align 8, !dbg !3523
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive48, i32 %30, i8* getelementptr inbounds ([64 x i8], [64 x i8]* @.str.26, i32 0, i32 0), i8* %31), !dbg !3524
  store i32 -25, i32* %retval, align 4, !dbg !3526
  br label %return, !dbg !3526

if.end50:                                         ; preds = %if.end43
  br label %if.end73, !dbg !3527

if.else51:                                        ; preds = %if.end32
  %call52 = call i32* @__errno_location() #1, !dbg !3528
  %32 = load i32, i32* %call52, align 4, !dbg !3528
  %cmp53 = icmp ne i32 %32, 2, !dbg !3531
  br i1 %cmp53, label %land.lhs.true55, label %if.else62, !dbg !3532

land.lhs.true55:                                  ; preds = %if.else51
  %call56 = call i32* @__errno_location() #1, !dbg !3533
  %33 = load i32, i32* %call56, align 4, !dbg !3533
  %cmp57 = icmp ne i32 %33, 20, !dbg !3535
  br i1 %cmp57, label %if.then59, label %if.else62, !dbg !3536

if.then59:                                        ; preds = %land.lhs.true55
  %34 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3537
  %archive60 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %34, i32 0, i32 0, !dbg !3539
  %call61 = call i32* @__errno_location() #1, !dbg !3540
  %35 = load i32, i32* %call61, align 4, !dbg !3540
  %36 = load i8*, i8** %path.addr, align 8, !dbg !3541
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive60, i32 %35, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.27, i32 0, i32 0), i8* %36), !dbg !3542
  store i32 -25, i32* %retval, align 4, !dbg !3544
  br label %return, !dbg !3544

if.else62:                                        ; preds = %land.lhs.true55, %if.else51
  %37 = load i8*, i8** %slash, align 8, !dbg !3545
  %cmp63 = icmp ne i8* %37, null, !dbg !3547
  br i1 %cmp63, label %if.then65, label %if.end71, !dbg !3548

if.then65:                                        ; preds = %if.else62
  %38 = load i8*, i8** %slash, align 8, !dbg !3549
  store i8 0, i8* %38, align 1, !dbg !3551
  %39 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3552
  %40 = load i8*, i8** %path.addr, align 8, !dbg !3553
  %call66 = call i32 @create_dir(%struct.archive_write_disk* %39, i8* %40), !dbg !3554
  store i32 %call66, i32* %r, align 4, !dbg !3555
  %41 = load i8*, i8** %slash, align 8, !dbg !3556
  store i8 47, i8* %41, align 1, !dbg !3557
  %42 = load i32, i32* %r, align 4, !dbg !3558
  %cmp67 = icmp ne i32 %42, 0, !dbg !3560
  br i1 %cmp67, label %if.then69, label %if.end70, !dbg !3561

if.then69:                                        ; preds = %if.then65
  %43 = load i32, i32* %r, align 4, !dbg !3562
  store i32 %43, i32* %retval, align 4, !dbg !3563
  br label %return, !dbg !3563

if.end70:                                         ; preds = %if.then65
  br label %if.end71, !dbg !3564

if.end71:                                         ; preds = %if.end70, %if.else62
  br label %if.end72

if.end72:                                         ; preds = %if.end71
  br label %if.end73

if.end73:                                         ; preds = %if.end72, %if.end50
  %44 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3565
  %user_umask = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %44, i32 0, i32 1, !dbg !3566
  %45 = load i32, i32* %user_umask, align 8, !dbg !3566
  %neg = xor i32 %45, -1, !dbg !3567
  %and74 = and i32 511, %neg, !dbg !3568
  store i32 %and74, i32* %mode_final, align 4, !dbg !3569
  %46 = load i32, i32* %mode_final, align 4, !dbg !3570
  store i32 %46, i32* %mode, align 4, !dbg !3571
  %47 = load i32, i32* %mode, align 4, !dbg !3572
  %or = or i32 %47, 448, !dbg !3572
  store i32 %or, i32* %mode, align 4, !dbg !3572
  %48 = load i32, i32* %mode, align 4, !dbg !3573
  %and75 = and i32 %48, 509, !dbg !3573
  store i32 %and75, i32* %mode, align 4, !dbg !3573
  %49 = load i8*, i8** %path.addr, align 8, !dbg !3574
  %50 = load i32, i32* %mode, align 4, !dbg !3576
  %call76 = call i32 @mkdir(i8* %49, i32 %50) #7, !dbg !3577
  %cmp77 = icmp eq i32 %call76, 0, !dbg !3578
  br i1 %cmp77, label %if.then79, label %if.end91, !dbg !3579

if.then79:                                        ; preds = %if.end73
  %51 = load i32, i32* %mode, align 4, !dbg !3580
  %52 = load i32, i32* %mode_final, align 4, !dbg !3583
  %cmp80 = icmp ne i32 %51, %52, !dbg !3584
  br i1 %cmp80, label %if.then82, label %if.end90, !dbg !3585

if.then82:                                        ; preds = %if.then79
  %53 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3586
  %54 = load i8*, i8** %path.addr, align 8, !dbg !3588
  %call83 = call %struct.fixup_entry* @new_fixup(%struct.archive_write_disk* %53, i8* %54), !dbg !3589
  store %struct.fixup_entry* %call83, %struct.fixup_entry** %le, align 8, !dbg !3590
  %55 = load %struct.fixup_entry*, %struct.fixup_entry** %le, align 8, !dbg !3591
  %cmp84 = icmp eq %struct.fixup_entry* %55, null, !dbg !3593
  br i1 %cmp84, label %if.then86, label %if.end87, !dbg !3594

if.then86:                                        ; preds = %if.then82
  store i32 -30, i32* %retval, align 4, !dbg !3595
  br label %return, !dbg !3595

if.end87:                                         ; preds = %if.then82
  %56 = load %struct.fixup_entry*, %struct.fixup_entry** %le, align 8, !dbg !3596
  %fixup = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %56, i32 0, i32 14, !dbg !3597
  %57 = load i32, i32* %fixup, align 8, !dbg !3598
  %or88 = or i32 %57, 536870912, !dbg !3598
  store i32 %or88, i32* %fixup, align 8, !dbg !3598
  %58 = load i32, i32* %mode_final, align 4, !dbg !3599
  %59 = load %struct.fixup_entry*, %struct.fixup_entry** %le, align 8, !dbg !3600
  %mode89 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %59, i32 0, i32 2, !dbg !3601
  store i32 %58, i32* %mode89, align 8, !dbg !3602
  br label %if.end90, !dbg !3603

if.end90:                                         ; preds = %if.end87, %if.then79
  store i32 0, i32* %retval, align 4, !dbg !3604
  br label %return, !dbg !3604

if.end91:                                         ; preds = %if.end73
  %60 = load i8*, i8** %path.addr, align 8, !dbg !3605
  %call92 = call i32 @stat(i8* %60, %struct.stat* %st) #7, !dbg !3607
  %cmp93 = icmp eq i32 %call92, 0, !dbg !3608
  br i1 %cmp93, label %land.lhs.true95, label %if.end101, !dbg !3609

land.lhs.true95:                                  ; preds = %if.end91
  %st_mode96 = getelementptr inbounds %struct.stat, %struct.stat* %st, i32 0, i32 3, !dbg !3610
  %61 = load i32, i32* %st_mode96, align 8, !dbg !3610
  %and97 = and i32 %61, 61440, !dbg !3610
  %cmp98 = icmp eq i32 %and97, 16384, !dbg !3610
  br i1 %cmp98, label %if.then100, label %if.end101, !dbg !3612

if.then100:                                       ; preds = %land.lhs.true95
  store i32 0, i32* %retval, align 4, !dbg !3613
  br label %return, !dbg !3613

if.end101:                                        ; preds = %land.lhs.true95, %if.end91
  %62 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3614
  %archive102 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %62, i32 0, i32 0, !dbg !3615
  %call103 = call i32* @__errno_location() #1, !dbg !3616
  %63 = load i32, i32* %call103, align 4, !dbg !3616
  %64 = load i8*, i8** %path.addr, align 8, !dbg !3617
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive102, i32 %63, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.28, i32 0, i32 0), i8* %64), !dbg !3618
  store i32 -25, i32* %retval, align 4, !dbg !3619
  br label %return, !dbg !3619

return:                                           ; preds = %if.end101, %if.then100, %if.end90, %if.then86, %if.then69, %if.then59, %if.then47, %if.then42, %if.then39, %if.end31, %if.then29
  %65 = load i32, i32* %retval, align 4, !dbg !3620
  ret i32 %65, !dbg !3620
}

; Function Attrs: nounwind readonly
declare i8* @strrchr(i8*, i32) #4

; Function Attrs: nounwind
declare i32 @mkdir(i8*, i32) #3

; Function Attrs: nounwind uwtable
define internal %struct.fixup_entry* @new_fixup(%struct.archive_write_disk* %a, i8* %pathname) #0 !dbg !362 {
entry:
  %retval = alloca %struct.fixup_entry*, align 8
  %a.addr = alloca %struct.archive_write_disk*, align 8
  %pathname.addr = alloca i8*, align 8
  %fe = alloca %struct.fixup_entry*, align 8
  store %struct.archive_write_disk* %a, %struct.archive_write_disk** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_disk** %a.addr, metadata !3621, metadata !399), !dbg !3622
  store i8* %pathname, i8** %pathname.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %pathname.addr, metadata !3623, metadata !399), !dbg !3624
  call void @llvm.dbg.declare(metadata %struct.fixup_entry** %fe, metadata !3625, metadata !399), !dbg !3626
  %call = call noalias i8* @calloc(i64 1, i64 176) #7, !dbg !3627
  %0 = bitcast i8* %call to %struct.fixup_entry*, !dbg !3628
  store %struct.fixup_entry* %0, %struct.fixup_entry** %fe, align 8, !dbg !3629
  %1 = load %struct.fixup_entry*, %struct.fixup_entry** %fe, align 8, !dbg !3630
  %cmp = icmp eq %struct.fixup_entry* %1, null, !dbg !3632
  br i1 %cmp, label %if.then, label %if.end, !dbg !3633

if.then:                                          ; preds = %entry
  %2 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3634
  %archive = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %2, i32 0, i32 0, !dbg !3636
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.29, i32 0, i32 0)), !dbg !3637
  store %struct.fixup_entry* null, %struct.fixup_entry** %retval, align 8, !dbg !3638
  br label %return, !dbg !3638

if.end:                                           ; preds = %entry
  %3 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3639
  %fixup_list = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %3, i32 0, i32 2, !dbg !3640
  %4 = load %struct.fixup_entry*, %struct.fixup_entry** %fixup_list, align 8, !dbg !3640
  %5 = load %struct.fixup_entry*, %struct.fixup_entry** %fe, align 8, !dbg !3641
  %next = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %5, i32 0, i32 0, !dbg !3642
  store %struct.fixup_entry* %4, %struct.fixup_entry** %next, align 8, !dbg !3643
  %6 = load %struct.fixup_entry*, %struct.fixup_entry** %fe, align 8, !dbg !3644
  %7 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3645
  %fixup_list1 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %7, i32 0, i32 2, !dbg !3646
  store %struct.fixup_entry* %6, %struct.fixup_entry** %fixup_list1, align 8, !dbg !3647
  %8 = load %struct.fixup_entry*, %struct.fixup_entry** %fe, align 8, !dbg !3648
  %fixup = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %8, i32 0, i32 14, !dbg !3649
  store i32 0, i32* %fixup, align 8, !dbg !3650
  %9 = load i8*, i8** %pathname.addr, align 8, !dbg !3651
  %call2 = call noalias i8* @strdup(i8* %9) #7, !dbg !3652
  %10 = load %struct.fixup_entry*, %struct.fixup_entry** %fe, align 8, !dbg !3653
  %name = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %10, i32 0, i32 15, !dbg !3654
  store i8* %call2, i8** %name, align 8, !dbg !3655
  %11 = load %struct.fixup_entry*, %struct.fixup_entry** %fe, align 8, !dbg !3656
  store %struct.fixup_entry* %11, %struct.fixup_entry** %retval, align 8, !dbg !3657
  br label %return, !dbg !3657

return:                                           ; preds = %if.end, %if.then
  %12 = load %struct.fixup_entry*, %struct.fixup_entry** %retval, align 8, !dbg !3658
  ret %struct.fixup_entry* %12, !dbg !3658
}

; Function Attrs: nounwind
declare noalias i8* @strdup(i8*) #3

; Function Attrs: nounwind uwtable
define internal i32 @clear_nochange_fflags(%struct.archive_write_disk* %a) #0 !dbg !366 {
entry:
  %a.addr = alloca %struct.archive_write_disk*, align 8
  %nochange_flags = alloca i32, align 4
  %mode = alloca i32, align 4
  store %struct.archive_write_disk* %a, %struct.archive_write_disk** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_disk** %a.addr, metadata !3659, metadata !399), !dbg !3660
  call void @llvm.dbg.declare(metadata i32* %nochange_flags, metadata !3661, metadata !399), !dbg !3662
  call void @llvm.dbg.declare(metadata i32* %mode, metadata !3663, metadata !399), !dbg !3664
  %0 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3665
  %entry1 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %0, i32 0, i32 18, !dbg !3666
  %1 = load %struct.archive_entry*, %struct.archive_entry** %entry1, align 8, !dbg !3666
  %call = call i32 @archive_entry_mode(%struct.archive_entry* %1), !dbg !3667
  store i32 %call, i32* %mode, align 4, !dbg !3664
  store i32 0, i32* %nochange_flags, align 4, !dbg !3668
  %2 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3669
  %3 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3670
  %fd = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %3, i32 0, i32 24, !dbg !3671
  %4 = load i32, i32* %fd, align 4, !dbg !3671
  %5 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3672
  %name = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %5, i32 0, i32 19, !dbg !3673
  %6 = load i8*, i8** %name, align 8, !dbg !3673
  %7 = load i32, i32* %mode, align 4, !dbg !3674
  %8 = load i32, i32* %nochange_flags, align 4, !dbg !3675
  %conv = sext i32 %8 to i64, !dbg !3675
  %call2 = call i32 @set_fflags_platform(%struct.archive_write_disk* %2, i32 %4, i8* %6, i32 %7, i64 0, i64 %conv), !dbg !3676
  ret i32 %call2, !dbg !3677
}

; Function Attrs: nounwind
declare i32 @rmdir(i8*) #3

; Function Attrs: nounwind uwtable
define internal i32 @create_filesystem_object(%struct.archive_write_disk* %a) #0 !dbg !367 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write_disk*, align 8
  %linkname = alloca i8*, align 8
  %final_mode = alloca i32, align 4
  %mode = alloca i32, align 4
  %r = alloca i32, align 4
  %linkname_copy = alloca i8*, align 8
  %st = alloca %struct.stat, align 8
  %error_string = alloca %struct.archive_string, align 8
  %error_number = alloca i32, align 4
  store %struct.archive_write_disk* %a, %struct.archive_write_disk** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_disk** %a.addr, metadata !3678, metadata !399), !dbg !3679
  call void @llvm.dbg.declare(metadata i8** %linkname, metadata !3680, metadata !399), !dbg !3681
  call void @llvm.dbg.declare(metadata i32* %final_mode, metadata !3682, metadata !399), !dbg !3683
  call void @llvm.dbg.declare(metadata i32* %mode, metadata !3684, metadata !399), !dbg !3685
  call void @llvm.dbg.declare(metadata i32* %r, metadata !3686, metadata !399), !dbg !3687
  call void @llvm.dbg.declare(metadata i8** %linkname_copy, metadata !3688, metadata !399), !dbg !3689
  call void @llvm.dbg.declare(metadata %struct.stat* %st, metadata !3690, metadata !399), !dbg !3691
  call void @llvm.dbg.declare(metadata %struct.archive_string* %error_string, metadata !3692, metadata !399), !dbg !3693
  call void @llvm.dbg.declare(metadata i32* %error_number, metadata !3694, metadata !399), !dbg !3695
  %0 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3696
  %entry1 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %0, i32 0, i32 18, !dbg !3697
  %1 = load %struct.archive_entry*, %struct.archive_entry** %entry1, align 8, !dbg !3697
  %call = call i8* @archive_entry_hardlink(%struct.archive_entry* %1), !dbg !3698
  store i8* %call, i8** %linkname, align 8, !dbg !3699
  %2 = load i8*, i8** %linkname, align 8, !dbg !3700
  %cmp = icmp ne i8* %2, null, !dbg !3702
  br i1 %cmp, label %if.then, label %if.end47, !dbg !3703

if.then:                                          ; preds = %entry
  br label %do.body, !dbg !3704

do.body:                                          ; preds = %if.then
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %error_string, i32 0, i32 0, !dbg !3706
  store i8* null, i8** %s, align 8, !dbg !3706
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %error_string, i32 0, i32 1, !dbg !3706
  store i64 0, i64* %length, align 8, !dbg !3706
  %buffer_length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %error_string, i32 0, i32 2, !dbg !3706
  store i64 0, i64* %buffer_length, align 8, !dbg !3706
  br label %do.end, !dbg !3706

do.end:                                           ; preds = %do.body
  %3 = load i8*, i8** %linkname, align 8, !dbg !3709
  %call2 = call noalias i8* @strdup(i8* %3) #7, !dbg !3710
  store i8* %call2, i8** %linkname_copy, align 8, !dbg !3711
  %4 = load i8*, i8** %linkname_copy, align 8, !dbg !3712
  %cmp3 = icmp eq i8* %4, null, !dbg !3714
  br i1 %cmp3, label %if.then4, label %if.end, !dbg !3715

if.then4:                                         ; preds = %do.end
  store i32 1, i32* %retval, align 4, !dbg !3716
  br label %return, !dbg !3716

if.end:                                           ; preds = %do.end
  %5 = load i8*, i8** %linkname_copy, align 8, !dbg !3718
  %6 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3719
  %flags = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %6, i32 0, i32 23, !dbg !3720
  %7 = load i32, i32* %flags, align 8, !dbg !3720
  %call5 = call i32 @cleanup_pathname_fsobj(i8* %5, i32* %error_number, %struct.archive_string* %error_string, i32 %7), !dbg !3721
  store i32 %call5, i32* %r, align 4, !dbg !3722
  %8 = load i32, i32* %r, align 4, !dbg !3723
  %cmp6 = icmp ne i32 %8, 0, !dbg !3725
  br i1 %cmp6, label %if.then7, label %if.end9, !dbg !3726

if.then7:                                         ; preds = %if.end
  %9 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3727
  %archive = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %9, i32 0, i32 0, !dbg !3729
  %10 = load i32, i32* %error_number, align 4, !dbg !3730
  %s8 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %error_string, i32 0, i32 0, !dbg !3731
  %11 = load i8*, i8** %s8, align 8, !dbg !3731
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 %10, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.11, i32 0, i32 0), i8* %11), !dbg !3732
  %12 = load i8*, i8** %linkname_copy, align 8, !dbg !3733
  call void @free(i8* %12) #7, !dbg !3734
  call void @archive_string_free(%struct.archive_string* %error_string), !dbg !3735
  store i32 1, i32* %retval, align 4, !dbg !3736
  br label %return, !dbg !3736

if.end9:                                          ; preds = %if.end
  %13 = load i8*, i8** %linkname_copy, align 8, !dbg !3737
  %14 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3738
  %flags10 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %14, i32 0, i32 23, !dbg !3739
  %15 = load i32, i32* %flags10, align 8, !dbg !3739
  %call11 = call i32 @check_symlinks_fsobj(i8* %13, i32* %error_number, %struct.archive_string* %error_string, i32 %15), !dbg !3740
  store i32 %call11, i32* %r, align 4, !dbg !3741
  %16 = load i32, i32* %r, align 4, !dbg !3742
  %cmp12 = icmp ne i32 %16, 0, !dbg !3744
  br i1 %cmp12, label %if.then13, label %if.end16, !dbg !3745

if.then13:                                        ; preds = %if.end9
  %17 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3746
  %archive14 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %17, i32 0, i32 0, !dbg !3748
  %18 = load i32, i32* %error_number, align 4, !dbg !3749
  %s15 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %error_string, i32 0, i32 0, !dbg !3750
  %19 = load i8*, i8** %s15, align 8, !dbg !3750
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive14, i32 %18, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.11, i32 0, i32 0), i8* %19), !dbg !3751
  %20 = load i8*, i8** %linkname_copy, align 8, !dbg !3752
  call void @free(i8* %20) #7, !dbg !3753
  call void @archive_string_free(%struct.archive_string* %error_string), !dbg !3754
  store i32 1, i32* %retval, align 4, !dbg !3755
  br label %return, !dbg !3755

if.end16:                                         ; preds = %if.end9
  %21 = load i8*, i8** %linkname_copy, align 8, !dbg !3756
  call void @free(i8* %21) #7, !dbg !3757
  call void @archive_string_free(%struct.archive_string* %error_string), !dbg !3758
  %22 = load i8*, i8** %linkname, align 8, !dbg !3759
  %23 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3760
  %name = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %23, i32 0, i32 19, !dbg !3761
  %24 = load i8*, i8** %name, align 8, !dbg !3761
  %call17 = call i32 @link(i8* %22, i8* %24) #7, !dbg !3762
  %tobool = icmp ne i32 %call17, 0, !dbg !3762
  br i1 %tobool, label %cond.true, label %cond.false, !dbg !3762

cond.true:                                        ; preds = %if.end16
  %call18 = call i32* @__errno_location() #1, !dbg !3763
  %25 = load i32, i32* %call18, align 4, !dbg !3763
  br label %cond.end, !dbg !3765

cond.false:                                       ; preds = %if.end16
  br label %cond.end, !dbg !3766

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ %25, %cond.true ], [ 0, %cond.false ], !dbg !3768
  store i32 %cond, i32* %r, align 4, !dbg !3770
  %26 = load i32, i32* %r, align 4, !dbg !3771
  %cmp19 = icmp eq i32 %26, 0, !dbg !3773
  br i1 %cmp19, label %land.lhs.true, label %if.else, !dbg !3774

land.lhs.true:                                    ; preds = %cond.end
  %27 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3775
  %filesize = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %27, i32 0, i32 28, !dbg !3777
  %28 = load i64, i64* %filesize, align 8, !dbg !3777
  %cmp20 = icmp sle i64 %28, 0, !dbg !3778
  br i1 %cmp20, label %if.then21, label %if.else, !dbg !3779

if.then21:                                        ; preds = %land.lhs.true
  %29 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3780
  %todo = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %29, i32 0, i32 21, !dbg !3782
  store i32 0, i32* %todo, align 8, !dbg !3783
  %30 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3784
  %deferred = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %30, i32 0, i32 22, !dbg !3785
  store i32 0, i32* %deferred, align 4, !dbg !3786
  br label %if.end46, !dbg !3787

if.else:                                          ; preds = %land.lhs.true, %cond.end
  %31 = load i32, i32* %r, align 4, !dbg !3788
  %cmp22 = icmp eq i32 %31, 0, !dbg !3791
  br i1 %cmp22, label %land.lhs.true23, label %if.end45, !dbg !3792

land.lhs.true23:                                  ; preds = %if.else
  %32 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3793
  %filesize24 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %32, i32 0, i32 28, !dbg !3795
  %33 = load i64, i64* %filesize24, align 8, !dbg !3795
  %cmp25 = icmp sgt i64 %33, 0, !dbg !3796
  br i1 %cmp25, label %if.then26, label %if.end45, !dbg !3797

if.then26:                                        ; preds = %land.lhs.true23
  %34 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3798
  %name27 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %34, i32 0, i32 19, !dbg !3800
  %35 = load i8*, i8** %name27, align 8, !dbg !3800
  %call28 = call i32 @lstat(i8* %35, %struct.stat* %st) #7, !dbg !3801
  store i32 %call28, i32* %r, align 4, !dbg !3802
  %36 = load i32, i32* %r, align 4, !dbg !3803
  %cmp29 = icmp ne i32 %36, 0, !dbg !3805
  br i1 %cmp29, label %if.then30, label %if.else32, !dbg !3806

if.then30:                                        ; preds = %if.then26
  %call31 = call i32* @__errno_location() #1, !dbg !3807
  %37 = load i32, i32* %call31, align 4, !dbg !3807
  store i32 %37, i32* %r, align 4, !dbg !3808
  br label %if.end44, !dbg !3809

if.else32:                                        ; preds = %if.then26
  %st_mode = getelementptr inbounds %struct.stat, %struct.stat* %st, i32 0, i32 3, !dbg !3810
  %38 = load i32, i32* %st_mode, align 8, !dbg !3810
  %and = and i32 %38, 61440, !dbg !3812
  %cmp33 = icmp eq i32 %and, 32768, !dbg !3813
  br i1 %cmp33, label %if.then34, label %if.end43, !dbg !3814

if.then34:                                        ; preds = %if.else32
  %39 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3815
  %name35 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %39, i32 0, i32 19, !dbg !3817
  %40 = load i8*, i8** %name35, align 8, !dbg !3817
  %call36 = call i32 (i8*, i32, ...) @open(i8* %40, i32 655873), !dbg !3818
  %41 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3819
  %fd = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %41, i32 0, i32 24, !dbg !3820
  store i32 %call36, i32* %fd, align 4, !dbg !3821
  %42 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3822
  %fd37 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %42, i32 0, i32 24, !dbg !3823
  %43 = load i32, i32* %fd37, align 4, !dbg !3823
  call void @__archive_ensure_cloexec_flag(i32 %43), !dbg !3824
  %44 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3825
  %fd38 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %44, i32 0, i32 24, !dbg !3827
  %45 = load i32, i32* %fd38, align 4, !dbg !3827
  %cmp39 = icmp slt i32 %45, 0, !dbg !3828
  br i1 %cmp39, label %if.then40, label %if.end42, !dbg !3829

if.then40:                                        ; preds = %if.then34
  %call41 = call i32* @__errno_location() #1, !dbg !3830
  %46 = load i32, i32* %call41, align 4, !dbg !3830
  store i32 %46, i32* %r, align 4, !dbg !3831
  br label %if.end42, !dbg !3832

if.end42:                                         ; preds = %if.then40, %if.then34
  br label %if.end43, !dbg !3833

if.end43:                                         ; preds = %if.end42, %if.else32
  br label %if.end44

if.end44:                                         ; preds = %if.end43, %if.then30
  br label %if.end45, !dbg !3834

if.end45:                                         ; preds = %if.end44, %land.lhs.true23, %if.else
  br label %if.end46

if.end46:                                         ; preds = %if.end45, %if.then21
  %47 = load i32, i32* %r, align 4, !dbg !3835
  store i32 %47, i32* %retval, align 4, !dbg !3836
  br label %return, !dbg !3836

if.end47:                                         ; preds = %entry
  %48 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3837
  %entry48 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %48, i32 0, i32 18, !dbg !3838
  %49 = load %struct.archive_entry*, %struct.archive_entry** %entry48, align 8, !dbg !3838
  %call49 = call i8* @archive_entry_symlink(%struct.archive_entry* %49), !dbg !3839
  store i8* %call49, i8** %linkname, align 8, !dbg !3840
  %50 = load i8*, i8** %linkname, align 8, !dbg !3841
  %cmp50 = icmp ne i8* %50, null, !dbg !3843
  br i1 %cmp50, label %if.then51, label %if.end60, !dbg !3844

if.then51:                                        ; preds = %if.end47
  %51 = load i8*, i8** %linkname, align 8, !dbg !3845
  %52 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3847
  %name52 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %52, i32 0, i32 19, !dbg !3848
  %53 = load i8*, i8** %name52, align 8, !dbg !3848
  %call53 = call i32 @symlink(i8* %51, i8* %53) #7, !dbg !3849
  %tobool54 = icmp ne i32 %call53, 0, !dbg !3849
  br i1 %tobool54, label %cond.true55, label %cond.false57, !dbg !3849

cond.true55:                                      ; preds = %if.then51
  %call56 = call i32* @__errno_location() #1, !dbg !3850
  %54 = load i32, i32* %call56, align 4, !dbg !3850
  br label %cond.end58, !dbg !3852

cond.false57:                                     ; preds = %if.then51
  br label %cond.end58, !dbg !3853

cond.end58:                                       ; preds = %cond.false57, %cond.true55
  %cond59 = phi i32 [ %54, %cond.true55 ], [ 0, %cond.false57 ], !dbg !3855
  store i32 %cond59, i32* %retval, align 4, !dbg !3857
  br label %return, !dbg !3857

if.end60:                                         ; preds = %if.end47
  %55 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3858
  %mode61 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %55, i32 0, i32 30, !dbg !3859
  %56 = load i32, i32* %mode61, align 4, !dbg !3859
  %and62 = and i32 %56, 4095, !dbg !3860
  store i32 %and62, i32* %final_mode, align 4, !dbg !3861
  %57 = load i32, i32* %final_mode, align 4, !dbg !3862
  %and63 = and i32 %57, 511, !dbg !3863
  %58 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3864
  %user_umask = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %58, i32 0, i32 1, !dbg !3865
  %59 = load i32, i32* %user_umask, align 8, !dbg !3865
  %neg = xor i32 %59, -1, !dbg !3866
  %and64 = and i32 %and63, %neg, !dbg !3867
  store i32 %and64, i32* %mode, align 4, !dbg !3868
  %60 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3869
  %mode65 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %60, i32 0, i32 30, !dbg !3870
  %61 = load i32, i32* %mode65, align 4, !dbg !3870
  %and66 = and i32 %61, 61440, !dbg !3871
  switch i32 %and66, label %sw.default [
    i32 32768, label %sw.bb
    i32 8192, label %sw.bb73
    i32 24576, label %sw.bb78
    i32 16384, label %sw.bb84
    i32 4096, label %sw.bb112
  ], !dbg !3872

sw.default:                                       ; preds = %if.end60
  br label %sw.bb, !dbg !3873

sw.bb:                                            ; preds = %if.end60, %sw.default
  %62 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3875
  %name67 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %62, i32 0, i32 19, !dbg !3877
  %63 = load i8*, i8** %name67, align 8, !dbg !3877
  %64 = load i32, i32* %mode, align 4, !dbg !3878
  %call68 = call i32 (i8*, i32, ...) @open(i8* %63, i32 524481, i32 %64), !dbg !3879
  %65 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3880
  %fd69 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %65, i32 0, i32 24, !dbg !3881
  store i32 %call68, i32* %fd69, align 4, !dbg !3882
  %66 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3883
  %fd70 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %66, i32 0, i32 24, !dbg !3884
  %67 = load i32, i32* %fd70, align 4, !dbg !3884
  call void @__archive_ensure_cloexec_flag(i32 %67), !dbg !3885
  %68 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3886
  %fd71 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %68, i32 0, i32 24, !dbg !3887
  %69 = load i32, i32* %fd71, align 4, !dbg !3887
  %cmp72 = icmp slt i32 %69, 0, !dbg !3888
  %conv = zext i1 %cmp72 to i32, !dbg !3888
  store i32 %conv, i32* %r, align 4, !dbg !3889
  br label %sw.epilog, !dbg !3890

sw.bb73:                                          ; preds = %if.end60
  %70 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3891
  %name74 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %70, i32 0, i32 19, !dbg !3892
  %71 = load i8*, i8** %name74, align 8, !dbg !3892
  %72 = load i32, i32* %mode, align 4, !dbg !3893
  %or = or i32 %72, 8192, !dbg !3894
  %73 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3895
  %entry75 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %73, i32 0, i32 18, !dbg !3896
  %74 = load %struct.archive_entry*, %struct.archive_entry** %entry75, align 8, !dbg !3896
  %call76 = call i64 @archive_entry_rdev(%struct.archive_entry* %74), !dbg !3897
  %call77 = call i32 @mknod(i8* %71, i32 %or, i64 %call76) #7, !dbg !3898
  store i32 %call77, i32* %r, align 4, !dbg !3899
  br label %sw.epilog, !dbg !3900

sw.bb78:                                          ; preds = %if.end60
  %75 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3901
  %name79 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %75, i32 0, i32 19, !dbg !3902
  %76 = load i8*, i8** %name79, align 8, !dbg !3902
  %77 = load i32, i32* %mode, align 4, !dbg !3903
  %or80 = or i32 %77, 24576, !dbg !3904
  %78 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3905
  %entry81 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %78, i32 0, i32 18, !dbg !3906
  %79 = load %struct.archive_entry*, %struct.archive_entry** %entry81, align 8, !dbg !3906
  %call82 = call i64 @archive_entry_rdev(%struct.archive_entry* %79), !dbg !3907
  %call83 = call i32 @mknod(i8* %76, i32 %or80, i64 %call82) #7, !dbg !3908
  store i32 %call83, i32* %r, align 4, !dbg !3909
  br label %sw.epilog, !dbg !3910

sw.bb84:                                          ; preds = %if.end60
  %80 = load i32, i32* %mode, align 4, !dbg !3911
  %or85 = or i32 %80, 448, !dbg !3912
  %and86 = and i32 %or85, 509, !dbg !3913
  store i32 %and86, i32* %mode, align 4, !dbg !3914
  %81 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3915
  %name87 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %81, i32 0, i32 19, !dbg !3916
  %82 = load i8*, i8** %name87, align 8, !dbg !3916
  %83 = load i32, i32* %mode, align 4, !dbg !3917
  %call88 = call i32 @mkdir(i8* %82, i32 %83) #7, !dbg !3918
  store i32 %call88, i32* %r, align 4, !dbg !3919
  %84 = load i32, i32* %r, align 4, !dbg !3920
  %cmp89 = icmp eq i32 %84, 0, !dbg !3922
  br i1 %cmp89, label %if.then91, label %if.end111, !dbg !3923

if.then91:                                        ; preds = %sw.bb84
  %85 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3924
  %todo92 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %85, i32 0, i32 21, !dbg !3926
  %86 = load i32, i32* %todo92, align 8, !dbg !3926
  %and93 = and i32 %86, 4, !dbg !3927
  %87 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3928
  %deferred94 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %87, i32 0, i32 22, !dbg !3929
  %88 = load i32, i32* %deferred94, align 4, !dbg !3930
  %or95 = or i32 %88, %and93, !dbg !3930
  store i32 %or95, i32* %deferred94, align 4, !dbg !3930
  %89 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3931
  %todo96 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %89, i32 0, i32 21, !dbg !3932
  %90 = load i32, i32* %todo96, align 8, !dbg !3933
  %and97 = and i32 %90, -5, !dbg !3933
  store i32 %and97, i32* %todo96, align 8, !dbg !3933
  %91 = load i32, i32* %mode, align 4, !dbg !3934
  %92 = load i32, i32* %final_mode, align 4, !dbg !3936
  %cmp98 = icmp ne i32 %91, %92, !dbg !3937
  br i1 %cmp98, label %if.then103, label %lor.lhs.false, !dbg !3938

lor.lhs.false:                                    ; preds = %if.then91
  %93 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3939
  %flags100 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %93, i32 0, i32 23, !dbg !3941
  %94 = load i32, i32* %flags100, align 8, !dbg !3941
  %and101 = and i32 %94, 2, !dbg !3942
  %tobool102 = icmp ne i32 %and101, 0, !dbg !3942
  br i1 %tobool102, label %if.then103, label %if.end108, !dbg !3943

if.then103:                                       ; preds = %lor.lhs.false, %if.then91
  %95 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3945
  %todo104 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %95, i32 0, i32 21, !dbg !3946
  %96 = load i32, i32* %todo104, align 8, !dbg !3946
  %and105 = and i32 %96, 872415232, !dbg !3947
  %97 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3948
  %deferred106 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %97, i32 0, i32 22, !dbg !3949
  %98 = load i32, i32* %deferred106, align 4, !dbg !3950
  %or107 = or i32 %98, %and105, !dbg !3950
  store i32 %or107, i32* %deferred106, align 4, !dbg !3950
  br label %if.end108, !dbg !3948

if.end108:                                        ; preds = %if.then103, %lor.lhs.false
  %99 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3951
  %todo109 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %99, i32 0, i32 21, !dbg !3952
  %100 = load i32, i32* %todo109, align 8, !dbg !3953
  %and110 = and i32 %100, -872415233, !dbg !3953
  store i32 %and110, i32* %todo109, align 8, !dbg !3953
  br label %if.end111, !dbg !3954

if.end111:                                        ; preds = %if.end108, %sw.bb84
  br label %sw.epilog, !dbg !3955

sw.bb112:                                         ; preds = %if.end60
  %101 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3956
  %name113 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %101, i32 0, i32 19, !dbg !3957
  %102 = load i8*, i8** %name113, align 8, !dbg !3957
  %103 = load i32, i32* %mode, align 4, !dbg !3958
  %call114 = call i32 @mkfifo(i8* %102, i32 %103) #7, !dbg !3959
  store i32 %call114, i32* %r, align 4, !dbg !3960
  br label %sw.epilog, !dbg !3961

sw.epilog:                                        ; preds = %sw.bb112, %if.end111, %sw.bb78, %sw.bb73, %sw.bb
  %104 = load i32, i32* %r, align 4, !dbg !3962
  %tobool115 = icmp ne i32 %104, 0, !dbg !3962
  br i1 %tobool115, label %if.then116, label %if.end118, !dbg !3964

if.then116:                                       ; preds = %sw.epilog
  %call117 = call i32* @__errno_location() #1, !dbg !3965
  %105 = load i32, i32* %call117, align 4, !dbg !3965
  store i32 %105, i32* %retval, align 4, !dbg !3966
  br label %return, !dbg !3966

if.end118:                                        ; preds = %sw.epilog
  %106 = load i32, i32* %mode, align 4, !dbg !3967
  %107 = load i32, i32* %final_mode, align 4, !dbg !3969
  %cmp119 = icmp eq i32 %106, %107, !dbg !3970
  br i1 %cmp119, label %if.then121, label %if.end124, !dbg !3971

if.then121:                                       ; preds = %if.end118
  %108 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3972
  %todo122 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %108, i32 0, i32 21, !dbg !3973
  %109 = load i32, i32* %todo122, align 8, !dbg !3974
  %and123 = and i32 %109, -872415233, !dbg !3974
  store i32 %and123, i32* %todo122, align 8, !dbg !3974
  br label %if.end124, !dbg !3972

if.end124:                                        ; preds = %if.then121, %if.end118
  store i32 0, i32* %retval, align 4, !dbg !3975
  br label %return, !dbg !3975

return:                                           ; preds = %if.end124, %if.then116, %cond.end58, %if.end46, %if.then13, %if.then7, %if.then4
  %110 = load i32, i32* %retval, align 4, !dbg !3976
  ret i32 %110, !dbg !3976
}

; Function Attrs: nounwind uwtable
define internal i32 @create_parent_dir(%struct.archive_write_disk* %a, i8* %path) #0 !dbg !368 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write_disk*, align 8
  %path.addr = alloca i8*, align 8
  %slash = alloca i8*, align 8
  %r = alloca i32, align 4
  store %struct.archive_write_disk* %a, %struct.archive_write_disk** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_disk** %a.addr, metadata !3977, metadata !399), !dbg !3978
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !3979, metadata !399), !dbg !3980
  call void @llvm.dbg.declare(metadata i8** %slash, metadata !3981, metadata !399), !dbg !3982
  call void @llvm.dbg.declare(metadata i32* %r, metadata !3983, metadata !399), !dbg !3984
  %0 = load i8*, i8** %path.addr, align 8, !dbg !3985
  %call = call i8* @strrchr(i8* %0, i32 47) #8, !dbg !3986
  store i8* %call, i8** %slash, align 8, !dbg !3987
  %1 = load i8*, i8** %slash, align 8, !dbg !3988
  %cmp = icmp eq i8* %1, null, !dbg !3990
  br i1 %cmp, label %if.then, label %if.end, !dbg !3991

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !3992
  br label %return, !dbg !3992

if.end:                                           ; preds = %entry
  %2 = load i8*, i8** %slash, align 8, !dbg !3993
  store i8 0, i8* %2, align 1, !dbg !3994
  %3 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !3995
  %4 = load i8*, i8** %path.addr, align 8, !dbg !3996
  %call1 = call i32 @create_dir(%struct.archive_write_disk* %3, i8* %4), !dbg !3997
  store i32 %call1, i32* %r, align 4, !dbg !3998
  %5 = load i8*, i8** %slash, align 8, !dbg !3999
  store i8 47, i8* %5, align 1, !dbg !4000
  %6 = load i32, i32* %r, align 4, !dbg !4001
  store i32 %6, i32* %retval, align 4, !dbg !4002
  br label %return, !dbg !4002

return:                                           ; preds = %if.end, %if.then
  %7 = load i32, i32* %retval, align 4, !dbg !4003
  ret i32 %7, !dbg !4003
}

declare i8* @archive_entry_hardlink(%struct.archive_entry*) #2

declare void @archive_entry_unset_size(%struct.archive_entry*) #2

; Function Attrs: nounwind uwtable
define internal i32 @older(%struct.stat* %st, %struct.archive_entry* %entry1) #0 !dbg !369 {
entry:
  %retval = alloca i32, align 4
  %st.addr = alloca %struct.stat*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.stat* %st, %struct.stat** %st.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.stat** %st.addr, metadata !4004, metadata !399), !dbg !4005
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !4006, metadata !399), !dbg !4007
  %0 = load %struct.stat*, %struct.stat** %st.addr, align 8, !dbg !4008
  %st_mtim = getelementptr inbounds %struct.stat, %struct.stat* %0, i32 0, i32 12, !dbg !4008
  %tv_sec = getelementptr inbounds %struct.timespec, %struct.timespec* %st_mtim, i32 0, i32 0, !dbg !4008
  %1 = load i64, i64* %tv_sec, align 8, !dbg !4008
  %cmp = icmp slt i64 %1, 0, !dbg !4008
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !4008

cond.true:                                        ; preds = %entry
  %2 = load %struct.stat*, %struct.stat** %st.addr, align 8, !dbg !4010
  %st_mtim2 = getelementptr inbounds %struct.stat, %struct.stat* %2, i32 0, i32 12, !dbg !4010
  %tv_sec3 = getelementptr inbounds %struct.timespec, %struct.timespec* %st_mtim2, i32 0, i32 0, !dbg !4010
  %3 = load i64, i64* %tv_sec3, align 8, !dbg !4010
  br label %cond.end11, !dbg !4010

cond.false:                                       ; preds = %entry
  %4 = load %struct.stat*, %struct.stat** %st.addr, align 8, !dbg !4012
  %st_mtim4 = getelementptr inbounds %struct.stat, %struct.stat* %4, i32 0, i32 12, !dbg !4012
  %tv_sec5 = getelementptr inbounds %struct.timespec, %struct.timespec* %st_mtim4, i32 0, i32 0, !dbg !4012
  %5 = load i64, i64* %tv_sec5, align 8, !dbg !4012
  %cmp6 = icmp ugt i64 %5, 9223372036854775807, !dbg !4012
  br i1 %cmp6, label %cond.true7, label %cond.false8, !dbg !4012

cond.true7:                                       ; preds = %cond.false
  br label %cond.end, !dbg !4014

cond.false8:                                      ; preds = %cond.false
  %6 = load %struct.stat*, %struct.stat** %st.addr, align 8, !dbg !4016
  %st_mtim9 = getelementptr inbounds %struct.stat, %struct.stat* %6, i32 0, i32 12, !dbg !4016
  %tv_sec10 = getelementptr inbounds %struct.timespec, %struct.timespec* %st_mtim9, i32 0, i32 0, !dbg !4016
  %7 = load i64, i64* %tv_sec10, align 8, !dbg !4016
  br label %cond.end, !dbg !4016

cond.end:                                         ; preds = %cond.false8, %cond.true7
  %cond = phi i64 [ 9223372036854775807, %cond.true7 ], [ %7, %cond.false8 ], !dbg !4018
  br label %cond.end11, !dbg !4018

cond.end11:                                       ; preds = %cond.end, %cond.true
  %cond12 = phi i64 [ %3, %cond.true ], [ %cond, %cond.end ], !dbg !4020
  %8 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4022
  %call = call i64 @archive_entry_mtime(%struct.archive_entry* %8), !dbg !4022
  %cmp13 = icmp slt i64 %call, 0, !dbg !4022
  br i1 %cmp13, label %cond.true14, label %cond.false16, !dbg !4022

cond.true14:                                      ; preds = %cond.end11
  %9 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4023
  %call15 = call i64 @archive_entry_mtime(%struct.archive_entry* %9), !dbg !4023
  br label %cond.end24, !dbg !4023

cond.false16:                                     ; preds = %cond.end11
  %10 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4025
  %call17 = call i64 @archive_entry_mtime(%struct.archive_entry* %10), !dbg !4025
  %cmp18 = icmp ugt i64 %call17, 9223372036854775807, !dbg !4025
  br i1 %cmp18, label %cond.true19, label %cond.false20, !dbg !4025

cond.true19:                                      ; preds = %cond.false16
  br label %cond.end22, !dbg !4027

cond.false20:                                     ; preds = %cond.false16
  %11 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4029
  %call21 = call i64 @archive_entry_mtime(%struct.archive_entry* %11), !dbg !4029
  br label %cond.end22, !dbg !4029

cond.end22:                                       ; preds = %cond.false20, %cond.true19
  %cond23 = phi i64 [ 9223372036854775807, %cond.true19 ], [ %call21, %cond.false20 ], !dbg !4031
  br label %cond.end24, !dbg !4031

cond.end24:                                       ; preds = %cond.end22, %cond.true14
  %cond25 = phi i64 [ %call15, %cond.true14 ], [ %cond23, %cond.end22 ], !dbg !4033
  %cmp26 = icmp slt i64 %cond12, %cond25, !dbg !4035
  br i1 %cmp26, label %if.then, label %if.end, !dbg !4036

if.then:                                          ; preds = %cond.end24
  store i32 1, i32* %retval, align 4, !dbg !4037
  br label %return, !dbg !4037

if.end:                                           ; preds = %cond.end24
  %12 = load %struct.stat*, %struct.stat** %st.addr, align 8, !dbg !4038
  %st_mtim27 = getelementptr inbounds %struct.stat, %struct.stat* %12, i32 0, i32 12, !dbg !4038
  %tv_sec28 = getelementptr inbounds %struct.timespec, %struct.timespec* %st_mtim27, i32 0, i32 0, !dbg !4038
  %13 = load i64, i64* %tv_sec28, align 8, !dbg !4038
  %cmp29 = icmp slt i64 %13, 0, !dbg !4038
  br i1 %cmp29, label %cond.true30, label %cond.false33, !dbg !4038

cond.true30:                                      ; preds = %if.end
  %14 = load %struct.stat*, %struct.stat** %st.addr, align 8, !dbg !4040
  %st_mtim31 = getelementptr inbounds %struct.stat, %struct.stat* %14, i32 0, i32 12, !dbg !4040
  %tv_sec32 = getelementptr inbounds %struct.timespec, %struct.timespec* %st_mtim31, i32 0, i32 0, !dbg !4040
  %15 = load i64, i64* %tv_sec32, align 8, !dbg !4040
  br label %cond.end43, !dbg !4040

cond.false33:                                     ; preds = %if.end
  %16 = load %struct.stat*, %struct.stat** %st.addr, align 8, !dbg !4042
  %st_mtim34 = getelementptr inbounds %struct.stat, %struct.stat* %16, i32 0, i32 12, !dbg !4042
  %tv_sec35 = getelementptr inbounds %struct.timespec, %struct.timespec* %st_mtim34, i32 0, i32 0, !dbg !4042
  %17 = load i64, i64* %tv_sec35, align 8, !dbg !4042
  %cmp36 = icmp ugt i64 %17, 9223372036854775807, !dbg !4042
  br i1 %cmp36, label %cond.true37, label %cond.false38, !dbg !4042

cond.true37:                                      ; preds = %cond.false33
  br label %cond.end41, !dbg !4044

cond.false38:                                     ; preds = %cond.false33
  %18 = load %struct.stat*, %struct.stat** %st.addr, align 8, !dbg !4046
  %st_mtim39 = getelementptr inbounds %struct.stat, %struct.stat* %18, i32 0, i32 12, !dbg !4046
  %tv_sec40 = getelementptr inbounds %struct.timespec, %struct.timespec* %st_mtim39, i32 0, i32 0, !dbg !4046
  %19 = load i64, i64* %tv_sec40, align 8, !dbg !4046
  br label %cond.end41, !dbg !4046

cond.end41:                                       ; preds = %cond.false38, %cond.true37
  %cond42 = phi i64 [ 9223372036854775807, %cond.true37 ], [ %19, %cond.false38 ], !dbg !4048
  br label %cond.end43, !dbg !4048

cond.end43:                                       ; preds = %cond.end41, %cond.true30
  %cond44 = phi i64 [ %15, %cond.true30 ], [ %cond42, %cond.end41 ], !dbg !4050
  %20 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4052
  %call45 = call i64 @archive_entry_mtime(%struct.archive_entry* %20), !dbg !4052
  %cmp46 = icmp slt i64 %call45, 0, !dbg !4052
  br i1 %cmp46, label %cond.true47, label %cond.false49, !dbg !4052

cond.true47:                                      ; preds = %cond.end43
  %21 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4053
  %call48 = call i64 @archive_entry_mtime(%struct.archive_entry* %21), !dbg !4053
  br label %cond.end57, !dbg !4053

cond.false49:                                     ; preds = %cond.end43
  %22 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4055
  %call50 = call i64 @archive_entry_mtime(%struct.archive_entry* %22), !dbg !4055
  %cmp51 = icmp ugt i64 %call50, 9223372036854775807, !dbg !4055
  br i1 %cmp51, label %cond.true52, label %cond.false53, !dbg !4055

cond.true52:                                      ; preds = %cond.false49
  br label %cond.end55, !dbg !4057

cond.false53:                                     ; preds = %cond.false49
  %23 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4059
  %call54 = call i64 @archive_entry_mtime(%struct.archive_entry* %23), !dbg !4059
  br label %cond.end55, !dbg !4059

cond.end55:                                       ; preds = %cond.false53, %cond.true52
  %cond56 = phi i64 [ 9223372036854775807, %cond.true52 ], [ %call54, %cond.false53 ], !dbg !4061
  br label %cond.end57, !dbg !4061

cond.end57:                                       ; preds = %cond.end55, %cond.true47
  %cond58 = phi i64 [ %call48, %cond.true47 ], [ %cond56, %cond.end55 ], !dbg !4063
  %cmp59 = icmp sgt i64 %cond44, %cond58, !dbg !4065
  br i1 %cmp59, label %if.then60, label %if.end61, !dbg !4066

if.then60:                                        ; preds = %cond.end57
  store i32 0, i32* %retval, align 4, !dbg !4067
  br label %return, !dbg !4067

if.end61:                                         ; preds = %cond.end57
  %24 = load %struct.stat*, %struct.stat** %st.addr, align 8, !dbg !4068
  %st_mtim62 = getelementptr inbounds %struct.stat, %struct.stat* %24, i32 0, i32 12, !dbg !4070
  %tv_nsec = getelementptr inbounds %struct.timespec, %struct.timespec* %st_mtim62, i32 0, i32 1, !dbg !4071
  %25 = load i64, i64* %tv_nsec, align 8, !dbg !4071
  %26 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4072
  %call63 = call i64 @archive_entry_mtime_nsec(%struct.archive_entry* %26), !dbg !4073
  %cmp64 = icmp slt i64 %25, %call63, !dbg !4074
  br i1 %cmp64, label %if.then65, label %if.end66, !dbg !4075

if.then65:                                        ; preds = %if.end61
  store i32 1, i32* %retval, align 4, !dbg !4076
  br label %return, !dbg !4076

if.end66:                                         ; preds = %if.end61
  store i32 0, i32* %retval, align 4, !dbg !4077
  br label %return, !dbg !4077

return:                                           ; preds = %if.end66, %if.then65, %if.then60, %if.then
  %27 = load i32, i32* %retval, align 4, !dbg !4078
  ret i32 %27, !dbg !4078
}

; Function Attrs: nounwind
declare i32 @link(i8*, i8*) #3

declare i8* @archive_entry_symlink(%struct.archive_entry*) #2

; Function Attrs: nounwind
declare i32 @symlink(i8*, i8*) #3

; Function Attrs: nounwind
declare i32 @mknod(i8*, i32, i64) #3

declare i64 @archive_entry_rdev(%struct.archive_entry*) #2

; Function Attrs: nounwind
declare i32 @mkfifo(i8*, i32) #3

; Function Attrs: nounwind
declare i32 @ftruncate(i32, i64) #3

; Function Attrs: nounwind uwtable
define internal i32 @lazy_stat(%struct.archive_write_disk* %a) #0 !dbg !374 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write_disk*, align 8
  store %struct.archive_write_disk* %a, %struct.archive_write_disk** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_disk** %a.addr, metadata !4079, metadata !399), !dbg !4080
  %0 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4081
  %pst = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %0, i32 0, i32 17, !dbg !4083
  %1 = load %struct.stat*, %struct.stat** %pst, align 8, !dbg !4083
  %cmp = icmp ne %struct.stat* %1, null, !dbg !4084
  br i1 %cmp, label %if.then, label %if.end, !dbg !4085

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !4086
  br label %return, !dbg !4086

if.end:                                           ; preds = %entry
  %2 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4088
  %fd = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %2, i32 0, i32 24, !dbg !4090
  %3 = load i32, i32* %fd, align 4, !dbg !4090
  %cmp1 = icmp sge i32 %3, 0, !dbg !4091
  br i1 %cmp1, label %land.lhs.true, label %if.end7, !dbg !4092

land.lhs.true:                                    ; preds = %if.end
  %4 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4093
  %fd2 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %4, i32 0, i32 24, !dbg !4095
  %5 = load i32, i32* %fd2, align 4, !dbg !4095
  %6 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4096
  %st = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %6, i32 0, i32 16, !dbg !4097
  %call = call i32 @fstat(i32 %5, %struct.stat* %st) #7, !dbg !4098
  %cmp3 = icmp eq i32 %call, 0, !dbg !4099
  br i1 %cmp3, label %if.then4, label %if.end7, !dbg !4100

if.then4:                                         ; preds = %land.lhs.true
  %7 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4101
  %st5 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %7, i32 0, i32 16, !dbg !4103
  %8 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4104
  %pst6 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %8, i32 0, i32 17, !dbg !4105
  store %struct.stat* %st5, %struct.stat** %pst6, align 8, !dbg !4106
  store i32 0, i32* %retval, align 4, !dbg !4107
  br label %return, !dbg !4107

if.end7:                                          ; preds = %land.lhs.true, %if.end
  %9 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4108
  %name = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %9, i32 0, i32 19, !dbg !4110
  %10 = load i8*, i8** %name, align 8, !dbg !4110
  %11 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4111
  %st8 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %11, i32 0, i32 16, !dbg !4112
  %call9 = call i32 @lstat(i8* %10, %struct.stat* %st8) #7, !dbg !4113
  %cmp10 = icmp eq i32 %call9, 0, !dbg !4114
  br i1 %cmp10, label %if.then11, label %if.end14, !dbg !4115

if.then11:                                        ; preds = %if.end7
  %12 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4116
  %st12 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %12, i32 0, i32 16, !dbg !4118
  %13 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4119
  %pst13 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %13, i32 0, i32 17, !dbg !4120
  store %struct.stat* %st12, %struct.stat** %pst13, align 8, !dbg !4121
  store i32 0, i32* %retval, align 4, !dbg !4122
  br label %return, !dbg !4122

if.end14:                                         ; preds = %if.end7
  %14 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4123
  %archive = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %14, i32 0, i32 0, !dbg !4124
  %call15 = call i32* @__errno_location() #1, !dbg !4125
  %15 = load i32, i32* %call15, align 4, !dbg !4125
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 %15, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.42, i32 0, i32 0)), !dbg !4126
  store i32 -20, i32* %retval, align 4, !dbg !4128
  br label %return, !dbg !4128

return:                                           ; preds = %if.end14, %if.then11, %if.then4, %if.then
  %16 = load i32, i32* %retval, align 4, !dbg !4129
  ret i32 %16, !dbg !4129
}

; Function Attrs: nounwind
declare i64 @lseek(i32, i64, i32) #3

declare i64 @write(i32, i8*, i64) #2

; Function Attrs: nounwind uwtable
define internal i32 @fixup_appledouble(%struct.archive_write_disk* %a, i8* %pathname) #0 !dbg !375 {
entry:
  %a.addr = alloca %struct.archive_write_disk*, align 8
  %pathname.addr = alloca i8*, align 8
  store %struct.archive_write_disk* %a, %struct.archive_write_disk** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_disk** %a.addr, metadata !4130, metadata !399), !dbg !4131
  store i8* %pathname, i8** %pathname.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %pathname.addr, metadata !4132, metadata !399), !dbg !4133
  %0 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4134
  %1 = load i8*, i8** %pathname.addr, align 8, !dbg !4135
  ret i32 0, !dbg !4136
}

declare i8* @archive_entry_uname(%struct.archive_entry*) #2

declare i64 @archive_entry_uid(%struct.archive_entry*) #2

declare i8* @archive_entry_gname(%struct.archive_entry*) #2

declare i64 @archive_entry_gid(%struct.archive_entry*) #2

; Function Attrs: nounwind uwtable
define internal i32 @set_ownership(%struct.archive_write_disk* %a) #0 !dbg !378 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write_disk*, align 8
  store %struct.archive_write_disk* %a, %struct.archive_write_disk** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_disk** %a.addr, metadata !4137, metadata !399), !dbg !4138
  %0 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4139
  %user_uid = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %0, i32 0, i32 4, !dbg !4141
  %1 = load i64, i64* %user_uid, align 8, !dbg !4141
  %cmp = icmp ne i64 %1, 0, !dbg !4142
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !4143

land.lhs.true:                                    ; preds = %entry
  %2 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4144
  %user_uid1 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %2, i32 0, i32 4, !dbg !4146
  %3 = load i64, i64* %user_uid1, align 8, !dbg !4146
  %4 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4147
  %uid = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %4, i32 0, i32 31, !dbg !4148
  %5 = load i64, i64* %uid, align 8, !dbg !4148
  %cmp2 = icmp ne i64 %3, %5, !dbg !4149
  br i1 %cmp2, label %if.then, label %if.end, !dbg !4150

if.then:                                          ; preds = %land.lhs.true
  %6 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4151
  %archive = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %6, i32 0, i32 0, !dbg !4153
  %call = call i32* @__errno_location() #1, !dbg !4154
  %7 = load i32, i32* %call, align 4, !dbg !4154
  %8 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4155
  %uid3 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %8, i32 0, i32 31, !dbg !4156
  %9 = load i64, i64* %uid3, align 8, !dbg !4156
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 %7, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.43, i32 0, i32 0), i64 %9), !dbg !4157
  store i32 -20, i32* %retval, align 4, !dbg !4159
  br label %return, !dbg !4159

if.end:                                           ; preds = %land.lhs.true, %entry
  %10 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4160
  %fd = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %10, i32 0, i32 24, !dbg !4162
  %11 = load i32, i32* %fd, align 4, !dbg !4162
  %cmp4 = icmp sge i32 %11, 0, !dbg !4163
  br i1 %cmp4, label %land.lhs.true5, label %if.end13, !dbg !4164

land.lhs.true5:                                   ; preds = %if.end
  %12 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4165
  %fd6 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %12, i32 0, i32 24, !dbg !4167
  %13 = load i32, i32* %fd6, align 4, !dbg !4167
  %14 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4168
  %uid7 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %14, i32 0, i32 31, !dbg !4169
  %15 = load i64, i64* %uid7, align 8, !dbg !4169
  %conv = trunc i64 %15 to i32, !dbg !4168
  %16 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4170
  %gid = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %16, i32 0, i32 32, !dbg !4171
  %17 = load i64, i64* %gid, align 8, !dbg !4171
  %conv8 = trunc i64 %17 to i32, !dbg !4170
  %call9 = call i32 @fchown(i32 %13, i32 %conv, i32 %conv8) #7, !dbg !4172
  %cmp10 = icmp eq i32 %call9, 0, !dbg !4173
  br i1 %cmp10, label %if.then12, label %if.end13, !dbg !4174

if.then12:                                        ; preds = %land.lhs.true5
  %18 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4175
  %todo = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %18, i32 0, i32 21, !dbg !4177
  %19 = load i32, i32* %todo, align 8, !dbg !4178
  %and = and i32 %19, -167772162, !dbg !4178
  store i32 %and, i32* %todo, align 8, !dbg !4178
  store i32 0, i32* %retval, align 4, !dbg !4179
  br label %return, !dbg !4179

if.end13:                                         ; preds = %land.lhs.true5, %if.end
  %20 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4180
  %name = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %20, i32 0, i32 19, !dbg !4182
  %21 = load i8*, i8** %name, align 8, !dbg !4182
  %22 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4183
  %uid14 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %22, i32 0, i32 31, !dbg !4184
  %23 = load i64, i64* %uid14, align 8, !dbg !4184
  %conv15 = trunc i64 %23 to i32, !dbg !4183
  %24 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4185
  %gid16 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %24, i32 0, i32 32, !dbg !4186
  %25 = load i64, i64* %gid16, align 8, !dbg !4186
  %conv17 = trunc i64 %25 to i32, !dbg !4185
  %call18 = call i32 @lchown(i8* %21, i32 %conv15, i32 %conv17) #7, !dbg !4187
  %cmp19 = icmp eq i32 %call18, 0, !dbg !4188
  br i1 %cmp19, label %if.then21, label %if.end24, !dbg !4189

if.then21:                                        ; preds = %if.end13
  %26 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4190
  %todo22 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %26, i32 0, i32 21, !dbg !4192
  %27 = load i32, i32* %todo22, align 8, !dbg !4193
  %and23 = and i32 %27, -167772162, !dbg !4193
  store i32 %and23, i32* %todo22, align 8, !dbg !4193
  store i32 0, i32* %retval, align 4, !dbg !4194
  br label %return, !dbg !4194

if.end24:                                         ; preds = %if.end13
  %28 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4195
  %archive25 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %28, i32 0, i32 0, !dbg !4196
  %call26 = call i32* @__errno_location() #1, !dbg !4197
  %29 = load i32, i32* %call26, align 4, !dbg !4197
  %30 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4198
  %uid27 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %30, i32 0, i32 31, !dbg !4199
  %31 = load i64, i64* %uid27, align 8, !dbg !4199
  %32 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4200
  %gid28 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %32, i32 0, i32 32, !dbg !4201
  %33 = load i64, i64* %gid28, align 8, !dbg !4201
  %34 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4202
  %name29 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %34, i32 0, i32 19, !dbg !4203
  %35 = load i8*, i8** %name29, align 8, !dbg !4203
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive25, i32 %29, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.44, i32 0, i32 0), i64 %31, i64 %33, i8* %35), !dbg !4204
  store i32 -20, i32* %retval, align 4, !dbg !4206
  br label %return, !dbg !4206

return:                                           ; preds = %if.end24, %if.then21, %if.then12, %if.then
  %36 = load i32, i32* %retval, align 4, !dbg !4207
  ret i32 %36, !dbg !4207
}

; Function Attrs: nounwind uwtable
define internal i32 @set_mode(%struct.archive_write_disk* %a, i32 %mode) #0 !dbg !379 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write_disk*, align 8
  %mode.addr = alloca i32, align 4
  %r = alloca i32, align 4
  store %struct.archive_write_disk* %a, %struct.archive_write_disk** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_disk** %a.addr, metadata !4208, metadata !399), !dbg !4209
  store i32 %mode, i32* %mode.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %mode.addr, metadata !4210, metadata !399), !dbg !4211
  call void @llvm.dbg.declare(metadata i32* %r, metadata !4212, metadata !399), !dbg !4213
  store i32 0, i32* %r, align 4, !dbg !4213
  %0 = load i32, i32* %mode.addr, align 4, !dbg !4214
  %and = and i32 %0, 4095, !dbg !4214
  store i32 %and, i32* %mode.addr, align 4, !dbg !4214
  %1 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4215
  %todo = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %1, i32 0, i32 21, !dbg !4217
  %2 = load i32, i32* %todo, align 8, !dbg !4217
  %and1 = and i32 %2, 33554432, !dbg !4218
  %tobool = icmp ne i32 %and1, 0, !dbg !4218
  br i1 %tobool, label %if.then, label %if.else, !dbg !4219

if.then:                                          ; preds = %entry
  %3 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4220
  %call = call i32 @lazy_stat(%struct.archive_write_disk* %3), !dbg !4223
  store i32 %call, i32* %r, align 4, !dbg !4224
  %cmp = icmp ne i32 %call, 0, !dbg !4225
  br i1 %cmp, label %if.then2, label %if.end, !dbg !4226

if.then2:                                         ; preds = %if.then
  %4 = load i32, i32* %r, align 4, !dbg !4227
  store i32 %4, i32* %retval, align 4, !dbg !4228
  br label %return, !dbg !4228

if.end:                                           ; preds = %if.then
  %5 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4229
  %pst = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %5, i32 0, i32 17, !dbg !4231
  %6 = load %struct.stat*, %struct.stat** %pst, align 8, !dbg !4231
  %st_gid = getelementptr inbounds %struct.stat, %struct.stat* %6, i32 0, i32 5, !dbg !4232
  %7 = load i32, i32* %st_gid, align 8, !dbg !4232
  %conv = zext i32 %7 to i64, !dbg !4229
  %8 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4233
  %gid = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %8, i32 0, i32 32, !dbg !4234
  %9 = load i64, i64* %gid, align 8, !dbg !4234
  %cmp3 = icmp ne i64 %conv, %9, !dbg !4235
  br i1 %cmp3, label %if.then5, label %if.end11, !dbg !4236

if.then5:                                         ; preds = %if.end
  %10 = load i32, i32* %mode.addr, align 4, !dbg !4237
  %and6 = and i32 %10, -1025, !dbg !4237
  store i32 %and6, i32* %mode.addr, align 4, !dbg !4237
  %11 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4239
  %flags = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %11, i32 0, i32 23, !dbg !4241
  %12 = load i32, i32* %flags, align 8, !dbg !4241
  %and7 = and i32 %12, 1, !dbg !4242
  %tobool8 = icmp ne i32 %and7, 0, !dbg !4242
  br i1 %tobool8, label %if.then9, label %if.end10, !dbg !4243

if.then9:                                         ; preds = %if.then5
  %13 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4244
  %archive = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %13, i32 0, i32 0, !dbg !4246
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 -1, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.45, i32 0, i32 0)), !dbg !4247
  store i32 -20, i32* %r, align 4, !dbg !4248
  br label %if.end10, !dbg !4249

if.end10:                                         ; preds = %if.then9, %if.then5
  br label %if.end11, !dbg !4250

if.end11:                                         ; preds = %if.end10, %if.end
  %14 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4251
  %pst12 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %14, i32 0, i32 17, !dbg !4253
  %15 = load %struct.stat*, %struct.stat** %pst12, align 8, !dbg !4253
  %st_uid = getelementptr inbounds %struct.stat, %struct.stat* %15, i32 0, i32 4, !dbg !4254
  %16 = load i32, i32* %st_uid, align 4, !dbg !4254
  %conv13 = zext i32 %16 to i64, !dbg !4251
  %17 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4255
  %uid = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %17, i32 0, i32 31, !dbg !4256
  %18 = load i64, i64* %uid, align 8, !dbg !4256
  %cmp14 = icmp ne i64 %conv13, %18, !dbg !4257
  br i1 %cmp14, label %land.lhs.true, label %if.end27, !dbg !4258

land.lhs.true:                                    ; preds = %if.end11
  %19 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4259
  %todo16 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %19, i32 0, i32 21, !dbg !4261
  %20 = load i32, i32* %todo16, align 8, !dbg !4261
  %and17 = and i32 %20, 268435456, !dbg !4262
  %tobool18 = icmp ne i32 %and17, 0, !dbg !4262
  br i1 %tobool18, label %if.then19, label %if.end27, !dbg !4263

if.then19:                                        ; preds = %land.lhs.true
  %21 = load i32, i32* %mode.addr, align 4, !dbg !4265
  %and20 = and i32 %21, -2049, !dbg !4265
  store i32 %and20, i32* %mode.addr, align 4, !dbg !4265
  %22 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4267
  %flags21 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %22, i32 0, i32 23, !dbg !4269
  %23 = load i32, i32* %flags21, align 8, !dbg !4269
  %and22 = and i32 %23, 1, !dbg !4270
  %tobool23 = icmp ne i32 %and22, 0, !dbg !4270
  br i1 %tobool23, label %if.then24, label %if.end26, !dbg !4271

if.then24:                                        ; preds = %if.then19
  %24 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4272
  %archive25 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %24, i32 0, i32 0, !dbg !4274
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive25, i32 -1, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.46, i32 0, i32 0)), !dbg !4275
  store i32 -20, i32* %r, align 4, !dbg !4276
  br label %if.end26, !dbg !4277

if.end26:                                         ; preds = %if.then24, %if.then19
  br label %if.end27, !dbg !4278

if.end27:                                         ; preds = %if.end26, %land.lhs.true, %if.end11
  %25 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4279
  %todo28 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %25, i32 0, i32 21, !dbg !4280
  %26 = load i32, i32* %todo28, align 8, !dbg !4281
  %and29 = and i32 %26, -33554433, !dbg !4281
  store i32 %and29, i32* %todo28, align 8, !dbg !4281
  %27 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4282
  %todo30 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %27, i32 0, i32 21, !dbg !4283
  %28 = load i32, i32* %todo30, align 8, !dbg !4284
  %and31 = and i32 %28, -134217729, !dbg !4284
  store i32 %and31, i32* %todo30, align 8, !dbg !4284
  br label %if.end51, !dbg !4285

if.else:                                          ; preds = %entry
  %29 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4286
  %todo32 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %29, i32 0, i32 21, !dbg !4289
  %30 = load i32, i32* %todo32, align 8, !dbg !4289
  %and33 = and i32 %30, 134217728, !dbg !4290
  %tobool34 = icmp ne i32 %and33, 0, !dbg !4290
  br i1 %tobool34, label %if.then35, label %if.end50, !dbg !4286

if.then35:                                        ; preds = %if.else
  %31 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4291
  %user_uid = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %31, i32 0, i32 4, !dbg !4294
  %32 = load i64, i64* %user_uid, align 8, !dbg !4294
  %33 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4295
  %uid36 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %33, i32 0, i32 31, !dbg !4296
  %34 = load i64, i64* %uid36, align 8, !dbg !4296
  %cmp37 = icmp ne i64 %32, %34, !dbg !4297
  br i1 %cmp37, label %if.then39, label %if.end47, !dbg !4298

if.then39:                                        ; preds = %if.then35
  %35 = load i32, i32* %mode.addr, align 4, !dbg !4299
  %and40 = and i32 %35, -2049, !dbg !4299
  store i32 %and40, i32* %mode.addr, align 4, !dbg !4299
  %36 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4301
  %flags41 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %36, i32 0, i32 23, !dbg !4303
  %37 = load i32, i32* %flags41, align 8, !dbg !4303
  %and42 = and i32 %37, 1, !dbg !4304
  %tobool43 = icmp ne i32 %and42, 0, !dbg !4304
  br i1 %tobool43, label %if.then44, label %if.end46, !dbg !4305

if.then44:                                        ; preds = %if.then39
  %38 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4306
  %archive45 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %38, i32 0, i32 0, !dbg !4308
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive45, i32 -1, i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.47, i32 0, i32 0)), !dbg !4309
  store i32 -20, i32* %r, align 4, !dbg !4310
  br label %if.end46, !dbg !4311

if.end46:                                         ; preds = %if.then44, %if.then39
  br label %if.end47, !dbg !4312

if.end47:                                         ; preds = %if.end46, %if.then35
  %39 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4313
  %todo48 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %39, i32 0, i32 21, !dbg !4314
  %40 = load i32, i32* %todo48, align 8, !dbg !4315
  %and49 = and i32 %40, -134217729, !dbg !4315
  store i32 %and49, i32* %todo48, align 8, !dbg !4315
  br label %if.end50, !dbg !4316

if.end50:                                         ; preds = %if.end47, %if.else
  br label %if.end51

if.end51:                                         ; preds = %if.end50, %if.end27
  %41 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4317
  %mode52 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %41, i32 0, i32 30, !dbg !4317
  %42 = load i32, i32* %mode52, align 4, !dbg !4317
  %and53 = and i32 %42, 61440, !dbg !4317
  %cmp54 = icmp eq i32 %and53, 40960, !dbg !4317
  br i1 %cmp54, label %if.then56, label %if.else57, !dbg !4319

if.then56:                                        ; preds = %if.end51
  br label %if.end84, !dbg !4320

if.else57:                                        ; preds = %if.end51
  %43 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4322
  %mode58 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %43, i32 0, i32 30, !dbg !4322
  %44 = load i32, i32* %mode58, align 4, !dbg !4322
  %and59 = and i32 %44, 61440, !dbg !4322
  %cmp60 = icmp eq i32 %and59, 16384, !dbg !4322
  br i1 %cmp60, label %if.end83, label %if.then62, !dbg !4325

if.then62:                                        ; preds = %if.else57
  %45 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4326
  %fd = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %45, i32 0, i32 24, !dbg !4329
  %46 = load i32, i32* %fd, align 4, !dbg !4329
  %cmp63 = icmp sge i32 %46, 0, !dbg !4330
  br i1 %cmp63, label %if.then65, label %if.else74, !dbg !4331

if.then65:                                        ; preds = %if.then62
  %47 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4332
  %fd66 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %47, i32 0, i32 24, !dbg !4335
  %48 = load i32, i32* %fd66, align 4, !dbg !4335
  %49 = load i32, i32* %mode.addr, align 4, !dbg !4336
  %call67 = call i32 @fchmod(i32 %48, i32 %49) #7, !dbg !4337
  %cmp68 = icmp ne i32 %call67, 0, !dbg !4338
  br i1 %cmp68, label %if.then70, label %if.end73, !dbg !4339

if.then70:                                        ; preds = %if.then65
  %50 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4340
  %archive71 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %50, i32 0, i32 0, !dbg !4342
  %call72 = call i32* @__errno_location() #1, !dbg !4343
  %51 = load i32, i32* %call72, align 4, !dbg !4343
  %52 = load i32, i32* %mode.addr, align 4, !dbg !4344
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive71, i32 %51, i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.48, i32 0, i32 0), i32 %52), !dbg !4345
  store i32 -20, i32* %r, align 4, !dbg !4347
  br label %if.end73, !dbg !4348

if.end73:                                         ; preds = %if.then70, %if.then65
  br label %if.end82, !dbg !4349

if.else74:                                        ; preds = %if.then62
  %53 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4350
  %name = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %53, i32 0, i32 19, !dbg !4352
  %54 = load i8*, i8** %name, align 8, !dbg !4352
  %55 = load i32, i32* %mode.addr, align 4, !dbg !4353
  %call75 = call i32 @chmod(i8* %54, i32 %55) #7, !dbg !4354
  %cmp76 = icmp ne i32 %call75, 0, !dbg !4355
  br i1 %cmp76, label %if.then78, label %if.end81, !dbg !4356

if.then78:                                        ; preds = %if.else74
  %56 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4357
  %archive79 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %56, i32 0, i32 0, !dbg !4359
  %call80 = call i32* @__errno_location() #1, !dbg !4360
  %57 = load i32, i32* %call80, align 4, !dbg !4360
  %58 = load i32, i32* %mode.addr, align 4, !dbg !4361
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive79, i32 %57, i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.48, i32 0, i32 0), i32 %58), !dbg !4362
  store i32 -20, i32* %r, align 4, !dbg !4364
  br label %if.end81, !dbg !4365

if.end81:                                         ; preds = %if.then78, %if.else74
  br label %if.end82

if.end82:                                         ; preds = %if.end81, %if.end73
  br label %if.end83, !dbg !4366

if.end83:                                         ; preds = %if.end82, %if.else57
  br label %if.end84

if.end84:                                         ; preds = %if.end83, %if.then56
  %59 = load i32, i32* %r, align 4, !dbg !4367
  store i32 %59, i32* %retval, align 4, !dbg !4368
  br label %return, !dbg !4368

return:                                           ; preds = %if.end84, %if.then2
  %60 = load i32, i32* %retval, align 4, !dbg !4369
  ret i32 %60, !dbg !4369
}

; Function Attrs: nounwind uwtable
define internal i32 @set_xattrs(%struct.archive_write_disk* %a) #0 !dbg !382 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write_disk*, align 8
  store %struct.archive_write_disk* %a, %struct.archive_write_disk** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_disk** %a.addr, metadata !4370, metadata !399), !dbg !4371
  %0 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4372
  %entry1 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %0, i32 0, i32 18, !dbg !4374
  %1 = load %struct.archive_entry*, %struct.archive_entry** %entry1, align 8, !dbg !4374
  %call = call i32 @archive_entry_xattr_count(%struct.archive_entry* %1), !dbg !4375
  %cmp = icmp ne i32 %call, 0, !dbg !4376
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !4377

land.lhs.true:                                    ; preds = %entry
  %2 = load i32, i32* @set_xattrs.warning_done, align 4, !dbg !4378
  %tobool = icmp ne i32 %2, 0, !dbg !4378
  br i1 %tobool, label %if.end, label %if.then, !dbg !4380

if.then:                                          ; preds = %land.lhs.true
  store i32 1, i32* @set_xattrs.warning_done, align 4, !dbg !4381
  %3 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4383
  %archive = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %3, i32 0, i32 0, !dbg !4384
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 84, i8* getelementptr inbounds ([50 x i8], [50 x i8]* @.str.49, i32 0, i32 0)), !dbg !4385
  store i32 -20, i32* %retval, align 4, !dbg !4386
  br label %return, !dbg !4386

if.end:                                           ; preds = %land.lhs.true, %entry
  store i32 0, i32* %retval, align 4, !dbg !4387
  br label %return, !dbg !4387

return:                                           ; preds = %if.end, %if.then
  %4 = load i32, i32* %retval, align 4, !dbg !4388
  ret i32 %4, !dbg !4388
}

; Function Attrs: nounwind uwtable
define internal i32 @set_fflags(%struct.archive_write_disk* %a) #0 !dbg !383 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write_disk*, align 8
  %le = alloca %struct.fixup_entry*, align 8
  %set = alloca i64, align 8
  %clear = alloca i64, align 8
  %r = alloca i32, align 4
  %critical_flags = alloca i32, align 4
  %mode = alloca i32, align 4
  store %struct.archive_write_disk* %a, %struct.archive_write_disk** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_disk** %a.addr, metadata !4389, metadata !399), !dbg !4390
  call void @llvm.dbg.declare(metadata %struct.fixup_entry** %le, metadata !4391, metadata !399), !dbg !4392
  call void @llvm.dbg.declare(metadata i64* %set, metadata !4393, metadata !399), !dbg !4394
  call void @llvm.dbg.declare(metadata i64* %clear, metadata !4395, metadata !399), !dbg !4396
  call void @llvm.dbg.declare(metadata i32* %r, metadata !4397, metadata !399), !dbg !4398
  call void @llvm.dbg.declare(metadata i32* %critical_flags, metadata !4399, metadata !399), !dbg !4400
  call void @llvm.dbg.declare(metadata i32* %mode, metadata !4401, metadata !399), !dbg !4402
  %0 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4403
  %entry1 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %0, i32 0, i32 18, !dbg !4404
  %1 = load %struct.archive_entry*, %struct.archive_entry** %entry1, align 8, !dbg !4404
  %call = call i32 @archive_entry_mode(%struct.archive_entry* %1), !dbg !4405
  store i32 %call, i32* %mode, align 4, !dbg !4402
  store i32 0, i32* %critical_flags, align 4, !dbg !4406
  %2 = load i32, i32* %critical_flags, align 4, !dbg !4407
  %or = or i32 %2, 32, !dbg !4407
  store i32 %or, i32* %critical_flags, align 4, !dbg !4407
  %3 = load i32, i32* %critical_flags, align 4, !dbg !4408
  %or2 = or i32 %3, 16, !dbg !4408
  store i32 %or2, i32* %critical_flags, align 4, !dbg !4408
  %4 = load i32, i32* %critical_flags, align 4, !dbg !4409
  %or3 = or i32 %4, 16384, !dbg !4409
  store i32 %or3, i32* %critical_flags, align 4, !dbg !4409
  %5 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4410
  %todo = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %5, i32 0, i32 21, !dbg !4412
  %6 = load i32, i32* %todo, align 8, !dbg !4412
  %and = and i32 %6, 64, !dbg !4413
  %tobool = icmp ne i32 %and, 0, !dbg !4413
  br i1 %tobool, label %if.then, label %if.end27, !dbg !4414

if.then:                                          ; preds = %entry
  %7 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4415
  %entry4 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %7, i32 0, i32 18, !dbg !4417
  %8 = load %struct.archive_entry*, %struct.archive_entry** %entry4, align 8, !dbg !4417
  call void @archive_entry_fflags(%struct.archive_entry* %8, i64* %set, i64* %clear), !dbg !4418
  %9 = load i32, i32* %critical_flags, align 4, !dbg !4419
  %cmp = icmp ne i32 %9, 0, !dbg !4421
  br i1 %cmp, label %land.lhs.true, label %if.else, !dbg !4422

land.lhs.true:                                    ; preds = %if.then
  %10 = load i64, i64* %set, align 8, !dbg !4423
  %11 = load i32, i32* %critical_flags, align 4, !dbg !4425
  %conv = sext i32 %11 to i64, !dbg !4425
  %and5 = and i64 %10, %conv, !dbg !4426
  %tobool6 = icmp ne i64 %and5, 0, !dbg !4426
  br i1 %tobool6, label %if.then7, label %if.else, !dbg !4427

if.then7:                                         ; preds = %land.lhs.true
  %12 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4428
  %13 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4430
  %name = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %13, i32 0, i32 19, !dbg !4431
  %14 = load i8*, i8** %name, align 8, !dbg !4431
  %call8 = call %struct.fixup_entry* @current_fixup(%struct.archive_write_disk* %12, i8* %14), !dbg !4432
  store %struct.fixup_entry* %call8, %struct.fixup_entry** %le, align 8, !dbg !4433
  %15 = load %struct.fixup_entry*, %struct.fixup_entry** %le, align 8, !dbg !4434
  %cmp9 = icmp eq %struct.fixup_entry* %15, null, !dbg !4436
  br i1 %cmp9, label %if.then11, label %if.end, !dbg !4437

if.then11:                                        ; preds = %if.then7
  store i32 -30, i32* %retval, align 4, !dbg !4438
  br label %return, !dbg !4438

if.end:                                           ; preds = %if.then7
  %16 = load %struct.fixup_entry*, %struct.fixup_entry** %le, align 8, !dbg !4439
  %fixup = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %16, i32 0, i32 14, !dbg !4440
  %17 = load i32, i32* %fixup, align 8, !dbg !4441
  %or12 = or i32 %17, 64, !dbg !4441
  store i32 %or12, i32* %fixup, align 8, !dbg !4441
  %18 = load i64, i64* %set, align 8, !dbg !4442
  %19 = load %struct.fixup_entry*, %struct.fixup_entry** %le, align 8, !dbg !4443
  %fflags_set = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %19, i32 0, i32 11, !dbg !4444
  store i64 %18, i64* %fflags_set, align 8, !dbg !4445
  %20 = load %struct.fixup_entry*, %struct.fixup_entry** %le, align 8, !dbg !4446
  %fixup13 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %20, i32 0, i32 14, !dbg !4448
  %21 = load i32, i32* %fixup13, align 8, !dbg !4448
  %and14 = and i32 %21, 872415232, !dbg !4449
  %cmp15 = icmp eq i32 %and14, 0, !dbg !4450
  br i1 %cmp15, label %if.then17, label %if.end19, !dbg !4451

if.then17:                                        ; preds = %if.end
  %22 = load i32, i32* %mode, align 4, !dbg !4452
  %23 = load %struct.fixup_entry*, %struct.fixup_entry** %le, align 8, !dbg !4453
  %mode18 = getelementptr inbounds %struct.fixup_entry, %struct.fixup_entry* %23, i32 0, i32 2, !dbg !4454
  store i32 %22, i32* %mode18, align 8, !dbg !4455
  br label %if.end19, !dbg !4453

if.end19:                                         ; preds = %if.then17, %if.end
  br label %if.end26, !dbg !4456

if.else:                                          ; preds = %land.lhs.true, %if.then
  %24 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4457
  %25 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4459
  %fd = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %25, i32 0, i32 24, !dbg !4460
  %26 = load i32, i32* %fd, align 4, !dbg !4460
  %27 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4461
  %name20 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %27, i32 0, i32 19, !dbg !4462
  %28 = load i8*, i8** %name20, align 8, !dbg !4462
  %29 = load i32, i32* %mode, align 4, !dbg !4463
  %30 = load i64, i64* %set, align 8, !dbg !4464
  %31 = load i64, i64* %clear, align 8, !dbg !4465
  %call21 = call i32 @set_fflags_platform(%struct.archive_write_disk* %24, i32 %26, i8* %28, i32 %29, i64 %30, i64 %31), !dbg !4466
  store i32 %call21, i32* %r, align 4, !dbg !4467
  %32 = load i32, i32* %r, align 4, !dbg !4468
  %cmp22 = icmp ne i32 %32, 0, !dbg !4470
  br i1 %cmp22, label %if.then24, label %if.end25, !dbg !4471

if.then24:                                        ; preds = %if.else
  %33 = load i32, i32* %r, align 4, !dbg !4472
  store i32 %33, i32* %retval, align 4, !dbg !4473
  br label %return, !dbg !4473

if.end25:                                         ; preds = %if.else
  br label %if.end26

if.end26:                                         ; preds = %if.end25, %if.end19
  br label %if.end27, !dbg !4474

if.end27:                                         ; preds = %if.end26, %entry
  store i32 0, i32* %retval, align 4, !dbg !4475
  br label %return, !dbg !4475

return:                                           ; preds = %if.end27, %if.then24, %if.then11
  %34 = load i32, i32* %retval, align 4, !dbg !4476
  ret i32 %34, !dbg !4476
}

; Function Attrs: nounwind uwtable
define internal i32 @set_times_from_entry(%struct.archive_write_disk* %a) #0 !dbg !384 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write_disk*, align 8
  %atime = alloca i64, align 8
  %birthtime = alloca i64, align 8
  %mtime = alloca i64, align 8
  %cctime = alloca i64, align 8
  %atime_nsec = alloca i64, align 8
  %birthtime_nsec = alloca i64, align 8
  %mtime_nsec = alloca i64, align 8
  %ctime_nsec = alloca i64, align 8
  store %struct.archive_write_disk* %a, %struct.archive_write_disk** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_disk** %a.addr, metadata !4477, metadata !399), !dbg !4478
  call void @llvm.dbg.declare(metadata i64* %atime, metadata !4479, metadata !399), !dbg !4480
  call void @llvm.dbg.declare(metadata i64* %birthtime, metadata !4481, metadata !399), !dbg !4482
  call void @llvm.dbg.declare(metadata i64* %mtime, metadata !4483, metadata !399), !dbg !4484
  call void @llvm.dbg.declare(metadata i64* %cctime, metadata !4485, metadata !399), !dbg !4486
  call void @llvm.dbg.declare(metadata i64* %atime_nsec, metadata !4487, metadata !399), !dbg !4488
  call void @llvm.dbg.declare(metadata i64* %birthtime_nsec, metadata !4489, metadata !399), !dbg !4490
  call void @llvm.dbg.declare(metadata i64* %mtime_nsec, metadata !4491, metadata !399), !dbg !4492
  call void @llvm.dbg.declare(metadata i64* %ctime_nsec, metadata !4493, metadata !399), !dbg !4494
  %0 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4495
  %start_time = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %0, i32 0, i32 8, !dbg !4496
  %1 = load i64, i64* %start_time, align 8, !dbg !4496
  store i64 %1, i64* %cctime, align 8, !dbg !4497
  store i64 %1, i64* %mtime, align 8, !dbg !4498
  store i64 %1, i64* %birthtime, align 8, !dbg !4499
  store i64 %1, i64* %atime, align 8, !dbg !4500
  store i64 0, i64* %ctime_nsec, align 8, !dbg !4501
  store i64 0, i64* %mtime_nsec, align 8, !dbg !4502
  store i64 0, i64* %birthtime_nsec, align 8, !dbg !4503
  store i64 0, i64* %atime_nsec, align 8, !dbg !4504
  %2 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4505
  %entry1 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %2, i32 0, i32 18, !dbg !4507
  %3 = load %struct.archive_entry*, %struct.archive_entry** %entry1, align 8, !dbg !4507
  %call = call i32 @archive_entry_atime_is_set(%struct.archive_entry* %3), !dbg !4508
  %tobool = icmp ne i32 %call, 0, !dbg !4508
  br i1 %tobool, label %if.end, label %land.lhs.true, !dbg !4509

land.lhs.true:                                    ; preds = %entry
  %4 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4510
  %entry2 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %4, i32 0, i32 18, !dbg !4512
  %5 = load %struct.archive_entry*, %struct.archive_entry** %entry2, align 8, !dbg !4512
  %call3 = call i32 @archive_entry_mtime_is_set(%struct.archive_entry* %5), !dbg !4513
  %tobool4 = icmp ne i32 %call3, 0, !dbg !4513
  br i1 %tobool4, label %if.end, label %if.then, !dbg !4514

if.then:                                          ; preds = %land.lhs.true
  store i32 0, i32* %retval, align 4, !dbg !4516
  br label %return, !dbg !4516

if.end:                                           ; preds = %land.lhs.true, %entry
  %6 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4517
  %entry5 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %6, i32 0, i32 18, !dbg !4519
  %7 = load %struct.archive_entry*, %struct.archive_entry** %entry5, align 8, !dbg !4519
  %call6 = call i32 @archive_entry_atime_is_set(%struct.archive_entry* %7), !dbg !4520
  %tobool7 = icmp ne i32 %call6, 0, !dbg !4520
  br i1 %tobool7, label %if.then8, label %if.end13, !dbg !4521

if.then8:                                         ; preds = %if.end
  %8 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4522
  %entry9 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %8, i32 0, i32 18, !dbg !4524
  %9 = load %struct.archive_entry*, %struct.archive_entry** %entry9, align 8, !dbg !4524
  %call10 = call i64 @archive_entry_atime(%struct.archive_entry* %9), !dbg !4525
  store i64 %call10, i64* %atime, align 8, !dbg !4526
  %10 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4527
  %entry11 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %10, i32 0, i32 18, !dbg !4528
  %11 = load %struct.archive_entry*, %struct.archive_entry** %entry11, align 8, !dbg !4528
  %call12 = call i64 @archive_entry_atime_nsec(%struct.archive_entry* %11), !dbg !4529
  store i64 %call12, i64* %atime_nsec, align 8, !dbg !4530
  br label %if.end13, !dbg !4531

if.end13:                                         ; preds = %if.then8, %if.end
  %12 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4532
  %entry14 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %12, i32 0, i32 18, !dbg !4534
  %13 = load %struct.archive_entry*, %struct.archive_entry** %entry14, align 8, !dbg !4534
  %call15 = call i32 @archive_entry_birthtime_is_set(%struct.archive_entry* %13), !dbg !4535
  %tobool16 = icmp ne i32 %call15, 0, !dbg !4535
  br i1 %tobool16, label %if.then17, label %if.end22, !dbg !4536

if.then17:                                        ; preds = %if.end13
  %14 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4537
  %entry18 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %14, i32 0, i32 18, !dbg !4539
  %15 = load %struct.archive_entry*, %struct.archive_entry** %entry18, align 8, !dbg !4539
  %call19 = call i64 @archive_entry_birthtime(%struct.archive_entry* %15), !dbg !4540
  store i64 %call19, i64* %birthtime, align 8, !dbg !4541
  %16 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4542
  %entry20 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %16, i32 0, i32 18, !dbg !4543
  %17 = load %struct.archive_entry*, %struct.archive_entry** %entry20, align 8, !dbg !4543
  %call21 = call i64 @archive_entry_birthtime_nsec(%struct.archive_entry* %17), !dbg !4544
  store i64 %call21, i64* %birthtime_nsec, align 8, !dbg !4545
  br label %if.end22, !dbg !4546

if.end22:                                         ; preds = %if.then17, %if.end13
  %18 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4547
  %entry23 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %18, i32 0, i32 18, !dbg !4549
  %19 = load %struct.archive_entry*, %struct.archive_entry** %entry23, align 8, !dbg !4549
  %call24 = call i32 @archive_entry_mtime_is_set(%struct.archive_entry* %19), !dbg !4550
  %tobool25 = icmp ne i32 %call24, 0, !dbg !4550
  br i1 %tobool25, label %if.then26, label %if.end31, !dbg !4551

if.then26:                                        ; preds = %if.end22
  %20 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4552
  %entry27 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %20, i32 0, i32 18, !dbg !4554
  %21 = load %struct.archive_entry*, %struct.archive_entry** %entry27, align 8, !dbg !4554
  %call28 = call i64 @archive_entry_mtime(%struct.archive_entry* %21), !dbg !4555
  store i64 %call28, i64* %mtime, align 8, !dbg !4556
  %22 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4557
  %entry29 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %22, i32 0, i32 18, !dbg !4558
  %23 = load %struct.archive_entry*, %struct.archive_entry** %entry29, align 8, !dbg !4558
  %call30 = call i64 @archive_entry_mtime_nsec(%struct.archive_entry* %23), !dbg !4559
  store i64 %call30, i64* %mtime_nsec, align 8, !dbg !4560
  br label %if.end31, !dbg !4561

if.end31:                                         ; preds = %if.then26, %if.end22
  %24 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4562
  %entry32 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %24, i32 0, i32 18, !dbg !4564
  %25 = load %struct.archive_entry*, %struct.archive_entry** %entry32, align 8, !dbg !4564
  %call33 = call i32 @archive_entry_ctime_is_set(%struct.archive_entry* %25), !dbg !4565
  %tobool34 = icmp ne i32 %call33, 0, !dbg !4565
  br i1 %tobool34, label %if.then35, label %if.end40, !dbg !4566

if.then35:                                        ; preds = %if.end31
  %26 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4567
  %entry36 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %26, i32 0, i32 18, !dbg !4569
  %27 = load %struct.archive_entry*, %struct.archive_entry** %entry36, align 8, !dbg !4569
  %call37 = call i64 @archive_entry_ctime(%struct.archive_entry* %27), !dbg !4570
  store i64 %call37, i64* %cctime, align 8, !dbg !4571
  %28 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4572
  %entry38 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %28, i32 0, i32 18, !dbg !4573
  %29 = load %struct.archive_entry*, %struct.archive_entry** %entry38, align 8, !dbg !4573
  %call39 = call i64 @archive_entry_ctime_nsec(%struct.archive_entry* %29), !dbg !4574
  store i64 %call39, i64* %ctime_nsec, align 8, !dbg !4575
  br label %if.end40, !dbg !4576

if.end40:                                         ; preds = %if.then35, %if.end31
  %30 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4577
  %31 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4578
  %fd = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %31, i32 0, i32 24, !dbg !4579
  %32 = load i32, i32* %fd, align 4, !dbg !4579
  %33 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4580
  %mode = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %33, i32 0, i32 30, !dbg !4581
  %34 = load i32, i32* %mode, align 4, !dbg !4581
  %35 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4582
  %name = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %35, i32 0, i32 19, !dbg !4583
  %36 = load i8*, i8** %name, align 8, !dbg !4583
  %37 = load i64, i64* %atime, align 8, !dbg !4584
  %38 = load i64, i64* %atime_nsec, align 8, !dbg !4585
  %39 = load i64, i64* %birthtime, align 8, !dbg !4586
  %40 = load i64, i64* %birthtime_nsec, align 8, !dbg !4587
  %41 = load i64, i64* %mtime, align 8, !dbg !4588
  %42 = load i64, i64* %mtime_nsec, align 8, !dbg !4589
  %43 = load i64, i64* %cctime, align 8, !dbg !4590
  %44 = load i64, i64* %ctime_nsec, align 8, !dbg !4591
  %call41 = call i32 @set_times(%struct.archive_write_disk* %30, i32 %32, i32 %34, i8* %36, i64 %37, i64 %38, i64 %39, i64 %40, i64 %41, i64 %42, i64 %43, i64 %44), !dbg !4592
  store i32 %call41, i32* %retval, align 4, !dbg !4593
  br label %return, !dbg !4593

return:                                           ; preds = %if.end40, %if.then
  %45 = load i32, i32* %retval, align 4, !dbg !4594
  ret i32 %45, !dbg !4594
}

; Function Attrs: nounwind
declare i32 @fstat(i32, %struct.stat*) #3

; Function Attrs: nounwind
declare i32 @fchown(i32, i32, i32) #3

; Function Attrs: nounwind
declare i32 @lchown(i8*, i32, i32) #3

; Function Attrs: nounwind
declare i32 @fchmod(i32, i32) #3

declare i32 @archive_entry_xattr_count(%struct.archive_entry*) #2

declare void @archive_entry_fflags(%struct.archive_entry*, i64*, i64*) #2

declare i32 @archive_entry_ctime_is_set(%struct.archive_entry*) #2

declare i64 @archive_entry_ctime(%struct.archive_entry*) #2

declare i64 @archive_entry_ctime_nsec(%struct.archive_entry*) #2

; Function Attrs: nounwind uwtable
define internal i64 @hfs_write_data_block(%struct.archive_write_disk* %a, i8* %buff, i64 %size) #0 !dbg !386 {
entry:
  %a.addr = alloca %struct.archive_write_disk*, align 8
  %buff.addr = alloca i8*, align 8
  %size.addr = alloca i64, align 8
  store %struct.archive_write_disk* %a, %struct.archive_write_disk** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_disk** %a.addr, metadata !4595, metadata !399), !dbg !4596
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !4597, metadata !399), !dbg !4598
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !4599, metadata !399), !dbg !4600
  %0 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4601
  %1 = load i8*, i8** %buff.addr, align 8, !dbg !4602
  %2 = load i64, i64* %size.addr, align 8, !dbg !4603
  %call = call i64 @write_data_block(%struct.archive_write_disk* %0, i8* %1, i64 %2), !dbg !4604
  ret i64 %call, !dbg !4605
}

; Function Attrs: nounwind uwtable
define internal i64 @write_data_block(%struct.archive_write_disk* %a, i8* %buff, i64 %size) #0 !dbg !389 {
entry:
  %retval = alloca i64, align 8
  %a.addr = alloca %struct.archive_write_disk*, align 8
  %buff.addr = alloca i8*, align 8
  %size.addr = alloca i64, align 8
  %start_size = alloca i64, align 8
  %bytes_written = alloca i64, align 8
  %block_size = alloca i64, align 8
  %bytes_to_write = alloca i64, align 8
  %r = alloca i32, align 4
  %p = alloca i8*, align 8
  %end = alloca i8*, align 8
  %block_end = alloca i64, align 8
  store %struct.archive_write_disk* %a, %struct.archive_write_disk** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_disk** %a.addr, metadata !4606, metadata !399), !dbg !4607
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !4608, metadata !399), !dbg !4609
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !4610, metadata !399), !dbg !4611
  call void @llvm.dbg.declare(metadata i64* %start_size, metadata !4612, metadata !399), !dbg !4613
  %0 = load i64, i64* %size.addr, align 8, !dbg !4614
  store i64 %0, i64* %start_size, align 8, !dbg !4613
  call void @llvm.dbg.declare(metadata i64* %bytes_written, metadata !4615, metadata !399), !dbg !4616
  store i64 0, i64* %bytes_written, align 8, !dbg !4616
  call void @llvm.dbg.declare(metadata i64* %block_size, metadata !4617, metadata !399), !dbg !4618
  store i64 0, i64* %block_size, align 8, !dbg !4618
  call void @llvm.dbg.declare(metadata i64* %bytes_to_write, metadata !4619, metadata !399), !dbg !4620
  %1 = load i64, i64* %size.addr, align 8, !dbg !4621
  %cmp = icmp eq i64 %1, 0, !dbg !4623
  br i1 %cmp, label %if.then, label %if.end, !dbg !4624

if.then:                                          ; preds = %entry
  store i64 0, i64* %retval, align 8, !dbg !4625
  br label %return, !dbg !4625

if.end:                                           ; preds = %entry
  %2 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4626
  %filesize = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %2, i32 0, i32 28, !dbg !4628
  %3 = load i64, i64* %filesize, align 8, !dbg !4628
  %cmp1 = icmp eq i64 %3, 0, !dbg !4629
  br i1 %cmp1, label %if.then3, label %lor.lhs.false, !dbg !4630

lor.lhs.false:                                    ; preds = %if.end
  %4 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4631
  %fd = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %4, i32 0, i32 24, !dbg !4633
  %5 = load i32, i32* %fd, align 4, !dbg !4633
  %cmp2 = icmp slt i32 %5, 0, !dbg !4634
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !4635

if.then3:                                         ; preds = %lor.lhs.false, %if.end
  %6 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4636
  %archive = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %6, i32 0, i32 0, !dbg !4638
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 0, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.51, i32 0, i32 0)), !dbg !4639
  store i64 -20, i64* %retval, align 8, !dbg !4640
  br label %return, !dbg !4640

if.end4:                                          ; preds = %lor.lhs.false
  %7 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4641
  %flags = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %7, i32 0, i32 23, !dbg !4643
  %8 = load i32, i32* %flags, align 8, !dbg !4643
  %and = and i32 %8, 4096, !dbg !4644
  %tobool = icmp ne i32 %and, 0, !dbg !4644
  br i1 %tobool, label %if.then5, label %if.end9, !dbg !4645

if.then5:                                         ; preds = %if.end4
  call void @llvm.dbg.declare(metadata i32* %r, metadata !4646, metadata !399), !dbg !4648
  %9 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4649
  %call = call i32 @lazy_stat(%struct.archive_write_disk* %9), !dbg !4651
  store i32 %call, i32* %r, align 4, !dbg !4652
  %cmp6 = icmp ne i32 %call, 0, !dbg !4653
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !4654

if.then7:                                         ; preds = %if.then5
  %10 = load i32, i32* %r, align 4, !dbg !4655
  %conv = sext i32 %10 to i64, !dbg !4656
  store i64 %conv, i64* %retval, align 8, !dbg !4657
  br label %return, !dbg !4657

if.end8:                                          ; preds = %if.then5
  %11 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4658
  %pst = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %11, i32 0, i32 17, !dbg !4659
  %12 = load %struct.stat*, %struct.stat** %pst, align 8, !dbg !4659
  %st_blksize = getelementptr inbounds %struct.stat, %struct.stat* %12, i32 0, i32 9, !dbg !4660
  %13 = load i64, i64* %st_blksize, align 8, !dbg !4660
  store i64 %13, i64* %block_size, align 8, !dbg !4661
  br label %if.end9, !dbg !4662

if.end9:                                          ; preds = %if.end8, %if.end4
  %14 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4663
  %filesize10 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %14, i32 0, i32 28, !dbg !4665
  %15 = load i64, i64* %filesize10, align 8, !dbg !4665
  %cmp11 = icmp sge i64 %15, 0, !dbg !4666
  br i1 %cmp11, label %land.lhs.true, label %if.end19, !dbg !4667

land.lhs.true:                                    ; preds = %if.end9
  %16 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4668
  %offset = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %16, i32 0, i32 25, !dbg !4670
  %17 = load i64, i64* %offset, align 8, !dbg !4670
  %18 = load i64, i64* %size.addr, align 8, !dbg !4671
  %add = add i64 %17, %18, !dbg !4672
  %19 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4673
  %filesize13 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %19, i32 0, i32 28, !dbg !4674
  %20 = load i64, i64* %filesize13, align 8, !dbg !4674
  %cmp14 = icmp sgt i64 %add, %20, !dbg !4675
  br i1 %cmp14, label %if.then16, label %if.end19, !dbg !4676

if.then16:                                        ; preds = %land.lhs.true
  %21 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4677
  %filesize17 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %21, i32 0, i32 28, !dbg !4678
  %22 = load i64, i64* %filesize17, align 8, !dbg !4678
  %23 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4679
  %offset18 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %23, i32 0, i32 25, !dbg !4680
  %24 = load i64, i64* %offset18, align 8, !dbg !4680
  %sub = sub nsw i64 %22, %24, !dbg !4681
  store i64 %sub, i64* %size.addr, align 8, !dbg !4682
  store i64 %sub, i64* %start_size, align 8, !dbg !4683
  br label %if.end19, !dbg !4684

if.end19:                                         ; preds = %if.then16, %land.lhs.true, %if.end9
  br label %while.cond, !dbg !4685

while.cond:                                       ; preds = %if.end76, %if.end19
  %25 = load i64, i64* %size.addr, align 8, !dbg !4686
  %cmp20 = icmp ugt i64 %25, 0, !dbg !4688
  br i1 %cmp20, label %while.body, label %while.end, !dbg !4689

while.body:                                       ; preds = %while.cond
  %26 = load i64, i64* %block_size, align 8, !dbg !4690
  %cmp22 = icmp eq i64 %26, 0, !dbg !4693
  br i1 %cmp22, label %if.then24, label %if.else, !dbg !4694

if.then24:                                        ; preds = %while.body
  %27 = load i64, i64* %size.addr, align 8, !dbg !4695
  store i64 %27, i64* %bytes_to_write, align 8, !dbg !4697
  br label %if.end52, !dbg !4698

if.else:                                          ; preds = %while.body
  call void @llvm.dbg.declare(metadata i8** %p, metadata !4699, metadata !399), !dbg !4701
  call void @llvm.dbg.declare(metadata i8** %end, metadata !4702, metadata !399), !dbg !4703
  call void @llvm.dbg.declare(metadata i64* %block_end, metadata !4704, metadata !399), !dbg !4705
  %28 = load i8*, i8** %buff.addr, align 8, !dbg !4706
  store i8* %28, i8** %p, align 8, !dbg !4708
  %29 = load i8*, i8** %buff.addr, align 8, !dbg !4709
  %30 = load i64, i64* %size.addr, align 8, !dbg !4710
  %add.ptr = getelementptr inbounds i8, i8* %29, i64 %30, !dbg !4711
  store i8* %add.ptr, i8** %end, align 8, !dbg !4712
  br label %for.cond, !dbg !4713

for.cond:                                         ; preds = %for.inc, %if.else
  %31 = load i8*, i8** %p, align 8, !dbg !4714
  %32 = load i8*, i8** %end, align 8, !dbg !4717
  %cmp25 = icmp ult i8* %31, %32, !dbg !4718
  br i1 %cmp25, label %for.body, label %for.end, !dbg !4719

for.body:                                         ; preds = %for.cond
  %33 = load i8*, i8** %p, align 8, !dbg !4720
  %34 = load i8, i8* %33, align 1, !dbg !4723
  %conv27 = sext i8 %34 to i32, !dbg !4723
  %cmp28 = icmp ne i32 %conv27, 0, !dbg !4724
  br i1 %cmp28, label %if.then30, label %if.end31, !dbg !4725

if.then30:                                        ; preds = %for.body
  br label %for.end, !dbg !4726

if.end31:                                         ; preds = %for.body
  br label %for.inc, !dbg !4727

for.inc:                                          ; preds = %if.end31
  %35 = load i8*, i8** %p, align 8, !dbg !4728
  %incdec.ptr = getelementptr inbounds i8, i8* %35, i32 1, !dbg !4728
  store i8* %incdec.ptr, i8** %p, align 8, !dbg !4728
  br label %for.cond, !dbg !4730

for.end:                                          ; preds = %if.then30, %for.cond
  %36 = load i8*, i8** %p, align 8, !dbg !4731
  %37 = load i8*, i8** %buff.addr, align 8, !dbg !4732
  %sub.ptr.lhs.cast = ptrtoint i8* %36 to i64, !dbg !4733
  %sub.ptr.rhs.cast = ptrtoint i8* %37 to i64, !dbg !4733
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !4733
  %38 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4734
  %offset32 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %38, i32 0, i32 25, !dbg !4735
  %39 = load i64, i64* %offset32, align 8, !dbg !4736
  %add33 = add nsw i64 %39, %sub.ptr.sub, !dbg !4736
  store i64 %add33, i64* %offset32, align 8, !dbg !4736
  %40 = load i8*, i8** %p, align 8, !dbg !4737
  %41 = load i8*, i8** %buff.addr, align 8, !dbg !4738
  %sub.ptr.lhs.cast34 = ptrtoint i8* %40 to i64, !dbg !4739
  %sub.ptr.rhs.cast35 = ptrtoint i8* %41 to i64, !dbg !4739
  %sub.ptr.sub36 = sub i64 %sub.ptr.lhs.cast34, %sub.ptr.rhs.cast35, !dbg !4739
  %42 = load i64, i64* %size.addr, align 8, !dbg !4740
  %sub37 = sub i64 %42, %sub.ptr.sub36, !dbg !4740
  store i64 %sub37, i64* %size.addr, align 8, !dbg !4740
  %43 = load i8*, i8** %p, align 8, !dbg !4741
  store i8* %43, i8** %buff.addr, align 8, !dbg !4742
  %44 = load i64, i64* %size.addr, align 8, !dbg !4743
  %cmp38 = icmp eq i64 %44, 0, !dbg !4745
  br i1 %cmp38, label %if.then40, label %if.end41, !dbg !4746

if.then40:                                        ; preds = %for.end
  br label %while.end, !dbg !4747

if.end41:                                         ; preds = %for.end
  %45 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4748
  %offset42 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %45, i32 0, i32 25, !dbg !4749
  %46 = load i64, i64* %offset42, align 8, !dbg !4749
  %47 = load i64, i64* %block_size, align 8, !dbg !4750
  %div = sdiv i64 %46, %47, !dbg !4751
  %add43 = add nsw i64 %div, 1, !dbg !4752
  %48 = load i64, i64* %block_size, align 8, !dbg !4753
  %mul = mul nsw i64 %add43, %48, !dbg !4754
  store i64 %mul, i64* %block_end, align 8, !dbg !4755
  %49 = load i64, i64* %size.addr, align 8, !dbg !4756
  store i64 %49, i64* %bytes_to_write, align 8, !dbg !4757
  %50 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4758
  %offset44 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %50, i32 0, i32 25, !dbg !4760
  %51 = load i64, i64* %offset44, align 8, !dbg !4760
  %52 = load i64, i64* %bytes_to_write, align 8, !dbg !4761
  %add45 = add nsw i64 %51, %52, !dbg !4762
  %53 = load i64, i64* %block_end, align 8, !dbg !4763
  %cmp46 = icmp sgt i64 %add45, %53, !dbg !4764
  br i1 %cmp46, label %if.then48, label %if.end51, !dbg !4765

if.then48:                                        ; preds = %if.end41
  %54 = load i64, i64* %block_end, align 8, !dbg !4766
  %55 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4767
  %offset49 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %55, i32 0, i32 25, !dbg !4768
  %56 = load i64, i64* %offset49, align 8, !dbg !4768
  %sub50 = sub nsw i64 %54, %56, !dbg !4769
  store i64 %sub50, i64* %bytes_to_write, align 8, !dbg !4770
  br label %if.end51, !dbg !4771

if.end51:                                         ; preds = %if.then48, %if.end41
  br label %if.end52

if.end52:                                         ; preds = %if.end51, %if.then24
  %57 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4772
  %offset53 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %57, i32 0, i32 25, !dbg !4774
  %58 = load i64, i64* %offset53, align 8, !dbg !4774
  %59 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4775
  %fd_offset = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %59, i32 0, i32 26, !dbg !4776
  %60 = load i64, i64* %fd_offset, align 8, !dbg !4776
  %cmp54 = icmp ne i64 %58, %60, !dbg !4777
  br i1 %cmp54, label %if.then56, label %if.end68, !dbg !4778

if.then56:                                        ; preds = %if.end52
  %61 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4779
  %fd57 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %61, i32 0, i32 24, !dbg !4782
  %62 = load i32, i32* %fd57, align 4, !dbg !4782
  %63 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4783
  %offset58 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %63, i32 0, i32 25, !dbg !4784
  %64 = load i64, i64* %offset58, align 8, !dbg !4784
  %call59 = call i64 @lseek(i32 %62, i64 %64, i32 0) #7, !dbg !4785
  %cmp60 = icmp slt i64 %call59, 0, !dbg !4786
  br i1 %cmp60, label %if.then62, label %if.end65, !dbg !4787

if.then62:                                        ; preds = %if.then56
  %65 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4788
  %archive63 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %65, i32 0, i32 0, !dbg !4790
  %call64 = call i32* @__errno_location() #1, !dbg !4791
  %66 = load i32, i32* %call64, align 4, !dbg !4791
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive63, i32 %66, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.40, i32 0, i32 0)), !dbg !4792
  store i64 -30, i64* %retval, align 8, !dbg !4794
  br label %return, !dbg !4794

if.end65:                                         ; preds = %if.then56
  %67 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4795
  %offset66 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %67, i32 0, i32 25, !dbg !4796
  %68 = load i64, i64* %offset66, align 8, !dbg !4796
  %69 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4797
  %fd_offset67 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %69, i32 0, i32 26, !dbg !4798
  store i64 %68, i64* %fd_offset67, align 8, !dbg !4799
  br label %if.end68, !dbg !4800

if.end68:                                         ; preds = %if.end65, %if.end52
  %70 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4801
  %fd69 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %70, i32 0, i32 24, !dbg !4802
  %71 = load i32, i32* %fd69, align 4, !dbg !4802
  %72 = load i8*, i8** %buff.addr, align 8, !dbg !4803
  %73 = load i64, i64* %bytes_to_write, align 8, !dbg !4804
  %call70 = call i64 @write(i32 %71, i8* %72, i64 %73), !dbg !4805
  store i64 %call70, i64* %bytes_written, align 8, !dbg !4806
  %74 = load i64, i64* %bytes_written, align 8, !dbg !4807
  %cmp71 = icmp slt i64 %74, 0, !dbg !4809
  br i1 %cmp71, label %if.then73, label %if.end76, !dbg !4810

if.then73:                                        ; preds = %if.end68
  %75 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4811
  %archive74 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %75, i32 0, i32 0, !dbg !4813
  %call75 = call i32* @__errno_location() #1, !dbg !4814
  %76 = load i32, i32* %call75, align 4, !dbg !4814
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive74, i32 %76, i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.52, i32 0, i32 0)), !dbg !4815
  store i64 -20, i64* %retval, align 8, !dbg !4817
  br label %return, !dbg !4817

if.end76:                                         ; preds = %if.end68
  %77 = load i64, i64* %bytes_written, align 8, !dbg !4818
  %78 = load i8*, i8** %buff.addr, align 8, !dbg !4819
  %add.ptr77 = getelementptr inbounds i8, i8* %78, i64 %77, !dbg !4819
  store i8* %add.ptr77, i8** %buff.addr, align 8, !dbg !4819
  %79 = load i64, i64* %bytes_written, align 8, !dbg !4820
  %80 = load i64, i64* %size.addr, align 8, !dbg !4821
  %sub78 = sub i64 %80, %79, !dbg !4821
  store i64 %sub78, i64* %size.addr, align 8, !dbg !4821
  %81 = load i64, i64* %bytes_written, align 8, !dbg !4822
  %82 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4823
  %total_bytes_written = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %82, i32 0, i32 27, !dbg !4824
  %83 = load i64, i64* %total_bytes_written, align 8, !dbg !4825
  %add79 = add nsw i64 %83, %81, !dbg !4825
  store i64 %add79, i64* %total_bytes_written, align 8, !dbg !4825
  %84 = load i64, i64* %bytes_written, align 8, !dbg !4826
  %85 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4827
  %offset80 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %85, i32 0, i32 25, !dbg !4828
  %86 = load i64, i64* %offset80, align 8, !dbg !4829
  %add81 = add nsw i64 %86, %84, !dbg !4829
  store i64 %add81, i64* %offset80, align 8, !dbg !4829
  %87 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4830
  %offset82 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %87, i32 0, i32 25, !dbg !4831
  %88 = load i64, i64* %offset82, align 8, !dbg !4831
  %89 = load %struct.archive_write_disk*, %struct.archive_write_disk** %a.addr, align 8, !dbg !4832
  %fd_offset83 = getelementptr inbounds %struct.archive_write_disk, %struct.archive_write_disk* %89, i32 0, i32 26, !dbg !4833
  store i64 %88, i64* %fd_offset83, align 8, !dbg !4834
  br label %while.cond, !dbg !4835

while.end:                                        ; preds = %if.then40, %while.cond
  %90 = load i64, i64* %start_size, align 8, !dbg !4837
  %91 = load i64, i64* %size.addr, align 8, !dbg !4838
  %sub84 = sub i64 %90, %91, !dbg !4839
  store i64 %sub84, i64* %retval, align 8, !dbg !4840
  br label %return, !dbg !4840

return:                                           ; preds = %while.end, %if.then73, %if.then62, %if.then7, %if.then3, %if.then
  %92 = load i64, i64* %retval, align 8, !dbg !4841
  ret i64 %92, !dbg !4841
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { argmemonly nounwind }
attributes #7 = { nounwind }
attributes #8 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!395, !396}
!llvm.ident = !{!397}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !304, globals: !391)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_disk_posix.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !163, !110, !113, !299, !300, !51, !301, !302, !22, !44, !303}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !5, size: 64, align: 64)
!5 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_write_disk", file: !1, line: 216, size: 6336, align: 64, elements: !6)
!6 = !{!7, !109, !112, !166, !167, !168, !169, !170, !171, !175, !179, !183, !184, !185, !186, !187, !188, !223, !225, !226, !227, !228, !229, !230, !231, !232, !233, !234, !235, !236, !237, !238, !239, !240, !242, !245, !246, !247, !248, !249, !251, !252, !253, !254, !255, !256, !257, !258, !259, !297, !298}
!7 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !5, file: !1, line: 217, baseType: !8, size: 1280, align: 64)
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
!109 = !DIDerivedType(tag: DW_TAG_member, name: "user_umask", scope: !5, file: !1, line: 219, baseType: !110, size: 32, align: 32, offset: 1280)
!110 = !DIDerivedType(tag: DW_TAG_typedef, name: "mode_t", file: !38, line: 70, baseType: !111)
!111 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !40, line: 129, baseType: !12)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "fixup_list", scope: !5, file: !1, line: 220, baseType: !113, size: 64, align: 64, offset: 1344)
!113 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !114, size: 64, align: 64)
!114 = !DICompositeType(tag: DW_TAG_structure_type, name: "fixup_entry", file: !1, line: 168, size: 1408, align: 64, elements: !115)
!115 = !{!116, !117, !151, !152, !153, !154, !155, !156, !157, !158, !159, !160, !161, !162, !164, !165}
!116 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !114, file: !1, line: 169, baseType: !113, size: 64, align: 64)
!117 = !DIDerivedType(tag: DW_TAG_member, name: "acl", scope: !114, file: !1, line: 170, baseType: !118, size: 448, align: 64, offset: 64)
!118 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_acl", file: !119, line: 46, size: 448, align: 64, elements: !120)
!119 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_acl_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!120 = !{!121, !122, !146, !147, !148, !149, !150}
!121 = !DIDerivedType(tag: DW_TAG_member, name: "mode", scope: !118, file: !119, line: 47, baseType: !110, size: 32, align: 32)
!122 = !DIDerivedType(tag: DW_TAG_member, name: "acl_head", scope: !118, file: !119, line: 48, baseType: !123, size: 64, align: 64, offset: 64)
!123 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !124, size: 64, align: 64)
!124 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_acl_entry", file: !119, line: 37, size: 1024, align: 64, elements: !125)
!125 = !{!126, !127, !128, !129, !130, !131}
!126 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !124, file: !119, line: 38, baseType: !123, size: 64, align: 64)
!127 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !124, file: !119, line: 39, baseType: !22, size: 32, align: 32, offset: 64)
!128 = !DIDerivedType(tag: DW_TAG_member, name: "tag", scope: !124, file: !119, line: 40, baseType: !22, size: 32, align: 32, offset: 96)
!129 = !DIDerivedType(tag: DW_TAG_member, name: "permset", scope: !124, file: !119, line: 41, baseType: !22, size: 32, align: 32, offset: 128)
!130 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !124, file: !119, line: 42, baseType: !22, size: 32, align: 32, offset: 160)
!131 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !124, file: !119, line: 43, baseType: !132, size: 832, align: 64, offset: 192)
!132 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_mstring", file: !91, line: 209, size: 832, align: 64, elements: !133)
!133 = !{!134, !135, !136, !144, !145}
!134 = !DIDerivedType(tag: DW_TAG_member, name: "aes_mbs", scope: !132, file: !91, line: 210, baseType: !90, size: 192, align: 64)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "aes_utf8", scope: !132, file: !91, line: 211, baseType: !90, size: 192, align: 64, offset: 192)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "aes_wcs", scope: !132, file: !91, line: 212, baseType: !137, size: 192, align: 64, offset: 384)
!137 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_wstring", file: !91, line: 64, size: 192, align: 64, elements: !138)
!138 = !{!139, !142, !143}
!139 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !137, file: !91, line: 65, baseType: !140, size: 64, align: 64)
!140 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !141, size: 64, align: 64)
!141 = !DIDerivedType(tag: DW_TAG_typedef, name: "wchar_t", file: !45, line: 90, baseType: !22)
!142 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !137, file: !91, line: 66, baseType: !44, size: 64, align: 64, offset: 64)
!143 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !137, file: !91, line: 67, baseType: !44, size: 64, align: 64, offset: 128)
!144 = !DIDerivedType(tag: DW_TAG_member, name: "aes_mbs_in_locale", scope: !132, file: !91, line: 213, baseType: !90, size: 192, align: 64, offset: 576)
!145 = !DIDerivedType(tag: DW_TAG_member, name: "aes_set", scope: !132, file: !91, line: 218, baseType: !22, size: 32, align: 32, offset: 768)
!146 = !DIDerivedType(tag: DW_TAG_member, name: "acl_p", scope: !118, file: !119, line: 49, baseType: !123, size: 64, align: 64, offset: 128)
!147 = !DIDerivedType(tag: DW_TAG_member, name: "acl_state", scope: !118, file: !119, line: 50, baseType: !22, size: 32, align: 32, offset: 192)
!148 = !DIDerivedType(tag: DW_TAG_member, name: "acl_text_w", scope: !118, file: !119, line: 51, baseType: !140, size: 64, align: 64, offset: 256)
!149 = !DIDerivedType(tag: DW_TAG_member, name: "acl_text", scope: !118, file: !119, line: 52, baseType: !94, size: 64, align: 64, offset: 320)
!150 = !DIDerivedType(tag: DW_TAG_member, name: "acl_types", scope: !118, file: !119, line: 53, baseType: !22, size: 32, align: 32, offset: 384)
!151 = !DIDerivedType(tag: DW_TAG_member, name: "mode", scope: !114, file: !1, line: 171, baseType: !110, size: 32, align: 32, offset: 512)
!152 = !DIDerivedType(tag: DW_TAG_member, name: "atime", scope: !114, file: !1, line: 172, baseType: !51, size: 64, align: 64, offset: 576)
!153 = !DIDerivedType(tag: DW_TAG_member, name: "birthtime", scope: !114, file: !1, line: 173, baseType: !51, size: 64, align: 64, offset: 640)
!154 = !DIDerivedType(tag: DW_TAG_member, name: "mtime", scope: !114, file: !1, line: 174, baseType: !51, size: 64, align: 64, offset: 704)
!155 = !DIDerivedType(tag: DW_TAG_member, name: "ctime", scope: !114, file: !1, line: 175, baseType: !51, size: 64, align: 64, offset: 768)
!156 = !DIDerivedType(tag: DW_TAG_member, name: "atime_nanos", scope: !114, file: !1, line: 176, baseType: !46, size: 64, align: 64, offset: 832)
!157 = !DIDerivedType(tag: DW_TAG_member, name: "birthtime_nanos", scope: !114, file: !1, line: 177, baseType: !46, size: 64, align: 64, offset: 896)
!158 = !DIDerivedType(tag: DW_TAG_member, name: "mtime_nanos", scope: !114, file: !1, line: 178, baseType: !46, size: 64, align: 64, offset: 960)
!159 = !DIDerivedType(tag: DW_TAG_member, name: "ctime_nanos", scope: !114, file: !1, line: 179, baseType: !46, size: 64, align: 64, offset: 1024)
!160 = !DIDerivedType(tag: DW_TAG_member, name: "fflags_set", scope: !114, file: !1, line: 180, baseType: !46, size: 64, align: 64, offset: 1088)
!161 = !DIDerivedType(tag: DW_TAG_member, name: "mac_metadata_size", scope: !114, file: !1, line: 181, baseType: !44, size: 64, align: 64, offset: 1152)
!162 = !DIDerivedType(tag: DW_TAG_member, name: "mac_metadata", scope: !114, file: !1, line: 182, baseType: !163, size: 64, align: 64, offset: 1216)
!163 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!164 = !DIDerivedType(tag: DW_TAG_member, name: "fixup", scope: !114, file: !1, line: 183, baseType: !22, size: 32, align: 32, offset: 1280)
!165 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !114, file: !1, line: 184, baseType: !94, size: 64, align: 64, offset: 1344)
!166 = !DIDerivedType(tag: DW_TAG_member, name: "current_fixup", scope: !5, file: !1, line: 221, baseType: !113, size: 64, align: 64, offset: 1408)
!167 = !DIDerivedType(tag: DW_TAG_member, name: "user_uid", scope: !5, file: !1, line: 222, baseType: !51, size: 64, align: 64, offset: 1472)
!168 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_set", scope: !5, file: !1, line: 223, baseType: !22, size: 32, align: 32, offset: 1536)
!169 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_dev", scope: !5, file: !1, line: 224, baseType: !51, size: 64, align: 64, offset: 1600)
!170 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_ino", scope: !5, file: !1, line: 225, baseType: !51, size: 64, align: 64, offset: 1664)
!171 = !DIDerivedType(tag: DW_TAG_member, name: "start_time", scope: !5, file: !1, line: 226, baseType: !172, size: 64, align: 64, offset: 1728)
!172 = !DIDerivedType(tag: DW_TAG_typedef, name: "time_t", file: !173, line: 75, baseType: !174)
!173 = !DIFile(filename: "/usr/include/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!174 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !40, line: 139, baseType: !41)
!175 = !DIDerivedType(tag: DW_TAG_member, name: "lookup_gid", scope: !5, file: !1, line: 228, baseType: !176, size: 64, align: 64, offset: 1792)
!176 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !177, size: 64, align: 64)
!177 = !DISubroutineType(types: !178)
!178 = !{!51, !163, !79, !51}
!179 = !DIDerivedType(tag: DW_TAG_member, name: "cleanup_gid", scope: !5, file: !1, line: 229, baseType: !180, size: 64, align: 64, offset: 1856)
!180 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !181, size: 64, align: 64)
!181 = !DISubroutineType(types: !182)
!182 = !{null, !163}
!183 = !DIDerivedType(tag: DW_TAG_member, name: "lookup_gid_data", scope: !5, file: !1, line: 230, baseType: !163, size: 64, align: 64, offset: 1920)
!184 = !DIDerivedType(tag: DW_TAG_member, name: "lookup_uid", scope: !5, file: !1, line: 231, baseType: !176, size: 64, align: 64, offset: 1984)
!185 = !DIDerivedType(tag: DW_TAG_member, name: "cleanup_uid", scope: !5, file: !1, line: 232, baseType: !180, size: 64, align: 64, offset: 2048)
!186 = !DIDerivedType(tag: DW_TAG_member, name: "lookup_uid_data", scope: !5, file: !1, line: 233, baseType: !163, size: 64, align: 64, offset: 2112)
!187 = !DIDerivedType(tag: DW_TAG_member, name: "path_safe", scope: !5, file: !1, line: 238, baseType: !90, size: 192, align: 64, offset: 2176)
!188 = !DIDerivedType(tag: DW_TAG_member, name: "st", scope: !5, file: !1, line: 245, baseType: !189, size: 1152, align: 64, offset: 2368)
!189 = !DICompositeType(tag: DW_TAG_structure_type, name: "stat", file: !190, line: 46, size: 1152, align: 64, elements: !191)
!190 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/stat.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!191 = !{!192, !194, !196, !198, !199, !201, !203, !204, !205, !207, !209, !211, !217, !218, !219}
!192 = !DIDerivedType(tag: DW_TAG_member, name: "st_dev", scope: !189, file: !190, line: 48, baseType: !193, size: 64, align: 64)
!193 = !DIDerivedType(tag: DW_TAG_typedef, name: "__dev_t", file: !40, line: 124, baseType: !46)
!194 = !DIDerivedType(tag: DW_TAG_member, name: "st_ino", scope: !189, file: !190, line: 53, baseType: !195, size: 64, align: 64, offset: 64)
!195 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ino_t", file: !40, line: 127, baseType: !46)
!196 = !DIDerivedType(tag: DW_TAG_member, name: "st_nlink", scope: !189, file: !190, line: 61, baseType: !197, size: 64, align: 64, offset: 128)
!197 = !DIDerivedType(tag: DW_TAG_typedef, name: "__nlink_t", file: !40, line: 130, baseType: !46)
!198 = !DIDerivedType(tag: DW_TAG_member, name: "st_mode", scope: !189, file: !190, line: 62, baseType: !111, size: 32, align: 32, offset: 192)
!199 = !DIDerivedType(tag: DW_TAG_member, name: "st_uid", scope: !189, file: !190, line: 64, baseType: !200, size: 32, align: 32, offset: 224)
!200 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uid_t", file: !40, line: 125, baseType: !12)
!201 = !DIDerivedType(tag: DW_TAG_member, name: "st_gid", scope: !189, file: !190, line: 65, baseType: !202, size: 32, align: 32, offset: 256)
!202 = !DIDerivedType(tag: DW_TAG_typedef, name: "__gid_t", file: !40, line: 126, baseType: !12)
!203 = !DIDerivedType(tag: DW_TAG_member, name: "__pad0", scope: !189, file: !190, line: 67, baseType: !22, size: 32, align: 32, offset: 288)
!204 = !DIDerivedType(tag: DW_TAG_member, name: "st_rdev", scope: !189, file: !190, line: 69, baseType: !193, size: 64, align: 64, offset: 320)
!205 = !DIDerivedType(tag: DW_TAG_member, name: "st_size", scope: !189, file: !190, line: 74, baseType: !206, size: 64, align: 64, offset: 384)
!206 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off_t", file: !40, line: 131, baseType: !41)
!207 = !DIDerivedType(tag: DW_TAG_member, name: "st_blksize", scope: !189, file: !190, line: 78, baseType: !208, size: 64, align: 64, offset: 448)
!208 = !DIDerivedType(tag: DW_TAG_typedef, name: "__blksize_t", file: !40, line: 153, baseType: !41)
!209 = !DIDerivedType(tag: DW_TAG_member, name: "st_blocks", scope: !189, file: !190, line: 80, baseType: !210, size: 64, align: 64, offset: 512)
!210 = !DIDerivedType(tag: DW_TAG_typedef, name: "__blkcnt_t", file: !40, line: 158, baseType: !41)
!211 = !DIDerivedType(tag: DW_TAG_member, name: "st_atim", scope: !189, file: !190, line: 91, baseType: !212, size: 128, align: 64, offset: 576)
!212 = !DICompositeType(tag: DW_TAG_structure_type, name: "timespec", file: !173, line: 120, size: 128, align: 64, elements: !213)
!213 = !{!214, !215}
!214 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !212, file: !173, line: 122, baseType: !174, size: 64, align: 64)
!215 = !DIDerivedType(tag: DW_TAG_member, name: "tv_nsec", scope: !212, file: !173, line: 123, baseType: !216, size: 64, align: 64, offset: 64)
!216 = !DIDerivedType(tag: DW_TAG_typedef, name: "__syscall_slong_t", file: !40, line: 175, baseType: !41)
!217 = !DIDerivedType(tag: DW_TAG_member, name: "st_mtim", scope: !189, file: !190, line: 92, baseType: !212, size: 128, align: 64, offset: 704)
!218 = !DIDerivedType(tag: DW_TAG_member, name: "st_ctim", scope: !189, file: !190, line: 93, baseType: !212, size: 128, align: 64, offset: 832)
!219 = !DIDerivedType(tag: DW_TAG_member, name: "__glibc_reserved", scope: !189, file: !190, line: 106, baseType: !220, size: 192, align: 64, offset: 960)
!220 = !DICompositeType(tag: DW_TAG_array_type, baseType: !216, size: 192, align: 64, elements: !221)
!221 = !{!222}
!222 = !DISubrange(count: 3)
!223 = !DIDerivedType(tag: DW_TAG_member, name: "pst", scope: !5, file: !1, line: 246, baseType: !224, size: 64, align: 64, offset: 3520)
!224 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !189, size: 64, align: 64)
!225 = !DIDerivedType(tag: DW_TAG_member, name: "entry", scope: !5, file: !1, line: 249, baseType: !29, size: 64, align: 64, offset: 3584)
!226 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !5, file: !1, line: 250, baseType: !94, size: 64, align: 64, offset: 3648)
!227 = !DIDerivedType(tag: DW_TAG_member, name: "_name_data", scope: !5, file: !1, line: 251, baseType: !90, size: 192, align: 64, offset: 3712)
!228 = !DIDerivedType(tag: DW_TAG_member, name: "todo", scope: !5, file: !1, line: 253, baseType: !22, size: 32, align: 32, offset: 3904)
!229 = !DIDerivedType(tag: DW_TAG_member, name: "deferred", scope: !5, file: !1, line: 255, baseType: !22, size: 32, align: 32, offset: 3936)
!230 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !5, file: !1, line: 257, baseType: !22, size: 32, align: 32, offset: 3968)
!231 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !5, file: !1, line: 259, baseType: !22, size: 32, align: 32, offset: 4000)
!232 = !DIDerivedType(tag: DW_TAG_member, name: "offset", scope: !5, file: !1, line: 261, baseType: !51, size: 64, align: 64, offset: 4032)
!233 = !DIDerivedType(tag: DW_TAG_member, name: "fd_offset", scope: !5, file: !1, line: 263, baseType: !51, size: 64, align: 64, offset: 4096)
!234 = !DIDerivedType(tag: DW_TAG_member, name: "total_bytes_written", scope: !5, file: !1, line: 265, baseType: !51, size: 64, align: 64, offset: 4160)
!235 = !DIDerivedType(tag: DW_TAG_member, name: "filesize", scope: !5, file: !1, line: 267, baseType: !51, size: 64, align: 64, offset: 4224)
!236 = !DIDerivedType(tag: DW_TAG_member, name: "restore_pwd", scope: !5, file: !1, line: 269, baseType: !22, size: 32, align: 32, offset: 4288)
!237 = !DIDerivedType(tag: DW_TAG_member, name: "mode", scope: !5, file: !1, line: 271, baseType: !110, size: 32, align: 32, offset: 4320)
!238 = !DIDerivedType(tag: DW_TAG_member, name: "uid", scope: !5, file: !1, line: 273, baseType: !51, size: 64, align: 64, offset: 4352)
!239 = !DIDerivedType(tag: DW_TAG_member, name: "gid", scope: !5, file: !1, line: 274, baseType: !51, size: 64, align: 64, offset: 4416)
!240 = !DIDerivedType(tag: DW_TAG_member, name: "decmpfs_attr_size", scope: !5, file: !1, line: 279, baseType: !241, size: 32, align: 32, offset: 4480)
!241 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !52, line: 51, baseType: !12)
!242 = !DIDerivedType(tag: DW_TAG_member, name: "decmpfs_header_p", scope: !5, file: !1, line: 280, baseType: !243, size: 64, align: 64, offset: 4544)
!243 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !244, size: 64, align: 64)
!244 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!245 = !DIDerivedType(tag: DW_TAG_member, name: "rsrc_xattr_options", scope: !5, file: !1, line: 282, baseType: !22, size: 32, align: 32, offset: 4608)
!246 = !DIDerivedType(tag: DW_TAG_member, name: "resource_fork", scope: !5, file: !1, line: 284, baseType: !243, size: 64, align: 64, offset: 4672)
!247 = !DIDerivedType(tag: DW_TAG_member, name: "resource_fork_allocated_size", scope: !5, file: !1, line: 285, baseType: !44, size: 64, align: 64, offset: 4736)
!248 = !DIDerivedType(tag: DW_TAG_member, name: "decmpfs_block_count", scope: !5, file: !1, line: 286, baseType: !12, size: 32, align: 32, offset: 4800)
!249 = !DIDerivedType(tag: DW_TAG_member, name: "decmpfs_block_info", scope: !5, file: !1, line: 287, baseType: !250, size: 64, align: 64, offset: 4864)
!250 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !241, size: 64, align: 64)
!251 = !DIDerivedType(tag: DW_TAG_member, name: "compressed_buffer", scope: !5, file: !1, line: 289, baseType: !243, size: 64, align: 64, offset: 4928)
!252 = !DIDerivedType(tag: DW_TAG_member, name: "compressed_buffer_size", scope: !5, file: !1, line: 290, baseType: !44, size: 64, align: 64, offset: 4992)
!253 = !DIDerivedType(tag: DW_TAG_member, name: "compressed_buffer_remaining", scope: !5, file: !1, line: 291, baseType: !44, size: 64, align: 64, offset: 5056)
!254 = !DIDerivedType(tag: DW_TAG_member, name: "compressed_rsrc_position", scope: !5, file: !1, line: 294, baseType: !241, size: 32, align: 32, offset: 5120)
!255 = !DIDerivedType(tag: DW_TAG_member, name: "compressed_rsrc_position_v", scope: !5, file: !1, line: 295, baseType: !241, size: 32, align: 32, offset: 5152)
!256 = !DIDerivedType(tag: DW_TAG_member, name: "uncompressed_buffer", scope: !5, file: !1, line: 297, baseType: !94, size: 64, align: 64, offset: 5184)
!257 = !DIDerivedType(tag: DW_TAG_member, name: "block_remaining_bytes", scope: !5, file: !1, line: 298, baseType: !44, size: 64, align: 64, offset: 5248)
!258 = !DIDerivedType(tag: DW_TAG_member, name: "file_remaining_bytes", scope: !5, file: !1, line: 299, baseType: !44, size: 64, align: 64, offset: 5312)
!259 = !DIDerivedType(tag: DW_TAG_member, name: "stream", scope: !5, file: !1, line: 301, baseType: !260, size: 896, align: 64, offset: 5376)
!260 = !DIDerivedType(tag: DW_TAG_typedef, name: "z_stream", file: !261, line: 101, baseType: !262)
!261 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmzlib/zlib.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!262 = !DICompositeType(tag: DW_TAG_structure_type, name: "z_stream_s", file: !261, line: 82, size: 896, align: 64, elements: !263)
!263 = !{!264, !269, !271, !273, !274, !275, !276, !277, !282, !288, !293, !294, !295, !296}
!264 = !DIDerivedType(tag: DW_TAG_member, name: "next_in", scope: !262, file: !261, line: 83, baseType: !265, size: 64, align: 64)
!265 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !266, size: 64, align: 64)
!266 = !DIDerivedType(tag: DW_TAG_typedef, name: "Bytef", file: !267, line: 276, baseType: !268)
!267 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmzlib/zconf.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!268 = !DIDerivedType(tag: DW_TAG_typedef, name: "Byte", file: !267, line: 267, baseType: !244)
!269 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in", scope: !262, file: !261, line: 84, baseType: !270, size: 32, align: 32, offset: 64)
!270 = !DIDerivedType(tag: DW_TAG_typedef, name: "uInt", file: !267, line: 269, baseType: !12)
!271 = !DIDerivedType(tag: DW_TAG_member, name: "total_in", scope: !262, file: !261, line: 85, baseType: !272, size: 64, align: 64, offset: 128)
!272 = !DIDerivedType(tag: DW_TAG_typedef, name: "uLong", file: !267, line: 270, baseType: !46)
!273 = !DIDerivedType(tag: DW_TAG_member, name: "next_out", scope: !262, file: !261, line: 87, baseType: !265, size: 64, align: 64, offset: 192)
!274 = !DIDerivedType(tag: DW_TAG_member, name: "avail_out", scope: !262, file: !261, line: 88, baseType: !270, size: 32, align: 32, offset: 256)
!275 = !DIDerivedType(tag: DW_TAG_member, name: "total_out", scope: !262, file: !261, line: 89, baseType: !272, size: 64, align: 64, offset: 320)
!276 = !DIDerivedType(tag: DW_TAG_member, name: "msg", scope: !262, file: !261, line: 91, baseType: !94, size: 64, align: 64, offset: 384)
!277 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !262, file: !261, line: 92, baseType: !278, size: 64, align: 64, offset: 448)
!278 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !279, size: 64, align: 64)
!279 = !DICompositeType(tag: DW_TAG_structure_type, name: "internal_state", file: !261, line: 1346, size: 32, align: 32, elements: !280)
!280 = !{!281}
!281 = !DIDerivedType(tag: DW_TAG_member, name: "dummy", scope: !279, file: !261, line: 1346, baseType: !22, size: 32, align: 32)
!282 = !DIDerivedType(tag: DW_TAG_member, name: "zalloc", scope: !262, file: !261, line: 94, baseType: !283, size: 64, align: 64, offset: 512)
!283 = !DIDerivedType(tag: DW_TAG_typedef, name: "alloc_func", file: !261, line: 77, baseType: !284)
!284 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !285, size: 64, align: 64)
!285 = !DISubroutineType(types: !286)
!286 = !{!287, !287, !270, !270}
!287 = !DIDerivedType(tag: DW_TAG_typedef, name: "voidpf", file: !267, line: 285, baseType: !163)
!288 = !DIDerivedType(tag: DW_TAG_member, name: "zfree", scope: !262, file: !261, line: 95, baseType: !289, size: 64, align: 64, offset: 576)
!289 = !DIDerivedType(tag: DW_TAG_typedef, name: "free_func", file: !261, line: 78, baseType: !290)
!290 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !291, size: 64, align: 64)
!291 = !DISubroutineType(types: !292)
!292 = !{null, !287, !287}
!293 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !262, file: !261, line: 96, baseType: !287, size: 64, align: 64, offset: 640)
!294 = !DIDerivedType(tag: DW_TAG_member, name: "data_type", scope: !262, file: !261, line: 98, baseType: !22, size: 32, align: 32, offset: 704)
!295 = !DIDerivedType(tag: DW_TAG_member, name: "adler", scope: !262, file: !261, line: 99, baseType: !272, size: 64, align: 64, offset: 768)
!296 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !262, file: !261, line: 100, baseType: !272, size: 64, align: 64, offset: 832)
!297 = !DIDerivedType(tag: DW_TAG_member, name: "stream_valid", scope: !5, file: !1, line: 302, baseType: !22, size: 32, align: 32, offset: 6272)
!298 = !DIDerivedType(tag: DW_TAG_member, name: "decmpfs_compression_level", scope: !5, file: !1, line: 303, baseType: !22, size: 32, align: 32, offset: 6304)
!299 = !DIDerivedType(tag: DW_TAG_typedef, name: "dev_t", file: !38, line: 60, baseType: !193)
!300 = !DIDerivedType(tag: DW_TAG_typedef, name: "ino_t", file: !38, line: 48, baseType: !195)
!301 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !52, line: 55, baseType: !46)
!302 = !DIDerivedType(tag: DW_TAG_typedef, name: "intmax_t", file: !52, line: 134, baseType: !41)
!303 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintmax_t", file: !52, line: 135, baseType: !46)
!304 = !{!305, !306, !309, !312, !313, !317, !318, !321, !324, !325, !328, !331, !334, !337, !340, !341, !342, !343, !346, !351, !354, !355, !356, !359, !362, !365, !366, !367, !368, !369, !372, !373, !374, !375, !378, !379, !382, !383, !384, !385, !386, !389, !390}
!305 = distinct !DISubprogram(name: "archive_write_disk_set_options", scope: !1, file: !1, line: 460, type: !73, isLocal: false, isDefinition: true, scopeLine: 461, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!306 = distinct !DISubprogram(name: "archive_write_disk_set_skip_file", scope: !1, file: !1, line: 780, type: !307, isLocal: false, isDefinition: true, scopeLine: 781, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!307 = !DISubroutineType(types: !308)
!308 = !{!22, !23, !51, !51}
!309 = distinct !DISubprogram(name: "archive_write_disk_set_group_lookup", scope: !1, file: !1, line: 1743, type: !310, isLocal: false, isDefinition: true, scopeLine: 1747, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!310 = !DISubroutineType(types: !311)
!311 = !{!22, !23, !163, !176, !180}
!312 = distinct !DISubprogram(name: "archive_write_disk_set_user_lookup", scope: !1, file: !1, line: 1762, type: !310, isLocal: false, isDefinition: true, scopeLine: 1766, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!313 = distinct !DISubprogram(name: "archive_write_disk_gid", scope: !1, file: !1, line: 1781, type: !314, isLocal: false, isDefinition: true, scopeLine: 1782, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!314 = !DISubroutineType(types: !315)
!315 = !{!316, !23, !79, !51}
!316 = !DIDerivedType(tag: DW_TAG_typedef, name: "la_int64_t", file: !31, line: 73, baseType: !51)
!317 = distinct !DISubprogram(name: "archive_write_disk_uid", scope: !1, file: !1, line: 1792, type: !314, isLocal: false, isDefinition: true, scopeLine: 1793, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!318 = distinct !DISubprogram(name: "archive_write_disk_new", scope: !1, file: !1, line: 1806, type: !319, isLocal: false, isDefinition: true, scopeLine: 1807, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!319 = !DISubroutineType(types: !320)
!320 = !{!23}
!321 = distinct !DISubprogram(name: "archive_write_disk_vtable", scope: !1, file: !1, line: 429, type: !322, isLocal: true, isDefinition: true, scopeLine: 430, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!322 = !DISubroutineType(types: !323)
!323 = !{!15}
!324 = distinct !DISubprogram(name: "_archive_write_disk_close", scope: !1, file: !1, line: 2270, type: !20, isLocal: true, isDefinition: true, scopeLine: 2271, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!325 = distinct !DISubprogram(name: "sort_dir_list", scope: !1, file: !1, line: 2367, type: !326, isLocal: true, isDefinition: true, scopeLine: 2368, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!326 = !DISubroutineType(types: !327)
!327 = !{!113, !113}
!328 = distinct !DISubprogram(name: "set_times", scope: !1, file: !1, line: 3217, type: !329, isLocal: true, isDefinition: true, scopeLine: 3223, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!329 = !DISubroutineType(types: !330)
!330 = !{!22, !4, !22, !22, !79, !172, !41, !172, !41, !172, !41, !172, !41}
!331 = distinct !DISubprogram(name: "set_time", scope: !1, file: !1, line: 3113, type: !332, isLocal: true, isDefinition: true, scopeLine: 3116, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!332 = !DISubroutineType(types: !333)
!333 = !{!22, !22, !22, !79, !172, !41, !172, !41}
!334 = distinct !DISubprogram(name: "set_fflags_platform", scope: !1, file: !1, line: 3602, type: !335, isLocal: true, isDefinition: true, scopeLine: 3604, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!335 = !DISubroutineType(types: !336)
!336 = !{!22, !4, !22, !79, !110, !46, !46}
!337 = distinct !DISubprogram(name: "set_mac_metadata", scope: !1, file: !1, line: 3721, type: !338, isLocal: true, isDefinition: true, scopeLine: 3723, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!338 = !DISubroutineType(types: !339)
!339 = !{!22, !4, !79, !42, !44}
!340 = distinct !DISubprogram(name: "_archive_write_disk_filter_bytes", scope: !1, file: !1, line: 449, type: !69, isLocal: true, isDefinition: true, scopeLine: 450, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!341 = distinct !DISubprogram(name: "_archive_write_disk_free", scope: !1, file: !1, line: 2321, type: !20, isLocal: true, isDefinition: true, scopeLine: 2322, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!342 = distinct !DISubprogram(name: "_archive_write_disk_header", scope: !1, file: !1, line: 481, type: !27, isLocal: true, isDefinition: true, scopeLine: 482, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!343 = distinct !DISubprogram(name: "cleanup_pathname", scope: !1, file: !1, line: 2910, type: !344, isLocal: true, isDefinition: true, scopeLine: 2911, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!344 = !DISubroutineType(types: !345)
!345 = !{!22, !4}
!346 = distinct !DISubprogram(name: "cleanup_pathname_fsobj", scope: !1, file: !1, line: 2812, type: !347, isLocal: true, isDefinition: true, scopeLine: 2814, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!347 = !DISubroutineType(types: !348)
!348 = !{!22, !94, !349, !350, !22}
!349 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !22, size: 64, align: 64)
!350 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !90, size: 64, align: 64)
!351 = distinct !DISubprogram(name: "fsobj_error", scope: !1, file: !1, line: 2464, type: !352, isLocal: true, isDefinition: true, scopeLine: 2466, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!352 = !DISubroutineType(types: !353)
!353 = !{null, !349, !350, !22, !79, !79}
!354 = distinct !DISubprogram(name: "check_symlinks", scope: !1, file: !1, line: 2721, type: !344, isLocal: true, isDefinition: true, scopeLine: 2722, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!355 = distinct !DISubprogram(name: "check_symlinks_fsobj", scope: !1, file: !1, line: 2485, type: !347, isLocal: true, isDefinition: true, scopeLine: 2487, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!356 = distinct !DISubprogram(name: "edit_deep_directories", scope: !1, file: !1, line: 1844, type: !357, isLocal: true, isDefinition: true, scopeLine: 1845, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!357 = !DISubroutineType(types: !358)
!358 = !{null, !4}
!359 = distinct !DISubprogram(name: "create_dir", scope: !1, file: !1, line: 2954, type: !360, isLocal: true, isDefinition: true, scopeLine: 2955, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!360 = !DISubroutineType(types: !361)
!361 = !{!22, !4, !94}
!362 = distinct !DISubprogram(name: "new_fixup", scope: !1, file: !1, line: 2434, type: !363, isLocal: true, isDefinition: true, scopeLine: 2435, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!363 = !DISubroutineType(types: !364)
!364 = !{!113, !4, !79}
!365 = distinct !DISubprogram(name: "restore_entry", scope: !1, file: !1, line: 1888, type: !344, isLocal: true, isDefinition: true, scopeLine: 1889, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!366 = distinct !DISubprogram(name: "clear_nochange_fflags", scope: !1, file: !1, line: 3511, type: !344, isLocal: true, isDefinition: true, scopeLine: 3512, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!367 = distinct !DISubprogram(name: "create_filesystem_object", scope: !1, file: !1, line: 2063, type: !344, isLocal: true, isDefinition: true, scopeLine: 2064, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!368 = distinct !DISubprogram(name: "create_parent_dir", scope: !1, file: !1, line: 2931, type: !360, isLocal: true, isDefinition: true, scopeLine: 2932, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!369 = distinct !DISubprogram(name: "older", scope: !1, file: !1, line: 4205, type: !370, isLocal: true, isDefinition: true, scopeLine: 4206, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!370 = !DISubroutineType(types: !371)
!371 = !{!22, !224, !29}
!372 = distinct !DISubprogram(name: "current_fixup", scope: !1, file: !1, line: 2455, type: !363, isLocal: true, isDefinition: true, scopeLine: 2456, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!373 = distinct !DISubprogram(name: "_archive_write_disk_finish_entry", scope: !1, file: !1, line: 1531, type: !20, isLocal: true, isDefinition: true, scopeLine: 1532, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!374 = distinct !DISubprogram(name: "lazy_stat", scope: !1, file: !1, line: 404, type: !344, isLocal: true, isDefinition: true, scopeLine: 405, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!375 = distinct !DISubprogram(name: "fixup_appledouble", scope: !1, file: !1, line: 3732, type: !376, isLocal: true, isDefinition: true, scopeLine: 3733, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!376 = !DISubroutineType(types: !377)
!377 = !{!22, !4, !79}
!378 = distinct !DISubprogram(name: "set_ownership", scope: !1, file: !1, line: 3064, type: !344, isLocal: true, isDefinition: true, scopeLine: 3065, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!379 = distinct !DISubprogram(name: "set_mode", scope: !1, file: !1, line: 3317, type: !380, isLocal: true, isDefinition: true, scopeLine: 3318, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!380 = !DISubroutineType(types: !381)
!381 = !{!22, !4, !22}
!382 = distinct !DISubprogram(name: "set_xattrs", scope: !1, file: !1, line: 4184, type: !344, isLocal: true, isDefinition: true, scopeLine: 4185, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!383 = distinct !DISubprogram(name: "set_fflags", scope: !1, file: !1, line: 3433, type: !344, isLocal: true, isDefinition: true, scopeLine: 3434, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!384 = distinct !DISubprogram(name: "set_times_from_entry", scope: !1, file: !1, line: 3275, type: !344, isLocal: true, isDefinition: true, scopeLine: 3276, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!385 = distinct !DISubprogram(name: "_archive_write_disk_data", scope: !1, file: !1, line: 1518, type: !35, isLocal: true, isDefinition: true, scopeLine: 1519, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!386 = distinct !DISubprogram(name: "hfs_write_data_block", scope: !1, file: !1, line: 1480, type: !387, isLocal: true, isDefinition: true, scopeLine: 1482, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!387 = !DISubroutineType(types: !388)
!388 = !{!37, !4, !79, !44}
!389 = distinct !DISubprogram(name: "write_data_block", scope: !1, file: !1, line: 792, type: !387, isLocal: true, isDefinition: true, scopeLine: 793, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!390 = distinct !DISubprogram(name: "_archive_write_disk_data_block", scope: !1, file: !1, line: 1488, type: !49, isLocal: true, isDefinition: true, scopeLine: 1490, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!391 = !{!392, !393, !394}
!392 = !DIGlobalVariable(name: "av", scope: !321, file: !1, line: 431, type: !16, isLocal: true, isDefinition: true, variable: %struct.archive_vtable* @archive_write_disk_vtable.av)
!393 = !DIGlobalVariable(name: "inited", scope: !321, file: !1, line: 432, type: !22, isLocal: true, isDefinition: true, variable: i32* @archive_write_disk_vtable.inited)
!394 = !DIGlobalVariable(name: "warning_done", scope: !382, file: !1, line: 4186, type: !22, isLocal: true, isDefinition: true, variable: i32* @set_xattrs.warning_done)
!395 = !{i32 2, !"Dwarf Version", i32 4}
!396 = !{i32 2, !"Debug Info Version", i32 3}
!397 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!398 = !DILocalVariable(name: "_a", arg: 1, scope: !305, file: !1, line: 460, type: !23)
!399 = !DIExpression()
!400 = !DILocation(line: 460, column: 48, scope: !305)
!401 = !DILocalVariable(name: "flags", arg: 2, scope: !305, file: !1, line: 460, type: !22)
!402 = !DILocation(line: 460, column: 56, scope: !305)
!403 = !DILocalVariable(name: "a", scope: !305, file: !1, line: 462, type: !4)
!404 = !DILocation(line: 462, column: 29, scope: !305)
!405 = !DILocation(line: 462, column: 62, scope: !305)
!406 = !DILocation(line: 462, column: 33, scope: !305)
!407 = !DILocation(line: 464, column: 13, scope: !305)
!408 = !DILocation(line: 464, column: 2, scope: !305)
!409 = !DILocation(line: 464, column: 5, scope: !305)
!410 = !DILocation(line: 464, column: 11, scope: !305)
!411 = !DILocation(line: 465, column: 2, scope: !305)
!412 = !DILocalVariable(name: "_a", arg: 1, scope: !306, file: !1, line: 780, type: !23)
!413 = !DILocation(line: 780, column: 50, scope: !306)
!414 = !DILocalVariable(name: "d", arg: 2, scope: !306, file: !1, line: 780, type: !51)
!415 = !DILocation(line: 780, column: 62, scope: !306)
!416 = !DILocalVariable(name: "i", arg: 3, scope: !306, file: !1, line: 780, type: !51)
!417 = !DILocation(line: 780, column: 73, scope: !306)
!418 = !DILocalVariable(name: "a", scope: !306, file: !1, line: 782, type: !4)
!419 = !DILocation(line: 782, column: 29, scope: !306)
!420 = !DILocation(line: 782, column: 62, scope: !306)
!421 = !DILocation(line: 782, column: 33, scope: !306)
!422 = !DILocation(line: 783, column: 2, scope: !306)
!423 = !DILocalVariable(name: "magic_test", scope: !424, file: !1, line: 783, type: !22)
!424 = distinct !DILexicalBlock(scope: !306, file: !1, line: 783, column: 2)
!425 = !DILocation(line: 783, column: 2, scope: !424)
!426 = !DILocation(line: 783, column: 2, scope: !427)
!427 = !DILexicalBlockFile(scope: !424, file: !1, discriminator: 1)
!428 = !DILocation(line: 783, column: 2, scope: !429)
!429 = !DILexicalBlockFile(scope: !430, file: !1, discriminator: 2)
!430 = distinct !DILexicalBlock(scope: !424, file: !1, line: 783, column: 2)
!431 = !DILocation(line: 783, column: 2, scope: !432)
!432 = !DILexicalBlockFile(scope: !424, file: !1, discriminator: 3)
!433 = !DILocation(line: 785, column: 2, scope: !306)
!434 = !DILocation(line: 785, column: 5, scope: !306)
!435 = !DILocation(line: 785, column: 19, scope: !306)
!436 = !DILocation(line: 786, column: 21, scope: !306)
!437 = !DILocation(line: 786, column: 2, scope: !306)
!438 = !DILocation(line: 786, column: 5, scope: !306)
!439 = !DILocation(line: 786, column: 19, scope: !306)
!440 = !DILocation(line: 787, column: 21, scope: !306)
!441 = !DILocation(line: 787, column: 2, scope: !306)
!442 = !DILocation(line: 787, column: 5, scope: !306)
!443 = !DILocation(line: 787, column: 19, scope: !306)
!444 = !DILocation(line: 788, column: 2, scope: !306)
!445 = !DILocation(line: 789, column: 1, scope: !306)
!446 = !DILocalVariable(name: "_a", arg: 1, scope: !309, file: !1, line: 1743, type: !23)
!447 = !DILocation(line: 1743, column: 53, scope: !309)
!448 = !DILocalVariable(name: "private_data", arg: 2, scope: !309, file: !1, line: 1744, type: !163)
!449 = !DILocation(line: 1744, column: 11, scope: !309)
!450 = !DILocalVariable(name: "lookup_gid", arg: 3, scope: !309, file: !1, line: 1745, type: !176)
!451 = !DILocation(line: 1745, column: 15, scope: !309)
!452 = !DILocalVariable(name: "cleanup_gid", arg: 4, scope: !309, file: !1, line: 1746, type: !180)
!453 = !DILocation(line: 1746, column: 12, scope: !309)
!454 = !DILocalVariable(name: "a", scope: !309, file: !1, line: 1748, type: !4)
!455 = !DILocation(line: 1748, column: 29, scope: !309)
!456 = !DILocation(line: 1748, column: 62, scope: !309)
!457 = !DILocation(line: 1748, column: 33, scope: !309)
!458 = !DILocation(line: 1749, column: 2, scope: !309)
!459 = !DILocalVariable(name: "magic_test", scope: !460, file: !1, line: 1749, type: !22)
!460 = distinct !DILexicalBlock(scope: !309, file: !1, line: 1749, column: 2)
!461 = !DILocation(line: 1749, column: 2, scope: !460)
!462 = !DILocation(line: 1749, column: 2, scope: !463)
!463 = !DILexicalBlockFile(scope: !460, file: !1, discriminator: 1)
!464 = !DILocation(line: 1749, column: 2, scope: !465)
!465 = !DILexicalBlockFile(scope: !466, file: !1, discriminator: 2)
!466 = distinct !DILexicalBlock(scope: !460, file: !1, line: 1749, column: 2)
!467 = !DILocation(line: 1749, column: 2, scope: !468)
!468 = !DILexicalBlockFile(scope: !460, file: !1, discriminator: 3)
!469 = !DILocation(line: 1752, column: 6, scope: !470)
!470 = distinct !DILexicalBlock(scope: !309, file: !1, line: 1752, column: 6)
!471 = !DILocation(line: 1752, column: 9, scope: !470)
!472 = !DILocation(line: 1752, column: 21, scope: !470)
!473 = !DILocation(line: 1752, column: 29, scope: !470)
!474 = !DILocation(line: 1752, column: 32, scope: !475)
!475 = !DILexicalBlockFile(scope: !470, file: !1, discriminator: 1)
!476 = !DILocation(line: 1752, column: 35, scope: !475)
!477 = !DILocation(line: 1752, column: 51, scope: !475)
!478 = !DILocation(line: 1752, column: 6, scope: !475)
!479 = !DILocation(line: 1753, column: 4, scope: !470)
!480 = !DILocation(line: 1753, column: 7, scope: !470)
!481 = !DILocation(line: 1753, column: 20, scope: !470)
!482 = !DILocation(line: 1753, column: 23, scope: !470)
!483 = !DILocation(line: 1753, column: 3, scope: !470)
!484 = !DILocation(line: 1755, column: 18, scope: !309)
!485 = !DILocation(line: 1755, column: 2, scope: !309)
!486 = !DILocation(line: 1755, column: 5, scope: !309)
!487 = !DILocation(line: 1755, column: 16, scope: !309)
!488 = !DILocation(line: 1756, column: 19, scope: !309)
!489 = !DILocation(line: 1756, column: 2, scope: !309)
!490 = !DILocation(line: 1756, column: 5, scope: !309)
!491 = !DILocation(line: 1756, column: 17, scope: !309)
!492 = !DILocation(line: 1757, column: 23, scope: !309)
!493 = !DILocation(line: 1757, column: 2, scope: !309)
!494 = !DILocation(line: 1757, column: 5, scope: !309)
!495 = !DILocation(line: 1757, column: 21, scope: !309)
!496 = !DILocation(line: 1758, column: 2, scope: !309)
!497 = !DILocation(line: 1759, column: 1, scope: !309)
!498 = !DILocalVariable(name: "_a", arg: 1, scope: !312, file: !1, line: 1762, type: !23)
!499 = !DILocation(line: 1762, column: 52, scope: !312)
!500 = !DILocalVariable(name: "private_data", arg: 2, scope: !312, file: !1, line: 1763, type: !163)
!501 = !DILocation(line: 1763, column: 11, scope: !312)
!502 = !DILocalVariable(name: "lookup_uid", arg: 3, scope: !312, file: !1, line: 1764, type: !176)
!503 = !DILocation(line: 1764, column: 15, scope: !312)
!504 = !DILocalVariable(name: "cleanup_uid", arg: 4, scope: !312, file: !1, line: 1765, type: !180)
!505 = !DILocation(line: 1765, column: 12, scope: !312)
!506 = !DILocalVariable(name: "a", scope: !312, file: !1, line: 1767, type: !4)
!507 = !DILocation(line: 1767, column: 29, scope: !312)
!508 = !DILocation(line: 1767, column: 62, scope: !312)
!509 = !DILocation(line: 1767, column: 33, scope: !312)
!510 = !DILocation(line: 1768, column: 2, scope: !312)
!511 = !DILocalVariable(name: "magic_test", scope: !512, file: !1, line: 1768, type: !22)
!512 = distinct !DILexicalBlock(scope: !312, file: !1, line: 1768, column: 2)
!513 = !DILocation(line: 1768, column: 2, scope: !512)
!514 = !DILocation(line: 1768, column: 2, scope: !515)
!515 = !DILexicalBlockFile(scope: !512, file: !1, discriminator: 1)
!516 = !DILocation(line: 1768, column: 2, scope: !517)
!517 = !DILexicalBlockFile(scope: !518, file: !1, discriminator: 2)
!518 = distinct !DILexicalBlock(scope: !512, file: !1, line: 1768, column: 2)
!519 = !DILocation(line: 1768, column: 2, scope: !520)
!520 = !DILexicalBlockFile(scope: !512, file: !1, discriminator: 3)
!521 = !DILocation(line: 1771, column: 6, scope: !522)
!522 = distinct !DILexicalBlock(scope: !312, file: !1, line: 1771, column: 6)
!523 = !DILocation(line: 1771, column: 9, scope: !522)
!524 = !DILocation(line: 1771, column: 21, scope: !522)
!525 = !DILocation(line: 1771, column: 29, scope: !522)
!526 = !DILocation(line: 1771, column: 32, scope: !527)
!527 = !DILexicalBlockFile(scope: !522, file: !1, discriminator: 1)
!528 = !DILocation(line: 1771, column: 35, scope: !527)
!529 = !DILocation(line: 1771, column: 51, scope: !527)
!530 = !DILocation(line: 1771, column: 6, scope: !527)
!531 = !DILocation(line: 1772, column: 4, scope: !522)
!532 = !DILocation(line: 1772, column: 7, scope: !522)
!533 = !DILocation(line: 1772, column: 20, scope: !522)
!534 = !DILocation(line: 1772, column: 23, scope: !522)
!535 = !DILocation(line: 1772, column: 3, scope: !522)
!536 = !DILocation(line: 1774, column: 18, scope: !312)
!537 = !DILocation(line: 1774, column: 2, scope: !312)
!538 = !DILocation(line: 1774, column: 5, scope: !312)
!539 = !DILocation(line: 1774, column: 16, scope: !312)
!540 = !DILocation(line: 1775, column: 19, scope: !312)
!541 = !DILocation(line: 1775, column: 2, scope: !312)
!542 = !DILocation(line: 1775, column: 5, scope: !312)
!543 = !DILocation(line: 1775, column: 17, scope: !312)
!544 = !DILocation(line: 1776, column: 23, scope: !312)
!545 = !DILocation(line: 1776, column: 2, scope: !312)
!546 = !DILocation(line: 1776, column: 5, scope: !312)
!547 = !DILocation(line: 1776, column: 21, scope: !312)
!548 = !DILocation(line: 1777, column: 2, scope: !312)
!549 = !DILocation(line: 1778, column: 1, scope: !312)
!550 = !DILocalVariable(name: "_a", arg: 1, scope: !313, file: !1, line: 1781, type: !23)
!551 = !DILocation(line: 1781, column: 40, scope: !313)
!552 = !DILocalVariable(name: "name", arg: 2, scope: !313, file: !1, line: 1781, type: !79)
!553 = !DILocation(line: 1781, column: 56, scope: !313)
!554 = !DILocalVariable(name: "id", arg: 3, scope: !313, file: !1, line: 1781, type: !51)
!555 = !DILocation(line: 1781, column: 70, scope: !313)
!556 = !DILocalVariable(name: "a", scope: !313, file: !1, line: 1783, type: !4)
!557 = !DILocation(line: 1783, column: 35, scope: !313)
!558 = !DILocation(line: 1783, column: 68, scope: !313)
!559 = !DILocation(line: 1783, column: 39, scope: !313)
!560 = !DILocation(line: 1784, column: 8, scope: !313)
!561 = !DILocalVariable(name: "magic_test", scope: !562, file: !1, line: 1784, type: !22)
!562 = distinct !DILexicalBlock(scope: !313, file: !1, line: 1784, column: 8)
!563 = !DILocation(line: 1784, column: 8, scope: !562)
!564 = !DILocation(line: 1784, column: 8, scope: !565)
!565 = !DILexicalBlockFile(scope: !562, file: !1, discriminator: 1)
!566 = !DILocation(line: 1784, column: 8, scope: !567)
!567 = !DILexicalBlockFile(scope: !568, file: !1, discriminator: 2)
!568 = distinct !DILexicalBlock(scope: !562, file: !1, line: 1784, column: 8)
!569 = !DILocation(line: 1784, column: 8, scope: !570)
!570 = !DILexicalBlockFile(scope: !562, file: !1, discriminator: 3)
!571 = !DILocation(line: 1786, column: 12, scope: !572)
!572 = distinct !DILexicalBlock(scope: !313, file: !1, line: 1786, column: 12)
!573 = !DILocation(line: 1786, column: 15, scope: !572)
!574 = !DILocation(line: 1786, column: 12, scope: !313)
!575 = !DILocation(line: 1787, column: 24, scope: !572)
!576 = !DILocation(line: 1787, column: 27, scope: !572)
!577 = !DILocation(line: 1787, column: 39, scope: !572)
!578 = !DILocation(line: 1787, column: 42, scope: !572)
!579 = !DILocation(line: 1787, column: 59, scope: !572)
!580 = !DILocation(line: 1787, column: 65, scope: !572)
!581 = !DILocation(line: 1787, column: 23, scope: !572)
!582 = !DILocation(line: 1787, column: 16, scope: !572)
!583 = !DILocation(line: 1788, column: 16, scope: !313)
!584 = !DILocation(line: 1788, column: 8, scope: !313)
!585 = !DILocation(line: 1789, column: 1, scope: !313)
!586 = !DILocalVariable(name: "_a", arg: 1, scope: !317, file: !1, line: 1792, type: !23)
!587 = !DILocation(line: 1792, column: 40, scope: !317)
!588 = !DILocalVariable(name: "name", arg: 2, scope: !317, file: !1, line: 1792, type: !79)
!589 = !DILocation(line: 1792, column: 56, scope: !317)
!590 = !DILocalVariable(name: "id", arg: 3, scope: !317, file: !1, line: 1792, type: !51)
!591 = !DILocation(line: 1792, column: 70, scope: !317)
!592 = !DILocalVariable(name: "a", scope: !317, file: !1, line: 1794, type: !4)
!593 = !DILocation(line: 1794, column: 29, scope: !317)
!594 = !DILocation(line: 1794, column: 62, scope: !317)
!595 = !DILocation(line: 1794, column: 33, scope: !317)
!596 = !DILocation(line: 1795, column: 2, scope: !317)
!597 = !DILocalVariable(name: "magic_test", scope: !598, file: !1, line: 1795, type: !22)
!598 = distinct !DILexicalBlock(scope: !317, file: !1, line: 1795, column: 2)
!599 = !DILocation(line: 1795, column: 2, scope: !598)
!600 = !DILocation(line: 1795, column: 2, scope: !601)
!601 = !DILexicalBlockFile(scope: !598, file: !1, discriminator: 1)
!602 = !DILocation(line: 1795, column: 2, scope: !603)
!603 = !DILexicalBlockFile(scope: !604, file: !1, discriminator: 2)
!604 = distinct !DILexicalBlock(scope: !598, file: !1, line: 1795, column: 2)
!605 = !DILocation(line: 1795, column: 2, scope: !606)
!606 = !DILexicalBlockFile(scope: !598, file: !1, discriminator: 3)
!607 = !DILocation(line: 1797, column: 6, scope: !608)
!608 = distinct !DILexicalBlock(scope: !317, file: !1, line: 1797, column: 6)
!609 = !DILocation(line: 1797, column: 9, scope: !608)
!610 = !DILocation(line: 1797, column: 6, scope: !317)
!611 = !DILocation(line: 1798, column: 11, scope: !608)
!612 = !DILocation(line: 1798, column: 14, scope: !608)
!613 = !DILocation(line: 1798, column: 26, scope: !608)
!614 = !DILocation(line: 1798, column: 29, scope: !608)
!615 = !DILocation(line: 1798, column: 46, scope: !608)
!616 = !DILocation(line: 1798, column: 52, scope: !608)
!617 = !DILocation(line: 1798, column: 10, scope: !608)
!618 = !DILocation(line: 1798, column: 3, scope: !608)
!619 = !DILocation(line: 1799, column: 10, scope: !317)
!620 = !DILocation(line: 1799, column: 2, scope: !317)
!621 = !DILocation(line: 1800, column: 1, scope: !317)
!622 = !DILocalVariable(name: "a", scope: !318, file: !1, line: 1808, type: !4)
!623 = !DILocation(line: 1808, column: 29, scope: !318)
!624 = !DILocation(line: 1810, column: 35, scope: !318)
!625 = !DILocation(line: 1810, column: 6, scope: !318)
!626 = !DILocation(line: 1810, column: 4, scope: !318)
!627 = !DILocation(line: 1811, column: 6, scope: !628)
!628 = distinct !DILexicalBlock(scope: !318, file: !1, line: 1811, column: 6)
!629 = !DILocation(line: 1811, column: 8, scope: !628)
!630 = !DILocation(line: 1811, column: 6, scope: !318)
!631 = !DILocation(line: 1812, column: 3, scope: !628)
!632 = !DILocation(line: 1813, column: 2, scope: !318)
!633 = !DILocation(line: 1813, column: 5, scope: !318)
!634 = !DILocation(line: 1813, column: 13, scope: !318)
!635 = !DILocation(line: 1813, column: 19, scope: !318)
!636 = !DILocation(line: 1815, column: 2, scope: !318)
!637 = !DILocation(line: 1815, column: 5, scope: !318)
!638 = !DILocation(line: 1815, column: 13, scope: !318)
!639 = !DILocation(line: 1815, column: 19, scope: !318)
!640 = !DILocation(line: 1816, column: 22, scope: !318)
!641 = !DILocation(line: 1816, column: 2, scope: !318)
!642 = !DILocation(line: 1816, column: 5, scope: !318)
!643 = !DILocation(line: 1816, column: 13, scope: !318)
!644 = !DILocation(line: 1816, column: 20, scope: !318)
!645 = !DILocation(line: 1817, column: 18, scope: !318)
!646 = !DILocation(line: 1817, column: 2, scope: !318)
!647 = !DILocation(line: 1817, column: 5, scope: !318)
!648 = !DILocation(line: 1817, column: 16, scope: !318)
!649 = !DILocation(line: 1819, column: 24, scope: !318)
!650 = !DILocation(line: 1819, column: 8, scope: !318)
!651 = !DILocation(line: 1819, column: 11, scope: !318)
!652 = !DILocation(line: 1819, column: 22, scope: !318)
!653 = !DILocation(line: 1819, column: 2, scope: !654)
!654 = !DILexicalBlockFile(scope: !318, file: !1, discriminator: 1)
!655 = !DILocation(line: 1821, column: 16, scope: !318)
!656 = !DILocation(line: 1821, column: 2, scope: !318)
!657 = !DILocation(line: 1821, column: 5, scope: !318)
!658 = !DILocation(line: 1821, column: 14, scope: !318)
!659 = !DILocation(line: 1823, column: 29, scope: !660)
!660 = distinct !DILexicalBlock(scope: !318, file: !1, line: 1823, column: 6)
!661 = !DILocation(line: 1823, column: 32, scope: !660)
!662 = !DILocation(line: 1823, column: 6, scope: !660)
!663 = !DILocation(line: 1823, column: 48, scope: !660)
!664 = !DILocation(line: 1823, column: 6, scope: !318)
!665 = !DILocation(line: 1824, column: 8, scope: !666)
!666 = distinct !DILexicalBlock(scope: !660, file: !1, line: 1823, column: 57)
!667 = !DILocation(line: 1824, column: 3, scope: !666)
!668 = !DILocation(line: 1825, column: 3, scope: !666)
!669 = !DILocation(line: 1828, column: 2, scope: !318)
!670 = !DILocation(line: 1828, column: 5, scope: !318)
!671 = !DILocation(line: 1828, column: 31, scope: !318)
!672 = !DILocation(line: 1830, column: 11, scope: !318)
!673 = !DILocation(line: 1830, column: 14, scope: !318)
!674 = !DILocation(line: 1830, column: 2, scope: !318)
!675 = !DILocation(line: 1831, column: 1, scope: !318)
!676 = !DILocation(line: 434, column: 7, scope: !677)
!677 = distinct !DILexicalBlock(scope: !321, file: !1, line: 434, column: 6)
!678 = !DILocation(line: 434, column: 6, scope: !321)
!679 = !DILocation(line: 435, column: 20, scope: !680)
!680 = distinct !DILexicalBlock(scope: !677, file: !1, line: 434, column: 15)
!681 = !DILocation(line: 436, column: 27, scope: !680)
!682 = !DILocation(line: 437, column: 19, scope: !680)
!683 = !DILocation(line: 438, column: 27, scope: !680)
!684 = !DILocation(line: 440, column: 7, scope: !680)
!685 = !DILocation(line: 441, column: 25, scope: !680)
!686 = !DILocation(line: 442, column: 31, scope: !680)
!687 = !DILocation(line: 443, column: 10, scope: !680)
!688 = !DILocation(line: 444, column: 2, scope: !680)
!689 = !DILocation(line: 445, column: 2, scope: !321)
!690 = !DILocalVariable(name: "_a", arg: 1, scope: !324, file: !1, line: 2270, type: !23)
!691 = !DILocation(line: 2270, column: 43, scope: !324)
!692 = !DILocalVariable(name: "a", scope: !324, file: !1, line: 2272, type: !4)
!693 = !DILocation(line: 2272, column: 29, scope: !324)
!694 = !DILocation(line: 2272, column: 62, scope: !324)
!695 = !DILocation(line: 2272, column: 33, scope: !324)
!696 = !DILocalVariable(name: "next", scope: !324, file: !1, line: 2273, type: !113)
!697 = !DILocation(line: 2273, column: 22, scope: !324)
!698 = !DILocalVariable(name: "p", scope: !324, file: !1, line: 2273, type: !113)
!699 = !DILocation(line: 2273, column: 29, scope: !324)
!700 = !DILocalVariable(name: "ret", scope: !324, file: !1, line: 2274, type: !22)
!701 = !DILocation(line: 2274, column: 6, scope: !324)
!702 = !DILocation(line: 2276, column: 2, scope: !324)
!703 = !DILocalVariable(name: "magic_test", scope: !704, file: !1, line: 2276, type: !22)
!704 = distinct !DILexicalBlock(scope: !324, file: !1, line: 2276, column: 2)
!705 = !DILocation(line: 2276, column: 2, scope: !704)
!706 = !DILocation(line: 2276, column: 2, scope: !707)
!707 = !DILexicalBlockFile(scope: !704, file: !1, discriminator: 1)
!708 = !DILocation(line: 2276, column: 2, scope: !709)
!709 = !DILexicalBlockFile(scope: !710, file: !1, discriminator: 2)
!710 = distinct !DILexicalBlock(scope: !704, file: !1, line: 2276, column: 2)
!711 = !DILocation(line: 2276, column: 2, scope: !712)
!712 = !DILexicalBlockFile(scope: !704, file: !1, discriminator: 3)
!713 = !DILocation(line: 2279, column: 42, scope: !324)
!714 = !DILocation(line: 2279, column: 45, scope: !324)
!715 = !DILocation(line: 2279, column: 8, scope: !324)
!716 = !DILocation(line: 2279, column: 6, scope: !324)
!717 = !DILocation(line: 2282, column: 20, scope: !324)
!718 = !DILocation(line: 2282, column: 23, scope: !324)
!719 = !DILocation(line: 2282, column: 6, scope: !324)
!720 = !DILocation(line: 2282, column: 4, scope: !324)
!721 = !DILocation(line: 2284, column: 2, scope: !324)
!722 = !DILocation(line: 2284, column: 9, scope: !723)
!723 = !DILexicalBlockFile(scope: !324, file: !1, discriminator: 1)
!724 = !DILocation(line: 2284, column: 11, scope: !723)
!725 = !DILocation(line: 2284, column: 2, scope: !723)
!726 = !DILocation(line: 2285, column: 3, scope: !727)
!727 = distinct !DILexicalBlock(scope: !324, file: !1, line: 2284, column: 20)
!728 = !DILocation(line: 2285, column: 6, scope: !727)
!729 = !DILocation(line: 2285, column: 10, scope: !727)
!730 = !DILocation(line: 2286, column: 7, scope: !731)
!731 = distinct !DILexicalBlock(scope: !727, file: !1, line: 2286, column: 7)
!732 = !DILocation(line: 2286, column: 10, scope: !731)
!733 = !DILocation(line: 2286, column: 16, scope: !731)
!734 = !DILocation(line: 2286, column: 7, scope: !727)
!735 = !DILocation(line: 2287, column: 14, scope: !736)
!736 = distinct !DILexicalBlock(scope: !731, file: !1, line: 2286, column: 30)
!737 = !DILocation(line: 2287, column: 21, scope: !736)
!738 = !DILocation(line: 2287, column: 24, scope: !736)
!739 = !DILocation(line: 2287, column: 30, scope: !736)
!740 = !DILocation(line: 2287, column: 33, scope: !736)
!741 = !DILocation(line: 2288, column: 8, scope: !736)
!742 = !DILocation(line: 2288, column: 11, scope: !736)
!743 = !DILocation(line: 2288, column: 18, scope: !736)
!744 = !DILocation(line: 2288, column: 21, scope: !736)
!745 = !DILocation(line: 2289, column: 8, scope: !736)
!746 = !DILocation(line: 2289, column: 11, scope: !736)
!747 = !DILocation(line: 2289, column: 22, scope: !736)
!748 = !DILocation(line: 2289, column: 25, scope: !736)
!749 = !DILocation(line: 2290, column: 8, scope: !736)
!750 = !DILocation(line: 2290, column: 11, scope: !736)
!751 = !DILocation(line: 2290, column: 18, scope: !736)
!752 = !DILocation(line: 2290, column: 21, scope: !736)
!753 = !DILocation(line: 2291, column: 8, scope: !736)
!754 = !DILocation(line: 2291, column: 11, scope: !736)
!755 = !DILocation(line: 2291, column: 18, scope: !736)
!756 = !DILocation(line: 2291, column: 21, scope: !736)
!757 = !DILocation(line: 2287, column: 4, scope: !736)
!758 = !DILocation(line: 2292, column: 3, scope: !736)
!759 = !DILocation(line: 2293, column: 7, scope: !760)
!760 = distinct !DILexicalBlock(scope: !727, file: !1, line: 2293, column: 7)
!761 = !DILocation(line: 2293, column: 10, scope: !760)
!762 = !DILocation(line: 2293, column: 16, scope: !760)
!763 = !DILocation(line: 2293, column: 7, scope: !727)
!764 = !DILocation(line: 2294, column: 10, scope: !760)
!765 = !DILocation(line: 2294, column: 13, scope: !760)
!766 = !DILocation(line: 2294, column: 19, scope: !760)
!767 = !DILocation(line: 2294, column: 22, scope: !760)
!768 = !DILocation(line: 2294, column: 4, scope: !760)
!769 = !DILocation(line: 2295, column: 7, scope: !770)
!770 = distinct !DILexicalBlock(scope: !727, file: !1, line: 2295, column: 7)
!771 = !DILocation(line: 2295, column: 10, scope: !770)
!772 = !DILocation(line: 2295, column: 16, scope: !770)
!773 = !DILocation(line: 2295, column: 7, scope: !727)
!774 = !DILocation(line: 2301, column: 34, scope: !770)
!775 = !DILocation(line: 2301, column: 37, scope: !770)
!776 = !DILocation(line: 2302, column: 13, scope: !770)
!777 = !DILocation(line: 2302, column: 16, scope: !770)
!778 = !DILocation(line: 2302, column: 23, scope: !770)
!779 = !DILocation(line: 2302, column: 26, scope: !770)
!780 = !DILocation(line: 2301, column: 5, scope: !770)
!781 = !DILocation(line: 2303, column: 7, scope: !782)
!782 = distinct !DILexicalBlock(scope: !727, file: !1, line: 2303, column: 7)
!783 = !DILocation(line: 2303, column: 10, scope: !782)
!784 = !DILocation(line: 2303, column: 16, scope: !782)
!785 = !DILocation(line: 2303, column: 7, scope: !727)
!786 = !DILocation(line: 2304, column: 24, scope: !782)
!787 = !DILocation(line: 2304, column: 31, scope: !782)
!788 = !DILocation(line: 2304, column: 34, scope: !782)
!789 = !DILocation(line: 2305, column: 8, scope: !782)
!790 = !DILocation(line: 2305, column: 11, scope: !782)
!791 = !DILocation(line: 2305, column: 17, scope: !782)
!792 = !DILocation(line: 2305, column: 20, scope: !782)
!793 = !DILocation(line: 2304, column: 4, scope: !782)
!794 = !DILocation(line: 2306, column: 7, scope: !795)
!795 = distinct !DILexicalBlock(scope: !727, file: !1, line: 2306, column: 7)
!796 = !DILocation(line: 2306, column: 10, scope: !795)
!797 = !DILocation(line: 2306, column: 16, scope: !795)
!798 = !DILocation(line: 2306, column: 7, scope: !727)
!799 = !DILocation(line: 2307, column: 21, scope: !795)
!800 = !DILocation(line: 2307, column: 24, scope: !795)
!801 = !DILocation(line: 2307, column: 27, scope: !795)
!802 = !DILocation(line: 2307, column: 33, scope: !795)
!803 = !DILocation(line: 2307, column: 36, scope: !795)
!804 = !DILocation(line: 2308, column: 7, scope: !795)
!805 = !DILocation(line: 2308, column: 10, scope: !795)
!806 = !DILocation(line: 2307, column: 4, scope: !795)
!807 = !DILocation(line: 2309, column: 10, scope: !727)
!808 = !DILocation(line: 2309, column: 13, scope: !727)
!809 = !DILocation(line: 2309, column: 8, scope: !727)
!810 = !DILocation(line: 2310, column: 22, scope: !727)
!811 = !DILocation(line: 2310, column: 25, scope: !727)
!812 = !DILocation(line: 2310, column: 3, scope: !727)
!813 = !DILocation(line: 2311, column: 8, scope: !727)
!814 = !DILocation(line: 2311, column: 11, scope: !727)
!815 = !DILocation(line: 2311, column: 3, scope: !727)
!816 = !DILocation(line: 2312, column: 8, scope: !727)
!817 = !DILocation(line: 2312, column: 11, scope: !727)
!818 = !DILocation(line: 2312, column: 3, scope: !727)
!819 = !DILocation(line: 2313, column: 8, scope: !727)
!820 = !DILocation(line: 2313, column: 3, scope: !727)
!821 = !DILocation(line: 2314, column: 7, scope: !727)
!822 = !DILocation(line: 2314, column: 5, scope: !727)
!823 = !DILocation(line: 2284, column: 2, scope: !824)
!824 = !DILexicalBlockFile(scope: !324, file: !1, discriminator: 2)
!825 = !DILocation(line: 2316, column: 2, scope: !324)
!826 = !DILocation(line: 2316, column: 5, scope: !324)
!827 = !DILocation(line: 2316, column: 16, scope: !324)
!828 = !DILocation(line: 2317, column: 10, scope: !324)
!829 = !DILocation(line: 2317, column: 2, scope: !324)
!830 = !DILocation(line: 2318, column: 1, scope: !324)
!831 = !DILocalVariable(name: "_a", arg: 1, scope: !340, file: !1, line: 449, type: !23)
!832 = !DILocation(line: 449, column: 50, scope: !340)
!833 = !DILocalVariable(name: "n", arg: 2, scope: !340, file: !1, line: 449, type: !22)
!834 = !DILocation(line: 449, column: 58, scope: !340)
!835 = !DILocalVariable(name: "a", scope: !340, file: !1, line: 451, type: !4)
!836 = !DILocation(line: 451, column: 29, scope: !340)
!837 = !DILocation(line: 451, column: 62, scope: !340)
!838 = !DILocation(line: 451, column: 33, scope: !340)
!839 = !DILocation(line: 452, column: 8, scope: !340)
!840 = !DILocation(line: 453, column: 6, scope: !841)
!841 = distinct !DILexicalBlock(scope: !340, file: !1, line: 453, column: 6)
!842 = !DILocation(line: 453, column: 8, scope: !841)
!843 = !DILocation(line: 453, column: 14, scope: !841)
!844 = !DILocation(line: 453, column: 17, scope: !845)
!845 = !DILexicalBlockFile(scope: !841, file: !1, discriminator: 1)
!846 = !DILocation(line: 453, column: 19, scope: !845)
!847 = !DILocation(line: 453, column: 6, scope: !845)
!848 = !DILocation(line: 454, column: 11, scope: !841)
!849 = !DILocation(line: 454, column: 14, scope: !841)
!850 = !DILocation(line: 454, column: 3, scope: !841)
!851 = !DILocation(line: 455, column: 2, scope: !340)
!852 = !DILocation(line: 456, column: 1, scope: !340)
!853 = !DILocalVariable(name: "_a", arg: 1, scope: !341, file: !1, line: 2321, type: !23)
!854 = !DILocation(line: 2321, column: 42, scope: !341)
!855 = !DILocalVariable(name: "a", scope: !341, file: !1, line: 2323, type: !4)
!856 = !DILocation(line: 2323, column: 29, scope: !341)
!857 = !DILocalVariable(name: "ret", scope: !341, file: !1, line: 2324, type: !22)
!858 = !DILocation(line: 2324, column: 6, scope: !341)
!859 = !DILocation(line: 2325, column: 6, scope: !860)
!860 = distinct !DILexicalBlock(scope: !341, file: !1, line: 2325, column: 6)
!861 = !DILocation(line: 2325, column: 9, scope: !860)
!862 = !DILocation(line: 2325, column: 6, scope: !341)
!863 = !DILocation(line: 2326, column: 3, scope: !860)
!864 = !DILocation(line: 2327, column: 2, scope: !341)
!865 = !DILocalVariable(name: "magic_test", scope: !866, file: !1, line: 2327, type: !22)
!866 = distinct !DILexicalBlock(scope: !341, file: !1, line: 2327, column: 2)
!867 = !DILocation(line: 2327, column: 2, scope: !866)
!868 = !DILocation(line: 2327, column: 2, scope: !869)
!869 = !DILexicalBlockFile(scope: !866, file: !1, discriminator: 1)
!870 = !DILocation(line: 2327, column: 2, scope: !871)
!871 = !DILexicalBlockFile(scope: !872, file: !1, discriminator: 2)
!872 = distinct !DILexicalBlock(scope: !866, file: !1, line: 2327, column: 2)
!873 = !DILocation(line: 2327, column: 2, scope: !874)
!874 = !DILexicalBlockFile(scope: !866, file: !1, discriminator: 3)
!875 = !DILocation(line: 2329, column: 35, scope: !341)
!876 = !DILocation(line: 2329, column: 6, scope: !341)
!877 = !DILocation(line: 2329, column: 4, scope: !341)
!878 = !DILocation(line: 2330, column: 35, scope: !341)
!879 = !DILocation(line: 2330, column: 38, scope: !341)
!880 = !DILocation(line: 2330, column: 8, scope: !341)
!881 = !DILocation(line: 2330, column: 6, scope: !341)
!882 = !DILocation(line: 2331, column: 39, scope: !341)
!883 = !DILocation(line: 2331, column: 42, scope: !341)
!884 = !DILocation(line: 2331, column: 2, scope: !341)
!885 = !DILocation(line: 2332, column: 38, scope: !341)
!886 = !DILocation(line: 2332, column: 41, scope: !341)
!887 = !DILocation(line: 2332, column: 2, scope: !341)
!888 = !DILocation(line: 2333, column: 6, scope: !889)
!889 = distinct !DILexicalBlock(scope: !341, file: !1, line: 2333, column: 6)
!890 = !DILocation(line: 2333, column: 9, scope: !889)
!891 = !DILocation(line: 2333, column: 6, scope: !341)
!892 = !DILocation(line: 2334, column: 22, scope: !889)
!893 = !DILocation(line: 2334, column: 25, scope: !889)
!894 = !DILocation(line: 2334, column: 3, scope: !889)
!895 = !DILocation(line: 2335, column: 23, scope: !341)
!896 = !DILocation(line: 2335, column: 26, scope: !341)
!897 = !DILocation(line: 2335, column: 2, scope: !341)
!898 = !DILocation(line: 2336, column: 23, scope: !341)
!899 = !DILocation(line: 2336, column: 26, scope: !341)
!900 = !DILocation(line: 2336, column: 34, scope: !341)
!901 = !DILocation(line: 2336, column: 2, scope: !341)
!902 = !DILocation(line: 2337, column: 23, scope: !341)
!903 = !DILocation(line: 2337, column: 26, scope: !341)
!904 = !DILocation(line: 2337, column: 2, scope: !341)
!905 = !DILocation(line: 2338, column: 2, scope: !341)
!906 = !DILocation(line: 2338, column: 5, scope: !341)
!907 = !DILocation(line: 2338, column: 13, scope: !341)
!908 = !DILocation(line: 2338, column: 19, scope: !341)
!909 = !DILocation(line: 2339, column: 19, scope: !341)
!910 = !DILocation(line: 2339, column: 22, scope: !341)
!911 = !DILocation(line: 2339, column: 2, scope: !341)
!912 = !DILocation(line: 2340, column: 7, scope: !341)
!913 = !DILocation(line: 2340, column: 10, scope: !341)
!914 = !DILocation(line: 2340, column: 2, scope: !341)
!915 = !DILocation(line: 2341, column: 7, scope: !341)
!916 = !DILocation(line: 2341, column: 10, scope: !341)
!917 = !DILocation(line: 2341, column: 2, scope: !341)
!918 = !DILocation(line: 2342, column: 7, scope: !341)
!919 = !DILocation(line: 2342, column: 10, scope: !341)
!920 = !DILocation(line: 2342, column: 2, scope: !341)
!921 = !DILocation(line: 2343, column: 7, scope: !341)
!922 = !DILocation(line: 2343, column: 10, scope: !341)
!923 = !DILocation(line: 2343, column: 2, scope: !341)
!924 = !DILocation(line: 2358, column: 7, scope: !341)
!925 = !DILocation(line: 2358, column: 2, scope: !341)
!926 = !DILocation(line: 2359, column: 10, scope: !341)
!927 = !DILocation(line: 2359, column: 2, scope: !341)
!928 = !DILocation(line: 2360, column: 1, scope: !341)
!929 = !DILocalVariable(name: "_a", arg: 1, scope: !342, file: !1, line: 481, type: !23)
!930 = !DILocation(line: 481, column: 44, scope: !342)
!931 = !DILocalVariable(name: "entry", arg: 2, scope: !342, file: !1, line: 481, type: !29)
!932 = !DILocation(line: 481, column: 70, scope: !342)
!933 = !DILocalVariable(name: "a", scope: !342, file: !1, line: 483, type: !4)
!934 = !DILocation(line: 483, column: 29, scope: !342)
!935 = !DILocation(line: 483, column: 62, scope: !342)
!936 = !DILocation(line: 483, column: 33, scope: !342)
!937 = !DILocalVariable(name: "fe", scope: !342, file: !1, line: 484, type: !113)
!938 = !DILocation(line: 484, column: 22, scope: !342)
!939 = !DILocalVariable(name: "ret", scope: !342, file: !1, line: 485, type: !22)
!940 = !DILocation(line: 485, column: 6, scope: !342)
!941 = !DILocalVariable(name: "r", scope: !342, file: !1, line: 485, type: !22)
!942 = !DILocation(line: 485, column: 11, scope: !342)
!943 = !DILocation(line: 487, column: 2, scope: !342)
!944 = !DILocalVariable(name: "magic_test", scope: !945, file: !1, line: 487, type: !22)
!945 = distinct !DILexicalBlock(scope: !342, file: !1, line: 487, column: 2)
!946 = !DILocation(line: 487, column: 2, scope: !945)
!947 = !DILocation(line: 487, column: 2, scope: !948)
!948 = !DILexicalBlockFile(scope: !945, file: !1, discriminator: 1)
!949 = !DILocation(line: 487, column: 2, scope: !950)
!950 = !DILexicalBlockFile(scope: !951, file: !1, discriminator: 2)
!951 = distinct !DILexicalBlock(scope: !945, file: !1, line: 487, column: 2)
!952 = !DILocation(line: 487, column: 2, scope: !953)
!953 = !DILexicalBlockFile(scope: !945, file: !1, discriminator: 3)
!954 = !DILocation(line: 490, column: 23, scope: !342)
!955 = !DILocation(line: 490, column: 26, scope: !342)
!956 = !DILocation(line: 490, column: 2, scope: !342)
!957 = !DILocation(line: 491, column: 6, scope: !958)
!958 = distinct !DILexicalBlock(scope: !342, file: !1, line: 491, column: 6)
!959 = !DILocation(line: 491, column: 9, scope: !958)
!960 = !DILocation(line: 491, column: 17, scope: !958)
!961 = !DILocation(line: 491, column: 23, scope: !958)
!962 = !DILocation(line: 491, column: 6, scope: !342)
!963 = !DILocation(line: 492, column: 41, scope: !964)
!964 = distinct !DILexicalBlock(scope: !958, file: !1, line: 491, column: 45)
!965 = !DILocation(line: 492, column: 44, scope: !964)
!966 = !DILocation(line: 492, column: 7, scope: !964)
!967 = !DILocation(line: 492, column: 5, scope: !964)
!968 = !DILocation(line: 493, column: 7, scope: !969)
!969 = distinct !DILexicalBlock(scope: !964, file: !1, line: 493, column: 7)
!970 = !DILocation(line: 493, column: 9, scope: !969)
!971 = !DILocation(line: 493, column: 7, scope: !964)
!972 = !DILocation(line: 494, column: 12, scope: !969)
!973 = !DILocation(line: 494, column: 4, scope: !969)
!974 = !DILocation(line: 495, column: 2, scope: !964)
!975 = !DILocation(line: 498, column: 2, scope: !342)
!976 = !DILocation(line: 498, column: 5, scope: !342)
!977 = !DILocation(line: 498, column: 9, scope: !342)
!978 = !DILocation(line: 499, column: 2, scope: !342)
!979 = !DILocation(line: 499, column: 5, scope: !342)
!980 = !DILocation(line: 499, column: 19, scope: !342)
!981 = !DILocation(line: 500, column: 2, scope: !342)
!982 = !DILocation(line: 500, column: 5, scope: !342)
!983 = !DILocation(line: 500, column: 14, scope: !342)
!984 = !DILocation(line: 501, column: 6, scope: !985)
!985 = distinct !DILexicalBlock(scope: !342, file: !1, line: 501, column: 6)
!986 = !DILocation(line: 501, column: 9, scope: !985)
!987 = !DILocation(line: 501, column: 6, scope: !342)
!988 = !DILocation(line: 502, column: 22, scope: !989)
!989 = distinct !DILexicalBlock(scope: !985, file: !1, line: 501, column: 16)
!990 = !DILocation(line: 502, column: 25, scope: !989)
!991 = !DILocation(line: 502, column: 3, scope: !989)
!992 = !DILocation(line: 503, column: 3, scope: !989)
!993 = !DILocation(line: 503, column: 6, scope: !989)
!994 = !DILocation(line: 503, column: 12, scope: !989)
!995 = !DILocation(line: 504, column: 2, scope: !989)
!996 = !DILocation(line: 505, column: 33, scope: !342)
!997 = !DILocation(line: 505, column: 13, scope: !342)
!998 = !DILocation(line: 505, column: 2, scope: !342)
!999 = !DILocation(line: 505, column: 5, scope: !342)
!1000 = !DILocation(line: 505, column: 11, scope: !342)
!1001 = !DILocation(line: 506, column: 2, scope: !342)
!1002 = !DILocation(line: 506, column: 5, scope: !342)
!1003 = !DILocation(line: 506, column: 8, scope: !342)
!1004 = !DILocation(line: 507, column: 2, scope: !342)
!1005 = !DILocation(line: 507, column: 5, scope: !342)
!1006 = !DILocation(line: 507, column: 15, scope: !342)
!1007 = !DILocation(line: 508, column: 2, scope: !342)
!1008 = !DILocation(line: 508, column: 5, scope: !342)
!1009 = !DILocation(line: 508, column: 12, scope: !342)
!1010 = !DILocation(line: 509, column: 2, scope: !342)
!1011 = !DILocation(line: 509, column: 5, scope: !342)
!1012 = !DILocation(line: 509, column: 17, scope: !342)
!1013 = !DILocation(line: 510, column: 11, scope: !342)
!1014 = !DILocation(line: 510, column: 14, scope: !342)
!1015 = !DILocation(line: 510, column: 2, scope: !342)
!1016 = !DILocation(line: 510, column: 5, scope: !342)
!1017 = !DILocation(line: 510, column: 9, scope: !342)
!1018 = !DILocation(line: 511, column: 31, scope: !342)
!1019 = !DILocation(line: 511, column: 34, scope: !342)
!1020 = !DILocation(line: 511, column: 12, scope: !342)
!1021 = !DILocation(line: 511, column: 2, scope: !342)
!1022 = !DILocation(line: 511, column: 5, scope: !342)
!1023 = !DILocation(line: 511, column: 10, scope: !342)
!1024 = !DILocation(line: 512, column: 32, scope: !1025)
!1025 = distinct !DILexicalBlock(scope: !342, file: !1, line: 512, column: 6)
!1026 = !DILocation(line: 512, column: 35, scope: !1025)
!1027 = !DILocation(line: 512, column: 6, scope: !1025)
!1028 = !DILocation(line: 512, column: 6, scope: !342)
!1029 = !DILocation(line: 513, column: 36, scope: !1025)
!1030 = !DILocation(line: 513, column: 39, scope: !1025)
!1031 = !DILocation(line: 513, column: 17, scope: !1025)
!1032 = !DILocation(line: 513, column: 3, scope: !1025)
!1033 = !DILocation(line: 513, column: 6, scope: !1025)
!1034 = !DILocation(line: 513, column: 15, scope: !1025)
!1035 = !DILocation(line: 515, column: 3, scope: !1025)
!1036 = !DILocation(line: 515, column: 6, scope: !1025)
!1037 = !DILocation(line: 515, column: 15, scope: !1025)
!1038 = !DILocation(line: 516, column: 2, scope: !342)
!1039 = !DILocation(line: 516, column: 2, scope: !1040)
!1040 = !DILexicalBlockFile(scope: !342, file: !1, discriminator: 4)
!1041 = !DILocation(line: 516, column: 2, scope: !1042)
!1042 = !DILexicalBlockFile(scope: !342, file: !1, discriminator: 1)
!1043 = !DILocation(line: 516, column: 2, scope: !1044)
!1044 = !DILexicalBlockFile(scope: !342, file: !1, discriminator: 2)
!1045 = !DILocation(line: 516, column: 2, scope: !1046)
!1046 = !DILexicalBlockFile(scope: !1044, file: !1, discriminator: 5)
!1047 = !DILocation(line: 516, column: 2, scope: !1048)
!1048 = !DILexicalBlockFile(scope: !342, file: !1, discriminator: 3)
!1049 = !DILocation(line: 517, column: 12, scope: !342)
!1050 = !DILocation(line: 517, column: 15, scope: !342)
!1051 = !DILocation(line: 517, column: 26, scope: !342)
!1052 = !DILocation(line: 517, column: 2, scope: !342)
!1053 = !DILocation(line: 517, column: 5, scope: !342)
!1054 = !DILocation(line: 517, column: 10, scope: !342)
!1055 = !DILocation(line: 518, column: 23, scope: !342)
!1056 = !DILocation(line: 518, column: 26, scope: !342)
!1057 = !DILocation(line: 518, column: 2, scope: !342)
!1058 = !DILocation(line: 525, column: 25, scope: !342)
!1059 = !DILocation(line: 525, column: 8, scope: !342)
!1060 = !DILocation(line: 525, column: 6, scope: !342)
!1061 = !DILocation(line: 526, column: 6, scope: !1062)
!1062 = distinct !DILexicalBlock(scope: !342, file: !1, line: 526, column: 6)
!1063 = !DILocation(line: 526, column: 10, scope: !1062)
!1064 = !DILocation(line: 526, column: 6, scope: !342)
!1065 = !DILocation(line: 527, column: 11, scope: !1062)
!1066 = !DILocation(line: 527, column: 3, scope: !1062)
!1067 = !DILocation(line: 535, column: 24, scope: !342)
!1068 = !DILocation(line: 535, column: 8, scope: !342)
!1069 = !DILocation(line: 535, column: 11, scope: !342)
!1070 = !DILocation(line: 535, column: 22, scope: !342)
!1071 = !DILocation(line: 535, column: 2, scope: !1042)
!1072 = !DILocation(line: 538, column: 2, scope: !342)
!1073 = !DILocation(line: 538, column: 5, scope: !342)
!1074 = !DILocation(line: 538, column: 10, scope: !342)
!1075 = !DILocation(line: 539, column: 6, scope: !1076)
!1076 = distinct !DILexicalBlock(scope: !342, file: !1, line: 539, column: 6)
!1077 = !DILocation(line: 539, column: 9, scope: !1076)
!1078 = !DILocation(line: 539, column: 15, scope: !1076)
!1079 = !DILocation(line: 539, column: 6, scope: !342)
!1080 = !DILocation(line: 540, column: 3, scope: !1081)
!1081 = distinct !DILexicalBlock(scope: !1076, file: !1, line: 539, column: 39)
!1082 = !DILocation(line: 540, column: 6, scope: !1081)
!1083 = !DILocation(line: 540, column: 11, scope: !1081)
!1084 = !DILocation(line: 555, column: 7, scope: !1085)
!1085 = distinct !DILexicalBlock(scope: !1081, file: !1, line: 555, column: 7)
!1086 = !DILocation(line: 555, column: 10, scope: !1085)
!1087 = !DILocation(line: 555, column: 15, scope: !1085)
!1088 = !DILocation(line: 555, column: 7, scope: !1081)
!1089 = !DILocation(line: 556, column: 4, scope: !1085)
!1090 = !DILocation(line: 556, column: 7, scope: !1085)
!1091 = !DILocation(line: 556, column: 12, scope: !1085)
!1092 = !DILocation(line: 561, column: 7, scope: !1093)
!1093 = distinct !DILexicalBlock(scope: !1081, file: !1, line: 561, column: 7)
!1094 = !DILocation(line: 561, column: 10, scope: !1093)
!1095 = !DILocation(line: 561, column: 15, scope: !1093)
!1096 = !DILocation(line: 561, column: 7, scope: !1081)
!1097 = !DILocation(line: 562, column: 4, scope: !1093)
!1098 = !DILocation(line: 562, column: 7, scope: !1093)
!1099 = !DILocation(line: 562, column: 12, scope: !1093)
!1100 = !DILocation(line: 563, column: 2, scope: !1081)
!1101 = !DILocation(line: 568, column: 3, scope: !1102)
!1102 = distinct !DILexicalBlock(scope: !1076, file: !1, line: 563, column: 9)
!1103 = !DILocation(line: 568, column: 6, scope: !1102)
!1104 = !DILocation(line: 568, column: 11, scope: !1102)
!1105 = !DILocation(line: 569, column: 3, scope: !1102)
!1106 = !DILocation(line: 569, column: 6, scope: !1102)
!1107 = !DILocation(line: 569, column: 11, scope: !1102)
!1108 = !DILocation(line: 570, column: 3, scope: !1102)
!1109 = !DILocation(line: 570, column: 6, scope: !1102)
!1110 = !DILocation(line: 570, column: 11, scope: !1102)
!1111 = !DILocation(line: 571, column: 15, scope: !1102)
!1112 = !DILocation(line: 571, column: 18, scope: !1102)
!1113 = !DILocation(line: 571, column: 14, scope: !1102)
!1114 = !DILocation(line: 571, column: 3, scope: !1102)
!1115 = !DILocation(line: 571, column: 6, scope: !1102)
!1116 = !DILocation(line: 571, column: 11, scope: !1102)
!1117 = !DILocation(line: 573, column: 6, scope: !1118)
!1118 = distinct !DILexicalBlock(scope: !342, file: !1, line: 573, column: 6)
!1119 = !DILocation(line: 573, column: 9, scope: !1118)
!1120 = !DILocation(line: 573, column: 15, scope: !1118)
!1121 = !DILocation(line: 573, column: 6, scope: !342)
!1122 = !DILocation(line: 574, column: 3, scope: !1118)
!1123 = !DILocation(line: 574, column: 6, scope: !1118)
!1124 = !DILocation(line: 574, column: 11, scope: !1118)
!1125 = !DILocation(line: 575, column: 6, scope: !1126)
!1126 = distinct !DILexicalBlock(scope: !342, file: !1, line: 575, column: 6)
!1127 = !DILocation(line: 575, column: 9, scope: !1126)
!1128 = !DILocation(line: 575, column: 15, scope: !1126)
!1129 = !DILocation(line: 575, column: 6, scope: !342)
!1130 = !DILocation(line: 576, column: 3, scope: !1126)
!1131 = !DILocation(line: 576, column: 6, scope: !1126)
!1132 = !DILocation(line: 576, column: 11, scope: !1126)
!1133 = !DILocation(line: 577, column: 6, scope: !1134)
!1134 = distinct !DILexicalBlock(scope: !342, file: !1, line: 577, column: 6)
!1135 = !DILocation(line: 577, column: 9, scope: !1134)
!1136 = !DILocation(line: 577, column: 15, scope: !1134)
!1137 = !DILocation(line: 577, column: 6, scope: !342)
!1138 = !DILocation(line: 578, column: 30, scope: !1139)
!1139 = distinct !DILexicalBlock(scope: !1140, file: !1, line: 578, column: 7)
!1140 = distinct !DILexicalBlock(scope: !1134, file: !1, line: 577, column: 38)
!1141 = !DILocation(line: 578, column: 33, scope: !1139)
!1142 = !DILocation(line: 578, column: 7, scope: !1139)
!1143 = !DILocation(line: 578, column: 40, scope: !1139)
!1144 = !DILocation(line: 578, column: 7, scope: !1140)
!1145 = !DILocation(line: 579, column: 4, scope: !1139)
!1146 = !DILocation(line: 579, column: 7, scope: !1139)
!1147 = !DILocation(line: 579, column: 16, scope: !1139)
!1148 = !DILocation(line: 581, column: 4, scope: !1139)
!1149 = !DILocation(line: 581, column: 7, scope: !1139)
!1150 = !DILocation(line: 581, column: 12, scope: !1139)
!1151 = !DILocation(line: 582, column: 2, scope: !1140)
!1152 = !DILocation(line: 583, column: 6, scope: !1153)
!1153 = distinct !DILexicalBlock(scope: !342, file: !1, line: 583, column: 6)
!1154 = !DILocation(line: 583, column: 9, scope: !1153)
!1155 = !DILocation(line: 583, column: 15, scope: !1153)
!1156 = !DILocation(line: 583, column: 6, scope: !342)
!1157 = !DILocation(line: 584, column: 30, scope: !1158)
!1158 = distinct !DILexicalBlock(scope: !1159, file: !1, line: 584, column: 7)
!1159 = distinct !DILexicalBlock(scope: !1153, file: !1, line: 583, column: 47)
!1160 = !DILocation(line: 584, column: 33, scope: !1158)
!1161 = !DILocation(line: 584, column: 7, scope: !1158)
!1162 = !DILocation(line: 584, column: 40, scope: !1158)
!1163 = !DILocation(line: 584, column: 7, scope: !1159)
!1164 = !DILocation(line: 585, column: 4, scope: !1158)
!1165 = !DILocation(line: 585, column: 7, scope: !1158)
!1166 = !DILocation(line: 585, column: 16, scope: !1158)
!1167 = !DILocation(line: 587, column: 4, scope: !1158)
!1168 = !DILocation(line: 587, column: 7, scope: !1158)
!1169 = !DILocation(line: 587, column: 12, scope: !1158)
!1170 = !DILocation(line: 588, column: 2, scope: !1159)
!1171 = !DILocation(line: 622, column: 6, scope: !1172)
!1172 = distinct !DILexicalBlock(scope: !342, file: !1, line: 622, column: 6)
!1173 = !DILocation(line: 622, column: 9, scope: !1172)
!1174 = !DILocation(line: 622, column: 15, scope: !1172)
!1175 = !DILocation(line: 622, column: 6, scope: !342)
!1176 = !DILocation(line: 623, column: 3, scope: !1172)
!1177 = !DILocation(line: 623, column: 6, scope: !1172)
!1178 = !DILocation(line: 623, column: 11, scope: !1172)
!1179 = !DILocation(line: 624, column: 6, scope: !1180)
!1180 = distinct !DILexicalBlock(scope: !342, file: !1, line: 624, column: 6)
!1181 = !DILocation(line: 624, column: 9, scope: !1180)
!1182 = !DILocation(line: 624, column: 15, scope: !1180)
!1183 = !DILocation(line: 624, column: 6, scope: !342)
!1184 = !DILocation(line: 625, column: 3, scope: !1180)
!1185 = !DILocation(line: 625, column: 6, scope: !1180)
!1186 = !DILocation(line: 625, column: 11, scope: !1180)
!1187 = !DILocation(line: 626, column: 6, scope: !1188)
!1188 = distinct !DILexicalBlock(scope: !342, file: !1, line: 626, column: 6)
!1189 = !DILocation(line: 626, column: 9, scope: !1188)
!1190 = !DILocation(line: 626, column: 15, scope: !1188)
!1191 = !DILocation(line: 626, column: 6, scope: !342)
!1192 = !DILocation(line: 627, column: 24, scope: !1193)
!1193 = distinct !DILexicalBlock(scope: !1188, file: !1, line: 626, column: 50)
!1194 = !DILocation(line: 627, column: 9, scope: !1193)
!1195 = !DILocation(line: 627, column: 7, scope: !1193)
!1196 = !DILocation(line: 628, column: 7, scope: !1197)
!1197 = distinct !DILexicalBlock(scope: !1193, file: !1, line: 628, column: 7)
!1198 = !DILocation(line: 628, column: 11, scope: !1197)
!1199 = !DILocation(line: 628, column: 7, scope: !1193)
!1200 = !DILocation(line: 629, column: 12, scope: !1197)
!1201 = !DILocation(line: 629, column: 4, scope: !1197)
!1202 = !DILocation(line: 630, column: 2, scope: !1193)
!1203 = !DILocation(line: 633, column: 24, scope: !342)
!1204 = !DILocation(line: 633, column: 2, scope: !342)
!1205 = !DILocation(line: 636, column: 22, scope: !342)
!1206 = !DILocation(line: 636, column: 8, scope: !342)
!1207 = !DILocation(line: 636, column: 6, scope: !342)
!1208 = !DILocation(line: 669, column: 6, scope: !1209)
!1209 = distinct !DILexicalBlock(scope: !342, file: !1, line: 669, column: 6)
!1210 = !DILocation(line: 669, column: 9, scope: !1209)
!1211 = !DILocation(line: 669, column: 21, scope: !1209)
!1212 = !DILocation(line: 669, column: 6, scope: !342)
!1213 = !DILocation(line: 670, column: 14, scope: !1214)
!1214 = distinct !DILexicalBlock(scope: !1209, file: !1, line: 669, column: 27)
!1215 = !DILocation(line: 670, column: 17, scope: !1214)
!1216 = !DILocation(line: 670, column: 7, scope: !1214)
!1217 = !DILocation(line: 670, column: 5, scope: !1214)
!1218 = !DILocation(line: 671, column: 7, scope: !1219)
!1219 = distinct !DILexicalBlock(scope: !1214, file: !1, line: 671, column: 7)
!1220 = !DILocation(line: 671, column: 9, scope: !1219)
!1221 = !DILocation(line: 671, column: 7, scope: !1214)
!1222 = !DILocation(line: 672, column: 23, scope: !1223)
!1223 = distinct !DILexicalBlock(scope: !1219, file: !1, line: 671, column: 15)
!1224 = !DILocation(line: 672, column: 26, scope: !1223)
!1225 = !DILocation(line: 672, column: 35, scope: !1223)
!1226 = !DILocation(line: 672, column: 4, scope: !1227)
!1227 = !DILexicalBlockFile(scope: !1223, file: !1, discriminator: 1)
!1228 = !DILocation(line: 674, column: 8, scope: !1223)
!1229 = !DILocation(line: 675, column: 3, scope: !1223)
!1230 = !DILocation(line: 676, column: 9, scope: !1214)
!1231 = !DILocation(line: 676, column: 12, scope: !1214)
!1232 = !DILocation(line: 676, column: 3, scope: !1214)
!1233 = !DILocation(line: 677, column: 3, scope: !1214)
!1234 = !DILocation(line: 677, column: 6, scope: !1214)
!1235 = !DILocation(line: 677, column: 18, scope: !1214)
!1236 = !DILocation(line: 678, column: 2, scope: !1214)
!1237 = !DILocation(line: 687, column: 6, scope: !1238)
!1238 = distinct !DILexicalBlock(scope: !342, file: !1, line: 687, column: 6)
!1239 = !DILocation(line: 687, column: 9, scope: !1238)
!1240 = !DILocation(line: 687, column: 18, scope: !1238)
!1241 = !DILocation(line: 687, column: 6, scope: !342)
!1242 = !DILocation(line: 688, column: 22, scope: !1243)
!1243 = distinct !DILexicalBlock(scope: !1238, file: !1, line: 687, column: 31)
!1244 = !DILocation(line: 688, column: 48, scope: !1243)
!1245 = !DILocation(line: 688, column: 25, scope: !1243)
!1246 = !DILocation(line: 688, column: 8, scope: !1247)
!1247 = !DILexicalBlockFile(scope: !1243, file: !1, discriminator: 1)
!1248 = !DILocation(line: 688, column: 6, scope: !1243)
!1249 = !DILocation(line: 689, column: 7, scope: !1250)
!1250 = distinct !DILexicalBlock(scope: !1243, file: !1, line: 689, column: 7)
!1251 = !DILocation(line: 689, column: 10, scope: !1250)
!1252 = !DILocation(line: 689, column: 7, scope: !1243)
!1253 = !DILocation(line: 690, column: 4, scope: !1250)
!1254 = !DILocation(line: 691, column: 3, scope: !1243)
!1255 = !DILocation(line: 691, column: 7, scope: !1243)
!1256 = !DILocation(line: 691, column: 13, scope: !1243)
!1257 = !DILocation(line: 692, column: 14, scope: !1243)
!1258 = !DILocation(line: 692, column: 17, scope: !1243)
!1259 = !DILocation(line: 692, column: 3, scope: !1243)
!1260 = !DILocation(line: 692, column: 7, scope: !1243)
!1261 = !DILocation(line: 692, column: 12, scope: !1243)
!1262 = !DILocation(line: 693, column: 2, scope: !1243)
!1263 = !DILocation(line: 695, column: 7, scope: !1264)
!1264 = distinct !DILexicalBlock(scope: !342, file: !1, line: 695, column: 6)
!1265 = !DILocation(line: 695, column: 10, scope: !1264)
!1266 = !DILocation(line: 695, column: 19, scope: !1264)
!1267 = !DILocation(line: 696, column: 3, scope: !1264)
!1268 = !DILocation(line: 696, column: 34, scope: !1269)
!1269 = !DILexicalBlockFile(scope: !1264, file: !1, discriminator: 1)
!1270 = !DILocation(line: 696, column: 7, scope: !1269)
!1271 = !DILocation(line: 697, column: 7, scope: !1264)
!1272 = !DILocation(line: 697, column: 37, scope: !1269)
!1273 = !DILocation(line: 697, column: 10, scope: !1269)
!1274 = !DILocation(line: 695, column: 6, scope: !1042)
!1275 = !DILocation(line: 698, column: 22, scope: !1276)
!1276 = distinct !DILexicalBlock(scope: !1264, file: !1, line: 697, column: 46)
!1277 = !DILocation(line: 698, column: 48, scope: !1276)
!1278 = !DILocation(line: 698, column: 25, scope: !1276)
!1279 = !DILocation(line: 698, column: 8, scope: !1280)
!1280 = !DILexicalBlockFile(scope: !1276, file: !1, discriminator: 1)
!1281 = !DILocation(line: 698, column: 6, scope: !1276)
!1282 = !DILocation(line: 699, column: 7, scope: !1283)
!1283 = distinct !DILexicalBlock(scope: !1276, file: !1, line: 699, column: 7)
!1284 = !DILocation(line: 699, column: 10, scope: !1283)
!1285 = !DILocation(line: 699, column: 7, scope: !1276)
!1286 = !DILocation(line: 700, column: 4, scope: !1283)
!1287 = !DILocation(line: 701, column: 14, scope: !1276)
!1288 = !DILocation(line: 701, column: 17, scope: !1276)
!1289 = !DILocation(line: 701, column: 3, scope: !1276)
!1290 = !DILocation(line: 701, column: 7, scope: !1276)
!1291 = !DILocation(line: 701, column: 12, scope: !1276)
!1292 = !DILocation(line: 702, column: 3, scope: !1276)
!1293 = !DILocation(line: 702, column: 7, scope: !1276)
!1294 = !DILocation(line: 702, column: 13, scope: !1276)
!1295 = !DILocation(line: 703, column: 34, scope: !1296)
!1296 = distinct !DILexicalBlock(scope: !1276, file: !1, line: 703, column: 7)
!1297 = !DILocation(line: 703, column: 7, scope: !1296)
!1298 = !DILocation(line: 703, column: 7, scope: !1276)
!1299 = !DILocation(line: 704, column: 36, scope: !1300)
!1300 = distinct !DILexicalBlock(scope: !1296, file: !1, line: 703, column: 42)
!1301 = !DILocation(line: 704, column: 16, scope: !1300)
!1302 = !DILocation(line: 704, column: 4, scope: !1300)
!1303 = !DILocation(line: 704, column: 8, scope: !1300)
!1304 = !DILocation(line: 704, column: 14, scope: !1300)
!1305 = !DILocation(line: 705, column: 47, scope: !1300)
!1306 = !DILocation(line: 705, column: 22, scope: !1300)
!1307 = !DILocation(line: 705, column: 4, scope: !1300)
!1308 = !DILocation(line: 705, column: 8, scope: !1300)
!1309 = !DILocation(line: 705, column: 20, scope: !1300)
!1310 = !DILocation(line: 706, column: 3, scope: !1300)
!1311 = !DILocation(line: 708, column: 16, scope: !1312)
!1312 = distinct !DILexicalBlock(scope: !1296, file: !1, line: 706, column: 10)
!1313 = !DILocation(line: 708, column: 19, scope: !1312)
!1314 = !DILocation(line: 708, column: 4, scope: !1312)
!1315 = !DILocation(line: 708, column: 8, scope: !1312)
!1316 = !DILocation(line: 708, column: 14, scope: !1312)
!1317 = !DILocation(line: 709, column: 4, scope: !1312)
!1318 = !DILocation(line: 709, column: 8, scope: !1312)
!1319 = !DILocation(line: 709, column: 20, scope: !1312)
!1320 = !DILocation(line: 711, column: 34, scope: !1321)
!1321 = distinct !DILexicalBlock(scope: !1276, file: !1, line: 711, column: 7)
!1322 = !DILocation(line: 711, column: 7, scope: !1321)
!1323 = !DILocation(line: 711, column: 7, scope: !1276)
!1324 = !DILocation(line: 712, column: 36, scope: !1325)
!1325 = distinct !DILexicalBlock(scope: !1321, file: !1, line: 711, column: 42)
!1326 = !DILocation(line: 712, column: 16, scope: !1325)
!1327 = !DILocation(line: 712, column: 4, scope: !1325)
!1328 = !DILocation(line: 712, column: 8, scope: !1325)
!1329 = !DILocation(line: 712, column: 14, scope: !1325)
!1330 = !DILocation(line: 713, column: 47, scope: !1325)
!1331 = !DILocation(line: 713, column: 22, scope: !1325)
!1332 = !DILocation(line: 713, column: 4, scope: !1325)
!1333 = !DILocation(line: 713, column: 8, scope: !1325)
!1334 = !DILocation(line: 713, column: 20, scope: !1325)
!1335 = !DILocation(line: 714, column: 3, scope: !1325)
!1336 = !DILocation(line: 716, column: 16, scope: !1337)
!1337 = distinct !DILexicalBlock(scope: !1321, file: !1, line: 714, column: 10)
!1338 = !DILocation(line: 716, column: 19, scope: !1337)
!1339 = !DILocation(line: 716, column: 4, scope: !1337)
!1340 = !DILocation(line: 716, column: 8, scope: !1337)
!1341 = !DILocation(line: 716, column: 14, scope: !1337)
!1342 = !DILocation(line: 717, column: 4, scope: !1337)
!1343 = !DILocation(line: 717, column: 8, scope: !1337)
!1344 = !DILocation(line: 717, column: 20, scope: !1337)
!1345 = !DILocation(line: 719, column: 38, scope: !1346)
!1346 = distinct !DILexicalBlock(scope: !1276, file: !1, line: 719, column: 7)
!1347 = !DILocation(line: 719, column: 7, scope: !1346)
!1348 = !DILocation(line: 719, column: 7, scope: !1276)
!1349 = !DILocation(line: 720, column: 44, scope: !1350)
!1350 = distinct !DILexicalBlock(scope: !1346, file: !1, line: 719, column: 46)
!1351 = !DILocation(line: 720, column: 20, scope: !1350)
!1352 = !DILocation(line: 720, column: 4, scope: !1350)
!1353 = !DILocation(line: 720, column: 8, scope: !1350)
!1354 = !DILocation(line: 720, column: 18, scope: !1350)
!1355 = !DILocation(line: 722, column: 8, scope: !1350)
!1356 = !DILocation(line: 721, column: 26, scope: !1350)
!1357 = !DILocation(line: 721, column: 4, scope: !1350)
!1358 = !DILocation(line: 721, column: 8, scope: !1350)
!1359 = !DILocation(line: 721, column: 24, scope: !1350)
!1360 = !DILocation(line: 723, column: 3, scope: !1350)
!1361 = !DILocation(line: 725, column: 20, scope: !1362)
!1362 = distinct !DILexicalBlock(scope: !1346, file: !1, line: 723, column: 10)
!1363 = !DILocation(line: 725, column: 24, scope: !1362)
!1364 = !DILocation(line: 725, column: 4, scope: !1362)
!1365 = !DILocation(line: 725, column: 8, scope: !1362)
!1366 = !DILocation(line: 725, column: 18, scope: !1362)
!1367 = !DILocation(line: 726, column: 26, scope: !1362)
!1368 = !DILocation(line: 726, column: 30, scope: !1362)
!1369 = !DILocation(line: 726, column: 4, scope: !1362)
!1370 = !DILocation(line: 726, column: 8, scope: !1362)
!1371 = !DILocation(line: 726, column: 24, scope: !1362)
!1372 = !DILocation(line: 728, column: 2, scope: !1276)
!1373 = !DILocation(line: 730, column: 6, scope: !1374)
!1374 = distinct !DILexicalBlock(scope: !342, file: !1, line: 730, column: 6)
!1375 = !DILocation(line: 730, column: 9, scope: !1374)
!1376 = !DILocation(line: 730, column: 18, scope: !1374)
!1377 = !DILocation(line: 730, column: 6, scope: !342)
!1378 = !DILocation(line: 731, column: 22, scope: !1379)
!1379 = distinct !DILexicalBlock(scope: !1374, file: !1, line: 730, column: 31)
!1380 = !DILocation(line: 731, column: 48, scope: !1379)
!1381 = !DILocation(line: 731, column: 25, scope: !1379)
!1382 = !DILocation(line: 731, column: 8, scope: !1383)
!1383 = !DILexicalBlockFile(scope: !1379, file: !1, discriminator: 1)
!1384 = !DILocation(line: 731, column: 6, scope: !1379)
!1385 = !DILocation(line: 732, column: 7, scope: !1386)
!1386 = distinct !DILexicalBlock(scope: !1379, file: !1, line: 732, column: 7)
!1387 = !DILocation(line: 732, column: 10, scope: !1386)
!1388 = !DILocation(line: 732, column: 7, scope: !1379)
!1389 = !DILocation(line: 733, column: 4, scope: !1386)
!1390 = !DILocation(line: 734, column: 3, scope: !1379)
!1391 = !DILocation(line: 734, column: 7, scope: !1379)
!1392 = !DILocation(line: 734, column: 13, scope: !1379)
!1393 = !DILocation(line: 735, column: 21, scope: !1379)
!1394 = !DILocation(line: 735, column: 25, scope: !1379)
!1395 = !DILocation(line: 735, column: 48, scope: !1379)
!1396 = !DILocation(line: 735, column: 30, scope: !1379)
!1397 = !DILocation(line: 735, column: 3, scope: !1383)
!1398 = !DILocation(line: 736, column: 2, scope: !1379)
!1399 = !DILocation(line: 738, column: 6, scope: !1400)
!1400 = distinct !DILexicalBlock(scope: !342, file: !1, line: 738, column: 6)
!1401 = !DILocation(line: 738, column: 9, scope: !1400)
!1402 = !DILocation(line: 738, column: 18, scope: !1400)
!1403 = !DILocation(line: 738, column: 6, scope: !342)
!1404 = !DILocalVariable(name: "metadata", scope: !1405, file: !1, line: 739, type: !42)
!1405 = distinct !DILexicalBlock(scope: !1400, file: !1, line: 738, column: 39)
!1406 = !DILocation(line: 739, column: 15, scope: !1405)
!1407 = !DILocalVariable(name: "metadata_size", scope: !1405, file: !1, line: 740, type: !44)
!1408 = !DILocation(line: 740, column: 10, scope: !1405)
!1409 = !DILocation(line: 741, column: 41, scope: !1405)
!1410 = !DILocation(line: 741, column: 44, scope: !1405)
!1411 = !DILocation(line: 741, column: 14, scope: !1405)
!1412 = !DILocation(line: 741, column: 12, scope: !1405)
!1413 = !DILocation(line: 742, column: 7, scope: !1414)
!1414 = distinct !DILexicalBlock(scope: !1405, file: !1, line: 742, column: 7)
!1415 = !DILocation(line: 742, column: 16, scope: !1414)
!1416 = !DILocation(line: 742, column: 24, scope: !1414)
!1417 = !DILocation(line: 742, column: 27, scope: !1418)
!1418 = !DILexicalBlockFile(scope: !1414, file: !1, discriminator: 1)
!1419 = !DILocation(line: 742, column: 41, scope: !1418)
!1420 = !DILocation(line: 742, column: 7, scope: !1418)
!1421 = !DILocation(line: 743, column: 23, scope: !1422)
!1422 = distinct !DILexicalBlock(scope: !1414, file: !1, line: 742, column: 46)
!1423 = !DILocation(line: 743, column: 49, scope: !1422)
!1424 = !DILocation(line: 743, column: 26, scope: !1422)
!1425 = !DILocation(line: 743, column: 9, scope: !1426)
!1426 = !DILexicalBlockFile(scope: !1422, file: !1, discriminator: 1)
!1427 = !DILocation(line: 743, column: 7, scope: !1422)
!1428 = !DILocation(line: 744, column: 8, scope: !1429)
!1429 = distinct !DILexicalBlock(scope: !1422, file: !1, line: 744, column: 8)
!1430 = !DILocation(line: 744, column: 11, scope: !1429)
!1431 = !DILocation(line: 744, column: 8, scope: !1422)
!1432 = !DILocation(line: 745, column: 5, scope: !1429)
!1433 = !DILocation(line: 746, column: 30, scope: !1422)
!1434 = !DILocation(line: 746, column: 23, scope: !1422)
!1435 = !DILocation(line: 746, column: 4, scope: !1422)
!1436 = !DILocation(line: 746, column: 8, scope: !1422)
!1437 = !DILocation(line: 746, column: 21, scope: !1422)
!1438 = !DILocation(line: 747, column: 8, scope: !1439)
!1439 = distinct !DILexicalBlock(scope: !1422, file: !1, line: 747, column: 8)
!1440 = !DILocation(line: 747, column: 12, scope: !1439)
!1441 = !DILocation(line: 747, column: 25, scope: !1439)
!1442 = !DILocation(line: 747, column: 8, scope: !1422)
!1443 = !DILocation(line: 748, column: 12, scope: !1444)
!1444 = distinct !DILexicalBlock(scope: !1439, file: !1, line: 747, column: 34)
!1445 = !DILocation(line: 748, column: 16, scope: !1444)
!1446 = !DILocation(line: 748, column: 30, scope: !1444)
!1447 = !DILocation(line: 749, column: 9, scope: !1444)
!1448 = !DILocation(line: 748, column: 5, scope: !1444)
!1449 = !DILocation(line: 750, column: 29, scope: !1444)
!1450 = !DILocation(line: 750, column: 5, scope: !1444)
!1451 = !DILocation(line: 750, column: 9, scope: !1444)
!1452 = !DILocation(line: 750, column: 27, scope: !1444)
!1453 = !DILocation(line: 751, column: 5, scope: !1444)
!1454 = !DILocation(line: 751, column: 9, scope: !1444)
!1455 = !DILocation(line: 751, column: 15, scope: !1444)
!1456 = !DILocation(line: 752, column: 4, scope: !1444)
!1457 = !DILocation(line: 753, column: 3, scope: !1422)
!1458 = !DILocation(line: 754, column: 2, scope: !1405)
!1459 = !DILocation(line: 756, column: 6, scope: !1460)
!1460 = distinct !DILexicalBlock(scope: !342, file: !1, line: 756, column: 6)
!1461 = !DILocation(line: 756, column: 9, scope: !1460)
!1462 = !DILocation(line: 756, column: 18, scope: !1460)
!1463 = !DILocation(line: 756, column: 6, scope: !342)
!1464 = !DILocation(line: 757, column: 22, scope: !1465)
!1465 = distinct !DILexicalBlock(scope: !1460, file: !1, line: 756, column: 33)
!1466 = !DILocation(line: 757, column: 48, scope: !1465)
!1467 = !DILocation(line: 757, column: 25, scope: !1465)
!1468 = !DILocation(line: 757, column: 8, scope: !1469)
!1469 = !DILexicalBlockFile(scope: !1465, file: !1, discriminator: 1)
!1470 = !DILocation(line: 757, column: 6, scope: !1465)
!1471 = !DILocation(line: 758, column: 7, scope: !1472)
!1472 = distinct !DILexicalBlock(scope: !1465, file: !1, line: 758, column: 7)
!1473 = !DILocation(line: 758, column: 10, scope: !1472)
!1474 = !DILocation(line: 758, column: 7, scope: !1465)
!1475 = !DILocation(line: 759, column: 4, scope: !1472)
!1476 = !DILocation(line: 760, column: 3, scope: !1465)
!1477 = !DILocation(line: 760, column: 7, scope: !1465)
!1478 = !DILocation(line: 760, column: 13, scope: !1465)
!1479 = !DILocation(line: 762, column: 2, scope: !1465)
!1480 = !DILocation(line: 765, column: 6, scope: !1481)
!1481 = distinct !DILexicalBlock(scope: !342, file: !1, line: 765, column: 6)
!1482 = !DILocation(line: 765, column: 10, scope: !1481)
!1483 = !DILocation(line: 765, column: 6, scope: !342)
!1484 = !DILocation(line: 766, column: 3, scope: !1481)
!1485 = !DILocation(line: 766, column: 6, scope: !1481)
!1486 = !DILocation(line: 766, column: 14, scope: !1481)
!1487 = !DILocation(line: 766, column: 20, scope: !1481)
!1488 = !DILocation(line: 771, column: 6, scope: !1489)
!1489 = distinct !DILexicalBlock(scope: !342, file: !1, line: 771, column: 6)
!1490 = !DILocation(line: 771, column: 9, scope: !1489)
!1491 = !DILocation(line: 771, column: 12, scope: !1489)
!1492 = !DILocation(line: 771, column: 6, scope: !342)
!1493 = !DILocation(line: 772, column: 26, scope: !1494)
!1494 = distinct !DILexicalBlock(scope: !1489, file: !1, line: 771, column: 17)
!1495 = !DILocation(line: 772, column: 3, scope: !1494)
!1496 = !DILocation(line: 773, column: 3, scope: !1494)
!1497 = !DILocation(line: 773, column: 6, scope: !1494)
!1498 = !DILocation(line: 773, column: 15, scope: !1494)
!1499 = !DILocation(line: 774, column: 2, scope: !1494)
!1500 = !DILocation(line: 776, column: 10, scope: !342)
!1501 = !DILocation(line: 776, column: 2, scope: !342)
!1502 = !DILocation(line: 777, column: 1, scope: !342)
!1503 = !DILocalVariable(name: "_a", arg: 1, scope: !373, file: !1, line: 1531, type: !23)
!1504 = !DILocation(line: 1531, column: 50, scope: !373)
!1505 = !DILocalVariable(name: "a", scope: !373, file: !1, line: 1533, type: !4)
!1506 = !DILocation(line: 1533, column: 29, scope: !373)
!1507 = !DILocation(line: 1533, column: 62, scope: !373)
!1508 = !DILocation(line: 1533, column: 33, scope: !373)
!1509 = !DILocalVariable(name: "ret", scope: !373, file: !1, line: 1534, type: !22)
!1510 = !DILocation(line: 1534, column: 6, scope: !373)
!1511 = !DILocation(line: 1536, column: 2, scope: !373)
!1512 = !DILocalVariable(name: "magic_test", scope: !1513, file: !1, line: 1536, type: !22)
!1513 = distinct !DILexicalBlock(scope: !373, file: !1, line: 1536, column: 2)
!1514 = !DILocation(line: 1536, column: 2, scope: !1513)
!1515 = !DILocation(line: 1536, column: 2, scope: !1516)
!1516 = !DILexicalBlockFile(scope: !1513, file: !1, discriminator: 1)
!1517 = !DILocation(line: 1536, column: 2, scope: !1518)
!1518 = !DILexicalBlockFile(scope: !1519, file: !1, discriminator: 2)
!1519 = distinct !DILexicalBlock(scope: !1513, file: !1, line: 1536, column: 2)
!1520 = !DILocation(line: 1536, column: 2, scope: !1521)
!1521 = !DILexicalBlockFile(scope: !1513, file: !1, discriminator: 3)
!1522 = !DILocation(line: 1539, column: 6, scope: !1523)
!1523 = distinct !DILexicalBlock(scope: !373, file: !1, line: 1539, column: 6)
!1524 = !DILocation(line: 1539, column: 9, scope: !1523)
!1525 = !DILocation(line: 1539, column: 17, scope: !1523)
!1526 = !DILocation(line: 1539, column: 23, scope: !1523)
!1527 = !DILocation(line: 1539, column: 6, scope: !373)
!1528 = !DILocation(line: 1540, column: 3, scope: !1523)
!1529 = !DILocation(line: 1541, column: 23, scope: !373)
!1530 = !DILocation(line: 1541, column: 26, scope: !373)
!1531 = !DILocation(line: 1541, column: 2, scope: !373)
!1532 = !DILocation(line: 1544, column: 6, scope: !1533)
!1533 = distinct !DILexicalBlock(scope: !373, file: !1, line: 1544, column: 6)
!1534 = !DILocation(line: 1544, column: 9, scope: !1533)
!1535 = !DILocation(line: 1544, column: 12, scope: !1533)
!1536 = !DILocation(line: 1544, column: 6, scope: !373)
!1537 = !DILocation(line: 1546, column: 2, scope: !1538)
!1538 = distinct !DILexicalBlock(scope: !1533, file: !1, line: 1544, column: 17)
!1539 = !DILocation(line: 1546, column: 13, scope: !1540)
!1540 = !DILexicalBlockFile(scope: !1541, file: !1, discriminator: 1)
!1541 = distinct !DILexicalBlock(scope: !1533, file: !1, line: 1546, column: 13)
!1542 = !DILocation(line: 1546, column: 16, scope: !1540)
!1543 = !DILocation(line: 1546, column: 25, scope: !1540)
!1544 = !DILocation(line: 1548, column: 2, scope: !1545)
!1545 = distinct !DILexicalBlock(scope: !1541, file: !1, line: 1546, column: 30)
!1546 = !DILocation(line: 1548, column: 13, scope: !1547)
!1547 = !DILexicalBlockFile(scope: !1548, file: !1, discriminator: 1)
!1548 = distinct !DILexicalBlock(scope: !1541, file: !1, line: 1548, column: 13)
!1549 = !DILocation(line: 1548, column: 16, scope: !1547)
!1550 = !DILocation(line: 1548, column: 29, scope: !1547)
!1551 = !DILocation(line: 1548, column: 32, scope: !1547)
!1552 = !DILocation(line: 1548, column: 26, scope: !1547)
!1553 = !DILocation(line: 1569, column: 2, scope: !1554)
!1554 = distinct !DILexicalBlock(scope: !1548, file: !1, line: 1548, column: 42)
!1555 = !DILocation(line: 1571, column: 17, scope: !1556)
!1556 = distinct !DILexicalBlock(scope: !1557, file: !1, line: 1571, column: 7)
!1557 = distinct !DILexicalBlock(scope: !1548, file: !1, line: 1569, column: 9)
!1558 = !DILocation(line: 1571, column: 20, scope: !1556)
!1559 = !DILocation(line: 1571, column: 24, scope: !1556)
!1560 = !DILocation(line: 1571, column: 27, scope: !1556)
!1561 = !DILocation(line: 1571, column: 7, scope: !1556)
!1562 = !DILocation(line: 1571, column: 37, scope: !1556)
!1563 = !DILocation(line: 1571, column: 43, scope: !1556)
!1564 = !DILocation(line: 1572, column: 7, scope: !1556)
!1565 = !DILocation(line: 1572, column: 10, scope: !1556)
!1566 = !DILocation(line: 1572, column: 19, scope: !1556)
!1567 = !DILocation(line: 1571, column: 7, scope: !1568)
!1568 = !DILexicalBlockFile(scope: !1557, file: !1, discriminator: 1)
!1569 = !DILocation(line: 1573, column: 23, scope: !1570)
!1570 = distinct !DILexicalBlock(scope: !1556, file: !1, line: 1572, column: 25)
!1571 = !DILocation(line: 1573, column: 26, scope: !1570)
!1572 = !DILocation(line: 1573, column: 35, scope: !1570)
!1573 = !DILocation(line: 1573, column: 4, scope: !1574)
!1574 = !DILexicalBlockFile(scope: !1570, file: !1, discriminator: 1)
!1575 = !DILocation(line: 1575, column: 4, scope: !1570)
!1576 = !DILocation(line: 1583, column: 3, scope: !1557)
!1577 = !DILocation(line: 1583, column: 6, scope: !1557)
!1578 = !DILocation(line: 1583, column: 10, scope: !1557)
!1579 = !DILocation(line: 1584, column: 24, scope: !1580)
!1580 = distinct !DILexicalBlock(scope: !1557, file: !1, line: 1584, column: 7)
!1581 = !DILocation(line: 1584, column: 14, scope: !1580)
!1582 = !DILocation(line: 1584, column: 12, scope: !1580)
!1583 = !DILocation(line: 1584, column: 28, scope: !1580)
!1584 = !DILocation(line: 1584, column: 7, scope: !1557)
!1585 = !DILocation(line: 1585, column: 12, scope: !1580)
!1586 = !DILocation(line: 1585, column: 4, scope: !1580)
!1587 = !DILocation(line: 1588, column: 7, scope: !1588)
!1588 = distinct !DILexicalBlock(scope: !1557, file: !1, line: 1588, column: 7)
!1589 = !DILocation(line: 1588, column: 10, scope: !1588)
!1590 = !DILocation(line: 1588, column: 13, scope: !1588)
!1591 = !DILocation(line: 1588, column: 23, scope: !1588)
!1592 = !DILocation(line: 1588, column: 26, scope: !1588)
!1593 = !DILocation(line: 1588, column: 21, scope: !1588)
!1594 = !DILocation(line: 1588, column: 7, scope: !1557)
!1595 = !DILocalVariable(name: "nul", scope: !1596, file: !1, line: 1589, type: !80)
!1596 = distinct !DILexicalBlock(scope: !1588, file: !1, line: 1588, column: 36)
!1597 = !DILocation(line: 1589, column: 15, scope: !1596)
!1598 = !DILocation(line: 1590, column: 14, scope: !1599)
!1599 = distinct !DILexicalBlock(scope: !1596, file: !1, line: 1590, column: 8)
!1600 = !DILocation(line: 1590, column: 17, scope: !1599)
!1601 = !DILocation(line: 1590, column: 21, scope: !1599)
!1602 = !DILocation(line: 1590, column: 24, scope: !1599)
!1603 = !DILocation(line: 1590, column: 33, scope: !1599)
!1604 = !DILocation(line: 1590, column: 8, scope: !1599)
!1605 = !DILocation(line: 1590, column: 48, scope: !1599)
!1606 = !DILocation(line: 1590, column: 8, scope: !1596)
!1607 = !DILocation(line: 1591, column: 24, scope: !1608)
!1608 = distinct !DILexicalBlock(scope: !1599, file: !1, line: 1590, column: 53)
!1609 = !DILocation(line: 1591, column: 27, scope: !1608)
!1610 = !DILocation(line: 1591, column: 36, scope: !1608)
!1611 = !DILocation(line: 1591, column: 5, scope: !1612)
!1612 = !DILexicalBlockFile(scope: !1608, file: !1, discriminator: 1)
!1613 = !DILocation(line: 1593, column: 5, scope: !1608)
!1614 = !DILocation(line: 1595, column: 14, scope: !1615)
!1615 = distinct !DILexicalBlock(scope: !1596, file: !1, line: 1595, column: 8)
!1616 = !DILocation(line: 1595, column: 17, scope: !1615)
!1617 = !DILocation(line: 1595, column: 8, scope: !1615)
!1618 = !DILocation(line: 1595, column: 30, scope: !1615)
!1619 = !DILocation(line: 1595, column: 8, scope: !1596)
!1620 = !DILocation(line: 1596, column: 24, scope: !1621)
!1621 = distinct !DILexicalBlock(scope: !1615, file: !1, line: 1595, column: 35)
!1622 = !DILocation(line: 1596, column: 27, scope: !1621)
!1623 = !DILocation(line: 1596, column: 36, scope: !1621)
!1624 = !DILocation(line: 1596, column: 5, scope: !1625)
!1625 = !DILexicalBlockFile(scope: !1621, file: !1, discriminator: 1)
!1626 = !DILocation(line: 1598, column: 5, scope: !1621)
!1627 = !DILocation(line: 1600, column: 4, scope: !1596)
!1628 = !DILocation(line: 1600, column: 7, scope: !1596)
!1629 = !DILocation(line: 1600, column: 11, scope: !1596)
!1630 = !DILocation(line: 1601, column: 3, scope: !1596)
!1631 = !DILocation(line: 1611, column: 6, scope: !1632)
!1632 = distinct !DILexicalBlock(scope: !373, file: !1, line: 1611, column: 6)
!1633 = !DILocation(line: 1611, column: 9, scope: !1632)
!1634 = !DILocation(line: 1611, column: 14, scope: !1632)
!1635 = !DILocation(line: 1611, column: 6, scope: !373)
!1636 = !DILocalVariable(name: "r2", scope: !1637, file: !1, line: 1612, type: !22)
!1637 = distinct !DILexicalBlock(scope: !1632, file: !1, line: 1611, column: 34)
!1638 = !DILocation(line: 1612, column: 7, scope: !1637)
!1639 = !DILocation(line: 1612, column: 30, scope: !1637)
!1640 = !DILocation(line: 1612, column: 33, scope: !1637)
!1641 = !DILocation(line: 1612, column: 36, scope: !1637)
!1642 = !DILocation(line: 1612, column: 12, scope: !1637)
!1643 = !DILocation(line: 1613, column: 7, scope: !1644)
!1644 = distinct !DILexicalBlock(scope: !1637, file: !1, line: 1613, column: 7)
!1645 = !DILocation(line: 1613, column: 10, scope: !1644)
!1646 = !DILocation(line: 1613, column: 7, scope: !1637)
!1647 = !DILocation(line: 1617, column: 4, scope: !1648)
!1648 = distinct !DILexicalBlock(scope: !1644, file: !1, line: 1613, column: 26)
!1649 = !DILocation(line: 1619, column: 7, scope: !1650)
!1650 = distinct !DILexicalBlock(scope: !1637, file: !1, line: 1619, column: 7)
!1651 = !DILocation(line: 1619, column: 12, scope: !1650)
!1652 = !DILocation(line: 1619, column: 10, scope: !1650)
!1653 = !DILocation(line: 1619, column: 7, scope: !1637)
!1654 = !DILocation(line: 1619, column: 23, scope: !1655)
!1655 = !DILexicalBlockFile(scope: !1650, file: !1, discriminator: 1)
!1656 = !DILocation(line: 1619, column: 21, scope: !1655)
!1657 = !DILocation(line: 1619, column: 17, scope: !1655)
!1658 = !DILocation(line: 1620, column: 2, scope: !1637)
!1659 = !DILocation(line: 1626, column: 6, scope: !1660)
!1660 = distinct !DILexicalBlock(scope: !373, file: !1, line: 1626, column: 6)
!1661 = !DILocation(line: 1626, column: 9, scope: !1660)
!1662 = !DILocation(line: 1626, column: 14, scope: !1660)
!1663 = !DILocation(line: 1626, column: 6, scope: !373)
!1664 = !DILocation(line: 1627, column: 36, scope: !1665)
!1665 = distinct !DILexicalBlock(scope: !1660, file: !1, line: 1626, column: 54)
!1666 = !DILocation(line: 1627, column: 39, scope: !1665)
!1667 = !DILocation(line: 1628, column: 27, scope: !1665)
!1668 = !DILocation(line: 1628, column: 30, scope: !1665)
!1669 = !DILocation(line: 1628, column: 7, scope: !1665)
!1670 = !DILocation(line: 1629, column: 25, scope: !1665)
!1671 = !DILocation(line: 1629, column: 28, scope: !1665)
!1672 = !DILocation(line: 1629, column: 7, scope: !1665)
!1673 = !DILocation(line: 1627, column: 12, scope: !1665)
!1674 = !DILocation(line: 1627, column: 3, scope: !1665)
!1675 = !DILocation(line: 1627, column: 6, scope: !1665)
!1676 = !DILocation(line: 1627, column: 10, scope: !1665)
!1677 = !DILocation(line: 1630, column: 2, scope: !1665)
!1678 = !DILocation(line: 1633, column: 6, scope: !1679)
!1679 = distinct !DILexicalBlock(scope: !373, file: !1, line: 1633, column: 6)
!1680 = !DILocation(line: 1633, column: 9, scope: !1679)
!1681 = !DILocation(line: 1633, column: 14, scope: !1679)
!1682 = !DILocation(line: 1633, column: 6, scope: !373)
!1683 = !DILocation(line: 1634, column: 36, scope: !1684)
!1684 = distinct !DILexicalBlock(scope: !1679, file: !1, line: 1633, column: 54)
!1685 = !DILocation(line: 1634, column: 39, scope: !1684)
!1686 = !DILocation(line: 1635, column: 27, scope: !1684)
!1687 = !DILocation(line: 1635, column: 30, scope: !1684)
!1688 = !DILocation(line: 1635, column: 7, scope: !1684)
!1689 = !DILocation(line: 1636, column: 25, scope: !1684)
!1690 = !DILocation(line: 1636, column: 28, scope: !1684)
!1691 = !DILocation(line: 1636, column: 7, scope: !1684)
!1692 = !DILocation(line: 1634, column: 12, scope: !1684)
!1693 = !DILocation(line: 1634, column: 3, scope: !1684)
!1694 = !DILocation(line: 1634, column: 6, scope: !1684)
!1695 = !DILocation(line: 1634, column: 10, scope: !1684)
!1696 = !DILocation(line: 1637, column: 3, scope: !1684)
!1697 = !DILocation(line: 1644, column: 6, scope: !1698)
!1698 = distinct !DILexicalBlock(scope: !373, file: !1, line: 1644, column: 6)
!1699 = !DILocation(line: 1644, column: 9, scope: !1698)
!1700 = !DILocation(line: 1644, column: 14, scope: !1698)
!1701 = !DILocation(line: 1644, column: 6, scope: !373)
!1702 = !DILocalVariable(name: "r2", scope: !1703, file: !1, line: 1645, type: !22)
!1703 = distinct !DILexicalBlock(scope: !1698, file: !1, line: 1644, column: 28)
!1704 = !DILocation(line: 1645, column: 7, scope: !1703)
!1705 = !DILocation(line: 1645, column: 26, scope: !1703)
!1706 = !DILocation(line: 1645, column: 12, scope: !1703)
!1707 = !DILocation(line: 1646, column: 7, scope: !1708)
!1708 = distinct !DILexicalBlock(scope: !1703, file: !1, line: 1646, column: 7)
!1709 = !DILocation(line: 1646, column: 12, scope: !1708)
!1710 = !DILocation(line: 1646, column: 10, scope: !1708)
!1711 = !DILocation(line: 1646, column: 7, scope: !1703)
!1712 = !DILocation(line: 1646, column: 23, scope: !1713)
!1713 = !DILexicalBlockFile(scope: !1708, file: !1, discriminator: 1)
!1714 = !DILocation(line: 1646, column: 21, scope: !1713)
!1715 = !DILocation(line: 1646, column: 17, scope: !1713)
!1716 = !DILocation(line: 1647, column: 2, scope: !1703)
!1717 = !DILocation(line: 1653, column: 6, scope: !1718)
!1718 = distinct !DILexicalBlock(scope: !373, file: !1, line: 1653, column: 6)
!1719 = !DILocation(line: 1653, column: 9, scope: !1718)
!1720 = !DILocation(line: 1653, column: 14, scope: !1718)
!1721 = !DILocation(line: 1653, column: 6, scope: !373)
!1722 = !DILocalVariable(name: "r2", scope: !1723, file: !1, line: 1654, type: !22)
!1723 = distinct !DILexicalBlock(scope: !1718, file: !1, line: 1653, column: 27)
!1724 = !DILocation(line: 1654, column: 7, scope: !1723)
!1725 = !DILocation(line: 1654, column: 21, scope: !1723)
!1726 = !DILocation(line: 1654, column: 24, scope: !1723)
!1727 = !DILocation(line: 1654, column: 27, scope: !1723)
!1728 = !DILocation(line: 1654, column: 12, scope: !1723)
!1729 = !DILocation(line: 1655, column: 7, scope: !1730)
!1730 = distinct !DILexicalBlock(scope: !1723, file: !1, line: 1655, column: 7)
!1731 = !DILocation(line: 1655, column: 12, scope: !1730)
!1732 = !DILocation(line: 1655, column: 10, scope: !1730)
!1733 = !DILocation(line: 1655, column: 7, scope: !1723)
!1734 = !DILocation(line: 1655, column: 23, scope: !1735)
!1735 = !DILexicalBlockFile(scope: !1730, file: !1, discriminator: 1)
!1736 = !DILocation(line: 1655, column: 21, scope: !1735)
!1737 = !DILocation(line: 1655, column: 17, scope: !1735)
!1738 = !DILocation(line: 1656, column: 2, scope: !1723)
!1739 = !DILocation(line: 1663, column: 6, scope: !1740)
!1740 = distinct !DILexicalBlock(scope: !373, file: !1, line: 1663, column: 6)
!1741 = !DILocation(line: 1663, column: 9, scope: !1740)
!1742 = !DILocation(line: 1663, column: 14, scope: !1740)
!1743 = !DILocation(line: 1663, column: 6, scope: !373)
!1744 = !DILocalVariable(name: "r2", scope: !1745, file: !1, line: 1664, type: !22)
!1745 = distinct !DILexicalBlock(scope: !1740, file: !1, line: 1663, column: 28)
!1746 = !DILocation(line: 1664, column: 7, scope: !1745)
!1747 = !DILocation(line: 1664, column: 23, scope: !1745)
!1748 = !DILocation(line: 1664, column: 12, scope: !1745)
!1749 = !DILocation(line: 1665, column: 7, scope: !1750)
!1750 = distinct !DILexicalBlock(scope: !1745, file: !1, line: 1665, column: 7)
!1751 = !DILocation(line: 1665, column: 12, scope: !1750)
!1752 = !DILocation(line: 1665, column: 10, scope: !1750)
!1753 = !DILocation(line: 1665, column: 7, scope: !1745)
!1754 = !DILocation(line: 1665, column: 23, scope: !1755)
!1755 = !DILexicalBlockFile(scope: !1750, file: !1, discriminator: 1)
!1756 = !DILocation(line: 1665, column: 21, scope: !1755)
!1757 = !DILocation(line: 1665, column: 17, scope: !1755)
!1758 = !DILocation(line: 1666, column: 2, scope: !1745)
!1759 = !DILocation(line: 1672, column: 6, scope: !1760)
!1760 = distinct !DILexicalBlock(scope: !373, file: !1, line: 1672, column: 6)
!1761 = !DILocation(line: 1672, column: 9, scope: !1760)
!1762 = !DILocation(line: 1672, column: 14, scope: !1760)
!1763 = !DILocation(line: 1672, column: 6, scope: !373)
!1764 = !DILocalVariable(name: "r2", scope: !1765, file: !1, line: 1673, type: !22)
!1765 = distinct !DILexicalBlock(scope: !1760, file: !1, line: 1672, column: 29)
!1766 = !DILocation(line: 1673, column: 7, scope: !1765)
!1767 = !DILocation(line: 1673, column: 23, scope: !1765)
!1768 = !DILocation(line: 1673, column: 12, scope: !1765)
!1769 = !DILocation(line: 1674, column: 7, scope: !1770)
!1770 = distinct !DILexicalBlock(scope: !1765, file: !1, line: 1674, column: 7)
!1771 = !DILocation(line: 1674, column: 12, scope: !1770)
!1772 = !DILocation(line: 1674, column: 10, scope: !1770)
!1773 = !DILocation(line: 1674, column: 7, scope: !1765)
!1774 = !DILocation(line: 1674, column: 23, scope: !1775)
!1775 = !DILexicalBlockFile(scope: !1770, file: !1, discriminator: 1)
!1776 = !DILocation(line: 1674, column: 21, scope: !1775)
!1777 = !DILocation(line: 1674, column: 17, scope: !1775)
!1778 = !DILocation(line: 1675, column: 2, scope: !1765)
!1779 = !DILocation(line: 1681, column: 6, scope: !1780)
!1780 = distinct !DILexicalBlock(scope: !373, file: !1, line: 1681, column: 6)
!1781 = !DILocation(line: 1681, column: 9, scope: !1780)
!1782 = !DILocation(line: 1681, column: 14, scope: !1780)
!1783 = !DILocation(line: 1681, column: 6, scope: !373)
!1784 = !DILocalVariable(name: "r2", scope: !1785, file: !1, line: 1682, type: !22)
!1785 = distinct !DILexicalBlock(scope: !1780, file: !1, line: 1681, column: 28)
!1786 = !DILocation(line: 1682, column: 7, scope: !1785)
!1787 = !DILocation(line: 1682, column: 33, scope: !1785)
!1788 = !DILocation(line: 1682, column: 12, scope: !1785)
!1789 = !DILocation(line: 1683, column: 7, scope: !1790)
!1790 = distinct !DILexicalBlock(scope: !1785, file: !1, line: 1683, column: 7)
!1791 = !DILocation(line: 1683, column: 12, scope: !1790)
!1792 = !DILocation(line: 1683, column: 10, scope: !1790)
!1793 = !DILocation(line: 1683, column: 7, scope: !1785)
!1794 = !DILocation(line: 1683, column: 23, scope: !1795)
!1795 = !DILexicalBlockFile(scope: !1790, file: !1, discriminator: 1)
!1796 = !DILocation(line: 1683, column: 21, scope: !1795)
!1797 = !DILocation(line: 1683, column: 17, scope: !1795)
!1798 = !DILocation(line: 1684, column: 2, scope: !1785)
!1799 = !DILocation(line: 1689, column: 6, scope: !1800)
!1800 = distinct !DILexicalBlock(scope: !373, file: !1, line: 1689, column: 6)
!1801 = !DILocation(line: 1689, column: 9, scope: !1800)
!1802 = !DILocation(line: 1689, column: 14, scope: !1800)
!1803 = !DILocation(line: 1689, column: 6, scope: !373)
!1804 = !DILocalVariable(name: "metadata", scope: !1805, file: !1, line: 1690, type: !42)
!1805 = distinct !DILexicalBlock(scope: !1800, file: !1, line: 1689, column: 35)
!1806 = !DILocation(line: 1690, column: 15, scope: !1805)
!1807 = !DILocalVariable(name: "metadata_size", scope: !1805, file: !1, line: 1691, type: !44)
!1808 = !DILocation(line: 1691, column: 10, scope: !1805)
!1809 = !DILocation(line: 1692, column: 41, scope: !1805)
!1810 = !DILocation(line: 1692, column: 44, scope: !1805)
!1811 = !DILocation(line: 1692, column: 14, scope: !1805)
!1812 = !DILocation(line: 1692, column: 12, scope: !1805)
!1813 = !DILocation(line: 1693, column: 7, scope: !1814)
!1814 = distinct !DILexicalBlock(scope: !1805, file: !1, line: 1693, column: 7)
!1815 = !DILocation(line: 1693, column: 16, scope: !1814)
!1816 = !DILocation(line: 1693, column: 24, scope: !1814)
!1817 = !DILocation(line: 1693, column: 27, scope: !1818)
!1818 = !DILexicalBlockFile(scope: !1814, file: !1, discriminator: 1)
!1819 = !DILocation(line: 1693, column: 41, scope: !1818)
!1820 = !DILocation(line: 1693, column: 7, scope: !1818)
!1821 = !DILocalVariable(name: "r2", scope: !1822, file: !1, line: 1694, type: !22)
!1822 = distinct !DILexicalBlock(scope: !1814, file: !1, line: 1693, column: 46)
!1823 = !DILocation(line: 1694, column: 8, scope: !1822)
!1824 = !DILocation(line: 1694, column: 30, scope: !1822)
!1825 = !DILocation(line: 1695, column: 8, scope: !1822)
!1826 = !DILocation(line: 1695, column: 11, scope: !1822)
!1827 = !DILocation(line: 1694, column: 33, scope: !1822)
!1828 = !DILocation(line: 1695, column: 19, scope: !1822)
!1829 = !DILocation(line: 1695, column: 29, scope: !1822)
!1830 = !DILocation(line: 1694, column: 13, scope: !1831)
!1831 = !DILexicalBlockFile(scope: !1822, file: !1, discriminator: 1)
!1832 = !DILocation(line: 1696, column: 8, scope: !1833)
!1833 = distinct !DILexicalBlock(scope: !1822, file: !1, line: 1696, column: 8)
!1834 = !DILocation(line: 1696, column: 13, scope: !1833)
!1835 = !DILocation(line: 1696, column: 11, scope: !1833)
!1836 = !DILocation(line: 1696, column: 8, scope: !1822)
!1837 = !DILocation(line: 1696, column: 24, scope: !1838)
!1838 = !DILexicalBlockFile(scope: !1833, file: !1, discriminator: 1)
!1839 = !DILocation(line: 1696, column: 22, scope: !1838)
!1840 = !DILocation(line: 1696, column: 18, scope: !1838)
!1841 = !DILocation(line: 1697, column: 3, scope: !1822)
!1842 = !DILocation(line: 1698, column: 2, scope: !1805)
!1843 = !DILocation(line: 1704, column: 6, scope: !1844)
!1844 = distinct !DILexicalBlock(scope: !373, file: !1, line: 1704, column: 6)
!1845 = !DILocation(line: 1704, column: 9, scope: !1844)
!1846 = !DILocation(line: 1704, column: 14, scope: !1844)
!1847 = !DILocation(line: 1704, column: 6, scope: !373)
!1848 = !DILocalVariable(name: "r2", scope: !1849, file: !1, line: 1705, type: !22)
!1849 = distinct !DILexicalBlock(scope: !1844, file: !1, line: 1704, column: 27)
!1850 = !DILocation(line: 1705, column: 7, scope: !1849)
!1851 = !DILocation(line: 1718, column: 37, scope: !1849)
!1852 = !DILocation(line: 1718, column: 40, scope: !1849)
!1853 = !DILocation(line: 1718, column: 49, scope: !1849)
!1854 = !DILocation(line: 1718, column: 52, scope: !1849)
!1855 = !DILocation(line: 1719, column: 30, scope: !1849)
!1856 = !DILocation(line: 1719, column: 33, scope: !1849)
!1857 = !DILocation(line: 1719, column: 7, scope: !1849)
!1858 = !DILocation(line: 1720, column: 25, scope: !1849)
!1859 = !DILocation(line: 1720, column: 28, scope: !1849)
!1860 = !DILocation(line: 1720, column: 7, scope: !1849)
!1861 = !DILocation(line: 1718, column: 8, scope: !1849)
!1862 = !DILocation(line: 1718, column: 6, scope: !1849)
!1863 = !DILocation(line: 1721, column: 7, scope: !1864)
!1864 = distinct !DILexicalBlock(scope: !1849, file: !1, line: 1721, column: 7)
!1865 = !DILocation(line: 1721, column: 12, scope: !1864)
!1866 = !DILocation(line: 1721, column: 10, scope: !1864)
!1867 = !DILocation(line: 1721, column: 7, scope: !1849)
!1868 = !DILocation(line: 1721, column: 23, scope: !1869)
!1869 = !DILexicalBlockFile(scope: !1864, file: !1, discriminator: 1)
!1870 = !DILocation(line: 1721, column: 21, scope: !1869)
!1871 = !DILocation(line: 1721, column: 17, scope: !1869)
!1872 = !DILocation(line: 1725, column: 2, scope: !1849)
!1873 = !DILocation(line: 1704, column: 16, scope: !1874)
!1874 = !DILexicalBlockFile(scope: !1844, file: !1, discriminator: 1)
!1875 = !DILocation(line: 1729, column: 6, scope: !1876)
!1876 = distinct !DILexicalBlock(scope: !373, file: !1, line: 1729, column: 6)
!1877 = !DILocation(line: 1729, column: 9, scope: !1876)
!1878 = !DILocation(line: 1729, column: 12, scope: !1876)
!1879 = !DILocation(line: 1729, column: 6, scope: !373)
!1880 = !DILocation(line: 1730, column: 9, scope: !1881)
!1881 = distinct !DILexicalBlock(scope: !1876, file: !1, line: 1729, column: 18)
!1882 = !DILocation(line: 1730, column: 12, scope: !1881)
!1883 = !DILocation(line: 1730, column: 3, scope: !1881)
!1884 = !DILocation(line: 1731, column: 3, scope: !1881)
!1885 = !DILocation(line: 1731, column: 6, scope: !1881)
!1886 = !DILocation(line: 1731, column: 9, scope: !1881)
!1887 = !DILocation(line: 1732, column: 2, scope: !1881)
!1888 = !DILocation(line: 1734, column: 6, scope: !1889)
!1889 = distinct !DILexicalBlock(scope: !373, file: !1, line: 1734, column: 6)
!1890 = !DILocation(line: 1734, column: 9, scope: !1889)
!1891 = !DILocation(line: 1734, column: 6, scope: !373)
!1892 = !DILocation(line: 1735, column: 22, scope: !1893)
!1893 = distinct !DILexicalBlock(scope: !1889, file: !1, line: 1734, column: 16)
!1894 = !DILocation(line: 1735, column: 25, scope: !1893)
!1895 = !DILocation(line: 1735, column: 3, scope: !1893)
!1896 = !DILocation(line: 1736, column: 3, scope: !1893)
!1897 = !DILocation(line: 1736, column: 6, scope: !1893)
!1898 = !DILocation(line: 1736, column: 12, scope: !1893)
!1899 = !DILocation(line: 1737, column: 2, scope: !1893)
!1900 = !DILocation(line: 1738, column: 2, scope: !373)
!1901 = !DILocation(line: 1738, column: 5, scope: !373)
!1902 = !DILocation(line: 1738, column: 13, scope: !373)
!1903 = !DILocation(line: 1738, column: 19, scope: !373)
!1904 = !DILocation(line: 1739, column: 10, scope: !373)
!1905 = !DILocation(line: 1739, column: 2, scope: !373)
!1906 = !DILocation(line: 1740, column: 1, scope: !373)
!1907 = !DILocalVariable(name: "_a", arg: 1, scope: !385, file: !1, line: 1518, type: !23)
!1908 = !DILocation(line: 1518, column: 42, scope: !385)
!1909 = !DILocalVariable(name: "buff", arg: 2, scope: !385, file: !1, line: 1518, type: !42)
!1910 = !DILocation(line: 1518, column: 58, scope: !385)
!1911 = !DILocalVariable(name: "size", arg: 3, scope: !385, file: !1, line: 1518, type: !44)
!1912 = !DILocation(line: 1518, column: 71, scope: !385)
!1913 = !DILocalVariable(name: "a", scope: !385, file: !1, line: 1520, type: !4)
!1914 = !DILocation(line: 1520, column: 29, scope: !385)
!1915 = !DILocation(line: 1520, column: 62, scope: !385)
!1916 = !DILocation(line: 1520, column: 33, scope: !385)
!1917 = !DILocation(line: 1522, column: 2, scope: !385)
!1918 = !DILocalVariable(name: "magic_test", scope: !1919, file: !1, line: 1522, type: !22)
!1919 = distinct !DILexicalBlock(scope: !385, file: !1, line: 1522, column: 2)
!1920 = !DILocation(line: 1522, column: 2, scope: !1919)
!1921 = !DILocation(line: 1522, column: 2, scope: !1922)
!1922 = !DILexicalBlockFile(scope: !1919, file: !1, discriminator: 1)
!1923 = !DILocation(line: 1522, column: 2, scope: !1924)
!1924 = !DILexicalBlockFile(scope: !1925, file: !1, discriminator: 2)
!1925 = distinct !DILexicalBlock(scope: !1919, file: !1, line: 1522, column: 2)
!1926 = !DILocation(line: 1522, column: 2, scope: !1927)
!1927 = !DILexicalBlockFile(scope: !1919, file: !1, discriminator: 3)
!1928 = !DILocation(line: 1525, column: 6, scope: !1929)
!1929 = distinct !DILexicalBlock(scope: !385, file: !1, line: 1525, column: 6)
!1930 = !DILocation(line: 1525, column: 9, scope: !1929)
!1931 = !DILocation(line: 1525, column: 14, scope: !1929)
!1932 = !DILocation(line: 1525, column: 6, scope: !385)
!1933 = !DILocation(line: 1526, column: 32, scope: !1929)
!1934 = !DILocation(line: 1526, column: 35, scope: !1929)
!1935 = !DILocation(line: 1526, column: 41, scope: !1929)
!1936 = !DILocation(line: 1526, column: 11, scope: !1929)
!1937 = !DILocation(line: 1526, column: 3, scope: !1929)
!1938 = !DILocation(line: 1527, column: 27, scope: !385)
!1939 = !DILocation(line: 1527, column: 30, scope: !385)
!1940 = !DILocation(line: 1527, column: 36, scope: !385)
!1941 = !DILocation(line: 1527, column: 10, scope: !385)
!1942 = !DILocation(line: 1527, column: 2, scope: !385)
!1943 = !DILocation(line: 1528, column: 1, scope: !385)
!1944 = !DILocalVariable(name: "_a", arg: 1, scope: !390, file: !1, line: 1488, type: !23)
!1945 = !DILocation(line: 1488, column: 48, scope: !390)
!1946 = !DILocalVariable(name: "buff", arg: 2, scope: !390, file: !1, line: 1489, type: !42)
!1947 = !DILocation(line: 1489, column: 17, scope: !390)
!1948 = !DILocalVariable(name: "size", arg: 3, scope: !390, file: !1, line: 1489, type: !44)
!1949 = !DILocation(line: 1489, column: 30, scope: !390)
!1950 = !DILocalVariable(name: "offset", arg: 4, scope: !390, file: !1, line: 1489, type: !51)
!1951 = !DILocation(line: 1489, column: 44, scope: !390)
!1952 = !DILocalVariable(name: "a", scope: !390, file: !1, line: 1491, type: !4)
!1953 = !DILocation(line: 1491, column: 29, scope: !390)
!1954 = !DILocation(line: 1491, column: 62, scope: !390)
!1955 = !DILocation(line: 1491, column: 33, scope: !390)
!1956 = !DILocalVariable(name: "r", scope: !390, file: !1, line: 1492, type: !37)
!1957 = !DILocation(line: 1492, column: 10, scope: !390)
!1958 = !DILocation(line: 1494, column: 2, scope: !390)
!1959 = !DILocalVariable(name: "magic_test", scope: !1960, file: !1, line: 1494, type: !22)
!1960 = distinct !DILexicalBlock(scope: !390, file: !1, line: 1494, column: 2)
!1961 = !DILocation(line: 1494, column: 2, scope: !1960)
!1962 = !DILocation(line: 1494, column: 2, scope: !1963)
!1963 = !DILexicalBlockFile(scope: !1960, file: !1, discriminator: 1)
!1964 = !DILocation(line: 1494, column: 2, scope: !1965)
!1965 = !DILexicalBlockFile(scope: !1966, file: !1, discriminator: 2)
!1966 = distinct !DILexicalBlock(scope: !1960, file: !1, line: 1494, column: 2)
!1967 = !DILocation(line: 1494, column: 2, scope: !1968)
!1968 = !DILexicalBlockFile(scope: !1960, file: !1, discriminator: 3)
!1969 = !DILocation(line: 1497, column: 14, scope: !390)
!1970 = !DILocation(line: 1497, column: 2, scope: !390)
!1971 = !DILocation(line: 1497, column: 5, scope: !390)
!1972 = !DILocation(line: 1497, column: 12, scope: !390)
!1973 = !DILocation(line: 1498, column: 6, scope: !1974)
!1974 = distinct !DILexicalBlock(scope: !390, file: !1, line: 1498, column: 6)
!1975 = !DILocation(line: 1498, column: 9, scope: !1974)
!1976 = !DILocation(line: 1498, column: 14, scope: !1974)
!1977 = !DILocation(line: 1498, column: 6, scope: !390)
!1978 = !DILocation(line: 1499, column: 28, scope: !1974)
!1979 = !DILocation(line: 1499, column: 31, scope: !1974)
!1980 = !DILocation(line: 1499, column: 37, scope: !1974)
!1981 = !DILocation(line: 1499, column: 7, scope: !1974)
!1982 = !DILocation(line: 1499, column: 5, scope: !1974)
!1983 = !DILocation(line: 1499, column: 3, scope: !1974)
!1984 = !DILocation(line: 1501, column: 24, scope: !1974)
!1985 = !DILocation(line: 1501, column: 27, scope: !1974)
!1986 = !DILocation(line: 1501, column: 33, scope: !1974)
!1987 = !DILocation(line: 1501, column: 7, scope: !1974)
!1988 = !DILocation(line: 1501, column: 5, scope: !1974)
!1989 = !DILocation(line: 1502, column: 6, scope: !1990)
!1990 = distinct !DILexicalBlock(scope: !390, file: !1, line: 1502, column: 6)
!1991 = !DILocation(line: 1502, column: 8, scope: !1990)
!1992 = !DILocation(line: 1502, column: 6, scope: !390)
!1993 = !DILocation(line: 1503, column: 11, scope: !1990)
!1994 = !DILocation(line: 1503, column: 3, scope: !1990)
!1995 = !DILocation(line: 1504, column: 14, scope: !1996)
!1996 = distinct !DILexicalBlock(scope: !390, file: !1, line: 1504, column: 6)
!1997 = !DILocation(line: 1504, column: 18, scope: !1996)
!1998 = !DILocation(line: 1504, column: 16, scope: !1996)
!1999 = !DILocation(line: 1504, column: 6, scope: !390)
!2000 = !DILocation(line: 1505, column: 22, scope: !2001)
!2001 = distinct !DILexicalBlock(scope: !1996, file: !1, line: 1504, column: 24)
!2002 = !DILocation(line: 1505, column: 25, scope: !2001)
!2003 = !DILocation(line: 1507, column: 18, scope: !2001)
!2004 = !DILocation(line: 1507, column: 21, scope: !2001)
!2005 = !DILocation(line: 1505, column: 3, scope: !2001)
!2006 = !DILocation(line: 1508, column: 3, scope: !2001)
!2007 = !DILocation(line: 1511, column: 2, scope: !390)
!2008 = !DILocation(line: 1515, column: 1, scope: !390)
!2009 = !DILocalVariable(name: "p", arg: 1, scope: !325, file: !1, line: 2367, type: !113)
!2010 = !DILocation(line: 2367, column: 35, scope: !325)
!2011 = !DILocalVariable(name: "a", scope: !325, file: !1, line: 2369, type: !113)
!2012 = !DILocation(line: 2369, column: 22, scope: !325)
!2013 = !DILocalVariable(name: "b", scope: !325, file: !1, line: 2369, type: !113)
!2014 = !DILocation(line: 2369, column: 26, scope: !325)
!2015 = !DILocalVariable(name: "t", scope: !325, file: !1, line: 2369, type: !113)
!2016 = !DILocation(line: 2369, column: 30, scope: !325)
!2017 = !DILocation(line: 2371, column: 6, scope: !2018)
!2018 = distinct !DILexicalBlock(scope: !325, file: !1, line: 2371, column: 6)
!2019 = !DILocation(line: 2371, column: 8, scope: !2018)
!2020 = !DILocation(line: 2371, column: 6, scope: !325)
!2021 = !DILocation(line: 2372, column: 3, scope: !2018)
!2022 = !DILocation(line: 2374, column: 6, scope: !2023)
!2023 = distinct !DILexicalBlock(scope: !325, file: !1, line: 2374, column: 6)
!2024 = !DILocation(line: 2374, column: 9, scope: !2023)
!2025 = !DILocation(line: 2374, column: 14, scope: !2023)
!2026 = !DILocation(line: 2374, column: 6, scope: !325)
!2027 = !DILocation(line: 2375, column: 11, scope: !2023)
!2028 = !DILocation(line: 2375, column: 3, scope: !2023)
!2029 = !DILocation(line: 2378, column: 6, scope: !325)
!2030 = !DILocation(line: 2378, column: 4, scope: !325)
!2031 = !DILocation(line: 2379, column: 6, scope: !325)
!2032 = !DILocation(line: 2379, column: 9, scope: !325)
!2033 = !DILocation(line: 2379, column: 15, scope: !325)
!2034 = !DILocation(line: 2379, column: 4, scope: !325)
!2035 = !DILocation(line: 2380, column: 2, scope: !325)
!2036 = !DILocation(line: 2380, column: 9, scope: !2037)
!2037 = !DILexicalBlockFile(scope: !325, file: !1, discriminator: 1)
!2038 = !DILocation(line: 2380, column: 11, scope: !2037)
!2039 = !DILocation(line: 2380, column: 2, scope: !2037)
!2040 = !DILocation(line: 2382, column: 7, scope: !2041)
!2041 = distinct !DILexicalBlock(scope: !325, file: !1, line: 2380, column: 20)
!2042 = !DILocation(line: 2382, column: 10, scope: !2041)
!2043 = !DILocation(line: 2382, column: 5, scope: !2041)
!2044 = !DILocation(line: 2383, column: 7, scope: !2045)
!2045 = distinct !DILexicalBlock(scope: !2041, file: !1, line: 2383, column: 7)
!2046 = !DILocation(line: 2383, column: 9, scope: !2045)
!2047 = !DILocation(line: 2383, column: 7, scope: !2041)
!2048 = !DILocation(line: 2384, column: 8, scope: !2045)
!2049 = !DILocation(line: 2384, column: 11, scope: !2045)
!2050 = !DILocation(line: 2384, column: 6, scope: !2045)
!2051 = !DILocation(line: 2384, column: 4, scope: !2045)
!2052 = !DILocation(line: 2385, column: 7, scope: !2041)
!2053 = !DILocation(line: 2385, column: 10, scope: !2041)
!2054 = !DILocation(line: 2385, column: 5, scope: !2041)
!2055 = !DILocation(line: 2380, column: 2, scope: !2056)
!2056 = !DILexicalBlockFile(scope: !325, file: !1, discriminator: 2)
!2057 = !DILocation(line: 2388, column: 6, scope: !325)
!2058 = !DILocation(line: 2388, column: 9, scope: !325)
!2059 = !DILocation(line: 2388, column: 4, scope: !325)
!2060 = !DILocation(line: 2389, column: 2, scope: !325)
!2061 = !DILocation(line: 2389, column: 5, scope: !325)
!2062 = !DILocation(line: 2389, column: 10, scope: !325)
!2063 = !DILocation(line: 2390, column: 6, scope: !325)
!2064 = !DILocation(line: 2390, column: 4, scope: !325)
!2065 = !DILocation(line: 2393, column: 20, scope: !325)
!2066 = !DILocation(line: 2393, column: 6, scope: !325)
!2067 = !DILocation(line: 2393, column: 4, scope: !325)
!2068 = !DILocation(line: 2394, column: 20, scope: !325)
!2069 = !DILocation(line: 2394, column: 6, scope: !325)
!2070 = !DILocation(line: 2394, column: 4, scope: !325)
!2071 = !DILocation(line: 2398, column: 13, scope: !2072)
!2072 = distinct !DILexicalBlock(scope: !325, file: !1, line: 2398, column: 6)
!2073 = !DILocation(line: 2398, column: 16, scope: !2072)
!2074 = !DILocation(line: 2398, column: 22, scope: !2072)
!2075 = !DILocation(line: 2398, column: 25, scope: !2072)
!2076 = !DILocation(line: 2398, column: 6, scope: !2072)
!2077 = !DILocation(line: 2398, column: 31, scope: !2072)
!2078 = !DILocation(line: 2398, column: 6, scope: !325)
!2079 = !DILocation(line: 2399, column: 11, scope: !2080)
!2080 = distinct !DILexicalBlock(scope: !2072, file: !1, line: 2398, column: 36)
!2081 = !DILocation(line: 2399, column: 9, scope: !2080)
!2082 = !DILocation(line: 2399, column: 5, scope: !2080)
!2083 = !DILocation(line: 2400, column: 7, scope: !2080)
!2084 = !DILocation(line: 2400, column: 10, scope: !2080)
!2085 = !DILocation(line: 2400, column: 5, scope: !2080)
!2086 = !DILocation(line: 2401, column: 2, scope: !2080)
!2087 = !DILocation(line: 2402, column: 11, scope: !2088)
!2088 = distinct !DILexicalBlock(scope: !2072, file: !1, line: 2401, column: 9)
!2089 = !DILocation(line: 2402, column: 9, scope: !2088)
!2090 = !DILocation(line: 2402, column: 5, scope: !2088)
!2091 = !DILocation(line: 2403, column: 7, scope: !2088)
!2092 = !DILocation(line: 2403, column: 10, scope: !2088)
!2093 = !DILocation(line: 2403, column: 5, scope: !2088)
!2094 = !DILocation(line: 2407, column: 2, scope: !325)
!2095 = !DILocation(line: 2407, column: 9, scope: !2037)
!2096 = !DILocation(line: 2407, column: 11, scope: !2037)
!2097 = !DILocation(line: 2407, column: 19, scope: !2037)
!2098 = !DILocation(line: 2407, column: 22, scope: !2056)
!2099 = !DILocation(line: 2407, column: 24, scope: !2056)
!2100 = !DILocation(line: 2407, column: 2, scope: !2101)
!2101 = !DILexicalBlockFile(scope: !325, file: !1, discriminator: 3)
!2102 = !DILocation(line: 2408, column: 14, scope: !2103)
!2103 = distinct !DILexicalBlock(scope: !2104, file: !1, line: 2408, column: 7)
!2104 = distinct !DILexicalBlock(scope: !325, file: !1, line: 2407, column: 33)
!2105 = !DILocation(line: 2408, column: 17, scope: !2103)
!2106 = !DILocation(line: 2408, column: 23, scope: !2103)
!2107 = !DILocation(line: 2408, column: 26, scope: !2103)
!2108 = !DILocation(line: 2408, column: 7, scope: !2103)
!2109 = !DILocation(line: 2408, column: 32, scope: !2103)
!2110 = !DILocation(line: 2408, column: 7, scope: !2104)
!2111 = !DILocation(line: 2409, column: 14, scope: !2112)
!2112 = distinct !DILexicalBlock(scope: !2103, file: !1, line: 2408, column: 37)
!2113 = !DILocation(line: 2409, column: 4, scope: !2112)
!2114 = !DILocation(line: 2409, column: 7, scope: !2112)
!2115 = !DILocation(line: 2409, column: 12, scope: !2112)
!2116 = !DILocation(line: 2410, column: 8, scope: !2112)
!2117 = !DILocation(line: 2410, column: 11, scope: !2112)
!2118 = !DILocation(line: 2410, column: 6, scope: !2112)
!2119 = !DILocation(line: 2411, column: 3, scope: !2112)
!2120 = !DILocation(line: 2412, column: 14, scope: !2121)
!2121 = distinct !DILexicalBlock(scope: !2103, file: !1, line: 2411, column: 10)
!2122 = !DILocation(line: 2412, column: 4, scope: !2121)
!2123 = !DILocation(line: 2412, column: 7, scope: !2121)
!2124 = !DILocation(line: 2412, column: 12, scope: !2121)
!2125 = !DILocation(line: 2413, column: 8, scope: !2121)
!2126 = !DILocation(line: 2413, column: 11, scope: !2121)
!2127 = !DILocation(line: 2413, column: 6, scope: !2121)
!2128 = !DILocation(line: 2415, column: 7, scope: !2104)
!2129 = !DILocation(line: 2415, column: 10, scope: !2104)
!2130 = !DILocation(line: 2415, column: 5, scope: !2104)
!2131 = !DILocation(line: 2407, column: 2, scope: !2132)
!2132 = !DILexicalBlockFile(scope: !325, file: !1, discriminator: 4)
!2133 = !DILocation(line: 2419, column: 6, scope: !2134)
!2134 = distinct !DILexicalBlock(scope: !325, file: !1, line: 2419, column: 6)
!2135 = !DILocation(line: 2419, column: 8, scope: !2134)
!2136 = !DILocation(line: 2419, column: 6, scope: !325)
!2137 = !DILocation(line: 2420, column: 13, scope: !2134)
!2138 = !DILocation(line: 2420, column: 3, scope: !2134)
!2139 = !DILocation(line: 2420, column: 6, scope: !2134)
!2140 = !DILocation(line: 2420, column: 11, scope: !2134)
!2141 = !DILocation(line: 2421, column: 6, scope: !2142)
!2142 = distinct !DILexicalBlock(scope: !325, file: !1, line: 2421, column: 6)
!2143 = !DILocation(line: 2421, column: 8, scope: !2142)
!2144 = !DILocation(line: 2421, column: 6, scope: !325)
!2145 = !DILocation(line: 2422, column: 13, scope: !2142)
!2146 = !DILocation(line: 2422, column: 3, scope: !2142)
!2147 = !DILocation(line: 2422, column: 6, scope: !2142)
!2148 = !DILocation(line: 2422, column: 11, scope: !2142)
!2149 = !DILocation(line: 2424, column: 10, scope: !325)
!2150 = !DILocation(line: 2424, column: 2, scope: !325)
!2151 = !DILocation(line: 2425, column: 1, scope: !325)
!2152 = !DILocalVariable(name: "a", arg: 1, scope: !328, file: !1, line: 3217, type: !4)
!2153 = !DILocation(line: 3217, column: 38, scope: !328)
!2154 = !DILocalVariable(name: "fd", arg: 2, scope: !328, file: !1, line: 3218, type: !22)
!2155 = !DILocation(line: 3218, column: 9, scope: !328)
!2156 = !DILocalVariable(name: "mode", arg: 3, scope: !328, file: !1, line: 3218, type: !22)
!2157 = !DILocation(line: 3218, column: 17, scope: !328)
!2158 = !DILocalVariable(name: "name", arg: 4, scope: !328, file: !1, line: 3218, type: !79)
!2159 = !DILocation(line: 3218, column: 35, scope: !328)
!2160 = !DILocalVariable(name: "atime", arg: 5, scope: !328, file: !1, line: 3219, type: !172)
!2161 = !DILocation(line: 3219, column: 12, scope: !328)
!2162 = !DILocalVariable(name: "atime_nanos", arg: 6, scope: !328, file: !1, line: 3219, type: !41)
!2163 = !DILocation(line: 3219, column: 24, scope: !328)
!2164 = !DILocalVariable(name: "birthtime", arg: 7, scope: !328, file: !1, line: 3220, type: !172)
!2165 = !DILocation(line: 3220, column: 12, scope: !328)
!2166 = !DILocalVariable(name: "birthtime_nanos", arg: 8, scope: !328, file: !1, line: 3220, type: !41)
!2167 = !DILocation(line: 3220, column: 28, scope: !328)
!2168 = !DILocalVariable(name: "mtime", arg: 9, scope: !328, file: !1, line: 3221, type: !172)
!2169 = !DILocation(line: 3221, column: 12, scope: !328)
!2170 = !DILocalVariable(name: "mtime_nanos", arg: 10, scope: !328, file: !1, line: 3221, type: !41)
!2171 = !DILocation(line: 3221, column: 24, scope: !328)
!2172 = !DILocalVariable(name: "cctime", arg: 11, scope: !328, file: !1, line: 3222, type: !172)
!2173 = !DILocation(line: 3222, column: 12, scope: !328)
!2174 = !DILocalVariable(name: "ctime_nanos", arg: 12, scope: !328, file: !1, line: 3222, type: !41)
!2175 = !DILocation(line: 3222, column: 25, scope: !328)
!2176 = !DILocalVariable(name: "r1", scope: !328, file: !1, line: 3226, type: !22)
!2177 = !DILocation(line: 3226, column: 6, scope: !328)
!2178 = !DILocalVariable(name: "r2", scope: !328, file: !1, line: 3226, type: !22)
!2179 = !DILocation(line: 3226, column: 14, scope: !328)
!2180 = !DILocation(line: 3241, column: 8, scope: !328)
!2181 = !DILocation(line: 3242, column: 8, scope: !328)
!2182 = !DILocation(line: 3260, column: 8, scope: !328)
!2183 = !DILocation(line: 3261, column: 8, scope: !328)
!2184 = !DILocation(line: 3263, column: 16, scope: !328)
!2185 = !DILocation(line: 3263, column: 20, scope: !328)
!2186 = !DILocation(line: 3263, column: 26, scope: !328)
!2187 = !DILocation(line: 3264, column: 9, scope: !328)
!2188 = !DILocation(line: 3264, column: 16, scope: !328)
!2189 = !DILocation(line: 3265, column: 9, scope: !328)
!2190 = !DILocation(line: 3265, column: 16, scope: !328)
!2191 = !DILocation(line: 3263, column: 7, scope: !328)
!2192 = !DILocation(line: 3263, column: 5, scope: !328)
!2193 = !DILocation(line: 3266, column: 6, scope: !2194)
!2194 = distinct !DILexicalBlock(scope: !328, file: !1, line: 3266, column: 6)
!2195 = !DILocation(line: 3266, column: 9, scope: !2194)
!2196 = !DILocation(line: 3266, column: 14, scope: !2194)
!2197 = !DILocation(line: 3266, column: 17, scope: !2198)
!2198 = !DILexicalBlockFile(scope: !2194, file: !1, discriminator: 1)
!2199 = !DILocation(line: 3266, column: 20, scope: !2198)
!2200 = !DILocation(line: 3266, column: 6, scope: !2198)
!2201 = !DILocation(line: 3267, column: 22, scope: !2202)
!2202 = distinct !DILexicalBlock(scope: !2194, file: !1, line: 3266, column: 26)
!2203 = !DILocation(line: 3267, column: 25, scope: !2202)
!2204 = !DILocation(line: 3267, column: 34, scope: !2202)
!2205 = !DILocation(line: 3267, column: 3, scope: !2206)
!2206 = !DILexicalBlockFile(scope: !2202, file: !1, discriminator: 1)
!2207 = !DILocation(line: 3269, column: 3, scope: !2202)
!2208 = !DILocation(line: 3271, column: 2, scope: !328)
!2209 = !DILocation(line: 3272, column: 1, scope: !328)
!2210 = !DILocalVariable(name: "a", arg: 1, scope: !334, file: !1, line: 3602, type: !4)
!2211 = !DILocation(line: 3602, column: 48, scope: !334)
!2212 = !DILocalVariable(name: "fd", arg: 2, scope: !334, file: !1, line: 3602, type: !22)
!2213 = !DILocation(line: 3602, column: 55, scope: !334)
!2214 = !DILocalVariable(name: "name", arg: 3, scope: !334, file: !1, line: 3602, type: !79)
!2215 = !DILocation(line: 3602, column: 71, scope: !334)
!2216 = !DILocalVariable(name: "mode", arg: 4, scope: !334, file: !1, line: 3603, type: !110)
!2217 = !DILocation(line: 3603, column: 12, scope: !334)
!2218 = !DILocalVariable(name: "set", arg: 5, scope: !334, file: !1, line: 3603, type: !46)
!2219 = !DILocation(line: 3603, column: 32, scope: !334)
!2220 = !DILocalVariable(name: "clear", arg: 6, scope: !334, file: !1, line: 3603, type: !46)
!2221 = !DILocation(line: 3603, column: 51, scope: !334)
!2222 = !DILocalVariable(name: "ret", scope: !334, file: !1, line: 3605, type: !22)
!2223 = !DILocation(line: 3605, column: 8, scope: !334)
!2224 = !DILocalVariable(name: "myfd", scope: !334, file: !1, line: 3606, type: !22)
!2225 = !DILocation(line: 3606, column: 8, scope: !334)
!2226 = !DILocation(line: 3606, column: 15, scope: !334)
!2227 = !DILocalVariable(name: "newflags", scope: !334, file: !1, line: 3607, type: !22)
!2228 = !DILocation(line: 3607, column: 6, scope: !334)
!2229 = !DILocalVariable(name: "oldflags", scope: !334, file: !1, line: 3607, type: !22)
!2230 = !DILocation(line: 3607, column: 16, scope: !334)
!2231 = !DILocalVariable(name: "sf_mask", scope: !334, file: !1, line: 3608, type: !22)
!2232 = !DILocation(line: 3608, column: 6, scope: !334)
!2233 = !DILocation(line: 3610, column: 6, scope: !2234)
!2234 = distinct !DILexicalBlock(scope: !334, file: !1, line: 3610, column: 6)
!2235 = !DILocation(line: 3610, column: 10, scope: !2234)
!2236 = !DILocation(line: 3610, column: 15, scope: !2234)
!2237 = !DILocation(line: 3610, column: 18, scope: !2238)
!2238 = !DILexicalBlockFile(scope: !2234, file: !1, discriminator: 1)
!2239 = !DILocation(line: 3610, column: 24, scope: !2238)
!2240 = !DILocation(line: 3610, column: 6, scope: !2238)
!2241 = !DILocation(line: 3611, column: 3, scope: !2234)
!2242 = !DILocation(line: 3613, column: 7, scope: !2243)
!2243 = distinct !DILexicalBlock(scope: !334, file: !1, line: 3613, column: 6)
!2244 = !DILocation(line: 3613, column: 21, scope: !2243)
!2245 = !DILocation(line: 3613, column: 25, scope: !2246)
!2246 = !DILexicalBlockFile(scope: !2243, file: !1, discriminator: 1)
!2247 = !DILocation(line: 3613, column: 6, scope: !2246)
!2248 = !DILocation(line: 3614, column: 3, scope: !2243)
!2249 = !DILocation(line: 3617, column: 6, scope: !2250)
!2250 = distinct !DILexicalBlock(scope: !334, file: !1, line: 3617, column: 6)
!2251 = !DILocation(line: 3617, column: 11, scope: !2250)
!2252 = !DILocation(line: 3617, column: 6, scope: !334)
!2253 = !DILocation(line: 3618, column: 15, scope: !2254)
!2254 = distinct !DILexicalBlock(scope: !2250, file: !1, line: 3617, column: 16)
!2255 = !DILocation(line: 3618, column: 10, scope: !2254)
!2256 = !DILocation(line: 3618, column: 8, scope: !2254)
!2257 = !DILocation(line: 3619, column: 33, scope: !2254)
!2258 = !DILocation(line: 3619, column: 3, scope: !2254)
!2259 = !DILocation(line: 3620, column: 2, scope: !2254)
!2260 = !DILocation(line: 3621, column: 6, scope: !2261)
!2261 = distinct !DILexicalBlock(scope: !334, file: !1, line: 3621, column: 6)
!2262 = !DILocation(line: 3621, column: 11, scope: !2261)
!2263 = !DILocation(line: 3621, column: 6, scope: !334)
!2264 = !DILocation(line: 3622, column: 3, scope: !2261)
!2265 = !DILocation(line: 3632, column: 10, scope: !334)
!2266 = !DILocation(line: 3637, column: 10, scope: !334)
!2267 = !DILocation(line: 3642, column: 10, scope: !334)
!2268 = !DILocation(line: 3648, column: 6, scope: !334)
!2269 = !DILocation(line: 3651, column: 12, scope: !2270)
!2270 = distinct !DILexicalBlock(scope: !334, file: !1, line: 3651, column: 6)
!2271 = !DILocation(line: 3651, column: 6, scope: !2270)
!2272 = !DILocation(line: 3657, column: 17, scope: !2270)
!2273 = !DILocation(line: 3651, column: 6, scope: !334)
!2274 = !DILocation(line: 3658, column: 3, scope: !2270)
!2275 = !DILocation(line: 3661, column: 14, scope: !334)
!2276 = !DILocation(line: 3661, column: 26, scope: !334)
!2277 = !DILocation(line: 3661, column: 25, scope: !334)
!2278 = !DILocation(line: 3661, column: 23, scope: !334)
!2279 = !DILocation(line: 3661, column: 35, scope: !334)
!2280 = !DILocation(line: 3661, column: 33, scope: !334)
!2281 = !DILocation(line: 3661, column: 13, scope: !334)
!2282 = !DILocation(line: 3661, column: 11, scope: !334)
!2283 = !DILocation(line: 3662, column: 12, scope: !2284)
!2284 = distinct !DILexicalBlock(scope: !334, file: !1, line: 3662, column: 6)
!2285 = !DILocation(line: 3662, column: 6, scope: !2284)
!2286 = !DILocation(line: 3668, column: 17, scope: !2284)
!2287 = !DILocation(line: 3662, column: 6, scope: !334)
!2288 = !DILocation(line: 3669, column: 3, scope: !2284)
!2289 = !DILocation(line: 3670, column: 6, scope: !2290)
!2290 = distinct !DILexicalBlock(scope: !334, file: !1, line: 3670, column: 6)
!2291 = !DILocation(line: 3670, column: 12, scope: !2290)
!2292 = !DILocation(line: 3670, column: 6, scope: !334)
!2293 = !DILocation(line: 3671, column: 3, scope: !2290)
!2294 = !DILocation(line: 3674, column: 15, scope: !334)
!2295 = !DILocation(line: 3674, column: 14, scope: !334)
!2296 = !DILocation(line: 3674, column: 11, scope: !334)
!2297 = !DILocation(line: 3675, column: 14, scope: !334)
!2298 = !DILocation(line: 3675, column: 11, scope: !334)
!2299 = !DILocation(line: 3676, column: 14, scope: !334)
!2300 = !DILocation(line: 3676, column: 11, scope: !334)
!2301 = !DILocation(line: 3677, column: 12, scope: !2302)
!2302 = distinct !DILexicalBlock(scope: !334, file: !1, line: 3677, column: 6)
!2303 = !DILocation(line: 3677, column: 6, scope: !2302)
!2304 = !DILocation(line: 3683, column: 17, scope: !2302)
!2305 = !DILocation(line: 3677, column: 6, scope: !334)
!2306 = !DILocation(line: 3684, column: 3, scope: !2302)
!2307 = !DILocation(line: 3683, column: 20, scope: !2308)
!2308 = !DILexicalBlockFile(scope: !2302, file: !1, discriminator: 1)
!2309 = !DILocation(line: 3688, column: 21, scope: !334)
!2310 = !DILocation(line: 3688, column: 24, scope: !334)
!2311 = !DILocation(line: 3688, column: 33, scope: !334)
!2312 = !DILocation(line: 3688, column: 2, scope: !2313)
!2313 = !DILexicalBlockFile(scope: !334, file: !1, discriminator: 1)
!2314 = !DILocation(line: 3690, column: 6, scope: !334)
!2315 = !DILocation(line: 3690, column: 2, scope: !334)
!2316 = !DILocation(line: 3692, column: 6, scope: !2317)
!2317 = distinct !DILexicalBlock(scope: !334, file: !1, line: 3692, column: 6)
!2318 = !DILocation(line: 3692, column: 9, scope: !2317)
!2319 = !DILocation(line: 3692, column: 6, scope: !334)
!2320 = !DILocation(line: 3693, column: 9, scope: !2317)
!2321 = !DILocation(line: 3693, column: 3, scope: !2317)
!2322 = !DILocation(line: 3694, column: 10, scope: !334)
!2323 = !DILocation(line: 3694, column: 2, scope: !334)
!2324 = !DILocation(line: 3695, column: 1, scope: !334)
!2325 = !DILocalVariable(name: "a", arg: 1, scope: !337, file: !1, line: 3721, type: !4)
!2326 = !DILocation(line: 3721, column: 45, scope: !337)
!2327 = !DILocalVariable(name: "pathname", arg: 2, scope: !337, file: !1, line: 3721, type: !79)
!2328 = !DILocation(line: 3721, column: 60, scope: !337)
!2329 = !DILocalVariable(name: "metadata", arg: 3, scope: !337, file: !1, line: 3722, type: !42)
!2330 = !DILocation(line: 3722, column: 16, scope: !337)
!2331 = !DILocalVariable(name: "metadata_size", arg: 4, scope: !337, file: !1, line: 3722, type: !44)
!2332 = !DILocation(line: 3722, column: 33, scope: !337)
!2333 = !DILocation(line: 3724, column: 8, scope: !337)
!2334 = !DILocation(line: 3725, column: 8, scope: !337)
!2335 = !DILocation(line: 3726, column: 8, scope: !337)
!2336 = !DILocation(line: 3727, column: 8, scope: !337)
!2337 = !DILocation(line: 3728, column: 2, scope: !337)
!2338 = !DILocalVariable(name: "fd", arg: 1, scope: !331, file: !1, line: 3113, type: !22)
!2339 = !DILocation(line: 3113, column: 14, scope: !331)
!2340 = !DILocalVariable(name: "mode", arg: 2, scope: !331, file: !1, line: 3113, type: !22)
!2341 = !DILocation(line: 3113, column: 22, scope: !331)
!2342 = !DILocalVariable(name: "name", arg: 3, scope: !331, file: !1, line: 3113, type: !79)
!2343 = !DILocation(line: 3113, column: 40, scope: !331)
!2344 = !DILocalVariable(name: "atime", arg: 4, scope: !331, file: !1, line: 3114, type: !172)
!2345 = !DILocation(line: 3114, column: 12, scope: !331)
!2346 = !DILocalVariable(name: "atime_nsec", arg: 5, scope: !331, file: !1, line: 3114, type: !41)
!2347 = !DILocation(line: 3114, column: 24, scope: !331)
!2348 = !DILocalVariable(name: "mtime", arg: 6, scope: !331, file: !1, line: 3115, type: !172)
!2349 = !DILocation(line: 3115, column: 12, scope: !331)
!2350 = !DILocalVariable(name: "mtime_nsec", arg: 7, scope: !331, file: !1, line: 3115, type: !41)
!2351 = !DILocation(line: 3115, column: 24, scope: !331)
!2352 = !DILocalVariable(name: "ts", scope: !331, file: !1, line: 3124, type: !2353)
!2353 = !DICompositeType(tag: DW_TAG_array_type, baseType: !212, size: 256, align: 64, elements: !2354)
!2354 = !{!2355}
!2355 = !DISubrange(count: 2)
!2356 = !DILocation(line: 3124, column: 18, scope: !331)
!2357 = !DILocation(line: 3125, column: 8, scope: !331)
!2358 = !DILocation(line: 3126, column: 17, scope: !331)
!2359 = !DILocation(line: 3126, column: 2, scope: !331)
!2360 = !DILocation(line: 3126, column: 8, scope: !331)
!2361 = !DILocation(line: 3126, column: 15, scope: !331)
!2362 = !DILocation(line: 3127, column: 18, scope: !331)
!2363 = !DILocation(line: 3127, column: 2, scope: !331)
!2364 = !DILocation(line: 3127, column: 8, scope: !331)
!2365 = !DILocation(line: 3127, column: 16, scope: !331)
!2366 = !DILocation(line: 3128, column: 17, scope: !331)
!2367 = !DILocation(line: 3128, column: 2, scope: !331)
!2368 = !DILocation(line: 3128, column: 8, scope: !331)
!2369 = !DILocation(line: 3128, column: 15, scope: !331)
!2370 = !DILocation(line: 3129, column: 18, scope: !331)
!2371 = !DILocation(line: 3129, column: 2, scope: !331)
!2372 = !DILocation(line: 3129, column: 8, scope: !331)
!2373 = !DILocation(line: 3129, column: 16, scope: !331)
!2374 = !DILocation(line: 3130, column: 6, scope: !2375)
!2375 = distinct !DILexicalBlock(scope: !331, file: !1, line: 3130, column: 6)
!2376 = !DILocation(line: 3130, column: 9, scope: !2375)
!2377 = !DILocation(line: 3130, column: 6, scope: !331)
!2378 = !DILocation(line: 3131, column: 19, scope: !2375)
!2379 = !DILocation(line: 3131, column: 23, scope: !2375)
!2380 = !DILocation(line: 3131, column: 10, scope: !2375)
!2381 = !DILocation(line: 3131, column: 3, scope: !2375)
!2382 = !DILocation(line: 3132, column: 29, scope: !331)
!2383 = !DILocation(line: 3132, column: 35, scope: !331)
!2384 = !DILocation(line: 3132, column: 9, scope: !331)
!2385 = !DILocation(line: 3132, column: 2, scope: !331)
!2386 = !DILocation(line: 3190, column: 1, scope: !331)
!2387 = !DILocalVariable(name: "a", arg: 1, scope: !343, file: !1, line: 2910, type: !4)
!2388 = !DILocation(line: 2910, column: 45, scope: !343)
!2389 = !DILocalVariable(name: "error_string", scope: !343, file: !1, line: 2912, type: !90)
!2390 = !DILocation(line: 2912, column: 24, scope: !343)
!2391 = !DILocalVariable(name: "error_number", scope: !343, file: !1, line: 2913, type: !22)
!2392 = !DILocation(line: 2913, column: 6, scope: !343)
!2393 = !DILocalVariable(name: "rc", scope: !343, file: !1, line: 2914, type: !22)
!2394 = !DILocation(line: 2914, column: 6, scope: !343)
!2395 = !DILocation(line: 2915, column: 2, scope: !343)
!2396 = !DILocation(line: 2915, column: 2, scope: !2397)
!2397 = !DILexicalBlockFile(scope: !2398, file: !1, discriminator: 1)
!2398 = distinct !DILexicalBlock(scope: !343, file: !1, line: 2915, column: 2)
!2399 = !DILocation(line: 2916, column: 30, scope: !343)
!2400 = !DILocation(line: 2916, column: 33, scope: !343)
!2401 = !DILocation(line: 2917, column: 6, scope: !343)
!2402 = !DILocation(line: 2917, column: 9, scope: !343)
!2403 = !DILocation(line: 2916, column: 7, scope: !343)
!2404 = !DILocation(line: 2916, column: 5, scope: !343)
!2405 = !DILocation(line: 2918, column: 6, scope: !2406)
!2406 = distinct !DILexicalBlock(scope: !343, file: !1, line: 2918, column: 6)
!2407 = !DILocation(line: 2918, column: 9, scope: !2406)
!2408 = !DILocation(line: 2918, column: 6, scope: !343)
!2409 = !DILocation(line: 2919, column: 22, scope: !2410)
!2410 = distinct !DILexicalBlock(scope: !2406, file: !1, line: 2918, column: 24)
!2411 = !DILocation(line: 2919, column: 25, scope: !2410)
!2412 = !DILocation(line: 2919, column: 34, scope: !2410)
!2413 = !DILocation(line: 2920, column: 20, scope: !2410)
!2414 = !DILocation(line: 2919, column: 3, scope: !2410)
!2415 = !DILocation(line: 2921, column: 2, scope: !2410)
!2416 = !DILocation(line: 2922, column: 2, scope: !343)
!2417 = !DILocation(line: 2923, column: 9, scope: !343)
!2418 = !DILocation(line: 2923, column: 2, scope: !343)
!2419 = !DILocalVariable(name: "a", arg: 1, scope: !354, file: !1, line: 2721, type: !4)
!2420 = !DILocation(line: 2721, column: 43, scope: !354)
!2421 = !DILocalVariable(name: "error_string", scope: !354, file: !1, line: 2723, type: !90)
!2422 = !DILocation(line: 2723, column: 24, scope: !354)
!2423 = !DILocalVariable(name: "error_number", scope: !354, file: !1, line: 2724, type: !22)
!2424 = !DILocation(line: 2724, column: 6, scope: !354)
!2425 = !DILocalVariable(name: "rc", scope: !354, file: !1, line: 2725, type: !22)
!2426 = !DILocation(line: 2725, column: 6, scope: !354)
!2427 = !DILocation(line: 2726, column: 2, scope: !354)
!2428 = !DILocation(line: 2726, column: 2, scope: !2429)
!2429 = !DILexicalBlockFile(scope: !2430, file: !1, discriminator: 1)
!2430 = distinct !DILexicalBlock(scope: !354, file: !1, line: 2726, column: 2)
!2431 = !DILocation(line: 2727, column: 28, scope: !354)
!2432 = !DILocation(line: 2727, column: 31, scope: !354)
!2433 = !DILocation(line: 2728, column: 6, scope: !354)
!2434 = !DILocation(line: 2728, column: 9, scope: !354)
!2435 = !DILocation(line: 2727, column: 7, scope: !354)
!2436 = !DILocation(line: 2727, column: 5, scope: !354)
!2437 = !DILocation(line: 2729, column: 6, scope: !2438)
!2438 = distinct !DILexicalBlock(scope: !354, file: !1, line: 2729, column: 6)
!2439 = !DILocation(line: 2729, column: 9, scope: !2438)
!2440 = !DILocation(line: 2729, column: 6, scope: !354)
!2441 = !DILocation(line: 2730, column: 22, scope: !2442)
!2442 = distinct !DILexicalBlock(scope: !2438, file: !1, line: 2729, column: 24)
!2443 = !DILocation(line: 2730, column: 25, scope: !2442)
!2444 = !DILocation(line: 2730, column: 34, scope: !2442)
!2445 = !DILocation(line: 2731, column: 20, scope: !2442)
!2446 = !DILocation(line: 2730, column: 3, scope: !2442)
!2447 = !DILocation(line: 2732, column: 2, scope: !2442)
!2448 = !DILocation(line: 2733, column: 2, scope: !354)
!2449 = !DILocation(line: 2734, column: 2, scope: !354)
!2450 = !DILocation(line: 2734, column: 5, scope: !354)
!2451 = !DILocation(line: 2734, column: 9, scope: !354)
!2452 = !DILocation(line: 2735, column: 9, scope: !354)
!2453 = !DILocation(line: 2735, column: 2, scope: !354)
!2454 = !DILocalVariable(name: "a", arg: 1, scope: !356, file: !1, line: 1844, type: !4)
!2455 = !DILocation(line: 1844, column: 50, scope: !356)
!2456 = !DILocalVariable(name: "ret", scope: !356, file: !1, line: 1846, type: !22)
!2457 = !DILocation(line: 1846, column: 6, scope: !356)
!2458 = !DILocalVariable(name: "tail", scope: !356, file: !1, line: 1847, type: !94)
!2459 = !DILocation(line: 1847, column: 8, scope: !356)
!2460 = !DILocation(line: 1847, column: 15, scope: !356)
!2461 = !DILocation(line: 1847, column: 18, scope: !356)
!2462 = !DILocation(line: 1850, column: 13, scope: !2463)
!2463 = distinct !DILexicalBlock(scope: !356, file: !1, line: 1850, column: 6)
!2464 = !DILocation(line: 1850, column: 6, scope: !2463)
!2465 = !DILocation(line: 1850, column: 19, scope: !2463)
!2466 = !DILocation(line: 1850, column: 6, scope: !356)
!2467 = !DILocation(line: 1851, column: 3, scope: !2463)
!2468 = !DILocation(line: 1854, column: 19, scope: !356)
!2469 = !DILocation(line: 1854, column: 2, scope: !356)
!2470 = !DILocation(line: 1854, column: 5, scope: !356)
!2471 = !DILocation(line: 1854, column: 17, scope: !356)
!2472 = !DILocation(line: 1855, column: 32, scope: !356)
!2473 = !DILocation(line: 1855, column: 35, scope: !356)
!2474 = !DILocation(line: 1855, column: 2, scope: !356)
!2475 = !DILocation(line: 1856, column: 6, scope: !2476)
!2476 = distinct !DILexicalBlock(scope: !356, file: !1, line: 1856, column: 6)
!2477 = !DILocation(line: 1856, column: 9, scope: !2476)
!2478 = !DILocation(line: 1856, column: 21, scope: !2476)
!2479 = !DILocation(line: 1856, column: 6, scope: !356)
!2480 = !DILocation(line: 1857, column: 3, scope: !2476)
!2481 = !DILocation(line: 1860, column: 2, scope: !356)
!2482 = !DILocation(line: 1860, column: 16, scope: !2483)
!2483 = !DILexicalBlockFile(scope: !356, file: !1, discriminator: 1)
!2484 = !DILocation(line: 1860, column: 9, scope: !2483)
!2485 = !DILocation(line: 1860, column: 22, scope: !2483)
!2486 = !DILocation(line: 1860, column: 2, scope: !2483)
!2487 = !DILocation(line: 1862, column: 8, scope: !2488)
!2488 = distinct !DILexicalBlock(scope: !356, file: !1, line: 1860, column: 35)
!2489 = !DILocation(line: 1863, column: 3, scope: !2488)
!2490 = !DILocation(line: 1863, column: 10, scope: !2491)
!2491 = !DILexicalBlockFile(scope: !2488, file: !1, discriminator: 1)
!2492 = !DILocation(line: 1863, column: 17, scope: !2491)
!2493 = !DILocation(line: 1863, column: 20, scope: !2491)
!2494 = !DILocation(line: 1863, column: 15, scope: !2491)
!2495 = !DILocation(line: 1863, column: 25, scope: !2491)
!2496 = !DILocation(line: 1863, column: 29, scope: !2497)
!2497 = !DILexicalBlockFile(scope: !2488, file: !1, discriminator: 2)
!2498 = !DILocation(line: 1863, column: 28, scope: !2497)
!2499 = !DILocation(line: 1863, column: 34, scope: !2497)
!2500 = !DILocation(line: 1863, column: 3, scope: !2501)
!2501 = !DILexicalBlockFile(scope: !2488, file: !1, discriminator: 3)
!2502 = !DILocation(line: 1864, column: 8, scope: !2488)
!2503 = !DILocation(line: 1863, column: 3, scope: !2504)
!2504 = !DILexicalBlockFile(scope: !2488, file: !1, discriminator: 4)
!2505 = !DILocation(line: 1866, column: 7, scope: !2506)
!2506 = distinct !DILexicalBlock(scope: !2488, file: !1, line: 1866, column: 7)
!2507 = !DILocation(line: 1866, column: 15, scope: !2506)
!2508 = !DILocation(line: 1866, column: 18, scope: !2506)
!2509 = !DILocation(line: 1866, column: 12, scope: !2506)
!2510 = !DILocation(line: 1866, column: 7, scope: !2488)
!2511 = !DILocation(line: 1867, column: 4, scope: !2506)
!2512 = !DILocation(line: 1869, column: 4, scope: !2488)
!2513 = !DILocation(line: 1869, column: 9, scope: !2488)
!2514 = !DILocation(line: 1870, column: 20, scope: !2488)
!2515 = !DILocation(line: 1870, column: 23, scope: !2488)
!2516 = !DILocation(line: 1870, column: 26, scope: !2488)
!2517 = !DILocation(line: 1870, column: 9, scope: !2488)
!2518 = !DILocation(line: 1870, column: 7, scope: !2488)
!2519 = !DILocation(line: 1871, column: 7, scope: !2520)
!2520 = distinct !DILexicalBlock(scope: !2488, file: !1, line: 1871, column: 7)
!2521 = !DILocation(line: 1871, column: 11, scope: !2520)
!2522 = !DILocation(line: 1871, column: 25, scope: !2520)
!2523 = !DILocation(line: 1871, column: 34, scope: !2524)
!2524 = !DILexicalBlockFile(scope: !2520, file: !1, discriminator: 1)
!2525 = !DILocation(line: 1871, column: 37, scope: !2524)
!2526 = !DILocation(line: 1871, column: 28, scope: !2524)
!2527 = !DILocation(line: 1871, column: 43, scope: !2524)
!2528 = !DILocation(line: 1871, column: 7, scope: !2524)
!2529 = !DILocation(line: 1872, column: 8, scope: !2520)
!2530 = !DILocation(line: 1872, column: 4, scope: !2520)
!2531 = !DILocation(line: 1873, column: 4, scope: !2488)
!2532 = !DILocation(line: 1873, column: 9, scope: !2488)
!2533 = !DILocation(line: 1874, column: 7, scope: !2534)
!2534 = distinct !DILexicalBlock(scope: !2488, file: !1, line: 1874, column: 7)
!2535 = !DILocation(line: 1874, column: 11, scope: !2534)
!2536 = !DILocation(line: 1874, column: 7, scope: !2488)
!2537 = !DILocation(line: 1875, column: 4, scope: !2534)
!2538 = !DILocation(line: 1876, column: 7, scope: !2488)
!2539 = !DILocation(line: 1878, column: 13, scope: !2488)
!2540 = !DILocation(line: 1878, column: 3, scope: !2488)
!2541 = !DILocation(line: 1878, column: 6, scope: !2488)
!2542 = !DILocation(line: 1878, column: 11, scope: !2488)
!2543 = !DILocation(line: 1860, column: 2, scope: !2544)
!2544 = !DILexicalBlockFile(scope: !356, file: !1, discriminator: 2)
!2545 = !DILocation(line: 1880, column: 2, scope: !356)
!2546 = !DILocation(line: 1881, column: 1, scope: !356)
!2547 = !DILocalVariable(name: "a", arg: 1, scope: !365, file: !1, line: 1888, type: !4)
!2548 = !DILocation(line: 1888, column: 42, scope: !365)
!2549 = !DILocalVariable(name: "ret", scope: !365, file: !1, line: 1890, type: !22)
!2550 = !DILocation(line: 1890, column: 6, scope: !365)
!2551 = !DILocalVariable(name: "en", scope: !365, file: !1, line: 1890, type: !22)
!2552 = !DILocation(line: 1890, column: 24, scope: !365)
!2553 = !DILocation(line: 1892, column: 6, scope: !2554)
!2554 = distinct !DILexicalBlock(scope: !365, file: !1, line: 1892, column: 6)
!2555 = !DILocation(line: 1892, column: 9, scope: !2554)
!2556 = !DILocation(line: 1892, column: 15, scope: !2554)
!2557 = !DILocation(line: 1892, column: 40, scope: !2554)
!2558 = !DILocation(line: 1892, column: 44, scope: !2559)
!2559 = !DILexicalBlockFile(scope: !2554, file: !1, discriminator: 1)
!2560 = !DILocation(line: 1892, column: 6, scope: !2559)
!2561 = !DILocation(line: 1901, column: 7, scope: !2562)
!2562 = distinct !DILexicalBlock(scope: !2563, file: !1, line: 1901, column: 7)
!2563 = distinct !DILexicalBlock(scope: !2554, file: !1, line: 1892, column: 62)
!2564 = !DILocation(line: 1901, column: 10, scope: !2562)
!2565 = !DILocation(line: 1901, column: 16, scope: !2562)
!2566 = !DILocation(line: 1901, column: 7, scope: !2563)
!2567 = !DILocation(line: 1902, column: 32, scope: !2562)
!2568 = !DILocation(line: 1902, column: 10, scope: !2562)
!2569 = !DILocation(line: 1902, column: 4, scope: !2562)
!2570 = !DILocation(line: 1903, column: 14, scope: !2571)
!2571 = distinct !DILexicalBlock(scope: !2563, file: !1, line: 1903, column: 7)
!2572 = !DILocation(line: 1903, column: 17, scope: !2571)
!2573 = !DILocation(line: 1903, column: 7, scope: !2571)
!2574 = !DILocation(line: 1903, column: 23, scope: !2571)
!2575 = !DILocation(line: 1903, column: 7, scope: !2563)
!2576 = !DILocation(line: 1905, column: 4, scope: !2577)
!2577 = distinct !DILexicalBlock(scope: !2571, file: !1, line: 1903, column: 29)
!2578 = !DILocation(line: 1905, column: 7, scope: !2577)
!2579 = !DILocation(line: 1905, column: 11, scope: !2577)
!2580 = !DILocation(line: 1906, column: 3, scope: !2577)
!2581 = !DILocation(line: 1906, column: 14, scope: !2582)
!2582 = !DILexicalBlockFile(scope: !2583, file: !1, discriminator: 1)
!2583 = distinct !DILexicalBlock(scope: !2571, file: !1, line: 1906, column: 14)
!2584 = !DILocation(line: 1906, column: 20, scope: !2582)
!2585 = !DILocation(line: 1908, column: 3, scope: !2586)
!2586 = distinct !DILexicalBlock(scope: !2583, file: !1, line: 1906, column: 31)
!2587 = !DILocation(line: 1908, column: 20, scope: !2588)
!2588 = !DILexicalBlockFile(scope: !2589, file: !1, discriminator: 1)
!2589 = distinct !DILexicalBlock(scope: !2583, file: !1, line: 1908, column: 14)
!2590 = !DILocation(line: 1908, column: 23, scope: !2588)
!2591 = !DILocation(line: 1908, column: 14, scope: !2588)
!2592 = !DILocation(line: 1908, column: 29, scope: !2588)
!2593 = !DILocation(line: 1910, column: 4, scope: !2594)
!2594 = distinct !DILexicalBlock(scope: !2589, file: !1, line: 1908, column: 35)
!2595 = !DILocation(line: 1910, column: 7, scope: !2594)
!2596 = !DILocation(line: 1910, column: 11, scope: !2594)
!2597 = !DILocation(line: 1911, column: 3, scope: !2594)
!2598 = !DILocation(line: 1913, column: 23, scope: !2599)
!2599 = distinct !DILexicalBlock(scope: !2589, file: !1, line: 1911, column: 10)
!2600 = !DILocation(line: 1913, column: 26, scope: !2599)
!2601 = !DILocation(line: 1913, column: 35, scope: !2599)
!2602 = !DILocation(line: 1913, column: 4, scope: !2603)
!2603 = !DILexicalBlockFile(scope: !2599, file: !1, discriminator: 1)
!2604 = !DILocation(line: 1915, column: 4, scope: !2599)
!2605 = !DILocation(line: 1917, column: 2, scope: !2563)
!2606 = !DILocation(line: 1920, column: 32, scope: !365)
!2607 = !DILocation(line: 1920, column: 7, scope: !365)
!2608 = !DILocation(line: 1920, column: 5, scope: !365)
!2609 = !DILocation(line: 1922, column: 7, scope: !2610)
!2610 = distinct !DILexicalBlock(scope: !365, file: !1, line: 1922, column: 6)
!2611 = !DILocation(line: 1922, column: 10, scope: !2610)
!2612 = !DILocation(line: 1922, column: 21, scope: !2610)
!2613 = !DILocation(line: 1922, column: 24, scope: !2614)
!2614 = !DILexicalBlockFile(scope: !2610, file: !1, discriminator: 1)
!2615 = !DILocation(line: 1922, column: 27, scope: !2614)
!2616 = !DILocation(line: 1923, column: 6, scope: !2610)
!2617 = !DILocation(line: 1923, column: 11, scope: !2614)
!2618 = !DILocation(line: 1923, column: 14, scope: !2614)
!2619 = !DILocation(line: 1923, column: 20, scope: !2614)
!2620 = !DILocation(line: 1922, column: 6, scope: !2621)
!2621 = !DILexicalBlockFile(scope: !365, file: !1, discriminator: 2)
!2622 = !DILocation(line: 1925, column: 21, scope: !2623)
!2623 = distinct !DILexicalBlock(scope: !2610, file: !1, line: 1923, column: 51)
!2624 = !DILocation(line: 1925, column: 24, scope: !2623)
!2625 = !DILocation(line: 1925, column: 27, scope: !2623)
!2626 = !DILocation(line: 1925, column: 3, scope: !2623)
!2627 = !DILocation(line: 1927, column: 33, scope: !2623)
!2628 = !DILocation(line: 1927, column: 8, scope: !2623)
!2629 = !DILocation(line: 1927, column: 6, scope: !2623)
!2630 = !DILocation(line: 1928, column: 2, scope: !2623)
!2631 = !DILocation(line: 1930, column: 7, scope: !2632)
!2632 = distinct !DILexicalBlock(scope: !365, file: !1, line: 1930, column: 6)
!2633 = !DILocation(line: 1930, column: 10, scope: !2632)
!2634 = !DILocation(line: 1930, column: 21, scope: !2632)
!2635 = !DILocation(line: 1930, column: 48, scope: !2636)
!2636 = !DILexicalBlockFile(scope: !2632, file: !1, discriminator: 1)
!2637 = !DILocation(line: 1930, column: 51, scope: !2636)
!2638 = !DILocation(line: 1930, column: 25, scope: !2636)
!2639 = !DILocation(line: 1930, column: 58, scope: !2636)
!2640 = !DILocation(line: 1930, column: 6, scope: !2636)
!2641 = !DILocation(line: 1931, column: 22, scope: !2642)
!2642 = distinct !DILexicalBlock(scope: !2632, file: !1, line: 1930, column: 68)
!2643 = !DILocation(line: 1931, column: 25, scope: !2642)
!2644 = !DILocation(line: 1931, column: 34, scope: !2642)
!2645 = !DILocation(line: 1933, column: 30, scope: !2642)
!2646 = !DILocation(line: 1933, column: 33, scope: !2642)
!2647 = !DILocation(line: 1933, column: 7, scope: !2642)
!2648 = !DILocation(line: 1931, column: 3, scope: !2642)
!2649 = !DILocation(line: 1934, column: 3, scope: !2642)
!2650 = !DILocation(line: 1937, column: 7, scope: !2651)
!2651 = distinct !DILexicalBlock(scope: !365, file: !1, line: 1937, column: 6)
!2652 = !DILocation(line: 1937, column: 10, scope: !2651)
!2653 = !DILocation(line: 1937, column: 20, scope: !2651)
!2654 = !DILocation(line: 1937, column: 23, scope: !2655)
!2655 = !DILexicalBlockFile(scope: !2651, file: !1, discriminator: 1)
!2656 = !DILocation(line: 1937, column: 26, scope: !2655)
!2657 = !DILocation(line: 1938, column: 6, scope: !2651)
!2658 = !DILocation(line: 1938, column: 10, scope: !2655)
!2659 = !DILocation(line: 1938, column: 13, scope: !2655)
!2660 = !DILocation(line: 1938, column: 19, scope: !2655)
!2661 = !DILocation(line: 1937, column: 6, scope: !2621)
!2662 = !DILocation(line: 1940, column: 28, scope: !2663)
!2663 = distinct !DILexicalBlock(scope: !2651, file: !1, line: 1938, column: 52)
!2664 = !DILocation(line: 1940, column: 31, scope: !2663)
!2665 = !DILocation(line: 1940, column: 3, scope: !2663)
!2666 = !DILocation(line: 1941, column: 3, scope: !2663)
!2667 = !DILocation(line: 1951, column: 6, scope: !2668)
!2668 = distinct !DILexicalBlock(scope: !365, file: !1, line: 1951, column: 6)
!2669 = !DILocation(line: 1951, column: 9, scope: !2668)
!2670 = !DILocation(line: 1951, column: 6, scope: !365)
!2671 = !DILocation(line: 1953, column: 13, scope: !2672)
!2672 = distinct !DILexicalBlock(scope: !2673, file: !1, line: 1953, column: 7)
!2673 = distinct !DILexicalBlock(scope: !2668, file: !1, line: 1951, column: 20)
!2674 = !DILocation(line: 1953, column: 16, scope: !2672)
!2675 = !DILocation(line: 1953, column: 7, scope: !2672)
!2676 = !DILocation(line: 1953, column: 22, scope: !2672)
!2677 = !DILocation(line: 1953, column: 7, scope: !2673)
!2678 = !DILocation(line: 1954, column: 23, scope: !2679)
!2679 = distinct !DILexicalBlock(scope: !2672, file: !1, line: 1953, column: 28)
!2680 = !DILocation(line: 1954, column: 26, scope: !2679)
!2681 = !DILocation(line: 1954, column: 35, scope: !2679)
!2682 = !DILocation(line: 1954, column: 4, scope: !2683)
!2683 = !DILexicalBlockFile(scope: !2679, file: !1, discriminator: 1)
!2684 = !DILocation(line: 1956, column: 4, scope: !2679)
!2685 = !DILocation(line: 1958, column: 3, scope: !2673)
!2686 = !DILocation(line: 1958, column: 6, scope: !2673)
!2687 = !DILocation(line: 1958, column: 10, scope: !2673)
!2688 = !DILocation(line: 1960, column: 33, scope: !2673)
!2689 = !DILocation(line: 1960, column: 8, scope: !2673)
!2690 = !DILocation(line: 1960, column: 6, scope: !2673)
!2691 = !DILocation(line: 1961, column: 2, scope: !2673)
!2692 = !DILocation(line: 1961, column: 13, scope: !2693)
!2693 = !DILexicalBlockFile(scope: !2694, file: !1, discriminator: 1)
!2694 = distinct !DILexicalBlock(scope: !2668, file: !1, line: 1961, column: 13)
!2695 = !DILocation(line: 1961, column: 16, scope: !2693)
!2696 = !DILocalVariable(name: "r", scope: !2697, file: !1, line: 1966, type: !22)
!2697 = distinct !DILexicalBlock(scope: !2694, file: !1, line: 1961, column: 27)
!2698 = !DILocation(line: 1966, column: 7, scope: !2697)
!2699 = !DILocation(line: 1972, column: 7, scope: !2700)
!2700 = distinct !DILexicalBlock(scope: !2697, file: !1, line: 1972, column: 7)
!2701 = !DILocation(line: 1972, column: 7, scope: !2697)
!2702 = !DILocation(line: 1973, column: 13, scope: !2700)
!2703 = !DILocation(line: 1973, column: 16, scope: !2700)
!2704 = !DILocation(line: 1973, column: 23, scope: !2700)
!2705 = !DILocation(line: 1973, column: 26, scope: !2700)
!2706 = !DILocation(line: 1973, column: 8, scope: !2700)
!2707 = !DILocation(line: 1973, column: 6, scope: !2700)
!2708 = !DILocation(line: 1973, column: 4, scope: !2700)
!2709 = !DILocation(line: 1978, column: 7, scope: !2710)
!2710 = distinct !DILexicalBlock(scope: !2697, file: !1, line: 1978, column: 7)
!2711 = !DILocation(line: 1978, column: 9, scope: !2710)
!2712 = !DILocation(line: 1978, column: 14, scope: !2710)
!2713 = !DILocation(line: 1978, column: 18, scope: !2714)
!2714 = !DILexicalBlockFile(scope: !2710, file: !1, discriminator: 1)
!2715 = !DILocation(line: 1978, column: 7, scope: !2714)
!2716 = !DILocation(line: 1979, column: 14, scope: !2710)
!2717 = !DILocation(line: 1979, column: 17, scope: !2710)
!2718 = !DILocation(line: 1979, column: 24, scope: !2710)
!2719 = !DILocation(line: 1979, column: 27, scope: !2710)
!2720 = !DILocation(line: 1979, column: 8, scope: !2710)
!2721 = !DILocation(line: 1979, column: 6, scope: !2710)
!2722 = !DILocation(line: 1979, column: 4, scope: !2710)
!2723 = !DILocation(line: 1980, column: 7, scope: !2724)
!2724 = distinct !DILexicalBlock(scope: !2697, file: !1, line: 1980, column: 7)
!2725 = !DILocation(line: 1980, column: 9, scope: !2724)
!2726 = !DILocation(line: 1980, column: 7, scope: !2697)
!2727 = !DILocation(line: 1981, column: 23, scope: !2728)
!2728 = distinct !DILexicalBlock(scope: !2724, file: !1, line: 1980, column: 15)
!2729 = !DILocation(line: 1981, column: 26, scope: !2728)
!2730 = !DILocation(line: 1981, column: 35, scope: !2728)
!2731 = !DILocation(line: 1981, column: 4, scope: !2732)
!2732 = !DILexicalBlockFile(scope: !2728, file: !1, discriminator: 1)
!2733 = !DILocation(line: 1983, column: 4, scope: !2728)
!2734 = !DILocation(line: 1989, column: 8, scope: !2735)
!2735 = distinct !DILexicalBlock(scope: !2697, file: !1, line: 1989, column: 7)
!2736 = !DILocation(line: 1989, column: 11, scope: !2735)
!2737 = !DILocation(line: 1989, column: 17, scope: !2735)
!2738 = !DILocation(line: 1990, column: 7, scope: !2735)
!2739 = !DILocation(line: 1990, column: 12, scope: !2740)
!2740 = !DILexicalBlockFile(scope: !2735, file: !1, discriminator: 1)
!2741 = !DILocation(line: 1989, column: 7, scope: !2742)
!2742 = !DILexicalBlockFile(scope: !2697, file: !1, discriminator: 1)
!2743 = !DILocation(line: 1991, column: 17, scope: !2744)
!2744 = distinct !DILexicalBlock(scope: !2745, file: !1, line: 1991, column: 8)
!2745 = distinct !DILexicalBlock(scope: !2735, file: !1, line: 1990, column: 36)
!2746 = !DILocation(line: 1991, column: 20, scope: !2744)
!2747 = !DILocation(line: 1991, column: 25, scope: !2744)
!2748 = !DILocation(line: 1991, column: 28, scope: !2744)
!2749 = !DILocation(line: 1991, column: 9, scope: !2744)
!2750 = !DILocation(line: 1991, column: 8, scope: !2745)
!2751 = !DILocation(line: 1992, column: 30, scope: !2752)
!2752 = distinct !DILexicalBlock(scope: !2744, file: !1, line: 1991, column: 36)
!2753 = !DILocation(line: 1992, column: 33, scope: !2752)
!2754 = !DILocation(line: 1992, column: 5, scope: !2752)
!2755 = !DILocation(line: 1993, column: 5, scope: !2752)
!2756 = !DILocation(line: 1995, column: 3, scope: !2745)
!2757 = !DILocation(line: 1998, column: 7, scope: !2758)
!2758 = distinct !DILexicalBlock(scope: !2697, file: !1, line: 1998, column: 7)
!2759 = !DILocation(line: 1998, column: 10, scope: !2758)
!2760 = !DILocation(line: 1998, column: 24, scope: !2758)
!2761 = !DILocation(line: 1999, column: 7, scope: !2758)
!2762 = !DILocation(line: 1999, column: 10, scope: !2758)
!2763 = !DILocation(line: 1999, column: 13, scope: !2758)
!2764 = !DILocation(line: 1999, column: 30, scope: !2758)
!2765 = !DILocation(line: 1999, column: 33, scope: !2758)
!2766 = !DILocation(line: 1999, column: 20, scope: !2758)
!2767 = !DILocation(line: 1999, column: 47, scope: !2758)
!2768 = !DILocation(line: 2000, column: 7, scope: !2758)
!2769 = !DILocation(line: 2000, column: 10, scope: !2758)
!2770 = !DILocation(line: 2000, column: 13, scope: !2758)
!2771 = !DILocation(line: 2000, column: 30, scope: !2758)
!2772 = !DILocation(line: 2000, column: 33, scope: !2758)
!2773 = !DILocation(line: 2000, column: 20, scope: !2758)
!2774 = !DILocation(line: 1998, column: 7, scope: !2742)
!2775 = !DILocation(line: 2001, column: 23, scope: !2776)
!2776 = distinct !DILexicalBlock(scope: !2758, file: !1, line: 2000, column: 48)
!2777 = !DILocation(line: 2001, column: 26, scope: !2776)
!2778 = !DILocation(line: 2001, column: 4, scope: !2776)
!2779 = !DILocation(line: 2003, column: 4, scope: !2776)
!2780 = !DILocation(line: 2006, column: 8, scope: !2781)
!2781 = distinct !DILexicalBlock(scope: !2697, file: !1, line: 2006, column: 7)
!2782 = !DILocation(line: 2006, column: 7, scope: !2697)
!2783 = !DILocation(line: 2008, column: 8, scope: !2784)
!2784 = distinct !DILexicalBlock(scope: !2785, file: !1, line: 2008, column: 8)
!2785 = distinct !DILexicalBlock(scope: !2781, file: !1, line: 2006, column: 32)
!2786 = !DILocation(line: 2008, column: 11, scope: !2784)
!2787 = !DILocation(line: 2008, column: 17, scope: !2784)
!2788 = !DILocation(line: 2008, column: 8, scope: !2785)
!2789 = !DILocation(line: 2009, column: 33, scope: !2784)
!2790 = !DILocation(line: 2009, column: 11, scope: !2784)
!2791 = !DILocation(line: 2009, column: 5, scope: !2784)
!2792 = !DILocation(line: 2010, column: 15, scope: !2793)
!2793 = distinct !DILexicalBlock(scope: !2785, file: !1, line: 2010, column: 8)
!2794 = !DILocation(line: 2010, column: 18, scope: !2793)
!2795 = !DILocation(line: 2010, column: 8, scope: !2793)
!2796 = !DILocation(line: 2010, column: 24, scope: !2793)
!2797 = !DILocation(line: 2010, column: 8, scope: !2785)
!2798 = !DILocation(line: 2011, column: 24, scope: !2799)
!2799 = distinct !DILexicalBlock(scope: !2793, file: !1, line: 2010, column: 30)
!2800 = !DILocation(line: 2011, column: 27, scope: !2799)
!2801 = !DILocation(line: 2011, column: 36, scope: !2799)
!2802 = !DILocation(line: 2011, column: 5, scope: !2803)
!2803 = !DILexicalBlockFile(scope: !2799, file: !1, discriminator: 1)
!2804 = !DILocation(line: 2013, column: 5, scope: !2799)
!2805 = !DILocation(line: 2015, column: 4, scope: !2785)
!2806 = !DILocation(line: 2015, column: 7, scope: !2785)
!2807 = !DILocation(line: 2015, column: 11, scope: !2785)
!2808 = !DILocation(line: 2017, column: 34, scope: !2785)
!2809 = !DILocation(line: 2017, column: 9, scope: !2785)
!2810 = !DILocation(line: 2017, column: 7, scope: !2785)
!2811 = !DILocation(line: 2018, column: 3, scope: !2785)
!2812 = !DILocation(line: 2018, column: 15, scope: !2813)
!2813 = !DILexicalBlockFile(scope: !2814, file: !1, discriminator: 1)
!2814 = distinct !DILexicalBlock(scope: !2781, file: !1, line: 2018, column: 14)
!2815 = !DILocation(line: 2018, column: 14, scope: !2813)
!2816 = !DILocation(line: 2020, column: 8, scope: !2817)
!2817 = distinct !DILexicalBlock(scope: !2818, file: !1, line: 2020, column: 8)
!2818 = distinct !DILexicalBlock(scope: !2814, file: !1, line: 2018, column: 33)
!2819 = !DILocation(line: 2020, column: 11, scope: !2817)
!2820 = !DILocation(line: 2020, column: 17, scope: !2817)
!2821 = !DILocation(line: 2020, column: 8, scope: !2818)
!2822 = !DILocation(line: 2021, column: 33, scope: !2817)
!2823 = !DILocation(line: 2021, column: 11, scope: !2817)
!2824 = !DILocation(line: 2021, column: 5, scope: !2817)
!2825 = !DILocation(line: 2022, column: 14, scope: !2826)
!2826 = distinct !DILexicalBlock(scope: !2818, file: !1, line: 2022, column: 8)
!2827 = !DILocation(line: 2022, column: 17, scope: !2826)
!2828 = !DILocation(line: 2022, column: 8, scope: !2826)
!2829 = !DILocation(line: 2022, column: 23, scope: !2826)
!2830 = !DILocation(line: 2022, column: 8, scope: !2818)
!2831 = !DILocation(line: 2023, column: 24, scope: !2832)
!2832 = distinct !DILexicalBlock(scope: !2826, file: !1, line: 2022, column: 29)
!2833 = !DILocation(line: 2023, column: 27, scope: !2832)
!2834 = !DILocation(line: 2023, column: 36, scope: !2832)
!2835 = !DILocation(line: 2023, column: 5, scope: !2836)
!2836 = !DILexicalBlockFile(scope: !2832, file: !1, discriminator: 1)
!2837 = !DILocation(line: 2025, column: 5, scope: !2832)
!2838 = !DILocation(line: 2028, column: 34, scope: !2818)
!2839 = !DILocation(line: 2028, column: 9, scope: !2818)
!2840 = !DILocation(line: 2028, column: 7, scope: !2818)
!2841 = !DILocation(line: 2029, column: 3, scope: !2818)
!2842 = !DILocation(line: 2037, column: 9, scope: !2843)
!2843 = distinct !DILexicalBlock(scope: !2844, file: !1, line: 2037, column: 8)
!2844 = distinct !DILexicalBlock(scope: !2814, file: !1, line: 2029, column: 10)
!2845 = !DILocation(line: 2037, column: 12, scope: !2843)
!2846 = !DILocation(line: 2037, column: 20, scope: !2843)
!2847 = !DILocation(line: 2037, column: 23, scope: !2843)
!2848 = !DILocation(line: 2037, column: 26, scope: !2843)
!2849 = !DILocation(line: 2037, column: 17, scope: !2843)
!2850 = !DILocation(line: 2038, column: 8, scope: !2843)
!2851 = !DILocation(line: 2038, column: 12, scope: !2852)
!2852 = !DILexicalBlockFile(scope: !2843, file: !1, discriminator: 1)
!2853 = !DILocation(line: 2038, column: 15, scope: !2852)
!2854 = !DILocation(line: 2038, column: 20, scope: !2852)
!2855 = !DILocation(line: 2037, column: 8, scope: !2856)
!2856 = !DILexicalBlockFile(scope: !2844, file: !1, discriminator: 1)
!2857 = !DILocation(line: 2039, column: 21, scope: !2843)
!2858 = !DILocation(line: 2039, column: 24, scope: !2843)
!2859 = !DILocation(line: 2039, column: 29, scope: !2843)
!2860 = !DILocation(line: 2039, column: 5, scope: !2843)
!2861 = !DILocation(line: 2039, column: 8, scope: !2843)
!2862 = !DILocation(line: 2039, column: 17, scope: !2843)
!2863 = !DILocation(line: 2041, column: 7, scope: !2844)
!2864 = !DILocation(line: 2043, column: 2, scope: !2697)
!2865 = !DILocation(line: 2045, column: 6, scope: !2866)
!2866 = distinct !DILexicalBlock(scope: !365, file: !1, line: 2045, column: 6)
!2867 = !DILocation(line: 2045, column: 6, scope: !365)
!2868 = !DILocation(line: 2047, column: 9, scope: !2869)
!2869 = distinct !DILexicalBlock(scope: !2870, file: !1, line: 2047, column: 7)
!2870 = distinct !DILexicalBlock(scope: !2866, file: !1, line: 2045, column: 10)
!2871 = !DILocation(line: 2047, column: 12, scope: !2869)
!2872 = !DILocation(line: 2047, column: 22, scope: !2869)
!2873 = !DILocation(line: 2047, column: 28, scope: !2869)
!2874 = !DILocation(line: 2047, column: 7, scope: !2870)
!2875 = !DILocation(line: 2048, column: 23, scope: !2869)
!2876 = !DILocation(line: 2048, column: 26, scope: !2869)
!2877 = !DILocation(line: 2048, column: 35, scope: !2869)
!2878 = !DILocation(line: 2049, column: 8, scope: !2869)
!2879 = !DILocation(line: 2049, column: 11, scope: !2869)
!2880 = !DILocation(line: 2048, column: 4, scope: !2869)
!2881 = !DILocation(line: 2050, column: 3, scope: !2870)
!2882 = !DILocation(line: 2053, column: 2, scope: !365)
!2883 = !DILocation(line: 2053, column: 5, scope: !365)
!2884 = !DILocation(line: 2053, column: 9, scope: !365)
!2885 = !DILocation(line: 2054, column: 10, scope: !365)
!2886 = !DILocation(line: 2054, column: 2, scope: !365)
!2887 = !DILocation(line: 2055, column: 1, scope: !365)
!2888 = !DILocalVariable(name: "a", arg: 1, scope: !372, file: !1, line: 2455, type: !4)
!2889 = !DILocation(line: 2455, column: 42, scope: !372)
!2890 = !DILocalVariable(name: "pathname", arg: 2, scope: !372, file: !1, line: 2455, type: !79)
!2891 = !DILocation(line: 2455, column: 57, scope: !372)
!2892 = !DILocation(line: 2457, column: 6, scope: !2893)
!2893 = distinct !DILexicalBlock(scope: !372, file: !1, line: 2457, column: 6)
!2894 = !DILocation(line: 2457, column: 9, scope: !2893)
!2895 = !DILocation(line: 2457, column: 23, scope: !2893)
!2896 = !DILocation(line: 2457, column: 6, scope: !372)
!2897 = !DILocation(line: 2458, column: 32, scope: !2893)
!2898 = !DILocation(line: 2458, column: 35, scope: !2893)
!2899 = !DILocation(line: 2458, column: 22, scope: !2893)
!2900 = !DILocation(line: 2458, column: 3, scope: !2893)
!2901 = !DILocation(line: 2458, column: 6, scope: !2893)
!2902 = !DILocation(line: 2458, column: 20, scope: !2893)
!2903 = !DILocation(line: 2459, column: 10, scope: !372)
!2904 = !DILocation(line: 2459, column: 13, scope: !372)
!2905 = !DILocation(line: 2459, column: 2, scope: !372)
!2906 = !DILocalVariable(name: "path", arg: 1, scope: !346, file: !1, line: 2812, type: !94)
!2907 = !DILocation(line: 2812, column: 30, scope: !346)
!2908 = !DILocalVariable(name: "a_eno", arg: 2, scope: !346, file: !1, line: 2812, type: !349)
!2909 = !DILocation(line: 2812, column: 41, scope: !346)
!2910 = !DILocalVariable(name: "a_estr", arg: 3, scope: !346, file: !1, line: 2812, type: !350)
!2911 = !DILocation(line: 2812, column: 71, scope: !346)
!2912 = !DILocalVariable(name: "flags", arg: 4, scope: !346, file: !1, line: 2813, type: !22)
!2913 = !DILocation(line: 2813, column: 9, scope: !346)
!2914 = !DILocalVariable(name: "dest", scope: !346, file: !1, line: 2815, type: !94)
!2915 = !DILocation(line: 2815, column: 8, scope: !346)
!2916 = !DILocalVariable(name: "src", scope: !346, file: !1, line: 2815, type: !94)
!2917 = !DILocation(line: 2815, column: 15, scope: !346)
!2918 = !DILocalVariable(name: "separator", scope: !346, file: !1, line: 2816, type: !81)
!2919 = !DILocation(line: 2816, column: 7, scope: !346)
!2920 = !DILocation(line: 2818, column: 15, scope: !346)
!2921 = !DILocation(line: 2818, column: 13, scope: !346)
!2922 = !DILocation(line: 2818, column: 7, scope: !346)
!2923 = !DILocation(line: 2819, column: 7, scope: !2924)
!2924 = distinct !DILexicalBlock(scope: !346, file: !1, line: 2819, column: 6)
!2925 = !DILocation(line: 2819, column: 6, scope: !2924)
!2926 = !DILocation(line: 2819, column: 11, scope: !2924)
!2927 = !DILocation(line: 2819, column: 6, scope: !346)
!2928 = !DILocation(line: 2820, column: 15, scope: !2929)
!2929 = distinct !DILexicalBlock(scope: !2924, file: !1, line: 2819, column: 20)
!2930 = !DILocation(line: 2820, column: 22, scope: !2929)
!2931 = !DILocation(line: 2820, column: 3, scope: !2929)
!2932 = !DILocation(line: 2822, column: 3, scope: !2929)
!2933 = !DILocation(line: 2829, column: 7, scope: !2934)
!2934 = distinct !DILexicalBlock(scope: !346, file: !1, line: 2829, column: 6)
!2935 = !DILocation(line: 2829, column: 6, scope: !2934)
!2936 = !DILocation(line: 2829, column: 11, scope: !2934)
!2937 = !DILocation(line: 2829, column: 6, scope: !346)
!2938 = !DILocation(line: 2830, column: 7, scope: !2939)
!2939 = distinct !DILexicalBlock(scope: !2940, file: !1, line: 2830, column: 7)
!2940 = distinct !DILexicalBlock(scope: !2934, file: !1, line: 2829, column: 19)
!2941 = !DILocation(line: 2830, column: 13, scope: !2939)
!2942 = !DILocation(line: 2830, column: 7, scope: !2940)
!2943 = !DILocation(line: 2831, column: 16, scope: !2944)
!2944 = distinct !DILexicalBlock(scope: !2939, file: !1, line: 2830, column: 55)
!2945 = !DILocation(line: 2831, column: 23, scope: !2944)
!2946 = !DILocation(line: 2831, column: 4, scope: !2944)
!2947 = !DILocation(line: 2833, column: 4, scope: !2944)
!2948 = !DILocation(line: 2836, column: 19, scope: !2940)
!2949 = !DILocation(line: 2836, column: 15, scope: !2940)
!2950 = !DILocation(line: 2836, column: 13, scope: !2940)
!2951 = !DILocation(line: 2837, column: 2, scope: !2940)
!2952 = !DILocation(line: 2840, column: 2, scope: !346)
!2953 = !DILocation(line: 2842, column: 7, scope: !2954)
!2954 = distinct !DILexicalBlock(scope: !2955, file: !1, line: 2842, column: 7)
!2955 = distinct !DILexicalBlock(scope: !2956, file: !1, line: 2840, column: 11)
!2956 = distinct !DILexicalBlock(scope: !2957, file: !1, line: 2840, column: 2)
!2957 = distinct !DILexicalBlock(scope: !346, file: !1, line: 2840, column: 2)
!2958 = !DILocation(line: 2842, column: 14, scope: !2954)
!2959 = !DILocation(line: 2842, column: 7, scope: !2955)
!2960 = !DILocation(line: 2843, column: 4, scope: !2961)
!2961 = distinct !DILexicalBlock(scope: !2954, file: !1, line: 2842, column: 23)
!2962 = !DILocation(line: 2844, column: 14, scope: !2963)
!2963 = distinct !DILexicalBlock(scope: !2954, file: !1, line: 2844, column: 14)
!2964 = !DILocation(line: 2844, column: 21, scope: !2963)
!2965 = !DILocation(line: 2844, column: 14, scope: !2954)
!2966 = !DILocation(line: 2846, column: 7, scope: !2967)
!2967 = distinct !DILexicalBlock(scope: !2963, file: !1, line: 2844, column: 29)
!2968 = !DILocation(line: 2847, column: 4, scope: !2967)
!2969 = !DILocation(line: 2848, column: 14, scope: !2970)
!2970 = distinct !DILexicalBlock(scope: !2963, file: !1, line: 2848, column: 14)
!2971 = !DILocation(line: 2848, column: 21, scope: !2970)
!2972 = !DILocation(line: 2848, column: 14, scope: !2963)
!2973 = !DILocation(line: 2849, column: 8, scope: !2974)
!2974 = distinct !DILexicalBlock(scope: !2975, file: !1, line: 2849, column: 8)
!2975 = distinct !DILexicalBlock(scope: !2970, file: !1, line: 2848, column: 29)
!2976 = !DILocation(line: 2849, column: 15, scope: !2974)
!2977 = !DILocation(line: 2849, column: 8, scope: !2975)
!2978 = !DILocation(line: 2851, column: 5, scope: !2979)
!2979 = distinct !DILexicalBlock(scope: !2974, file: !1, line: 2849, column: 24)
!2980 = !DILocation(line: 2852, column: 15, scope: !2981)
!2981 = distinct !DILexicalBlock(scope: !2974, file: !1, line: 2852, column: 15)
!2982 = !DILocation(line: 2852, column: 22, scope: !2981)
!2983 = !DILocation(line: 2852, column: 15, scope: !2974)
!2984 = !DILocation(line: 2854, column: 9, scope: !2985)
!2985 = distinct !DILexicalBlock(scope: !2981, file: !1, line: 2852, column: 30)
!2986 = !DILocation(line: 2855, column: 5, scope: !2985)
!2987 = !DILocation(line: 2856, column: 15, scope: !2988)
!2988 = distinct !DILexicalBlock(scope: !2981, file: !1, line: 2856, column: 15)
!2989 = !DILocation(line: 2856, column: 22, scope: !2988)
!2990 = !DILocation(line: 2856, column: 15, scope: !2981)
!2991 = !DILocation(line: 2857, column: 9, scope: !2992)
!2992 = distinct !DILexicalBlock(scope: !2993, file: !1, line: 2857, column: 9)
!2993 = distinct !DILexicalBlock(scope: !2988, file: !1, line: 2856, column: 30)
!2994 = !DILocation(line: 2857, column: 16, scope: !2992)
!2995 = !DILocation(line: 2857, column: 23, scope: !2992)
!2996 = !DILocation(line: 2857, column: 26, scope: !2997)
!2997 = !DILexicalBlockFile(scope: !2992, file: !1, discriminator: 1)
!2998 = !DILocation(line: 2857, column: 33, scope: !2997)
!2999 = !DILocation(line: 2857, column: 9, scope: !2997)
!3000 = !DILocation(line: 2859, column: 10, scope: !3001)
!3001 = distinct !DILexicalBlock(scope: !3002, file: !1, line: 2859, column: 10)
!3002 = distinct !DILexicalBlock(scope: !2992, file: !1, line: 2857, column: 42)
!3003 = !DILocation(line: 2860, column: 10, scope: !3001)
!3004 = !DILocation(line: 2859, column: 10, scope: !3002)
!3005 = !DILocation(line: 2861, column: 19, scope: !3006)
!3006 = distinct !DILexicalBlock(scope: !3001, file: !1, line: 2860, column: 45)
!3007 = !DILocation(line: 2861, column: 26, scope: !3006)
!3008 = !DILocation(line: 2861, column: 7, scope: !3006)
!3009 = !DILocation(line: 2864, column: 7, scope: !3006)
!3010 = !DILocation(line: 2866, column: 5, scope: !3002)
!3011 = !DILocation(line: 2874, column: 4, scope: !2993)
!3012 = !DILocation(line: 2875, column: 3, scope: !2975)
!3013 = !DILocation(line: 2878, column: 7, scope: !3014)
!3014 = distinct !DILexicalBlock(scope: !2955, file: !1, line: 2878, column: 7)
!3015 = !DILocation(line: 2878, column: 7, scope: !2955)
!3016 = !DILocation(line: 2879, column: 9, scope: !3014)
!3017 = !DILocation(line: 2879, column: 12, scope: !3014)
!3018 = !DILocation(line: 2879, column: 4, scope: !3014)
!3019 = !DILocation(line: 2880, column: 3, scope: !2955)
!3020 = !DILocation(line: 2880, column: 11, scope: !3021)
!3021 = !DILexicalBlockFile(scope: !2955, file: !1, discriminator: 1)
!3022 = !DILocation(line: 2880, column: 10, scope: !3021)
!3023 = !DILocation(line: 2880, column: 15, scope: !3021)
!3024 = !DILocation(line: 2880, column: 23, scope: !3021)
!3025 = !DILocation(line: 2880, column: 27, scope: !3026)
!3026 = !DILexicalBlockFile(scope: !2955, file: !1, discriminator: 2)
!3027 = !DILocation(line: 2880, column: 26, scope: !3026)
!3028 = !DILocation(line: 2880, column: 31, scope: !3026)
!3029 = !DILocation(line: 2880, column: 3, scope: !3030)
!3030 = !DILexicalBlockFile(scope: !2955, file: !1, discriminator: 3)
!3031 = !DILocation(line: 2881, column: 18, scope: !3032)
!3032 = distinct !DILexicalBlock(scope: !2955, file: !1, line: 2880, column: 39)
!3033 = !DILocation(line: 2881, column: 14, scope: !3032)
!3034 = !DILocation(line: 2881, column: 9, scope: !3032)
!3035 = !DILocation(line: 2881, column: 12, scope: !3032)
!3036 = !DILocation(line: 2880, column: 3, scope: !3037)
!3037 = !DILexicalBlockFile(scope: !2955, file: !1, discriminator: 4)
!3038 = !DILocation(line: 2884, column: 8, scope: !3039)
!3039 = distinct !DILexicalBlock(scope: !2955, file: !1, line: 2884, column: 7)
!3040 = !DILocation(line: 2884, column: 7, scope: !3039)
!3041 = !DILocation(line: 2884, column: 12, scope: !3039)
!3042 = !DILocation(line: 2884, column: 7, scope: !2955)
!3043 = !DILocation(line: 2885, column: 4, scope: !3039)
!3044 = !DILocation(line: 2888, column: 19, scope: !2955)
!3045 = !DILocation(line: 2888, column: 15, scope: !2955)
!3046 = !DILocation(line: 2888, column: 13, scope: !2955)
!3047 = !DILocation(line: 2840, column: 2, scope: !3048)
!3048 = !DILexicalBlockFile(scope: !2956, file: !1, discriminator: 1)
!3049 = !DILocation(line: 2894, column: 6, scope: !3050)
!3050 = distinct !DILexicalBlock(scope: !346, file: !1, line: 2894, column: 6)
!3051 = !DILocation(line: 2894, column: 14, scope: !3050)
!3052 = !DILocation(line: 2894, column: 11, scope: !3050)
!3053 = !DILocation(line: 2894, column: 6, scope: !346)
!3054 = !DILocation(line: 2899, column: 7, scope: !3055)
!3055 = distinct !DILexicalBlock(scope: !3056, file: !1, line: 2899, column: 7)
!3056 = distinct !DILexicalBlock(scope: !3050, file: !1, line: 2894, column: 20)
!3057 = !DILocation(line: 2899, column: 7, scope: !3056)
!3058 = !DILocation(line: 2900, column: 9, scope: !3055)
!3059 = !DILocation(line: 2900, column: 12, scope: !3055)
!3060 = !DILocation(line: 2900, column: 4, scope: !3055)
!3061 = !DILocation(line: 2902, column: 9, scope: !3055)
!3062 = !DILocation(line: 2902, column: 12, scope: !3055)
!3063 = !DILocation(line: 2903, column: 2, scope: !3056)
!3064 = !DILocation(line: 2905, column: 3, scope: !346)
!3065 = !DILocation(line: 2905, column: 8, scope: !346)
!3066 = !DILocation(line: 2906, column: 2, scope: !346)
!3067 = !DILocation(line: 2907, column: 1, scope: !346)
!3068 = !DILocalVariable(name: "a_eno", arg: 1, scope: !351, file: !1, line: 2464, type: !349)
!3069 = !DILocation(line: 2464, column: 18, scope: !351)
!3070 = !DILocalVariable(name: "a_estr", arg: 2, scope: !351, file: !1, line: 2464, type: !350)
!3071 = !DILocation(line: 2464, column: 48, scope: !351)
!3072 = !DILocalVariable(name: "err", arg: 3, scope: !351, file: !1, line: 2465, type: !22)
!3073 = !DILocation(line: 2465, column: 9, scope: !351)
!3074 = !DILocalVariable(name: "errstr", arg: 4, scope: !351, file: !1, line: 2465, type: !79)
!3075 = !DILocation(line: 2465, column: 26, scope: !351)
!3076 = !DILocalVariable(name: "path", arg: 5, scope: !351, file: !1, line: 2465, type: !79)
!3077 = !DILocation(line: 2465, column: 46, scope: !351)
!3078 = !DILocation(line: 2467, column: 6, scope: !3079)
!3079 = distinct !DILexicalBlock(scope: !351, file: !1, line: 2467, column: 6)
!3080 = !DILocation(line: 2467, column: 6, scope: !351)
!3081 = !DILocation(line: 2468, column: 12, scope: !3079)
!3082 = !DILocation(line: 2468, column: 4, scope: !3079)
!3083 = !DILocation(line: 2468, column: 10, scope: !3079)
!3084 = !DILocation(line: 2468, column: 3, scope: !3079)
!3085 = !DILocation(line: 2469, column: 6, scope: !3086)
!3086 = distinct !DILexicalBlock(scope: !351, file: !1, line: 2469, column: 6)
!3087 = !DILocation(line: 2469, column: 6, scope: !351)
!3088 = !DILocation(line: 2470, column: 26, scope: !3086)
!3089 = !DILocation(line: 2470, column: 34, scope: !3086)
!3090 = !DILocation(line: 2470, column: 42, scope: !3086)
!3091 = !DILocation(line: 2470, column: 3, scope: !3086)
!3092 = !DILocation(line: 2471, column: 1, scope: !351)
!3093 = !DILocalVariable(name: "path", arg: 1, scope: !355, file: !1, line: 2485, type: !94)
!3094 = !DILocation(line: 2485, column: 28, scope: !355)
!3095 = !DILocalVariable(name: "a_eno", arg: 2, scope: !355, file: !1, line: 2485, type: !349)
!3096 = !DILocation(line: 2485, column: 39, scope: !355)
!3097 = !DILocalVariable(name: "a_estr", arg: 3, scope: !355, file: !1, line: 2485, type: !350)
!3098 = !DILocation(line: 2485, column: 69, scope: !355)
!3099 = !DILocalVariable(name: "flags", arg: 4, scope: !355, file: !1, line: 2486, type: !22)
!3100 = !DILocation(line: 2486, column: 9, scope: !355)
!3101 = !DILocalVariable(name: "res", scope: !355, file: !1, line: 2496, type: !22)
!3102 = !DILocation(line: 2496, column: 6, scope: !355)
!3103 = !DILocalVariable(name: "tail", scope: !355, file: !1, line: 2497, type: !94)
!3104 = !DILocation(line: 2497, column: 8, scope: !355)
!3105 = !DILocalVariable(name: "head", scope: !355, file: !1, line: 2498, type: !94)
!3106 = !DILocation(line: 2498, column: 8, scope: !355)
!3107 = !DILocalVariable(name: "last", scope: !355, file: !1, line: 2499, type: !22)
!3108 = !DILocation(line: 2499, column: 6, scope: !355)
!3109 = !DILocalVariable(name: "c", scope: !355, file: !1, line: 2500, type: !81)
!3110 = !DILocation(line: 2500, column: 7, scope: !355)
!3111 = !DILocalVariable(name: "r", scope: !355, file: !1, line: 2501, type: !22)
!3112 = !DILocation(line: 2501, column: 6, scope: !355)
!3113 = !DILocalVariable(name: "st", scope: !355, file: !1, line: 2502, type: !189)
!3114 = !DILocation(line: 2502, column: 14, scope: !355)
!3115 = !DILocalVariable(name: "restore_pwd", scope: !355, file: !1, line: 2503, type: !22)
!3116 = !DILocation(line: 2503, column: 6, scope: !355)
!3117 = !DILocation(line: 2506, column: 5, scope: !3118)
!3118 = distinct !DILexicalBlock(scope: !355, file: !1, line: 2506, column: 5)
!3119 = !DILocation(line: 2506, column: 13, scope: !3118)
!3120 = !DILocation(line: 2506, column: 5, scope: !355)
!3121 = !DILocation(line: 2507, column: 6, scope: !3118)
!3122 = !DILocation(line: 2524, column: 16, scope: !355)
!3123 = !DILocation(line: 2524, column: 14, scope: !355)
!3124 = !DILocation(line: 2525, column: 32, scope: !355)
!3125 = !DILocation(line: 2525, column: 2, scope: !355)
!3126 = !DILocation(line: 2526, column: 6, scope: !3127)
!3127 = distinct !DILexicalBlock(scope: !355, file: !1, line: 2526, column: 6)
!3128 = !DILocation(line: 2526, column: 18, scope: !3127)
!3129 = !DILocation(line: 2526, column: 6, scope: !355)
!3130 = !DILocation(line: 2527, column: 3, scope: !3127)
!3131 = !DILocation(line: 2528, column: 9, scope: !355)
!3132 = !DILocation(line: 2528, column: 7, scope: !355)
!3133 = !DILocation(line: 2529, column: 9, scope: !355)
!3134 = !DILocation(line: 2529, column: 7, scope: !355)
!3135 = !DILocation(line: 2530, column: 7, scope: !355)
!3136 = !DILocation(line: 2533, column: 5, scope: !3137)
!3137 = distinct !DILexicalBlock(scope: !355, file: !1, line: 2533, column: 5)
!3138 = !DILocation(line: 2533, column: 13, scope: !3137)
!3139 = !DILocation(line: 2533, column: 10, scope: !3137)
!3140 = !DILocation(line: 2533, column: 18, scope: !3137)
!3141 = !DILocation(line: 2533, column: 21, scope: !3142)
!3142 = !DILexicalBlockFile(scope: !3137, file: !1, discriminator: 1)
!3143 = !DILocation(line: 2533, column: 29, scope: !3142)
!3144 = !DILocation(line: 2533, column: 5, scope: !3142)
!3145 = !DILocation(line: 2534, column: 3, scope: !3137)
!3146 = !DILocation(line: 2541, column: 2, scope: !355)
!3147 = !DILocation(line: 2541, column: 10, scope: !3148)
!3148 = !DILexicalBlockFile(scope: !355, file: !1, discriminator: 1)
!3149 = !DILocation(line: 2541, column: 9, scope: !3148)
!3150 = !DILocation(line: 2541, column: 2, scope: !3148)
!3151 = !DILocation(line: 2545, column: 3, scope: !3152)
!3152 = distinct !DILexicalBlock(scope: !355, file: !1, line: 2541, column: 16)
!3153 = !DILocation(line: 2545, column: 11, scope: !3154)
!3154 = !DILexicalBlockFile(scope: !3152, file: !1, discriminator: 1)
!3155 = !DILocation(line: 2545, column: 10, scope: !3154)
!3156 = !DILocation(line: 2545, column: 16, scope: !3154)
!3157 = !DILocation(line: 2545, column: 3, scope: !3154)
!3158 = !DILocation(line: 2546, column: 7, scope: !3152)
!3159 = !DILocation(line: 2545, column: 3, scope: !3160)
!3160 = !DILexicalBlockFile(scope: !3152, file: !1, discriminator: 2)
!3161 = !DILocation(line: 2548, column: 3, scope: !3152)
!3162 = !DILocation(line: 2548, column: 11, scope: !3154)
!3163 = !DILocation(line: 2548, column: 10, scope: !3154)
!3164 = !DILocation(line: 2548, column: 16, scope: !3154)
!3165 = !DILocation(line: 2548, column: 24, scope: !3154)
!3166 = !DILocation(line: 2548, column: 28, scope: !3160)
!3167 = !DILocation(line: 2548, column: 27, scope: !3160)
!3168 = !DILocation(line: 2548, column: 33, scope: !3160)
!3169 = !DILocation(line: 2548, column: 3, scope: !3170)
!3170 = !DILexicalBlockFile(scope: !3152, file: !1, discriminator: 3)
!3171 = !DILocation(line: 2549, column: 4, scope: !3152)
!3172 = !DILocation(line: 2548, column: 3, scope: !3173)
!3173 = !DILexicalBlockFile(scope: !3152, file: !1, discriminator: 4)
!3174 = !DILocation(line: 2551, column: 11, scope: !3152)
!3175 = !DILocation(line: 2551, column: 19, scope: !3152)
!3176 = !DILocation(line: 2551, column: 28, scope: !3152)
!3177 = !DILocation(line: 2551, column: 32, scope: !3154)
!3178 = !DILocation(line: 2551, column: 40, scope: !3154)
!3179 = !DILocation(line: 2551, column: 47, scope: !3154)
!3180 = !DILocation(line: 2551, column: 50, scope: !3160)
!3181 = !DILocation(line: 2551, column: 58, scope: !3160)
!3182 = !DILocation(line: 2551, column: 28, scope: !3170)
!3183 = !DILocation(line: 2551, column: 28, scope: !3173)
!3184 = !DILocation(line: 2551, column: 8, scope: !3173)
!3185 = !DILocation(line: 2553, column: 7, scope: !3152)
!3186 = !DILocation(line: 2553, column: 5, scope: !3152)
!3187 = !DILocation(line: 2554, column: 3, scope: !3152)
!3188 = !DILocation(line: 2554, column: 11, scope: !3152)
!3189 = !DILocation(line: 2556, column: 13, scope: !3152)
!3190 = !DILocation(line: 2556, column: 7, scope: !3152)
!3191 = !DILocation(line: 2556, column: 5, scope: !3152)
!3192 = !DILocation(line: 2557, column: 7, scope: !3193)
!3193 = distinct !DILexicalBlock(scope: !3152, file: !1, line: 2557, column: 7)
!3194 = !DILocation(line: 2557, column: 9, scope: !3193)
!3195 = !DILocation(line: 2557, column: 7, scope: !3152)
!3196 = !DILocation(line: 2558, column: 14, scope: !3197)
!3197 = distinct !DILexicalBlock(scope: !3193, file: !1, line: 2557, column: 15)
!3198 = !DILocation(line: 2558, column: 4, scope: !3197)
!3199 = !DILocation(line: 2558, column: 12, scope: !3197)
!3200 = !DILocation(line: 2560, column: 8, scope: !3201)
!3201 = distinct !DILexicalBlock(scope: !3197, file: !1, line: 2560, column: 8)
!3202 = !DILocation(line: 2560, column: 14, scope: !3201)
!3203 = !DILocation(line: 2560, column: 8, scope: !3197)
!3204 = !DILocation(line: 2561, column: 5, scope: !3205)
!3205 = distinct !DILexicalBlock(scope: !3201, file: !1, line: 2560, column: 25)
!3206 = !DILocation(line: 2575, column: 17, scope: !3207)
!3207 = distinct !DILexicalBlock(scope: !3201, file: !1, line: 2562, column: 11)
!3208 = !DILocation(line: 2575, column: 24, scope: !3207)
!3209 = !DILocation(line: 2575, column: 32, scope: !3207)
!3210 = !DILocation(line: 2576, column: 30, scope: !3207)
!3211 = !DILocation(line: 2575, column: 5, scope: !3212)
!3212 = !DILexicalBlockFile(scope: !3207, file: !1, discriminator: 1)
!3213 = !DILocation(line: 2577, column: 9, scope: !3207)
!3214 = !DILocation(line: 2578, column: 5, scope: !3207)
!3215 = !DILocation(line: 2580, column: 14, scope: !3216)
!3216 = distinct !DILexicalBlock(scope: !3193, file: !1, line: 2580, column: 14)
!3217 = !DILocation(line: 2580, column: 14, scope: !3193)
!3218 = !DILocation(line: 2581, column: 9, scope: !3219)
!3219 = distinct !DILexicalBlock(scope: !3220, file: !1, line: 2581, column: 8)
!3220 = distinct !DILexicalBlock(scope: !3216, file: !1, line: 2580, column: 35)
!3221 = !DILocation(line: 2581, column: 8, scope: !3220)
!3222 = !DILocation(line: 2582, column: 15, scope: !3223)
!3223 = distinct !DILexicalBlock(scope: !3224, file: !1, line: 2582, column: 9)
!3224 = distinct !DILexicalBlock(scope: !3219, file: !1, line: 2581, column: 15)
!3225 = !DILocation(line: 2582, column: 9, scope: !3223)
!3226 = !DILocation(line: 2582, column: 21, scope: !3223)
!3227 = !DILocation(line: 2582, column: 9, scope: !3224)
!3228 = !DILocation(line: 2583, column: 16, scope: !3229)
!3229 = distinct !DILexicalBlock(scope: !3223, file: !1, line: 2582, column: 27)
!3230 = !DILocation(line: 2583, column: 6, scope: !3229)
!3231 = !DILocation(line: 2583, column: 14, scope: !3229)
!3232 = !DILocation(line: 2584, column: 18, scope: !3229)
!3233 = !DILocation(line: 2584, column: 25, scope: !3229)
!3234 = !DILocation(line: 2584, column: 33, scope: !3229)
!3235 = !DILocation(line: 2585, column: 32, scope: !3229)
!3236 = !DILocation(line: 2584, column: 6, scope: !3237)
!3237 = !DILexicalBlockFile(scope: !3229, file: !1, discriminator: 1)
!3238 = !DILocation(line: 2586, column: 10, scope: !3229)
!3239 = !DILocation(line: 2587, column: 6, scope: !3229)
!3240 = !DILocation(line: 2590, column: 12, scope: !3224)
!3241 = !DILocation(line: 2590, column: 17, scope: !3224)
!3242 = !DILocation(line: 2590, column: 10, scope: !3224)
!3243 = !DILocation(line: 2591, column: 4, scope: !3224)
!3244 = !DILocation(line: 2592, column: 3, scope: !3220)
!3245 = !DILocation(line: 2592, column: 14, scope: !3246)
!3246 = !DILexicalBlockFile(scope: !3247, file: !1, discriminator: 1)
!3247 = distinct !DILexicalBlock(scope: !3216, file: !1, line: 2592, column: 14)
!3248 = !DILocation(line: 2593, column: 8, scope: !3249)
!3249 = distinct !DILexicalBlock(scope: !3250, file: !1, line: 2593, column: 8)
!3250 = distinct !DILexicalBlock(scope: !3247, file: !1, line: 2592, column: 35)
!3251 = !DILocation(line: 2593, column: 8, scope: !3250)
!3252 = !DILocation(line: 2599, column: 16, scope: !3253)
!3253 = distinct !DILexicalBlock(scope: !3254, file: !1, line: 2599, column: 9)
!3254 = distinct !DILexicalBlock(scope: !3249, file: !1, line: 2593, column: 14)
!3255 = !DILocation(line: 2599, column: 9, scope: !3253)
!3256 = !DILocation(line: 2599, column: 9, scope: !3254)
!3257 = !DILocation(line: 2600, column: 16, scope: !3258)
!3258 = distinct !DILexicalBlock(scope: !3253, file: !1, line: 2599, column: 23)
!3259 = !DILocation(line: 2600, column: 6, scope: !3258)
!3260 = !DILocation(line: 2600, column: 14, scope: !3258)
!3261 = !DILocation(line: 2601, column: 18, scope: !3258)
!3262 = !DILocation(line: 2601, column: 25, scope: !3258)
!3263 = !DILocation(line: 2601, column: 33, scope: !3258)
!3264 = !DILocation(line: 2603, column: 10, scope: !3258)
!3265 = !DILocation(line: 2601, column: 6, scope: !3266)
!3266 = !DILexicalBlockFile(scope: !3258, file: !1, discriminator: 1)
!3267 = !DILocation(line: 2604, column: 10, scope: !3258)
!3268 = !DILocation(line: 2605, column: 6, scope: !3258)
!3269 = !DILocation(line: 2613, column: 15, scope: !3254)
!3270 = !DILocation(line: 2613, column: 5, scope: !3254)
!3271 = !DILocation(line: 2613, column: 13, scope: !3254)
!3272 = !DILocation(line: 2625, column: 9, scope: !3254)
!3273 = !DILocation(line: 2626, column: 5, scope: !3254)
!3274 = !DILocation(line: 2627, column: 15, scope: !3275)
!3275 = distinct !DILexicalBlock(scope: !3249, file: !1, line: 2627, column: 15)
!3276 = !DILocation(line: 2627, column: 21, scope: !3275)
!3277 = !DILocation(line: 2627, column: 15, scope: !3249)
!3278 = !DILocation(line: 2629, column: 16, scope: !3279)
!3279 = distinct !DILexicalBlock(scope: !3280, file: !1, line: 2629, column: 9)
!3280 = distinct !DILexicalBlock(scope: !3275, file: !1, line: 2627, column: 47)
!3281 = !DILocation(line: 2629, column: 9, scope: !3279)
!3282 = !DILocation(line: 2629, column: 22, scope: !3279)
!3283 = !DILocation(line: 2629, column: 9, scope: !3280)
!3284 = !DILocation(line: 2630, column: 16, scope: !3285)
!3285 = distinct !DILexicalBlock(scope: !3279, file: !1, line: 2629, column: 28)
!3286 = !DILocation(line: 2630, column: 6, scope: !3285)
!3287 = !DILocation(line: 2630, column: 14, scope: !3285)
!3288 = !DILocation(line: 2631, column: 18, scope: !3285)
!3289 = !DILocation(line: 2631, column: 25, scope: !3285)
!3290 = !DILocation(line: 2633, column: 24, scope: !3285)
!3291 = !DILocation(line: 2631, column: 6, scope: !3285)
!3292 = !DILocation(line: 2634, column: 10, scope: !3285)
!3293 = !DILocation(line: 2635, column: 6, scope: !3285)
!3294 = !DILocation(line: 2637, column: 15, scope: !3280)
!3295 = !DILocation(line: 2637, column: 5, scope: !3280)
!3296 = !DILocation(line: 2637, column: 13, scope: !3280)
!3297 = !DILocation(line: 2638, column: 4, scope: !3280)
!3298 = !DILocation(line: 2638, column: 16, scope: !3299)
!3299 = !DILexicalBlockFile(scope: !3300, file: !1, discriminator: 1)
!3300 = distinct !DILexicalBlock(scope: !3275, file: !1, line: 2638, column: 15)
!3301 = !DILocation(line: 2638, column: 22, scope: !3299)
!3302 = !DILocation(line: 2639, column: 41, scope: !3300)
!3303 = !DILocation(line: 2638, column: 15, scope: !3299)
!3304 = !DILocation(line: 2647, column: 14, scope: !3305)
!3305 = distinct !DILexicalBlock(scope: !3300, file: !1, line: 2639, column: 47)
!3306 = !DILocation(line: 2647, column: 9, scope: !3305)
!3307 = !DILocation(line: 2647, column: 7, scope: !3305)
!3308 = !DILocation(line: 2648, column: 9, scope: !3309)
!3309 = distinct !DILexicalBlock(scope: !3305, file: !1, line: 2648, column: 9)
!3310 = !DILocation(line: 2648, column: 11, scope: !3309)
!3311 = !DILocation(line: 2648, column: 9, scope: !3305)
!3312 = !DILocation(line: 2649, column: 16, scope: !3313)
!3313 = distinct !DILexicalBlock(scope: !3309, file: !1, line: 2648, column: 17)
!3314 = !DILocation(line: 2649, column: 6, scope: !3313)
!3315 = !DILocation(line: 2649, column: 14, scope: !3313)
!3316 = !DILocation(line: 2650, column: 10, scope: !3317)
!3317 = distinct !DILexicalBlock(scope: !3313, file: !1, line: 2650, column: 10)
!3318 = !DILocation(line: 2650, column: 16, scope: !3317)
!3319 = !DILocation(line: 2650, column: 10, scope: !3313)
!3320 = !DILocation(line: 2651, column: 7, scope: !3321)
!3321 = distinct !DILexicalBlock(scope: !3317, file: !1, line: 2650, column: 27)
!3322 = !DILocation(line: 2653, column: 19, scope: !3323)
!3323 = distinct !DILexicalBlock(scope: !3317, file: !1, line: 2652, column: 13)
!3324 = !DILocation(line: 2653, column: 26, scope: !3323)
!3325 = !DILocation(line: 2654, column: 11, scope: !3323)
!3326 = !DILocation(line: 2655, column: 32, scope: !3323)
!3327 = !DILocation(line: 2653, column: 7, scope: !3323)
!3328 = !DILocation(line: 2656, column: 11, scope: !3323)
!3329 = !DILocation(line: 2657, column: 7, scope: !3323)
!3330 = !DILocation(line: 2659, column: 16, scope: !3331)
!3331 = distinct !DILexicalBlock(scope: !3309, file: !1, line: 2659, column: 16)
!3332 = !DILocation(line: 2659, column: 16, scope: !3309)
!3333 = !DILocation(line: 2660, column: 16, scope: !3334)
!3334 = distinct !DILexicalBlock(scope: !3335, file: !1, line: 2660, column: 10)
!3335 = distinct !DILexicalBlock(scope: !3331, file: !1, line: 2659, column: 37)
!3336 = !DILocation(line: 2660, column: 10, scope: !3334)
!3337 = !DILocation(line: 2660, column: 22, scope: !3334)
!3338 = !DILocation(line: 2660, column: 10, scope: !3335)
!3339 = !DILocation(line: 2661, column: 17, scope: !3340)
!3340 = distinct !DILexicalBlock(scope: !3334, file: !1, line: 2660, column: 28)
!3341 = !DILocation(line: 2661, column: 7, scope: !3340)
!3342 = !DILocation(line: 2661, column: 15, scope: !3340)
!3343 = !DILocation(line: 2662, column: 19, scope: !3340)
!3344 = !DILocation(line: 2662, column: 26, scope: !3340)
!3345 = !DILocation(line: 2663, column: 11, scope: !3340)
!3346 = !DILocation(line: 2664, column: 33, scope: !3340)
!3347 = !DILocation(line: 2662, column: 7, scope: !3340)
!3348 = !DILocation(line: 2665, column: 11, scope: !3340)
!3349 = !DILocation(line: 2666, column: 7, scope: !3340)
!3350 = !DILocation(line: 2672, column: 13, scope: !3335)
!3351 = !DILocation(line: 2672, column: 18, scope: !3335)
!3352 = !DILocation(line: 2672, column: 11, scope: !3335)
!3353 = !DILocation(line: 2673, column: 5, scope: !3335)
!3354 = !DILocation(line: 2674, column: 16, scope: !3355)
!3355 = distinct !DILexicalBlock(scope: !3331, file: !1, line: 2673, column: 12)
!3356 = !DILocation(line: 2674, column: 6, scope: !3355)
!3357 = !DILocation(line: 2674, column: 14, scope: !3355)
!3358 = !DILocation(line: 2675, column: 18, scope: !3355)
!3359 = !DILocation(line: 2675, column: 25, scope: !3355)
!3360 = !DILocation(line: 2677, column: 24, scope: !3355)
!3361 = !DILocation(line: 2675, column: 6, scope: !3355)
!3362 = !DILocation(line: 2678, column: 10, scope: !3355)
!3363 = !DILocation(line: 2679, column: 6, scope: !3355)
!3364 = !DILocation(line: 2681, column: 4, scope: !3305)
!3365 = !DILocation(line: 2682, column: 15, scope: !3366)
!3366 = distinct !DILexicalBlock(scope: !3300, file: !1, line: 2681, column: 11)
!3367 = !DILocation(line: 2682, column: 5, scope: !3366)
!3368 = !DILocation(line: 2682, column: 13, scope: !3366)
!3369 = !DILocation(line: 2683, column: 17, scope: !3366)
!3370 = !DILocation(line: 2683, column: 24, scope: !3366)
!3371 = !DILocation(line: 2684, column: 46, scope: !3366)
!3372 = !DILocation(line: 2683, column: 5, scope: !3366)
!3373 = !DILocation(line: 2685, column: 9, scope: !3366)
!3374 = !DILocation(line: 2686, column: 5, scope: !3366)
!3375 = !DILocation(line: 2688, column: 3, scope: !3250)
!3376 = !DILocation(line: 2690, column: 13, scope: !3152)
!3377 = !DILocation(line: 2690, column: 3, scope: !3152)
!3378 = !DILocation(line: 2690, column: 11, scope: !3152)
!3379 = !DILocation(line: 2691, column: 7, scope: !3380)
!3380 = distinct !DILexicalBlock(scope: !3152, file: !1, line: 2691, column: 7)
!3381 = !DILocation(line: 2691, column: 15, scope: !3380)
!3382 = !DILocation(line: 2691, column: 7, scope: !3152)
!3383 = !DILocation(line: 2692, column: 8, scope: !3380)
!3384 = !DILocation(line: 2692, column: 4, scope: !3380)
!3385 = !DILocation(line: 2541, column: 2, scope: !3386)
!3386 = !DILexicalBlockFile(scope: !355, file: !1, discriminator: 2)
!3387 = !DILocation(line: 2695, column: 12, scope: !355)
!3388 = !DILocation(line: 2695, column: 2, scope: !355)
!3389 = !DILocation(line: 2695, column: 10, scope: !355)
!3390 = !DILocation(line: 2698, column: 6, scope: !3391)
!3391 = distinct !DILexicalBlock(scope: !355, file: !1, line: 2698, column: 6)
!3392 = !DILocation(line: 2698, column: 18, scope: !3391)
!3393 = !DILocation(line: 2698, column: 6, scope: !355)
!3394 = !DILocation(line: 2699, column: 14, scope: !3395)
!3395 = distinct !DILexicalBlock(scope: !3391, file: !1, line: 2698, column: 24)
!3396 = !DILocation(line: 2699, column: 7, scope: !3395)
!3397 = !DILocation(line: 2699, column: 5, scope: !3395)
!3398 = !DILocation(line: 2700, column: 7, scope: !3399)
!3399 = distinct !DILexicalBlock(scope: !3395, file: !1, line: 2700, column: 7)
!3400 = !DILocation(line: 2700, column: 9, scope: !3399)
!3401 = !DILocation(line: 2700, column: 7, scope: !3395)
!3402 = !DILocation(line: 2701, column: 16, scope: !3403)
!3403 = distinct !DILexicalBlock(scope: !3399, file: !1, line: 2700, column: 15)
!3404 = !DILocation(line: 2701, column: 23, scope: !3403)
!3405 = !DILocation(line: 2701, column: 31, scope: !3403)
!3406 = !DILocation(line: 2701, column: 4, scope: !3407)
!3407 = !DILexicalBlockFile(scope: !3403, file: !1, discriminator: 1)
!3408 = !DILocation(line: 2703, column: 3, scope: !3403)
!3409 = !DILocation(line: 2704, column: 9, scope: !3395)
!3410 = !DILocation(line: 2704, column: 3, scope: !3395)
!3411 = !DILocation(line: 2705, column: 15, scope: !3395)
!3412 = !DILocation(line: 2706, column: 7, scope: !3413)
!3413 = distinct !DILexicalBlock(scope: !3395, file: !1, line: 2706, column: 7)
!3414 = !DILocation(line: 2706, column: 9, scope: !3413)
!3415 = !DILocation(line: 2706, column: 7, scope: !3395)
!3416 = !DILocation(line: 2707, column: 8, scope: !3417)
!3417 = distinct !DILexicalBlock(scope: !3413, file: !1, line: 2706, column: 15)
!3418 = !DILocation(line: 2708, column: 3, scope: !3417)
!3419 = !DILocation(line: 2709, column: 2, scope: !3395)
!3420 = !DILocation(line: 2712, column: 9, scope: !355)
!3421 = !DILocation(line: 2712, column: 2, scope: !355)
!3422 = !DILocation(line: 2714, column: 1, scope: !355)
!3423 = !DILocalVariable(name: "a", arg: 1, scope: !359, file: !1, line: 2954, type: !4)
!3424 = !DILocation(line: 2954, column: 39, scope: !359)
!3425 = !DILocalVariable(name: "path", arg: 2, scope: !359, file: !1, line: 2954, type: !94)
!3426 = !DILocation(line: 2954, column: 48, scope: !359)
!3427 = !DILocalVariable(name: "st", scope: !359, file: !1, line: 2956, type: !189)
!3428 = !DILocation(line: 2956, column: 14, scope: !359)
!3429 = !DILocalVariable(name: "le", scope: !359, file: !1, line: 2957, type: !113)
!3430 = !DILocation(line: 2957, column: 22, scope: !359)
!3431 = !DILocalVariable(name: "slash", scope: !359, file: !1, line: 2958, type: !94)
!3432 = !DILocation(line: 2958, column: 8, scope: !359)
!3433 = !DILocalVariable(name: "base", scope: !359, file: !1, line: 2958, type: !94)
!3434 = !DILocation(line: 2958, column: 16, scope: !359)
!3435 = !DILocalVariable(name: "mode_final", scope: !359, file: !1, line: 2959, type: !110)
!3436 = !DILocation(line: 2959, column: 9, scope: !359)
!3437 = !DILocalVariable(name: "mode", scope: !359, file: !1, line: 2959, type: !110)
!3438 = !DILocation(line: 2959, column: 21, scope: !359)
!3439 = !DILocalVariable(name: "r", scope: !359, file: !1, line: 2960, type: !22)
!3440 = !DILocation(line: 2960, column: 6, scope: !359)
!3441 = !DILocation(line: 2963, column: 18, scope: !359)
!3442 = !DILocation(line: 2963, column: 10, scope: !359)
!3443 = !DILocation(line: 2963, column: 8, scope: !359)
!3444 = !DILocation(line: 2964, column: 6, scope: !3445)
!3445 = distinct !DILexicalBlock(scope: !359, file: !1, line: 2964, column: 6)
!3446 = !DILocation(line: 2964, column: 12, scope: !3445)
!3447 = !DILocation(line: 2964, column: 6, scope: !359)
!3448 = !DILocation(line: 2965, column: 10, scope: !3445)
!3449 = !DILocation(line: 2965, column: 8, scope: !3445)
!3450 = !DILocation(line: 2965, column: 3, scope: !3445)
!3451 = !DILocation(line: 2967, column: 10, scope: !3445)
!3452 = !DILocation(line: 2967, column: 16, scope: !3445)
!3453 = !DILocation(line: 2967, column: 8, scope: !3445)
!3454 = !DILocation(line: 2969, column: 6, scope: !3455)
!3455 = distinct !DILexicalBlock(scope: !359, file: !1, line: 2969, column: 6)
!3456 = !DILocation(line: 2969, column: 14, scope: !3455)
!3457 = !DILocation(line: 2969, column: 22, scope: !3455)
!3458 = !DILocation(line: 2970, column: 7, scope: !3455)
!3459 = !DILocation(line: 2970, column: 15, scope: !3455)
!3460 = !DILocation(line: 2970, column: 22, scope: !3455)
!3461 = !DILocation(line: 2970, column: 25, scope: !3462)
!3462 = !DILexicalBlockFile(scope: !3455, file: !1, discriminator: 1)
!3463 = !DILocation(line: 2970, column: 33, scope: !3462)
!3464 = !DILocation(line: 2970, column: 42, scope: !3462)
!3465 = !DILocation(line: 2971, column: 7, scope: !3455)
!3466 = !DILocation(line: 2971, column: 15, scope: !3455)
!3467 = !DILocation(line: 2971, column: 22, scope: !3455)
!3468 = !DILocation(line: 2971, column: 25, scope: !3462)
!3469 = !DILocation(line: 2971, column: 33, scope: !3462)
!3470 = !DILocation(line: 2971, column: 40, scope: !3462)
!3471 = !DILocation(line: 2971, column: 43, scope: !3472)
!3472 = !DILexicalBlockFile(scope: !3455, file: !1, discriminator: 2)
!3473 = !DILocation(line: 2971, column: 51, scope: !3472)
!3474 = !DILocation(line: 2969, column: 6, scope: !3475)
!3475 = !DILexicalBlockFile(scope: !359, file: !1, discriminator: 1)
!3476 = !DILocation(line: 2973, column: 7, scope: !3477)
!3477 = distinct !DILexicalBlock(scope: !3478, file: !1, line: 2973, column: 7)
!3478 = distinct !DILexicalBlock(scope: !3455, file: !1, line: 2971, column: 61)
!3479 = !DILocation(line: 2973, column: 13, scope: !3477)
!3480 = !DILocation(line: 2973, column: 7, scope: !3478)
!3481 = !DILocation(line: 2974, column: 5, scope: !3482)
!3482 = distinct !DILexicalBlock(scope: !3477, file: !1, line: 2973, column: 22)
!3483 = !DILocation(line: 2974, column: 11, scope: !3482)
!3484 = !DILocation(line: 2975, column: 19, scope: !3482)
!3485 = !DILocation(line: 2975, column: 22, scope: !3482)
!3486 = !DILocation(line: 2975, column: 8, scope: !3482)
!3487 = !DILocation(line: 2975, column: 6, scope: !3482)
!3488 = !DILocation(line: 2976, column: 5, scope: !3482)
!3489 = !DILocation(line: 2976, column: 11, scope: !3482)
!3490 = !DILocation(line: 2977, column: 12, scope: !3482)
!3491 = !DILocation(line: 2977, column: 4, scope: !3482)
!3492 = !DILocation(line: 2979, column: 3, scope: !3478)
!3493 = !DILocation(line: 2987, column: 11, scope: !3494)
!3494 = distinct !DILexicalBlock(scope: !359, file: !1, line: 2987, column: 6)
!3495 = !DILocation(line: 2987, column: 6, scope: !3494)
!3496 = !DILocation(line: 2987, column: 22, scope: !3494)
!3497 = !DILocation(line: 2987, column: 6, scope: !359)
!3498 = !DILocation(line: 2988, column: 7, scope: !3499)
!3499 = distinct !DILexicalBlock(scope: !3500, file: !1, line: 2988, column: 7)
!3500 = distinct !DILexicalBlock(scope: !3494, file: !1, line: 2987, column: 28)
!3501 = !DILocation(line: 2988, column: 7, scope: !3500)
!3502 = !DILocation(line: 2989, column: 4, scope: !3499)
!3503 = !DILocation(line: 2990, column: 8, scope: !3504)
!3504 = distinct !DILexicalBlock(scope: !3500, file: !1, line: 2990, column: 7)
!3505 = !DILocation(line: 2990, column: 11, scope: !3504)
!3506 = !DILocation(line: 2990, column: 17, scope: !3504)
!3507 = !DILocation(line: 2990, column: 7, scope: !3500)
!3508 = !DILocation(line: 2991, column: 23, scope: !3509)
!3509 = distinct !DILexicalBlock(scope: !3504, file: !1, line: 2990, column: 50)
!3510 = !DILocation(line: 2991, column: 26, scope: !3509)
!3511 = !DILocation(line: 2992, column: 39, scope: !3509)
!3512 = !DILocation(line: 2991, column: 4, scope: !3509)
!3513 = !DILocation(line: 2993, column: 4, scope: !3509)
!3514 = !DILocation(line: 2995, column: 14, scope: !3515)
!3515 = distinct !DILexicalBlock(scope: !3500, file: !1, line: 2995, column: 7)
!3516 = !DILocation(line: 2995, column: 7, scope: !3515)
!3517 = !DILocation(line: 2995, column: 20, scope: !3515)
!3518 = !DILocation(line: 2995, column: 7, scope: !3500)
!3519 = !DILocation(line: 2996, column: 23, scope: !3520)
!3520 = distinct !DILexicalBlock(scope: !3515, file: !1, line: 2995, column: 26)
!3521 = !DILocation(line: 2996, column: 26, scope: !3520)
!3522 = !DILocation(line: 2996, column: 35, scope: !3520)
!3523 = !DILocation(line: 2999, column: 8, scope: !3520)
!3524 = !DILocation(line: 2996, column: 4, scope: !3525)
!3525 = !DILexicalBlockFile(scope: !3520, file: !1, discriminator: 1)
!3526 = !DILocation(line: 3000, column: 4, scope: !3520)
!3527 = !DILocation(line: 3002, column: 2, scope: !3500)
!3528 = !DILocation(line: 3002, column: 13, scope: !3529)
!3529 = !DILexicalBlockFile(scope: !3530, file: !1, discriminator: 1)
!3530 = distinct !DILexicalBlock(scope: !3494, file: !1, line: 3002, column: 13)
!3531 = !DILocation(line: 3002, column: 19, scope: !3529)
!3532 = !DILocation(line: 3002, column: 29, scope: !3529)
!3533 = !DILocation(line: 3002, column: 32, scope: !3534)
!3534 = !DILexicalBlockFile(scope: !3530, file: !1, discriminator: 2)
!3535 = !DILocation(line: 3002, column: 38, scope: !3534)
!3536 = !DILocation(line: 3002, column: 13, scope: !3534)
!3537 = !DILocation(line: 3004, column: 22, scope: !3538)
!3538 = distinct !DILexicalBlock(scope: !3530, file: !1, line: 3002, column: 50)
!3539 = !DILocation(line: 3004, column: 25, scope: !3538)
!3540 = !DILocation(line: 3004, column: 34, scope: !3538)
!3541 = !DILocation(line: 3005, column: 36, scope: !3538)
!3542 = !DILocation(line: 3004, column: 3, scope: !3543)
!3543 = !DILexicalBlockFile(scope: !3538, file: !1, discriminator: 1)
!3544 = !DILocation(line: 3006, column: 3, scope: !3538)
!3545 = !DILocation(line: 3007, column: 13, scope: !3546)
!3546 = distinct !DILexicalBlock(scope: !3530, file: !1, line: 3007, column: 13)
!3547 = !DILocation(line: 3007, column: 19, scope: !3546)
!3548 = !DILocation(line: 3007, column: 13, scope: !3530)
!3549 = !DILocation(line: 3008, column: 4, scope: !3550)
!3550 = distinct !DILexicalBlock(scope: !3546, file: !1, line: 3007, column: 28)
!3551 = !DILocation(line: 3008, column: 10, scope: !3550)
!3552 = !DILocation(line: 3009, column: 18, scope: !3550)
!3553 = !DILocation(line: 3009, column: 21, scope: !3550)
!3554 = !DILocation(line: 3009, column: 7, scope: !3550)
!3555 = !DILocation(line: 3009, column: 5, scope: !3550)
!3556 = !DILocation(line: 3010, column: 4, scope: !3550)
!3557 = !DILocation(line: 3010, column: 10, scope: !3550)
!3558 = !DILocation(line: 3011, column: 7, scope: !3559)
!3559 = distinct !DILexicalBlock(scope: !3550, file: !1, line: 3011, column: 7)
!3560 = !DILocation(line: 3011, column: 9, scope: !3559)
!3561 = !DILocation(line: 3011, column: 7, scope: !3550)
!3562 = !DILocation(line: 3012, column: 12, scope: !3559)
!3563 = !DILocation(line: 3012, column: 4, scope: !3559)
!3564 = !DILocation(line: 3013, column: 2, scope: !3550)
!3565 = !DILocation(line: 3023, column: 35, scope: !359)
!3566 = !DILocation(line: 3023, column: 38, scope: !359)
!3567 = !DILocation(line: 3023, column: 34, scope: !359)
!3568 = !DILocation(line: 3023, column: 32, scope: !359)
!3569 = !DILocation(line: 3023, column: 13, scope: !359)
!3570 = !DILocation(line: 3025, column: 9, scope: !359)
!3571 = !DILocation(line: 3025, column: 7, scope: !359)
!3572 = !DILocation(line: 3026, column: 7, scope: !359)
!3573 = !DILocation(line: 3027, column: 7, scope: !359)
!3574 = !DILocation(line: 3028, column: 12, scope: !3575)
!3575 = distinct !DILexicalBlock(scope: !359, file: !1, line: 3028, column: 6)
!3576 = !DILocation(line: 3028, column: 18, scope: !3575)
!3577 = !DILocation(line: 3028, column: 6, scope: !3575)
!3578 = !DILocation(line: 3028, column: 24, scope: !3575)
!3579 = !DILocation(line: 3028, column: 6, scope: !359)
!3580 = !DILocation(line: 3029, column: 7, scope: !3581)
!3581 = distinct !DILexicalBlock(scope: !3582, file: !1, line: 3029, column: 7)
!3582 = distinct !DILexicalBlock(scope: !3575, file: !1, line: 3028, column: 30)
!3583 = !DILocation(line: 3029, column: 15, scope: !3581)
!3584 = !DILocation(line: 3029, column: 12, scope: !3581)
!3585 = !DILocation(line: 3029, column: 7, scope: !3582)
!3586 = !DILocation(line: 3030, column: 19, scope: !3587)
!3587 = distinct !DILexicalBlock(scope: !3581, file: !1, line: 3029, column: 27)
!3588 = !DILocation(line: 3030, column: 22, scope: !3587)
!3589 = !DILocation(line: 3030, column: 9, scope: !3587)
!3590 = !DILocation(line: 3030, column: 7, scope: !3587)
!3591 = !DILocation(line: 3031, column: 8, scope: !3592)
!3592 = distinct !DILexicalBlock(scope: !3587, file: !1, line: 3031, column: 8)
!3593 = !DILocation(line: 3031, column: 11, scope: !3592)
!3594 = !DILocation(line: 3031, column: 8, scope: !3587)
!3595 = !DILocation(line: 3032, column: 5, scope: !3592)
!3596 = !DILocation(line: 3033, column: 4, scope: !3587)
!3597 = !DILocation(line: 3033, column: 8, scope: !3587)
!3598 = !DILocation(line: 3033, column: 14, scope: !3587)
!3599 = !DILocation(line: 3034, column: 15, scope: !3587)
!3600 = !DILocation(line: 3034, column: 4, scope: !3587)
!3601 = !DILocation(line: 3034, column: 8, scope: !3587)
!3602 = !DILocation(line: 3034, column: 13, scope: !3587)
!3603 = !DILocation(line: 3035, column: 3, scope: !3587)
!3604 = !DILocation(line: 3036, column: 3, scope: !3582)
!3605 = !DILocation(line: 3045, column: 11, scope: !3606)
!3606 = distinct !DILexicalBlock(scope: !359, file: !1, line: 3045, column: 6)
!3607 = !DILocation(line: 3045, column: 6, scope: !3606)
!3608 = !DILocation(line: 3045, column: 22, scope: !3606)
!3609 = !DILocation(line: 3045, column: 27, scope: !3606)
!3610 = !DILocation(line: 3045, column: 30, scope: !3611)
!3611 = !DILexicalBlockFile(scope: !3606, file: !1, discriminator: 1)
!3612 = !DILocation(line: 3045, column: 6, scope: !3611)
!3613 = !DILocation(line: 3046, column: 3, scope: !3606)
!3614 = !DILocation(line: 3048, column: 21, scope: !359)
!3615 = !DILocation(line: 3048, column: 24, scope: !359)
!3616 = !DILocation(line: 3048, column: 33, scope: !359)
!3617 = !DILocation(line: 3049, column: 6, scope: !359)
!3618 = !DILocation(line: 3048, column: 2, scope: !3475)
!3619 = !DILocation(line: 3050, column: 2, scope: !359)
!3620 = !DILocation(line: 3051, column: 1, scope: !359)
!3621 = !DILocalVariable(name: "a", arg: 1, scope: !362, file: !1, line: 2434, type: !4)
!3622 = !DILocation(line: 2434, column: 38, scope: !362)
!3623 = !DILocalVariable(name: "pathname", arg: 2, scope: !362, file: !1, line: 2434, type: !79)
!3624 = !DILocation(line: 2434, column: 53, scope: !362)
!3625 = !DILocalVariable(name: "fe", scope: !362, file: !1, line: 2436, type: !113)
!3626 = !DILocation(line: 2436, column: 22, scope: !362)
!3627 = !DILocation(line: 2438, column: 29, scope: !362)
!3628 = !DILocation(line: 2438, column: 7, scope: !362)
!3629 = !DILocation(line: 2438, column: 5, scope: !362)
!3630 = !DILocation(line: 2439, column: 6, scope: !3631)
!3631 = distinct !DILexicalBlock(scope: !362, file: !1, line: 2439, column: 6)
!3632 = !DILocation(line: 2439, column: 9, scope: !3631)
!3633 = !DILocation(line: 2439, column: 6, scope: !362)
!3634 = !DILocation(line: 2440, column: 22, scope: !3635)
!3635 = distinct !DILexicalBlock(scope: !3631, file: !1, line: 2439, column: 18)
!3636 = !DILocation(line: 2440, column: 25, scope: !3635)
!3637 = !DILocation(line: 2440, column: 3, scope: !3635)
!3638 = !DILocation(line: 2442, column: 3, scope: !3635)
!3639 = !DILocation(line: 2444, column: 13, scope: !362)
!3640 = !DILocation(line: 2444, column: 16, scope: !362)
!3641 = !DILocation(line: 2444, column: 2, scope: !362)
!3642 = !DILocation(line: 2444, column: 6, scope: !362)
!3643 = !DILocation(line: 2444, column: 11, scope: !362)
!3644 = !DILocation(line: 2445, column: 18, scope: !362)
!3645 = !DILocation(line: 2445, column: 2, scope: !362)
!3646 = !DILocation(line: 2445, column: 5, scope: !362)
!3647 = !DILocation(line: 2445, column: 16, scope: !362)
!3648 = !DILocation(line: 2446, column: 2, scope: !362)
!3649 = !DILocation(line: 2446, column: 6, scope: !362)
!3650 = !DILocation(line: 2446, column: 12, scope: !362)
!3651 = !DILocation(line: 2447, column: 20, scope: !362)
!3652 = !DILocation(line: 2447, column: 13, scope: !362)
!3653 = !DILocation(line: 2447, column: 2, scope: !362)
!3654 = !DILocation(line: 2447, column: 6, scope: !362)
!3655 = !DILocation(line: 2447, column: 11, scope: !362)
!3656 = !DILocation(line: 2448, column: 10, scope: !362)
!3657 = !DILocation(line: 2448, column: 2, scope: !362)
!3658 = !DILocation(line: 2449, column: 1, scope: !362)
!3659 = !DILocalVariable(name: "a", arg: 1, scope: !366, file: !1, line: 3511, type: !4)
!3660 = !DILocation(line: 3511, column: 50, scope: !366)
!3661 = !DILocalVariable(name: "nochange_flags", scope: !366, file: !1, line: 3513, type: !22)
!3662 = !DILocation(line: 3513, column: 7, scope: !366)
!3663 = !DILocalVariable(name: "mode", scope: !366, file: !1, line: 3514, type: !110)
!3664 = !DILocation(line: 3514, column: 10, scope: !366)
!3665 = !DILocation(line: 3514, column: 36, scope: !366)
!3666 = !DILocation(line: 3514, column: 39, scope: !366)
!3667 = !DILocation(line: 3514, column: 17, scope: !366)
!3668 = !DILocation(line: 3517, column: 17, scope: !366)
!3669 = !DILocation(line: 3537, column: 30, scope: !366)
!3670 = !DILocation(line: 3537, column: 33, scope: !366)
!3671 = !DILocation(line: 3537, column: 36, scope: !366)
!3672 = !DILocation(line: 3537, column: 40, scope: !366)
!3673 = !DILocation(line: 3537, column: 43, scope: !366)
!3674 = !DILocation(line: 3537, column: 49, scope: !366)
!3675 = !DILocation(line: 3538, column: 6, scope: !366)
!3676 = !DILocation(line: 3537, column: 10, scope: !366)
!3677 = !DILocation(line: 3537, column: 2, scope: !366)
!3678 = !DILocalVariable(name: "a", arg: 1, scope: !367, file: !1, line: 2063, type: !4)
!3679 = !DILocation(line: 2063, column: 53, scope: !367)
!3680 = !DILocalVariable(name: "linkname", scope: !367, file: !1, line: 2066, type: !79)
!3681 = !DILocation(line: 2066, column: 14, scope: !367)
!3682 = !DILocalVariable(name: "final_mode", scope: !367, file: !1, line: 2067, type: !110)
!3683 = !DILocation(line: 2067, column: 9, scope: !367)
!3684 = !DILocalVariable(name: "mode", scope: !367, file: !1, line: 2067, type: !110)
!3685 = !DILocation(line: 2067, column: 21, scope: !367)
!3686 = !DILocalVariable(name: "r", scope: !367, file: !1, line: 2068, type: !22)
!3687 = !DILocation(line: 2068, column: 6, scope: !367)
!3688 = !DILocalVariable(name: "linkname_copy", scope: !367, file: !1, line: 2070, type: !94)
!3689 = !DILocation(line: 2070, column: 8, scope: !367)
!3690 = !DILocalVariable(name: "st", scope: !367, file: !1, line: 2071, type: !189)
!3691 = !DILocation(line: 2071, column: 14, scope: !367)
!3692 = !DILocalVariable(name: "error_string", scope: !367, file: !1, line: 2072, type: !90)
!3693 = !DILocation(line: 2072, column: 24, scope: !367)
!3694 = !DILocalVariable(name: "error_number", scope: !367, file: !1, line: 2073, type: !22)
!3695 = !DILocation(line: 2073, column: 6, scope: !367)
!3696 = !DILocation(line: 2077, column: 36, scope: !367)
!3697 = !DILocation(line: 2077, column: 39, scope: !367)
!3698 = !DILocation(line: 2077, column: 13, scope: !367)
!3699 = !DILocation(line: 2077, column: 11, scope: !367)
!3700 = !DILocation(line: 2078, column: 6, scope: !3701)
!3701 = distinct !DILexicalBlock(scope: !367, file: !1, line: 2078, column: 6)
!3702 = !DILocation(line: 2078, column: 15, scope: !3701)
!3703 = !DILocation(line: 2078, column: 6, scope: !367)
!3704 = !DILocation(line: 2082, column: 3, scope: !3705)
!3705 = distinct !DILexicalBlock(scope: !3701, file: !1, line: 2078, column: 24)
!3706 = !DILocation(line: 2082, column: 3, scope: !3707)
!3707 = !DILexicalBlockFile(scope: !3708, file: !1, discriminator: 1)
!3708 = distinct !DILexicalBlock(scope: !3705, file: !1, line: 2082, column: 3)
!3709 = !DILocation(line: 2083, column: 26, scope: !3705)
!3710 = !DILocation(line: 2083, column: 19, scope: !3705)
!3711 = !DILocation(line: 2083, column: 17, scope: !3705)
!3712 = !DILocation(line: 2084, column: 7, scope: !3713)
!3713 = distinct !DILexicalBlock(scope: !3705, file: !1, line: 2084, column: 7)
!3714 = !DILocation(line: 2084, column: 21, scope: !3713)
!3715 = !DILocation(line: 2084, column: 7, scope: !3705)
!3716 = !DILocation(line: 2085, column: 7, scope: !3717)
!3717 = distinct !DILexicalBlock(scope: !3713, file: !1, line: 2084, column: 30)
!3718 = !DILocation(line: 2091, column: 30, scope: !3705)
!3719 = !DILocation(line: 2092, column: 22, scope: !3705)
!3720 = !DILocation(line: 2092, column: 25, scope: !3705)
!3721 = !DILocation(line: 2091, column: 7, scope: !3705)
!3722 = !DILocation(line: 2091, column: 5, scope: !3705)
!3723 = !DILocation(line: 2093, column: 7, scope: !3724)
!3724 = distinct !DILexicalBlock(scope: !3705, file: !1, line: 2093, column: 7)
!3725 = !DILocation(line: 2093, column: 9, scope: !3724)
!3726 = !DILocation(line: 2093, column: 7, scope: !3705)
!3727 = !DILocation(line: 2094, column: 23, scope: !3728)
!3728 = distinct !DILexicalBlock(scope: !3724, file: !1, line: 2093, column: 24)
!3729 = !DILocation(line: 2094, column: 26, scope: !3728)
!3730 = !DILocation(line: 2094, column: 35, scope: !3728)
!3731 = !DILocation(line: 2095, column: 21, scope: !3728)
!3732 = !DILocation(line: 2094, column: 4, scope: !3728)
!3733 = !DILocation(line: 2096, column: 9, scope: !3728)
!3734 = !DILocation(line: 2096, column: 4, scope: !3728)
!3735 = !DILocation(line: 2097, column: 4, scope: !3728)
!3736 = !DILocation(line: 2102, column: 4, scope: !3728)
!3737 = !DILocation(line: 2104, column: 28, scope: !3705)
!3738 = !DILocation(line: 2105, column: 22, scope: !3705)
!3739 = !DILocation(line: 2105, column: 25, scope: !3705)
!3740 = !DILocation(line: 2104, column: 7, scope: !3705)
!3741 = !DILocation(line: 2104, column: 5, scope: !3705)
!3742 = !DILocation(line: 2106, column: 7, scope: !3743)
!3743 = distinct !DILexicalBlock(scope: !3705, file: !1, line: 2106, column: 7)
!3744 = !DILocation(line: 2106, column: 9, scope: !3743)
!3745 = !DILocation(line: 2106, column: 7, scope: !3705)
!3746 = !DILocation(line: 2107, column: 23, scope: !3747)
!3747 = distinct !DILexicalBlock(scope: !3743, file: !1, line: 2106, column: 24)
!3748 = !DILocation(line: 2107, column: 26, scope: !3747)
!3749 = !DILocation(line: 2107, column: 35, scope: !3747)
!3750 = !DILocation(line: 2108, column: 21, scope: !3747)
!3751 = !DILocation(line: 2107, column: 4, scope: !3747)
!3752 = !DILocation(line: 2109, column: 9, scope: !3747)
!3753 = !DILocation(line: 2109, column: 4, scope: !3747)
!3754 = !DILocation(line: 2110, column: 4, scope: !3747)
!3755 = !DILocation(line: 2115, column: 4, scope: !3747)
!3756 = !DILocation(line: 2117, column: 8, scope: !3705)
!3757 = !DILocation(line: 2117, column: 3, scope: !3705)
!3758 = !DILocation(line: 2118, column: 3, scope: !3705)
!3759 = !DILocation(line: 2119, column: 12, scope: !3705)
!3760 = !DILocation(line: 2119, column: 22, scope: !3705)
!3761 = !DILocation(line: 2119, column: 25, scope: !3705)
!3762 = !DILocation(line: 2119, column: 7, scope: !3705)
!3763 = !DILocation(line: 2119, column: 33, scope: !3764)
!3764 = !DILexicalBlockFile(scope: !3705, file: !1, discriminator: 1)
!3765 = !DILocation(line: 2119, column: 7, scope: !3764)
!3766 = !DILocation(line: 2119, column: 7, scope: !3767)
!3767 = !DILexicalBlockFile(scope: !3705, file: !1, discriminator: 2)
!3768 = !DILocation(line: 2119, column: 7, scope: !3769)
!3769 = !DILexicalBlockFile(scope: !3705, file: !1, discriminator: 3)
!3770 = !DILocation(line: 2119, column: 5, scope: !3769)
!3771 = !DILocation(line: 2132, column: 7, scope: !3772)
!3772 = distinct !DILexicalBlock(scope: !3705, file: !1, line: 2132, column: 7)
!3773 = !DILocation(line: 2132, column: 9, scope: !3772)
!3774 = !DILocation(line: 2132, column: 14, scope: !3772)
!3775 = !DILocation(line: 2132, column: 17, scope: !3776)
!3776 = !DILexicalBlockFile(scope: !3772, file: !1, discriminator: 1)
!3777 = !DILocation(line: 2132, column: 20, scope: !3776)
!3778 = !DILocation(line: 2132, column: 29, scope: !3776)
!3779 = !DILocation(line: 2132, column: 7, scope: !3776)
!3780 = !DILocation(line: 2133, column: 4, scope: !3781)
!3781 = distinct !DILexicalBlock(scope: !3772, file: !1, line: 2132, column: 35)
!3782 = !DILocation(line: 2133, column: 7, scope: !3781)
!3783 = !DILocation(line: 2133, column: 12, scope: !3781)
!3784 = !DILocation(line: 2134, column: 4, scope: !3781)
!3785 = !DILocation(line: 2134, column: 7, scope: !3781)
!3786 = !DILocation(line: 2134, column: 16, scope: !3781)
!3787 = !DILocation(line: 2135, column: 3, scope: !3781)
!3788 = !DILocation(line: 2135, column: 14, scope: !3789)
!3789 = !DILexicalBlockFile(scope: !3790, file: !1, discriminator: 1)
!3790 = distinct !DILexicalBlock(scope: !3772, file: !1, line: 2135, column: 14)
!3791 = !DILocation(line: 2135, column: 16, scope: !3789)
!3792 = !DILocation(line: 2135, column: 21, scope: !3789)
!3793 = !DILocation(line: 2135, column: 24, scope: !3794)
!3794 = !DILexicalBlockFile(scope: !3790, file: !1, discriminator: 2)
!3795 = !DILocation(line: 2135, column: 27, scope: !3794)
!3796 = !DILocation(line: 2135, column: 36, scope: !3794)
!3797 = !DILocation(line: 2135, column: 14, scope: !3794)
!3798 = !DILocation(line: 2137, column: 14, scope: !3799)
!3799 = distinct !DILexicalBlock(scope: !3790, file: !1, line: 2135, column: 41)
!3800 = !DILocation(line: 2137, column: 17, scope: !3799)
!3801 = !DILocation(line: 2137, column: 8, scope: !3799)
!3802 = !DILocation(line: 2137, column: 6, scope: !3799)
!3803 = !DILocation(line: 2141, column: 8, scope: !3804)
!3804 = distinct !DILexicalBlock(scope: !3799, file: !1, line: 2141, column: 8)
!3805 = !DILocation(line: 2141, column: 10, scope: !3804)
!3806 = !DILocation(line: 2141, column: 8, scope: !3799)
!3807 = !DILocation(line: 2142, column: 9, scope: !3804)
!3808 = !DILocation(line: 2142, column: 7, scope: !3804)
!3809 = !DILocation(line: 2142, column: 5, scope: !3804)
!3810 = !DILocation(line: 2143, column: 17, scope: !3811)
!3811 = distinct !DILexicalBlock(scope: !3804, file: !1, line: 2143, column: 13)
!3812 = !DILocation(line: 2143, column: 25, scope: !3811)
!3813 = !DILocation(line: 2143, column: 36, scope: !3811)
!3814 = !DILocation(line: 2143, column: 13, scope: !3804)
!3815 = !DILocation(line: 2144, column: 18, scope: !3816)
!3816 = distinct !DILexicalBlock(scope: !3811, file: !1, line: 2143, column: 49)
!3817 = !DILocation(line: 2144, column: 21, scope: !3816)
!3818 = !DILocation(line: 2144, column: 13, scope: !3816)
!3819 = !DILocation(line: 2144, column: 5, scope: !3816)
!3820 = !DILocation(line: 2144, column: 8, scope: !3816)
!3821 = !DILocation(line: 2144, column: 11, scope: !3816)
!3822 = !DILocation(line: 2146, column: 35, scope: !3816)
!3823 = !DILocation(line: 2146, column: 38, scope: !3816)
!3824 = !DILocation(line: 2146, column: 5, scope: !3816)
!3825 = !DILocation(line: 2147, column: 9, scope: !3826)
!3826 = distinct !DILexicalBlock(scope: !3816, file: !1, line: 2147, column: 9)
!3827 = !DILocation(line: 2147, column: 12, scope: !3826)
!3828 = !DILocation(line: 2147, column: 15, scope: !3826)
!3829 = !DILocation(line: 2147, column: 9, scope: !3816)
!3830 = !DILocation(line: 2148, column: 10, scope: !3826)
!3831 = !DILocation(line: 2148, column: 8, scope: !3826)
!3832 = !DILocation(line: 2148, column: 6, scope: !3826)
!3833 = !DILocation(line: 2149, column: 4, scope: !3816)
!3834 = !DILocation(line: 2150, column: 3, scope: !3799)
!3835 = !DILocation(line: 2151, column: 11, scope: !3705)
!3836 = !DILocation(line: 2151, column: 3, scope: !3705)
!3837 = !DILocation(line: 2154, column: 35, scope: !367)
!3838 = !DILocation(line: 2154, column: 38, scope: !367)
!3839 = !DILocation(line: 2154, column: 13, scope: !367)
!3840 = !DILocation(line: 2154, column: 11, scope: !367)
!3841 = !DILocation(line: 2155, column: 6, scope: !3842)
!3842 = distinct !DILexicalBlock(scope: !367, file: !1, line: 2155, column: 6)
!3843 = !DILocation(line: 2155, column: 15, scope: !3842)
!3844 = !DILocation(line: 2155, column: 6, scope: !367)
!3845 = !DILocation(line: 2157, column: 18, scope: !3846)
!3846 = distinct !DILexicalBlock(scope: !3842, file: !1, line: 2155, column: 24)
!3847 = !DILocation(line: 2157, column: 28, scope: !3846)
!3848 = !DILocation(line: 2157, column: 31, scope: !3846)
!3849 = !DILocation(line: 2157, column: 10, scope: !3846)
!3850 = !DILocation(line: 2157, column: 39, scope: !3851)
!3851 = !DILexicalBlockFile(scope: !3846, file: !1, discriminator: 1)
!3852 = !DILocation(line: 2157, column: 10, scope: !3851)
!3853 = !DILocation(line: 2157, column: 10, scope: !3854)
!3854 = !DILexicalBlockFile(scope: !3846, file: !1, discriminator: 2)
!3855 = !DILocation(line: 2157, column: 10, scope: !3856)
!3856 = !DILexicalBlockFile(scope: !3846, file: !1, discriminator: 3)
!3857 = !DILocation(line: 2157, column: 3, scope: !3856)
!3858 = !DILocation(line: 2170, column: 15, scope: !367)
!3859 = !DILocation(line: 2170, column: 18, scope: !367)
!3860 = !DILocation(line: 2170, column: 23, scope: !367)
!3861 = !DILocation(line: 2170, column: 13, scope: !367)
!3862 = !DILocation(line: 2176, column: 9, scope: !367)
!3863 = !DILocation(line: 2176, column: 20, scope: !367)
!3864 = !DILocation(line: 2176, column: 30, scope: !367)
!3865 = !DILocation(line: 2176, column: 33, scope: !367)
!3866 = !DILocation(line: 2176, column: 29, scope: !367)
!3867 = !DILocation(line: 2176, column: 27, scope: !367)
!3868 = !DILocation(line: 2176, column: 7, scope: !367)
!3869 = !DILocation(line: 2178, column: 10, scope: !367)
!3870 = !DILocation(line: 2178, column: 13, scope: !367)
!3871 = !DILocation(line: 2178, column: 18, scope: !367)
!3872 = !DILocation(line: 2178, column: 2, scope: !367)
!3873 = !DILocation(line: 2178, column: 29, scope: !3874)
!3874 = !DILexicalBlockFile(scope: !367, file: !1, discriminator: 1)
!3875 = !DILocation(line: 2183, column: 16, scope: !3876)
!3876 = distinct !DILexicalBlock(scope: !367, file: !1, line: 2178, column: 29)
!3877 = !DILocation(line: 2183, column: 19, scope: !3876)
!3878 = !DILocation(line: 2184, column: 59, scope: !3876)
!3879 = !DILocation(line: 2183, column: 11, scope: !3876)
!3880 = !DILocation(line: 2183, column: 3, scope: !3876)
!3881 = !DILocation(line: 2183, column: 6, scope: !3876)
!3882 = !DILocation(line: 2183, column: 9, scope: !3876)
!3883 = !DILocation(line: 2185, column: 33, scope: !3876)
!3884 = !DILocation(line: 2185, column: 36, scope: !3876)
!3885 = !DILocation(line: 2185, column: 3, scope: !3876)
!3886 = !DILocation(line: 2186, column: 8, scope: !3876)
!3887 = !DILocation(line: 2186, column: 11, scope: !3876)
!3888 = !DILocation(line: 2186, column: 14, scope: !3876)
!3889 = !DILocation(line: 2186, column: 5, scope: !3876)
!3890 = !DILocation(line: 2187, column: 3, scope: !3876)
!3891 = !DILocation(line: 2192, column: 13, scope: !3876)
!3892 = !DILocation(line: 2192, column: 16, scope: !3876)
!3893 = !DILocation(line: 2192, column: 22, scope: !3876)
!3894 = !DILocation(line: 2192, column: 27, scope: !3876)
!3895 = !DILocation(line: 2193, column: 26, scope: !3876)
!3896 = !DILocation(line: 2193, column: 29, scope: !3876)
!3897 = !DILocation(line: 2193, column: 7, scope: !3876)
!3898 = !DILocation(line: 2192, column: 7, scope: !3876)
!3899 = !DILocation(line: 2192, column: 5, scope: !3876)
!3900 = !DILocation(line: 2194, column: 3, scope: !3876)
!3901 = !DILocation(line: 2202, column: 13, scope: !3876)
!3902 = !DILocation(line: 2202, column: 16, scope: !3876)
!3903 = !DILocation(line: 2202, column: 22, scope: !3876)
!3904 = !DILocation(line: 2202, column: 27, scope: !3876)
!3905 = !DILocation(line: 2203, column: 26, scope: !3876)
!3906 = !DILocation(line: 2203, column: 29, scope: !3876)
!3907 = !DILocation(line: 2203, column: 7, scope: !3876)
!3908 = !DILocation(line: 2202, column: 7, scope: !3876)
!3909 = !DILocation(line: 2202, column: 5, scope: !3876)
!3910 = !DILocation(line: 2204, column: 3, scope: !3876)
!3911 = !DILocation(line: 2211, column: 11, scope: !3876)
!3912 = !DILocation(line: 2211, column: 16, scope: !3876)
!3913 = !DILocation(line: 2211, column: 36, scope: !3876)
!3914 = !DILocation(line: 2211, column: 8, scope: !3876)
!3915 = !DILocation(line: 2212, column: 13, scope: !3876)
!3916 = !DILocation(line: 2212, column: 16, scope: !3876)
!3917 = !DILocation(line: 2212, column: 22, scope: !3876)
!3918 = !DILocation(line: 2212, column: 7, scope: !3876)
!3919 = !DILocation(line: 2212, column: 5, scope: !3876)
!3920 = !DILocation(line: 2213, column: 7, scope: !3921)
!3921 = distinct !DILexicalBlock(scope: !3876, file: !1, line: 2213, column: 7)
!3922 = !DILocation(line: 2213, column: 9, scope: !3921)
!3923 = !DILocation(line: 2213, column: 7, scope: !3876)
!3924 = !DILocation(line: 2215, column: 20, scope: !3925)
!3925 = distinct !DILexicalBlock(scope: !3921, file: !1, line: 2213, column: 15)
!3926 = !DILocation(line: 2215, column: 23, scope: !3925)
!3927 = !DILocation(line: 2215, column: 28, scope: !3925)
!3928 = !DILocation(line: 2215, column: 4, scope: !3925)
!3929 = !DILocation(line: 2215, column: 7, scope: !3925)
!3930 = !DILocation(line: 2215, column: 16, scope: !3925)
!3931 = !DILocation(line: 2216, column: 4, scope: !3925)
!3932 = !DILocation(line: 2216, column: 7, scope: !3925)
!3933 = !DILocation(line: 2216, column: 12, scope: !3925)
!3934 = !DILocation(line: 2220, column: 9, scope: !3935)
!3935 = distinct !DILexicalBlock(scope: !3925, file: !1, line: 2220, column: 8)
!3936 = !DILocation(line: 2220, column: 17, scope: !3935)
!3937 = !DILocation(line: 2220, column: 14, scope: !3935)
!3938 = !DILocation(line: 2221, column: 8, scope: !3935)
!3939 = !DILocation(line: 2221, column: 12, scope: !3940)
!3940 = !DILexicalBlockFile(scope: !3935, file: !1, discriminator: 1)
!3941 = !DILocation(line: 2221, column: 15, scope: !3940)
!3942 = !DILocation(line: 2221, column: 21, scope: !3940)
!3943 = !DILocation(line: 2220, column: 8, scope: !3944)
!3944 = !DILexicalBlockFile(scope: !3925, file: !1, discriminator: 1)
!3945 = !DILocation(line: 2222, column: 21, scope: !3935)
!3946 = !DILocation(line: 2222, column: 24, scope: !3935)
!3947 = !DILocation(line: 2222, column: 29, scope: !3935)
!3948 = !DILocation(line: 2222, column: 5, scope: !3935)
!3949 = !DILocation(line: 2222, column: 8, scope: !3935)
!3950 = !DILocation(line: 2222, column: 17, scope: !3935)
!3951 = !DILocation(line: 2223, column: 4, scope: !3925)
!3952 = !DILocation(line: 2223, column: 7, scope: !3925)
!3953 = !DILocation(line: 2223, column: 12, scope: !3925)
!3954 = !DILocation(line: 2224, column: 3, scope: !3925)
!3955 = !DILocation(line: 2225, column: 3, scope: !3876)
!3956 = !DILocation(line: 2228, column: 14, scope: !3876)
!3957 = !DILocation(line: 2228, column: 17, scope: !3876)
!3958 = !DILocation(line: 2228, column: 23, scope: !3876)
!3959 = !DILocation(line: 2228, column: 7, scope: !3876)
!3960 = !DILocation(line: 2228, column: 5, scope: !3876)
!3961 = !DILocation(line: 2229, column: 3, scope: !3876)
!3962 = !DILocation(line: 2238, column: 6, scope: !3963)
!3963 = distinct !DILexicalBlock(scope: !367, file: !1, line: 2238, column: 6)
!3964 = !DILocation(line: 2238, column: 6, scope: !367)
!3965 = !DILocation(line: 2239, column: 11, scope: !3963)
!3966 = !DILocation(line: 2239, column: 3, scope: !3963)
!3967 = !DILocation(line: 2242, column: 6, scope: !3968)
!3968 = distinct !DILexicalBlock(scope: !367, file: !1, line: 2242, column: 6)
!3969 = !DILocation(line: 2242, column: 14, scope: !3968)
!3970 = !DILocation(line: 2242, column: 11, scope: !3968)
!3971 = !DILocation(line: 2242, column: 6, scope: !367)
!3972 = !DILocation(line: 2243, column: 3, scope: !3968)
!3973 = !DILocation(line: 2243, column: 6, scope: !3968)
!3974 = !DILocation(line: 2243, column: 11, scope: !3968)
!3975 = !DILocation(line: 2244, column: 2, scope: !367)
!3976 = !DILocation(line: 2245, column: 1, scope: !367)
!3977 = !DILocalVariable(name: "a", arg: 1, scope: !368, file: !1, line: 2931, type: !4)
!3978 = !DILocation(line: 2931, column: 46, scope: !368)
!3979 = !DILocalVariable(name: "path", arg: 2, scope: !368, file: !1, line: 2931, type: !94)
!3980 = !DILocation(line: 2931, column: 55, scope: !368)
!3981 = !DILocalVariable(name: "slash", scope: !368, file: !1, line: 2933, type: !94)
!3982 = !DILocation(line: 2933, column: 8, scope: !368)
!3983 = !DILocalVariable(name: "r", scope: !368, file: !1, line: 2934, type: !22)
!3984 = !DILocation(line: 2934, column: 6, scope: !368)
!3985 = !DILocation(line: 2937, column: 18, scope: !368)
!3986 = !DILocation(line: 2937, column: 10, scope: !368)
!3987 = !DILocation(line: 2937, column: 8, scope: !368)
!3988 = !DILocation(line: 2938, column: 6, scope: !3989)
!3989 = distinct !DILexicalBlock(scope: !368, file: !1, line: 2938, column: 6)
!3990 = !DILocation(line: 2938, column: 12, scope: !3989)
!3991 = !DILocation(line: 2938, column: 6, scope: !368)
!3992 = !DILocation(line: 2939, column: 3, scope: !3989)
!3993 = !DILocation(line: 2940, column: 3, scope: !368)
!3994 = !DILocation(line: 2940, column: 9, scope: !368)
!3995 = !DILocation(line: 2941, column: 17, scope: !368)
!3996 = !DILocation(line: 2941, column: 20, scope: !368)
!3997 = !DILocation(line: 2941, column: 6, scope: !368)
!3998 = !DILocation(line: 2941, column: 4, scope: !368)
!3999 = !DILocation(line: 2942, column: 3, scope: !368)
!4000 = !DILocation(line: 2942, column: 9, scope: !368)
!4001 = !DILocation(line: 2943, column: 10, scope: !368)
!4002 = !DILocation(line: 2943, column: 2, scope: !368)
!4003 = !DILocation(line: 2944, column: 1, scope: !368)
!4004 = !DILocalVariable(name: "st", arg: 1, scope: !369, file: !1, line: 4205, type: !224)
!4005 = !DILocation(line: 4205, column: 20, scope: !369)
!4006 = !DILocalVariable(name: "entry", arg: 2, scope: !369, file: !1, line: 4205, type: !29)
!4007 = !DILocation(line: 4205, column: 46, scope: !369)
!4008 = !DILocation(line: 4209, column: 6, scope: !4009)
!4009 = distinct !DILexicalBlock(scope: !369, file: !1, line: 4209, column: 6)
!4010 = !DILocation(line: 4209, column: 6, scope: !4011)
!4011 = !DILexicalBlockFile(scope: !4009, file: !1, discriminator: 1)
!4012 = !DILocation(line: 4209, column: 6, scope: !4013)
!4013 = !DILexicalBlockFile(scope: !4009, file: !1, discriminator: 2)
!4014 = !DILocation(line: 4209, column: 6, scope: !4015)
!4015 = !DILexicalBlockFile(scope: !4009, file: !1, discriminator: 3)
!4016 = !DILocation(line: 4209, column: 6, scope: !4017)
!4017 = !DILexicalBlockFile(scope: !4009, file: !1, discriminator: 4)
!4018 = !DILocation(line: 4209, column: 6, scope: !4019)
!4019 = !DILexicalBlockFile(scope: !4009, file: !1, discriminator: 5)
!4020 = !DILocation(line: 4209, column: 6, scope: !4021)
!4021 = !DILexicalBlockFile(scope: !4009, file: !1, discriminator: 6)
!4022 = !DILocation(line: 4209, column: 36, scope: !4021)
!4023 = !DILocation(line: 4209, column: 36, scope: !4024)
!4024 = !DILexicalBlockFile(scope: !4009, file: !1, discriminator: 7)
!4025 = !DILocation(line: 4209, column: 36, scope: !4026)
!4026 = !DILexicalBlockFile(scope: !4009, file: !1, discriminator: 8)
!4027 = !DILocation(line: 4209, column: 36, scope: !4028)
!4028 = !DILexicalBlockFile(scope: !4009, file: !1, discriminator: 9)
!4029 = !DILocation(line: 4209, column: 36, scope: !4030)
!4030 = !DILexicalBlockFile(scope: !4009, file: !1, discriminator: 10)
!4031 = !DILocation(line: 4209, column: 36, scope: !4032)
!4032 = !DILexicalBlockFile(scope: !4009, file: !1, discriminator: 11)
!4033 = !DILocation(line: 4209, column: 36, scope: !4034)
!4034 = !DILexicalBlockFile(scope: !4009, file: !1, discriminator: 12)
!4035 = !DILocation(line: 4209, column: 34, scope: !4034)
!4036 = !DILocation(line: 4209, column: 6, scope: !4034)
!4037 = !DILocation(line: 4210, column: 3, scope: !4009)
!4038 = !DILocation(line: 4212, column: 6, scope: !4039)
!4039 = distinct !DILexicalBlock(scope: !369, file: !1, line: 4212, column: 6)
!4040 = !DILocation(line: 4212, column: 6, scope: !4041)
!4041 = !DILexicalBlockFile(scope: !4039, file: !1, discriminator: 1)
!4042 = !DILocation(line: 4212, column: 6, scope: !4043)
!4043 = !DILexicalBlockFile(scope: !4039, file: !1, discriminator: 2)
!4044 = !DILocation(line: 4212, column: 6, scope: !4045)
!4045 = !DILexicalBlockFile(scope: !4039, file: !1, discriminator: 3)
!4046 = !DILocation(line: 4212, column: 6, scope: !4047)
!4047 = !DILexicalBlockFile(scope: !4039, file: !1, discriminator: 4)
!4048 = !DILocation(line: 4212, column: 6, scope: !4049)
!4049 = !DILexicalBlockFile(scope: !4039, file: !1, discriminator: 5)
!4050 = !DILocation(line: 4212, column: 6, scope: !4051)
!4051 = !DILexicalBlockFile(scope: !4039, file: !1, discriminator: 6)
!4052 = !DILocation(line: 4212, column: 36, scope: !4051)
!4053 = !DILocation(line: 4212, column: 36, scope: !4054)
!4054 = !DILexicalBlockFile(scope: !4039, file: !1, discriminator: 7)
!4055 = !DILocation(line: 4212, column: 36, scope: !4056)
!4056 = !DILexicalBlockFile(scope: !4039, file: !1, discriminator: 8)
!4057 = !DILocation(line: 4212, column: 36, scope: !4058)
!4058 = !DILexicalBlockFile(scope: !4039, file: !1, discriminator: 9)
!4059 = !DILocation(line: 4212, column: 36, scope: !4060)
!4060 = !DILexicalBlockFile(scope: !4039, file: !1, discriminator: 10)
!4061 = !DILocation(line: 4212, column: 36, scope: !4062)
!4062 = !DILexicalBlockFile(scope: !4039, file: !1, discriminator: 11)
!4063 = !DILocation(line: 4212, column: 36, scope: !4064)
!4064 = !DILexicalBlockFile(scope: !4039, file: !1, discriminator: 12)
!4065 = !DILocation(line: 4212, column: 34, scope: !4064)
!4066 = !DILocation(line: 4212, column: 6, scope: !4064)
!4067 = !DILocation(line: 4213, column: 3, scope: !4039)
!4068 = !DILocation(line: 4221, column: 6, scope: !4069)
!4069 = distinct !DILexicalBlock(scope: !369, file: !1, line: 4221, column: 6)
!4070 = !DILocation(line: 4221, column: 10, scope: !4069)
!4071 = !DILocation(line: 4221, column: 18, scope: !4069)
!4072 = !DILocation(line: 4221, column: 53, scope: !4069)
!4073 = !DILocation(line: 4221, column: 28, scope: !4069)
!4074 = !DILocation(line: 4221, column: 26, scope: !4069)
!4075 = !DILocation(line: 4221, column: 6, scope: !369)
!4076 = !DILocation(line: 4222, column: 3, scope: !4069)
!4077 = !DILocation(line: 4239, column: 2, scope: !369)
!4078 = !DILocation(line: 4240, column: 1, scope: !369)
!4079 = !DILocalVariable(name: "a", arg: 1, scope: !374, file: !1, line: 404, type: !4)
!4080 = !DILocation(line: 404, column: 38, scope: !374)
!4081 = !DILocation(line: 406, column: 6, scope: !4082)
!4082 = distinct !DILexicalBlock(scope: !374, file: !1, line: 406, column: 6)
!4083 = !DILocation(line: 406, column: 9, scope: !4082)
!4084 = !DILocation(line: 406, column: 13, scope: !4082)
!4085 = !DILocation(line: 406, column: 6, scope: !374)
!4086 = !DILocation(line: 408, column: 3, scope: !4087)
!4087 = distinct !DILexicalBlock(scope: !4082, file: !1, line: 406, column: 22)
!4088 = !DILocation(line: 411, column: 6, scope: !4089)
!4089 = distinct !DILexicalBlock(scope: !374, file: !1, line: 411, column: 6)
!4090 = !DILocation(line: 411, column: 9, scope: !4089)
!4091 = !DILocation(line: 411, column: 12, scope: !4089)
!4092 = !DILocation(line: 411, column: 17, scope: !4089)
!4093 = !DILocation(line: 411, column: 26, scope: !4094)
!4094 = !DILexicalBlockFile(scope: !4089, file: !1, discriminator: 1)
!4095 = !DILocation(line: 411, column: 29, scope: !4094)
!4096 = !DILocation(line: 411, column: 34, scope: !4094)
!4097 = !DILocation(line: 411, column: 37, scope: !4094)
!4098 = !DILocation(line: 411, column: 20, scope: !4094)
!4099 = !DILocation(line: 411, column: 41, scope: !4094)
!4100 = !DILocation(line: 411, column: 6, scope: !4094)
!4101 = !DILocation(line: 412, column: 13, scope: !4102)
!4102 = distinct !DILexicalBlock(scope: !4089, file: !1, line: 411, column: 47)
!4103 = !DILocation(line: 412, column: 16, scope: !4102)
!4104 = !DILocation(line: 412, column: 3, scope: !4102)
!4105 = !DILocation(line: 412, column: 6, scope: !4102)
!4106 = !DILocation(line: 412, column: 10, scope: !4102)
!4107 = !DILocation(line: 413, column: 3, scope: !4102)
!4108 = !DILocation(line: 420, column: 12, scope: !4109)
!4109 = distinct !DILexicalBlock(scope: !374, file: !1, line: 420, column: 6)
!4110 = !DILocation(line: 420, column: 15, scope: !4109)
!4111 = !DILocation(line: 420, column: 22, scope: !4109)
!4112 = !DILocation(line: 420, column: 25, scope: !4109)
!4113 = !DILocation(line: 420, column: 6, scope: !4109)
!4114 = !DILocation(line: 420, column: 29, scope: !4109)
!4115 = !DILocation(line: 420, column: 6, scope: !374)
!4116 = !DILocation(line: 421, column: 13, scope: !4117)
!4117 = distinct !DILexicalBlock(scope: !4109, file: !1, line: 420, column: 35)
!4118 = !DILocation(line: 421, column: 16, scope: !4117)
!4119 = !DILocation(line: 421, column: 3, scope: !4117)
!4120 = !DILocation(line: 421, column: 6, scope: !4117)
!4121 = !DILocation(line: 421, column: 10, scope: !4117)
!4122 = !DILocation(line: 422, column: 3, scope: !4117)
!4123 = !DILocation(line: 424, column: 21, scope: !374)
!4124 = !DILocation(line: 424, column: 24, scope: !374)
!4125 = !DILocation(line: 424, column: 33, scope: !374)
!4126 = !DILocation(line: 424, column: 2, scope: !4127)
!4127 = !DILexicalBlockFile(scope: !374, file: !1, discriminator: 1)
!4128 = !DILocation(line: 425, column: 2, scope: !374)
!4129 = !DILocation(line: 426, column: 1, scope: !374)
!4130 = !DILocalVariable(name: "a", arg: 1, scope: !375, file: !1, line: 3732, type: !4)
!4131 = !DILocation(line: 3732, column: 46, scope: !375)
!4132 = !DILocalVariable(name: "pathname", arg: 2, scope: !375, file: !1, line: 3732, type: !79)
!4133 = !DILocation(line: 3732, column: 61, scope: !375)
!4134 = !DILocation(line: 3734, column: 8, scope: !375)
!4135 = !DILocation(line: 3735, column: 8, scope: !375)
!4136 = !DILocation(line: 3736, column: 2, scope: !375)
!4137 = !DILocalVariable(name: "a", arg: 1, scope: !378, file: !1, line: 3064, type: !4)
!4138 = !DILocation(line: 3064, column: 42, scope: !378)
!4139 = !DILocation(line: 3071, column: 6, scope: !4140)
!4140 = distinct !DILexicalBlock(scope: !378, file: !1, line: 3071, column: 6)
!4141 = !DILocation(line: 3071, column: 9, scope: !4140)
!4142 = !DILocation(line: 3071, column: 18, scope: !4140)
!4143 = !DILocation(line: 3071, column: 24, scope: !4140)
!4144 = !DILocation(line: 3071, column: 28, scope: !4145)
!4145 = !DILexicalBlockFile(scope: !4140, file: !1, discriminator: 1)
!4146 = !DILocation(line: 3071, column: 31, scope: !4145)
!4147 = !DILocation(line: 3071, column: 43, scope: !4145)
!4148 = !DILocation(line: 3071, column: 46, scope: !4145)
!4149 = !DILocation(line: 3071, column: 40, scope: !4145)
!4150 = !DILocation(line: 3071, column: 6, scope: !4145)
!4151 = !DILocation(line: 3072, column: 22, scope: !4152)
!4152 = distinct !DILexicalBlock(scope: !4140, file: !1, line: 3071, column: 51)
!4153 = !DILocation(line: 3072, column: 25, scope: !4152)
!4154 = !DILocation(line: 3072, column: 34, scope: !4152)
!4155 = !DILocation(line: 3073, column: 38, scope: !4152)
!4156 = !DILocation(line: 3073, column: 41, scope: !4152)
!4157 = !DILocation(line: 3072, column: 3, scope: !4158)
!4158 = !DILexicalBlockFile(scope: !4152, file: !1, discriminator: 1)
!4159 = !DILocation(line: 3074, column: 3, scope: !4152)
!4160 = !DILocation(line: 3080, column: 6, scope: !4161)
!4161 = distinct !DILexicalBlock(scope: !378, file: !1, line: 3080, column: 6)
!4162 = !DILocation(line: 3080, column: 9, scope: !4161)
!4163 = !DILocation(line: 3080, column: 12, scope: !4161)
!4164 = !DILocation(line: 3080, column: 17, scope: !4161)
!4165 = !DILocation(line: 3080, column: 27, scope: !4166)
!4166 = !DILexicalBlockFile(scope: !4161, file: !1, discriminator: 1)
!4167 = !DILocation(line: 3080, column: 30, scope: !4166)
!4168 = !DILocation(line: 3080, column: 34, scope: !4166)
!4169 = !DILocation(line: 3080, column: 37, scope: !4166)
!4170 = !DILocation(line: 3080, column: 42, scope: !4166)
!4171 = !DILocation(line: 3080, column: 45, scope: !4166)
!4172 = !DILocation(line: 3080, column: 20, scope: !4166)
!4173 = !DILocation(line: 3080, column: 50, scope: !4166)
!4174 = !DILocation(line: 3080, column: 6, scope: !4166)
!4175 = !DILocation(line: 3082, column: 3, scope: !4176)
!4176 = distinct !DILexicalBlock(scope: !4161, file: !1, line: 3080, column: 56)
!4177 = !DILocation(line: 3082, column: 6, scope: !4176)
!4178 = !DILocation(line: 3082, column: 11, scope: !4176)
!4179 = !DILocation(line: 3083, column: 3, scope: !4176)
!4180 = !DILocation(line: 3090, column: 13, scope: !4181)
!4181 = distinct !DILexicalBlock(scope: !378, file: !1, line: 3090, column: 6)
!4182 = !DILocation(line: 3090, column: 16, scope: !4181)
!4183 = !DILocation(line: 3090, column: 22, scope: !4181)
!4184 = !DILocation(line: 3090, column: 25, scope: !4181)
!4185 = !DILocation(line: 3090, column: 30, scope: !4181)
!4186 = !DILocation(line: 3090, column: 33, scope: !4181)
!4187 = !DILocation(line: 3090, column: 6, scope: !4181)
!4188 = !DILocation(line: 3090, column: 38, scope: !4181)
!4189 = !DILocation(line: 3090, column: 6, scope: !378)
!4190 = !DILocation(line: 3092, column: 3, scope: !4191)
!4191 = distinct !DILexicalBlock(scope: !4181, file: !1, line: 3090, column: 44)
!4192 = !DILocation(line: 3092, column: 6, scope: !4191)
!4193 = !DILocation(line: 3092, column: 11, scope: !4191)
!4194 = !DILocation(line: 3093, column: 3, scope: !4191)
!4195 = !DILocation(line: 3103, column: 21, scope: !378)
!4196 = !DILocation(line: 3103, column: 24, scope: !378)
!4197 = !DILocation(line: 3103, column: 33, scope: !378)
!4198 = !DILocation(line: 3105, column: 16, scope: !378)
!4199 = !DILocation(line: 3105, column: 19, scope: !378)
!4200 = !DILocation(line: 3105, column: 34, scope: !378)
!4201 = !DILocation(line: 3105, column: 37, scope: !378)
!4202 = !DILocation(line: 3105, column: 42, scope: !378)
!4203 = !DILocation(line: 3105, column: 45, scope: !378)
!4204 = !DILocation(line: 3103, column: 2, scope: !4205)
!4205 = !DILexicalBlockFile(scope: !378, file: !1, discriminator: 1)
!4206 = !DILocation(line: 3106, column: 2, scope: !378)
!4207 = !DILocation(line: 3107, column: 1, scope: !378)
!4208 = !DILocalVariable(name: "a", arg: 1, scope: !379, file: !1, line: 3317, type: !4)
!4209 = !DILocation(line: 3317, column: 37, scope: !379)
!4210 = !DILocalVariable(name: "mode", arg: 2, scope: !379, file: !1, line: 3317, type: !22)
!4211 = !DILocation(line: 3317, column: 44, scope: !379)
!4212 = !DILocalVariable(name: "r", scope: !379, file: !1, line: 3319, type: !22)
!4213 = !DILocation(line: 3319, column: 6, scope: !379)
!4214 = !DILocation(line: 3320, column: 7, scope: !379)
!4215 = !DILocation(line: 3322, column: 6, scope: !4216)
!4216 = distinct !DILexicalBlock(scope: !379, file: !1, line: 3322, column: 6)
!4217 = !DILocation(line: 3322, column: 9, scope: !4216)
!4218 = !DILocation(line: 3322, column: 14, scope: !4216)
!4219 = !DILocation(line: 3322, column: 6, scope: !379)
!4220 = !DILocation(line: 3329, column: 22, scope: !4221)
!4221 = distinct !DILexicalBlock(scope: !4222, file: !1, line: 3329, column: 7)
!4222 = distinct !DILexicalBlock(scope: !4216, file: !1, line: 3322, column: 33)
!4223 = !DILocation(line: 3329, column: 12, scope: !4221)
!4224 = !DILocation(line: 3329, column: 10, scope: !4221)
!4225 = !DILocation(line: 3329, column: 26, scope: !4221)
!4226 = !DILocation(line: 3329, column: 7, scope: !4222)
!4227 = !DILocation(line: 3330, column: 12, scope: !4221)
!4228 = !DILocation(line: 3330, column: 4, scope: !4221)
!4229 = !DILocation(line: 3331, column: 7, scope: !4230)
!4230 = distinct !DILexicalBlock(scope: !4222, file: !1, line: 3331, column: 7)
!4231 = !DILocation(line: 3331, column: 10, scope: !4230)
!4232 = !DILocation(line: 3331, column: 15, scope: !4230)
!4233 = !DILocation(line: 3331, column: 25, scope: !4230)
!4234 = !DILocation(line: 3331, column: 28, scope: !4230)
!4235 = !DILocation(line: 3331, column: 22, scope: !4230)
!4236 = !DILocation(line: 3331, column: 7, scope: !4222)
!4237 = !DILocation(line: 3332, column: 9, scope: !4238)
!4238 = distinct !DILexicalBlock(scope: !4230, file: !1, line: 3331, column: 33)
!4239 = !DILocation(line: 3333, column: 8, scope: !4240)
!4240 = distinct !DILexicalBlock(scope: !4238, file: !1, line: 3333, column: 8)
!4241 = !DILocation(line: 3333, column: 11, scope: !4240)
!4242 = !DILocation(line: 3333, column: 17, scope: !4240)
!4243 = !DILocation(line: 3333, column: 8, scope: !4238)
!4244 = !DILocation(line: 3341, column: 24, scope: !4245)
!4245 = distinct !DILexicalBlock(scope: !4240, file: !1, line: 3333, column: 42)
!4246 = !DILocation(line: 3341, column: 27, scope: !4245)
!4247 = !DILocation(line: 3341, column: 5, scope: !4245)
!4248 = !DILocation(line: 3343, column: 7, scope: !4245)
!4249 = !DILocation(line: 3344, column: 4, scope: !4245)
!4250 = !DILocation(line: 3345, column: 3, scope: !4238)
!4251 = !DILocation(line: 3347, column: 7, scope: !4252)
!4252 = distinct !DILexicalBlock(scope: !4222, file: !1, line: 3347, column: 7)
!4253 = !DILocation(line: 3347, column: 10, scope: !4252)
!4254 = !DILocation(line: 3347, column: 15, scope: !4252)
!4255 = !DILocation(line: 3347, column: 25, scope: !4252)
!4256 = !DILocation(line: 3347, column: 28, scope: !4252)
!4257 = !DILocation(line: 3347, column: 22, scope: !4252)
!4258 = !DILocation(line: 3348, column: 7, scope: !4252)
!4259 = !DILocation(line: 3348, column: 11, scope: !4260)
!4260 = !DILexicalBlockFile(scope: !4252, file: !1, discriminator: 1)
!4261 = !DILocation(line: 3348, column: 14, scope: !4260)
!4262 = !DILocation(line: 3348, column: 19, scope: !4260)
!4263 = !DILocation(line: 3347, column: 7, scope: !4264)
!4264 = !DILexicalBlockFile(scope: !4222, file: !1, discriminator: 1)
!4265 = !DILocation(line: 3349, column: 9, scope: !4266)
!4266 = distinct !DILexicalBlock(scope: !4252, file: !1, line: 3348, column: 33)
!4267 = !DILocation(line: 3350, column: 8, scope: !4268)
!4268 = distinct !DILexicalBlock(scope: !4266, file: !1, line: 3350, column: 8)
!4269 = !DILocation(line: 3350, column: 11, scope: !4268)
!4270 = !DILocation(line: 3350, column: 17, scope: !4268)
!4271 = !DILocation(line: 3350, column: 8, scope: !4266)
!4272 = !DILocation(line: 3351, column: 24, scope: !4273)
!4273 = distinct !DILexicalBlock(scope: !4268, file: !1, line: 3350, column: 42)
!4274 = !DILocation(line: 3351, column: 27, scope: !4273)
!4275 = !DILocation(line: 3351, column: 5, scope: !4273)
!4276 = !DILocation(line: 3353, column: 7, scope: !4273)
!4277 = !DILocation(line: 3354, column: 4, scope: !4273)
!4278 = !DILocation(line: 3355, column: 3, scope: !4266)
!4279 = !DILocation(line: 3356, column: 3, scope: !4222)
!4280 = !DILocation(line: 3356, column: 6, scope: !4222)
!4281 = !DILocation(line: 3356, column: 11, scope: !4222)
!4282 = !DILocation(line: 3357, column: 3, scope: !4222)
!4283 = !DILocation(line: 3357, column: 6, scope: !4222)
!4284 = !DILocation(line: 3357, column: 11, scope: !4222)
!4285 = !DILocation(line: 3358, column: 2, scope: !4222)
!4286 = !DILocation(line: 3358, column: 13, scope: !4287)
!4287 = !DILexicalBlockFile(scope: !4288, file: !1, discriminator: 1)
!4288 = distinct !DILexicalBlock(scope: !4216, file: !1, line: 3358, column: 13)
!4289 = !DILocation(line: 3358, column: 16, scope: !4287)
!4290 = !DILocation(line: 3358, column: 21, scope: !4287)
!4291 = !DILocation(line: 3364, column: 7, scope: !4292)
!4292 = distinct !DILexicalBlock(scope: !4293, file: !1, line: 3364, column: 7)
!4293 = distinct !DILexicalBlock(scope: !4288, file: !1, line: 3358, column: 40)
!4294 = !DILocation(line: 3364, column: 10, scope: !4292)
!4295 = !DILocation(line: 3364, column: 22, scope: !4292)
!4296 = !DILocation(line: 3364, column: 25, scope: !4292)
!4297 = !DILocation(line: 3364, column: 19, scope: !4292)
!4298 = !DILocation(line: 3364, column: 7, scope: !4293)
!4299 = !DILocation(line: 3365, column: 9, scope: !4300)
!4300 = distinct !DILexicalBlock(scope: !4292, file: !1, line: 3364, column: 30)
!4301 = !DILocation(line: 3366, column: 8, scope: !4302)
!4302 = distinct !DILexicalBlock(scope: !4300, file: !1, line: 3366, column: 8)
!4303 = !DILocation(line: 3366, column: 11, scope: !4302)
!4304 = !DILocation(line: 3366, column: 17, scope: !4302)
!4305 = !DILocation(line: 3366, column: 8, scope: !4300)
!4306 = !DILocation(line: 3367, column: 24, scope: !4307)
!4307 = distinct !DILexicalBlock(scope: !4302, file: !1, line: 3366, column: 42)
!4308 = !DILocation(line: 3367, column: 27, scope: !4307)
!4309 = !DILocation(line: 3367, column: 5, scope: !4307)
!4310 = !DILocation(line: 3369, column: 7, scope: !4307)
!4311 = !DILocation(line: 3370, column: 4, scope: !4307)
!4312 = !DILocation(line: 3371, column: 3, scope: !4300)
!4313 = !DILocation(line: 3372, column: 3, scope: !4293)
!4314 = !DILocation(line: 3372, column: 6, scope: !4293)
!4315 = !DILocation(line: 3372, column: 11, scope: !4293)
!4316 = !DILocation(line: 3373, column: 2, scope: !4293)
!4317 = !DILocation(line: 3375, column: 6, scope: !4318)
!4318 = distinct !DILexicalBlock(scope: !379, file: !1, line: 3375, column: 6)
!4319 = !DILocation(line: 3375, column: 6, scope: !379)
!4320 = !DILocation(line: 3405, column: 2, scope: !4321)
!4321 = distinct !DILexicalBlock(scope: !4318, file: !1, line: 3375, column: 24)
!4322 = !DILocation(line: 3405, column: 14, scope: !4323)
!4323 = !DILexicalBlockFile(scope: !4324, file: !1, discriminator: 1)
!4324 = distinct !DILexicalBlock(scope: !4318, file: !1, line: 3405, column: 13)
!4325 = !DILocation(line: 3405, column: 13, scope: !4323)
!4326 = !DILocation(line: 3413, column: 7, scope: !4327)
!4327 = distinct !DILexicalBlock(scope: !4328, file: !1, line: 3413, column: 7)
!4328 = distinct !DILexicalBlock(scope: !4324, file: !1, line: 3405, column: 32)
!4329 = !DILocation(line: 3413, column: 10, scope: !4327)
!4330 = !DILocation(line: 3413, column: 13, scope: !4327)
!4331 = !DILocation(line: 3413, column: 7, scope: !4328)
!4332 = !DILocation(line: 3414, column: 15, scope: !4333)
!4333 = distinct !DILexicalBlock(scope: !4334, file: !1, line: 3414, column: 8)
!4334 = distinct !DILexicalBlock(scope: !4327, file: !1, line: 3413, column: 19)
!4335 = !DILocation(line: 3414, column: 18, scope: !4333)
!4336 = !DILocation(line: 3414, column: 22, scope: !4333)
!4337 = !DILocation(line: 3414, column: 8, scope: !4333)
!4338 = !DILocation(line: 3414, column: 28, scope: !4333)
!4339 = !DILocation(line: 3414, column: 8, scope: !4334)
!4340 = !DILocation(line: 3415, column: 24, scope: !4341)
!4341 = distinct !DILexicalBlock(scope: !4333, file: !1, line: 3414, column: 34)
!4342 = !DILocation(line: 3415, column: 27, scope: !4341)
!4343 = !DILocation(line: 3415, column: 36, scope: !4341)
!4344 = !DILocation(line: 3416, column: 46, scope: !4341)
!4345 = !DILocation(line: 3415, column: 5, scope: !4346)
!4346 = !DILexicalBlockFile(scope: !4341, file: !1, discriminator: 1)
!4347 = !DILocation(line: 3417, column: 7, scope: !4341)
!4348 = !DILocation(line: 3418, column: 4, scope: !4341)
!4349 = !DILocation(line: 3419, column: 3, scope: !4334)
!4350 = !DILocation(line: 3423, column: 14, scope: !4351)
!4351 = distinct !DILexicalBlock(scope: !4327, file: !1, line: 3423, column: 8)
!4352 = !DILocation(line: 3423, column: 17, scope: !4351)
!4353 = !DILocation(line: 3423, column: 23, scope: !4351)
!4354 = !DILocation(line: 3423, column: 8, scope: !4351)
!4355 = !DILocation(line: 3423, column: 29, scope: !4351)
!4356 = !DILocation(line: 3423, column: 8, scope: !4327)
!4357 = !DILocation(line: 3424, column: 24, scope: !4358)
!4358 = distinct !DILexicalBlock(scope: !4351, file: !1, line: 3423, column: 35)
!4359 = !DILocation(line: 3424, column: 27, scope: !4358)
!4360 = !DILocation(line: 3424, column: 36, scope: !4358)
!4361 = !DILocation(line: 3425, column: 46, scope: !4358)
!4362 = !DILocation(line: 3424, column: 5, scope: !4363)
!4363 = !DILexicalBlockFile(scope: !4358, file: !1, discriminator: 1)
!4364 = !DILocation(line: 3426, column: 7, scope: !4358)
!4365 = !DILocation(line: 3427, column: 4, scope: !4358)
!4366 = !DILocation(line: 3428, column: 2, scope: !4328)
!4367 = !DILocation(line: 3429, column: 10, scope: !379)
!4368 = !DILocation(line: 3429, column: 2, scope: !379)
!4369 = !DILocation(line: 3430, column: 1, scope: !379)
!4370 = !DILocalVariable(name: "a", arg: 1, scope: !382, file: !1, line: 4184, type: !4)
!4371 = !DILocation(line: 4184, column: 39, scope: !382)
!4372 = !DILocation(line: 4190, column: 32, scope: !4373)
!4373 = distinct !DILexicalBlock(scope: !382, file: !1, line: 4190, column: 6)
!4374 = !DILocation(line: 4190, column: 35, scope: !4373)
!4375 = !DILocation(line: 4190, column: 6, scope: !4373)
!4376 = !DILocation(line: 4190, column: 42, scope: !4373)
!4377 = !DILocation(line: 4190, column: 47, scope: !4373)
!4378 = !DILocation(line: 4190, column: 51, scope: !4379)
!4379 = !DILexicalBlockFile(scope: !4373, file: !1, discriminator: 1)
!4380 = !DILocation(line: 4190, column: 6, scope: !4379)
!4381 = !DILocation(line: 4191, column: 16, scope: !4382)
!4382 = distinct !DILexicalBlock(scope: !4373, file: !1, line: 4190, column: 65)
!4383 = !DILocation(line: 4192, column: 22, scope: !4382)
!4384 = !DILocation(line: 4192, column: 25, scope: !4382)
!4385 = !DILocation(line: 4192, column: 3, scope: !4382)
!4386 = !DILocation(line: 4194, column: 3, scope: !4382)
!4387 = !DILocation(line: 4197, column: 2, scope: !382)
!4388 = !DILocation(line: 4198, column: 1, scope: !382)
!4389 = !DILocalVariable(name: "a", arg: 1, scope: !383, file: !1, line: 3433, type: !4)
!4390 = !DILocation(line: 3433, column: 39, scope: !383)
!4391 = !DILocalVariable(name: "le", scope: !383, file: !1, line: 3435, type: !113)
!4392 = !DILocation(line: 3435, column: 22, scope: !383)
!4393 = !DILocalVariable(name: "set", scope: !383, file: !1, line: 3436, type: !46)
!4394 = !DILocation(line: 3436, column: 16, scope: !383)
!4395 = !DILocalVariable(name: "clear", scope: !383, file: !1, line: 3436, type: !46)
!4396 = !DILocation(line: 3436, column: 21, scope: !383)
!4397 = !DILocalVariable(name: "r", scope: !383, file: !1, line: 3437, type: !22)
!4398 = !DILocation(line: 3437, column: 7, scope: !383)
!4399 = !DILocalVariable(name: "critical_flags", scope: !383, file: !1, line: 3438, type: !22)
!4400 = !DILocation(line: 3438, column: 7, scope: !383)
!4401 = !DILocalVariable(name: "mode", scope: !383, file: !1, line: 3439, type: !110)
!4402 = !DILocation(line: 3439, column: 10, scope: !383)
!4403 = !DILocation(line: 3439, column: 36, scope: !383)
!4404 = !DILocation(line: 3439, column: 39, scope: !383)
!4405 = !DILocation(line: 3439, column: 17, scope: !383)
!4406 = !DILocation(line: 3457, column: 17, scope: !383)
!4407 = !DILocation(line: 3471, column: 17, scope: !383)
!4408 = !DILocation(line: 3476, column: 17, scope: !383)
!4409 = !DILocation(line: 3481, column: 17, scope: !383)
!4410 = !DILocation(line: 3484, column: 6, scope: !4411)
!4411 = distinct !DILexicalBlock(scope: !383, file: !1, line: 3484, column: 6)
!4412 = !DILocation(line: 3484, column: 9, scope: !4411)
!4413 = !DILocation(line: 3484, column: 14, scope: !4411)
!4414 = !DILocation(line: 3484, column: 6, scope: !383)
!4415 = !DILocation(line: 3485, column: 24, scope: !4416)
!4416 = distinct !DILexicalBlock(scope: !4411, file: !1, line: 3484, column: 29)
!4417 = !DILocation(line: 3485, column: 27, scope: !4416)
!4418 = !DILocation(line: 3485, column: 3, scope: !4416)
!4419 = !DILocation(line: 3491, column: 8, scope: !4420)
!4420 = distinct !DILexicalBlock(scope: !4416, file: !1, line: 3491, column: 7)
!4421 = !DILocation(line: 3491, column: 23, scope: !4420)
!4422 = !DILocation(line: 3491, column: 30, scope: !4420)
!4423 = !DILocation(line: 3491, column: 35, scope: !4424)
!4424 = !DILexicalBlockFile(scope: !4420, file: !1, discriminator: 1)
!4425 = !DILocation(line: 3491, column: 41, scope: !4424)
!4426 = !DILocation(line: 3491, column: 39, scope: !4424)
!4427 = !DILocation(line: 3491, column: 7, scope: !4424)
!4428 = !DILocation(line: 3492, column: 23, scope: !4429)
!4429 = distinct !DILexicalBlock(scope: !4420, file: !1, line: 3491, column: 58)
!4430 = !DILocation(line: 3492, column: 26, scope: !4429)
!4431 = !DILocation(line: 3492, column: 29, scope: !4429)
!4432 = !DILocation(line: 3492, column: 9, scope: !4429)
!4433 = !DILocation(line: 3492, column: 7, scope: !4429)
!4434 = !DILocation(line: 3493, column: 8, scope: !4435)
!4435 = distinct !DILexicalBlock(scope: !4429, file: !1, line: 3493, column: 8)
!4436 = !DILocation(line: 3493, column: 11, scope: !4435)
!4437 = !DILocation(line: 3493, column: 8, scope: !4429)
!4438 = !DILocation(line: 3494, column: 5, scope: !4435)
!4439 = !DILocation(line: 3495, column: 4, scope: !4429)
!4440 = !DILocation(line: 3495, column: 8, scope: !4429)
!4441 = !DILocation(line: 3495, column: 14, scope: !4429)
!4442 = !DILocation(line: 3496, column: 21, scope: !4429)
!4443 = !DILocation(line: 3496, column: 4, scope: !4429)
!4444 = !DILocation(line: 3496, column: 8, scope: !4429)
!4445 = !DILocation(line: 3496, column: 19, scope: !4429)
!4446 = !DILocation(line: 3498, column: 9, scope: !4447)
!4447 = distinct !DILexicalBlock(scope: !4429, file: !1, line: 3498, column: 8)
!4448 = !DILocation(line: 3498, column: 13, scope: !4447)
!4449 = !DILocation(line: 3498, column: 19, scope: !4447)
!4450 = !DILocation(line: 3498, column: 32, scope: !4447)
!4451 = !DILocation(line: 3498, column: 8, scope: !4429)
!4452 = !DILocation(line: 3499, column: 16, scope: !4447)
!4453 = !DILocation(line: 3499, column: 5, scope: !4447)
!4454 = !DILocation(line: 3499, column: 9, scope: !4447)
!4455 = !DILocation(line: 3499, column: 14, scope: !4447)
!4456 = !DILocation(line: 3500, column: 3, scope: !4429)
!4457 = !DILocation(line: 3501, column: 28, scope: !4458)
!4458 = distinct !DILexicalBlock(scope: !4420, file: !1, line: 3500, column: 10)
!4459 = !DILocation(line: 3501, column: 31, scope: !4458)
!4460 = !DILocation(line: 3501, column: 34, scope: !4458)
!4461 = !DILocation(line: 3502, column: 8, scope: !4458)
!4462 = !DILocation(line: 3502, column: 11, scope: !4458)
!4463 = !DILocation(line: 3502, column: 17, scope: !4458)
!4464 = !DILocation(line: 3502, column: 23, scope: !4458)
!4465 = !DILocation(line: 3502, column: 28, scope: !4458)
!4466 = !DILocation(line: 3501, column: 8, scope: !4458)
!4467 = !DILocation(line: 3501, column: 6, scope: !4458)
!4468 = !DILocation(line: 3503, column: 8, scope: !4469)
!4469 = distinct !DILexicalBlock(scope: !4458, file: !1, line: 3503, column: 8)
!4470 = !DILocation(line: 3503, column: 10, scope: !4469)
!4471 = !DILocation(line: 3503, column: 8, scope: !4458)
!4472 = !DILocation(line: 3504, column: 13, scope: !4469)
!4473 = !DILocation(line: 3504, column: 5, scope: !4469)
!4474 = !DILocation(line: 3506, column: 2, scope: !4416)
!4475 = !DILocation(line: 3507, column: 2, scope: !383)
!4476 = !DILocation(line: 3508, column: 1, scope: !383)
!4477 = !DILocalVariable(name: "a", arg: 1, scope: !384, file: !1, line: 3275, type: !4)
!4478 = !DILocation(line: 3275, column: 49, scope: !384)
!4479 = !DILocalVariable(name: "atime", scope: !384, file: !1, line: 3277, type: !172)
!4480 = !DILocation(line: 3277, column: 9, scope: !384)
!4481 = !DILocalVariable(name: "birthtime", scope: !384, file: !1, line: 3277, type: !172)
!4482 = !DILocation(line: 3277, column: 16, scope: !384)
!4483 = !DILocalVariable(name: "mtime", scope: !384, file: !1, line: 3277, type: !172)
!4484 = !DILocation(line: 3277, column: 27, scope: !384)
!4485 = !DILocalVariable(name: "cctime", scope: !384, file: !1, line: 3277, type: !172)
!4486 = !DILocation(line: 3277, column: 34, scope: !384)
!4487 = !DILocalVariable(name: "atime_nsec", scope: !384, file: !1, line: 3278, type: !41)
!4488 = !DILocation(line: 3278, column: 7, scope: !384)
!4489 = !DILocalVariable(name: "birthtime_nsec", scope: !384, file: !1, line: 3278, type: !41)
!4490 = !DILocation(line: 3278, column: 19, scope: !384)
!4491 = !DILocalVariable(name: "mtime_nsec", scope: !384, file: !1, line: 3278, type: !41)
!4492 = !DILocation(line: 3278, column: 35, scope: !384)
!4493 = !DILocalVariable(name: "ctime_nsec", scope: !384, file: !1, line: 3278, type: !41)
!4494 = !DILocation(line: 3278, column: 47, scope: !384)
!4495 = !DILocation(line: 3281, column: 39, scope: !384)
!4496 = !DILocation(line: 3281, column: 42, scope: !384)
!4497 = !DILocation(line: 3281, column: 37, scope: !384)
!4498 = !DILocation(line: 3281, column: 28, scope: !384)
!4499 = !DILocation(line: 3281, column: 20, scope: !384)
!4500 = !DILocation(line: 3281, column: 8, scope: !384)
!4501 = !DILocation(line: 3282, column: 56, scope: !384)
!4502 = !DILocation(line: 3282, column: 43, scope: !384)
!4503 = !DILocation(line: 3282, column: 30, scope: !384)
!4504 = !DILocation(line: 3282, column: 13, scope: !384)
!4505 = !DILocation(line: 3285, column: 34, scope: !4506)
!4506 = distinct !DILexicalBlock(scope: !384, file: !1, line: 3285, column: 6)
!4507 = !DILocation(line: 3285, column: 37, scope: !4506)
!4508 = !DILocation(line: 3285, column: 7, scope: !4506)
!4509 = !DILocation(line: 3289, column: 6, scope: !4506)
!4510 = !DILocation(line: 3289, column: 37, scope: !4511)
!4511 = !DILexicalBlockFile(scope: !4506, file: !1, discriminator: 1)
!4512 = !DILocation(line: 3289, column: 40, scope: !4511)
!4513 = !DILocation(line: 3289, column: 10, scope: !4511)
!4514 = !DILocation(line: 3285, column: 6, scope: !4515)
!4515 = !DILexicalBlockFile(scope: !384, file: !1, discriminator: 1)
!4516 = !DILocation(line: 3290, column: 3, scope: !4506)
!4517 = !DILocation(line: 3292, column: 33, scope: !4518)
!4518 = distinct !DILexicalBlock(scope: !384, file: !1, line: 3292, column: 6)
!4519 = !DILocation(line: 3292, column: 36, scope: !4518)
!4520 = !DILocation(line: 3292, column: 6, scope: !4518)
!4521 = !DILocation(line: 3292, column: 6, scope: !384)
!4522 = !DILocation(line: 3293, column: 31, scope: !4523)
!4523 = distinct !DILexicalBlock(scope: !4518, file: !1, line: 3292, column: 44)
!4524 = !DILocation(line: 3293, column: 34, scope: !4523)
!4525 = !DILocation(line: 3293, column: 11, scope: !4523)
!4526 = !DILocation(line: 3293, column: 9, scope: !4523)
!4527 = !DILocation(line: 3294, column: 41, scope: !4523)
!4528 = !DILocation(line: 3294, column: 44, scope: !4523)
!4529 = !DILocation(line: 3294, column: 16, scope: !4523)
!4530 = !DILocation(line: 3294, column: 14, scope: !4523)
!4531 = !DILocation(line: 3295, column: 2, scope: !4523)
!4532 = !DILocation(line: 3296, column: 37, scope: !4533)
!4533 = distinct !DILexicalBlock(scope: !384, file: !1, line: 3296, column: 6)
!4534 = !DILocation(line: 3296, column: 40, scope: !4533)
!4535 = !DILocation(line: 3296, column: 6, scope: !4533)
!4536 = !DILocation(line: 3296, column: 6, scope: !384)
!4537 = !DILocation(line: 3297, column: 39, scope: !4538)
!4538 = distinct !DILexicalBlock(scope: !4533, file: !1, line: 3296, column: 48)
!4539 = !DILocation(line: 3297, column: 42, scope: !4538)
!4540 = !DILocation(line: 3297, column: 15, scope: !4538)
!4541 = !DILocation(line: 3297, column: 13, scope: !4538)
!4542 = !DILocation(line: 3298, column: 49, scope: !4538)
!4543 = !DILocation(line: 3298, column: 52, scope: !4538)
!4544 = !DILocation(line: 3298, column: 20, scope: !4538)
!4545 = !DILocation(line: 3298, column: 18, scope: !4538)
!4546 = !DILocation(line: 3299, column: 2, scope: !4538)
!4547 = !DILocation(line: 3300, column: 33, scope: !4548)
!4548 = distinct !DILexicalBlock(scope: !384, file: !1, line: 3300, column: 6)
!4549 = !DILocation(line: 3300, column: 36, scope: !4548)
!4550 = !DILocation(line: 3300, column: 6, scope: !4548)
!4551 = !DILocation(line: 3300, column: 6, scope: !384)
!4552 = !DILocation(line: 3301, column: 31, scope: !4553)
!4553 = distinct !DILexicalBlock(scope: !4548, file: !1, line: 3300, column: 44)
!4554 = !DILocation(line: 3301, column: 34, scope: !4553)
!4555 = !DILocation(line: 3301, column: 11, scope: !4553)
!4556 = !DILocation(line: 3301, column: 9, scope: !4553)
!4557 = !DILocation(line: 3302, column: 41, scope: !4553)
!4558 = !DILocation(line: 3302, column: 44, scope: !4553)
!4559 = !DILocation(line: 3302, column: 16, scope: !4553)
!4560 = !DILocation(line: 3302, column: 14, scope: !4553)
!4561 = !DILocation(line: 3303, column: 2, scope: !4553)
!4562 = !DILocation(line: 3304, column: 33, scope: !4563)
!4563 = distinct !DILexicalBlock(scope: !384, file: !1, line: 3304, column: 6)
!4564 = !DILocation(line: 3304, column: 36, scope: !4563)
!4565 = !DILocation(line: 3304, column: 6, scope: !4563)
!4566 = !DILocation(line: 3304, column: 6, scope: !384)
!4567 = !DILocation(line: 3305, column: 32, scope: !4568)
!4568 = distinct !DILexicalBlock(scope: !4563, file: !1, line: 3304, column: 44)
!4569 = !DILocation(line: 3305, column: 35, scope: !4568)
!4570 = !DILocation(line: 3305, column: 12, scope: !4568)
!4571 = !DILocation(line: 3305, column: 10, scope: !4568)
!4572 = !DILocation(line: 3306, column: 41, scope: !4568)
!4573 = !DILocation(line: 3306, column: 44, scope: !4568)
!4574 = !DILocation(line: 3306, column: 16, scope: !4568)
!4575 = !DILocation(line: 3306, column: 14, scope: !4568)
!4576 = !DILocation(line: 3307, column: 2, scope: !4568)
!4577 = !DILocation(line: 3309, column: 19, scope: !384)
!4578 = !DILocation(line: 3309, column: 22, scope: !384)
!4579 = !DILocation(line: 3309, column: 25, scope: !384)
!4580 = !DILocation(line: 3309, column: 29, scope: !384)
!4581 = !DILocation(line: 3309, column: 32, scope: !384)
!4582 = !DILocation(line: 3309, column: 38, scope: !384)
!4583 = !DILocation(line: 3309, column: 41, scope: !384)
!4584 = !DILocation(line: 3310, column: 5, scope: !384)
!4585 = !DILocation(line: 3310, column: 12, scope: !384)
!4586 = !DILocation(line: 3311, column: 5, scope: !384)
!4587 = !DILocation(line: 3311, column: 16, scope: !384)
!4588 = !DILocation(line: 3312, column: 5, scope: !384)
!4589 = !DILocation(line: 3312, column: 12, scope: !384)
!4590 = !DILocation(line: 3313, column: 5, scope: !384)
!4591 = !DILocation(line: 3313, column: 13, scope: !384)
!4592 = !DILocation(line: 3309, column: 9, scope: !384)
!4593 = !DILocation(line: 3309, column: 2, scope: !384)
!4594 = !DILocation(line: 3314, column: 1, scope: !384)
!4595 = !DILocalVariable(name: "a", arg: 1, scope: !386, file: !1, line: 1480, type: !4)
!4596 = !DILocation(line: 1480, column: 49, scope: !386)
!4597 = !DILocalVariable(name: "buff", arg: 2, scope: !386, file: !1, line: 1480, type: !79)
!4598 = !DILocation(line: 1480, column: 64, scope: !386)
!4599 = !DILocalVariable(name: "size", arg: 3, scope: !386, file: !1, line: 1481, type: !44)
!4600 = !DILocation(line: 1481, column: 12, scope: !386)
!4601 = !DILocation(line: 1483, column: 27, scope: !386)
!4602 = !DILocation(line: 1483, column: 30, scope: !386)
!4603 = !DILocation(line: 1483, column: 36, scope: !386)
!4604 = !DILocation(line: 1483, column: 10, scope: !386)
!4605 = !DILocation(line: 1483, column: 2, scope: !386)
!4606 = !DILocalVariable(name: "a", arg: 1, scope: !389, file: !1, line: 792, type: !4)
!4607 = !DILocation(line: 792, column: 45, scope: !389)
!4608 = !DILocalVariable(name: "buff", arg: 2, scope: !389, file: !1, line: 792, type: !79)
!4609 = !DILocation(line: 792, column: 60, scope: !389)
!4610 = !DILocalVariable(name: "size", arg: 3, scope: !389, file: !1, line: 792, type: !44)
!4611 = !DILocation(line: 792, column: 73, scope: !389)
!4612 = !DILocalVariable(name: "start_size", scope: !389, file: !1, line: 794, type: !301)
!4613 = !DILocation(line: 794, column: 11, scope: !389)
!4614 = !DILocation(line: 794, column: 24, scope: !389)
!4615 = !DILocalVariable(name: "bytes_written", scope: !389, file: !1, line: 795, type: !37)
!4616 = !DILocation(line: 795, column: 10, scope: !389)
!4617 = !DILocalVariable(name: "block_size", scope: !389, file: !1, line: 796, type: !37)
!4618 = !DILocation(line: 796, column: 10, scope: !389)
!4619 = !DILocalVariable(name: "bytes_to_write", scope: !389, file: !1, line: 796, type: !37)
!4620 = !DILocation(line: 796, column: 26, scope: !389)
!4621 = !DILocation(line: 798, column: 6, scope: !4622)
!4622 = distinct !DILexicalBlock(scope: !389, file: !1, line: 798, column: 6)
!4623 = !DILocation(line: 798, column: 11, scope: !4622)
!4624 = !DILocation(line: 798, column: 6, scope: !389)
!4625 = !DILocation(line: 799, column: 3, scope: !4622)
!4626 = !DILocation(line: 801, column: 6, scope: !4627)
!4627 = distinct !DILexicalBlock(scope: !389, file: !1, line: 801, column: 6)
!4628 = !DILocation(line: 801, column: 9, scope: !4627)
!4629 = !DILocation(line: 801, column: 18, scope: !4627)
!4630 = !DILocation(line: 801, column: 23, scope: !4627)
!4631 = !DILocation(line: 801, column: 26, scope: !4632)
!4632 = !DILexicalBlockFile(scope: !4627, file: !1, discriminator: 1)
!4633 = !DILocation(line: 801, column: 29, scope: !4632)
!4634 = !DILocation(line: 801, column: 32, scope: !4632)
!4635 = !DILocation(line: 801, column: 6, scope: !4632)
!4636 = !DILocation(line: 802, column: 22, scope: !4637)
!4637 = distinct !DILexicalBlock(scope: !4627, file: !1, line: 801, column: 37)
!4638 = !DILocation(line: 802, column: 25, scope: !4637)
!4639 = !DILocation(line: 802, column: 3, scope: !4637)
!4640 = !DILocation(line: 804, column: 3, scope: !4637)
!4641 = !DILocation(line: 807, column: 6, scope: !4642)
!4642 = distinct !DILexicalBlock(scope: !389, file: !1, line: 807, column: 6)
!4643 = !DILocation(line: 807, column: 9, scope: !4642)
!4644 = !DILocation(line: 807, column: 15, scope: !4642)
!4645 = !DILocation(line: 807, column: 6, scope: !389)
!4646 = !DILocalVariable(name: "r", scope: !4647, file: !1, line: 809, type: !22)
!4647 = distinct !DILexicalBlock(scope: !4642, file: !1, line: 807, column: 41)
!4648 = !DILocation(line: 809, column: 7, scope: !4647)
!4649 = !DILocation(line: 810, column: 22, scope: !4650)
!4650 = distinct !DILexicalBlock(scope: !4647, file: !1, line: 810, column: 7)
!4651 = !DILocation(line: 810, column: 12, scope: !4650)
!4652 = !DILocation(line: 810, column: 10, scope: !4650)
!4653 = !DILocation(line: 810, column: 26, scope: !4650)
!4654 = !DILocation(line: 810, column: 7, scope: !4647)
!4655 = !DILocation(line: 811, column: 12, scope: !4650)
!4656 = !DILocation(line: 811, column: 11, scope: !4650)
!4657 = !DILocation(line: 811, column: 4, scope: !4650)
!4658 = !DILocation(line: 812, column: 16, scope: !4647)
!4659 = !DILocation(line: 812, column: 19, scope: !4647)
!4660 = !DILocation(line: 812, column: 24, scope: !4647)
!4661 = !DILocation(line: 812, column: 14, scope: !4647)
!4662 = !DILocation(line: 818, column: 2, scope: !4647)
!4663 = !DILocation(line: 821, column: 6, scope: !4664)
!4664 = distinct !DILexicalBlock(scope: !389, file: !1, line: 821, column: 6)
!4665 = !DILocation(line: 821, column: 9, scope: !4664)
!4666 = !DILocation(line: 821, column: 18, scope: !4664)
!4667 = !DILocation(line: 821, column: 23, scope: !4664)
!4668 = !DILocation(line: 821, column: 36, scope: !4669)
!4669 = !DILexicalBlockFile(scope: !4664, file: !1, discriminator: 1)
!4670 = !DILocation(line: 821, column: 39, scope: !4669)
!4671 = !DILocation(line: 821, column: 48, scope: !4669)
!4672 = !DILocation(line: 821, column: 46, scope: !4669)
!4673 = !DILocation(line: 821, column: 56, scope: !4669)
!4674 = !DILocation(line: 821, column: 59, scope: !4669)
!4675 = !DILocation(line: 821, column: 54, scope: !4669)
!4676 = !DILocation(line: 821, column: 6, scope: !4669)
!4677 = !DILocation(line: 822, column: 32, scope: !4664)
!4678 = !DILocation(line: 822, column: 35, scope: !4664)
!4679 = !DILocation(line: 822, column: 46, scope: !4664)
!4680 = !DILocation(line: 822, column: 49, scope: !4664)
!4681 = !DILocation(line: 822, column: 44, scope: !4664)
!4682 = !DILocation(line: 822, column: 21, scope: !4664)
!4683 = !DILocation(line: 822, column: 14, scope: !4664)
!4684 = !DILocation(line: 822, column: 3, scope: !4664)
!4685 = !DILocation(line: 825, column: 2, scope: !389)
!4686 = !DILocation(line: 825, column: 9, scope: !4687)
!4687 = !DILexicalBlockFile(scope: !389, file: !1, discriminator: 1)
!4688 = !DILocation(line: 825, column: 14, scope: !4687)
!4689 = !DILocation(line: 825, column: 2, scope: !4687)
!4690 = !DILocation(line: 826, column: 7, scope: !4691)
!4691 = distinct !DILexicalBlock(scope: !4692, file: !1, line: 826, column: 7)
!4692 = distinct !DILexicalBlock(scope: !389, file: !1, line: 825, column: 19)
!4693 = !DILocation(line: 826, column: 18, scope: !4691)
!4694 = !DILocation(line: 826, column: 7, scope: !4692)
!4695 = !DILocation(line: 827, column: 21, scope: !4696)
!4696 = distinct !DILexicalBlock(scope: !4691, file: !1, line: 826, column: 24)
!4697 = !DILocation(line: 827, column: 19, scope: !4696)
!4698 = !DILocation(line: 828, column: 3, scope: !4696)
!4699 = !DILocalVariable(name: "p", scope: !4700, file: !1, line: 830, type: !79)
!4700 = distinct !DILexicalBlock(scope: !4691, file: !1, line: 828, column: 10)
!4701 = !DILocation(line: 830, column: 16, scope: !4700)
!4702 = !DILocalVariable(name: "end", scope: !4700, file: !1, line: 830, type: !79)
!4703 = !DILocation(line: 830, column: 20, scope: !4700)
!4704 = !DILocalVariable(name: "block_end", scope: !4700, file: !1, line: 831, type: !51)
!4705 = !DILocation(line: 831, column: 12, scope: !4700)
!4706 = !DILocation(line: 834, column: 13, scope: !4707)
!4707 = distinct !DILexicalBlock(scope: !4700, file: !1, line: 834, column: 4)
!4708 = !DILocation(line: 834, column: 11, scope: !4707)
!4709 = !DILocation(line: 834, column: 25, scope: !4707)
!4710 = !DILocation(line: 834, column: 32, scope: !4707)
!4711 = !DILocation(line: 834, column: 30, scope: !4707)
!4712 = !DILocation(line: 834, column: 23, scope: !4707)
!4713 = !DILocation(line: 834, column: 9, scope: !4707)
!4714 = !DILocation(line: 834, column: 38, scope: !4715)
!4715 = !DILexicalBlockFile(scope: !4716, file: !1, discriminator: 1)
!4716 = distinct !DILexicalBlock(scope: !4707, file: !1, line: 834, column: 4)
!4717 = !DILocation(line: 834, column: 42, scope: !4715)
!4718 = !DILocation(line: 834, column: 40, scope: !4715)
!4719 = !DILocation(line: 834, column: 4, scope: !4715)
!4720 = !DILocation(line: 835, column: 10, scope: !4721)
!4721 = distinct !DILexicalBlock(scope: !4722, file: !1, line: 835, column: 9)
!4722 = distinct !DILexicalBlock(scope: !4716, file: !1, line: 834, column: 52)
!4723 = !DILocation(line: 835, column: 9, scope: !4721)
!4724 = !DILocation(line: 835, column: 12, scope: !4721)
!4725 = !DILocation(line: 835, column: 9, scope: !4722)
!4726 = !DILocation(line: 836, column: 6, scope: !4721)
!4727 = !DILocation(line: 837, column: 4, scope: !4722)
!4728 = !DILocation(line: 834, column: 47, scope: !4729)
!4729 = !DILexicalBlockFile(scope: !4716, file: !1, discriminator: 2)
!4730 = !DILocation(line: 834, column: 4, scope: !4729)
!4731 = !DILocation(line: 838, column: 17, scope: !4700)
!4732 = !DILocation(line: 838, column: 21, scope: !4700)
!4733 = !DILocation(line: 838, column: 19, scope: !4700)
!4734 = !DILocation(line: 838, column: 4, scope: !4700)
!4735 = !DILocation(line: 838, column: 7, scope: !4700)
!4736 = !DILocation(line: 838, column: 14, scope: !4700)
!4737 = !DILocation(line: 839, column: 12, scope: !4700)
!4738 = !DILocation(line: 839, column: 16, scope: !4700)
!4739 = !DILocation(line: 839, column: 14, scope: !4700)
!4740 = !DILocation(line: 839, column: 9, scope: !4700)
!4741 = !DILocation(line: 840, column: 11, scope: !4700)
!4742 = !DILocation(line: 840, column: 9, scope: !4700)
!4743 = !DILocation(line: 841, column: 8, scope: !4744)
!4744 = distinct !DILexicalBlock(scope: !4700, file: !1, line: 841, column: 8)
!4745 = !DILocation(line: 841, column: 13, scope: !4744)
!4746 = !DILocation(line: 841, column: 8, scope: !4700)
!4747 = !DILocation(line: 842, column: 5, scope: !4744)
!4748 = !DILocation(line: 846, column: 11, scope: !4700)
!4749 = !DILocation(line: 846, column: 14, scope: !4700)
!4750 = !DILocation(line: 846, column: 23, scope: !4700)
!4751 = !DILocation(line: 846, column: 21, scope: !4700)
!4752 = !DILocation(line: 846, column: 34, scope: !4700)
!4753 = !DILocation(line: 846, column: 41, scope: !4700)
!4754 = !DILocation(line: 846, column: 39, scope: !4700)
!4755 = !DILocation(line: 846, column: 8, scope: !4700)
!4756 = !DILocation(line: 850, column: 21, scope: !4700)
!4757 = !DILocation(line: 850, column: 19, scope: !4700)
!4758 = !DILocation(line: 851, column: 8, scope: !4759)
!4759 = distinct !DILexicalBlock(scope: !4700, file: !1, line: 851, column: 8)
!4760 = !DILocation(line: 851, column: 11, scope: !4759)
!4761 = !DILocation(line: 851, column: 20, scope: !4759)
!4762 = !DILocation(line: 851, column: 18, scope: !4759)
!4763 = !DILocation(line: 851, column: 37, scope: !4759)
!4764 = !DILocation(line: 851, column: 35, scope: !4759)
!4765 = !DILocation(line: 851, column: 8, scope: !4700)
!4766 = !DILocation(line: 852, column: 22, scope: !4759)
!4767 = !DILocation(line: 852, column: 34, scope: !4759)
!4768 = !DILocation(line: 852, column: 37, scope: !4759)
!4769 = !DILocation(line: 852, column: 32, scope: !4759)
!4770 = !DILocation(line: 852, column: 20, scope: !4759)
!4771 = !DILocation(line: 852, column: 5, scope: !4759)
!4772 = !DILocation(line: 855, column: 7, scope: !4773)
!4773 = distinct !DILexicalBlock(scope: !4692, file: !1, line: 855, column: 7)
!4774 = !DILocation(line: 855, column: 10, scope: !4773)
!4775 = !DILocation(line: 855, column: 20, scope: !4773)
!4776 = !DILocation(line: 855, column: 23, scope: !4773)
!4777 = !DILocation(line: 855, column: 17, scope: !4773)
!4778 = !DILocation(line: 855, column: 7, scope: !4692)
!4779 = !DILocation(line: 856, column: 14, scope: !4780)
!4780 = distinct !DILexicalBlock(scope: !4781, file: !1, line: 856, column: 8)
!4781 = distinct !DILexicalBlock(scope: !4773, file: !1, line: 855, column: 34)
!4782 = !DILocation(line: 856, column: 17, scope: !4780)
!4783 = !DILocation(line: 856, column: 21, scope: !4780)
!4784 = !DILocation(line: 856, column: 24, scope: !4780)
!4785 = !DILocation(line: 856, column: 8, scope: !4780)
!4786 = !DILocation(line: 856, column: 42, scope: !4780)
!4787 = !DILocation(line: 856, column: 8, scope: !4781)
!4788 = !DILocation(line: 857, column: 24, scope: !4789)
!4789 = distinct !DILexicalBlock(scope: !4780, file: !1, line: 856, column: 47)
!4790 = !DILocation(line: 857, column: 27, scope: !4789)
!4791 = !DILocation(line: 857, column: 36, scope: !4789)
!4792 = !DILocation(line: 857, column: 5, scope: !4793)
!4793 = !DILexicalBlockFile(scope: !4789, file: !1, discriminator: 1)
!4794 = !DILocation(line: 859, column: 5, scope: !4789)
!4795 = !DILocation(line: 861, column: 19, scope: !4781)
!4796 = !DILocation(line: 861, column: 22, scope: !4781)
!4797 = !DILocation(line: 861, column: 4, scope: !4781)
!4798 = !DILocation(line: 861, column: 7, scope: !4781)
!4799 = !DILocation(line: 861, column: 17, scope: !4781)
!4800 = !DILocation(line: 862, column: 3, scope: !4781)
!4801 = !DILocation(line: 863, column: 25, scope: !4692)
!4802 = !DILocation(line: 863, column: 28, scope: !4692)
!4803 = !DILocation(line: 863, column: 32, scope: !4692)
!4804 = !DILocation(line: 863, column: 38, scope: !4692)
!4805 = !DILocation(line: 863, column: 19, scope: !4692)
!4806 = !DILocation(line: 863, column: 17, scope: !4692)
!4807 = !DILocation(line: 864, column: 7, scope: !4808)
!4808 = distinct !DILexicalBlock(scope: !4692, file: !1, line: 864, column: 7)
!4809 = !DILocation(line: 864, column: 21, scope: !4808)
!4810 = !DILocation(line: 864, column: 7, scope: !4692)
!4811 = !DILocation(line: 865, column: 23, scope: !4812)
!4812 = distinct !DILexicalBlock(scope: !4808, file: !1, line: 864, column: 26)
!4813 = !DILocation(line: 865, column: 26, scope: !4812)
!4814 = !DILocation(line: 865, column: 35, scope: !4812)
!4815 = !DILocation(line: 865, column: 4, scope: !4816)
!4816 = !DILexicalBlockFile(scope: !4812, file: !1, discriminator: 1)
!4817 = !DILocation(line: 866, column: 4, scope: !4812)
!4818 = !DILocation(line: 868, column: 11, scope: !4692)
!4819 = !DILocation(line: 868, column: 8, scope: !4692)
!4820 = !DILocation(line: 869, column: 11, scope: !4692)
!4821 = !DILocation(line: 869, column: 8, scope: !4692)
!4822 = !DILocation(line: 870, column: 29, scope: !4692)
!4823 = !DILocation(line: 870, column: 3, scope: !4692)
!4824 = !DILocation(line: 870, column: 6, scope: !4692)
!4825 = !DILocation(line: 870, column: 26, scope: !4692)
!4826 = !DILocation(line: 871, column: 16, scope: !4692)
!4827 = !DILocation(line: 871, column: 3, scope: !4692)
!4828 = !DILocation(line: 871, column: 6, scope: !4692)
!4829 = !DILocation(line: 871, column: 13, scope: !4692)
!4830 = !DILocation(line: 872, column: 18, scope: !4692)
!4831 = !DILocation(line: 872, column: 21, scope: !4692)
!4832 = !DILocation(line: 872, column: 3, scope: !4692)
!4833 = !DILocation(line: 872, column: 6, scope: !4692)
!4834 = !DILocation(line: 872, column: 16, scope: !4692)
!4835 = !DILocation(line: 825, column: 2, scope: !4836)
!4836 = !DILexicalBlockFile(scope: !389, file: !1, discriminator: 2)
!4837 = !DILocation(line: 874, column: 10, scope: !389)
!4838 = !DILocation(line: 874, column: 23, scope: !389)
!4839 = !DILocation(line: 874, column: 21, scope: !389)
!4840 = !DILocation(line: 874, column: 2, scope: !389)
!4841 = !DILocation(line: 875, column: 1, scope: !389)
