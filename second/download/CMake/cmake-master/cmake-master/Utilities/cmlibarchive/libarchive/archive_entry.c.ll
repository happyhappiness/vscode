; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_entry.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.flag = type { i8*, i32*, i64, i64 }
%struct.archive_entry = type { %struct.archive*, i8*, i32, %struct.aest, i32, %struct.archive_mstring, i64, i64, %struct.archive_mstring, %struct.archive_mstring, %struct.archive_mstring, %struct.archive_mstring, %struct.archive_mstring, %struct.archive_mstring, i8, i8*, i64, %struct.archive_acl, %struct.ae_xattr*, %struct.ae_xattr*, %struct.ae_sparse*, %struct.ae_sparse*, %struct.ae_sparse*, [12 x i8] }
%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { i32 (%struct.archive*)*, i32 (%struct.archive*)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)*, i8* (%struct.archive*, i32)* }
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque
%struct.aest = type { i64, i32, i64, i32, i64, i32, i64, i32, i64, i64, i32, i64, i64, i32, i64, i64, i64, i32, i64, i64, i64 }
%struct.archive_mstring = type { %struct.archive_string, %struct.archive_string, %struct.archive_wstring, %struct.archive_string, i32 }
%struct.archive_wstring = type { i32*, i64, i64 }
%struct.archive_acl = type { i32, %struct.archive_acl_entry*, %struct.archive_acl_entry*, i32, i32*, i8*, i32 }
%struct.archive_acl_entry = type { %struct.archive_acl_entry*, i32, i32, i32, i32, %struct.archive_mstring }
%struct.ae_xattr = type { %struct.ae_xattr*, i8*, i8*, i64 }
%struct.ae_sparse = type { %struct.ae_sparse*, i64, i64 }

@.str = private unnamed_addr constant [10 x i8] c"No memory\00", align 1
@flags = internal global [25 x %struct.flag] [%struct.flag { i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.1, i32 0, i32 0), i32* getelementptr inbounds ([9 x i32], [9 x i32]* @.str.2, i32 0, i32 0), i64 32, i64 0 }, %struct.flag { i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.3, i32 0, i32 0), i32* getelementptr inbounds ([10 x i32], [10 x i32]* @.str.4, i32 0, i32 0), i64 32, i64 0 }, %struct.flag { i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.5, i32 0, i32 0), i32* getelementptr inbounds ([7 x i32], [7 x i32]* @.str.6, i32 0, i32 0), i64 16, i64 0 }, %struct.flag { i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.7, i32 0, i32 0), i32* getelementptr inbounds ([10 x i32], [10 x i32]* @.str.8, i32 0, i32 0), i64 16, i64 0 }, %struct.flag { i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.9, i32 0, i32 0), i32* getelementptr inbounds ([13 x i32], [13 x i32]* @.str.10, i32 0, i32 0), i64 16, i64 0 }, %struct.flag { i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.11, i32 0, i32 0), i32* getelementptr inbounds ([7 x i32], [7 x i32]* @.str.12, i32 0, i32 0), i64 0, i64 64 }, %struct.flag { i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.13, i32 0, i32 0), i32* getelementptr inbounds ([10 x i32], [10 x i32]* @.str.14, i32 0, i32 0), i64 2, i64 0 }, %struct.flag { i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.15, i32 0, i32 0), i32* getelementptr inbounds ([8 x i32], [8 x i32]* @.str.16, i32 0, i32 0), i64 4096, i64 0 }, %struct.flag { i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.17, i32 0, i32 0), i32* getelementptr inbounds ([10 x i32], [10 x i32]* @.str.18, i32 0, i32 0), i64 2048, i64 0 }, %struct.flag { i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.19, i32 0, i32 0), i32* getelementptr inbounds ([11 x i32], [11 x i32]* @.str.20, i32 0, i32 0), i64 4, i64 0 }, %struct.flag { i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.21, i32 0, i32 0), i32* getelementptr inbounds ([8 x i32], [8 x i32]* @.str.22, i32 0, i32 0), i64 0, i64 128 }, %struct.flag { i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.23, i32 0, i32 0), i32* getelementptr inbounds ([12 x i32], [12 x i32]* @.str.24, i32 0, i32 0), i64 256, i64 0 }, %struct.flag { i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.25, i32 0, i32 0), i32* getelementptr inbounds ([11 x i32], [11 x i32]* @.str.26, i32 0, i32 0), i64 512, i64 0 }, %struct.flag { i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.27, i32 0, i32 0), i32* getelementptr inbounds ([10 x i32], [10 x i32]* @.str.28, i32 0, i32 0), i64 65536, i64 0 }, %struct.flag { i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.29, i32 0, i32 0), i32* getelementptr inbounds ([10 x i32], [10 x i32]* @.str.30, i32 0, i32 0), i64 4096, i64 0 }, %struct.flag { i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.31, i32 0, i32 0), i32* getelementptr inbounds ([9 x i32], [9 x i32]* @.str.32, i32 0, i32 0), i64 8192, i64 0 }, %struct.flag { i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.33, i32 0, i32 0), i32* getelementptr inbounds ([10 x i32], [10 x i32]* @.str.34, i32 0, i32 0), i64 16384, i64 0 }, %struct.flag { i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.35, i32 0, i32 0), i32* getelementptr inbounds ([17 x i32], [17 x i32]* @.str.36, i32 0, i32 0), i64 1, i64 0 }, %struct.flag { i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.37, i32 0, i32 0), i32* getelementptr inbounds ([7 x i32], [7 x i32]* @.str.38, i32 0, i32 0), i64 8, i64 0 }, %struct.flag { i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.39, i32 0, i32 0), i32* getelementptr inbounds ([7 x i32], [7 x i32]* @.str.40, i32 0, i32 0), i64 0, i64 32768 }, %struct.flag { i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.41, i32 0, i32 0), i32* getelementptr inbounds ([9 x i32], [9 x i32]* @.str.42, i32 0, i32 0), i64 131072, i64 0 }, %struct.flag { i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.43, i32 0, i32 0), i32* getelementptr inbounds ([9 x i32], [9 x i32]* @.str.44, i32 0, i32 0), i64 524288, i64 0 }, %struct.flag { i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.45, i32 0, i32 0), i32* getelementptr inbounds ([6 x i32], [6 x i32]* @.str.46, i32 0, i32 0), i64 8388608, i64 0 }, %struct.flag { i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.47, i32 0, i32 0), i32* getelementptr inbounds ([11 x i32], [11 x i32]* @.str.48, i32 0, i32 0), i64 2147483648, i64 0 }, %struct.flag zeroinitializer], align 16
@.str.1 = private unnamed_addr constant [9 x i8] c"nosappnd\00", align 1
@.str.2 = private unnamed_addr constant [9 x i32] [i32 110, i32 111, i32 115, i32 97, i32 112, i32 112, i32 110, i32 100, i32 0], align 4
@.str.3 = private unnamed_addr constant [10 x i8] c"nosappend\00", align 1
@.str.4 = private unnamed_addr constant [10 x i32] [i32 110, i32 111, i32 115, i32 97, i32 112, i32 112, i32 101, i32 110, i32 100, i32 0], align 4
@.str.5 = private unnamed_addr constant [7 x i8] c"noschg\00", align 1
@.str.6 = private unnamed_addr constant [7 x i32] [i32 110, i32 111, i32 115, i32 99, i32 104, i32 103, i32 0], align 4
@.str.7 = private unnamed_addr constant [10 x i8] c"noschange\00", align 1
@.str.8 = private unnamed_addr constant [10 x i32] [i32 110, i32 111, i32 115, i32 99, i32 104, i32 97, i32 110, i32 103, i32 101, i32 0], align 4
@.str.9 = private unnamed_addr constant [13 x i8] c"nosimmutable\00", align 1
@.str.10 = private unnamed_addr constant [13 x i32] [i32 110, i32 111, i32 115, i32 105, i32 109, i32 109, i32 117, i32 116, i32 97, i32 98, i32 108, i32 101, i32 0], align 4
@.str.11 = private unnamed_addr constant [7 x i8] c"nodump\00", align 1
@.str.12 = private unnamed_addr constant [7 x i32] [i32 110, i32 111, i32 100, i32 117, i32 109, i32 112, i32 0], align 4
@.str.13 = private unnamed_addr constant [10 x i8] c"nouunlink\00", align 1
@.str.14 = private unnamed_addr constant [10 x i32] [i32 110, i32 111, i32 117, i32 117, i32 110, i32 108, i32 105, i32 110, i32 107, i32 0], align 4
@.str.15 = private unnamed_addr constant [8 x i8] c"nobtree\00", align 1
@.str.16 = private unnamed_addr constant [8 x i32] [i32 110, i32 111, i32 98, i32 116, i32 114, i32 101, i32 101, i32 0], align 4
@.str.17 = private unnamed_addr constant [10 x i8] c"nocomperr\00", align 1
@.str.18 = private unnamed_addr constant [10 x i32] [i32 110, i32 111, i32 99, i32 111, i32 109, i32 112, i32 101, i32 114, i32 114, i32 0], align 4
@.str.19 = private unnamed_addr constant [11 x i8] c"nocompress\00", align 1
@.str.20 = private unnamed_addr constant [11 x i32] [i32 110, i32 111, i32 99, i32 111, i32 109, i32 112, i32 114, i32 101, i32 115, i32 115, i32 0], align 4
@.str.21 = private unnamed_addr constant [8 x i8] c"noatime\00", align 1
@.str.22 = private unnamed_addr constant [8 x i32] [i32 110, i32 111, i32 97, i32 116, i32 105, i32 109, i32 101, i32 0], align 4
@.str.23 = private unnamed_addr constant [12 x i8] c"nocompdirty\00", align 1
@.str.24 = private unnamed_addr constant [12 x i32] [i32 110, i32 111, i32 99, i32 111, i32 109, i32 112, i32 100, i32 105, i32 114, i32 116, i32 121, i32 0], align 4
@.str.25 = private unnamed_addr constant [11 x i8] c"nocomprblk\00", align 1
@.str.26 = private unnamed_addr constant [11 x i32] [i32 110, i32 111, i32 99, i32 111, i32 109, i32 112, i32 114, i32 98, i32 108, i32 107, i32 0], align 4
@.str.27 = private unnamed_addr constant [10 x i8] c"nodirsync\00", align 1
@.str.28 = private unnamed_addr constant [10 x i32] [i32 110, i32 111, i32 100, i32 105, i32 114, i32 115, i32 121, i32 110, i32 99, i32 0], align 4
@.str.29 = private unnamed_addr constant [10 x i8] c"nohashidx\00", align 1
@.str.30 = private unnamed_addr constant [10 x i32] [i32 110, i32 111, i32 104, i32 97, i32 115, i32 104, i32 105, i32 100, i32 120, i32 0], align 4
@.str.31 = private unnamed_addr constant [9 x i8] c"noimagic\00", align 1
@.str.32 = private unnamed_addr constant [9 x i32] [i32 110, i32 111, i32 105, i32 109, i32 97, i32 103, i32 105, i32 99, i32 0], align 4
@.str.33 = private unnamed_addr constant [10 x i8] c"nojournal\00", align 1
@.str.34 = private unnamed_addr constant [10 x i32] [i32 110, i32 111, i32 106, i32 111, i32 117, i32 114, i32 110, i32 97, i32 108, i32 0], align 4
@.str.35 = private unnamed_addr constant [17 x i8] c"nosecuredeletion\00", align 1
@.str.36 = private unnamed_addr constant [17 x i32] [i32 110, i32 111, i32 115, i32 101, i32 99, i32 117, i32 114, i32 101, i32 100, i32 101, i32 108, i32 101, i32 116, i32 105, i32 111, i32 110, i32 0], align 4
@.str.37 = private unnamed_addr constant [7 x i8] c"nosync\00", align 1
@.str.38 = private unnamed_addr constant [7 x i32] [i32 110, i32 111, i32 115, i32 121, i32 110, i32 99, i32 0], align 4
@.str.39 = private unnamed_addr constant [7 x i8] c"notail\00", align 1
@.str.40 = private unnamed_addr constant [7 x i32] [i32 110, i32 111, i32 116, i32 97, i32 105, i32 108, i32 0], align 4
@.str.41 = private unnamed_addr constant [9 x i8] c"notopdir\00", align 1
@.str.42 = private unnamed_addr constant [9 x i32] [i32 110, i32 111, i32 116, i32 111, i32 112, i32 100, i32 105, i32 114, i32 0], align 4
@.str.43 = private unnamed_addr constant [9 x i8] c"noextent\00", align 1
@.str.44 = private unnamed_addr constant [9 x i32] [i32 110, i32 111, i32 101, i32 120, i32 116, i32 101, i32 110, i32 116, i32 0], align 4
@.str.45 = private unnamed_addr constant [6 x i8] c"nocow\00", align 1
@.str.46 = private unnamed_addr constant [6 x i32] [i32 110, i32 111, i32 99, i32 111, i32 119, i32 0], align 4
@.str.47 = private unnamed_addr constant [11 x i8] c"noreserved\00", align 1
@.str.48 = private unnamed_addr constant [11 x i32] [i32 110, i32 111, i32 114, i32 101, i32 115, i32 101, i32 114, i32 118, i32 101, i32 100, i32 0], align 4

; Function Attrs: nounwind uwtable
define %struct.archive_entry* @archive_entry_clear(%struct.archive_entry* %entry1) #0 !dbg !212 {
entry:
  %retval = alloca %struct.archive_entry*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !485, metadata !486), !dbg !487
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !488
  %cmp = icmp eq %struct.archive_entry* %0, null, !dbg !490
  br i1 %cmp, label %if.then, label %if.end, !dbg !491

if.then:                                          ; preds = %entry
  store %struct.archive_entry* null, %struct.archive_entry** %retval, align 8, !dbg !492
  br label %return, !dbg !492

if.end:                                           ; preds = %entry
  %1 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !493
  %ae_fflags_text = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %1, i32 0, i32 5, !dbg !494
  call void @archive_mstring_clean(%struct.archive_mstring* %ae_fflags_text), !dbg !495
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !496
  %ae_gname = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 8, !dbg !497
  call void @archive_mstring_clean(%struct.archive_mstring* %ae_gname), !dbg !498
  %3 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !499
  %ae_hardlink = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %3, i32 0, i32 9, !dbg !500
  call void @archive_mstring_clean(%struct.archive_mstring* %ae_hardlink), !dbg !501
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !502
  %ae_pathname = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %4, i32 0, i32 10, !dbg !503
  call void @archive_mstring_clean(%struct.archive_mstring* %ae_pathname), !dbg !504
  %5 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !505
  %ae_sourcepath = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %5, i32 0, i32 13, !dbg !506
  call void @archive_mstring_clean(%struct.archive_mstring* %ae_sourcepath), !dbg !507
  %6 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !508
  %ae_symlink = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %6, i32 0, i32 11, !dbg !509
  call void @archive_mstring_clean(%struct.archive_mstring* %ae_symlink), !dbg !510
  %7 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !511
  %ae_uname = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %7, i32 0, i32 12, !dbg !512
  call void @archive_mstring_clean(%struct.archive_mstring* %ae_uname), !dbg !513
  %8 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !514
  call void @archive_entry_copy_mac_metadata(%struct.archive_entry* %8, i8* null, i64 0), !dbg !515
  %9 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !516
  %acl = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %9, i32 0, i32 17, !dbg !517
  call void @archive_acl_clear(%struct.archive_acl* %acl), !dbg !518
  %10 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !519
  call void @archive_entry_xattr_clear(%struct.archive_entry* %10), !dbg !520
  %11 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !521
  call void @archive_entry_sparse_clear(%struct.archive_entry* %11), !dbg !522
  %12 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !523
  %stat = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %12, i32 0, i32 1, !dbg !524
  %13 = load i8*, i8** %stat, align 8, !dbg !524
  call void @free(i8* %13) #9, !dbg !525
  %14 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !526
  %15 = bitcast %struct.archive_entry* %14 to i8*, !dbg !527
  call void @llvm.memset.p0i8.i64(i8* %15, i8 0, i64 1080, i32 8, i1 false), !dbg !527
  %16 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !528
  store %struct.archive_entry* %16, %struct.archive_entry** %retval, align 8, !dbg !529
  br label %return, !dbg !529

return:                                           ; preds = %if.end, %if.then
  %17 = load %struct.archive_entry*, %struct.archive_entry** %retval, align 8, !dbg !530
  ret %struct.archive_entry* %17, !dbg !530
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare void @archive_mstring_clean(%struct.archive_mstring*) #2

; Function Attrs: nounwind uwtable
define void @archive_entry_copy_mac_metadata(%struct.archive_entry* %entry1, i8* %p, i64 %s) #0 !dbg !409 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %p.addr = alloca i8*, align 8
  %s.addr = alloca i64, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !531, metadata !486), !dbg !532
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !533, metadata !486), !dbg !534
  store i64 %s, i64* %s.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %s.addr, metadata !535, metadata !486), !dbg !536
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !537
  %mac_metadata = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 15, !dbg !538
  %1 = load i8*, i8** %mac_metadata, align 8, !dbg !538
  call void @free(i8* %1) #9, !dbg !539
  %2 = load i8*, i8** %p.addr, align 8, !dbg !540
  %cmp = icmp eq i8* %2, null, !dbg !542
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !543

lor.lhs.false:                                    ; preds = %entry
  %3 = load i64, i64* %s.addr, align 8, !dbg !544
  %cmp2 = icmp eq i64 %3, 0, !dbg !546
  br i1 %cmp2, label %if.then, label %if.else, !dbg !547

if.then:                                          ; preds = %lor.lhs.false, %entry
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !548
  %mac_metadata3 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %4, i32 0, i32 15, !dbg !550
  store i8* null, i8** %mac_metadata3, align 8, !dbg !551
  %5 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !552
  %mac_metadata_size = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %5, i32 0, i32 16, !dbg !553
  store i64 0, i64* %mac_metadata_size, align 8, !dbg !554
  br label %if.end10, !dbg !555

if.else:                                          ; preds = %lor.lhs.false
  %6 = load i64, i64* %s.addr, align 8, !dbg !556
  %7 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !558
  %mac_metadata_size4 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %7, i32 0, i32 16, !dbg !559
  store i64 %6, i64* %mac_metadata_size4, align 8, !dbg !560
  %8 = load i64, i64* %s.addr, align 8, !dbg !561
  %call = call noalias i8* @malloc(i64 %8) #9, !dbg !562
  %9 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !563
  %mac_metadata5 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %9, i32 0, i32 15, !dbg !564
  store i8* %call, i8** %mac_metadata5, align 8, !dbg !565
  %10 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !566
  %mac_metadata6 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %10, i32 0, i32 15, !dbg !568
  %11 = load i8*, i8** %mac_metadata6, align 8, !dbg !568
  %cmp7 = icmp eq i8* %11, null, !dbg !569
  br i1 %cmp7, label %if.then8, label %if.end, !dbg !570

if.then8:                                         ; preds = %if.else
  call void @abort() #10, !dbg !571
  unreachable, !dbg !571

if.end:                                           ; preds = %if.else
  %12 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !572
  %mac_metadata9 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %12, i32 0, i32 15, !dbg !573
  %13 = load i8*, i8** %mac_metadata9, align 8, !dbg !573
  %14 = load i8*, i8** %p.addr, align 8, !dbg !574
  %15 = load i64, i64* %s.addr, align 8, !dbg !575
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %13, i8* %14, i64 %15, i32 1, i1 false), !dbg !576
  br label %if.end10

if.end10:                                         ; preds = %if.end, %if.then
  ret void, !dbg !577
}

declare void @archive_acl_clear(%struct.archive_acl*) #2

declare void @archive_entry_xattr_clear(%struct.archive_entry*) #2

declare void @archive_entry_sparse_clear(%struct.archive_entry*) #2

; Function Attrs: nounwind
declare void @free(i8*) #3

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #4

; Function Attrs: nounwind uwtable
define %struct.archive_entry* @archive_entry_clone(%struct.archive_entry* %entry1) #0 !dbg !215 {
entry:
  %retval = alloca %struct.archive_entry*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %entry2 = alloca %struct.archive_entry*, align 8
  %xp = alloca %struct.ae_xattr*, align 8
  %sp = alloca %struct.ae_sparse*, align 8
  %s = alloca i64, align 8
  %p = alloca i8*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !578, metadata !486), !dbg !579
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry2, metadata !580, metadata !486), !dbg !581
  call void @llvm.dbg.declare(metadata %struct.ae_xattr** %xp, metadata !582, metadata !486), !dbg !583
  call void @llvm.dbg.declare(metadata %struct.ae_sparse** %sp, metadata !584, metadata !486), !dbg !585
  call void @llvm.dbg.declare(metadata i64* %s, metadata !586, metadata !486), !dbg !587
  call void @llvm.dbg.declare(metadata i8** %p, metadata !588, metadata !486), !dbg !589
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !590
  %archive = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 0, !dbg !591
  %1 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !591
  %call = call %struct.archive_entry* @archive_entry_new2(%struct.archive* %1), !dbg !592
  store %struct.archive_entry* %call, %struct.archive_entry** %entry2, align 8, !dbg !593
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry2, align 8, !dbg !594
  %cmp = icmp eq %struct.archive_entry* %2, null, !dbg !596
  br i1 %cmp, label %if.then, label %if.end, !dbg !597

if.then:                                          ; preds = %entry
  store %struct.archive_entry* null, %struct.archive_entry** %retval, align 8, !dbg !598
  br label %return, !dbg !598

if.end:                                           ; preds = %entry
  %3 = load %struct.archive_entry*, %struct.archive_entry** %entry2, align 8, !dbg !599
  %ae_stat = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %3, i32 0, i32 3, !dbg !600
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !601
  %ae_stat2 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %4, i32 0, i32 3, !dbg !602
  %5 = bitcast %struct.aest* %ae_stat to i8*, !dbg !602
  %6 = bitcast %struct.aest* %ae_stat2 to i8*, !dbg !602
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %5, i8* %6, i64 168, i32 8, i1 false), !dbg !602
  %7 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !603
  %ae_fflags_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %7, i32 0, i32 6, !dbg !604
  %8 = load i64, i64* %ae_fflags_set, align 8, !dbg !604
  %9 = load %struct.archive_entry*, %struct.archive_entry** %entry2, align 8, !dbg !605
  %ae_fflags_set3 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %9, i32 0, i32 6, !dbg !606
  store i64 %8, i64* %ae_fflags_set3, align 8, !dbg !607
  %10 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !608
  %ae_fflags_clear = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %10, i32 0, i32 7, !dbg !609
  %11 = load i64, i64* %ae_fflags_clear, align 8, !dbg !609
  %12 = load %struct.archive_entry*, %struct.archive_entry** %entry2, align 8, !dbg !610
  %ae_fflags_clear4 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %12, i32 0, i32 7, !dbg !611
  store i64 %11, i64* %ae_fflags_clear4, align 8, !dbg !612
  %13 = load %struct.archive_entry*, %struct.archive_entry** %entry2, align 8, !dbg !613
  %ae_fflags_text = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %13, i32 0, i32 5, !dbg !614
  %14 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !615
  %ae_fflags_text5 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %14, i32 0, i32 5, !dbg !616
  call void @archive_mstring_copy(%struct.archive_mstring* %ae_fflags_text, %struct.archive_mstring* %ae_fflags_text5), !dbg !617
  %15 = load %struct.archive_entry*, %struct.archive_entry** %entry2, align 8, !dbg !618
  %ae_gname = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %15, i32 0, i32 8, !dbg !619
  %16 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !620
  %ae_gname6 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %16, i32 0, i32 8, !dbg !621
  call void @archive_mstring_copy(%struct.archive_mstring* %ae_gname, %struct.archive_mstring* %ae_gname6), !dbg !622
  %17 = load %struct.archive_entry*, %struct.archive_entry** %entry2, align 8, !dbg !623
  %ae_hardlink = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %17, i32 0, i32 9, !dbg !624
  %18 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !625
  %ae_hardlink7 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %18, i32 0, i32 9, !dbg !626
  call void @archive_mstring_copy(%struct.archive_mstring* %ae_hardlink, %struct.archive_mstring* %ae_hardlink7), !dbg !627
  %19 = load %struct.archive_entry*, %struct.archive_entry** %entry2, align 8, !dbg !628
  %ae_pathname = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %19, i32 0, i32 10, !dbg !629
  %20 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !630
  %ae_pathname8 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %20, i32 0, i32 10, !dbg !631
  call void @archive_mstring_copy(%struct.archive_mstring* %ae_pathname, %struct.archive_mstring* %ae_pathname8), !dbg !632
  %21 = load %struct.archive_entry*, %struct.archive_entry** %entry2, align 8, !dbg !633
  %ae_sourcepath = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %21, i32 0, i32 13, !dbg !634
  %22 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !635
  %ae_sourcepath9 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %22, i32 0, i32 13, !dbg !636
  call void @archive_mstring_copy(%struct.archive_mstring* %ae_sourcepath, %struct.archive_mstring* %ae_sourcepath9), !dbg !637
  %23 = load %struct.archive_entry*, %struct.archive_entry** %entry2, align 8, !dbg !638
  %ae_symlink = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %23, i32 0, i32 11, !dbg !639
  %24 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !640
  %ae_symlink10 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %24, i32 0, i32 11, !dbg !641
  call void @archive_mstring_copy(%struct.archive_mstring* %ae_symlink, %struct.archive_mstring* %ae_symlink10), !dbg !642
  %25 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !643
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %25, i32 0, i32 4, !dbg !644
  %26 = load i32, i32* %ae_set, align 8, !dbg !644
  %27 = load %struct.archive_entry*, %struct.archive_entry** %entry2, align 8, !dbg !645
  %ae_set11 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %27, i32 0, i32 4, !dbg !646
  store i32 %26, i32* %ae_set11, align 8, !dbg !647
  %28 = load %struct.archive_entry*, %struct.archive_entry** %entry2, align 8, !dbg !648
  %ae_uname = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %28, i32 0, i32 12, !dbg !649
  %29 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !650
  %ae_uname12 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %29, i32 0, i32 12, !dbg !651
  call void @archive_mstring_copy(%struct.archive_mstring* %ae_uname, %struct.archive_mstring* %ae_uname12), !dbg !652
  %30 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !653
  %encryption = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %30, i32 0, i32 14, !dbg !654
  %31 = load i8, i8* %encryption, align 8, !dbg !654
  %32 = load %struct.archive_entry*, %struct.archive_entry** %entry2, align 8, !dbg !655
  %encryption13 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %32, i32 0, i32 14, !dbg !656
  store i8 %31, i8* %encryption13, align 8, !dbg !657
  %33 = load %struct.archive_entry*, %struct.archive_entry** %entry2, align 8, !dbg !658
  %acl = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %33, i32 0, i32 17, !dbg !659
  %34 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !660
  %acl14 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %34, i32 0, i32 17, !dbg !661
  call void @archive_acl_copy(%struct.archive_acl* %acl, %struct.archive_acl* %acl14), !dbg !662
  %35 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !663
  %call15 = call i8* @archive_entry_mac_metadata(%struct.archive_entry* %35, i64* %s), !dbg !664
  store i8* %call15, i8** %p, align 8, !dbg !665
  %36 = load %struct.archive_entry*, %struct.archive_entry** %entry2, align 8, !dbg !666
  %37 = load i8*, i8** %p, align 8, !dbg !667
  %38 = load i64, i64* %s, align 8, !dbg !668
  call void @archive_entry_copy_mac_metadata(%struct.archive_entry* %36, i8* %37, i64 %38), !dbg !669
  %39 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !670
  %xattr_head = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %39, i32 0, i32 18, !dbg !671
  %40 = load %struct.ae_xattr*, %struct.ae_xattr** %xattr_head, align 8, !dbg !671
  store %struct.ae_xattr* %40, %struct.ae_xattr** %xp, align 8, !dbg !672
  br label %while.cond, !dbg !673

while.cond:                                       ; preds = %while.body, %if.end
  %41 = load %struct.ae_xattr*, %struct.ae_xattr** %xp, align 8, !dbg !674
  %cmp16 = icmp ne %struct.ae_xattr* %41, null, !dbg !676
  br i1 %cmp16, label %while.body, label %while.end, !dbg !677

while.body:                                       ; preds = %while.cond
  %42 = load %struct.archive_entry*, %struct.archive_entry** %entry2, align 8, !dbg !678
  %43 = load %struct.ae_xattr*, %struct.ae_xattr** %xp, align 8, !dbg !680
  %name = getelementptr inbounds %struct.ae_xattr, %struct.ae_xattr* %43, i32 0, i32 1, !dbg !681
  %44 = load i8*, i8** %name, align 8, !dbg !681
  %45 = load %struct.ae_xattr*, %struct.ae_xattr** %xp, align 8, !dbg !682
  %value = getelementptr inbounds %struct.ae_xattr, %struct.ae_xattr* %45, i32 0, i32 2, !dbg !683
  %46 = load i8*, i8** %value, align 8, !dbg !683
  %47 = load %struct.ae_xattr*, %struct.ae_xattr** %xp, align 8, !dbg !684
  %size = getelementptr inbounds %struct.ae_xattr, %struct.ae_xattr* %47, i32 0, i32 3, !dbg !685
  %48 = load i64, i64* %size, align 8, !dbg !685
  call void @archive_entry_xattr_add_entry(%struct.archive_entry* %42, i8* %44, i8* %46, i64 %48), !dbg !686
  %49 = load %struct.ae_xattr*, %struct.ae_xattr** %xp, align 8, !dbg !687
  %next = getelementptr inbounds %struct.ae_xattr, %struct.ae_xattr* %49, i32 0, i32 0, !dbg !688
  %50 = load %struct.ae_xattr*, %struct.ae_xattr** %next, align 8, !dbg !688
  store %struct.ae_xattr* %50, %struct.ae_xattr** %xp, align 8, !dbg !689
  br label %while.cond, !dbg !690

while.end:                                        ; preds = %while.cond
  %51 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !692
  %sparse_head = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %51, i32 0, i32 20, !dbg !693
  %52 = load %struct.ae_sparse*, %struct.ae_sparse** %sparse_head, align 8, !dbg !693
  store %struct.ae_sparse* %52, %struct.ae_sparse** %sp, align 8, !dbg !694
  br label %while.cond17, !dbg !695

while.cond17:                                     ; preds = %while.body19, %while.end
  %53 = load %struct.ae_sparse*, %struct.ae_sparse** %sp, align 8, !dbg !696
  %cmp18 = icmp ne %struct.ae_sparse* %53, null, !dbg !697
  br i1 %cmp18, label %while.body19, label %while.end21, !dbg !698

while.body19:                                     ; preds = %while.cond17
  %54 = load %struct.archive_entry*, %struct.archive_entry** %entry2, align 8, !dbg !699
  %55 = load %struct.ae_sparse*, %struct.ae_sparse** %sp, align 8, !dbg !701
  %offset = getelementptr inbounds %struct.ae_sparse, %struct.ae_sparse* %55, i32 0, i32 1, !dbg !702
  %56 = load i64, i64* %offset, align 8, !dbg !702
  %57 = load %struct.ae_sparse*, %struct.ae_sparse** %sp, align 8, !dbg !703
  %length = getelementptr inbounds %struct.ae_sparse, %struct.ae_sparse* %57, i32 0, i32 2, !dbg !704
  %58 = load i64, i64* %length, align 8, !dbg !704
  call void @archive_entry_sparse_add_entry(%struct.archive_entry* %54, i64 %56, i64 %58), !dbg !705
  %59 = load %struct.ae_sparse*, %struct.ae_sparse** %sp, align 8, !dbg !706
  %next20 = getelementptr inbounds %struct.ae_sparse, %struct.ae_sparse* %59, i32 0, i32 0, !dbg !707
  %60 = load %struct.ae_sparse*, %struct.ae_sparse** %next20, align 8, !dbg !707
  store %struct.ae_sparse* %60, %struct.ae_sparse** %sp, align 8, !dbg !708
  br label %while.cond17, !dbg !709

while.end21:                                      ; preds = %while.cond17
  %61 = load %struct.archive_entry*, %struct.archive_entry** %entry2, align 8, !dbg !710
  store %struct.archive_entry* %61, %struct.archive_entry** %retval, align 8, !dbg !711
  br label %return, !dbg !711

return:                                           ; preds = %while.end21, %if.then
  %62 = load %struct.archive_entry*, %struct.archive_entry** %retval, align 8, !dbg !712
  ret %struct.archive_entry* %62, !dbg !712
}

; Function Attrs: nounwind uwtable
define %struct.archive_entry* @archive_entry_new2(%struct.archive* %a) #0 !dbg !222 {
entry:
  %retval = alloca %struct.archive_entry*, align 8
  %a.addr = alloca %struct.archive*, align 8
  %entry1 = alloca %struct.archive_entry*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !713, metadata !486), !dbg !714
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry1, metadata !715, metadata !486), !dbg !716
  %call = call noalias i8* @calloc(i64 1, i64 1080) #9, !dbg !717
  %0 = bitcast i8* %call to %struct.archive_entry*, !dbg !718
  store %struct.archive_entry* %0, %struct.archive_entry** %entry1, align 8, !dbg !719
  %1 = load %struct.archive_entry*, %struct.archive_entry** %entry1, align 8, !dbg !720
  %cmp = icmp eq %struct.archive_entry* %1, null, !dbg !722
  br i1 %cmp, label %if.then, label %if.end, !dbg !723

if.then:                                          ; preds = %entry
  store %struct.archive_entry* null, %struct.archive_entry** %retval, align 8, !dbg !724
  br label %return, !dbg !724

if.end:                                           ; preds = %entry
  %2 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !725
  %3 = load %struct.archive_entry*, %struct.archive_entry** %entry1, align 8, !dbg !726
  %archive = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %3, i32 0, i32 0, !dbg !727
  store %struct.archive* %2, %struct.archive** %archive, align 8, !dbg !728
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry1, align 8, !dbg !729
  store %struct.archive_entry* %4, %struct.archive_entry** %retval, align 8, !dbg !730
  br label %return, !dbg !730

return:                                           ; preds = %if.end, %if.then
  %5 = load %struct.archive_entry*, %struct.archive_entry** %retval, align 8, !dbg !731
  ret %struct.archive_entry* %5, !dbg !731
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #4

declare void @archive_mstring_copy(%struct.archive_mstring*, %struct.archive_mstring*) #2

declare void @archive_acl_copy(%struct.archive_acl*, %struct.archive_acl*) #2

; Function Attrs: nounwind uwtable
define i8* @archive_entry_mac_metadata(%struct.archive_entry* %entry1, i64* %s) #0 !dbg !406 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %s.addr = alloca i64*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !732, metadata !486), !dbg !733
  store i64* %s, i64** %s.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %s.addr, metadata !734, metadata !486), !dbg !735
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !736
  %mac_metadata_size = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 16, !dbg !737
  %1 = load i64, i64* %mac_metadata_size, align 8, !dbg !737
  %2 = load i64*, i64** %s.addr, align 8, !dbg !738
  store i64 %1, i64* %2, align 8, !dbg !739
  %3 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !740
  %mac_metadata = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %3, i32 0, i32 15, !dbg !741
  %4 = load i8*, i8** %mac_metadata, align 8, !dbg !741
  ret i8* %4, !dbg !742
}

declare void @archive_entry_xattr_add_entry(%struct.archive_entry*, i8*, i8*, i64) #2

declare void @archive_entry_sparse_add_entry(%struct.archive_entry*, i64, i64) #2

; Function Attrs: nounwind uwtable
define void @archive_entry_free(%struct.archive_entry* %entry1) #0 !dbg !216 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !743, metadata !486), !dbg !744
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !745
  %call = call %struct.archive_entry* @archive_entry_clear(%struct.archive_entry* %0), !dbg !746
  %1 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !747
  %2 = bitcast %struct.archive_entry* %1 to i8*, !dbg !747
  call void @free(i8* %2) #9, !dbg !748
  ret void, !dbg !749
}

; Function Attrs: nounwind uwtable
define %struct.archive_entry* @archive_entry_new() #0 !dbg !219 {
entry:
  %call = call %struct.archive_entry* @archive_entry_new2(%struct.archive* null), !dbg !750
  ret %struct.archive_entry* %call, !dbg !751
}

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #3

; Function Attrs: nounwind uwtable
define i64 @archive_entry_atime(%struct.archive_entry* %entry1) #0 !dbg !225 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !752, metadata !486), !dbg !753
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !754
  %ae_stat = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 3, !dbg !755
  %aest_atime = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat, i32 0, i32 0, !dbg !756
  %1 = load i64, i64* %aest_atime, align 8, !dbg !756
  ret i64 %1, !dbg !757
}

; Function Attrs: nounwind uwtable
define i64 @archive_entry_atime_nsec(%struct.archive_entry* %entry1) #0 !dbg !231 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !758, metadata !486), !dbg !759
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !760
  %ae_stat = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 3, !dbg !761
  %aest_atime_nsec = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat, i32 0, i32 1, !dbg !762
  %1 = load i32, i32* %aest_atime_nsec, align 8, !dbg !762
  %conv = zext i32 %1 to i64, !dbg !763
  ret i64 %conv, !dbg !764
}

; Function Attrs: nounwind uwtable
define i32 @archive_entry_atime_is_set(%struct.archive_entry* %entry1) #0 !dbg !234 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !765, metadata !486), !dbg !766
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !767
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 4, !dbg !768
  %1 = load i32, i32* %ae_set, align 8, !dbg !768
  %and = and i32 %1, 4, !dbg !769
  ret i32 %and, !dbg !770
}

; Function Attrs: nounwind uwtable
define i64 @archive_entry_birthtime(%struct.archive_entry* %entry1) #0 !dbg !237 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !771, metadata !486), !dbg !772
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !773
  %ae_stat = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 3, !dbg !774
  %aest_birthtime = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat, i32 0, i32 6, !dbg !775
  %1 = load i64, i64* %aest_birthtime, align 8, !dbg !775
  ret i64 %1, !dbg !776
}

; Function Attrs: nounwind uwtable
define i64 @archive_entry_birthtime_nsec(%struct.archive_entry* %entry1) #0 !dbg !238 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !777, metadata !486), !dbg !778
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !779
  %ae_stat = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 3, !dbg !780
  %aest_birthtime_nsec = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat, i32 0, i32 7, !dbg !781
  %1 = load i32, i32* %aest_birthtime_nsec, align 8, !dbg !781
  %conv = zext i32 %1 to i64, !dbg !782
  ret i64 %conv, !dbg !783
}

; Function Attrs: nounwind uwtable
define i32 @archive_entry_birthtime_is_set(%struct.archive_entry* %entry1) #0 !dbg !239 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !784, metadata !486), !dbg !785
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !786
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 4, !dbg !787
  %1 = load i32, i32* %ae_set, align 8, !dbg !787
  %and = and i32 %1, 32, !dbg !788
  ret i32 %and, !dbg !789
}

; Function Attrs: nounwind uwtable
define i64 @archive_entry_ctime(%struct.archive_entry* %entry1) #0 !dbg !240 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !790, metadata !486), !dbg !791
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !792
  %ae_stat = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 3, !dbg !793
  %aest_ctime = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat, i32 0, i32 2, !dbg !794
  %1 = load i64, i64* %aest_ctime, align 8, !dbg !794
  ret i64 %1, !dbg !795
}

; Function Attrs: nounwind uwtable
define i32 @archive_entry_ctime_is_set(%struct.archive_entry* %entry1) #0 !dbg !241 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !796, metadata !486), !dbg !797
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !798
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 4, !dbg !799
  %1 = load i32, i32* %ae_set, align 8, !dbg !799
  %and = and i32 %1, 8, !dbg !800
  ret i32 %and, !dbg !801
}

; Function Attrs: nounwind uwtable
define i64 @archive_entry_ctime_nsec(%struct.archive_entry* %entry1) #0 !dbg !242 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !802, metadata !486), !dbg !803
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !804
  %ae_stat = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 3, !dbg !805
  %aest_ctime_nsec = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat, i32 0, i32 3, !dbg !806
  %1 = load i32, i32* %aest_ctime_nsec, align 8, !dbg !806
  %conv = zext i32 %1 to i64, !dbg !807
  ret i64 %conv, !dbg !808
}

; Function Attrs: nounwind uwtable
define i64 @archive_entry_dev(%struct.archive_entry* %entry1) #0 !dbg !243 {
entry:
  %retval = alloca i64, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !809, metadata !486), !dbg !810
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !811
  %ae_stat = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 3, !dbg !813
  %aest_dev_is_broken_down = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat, i32 0, i32 13, !dbg !814
  %1 = load i32, i32* %aest_dev_is_broken_down, align 8, !dbg !814
  %tobool = icmp ne i32 %1, 0, !dbg !811
  br i1 %tobool, label %if.then, label %if.else, !dbg !815

if.then:                                          ; preds = %entry
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !816
  %ae_stat2 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 3, !dbg !816
  %aest_devmajor = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat2, i32 0, i32 15, !dbg !816
  %3 = load i64, i64* %aest_devmajor, align 8, !dbg !816
  %conv = trunc i64 %3 to i32, !dbg !816
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !816
  %ae_stat3 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %4, i32 0, i32 3, !dbg !816
  %aest_devminor = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat3, i32 0, i32 16, !dbg !816
  %5 = load i64, i64* %aest_devminor, align 8, !dbg !816
  %conv4 = trunc i64 %5 to i32, !dbg !816
  %call = call i64 @gnu_dev_makedev(i32 %conv, i32 %conv4) #1, !dbg !816
  store i64 %call, i64* %retval, align 8, !dbg !817
  br label %return, !dbg !817

if.else:                                          ; preds = %entry
  %6 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !818
  %ae_stat5 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %6, i32 0, i32 3, !dbg !819
  %aest_dev = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat5, i32 0, i32 14, !dbg !820
  %7 = load i64, i64* %aest_dev, align 8, !dbg !820
  store i64 %7, i64* %retval, align 8, !dbg !821
  br label %return, !dbg !821

return:                                           ; preds = %if.else, %if.then
  %8 = load i64, i64* %retval, align 8, !dbg !822
  ret i64 %8, !dbg !822
}

; Function Attrs: nounwind readnone
declare i64 @gnu_dev_makedev(i32, i32) #5

; Function Attrs: nounwind uwtable
define i32 @archive_entry_dev_is_set(%struct.archive_entry* %entry1) #0 !dbg !246 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !823, metadata !486), !dbg !824
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !825
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 4, !dbg !826
  %1 = load i32, i32* %ae_set, align 8, !dbg !826
  %and = and i32 %1, 256, !dbg !827
  ret i32 %and, !dbg !828
}

; Function Attrs: nounwind uwtable
define i64 @archive_entry_devmajor(%struct.archive_entry* %entry1) #0 !dbg !247 {
entry:
  %retval = alloca i64, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !829, metadata !486), !dbg !830
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !831
  %ae_stat = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 3, !dbg !833
  %aest_dev_is_broken_down = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat, i32 0, i32 13, !dbg !834
  %1 = load i32, i32* %aest_dev_is_broken_down, align 8, !dbg !834
  %tobool = icmp ne i32 %1, 0, !dbg !831
  br i1 %tobool, label %if.then, label %if.else, !dbg !835

if.then:                                          ; preds = %entry
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !836
  %ae_stat2 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 3, !dbg !837
  %aest_devmajor = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat2, i32 0, i32 15, !dbg !838
  %3 = load i64, i64* %aest_devmajor, align 8, !dbg !838
  store i64 %3, i64* %retval, align 8, !dbg !839
  br label %return, !dbg !839

if.else:                                          ; preds = %entry
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !840
  %ae_stat3 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %4, i32 0, i32 3, !dbg !840
  %aest_dev = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat3, i32 0, i32 14, !dbg !840
  %5 = load i64, i64* %aest_dev, align 8, !dbg !840
  %call = call i32 @gnu_dev_major(i64 %5) #1, !dbg !840
  %conv = zext i32 %call to i64, !dbg !840
  store i64 %conv, i64* %retval, align 8, !dbg !841
  br label %return, !dbg !841

return:                                           ; preds = %if.else, %if.then
  %6 = load i64, i64* %retval, align 8, !dbg !842
  ret i64 %6, !dbg !842
}

; Function Attrs: nounwind readnone
declare i32 @gnu_dev_major(i64) #5

; Function Attrs: nounwind uwtable
define i64 @archive_entry_devminor(%struct.archive_entry* %entry1) #0 !dbg !248 {
entry:
  %retval = alloca i64, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !843, metadata !486), !dbg !844
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !845
  %ae_stat = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 3, !dbg !847
  %aest_dev_is_broken_down = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat, i32 0, i32 13, !dbg !848
  %1 = load i32, i32* %aest_dev_is_broken_down, align 8, !dbg !848
  %tobool = icmp ne i32 %1, 0, !dbg !845
  br i1 %tobool, label %if.then, label %if.else, !dbg !849

if.then:                                          ; preds = %entry
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !850
  %ae_stat2 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 3, !dbg !851
  %aest_devminor = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat2, i32 0, i32 16, !dbg !852
  %3 = load i64, i64* %aest_devminor, align 8, !dbg !852
  store i64 %3, i64* %retval, align 8, !dbg !853
  br label %return, !dbg !853

if.else:                                          ; preds = %entry
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !854
  %ae_stat3 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %4, i32 0, i32 3, !dbg !854
  %aest_dev = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat3, i32 0, i32 14, !dbg !854
  %5 = load i64, i64* %aest_dev, align 8, !dbg !854
  %call = call i32 @gnu_dev_minor(i64 %5) #1, !dbg !854
  %conv = zext i32 %call to i64, !dbg !854
  store i64 %conv, i64* %retval, align 8, !dbg !855
  br label %return, !dbg !855

return:                                           ; preds = %if.else, %if.then
  %6 = load i64, i64* %retval, align 8, !dbg !856
  ret i64 %6, !dbg !856
}

; Function Attrs: nounwind readnone
declare i32 @gnu_dev_minor(i64) #5

; Function Attrs: nounwind uwtable
define i32 @archive_entry_filetype(%struct.archive_entry* %entry1) #0 !dbg !249 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !857, metadata !486), !dbg !858
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !859
  %acl = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 17, !dbg !860
  %mode = getelementptr inbounds %struct.archive_acl, %struct.archive_acl* %acl, i32 0, i32 0, !dbg !861
  %1 = load i32, i32* %mode, align 8, !dbg !861
  %and = and i32 61440, %1, !dbg !862
  ret i32 %and, !dbg !863
}

; Function Attrs: nounwind uwtable
define void @archive_entry_fflags(%struct.archive_entry* %entry1, i64* %set, i64* %clear) #0 !dbg !252 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %set.addr = alloca i64*, align 8
  %clear.addr = alloca i64*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !864, metadata !486), !dbg !865
  store i64* %set, i64** %set.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %set.addr, metadata !866, metadata !486), !dbg !867
  store i64* %clear, i64** %clear.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %clear.addr, metadata !868, metadata !486), !dbg !869
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !870
  %ae_fflags_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 6, !dbg !871
  %1 = load i64, i64* %ae_fflags_set, align 8, !dbg !871
  %2 = load i64*, i64** %set.addr, align 8, !dbg !872
  store i64 %1, i64* %2, align 8, !dbg !873
  %3 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !874
  %ae_fflags_clear = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %3, i32 0, i32 7, !dbg !875
  %4 = load i64, i64* %ae_fflags_clear, align 8, !dbg !875
  %5 = load i64*, i64** %clear.addr, align 8, !dbg !876
  store i64 %4, i64* %5, align 8, !dbg !877
  ret void, !dbg !878
}

; Function Attrs: nounwind uwtable
define i8* @archive_entry_fflags_text(%struct.archive_entry* %entry1) #0 !dbg !256 {
entry:
  %retval = alloca i8*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %f = alloca i8*, align 8
  %p = alloca i8*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !879, metadata !486), !dbg !880
  call void @llvm.dbg.declare(metadata i8** %f, metadata !881, metadata !486), !dbg !882
  call void @llvm.dbg.declare(metadata i8** %p, metadata !883, metadata !486), !dbg !884
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !885
  %archive = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 0, !dbg !887
  %1 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !887
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !888
  %ae_fflags_text = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 5, !dbg !889
  %call = call i32 @archive_mstring_get_mbs(%struct.archive* %1, %struct.archive_mstring* %ae_fflags_text, i8** %f), !dbg !890
  %cmp = icmp eq i32 %call, 0, !dbg !891
  br i1 %cmp, label %if.then, label %if.else, !dbg !892

if.then:                                          ; preds = %entry
  %3 = load i8*, i8** %f, align 8, !dbg !893
  %cmp2 = icmp ne i8* %3, null, !dbg !896
  br i1 %cmp2, label %if.then3, label %if.end, !dbg !897

if.then3:                                         ; preds = %if.then
  %4 = load i8*, i8** %f, align 8, !dbg !898
  store i8* %4, i8** %retval, align 8, !dbg !899
  br label %return, !dbg !899

if.end:                                           ; preds = %if.then
  br label %if.end8, !dbg !900

if.else:                                          ; preds = %entry
  %call4 = call i32* @__errno_location() #1, !dbg !901
  %5 = load i32, i32* %call4, align 4, !dbg !901
  %cmp5 = icmp eq i32 %5, 12, !dbg !904
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !901

if.then6:                                         ; preds = %if.else
  call void @__archive_errx(i32 1, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0)) #11, !dbg !905
  unreachable, !dbg !905

if.end7:                                          ; preds = %if.else
  br label %if.end8

if.end8:                                          ; preds = %if.end7, %if.end
  %6 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !906
  %ae_fflags_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %6, i32 0, i32 6, !dbg !908
  %7 = load i64, i64* %ae_fflags_set, align 8, !dbg !908
  %cmp9 = icmp eq i64 %7, 0, !dbg !909
  br i1 %cmp9, label %land.lhs.true, label %if.end12, !dbg !910

land.lhs.true:                                    ; preds = %if.end8
  %8 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !911
  %ae_fflags_clear = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %8, i32 0, i32 7, !dbg !913
  %9 = load i64, i64* %ae_fflags_clear, align 8, !dbg !913
  %cmp10 = icmp eq i64 %9, 0, !dbg !914
  br i1 %cmp10, label %if.then11, label %if.end12, !dbg !915

if.then11:                                        ; preds = %land.lhs.true
  store i8* null, i8** %retval, align 8, !dbg !916
  br label %return, !dbg !916

if.end12:                                         ; preds = %land.lhs.true, %if.end8
  %10 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !917
  %ae_fflags_set13 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %10, i32 0, i32 6, !dbg !918
  %11 = load i64, i64* %ae_fflags_set13, align 8, !dbg !918
  %12 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !919
  %ae_fflags_clear14 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %12, i32 0, i32 7, !dbg !920
  %13 = load i64, i64* %ae_fflags_clear14, align 8, !dbg !920
  %call15 = call i8* @ae_fflagstostr(i64 %11, i64 %13), !dbg !921
  store i8* %call15, i8** %p, align 8, !dbg !922
  %14 = load i8*, i8** %p, align 8, !dbg !923
  %cmp16 = icmp eq i8* %14, null, !dbg !925
  br i1 %cmp16, label %if.then17, label %if.end18, !dbg !926

if.then17:                                        ; preds = %if.end12
  store i8* null, i8** %retval, align 8, !dbg !927
  br label %return, !dbg !927

if.end18:                                         ; preds = %if.end12
  %15 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !928
  %ae_fflags_text19 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %15, i32 0, i32 5, !dbg !929
  %16 = load i8*, i8** %p, align 8, !dbg !930
  %call20 = call i32 @archive_mstring_copy_mbs(%struct.archive_mstring* %ae_fflags_text19, i8* %16), !dbg !931
  %17 = load i8*, i8** %p, align 8, !dbg !932
  call void @free(i8* %17) #9, !dbg !933
  %18 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !934
  %archive21 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %18, i32 0, i32 0, !dbg !936
  %19 = load %struct.archive*, %struct.archive** %archive21, align 8, !dbg !936
  %20 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !937
  %ae_fflags_text22 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %20, i32 0, i32 5, !dbg !938
  %call23 = call i32 @archive_mstring_get_mbs(%struct.archive* %19, %struct.archive_mstring* %ae_fflags_text22, i8** %f), !dbg !939
  %cmp24 = icmp eq i32 %call23, 0, !dbg !940
  br i1 %cmp24, label %if.then25, label %if.end26, !dbg !941

if.then25:                                        ; preds = %if.end18
  %21 = load i8*, i8** %f, align 8, !dbg !942
  store i8* %21, i8** %retval, align 8, !dbg !943
  br label %return, !dbg !943

if.end26:                                         ; preds = %if.end18
  %call27 = call i32* @__errno_location() #1, !dbg !944
  %22 = load i32, i32* %call27, align 4, !dbg !944
  %cmp28 = icmp eq i32 %22, 12, !dbg !946
  br i1 %cmp28, label %if.then29, label %if.end30, !dbg !947

if.then29:                                        ; preds = %if.end26
  call void @__archive_errx(i32 1, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0)) #11, !dbg !948
  unreachable, !dbg !948

if.end30:                                         ; preds = %if.end26
  store i8* null, i8** %retval, align 8, !dbg !949
  br label %return, !dbg !949

return:                                           ; preds = %if.end30, %if.then25, %if.then17, %if.then11, %if.then3
  %23 = load i8*, i8** %retval, align 8, !dbg !950
  ret i8* %23, !dbg !950
}

declare i32 @archive_mstring_get_mbs(%struct.archive*, %struct.archive_mstring*, i8**) #2

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #5

; Function Attrs: noreturn
declare void @__archive_errx(i32, i8*) #6

; Function Attrs: nounwind uwtable
define internal i8* @ae_fflagstostr(i64 %bitset, i64 %bitclear) #0 !dbg !462 {
entry:
  %retval = alloca i8*, align 8
  %bitset.addr = alloca i64, align 8
  %bitclear.addr = alloca i64, align 8
  %string = alloca i8*, align 8
  %dp = alloca i8*, align 8
  %sp = alloca i8*, align 8
  %bits = alloca i64, align 8
  %flag = alloca %struct.flag*, align 8
  %length = alloca i64, align 8
  store i64 %bitset, i64* %bitset.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %bitset.addr, metadata !951, metadata !486), !dbg !952
  store i64 %bitclear, i64* %bitclear.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %bitclear.addr, metadata !953, metadata !486), !dbg !954
  call void @llvm.dbg.declare(metadata i8** %string, metadata !955, metadata !486), !dbg !956
  call void @llvm.dbg.declare(metadata i8** %dp, metadata !957, metadata !486), !dbg !958
  call void @llvm.dbg.declare(metadata i8** %sp, metadata !959, metadata !486), !dbg !960
  call void @llvm.dbg.declare(metadata i64* %bits, metadata !961, metadata !486), !dbg !962
  call void @llvm.dbg.declare(metadata %struct.flag** %flag, metadata !963, metadata !486), !dbg !965
  call void @llvm.dbg.declare(metadata i64* %length, metadata !966, metadata !486), !dbg !967
  %0 = load i64, i64* %bitset.addr, align 8, !dbg !968
  %1 = load i64, i64* %bitclear.addr, align 8, !dbg !969
  %or = or i64 %0, %1, !dbg !970
  store i64 %or, i64* %bits, align 8, !dbg !971
  store i64 0, i64* %length, align 8, !dbg !972
  store %struct.flag* getelementptr inbounds ([25 x %struct.flag], [25 x %struct.flag]* @flags, i32 0, i32 0), %struct.flag** %flag, align 8, !dbg !973
  br label %for.cond, !dbg !975

for.cond:                                         ; preds = %for.inc, %entry
  %2 = load %struct.flag*, %struct.flag** %flag, align 8, !dbg !976
  %name = getelementptr inbounds %struct.flag, %struct.flag* %2, i32 0, i32 0, !dbg !979
  %3 = load i8*, i8** %name, align 8, !dbg !979
  %cmp = icmp ne i8* %3, null, !dbg !980
  br i1 %cmp, label %for.body, label %for.end, !dbg !981

for.body:                                         ; preds = %for.cond
  %4 = load i64, i64* %bits, align 8, !dbg !982
  %5 = load %struct.flag*, %struct.flag** %flag, align 8, !dbg !984
  %set = getelementptr inbounds %struct.flag, %struct.flag* %5, i32 0, i32 2, !dbg !985
  %6 = load i64, i64* %set, align 8, !dbg !985
  %7 = load %struct.flag*, %struct.flag** %flag, align 8, !dbg !986
  %clear = getelementptr inbounds %struct.flag, %struct.flag* %7, i32 0, i32 3, !dbg !987
  %8 = load i64, i64* %clear, align 8, !dbg !987
  %or1 = or i64 %6, %8, !dbg !988
  %and = and i64 %4, %or1, !dbg !989
  %tobool = icmp ne i64 %and, 0, !dbg !989
  br i1 %tobool, label %if.then, label %if.end, !dbg !990

if.then:                                          ; preds = %for.body
  %9 = load %struct.flag*, %struct.flag** %flag, align 8, !dbg !991
  %name2 = getelementptr inbounds %struct.flag, %struct.flag* %9, i32 0, i32 0, !dbg !993
  %10 = load i8*, i8** %name2, align 8, !dbg !993
  %call = call i64 @strlen(i8* %10) #12, !dbg !994
  %add = add i64 %call, 1, !dbg !995
  %11 = load i64, i64* %length, align 8, !dbg !996
  %add3 = add i64 %11, %add, !dbg !996
  store i64 %add3, i64* %length, align 8, !dbg !996
  %12 = load %struct.flag*, %struct.flag** %flag, align 8, !dbg !997
  %set4 = getelementptr inbounds %struct.flag, %struct.flag* %12, i32 0, i32 2, !dbg !998
  %13 = load i64, i64* %set4, align 8, !dbg !998
  %14 = load %struct.flag*, %struct.flag** %flag, align 8, !dbg !999
  %clear5 = getelementptr inbounds %struct.flag, %struct.flag* %14, i32 0, i32 3, !dbg !1000
  %15 = load i64, i64* %clear5, align 8, !dbg !1000
  %or6 = or i64 %13, %15, !dbg !1001
  %neg = xor i64 %or6, -1, !dbg !1002
  %16 = load i64, i64* %bits, align 8, !dbg !1003
  %and7 = and i64 %16, %neg, !dbg !1003
  store i64 %and7, i64* %bits, align 8, !dbg !1003
  br label %if.end, !dbg !1004

if.end:                                           ; preds = %if.then, %for.body
  br label %for.inc, !dbg !1005

for.inc:                                          ; preds = %if.end
  %17 = load %struct.flag*, %struct.flag** %flag, align 8, !dbg !1007
  %incdec.ptr = getelementptr inbounds %struct.flag, %struct.flag* %17, i32 1, !dbg !1007
  store %struct.flag* %incdec.ptr, %struct.flag** %flag, align 8, !dbg !1007
  br label %for.cond, !dbg !1009

for.end:                                          ; preds = %for.cond
  %18 = load i64, i64* %length, align 8, !dbg !1010
  %cmp8 = icmp eq i64 %18, 0, !dbg !1012
  br i1 %cmp8, label %if.then9, label %if.end10, !dbg !1013

if.then9:                                         ; preds = %for.end
  store i8* null, i8** %retval, align 8, !dbg !1014
  br label %return, !dbg !1014

if.end10:                                         ; preds = %for.end
  %19 = load i64, i64* %length, align 8, !dbg !1015
  %call11 = call noalias i8* @malloc(i64 %19) #9, !dbg !1016
  store i8* %call11, i8** %string, align 8, !dbg !1017
  %20 = load i8*, i8** %string, align 8, !dbg !1018
  %cmp12 = icmp eq i8* %20, null, !dbg !1020
  br i1 %cmp12, label %if.then13, label %if.end14, !dbg !1021

if.then13:                                        ; preds = %if.end10
  store i8* null, i8** %retval, align 8, !dbg !1022
  br label %return, !dbg !1022

if.end14:                                         ; preds = %if.end10
  %21 = load i8*, i8** %string, align 8, !dbg !1023
  store i8* %21, i8** %dp, align 8, !dbg !1024
  store %struct.flag* getelementptr inbounds ([25 x %struct.flag], [25 x %struct.flag]* @flags, i32 0, i32 0), %struct.flag** %flag, align 8, !dbg !1025
  br label %for.cond15, !dbg !1027

for.cond15:                                       ; preds = %for.inc58, %if.end14
  %22 = load %struct.flag*, %struct.flag** %flag, align 8, !dbg !1028
  %name16 = getelementptr inbounds %struct.flag, %struct.flag* %22, i32 0, i32 0, !dbg !1031
  %23 = load i8*, i8** %name16, align 8, !dbg !1031
  %cmp17 = icmp ne i8* %23, null, !dbg !1032
  br i1 %cmp17, label %for.body18, label %for.end60, !dbg !1033

for.body18:                                       ; preds = %for.cond15
  %24 = load i64, i64* %bitset.addr, align 8, !dbg !1034
  %25 = load %struct.flag*, %struct.flag** %flag, align 8, !dbg !1037
  %set19 = getelementptr inbounds %struct.flag, %struct.flag* %25, i32 0, i32 2, !dbg !1038
  %26 = load i64, i64* %set19, align 8, !dbg !1038
  %and20 = and i64 %24, %26, !dbg !1039
  %tobool21 = icmp ne i64 %and20, 0, !dbg !1039
  br i1 %tobool21, label %if.then25, label %lor.lhs.false, !dbg !1040

lor.lhs.false:                                    ; preds = %for.body18
  %27 = load i64, i64* %bitclear.addr, align 8, !dbg !1041
  %28 = load %struct.flag*, %struct.flag** %flag, align 8, !dbg !1043
  %clear22 = getelementptr inbounds %struct.flag, %struct.flag* %28, i32 0, i32 3, !dbg !1044
  %29 = load i64, i64* %clear22, align 8, !dbg !1044
  %and23 = and i64 %27, %29, !dbg !1045
  %tobool24 = icmp ne i64 %and23, 0, !dbg !1045
  br i1 %tobool24, label %if.then25, label %if.else, !dbg !1046

if.then25:                                        ; preds = %lor.lhs.false, %for.body18
  %30 = load %struct.flag*, %struct.flag** %flag, align 8, !dbg !1047
  %name26 = getelementptr inbounds %struct.flag, %struct.flag* %30, i32 0, i32 0, !dbg !1049
  %31 = load i8*, i8** %name26, align 8, !dbg !1049
  %add.ptr = getelementptr inbounds i8, i8* %31, i64 2, !dbg !1050
  store i8* %add.ptr, i8** %sp, align 8, !dbg !1051
  br label %if.end38, !dbg !1052

if.else:                                          ; preds = %lor.lhs.false
  %32 = load i64, i64* %bitset.addr, align 8, !dbg !1053
  %33 = load %struct.flag*, %struct.flag** %flag, align 8, !dbg !1056
  %clear27 = getelementptr inbounds %struct.flag, %struct.flag* %33, i32 0, i32 3, !dbg !1057
  %34 = load i64, i64* %clear27, align 8, !dbg !1057
  %and28 = and i64 %32, %34, !dbg !1058
  %tobool29 = icmp ne i64 %and28, 0, !dbg !1058
  br i1 %tobool29, label %if.then34, label %lor.lhs.false30, !dbg !1059

lor.lhs.false30:                                  ; preds = %if.else
  %35 = load i64, i64* %bitclear.addr, align 8, !dbg !1060
  %36 = load %struct.flag*, %struct.flag** %flag, align 8, !dbg !1062
  %set31 = getelementptr inbounds %struct.flag, %struct.flag* %36, i32 0, i32 2, !dbg !1063
  %37 = load i64, i64* %set31, align 8, !dbg !1063
  %and32 = and i64 %35, %37, !dbg !1064
  %tobool33 = icmp ne i64 %and32, 0, !dbg !1064
  br i1 %tobool33, label %if.then34, label %if.else36, !dbg !1065

if.then34:                                        ; preds = %lor.lhs.false30, %if.else
  %38 = load %struct.flag*, %struct.flag** %flag, align 8, !dbg !1066
  %name35 = getelementptr inbounds %struct.flag, %struct.flag* %38, i32 0, i32 0, !dbg !1068
  %39 = load i8*, i8** %name35, align 8, !dbg !1068
  store i8* %39, i8** %sp, align 8, !dbg !1069
  br label %if.end37, !dbg !1070

if.else36:                                        ; preds = %lor.lhs.false30
  br label %for.inc58, !dbg !1071

if.end37:                                         ; preds = %if.then34
  br label %if.end38

if.end38:                                         ; preds = %if.end37, %if.then25
  %40 = load %struct.flag*, %struct.flag** %flag, align 8, !dbg !1072
  %set39 = getelementptr inbounds %struct.flag, %struct.flag* %40, i32 0, i32 2, !dbg !1073
  %41 = load i64, i64* %set39, align 8, !dbg !1073
  %42 = load %struct.flag*, %struct.flag** %flag, align 8, !dbg !1074
  %clear40 = getelementptr inbounds %struct.flag, %struct.flag* %42, i32 0, i32 3, !dbg !1075
  %43 = load i64, i64* %clear40, align 8, !dbg !1075
  %or41 = or i64 %41, %43, !dbg !1076
  %neg42 = xor i64 %or41, -1, !dbg !1077
  %44 = load i64, i64* %bitset.addr, align 8, !dbg !1078
  %and43 = and i64 %44, %neg42, !dbg !1078
  store i64 %and43, i64* %bitset.addr, align 8, !dbg !1078
  %45 = load %struct.flag*, %struct.flag** %flag, align 8, !dbg !1079
  %set44 = getelementptr inbounds %struct.flag, %struct.flag* %45, i32 0, i32 2, !dbg !1080
  %46 = load i64, i64* %set44, align 8, !dbg !1080
  %47 = load %struct.flag*, %struct.flag** %flag, align 8, !dbg !1081
  %clear45 = getelementptr inbounds %struct.flag, %struct.flag* %47, i32 0, i32 3, !dbg !1082
  %48 = load i64, i64* %clear45, align 8, !dbg !1082
  %or46 = or i64 %46, %48, !dbg !1083
  %neg47 = xor i64 %or46, -1, !dbg !1084
  %49 = load i64, i64* %bitclear.addr, align 8, !dbg !1085
  %and48 = and i64 %49, %neg47, !dbg !1085
  store i64 %and48, i64* %bitclear.addr, align 8, !dbg !1085
  %50 = load i8*, i8** %dp, align 8, !dbg !1086
  %51 = load i8*, i8** %string, align 8, !dbg !1088
  %cmp49 = icmp ugt i8* %50, %51, !dbg !1089
  br i1 %cmp49, label %if.then50, label %if.end52, !dbg !1090

if.then50:                                        ; preds = %if.end38
  %52 = load i8*, i8** %dp, align 8, !dbg !1091
  %incdec.ptr51 = getelementptr inbounds i8, i8* %52, i32 1, !dbg !1091
  store i8* %incdec.ptr51, i8** %dp, align 8, !dbg !1091
  store i8 44, i8* %52, align 1, !dbg !1092
  br label %if.end52, !dbg !1093

if.end52:                                         ; preds = %if.then50, %if.end38
  br label %while.cond, !dbg !1094

while.cond:                                       ; preds = %while.body, %if.end52
  %53 = load i8*, i8** %sp, align 8, !dbg !1095
  %incdec.ptr53 = getelementptr inbounds i8, i8* %53, i32 1, !dbg !1095
  store i8* %incdec.ptr53, i8** %sp, align 8, !dbg !1095
  %54 = load i8, i8* %53, align 1, !dbg !1097
  %55 = load i8*, i8** %dp, align 8, !dbg !1098
  %incdec.ptr54 = getelementptr inbounds i8, i8* %55, i32 1, !dbg !1098
  store i8* %incdec.ptr54, i8** %dp, align 8, !dbg !1098
  store i8 %54, i8* %55, align 1, !dbg !1099
  %conv = sext i8 %54 to i32, !dbg !1100
  %cmp55 = icmp ne i32 %conv, 0, !dbg !1101
  br i1 %cmp55, label %while.body, label %while.end, !dbg !1102

while.body:                                       ; preds = %while.cond
  br label %while.cond, !dbg !1103

while.end:                                        ; preds = %while.cond
  %56 = load i8*, i8** %dp, align 8, !dbg !1105
  %incdec.ptr57 = getelementptr inbounds i8, i8* %56, i32 -1, !dbg !1105
  store i8* %incdec.ptr57, i8** %dp, align 8, !dbg !1105
  br label %for.inc58, !dbg !1106

for.inc58:                                        ; preds = %while.end, %if.else36
  %57 = load %struct.flag*, %struct.flag** %flag, align 8, !dbg !1107
  %incdec.ptr59 = getelementptr inbounds %struct.flag, %struct.flag* %57, i32 1, !dbg !1107
  store %struct.flag* %incdec.ptr59, %struct.flag** %flag, align 8, !dbg !1107
  br label %for.cond15, !dbg !1109

for.end60:                                        ; preds = %for.cond15
  %58 = load i8*, i8** %dp, align 8, !dbg !1110
  store i8 0, i8* %58, align 1, !dbg !1111
  %59 = load i8*, i8** %string, align 8, !dbg !1112
  store i8* %59, i8** %retval, align 8, !dbg !1113
  br label %return, !dbg !1113

return:                                           ; preds = %for.end60, %if.then13, %if.then9
  %60 = load i8*, i8** %retval, align 8, !dbg !1114
  ret i8* %60, !dbg !1114
}

declare i32 @archive_mstring_copy_mbs(%struct.archive_mstring*, i8*) #2

; Function Attrs: nounwind uwtable
define i64 @archive_entry_gid(%struct.archive_entry* %entry1) #0 !dbg !259 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1115, metadata !486), !dbg !1116
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1117
  %ae_stat = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 3, !dbg !1118
  %aest_gid = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat, i32 0, i32 8, !dbg !1119
  %1 = load i64, i64* %aest_gid, align 8, !dbg !1119
  ret i64 %1, !dbg !1120
}

; Function Attrs: nounwind uwtable
define i8* @archive_entry_gname(%struct.archive_entry* %entry1) #0 !dbg !264 {
entry:
  %retval = alloca i8*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %p = alloca i8*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1121, metadata !486), !dbg !1122
  call void @llvm.dbg.declare(metadata i8** %p, metadata !1123, metadata !486), !dbg !1124
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1125
  %archive = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 0, !dbg !1127
  %1 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !1127
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1128
  %ae_gname = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 8, !dbg !1129
  %call = call i32 @archive_mstring_get_mbs(%struct.archive* %1, %struct.archive_mstring* %ae_gname, i8** %p), !dbg !1130
  %cmp = icmp eq i32 %call, 0, !dbg !1131
  br i1 %cmp, label %if.then, label %if.end, !dbg !1132

if.then:                                          ; preds = %entry
  %3 = load i8*, i8** %p, align 8, !dbg !1133
  store i8* %3, i8** %retval, align 8, !dbg !1134
  br label %return, !dbg !1134

if.end:                                           ; preds = %entry
  %call2 = call i32* @__errno_location() #1, !dbg !1135
  %4 = load i32, i32* %call2, align 4, !dbg !1135
  %cmp3 = icmp eq i32 %4, 12, !dbg !1137
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !1138

if.then4:                                         ; preds = %if.end
  call void @__archive_errx(i32 1, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0)) #11, !dbg !1139
  unreachable, !dbg !1139

if.end5:                                          ; preds = %if.end
  store i8* null, i8** %retval, align 8, !dbg !1140
  br label %return, !dbg !1140

return:                                           ; preds = %if.end5, %if.then
  %5 = load i8*, i8** %retval, align 8, !dbg !1141
  ret i8* %5, !dbg !1141
}

; Function Attrs: nounwind uwtable
define i8* @archive_entry_gname_utf8(%struct.archive_entry* %entry1) #0 !dbg !265 {
entry:
  %retval = alloca i8*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %p = alloca i8*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1142, metadata !486), !dbg !1143
  call void @llvm.dbg.declare(metadata i8** %p, metadata !1144, metadata !486), !dbg !1145
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1146
  %archive = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 0, !dbg !1148
  %1 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !1148
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1149
  %ae_gname = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 8, !dbg !1150
  %call = call i32 @archive_mstring_get_utf8(%struct.archive* %1, %struct.archive_mstring* %ae_gname, i8** %p), !dbg !1151
  %cmp = icmp eq i32 %call, 0, !dbg !1152
  br i1 %cmp, label %if.then, label %if.end, !dbg !1153

if.then:                                          ; preds = %entry
  %3 = load i8*, i8** %p, align 8, !dbg !1154
  store i8* %3, i8** %retval, align 8, !dbg !1155
  br label %return, !dbg !1155

if.end:                                           ; preds = %entry
  %call2 = call i32* @__errno_location() #1, !dbg !1156
  %4 = load i32, i32* %call2, align 4, !dbg !1156
  %cmp3 = icmp eq i32 %4, 12, !dbg !1158
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !1159

if.then4:                                         ; preds = %if.end
  call void @__archive_errx(i32 1, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0)) #11, !dbg !1160
  unreachable, !dbg !1160

if.end5:                                          ; preds = %if.end
  store i8* null, i8** %retval, align 8, !dbg !1161
  br label %return, !dbg !1161

return:                                           ; preds = %if.end5, %if.then
  %5 = load i8*, i8** %retval, align 8, !dbg !1162
  ret i8* %5, !dbg !1162
}

declare i32 @archive_mstring_get_utf8(%struct.archive*, %struct.archive_mstring*, i8**) #2

; Function Attrs: nounwind uwtable
define i32* @archive_entry_gname_w(%struct.archive_entry* %entry1) #0 !dbg !266 {
entry:
  %retval = alloca i32*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %p = alloca i32*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1163, metadata !486), !dbg !1164
  call void @llvm.dbg.declare(metadata i32** %p, metadata !1165, metadata !486), !dbg !1166
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1167
  %archive = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 0, !dbg !1169
  %1 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !1169
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1170
  %ae_gname = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 8, !dbg !1171
  %call = call i32 @archive_mstring_get_wcs(%struct.archive* %1, %struct.archive_mstring* %ae_gname, i32** %p), !dbg !1172
  %cmp = icmp eq i32 %call, 0, !dbg !1173
  br i1 %cmp, label %if.then, label %if.end, !dbg !1174

if.then:                                          ; preds = %entry
  %3 = load i32*, i32** %p, align 8, !dbg !1175
  store i32* %3, i32** %retval, align 8, !dbg !1176
  br label %return, !dbg !1176

if.end:                                           ; preds = %entry
  %call2 = call i32* @__errno_location() #1, !dbg !1177
  %4 = load i32, i32* %call2, align 4, !dbg !1177
  %cmp3 = icmp eq i32 %4, 12, !dbg !1179
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !1180

if.then4:                                         ; preds = %if.end
  call void @__archive_errx(i32 1, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0)) #11, !dbg !1181
  unreachable, !dbg !1181

if.end5:                                          ; preds = %if.end
  store i32* null, i32** %retval, align 8, !dbg !1182
  br label %return, !dbg !1182

return:                                           ; preds = %if.end5, %if.then
  %5 = load i32*, i32** %retval, align 8, !dbg !1183
  ret i32* %5, !dbg !1183
}

declare i32 @archive_mstring_get_wcs(%struct.archive*, %struct.archive_mstring*, i32**) #2

; Function Attrs: nounwind uwtable
define i32 @_archive_entry_gname_l(%struct.archive_entry* %entry1, i8** %p, i64* %len, %struct.archive_string_conv* %sc) #0 !dbg !271 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %p.addr = alloca i8**, align 8
  %len.addr = alloca i64*, align 8
  %sc.addr = alloca %struct.archive_string_conv*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1184, metadata !486), !dbg !1185
  store i8** %p, i8*** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %p.addr, metadata !1186, metadata !486), !dbg !1187
  store i64* %len, i64** %len.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %len.addr, metadata !1188, metadata !486), !dbg !1189
  store %struct.archive_string_conv* %sc, %struct.archive_string_conv** %sc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string_conv** %sc.addr, metadata !1190, metadata !486), !dbg !1191
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1192
  %ae_gname = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 8, !dbg !1193
  %1 = load i8**, i8*** %p.addr, align 8, !dbg !1194
  %2 = load i64*, i64** %len.addr, align 8, !dbg !1195
  %3 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sc.addr, align 8, !dbg !1196
  %call = call i32 @archive_mstring_get_mbs_l(%struct.archive_mstring* %ae_gname, i8** %1, i64* %2, %struct.archive_string_conv* %3), !dbg !1197
  ret i32 %call, !dbg !1198
}

declare i32 @archive_mstring_get_mbs_l(%struct.archive_mstring*, i8**, i64*, %struct.archive_string_conv*) #2

; Function Attrs: nounwind uwtable
define i8* @archive_entry_hardlink(%struct.archive_entry* %entry1) #0 !dbg !275 {
entry:
  %retval = alloca i8*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %p = alloca i8*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1199, metadata !486), !dbg !1200
  call void @llvm.dbg.declare(metadata i8** %p, metadata !1201, metadata !486), !dbg !1202
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1203
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 4, !dbg !1205
  %1 = load i32, i32* %ae_set, align 8, !dbg !1205
  %and = and i32 %1, 1, !dbg !1206
  %cmp = icmp eq i32 %and, 0, !dbg !1207
  br i1 %cmp, label %if.then, label %if.end, !dbg !1208

if.then:                                          ; preds = %entry
  store i8* null, i8** %retval, align 8, !dbg !1209
  br label %return, !dbg !1209

if.end:                                           ; preds = %entry
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1210
  %archive = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 0, !dbg !1212
  %3 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !1212
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1213
  %ae_hardlink = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %4, i32 0, i32 9, !dbg !1214
  %call = call i32 @archive_mstring_get_mbs(%struct.archive* %3, %struct.archive_mstring* %ae_hardlink, i8** %p), !dbg !1215
  %cmp2 = icmp eq i32 %call, 0, !dbg !1216
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !1217

if.then3:                                         ; preds = %if.end
  %5 = load i8*, i8** %p, align 8, !dbg !1218
  store i8* %5, i8** %retval, align 8, !dbg !1219
  br label %return, !dbg !1219

if.end4:                                          ; preds = %if.end
  %call5 = call i32* @__errno_location() #1, !dbg !1220
  %6 = load i32, i32* %call5, align 4, !dbg !1220
  %cmp6 = icmp eq i32 %6, 12, !dbg !1222
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !1223

if.then7:                                         ; preds = %if.end4
  call void @__archive_errx(i32 1, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0)) #11, !dbg !1224
  unreachable, !dbg !1224

if.end8:                                          ; preds = %if.end4
  store i8* null, i8** %retval, align 8, !dbg !1225
  br label %return, !dbg !1225

return:                                           ; preds = %if.end8, %if.then3, %if.then
  %7 = load i8*, i8** %retval, align 8, !dbg !1226
  ret i8* %7, !dbg !1226
}

; Function Attrs: nounwind uwtable
define i8* @archive_entry_hardlink_utf8(%struct.archive_entry* %entry1) #0 !dbg !276 {
entry:
  %retval = alloca i8*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %p = alloca i8*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1227, metadata !486), !dbg !1228
  call void @llvm.dbg.declare(metadata i8** %p, metadata !1229, metadata !486), !dbg !1230
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1231
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 4, !dbg !1233
  %1 = load i32, i32* %ae_set, align 8, !dbg !1233
  %and = and i32 %1, 1, !dbg !1234
  %cmp = icmp eq i32 %and, 0, !dbg !1235
  br i1 %cmp, label %if.then, label %if.end, !dbg !1236

if.then:                                          ; preds = %entry
  store i8* null, i8** %retval, align 8, !dbg !1237
  br label %return, !dbg !1237

if.end:                                           ; preds = %entry
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1238
  %archive = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 0, !dbg !1240
  %3 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !1240
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1241
  %ae_hardlink = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %4, i32 0, i32 9, !dbg !1242
  %call = call i32 @archive_mstring_get_utf8(%struct.archive* %3, %struct.archive_mstring* %ae_hardlink, i8** %p), !dbg !1243
  %cmp2 = icmp eq i32 %call, 0, !dbg !1244
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !1245

if.then3:                                         ; preds = %if.end
  %5 = load i8*, i8** %p, align 8, !dbg !1246
  store i8* %5, i8** %retval, align 8, !dbg !1247
  br label %return, !dbg !1247

if.end4:                                          ; preds = %if.end
  %call5 = call i32* @__errno_location() #1, !dbg !1248
  %6 = load i32, i32* %call5, align 4, !dbg !1248
  %cmp6 = icmp eq i32 %6, 12, !dbg !1250
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !1251

if.then7:                                         ; preds = %if.end4
  call void @__archive_errx(i32 1, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0)) #11, !dbg !1252
  unreachable, !dbg !1252

if.end8:                                          ; preds = %if.end4
  store i8* null, i8** %retval, align 8, !dbg !1253
  br label %return, !dbg !1253

return:                                           ; preds = %if.end8, %if.then3, %if.then
  %7 = load i8*, i8** %retval, align 8, !dbg !1254
  ret i8* %7, !dbg !1254
}

; Function Attrs: nounwind uwtable
define i32* @archive_entry_hardlink_w(%struct.archive_entry* %entry1) #0 !dbg !277 {
entry:
  %retval = alloca i32*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %p = alloca i32*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1255, metadata !486), !dbg !1256
  call void @llvm.dbg.declare(metadata i32** %p, metadata !1257, metadata !486), !dbg !1258
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1259
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 4, !dbg !1261
  %1 = load i32, i32* %ae_set, align 8, !dbg !1261
  %and = and i32 %1, 1, !dbg !1262
  %cmp = icmp eq i32 %and, 0, !dbg !1263
  br i1 %cmp, label %if.then, label %if.end, !dbg !1264

if.then:                                          ; preds = %entry
  store i32* null, i32** %retval, align 8, !dbg !1265
  br label %return, !dbg !1265

if.end:                                           ; preds = %entry
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1266
  %archive = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 0, !dbg !1268
  %3 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !1268
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1269
  %ae_hardlink = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %4, i32 0, i32 9, !dbg !1270
  %call = call i32 @archive_mstring_get_wcs(%struct.archive* %3, %struct.archive_mstring* %ae_hardlink, i32** %p), !dbg !1271
  %cmp2 = icmp eq i32 %call, 0, !dbg !1272
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !1273

if.then3:                                         ; preds = %if.end
  %5 = load i32*, i32** %p, align 8, !dbg !1274
  store i32* %5, i32** %retval, align 8, !dbg !1275
  br label %return, !dbg !1275

if.end4:                                          ; preds = %if.end
  %call5 = call i32* @__errno_location() #1, !dbg !1276
  %6 = load i32, i32* %call5, align 4, !dbg !1276
  %cmp6 = icmp eq i32 %6, 12, !dbg !1278
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !1279

if.then7:                                         ; preds = %if.end4
  call void @__archive_errx(i32 1, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0)) #11, !dbg !1280
  unreachable, !dbg !1280

if.end8:                                          ; preds = %if.end4
  store i32* null, i32** %retval, align 8, !dbg !1281
  br label %return, !dbg !1281

return:                                           ; preds = %if.end8, %if.then3, %if.then
  %7 = load i32*, i32** %retval, align 8, !dbg !1282
  ret i32* %7, !dbg !1282
}

; Function Attrs: nounwind uwtable
define i32 @_archive_entry_hardlink_l(%struct.archive_entry* %entry1, i8** %p, i64* %len, %struct.archive_string_conv* %sc) #0 !dbg !278 {
entry:
  %retval = alloca i32, align 4
  %entry.addr = alloca %struct.archive_entry*, align 8
  %p.addr = alloca i8**, align 8
  %len.addr = alloca i64*, align 8
  %sc.addr = alloca %struct.archive_string_conv*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1283, metadata !486), !dbg !1284
  store i8** %p, i8*** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %p.addr, metadata !1285, metadata !486), !dbg !1286
  store i64* %len, i64** %len.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %len.addr, metadata !1287, metadata !486), !dbg !1288
  store %struct.archive_string_conv* %sc, %struct.archive_string_conv** %sc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string_conv** %sc.addr, metadata !1289, metadata !486), !dbg !1290
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1291
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 4, !dbg !1293
  %1 = load i32, i32* %ae_set, align 8, !dbg !1293
  %and = and i32 %1, 1, !dbg !1294
  %cmp = icmp eq i32 %and, 0, !dbg !1295
  br i1 %cmp, label %if.then, label %if.end, !dbg !1296

if.then:                                          ; preds = %entry
  %2 = load i8**, i8*** %p.addr, align 8, !dbg !1297
  store i8* null, i8** %2, align 8, !dbg !1299
  %3 = load i64*, i64** %len.addr, align 8, !dbg !1300
  store i64 0, i64* %3, align 8, !dbg !1301
  store i32 0, i32* %retval, align 4, !dbg !1302
  br label %return, !dbg !1302

if.end:                                           ; preds = %entry
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1303
  %ae_hardlink = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %4, i32 0, i32 9, !dbg !1304
  %5 = load i8**, i8*** %p.addr, align 8, !dbg !1305
  %6 = load i64*, i64** %len.addr, align 8, !dbg !1306
  %7 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sc.addr, align 8, !dbg !1307
  %call = call i32 @archive_mstring_get_mbs_l(%struct.archive_mstring* %ae_hardlink, i8** %5, i64* %6, %struct.archive_string_conv* %7), !dbg !1308
  store i32 %call, i32* %retval, align 4, !dbg !1309
  br label %return, !dbg !1309

return:                                           ; preds = %if.end, %if.then
  %8 = load i32, i32* %retval, align 4, !dbg !1310
  ret i32 %8, !dbg !1310
}

; Function Attrs: nounwind uwtable
define i64 @archive_entry_ino(%struct.archive_entry* %entry1) #0 !dbg !279 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1311, metadata !486), !dbg !1312
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1313
  %ae_stat = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 3, !dbg !1314
  %aest_ino = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat, i32 0, i32 9, !dbg !1315
  %1 = load i64, i64* %aest_ino, align 8, !dbg !1315
  ret i64 %1, !dbg !1316
}

; Function Attrs: nounwind uwtable
define i32 @archive_entry_ino_is_set(%struct.archive_entry* %entry1) #0 !dbg !280 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1317, metadata !486), !dbg !1318
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1319
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 4, !dbg !1320
  %1 = load i32, i32* %ae_set, align 8, !dbg !1320
  %and = and i32 %1, 128, !dbg !1321
  ret i32 %and, !dbg !1322
}

; Function Attrs: nounwind uwtable
define i64 @archive_entry_ino64(%struct.archive_entry* %entry1) #0 !dbg !281 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1323, metadata !486), !dbg !1324
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1325
  %ae_stat = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 3, !dbg !1326
  %aest_ino = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat, i32 0, i32 9, !dbg !1327
  %1 = load i64, i64* %aest_ino, align 8, !dbg !1327
  ret i64 %1, !dbg !1328
}

; Function Attrs: nounwind uwtable
define i32 @archive_entry_mode(%struct.archive_entry* %entry1) #0 !dbg !282 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1329, metadata !486), !dbg !1330
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1331
  %acl = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 17, !dbg !1332
  %mode = getelementptr inbounds %struct.archive_acl, %struct.archive_acl* %acl, i32 0, i32 0, !dbg !1333
  %1 = load i32, i32* %mode, align 8, !dbg !1333
  ret i32 %1, !dbg !1334
}

; Function Attrs: nounwind uwtable
define i64 @archive_entry_mtime(%struct.archive_entry* %entry1) #0 !dbg !283 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1335, metadata !486), !dbg !1336
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1337
  %ae_stat = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 3, !dbg !1338
  %aest_mtime = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat, i32 0, i32 4, !dbg !1339
  %1 = load i64, i64* %aest_mtime, align 8, !dbg !1339
  ret i64 %1, !dbg !1340
}

; Function Attrs: nounwind uwtable
define i64 @archive_entry_mtime_nsec(%struct.archive_entry* %entry1) #0 !dbg !284 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1341, metadata !486), !dbg !1342
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1343
  %ae_stat = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 3, !dbg !1344
  %aest_mtime_nsec = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat, i32 0, i32 5, !dbg !1345
  %1 = load i32, i32* %aest_mtime_nsec, align 8, !dbg !1345
  %conv = zext i32 %1 to i64, !dbg !1346
  ret i64 %conv, !dbg !1347
}

; Function Attrs: nounwind uwtable
define i32 @archive_entry_mtime_is_set(%struct.archive_entry* %entry1) #0 !dbg !285 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1348, metadata !486), !dbg !1349
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1350
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 4, !dbg !1351
  %1 = load i32, i32* %ae_set, align 8, !dbg !1351
  %and = and i32 %1, 16, !dbg !1352
  ret i32 %and, !dbg !1353
}

; Function Attrs: nounwind uwtable
define i32 @archive_entry_nlink(%struct.archive_entry* %entry1) #0 !dbg !286 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1354, metadata !486), !dbg !1355
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1356
  %ae_stat = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 3, !dbg !1357
  %aest_nlink = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat, i32 0, i32 10, !dbg !1358
  %1 = load i32, i32* %aest_nlink, align 8, !dbg !1358
  ret i32 %1, !dbg !1359
}

; Function Attrs: nounwind uwtable
define i8* @archive_entry_pathname(%struct.archive_entry* %entry1) #0 !dbg !289 {
entry:
  %retval = alloca i8*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %p = alloca i8*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1360, metadata !486), !dbg !1361
  call void @llvm.dbg.declare(metadata i8** %p, metadata !1362, metadata !486), !dbg !1363
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1364
  %archive = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 0, !dbg !1366
  %1 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !1366
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1367
  %ae_pathname = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 10, !dbg !1368
  %call = call i32 @archive_mstring_get_mbs(%struct.archive* %1, %struct.archive_mstring* %ae_pathname, i8** %p), !dbg !1369
  %cmp = icmp eq i32 %call, 0, !dbg !1370
  br i1 %cmp, label %if.then, label %if.end, !dbg !1371

if.then:                                          ; preds = %entry
  %3 = load i8*, i8** %p, align 8, !dbg !1372
  store i8* %3, i8** %retval, align 8, !dbg !1373
  br label %return, !dbg !1373

if.end:                                           ; preds = %entry
  %call2 = call i32* @__errno_location() #1, !dbg !1374
  %4 = load i32, i32* %call2, align 4, !dbg !1374
  %cmp3 = icmp eq i32 %4, 12, !dbg !1376
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !1377

if.then4:                                         ; preds = %if.end
  call void @__archive_errx(i32 1, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0)) #11, !dbg !1378
  unreachable, !dbg !1378

if.end5:                                          ; preds = %if.end
  store i8* null, i8** %retval, align 8, !dbg !1379
  br label %return, !dbg !1379

return:                                           ; preds = %if.end5, %if.then
  %5 = load i8*, i8** %retval, align 8, !dbg !1380
  ret i8* %5, !dbg !1380
}

; Function Attrs: nounwind uwtable
define i8* @archive_entry_pathname_utf8(%struct.archive_entry* %entry1) #0 !dbg !290 {
entry:
  %retval = alloca i8*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %p = alloca i8*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1381, metadata !486), !dbg !1382
  call void @llvm.dbg.declare(metadata i8** %p, metadata !1383, metadata !486), !dbg !1384
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1385
  %archive = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 0, !dbg !1387
  %1 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !1387
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1388
  %ae_pathname = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 10, !dbg !1389
  %call = call i32 @archive_mstring_get_utf8(%struct.archive* %1, %struct.archive_mstring* %ae_pathname, i8** %p), !dbg !1390
  %cmp = icmp eq i32 %call, 0, !dbg !1391
  br i1 %cmp, label %if.then, label %if.end, !dbg !1392

if.then:                                          ; preds = %entry
  %3 = load i8*, i8** %p, align 8, !dbg !1393
  store i8* %3, i8** %retval, align 8, !dbg !1394
  br label %return, !dbg !1394

if.end:                                           ; preds = %entry
  %call2 = call i32* @__errno_location() #1, !dbg !1395
  %4 = load i32, i32* %call2, align 4, !dbg !1395
  %cmp3 = icmp eq i32 %4, 12, !dbg !1397
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !1398

if.then4:                                         ; preds = %if.end
  call void @__archive_errx(i32 1, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0)) #11, !dbg !1399
  unreachable, !dbg !1399

if.end5:                                          ; preds = %if.end
  store i8* null, i8** %retval, align 8, !dbg !1400
  br label %return, !dbg !1400

return:                                           ; preds = %if.end5, %if.then
  %5 = load i8*, i8** %retval, align 8, !dbg !1401
  ret i8* %5, !dbg !1401
}

; Function Attrs: nounwind uwtable
define i32* @archive_entry_pathname_w(%struct.archive_entry* %entry1) #0 !dbg !291 {
entry:
  %retval = alloca i32*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %p = alloca i32*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1402, metadata !486), !dbg !1403
  call void @llvm.dbg.declare(metadata i32** %p, metadata !1404, metadata !486), !dbg !1405
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1406
  %archive = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 0, !dbg !1408
  %1 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !1408
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1409
  %ae_pathname = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 10, !dbg !1410
  %call = call i32 @archive_mstring_get_wcs(%struct.archive* %1, %struct.archive_mstring* %ae_pathname, i32** %p), !dbg !1411
  %cmp = icmp eq i32 %call, 0, !dbg !1412
  br i1 %cmp, label %if.then, label %if.end, !dbg !1413

if.then:                                          ; preds = %entry
  %3 = load i32*, i32** %p, align 8, !dbg !1414
  store i32* %3, i32** %retval, align 8, !dbg !1415
  br label %return, !dbg !1415

if.end:                                           ; preds = %entry
  %call2 = call i32* @__errno_location() #1, !dbg !1416
  %4 = load i32, i32* %call2, align 4, !dbg !1416
  %cmp3 = icmp eq i32 %4, 12, !dbg !1418
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !1419

if.then4:                                         ; preds = %if.end
  call void @__archive_errx(i32 1, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0)) #11, !dbg !1420
  unreachable, !dbg !1420

if.end5:                                          ; preds = %if.end
  store i32* null, i32** %retval, align 8, !dbg !1421
  br label %return, !dbg !1421

return:                                           ; preds = %if.end5, %if.then
  %5 = load i32*, i32** %retval, align 8, !dbg !1422
  ret i32* %5, !dbg !1422
}

; Function Attrs: nounwind uwtable
define i32 @_archive_entry_pathname_l(%struct.archive_entry* %entry1, i8** %p, i64* %len, %struct.archive_string_conv* %sc) #0 !dbg !292 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %p.addr = alloca i8**, align 8
  %len.addr = alloca i64*, align 8
  %sc.addr = alloca %struct.archive_string_conv*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1423, metadata !486), !dbg !1424
  store i8** %p, i8*** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %p.addr, metadata !1425, metadata !486), !dbg !1426
  store i64* %len, i64** %len.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %len.addr, metadata !1427, metadata !486), !dbg !1428
  store %struct.archive_string_conv* %sc, %struct.archive_string_conv** %sc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string_conv** %sc.addr, metadata !1429, metadata !486), !dbg !1430
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1431
  %ae_pathname = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 10, !dbg !1432
  %1 = load i8**, i8*** %p.addr, align 8, !dbg !1433
  %2 = load i64*, i64** %len.addr, align 8, !dbg !1434
  %3 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sc.addr, align 8, !dbg !1435
  %call = call i32 @archive_mstring_get_mbs_l(%struct.archive_mstring* %ae_pathname, i8** %1, i64* %2, %struct.archive_string_conv* %3), !dbg !1436
  ret i32 %call, !dbg !1437
}

; Function Attrs: nounwind uwtable
define i32 @archive_entry_perm(%struct.archive_entry* %entry1) #0 !dbg !293 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1438, metadata !486), !dbg !1439
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1440
  %acl = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 17, !dbg !1441
  %mode = getelementptr inbounds %struct.archive_acl, %struct.archive_acl* %acl, i32 0, i32 0, !dbg !1442
  %1 = load i32, i32* %mode, align 8, !dbg !1442
  %and = and i32 -61441, %1, !dbg !1443
  ret i32 %and, !dbg !1444
}

; Function Attrs: nounwind uwtable
define i64 @archive_entry_rdev(%struct.archive_entry* %entry1) #0 !dbg !294 {
entry:
  %retval = alloca i64, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1445, metadata !486), !dbg !1446
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1447
  %ae_stat = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 3, !dbg !1449
  %aest_rdev_is_broken_down = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat, i32 0, i32 17, !dbg !1450
  %1 = load i32, i32* %aest_rdev_is_broken_down, align 8, !dbg !1450
  %tobool = icmp ne i32 %1, 0, !dbg !1447
  br i1 %tobool, label %if.then, label %if.else, !dbg !1451

if.then:                                          ; preds = %entry
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1452
  %ae_stat2 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 3, !dbg !1452
  %aest_rdevmajor = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat2, i32 0, i32 19, !dbg !1452
  %3 = load i64, i64* %aest_rdevmajor, align 8, !dbg !1452
  %conv = trunc i64 %3 to i32, !dbg !1452
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1452
  %ae_stat3 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %4, i32 0, i32 3, !dbg !1452
  %aest_rdevminor = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat3, i32 0, i32 20, !dbg !1452
  %5 = load i64, i64* %aest_rdevminor, align 8, !dbg !1452
  %conv4 = trunc i64 %5 to i32, !dbg !1452
  %call = call i64 @gnu_dev_makedev(i32 %conv, i32 %conv4) #1, !dbg !1452
  store i64 %call, i64* %retval, align 8, !dbg !1453
  br label %return, !dbg !1453

if.else:                                          ; preds = %entry
  %6 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1454
  %ae_stat5 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %6, i32 0, i32 3, !dbg !1455
  %aest_rdev = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat5, i32 0, i32 18, !dbg !1456
  %7 = load i64, i64* %aest_rdev, align 8, !dbg !1456
  store i64 %7, i64* %retval, align 8, !dbg !1457
  br label %return, !dbg !1457

return:                                           ; preds = %if.else, %if.then
  %8 = load i64, i64* %retval, align 8, !dbg !1458
  ret i64 %8, !dbg !1458
}

; Function Attrs: nounwind uwtable
define i64 @archive_entry_rdevmajor(%struct.archive_entry* %entry1) #0 !dbg !295 {
entry:
  %retval = alloca i64, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1459, metadata !486), !dbg !1460
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1461
  %ae_stat = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 3, !dbg !1463
  %aest_rdev_is_broken_down = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat, i32 0, i32 17, !dbg !1464
  %1 = load i32, i32* %aest_rdev_is_broken_down, align 8, !dbg !1464
  %tobool = icmp ne i32 %1, 0, !dbg !1461
  br i1 %tobool, label %if.then, label %if.else, !dbg !1465

if.then:                                          ; preds = %entry
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1466
  %ae_stat2 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 3, !dbg !1467
  %aest_rdevmajor = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat2, i32 0, i32 19, !dbg !1468
  %3 = load i64, i64* %aest_rdevmajor, align 8, !dbg !1468
  store i64 %3, i64* %retval, align 8, !dbg !1469
  br label %return, !dbg !1469

if.else:                                          ; preds = %entry
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1470
  %ae_stat3 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %4, i32 0, i32 3, !dbg !1470
  %aest_rdev = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat3, i32 0, i32 18, !dbg !1470
  %5 = load i64, i64* %aest_rdev, align 8, !dbg !1470
  %call = call i32 @gnu_dev_major(i64 %5) #1, !dbg !1470
  %conv = zext i32 %call to i64, !dbg !1470
  store i64 %conv, i64* %retval, align 8, !dbg !1471
  br label %return, !dbg !1471

return:                                           ; preds = %if.else, %if.then
  %6 = load i64, i64* %retval, align 8, !dbg !1472
  ret i64 %6, !dbg !1472
}

; Function Attrs: nounwind uwtable
define i64 @archive_entry_rdevminor(%struct.archive_entry* %entry1) #0 !dbg !296 {
entry:
  %retval = alloca i64, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1473, metadata !486), !dbg !1474
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1475
  %ae_stat = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 3, !dbg !1477
  %aest_rdev_is_broken_down = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat, i32 0, i32 17, !dbg !1478
  %1 = load i32, i32* %aest_rdev_is_broken_down, align 8, !dbg !1478
  %tobool = icmp ne i32 %1, 0, !dbg !1475
  br i1 %tobool, label %if.then, label %if.else, !dbg !1479

if.then:                                          ; preds = %entry
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1480
  %ae_stat2 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 3, !dbg !1481
  %aest_rdevminor = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat2, i32 0, i32 20, !dbg !1482
  %3 = load i64, i64* %aest_rdevminor, align 8, !dbg !1482
  store i64 %3, i64* %retval, align 8, !dbg !1483
  br label %return, !dbg !1483

if.else:                                          ; preds = %entry
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1484
  %ae_stat3 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %4, i32 0, i32 3, !dbg !1484
  %aest_rdev = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat3, i32 0, i32 18, !dbg !1484
  %5 = load i64, i64* %aest_rdev, align 8, !dbg !1484
  %call = call i32 @gnu_dev_minor(i64 %5) #1, !dbg !1484
  %conv = zext i32 %call to i64, !dbg !1484
  store i64 %conv, i64* %retval, align 8, !dbg !1485
  br label %return, !dbg !1485

return:                                           ; preds = %if.else, %if.then
  %6 = load i64, i64* %retval, align 8, !dbg !1486
  ret i64 %6, !dbg !1486
}

; Function Attrs: nounwind uwtable
define i64 @archive_entry_size(%struct.archive_entry* %entry1) #0 !dbg !297 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1487, metadata !486), !dbg !1488
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1489
  %ae_stat = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 3, !dbg !1490
  %aest_size = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat, i32 0, i32 11, !dbg !1491
  %1 = load i64, i64* %aest_size, align 8, !dbg !1491
  ret i64 %1, !dbg !1492
}

; Function Attrs: nounwind uwtable
define i32 @archive_entry_size_is_set(%struct.archive_entry* %entry1) #0 !dbg !298 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1493, metadata !486), !dbg !1494
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1495
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 4, !dbg !1496
  %1 = load i32, i32* %ae_set, align 8, !dbg !1496
  %and = and i32 %1, 64, !dbg !1497
  ret i32 %and, !dbg !1498
}

; Function Attrs: nounwind uwtable
define i8* @archive_entry_sourcepath(%struct.archive_entry* %entry1) #0 !dbg !299 {
entry:
  %retval = alloca i8*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %p = alloca i8*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1499, metadata !486), !dbg !1500
  call void @llvm.dbg.declare(metadata i8** %p, metadata !1501, metadata !486), !dbg !1502
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1503
  %archive = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 0, !dbg !1505
  %1 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !1505
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1506
  %ae_sourcepath = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 13, !dbg !1507
  %call = call i32 @archive_mstring_get_mbs(%struct.archive* %1, %struct.archive_mstring* %ae_sourcepath, i8** %p), !dbg !1508
  %cmp = icmp eq i32 %call, 0, !dbg !1509
  br i1 %cmp, label %if.then, label %if.end, !dbg !1510

if.then:                                          ; preds = %entry
  %3 = load i8*, i8** %p, align 8, !dbg !1511
  store i8* %3, i8** %retval, align 8, !dbg !1512
  br label %return, !dbg !1512

if.end:                                           ; preds = %entry
  %call2 = call i32* @__errno_location() #1, !dbg !1513
  %4 = load i32, i32* %call2, align 4, !dbg !1513
  %cmp3 = icmp eq i32 %4, 12, !dbg !1515
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !1516

if.then4:                                         ; preds = %if.end
  call void @__archive_errx(i32 1, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0)) #11, !dbg !1517
  unreachable, !dbg !1517

if.end5:                                          ; preds = %if.end
  store i8* null, i8** %retval, align 8, !dbg !1518
  br label %return, !dbg !1518

return:                                           ; preds = %if.end5, %if.then
  %5 = load i8*, i8** %retval, align 8, !dbg !1519
  ret i8* %5, !dbg !1519
}

; Function Attrs: nounwind uwtable
define i32* @archive_entry_sourcepath_w(%struct.archive_entry* %entry1) #0 !dbg !300 {
entry:
  %retval = alloca i32*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %p = alloca i32*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1520, metadata !486), !dbg !1521
  call void @llvm.dbg.declare(metadata i32** %p, metadata !1522, metadata !486), !dbg !1523
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1524
  %archive = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 0, !dbg !1526
  %1 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !1526
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1527
  %ae_sourcepath = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 13, !dbg !1528
  %call = call i32 @archive_mstring_get_wcs(%struct.archive* %1, %struct.archive_mstring* %ae_sourcepath, i32** %p), !dbg !1529
  %cmp = icmp eq i32 %call, 0, !dbg !1530
  br i1 %cmp, label %if.then, label %if.end, !dbg !1531

if.then:                                          ; preds = %entry
  %3 = load i32*, i32** %p, align 8, !dbg !1532
  store i32* %3, i32** %retval, align 8, !dbg !1533
  br label %return, !dbg !1533

if.end:                                           ; preds = %entry
  store i32* null, i32** %retval, align 8, !dbg !1534
  br label %return, !dbg !1534

return:                                           ; preds = %if.end, %if.then
  %4 = load i32*, i32** %retval, align 8, !dbg !1535
  ret i32* %4, !dbg !1535
}

; Function Attrs: nounwind uwtable
define i8* @archive_entry_symlink(%struct.archive_entry* %entry1) #0 !dbg !301 {
entry:
  %retval = alloca i8*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %p = alloca i8*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1536, metadata !486), !dbg !1537
  call void @llvm.dbg.declare(metadata i8** %p, metadata !1538, metadata !486), !dbg !1539
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1540
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 4, !dbg !1542
  %1 = load i32, i32* %ae_set, align 8, !dbg !1542
  %and = and i32 %1, 2, !dbg !1543
  %cmp = icmp eq i32 %and, 0, !dbg !1544
  br i1 %cmp, label %if.then, label %if.end, !dbg !1545

if.then:                                          ; preds = %entry
  store i8* null, i8** %retval, align 8, !dbg !1546
  br label %return, !dbg !1546

if.end:                                           ; preds = %entry
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1547
  %archive = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 0, !dbg !1549
  %3 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !1549
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1550
  %ae_symlink = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %4, i32 0, i32 11, !dbg !1551
  %call = call i32 @archive_mstring_get_mbs(%struct.archive* %3, %struct.archive_mstring* %ae_symlink, i8** %p), !dbg !1552
  %cmp2 = icmp eq i32 %call, 0, !dbg !1553
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !1554

if.then3:                                         ; preds = %if.end
  %5 = load i8*, i8** %p, align 8, !dbg !1555
  store i8* %5, i8** %retval, align 8, !dbg !1556
  br label %return, !dbg !1556

if.end4:                                          ; preds = %if.end
  %call5 = call i32* @__errno_location() #1, !dbg !1557
  %6 = load i32, i32* %call5, align 4, !dbg !1557
  %cmp6 = icmp eq i32 %6, 12, !dbg !1559
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !1560

if.then7:                                         ; preds = %if.end4
  call void @__archive_errx(i32 1, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0)) #11, !dbg !1561
  unreachable, !dbg !1561

if.end8:                                          ; preds = %if.end4
  store i8* null, i8** %retval, align 8, !dbg !1562
  br label %return, !dbg !1562

return:                                           ; preds = %if.end8, %if.then3, %if.then
  %7 = load i8*, i8** %retval, align 8, !dbg !1563
  ret i8* %7, !dbg !1563
}

; Function Attrs: nounwind uwtable
define i8* @archive_entry_symlink_utf8(%struct.archive_entry* %entry1) #0 !dbg !302 {
entry:
  %retval = alloca i8*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %p = alloca i8*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1564, metadata !486), !dbg !1565
  call void @llvm.dbg.declare(metadata i8** %p, metadata !1566, metadata !486), !dbg !1567
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1568
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 4, !dbg !1570
  %1 = load i32, i32* %ae_set, align 8, !dbg !1570
  %and = and i32 %1, 2, !dbg !1571
  %cmp = icmp eq i32 %and, 0, !dbg !1572
  br i1 %cmp, label %if.then, label %if.end, !dbg !1573

if.then:                                          ; preds = %entry
  store i8* null, i8** %retval, align 8, !dbg !1574
  br label %return, !dbg !1574

if.end:                                           ; preds = %entry
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1575
  %archive = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 0, !dbg !1577
  %3 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !1577
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1578
  %ae_symlink = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %4, i32 0, i32 11, !dbg !1579
  %call = call i32 @archive_mstring_get_utf8(%struct.archive* %3, %struct.archive_mstring* %ae_symlink, i8** %p), !dbg !1580
  %cmp2 = icmp eq i32 %call, 0, !dbg !1581
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !1582

if.then3:                                         ; preds = %if.end
  %5 = load i8*, i8** %p, align 8, !dbg !1583
  store i8* %5, i8** %retval, align 8, !dbg !1584
  br label %return, !dbg !1584

if.end4:                                          ; preds = %if.end
  %call5 = call i32* @__errno_location() #1, !dbg !1585
  %6 = load i32, i32* %call5, align 4, !dbg !1585
  %cmp6 = icmp eq i32 %6, 12, !dbg !1587
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !1588

if.then7:                                         ; preds = %if.end4
  call void @__archive_errx(i32 1, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0)) #11, !dbg !1589
  unreachable, !dbg !1589

if.end8:                                          ; preds = %if.end4
  store i8* null, i8** %retval, align 8, !dbg !1590
  br label %return, !dbg !1590

return:                                           ; preds = %if.end8, %if.then3, %if.then
  %7 = load i8*, i8** %retval, align 8, !dbg !1591
  ret i8* %7, !dbg !1591
}

; Function Attrs: nounwind uwtable
define i32* @archive_entry_symlink_w(%struct.archive_entry* %entry1) #0 !dbg !303 {
entry:
  %retval = alloca i32*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %p = alloca i32*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1592, metadata !486), !dbg !1593
  call void @llvm.dbg.declare(metadata i32** %p, metadata !1594, metadata !486), !dbg !1595
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1596
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 4, !dbg !1598
  %1 = load i32, i32* %ae_set, align 8, !dbg !1598
  %and = and i32 %1, 2, !dbg !1599
  %cmp = icmp eq i32 %and, 0, !dbg !1600
  br i1 %cmp, label %if.then, label %if.end, !dbg !1601

if.then:                                          ; preds = %entry
  store i32* null, i32** %retval, align 8, !dbg !1602
  br label %return, !dbg !1602

if.end:                                           ; preds = %entry
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1603
  %archive = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 0, !dbg !1605
  %3 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !1605
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1606
  %ae_symlink = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %4, i32 0, i32 11, !dbg !1607
  %call = call i32 @archive_mstring_get_wcs(%struct.archive* %3, %struct.archive_mstring* %ae_symlink, i32** %p), !dbg !1608
  %cmp2 = icmp eq i32 %call, 0, !dbg !1609
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !1610

if.then3:                                         ; preds = %if.end
  %5 = load i32*, i32** %p, align 8, !dbg !1611
  store i32* %5, i32** %retval, align 8, !dbg !1612
  br label %return, !dbg !1612

if.end4:                                          ; preds = %if.end
  %call5 = call i32* @__errno_location() #1, !dbg !1613
  %6 = load i32, i32* %call5, align 4, !dbg !1613
  %cmp6 = icmp eq i32 %6, 12, !dbg !1615
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !1616

if.then7:                                         ; preds = %if.end4
  call void @__archive_errx(i32 1, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0)) #11, !dbg !1617
  unreachable, !dbg !1617

if.end8:                                          ; preds = %if.end4
  store i32* null, i32** %retval, align 8, !dbg !1618
  br label %return, !dbg !1618

return:                                           ; preds = %if.end8, %if.then3, %if.then
  %7 = load i32*, i32** %retval, align 8, !dbg !1619
  ret i32* %7, !dbg !1619
}

; Function Attrs: nounwind uwtable
define i32 @_archive_entry_symlink_l(%struct.archive_entry* %entry1, i8** %p, i64* %len, %struct.archive_string_conv* %sc) #0 !dbg !304 {
entry:
  %retval = alloca i32, align 4
  %entry.addr = alloca %struct.archive_entry*, align 8
  %p.addr = alloca i8**, align 8
  %len.addr = alloca i64*, align 8
  %sc.addr = alloca %struct.archive_string_conv*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1620, metadata !486), !dbg !1621
  store i8** %p, i8*** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %p.addr, metadata !1622, metadata !486), !dbg !1623
  store i64* %len, i64** %len.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %len.addr, metadata !1624, metadata !486), !dbg !1625
  store %struct.archive_string_conv* %sc, %struct.archive_string_conv** %sc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string_conv** %sc.addr, metadata !1626, metadata !486), !dbg !1627
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1628
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 4, !dbg !1630
  %1 = load i32, i32* %ae_set, align 8, !dbg !1630
  %and = and i32 %1, 2, !dbg !1631
  %cmp = icmp eq i32 %and, 0, !dbg !1632
  br i1 %cmp, label %if.then, label %if.end, !dbg !1633

if.then:                                          ; preds = %entry
  %2 = load i8**, i8*** %p.addr, align 8, !dbg !1634
  store i8* null, i8** %2, align 8, !dbg !1636
  %3 = load i64*, i64** %len.addr, align 8, !dbg !1637
  store i64 0, i64* %3, align 8, !dbg !1638
  store i32 0, i32* %retval, align 4, !dbg !1639
  br label %return, !dbg !1639

if.end:                                           ; preds = %entry
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1640
  %ae_symlink = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %4, i32 0, i32 11, !dbg !1641
  %5 = load i8**, i8*** %p.addr, align 8, !dbg !1642
  %6 = load i64*, i64** %len.addr, align 8, !dbg !1643
  %7 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sc.addr, align 8, !dbg !1644
  %call = call i32 @archive_mstring_get_mbs_l(%struct.archive_mstring* %ae_symlink, i8** %5, i64* %6, %struct.archive_string_conv* %7), !dbg !1645
  store i32 %call, i32* %retval, align 4, !dbg !1646
  br label %return, !dbg !1646

return:                                           ; preds = %if.end, %if.then
  %8 = load i32, i32* %retval, align 4, !dbg !1647
  ret i32 %8, !dbg !1647
}

; Function Attrs: nounwind uwtable
define i64 @archive_entry_uid(%struct.archive_entry* %entry1) #0 !dbg !305 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1648, metadata !486), !dbg !1649
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1650
  %ae_stat = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 3, !dbg !1651
  %aest_uid = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat, i32 0, i32 12, !dbg !1652
  %1 = load i64, i64* %aest_uid, align 8, !dbg !1652
  ret i64 %1, !dbg !1653
}

; Function Attrs: nounwind uwtable
define i8* @archive_entry_uname(%struct.archive_entry* %entry1) #0 !dbg !306 {
entry:
  %retval = alloca i8*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %p = alloca i8*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1654, metadata !486), !dbg !1655
  call void @llvm.dbg.declare(metadata i8** %p, metadata !1656, metadata !486), !dbg !1657
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1658
  %archive = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 0, !dbg !1660
  %1 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !1660
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1661
  %ae_uname = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 12, !dbg !1662
  %call = call i32 @archive_mstring_get_mbs(%struct.archive* %1, %struct.archive_mstring* %ae_uname, i8** %p), !dbg !1663
  %cmp = icmp eq i32 %call, 0, !dbg !1664
  br i1 %cmp, label %if.then, label %if.end, !dbg !1665

if.then:                                          ; preds = %entry
  %3 = load i8*, i8** %p, align 8, !dbg !1666
  store i8* %3, i8** %retval, align 8, !dbg !1667
  br label %return, !dbg !1667

if.end:                                           ; preds = %entry
  %call2 = call i32* @__errno_location() #1, !dbg !1668
  %4 = load i32, i32* %call2, align 4, !dbg !1668
  %cmp3 = icmp eq i32 %4, 12, !dbg !1670
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !1671

if.then4:                                         ; preds = %if.end
  call void @__archive_errx(i32 1, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0)) #11, !dbg !1672
  unreachable, !dbg !1672

if.end5:                                          ; preds = %if.end
  store i8* null, i8** %retval, align 8, !dbg !1673
  br label %return, !dbg !1673

return:                                           ; preds = %if.end5, %if.then
  %5 = load i8*, i8** %retval, align 8, !dbg !1674
  ret i8* %5, !dbg !1674
}

; Function Attrs: nounwind uwtable
define i8* @archive_entry_uname_utf8(%struct.archive_entry* %entry1) #0 !dbg !307 {
entry:
  %retval = alloca i8*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %p = alloca i8*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1675, metadata !486), !dbg !1676
  call void @llvm.dbg.declare(metadata i8** %p, metadata !1677, metadata !486), !dbg !1678
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1679
  %archive = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 0, !dbg !1681
  %1 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !1681
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1682
  %ae_uname = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 12, !dbg !1683
  %call = call i32 @archive_mstring_get_utf8(%struct.archive* %1, %struct.archive_mstring* %ae_uname, i8** %p), !dbg !1684
  %cmp = icmp eq i32 %call, 0, !dbg !1685
  br i1 %cmp, label %if.then, label %if.end, !dbg !1686

if.then:                                          ; preds = %entry
  %3 = load i8*, i8** %p, align 8, !dbg !1687
  store i8* %3, i8** %retval, align 8, !dbg !1688
  br label %return, !dbg !1688

if.end:                                           ; preds = %entry
  %call2 = call i32* @__errno_location() #1, !dbg !1689
  %4 = load i32, i32* %call2, align 4, !dbg !1689
  %cmp3 = icmp eq i32 %4, 12, !dbg !1691
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !1692

if.then4:                                         ; preds = %if.end
  call void @__archive_errx(i32 1, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0)) #11, !dbg !1693
  unreachable, !dbg !1693

if.end5:                                          ; preds = %if.end
  store i8* null, i8** %retval, align 8, !dbg !1694
  br label %return, !dbg !1694

return:                                           ; preds = %if.end5, %if.then
  %5 = load i8*, i8** %retval, align 8, !dbg !1695
  ret i8* %5, !dbg !1695
}

; Function Attrs: nounwind uwtable
define i32* @archive_entry_uname_w(%struct.archive_entry* %entry1) #0 !dbg !308 {
entry:
  %retval = alloca i32*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %p = alloca i32*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1696, metadata !486), !dbg !1697
  call void @llvm.dbg.declare(metadata i32** %p, metadata !1698, metadata !486), !dbg !1699
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1700
  %archive = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 0, !dbg !1702
  %1 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !1702
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1703
  %ae_uname = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 12, !dbg !1704
  %call = call i32 @archive_mstring_get_wcs(%struct.archive* %1, %struct.archive_mstring* %ae_uname, i32** %p), !dbg !1705
  %cmp = icmp eq i32 %call, 0, !dbg !1706
  br i1 %cmp, label %if.then, label %if.end, !dbg !1707

if.then:                                          ; preds = %entry
  %3 = load i32*, i32** %p, align 8, !dbg !1708
  store i32* %3, i32** %retval, align 8, !dbg !1709
  br label %return, !dbg !1709

if.end:                                           ; preds = %entry
  %call2 = call i32* @__errno_location() #1, !dbg !1710
  %4 = load i32, i32* %call2, align 4, !dbg !1710
  %cmp3 = icmp eq i32 %4, 12, !dbg !1712
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !1713

if.then4:                                         ; preds = %if.end
  call void @__archive_errx(i32 1, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0)) #11, !dbg !1714
  unreachable, !dbg !1714

if.end5:                                          ; preds = %if.end
  store i32* null, i32** %retval, align 8, !dbg !1715
  br label %return, !dbg !1715

return:                                           ; preds = %if.end5, %if.then
  %5 = load i32*, i32** %retval, align 8, !dbg !1716
  ret i32* %5, !dbg !1716
}

; Function Attrs: nounwind uwtable
define i32 @_archive_entry_uname_l(%struct.archive_entry* %entry1, i8** %p, i64* %len, %struct.archive_string_conv* %sc) #0 !dbg !309 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %p.addr = alloca i8**, align 8
  %len.addr = alloca i64*, align 8
  %sc.addr = alloca %struct.archive_string_conv*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1717, metadata !486), !dbg !1718
  store i8** %p, i8*** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %p.addr, metadata !1719, metadata !486), !dbg !1720
  store i64* %len, i64** %len.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %len.addr, metadata !1721, metadata !486), !dbg !1722
  store %struct.archive_string_conv* %sc, %struct.archive_string_conv** %sc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string_conv** %sc.addr, metadata !1723, metadata !486), !dbg !1724
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1725
  %ae_uname = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 12, !dbg !1726
  %1 = load i8**, i8*** %p.addr, align 8, !dbg !1727
  %2 = load i64*, i64** %len.addr, align 8, !dbg !1728
  %3 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sc.addr, align 8, !dbg !1729
  %call = call i32 @archive_mstring_get_mbs_l(%struct.archive_mstring* %ae_uname, i8** %1, i64* %2, %struct.archive_string_conv* %3), !dbg !1730
  ret i32 %call, !dbg !1731
}

; Function Attrs: nounwind uwtable
define i32 @archive_entry_is_data_encrypted(%struct.archive_entry* %entry1) #0 !dbg !310 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1732, metadata !486), !dbg !1733
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1734
  %encryption = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 14, !dbg !1735
  %1 = load i8, i8* %encryption, align 8, !dbg !1735
  %conv = sext i8 %1 to i32, !dbg !1734
  %and = and i32 %conv, 1, !dbg !1736
  %cmp = icmp eq i32 %and, 1, !dbg !1737
  %conv2 = zext i1 %cmp to i32, !dbg !1737
  ret i32 %conv2, !dbg !1738
}

; Function Attrs: nounwind uwtable
define i32 @archive_entry_is_metadata_encrypted(%struct.archive_entry* %entry1) #0 !dbg !311 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1739, metadata !486), !dbg !1740
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1741
  %encryption = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 14, !dbg !1742
  %1 = load i8, i8* %encryption, align 8, !dbg !1742
  %conv = sext i8 %1 to i32, !dbg !1741
  %and = and i32 %conv, 2, !dbg !1743
  %cmp = icmp eq i32 %and, 2, !dbg !1744
  %conv2 = zext i1 %cmp to i32, !dbg !1744
  ret i32 %conv2, !dbg !1745
}

; Function Attrs: nounwind uwtable
define i32 @archive_entry_is_encrypted(%struct.archive_entry* %entry1) #0 !dbg !312 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1746, metadata !486), !dbg !1747
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1748
  %encryption = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 14, !dbg !1749
  %1 = load i8, i8* %encryption, align 8, !dbg !1749
  %conv = sext i8 %1 to i32, !dbg !1748
  %and = and i32 %conv, 3, !dbg !1750
  ret i32 %and, !dbg !1751
}

; Function Attrs: nounwind uwtable
define void @archive_entry_set_filetype(%struct.archive_entry* %entry1, i32 %type) #0 !dbg !313 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %type.addr = alloca i32, align 4
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1752, metadata !486), !dbg !1753
  store i32 %type, i32* %type.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %type.addr, metadata !1754, metadata !486), !dbg !1755
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1756
  %stat_valid = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 2, !dbg !1757
  store i32 0, i32* %stat_valid, align 8, !dbg !1758
  %1 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1759
  %acl = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %1, i32 0, i32 17, !dbg !1760
  %mode = getelementptr inbounds %struct.archive_acl, %struct.archive_acl* %acl, i32 0, i32 0, !dbg !1761
  %2 = load i32, i32* %mode, align 8, !dbg !1762
  %and = and i32 %2, -61441, !dbg !1762
  store i32 %and, i32* %mode, align 8, !dbg !1762
  %3 = load i32, i32* %type.addr, align 4, !dbg !1763
  %and2 = and i32 61440, %3, !dbg !1764
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1765
  %acl3 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %4, i32 0, i32 17, !dbg !1766
  %mode4 = getelementptr inbounds %struct.archive_acl, %struct.archive_acl* %acl3, i32 0, i32 0, !dbg !1767
  %5 = load i32, i32* %mode4, align 8, !dbg !1768
  %or = or i32 %5, %and2, !dbg !1768
  store i32 %or, i32* %mode4, align 8, !dbg !1768
  ret void, !dbg !1769
}

; Function Attrs: nounwind uwtable
define void @archive_entry_set_fflags(%struct.archive_entry* %entry1, i64 %set, i64 %clear) #0 !dbg !316 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %set.addr = alloca i64, align 8
  %clear.addr = alloca i64, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1770, metadata !486), !dbg !1771
  store i64 %set, i64* %set.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %set.addr, metadata !1772, metadata !486), !dbg !1773
  store i64 %clear, i64* %clear.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %clear.addr, metadata !1774, metadata !486), !dbg !1775
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1776
  %ae_fflags_text = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 5, !dbg !1777
  call void @archive_mstring_clean(%struct.archive_mstring* %ae_fflags_text), !dbg !1778
  %1 = load i64, i64* %set.addr, align 8, !dbg !1779
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1780
  %ae_fflags_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 6, !dbg !1781
  store i64 %1, i64* %ae_fflags_set, align 8, !dbg !1782
  %3 = load i64, i64* %clear.addr, align 8, !dbg !1783
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1784
  %ae_fflags_clear = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %4, i32 0, i32 7, !dbg !1785
  store i64 %3, i64* %ae_fflags_clear, align 8, !dbg !1786
  ret void, !dbg !1787
}

; Function Attrs: nounwind uwtable
define i8* @archive_entry_copy_fflags_text(%struct.archive_entry* %entry1, i8* %flags) #0 !dbg !319 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %flags.addr = alloca i8*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1788, metadata !486), !dbg !1789
  store i8* %flags, i8** %flags.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %flags.addr, metadata !1790, metadata !486), !dbg !1791
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1792
  %ae_fflags_text = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 5, !dbg !1793
  %1 = load i8*, i8** %flags.addr, align 8, !dbg !1794
  %call = call i32 @archive_mstring_copy_mbs(%struct.archive_mstring* %ae_fflags_text, i8* %1), !dbg !1795
  %2 = load i8*, i8** %flags.addr, align 8, !dbg !1796
  %3 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1797
  %ae_fflags_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %3, i32 0, i32 6, !dbg !1798
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1799
  %ae_fflags_clear = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %4, i32 0, i32 7, !dbg !1800
  %call2 = call i8* @ae_strtofflags(i8* %2, i64* %ae_fflags_set, i64* %ae_fflags_clear), !dbg !1801
  ret i8* %call2, !dbg !1802
}

; Function Attrs: nounwind uwtable
define internal i8* @ae_strtofflags(i8* %s, i64* %setp, i64* %clrp) #0 !dbg !465 {
entry:
  %s.addr = alloca i8*, align 8
  %setp.addr = alloca i64*, align 8
  %clrp.addr = alloca i64*, align 8
  %start = alloca i8*, align 8
  %end = alloca i8*, align 8
  %flag = alloca %struct.flag*, align 8
  %set = alloca i64, align 8
  %clear = alloca i64, align 8
  %failed = alloca i8*, align 8
  %length = alloca i64, align 8
  %flag_length = alloca i64, align 8
  store i8* %s, i8** %s.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %s.addr, metadata !1803, metadata !486), !dbg !1804
  store i64* %setp, i64** %setp.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %setp.addr, metadata !1805, metadata !486), !dbg !1806
  store i64* %clrp, i64** %clrp.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %clrp.addr, metadata !1807, metadata !486), !dbg !1808
  call void @llvm.dbg.declare(metadata i8** %start, metadata !1809, metadata !486), !dbg !1810
  call void @llvm.dbg.declare(metadata i8** %end, metadata !1811, metadata !486), !dbg !1812
  call void @llvm.dbg.declare(metadata %struct.flag** %flag, metadata !1813, metadata !486), !dbg !1814
  call void @llvm.dbg.declare(metadata i64* %set, metadata !1815, metadata !486), !dbg !1816
  call void @llvm.dbg.declare(metadata i64* %clear, metadata !1817, metadata !486), !dbg !1818
  call void @llvm.dbg.declare(metadata i8** %failed, metadata !1819, metadata !486), !dbg !1820
  store i64 0, i64* %clear, align 8, !dbg !1821
  store i64 0, i64* %set, align 8, !dbg !1822
  %0 = load i8*, i8** %s.addr, align 8, !dbg !1823
  store i8* %0, i8** %start, align 8, !dbg !1824
  store i8* null, i8** %failed, align 8, !dbg !1825
  br label %while.cond, !dbg !1826

while.cond:                                       ; preds = %while.body, %entry
  %1 = load i8*, i8** %start, align 8, !dbg !1827
  %2 = load i8, i8* %1, align 1, !dbg !1829
  %conv = sext i8 %2 to i32, !dbg !1829
  %cmp = icmp eq i32 %conv, 9, !dbg !1830
  br i1 %cmp, label %lor.end, label %lor.lhs.false, !dbg !1831

lor.lhs.false:                                    ; preds = %while.cond
  %3 = load i8*, i8** %start, align 8, !dbg !1832
  %4 = load i8, i8* %3, align 1, !dbg !1834
  %conv2 = sext i8 %4 to i32, !dbg !1834
  %cmp3 = icmp eq i32 %conv2, 32, !dbg !1835
  br i1 %cmp3, label %lor.end, label %lor.rhs, !dbg !1836

lor.rhs:                                          ; preds = %lor.lhs.false
  %5 = load i8*, i8** %start, align 8, !dbg !1837
  %6 = load i8, i8* %5, align 1, !dbg !1839
  %conv5 = sext i8 %6 to i32, !dbg !1839
  %cmp6 = icmp eq i32 %conv5, 44, !dbg !1840
  br label %lor.end, !dbg !1841

lor.end:                                          ; preds = %lor.rhs, %lor.lhs.false, %while.cond
  %7 = phi i1 [ true, %lor.lhs.false ], [ true, %while.cond ], [ %cmp6, %lor.rhs ]
  br i1 %7, label %while.body, label %while.end, !dbg !1842

while.body:                                       ; preds = %lor.end
  %8 = load i8*, i8** %start, align 8, !dbg !1844
  %incdec.ptr = getelementptr inbounds i8, i8* %8, i32 1, !dbg !1844
  store i8* %incdec.ptr, i8** %start, align 8, !dbg !1844
  br label %while.cond, !dbg !1845

while.end:                                        ; preds = %lor.end
  br label %while.cond8, !dbg !1847

while.cond8:                                      ; preds = %while.end80, %while.end
  %9 = load i8*, i8** %start, align 8, !dbg !1848
  %10 = load i8, i8* %9, align 1, !dbg !1849
  %conv9 = sext i8 %10 to i32, !dbg !1849
  %cmp10 = icmp ne i32 %conv9, 0, !dbg !1850
  br i1 %cmp10, label %while.body12, label %while.end81, !dbg !1851

while.body12:                                     ; preds = %while.cond8
  call void @llvm.dbg.declare(metadata i64* %length, metadata !1852, metadata !486), !dbg !1854
  %11 = load i8*, i8** %start, align 8, !dbg !1855
  store i8* %11, i8** %end, align 8, !dbg !1856
  br label %while.cond13, !dbg !1857

while.cond13:                                     ; preds = %while.body27, %while.body12
  %12 = load i8*, i8** %end, align 8, !dbg !1858
  %13 = load i8, i8* %12, align 1, !dbg !1860
  %conv14 = sext i8 %13 to i32, !dbg !1860
  %cmp15 = icmp ne i32 %conv14, 0, !dbg !1861
  br i1 %cmp15, label %land.lhs.true, label %land.end, !dbg !1862

land.lhs.true:                                    ; preds = %while.cond13
  %14 = load i8*, i8** %end, align 8, !dbg !1863
  %15 = load i8, i8* %14, align 1, !dbg !1865
  %conv17 = sext i8 %15 to i32, !dbg !1865
  %cmp18 = icmp ne i32 %conv17, 9, !dbg !1866
  br i1 %cmp18, label %land.lhs.true20, label %land.end, !dbg !1867

land.lhs.true20:                                  ; preds = %land.lhs.true
  %16 = load i8*, i8** %end, align 8, !dbg !1868
  %17 = load i8, i8* %16, align 1, !dbg !1869
  %conv21 = sext i8 %17 to i32, !dbg !1869
  %cmp22 = icmp ne i32 %conv21, 32, !dbg !1870
  br i1 %cmp22, label %land.rhs, label %land.end, !dbg !1871

land.rhs:                                         ; preds = %land.lhs.true20
  %18 = load i8*, i8** %end, align 8, !dbg !1872
  %19 = load i8, i8* %18, align 1, !dbg !1873
  %conv24 = sext i8 %19 to i32, !dbg !1873
  %cmp25 = icmp ne i32 %conv24, 44, !dbg !1874
  br label %land.end

land.end:                                         ; preds = %land.rhs, %land.lhs.true20, %land.lhs.true, %while.cond13
  %20 = phi i1 [ false, %land.lhs.true20 ], [ false, %land.lhs.true ], [ false, %while.cond13 ], [ %cmp25, %land.rhs ]
  br i1 %20, label %while.body27, label %while.end29, !dbg !1875

while.body27:                                     ; preds = %land.end
  %21 = load i8*, i8** %end, align 8, !dbg !1877
  %incdec.ptr28 = getelementptr inbounds i8, i8* %21, i32 1, !dbg !1877
  store i8* %incdec.ptr28, i8** %end, align 8, !dbg !1877
  br label %while.cond13, !dbg !1878

while.end29:                                      ; preds = %land.end
  %22 = load i8*, i8** %end, align 8, !dbg !1880
  %23 = load i8*, i8** %start, align 8, !dbg !1881
  %sub.ptr.lhs.cast = ptrtoint i8* %22 to i64, !dbg !1882
  %sub.ptr.rhs.cast = ptrtoint i8* %23 to i64, !dbg !1882
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !1882
  store i64 %sub.ptr.sub, i64* %length, align 8, !dbg !1883
  store %struct.flag* getelementptr inbounds ([25 x %struct.flag], [25 x %struct.flag]* @flags, i32 0, i32 0), %struct.flag** %flag, align 8, !dbg !1884
  br label %for.cond, !dbg !1886

for.cond:                                         ; preds = %for.inc, %while.end29
  %24 = load %struct.flag*, %struct.flag** %flag, align 8, !dbg !1887
  %name = getelementptr inbounds %struct.flag, %struct.flag* %24, i32 0, i32 0, !dbg !1890
  %25 = load i8*, i8** %name, align 8, !dbg !1890
  %cmp30 = icmp ne i8* %25, null, !dbg !1891
  br i1 %cmp30, label %for.body, label %for.end, !dbg !1892

for.body:                                         ; preds = %for.cond
  call void @llvm.dbg.declare(metadata i64* %flag_length, metadata !1893, metadata !486), !dbg !1895
  %26 = load %struct.flag*, %struct.flag** %flag, align 8, !dbg !1896
  %name32 = getelementptr inbounds %struct.flag, %struct.flag* %26, i32 0, i32 0, !dbg !1897
  %27 = load i8*, i8** %name32, align 8, !dbg !1897
  %call = call i64 @strlen(i8* %27) #12, !dbg !1898
  store i64 %call, i64* %flag_length, align 8, !dbg !1895
  %28 = load i64, i64* %length, align 8, !dbg !1899
  %29 = load i64, i64* %flag_length, align 8, !dbg !1901
  %cmp33 = icmp eq i64 %28, %29, !dbg !1902
  br i1 %cmp33, label %land.lhs.true35, label %if.else, !dbg !1903

land.lhs.true35:                                  ; preds = %for.body
  %30 = load i8*, i8** %start, align 8, !dbg !1904
  %31 = load %struct.flag*, %struct.flag** %flag, align 8, !dbg !1906
  %name36 = getelementptr inbounds %struct.flag, %struct.flag* %31, i32 0, i32 0, !dbg !1907
  %32 = load i8*, i8** %name36, align 8, !dbg !1907
  %33 = load i64, i64* %length, align 8, !dbg !1908
  %call37 = call i32 @memcmp(i8* %30, i8* %32, i64 %33) #12, !dbg !1909
  %cmp38 = icmp eq i32 %call37, 0, !dbg !1910
  br i1 %cmp38, label %if.then, label %if.else, !dbg !1911

if.then:                                          ; preds = %land.lhs.true35
  %34 = load %struct.flag*, %struct.flag** %flag, align 8, !dbg !1913
  %set40 = getelementptr inbounds %struct.flag, %struct.flag* %34, i32 0, i32 2, !dbg !1915
  %35 = load i64, i64* %set40, align 8, !dbg !1915
  %36 = load i64, i64* %clear, align 8, !dbg !1916
  %or = or i64 %36, %35, !dbg !1916
  store i64 %or, i64* %clear, align 8, !dbg !1916
  %37 = load %struct.flag*, %struct.flag** %flag, align 8, !dbg !1917
  %clear41 = getelementptr inbounds %struct.flag, %struct.flag* %37, i32 0, i32 3, !dbg !1918
  %38 = load i64, i64* %clear41, align 8, !dbg !1918
  %39 = load i64, i64* %set, align 8, !dbg !1919
  %or42 = or i64 %39, %38, !dbg !1919
  store i64 %or42, i64* %set, align 8, !dbg !1919
  br label %for.end, !dbg !1920

if.else:                                          ; preds = %land.lhs.true35, %for.body
  %40 = load i64, i64* %length, align 8, !dbg !1921
  %41 = load i64, i64* %flag_length, align 8, !dbg !1923
  %sub = sub i64 %41, 2, !dbg !1924
  %cmp43 = icmp eq i64 %40, %sub, !dbg !1925
  br i1 %cmp43, label %land.lhs.true45, label %if.end, !dbg !1926

land.lhs.true45:                                  ; preds = %if.else
  %42 = load i8*, i8** %start, align 8, !dbg !1927
  %43 = load %struct.flag*, %struct.flag** %flag, align 8, !dbg !1929
  %name46 = getelementptr inbounds %struct.flag, %struct.flag* %43, i32 0, i32 0, !dbg !1930
  %44 = load i8*, i8** %name46, align 8, !dbg !1930
  %add.ptr = getelementptr inbounds i8, i8* %44, i64 2, !dbg !1931
  %45 = load i64, i64* %length, align 8, !dbg !1932
  %call47 = call i32 @memcmp(i8* %42, i8* %add.ptr, i64 %45) #12, !dbg !1933
  %cmp48 = icmp eq i32 %call47, 0, !dbg !1934
  br i1 %cmp48, label %if.then50, label %if.end, !dbg !1935

if.then50:                                        ; preds = %land.lhs.true45
  %46 = load %struct.flag*, %struct.flag** %flag, align 8, !dbg !1936
  %set51 = getelementptr inbounds %struct.flag, %struct.flag* %46, i32 0, i32 2, !dbg !1938
  %47 = load i64, i64* %set51, align 8, !dbg !1938
  %48 = load i64, i64* %set, align 8, !dbg !1939
  %or52 = or i64 %48, %47, !dbg !1939
  store i64 %or52, i64* %set, align 8, !dbg !1939
  %49 = load %struct.flag*, %struct.flag** %flag, align 8, !dbg !1940
  %clear53 = getelementptr inbounds %struct.flag, %struct.flag* %49, i32 0, i32 3, !dbg !1941
  %50 = load i64, i64* %clear53, align 8, !dbg !1941
  %51 = load i64, i64* %clear, align 8, !dbg !1942
  %or54 = or i64 %51, %50, !dbg !1942
  store i64 %or54, i64* %clear, align 8, !dbg !1942
  br label %for.end, !dbg !1943

if.end:                                           ; preds = %land.lhs.true45, %if.else
  br label %if.end55

if.end55:                                         ; preds = %if.end
  br label %for.inc, !dbg !1944

for.inc:                                          ; preds = %if.end55
  %52 = load %struct.flag*, %struct.flag** %flag, align 8, !dbg !1945
  %incdec.ptr56 = getelementptr inbounds %struct.flag, %struct.flag* %52, i32 1, !dbg !1945
  store %struct.flag* %incdec.ptr56, %struct.flag** %flag, align 8, !dbg !1945
  br label %for.cond, !dbg !1947

for.end:                                          ; preds = %if.then50, %if.then, %for.cond
  %53 = load %struct.flag*, %struct.flag** %flag, align 8, !dbg !1948
  %name57 = getelementptr inbounds %struct.flag, %struct.flag* %53, i32 0, i32 0, !dbg !1950
  %54 = load i8*, i8** %name57, align 8, !dbg !1950
  %cmp58 = icmp eq i8* %54, null, !dbg !1951
  br i1 %cmp58, label %land.lhs.true60, label %if.end64, !dbg !1952

land.lhs.true60:                                  ; preds = %for.end
  %55 = load i8*, i8** %failed, align 8, !dbg !1953
  %cmp61 = icmp eq i8* %55, null, !dbg !1955
  br i1 %cmp61, label %if.then63, label %if.end64, !dbg !1956

if.then63:                                        ; preds = %land.lhs.true60
  %56 = load i8*, i8** %start, align 8, !dbg !1957
  store i8* %56, i8** %failed, align 8, !dbg !1958
  br label %if.end64, !dbg !1959

if.end64:                                         ; preds = %if.then63, %land.lhs.true60, %for.end
  %57 = load i8*, i8** %end, align 8, !dbg !1960
  store i8* %57, i8** %start, align 8, !dbg !1961
  br label %while.cond65, !dbg !1962

while.cond65:                                     ; preds = %while.body78, %if.end64
  %58 = load i8*, i8** %start, align 8, !dbg !1963
  %59 = load i8, i8* %58, align 1, !dbg !1964
  %conv66 = sext i8 %59 to i32, !dbg !1964
  %cmp67 = icmp eq i32 %conv66, 9, !dbg !1965
  br i1 %cmp67, label %lor.end77, label %lor.lhs.false69, !dbg !1966

lor.lhs.false69:                                  ; preds = %while.cond65
  %60 = load i8*, i8** %start, align 8, !dbg !1967
  %61 = load i8, i8* %60, align 1, !dbg !1968
  %conv70 = sext i8 %61 to i32, !dbg !1968
  %cmp71 = icmp eq i32 %conv70, 32, !dbg !1969
  br i1 %cmp71, label %lor.end77, label %lor.rhs73, !dbg !1970

lor.rhs73:                                        ; preds = %lor.lhs.false69
  %62 = load i8*, i8** %start, align 8, !dbg !1971
  %63 = load i8, i8* %62, align 1, !dbg !1972
  %conv74 = sext i8 %63 to i32, !dbg !1972
  %cmp75 = icmp eq i32 %conv74, 44, !dbg !1973
  br label %lor.end77, !dbg !1974

lor.end77:                                        ; preds = %lor.rhs73, %lor.lhs.false69, %while.cond65
  %64 = phi i1 [ true, %lor.lhs.false69 ], [ true, %while.cond65 ], [ %cmp75, %lor.rhs73 ]
  br i1 %64, label %while.body78, label %while.end80, !dbg !1975

while.body78:                                     ; preds = %lor.end77
  %65 = load i8*, i8** %start, align 8, !dbg !1976
  %incdec.ptr79 = getelementptr inbounds i8, i8* %65, i32 1, !dbg !1976
  store i8* %incdec.ptr79, i8** %start, align 8, !dbg !1976
  br label %while.cond65, !dbg !1977

while.end80:                                      ; preds = %lor.end77
  br label %while.cond8, !dbg !1979

while.end81:                                      ; preds = %while.cond8
  %66 = load i64*, i64** %setp.addr, align 8, !dbg !1980
  %tobool = icmp ne i64* %66, null, !dbg !1980
  br i1 %tobool, label %if.then82, label %if.end83, !dbg !1982

if.then82:                                        ; preds = %while.end81
  %67 = load i64, i64* %set, align 8, !dbg !1983
  %68 = load i64*, i64** %setp.addr, align 8, !dbg !1984
  store i64 %67, i64* %68, align 8, !dbg !1985
  br label %if.end83, !dbg !1986

if.end83:                                         ; preds = %if.then82, %while.end81
  %69 = load i64*, i64** %clrp.addr, align 8, !dbg !1987
  %tobool84 = icmp ne i64* %69, null, !dbg !1987
  br i1 %tobool84, label %if.then85, label %if.end86, !dbg !1989

if.then85:                                        ; preds = %if.end83
  %70 = load i64, i64* %clear, align 8, !dbg !1990
  %71 = load i64*, i64** %clrp.addr, align 8, !dbg !1991
  store i64 %70, i64* %71, align 8, !dbg !1992
  br label %if.end86, !dbg !1993

if.end86:                                         ; preds = %if.then85, %if.end83
  %72 = load i8*, i8** %failed, align 8, !dbg !1994
  ret i8* %72, !dbg !1995
}

; Function Attrs: nounwind uwtable
define i32* @archive_entry_copy_fflags_text_w(%struct.archive_entry* %entry1, i32* %flags) #0 !dbg !322 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %flags.addr = alloca i32*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1996, metadata !486), !dbg !1997
  store i32* %flags, i32** %flags.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %flags.addr, metadata !1998, metadata !486), !dbg !1999
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2000
  %ae_fflags_text = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 5, !dbg !2001
  %1 = load i32*, i32** %flags.addr, align 8, !dbg !2002
  %call = call i32 @archive_mstring_copy_wcs(%struct.archive_mstring* %ae_fflags_text, i32* %1), !dbg !2003
  %2 = load i32*, i32** %flags.addr, align 8, !dbg !2004
  %3 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2005
  %ae_fflags_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %3, i32 0, i32 6, !dbg !2006
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2007
  %ae_fflags_clear = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %4, i32 0, i32 7, !dbg !2008
  %call2 = call i32* @ae_wcstofflags(i32* %2, i64* %ae_fflags_set, i64* %ae_fflags_clear), !dbg !2009
  ret i32* %call2, !dbg !2010
}

declare i32 @archive_mstring_copy_wcs(%struct.archive_mstring*, i32*) #2

; Function Attrs: nounwind uwtable
define internal i32* @ae_wcstofflags(i32* %s, i64* %setp, i64* %clrp) #0 !dbg !468 {
entry:
  %s.addr = alloca i32*, align 8
  %setp.addr = alloca i64*, align 8
  %clrp.addr = alloca i64*, align 8
  %start = alloca i32*, align 8
  %end = alloca i32*, align 8
  %flag = alloca %struct.flag*, align 8
  %set = alloca i64, align 8
  %clear = alloca i64, align 8
  %failed = alloca i32*, align 8
  %length = alloca i64, align 8
  %flag_length = alloca i64, align 8
  store i32* %s, i32** %s.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %s.addr, metadata !2011, metadata !486), !dbg !2012
  store i64* %setp, i64** %setp.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %setp.addr, metadata !2013, metadata !486), !dbg !2014
  store i64* %clrp, i64** %clrp.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %clrp.addr, metadata !2015, metadata !486), !dbg !2016
  call void @llvm.dbg.declare(metadata i32** %start, metadata !2017, metadata !486), !dbg !2018
  call void @llvm.dbg.declare(metadata i32** %end, metadata !2019, metadata !486), !dbg !2020
  call void @llvm.dbg.declare(metadata %struct.flag** %flag, metadata !2021, metadata !486), !dbg !2022
  call void @llvm.dbg.declare(metadata i64* %set, metadata !2023, metadata !486), !dbg !2024
  call void @llvm.dbg.declare(metadata i64* %clear, metadata !2025, metadata !486), !dbg !2026
  call void @llvm.dbg.declare(metadata i32** %failed, metadata !2027, metadata !486), !dbg !2028
  store i64 0, i64* %clear, align 8, !dbg !2029
  store i64 0, i64* %set, align 8, !dbg !2030
  %0 = load i32*, i32** %s.addr, align 8, !dbg !2031
  store i32* %0, i32** %start, align 8, !dbg !2032
  store i32* null, i32** %failed, align 8, !dbg !2033
  br label %while.cond, !dbg !2034

while.cond:                                       ; preds = %while.body, %entry
  %1 = load i32*, i32** %start, align 8, !dbg !2035
  %2 = load i32, i32* %1, align 4, !dbg !2037
  %cmp = icmp eq i32 %2, 9, !dbg !2038
  br i1 %cmp, label %lor.end, label %lor.lhs.false, !dbg !2039

lor.lhs.false:                                    ; preds = %while.cond
  %3 = load i32*, i32** %start, align 8, !dbg !2040
  %4 = load i32, i32* %3, align 4, !dbg !2042
  %cmp1 = icmp eq i32 %4, 32, !dbg !2043
  br i1 %cmp1, label %lor.end, label %lor.rhs, !dbg !2044

lor.rhs:                                          ; preds = %lor.lhs.false
  %5 = load i32*, i32** %start, align 8, !dbg !2045
  %6 = load i32, i32* %5, align 4, !dbg !2047
  %cmp2 = icmp eq i32 %6, 44, !dbg !2048
  br label %lor.end, !dbg !2049

lor.end:                                          ; preds = %lor.rhs, %lor.lhs.false, %while.cond
  %7 = phi i1 [ true, %lor.lhs.false ], [ true, %while.cond ], [ %cmp2, %lor.rhs ]
  br i1 %7, label %while.body, label %while.end, !dbg !2050

while.body:                                       ; preds = %lor.end
  %8 = load i32*, i32** %start, align 8, !dbg !2052
  %incdec.ptr = getelementptr inbounds i32, i32* %8, i32 1, !dbg !2052
  store i32* %incdec.ptr, i32** %start, align 8, !dbg !2052
  br label %while.cond, !dbg !2053

while.end:                                        ; preds = %lor.end
  br label %while.cond3, !dbg !2055

while.cond3:                                      ; preds = %while.end52, %while.end
  %9 = load i32*, i32** %start, align 8, !dbg !2056
  %10 = load i32, i32* %9, align 4, !dbg !2057
  %cmp4 = icmp ne i32 %10, 0, !dbg !2058
  br i1 %cmp4, label %while.body5, label %while.end53, !dbg !2059

while.body5:                                      ; preds = %while.cond3
  call void @llvm.dbg.declare(metadata i64* %length, metadata !2060, metadata !486), !dbg !2062
  %11 = load i32*, i32** %start, align 8, !dbg !2063
  store i32* %11, i32** %end, align 8, !dbg !2064
  br label %while.cond6, !dbg !2065

while.cond6:                                      ; preds = %while.body12, %while.body5
  %12 = load i32*, i32** %end, align 8, !dbg !2066
  %13 = load i32, i32* %12, align 4, !dbg !2068
  %cmp7 = icmp ne i32 %13, 0, !dbg !2069
  br i1 %cmp7, label %land.lhs.true, label %land.end, !dbg !2070

land.lhs.true:                                    ; preds = %while.cond6
  %14 = load i32*, i32** %end, align 8, !dbg !2071
  %15 = load i32, i32* %14, align 4, !dbg !2073
  %cmp8 = icmp ne i32 %15, 9, !dbg !2074
  br i1 %cmp8, label %land.lhs.true9, label %land.end, !dbg !2075

land.lhs.true9:                                   ; preds = %land.lhs.true
  %16 = load i32*, i32** %end, align 8, !dbg !2076
  %17 = load i32, i32* %16, align 4, !dbg !2077
  %cmp10 = icmp ne i32 %17, 32, !dbg !2078
  br i1 %cmp10, label %land.rhs, label %land.end, !dbg !2079

land.rhs:                                         ; preds = %land.lhs.true9
  %18 = load i32*, i32** %end, align 8, !dbg !2080
  %19 = load i32, i32* %18, align 4, !dbg !2081
  %cmp11 = icmp ne i32 %19, 44, !dbg !2082
  br label %land.end

land.end:                                         ; preds = %land.rhs, %land.lhs.true9, %land.lhs.true, %while.cond6
  %20 = phi i1 [ false, %land.lhs.true9 ], [ false, %land.lhs.true ], [ false, %while.cond6 ], [ %cmp11, %land.rhs ]
  br i1 %20, label %while.body12, label %while.end14, !dbg !2083

while.body12:                                     ; preds = %land.end
  %21 = load i32*, i32** %end, align 8, !dbg !2085
  %incdec.ptr13 = getelementptr inbounds i32, i32* %21, i32 1, !dbg !2085
  store i32* %incdec.ptr13, i32** %end, align 8, !dbg !2085
  br label %while.cond6, !dbg !2086

while.end14:                                      ; preds = %land.end
  %22 = load i32*, i32** %end, align 8, !dbg !2088
  %23 = load i32*, i32** %start, align 8, !dbg !2089
  %sub.ptr.lhs.cast = ptrtoint i32* %22 to i64, !dbg !2090
  %sub.ptr.rhs.cast = ptrtoint i32* %23 to i64, !dbg !2090
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !2090
  %sub.ptr.div = sdiv exact i64 %sub.ptr.sub, 4, !dbg !2090
  store i64 %sub.ptr.div, i64* %length, align 8, !dbg !2091
  store %struct.flag* getelementptr inbounds ([25 x %struct.flag], [25 x %struct.flag]* @flags, i32 0, i32 0), %struct.flag** %flag, align 8, !dbg !2092
  br label %for.cond, !dbg !2094

for.cond:                                         ; preds = %for.inc, %while.end14
  %24 = load %struct.flag*, %struct.flag** %flag, align 8, !dbg !2095
  %wname = getelementptr inbounds %struct.flag, %struct.flag* %24, i32 0, i32 1, !dbg !2098
  %25 = load i32*, i32** %wname, align 8, !dbg !2098
  %cmp15 = icmp ne i32* %25, null, !dbg !2099
  br i1 %cmp15, label %for.body, label %for.end, !dbg !2100

for.body:                                         ; preds = %for.cond
  call void @llvm.dbg.declare(metadata i64* %flag_length, metadata !2101, metadata !486), !dbg !2103
  %26 = load %struct.flag*, %struct.flag** %flag, align 8, !dbg !2104
  %wname16 = getelementptr inbounds %struct.flag, %struct.flag* %26, i32 0, i32 1, !dbg !2105
  %27 = load i32*, i32** %wname16, align 8, !dbg !2105
  %call = call i64 @wcslen(i32* %27) #12, !dbg !2106
  store i64 %call, i64* %flag_length, align 8, !dbg !2103
  %28 = load i64, i64* %length, align 8, !dbg !2107
  %29 = load i64, i64* %flag_length, align 8, !dbg !2109
  %cmp17 = icmp eq i64 %28, %29, !dbg !2110
  br i1 %cmp17, label %land.lhs.true18, label %if.else, !dbg !2111

land.lhs.true18:                                  ; preds = %for.body
  %30 = load i32*, i32** %start, align 8, !dbg !2112
  %31 = load %struct.flag*, %struct.flag** %flag, align 8, !dbg !2114
  %wname19 = getelementptr inbounds %struct.flag, %struct.flag* %31, i32 0, i32 1, !dbg !2115
  %32 = load i32*, i32** %wname19, align 8, !dbg !2115
  %33 = load i64, i64* %length, align 8, !dbg !2116
  %call20 = call i32 @wmemcmp(i32* %30, i32* %32, i64 %33) #12, !dbg !2117
  %cmp21 = icmp eq i32 %call20, 0, !dbg !2118
  br i1 %cmp21, label %if.then, label %if.else, !dbg !2119

if.then:                                          ; preds = %land.lhs.true18
  %34 = load %struct.flag*, %struct.flag** %flag, align 8, !dbg !2121
  %set22 = getelementptr inbounds %struct.flag, %struct.flag* %34, i32 0, i32 2, !dbg !2123
  %35 = load i64, i64* %set22, align 8, !dbg !2123
  %36 = load i64, i64* %clear, align 8, !dbg !2124
  %or = or i64 %36, %35, !dbg !2124
  store i64 %or, i64* %clear, align 8, !dbg !2124
  %37 = load %struct.flag*, %struct.flag** %flag, align 8, !dbg !2125
  %clear23 = getelementptr inbounds %struct.flag, %struct.flag* %37, i32 0, i32 3, !dbg !2126
  %38 = load i64, i64* %clear23, align 8, !dbg !2126
  %39 = load i64, i64* %set, align 8, !dbg !2127
  %or24 = or i64 %39, %38, !dbg !2127
  store i64 %or24, i64* %set, align 8, !dbg !2127
  br label %for.end, !dbg !2128

if.else:                                          ; preds = %land.lhs.true18, %for.body
  %40 = load i64, i64* %length, align 8, !dbg !2129
  %41 = load i64, i64* %flag_length, align 8, !dbg !2131
  %sub = sub i64 %41, 2, !dbg !2132
  %cmp25 = icmp eq i64 %40, %sub, !dbg !2133
  br i1 %cmp25, label %land.lhs.true26, label %if.end, !dbg !2134

land.lhs.true26:                                  ; preds = %if.else
  %42 = load i32*, i32** %start, align 8, !dbg !2135
  %43 = load %struct.flag*, %struct.flag** %flag, align 8, !dbg !2137
  %wname27 = getelementptr inbounds %struct.flag, %struct.flag* %43, i32 0, i32 1, !dbg !2138
  %44 = load i32*, i32** %wname27, align 8, !dbg !2138
  %add.ptr = getelementptr inbounds i32, i32* %44, i64 2, !dbg !2139
  %45 = load i64, i64* %length, align 8, !dbg !2140
  %call28 = call i32 @wmemcmp(i32* %42, i32* %add.ptr, i64 %45) #12, !dbg !2141
  %cmp29 = icmp eq i32 %call28, 0, !dbg !2142
  br i1 %cmp29, label %if.then30, label %if.end, !dbg !2143

if.then30:                                        ; preds = %land.lhs.true26
  %46 = load %struct.flag*, %struct.flag** %flag, align 8, !dbg !2144
  %set31 = getelementptr inbounds %struct.flag, %struct.flag* %46, i32 0, i32 2, !dbg !2146
  %47 = load i64, i64* %set31, align 8, !dbg !2146
  %48 = load i64, i64* %set, align 8, !dbg !2147
  %or32 = or i64 %48, %47, !dbg !2147
  store i64 %or32, i64* %set, align 8, !dbg !2147
  %49 = load %struct.flag*, %struct.flag** %flag, align 8, !dbg !2148
  %clear33 = getelementptr inbounds %struct.flag, %struct.flag* %49, i32 0, i32 3, !dbg !2149
  %50 = load i64, i64* %clear33, align 8, !dbg !2149
  %51 = load i64, i64* %clear, align 8, !dbg !2150
  %or34 = or i64 %51, %50, !dbg !2150
  store i64 %or34, i64* %clear, align 8, !dbg !2150
  br label %for.end, !dbg !2151

if.end:                                           ; preds = %land.lhs.true26, %if.else
  br label %if.end35

if.end35:                                         ; preds = %if.end
  br label %for.inc, !dbg !2152

for.inc:                                          ; preds = %if.end35
  %52 = load %struct.flag*, %struct.flag** %flag, align 8, !dbg !2153
  %incdec.ptr36 = getelementptr inbounds %struct.flag, %struct.flag* %52, i32 1, !dbg !2153
  store %struct.flag* %incdec.ptr36, %struct.flag** %flag, align 8, !dbg !2153
  br label %for.cond, !dbg !2155

for.end:                                          ; preds = %if.then30, %if.then, %for.cond
  %53 = load %struct.flag*, %struct.flag** %flag, align 8, !dbg !2156
  %wname37 = getelementptr inbounds %struct.flag, %struct.flag* %53, i32 0, i32 1, !dbg !2158
  %54 = load i32*, i32** %wname37, align 8, !dbg !2158
  %cmp38 = icmp eq i32* %54, null, !dbg !2159
  br i1 %cmp38, label %land.lhs.true39, label %if.end42, !dbg !2160

land.lhs.true39:                                  ; preds = %for.end
  %55 = load i32*, i32** %failed, align 8, !dbg !2161
  %cmp40 = icmp eq i32* %55, null, !dbg !2163
  br i1 %cmp40, label %if.then41, label %if.end42, !dbg !2164

if.then41:                                        ; preds = %land.lhs.true39
  %56 = load i32*, i32** %start, align 8, !dbg !2165
  store i32* %56, i32** %failed, align 8, !dbg !2166
  br label %if.end42, !dbg !2167

if.end42:                                         ; preds = %if.then41, %land.lhs.true39, %for.end
  %57 = load i32*, i32** %end, align 8, !dbg !2168
  store i32* %57, i32** %start, align 8, !dbg !2169
  br label %while.cond43, !dbg !2170

while.cond43:                                     ; preds = %while.body50, %if.end42
  %58 = load i32*, i32** %start, align 8, !dbg !2171
  %59 = load i32, i32* %58, align 4, !dbg !2172
  %cmp44 = icmp eq i32 %59, 9, !dbg !2173
  br i1 %cmp44, label %lor.end49, label %lor.lhs.false45, !dbg !2174

lor.lhs.false45:                                  ; preds = %while.cond43
  %60 = load i32*, i32** %start, align 8, !dbg !2175
  %61 = load i32, i32* %60, align 4, !dbg !2176
  %cmp46 = icmp eq i32 %61, 32, !dbg !2177
  br i1 %cmp46, label %lor.end49, label %lor.rhs47, !dbg !2178

lor.rhs47:                                        ; preds = %lor.lhs.false45
  %62 = load i32*, i32** %start, align 8, !dbg !2179
  %63 = load i32, i32* %62, align 4, !dbg !2180
  %cmp48 = icmp eq i32 %63, 44, !dbg !2181
  br label %lor.end49, !dbg !2182

lor.end49:                                        ; preds = %lor.rhs47, %lor.lhs.false45, %while.cond43
  %64 = phi i1 [ true, %lor.lhs.false45 ], [ true, %while.cond43 ], [ %cmp48, %lor.rhs47 ]
  br i1 %64, label %while.body50, label %while.end52, !dbg !2183

while.body50:                                     ; preds = %lor.end49
  %65 = load i32*, i32** %start, align 8, !dbg !2184
  %incdec.ptr51 = getelementptr inbounds i32, i32* %65, i32 1, !dbg !2184
  store i32* %incdec.ptr51, i32** %start, align 8, !dbg !2184
  br label %while.cond43, !dbg !2185

while.end52:                                      ; preds = %lor.end49
  br label %while.cond3, !dbg !2187

while.end53:                                      ; preds = %while.cond3
  %66 = load i64*, i64** %setp.addr, align 8, !dbg !2188
  %tobool = icmp ne i64* %66, null, !dbg !2188
  br i1 %tobool, label %if.then54, label %if.end55, !dbg !2190

if.then54:                                        ; preds = %while.end53
  %67 = load i64, i64* %set, align 8, !dbg !2191
  %68 = load i64*, i64** %setp.addr, align 8, !dbg !2192
  store i64 %67, i64* %68, align 8, !dbg !2193
  br label %if.end55, !dbg !2194

if.end55:                                         ; preds = %if.then54, %while.end53
  %69 = load i64*, i64** %clrp.addr, align 8, !dbg !2195
  %tobool56 = icmp ne i64* %69, null, !dbg !2195
  br i1 %tobool56, label %if.then57, label %if.end58, !dbg !2197

if.then57:                                        ; preds = %if.end55
  %70 = load i64, i64* %clear, align 8, !dbg !2198
  %71 = load i64*, i64** %clrp.addr, align 8, !dbg !2199
  store i64 %70, i64* %71, align 8, !dbg !2200
  br label %if.end58, !dbg !2201

if.end58:                                         ; preds = %if.then57, %if.end55
  %72 = load i32*, i32** %failed, align 8, !dbg !2202
  ret i32* %72, !dbg !2203
}

; Function Attrs: nounwind uwtable
define void @archive_entry_set_gid(%struct.archive_entry* %entry1, i64 %g) #0 !dbg !325 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %g.addr = alloca i64, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2204, metadata !486), !dbg !2205
  store i64 %g, i64* %g.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %g.addr, metadata !2206, metadata !486), !dbg !2207
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2208
  %stat_valid = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 2, !dbg !2209
  store i32 0, i32* %stat_valid, align 8, !dbg !2210
  %1 = load i64, i64* %g.addr, align 8, !dbg !2211
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2212
  %ae_stat = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 3, !dbg !2213
  %aest_gid = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat, i32 0, i32 8, !dbg !2214
  store i64 %1, i64* %aest_gid, align 8, !dbg !2215
  ret void, !dbg !2216
}

; Function Attrs: nounwind uwtable
define void @archive_entry_set_gname(%struct.archive_entry* %entry1, i8* %name) #0 !dbg !328 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %name.addr = alloca i8*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2217, metadata !486), !dbg !2218
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !2219, metadata !486), !dbg !2220
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2221
  %ae_gname = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 8, !dbg !2222
  %1 = load i8*, i8** %name.addr, align 8, !dbg !2223
  %call = call i32 @archive_mstring_copy_mbs(%struct.archive_mstring* %ae_gname, i8* %1), !dbg !2224
  ret void, !dbg !2225
}

; Function Attrs: nounwind uwtable
define void @archive_entry_set_gname_utf8(%struct.archive_entry* %entry1, i8* %name) #0 !dbg !331 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %name.addr = alloca i8*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2226, metadata !486), !dbg !2227
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !2228, metadata !486), !dbg !2229
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2230
  %ae_gname = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 8, !dbg !2231
  %1 = load i8*, i8** %name.addr, align 8, !dbg !2232
  %call = call i32 @archive_mstring_copy_utf8(%struct.archive_mstring* %ae_gname, i8* %1), !dbg !2233
  ret void, !dbg !2234
}

declare i32 @archive_mstring_copy_utf8(%struct.archive_mstring*, i8*) #2

; Function Attrs: nounwind uwtable
define void @archive_entry_copy_gname(%struct.archive_entry* %entry1, i8* %name) #0 !dbg !332 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %name.addr = alloca i8*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2235, metadata !486), !dbg !2236
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !2237, metadata !486), !dbg !2238
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2239
  %ae_gname = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 8, !dbg !2240
  %1 = load i8*, i8** %name.addr, align 8, !dbg !2241
  %call = call i32 @archive_mstring_copy_mbs(%struct.archive_mstring* %ae_gname, i8* %1), !dbg !2242
  ret void, !dbg !2243
}

; Function Attrs: nounwind uwtable
define void @archive_entry_copy_gname_w(%struct.archive_entry* %entry1, i32* %name) #0 !dbg !333 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %name.addr = alloca i32*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2244, metadata !486), !dbg !2245
  store i32* %name, i32** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %name.addr, metadata !2246, metadata !486), !dbg !2247
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2248
  %ae_gname = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 8, !dbg !2249
  %1 = load i32*, i32** %name.addr, align 8, !dbg !2250
  %call = call i32 @archive_mstring_copy_wcs(%struct.archive_mstring* %ae_gname, i32* %1), !dbg !2251
  ret void, !dbg !2252
}

; Function Attrs: nounwind uwtable
define i32 @archive_entry_update_gname_utf8(%struct.archive_entry* %entry1, i8* %name) #0 !dbg !336 {
entry:
  %retval = alloca i32, align 4
  %entry.addr = alloca %struct.archive_entry*, align 8
  %name.addr = alloca i8*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2253, metadata !486), !dbg !2254
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !2255, metadata !486), !dbg !2256
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2257
  %archive = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 0, !dbg !2259
  %1 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !2259
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2260
  %ae_gname = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 8, !dbg !2261
  %3 = load i8*, i8** %name.addr, align 8, !dbg !2262
  %call = call i32 @archive_mstring_update_utf8(%struct.archive* %1, %struct.archive_mstring* %ae_gname, i8* %3), !dbg !2263
  %cmp = icmp eq i32 %call, 0, !dbg !2264
  br i1 %cmp, label %if.then, label %if.end, !dbg !2265

if.then:                                          ; preds = %entry
  store i32 1, i32* %retval, align 4, !dbg !2266
  br label %return, !dbg !2266

if.end:                                           ; preds = %entry
  %call2 = call i32* @__errno_location() #1, !dbg !2267
  %4 = load i32, i32* %call2, align 4, !dbg !2267
  %cmp3 = icmp eq i32 %4, 12, !dbg !2269
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !2270

if.then4:                                         ; preds = %if.end
  call void @__archive_errx(i32 1, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0)) #11, !dbg !2271
  unreachable, !dbg !2271

if.end5:                                          ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !2272
  br label %return, !dbg !2272

return:                                           ; preds = %if.end5, %if.then
  %5 = load i32, i32* %retval, align 4, !dbg !2273
  ret i32 %5, !dbg !2273
}

declare i32 @archive_mstring_update_utf8(%struct.archive*, %struct.archive_mstring*, i8*) #2

; Function Attrs: nounwind uwtable
define i32 @_archive_entry_copy_gname_l(%struct.archive_entry* %entry1, i8* %name, i64 %len, %struct.archive_string_conv* %sc) #0 !dbg !339 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %name.addr = alloca i8*, align 8
  %len.addr = alloca i64, align 8
  %sc.addr = alloca %struct.archive_string_conv*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2274, metadata !486), !dbg !2275
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !2276, metadata !486), !dbg !2277
  store i64 %len, i64* %len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %len.addr, metadata !2278, metadata !486), !dbg !2279
  store %struct.archive_string_conv* %sc, %struct.archive_string_conv** %sc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string_conv** %sc.addr, metadata !2280, metadata !486), !dbg !2281
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2282
  %ae_gname = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 8, !dbg !2283
  %1 = load i8*, i8** %name.addr, align 8, !dbg !2284
  %2 = load i64, i64* %len.addr, align 8, !dbg !2285
  %3 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sc.addr, align 8, !dbg !2286
  %call = call i32 @archive_mstring_copy_mbs_len_l(%struct.archive_mstring* %ae_gname, i8* %1, i64 %2, %struct.archive_string_conv* %3), !dbg !2287
  ret i32 %call, !dbg !2288
}

declare i32 @archive_mstring_copy_mbs_len_l(%struct.archive_mstring*, i8*, i64, %struct.archive_string_conv*) #2

; Function Attrs: nounwind uwtable
define void @archive_entry_set_ino(%struct.archive_entry* %entry1, i64 %ino) #0 !dbg !342 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %ino.addr = alloca i64, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2289, metadata !486), !dbg !2290
  store i64 %ino, i64* %ino.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %ino.addr, metadata !2291, metadata !486), !dbg !2292
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2293
  %stat_valid = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 2, !dbg !2294
  store i32 0, i32* %stat_valid, align 8, !dbg !2295
  %1 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2296
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %1, i32 0, i32 4, !dbg !2297
  %2 = load i32, i32* %ae_set, align 8, !dbg !2298
  %or = or i32 %2, 128, !dbg !2298
  store i32 %or, i32* %ae_set, align 8, !dbg !2298
  %3 = load i64, i64* %ino.addr, align 8, !dbg !2299
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2300
  %ae_stat = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %4, i32 0, i32 3, !dbg !2301
  %aest_ino = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat, i32 0, i32 9, !dbg !2302
  store i64 %3, i64* %aest_ino, align 8, !dbg !2303
  ret void, !dbg !2304
}

; Function Attrs: nounwind uwtable
define void @archive_entry_set_ino64(%struct.archive_entry* %entry1, i64 %ino) #0 !dbg !343 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %ino.addr = alloca i64, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2305, metadata !486), !dbg !2306
  store i64 %ino, i64* %ino.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %ino.addr, metadata !2307, metadata !486), !dbg !2308
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2309
  %stat_valid = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 2, !dbg !2310
  store i32 0, i32* %stat_valid, align 8, !dbg !2311
  %1 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2312
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %1, i32 0, i32 4, !dbg !2313
  %2 = load i32, i32* %ae_set, align 8, !dbg !2314
  %or = or i32 %2, 128, !dbg !2314
  store i32 %or, i32* %ae_set, align 8, !dbg !2314
  %3 = load i64, i64* %ino.addr, align 8, !dbg !2315
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2316
  %ae_stat = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %4, i32 0, i32 3, !dbg !2317
  %aest_ino = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat, i32 0, i32 9, !dbg !2318
  store i64 %3, i64* %aest_ino, align 8, !dbg !2319
  ret void, !dbg !2320
}

; Function Attrs: nounwind uwtable
define void @archive_entry_set_hardlink(%struct.archive_entry* %entry1, i8* %target) #0 !dbg !344 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %target.addr = alloca i8*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2321, metadata !486), !dbg !2322
  store i8* %target, i8** %target.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %target.addr, metadata !2323, metadata !486), !dbg !2324
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2325
  %ae_hardlink = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 9, !dbg !2326
  %1 = load i8*, i8** %target.addr, align 8, !dbg !2327
  %call = call i32 @archive_mstring_copy_mbs(%struct.archive_mstring* %ae_hardlink, i8* %1), !dbg !2328
  %2 = load i8*, i8** %target.addr, align 8, !dbg !2329
  %cmp = icmp ne i8* %2, null, !dbg !2331
  br i1 %cmp, label %if.then, label %if.else, !dbg !2332

if.then:                                          ; preds = %entry
  %3 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2333
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %3, i32 0, i32 4, !dbg !2334
  %4 = load i32, i32* %ae_set, align 8, !dbg !2335
  %or = or i32 %4, 1, !dbg !2335
  store i32 %or, i32* %ae_set, align 8, !dbg !2335
  br label %if.end, !dbg !2333

if.else:                                          ; preds = %entry
  %5 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2336
  %ae_set2 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %5, i32 0, i32 4, !dbg !2337
  %6 = load i32, i32* %ae_set2, align 8, !dbg !2338
  %and = and i32 %6, -2, !dbg !2338
  store i32 %and, i32* %ae_set2, align 8, !dbg !2338
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  ret void, !dbg !2339
}

; Function Attrs: nounwind uwtable
define void @archive_entry_set_hardlink_utf8(%struct.archive_entry* %entry1, i8* %target) #0 !dbg !345 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %target.addr = alloca i8*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2340, metadata !486), !dbg !2341
  store i8* %target, i8** %target.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %target.addr, metadata !2342, metadata !486), !dbg !2343
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2344
  %ae_hardlink = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 9, !dbg !2345
  %1 = load i8*, i8** %target.addr, align 8, !dbg !2346
  %call = call i32 @archive_mstring_copy_utf8(%struct.archive_mstring* %ae_hardlink, i8* %1), !dbg !2347
  %2 = load i8*, i8** %target.addr, align 8, !dbg !2348
  %cmp = icmp ne i8* %2, null, !dbg !2350
  br i1 %cmp, label %if.then, label %if.else, !dbg !2351

if.then:                                          ; preds = %entry
  %3 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2352
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %3, i32 0, i32 4, !dbg !2353
  %4 = load i32, i32* %ae_set, align 8, !dbg !2354
  %or = or i32 %4, 1, !dbg !2354
  store i32 %or, i32* %ae_set, align 8, !dbg !2354
  br label %if.end, !dbg !2352

if.else:                                          ; preds = %entry
  %5 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2355
  %ae_set2 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %5, i32 0, i32 4, !dbg !2356
  %6 = load i32, i32* %ae_set2, align 8, !dbg !2357
  %and = and i32 %6, -2, !dbg !2357
  store i32 %and, i32* %ae_set2, align 8, !dbg !2357
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  ret void, !dbg !2358
}

; Function Attrs: nounwind uwtable
define void @archive_entry_copy_hardlink(%struct.archive_entry* %entry1, i8* %target) #0 !dbg !346 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %target.addr = alloca i8*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2359, metadata !486), !dbg !2360
  store i8* %target, i8** %target.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %target.addr, metadata !2361, metadata !486), !dbg !2362
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2363
  %ae_hardlink = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 9, !dbg !2364
  %1 = load i8*, i8** %target.addr, align 8, !dbg !2365
  %call = call i32 @archive_mstring_copy_mbs(%struct.archive_mstring* %ae_hardlink, i8* %1), !dbg !2366
  %2 = load i8*, i8** %target.addr, align 8, !dbg !2367
  %cmp = icmp ne i8* %2, null, !dbg !2369
  br i1 %cmp, label %if.then, label %if.else, !dbg !2370

if.then:                                          ; preds = %entry
  %3 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2371
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %3, i32 0, i32 4, !dbg !2372
  %4 = load i32, i32* %ae_set, align 8, !dbg !2373
  %or = or i32 %4, 1, !dbg !2373
  store i32 %or, i32* %ae_set, align 8, !dbg !2373
  br label %if.end, !dbg !2371

if.else:                                          ; preds = %entry
  %5 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2374
  %ae_set2 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %5, i32 0, i32 4, !dbg !2375
  %6 = load i32, i32* %ae_set2, align 8, !dbg !2376
  %and = and i32 %6, -2, !dbg !2376
  store i32 %and, i32* %ae_set2, align 8, !dbg !2376
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  ret void, !dbg !2377
}

; Function Attrs: nounwind uwtable
define void @archive_entry_copy_hardlink_w(%struct.archive_entry* %entry1, i32* %target) #0 !dbg !347 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %target.addr = alloca i32*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2378, metadata !486), !dbg !2379
  store i32* %target, i32** %target.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %target.addr, metadata !2380, metadata !486), !dbg !2381
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2382
  %ae_hardlink = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 9, !dbg !2383
  %1 = load i32*, i32** %target.addr, align 8, !dbg !2384
  %call = call i32 @archive_mstring_copy_wcs(%struct.archive_mstring* %ae_hardlink, i32* %1), !dbg !2385
  %2 = load i32*, i32** %target.addr, align 8, !dbg !2386
  %cmp = icmp ne i32* %2, null, !dbg !2388
  br i1 %cmp, label %if.then, label %if.else, !dbg !2389

if.then:                                          ; preds = %entry
  %3 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2390
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %3, i32 0, i32 4, !dbg !2391
  %4 = load i32, i32* %ae_set, align 8, !dbg !2392
  %or = or i32 %4, 1, !dbg !2392
  store i32 %or, i32* %ae_set, align 8, !dbg !2392
  br label %if.end, !dbg !2390

if.else:                                          ; preds = %entry
  %5 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2393
  %ae_set2 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %5, i32 0, i32 4, !dbg !2394
  %6 = load i32, i32* %ae_set2, align 8, !dbg !2395
  %and = and i32 %6, -2, !dbg !2395
  store i32 %and, i32* %ae_set2, align 8, !dbg !2395
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  ret void, !dbg !2396
}

; Function Attrs: nounwind uwtable
define i32 @archive_entry_update_hardlink_utf8(%struct.archive_entry* %entry1, i8* %target) #0 !dbg !348 {
entry:
  %retval = alloca i32, align 4
  %entry.addr = alloca %struct.archive_entry*, align 8
  %target.addr = alloca i8*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2397, metadata !486), !dbg !2398
  store i8* %target, i8** %target.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %target.addr, metadata !2399, metadata !486), !dbg !2400
  %0 = load i8*, i8** %target.addr, align 8, !dbg !2401
  %cmp = icmp ne i8* %0, null, !dbg !2403
  br i1 %cmp, label %if.then, label %if.else, !dbg !2404

if.then:                                          ; preds = %entry
  %1 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2405
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %1, i32 0, i32 4, !dbg !2406
  %2 = load i32, i32* %ae_set, align 8, !dbg !2407
  %or = or i32 %2, 1, !dbg !2407
  store i32 %or, i32* %ae_set, align 8, !dbg !2407
  br label %if.end, !dbg !2405

if.else:                                          ; preds = %entry
  %3 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2408
  %ae_set2 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %3, i32 0, i32 4, !dbg !2409
  %4 = load i32, i32* %ae_set2, align 8, !dbg !2410
  %and = and i32 %4, -2, !dbg !2410
  store i32 %and, i32* %ae_set2, align 8, !dbg !2410
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %5 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2411
  %archive = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %5, i32 0, i32 0, !dbg !2413
  %6 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !2413
  %7 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2414
  %ae_hardlink = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %7, i32 0, i32 9, !dbg !2415
  %8 = load i8*, i8** %target.addr, align 8, !dbg !2416
  %call = call i32 @archive_mstring_update_utf8(%struct.archive* %6, %struct.archive_mstring* %ae_hardlink, i8* %8), !dbg !2417
  %cmp3 = icmp eq i32 %call, 0, !dbg !2418
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !2419

if.then4:                                         ; preds = %if.end
  store i32 1, i32* %retval, align 4, !dbg !2420
  br label %return, !dbg !2420

if.end5:                                          ; preds = %if.end
  %call6 = call i32* @__errno_location() #1, !dbg !2421
  %9 = load i32, i32* %call6, align 4, !dbg !2421
  %cmp7 = icmp eq i32 %9, 12, !dbg !2423
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !2424

if.then8:                                         ; preds = %if.end5
  call void @__archive_errx(i32 1, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0)) #11, !dbg !2425
  unreachable, !dbg !2425

if.end9:                                          ; preds = %if.end5
  store i32 0, i32* %retval, align 4, !dbg !2426
  br label %return, !dbg !2426

return:                                           ; preds = %if.end9, %if.then4
  %10 = load i32, i32* %retval, align 4, !dbg !2427
  ret i32 %10, !dbg !2427
}

; Function Attrs: nounwind uwtable
define i32 @_archive_entry_copy_hardlink_l(%struct.archive_entry* %entry1, i8* %target, i64 %len, %struct.archive_string_conv* %sc) #0 !dbg !349 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %target.addr = alloca i8*, align 8
  %len.addr = alloca i64, align 8
  %sc.addr = alloca %struct.archive_string_conv*, align 8
  %r = alloca i32, align 4
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2428, metadata !486), !dbg !2429
  store i8* %target, i8** %target.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %target.addr, metadata !2430, metadata !486), !dbg !2431
  store i64 %len, i64* %len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %len.addr, metadata !2432, metadata !486), !dbg !2433
  store %struct.archive_string_conv* %sc, %struct.archive_string_conv** %sc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string_conv** %sc.addr, metadata !2434, metadata !486), !dbg !2435
  call void @llvm.dbg.declare(metadata i32* %r, metadata !2436, metadata !486), !dbg !2437
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2438
  %ae_hardlink = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 9, !dbg !2439
  %1 = load i8*, i8** %target.addr, align 8, !dbg !2440
  %2 = load i64, i64* %len.addr, align 8, !dbg !2441
  %3 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sc.addr, align 8, !dbg !2442
  %call = call i32 @archive_mstring_copy_mbs_len_l(%struct.archive_mstring* %ae_hardlink, i8* %1, i64 %2, %struct.archive_string_conv* %3), !dbg !2443
  store i32 %call, i32* %r, align 4, !dbg !2444
  %4 = load i8*, i8** %target.addr, align 8, !dbg !2445
  %cmp = icmp ne i8* %4, null, !dbg !2447
  br i1 %cmp, label %land.lhs.true, label %if.else, !dbg !2448

land.lhs.true:                                    ; preds = %entry
  %5 = load i32, i32* %r, align 4, !dbg !2449
  %cmp2 = icmp eq i32 %5, 0, !dbg !2451
  br i1 %cmp2, label %if.then, label %if.else, !dbg !2452

if.then:                                          ; preds = %land.lhs.true
  %6 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2453
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %6, i32 0, i32 4, !dbg !2454
  %7 = load i32, i32* %ae_set, align 8, !dbg !2455
  %or = or i32 %7, 1, !dbg !2455
  store i32 %or, i32* %ae_set, align 8, !dbg !2455
  br label %if.end, !dbg !2453

if.else:                                          ; preds = %land.lhs.true, %entry
  %8 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2456
  %ae_set3 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %8, i32 0, i32 4, !dbg !2457
  %9 = load i32, i32* %ae_set3, align 8, !dbg !2458
  %and = and i32 %9, -2, !dbg !2458
  store i32 %and, i32* %ae_set3, align 8, !dbg !2458
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %10 = load i32, i32* %r, align 4, !dbg !2459
  ret i32 %10, !dbg !2460
}

; Function Attrs: nounwind uwtable
define void @archive_entry_set_atime(%struct.archive_entry* %entry1, i64 %t, i64 %ns) #0 !dbg !350 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %t.addr = alloca i64, align 8
  %ns.addr = alloca i64, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2461, metadata !486), !dbg !2462
  store i64 %t, i64* %t.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %t.addr, metadata !2463, metadata !486), !dbg !2464
  store i64 %ns, i64* %ns.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %ns.addr, metadata !2465, metadata !486), !dbg !2466
  br label %do.body, !dbg !2467

do.body:                                          ; preds = %entry
  %0 = load i64, i64* %ns.addr, align 8, !dbg !2468
  %div = sdiv i64 %0, 1000000000, !dbg !2468
  %1 = load i64, i64* %t.addr, align 8, !dbg !2468
  %add = add nsw i64 %1, %div, !dbg !2468
  store i64 %add, i64* %t.addr, align 8, !dbg !2468
  %2 = load i64, i64* %ns.addr, align 8, !dbg !2468
  %rem = srem i64 %2, 1000000000, !dbg !2468
  store i64 %rem, i64* %ns.addr, align 8, !dbg !2468
  %3 = load i64, i64* %ns.addr, align 8, !dbg !2468
  %cmp = icmp slt i64 %3, 0, !dbg !2468
  br i1 %cmp, label %if.then, label %if.end, !dbg !2468

if.then:                                          ; preds = %do.body
  %4 = load i64, i64* %t.addr, align 8, !dbg !2471
  %dec = add nsw i64 %4, -1, !dbg !2471
  store i64 %dec, i64* %t.addr, align 8, !dbg !2471
  %5 = load i64, i64* %ns.addr, align 8, !dbg !2471
  %add2 = add nsw i64 %5, 1000000000, !dbg !2471
  store i64 %add2, i64* %ns.addr, align 8, !dbg !2471
  br label %if.end, !dbg !2471

if.end:                                           ; preds = %if.then, %do.body
  br label %do.end, !dbg !2475

do.end:                                           ; preds = %if.end
  %6 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2477
  %stat_valid = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %6, i32 0, i32 2, !dbg !2478
  store i32 0, i32* %stat_valid, align 8, !dbg !2479
  %7 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2480
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %7, i32 0, i32 4, !dbg !2481
  %8 = load i32, i32* %ae_set, align 8, !dbg !2482
  %or = or i32 %8, 4, !dbg !2482
  store i32 %or, i32* %ae_set, align 8, !dbg !2482
  %9 = load i64, i64* %t.addr, align 8, !dbg !2483
  %10 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2484
  %ae_stat = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %10, i32 0, i32 3, !dbg !2485
  %aest_atime = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat, i32 0, i32 0, !dbg !2486
  store i64 %9, i64* %aest_atime, align 8, !dbg !2487
  %11 = load i64, i64* %ns.addr, align 8, !dbg !2488
  %conv = trunc i64 %11 to i32, !dbg !2488
  %12 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2489
  %ae_stat3 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %12, i32 0, i32 3, !dbg !2490
  %aest_atime_nsec = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat3, i32 0, i32 1, !dbg !2491
  store i32 %conv, i32* %aest_atime_nsec, align 8, !dbg !2492
  ret void, !dbg !2493
}

; Function Attrs: nounwind uwtable
define void @archive_entry_unset_atime(%struct.archive_entry* %entry1) #0 !dbg !353 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2494, metadata !486), !dbg !2495
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2496
  call void @archive_entry_set_atime(%struct.archive_entry* %0, i64 0, i64 0), !dbg !2497
  %1 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2498
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %1, i32 0, i32 4, !dbg !2499
  %2 = load i32, i32* %ae_set, align 8, !dbg !2500
  %and = and i32 %2, -5, !dbg !2500
  store i32 %and, i32* %ae_set, align 8, !dbg !2500
  ret void, !dbg !2501
}

; Function Attrs: nounwind uwtable
define void @archive_entry_set_birthtime(%struct.archive_entry* %entry1, i64 %t, i64 %ns) #0 !dbg !354 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %t.addr = alloca i64, align 8
  %ns.addr = alloca i64, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2502, metadata !486), !dbg !2503
  store i64 %t, i64* %t.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %t.addr, metadata !2504, metadata !486), !dbg !2505
  store i64 %ns, i64* %ns.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %ns.addr, metadata !2506, metadata !486), !dbg !2507
  br label %do.body, !dbg !2508

do.body:                                          ; preds = %entry
  %0 = load i64, i64* %ns.addr, align 8, !dbg !2509
  %div = sdiv i64 %0, 1000000000, !dbg !2509
  %1 = load i64, i64* %t.addr, align 8, !dbg !2509
  %add = add nsw i64 %1, %div, !dbg !2509
  store i64 %add, i64* %t.addr, align 8, !dbg !2509
  %2 = load i64, i64* %ns.addr, align 8, !dbg !2509
  %rem = srem i64 %2, 1000000000, !dbg !2509
  store i64 %rem, i64* %ns.addr, align 8, !dbg !2509
  %3 = load i64, i64* %ns.addr, align 8, !dbg !2509
  %cmp = icmp slt i64 %3, 0, !dbg !2509
  br i1 %cmp, label %if.then, label %if.end, !dbg !2509

if.then:                                          ; preds = %do.body
  %4 = load i64, i64* %t.addr, align 8, !dbg !2512
  %dec = add nsw i64 %4, -1, !dbg !2512
  store i64 %dec, i64* %t.addr, align 8, !dbg !2512
  %5 = load i64, i64* %ns.addr, align 8, !dbg !2512
  %add2 = add nsw i64 %5, 1000000000, !dbg !2512
  store i64 %add2, i64* %ns.addr, align 8, !dbg !2512
  br label %if.end, !dbg !2512

if.end:                                           ; preds = %if.then, %do.body
  br label %do.end, !dbg !2516

do.end:                                           ; preds = %if.end
  %6 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2518
  %stat_valid = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %6, i32 0, i32 2, !dbg !2519
  store i32 0, i32* %stat_valid, align 8, !dbg !2520
  %7 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2521
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %7, i32 0, i32 4, !dbg !2522
  %8 = load i32, i32* %ae_set, align 8, !dbg !2523
  %or = or i32 %8, 32, !dbg !2523
  store i32 %or, i32* %ae_set, align 8, !dbg !2523
  %9 = load i64, i64* %t.addr, align 8, !dbg !2524
  %10 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2525
  %ae_stat = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %10, i32 0, i32 3, !dbg !2526
  %aest_birthtime = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat, i32 0, i32 6, !dbg !2527
  store i64 %9, i64* %aest_birthtime, align 8, !dbg !2528
  %11 = load i64, i64* %ns.addr, align 8, !dbg !2529
  %conv = trunc i64 %11 to i32, !dbg !2529
  %12 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2530
  %ae_stat3 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %12, i32 0, i32 3, !dbg !2531
  %aest_birthtime_nsec = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat3, i32 0, i32 7, !dbg !2532
  store i32 %conv, i32* %aest_birthtime_nsec, align 8, !dbg !2533
  ret void, !dbg !2534
}

; Function Attrs: nounwind uwtable
define void @archive_entry_unset_birthtime(%struct.archive_entry* %entry1) #0 !dbg !355 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2535, metadata !486), !dbg !2536
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2537
  call void @archive_entry_set_birthtime(%struct.archive_entry* %0, i64 0, i64 0), !dbg !2538
  %1 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2539
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %1, i32 0, i32 4, !dbg !2540
  %2 = load i32, i32* %ae_set, align 8, !dbg !2541
  %and = and i32 %2, -33, !dbg !2541
  store i32 %and, i32* %ae_set, align 8, !dbg !2541
  ret void, !dbg !2542
}

; Function Attrs: nounwind uwtable
define void @archive_entry_set_ctime(%struct.archive_entry* %entry1, i64 %t, i64 %ns) #0 !dbg !356 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %t.addr = alloca i64, align 8
  %ns.addr = alloca i64, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2543, metadata !486), !dbg !2544
  store i64 %t, i64* %t.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %t.addr, metadata !2545, metadata !486), !dbg !2546
  store i64 %ns, i64* %ns.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %ns.addr, metadata !2547, metadata !486), !dbg !2548
  br label %do.body, !dbg !2549

do.body:                                          ; preds = %entry
  %0 = load i64, i64* %ns.addr, align 8, !dbg !2550
  %div = sdiv i64 %0, 1000000000, !dbg !2550
  %1 = load i64, i64* %t.addr, align 8, !dbg !2550
  %add = add nsw i64 %1, %div, !dbg !2550
  store i64 %add, i64* %t.addr, align 8, !dbg !2550
  %2 = load i64, i64* %ns.addr, align 8, !dbg !2550
  %rem = srem i64 %2, 1000000000, !dbg !2550
  store i64 %rem, i64* %ns.addr, align 8, !dbg !2550
  %3 = load i64, i64* %ns.addr, align 8, !dbg !2550
  %cmp = icmp slt i64 %3, 0, !dbg !2550
  br i1 %cmp, label %if.then, label %if.end, !dbg !2550

if.then:                                          ; preds = %do.body
  %4 = load i64, i64* %t.addr, align 8, !dbg !2553
  %dec = add nsw i64 %4, -1, !dbg !2553
  store i64 %dec, i64* %t.addr, align 8, !dbg !2553
  %5 = load i64, i64* %ns.addr, align 8, !dbg !2553
  %add2 = add nsw i64 %5, 1000000000, !dbg !2553
  store i64 %add2, i64* %ns.addr, align 8, !dbg !2553
  br label %if.end, !dbg !2553

if.end:                                           ; preds = %if.then, %do.body
  br label %do.end, !dbg !2557

do.end:                                           ; preds = %if.end
  %6 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2559
  %stat_valid = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %6, i32 0, i32 2, !dbg !2560
  store i32 0, i32* %stat_valid, align 8, !dbg !2561
  %7 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2562
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %7, i32 0, i32 4, !dbg !2563
  %8 = load i32, i32* %ae_set, align 8, !dbg !2564
  %or = or i32 %8, 8, !dbg !2564
  store i32 %or, i32* %ae_set, align 8, !dbg !2564
  %9 = load i64, i64* %t.addr, align 8, !dbg !2565
  %10 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2566
  %ae_stat = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %10, i32 0, i32 3, !dbg !2567
  %aest_ctime = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat, i32 0, i32 2, !dbg !2568
  store i64 %9, i64* %aest_ctime, align 8, !dbg !2569
  %11 = load i64, i64* %ns.addr, align 8, !dbg !2570
  %conv = trunc i64 %11 to i32, !dbg !2570
  %12 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2571
  %ae_stat3 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %12, i32 0, i32 3, !dbg !2572
  %aest_ctime_nsec = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat3, i32 0, i32 3, !dbg !2573
  store i32 %conv, i32* %aest_ctime_nsec, align 8, !dbg !2574
  ret void, !dbg !2575
}

; Function Attrs: nounwind uwtable
define void @archive_entry_unset_ctime(%struct.archive_entry* %entry1) #0 !dbg !357 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2576, metadata !486), !dbg !2577
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2578
  call void @archive_entry_set_ctime(%struct.archive_entry* %0, i64 0, i64 0), !dbg !2579
  %1 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2580
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %1, i32 0, i32 4, !dbg !2581
  %2 = load i32, i32* %ae_set, align 8, !dbg !2582
  %and = and i32 %2, -9, !dbg !2582
  store i32 %and, i32* %ae_set, align 8, !dbg !2582
  ret void, !dbg !2583
}

; Function Attrs: nounwind uwtable
define void @archive_entry_set_dev(%struct.archive_entry* %entry1, i64 %d) #0 !dbg !358 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %d.addr = alloca i64, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2584, metadata !486), !dbg !2585
  store i64 %d, i64* %d.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %d.addr, metadata !2586, metadata !486), !dbg !2587
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2588
  %stat_valid = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 2, !dbg !2589
  store i32 0, i32* %stat_valid, align 8, !dbg !2590
  %1 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2591
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %1, i32 0, i32 4, !dbg !2592
  %2 = load i32, i32* %ae_set, align 8, !dbg !2593
  %or = or i32 %2, 256, !dbg !2593
  store i32 %or, i32* %ae_set, align 8, !dbg !2593
  %3 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2594
  %ae_stat = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %3, i32 0, i32 3, !dbg !2595
  %aest_dev_is_broken_down = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat, i32 0, i32 13, !dbg !2596
  store i32 0, i32* %aest_dev_is_broken_down, align 8, !dbg !2597
  %4 = load i64, i64* %d.addr, align 8, !dbg !2598
  %5 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2599
  %ae_stat2 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %5, i32 0, i32 3, !dbg !2600
  %aest_dev = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat2, i32 0, i32 14, !dbg !2601
  store i64 %4, i64* %aest_dev, align 8, !dbg !2602
  ret void, !dbg !2603
}

; Function Attrs: nounwind uwtable
define void @archive_entry_set_devmajor(%struct.archive_entry* %entry1, i64 %m) #0 !dbg !361 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %m.addr = alloca i64, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2604, metadata !486), !dbg !2605
  store i64 %m, i64* %m.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %m.addr, metadata !2606, metadata !486), !dbg !2607
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2608
  %stat_valid = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 2, !dbg !2609
  store i32 0, i32* %stat_valid, align 8, !dbg !2610
  %1 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2611
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %1, i32 0, i32 4, !dbg !2612
  %2 = load i32, i32* %ae_set, align 8, !dbg !2613
  %or = or i32 %2, 256, !dbg !2613
  store i32 %or, i32* %ae_set, align 8, !dbg !2613
  %3 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2614
  %ae_stat = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %3, i32 0, i32 3, !dbg !2615
  %aest_dev_is_broken_down = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat, i32 0, i32 13, !dbg !2616
  store i32 1, i32* %aest_dev_is_broken_down, align 8, !dbg !2617
  %4 = load i64, i64* %m.addr, align 8, !dbg !2618
  %5 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2619
  %ae_stat2 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %5, i32 0, i32 3, !dbg !2620
  %aest_devmajor = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat2, i32 0, i32 15, !dbg !2621
  store i64 %4, i64* %aest_devmajor, align 8, !dbg !2622
  ret void, !dbg !2623
}

; Function Attrs: nounwind uwtable
define void @archive_entry_set_devminor(%struct.archive_entry* %entry1, i64 %m) #0 !dbg !362 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %m.addr = alloca i64, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2624, metadata !486), !dbg !2625
  store i64 %m, i64* %m.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %m.addr, metadata !2626, metadata !486), !dbg !2627
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2628
  %stat_valid = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 2, !dbg !2629
  store i32 0, i32* %stat_valid, align 8, !dbg !2630
  %1 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2631
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %1, i32 0, i32 4, !dbg !2632
  %2 = load i32, i32* %ae_set, align 8, !dbg !2633
  %or = or i32 %2, 256, !dbg !2633
  store i32 %or, i32* %ae_set, align 8, !dbg !2633
  %3 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2634
  %ae_stat = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %3, i32 0, i32 3, !dbg !2635
  %aest_dev_is_broken_down = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat, i32 0, i32 13, !dbg !2636
  store i32 1, i32* %aest_dev_is_broken_down, align 8, !dbg !2637
  %4 = load i64, i64* %m.addr, align 8, !dbg !2638
  %5 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2639
  %ae_stat2 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %5, i32 0, i32 3, !dbg !2640
  %aest_devminor = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat2, i32 0, i32 16, !dbg !2641
  store i64 %4, i64* %aest_devminor, align 8, !dbg !2642
  ret void, !dbg !2643
}

; Function Attrs: nounwind uwtable
define void @archive_entry_set_link(%struct.archive_entry* %entry1, i8* %target) #0 !dbg !363 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %target.addr = alloca i8*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2644, metadata !486), !dbg !2645
  store i8* %target, i8** %target.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %target.addr, metadata !2646, metadata !486), !dbg !2647
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2648
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 4, !dbg !2650
  %1 = load i32, i32* %ae_set, align 8, !dbg !2650
  %and = and i32 %1, 2, !dbg !2651
  %tobool = icmp ne i32 %and, 0, !dbg !2651
  br i1 %tobool, label %if.then, label %if.else, !dbg !2652

if.then:                                          ; preds = %entry
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2653
  %ae_symlink = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 11, !dbg !2654
  %3 = load i8*, i8** %target.addr, align 8, !dbg !2655
  %call = call i32 @archive_mstring_copy_mbs(%struct.archive_mstring* %ae_symlink, i8* %3), !dbg !2656
  br label %if.end, !dbg !2656

if.else:                                          ; preds = %entry
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2657
  %ae_hardlink = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %4, i32 0, i32 9, !dbg !2658
  %5 = load i8*, i8** %target.addr, align 8, !dbg !2659
  %call2 = call i32 @archive_mstring_copy_mbs(%struct.archive_mstring* %ae_hardlink, i8* %5), !dbg !2660
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  ret void, !dbg !2661
}

; Function Attrs: nounwind uwtable
define void @archive_entry_set_link_utf8(%struct.archive_entry* %entry1, i8* %target) #0 !dbg !364 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %target.addr = alloca i8*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2662, metadata !486), !dbg !2663
  store i8* %target, i8** %target.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %target.addr, metadata !2664, metadata !486), !dbg !2665
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2666
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 4, !dbg !2668
  %1 = load i32, i32* %ae_set, align 8, !dbg !2668
  %and = and i32 %1, 2, !dbg !2669
  %tobool = icmp ne i32 %and, 0, !dbg !2669
  br i1 %tobool, label %if.then, label %if.else, !dbg !2670

if.then:                                          ; preds = %entry
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2671
  %ae_symlink = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 11, !dbg !2672
  %3 = load i8*, i8** %target.addr, align 8, !dbg !2673
  %call = call i32 @archive_mstring_copy_utf8(%struct.archive_mstring* %ae_symlink, i8* %3), !dbg !2674
  br label %if.end, !dbg !2674

if.else:                                          ; preds = %entry
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2675
  %ae_hardlink = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %4, i32 0, i32 9, !dbg !2676
  %5 = load i8*, i8** %target.addr, align 8, !dbg !2677
  %call2 = call i32 @archive_mstring_copy_utf8(%struct.archive_mstring* %ae_hardlink, i8* %5), !dbg !2678
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  ret void, !dbg !2679
}

; Function Attrs: nounwind uwtable
define void @archive_entry_copy_link(%struct.archive_entry* %entry1, i8* %target) #0 !dbg !365 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %target.addr = alloca i8*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2680, metadata !486), !dbg !2681
  store i8* %target, i8** %target.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %target.addr, metadata !2682, metadata !486), !dbg !2683
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2684
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 4, !dbg !2686
  %1 = load i32, i32* %ae_set, align 8, !dbg !2686
  %and = and i32 %1, 2, !dbg !2687
  %tobool = icmp ne i32 %and, 0, !dbg !2687
  br i1 %tobool, label %if.then, label %if.else, !dbg !2688

if.then:                                          ; preds = %entry
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2689
  %ae_symlink = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 11, !dbg !2690
  %3 = load i8*, i8** %target.addr, align 8, !dbg !2691
  %call = call i32 @archive_mstring_copy_mbs(%struct.archive_mstring* %ae_symlink, i8* %3), !dbg !2692
  br label %if.end, !dbg !2692

if.else:                                          ; preds = %entry
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2693
  %ae_hardlink = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %4, i32 0, i32 9, !dbg !2694
  %5 = load i8*, i8** %target.addr, align 8, !dbg !2695
  %call2 = call i32 @archive_mstring_copy_mbs(%struct.archive_mstring* %ae_hardlink, i8* %5), !dbg !2696
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  ret void, !dbg !2697
}

; Function Attrs: nounwind uwtable
define void @archive_entry_copy_link_w(%struct.archive_entry* %entry1, i32* %target) #0 !dbg !366 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %target.addr = alloca i32*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2698, metadata !486), !dbg !2699
  store i32* %target, i32** %target.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %target.addr, metadata !2700, metadata !486), !dbg !2701
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2702
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 4, !dbg !2704
  %1 = load i32, i32* %ae_set, align 8, !dbg !2704
  %and = and i32 %1, 2, !dbg !2705
  %tobool = icmp ne i32 %and, 0, !dbg !2705
  br i1 %tobool, label %if.then, label %if.else, !dbg !2706

if.then:                                          ; preds = %entry
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2707
  %ae_symlink = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 11, !dbg !2708
  %3 = load i32*, i32** %target.addr, align 8, !dbg !2709
  %call = call i32 @archive_mstring_copy_wcs(%struct.archive_mstring* %ae_symlink, i32* %3), !dbg !2710
  br label %if.end, !dbg !2710

if.else:                                          ; preds = %entry
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2711
  %ae_hardlink = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %4, i32 0, i32 9, !dbg !2712
  %5 = load i32*, i32** %target.addr, align 8, !dbg !2713
  %call2 = call i32 @archive_mstring_copy_wcs(%struct.archive_mstring* %ae_hardlink, i32* %5), !dbg !2714
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  ret void, !dbg !2715
}

; Function Attrs: nounwind uwtable
define i32 @archive_entry_update_link_utf8(%struct.archive_entry* %entry1, i8* %target) #0 !dbg !367 {
entry:
  %retval = alloca i32, align 4
  %entry.addr = alloca %struct.archive_entry*, align 8
  %target.addr = alloca i8*, align 8
  %r = alloca i32, align 4
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2716, metadata !486), !dbg !2717
  store i8* %target, i8** %target.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %target.addr, metadata !2718, metadata !486), !dbg !2719
  call void @llvm.dbg.declare(metadata i32* %r, metadata !2720, metadata !486), !dbg !2721
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2722
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 4, !dbg !2724
  %1 = load i32, i32* %ae_set, align 8, !dbg !2724
  %and = and i32 %1, 2, !dbg !2725
  %tobool = icmp ne i32 %and, 0, !dbg !2725
  br i1 %tobool, label %if.then, label %if.else, !dbg !2726

if.then:                                          ; preds = %entry
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2727
  %archive = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 0, !dbg !2728
  %3 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !2728
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2729
  %ae_symlink = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %4, i32 0, i32 11, !dbg !2730
  %5 = load i8*, i8** %target.addr, align 8, !dbg !2731
  %call = call i32 @archive_mstring_update_utf8(%struct.archive* %3, %struct.archive_mstring* %ae_symlink, i8* %5), !dbg !2732
  store i32 %call, i32* %r, align 4, !dbg !2733
  br label %if.end, !dbg !2734

if.else:                                          ; preds = %entry
  %6 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2735
  %archive2 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %6, i32 0, i32 0, !dbg !2736
  %7 = load %struct.archive*, %struct.archive** %archive2, align 8, !dbg !2736
  %8 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2737
  %ae_hardlink = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %8, i32 0, i32 9, !dbg !2738
  %9 = load i8*, i8** %target.addr, align 8, !dbg !2739
  %call3 = call i32 @archive_mstring_update_utf8(%struct.archive* %7, %struct.archive_mstring* %ae_hardlink, i8* %9), !dbg !2740
  store i32 %call3, i32* %r, align 4, !dbg !2741
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %10 = load i32, i32* %r, align 4, !dbg !2742
  %cmp = icmp eq i32 %10, 0, !dbg !2744
  br i1 %cmp, label %if.then4, label %if.end5, !dbg !2745

if.then4:                                         ; preds = %if.end
  store i32 1, i32* %retval, align 4, !dbg !2746
  br label %return, !dbg !2746

if.end5:                                          ; preds = %if.end
  %call6 = call i32* @__errno_location() #1, !dbg !2747
  %11 = load i32, i32* %call6, align 4, !dbg !2747
  %cmp7 = icmp eq i32 %11, 12, !dbg !2749
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !2750

if.then8:                                         ; preds = %if.end5
  call void @__archive_errx(i32 1, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0)) #11, !dbg !2751
  unreachable, !dbg !2751

if.end9:                                          ; preds = %if.end5
  store i32 0, i32* %retval, align 4, !dbg !2752
  br label %return, !dbg !2752

return:                                           ; preds = %if.end9, %if.then4
  %12 = load i32, i32* %retval, align 4, !dbg !2753
  ret i32 %12, !dbg !2753
}

; Function Attrs: nounwind uwtable
define i32 @_archive_entry_copy_link_l(%struct.archive_entry* %entry1, i8* %target, i64 %len, %struct.archive_string_conv* %sc) #0 !dbg !368 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %target.addr = alloca i8*, align 8
  %len.addr = alloca i64, align 8
  %sc.addr = alloca %struct.archive_string_conv*, align 8
  %r = alloca i32, align 4
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2754, metadata !486), !dbg !2755
  store i8* %target, i8** %target.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %target.addr, metadata !2756, metadata !486), !dbg !2757
  store i64 %len, i64* %len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %len.addr, metadata !2758, metadata !486), !dbg !2759
  store %struct.archive_string_conv* %sc, %struct.archive_string_conv** %sc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string_conv** %sc.addr, metadata !2760, metadata !486), !dbg !2761
  call void @llvm.dbg.declare(metadata i32* %r, metadata !2762, metadata !486), !dbg !2763
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2764
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 4, !dbg !2766
  %1 = load i32, i32* %ae_set, align 8, !dbg !2766
  %and = and i32 %1, 2, !dbg !2767
  %tobool = icmp ne i32 %and, 0, !dbg !2767
  br i1 %tobool, label %if.then, label %if.else, !dbg !2768

if.then:                                          ; preds = %entry
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2769
  %ae_symlink = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 11, !dbg !2770
  %3 = load i8*, i8** %target.addr, align 8, !dbg !2771
  %4 = load i64, i64* %len.addr, align 8, !dbg !2772
  %5 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sc.addr, align 8, !dbg !2773
  %call = call i32 @archive_mstring_copy_mbs_len_l(%struct.archive_mstring* %ae_symlink, i8* %3, i64 %4, %struct.archive_string_conv* %5), !dbg !2774
  store i32 %call, i32* %r, align 4, !dbg !2775
  br label %if.end, !dbg !2776

if.else:                                          ; preds = %entry
  %6 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2777
  %ae_hardlink = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %6, i32 0, i32 9, !dbg !2778
  %7 = load i8*, i8** %target.addr, align 8, !dbg !2779
  %8 = load i64, i64* %len.addr, align 8, !dbg !2780
  %9 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sc.addr, align 8, !dbg !2781
  %call2 = call i32 @archive_mstring_copy_mbs_len_l(%struct.archive_mstring* %ae_hardlink, i8* %7, i64 %8, %struct.archive_string_conv* %9), !dbg !2782
  store i32 %call2, i32* %r, align 4, !dbg !2783
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %10 = load i32, i32* %r, align 4, !dbg !2784
  ret i32 %10, !dbg !2785
}

; Function Attrs: nounwind uwtable
define void @archive_entry_set_mode(%struct.archive_entry* %entry1, i32 %m) #0 !dbg !369 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %m.addr = alloca i32, align 4
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2786, metadata !486), !dbg !2787
  store i32 %m, i32* %m.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %m.addr, metadata !2788, metadata !486), !dbg !2789
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2790
  %stat_valid = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 2, !dbg !2791
  store i32 0, i32* %stat_valid, align 8, !dbg !2792
  %1 = load i32, i32* %m.addr, align 4, !dbg !2793
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2794
  %acl = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 17, !dbg !2795
  %mode = getelementptr inbounds %struct.archive_acl, %struct.archive_acl* %acl, i32 0, i32 0, !dbg !2796
  store i32 %1, i32* %mode, align 8, !dbg !2797
  ret void, !dbg !2798
}

; Function Attrs: nounwind uwtable
define void @archive_entry_set_mtime(%struct.archive_entry* %entry1, i64 %t, i64 %ns) #0 !dbg !372 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %t.addr = alloca i64, align 8
  %ns.addr = alloca i64, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2799, metadata !486), !dbg !2800
  store i64 %t, i64* %t.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %t.addr, metadata !2801, metadata !486), !dbg !2802
  store i64 %ns, i64* %ns.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %ns.addr, metadata !2803, metadata !486), !dbg !2804
  br label %do.body, !dbg !2805

do.body:                                          ; preds = %entry
  %0 = load i64, i64* %ns.addr, align 8, !dbg !2806
  %div = sdiv i64 %0, 1000000000, !dbg !2806
  %1 = load i64, i64* %t.addr, align 8, !dbg !2806
  %add = add nsw i64 %1, %div, !dbg !2806
  store i64 %add, i64* %t.addr, align 8, !dbg !2806
  %2 = load i64, i64* %ns.addr, align 8, !dbg !2806
  %rem = srem i64 %2, 1000000000, !dbg !2806
  store i64 %rem, i64* %ns.addr, align 8, !dbg !2806
  %3 = load i64, i64* %ns.addr, align 8, !dbg !2806
  %cmp = icmp slt i64 %3, 0, !dbg !2806
  br i1 %cmp, label %if.then, label %if.end, !dbg !2806

if.then:                                          ; preds = %do.body
  %4 = load i64, i64* %t.addr, align 8, !dbg !2809
  %dec = add nsw i64 %4, -1, !dbg !2809
  store i64 %dec, i64* %t.addr, align 8, !dbg !2809
  %5 = load i64, i64* %ns.addr, align 8, !dbg !2809
  %add2 = add nsw i64 %5, 1000000000, !dbg !2809
  store i64 %add2, i64* %ns.addr, align 8, !dbg !2809
  br label %if.end, !dbg !2809

if.end:                                           ; preds = %if.then, %do.body
  br label %do.end, !dbg !2813

do.end:                                           ; preds = %if.end
  %6 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2815
  %stat_valid = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %6, i32 0, i32 2, !dbg !2816
  store i32 0, i32* %stat_valid, align 8, !dbg !2817
  %7 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2818
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %7, i32 0, i32 4, !dbg !2819
  %8 = load i32, i32* %ae_set, align 8, !dbg !2820
  %or = or i32 %8, 16, !dbg !2820
  store i32 %or, i32* %ae_set, align 8, !dbg !2820
  %9 = load i64, i64* %t.addr, align 8, !dbg !2821
  %10 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2822
  %ae_stat = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %10, i32 0, i32 3, !dbg !2823
  %aest_mtime = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat, i32 0, i32 4, !dbg !2824
  store i64 %9, i64* %aest_mtime, align 8, !dbg !2825
  %11 = load i64, i64* %ns.addr, align 8, !dbg !2826
  %conv = trunc i64 %11 to i32, !dbg !2826
  %12 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2827
  %ae_stat3 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %12, i32 0, i32 3, !dbg !2828
  %aest_mtime_nsec = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat3, i32 0, i32 5, !dbg !2829
  store i32 %conv, i32* %aest_mtime_nsec, align 8, !dbg !2830
  ret void, !dbg !2831
}

; Function Attrs: nounwind uwtable
define void @archive_entry_unset_mtime(%struct.archive_entry* %entry1) #0 !dbg !373 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2832, metadata !486), !dbg !2833
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2834
  call void @archive_entry_set_mtime(%struct.archive_entry* %0, i64 0, i64 0), !dbg !2835
  %1 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2836
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %1, i32 0, i32 4, !dbg !2837
  %2 = load i32, i32* %ae_set, align 8, !dbg !2838
  %and = and i32 %2, -17, !dbg !2838
  store i32 %and, i32* %ae_set, align 8, !dbg !2838
  ret void, !dbg !2839
}

; Function Attrs: nounwind uwtable
define void @archive_entry_set_nlink(%struct.archive_entry* %entry1, i32 %nlink) #0 !dbg !374 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %nlink.addr = alloca i32, align 4
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2840, metadata !486), !dbg !2841
  store i32 %nlink, i32* %nlink.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %nlink.addr, metadata !2842, metadata !486), !dbg !2843
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2844
  %stat_valid = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 2, !dbg !2845
  store i32 0, i32* %stat_valid, align 8, !dbg !2846
  %1 = load i32, i32* %nlink.addr, align 4, !dbg !2847
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2848
  %ae_stat = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 3, !dbg !2849
  %aest_nlink = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat, i32 0, i32 10, !dbg !2850
  store i32 %1, i32* %aest_nlink, align 8, !dbg !2851
  ret void, !dbg !2852
}

; Function Attrs: nounwind uwtable
define void @archive_entry_set_pathname(%struct.archive_entry* %entry1, i8* %name) #0 !dbg !375 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %name.addr = alloca i8*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2853, metadata !486), !dbg !2854
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !2855, metadata !486), !dbg !2856
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2857
  %ae_pathname = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 10, !dbg !2858
  %1 = load i8*, i8** %name.addr, align 8, !dbg !2859
  %call = call i32 @archive_mstring_copy_mbs(%struct.archive_mstring* %ae_pathname, i8* %1), !dbg !2860
  ret void, !dbg !2861
}

; Function Attrs: nounwind uwtable
define void @archive_entry_set_pathname_utf8(%struct.archive_entry* %entry1, i8* %name) #0 !dbg !376 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %name.addr = alloca i8*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2862, metadata !486), !dbg !2863
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !2864, metadata !486), !dbg !2865
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2866
  %ae_pathname = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 10, !dbg !2867
  %1 = load i8*, i8** %name.addr, align 8, !dbg !2868
  %call = call i32 @archive_mstring_copy_utf8(%struct.archive_mstring* %ae_pathname, i8* %1), !dbg !2869
  ret void, !dbg !2870
}

; Function Attrs: nounwind uwtable
define void @archive_entry_copy_pathname(%struct.archive_entry* %entry1, i8* %name) #0 !dbg !377 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %name.addr = alloca i8*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2871, metadata !486), !dbg !2872
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !2873, metadata !486), !dbg !2874
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2875
  %ae_pathname = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 10, !dbg !2876
  %1 = load i8*, i8** %name.addr, align 8, !dbg !2877
  %call = call i32 @archive_mstring_copy_mbs(%struct.archive_mstring* %ae_pathname, i8* %1), !dbg !2878
  ret void, !dbg !2879
}

; Function Attrs: nounwind uwtable
define void @archive_entry_copy_pathname_w(%struct.archive_entry* %entry1, i32* %name) #0 !dbg !378 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %name.addr = alloca i32*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2880, metadata !486), !dbg !2881
  store i32* %name, i32** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %name.addr, metadata !2882, metadata !486), !dbg !2883
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2884
  %ae_pathname = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 10, !dbg !2885
  %1 = load i32*, i32** %name.addr, align 8, !dbg !2886
  %call = call i32 @archive_mstring_copy_wcs(%struct.archive_mstring* %ae_pathname, i32* %1), !dbg !2887
  ret void, !dbg !2888
}

; Function Attrs: nounwind uwtable
define i32 @archive_entry_update_pathname_utf8(%struct.archive_entry* %entry1, i8* %name) #0 !dbg !379 {
entry:
  %retval = alloca i32, align 4
  %entry.addr = alloca %struct.archive_entry*, align 8
  %name.addr = alloca i8*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2889, metadata !486), !dbg !2890
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !2891, metadata !486), !dbg !2892
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2893
  %archive = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 0, !dbg !2895
  %1 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !2895
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2896
  %ae_pathname = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 10, !dbg !2897
  %3 = load i8*, i8** %name.addr, align 8, !dbg !2898
  %call = call i32 @archive_mstring_update_utf8(%struct.archive* %1, %struct.archive_mstring* %ae_pathname, i8* %3), !dbg !2899
  %cmp = icmp eq i32 %call, 0, !dbg !2900
  br i1 %cmp, label %if.then, label %if.end, !dbg !2901

if.then:                                          ; preds = %entry
  store i32 1, i32* %retval, align 4, !dbg !2902
  br label %return, !dbg !2902

if.end:                                           ; preds = %entry
  %call2 = call i32* @__errno_location() #1, !dbg !2903
  %4 = load i32, i32* %call2, align 4, !dbg !2903
  %cmp3 = icmp eq i32 %4, 12, !dbg !2905
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !2906

if.then4:                                         ; preds = %if.end
  call void @__archive_errx(i32 1, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0)) #11, !dbg !2907
  unreachable, !dbg !2907

if.end5:                                          ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !2908
  br label %return, !dbg !2908

return:                                           ; preds = %if.end5, %if.then
  %5 = load i32, i32* %retval, align 4, !dbg !2909
  ret i32 %5, !dbg !2909
}

; Function Attrs: nounwind uwtable
define i32 @_archive_entry_copy_pathname_l(%struct.archive_entry* %entry1, i8* %name, i64 %len, %struct.archive_string_conv* %sc) #0 !dbg !380 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %name.addr = alloca i8*, align 8
  %len.addr = alloca i64, align 8
  %sc.addr = alloca %struct.archive_string_conv*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2910, metadata !486), !dbg !2911
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !2912, metadata !486), !dbg !2913
  store i64 %len, i64* %len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %len.addr, metadata !2914, metadata !486), !dbg !2915
  store %struct.archive_string_conv* %sc, %struct.archive_string_conv** %sc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string_conv** %sc.addr, metadata !2916, metadata !486), !dbg !2917
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2918
  %ae_pathname = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 10, !dbg !2919
  %1 = load i8*, i8** %name.addr, align 8, !dbg !2920
  %2 = load i64, i64* %len.addr, align 8, !dbg !2921
  %3 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sc.addr, align 8, !dbg !2922
  %call = call i32 @archive_mstring_copy_mbs_len_l(%struct.archive_mstring* %ae_pathname, i8* %1, i64 %2, %struct.archive_string_conv* %3), !dbg !2923
  ret i32 %call, !dbg !2924
}

; Function Attrs: nounwind uwtable
define void @archive_entry_set_perm(%struct.archive_entry* %entry1, i32 %p) #0 !dbg !381 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %p.addr = alloca i32, align 4
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2925, metadata !486), !dbg !2926
  store i32 %p, i32* %p.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %p.addr, metadata !2927, metadata !486), !dbg !2928
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2929
  %stat_valid = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 2, !dbg !2930
  store i32 0, i32* %stat_valid, align 8, !dbg !2931
  %1 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2932
  %acl = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %1, i32 0, i32 17, !dbg !2933
  %mode = getelementptr inbounds %struct.archive_acl, %struct.archive_acl* %acl, i32 0, i32 0, !dbg !2934
  %2 = load i32, i32* %mode, align 8, !dbg !2935
  %and = and i32 %2, 61440, !dbg !2935
  store i32 %and, i32* %mode, align 8, !dbg !2935
  %3 = load i32, i32* %p.addr, align 4, !dbg !2936
  %and2 = and i32 -61441, %3, !dbg !2937
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2938
  %acl3 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %4, i32 0, i32 17, !dbg !2939
  %mode4 = getelementptr inbounds %struct.archive_acl, %struct.archive_acl* %acl3, i32 0, i32 0, !dbg !2940
  %5 = load i32, i32* %mode4, align 8, !dbg !2941
  %or = or i32 %5, %and2, !dbg !2941
  store i32 %or, i32* %mode4, align 8, !dbg !2941
  ret void, !dbg !2942
}

; Function Attrs: nounwind uwtable
define void @archive_entry_set_rdev(%struct.archive_entry* %entry1, i64 %m) #0 !dbg !382 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %m.addr = alloca i64, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2943, metadata !486), !dbg !2944
  store i64 %m, i64* %m.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %m.addr, metadata !2945, metadata !486), !dbg !2946
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2947
  %stat_valid = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 2, !dbg !2948
  store i32 0, i32* %stat_valid, align 8, !dbg !2949
  %1 = load i64, i64* %m.addr, align 8, !dbg !2950
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2951
  %ae_stat = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 3, !dbg !2952
  %aest_rdev = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat, i32 0, i32 18, !dbg !2953
  store i64 %1, i64* %aest_rdev, align 8, !dbg !2954
  %3 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2955
  %ae_stat2 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %3, i32 0, i32 3, !dbg !2956
  %aest_rdev_is_broken_down = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat2, i32 0, i32 17, !dbg !2957
  store i32 0, i32* %aest_rdev_is_broken_down, align 8, !dbg !2958
  ret void, !dbg !2959
}

; Function Attrs: nounwind uwtable
define void @archive_entry_set_rdevmajor(%struct.archive_entry* %entry1, i64 %m) #0 !dbg !383 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %m.addr = alloca i64, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2960, metadata !486), !dbg !2961
  store i64 %m, i64* %m.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %m.addr, metadata !2962, metadata !486), !dbg !2963
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2964
  %stat_valid = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 2, !dbg !2965
  store i32 0, i32* %stat_valid, align 8, !dbg !2966
  %1 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2967
  %ae_stat = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %1, i32 0, i32 3, !dbg !2968
  %aest_rdev_is_broken_down = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat, i32 0, i32 17, !dbg !2969
  store i32 1, i32* %aest_rdev_is_broken_down, align 8, !dbg !2970
  %2 = load i64, i64* %m.addr, align 8, !dbg !2971
  %3 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2972
  %ae_stat2 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %3, i32 0, i32 3, !dbg !2973
  %aest_rdevmajor = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat2, i32 0, i32 19, !dbg !2974
  store i64 %2, i64* %aest_rdevmajor, align 8, !dbg !2975
  ret void, !dbg !2976
}

; Function Attrs: nounwind uwtable
define void @archive_entry_set_rdevminor(%struct.archive_entry* %entry1, i64 %m) #0 !dbg !384 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %m.addr = alloca i64, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2977, metadata !486), !dbg !2978
  store i64 %m, i64* %m.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %m.addr, metadata !2979, metadata !486), !dbg !2980
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2981
  %stat_valid = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 2, !dbg !2982
  store i32 0, i32* %stat_valid, align 8, !dbg !2983
  %1 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2984
  %ae_stat = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %1, i32 0, i32 3, !dbg !2985
  %aest_rdev_is_broken_down = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat, i32 0, i32 17, !dbg !2986
  store i32 1, i32* %aest_rdev_is_broken_down, align 8, !dbg !2987
  %2 = load i64, i64* %m.addr, align 8, !dbg !2988
  %3 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2989
  %ae_stat2 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %3, i32 0, i32 3, !dbg !2990
  %aest_rdevminor = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat2, i32 0, i32 20, !dbg !2991
  store i64 %2, i64* %aest_rdevminor, align 8, !dbg !2992
  ret void, !dbg !2993
}

; Function Attrs: nounwind uwtable
define void @archive_entry_set_size(%struct.archive_entry* %entry1, i64 %s) #0 !dbg !385 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %s.addr = alloca i64, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2994, metadata !486), !dbg !2995
  store i64 %s, i64* %s.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %s.addr, metadata !2996, metadata !486), !dbg !2997
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2998
  %stat_valid = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 2, !dbg !2999
  store i32 0, i32* %stat_valid, align 8, !dbg !3000
  %1 = load i64, i64* %s.addr, align 8, !dbg !3001
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3002
  %ae_stat = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 3, !dbg !3003
  %aest_size = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat, i32 0, i32 11, !dbg !3004
  store i64 %1, i64* %aest_size, align 8, !dbg !3005
  %3 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3006
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %3, i32 0, i32 4, !dbg !3007
  %4 = load i32, i32* %ae_set, align 8, !dbg !3008
  %or = or i32 %4, 64, !dbg !3008
  store i32 %or, i32* %ae_set, align 8, !dbg !3008
  ret void, !dbg !3009
}

; Function Attrs: nounwind uwtable
define void @archive_entry_unset_size(%struct.archive_entry* %entry1) #0 !dbg !386 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3010, metadata !486), !dbg !3011
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3012
  call void @archive_entry_set_size(%struct.archive_entry* %0, i64 0), !dbg !3013
  %1 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3014
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %1, i32 0, i32 4, !dbg !3015
  %2 = load i32, i32* %ae_set, align 8, !dbg !3016
  %and = and i32 %2, -65, !dbg !3016
  store i32 %and, i32* %ae_set, align 8, !dbg !3016
  ret void, !dbg !3017
}

; Function Attrs: nounwind uwtable
define void @archive_entry_copy_sourcepath(%struct.archive_entry* %entry1, i8* %path) #0 !dbg !387 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %path.addr = alloca i8*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3018, metadata !486), !dbg !3019
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !3020, metadata !486), !dbg !3021
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3022
  %ae_sourcepath = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 13, !dbg !3023
  %1 = load i8*, i8** %path.addr, align 8, !dbg !3024
  %call = call i32 @archive_mstring_copy_mbs(%struct.archive_mstring* %ae_sourcepath, i8* %1), !dbg !3025
  ret void, !dbg !3026
}

; Function Attrs: nounwind uwtable
define void @archive_entry_copy_sourcepath_w(%struct.archive_entry* %entry1, i32* %path) #0 !dbg !388 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %path.addr = alloca i32*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3027, metadata !486), !dbg !3028
  store i32* %path, i32** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %path.addr, metadata !3029, metadata !486), !dbg !3030
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3031
  %ae_sourcepath = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 13, !dbg !3032
  %1 = load i32*, i32** %path.addr, align 8, !dbg !3033
  %call = call i32 @archive_mstring_copy_wcs(%struct.archive_mstring* %ae_sourcepath, i32* %1), !dbg !3034
  ret void, !dbg !3035
}

; Function Attrs: nounwind uwtable
define void @archive_entry_set_symlink(%struct.archive_entry* %entry1, i8* %linkname) #0 !dbg !389 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %linkname.addr = alloca i8*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3036, metadata !486), !dbg !3037
  store i8* %linkname, i8** %linkname.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %linkname.addr, metadata !3038, metadata !486), !dbg !3039
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3040
  %ae_symlink = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 11, !dbg !3041
  %1 = load i8*, i8** %linkname.addr, align 8, !dbg !3042
  %call = call i32 @archive_mstring_copy_mbs(%struct.archive_mstring* %ae_symlink, i8* %1), !dbg !3043
  %2 = load i8*, i8** %linkname.addr, align 8, !dbg !3044
  %cmp = icmp ne i8* %2, null, !dbg !3046
  br i1 %cmp, label %if.then, label %if.else, !dbg !3047

if.then:                                          ; preds = %entry
  %3 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3048
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %3, i32 0, i32 4, !dbg !3049
  %4 = load i32, i32* %ae_set, align 8, !dbg !3050
  %or = or i32 %4, 2, !dbg !3050
  store i32 %or, i32* %ae_set, align 8, !dbg !3050
  br label %if.end, !dbg !3048

if.else:                                          ; preds = %entry
  %5 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3051
  %ae_set2 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %5, i32 0, i32 4, !dbg !3052
  %6 = load i32, i32* %ae_set2, align 8, !dbg !3053
  %and = and i32 %6, -3, !dbg !3053
  store i32 %and, i32* %ae_set2, align 8, !dbg !3053
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  ret void, !dbg !3054
}

; Function Attrs: nounwind uwtable
define void @archive_entry_set_symlink_utf8(%struct.archive_entry* %entry1, i8* %linkname) #0 !dbg !390 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %linkname.addr = alloca i8*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3055, metadata !486), !dbg !3056
  store i8* %linkname, i8** %linkname.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %linkname.addr, metadata !3057, metadata !486), !dbg !3058
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3059
  %ae_symlink = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 11, !dbg !3060
  %1 = load i8*, i8** %linkname.addr, align 8, !dbg !3061
  %call = call i32 @archive_mstring_copy_utf8(%struct.archive_mstring* %ae_symlink, i8* %1), !dbg !3062
  %2 = load i8*, i8** %linkname.addr, align 8, !dbg !3063
  %cmp = icmp ne i8* %2, null, !dbg !3065
  br i1 %cmp, label %if.then, label %if.else, !dbg !3066

if.then:                                          ; preds = %entry
  %3 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3067
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %3, i32 0, i32 4, !dbg !3068
  %4 = load i32, i32* %ae_set, align 8, !dbg !3069
  %or = or i32 %4, 2, !dbg !3069
  store i32 %or, i32* %ae_set, align 8, !dbg !3069
  br label %if.end, !dbg !3067

if.else:                                          ; preds = %entry
  %5 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3070
  %ae_set2 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %5, i32 0, i32 4, !dbg !3071
  %6 = load i32, i32* %ae_set2, align 8, !dbg !3072
  %and = and i32 %6, -3, !dbg !3072
  store i32 %and, i32* %ae_set2, align 8, !dbg !3072
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  ret void, !dbg !3073
}

; Function Attrs: nounwind uwtable
define void @archive_entry_copy_symlink(%struct.archive_entry* %entry1, i8* %linkname) #0 !dbg !391 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %linkname.addr = alloca i8*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3074, metadata !486), !dbg !3075
  store i8* %linkname, i8** %linkname.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %linkname.addr, metadata !3076, metadata !486), !dbg !3077
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3078
  %ae_symlink = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 11, !dbg !3079
  %1 = load i8*, i8** %linkname.addr, align 8, !dbg !3080
  %call = call i32 @archive_mstring_copy_mbs(%struct.archive_mstring* %ae_symlink, i8* %1), !dbg !3081
  %2 = load i8*, i8** %linkname.addr, align 8, !dbg !3082
  %cmp = icmp ne i8* %2, null, !dbg !3084
  br i1 %cmp, label %if.then, label %if.else, !dbg !3085

if.then:                                          ; preds = %entry
  %3 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3086
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %3, i32 0, i32 4, !dbg !3087
  %4 = load i32, i32* %ae_set, align 8, !dbg !3088
  %or = or i32 %4, 2, !dbg !3088
  store i32 %or, i32* %ae_set, align 8, !dbg !3088
  br label %if.end, !dbg !3086

if.else:                                          ; preds = %entry
  %5 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3089
  %ae_set2 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %5, i32 0, i32 4, !dbg !3090
  %6 = load i32, i32* %ae_set2, align 8, !dbg !3091
  %and = and i32 %6, -3, !dbg !3091
  store i32 %and, i32* %ae_set2, align 8, !dbg !3091
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  ret void, !dbg !3092
}

; Function Attrs: nounwind uwtable
define void @archive_entry_copy_symlink_w(%struct.archive_entry* %entry1, i32* %linkname) #0 !dbg !392 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %linkname.addr = alloca i32*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3093, metadata !486), !dbg !3094
  store i32* %linkname, i32** %linkname.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %linkname.addr, metadata !3095, metadata !486), !dbg !3096
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3097
  %ae_symlink = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 11, !dbg !3098
  %1 = load i32*, i32** %linkname.addr, align 8, !dbg !3099
  %call = call i32 @archive_mstring_copy_wcs(%struct.archive_mstring* %ae_symlink, i32* %1), !dbg !3100
  %2 = load i32*, i32** %linkname.addr, align 8, !dbg !3101
  %cmp = icmp ne i32* %2, null, !dbg !3103
  br i1 %cmp, label %if.then, label %if.else, !dbg !3104

if.then:                                          ; preds = %entry
  %3 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3105
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %3, i32 0, i32 4, !dbg !3106
  %4 = load i32, i32* %ae_set, align 8, !dbg !3107
  %or = or i32 %4, 2, !dbg !3107
  store i32 %or, i32* %ae_set, align 8, !dbg !3107
  br label %if.end, !dbg !3105

if.else:                                          ; preds = %entry
  %5 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3108
  %ae_set2 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %5, i32 0, i32 4, !dbg !3109
  %6 = load i32, i32* %ae_set2, align 8, !dbg !3110
  %and = and i32 %6, -3, !dbg !3110
  store i32 %and, i32* %ae_set2, align 8, !dbg !3110
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  ret void, !dbg !3111
}

; Function Attrs: nounwind uwtable
define i32 @archive_entry_update_symlink_utf8(%struct.archive_entry* %entry1, i8* %linkname) #0 !dbg !393 {
entry:
  %retval = alloca i32, align 4
  %entry.addr = alloca %struct.archive_entry*, align 8
  %linkname.addr = alloca i8*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3112, metadata !486), !dbg !3113
  store i8* %linkname, i8** %linkname.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %linkname.addr, metadata !3114, metadata !486), !dbg !3115
  %0 = load i8*, i8** %linkname.addr, align 8, !dbg !3116
  %cmp = icmp ne i8* %0, null, !dbg !3118
  br i1 %cmp, label %if.then, label %if.else, !dbg !3119

if.then:                                          ; preds = %entry
  %1 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3120
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %1, i32 0, i32 4, !dbg !3121
  %2 = load i32, i32* %ae_set, align 8, !dbg !3122
  %or = or i32 %2, 2, !dbg !3122
  store i32 %or, i32* %ae_set, align 8, !dbg !3122
  br label %if.end, !dbg !3120

if.else:                                          ; preds = %entry
  %3 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3123
  %ae_set2 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %3, i32 0, i32 4, !dbg !3124
  %4 = load i32, i32* %ae_set2, align 8, !dbg !3125
  %and = and i32 %4, -3, !dbg !3125
  store i32 %and, i32* %ae_set2, align 8, !dbg !3125
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %5 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3126
  %archive = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %5, i32 0, i32 0, !dbg !3128
  %6 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !3128
  %7 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3129
  %ae_symlink = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %7, i32 0, i32 11, !dbg !3130
  %8 = load i8*, i8** %linkname.addr, align 8, !dbg !3131
  %call = call i32 @archive_mstring_update_utf8(%struct.archive* %6, %struct.archive_mstring* %ae_symlink, i8* %8), !dbg !3132
  %cmp3 = icmp eq i32 %call, 0, !dbg !3133
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !3134

if.then4:                                         ; preds = %if.end
  store i32 1, i32* %retval, align 4, !dbg !3135
  br label %return, !dbg !3135

if.end5:                                          ; preds = %if.end
  %call6 = call i32* @__errno_location() #1, !dbg !3136
  %9 = load i32, i32* %call6, align 4, !dbg !3136
  %cmp7 = icmp eq i32 %9, 12, !dbg !3138
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !3139

if.then8:                                         ; preds = %if.end5
  call void @__archive_errx(i32 1, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0)) #11, !dbg !3140
  unreachable, !dbg !3140

if.end9:                                          ; preds = %if.end5
  store i32 0, i32* %retval, align 4, !dbg !3141
  br label %return, !dbg !3141

return:                                           ; preds = %if.end9, %if.then4
  %10 = load i32, i32* %retval, align 4, !dbg !3142
  ret i32 %10, !dbg !3142
}

; Function Attrs: nounwind uwtable
define i32 @_archive_entry_copy_symlink_l(%struct.archive_entry* %entry1, i8* %linkname, i64 %len, %struct.archive_string_conv* %sc) #0 !dbg !394 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %linkname.addr = alloca i8*, align 8
  %len.addr = alloca i64, align 8
  %sc.addr = alloca %struct.archive_string_conv*, align 8
  %r = alloca i32, align 4
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3143, metadata !486), !dbg !3144
  store i8* %linkname, i8** %linkname.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %linkname.addr, metadata !3145, metadata !486), !dbg !3146
  store i64 %len, i64* %len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %len.addr, metadata !3147, metadata !486), !dbg !3148
  store %struct.archive_string_conv* %sc, %struct.archive_string_conv** %sc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string_conv** %sc.addr, metadata !3149, metadata !486), !dbg !3150
  call void @llvm.dbg.declare(metadata i32* %r, metadata !3151, metadata !486), !dbg !3152
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3153
  %ae_symlink = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 11, !dbg !3154
  %1 = load i8*, i8** %linkname.addr, align 8, !dbg !3155
  %2 = load i64, i64* %len.addr, align 8, !dbg !3156
  %3 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sc.addr, align 8, !dbg !3157
  %call = call i32 @archive_mstring_copy_mbs_len_l(%struct.archive_mstring* %ae_symlink, i8* %1, i64 %2, %struct.archive_string_conv* %3), !dbg !3158
  store i32 %call, i32* %r, align 4, !dbg !3159
  %4 = load i8*, i8** %linkname.addr, align 8, !dbg !3160
  %cmp = icmp ne i8* %4, null, !dbg !3162
  br i1 %cmp, label %land.lhs.true, label %if.else, !dbg !3163

land.lhs.true:                                    ; preds = %entry
  %5 = load i32, i32* %r, align 4, !dbg !3164
  %cmp2 = icmp eq i32 %5, 0, !dbg !3166
  br i1 %cmp2, label %if.then, label %if.else, !dbg !3167

if.then:                                          ; preds = %land.lhs.true
  %6 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3168
  %ae_set = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %6, i32 0, i32 4, !dbg !3169
  %7 = load i32, i32* %ae_set, align 8, !dbg !3170
  %or = or i32 %7, 2, !dbg !3170
  store i32 %or, i32* %ae_set, align 8, !dbg !3170
  br label %if.end, !dbg !3168

if.else:                                          ; preds = %land.lhs.true, %entry
  %8 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3171
  %ae_set3 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %8, i32 0, i32 4, !dbg !3172
  %9 = load i32, i32* %ae_set3, align 8, !dbg !3173
  %and = and i32 %9, -3, !dbg !3173
  store i32 %and, i32* %ae_set3, align 8, !dbg !3173
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %10 = load i32, i32* %r, align 4, !dbg !3174
  ret i32 %10, !dbg !3175
}

; Function Attrs: nounwind uwtable
define void @archive_entry_set_uid(%struct.archive_entry* %entry1, i64 %u) #0 !dbg !395 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %u.addr = alloca i64, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3176, metadata !486), !dbg !3177
  store i64 %u, i64* %u.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %u.addr, metadata !3178, metadata !486), !dbg !3179
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3180
  %stat_valid = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 2, !dbg !3181
  store i32 0, i32* %stat_valid, align 8, !dbg !3182
  %1 = load i64, i64* %u.addr, align 8, !dbg !3183
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3184
  %ae_stat = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 3, !dbg !3185
  %aest_uid = getelementptr inbounds %struct.aest, %struct.aest* %ae_stat, i32 0, i32 12, !dbg !3186
  store i64 %1, i64* %aest_uid, align 8, !dbg !3187
  ret void, !dbg !3188
}

; Function Attrs: nounwind uwtable
define void @archive_entry_set_uname(%struct.archive_entry* %entry1, i8* %name) #0 !dbg !396 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %name.addr = alloca i8*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3189, metadata !486), !dbg !3190
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !3191, metadata !486), !dbg !3192
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3193
  %ae_uname = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 12, !dbg !3194
  %1 = load i8*, i8** %name.addr, align 8, !dbg !3195
  %call = call i32 @archive_mstring_copy_mbs(%struct.archive_mstring* %ae_uname, i8* %1), !dbg !3196
  ret void, !dbg !3197
}

; Function Attrs: nounwind uwtable
define void @archive_entry_set_uname_utf8(%struct.archive_entry* %entry1, i8* %name) #0 !dbg !397 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %name.addr = alloca i8*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3198, metadata !486), !dbg !3199
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !3200, metadata !486), !dbg !3201
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3202
  %ae_uname = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 12, !dbg !3203
  %1 = load i8*, i8** %name.addr, align 8, !dbg !3204
  %call = call i32 @archive_mstring_copy_utf8(%struct.archive_mstring* %ae_uname, i8* %1), !dbg !3205
  ret void, !dbg !3206
}

; Function Attrs: nounwind uwtable
define void @archive_entry_copy_uname(%struct.archive_entry* %entry1, i8* %name) #0 !dbg !398 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %name.addr = alloca i8*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3207, metadata !486), !dbg !3208
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !3209, metadata !486), !dbg !3210
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3211
  %ae_uname = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 12, !dbg !3212
  %1 = load i8*, i8** %name.addr, align 8, !dbg !3213
  %call = call i32 @archive_mstring_copy_mbs(%struct.archive_mstring* %ae_uname, i8* %1), !dbg !3214
  ret void, !dbg !3215
}

; Function Attrs: nounwind uwtable
define void @archive_entry_copy_uname_w(%struct.archive_entry* %entry1, i32* %name) #0 !dbg !399 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %name.addr = alloca i32*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3216, metadata !486), !dbg !3217
  store i32* %name, i32** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %name.addr, metadata !3218, metadata !486), !dbg !3219
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3220
  %ae_uname = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 12, !dbg !3221
  %1 = load i32*, i32** %name.addr, align 8, !dbg !3222
  %call = call i32 @archive_mstring_copy_wcs(%struct.archive_mstring* %ae_uname, i32* %1), !dbg !3223
  ret void, !dbg !3224
}

; Function Attrs: nounwind uwtable
define i32 @archive_entry_update_uname_utf8(%struct.archive_entry* %entry1, i8* %name) #0 !dbg !400 {
entry:
  %retval = alloca i32, align 4
  %entry.addr = alloca %struct.archive_entry*, align 8
  %name.addr = alloca i8*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3225, metadata !486), !dbg !3226
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !3227, metadata !486), !dbg !3228
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3229
  %archive = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 0, !dbg !3231
  %1 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !3231
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3232
  %ae_uname = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 12, !dbg !3233
  %3 = load i8*, i8** %name.addr, align 8, !dbg !3234
  %call = call i32 @archive_mstring_update_utf8(%struct.archive* %1, %struct.archive_mstring* %ae_uname, i8* %3), !dbg !3235
  %cmp = icmp eq i32 %call, 0, !dbg !3236
  br i1 %cmp, label %if.then, label %if.end, !dbg !3237

if.then:                                          ; preds = %entry
  store i32 1, i32* %retval, align 4, !dbg !3238
  br label %return, !dbg !3238

if.end:                                           ; preds = %entry
  %call2 = call i32* @__errno_location() #1, !dbg !3239
  %4 = load i32, i32* %call2, align 4, !dbg !3239
  %cmp3 = icmp eq i32 %4, 12, !dbg !3241
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !3242

if.then4:                                         ; preds = %if.end
  call void @__archive_errx(i32 1, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0)) #11, !dbg !3243
  unreachable, !dbg !3243

if.end5:                                          ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !3244
  br label %return, !dbg !3244

return:                                           ; preds = %if.end5, %if.then
  %5 = load i32, i32* %retval, align 4, !dbg !3245
  ret i32 %5, !dbg !3245
}

; Function Attrs: nounwind uwtable
define void @archive_entry_set_is_data_encrypted(%struct.archive_entry* %entry1, i8 signext %is_encrypted) #0 !dbg !401 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %is_encrypted.addr = alloca i8, align 1
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3246, metadata !486), !dbg !3247
  store i8 %is_encrypted, i8* %is_encrypted.addr, align 1
  call void @llvm.dbg.declare(metadata i8* %is_encrypted.addr, metadata !3248, metadata !486), !dbg !3249
  %0 = load i8, i8* %is_encrypted.addr, align 1, !dbg !3250
  %tobool = icmp ne i8 %0, 0, !dbg !3250
  br i1 %tobool, label %if.then, label %if.else, !dbg !3252

if.then:                                          ; preds = %entry
  %1 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3253
  %encryption = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %1, i32 0, i32 14, !dbg !3255
  %2 = load i8, i8* %encryption, align 8, !dbg !3256
  %conv = sext i8 %2 to i32, !dbg !3256
  %or = or i32 %conv, 1, !dbg !3256
  %conv2 = trunc i32 %or to i8, !dbg !3256
  store i8 %conv2, i8* %encryption, align 8, !dbg !3256
  br label %if.end, !dbg !3257

if.else:                                          ; preds = %entry
  %3 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3258
  %encryption3 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %3, i32 0, i32 14, !dbg !3260
  %4 = load i8, i8* %encryption3, align 8, !dbg !3261
  %conv4 = sext i8 %4 to i32, !dbg !3261
  %and = and i32 %conv4, -2, !dbg !3261
  %conv5 = trunc i32 %and to i8, !dbg !3261
  store i8 %conv5, i8* %encryption3, align 8, !dbg !3261
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  ret void, !dbg !3262
}

; Function Attrs: nounwind uwtable
define void @archive_entry_set_is_metadata_encrypted(%struct.archive_entry* %entry1, i8 signext %is_encrypted) #0 !dbg !404 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %is_encrypted.addr = alloca i8, align 1
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3263, metadata !486), !dbg !3264
  store i8 %is_encrypted, i8* %is_encrypted.addr, align 1
  call void @llvm.dbg.declare(metadata i8* %is_encrypted.addr, metadata !3265, metadata !486), !dbg !3266
  %0 = load i8, i8* %is_encrypted.addr, align 1, !dbg !3267
  %tobool = icmp ne i8 %0, 0, !dbg !3267
  br i1 %tobool, label %if.then, label %if.else, !dbg !3269

if.then:                                          ; preds = %entry
  %1 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3270
  %encryption = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %1, i32 0, i32 14, !dbg !3272
  %2 = load i8, i8* %encryption, align 8, !dbg !3273
  %conv = sext i8 %2 to i32, !dbg !3273
  %or = or i32 %conv, 2, !dbg !3273
  %conv2 = trunc i32 %or to i8, !dbg !3273
  store i8 %conv2, i8* %encryption, align 8, !dbg !3273
  br label %if.end, !dbg !3274

if.else:                                          ; preds = %entry
  %3 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3275
  %encryption3 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %3, i32 0, i32 14, !dbg !3277
  %4 = load i8, i8* %encryption3, align 8, !dbg !3278
  %conv4 = sext i8 %4 to i32, !dbg !3278
  %and = and i32 %conv4, -3, !dbg !3278
  %conv5 = trunc i32 %and to i8, !dbg !3278
  store i8 %conv5, i8* %encryption3, align 8, !dbg !3278
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  ret void, !dbg !3279
}

; Function Attrs: nounwind uwtable
define i32 @_archive_entry_copy_uname_l(%struct.archive_entry* %entry1, i8* %name, i64 %len, %struct.archive_string_conv* %sc) #0 !dbg !405 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %name.addr = alloca i8*, align 8
  %len.addr = alloca i64, align 8
  %sc.addr = alloca %struct.archive_string_conv*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3280, metadata !486), !dbg !3281
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !3282, metadata !486), !dbg !3283
  store i64 %len, i64* %len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %len.addr, metadata !3284, metadata !486), !dbg !3285
  store %struct.archive_string_conv* %sc, %struct.archive_string_conv** %sc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string_conv** %sc.addr, metadata !3286, metadata !486), !dbg !3287
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3288
  %ae_uname = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 12, !dbg !3289
  %1 = load i8*, i8** %name.addr, align 8, !dbg !3290
  %2 = load i64, i64* %len.addr, align 8, !dbg !3291
  %3 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sc.addr, align 8, !dbg !3292
  %call = call i32 @archive_mstring_copy_mbs_len_l(%struct.archive_mstring* %ae_uname, i8* %1, i64 %2, %struct.archive_string_conv* %3), !dbg !3293
  ret i32 %call, !dbg !3294
}

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #3

; Function Attrs: noreturn nounwind
declare void @abort() #7

; Function Attrs: nounwind uwtable
define %struct.archive_acl* @archive_entry_acl(%struct.archive_entry* %entry1) #0 !dbg !412 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3295, metadata !486), !dbg !3296
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3297
  %acl = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 17, !dbg !3298
  ret %struct.archive_acl* %acl, !dbg !3299
}

; Function Attrs: nounwind uwtable
define void @archive_entry_acl_clear(%struct.archive_entry* %entry1) #0 !dbg !416 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3300, metadata !486), !dbg !3301
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3302
  %acl = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 17, !dbg !3303
  call void @archive_acl_clear(%struct.archive_acl* %acl), !dbg !3304
  ret void, !dbg !3305
}

; Function Attrs: nounwind uwtable
define i32 @archive_entry_acl_add_entry(%struct.archive_entry* %entry1, i32 %type, i32 %permset, i32 %tag, i32 %id, i8* %name) #0 !dbg !417 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %type.addr = alloca i32, align 4
  %permset.addr = alloca i32, align 4
  %tag.addr = alloca i32, align 4
  %id.addr = alloca i32, align 4
  %name.addr = alloca i8*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3306, metadata !486), !dbg !3307
  store i32 %type, i32* %type.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %type.addr, metadata !3308, metadata !486), !dbg !3309
  store i32 %permset, i32* %permset.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %permset.addr, metadata !3310, metadata !486), !dbg !3311
  store i32 %tag, i32* %tag.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tag.addr, metadata !3312, metadata !486), !dbg !3313
  store i32 %id, i32* %id.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %id.addr, metadata !3314, metadata !486), !dbg !3315
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !3316, metadata !486), !dbg !3317
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3318
  %acl = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 17, !dbg !3319
  %1 = load i32, i32* %type.addr, align 4, !dbg !3320
  %2 = load i32, i32* %permset.addr, align 4, !dbg !3321
  %3 = load i32, i32* %tag.addr, align 4, !dbg !3322
  %4 = load i32, i32* %id.addr, align 4, !dbg !3323
  %5 = load i8*, i8** %name.addr, align 8, !dbg !3324
  %call = call i32 @archive_acl_add_entry(%struct.archive_acl* %acl, i32 %1, i32 %2, i32 %3, i32 %4, i8* %5), !dbg !3325
  ret i32 %call, !dbg !3326
}

declare i32 @archive_acl_add_entry(%struct.archive_acl*, i32, i32, i32, i32, i8*) #2

; Function Attrs: nounwind uwtable
define i32 @archive_entry_acl_add_entry_w(%struct.archive_entry* %entry1, i32 %type, i32 %permset, i32 %tag, i32 %id, i32* %name) #0 !dbg !420 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %type.addr = alloca i32, align 4
  %permset.addr = alloca i32, align 4
  %tag.addr = alloca i32, align 4
  %id.addr = alloca i32, align 4
  %name.addr = alloca i32*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3327, metadata !486), !dbg !3328
  store i32 %type, i32* %type.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %type.addr, metadata !3329, metadata !486), !dbg !3330
  store i32 %permset, i32* %permset.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %permset.addr, metadata !3331, metadata !486), !dbg !3332
  store i32 %tag, i32* %tag.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tag.addr, metadata !3333, metadata !486), !dbg !3334
  store i32 %id, i32* %id.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %id.addr, metadata !3335, metadata !486), !dbg !3336
  store i32* %name, i32** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %name.addr, metadata !3337, metadata !486), !dbg !3338
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3339
  %acl = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 17, !dbg !3340
  %1 = load i32, i32* %type.addr, align 4, !dbg !3341
  %2 = load i32, i32* %permset.addr, align 4, !dbg !3342
  %3 = load i32, i32* %tag.addr, align 4, !dbg !3343
  %4 = load i32, i32* %id.addr, align 4, !dbg !3344
  %5 = load i32*, i32** %name.addr, align 8, !dbg !3345
  %6 = load i32*, i32** %name.addr, align 8, !dbg !3346
  %call = call i64 @wcslen(i32* %6) #12, !dbg !3347
  %call2 = call i32 @archive_acl_add_entry_w_len(%struct.archive_acl* %acl, i32 %1, i32 %2, i32 %3, i32 %4, i32* %5, i64 %call), !dbg !3348
  ret i32 %call2, !dbg !3349
}

declare i32 @archive_acl_add_entry_w_len(%struct.archive_acl*, i32, i32, i32, i32, i32*, i64) #2

; Function Attrs: nounwind readonly
declare i64 @wcslen(i32*) #8

; Function Attrs: nounwind uwtable
define i32 @archive_entry_acl_types(%struct.archive_entry* %entry1) #0 !dbg !423 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3350, metadata !486), !dbg !3351
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3352
  %acl = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 17, !dbg !3353
  %call = call i32 @archive_acl_types(%struct.archive_acl* %acl), !dbg !3354
  ret i32 %call, !dbg !3355
}

declare i32 @archive_acl_types(%struct.archive_acl*) #2

; Function Attrs: nounwind uwtable
define i32 @archive_entry_acl_count(%struct.archive_entry* %entry1, i32 %want_type) #0 !dbg !424 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %want_type.addr = alloca i32, align 4
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3356, metadata !486), !dbg !3357
  store i32 %want_type, i32* %want_type.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %want_type.addr, metadata !3358, metadata !486), !dbg !3359
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3360
  %acl = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 17, !dbg !3361
  %1 = load i32, i32* %want_type.addr, align 4, !dbg !3362
  %call = call i32 @archive_acl_count(%struct.archive_acl* %acl, i32 %1), !dbg !3363
  ret i32 %call, !dbg !3364
}

declare i32 @archive_acl_count(%struct.archive_acl*, i32) #2

; Function Attrs: nounwind uwtable
define i32 @archive_entry_acl_reset(%struct.archive_entry* %entry1, i32 %want_type) #0 !dbg !427 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %want_type.addr = alloca i32, align 4
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3365, metadata !486), !dbg !3366
  store i32 %want_type, i32* %want_type.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %want_type.addr, metadata !3367, metadata !486), !dbg !3368
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3369
  %acl = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 17, !dbg !3370
  %1 = load i32, i32* %want_type.addr, align 4, !dbg !3371
  %call = call i32 @archive_acl_reset(%struct.archive_acl* %acl, i32 %1), !dbg !3372
  ret i32 %call, !dbg !3373
}

declare i32 @archive_acl_reset(%struct.archive_acl*, i32) #2

; Function Attrs: nounwind uwtable
define i32 @archive_entry_acl_next(%struct.archive_entry* %entry1, i32 %want_type, i32* %type, i32* %permset, i32* %tag, i32* %id, i8** %name) #0 !dbg !428 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %want_type.addr = alloca i32, align 4
  %type.addr = alloca i32*, align 8
  %permset.addr = alloca i32*, align 8
  %tag.addr = alloca i32*, align 8
  %id.addr = alloca i32*, align 8
  %name.addr = alloca i8**, align 8
  %r = alloca i32, align 4
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3374, metadata !486), !dbg !3375
  store i32 %want_type, i32* %want_type.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %want_type.addr, metadata !3376, metadata !486), !dbg !3377
  store i32* %type, i32** %type.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %type.addr, metadata !3378, metadata !486), !dbg !3379
  store i32* %permset, i32** %permset.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %permset.addr, metadata !3380, metadata !486), !dbg !3381
  store i32* %tag, i32** %tag.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %tag.addr, metadata !3382, metadata !486), !dbg !3383
  store i32* %id, i32** %id.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %id.addr, metadata !3384, metadata !486), !dbg !3385
  store i8** %name, i8*** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %name.addr, metadata !3386, metadata !486), !dbg !3387
  call void @llvm.dbg.declare(metadata i32* %r, metadata !3388, metadata !486), !dbg !3389
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3390
  %archive = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 0, !dbg !3391
  %1 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !3391
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3392
  %acl = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 17, !dbg !3393
  %3 = load i32, i32* %want_type.addr, align 4, !dbg !3394
  %4 = load i32*, i32** %type.addr, align 8, !dbg !3395
  %5 = load i32*, i32** %permset.addr, align 8, !dbg !3396
  %6 = load i32*, i32** %tag.addr, align 8, !dbg !3397
  %7 = load i32*, i32** %id.addr, align 8, !dbg !3398
  %8 = load i8**, i8*** %name.addr, align 8, !dbg !3399
  %call = call i32 @archive_acl_next(%struct.archive* %1, %struct.archive_acl* %acl, i32 %3, i32* %4, i32* %5, i32* %6, i32* %7, i8** %8), !dbg !3400
  store i32 %call, i32* %r, align 4, !dbg !3401
  %9 = load i32, i32* %r, align 4, !dbg !3402
  %cmp = icmp eq i32 %9, -30, !dbg !3404
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !3405

land.lhs.true:                                    ; preds = %entry
  %call2 = call i32* @__errno_location() #1, !dbg !3406
  %10 = load i32, i32* %call2, align 4, !dbg !3406
  %cmp3 = icmp eq i32 %10, 12, !dbg !3408
  br i1 %cmp3, label %if.then, label %if.end, !dbg !3409

if.then:                                          ; preds = %land.lhs.true
  call void @__archive_errx(i32 1, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0)) #11, !dbg !3410
  unreachable, !dbg !3410

if.end:                                           ; preds = %land.lhs.true, %entry
  %11 = load i32, i32* %r, align 4, !dbg !3411
  ret i32 %11, !dbg !3412
}

declare i32 @archive_acl_next(%struct.archive*, %struct.archive_acl*, i32, i32*, i32*, i32*, i32*, i8**) #2

; Function Attrs: nounwind uwtable
define i32* @archive_entry_acl_to_text_w(%struct.archive_entry* %entry1, i64* %len, i32 %flags) #0 !dbg !432 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %len.addr = alloca i64*, align 8
  %flags.addr = alloca i32, align 4
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3413, metadata !486), !dbg !3414
  store i64* %len, i64** %len.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %len.addr, metadata !3415, metadata !486), !dbg !3416
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !3417, metadata !486), !dbg !3418
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3419
  %acl = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 17, !dbg !3420
  %1 = load i64*, i64** %len.addr, align 8, !dbg !3421
  %2 = load i32, i32* %flags.addr, align 4, !dbg !3422
  %3 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3423
  %archive = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %3, i32 0, i32 0, !dbg !3424
  %4 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !3424
  %call = call i32* @archive_acl_to_text_w(%struct.archive_acl* %acl, i64* %1, i32 %2, %struct.archive* %4), !dbg !3425
  ret i32* %call, !dbg !3426
}

declare i32* @archive_acl_to_text_w(%struct.archive_acl*, i64*, i32, %struct.archive*) #2

; Function Attrs: nounwind uwtable
define i8* @archive_entry_acl_to_text(%struct.archive_entry* %entry1, i64* %len, i32 %flags) #0 !dbg !435 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %len.addr = alloca i64*, align 8
  %flags.addr = alloca i32, align 4
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3427, metadata !486), !dbg !3428
  store i64* %len, i64** %len.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %len.addr, metadata !3429, metadata !486), !dbg !3430
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !3431, metadata !486), !dbg !3432
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3433
  %acl = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 17, !dbg !3434
  %1 = load i64*, i64** %len.addr, align 8, !dbg !3435
  %2 = load i32, i32* %flags.addr, align 4, !dbg !3436
  %call = call i8* @archive_acl_to_text_l(%struct.archive_acl* %acl, i64* %1, i32 %2, %struct.archive_string_conv* null), !dbg !3437
  ret i8* %call, !dbg !3438
}

declare i8* @archive_acl_to_text_l(%struct.archive_acl*, i64*, i32, %struct.archive_string_conv*) #2

; Function Attrs: nounwind uwtable
define i8* @_archive_entry_acl_to_text_l(%struct.archive_entry* %entry1, i64* %len, i32 %flags, %struct.archive_string_conv* %sc) #0 !dbg !438 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %len.addr = alloca i64*, align 8
  %flags.addr = alloca i32, align 4
  %sc.addr = alloca %struct.archive_string_conv*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3439, metadata !486), !dbg !3440
  store i64* %len, i64** %len.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %len.addr, metadata !3441, metadata !486), !dbg !3442
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !3443, metadata !486), !dbg !3444
  store %struct.archive_string_conv* %sc, %struct.archive_string_conv** %sc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string_conv** %sc.addr, metadata !3445, metadata !486), !dbg !3446
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3447
  %acl = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 17, !dbg !3448
  %1 = load i64*, i64** %len.addr, align 8, !dbg !3449
  %2 = load i32, i32* %flags.addr, align 4, !dbg !3450
  %3 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sc.addr, align 8, !dbg !3451
  %call = call i8* @archive_acl_to_text_l(%struct.archive_acl* %acl, i64* %1, i32 %2, %struct.archive_string_conv* %3), !dbg !3452
  ret i8* %call, !dbg !3453
}

; Function Attrs: nounwind uwtable
define i32 @archive_entry_acl_from_text_w(%struct.archive_entry* %entry1, i32* %wtext, i32 %type) #0 !dbg !441 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %wtext.addr = alloca i32*, align 8
  %type.addr = alloca i32, align 4
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3454, metadata !486), !dbg !3455
  store i32* %wtext, i32** %wtext.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %wtext.addr, metadata !3456, metadata !486), !dbg !3457
  store i32 %type, i32* %type.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %type.addr, metadata !3458, metadata !486), !dbg !3459
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3460
  %acl = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 17, !dbg !3461
  %1 = load i32*, i32** %wtext.addr, align 8, !dbg !3462
  %2 = load i32, i32* %type.addr, align 4, !dbg !3463
  %call = call i32 @archive_acl_from_text_w(%struct.archive_acl* %acl, i32* %1, i32 %2), !dbg !3464
  ret i32 %call, !dbg !3465
}

declare i32 @archive_acl_from_text_w(%struct.archive_acl*, i32*, i32) #2

; Function Attrs: nounwind uwtable
define i32 @archive_entry_acl_from_text(%struct.archive_entry* %entry1, i8* %text, i32 %type) #0 !dbg !444 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %text.addr = alloca i8*, align 8
  %type.addr = alloca i32, align 4
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3466, metadata !486), !dbg !3467
  store i8* %text, i8** %text.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %text.addr, metadata !3468, metadata !486), !dbg !3469
  store i32 %type, i32* %type.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %type.addr, metadata !3470, metadata !486), !dbg !3471
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3472
  %acl = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 17, !dbg !3473
  %1 = load i8*, i8** %text.addr, align 8, !dbg !3474
  %2 = load i32, i32* %type.addr, align 4, !dbg !3475
  %call = call i32 @archive_acl_from_text_l(%struct.archive_acl* %acl, i8* %1, i32 %2, %struct.archive_string_conv* null), !dbg !3476
  ret i32 %call, !dbg !3477
}

declare i32 @archive_acl_from_text_l(%struct.archive_acl*, i8*, i32, %struct.archive_string_conv*) #2

; Function Attrs: nounwind uwtable
define i32 @_archive_entry_acl_from_text_l(%struct.archive_entry* %entry1, i8* %text, i32 %type, %struct.archive_string_conv* %sc) #0 !dbg !447 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %text.addr = alloca i8*, align 8
  %type.addr = alloca i32, align 4
  %sc.addr = alloca %struct.archive_string_conv*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3478, metadata !486), !dbg !3479
  store i8* %text, i8** %text.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %text.addr, metadata !3480, metadata !486), !dbg !3481
  store i32 %type, i32* %type.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %type.addr, metadata !3482, metadata !486), !dbg !3483
  store %struct.archive_string_conv* %sc, %struct.archive_string_conv** %sc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string_conv** %sc.addr, metadata !3484, metadata !486), !dbg !3485
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3486
  %acl = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 17, !dbg !3487
  %1 = load i8*, i8** %text.addr, align 8, !dbg !3488
  %2 = load i32, i32* %type.addr, align 4, !dbg !3489
  %3 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sc.addr, align 8, !dbg !3490
  %call = call i32 @archive_acl_from_text_l(%struct.archive_acl* %acl, i8* %1, i32 %2, %struct.archive_string_conv* %3), !dbg !3491
  ret i32 %call, !dbg !3492
}

; Function Attrs: nounwind uwtable
define i32* @archive_entry_acl_text_w(%struct.archive_entry* %entry1, i32 %flags) #0 !dbg !450 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %flags.addr = alloca i32, align 4
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3493, metadata !486), !dbg !3494
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !3495, metadata !486), !dbg !3496
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3497
  %acl = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 17, !dbg !3499
  %acl_text_w = getelementptr inbounds %struct.archive_acl, %struct.archive_acl* %acl, i32 0, i32 4, !dbg !3500
  %1 = load i32*, i32** %acl_text_w, align 8, !dbg !3500
  %cmp = icmp ne i32* %1, null, !dbg !3501
  br i1 %cmp, label %if.then, label %if.end, !dbg !3502

if.then:                                          ; preds = %entry
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3503
  %acl2 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 17, !dbg !3505
  %acl_text_w3 = getelementptr inbounds %struct.archive_acl, %struct.archive_acl* %acl2, i32 0, i32 4, !dbg !3506
  %3 = load i32*, i32** %acl_text_w3, align 8, !dbg !3506
  %4 = bitcast i32* %3 to i8*, !dbg !3503
  call void @free(i8* %4) #9, !dbg !3507
  %5 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3508
  %acl4 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %5, i32 0, i32 17, !dbg !3509
  %acl_text_w5 = getelementptr inbounds %struct.archive_acl, %struct.archive_acl* %acl4, i32 0, i32 4, !dbg !3510
  store i32* null, i32** %acl_text_w5, align 8, !dbg !3511
  br label %if.end, !dbg !3512

if.end:                                           ; preds = %if.then, %entry
  %call = call i32 @archive_entry_acl_text_compat(i32* %flags.addr), !dbg !3513
  %cmp6 = icmp eq i32 %call, 0, !dbg !3515
  br i1 %cmp6, label %if.then7, label %if.end12, !dbg !3516

if.then7:                                         ; preds = %if.end
  %6 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3517
  %acl8 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %6, i32 0, i32 17, !dbg !3518
  %7 = load i32, i32* %flags.addr, align 4, !dbg !3519
  %8 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3520
  %archive = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %8, i32 0, i32 0, !dbg !3521
  %9 = load %struct.archive*, %struct.archive** %archive, align 8, !dbg !3521
  %call9 = call i32* @archive_acl_to_text_w(%struct.archive_acl* %acl8, i64* null, i32 %7, %struct.archive* %9), !dbg !3522
  %10 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3523
  %acl10 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %10, i32 0, i32 17, !dbg !3524
  %acl_text_w11 = getelementptr inbounds %struct.archive_acl, %struct.archive_acl* %acl10, i32 0, i32 4, !dbg !3525
  store i32* %call9, i32** %acl_text_w11, align 8, !dbg !3526
  br label %if.end12, !dbg !3523

if.end12:                                         ; preds = %if.then7, %if.end
  %11 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3527
  %acl13 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %11, i32 0, i32 17, !dbg !3528
  %acl_text_w14 = getelementptr inbounds %struct.archive_acl, %struct.archive_acl* %acl13, i32 0, i32 4, !dbg !3529
  %12 = load i32*, i32** %acl_text_w14, align 8, !dbg !3529
  ret i32* %12, !dbg !3530
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_entry_acl_text_compat(i32* %flags) #0 !dbg !459 {
entry:
  %retval = alloca i32, align 4
  %flags.addr = alloca i32*, align 8
  store i32* %flags, i32** %flags.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %flags.addr, metadata !3531, metadata !486), !dbg !3532
  %0 = load i32*, i32** %flags.addr, align 8, !dbg !3533
  %1 = load i32, i32* %0, align 4, !dbg !3535
  %and = and i32 %1, 768, !dbg !3536
  %cmp = icmp eq i32 %and, 0, !dbg !3537
  br i1 %cmp, label %if.then, label %if.end, !dbg !3538

if.then:                                          ; preds = %entry
  store i32 1, i32* %retval, align 4, !dbg !3539
  br label %return, !dbg !3539

if.end:                                           ; preds = %entry
  %2 = load i32*, i32** %flags.addr, align 8, !dbg !3540
  %3 = load i32, i32* %2, align 4, !dbg !3542
  %and1 = and i32 %3, 1024, !dbg !3543
  %cmp2 = icmp ne i32 %and1, 0, !dbg !3544
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !3545

if.then3:                                         ; preds = %if.end
  %4 = load i32*, i32** %flags.addr, align 8, !dbg !3546
  %5 = load i32, i32* %4, align 4, !dbg !3547
  %or = or i32 %5, 1, !dbg !3547
  store i32 %or, i32* %4, align 4, !dbg !3547
  br label %if.end4, !dbg !3548

if.end4:                                          ; preds = %if.then3, %if.end
  %6 = load i32*, i32** %flags.addr, align 8, !dbg !3549
  %7 = load i32, i32* %6, align 4, !dbg !3551
  %and5 = and i32 %7, 2048, !dbg !3552
  %cmp6 = icmp ne i32 %and5, 0, !dbg !3553
  br i1 %cmp6, label %if.then7, label %if.end9, !dbg !3554

if.then7:                                         ; preds = %if.end4
  %8 = load i32*, i32** %flags.addr, align 8, !dbg !3555
  %9 = load i32, i32* %8, align 4, !dbg !3556
  %or8 = or i32 %9, 2, !dbg !3556
  store i32 %or8, i32* %8, align 4, !dbg !3556
  br label %if.end9, !dbg !3557

if.end9:                                          ; preds = %if.then7, %if.end4
  %10 = load i32*, i32** %flags.addr, align 8, !dbg !3558
  %11 = load i32, i32* %10, align 4, !dbg !3559
  %or10 = or i32 %11, 8, !dbg !3559
  store i32 %or10, i32* %10, align 4, !dbg !3559
  store i32 0, i32* %retval, align 4, !dbg !3560
  br label %return, !dbg !3560

return:                                           ; preds = %if.end9, %if.then
  %12 = load i32, i32* %retval, align 4, !dbg !3561
  ret i32 %12, !dbg !3561
}

; Function Attrs: nounwind uwtable
define i8* @archive_entry_acl_text(%struct.archive_entry* %entry1, i32 %flags) #0 !dbg !453 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %flags.addr = alloca i32, align 4
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3562, metadata !486), !dbg !3563
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !3564, metadata !486), !dbg !3565
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3566
  %acl = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 17, !dbg !3568
  %acl_text = getelementptr inbounds %struct.archive_acl, %struct.archive_acl* %acl, i32 0, i32 5, !dbg !3569
  %1 = load i8*, i8** %acl_text, align 8, !dbg !3569
  %cmp = icmp ne i8* %1, null, !dbg !3570
  br i1 %cmp, label %if.then, label %if.end, !dbg !3571

if.then:                                          ; preds = %entry
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3572
  %acl2 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 17, !dbg !3574
  %acl_text3 = getelementptr inbounds %struct.archive_acl, %struct.archive_acl* %acl2, i32 0, i32 5, !dbg !3575
  %3 = load i8*, i8** %acl_text3, align 8, !dbg !3575
  call void @free(i8* %3) #9, !dbg !3576
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3577
  %acl4 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %4, i32 0, i32 17, !dbg !3578
  %acl_text5 = getelementptr inbounds %struct.archive_acl, %struct.archive_acl* %acl4, i32 0, i32 5, !dbg !3579
  store i8* null, i8** %acl_text5, align 8, !dbg !3580
  br label %if.end, !dbg !3581

if.end:                                           ; preds = %if.then, %entry
  %call = call i32 @archive_entry_acl_text_compat(i32* %flags.addr), !dbg !3582
  %cmp6 = icmp eq i32 %call, 0, !dbg !3584
  br i1 %cmp6, label %if.then7, label %if.end12, !dbg !3585

if.then7:                                         ; preds = %if.end
  %5 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3586
  %acl8 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %5, i32 0, i32 17, !dbg !3587
  %6 = load i32, i32* %flags.addr, align 4, !dbg !3588
  %call9 = call i8* @archive_acl_to_text_l(%struct.archive_acl* %acl8, i64* null, i32 %6, %struct.archive_string_conv* null), !dbg !3589
  %7 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3590
  %acl10 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %7, i32 0, i32 17, !dbg !3591
  %acl_text11 = getelementptr inbounds %struct.archive_acl, %struct.archive_acl* %acl10, i32 0, i32 5, !dbg !3592
  store i8* %call9, i8** %acl_text11, align 8, !dbg !3593
  br label %if.end12, !dbg !3590

if.end12:                                         ; preds = %if.then7, %if.end
  %8 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3594
  %acl13 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %8, i32 0, i32 17, !dbg !3595
  %acl_text14 = getelementptr inbounds %struct.archive_acl, %struct.archive_acl* %acl13, i32 0, i32 5, !dbg !3596
  %9 = load i8*, i8** %acl_text14, align 8, !dbg !3596
  ret i8* %9, !dbg !3597
}

; Function Attrs: nounwind uwtable
define i32 @_archive_entry_acl_text_l(%struct.archive_entry* %entry1, i32 %flags, i8** %acl_text, i64* %len, %struct.archive_string_conv* %sc) #0 !dbg !456 {
entry:
  %entry.addr = alloca %struct.archive_entry*, align 8
  %flags.addr = alloca i32, align 4
  %acl_text.addr = alloca i8**, align 8
  %len.addr = alloca i64*, align 8
  %sc.addr = alloca %struct.archive_string_conv*, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3598, metadata !486), !dbg !3599
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !3600, metadata !486), !dbg !3601
  store i8** %acl_text, i8*** %acl_text.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %acl_text.addr, metadata !3602, metadata !486), !dbg !3603
  store i64* %len, i64** %len.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %len.addr, metadata !3604, metadata !486), !dbg !3605
  store %struct.archive_string_conv* %sc, %struct.archive_string_conv** %sc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string_conv** %sc.addr, metadata !3606, metadata !486), !dbg !3607
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3608
  %acl = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %0, i32 0, i32 17, !dbg !3610
  %acl_text2 = getelementptr inbounds %struct.archive_acl, %struct.archive_acl* %acl, i32 0, i32 5, !dbg !3611
  %1 = load i8*, i8** %acl_text2, align 8, !dbg !3611
  %cmp = icmp ne i8* %1, null, !dbg !3612
  br i1 %cmp, label %if.then, label %if.end, !dbg !3613

if.then:                                          ; preds = %entry
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3614
  %acl3 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %2, i32 0, i32 17, !dbg !3616
  %acl_text4 = getelementptr inbounds %struct.archive_acl, %struct.archive_acl* %acl3, i32 0, i32 5, !dbg !3617
  %3 = load i8*, i8** %acl_text4, align 8, !dbg !3617
  call void @free(i8* %3) #9, !dbg !3618
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3619
  %acl5 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %4, i32 0, i32 17, !dbg !3620
  %acl_text6 = getelementptr inbounds %struct.archive_acl, %struct.archive_acl* %acl5, i32 0, i32 5, !dbg !3621
  store i8* null, i8** %acl_text6, align 8, !dbg !3622
  br label %if.end, !dbg !3623

if.end:                                           ; preds = %if.then, %entry
  %call = call i32 @archive_entry_acl_text_compat(i32* %flags.addr), !dbg !3624
  %cmp7 = icmp eq i32 %call, 0, !dbg !3626
  br i1 %cmp7, label %if.then8, label %if.end13, !dbg !3627

if.then8:                                         ; preds = %if.end
  %5 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3628
  %acl9 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %5, i32 0, i32 17, !dbg !3629
  %6 = load i64*, i64** %len.addr, align 8, !dbg !3630
  %7 = load i32, i32* %flags.addr, align 4, !dbg !3631
  %8 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sc.addr, align 8, !dbg !3632
  %call10 = call i8* @archive_acl_to_text_l(%struct.archive_acl* %acl9, i64* %6, i32 %7, %struct.archive_string_conv* %8), !dbg !3633
  %9 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3634
  %acl11 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %9, i32 0, i32 17, !dbg !3635
  %acl_text12 = getelementptr inbounds %struct.archive_acl, %struct.archive_acl* %acl11, i32 0, i32 5, !dbg !3636
  store i8* %call10, i8** %acl_text12, align 8, !dbg !3637
  br label %if.end13, !dbg !3634

if.end13:                                         ; preds = %if.then8, %if.end
  %10 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3638
  %acl14 = getelementptr inbounds %struct.archive_entry, %struct.archive_entry* %10, i32 0, i32 17, !dbg !3639
  %acl_text15 = getelementptr inbounds %struct.archive_acl, %struct.archive_acl* %acl14, i32 0, i32 5, !dbg !3640
  %11 = load i8*, i8** %acl_text15, align 8, !dbg !3640
  %12 = load i8**, i8*** %acl_text.addr, align 8, !dbg !3641
  store i8* %11, i8** %12, align 8, !dbg !3642
  ret i32 0, !dbg !3643
}

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #8

; Function Attrs: nounwind readonly
declare i32 @memcmp(i8*, i8*, i64) #8

; Function Attrs: nounwind readonly
declare i32 @wmemcmp(i32*, i32*, i64) #8

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { argmemonly nounwind }
attributes #5 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { noreturn "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #8 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #9 = { nounwind }
attributes #10 = { noreturn nounwind }
attributes #11 = { noreturn }
attributes #12 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!482, !483}
!llvm.ident = !{!484}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !211, globals: !471)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_entry.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !5, !171, !210, !93}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!5 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !6, size: 64, align: 64)
!6 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_entry", file: !7, line: 73, size: 8640, align: 64, elements: !8)
!7 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_entry_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!8 = !{!9, !108, !109, !110, !139, !140, !155, !156, !157, !158, !159, !160, !161, !162, !163, !164, !165, !166, !188, !196, !197, !204, !205, !206}
!9 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !6, file: !7, line: 74, baseType: !10, size: 64, align: 64)
!10 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !11, size: 64, align: 64)
!11 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !12, line: 89, size: 1280, align: 64, elements: !13)
!12 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!13 = !{!14, !16, !17, !81, !82, !83, !84, !85, !86, !87, !88, !96, !97, !98, !99, !102, !103, !104, !105, !106, !107}
!14 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !11, file: !12, line: 96, baseType: !15, size: 32, align: 32)
!15 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!16 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !11, file: !12, line: 97, baseType: !15, size: 32, align: 32, offset: 32)
!17 = !DIDerivedType(tag: DW_TAG_member, name: "vtable", scope: !11, file: !12, line: 103, baseType: !18, size: 64, align: 64, offset: 64)
!18 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !19, size: 64, align: 64)
!19 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_vtable", file: !12, line: 63, size: 832, align: 64, elements: !20)
!20 = !{!21, !26, !27, !31, !32, !46, !52, !57, !58, !65, !66, !70, !74}
!21 = !DIDerivedType(tag: DW_TAG_member, name: "archive_close", scope: !19, file: !12, line: 64, baseType: !22, size: 64, align: 64)
!22 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !23, size: 64, align: 64)
!23 = !DISubroutineType(types: !24)
!24 = !{!25, !10}
!25 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!26 = !DIDerivedType(tag: DW_TAG_member, name: "archive_free", scope: !19, file: !12, line: 65, baseType: !22, size: 64, align: 64, offset: 64)
!27 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_header", scope: !19, file: !12, line: 66, baseType: !28, size: 64, align: 64, offset: 128)
!28 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !29, size: 64, align: 64)
!29 = !DISubroutineType(types: !30)
!30 = !{!25, !10, !5}
!31 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_finish_entry", scope: !19, file: !12, line: 68, baseType: !22, size: 64, align: 64, offset: 192)
!32 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data", scope: !19, file: !12, line: 69, baseType: !33, size: 64, align: 64, offset: 256)
!33 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !34, size: 64, align: 64)
!34 = !DISubroutineType(types: !35)
!35 = !{!36, !10, !41, !43}
!36 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !37, line: 109, baseType: !38)
!37 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!38 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !39, line: 172, baseType: !40)
!39 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!40 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!41 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !42, size: 64, align: 64)
!42 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!43 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !44, line: 62, baseType: !45)
!44 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!45 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!46 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data_block", scope: !19, file: !12, line: 71, baseType: !47, size: 64, align: 64, offset: 320)
!47 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !48, size: 64, align: 64)
!48 = !DISubroutineType(types: !49)
!49 = !{!36, !10, !41, !43, !50}
!50 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !51, line: 40, baseType: !40)
!51 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!52 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header", scope: !19, file: !12, line: 74, baseType: !53, size: 64, align: 64, offset: 384)
!53 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !54, size: 64, align: 64)
!54 = !DISubroutineType(types: !55)
!55 = !{!25, !10, !56}
!56 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !5, size: 64, align: 64)
!57 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header2", scope: !19, file: !12, line: 76, baseType: !28, size: 64, align: 64, offset: 448)
!58 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_data_block", scope: !19, file: !12, line: 78, baseType: !59, size: 64, align: 64, offset: 512)
!59 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !60, size: 64, align: 64)
!60 = !DISubroutineType(types: !61)
!61 = !{!25, !10, !62, !63, !64}
!62 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !41, size: 64, align: 64)
!63 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !43, size: 64, align: 64)
!64 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !50, size: 64, align: 64)
!65 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_count", scope: !19, file: !12, line: 81, baseType: !22, size: 64, align: 64, offset: 576)
!66 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_bytes", scope: !19, file: !12, line: 82, baseType: !67, size: 64, align: 64, offset: 640)
!67 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !68, size: 64, align: 64)
!68 = !DISubroutineType(types: !69)
!69 = !{!50, !10, !25}
!70 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_code", scope: !19, file: !12, line: 83, baseType: !71, size: 64, align: 64, offset: 704)
!71 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !72, size: 64, align: 64)
!72 = !DISubroutineType(types: !73)
!73 = !{!25, !10, !25}
!74 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_name", scope: !19, file: !12, line: 84, baseType: !75, size: 64, align: 64, offset: 768)
!75 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !76, size: 64, align: 64)
!76 = !DISubroutineType(types: !77)
!77 = !{!78, !10, !25}
!78 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !79, size: 64, align: 64)
!79 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !80)
!80 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!81 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format", scope: !11, file: !12, line: 105, baseType: !25, size: 32, align: 32, offset: 128)
!82 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format_name", scope: !11, file: !12, line: 106, baseType: !78, size: 64, align: 64, offset: 192)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "compression_code", scope: !11, file: !12, line: 108, baseType: !25, size: 32, align: 32, offset: 256)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "compression_name", scope: !11, file: !12, line: 109, baseType: !78, size: 64, align: 64, offset: 320)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "file_count", scope: !11, file: !12, line: 112, baseType: !25, size: 32, align: 32, offset: 384)
!86 = !DIDerivedType(tag: DW_TAG_member, name: "archive_error_number", scope: !11, file: !12, line: 114, baseType: !25, size: 32, align: 32, offset: 416)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "error", scope: !11, file: !12, line: 115, baseType: !78, size: 64, align: 64, offset: 448)
!88 = !DIDerivedType(tag: DW_TAG_member, name: "error_string", scope: !11, file: !12, line: 116, baseType: !89, size: 192, align: 64, offset: 512)
!89 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string", file: !90, line: 58, size: 192, align: 64, elements: !91)
!90 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_string.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!91 = !{!92, !94, !95}
!92 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !89, file: !90, line: 59, baseType: !93, size: 64, align: 64)
!93 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !80, size: 64, align: 64)
!94 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !89, file: !90, line: 60, baseType: !43, size: 64, align: 64, offset: 64)
!95 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !89, file: !90, line: 61, baseType: !43, size: 64, align: 64, offset: 128)
!96 = !DIDerivedType(tag: DW_TAG_member, name: "current_code", scope: !11, file: !12, line: 118, baseType: !93, size: 64, align: 64, offset: 704)
!97 = !DIDerivedType(tag: DW_TAG_member, name: "current_codepage", scope: !11, file: !12, line: 119, baseType: !15, size: 32, align: 32, offset: 768)
!98 = !DIDerivedType(tag: DW_TAG_member, name: "current_oemcp", scope: !11, file: !12, line: 120, baseType: !15, size: 32, align: 32, offset: 800)
!99 = !DIDerivedType(tag: DW_TAG_member, name: "sconv", scope: !11, file: !12, line: 121, baseType: !100, size: 64, align: 64, offset: 832)
!100 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !101, size: 64, align: 64)
!101 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string_conv", file: !90, line: 70, flags: DIFlagFwdDecl)
!102 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_block", scope: !11, file: !12, line: 127, baseType: !78, size: 64, align: 64, offset: 896)
!103 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_offset", scope: !11, file: !12, line: 128, baseType: !50, size: 64, align: 64, offset: 960)
!104 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_output_offset", scope: !11, file: !12, line: 129, baseType: !50, size: 64, align: 64, offset: 1024)
!105 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_remaining", scope: !11, file: !12, line: 130, baseType: !43, size: 64, align: 64, offset: 1088)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_is_posix_read", scope: !11, file: !12, line: 137, baseType: !80, size: 8, align: 8, offset: 1152)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_requested", scope: !11, file: !12, line: 138, baseType: !43, size: 64, align: 64, offset: 1216)
!108 = !DIDerivedType(tag: DW_TAG_member, name: "stat", scope: !6, file: !7, line: 96, baseType: !4, size: 64, align: 64, offset: 64)
!109 = !DIDerivedType(tag: DW_TAG_member, name: "stat_valid", scope: !6, file: !7, line: 97, baseType: !25, size: 32, align: 32, offset: 128)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "ae_stat", scope: !6, file: !7, line: 129, baseType: !111, size: 1344, align: 64, offset: 192)
!111 = !DICompositeType(tag: DW_TAG_structure_type, name: "aest", file: !7, line: 99, size: 1344, align: 64, elements: !112)
!112 = !{!113, !114, !116, !117, !118, !119, !120, !121, !122, !123, !124, !125, !127, !128, !129, !133, !134, !135, !136, !137, !138}
!113 = !DIDerivedType(tag: DW_TAG_member, name: "aest_atime", scope: !111, file: !7, line: 100, baseType: !50, size: 64, align: 64)
!114 = !DIDerivedType(tag: DW_TAG_member, name: "aest_atime_nsec", scope: !111, file: !7, line: 101, baseType: !115, size: 32, align: 32, offset: 64)
!115 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !51, line: 51, baseType: !15)
!116 = !DIDerivedType(tag: DW_TAG_member, name: "aest_ctime", scope: !111, file: !7, line: 102, baseType: !50, size: 64, align: 64, offset: 128)
!117 = !DIDerivedType(tag: DW_TAG_member, name: "aest_ctime_nsec", scope: !111, file: !7, line: 103, baseType: !115, size: 32, align: 32, offset: 192)
!118 = !DIDerivedType(tag: DW_TAG_member, name: "aest_mtime", scope: !111, file: !7, line: 104, baseType: !50, size: 64, align: 64, offset: 256)
!119 = !DIDerivedType(tag: DW_TAG_member, name: "aest_mtime_nsec", scope: !111, file: !7, line: 105, baseType: !115, size: 32, align: 32, offset: 320)
!120 = !DIDerivedType(tag: DW_TAG_member, name: "aest_birthtime", scope: !111, file: !7, line: 106, baseType: !50, size: 64, align: 64, offset: 384)
!121 = !DIDerivedType(tag: DW_TAG_member, name: "aest_birthtime_nsec", scope: !111, file: !7, line: 107, baseType: !115, size: 32, align: 32, offset: 448)
!122 = !DIDerivedType(tag: DW_TAG_member, name: "aest_gid", scope: !111, file: !7, line: 108, baseType: !50, size: 64, align: 64, offset: 512)
!123 = !DIDerivedType(tag: DW_TAG_member, name: "aest_ino", scope: !111, file: !7, line: 109, baseType: !50, size: 64, align: 64, offset: 576)
!124 = !DIDerivedType(tag: DW_TAG_member, name: "aest_nlink", scope: !111, file: !7, line: 110, baseType: !115, size: 32, align: 32, offset: 640)
!125 = !DIDerivedType(tag: DW_TAG_member, name: "aest_size", scope: !111, file: !7, line: 111, baseType: !126, size: 64, align: 64, offset: 704)
!126 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !51, line: 55, baseType: !45)
!127 = !DIDerivedType(tag: DW_TAG_member, name: "aest_uid", scope: !111, file: !7, line: 112, baseType: !50, size: 64, align: 64, offset: 768)
!128 = !DIDerivedType(tag: DW_TAG_member, name: "aest_dev_is_broken_down", scope: !111, file: !7, line: 121, baseType: !25, size: 32, align: 32, offset: 832)
!129 = !DIDerivedType(tag: DW_TAG_member, name: "aest_dev", scope: !111, file: !7, line: 122, baseType: !130, size: 64, align: 64, offset: 896)
!130 = !DIDerivedType(tag: DW_TAG_typedef, name: "dev_t", file: !131, line: 44, baseType: !132)
!131 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/stat.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!132 = !DIDerivedType(tag: DW_TAG_typedef, name: "__dev_t", file: !39, line: 124, baseType: !45)
!133 = !DIDerivedType(tag: DW_TAG_member, name: "aest_devmajor", scope: !111, file: !7, line: 123, baseType: !130, size: 64, align: 64, offset: 960)
!134 = !DIDerivedType(tag: DW_TAG_member, name: "aest_devminor", scope: !111, file: !7, line: 124, baseType: !130, size: 64, align: 64, offset: 1024)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "aest_rdev_is_broken_down", scope: !111, file: !7, line: 125, baseType: !25, size: 32, align: 32, offset: 1088)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "aest_rdev", scope: !111, file: !7, line: 126, baseType: !130, size: 64, align: 64, offset: 1152)
!137 = !DIDerivedType(tag: DW_TAG_member, name: "aest_rdevmajor", scope: !111, file: !7, line: 127, baseType: !130, size: 64, align: 64, offset: 1216)
!138 = !DIDerivedType(tag: DW_TAG_member, name: "aest_rdevminor", scope: !111, file: !7, line: 128, baseType: !130, size: 64, align: 64, offset: 1280)
!139 = !DIDerivedType(tag: DW_TAG_member, name: "ae_set", scope: !6, file: !7, line: 131, baseType: !25, size: 32, align: 32, offset: 1536)
!140 = !DIDerivedType(tag: DW_TAG_member, name: "ae_fflags_text", scope: !6, file: !7, line: 145, baseType: !141, size: 832, align: 64, offset: 1600)
!141 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_mstring", file: !90, line: 209, size: 832, align: 64, elements: !142)
!142 = !{!143, !144, !145, !153, !154}
!143 = !DIDerivedType(tag: DW_TAG_member, name: "aes_mbs", scope: !141, file: !90, line: 210, baseType: !89, size: 192, align: 64)
!144 = !DIDerivedType(tag: DW_TAG_member, name: "aes_utf8", scope: !141, file: !90, line: 211, baseType: !89, size: 192, align: 64, offset: 192)
!145 = !DIDerivedType(tag: DW_TAG_member, name: "aes_wcs", scope: !141, file: !90, line: 212, baseType: !146, size: 192, align: 64, offset: 384)
!146 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_wstring", file: !90, line: 64, size: 192, align: 64, elements: !147)
!147 = !{!148, !151, !152}
!148 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !146, file: !90, line: 65, baseType: !149, size: 64, align: 64)
!149 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !150, size: 64, align: 64)
!150 = !DIDerivedType(tag: DW_TAG_typedef, name: "wchar_t", file: !44, line: 90, baseType: !25)
!151 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !146, file: !90, line: 66, baseType: !43, size: 64, align: 64, offset: 64)
!152 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !146, file: !90, line: 67, baseType: !43, size: 64, align: 64, offset: 128)
!153 = !DIDerivedType(tag: DW_TAG_member, name: "aes_mbs_in_locale", scope: !141, file: !90, line: 213, baseType: !89, size: 192, align: 64, offset: 576)
!154 = !DIDerivedType(tag: DW_TAG_member, name: "aes_set", scope: !141, file: !90, line: 218, baseType: !25, size: 32, align: 32, offset: 768)
!155 = !DIDerivedType(tag: DW_TAG_member, name: "ae_fflags_set", scope: !6, file: !7, line: 146, baseType: !45, size: 64, align: 64, offset: 2432)
!156 = !DIDerivedType(tag: DW_TAG_member, name: "ae_fflags_clear", scope: !6, file: !7, line: 147, baseType: !45, size: 64, align: 64, offset: 2496)
!157 = !DIDerivedType(tag: DW_TAG_member, name: "ae_gname", scope: !6, file: !7, line: 148, baseType: !141, size: 832, align: 64, offset: 2560)
!158 = !DIDerivedType(tag: DW_TAG_member, name: "ae_hardlink", scope: !6, file: !7, line: 149, baseType: !141, size: 832, align: 64, offset: 3392)
!159 = !DIDerivedType(tag: DW_TAG_member, name: "ae_pathname", scope: !6, file: !7, line: 150, baseType: !141, size: 832, align: 64, offset: 4224)
!160 = !DIDerivedType(tag: DW_TAG_member, name: "ae_symlink", scope: !6, file: !7, line: 151, baseType: !141, size: 832, align: 64, offset: 5056)
!161 = !DIDerivedType(tag: DW_TAG_member, name: "ae_uname", scope: !6, file: !7, line: 152, baseType: !141, size: 832, align: 64, offset: 5888)
!162 = !DIDerivedType(tag: DW_TAG_member, name: "ae_sourcepath", scope: !6, file: !7, line: 155, baseType: !141, size: 832, align: 64, offset: 6720)
!163 = !DIDerivedType(tag: DW_TAG_member, name: "encryption", scope: !6, file: !7, line: 160, baseType: !80, size: 8, align: 8, offset: 7552)
!164 = !DIDerivedType(tag: DW_TAG_member, name: "mac_metadata", scope: !6, file: !7, line: 162, baseType: !4, size: 64, align: 64, offset: 7616)
!165 = !DIDerivedType(tag: DW_TAG_member, name: "mac_metadata_size", scope: !6, file: !7, line: 163, baseType: !43, size: 64, align: 64, offset: 7680)
!166 = !DIDerivedType(tag: DW_TAG_member, name: "acl", scope: !6, file: !7, line: 166, baseType: !167, size: 448, align: 64, offset: 7744)
!167 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_acl", file: !168, line: 46, size: 448, align: 64, elements: !169)
!168 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_acl_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!169 = !{!170, !173, !183, !184, !185, !186, !187}
!170 = !DIDerivedType(tag: DW_TAG_member, name: "mode", scope: !167, file: !168, line: 47, baseType: !171, size: 32, align: 32)
!171 = !DIDerivedType(tag: DW_TAG_typedef, name: "mode_t", file: !131, line: 63, baseType: !172)
!172 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !39, line: 129, baseType: !15)
!173 = !DIDerivedType(tag: DW_TAG_member, name: "acl_head", scope: !167, file: !168, line: 48, baseType: !174, size: 64, align: 64, offset: 64)
!174 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !175, size: 64, align: 64)
!175 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_acl_entry", file: !168, line: 37, size: 1024, align: 64, elements: !176)
!176 = !{!177, !178, !179, !180, !181, !182}
!177 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !175, file: !168, line: 38, baseType: !174, size: 64, align: 64)
!178 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !175, file: !168, line: 39, baseType: !25, size: 32, align: 32, offset: 64)
!179 = !DIDerivedType(tag: DW_TAG_member, name: "tag", scope: !175, file: !168, line: 40, baseType: !25, size: 32, align: 32, offset: 96)
!180 = !DIDerivedType(tag: DW_TAG_member, name: "permset", scope: !175, file: !168, line: 41, baseType: !25, size: 32, align: 32, offset: 128)
!181 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !175, file: !168, line: 42, baseType: !25, size: 32, align: 32, offset: 160)
!182 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !175, file: !168, line: 43, baseType: !141, size: 832, align: 64, offset: 192)
!183 = !DIDerivedType(tag: DW_TAG_member, name: "acl_p", scope: !167, file: !168, line: 49, baseType: !174, size: 64, align: 64, offset: 128)
!184 = !DIDerivedType(tag: DW_TAG_member, name: "acl_state", scope: !167, file: !168, line: 50, baseType: !25, size: 32, align: 32, offset: 192)
!185 = !DIDerivedType(tag: DW_TAG_member, name: "acl_text_w", scope: !167, file: !168, line: 51, baseType: !149, size: 64, align: 64, offset: 256)
!186 = !DIDerivedType(tag: DW_TAG_member, name: "acl_text", scope: !167, file: !168, line: 52, baseType: !93, size: 64, align: 64, offset: 320)
!187 = !DIDerivedType(tag: DW_TAG_member, name: "acl_types", scope: !167, file: !168, line: 53, baseType: !25, size: 32, align: 32, offset: 384)
!188 = !DIDerivedType(tag: DW_TAG_member, name: "xattr_head", scope: !6, file: !7, line: 169, baseType: !189, size: 64, align: 64, offset: 8192)
!189 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !190, size: 64, align: 64)
!190 = !DICompositeType(tag: DW_TAG_structure_type, name: "ae_xattr", file: !7, line: 38, size: 256, align: 64, elements: !191)
!191 = !{!192, !193, !194, !195}
!192 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !190, file: !7, line: 39, baseType: !189, size: 64, align: 64)
!193 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !190, file: !7, line: 41, baseType: !93, size: 64, align: 64, offset: 64)
!194 = !DIDerivedType(tag: DW_TAG_member, name: "value", scope: !190, file: !7, line: 42, baseType: !4, size: 64, align: 64, offset: 128)
!195 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !190, file: !7, line: 43, baseType: !43, size: 64, align: 64, offset: 192)
!196 = !DIDerivedType(tag: DW_TAG_member, name: "xattr_p", scope: !6, file: !7, line: 170, baseType: !189, size: 64, align: 64, offset: 8256)
!197 = !DIDerivedType(tag: DW_TAG_member, name: "sparse_head", scope: !6, file: !7, line: 173, baseType: !198, size: 64, align: 64, offset: 8320)
!198 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !199, size: 64, align: 64)
!199 = !DICompositeType(tag: DW_TAG_structure_type, name: "ae_sparse", file: !7, line: 46, size: 192, align: 64, elements: !200)
!200 = !{!201, !202, !203}
!201 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !199, file: !7, line: 47, baseType: !198, size: 64, align: 64)
!202 = !DIDerivedType(tag: DW_TAG_member, name: "offset", scope: !199, file: !7, line: 49, baseType: !50, size: 64, align: 64, offset: 64)
!203 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !199, file: !7, line: 50, baseType: !50, size: 64, align: 64, offset: 128)
!204 = !DIDerivedType(tag: DW_TAG_member, name: "sparse_tail", scope: !6, file: !7, line: 174, baseType: !198, size: 64, align: 64, offset: 8384)
!205 = !DIDerivedType(tag: DW_TAG_member, name: "sparse_p", scope: !6, file: !7, line: 175, baseType: !198, size: 64, align: 64, offset: 8448)
!206 = !DIDerivedType(tag: DW_TAG_member, name: "strmode", scope: !6, file: !7, line: 178, baseType: !207, size: 96, align: 8, offset: 8512)
!207 = !DICompositeType(tag: DW_TAG_array_type, baseType: !80, size: 96, align: 8, elements: !208)
!208 = !{!209}
!209 = !DISubrange(count: 12)
!210 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !36, size: 64, align: 64)
!211 = !{!212, !215, !216, !219, !222, !225, !231, !234, !237, !238, !239, !240, !241, !242, !243, !246, !247, !248, !249, !252, !256, !259, !264, !265, !266, !271, !275, !276, !277, !278, !279, !280, !281, !282, !283, !284, !285, !286, !289, !290, !291, !292, !293, !294, !295, !296, !297, !298, !299, !300, !301, !302, !303, !304, !305, !306, !307, !308, !309, !310, !311, !312, !313, !316, !319, !322, !325, !328, !331, !332, !333, !336, !339, !342, !343, !344, !345, !346, !347, !348, !349, !350, !353, !354, !355, !356, !357, !358, !361, !362, !363, !364, !365, !366, !367, !368, !369, !372, !373, !374, !375, !376, !377, !378, !379, !380, !381, !382, !383, !384, !385, !386, !387, !388, !389, !390, !391, !392, !393, !394, !395, !396, !397, !398, !399, !400, !401, !404, !405, !406, !409, !412, !416, !417, !420, !423, !424, !427, !428, !432, !435, !438, !441, !444, !447, !450, !453, !456, !459, !462, !465, !468}
!212 = distinct !DISubprogram(name: "archive_entry_clear", scope: !1, file: !1, line: 155, type: !213, isLocal: false, isDefinition: true, scopeLine: 156, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!213 = !DISubroutineType(types: !214)
!214 = !{!5, !5}
!215 = distinct !DISubprogram(name: "archive_entry_clone", scope: !1, file: !1, line: 176, type: !213, isLocal: false, isDefinition: true, scopeLine: 177, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!216 = distinct !DISubprogram(name: "archive_entry_free", scope: !1, file: !1, line: 235, type: !217, isLocal: false, isDefinition: true, scopeLine: 236, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!217 = !DISubroutineType(types: !218)
!218 = !{null, !5}
!219 = distinct !DISubprogram(name: "archive_entry_new", scope: !1, file: !1, line: 242, type: !220, isLocal: false, isDefinition: true, scopeLine: 243, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!220 = !DISubroutineType(types: !221)
!221 = !{!5}
!222 = distinct !DISubprogram(name: "archive_entry_new2", scope: !1, file: !1, line: 248, type: !223, isLocal: false, isDefinition: true, scopeLine: 249, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!223 = !DISubroutineType(types: !224)
!224 = !{!5, !10}
!225 = distinct !DISubprogram(name: "archive_entry_atime", scope: !1, file: !1, line: 264, type: !226, isLocal: false, isDefinition: true, scopeLine: 265, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!226 = !DISubroutineType(types: !227)
!227 = !{!228, !5}
!228 = !DIDerivedType(tag: DW_TAG_typedef, name: "time_t", file: !229, line: 75, baseType: !230)
!229 = !DIFile(filename: "/usr/include/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!230 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !39, line: 139, baseType: !40)
!231 = distinct !DISubprogram(name: "archive_entry_atime_nsec", scope: !1, file: !1, line: 270, type: !232, isLocal: false, isDefinition: true, scopeLine: 271, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!232 = !DISubroutineType(types: !233)
!233 = !{!40, !5}
!234 = distinct !DISubprogram(name: "archive_entry_atime_is_set", scope: !1, file: !1, line: 276, type: !235, isLocal: false, isDefinition: true, scopeLine: 277, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!235 = !DISubroutineType(types: !236)
!236 = !{!25, !5}
!237 = distinct !DISubprogram(name: "archive_entry_birthtime", scope: !1, file: !1, line: 282, type: !226, isLocal: false, isDefinition: true, scopeLine: 283, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!238 = distinct !DISubprogram(name: "archive_entry_birthtime_nsec", scope: !1, file: !1, line: 288, type: !232, isLocal: false, isDefinition: true, scopeLine: 289, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!239 = distinct !DISubprogram(name: "archive_entry_birthtime_is_set", scope: !1, file: !1, line: 294, type: !235, isLocal: false, isDefinition: true, scopeLine: 295, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!240 = distinct !DISubprogram(name: "archive_entry_ctime", scope: !1, file: !1, line: 300, type: !226, isLocal: false, isDefinition: true, scopeLine: 301, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!241 = distinct !DISubprogram(name: "archive_entry_ctime_is_set", scope: !1, file: !1, line: 306, type: !235, isLocal: false, isDefinition: true, scopeLine: 307, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!242 = distinct !DISubprogram(name: "archive_entry_ctime_nsec", scope: !1, file: !1, line: 312, type: !232, isLocal: false, isDefinition: true, scopeLine: 313, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!243 = distinct !DISubprogram(name: "archive_entry_dev", scope: !1, file: !1, line: 318, type: !244, isLocal: false, isDefinition: true, scopeLine: 319, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!244 = !DISubroutineType(types: !245)
!245 = !{!130, !5}
!246 = distinct !DISubprogram(name: "archive_entry_dev_is_set", scope: !1, file: !1, line: 328, type: !235, isLocal: false, isDefinition: true, scopeLine: 329, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!247 = distinct !DISubprogram(name: "archive_entry_devmajor", scope: !1, file: !1, line: 334, type: !244, isLocal: false, isDefinition: true, scopeLine: 335, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!248 = distinct !DISubprogram(name: "archive_entry_devminor", scope: !1, file: !1, line: 343, type: !244, isLocal: false, isDefinition: true, scopeLine: 344, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!249 = distinct !DISubprogram(name: "archive_entry_filetype", scope: !1, file: !1, line: 352, type: !250, isLocal: false, isDefinition: true, scopeLine: 353, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!250 = !DISubroutineType(types: !251)
!251 = !{!171, !5}
!252 = distinct !DISubprogram(name: "archive_entry_fflags", scope: !1, file: !1, line: 358, type: !253, isLocal: false, isDefinition: true, scopeLine: 360, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!253 = !DISubroutineType(types: !254)
!254 = !{null, !5, !255, !255}
!255 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !45, size: 64, align: 64)
!256 = distinct !DISubprogram(name: "archive_entry_fflags_text", scope: !1, file: !1, line: 375, type: !257, isLocal: false, isDefinition: true, scopeLine: 376, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!257 = !DISubroutineType(types: !258)
!258 = !{!78, !5}
!259 = distinct !DISubprogram(name: "archive_entry_gid", scope: !1, file: !1, line: 405, type: !260, isLocal: false, isDefinition: true, scopeLine: 406, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!260 = !DISubroutineType(types: !261)
!261 = !{!262, !5}
!262 = !DIDerivedType(tag: DW_TAG_typedef, name: "la_int64_t", file: !263, line: 73, baseType: !50)
!263 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!264 = distinct !DISubprogram(name: "archive_entry_gname", scope: !1, file: !1, line: 411, type: !257, isLocal: false, isDefinition: true, scopeLine: 412, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!265 = distinct !DISubprogram(name: "archive_entry_gname_utf8", scope: !1, file: !1, line: 422, type: !257, isLocal: false, isDefinition: true, scopeLine: 423, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!266 = distinct !DISubprogram(name: "archive_entry_gname_w", scope: !1, file: !1, line: 434, type: !267, isLocal: false, isDefinition: true, scopeLine: 435, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!267 = !DISubroutineType(types: !268)
!268 = !{!269, !5}
!269 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !270, size: 64, align: 64)
!270 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !150)
!271 = distinct !DISubprogram(name: "_archive_entry_gname_l", scope: !1, file: !1, line: 445, type: !272, isLocal: false, isDefinition: true, scopeLine: 447, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!272 = !DISubroutineType(types: !273)
!273 = !{!25, !5, !274, !63, !100}
!274 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !78, size: 64, align: 64)
!275 = distinct !DISubprogram(name: "archive_entry_hardlink", scope: !1, file: !1, line: 452, type: !257, isLocal: false, isDefinition: true, scopeLine: 453, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!276 = distinct !DISubprogram(name: "archive_entry_hardlink_utf8", scope: !1, file: !1, line: 466, type: !257, isLocal: false, isDefinition: true, scopeLine: 467, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!277 = distinct !DISubprogram(name: "archive_entry_hardlink_w", scope: !1, file: !1, line: 480, type: !267, isLocal: false, isDefinition: true, scopeLine: 481, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!278 = distinct !DISubprogram(name: "_archive_entry_hardlink_l", scope: !1, file: !1, line: 494, type: !272, isLocal: false, isDefinition: true, scopeLine: 496, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!279 = distinct !DISubprogram(name: "archive_entry_ino", scope: !1, file: !1, line: 506, type: !260, isLocal: false, isDefinition: true, scopeLine: 507, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!280 = distinct !DISubprogram(name: "archive_entry_ino_is_set", scope: !1, file: !1, line: 512, type: !235, isLocal: false, isDefinition: true, scopeLine: 513, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!281 = distinct !DISubprogram(name: "archive_entry_ino64", scope: !1, file: !1, line: 518, type: !260, isLocal: false, isDefinition: true, scopeLine: 519, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!282 = distinct !DISubprogram(name: "archive_entry_mode", scope: !1, file: !1, line: 524, type: !250, isLocal: false, isDefinition: true, scopeLine: 525, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!283 = distinct !DISubprogram(name: "archive_entry_mtime", scope: !1, file: !1, line: 530, type: !226, isLocal: false, isDefinition: true, scopeLine: 531, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!284 = distinct !DISubprogram(name: "archive_entry_mtime_nsec", scope: !1, file: !1, line: 536, type: !232, isLocal: false, isDefinition: true, scopeLine: 537, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!285 = distinct !DISubprogram(name: "archive_entry_mtime_is_set", scope: !1, file: !1, line: 542, type: !235, isLocal: false, isDefinition: true, scopeLine: 543, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!286 = distinct !DISubprogram(name: "archive_entry_nlink", scope: !1, file: !1, line: 548, type: !287, isLocal: false, isDefinition: true, scopeLine: 549, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!287 = !DISubroutineType(types: !288)
!288 = !{!15, !5}
!289 = distinct !DISubprogram(name: "archive_entry_pathname", scope: !1, file: !1, line: 554, type: !257, isLocal: false, isDefinition: true, scopeLine: 555, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!290 = distinct !DISubprogram(name: "archive_entry_pathname_utf8", scope: !1, file: !1, line: 566, type: !257, isLocal: false, isDefinition: true, scopeLine: 567, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!291 = distinct !DISubprogram(name: "archive_entry_pathname_w", scope: !1, file: !1, line: 578, type: !267, isLocal: false, isDefinition: true, scopeLine: 579, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!292 = distinct !DISubprogram(name: "_archive_entry_pathname_l", scope: !1, file: !1, line: 590, type: !272, isLocal: false, isDefinition: true, scopeLine: 592, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!293 = distinct !DISubprogram(name: "archive_entry_perm", scope: !1, file: !1, line: 597, type: !250, isLocal: false, isDefinition: true, scopeLine: 598, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!294 = distinct !DISubprogram(name: "archive_entry_rdev", scope: !1, file: !1, line: 603, type: !244, isLocal: false, isDefinition: true, scopeLine: 604, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!295 = distinct !DISubprogram(name: "archive_entry_rdevmajor", scope: !1, file: !1, line: 613, type: !244, isLocal: false, isDefinition: true, scopeLine: 614, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!296 = distinct !DISubprogram(name: "archive_entry_rdevminor", scope: !1, file: !1, line: 622, type: !244, isLocal: false, isDefinition: true, scopeLine: 623, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!297 = distinct !DISubprogram(name: "archive_entry_size", scope: !1, file: !1, line: 631, type: !260, isLocal: false, isDefinition: true, scopeLine: 632, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!298 = distinct !DISubprogram(name: "archive_entry_size_is_set", scope: !1, file: !1, line: 637, type: !235, isLocal: false, isDefinition: true, scopeLine: 638, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!299 = distinct !DISubprogram(name: "archive_entry_sourcepath", scope: !1, file: !1, line: 643, type: !257, isLocal: false, isDefinition: true, scopeLine: 644, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!300 = distinct !DISubprogram(name: "archive_entry_sourcepath_w", scope: !1, file: !1, line: 655, type: !267, isLocal: false, isDefinition: true, scopeLine: 656, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!301 = distinct !DISubprogram(name: "archive_entry_symlink", scope: !1, file: !1, line: 665, type: !257, isLocal: false, isDefinition: true, scopeLine: 666, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!302 = distinct !DISubprogram(name: "archive_entry_symlink_utf8", scope: !1, file: !1, line: 679, type: !257, isLocal: false, isDefinition: true, scopeLine: 680, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!303 = distinct !DISubprogram(name: "archive_entry_symlink_w", scope: !1, file: !1, line: 693, type: !267, isLocal: false, isDefinition: true, scopeLine: 694, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!304 = distinct !DISubprogram(name: "_archive_entry_symlink_l", scope: !1, file: !1, line: 707, type: !272, isLocal: false, isDefinition: true, scopeLine: 709, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!305 = distinct !DISubprogram(name: "archive_entry_uid", scope: !1, file: !1, line: 719, type: !260, isLocal: false, isDefinition: true, scopeLine: 720, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!306 = distinct !DISubprogram(name: "archive_entry_uname", scope: !1, file: !1, line: 725, type: !257, isLocal: false, isDefinition: true, scopeLine: 726, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!307 = distinct !DISubprogram(name: "archive_entry_uname_utf8", scope: !1, file: !1, line: 736, type: !257, isLocal: false, isDefinition: true, scopeLine: 737, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!308 = distinct !DISubprogram(name: "archive_entry_uname_w", scope: !1, file: !1, line: 747, type: !267, isLocal: false, isDefinition: true, scopeLine: 748, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!309 = distinct !DISubprogram(name: "_archive_entry_uname_l", scope: !1, file: !1, line: 758, type: !272, isLocal: false, isDefinition: true, scopeLine: 760, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!310 = distinct !DISubprogram(name: "archive_entry_is_data_encrypted", scope: !1, file: !1, line: 765, type: !235, isLocal: false, isDefinition: true, scopeLine: 766, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!311 = distinct !DISubprogram(name: "archive_entry_is_metadata_encrypted", scope: !1, file: !1, line: 771, type: !235, isLocal: false, isDefinition: true, scopeLine: 772, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!312 = distinct !DISubprogram(name: "archive_entry_is_encrypted", scope: !1, file: !1, line: 777, type: !235, isLocal: false, isDefinition: true, scopeLine: 778, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!313 = distinct !DISubprogram(name: "archive_entry_set_filetype", scope: !1, file: !1, line: 787, type: !314, isLocal: false, isDefinition: true, scopeLine: 788, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!314 = !DISubroutineType(types: !315)
!315 = !{null, !5, !15}
!316 = distinct !DISubprogram(name: "archive_entry_set_fflags", scope: !1, file: !1, line: 795, type: !317, isLocal: false, isDefinition: true, scopeLine: 797, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!317 = !DISubroutineType(types: !318)
!318 = !{null, !5, !45, !45}
!319 = distinct !DISubprogram(name: "archive_entry_copy_fflags_text", scope: !1, file: !1, line: 804, type: !320, isLocal: false, isDefinition: true, scopeLine: 806, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!320 = !DISubroutineType(types: !321)
!321 = !{!78, !5, !78}
!322 = distinct !DISubprogram(name: "archive_entry_copy_fflags_text_w", scope: !1, file: !1, line: 813, type: !323, isLocal: false, isDefinition: true, scopeLine: 815, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!323 = !DISubroutineType(types: !324)
!324 = !{!269, !5, !269}
!325 = distinct !DISubprogram(name: "archive_entry_set_gid", scope: !1, file: !1, line: 822, type: !326, isLocal: false, isDefinition: true, scopeLine: 823, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!326 = !DISubroutineType(types: !327)
!327 = !{null, !5, !50}
!328 = distinct !DISubprogram(name: "archive_entry_set_gname", scope: !1, file: !1, line: 829, type: !329, isLocal: false, isDefinition: true, scopeLine: 830, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!329 = !DISubroutineType(types: !330)
!330 = !{null, !5, !78}
!331 = distinct !DISubprogram(name: "archive_entry_set_gname_utf8", scope: !1, file: !1, line: 835, type: !329, isLocal: false, isDefinition: true, scopeLine: 836, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!332 = distinct !DISubprogram(name: "archive_entry_copy_gname", scope: !1, file: !1, line: 841, type: !329, isLocal: false, isDefinition: true, scopeLine: 842, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!333 = distinct !DISubprogram(name: "archive_entry_copy_gname_w", scope: !1, file: !1, line: 847, type: !334, isLocal: false, isDefinition: true, scopeLine: 848, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!334 = !DISubroutineType(types: !335)
!335 = !{null, !5, !269}
!336 = distinct !DISubprogram(name: "archive_entry_update_gname_utf8", scope: !1, file: !1, line: 853, type: !337, isLocal: false, isDefinition: true, scopeLine: 854, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!337 = !DISubroutineType(types: !338)
!338 = !{!25, !5, !78}
!339 = distinct !DISubprogram(name: "_archive_entry_copy_gname_l", scope: !1, file: !1, line: 864, type: !340, isLocal: false, isDefinition: true, scopeLine: 866, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!340 = !DISubroutineType(types: !341)
!341 = !{!25, !5, !78, !43, !100}
!342 = distinct !DISubprogram(name: "archive_entry_set_ino", scope: !1, file: !1, line: 871, type: !326, isLocal: false, isDefinition: true, scopeLine: 872, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!343 = distinct !DISubprogram(name: "archive_entry_set_ino64", scope: !1, file: !1, line: 879, type: !326, isLocal: false, isDefinition: true, scopeLine: 880, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!344 = distinct !DISubprogram(name: "archive_entry_set_hardlink", scope: !1, file: !1, line: 887, type: !329, isLocal: false, isDefinition: true, scopeLine: 888, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!345 = distinct !DISubprogram(name: "archive_entry_set_hardlink_utf8", scope: !1, file: !1, line: 897, type: !329, isLocal: false, isDefinition: true, scopeLine: 898, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!346 = distinct !DISubprogram(name: "archive_entry_copy_hardlink", scope: !1, file: !1, line: 907, type: !329, isLocal: false, isDefinition: true, scopeLine: 908, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!347 = distinct !DISubprogram(name: "archive_entry_copy_hardlink_w", scope: !1, file: !1, line: 917, type: !334, isLocal: false, isDefinition: true, scopeLine: 918, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!348 = distinct !DISubprogram(name: "archive_entry_update_hardlink_utf8", scope: !1, file: !1, line: 927, type: !337, isLocal: false, isDefinition: true, scopeLine: 928, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!349 = distinct !DISubprogram(name: "_archive_entry_copy_hardlink_l", scope: !1, file: !1, line: 942, type: !340, isLocal: false, isDefinition: true, scopeLine: 944, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!350 = distinct !DISubprogram(name: "archive_entry_set_atime", scope: !1, file: !1, line: 957, type: !351, isLocal: false, isDefinition: true, scopeLine: 958, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!351 = !DISubroutineType(types: !352)
!352 = !{null, !5, !228, !40}
!353 = distinct !DISubprogram(name: "archive_entry_unset_atime", scope: !1, file: !1, line: 967, type: !217, isLocal: false, isDefinition: true, scopeLine: 968, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!354 = distinct !DISubprogram(name: "archive_entry_set_birthtime", scope: !1, file: !1, line: 974, type: !351, isLocal: false, isDefinition: true, scopeLine: 975, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!355 = distinct !DISubprogram(name: "archive_entry_unset_birthtime", scope: !1, file: !1, line: 984, type: !217, isLocal: false, isDefinition: true, scopeLine: 985, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!356 = distinct !DISubprogram(name: "archive_entry_set_ctime", scope: !1, file: !1, line: 991, type: !351, isLocal: false, isDefinition: true, scopeLine: 992, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!357 = distinct !DISubprogram(name: "archive_entry_unset_ctime", scope: !1, file: !1, line: 1001, type: !217, isLocal: false, isDefinition: true, scopeLine: 1002, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!358 = distinct !DISubprogram(name: "archive_entry_set_dev", scope: !1, file: !1, line: 1008, type: !359, isLocal: false, isDefinition: true, scopeLine: 1009, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!359 = !DISubroutineType(types: !360)
!360 = !{null, !5, !130}
!361 = distinct !DISubprogram(name: "archive_entry_set_devmajor", scope: !1, file: !1, line: 1017, type: !359, isLocal: false, isDefinition: true, scopeLine: 1018, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!362 = distinct !DISubprogram(name: "archive_entry_set_devminor", scope: !1, file: !1, line: 1026, type: !359, isLocal: false, isDefinition: true, scopeLine: 1027, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!363 = distinct !DISubprogram(name: "archive_entry_set_link", scope: !1, file: !1, line: 1036, type: !329, isLocal: false, isDefinition: true, scopeLine: 1037, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!364 = distinct !DISubprogram(name: "archive_entry_set_link_utf8", scope: !1, file: !1, line: 1045, type: !329, isLocal: false, isDefinition: true, scopeLine: 1046, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!365 = distinct !DISubprogram(name: "archive_entry_copy_link", scope: !1, file: !1, line: 1055, type: !329, isLocal: false, isDefinition: true, scopeLine: 1056, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!366 = distinct !DISubprogram(name: "archive_entry_copy_link_w", scope: !1, file: !1, line: 1065, type: !334, isLocal: false, isDefinition: true, scopeLine: 1066, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!367 = distinct !DISubprogram(name: "archive_entry_update_link_utf8", scope: !1, file: !1, line: 1074, type: !337, isLocal: false, isDefinition: true, scopeLine: 1075, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!368 = distinct !DISubprogram(name: "_archive_entry_copy_link_l", scope: !1, file: !1, line: 1091, type: !340, isLocal: false, isDefinition: true, scopeLine: 1093, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!369 = distinct !DISubprogram(name: "archive_entry_set_mode", scope: !1, file: !1, line: 1106, type: !370, isLocal: false, isDefinition: true, scopeLine: 1107, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!370 = !DISubroutineType(types: !371)
!371 = !{null, !5, !171}
!372 = distinct !DISubprogram(name: "archive_entry_set_mtime", scope: !1, file: !1, line: 1113, type: !351, isLocal: false, isDefinition: true, scopeLine: 1114, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!373 = distinct !DISubprogram(name: "archive_entry_unset_mtime", scope: !1, file: !1, line: 1123, type: !217, isLocal: false, isDefinition: true, scopeLine: 1124, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!374 = distinct !DISubprogram(name: "archive_entry_set_nlink", scope: !1, file: !1, line: 1130, type: !314, isLocal: false, isDefinition: true, scopeLine: 1131, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!375 = distinct !DISubprogram(name: "archive_entry_set_pathname", scope: !1, file: !1, line: 1137, type: !329, isLocal: false, isDefinition: true, scopeLine: 1138, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!376 = distinct !DISubprogram(name: "archive_entry_set_pathname_utf8", scope: !1, file: !1, line: 1143, type: !329, isLocal: false, isDefinition: true, scopeLine: 1144, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!377 = distinct !DISubprogram(name: "archive_entry_copy_pathname", scope: !1, file: !1, line: 1149, type: !329, isLocal: false, isDefinition: true, scopeLine: 1150, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!378 = distinct !DISubprogram(name: "archive_entry_copy_pathname_w", scope: !1, file: !1, line: 1155, type: !334, isLocal: false, isDefinition: true, scopeLine: 1156, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!379 = distinct !DISubprogram(name: "archive_entry_update_pathname_utf8", scope: !1, file: !1, line: 1161, type: !337, isLocal: false, isDefinition: true, scopeLine: 1162, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!380 = distinct !DISubprogram(name: "_archive_entry_copy_pathname_l", scope: !1, file: !1, line: 1172, type: !340, isLocal: false, isDefinition: true, scopeLine: 1174, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!381 = distinct !DISubprogram(name: "archive_entry_set_perm", scope: !1, file: !1, line: 1180, type: !370, isLocal: false, isDefinition: true, scopeLine: 1181, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!382 = distinct !DISubprogram(name: "archive_entry_set_rdev", scope: !1, file: !1, line: 1188, type: !359, isLocal: false, isDefinition: true, scopeLine: 1189, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!383 = distinct !DISubprogram(name: "archive_entry_set_rdevmajor", scope: !1, file: !1, line: 1196, type: !359, isLocal: false, isDefinition: true, scopeLine: 1197, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!384 = distinct !DISubprogram(name: "archive_entry_set_rdevminor", scope: !1, file: !1, line: 1204, type: !359, isLocal: false, isDefinition: true, scopeLine: 1205, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!385 = distinct !DISubprogram(name: "archive_entry_set_size", scope: !1, file: !1, line: 1212, type: !326, isLocal: false, isDefinition: true, scopeLine: 1213, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!386 = distinct !DISubprogram(name: "archive_entry_unset_size", scope: !1, file: !1, line: 1220, type: !217, isLocal: false, isDefinition: true, scopeLine: 1221, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!387 = distinct !DISubprogram(name: "archive_entry_copy_sourcepath", scope: !1, file: !1, line: 1227, type: !329, isLocal: false, isDefinition: true, scopeLine: 1228, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!388 = distinct !DISubprogram(name: "archive_entry_copy_sourcepath_w", scope: !1, file: !1, line: 1233, type: !334, isLocal: false, isDefinition: true, scopeLine: 1234, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!389 = distinct !DISubprogram(name: "archive_entry_set_symlink", scope: !1, file: !1, line: 1239, type: !329, isLocal: false, isDefinition: true, scopeLine: 1240, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!390 = distinct !DISubprogram(name: "archive_entry_set_symlink_utf8", scope: !1, file: !1, line: 1249, type: !329, isLocal: false, isDefinition: true, scopeLine: 1250, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!391 = distinct !DISubprogram(name: "archive_entry_copy_symlink", scope: !1, file: !1, line: 1259, type: !329, isLocal: false, isDefinition: true, scopeLine: 1260, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!392 = distinct !DISubprogram(name: "archive_entry_copy_symlink_w", scope: !1, file: !1, line: 1269, type: !334, isLocal: false, isDefinition: true, scopeLine: 1270, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!393 = distinct !DISubprogram(name: "archive_entry_update_symlink_utf8", scope: !1, file: !1, line: 1279, type: !337, isLocal: false, isDefinition: true, scopeLine: 1280, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!394 = distinct !DISubprogram(name: "_archive_entry_copy_symlink_l", scope: !1, file: !1, line: 1294, type: !340, isLocal: false, isDefinition: true, scopeLine: 1296, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!395 = distinct !DISubprogram(name: "archive_entry_set_uid", scope: !1, file: !1, line: 1309, type: !326, isLocal: false, isDefinition: true, scopeLine: 1310, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!396 = distinct !DISubprogram(name: "archive_entry_set_uname", scope: !1, file: !1, line: 1316, type: !329, isLocal: false, isDefinition: true, scopeLine: 1317, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!397 = distinct !DISubprogram(name: "archive_entry_set_uname_utf8", scope: !1, file: !1, line: 1322, type: !329, isLocal: false, isDefinition: true, scopeLine: 1323, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!398 = distinct !DISubprogram(name: "archive_entry_copy_uname", scope: !1, file: !1, line: 1328, type: !329, isLocal: false, isDefinition: true, scopeLine: 1329, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!399 = distinct !DISubprogram(name: "archive_entry_copy_uname_w", scope: !1, file: !1, line: 1334, type: !334, isLocal: false, isDefinition: true, scopeLine: 1335, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!400 = distinct !DISubprogram(name: "archive_entry_update_uname_utf8", scope: !1, file: !1, line: 1340, type: !337, isLocal: false, isDefinition: true, scopeLine: 1341, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!401 = distinct !DISubprogram(name: "archive_entry_set_is_data_encrypted", scope: !1, file: !1, line: 1351, type: !402, isLocal: false, isDefinition: true, scopeLine: 1352, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!402 = !DISubroutineType(types: !403)
!403 = !{null, !5, !80}
!404 = distinct !DISubprogram(name: "archive_entry_set_is_metadata_encrypted", scope: !1, file: !1, line: 1361, type: !402, isLocal: false, isDefinition: true, scopeLine: 1362, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!405 = distinct !DISubprogram(name: "_archive_entry_copy_uname_l", scope: !1, file: !1, line: 1371, type: !340, isLocal: false, isDefinition: true, scopeLine: 1373, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!406 = distinct !DISubprogram(name: "archive_entry_mac_metadata", scope: !1, file: !1, line: 1379, type: !407, isLocal: false, isDefinition: true, scopeLine: 1380, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!407 = !DISubroutineType(types: !408)
!408 = !{!41, !5, !63}
!409 = distinct !DISubprogram(name: "archive_entry_copy_mac_metadata", scope: !1, file: !1, line: 1386, type: !410, isLocal: false, isDefinition: true, scopeLine: 1388, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!410 = !DISubroutineType(types: !411)
!411 = !{null, !5, !41, !43}
!412 = distinct !DISubprogram(name: "archive_entry_acl", scope: !1, file: !1, line: 1412, type: !413, isLocal: false, isDefinition: true, scopeLine: 1413, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!413 = !DISubroutineType(types: !414)
!414 = !{!415, !5}
!415 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !167, size: 64, align: 64)
!416 = distinct !DISubprogram(name: "archive_entry_acl_clear", scope: !1, file: !1, line: 1418, type: !217, isLocal: false, isDefinition: true, scopeLine: 1419, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!417 = distinct !DISubprogram(name: "archive_entry_acl_add_entry", scope: !1, file: !1, line: 1427, type: !418, isLocal: false, isDefinition: true, scopeLine: 1429, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!418 = !DISubroutineType(types: !419)
!419 = !{!25, !5, !25, !25, !25, !25, !78}
!420 = distinct !DISubprogram(name: "archive_entry_acl_add_entry_w", scope: !1, file: !1, line: 1437, type: !421, isLocal: false, isDefinition: true, scopeLine: 1439, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!421 = !DISubroutineType(types: !422)
!422 = !{!25, !5, !25, !25, !25, !25, !269}
!423 = distinct !DISubprogram(name: "archive_entry_acl_types", scope: !1, file: !1, line: 1448, type: !235, isLocal: false, isDefinition: true, scopeLine: 1449, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!424 = distinct !DISubprogram(name: "archive_entry_acl_count", scope: !1, file: !1, line: 1457, type: !425, isLocal: false, isDefinition: true, scopeLine: 1458, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!425 = !DISubroutineType(types: !426)
!426 = !{!25, !5, !25}
!427 = distinct !DISubprogram(name: "archive_entry_acl_reset", scope: !1, file: !1, line: 1468, type: !425, isLocal: false, isDefinition: true, scopeLine: 1469, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!428 = distinct !DISubprogram(name: "archive_entry_acl_next", scope: !1, file: !1, line: 1478, type: !429, isLocal: false, isDefinition: true, scopeLine: 1480, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!429 = !DISubroutineType(types: !430)
!430 = !{!25, !5, !25, !431, !431, !431, !431, !274}
!431 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !25, size: 64, align: 64)
!432 = distinct !DISubprogram(name: "archive_entry_acl_to_text_w", scope: !1, file: !1, line: 1494, type: !433, isLocal: false, isDefinition: true, scopeLine: 1496, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!433 = !DISubroutineType(types: !434)
!434 = !{!149, !5, !210, !25}
!435 = distinct !DISubprogram(name: "archive_entry_acl_to_text", scope: !1, file: !1, line: 1502, type: !436, isLocal: false, isDefinition: true, scopeLine: 1504, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!436 = !DISubroutineType(types: !437)
!437 = !{!93, !5, !210, !25}
!438 = distinct !DISubprogram(name: "_archive_entry_acl_to_text_l", scope: !1, file: !1, line: 1509, type: !439, isLocal: false, isDefinition: true, scopeLine: 1511, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!439 = !DISubroutineType(types: !440)
!440 = !{!93, !5, !210, !25, !100}
!441 = distinct !DISubprogram(name: "archive_entry_acl_from_text_w", scope: !1, file: !1, line: 1519, type: !442, isLocal: false, isDefinition: true, scopeLine: 1521, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!442 = !DISubroutineType(types: !443)
!443 = !{!25, !5, !269, !25}
!444 = distinct !DISubprogram(name: "archive_entry_acl_from_text", scope: !1, file: !1, line: 1526, type: !445, isLocal: false, isDefinition: true, scopeLine: 1528, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!445 = !DISubroutineType(types: !446)
!446 = !{!25, !5, !78, !25}
!447 = distinct !DISubprogram(name: "_archive_entry_acl_from_text_l", scope: !1, file: !1, line: 1533, type: !448, isLocal: false, isDefinition: true, scopeLine: 1535, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!448 = !DISubroutineType(types: !449)
!449 = !{!25, !5, !78, !25, !100}
!450 = distinct !DISubprogram(name: "archive_entry_acl_text_w", scope: !1, file: !1, line: 1561, type: !451, isLocal: false, isDefinition: true, scopeLine: 1562, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!451 = !DISubroutineType(types: !452)
!452 = !{!269, !5, !25}
!453 = distinct !DISubprogram(name: "archive_entry_acl_text", scope: !1, file: !1, line: 1575, type: !454, isLocal: false, isDefinition: true, scopeLine: 1576, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!454 = !DISubroutineType(types: !455)
!455 = !{!78, !5, !25}
!456 = distinct !DISubprogram(name: "_archive_entry_acl_text_l", scope: !1, file: !1, line: 1590, type: !457, isLocal: false, isDefinition: true, scopeLine: 1592, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!457 = !DISubroutineType(types: !458)
!458 = !{!25, !5, !25, !274, !63, !100}
!459 = distinct !DISubprogram(name: "archive_entry_acl_text_compat", scope: !1, file: !1, line: 1541, type: !460, isLocal: true, isDefinition: true, scopeLine: 1542, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!460 = !DISubroutineType(types: !461)
!461 = !{!25, !431}
!462 = distinct !DISubprogram(name: "ae_fflagstostr", scope: !1, file: !1, line: 1838, type: !463, isLocal: true, isDefinition: true, scopeLine: 1839, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!463 = !DISubroutineType(types: !464)
!464 = !{!93, !45, !45}
!465 = distinct !DISubprogram(name: "ae_strtofflags", scope: !1, file: !1, line: 1892, type: !466, isLocal: true, isDefinition: true, scopeLine: 1893, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!466 = !DISubroutineType(types: !467)
!467 = !{!78, !78, !255, !255}
!468 = distinct !DISubprogram(name: "ae_wcstofflags", scope: !1, file: !1, line: 1960, type: !469, isLocal: true, isDefinition: true, scopeLine: 1961, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!469 = !DISubroutineType(types: !470)
!470 = !{!269, !269, !255, !255}
!471 = !{!472}
!472 = !DIGlobalVariable(name: "flags", scope: !0, file: !1, line: 1646, type: !473, isLocal: true, isDefinition: true, variable: [25 x %struct.flag]* @flags)
!473 = !DICompositeType(tag: DW_TAG_array_type, baseType: !474, size: 6400, align: 64, elements: !480)
!474 = !DICompositeType(tag: DW_TAG_structure_type, name: "flag", file: !1, line: 1641, size: 256, align: 64, elements: !475)
!475 = !{!476, !477, !478, !479}
!476 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !474, file: !1, line: 1642, baseType: !78, size: 64, align: 64)
!477 = !DIDerivedType(tag: DW_TAG_member, name: "wname", scope: !474, file: !1, line: 1643, baseType: !269, size: 64, align: 64, offset: 64)
!478 = !DIDerivedType(tag: DW_TAG_member, name: "set", scope: !474, file: !1, line: 1644, baseType: !45, size: 64, align: 64, offset: 128)
!479 = !DIDerivedType(tag: DW_TAG_member, name: "clear", scope: !474, file: !1, line: 1645, baseType: !45, size: 64, align: 64, offset: 192)
!480 = !{!481}
!481 = !DISubrange(count: 25)
!482 = !{i32 2, !"Dwarf Version", i32 4}
!483 = !{i32 2, !"Debug Info Version", i32 3}
!484 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!485 = !DILocalVariable(name: "entry", arg: 1, scope: !212, file: !1, line: 155, type: !5)
!486 = !DIExpression()
!487 = !DILocation(line: 155, column: 43, scope: !212)
!488 = !DILocation(line: 157, column: 6, scope: !489)
!489 = distinct !DILexicalBlock(scope: !212, file: !1, line: 157, column: 6)
!490 = !DILocation(line: 157, column: 12, scope: !489)
!491 = !DILocation(line: 157, column: 6, scope: !212)
!492 = !DILocation(line: 158, column: 3, scope: !489)
!493 = !DILocation(line: 159, column: 25, scope: !212)
!494 = !DILocation(line: 159, column: 32, scope: !212)
!495 = !DILocation(line: 159, column: 2, scope: !212)
!496 = !DILocation(line: 160, column: 25, scope: !212)
!497 = !DILocation(line: 160, column: 32, scope: !212)
!498 = !DILocation(line: 160, column: 2, scope: !212)
!499 = !DILocation(line: 161, column: 25, scope: !212)
!500 = !DILocation(line: 161, column: 32, scope: !212)
!501 = !DILocation(line: 161, column: 2, scope: !212)
!502 = !DILocation(line: 162, column: 25, scope: !212)
!503 = !DILocation(line: 162, column: 32, scope: !212)
!504 = !DILocation(line: 162, column: 2, scope: !212)
!505 = !DILocation(line: 163, column: 25, scope: !212)
!506 = !DILocation(line: 163, column: 32, scope: !212)
!507 = !DILocation(line: 163, column: 2, scope: !212)
!508 = !DILocation(line: 164, column: 25, scope: !212)
!509 = !DILocation(line: 164, column: 32, scope: !212)
!510 = !DILocation(line: 164, column: 2, scope: !212)
!511 = !DILocation(line: 165, column: 25, scope: !212)
!512 = !DILocation(line: 165, column: 32, scope: !212)
!513 = !DILocation(line: 165, column: 2, scope: !212)
!514 = !DILocation(line: 166, column: 34, scope: !212)
!515 = !DILocation(line: 166, column: 2, scope: !212)
!516 = !DILocation(line: 167, column: 21, scope: !212)
!517 = !DILocation(line: 167, column: 28, scope: !212)
!518 = !DILocation(line: 167, column: 2, scope: !212)
!519 = !DILocation(line: 168, column: 28, scope: !212)
!520 = !DILocation(line: 168, column: 2, scope: !212)
!521 = !DILocation(line: 169, column: 29, scope: !212)
!522 = !DILocation(line: 169, column: 2, scope: !212)
!523 = !DILocation(line: 170, column: 7, scope: !212)
!524 = !DILocation(line: 170, column: 14, scope: !212)
!525 = !DILocation(line: 170, column: 2, scope: !212)
!526 = !DILocation(line: 171, column: 9, scope: !212)
!527 = !DILocation(line: 171, column: 2, scope: !212)
!528 = !DILocation(line: 172, column: 9, scope: !212)
!529 = !DILocation(line: 172, column: 2, scope: !212)
!530 = !DILocation(line: 173, column: 1, scope: !212)
!531 = !DILocalVariable(name: "entry", arg: 1, scope: !409, file: !1, line: 1386, type: !5)
!532 = !DILocation(line: 1386, column: 55, scope: !409)
!533 = !DILocalVariable(name: "p", arg: 2, scope: !409, file: !1, line: 1387, type: !41)
!534 = !DILocation(line: 1387, column: 17, scope: !409)
!535 = !DILocalVariable(name: "s", arg: 3, scope: !409, file: !1, line: 1387, type: !43)
!536 = !DILocation(line: 1387, column: 27, scope: !409)
!537 = !DILocation(line: 1389, column: 8, scope: !409)
!538 = !DILocation(line: 1389, column: 15, scope: !409)
!539 = !DILocation(line: 1389, column: 3, scope: !409)
!540 = !DILocation(line: 1390, column: 7, scope: !541)
!541 = distinct !DILexicalBlock(scope: !409, file: !1, line: 1390, column: 7)
!542 = !DILocation(line: 1390, column: 9, scope: !541)
!543 = !DILocation(line: 1390, column: 17, scope: !541)
!544 = !DILocation(line: 1390, column: 20, scope: !545)
!545 = !DILexicalBlockFile(scope: !541, file: !1, discriminator: 1)
!546 = !DILocation(line: 1390, column: 22, scope: !545)
!547 = !DILocation(line: 1390, column: 7, scope: !545)
!548 = !DILocation(line: 1391, column: 5, scope: !549)
!549 = distinct !DILexicalBlock(scope: !541, file: !1, line: 1390, column: 28)
!550 = !DILocation(line: 1391, column: 12, scope: !549)
!551 = !DILocation(line: 1391, column: 25, scope: !549)
!552 = !DILocation(line: 1392, column: 5, scope: !549)
!553 = !DILocation(line: 1392, column: 12, scope: !549)
!554 = !DILocation(line: 1392, column: 30, scope: !549)
!555 = !DILocation(line: 1393, column: 3, scope: !549)
!556 = !DILocation(line: 1394, column: 32, scope: !557)
!557 = distinct !DILexicalBlock(scope: !541, file: !1, line: 1393, column: 10)
!558 = !DILocation(line: 1394, column: 5, scope: !557)
!559 = !DILocation(line: 1394, column: 12, scope: !557)
!560 = !DILocation(line: 1394, column: 30, scope: !557)
!561 = !DILocation(line: 1395, column: 34, scope: !557)
!562 = !DILocation(line: 1395, column: 27, scope: !557)
!563 = !DILocation(line: 1395, column: 5, scope: !557)
!564 = !DILocation(line: 1395, column: 12, scope: !557)
!565 = !DILocation(line: 1395, column: 25, scope: !557)
!566 = !DILocation(line: 1396, column: 9, scope: !567)
!567 = distinct !DILexicalBlock(scope: !557, file: !1, line: 1396, column: 9)
!568 = !DILocation(line: 1396, column: 16, scope: !567)
!569 = !DILocation(line: 1396, column: 29, scope: !567)
!570 = !DILocation(line: 1396, column: 9, scope: !557)
!571 = !DILocation(line: 1397, column: 7, scope: !567)
!572 = !DILocation(line: 1398, column: 12, scope: !557)
!573 = !DILocation(line: 1398, column: 19, scope: !557)
!574 = !DILocation(line: 1398, column: 33, scope: !557)
!575 = !DILocation(line: 1398, column: 36, scope: !557)
!576 = !DILocation(line: 1398, column: 5, scope: !557)
!577 = !DILocation(line: 1400, column: 1, scope: !409)
!578 = !DILocalVariable(name: "entry", arg: 1, scope: !215, file: !1, line: 176, type: !5)
!579 = !DILocation(line: 176, column: 43, scope: !215)
!580 = !DILocalVariable(name: "entry2", scope: !215, file: !1, line: 178, type: !5)
!581 = !DILocation(line: 178, column: 24, scope: !215)
!582 = !DILocalVariable(name: "xp", scope: !215, file: !1, line: 179, type: !189)
!583 = !DILocation(line: 179, column: 19, scope: !215)
!584 = !DILocalVariable(name: "sp", scope: !215, file: !1, line: 180, type: !198)
!585 = !DILocation(line: 180, column: 20, scope: !215)
!586 = !DILocalVariable(name: "s", scope: !215, file: !1, line: 181, type: !43)
!587 = !DILocation(line: 181, column: 9, scope: !215)
!588 = !DILocalVariable(name: "p", scope: !215, file: !1, line: 182, type: !41)
!589 = !DILocation(line: 182, column: 14, scope: !215)
!590 = !DILocation(line: 187, column: 30, scope: !215)
!591 = !DILocation(line: 187, column: 37, scope: !215)
!592 = !DILocation(line: 187, column: 11, scope: !215)
!593 = !DILocation(line: 187, column: 9, scope: !215)
!594 = !DILocation(line: 188, column: 6, scope: !595)
!595 = distinct !DILexicalBlock(scope: !215, file: !1, line: 188, column: 6)
!596 = !DILocation(line: 188, column: 13, scope: !595)
!597 = !DILocation(line: 188, column: 6, scope: !215)
!598 = !DILocation(line: 189, column: 3, scope: !595)
!599 = !DILocation(line: 190, column: 2, scope: !215)
!600 = !DILocation(line: 190, column: 10, scope: !215)
!601 = !DILocation(line: 190, column: 20, scope: !215)
!602 = !DILocation(line: 190, column: 27, scope: !215)
!603 = !DILocation(line: 191, column: 26, scope: !215)
!604 = !DILocation(line: 191, column: 33, scope: !215)
!605 = !DILocation(line: 191, column: 2, scope: !215)
!606 = !DILocation(line: 191, column: 10, scope: !215)
!607 = !DILocation(line: 191, column: 24, scope: !215)
!608 = !DILocation(line: 192, column: 28, scope: !215)
!609 = !DILocation(line: 192, column: 35, scope: !215)
!610 = !DILocation(line: 192, column: 2, scope: !215)
!611 = !DILocation(line: 192, column: 10, scope: !215)
!612 = !DILocation(line: 192, column: 26, scope: !215)
!613 = !DILocation(line: 196, column: 24, scope: !215)
!614 = !DILocation(line: 196, column: 32, scope: !215)
!615 = !DILocation(line: 196, column: 49, scope: !215)
!616 = !DILocation(line: 196, column: 56, scope: !215)
!617 = !DILocation(line: 196, column: 2, scope: !215)
!618 = !DILocation(line: 197, column: 24, scope: !215)
!619 = !DILocation(line: 197, column: 32, scope: !215)
!620 = !DILocation(line: 197, column: 43, scope: !215)
!621 = !DILocation(line: 197, column: 50, scope: !215)
!622 = !DILocation(line: 197, column: 2, scope: !215)
!623 = !DILocation(line: 198, column: 24, scope: !215)
!624 = !DILocation(line: 198, column: 32, scope: !215)
!625 = !DILocation(line: 198, column: 46, scope: !215)
!626 = !DILocation(line: 198, column: 53, scope: !215)
!627 = !DILocation(line: 198, column: 2, scope: !215)
!628 = !DILocation(line: 199, column: 24, scope: !215)
!629 = !DILocation(line: 199, column: 32, scope: !215)
!630 = !DILocation(line: 199, column: 46, scope: !215)
!631 = !DILocation(line: 199, column: 53, scope: !215)
!632 = !DILocation(line: 199, column: 2, scope: !215)
!633 = !DILocation(line: 200, column: 24, scope: !215)
!634 = !DILocation(line: 200, column: 32, scope: !215)
!635 = !DILocation(line: 200, column: 48, scope: !215)
!636 = !DILocation(line: 200, column: 55, scope: !215)
!637 = !DILocation(line: 200, column: 2, scope: !215)
!638 = !DILocation(line: 201, column: 24, scope: !215)
!639 = !DILocation(line: 201, column: 32, scope: !215)
!640 = !DILocation(line: 201, column: 45, scope: !215)
!641 = !DILocation(line: 201, column: 52, scope: !215)
!642 = !DILocation(line: 201, column: 2, scope: !215)
!643 = !DILocation(line: 202, column: 19, scope: !215)
!644 = !DILocation(line: 202, column: 26, scope: !215)
!645 = !DILocation(line: 202, column: 2, scope: !215)
!646 = !DILocation(line: 202, column: 10, scope: !215)
!647 = !DILocation(line: 202, column: 17, scope: !215)
!648 = !DILocation(line: 203, column: 24, scope: !215)
!649 = !DILocation(line: 203, column: 32, scope: !215)
!650 = !DILocation(line: 203, column: 43, scope: !215)
!651 = !DILocation(line: 203, column: 50, scope: !215)
!652 = !DILocation(line: 203, column: 2, scope: !215)
!653 = !DILocation(line: 206, column: 23, scope: !215)
!654 = !DILocation(line: 206, column: 30, scope: !215)
!655 = !DILocation(line: 206, column: 2, scope: !215)
!656 = !DILocation(line: 206, column: 10, scope: !215)
!657 = !DILocation(line: 206, column: 21, scope: !215)
!658 = !DILocation(line: 209, column: 20, scope: !215)
!659 = !DILocation(line: 209, column: 28, scope: !215)
!660 = !DILocation(line: 209, column: 34, scope: !215)
!661 = !DILocation(line: 209, column: 41, scope: !215)
!662 = !DILocation(line: 209, column: 2, scope: !215)
!663 = !DILocation(line: 212, column: 33, scope: !215)
!664 = !DILocation(line: 212, column: 6, scope: !215)
!665 = !DILocation(line: 212, column: 4, scope: !215)
!666 = !DILocation(line: 213, column: 34, scope: !215)
!667 = !DILocation(line: 213, column: 42, scope: !215)
!668 = !DILocation(line: 213, column: 45, scope: !215)
!669 = !DILocation(line: 213, column: 2, scope: !215)
!670 = !DILocation(line: 216, column: 7, scope: !215)
!671 = !DILocation(line: 216, column: 14, scope: !215)
!672 = !DILocation(line: 216, column: 5, scope: !215)
!673 = !DILocation(line: 217, column: 2, scope: !215)
!674 = !DILocation(line: 217, column: 9, scope: !675)
!675 = !DILexicalBlockFile(scope: !215, file: !1, discriminator: 1)
!676 = !DILocation(line: 217, column: 12, scope: !675)
!677 = !DILocation(line: 217, column: 2, scope: !675)
!678 = !DILocation(line: 218, column: 33, scope: !679)
!679 = distinct !DILexicalBlock(scope: !215, file: !1, line: 217, column: 21)
!680 = !DILocation(line: 219, column: 7, scope: !679)
!681 = !DILocation(line: 219, column: 11, scope: !679)
!682 = !DILocation(line: 219, column: 17, scope: !679)
!683 = !DILocation(line: 219, column: 21, scope: !679)
!684 = !DILocation(line: 219, column: 28, scope: !679)
!685 = !DILocation(line: 219, column: 32, scope: !679)
!686 = !DILocation(line: 218, column: 3, scope: !679)
!687 = !DILocation(line: 220, column: 8, scope: !679)
!688 = !DILocation(line: 220, column: 12, scope: !679)
!689 = !DILocation(line: 220, column: 6, scope: !679)
!690 = !DILocation(line: 217, column: 2, scope: !691)
!691 = !DILexicalBlockFile(scope: !215, file: !1, discriminator: 2)
!692 = !DILocation(line: 224, column: 7, scope: !215)
!693 = !DILocation(line: 224, column: 14, scope: !215)
!694 = !DILocation(line: 224, column: 5, scope: !215)
!695 = !DILocation(line: 225, column: 2, scope: !215)
!696 = !DILocation(line: 225, column: 9, scope: !675)
!697 = !DILocation(line: 225, column: 12, scope: !675)
!698 = !DILocation(line: 225, column: 2, scope: !675)
!699 = !DILocation(line: 226, column: 34, scope: !700)
!700 = distinct !DILexicalBlock(scope: !215, file: !1, line: 225, column: 21)
!701 = !DILocation(line: 227, column: 7, scope: !700)
!702 = !DILocation(line: 227, column: 11, scope: !700)
!703 = !DILocation(line: 227, column: 19, scope: !700)
!704 = !DILocation(line: 227, column: 23, scope: !700)
!705 = !DILocation(line: 226, column: 3, scope: !700)
!706 = !DILocation(line: 228, column: 8, scope: !700)
!707 = !DILocation(line: 228, column: 12, scope: !700)
!708 = !DILocation(line: 228, column: 6, scope: !700)
!709 = !DILocation(line: 225, column: 2, scope: !691)
!710 = !DILocation(line: 231, column: 10, scope: !215)
!711 = !DILocation(line: 231, column: 2, scope: !215)
!712 = !DILocation(line: 232, column: 1, scope: !215)
!713 = !DILocalVariable(name: "a", arg: 1, scope: !222, file: !1, line: 248, type: !10)
!714 = !DILocation(line: 248, column: 36, scope: !222)
!715 = !DILocalVariable(name: "entry", scope: !222, file: !1, line: 250, type: !5)
!716 = !DILocation(line: 250, column: 24, scope: !222)
!717 = !DILocation(line: 252, column: 34, scope: !222)
!718 = !DILocation(line: 252, column: 10, scope: !222)
!719 = !DILocation(line: 252, column: 8, scope: !222)
!720 = !DILocation(line: 253, column: 6, scope: !721)
!721 = distinct !DILexicalBlock(scope: !222, file: !1, line: 253, column: 6)
!722 = !DILocation(line: 253, column: 12, scope: !721)
!723 = !DILocation(line: 253, column: 6, scope: !222)
!724 = !DILocation(line: 254, column: 3, scope: !721)
!725 = !DILocation(line: 255, column: 19, scope: !222)
!726 = !DILocation(line: 255, column: 2, scope: !222)
!727 = !DILocation(line: 255, column: 9, scope: !222)
!728 = !DILocation(line: 255, column: 17, scope: !222)
!729 = !DILocation(line: 256, column: 10, scope: !222)
!730 = !DILocation(line: 256, column: 2, scope: !222)
!731 = !DILocation(line: 257, column: 1, scope: !222)
!732 = !DILocalVariable(name: "entry", arg: 1, scope: !406, file: !1, line: 1379, type: !5)
!733 = !DILocation(line: 1379, column: 50, scope: !406)
!734 = !DILocalVariable(name: "s", arg: 2, scope: !406, file: !1, line: 1379, type: !63)
!735 = !DILocation(line: 1379, column: 65, scope: !406)
!736 = !DILocation(line: 1381, column: 8, scope: !406)
!737 = !DILocation(line: 1381, column: 15, scope: !406)
!738 = !DILocation(line: 1381, column: 4, scope: !406)
!739 = !DILocation(line: 1381, column: 6, scope: !406)
!740 = !DILocation(line: 1382, column: 10, scope: !406)
!741 = !DILocation(line: 1382, column: 17, scope: !406)
!742 = !DILocation(line: 1382, column: 3, scope: !406)
!743 = !DILocalVariable(name: "entry", arg: 1, scope: !216, file: !1, line: 235, type: !5)
!744 = !DILocation(line: 235, column: 42, scope: !216)
!745 = !DILocation(line: 237, column: 22, scope: !216)
!746 = !DILocation(line: 237, column: 2, scope: !216)
!747 = !DILocation(line: 238, column: 7, scope: !216)
!748 = !DILocation(line: 238, column: 2, scope: !216)
!749 = !DILocation(line: 239, column: 1, scope: !216)
!750 = !DILocation(line: 244, column: 9, scope: !219)
!751 = !DILocation(line: 244, column: 2, scope: !219)
!752 = !DILocalVariable(name: "entry", arg: 1, scope: !225, file: !1, line: 264, type: !5)
!753 = !DILocation(line: 264, column: 43, scope: !225)
!754 = !DILocation(line: 266, column: 10, scope: !225)
!755 = !DILocation(line: 266, column: 17, scope: !225)
!756 = !DILocation(line: 266, column: 25, scope: !225)
!757 = !DILocation(line: 266, column: 2, scope: !225)
!758 = !DILocalVariable(name: "entry", arg: 1, scope: !231, file: !1, line: 270, type: !5)
!759 = !DILocation(line: 270, column: 48, scope: !231)
!760 = !DILocation(line: 272, column: 10, scope: !231)
!761 = !DILocation(line: 272, column: 17, scope: !231)
!762 = !DILocation(line: 272, column: 25, scope: !231)
!763 = !DILocation(line: 272, column: 9, scope: !231)
!764 = !DILocation(line: 272, column: 2, scope: !231)
!765 = !DILocalVariable(name: "entry", arg: 1, scope: !234, file: !1, line: 276, type: !5)
!766 = !DILocation(line: 276, column: 50, scope: !234)
!767 = !DILocation(line: 278, column: 10, scope: !234)
!768 = !DILocation(line: 278, column: 17, scope: !234)
!769 = !DILocation(line: 278, column: 24, scope: !234)
!770 = !DILocation(line: 278, column: 2, scope: !234)
!771 = !DILocalVariable(name: "entry", arg: 1, scope: !237, file: !1, line: 282, type: !5)
!772 = !DILocation(line: 282, column: 47, scope: !237)
!773 = !DILocation(line: 284, column: 10, scope: !237)
!774 = !DILocation(line: 284, column: 17, scope: !237)
!775 = !DILocation(line: 284, column: 25, scope: !237)
!776 = !DILocation(line: 284, column: 2, scope: !237)
!777 = !DILocalVariable(name: "entry", arg: 1, scope: !238, file: !1, line: 288, type: !5)
!778 = !DILocation(line: 288, column: 52, scope: !238)
!779 = !DILocation(line: 290, column: 10, scope: !238)
!780 = !DILocation(line: 290, column: 17, scope: !238)
!781 = !DILocation(line: 290, column: 25, scope: !238)
!782 = !DILocation(line: 290, column: 9, scope: !238)
!783 = !DILocation(line: 290, column: 2, scope: !238)
!784 = !DILocalVariable(name: "entry", arg: 1, scope: !239, file: !1, line: 294, type: !5)
!785 = !DILocation(line: 294, column: 54, scope: !239)
!786 = !DILocation(line: 296, column: 10, scope: !239)
!787 = !DILocation(line: 296, column: 17, scope: !239)
!788 = !DILocation(line: 296, column: 24, scope: !239)
!789 = !DILocation(line: 296, column: 2, scope: !239)
!790 = !DILocalVariable(name: "entry", arg: 1, scope: !240, file: !1, line: 300, type: !5)
!791 = !DILocation(line: 300, column: 43, scope: !240)
!792 = !DILocation(line: 302, column: 10, scope: !240)
!793 = !DILocation(line: 302, column: 17, scope: !240)
!794 = !DILocation(line: 302, column: 25, scope: !240)
!795 = !DILocation(line: 302, column: 2, scope: !240)
!796 = !DILocalVariable(name: "entry", arg: 1, scope: !241, file: !1, line: 306, type: !5)
!797 = !DILocation(line: 306, column: 50, scope: !241)
!798 = !DILocation(line: 308, column: 10, scope: !241)
!799 = !DILocation(line: 308, column: 17, scope: !241)
!800 = !DILocation(line: 308, column: 24, scope: !241)
!801 = !DILocation(line: 308, column: 2, scope: !241)
!802 = !DILocalVariable(name: "entry", arg: 1, scope: !242, file: !1, line: 312, type: !5)
!803 = !DILocation(line: 312, column: 48, scope: !242)
!804 = !DILocation(line: 314, column: 10, scope: !242)
!805 = !DILocation(line: 314, column: 17, scope: !242)
!806 = !DILocation(line: 314, column: 25, scope: !242)
!807 = !DILocation(line: 314, column: 9, scope: !242)
!808 = !DILocation(line: 314, column: 2, scope: !242)
!809 = !DILocalVariable(name: "entry", arg: 1, scope: !243, file: !1, line: 318, type: !5)
!810 = !DILocation(line: 318, column: 41, scope: !243)
!811 = !DILocation(line: 320, column: 6, scope: !812)
!812 = distinct !DILexicalBlock(scope: !243, file: !1, line: 320, column: 6)
!813 = !DILocation(line: 320, column: 13, scope: !812)
!814 = !DILocation(line: 320, column: 21, scope: !812)
!815 = !DILocation(line: 320, column: 6, scope: !243)
!816 = !DILocation(line: 321, column: 10, scope: !812)
!817 = !DILocation(line: 321, column: 3, scope: !812)
!818 = !DILocation(line: 324, column: 11, scope: !812)
!819 = !DILocation(line: 324, column: 18, scope: !812)
!820 = !DILocation(line: 324, column: 26, scope: !812)
!821 = !DILocation(line: 324, column: 3, scope: !812)
!822 = !DILocation(line: 325, column: 1, scope: !243)
!823 = !DILocalVariable(name: "entry", arg: 1, scope: !246, file: !1, line: 328, type: !5)
!824 = !DILocation(line: 328, column: 48, scope: !246)
!825 = !DILocation(line: 330, column: 10, scope: !246)
!826 = !DILocation(line: 330, column: 17, scope: !246)
!827 = !DILocation(line: 330, column: 24, scope: !246)
!828 = !DILocation(line: 330, column: 2, scope: !246)
!829 = !DILocalVariable(name: "entry", arg: 1, scope: !247, file: !1, line: 334, type: !5)
!830 = !DILocation(line: 334, column: 46, scope: !247)
!831 = !DILocation(line: 336, column: 6, scope: !832)
!832 = distinct !DILexicalBlock(scope: !247, file: !1, line: 336, column: 6)
!833 = !DILocation(line: 336, column: 13, scope: !832)
!834 = !DILocation(line: 336, column: 21, scope: !832)
!835 = !DILocation(line: 336, column: 6, scope: !247)
!836 = !DILocation(line: 337, column: 11, scope: !832)
!837 = !DILocation(line: 337, column: 18, scope: !832)
!838 = !DILocation(line: 337, column: 26, scope: !832)
!839 = !DILocation(line: 337, column: 3, scope: !832)
!840 = !DILocation(line: 339, column: 10, scope: !832)
!841 = !DILocation(line: 339, column: 3, scope: !832)
!842 = !DILocation(line: 340, column: 1, scope: !247)
!843 = !DILocalVariable(name: "entry", arg: 1, scope: !248, file: !1, line: 343, type: !5)
!844 = !DILocation(line: 343, column: 46, scope: !248)
!845 = !DILocation(line: 345, column: 6, scope: !846)
!846 = distinct !DILexicalBlock(scope: !248, file: !1, line: 345, column: 6)
!847 = !DILocation(line: 345, column: 13, scope: !846)
!848 = !DILocation(line: 345, column: 21, scope: !846)
!849 = !DILocation(line: 345, column: 6, scope: !248)
!850 = !DILocation(line: 346, column: 11, scope: !846)
!851 = !DILocation(line: 346, column: 18, scope: !846)
!852 = !DILocation(line: 346, column: 26, scope: !846)
!853 = !DILocation(line: 346, column: 3, scope: !846)
!854 = !DILocation(line: 348, column: 10, scope: !846)
!855 = !DILocation(line: 348, column: 3, scope: !846)
!856 = !DILocation(line: 349, column: 1, scope: !248)
!857 = !DILocalVariable(name: "entry", arg: 1, scope: !249, file: !1, line: 352, type: !5)
!858 = !DILocation(line: 352, column: 46, scope: !249)
!859 = !DILocation(line: 354, column: 20, scope: !249)
!860 = !DILocation(line: 354, column: 27, scope: !249)
!861 = !DILocation(line: 354, column: 31, scope: !249)
!862 = !DILocation(line: 354, column: 18, scope: !249)
!863 = !DILocation(line: 354, column: 2, scope: !249)
!864 = !DILocalVariable(name: "entry", arg: 1, scope: !252, file: !1, line: 358, type: !5)
!865 = !DILocation(line: 358, column: 44, scope: !252)
!866 = !DILocalVariable(name: "set", arg: 2, scope: !252, file: !1, line: 359, type: !255)
!867 = !DILocation(line: 359, column: 20, scope: !252)
!868 = !DILocalVariable(name: "clear", arg: 3, scope: !252, file: !1, line: 359, type: !255)
!869 = !DILocation(line: 359, column: 40, scope: !252)
!870 = !DILocation(line: 361, column: 9, scope: !252)
!871 = !DILocation(line: 361, column: 16, scope: !252)
!872 = !DILocation(line: 361, column: 3, scope: !252)
!873 = !DILocation(line: 361, column: 7, scope: !252)
!874 = !DILocation(line: 362, column: 11, scope: !252)
!875 = !DILocation(line: 362, column: 18, scope: !252)
!876 = !DILocation(line: 362, column: 3, scope: !252)
!877 = !DILocation(line: 362, column: 9, scope: !252)
!878 = !DILocation(line: 363, column: 1, scope: !252)
!879 = !DILocalVariable(name: "entry", arg: 1, scope: !256, file: !1, line: 375, type: !5)
!880 = !DILocation(line: 375, column: 49, scope: !256)
!881 = !DILocalVariable(name: "f", scope: !256, file: !1, line: 377, type: !78)
!882 = !DILocation(line: 377, column: 14, scope: !256)
!883 = !DILocalVariable(name: "p", scope: !256, file: !1, line: 378, type: !93)
!884 = !DILocation(line: 378, column: 8, scope: !256)
!885 = !DILocation(line: 380, column: 30, scope: !886)
!886 = distinct !DILexicalBlock(scope: !256, file: !1, line: 380, column: 6)
!887 = !DILocation(line: 380, column: 37, scope: !886)
!888 = !DILocation(line: 381, column: 7, scope: !886)
!889 = !DILocation(line: 381, column: 14, scope: !886)
!890 = !DILocation(line: 380, column: 6, scope: !886)
!891 = !DILocation(line: 381, column: 34, scope: !886)
!892 = !DILocation(line: 380, column: 6, scope: !256)
!893 = !DILocation(line: 382, column: 7, scope: !894)
!894 = distinct !DILexicalBlock(scope: !895, file: !1, line: 382, column: 7)
!895 = distinct !DILexicalBlock(scope: !886, file: !1, line: 381, column: 40)
!896 = !DILocation(line: 382, column: 9, scope: !894)
!897 = !DILocation(line: 382, column: 7, scope: !895)
!898 = !DILocation(line: 383, column: 12, scope: !894)
!899 = !DILocation(line: 383, column: 4, scope: !894)
!900 = !DILocation(line: 384, column: 2, scope: !895)
!901 = !DILocation(line: 384, column: 13, scope: !902)
!902 = !DILexicalBlockFile(scope: !903, file: !1, discriminator: 1)
!903 = distinct !DILexicalBlock(scope: !886, file: !1, line: 384, column: 13)
!904 = !DILocation(line: 384, column: 19, scope: !902)
!905 = !DILocation(line: 385, column: 3, scope: !903)
!906 = !DILocation(line: 387, column: 6, scope: !907)
!907 = distinct !DILexicalBlock(scope: !256, file: !1, line: 387, column: 6)
!908 = !DILocation(line: 387, column: 13, scope: !907)
!909 = !DILocation(line: 387, column: 27, scope: !907)
!910 = !DILocation(line: 387, column: 33, scope: !907)
!911 = !DILocation(line: 387, column: 37, scope: !912)
!912 = !DILexicalBlockFile(scope: !907, file: !1, discriminator: 1)
!913 = !DILocation(line: 387, column: 44, scope: !912)
!914 = !DILocation(line: 387, column: 60, scope: !912)
!915 = !DILocation(line: 387, column: 6, scope: !912)
!916 = !DILocation(line: 388, column: 3, scope: !907)
!917 = !DILocation(line: 390, column: 21, scope: !256)
!918 = !DILocation(line: 390, column: 28, scope: !256)
!919 = !DILocation(line: 390, column: 43, scope: !256)
!920 = !DILocation(line: 390, column: 50, scope: !256)
!921 = !DILocation(line: 390, column: 6, scope: !256)
!922 = !DILocation(line: 390, column: 4, scope: !256)
!923 = !DILocation(line: 391, column: 6, scope: !924)
!924 = distinct !DILexicalBlock(scope: !256, file: !1, line: 391, column: 6)
!925 = !DILocation(line: 391, column: 8, scope: !924)
!926 = !DILocation(line: 391, column: 6, scope: !256)
!927 = !DILocation(line: 392, column: 3, scope: !924)
!928 = !DILocation(line: 394, column: 28, scope: !256)
!929 = !DILocation(line: 394, column: 35, scope: !256)
!930 = !DILocation(line: 394, column: 51, scope: !256)
!931 = !DILocation(line: 394, column: 2, scope: !256)
!932 = !DILocation(line: 395, column: 7, scope: !256)
!933 = !DILocation(line: 395, column: 2, scope: !256)
!934 = !DILocation(line: 396, column: 30, scope: !935)
!935 = distinct !DILexicalBlock(scope: !256, file: !1, line: 396, column: 6)
!936 = !DILocation(line: 396, column: 37, scope: !935)
!937 = !DILocation(line: 397, column: 7, scope: !935)
!938 = !DILocation(line: 397, column: 14, scope: !935)
!939 = !DILocation(line: 396, column: 6, scope: !935)
!940 = !DILocation(line: 397, column: 34, scope: !935)
!941 = !DILocation(line: 396, column: 6, scope: !256)
!942 = !DILocation(line: 398, column: 11, scope: !935)
!943 = !DILocation(line: 398, column: 3, scope: !935)
!944 = !DILocation(line: 399, column: 6, scope: !945)
!945 = distinct !DILexicalBlock(scope: !256, file: !1, line: 399, column: 6)
!946 = !DILocation(line: 399, column: 12, scope: !945)
!947 = !DILocation(line: 399, column: 6, scope: !256)
!948 = !DILocation(line: 400, column: 3, scope: !945)
!949 = !DILocation(line: 401, column: 2, scope: !256)
!950 = !DILocation(line: 402, column: 1, scope: !256)
!951 = !DILocalVariable(name: "bitset", arg: 1, scope: !462, file: !1, line: 1838, type: !45)
!952 = !DILocation(line: 1838, column: 30, scope: !462)
!953 = !DILocalVariable(name: "bitclear", arg: 2, scope: !462, file: !1, line: 1838, type: !45)
!954 = !DILocation(line: 1838, column: 52, scope: !462)
!955 = !DILocalVariable(name: "string", scope: !462, file: !1, line: 1840, type: !93)
!956 = !DILocation(line: 1840, column: 8, scope: !462)
!957 = !DILocalVariable(name: "dp", scope: !462, file: !1, line: 1840, type: !93)
!958 = !DILocation(line: 1840, column: 17, scope: !462)
!959 = !DILocalVariable(name: "sp", scope: !462, file: !1, line: 1841, type: !78)
!960 = !DILocation(line: 1841, column: 14, scope: !462)
!961 = !DILocalVariable(name: "bits", scope: !462, file: !1, line: 1842, type: !45)
!962 = !DILocation(line: 1842, column: 16, scope: !462)
!963 = !DILocalVariable(name: "flag", scope: !462, file: !1, line: 1843, type: !964)
!964 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !474, size: 64, align: 64)
!965 = !DILocation(line: 1843, column: 15, scope: !462)
!966 = !DILocalVariable(name: "length", scope: !462, file: !1, line: 1844, type: !43)
!967 = !DILocation(line: 1844, column: 9, scope: !462)
!968 = !DILocation(line: 1846, column: 9, scope: !462)
!969 = !DILocation(line: 1846, column: 18, scope: !462)
!970 = !DILocation(line: 1846, column: 16, scope: !462)
!971 = !DILocation(line: 1846, column: 7, scope: !462)
!972 = !DILocation(line: 1847, column: 9, scope: !462)
!973 = !DILocation(line: 1848, column: 12, scope: !974)
!974 = distinct !DILexicalBlock(scope: !462, file: !1, line: 1848, column: 2)
!975 = !DILocation(line: 1848, column: 7, scope: !974)
!976 = !DILocation(line: 1848, column: 21, scope: !977)
!977 = !DILexicalBlockFile(scope: !978, file: !1, discriminator: 1)
!978 = distinct !DILexicalBlock(scope: !974, file: !1, line: 1848, column: 2)
!979 = !DILocation(line: 1848, column: 27, scope: !977)
!980 = !DILocation(line: 1848, column: 32, scope: !977)
!981 = !DILocation(line: 1848, column: 2, scope: !977)
!982 = !DILocation(line: 1849, column: 7, scope: !983)
!983 = distinct !DILexicalBlock(scope: !978, file: !1, line: 1849, column: 7)
!984 = !DILocation(line: 1849, column: 15, scope: !983)
!985 = !DILocation(line: 1849, column: 21, scope: !983)
!986 = !DILocation(line: 1849, column: 27, scope: !983)
!987 = !DILocation(line: 1849, column: 33, scope: !983)
!988 = !DILocation(line: 1849, column: 25, scope: !983)
!989 = !DILocation(line: 1849, column: 12, scope: !983)
!990 = !DILocation(line: 1849, column: 7, scope: !978)
!991 = !DILocation(line: 1850, column: 21, scope: !992)
!992 = distinct !DILexicalBlock(scope: !983, file: !1, line: 1849, column: 41)
!993 = !DILocation(line: 1850, column: 27, scope: !992)
!994 = !DILocation(line: 1850, column: 14, scope: !992)
!995 = !DILocation(line: 1850, column: 33, scope: !992)
!996 = !DILocation(line: 1850, column: 11, scope: !992)
!997 = !DILocation(line: 1851, column: 14, scope: !992)
!998 = !DILocation(line: 1851, column: 20, scope: !992)
!999 = !DILocation(line: 1851, column: 26, scope: !992)
!1000 = !DILocation(line: 1851, column: 32, scope: !992)
!1001 = !DILocation(line: 1851, column: 24, scope: !992)
!1002 = !DILocation(line: 1851, column: 12, scope: !992)
!1003 = !DILocation(line: 1851, column: 9, scope: !992)
!1004 = !DILocation(line: 1852, column: 3, scope: !992)
!1005 = !DILocation(line: 1849, column: 38, scope: !1006)
!1006 = !DILexicalBlockFile(scope: !983, file: !1, discriminator: 1)
!1007 = !DILocation(line: 1848, column: 45, scope: !1008)
!1008 = !DILexicalBlockFile(scope: !978, file: !1, discriminator: 2)
!1009 = !DILocation(line: 1848, column: 2, scope: !1008)
!1010 = !DILocation(line: 1854, column: 6, scope: !1011)
!1011 = distinct !DILexicalBlock(scope: !462, file: !1, line: 1854, column: 6)
!1012 = !DILocation(line: 1854, column: 13, scope: !1011)
!1013 = !DILocation(line: 1854, column: 6, scope: !462)
!1014 = !DILocation(line: 1855, column: 3, scope: !1011)
!1015 = !DILocation(line: 1856, column: 26, scope: !462)
!1016 = !DILocation(line: 1856, column: 19, scope: !462)
!1017 = !DILocation(line: 1856, column: 9, scope: !462)
!1018 = !DILocation(line: 1857, column: 6, scope: !1019)
!1019 = distinct !DILexicalBlock(scope: !462, file: !1, line: 1857, column: 6)
!1020 = !DILocation(line: 1857, column: 13, scope: !1019)
!1021 = !DILocation(line: 1857, column: 6, scope: !462)
!1022 = !DILocation(line: 1858, column: 3, scope: !1019)
!1023 = !DILocation(line: 1860, column: 7, scope: !462)
!1024 = !DILocation(line: 1860, column: 5, scope: !462)
!1025 = !DILocation(line: 1861, column: 12, scope: !1026)
!1026 = distinct !DILexicalBlock(scope: !462, file: !1, line: 1861, column: 2)
!1027 = !DILocation(line: 1861, column: 7, scope: !1026)
!1028 = !DILocation(line: 1861, column: 21, scope: !1029)
!1029 = !DILexicalBlockFile(scope: !1030, file: !1, discriminator: 1)
!1030 = distinct !DILexicalBlock(scope: !1026, file: !1, line: 1861, column: 2)
!1031 = !DILocation(line: 1861, column: 27, scope: !1029)
!1032 = !DILocation(line: 1861, column: 32, scope: !1029)
!1033 = !DILocation(line: 1861, column: 2, scope: !1029)
!1034 = !DILocation(line: 1862, column: 7, scope: !1035)
!1035 = distinct !DILexicalBlock(scope: !1036, file: !1, line: 1862, column: 7)
!1036 = distinct !DILexicalBlock(scope: !1030, file: !1, line: 1861, column: 49)
!1037 = !DILocation(line: 1862, column: 16, scope: !1035)
!1038 = !DILocation(line: 1862, column: 22, scope: !1035)
!1039 = !DILocation(line: 1862, column: 14, scope: !1035)
!1040 = !DILocation(line: 1862, column: 26, scope: !1035)
!1041 = !DILocation(line: 1862, column: 29, scope: !1042)
!1042 = !DILexicalBlockFile(scope: !1035, file: !1, discriminator: 1)
!1043 = !DILocation(line: 1862, column: 40, scope: !1042)
!1044 = !DILocation(line: 1862, column: 46, scope: !1042)
!1045 = !DILocation(line: 1862, column: 38, scope: !1042)
!1046 = !DILocation(line: 1862, column: 7, scope: !1042)
!1047 = !DILocation(line: 1863, column: 9, scope: !1048)
!1048 = distinct !DILexicalBlock(scope: !1035, file: !1, line: 1862, column: 53)
!1049 = !DILocation(line: 1863, column: 15, scope: !1048)
!1050 = !DILocation(line: 1863, column: 20, scope: !1048)
!1051 = !DILocation(line: 1863, column: 7, scope: !1048)
!1052 = !DILocation(line: 1864, column: 3, scope: !1048)
!1053 = !DILocation(line: 1864, column: 14, scope: !1054)
!1054 = !DILexicalBlockFile(scope: !1055, file: !1, discriminator: 1)
!1055 = distinct !DILexicalBlock(scope: !1035, file: !1, line: 1864, column: 14)
!1056 = !DILocation(line: 1864, column: 23, scope: !1054)
!1057 = !DILocation(line: 1864, column: 29, scope: !1054)
!1058 = !DILocation(line: 1864, column: 21, scope: !1054)
!1059 = !DILocation(line: 1864, column: 36, scope: !1054)
!1060 = !DILocation(line: 1864, column: 40, scope: !1061)
!1061 = !DILexicalBlockFile(scope: !1055, file: !1, discriminator: 2)
!1062 = !DILocation(line: 1864, column: 51, scope: !1061)
!1063 = !DILocation(line: 1864, column: 57, scope: !1061)
!1064 = !DILocation(line: 1864, column: 49, scope: !1061)
!1065 = !DILocation(line: 1864, column: 14, scope: !1061)
!1066 = !DILocation(line: 1865, column: 9, scope: !1067)
!1067 = distinct !DILexicalBlock(scope: !1055, file: !1, line: 1864, column: 62)
!1068 = !DILocation(line: 1865, column: 15, scope: !1067)
!1069 = !DILocation(line: 1865, column: 7, scope: !1067)
!1070 = !DILocation(line: 1866, column: 3, scope: !1067)
!1071 = !DILocation(line: 1867, column: 4, scope: !1055)
!1072 = !DILocation(line: 1868, column: 15, scope: !1036)
!1073 = !DILocation(line: 1868, column: 21, scope: !1036)
!1074 = !DILocation(line: 1868, column: 27, scope: !1036)
!1075 = !DILocation(line: 1868, column: 33, scope: !1036)
!1076 = !DILocation(line: 1868, column: 25, scope: !1036)
!1077 = !DILocation(line: 1868, column: 13, scope: !1036)
!1078 = !DILocation(line: 1868, column: 10, scope: !1036)
!1079 = !DILocation(line: 1869, column: 17, scope: !1036)
!1080 = !DILocation(line: 1869, column: 23, scope: !1036)
!1081 = !DILocation(line: 1869, column: 29, scope: !1036)
!1082 = !DILocation(line: 1869, column: 35, scope: !1036)
!1083 = !DILocation(line: 1869, column: 27, scope: !1036)
!1084 = !DILocation(line: 1869, column: 15, scope: !1036)
!1085 = !DILocation(line: 1869, column: 12, scope: !1036)
!1086 = !DILocation(line: 1870, column: 7, scope: !1087)
!1087 = distinct !DILexicalBlock(scope: !1036, file: !1, line: 1870, column: 7)
!1088 = !DILocation(line: 1870, column: 12, scope: !1087)
!1089 = !DILocation(line: 1870, column: 10, scope: !1087)
!1090 = !DILocation(line: 1870, column: 7, scope: !1036)
!1091 = !DILocation(line: 1871, column: 7, scope: !1087)
!1092 = !DILocation(line: 1871, column: 10, scope: !1087)
!1093 = !DILocation(line: 1871, column: 4, scope: !1087)
!1094 = !DILocation(line: 1872, column: 3, scope: !1036)
!1095 = !DILocation(line: 1872, column: 22, scope: !1096)
!1096 = !DILexicalBlockFile(scope: !1036, file: !1, discriminator: 1)
!1097 = !DILocation(line: 1872, column: 19, scope: !1096)
!1098 = !DILocation(line: 1872, column: 14, scope: !1096)
!1099 = !DILocation(line: 1872, column: 17, scope: !1096)
!1100 = !DILocation(line: 1872, column: 10, scope: !1096)
!1101 = !DILocation(line: 1872, column: 26, scope: !1096)
!1102 = !DILocation(line: 1872, column: 3, scope: !1096)
!1103 = !DILocation(line: 1872, column: 3, scope: !1104)
!1104 = !DILexicalBlockFile(scope: !1036, file: !1, discriminator: 2)
!1105 = !DILocation(line: 1874, column: 5, scope: !1036)
!1106 = !DILocation(line: 1875, column: 2, scope: !1036)
!1107 = !DILocation(line: 1861, column: 45, scope: !1108)
!1108 = !DILexicalBlockFile(scope: !1030, file: !1, discriminator: 2)
!1109 = !DILocation(line: 1861, column: 2, scope: !1108)
!1110 = !DILocation(line: 1877, column: 3, scope: !462)
!1111 = !DILocation(line: 1877, column: 6, scope: !462)
!1112 = !DILocation(line: 1878, column: 10, scope: !462)
!1113 = !DILocation(line: 1878, column: 2, scope: !462)
!1114 = !DILocation(line: 1879, column: 1, scope: !462)
!1115 = !DILocalVariable(name: "entry", arg: 1, scope: !259, file: !1, line: 405, type: !5)
!1116 = !DILocation(line: 405, column: 41, scope: !259)
!1117 = !DILocation(line: 407, column: 10, scope: !259)
!1118 = !DILocation(line: 407, column: 17, scope: !259)
!1119 = !DILocation(line: 407, column: 25, scope: !259)
!1120 = !DILocation(line: 407, column: 2, scope: !259)
!1121 = !DILocalVariable(name: "entry", arg: 1, scope: !264, file: !1, line: 411, type: !5)
!1122 = !DILocation(line: 411, column: 43, scope: !264)
!1123 = !DILocalVariable(name: "p", scope: !264, file: !1, line: 413, type: !78)
!1124 = !DILocation(line: 413, column: 14, scope: !264)
!1125 = !DILocation(line: 414, column: 30, scope: !1126)
!1126 = distinct !DILexicalBlock(scope: !264, file: !1, line: 414, column: 6)
!1127 = !DILocation(line: 414, column: 37, scope: !1126)
!1128 = !DILocation(line: 414, column: 47, scope: !1126)
!1129 = !DILocation(line: 414, column: 54, scope: !1126)
!1130 = !DILocation(line: 414, column: 6, scope: !1126)
!1131 = !DILocation(line: 414, column: 68, scope: !1126)
!1132 = !DILocation(line: 414, column: 6, scope: !264)
!1133 = !DILocation(line: 415, column: 11, scope: !1126)
!1134 = !DILocation(line: 415, column: 3, scope: !1126)
!1135 = !DILocation(line: 416, column: 6, scope: !1136)
!1136 = distinct !DILexicalBlock(scope: !264, file: !1, line: 416, column: 6)
!1137 = !DILocation(line: 416, column: 12, scope: !1136)
!1138 = !DILocation(line: 416, column: 6, scope: !264)
!1139 = !DILocation(line: 417, column: 3, scope: !1136)
!1140 = !DILocation(line: 418, column: 2, scope: !264)
!1141 = !DILocation(line: 419, column: 1, scope: !264)
!1142 = !DILocalVariable(name: "entry", arg: 1, scope: !265, file: !1, line: 422, type: !5)
!1143 = !DILocation(line: 422, column: 48, scope: !265)
!1144 = !DILocalVariable(name: "p", scope: !265, file: !1, line: 424, type: !78)
!1145 = !DILocation(line: 424, column: 14, scope: !265)
!1146 = !DILocation(line: 425, column: 31, scope: !1147)
!1147 = distinct !DILexicalBlock(scope: !265, file: !1, line: 425, column: 6)
!1148 = !DILocation(line: 425, column: 38, scope: !1147)
!1149 = !DILocation(line: 425, column: 48, scope: !1147)
!1150 = !DILocation(line: 425, column: 55, scope: !1147)
!1151 = !DILocation(line: 425, column: 6, scope: !1147)
!1152 = !DILocation(line: 425, column: 69, scope: !1147)
!1153 = !DILocation(line: 425, column: 6, scope: !265)
!1154 = !DILocation(line: 426, column: 11, scope: !1147)
!1155 = !DILocation(line: 426, column: 3, scope: !1147)
!1156 = !DILocation(line: 427, column: 6, scope: !1157)
!1157 = distinct !DILexicalBlock(scope: !265, file: !1, line: 427, column: 6)
!1158 = !DILocation(line: 427, column: 12, scope: !1157)
!1159 = !DILocation(line: 427, column: 6, scope: !265)
!1160 = !DILocation(line: 428, column: 3, scope: !1157)
!1161 = !DILocation(line: 429, column: 2, scope: !265)
!1162 = !DILocation(line: 430, column: 1, scope: !265)
!1163 = !DILocalVariable(name: "entry", arg: 1, scope: !266, file: !1, line: 434, type: !5)
!1164 = !DILocation(line: 434, column: 45, scope: !266)
!1165 = !DILocalVariable(name: "p", scope: !266, file: !1, line: 436, type: !269)
!1166 = !DILocation(line: 436, column: 17, scope: !266)
!1167 = !DILocation(line: 437, column: 30, scope: !1168)
!1168 = distinct !DILexicalBlock(scope: !266, file: !1, line: 437, column: 6)
!1169 = !DILocation(line: 437, column: 37, scope: !1168)
!1170 = !DILocation(line: 437, column: 47, scope: !1168)
!1171 = !DILocation(line: 437, column: 54, scope: !1168)
!1172 = !DILocation(line: 437, column: 6, scope: !1168)
!1173 = !DILocation(line: 437, column: 68, scope: !1168)
!1174 = !DILocation(line: 437, column: 6, scope: !266)
!1175 = !DILocation(line: 438, column: 11, scope: !1168)
!1176 = !DILocation(line: 438, column: 3, scope: !1168)
!1177 = !DILocation(line: 439, column: 6, scope: !1178)
!1178 = distinct !DILexicalBlock(scope: !266, file: !1, line: 439, column: 6)
!1179 = !DILocation(line: 439, column: 12, scope: !1178)
!1180 = !DILocation(line: 439, column: 6, scope: !266)
!1181 = !DILocation(line: 440, column: 3, scope: !1178)
!1182 = !DILocation(line: 441, column: 2, scope: !266)
!1183 = !DILocation(line: 442, column: 1, scope: !266)
!1184 = !DILocalVariable(name: "entry", arg: 1, scope: !271, file: !1, line: 445, type: !5)
!1185 = !DILocation(line: 445, column: 46, scope: !271)
!1186 = !DILocalVariable(name: "p", arg: 2, scope: !271, file: !1, line: 446, type: !274)
!1187 = !DILocation(line: 446, column: 18, scope: !271)
!1188 = !DILocalVariable(name: "len", arg: 3, scope: !271, file: !1, line: 446, type: !63)
!1189 = !DILocation(line: 446, column: 29, scope: !271)
!1190 = !DILocalVariable(name: "sc", arg: 4, scope: !271, file: !1, line: 446, type: !100)
!1191 = !DILocation(line: 446, column: 62, scope: !271)
!1192 = !DILocation(line: 448, column: 37, scope: !271)
!1193 = !DILocation(line: 448, column: 44, scope: !271)
!1194 = !DILocation(line: 448, column: 54, scope: !271)
!1195 = !DILocation(line: 448, column: 57, scope: !271)
!1196 = !DILocation(line: 448, column: 62, scope: !271)
!1197 = !DILocation(line: 448, column: 10, scope: !271)
!1198 = !DILocation(line: 448, column: 2, scope: !271)
!1199 = !DILocalVariable(name: "entry", arg: 1, scope: !275, file: !1, line: 452, type: !5)
!1200 = !DILocation(line: 452, column: 46, scope: !275)
!1201 = !DILocalVariable(name: "p", scope: !275, file: !1, line: 454, type: !78)
!1202 = !DILocation(line: 454, column: 14, scope: !275)
!1203 = !DILocation(line: 455, column: 7, scope: !1204)
!1204 = distinct !DILexicalBlock(scope: !275, file: !1, line: 455, column: 6)
!1205 = !DILocation(line: 455, column: 14, scope: !1204)
!1206 = !DILocation(line: 455, column: 21, scope: !1204)
!1207 = !DILocation(line: 455, column: 40, scope: !1204)
!1208 = !DILocation(line: 455, column: 6, scope: !275)
!1209 = !DILocation(line: 456, column: 3, scope: !1204)
!1210 = !DILocation(line: 458, column: 6, scope: !1211)
!1211 = distinct !DILexicalBlock(scope: !275, file: !1, line: 457, column: 6)
!1212 = !DILocation(line: 458, column: 13, scope: !1211)
!1213 = !DILocation(line: 458, column: 23, scope: !1211)
!1214 = !DILocation(line: 458, column: 30, scope: !1211)
!1215 = !DILocation(line: 457, column: 6, scope: !1211)
!1216 = !DILocation(line: 458, column: 47, scope: !1211)
!1217 = !DILocation(line: 457, column: 6, scope: !275)
!1218 = !DILocation(line: 459, column: 11, scope: !1211)
!1219 = !DILocation(line: 459, column: 3, scope: !1211)
!1220 = !DILocation(line: 460, column: 6, scope: !1221)
!1221 = distinct !DILexicalBlock(scope: !275, file: !1, line: 460, column: 6)
!1222 = !DILocation(line: 460, column: 12, scope: !1221)
!1223 = !DILocation(line: 460, column: 6, scope: !275)
!1224 = !DILocation(line: 461, column: 3, scope: !1221)
!1225 = !DILocation(line: 462, column: 2, scope: !275)
!1226 = !DILocation(line: 463, column: 1, scope: !275)
!1227 = !DILocalVariable(name: "entry", arg: 1, scope: !276, file: !1, line: 466, type: !5)
!1228 = !DILocation(line: 466, column: 51, scope: !276)
!1229 = !DILocalVariable(name: "p", scope: !276, file: !1, line: 468, type: !78)
!1230 = !DILocation(line: 468, column: 14, scope: !276)
!1231 = !DILocation(line: 469, column: 7, scope: !1232)
!1232 = distinct !DILexicalBlock(scope: !276, file: !1, line: 469, column: 6)
!1233 = !DILocation(line: 469, column: 14, scope: !1232)
!1234 = !DILocation(line: 469, column: 21, scope: !1232)
!1235 = !DILocation(line: 469, column: 40, scope: !1232)
!1236 = !DILocation(line: 469, column: 6, scope: !276)
!1237 = !DILocation(line: 470, column: 3, scope: !1232)
!1238 = !DILocation(line: 472, column: 6, scope: !1239)
!1239 = distinct !DILexicalBlock(scope: !276, file: !1, line: 471, column: 6)
!1240 = !DILocation(line: 472, column: 13, scope: !1239)
!1241 = !DILocation(line: 472, column: 23, scope: !1239)
!1242 = !DILocation(line: 472, column: 30, scope: !1239)
!1243 = !DILocation(line: 471, column: 6, scope: !1239)
!1244 = !DILocation(line: 472, column: 47, scope: !1239)
!1245 = !DILocation(line: 471, column: 6, scope: !276)
!1246 = !DILocation(line: 473, column: 11, scope: !1239)
!1247 = !DILocation(line: 473, column: 3, scope: !1239)
!1248 = !DILocation(line: 474, column: 6, scope: !1249)
!1249 = distinct !DILexicalBlock(scope: !276, file: !1, line: 474, column: 6)
!1250 = !DILocation(line: 474, column: 12, scope: !1249)
!1251 = !DILocation(line: 474, column: 6, scope: !276)
!1252 = !DILocation(line: 475, column: 3, scope: !1249)
!1253 = !DILocation(line: 476, column: 2, scope: !276)
!1254 = !DILocation(line: 477, column: 1, scope: !276)
!1255 = !DILocalVariable(name: "entry", arg: 1, scope: !277, file: !1, line: 480, type: !5)
!1256 = !DILocation(line: 480, column: 48, scope: !277)
!1257 = !DILocalVariable(name: "p", scope: !277, file: !1, line: 482, type: !269)
!1258 = !DILocation(line: 482, column: 17, scope: !277)
!1259 = !DILocation(line: 483, column: 7, scope: !1260)
!1260 = distinct !DILexicalBlock(scope: !277, file: !1, line: 483, column: 6)
!1261 = !DILocation(line: 483, column: 14, scope: !1260)
!1262 = !DILocation(line: 483, column: 21, scope: !1260)
!1263 = !DILocation(line: 483, column: 40, scope: !1260)
!1264 = !DILocation(line: 483, column: 6, scope: !277)
!1265 = !DILocation(line: 484, column: 3, scope: !1260)
!1266 = !DILocation(line: 486, column: 6, scope: !1267)
!1267 = distinct !DILexicalBlock(scope: !277, file: !1, line: 485, column: 6)
!1268 = !DILocation(line: 486, column: 13, scope: !1267)
!1269 = !DILocation(line: 486, column: 23, scope: !1267)
!1270 = !DILocation(line: 486, column: 30, scope: !1267)
!1271 = !DILocation(line: 485, column: 6, scope: !1267)
!1272 = !DILocation(line: 486, column: 47, scope: !1267)
!1273 = !DILocation(line: 485, column: 6, scope: !277)
!1274 = !DILocation(line: 487, column: 11, scope: !1267)
!1275 = !DILocation(line: 487, column: 3, scope: !1267)
!1276 = !DILocation(line: 488, column: 6, scope: !1277)
!1277 = distinct !DILexicalBlock(scope: !277, file: !1, line: 488, column: 6)
!1278 = !DILocation(line: 488, column: 12, scope: !1277)
!1279 = !DILocation(line: 488, column: 6, scope: !277)
!1280 = !DILocation(line: 489, column: 3, scope: !1277)
!1281 = !DILocation(line: 490, column: 2, scope: !277)
!1282 = !DILocation(line: 491, column: 1, scope: !277)
!1283 = !DILocalVariable(name: "entry", arg: 1, scope: !278, file: !1, line: 494, type: !5)
!1284 = !DILocation(line: 494, column: 49, scope: !278)
!1285 = !DILocalVariable(name: "p", arg: 2, scope: !278, file: !1, line: 495, type: !274)
!1286 = !DILocation(line: 495, column: 18, scope: !278)
!1287 = !DILocalVariable(name: "len", arg: 3, scope: !278, file: !1, line: 495, type: !63)
!1288 = !DILocation(line: 495, column: 29, scope: !278)
!1289 = !DILocalVariable(name: "sc", arg: 4, scope: !278, file: !1, line: 495, type: !100)
!1290 = !DILocation(line: 495, column: 62, scope: !278)
!1291 = !DILocation(line: 497, column: 7, scope: !1292)
!1292 = distinct !DILexicalBlock(scope: !278, file: !1, line: 497, column: 6)
!1293 = !DILocation(line: 497, column: 14, scope: !1292)
!1294 = !DILocation(line: 497, column: 21, scope: !1292)
!1295 = !DILocation(line: 497, column: 40, scope: !1292)
!1296 = !DILocation(line: 497, column: 6, scope: !278)
!1297 = !DILocation(line: 498, column: 4, scope: !1298)
!1298 = distinct !DILexicalBlock(scope: !1292, file: !1, line: 497, column: 46)
!1299 = !DILocation(line: 498, column: 6, scope: !1298)
!1300 = !DILocation(line: 499, column: 4, scope: !1298)
!1301 = !DILocation(line: 499, column: 8, scope: !1298)
!1302 = !DILocation(line: 500, column: 3, scope: !1298)
!1303 = !DILocation(line: 502, column: 37, scope: !278)
!1304 = !DILocation(line: 502, column: 44, scope: !278)
!1305 = !DILocation(line: 502, column: 57, scope: !278)
!1306 = !DILocation(line: 502, column: 60, scope: !278)
!1307 = !DILocation(line: 502, column: 65, scope: !278)
!1308 = !DILocation(line: 502, column: 10, scope: !278)
!1309 = !DILocation(line: 502, column: 2, scope: !278)
!1310 = !DILocation(line: 503, column: 1, scope: !278)
!1311 = !DILocalVariable(name: "entry", arg: 1, scope: !279, file: !1, line: 506, type: !5)
!1312 = !DILocation(line: 506, column: 41, scope: !279)
!1313 = !DILocation(line: 508, column: 10, scope: !279)
!1314 = !DILocation(line: 508, column: 17, scope: !279)
!1315 = !DILocation(line: 508, column: 25, scope: !279)
!1316 = !DILocation(line: 508, column: 2, scope: !279)
!1317 = !DILocalVariable(name: "entry", arg: 1, scope: !280, file: !1, line: 512, type: !5)
!1318 = !DILocation(line: 512, column: 48, scope: !280)
!1319 = !DILocation(line: 514, column: 10, scope: !280)
!1320 = !DILocation(line: 514, column: 17, scope: !280)
!1321 = !DILocation(line: 514, column: 24, scope: !280)
!1322 = !DILocation(line: 514, column: 2, scope: !280)
!1323 = !DILocalVariable(name: "entry", arg: 1, scope: !281, file: !1, line: 518, type: !5)
!1324 = !DILocation(line: 518, column: 43, scope: !281)
!1325 = !DILocation(line: 520, column: 10, scope: !281)
!1326 = !DILocation(line: 520, column: 17, scope: !281)
!1327 = !DILocation(line: 520, column: 25, scope: !281)
!1328 = !DILocation(line: 520, column: 2, scope: !281)
!1329 = !DILocalVariable(name: "entry", arg: 1, scope: !282, file: !1, line: 524, type: !5)
!1330 = !DILocation(line: 524, column: 42, scope: !282)
!1331 = !DILocation(line: 526, column: 10, scope: !282)
!1332 = !DILocation(line: 526, column: 17, scope: !282)
!1333 = !DILocation(line: 526, column: 21, scope: !282)
!1334 = !DILocation(line: 526, column: 2, scope: !282)
!1335 = !DILocalVariable(name: "entry", arg: 1, scope: !283, file: !1, line: 530, type: !5)
!1336 = !DILocation(line: 530, column: 43, scope: !283)
!1337 = !DILocation(line: 532, column: 10, scope: !283)
!1338 = !DILocation(line: 532, column: 17, scope: !283)
!1339 = !DILocation(line: 532, column: 25, scope: !283)
!1340 = !DILocation(line: 532, column: 2, scope: !283)
!1341 = !DILocalVariable(name: "entry", arg: 1, scope: !284, file: !1, line: 536, type: !5)
!1342 = !DILocation(line: 536, column: 48, scope: !284)
!1343 = !DILocation(line: 538, column: 10, scope: !284)
!1344 = !DILocation(line: 538, column: 17, scope: !284)
!1345 = !DILocation(line: 538, column: 25, scope: !284)
!1346 = !DILocation(line: 538, column: 9, scope: !284)
!1347 = !DILocation(line: 538, column: 2, scope: !284)
!1348 = !DILocalVariable(name: "entry", arg: 1, scope: !285, file: !1, line: 542, type: !5)
!1349 = !DILocation(line: 542, column: 50, scope: !285)
!1350 = !DILocation(line: 544, column: 10, scope: !285)
!1351 = !DILocation(line: 544, column: 17, scope: !285)
!1352 = !DILocation(line: 544, column: 24, scope: !285)
!1353 = !DILocation(line: 544, column: 2, scope: !285)
!1354 = !DILocalVariable(name: "entry", arg: 1, scope: !286, file: !1, line: 548, type: !5)
!1355 = !DILocation(line: 548, column: 43, scope: !286)
!1356 = !DILocation(line: 550, column: 10, scope: !286)
!1357 = !DILocation(line: 550, column: 17, scope: !286)
!1358 = !DILocation(line: 550, column: 25, scope: !286)
!1359 = !DILocation(line: 550, column: 2, scope: !286)
!1360 = !DILocalVariable(name: "entry", arg: 1, scope: !289, file: !1, line: 554, type: !5)
!1361 = !DILocation(line: 554, column: 46, scope: !289)
!1362 = !DILocalVariable(name: "p", scope: !289, file: !1, line: 556, type: !78)
!1363 = !DILocation(line: 556, column: 14, scope: !289)
!1364 = !DILocation(line: 558, column: 6, scope: !1365)
!1365 = distinct !DILexicalBlock(scope: !289, file: !1, line: 557, column: 6)
!1366 = !DILocation(line: 558, column: 13, scope: !1365)
!1367 = !DILocation(line: 558, column: 23, scope: !1365)
!1368 = !DILocation(line: 558, column: 30, scope: !1365)
!1369 = !DILocation(line: 557, column: 6, scope: !1365)
!1370 = !DILocation(line: 558, column: 47, scope: !1365)
!1371 = !DILocation(line: 557, column: 6, scope: !289)
!1372 = !DILocation(line: 559, column: 11, scope: !1365)
!1373 = !DILocation(line: 559, column: 3, scope: !1365)
!1374 = !DILocation(line: 560, column: 6, scope: !1375)
!1375 = distinct !DILexicalBlock(scope: !289, file: !1, line: 560, column: 6)
!1376 = !DILocation(line: 560, column: 12, scope: !1375)
!1377 = !DILocation(line: 560, column: 6, scope: !289)
!1378 = !DILocation(line: 561, column: 3, scope: !1375)
!1379 = !DILocation(line: 562, column: 2, scope: !289)
!1380 = !DILocation(line: 563, column: 1, scope: !289)
!1381 = !DILocalVariable(name: "entry", arg: 1, scope: !290, file: !1, line: 566, type: !5)
!1382 = !DILocation(line: 566, column: 51, scope: !290)
!1383 = !DILocalVariable(name: "p", scope: !290, file: !1, line: 568, type: !78)
!1384 = !DILocation(line: 568, column: 14, scope: !290)
!1385 = !DILocation(line: 570, column: 6, scope: !1386)
!1386 = distinct !DILexicalBlock(scope: !290, file: !1, line: 569, column: 6)
!1387 = !DILocation(line: 570, column: 13, scope: !1386)
!1388 = !DILocation(line: 570, column: 23, scope: !1386)
!1389 = !DILocation(line: 570, column: 30, scope: !1386)
!1390 = !DILocation(line: 569, column: 6, scope: !1386)
!1391 = !DILocation(line: 570, column: 47, scope: !1386)
!1392 = !DILocation(line: 569, column: 6, scope: !290)
!1393 = !DILocation(line: 571, column: 11, scope: !1386)
!1394 = !DILocation(line: 571, column: 3, scope: !1386)
!1395 = !DILocation(line: 572, column: 6, scope: !1396)
!1396 = distinct !DILexicalBlock(scope: !290, file: !1, line: 572, column: 6)
!1397 = !DILocation(line: 572, column: 12, scope: !1396)
!1398 = !DILocation(line: 572, column: 6, scope: !290)
!1399 = !DILocation(line: 573, column: 3, scope: !1396)
!1400 = !DILocation(line: 574, column: 2, scope: !290)
!1401 = !DILocation(line: 575, column: 1, scope: !290)
!1402 = !DILocalVariable(name: "entry", arg: 1, scope: !291, file: !1, line: 578, type: !5)
!1403 = !DILocation(line: 578, column: 48, scope: !291)
!1404 = !DILocalVariable(name: "p", scope: !291, file: !1, line: 580, type: !269)
!1405 = !DILocation(line: 580, column: 17, scope: !291)
!1406 = !DILocation(line: 582, column: 6, scope: !1407)
!1407 = distinct !DILexicalBlock(scope: !291, file: !1, line: 581, column: 6)
!1408 = !DILocation(line: 582, column: 13, scope: !1407)
!1409 = !DILocation(line: 582, column: 23, scope: !1407)
!1410 = !DILocation(line: 582, column: 30, scope: !1407)
!1411 = !DILocation(line: 581, column: 6, scope: !1407)
!1412 = !DILocation(line: 582, column: 47, scope: !1407)
!1413 = !DILocation(line: 581, column: 6, scope: !291)
!1414 = !DILocation(line: 583, column: 11, scope: !1407)
!1415 = !DILocation(line: 583, column: 3, scope: !1407)
!1416 = !DILocation(line: 584, column: 6, scope: !1417)
!1417 = distinct !DILexicalBlock(scope: !291, file: !1, line: 584, column: 6)
!1418 = !DILocation(line: 584, column: 12, scope: !1417)
!1419 = !DILocation(line: 584, column: 6, scope: !291)
!1420 = !DILocation(line: 585, column: 3, scope: !1417)
!1421 = !DILocation(line: 586, column: 2, scope: !291)
!1422 = !DILocation(line: 587, column: 1, scope: !291)
!1423 = !DILocalVariable(name: "entry", arg: 1, scope: !292, file: !1, line: 590, type: !5)
!1424 = !DILocation(line: 590, column: 49, scope: !292)
!1425 = !DILocalVariable(name: "p", arg: 2, scope: !292, file: !1, line: 591, type: !274)
!1426 = !DILocation(line: 591, column: 18, scope: !292)
!1427 = !DILocalVariable(name: "len", arg: 3, scope: !292, file: !1, line: 591, type: !63)
!1428 = !DILocation(line: 591, column: 29, scope: !292)
!1429 = !DILocalVariable(name: "sc", arg: 4, scope: !292, file: !1, line: 591, type: !100)
!1430 = !DILocation(line: 591, column: 62, scope: !292)
!1431 = !DILocation(line: 593, column: 37, scope: !292)
!1432 = !DILocation(line: 593, column: 44, scope: !292)
!1433 = !DILocation(line: 593, column: 57, scope: !292)
!1434 = !DILocation(line: 593, column: 60, scope: !292)
!1435 = !DILocation(line: 593, column: 65, scope: !292)
!1436 = !DILocation(line: 593, column: 10, scope: !292)
!1437 = !DILocation(line: 593, column: 2, scope: !292)
!1438 = !DILocalVariable(name: "entry", arg: 1, scope: !293, file: !1, line: 597, type: !5)
!1439 = !DILocation(line: 597, column: 42, scope: !293)
!1440 = !DILocation(line: 599, column: 21, scope: !293)
!1441 = !DILocation(line: 599, column: 28, scope: !293)
!1442 = !DILocation(line: 599, column: 32, scope: !293)
!1443 = !DILocation(line: 599, column: 19, scope: !293)
!1444 = !DILocation(line: 599, column: 2, scope: !293)
!1445 = !DILocalVariable(name: "entry", arg: 1, scope: !294, file: !1, line: 603, type: !5)
!1446 = !DILocation(line: 603, column: 42, scope: !294)
!1447 = !DILocation(line: 605, column: 6, scope: !1448)
!1448 = distinct !DILexicalBlock(scope: !294, file: !1, line: 605, column: 6)
!1449 = !DILocation(line: 605, column: 13, scope: !1448)
!1450 = !DILocation(line: 605, column: 21, scope: !1448)
!1451 = !DILocation(line: 605, column: 6, scope: !294)
!1452 = !DILocation(line: 606, column: 10, scope: !1448)
!1453 = !DILocation(line: 606, column: 3, scope: !1448)
!1454 = !DILocation(line: 609, column: 11, scope: !1448)
!1455 = !DILocation(line: 609, column: 18, scope: !1448)
!1456 = !DILocation(line: 609, column: 26, scope: !1448)
!1457 = !DILocation(line: 609, column: 3, scope: !1448)
!1458 = !DILocation(line: 610, column: 1, scope: !294)
!1459 = !DILocalVariable(name: "entry", arg: 1, scope: !295, file: !1, line: 613, type: !5)
!1460 = !DILocation(line: 613, column: 47, scope: !295)
!1461 = !DILocation(line: 615, column: 6, scope: !1462)
!1462 = distinct !DILexicalBlock(scope: !295, file: !1, line: 615, column: 6)
!1463 = !DILocation(line: 615, column: 13, scope: !1462)
!1464 = !DILocation(line: 615, column: 21, scope: !1462)
!1465 = !DILocation(line: 615, column: 6, scope: !295)
!1466 = !DILocation(line: 616, column: 11, scope: !1462)
!1467 = !DILocation(line: 616, column: 18, scope: !1462)
!1468 = !DILocation(line: 616, column: 26, scope: !1462)
!1469 = !DILocation(line: 616, column: 3, scope: !1462)
!1470 = !DILocation(line: 618, column: 10, scope: !1462)
!1471 = !DILocation(line: 618, column: 3, scope: !1462)
!1472 = !DILocation(line: 619, column: 1, scope: !295)
!1473 = !DILocalVariable(name: "entry", arg: 1, scope: !296, file: !1, line: 622, type: !5)
!1474 = !DILocation(line: 622, column: 47, scope: !296)
!1475 = !DILocation(line: 624, column: 6, scope: !1476)
!1476 = distinct !DILexicalBlock(scope: !296, file: !1, line: 624, column: 6)
!1477 = !DILocation(line: 624, column: 13, scope: !1476)
!1478 = !DILocation(line: 624, column: 21, scope: !1476)
!1479 = !DILocation(line: 624, column: 6, scope: !296)
!1480 = !DILocation(line: 625, column: 11, scope: !1476)
!1481 = !DILocation(line: 625, column: 18, scope: !1476)
!1482 = !DILocation(line: 625, column: 26, scope: !1476)
!1483 = !DILocation(line: 625, column: 3, scope: !1476)
!1484 = !DILocation(line: 627, column: 10, scope: !1476)
!1485 = !DILocation(line: 627, column: 3, scope: !1476)
!1486 = !DILocation(line: 628, column: 1, scope: !296)
!1487 = !DILocalVariable(name: "entry", arg: 1, scope: !297, file: !1, line: 631, type: !5)
!1488 = !DILocation(line: 631, column: 42, scope: !297)
!1489 = !DILocation(line: 633, column: 10, scope: !297)
!1490 = !DILocation(line: 633, column: 17, scope: !297)
!1491 = !DILocation(line: 633, column: 25, scope: !297)
!1492 = !DILocation(line: 633, column: 2, scope: !297)
!1493 = !DILocalVariable(name: "entry", arg: 1, scope: !298, file: !1, line: 637, type: !5)
!1494 = !DILocation(line: 637, column: 49, scope: !298)
!1495 = !DILocation(line: 639, column: 10, scope: !298)
!1496 = !DILocation(line: 639, column: 17, scope: !298)
!1497 = !DILocation(line: 639, column: 24, scope: !298)
!1498 = !DILocation(line: 639, column: 2, scope: !298)
!1499 = !DILocalVariable(name: "entry", arg: 1, scope: !299, file: !1, line: 643, type: !5)
!1500 = !DILocation(line: 643, column: 48, scope: !299)
!1501 = !DILocalVariable(name: "p", scope: !299, file: !1, line: 645, type: !78)
!1502 = !DILocation(line: 645, column: 14, scope: !299)
!1503 = !DILocation(line: 647, column: 6, scope: !1504)
!1504 = distinct !DILexicalBlock(scope: !299, file: !1, line: 646, column: 6)
!1505 = !DILocation(line: 647, column: 13, scope: !1504)
!1506 = !DILocation(line: 647, column: 23, scope: !1504)
!1507 = !DILocation(line: 647, column: 30, scope: !1504)
!1508 = !DILocation(line: 646, column: 6, scope: !1504)
!1509 = !DILocation(line: 647, column: 49, scope: !1504)
!1510 = !DILocation(line: 646, column: 6, scope: !299)
!1511 = !DILocation(line: 648, column: 11, scope: !1504)
!1512 = !DILocation(line: 648, column: 3, scope: !1504)
!1513 = !DILocation(line: 649, column: 6, scope: !1514)
!1514 = distinct !DILexicalBlock(scope: !299, file: !1, line: 649, column: 6)
!1515 = !DILocation(line: 649, column: 12, scope: !1514)
!1516 = !DILocation(line: 649, column: 6, scope: !299)
!1517 = !DILocation(line: 650, column: 3, scope: !1514)
!1518 = !DILocation(line: 651, column: 2, scope: !299)
!1519 = !DILocation(line: 652, column: 1, scope: !299)
!1520 = !DILocalVariable(name: "entry", arg: 1, scope: !300, file: !1, line: 655, type: !5)
!1521 = !DILocation(line: 655, column: 50, scope: !300)
!1522 = !DILocalVariable(name: "p", scope: !300, file: !1, line: 657, type: !269)
!1523 = !DILocation(line: 657, column: 17, scope: !300)
!1524 = !DILocation(line: 659, column: 6, scope: !1525)
!1525 = distinct !DILexicalBlock(scope: !300, file: !1, line: 658, column: 6)
!1526 = !DILocation(line: 659, column: 13, scope: !1525)
!1527 = !DILocation(line: 659, column: 23, scope: !1525)
!1528 = !DILocation(line: 659, column: 30, scope: !1525)
!1529 = !DILocation(line: 658, column: 6, scope: !1525)
!1530 = !DILocation(line: 659, column: 49, scope: !1525)
!1531 = !DILocation(line: 658, column: 6, scope: !300)
!1532 = !DILocation(line: 660, column: 11, scope: !1525)
!1533 = !DILocation(line: 660, column: 3, scope: !1525)
!1534 = !DILocation(line: 661, column: 2, scope: !300)
!1535 = !DILocation(line: 662, column: 1, scope: !300)
!1536 = !DILocalVariable(name: "entry", arg: 1, scope: !301, file: !1, line: 665, type: !5)
!1537 = !DILocation(line: 665, column: 45, scope: !301)
!1538 = !DILocalVariable(name: "p", scope: !301, file: !1, line: 667, type: !78)
!1539 = !DILocation(line: 667, column: 14, scope: !301)
!1540 = !DILocation(line: 668, column: 7, scope: !1541)
!1541 = distinct !DILexicalBlock(scope: !301, file: !1, line: 668, column: 6)
!1542 = !DILocation(line: 668, column: 14, scope: !1541)
!1543 = !DILocation(line: 668, column: 21, scope: !1541)
!1544 = !DILocation(line: 668, column: 39, scope: !1541)
!1545 = !DILocation(line: 668, column: 6, scope: !301)
!1546 = !DILocation(line: 669, column: 3, scope: !1541)
!1547 = !DILocation(line: 671, column: 6, scope: !1548)
!1548 = distinct !DILexicalBlock(scope: !301, file: !1, line: 670, column: 6)
!1549 = !DILocation(line: 671, column: 13, scope: !1548)
!1550 = !DILocation(line: 671, column: 23, scope: !1548)
!1551 = !DILocation(line: 671, column: 30, scope: !1548)
!1552 = !DILocation(line: 670, column: 6, scope: !1548)
!1553 = !DILocation(line: 671, column: 46, scope: !1548)
!1554 = !DILocation(line: 670, column: 6, scope: !301)
!1555 = !DILocation(line: 672, column: 11, scope: !1548)
!1556 = !DILocation(line: 672, column: 3, scope: !1548)
!1557 = !DILocation(line: 673, column: 6, scope: !1558)
!1558 = distinct !DILexicalBlock(scope: !301, file: !1, line: 673, column: 6)
!1559 = !DILocation(line: 673, column: 12, scope: !1558)
!1560 = !DILocation(line: 673, column: 6, scope: !301)
!1561 = !DILocation(line: 674, column: 3, scope: !1558)
!1562 = !DILocation(line: 675, column: 2, scope: !301)
!1563 = !DILocation(line: 676, column: 1, scope: !301)
!1564 = !DILocalVariable(name: "entry", arg: 1, scope: !302, file: !1, line: 679, type: !5)
!1565 = !DILocation(line: 679, column: 50, scope: !302)
!1566 = !DILocalVariable(name: "p", scope: !302, file: !1, line: 681, type: !78)
!1567 = !DILocation(line: 681, column: 14, scope: !302)
!1568 = !DILocation(line: 682, column: 7, scope: !1569)
!1569 = distinct !DILexicalBlock(scope: !302, file: !1, line: 682, column: 6)
!1570 = !DILocation(line: 682, column: 14, scope: !1569)
!1571 = !DILocation(line: 682, column: 21, scope: !1569)
!1572 = !DILocation(line: 682, column: 39, scope: !1569)
!1573 = !DILocation(line: 682, column: 6, scope: !302)
!1574 = !DILocation(line: 683, column: 3, scope: !1569)
!1575 = !DILocation(line: 685, column: 6, scope: !1576)
!1576 = distinct !DILexicalBlock(scope: !302, file: !1, line: 684, column: 6)
!1577 = !DILocation(line: 685, column: 13, scope: !1576)
!1578 = !DILocation(line: 685, column: 23, scope: !1576)
!1579 = !DILocation(line: 685, column: 30, scope: !1576)
!1580 = !DILocation(line: 684, column: 6, scope: !1576)
!1581 = !DILocation(line: 685, column: 46, scope: !1576)
!1582 = !DILocation(line: 684, column: 6, scope: !302)
!1583 = !DILocation(line: 686, column: 11, scope: !1576)
!1584 = !DILocation(line: 686, column: 3, scope: !1576)
!1585 = !DILocation(line: 687, column: 6, scope: !1586)
!1586 = distinct !DILexicalBlock(scope: !302, file: !1, line: 687, column: 6)
!1587 = !DILocation(line: 687, column: 12, scope: !1586)
!1588 = !DILocation(line: 687, column: 6, scope: !302)
!1589 = !DILocation(line: 688, column: 3, scope: !1586)
!1590 = !DILocation(line: 689, column: 2, scope: !302)
!1591 = !DILocation(line: 690, column: 1, scope: !302)
!1592 = !DILocalVariable(name: "entry", arg: 1, scope: !303, file: !1, line: 693, type: !5)
!1593 = !DILocation(line: 693, column: 47, scope: !303)
!1594 = !DILocalVariable(name: "p", scope: !303, file: !1, line: 695, type: !269)
!1595 = !DILocation(line: 695, column: 17, scope: !303)
!1596 = !DILocation(line: 696, column: 7, scope: !1597)
!1597 = distinct !DILexicalBlock(scope: !303, file: !1, line: 696, column: 6)
!1598 = !DILocation(line: 696, column: 14, scope: !1597)
!1599 = !DILocation(line: 696, column: 21, scope: !1597)
!1600 = !DILocation(line: 696, column: 39, scope: !1597)
!1601 = !DILocation(line: 696, column: 6, scope: !303)
!1602 = !DILocation(line: 697, column: 3, scope: !1597)
!1603 = !DILocation(line: 699, column: 6, scope: !1604)
!1604 = distinct !DILexicalBlock(scope: !303, file: !1, line: 698, column: 6)
!1605 = !DILocation(line: 699, column: 13, scope: !1604)
!1606 = !DILocation(line: 699, column: 23, scope: !1604)
!1607 = !DILocation(line: 699, column: 30, scope: !1604)
!1608 = !DILocation(line: 698, column: 6, scope: !1604)
!1609 = !DILocation(line: 699, column: 46, scope: !1604)
!1610 = !DILocation(line: 698, column: 6, scope: !303)
!1611 = !DILocation(line: 700, column: 11, scope: !1604)
!1612 = !DILocation(line: 700, column: 3, scope: !1604)
!1613 = !DILocation(line: 701, column: 6, scope: !1614)
!1614 = distinct !DILexicalBlock(scope: !303, file: !1, line: 701, column: 6)
!1615 = !DILocation(line: 701, column: 12, scope: !1614)
!1616 = !DILocation(line: 701, column: 6, scope: !303)
!1617 = !DILocation(line: 702, column: 3, scope: !1614)
!1618 = !DILocation(line: 703, column: 2, scope: !303)
!1619 = !DILocation(line: 704, column: 1, scope: !303)
!1620 = !DILocalVariable(name: "entry", arg: 1, scope: !304, file: !1, line: 707, type: !5)
!1621 = !DILocation(line: 707, column: 48, scope: !304)
!1622 = !DILocalVariable(name: "p", arg: 2, scope: !304, file: !1, line: 708, type: !274)
!1623 = !DILocation(line: 708, column: 18, scope: !304)
!1624 = !DILocalVariable(name: "len", arg: 3, scope: !304, file: !1, line: 708, type: !63)
!1625 = !DILocation(line: 708, column: 29, scope: !304)
!1626 = !DILocalVariable(name: "sc", arg: 4, scope: !304, file: !1, line: 708, type: !100)
!1627 = !DILocation(line: 708, column: 62, scope: !304)
!1628 = !DILocation(line: 710, column: 7, scope: !1629)
!1629 = distinct !DILexicalBlock(scope: !304, file: !1, line: 710, column: 6)
!1630 = !DILocation(line: 710, column: 14, scope: !1629)
!1631 = !DILocation(line: 710, column: 21, scope: !1629)
!1632 = !DILocation(line: 710, column: 39, scope: !1629)
!1633 = !DILocation(line: 710, column: 6, scope: !304)
!1634 = !DILocation(line: 711, column: 4, scope: !1635)
!1635 = distinct !DILexicalBlock(scope: !1629, file: !1, line: 710, column: 45)
!1636 = !DILocation(line: 711, column: 6, scope: !1635)
!1637 = !DILocation(line: 712, column: 4, scope: !1635)
!1638 = !DILocation(line: 712, column: 8, scope: !1635)
!1639 = !DILocation(line: 713, column: 3, scope: !1635)
!1640 = !DILocation(line: 715, column: 38, scope: !304)
!1641 = !DILocation(line: 715, column: 45, scope: !304)
!1642 = !DILocation(line: 715, column: 57, scope: !304)
!1643 = !DILocation(line: 715, column: 60, scope: !304)
!1644 = !DILocation(line: 715, column: 65, scope: !304)
!1645 = !DILocation(line: 715, column: 10, scope: !304)
!1646 = !DILocation(line: 715, column: 2, scope: !304)
!1647 = !DILocation(line: 716, column: 1, scope: !304)
!1648 = !DILocalVariable(name: "entry", arg: 1, scope: !305, file: !1, line: 719, type: !5)
!1649 = !DILocation(line: 719, column: 41, scope: !305)
!1650 = !DILocation(line: 721, column: 10, scope: !305)
!1651 = !DILocation(line: 721, column: 17, scope: !305)
!1652 = !DILocation(line: 721, column: 25, scope: !305)
!1653 = !DILocation(line: 721, column: 2, scope: !305)
!1654 = !DILocalVariable(name: "entry", arg: 1, scope: !306, file: !1, line: 725, type: !5)
!1655 = !DILocation(line: 725, column: 43, scope: !306)
!1656 = !DILocalVariable(name: "p", scope: !306, file: !1, line: 727, type: !78)
!1657 = !DILocation(line: 727, column: 14, scope: !306)
!1658 = !DILocation(line: 728, column: 30, scope: !1659)
!1659 = distinct !DILexicalBlock(scope: !306, file: !1, line: 728, column: 6)
!1660 = !DILocation(line: 728, column: 37, scope: !1659)
!1661 = !DILocation(line: 728, column: 47, scope: !1659)
!1662 = !DILocation(line: 728, column: 54, scope: !1659)
!1663 = !DILocation(line: 728, column: 6, scope: !1659)
!1664 = !DILocation(line: 728, column: 68, scope: !1659)
!1665 = !DILocation(line: 728, column: 6, scope: !306)
!1666 = !DILocation(line: 729, column: 11, scope: !1659)
!1667 = !DILocation(line: 729, column: 3, scope: !1659)
!1668 = !DILocation(line: 730, column: 6, scope: !1669)
!1669 = distinct !DILexicalBlock(scope: !306, file: !1, line: 730, column: 6)
!1670 = !DILocation(line: 730, column: 12, scope: !1669)
!1671 = !DILocation(line: 730, column: 6, scope: !306)
!1672 = !DILocation(line: 731, column: 3, scope: !1669)
!1673 = !DILocation(line: 732, column: 2, scope: !306)
!1674 = !DILocation(line: 733, column: 1, scope: !306)
!1675 = !DILocalVariable(name: "entry", arg: 1, scope: !307, file: !1, line: 736, type: !5)
!1676 = !DILocation(line: 736, column: 48, scope: !307)
!1677 = !DILocalVariable(name: "p", scope: !307, file: !1, line: 738, type: !78)
!1678 = !DILocation(line: 738, column: 14, scope: !307)
!1679 = !DILocation(line: 739, column: 31, scope: !1680)
!1680 = distinct !DILexicalBlock(scope: !307, file: !1, line: 739, column: 6)
!1681 = !DILocation(line: 739, column: 38, scope: !1680)
!1682 = !DILocation(line: 739, column: 48, scope: !1680)
!1683 = !DILocation(line: 739, column: 55, scope: !1680)
!1684 = !DILocation(line: 739, column: 6, scope: !1680)
!1685 = !DILocation(line: 739, column: 69, scope: !1680)
!1686 = !DILocation(line: 739, column: 6, scope: !307)
!1687 = !DILocation(line: 740, column: 11, scope: !1680)
!1688 = !DILocation(line: 740, column: 3, scope: !1680)
!1689 = !DILocation(line: 741, column: 6, scope: !1690)
!1690 = distinct !DILexicalBlock(scope: !307, file: !1, line: 741, column: 6)
!1691 = !DILocation(line: 741, column: 12, scope: !1690)
!1692 = !DILocation(line: 741, column: 6, scope: !307)
!1693 = !DILocation(line: 742, column: 3, scope: !1690)
!1694 = !DILocation(line: 743, column: 2, scope: !307)
!1695 = !DILocation(line: 744, column: 1, scope: !307)
!1696 = !DILocalVariable(name: "entry", arg: 1, scope: !308, file: !1, line: 747, type: !5)
!1697 = !DILocation(line: 747, column: 45, scope: !308)
!1698 = !DILocalVariable(name: "p", scope: !308, file: !1, line: 749, type: !269)
!1699 = !DILocation(line: 749, column: 17, scope: !308)
!1700 = !DILocation(line: 750, column: 30, scope: !1701)
!1701 = distinct !DILexicalBlock(scope: !308, file: !1, line: 750, column: 6)
!1702 = !DILocation(line: 750, column: 37, scope: !1701)
!1703 = !DILocation(line: 750, column: 47, scope: !1701)
!1704 = !DILocation(line: 750, column: 54, scope: !1701)
!1705 = !DILocation(line: 750, column: 6, scope: !1701)
!1706 = !DILocation(line: 750, column: 68, scope: !1701)
!1707 = !DILocation(line: 750, column: 6, scope: !308)
!1708 = !DILocation(line: 751, column: 11, scope: !1701)
!1709 = !DILocation(line: 751, column: 3, scope: !1701)
!1710 = !DILocation(line: 752, column: 6, scope: !1711)
!1711 = distinct !DILexicalBlock(scope: !308, file: !1, line: 752, column: 6)
!1712 = !DILocation(line: 752, column: 12, scope: !1711)
!1713 = !DILocation(line: 752, column: 6, scope: !308)
!1714 = !DILocation(line: 753, column: 3, scope: !1711)
!1715 = !DILocation(line: 754, column: 2, scope: !308)
!1716 = !DILocation(line: 755, column: 1, scope: !308)
!1717 = !DILocalVariable(name: "entry", arg: 1, scope: !309, file: !1, line: 758, type: !5)
!1718 = !DILocation(line: 758, column: 46, scope: !309)
!1719 = !DILocalVariable(name: "p", arg: 2, scope: !309, file: !1, line: 759, type: !274)
!1720 = !DILocation(line: 759, column: 18, scope: !309)
!1721 = !DILocalVariable(name: "len", arg: 3, scope: !309, file: !1, line: 759, type: !63)
!1722 = !DILocation(line: 759, column: 29, scope: !309)
!1723 = !DILocalVariable(name: "sc", arg: 4, scope: !309, file: !1, line: 759, type: !100)
!1724 = !DILocation(line: 759, column: 62, scope: !309)
!1725 = !DILocation(line: 761, column: 37, scope: !309)
!1726 = !DILocation(line: 761, column: 44, scope: !309)
!1727 = !DILocation(line: 761, column: 54, scope: !309)
!1728 = !DILocation(line: 761, column: 57, scope: !309)
!1729 = !DILocation(line: 761, column: 62, scope: !309)
!1730 = !DILocation(line: 761, column: 10, scope: !309)
!1731 = !DILocation(line: 761, column: 2, scope: !309)
!1732 = !DILocalVariable(name: "entry", arg: 1, scope: !310, file: !1, line: 765, type: !5)
!1733 = !DILocation(line: 765, column: 55, scope: !310)
!1734 = !DILocation(line: 767, column: 11, scope: !310)
!1735 = !DILocation(line: 767, column: 18, scope: !310)
!1736 = !DILocation(line: 767, column: 29, scope: !310)
!1737 = !DILocation(line: 767, column: 51, scope: !310)
!1738 = !DILocation(line: 767, column: 2, scope: !310)
!1739 = !DILocalVariable(name: "entry", arg: 1, scope: !311, file: !1, line: 771, type: !5)
!1740 = !DILocation(line: 771, column: 59, scope: !311)
!1741 = !DILocation(line: 773, column: 11, scope: !311)
!1742 = !DILocation(line: 773, column: 18, scope: !311)
!1743 = !DILocation(line: 773, column: 29, scope: !311)
!1744 = !DILocation(line: 773, column: 55, scope: !311)
!1745 = !DILocation(line: 773, column: 2, scope: !311)
!1746 = !DILocalVariable(name: "entry", arg: 1, scope: !312, file: !1, line: 777, type: !5)
!1747 = !DILocation(line: 777, column: 50, scope: !312)
!1748 = !DILocation(line: 779, column: 10, scope: !312)
!1749 = !DILocation(line: 779, column: 17, scope: !312)
!1750 = !DILocation(line: 779, column: 28, scope: !312)
!1751 = !DILocation(line: 779, column: 2, scope: !312)
!1752 = !DILocalVariable(name: "entry", arg: 1, scope: !313, file: !1, line: 787, type: !5)
!1753 = !DILocation(line: 787, column: 50, scope: !313)
!1754 = !DILocalVariable(name: "type", arg: 2, scope: !313, file: !1, line: 787, type: !15)
!1755 = !DILocation(line: 787, column: 70, scope: !313)
!1756 = !DILocation(line: 789, column: 2, scope: !313)
!1757 = !DILocation(line: 789, column: 9, scope: !313)
!1758 = !DILocation(line: 789, column: 20, scope: !313)
!1759 = !DILocation(line: 790, column: 2, scope: !313)
!1760 = !DILocation(line: 790, column: 9, scope: !313)
!1761 = !DILocation(line: 790, column: 13, scope: !313)
!1762 = !DILocation(line: 790, column: 18, scope: !313)
!1763 = !DILocation(line: 791, column: 31, scope: !313)
!1764 = !DILocation(line: 791, column: 29, scope: !313)
!1765 = !DILocation(line: 791, column: 2, scope: !313)
!1766 = !DILocation(line: 791, column: 9, scope: !313)
!1767 = !DILocation(line: 791, column: 13, scope: !313)
!1768 = !DILocation(line: 791, column: 18, scope: !313)
!1769 = !DILocation(line: 792, column: 1, scope: !313)
!1770 = !DILocalVariable(name: "entry", arg: 1, scope: !316, file: !1, line: 795, type: !5)
!1771 = !DILocation(line: 795, column: 48, scope: !316)
!1772 = !DILocalVariable(name: "set", arg: 2, scope: !316, file: !1, line: 796, type: !45)
!1773 = !DILocation(line: 796, column: 19, scope: !316)
!1774 = !DILocalVariable(name: "clear", arg: 3, scope: !316, file: !1, line: 796, type: !45)
!1775 = !DILocation(line: 796, column: 38, scope: !316)
!1776 = !DILocation(line: 798, column: 25, scope: !316)
!1777 = !DILocation(line: 798, column: 32, scope: !316)
!1778 = !DILocation(line: 798, column: 2, scope: !316)
!1779 = !DILocation(line: 799, column: 25, scope: !316)
!1780 = !DILocation(line: 799, column: 2, scope: !316)
!1781 = !DILocation(line: 799, column: 9, scope: !316)
!1782 = !DILocation(line: 799, column: 23, scope: !316)
!1783 = !DILocation(line: 800, column: 27, scope: !316)
!1784 = !DILocation(line: 800, column: 2, scope: !316)
!1785 = !DILocation(line: 800, column: 9, scope: !316)
!1786 = !DILocation(line: 800, column: 25, scope: !316)
!1787 = !DILocation(line: 801, column: 1, scope: !316)
!1788 = !DILocalVariable(name: "entry", arg: 1, scope: !319, file: !1, line: 804, type: !5)
!1789 = !DILocation(line: 804, column: 54, scope: !319)
!1790 = !DILocalVariable(name: "flags", arg: 2, scope: !319, file: !1, line: 805, type: !78)
!1791 = !DILocation(line: 805, column: 17, scope: !319)
!1792 = !DILocation(line: 807, column: 28, scope: !319)
!1793 = !DILocation(line: 807, column: 35, scope: !319)
!1794 = !DILocation(line: 807, column: 51, scope: !319)
!1795 = !DILocation(line: 807, column: 2, scope: !319)
!1796 = !DILocation(line: 808, column: 25, scope: !319)
!1797 = !DILocation(line: 809, column: 8, scope: !319)
!1798 = !DILocation(line: 809, column: 15, scope: !319)
!1799 = !DILocation(line: 809, column: 31, scope: !319)
!1800 = !DILocation(line: 809, column: 38, scope: !319)
!1801 = !DILocation(line: 808, column: 10, scope: !319)
!1802 = !DILocation(line: 808, column: 2, scope: !319)
!1803 = !DILocalVariable(name: "s", arg: 1, scope: !465, file: !1, line: 1892, type: !78)
!1804 = !DILocation(line: 1892, column: 28, scope: !465)
!1805 = !DILocalVariable(name: "setp", arg: 2, scope: !465, file: !1, line: 1892, type: !255)
!1806 = !DILocation(line: 1892, column: 46, scope: !465)
!1807 = !DILocalVariable(name: "clrp", arg: 3, scope: !465, file: !1, line: 1892, type: !255)
!1808 = !DILocation(line: 1892, column: 67, scope: !465)
!1809 = !DILocalVariable(name: "start", scope: !465, file: !1, line: 1894, type: !78)
!1810 = !DILocation(line: 1894, column: 14, scope: !465)
!1811 = !DILocalVariable(name: "end", scope: !465, file: !1, line: 1894, type: !78)
!1812 = !DILocation(line: 1894, column: 22, scope: !465)
!1813 = !DILocalVariable(name: "flag", scope: !465, file: !1, line: 1895, type: !964)
!1814 = !DILocation(line: 1895, column: 15, scope: !465)
!1815 = !DILocalVariable(name: "set", scope: !465, file: !1, line: 1896, type: !45)
!1816 = !DILocation(line: 1896, column: 16, scope: !465)
!1817 = !DILocalVariable(name: "clear", scope: !465, file: !1, line: 1896, type: !45)
!1818 = !DILocation(line: 1896, column: 21, scope: !465)
!1819 = !DILocalVariable(name: "failed", scope: !465, file: !1, line: 1897, type: !78)
!1820 = !DILocation(line: 1897, column: 14, scope: !465)
!1821 = !DILocation(line: 1899, column: 14, scope: !465)
!1822 = !DILocation(line: 1899, column: 6, scope: !465)
!1823 = !DILocation(line: 1900, column: 10, scope: !465)
!1824 = !DILocation(line: 1900, column: 8, scope: !465)
!1825 = !DILocation(line: 1901, column: 9, scope: !465)
!1826 = !DILocation(line: 1903, column: 2, scope: !465)
!1827 = !DILocation(line: 1903, column: 10, scope: !1828)
!1828 = !DILexicalBlockFile(scope: !465, file: !1, discriminator: 1)
!1829 = !DILocation(line: 1903, column: 9, scope: !1828)
!1830 = !DILocation(line: 1903, column: 16, scope: !1828)
!1831 = !DILocation(line: 1903, column: 25, scope: !1828)
!1832 = !DILocation(line: 1903, column: 30, scope: !1833)
!1833 = !DILexicalBlockFile(scope: !465, file: !1, discriminator: 2)
!1834 = !DILocation(line: 1903, column: 29, scope: !1833)
!1835 = !DILocation(line: 1903, column: 36, scope: !1833)
!1836 = !DILocation(line: 1903, column: 44, scope: !1833)
!1837 = !DILocation(line: 1903, column: 49, scope: !1838)
!1838 = !DILexicalBlockFile(scope: !465, file: !1, discriminator: 3)
!1839 = !DILocation(line: 1903, column: 48, scope: !1838)
!1840 = !DILocation(line: 1903, column: 55, scope: !1838)
!1841 = !DILocation(line: 1903, column: 44, scope: !1838)
!1842 = !DILocation(line: 1903, column: 2, scope: !1843)
!1843 = !DILexicalBlockFile(scope: !465, file: !1, discriminator: 4)
!1844 = !DILocation(line: 1904, column: 8, scope: !465)
!1845 = !DILocation(line: 1903, column: 2, scope: !1846)
!1846 = !DILexicalBlockFile(scope: !465, file: !1, discriminator: 5)
!1847 = !DILocation(line: 1905, column: 2, scope: !465)
!1848 = !DILocation(line: 1905, column: 10, scope: !1828)
!1849 = !DILocation(line: 1905, column: 9, scope: !1828)
!1850 = !DILocation(line: 1905, column: 16, scope: !1828)
!1851 = !DILocation(line: 1905, column: 2, scope: !1828)
!1852 = !DILocalVariable(name: "length", scope: !1853, file: !1, line: 1906, type: !43)
!1853 = distinct !DILexicalBlock(scope: !465, file: !1, line: 1905, column: 25)
!1854 = !DILocation(line: 1906, column: 10, scope: !1853)
!1855 = !DILocation(line: 1908, column: 9, scope: !1853)
!1856 = !DILocation(line: 1908, column: 7, scope: !1853)
!1857 = !DILocation(line: 1909, column: 3, scope: !1853)
!1858 = !DILocation(line: 1909, column: 11, scope: !1859)
!1859 = !DILexicalBlockFile(scope: !1853, file: !1, discriminator: 1)
!1860 = !DILocation(line: 1909, column: 10, scope: !1859)
!1861 = !DILocation(line: 1909, column: 15, scope: !1859)
!1862 = !DILocation(line: 1909, column: 24, scope: !1859)
!1863 = !DILocation(line: 1909, column: 29, scope: !1864)
!1864 = !DILexicalBlockFile(scope: !1853, file: !1, discriminator: 2)
!1865 = !DILocation(line: 1909, column: 28, scope: !1864)
!1866 = !DILocation(line: 1909, column: 33, scope: !1864)
!1867 = !DILocation(line: 1909, column: 42, scope: !1864)
!1868 = !DILocation(line: 1910, column: 8, scope: !1853)
!1869 = !DILocation(line: 1910, column: 7, scope: !1853)
!1870 = !DILocation(line: 1910, column: 12, scope: !1853)
!1871 = !DILocation(line: 1910, column: 20, scope: !1853)
!1872 = !DILocation(line: 1910, column: 25, scope: !1859)
!1873 = !DILocation(line: 1910, column: 24, scope: !1859)
!1874 = !DILocation(line: 1910, column: 29, scope: !1859)
!1875 = !DILocation(line: 1909, column: 3, scope: !1876)
!1876 = !DILexicalBlockFile(scope: !1853, file: !1, discriminator: 3)
!1877 = !DILocation(line: 1911, column: 7, scope: !1853)
!1878 = !DILocation(line: 1909, column: 3, scope: !1879)
!1879 = !DILexicalBlockFile(scope: !1853, file: !1, discriminator: 4)
!1880 = !DILocation(line: 1912, column: 12, scope: !1853)
!1881 = !DILocation(line: 1912, column: 18, scope: !1853)
!1882 = !DILocation(line: 1912, column: 16, scope: !1853)
!1883 = !DILocation(line: 1912, column: 10, scope: !1853)
!1884 = !DILocation(line: 1913, column: 13, scope: !1885)
!1885 = distinct !DILexicalBlock(scope: !1853, file: !1, line: 1913, column: 3)
!1886 = !DILocation(line: 1913, column: 8, scope: !1885)
!1887 = !DILocation(line: 1913, column: 22, scope: !1888)
!1888 = !DILexicalBlockFile(scope: !1889, file: !1, discriminator: 1)
!1889 = distinct !DILexicalBlock(scope: !1885, file: !1, line: 1913, column: 3)
!1890 = !DILocation(line: 1913, column: 28, scope: !1888)
!1891 = !DILocation(line: 1913, column: 33, scope: !1888)
!1892 = !DILocation(line: 1913, column: 3, scope: !1888)
!1893 = !DILocalVariable(name: "flag_length", scope: !1894, file: !1, line: 1914, type: !43)
!1894 = distinct !DILexicalBlock(scope: !1889, file: !1, line: 1913, column: 50)
!1895 = !DILocation(line: 1914, column: 11, scope: !1894)
!1896 = !DILocation(line: 1914, column: 32, scope: !1894)
!1897 = !DILocation(line: 1914, column: 38, scope: !1894)
!1898 = !DILocation(line: 1914, column: 25, scope: !1894)
!1899 = !DILocation(line: 1915, column: 8, scope: !1900)
!1900 = distinct !DILexicalBlock(scope: !1894, file: !1, line: 1915, column: 8)
!1901 = !DILocation(line: 1915, column: 18, scope: !1900)
!1902 = !DILocation(line: 1915, column: 15, scope: !1900)
!1903 = !DILocation(line: 1916, column: 8, scope: !1900)
!1904 = !DILocation(line: 1916, column: 18, scope: !1905)
!1905 = !DILexicalBlockFile(scope: !1900, file: !1, discriminator: 1)
!1906 = !DILocation(line: 1916, column: 25, scope: !1905)
!1907 = !DILocation(line: 1916, column: 31, scope: !1905)
!1908 = !DILocation(line: 1916, column: 37, scope: !1905)
!1909 = !DILocation(line: 1916, column: 11, scope: !1905)
!1910 = !DILocation(line: 1916, column: 45, scope: !1905)
!1911 = !DILocation(line: 1915, column: 8, scope: !1912)
!1912 = !DILexicalBlockFile(scope: !1894, file: !1, discriminator: 1)
!1913 = !DILocation(line: 1918, column: 14, scope: !1914)
!1914 = distinct !DILexicalBlock(scope: !1900, file: !1, line: 1916, column: 51)
!1915 = !DILocation(line: 1918, column: 20, scope: !1914)
!1916 = !DILocation(line: 1918, column: 11, scope: !1914)
!1917 = !DILocation(line: 1919, column: 12, scope: !1914)
!1918 = !DILocation(line: 1919, column: 18, scope: !1914)
!1919 = !DILocation(line: 1919, column: 9, scope: !1914)
!1920 = !DILocation(line: 1920, column: 5, scope: !1914)
!1921 = !DILocation(line: 1921, column: 15, scope: !1922)
!1922 = distinct !DILexicalBlock(scope: !1900, file: !1, line: 1921, column: 15)
!1923 = !DILocation(line: 1921, column: 25, scope: !1922)
!1924 = !DILocation(line: 1921, column: 37, scope: !1922)
!1925 = !DILocation(line: 1921, column: 22, scope: !1922)
!1926 = !DILocation(line: 1922, column: 8, scope: !1922)
!1927 = !DILocation(line: 1922, column: 18, scope: !1928)
!1928 = !DILexicalBlockFile(scope: !1922, file: !1, discriminator: 1)
!1929 = !DILocation(line: 1922, column: 25, scope: !1928)
!1930 = !DILocation(line: 1922, column: 31, scope: !1928)
!1931 = !DILocation(line: 1922, column: 36, scope: !1928)
!1932 = !DILocation(line: 1922, column: 41, scope: !1928)
!1933 = !DILocation(line: 1922, column: 11, scope: !1928)
!1934 = !DILocation(line: 1922, column: 49, scope: !1928)
!1935 = !DILocation(line: 1921, column: 15, scope: !1905)
!1936 = !DILocation(line: 1924, column: 12, scope: !1937)
!1937 = distinct !DILexicalBlock(scope: !1922, file: !1, line: 1922, column: 55)
!1938 = !DILocation(line: 1924, column: 18, scope: !1937)
!1939 = !DILocation(line: 1924, column: 9, scope: !1937)
!1940 = !DILocation(line: 1925, column: 14, scope: !1937)
!1941 = !DILocation(line: 1925, column: 20, scope: !1937)
!1942 = !DILocation(line: 1925, column: 11, scope: !1937)
!1943 = !DILocation(line: 1926, column: 5, scope: !1937)
!1944 = !DILocation(line: 1928, column: 3, scope: !1894)
!1945 = !DILocation(line: 1913, column: 46, scope: !1946)
!1946 = !DILexicalBlockFile(scope: !1889, file: !1, discriminator: 2)
!1947 = !DILocation(line: 1913, column: 3, scope: !1946)
!1948 = !DILocation(line: 1930, column: 7, scope: !1949)
!1949 = distinct !DILexicalBlock(scope: !1853, file: !1, line: 1930, column: 7)
!1950 = !DILocation(line: 1930, column: 13, scope: !1949)
!1951 = !DILocation(line: 1930, column: 18, scope: !1949)
!1952 = !DILocation(line: 1930, column: 27, scope: !1949)
!1953 = !DILocation(line: 1930, column: 31, scope: !1954)
!1954 = !DILexicalBlockFile(scope: !1949, file: !1, discriminator: 1)
!1955 = !DILocation(line: 1930, column: 38, scope: !1954)
!1956 = !DILocation(line: 1930, column: 7, scope: !1954)
!1957 = !DILocation(line: 1931, column: 13, scope: !1949)
!1958 = !DILocation(line: 1931, column: 11, scope: !1949)
!1959 = !DILocation(line: 1931, column: 4, scope: !1949)
!1960 = !DILocation(line: 1934, column: 11, scope: !1853)
!1961 = !DILocation(line: 1934, column: 9, scope: !1853)
!1962 = !DILocation(line: 1935, column: 3, scope: !1853)
!1963 = !DILocation(line: 1935, column: 11, scope: !1859)
!1964 = !DILocation(line: 1935, column: 10, scope: !1859)
!1965 = !DILocation(line: 1935, column: 17, scope: !1859)
!1966 = !DILocation(line: 1935, column: 26, scope: !1859)
!1967 = !DILocation(line: 1935, column: 31, scope: !1864)
!1968 = !DILocation(line: 1935, column: 30, scope: !1864)
!1969 = !DILocation(line: 1935, column: 37, scope: !1864)
!1970 = !DILocation(line: 1935, column: 45, scope: !1864)
!1971 = !DILocation(line: 1935, column: 50, scope: !1876)
!1972 = !DILocation(line: 1935, column: 49, scope: !1876)
!1973 = !DILocation(line: 1935, column: 56, scope: !1876)
!1974 = !DILocation(line: 1935, column: 45, scope: !1876)
!1975 = !DILocation(line: 1935, column: 3, scope: !1879)
!1976 = !DILocation(line: 1936, column: 9, scope: !1853)
!1977 = !DILocation(line: 1935, column: 3, scope: !1978)
!1978 = !DILexicalBlockFile(scope: !1853, file: !1, discriminator: 5)
!1979 = !DILocation(line: 1905, column: 2, scope: !1833)
!1980 = !DILocation(line: 1940, column: 6, scope: !1981)
!1981 = distinct !DILexicalBlock(scope: !465, file: !1, line: 1940, column: 6)
!1982 = !DILocation(line: 1940, column: 6, scope: !465)
!1983 = !DILocation(line: 1941, column: 11, scope: !1981)
!1984 = !DILocation(line: 1941, column: 4, scope: !1981)
!1985 = !DILocation(line: 1941, column: 9, scope: !1981)
!1986 = !DILocation(line: 1941, column: 3, scope: !1981)
!1987 = !DILocation(line: 1942, column: 6, scope: !1988)
!1988 = distinct !DILexicalBlock(scope: !465, file: !1, line: 1942, column: 6)
!1989 = !DILocation(line: 1942, column: 6, scope: !465)
!1990 = !DILocation(line: 1943, column: 11, scope: !1988)
!1991 = !DILocation(line: 1943, column: 4, scope: !1988)
!1992 = !DILocation(line: 1943, column: 9, scope: !1988)
!1993 = !DILocation(line: 1943, column: 3, scope: !1988)
!1994 = !DILocation(line: 1946, column: 10, scope: !465)
!1995 = !DILocation(line: 1946, column: 2, scope: !465)
!1996 = !DILocalVariable(name: "entry", arg: 1, scope: !322, file: !1, line: 813, type: !5)
!1997 = !DILocation(line: 813, column: 56, scope: !322)
!1998 = !DILocalVariable(name: "flags", arg: 2, scope: !322, file: !1, line: 814, type: !269)
!1999 = !DILocation(line: 814, column: 20, scope: !322)
!2000 = !DILocation(line: 816, column: 28, scope: !322)
!2001 = !DILocation(line: 816, column: 35, scope: !322)
!2002 = !DILocation(line: 816, column: 51, scope: !322)
!2003 = !DILocation(line: 816, column: 2, scope: !322)
!2004 = !DILocation(line: 817, column: 25, scope: !322)
!2005 = !DILocation(line: 818, column: 8, scope: !322)
!2006 = !DILocation(line: 818, column: 15, scope: !322)
!2007 = !DILocation(line: 818, column: 31, scope: !322)
!2008 = !DILocation(line: 818, column: 38, scope: !322)
!2009 = !DILocation(line: 817, column: 10, scope: !322)
!2010 = !DILocation(line: 817, column: 2, scope: !322)
!2011 = !DILocalVariable(name: "s", arg: 1, scope: !468, file: !1, line: 1960, type: !269)
!2012 = !DILocation(line: 1960, column: 31, scope: !468)
!2013 = !DILocalVariable(name: "setp", arg: 2, scope: !468, file: !1, line: 1960, type: !255)
!2014 = !DILocation(line: 1960, column: 49, scope: !468)
!2015 = !DILocalVariable(name: "clrp", arg: 3, scope: !468, file: !1, line: 1960, type: !255)
!2016 = !DILocation(line: 1960, column: 70, scope: !468)
!2017 = !DILocalVariable(name: "start", scope: !468, file: !1, line: 1962, type: !269)
!2018 = !DILocation(line: 1962, column: 17, scope: !468)
!2019 = !DILocalVariable(name: "end", scope: !468, file: !1, line: 1962, type: !269)
!2020 = !DILocation(line: 1962, column: 25, scope: !468)
!2021 = !DILocalVariable(name: "flag", scope: !468, file: !1, line: 1963, type: !964)
!2022 = !DILocation(line: 1963, column: 15, scope: !468)
!2023 = !DILocalVariable(name: "set", scope: !468, file: !1, line: 1964, type: !45)
!2024 = !DILocation(line: 1964, column: 16, scope: !468)
!2025 = !DILocalVariable(name: "clear", scope: !468, file: !1, line: 1964, type: !45)
!2026 = !DILocation(line: 1964, column: 21, scope: !468)
!2027 = !DILocalVariable(name: "failed", scope: !468, file: !1, line: 1965, type: !269)
!2028 = !DILocation(line: 1965, column: 17, scope: !468)
!2029 = !DILocation(line: 1967, column: 14, scope: !468)
!2030 = !DILocation(line: 1967, column: 6, scope: !468)
!2031 = !DILocation(line: 1968, column: 10, scope: !468)
!2032 = !DILocation(line: 1968, column: 8, scope: !468)
!2033 = !DILocation(line: 1969, column: 9, scope: !468)
!2034 = !DILocation(line: 1971, column: 2, scope: !468)
!2035 = !DILocation(line: 1971, column: 10, scope: !2036)
!2036 = !DILexicalBlockFile(scope: !468, file: !1, discriminator: 1)
!2037 = !DILocation(line: 1971, column: 9, scope: !2036)
!2038 = !DILocation(line: 1971, column: 16, scope: !2036)
!2039 = !DILocation(line: 1971, column: 26, scope: !2036)
!2040 = !DILocation(line: 1971, column: 31, scope: !2041)
!2041 = !DILexicalBlockFile(scope: !468, file: !1, discriminator: 2)
!2042 = !DILocation(line: 1971, column: 30, scope: !2041)
!2043 = !DILocation(line: 1971, column: 37, scope: !2041)
!2044 = !DILocation(line: 1971, column: 46, scope: !2041)
!2045 = !DILocation(line: 1971, column: 51, scope: !2046)
!2046 = !DILexicalBlockFile(scope: !468, file: !1, discriminator: 3)
!2047 = !DILocation(line: 1971, column: 50, scope: !2046)
!2048 = !DILocation(line: 1971, column: 57, scope: !2046)
!2049 = !DILocation(line: 1971, column: 46, scope: !2046)
!2050 = !DILocation(line: 1971, column: 2, scope: !2051)
!2051 = !DILexicalBlockFile(scope: !468, file: !1, discriminator: 4)
!2052 = !DILocation(line: 1972, column: 8, scope: !468)
!2053 = !DILocation(line: 1971, column: 2, scope: !2054)
!2054 = !DILexicalBlockFile(scope: !468, file: !1, discriminator: 5)
!2055 = !DILocation(line: 1973, column: 2, scope: !468)
!2056 = !DILocation(line: 1973, column: 10, scope: !2036)
!2057 = !DILocation(line: 1973, column: 9, scope: !2036)
!2058 = !DILocation(line: 1973, column: 16, scope: !2036)
!2059 = !DILocation(line: 1973, column: 2, scope: !2036)
!2060 = !DILocalVariable(name: "length", scope: !2061, file: !1, line: 1974, type: !43)
!2061 = distinct !DILexicalBlock(scope: !468, file: !1, line: 1973, column: 26)
!2062 = !DILocation(line: 1974, column: 10, scope: !2061)
!2063 = !DILocation(line: 1976, column: 9, scope: !2061)
!2064 = !DILocation(line: 1976, column: 7, scope: !2061)
!2065 = !DILocation(line: 1977, column: 3, scope: !2061)
!2066 = !DILocation(line: 1977, column: 11, scope: !2067)
!2067 = !DILexicalBlockFile(scope: !2061, file: !1, discriminator: 1)
!2068 = !DILocation(line: 1977, column: 10, scope: !2067)
!2069 = !DILocation(line: 1977, column: 15, scope: !2067)
!2070 = !DILocation(line: 1977, column: 25, scope: !2067)
!2071 = !DILocation(line: 1977, column: 30, scope: !2072)
!2072 = !DILexicalBlockFile(scope: !2061, file: !1, discriminator: 2)
!2073 = !DILocation(line: 1977, column: 29, scope: !2072)
!2074 = !DILocation(line: 1977, column: 34, scope: !2072)
!2075 = !DILocation(line: 1977, column: 44, scope: !2072)
!2076 = !DILocation(line: 1978, column: 8, scope: !2061)
!2077 = !DILocation(line: 1978, column: 7, scope: !2061)
!2078 = !DILocation(line: 1978, column: 12, scope: !2061)
!2079 = !DILocation(line: 1978, column: 21, scope: !2061)
!2080 = !DILocation(line: 1978, column: 26, scope: !2067)
!2081 = !DILocation(line: 1978, column: 25, scope: !2067)
!2082 = !DILocation(line: 1978, column: 30, scope: !2067)
!2083 = !DILocation(line: 1977, column: 3, scope: !2084)
!2084 = !DILexicalBlockFile(scope: !2061, file: !1, discriminator: 3)
!2085 = !DILocation(line: 1979, column: 7, scope: !2061)
!2086 = !DILocation(line: 1977, column: 3, scope: !2087)
!2087 = !DILexicalBlockFile(scope: !2061, file: !1, discriminator: 4)
!2088 = !DILocation(line: 1980, column: 12, scope: !2061)
!2089 = !DILocation(line: 1980, column: 18, scope: !2061)
!2090 = !DILocation(line: 1980, column: 16, scope: !2061)
!2091 = !DILocation(line: 1980, column: 10, scope: !2061)
!2092 = !DILocation(line: 1981, column: 13, scope: !2093)
!2093 = distinct !DILexicalBlock(scope: !2061, file: !1, line: 1981, column: 3)
!2094 = !DILocation(line: 1981, column: 8, scope: !2093)
!2095 = !DILocation(line: 1981, column: 22, scope: !2096)
!2096 = !DILexicalBlockFile(scope: !2097, file: !1, discriminator: 1)
!2097 = distinct !DILexicalBlock(scope: !2093, file: !1, line: 1981, column: 3)
!2098 = !DILocation(line: 1981, column: 28, scope: !2096)
!2099 = !DILocation(line: 1981, column: 34, scope: !2096)
!2100 = !DILocation(line: 1981, column: 3, scope: !2096)
!2101 = !DILocalVariable(name: "flag_length", scope: !2102, file: !1, line: 1982, type: !43)
!2102 = distinct !DILexicalBlock(scope: !2097, file: !1, line: 1981, column: 51)
!2103 = !DILocation(line: 1982, column: 11, scope: !2102)
!2104 = !DILocation(line: 1982, column: 32, scope: !2102)
!2105 = !DILocation(line: 1982, column: 38, scope: !2102)
!2106 = !DILocation(line: 1982, column: 25, scope: !2102)
!2107 = !DILocation(line: 1983, column: 8, scope: !2108)
!2108 = distinct !DILexicalBlock(scope: !2102, file: !1, line: 1983, column: 8)
!2109 = !DILocation(line: 1983, column: 18, scope: !2108)
!2110 = !DILocation(line: 1983, column: 15, scope: !2108)
!2111 = !DILocation(line: 1984, column: 8, scope: !2108)
!2112 = !DILocation(line: 1984, column: 19, scope: !2113)
!2113 = !DILexicalBlockFile(scope: !2108, file: !1, discriminator: 1)
!2114 = !DILocation(line: 1984, column: 26, scope: !2113)
!2115 = !DILocation(line: 1984, column: 32, scope: !2113)
!2116 = !DILocation(line: 1984, column: 39, scope: !2113)
!2117 = !DILocation(line: 1984, column: 11, scope: !2113)
!2118 = !DILocation(line: 1984, column: 47, scope: !2113)
!2119 = !DILocation(line: 1983, column: 8, scope: !2120)
!2120 = !DILexicalBlockFile(scope: !2102, file: !1, discriminator: 1)
!2121 = !DILocation(line: 1986, column: 14, scope: !2122)
!2122 = distinct !DILexicalBlock(scope: !2108, file: !1, line: 1984, column: 53)
!2123 = !DILocation(line: 1986, column: 20, scope: !2122)
!2124 = !DILocation(line: 1986, column: 11, scope: !2122)
!2125 = !DILocation(line: 1987, column: 12, scope: !2122)
!2126 = !DILocation(line: 1987, column: 18, scope: !2122)
!2127 = !DILocation(line: 1987, column: 9, scope: !2122)
!2128 = !DILocation(line: 1988, column: 5, scope: !2122)
!2129 = !DILocation(line: 1989, column: 15, scope: !2130)
!2130 = distinct !DILexicalBlock(scope: !2108, file: !1, line: 1989, column: 15)
!2131 = !DILocation(line: 1989, column: 25, scope: !2130)
!2132 = !DILocation(line: 1989, column: 37, scope: !2130)
!2133 = !DILocation(line: 1989, column: 22, scope: !2130)
!2134 = !DILocation(line: 1990, column: 8, scope: !2130)
!2135 = !DILocation(line: 1990, column: 19, scope: !2136)
!2136 = !DILexicalBlockFile(scope: !2130, file: !1, discriminator: 1)
!2137 = !DILocation(line: 1990, column: 26, scope: !2136)
!2138 = !DILocation(line: 1990, column: 32, scope: !2136)
!2139 = !DILocation(line: 1990, column: 38, scope: !2136)
!2140 = !DILocation(line: 1990, column: 43, scope: !2136)
!2141 = !DILocation(line: 1990, column: 11, scope: !2136)
!2142 = !DILocation(line: 1990, column: 51, scope: !2136)
!2143 = !DILocation(line: 1989, column: 15, scope: !2113)
!2144 = !DILocation(line: 1992, column: 12, scope: !2145)
!2145 = distinct !DILexicalBlock(scope: !2130, file: !1, line: 1990, column: 57)
!2146 = !DILocation(line: 1992, column: 18, scope: !2145)
!2147 = !DILocation(line: 1992, column: 9, scope: !2145)
!2148 = !DILocation(line: 1993, column: 14, scope: !2145)
!2149 = !DILocation(line: 1993, column: 20, scope: !2145)
!2150 = !DILocation(line: 1993, column: 11, scope: !2145)
!2151 = !DILocation(line: 1994, column: 5, scope: !2145)
!2152 = !DILocation(line: 1996, column: 3, scope: !2102)
!2153 = !DILocation(line: 1981, column: 47, scope: !2154)
!2154 = !DILexicalBlockFile(scope: !2097, file: !1, discriminator: 2)
!2155 = !DILocation(line: 1981, column: 3, scope: !2154)
!2156 = !DILocation(line: 1998, column: 7, scope: !2157)
!2157 = distinct !DILexicalBlock(scope: !2061, file: !1, line: 1998, column: 7)
!2158 = !DILocation(line: 1998, column: 13, scope: !2157)
!2159 = !DILocation(line: 1998, column: 19, scope: !2157)
!2160 = !DILocation(line: 1998, column: 28, scope: !2157)
!2161 = !DILocation(line: 1998, column: 32, scope: !2162)
!2162 = !DILexicalBlockFile(scope: !2157, file: !1, discriminator: 1)
!2163 = !DILocation(line: 1998, column: 39, scope: !2162)
!2164 = !DILocation(line: 1998, column: 7, scope: !2162)
!2165 = !DILocation(line: 1999, column: 13, scope: !2157)
!2166 = !DILocation(line: 1999, column: 11, scope: !2157)
!2167 = !DILocation(line: 1999, column: 4, scope: !2157)
!2168 = !DILocation(line: 2002, column: 11, scope: !2061)
!2169 = !DILocation(line: 2002, column: 9, scope: !2061)
!2170 = !DILocation(line: 2003, column: 3, scope: !2061)
!2171 = !DILocation(line: 2003, column: 11, scope: !2067)
!2172 = !DILocation(line: 2003, column: 10, scope: !2067)
!2173 = !DILocation(line: 2003, column: 17, scope: !2067)
!2174 = !DILocation(line: 2003, column: 27, scope: !2067)
!2175 = !DILocation(line: 2003, column: 32, scope: !2072)
!2176 = !DILocation(line: 2003, column: 31, scope: !2072)
!2177 = !DILocation(line: 2003, column: 38, scope: !2072)
!2178 = !DILocation(line: 2003, column: 47, scope: !2072)
!2179 = !DILocation(line: 2003, column: 52, scope: !2084)
!2180 = !DILocation(line: 2003, column: 51, scope: !2084)
!2181 = !DILocation(line: 2003, column: 58, scope: !2084)
!2182 = !DILocation(line: 2003, column: 47, scope: !2084)
!2183 = !DILocation(line: 2003, column: 3, scope: !2087)
!2184 = !DILocation(line: 2004, column: 9, scope: !2061)
!2185 = !DILocation(line: 2003, column: 3, scope: !2186)
!2186 = !DILexicalBlockFile(scope: !2061, file: !1, discriminator: 5)
!2187 = !DILocation(line: 1973, column: 2, scope: !2041)
!2188 = !DILocation(line: 2008, column: 6, scope: !2189)
!2189 = distinct !DILexicalBlock(scope: !468, file: !1, line: 2008, column: 6)
!2190 = !DILocation(line: 2008, column: 6, scope: !468)
!2191 = !DILocation(line: 2009, column: 11, scope: !2189)
!2192 = !DILocation(line: 2009, column: 4, scope: !2189)
!2193 = !DILocation(line: 2009, column: 9, scope: !2189)
!2194 = !DILocation(line: 2009, column: 3, scope: !2189)
!2195 = !DILocation(line: 2010, column: 6, scope: !2196)
!2196 = distinct !DILexicalBlock(scope: !468, file: !1, line: 2010, column: 6)
!2197 = !DILocation(line: 2010, column: 6, scope: !468)
!2198 = !DILocation(line: 2011, column: 11, scope: !2196)
!2199 = !DILocation(line: 2011, column: 4, scope: !2196)
!2200 = !DILocation(line: 2011, column: 9, scope: !2196)
!2201 = !DILocation(line: 2011, column: 3, scope: !2196)
!2202 = !DILocation(line: 2014, column: 10, scope: !468)
!2203 = !DILocation(line: 2014, column: 2, scope: !468)
!2204 = !DILocalVariable(name: "entry", arg: 1, scope: !325, file: !1, line: 822, type: !5)
!2205 = !DILocation(line: 822, column: 45, scope: !325)
!2206 = !DILocalVariable(name: "g", arg: 2, scope: !325, file: !1, line: 822, type: !50)
!2207 = !DILocation(line: 822, column: 60, scope: !325)
!2208 = !DILocation(line: 824, column: 2, scope: !325)
!2209 = !DILocation(line: 824, column: 9, scope: !325)
!2210 = !DILocation(line: 824, column: 20, scope: !325)
!2211 = !DILocation(line: 825, column: 28, scope: !325)
!2212 = !DILocation(line: 825, column: 2, scope: !325)
!2213 = !DILocation(line: 825, column: 9, scope: !325)
!2214 = !DILocation(line: 825, column: 17, scope: !325)
!2215 = !DILocation(line: 825, column: 26, scope: !325)
!2216 = !DILocation(line: 826, column: 1, scope: !325)
!2217 = !DILocalVariable(name: "entry", arg: 1, scope: !328, file: !1, line: 829, type: !5)
!2218 = !DILocation(line: 829, column: 47, scope: !328)
!2219 = !DILocalVariable(name: "name", arg: 2, scope: !328, file: !1, line: 829, type: !78)
!2220 = !DILocation(line: 829, column: 66, scope: !328)
!2221 = !DILocation(line: 831, column: 28, scope: !328)
!2222 = !DILocation(line: 831, column: 35, scope: !328)
!2223 = !DILocation(line: 831, column: 45, scope: !328)
!2224 = !DILocation(line: 831, column: 2, scope: !328)
!2225 = !DILocation(line: 832, column: 1, scope: !328)
!2226 = !DILocalVariable(name: "entry", arg: 1, scope: !331, file: !1, line: 835, type: !5)
!2227 = !DILocation(line: 835, column: 52, scope: !331)
!2228 = !DILocalVariable(name: "name", arg: 2, scope: !331, file: !1, line: 835, type: !78)
!2229 = !DILocation(line: 835, column: 71, scope: !331)
!2230 = !DILocation(line: 837, column: 29, scope: !331)
!2231 = !DILocation(line: 837, column: 36, scope: !331)
!2232 = !DILocation(line: 837, column: 46, scope: !331)
!2233 = !DILocation(line: 837, column: 2, scope: !331)
!2234 = !DILocation(line: 838, column: 1, scope: !331)
!2235 = !DILocalVariable(name: "entry", arg: 1, scope: !332, file: !1, line: 841, type: !5)
!2236 = !DILocation(line: 841, column: 48, scope: !332)
!2237 = !DILocalVariable(name: "name", arg: 2, scope: !332, file: !1, line: 841, type: !78)
!2238 = !DILocation(line: 841, column: 67, scope: !332)
!2239 = !DILocation(line: 843, column: 28, scope: !332)
!2240 = !DILocation(line: 843, column: 35, scope: !332)
!2241 = !DILocation(line: 843, column: 45, scope: !332)
!2242 = !DILocation(line: 843, column: 2, scope: !332)
!2243 = !DILocation(line: 844, column: 1, scope: !332)
!2244 = !DILocalVariable(name: "entry", arg: 1, scope: !333, file: !1, line: 847, type: !5)
!2245 = !DILocation(line: 847, column: 50, scope: !333)
!2246 = !DILocalVariable(name: "name", arg: 2, scope: !333, file: !1, line: 847, type: !269)
!2247 = !DILocation(line: 847, column: 72, scope: !333)
!2248 = !DILocation(line: 849, column: 28, scope: !333)
!2249 = !DILocation(line: 849, column: 35, scope: !333)
!2250 = !DILocation(line: 849, column: 45, scope: !333)
!2251 = !DILocation(line: 849, column: 2, scope: !333)
!2252 = !DILocation(line: 850, column: 1, scope: !333)
!2253 = !DILocalVariable(name: "entry", arg: 1, scope: !336, file: !1, line: 853, type: !5)
!2254 = !DILocation(line: 853, column: 55, scope: !336)
!2255 = !DILocalVariable(name: "name", arg: 2, scope: !336, file: !1, line: 853, type: !78)
!2256 = !DILocation(line: 853, column: 74, scope: !336)
!2257 = !DILocation(line: 855, column: 34, scope: !2258)
!2258 = distinct !DILexicalBlock(scope: !336, file: !1, line: 855, column: 6)
!2259 = !DILocation(line: 855, column: 41, scope: !2258)
!2260 = !DILocation(line: 856, column: 7, scope: !2258)
!2261 = !DILocation(line: 856, column: 14, scope: !2258)
!2262 = !DILocation(line: 856, column: 24, scope: !2258)
!2263 = !DILocation(line: 855, column: 6, scope: !2258)
!2264 = !DILocation(line: 856, column: 30, scope: !2258)
!2265 = !DILocation(line: 855, column: 6, scope: !336)
!2266 = !DILocation(line: 857, column: 3, scope: !2258)
!2267 = !DILocation(line: 858, column: 6, scope: !2268)
!2268 = distinct !DILexicalBlock(scope: !336, file: !1, line: 858, column: 6)
!2269 = !DILocation(line: 858, column: 12, scope: !2268)
!2270 = !DILocation(line: 858, column: 6, scope: !336)
!2271 = !DILocation(line: 859, column: 3, scope: !2268)
!2272 = !DILocation(line: 860, column: 2, scope: !336)
!2273 = !DILocation(line: 861, column: 1, scope: !336)
!2274 = !DILocalVariable(name: "entry", arg: 1, scope: !339, file: !1, line: 864, type: !5)
!2275 = !DILocation(line: 864, column: 51, scope: !339)
!2276 = !DILocalVariable(name: "name", arg: 2, scope: !339, file: !1, line: 865, type: !78)
!2277 = !DILocation(line: 865, column: 17, scope: !339)
!2278 = !DILocalVariable(name: "len", arg: 3, scope: !339, file: !1, line: 865, type: !43)
!2279 = !DILocation(line: 865, column: 30, scope: !339)
!2280 = !DILocalVariable(name: "sc", arg: 4, scope: !339, file: !1, line: 865, type: !100)
!2281 = !DILocation(line: 865, column: 63, scope: !339)
!2282 = !DILocation(line: 867, column: 42, scope: !339)
!2283 = !DILocation(line: 867, column: 49, scope: !339)
!2284 = !DILocation(line: 867, column: 59, scope: !339)
!2285 = !DILocation(line: 867, column: 65, scope: !339)
!2286 = !DILocation(line: 867, column: 70, scope: !339)
!2287 = !DILocation(line: 867, column: 10, scope: !339)
!2288 = !DILocation(line: 867, column: 2, scope: !339)
!2289 = !DILocalVariable(name: "entry", arg: 1, scope: !342, file: !1, line: 871, type: !5)
!2290 = !DILocation(line: 871, column: 45, scope: !342)
!2291 = !DILocalVariable(name: "ino", arg: 2, scope: !342, file: !1, line: 871, type: !50)
!2292 = !DILocation(line: 871, column: 60, scope: !342)
!2293 = !DILocation(line: 873, column: 2, scope: !342)
!2294 = !DILocation(line: 873, column: 9, scope: !342)
!2295 = !DILocation(line: 873, column: 20, scope: !342)
!2296 = !DILocation(line: 874, column: 2, scope: !342)
!2297 = !DILocation(line: 874, column: 9, scope: !342)
!2298 = !DILocation(line: 874, column: 16, scope: !342)
!2299 = !DILocation(line: 875, column: 28, scope: !342)
!2300 = !DILocation(line: 875, column: 2, scope: !342)
!2301 = !DILocation(line: 875, column: 9, scope: !342)
!2302 = !DILocation(line: 875, column: 17, scope: !342)
!2303 = !DILocation(line: 875, column: 26, scope: !342)
!2304 = !DILocation(line: 876, column: 1, scope: !342)
!2305 = !DILocalVariable(name: "entry", arg: 1, scope: !343, file: !1, line: 879, type: !5)
!2306 = !DILocation(line: 879, column: 47, scope: !343)
!2307 = !DILocalVariable(name: "ino", arg: 2, scope: !343, file: !1, line: 879, type: !50)
!2308 = !DILocation(line: 879, column: 62, scope: !343)
!2309 = !DILocation(line: 881, column: 2, scope: !343)
!2310 = !DILocation(line: 881, column: 9, scope: !343)
!2311 = !DILocation(line: 881, column: 20, scope: !343)
!2312 = !DILocation(line: 882, column: 2, scope: !343)
!2313 = !DILocation(line: 882, column: 9, scope: !343)
!2314 = !DILocation(line: 882, column: 16, scope: !343)
!2315 = !DILocation(line: 883, column: 28, scope: !343)
!2316 = !DILocation(line: 883, column: 2, scope: !343)
!2317 = !DILocation(line: 883, column: 9, scope: !343)
!2318 = !DILocation(line: 883, column: 17, scope: !343)
!2319 = !DILocation(line: 883, column: 26, scope: !343)
!2320 = !DILocation(line: 884, column: 1, scope: !343)
!2321 = !DILocalVariable(name: "entry", arg: 1, scope: !344, file: !1, line: 887, type: !5)
!2322 = !DILocation(line: 887, column: 50, scope: !344)
!2323 = !DILocalVariable(name: "target", arg: 2, scope: !344, file: !1, line: 887, type: !78)
!2324 = !DILocation(line: 887, column: 69, scope: !344)
!2325 = !DILocation(line: 889, column: 28, scope: !344)
!2326 = !DILocation(line: 889, column: 35, scope: !344)
!2327 = !DILocation(line: 889, column: 48, scope: !344)
!2328 = !DILocation(line: 889, column: 2, scope: !344)
!2329 = !DILocation(line: 890, column: 6, scope: !2330)
!2330 = distinct !DILexicalBlock(scope: !344, file: !1, line: 890, column: 6)
!2331 = !DILocation(line: 890, column: 13, scope: !2330)
!2332 = !DILocation(line: 890, column: 6, scope: !344)
!2333 = !DILocation(line: 891, column: 3, scope: !2330)
!2334 = !DILocation(line: 891, column: 10, scope: !2330)
!2335 = !DILocation(line: 891, column: 17, scope: !2330)
!2336 = !DILocation(line: 893, column: 3, scope: !2330)
!2337 = !DILocation(line: 893, column: 10, scope: !2330)
!2338 = !DILocation(line: 893, column: 17, scope: !2330)
!2339 = !DILocation(line: 894, column: 1, scope: !344)
!2340 = !DILocalVariable(name: "entry", arg: 1, scope: !345, file: !1, line: 897, type: !5)
!2341 = !DILocation(line: 897, column: 55, scope: !345)
!2342 = !DILocalVariable(name: "target", arg: 2, scope: !345, file: !1, line: 897, type: !78)
!2343 = !DILocation(line: 897, column: 74, scope: !345)
!2344 = !DILocation(line: 899, column: 29, scope: !345)
!2345 = !DILocation(line: 899, column: 36, scope: !345)
!2346 = !DILocation(line: 899, column: 49, scope: !345)
!2347 = !DILocation(line: 899, column: 2, scope: !345)
!2348 = !DILocation(line: 900, column: 6, scope: !2349)
!2349 = distinct !DILexicalBlock(scope: !345, file: !1, line: 900, column: 6)
!2350 = !DILocation(line: 900, column: 13, scope: !2349)
!2351 = !DILocation(line: 900, column: 6, scope: !345)
!2352 = !DILocation(line: 901, column: 3, scope: !2349)
!2353 = !DILocation(line: 901, column: 10, scope: !2349)
!2354 = !DILocation(line: 901, column: 17, scope: !2349)
!2355 = !DILocation(line: 903, column: 3, scope: !2349)
!2356 = !DILocation(line: 903, column: 10, scope: !2349)
!2357 = !DILocation(line: 903, column: 17, scope: !2349)
!2358 = !DILocation(line: 904, column: 1, scope: !345)
!2359 = !DILocalVariable(name: "entry", arg: 1, scope: !346, file: !1, line: 907, type: !5)
!2360 = !DILocation(line: 907, column: 51, scope: !346)
!2361 = !DILocalVariable(name: "target", arg: 2, scope: !346, file: !1, line: 907, type: !78)
!2362 = !DILocation(line: 907, column: 70, scope: !346)
!2363 = !DILocation(line: 909, column: 28, scope: !346)
!2364 = !DILocation(line: 909, column: 35, scope: !346)
!2365 = !DILocation(line: 909, column: 48, scope: !346)
!2366 = !DILocation(line: 909, column: 2, scope: !346)
!2367 = !DILocation(line: 910, column: 6, scope: !2368)
!2368 = distinct !DILexicalBlock(scope: !346, file: !1, line: 910, column: 6)
!2369 = !DILocation(line: 910, column: 13, scope: !2368)
!2370 = !DILocation(line: 910, column: 6, scope: !346)
!2371 = !DILocation(line: 911, column: 3, scope: !2368)
!2372 = !DILocation(line: 911, column: 10, scope: !2368)
!2373 = !DILocation(line: 911, column: 17, scope: !2368)
!2374 = !DILocation(line: 913, column: 3, scope: !2368)
!2375 = !DILocation(line: 913, column: 10, scope: !2368)
!2376 = !DILocation(line: 913, column: 17, scope: !2368)
!2377 = !DILocation(line: 914, column: 1, scope: !346)
!2378 = !DILocalVariable(name: "entry", arg: 1, scope: !347, file: !1, line: 917, type: !5)
!2379 = !DILocation(line: 917, column: 53, scope: !347)
!2380 = !DILocalVariable(name: "target", arg: 2, scope: !347, file: !1, line: 917, type: !269)
!2381 = !DILocation(line: 917, column: 75, scope: !347)
!2382 = !DILocation(line: 919, column: 28, scope: !347)
!2383 = !DILocation(line: 919, column: 35, scope: !347)
!2384 = !DILocation(line: 919, column: 48, scope: !347)
!2385 = !DILocation(line: 919, column: 2, scope: !347)
!2386 = !DILocation(line: 920, column: 6, scope: !2387)
!2387 = distinct !DILexicalBlock(scope: !347, file: !1, line: 920, column: 6)
!2388 = !DILocation(line: 920, column: 13, scope: !2387)
!2389 = !DILocation(line: 920, column: 6, scope: !347)
!2390 = !DILocation(line: 921, column: 3, scope: !2387)
!2391 = !DILocation(line: 921, column: 10, scope: !2387)
!2392 = !DILocation(line: 921, column: 17, scope: !2387)
!2393 = !DILocation(line: 923, column: 3, scope: !2387)
!2394 = !DILocation(line: 923, column: 10, scope: !2387)
!2395 = !DILocation(line: 923, column: 17, scope: !2387)
!2396 = !DILocation(line: 924, column: 1, scope: !347)
!2397 = !DILocalVariable(name: "entry", arg: 1, scope: !348, file: !1, line: 927, type: !5)
!2398 = !DILocation(line: 927, column: 58, scope: !348)
!2399 = !DILocalVariable(name: "target", arg: 2, scope: !348, file: !1, line: 927, type: !78)
!2400 = !DILocation(line: 927, column: 77, scope: !348)
!2401 = !DILocation(line: 929, column: 6, scope: !2402)
!2402 = distinct !DILexicalBlock(scope: !348, file: !1, line: 929, column: 6)
!2403 = !DILocation(line: 929, column: 13, scope: !2402)
!2404 = !DILocation(line: 929, column: 6, scope: !348)
!2405 = !DILocation(line: 930, column: 3, scope: !2402)
!2406 = !DILocation(line: 930, column: 10, scope: !2402)
!2407 = !DILocation(line: 930, column: 17, scope: !2402)
!2408 = !DILocation(line: 932, column: 3, scope: !2402)
!2409 = !DILocation(line: 932, column: 10, scope: !2402)
!2410 = !DILocation(line: 932, column: 17, scope: !2402)
!2411 = !DILocation(line: 933, column: 34, scope: !2412)
!2412 = distinct !DILexicalBlock(scope: !348, file: !1, line: 933, column: 6)
!2413 = !DILocation(line: 933, column: 41, scope: !2412)
!2414 = !DILocation(line: 934, column: 7, scope: !2412)
!2415 = !DILocation(line: 934, column: 14, scope: !2412)
!2416 = !DILocation(line: 934, column: 27, scope: !2412)
!2417 = !DILocation(line: 933, column: 6, scope: !2412)
!2418 = !DILocation(line: 934, column: 35, scope: !2412)
!2419 = !DILocation(line: 933, column: 6, scope: !348)
!2420 = !DILocation(line: 935, column: 3, scope: !2412)
!2421 = !DILocation(line: 936, column: 6, scope: !2422)
!2422 = distinct !DILexicalBlock(scope: !348, file: !1, line: 936, column: 6)
!2423 = !DILocation(line: 936, column: 12, scope: !2422)
!2424 = !DILocation(line: 936, column: 6, scope: !348)
!2425 = !DILocation(line: 937, column: 3, scope: !2422)
!2426 = !DILocation(line: 938, column: 2, scope: !348)
!2427 = !DILocation(line: 939, column: 1, scope: !348)
!2428 = !DILocalVariable(name: "entry", arg: 1, scope: !349, file: !1, line: 942, type: !5)
!2429 = !DILocation(line: 942, column: 54, scope: !349)
!2430 = !DILocalVariable(name: "target", arg: 2, scope: !349, file: !1, line: 943, type: !78)
!2431 = !DILocation(line: 943, column: 17, scope: !349)
!2432 = !DILocalVariable(name: "len", arg: 3, scope: !349, file: !1, line: 943, type: !43)
!2433 = !DILocation(line: 943, column: 32, scope: !349)
!2434 = !DILocalVariable(name: "sc", arg: 4, scope: !349, file: !1, line: 943, type: !100)
!2435 = !DILocation(line: 943, column: 65, scope: !349)
!2436 = !DILocalVariable(name: "r", scope: !349, file: !1, line: 945, type: !25)
!2437 = !DILocation(line: 945, column: 6, scope: !349)
!2438 = !DILocation(line: 947, column: 38, scope: !349)
!2439 = !DILocation(line: 947, column: 45, scope: !349)
!2440 = !DILocation(line: 948, column: 6, scope: !349)
!2441 = !DILocation(line: 948, column: 14, scope: !349)
!2442 = !DILocation(line: 948, column: 19, scope: !349)
!2443 = !DILocation(line: 947, column: 6, scope: !349)
!2444 = !DILocation(line: 947, column: 4, scope: !349)
!2445 = !DILocation(line: 949, column: 6, scope: !2446)
!2446 = distinct !DILexicalBlock(scope: !349, file: !1, line: 949, column: 6)
!2447 = !DILocation(line: 949, column: 13, scope: !2446)
!2448 = !DILocation(line: 949, column: 21, scope: !2446)
!2449 = !DILocation(line: 949, column: 24, scope: !2450)
!2450 = !DILexicalBlockFile(scope: !2446, file: !1, discriminator: 1)
!2451 = !DILocation(line: 949, column: 26, scope: !2450)
!2452 = !DILocation(line: 949, column: 6, scope: !2450)
!2453 = !DILocation(line: 950, column: 3, scope: !2446)
!2454 = !DILocation(line: 950, column: 10, scope: !2446)
!2455 = !DILocation(line: 950, column: 17, scope: !2446)
!2456 = !DILocation(line: 952, column: 3, scope: !2446)
!2457 = !DILocation(line: 952, column: 10, scope: !2446)
!2458 = !DILocation(line: 952, column: 17, scope: !2446)
!2459 = !DILocation(line: 953, column: 10, scope: !349)
!2460 = !DILocation(line: 953, column: 2, scope: !349)
!2461 = !DILocalVariable(name: "entry", arg: 1, scope: !350, file: !1, line: 957, type: !5)
!2462 = !DILocation(line: 957, column: 47, scope: !350)
!2463 = !DILocalVariable(name: "t", arg: 2, scope: !350, file: !1, line: 957, type: !228)
!2464 = !DILocation(line: 957, column: 61, scope: !350)
!2465 = !DILocalVariable(name: "ns", arg: 3, scope: !350, file: !1, line: 957, type: !40)
!2466 = !DILocation(line: 957, column: 69, scope: !350)
!2467 = !DILocation(line: 959, column: 2, scope: !350)
!2468 = !DILocation(line: 959, column: 2, scope: !2469)
!2469 = !DILexicalBlockFile(scope: !2470, file: !1, discriminator: 1)
!2470 = distinct !DILexicalBlock(scope: !350, file: !1, line: 959, column: 2)
!2471 = !DILocation(line: 959, column: 2, scope: !2472)
!2472 = !DILexicalBlockFile(scope: !2473, file: !1, discriminator: 2)
!2473 = distinct !DILexicalBlock(scope: !2474, file: !1, line: 959, column: 2)
!2474 = distinct !DILexicalBlock(scope: !2470, file: !1, line: 959, column: 2)
!2475 = !DILocation(line: 959, column: 2, scope: !2476)
!2476 = !DILexicalBlockFile(scope: !2470, file: !1, discriminator: 3)
!2477 = !DILocation(line: 960, column: 2, scope: !350)
!2478 = !DILocation(line: 960, column: 9, scope: !350)
!2479 = !DILocation(line: 960, column: 20, scope: !350)
!2480 = !DILocation(line: 961, column: 2, scope: !350)
!2481 = !DILocation(line: 961, column: 9, scope: !350)
!2482 = !DILocation(line: 961, column: 16, scope: !350)
!2483 = !DILocation(line: 962, column: 30, scope: !350)
!2484 = !DILocation(line: 962, column: 2, scope: !350)
!2485 = !DILocation(line: 962, column: 9, scope: !350)
!2486 = !DILocation(line: 962, column: 17, scope: !350)
!2487 = !DILocation(line: 962, column: 28, scope: !350)
!2488 = !DILocation(line: 963, column: 35, scope: !350)
!2489 = !DILocation(line: 963, column: 2, scope: !350)
!2490 = !DILocation(line: 963, column: 9, scope: !350)
!2491 = !DILocation(line: 963, column: 17, scope: !350)
!2492 = !DILocation(line: 963, column: 33, scope: !350)
!2493 = !DILocation(line: 964, column: 1, scope: !350)
!2494 = !DILocalVariable(name: "entry", arg: 1, scope: !353, file: !1, line: 967, type: !5)
!2495 = !DILocation(line: 967, column: 49, scope: !353)
!2496 = !DILocation(line: 969, column: 26, scope: !353)
!2497 = !DILocation(line: 969, column: 2, scope: !353)
!2498 = !DILocation(line: 970, column: 2, scope: !353)
!2499 = !DILocation(line: 970, column: 9, scope: !353)
!2500 = !DILocation(line: 970, column: 16, scope: !353)
!2501 = !DILocation(line: 971, column: 1, scope: !353)
!2502 = !DILocalVariable(name: "entry", arg: 1, scope: !354, file: !1, line: 974, type: !5)
!2503 = !DILocation(line: 974, column: 51, scope: !354)
!2504 = !DILocalVariable(name: "t", arg: 2, scope: !354, file: !1, line: 974, type: !228)
!2505 = !DILocation(line: 974, column: 65, scope: !354)
!2506 = !DILocalVariable(name: "ns", arg: 3, scope: !354, file: !1, line: 974, type: !40)
!2507 = !DILocation(line: 974, column: 73, scope: !354)
!2508 = !DILocation(line: 976, column: 2, scope: !354)
!2509 = !DILocation(line: 976, column: 2, scope: !2510)
!2510 = !DILexicalBlockFile(scope: !2511, file: !1, discriminator: 1)
!2511 = distinct !DILexicalBlock(scope: !354, file: !1, line: 976, column: 2)
!2512 = !DILocation(line: 976, column: 2, scope: !2513)
!2513 = !DILexicalBlockFile(scope: !2514, file: !1, discriminator: 2)
!2514 = distinct !DILexicalBlock(scope: !2515, file: !1, line: 976, column: 2)
!2515 = distinct !DILexicalBlock(scope: !2511, file: !1, line: 976, column: 2)
!2516 = !DILocation(line: 976, column: 2, scope: !2517)
!2517 = !DILexicalBlockFile(scope: !2511, file: !1, discriminator: 3)
!2518 = !DILocation(line: 977, column: 2, scope: !354)
!2519 = !DILocation(line: 977, column: 9, scope: !354)
!2520 = !DILocation(line: 977, column: 20, scope: !354)
!2521 = !DILocation(line: 978, column: 2, scope: !354)
!2522 = !DILocation(line: 978, column: 9, scope: !354)
!2523 = !DILocation(line: 978, column: 16, scope: !354)
!2524 = !DILocation(line: 979, column: 34, scope: !354)
!2525 = !DILocation(line: 979, column: 2, scope: !354)
!2526 = !DILocation(line: 979, column: 9, scope: !354)
!2527 = !DILocation(line: 979, column: 17, scope: !354)
!2528 = !DILocation(line: 979, column: 32, scope: !354)
!2529 = !DILocation(line: 980, column: 39, scope: !354)
!2530 = !DILocation(line: 980, column: 2, scope: !354)
!2531 = !DILocation(line: 980, column: 9, scope: !354)
!2532 = !DILocation(line: 980, column: 17, scope: !354)
!2533 = !DILocation(line: 980, column: 37, scope: !354)
!2534 = !DILocation(line: 981, column: 1, scope: !354)
!2535 = !DILocalVariable(name: "entry", arg: 1, scope: !355, file: !1, line: 984, type: !5)
!2536 = !DILocation(line: 984, column: 53, scope: !355)
!2537 = !DILocation(line: 986, column: 30, scope: !355)
!2538 = !DILocation(line: 986, column: 2, scope: !355)
!2539 = !DILocation(line: 987, column: 2, scope: !355)
!2540 = !DILocation(line: 987, column: 9, scope: !355)
!2541 = !DILocation(line: 987, column: 16, scope: !355)
!2542 = !DILocation(line: 988, column: 1, scope: !355)
!2543 = !DILocalVariable(name: "entry", arg: 1, scope: !356, file: !1, line: 991, type: !5)
!2544 = !DILocation(line: 991, column: 47, scope: !356)
!2545 = !DILocalVariable(name: "t", arg: 2, scope: !356, file: !1, line: 991, type: !228)
!2546 = !DILocation(line: 991, column: 61, scope: !356)
!2547 = !DILocalVariable(name: "ns", arg: 3, scope: !356, file: !1, line: 991, type: !40)
!2548 = !DILocation(line: 991, column: 69, scope: !356)
!2549 = !DILocation(line: 993, column: 2, scope: !356)
!2550 = !DILocation(line: 993, column: 2, scope: !2551)
!2551 = !DILexicalBlockFile(scope: !2552, file: !1, discriminator: 1)
!2552 = distinct !DILexicalBlock(scope: !356, file: !1, line: 993, column: 2)
!2553 = !DILocation(line: 993, column: 2, scope: !2554)
!2554 = !DILexicalBlockFile(scope: !2555, file: !1, discriminator: 2)
!2555 = distinct !DILexicalBlock(scope: !2556, file: !1, line: 993, column: 2)
!2556 = distinct !DILexicalBlock(scope: !2552, file: !1, line: 993, column: 2)
!2557 = !DILocation(line: 993, column: 2, scope: !2558)
!2558 = !DILexicalBlockFile(scope: !2552, file: !1, discriminator: 3)
!2559 = !DILocation(line: 994, column: 2, scope: !356)
!2560 = !DILocation(line: 994, column: 9, scope: !356)
!2561 = !DILocation(line: 994, column: 20, scope: !356)
!2562 = !DILocation(line: 995, column: 2, scope: !356)
!2563 = !DILocation(line: 995, column: 9, scope: !356)
!2564 = !DILocation(line: 995, column: 16, scope: !356)
!2565 = !DILocation(line: 996, column: 30, scope: !356)
!2566 = !DILocation(line: 996, column: 2, scope: !356)
!2567 = !DILocation(line: 996, column: 9, scope: !356)
!2568 = !DILocation(line: 996, column: 17, scope: !356)
!2569 = !DILocation(line: 996, column: 28, scope: !356)
!2570 = !DILocation(line: 997, column: 35, scope: !356)
!2571 = !DILocation(line: 997, column: 2, scope: !356)
!2572 = !DILocation(line: 997, column: 9, scope: !356)
!2573 = !DILocation(line: 997, column: 17, scope: !356)
!2574 = !DILocation(line: 997, column: 33, scope: !356)
!2575 = !DILocation(line: 998, column: 1, scope: !356)
!2576 = !DILocalVariable(name: "entry", arg: 1, scope: !357, file: !1, line: 1001, type: !5)
!2577 = !DILocation(line: 1001, column: 49, scope: !357)
!2578 = !DILocation(line: 1003, column: 26, scope: !357)
!2579 = !DILocation(line: 1003, column: 2, scope: !357)
!2580 = !DILocation(line: 1004, column: 2, scope: !357)
!2581 = !DILocation(line: 1004, column: 9, scope: !357)
!2582 = !DILocation(line: 1004, column: 16, scope: !357)
!2583 = !DILocation(line: 1005, column: 1, scope: !357)
!2584 = !DILocalVariable(name: "entry", arg: 1, scope: !358, file: !1, line: 1008, type: !5)
!2585 = !DILocation(line: 1008, column: 45, scope: !358)
!2586 = !DILocalVariable(name: "d", arg: 2, scope: !358, file: !1, line: 1008, type: !130)
!2587 = !DILocation(line: 1008, column: 58, scope: !358)
!2588 = !DILocation(line: 1010, column: 2, scope: !358)
!2589 = !DILocation(line: 1010, column: 9, scope: !358)
!2590 = !DILocation(line: 1010, column: 20, scope: !358)
!2591 = !DILocation(line: 1011, column: 2, scope: !358)
!2592 = !DILocation(line: 1011, column: 9, scope: !358)
!2593 = !DILocation(line: 1011, column: 16, scope: !358)
!2594 = !DILocation(line: 1012, column: 2, scope: !358)
!2595 = !DILocation(line: 1012, column: 9, scope: !358)
!2596 = !DILocation(line: 1012, column: 17, scope: !358)
!2597 = !DILocation(line: 1012, column: 41, scope: !358)
!2598 = !DILocation(line: 1013, column: 28, scope: !358)
!2599 = !DILocation(line: 1013, column: 2, scope: !358)
!2600 = !DILocation(line: 1013, column: 9, scope: !358)
!2601 = !DILocation(line: 1013, column: 17, scope: !358)
!2602 = !DILocation(line: 1013, column: 26, scope: !358)
!2603 = !DILocation(line: 1014, column: 1, scope: !358)
!2604 = !DILocalVariable(name: "entry", arg: 1, scope: !361, file: !1, line: 1017, type: !5)
!2605 = !DILocation(line: 1017, column: 50, scope: !361)
!2606 = !DILocalVariable(name: "m", arg: 2, scope: !361, file: !1, line: 1017, type: !130)
!2607 = !DILocation(line: 1017, column: 63, scope: !361)
!2608 = !DILocation(line: 1019, column: 2, scope: !361)
!2609 = !DILocation(line: 1019, column: 9, scope: !361)
!2610 = !DILocation(line: 1019, column: 20, scope: !361)
!2611 = !DILocation(line: 1020, column: 2, scope: !361)
!2612 = !DILocation(line: 1020, column: 9, scope: !361)
!2613 = !DILocation(line: 1020, column: 16, scope: !361)
!2614 = !DILocation(line: 1021, column: 2, scope: !361)
!2615 = !DILocation(line: 1021, column: 9, scope: !361)
!2616 = !DILocation(line: 1021, column: 17, scope: !361)
!2617 = !DILocation(line: 1021, column: 41, scope: !361)
!2618 = !DILocation(line: 1022, column: 33, scope: !361)
!2619 = !DILocation(line: 1022, column: 2, scope: !361)
!2620 = !DILocation(line: 1022, column: 9, scope: !361)
!2621 = !DILocation(line: 1022, column: 17, scope: !361)
!2622 = !DILocation(line: 1022, column: 31, scope: !361)
!2623 = !DILocation(line: 1023, column: 1, scope: !361)
!2624 = !DILocalVariable(name: "entry", arg: 1, scope: !362, file: !1, line: 1026, type: !5)
!2625 = !DILocation(line: 1026, column: 50, scope: !362)
!2626 = !DILocalVariable(name: "m", arg: 2, scope: !362, file: !1, line: 1026, type: !130)
!2627 = !DILocation(line: 1026, column: 63, scope: !362)
!2628 = !DILocation(line: 1028, column: 2, scope: !362)
!2629 = !DILocation(line: 1028, column: 9, scope: !362)
!2630 = !DILocation(line: 1028, column: 20, scope: !362)
!2631 = !DILocation(line: 1029, column: 2, scope: !362)
!2632 = !DILocation(line: 1029, column: 9, scope: !362)
!2633 = !DILocation(line: 1029, column: 16, scope: !362)
!2634 = !DILocation(line: 1030, column: 2, scope: !362)
!2635 = !DILocation(line: 1030, column: 9, scope: !362)
!2636 = !DILocation(line: 1030, column: 17, scope: !362)
!2637 = !DILocation(line: 1030, column: 41, scope: !362)
!2638 = !DILocation(line: 1031, column: 33, scope: !362)
!2639 = !DILocation(line: 1031, column: 2, scope: !362)
!2640 = !DILocation(line: 1031, column: 9, scope: !362)
!2641 = !DILocation(line: 1031, column: 17, scope: !362)
!2642 = !DILocation(line: 1031, column: 31, scope: !362)
!2643 = !DILocation(line: 1032, column: 1, scope: !362)
!2644 = !DILocalVariable(name: "entry", arg: 1, scope: !363, file: !1, line: 1036, type: !5)
!2645 = !DILocation(line: 1036, column: 46, scope: !363)
!2646 = !DILocalVariable(name: "target", arg: 2, scope: !363, file: !1, line: 1036, type: !78)
!2647 = !DILocation(line: 1036, column: 65, scope: !363)
!2648 = !DILocation(line: 1038, column: 6, scope: !2649)
!2649 = distinct !DILexicalBlock(scope: !363, file: !1, line: 1038, column: 6)
!2650 = !DILocation(line: 1038, column: 13, scope: !2649)
!2651 = !DILocation(line: 1038, column: 20, scope: !2649)
!2652 = !DILocation(line: 1038, column: 6, scope: !363)
!2653 = !DILocation(line: 1039, column: 29, scope: !2649)
!2654 = !DILocation(line: 1039, column: 36, scope: !2649)
!2655 = !DILocation(line: 1039, column: 48, scope: !2649)
!2656 = !DILocation(line: 1039, column: 3, scope: !2649)
!2657 = !DILocation(line: 1041, column: 29, scope: !2649)
!2658 = !DILocation(line: 1041, column: 36, scope: !2649)
!2659 = !DILocation(line: 1041, column: 49, scope: !2649)
!2660 = !DILocation(line: 1041, column: 3, scope: !2649)
!2661 = !DILocation(line: 1042, column: 1, scope: !363)
!2662 = !DILocalVariable(name: "entry", arg: 1, scope: !364, file: !1, line: 1045, type: !5)
!2663 = !DILocation(line: 1045, column: 51, scope: !364)
!2664 = !DILocalVariable(name: "target", arg: 2, scope: !364, file: !1, line: 1045, type: !78)
!2665 = !DILocation(line: 1045, column: 70, scope: !364)
!2666 = !DILocation(line: 1047, column: 6, scope: !2667)
!2667 = distinct !DILexicalBlock(scope: !364, file: !1, line: 1047, column: 6)
!2668 = !DILocation(line: 1047, column: 13, scope: !2667)
!2669 = !DILocation(line: 1047, column: 20, scope: !2667)
!2670 = !DILocation(line: 1047, column: 6, scope: !364)
!2671 = !DILocation(line: 1048, column: 30, scope: !2667)
!2672 = !DILocation(line: 1048, column: 37, scope: !2667)
!2673 = !DILocation(line: 1048, column: 49, scope: !2667)
!2674 = !DILocation(line: 1048, column: 3, scope: !2667)
!2675 = !DILocation(line: 1050, column: 30, scope: !2667)
!2676 = !DILocation(line: 1050, column: 37, scope: !2667)
!2677 = !DILocation(line: 1050, column: 50, scope: !2667)
!2678 = !DILocation(line: 1050, column: 3, scope: !2667)
!2679 = !DILocation(line: 1051, column: 1, scope: !364)
!2680 = !DILocalVariable(name: "entry", arg: 1, scope: !365, file: !1, line: 1055, type: !5)
!2681 = !DILocation(line: 1055, column: 47, scope: !365)
!2682 = !DILocalVariable(name: "target", arg: 2, scope: !365, file: !1, line: 1055, type: !78)
!2683 = !DILocation(line: 1055, column: 66, scope: !365)
!2684 = !DILocation(line: 1057, column: 6, scope: !2685)
!2685 = distinct !DILexicalBlock(scope: !365, file: !1, line: 1057, column: 6)
!2686 = !DILocation(line: 1057, column: 13, scope: !2685)
!2687 = !DILocation(line: 1057, column: 20, scope: !2685)
!2688 = !DILocation(line: 1057, column: 6, scope: !365)
!2689 = !DILocation(line: 1058, column: 29, scope: !2685)
!2690 = !DILocation(line: 1058, column: 36, scope: !2685)
!2691 = !DILocation(line: 1058, column: 48, scope: !2685)
!2692 = !DILocation(line: 1058, column: 3, scope: !2685)
!2693 = !DILocation(line: 1060, column: 29, scope: !2685)
!2694 = !DILocation(line: 1060, column: 36, scope: !2685)
!2695 = !DILocation(line: 1060, column: 49, scope: !2685)
!2696 = !DILocation(line: 1060, column: 3, scope: !2685)
!2697 = !DILocation(line: 1061, column: 1, scope: !365)
!2698 = !DILocalVariable(name: "entry", arg: 1, scope: !366, file: !1, line: 1065, type: !5)
!2699 = !DILocation(line: 1065, column: 49, scope: !366)
!2700 = !DILocalVariable(name: "target", arg: 2, scope: !366, file: !1, line: 1065, type: !269)
!2701 = !DILocation(line: 1065, column: 71, scope: !366)
!2702 = !DILocation(line: 1067, column: 6, scope: !2703)
!2703 = distinct !DILexicalBlock(scope: !366, file: !1, line: 1067, column: 6)
!2704 = !DILocation(line: 1067, column: 13, scope: !2703)
!2705 = !DILocation(line: 1067, column: 20, scope: !2703)
!2706 = !DILocation(line: 1067, column: 6, scope: !366)
!2707 = !DILocation(line: 1068, column: 29, scope: !2703)
!2708 = !DILocation(line: 1068, column: 36, scope: !2703)
!2709 = !DILocation(line: 1068, column: 48, scope: !2703)
!2710 = !DILocation(line: 1068, column: 3, scope: !2703)
!2711 = !DILocation(line: 1070, column: 29, scope: !2703)
!2712 = !DILocation(line: 1070, column: 36, scope: !2703)
!2713 = !DILocation(line: 1070, column: 49, scope: !2703)
!2714 = !DILocation(line: 1070, column: 3, scope: !2703)
!2715 = !DILocation(line: 1071, column: 1, scope: !366)
!2716 = !DILocalVariable(name: "entry", arg: 1, scope: !367, file: !1, line: 1074, type: !5)
!2717 = !DILocation(line: 1074, column: 54, scope: !367)
!2718 = !DILocalVariable(name: "target", arg: 2, scope: !367, file: !1, line: 1074, type: !78)
!2719 = !DILocation(line: 1074, column: 73, scope: !367)
!2720 = !DILocalVariable(name: "r", scope: !367, file: !1, line: 1076, type: !25)
!2721 = !DILocation(line: 1076, column: 6, scope: !367)
!2722 = !DILocation(line: 1077, column: 6, scope: !2723)
!2723 = distinct !DILexicalBlock(scope: !367, file: !1, line: 1077, column: 6)
!2724 = !DILocation(line: 1077, column: 13, scope: !2723)
!2725 = !DILocation(line: 1077, column: 20, scope: !2723)
!2726 = !DILocation(line: 1077, column: 6, scope: !367)
!2727 = !DILocation(line: 1078, column: 35, scope: !2723)
!2728 = !DILocation(line: 1078, column: 42, scope: !2723)
!2729 = !DILocation(line: 1079, column: 8, scope: !2723)
!2730 = !DILocation(line: 1079, column: 15, scope: !2723)
!2731 = !DILocation(line: 1079, column: 27, scope: !2723)
!2732 = !DILocation(line: 1078, column: 7, scope: !2723)
!2733 = !DILocation(line: 1078, column: 5, scope: !2723)
!2734 = !DILocation(line: 1078, column: 3, scope: !2723)
!2735 = !DILocation(line: 1081, column: 35, scope: !2723)
!2736 = !DILocation(line: 1081, column: 42, scope: !2723)
!2737 = !DILocation(line: 1082, column: 8, scope: !2723)
!2738 = !DILocation(line: 1082, column: 15, scope: !2723)
!2739 = !DILocation(line: 1082, column: 28, scope: !2723)
!2740 = !DILocation(line: 1081, column: 7, scope: !2723)
!2741 = !DILocation(line: 1081, column: 5, scope: !2723)
!2742 = !DILocation(line: 1083, column: 6, scope: !2743)
!2743 = distinct !DILexicalBlock(scope: !367, file: !1, line: 1083, column: 6)
!2744 = !DILocation(line: 1083, column: 8, scope: !2743)
!2745 = !DILocation(line: 1083, column: 6, scope: !367)
!2746 = !DILocation(line: 1084, column: 3, scope: !2743)
!2747 = !DILocation(line: 1085, column: 6, scope: !2748)
!2748 = distinct !DILexicalBlock(scope: !367, file: !1, line: 1085, column: 6)
!2749 = !DILocation(line: 1085, column: 12, scope: !2748)
!2750 = !DILocation(line: 1085, column: 6, scope: !367)
!2751 = !DILocation(line: 1086, column: 3, scope: !2748)
!2752 = !DILocation(line: 1087, column: 2, scope: !367)
!2753 = !DILocation(line: 1088, column: 1, scope: !367)
!2754 = !DILocalVariable(name: "entry", arg: 1, scope: !368, file: !1, line: 1091, type: !5)
!2755 = !DILocation(line: 1091, column: 50, scope: !368)
!2756 = !DILocalVariable(name: "target", arg: 2, scope: !368, file: !1, line: 1092, type: !78)
!2757 = !DILocation(line: 1092, column: 17, scope: !368)
!2758 = !DILocalVariable(name: "len", arg: 3, scope: !368, file: !1, line: 1092, type: !43)
!2759 = !DILocation(line: 1092, column: 32, scope: !368)
!2760 = !DILocalVariable(name: "sc", arg: 4, scope: !368, file: !1, line: 1092, type: !100)
!2761 = !DILocation(line: 1092, column: 65, scope: !368)
!2762 = !DILocalVariable(name: "r", scope: !368, file: !1, line: 1094, type: !25)
!2763 = !DILocation(line: 1094, column: 6, scope: !368)
!2764 = !DILocation(line: 1096, column: 6, scope: !2765)
!2765 = distinct !DILexicalBlock(scope: !368, file: !1, line: 1096, column: 6)
!2766 = !DILocation(line: 1096, column: 13, scope: !2765)
!2767 = !DILocation(line: 1096, column: 20, scope: !2765)
!2768 = !DILocation(line: 1096, column: 6, scope: !368)
!2769 = !DILocation(line: 1097, column: 39, scope: !2765)
!2770 = !DILocation(line: 1097, column: 46, scope: !2765)
!2771 = !DILocation(line: 1098, column: 7, scope: !2765)
!2772 = !DILocation(line: 1098, column: 15, scope: !2765)
!2773 = !DILocation(line: 1098, column: 20, scope: !2765)
!2774 = !DILocation(line: 1097, column: 7, scope: !2765)
!2775 = !DILocation(line: 1097, column: 5, scope: !2765)
!2776 = !DILocation(line: 1097, column: 3, scope: !2765)
!2777 = !DILocation(line: 1100, column: 39, scope: !2765)
!2778 = !DILocation(line: 1100, column: 46, scope: !2765)
!2779 = !DILocation(line: 1101, column: 7, scope: !2765)
!2780 = !DILocation(line: 1101, column: 15, scope: !2765)
!2781 = !DILocation(line: 1101, column: 20, scope: !2765)
!2782 = !DILocation(line: 1100, column: 7, scope: !2765)
!2783 = !DILocation(line: 1100, column: 5, scope: !2765)
!2784 = !DILocation(line: 1102, column: 10, scope: !368)
!2785 = !DILocation(line: 1102, column: 2, scope: !368)
!2786 = !DILocalVariable(name: "entry", arg: 1, scope: !369, file: !1, line: 1106, type: !5)
!2787 = !DILocation(line: 1106, column: 46, scope: !369)
!2788 = !DILocalVariable(name: "m", arg: 2, scope: !369, file: !1, line: 1106, type: !171)
!2789 = !DILocation(line: 1106, column: 60, scope: !369)
!2790 = !DILocation(line: 1108, column: 2, scope: !369)
!2791 = !DILocation(line: 1108, column: 9, scope: !369)
!2792 = !DILocation(line: 1108, column: 20, scope: !369)
!2793 = !DILocation(line: 1109, column: 20, scope: !369)
!2794 = !DILocation(line: 1109, column: 2, scope: !369)
!2795 = !DILocation(line: 1109, column: 9, scope: !369)
!2796 = !DILocation(line: 1109, column: 13, scope: !369)
!2797 = !DILocation(line: 1109, column: 18, scope: !369)
!2798 = !DILocation(line: 1110, column: 1, scope: !369)
!2799 = !DILocalVariable(name: "entry", arg: 1, scope: !372, file: !1, line: 1113, type: !5)
!2800 = !DILocation(line: 1113, column: 47, scope: !372)
!2801 = !DILocalVariable(name: "t", arg: 2, scope: !372, file: !1, line: 1113, type: !228)
!2802 = !DILocation(line: 1113, column: 61, scope: !372)
!2803 = !DILocalVariable(name: "ns", arg: 3, scope: !372, file: !1, line: 1113, type: !40)
!2804 = !DILocation(line: 1113, column: 69, scope: !372)
!2805 = !DILocation(line: 1115, column: 2, scope: !372)
!2806 = !DILocation(line: 1115, column: 2, scope: !2807)
!2807 = !DILexicalBlockFile(scope: !2808, file: !1, discriminator: 1)
!2808 = distinct !DILexicalBlock(scope: !372, file: !1, line: 1115, column: 2)
!2809 = !DILocation(line: 1115, column: 2, scope: !2810)
!2810 = !DILexicalBlockFile(scope: !2811, file: !1, discriminator: 2)
!2811 = distinct !DILexicalBlock(scope: !2812, file: !1, line: 1115, column: 2)
!2812 = distinct !DILexicalBlock(scope: !2808, file: !1, line: 1115, column: 2)
!2813 = !DILocation(line: 1115, column: 2, scope: !2814)
!2814 = !DILexicalBlockFile(scope: !2808, file: !1, discriminator: 3)
!2815 = !DILocation(line: 1116, column: 2, scope: !372)
!2816 = !DILocation(line: 1116, column: 9, scope: !372)
!2817 = !DILocation(line: 1116, column: 20, scope: !372)
!2818 = !DILocation(line: 1117, column: 2, scope: !372)
!2819 = !DILocation(line: 1117, column: 9, scope: !372)
!2820 = !DILocation(line: 1117, column: 16, scope: !372)
!2821 = !DILocation(line: 1118, column: 30, scope: !372)
!2822 = !DILocation(line: 1118, column: 2, scope: !372)
!2823 = !DILocation(line: 1118, column: 9, scope: !372)
!2824 = !DILocation(line: 1118, column: 17, scope: !372)
!2825 = !DILocation(line: 1118, column: 28, scope: !372)
!2826 = !DILocation(line: 1119, column: 35, scope: !372)
!2827 = !DILocation(line: 1119, column: 2, scope: !372)
!2828 = !DILocation(line: 1119, column: 9, scope: !372)
!2829 = !DILocation(line: 1119, column: 17, scope: !372)
!2830 = !DILocation(line: 1119, column: 33, scope: !372)
!2831 = !DILocation(line: 1120, column: 1, scope: !372)
!2832 = !DILocalVariable(name: "entry", arg: 1, scope: !373, file: !1, line: 1123, type: !5)
!2833 = !DILocation(line: 1123, column: 49, scope: !373)
!2834 = !DILocation(line: 1125, column: 26, scope: !373)
!2835 = !DILocation(line: 1125, column: 2, scope: !373)
!2836 = !DILocation(line: 1126, column: 2, scope: !373)
!2837 = !DILocation(line: 1126, column: 9, scope: !373)
!2838 = !DILocation(line: 1126, column: 16, scope: !373)
!2839 = !DILocation(line: 1127, column: 1, scope: !373)
!2840 = !DILocalVariable(name: "entry", arg: 1, scope: !374, file: !1, line: 1130, type: !5)
!2841 = !DILocation(line: 1130, column: 47, scope: !374)
!2842 = !DILocalVariable(name: "nlink", arg: 2, scope: !374, file: !1, line: 1130, type: !15)
!2843 = !DILocation(line: 1130, column: 67, scope: !374)
!2844 = !DILocation(line: 1132, column: 2, scope: !374)
!2845 = !DILocation(line: 1132, column: 9, scope: !374)
!2846 = !DILocation(line: 1132, column: 20, scope: !374)
!2847 = !DILocation(line: 1133, column: 30, scope: !374)
!2848 = !DILocation(line: 1133, column: 2, scope: !374)
!2849 = !DILocation(line: 1133, column: 9, scope: !374)
!2850 = !DILocation(line: 1133, column: 17, scope: !374)
!2851 = !DILocation(line: 1133, column: 28, scope: !374)
!2852 = !DILocation(line: 1134, column: 1, scope: !374)
!2853 = !DILocalVariable(name: "entry", arg: 1, scope: !375, file: !1, line: 1137, type: !5)
!2854 = !DILocation(line: 1137, column: 50, scope: !375)
!2855 = !DILocalVariable(name: "name", arg: 2, scope: !375, file: !1, line: 1137, type: !78)
!2856 = !DILocation(line: 1137, column: 69, scope: !375)
!2857 = !DILocation(line: 1139, column: 28, scope: !375)
!2858 = !DILocation(line: 1139, column: 35, scope: !375)
!2859 = !DILocation(line: 1139, column: 48, scope: !375)
!2860 = !DILocation(line: 1139, column: 2, scope: !375)
!2861 = !DILocation(line: 1140, column: 1, scope: !375)
!2862 = !DILocalVariable(name: "entry", arg: 1, scope: !376, file: !1, line: 1143, type: !5)
!2863 = !DILocation(line: 1143, column: 55, scope: !376)
!2864 = !DILocalVariable(name: "name", arg: 2, scope: !376, file: !1, line: 1143, type: !78)
!2865 = !DILocation(line: 1143, column: 74, scope: !376)
!2866 = !DILocation(line: 1145, column: 29, scope: !376)
!2867 = !DILocation(line: 1145, column: 36, scope: !376)
!2868 = !DILocation(line: 1145, column: 49, scope: !376)
!2869 = !DILocation(line: 1145, column: 2, scope: !376)
!2870 = !DILocation(line: 1146, column: 1, scope: !376)
!2871 = !DILocalVariable(name: "entry", arg: 1, scope: !377, file: !1, line: 1149, type: !5)
!2872 = !DILocation(line: 1149, column: 51, scope: !377)
!2873 = !DILocalVariable(name: "name", arg: 2, scope: !377, file: !1, line: 1149, type: !78)
!2874 = !DILocation(line: 1149, column: 70, scope: !377)
!2875 = !DILocation(line: 1151, column: 28, scope: !377)
!2876 = !DILocation(line: 1151, column: 35, scope: !377)
!2877 = !DILocation(line: 1151, column: 48, scope: !377)
!2878 = !DILocation(line: 1151, column: 2, scope: !377)
!2879 = !DILocation(line: 1152, column: 1, scope: !377)
!2880 = !DILocalVariable(name: "entry", arg: 1, scope: !378, file: !1, line: 1155, type: !5)
!2881 = !DILocation(line: 1155, column: 53, scope: !378)
!2882 = !DILocalVariable(name: "name", arg: 2, scope: !378, file: !1, line: 1155, type: !269)
!2883 = !DILocation(line: 1155, column: 75, scope: !378)
!2884 = !DILocation(line: 1157, column: 28, scope: !378)
!2885 = !DILocation(line: 1157, column: 35, scope: !378)
!2886 = !DILocation(line: 1157, column: 48, scope: !378)
!2887 = !DILocation(line: 1157, column: 2, scope: !378)
!2888 = !DILocation(line: 1158, column: 1, scope: !378)
!2889 = !DILocalVariable(name: "entry", arg: 1, scope: !379, file: !1, line: 1161, type: !5)
!2890 = !DILocation(line: 1161, column: 58, scope: !379)
!2891 = !DILocalVariable(name: "name", arg: 2, scope: !379, file: !1, line: 1161, type: !78)
!2892 = !DILocation(line: 1161, column: 77, scope: !379)
!2893 = !DILocation(line: 1163, column: 34, scope: !2894)
!2894 = distinct !DILexicalBlock(scope: !379, file: !1, line: 1163, column: 6)
!2895 = !DILocation(line: 1163, column: 41, scope: !2894)
!2896 = !DILocation(line: 1164, column: 7, scope: !2894)
!2897 = !DILocation(line: 1164, column: 14, scope: !2894)
!2898 = !DILocation(line: 1164, column: 27, scope: !2894)
!2899 = !DILocation(line: 1163, column: 6, scope: !2894)
!2900 = !DILocation(line: 1164, column: 33, scope: !2894)
!2901 = !DILocation(line: 1163, column: 6, scope: !379)
!2902 = !DILocation(line: 1165, column: 3, scope: !2894)
!2903 = !DILocation(line: 1166, column: 6, scope: !2904)
!2904 = distinct !DILexicalBlock(scope: !379, file: !1, line: 1166, column: 6)
!2905 = !DILocation(line: 1166, column: 12, scope: !2904)
!2906 = !DILocation(line: 1166, column: 6, scope: !379)
!2907 = !DILocation(line: 1167, column: 3, scope: !2904)
!2908 = !DILocation(line: 1168, column: 2, scope: !379)
!2909 = !DILocation(line: 1169, column: 1, scope: !379)
!2910 = !DILocalVariable(name: "entry", arg: 1, scope: !380, file: !1, line: 1172, type: !5)
!2911 = !DILocation(line: 1172, column: 54, scope: !380)
!2912 = !DILocalVariable(name: "name", arg: 2, scope: !380, file: !1, line: 1173, type: !78)
!2913 = !DILocation(line: 1173, column: 17, scope: !380)
!2914 = !DILocalVariable(name: "len", arg: 3, scope: !380, file: !1, line: 1173, type: !43)
!2915 = !DILocation(line: 1173, column: 30, scope: !380)
!2916 = !DILocalVariable(name: "sc", arg: 4, scope: !380, file: !1, line: 1173, type: !100)
!2917 = !DILocation(line: 1173, column: 63, scope: !380)
!2918 = !DILocation(line: 1175, column: 42, scope: !380)
!2919 = !DILocation(line: 1175, column: 49, scope: !380)
!2920 = !DILocation(line: 1176, column: 6, scope: !380)
!2921 = !DILocation(line: 1176, column: 12, scope: !380)
!2922 = !DILocation(line: 1176, column: 17, scope: !380)
!2923 = !DILocation(line: 1175, column: 10, scope: !380)
!2924 = !DILocation(line: 1175, column: 2, scope: !380)
!2925 = !DILocalVariable(name: "entry", arg: 1, scope: !381, file: !1, line: 1180, type: !5)
!2926 = !DILocation(line: 1180, column: 46, scope: !381)
!2927 = !DILocalVariable(name: "p", arg: 2, scope: !381, file: !1, line: 1180, type: !171)
!2928 = !DILocation(line: 1180, column: 60, scope: !381)
!2929 = !DILocation(line: 1182, column: 2, scope: !381)
!2930 = !DILocation(line: 1182, column: 9, scope: !381)
!2931 = !DILocation(line: 1182, column: 20, scope: !381)
!2932 = !DILocation(line: 1183, column: 2, scope: !381)
!2933 = !DILocation(line: 1183, column: 9, scope: !381)
!2934 = !DILocation(line: 1183, column: 13, scope: !381)
!2935 = !DILocation(line: 1183, column: 18, scope: !381)
!2936 = !DILocation(line: 1184, column: 32, scope: !381)
!2937 = !DILocation(line: 1184, column: 30, scope: !381)
!2938 = !DILocation(line: 1184, column: 2, scope: !381)
!2939 = !DILocation(line: 1184, column: 9, scope: !381)
!2940 = !DILocation(line: 1184, column: 13, scope: !381)
!2941 = !DILocation(line: 1184, column: 18, scope: !381)
!2942 = !DILocation(line: 1185, column: 1, scope: !381)
!2943 = !DILocalVariable(name: "entry", arg: 1, scope: !382, file: !1, line: 1188, type: !5)
!2944 = !DILocation(line: 1188, column: 46, scope: !382)
!2945 = !DILocalVariable(name: "m", arg: 2, scope: !382, file: !1, line: 1188, type: !130)
!2946 = !DILocation(line: 1188, column: 59, scope: !382)
!2947 = !DILocation(line: 1190, column: 2, scope: !382)
!2948 = !DILocation(line: 1190, column: 9, scope: !382)
!2949 = !DILocation(line: 1190, column: 20, scope: !382)
!2950 = !DILocation(line: 1191, column: 29, scope: !382)
!2951 = !DILocation(line: 1191, column: 2, scope: !382)
!2952 = !DILocation(line: 1191, column: 9, scope: !382)
!2953 = !DILocation(line: 1191, column: 17, scope: !382)
!2954 = !DILocation(line: 1191, column: 27, scope: !382)
!2955 = !DILocation(line: 1192, column: 2, scope: !382)
!2956 = !DILocation(line: 1192, column: 9, scope: !382)
!2957 = !DILocation(line: 1192, column: 17, scope: !382)
!2958 = !DILocation(line: 1192, column: 42, scope: !382)
!2959 = !DILocation(line: 1193, column: 1, scope: !382)
!2960 = !DILocalVariable(name: "entry", arg: 1, scope: !383, file: !1, line: 1196, type: !5)
!2961 = !DILocation(line: 1196, column: 51, scope: !383)
!2962 = !DILocalVariable(name: "m", arg: 2, scope: !383, file: !1, line: 1196, type: !130)
!2963 = !DILocation(line: 1196, column: 64, scope: !383)
!2964 = !DILocation(line: 1198, column: 2, scope: !383)
!2965 = !DILocation(line: 1198, column: 9, scope: !383)
!2966 = !DILocation(line: 1198, column: 20, scope: !383)
!2967 = !DILocation(line: 1199, column: 2, scope: !383)
!2968 = !DILocation(line: 1199, column: 9, scope: !383)
!2969 = !DILocation(line: 1199, column: 17, scope: !383)
!2970 = !DILocation(line: 1199, column: 42, scope: !383)
!2971 = !DILocation(line: 1200, column: 34, scope: !383)
!2972 = !DILocation(line: 1200, column: 2, scope: !383)
!2973 = !DILocation(line: 1200, column: 9, scope: !383)
!2974 = !DILocation(line: 1200, column: 17, scope: !383)
!2975 = !DILocation(line: 1200, column: 32, scope: !383)
!2976 = !DILocation(line: 1201, column: 1, scope: !383)
!2977 = !DILocalVariable(name: "entry", arg: 1, scope: !384, file: !1, line: 1204, type: !5)
!2978 = !DILocation(line: 1204, column: 51, scope: !384)
!2979 = !DILocalVariable(name: "m", arg: 2, scope: !384, file: !1, line: 1204, type: !130)
!2980 = !DILocation(line: 1204, column: 64, scope: !384)
!2981 = !DILocation(line: 1206, column: 2, scope: !384)
!2982 = !DILocation(line: 1206, column: 9, scope: !384)
!2983 = !DILocation(line: 1206, column: 20, scope: !384)
!2984 = !DILocation(line: 1207, column: 2, scope: !384)
!2985 = !DILocation(line: 1207, column: 9, scope: !384)
!2986 = !DILocation(line: 1207, column: 17, scope: !384)
!2987 = !DILocation(line: 1207, column: 42, scope: !384)
!2988 = !DILocation(line: 1208, column: 34, scope: !384)
!2989 = !DILocation(line: 1208, column: 2, scope: !384)
!2990 = !DILocation(line: 1208, column: 9, scope: !384)
!2991 = !DILocation(line: 1208, column: 17, scope: !384)
!2992 = !DILocation(line: 1208, column: 32, scope: !384)
!2993 = !DILocation(line: 1209, column: 1, scope: !384)
!2994 = !DILocalVariable(name: "entry", arg: 1, scope: !385, file: !1, line: 1212, type: !5)
!2995 = !DILocation(line: 1212, column: 46, scope: !385)
!2996 = !DILocalVariable(name: "s", arg: 2, scope: !385, file: !1, line: 1212, type: !50)
!2997 = !DILocation(line: 1212, column: 61, scope: !385)
!2998 = !DILocation(line: 1214, column: 2, scope: !385)
!2999 = !DILocation(line: 1214, column: 9, scope: !385)
!3000 = !DILocation(line: 1214, column: 20, scope: !385)
!3001 = !DILocation(line: 1215, column: 29, scope: !385)
!3002 = !DILocation(line: 1215, column: 2, scope: !385)
!3003 = !DILocation(line: 1215, column: 9, scope: !385)
!3004 = !DILocation(line: 1215, column: 17, scope: !385)
!3005 = !DILocation(line: 1215, column: 27, scope: !385)
!3006 = !DILocation(line: 1216, column: 2, scope: !385)
!3007 = !DILocation(line: 1216, column: 9, scope: !385)
!3008 = !DILocation(line: 1216, column: 16, scope: !385)
!3009 = !DILocation(line: 1217, column: 1, scope: !385)
!3010 = !DILocalVariable(name: "entry", arg: 1, scope: !386, file: !1, line: 1220, type: !5)
!3011 = !DILocation(line: 1220, column: 48, scope: !386)
!3012 = !DILocation(line: 1222, column: 25, scope: !386)
!3013 = !DILocation(line: 1222, column: 2, scope: !386)
!3014 = !DILocation(line: 1223, column: 2, scope: !386)
!3015 = !DILocation(line: 1223, column: 9, scope: !386)
!3016 = !DILocation(line: 1223, column: 16, scope: !386)
!3017 = !DILocation(line: 1224, column: 1, scope: !386)
!3018 = !DILocalVariable(name: "entry", arg: 1, scope: !387, file: !1, line: 1227, type: !5)
!3019 = !DILocation(line: 1227, column: 53, scope: !387)
!3020 = !DILocalVariable(name: "path", arg: 2, scope: !387, file: !1, line: 1227, type: !78)
!3021 = !DILocation(line: 1227, column: 72, scope: !387)
!3022 = !DILocation(line: 1229, column: 28, scope: !387)
!3023 = !DILocation(line: 1229, column: 35, scope: !387)
!3024 = !DILocation(line: 1229, column: 50, scope: !387)
!3025 = !DILocation(line: 1229, column: 2, scope: !387)
!3026 = !DILocation(line: 1230, column: 1, scope: !387)
!3027 = !DILocalVariable(name: "entry", arg: 1, scope: !388, file: !1, line: 1233, type: !5)
!3028 = !DILocation(line: 1233, column: 55, scope: !388)
!3029 = !DILocalVariable(name: "path", arg: 2, scope: !388, file: !1, line: 1233, type: !269)
!3030 = !DILocation(line: 1233, column: 77, scope: !388)
!3031 = !DILocation(line: 1235, column: 28, scope: !388)
!3032 = !DILocation(line: 1235, column: 35, scope: !388)
!3033 = !DILocation(line: 1235, column: 50, scope: !388)
!3034 = !DILocation(line: 1235, column: 2, scope: !388)
!3035 = !DILocation(line: 1236, column: 1, scope: !388)
!3036 = !DILocalVariable(name: "entry", arg: 1, scope: !389, file: !1, line: 1239, type: !5)
!3037 = !DILocation(line: 1239, column: 49, scope: !389)
!3038 = !DILocalVariable(name: "linkname", arg: 2, scope: !389, file: !1, line: 1239, type: !78)
!3039 = !DILocation(line: 1239, column: 68, scope: !389)
!3040 = !DILocation(line: 1241, column: 28, scope: !389)
!3041 = !DILocation(line: 1241, column: 35, scope: !389)
!3042 = !DILocation(line: 1241, column: 47, scope: !389)
!3043 = !DILocation(line: 1241, column: 2, scope: !389)
!3044 = !DILocation(line: 1242, column: 6, scope: !3045)
!3045 = distinct !DILexicalBlock(scope: !389, file: !1, line: 1242, column: 6)
!3046 = !DILocation(line: 1242, column: 15, scope: !3045)
!3047 = !DILocation(line: 1242, column: 6, scope: !389)
!3048 = !DILocation(line: 1243, column: 3, scope: !3045)
!3049 = !DILocation(line: 1243, column: 10, scope: !3045)
!3050 = !DILocation(line: 1243, column: 17, scope: !3045)
!3051 = !DILocation(line: 1245, column: 3, scope: !3045)
!3052 = !DILocation(line: 1245, column: 10, scope: !3045)
!3053 = !DILocation(line: 1245, column: 17, scope: !3045)
!3054 = !DILocation(line: 1246, column: 1, scope: !389)
!3055 = !DILocalVariable(name: "entry", arg: 1, scope: !390, file: !1, line: 1249, type: !5)
!3056 = !DILocation(line: 1249, column: 54, scope: !390)
!3057 = !DILocalVariable(name: "linkname", arg: 2, scope: !390, file: !1, line: 1249, type: !78)
!3058 = !DILocation(line: 1249, column: 73, scope: !390)
!3059 = !DILocation(line: 1251, column: 29, scope: !390)
!3060 = !DILocation(line: 1251, column: 36, scope: !390)
!3061 = !DILocation(line: 1251, column: 48, scope: !390)
!3062 = !DILocation(line: 1251, column: 2, scope: !390)
!3063 = !DILocation(line: 1252, column: 6, scope: !3064)
!3064 = distinct !DILexicalBlock(scope: !390, file: !1, line: 1252, column: 6)
!3065 = !DILocation(line: 1252, column: 15, scope: !3064)
!3066 = !DILocation(line: 1252, column: 6, scope: !390)
!3067 = !DILocation(line: 1253, column: 3, scope: !3064)
!3068 = !DILocation(line: 1253, column: 10, scope: !3064)
!3069 = !DILocation(line: 1253, column: 17, scope: !3064)
!3070 = !DILocation(line: 1255, column: 3, scope: !3064)
!3071 = !DILocation(line: 1255, column: 10, scope: !3064)
!3072 = !DILocation(line: 1255, column: 17, scope: !3064)
!3073 = !DILocation(line: 1256, column: 1, scope: !390)
!3074 = !DILocalVariable(name: "entry", arg: 1, scope: !391, file: !1, line: 1259, type: !5)
!3075 = !DILocation(line: 1259, column: 50, scope: !391)
!3076 = !DILocalVariable(name: "linkname", arg: 2, scope: !391, file: !1, line: 1259, type: !78)
!3077 = !DILocation(line: 1259, column: 69, scope: !391)
!3078 = !DILocation(line: 1261, column: 28, scope: !391)
!3079 = !DILocation(line: 1261, column: 35, scope: !391)
!3080 = !DILocation(line: 1261, column: 47, scope: !391)
!3081 = !DILocation(line: 1261, column: 2, scope: !391)
!3082 = !DILocation(line: 1262, column: 6, scope: !3083)
!3083 = distinct !DILexicalBlock(scope: !391, file: !1, line: 1262, column: 6)
!3084 = !DILocation(line: 1262, column: 15, scope: !3083)
!3085 = !DILocation(line: 1262, column: 6, scope: !391)
!3086 = !DILocation(line: 1263, column: 3, scope: !3083)
!3087 = !DILocation(line: 1263, column: 10, scope: !3083)
!3088 = !DILocation(line: 1263, column: 17, scope: !3083)
!3089 = !DILocation(line: 1265, column: 3, scope: !3083)
!3090 = !DILocation(line: 1265, column: 10, scope: !3083)
!3091 = !DILocation(line: 1265, column: 17, scope: !3083)
!3092 = !DILocation(line: 1266, column: 1, scope: !391)
!3093 = !DILocalVariable(name: "entry", arg: 1, scope: !392, file: !1, line: 1269, type: !5)
!3094 = !DILocation(line: 1269, column: 52, scope: !392)
!3095 = !DILocalVariable(name: "linkname", arg: 2, scope: !392, file: !1, line: 1269, type: !269)
!3096 = !DILocation(line: 1269, column: 74, scope: !392)
!3097 = !DILocation(line: 1271, column: 28, scope: !392)
!3098 = !DILocation(line: 1271, column: 35, scope: !392)
!3099 = !DILocation(line: 1271, column: 47, scope: !392)
!3100 = !DILocation(line: 1271, column: 2, scope: !392)
!3101 = !DILocation(line: 1272, column: 6, scope: !3102)
!3102 = distinct !DILexicalBlock(scope: !392, file: !1, line: 1272, column: 6)
!3103 = !DILocation(line: 1272, column: 15, scope: !3102)
!3104 = !DILocation(line: 1272, column: 6, scope: !392)
!3105 = !DILocation(line: 1273, column: 3, scope: !3102)
!3106 = !DILocation(line: 1273, column: 10, scope: !3102)
!3107 = !DILocation(line: 1273, column: 17, scope: !3102)
!3108 = !DILocation(line: 1275, column: 3, scope: !3102)
!3109 = !DILocation(line: 1275, column: 10, scope: !3102)
!3110 = !DILocation(line: 1275, column: 17, scope: !3102)
!3111 = !DILocation(line: 1276, column: 1, scope: !392)
!3112 = !DILocalVariable(name: "entry", arg: 1, scope: !393, file: !1, line: 1279, type: !5)
!3113 = !DILocation(line: 1279, column: 57, scope: !393)
!3114 = !DILocalVariable(name: "linkname", arg: 2, scope: !393, file: !1, line: 1279, type: !78)
!3115 = !DILocation(line: 1279, column: 76, scope: !393)
!3116 = !DILocation(line: 1281, column: 6, scope: !3117)
!3117 = distinct !DILexicalBlock(scope: !393, file: !1, line: 1281, column: 6)
!3118 = !DILocation(line: 1281, column: 15, scope: !3117)
!3119 = !DILocation(line: 1281, column: 6, scope: !393)
!3120 = !DILocation(line: 1282, column: 3, scope: !3117)
!3121 = !DILocation(line: 1282, column: 10, scope: !3117)
!3122 = !DILocation(line: 1282, column: 17, scope: !3117)
!3123 = !DILocation(line: 1284, column: 3, scope: !3117)
!3124 = !DILocation(line: 1284, column: 10, scope: !3117)
!3125 = !DILocation(line: 1284, column: 17, scope: !3117)
!3126 = !DILocation(line: 1285, column: 34, scope: !3127)
!3127 = distinct !DILexicalBlock(scope: !393, file: !1, line: 1285, column: 6)
!3128 = !DILocation(line: 1285, column: 41, scope: !3127)
!3129 = !DILocation(line: 1286, column: 7, scope: !3127)
!3130 = !DILocation(line: 1286, column: 14, scope: !3127)
!3131 = !DILocation(line: 1286, column: 26, scope: !3127)
!3132 = !DILocation(line: 1285, column: 6, scope: !3127)
!3133 = !DILocation(line: 1286, column: 36, scope: !3127)
!3134 = !DILocation(line: 1285, column: 6, scope: !393)
!3135 = !DILocation(line: 1287, column: 3, scope: !3127)
!3136 = !DILocation(line: 1288, column: 6, scope: !3137)
!3137 = distinct !DILexicalBlock(scope: !393, file: !1, line: 1288, column: 6)
!3138 = !DILocation(line: 1288, column: 12, scope: !3137)
!3139 = !DILocation(line: 1288, column: 6, scope: !393)
!3140 = !DILocation(line: 1289, column: 3, scope: !3137)
!3141 = !DILocation(line: 1290, column: 2, scope: !393)
!3142 = !DILocation(line: 1291, column: 1, scope: !393)
!3143 = !DILocalVariable(name: "entry", arg: 1, scope: !394, file: !1, line: 1294, type: !5)
!3144 = !DILocation(line: 1294, column: 53, scope: !394)
!3145 = !DILocalVariable(name: "linkname", arg: 2, scope: !394, file: !1, line: 1295, type: !78)
!3146 = !DILocation(line: 1295, column: 17, scope: !394)
!3147 = !DILocalVariable(name: "len", arg: 3, scope: !394, file: !1, line: 1295, type: !43)
!3148 = !DILocation(line: 1295, column: 34, scope: !394)
!3149 = !DILocalVariable(name: "sc", arg: 4, scope: !394, file: !1, line: 1295, type: !100)
!3150 = !DILocation(line: 1295, column: 67, scope: !394)
!3151 = !DILocalVariable(name: "r", scope: !394, file: !1, line: 1297, type: !25)
!3152 = !DILocation(line: 1297, column: 6, scope: !394)
!3153 = !DILocation(line: 1299, column: 38, scope: !394)
!3154 = !DILocation(line: 1299, column: 45, scope: !394)
!3155 = !DILocation(line: 1300, column: 6, scope: !394)
!3156 = !DILocation(line: 1300, column: 16, scope: !394)
!3157 = !DILocation(line: 1300, column: 21, scope: !394)
!3158 = !DILocation(line: 1299, column: 6, scope: !394)
!3159 = !DILocation(line: 1299, column: 4, scope: !394)
!3160 = !DILocation(line: 1301, column: 6, scope: !3161)
!3161 = distinct !DILexicalBlock(scope: !394, file: !1, line: 1301, column: 6)
!3162 = !DILocation(line: 1301, column: 15, scope: !3161)
!3163 = !DILocation(line: 1301, column: 23, scope: !3161)
!3164 = !DILocation(line: 1301, column: 26, scope: !3165)
!3165 = !DILexicalBlockFile(scope: !3161, file: !1, discriminator: 1)
!3166 = !DILocation(line: 1301, column: 28, scope: !3165)
!3167 = !DILocation(line: 1301, column: 6, scope: !3165)
!3168 = !DILocation(line: 1302, column: 3, scope: !3161)
!3169 = !DILocation(line: 1302, column: 10, scope: !3161)
!3170 = !DILocation(line: 1302, column: 17, scope: !3161)
!3171 = !DILocation(line: 1304, column: 3, scope: !3161)
!3172 = !DILocation(line: 1304, column: 10, scope: !3161)
!3173 = !DILocation(line: 1304, column: 17, scope: !3161)
!3174 = !DILocation(line: 1305, column: 10, scope: !394)
!3175 = !DILocation(line: 1305, column: 2, scope: !394)
!3176 = !DILocalVariable(name: "entry", arg: 1, scope: !395, file: !1, line: 1309, type: !5)
!3177 = !DILocation(line: 1309, column: 45, scope: !395)
!3178 = !DILocalVariable(name: "u", arg: 2, scope: !395, file: !1, line: 1309, type: !50)
!3179 = !DILocation(line: 1309, column: 60, scope: !395)
!3180 = !DILocation(line: 1311, column: 2, scope: !395)
!3181 = !DILocation(line: 1311, column: 9, scope: !395)
!3182 = !DILocation(line: 1311, column: 20, scope: !395)
!3183 = !DILocation(line: 1312, column: 28, scope: !395)
!3184 = !DILocation(line: 1312, column: 2, scope: !395)
!3185 = !DILocation(line: 1312, column: 9, scope: !395)
!3186 = !DILocation(line: 1312, column: 17, scope: !395)
!3187 = !DILocation(line: 1312, column: 26, scope: !395)
!3188 = !DILocation(line: 1313, column: 1, scope: !395)
!3189 = !DILocalVariable(name: "entry", arg: 1, scope: !396, file: !1, line: 1316, type: !5)
!3190 = !DILocation(line: 1316, column: 47, scope: !396)
!3191 = !DILocalVariable(name: "name", arg: 2, scope: !396, file: !1, line: 1316, type: !78)
!3192 = !DILocation(line: 1316, column: 66, scope: !396)
!3193 = !DILocation(line: 1318, column: 28, scope: !396)
!3194 = !DILocation(line: 1318, column: 35, scope: !396)
!3195 = !DILocation(line: 1318, column: 45, scope: !396)
!3196 = !DILocation(line: 1318, column: 2, scope: !396)
!3197 = !DILocation(line: 1319, column: 1, scope: !396)
!3198 = !DILocalVariable(name: "entry", arg: 1, scope: !397, file: !1, line: 1322, type: !5)
!3199 = !DILocation(line: 1322, column: 52, scope: !397)
!3200 = !DILocalVariable(name: "name", arg: 2, scope: !397, file: !1, line: 1322, type: !78)
!3201 = !DILocation(line: 1322, column: 71, scope: !397)
!3202 = !DILocation(line: 1324, column: 29, scope: !397)
!3203 = !DILocation(line: 1324, column: 36, scope: !397)
!3204 = !DILocation(line: 1324, column: 46, scope: !397)
!3205 = !DILocation(line: 1324, column: 2, scope: !397)
!3206 = !DILocation(line: 1325, column: 1, scope: !397)
!3207 = !DILocalVariable(name: "entry", arg: 1, scope: !398, file: !1, line: 1328, type: !5)
!3208 = !DILocation(line: 1328, column: 48, scope: !398)
!3209 = !DILocalVariable(name: "name", arg: 2, scope: !398, file: !1, line: 1328, type: !78)
!3210 = !DILocation(line: 1328, column: 67, scope: !398)
!3211 = !DILocation(line: 1330, column: 28, scope: !398)
!3212 = !DILocation(line: 1330, column: 35, scope: !398)
!3213 = !DILocation(line: 1330, column: 45, scope: !398)
!3214 = !DILocation(line: 1330, column: 2, scope: !398)
!3215 = !DILocation(line: 1331, column: 1, scope: !398)
!3216 = !DILocalVariable(name: "entry", arg: 1, scope: !399, file: !1, line: 1334, type: !5)
!3217 = !DILocation(line: 1334, column: 50, scope: !399)
!3218 = !DILocalVariable(name: "name", arg: 2, scope: !399, file: !1, line: 1334, type: !269)
!3219 = !DILocation(line: 1334, column: 72, scope: !399)
!3220 = !DILocation(line: 1336, column: 28, scope: !399)
!3221 = !DILocation(line: 1336, column: 35, scope: !399)
!3222 = !DILocation(line: 1336, column: 45, scope: !399)
!3223 = !DILocation(line: 1336, column: 2, scope: !399)
!3224 = !DILocation(line: 1337, column: 1, scope: !399)
!3225 = !DILocalVariable(name: "entry", arg: 1, scope: !400, file: !1, line: 1340, type: !5)
!3226 = !DILocation(line: 1340, column: 55, scope: !400)
!3227 = !DILocalVariable(name: "name", arg: 2, scope: !400, file: !1, line: 1340, type: !78)
!3228 = !DILocation(line: 1340, column: 74, scope: !400)
!3229 = !DILocation(line: 1342, column: 34, scope: !3230)
!3230 = distinct !DILexicalBlock(scope: !400, file: !1, line: 1342, column: 6)
!3231 = !DILocation(line: 1342, column: 41, scope: !3230)
!3232 = !DILocation(line: 1343, column: 7, scope: !3230)
!3233 = !DILocation(line: 1343, column: 14, scope: !3230)
!3234 = !DILocation(line: 1343, column: 24, scope: !3230)
!3235 = !DILocation(line: 1342, column: 6, scope: !3230)
!3236 = !DILocation(line: 1343, column: 30, scope: !3230)
!3237 = !DILocation(line: 1342, column: 6, scope: !400)
!3238 = !DILocation(line: 1344, column: 3, scope: !3230)
!3239 = !DILocation(line: 1345, column: 6, scope: !3240)
!3240 = distinct !DILexicalBlock(scope: !400, file: !1, line: 1345, column: 6)
!3241 = !DILocation(line: 1345, column: 12, scope: !3240)
!3242 = !DILocation(line: 1345, column: 6, scope: !400)
!3243 = !DILocation(line: 1346, column: 3, scope: !3240)
!3244 = !DILocation(line: 1347, column: 2, scope: !400)
!3245 = !DILocation(line: 1348, column: 1, scope: !400)
!3246 = !DILocalVariable(name: "entry", arg: 1, scope: !401, file: !1, line: 1351, type: !5)
!3247 = !DILocation(line: 1351, column: 59, scope: !401)
!3248 = !DILocalVariable(name: "is_encrypted", arg: 2, scope: !401, file: !1, line: 1351, type: !80)
!3249 = !DILocation(line: 1351, column: 71, scope: !401)
!3250 = !DILocation(line: 1353, column: 6, scope: !3251)
!3251 = distinct !DILexicalBlock(scope: !401, file: !1, line: 1353, column: 6)
!3252 = !DILocation(line: 1353, column: 6, scope: !401)
!3253 = !DILocation(line: 1354, column: 3, scope: !3254)
!3254 = distinct !DILexicalBlock(scope: !3251, file: !1, line: 1353, column: 20)
!3255 = !DILocation(line: 1354, column: 10, scope: !3254)
!3256 = !DILocation(line: 1354, column: 21, scope: !3254)
!3257 = !DILocation(line: 1355, column: 2, scope: !3254)
!3258 = !DILocation(line: 1356, column: 3, scope: !3259)
!3259 = distinct !DILexicalBlock(scope: !3251, file: !1, line: 1355, column: 9)
!3260 = !DILocation(line: 1356, column: 10, scope: !3259)
!3261 = !DILocation(line: 1356, column: 21, scope: !3259)
!3262 = !DILocation(line: 1358, column: 1, scope: !401)
!3263 = !DILocalVariable(name: "entry", arg: 1, scope: !404, file: !1, line: 1361, type: !5)
!3264 = !DILocation(line: 1361, column: 63, scope: !404)
!3265 = !DILocalVariable(name: "is_encrypted", arg: 2, scope: !404, file: !1, line: 1361, type: !80)
!3266 = !DILocation(line: 1361, column: 75, scope: !404)
!3267 = !DILocation(line: 1363, column: 6, scope: !3268)
!3268 = distinct !DILexicalBlock(scope: !404, file: !1, line: 1363, column: 6)
!3269 = !DILocation(line: 1363, column: 6, scope: !404)
!3270 = !DILocation(line: 1364, column: 3, scope: !3271)
!3271 = distinct !DILexicalBlock(scope: !3268, file: !1, line: 1363, column: 20)
!3272 = !DILocation(line: 1364, column: 10, scope: !3271)
!3273 = !DILocation(line: 1364, column: 21, scope: !3271)
!3274 = !DILocation(line: 1365, column: 2, scope: !3271)
!3275 = !DILocation(line: 1366, column: 3, scope: !3276)
!3276 = distinct !DILexicalBlock(scope: !3268, file: !1, line: 1365, column: 9)
!3277 = !DILocation(line: 1366, column: 10, scope: !3276)
!3278 = !DILocation(line: 1366, column: 21, scope: !3276)
!3279 = !DILocation(line: 1368, column: 1, scope: !404)
!3280 = !DILocalVariable(name: "entry", arg: 1, scope: !405, file: !1, line: 1371, type: !5)
!3281 = !DILocation(line: 1371, column: 51, scope: !405)
!3282 = !DILocalVariable(name: "name", arg: 2, scope: !405, file: !1, line: 1372, type: !78)
!3283 = !DILocation(line: 1372, column: 17, scope: !405)
!3284 = !DILocalVariable(name: "len", arg: 3, scope: !405, file: !1, line: 1372, type: !43)
!3285 = !DILocation(line: 1372, column: 30, scope: !405)
!3286 = !DILocalVariable(name: "sc", arg: 4, scope: !405, file: !1, line: 1372, type: !100)
!3287 = !DILocation(line: 1372, column: 63, scope: !405)
!3288 = !DILocation(line: 1374, column: 42, scope: !405)
!3289 = !DILocation(line: 1374, column: 49, scope: !405)
!3290 = !DILocation(line: 1375, column: 6, scope: !405)
!3291 = !DILocation(line: 1375, column: 12, scope: !405)
!3292 = !DILocation(line: 1375, column: 17, scope: !405)
!3293 = !DILocation(line: 1374, column: 10, scope: !405)
!3294 = !DILocation(line: 1374, column: 2, scope: !405)
!3295 = !DILocalVariable(name: "entry", arg: 1, scope: !412, file: !1, line: 1412, type: !5)
!3296 = !DILocation(line: 1412, column: 41, scope: !412)
!3297 = !DILocation(line: 1414, column: 10, scope: !412)
!3298 = !DILocation(line: 1414, column: 17, scope: !412)
!3299 = !DILocation(line: 1414, column: 2, scope: !412)
!3300 = !DILocalVariable(name: "entry", arg: 1, scope: !416, file: !1, line: 1418, type: !5)
!3301 = !DILocation(line: 1418, column: 47, scope: !416)
!3302 = !DILocation(line: 1420, column: 21, scope: !416)
!3303 = !DILocation(line: 1420, column: 28, scope: !416)
!3304 = !DILocation(line: 1420, column: 2, scope: !416)
!3305 = !DILocation(line: 1421, column: 1, scope: !416)
!3306 = !DILocalVariable(name: "entry", arg: 1, scope: !417, file: !1, line: 1427, type: !5)
!3307 = !DILocation(line: 1427, column: 51, scope: !417)
!3308 = !DILocalVariable(name: "type", arg: 2, scope: !417, file: !1, line: 1428, type: !25)
!3309 = !DILocation(line: 1428, column: 9, scope: !417)
!3310 = !DILocalVariable(name: "permset", arg: 3, scope: !417, file: !1, line: 1428, type: !25)
!3311 = !DILocation(line: 1428, column: 19, scope: !417)
!3312 = !DILocalVariable(name: "tag", arg: 4, scope: !417, file: !1, line: 1428, type: !25)
!3313 = !DILocation(line: 1428, column: 32, scope: !417)
!3314 = !DILocalVariable(name: "id", arg: 5, scope: !417, file: !1, line: 1428, type: !25)
!3315 = !DILocation(line: 1428, column: 41, scope: !417)
!3316 = !DILocalVariable(name: "name", arg: 6, scope: !417, file: !1, line: 1428, type: !78)
!3317 = !DILocation(line: 1428, column: 57, scope: !417)
!3318 = !DILocation(line: 1430, column: 32, scope: !417)
!3319 = !DILocation(line: 1430, column: 39, scope: !417)
!3320 = !DILocation(line: 1430, column: 44, scope: !417)
!3321 = !DILocation(line: 1430, column: 50, scope: !417)
!3322 = !DILocation(line: 1430, column: 59, scope: !417)
!3323 = !DILocation(line: 1430, column: 64, scope: !417)
!3324 = !DILocation(line: 1430, column: 68, scope: !417)
!3325 = !DILocation(line: 1430, column: 9, scope: !417)
!3326 = !DILocation(line: 1430, column: 2, scope: !417)
!3327 = !DILocalVariable(name: "entry", arg: 1, scope: !420, file: !1, line: 1437, type: !5)
!3328 = !DILocation(line: 1437, column: 53, scope: !420)
!3329 = !DILocalVariable(name: "type", arg: 2, scope: !420, file: !1, line: 1438, type: !25)
!3330 = !DILocation(line: 1438, column: 9, scope: !420)
!3331 = !DILocalVariable(name: "permset", arg: 3, scope: !420, file: !1, line: 1438, type: !25)
!3332 = !DILocation(line: 1438, column: 19, scope: !420)
!3333 = !DILocalVariable(name: "tag", arg: 4, scope: !420, file: !1, line: 1438, type: !25)
!3334 = !DILocation(line: 1438, column: 32, scope: !420)
!3335 = !DILocalVariable(name: "id", arg: 5, scope: !420, file: !1, line: 1438, type: !25)
!3336 = !DILocation(line: 1438, column: 41, scope: !420)
!3337 = !DILocalVariable(name: "name", arg: 6, scope: !420, file: !1, line: 1438, type: !269)
!3338 = !DILocation(line: 1438, column: 60, scope: !420)
!3339 = !DILocation(line: 1440, column: 38, scope: !420)
!3340 = !DILocation(line: 1440, column: 45, scope: !420)
!3341 = !DILocation(line: 1441, column: 6, scope: !420)
!3342 = !DILocation(line: 1441, column: 12, scope: !420)
!3343 = !DILocation(line: 1441, column: 21, scope: !420)
!3344 = !DILocation(line: 1441, column: 26, scope: !420)
!3345 = !DILocation(line: 1441, column: 30, scope: !420)
!3346 = !DILocation(line: 1441, column: 43, scope: !420)
!3347 = !DILocation(line: 1441, column: 36, scope: !420)
!3348 = !DILocation(line: 1440, column: 9, scope: !420)
!3349 = !DILocation(line: 1440, column: 2, scope: !420)
!3350 = !DILocalVariable(name: "entry", arg: 1, scope: !423, file: !1, line: 1448, type: !5)
!3351 = !DILocation(line: 1448, column: 47, scope: !423)
!3352 = !DILocation(line: 1450, column: 29, scope: !423)
!3353 = !DILocation(line: 1450, column: 36, scope: !423)
!3354 = !DILocation(line: 1450, column: 10, scope: !423)
!3355 = !DILocation(line: 1450, column: 2, scope: !423)
!3356 = !DILocalVariable(name: "entry", arg: 1, scope: !424, file: !1, line: 1457, type: !5)
!3357 = !DILocation(line: 1457, column: 47, scope: !424)
!3358 = !DILocalVariable(name: "want_type", arg: 2, scope: !424, file: !1, line: 1457, type: !25)
!3359 = !DILocation(line: 1457, column: 58, scope: !424)
!3360 = !DILocation(line: 1459, column: 28, scope: !424)
!3361 = !DILocation(line: 1459, column: 35, scope: !424)
!3362 = !DILocation(line: 1459, column: 40, scope: !424)
!3363 = !DILocation(line: 1459, column: 9, scope: !424)
!3364 = !DILocation(line: 1459, column: 2, scope: !424)
!3365 = !DILocalVariable(name: "entry", arg: 1, scope: !427, file: !1, line: 1468, type: !5)
!3366 = !DILocation(line: 1468, column: 47, scope: !427)
!3367 = !DILocalVariable(name: "want_type", arg: 2, scope: !427, file: !1, line: 1468, type: !25)
!3368 = !DILocation(line: 1468, column: 58, scope: !427)
!3369 = !DILocation(line: 1470, column: 28, scope: !427)
!3370 = !DILocation(line: 1470, column: 35, scope: !427)
!3371 = !DILocation(line: 1470, column: 40, scope: !427)
!3372 = !DILocation(line: 1470, column: 9, scope: !427)
!3373 = !DILocation(line: 1470, column: 2, scope: !427)
!3374 = !DILocalVariable(name: "entry", arg: 1, scope: !428, file: !1, line: 1478, type: !5)
!3375 = !DILocation(line: 1478, column: 46, scope: !428)
!3376 = !DILocalVariable(name: "want_type", arg: 2, scope: !428, file: !1, line: 1478, type: !25)
!3377 = !DILocation(line: 1478, column: 57, scope: !428)
!3378 = !DILocalVariable(name: "type", arg: 3, scope: !428, file: !1, line: 1478, type: !431)
!3379 = !DILocation(line: 1478, column: 73, scope: !428)
!3380 = !DILocalVariable(name: "permset", arg: 4, scope: !428, file: !1, line: 1479, type: !431)
!3381 = !DILocation(line: 1479, column: 10, scope: !428)
!3382 = !DILocalVariable(name: "tag", arg: 5, scope: !428, file: !1, line: 1479, type: !431)
!3383 = !DILocation(line: 1479, column: 24, scope: !428)
!3384 = !DILocalVariable(name: "id", arg: 6, scope: !428, file: !1, line: 1479, type: !431)
!3385 = !DILocation(line: 1479, column: 34, scope: !428)
!3386 = !DILocalVariable(name: "name", arg: 7, scope: !428, file: !1, line: 1479, type: !274)
!3387 = !DILocation(line: 1479, column: 51, scope: !428)
!3388 = !DILocalVariable(name: "r", scope: !428, file: !1, line: 1481, type: !25)
!3389 = !DILocation(line: 1481, column: 6, scope: !428)
!3390 = !DILocation(line: 1482, column: 23, scope: !428)
!3391 = !DILocation(line: 1482, column: 30, scope: !428)
!3392 = !DILocation(line: 1482, column: 40, scope: !428)
!3393 = !DILocation(line: 1482, column: 47, scope: !428)
!3394 = !DILocation(line: 1482, column: 52, scope: !428)
!3395 = !DILocation(line: 1482, column: 63, scope: !428)
!3396 = !DILocation(line: 1483, column: 3, scope: !428)
!3397 = !DILocation(line: 1483, column: 12, scope: !428)
!3398 = !DILocation(line: 1483, column: 17, scope: !428)
!3399 = !DILocation(line: 1483, column: 21, scope: !428)
!3400 = !DILocation(line: 1482, column: 6, scope: !428)
!3401 = !DILocation(line: 1482, column: 4, scope: !428)
!3402 = !DILocation(line: 1484, column: 6, scope: !3403)
!3403 = distinct !DILexicalBlock(scope: !428, file: !1, line: 1484, column: 6)
!3404 = !DILocation(line: 1484, column: 8, scope: !3403)
!3405 = !DILocation(line: 1484, column: 25, scope: !3403)
!3406 = !DILocation(line: 1484, column: 28, scope: !3407)
!3407 = !DILexicalBlockFile(scope: !3403, file: !1, discriminator: 1)
!3408 = !DILocation(line: 1484, column: 34, scope: !3407)
!3409 = !DILocation(line: 1484, column: 6, scope: !3407)
!3410 = !DILocation(line: 1485, column: 3, scope: !3403)
!3411 = !DILocation(line: 1486, column: 10, scope: !428)
!3412 = !DILocation(line: 1486, column: 2, scope: !428)
!3413 = !DILocalVariable(name: "entry", arg: 1, scope: !432, file: !1, line: 1494, type: !5)
!3414 = !DILocation(line: 1494, column: 51, scope: !432)
!3415 = !DILocalVariable(name: "len", arg: 2, scope: !432, file: !1, line: 1494, type: !210)
!3416 = !DILocation(line: 1494, column: 67, scope: !432)
!3417 = !DILocalVariable(name: "flags", arg: 3, scope: !432, file: !1, line: 1495, type: !25)
!3418 = !DILocation(line: 1495, column: 9, scope: !432)
!3419 = !DILocation(line: 1497, column: 33, scope: !432)
!3420 = !DILocation(line: 1497, column: 40, scope: !432)
!3421 = !DILocation(line: 1497, column: 45, scope: !432)
!3422 = !DILocation(line: 1497, column: 50, scope: !432)
!3423 = !DILocation(line: 1498, column: 6, scope: !432)
!3424 = !DILocation(line: 1498, column: 13, scope: !432)
!3425 = !DILocation(line: 1497, column: 10, scope: !432)
!3426 = !DILocation(line: 1497, column: 2, scope: !432)
!3427 = !DILocalVariable(name: "entry", arg: 1, scope: !435, file: !1, line: 1502, type: !5)
!3428 = !DILocation(line: 1502, column: 49, scope: !435)
!3429 = !DILocalVariable(name: "len", arg: 2, scope: !435, file: !1, line: 1502, type: !210)
!3430 = !DILocation(line: 1502, column: 65, scope: !435)
!3431 = !DILocalVariable(name: "flags", arg: 3, scope: !435, file: !1, line: 1503, type: !25)
!3432 = !DILocation(line: 1503, column: 9, scope: !435)
!3433 = !DILocation(line: 1505, column: 33, scope: !435)
!3434 = !DILocation(line: 1505, column: 40, scope: !435)
!3435 = !DILocation(line: 1505, column: 45, scope: !435)
!3436 = !DILocation(line: 1505, column: 50, scope: !435)
!3437 = !DILocation(line: 1505, column: 10, scope: !435)
!3438 = !DILocation(line: 1505, column: 2, scope: !435)
!3439 = !DILocalVariable(name: "entry", arg: 1, scope: !438, file: !1, line: 1509, type: !5)
!3440 = !DILocation(line: 1509, column: 52, scope: !438)
!3441 = !DILocalVariable(name: "len", arg: 2, scope: !438, file: !1, line: 1509, type: !210)
!3442 = !DILocation(line: 1509, column: 68, scope: !438)
!3443 = !DILocalVariable(name: "flags", arg: 3, scope: !438, file: !1, line: 1510, type: !25)
!3444 = !DILocation(line: 1510, column: 8, scope: !438)
!3445 = !DILocalVariable(name: "sc", arg: 4, scope: !438, file: !1, line: 1510, type: !100)
!3446 = !DILocation(line: 1510, column: 43, scope: !438)
!3447 = !DILocation(line: 1512, column: 33, scope: !438)
!3448 = !DILocation(line: 1512, column: 40, scope: !438)
!3449 = !DILocation(line: 1512, column: 45, scope: !438)
!3450 = !DILocation(line: 1512, column: 50, scope: !438)
!3451 = !DILocation(line: 1512, column: 57, scope: !438)
!3452 = !DILocation(line: 1512, column: 10, scope: !438)
!3453 = !DILocation(line: 1512, column: 2, scope: !438)
!3454 = !DILocalVariable(name: "entry", arg: 1, scope: !441, file: !1, line: 1519, type: !5)
!3455 = !DILocation(line: 1519, column: 53, scope: !441)
!3456 = !DILocalVariable(name: "wtext", arg: 2, scope: !441, file: !1, line: 1520, type: !269)
!3457 = !DILocation(line: 1520, column: 20, scope: !441)
!3458 = !DILocalVariable(name: "type", arg: 3, scope: !441, file: !1, line: 1520, type: !25)
!3459 = !DILocation(line: 1520, column: 31, scope: !441)
!3460 = !DILocation(line: 1522, column: 35, scope: !441)
!3461 = !DILocation(line: 1522, column: 42, scope: !441)
!3462 = !DILocation(line: 1522, column: 47, scope: !441)
!3463 = !DILocation(line: 1522, column: 54, scope: !441)
!3464 = !DILocation(line: 1522, column: 10, scope: !441)
!3465 = !DILocation(line: 1522, column: 2, scope: !441)
!3466 = !DILocalVariable(name: "entry", arg: 1, scope: !444, file: !1, line: 1526, type: !5)
!3467 = !DILocation(line: 1526, column: 51, scope: !444)
!3468 = !DILocalVariable(name: "text", arg: 2, scope: !444, file: !1, line: 1527, type: !78)
!3469 = !DILocation(line: 1527, column: 17, scope: !444)
!3470 = !DILocalVariable(name: "type", arg: 3, scope: !444, file: !1, line: 1527, type: !25)
!3471 = !DILocation(line: 1527, column: 27, scope: !444)
!3472 = !DILocation(line: 1529, column: 35, scope: !444)
!3473 = !DILocation(line: 1529, column: 42, scope: !444)
!3474 = !DILocation(line: 1529, column: 47, scope: !444)
!3475 = !DILocation(line: 1529, column: 53, scope: !444)
!3476 = !DILocation(line: 1529, column: 10, scope: !444)
!3477 = !DILocation(line: 1529, column: 2, scope: !444)
!3478 = !DILocalVariable(name: "entry", arg: 1, scope: !447, file: !1, line: 1533, type: !5)
!3479 = !DILocation(line: 1533, column: 54, scope: !447)
!3480 = !DILocalVariable(name: "text", arg: 2, scope: !447, file: !1, line: 1533, type: !78)
!3481 = !DILocation(line: 1533, column: 73, scope: !447)
!3482 = !DILocalVariable(name: "type", arg: 3, scope: !447, file: !1, line: 1534, type: !25)
!3483 = !DILocation(line: 1534, column: 9, scope: !447)
!3484 = !DILocalVariable(name: "sc", arg: 4, scope: !447, file: !1, line: 1534, type: !100)
!3485 = !DILocation(line: 1534, column: 43, scope: !447)
!3486 = !DILocation(line: 1536, column: 35, scope: !447)
!3487 = !DILocation(line: 1536, column: 42, scope: !447)
!3488 = !DILocation(line: 1536, column: 47, scope: !447)
!3489 = !DILocation(line: 1536, column: 53, scope: !447)
!3490 = !DILocation(line: 1536, column: 59, scope: !447)
!3491 = !DILocation(line: 1536, column: 10, scope: !447)
!3492 = !DILocation(line: 1536, column: 2, scope: !447)
!3493 = !DILocalVariable(name: "entry", arg: 1, scope: !450, file: !1, line: 1561, type: !5)
!3494 = !DILocation(line: 1561, column: 48, scope: !450)
!3495 = !DILocalVariable(name: "flags", arg: 2, scope: !450, file: !1, line: 1561, type: !25)
!3496 = !DILocation(line: 1561, column: 59, scope: !450)
!3497 = !DILocation(line: 1563, column: 6, scope: !3498)
!3498 = distinct !DILexicalBlock(scope: !450, file: !1, line: 1563, column: 6)
!3499 = !DILocation(line: 1563, column: 13, scope: !3498)
!3500 = !DILocation(line: 1563, column: 17, scope: !3498)
!3501 = !DILocation(line: 1563, column: 28, scope: !3498)
!3502 = !DILocation(line: 1563, column: 6, scope: !450)
!3503 = !DILocation(line: 1564, column: 8, scope: !3504)
!3504 = distinct !DILexicalBlock(scope: !3498, file: !1, line: 1563, column: 37)
!3505 = !DILocation(line: 1564, column: 15, scope: !3504)
!3506 = !DILocation(line: 1564, column: 19, scope: !3504)
!3507 = !DILocation(line: 1564, column: 3, scope: !3504)
!3508 = !DILocation(line: 1565, column: 3, scope: !3504)
!3509 = !DILocation(line: 1565, column: 10, scope: !3504)
!3510 = !DILocation(line: 1565, column: 14, scope: !3504)
!3511 = !DILocation(line: 1565, column: 25, scope: !3504)
!3512 = !DILocation(line: 1566, column: 2, scope: !3504)
!3513 = !DILocation(line: 1567, column: 6, scope: !3514)
!3514 = distinct !DILexicalBlock(scope: !450, file: !1, line: 1567, column: 6)
!3515 = !DILocation(line: 1567, column: 44, scope: !3514)
!3516 = !DILocation(line: 1567, column: 6, scope: !450)
!3517 = !DILocation(line: 1568, column: 50, scope: !3514)
!3518 = !DILocation(line: 1568, column: 57, scope: !3514)
!3519 = !DILocation(line: 1569, column: 13, scope: !3514)
!3520 = !DILocation(line: 1569, column: 20, scope: !3514)
!3521 = !DILocation(line: 1569, column: 27, scope: !3514)
!3522 = !DILocation(line: 1568, column: 27, scope: !3514)
!3523 = !DILocation(line: 1568, column: 3, scope: !3514)
!3524 = !DILocation(line: 1568, column: 10, scope: !3514)
!3525 = !DILocation(line: 1568, column: 14, scope: !3514)
!3526 = !DILocation(line: 1568, column: 25, scope: !3514)
!3527 = !DILocation(line: 1570, column: 10, scope: !450)
!3528 = !DILocation(line: 1570, column: 17, scope: !450)
!3529 = !DILocation(line: 1570, column: 21, scope: !450)
!3530 = !DILocation(line: 1570, column: 2, scope: !450)
!3531 = !DILocalVariable(name: "flags", arg: 1, scope: !459, file: !1, line: 1541, type: !431)
!3532 = !DILocation(line: 1541, column: 36, scope: !459)
!3533 = !DILocation(line: 1543, column: 8, scope: !3534)
!3534 = distinct !DILexicalBlock(scope: !459, file: !1, line: 1543, column: 6)
!3535 = !DILocation(line: 1543, column: 7, scope: !3534)
!3536 = !DILocation(line: 1543, column: 14, scope: !3534)
!3537 = !DILocation(line: 1543, column: 48, scope: !3534)
!3538 = !DILocation(line: 1543, column: 6, scope: !459)
!3539 = !DILocation(line: 1544, column: 3, scope: !3534)
!3540 = !DILocation(line: 1547, column: 8, scope: !3541)
!3541 = distinct !DILexicalBlock(scope: !459, file: !1, line: 1547, column: 6)
!3542 = !DILocation(line: 1547, column: 7, scope: !3541)
!3543 = !DILocation(line: 1547, column: 14, scope: !3541)
!3544 = !DILocation(line: 1547, column: 54, scope: !3541)
!3545 = !DILocation(line: 1547, column: 6, scope: !459)
!3546 = !DILocation(line: 1548, column: 4, scope: !3541)
!3547 = !DILocation(line: 1548, column: 10, scope: !3541)
!3548 = !DILocation(line: 1548, column: 3, scope: !3541)
!3549 = !DILocation(line: 1551, column: 8, scope: !3550)
!3550 = distinct !DILexicalBlock(scope: !459, file: !1, line: 1551, column: 6)
!3551 = !DILocation(line: 1551, column: 7, scope: !3550)
!3552 = !DILocation(line: 1551, column: 14, scope: !3550)
!3553 = !DILocation(line: 1551, column: 58, scope: !3550)
!3554 = !DILocation(line: 1551, column: 6, scope: !459)
!3555 = !DILocation(line: 1552, column: 4, scope: !3550)
!3556 = !DILocation(line: 1552, column: 10, scope: !3550)
!3557 = !DILocation(line: 1552, column: 3, scope: !3550)
!3558 = !DILocation(line: 1554, column: 3, scope: !459)
!3559 = !DILocation(line: 1554, column: 9, scope: !459)
!3560 = !DILocation(line: 1556, column: 2, scope: !459)
!3561 = !DILocation(line: 1557, column: 1, scope: !459)
!3562 = !DILocalVariable(name: "entry", arg: 1, scope: !453, file: !1, line: 1575, type: !5)
!3563 = !DILocation(line: 1575, column: 46, scope: !453)
!3564 = !DILocalVariable(name: "flags", arg: 2, scope: !453, file: !1, line: 1575, type: !25)
!3565 = !DILocation(line: 1575, column: 57, scope: !453)
!3566 = !DILocation(line: 1577, column: 6, scope: !3567)
!3567 = distinct !DILexicalBlock(scope: !453, file: !1, line: 1577, column: 6)
!3568 = !DILocation(line: 1577, column: 13, scope: !3567)
!3569 = !DILocation(line: 1577, column: 17, scope: !3567)
!3570 = !DILocation(line: 1577, column: 26, scope: !3567)
!3571 = !DILocation(line: 1577, column: 6, scope: !453)
!3572 = !DILocation(line: 1578, column: 8, scope: !3573)
!3573 = distinct !DILexicalBlock(scope: !3567, file: !1, line: 1577, column: 35)
!3574 = !DILocation(line: 1578, column: 15, scope: !3573)
!3575 = !DILocation(line: 1578, column: 19, scope: !3573)
!3576 = !DILocation(line: 1578, column: 3, scope: !3573)
!3577 = !DILocation(line: 1579, column: 3, scope: !3573)
!3578 = !DILocation(line: 1579, column: 10, scope: !3573)
!3579 = !DILocation(line: 1579, column: 14, scope: !3573)
!3580 = !DILocation(line: 1579, column: 23, scope: !3573)
!3581 = !DILocation(line: 1580, column: 2, scope: !3573)
!3582 = !DILocation(line: 1581, column: 6, scope: !3583)
!3583 = distinct !DILexicalBlock(scope: !453, file: !1, line: 1581, column: 6)
!3584 = !DILocation(line: 1581, column: 44, scope: !3583)
!3585 = !DILocation(line: 1581, column: 6, scope: !453)
!3586 = !DILocation(line: 1582, column: 48, scope: !3583)
!3587 = !DILocation(line: 1582, column: 55, scope: !3583)
!3588 = !DILocation(line: 1583, column: 7, scope: !3583)
!3589 = !DILocation(line: 1582, column: 25, scope: !3583)
!3590 = !DILocation(line: 1582, column: 3, scope: !3583)
!3591 = !DILocation(line: 1582, column: 10, scope: !3583)
!3592 = !DILocation(line: 1582, column: 14, scope: !3583)
!3593 = !DILocation(line: 1582, column: 23, scope: !3583)
!3594 = !DILocation(line: 1585, column: 10, scope: !453)
!3595 = !DILocation(line: 1585, column: 17, scope: !453)
!3596 = !DILocation(line: 1585, column: 21, scope: !453)
!3597 = !DILocation(line: 1585, column: 2, scope: !453)
!3598 = !DILocalVariable(name: "entry", arg: 1, scope: !456, file: !1, line: 1590, type: !5)
!3599 = !DILocation(line: 1590, column: 49, scope: !456)
!3600 = !DILocalVariable(name: "flags", arg: 2, scope: !456, file: !1, line: 1590, type: !25)
!3601 = !DILocation(line: 1590, column: 60, scope: !456)
!3602 = !DILocalVariable(name: "acl_text", arg: 3, scope: !456, file: !1, line: 1591, type: !274)
!3603 = !DILocation(line: 1591, column: 18, scope: !456)
!3604 = !DILocalVariable(name: "len", arg: 4, scope: !456, file: !1, line: 1591, type: !63)
!3605 = !DILocation(line: 1591, column: 36, scope: !456)
!3606 = !DILocalVariable(name: "sc", arg: 5, scope: !456, file: !1, line: 1591, type: !100)
!3607 = !DILocation(line: 1591, column: 69, scope: !456)
!3608 = !DILocation(line: 1593, column: 6, scope: !3609)
!3609 = distinct !DILexicalBlock(scope: !456, file: !1, line: 1593, column: 6)
!3610 = !DILocation(line: 1593, column: 13, scope: !3609)
!3611 = !DILocation(line: 1593, column: 17, scope: !3609)
!3612 = !DILocation(line: 1593, column: 26, scope: !3609)
!3613 = !DILocation(line: 1593, column: 6, scope: !456)
!3614 = !DILocation(line: 1594, column: 8, scope: !3615)
!3615 = distinct !DILexicalBlock(scope: !3609, file: !1, line: 1593, column: 35)
!3616 = !DILocation(line: 1594, column: 15, scope: !3615)
!3617 = !DILocation(line: 1594, column: 19, scope: !3615)
!3618 = !DILocation(line: 1594, column: 3, scope: !3615)
!3619 = !DILocation(line: 1595, column: 3, scope: !3615)
!3620 = !DILocation(line: 1595, column: 10, scope: !3615)
!3621 = !DILocation(line: 1595, column: 14, scope: !3615)
!3622 = !DILocation(line: 1595, column: 23, scope: !3615)
!3623 = !DILocation(line: 1596, column: 9, scope: !3615)
!3624 = !DILocation(line: 1598, column: 6, scope: !3625)
!3625 = distinct !DILexicalBlock(scope: !456, file: !1, line: 1598, column: 6)
!3626 = !DILocation(line: 1598, column: 44, scope: !3625)
!3627 = !DILocation(line: 1598, column: 6, scope: !456)
!3628 = !DILocation(line: 1599, column: 48, scope: !3625)
!3629 = !DILocation(line: 1599, column: 55, scope: !3625)
!3630 = !DILocation(line: 1600, column: 18, scope: !3625)
!3631 = !DILocation(line: 1600, column: 23, scope: !3625)
!3632 = !DILocation(line: 1600, column: 30, scope: !3625)
!3633 = !DILocation(line: 1599, column: 25, scope: !3625)
!3634 = !DILocation(line: 1599, column: 3, scope: !3625)
!3635 = !DILocation(line: 1599, column: 10, scope: !3625)
!3636 = !DILocation(line: 1599, column: 14, scope: !3625)
!3637 = !DILocation(line: 1599, column: 23, scope: !3625)
!3638 = !DILocation(line: 1602, column: 14, scope: !456)
!3639 = !DILocation(line: 1602, column: 21, scope: !456)
!3640 = !DILocation(line: 1602, column: 25, scope: !456)
!3641 = !DILocation(line: 1602, column: 3, scope: !456)
!3642 = !DILocation(line: 1602, column: 12, scope: !456)
!3643 = !DILocation(line: 1604, column: 2, scope: !456)
