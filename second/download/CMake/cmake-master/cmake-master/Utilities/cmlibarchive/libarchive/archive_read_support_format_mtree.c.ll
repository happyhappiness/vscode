; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_support_format_mtree.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { {}*, {}*, i32 (%struct.archive*, %struct.archive_entry*)*, {}*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, {}*, i64 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)*, i8* (%struct.archive*, i32)* }
%struct.archive_entry = type opaque
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque
%struct.archive_read = type { %struct.archive, %struct.archive_entry*, i32, i64, i64, %struct.archive_read_client, [16 x %struct.archive_read_filter_bidder], %struct.archive_read_filter*, i32, i64, i32, i32, [16 x %struct.archive_format_descriptor], %struct.archive_format_descriptor*, %struct.archive_read_extract*, i32 (%struct.archive_read*)*, %struct.anon }
%struct.archive_read_client = type { i32 (%struct.archive*, i8*)*, i64 (%struct.archive*, i8*, i8**)*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i32)*, i32 (%struct.archive*, i8*)*, i32 (%struct.archive*, i8*, i8*)*, i32, i32, i64, %struct.archive_read_data_node* }
%struct.archive_read_data_node = type { i64, i64, i8* }
%struct.archive_read_filter_bidder = type { i8*, i8*, i32 (%struct.archive_read_filter_bidder*, %struct.archive_read_filter*)*, i32 (%struct.archive_read_filter*)*, i32 (%struct.archive_read_filter_bidder*, i8*, i8*)*, i32 (%struct.archive_read_filter_bidder*)* }
%struct.archive_read_filter = type { i64, %struct.archive_read_filter_bidder*, %struct.archive_read_filter*, %struct.archive_read*, i32 (%struct.archive_read_filter*)*, i64 (%struct.archive_read_filter*, i8**)*, i64 (%struct.archive_read_filter*, i64)*, i64 (%struct.archive_read_filter*, i64, i32)*, i32 (%struct.archive_read_filter*)*, i32 (%struct.archive_read_filter*, i32)*, i8*, i8*, i32, i8*, i64, i8*, i64, i8*, i64, i8*, i64, i8, i8, i8 }
%struct.archive_format_descriptor = type { i8*, i8*, i32 (%struct.archive_read*, i32)*, i32 (%struct.archive_read*, i8*, i8*)*, i32 (%struct.archive_read*, %struct.archive_entry*)*, i32 (%struct.archive_read*, i8**, i64*, i64*)*, i32 (%struct.archive_read*)*, i64 (%struct.archive_read*, i64, i32)*, i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)* }
%struct.archive_read_extract = type { %struct.archive*, void (i8*)*, i8* }
%struct.anon = type { %struct.archive_read_passphrase*, %struct.archive_read_passphrase**, i32, i8* (%struct.archive*, i8*)*, i8* }
%struct.archive_read_passphrase = type { i8*, %struct.archive_read_passphrase* }
%struct.mtree = type { %struct.archive_string, i64, i8*, i64, i32, i32, i8*, %struct.mtree_entry*, %struct.mtree_entry*, [1024 x %struct.mtree_entry*], %struct.archive_string, %struct.archive_string, %struct.archive_entry_linkresolver*, i64, i8 }
%struct.mtree_entry = type { %struct.mtree_entry*, %struct.mtree_option*, i8*, i8, i8, i32, %struct.mtree_entry* }
%struct.mtree_option = type { %struct.mtree_option*, i8* }
%struct.archive_entry_linkresolver = type opaque
%struct.stat = type { i64, i64, i64, i32, i32, i32, i32, i64, i64, i64, i64, %struct.timespec, %struct.timespec, %struct.timespec, [3 x i64] }
%struct.timespec = type { i64, i64 }

@.str = private unnamed_addr constant [34 x i8] c"archive_read_support_format_mtree\00", align 1
@.str.1 = private unnamed_addr constant [26 x i8] c"Can't allocate mtree data\00", align 1
@.str.2 = private unnamed_addr constant [6 x i8] c"mtree\00", align 1
@.str.3 = private unnamed_addr constant [8 x i8] c"checkfs\00", align 1
@.str.4 = private unnamed_addr constant [7 x i8] c"#mtree\00", align 1
@.str.5 = private unnamed_addr constant [5 x i8] c"/set\00", align 1
@.str.6 = private unnamed_addr constant [7 x i8] c"/unset\00", align 1
@.str.7 = private unnamed_addr constant [4 x i8] c"all\00", align 1
@bid_keyword.keys_c = internal global [4 x i8*] [i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.8, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.9, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.10, i32 0, i32 0), i8* null], align 16
@.str.8 = private unnamed_addr constant [8 x i8] c"content\00", align 1
@.str.9 = private unnamed_addr constant [9 x i8] c"contents\00", align 1
@.str.10 = private unnamed_addr constant [6 x i8] c"cksum\00", align 1
@bid_keyword.keys_df = internal global [3 x i8*] [i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.11, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.12, i32 0, i32 0), i8* null], align 16
@.str.11 = private unnamed_addr constant [7 x i8] c"device\00", align 1
@.str.12 = private unnamed_addr constant [6 x i8] c"flags\00", align 1
@bid_keyword.keys_g = internal global [3 x i8*] [i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.13, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.14, i32 0, i32 0), i8* null], align 16
@.str.13 = private unnamed_addr constant [4 x i8] c"gid\00", align 1
@.str.14 = private unnamed_addr constant [6 x i8] c"gname\00", align 1
@bid_keyword.keys_il = internal global [4 x i8*] [i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.15, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.16, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.17, i32 0, i32 0), i8* null], align 16
@.str.15 = private unnamed_addr constant [7 x i8] c"ignore\00", align 1
@.str.16 = private unnamed_addr constant [6 x i8] c"inode\00", align 1
@.str.17 = private unnamed_addr constant [5 x i8] c"link\00", align 1
@bid_keyword.keys_m = internal global [4 x i8*] [i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.18, i32 0, i32 0), i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.19, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.20, i32 0, i32 0), i8* null], align 16
@.str.18 = private unnamed_addr constant [4 x i8] c"md5\00", align 1
@.str.19 = private unnamed_addr constant [10 x i8] c"md5digest\00", align 1
@.str.20 = private unnamed_addr constant [5 x i8] c"mode\00", align 1
@bid_keyword.keys_no = internal global [4 x i8*] [i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.21, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.22, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.23, i32 0, i32 0), i8* null], align 16
@.str.21 = private unnamed_addr constant [6 x i8] c"nlink\00", align 1
@.str.22 = private unnamed_addr constant [9 x i8] c"nochange\00", align 1
@.str.23 = private unnamed_addr constant [9 x i8] c"optional\00", align 1
@bid_keyword.keys_r = internal global [4 x i8*] [i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.24, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.25, i32 0, i32 0), i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.26, i32 0, i32 0), i8* null], align 16
@.str.24 = private unnamed_addr constant [10 x i8] c"resdevice\00", align 1
@.str.25 = private unnamed_addr constant [7 x i8] c"rmd160\00", align 1
@.str.26 = private unnamed_addr constant [13 x i8] c"rmd160digest\00", align 1
@bid_keyword.keys_s = internal global [10 x i8*] [i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.27, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.28, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.29, i32 0, i32 0), i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.30, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.31, i32 0, i32 0), i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.32, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.33, i32 0, i32 0), i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.34, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.35, i32 0, i32 0), i8* null], align 16
@.str.27 = private unnamed_addr constant [5 x i8] c"sha1\00", align 1
@.str.28 = private unnamed_addr constant [11 x i8] c"sha1digest\00", align 1
@.str.29 = private unnamed_addr constant [7 x i8] c"sha256\00", align 1
@.str.30 = private unnamed_addr constant [13 x i8] c"sha256digest\00", align 1
@.str.31 = private unnamed_addr constant [7 x i8] c"sha384\00", align 1
@.str.32 = private unnamed_addr constant [13 x i8] c"sha384digest\00", align 1
@.str.33 = private unnamed_addr constant [7 x i8] c"sha512\00", align 1
@.str.34 = private unnamed_addr constant [13 x i8] c"sha512digest\00", align 1
@.str.35 = private unnamed_addr constant [5 x i8] c"size\00", align 1
@bid_keyword.keys_t = internal global [4 x i8*] [i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.36, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.37, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.38, i32 0, i32 0), i8* null], align 16
@.str.36 = private unnamed_addr constant [5 x i8] c"tags\00", align 1
@.str.37 = private unnamed_addr constant [5 x i8] c"time\00", align 1
@.str.38 = private unnamed_addr constant [5 x i8] c"type\00", align 1
@bid_keyword.keys_u = internal global [3 x i8*] [i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.39, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.40, i32 0, i32 0), i8* null], align 16
@.str.39 = private unnamed_addr constant [4 x i8] c"uid\00", align 1
@.str.40 = private unnamed_addr constant [6 x i8] c"uname\00", align 1
@bid_entry.safe_char = internal constant [256 x i8] c"\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\01\01\00\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\00\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\01\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00", align 16
@.str.41 = private unnamed_addr constant [3 x i8] c"..\00", align 1
@.str.42 = private unnamed_addr constant [21 x i8] c"Can't parse line %ju\00", align 1
@.str.43 = private unnamed_addr constant [14 x i8] c"Line too long\00", align 1
@.str.44 = private unnamed_addr constant [30 x i8] c"Can't allocate working buffer\00", align 1
@.str.45 = private unnamed_addr constant [22 x i8] c"Can't allocate memory\00", align 1
@.str.46 = private unnamed_addr constant [5 x i8] c" \09\0D\0A\00", align 1
@.str.47 = private unnamed_addr constant [2 x i8] c".\00", align 1
@.str.48 = private unnamed_addr constant [29 x i8] c"/unset shall not contain `='\00", align 1
@.str.49 = private unnamed_addr constant [2 x i8] c"/\00", align 1
@.str.50 = private unnamed_addr constant [14 x i8] c"Can't open %s\00", align 1
@.str.51 = private unnamed_addr constant [19 x i8] c"Could not fstat %s\00", align 1
@.str.52 = private unnamed_addr constant [46 x i8] c"mtree specification has different type for %s\00", align 1
@.str.53 = private unnamed_addr constant [44 x i8] c"Missing type keyword in mtree specification\00", align 1
@.str.54 = private unnamed_addr constant [30 x i8] c"Malformed attribute \22%s\22 (%d)\00", align 1
@.str.55 = private unnamed_addr constant [31 x i8] c"Symbolic mode \22%s\22 unsupported\00", align 1
@.str.56 = private unnamed_addr constant [6 x i8] c"block\00", align 1
@.str.57 = private unnamed_addr constant [5 x i8] c"char\00", align 1
@.str.58 = private unnamed_addr constant [4 x i8] c"dir\00", align 1
@.str.59 = private unnamed_addr constant [5 x i8] c"fifo\00", align 1
@.str.60 = private unnamed_addr constant [5 x i8] c"file\00", align 1
@.str.61 = private unnamed_addr constant [45 x i8] c"Unrecognized file type \22%s\22; assuming \22file\22\00", align 1
@.str.62 = private unnamed_addr constant [23 x i8] c"Unrecognized key %s=%s\00", align 1
@.str.63 = private unnamed_addr constant [20 x i8] c"Unknown format `%s'\00", align 1
@.str.64 = private unnamed_addr constant [2 x i8] c",\00", align 1
@.str.65 = private unnamed_addr constant [15 x i8] c"Missing number\00", align 1
@.str.66 = private unnamed_addr constant [19 x i8] c"Too many arguments\00", align 1
@.str.67 = private unnamed_addr constant [21 x i8] c"Not enough arguments\00", align 1
@.str.68 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@.str.69 = private unnamed_addr constant [11 x i8] c"Can't read\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_read_support_format_mtree(%struct.archive* %_a) #0 !dbg !343 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_read*, align 8
  %mtree = alloca %struct.mtree*, align 8
  %r = alloca i32, align 4
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !459, metadata !460), !dbg !461
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !462, metadata !460), !dbg !463
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !464
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !465
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !463
  call void @llvm.dbg.declare(metadata %struct.mtree** %mtree, metadata !466, metadata !460), !dbg !467
  call void @llvm.dbg.declare(metadata i32* %r, metadata !468, metadata !460), !dbg !469
  br label %do.body, !dbg !470

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !471, metadata !460), !dbg !473
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !474
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 14594245, i32 1, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str, i32 0, i32 0)), !dbg !474
  store i32 %call, i32* %magic_test, align 4, !dbg !474
  %3 = load i32, i32* %magic_test, align 4, !dbg !474
  %cmp = icmp eq i32 %3, -30, !dbg !474
  br i1 %cmp, label %if.then, label %if.end, !dbg !474

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !476
  br label %return, !dbg !476

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !479

do.end:                                           ; preds = %if.end
  %call1 = call noalias i8* @calloc(i64 1, i64 8344) #7, !dbg !481
  %4 = bitcast i8* %call1 to %struct.mtree*, !dbg !482
  store %struct.mtree* %4, %struct.mtree** %mtree, align 8, !dbg !483
  %5 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !484
  %cmp2 = icmp eq %struct.mtree* %5, null, !dbg !486
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !487

if.then3:                                         ; preds = %do.end
  %6 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !488
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %6, i32 0, i32 0, !dbg !490
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.1, i32 0, i32 0)), !dbg !491
  store i32 -30, i32* %retval, align 4, !dbg !492
  br label %return, !dbg !492

if.end4:                                          ; preds = %do.end
  %7 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !493
  %fd = getelementptr inbounds %struct.mtree, %struct.mtree* %7, i32 0, i32 4, !dbg !494
  store i32 -1, i32* %fd, align 8, !dbg !495
  %8 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !496
  %9 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !497
  %10 = bitcast %struct.mtree* %9 to i8*, !dbg !497
  %call5 = call i32 @__archive_read_register_format(%struct.archive_read* %8, i8* %10, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.2, i32 0, i32 0), i32 (%struct.archive_read*, i32)* @mtree_bid, i32 (%struct.archive_read*, i8*, i8*)* @archive_read_format_mtree_options, i32 (%struct.archive_read*, %struct.archive_entry*)* @read_header, i32 (%struct.archive_read*, i8**, i64*, i64*)* @read_data, i32 (%struct.archive_read*)* @skip, i64 (%struct.archive_read*, i64, i32)* null, i32 (%struct.archive_read*)* @cleanup, i32 (%struct.archive_read*)* null, i32 (%struct.archive_read*)* null), !dbg !498
  store i32 %call5, i32* %r, align 4, !dbg !499
  %11 = load i32, i32* %r, align 4, !dbg !500
  %cmp6 = icmp ne i32 %11, 0, !dbg !502
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !503

if.then7:                                         ; preds = %if.end4
  %12 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !504
  %13 = bitcast %struct.mtree* %12 to i8*, !dbg !504
  call void @free(i8* %13) #7, !dbg !505
  br label %if.end8, !dbg !505

if.end8:                                          ; preds = %if.then7, %if.end4
  store i32 0, i32* %retval, align 4, !dbg !506
  br label %return, !dbg !506

return:                                           ; preds = %if.end8, %if.then3, %if.then
  %14 = load i32, i32* %retval, align 4, !dbg !507
  ret i32 %14, !dbg !507
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @__archive_check_magic(%struct.archive*, i32, i32, i8*) #2

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #3

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

declare i32 @__archive_read_register_format(%struct.archive_read*, i8*, i8*, i32 (%struct.archive_read*, i32)*, i32 (%struct.archive_read*, i8*, i8*)*, i32 (%struct.archive_read*, %struct.archive_entry*)*, i32 (%struct.archive_read*, i8**, i64*, i64*)*, i32 (%struct.archive_read*)*, i64 (%struct.archive_read*, i64, i32)*, i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)*) #2

; Function Attrs: nounwind uwtable
define internal i32 @mtree_bid(%struct.archive_read* %a, i32 %best_bid) #0 !dbg !349 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %best_bid.addr = alloca i32, align 4
  %signature = alloca i8*, align 8
  %p = alloca i8*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !508, metadata !460), !dbg !509
  store i32 %best_bid, i32* %best_bid.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %best_bid.addr, metadata !510, metadata !460), !dbg !511
  call void @llvm.dbg.declare(metadata i8** %signature, metadata !512, metadata !460), !dbg !513
  store i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.4, i32 0, i32 0), i8** %signature, align 8, !dbg !513
  call void @llvm.dbg.declare(metadata i8** %p, metadata !514, metadata !460), !dbg !515
  %0 = load i32, i32* %best_bid.addr, align 4, !dbg !516
  %1 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !517
  %2 = load i8*, i8** %signature, align 8, !dbg !518
  %call = call i64 @strlen(i8* %2) #8, !dbg !519
  %call1 = call i8* @__archive_read_ahead(%struct.archive_read* %1, i64 %call, i64* null), !dbg !520
  store i8* %call1, i8** %p, align 8, !dbg !522
  %3 = load i8*, i8** %p, align 8, !dbg !523
  %cmp = icmp eq i8* %3, null, !dbg !525
  br i1 %cmp, label %if.then, label %if.end, !dbg !526

if.then:                                          ; preds = %entry
  store i32 -1, i32* %retval, align 4, !dbg !527
  br label %return, !dbg !527

if.end:                                           ; preds = %entry
  %4 = load i8*, i8** %p, align 8, !dbg !528
  %5 = load i8*, i8** %signature, align 8, !dbg !530
  %6 = load i8*, i8** %signature, align 8, !dbg !531
  %call2 = call i64 @strlen(i8* %6) #8, !dbg !532
  %call3 = call i32 @memcmp(i8* %4, i8* %5, i64 %call2) #8, !dbg !533
  %cmp4 = icmp eq i32 %call3, 0, !dbg !535
  br i1 %cmp4, label %if.then5, label %if.end7, !dbg !536

if.then5:                                         ; preds = %if.end
  %7 = load i8*, i8** %signature, align 8, !dbg !537
  %call6 = call i64 @strlen(i8* %7) #8, !dbg !538
  %conv = trunc i64 %call6 to i32, !dbg !539
  %mul = mul nsw i32 8, %conv, !dbg !540
  store i32 %mul, i32* %retval, align 4, !dbg !541
  br label %return, !dbg !541

if.end7:                                          ; preds = %if.end
  %8 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !542
  %call8 = call i32 @detect_form(%struct.archive_read* %8, i32* null), !dbg !543
  store i32 %call8, i32* %retval, align 4, !dbg !544
  br label %return, !dbg !544

return:                                           ; preds = %if.end7, %if.then5, %if.then
  %9 = load i32, i32* %retval, align 4, !dbg !545
  ret i32 %9, !dbg !545
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_read_format_mtree_options(%struct.archive_read* %a, i8* %key, i8* %val) #0 !dbg !344 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %key.addr = alloca i8*, align 8
  %val.addr = alloca i8*, align 8
  %mtree = alloca %struct.mtree*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !546, metadata !460), !dbg !547
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !548, metadata !460), !dbg !549
  store i8* %val, i8** %val.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %val.addr, metadata !550, metadata !460), !dbg !551
  call void @llvm.dbg.declare(metadata %struct.mtree** %mtree, metadata !552, metadata !460), !dbg !553
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !554
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 13, !dbg !555
  %1 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !555
  %data = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %1, i32 0, i32 0, !dbg !556
  %2 = load i8*, i8** %data, align 8, !dbg !556
  %3 = bitcast i8* %2 to %struct.mtree*, !dbg !557
  store %struct.mtree* %3, %struct.mtree** %mtree, align 8, !dbg !558
  %4 = load i8*, i8** %key.addr, align 8, !dbg !559
  %call = call i32 @strcmp(i8* %4, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.3, i32 0, i32 0)) #8, !dbg !561
  %cmp = icmp eq i32 %call, 0, !dbg !562
  br i1 %cmp, label %if.then, label %if.end6, !dbg !563

if.then:                                          ; preds = %entry
  %5 = load i8*, i8** %val.addr, align 8, !dbg !564
  %cmp1 = icmp eq i8* %5, null, !dbg !567
  br i1 %cmp1, label %if.then4, label %lor.lhs.false, !dbg !568

lor.lhs.false:                                    ; preds = %if.then
  %6 = load i8*, i8** %val.addr, align 8, !dbg !569
  %arrayidx = getelementptr inbounds i8, i8* %6, i64 0, !dbg !569
  %7 = load i8, i8* %arrayidx, align 1, !dbg !569
  %conv = sext i8 %7 to i32, !dbg !569
  %cmp2 = icmp eq i32 %conv, 0, !dbg !571
  br i1 %cmp2, label %if.then4, label %if.else, !dbg !572

if.then4:                                         ; preds = %lor.lhs.false, %if.then
  %8 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !573
  %checkfs = getelementptr inbounds %struct.mtree, %struct.mtree* %8, i32 0, i32 14, !dbg !575
  store i8 0, i8* %checkfs, align 8, !dbg !576
  br label %if.end, !dbg !577

if.else:                                          ; preds = %lor.lhs.false
  %9 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !578
  %checkfs5 = getelementptr inbounds %struct.mtree, %struct.mtree* %9, i32 0, i32 14, !dbg !580
  store i8 1, i8* %checkfs5, align 8, !dbg !581
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then4
  store i32 0, i32* %retval, align 4, !dbg !582
  br label %return, !dbg !582

if.end6:                                          ; preds = %entry
  store i32 -20, i32* %retval, align 4, !dbg !583
  br label %return, !dbg !583

return:                                           ; preds = %if.end6, %if.end
  %10 = load i32, i32* %retval, align 4, !dbg !584
  ret i32 %10, !dbg !584
}

; Function Attrs: nounwind uwtable
define internal i32 @read_header(%struct.archive_read* %a, %struct.archive_entry* %entry1) #0 !dbg !374 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %mtree = alloca %struct.mtree*, align 8
  %p = alloca i8*, align 8
  %r = alloca i32, align 4
  %use_next = alloca i32, align 4
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !585, metadata !460), !dbg !586
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !587, metadata !460), !dbg !588
  call void @llvm.dbg.declare(metadata %struct.mtree** %mtree, metadata !589, metadata !460), !dbg !590
  call void @llvm.dbg.declare(metadata i8** %p, metadata !591, metadata !460), !dbg !592
  call void @llvm.dbg.declare(metadata i32* %r, metadata !593, metadata !460), !dbg !594
  call void @llvm.dbg.declare(metadata i32* %use_next, metadata !595, metadata !460), !dbg !596
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !597
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 13, !dbg !598
  %1 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !598
  %data = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %1, i32 0, i32 0, !dbg !599
  %2 = load i8*, i8** %data, align 8, !dbg !599
  %3 = bitcast i8* %2 to %struct.mtree*, !dbg !600
  store %struct.mtree* %3, %struct.mtree** %mtree, align 8, !dbg !601
  %4 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !602
  %fd = getelementptr inbounds %struct.mtree, %struct.mtree* %4, i32 0, i32 4, !dbg !604
  %5 = load i32, i32* %fd, align 8, !dbg !604
  %cmp = icmp sge i32 %5, 0, !dbg !605
  br i1 %cmp, label %if.then, label %if.end, !dbg !606

if.then:                                          ; preds = %entry
  %6 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !607
  %fd2 = getelementptr inbounds %struct.mtree, %struct.mtree* %6, i32 0, i32 4, !dbg !609
  %7 = load i32, i32* %fd2, align 8, !dbg !609
  %call = call i32 @close(i32 %7), !dbg !610
  %8 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !611
  %fd3 = getelementptr inbounds %struct.mtree, %struct.mtree* %8, i32 0, i32 4, !dbg !612
  store i32 -1, i32* %fd3, align 8, !dbg !613
  br label %if.end, !dbg !614

if.end:                                           ; preds = %if.then, %entry
  %9 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !615
  %entries = getelementptr inbounds %struct.mtree, %struct.mtree* %9, i32 0, i32 7, !dbg !617
  %10 = load %struct.mtree_entry*, %struct.mtree_entry** %entries, align 8, !dbg !617
  %cmp4 = icmp eq %struct.mtree_entry* %10, null, !dbg !618
  br i1 %cmp4, label %if.then5, label %if.end16, !dbg !619

if.then5:                                         ; preds = %if.end
  %call6 = call %struct.archive_entry_linkresolver* @archive_entry_linkresolver_new(), !dbg !620
  %11 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !622
  %resolver = getelementptr inbounds %struct.mtree, %struct.mtree* %11, i32 0, i32 12, !dbg !623
  store %struct.archive_entry_linkresolver* %call6, %struct.archive_entry_linkresolver** %resolver, align 8, !dbg !624
  %12 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !625
  %resolver7 = getelementptr inbounds %struct.mtree, %struct.mtree* %12, i32 0, i32 12, !dbg !627
  %13 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %resolver7, align 8, !dbg !627
  %cmp8 = icmp eq %struct.archive_entry_linkresolver* %13, null, !dbg !628
  br i1 %cmp8, label %if.then9, label %if.end10, !dbg !629

if.then9:                                         ; preds = %if.then5
  store i32 -30, i32* %retval, align 4, !dbg !630
  br label %return, !dbg !630

if.end10:                                         ; preds = %if.then5
  %14 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !631
  %resolver11 = getelementptr inbounds %struct.mtree, %struct.mtree* %14, i32 0, i32 12, !dbg !632
  %15 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %resolver11, align 8, !dbg !632
  call void @archive_entry_linkresolver_set_strategy(%struct.archive_entry_linkresolver* %15, i32 524288), !dbg !633
  %16 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !634
  %17 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !635
  %call12 = call i32 @read_mtree(%struct.archive_read* %16, %struct.mtree* %17), !dbg !636
  store i32 %call12, i32* %r, align 4, !dbg !637
  %18 = load i32, i32* %r, align 4, !dbg !638
  %cmp13 = icmp ne i32 %18, 0, !dbg !640
  br i1 %cmp13, label %if.then14, label %if.end15, !dbg !641

if.then14:                                        ; preds = %if.end10
  %19 = load i32, i32* %r, align 4, !dbg !642
  store i32 %19, i32* %retval, align 4, !dbg !643
  br label %return, !dbg !643

if.end15:                                         ; preds = %if.end10
  br label %if.end16, !dbg !644

if.end16:                                         ; preds = %if.end15, %if.end
  %20 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !645
  %archive_format = getelementptr inbounds %struct.mtree, %struct.mtree* %20, i32 0, i32 5, !dbg !646
  %21 = load i32, i32* %archive_format, align 4, !dbg !646
  %22 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !647
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %22, i32 0, i32 0, !dbg !648
  %archive_format17 = getelementptr inbounds %struct.archive, %struct.archive* %archive, i32 0, i32 3, !dbg !649
  store i32 %21, i32* %archive_format17, align 8, !dbg !650
  %23 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !651
  %archive_format_name = getelementptr inbounds %struct.mtree, %struct.mtree* %23, i32 0, i32 6, !dbg !652
  %24 = load i8*, i8** %archive_format_name, align 8, !dbg !652
  %25 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !653
  %archive18 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %25, i32 0, i32 0, !dbg !654
  %archive_format_name19 = getelementptr inbounds %struct.archive, %struct.archive* %archive18, i32 0, i32 4, !dbg !655
  store i8* %24, i8** %archive_format_name19, align 8, !dbg !656
  br label %for.cond, !dbg !657

for.cond:                                         ; preds = %if.end61, %if.end16
  %26 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !658
  %this_entry = getelementptr inbounds %struct.mtree, %struct.mtree* %26, i32 0, i32 8, !dbg !663
  %27 = load %struct.mtree_entry*, %struct.mtree_entry** %this_entry, align 8, !dbg !663
  %cmp20 = icmp eq %struct.mtree_entry* %27, null, !dbg !664
  br i1 %cmp20, label %if.then21, label %if.end22, !dbg !665

if.then21:                                        ; preds = %for.cond
  store i32 1, i32* %retval, align 4, !dbg !666
  br label %return, !dbg !666

if.end22:                                         ; preds = %for.cond
  %28 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !667
  %this_entry23 = getelementptr inbounds %struct.mtree, %struct.mtree* %28, i32 0, i32 8, !dbg !669
  %29 = load %struct.mtree_entry*, %struct.mtree_entry** %this_entry23, align 8, !dbg !669
  %name = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %29, i32 0, i32 2, !dbg !670
  %30 = load i8*, i8** %name, align 8, !dbg !670
  %call24 = call i32 @strcmp(i8* %30, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.41, i32 0, i32 0)) #8, !dbg !671
  %cmp25 = icmp eq i32 %call24, 0, !dbg !672
  br i1 %cmp25, label %if.then26, label %if.end51, !dbg !673

if.then26:                                        ; preds = %if.end22
  %31 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !674
  %this_entry27 = getelementptr inbounds %struct.mtree, %struct.mtree* %31, i32 0, i32 8, !dbg !676
  %32 = load %struct.mtree_entry*, %struct.mtree_entry** %this_entry27, align 8, !dbg !676
  %used = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %32, i32 0, i32 4, !dbg !677
  store i8 1, i8* %used, align 1, !dbg !678
  %33 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !679
  %current_dir = getelementptr inbounds %struct.mtree, %struct.mtree* %33, i32 0, i32 10, !dbg !679
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %current_dir, i32 0, i32 1, !dbg !679
  %34 = load i64, i64* %length, align 8, !dbg !679
  %cmp28 = icmp ugt i64 %34, 0, !dbg !681
  br i1 %cmp28, label %if.then29, label %if.end50, !dbg !682

if.then29:                                        ; preds = %if.then26
  %35 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !683
  %current_dir30 = getelementptr inbounds %struct.mtree, %struct.mtree* %35, i32 0, i32 10, !dbg !685
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %current_dir30, i32 0, i32 0, !dbg !686
  %36 = load i8*, i8** %s, align 8, !dbg !686
  %37 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !687
  %current_dir31 = getelementptr inbounds %struct.mtree, %struct.mtree* %37, i32 0, i32 10, !dbg !688
  %length32 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %current_dir31, i32 0, i32 1, !dbg !689
  %38 = load i64, i64* %length32, align 8, !dbg !689
  %add.ptr = getelementptr inbounds i8, i8* %36, i64 %38, !dbg !690
  %add.ptr33 = getelementptr inbounds i8, i8* %add.ptr, i64 -1, !dbg !691
  store i8* %add.ptr33, i8** %p, align 8, !dbg !692
  br label %while.cond, !dbg !693

while.cond:                                       ; preds = %while.body, %if.then29
  %39 = load i8*, i8** %p, align 8, !dbg !694
  %40 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !696
  %current_dir34 = getelementptr inbounds %struct.mtree, %struct.mtree* %40, i32 0, i32 10, !dbg !697
  %s35 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %current_dir34, i32 0, i32 0, !dbg !698
  %41 = load i8*, i8** %s35, align 8, !dbg !698
  %cmp36 = icmp uge i8* %39, %41, !dbg !699
  br i1 %cmp36, label %land.rhs, label %land.end, !dbg !700

land.rhs:                                         ; preds = %while.cond
  %42 = load i8*, i8** %p, align 8, !dbg !701
  %43 = load i8, i8* %42, align 1, !dbg !703
  %conv = sext i8 %43 to i32, !dbg !703
  %cmp37 = icmp ne i32 %conv, 47, !dbg !704
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond
  %44 = phi i1 [ false, %while.cond ], [ %cmp37, %land.rhs ]
  br i1 %44, label %while.body, label %while.end, !dbg !705

while.body:                                       ; preds = %land.end
  %45 = load i8*, i8** %p, align 8, !dbg !707
  %incdec.ptr = getelementptr inbounds i8, i8* %45, i32 -1, !dbg !707
  store i8* %incdec.ptr, i8** %p, align 8, !dbg !707
  br label %while.cond, !dbg !708

while.end:                                        ; preds = %land.end
  %46 = load i8*, i8** %p, align 8, !dbg !710
  %47 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !712
  %current_dir39 = getelementptr inbounds %struct.mtree, %struct.mtree* %47, i32 0, i32 10, !dbg !713
  %s40 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %current_dir39, i32 0, i32 0, !dbg !714
  %48 = load i8*, i8** %s40, align 8, !dbg !714
  %cmp41 = icmp uge i8* %46, %48, !dbg !715
  br i1 %cmp41, label %if.then43, label %if.end45, !dbg !716

if.then43:                                        ; preds = %while.end
  %49 = load i8*, i8** %p, align 8, !dbg !717
  %incdec.ptr44 = getelementptr inbounds i8, i8* %49, i32 -1, !dbg !717
  store i8* %incdec.ptr44, i8** %p, align 8, !dbg !717
  br label %if.end45, !dbg !717

if.end45:                                         ; preds = %if.then43, %while.end
  %50 = load i8*, i8** %p, align 8, !dbg !718
  %51 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !719
  %current_dir46 = getelementptr inbounds %struct.mtree, %struct.mtree* %51, i32 0, i32 10, !dbg !720
  %s47 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %current_dir46, i32 0, i32 0, !dbg !721
  %52 = load i8*, i8** %s47, align 8, !dbg !721
  %sub.ptr.lhs.cast = ptrtoint i8* %50 to i64, !dbg !722
  %sub.ptr.rhs.cast = ptrtoint i8* %52 to i64, !dbg !722
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !722
  %add = add nsw i64 %sub.ptr.sub, 1, !dbg !723
  %53 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !724
  %current_dir48 = getelementptr inbounds %struct.mtree, %struct.mtree* %53, i32 0, i32 10, !dbg !725
  %length49 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %current_dir48, i32 0, i32 1, !dbg !726
  store i64 %add, i64* %length49, align 8, !dbg !727
  br label %if.end50, !dbg !728

if.end50:                                         ; preds = %if.end45, %if.then26
  br label %if.end51, !dbg !729

if.end51:                                         ; preds = %if.end50, %if.end22
  %54 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !730
  %this_entry52 = getelementptr inbounds %struct.mtree, %struct.mtree* %54, i32 0, i32 8, !dbg !732
  %55 = load %struct.mtree_entry*, %struct.mtree_entry** %this_entry52, align 8, !dbg !732
  %used53 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %55, i32 0, i32 4, !dbg !733
  %56 = load i8, i8* %used53, align 1, !dbg !733
  %tobool = icmp ne i8 %56, 0, !dbg !730
  br i1 %tobool, label %if.end61, label %if.then54, !dbg !734

if.then54:                                        ; preds = %if.end51
  store i32 0, i32* %use_next, align 4, !dbg !735
  %57 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !737
  %58 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !738
  %59 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !739
  %60 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !740
  %this_entry55 = getelementptr inbounds %struct.mtree, %struct.mtree* %60, i32 0, i32 8, !dbg !741
  %61 = load %struct.mtree_entry*, %struct.mtree_entry** %this_entry55, align 8, !dbg !741
  %call56 = call i32 @parse_file(%struct.archive_read* %57, %struct.archive_entry* %58, %struct.mtree* %59, %struct.mtree_entry* %61, i32* %use_next), !dbg !742
  store i32 %call56, i32* %r, align 4, !dbg !743
  %62 = load i32, i32* %use_next, align 4, !dbg !744
  %cmp57 = icmp eq i32 %62, 0, !dbg !746
  br i1 %cmp57, label %if.then59, label %if.end60, !dbg !747

if.then59:                                        ; preds = %if.then54
  %63 = load i32, i32* %r, align 4, !dbg !748
  store i32 %63, i32* %retval, align 4, !dbg !749
  br label %return, !dbg !749

if.end60:                                         ; preds = %if.then54
  br label %if.end61, !dbg !750

if.end61:                                         ; preds = %if.end60, %if.end51
  %64 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !751
  %this_entry62 = getelementptr inbounds %struct.mtree, %struct.mtree* %64, i32 0, i32 8, !dbg !752
  %65 = load %struct.mtree_entry*, %struct.mtree_entry** %this_entry62, align 8, !dbg !752
  %next = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %65, i32 0, i32 0, !dbg !753
  %66 = load %struct.mtree_entry*, %struct.mtree_entry** %next, align 8, !dbg !753
  %67 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !754
  %this_entry63 = getelementptr inbounds %struct.mtree, %struct.mtree* %67, i32 0, i32 8, !dbg !755
  store %struct.mtree_entry* %66, %struct.mtree_entry** %this_entry63, align 8, !dbg !756
  br label %for.cond, !dbg !757

return:                                           ; preds = %if.then59, %if.then21, %if.then14, %if.then9
  %68 = load i32, i32* %retval, align 4, !dbg !759
  ret i32 %68, !dbg !759
}

; Function Attrs: nounwind uwtable
define internal i32 @read_data(%struct.archive_read* %a, i8** %buff, i64* %size, i64* %offset) #0 !dbg !430 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %buff.addr = alloca i8**, align 8
  %size.addr = alloca i64*, align 8
  %offset.addr = alloca i64*, align 8
  %bytes_to_read = alloca i64, align 8
  %bytes_read = alloca i64, align 8
  %mtree = alloca %struct.mtree*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !760, metadata !460), !dbg !761
  store i8** %buff, i8*** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %buff.addr, metadata !762, metadata !460), !dbg !763
  store i64* %size, i64** %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %size.addr, metadata !764, metadata !460), !dbg !765
  store i64* %offset, i64** %offset.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %offset.addr, metadata !766, metadata !460), !dbg !767
  call void @llvm.dbg.declare(metadata i64* %bytes_to_read, metadata !768, metadata !460), !dbg !769
  call void @llvm.dbg.declare(metadata i64* %bytes_read, metadata !770, metadata !460), !dbg !771
  call void @llvm.dbg.declare(metadata %struct.mtree** %mtree, metadata !772, metadata !460), !dbg !773
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !774
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 13, !dbg !775
  %1 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !775
  %data = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %1, i32 0, i32 0, !dbg !776
  %2 = load i8*, i8** %data, align 8, !dbg !776
  %3 = bitcast i8* %2 to %struct.mtree*, !dbg !777
  store %struct.mtree* %3, %struct.mtree** %mtree, align 8, !dbg !778
  %4 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !779
  %fd = getelementptr inbounds %struct.mtree, %struct.mtree* %4, i32 0, i32 4, !dbg !781
  %5 = load i32, i32* %fd, align 8, !dbg !781
  %cmp = icmp slt i32 %5, 0, !dbg !782
  br i1 %cmp, label %if.then, label %if.end, !dbg !783

if.then:                                          ; preds = %entry
  %6 = load i8**, i8*** %buff.addr, align 8, !dbg !784
  store i8* null, i8** %6, align 8, !dbg !786
  %7 = load i64*, i64** %offset.addr, align 8, !dbg !787
  store i64 0, i64* %7, align 8, !dbg !788
  %8 = load i64*, i64** %size.addr, align 8, !dbg !789
  store i64 0, i64* %8, align 8, !dbg !790
  store i32 1, i32* %retval, align 4, !dbg !791
  br label %return, !dbg !791

if.end:                                           ; preds = %entry
  %9 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !792
  %buff1 = getelementptr inbounds %struct.mtree, %struct.mtree* %9, i32 0, i32 2, !dbg !794
  %10 = load i8*, i8** %buff1, align 8, !dbg !794
  %cmp2 = icmp eq i8* %10, null, !dbg !795
  br i1 %cmp2, label %if.then3, label %if.end10, !dbg !796

if.then3:                                         ; preds = %if.end
  %11 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !797
  %buffsize = getelementptr inbounds %struct.mtree, %struct.mtree* %11, i32 0, i32 1, !dbg !799
  store i64 65536, i64* %buffsize, align 8, !dbg !800
  %12 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !801
  %buffsize4 = getelementptr inbounds %struct.mtree, %struct.mtree* %12, i32 0, i32 1, !dbg !802
  %13 = load i64, i64* %buffsize4, align 8, !dbg !802
  %call = call noalias i8* @malloc(i64 %13) #7, !dbg !803
  %14 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !804
  %buff5 = getelementptr inbounds %struct.mtree, %struct.mtree* %14, i32 0, i32 2, !dbg !805
  store i8* %call, i8** %buff5, align 8, !dbg !806
  %15 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !807
  %buff6 = getelementptr inbounds %struct.mtree, %struct.mtree* %15, i32 0, i32 2, !dbg !809
  %16 = load i8*, i8** %buff6, align 8, !dbg !809
  %cmp7 = icmp eq i8* %16, null, !dbg !810
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !811

if.then8:                                         ; preds = %if.then3
  %17 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !812
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %17, i32 0, i32 0, !dbg !814
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.45, i32 0, i32 0)), !dbg !815
  store i32 -30, i32* %retval, align 4, !dbg !816
  br label %return, !dbg !816

if.end9:                                          ; preds = %if.then3
  br label %if.end10, !dbg !817

if.end10:                                         ; preds = %if.end9, %if.end
  %18 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !818
  %buff11 = getelementptr inbounds %struct.mtree, %struct.mtree* %18, i32 0, i32 2, !dbg !819
  %19 = load i8*, i8** %buff11, align 8, !dbg !819
  %20 = load i8**, i8*** %buff.addr, align 8, !dbg !820
  store i8* %19, i8** %20, align 8, !dbg !821
  %21 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !822
  %offset12 = getelementptr inbounds %struct.mtree, %struct.mtree* %21, i32 0, i32 3, !dbg !823
  %22 = load i64, i64* %offset12, align 8, !dbg !823
  %23 = load i64*, i64** %offset.addr, align 8, !dbg !824
  store i64 %22, i64* %23, align 8, !dbg !825
  %24 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !826
  %buffsize13 = getelementptr inbounds %struct.mtree, %struct.mtree* %24, i32 0, i32 1, !dbg !828
  %25 = load i64, i64* %buffsize13, align 8, !dbg !828
  %26 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !829
  %cur_size = getelementptr inbounds %struct.mtree, %struct.mtree* %26, i32 0, i32 13, !dbg !830
  %27 = load i64, i64* %cur_size, align 8, !dbg !830
  %28 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !831
  %offset14 = getelementptr inbounds %struct.mtree, %struct.mtree* %28, i32 0, i32 3, !dbg !832
  %29 = load i64, i64* %offset14, align 8, !dbg !832
  %sub = sub nsw i64 %27, %29, !dbg !833
  %cmp15 = icmp sgt i64 %25, %sub, !dbg !834
  br i1 %cmp15, label %if.then16, label %if.else, !dbg !835

if.then16:                                        ; preds = %if.end10
  %30 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !836
  %cur_size17 = getelementptr inbounds %struct.mtree, %struct.mtree* %30, i32 0, i32 13, !dbg !837
  %31 = load i64, i64* %cur_size17, align 8, !dbg !837
  %32 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !838
  %offset18 = getelementptr inbounds %struct.mtree, %struct.mtree* %32, i32 0, i32 3, !dbg !839
  %33 = load i64, i64* %offset18, align 8, !dbg !839
  %sub19 = sub nsw i64 %31, %33, !dbg !840
  store i64 %sub19, i64* %bytes_to_read, align 8, !dbg !841
  br label %if.end21, !dbg !842

if.else:                                          ; preds = %if.end10
  %34 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !843
  %buffsize20 = getelementptr inbounds %struct.mtree, %struct.mtree* %34, i32 0, i32 1, !dbg !844
  %35 = load i64, i64* %buffsize20, align 8, !dbg !844
  store i64 %35, i64* %bytes_to_read, align 8, !dbg !845
  br label %if.end21

if.end21:                                         ; preds = %if.else, %if.then16
  %36 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !846
  %fd22 = getelementptr inbounds %struct.mtree, %struct.mtree* %36, i32 0, i32 4, !dbg !847
  %37 = load i32, i32* %fd22, align 8, !dbg !847
  %38 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !848
  %buff23 = getelementptr inbounds %struct.mtree, %struct.mtree* %38, i32 0, i32 2, !dbg !849
  %39 = load i8*, i8** %buff23, align 8, !dbg !849
  %40 = load i64, i64* %bytes_to_read, align 8, !dbg !850
  %call24 = call i64 @read(i32 %37, i8* %39, i64 %40), !dbg !851
  store i64 %call24, i64* %bytes_read, align 8, !dbg !852
  %41 = load i64, i64* %bytes_read, align 8, !dbg !853
  %cmp25 = icmp slt i64 %41, 0, !dbg !855
  br i1 %cmp25, label %if.then26, label %if.end29, !dbg !856

if.then26:                                        ; preds = %if.end21
  %42 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !857
  %archive27 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %42, i32 0, i32 0, !dbg !859
  %call28 = call i32* @__errno_location() #1, !dbg !860
  %43 = load i32, i32* %call28, align 4, !dbg !860
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive27, i32 %43, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.69, i32 0, i32 0)), !dbg !861
  store i32 -20, i32* %retval, align 4, !dbg !863
  br label %return, !dbg !863

if.end29:                                         ; preds = %if.end21
  %44 = load i64, i64* %bytes_read, align 8, !dbg !864
  %cmp30 = icmp eq i64 %44, 0, !dbg !866
  br i1 %cmp30, label %if.then31, label %if.end32, !dbg !867

if.then31:                                        ; preds = %if.end29
  %45 = load i64*, i64** %size.addr, align 8, !dbg !868
  store i64 0, i64* %45, align 8, !dbg !870
  store i32 1, i32* %retval, align 4, !dbg !871
  br label %return, !dbg !871

if.end32:                                         ; preds = %if.end29
  %46 = load i64, i64* %bytes_read, align 8, !dbg !872
  %47 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !873
  %offset33 = getelementptr inbounds %struct.mtree, %struct.mtree* %47, i32 0, i32 3, !dbg !874
  %48 = load i64, i64* %offset33, align 8, !dbg !875
  %add = add nsw i64 %48, %46, !dbg !875
  store i64 %add, i64* %offset33, align 8, !dbg !875
  %49 = load i64, i64* %bytes_read, align 8, !dbg !876
  %50 = load i64*, i64** %size.addr, align 8, !dbg !877
  store i64 %49, i64* %50, align 8, !dbg !878
  store i32 0, i32* %retval, align 4, !dbg !879
  br label %return, !dbg !879

return:                                           ; preds = %if.end32, %if.then31, %if.then26, %if.then8, %if.then
  %51 = load i32, i32* %retval, align 4, !dbg !880
  ret i32 %51, !dbg !880
}

; Function Attrs: nounwind uwtable
define internal i32 @skip(%struct.archive_read* %a) #0 !dbg !431 {
entry:
  %a.addr = alloca %struct.archive_read*, align 8
  %mtree = alloca %struct.mtree*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !881, metadata !460), !dbg !882
  call void @llvm.dbg.declare(metadata %struct.mtree** %mtree, metadata !883, metadata !460), !dbg !884
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !885
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 13, !dbg !886
  %1 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !886
  %data = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %1, i32 0, i32 0, !dbg !887
  %2 = load i8*, i8** %data, align 8, !dbg !887
  %3 = bitcast i8* %2 to %struct.mtree*, !dbg !888
  store %struct.mtree* %3, %struct.mtree** %mtree, align 8, !dbg !889
  %4 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !890
  %fd = getelementptr inbounds %struct.mtree, %struct.mtree* %4, i32 0, i32 4, !dbg !892
  %5 = load i32, i32* %fd, align 8, !dbg !892
  %cmp = icmp sge i32 %5, 0, !dbg !893
  br i1 %cmp, label %if.then, label %if.end, !dbg !894

if.then:                                          ; preds = %entry
  %6 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !895
  %fd1 = getelementptr inbounds %struct.mtree, %struct.mtree* %6, i32 0, i32 4, !dbg !897
  %7 = load i32, i32* %fd1, align 8, !dbg !897
  %call = call i32 @close(i32 %7), !dbg !898
  %8 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !899
  %fd2 = getelementptr inbounds %struct.mtree, %struct.mtree* %8, i32 0, i32 4, !dbg !900
  store i32 -1, i32* %fd2, align 8, !dbg !901
  br label %if.end, !dbg !902

if.end:                                           ; preds = %if.then, %entry
  ret i32 0, !dbg !903
}

; Function Attrs: nounwind uwtable
define internal i32 @cleanup(%struct.archive_read* %a) #0 !dbg !345 {
entry:
  %a.addr = alloca %struct.archive_read*, align 8
  %mtree = alloca %struct.mtree*, align 8
  %p = alloca %struct.mtree_entry*, align 8
  %q = alloca %struct.mtree_entry*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !904, metadata !460), !dbg !905
  call void @llvm.dbg.declare(metadata %struct.mtree** %mtree, metadata !906, metadata !460), !dbg !907
  call void @llvm.dbg.declare(metadata %struct.mtree_entry** %p, metadata !908, metadata !460), !dbg !909
  call void @llvm.dbg.declare(metadata %struct.mtree_entry** %q, metadata !910, metadata !460), !dbg !911
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !912
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 13, !dbg !913
  %1 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !913
  %data = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %1, i32 0, i32 0, !dbg !914
  %2 = load i8*, i8** %data, align 8, !dbg !914
  %3 = bitcast i8* %2 to %struct.mtree*, !dbg !915
  store %struct.mtree* %3, %struct.mtree** %mtree, align 8, !dbg !916
  %4 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !917
  %entries = getelementptr inbounds %struct.mtree, %struct.mtree* %4, i32 0, i32 7, !dbg !918
  %5 = load %struct.mtree_entry*, %struct.mtree_entry** %entries, align 8, !dbg !918
  store %struct.mtree_entry* %5, %struct.mtree_entry** %p, align 8, !dbg !919
  br label %while.cond, !dbg !920

while.cond:                                       ; preds = %while.body, %entry
  %6 = load %struct.mtree_entry*, %struct.mtree_entry** %p, align 8, !dbg !921
  %cmp = icmp ne %struct.mtree_entry* %6, null, !dbg !923
  br i1 %cmp, label %while.body, label %while.end, !dbg !924

while.body:                                       ; preds = %while.cond
  %7 = load %struct.mtree_entry*, %struct.mtree_entry** %p, align 8, !dbg !925
  %next = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %7, i32 0, i32 0, !dbg !927
  %8 = load %struct.mtree_entry*, %struct.mtree_entry** %next, align 8, !dbg !927
  store %struct.mtree_entry* %8, %struct.mtree_entry** %q, align 8, !dbg !928
  %9 = load %struct.mtree_entry*, %struct.mtree_entry** %p, align 8, !dbg !929
  %name = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %9, i32 0, i32 2, !dbg !930
  %10 = load i8*, i8** %name, align 8, !dbg !930
  call void @free(i8* %10) #7, !dbg !931
  %11 = load %struct.mtree_entry*, %struct.mtree_entry** %p, align 8, !dbg !932
  %options = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %11, i32 0, i32 1, !dbg !933
  %12 = load %struct.mtree_option*, %struct.mtree_option** %options, align 8, !dbg !933
  call void @free_options(%struct.mtree_option* %12), !dbg !934
  %13 = load %struct.mtree_entry*, %struct.mtree_entry** %p, align 8, !dbg !935
  %14 = bitcast %struct.mtree_entry* %13 to i8*, !dbg !935
  call void @free(i8* %14) #7, !dbg !936
  %15 = load %struct.mtree_entry*, %struct.mtree_entry** %q, align 8, !dbg !937
  store %struct.mtree_entry* %15, %struct.mtree_entry** %p, align 8, !dbg !938
  br label %while.cond, !dbg !939

while.end:                                        ; preds = %while.cond
  %16 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !941
  %line = getelementptr inbounds %struct.mtree, %struct.mtree* %16, i32 0, i32 0, !dbg !942
  call void @archive_string_free(%struct.archive_string* %line), !dbg !943
  %17 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !944
  %current_dir = getelementptr inbounds %struct.mtree, %struct.mtree* %17, i32 0, i32 10, !dbg !945
  call void @archive_string_free(%struct.archive_string* %current_dir), !dbg !946
  %18 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !947
  %contents_name = getelementptr inbounds %struct.mtree, %struct.mtree* %18, i32 0, i32 11, !dbg !948
  call void @archive_string_free(%struct.archive_string* %contents_name), !dbg !949
  %19 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !950
  %resolver = getelementptr inbounds %struct.mtree, %struct.mtree* %19, i32 0, i32 12, !dbg !951
  %20 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %resolver, align 8, !dbg !951
  call void @archive_entry_linkresolver_free(%struct.archive_entry_linkresolver* %20), !dbg !952
  %21 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !953
  %buff = getelementptr inbounds %struct.mtree, %struct.mtree* %21, i32 0, i32 2, !dbg !954
  %22 = load i8*, i8** %buff, align 8, !dbg !954
  call void @free(i8* %22) #7, !dbg !955
  %23 = load %struct.mtree*, %struct.mtree** %mtree, align 8, !dbg !956
  %24 = bitcast %struct.mtree* %23 to i8*, !dbg !956
  call void @free(i8* %24) #7, !dbg !957
  %25 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !958
  %format1 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %25, i32 0, i32 13, !dbg !959
  %26 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format1, align 8, !dbg !959
  %data2 = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %26, i32 0, i32 0, !dbg !960
  store i8* null, i8** %data2, align 8, !dbg !961
  ret i32 0, !dbg !962
}

; Function Attrs: nounwind
declare void @free(i8*) #3

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #4

; Function Attrs: nounwind uwtable
define internal void @free_options(%struct.mtree_option* %head) #0 !dbg !346 {
entry:
  %head.addr = alloca %struct.mtree_option*, align 8
  %next = alloca %struct.mtree_option*, align 8
  store %struct.mtree_option* %head, %struct.mtree_option** %head.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree_option** %head.addr, metadata !963, metadata !460), !dbg !964
  call void @llvm.dbg.declare(metadata %struct.mtree_option** %next, metadata !965, metadata !460), !dbg !966
  br label %for.cond, !dbg !967

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load %struct.mtree_option*, %struct.mtree_option** %head.addr, align 8, !dbg !968
  %cmp = icmp ne %struct.mtree_option* %0, null, !dbg !972
  br i1 %cmp, label %for.body, label %for.end, !dbg !973

for.body:                                         ; preds = %for.cond
  %1 = load %struct.mtree_option*, %struct.mtree_option** %head.addr, align 8, !dbg !974
  %next1 = getelementptr inbounds %struct.mtree_option, %struct.mtree_option* %1, i32 0, i32 0, !dbg !976
  %2 = load %struct.mtree_option*, %struct.mtree_option** %next1, align 8, !dbg !976
  store %struct.mtree_option* %2, %struct.mtree_option** %next, align 8, !dbg !977
  %3 = load %struct.mtree_option*, %struct.mtree_option** %head.addr, align 8, !dbg !978
  %value = getelementptr inbounds %struct.mtree_option, %struct.mtree_option* %3, i32 0, i32 1, !dbg !979
  %4 = load i8*, i8** %value, align 8, !dbg !979
  call void @free(i8* %4) #7, !dbg !980
  %5 = load %struct.mtree_option*, %struct.mtree_option** %head.addr, align 8, !dbg !981
  %6 = bitcast %struct.mtree_option* %5 to i8*, !dbg !981
  call void @free(i8* %6) #7, !dbg !982
  br label %for.inc, !dbg !983

for.inc:                                          ; preds = %for.body
  %7 = load %struct.mtree_option*, %struct.mtree_option** %next, align 8, !dbg !984
  store %struct.mtree_option* %7, %struct.mtree_option** %head.addr, align 8, !dbg !986
  br label %for.cond, !dbg !987

for.end:                                          ; preds = %for.cond
  ret void, !dbg !988
}

declare void @archive_string_free(%struct.archive_string*) #2

declare void @archive_entry_linkresolver_free(%struct.archive_entry_linkresolver*) #2

declare i8* @__archive_read_ahead(%struct.archive_read*, i64, i64*) #2

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #4

; Function Attrs: nounwind readonly
declare i32 @memcmp(i8*, i8*, i64) #4

; Function Attrs: nounwind uwtable
define internal i32 @detect_form(%struct.archive_read* %a, i32* %is_form_d) #0 !dbg !350 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %is_form_d.addr = alloca i32*, align 8
  %p = alloca i8*, align 8
  %avail = alloca i64, align 8
  %ravail = alloca i64, align 8
  %detected_bytes = alloca i64, align 8
  %len = alloca i64, align 8
  %nl = alloca i64, align 8
  %entry_cnt = alloca i32, align 4
  %multiline = alloca i32, align 4
  %form_D = alloca i32, align 4
  %last_is_path = alloca i32, align 4
  %keywords = alloca i32, align 4
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !989, metadata !460), !dbg !990
  store i32* %is_form_d, i32** %is_form_d.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %is_form_d.addr, metadata !991, metadata !460), !dbg !992
  call void @llvm.dbg.declare(metadata i8** %p, metadata !993, metadata !460), !dbg !994
  call void @llvm.dbg.declare(metadata i64* %avail, metadata !995, metadata !460), !dbg !996
  call void @llvm.dbg.declare(metadata i64* %ravail, metadata !997, metadata !460), !dbg !998
  call void @llvm.dbg.declare(metadata i64* %detected_bytes, metadata !999, metadata !460), !dbg !1000
  store i64 0, i64* %detected_bytes, align 8, !dbg !1000
  call void @llvm.dbg.declare(metadata i64* %len, metadata !1001, metadata !460), !dbg !1002
  call void @llvm.dbg.declare(metadata i64* %nl, metadata !1003, metadata !460), !dbg !1004
  call void @llvm.dbg.declare(metadata i32* %entry_cnt, metadata !1005, metadata !460), !dbg !1006
  store i32 0, i32* %entry_cnt, align 4, !dbg !1006
  call void @llvm.dbg.declare(metadata i32* %multiline, metadata !1007, metadata !460), !dbg !1008
  store i32 0, i32* %multiline, align 4, !dbg !1008
  call void @llvm.dbg.declare(metadata i32* %form_D, metadata !1009, metadata !460), !dbg !1010
  store i32 0, i32* %form_D, align 4, !dbg !1010
  %0 = load i32*, i32** %is_form_d.addr, align 8, !dbg !1011
  %cmp = icmp ne i32* %0, null, !dbg !1013
  br i1 %cmp, label %if.then, label %if.end, !dbg !1014

if.then:                                          ; preds = %entry
  %1 = load i32*, i32** %is_form_d.addr, align 8, !dbg !1015
  store i32 0, i32* %1, align 4, !dbg !1016
  br label %if.end, !dbg !1017

if.end:                                           ; preds = %if.then, %entry
  %2 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1018
  %call = call i8* @__archive_read_ahead(%struct.archive_read* %2, i64 1, i64* %avail), !dbg !1019
  store i8* %call, i8** %p, align 8, !dbg !1020
  %3 = load i8*, i8** %p, align 8, !dbg !1021
  %cmp1 = icmp eq i8* %3, null, !dbg !1023
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !1024

if.then2:                                         ; preds = %if.end
  store i32 -1, i32* %retval, align 4, !dbg !1025
  br label %return, !dbg !1025

if.end3:                                          ; preds = %if.end
  %4 = load i64, i64* %avail, align 8, !dbg !1026
  store i64 %4, i64* %ravail, align 8, !dbg !1027
  br label %for.cond, !dbg !1028

for.cond:                                         ; preds = %if.end158, %if.end54, %if.then30, %if.end3
  %5 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1029
  %call4 = call i64 @next_line(%struct.archive_read* %5, i8** %p, i64* %avail, i64* %ravail, i64* %nl), !dbg !1033
  store i64 %call4, i64* %len, align 8, !dbg !1034
  %6 = load i64, i64* %len, align 8, !dbg !1035
  %cmp5 = icmp sle i64 %6, 0, !dbg !1037
  br i1 %cmp5, label %if.then7, label %lor.lhs.false, !dbg !1038

lor.lhs.false:                                    ; preds = %for.cond
  %7 = load i64, i64* %nl, align 8, !dbg !1039
  %cmp6 = icmp eq i64 %7, 0, !dbg !1041
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !1042

if.then7:                                         ; preds = %lor.lhs.false, %for.cond
  br label %for.end, !dbg !1043

if.end8:                                          ; preds = %lor.lhs.false
  %8 = load i32, i32* %multiline, align 4, !dbg !1044
  %tobool = icmp ne i32 %8, 0, !dbg !1044
  br i1 %tobool, label %if.else, label %if.then9, !dbg !1046

if.then9:                                         ; preds = %if.end8
  br label %while.cond, !dbg !1047

while.cond:                                       ; preds = %while.body, %if.then9
  %9 = load i64, i64* %len, align 8, !dbg !1049
  %cmp10 = icmp sgt i64 %9, 0, !dbg !1051
  br i1 %cmp10, label %land.rhs, label %land.end, !dbg !1052

land.rhs:                                         ; preds = %while.cond
  %10 = load i8*, i8** %p, align 8, !dbg !1053
  %11 = load i8, i8* %10, align 1, !dbg !1055
  %conv = sext i8 %11 to i32, !dbg !1055
  %cmp11 = icmp eq i32 %conv, 32, !dbg !1056
  br i1 %cmp11, label %lor.end, label %lor.rhs, !dbg !1057

lor.rhs:                                          ; preds = %land.rhs
  %12 = load i8*, i8** %p, align 8, !dbg !1058
  %13 = load i8, i8* %12, align 1, !dbg !1060
  %conv13 = sext i8 %13 to i32, !dbg !1060
  %cmp14 = icmp eq i32 %conv13, 9, !dbg !1061
  br label %lor.end, !dbg !1062

lor.end:                                          ; preds = %lor.rhs, %land.rhs
  %14 = phi i1 [ true, %land.rhs ], [ %cmp14, %lor.rhs ]
  br label %land.end

land.end:                                         ; preds = %lor.end, %while.cond
  %15 = phi i1 [ false, %while.cond ], [ %14, %lor.end ]
  br i1 %15, label %while.body, label %while.end, !dbg !1063

while.body:                                       ; preds = %land.end
  %16 = load i8*, i8** %p, align 8, !dbg !1065
  %incdec.ptr = getelementptr inbounds i8, i8* %16, i32 1, !dbg !1065
  store i8* %incdec.ptr, i8** %p, align 8, !dbg !1065
  %17 = load i64, i64* %avail, align 8, !dbg !1067
  %dec = add nsw i64 %17, -1, !dbg !1067
  store i64 %dec, i64* %avail, align 8, !dbg !1067
  %18 = load i64, i64* %len, align 8, !dbg !1068
  %dec16 = add nsw i64 %18, -1, !dbg !1068
  store i64 %dec16, i64* %len, align 8, !dbg !1068
  br label %while.cond, !dbg !1069

while.end:                                        ; preds = %land.end
  %19 = load i8*, i8** %p, align 8, !dbg !1071
  %arrayidx = getelementptr inbounds i8, i8* %19, i64 0, !dbg !1071
  %20 = load i8, i8* %arrayidx, align 1, !dbg !1071
  %conv17 = sext i8 %20 to i32, !dbg !1071
  %cmp18 = icmp eq i32 %conv17, 35, !dbg !1073
  br i1 %cmp18, label %if.then30, label %lor.lhs.false20, !dbg !1074

lor.lhs.false20:                                  ; preds = %while.end
  %21 = load i8*, i8** %p, align 8, !dbg !1075
  %arrayidx21 = getelementptr inbounds i8, i8* %21, i64 0, !dbg !1075
  %22 = load i8, i8* %arrayidx21, align 1, !dbg !1075
  %conv22 = sext i8 %22 to i32, !dbg !1075
  %cmp23 = icmp eq i32 %conv22, 10, !dbg !1077
  br i1 %cmp23, label %if.then30, label %lor.lhs.false25, !dbg !1078

lor.lhs.false25:                                  ; preds = %lor.lhs.false20
  %23 = load i8*, i8** %p, align 8, !dbg !1079
  %arrayidx26 = getelementptr inbounds i8, i8* %23, i64 0, !dbg !1079
  %24 = load i8, i8* %arrayidx26, align 1, !dbg !1079
  %conv27 = sext i8 %24 to i32, !dbg !1079
  %cmp28 = icmp eq i32 %conv27, 13, !dbg !1081
  br i1 %cmp28, label %if.then30, label %if.end31, !dbg !1082

if.then30:                                        ; preds = %lor.lhs.false25, %lor.lhs.false20, %while.end
  %25 = load i64, i64* %len, align 8, !dbg !1083
  %26 = load i8*, i8** %p, align 8, !dbg !1085
  %add.ptr = getelementptr inbounds i8, i8* %26, i64 %25, !dbg !1085
  store i8* %add.ptr, i8** %p, align 8, !dbg !1085
  %27 = load i64, i64* %len, align 8, !dbg !1086
  %28 = load i64, i64* %avail, align 8, !dbg !1087
  %sub = sub nsw i64 %28, %27, !dbg !1087
  store i64 %sub, i64* %avail, align 8, !dbg !1087
  br label %for.cond, !dbg !1088

if.end31:                                         ; preds = %lor.lhs.false25
  br label %if.end57, !dbg !1089

if.else:                                          ; preds = %if.end8
  %29 = load i8*, i8** %p, align 8, !dbg !1090
  %30 = load i64, i64* %len, align 8, !dbg !1093
  %call32 = call i32 @bid_keyword_list(i8* %29, i64 %30, i32 0, i32 0), !dbg !1094
  %cmp33 = icmp sle i32 %call32, 0, !dbg !1095
  br i1 %cmp33, label %if.then35, label %if.end36, !dbg !1096

if.then35:                                        ; preds = %if.else
  br label %for.end, !dbg !1097

if.end36:                                         ; preds = %if.else
  %31 = load i32, i32* %multiline, align 4, !dbg !1098
  %cmp37 = icmp eq i32 %31, 1, !dbg !1100
  br i1 %cmp37, label %if.then39, label %if.end40, !dbg !1101

if.then39:                                        ; preds = %if.end36
  %32 = load i64, i64* %len, align 8, !dbg !1102
  %33 = load i64, i64* %detected_bytes, align 8, !dbg !1103
  %add = add nsw i64 %33, %32, !dbg !1103
  store i64 %add, i64* %detected_bytes, align 8, !dbg !1103
  br label %if.end40, !dbg !1104

if.end40:                                         ; preds = %if.then39, %if.end36
  %34 = load i64, i64* %len, align 8, !dbg !1105
  %35 = load i64, i64* %nl, align 8, !dbg !1107
  %sub41 = sub nsw i64 %34, %35, !dbg !1108
  %sub42 = sub nsw i64 %sub41, 1, !dbg !1109
  %36 = load i8*, i8** %p, align 8, !dbg !1110
  %arrayidx43 = getelementptr inbounds i8, i8* %36, i64 %sub42, !dbg !1110
  %37 = load i8, i8* %arrayidx43, align 1, !dbg !1110
  %conv44 = sext i8 %37 to i32, !dbg !1110
  %cmp45 = icmp ne i32 %conv44, 92, !dbg !1111
  br i1 %cmp45, label %if.then47, label %if.end54, !dbg !1112

if.then47:                                        ; preds = %if.end40
  %38 = load i32, i32* %multiline, align 4, !dbg !1113
  %cmp48 = icmp eq i32 %38, 1, !dbg !1116
  br i1 %cmp48, label %land.lhs.true, label %if.end53, !dbg !1117

land.lhs.true:                                    ; preds = %if.then47
  %39 = load i32, i32* %entry_cnt, align 4, !dbg !1118
  %inc = add nsw i32 %39, 1, !dbg !1118
  store i32 %inc, i32* %entry_cnt, align 4, !dbg !1118
  %cmp50 = icmp sge i32 %inc, 3, !dbg !1119
  br i1 %cmp50, label %if.then52, label %if.end53, !dbg !1120

if.then52:                                        ; preds = %land.lhs.true
  br label %for.end, !dbg !1122

if.end53:                                         ; preds = %land.lhs.true, %if.then47
  store i32 0, i32* %multiline, align 4, !dbg !1123
  br label %if.end54, !dbg !1124

if.end54:                                         ; preds = %if.end53, %if.end40
  %40 = load i64, i64* %len, align 8, !dbg !1125
  %41 = load i8*, i8** %p, align 8, !dbg !1126
  %add.ptr55 = getelementptr inbounds i8, i8* %41, i64 %40, !dbg !1126
  store i8* %add.ptr55, i8** %p, align 8, !dbg !1126
  %42 = load i64, i64* %len, align 8, !dbg !1127
  %43 = load i64, i64* %avail, align 8, !dbg !1128
  %sub56 = sub nsw i64 %43, %42, !dbg !1128
  store i64 %sub56, i64* %avail, align 8, !dbg !1128
  br label %for.cond, !dbg !1129

if.end57:                                         ; preds = %if.end31
  %44 = load i8*, i8** %p, align 8, !dbg !1130
  %arrayidx58 = getelementptr inbounds i8, i8* %44, i64 0, !dbg !1130
  %45 = load i8, i8* %arrayidx58, align 1, !dbg !1130
  %conv59 = sext i8 %45 to i32, !dbg !1130
  %cmp60 = icmp ne i32 %conv59, 47, !dbg !1132
  br i1 %cmp60, label %if.then62, label %if.else109, !dbg !1133

if.then62:                                        ; preds = %if.end57
  call void @llvm.dbg.declare(metadata i32* %last_is_path, metadata !1134, metadata !460), !dbg !1136
  call void @llvm.dbg.declare(metadata i32* %keywords, metadata !1137, metadata !460), !dbg !1138
  %46 = load i8*, i8** %p, align 8, !dbg !1139
  %47 = load i64, i64* %len, align 8, !dbg !1140
  %48 = load i64, i64* %nl, align 8, !dbg !1141
  %call63 = call i32 @bid_entry(i8* %46, i64 %47, i64 %48, i32* %last_is_path), !dbg !1142
  store i32 %call63, i32* %keywords, align 4, !dbg !1143
  %49 = load i32, i32* %keywords, align 4, !dbg !1144
  %cmp64 = icmp sge i32 %49, 0, !dbg !1146
  br i1 %cmp64, label %if.then66, label %if.else107, !dbg !1147

if.then66:                                        ; preds = %if.then62
  %50 = load i64, i64* %len, align 8, !dbg !1148
  %51 = load i64, i64* %detected_bytes, align 8, !dbg !1150
  %add67 = add nsw i64 %51, %50, !dbg !1150
  store i64 %add67, i64* %detected_bytes, align 8, !dbg !1150
  %52 = load i32, i32* %form_D, align 4, !dbg !1151
  %cmp68 = icmp eq i32 %52, 0, !dbg !1153
  br i1 %cmp68, label %if.then70, label %if.else79, !dbg !1154

if.then70:                                        ; preds = %if.then66
  %53 = load i32, i32* %last_is_path, align 4, !dbg !1155
  %tobool71 = icmp ne i32 %53, 0, !dbg !1155
  br i1 %tobool71, label %if.then72, label %if.else73, !dbg !1158

if.then72:                                        ; preds = %if.then70
  store i32 1, i32* %form_D, align 4, !dbg !1159
  br label %if.end78, !dbg !1160

if.else73:                                        ; preds = %if.then70
  %54 = load i32, i32* %keywords, align 4, !dbg !1161
  %cmp74 = icmp sgt i32 %54, 0, !dbg !1163
  br i1 %cmp74, label %if.then76, label %if.end77, !dbg !1164

if.then76:                                        ; preds = %if.else73
  store i32 -1, i32* %form_D, align 4, !dbg !1165
  br label %if.end77, !dbg !1166

if.end77:                                         ; preds = %if.then76, %if.else73
  br label %if.end78

if.end78:                                         ; preds = %if.end77, %if.then72
  br label %if.end90, !dbg !1167

if.else79:                                        ; preds = %if.then66
  %55 = load i32, i32* %form_D, align 4, !dbg !1168
  %cmp80 = icmp eq i32 %55, 1, !dbg !1171
  br i1 %cmp80, label %if.then82, label %if.end89, !dbg !1168

if.then82:                                        ; preds = %if.else79
  %56 = load i32, i32* %last_is_path, align 4, !dbg !1172
  %tobool83 = icmp ne i32 %56, 0, !dbg !1172
  br i1 %tobool83, label %if.end88, label %land.lhs.true84, !dbg !1175

land.lhs.true84:                                  ; preds = %if.then82
  %57 = load i32, i32* %keywords, align 4, !dbg !1176
  %cmp85 = icmp sgt i32 %57, 0, !dbg !1178
  br i1 %cmp85, label %if.then87, label %if.end88, !dbg !1179

if.then87:                                        ; preds = %land.lhs.true84
  br label %for.end, !dbg !1180

if.end88:                                         ; preds = %land.lhs.true84, %if.then82
  br label %if.end89, !dbg !1181

if.end89:                                         ; preds = %if.end88, %if.else79
  br label %if.end90

if.end90:                                         ; preds = %if.end89, %if.end78
  %58 = load i32, i32* %last_is_path, align 4, !dbg !1182
  %tobool91 = icmp ne i32 %58, 0, !dbg !1182
  br i1 %tobool91, label %if.else100, label %land.lhs.true92, !dbg !1184

land.lhs.true92:                                  ; preds = %if.end90
  %59 = load i64, i64* %len, align 8, !dbg !1185
  %60 = load i64, i64* %nl, align 8, !dbg !1187
  %sub93 = sub nsw i64 %59, %60, !dbg !1188
  %sub94 = sub nsw i64 %sub93, 1, !dbg !1189
  %61 = load i8*, i8** %p, align 8, !dbg !1190
  %arrayidx95 = getelementptr inbounds i8, i8* %61, i64 %sub94, !dbg !1190
  %62 = load i8, i8* %arrayidx95, align 1, !dbg !1190
  %conv96 = sext i8 %62 to i32, !dbg !1190
  %cmp97 = icmp eq i32 %conv96, 92, !dbg !1191
  br i1 %cmp97, label %if.then99, label %if.else100, !dbg !1192

if.then99:                                        ; preds = %land.lhs.true92
  store i32 1, i32* %multiline, align 4, !dbg !1193
  br label %if.end106, !dbg !1194

if.else100:                                       ; preds = %land.lhs.true92, %if.end90
  %63 = load i32, i32* %entry_cnt, align 4, !dbg !1195
  %inc101 = add nsw i32 %63, 1, !dbg !1195
  store i32 %inc101, i32* %entry_cnt, align 4, !dbg !1195
  %cmp102 = icmp sge i32 %inc101, 3, !dbg !1198
  br i1 %cmp102, label %if.then104, label %if.end105, !dbg !1199

if.then104:                                       ; preds = %if.else100
  br label %for.end, !dbg !1200

if.end105:                                        ; preds = %if.else100
  br label %if.end106

if.end106:                                        ; preds = %if.end105, %if.then99
  br label %if.end108, !dbg !1201

if.else107:                                       ; preds = %if.then62
  br label %for.end, !dbg !1202

if.end108:                                        ; preds = %if.end106
  br label %if.end158, !dbg !1203

if.else109:                                       ; preds = %if.end57
  %64 = load i64, i64* %len, align 8, !dbg !1204
  %cmp110 = icmp sgt i64 %64, 4, !dbg !1207
  br i1 %cmp110, label %land.lhs.true112, label %if.else132, !dbg !1208

land.lhs.true112:                                 ; preds = %if.else109
  %65 = load i8*, i8** %p, align 8, !dbg !1209
  %call113 = call i32 @strncmp(i8* %65, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.5, i32 0, i32 0), i64 4) #8, !dbg !1211
  %cmp114 = icmp eq i32 %call113, 0, !dbg !1212
  br i1 %cmp114, label %if.then116, label %if.else132, !dbg !1213

if.then116:                                       ; preds = %land.lhs.true112
  %66 = load i8*, i8** %p, align 8, !dbg !1214
  %add.ptr117 = getelementptr inbounds i8, i8* %66, i64 4, !dbg !1217
  %67 = load i64, i64* %len, align 8, !dbg !1218
  %sub118 = sub nsw i64 %67, 4, !dbg !1219
  %call119 = call i32 @bid_keyword_list(i8* %add.ptr117, i64 %sub118, i32 0, i32 0), !dbg !1220
  %cmp120 = icmp sle i32 %call119, 0, !dbg !1221
  br i1 %cmp120, label %if.then122, label %if.end123, !dbg !1222

if.then122:                                       ; preds = %if.then116
  br label %for.end, !dbg !1223

if.end123:                                        ; preds = %if.then116
  %68 = load i64, i64* %len, align 8, !dbg !1224
  %69 = load i64, i64* %nl, align 8, !dbg !1226
  %sub124 = sub nsw i64 %68, %69, !dbg !1227
  %sub125 = sub nsw i64 %sub124, 1, !dbg !1228
  %70 = load i8*, i8** %p, align 8, !dbg !1229
  %arrayidx126 = getelementptr inbounds i8, i8* %70, i64 %sub125, !dbg !1229
  %71 = load i8, i8* %arrayidx126, align 1, !dbg !1229
  %conv127 = sext i8 %71 to i32, !dbg !1229
  %cmp128 = icmp eq i32 %conv127, 92, !dbg !1230
  br i1 %cmp128, label %if.then130, label %if.end131, !dbg !1231

if.then130:                                       ; preds = %if.end123
  store i32 2, i32* %multiline, align 4, !dbg !1232
  br label %if.end131, !dbg !1233

if.end131:                                        ; preds = %if.then130, %if.end123
  br label %if.end157, !dbg !1234

if.else132:                                       ; preds = %land.lhs.true112, %if.else109
  %72 = load i64, i64* %len, align 8, !dbg !1235
  %cmp133 = icmp sgt i64 %72, 6, !dbg !1238
  br i1 %cmp133, label %land.lhs.true135, label %if.else155, !dbg !1239

land.lhs.true135:                                 ; preds = %if.else132
  %73 = load i8*, i8** %p, align 8, !dbg !1240
  %call136 = call i32 @strncmp(i8* %73, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.6, i32 0, i32 0), i64 6) #8, !dbg !1242
  %cmp137 = icmp eq i32 %call136, 0, !dbg !1243
  br i1 %cmp137, label %if.then139, label %if.else155, !dbg !1244

if.then139:                                       ; preds = %land.lhs.true135
  %74 = load i8*, i8** %p, align 8, !dbg !1245
  %add.ptr140 = getelementptr inbounds i8, i8* %74, i64 6, !dbg !1248
  %75 = load i64, i64* %len, align 8, !dbg !1249
  %sub141 = sub nsw i64 %75, 6, !dbg !1250
  %call142 = call i32 @bid_keyword_list(i8* %add.ptr140, i64 %sub141, i32 1, i32 0), !dbg !1251
  %cmp143 = icmp sle i32 %call142, 0, !dbg !1252
  br i1 %cmp143, label %if.then145, label %if.end146, !dbg !1253

if.then145:                                       ; preds = %if.then139
  br label %for.end, !dbg !1254

if.end146:                                        ; preds = %if.then139
  %76 = load i64, i64* %len, align 8, !dbg !1255
  %77 = load i64, i64* %nl, align 8, !dbg !1257
  %sub147 = sub nsw i64 %76, %77, !dbg !1258
  %sub148 = sub nsw i64 %sub147, 1, !dbg !1259
  %78 = load i8*, i8** %p, align 8, !dbg !1260
  %arrayidx149 = getelementptr inbounds i8, i8* %78, i64 %sub148, !dbg !1260
  %79 = load i8, i8* %arrayidx149, align 1, !dbg !1260
  %conv150 = sext i8 %79 to i32, !dbg !1260
  %cmp151 = icmp eq i32 %conv150, 92, !dbg !1261
  br i1 %cmp151, label %if.then153, label %if.end154, !dbg !1262

if.then153:                                       ; preds = %if.end146
  store i32 2, i32* %multiline, align 4, !dbg !1263
  br label %if.end154, !dbg !1264

if.end154:                                        ; preds = %if.then153, %if.end146
  br label %if.end156, !dbg !1265

if.else155:                                       ; preds = %land.lhs.true135, %if.else132
  br label %for.end, !dbg !1266

if.end156:                                        ; preds = %if.end154
  br label %if.end157

if.end157:                                        ; preds = %if.end156, %if.end131
  br label %if.end158

if.end158:                                        ; preds = %if.end157, %if.end108
  %80 = load i64, i64* %len, align 8, !dbg !1267
  %81 = load i8*, i8** %p, align 8, !dbg !1268
  %add.ptr159 = getelementptr inbounds i8, i8* %81, i64 %80, !dbg !1268
  store i8* %add.ptr159, i8** %p, align 8, !dbg !1268
  %82 = load i64, i64* %len, align 8, !dbg !1269
  %83 = load i64, i64* %avail, align 8, !dbg !1270
  %sub160 = sub nsw i64 %83, %82, !dbg !1270
  store i64 %sub160, i64* %avail, align 8, !dbg !1270
  br label %for.cond, !dbg !1271

for.end:                                          ; preds = %if.else155, %if.then145, %if.then122, %if.else107, %if.then104, %if.then87, %if.then52, %if.then35, %if.then7
  %84 = load i32, i32* %entry_cnt, align 4, !dbg !1273
  %cmp161 = icmp sge i32 %84, 3, !dbg !1275
  br i1 %cmp161, label %if.then169, label %lor.lhs.false163, !dbg !1276

lor.lhs.false163:                                 ; preds = %for.end
  %85 = load i32, i32* %entry_cnt, align 4, !dbg !1277
  %cmp164 = icmp sgt i32 %85, 0, !dbg !1279
  br i1 %cmp164, label %land.lhs.true166, label %if.end178, !dbg !1280

land.lhs.true166:                                 ; preds = %lor.lhs.false163
  %86 = load i64, i64* %len, align 8, !dbg !1281
  %cmp167 = icmp eq i64 %86, 0, !dbg !1283
  br i1 %cmp167, label %if.then169, label %if.end178, !dbg !1284

if.then169:                                       ; preds = %land.lhs.true166, %for.end
  %87 = load i32*, i32** %is_form_d.addr, align 8, !dbg !1285
  %cmp170 = icmp ne i32* %87, null, !dbg !1288
  br i1 %cmp170, label %if.then172, label %if.end177, !dbg !1289

if.then172:                                       ; preds = %if.then169
  %88 = load i32, i32* %form_D, align 4, !dbg !1290
  %cmp173 = icmp eq i32 %88, 1, !dbg !1293
  br i1 %cmp173, label %if.then175, label %if.end176, !dbg !1294

if.then175:                                       ; preds = %if.then172
  %89 = load i32*, i32** %is_form_d.addr, align 8, !dbg !1295
  store i32 1, i32* %89, align 4, !dbg !1296
  br label %if.end176, !dbg !1297

if.end176:                                        ; preds = %if.then175, %if.then172
  br label %if.end177, !dbg !1298

if.end177:                                        ; preds = %if.end176, %if.then169
  store i32 32, i32* %retval, align 4, !dbg !1299
  br label %return, !dbg !1299

if.end178:                                        ; preds = %land.lhs.true166, %lor.lhs.false163
  store i32 0, i32* %retval, align 4, !dbg !1300
  br label %return, !dbg !1300

return:                                           ; preds = %if.end178, %if.end177, %if.then2
  %90 = load i32, i32* %retval, align 4, !dbg !1301
  ret i32 %90, !dbg !1301
}

; Function Attrs: nounwind uwtable
define internal i64 @next_line(%struct.archive_read* %a, i8** %b, i64* %avail, i64* %ravail, i64* %nl) #0 !dbg !354 {
entry:
  %retval = alloca i64, align 8
  %a.addr = alloca %struct.archive_read*, align 8
  %b.addr = alloca i8**, align 8
  %avail.addr = alloca i64*, align 8
  %ravail.addr = alloca i64*, align 8
  %nl.addr = alloca i64*, align 8
  %len = alloca i64, align 8
  %quit = alloca i32, align 4
  %diff = alloca i64, align 8
  %nbytes_req = alloca i64, align 8
  %tested = alloca i64, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !1302, metadata !460), !dbg !1303
  store i8** %b, i8*** %b.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %b.addr, metadata !1304, metadata !460), !dbg !1305
  store i64* %avail, i64** %avail.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %avail.addr, metadata !1306, metadata !460), !dbg !1307
  store i64* %ravail, i64** %ravail.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %ravail.addr, metadata !1308, metadata !460), !dbg !1309
  store i64* %nl, i64** %nl.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %nl.addr, metadata !1310, metadata !460), !dbg !1311
  call void @llvm.dbg.declare(metadata i64* %len, metadata !1312, metadata !460), !dbg !1313
  call void @llvm.dbg.declare(metadata i32* %quit, metadata !1314, metadata !460), !dbg !1315
  store i32 0, i32* %quit, align 4, !dbg !1316
  %0 = load i64*, i64** %avail.addr, align 8, !dbg !1317
  %1 = load i64, i64* %0, align 8, !dbg !1319
  %cmp = icmp eq i64 %1, 0, !dbg !1320
  br i1 %cmp, label %if.then, label %if.else, !dbg !1321

if.then:                                          ; preds = %entry
  %2 = load i64*, i64** %nl.addr, align 8, !dbg !1322
  store i64 0, i64* %2, align 8, !dbg !1324
  store i64 0, i64* %len, align 8, !dbg !1325
  br label %if.end, !dbg !1326

if.else:                                          ; preds = %entry
  %3 = load i8**, i8*** %b.addr, align 8, !dbg !1327
  %4 = load i8*, i8** %3, align 8, !dbg !1328
  %5 = load i64*, i64** %avail.addr, align 8, !dbg !1329
  %6 = load i64, i64* %5, align 8, !dbg !1330
  %7 = load i64*, i64** %nl.addr, align 8, !dbg !1331
  %call = call i64 @get_line_size(i8* %4, i64 %6, i64* %7), !dbg !1332
  store i64 %call, i64* %len, align 8, !dbg !1333
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  br label %while.cond, !dbg !1334

while.cond:                                       ; preds = %if.end22, %if.end
  %8 = load i64*, i64** %nl.addr, align 8, !dbg !1335
  %9 = load i64, i64* %8, align 8, !dbg !1337
  %cmp1 = icmp eq i64 %9, 0, !dbg !1338
  br i1 %cmp1, label %land.lhs.true, label %land.end, !dbg !1339

land.lhs.true:                                    ; preds = %while.cond
  %10 = load i64, i64* %len, align 8, !dbg !1340
  %11 = load i64*, i64** %avail.addr, align 8, !dbg !1342
  %12 = load i64, i64* %11, align 8, !dbg !1343
  %cmp2 = icmp eq i64 %10, %12, !dbg !1344
  br i1 %cmp2, label %land.rhs, label %land.end, !dbg !1345

land.rhs:                                         ; preds = %land.lhs.true
  %13 = load i32, i32* %quit, align 4, !dbg !1346
  %tobool = icmp ne i32 %13, 0, !dbg !1348
  %lnot = xor i1 %tobool, true, !dbg !1348
  br label %land.end

land.end:                                         ; preds = %land.rhs, %land.lhs.true, %while.cond
  %14 = phi i1 [ false, %land.lhs.true ], [ false, %while.cond ], [ %lnot, %land.rhs ]
  br i1 %14, label %while.body, label %while.end, !dbg !1349

while.body:                                       ; preds = %land.end
  call void @llvm.dbg.declare(metadata i64* %diff, metadata !1351, metadata !460), !dbg !1353
  %15 = load i64*, i64** %ravail.addr, align 8, !dbg !1354
  %16 = load i64, i64* %15, align 8, !dbg !1355
  %17 = load i64*, i64** %avail.addr, align 8, !dbg !1356
  %18 = load i64, i64* %17, align 8, !dbg !1357
  %sub = sub nsw i64 %16, %18, !dbg !1358
  store i64 %sub, i64* %diff, align 8, !dbg !1353
  call void @llvm.dbg.declare(metadata i64* %nbytes_req, metadata !1359, metadata !460), !dbg !1360
  %19 = load i64*, i64** %ravail.addr, align 8, !dbg !1361
  %20 = load i64, i64* %19, align 8, !dbg !1362
  %add = add nsw i64 %20, 1023, !dbg !1363
  %and = and i64 %add, 4294966272, !dbg !1364
  store i64 %and, i64* %nbytes_req, align 8, !dbg !1360
  call void @llvm.dbg.declare(metadata i64* %tested, metadata !1365, metadata !460), !dbg !1366
  %21 = load i64, i64* %nbytes_req, align 8, !dbg !1367
  %22 = load i64*, i64** %ravail.addr, align 8, !dbg !1369
  %23 = load i64, i64* %22, align 8, !dbg !1370
  %add3 = add i64 %23, 160, !dbg !1371
  %cmp4 = icmp ult i64 %21, %add3, !dbg !1372
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !1373

if.then5:                                         ; preds = %while.body
  %24 = load i64, i64* %nbytes_req, align 8, !dbg !1374
  %shl = shl i64 %24, 1, !dbg !1374
  store i64 %shl, i64* %nbytes_req, align 8, !dbg !1374
  br label %if.end6, !dbg !1375

if.end6:                                          ; preds = %if.then5, %while.body
  %25 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1376
  %26 = load i64, i64* %nbytes_req, align 8, !dbg !1377
  %27 = load i64*, i64** %avail.addr, align 8, !dbg !1378
  %call7 = call i8* @__archive_read_ahead(%struct.archive_read* %25, i64 %26, i64* %27), !dbg !1379
  %28 = load i8**, i8*** %b.addr, align 8, !dbg !1380
  store i8* %call7, i8** %28, align 8, !dbg !1381
  %29 = load i8**, i8*** %b.addr, align 8, !dbg !1382
  %30 = load i8*, i8** %29, align 8, !dbg !1384
  %cmp8 = icmp eq i8* %30, null, !dbg !1385
  br i1 %cmp8, label %if.then9, label %if.end14, !dbg !1386

if.then9:                                         ; preds = %if.end6
  %31 = load i64*, i64** %ravail.addr, align 8, !dbg !1387
  %32 = load i64, i64* %31, align 8, !dbg !1390
  %33 = load i64*, i64** %avail.addr, align 8, !dbg !1391
  %34 = load i64, i64* %33, align 8, !dbg !1392
  %cmp10 = icmp sge i64 %32, %34, !dbg !1393
  br i1 %cmp10, label %if.then11, label %if.end12, !dbg !1394

if.then11:                                        ; preds = %if.then9
  store i64 0, i64* %retval, align 8, !dbg !1395
  br label %return, !dbg !1395

if.end12:                                         ; preds = %if.then9
  %35 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1396
  %36 = load i64*, i64** %avail.addr, align 8, !dbg !1397
  %37 = load i64, i64* %36, align 8, !dbg !1398
  %38 = load i64*, i64** %avail.addr, align 8, !dbg !1399
  %call13 = call i8* @__archive_read_ahead(%struct.archive_read* %35, i64 %37, i64* %38), !dbg !1400
  %39 = load i8**, i8*** %b.addr, align 8, !dbg !1401
  store i8* %call13, i8** %39, align 8, !dbg !1402
  store i32 1, i32* %quit, align 4, !dbg !1403
  br label %if.end14, !dbg !1404

if.end14:                                         ; preds = %if.end12, %if.end6
  %40 = load i64*, i64** %avail.addr, align 8, !dbg !1405
  %41 = load i64, i64* %40, align 8, !dbg !1406
  %42 = load i64*, i64** %ravail.addr, align 8, !dbg !1407
  store i64 %41, i64* %42, align 8, !dbg !1408
  %43 = load i64, i64* %diff, align 8, !dbg !1409
  %44 = load i8**, i8*** %b.addr, align 8, !dbg !1410
  %45 = load i8*, i8** %44, align 8, !dbg !1411
  %add.ptr = getelementptr inbounds i8, i8* %45, i64 %43, !dbg !1411
  store i8* %add.ptr, i8** %44, align 8, !dbg !1411
  %46 = load i64, i64* %diff, align 8, !dbg !1412
  %47 = load i64*, i64** %avail.addr, align 8, !dbg !1413
  %48 = load i64, i64* %47, align 8, !dbg !1414
  %sub15 = sub nsw i64 %48, %46, !dbg !1414
  store i64 %sub15, i64* %47, align 8, !dbg !1414
  %49 = load i64, i64* %len, align 8, !dbg !1415
  store i64 %49, i64* %tested, align 8, !dbg !1416
  %50 = load i8**, i8*** %b.addr, align 8, !dbg !1417
  %51 = load i8*, i8** %50, align 8, !dbg !1418
  %52 = load i64, i64* %len, align 8, !dbg !1419
  %add.ptr16 = getelementptr inbounds i8, i8* %51, i64 %52, !dbg !1420
  %53 = load i64*, i64** %avail.addr, align 8, !dbg !1421
  %54 = load i64, i64* %53, align 8, !dbg !1422
  %55 = load i64, i64* %len, align 8, !dbg !1423
  %sub17 = sub nsw i64 %54, %55, !dbg !1424
  %56 = load i64*, i64** %nl.addr, align 8, !dbg !1425
  %call18 = call i64 @get_line_size(i8* %add.ptr16, i64 %sub17, i64* %56), !dbg !1426
  store i64 %call18, i64* %len, align 8, !dbg !1427
  %57 = load i64, i64* %len, align 8, !dbg !1428
  %cmp19 = icmp sge i64 %57, 0, !dbg !1430
  br i1 %cmp19, label %if.then20, label %if.end22, !dbg !1431

if.then20:                                        ; preds = %if.end14
  %58 = load i64, i64* %tested, align 8, !dbg !1432
  %59 = load i64, i64* %len, align 8, !dbg !1433
  %add21 = add nsw i64 %59, %58, !dbg !1433
  store i64 %add21, i64* %len, align 8, !dbg !1433
  br label %if.end22, !dbg !1434

if.end22:                                         ; preds = %if.then20, %if.end14
  br label %while.cond, !dbg !1435

while.end:                                        ; preds = %land.end
  %60 = load i64, i64* %len, align 8, !dbg !1437
  store i64 %60, i64* %retval, align 8, !dbg !1438
  br label %return, !dbg !1438

return:                                           ; preds = %while.end, %if.then11
  %61 = load i64, i64* %retval, align 8, !dbg !1439
  ret i64 %61, !dbg !1439
}

; Function Attrs: nounwind uwtable
define internal i32 @bid_keyword_list(i8* %p, i64 %len, i32 %unset, i32 %last_is_path) #0 !dbg !362 {
entry:
  %retval = alloca i32, align 4
  %p.addr = alloca i8*, align 8
  %len.addr = alloca i64, align 8
  %unset.addr = alloca i32, align 4
  %last_is_path.addr = alloca i32, align 4
  %l = alloca i32, align 4
  %keycnt = alloca i32, align 4
  %blank = alloca i32, align 4
  %value = alloca i32, align 4
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !1440, metadata !460), !dbg !1441
  store i64 %len, i64* %len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %len.addr, metadata !1442, metadata !460), !dbg !1443
  store i32 %unset, i32* %unset.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %unset.addr, metadata !1444, metadata !460), !dbg !1445
  store i32 %last_is_path, i32* %last_is_path.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %last_is_path.addr, metadata !1446, metadata !460), !dbg !1447
  call void @llvm.dbg.declare(metadata i32* %l, metadata !1448, metadata !460), !dbg !1449
  call void @llvm.dbg.declare(metadata i32* %keycnt, metadata !1450, metadata !460), !dbg !1451
  store i32 0, i32* %keycnt, align 4, !dbg !1451
  br label %while.cond, !dbg !1452

while.cond:                                       ; preds = %if.end85, %entry
  %0 = load i64, i64* %len.addr, align 8, !dbg !1453
  %cmp = icmp sgt i64 %0, 0, !dbg !1455
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !1456

land.rhs:                                         ; preds = %while.cond
  %1 = load i8*, i8** %p.addr, align 8, !dbg !1457
  %2 = load i8, i8* %1, align 1, !dbg !1459
  %conv = sext i8 %2 to i32, !dbg !1459
  %tobool = icmp ne i32 %conv, 0, !dbg !1460
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond
  %3 = phi i1 [ false, %while.cond ], [ %tobool, %land.rhs ]
  br i1 %3, label %while.body, label %while.end86, !dbg !1461

while.body:                                       ; preds = %land.end
  call void @llvm.dbg.declare(metadata i32* %blank, metadata !1463, metadata !460), !dbg !1465
  store i32 0, i32* %blank, align 4, !dbg !1465
  br label %while.cond1, !dbg !1466

while.cond1:                                      ; preds = %while.body12, %while.body
  %4 = load i64, i64* %len.addr, align 8, !dbg !1467
  %cmp2 = icmp sgt i64 %4, 0, !dbg !1469
  br i1 %cmp2, label %land.rhs4, label %land.end11, !dbg !1470

land.rhs4:                                        ; preds = %while.cond1
  %5 = load i8*, i8** %p.addr, align 8, !dbg !1471
  %6 = load i8, i8* %5, align 1, !dbg !1473
  %conv5 = sext i8 %6 to i32, !dbg !1473
  %cmp6 = icmp eq i32 %conv5, 32, !dbg !1474
  br i1 %cmp6, label %lor.end, label %lor.rhs, !dbg !1475

lor.rhs:                                          ; preds = %land.rhs4
  %7 = load i8*, i8** %p.addr, align 8, !dbg !1476
  %8 = load i8, i8* %7, align 1, !dbg !1478
  %conv8 = sext i8 %8 to i32, !dbg !1478
  %cmp9 = icmp eq i32 %conv8, 9, !dbg !1479
  br label %lor.end, !dbg !1480

lor.end:                                          ; preds = %lor.rhs, %land.rhs4
  %9 = phi i1 [ true, %land.rhs4 ], [ %cmp9, %lor.rhs ]
  br label %land.end11

land.end11:                                       ; preds = %lor.end, %while.cond1
  %10 = phi i1 [ false, %while.cond1 ], [ %9, %lor.end ]
  br i1 %10, label %while.body12, label %while.end, !dbg !1481

while.body12:                                     ; preds = %land.end11
  %11 = load i8*, i8** %p.addr, align 8, !dbg !1483
  %incdec.ptr = getelementptr inbounds i8, i8* %11, i32 1, !dbg !1483
  store i8* %incdec.ptr, i8** %p.addr, align 8, !dbg !1483
  %12 = load i64, i64* %len.addr, align 8, !dbg !1485
  %dec = add nsw i64 %12, -1, !dbg !1485
  store i64 %dec, i64* %len.addr, align 8, !dbg !1485
  store i32 1, i32* %blank, align 4, !dbg !1486
  br label %while.cond1, !dbg !1487

while.end:                                        ; preds = %land.end11
  %13 = load i8*, i8** %p.addr, align 8, !dbg !1489
  %14 = load i8, i8* %13, align 1, !dbg !1491
  %conv13 = sext i8 %14 to i32, !dbg !1491
  %cmp14 = icmp eq i32 %conv13, 10, !dbg !1492
  br i1 %cmp14, label %if.then, label %lor.lhs.false, !dbg !1493

lor.lhs.false:                                    ; preds = %while.end
  %15 = load i8*, i8** %p.addr, align 8, !dbg !1494
  %16 = load i8, i8* %15, align 1, !dbg !1496
  %conv16 = sext i8 %16 to i32, !dbg !1496
  %cmp17 = icmp eq i32 %conv16, 13, !dbg !1497
  br i1 %cmp17, label %if.then, label %if.end, !dbg !1498

if.then:                                          ; preds = %lor.lhs.false, %while.end
  br label %while.end86, !dbg !1499

if.end:                                           ; preds = %lor.lhs.false
  %17 = load i8*, i8** %p.addr, align 8, !dbg !1500
  %arrayidx = getelementptr inbounds i8, i8* %17, i64 0, !dbg !1500
  %18 = load i8, i8* %arrayidx, align 1, !dbg !1500
  %conv19 = sext i8 %18 to i32, !dbg !1500
  %cmp20 = icmp eq i32 %conv19, 92, !dbg !1502
  br i1 %cmp20, label %land.lhs.true, label %if.end32, !dbg !1503

land.lhs.true:                                    ; preds = %if.end
  %19 = load i8*, i8** %p.addr, align 8, !dbg !1504
  %arrayidx22 = getelementptr inbounds i8, i8* %19, i64 1, !dbg !1504
  %20 = load i8, i8* %arrayidx22, align 1, !dbg !1504
  %conv23 = sext i8 %20 to i32, !dbg !1504
  %cmp24 = icmp eq i32 %conv23, 10, !dbg !1506
  br i1 %cmp24, label %if.then31, label %lor.lhs.false26, !dbg !1507

lor.lhs.false26:                                  ; preds = %land.lhs.true
  %21 = load i8*, i8** %p.addr, align 8, !dbg !1508
  %arrayidx27 = getelementptr inbounds i8, i8* %21, i64 1, !dbg !1508
  %22 = load i8, i8* %arrayidx27, align 1, !dbg !1508
  %conv28 = sext i8 %22 to i32, !dbg !1508
  %cmp29 = icmp eq i32 %conv28, 13, !dbg !1510
  br i1 %cmp29, label %if.then31, label %if.end32, !dbg !1511

if.then31:                                        ; preds = %lor.lhs.false26, %land.lhs.true
  br label %while.end86, !dbg !1512

if.end32:                                         ; preds = %lor.lhs.false26, %if.end
  %23 = load i32, i32* %blank, align 4, !dbg !1513
  %tobool33 = icmp ne i32 %23, 0, !dbg !1513
  br i1 %tobool33, label %if.end37, label %land.lhs.true34, !dbg !1515

land.lhs.true34:                                  ; preds = %if.end32
  %24 = load i32, i32* %last_is_path.addr, align 4, !dbg !1516
  %tobool35 = icmp ne i32 %24, 0, !dbg !1516
  br i1 %tobool35, label %if.end37, label %if.then36, !dbg !1518

if.then36:                                        ; preds = %land.lhs.true34
  store i32 -1, i32* %retval, align 4, !dbg !1519
  br label %return, !dbg !1519

if.end37:                                         ; preds = %land.lhs.true34, %if.end32
  %25 = load i32, i32* %last_is_path.addr, align 4, !dbg !1520
  %tobool38 = icmp ne i32 %25, 0, !dbg !1520
  br i1 %tobool38, label %land.lhs.true39, label %if.end43, !dbg !1522

land.lhs.true39:                                  ; preds = %if.end37
  %26 = load i64, i64* %len.addr, align 8, !dbg !1523
  %cmp40 = icmp eq i64 %26, 0, !dbg !1525
  br i1 %cmp40, label %if.then42, label %if.end43, !dbg !1526

if.then42:                                        ; preds = %land.lhs.true39
  %27 = load i32, i32* %keycnt, align 4, !dbg !1527
  store i32 %27, i32* %retval, align 4, !dbg !1528
  br label %return, !dbg !1528

if.end43:                                         ; preds = %land.lhs.true39, %if.end37
  %28 = load i32, i32* %unset.addr, align 4, !dbg !1529
  %tobool44 = icmp ne i32 %28, 0, !dbg !1529
  br i1 %tobool44, label %if.then45, label %if.end50, !dbg !1531

if.then45:                                        ; preds = %if.end43
  %29 = load i8*, i8** %p.addr, align 8, !dbg !1532
  %30 = load i64, i64* %len.addr, align 8, !dbg !1534
  %call = call i32 @bid_keycmp(i8* %29, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.7, i32 0, i32 0), i64 %30), !dbg !1535
  store i32 %call, i32* %l, align 4, !dbg !1536
  %31 = load i32, i32* %l, align 4, !dbg !1537
  %cmp46 = icmp sgt i32 %31, 0, !dbg !1539
  br i1 %cmp46, label %if.then48, label %if.end49, !dbg !1540

if.then48:                                        ; preds = %if.then45
  store i32 1, i32* %retval, align 4, !dbg !1541
  br label %return, !dbg !1541

if.end49:                                         ; preds = %if.then45
  br label %if.end50, !dbg !1542

if.end50:                                         ; preds = %if.end49, %if.end43
  %32 = load i8*, i8** %p.addr, align 8, !dbg !1543
  %33 = load i64, i64* %len.addr, align 8, !dbg !1544
  %call51 = call i32 @bid_keyword(i8* %32, i64 %33), !dbg !1545
  store i32 %call51, i32* %l, align 4, !dbg !1546
  %34 = load i32, i32* %l, align 4, !dbg !1547
  %cmp52 = icmp eq i32 %34, 0, !dbg !1549
  br i1 %cmp52, label %if.then54, label %if.end55, !dbg !1550

if.then54:                                        ; preds = %if.end50
  store i32 -1, i32* %retval, align 4, !dbg !1551
  br label %return, !dbg !1551

if.end55:                                         ; preds = %if.end50
  %35 = load i32, i32* %l, align 4, !dbg !1552
  %36 = load i8*, i8** %p.addr, align 8, !dbg !1553
  %idx.ext = sext i32 %35 to i64, !dbg !1553
  %add.ptr = getelementptr inbounds i8, i8* %36, i64 %idx.ext, !dbg !1553
  store i8* %add.ptr, i8** %p.addr, align 8, !dbg !1553
  %37 = load i32, i32* %l, align 4, !dbg !1554
  %conv56 = sext i32 %37 to i64, !dbg !1554
  %38 = load i64, i64* %len.addr, align 8, !dbg !1555
  %sub = sub nsw i64 %38, %conv56, !dbg !1555
  store i64 %sub, i64* %len.addr, align 8, !dbg !1555
  %39 = load i32, i32* %keycnt, align 4, !dbg !1556
  %inc = add nsw i32 %39, 1, !dbg !1556
  store i32 %inc, i32* %keycnt, align 4, !dbg !1556
  %40 = load i8*, i8** %p.addr, align 8, !dbg !1557
  %41 = load i8, i8* %40, align 1, !dbg !1559
  %conv57 = sext i8 %41 to i32, !dbg !1559
  %cmp58 = icmp eq i32 %conv57, 61, !dbg !1560
  br i1 %cmp58, label %if.then60, label %if.end85, !dbg !1561

if.then60:                                        ; preds = %if.end55
  call void @llvm.dbg.declare(metadata i32* %value, metadata !1562, metadata !460), !dbg !1564
  store i32 0, i32* %value, align 4, !dbg !1564
  %42 = load i8*, i8** %p.addr, align 8, !dbg !1565
  %incdec.ptr61 = getelementptr inbounds i8, i8* %42, i32 1, !dbg !1565
  store i8* %incdec.ptr61, i8** %p.addr, align 8, !dbg !1565
  %43 = load i64, i64* %len.addr, align 8, !dbg !1566
  %dec62 = add nsw i64 %43, -1, !dbg !1566
  store i64 %dec62, i64* %len.addr, align 8, !dbg !1566
  br label %while.cond63, !dbg !1567

while.cond63:                                     ; preds = %while.body75, %if.then60
  %44 = load i64, i64* %len.addr, align 8, !dbg !1568
  %cmp64 = icmp sgt i64 %44, 0, !dbg !1570
  br i1 %cmp64, label %land.lhs.true66, label %land.end74, !dbg !1571

land.lhs.true66:                                  ; preds = %while.cond63
  %45 = load i8*, i8** %p.addr, align 8, !dbg !1572
  %46 = load i8, i8* %45, align 1, !dbg !1574
  %conv67 = sext i8 %46 to i32, !dbg !1574
  %cmp68 = icmp ne i32 %conv67, 32, !dbg !1575
  br i1 %cmp68, label %land.rhs70, label %land.end74, !dbg !1576

land.rhs70:                                       ; preds = %land.lhs.true66
  %47 = load i8*, i8** %p.addr, align 8, !dbg !1577
  %48 = load i8, i8* %47, align 1, !dbg !1579
  %conv71 = sext i8 %48 to i32, !dbg !1579
  %cmp72 = icmp ne i32 %conv71, 9, !dbg !1580
  br label %land.end74

land.end74:                                       ; preds = %land.rhs70, %land.lhs.true66, %while.cond63
  %49 = phi i1 [ false, %land.lhs.true66 ], [ false, %while.cond63 ], [ %cmp72, %land.rhs70 ]
  br i1 %49, label %while.body75, label %while.end78, !dbg !1581

while.body75:                                     ; preds = %land.end74
  %50 = load i8*, i8** %p.addr, align 8, !dbg !1583
  %incdec.ptr76 = getelementptr inbounds i8, i8* %50, i32 1, !dbg !1583
  store i8* %incdec.ptr76, i8** %p.addr, align 8, !dbg !1583
  %51 = load i64, i64* %len.addr, align 8, !dbg !1585
  %dec77 = add nsw i64 %51, -1, !dbg !1585
  store i64 %dec77, i64* %len.addr, align 8, !dbg !1585
  store i32 1, i32* %value, align 4, !dbg !1586
  br label %while.cond63, !dbg !1587

while.end78:                                      ; preds = %land.end74
  %52 = load i32, i32* %unset.addr, align 4, !dbg !1589
  %tobool79 = icmp ne i32 %52, 0, !dbg !1589
  br i1 %tobool79, label %if.end84, label %land.lhs.true80, !dbg !1591

land.lhs.true80:                                  ; preds = %while.end78
  %53 = load i32, i32* %value, align 4, !dbg !1592
  %cmp81 = icmp eq i32 %53, 0, !dbg !1594
  br i1 %cmp81, label %if.then83, label %if.end84, !dbg !1595

if.then83:                                        ; preds = %land.lhs.true80
  store i32 -1, i32* %retval, align 4, !dbg !1596
  br label %return, !dbg !1596

if.end84:                                         ; preds = %land.lhs.true80, %while.end78
  br label %if.end85, !dbg !1597

if.end85:                                         ; preds = %if.end84, %if.end55
  br label %while.cond, !dbg !1598

while.end86:                                      ; preds = %if.then31, %if.then, %land.end
  %54 = load i32, i32* %keycnt, align 4, !dbg !1600
  store i32 %54, i32* %retval, align 4, !dbg !1601
  br label %return, !dbg !1601

return:                                           ; preds = %while.end86, %if.then83, %if.then54, %if.then48, %if.then42, %if.then36
  %55 = load i32, i32* %retval, align 4, !dbg !1602
  ret i32 %55, !dbg !1602
}

; Function Attrs: nounwind uwtable
define internal i32 @bid_entry(i8* %p, i64 %len, i64 %nl, i32* %last_is_path) #0 !dbg !371 {
entry:
  %retval = alloca i32, align 4
  %p.addr = alloca i8*, align 8
  %len.addr = alloca i64, align 8
  %nl.addr = alloca i64, align 8
  %last_is_path.addr = alloca i32*, align 8
  %f = alloca i32, align 4
  %ll = alloca i64, align 8
  %pp = alloca i8*, align 8
  %pp_end = alloca i8*, align 8
  %pb = alloca i8*, align 8
  %name_len = alloca i32, align 4
  %slash = alloca i32, align 4
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !1603, metadata !460), !dbg !1604
  store i64 %len, i64* %len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %len.addr, metadata !1605, metadata !460), !dbg !1606
  store i64 %nl, i64* %nl.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %nl.addr, metadata !1607, metadata !460), !dbg !1608
  store i32* %last_is_path, i32** %last_is_path.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %last_is_path.addr, metadata !1609, metadata !460), !dbg !1610
  call void @llvm.dbg.declare(metadata i32* %f, metadata !1611, metadata !460), !dbg !1612
  store i32 0, i32* %f, align 4, !dbg !1612
  call void @llvm.dbg.declare(metadata i64* %ll, metadata !1613, metadata !460), !dbg !1614
  call void @llvm.dbg.declare(metadata i8** %pp, metadata !1615, metadata !460), !dbg !1616
  %0 = load i8*, i8** %p.addr, align 8, !dbg !1617
  store i8* %0, i8** %pp, align 8, !dbg !1616
  call void @llvm.dbg.declare(metadata i8** %pp_end, metadata !1618, metadata !460), !dbg !1620
  %1 = load i8*, i8** %pp, align 8, !dbg !1621
  %2 = load i64, i64* %len.addr, align 8, !dbg !1622
  %add.ptr = getelementptr inbounds i8, i8* %1, i64 %2, !dbg !1623
  store i8* %add.ptr, i8** %pp_end, align 8, !dbg !1620
  %3 = load i32*, i32** %last_is_path.addr, align 8, !dbg !1624
  store i32 0, i32* %3, align 4, !dbg !1625
  br label %for.cond, !dbg !1626

for.cond:                                         ; preds = %for.inc, %entry
  %4 = load i8*, i8** %pp, align 8, !dbg !1627
  %5 = load i8*, i8** %pp_end, align 8, !dbg !1631
  %cmp = icmp ult i8* %4, %5, !dbg !1632
  br i1 %cmp, label %for.body, label %for.end, !dbg !1633

for.body:                                         ; preds = %for.cond
  %6 = load i8*, i8** %pp, align 8, !dbg !1634
  %7 = load i8, i8* %6, align 1, !dbg !1637
  %idxprom = zext i8 %7 to i64, !dbg !1638
  %arrayidx = getelementptr inbounds [256 x i8], [256 x i8]* @bid_entry.safe_char, i64 0, i64 %idxprom, !dbg !1638
  %8 = load i8, i8* %arrayidx, align 1, !dbg !1638
  %tobool = icmp ne i8 %8, 0, !dbg !1638
  br i1 %tobool, label %if.end15, label %if.then, !dbg !1639

if.then:                                          ; preds = %for.body
  %9 = load i8*, i8** %pp, align 8, !dbg !1640
  %10 = load i8, i8* %9, align 1, !dbg !1643
  %conv = sext i8 %10 to i32, !dbg !1643
  %cmp1 = icmp ne i32 %conv, 32, !dbg !1644
  br i1 %cmp1, label %land.lhs.true, label %if.end, !dbg !1645

land.lhs.true:                                    ; preds = %if.then
  %11 = load i8*, i8** %pp, align 8, !dbg !1646
  %12 = load i8, i8* %11, align 1, !dbg !1648
  %conv3 = sext i8 %12 to i32, !dbg !1648
  %cmp4 = icmp ne i32 %conv3, 9, !dbg !1649
  br i1 %cmp4, label %land.lhs.true6, label %if.end, !dbg !1650

land.lhs.true6:                                   ; preds = %land.lhs.true
  %13 = load i8*, i8** %pp, align 8, !dbg !1651
  %14 = load i8, i8* %13, align 1, !dbg !1653
  %conv7 = sext i8 %14 to i32, !dbg !1653
  %cmp8 = icmp ne i32 %conv7, 13, !dbg !1654
  br i1 %cmp8, label %land.lhs.true10, label %if.end, !dbg !1655

land.lhs.true10:                                  ; preds = %land.lhs.true6
  %15 = load i8*, i8** %pp, align 8, !dbg !1656
  %16 = load i8, i8* %15, align 1, !dbg !1657
  %conv11 = sext i8 %16 to i32, !dbg !1657
  %cmp12 = icmp ne i32 %conv11, 10, !dbg !1658
  br i1 %cmp12, label %if.then14, label %if.end, !dbg !1659

if.then14:                                        ; preds = %land.lhs.true10
  store i32 0, i32* %f, align 4, !dbg !1661
  br label %if.end, !dbg !1662

if.end:                                           ; preds = %if.then14, %land.lhs.true10, %land.lhs.true6, %land.lhs.true, %if.then
  br label %for.end, !dbg !1663

if.end15:                                         ; preds = %for.body
  store i32 1, i32* %f, align 4, !dbg !1664
  br label %for.inc, !dbg !1665

for.inc:                                          ; preds = %if.end15
  %17 = load i8*, i8** %pp, align 8, !dbg !1666
  %incdec.ptr = getelementptr inbounds i8, i8* %17, i32 1, !dbg !1666
  store i8* %incdec.ptr, i8** %pp, align 8, !dbg !1666
  br label %for.cond, !dbg !1668

for.end:                                          ; preds = %if.end, %for.cond
  %18 = load i8*, i8** %pp_end, align 8, !dbg !1669
  %19 = load i8*, i8** %pp, align 8, !dbg !1670
  %sub.ptr.lhs.cast = ptrtoint i8* %18 to i64, !dbg !1671
  %sub.ptr.rhs.cast = ptrtoint i8* %19 to i64, !dbg !1671
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !1671
  store i64 %sub.ptr.sub, i64* %ll, align 8, !dbg !1672
  %20 = load i32, i32* %f, align 4, !dbg !1673
  %cmp16 = icmp eq i32 %20, 0, !dbg !1675
  br i1 %cmp16, label %if.then18, label %if.end85, !dbg !1676

if.then18:                                        ; preds = %for.end
  call void @llvm.dbg.declare(metadata i8** %pb, metadata !1677, metadata !460), !dbg !1679
  %21 = load i8*, i8** %p.addr, align 8, !dbg !1680
  %22 = load i64, i64* %len.addr, align 8, !dbg !1681
  %add.ptr19 = getelementptr inbounds i8, i8* %21, i64 %22, !dbg !1682
  %23 = load i64, i64* %nl.addr, align 8, !dbg !1683
  %idx.neg = sub i64 0, %23, !dbg !1684
  %add.ptr20 = getelementptr inbounds i8, i8* %add.ptr19, i64 %idx.neg, !dbg !1684
  store i8* %add.ptr20, i8** %pb, align 8, !dbg !1679
  call void @llvm.dbg.declare(metadata i32* %name_len, metadata !1685, metadata !460), !dbg !1686
  store i32 0, i32* %name_len, align 4, !dbg !1686
  call void @llvm.dbg.declare(metadata i32* %slash, metadata !1687, metadata !460), !dbg !1688
  %24 = load i8*, i8** %pb, align 8, !dbg !1689
  %add.ptr21 = getelementptr inbounds i8, i8* %24, i64 -2, !dbg !1691
  %25 = load i8*, i8** %p.addr, align 8, !dbg !1692
  %cmp22 = icmp uge i8* %add.ptr21, %25, !dbg !1693
  br i1 %cmp22, label %land.lhs.true24, label %if.end39, !dbg !1694

land.lhs.true24:                                  ; preds = %if.then18
  %26 = load i8*, i8** %pb, align 8, !dbg !1695
  %arrayidx25 = getelementptr inbounds i8, i8* %26, i64 -1, !dbg !1695
  %27 = load i8, i8* %arrayidx25, align 1, !dbg !1695
  %conv26 = sext i8 %27 to i32, !dbg !1695
  %cmp27 = icmp eq i32 %conv26, 92, !dbg !1696
  br i1 %cmp27, label %land.lhs.true29, label %if.end39, !dbg !1697

land.lhs.true29:                                  ; preds = %land.lhs.true24
  %28 = load i8*, i8** %pb, align 8, !dbg !1698
  %arrayidx30 = getelementptr inbounds i8, i8* %28, i64 -2, !dbg !1698
  %29 = load i8, i8* %arrayidx30, align 1, !dbg !1698
  %conv31 = sext i8 %29 to i32, !dbg !1698
  %cmp32 = icmp eq i32 %conv31, 32, !dbg !1700
  br i1 %cmp32, label %if.then38, label %lor.lhs.false, !dbg !1701

lor.lhs.false:                                    ; preds = %land.lhs.true29
  %30 = load i8*, i8** %pb, align 8, !dbg !1702
  %arrayidx34 = getelementptr inbounds i8, i8* %30, i64 -2, !dbg !1702
  %31 = load i8, i8* %arrayidx34, align 1, !dbg !1702
  %conv35 = sext i8 %31 to i32, !dbg !1702
  %cmp36 = icmp eq i32 %conv35, 9, !dbg !1704
  br i1 %cmp36, label %if.then38, label %if.end39, !dbg !1705

if.then38:                                        ; preds = %lor.lhs.false, %land.lhs.true29
  store i32 -1, i32* %retval, align 4, !dbg !1707
  br label %return, !dbg !1707

if.end39:                                         ; preds = %lor.lhs.false, %land.lhs.true24, %if.then18
  %32 = load i8*, i8** %pb, align 8, !dbg !1708
  %add.ptr40 = getelementptr inbounds i8, i8* %32, i64 -1, !dbg !1710
  %33 = load i8*, i8** %p.addr, align 8, !dbg !1711
  %cmp41 = icmp uge i8* %add.ptr40, %33, !dbg !1712
  br i1 %cmp41, label %land.lhs.true43, label %if.end49, !dbg !1713

land.lhs.true43:                                  ; preds = %if.end39
  %34 = load i8*, i8** %pb, align 8, !dbg !1714
  %arrayidx44 = getelementptr inbounds i8, i8* %34, i64 -1, !dbg !1714
  %35 = load i8, i8* %arrayidx44, align 1, !dbg !1714
  %conv45 = sext i8 %35 to i32, !dbg !1714
  %cmp46 = icmp eq i32 %conv45, 92, !dbg !1716
  br i1 %cmp46, label %if.then48, label %if.end49, !dbg !1717

if.then48:                                        ; preds = %land.lhs.true43
  store i32 -1, i32* %retval, align 4, !dbg !1718
  br label %return, !dbg !1718

if.end49:                                         ; preds = %land.lhs.true43, %if.end39
  store i32 0, i32* %slash, align 4, !dbg !1719
  br label %while.cond, !dbg !1720

while.cond:                                       ; preds = %if.end69, %if.end49
  %36 = load i8*, i8** %p.addr, align 8, !dbg !1721
  %37 = load i8*, i8** %pb, align 8, !dbg !1722
  %incdec.ptr50 = getelementptr inbounds i8, i8* %37, i32 -1, !dbg !1722
  store i8* %incdec.ptr50, i8** %pb, align 8, !dbg !1722
  %cmp51 = icmp ule i8* %36, %incdec.ptr50, !dbg !1723
  br i1 %cmp51, label %land.lhs.true53, label %land.end, !dbg !1724

land.lhs.true53:                                  ; preds = %while.cond
  %38 = load i8*, i8** %pb, align 8, !dbg !1725
  %39 = load i8, i8* %38, align 1, !dbg !1727
  %conv54 = sext i8 %39 to i32, !dbg !1727
  %cmp55 = icmp ne i32 %conv54, 32, !dbg !1728
  br i1 %cmp55, label %land.rhs, label %land.end, !dbg !1729

land.rhs:                                         ; preds = %land.lhs.true53
  %40 = load i8*, i8** %pb, align 8, !dbg !1730
  %41 = load i8, i8* %40, align 1, !dbg !1732
  %conv57 = sext i8 %41 to i32, !dbg !1732
  %cmp58 = icmp ne i32 %conv57, 9, !dbg !1733
  br label %land.end

land.end:                                         ; preds = %land.rhs, %land.lhs.true53, %while.cond
  %42 = phi i1 [ false, %land.lhs.true53 ], [ false, %while.cond ], [ %cmp58, %land.rhs ]
  br i1 %42, label %while.body, label %while.end, !dbg !1734

while.body:                                       ; preds = %land.end
  %43 = load i8*, i8** %pb, align 8, !dbg !1736
  %44 = load i8, i8* %43, align 1, !dbg !1739
  %idxprom60 = zext i8 %44 to i64, !dbg !1740
  %arrayidx61 = getelementptr inbounds [256 x i8], [256 x i8]* @bid_entry.safe_char, i64 0, i64 %idxprom60, !dbg !1740
  %45 = load i8, i8* %arrayidx61, align 1, !dbg !1740
  %tobool62 = icmp ne i8 %45, 0, !dbg !1740
  br i1 %tobool62, label %if.end64, label %if.then63, !dbg !1741

if.then63:                                        ; preds = %while.body
  store i32 -1, i32* %retval, align 4, !dbg !1742
  br label %return, !dbg !1742

if.end64:                                         ; preds = %while.body
  %46 = load i32, i32* %name_len, align 4, !dbg !1743
  %inc = add nsw i32 %46, 1, !dbg !1743
  store i32 %inc, i32* %name_len, align 4, !dbg !1743
  %47 = load i8*, i8** %pb, align 8, !dbg !1744
  %48 = load i8, i8* %47, align 1, !dbg !1746
  %conv65 = sext i8 %48 to i32, !dbg !1746
  %cmp66 = icmp eq i32 %conv65, 47, !dbg !1747
  br i1 %cmp66, label %if.then68, label %if.end69, !dbg !1748

if.then68:                                        ; preds = %if.end64
  store i32 1, i32* %slash, align 4, !dbg !1749
  br label %if.end69, !dbg !1750

if.end69:                                         ; preds = %if.then68, %if.end64
  br label %while.cond, !dbg !1751

while.end:                                        ; preds = %land.end
  %49 = load i32, i32* %name_len, align 4, !dbg !1753
  %cmp70 = icmp eq i32 %49, 0, !dbg !1755
  br i1 %cmp70, label %if.then75, label %lor.lhs.false72, !dbg !1756

lor.lhs.false72:                                  ; preds = %while.end
  %50 = load i32, i32* %slash, align 4, !dbg !1757
  %cmp73 = icmp eq i32 %50, 0, !dbg !1759
  br i1 %cmp73, label %if.then75, label %if.end76, !dbg !1760

if.then75:                                        ; preds = %lor.lhs.false72, %while.end
  store i32 -1, i32* %retval, align 4, !dbg !1761
  br label %return, !dbg !1761

if.end76:                                         ; preds = %lor.lhs.false72
  %51 = load i8*, i8** %pb, align 8, !dbg !1762
  %arrayidx77 = getelementptr inbounds i8, i8* %51, i64 1, !dbg !1762
  %52 = load i8, i8* %arrayidx77, align 1, !dbg !1762
  %conv78 = sext i8 %52 to i32, !dbg !1762
  %cmp79 = icmp eq i32 %conv78, 47, !dbg !1764
  br i1 %cmp79, label %if.then81, label %if.end82, !dbg !1765

if.then81:                                        ; preds = %if.end76
  store i32 -1, i32* %retval, align 4, !dbg !1766
  br label %return, !dbg !1766

if.end82:                                         ; preds = %if.end76
  %53 = load i64, i64* %len.addr, align 8, !dbg !1767
  %54 = load i64, i64* %nl.addr, align 8, !dbg !1768
  %sub = sub nsw i64 %53, %54, !dbg !1769
  %55 = load i32, i32* %name_len, align 4, !dbg !1770
  %conv83 = sext i32 %55 to i64, !dbg !1770
  %sub84 = sub nsw i64 %sub, %conv83, !dbg !1771
  store i64 %sub84, i64* %ll, align 8, !dbg !1772
  %56 = load i8*, i8** %p.addr, align 8, !dbg !1773
  store i8* %56, i8** %pp, align 8, !dbg !1774
  %57 = load i32*, i32** %last_is_path.addr, align 8, !dbg !1775
  store i32 1, i32* %57, align 4, !dbg !1776
  br label %if.end85, !dbg !1777

if.end85:                                         ; preds = %if.end82, %for.end
  %58 = load i8*, i8** %pp, align 8, !dbg !1778
  %59 = load i64, i64* %ll, align 8, !dbg !1779
  %60 = load i32*, i32** %last_is_path.addr, align 8, !dbg !1780
  %61 = load i32, i32* %60, align 4, !dbg !1781
  %call = call i32 @bid_keyword_list(i8* %58, i64 %59, i32 0, i32 %61), !dbg !1782
  store i32 %call, i32* %retval, align 4, !dbg !1783
  br label %return, !dbg !1783

return:                                           ; preds = %if.end85, %if.then81, %if.then75, %if.then63, %if.then48, %if.then38
  %62 = load i32, i32* %retval, align 4, !dbg !1784
  ret i32 %62, !dbg !1784
}

; Function Attrs: nounwind readonly
declare i32 @strncmp(i8*, i8*, i64) #4

; Function Attrs: nounwind uwtable
define internal i64 @get_line_size(i8* %b, i64 %avail, i64* %nlsize) #0 !dbg !359 {
entry:
  %retval = alloca i64, align 8
  %b.addr = alloca i8*, align 8
  %avail.addr = alloca i64, align 8
  %nlsize.addr = alloca i64*, align 8
  %len = alloca i64, align 8
  store i8* %b, i8** %b.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %b.addr, metadata !1785, metadata !460), !dbg !1786
  store i64 %avail, i64* %avail.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %avail.addr, metadata !1787, metadata !460), !dbg !1788
  store i64* %nlsize, i64** %nlsize.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %nlsize.addr, metadata !1789, metadata !460), !dbg !1790
  call void @llvm.dbg.declare(metadata i64* %len, metadata !1791, metadata !460), !dbg !1792
  store i64 0, i64* %len, align 8, !dbg !1793
  br label %while.cond, !dbg !1794

while.cond:                                       ; preds = %sw.epilog, %entry
  %0 = load i64, i64* %len, align 8, !dbg !1795
  %1 = load i64, i64* %avail.addr, align 8, !dbg !1797
  %cmp = icmp slt i64 %0, %1, !dbg !1798
  br i1 %cmp, label %while.body, label %while.end, !dbg !1799

while.body:                                       ; preds = %while.cond
  %2 = load i8*, i8** %b.addr, align 8, !dbg !1800
  %3 = load i8, i8* %2, align 1, !dbg !1802
  %conv = sext i8 %3 to i32, !dbg !1802
  switch i32 %conv, label %sw.default [
    i32 0, label %sw.bb
    i32 13, label %sw.bb3
    i32 10, label %sw.bb15
  ], !dbg !1803

sw.bb:                                            ; preds = %while.body
  %4 = load i64*, i64** %nlsize.addr, align 8, !dbg !1804
  %cmp1 = icmp ne i64* %4, null, !dbg !1807
  br i1 %cmp1, label %if.then, label %if.end, !dbg !1808

if.then:                                          ; preds = %sw.bb
  %5 = load i64*, i64** %nlsize.addr, align 8, !dbg !1809
  store i64 0, i64* %5, align 8, !dbg !1810
  br label %if.end, !dbg !1811

if.end:                                           ; preds = %if.then, %sw.bb
  store i64 -1, i64* %retval, align 8, !dbg !1812
  br label %return, !dbg !1812

sw.bb3:                                           ; preds = %while.body
  %6 = load i64, i64* %avail.addr, align 8, !dbg !1813
  %7 = load i64, i64* %len, align 8, !dbg !1815
  %sub = sub nsw i64 %6, %7, !dbg !1816
  %cmp4 = icmp sgt i64 %sub, 1, !dbg !1817
  br i1 %cmp4, label %land.lhs.true, label %if.end14, !dbg !1818

land.lhs.true:                                    ; preds = %sw.bb3
  %8 = load i8*, i8** %b.addr, align 8, !dbg !1819
  %arrayidx = getelementptr inbounds i8, i8* %8, i64 1, !dbg !1819
  %9 = load i8, i8* %arrayidx, align 1, !dbg !1819
  %conv6 = sext i8 %9 to i32, !dbg !1819
  %cmp7 = icmp eq i32 %conv6, 10, !dbg !1821
  br i1 %cmp7, label %if.then9, label %if.end14, !dbg !1822

if.then9:                                         ; preds = %land.lhs.true
  %10 = load i64*, i64** %nlsize.addr, align 8, !dbg !1823
  %cmp10 = icmp ne i64* %10, null, !dbg !1826
  br i1 %cmp10, label %if.then12, label %if.end13, !dbg !1827

if.then12:                                        ; preds = %if.then9
  %11 = load i64*, i64** %nlsize.addr, align 8, !dbg !1828
  store i64 2, i64* %11, align 8, !dbg !1829
  br label %if.end13, !dbg !1830

if.end13:                                         ; preds = %if.then12, %if.then9
  %12 = load i64, i64* %len, align 8, !dbg !1831
  %add = add nsw i64 %12, 2, !dbg !1832
  store i64 %add, i64* %retval, align 8, !dbg !1833
  br label %return, !dbg !1833

if.end14:                                         ; preds = %land.lhs.true, %sw.bb3
  br label %sw.bb15, !dbg !1834

sw.bb15:                                          ; preds = %while.body, %if.end14
  %13 = load i64*, i64** %nlsize.addr, align 8, !dbg !1836
  %cmp16 = icmp ne i64* %13, null, !dbg !1838
  br i1 %cmp16, label %if.then18, label %if.end19, !dbg !1839

if.then18:                                        ; preds = %sw.bb15
  %14 = load i64*, i64** %nlsize.addr, align 8, !dbg !1840
  store i64 1, i64* %14, align 8, !dbg !1841
  br label %if.end19, !dbg !1842

if.end19:                                         ; preds = %if.then18, %sw.bb15
  %15 = load i64, i64* %len, align 8, !dbg !1843
  %add20 = add nsw i64 %15, 1, !dbg !1844
  store i64 %add20, i64* %retval, align 8, !dbg !1845
  br label %return, !dbg !1845

sw.default:                                       ; preds = %while.body
  %16 = load i8*, i8** %b.addr, align 8, !dbg !1846
  %incdec.ptr = getelementptr inbounds i8, i8* %16, i32 1, !dbg !1846
  store i8* %incdec.ptr, i8** %b.addr, align 8, !dbg !1846
  %17 = load i64, i64* %len, align 8, !dbg !1847
  %inc = add nsw i64 %17, 1, !dbg !1847
  store i64 %inc, i64* %len, align 8, !dbg !1847
  br label %sw.epilog, !dbg !1848

sw.epilog:                                        ; preds = %sw.default
  br label %while.cond, !dbg !1849

while.end:                                        ; preds = %while.cond
  %18 = load i64*, i64** %nlsize.addr, align 8, !dbg !1851
  %cmp21 = icmp ne i64* %18, null, !dbg !1853
  br i1 %cmp21, label %if.then23, label %if.end24, !dbg !1854

if.then23:                                        ; preds = %while.end
  %19 = load i64*, i64** %nlsize.addr, align 8, !dbg !1855
  store i64 0, i64* %19, align 8, !dbg !1856
  br label %if.end24, !dbg !1857

if.end24:                                         ; preds = %if.then23, %while.end
  %20 = load i64, i64* %avail.addr, align 8, !dbg !1858
  store i64 %20, i64* %retval, align 8, !dbg !1859
  br label %return, !dbg !1859

return:                                           ; preds = %if.end24, %if.end19, %if.end13, %if.end
  %21 = load i64, i64* %retval, align 8, !dbg !1860
  ret i64 %21, !dbg !1860
}

; Function Attrs: nounwind uwtable
define internal i32 @bid_keycmp(i8* %p, i8* %key, i64 %len) #0 !dbg !365 {
entry:
  %retval = alloca i32, align 4
  %p.addr = alloca i8*, align 8
  %key.addr = alloca i8*, align 8
  %len.addr = alloca i64, align 8
  %match_len = alloca i32, align 4
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !1861, metadata !460), !dbg !1862
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !1863, metadata !460), !dbg !1864
  store i64 %len, i64* %len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %len.addr, metadata !1865, metadata !460), !dbg !1866
  call void @llvm.dbg.declare(metadata i32* %match_len, metadata !1867, metadata !460), !dbg !1868
  store i32 0, i32* %match_len, align 4, !dbg !1868
  br label %while.cond, !dbg !1869

while.cond:                                       ; preds = %if.then, %entry
  %0 = load i64, i64* %len.addr, align 8, !dbg !1870
  %cmp = icmp sgt i64 %0, 0, !dbg !1872
  br i1 %cmp, label %land.lhs.true, label %land.end, !dbg !1873

land.lhs.true:                                    ; preds = %while.cond
  %1 = load i8*, i8** %p.addr, align 8, !dbg !1874
  %2 = load i8, i8* %1, align 1, !dbg !1876
  %conv = sext i8 %2 to i32, !dbg !1876
  %tobool = icmp ne i32 %conv, 0, !dbg !1876
  br i1 %tobool, label %land.rhs, label %land.end, !dbg !1877

land.rhs:                                         ; preds = %land.lhs.true
  %3 = load i8*, i8** %key.addr, align 8, !dbg !1878
  %4 = load i8, i8* %3, align 1, !dbg !1880
  %conv1 = sext i8 %4 to i32, !dbg !1880
  %tobool2 = icmp ne i32 %conv1, 0, !dbg !1881
  br label %land.end

land.end:                                         ; preds = %land.rhs, %land.lhs.true, %while.cond
  %5 = phi i1 [ false, %land.lhs.true ], [ false, %while.cond ], [ %tobool2, %land.rhs ]
  br i1 %5, label %while.body, label %while.end, !dbg !1882

while.body:                                       ; preds = %land.end
  %6 = load i8*, i8** %p.addr, align 8, !dbg !1884
  %7 = load i8, i8* %6, align 1, !dbg !1887
  %conv3 = sext i8 %7 to i32, !dbg !1887
  %8 = load i8*, i8** %key.addr, align 8, !dbg !1888
  %9 = load i8, i8* %8, align 1, !dbg !1889
  %conv4 = sext i8 %9 to i32, !dbg !1889
  %cmp5 = icmp eq i32 %conv3, %conv4, !dbg !1890
  br i1 %cmp5, label %if.then, label %if.end, !dbg !1891

if.then:                                          ; preds = %while.body
  %10 = load i64, i64* %len.addr, align 8, !dbg !1892
  %dec = add nsw i64 %10, -1, !dbg !1892
  store i64 %dec, i64* %len.addr, align 8, !dbg !1892
  %11 = load i8*, i8** %p.addr, align 8, !dbg !1894
  %incdec.ptr = getelementptr inbounds i8, i8* %11, i32 1, !dbg !1894
  store i8* %incdec.ptr, i8** %p.addr, align 8, !dbg !1894
  %12 = load i8*, i8** %key.addr, align 8, !dbg !1895
  %incdec.ptr7 = getelementptr inbounds i8, i8* %12, i32 1, !dbg !1895
  store i8* %incdec.ptr7, i8** %key.addr, align 8, !dbg !1895
  %13 = load i32, i32* %match_len, align 4, !dbg !1896
  %inc = add nsw i32 %13, 1, !dbg !1896
  store i32 %inc, i32* %match_len, align 4, !dbg !1896
  br label %while.cond, !dbg !1897

if.end:                                           ; preds = %while.body
  store i32 0, i32* %retval, align 4, !dbg !1898
  br label %return, !dbg !1898

while.end:                                        ; preds = %land.end
  %14 = load i8*, i8** %key.addr, align 8, !dbg !1899
  %15 = load i8, i8* %14, align 1, !dbg !1901
  %conv8 = sext i8 %15 to i32, !dbg !1901
  %cmp9 = icmp ne i32 %conv8, 0, !dbg !1902
  br i1 %cmp9, label %if.then11, label %if.end12, !dbg !1903

if.then11:                                        ; preds = %while.end
  store i32 0, i32* %retval, align 4, !dbg !1904
  br label %return, !dbg !1904

if.end12:                                         ; preds = %while.end
  %16 = load i8*, i8** %p.addr, align 8, !dbg !1905
  %arrayidx = getelementptr inbounds i8, i8* %16, i64 0, !dbg !1905
  %17 = load i8, i8* %arrayidx, align 1, !dbg !1905
  %conv13 = sext i8 %17 to i32, !dbg !1905
  %cmp14 = icmp eq i32 %conv13, 61, !dbg !1907
  br i1 %cmp14, label %if.then50, label %lor.lhs.false, !dbg !1908

lor.lhs.false:                                    ; preds = %if.end12
  %18 = load i8*, i8** %p.addr, align 8, !dbg !1909
  %arrayidx16 = getelementptr inbounds i8, i8* %18, i64 0, !dbg !1909
  %19 = load i8, i8* %arrayidx16, align 1, !dbg !1909
  %conv17 = sext i8 %19 to i32, !dbg !1909
  %cmp18 = icmp eq i32 %conv17, 32, !dbg !1911
  br i1 %cmp18, label %if.then50, label %lor.lhs.false20, !dbg !1912

lor.lhs.false20:                                  ; preds = %lor.lhs.false
  %20 = load i8*, i8** %p.addr, align 8, !dbg !1913
  %arrayidx21 = getelementptr inbounds i8, i8* %20, i64 0, !dbg !1913
  %21 = load i8, i8* %arrayidx21, align 1, !dbg !1913
  %conv22 = sext i8 %21 to i32, !dbg !1913
  %cmp23 = icmp eq i32 %conv22, 9, !dbg !1915
  br i1 %cmp23, label %if.then50, label %lor.lhs.false25, !dbg !1916

lor.lhs.false25:                                  ; preds = %lor.lhs.false20
  %22 = load i8*, i8** %p.addr, align 8, !dbg !1917
  %arrayidx26 = getelementptr inbounds i8, i8* %22, i64 0, !dbg !1917
  %23 = load i8, i8* %arrayidx26, align 1, !dbg !1917
  %conv27 = sext i8 %23 to i32, !dbg !1917
  %cmp28 = icmp eq i32 %conv27, 10, !dbg !1918
  br i1 %cmp28, label %if.then50, label %lor.lhs.false30, !dbg !1919

lor.lhs.false30:                                  ; preds = %lor.lhs.false25
  %24 = load i8*, i8** %p.addr, align 8, !dbg !1920
  %arrayidx31 = getelementptr inbounds i8, i8* %24, i64 0, !dbg !1920
  %25 = load i8, i8* %arrayidx31, align 1, !dbg !1920
  %conv32 = sext i8 %25 to i32, !dbg !1920
  %cmp33 = icmp eq i32 %conv32, 13, !dbg !1921
  br i1 %cmp33, label %if.then50, label %lor.lhs.false35, !dbg !1922

lor.lhs.false35:                                  ; preds = %lor.lhs.false30
  %26 = load i8*, i8** %p.addr, align 8, !dbg !1923
  %arrayidx36 = getelementptr inbounds i8, i8* %26, i64 0, !dbg !1923
  %27 = load i8, i8* %arrayidx36, align 1, !dbg !1923
  %conv37 = sext i8 %27 to i32, !dbg !1923
  %cmp38 = icmp eq i32 %conv37, 92, !dbg !1924
  br i1 %cmp38, label %land.lhs.true40, label %if.end51, !dbg !1925

land.lhs.true40:                                  ; preds = %lor.lhs.false35
  %28 = load i8*, i8** %p.addr, align 8, !dbg !1926
  %arrayidx41 = getelementptr inbounds i8, i8* %28, i64 1, !dbg !1926
  %29 = load i8, i8* %arrayidx41, align 1, !dbg !1926
  %conv42 = sext i8 %29 to i32, !dbg !1926
  %cmp43 = icmp eq i32 %conv42, 10, !dbg !1927
  br i1 %cmp43, label %if.then50, label %lor.lhs.false45, !dbg !1928

lor.lhs.false45:                                  ; preds = %land.lhs.true40
  %30 = load i8*, i8** %p.addr, align 8, !dbg !1929
  %arrayidx46 = getelementptr inbounds i8, i8* %30, i64 1, !dbg !1929
  %31 = load i8, i8* %arrayidx46, align 1, !dbg !1929
  %conv47 = sext i8 %31 to i32, !dbg !1929
  %cmp48 = icmp eq i32 %conv47, 13, !dbg !1930
  br i1 %cmp48, label %if.then50, label %if.end51, !dbg !1931

if.then50:                                        ; preds = %lor.lhs.false45, %land.lhs.true40, %lor.lhs.false30, %lor.lhs.false25, %lor.lhs.false20, %lor.lhs.false, %if.end12
  %32 = load i32, i32* %match_len, align 4, !dbg !1932
  store i32 %32, i32* %retval, align 4, !dbg !1933
  br label %return, !dbg !1933

if.end51:                                         ; preds = %lor.lhs.false45, %lor.lhs.false35
  store i32 0, i32* %retval, align 4, !dbg !1934
  br label %return, !dbg !1934

return:                                           ; preds = %if.end51, %if.then50, %if.then11, %if.end
  %33 = load i32, i32* %retval, align 4, !dbg !1935
  ret i32 %33, !dbg !1935
}

; Function Attrs: nounwind uwtable
define internal i32 @bid_keyword(i8* %p, i64 %len) #0 !dbg !368 {
entry:
  %retval = alloca i32, align 4
  %p.addr = alloca i8*, align 8
  %len.addr = alloca i64, align 8
  %keys = alloca i8**, align 8
  %i = alloca i32, align 4
  %l = alloca i32, align 4
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !1936, metadata !460), !dbg !1937
  store i64 %len, i64* %len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %len.addr, metadata !1938, metadata !460), !dbg !1939
  call void @llvm.dbg.declare(metadata i8*** %keys, metadata !1940, metadata !460), !dbg !1941
  call void @llvm.dbg.declare(metadata i32* %i, metadata !1942, metadata !460), !dbg !1943
  %0 = load i8*, i8** %p.addr, align 8, !dbg !1944
  %1 = load i8, i8* %0, align 1, !dbg !1945
  %conv = sext i8 %1 to i32, !dbg !1945
  switch i32 %conv, label %sw.default [
    i32 99, label %sw.bb
    i32 100, label %sw.bb1
    i32 102, label %sw.bb1
    i32 103, label %sw.bb2
    i32 105, label %sw.bb3
    i32 108, label %sw.bb3
    i32 109, label %sw.bb4
    i32 110, label %sw.bb5
    i32 111, label %sw.bb5
    i32 114, label %sw.bb6
    i32 115, label %sw.bb7
    i32 116, label %sw.bb8
    i32 117, label %sw.bb9
  ], !dbg !1946

sw.bb:                                            ; preds = %entry
  store i8** getelementptr inbounds ([4 x i8*], [4 x i8*]* @bid_keyword.keys_c, i32 0, i32 0), i8*** %keys, align 8, !dbg !1947
  br label %sw.epilog, !dbg !1949

sw.bb1:                                           ; preds = %entry, %entry
  store i8** getelementptr inbounds ([3 x i8*], [3 x i8*]* @bid_keyword.keys_df, i32 0, i32 0), i8*** %keys, align 8, !dbg !1950
  br label %sw.epilog, !dbg !1951

sw.bb2:                                           ; preds = %entry
  store i8** getelementptr inbounds ([3 x i8*], [3 x i8*]* @bid_keyword.keys_g, i32 0, i32 0), i8*** %keys, align 8, !dbg !1952
  br label %sw.epilog, !dbg !1953

sw.bb3:                                           ; preds = %entry, %entry
  store i8** getelementptr inbounds ([4 x i8*], [4 x i8*]* @bid_keyword.keys_il, i32 0, i32 0), i8*** %keys, align 8, !dbg !1954
  br label %sw.epilog, !dbg !1955

sw.bb4:                                           ; preds = %entry
  store i8** getelementptr inbounds ([4 x i8*], [4 x i8*]* @bid_keyword.keys_m, i32 0, i32 0), i8*** %keys, align 8, !dbg !1956
  br label %sw.epilog, !dbg !1957

sw.bb5:                                           ; preds = %entry, %entry
  store i8** getelementptr inbounds ([4 x i8*], [4 x i8*]* @bid_keyword.keys_no, i32 0, i32 0), i8*** %keys, align 8, !dbg !1958
  br label %sw.epilog, !dbg !1959

sw.bb6:                                           ; preds = %entry
  store i8** getelementptr inbounds ([4 x i8*], [4 x i8*]* @bid_keyword.keys_r, i32 0, i32 0), i8*** %keys, align 8, !dbg !1960
  br label %sw.epilog, !dbg !1961

sw.bb7:                                           ; preds = %entry
  store i8** getelementptr inbounds ([10 x i8*], [10 x i8*]* @bid_keyword.keys_s, i32 0, i32 0), i8*** %keys, align 8, !dbg !1962
  br label %sw.epilog, !dbg !1963

sw.bb8:                                           ; preds = %entry
  store i8** getelementptr inbounds ([4 x i8*], [4 x i8*]* @bid_keyword.keys_t, i32 0, i32 0), i8*** %keys, align 8, !dbg !1964
  br label %sw.epilog, !dbg !1965

sw.bb9:                                           ; preds = %entry
  store i8** getelementptr inbounds ([3 x i8*], [3 x i8*]* @bid_keyword.keys_u, i32 0, i32 0), i8*** %keys, align 8, !dbg !1966
  br label %sw.epilog, !dbg !1967

sw.default:                                       ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !1968
  br label %return, !dbg !1968

sw.epilog:                                        ; preds = %sw.bb9, %sw.bb8, %sw.bb7, %sw.bb6, %sw.bb5, %sw.bb4, %sw.bb3, %sw.bb2, %sw.bb1, %sw.bb
  store i32 0, i32* %i, align 4, !dbg !1969
  br label %for.cond, !dbg !1971

for.cond:                                         ; preds = %for.inc, %sw.epilog
  %2 = load i32, i32* %i, align 4, !dbg !1972
  %idxprom = sext i32 %2 to i64, !dbg !1975
  %3 = load i8**, i8*** %keys, align 8, !dbg !1975
  %arrayidx = getelementptr inbounds i8*, i8** %3, i64 %idxprom, !dbg !1975
  %4 = load i8*, i8** %arrayidx, align 8, !dbg !1975
  %cmp = icmp ne i8* %4, null, !dbg !1976
  br i1 %cmp, label %for.body, label %for.end, !dbg !1977

for.body:                                         ; preds = %for.cond
  call void @llvm.dbg.declare(metadata i32* %l, metadata !1978, metadata !460), !dbg !1980
  %5 = load i8*, i8** %p.addr, align 8, !dbg !1981
  %6 = load i32, i32* %i, align 4, !dbg !1982
  %idxprom11 = sext i32 %6 to i64, !dbg !1983
  %7 = load i8**, i8*** %keys, align 8, !dbg !1983
  %arrayidx12 = getelementptr inbounds i8*, i8** %7, i64 %idxprom11, !dbg !1983
  %8 = load i8*, i8** %arrayidx12, align 8, !dbg !1983
  %9 = load i64, i64* %len.addr, align 8, !dbg !1984
  %call = call i32 @bid_keycmp(i8* %5, i8* %8, i64 %9), !dbg !1985
  store i32 %call, i32* %l, align 4, !dbg !1980
  %10 = load i32, i32* %l, align 4, !dbg !1986
  %cmp13 = icmp sgt i32 %10, 0, !dbg !1988
  br i1 %cmp13, label %if.then, label %if.end, !dbg !1989

if.then:                                          ; preds = %for.body
  %11 = load i32, i32* %l, align 4, !dbg !1990
  store i32 %11, i32* %retval, align 4, !dbg !1991
  br label %return, !dbg !1991

if.end:                                           ; preds = %for.body
  br label %for.inc, !dbg !1992

for.inc:                                          ; preds = %if.end
  %12 = load i32, i32* %i, align 4, !dbg !1993
  %inc = add nsw i32 %12, 1, !dbg !1993
  store i32 %inc, i32* %i, align 4, !dbg !1993
  br label %for.cond, !dbg !1995

for.end:                                          ; preds = %for.cond
  store i32 0, i32* %retval, align 4, !dbg !1996
  br label %return, !dbg !1996

return:                                           ; preds = %for.end, %if.then, %sw.default
  %13 = load i32, i32* %retval, align 4, !dbg !1997
  ret i32 %13, !dbg !1997
}

declare i32 @close(i32) #2

declare %struct.archive_entry_linkresolver* @archive_entry_linkresolver_new() #2

declare void @archive_entry_linkresolver_set_strategy(%struct.archive_entry_linkresolver*, i32) #2

; Function Attrs: nounwind uwtable
define internal i32 @read_mtree(%struct.archive_read* %a, %struct.mtree* %mtree) #0 !dbg !375 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %mtree.addr = alloca %struct.mtree*, align 8
  %len = alloca i64, align 8
  %counter = alloca i64, align 8
  %p = alloca i8*, align 8
  %global = alloca %struct.mtree_option*, align 8
  %last_entry = alloca %struct.mtree_entry*, align 8
  %r = alloca i32, align 4
  %is_form_d = alloca i32, align 4
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !1998, metadata !460), !dbg !1999
  store %struct.mtree* %mtree, %struct.mtree** %mtree.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree** %mtree.addr, metadata !2000, metadata !460), !dbg !2001
  call void @llvm.dbg.declare(metadata i64* %len, metadata !2002, metadata !460), !dbg !2003
  call void @llvm.dbg.declare(metadata i64* %counter, metadata !2004, metadata !460), !dbg !2006
  call void @llvm.dbg.declare(metadata i8** %p, metadata !2007, metadata !460), !dbg !2008
  call void @llvm.dbg.declare(metadata %struct.mtree_option** %global, metadata !2009, metadata !460), !dbg !2010
  call void @llvm.dbg.declare(metadata %struct.mtree_entry** %last_entry, metadata !2011, metadata !460), !dbg !2012
  call void @llvm.dbg.declare(metadata i32* %r, metadata !2013, metadata !460), !dbg !2014
  call void @llvm.dbg.declare(metadata i32* %is_form_d, metadata !2015, metadata !460), !dbg !2016
  %0 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !2017
  %archive_format = getelementptr inbounds %struct.mtree, %struct.mtree* %0, i32 0, i32 5, !dbg !2018
  store i32 524288, i32* %archive_format, align 4, !dbg !2019
  %1 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !2020
  %archive_format_name = getelementptr inbounds %struct.mtree, %struct.mtree* %1, i32 0, i32 6, !dbg !2021
  store i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.2, i32 0, i32 0), i8** %archive_format_name, align 8, !dbg !2022
  store %struct.mtree_option* null, %struct.mtree_option** %global, align 8, !dbg !2023
  store %struct.mtree_entry* null, %struct.mtree_entry** %last_entry, align 8, !dbg !2024
  %2 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2025
  %call = call i32 @detect_form(%struct.archive_read* %2, i32* %is_form_d), !dbg !2026
  store i64 1, i64* %counter, align 8, !dbg !2027
  br label %for.cond, !dbg !2029

for.cond:                                         ; preds = %for.inc, %entry
  %3 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2030
  %4 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !2033
  %call1 = call i64 @readline(%struct.archive_read* %3, %struct.mtree* %4, i8** %p, i64 65536), !dbg !2034
  store i64 %call1, i64* %len, align 8, !dbg !2035
  %5 = load i64, i64* %len, align 8, !dbg !2036
  %cmp = icmp eq i64 %5, 0, !dbg !2038
  br i1 %cmp, label %if.then, label %if.end, !dbg !2039

if.then:                                          ; preds = %for.cond
  %6 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !2040
  %entries = getelementptr inbounds %struct.mtree, %struct.mtree* %6, i32 0, i32 7, !dbg !2042
  %7 = load %struct.mtree_entry*, %struct.mtree_entry** %entries, align 8, !dbg !2042
  %8 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !2043
  %this_entry = getelementptr inbounds %struct.mtree, %struct.mtree* %8, i32 0, i32 8, !dbg !2044
  store %struct.mtree_entry* %7, %struct.mtree_entry** %this_entry, align 8, !dbg !2045
  %9 = load %struct.mtree_option*, %struct.mtree_option** %global, align 8, !dbg !2046
  call void @free_options(%struct.mtree_option* %9), !dbg !2047
  store i32 0, i32* %retval, align 4, !dbg !2048
  br label %return, !dbg !2048

if.end:                                           ; preds = %for.cond
  %10 = load i64, i64* %len, align 8, !dbg !2049
  %cmp2 = icmp slt i64 %10, 0, !dbg !2051
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !2052

if.then3:                                         ; preds = %if.end
  %11 = load %struct.mtree_option*, %struct.mtree_option** %global, align 8, !dbg !2053
  call void @free_options(%struct.mtree_option* %11), !dbg !2055
  %12 = load i64, i64* %len, align 8, !dbg !2056
  %conv = trunc i64 %12 to i32, !dbg !2057
  store i32 %conv, i32* %retval, align 4, !dbg !2058
  br label %return, !dbg !2058

if.end4:                                          ; preds = %if.end
  br label %while.cond, !dbg !2059

while.cond:                                       ; preds = %while.body, %if.end4
  %13 = load i8*, i8** %p, align 8, !dbg !2060
  %14 = load i8, i8* %13, align 1, !dbg !2062
  %conv5 = sext i8 %14 to i32, !dbg !2062
  %cmp6 = icmp eq i32 %conv5, 32, !dbg !2063
  br i1 %cmp6, label %lor.end, label %lor.rhs, !dbg !2064

lor.rhs:                                          ; preds = %while.cond
  %15 = load i8*, i8** %p, align 8, !dbg !2065
  %16 = load i8, i8* %15, align 1, !dbg !2067
  %conv8 = sext i8 %16 to i32, !dbg !2067
  %cmp9 = icmp eq i32 %conv8, 9, !dbg !2068
  br label %lor.end, !dbg !2069

lor.end:                                          ; preds = %lor.rhs, %while.cond
  %17 = phi i1 [ true, %while.cond ], [ %cmp9, %lor.rhs ]
  br i1 %17, label %while.body, label %while.end, !dbg !2070

while.body:                                       ; preds = %lor.end
  %18 = load i8*, i8** %p, align 8, !dbg !2072
  %incdec.ptr = getelementptr inbounds i8, i8* %18, i32 1, !dbg !2072
  store i8* %incdec.ptr, i8** %p, align 8, !dbg !2072
  %19 = load i64, i64* %len, align 8, !dbg !2074
  %dec = add nsw i64 %19, -1, !dbg !2074
  store i64 %dec, i64* %len, align 8, !dbg !2074
  br label %while.cond, !dbg !2075

while.end:                                        ; preds = %lor.end
  %20 = load i8*, i8** %p, align 8, !dbg !2077
  %21 = load i8, i8* %20, align 1, !dbg !2079
  %conv11 = sext i8 %21 to i32, !dbg !2079
  %cmp12 = icmp eq i32 %conv11, 35, !dbg !2080
  br i1 %cmp12, label %if.then14, label %if.end15, !dbg !2081

if.then14:                                        ; preds = %while.end
  br label %for.inc, !dbg !2082

if.end15:                                         ; preds = %while.end
  %22 = load i8*, i8** %p, align 8, !dbg !2083
  %23 = load i8, i8* %22, align 1, !dbg !2085
  %conv16 = sext i8 %23 to i32, !dbg !2085
  %cmp17 = icmp eq i32 %conv16, 13, !dbg !2086
  br i1 %cmp17, label %if.then26, label %lor.lhs.false, !dbg !2087

lor.lhs.false:                                    ; preds = %if.end15
  %24 = load i8*, i8** %p, align 8, !dbg !2088
  %25 = load i8, i8* %24, align 1, !dbg !2090
  %conv19 = sext i8 %25 to i32, !dbg !2090
  %cmp20 = icmp eq i32 %conv19, 10, !dbg !2091
  br i1 %cmp20, label %if.then26, label %lor.lhs.false22, !dbg !2092

lor.lhs.false22:                                  ; preds = %lor.lhs.false
  %26 = load i8*, i8** %p, align 8, !dbg !2093
  %27 = load i8, i8* %26, align 1, !dbg !2095
  %conv23 = sext i8 %27 to i32, !dbg !2095
  %cmp24 = icmp eq i32 %conv23, 0, !dbg !2096
  br i1 %cmp24, label %if.then26, label %if.end27, !dbg !2097

if.then26:                                        ; preds = %lor.lhs.false22, %lor.lhs.false, %if.end15
  br label %for.inc, !dbg !2098

if.end27:                                         ; preds = %lor.lhs.false22
  %28 = load i8*, i8** %p, align 8, !dbg !2099
  %29 = load i8, i8* %28, align 1, !dbg !2101
  %conv28 = sext i8 %29 to i32, !dbg !2101
  %cmp29 = icmp ne i32 %conv28, 47, !dbg !2102
  br i1 %cmp29, label %if.then31, label %if.else, !dbg !2103

if.then31:                                        ; preds = %if.end27
  %30 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2104
  %31 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !2106
  %32 = load i8*, i8** %p, align 8, !dbg !2107
  %33 = load i64, i64* %len, align 8, !dbg !2108
  %34 = load i32, i32* %is_form_d, align 4, !dbg !2109
  %call32 = call i32 @process_add_entry(%struct.archive_read* %30, %struct.mtree* %31, %struct.mtree_option** %global, i8* %32, i64 %33, %struct.mtree_entry** %last_entry, i32 %34), !dbg !2110
  store i32 %call32, i32* %r, align 4, !dbg !2111
  br label %if.end73, !dbg !2112

if.else:                                          ; preds = %if.end27
  %35 = load i64, i64* %len, align 8, !dbg !2113
  %cmp33 = icmp sgt i64 %35, 4, !dbg !2116
  br i1 %cmp33, label %land.lhs.true, label %if.else50, !dbg !2117

land.lhs.true:                                    ; preds = %if.else
  %36 = load i8*, i8** %p, align 8, !dbg !2118
  %call35 = call i32 @strncmp(i8* %36, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.5, i32 0, i32 0), i64 4) #8, !dbg !2120
  %cmp36 = icmp eq i32 %call35, 0, !dbg !2121
  br i1 %cmp36, label %if.then38, label %if.else50, !dbg !2122

if.then38:                                        ; preds = %land.lhs.true
  %37 = load i8*, i8** %p, align 8, !dbg !2123
  %arrayidx = getelementptr inbounds i8, i8* %37, i64 4, !dbg !2123
  %38 = load i8, i8* %arrayidx, align 1, !dbg !2123
  %conv39 = sext i8 %38 to i32, !dbg !2123
  %cmp40 = icmp ne i32 %conv39, 32, !dbg !2126
  br i1 %cmp40, label %land.lhs.true42, label %if.end48, !dbg !2127

land.lhs.true42:                                  ; preds = %if.then38
  %39 = load i8*, i8** %p, align 8, !dbg !2128
  %arrayidx43 = getelementptr inbounds i8, i8* %39, i64 4, !dbg !2128
  %40 = load i8, i8* %arrayidx43, align 1, !dbg !2128
  %conv44 = sext i8 %40 to i32, !dbg !2128
  %cmp45 = icmp ne i32 %conv44, 9, !dbg !2130
  br i1 %cmp45, label %if.then47, label %if.end48, !dbg !2131

if.then47:                                        ; preds = %land.lhs.true42
  br label %for.end, !dbg !2132

if.end48:                                         ; preds = %land.lhs.true42, %if.then38
  %41 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2133
  %42 = load i8*, i8** %p, align 8, !dbg !2134
  %call49 = call i32 @process_global_set(%struct.archive_read* %41, %struct.mtree_option** %global, i8* %42), !dbg !2135
  store i32 %call49, i32* %r, align 4, !dbg !2136
  br label %if.end72, !dbg !2137

if.else50:                                        ; preds = %land.lhs.true, %if.else
  %43 = load i64, i64* %len, align 8, !dbg !2138
  %cmp51 = icmp sgt i64 %43, 6, !dbg !2141
  br i1 %cmp51, label %land.lhs.true53, label %if.else70, !dbg !2142

land.lhs.true53:                                  ; preds = %if.else50
  %44 = load i8*, i8** %p, align 8, !dbg !2143
  %call54 = call i32 @strncmp(i8* %44, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.6, i32 0, i32 0), i64 6) #8, !dbg !2145
  %cmp55 = icmp eq i32 %call54, 0, !dbg !2146
  br i1 %cmp55, label %if.then57, label %if.else70, !dbg !2147

if.then57:                                        ; preds = %land.lhs.true53
  %45 = load i8*, i8** %p, align 8, !dbg !2148
  %arrayidx58 = getelementptr inbounds i8, i8* %45, i64 6, !dbg !2148
  %46 = load i8, i8* %arrayidx58, align 1, !dbg !2148
  %conv59 = sext i8 %46 to i32, !dbg !2148
  %cmp60 = icmp ne i32 %conv59, 32, !dbg !2151
  br i1 %cmp60, label %land.lhs.true62, label %if.end68, !dbg !2152

land.lhs.true62:                                  ; preds = %if.then57
  %47 = load i8*, i8** %p, align 8, !dbg !2153
  %arrayidx63 = getelementptr inbounds i8, i8* %47, i64 6, !dbg !2153
  %48 = load i8, i8* %arrayidx63, align 1, !dbg !2153
  %conv64 = sext i8 %48 to i32, !dbg !2153
  %cmp65 = icmp ne i32 %conv64, 9, !dbg !2155
  br i1 %cmp65, label %if.then67, label %if.end68, !dbg !2156

if.then67:                                        ; preds = %land.lhs.true62
  br label %for.end, !dbg !2157

if.end68:                                         ; preds = %land.lhs.true62, %if.then57
  %49 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2158
  %50 = load i8*, i8** %p, align 8, !dbg !2159
  %call69 = call i32 @process_global_unset(%struct.archive_read* %49, %struct.mtree_option** %global, i8* %50), !dbg !2160
  store i32 %call69, i32* %r, align 4, !dbg !2161
  br label %if.end71, !dbg !2162

if.else70:                                        ; preds = %land.lhs.true53, %if.else50
  br label %for.end, !dbg !2163

if.end71:                                         ; preds = %if.end68
  br label %if.end72

if.end72:                                         ; preds = %if.end71, %if.end48
  br label %if.end73

if.end73:                                         ; preds = %if.end72, %if.then31
  %51 = load i32, i32* %r, align 4, !dbg !2164
  %cmp74 = icmp ne i32 %51, 0, !dbg !2166
  br i1 %cmp74, label %if.then76, label %if.end77, !dbg !2167

if.then76:                                        ; preds = %if.end73
  %52 = load %struct.mtree_option*, %struct.mtree_option** %global, align 8, !dbg !2168
  call void @free_options(%struct.mtree_option* %52), !dbg !2170
  %53 = load i32, i32* %r, align 4, !dbg !2171
  store i32 %53, i32* %retval, align 4, !dbg !2172
  br label %return, !dbg !2172

if.end77:                                         ; preds = %if.end73
  br label %for.inc, !dbg !2173

for.inc:                                          ; preds = %if.end77, %if.then26, %if.then14
  %54 = load i64, i64* %counter, align 8, !dbg !2174
  %inc = add i64 %54, 1, !dbg !2174
  store i64 %inc, i64* %counter, align 8, !dbg !2174
  br label %for.cond, !dbg !2176

for.end:                                          ; preds = %if.else70, %if.then67, %if.then47
  %55 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2177
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %55, i32 0, i32 0, !dbg !2178
  %56 = load i64, i64* %counter, align 8, !dbg !2179
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 84, i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.42, i32 0, i32 0), i64 %56), !dbg !2180
  %57 = load %struct.mtree_option*, %struct.mtree_option** %global, align 8, !dbg !2181
  call void @free_options(%struct.mtree_option* %57), !dbg !2182
  store i32 -30, i32* %retval, align 4, !dbg !2183
  br label %return, !dbg !2183

return:                                           ; preds = %for.end, %if.then76, %if.then3, %if.then
  %58 = load i32, i32* %retval, align 4, !dbg !2184
  ret i32 %58, !dbg !2184
}

; Function Attrs: nounwind uwtable
define internal i32 @parse_file(%struct.archive_read* %a, %struct.archive_entry* %entry1, %struct.mtree* %mtree, %struct.mtree_entry* %mentry, i32* %use_next) #0 !dbg !403 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %mtree.addr = alloca %struct.mtree*, align 8
  %mentry.addr = alloca %struct.mtree_entry*, align 8
  %use_next.addr = alloca i32*, align 8
  %path = alloca i8*, align 8
  %st_storage = alloca %struct.stat, align 8
  %st = alloca %struct.stat*, align 8
  %mp = alloca %struct.mtree_entry*, align 8
  %sparse_entry = alloca %struct.archive_entry*, align 8
  %r = alloca i32, align 4
  %r1 = alloca i32, align 4
  %parsed_kws = alloca i32, align 4
  %n = alloca i64, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !2185, metadata !460), !dbg !2186
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2187, metadata !460), !dbg !2188
  store %struct.mtree* %mtree, %struct.mtree** %mtree.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree** %mtree.addr, metadata !2189, metadata !460), !dbg !2190
  store %struct.mtree_entry* %mentry, %struct.mtree_entry** %mentry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree_entry** %mentry.addr, metadata !2191, metadata !460), !dbg !2192
  store i32* %use_next, i32** %use_next.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %use_next.addr, metadata !2193, metadata !460), !dbg !2194
  call void @llvm.dbg.declare(metadata i8** %path, metadata !2195, metadata !460), !dbg !2196
  call void @llvm.dbg.declare(metadata %struct.stat* %st_storage, metadata !2197, metadata !460), !dbg !2229
  call void @llvm.dbg.declare(metadata %struct.stat** %st, metadata !2230, metadata !460), !dbg !2232
  call void @llvm.dbg.declare(metadata %struct.mtree_entry** %mp, metadata !2233, metadata !460), !dbg !2234
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %sparse_entry, metadata !2235, metadata !460), !dbg !2236
  call void @llvm.dbg.declare(metadata i32* %r, metadata !2237, metadata !460), !dbg !2238
  store i32 0, i32* %r, align 4, !dbg !2238
  call void @llvm.dbg.declare(metadata i32* %r1, metadata !2239, metadata !460), !dbg !2240
  call void @llvm.dbg.declare(metadata i32* %parsed_kws, metadata !2241, metadata !460), !dbg !2242
  %0 = load %struct.mtree_entry*, %struct.mtree_entry** %mentry.addr, align 8, !dbg !2243
  %used = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %0, i32 0, i32 4, !dbg !2244
  store i8 1, i8* %used, align 1, !dbg !2245
  %1 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2246
  call void @archive_entry_set_filetype(%struct.archive_entry* %1, i32 32768), !dbg !2247
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2248
  call void @archive_entry_set_size(%struct.archive_entry* %2, i64 0), !dbg !2249
  %3 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !2250
  %contents_name = getelementptr inbounds %struct.mtree, %struct.mtree* %3, i32 0, i32 11, !dbg !2250
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %contents_name, i32 0, i32 1, !dbg !2250
  store i64 0, i64* %length, align 8, !dbg !2250
  store i32 0, i32* %parsed_kws, align 4, !dbg !2251
  %4 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2252
  %5 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2253
  %6 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !2254
  %7 = load %struct.mtree_entry*, %struct.mtree_entry** %mentry.addr, align 8, !dbg !2255
  %call = call i32 @parse_line(%struct.archive_read* %4, %struct.archive_entry* %5, %struct.mtree* %6, %struct.mtree_entry* %7, i32* %parsed_kws), !dbg !2256
  store i32 %call, i32* %r, align 4, !dbg !2257
  %8 = load %struct.mtree_entry*, %struct.mtree_entry** %mentry.addr, align 8, !dbg !2258
  %full = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %8, i32 0, i32 3, !dbg !2260
  %9 = load i8, i8* %full, align 8, !dbg !2260
  %tobool = icmp ne i8 %9, 0, !dbg !2258
  br i1 %tobool, label %if.then, label %if.else, !dbg !2261

if.then:                                          ; preds = %entry
  %10 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2262
  %11 = load %struct.mtree_entry*, %struct.mtree_entry** %mentry.addr, align 8, !dbg !2264
  %name = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %11, i32 0, i32 2, !dbg !2265
  %12 = load i8*, i8** %name, align 8, !dbg !2265
  call void @archive_entry_copy_pathname(%struct.archive_entry* %10, i8* %12), !dbg !2266
  %13 = load %struct.mtree_entry*, %struct.mtree_entry** %mentry.addr, align 8, !dbg !2267
  %hashtable_next = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %13, i32 0, i32 6, !dbg !2269
  %14 = load %struct.mtree_entry*, %struct.mtree_entry** %hashtable_next, align 8, !dbg !2269
  store %struct.mtree_entry* %14, %struct.mtree_entry** %mp, align 8, !dbg !2270
  br label %for.cond, !dbg !2271

for.cond:                                         ; preds = %for.inc, %if.then
  %15 = load %struct.mtree_entry*, %struct.mtree_entry** %mp, align 8, !dbg !2272
  %cmp = icmp ne %struct.mtree_entry* %15, null, !dbg !2275
  br i1 %cmp, label %for.body, label %for.end, !dbg !2276

for.body:                                         ; preds = %for.cond
  %16 = load %struct.mtree_entry*, %struct.mtree_entry** %mp, align 8, !dbg !2277
  %full2 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %16, i32 0, i32 3, !dbg !2280
  %17 = load i8, i8* %full2, align 8, !dbg !2280
  %conv = sext i8 %17 to i32, !dbg !2277
  %tobool3 = icmp ne i32 %conv, 0, !dbg !2277
  br i1 %tobool3, label %land.lhs.true, label %if.end22, !dbg !2281

land.lhs.true:                                    ; preds = %for.body
  %18 = load %struct.mtree_entry*, %struct.mtree_entry** %mp, align 8, !dbg !2282
  %used4 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %18, i32 0, i32 4, !dbg !2284
  %19 = load i8, i8* %used4, align 1, !dbg !2284
  %tobool5 = icmp ne i8 %19, 0, !dbg !2282
  br i1 %tobool5, label %if.end22, label %land.lhs.true6, !dbg !2285

land.lhs.true6:                                   ; preds = %land.lhs.true
  %20 = load %struct.mtree_entry*, %struct.mtree_entry** %mentry.addr, align 8, !dbg !2286
  %name_hash = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %20, i32 0, i32 5, !dbg !2287
  %21 = load i32, i32* %name_hash, align 4, !dbg !2287
  %22 = load %struct.mtree_entry*, %struct.mtree_entry** %mp, align 8, !dbg !2288
  %name_hash7 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %22, i32 0, i32 5, !dbg !2289
  %23 = load i32, i32* %name_hash7, align 4, !dbg !2289
  %cmp8 = icmp eq i32 %21, %23, !dbg !2290
  br i1 %cmp8, label %land.lhs.true10, label %if.end22, !dbg !2291

land.lhs.true10:                                  ; preds = %land.lhs.true6
  %24 = load %struct.mtree_entry*, %struct.mtree_entry** %mentry.addr, align 8, !dbg !2292
  %name11 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %24, i32 0, i32 2, !dbg !2293
  %25 = load i8*, i8** %name11, align 8, !dbg !2293
  %26 = load %struct.mtree_entry*, %struct.mtree_entry** %mp, align 8, !dbg !2294
  %name12 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %26, i32 0, i32 2, !dbg !2295
  %27 = load i8*, i8** %name12, align 8, !dbg !2295
  %call13 = call i32 @strcmp(i8* %25, i8* %27) #8, !dbg !2296
  %cmp14 = icmp eq i32 %call13, 0, !dbg !2297
  br i1 %cmp14, label %if.then16, label %if.end22, !dbg !2298

if.then16:                                        ; preds = %land.lhs.true10
  %28 = load %struct.mtree_entry*, %struct.mtree_entry** %mp, align 8, !dbg !2300
  %used17 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %28, i32 0, i32 4, !dbg !2302
  store i8 1, i8* %used17, align 1, !dbg !2303
  %29 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2304
  %30 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2305
  %31 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !2306
  %32 = load %struct.mtree_entry*, %struct.mtree_entry** %mp, align 8, !dbg !2307
  %call18 = call i32 @parse_line(%struct.archive_read* %29, %struct.archive_entry* %30, %struct.mtree* %31, %struct.mtree_entry* %32, i32* %parsed_kws), !dbg !2308
  store i32 %call18, i32* %r1, align 4, !dbg !2309
  %33 = load i32, i32* %r1, align 4, !dbg !2310
  %34 = load i32, i32* %r, align 4, !dbg !2312
  %cmp19 = icmp slt i32 %33, %34, !dbg !2313
  br i1 %cmp19, label %if.then21, label %if.end, !dbg !2314

if.then21:                                        ; preds = %if.then16
  %35 = load i32, i32* %r1, align 4, !dbg !2315
  store i32 %35, i32* %r, align 4, !dbg !2316
  br label %if.end, !dbg !2317

if.end:                                           ; preds = %if.then21, %if.then16
  br label %if.end22, !dbg !2318

if.end22:                                         ; preds = %if.end, %land.lhs.true10, %land.lhs.true6, %land.lhs.true, %for.body
  br label %for.inc, !dbg !2319

for.inc:                                          ; preds = %if.end22
  %36 = load %struct.mtree_entry*, %struct.mtree_entry** %mp, align 8, !dbg !2320
  %hashtable_next23 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %36, i32 0, i32 6, !dbg !2322
  %37 = load %struct.mtree_entry*, %struct.mtree_entry** %hashtable_next23, align 8, !dbg !2322
  store %struct.mtree_entry* %37, %struct.mtree_entry** %mp, align 8, !dbg !2323
  br label %for.cond, !dbg !2324

for.end:                                          ; preds = %for.cond
  br label %if.end42, !dbg !2325

if.else:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i64* %n, metadata !2326, metadata !460), !dbg !2328
  %38 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !2329
  %current_dir = getelementptr inbounds %struct.mtree, %struct.mtree* %38, i32 0, i32 10, !dbg !2329
  %length24 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %current_dir, i32 0, i32 1, !dbg !2329
  %39 = load i64, i64* %length24, align 8, !dbg !2329
  store i64 %39, i64* %n, align 8, !dbg !2328
  %40 = load i64, i64* %n, align 8, !dbg !2330
  %cmp25 = icmp ugt i64 %40, 0, !dbg !2332
  br i1 %cmp25, label %if.then27, label %if.end30, !dbg !2333

if.then27:                                        ; preds = %if.else
  %41 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !2334
  %current_dir28 = getelementptr inbounds %struct.mtree, %struct.mtree* %41, i32 0, i32 10, !dbg !2335
  %call29 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %current_dir28, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.49, i32 0, i32 0)), !dbg !2336
  br label %if.end30, !dbg !2336

if.end30:                                         ; preds = %if.then27, %if.else
  %42 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !2337
  %current_dir31 = getelementptr inbounds %struct.mtree, %struct.mtree* %42, i32 0, i32 10, !dbg !2338
  %43 = load %struct.mtree_entry*, %struct.mtree_entry** %mentry.addr, align 8, !dbg !2339
  %name32 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %43, i32 0, i32 2, !dbg !2340
  %44 = load i8*, i8** %name32, align 8, !dbg !2340
  %call33 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %current_dir31, i8* %44), !dbg !2341
  %45 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2342
  %46 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !2343
  %current_dir34 = getelementptr inbounds %struct.mtree, %struct.mtree* %46, i32 0, i32 10, !dbg !2344
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %current_dir34, i32 0, i32 0, !dbg !2345
  %47 = load i8*, i8** %s, align 8, !dbg !2345
  call void @archive_entry_copy_pathname(%struct.archive_entry* %45, i8* %47), !dbg !2346
  %48 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2347
  %call35 = call i32 @archive_entry_filetype(%struct.archive_entry* %48), !dbg !2349
  %cmp36 = icmp ne i32 %call35, 16384, !dbg !2350
  br i1 %cmp36, label %if.then38, label %if.end41, !dbg !2351

if.then38:                                        ; preds = %if.end30
  %49 = load i64, i64* %n, align 8, !dbg !2352
  %50 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !2353
  %current_dir39 = getelementptr inbounds %struct.mtree, %struct.mtree* %50, i32 0, i32 10, !dbg !2354
  %length40 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %current_dir39, i32 0, i32 1, !dbg !2355
  store i64 %49, i64* %length40, align 8, !dbg !2356
  br label %if.end41, !dbg !2353

if.end41:                                         ; preds = %if.then38, %if.end30
  br label %if.end42

if.end42:                                         ; preds = %if.end41, %for.end
  %51 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !2357
  %checkfs = getelementptr inbounds %struct.mtree, %struct.mtree* %51, i32 0, i32 14, !dbg !2359
  %52 = load i8, i8* %checkfs, align 8, !dbg !2359
  %tobool43 = icmp ne i8 %52, 0, !dbg !2357
  br i1 %tobool43, label %if.then44, label %if.end274, !dbg !2360

if.then44:                                        ; preds = %if.end42
  %53 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !2361
  %fd = getelementptr inbounds %struct.mtree, %struct.mtree* %53, i32 0, i32 4, !dbg !2363
  store i32 -1, i32* %fd, align 8, !dbg !2364
  %54 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !2365
  %contents_name45 = getelementptr inbounds %struct.mtree, %struct.mtree* %54, i32 0, i32 11, !dbg !2365
  %length46 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %contents_name45, i32 0, i32 1, !dbg !2365
  %55 = load i64, i64* %length46, align 8, !dbg !2365
  %cmp47 = icmp ugt i64 %55, 0, !dbg !2367
  br i1 %cmp47, label %if.then49, label %if.else52, !dbg !2368

if.then49:                                        ; preds = %if.then44
  %56 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !2369
  %contents_name50 = getelementptr inbounds %struct.mtree, %struct.mtree* %56, i32 0, i32 11, !dbg !2370
  %s51 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %contents_name50, i32 0, i32 0, !dbg !2371
  %57 = load i8*, i8** %s51, align 8, !dbg !2371
  store i8* %57, i8** %path, align 8, !dbg !2372
  br label %if.end54, !dbg !2373

if.else52:                                        ; preds = %if.then44
  %58 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2374
  %call53 = call i8* @archive_entry_pathname(%struct.archive_entry* %58), !dbg !2375
  store i8* %call53, i8** %path, align 8, !dbg !2376
  br label %if.end54

if.end54:                                         ; preds = %if.else52, %if.then49
  %59 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2377
  %call55 = call i32 @archive_entry_filetype(%struct.archive_entry* %59), !dbg !2379
  %cmp56 = icmp eq i32 %call55, 32768, !dbg !2380
  br i1 %cmp56, label %if.then61, label %lor.lhs.false, !dbg !2381

lor.lhs.false:                                    ; preds = %if.end54
  %60 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2382
  %call58 = call i32 @archive_entry_filetype(%struct.archive_entry* %60), !dbg !2383
  %cmp59 = icmp eq i32 %call58, 16384, !dbg !2384
  br i1 %cmp59, label %if.then61, label %if.end80, !dbg !2385

if.then61:                                        ; preds = %lor.lhs.false, %if.end54
  %61 = load i8*, i8** %path, align 8, !dbg !2387
  %call62 = call i32 (i8*, i32, ...) @open(i8* %61, i32 524288), !dbg !2389
  %62 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !2390
  %fd63 = getelementptr inbounds %struct.mtree, %struct.mtree* %62, i32 0, i32 4, !dbg !2391
  store i32 %call62, i32* %fd63, align 8, !dbg !2392
  %63 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !2393
  %fd64 = getelementptr inbounds %struct.mtree, %struct.mtree* %63, i32 0, i32 4, !dbg !2394
  %64 = load i32, i32* %fd64, align 8, !dbg !2394
  call void @__archive_ensure_cloexec_flag(i32 %64), !dbg !2395
  %65 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !2396
  %fd65 = getelementptr inbounds %struct.mtree, %struct.mtree* %65, i32 0, i32 4, !dbg !2398
  %66 = load i32, i32* %fd65, align 8, !dbg !2398
  %cmp66 = icmp eq i32 %66, -1, !dbg !2399
  br i1 %cmp66, label %land.lhs.true68, label %if.end79, !dbg !2400

land.lhs.true68:                                  ; preds = %if.then61
  %call69 = call i32* @__errno_location() #1, !dbg !2401
  %67 = load i32, i32* %call69, align 4, !dbg !2401
  %cmp70 = icmp ne i32 %67, 2, !dbg !2402
  br i1 %cmp70, label %if.then77, label %lor.lhs.false72, !dbg !2403

lor.lhs.false72:                                  ; preds = %land.lhs.true68
  %68 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !2404
  %contents_name73 = getelementptr inbounds %struct.mtree, %struct.mtree* %68, i32 0, i32 11, !dbg !2404
  %length74 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %contents_name73, i32 0, i32 1, !dbg !2404
  %69 = load i64, i64* %length74, align 8, !dbg !2404
  %cmp75 = icmp ugt i64 %69, 0, !dbg !2405
  br i1 %cmp75, label %if.then77, label %if.end79, !dbg !2406

if.then77:                                        ; preds = %lor.lhs.false72, %land.lhs.true68
  %70 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2408
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %70, i32 0, i32 0, !dbg !2410
  %call78 = call i32* @__errno_location() #1, !dbg !2411
  %71 = load i32, i32* %call78, align 4, !dbg !2411
  %72 = load i8*, i8** %path, align 8, !dbg !2412
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 %71, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.50, i32 0, i32 0), i8* %72), !dbg !2413
  store i32 -20, i32* %r, align 4, !dbg !2415
  br label %if.end79, !dbg !2416

if.end79:                                         ; preds = %if.then77, %lor.lhs.false72, %if.then61
  br label %if.end80, !dbg !2417

if.end80:                                         ; preds = %if.end79, %lor.lhs.false
  store %struct.stat* %st_storage, %struct.stat** %st, align 8, !dbg !2418
  %73 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !2419
  %fd81 = getelementptr inbounds %struct.mtree, %struct.mtree* %73, i32 0, i32 4, !dbg !2421
  %74 = load i32, i32* %fd81, align 8, !dbg !2421
  %cmp82 = icmp sge i32 %74, 0, !dbg !2422
  br i1 %cmp82, label %if.then84, label %if.else96, !dbg !2423

if.then84:                                        ; preds = %if.end80
  %75 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !2424
  %fd85 = getelementptr inbounds %struct.mtree, %struct.mtree* %75, i32 0, i32 4, !dbg !2427
  %76 = load i32, i32* %fd85, align 8, !dbg !2427
  %77 = load %struct.stat*, %struct.stat** %st, align 8, !dbg !2428
  %call86 = call i32 @fstat(i32 %76, %struct.stat* %77) #7, !dbg !2429
  %cmp87 = icmp eq i32 %call86, -1, !dbg !2430
  br i1 %cmp87, label %if.then89, label %if.end95, !dbg !2431

if.then89:                                        ; preds = %if.then84
  %78 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2432
  %archive90 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %78, i32 0, i32 0, !dbg !2434
  %call91 = call i32* @__errno_location() #1, !dbg !2435
  %79 = load i32, i32* %call91, align 4, !dbg !2435
  %80 = load i8*, i8** %path, align 8, !dbg !2436
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive90, i32 %79, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.51, i32 0, i32 0), i8* %80), !dbg !2437
  store i32 -20, i32* %r, align 4, !dbg !2439
  %81 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !2440
  %fd92 = getelementptr inbounds %struct.mtree, %struct.mtree* %81, i32 0, i32 4, !dbg !2441
  %82 = load i32, i32* %fd92, align 8, !dbg !2441
  %call93 = call i32 @close(i32 %82), !dbg !2442
  %83 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !2443
  %fd94 = getelementptr inbounds %struct.mtree, %struct.mtree* %83, i32 0, i32 4, !dbg !2444
  store i32 -1, i32* %fd94, align 8, !dbg !2445
  store %struct.stat* null, %struct.stat** %st, align 8, !dbg !2446
  br label %if.end95, !dbg !2447

if.end95:                                         ; preds = %if.then89, %if.then84
  br label %if.end102, !dbg !2448

if.else96:                                        ; preds = %if.end80
  %84 = load i8*, i8** %path, align 8, !dbg !2449
  %85 = load %struct.stat*, %struct.stat** %st, align 8, !dbg !2452
  %call97 = call i32 @lstat(i8* %84, %struct.stat* %85) #7, !dbg !2453
  %cmp98 = icmp eq i32 %call97, -1, !dbg !2454
  br i1 %cmp98, label %if.then100, label %if.end101, !dbg !2453

if.then100:                                       ; preds = %if.else96
  store %struct.stat* null, %struct.stat** %st, align 8, !dbg !2455
  br label %if.end101, !dbg !2457

if.end101:                                        ; preds = %if.then100, %if.else96
  br label %if.end102

if.end102:                                        ; preds = %if.end101, %if.end95
  %86 = load %struct.stat*, %struct.stat** %st, align 8, !dbg !2458
  %cmp103 = icmp ne %struct.stat* %86, null, !dbg !2460
  br i1 %cmp103, label %if.then105, label %if.end188, !dbg !2461

if.then105:                                       ; preds = %if.end102
  %87 = load %struct.stat*, %struct.stat** %st, align 8, !dbg !2462
  %st_mode = getelementptr inbounds %struct.stat, %struct.stat* %87, i32 0, i32 3, !dbg !2465
  %88 = load i32, i32* %st_mode, align 8, !dbg !2465
  %and = and i32 %88, 61440, !dbg !2466
  %cmp106 = icmp eq i32 %and, 32768, !dbg !2467
  br i1 %cmp106, label %land.lhs.true108, label %lor.lhs.false112, !dbg !2468

land.lhs.true108:                                 ; preds = %if.then105
  %89 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2469
  %call109 = call i32 @archive_entry_filetype(%struct.archive_entry* %89), !dbg !2470
  %cmp110 = icmp eq i32 %call109, 32768, !dbg !2471
  br i1 %cmp110, label %if.then166, label %lor.lhs.false112, !dbg !2472

lor.lhs.false112:                                 ; preds = %land.lhs.true108, %if.then105
  %90 = load %struct.stat*, %struct.stat** %st, align 8, !dbg !2473
  %st_mode113 = getelementptr inbounds %struct.stat, %struct.stat* %90, i32 0, i32 3, !dbg !2475
  %91 = load i32, i32* %st_mode113, align 8, !dbg !2475
  %and114 = and i32 %91, 61440, !dbg !2476
  %cmp115 = icmp eq i32 %and114, 40960, !dbg !2477
  br i1 %cmp115, label %land.lhs.true117, label %lor.lhs.false121, !dbg !2478

land.lhs.true117:                                 ; preds = %lor.lhs.false112
  %92 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2479
  %call118 = call i32 @archive_entry_filetype(%struct.archive_entry* %92), !dbg !2480
  %cmp119 = icmp eq i32 %call118, 40960, !dbg !2481
  br i1 %cmp119, label %if.then166, label %lor.lhs.false121, !dbg !2482

lor.lhs.false121:                                 ; preds = %land.lhs.true117, %lor.lhs.false112
  %93 = load %struct.stat*, %struct.stat** %st, align 8, !dbg !2483
  %st_mode122 = getelementptr inbounds %struct.stat, %struct.stat* %93, i32 0, i32 3, !dbg !2484
  %94 = load i32, i32* %st_mode122, align 8, !dbg !2484
  %and123 = and i32 %94, 49152, !dbg !2485
  %cmp124 = icmp eq i32 %and123, 49152, !dbg !2486
  br i1 %cmp124, label %land.lhs.true126, label %lor.lhs.false130, !dbg !2487

land.lhs.true126:                                 ; preds = %lor.lhs.false121
  %95 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2488
  %call127 = call i32 @archive_entry_filetype(%struct.archive_entry* %95), !dbg !2489
  %cmp128 = icmp eq i32 %call127, 49152, !dbg !2490
  br i1 %cmp128, label %if.then166, label %lor.lhs.false130, !dbg !2491

lor.lhs.false130:                                 ; preds = %land.lhs.true126, %lor.lhs.false121
  %96 = load %struct.stat*, %struct.stat** %st, align 8, !dbg !2492
  %st_mode131 = getelementptr inbounds %struct.stat, %struct.stat* %96, i32 0, i32 3, !dbg !2493
  %97 = load i32, i32* %st_mode131, align 8, !dbg !2493
  %and132 = and i32 %97, 61440, !dbg !2494
  %cmp133 = icmp eq i32 %and132, 8192, !dbg !2495
  br i1 %cmp133, label %land.lhs.true135, label %lor.lhs.false139, !dbg !2496

land.lhs.true135:                                 ; preds = %lor.lhs.false130
  %98 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2497
  %call136 = call i32 @archive_entry_filetype(%struct.archive_entry* %98), !dbg !2498
  %cmp137 = icmp eq i32 %call136, 8192, !dbg !2499
  br i1 %cmp137, label %if.then166, label %lor.lhs.false139, !dbg !2500

lor.lhs.false139:                                 ; preds = %land.lhs.true135, %lor.lhs.false130
  %99 = load %struct.stat*, %struct.stat** %st, align 8, !dbg !2501
  %st_mode140 = getelementptr inbounds %struct.stat, %struct.stat* %99, i32 0, i32 3, !dbg !2502
  %100 = load i32, i32* %st_mode140, align 8, !dbg !2502
  %and141 = and i32 %100, 61440, !dbg !2503
  %cmp142 = icmp eq i32 %and141, 24576, !dbg !2504
  br i1 %cmp142, label %land.lhs.true144, label %lor.lhs.false148, !dbg !2505

land.lhs.true144:                                 ; preds = %lor.lhs.false139
  %101 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2506
  %call145 = call i32 @archive_entry_filetype(%struct.archive_entry* %101), !dbg !2507
  %cmp146 = icmp eq i32 %call145, 24576, !dbg !2508
  br i1 %cmp146, label %if.then166, label %lor.lhs.false148, !dbg !2509

lor.lhs.false148:                                 ; preds = %land.lhs.true144, %lor.lhs.false139
  %102 = load %struct.stat*, %struct.stat** %st, align 8, !dbg !2510
  %st_mode149 = getelementptr inbounds %struct.stat, %struct.stat* %102, i32 0, i32 3, !dbg !2511
  %103 = load i32, i32* %st_mode149, align 8, !dbg !2511
  %and150 = and i32 %103, 61440, !dbg !2512
  %cmp151 = icmp eq i32 %and150, 16384, !dbg !2513
  br i1 %cmp151, label %land.lhs.true153, label %lor.lhs.false157, !dbg !2514

land.lhs.true153:                                 ; preds = %lor.lhs.false148
  %104 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2515
  %call154 = call i32 @archive_entry_filetype(%struct.archive_entry* %104), !dbg !2516
  %cmp155 = icmp eq i32 %call154, 16384, !dbg !2517
  br i1 %cmp155, label %if.then166, label %lor.lhs.false157, !dbg !2518

lor.lhs.false157:                                 ; preds = %land.lhs.true153, %lor.lhs.false148
  %105 = load %struct.stat*, %struct.stat** %st, align 8, !dbg !2519
  %st_mode158 = getelementptr inbounds %struct.stat, %struct.stat* %105, i32 0, i32 3, !dbg !2520
  %106 = load i32, i32* %st_mode158, align 8, !dbg !2520
  %and159 = and i32 %106, 61440, !dbg !2521
  %cmp160 = icmp eq i32 %and159, 4096, !dbg !2522
  br i1 %cmp160, label %land.lhs.true162, label %if.else167, !dbg !2523

land.lhs.true162:                                 ; preds = %lor.lhs.false157
  %107 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2524
  %call163 = call i32 @archive_entry_filetype(%struct.archive_entry* %107), !dbg !2525
  %cmp164 = icmp eq i32 %call163, 4096, !dbg !2526
  br i1 %cmp164, label %if.then166, label %if.else167, !dbg !2527

if.then166:                                       ; preds = %land.lhs.true162, %land.lhs.true153, %land.lhs.true144, %land.lhs.true135, %land.lhs.true126, %land.lhs.true117, %land.lhs.true108
  br label %if.end187, !dbg !2529

if.else167:                                       ; preds = %land.lhs.true162, %lor.lhs.false157
  %108 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !2531
  %fd168 = getelementptr inbounds %struct.mtree, %struct.mtree* %108, i32 0, i32 4, !dbg !2534
  %109 = load i32, i32* %fd168, align 8, !dbg !2534
  %cmp169 = icmp sge i32 %109, 0, !dbg !2535
  br i1 %cmp169, label %if.then171, label %if.end174, !dbg !2536

if.then171:                                       ; preds = %if.else167
  %110 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !2537
  %fd172 = getelementptr inbounds %struct.mtree, %struct.mtree* %110, i32 0, i32 4, !dbg !2538
  %111 = load i32, i32* %fd172, align 8, !dbg !2538
  %call173 = call i32 @close(i32 %111), !dbg !2539
  br label %if.end174, !dbg !2539

if.end174:                                        ; preds = %if.then171, %if.else167
  %112 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !2540
  %fd175 = getelementptr inbounds %struct.mtree, %struct.mtree* %112, i32 0, i32 4, !dbg !2541
  store i32 -1, i32* %fd175, align 8, !dbg !2542
  %113 = load i32, i32* %parsed_kws, align 4, !dbg !2543
  %and176 = and i32 %113, 2048, !dbg !2545
  %tobool177 = icmp ne i32 %and176, 0, !dbg !2545
  br i1 %tobool177, label %if.then178, label %if.else179, !dbg !2546

if.then178:                                       ; preds = %if.end174
  %114 = load i32*, i32** %use_next.addr, align 8, !dbg !2547
  store i32 1, i32* %114, align 4, !dbg !2549
  br label %if.end186, !dbg !2550

if.else179:                                       ; preds = %if.end174
  %115 = load i32, i32* %r, align 4, !dbg !2551
  %cmp180 = icmp eq i32 %115, 0, !dbg !2554
  br i1 %cmp180, label %if.then182, label %if.end185, !dbg !2551

if.then182:                                       ; preds = %if.else179
  %116 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2555
  %archive183 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %116, i32 0, i32 0, !dbg !2557
  %117 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2558
  %call184 = call i8* @archive_entry_pathname(%struct.archive_entry* %117), !dbg !2559
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive183, i32 -1, i8* getelementptr inbounds ([46 x i8], [46 x i8]* @.str.52, i32 0, i32 0), i8* %call184), !dbg !2560
  store i32 -20, i32* %r, align 4, !dbg !2561
  br label %if.end185, !dbg !2562

if.end185:                                        ; preds = %if.then182, %if.else179
  br label %if.end186

if.end186:                                        ; preds = %if.end185, %if.then178
  %118 = load i32, i32* %r, align 4, !dbg !2563
  store i32 %118, i32* %retval, align 4, !dbg !2564
  br label %return, !dbg !2564

if.end187:                                        ; preds = %if.then166
  br label %if.end188, !dbg !2565

if.end188:                                        ; preds = %if.end187, %if.end102
  %119 = load %struct.stat*, %struct.stat** %st, align 8, !dbg !2566
  %cmp189 = icmp ne %struct.stat* %119, null, !dbg !2568
  br i1 %cmp189, label %if.then191, label %if.else268, !dbg !2569

if.then191:                                       ; preds = %if.end188
  %120 = load i32, i32* %parsed_kws, align 4, !dbg !2570
  %and192 = and i32 %120, 1, !dbg !2573
  %cmp193 = icmp eq i32 %and192, 0, !dbg !2574
  br i1 %cmp193, label %land.lhs.true199, label %lor.lhs.false195, !dbg !2575

lor.lhs.false195:                                 ; preds = %if.then191
  %121 = load i32, i32* %parsed_kws, align 4, !dbg !2576
  %and196 = and i32 %121, 4096, !dbg !2577
  %cmp197 = icmp ne i32 %and196, 0, !dbg !2578
  br i1 %cmp197, label %land.lhs.true199, label %if.end208, !dbg !2579

land.lhs.true199:                                 ; preds = %lor.lhs.false195, %if.then191
  %122 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2580
  %call200 = call i32 @archive_entry_filetype(%struct.archive_entry* %122), !dbg !2581
  %cmp201 = icmp eq i32 %call200, 8192, !dbg !2582
  br i1 %cmp201, label %if.then207, label %lor.lhs.false203, !dbg !2583

lor.lhs.false203:                                 ; preds = %land.lhs.true199
  %123 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2584
  %call204 = call i32 @archive_entry_filetype(%struct.archive_entry* %123), !dbg !2585
  %cmp205 = icmp eq i32 %call204, 24576, !dbg !2586
  br i1 %cmp205, label %if.then207, label %if.end208, !dbg !2587

if.then207:                                       ; preds = %lor.lhs.false203, %land.lhs.true199
  %124 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2589
  %125 = load %struct.stat*, %struct.stat** %st, align 8, !dbg !2590
  %st_rdev = getelementptr inbounds %struct.stat, %struct.stat* %125, i32 0, i32 7, !dbg !2591
  %126 = load i64, i64* %st_rdev, align 8, !dbg !2591
  call void @archive_entry_set_rdev(%struct.archive_entry* %124, i64 %126), !dbg !2592
  br label %if.end208, !dbg !2592

if.end208:                                        ; preds = %if.then207, %lor.lhs.false203, %lor.lhs.false195
  %127 = load i32, i32* %parsed_kws, align 4, !dbg !2593
  %and209 = and i32 %127, 12, !dbg !2595
  %cmp210 = icmp eq i32 %and209, 0, !dbg !2596
  br i1 %cmp210, label %if.then216, label %lor.lhs.false212, !dbg !2597

lor.lhs.false212:                                 ; preds = %if.end208
  %128 = load i32, i32* %parsed_kws, align 4, !dbg !2598
  %and213 = and i32 %128, 4096, !dbg !2599
  %cmp214 = icmp ne i32 %and213, 0, !dbg !2600
  br i1 %cmp214, label %if.then216, label %if.end218, !dbg !2601

if.then216:                                       ; preds = %lor.lhs.false212, %if.end208
  %129 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2602
  %130 = load %struct.stat*, %struct.stat** %st, align 8, !dbg !2603
  %st_gid = getelementptr inbounds %struct.stat, %struct.stat* %130, i32 0, i32 5, !dbg !2604
  %131 = load i32, i32* %st_gid, align 8, !dbg !2604
  %conv217 = zext i32 %131 to i64, !dbg !2603
  call void @archive_entry_set_gid(%struct.archive_entry* %129, i64 %conv217), !dbg !2605
  br label %if.end218, !dbg !2605

if.end218:                                        ; preds = %if.then216, %lor.lhs.false212
  %132 = load i32, i32* %parsed_kws, align 4, !dbg !2606
  %and219 = and i32 %132, 1536, !dbg !2608
  %cmp220 = icmp eq i32 %and219, 0, !dbg !2609
  br i1 %cmp220, label %if.then226, label %lor.lhs.false222, !dbg !2610

lor.lhs.false222:                                 ; preds = %if.end218
  %133 = load i32, i32* %parsed_kws, align 4, !dbg !2611
  %and223 = and i32 %133, 4096, !dbg !2612
  %cmp224 = icmp ne i32 %and223, 0, !dbg !2613
  br i1 %cmp224, label %if.then226, label %if.end228, !dbg !2614

if.then226:                                       ; preds = %lor.lhs.false222, %if.end218
  %134 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2615
  %135 = load %struct.stat*, %struct.stat** %st, align 8, !dbg !2616
  %st_uid = getelementptr inbounds %struct.stat, %struct.stat* %135, i32 0, i32 4, !dbg !2617
  %136 = load i32, i32* %st_uid, align 4, !dbg !2617
  %conv227 = zext i32 %136 to i64, !dbg !2616
  call void @archive_entry_set_uid(%struct.archive_entry* %134, i64 %conv227), !dbg !2618
  br label %if.end228, !dbg !2618

if.end228:                                        ; preds = %if.then226, %lor.lhs.false222
  %137 = load i32, i32* %parsed_kws, align 4, !dbg !2619
  %and229 = and i32 %137, 16, !dbg !2621
  %cmp230 = icmp eq i32 %and229, 0, !dbg !2622
  br i1 %cmp230, label %if.then236, label %lor.lhs.false232, !dbg !2623

lor.lhs.false232:                                 ; preds = %if.end228
  %138 = load i32, i32* %parsed_kws, align 4, !dbg !2624
  %and233 = and i32 %138, 4096, !dbg !2625
  %cmp234 = icmp ne i32 %and233, 0, !dbg !2626
  br i1 %cmp234, label %if.then236, label %if.end238, !dbg !2627

if.then236:                                       ; preds = %lor.lhs.false232, %if.end228
  %139 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2628
  %140 = load %struct.stat*, %struct.stat** %st, align 8, !dbg !2630
  %st_mtim = getelementptr inbounds %struct.stat, %struct.stat* %140, i32 0, i32 12, !dbg !2631
  %tv_sec = getelementptr inbounds %struct.timespec, %struct.timespec* %st_mtim, i32 0, i32 0, !dbg !2631
  %141 = load i64, i64* %tv_sec, align 8, !dbg !2631
  %142 = load %struct.stat*, %struct.stat** %st, align 8, !dbg !2632
  %st_mtim237 = getelementptr inbounds %struct.stat, %struct.stat* %142, i32 0, i32 12, !dbg !2633
  %tv_nsec = getelementptr inbounds %struct.timespec, %struct.timespec* %st_mtim237, i32 0, i32 1, !dbg !2634
  %143 = load i64, i64* %tv_nsec, align 8, !dbg !2634
  call void @archive_entry_set_mtime(%struct.archive_entry* %139, i64 %141, i64 %143), !dbg !2635
  br label %if.end238, !dbg !2636

if.end238:                                        ; preds = %if.then236, %lor.lhs.false232
  %144 = load i32, i32* %parsed_kws, align 4, !dbg !2637
  %and239 = and i32 %144, 32, !dbg !2639
  %cmp240 = icmp eq i32 %and239, 0, !dbg !2640
  br i1 %cmp240, label %if.then246, label %lor.lhs.false242, !dbg !2641

lor.lhs.false242:                                 ; preds = %if.end238
  %145 = load i32, i32* %parsed_kws, align 4, !dbg !2642
  %and243 = and i32 %145, 4096, !dbg !2643
  %cmp244 = icmp ne i32 %and243, 0, !dbg !2644
  br i1 %cmp244, label %if.then246, label %if.end248, !dbg !2645

if.then246:                                       ; preds = %lor.lhs.false242, %if.end238
  %146 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2646
  %147 = load %struct.stat*, %struct.stat** %st, align 8, !dbg !2647
  %st_nlink = getelementptr inbounds %struct.stat, %struct.stat* %147, i32 0, i32 2, !dbg !2648
  %148 = load i64, i64* %st_nlink, align 8, !dbg !2648
  %conv247 = trunc i64 %148 to i32, !dbg !2647
  call void @archive_entry_set_nlink(%struct.archive_entry* %146, i32 %conv247), !dbg !2649
  br label %if.end248, !dbg !2649

if.end248:                                        ; preds = %if.then246, %lor.lhs.false242
  %149 = load i32, i32* %parsed_kws, align 4, !dbg !2650
  %and249 = and i32 %149, 64, !dbg !2652
  %cmp250 = icmp eq i32 %and249, 0, !dbg !2653
  br i1 %cmp250, label %if.then256, label %lor.lhs.false252, !dbg !2654

lor.lhs.false252:                                 ; preds = %if.end248
  %150 = load i32, i32* %parsed_kws, align 4, !dbg !2655
  %and253 = and i32 %150, 4096, !dbg !2656
  %cmp254 = icmp ne i32 %and253, 0, !dbg !2657
  br i1 %cmp254, label %if.then256, label %if.end258, !dbg !2658

if.then256:                                       ; preds = %lor.lhs.false252, %if.end248
  %151 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2659
  %152 = load %struct.stat*, %struct.stat** %st, align 8, !dbg !2660
  %st_mode257 = getelementptr inbounds %struct.stat, %struct.stat* %152, i32 0, i32 3, !dbg !2661
  %153 = load i32, i32* %st_mode257, align 8, !dbg !2661
  call void @archive_entry_set_perm(%struct.archive_entry* %151, i32 %153), !dbg !2662
  br label %if.end258, !dbg !2662

if.end258:                                        ; preds = %if.then256, %lor.lhs.false252
  %154 = load i32, i32* %parsed_kws, align 4, !dbg !2663
  %and259 = and i32 %154, 128, !dbg !2665
  %cmp260 = icmp eq i32 %and259, 0, !dbg !2666
  br i1 %cmp260, label %if.then266, label %lor.lhs.false262, !dbg !2667

lor.lhs.false262:                                 ; preds = %if.end258
  %155 = load i32, i32* %parsed_kws, align 4, !dbg !2668
  %and263 = and i32 %155, 4096, !dbg !2669
  %cmp264 = icmp ne i32 %and263, 0, !dbg !2670
  br i1 %cmp264, label %if.then266, label %if.end267, !dbg !2671

if.then266:                                       ; preds = %lor.lhs.false262, %if.end258
  %156 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2672
  %157 = load %struct.stat*, %struct.stat** %st, align 8, !dbg !2673
  %st_size = getelementptr inbounds %struct.stat, %struct.stat* %157, i32 0, i32 8, !dbg !2674
  %158 = load i64, i64* %st_size, align 8, !dbg !2674
  call void @archive_entry_set_size(%struct.archive_entry* %156, i64 %158), !dbg !2675
  br label %if.end267, !dbg !2675

if.end267:                                        ; preds = %if.then266, %lor.lhs.false262
  %159 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2676
  %160 = load %struct.stat*, %struct.stat** %st, align 8, !dbg !2677
  %st_ino = getelementptr inbounds %struct.stat, %struct.stat* %160, i32 0, i32 1, !dbg !2678
  %161 = load i64, i64* %st_ino, align 8, !dbg !2678
  call void @archive_entry_set_ino(%struct.archive_entry* %159, i64 %161), !dbg !2679
  %162 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2680
  %163 = load %struct.stat*, %struct.stat** %st, align 8, !dbg !2681
  %st_dev = getelementptr inbounds %struct.stat, %struct.stat* %163, i32 0, i32 0, !dbg !2682
  %164 = load i64, i64* %st_dev, align 8, !dbg !2682
  call void @archive_entry_set_dev(%struct.archive_entry* %162, i64 %164), !dbg !2683
  %165 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !2684
  %resolver = getelementptr inbounds %struct.mtree, %struct.mtree* %165, i32 0, i32 12, !dbg !2685
  %166 = load %struct.archive_entry_linkresolver*, %struct.archive_entry_linkresolver** %resolver, align 8, !dbg !2685
  call void @archive_entry_linkify(%struct.archive_entry_linkresolver* %166, %struct.archive_entry** %entry.addr, %struct.archive_entry** %sparse_entry), !dbg !2686
  br label %if.end273, !dbg !2687

if.else268:                                       ; preds = %if.end188
  %167 = load i32, i32* %parsed_kws, align 4, !dbg !2688
  %and269 = and i32 %167, 2048, !dbg !2691
  %tobool270 = icmp ne i32 %and269, 0, !dbg !2691
  br i1 %tobool270, label %if.then271, label %if.end272, !dbg !2688

if.then271:                                       ; preds = %if.else268
  %168 = load i32*, i32** %use_next.addr, align 8, !dbg !2692
  store i32 1, i32* %168, align 4, !dbg !2694
  store i32 0, i32* %retval, align 4, !dbg !2695
  br label %return, !dbg !2695

if.end272:                                        ; preds = %if.else268
  br label %if.end273

if.end273:                                        ; preds = %if.end272, %if.end267
  br label %if.end274, !dbg !2696

if.end274:                                        ; preds = %if.end273, %if.end42
  %169 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2697
  %call275 = call i64 @archive_entry_size(%struct.archive_entry* %169), !dbg !2698
  %170 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !2699
  %cur_size = getelementptr inbounds %struct.mtree, %struct.mtree* %170, i32 0, i32 13, !dbg !2700
  store i64 %call275, i64* %cur_size, align 8, !dbg !2701
  %171 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !2702
  %offset = getelementptr inbounds %struct.mtree, %struct.mtree* %171, i32 0, i32 3, !dbg !2703
  store i64 0, i64* %offset, align 8, !dbg !2704
  %172 = load i32, i32* %r, align 4, !dbg !2705
  store i32 %172, i32* %retval, align 4, !dbg !2706
  br label %return, !dbg !2706

return:                                           ; preds = %if.end274, %if.then271, %if.end186
  %173 = load i32, i32* %retval, align 4, !dbg !2707
  ret i32 %173, !dbg !2707
}

; Function Attrs: nounwind uwtable
define internal i64 @readline(%struct.archive_read* %a, %struct.mtree* %mtree, i8** %start, i64 %limit) #0 !dbg !378 {
entry:
  %retval = alloca i64, align 8
  %a.addr = alloca %struct.archive_read*, align 8
  %mtree.addr = alloca %struct.mtree*, align 8
  %start.addr = alloca i8**, align 8
  %limit.addr = alloca i64, align 8
  %bytes_read = alloca i64, align 8
  %total_size = alloca i64, align 8
  %find_off = alloca i64, align 8
  %t = alloca i8*, align 8
  %nl = alloca i8*, align 8
  %u = alloca i8*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !2708, metadata !460), !dbg !2709
  store %struct.mtree* %mtree, %struct.mtree** %mtree.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree** %mtree.addr, metadata !2710, metadata !460), !dbg !2711
  store i8** %start, i8*** %start.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %start.addr, metadata !2712, metadata !460), !dbg !2713
  store i64 %limit, i64* %limit.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %limit.addr, metadata !2714, metadata !460), !dbg !2715
  call void @llvm.dbg.declare(metadata i64* %bytes_read, metadata !2716, metadata !460), !dbg !2717
  call void @llvm.dbg.declare(metadata i64* %total_size, metadata !2718, metadata !460), !dbg !2719
  store i64 0, i64* %total_size, align 8, !dbg !2719
  call void @llvm.dbg.declare(metadata i64* %find_off, metadata !2720, metadata !460), !dbg !2721
  store i64 0, i64* %find_off, align 8, !dbg !2721
  call void @llvm.dbg.declare(metadata i8** %t, metadata !2722, metadata !460), !dbg !2723
  call void @llvm.dbg.declare(metadata i8** %nl, metadata !2724, metadata !460), !dbg !2725
  call void @llvm.dbg.declare(metadata i8** %u, metadata !2726, metadata !460), !dbg !2727
  br label %for.cond, !dbg !2728

for.cond:                                         ; preds = %for.end, %entry
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2729
  %call = call i8* @__archive_read_ahead(%struct.archive_read* %0, i64 1, i64* %bytes_read), !dbg !2733
  store i8* %call, i8** %t, align 8, !dbg !2734
  %1 = load i8*, i8** %t, align 8, !dbg !2735
  %cmp = icmp eq i8* %1, null, !dbg !2737
  br i1 %cmp, label %if.then, label %if.end, !dbg !2738

if.then:                                          ; preds = %for.cond
  store i64 0, i64* %retval, align 8, !dbg !2739
  br label %return, !dbg !2739

if.end:                                           ; preds = %for.cond
  %2 = load i64, i64* %bytes_read, align 8, !dbg !2740
  %cmp1 = icmp slt i64 %2, 0, !dbg !2742
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !2743

if.then2:                                         ; preds = %if.end
  store i64 -30, i64* %retval, align 8, !dbg !2744
  br label %return, !dbg !2744

if.end3:                                          ; preds = %if.end
  %3 = load i8*, i8** %t, align 8, !dbg !2745
  %4 = load i64, i64* %bytes_read, align 8, !dbg !2746
  %call4 = call i8* @memchr(i8* %3, i32 10, i64 %4) #8, !dbg !2747
  store i8* %call4, i8** %nl, align 8, !dbg !2748
  %5 = load i8*, i8** %nl, align 8, !dbg !2749
  %cmp5 = icmp ne i8* %5, null, !dbg !2751
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !2752

if.then6:                                         ; preds = %if.end3
  %6 = load i8*, i8** %nl, align 8, !dbg !2753
  %7 = load i8*, i8** %t, align 8, !dbg !2755
  %sub.ptr.lhs.cast = ptrtoint i8* %6 to i64, !dbg !2756
  %sub.ptr.rhs.cast = ptrtoint i8* %7 to i64, !dbg !2756
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !2756
  %add = add nsw i64 %sub.ptr.sub, 1, !dbg !2757
  store i64 %add, i64* %bytes_read, align 8, !dbg !2758
  br label %if.end7, !dbg !2759

if.end7:                                          ; preds = %if.then6, %if.end3
  %8 = load i64, i64* %total_size, align 8, !dbg !2760
  %9 = load i64, i64* %bytes_read, align 8, !dbg !2762
  %add8 = add nsw i64 %8, %9, !dbg !2763
  %add9 = add nsw i64 %add8, 1, !dbg !2764
  %10 = load i64, i64* %limit.addr, align 8, !dbg !2765
  %cmp10 = icmp sgt i64 %add9, %10, !dbg !2766
  br i1 %cmp10, label %if.then11, label %if.end12, !dbg !2767

if.then11:                                        ; preds = %if.end7
  %11 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2768
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %11, i32 0, i32 0, !dbg !2770
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 84, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.43, i32 0, i32 0)), !dbg !2771
  store i64 -30, i64* %retval, align 8, !dbg !2772
  br label %return, !dbg !2772

if.end12:                                         ; preds = %if.end7
  %12 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !2773
  %line = getelementptr inbounds %struct.mtree, %struct.mtree* %12, i32 0, i32 0, !dbg !2775
  %13 = load i64, i64* %total_size, align 8, !dbg !2776
  %14 = load i64, i64* %bytes_read, align 8, !dbg !2777
  %add13 = add nsw i64 %13, %14, !dbg !2778
  %add14 = add nsw i64 %add13, 1, !dbg !2779
  %call15 = call %struct.archive_string* @archive_string_ensure(%struct.archive_string* %line, i64 %add14), !dbg !2780
  %cmp16 = icmp eq %struct.archive_string* %call15, null, !dbg !2781
  br i1 %cmp16, label %if.then17, label %if.end19, !dbg !2782

if.then17:                                        ; preds = %if.end12
  %15 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2783
  %archive18 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %15, i32 0, i32 0, !dbg !2785
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive18, i32 12, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.44, i32 0, i32 0)), !dbg !2786
  store i64 -30, i64* %retval, align 8, !dbg !2787
  br label %return, !dbg !2787

if.end19:                                         ; preds = %if.end12
  %16 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !2788
  %line20 = getelementptr inbounds %struct.mtree, %struct.mtree* %16, i32 0, i32 0, !dbg !2789
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %line20, i32 0, i32 0, !dbg !2790
  %17 = load i8*, i8** %s, align 8, !dbg !2790
  %18 = load i64, i64* %total_size, align 8, !dbg !2791
  %add.ptr = getelementptr inbounds i8, i8* %17, i64 %18, !dbg !2792
  %19 = load i8*, i8** %t, align 8, !dbg !2793
  %20 = load i64, i64* %bytes_read, align 8, !dbg !2794
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %add.ptr, i8* %19, i64 %20, i32 1, i1 false), !dbg !2795
  %21 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2796
  %22 = load i64, i64* %bytes_read, align 8, !dbg !2797
  %call21 = call i64 @__archive_read_consume(%struct.archive_read* %21, i64 %22), !dbg !2798
  %23 = load i64, i64* %bytes_read, align 8, !dbg !2799
  %24 = load i64, i64* %total_size, align 8, !dbg !2800
  %add22 = add nsw i64 %24, %23, !dbg !2800
  store i64 %add22, i64* %total_size, align 8, !dbg !2800
  %25 = load i64, i64* %total_size, align 8, !dbg !2801
  %26 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !2802
  %line23 = getelementptr inbounds %struct.mtree, %struct.mtree* %26, i32 0, i32 0, !dbg !2803
  %s24 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %line23, i32 0, i32 0, !dbg !2804
  %27 = load i8*, i8** %s24, align 8, !dbg !2804
  %arrayidx = getelementptr inbounds i8, i8* %27, i64 %25, !dbg !2802
  store i8 0, i8* %arrayidx, align 1, !dbg !2805
  %28 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !2806
  %line25 = getelementptr inbounds %struct.mtree, %struct.mtree* %28, i32 0, i32 0, !dbg !2808
  %s26 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %line25, i32 0, i32 0, !dbg !2809
  %29 = load i8*, i8** %s26, align 8, !dbg !2809
  %30 = load i64, i64* %find_off, align 8, !dbg !2810
  %add.ptr27 = getelementptr inbounds i8, i8* %29, i64 %30, !dbg !2811
  store i8* %add.ptr27, i8** %u, align 8, !dbg !2812
  br label %for.cond28, !dbg !2813

for.cond28:                                       ; preds = %for.inc, %if.end19
  %31 = load i8*, i8** %u, align 8, !dbg !2814
  %32 = load i8, i8* %31, align 1, !dbg !2817
  %tobool = icmp ne i8 %32, 0, !dbg !2818
  br i1 %tobool, label %for.body, label %for.end, !dbg !2818

for.body:                                         ; preds = %for.cond28
  %33 = load i8*, i8** %u, align 8, !dbg !2819
  %arrayidx29 = getelementptr inbounds i8, i8* %33, i64 0, !dbg !2819
  %34 = load i8, i8* %arrayidx29, align 1, !dbg !2819
  %conv = sext i8 %34 to i32, !dbg !2819
  %cmp30 = icmp eq i32 %conv, 10, !dbg !2822
  br i1 %cmp30, label %if.then32, label %if.else, !dbg !2823

if.then32:                                        ; preds = %for.body
  %35 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !2824
  %line33 = getelementptr inbounds %struct.mtree, %struct.mtree* %35, i32 0, i32 0, !dbg !2826
  %s34 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %line33, i32 0, i32 0, !dbg !2827
  %36 = load i8*, i8** %s34, align 8, !dbg !2827
  %37 = load i8**, i8*** %start.addr, align 8, !dbg !2828
  store i8* %36, i8** %37, align 8, !dbg !2829
  %38 = load i64, i64* %total_size, align 8, !dbg !2830
  store i64 %38, i64* %retval, align 8, !dbg !2831
  br label %return, !dbg !2831

if.else:                                          ; preds = %for.body
  %39 = load i8*, i8** %u, align 8, !dbg !2832
  %arrayidx35 = getelementptr inbounds i8, i8* %39, i64 0, !dbg !2832
  %40 = load i8, i8* %arrayidx35, align 1, !dbg !2832
  %conv36 = sext i8 %40 to i32, !dbg !2832
  %cmp37 = icmp eq i32 %conv36, 35, !dbg !2834
  br i1 %cmp37, label %if.then39, label %if.else44, !dbg !2835

if.then39:                                        ; preds = %if.else
  %41 = load i8*, i8** %nl, align 8, !dbg !2836
  %cmp40 = icmp eq i8* %41, null, !dbg !2839
  br i1 %cmp40, label %if.then42, label %if.end43, !dbg !2840

if.then42:                                        ; preds = %if.then39
  br label %for.end, !dbg !2841

if.end43:                                         ; preds = %if.then39
  br label %if.end67, !dbg !2843

if.else44:                                        ; preds = %if.else
  %42 = load i8*, i8** %u, align 8, !dbg !2844
  %arrayidx45 = getelementptr inbounds i8, i8* %42, i64 0, !dbg !2844
  %43 = load i8, i8* %arrayidx45, align 1, !dbg !2844
  %conv46 = sext i8 %43 to i32, !dbg !2844
  %cmp47 = icmp eq i32 %conv46, 92, !dbg !2847
  br i1 %cmp47, label %if.then49, label %if.end66, !dbg !2844

if.then49:                                        ; preds = %if.else44
  %44 = load i8*, i8** %u, align 8, !dbg !2848
  %arrayidx50 = getelementptr inbounds i8, i8* %44, i64 1, !dbg !2848
  %45 = load i8, i8* %arrayidx50, align 1, !dbg !2848
  %conv51 = sext i8 %45 to i32, !dbg !2848
  %cmp52 = icmp eq i32 %conv51, 10, !dbg !2851
  br i1 %cmp52, label %if.then54, label %if.else58, !dbg !2852

if.then54:                                        ; preds = %if.then49
  %46 = load i64, i64* %total_size, align 8, !dbg !2853
  %sub = sub nsw i64 %46, 2, !dbg !2853
  store i64 %sub, i64* %total_size, align 8, !dbg !2853
  %47 = load i64, i64* %total_size, align 8, !dbg !2855
  %48 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !2856
  %line55 = getelementptr inbounds %struct.mtree, %struct.mtree* %48, i32 0, i32 0, !dbg !2857
  %s56 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %line55, i32 0, i32 0, !dbg !2858
  %49 = load i8*, i8** %s56, align 8, !dbg !2858
  %arrayidx57 = getelementptr inbounds i8, i8* %49, i64 %47, !dbg !2856
  store i8 0, i8* %arrayidx57, align 1, !dbg !2859
  br label %for.end, !dbg !2860

if.else58:                                        ; preds = %if.then49
  %50 = load i8*, i8** %u, align 8, !dbg !2861
  %arrayidx59 = getelementptr inbounds i8, i8* %50, i64 1, !dbg !2861
  %51 = load i8, i8* %arrayidx59, align 1, !dbg !2861
  %conv60 = sext i8 %51 to i32, !dbg !2861
  %cmp61 = icmp ne i32 %conv60, 0, !dbg !2863
  br i1 %cmp61, label %if.then63, label %if.end64, !dbg !2864

if.then63:                                        ; preds = %if.else58
  %52 = load i8*, i8** %u, align 8, !dbg !2865
  %incdec.ptr = getelementptr inbounds i8, i8* %52, i32 1, !dbg !2865
  store i8* %incdec.ptr, i8** %u, align 8, !dbg !2865
  br label %if.end64, !dbg !2867

if.end64:                                         ; preds = %if.then63, %if.else58
  br label %if.end65

if.end65:                                         ; preds = %if.end64
  br label %if.end66, !dbg !2868

if.end66:                                         ; preds = %if.end65, %if.else44
  br label %if.end67

if.end67:                                         ; preds = %if.end66, %if.end43
  br label %if.end68

if.end68:                                         ; preds = %if.end67
  br label %for.inc, !dbg !2869

for.inc:                                          ; preds = %if.end68
  %53 = load i8*, i8** %u, align 8, !dbg !2870
  %incdec.ptr69 = getelementptr inbounds i8, i8* %53, i32 1, !dbg !2870
  store i8* %incdec.ptr69, i8** %u, align 8, !dbg !2870
  br label %for.cond28, !dbg !2872

for.end:                                          ; preds = %if.then54, %if.then42, %for.cond28
  %54 = load i8*, i8** %u, align 8, !dbg !2873
  %55 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !2874
  %line70 = getelementptr inbounds %struct.mtree, %struct.mtree* %55, i32 0, i32 0, !dbg !2875
  %s71 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %line70, i32 0, i32 0, !dbg !2876
  %56 = load i8*, i8** %s71, align 8, !dbg !2876
  %sub.ptr.lhs.cast72 = ptrtoint i8* %54 to i64, !dbg !2877
  %sub.ptr.rhs.cast73 = ptrtoint i8* %56 to i64, !dbg !2877
  %sub.ptr.sub74 = sub i64 %sub.ptr.lhs.cast72, %sub.ptr.rhs.cast73, !dbg !2877
  store i64 %sub.ptr.sub74, i64* %find_off, align 8, !dbg !2878
  br label %for.cond, !dbg !2879

return:                                           ; preds = %if.then32, %if.then17, %if.then11, %if.then2, %if.then
  %57 = load i64, i64* %retval, align 8, !dbg !2881
  ret i64 %57, !dbg !2881
}

; Function Attrs: nounwind uwtable
define internal i32 @process_add_entry(%struct.archive_read* %a, %struct.mtree* %mtree, %struct.mtree_option** %global, i8* %line, i64 %line_len, %struct.mtree_entry** %last_entry, i32 %is_form_d) #0 !dbg !382 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %mtree.addr = alloca %struct.mtree*, align 8
  %global.addr = alloca %struct.mtree_option**, align 8
  %line.addr = alloca i8*, align 8
  %line_len.addr = alloca i64, align 8
  %last_entry.addr = alloca %struct.mtree_entry**, align 8
  %is_form_d.addr = alloca i32, align 4
  %entry1 = alloca %struct.mtree_entry*, align 8
  %ht_iter = alloca %struct.mtree_entry*, align 8
  %iter = alloca %struct.mtree_option*, align 8
  %next = alloca i8*, align 8
  %eq = alloca i8*, align 8
  %name = alloca i8*, align 8
  %end = alloca i8*, align 8
  %name_len = alloca i64, align 8
  %len = alloca i64, align 8
  %r = alloca i32, align 4
  %i = alloca i32, align 4
  %ht_idx = alloca i32, align 4
  %last_character = alloca i8, align 1
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !2882, metadata !460), !dbg !2883
  store %struct.mtree* %mtree, %struct.mtree** %mtree.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree** %mtree.addr, metadata !2884, metadata !460), !dbg !2885
  store %struct.mtree_option** %global, %struct.mtree_option*** %global.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree_option*** %global.addr, metadata !2886, metadata !460), !dbg !2887
  store i8* %line, i8** %line.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %line.addr, metadata !2888, metadata !460), !dbg !2889
  store i64 %line_len, i64* %line_len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %line_len.addr, metadata !2890, metadata !460), !dbg !2891
  store %struct.mtree_entry** %last_entry, %struct.mtree_entry*** %last_entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree_entry*** %last_entry.addr, metadata !2892, metadata !460), !dbg !2893
  store i32 %is_form_d, i32* %is_form_d.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %is_form_d.addr, metadata !2894, metadata !460), !dbg !2895
  call void @llvm.dbg.declare(metadata %struct.mtree_entry** %entry1, metadata !2896, metadata !460), !dbg !2897
  call void @llvm.dbg.declare(metadata %struct.mtree_entry** %ht_iter, metadata !2898, metadata !460), !dbg !2899
  call void @llvm.dbg.declare(metadata %struct.mtree_option** %iter, metadata !2900, metadata !460), !dbg !2901
  call void @llvm.dbg.declare(metadata i8** %next, metadata !2902, metadata !460), !dbg !2903
  call void @llvm.dbg.declare(metadata i8** %eq, metadata !2904, metadata !460), !dbg !2905
  call void @llvm.dbg.declare(metadata i8** %name, metadata !2906, metadata !460), !dbg !2907
  call void @llvm.dbg.declare(metadata i8** %end, metadata !2908, metadata !460), !dbg !2909
  call void @llvm.dbg.declare(metadata i64* %name_len, metadata !2910, metadata !460), !dbg !2911
  call void @llvm.dbg.declare(metadata i64* %len, metadata !2912, metadata !460), !dbg !2913
  call void @llvm.dbg.declare(metadata i32* %r, metadata !2914, metadata !460), !dbg !2915
  call void @llvm.dbg.declare(metadata i32* %i, metadata !2916, metadata !460), !dbg !2917
  call void @llvm.dbg.declare(metadata i32* %ht_idx, metadata !2918, metadata !460), !dbg !2919
  %call = call noalias i8* @malloc(i64 40) #7, !dbg !2920
  %0 = bitcast i8* %call to %struct.mtree_entry*, !dbg !2920
  store %struct.mtree_entry* %0, %struct.mtree_entry** %entry1, align 8, !dbg !2922
  %cmp = icmp eq %struct.mtree_entry* %0, null, !dbg !2923
  br i1 %cmp, label %if.then, label %if.end, !dbg !2924

if.then:                                          ; preds = %entry
  %1 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2925
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %1, i32 0, i32 0, !dbg !2927
  %call2 = call i32* @__errno_location() #1, !dbg !2928
  %2 = load i32, i32* %call2, align 4, !dbg !2928
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 %2, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.45, i32 0, i32 0)), !dbg !2929
  store i32 -30, i32* %retval, align 4, !dbg !2931
  br label %return, !dbg !2931

if.end:                                           ; preds = %entry
  %3 = load %struct.mtree_entry*, %struct.mtree_entry** %entry1, align 8, !dbg !2932
  %next3 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %3, i32 0, i32 0, !dbg !2933
  store %struct.mtree_entry* null, %struct.mtree_entry** %next3, align 8, !dbg !2934
  %4 = load %struct.mtree_entry*, %struct.mtree_entry** %entry1, align 8, !dbg !2935
  %options = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %4, i32 0, i32 1, !dbg !2936
  store %struct.mtree_option* null, %struct.mtree_option** %options, align 8, !dbg !2937
  %5 = load %struct.mtree_entry*, %struct.mtree_entry** %entry1, align 8, !dbg !2938
  %name4 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %5, i32 0, i32 2, !dbg !2939
  store i8* null, i8** %name4, align 8, !dbg !2940
  %6 = load %struct.mtree_entry*, %struct.mtree_entry** %entry1, align 8, !dbg !2941
  %used = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %6, i32 0, i32 4, !dbg !2942
  store i8 0, i8* %used, align 1, !dbg !2943
  %7 = load %struct.mtree_entry*, %struct.mtree_entry** %entry1, align 8, !dbg !2944
  %full = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %7, i32 0, i32 3, !dbg !2945
  store i8 0, i8* %full, align 8, !dbg !2946
  %8 = load %struct.mtree_entry*, %struct.mtree_entry** %entry1, align 8, !dbg !2947
  %name_hash = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %8, i32 0, i32 5, !dbg !2948
  store i32 0, i32* %name_hash, align 4, !dbg !2949
  %9 = load %struct.mtree_entry*, %struct.mtree_entry** %entry1, align 8, !dbg !2950
  %hashtable_next = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %9, i32 0, i32 6, !dbg !2951
  store %struct.mtree_entry* null, %struct.mtree_entry** %hashtable_next, align 8, !dbg !2952
  %10 = load %struct.mtree_entry**, %struct.mtree_entry*** %last_entry.addr, align 8, !dbg !2953
  %11 = load %struct.mtree_entry*, %struct.mtree_entry** %10, align 8, !dbg !2955
  %cmp5 = icmp eq %struct.mtree_entry* %11, null, !dbg !2956
  br i1 %cmp5, label %if.then6, label %if.else, !dbg !2957

if.then6:                                         ; preds = %if.end
  %12 = load %struct.mtree_entry*, %struct.mtree_entry** %entry1, align 8, !dbg !2958
  %13 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !2959
  %entries = getelementptr inbounds %struct.mtree, %struct.mtree* %13, i32 0, i32 7, !dbg !2960
  store %struct.mtree_entry* %12, %struct.mtree_entry** %entries, align 8, !dbg !2961
  br label %if.end8, !dbg !2959

if.else:                                          ; preds = %if.end
  %14 = load %struct.mtree_entry*, %struct.mtree_entry** %entry1, align 8, !dbg !2962
  %15 = load %struct.mtree_entry**, %struct.mtree_entry*** %last_entry.addr, align 8, !dbg !2963
  %16 = load %struct.mtree_entry*, %struct.mtree_entry** %15, align 8, !dbg !2964
  %next7 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %16, i32 0, i32 0, !dbg !2965
  store %struct.mtree_entry* %14, %struct.mtree_entry** %next7, align 8, !dbg !2966
  br label %if.end8

if.end8:                                          ; preds = %if.else, %if.then6
  %17 = load %struct.mtree_entry*, %struct.mtree_entry** %entry1, align 8, !dbg !2967
  %18 = load %struct.mtree_entry**, %struct.mtree_entry*** %last_entry.addr, align 8, !dbg !2968
  store %struct.mtree_entry* %17, %struct.mtree_entry** %18, align 8, !dbg !2969
  %19 = load i32, i32* %is_form_d.addr, align 4, !dbg !2970
  %tobool = icmp ne i32 %19, 0, !dbg !2970
  br i1 %tobool, label %if.then9, label %if.else56, !dbg !2972

if.then9:                                         ; preds = %if.end8
  br label %while.cond, !dbg !2973

while.cond:                                       ; preds = %if.end26, %if.then9
  %20 = load i64, i64* %line_len.addr, align 8, !dbg !2975
  %cmp10 = icmp sgt i64 %20, 0, !dbg !2977
  br i1 %cmp10, label %while.body, label %while.end, !dbg !2978

while.body:                                       ; preds = %while.cond
  call void @llvm.dbg.declare(metadata i8* %last_character, metadata !2979, metadata !460), !dbg !2981
  %21 = load i64, i64* %line_len.addr, align 8, !dbg !2982
  %sub = sub nsw i64 %21, 1, !dbg !2983
  %22 = load i8*, i8** %line.addr, align 8, !dbg !2984
  %arrayidx = getelementptr inbounds i8, i8* %22, i64 %sub, !dbg !2984
  %23 = load i8, i8* %arrayidx, align 1, !dbg !2984
  store i8 %23, i8* %last_character, align 1, !dbg !2981
  %24 = load i8, i8* %last_character, align 1, !dbg !2985
  %conv = sext i8 %24 to i32, !dbg !2985
  %cmp11 = icmp eq i32 %conv, 13, !dbg !2987
  br i1 %cmp11, label %if.then24, label %lor.lhs.false, !dbg !2988

lor.lhs.false:                                    ; preds = %while.body
  %25 = load i8, i8* %last_character, align 1, !dbg !2989
  %conv13 = sext i8 %25 to i32, !dbg !2989
  %cmp14 = icmp eq i32 %conv13, 10, !dbg !2991
  br i1 %cmp14, label %if.then24, label %lor.lhs.false16, !dbg !2992

lor.lhs.false16:                                  ; preds = %lor.lhs.false
  %26 = load i8, i8* %last_character, align 1, !dbg !2993
  %conv17 = sext i8 %26 to i32, !dbg !2993
  %cmp18 = icmp eq i32 %conv17, 9, !dbg !2994
  br i1 %cmp18, label %if.then24, label %lor.lhs.false20, !dbg !2995

lor.lhs.false20:                                  ; preds = %lor.lhs.false16
  %27 = load i8, i8* %last_character, align 1, !dbg !2996
  %conv21 = sext i8 %27 to i32, !dbg !2996
  %cmp22 = icmp eq i32 %conv21, 32, !dbg !2997
  br i1 %cmp22, label %if.then24, label %if.else25, !dbg !2998

if.then24:                                        ; preds = %lor.lhs.false20, %lor.lhs.false16, %lor.lhs.false, %while.body
  %28 = load i64, i64* %line_len.addr, align 8, !dbg !3000
  %dec = add nsw i64 %28, -1, !dbg !3000
  store i64 %dec, i64* %line_len.addr, align 8, !dbg !3000
  br label %if.end26, !dbg !3002

if.else25:                                        ; preds = %lor.lhs.false20
  br label %while.end, !dbg !3003

if.end26:                                         ; preds = %if.then24
  br label %while.cond, !dbg !3005

while.end:                                        ; preds = %if.else25, %while.cond
  %29 = load i8*, i8** %line.addr, align 8, !dbg !3007
  store i8* %29, i8** %name, align 8, !dbg !3008
  store i32 0, i32* %i, align 4, !dbg !3009
  br label %for.cond, !dbg !3011

for.cond:                                         ; preds = %for.inc, %while.end
  %30 = load i32, i32* %i, align 4, !dbg !3012
  %conv27 = sext i32 %30 to i64, !dbg !3012
  %31 = load i64, i64* %line_len.addr, align 8, !dbg !3015
  %cmp28 = icmp slt i64 %conv27, %31, !dbg !3016
  br i1 %cmp28, label %for.body, label %for.end, !dbg !3017

for.body:                                         ; preds = %for.cond
  %32 = load i32, i32* %i, align 4, !dbg !3018
  %idxprom = sext i32 %32 to i64, !dbg !3021
  %33 = load i8*, i8** %line.addr, align 8, !dbg !3021
  %arrayidx30 = getelementptr inbounds i8, i8* %33, i64 %idxprom, !dbg !3021
  %34 = load i8, i8* %arrayidx30, align 1, !dbg !3021
  %conv31 = sext i8 %34 to i32, !dbg !3021
  %cmp32 = icmp eq i32 %conv31, 13, !dbg !3022
  br i1 %cmp32, label %if.then52, label %lor.lhs.false34, !dbg !3023

lor.lhs.false34:                                  ; preds = %for.body
  %35 = load i32, i32* %i, align 4, !dbg !3024
  %idxprom35 = sext i32 %35 to i64, !dbg !3026
  %36 = load i8*, i8** %line.addr, align 8, !dbg !3026
  %arrayidx36 = getelementptr inbounds i8, i8* %36, i64 %idxprom35, !dbg !3026
  %37 = load i8, i8* %arrayidx36, align 1, !dbg !3026
  %conv37 = sext i8 %37 to i32, !dbg !3026
  %cmp38 = icmp eq i32 %conv37, 10, !dbg !3027
  br i1 %cmp38, label %if.then52, label %lor.lhs.false40, !dbg !3028

lor.lhs.false40:                                  ; preds = %lor.lhs.false34
  %38 = load i32, i32* %i, align 4, !dbg !3029
  %idxprom41 = sext i32 %38 to i64, !dbg !3030
  %39 = load i8*, i8** %line.addr, align 8, !dbg !3030
  %arrayidx42 = getelementptr inbounds i8, i8* %39, i64 %idxprom41, !dbg !3030
  %40 = load i8, i8* %arrayidx42, align 1, !dbg !3030
  %conv43 = sext i8 %40 to i32, !dbg !3030
  %cmp44 = icmp eq i32 %conv43, 9, !dbg !3031
  br i1 %cmp44, label %if.then52, label %lor.lhs.false46, !dbg !3032

lor.lhs.false46:                                  ; preds = %lor.lhs.false40
  %41 = load i32, i32* %i, align 4, !dbg !3033
  %idxprom47 = sext i32 %41 to i64, !dbg !3034
  %42 = load i8*, i8** %line.addr, align 8, !dbg !3034
  %arrayidx48 = getelementptr inbounds i8, i8* %42, i64 %idxprom47, !dbg !3034
  %43 = load i8, i8* %arrayidx48, align 1, !dbg !3034
  %conv49 = sext i8 %43 to i32, !dbg !3034
  %cmp50 = icmp eq i32 %conv49, 32, !dbg !3035
  br i1 %cmp50, label %if.then52, label %if.end54, !dbg !3036

if.then52:                                        ; preds = %lor.lhs.false46, %lor.lhs.false40, %lor.lhs.false34, %for.body
  %44 = load i8*, i8** %line.addr, align 8, !dbg !3038
  %45 = load i32, i32* %i, align 4, !dbg !3040
  %idx.ext = sext i32 %45 to i64, !dbg !3041
  %add.ptr = getelementptr inbounds i8, i8* %44, i64 %idx.ext, !dbg !3041
  %add.ptr53 = getelementptr inbounds i8, i8* %add.ptr, i64 1, !dbg !3042
  store i8* %add.ptr53, i8** %name, align 8, !dbg !3043
  br label %if.end54, !dbg !3044

if.end54:                                         ; preds = %if.then52, %lor.lhs.false46
  br label %for.inc, !dbg !3045

for.inc:                                          ; preds = %if.end54
  %46 = load i32, i32* %i, align 4, !dbg !3046
  %inc = add nsw i32 %46, 1, !dbg !3046
  store i32 %inc, i32* %i, align 4, !dbg !3046
  br label %for.cond, !dbg !3048

for.end:                                          ; preds = %for.cond
  %47 = load i8*, i8** %line.addr, align 8, !dbg !3049
  %48 = load i64, i64* %line_len.addr, align 8, !dbg !3050
  %add.ptr55 = getelementptr inbounds i8, i8* %47, i64 %48, !dbg !3051
  %49 = load i8*, i8** %name, align 8, !dbg !3052
  %sub.ptr.lhs.cast = ptrtoint i8* %add.ptr55 to i64, !dbg !3053
  %sub.ptr.rhs.cast = ptrtoint i8* %49 to i64, !dbg !3053
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !3053
  store i64 %sub.ptr.sub, i64* %name_len, align 8, !dbg !3054
  %50 = load i8*, i8** %name, align 8, !dbg !3055
  store i8* %50, i8** %end, align 8, !dbg !3056
  br label %if.end60, !dbg !3057

if.else56:                                        ; preds = %if.end8
  %51 = load i8*, i8** %line.addr, align 8, !dbg !3058
  %call57 = call i64 @strcspn(i8* %51, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.46, i32 0, i32 0)) #8, !dbg !3060
  store i64 %call57, i64* %name_len, align 8, !dbg !3061
  %52 = load i8*, i8** %line.addr, align 8, !dbg !3062
  store i8* %52, i8** %name, align 8, !dbg !3063
  %53 = load i64, i64* %name_len, align 8, !dbg !3064
  %54 = load i8*, i8** %line.addr, align 8, !dbg !3065
  %add.ptr58 = getelementptr inbounds i8, i8* %54, i64 %53, !dbg !3065
  store i8* %add.ptr58, i8** %line.addr, align 8, !dbg !3065
  %55 = load i8*, i8** %line.addr, align 8, !dbg !3066
  %56 = load i64, i64* %line_len.addr, align 8, !dbg !3067
  %add.ptr59 = getelementptr inbounds i8, i8* %55, i64 %56, !dbg !3068
  store i8* %add.ptr59, i8** %end, align 8, !dbg !3069
  br label %if.end60

if.end60:                                         ; preds = %if.else56, %for.end
  %57 = load i64, i64* %name_len, align 8, !dbg !3070
  %add = add i64 %57, 1, !dbg !3072
  %call61 = call noalias i8* @malloc(i64 %add) #7, !dbg !3073
  %58 = load %struct.mtree_entry*, %struct.mtree_entry** %entry1, align 8, !dbg !3074
  %name62 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %58, i32 0, i32 2, !dbg !3075
  store i8* %call61, i8** %name62, align 8, !dbg !3076
  %cmp63 = icmp eq i8* %call61, null, !dbg !3077
  br i1 %cmp63, label %if.then65, label %if.end68, !dbg !3078

if.then65:                                        ; preds = %if.end60
  %59 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3079
  %archive66 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %59, i32 0, i32 0, !dbg !3081
  %call67 = call i32* @__errno_location() #1, !dbg !3082
  %60 = load i32, i32* %call67, align 4, !dbg !3082
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive66, i32 %60, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.45, i32 0, i32 0)), !dbg !3083
  store i32 -30, i32* %retval, align 4, !dbg !3085
  br label %return, !dbg !3085

if.end68:                                         ; preds = %if.end60
  %61 = load %struct.mtree_entry*, %struct.mtree_entry** %entry1, align 8, !dbg !3086
  %name69 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %61, i32 0, i32 2, !dbg !3087
  %62 = load i8*, i8** %name69, align 8, !dbg !3087
  %63 = load i8*, i8** %name, align 8, !dbg !3088
  %64 = load i64, i64* %name_len, align 8, !dbg !3089
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %62, i8* %63, i64 %64, i32 1, i1 false), !dbg !3090
  %65 = load i64, i64* %name_len, align 8, !dbg !3091
  %66 = load %struct.mtree_entry*, %struct.mtree_entry** %entry1, align 8, !dbg !3092
  %name70 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %66, i32 0, i32 2, !dbg !3093
  %67 = load i8*, i8** %name70, align 8, !dbg !3093
  %arrayidx71 = getelementptr inbounds i8, i8* %67, i64 %65, !dbg !3092
  store i8 0, i8* %arrayidx71, align 1, !dbg !3094
  %68 = load %struct.mtree_entry*, %struct.mtree_entry** %entry1, align 8, !dbg !3095
  %name72 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %68, i32 0, i32 2, !dbg !3096
  %69 = load i8*, i8** %name72, align 8, !dbg !3096
  %70 = load %struct.mtree_entry*, %struct.mtree_entry** %entry1, align 8, !dbg !3097
  call void @parse_escapes(i8* %69, %struct.mtree_entry* %70), !dbg !3098
  %71 = load %struct.mtree_entry*, %struct.mtree_entry** %entry1, align 8, !dbg !3099
  %name73 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %71, i32 0, i32 2, !dbg !3100
  %72 = load i8*, i8** %name73, align 8, !dbg !3100
  %call74 = call i32 @hash(i8* %72), !dbg !3101
  %73 = load %struct.mtree_entry*, %struct.mtree_entry** %entry1, align 8, !dbg !3102
  %name_hash75 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %73, i32 0, i32 5, !dbg !3103
  store i32 %call74, i32* %name_hash75, align 4, !dbg !3104
  %74 = load %struct.mtree_entry*, %struct.mtree_entry** %entry1, align 8, !dbg !3105
  %name_hash76 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %74, i32 0, i32 5, !dbg !3106
  %75 = load i32, i32* %name_hash76, align 4, !dbg !3106
  %rem = urem i32 %75, 1024, !dbg !3107
  store i32 %rem, i32* %ht_idx, align 4, !dbg !3108
  %76 = load i32, i32* %ht_idx, align 4, !dbg !3109
  %idxprom77 = zext i32 %76 to i64, !dbg !3111
  %77 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !3111
  %entry_hashtable = getelementptr inbounds %struct.mtree, %struct.mtree* %77, i32 0, i32 9, !dbg !3112
  %arrayidx78 = getelementptr inbounds [1024 x %struct.mtree_entry*], [1024 x %struct.mtree_entry*]* %entry_hashtable, i64 0, i64 %idxprom77, !dbg !3111
  %78 = load %struct.mtree_entry*, %struct.mtree_entry** %arrayidx78, align 8, !dbg !3111
  store %struct.mtree_entry* %78, %struct.mtree_entry** %ht_iter, align 8, !dbg !3113
  %cmp79 = icmp ne %struct.mtree_entry* %78, null, !dbg !3114
  br i1 %cmp79, label %if.then81, label %if.else89, !dbg !3115

if.then81:                                        ; preds = %if.end68
  br label %while.cond82, !dbg !3116

while.cond82:                                     ; preds = %while.body85, %if.then81
  %79 = load %struct.mtree_entry*, %struct.mtree_entry** %ht_iter, align 8, !dbg !3118
  %hashtable_next83 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %79, i32 0, i32 6, !dbg !3120
  %80 = load %struct.mtree_entry*, %struct.mtree_entry** %hashtable_next83, align 8, !dbg !3120
  %tobool84 = icmp ne %struct.mtree_entry* %80, null, !dbg !3121
  br i1 %tobool84, label %while.body85, label %while.end87, !dbg !3121

while.body85:                                     ; preds = %while.cond82
  %81 = load %struct.mtree_entry*, %struct.mtree_entry** %ht_iter, align 8, !dbg !3122
  %hashtable_next86 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %81, i32 0, i32 6, !dbg !3123
  %82 = load %struct.mtree_entry*, %struct.mtree_entry** %hashtable_next86, align 8, !dbg !3123
  store %struct.mtree_entry* %82, %struct.mtree_entry** %ht_iter, align 8, !dbg !3124
  br label %while.cond82, !dbg !3125

while.end87:                                      ; preds = %while.cond82
  %83 = load %struct.mtree_entry*, %struct.mtree_entry** %entry1, align 8, !dbg !3127
  %84 = load %struct.mtree_entry*, %struct.mtree_entry** %ht_iter, align 8, !dbg !3128
  %hashtable_next88 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %84, i32 0, i32 6, !dbg !3129
  store %struct.mtree_entry* %83, %struct.mtree_entry** %hashtable_next88, align 8, !dbg !3130
  br label %if.end93, !dbg !3131

if.else89:                                        ; preds = %if.end68
  %85 = load %struct.mtree_entry*, %struct.mtree_entry** %entry1, align 8, !dbg !3132
  %86 = load i32, i32* %ht_idx, align 4, !dbg !3134
  %idxprom90 = zext i32 %86 to i64, !dbg !3135
  %87 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !3135
  %entry_hashtable91 = getelementptr inbounds %struct.mtree, %struct.mtree* %87, i32 0, i32 9, !dbg !3136
  %arrayidx92 = getelementptr inbounds [1024 x %struct.mtree_entry*], [1024 x %struct.mtree_entry*]* %entry_hashtable91, i64 0, i64 %idxprom90, !dbg !3135
  store %struct.mtree_entry* %85, %struct.mtree_entry** %arrayidx92, align 8, !dbg !3137
  br label %if.end93

if.end93:                                         ; preds = %if.else89, %while.end87
  %88 = load %struct.mtree_option**, %struct.mtree_option*** %global.addr, align 8, !dbg !3138
  %89 = load %struct.mtree_option*, %struct.mtree_option** %88, align 8, !dbg !3140
  store %struct.mtree_option* %89, %struct.mtree_option** %iter, align 8, !dbg !3141
  br label %for.cond94, !dbg !3142

for.cond94:                                       ; preds = %for.inc106, %if.end93
  %90 = load %struct.mtree_option*, %struct.mtree_option** %iter, align 8, !dbg !3143
  %cmp95 = icmp ne %struct.mtree_option* %90, null, !dbg !3146
  br i1 %cmp95, label %for.body97, label %for.end108, !dbg !3147

for.body97:                                       ; preds = %for.cond94
  %91 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3148
  %92 = load %struct.mtree_entry*, %struct.mtree_entry** %entry1, align 8, !dbg !3150
  %options98 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %92, i32 0, i32 1, !dbg !3151
  %93 = load %struct.mtree_option*, %struct.mtree_option** %iter, align 8, !dbg !3152
  %value = getelementptr inbounds %struct.mtree_option, %struct.mtree_option* %93, i32 0, i32 1, !dbg !3153
  %94 = load i8*, i8** %value, align 8, !dbg !3153
  %95 = load %struct.mtree_option*, %struct.mtree_option** %iter, align 8, !dbg !3154
  %value99 = getelementptr inbounds %struct.mtree_option, %struct.mtree_option* %95, i32 0, i32 1, !dbg !3155
  %96 = load i8*, i8** %value99, align 8, !dbg !3155
  %call100 = call i64 @strlen(i8* %96) #8, !dbg !3156
  %call101 = call i32 @add_option(%struct.archive_read* %91, %struct.mtree_option** %options98, i8* %94, i64 %call100), !dbg !3157
  store i32 %call101, i32* %r, align 4, !dbg !3158
  %97 = load i32, i32* %r, align 4, !dbg !3159
  %cmp102 = icmp ne i32 %97, 0, !dbg !3161
  br i1 %cmp102, label %if.then104, label %if.end105, !dbg !3162

if.then104:                                       ; preds = %for.body97
  %98 = load i32, i32* %r, align 4, !dbg !3163
  store i32 %98, i32* %retval, align 4, !dbg !3164
  br label %return, !dbg !3164

if.end105:                                        ; preds = %for.body97
  br label %for.inc106, !dbg !3165

for.inc106:                                       ; preds = %if.end105
  %99 = load %struct.mtree_option*, %struct.mtree_option** %iter, align 8, !dbg !3166
  %next107 = getelementptr inbounds %struct.mtree_option, %struct.mtree_option* %99, i32 0, i32 0, !dbg !3168
  %100 = load %struct.mtree_option*, %struct.mtree_option** %next107, align 8, !dbg !3168
  store %struct.mtree_option* %100, %struct.mtree_option** %iter, align 8, !dbg !3169
  br label %for.cond94, !dbg !3170

for.end108:                                       ; preds = %for.cond94
  br label %for.cond109, !dbg !3171

for.cond109:                                      ; preds = %if.end147, %for.end108
  %101 = load i8*, i8** %line.addr, align 8, !dbg !3172
  %102 = load i8*, i8** %line.addr, align 8, !dbg !3176
  %call110 = call i64 @strspn(i8* %102, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.46, i32 0, i32 0)) #8, !dbg !3177
  %add.ptr111 = getelementptr inbounds i8, i8* %101, i64 %call110, !dbg !3178
  store i8* %add.ptr111, i8** %next, align 8, !dbg !3179
  %103 = load i8*, i8** %next, align 8, !dbg !3180
  %104 = load i8, i8* %103, align 1, !dbg !3182
  %conv112 = sext i8 %104 to i32, !dbg !3182
  %cmp113 = icmp eq i32 %conv112, 0, !dbg !3183
  br i1 %cmp113, label %if.then115, label %if.end116, !dbg !3184

if.then115:                                       ; preds = %for.cond109
  store i32 0, i32* %retval, align 4, !dbg !3185
  br label %return, !dbg !3185

if.end116:                                        ; preds = %for.cond109
  %105 = load i8*, i8** %next, align 8, !dbg !3186
  %106 = load i8*, i8** %end, align 8, !dbg !3188
  %cmp117 = icmp uge i8* %105, %106, !dbg !3189
  br i1 %cmp117, label %if.then119, label %if.end120, !dbg !3190

if.then119:                                       ; preds = %if.end116
  store i32 0, i32* %retval, align 4, !dbg !3191
  br label %return, !dbg !3191

if.end120:                                        ; preds = %if.end116
  %107 = load i8*, i8** %next, align 8, !dbg !3192
  store i8* %107, i8** %line.addr, align 8, !dbg !3193
  %108 = load i8*, i8** %line.addr, align 8, !dbg !3194
  %109 = load i8*, i8** %line.addr, align 8, !dbg !3195
  %call121 = call i64 @strcspn(i8* %109, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.46, i32 0, i32 0)) #8, !dbg !3196
  %add.ptr122 = getelementptr inbounds i8, i8* %108, i64 %call121, !dbg !3197
  store i8* %add.ptr122, i8** %next, align 8, !dbg !3198
  %110 = load i8*, i8** %line.addr, align 8, !dbg !3199
  %call123 = call i8* @strchr(i8* %110, i32 61) #8, !dbg !3200
  store i8* %call123, i8** %eq, align 8, !dbg !3201
  %111 = load i8*, i8** %eq, align 8, !dbg !3202
  %cmp124 = icmp eq i8* %111, null, !dbg !3204
  br i1 %cmp124, label %if.then129, label %lor.lhs.false126, !dbg !3205

lor.lhs.false126:                                 ; preds = %if.end120
  %112 = load i8*, i8** %eq, align 8, !dbg !3206
  %113 = load i8*, i8** %next, align 8, !dbg !3208
  %cmp127 = icmp ugt i8* %112, %113, !dbg !3209
  br i1 %cmp127, label %if.then129, label %if.else133, !dbg !3210

if.then129:                                       ; preds = %lor.lhs.false126, %if.end120
  %114 = load i8*, i8** %next, align 8, !dbg !3211
  %115 = load i8*, i8** %line.addr, align 8, !dbg !3212
  %sub.ptr.lhs.cast130 = ptrtoint i8* %114 to i64, !dbg !3213
  %sub.ptr.rhs.cast131 = ptrtoint i8* %115 to i64, !dbg !3213
  %sub.ptr.sub132 = sub i64 %sub.ptr.lhs.cast130, %sub.ptr.rhs.cast131, !dbg !3213
  store i64 %sub.ptr.sub132, i64* %len, align 8, !dbg !3214
  br label %if.end137, !dbg !3215

if.else133:                                       ; preds = %lor.lhs.false126
  %116 = load i8*, i8** %eq, align 8, !dbg !3216
  %117 = load i8*, i8** %line.addr, align 8, !dbg !3217
  %sub.ptr.lhs.cast134 = ptrtoint i8* %116 to i64, !dbg !3218
  %sub.ptr.rhs.cast135 = ptrtoint i8* %117 to i64, !dbg !3218
  %sub.ptr.sub136 = sub i64 %sub.ptr.lhs.cast134, %sub.ptr.rhs.cast135, !dbg !3218
  store i64 %sub.ptr.sub136, i64* %len, align 8, !dbg !3219
  br label %if.end137

if.end137:                                        ; preds = %if.else133, %if.then129
  %118 = load %struct.mtree_entry*, %struct.mtree_entry** %entry1, align 8, !dbg !3220
  %options138 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %118, i32 0, i32 1, !dbg !3221
  %119 = load i8*, i8** %line.addr, align 8, !dbg !3222
  %120 = load i64, i64* %len, align 8, !dbg !3223
  call void @remove_option(%struct.mtree_option** %options138, i8* %119, i64 %120), !dbg !3224
  %121 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3225
  %122 = load %struct.mtree_entry*, %struct.mtree_entry** %entry1, align 8, !dbg !3226
  %options139 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %122, i32 0, i32 1, !dbg !3227
  %123 = load i8*, i8** %line.addr, align 8, !dbg !3228
  %124 = load i8*, i8** %next, align 8, !dbg !3229
  %125 = load i8*, i8** %line.addr, align 8, !dbg !3230
  %sub.ptr.lhs.cast140 = ptrtoint i8* %124 to i64, !dbg !3231
  %sub.ptr.rhs.cast141 = ptrtoint i8* %125 to i64, !dbg !3231
  %sub.ptr.sub142 = sub i64 %sub.ptr.lhs.cast140, %sub.ptr.rhs.cast141, !dbg !3231
  %call143 = call i32 @add_option(%struct.archive_read* %121, %struct.mtree_option** %options139, i8* %123, i64 %sub.ptr.sub142), !dbg !3232
  store i32 %call143, i32* %r, align 4, !dbg !3233
  %126 = load i32, i32* %r, align 4, !dbg !3234
  %cmp144 = icmp ne i32 %126, 0, !dbg !3236
  br i1 %cmp144, label %if.then146, label %if.end147, !dbg !3237

if.then146:                                       ; preds = %if.end137
  %127 = load i32, i32* %r, align 4, !dbg !3238
  store i32 %127, i32* %retval, align 4, !dbg !3239
  br label %return, !dbg !3239

if.end147:                                        ; preds = %if.end137
  %128 = load i8*, i8** %next, align 8, !dbg !3240
  store i8* %128, i8** %line.addr, align 8, !dbg !3241
  br label %for.cond109, !dbg !3242

return:                                           ; preds = %if.then146, %if.then119, %if.then115, %if.then104, %if.then65, %if.then
  %129 = load i32, i32* %retval, align 4, !dbg !3244
  ret i32 %129, !dbg !3244
}

; Function Attrs: nounwind uwtable
define internal i32 @process_global_set(%struct.archive_read* %a, %struct.mtree_option** %global, i8* %line) #0 !dbg !399 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %global.addr = alloca %struct.mtree_option**, align 8
  %line.addr = alloca i8*, align 8
  %next = alloca i8*, align 8
  %eq = alloca i8*, align 8
  %len = alloca i64, align 8
  %r = alloca i32, align 4
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !3245, metadata !460), !dbg !3246
  store %struct.mtree_option** %global, %struct.mtree_option*** %global.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree_option*** %global.addr, metadata !3247, metadata !460), !dbg !3248
  store i8* %line, i8** %line.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %line.addr, metadata !3249, metadata !460), !dbg !3250
  call void @llvm.dbg.declare(metadata i8** %next, metadata !3251, metadata !460), !dbg !3252
  call void @llvm.dbg.declare(metadata i8** %eq, metadata !3253, metadata !460), !dbg !3254
  call void @llvm.dbg.declare(metadata i64* %len, metadata !3255, metadata !460), !dbg !3256
  call void @llvm.dbg.declare(metadata i32* %r, metadata !3257, metadata !460), !dbg !3258
  %0 = load i8*, i8** %line.addr, align 8, !dbg !3259
  %add.ptr = getelementptr inbounds i8, i8* %0, i64 4, !dbg !3259
  store i8* %add.ptr, i8** %line.addr, align 8, !dbg !3259
  br label %for.cond, !dbg !3260

for.cond:                                         ; preds = %if.end20, %entry
  %1 = load i8*, i8** %line.addr, align 8, !dbg !3261
  %2 = load i8*, i8** %line.addr, align 8, !dbg !3265
  %call = call i64 @strspn(i8* %2, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.46, i32 0, i32 0)) #8, !dbg !3266
  %add.ptr1 = getelementptr inbounds i8, i8* %1, i64 %call, !dbg !3267
  store i8* %add.ptr1, i8** %next, align 8, !dbg !3268
  %3 = load i8*, i8** %next, align 8, !dbg !3269
  %4 = load i8, i8* %3, align 1, !dbg !3271
  %conv = sext i8 %4 to i32, !dbg !3271
  %cmp = icmp eq i32 %conv, 0, !dbg !3272
  br i1 %cmp, label %if.then, label %if.end, !dbg !3273

if.then:                                          ; preds = %for.cond
  store i32 0, i32* %retval, align 4, !dbg !3274
  br label %return, !dbg !3274

if.end:                                           ; preds = %for.cond
  %5 = load i8*, i8** %next, align 8, !dbg !3275
  store i8* %5, i8** %line.addr, align 8, !dbg !3276
  %6 = load i8*, i8** %line.addr, align 8, !dbg !3277
  %7 = load i8*, i8** %line.addr, align 8, !dbg !3278
  %call3 = call i64 @strcspn(i8* %7, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.46, i32 0, i32 0)) #8, !dbg !3279
  %add.ptr4 = getelementptr inbounds i8, i8* %6, i64 %call3, !dbg !3280
  store i8* %add.ptr4, i8** %next, align 8, !dbg !3281
  %8 = load i8*, i8** %line.addr, align 8, !dbg !3282
  %call5 = call i8* @strchr(i8* %8, i32 61) #8, !dbg !3283
  store i8* %call5, i8** %eq, align 8, !dbg !3284
  %9 = load i8*, i8** %eq, align 8, !dbg !3285
  %10 = load i8*, i8** %next, align 8, !dbg !3287
  %cmp6 = icmp ugt i8* %9, %10, !dbg !3288
  br i1 %cmp6, label %if.then8, label %if.else, !dbg !3289

if.then8:                                         ; preds = %if.end
  %11 = load i8*, i8** %next, align 8, !dbg !3290
  %12 = load i8*, i8** %line.addr, align 8, !dbg !3291
  %sub.ptr.lhs.cast = ptrtoint i8* %11 to i64, !dbg !3292
  %sub.ptr.rhs.cast = ptrtoint i8* %12 to i64, !dbg !3292
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !3292
  store i64 %sub.ptr.sub, i64* %len, align 8, !dbg !3293
  br label %if.end12, !dbg !3294

if.else:                                          ; preds = %if.end
  %13 = load i8*, i8** %eq, align 8, !dbg !3295
  %14 = load i8*, i8** %line.addr, align 8, !dbg !3296
  %sub.ptr.lhs.cast9 = ptrtoint i8* %13 to i64, !dbg !3297
  %sub.ptr.rhs.cast10 = ptrtoint i8* %14 to i64, !dbg !3297
  %sub.ptr.sub11 = sub i64 %sub.ptr.lhs.cast9, %sub.ptr.rhs.cast10, !dbg !3297
  store i64 %sub.ptr.sub11, i64* %len, align 8, !dbg !3298
  br label %if.end12

if.end12:                                         ; preds = %if.else, %if.then8
  %15 = load %struct.mtree_option**, %struct.mtree_option*** %global.addr, align 8, !dbg !3299
  %16 = load i8*, i8** %line.addr, align 8, !dbg !3300
  %17 = load i64, i64* %len, align 8, !dbg !3301
  call void @remove_option(%struct.mtree_option** %15, i8* %16, i64 %17), !dbg !3302
  %18 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3303
  %19 = load %struct.mtree_option**, %struct.mtree_option*** %global.addr, align 8, !dbg !3304
  %20 = load i8*, i8** %line.addr, align 8, !dbg !3305
  %21 = load i8*, i8** %next, align 8, !dbg !3306
  %22 = load i8*, i8** %line.addr, align 8, !dbg !3307
  %sub.ptr.lhs.cast13 = ptrtoint i8* %21 to i64, !dbg !3308
  %sub.ptr.rhs.cast14 = ptrtoint i8* %22 to i64, !dbg !3308
  %sub.ptr.sub15 = sub i64 %sub.ptr.lhs.cast13, %sub.ptr.rhs.cast14, !dbg !3308
  %call16 = call i32 @add_option(%struct.archive_read* %18, %struct.mtree_option** %19, i8* %20, i64 %sub.ptr.sub15), !dbg !3309
  store i32 %call16, i32* %r, align 4, !dbg !3310
  %23 = load i32, i32* %r, align 4, !dbg !3311
  %cmp17 = icmp ne i32 %23, 0, !dbg !3313
  br i1 %cmp17, label %if.then19, label %if.end20, !dbg !3314

if.then19:                                        ; preds = %if.end12
  %24 = load i32, i32* %r, align 4, !dbg !3315
  store i32 %24, i32* %retval, align 4, !dbg !3316
  br label %return, !dbg !3316

if.end20:                                         ; preds = %if.end12
  %25 = load i8*, i8** %next, align 8, !dbg !3317
  store i8* %25, i8** %line.addr, align 8, !dbg !3318
  br label %for.cond, !dbg !3319

return:                                           ; preds = %if.then19, %if.then
  %26 = load i32, i32* %retval, align 4, !dbg !3321
  ret i32 %26, !dbg !3321
}

; Function Attrs: nounwind uwtable
define internal i32 @process_global_unset(%struct.archive_read* %a, %struct.mtree_option** %global, i8* %line) #0 !dbg !402 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %global.addr = alloca %struct.mtree_option**, align 8
  %line.addr = alloca i8*, align 8
  %next = alloca i8*, align 8
  %len = alloca i64, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !3322, metadata !460), !dbg !3323
  store %struct.mtree_option** %global, %struct.mtree_option*** %global.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree_option*** %global.addr, metadata !3324, metadata !460), !dbg !3325
  store i8* %line, i8** %line.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %line.addr, metadata !3326, metadata !460), !dbg !3327
  call void @llvm.dbg.declare(metadata i8** %next, metadata !3328, metadata !460), !dbg !3329
  call void @llvm.dbg.declare(metadata i64* %len, metadata !3330, metadata !460), !dbg !3331
  %0 = load i8*, i8** %line.addr, align 8, !dbg !3332
  %add.ptr = getelementptr inbounds i8, i8* %0, i64 6, !dbg !3332
  store i8* %add.ptr, i8** %line.addr, align 8, !dbg !3332
  %1 = load i8*, i8** %line.addr, align 8, !dbg !3333
  %call = call i8* @strchr(i8* %1, i32 61) #8, !dbg !3335
  %cmp = icmp ne i8* %call, null, !dbg !3336
  br i1 %cmp, label %if.then, label %if.end, !dbg !3337

if.then:                                          ; preds = %entry
  %2 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3338
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %2, i32 0, i32 0, !dbg !3340
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 -1, i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.48, i32 0, i32 0)), !dbg !3341
  store i32 -30, i32* %retval, align 4, !dbg !3342
  br label %return, !dbg !3342

if.end:                                           ; preds = %entry
  br label %for.cond, !dbg !3343

for.cond:                                         ; preds = %if.end14, %if.end
  %3 = load i8*, i8** %line.addr, align 8, !dbg !3344
  %4 = load i8*, i8** %line.addr, align 8, !dbg !3348
  %call1 = call i64 @strspn(i8* %4, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.46, i32 0, i32 0)) #8, !dbg !3349
  %add.ptr2 = getelementptr inbounds i8, i8* %3, i64 %call1, !dbg !3350
  store i8* %add.ptr2, i8** %next, align 8, !dbg !3351
  %5 = load i8*, i8** %next, align 8, !dbg !3352
  %6 = load i8, i8* %5, align 1, !dbg !3354
  %conv = sext i8 %6 to i32, !dbg !3354
  %cmp3 = icmp eq i32 %conv, 0, !dbg !3355
  br i1 %cmp3, label %if.then5, label %if.end6, !dbg !3356

if.then5:                                         ; preds = %for.cond
  store i32 0, i32* %retval, align 4, !dbg !3357
  br label %return, !dbg !3357

if.end6:                                          ; preds = %for.cond
  %7 = load i8*, i8** %next, align 8, !dbg !3358
  store i8* %7, i8** %line.addr, align 8, !dbg !3359
  %8 = load i8*, i8** %line.addr, align 8, !dbg !3360
  %call7 = call i64 @strcspn(i8* %8, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.46, i32 0, i32 0)) #8, !dbg !3361
  store i64 %call7, i64* %len, align 8, !dbg !3362
  %9 = load i64, i64* %len, align 8, !dbg !3363
  %cmp8 = icmp eq i64 %9, 3, !dbg !3365
  br i1 %cmp8, label %land.lhs.true, label %if.else, !dbg !3366

land.lhs.true:                                    ; preds = %if.end6
  %10 = load i8*, i8** %line.addr, align 8, !dbg !3367
  %call10 = call i32 @strncmp(i8* %10, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.7, i32 0, i32 0), i64 3) #8, !dbg !3369
  %cmp11 = icmp eq i32 %call10, 0, !dbg !3370
  br i1 %cmp11, label %if.then13, label %if.else, !dbg !3371

if.then13:                                        ; preds = %land.lhs.true
  %11 = load %struct.mtree_option**, %struct.mtree_option*** %global.addr, align 8, !dbg !3372
  %12 = load %struct.mtree_option*, %struct.mtree_option** %11, align 8, !dbg !3374
  call void @free_options(%struct.mtree_option* %12), !dbg !3375
  %13 = load %struct.mtree_option**, %struct.mtree_option*** %global.addr, align 8, !dbg !3376
  store %struct.mtree_option* null, %struct.mtree_option** %13, align 8, !dbg !3377
  br label %if.end14, !dbg !3378

if.else:                                          ; preds = %land.lhs.true, %if.end6
  %14 = load %struct.mtree_option**, %struct.mtree_option*** %global.addr, align 8, !dbg !3379
  %15 = load i8*, i8** %line.addr, align 8, !dbg !3381
  %16 = load i64, i64* %len, align 8, !dbg !3382
  call void @remove_option(%struct.mtree_option** %14, i8* %15, i64 %16), !dbg !3383
  br label %if.end14

if.end14:                                         ; preds = %if.else, %if.then13
  %17 = load i64, i64* %len, align 8, !dbg !3384
  %18 = load i8*, i8** %line.addr, align 8, !dbg !3385
  %add.ptr15 = getelementptr inbounds i8, i8* %18, i64 %17, !dbg !3385
  store i8* %add.ptr15, i8** %line.addr, align 8, !dbg !3385
  br label %for.cond, !dbg !3386

return:                                           ; preds = %if.then5, %if.then
  %19 = load i32, i32* %retval, align 4, !dbg !3388
  ret i32 %19, !dbg !3388
}

; Function Attrs: nounwind readonly
declare i8* @memchr(i8*, i32, i64) #4

declare %struct.archive_string* @archive_string_ensure(%struct.archive_string*, i64) #2

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #5

declare i64 @__archive_read_consume(%struct.archive_read*, i64) #2

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #3

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #6

; Function Attrs: nounwind readonly
declare i64 @strcspn(i8*, i8*) #4

; Function Attrs: nounwind uwtable
define internal void @parse_escapes(i8* %src, %struct.mtree_entry* %mentry) #0 !dbg !387 {
entry:
  %src.addr = alloca i8*, align 8
  %mentry.addr = alloca %struct.mtree_entry*, align 8
  %dest = alloca i8*, align 8
  %c = alloca i8, align 1
  store i8* %src, i8** %src.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %src.addr, metadata !3389, metadata !460), !dbg !3390
  store %struct.mtree_entry* %mentry, %struct.mtree_entry** %mentry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree_entry** %mentry.addr, metadata !3391, metadata !460), !dbg !3392
  call void @llvm.dbg.declare(metadata i8** %dest, metadata !3393, metadata !460), !dbg !3394
  %0 = load i8*, i8** %src.addr, align 8, !dbg !3395
  store i8* %0, i8** %dest, align 8, !dbg !3394
  call void @llvm.dbg.declare(metadata i8* %c, metadata !3396, metadata !460), !dbg !3397
  %1 = load %struct.mtree_entry*, %struct.mtree_entry** %mentry.addr, align 8, !dbg !3398
  %cmp = icmp ne %struct.mtree_entry* %1, null, !dbg !3400
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !3401

land.lhs.true:                                    ; preds = %entry
  %2 = load i8*, i8** %src.addr, align 8, !dbg !3402
  %call = call i32 @strcmp(i8* %2, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.47, i32 0, i32 0)) #8, !dbg !3404
  %cmp1 = icmp eq i32 %call, 0, !dbg !3405
  br i1 %cmp1, label %if.then, label %if.end, !dbg !3406

if.then:                                          ; preds = %land.lhs.true
  %3 = load %struct.mtree_entry*, %struct.mtree_entry** %mentry.addr, align 8, !dbg !3407
  %full = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %3, i32 0, i32 3, !dbg !3408
  store i8 1, i8* %full, align 8, !dbg !3409
  br label %if.end, !dbg !3407

if.end:                                           ; preds = %if.then, %land.lhs.true, %entry
  br label %while.cond, !dbg !3410

while.cond:                                       ; preds = %if.end84, %if.end
  %4 = load i8*, i8** %src.addr, align 8, !dbg !3411
  %5 = load i8, i8* %4, align 1, !dbg !3413
  %conv = sext i8 %5 to i32, !dbg !3413
  %cmp2 = icmp ne i32 %conv, 0, !dbg !3414
  br i1 %cmp2, label %while.body, label %while.end, !dbg !3415

while.body:                                       ; preds = %while.cond
  %6 = load i8*, i8** %src.addr, align 8, !dbg !3416
  %incdec.ptr = getelementptr inbounds i8, i8* %6, i32 1, !dbg !3416
  store i8* %incdec.ptr, i8** %src.addr, align 8, !dbg !3416
  %7 = load i8, i8* %6, align 1, !dbg !3418
  store i8 %7, i8* %c, align 1, !dbg !3419
  %8 = load i8, i8* %c, align 1, !dbg !3420
  %conv4 = sext i8 %8 to i32, !dbg !3420
  %cmp5 = icmp eq i32 %conv4, 47, !dbg !3422
  br i1 %cmp5, label %land.lhs.true7, label %if.end12, !dbg !3423

land.lhs.true7:                                   ; preds = %while.body
  %9 = load %struct.mtree_entry*, %struct.mtree_entry** %mentry.addr, align 8, !dbg !3424
  %cmp8 = icmp ne %struct.mtree_entry* %9, null, !dbg !3426
  br i1 %cmp8, label %if.then10, label %if.end12, !dbg !3427

if.then10:                                        ; preds = %land.lhs.true7
  %10 = load %struct.mtree_entry*, %struct.mtree_entry** %mentry.addr, align 8, !dbg !3428
  %full11 = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %10, i32 0, i32 3, !dbg !3429
  store i8 1, i8* %full11, align 8, !dbg !3430
  br label %if.end12, !dbg !3428

if.end12:                                         ; preds = %if.then10, %land.lhs.true7, %while.body
  %11 = load i8, i8* %c, align 1, !dbg !3431
  %conv13 = sext i8 %11 to i32, !dbg !3431
  %cmp14 = icmp eq i32 %conv13, 92, !dbg !3433
  br i1 %cmp14, label %if.then16, label %if.end84, !dbg !3434

if.then16:                                        ; preds = %if.end12
  %12 = load i8*, i8** %src.addr, align 8, !dbg !3435
  %arrayidx = getelementptr inbounds i8, i8* %12, i64 0, !dbg !3435
  %13 = load i8, i8* %arrayidx, align 1, !dbg !3435
  %conv17 = sext i8 %13 to i32, !dbg !3435
  switch i32 %conv17, label %sw.epilog [
    i32 48, label %sw.bb
    i32 49, label %sw.bb29
    i32 50, label %sw.bb29
    i32 51, label %sw.bb29
    i32 97, label %sw.bb66
    i32 98, label %sw.bb68
    i32 102, label %sw.bb70
    i32 110, label %sw.bb72
    i32 114, label %sw.bb74
    i32 115, label %sw.bb76
    i32 116, label %sw.bb78
    i32 118, label %sw.bb80
    i32 92, label %sw.bb82
  ], !dbg !3437

sw.bb:                                            ; preds = %if.then16
  %14 = load i8*, i8** %src.addr, align 8, !dbg !3438
  %arrayidx18 = getelementptr inbounds i8, i8* %14, i64 1, !dbg !3438
  %15 = load i8, i8* %arrayidx18, align 1, !dbg !3438
  %conv19 = sext i8 %15 to i32, !dbg !3438
  %cmp20 = icmp slt i32 %conv19, 48, !dbg !3441
  br i1 %cmp20, label %if.then26, label %lor.lhs.false, !dbg !3442

lor.lhs.false:                                    ; preds = %sw.bb
  %16 = load i8*, i8** %src.addr, align 8, !dbg !3443
  %arrayidx22 = getelementptr inbounds i8, i8* %16, i64 1, !dbg !3443
  %17 = load i8, i8* %arrayidx22, align 1, !dbg !3443
  %conv23 = sext i8 %17 to i32, !dbg !3443
  %cmp24 = icmp sgt i32 %conv23, 55, !dbg !3445
  br i1 %cmp24, label %if.then26, label %if.end28, !dbg !3446

if.then26:                                        ; preds = %lor.lhs.false, %sw.bb
  store i8 0, i8* %c, align 1, !dbg !3447
  %18 = load i8*, i8** %src.addr, align 8, !dbg !3449
  %incdec.ptr27 = getelementptr inbounds i8, i8* %18, i32 1, !dbg !3449
  store i8* %incdec.ptr27, i8** %src.addr, align 8, !dbg !3449
  br label %sw.epilog, !dbg !3450

if.end28:                                         ; preds = %lor.lhs.false
  br label %sw.bb29, !dbg !3451

sw.bb29:                                          ; preds = %if.then16, %if.then16, %if.then16, %if.end28
  %19 = load i8*, i8** %src.addr, align 8, !dbg !3453
  %arrayidx30 = getelementptr inbounds i8, i8* %19, i64 1, !dbg !3453
  %20 = load i8, i8* %arrayidx30, align 1, !dbg !3453
  %conv31 = sext i8 %20 to i32, !dbg !3453
  %cmp32 = icmp sge i32 %conv31, 48, !dbg !3455
  br i1 %cmp32, label %land.lhs.true34, label %if.end65, !dbg !3456

land.lhs.true34:                                  ; preds = %sw.bb29
  %21 = load i8*, i8** %src.addr, align 8, !dbg !3457
  %arrayidx35 = getelementptr inbounds i8, i8* %21, i64 1, !dbg !3457
  %22 = load i8, i8* %arrayidx35, align 1, !dbg !3457
  %conv36 = sext i8 %22 to i32, !dbg !3457
  %cmp37 = icmp sle i32 %conv36, 55, !dbg !3459
  br i1 %cmp37, label %land.lhs.true39, label %if.end65, !dbg !3460

land.lhs.true39:                                  ; preds = %land.lhs.true34
  %23 = load i8*, i8** %src.addr, align 8, !dbg !3461
  %arrayidx40 = getelementptr inbounds i8, i8* %23, i64 2, !dbg !3461
  %24 = load i8, i8* %arrayidx40, align 1, !dbg !3461
  %conv41 = sext i8 %24 to i32, !dbg !3461
  %cmp42 = icmp sge i32 %conv41, 48, !dbg !3462
  br i1 %cmp42, label %land.lhs.true44, label %if.end65, !dbg !3463

land.lhs.true44:                                  ; preds = %land.lhs.true39
  %25 = load i8*, i8** %src.addr, align 8, !dbg !3464
  %arrayidx45 = getelementptr inbounds i8, i8* %25, i64 2, !dbg !3464
  %26 = load i8, i8* %arrayidx45, align 1, !dbg !3464
  %conv46 = sext i8 %26 to i32, !dbg !3464
  %cmp47 = icmp sle i32 %conv46, 55, !dbg !3465
  br i1 %cmp47, label %if.then49, label %if.end65, !dbg !3466

if.then49:                                        ; preds = %land.lhs.true44
  %27 = load i8*, i8** %src.addr, align 8, !dbg !3468
  %arrayidx50 = getelementptr inbounds i8, i8* %27, i64 0, !dbg !3468
  %28 = load i8, i8* %arrayidx50, align 1, !dbg !3468
  %conv51 = sext i8 %28 to i32, !dbg !3468
  %sub = sub nsw i32 %conv51, 48, !dbg !3470
  %shl = shl i32 %sub, 6, !dbg !3471
  %conv52 = trunc i32 %shl to i8, !dbg !3472
  store i8 %conv52, i8* %c, align 1, !dbg !3473
  %29 = load i8*, i8** %src.addr, align 8, !dbg !3474
  %arrayidx53 = getelementptr inbounds i8, i8* %29, i64 1, !dbg !3474
  %30 = load i8, i8* %arrayidx53, align 1, !dbg !3474
  %conv54 = sext i8 %30 to i32, !dbg !3474
  %sub55 = sub nsw i32 %conv54, 48, !dbg !3475
  %shl56 = shl i32 %sub55, 3, !dbg !3476
  %31 = load i8, i8* %c, align 1, !dbg !3477
  %conv57 = sext i8 %31 to i32, !dbg !3477
  %or = or i32 %conv57, %shl56, !dbg !3477
  %conv58 = trunc i32 %or to i8, !dbg !3477
  store i8 %conv58, i8* %c, align 1, !dbg !3477
  %32 = load i8*, i8** %src.addr, align 8, !dbg !3478
  %arrayidx59 = getelementptr inbounds i8, i8* %32, i64 2, !dbg !3478
  %33 = load i8, i8* %arrayidx59, align 1, !dbg !3478
  %conv60 = sext i8 %33 to i32, !dbg !3478
  %sub61 = sub nsw i32 %conv60, 48, !dbg !3479
  %34 = load i8, i8* %c, align 1, !dbg !3480
  %conv62 = sext i8 %34 to i32, !dbg !3480
  %or63 = or i32 %conv62, %sub61, !dbg !3480
  %conv64 = trunc i32 %or63 to i8, !dbg !3480
  store i8 %conv64, i8* %c, align 1, !dbg !3480
  %35 = load i8*, i8** %src.addr, align 8, !dbg !3481
  %add.ptr = getelementptr inbounds i8, i8* %35, i64 3, !dbg !3481
  store i8* %add.ptr, i8** %src.addr, align 8, !dbg !3481
  br label %if.end65, !dbg !3482

if.end65:                                         ; preds = %if.then49, %land.lhs.true44, %land.lhs.true39, %land.lhs.true34, %sw.bb29
  br label %sw.epilog, !dbg !3483

sw.bb66:                                          ; preds = %if.then16
  store i8 7, i8* %c, align 1, !dbg !3484
  %36 = load i8*, i8** %src.addr, align 8, !dbg !3485
  %incdec.ptr67 = getelementptr inbounds i8, i8* %36, i32 1, !dbg !3485
  store i8* %incdec.ptr67, i8** %src.addr, align 8, !dbg !3485
  br label %sw.epilog, !dbg !3486

sw.bb68:                                          ; preds = %if.then16
  store i8 8, i8* %c, align 1, !dbg !3487
  %37 = load i8*, i8** %src.addr, align 8, !dbg !3488
  %incdec.ptr69 = getelementptr inbounds i8, i8* %37, i32 1, !dbg !3488
  store i8* %incdec.ptr69, i8** %src.addr, align 8, !dbg !3488
  br label %sw.epilog, !dbg !3489

sw.bb70:                                          ; preds = %if.then16
  store i8 12, i8* %c, align 1, !dbg !3490
  %38 = load i8*, i8** %src.addr, align 8, !dbg !3491
  %incdec.ptr71 = getelementptr inbounds i8, i8* %38, i32 1, !dbg !3491
  store i8* %incdec.ptr71, i8** %src.addr, align 8, !dbg !3491
  br label %sw.epilog, !dbg !3492

sw.bb72:                                          ; preds = %if.then16
  store i8 10, i8* %c, align 1, !dbg !3493
  %39 = load i8*, i8** %src.addr, align 8, !dbg !3494
  %incdec.ptr73 = getelementptr inbounds i8, i8* %39, i32 1, !dbg !3494
  store i8* %incdec.ptr73, i8** %src.addr, align 8, !dbg !3494
  br label %sw.epilog, !dbg !3495

sw.bb74:                                          ; preds = %if.then16
  store i8 13, i8* %c, align 1, !dbg !3496
  %40 = load i8*, i8** %src.addr, align 8, !dbg !3497
  %incdec.ptr75 = getelementptr inbounds i8, i8* %40, i32 1, !dbg !3497
  store i8* %incdec.ptr75, i8** %src.addr, align 8, !dbg !3497
  br label %sw.epilog, !dbg !3498

sw.bb76:                                          ; preds = %if.then16
  store i8 32, i8* %c, align 1, !dbg !3499
  %41 = load i8*, i8** %src.addr, align 8, !dbg !3500
  %incdec.ptr77 = getelementptr inbounds i8, i8* %41, i32 1, !dbg !3500
  store i8* %incdec.ptr77, i8** %src.addr, align 8, !dbg !3500
  br label %sw.epilog, !dbg !3501

sw.bb78:                                          ; preds = %if.then16
  store i8 9, i8* %c, align 1, !dbg !3502
  %42 = load i8*, i8** %src.addr, align 8, !dbg !3503
  %incdec.ptr79 = getelementptr inbounds i8, i8* %42, i32 1, !dbg !3503
  store i8* %incdec.ptr79, i8** %src.addr, align 8, !dbg !3503
  br label %sw.epilog, !dbg !3504

sw.bb80:                                          ; preds = %if.then16
  store i8 11, i8* %c, align 1, !dbg !3505
  %43 = load i8*, i8** %src.addr, align 8, !dbg !3506
  %incdec.ptr81 = getelementptr inbounds i8, i8* %43, i32 1, !dbg !3506
  store i8* %incdec.ptr81, i8** %src.addr, align 8, !dbg !3506
  br label %sw.epilog, !dbg !3507

sw.bb82:                                          ; preds = %if.then16
  store i8 92, i8* %c, align 1, !dbg !3508
  %44 = load i8*, i8** %src.addr, align 8, !dbg !3509
  %incdec.ptr83 = getelementptr inbounds i8, i8* %44, i32 1, !dbg !3509
  store i8* %incdec.ptr83, i8** %src.addr, align 8, !dbg !3509
  br label %sw.epilog, !dbg !3510

sw.epilog:                                        ; preds = %if.then16, %sw.bb82, %sw.bb80, %sw.bb78, %sw.bb76, %sw.bb74, %sw.bb72, %sw.bb70, %sw.bb68, %sw.bb66, %if.end65, %if.then26
  br label %if.end84, !dbg !3511

if.end84:                                         ; preds = %sw.epilog, %if.end12
  %45 = load i8, i8* %c, align 1, !dbg !3512
  %46 = load i8*, i8** %dest, align 8, !dbg !3513
  %incdec.ptr85 = getelementptr inbounds i8, i8* %46, i32 1, !dbg !3513
  store i8* %incdec.ptr85, i8** %dest, align 8, !dbg !3513
  store i8 %45, i8* %46, align 1, !dbg !3514
  br label %while.cond, !dbg !3515

while.end:                                        ; preds = %while.cond
  %47 = load i8*, i8** %dest, align 8, !dbg !3517
  store i8 0, i8* %47, align 1, !dbg !3518
  ret void, !dbg !3519
}

; Function Attrs: nounwind uwtable
define internal i32 @hash(i8* %p) #0 !dbg !390 {
entry:
  %p.addr = alloca i8*, align 8
  %g = alloca i32, align 4
  %h = alloca i32, align 4
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !3520, metadata !460), !dbg !3521
  call void @llvm.dbg.declare(metadata i32* %g, metadata !3522, metadata !460), !dbg !3523
  call void @llvm.dbg.declare(metadata i32* %h, metadata !3524, metadata !460), !dbg !3525
  store i32 0, i32* %h, align 4, !dbg !3525
  br label %while.cond, !dbg !3526

while.cond:                                       ; preds = %if.end, %entry
  %0 = load i8*, i8** %p.addr, align 8, !dbg !3527
  %1 = load i8, i8* %0, align 1, !dbg !3529
  %conv = sext i8 %1 to i32, !dbg !3529
  %cmp = icmp ne i32 %conv, 0, !dbg !3530
  br i1 %cmp, label %while.body, label %while.end, !dbg !3531

while.body:                                       ; preds = %while.cond
  %2 = load i32, i32* %h, align 4, !dbg !3532
  %shl = shl i32 %2, 4, !dbg !3534
  %3 = load i8*, i8** %p.addr, align 8, !dbg !3535
  %incdec.ptr = getelementptr inbounds i8, i8* %3, i32 1, !dbg !3535
  store i8* %incdec.ptr, i8** %p.addr, align 8, !dbg !3535
  %4 = load i8, i8* %3, align 1, !dbg !3536
  %conv2 = sext i8 %4 to i32, !dbg !3536
  %add = add i32 %shl, %conv2, !dbg !3537
  store i32 %add, i32* %h, align 4, !dbg !3538
  %5 = load i32, i32* %h, align 4, !dbg !3539
  %and = and i32 %5, -268435456, !dbg !3541
  store i32 %and, i32* %g, align 4, !dbg !3542
  %cmp3 = icmp ne i32 %and, 0, !dbg !3543
  br i1 %cmp3, label %if.then, label %if.end, !dbg !3544

if.then:                                          ; preds = %while.body
  %6 = load i32, i32* %g, align 4, !dbg !3545
  %shr = lshr i32 %6, 24, !dbg !3547
  %7 = load i32, i32* %h, align 4, !dbg !3548
  %xor = xor i32 %7, %shr, !dbg !3548
  store i32 %xor, i32* %h, align 4, !dbg !3548
  %8 = load i32, i32* %h, align 4, !dbg !3549
  %and5 = and i32 %8, 268435455, !dbg !3549
  store i32 %and5, i32* %h, align 4, !dbg !3549
  br label %if.end, !dbg !3550

if.end:                                           ; preds = %if.then, %while.body
  br label %while.cond, !dbg !3551

while.end:                                        ; preds = %while.cond
  %9 = load i32, i32* %h, align 4, !dbg !3553
  ret i32 %9, !dbg !3554
}

; Function Attrs: nounwind uwtable
define internal i32 @add_option(%struct.archive_read* %a, %struct.mtree_option** %global, i8* %value, i64 %len) #0 !dbg !393 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %global.addr = alloca %struct.mtree_option**, align 8
  %value.addr = alloca i8*, align 8
  %len.addr = alloca i64, align 8
  %opt = alloca %struct.mtree_option*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !3555, metadata !460), !dbg !3556
  store %struct.mtree_option** %global, %struct.mtree_option*** %global.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree_option*** %global.addr, metadata !3557, metadata !460), !dbg !3558
  store i8* %value, i8** %value.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %value.addr, metadata !3559, metadata !460), !dbg !3560
  store i64 %len, i64* %len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %len.addr, metadata !3561, metadata !460), !dbg !3562
  call void @llvm.dbg.declare(metadata %struct.mtree_option** %opt, metadata !3563, metadata !460), !dbg !3564
  %call = call noalias i8* @malloc(i64 16) #7, !dbg !3565
  %0 = bitcast i8* %call to %struct.mtree_option*, !dbg !3565
  store %struct.mtree_option* %0, %struct.mtree_option** %opt, align 8, !dbg !3567
  %cmp = icmp eq %struct.mtree_option* %0, null, !dbg !3568
  br i1 %cmp, label %if.then, label %if.end, !dbg !3569

if.then:                                          ; preds = %entry
  %1 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3570
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %1, i32 0, i32 0, !dbg !3572
  %call1 = call i32* @__errno_location() #1, !dbg !3573
  %2 = load i32, i32* %call1, align 4, !dbg !3573
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 %2, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.45, i32 0, i32 0)), !dbg !3574
  store i32 -30, i32* %retval, align 4, !dbg !3576
  br label %return, !dbg !3576

if.end:                                           ; preds = %entry
  %3 = load i64, i64* %len.addr, align 8, !dbg !3577
  %add = add i64 %3, 1, !dbg !3579
  %call2 = call noalias i8* @malloc(i64 %add) #7, !dbg !3580
  %4 = load %struct.mtree_option*, %struct.mtree_option** %opt, align 8, !dbg !3581
  %value3 = getelementptr inbounds %struct.mtree_option, %struct.mtree_option* %4, i32 0, i32 1, !dbg !3582
  store i8* %call2, i8** %value3, align 8, !dbg !3583
  %cmp4 = icmp eq i8* %call2, null, !dbg !3584
  br i1 %cmp4, label %if.then5, label %if.end8, !dbg !3585

if.then5:                                         ; preds = %if.end
  %5 = load %struct.mtree_option*, %struct.mtree_option** %opt, align 8, !dbg !3586
  %6 = bitcast %struct.mtree_option* %5 to i8*, !dbg !3586
  call void @free(i8* %6) #7, !dbg !3588
  %7 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3589
  %archive6 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %7, i32 0, i32 0, !dbg !3590
  %call7 = call i32* @__errno_location() #1, !dbg !3591
  %8 = load i32, i32* %call7, align 4, !dbg !3591
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive6, i32 %8, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.45, i32 0, i32 0)), !dbg !3592
  store i32 -30, i32* %retval, align 4, !dbg !3594
  br label %return, !dbg !3594

if.end8:                                          ; preds = %if.end
  %9 = load %struct.mtree_option*, %struct.mtree_option** %opt, align 8, !dbg !3595
  %value9 = getelementptr inbounds %struct.mtree_option, %struct.mtree_option* %9, i32 0, i32 1, !dbg !3596
  %10 = load i8*, i8** %value9, align 8, !dbg !3596
  %11 = load i8*, i8** %value.addr, align 8, !dbg !3597
  %12 = load i64, i64* %len.addr, align 8, !dbg !3598
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %10, i8* %11, i64 %12, i32 1, i1 false), !dbg !3599
  %13 = load i64, i64* %len.addr, align 8, !dbg !3600
  %14 = load %struct.mtree_option*, %struct.mtree_option** %opt, align 8, !dbg !3601
  %value10 = getelementptr inbounds %struct.mtree_option, %struct.mtree_option* %14, i32 0, i32 1, !dbg !3602
  %15 = load i8*, i8** %value10, align 8, !dbg !3602
  %arrayidx = getelementptr inbounds i8, i8* %15, i64 %13, !dbg !3601
  store i8 0, i8* %arrayidx, align 1, !dbg !3603
  %16 = load %struct.mtree_option**, %struct.mtree_option*** %global.addr, align 8, !dbg !3604
  %17 = load %struct.mtree_option*, %struct.mtree_option** %16, align 8, !dbg !3605
  %18 = load %struct.mtree_option*, %struct.mtree_option** %opt, align 8, !dbg !3606
  %next = getelementptr inbounds %struct.mtree_option, %struct.mtree_option* %18, i32 0, i32 0, !dbg !3607
  store %struct.mtree_option* %17, %struct.mtree_option** %next, align 8, !dbg !3608
  %19 = load %struct.mtree_option*, %struct.mtree_option** %opt, align 8, !dbg !3609
  %20 = load %struct.mtree_option**, %struct.mtree_option*** %global.addr, align 8, !dbg !3610
  store %struct.mtree_option* %19, %struct.mtree_option** %20, align 8, !dbg !3611
  store i32 0, i32* %retval, align 4, !dbg !3612
  br label %return, !dbg !3612

return:                                           ; preds = %if.end8, %if.then5, %if.then
  %21 = load i32, i32* %retval, align 4, !dbg !3613
  ret i32 %21, !dbg !3613
}

; Function Attrs: nounwind readonly
declare i64 @strspn(i8*, i8*) #4

; Function Attrs: nounwind readonly
declare i8* @strchr(i8*, i32) #4

; Function Attrs: nounwind uwtable
define internal void @remove_option(%struct.mtree_option** %global, i8* %value, i64 %len) #0 !dbg !396 {
entry:
  %global.addr = alloca %struct.mtree_option**, align 8
  %value.addr = alloca i8*, align 8
  %len.addr = alloca i64, align 8
  %iter = alloca %struct.mtree_option*, align 8
  %last = alloca %struct.mtree_option*, align 8
  store %struct.mtree_option** %global, %struct.mtree_option*** %global.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree_option*** %global.addr, metadata !3614, metadata !460), !dbg !3615
  store i8* %value, i8** %value.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %value.addr, metadata !3616, metadata !460), !dbg !3617
  store i64 %len, i64* %len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %len.addr, metadata !3618, metadata !460), !dbg !3619
  call void @llvm.dbg.declare(metadata %struct.mtree_option** %iter, metadata !3620, metadata !460), !dbg !3621
  call void @llvm.dbg.declare(metadata %struct.mtree_option** %last, metadata !3622, metadata !460), !dbg !3623
  store %struct.mtree_option* null, %struct.mtree_option** %last, align 8, !dbg !3624
  %0 = load %struct.mtree_option**, %struct.mtree_option*** %global.addr, align 8, !dbg !3625
  %1 = load %struct.mtree_option*, %struct.mtree_option** %0, align 8, !dbg !3627
  store %struct.mtree_option* %1, %struct.mtree_option** %iter, align 8, !dbg !3628
  br label %for.cond, !dbg !3629

for.cond:                                         ; preds = %for.inc, %entry
  %2 = load %struct.mtree_option*, %struct.mtree_option** %iter, align 8, !dbg !3630
  %cmp = icmp ne %struct.mtree_option* %2, null, !dbg !3633
  br i1 %cmp, label %for.body, label %for.end, !dbg !3634

for.body:                                         ; preds = %for.cond
  %3 = load %struct.mtree_option*, %struct.mtree_option** %iter, align 8, !dbg !3635
  %value1 = getelementptr inbounds %struct.mtree_option, %struct.mtree_option* %3, i32 0, i32 1, !dbg !3638
  %4 = load i8*, i8** %value1, align 8, !dbg !3638
  %5 = load i8*, i8** %value.addr, align 8, !dbg !3639
  %6 = load i64, i64* %len.addr, align 8, !dbg !3640
  %call = call i32 @strncmp(i8* %4, i8* %5, i64 %6) #8, !dbg !3641
  %cmp2 = icmp eq i32 %call, 0, !dbg !3642
  br i1 %cmp2, label %land.lhs.true, label %if.end, !dbg !3643

land.lhs.true:                                    ; preds = %for.body
  %7 = load i64, i64* %len.addr, align 8, !dbg !3644
  %8 = load %struct.mtree_option*, %struct.mtree_option** %iter, align 8, !dbg !3645
  %value3 = getelementptr inbounds %struct.mtree_option, %struct.mtree_option* %8, i32 0, i32 1, !dbg !3646
  %9 = load i8*, i8** %value3, align 8, !dbg !3646
  %arrayidx = getelementptr inbounds i8, i8* %9, i64 %7, !dbg !3645
  %10 = load i8, i8* %arrayidx, align 1, !dbg !3645
  %conv = sext i8 %10 to i32, !dbg !3645
  %cmp4 = icmp eq i32 %conv, 0, !dbg !3647
  br i1 %cmp4, label %if.then, label %lor.lhs.false, !dbg !3648

lor.lhs.false:                                    ; preds = %land.lhs.true
  %11 = load i64, i64* %len.addr, align 8, !dbg !3649
  %12 = load %struct.mtree_option*, %struct.mtree_option** %iter, align 8, !dbg !3650
  %value6 = getelementptr inbounds %struct.mtree_option, %struct.mtree_option* %12, i32 0, i32 1, !dbg !3651
  %13 = load i8*, i8** %value6, align 8, !dbg !3651
  %arrayidx7 = getelementptr inbounds i8, i8* %13, i64 %11, !dbg !3650
  %14 = load i8, i8* %arrayidx7, align 1, !dbg !3650
  %conv8 = sext i8 %14 to i32, !dbg !3650
  %cmp9 = icmp eq i32 %conv8, 61, !dbg !3652
  br i1 %cmp9, label %if.then, label %if.end, !dbg !3653

if.then:                                          ; preds = %lor.lhs.false, %land.lhs.true
  br label %for.end, !dbg !3655

if.end:                                           ; preds = %lor.lhs.false, %for.body
  br label %for.inc, !dbg !3656

for.inc:                                          ; preds = %if.end
  %15 = load %struct.mtree_option*, %struct.mtree_option** %iter, align 8, !dbg !3657
  store %struct.mtree_option* %15, %struct.mtree_option** %last, align 8, !dbg !3659
  %16 = load %struct.mtree_option*, %struct.mtree_option** %iter, align 8, !dbg !3660
  %next = getelementptr inbounds %struct.mtree_option, %struct.mtree_option* %16, i32 0, i32 0, !dbg !3661
  %17 = load %struct.mtree_option*, %struct.mtree_option** %next, align 8, !dbg !3661
  store %struct.mtree_option* %17, %struct.mtree_option** %iter, align 8, !dbg !3662
  br label %for.cond, !dbg !3663

for.end:                                          ; preds = %if.then, %for.cond
  %18 = load %struct.mtree_option*, %struct.mtree_option** %iter, align 8, !dbg !3664
  %cmp11 = icmp eq %struct.mtree_option* %18, null, !dbg !3666
  br i1 %cmp11, label %if.then13, label %if.end14, !dbg !3667

if.then13:                                        ; preds = %for.end
  br label %return, !dbg !3668

if.end14:                                         ; preds = %for.end
  %19 = load %struct.mtree_option*, %struct.mtree_option** %last, align 8, !dbg !3669
  %cmp15 = icmp eq %struct.mtree_option* %19, null, !dbg !3671
  br i1 %cmp15, label %if.then17, label %if.else, !dbg !3672

if.then17:                                        ; preds = %if.end14
  %20 = load %struct.mtree_option*, %struct.mtree_option** %iter, align 8, !dbg !3673
  %next18 = getelementptr inbounds %struct.mtree_option, %struct.mtree_option* %20, i32 0, i32 0, !dbg !3674
  %21 = load %struct.mtree_option*, %struct.mtree_option** %next18, align 8, !dbg !3674
  %22 = load %struct.mtree_option**, %struct.mtree_option*** %global.addr, align 8, !dbg !3675
  store %struct.mtree_option* %21, %struct.mtree_option** %22, align 8, !dbg !3676
  br label %if.end21, !dbg !3677

if.else:                                          ; preds = %if.end14
  %23 = load %struct.mtree_option*, %struct.mtree_option** %iter, align 8, !dbg !3678
  %next19 = getelementptr inbounds %struct.mtree_option, %struct.mtree_option* %23, i32 0, i32 0, !dbg !3679
  %24 = load %struct.mtree_option*, %struct.mtree_option** %next19, align 8, !dbg !3679
  %25 = load %struct.mtree_option*, %struct.mtree_option** %last, align 8, !dbg !3680
  %next20 = getelementptr inbounds %struct.mtree_option, %struct.mtree_option* %25, i32 0, i32 0, !dbg !3681
  store %struct.mtree_option* %24, %struct.mtree_option** %next20, align 8, !dbg !3682
  br label %if.end21

if.end21:                                         ; preds = %if.else, %if.then17
  %26 = load %struct.mtree_option*, %struct.mtree_option** %iter, align 8, !dbg !3683
  %value22 = getelementptr inbounds %struct.mtree_option, %struct.mtree_option* %26, i32 0, i32 1, !dbg !3684
  %27 = load i8*, i8** %value22, align 8, !dbg !3684
  call void @free(i8* %27) #7, !dbg !3685
  %28 = load %struct.mtree_option*, %struct.mtree_option** %iter, align 8, !dbg !3686
  %29 = bitcast %struct.mtree_option* %28 to i8*, !dbg !3686
  call void @free(i8* %29) #7, !dbg !3687
  br label %return, !dbg !3688

return:                                           ; preds = %if.end21, %if.then13
  ret void, !dbg !3689
}

declare void @archive_entry_set_filetype(%struct.archive_entry*, i32) #2

declare void @archive_entry_set_size(%struct.archive_entry*, i64) #2

; Function Attrs: nounwind uwtable
define internal i32 @parse_line(%struct.archive_read* %a, %struct.archive_entry* %entry1, %struct.mtree* %mtree, %struct.mtree_entry* %mp, i32* %parsed_kws) #0 !dbg !406 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %mtree.addr = alloca %struct.mtree*, align 8
  %mp.addr = alloca %struct.mtree_entry*, align 8
  %parsed_kws.addr = alloca i32*, align 8
  %iter = alloca %struct.mtree_option*, align 8
  %r = alloca i32, align 4
  %r1 = alloca i32, align 4
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !3691, metadata !460), !dbg !3692
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3693, metadata !460), !dbg !3694
  store %struct.mtree* %mtree, %struct.mtree** %mtree.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree** %mtree.addr, metadata !3695, metadata !460), !dbg !3696
  store %struct.mtree_entry* %mp, %struct.mtree_entry** %mp.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree_entry** %mp.addr, metadata !3697, metadata !460), !dbg !3698
  store i32* %parsed_kws, i32** %parsed_kws.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %parsed_kws.addr, metadata !3699, metadata !460), !dbg !3700
  call void @llvm.dbg.declare(metadata %struct.mtree_option** %iter, metadata !3701, metadata !460), !dbg !3702
  call void @llvm.dbg.declare(metadata i32* %r, metadata !3703, metadata !460), !dbg !3704
  store i32 0, i32* %r, align 4, !dbg !3704
  call void @llvm.dbg.declare(metadata i32* %r1, metadata !3705, metadata !460), !dbg !3706
  %0 = load %struct.mtree_entry*, %struct.mtree_entry** %mp.addr, align 8, !dbg !3707
  %options = getelementptr inbounds %struct.mtree_entry, %struct.mtree_entry* %0, i32 0, i32 1, !dbg !3709
  %1 = load %struct.mtree_option*, %struct.mtree_option** %options, align 8, !dbg !3709
  store %struct.mtree_option* %1, %struct.mtree_option** %iter, align 8, !dbg !3710
  br label %for.cond, !dbg !3711

for.cond:                                         ; preds = %for.inc, %entry
  %2 = load %struct.mtree_option*, %struct.mtree_option** %iter, align 8, !dbg !3712
  %cmp = icmp ne %struct.mtree_option* %2, null, !dbg !3715
  br i1 %cmp, label %for.body, label %for.end, !dbg !3716

for.body:                                         ; preds = %for.cond
  %3 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3717
  %4 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !3719
  %5 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3720
  %6 = load %struct.mtree_option*, %struct.mtree_option** %iter, align 8, !dbg !3721
  %7 = load i32*, i32** %parsed_kws.addr, align 8, !dbg !3722
  %call = call i32 @parse_keyword(%struct.archive_read* %3, %struct.mtree* %4, %struct.archive_entry* %5, %struct.mtree_option* %6, i32* %7), !dbg !3723
  store i32 %call, i32* %r1, align 4, !dbg !3724
  %8 = load i32, i32* %r1, align 4, !dbg !3725
  %9 = load i32, i32* %r, align 4, !dbg !3727
  %cmp2 = icmp slt i32 %8, %9, !dbg !3728
  br i1 %cmp2, label %if.then, label %if.end, !dbg !3729

if.then:                                          ; preds = %for.body
  %10 = load i32, i32* %r1, align 4, !dbg !3730
  store i32 %10, i32* %r, align 4, !dbg !3731
  br label %if.end, !dbg !3732

if.end:                                           ; preds = %if.then, %for.body
  br label %for.inc, !dbg !3733

for.inc:                                          ; preds = %if.end
  %11 = load %struct.mtree_option*, %struct.mtree_option** %iter, align 8, !dbg !3734
  %next = getelementptr inbounds %struct.mtree_option, %struct.mtree_option* %11, i32 0, i32 0, !dbg !3736
  %12 = load %struct.mtree_option*, %struct.mtree_option** %next, align 8, !dbg !3736
  store %struct.mtree_option* %12, %struct.mtree_option** %iter, align 8, !dbg !3737
  br label %for.cond, !dbg !3738

for.end:                                          ; preds = %for.cond
  %13 = load i32, i32* %r, align 4, !dbg !3739
  %cmp3 = icmp eq i32 %13, 0, !dbg !3741
  br i1 %cmp3, label %land.lhs.true, label %if.end6, !dbg !3742

land.lhs.true:                                    ; preds = %for.end
  %14 = load i32*, i32** %parsed_kws.addr, align 8, !dbg !3743
  %15 = load i32, i32* %14, align 4, !dbg !3745
  %and = and i32 %15, 256, !dbg !3746
  %cmp4 = icmp eq i32 %and, 0, !dbg !3747
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !3748

if.then5:                                         ; preds = %land.lhs.true
  %16 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3749
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %16, i32 0, i32 0, !dbg !3751
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 84, i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.53, i32 0, i32 0)), !dbg !3752
  store i32 -20, i32* %retval, align 4, !dbg !3753
  br label %return, !dbg !3753

if.end6:                                          ; preds = %land.lhs.true, %for.end
  %17 = load i32, i32* %r, align 4, !dbg !3754
  store i32 %17, i32* %retval, align 4, !dbg !3755
  br label %return, !dbg !3755

return:                                           ; preds = %if.end6, %if.then5
  %18 = load i32, i32* %retval, align 4, !dbg !3756
  ret i32 %18, !dbg !3756
}

declare void @archive_entry_copy_pathname(%struct.archive_entry*, i8*) #2

declare %struct.archive_string* @archive_strcat(%struct.archive_string*, i8*) #2

declare i32 @archive_entry_filetype(%struct.archive_entry*) #2

declare i8* @archive_entry_pathname(%struct.archive_entry*) #2

declare i32 @open(i8*, i32, ...) #2

declare void @__archive_ensure_cloexec_flag(i32) #2

; Function Attrs: nounwind
declare i32 @fstat(i32, %struct.stat*) #3

; Function Attrs: nounwind
declare i32 @lstat(i8*, %struct.stat*) #3

declare void @archive_entry_set_rdev(%struct.archive_entry*, i64) #2

declare void @archive_entry_set_gid(%struct.archive_entry*, i64) #2

declare void @archive_entry_set_uid(%struct.archive_entry*, i64) #2

declare void @archive_entry_set_mtime(%struct.archive_entry*, i64, i64) #2

declare void @archive_entry_set_nlink(%struct.archive_entry*, i32) #2

declare void @archive_entry_set_perm(%struct.archive_entry*, i32) #2

declare void @archive_entry_set_ino(%struct.archive_entry*, i64) #2

declare void @archive_entry_set_dev(%struct.archive_entry*, i64) #2

declare void @archive_entry_linkify(%struct.archive_entry_linkresolver*, %struct.archive_entry**, %struct.archive_entry**) #2

declare i64 @archive_entry_size(%struct.archive_entry*) #2

; Function Attrs: nounwind uwtable
define internal i32 @parse_keyword(%struct.archive_read* %a, %struct.mtree* %mtree, %struct.archive_entry* %entry1, %struct.mtree_option* %opt, i32* %parsed_kws) #0 !dbg !407 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %mtree.addr = alloca %struct.mtree*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %opt.addr = alloca %struct.mtree_option*, align 8
  %parsed_kws.addr = alloca i32*, align 8
  %val = alloca i8*, align 8
  %key = alloca i8*, align 8
  %r = alloca i32, align 4
  %dev = alloca i64, align 8
  %r135 = alloca i32, align 4
  %dev136 = alloca i64, align 8
  %m = alloca i64, align 8
  %my_time_t_max = alloca i64, align 8
  %my_time_t_min = alloca i64, align 8
  %ns = alloca i64, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !3757, metadata !460), !dbg !3758
  store %struct.mtree* %mtree, %struct.mtree** %mtree.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree** %mtree.addr, metadata !3759, metadata !460), !dbg !3760
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3761, metadata !460), !dbg !3762
  store %struct.mtree_option* %opt, %struct.mtree_option** %opt.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.mtree_option** %opt.addr, metadata !3763, metadata !460), !dbg !3764
  store i32* %parsed_kws, i32** %parsed_kws.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %parsed_kws.addr, metadata !3765, metadata !460), !dbg !3766
  call void @llvm.dbg.declare(metadata i8** %val, metadata !3767, metadata !460), !dbg !3768
  call void @llvm.dbg.declare(metadata i8** %key, metadata !3769, metadata !460), !dbg !3770
  %0 = load %struct.mtree_option*, %struct.mtree_option** %opt.addr, align 8, !dbg !3771
  %value = getelementptr inbounds %struct.mtree_option, %struct.mtree_option* %0, i32 0, i32 1, !dbg !3772
  %1 = load i8*, i8** %value, align 8, !dbg !3772
  store i8* %1, i8** %key, align 8, !dbg !3773
  %2 = load i8*, i8** %key, align 8, !dbg !3774
  %3 = load i8, i8* %2, align 1, !dbg !3776
  %conv = sext i8 %3 to i32, !dbg !3776
  %cmp = icmp eq i32 %conv, 0, !dbg !3777
  br i1 %cmp, label %if.then, label %if.end, !dbg !3778

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !3779
  br label %return, !dbg !3779

if.end:                                           ; preds = %entry
  %4 = load i8*, i8** %key, align 8, !dbg !3780
  %call = call i32 @strcmp(i8* %4, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.22, i32 0, i32 0)) #8, !dbg !3782
  %cmp3 = icmp eq i32 %call, 0, !dbg !3783
  br i1 %cmp3, label %if.then5, label %if.end6, !dbg !3784

if.then5:                                         ; preds = %if.end
  %5 = load i32*, i32** %parsed_kws.addr, align 8, !dbg !3785
  %6 = load i32, i32* %5, align 4, !dbg !3787
  %or = or i32 %6, 4096, !dbg !3787
  store i32 %or, i32* %5, align 4, !dbg !3787
  store i32 0, i32* %retval, align 4, !dbg !3788
  br label %return, !dbg !3788

if.end6:                                          ; preds = %if.end
  %7 = load i8*, i8** %key, align 8, !dbg !3789
  %call7 = call i32 @strcmp(i8* %7, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.23, i32 0, i32 0)) #8, !dbg !3791
  %cmp8 = icmp eq i32 %call7, 0, !dbg !3792
  br i1 %cmp8, label %if.then10, label %if.end12, !dbg !3793

if.then10:                                        ; preds = %if.end6
  %8 = load i32*, i32** %parsed_kws.addr, align 8, !dbg !3794
  %9 = load i32, i32* %8, align 4, !dbg !3796
  %or11 = or i32 %9, 2048, !dbg !3796
  store i32 %or11, i32* %8, align 4, !dbg !3796
  store i32 0, i32* %retval, align 4, !dbg !3797
  br label %return, !dbg !3797

if.end12:                                         ; preds = %if.end6
  %10 = load i8*, i8** %key, align 8, !dbg !3798
  %call13 = call i32 @strcmp(i8* %10, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.15, i32 0, i32 0)) #8, !dbg !3800
  %cmp14 = icmp eq i32 %call13, 0, !dbg !3801
  br i1 %cmp14, label %if.then16, label %if.end17, !dbg !3802

if.then16:                                        ; preds = %if.end12
  store i32 0, i32* %retval, align 4, !dbg !3803
  br label %return, !dbg !3803

if.end17:                                         ; preds = %if.end12
  %11 = load i8*, i8** %key, align 8, !dbg !3805
  %call18 = call i8* @strchr(i8* %11, i32 61) #8, !dbg !3806
  store i8* %call18, i8** %val, align 8, !dbg !3807
  %12 = load i8*, i8** %val, align 8, !dbg !3808
  %cmp19 = icmp eq i8* %12, null, !dbg !3810
  br i1 %cmp19, label %if.then21, label %if.end23, !dbg !3811

if.then21:                                        ; preds = %if.end17
  %13 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3812
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %13, i32 0, i32 0, !dbg !3814
  %14 = load i8*, i8** %key, align 8, !dbg !3815
  %15 = load i8*, i8** %key, align 8, !dbg !3816
  %arrayidx = getelementptr inbounds i8, i8* %15, i64 0, !dbg !3816
  %16 = load i8, i8* %arrayidx, align 1, !dbg !3816
  %conv22 = sext i8 %16 to i32, !dbg !3816
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 84, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.54, i32 0, i32 0), i8* %14, i32 %conv22), !dbg !3817
  store i32 -20, i32* %retval, align 4, !dbg !3818
  br label %return, !dbg !3818

if.end23:                                         ; preds = %if.end17
  %17 = load i8*, i8** %val, align 8, !dbg !3819
  store i8 0, i8* %17, align 1, !dbg !3820
  %18 = load i8*, i8** %val, align 8, !dbg !3821
  %incdec.ptr = getelementptr inbounds i8, i8* %18, i32 1, !dbg !3821
  store i8* %incdec.ptr, i8** %val, align 8, !dbg !3821
  %19 = load i8*, i8** %key, align 8, !dbg !3822
  %arrayidx24 = getelementptr inbounds i8, i8* %19, i64 0, !dbg !3822
  %20 = load i8, i8* %arrayidx24, align 1, !dbg !3822
  %conv25 = sext i8 %20 to i32, !dbg !3822
  switch i32 %conv25, label %sw.default294 [
    i32 99, label %sw.bb
    i32 100, label %sw.bb44
    i32 102, label %sw.bb57
    i32 103, label %sw.bb65
    i32 105, label %sw.bb79
    i32 108, label %sw.bb86
    i32 109, label %sw.bb92
    i32 110, label %sw.bb121
    i32 114, label %sw.bb130
    i32 115, label %sw.bb153
    i32 116, label %sw.bb196
    i32 117, label %sw.bb280
  ], !dbg !3823

sw.bb:                                            ; preds = %if.end23
  %21 = load i8*, i8** %key, align 8, !dbg !3824
  %call26 = call i32 @strcmp(i8* %21, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.8, i32 0, i32 0)) #8, !dbg !3827
  %cmp27 = icmp eq i32 %call26, 0, !dbg !3828
  br i1 %cmp27, label %if.then32, label %lor.lhs.false, !dbg !3829

lor.lhs.false:                                    ; preds = %sw.bb
  %22 = load i8*, i8** %key, align 8, !dbg !3830
  %call29 = call i32 @strcmp(i8* %22, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.9, i32 0, i32 0)) #8, !dbg !3832
  %cmp30 = icmp eq i32 %call29, 0, !dbg !3833
  br i1 %cmp30, label %if.then32, label %if.end38, !dbg !3834

if.then32:                                        ; preds = %lor.lhs.false, %sw.bb
  %23 = load i8*, i8** %val, align 8, !dbg !3836
  call void @parse_escapes(i8* %23, %struct.mtree_entry* null), !dbg !3838
  %24 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !3839
  %contents_name = getelementptr inbounds %struct.mtree, %struct.mtree* %24, i32 0, i32 11, !dbg !3839
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %contents_name, i32 0, i32 1, !dbg !3839
  store i64 0, i64* %length, align 8, !dbg !3839
  %25 = load %struct.mtree*, %struct.mtree** %mtree.addr, align 8, !dbg !3839
  %contents_name33 = getelementptr inbounds %struct.mtree, %struct.mtree* %25, i32 0, i32 11, !dbg !3839
  %26 = load i8*, i8** %val, align 8, !dbg !3839
  %27 = load i8*, i8** %val, align 8, !dbg !3839
  %cmp34 = icmp eq i8* %27, null, !dbg !3839
  br i1 %cmp34, label %cond.true, label %cond.false, !dbg !3839

cond.true:                                        ; preds = %if.then32
  br label %cond.end, !dbg !3840

cond.false:                                       ; preds = %if.then32
  %28 = load i8*, i8** %val, align 8, !dbg !3842
  %call36 = call i64 @strlen(i8* %28) #8, !dbg !3842
  br label %cond.end, !dbg !3842

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ 0, %cond.true ], [ %call36, %cond.false ], !dbg !3844
  %call37 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %contents_name33, i8* %26, i64 %cond), !dbg !3844
  br label %sw.epilog296, !dbg !3846

if.end38:                                         ; preds = %lor.lhs.false
  %29 = load i8*, i8** %key, align 8, !dbg !3847
  %call39 = call i32 @strcmp(i8* %29, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.10, i32 0, i32 0)) #8, !dbg !3849
  %cmp40 = icmp eq i32 %call39, 0, !dbg !3850
  br i1 %cmp40, label %if.then42, label %if.end43, !dbg !3851

if.then42:                                        ; preds = %if.end38
  br label %sw.epilog296, !dbg !3852

if.end43:                                         ; preds = %if.end38
  br label %sw.bb44, !dbg !3853

sw.bb44:                                          ; preds = %if.end23, %if.end43
  %30 = load i8*, i8** %key, align 8, !dbg !3855
  %call45 = call i32 @strcmp(i8* %30, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.11, i32 0, i32 0)) #8, !dbg !3857
  %cmp46 = icmp eq i32 %call45, 0, !dbg !3858
  br i1 %cmp46, label %if.then48, label %if.end56, !dbg !3859

if.then48:                                        ; preds = %sw.bb44
  call void @llvm.dbg.declare(metadata i32* %r, metadata !3860, metadata !460), !dbg !3862
  call void @llvm.dbg.declare(metadata i64* %dev, metadata !3863, metadata !460), !dbg !3864
  %31 = load i32*, i32** %parsed_kws.addr, align 8, !dbg !3865
  %32 = load i32, i32* %31, align 4, !dbg !3866
  %or49 = or i32 %32, 1, !dbg !3866
  store i32 %or49, i32* %31, align 4, !dbg !3866
  %33 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3867
  %archive50 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %33, i32 0, i32 0, !dbg !3868
  %34 = load i8*, i8** %val, align 8, !dbg !3869
  %call51 = call i32 @parse_device(i64* %dev, %struct.archive* %archive50, i8* %34), !dbg !3870
  store i32 %call51, i32* %r, align 4, !dbg !3871
  %35 = load i32, i32* %r, align 4, !dbg !3872
  %cmp52 = icmp eq i32 %35, 0, !dbg !3874
  br i1 %cmp52, label %if.then54, label %if.end55, !dbg !3875

if.then54:                                        ; preds = %if.then48
  %36 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3876
  %37 = load i64, i64* %dev, align 8, !dbg !3877
  call void @archive_entry_set_rdev(%struct.archive_entry* %36, i64 %37), !dbg !3878
  br label %if.end55, !dbg !3878

if.end55:                                         ; preds = %if.then54, %if.then48
  %38 = load i32, i32* %r, align 4, !dbg !3879
  store i32 %38, i32* %retval, align 4, !dbg !3880
  br label %return, !dbg !3880

if.end56:                                         ; preds = %sw.bb44
  br label %sw.bb57, !dbg !3881

sw.bb57:                                          ; preds = %if.end23, %if.end56
  %39 = load i8*, i8** %key, align 8, !dbg !3883
  %call58 = call i32 @strcmp(i8* %39, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.12, i32 0, i32 0)) #8, !dbg !3885
  %cmp59 = icmp eq i32 %call58, 0, !dbg !3886
  br i1 %cmp59, label %if.then61, label %if.end64, !dbg !3887

if.then61:                                        ; preds = %sw.bb57
  %40 = load i32*, i32** %parsed_kws.addr, align 8, !dbg !3888
  %41 = load i32, i32* %40, align 4, !dbg !3890
  %or62 = or i32 %41, 2, !dbg !3890
  store i32 %or62, i32* %40, align 4, !dbg !3890
  %42 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3891
  %43 = load i8*, i8** %val, align 8, !dbg !3892
  %call63 = call i8* @archive_entry_copy_fflags_text(%struct.archive_entry* %42, i8* %43), !dbg !3893
  br label %sw.epilog296, !dbg !3894

if.end64:                                         ; preds = %sw.bb57
  br label %sw.bb65, !dbg !3895

sw.bb65:                                          ; preds = %if.end23, %if.end64
  %44 = load i8*, i8** %key, align 8, !dbg !3897
  %call66 = call i32 @strcmp(i8* %44, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.13, i32 0, i32 0)) #8, !dbg !3899
  %cmp67 = icmp eq i32 %call66, 0, !dbg !3900
  br i1 %cmp67, label %if.then69, label %if.end72, !dbg !3901

if.then69:                                        ; preds = %sw.bb65
  %45 = load i32*, i32** %parsed_kws.addr, align 8, !dbg !3902
  %46 = load i32, i32* %45, align 4, !dbg !3904
  %or70 = or i32 %46, 4, !dbg !3904
  store i32 %or70, i32* %45, align 4, !dbg !3904
  %47 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3905
  %call71 = call i64 @mtree_atol10(i8** %val), !dbg !3906
  call void @archive_entry_set_gid(%struct.archive_entry* %47, i64 %call71), !dbg !3907
  br label %sw.epilog296, !dbg !3909

if.end72:                                         ; preds = %sw.bb65
  %48 = load i8*, i8** %key, align 8, !dbg !3910
  %call73 = call i32 @strcmp(i8* %48, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.14, i32 0, i32 0)) #8, !dbg !3912
  %cmp74 = icmp eq i32 %call73, 0, !dbg !3913
  br i1 %cmp74, label %if.then76, label %if.end78, !dbg !3914

if.then76:                                        ; preds = %if.end72
  %49 = load i32*, i32** %parsed_kws.addr, align 8, !dbg !3915
  %50 = load i32, i32* %49, align 4, !dbg !3917
  %or77 = or i32 %50, 8, !dbg !3917
  store i32 %or77, i32* %49, align 4, !dbg !3917
  %51 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3918
  %52 = load i8*, i8** %val, align 8, !dbg !3919
  call void @archive_entry_copy_gname(%struct.archive_entry* %51, i8* %52), !dbg !3920
  br label %sw.epilog296, !dbg !3921

if.end78:                                         ; preds = %if.end72
  br label %sw.bb79, !dbg !3922

sw.bb79:                                          ; preds = %if.end23, %if.end78
  %53 = load i8*, i8** %key, align 8, !dbg !3924
  %call80 = call i32 @strcmp(i8* %53, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.16, i32 0, i32 0)) #8, !dbg !3926
  %cmp81 = icmp eq i32 %call80, 0, !dbg !3927
  br i1 %cmp81, label %if.then83, label %if.end85, !dbg !3928

if.then83:                                        ; preds = %sw.bb79
  %54 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3929
  %call84 = call i64 @mtree_atol10(i8** %val), !dbg !3931
  call void @archive_entry_set_ino(%struct.archive_entry* %54, i64 %call84), !dbg !3932
  br label %sw.epilog296, !dbg !3934

if.end85:                                         ; preds = %sw.bb79
  br label %sw.bb86, !dbg !3935

sw.bb86:                                          ; preds = %if.end23, %if.end85
  %55 = load i8*, i8** %key, align 8, !dbg !3937
  %call87 = call i32 @strcmp(i8* %55, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.17, i32 0, i32 0)) #8, !dbg !3939
  %cmp88 = icmp eq i32 %call87, 0, !dbg !3940
  br i1 %cmp88, label %if.then90, label %if.end91, !dbg !3941

if.then90:                                        ; preds = %sw.bb86
  %56 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3942
  %57 = load i8*, i8** %val, align 8, !dbg !3944
  call void @archive_entry_copy_symlink(%struct.archive_entry* %56, i8* %57), !dbg !3945
  br label %sw.epilog296, !dbg !3946

if.end91:                                         ; preds = %sw.bb86
  br label %sw.bb92, !dbg !3947

sw.bb92:                                          ; preds = %if.end23, %if.end91
  %58 = load i8*, i8** %key, align 8, !dbg !3949
  %call93 = call i32 @strcmp(i8* %58, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.18, i32 0, i32 0)) #8, !dbg !3951
  %cmp94 = icmp eq i32 %call93, 0, !dbg !3952
  br i1 %cmp94, label %if.then100, label %lor.lhs.false96, !dbg !3953

lor.lhs.false96:                                  ; preds = %sw.bb92
  %59 = load i8*, i8** %key, align 8, !dbg !3954
  %call97 = call i32 @strcmp(i8* %59, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.19, i32 0, i32 0)) #8, !dbg !3956
  %cmp98 = icmp eq i32 %call97, 0, !dbg !3957
  br i1 %cmp98, label %if.then100, label %if.end101, !dbg !3958

if.then100:                                       ; preds = %lor.lhs.false96, %sw.bb92
  br label %sw.epilog296, !dbg !3959

if.end101:                                        ; preds = %lor.lhs.false96
  %60 = load i8*, i8** %key, align 8, !dbg !3960
  %call102 = call i32 @strcmp(i8* %60, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.20, i32 0, i32 0)) #8, !dbg !3962
  %cmp103 = icmp eq i32 %call102, 0, !dbg !3963
  br i1 %cmp103, label %if.then105, label %if.end120, !dbg !3964

if.then105:                                       ; preds = %if.end101
  %61 = load i8*, i8** %val, align 8, !dbg !3965
  %arrayidx106 = getelementptr inbounds i8, i8* %61, i64 0, !dbg !3965
  %62 = load i8, i8* %arrayidx106, align 1, !dbg !3965
  %conv107 = sext i8 %62 to i32, !dbg !3965
  %cmp108 = icmp sge i32 %conv107, 48, !dbg !3968
  br i1 %cmp108, label %land.lhs.true, label %if.else, !dbg !3969

land.lhs.true:                                    ; preds = %if.then105
  %63 = load i8*, i8** %val, align 8, !dbg !3970
  %arrayidx110 = getelementptr inbounds i8, i8* %63, i64 0, !dbg !3970
  %64 = load i8, i8* %arrayidx110, align 1, !dbg !3970
  %conv111 = sext i8 %64 to i32, !dbg !3970
  %cmp112 = icmp sle i32 %conv111, 57, !dbg !3972
  br i1 %cmp112, label %if.then114, label %if.else, !dbg !3973

if.then114:                                       ; preds = %land.lhs.true
  %65 = load i32*, i32** %parsed_kws.addr, align 8, !dbg !3974
  %66 = load i32, i32* %65, align 4, !dbg !3976
  %or115 = or i32 %66, 64, !dbg !3976
  store i32 %or115, i32* %65, align 4, !dbg !3976
  %67 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3977
  %call116 = call i64 @mtree_atol8(i8** %val), !dbg !3978
  %conv117 = trunc i64 %call116 to i32, !dbg !3979
  call void @archive_entry_set_perm(%struct.archive_entry* %67, i32 %conv117), !dbg !3980
  br label %if.end119, !dbg !3981

if.else:                                          ; preds = %land.lhs.true, %if.then105
  %68 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3982
  %archive118 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %68, i32 0, i32 0, !dbg !3984
  %69 = load i8*, i8** %val, align 8, !dbg !3985
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive118, i32 84, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.55, i32 0, i32 0), i8* %69), !dbg !3986
  store i32 -20, i32* %retval, align 4, !dbg !3987
  br label %return, !dbg !3987

if.end119:                                        ; preds = %if.then114
  br label %sw.epilog296, !dbg !3988

if.end120:                                        ; preds = %if.end101
  br label %sw.bb121, !dbg !3989

sw.bb121:                                         ; preds = %if.end23, %if.end120
  %70 = load i8*, i8** %key, align 8, !dbg !3991
  %call122 = call i32 @strcmp(i8* %70, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.21, i32 0, i32 0)) #8, !dbg !3993
  %cmp123 = icmp eq i32 %call122, 0, !dbg !3994
  br i1 %cmp123, label %if.then125, label %if.end129, !dbg !3995

if.then125:                                       ; preds = %sw.bb121
  %71 = load i32*, i32** %parsed_kws.addr, align 8, !dbg !3996
  %72 = load i32, i32* %71, align 4, !dbg !3998
  %or126 = or i32 %72, 32, !dbg !3998
  store i32 %or126, i32* %71, align 4, !dbg !3998
  %73 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3999
  %call127 = call i64 @mtree_atol10(i8** %val), !dbg !4000
  %conv128 = trunc i64 %call127 to i32, !dbg !4001
  call void @archive_entry_set_nlink(%struct.archive_entry* %73, i32 %conv128), !dbg !4002
  br label %sw.epilog296, !dbg !4003

if.end129:                                        ; preds = %sw.bb121
  br label %sw.bb130, !dbg !4004

sw.bb130:                                         ; preds = %if.end23, %if.end129
  %74 = load i8*, i8** %key, align 8, !dbg !4006
  %call131 = call i32 @strcmp(i8* %74, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.24, i32 0, i32 0)) #8, !dbg !4008
  %cmp132 = icmp eq i32 %call131, 0, !dbg !4009
  br i1 %cmp132, label %if.then134, label %if.end143, !dbg !4010

if.then134:                                       ; preds = %sw.bb130
  call void @llvm.dbg.declare(metadata i32* %r135, metadata !4011, metadata !460), !dbg !4013
  call void @llvm.dbg.declare(metadata i64* %dev136, metadata !4014, metadata !460), !dbg !4015
  %75 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !4016
  %archive137 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %75, i32 0, i32 0, !dbg !4017
  %76 = load i8*, i8** %val, align 8, !dbg !4018
  %call138 = call i32 @parse_device(i64* %dev136, %struct.archive* %archive137, i8* %76), !dbg !4019
  store i32 %call138, i32* %r135, align 4, !dbg !4020
  %77 = load i32, i32* %r135, align 4, !dbg !4021
  %cmp139 = icmp eq i32 %77, 0, !dbg !4023
  br i1 %cmp139, label %if.then141, label %if.end142, !dbg !4024

if.then141:                                       ; preds = %if.then134
  %78 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4025
  %79 = load i64, i64* %dev136, align 8, !dbg !4026
  call void @archive_entry_set_dev(%struct.archive_entry* %78, i64 %79), !dbg !4027
  br label %if.end142, !dbg !4027

if.end142:                                        ; preds = %if.then141, %if.then134
  %80 = load i32, i32* %r135, align 4, !dbg !4028
  store i32 %80, i32* %retval, align 4, !dbg !4029
  br label %return, !dbg !4029

if.end143:                                        ; preds = %sw.bb130
  %81 = load i8*, i8** %key, align 8, !dbg !4030
  %call144 = call i32 @strcmp(i8* %81, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.25, i32 0, i32 0)) #8, !dbg !4032
  %cmp145 = icmp eq i32 %call144, 0, !dbg !4033
  br i1 %cmp145, label %if.then151, label %lor.lhs.false147, !dbg !4034

lor.lhs.false147:                                 ; preds = %if.end143
  %82 = load i8*, i8** %key, align 8, !dbg !4035
  %call148 = call i32 @strcmp(i8* %82, i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.26, i32 0, i32 0)) #8, !dbg !4036
  %cmp149 = icmp eq i32 %call148, 0, !dbg !4037
  br i1 %cmp149, label %if.then151, label %if.end152, !dbg !4038

if.then151:                                       ; preds = %lor.lhs.false147, %if.end143
  br label %sw.epilog296, !dbg !4039

if.end152:                                        ; preds = %lor.lhs.false147
  br label %sw.bb153, !dbg !4040

sw.bb153:                                         ; preds = %if.end23, %if.end152
  %83 = load i8*, i8** %key, align 8, !dbg !4042
  %call154 = call i32 @strcmp(i8* %83, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.27, i32 0, i32 0)) #8, !dbg !4044
  %cmp155 = icmp eq i32 %call154, 0, !dbg !4045
  br i1 %cmp155, label %if.then161, label %lor.lhs.false157, !dbg !4046

lor.lhs.false157:                                 ; preds = %sw.bb153
  %84 = load i8*, i8** %key, align 8, !dbg !4047
  %call158 = call i32 @strcmp(i8* %84, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.28, i32 0, i32 0)) #8, !dbg !4049
  %cmp159 = icmp eq i32 %call158, 0, !dbg !4050
  br i1 %cmp159, label %if.then161, label %if.end162, !dbg !4051

if.then161:                                       ; preds = %lor.lhs.false157, %sw.bb153
  br label %sw.epilog296, !dbg !4052

if.end162:                                        ; preds = %lor.lhs.false157
  %85 = load i8*, i8** %key, align 8, !dbg !4053
  %call163 = call i32 @strcmp(i8* %85, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.29, i32 0, i32 0)) #8, !dbg !4055
  %cmp164 = icmp eq i32 %call163, 0, !dbg !4056
  br i1 %cmp164, label %if.then170, label %lor.lhs.false166, !dbg !4057

lor.lhs.false166:                                 ; preds = %if.end162
  %86 = load i8*, i8** %key, align 8, !dbg !4058
  %call167 = call i32 @strcmp(i8* %86, i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.30, i32 0, i32 0)) #8, !dbg !4059
  %cmp168 = icmp eq i32 %call167, 0, !dbg !4060
  br i1 %cmp168, label %if.then170, label %if.end171, !dbg !4061

if.then170:                                       ; preds = %lor.lhs.false166, %if.end162
  br label %sw.epilog296, !dbg !4062

if.end171:                                        ; preds = %lor.lhs.false166
  %87 = load i8*, i8** %key, align 8, !dbg !4063
  %call172 = call i32 @strcmp(i8* %87, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.31, i32 0, i32 0)) #8, !dbg !4065
  %cmp173 = icmp eq i32 %call172, 0, !dbg !4066
  br i1 %cmp173, label %if.then179, label %lor.lhs.false175, !dbg !4067

lor.lhs.false175:                                 ; preds = %if.end171
  %88 = load i8*, i8** %key, align 8, !dbg !4068
  %call176 = call i32 @strcmp(i8* %88, i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.32, i32 0, i32 0)) #8, !dbg !4069
  %cmp177 = icmp eq i32 %call176, 0, !dbg !4070
  br i1 %cmp177, label %if.then179, label %if.end180, !dbg !4071

if.then179:                                       ; preds = %lor.lhs.false175, %if.end171
  br label %sw.epilog296, !dbg !4072

if.end180:                                        ; preds = %lor.lhs.false175
  %89 = load i8*, i8** %key, align 8, !dbg !4073
  %call181 = call i32 @strcmp(i8* %89, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.33, i32 0, i32 0)) #8, !dbg !4075
  %cmp182 = icmp eq i32 %call181, 0, !dbg !4076
  br i1 %cmp182, label %if.then188, label %lor.lhs.false184, !dbg !4077

lor.lhs.false184:                                 ; preds = %if.end180
  %90 = load i8*, i8** %key, align 8, !dbg !4078
  %call185 = call i32 @strcmp(i8* %90, i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.34, i32 0, i32 0)) #8, !dbg !4079
  %cmp186 = icmp eq i32 %call185, 0, !dbg !4080
  br i1 %cmp186, label %if.then188, label %if.end189, !dbg !4081

if.then188:                                       ; preds = %lor.lhs.false184, %if.end180
  br label %sw.epilog296, !dbg !4082

if.end189:                                        ; preds = %lor.lhs.false184
  %91 = load i8*, i8** %key, align 8, !dbg !4083
  %call190 = call i32 @strcmp(i8* %91, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.35, i32 0, i32 0)) #8, !dbg !4085
  %cmp191 = icmp eq i32 %call190, 0, !dbg !4086
  br i1 %cmp191, label %if.then193, label %if.end195, !dbg !4087

if.then193:                                       ; preds = %if.end189
  %92 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4088
  %call194 = call i64 @mtree_atol10(i8** %val), !dbg !4090
  call void @archive_entry_set_size(%struct.archive_entry* %92, i64 %call194), !dbg !4091
  br label %sw.epilog296, !dbg !4093

if.end195:                                        ; preds = %if.end189
  br label %sw.bb196, !dbg !4094

sw.bb196:                                         ; preds = %if.end23, %if.end195
  %93 = load i8*, i8** %key, align 8, !dbg !4096
  %call197 = call i32 @strcmp(i8* %93, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.36, i32 0, i32 0)) #8, !dbg !4098
  %cmp198 = icmp eq i32 %call197, 0, !dbg !4099
  br i1 %cmp198, label %if.then200, label %if.end201, !dbg !4100

if.then200:                                       ; preds = %sw.bb196
  br label %sw.epilog296, !dbg !4101

if.end201:                                        ; preds = %sw.bb196
  %94 = load i8*, i8** %key, align 8, !dbg !4103
  %call202 = call i32 @strcmp(i8* %94, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.37, i32 0, i32 0)) #8, !dbg !4105
  %cmp203 = icmp eq i32 %call202, 0, !dbg !4106
  br i1 %cmp203, label %if.then205, label %if.end235, !dbg !4107

if.then205:                                       ; preds = %if.end201
  call void @llvm.dbg.declare(metadata i64* %m, metadata !4108, metadata !460), !dbg !4110
  call void @llvm.dbg.declare(metadata i64* %my_time_t_max, metadata !4111, metadata !460), !dbg !4112
  %call206 = call i64 @get_time_t_max(), !dbg !4113
  store i64 %call206, i64* %my_time_t_max, align 8, !dbg !4112
  call void @llvm.dbg.declare(metadata i64* %my_time_t_min, metadata !4114, metadata !460), !dbg !4115
  %call207 = call i64 @get_time_t_min(), !dbg !4116
  store i64 %call207, i64* %my_time_t_min, align 8, !dbg !4115
  call void @llvm.dbg.declare(metadata i64* %ns, metadata !4117, metadata !460), !dbg !4118
  store i64 0, i64* %ns, align 8, !dbg !4118
  %95 = load i32*, i32** %parsed_kws.addr, align 8, !dbg !4119
  %96 = load i32, i32* %95, align 4, !dbg !4120
  %or208 = or i32 %96, 16, !dbg !4120
  store i32 %or208, i32* %95, align 4, !dbg !4120
  %call209 = call i64 @mtree_atol10(i8** %val), !dbg !4121
  store i64 %call209, i64* %m, align 8, !dbg !4122
  %97 = load i8*, i8** %val, align 8, !dbg !4123
  %98 = load i8, i8* %97, align 1, !dbg !4125
  %conv210 = sext i8 %98 to i32, !dbg !4125
  %cmp211 = icmp eq i32 %conv210, 46, !dbg !4126
  br i1 %cmp211, label %if.then213, label %if.end225, !dbg !4127

if.then213:                                       ; preds = %if.then205
  %99 = load i8*, i8** %val, align 8, !dbg !4128
  %incdec.ptr214 = getelementptr inbounds i8, i8* %99, i32 1, !dbg !4128
  store i8* %incdec.ptr214, i8** %val, align 8, !dbg !4128
  %call215 = call i64 @mtree_atol10(i8** %val), !dbg !4130
  store i64 %call215, i64* %ns, align 8, !dbg !4131
  %100 = load i64, i64* %ns, align 8, !dbg !4132
  %cmp216 = icmp slt i64 %100, 0, !dbg !4134
  br i1 %cmp216, label %if.then218, label %if.else219, !dbg !4135

if.then218:                                       ; preds = %if.then213
  store i64 0, i64* %ns, align 8, !dbg !4136
  br label %if.end224, !dbg !4137

if.else219:                                       ; preds = %if.then213
  %101 = load i64, i64* %ns, align 8, !dbg !4138
  %cmp220 = icmp sgt i64 %101, 999999999, !dbg !4140
  br i1 %cmp220, label %if.then222, label %if.end223, !dbg !4141

if.then222:                                       ; preds = %if.else219
  store i64 999999999, i64* %ns, align 8, !dbg !4142
  br label %if.end223, !dbg !4143

if.end223:                                        ; preds = %if.then222, %if.else219
  br label %if.end224

if.end224:                                        ; preds = %if.end223, %if.then218
  br label %if.end225, !dbg !4144

if.end225:                                        ; preds = %if.end224, %if.then205
  %102 = load i64, i64* %m, align 8, !dbg !4145
  %103 = load i64, i64* %my_time_t_max, align 8, !dbg !4147
  %cmp226 = icmp sgt i64 %102, %103, !dbg !4148
  br i1 %cmp226, label %if.then228, label %if.else229, !dbg !4149

if.then228:                                       ; preds = %if.end225
  %104 = load i64, i64* %my_time_t_max, align 8, !dbg !4150
  store i64 %104, i64* %m, align 8, !dbg !4151
  br label %if.end234, !dbg !4152

if.else229:                                       ; preds = %if.end225
  %105 = load i64, i64* %m, align 8, !dbg !4153
  %106 = load i64, i64* %my_time_t_min, align 8, !dbg !4155
  %cmp230 = icmp slt i64 %105, %106, !dbg !4156
  br i1 %cmp230, label %if.then232, label %if.end233, !dbg !4157

if.then232:                                       ; preds = %if.else229
  %107 = load i64, i64* %my_time_t_min, align 8, !dbg !4158
  store i64 %107, i64* %m, align 8, !dbg !4159
  br label %if.end233, !dbg !4160

if.end233:                                        ; preds = %if.then232, %if.else229
  br label %if.end234

if.end234:                                        ; preds = %if.end233, %if.then228
  %108 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4161
  %109 = load i64, i64* %m, align 8, !dbg !4162
  %110 = load i64, i64* %ns, align 8, !dbg !4163
  call void @archive_entry_set_mtime(%struct.archive_entry* %108, i64 %109, i64 %110), !dbg !4164
  br label %sw.epilog296, !dbg !4165

if.end235:                                        ; preds = %if.end201
  %111 = load i8*, i8** %key, align 8, !dbg !4166
  %call236 = call i32 @strcmp(i8* %111, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.38, i32 0, i32 0)) #8, !dbg !4168
  %cmp237 = icmp eq i32 %call236, 0, !dbg !4169
  br i1 %cmp237, label %if.then239, label %if.end279, !dbg !4170

if.then239:                                       ; preds = %if.end235
  %112 = load i8*, i8** %val, align 8, !dbg !4171
  %arrayidx240 = getelementptr inbounds i8, i8* %112, i64 0, !dbg !4171
  %113 = load i8, i8* %arrayidx240, align 1, !dbg !4171
  %conv241 = sext i8 %113 to i32, !dbg !4171
  switch i32 %conv241, label %sw.default [
    i32 98, label %sw.bb242
    i32 99, label %sw.bb248
    i32 100, label %sw.bb254
    i32 102, label %sw.bb260
    i32 108, label %sw.bb271
  ], !dbg !4173

sw.bb242:                                         ; preds = %if.then239
  %114 = load i8*, i8** %val, align 8, !dbg !4174
  %call243 = call i32 @strcmp(i8* %114, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.56, i32 0, i32 0)) #8, !dbg !4177
  %cmp244 = icmp eq i32 %call243, 0, !dbg !4178
  br i1 %cmp244, label %if.then246, label %if.end247, !dbg !4179

if.then246:                                       ; preds = %sw.bb242
  %115 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4180
  call void @archive_entry_set_filetype(%struct.archive_entry* %115, i32 24576), !dbg !4182
  br label %sw.epilog, !dbg !4183

if.end247:                                        ; preds = %sw.bb242
  br label %sw.bb248, !dbg !4184

sw.bb248:                                         ; preds = %if.then239, %if.end247
  %116 = load i8*, i8** %val, align 8, !dbg !4186
  %call249 = call i32 @strcmp(i8* %116, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.57, i32 0, i32 0)) #8, !dbg !4188
  %cmp250 = icmp eq i32 %call249, 0, !dbg !4189
  br i1 %cmp250, label %if.then252, label %if.end253, !dbg !4190

if.then252:                                       ; preds = %sw.bb248
  %117 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4191
  call void @archive_entry_set_filetype(%struct.archive_entry* %117, i32 8192), !dbg !4193
  br label %sw.epilog, !dbg !4194

if.end253:                                        ; preds = %sw.bb248
  br label %sw.bb254, !dbg !4195

sw.bb254:                                         ; preds = %if.then239, %if.end253
  %118 = load i8*, i8** %val, align 8, !dbg !4197
  %call255 = call i32 @strcmp(i8* %118, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.58, i32 0, i32 0)) #8, !dbg !4199
  %cmp256 = icmp eq i32 %call255, 0, !dbg !4200
  br i1 %cmp256, label %if.then258, label %if.end259, !dbg !4201

if.then258:                                       ; preds = %sw.bb254
  %119 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4202
  call void @archive_entry_set_filetype(%struct.archive_entry* %119, i32 16384), !dbg !4204
  br label %sw.epilog, !dbg !4205

if.end259:                                        ; preds = %sw.bb254
  br label %sw.bb260, !dbg !4206

sw.bb260:                                         ; preds = %if.then239, %if.end259
  %120 = load i8*, i8** %val, align 8, !dbg !4208
  %call261 = call i32 @strcmp(i8* %120, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.59, i32 0, i32 0)) #8, !dbg !4210
  %cmp262 = icmp eq i32 %call261, 0, !dbg !4211
  br i1 %cmp262, label %if.then264, label %if.end265, !dbg !4212

if.then264:                                       ; preds = %sw.bb260
  %121 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4213
  call void @archive_entry_set_filetype(%struct.archive_entry* %121, i32 4096), !dbg !4215
  br label %sw.epilog, !dbg !4216

if.end265:                                        ; preds = %sw.bb260
  %122 = load i8*, i8** %val, align 8, !dbg !4217
  %call266 = call i32 @strcmp(i8* %122, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.60, i32 0, i32 0)) #8, !dbg !4219
  %cmp267 = icmp eq i32 %call266, 0, !dbg !4220
  br i1 %cmp267, label %if.then269, label %if.end270, !dbg !4221

if.then269:                                       ; preds = %if.end265
  %123 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4222
  call void @archive_entry_set_filetype(%struct.archive_entry* %123, i32 32768), !dbg !4224
  br label %sw.epilog, !dbg !4225

if.end270:                                        ; preds = %if.end265
  br label %sw.bb271, !dbg !4226

sw.bb271:                                         ; preds = %if.then239, %if.end270
  %124 = load i8*, i8** %val, align 8, !dbg !4228
  %call272 = call i32 @strcmp(i8* %124, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.17, i32 0, i32 0)) #8, !dbg !4230
  %cmp273 = icmp eq i32 %call272, 0, !dbg !4231
  br i1 %cmp273, label %if.then275, label %if.end276, !dbg !4232

if.then275:                                       ; preds = %sw.bb271
  %125 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4233
  call void @archive_entry_set_filetype(%struct.archive_entry* %125, i32 40960), !dbg !4235
  br label %sw.epilog, !dbg !4236

if.end276:                                        ; preds = %sw.bb271
  br label %sw.default, !dbg !4237

sw.default:                                       ; preds = %if.then239, %if.end276
  %126 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !4239
  %archive277 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %126, i32 0, i32 0, !dbg !4240
  %127 = load i8*, i8** %val, align 8, !dbg !4241
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive277, i32 84, i8* getelementptr inbounds ([45 x i8], [45 x i8]* @.str.61, i32 0, i32 0), i8* %127), !dbg !4242
  %128 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4243
  call void @archive_entry_set_filetype(%struct.archive_entry* %128, i32 32768), !dbg !4244
  store i32 -20, i32* %retval, align 4, !dbg !4245
  br label %return, !dbg !4245

sw.epilog:                                        ; preds = %if.then275, %if.then269, %if.then264, %if.then258, %if.then252, %if.then246
  %129 = load i32*, i32** %parsed_kws.addr, align 8, !dbg !4246
  %130 = load i32, i32* %129, align 4, !dbg !4247
  %or278 = or i32 %130, 256, !dbg !4247
  store i32 %or278, i32* %129, align 4, !dbg !4247
  br label %sw.epilog296, !dbg !4248

if.end279:                                        ; preds = %if.end235
  br label %sw.bb280, !dbg !4249

sw.bb280:                                         ; preds = %if.end23, %if.end279
  %131 = load i8*, i8** %key, align 8, !dbg !4251
  %call281 = call i32 @strcmp(i8* %131, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.39, i32 0, i32 0)) #8, !dbg !4253
  %cmp282 = icmp eq i32 %call281, 0, !dbg !4254
  br i1 %cmp282, label %if.then284, label %if.end287, !dbg !4255

if.then284:                                       ; preds = %sw.bb280
  %132 = load i32*, i32** %parsed_kws.addr, align 8, !dbg !4256
  %133 = load i32, i32* %132, align 4, !dbg !4258
  %or285 = or i32 %133, 512, !dbg !4258
  store i32 %or285, i32* %132, align 4, !dbg !4258
  %134 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4259
  %call286 = call i64 @mtree_atol10(i8** %val), !dbg !4260
  call void @archive_entry_set_uid(%struct.archive_entry* %134, i64 %call286), !dbg !4261
  br label %sw.epilog296, !dbg !4263

if.end287:                                        ; preds = %sw.bb280
  %135 = load i8*, i8** %key, align 8, !dbg !4264
  %call288 = call i32 @strcmp(i8* %135, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.40, i32 0, i32 0)) #8, !dbg !4266
  %cmp289 = icmp eq i32 %call288, 0, !dbg !4267
  br i1 %cmp289, label %if.then291, label %if.end293, !dbg !4268

if.then291:                                       ; preds = %if.end287
  %136 = load i32*, i32** %parsed_kws.addr, align 8, !dbg !4269
  %137 = load i32, i32* %136, align 4, !dbg !4271
  %or292 = or i32 %137, 1024, !dbg !4271
  store i32 %or292, i32* %136, align 4, !dbg !4271
  %138 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4272
  %139 = load i8*, i8** %val, align 8, !dbg !4273
  call void @archive_entry_copy_uname(%struct.archive_entry* %138, i8* %139), !dbg !4274
  br label %sw.epilog296, !dbg !4275

if.end293:                                        ; preds = %if.end287
  br label %sw.default294, !dbg !4276

sw.default294:                                    ; preds = %if.end23, %if.end293
  %140 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !4278
  %archive295 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %140, i32 0, i32 0, !dbg !4279
  %141 = load i8*, i8** %key, align 8, !dbg !4280
  %142 = load i8*, i8** %val, align 8, !dbg !4281
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive295, i32 84, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.62, i32 0, i32 0), i8* %141, i8* %142), !dbg !4282
  store i32 -20, i32* %retval, align 4, !dbg !4283
  br label %return, !dbg !4283

sw.epilog296:                                     ; preds = %if.then291, %if.then284, %sw.epilog, %if.end234, %if.then200, %if.then193, %if.then188, %if.then179, %if.then170, %if.then161, %if.then151, %if.then125, %if.end119, %if.then100, %if.then90, %if.then83, %if.then76, %if.then69, %if.then61, %if.then42, %cond.end
  store i32 0, i32* %retval, align 4, !dbg !4284
  br label %return, !dbg !4284

return:                                           ; preds = %sw.epilog296, %sw.default294, %sw.default, %if.end142, %if.else, %if.end55, %if.then21, %if.then16, %if.then10, %if.then5, %if.then
  %143 = load i32, i32* %retval, align 4, !dbg !4285
  ret i32 %143, !dbg !4285
}

declare %struct.archive_string* @archive_strncat(%struct.archive_string*, i8*, i64) #2

; Function Attrs: nounwind uwtable
define internal i32 @parse_device(i64* %pdev, %struct.archive* %a, i8* %val) #0 !dbg !410 {
entry:
  %retval = alloca i32, align 4
  %pdev.addr = alloca i64*, align 8
  %a.addr = alloca %struct.archive*, align 8
  %val.addr = alloca i8*, align 8
  %numbers = alloca [3 x i64], align 16
  %p = alloca i8*, align 8
  %dev = alloca i8*, align 8
  %argc = alloca i32, align 4
  %pack = alloca i64 (i32, i64*, i8**)*, align 8
  %result = alloca i64, align 8
  %error = alloca i8*, align 8
  store i64* %pdev, i64** %pdev.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %pdev.addr, metadata !4286, metadata !460), !dbg !4287
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !4288, metadata !460), !dbg !4289
  store i8* %val, i8** %val.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %val.addr, metadata !4290, metadata !460), !dbg !4291
  call void @llvm.dbg.declare(metadata [3 x i64]* %numbers, metadata !4292, metadata !460), !dbg !4294
  call void @llvm.dbg.declare(metadata i8** %p, metadata !4295, metadata !460), !dbg !4296
  call void @llvm.dbg.declare(metadata i8** %dev, metadata !4297, metadata !460), !dbg !4298
  call void @llvm.dbg.declare(metadata i32* %argc, metadata !4299, metadata !460), !dbg !4300
  call void @llvm.dbg.declare(metadata i64 (i32, i64*, i8**)** %pack, metadata !4301, metadata !460), !dbg !4308
  call void @llvm.dbg.declare(metadata i64* %result, metadata !4309, metadata !460), !dbg !4310
  call void @llvm.dbg.declare(metadata i8** %error, metadata !4311, metadata !460), !dbg !4312
  store i8* null, i8** %error, align 8, !dbg !4312
  %0 = load i64*, i64** %pdev.addr, align 8, !dbg !4313
  %1 = bitcast i64* %0 to i8*, !dbg !4314
  call void @llvm.memset.p0i8.i64(i8* %1, i8 0, i64 8, i32 8, i1 false), !dbg !4314
  %2 = load i8*, i8** %val.addr, align 8, !dbg !4315
  %call = call i8* @strchr(i8* %2, i32 44) #8, !dbg !4317
  store i8* %call, i8** %dev, align 8, !dbg !4318
  %cmp = icmp ne i8* %call, null, !dbg !4319
  br i1 %cmp, label %if.then, label %if.else, !dbg !4320

if.then:                                          ; preds = %entry
  %3 = load i8*, i8** %dev, align 8, !dbg !4321
  %incdec.ptr = getelementptr inbounds i8, i8* %3, i32 1, !dbg !4321
  store i8* %incdec.ptr, i8** %dev, align 8, !dbg !4321
  store i8 0, i8* %3, align 1, !dbg !4323
  %4 = load i8*, i8** %val.addr, align 8, !dbg !4324
  %call1 = call i64 (i32, i64*, i8**)* @pack_find(i8* %4), !dbg !4326
  store i64 (i32, i64*, i8**)* %call1, i64 (i32, i64*, i8**)** %pack, align 8, !dbg !4327
  %cmp2 = icmp eq i64 (i32, i64*, i8**)* %call1, null, !dbg !4328
  br i1 %cmp2, label %if.then3, label %if.end, !dbg !4329

if.then3:                                         ; preds = %if.then
  %5 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !4330
  %6 = load i8*, i8** %val.addr, align 8, !dbg !4332
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %5, i32 84, i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.63, i32 0, i32 0), i8* %6), !dbg !4333
  store i32 -20, i32* %retval, align 4, !dbg !4334
  br label %return, !dbg !4334

if.end:                                           ; preds = %if.then
  store i32 0, i32* %argc, align 4, !dbg !4335
  br label %while.cond, !dbg !4336

while.cond:                                       ; preds = %if.end13, %if.end
  %call4 = call i8* @la_strsep(i8** %dev, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.64, i32 0, i32 0)), !dbg !4337
  store i8* %call4, i8** %p, align 8, !dbg !4339
  %cmp5 = icmp ne i8* %call4, null, !dbg !4340
  br i1 %cmp5, label %while.body, label %while.end, !dbg !4341

while.body:                                       ; preds = %while.cond
  %7 = load i8*, i8** %p, align 8, !dbg !4342
  %8 = load i8, i8* %7, align 1, !dbg !4345
  %conv = sext i8 %8 to i32, !dbg !4345
  %cmp6 = icmp eq i32 %conv, 0, !dbg !4346
  br i1 %cmp6, label %if.then8, label %if.end9, !dbg !4347

if.then8:                                         ; preds = %while.body
  %9 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !4348
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %9, i32 84, i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.65, i32 0, i32 0)), !dbg !4350
  store i32 -20, i32* %retval, align 4, !dbg !4351
  br label %return, !dbg !4351

if.end9:                                          ; preds = %while.body
  %10 = load i32, i32* %argc, align 4, !dbg !4352
  %cmp10 = icmp sge i32 %10, 3, !dbg !4354
  br i1 %cmp10, label %if.then12, label %if.end13, !dbg !4355

if.then12:                                        ; preds = %if.end9
  %11 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !4356
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %11, i32 84, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.66, i32 0, i32 0)), !dbg !4358
  store i32 -20, i32* %retval, align 4, !dbg !4359
  br label %return, !dbg !4359

if.end13:                                         ; preds = %if.end9
  %call14 = call i64 @mtree_atol(i8** %p), !dbg !4360
  %12 = load i32, i32* %argc, align 4, !dbg !4361
  %inc = add nsw i32 %12, 1, !dbg !4361
  store i32 %inc, i32* %argc, align 4, !dbg !4361
  %idxprom = sext i32 %12 to i64, !dbg !4362
  %arrayidx = getelementptr inbounds [3 x i64], [3 x i64]* %numbers, i64 0, i64 %idxprom, !dbg !4362
  store i64 %call14, i64* %arrayidx, align 8, !dbg !4363
  br label %while.cond, !dbg !4364

while.end:                                        ; preds = %while.cond
  %13 = load i32, i32* %argc, align 4, !dbg !4366
  %cmp15 = icmp slt i32 %13, 2, !dbg !4368
  br i1 %cmp15, label %if.then17, label %if.end18, !dbg !4369

if.then17:                                        ; preds = %while.end
  %14 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !4370
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %14, i32 84, i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.67, i32 0, i32 0)), !dbg !4372
  store i32 -20, i32* %retval, align 4, !dbg !4373
  br label %return, !dbg !4373

if.end18:                                         ; preds = %while.end
  %15 = load i64 (i32, i64*, i8**)*, i64 (i32, i64*, i8**)** %pack, align 8, !dbg !4374
  %16 = load i32, i32* %argc, align 4, !dbg !4375
  %arraydecay = getelementptr inbounds [3 x i64], [3 x i64]* %numbers, i32 0, i32 0, !dbg !4376
  %call19 = call i64 %15(i32 %16, i64* %arraydecay, i8** %error), !dbg !4377
  store i64 %call19, i64* %result, align 8, !dbg !4378
  %17 = load i8*, i8** %error, align 8, !dbg !4379
  %cmp20 = icmp ne i8* %17, null, !dbg !4381
  br i1 %cmp20, label %if.then22, label %if.end23, !dbg !4382

if.then22:                                        ; preds = %if.end18
  %18 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !4383
  %19 = load i8*, i8** %error, align 8, !dbg !4385
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %18, i32 84, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.68, i32 0, i32 0), i8* %19), !dbg !4386
  store i32 -20, i32* %retval, align 4, !dbg !4387
  br label %return, !dbg !4387

if.end23:                                         ; preds = %if.end18
  br label %if.end25, !dbg !4388

if.else:                                          ; preds = %entry
  %call24 = call i64 @mtree_atol(i8** %val.addr), !dbg !4389
  store i64 %call24, i64* %result, align 8, !dbg !4391
  br label %if.end25

if.end25:                                         ; preds = %if.else, %if.end23
  %20 = load i64, i64* %result, align 8, !dbg !4392
  %21 = load i64*, i64** %pdev.addr, align 8, !dbg !4393
  store i64 %20, i64* %21, align 8, !dbg !4394
  store i32 0, i32* %retval, align 4, !dbg !4395
  br label %return, !dbg !4395

return:                                           ; preds = %if.end25, %if.then22, %if.then17, %if.then12, %if.then8, %if.then3
  %22 = load i32, i32* %retval, align 4, !dbg !4396
  ret i32 %22, !dbg !4396
}

declare i8* @archive_entry_copy_fflags_text(%struct.archive_entry*, i8*) #2

; Function Attrs: nounwind uwtable
define internal i64 @mtree_atol10(i8** %p) #0 !dbg !424 {
entry:
  %retval = alloca i64, align 8
  %p.addr = alloca i8**, align 8
  %l = alloca i64, align 8
  %limit = alloca i64, align 8
  %last_digit_limit = alloca i64, align 8
  %base = alloca i32, align 4
  %digit = alloca i32, align 4
  %sign = alloca i32, align 4
  store i8** %p, i8*** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %p.addr, metadata !4397, metadata !460), !dbg !4398
  call void @llvm.dbg.declare(metadata i64* %l, metadata !4399, metadata !460), !dbg !4400
  call void @llvm.dbg.declare(metadata i64* %limit, metadata !4401, metadata !460), !dbg !4402
  call void @llvm.dbg.declare(metadata i64* %last_digit_limit, metadata !4403, metadata !460), !dbg !4404
  call void @llvm.dbg.declare(metadata i32* %base, metadata !4405, metadata !460), !dbg !4406
  call void @llvm.dbg.declare(metadata i32* %digit, metadata !4407, metadata !460), !dbg !4408
  call void @llvm.dbg.declare(metadata i32* %sign, metadata !4409, metadata !460), !dbg !4410
  store i32 10, i32* %base, align 4, !dbg !4411
  %0 = load i8**, i8*** %p.addr, align 8, !dbg !4412
  %1 = load i8*, i8** %0, align 8, !dbg !4414
  %2 = load i8, i8* %1, align 1, !dbg !4415
  %conv = sext i8 %2 to i32, !dbg !4415
  %cmp = icmp eq i32 %conv, 45, !dbg !4416
  br i1 %cmp, label %if.then, label %if.else, !dbg !4417

if.then:                                          ; preds = %entry
  store i32 -1, i32* %sign, align 4, !dbg !4418
  %3 = load i32, i32* %base, align 4, !dbg !4420
  %conv2 = sext i32 %3 to i64, !dbg !4420
  %div = udiv i64 -9223372036854775808, %conv2, !dbg !4421
  store i64 %div, i64* %limit, align 8, !dbg !4422
  %4 = load i32, i32* %base, align 4, !dbg !4423
  %conv3 = sext i32 %4 to i64, !dbg !4423
  %rem = urem i64 -9223372036854775808, %conv3, !dbg !4424
  store i64 %rem, i64* %last_digit_limit, align 8, !dbg !4425
  %5 = load i8**, i8*** %p.addr, align 8, !dbg !4426
  %6 = load i8*, i8** %5, align 8, !dbg !4427
  %incdec.ptr = getelementptr inbounds i8, i8* %6, i32 1, !dbg !4427
  store i8* %incdec.ptr, i8** %5, align 8, !dbg !4427
  br label %if.end, !dbg !4428

if.else:                                          ; preds = %entry
  store i32 1, i32* %sign, align 4, !dbg !4429
  %7 = load i32, i32* %base, align 4, !dbg !4431
  %conv4 = sext i32 %7 to i64, !dbg !4431
  %div5 = sdiv i64 9223372036854775807, %conv4, !dbg !4432
  store i64 %div5, i64* %limit, align 8, !dbg !4433
  %8 = load i32, i32* %base, align 4, !dbg !4434
  %conv6 = sext i32 %8 to i64, !dbg !4434
  %rem7 = srem i64 9223372036854775807, %conv6, !dbg !4435
  store i64 %rem7, i64* %last_digit_limit, align 8, !dbg !4436
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  store i64 0, i64* %l, align 8, !dbg !4437
  %9 = load i8**, i8*** %p.addr, align 8, !dbg !4438
  %10 = load i8*, i8** %9, align 8, !dbg !4439
  %11 = load i8, i8* %10, align 1, !dbg !4440
  %conv8 = sext i8 %11 to i32, !dbg !4440
  %sub = sub nsw i32 %conv8, 48, !dbg !4441
  store i32 %sub, i32* %digit, align 4, !dbg !4442
  br label %while.cond, !dbg !4443

while.cond:                                       ; preds = %if.end23, %if.end
  %12 = load i32, i32* %digit, align 4, !dbg !4444
  %cmp9 = icmp sge i32 %12, 0, !dbg !4446
  br i1 %cmp9, label %land.rhs, label %land.end, !dbg !4447

land.rhs:                                         ; preds = %while.cond
  %13 = load i32, i32* %digit, align 4, !dbg !4448
  %14 = load i32, i32* %base, align 4, !dbg !4450
  %cmp11 = icmp slt i32 %13, %14, !dbg !4451
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond
  %15 = phi i1 [ false, %while.cond ], [ %cmp11, %land.rhs ]
  br i1 %15, label %while.body, label %while.end, !dbg !4452

while.body:                                       ; preds = %land.end
  %16 = load i64, i64* %l, align 8, !dbg !4454
  %17 = load i64, i64* %limit, align 8, !dbg !4457
  %cmp13 = icmp sgt i64 %16, %17, !dbg !4458
  br i1 %cmp13, label %if.then20, label %lor.lhs.false, !dbg !4459

lor.lhs.false:                                    ; preds = %while.body
  %18 = load i64, i64* %l, align 8, !dbg !4460
  %19 = load i64, i64* %limit, align 8, !dbg !4462
  %cmp15 = icmp eq i64 %18, %19, !dbg !4463
  br i1 %cmp15, label %land.lhs.true, label %if.end23, !dbg !4464

land.lhs.true:                                    ; preds = %lor.lhs.false
  %20 = load i32, i32* %digit, align 4, !dbg !4465
  %conv17 = sext i32 %20 to i64, !dbg !4465
  %21 = load i64, i64* %last_digit_limit, align 8, !dbg !4467
  %cmp18 = icmp sgt i64 %conv17, %21, !dbg !4468
  br i1 %cmp18, label %if.then20, label %if.end23, !dbg !4469

if.then20:                                        ; preds = %land.lhs.true, %while.body
  %22 = load i32, i32* %sign, align 4, !dbg !4470
  %cmp21 = icmp slt i32 %22, 0, !dbg !4471
  %cond = select i1 %cmp21, i64 -9223372036854775808, i64 9223372036854775807, !dbg !4472
  store i64 %cond, i64* %retval, align 8, !dbg !4473
  br label %return, !dbg !4473

if.end23:                                         ; preds = %land.lhs.true, %lor.lhs.false
  %23 = load i64, i64* %l, align 8, !dbg !4474
  %24 = load i32, i32* %base, align 4, !dbg !4475
  %conv24 = sext i32 %24 to i64, !dbg !4475
  %mul = mul nsw i64 %23, %conv24, !dbg !4476
  %25 = load i32, i32* %digit, align 4, !dbg !4477
  %conv25 = sext i32 %25 to i64, !dbg !4477
  %add = add nsw i64 %mul, %conv25, !dbg !4478
  store i64 %add, i64* %l, align 8, !dbg !4479
  %26 = load i8**, i8*** %p.addr, align 8, !dbg !4480
  %27 = load i8*, i8** %26, align 8, !dbg !4481
  %incdec.ptr26 = getelementptr inbounds i8, i8* %27, i32 1, !dbg !4481
  store i8* %incdec.ptr26, i8** %26, align 8, !dbg !4481
  %28 = load i8, i8* %incdec.ptr26, align 1, !dbg !4482
  %conv27 = sext i8 %28 to i32, !dbg !4482
  %sub28 = sub nsw i32 %conv27, 48, !dbg !4483
  store i32 %sub28, i32* %digit, align 4, !dbg !4484
  br label %while.cond, !dbg !4485

while.end:                                        ; preds = %land.end
  %29 = load i32, i32* %sign, align 4, !dbg !4487
  %cmp29 = icmp slt i32 %29, 0, !dbg !4488
  br i1 %cmp29, label %cond.true, label %cond.false, !dbg !4489

cond.true:                                        ; preds = %while.end
  %30 = load i64, i64* %l, align 8, !dbg !4490
  %sub31 = sub nsw i64 0, %30, !dbg !4491
  br label %cond.end, !dbg !4492

cond.false:                                       ; preds = %while.end
  %31 = load i64, i64* %l, align 8, !dbg !4493
  br label %cond.end, !dbg !4494

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond32 = phi i64 [ %sub31, %cond.true ], [ %31, %cond.false ], !dbg !4495
  store i64 %cond32, i64* %retval, align 8, !dbg !4496
  br label %return, !dbg !4496

return:                                           ; preds = %cond.end, %if.then20
  %32 = load i64, i64* %retval, align 8, !dbg !4497
  ret i64 %32, !dbg !4497
}

declare void @archive_entry_copy_gname(%struct.archive_entry*, i8*) #2

declare void @archive_entry_copy_symlink(%struct.archive_entry*, i8*) #2

; Function Attrs: nounwind uwtable
define internal i64 @mtree_atol8(i8** %p) #0 !dbg !425 {
entry:
  %p.addr = alloca i8**, align 8
  %l = alloca i64, align 8
  %limit = alloca i64, align 8
  %last_digit_limit = alloca i64, align 8
  %digit = alloca i32, align 4
  %base = alloca i32, align 4
  store i8** %p, i8*** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %p.addr, metadata !4498, metadata !460), !dbg !4499
  call void @llvm.dbg.declare(metadata i64* %l, metadata !4500, metadata !460), !dbg !4501
  call void @llvm.dbg.declare(metadata i64* %limit, metadata !4502, metadata !460), !dbg !4503
  call void @llvm.dbg.declare(metadata i64* %last_digit_limit, metadata !4504, metadata !460), !dbg !4505
  call void @llvm.dbg.declare(metadata i32* %digit, metadata !4506, metadata !460), !dbg !4507
  call void @llvm.dbg.declare(metadata i32* %base, metadata !4508, metadata !460), !dbg !4509
  store i32 8, i32* %base, align 4, !dbg !4510
  %0 = load i32, i32* %base, align 4, !dbg !4511
  %conv = sext i32 %0 to i64, !dbg !4511
  %div = sdiv i64 9223372036854775807, %conv, !dbg !4512
  store i64 %div, i64* %limit, align 8, !dbg !4513
  %1 = load i32, i32* %base, align 4, !dbg !4514
  %conv1 = sext i32 %1 to i64, !dbg !4514
  %rem = srem i64 9223372036854775807, %conv1, !dbg !4515
  store i64 %rem, i64* %last_digit_limit, align 8, !dbg !4516
  store i64 0, i64* %l, align 8, !dbg !4517
  %2 = load i8**, i8*** %p.addr, align 8, !dbg !4518
  %3 = load i8*, i8** %2, align 8, !dbg !4519
  %4 = load i8, i8* %3, align 1, !dbg !4520
  %conv2 = sext i8 %4 to i32, !dbg !4520
  %sub = sub nsw i32 %conv2, 48, !dbg !4521
  store i32 %sub, i32* %digit, align 4, !dbg !4522
  br label %while.cond, !dbg !4523

while.cond:                                       ; preds = %if.end, %entry
  %5 = load i32, i32* %digit, align 4, !dbg !4524
  %cmp = icmp sge i32 %5, 0, !dbg !4526
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !4527

land.rhs:                                         ; preds = %while.cond
  %6 = load i32, i32* %digit, align 4, !dbg !4528
  %7 = load i32, i32* %base, align 4, !dbg !4530
  %cmp4 = icmp slt i32 %6, %7, !dbg !4531
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond
  %8 = phi i1 [ false, %while.cond ], [ %cmp4, %land.rhs ]
  br i1 %8, label %while.body, label %while.end, !dbg !4532

while.body:                                       ; preds = %land.end
  %9 = load i64, i64* %l, align 8, !dbg !4534
  %10 = load i64, i64* %limit, align 8, !dbg !4537
  %cmp6 = icmp sgt i64 %9, %10, !dbg !4538
  br i1 %cmp6, label %if.then, label %lor.lhs.false, !dbg !4539

lor.lhs.false:                                    ; preds = %while.body
  %11 = load i64, i64* %l, align 8, !dbg !4540
  %12 = load i64, i64* %limit, align 8, !dbg !4542
  %cmp8 = icmp eq i64 %11, %12, !dbg !4543
  br i1 %cmp8, label %land.lhs.true, label %if.end, !dbg !4544

land.lhs.true:                                    ; preds = %lor.lhs.false
  %13 = load i32, i32* %digit, align 4, !dbg !4545
  %conv10 = sext i32 %13 to i64, !dbg !4545
  %14 = load i64, i64* %last_digit_limit, align 8, !dbg !4547
  %cmp11 = icmp sgt i64 %conv10, %14, !dbg !4548
  br i1 %cmp11, label %if.then, label %if.end, !dbg !4549

if.then:                                          ; preds = %land.lhs.true, %while.body
  store i64 9223372036854775807, i64* %l, align 8, !dbg !4550
  br label %while.end, !dbg !4552

if.end:                                           ; preds = %land.lhs.true, %lor.lhs.false
  %15 = load i64, i64* %l, align 8, !dbg !4553
  %16 = load i32, i32* %base, align 4, !dbg !4554
  %conv13 = sext i32 %16 to i64, !dbg !4554
  %mul = mul nsw i64 %15, %conv13, !dbg !4555
  %17 = load i32, i32* %digit, align 4, !dbg !4556
  %conv14 = sext i32 %17 to i64, !dbg !4556
  %add = add nsw i64 %mul, %conv14, !dbg !4557
  store i64 %add, i64* %l, align 8, !dbg !4558
  %18 = load i8**, i8*** %p.addr, align 8, !dbg !4559
  %19 = load i8*, i8** %18, align 8, !dbg !4560
  %incdec.ptr = getelementptr inbounds i8, i8* %19, i32 1, !dbg !4560
  store i8* %incdec.ptr, i8** %18, align 8, !dbg !4560
  %20 = load i8, i8* %incdec.ptr, align 1, !dbg !4561
  %conv15 = sext i8 %20 to i32, !dbg !4561
  %sub16 = sub nsw i32 %conv15, 48, !dbg !4562
  store i32 %sub16, i32* %digit, align 4, !dbg !4563
  br label %while.cond, !dbg !4564

while.end:                                        ; preds = %if.then, %land.end
  %21 = load i64, i64* %l, align 8, !dbg !4566
  ret i64 %21, !dbg !4567
}

; Function Attrs: nounwind uwtable
define internal i64 @get_time_t_max() #0 !dbg !426 {
entry:
  ret i64 9223372036854775807, !dbg !4568
}

; Function Attrs: nounwind uwtable
define internal i64 @get_time_t_min() #0 !dbg !429 {
entry:
  ret i64 -9223372036854775808, !dbg !4573
}

declare void @archive_entry_copy_uname(%struct.archive_entry*, i8*) #2

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #5

declare i64 (i32, i64*, i8**)* @pack_find(i8*) #2

; Function Attrs: nounwind uwtable
define internal i8* @la_strsep(i8** %sp, i8* %sep) #0 !dbg !414 {
entry:
  %retval = alloca i8*, align 8
  %sp.addr = alloca i8**, align 8
  %sep.addr = alloca i8*, align 8
  %p = alloca i8*, align 8
  %s = alloca i8*, align 8
  store i8** %sp, i8*** %sp.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %sp.addr, metadata !4578, metadata !460), !dbg !4579
  store i8* %sep, i8** %sep.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %sep.addr, metadata !4580, metadata !460), !dbg !4581
  call void @llvm.dbg.declare(metadata i8** %p, metadata !4582, metadata !460), !dbg !4583
  call void @llvm.dbg.declare(metadata i8** %s, metadata !4584, metadata !460), !dbg !4585
  %0 = load i8**, i8*** %sp.addr, align 8, !dbg !4586
  %cmp = icmp eq i8** %0, null, !dbg !4588
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !4589

lor.lhs.false:                                    ; preds = %entry
  %1 = load i8**, i8*** %sp.addr, align 8, !dbg !4590
  %2 = load i8*, i8** %1, align 8, !dbg !4592
  %cmp1 = icmp eq i8* %2, null, !dbg !4593
  br i1 %cmp1, label %if.then, label %lor.lhs.false2, !dbg !4594

lor.lhs.false2:                                   ; preds = %lor.lhs.false
  %3 = load i8**, i8*** %sp.addr, align 8, !dbg !4595
  %4 = load i8*, i8** %3, align 8, !dbg !4597
  %5 = load i8, i8* %4, align 1, !dbg !4598
  %conv = sext i8 %5 to i32, !dbg !4598
  %cmp3 = icmp eq i32 %conv, 0, !dbg !4599
  br i1 %cmp3, label %if.then, label %if.end, !dbg !4600

if.then:                                          ; preds = %lor.lhs.false2, %lor.lhs.false, %entry
  store i8* null, i8** %retval, align 8, !dbg !4601
  br label %return, !dbg !4601

if.end:                                           ; preds = %lor.lhs.false2
  %6 = load i8**, i8*** %sp.addr, align 8, !dbg !4602
  %7 = load i8*, i8** %6, align 8, !dbg !4603
  store i8* %7, i8** %s, align 8, !dbg !4604
  %8 = load i8*, i8** %s, align 8, !dbg !4605
  %9 = load i8*, i8** %s, align 8, !dbg !4606
  %10 = load i8*, i8** %sep.addr, align 8, !dbg !4607
  %call = call i64 @strcspn(i8* %9, i8* %10) #8, !dbg !4608
  %add.ptr = getelementptr inbounds i8, i8* %8, i64 %call, !dbg !4609
  store i8* %add.ptr, i8** %p, align 8, !dbg !4610
  %11 = load i8*, i8** %p, align 8, !dbg !4611
  %12 = load i8, i8* %11, align 1, !dbg !4613
  %conv5 = sext i8 %12 to i32, !dbg !4613
  %cmp6 = icmp ne i32 %conv5, 0, !dbg !4614
  br i1 %cmp6, label %if.then8, label %if.end9, !dbg !4615

if.then8:                                         ; preds = %if.end
  %13 = load i8*, i8** %p, align 8, !dbg !4616
  %incdec.ptr = getelementptr inbounds i8, i8* %13, i32 1, !dbg !4616
  store i8* %incdec.ptr, i8** %p, align 8, !dbg !4616
  store i8 0, i8* %13, align 1, !dbg !4617
  br label %if.end9, !dbg !4618

if.end9:                                          ; preds = %if.then8, %if.end
  %14 = load i8*, i8** %p, align 8, !dbg !4619
  %15 = load i8**, i8*** %sp.addr, align 8, !dbg !4620
  store i8* %14, i8** %15, align 8, !dbg !4621
  %16 = load i8*, i8** %s, align 8, !dbg !4622
  store i8* %16, i8** %retval, align 8, !dbg !4623
  br label %return, !dbg !4623

return:                                           ; preds = %if.end9, %if.then
  %17 = load i8*, i8** %retval, align 8, !dbg !4624
  ret i8* %17, !dbg !4624
}

; Function Attrs: nounwind uwtable
define internal i64 @mtree_atol(i8** %p) #0 !dbg !417 {
entry:
  %retval = alloca i64, align 8
  %p.addr = alloca i8**, align 8
  store i8** %p, i8*** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %p.addr, metadata !4625, metadata !460), !dbg !4626
  %0 = load i8**, i8*** %p.addr, align 8, !dbg !4627
  %1 = load i8*, i8** %0, align 8, !dbg !4629
  %2 = load i8, i8* %1, align 1, !dbg !4630
  %conv = sext i8 %2 to i32, !dbg !4630
  %cmp = icmp ne i32 %conv, 48, !dbg !4631
  br i1 %cmp, label %if.then, label %if.end, !dbg !4632

if.then:                                          ; preds = %entry
  %3 = load i8**, i8*** %p.addr, align 8, !dbg !4633
  %call = call i64 @mtree_atol10(i8** %3), !dbg !4634
  store i64 %call, i64* %retval, align 8, !dbg !4635
  br label %return, !dbg !4635

if.end:                                           ; preds = %entry
  %4 = load i8**, i8*** %p.addr, align 8, !dbg !4636
  %5 = load i8*, i8** %4, align 8, !dbg !4638
  %arrayidx = getelementptr inbounds i8, i8* %5, i64 1, !dbg !4639
  %6 = load i8, i8* %arrayidx, align 1, !dbg !4639
  %conv2 = sext i8 %6 to i32, !dbg !4639
  %cmp3 = icmp eq i32 %conv2, 120, !dbg !4640
  br i1 %cmp3, label %if.then9, label %lor.lhs.false, !dbg !4641

lor.lhs.false:                                    ; preds = %if.end
  %7 = load i8**, i8*** %p.addr, align 8, !dbg !4642
  %8 = load i8*, i8** %7, align 8, !dbg !4644
  %arrayidx5 = getelementptr inbounds i8, i8* %8, i64 1, !dbg !4645
  %9 = load i8, i8* %arrayidx5, align 1, !dbg !4645
  %conv6 = sext i8 %9 to i32, !dbg !4645
  %cmp7 = icmp eq i32 %conv6, 88, !dbg !4646
  br i1 %cmp7, label %if.then9, label %if.end11, !dbg !4647

if.then9:                                         ; preds = %lor.lhs.false, %if.end
  %10 = load i8**, i8*** %p.addr, align 8, !dbg !4648
  %11 = load i8*, i8** %10, align 8, !dbg !4650
  %add.ptr = getelementptr inbounds i8, i8* %11, i64 2, !dbg !4650
  store i8* %add.ptr, i8** %10, align 8, !dbg !4650
  %12 = load i8**, i8*** %p.addr, align 8, !dbg !4651
  %call10 = call i64 @mtree_atol16(i8** %12), !dbg !4652
  store i64 %call10, i64* %retval, align 8, !dbg !4653
  br label %return, !dbg !4653

if.end11:                                         ; preds = %lor.lhs.false
  %13 = load i8**, i8*** %p.addr, align 8, !dbg !4654
  %call12 = call i64 @mtree_atol8(i8** %13), !dbg !4655
  store i64 %call12, i64* %retval, align 8, !dbg !4656
  br label %return, !dbg !4656

return:                                           ; preds = %if.end11, %if.then9, %if.then
  %14 = load i64, i64* %retval, align 8, !dbg !4657
  ret i64 %14, !dbg !4657
}

; Function Attrs: nounwind uwtable
define internal i64 @mtree_atol16(i8** %p) #0 !dbg !420 {
entry:
  %retval = alloca i64, align 8
  %p.addr = alloca i8**, align 8
  %l = alloca i64, align 8
  %limit = alloca i64, align 8
  %last_digit_limit = alloca i64, align 8
  %base = alloca i32, align 4
  %digit = alloca i32, align 4
  %sign = alloca i32, align 4
  store i8** %p, i8*** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %p.addr, metadata !4658, metadata !460), !dbg !4659
  call void @llvm.dbg.declare(metadata i64* %l, metadata !4660, metadata !460), !dbg !4661
  call void @llvm.dbg.declare(metadata i64* %limit, metadata !4662, metadata !460), !dbg !4663
  call void @llvm.dbg.declare(metadata i64* %last_digit_limit, metadata !4664, metadata !460), !dbg !4665
  call void @llvm.dbg.declare(metadata i32* %base, metadata !4666, metadata !460), !dbg !4667
  call void @llvm.dbg.declare(metadata i32* %digit, metadata !4668, metadata !460), !dbg !4669
  call void @llvm.dbg.declare(metadata i32* %sign, metadata !4670, metadata !460), !dbg !4671
  store i32 16, i32* %base, align 4, !dbg !4672
  %0 = load i8**, i8*** %p.addr, align 8, !dbg !4673
  %1 = load i8*, i8** %0, align 8, !dbg !4675
  %2 = load i8, i8* %1, align 1, !dbg !4676
  %conv = sext i8 %2 to i32, !dbg !4676
  %cmp = icmp eq i32 %conv, 45, !dbg !4677
  br i1 %cmp, label %if.then, label %if.else, !dbg !4678

if.then:                                          ; preds = %entry
  store i32 -1, i32* %sign, align 4, !dbg !4679
  %3 = load i32, i32* %base, align 4, !dbg !4681
  %conv2 = sext i32 %3 to i64, !dbg !4681
  %div = udiv i64 -9223372036854775808, %conv2, !dbg !4682
  store i64 %div, i64* %limit, align 8, !dbg !4683
  %4 = load i32, i32* %base, align 4, !dbg !4684
  %conv3 = sext i32 %4 to i64, !dbg !4684
  %rem = urem i64 -9223372036854775808, %conv3, !dbg !4685
  store i64 %rem, i64* %last_digit_limit, align 8, !dbg !4686
  %5 = load i8**, i8*** %p.addr, align 8, !dbg !4687
  %6 = load i8*, i8** %5, align 8, !dbg !4688
  %incdec.ptr = getelementptr inbounds i8, i8* %6, i32 1, !dbg !4688
  store i8* %incdec.ptr, i8** %5, align 8, !dbg !4688
  br label %if.end, !dbg !4689

if.else:                                          ; preds = %entry
  store i32 1, i32* %sign, align 4, !dbg !4690
  %7 = load i32, i32* %base, align 4, !dbg !4692
  %conv4 = sext i32 %7 to i64, !dbg !4692
  %div5 = sdiv i64 9223372036854775807, %conv4, !dbg !4693
  store i64 %div5, i64* %limit, align 8, !dbg !4694
  %8 = load i32, i32* %base, align 4, !dbg !4695
  %conv6 = sext i32 %8 to i64, !dbg !4695
  %rem7 = srem i64 9223372036854775807, %conv6, !dbg !4696
  store i64 %rem7, i64* %last_digit_limit, align 8, !dbg !4697
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  store i64 0, i64* %l, align 8, !dbg !4698
  %9 = load i8**, i8*** %p.addr, align 8, !dbg !4699
  %10 = load i8*, i8** %9, align 8, !dbg !4700
  %11 = load i8, i8* %10, align 1, !dbg !4701
  %call = call i32 @parsehex(i8 signext %11), !dbg !4702
  store i32 %call, i32* %digit, align 4, !dbg !4703
  br label %while.cond, !dbg !4704

while.cond:                                       ; preds = %if.end22, %if.end
  %12 = load i32, i32* %digit, align 4, !dbg !4705
  %cmp8 = icmp sge i32 %12, 0, !dbg !4707
  br i1 %cmp8, label %land.rhs, label %land.end, !dbg !4708

land.rhs:                                         ; preds = %while.cond
  %13 = load i32, i32* %digit, align 4, !dbg !4709
  %14 = load i32, i32* %base, align 4, !dbg !4711
  %cmp10 = icmp slt i32 %13, %14, !dbg !4712
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond
  %15 = phi i1 [ false, %while.cond ], [ %cmp10, %land.rhs ]
  br i1 %15, label %while.body, label %while.end, !dbg !4713

while.body:                                       ; preds = %land.end
  %16 = load i64, i64* %l, align 8, !dbg !4715
  %17 = load i64, i64* %limit, align 8, !dbg !4718
  %cmp12 = icmp sgt i64 %16, %17, !dbg !4719
  br i1 %cmp12, label %if.then19, label %lor.lhs.false, !dbg !4720

lor.lhs.false:                                    ; preds = %while.body
  %18 = load i64, i64* %l, align 8, !dbg !4721
  %19 = load i64, i64* %limit, align 8, !dbg !4723
  %cmp14 = icmp eq i64 %18, %19, !dbg !4724
  br i1 %cmp14, label %land.lhs.true, label %if.end22, !dbg !4725

land.lhs.true:                                    ; preds = %lor.lhs.false
  %20 = load i32, i32* %digit, align 4, !dbg !4726
  %conv16 = sext i32 %20 to i64, !dbg !4726
  %21 = load i64, i64* %last_digit_limit, align 8, !dbg !4728
  %cmp17 = icmp sgt i64 %conv16, %21, !dbg !4729
  br i1 %cmp17, label %if.then19, label %if.end22, !dbg !4730

if.then19:                                        ; preds = %land.lhs.true, %while.body
  %22 = load i32, i32* %sign, align 4, !dbg !4731
  %cmp20 = icmp slt i32 %22, 0, !dbg !4732
  %cond = select i1 %cmp20, i64 -9223372036854775808, i64 9223372036854775807, !dbg !4733
  store i64 %cond, i64* %retval, align 8, !dbg !4734
  br label %return, !dbg !4734

if.end22:                                         ; preds = %land.lhs.true, %lor.lhs.false
  %23 = load i64, i64* %l, align 8, !dbg !4735
  %24 = load i32, i32* %base, align 4, !dbg !4736
  %conv23 = sext i32 %24 to i64, !dbg !4736
  %mul = mul nsw i64 %23, %conv23, !dbg !4737
  %25 = load i32, i32* %digit, align 4, !dbg !4738
  %conv24 = sext i32 %25 to i64, !dbg !4738
  %add = add nsw i64 %mul, %conv24, !dbg !4739
  store i64 %add, i64* %l, align 8, !dbg !4740
  %26 = load i8**, i8*** %p.addr, align 8, !dbg !4741
  %27 = load i8*, i8** %26, align 8, !dbg !4742
  %incdec.ptr25 = getelementptr inbounds i8, i8* %27, i32 1, !dbg !4742
  store i8* %incdec.ptr25, i8** %26, align 8, !dbg !4742
  %28 = load i8, i8* %incdec.ptr25, align 1, !dbg !4743
  %call26 = call i32 @parsehex(i8 signext %28), !dbg !4744
  store i32 %call26, i32* %digit, align 4, !dbg !4745
  br label %while.cond, !dbg !4746

while.end:                                        ; preds = %land.end
  %29 = load i32, i32* %sign, align 4, !dbg !4748
  %cmp27 = icmp slt i32 %29, 0, !dbg !4749
  br i1 %cmp27, label %cond.true, label %cond.false, !dbg !4750

cond.true:                                        ; preds = %while.end
  %30 = load i64, i64* %l, align 8, !dbg !4751
  %sub = sub nsw i64 0, %30, !dbg !4752
  br label %cond.end, !dbg !4753

cond.false:                                       ; preds = %while.end
  %31 = load i64, i64* %l, align 8, !dbg !4754
  br label %cond.end, !dbg !4755

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond29 = phi i64 [ %sub, %cond.true ], [ %31, %cond.false ], !dbg !4756
  store i64 %cond29, i64* %retval, align 8, !dbg !4757
  br label %return, !dbg !4757

return:                                           ; preds = %cond.end, %if.then19
  %32 = load i64, i64* %retval, align 8, !dbg !4758
  ret i64 %32, !dbg !4758
}

; Function Attrs: nounwind uwtable
define internal i32 @parsehex(i8 signext %c) #0 !dbg !421 {
entry:
  %retval = alloca i32, align 4
  %c.addr = alloca i8, align 1
  store i8 %c, i8* %c.addr, align 1
  call void @llvm.dbg.declare(metadata i8* %c.addr, metadata !4759, metadata !460), !dbg !4760
  %0 = load i8, i8* %c.addr, align 1, !dbg !4761
  %conv = sext i8 %0 to i32, !dbg !4761
  %cmp = icmp sge i32 %conv, 48, !dbg !4763
  br i1 %cmp, label %land.lhs.true, label %if.else, !dbg !4764

land.lhs.true:                                    ; preds = %entry
  %1 = load i8, i8* %c.addr, align 1, !dbg !4765
  %conv2 = sext i8 %1 to i32, !dbg !4765
  %cmp3 = icmp sle i32 %conv2, 57, !dbg !4767
  br i1 %cmp3, label %if.then, label %if.else, !dbg !4768

if.then:                                          ; preds = %land.lhs.true
  %2 = load i8, i8* %c.addr, align 1, !dbg !4769
  %conv5 = sext i8 %2 to i32, !dbg !4769
  %sub = sub nsw i32 %conv5, 48, !dbg !4770
  store i32 %sub, i32* %retval, align 4, !dbg !4771
  br label %return, !dbg !4771

if.else:                                          ; preds = %land.lhs.true, %entry
  %3 = load i8, i8* %c.addr, align 1, !dbg !4772
  %conv6 = sext i8 %3 to i32, !dbg !4772
  %cmp7 = icmp sge i32 %conv6, 97, !dbg !4774
  br i1 %cmp7, label %land.lhs.true9, label %if.else16, !dbg !4775

land.lhs.true9:                                   ; preds = %if.else
  %4 = load i8, i8* %c.addr, align 1, !dbg !4776
  %conv10 = sext i8 %4 to i32, !dbg !4776
  %cmp11 = icmp sle i32 %conv10, 102, !dbg !4778
  br i1 %cmp11, label %if.then13, label %if.else16, !dbg !4779

if.then13:                                        ; preds = %land.lhs.true9
  %5 = load i8, i8* %c.addr, align 1, !dbg !4780
  %conv14 = sext i8 %5 to i32, !dbg !4780
  %sub15 = sub nsw i32 %conv14, 97, !dbg !4781
  store i32 %sub15, i32* %retval, align 4, !dbg !4782
  br label %return, !dbg !4782

if.else16:                                        ; preds = %land.lhs.true9, %if.else
  %6 = load i8, i8* %c.addr, align 1, !dbg !4783
  %conv17 = sext i8 %6 to i32, !dbg !4783
  %cmp18 = icmp sge i32 %conv17, 65, !dbg !4785
  br i1 %cmp18, label %land.lhs.true20, label %if.else27, !dbg !4786

land.lhs.true20:                                  ; preds = %if.else16
  %7 = load i8, i8* %c.addr, align 1, !dbg !4787
  %conv21 = sext i8 %7 to i32, !dbg !4787
  %cmp22 = icmp sle i32 %conv21, 70, !dbg !4789
  br i1 %cmp22, label %if.then24, label %if.else27, !dbg !4790

if.then24:                                        ; preds = %land.lhs.true20
  %8 = load i8, i8* %c.addr, align 1, !dbg !4791
  %conv25 = sext i8 %8 to i32, !dbg !4791
  %sub26 = sub nsw i32 %conv25, 65, !dbg !4792
  store i32 %sub26, i32* %retval, align 4, !dbg !4793
  br label %return, !dbg !4793

if.else27:                                        ; preds = %land.lhs.true20, %if.else16
  store i32 -1, i32* %retval, align 4, !dbg !4794
  br label %return, !dbg !4794

return:                                           ; preds = %if.else27, %if.then24, %if.then13, %if.then
  %9 = load i32, i32* %retval, align 4, !dbg !4795
  ret i32 %9, !dbg !4795
}

declare i64 @read(i32, i8*, i64) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { argmemonly nounwind }
attributes #6 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { nounwind }
attributes #8 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!456, !457}
!llvm.ident = !{!458}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !342, globals: !432)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_support_format_mtree.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !291, !122, !23, !45, !330, !80, !333, !13, !42, !336, !47, !339, !341, !52}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !5, size: 64, align: 64)
!5 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read", file: !6, line: 159, size: 20288, align: 64, elements: !7)
!6 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!7 = !{!8, !110, !111, !112, !113, !114, !158, !222, !223, !224, !225, !226, !227, !260, !262, !272, !273}
!8 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !5, file: !6, line: 160, baseType: !9, size: 1280, align: 64)
!9 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !10, line: 89, size: 1280, align: 64, elements: !11)
!10 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!11 = !{!12, !14, !15, !83, !84, !85, !86, !87, !88, !89, !90, !98, !99, !100, !101, !104, !105, !106, !107, !108, !109}
!12 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !9, file: !10, line: 96, baseType: !13, size: 32, align: 32)
!13 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!14 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !9, file: !10, line: 97, baseType: !13, size: 32, align: 32, offset: 32)
!15 = !DIDerivedType(tag: DW_TAG_member, name: "vtable", scope: !9, file: !10, line: 103, baseType: !16, size: 64, align: 64, offset: 64)
!16 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !17, size: 64, align: 64)
!17 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_vtable", file: !10, line: 63, size: 832, align: 64, elements: !18)
!18 = !{!19, !25, !26, !33, !34, !48, !54, !59, !60, !67, !68, !72, !76}
!19 = !DIDerivedType(tag: DW_TAG_member, name: "archive_close", scope: !17, file: !10, line: 64, baseType: !20, size: 64, align: 64)
!20 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !21, size: 64, align: 64)
!21 = !DISubroutineType(types: !22)
!22 = !{!23, !24}
!23 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!24 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64, align: 64)
!25 = !DIDerivedType(tag: DW_TAG_member, name: "archive_free", scope: !17, file: !10, line: 65, baseType: !20, size: 64, align: 64, offset: 64)
!26 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_header", scope: !17, file: !10, line: 66, baseType: !27, size: 64, align: 64, offset: 128)
!27 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !28, size: 64, align: 64)
!28 = !DISubroutineType(types: !29)
!29 = !{!23, !24, !30}
!30 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !31, size: 64, align: 64)
!31 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_entry", file: !32, line: 180, flags: DIFlagFwdDecl)
!32 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!33 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_finish_entry", scope: !17, file: !10, line: 68, baseType: !20, size: 64, align: 64, offset: 192)
!34 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data", scope: !17, file: !10, line: 69, baseType: !35, size: 64, align: 64, offset: 256)
!35 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !36, size: 64, align: 64)
!36 = !DISubroutineType(types: !37)
!37 = !{!38, !24, !43, !45}
!38 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !39, line: 109, baseType: !40)
!39 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!40 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !41, line: 172, baseType: !42)
!41 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!42 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!43 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !44, size: 64, align: 64)
!44 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!45 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !46, line: 62, baseType: !47)
!46 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!47 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!48 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data_block", scope: !17, file: !10, line: 71, baseType: !49, size: 64, align: 64, offset: 320)
!49 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !50, size: 64, align: 64)
!50 = !DISubroutineType(types: !51)
!51 = !{!38, !24, !43, !45, !52}
!52 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !53, line: 40, baseType: !42)
!53 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!54 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header", scope: !17, file: !10, line: 74, baseType: !55, size: 64, align: 64, offset: 384)
!55 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !56, size: 64, align: 64)
!56 = !DISubroutineType(types: !57)
!57 = !{!23, !24, !58}
!58 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !30, size: 64, align: 64)
!59 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header2", scope: !17, file: !10, line: 76, baseType: !27, size: 64, align: 64, offset: 448)
!60 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_data_block", scope: !17, file: !10, line: 78, baseType: !61, size: 64, align: 64, offset: 512)
!61 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !62, size: 64, align: 64)
!62 = !DISubroutineType(types: !63)
!63 = !{!23, !24, !64, !65, !66}
!64 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !43, size: 64, align: 64)
!65 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !45, size: 64, align: 64)
!66 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !52, size: 64, align: 64)
!67 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_count", scope: !17, file: !10, line: 81, baseType: !20, size: 64, align: 64, offset: 576)
!68 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_bytes", scope: !17, file: !10, line: 82, baseType: !69, size: 64, align: 64, offset: 640)
!69 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !70, size: 64, align: 64)
!70 = !DISubroutineType(types: !71)
!71 = !{!52, !24, !23}
!72 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_code", scope: !17, file: !10, line: 83, baseType: !73, size: 64, align: 64, offset: 704)
!73 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !74, size: 64, align: 64)
!74 = !DISubroutineType(types: !75)
!75 = !{!23, !24, !23}
!76 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_name", scope: !17, file: !10, line: 84, baseType: !77, size: 64, align: 64, offset: 768)
!77 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !78, size: 64, align: 64)
!78 = !DISubroutineType(types: !79)
!79 = !{!80, !24, !23}
!80 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !81, size: 64, align: 64)
!81 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !82)
!82 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format", scope: !9, file: !10, line: 105, baseType: !23, size: 32, align: 32, offset: 128)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format_name", scope: !9, file: !10, line: 106, baseType: !80, size: 64, align: 64, offset: 192)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "compression_code", scope: !9, file: !10, line: 108, baseType: !23, size: 32, align: 32, offset: 256)
!86 = !DIDerivedType(tag: DW_TAG_member, name: "compression_name", scope: !9, file: !10, line: 109, baseType: !80, size: 64, align: 64, offset: 320)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "file_count", scope: !9, file: !10, line: 112, baseType: !23, size: 32, align: 32, offset: 384)
!88 = !DIDerivedType(tag: DW_TAG_member, name: "archive_error_number", scope: !9, file: !10, line: 114, baseType: !23, size: 32, align: 32, offset: 416)
!89 = !DIDerivedType(tag: DW_TAG_member, name: "error", scope: !9, file: !10, line: 115, baseType: !80, size: 64, align: 64, offset: 448)
!90 = !DIDerivedType(tag: DW_TAG_member, name: "error_string", scope: !9, file: !10, line: 116, baseType: !91, size: 192, align: 64, offset: 512)
!91 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string", file: !92, line: 58, size: 192, align: 64, elements: !93)
!92 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_string.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!93 = !{!94, !96, !97}
!94 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !91, file: !92, line: 59, baseType: !95, size: 64, align: 64)
!95 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !82, size: 64, align: 64)
!96 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !91, file: !92, line: 60, baseType: !45, size: 64, align: 64, offset: 64)
!97 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !91, file: !92, line: 61, baseType: !45, size: 64, align: 64, offset: 128)
!98 = !DIDerivedType(tag: DW_TAG_member, name: "current_code", scope: !9, file: !10, line: 118, baseType: !95, size: 64, align: 64, offset: 704)
!99 = !DIDerivedType(tag: DW_TAG_member, name: "current_codepage", scope: !9, file: !10, line: 119, baseType: !13, size: 32, align: 32, offset: 768)
!100 = !DIDerivedType(tag: DW_TAG_member, name: "current_oemcp", scope: !9, file: !10, line: 120, baseType: !13, size: 32, align: 32, offset: 800)
!101 = !DIDerivedType(tag: DW_TAG_member, name: "sconv", scope: !9, file: !10, line: 121, baseType: !102, size: 64, align: 64, offset: 832)
!102 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !103, size: 64, align: 64)
!103 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string_conv", file: !92, line: 70, flags: DIFlagFwdDecl)
!104 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_block", scope: !9, file: !10, line: 127, baseType: !80, size: 64, align: 64, offset: 896)
!105 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_offset", scope: !9, file: !10, line: 128, baseType: !52, size: 64, align: 64, offset: 960)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_output_offset", scope: !9, file: !10, line: 129, baseType: !52, size: 64, align: 64, offset: 1024)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_remaining", scope: !9, file: !10, line: 130, baseType: !45, size: 64, align: 64, offset: 1088)
!108 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_is_posix_read", scope: !9, file: !10, line: 137, baseType: !82, size: 8, align: 8, offset: 1152)
!109 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_requested", scope: !9, file: !10, line: 138, baseType: !45, size: 64, align: 64, offset: 1216)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "entry", scope: !5, file: !6, line: 162, baseType: !30, size: 64, align: 64, offset: 1280)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_set", scope: !5, file: !6, line: 165, baseType: !23, size: 32, align: 32, offset: 1344)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_dev", scope: !5, file: !6, line: 166, baseType: !52, size: 64, align: 64, offset: 1408)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_ino", scope: !5, file: !6, line: 167, baseType: !52, size: 64, align: 64, offset: 1472)
!114 = !DIDerivedType(tag: DW_TAG_member, name: "client", scope: !5, file: !6, line: 170, baseType: !115, size: 576, align: 64, offset: 1536)
!115 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_client", file: !6, line: 134, size: 576, align: 64, elements: !116)
!116 = !{!117, !123, !129, !135, !140, !143, !148, !149, !150, !151}
!117 = !DIDerivedType(tag: DW_TAG_member, name: "opener", scope: !115, file: !6, line: 135, baseType: !118, size: 64, align: 64)
!118 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !119, size: 64, align: 64)
!119 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_open_callback", file: !32, line: 241, baseType: !120)
!120 = !DISubroutineType(types: !121)
!121 = !{!23, !24, !122}
!122 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!123 = !DIDerivedType(tag: DW_TAG_member, name: "reader", scope: !115, file: !6, line: 136, baseType: !124, size: 64, align: 64, offset: 64)
!124 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !125, size: 64, align: 64)
!125 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_read_callback", file: !32, line: 218, baseType: !126)
!126 = !DISubroutineType(types: !127)
!127 = !{!128, !24, !122, !64}
!128 = !DIDerivedType(tag: DW_TAG_typedef, name: "la_ssize_t", file: !32, line: 95, baseType: !38)
!129 = !DIDerivedType(tag: DW_TAG_member, name: "skipper", scope: !115, file: !6, line: 137, baseType: !130, size: 64, align: 64, offset: 128)
!130 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !131, size: 64, align: 64)
!131 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_skip_callback", file: !32, line: 226, baseType: !132)
!132 = !DISubroutineType(types: !133)
!133 = !{!134, !24, !122, !134}
!134 = !DIDerivedType(tag: DW_TAG_typedef, name: "la_int64_t", file: !32, line: 73, baseType: !52)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "seeker", scope: !115, file: !6, line: 138, baseType: !136, size: 64, align: 64, offset: 192)
!136 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !137, size: 64, align: 64)
!137 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_seek_callback", file: !32, line: 233, baseType: !138)
!138 = !DISubroutineType(types: !139)
!139 = !{!134, !24, !122, !134, !23}
!140 = !DIDerivedType(tag: DW_TAG_member, name: "closer", scope: !115, file: !6, line: 139, baseType: !141, size: 64, align: 64, offset: 256)
!141 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !142, size: 64, align: 64)
!142 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_close_callback", file: !32, line: 243, baseType: !120)
!143 = !DIDerivedType(tag: DW_TAG_member, name: "switcher", scope: !115, file: !6, line: 140, baseType: !144, size: 64, align: 64, offset: 320)
!144 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !145, size: 64, align: 64)
!145 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_switch_callback", file: !32, line: 249, baseType: !146)
!146 = !DISubroutineType(types: !147)
!147 = !{!23, !24, !122, !122}
!148 = !DIDerivedType(tag: DW_TAG_member, name: "nodes", scope: !115, file: !6, line: 141, baseType: !13, size: 32, align: 32, offset: 384)
!149 = !DIDerivedType(tag: DW_TAG_member, name: "cursor", scope: !115, file: !6, line: 142, baseType: !13, size: 32, align: 32, offset: 416)
!150 = !DIDerivedType(tag: DW_TAG_member, name: "position", scope: !115, file: !6, line: 143, baseType: !52, size: 64, align: 64, offset: 448)
!151 = !DIDerivedType(tag: DW_TAG_member, name: "dataset", scope: !115, file: !6, line: 144, baseType: !152, size: 64, align: 64, offset: 512)
!152 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !153, size: 64, align: 64)
!153 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_data_node", file: !6, line: 129, size: 192, align: 64, elements: !154)
!154 = !{!155, !156, !157}
!155 = !DIDerivedType(tag: DW_TAG_member, name: "begin_position", scope: !153, file: !6, line: 130, baseType: !52, size: 64, align: 64)
!156 = !DIDerivedType(tag: DW_TAG_member, name: "total_size", scope: !153, file: !6, line: 131, baseType: !52, size: 64, align: 64, offset: 64)
!157 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !153, file: !6, line: 132, baseType: !122, size: 64, align: 64, offset: 128)
!158 = !DIDerivedType(tag: DW_TAG_member, name: "bidders", scope: !5, file: !6, line: 173, baseType: !159, size: 6144, align: 64, offset: 2112)
!159 = !DICompositeType(tag: DW_TAG_array_type, baseType: !160, size: 6144, align: 64, elements: !220)
!160 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_filter_bidder", file: !6, line: 60, size: 384, align: 64, elements: !161)
!161 = !{!162, !163, !164, !211, !212, !216}
!162 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !160, file: !6, line: 62, baseType: !122, size: 64, align: 64)
!163 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !160, file: !6, line: 64, baseType: !80, size: 64, align: 64, offset: 64)
!164 = !DIDerivedType(tag: DW_TAG_member, name: "bid", scope: !160, file: !6, line: 66, baseType: !165, size: 64, align: 64, offset: 128)
!165 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !166, size: 64, align: 64)
!166 = !DISubroutineType(types: !167)
!167 = !{!23, !168, !169}
!168 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !160, size: 64, align: 64)
!169 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !170, size: 64, align: 64)
!170 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_filter", file: !6, line: 82, size: 1408, align: 64, elements: !171)
!171 = !{!172, !173, !174, !175, !176, !180, !184, !188, !192, !193, !197, !198, !199, !200, !201, !202, !203, !204, !205, !206, !207, !208, !209, !210}
!172 = !DIDerivedType(tag: DW_TAG_member, name: "position", scope: !170, file: !6, line: 83, baseType: !52, size: 64, align: 64)
!173 = !DIDerivedType(tag: DW_TAG_member, name: "bidder", scope: !170, file: !6, line: 86, baseType: !168, size: 64, align: 64, offset: 64)
!174 = !DIDerivedType(tag: DW_TAG_member, name: "upstream", scope: !170, file: !6, line: 87, baseType: !169, size: 64, align: 64, offset: 128)
!175 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !170, file: !6, line: 88, baseType: !4, size: 64, align: 64, offset: 192)
!176 = !DIDerivedType(tag: DW_TAG_member, name: "open", scope: !170, file: !6, line: 90, baseType: !177, size: 64, align: 64, offset: 256)
!177 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !178, size: 64, align: 64)
!178 = !DISubroutineType(types: !179)
!179 = !{!23, !169}
!180 = !DIDerivedType(tag: DW_TAG_member, name: "read", scope: !170, file: !6, line: 92, baseType: !181, size: 64, align: 64, offset: 320)
!181 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !182, size: 64, align: 64)
!182 = !DISubroutineType(types: !183)
!183 = !{!38, !169, !64}
!184 = !DIDerivedType(tag: DW_TAG_member, name: "skip", scope: !170, file: !6, line: 94, baseType: !185, size: 64, align: 64, offset: 384)
!185 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !186, size: 64, align: 64)
!186 = !DISubroutineType(types: !187)
!187 = !{!52, !169, !52}
!188 = !DIDerivedType(tag: DW_TAG_member, name: "seek", scope: !170, file: !6, line: 96, baseType: !189, size: 64, align: 64, offset: 448)
!189 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !190, size: 64, align: 64)
!190 = !DISubroutineType(types: !191)
!191 = !{!52, !169, !52, !23}
!192 = !DIDerivedType(tag: DW_TAG_member, name: "close", scope: !170, file: !6, line: 98, baseType: !177, size: 64, align: 64, offset: 512)
!193 = !DIDerivedType(tag: DW_TAG_member, name: "sswitch", scope: !170, file: !6, line: 100, baseType: !194, size: 64, align: 64, offset: 576)
!194 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !195, size: 64, align: 64)
!195 = !DISubroutineType(types: !196)
!196 = !{!23, !169, !13}
!197 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !170, file: !6, line: 102, baseType: !122, size: 64, align: 64, offset: 640)
!198 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !170, file: !6, line: 104, baseType: !80, size: 64, align: 64, offset: 704)
!199 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !170, file: !6, line: 105, baseType: !23, size: 32, align: 32, offset: 768)
!200 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !170, file: !6, line: 108, baseType: !95, size: 64, align: 64, offset: 832)
!201 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_size", scope: !170, file: !6, line: 109, baseType: !45, size: 64, align: 64, offset: 896)
!202 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !170, file: !6, line: 110, baseType: !95, size: 64, align: 64, offset: 960)
!203 = !DIDerivedType(tag: DW_TAG_member, name: "avail", scope: !170, file: !6, line: 111, baseType: !45, size: 64, align: 64, offset: 1024)
!204 = !DIDerivedType(tag: DW_TAG_member, name: "client_buff", scope: !170, file: !6, line: 112, baseType: !43, size: 64, align: 64, offset: 1088)
!205 = !DIDerivedType(tag: DW_TAG_member, name: "client_total", scope: !170, file: !6, line: 113, baseType: !45, size: 64, align: 64, offset: 1152)
!206 = !DIDerivedType(tag: DW_TAG_member, name: "client_next", scope: !170, file: !6, line: 114, baseType: !80, size: 64, align: 64, offset: 1216)
!207 = !DIDerivedType(tag: DW_TAG_member, name: "client_avail", scope: !170, file: !6, line: 115, baseType: !45, size: 64, align: 64, offset: 1280)
!208 = !DIDerivedType(tag: DW_TAG_member, name: "end_of_file", scope: !170, file: !6, line: 116, baseType: !82, size: 8, align: 8, offset: 1344)
!209 = !DIDerivedType(tag: DW_TAG_member, name: "closed", scope: !170, file: !6, line: 117, baseType: !82, size: 8, align: 8, offset: 1352)
!210 = !DIDerivedType(tag: DW_TAG_member, name: "fatal", scope: !170, file: !6, line: 118, baseType: !82, size: 8, align: 8, offset: 1360)
!211 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !160, file: !6, line: 69, baseType: !177, size: 64, align: 64, offset: 192)
!212 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !160, file: !6, line: 71, baseType: !213, size: 64, align: 64, offset: 256)
!213 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !214, size: 64, align: 64)
!214 = !DISubroutineType(types: !215)
!215 = !{!23, !168, !80, !80}
!216 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !160, file: !6, line: 74, baseType: !217, size: 64, align: 64, offset: 320)
!217 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !218, size: 64, align: 64)
!218 = !DISubroutineType(types: !219)
!219 = !{!23, !168}
!220 = !{!221}
!221 = !DISubrange(count: 16)
!222 = !DIDerivedType(tag: DW_TAG_member, name: "filter", scope: !5, file: !6, line: 176, baseType: !169, size: 64, align: 64, offset: 8256)
!223 = !DIDerivedType(tag: DW_TAG_member, name: "bypass_filter_bidding", scope: !5, file: !6, line: 179, baseType: !23, size: 32, align: 32, offset: 8320)
!224 = !DIDerivedType(tag: DW_TAG_member, name: "header_position", scope: !5, file: !6, line: 182, baseType: !52, size: 64, align: 64, offset: 8384)
!225 = !DIDerivedType(tag: DW_TAG_member, name: "data_start_node", scope: !5, file: !6, line: 185, baseType: !13, size: 32, align: 32, offset: 8448)
!226 = !DIDerivedType(tag: DW_TAG_member, name: "data_end_node", scope: !5, file: !6, line: 186, baseType: !13, size: 32, align: 32, offset: 8480)
!227 = !DIDerivedType(tag: DW_TAG_member, name: "formats", scope: !5, file: !6, line: 209, baseType: !228, size: 11264, align: 64, offset: 8512)
!228 = !DICompositeType(tag: DW_TAG_array_type, baseType: !229, size: 11264, align: 64, elements: !220)
!229 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_format_descriptor", file: !6, line: 196, size: 704, align: 64, elements: !230)
!230 = !{!231, !232, !233, !237, !241, !245, !249, !253, !257, !258, !259}
!231 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !229, file: !6, line: 197, baseType: !122, size: 64, align: 64)
!232 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !229, file: !6, line: 198, baseType: !80, size: 64, align: 64, offset: 64)
!233 = !DIDerivedType(tag: DW_TAG_member, name: "bid", scope: !229, file: !6, line: 199, baseType: !234, size: 64, align: 64, offset: 128)
!234 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !235, size: 64, align: 64)
!235 = !DISubroutineType(types: !236)
!236 = !{!23, !4, !23}
!237 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !229, file: !6, line: 200, baseType: !238, size: 64, align: 64, offset: 192)
!238 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !239, size: 64, align: 64)
!239 = !DISubroutineType(types: !240)
!240 = !{!23, !4, !80, !80}
!241 = !DIDerivedType(tag: DW_TAG_member, name: "read_header", scope: !229, file: !6, line: 202, baseType: !242, size: 64, align: 64, offset: 256)
!242 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !243, size: 64, align: 64)
!243 = !DISubroutineType(types: !244)
!244 = !{!23, !4, !30}
!245 = !DIDerivedType(tag: DW_TAG_member, name: "read_data", scope: !229, file: !6, line: 203, baseType: !246, size: 64, align: 64, offset: 320)
!246 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !247, size: 64, align: 64)
!247 = !DISubroutineType(types: !248)
!248 = !{!23, !4, !64, !65, !66}
!249 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_skip", scope: !229, file: !6, line: 204, baseType: !250, size: 64, align: 64, offset: 384)
!250 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !251, size: 64, align: 64)
!251 = !DISubroutineType(types: !252)
!252 = !{!23, !4}
!253 = !DIDerivedType(tag: DW_TAG_member, name: "seek_data", scope: !229, file: !6, line: 205, baseType: !254, size: 64, align: 64, offset: 448)
!254 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !255, size: 64, align: 64)
!255 = !DISubroutineType(types: !256)
!256 = !{!52, !4, !52, !23}
!257 = !DIDerivedType(tag: DW_TAG_member, name: "cleanup", scope: !229, file: !6, line: 206, baseType: !250, size: 64, align: 64, offset: 512)
!258 = !DIDerivedType(tag: DW_TAG_member, name: "format_capabilties", scope: !229, file: !6, line: 207, baseType: !250, size: 64, align: 64, offset: 576)
!259 = !DIDerivedType(tag: DW_TAG_member, name: "has_encrypted_entries", scope: !229, file: !6, line: 208, baseType: !250, size: 64, align: 64, offset: 640)
!260 = !DIDerivedType(tag: DW_TAG_member, name: "format", scope: !5, file: !6, line: 210, baseType: !261, size: 64, align: 64, offset: 19776)
!261 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !229, size: 64, align: 64)
!262 = !DIDerivedType(tag: DW_TAG_member, name: "extract", scope: !5, file: !6, line: 215, baseType: !263, size: 64, align: 64, offset: 19840)
!263 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !264, size: 64, align: 64)
!264 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_extract", file: !6, line: 151, size: 192, align: 64, elements: !265)
!265 = !{!266, !267, !271}
!266 = !DIDerivedType(tag: DW_TAG_member, name: "ad", scope: !264, file: !6, line: 152, baseType: !24, size: 64, align: 64)
!267 = !DIDerivedType(tag: DW_TAG_member, name: "extract_progress", scope: !264, file: !6, line: 155, baseType: !268, size: 64, align: 64, offset: 64)
!268 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !269, size: 64, align: 64)
!269 = !DISubroutineType(types: !270)
!270 = !{null, !122}
!271 = !DIDerivedType(tag: DW_TAG_member, name: "extract_progress_user_data", scope: !264, file: !6, line: 156, baseType: !122, size: 64, align: 64, offset: 128)
!272 = !DIDerivedType(tag: DW_TAG_member, name: "cleanup_archive_extract", scope: !5, file: !6, line: 216, baseType: !250, size: 64, align: 64, offset: 19904)
!273 = !DIDerivedType(tag: DW_TAG_member, name: "passphrases", scope: !5, file: !6, line: 227, baseType: !274, size: 320, align: 64, offset: 19968)
!274 = !DICompositeType(tag: DW_TAG_structure_type, scope: !5, file: !6, line: 221, size: 320, align: 64, elements: !275)
!275 = !{!276, !282, !284, !285, !290}
!276 = !DIDerivedType(tag: DW_TAG_member, name: "first", scope: !274, file: !6, line: 222, baseType: !277, size: 64, align: 64)
!277 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !278, size: 64, align: 64)
!278 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_passphrase", file: !6, line: 146, size: 128, align: 64, elements: !279)
!279 = !{!280, !281}
!280 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase", scope: !278, file: !6, line: 147, baseType: !95, size: 64, align: 64)
!281 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !278, file: !6, line: 148, baseType: !277, size: 64, align: 64, offset: 64)
!282 = !DIDerivedType(tag: DW_TAG_member, name: "last", scope: !274, file: !6, line: 223, baseType: !283, size: 64, align: 64, offset: 64)
!283 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !277, size: 64, align: 64)
!284 = !DIDerivedType(tag: DW_TAG_member, name: "candidate", scope: !274, file: !6, line: 224, baseType: !23, size: 32, align: 32, offset: 128)
!285 = !DIDerivedType(tag: DW_TAG_member, name: "callback", scope: !274, file: !6, line: 225, baseType: !286, size: 64, align: 64, offset: 192)
!286 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !287, size: 64, align: 64)
!287 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_passphrase_callback", file: !32, line: 256, baseType: !288)
!288 = !DISubroutineType(types: !289)
!289 = !{!80, !24, !122}
!290 = !DIDerivedType(tag: DW_TAG_member, name: "client_data", scope: !274, file: !6, line: 226, baseType: !122, size: 64, align: 64, offset: 256)
!291 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !292, size: 64, align: 64)
!292 = !DICompositeType(tag: DW_TAG_structure_type, name: "mtree", file: !1, line: 95, size: 66752, align: 64, elements: !293)
!293 = !{!294, !295, !296, !297, !298, !299, !300, !301, !317, !318, !322, !323, !324, !328, !329}
!294 = !DIDerivedType(tag: DW_TAG_member, name: "line", scope: !292, file: !1, line: 96, baseType: !91, size: 192, align: 64)
!295 = !DIDerivedType(tag: DW_TAG_member, name: "buffsize", scope: !292, file: !1, line: 97, baseType: !45, size: 64, align: 64, offset: 192)
!296 = !DIDerivedType(tag: DW_TAG_member, name: "buff", scope: !292, file: !1, line: 98, baseType: !95, size: 64, align: 64, offset: 256)
!297 = !DIDerivedType(tag: DW_TAG_member, name: "offset", scope: !292, file: !1, line: 99, baseType: !52, size: 64, align: 64, offset: 320)
!298 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !292, file: !1, line: 100, baseType: !23, size: 32, align: 32, offset: 384)
!299 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format", scope: !292, file: !1, line: 101, baseType: !23, size: 32, align: 32, offset: 416)
!300 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format_name", scope: !292, file: !1, line: 102, baseType: !80, size: 64, align: 64, offset: 448)
!301 = !DIDerivedType(tag: DW_TAG_member, name: "entries", scope: !292, file: !1, line: 103, baseType: !302, size: 64, align: 64, offset: 512)
!302 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !303, size: 64, align: 64)
!303 = !DICompositeType(tag: DW_TAG_structure_type, name: "mtree_entry", file: !1, line: 85, size: 320, align: 64, elements: !304)
!304 = !{!305, !306, !312, !313, !314, !315, !316}
!305 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !303, file: !1, line: 86, baseType: !302, size: 64, align: 64)
!306 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !303, file: !1, line: 87, baseType: !307, size: 64, align: 64, offset: 64)
!307 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !308, size: 64, align: 64)
!308 = !DICompositeType(tag: DW_TAG_structure_type, name: "mtree_option", file: !1, line: 80, size: 128, align: 64, elements: !309)
!309 = !{!310, !311}
!310 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !308, file: !1, line: 81, baseType: !307, size: 64, align: 64)
!311 = !DIDerivedType(tag: DW_TAG_member, name: "value", scope: !308, file: !1, line: 82, baseType: !95, size: 64, align: 64, offset: 64)
!312 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !303, file: !1, line: 88, baseType: !95, size: 64, align: 64, offset: 128)
!313 = !DIDerivedType(tag: DW_TAG_member, name: "full", scope: !303, file: !1, line: 89, baseType: !82, size: 8, align: 8, offset: 192)
!314 = !DIDerivedType(tag: DW_TAG_member, name: "used", scope: !303, file: !1, line: 90, baseType: !82, size: 8, align: 8, offset: 200)
!315 = !DIDerivedType(tag: DW_TAG_member, name: "name_hash", scope: !303, file: !1, line: 91, baseType: !13, size: 32, align: 32, offset: 224)
!316 = !DIDerivedType(tag: DW_TAG_member, name: "hashtable_next", scope: !303, file: !1, line: 92, baseType: !302, size: 64, align: 64, offset: 256)
!317 = !DIDerivedType(tag: DW_TAG_member, name: "this_entry", scope: !292, file: !1, line: 104, baseType: !302, size: 64, align: 64, offset: 576)
!318 = !DIDerivedType(tag: DW_TAG_member, name: "entry_hashtable", scope: !292, file: !1, line: 105, baseType: !319, size: 65536, align: 64, offset: 640)
!319 = !DICompositeType(tag: DW_TAG_array_type, baseType: !302, size: 65536, align: 64, elements: !320)
!320 = !{!321}
!321 = !DISubrange(count: 1024)
!322 = !DIDerivedType(tag: DW_TAG_member, name: "current_dir", scope: !292, file: !1, line: 106, baseType: !91, size: 192, align: 64, offset: 66176)
!323 = !DIDerivedType(tag: DW_TAG_member, name: "contents_name", scope: !292, file: !1, line: 107, baseType: !91, size: 192, align: 64, offset: 66368)
!324 = !DIDerivedType(tag: DW_TAG_member, name: "resolver", scope: !292, file: !1, line: 109, baseType: !325, size: 64, align: 64, offset: 66560)
!325 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !326, size: 64, align: 64)
!326 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_entry_linkresolver", file: !327, line: 641, flags: DIFlagFwdDecl)
!327 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_entry.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!328 = !DIDerivedType(tag: DW_TAG_member, name: "cur_size", scope: !292, file: !1, line: 111, baseType: !52, size: 64, align: 64, offset: 66624)
!329 = !DIDerivedType(tag: DW_TAG_member, name: "checkfs", scope: !292, file: !1, line: 112, baseType: !82, size: 8, align: 8, offset: 66688)
!330 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !331, size: 64, align: 64)
!331 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !332)
!332 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!333 = !DIDerivedType(tag: DW_TAG_typedef, name: "mode_t", file: !334, line: 63, baseType: !335)
!334 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/stat.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!335 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !41, line: 129, baseType: !13)
!336 = !DIDerivedType(tag: DW_TAG_typedef, name: "time_t", file: !337, line: 75, baseType: !338)
!337 = !DIFile(filename: "/usr/include/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!338 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !41, line: 139, baseType: !42)
!339 = !DIDerivedType(tag: DW_TAG_typedef, name: "dev_t", file: !334, line: 44, baseType: !340)
!340 = !DIDerivedType(tag: DW_TAG_typedef, name: "__dev_t", file: !41, line: 124, baseType: !47)
!341 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !53, line: 55, baseType: !47)
!342 = !{!343, !344, !345, !346, !349, !350, !354, !359, !362, !365, !368, !371, !374, !375, !378, !382, !387, !390, !393, !396, !399, !402, !403, !406, !407, !410, !414, !417, !420, !421, !424, !425, !426, !429, !430, !431}
!343 = distinct !DISubprogram(name: "archive_read_support_format_mtree", scope: !1, file: !1, line: 223, type: !21, isLocal: false, isDefinition: true, scopeLine: 224, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!344 = distinct !DISubprogram(name: "archive_read_format_mtree_options", scope: !1, file: !1, line: 188, type: !239, isLocal: true, isDefinition: true, scopeLine: 190, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!345 = distinct !DISubprogram(name: "cleanup", scope: !1, file: !1, line: 249, type: !251, isLocal: true, isDefinition: true, scopeLine: 250, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!346 = distinct !DISubprogram(name: "free_options", scope: !1, file: !1, line: 211, type: !347, isLocal: true, isDefinition: true, scopeLine: 212, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!347 = !DISubroutineType(types: !348)
!348 = !{null, !307}
!349 = distinct !DISubprogram(name: "mtree_bid", scope: !1, file: !1, line: 613, type: !235, isLocal: true, isDefinition: true, scopeLine: 614, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!350 = distinct !DISubprogram(name: "detect_form", scope: !1, file: !1, line: 635, type: !351, isLocal: true, isDefinition: true, scopeLine: 636, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!351 = !DISubroutineType(types: !352)
!352 = !{!23, !4, !353}
!353 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !23, size: 64, align: 64)
!354 = distinct !DISubprogram(name: "next_line", scope: !1, file: !1, line: 319, type: !355, isLocal: true, isDefinition: true, scopeLine: 321, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!355 = !DISubroutineType(types: !356)
!356 = !{!38, !4, !357, !358, !358, !358}
!357 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !80, size: 64, align: 64)
!358 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !38, size: 64, align: 64)
!359 = distinct !DISubprogram(name: "get_line_size", scope: !1, file: !1, line: 276, type: !360, isLocal: true, isDefinition: true, scopeLine: 277, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!360 = !DISubroutineType(types: !361)
!361 = !{!38, !80, !38, !358}
!362 = distinct !DISubprogram(name: "bid_keyword_list", scope: !1, file: !1, line: 469, type: !363, isLocal: true, isDefinition: true, scopeLine: 470, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!363 = !DISubroutineType(types: !364)
!364 = !{!23, !80, !38, !23, !23}
!365 = distinct !DISubprogram(name: "bid_keycmp", scope: !1, file: !1, line: 369, type: !366, isLocal: true, isDefinition: true, scopeLine: 370, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!366 = !DISubroutineType(types: !367)
!367 = !{!23, !80, !80, !38}
!368 = distinct !DISubprogram(name: "bid_keyword", scope: !1, file: !1, line: 400, type: !369, isLocal: true, isDefinition: true, scopeLine: 401, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!369 = !DISubroutineType(types: !370)
!370 = !{!23, !80, !38}
!371 = distinct !DISubprogram(name: "bid_entry", scope: !1, file: !1, line: 525, type: !372, isLocal: true, isDefinition: true, scopeLine: 526, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!372 = !DISubroutineType(types: !373)
!373 = !{!23, !80, !38, !38, !353}
!374 = distinct !DISubprogram(name: "read_header", scope: !1, file: !1, line: 1050, type: !243, isLocal: true, isDefinition: true, scopeLine: 1051, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!375 = distinct !DISubprogram(name: "read_mtree", scope: !1, file: !1, line: 981, type: !376, isLocal: true, isDefinition: true, scopeLine: 982, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!376 = !DISubroutineType(types: !377)
!377 = !{!23, !4, !291}
!378 = distinct !DISubprogram(name: "readline", scope: !1, file: !1, line: 1958, type: !379, isLocal: true, isDefinition: true, scopeLine: 1960, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!379 = !DISubroutineType(types: !380)
!380 = !{!38, !4, !291, !381, !38}
!381 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !95, size: 64, align: 64)
!382 = distinct !DISubprogram(name: "process_add_entry", scope: !1, file: !1, line: 866, type: !383, isLocal: true, isDefinition: true, scopeLine: 869, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!383 = !DISubroutineType(types: !384)
!384 = !{!23, !4, !291, !385, !80, !38, !386, !23}
!385 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !307, size: 64, align: 64)
!386 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !302, size: 64, align: 64)
!387 = distinct !DISubprogram(name: "parse_escapes", scope: !1, file: !1, line: 1753, type: !388, isLocal: true, isDefinition: true, scopeLine: 1754, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!388 = !DISubroutineType(types: !389)
!389 = !{null, !95, !302}
!390 = distinct !DISubprogram(name: "hash", scope: !1, file: !1, line: 2027, type: !391, isLocal: true, isDefinition: true, scopeLine: 2028, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!391 = !DISubroutineType(types: !392)
!392 = !{!13, !80}
!393 = distinct !DISubprogram(name: "add_option", scope: !1, file: !1, line: 760, type: !394, isLocal: true, isDefinition: true, scopeLine: 762, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!394 = !DISubroutineType(types: !395)
!395 = !{!23, !4, !385, !80, !45}
!396 = distinct !DISubprogram(name: "remove_option", scope: !1, file: !1, line: 782, type: !397, isLocal: true, isDefinition: true, scopeLine: 783, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!397 = !DISubroutineType(types: !398)
!398 = !{null, !385, !80, !45}
!399 = distinct !DISubprogram(name: "process_global_set", scope: !1, file: !1, line: 805, type: !400, isLocal: true, isDefinition: true, scopeLine: 807, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!400 = !DISubroutineType(types: !401)
!401 = !{!23, !4, !385, !80}
!402 = distinct !DISubprogram(name: "process_global_unset", scope: !1, file: !1, line: 834, type: !400, isLocal: true, isDefinition: true, scopeLine: 836, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!403 = distinct !DISubprogram(name: "parse_file", scope: !1, file: !1, line: 1111, type: !404, isLocal: true, isDefinition: true, scopeLine: 1113, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!404 = !DISubroutineType(types: !405)
!405 = !{!23, !4, !30, !291, !302, !353}
!406 = distinct !DISubprogram(name: "parse_line", scope: !1, file: !1, line: 1344, type: !404, isLocal: true, isDefinition: true, scopeLine: 1346, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!407 = distinct !DISubprogram(name: "parse_keyword", scope: !1, file: !1, line: 1447, type: !408, isLocal: true, isDefinition: true, scopeLine: 1449, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!408 = !DISubroutineType(types: !409)
!409 = !{!23, !4, !291, !30, !307, !353}
!410 = distinct !DISubprogram(name: "parse_device", scope: !1, file: !1, line: 1387, type: !411, isLocal: true, isDefinition: true, scopeLine: 1388, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!411 = !DISubroutineType(types: !412)
!412 = !{!23, !413, !24, !95}
!413 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !339, size: 64, align: 64)
!414 = distinct !DISubprogram(name: "la_strsep", scope: !1, file: !1, line: 1373, type: !415, isLocal: true, isDefinition: true, scopeLine: 1374, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!415 = !DISubroutineType(types: !416)
!416 = !{!95, !381, !80}
!417 = distinct !DISubprogram(name: "mtree_atol", scope: !1, file: !1, line: 1941, type: !418, isLocal: true, isDefinition: true, scopeLine: 1942, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!418 = !DISubroutineType(types: !419)
!419 = !{!52, !381}
!420 = distinct !DISubprogram(name: "mtree_atol16", scope: !1, file: !1, line: 1911, type: !418, isLocal: true, isDefinition: true, scopeLine: 1912, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!421 = distinct !DISubprogram(name: "parsehex", scope: !1, file: !1, line: 1893, type: !422, isLocal: true, isDefinition: true, scopeLine: 1894, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!422 = !DISubroutineType(types: !423)
!423 = !{!23, !82}
!424 = distinct !DISubprogram(name: "mtree_atol10", scope: !1, file: !1, line: 1862, type: !418, isLocal: true, isDefinition: true, scopeLine: 1863, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!425 = distinct !DISubprogram(name: "mtree_atol8", scope: !1, file: !1, line: 1834, type: !418, isLocal: true, isDefinition: true, scopeLine: 1835, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!426 = distinct !DISubprogram(name: "get_time_t_max", scope: !1, file: !1, line: 143, type: !427, isLocal: true, isDefinition: true, scopeLine: 144, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!427 = !DISubroutineType(types: !428)
!428 = !{!52}
!429 = distinct !DISubprogram(name: "get_time_t_min", scope: !1, file: !1, line: 168, type: !427, isLocal: true, isDefinition: true, scopeLine: 169, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!430 = distinct !DISubprogram(name: "read_data", scope: !1, file: !1, line: 1690, type: !247, isLocal: true, isDefinition: true, scopeLine: 1692, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!431 = distinct !DISubprogram(name: "skip", scope: !1, file: !1, line: 1736, type: !251, isLocal: true, isDefinition: true, scopeLine: 1737, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!432 = !{!433, !437, !441, !442, !443, !444, !445, !446, !450, !451, !452}
!433 = !DIGlobalVariable(name: "keys_c", scope: !368, file: !1, line: 402, type: !434, isLocal: true, isDefinition: true, variable: [4 x i8*]* @bid_keyword.keys_c)
!434 = !DICompositeType(tag: DW_TAG_array_type, baseType: !80, size: 256, align: 64, elements: !435)
!435 = !{!436}
!436 = !DISubrange(count: 4)
!437 = !DIGlobalVariable(name: "keys_df", scope: !368, file: !1, line: 405, type: !438, isLocal: true, isDefinition: true, variable: [3 x i8*]* @bid_keyword.keys_df)
!438 = !DICompositeType(tag: DW_TAG_array_type, baseType: !80, size: 192, align: 64, elements: !439)
!439 = !{!440}
!440 = !DISubrange(count: 3)
!441 = !DIGlobalVariable(name: "keys_g", scope: !368, file: !1, line: 408, type: !438, isLocal: true, isDefinition: true, variable: [3 x i8*]* @bid_keyword.keys_g)
!442 = !DIGlobalVariable(name: "keys_il", scope: !368, file: !1, line: 411, type: !434, isLocal: true, isDefinition: true, variable: [4 x i8*]* @bid_keyword.keys_il)
!443 = !DIGlobalVariable(name: "keys_m", scope: !368, file: !1, line: 414, type: !434, isLocal: true, isDefinition: true, variable: [4 x i8*]* @bid_keyword.keys_m)
!444 = !DIGlobalVariable(name: "keys_no", scope: !368, file: !1, line: 417, type: !434, isLocal: true, isDefinition: true, variable: [4 x i8*]* @bid_keyword.keys_no)
!445 = !DIGlobalVariable(name: "keys_r", scope: !368, file: !1, line: 420, type: !434, isLocal: true, isDefinition: true, variable: [4 x i8*]* @bid_keyword.keys_r)
!446 = !DIGlobalVariable(name: "keys_s", scope: !368, file: !1, line: 423, type: !447, isLocal: true, isDefinition: true, variable: [10 x i8*]* @bid_keyword.keys_s)
!447 = !DICompositeType(tag: DW_TAG_array_type, baseType: !80, size: 640, align: 64, elements: !448)
!448 = !{!449}
!449 = !DISubrange(count: 10)
!450 = !DIGlobalVariable(name: "keys_t", scope: !368, file: !1, line: 430, type: !434, isLocal: true, isDefinition: true, variable: [4 x i8*]* @bid_keyword.keys_t)
!451 = !DIGlobalVariable(name: "keys_u", scope: !368, file: !1, line: 433, type: !438, isLocal: true, isDefinition: true, variable: [3 x i8*]* @bid_keyword.keys_u)
!452 = !DIGlobalVariable(name: "safe_char", scope: !371, file: !1, line: 528, type: !453, isLocal: true, isDefinition: true, variable: [256 x i8]* @bid_entry.safe_char)
!453 = !DICompositeType(tag: DW_TAG_array_type, baseType: !331, size: 2048, align: 8, elements: !454)
!454 = !{!455}
!455 = !DISubrange(count: 256)
!456 = !{i32 2, !"Dwarf Version", i32 4}
!457 = !{i32 2, !"Debug Info Version", i32 3}
!458 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!459 = !DILocalVariable(name: "_a", arg: 1, scope: !343, file: !1, line: 223, type: !24)
!460 = !DIExpression()
!461 = !DILocation(line: 223, column: 51, scope: !343)
!462 = !DILocalVariable(name: "a", scope: !343, file: !1, line: 225, type: !4)
!463 = !DILocation(line: 225, column: 23, scope: !343)
!464 = !DILocation(line: 225, column: 50, scope: !343)
!465 = !DILocation(line: 225, column: 27, scope: !343)
!466 = !DILocalVariable(name: "mtree", scope: !343, file: !1, line: 226, type: !291)
!467 = !DILocation(line: 226, column: 16, scope: !343)
!468 = !DILocalVariable(name: "r", scope: !343, file: !1, line: 227, type: !23)
!469 = !DILocation(line: 227, column: 6, scope: !343)
!470 = !DILocation(line: 229, column: 2, scope: !343)
!471 = !DILocalVariable(name: "magic_test", scope: !472, file: !1, line: 229, type: !23)
!472 = distinct !DILexicalBlock(scope: !343, file: !1, line: 229, column: 2)
!473 = !DILocation(line: 229, column: 2, scope: !472)
!474 = !DILocation(line: 229, column: 2, scope: !475)
!475 = !DILexicalBlockFile(scope: !472, file: !1, discriminator: 1)
!476 = !DILocation(line: 229, column: 2, scope: !477)
!477 = !DILexicalBlockFile(scope: !478, file: !1, discriminator: 2)
!478 = distinct !DILexicalBlock(scope: !472, file: !1, line: 229, column: 2)
!479 = !DILocation(line: 229, column: 2, scope: !480)
!480 = !DILexicalBlockFile(scope: !472, file: !1, discriminator: 3)
!481 = !DILocation(line: 232, column: 26, scope: !343)
!482 = !DILocation(line: 232, column: 10, scope: !343)
!483 = !DILocation(line: 232, column: 8, scope: !343)
!484 = !DILocation(line: 233, column: 6, scope: !485)
!485 = distinct !DILexicalBlock(scope: !343, file: !1, line: 233, column: 6)
!486 = !DILocation(line: 233, column: 12, scope: !485)
!487 = !DILocation(line: 233, column: 6, scope: !343)
!488 = !DILocation(line: 234, column: 22, scope: !489)
!489 = distinct !DILexicalBlock(scope: !485, file: !1, line: 233, column: 21)
!490 = !DILocation(line: 234, column: 25, scope: !489)
!491 = !DILocation(line: 234, column: 3, scope: !489)
!492 = !DILocation(line: 236, column: 3, scope: !489)
!493 = !DILocation(line: 238, column: 2, scope: !343)
!494 = !DILocation(line: 238, column: 9, scope: !343)
!495 = !DILocation(line: 238, column: 12, scope: !343)
!496 = !DILocation(line: 240, column: 37, scope: !343)
!497 = !DILocation(line: 240, column: 40, scope: !343)
!498 = !DILocation(line: 240, column: 6, scope: !343)
!499 = !DILocation(line: 240, column: 4, scope: !343)
!500 = !DILocation(line: 243, column: 6, scope: !501)
!501 = distinct !DILexicalBlock(scope: !343, file: !1, line: 243, column: 6)
!502 = !DILocation(line: 243, column: 8, scope: !501)
!503 = !DILocation(line: 243, column: 6, scope: !343)
!504 = !DILocation(line: 244, column: 8, scope: !501)
!505 = !DILocation(line: 244, column: 3, scope: !501)
!506 = !DILocation(line: 245, column: 2, scope: !343)
!507 = !DILocation(line: 246, column: 1, scope: !343)
!508 = !DILocalVariable(name: "a", arg: 1, scope: !349, file: !1, line: 613, type: !4)
!509 = !DILocation(line: 613, column: 32, scope: !349)
!510 = !DILocalVariable(name: "best_bid", arg: 2, scope: !349, file: !1, line: 613, type: !23)
!511 = !DILocation(line: 613, column: 39, scope: !349)
!512 = !DILocalVariable(name: "signature", scope: !349, file: !1, line: 615, type: !80)
!513 = !DILocation(line: 615, column: 14, scope: !349)
!514 = !DILocalVariable(name: "p", scope: !349, file: !1, line: 616, type: !80)
!515 = !DILocation(line: 616, column: 14, scope: !349)
!516 = !DILocation(line: 618, column: 8, scope: !349)
!517 = !DILocation(line: 621, column: 27, scope: !349)
!518 = !DILocation(line: 621, column: 37, scope: !349)
!519 = !DILocation(line: 621, column: 30, scope: !349)
!520 = !DILocation(line: 621, column: 6, scope: !521)
!521 = !DILexicalBlockFile(scope: !349, file: !1, discriminator: 1)
!522 = !DILocation(line: 621, column: 4, scope: !349)
!523 = !DILocation(line: 622, column: 6, scope: !524)
!524 = distinct !DILexicalBlock(scope: !349, file: !1, line: 622, column: 6)
!525 = !DILocation(line: 622, column: 8, scope: !524)
!526 = !DILocation(line: 622, column: 6, scope: !349)
!527 = !DILocation(line: 623, column: 3, scope: !524)
!528 = !DILocation(line: 625, column: 13, scope: !529)
!529 = distinct !DILexicalBlock(scope: !349, file: !1, line: 625, column: 6)
!530 = !DILocation(line: 625, column: 16, scope: !529)
!531 = !DILocation(line: 625, column: 34, scope: !529)
!532 = !DILocation(line: 625, column: 27, scope: !529)
!533 = !DILocation(line: 625, column: 6, scope: !534)
!534 = !DILexicalBlockFile(scope: !529, file: !1, discriminator: 1)
!535 = !DILocation(line: 625, column: 46, scope: !529)
!536 = !DILocation(line: 625, column: 6, scope: !349)
!537 = !DILocation(line: 626, column: 27, scope: !529)
!538 = !DILocation(line: 626, column: 20, scope: !529)
!539 = !DILocation(line: 626, column: 15, scope: !529)
!540 = !DILocation(line: 626, column: 13, scope: !529)
!541 = !DILocation(line: 626, column: 3, scope: !529)
!542 = !DILocation(line: 631, column: 22, scope: !349)
!543 = !DILocation(line: 631, column: 10, scope: !349)
!544 = !DILocation(line: 631, column: 2, scope: !349)
!545 = !DILocation(line: 632, column: 1, scope: !349)
!546 = !DILocalVariable(name: "a", arg: 1, scope: !344, file: !1, line: 188, type: !4)
!547 = !DILocation(line: 188, column: 56, scope: !344)
!548 = !DILocalVariable(name: "key", arg: 2, scope: !344, file: !1, line: 189, type: !80)
!549 = !DILocation(line: 189, column: 17, scope: !344)
!550 = !DILocalVariable(name: "val", arg: 3, scope: !344, file: !1, line: 189, type: !80)
!551 = !DILocation(line: 189, column: 34, scope: !344)
!552 = !DILocalVariable(name: "mtree", scope: !344, file: !1, line: 191, type: !291)
!553 = !DILocation(line: 191, column: 16, scope: !344)
!554 = !DILocation(line: 193, column: 27, scope: !344)
!555 = !DILocation(line: 193, column: 30, scope: !344)
!556 = !DILocation(line: 193, column: 38, scope: !344)
!557 = !DILocation(line: 193, column: 10, scope: !344)
!558 = !DILocation(line: 193, column: 8, scope: !344)
!559 = !DILocation(line: 194, column: 13, scope: !560)
!560 = distinct !DILexicalBlock(scope: !344, file: !1, line: 194, column: 6)
!561 = !DILocation(line: 194, column: 6, scope: !560)
!562 = !DILocation(line: 194, column: 30, scope: !560)
!563 = !DILocation(line: 194, column: 6, scope: !344)
!564 = !DILocation(line: 196, column: 7, scope: !565)
!565 = distinct !DILexicalBlock(scope: !566, file: !1, line: 196, column: 7)
!566 = distinct !DILexicalBlock(scope: !560, file: !1, line: 194, column: 36)
!567 = !DILocation(line: 196, column: 11, scope: !565)
!568 = !DILocation(line: 196, column: 19, scope: !565)
!569 = !DILocation(line: 196, column: 22, scope: !570)
!570 = !DILexicalBlockFile(scope: !565, file: !1, discriminator: 1)
!571 = !DILocation(line: 196, column: 29, scope: !570)
!572 = !DILocation(line: 196, column: 7, scope: !570)
!573 = !DILocation(line: 197, column: 4, scope: !574)
!574 = distinct !DILexicalBlock(scope: !565, file: !1, line: 196, column: 35)
!575 = !DILocation(line: 197, column: 11, scope: !574)
!576 = !DILocation(line: 197, column: 19, scope: !574)
!577 = !DILocation(line: 198, column: 3, scope: !574)
!578 = !DILocation(line: 199, column: 4, scope: !579)
!579 = distinct !DILexicalBlock(scope: !565, file: !1, line: 198, column: 10)
!580 = !DILocation(line: 199, column: 11, scope: !579)
!581 = !DILocation(line: 199, column: 19, scope: !579)
!582 = !DILocation(line: 201, column: 3, scope: !566)
!583 = !DILocation(line: 207, column: 2, scope: !344)
!584 = !DILocation(line: 208, column: 1, scope: !344)
!585 = !DILocalVariable(name: "a", arg: 1, scope: !374, file: !1, line: 1050, type: !4)
!586 = !DILocation(line: 1050, column: 34, scope: !374)
!587 = !DILocalVariable(name: "entry", arg: 2, scope: !374, file: !1, line: 1050, type: !30)
!588 = !DILocation(line: 1050, column: 59, scope: !374)
!589 = !DILocalVariable(name: "mtree", scope: !374, file: !1, line: 1052, type: !291)
!590 = !DILocation(line: 1052, column: 16, scope: !374)
!591 = !DILocalVariable(name: "p", scope: !374, file: !1, line: 1053, type: !95)
!592 = !DILocation(line: 1053, column: 8, scope: !374)
!593 = !DILocalVariable(name: "r", scope: !374, file: !1, line: 1054, type: !23)
!594 = !DILocation(line: 1054, column: 6, scope: !374)
!595 = !DILocalVariable(name: "use_next", scope: !374, file: !1, line: 1054, type: !23)
!596 = !DILocation(line: 1054, column: 9, scope: !374)
!597 = !DILocation(line: 1056, column: 27, scope: !374)
!598 = !DILocation(line: 1056, column: 30, scope: !374)
!599 = !DILocation(line: 1056, column: 38, scope: !374)
!600 = !DILocation(line: 1056, column: 10, scope: !374)
!601 = !DILocation(line: 1056, column: 8, scope: !374)
!602 = !DILocation(line: 1058, column: 6, scope: !603)
!603 = distinct !DILexicalBlock(scope: !374, file: !1, line: 1058, column: 6)
!604 = !DILocation(line: 1058, column: 13, scope: !603)
!605 = !DILocation(line: 1058, column: 16, scope: !603)
!606 = !DILocation(line: 1058, column: 6, scope: !374)
!607 = !DILocation(line: 1059, column: 9, scope: !608)
!608 = distinct !DILexicalBlock(scope: !603, file: !1, line: 1058, column: 22)
!609 = !DILocation(line: 1059, column: 16, scope: !608)
!610 = !DILocation(line: 1059, column: 3, scope: !608)
!611 = !DILocation(line: 1060, column: 3, scope: !608)
!612 = !DILocation(line: 1060, column: 10, scope: !608)
!613 = !DILocation(line: 1060, column: 13, scope: !608)
!614 = !DILocation(line: 1061, column: 2, scope: !608)
!615 = !DILocation(line: 1063, column: 6, scope: !616)
!616 = distinct !DILexicalBlock(scope: !374, file: !1, line: 1063, column: 6)
!617 = !DILocation(line: 1063, column: 13, scope: !616)
!618 = !DILocation(line: 1063, column: 21, scope: !616)
!619 = !DILocation(line: 1063, column: 6, scope: !374)
!620 = !DILocation(line: 1064, column: 21, scope: !621)
!621 = distinct !DILexicalBlock(scope: !616, file: !1, line: 1063, column: 30)
!622 = !DILocation(line: 1064, column: 3, scope: !621)
!623 = !DILocation(line: 1064, column: 10, scope: !621)
!624 = !DILocation(line: 1064, column: 19, scope: !621)
!625 = !DILocation(line: 1065, column: 7, scope: !626)
!626 = distinct !DILexicalBlock(scope: !621, file: !1, line: 1065, column: 7)
!627 = !DILocation(line: 1065, column: 14, scope: !626)
!628 = !DILocation(line: 1065, column: 23, scope: !626)
!629 = !DILocation(line: 1065, column: 7, scope: !621)
!630 = !DILocation(line: 1066, column: 4, scope: !626)
!631 = !DILocation(line: 1067, column: 43, scope: !621)
!632 = !DILocation(line: 1067, column: 50, scope: !621)
!633 = !DILocation(line: 1067, column: 3, scope: !621)
!634 = !DILocation(line: 1069, column: 18, scope: !621)
!635 = !DILocation(line: 1069, column: 21, scope: !621)
!636 = !DILocation(line: 1069, column: 7, scope: !621)
!637 = !DILocation(line: 1069, column: 5, scope: !621)
!638 = !DILocation(line: 1070, column: 7, scope: !639)
!639 = distinct !DILexicalBlock(scope: !621, file: !1, line: 1070, column: 7)
!640 = !DILocation(line: 1070, column: 9, scope: !639)
!641 = !DILocation(line: 1070, column: 7, scope: !621)
!642 = !DILocation(line: 1071, column: 12, scope: !639)
!643 = !DILocation(line: 1071, column: 4, scope: !639)
!644 = !DILocation(line: 1072, column: 2, scope: !621)
!645 = !DILocation(line: 1074, column: 30, scope: !374)
!646 = !DILocation(line: 1074, column: 37, scope: !374)
!647 = !DILocation(line: 1074, column: 2, scope: !374)
!648 = !DILocation(line: 1074, column: 5, scope: !374)
!649 = !DILocation(line: 1074, column: 13, scope: !374)
!650 = !DILocation(line: 1074, column: 28, scope: !374)
!651 = !DILocation(line: 1075, column: 35, scope: !374)
!652 = !DILocation(line: 1075, column: 42, scope: !374)
!653 = !DILocation(line: 1075, column: 2, scope: !374)
!654 = !DILocation(line: 1075, column: 5, scope: !374)
!655 = !DILocation(line: 1075, column: 13, scope: !374)
!656 = !DILocation(line: 1075, column: 33, scope: !374)
!657 = !DILocation(line: 1077, column: 2, scope: !374)
!658 = !DILocation(line: 1078, column: 7, scope: !659)
!659 = distinct !DILexicalBlock(scope: !660, file: !1, line: 1078, column: 7)
!660 = distinct !DILexicalBlock(scope: !661, file: !1, line: 1077, column: 11)
!661 = distinct !DILexicalBlock(scope: !662, file: !1, line: 1077, column: 2)
!662 = distinct !DILexicalBlock(scope: !374, file: !1, line: 1077, column: 2)
!663 = !DILocation(line: 1078, column: 14, scope: !659)
!664 = !DILocation(line: 1078, column: 25, scope: !659)
!665 = !DILocation(line: 1078, column: 7, scope: !660)
!666 = !DILocation(line: 1079, column: 4, scope: !659)
!667 = !DILocation(line: 1080, column: 14, scope: !668)
!668 = distinct !DILexicalBlock(scope: !660, file: !1, line: 1080, column: 7)
!669 = !DILocation(line: 1080, column: 21, scope: !668)
!670 = !DILocation(line: 1080, column: 33, scope: !668)
!671 = !DILocation(line: 1080, column: 7, scope: !668)
!672 = !DILocation(line: 1080, column: 45, scope: !668)
!673 = !DILocation(line: 1080, column: 7, scope: !660)
!674 = !DILocation(line: 1081, column: 4, scope: !675)
!675 = distinct !DILexicalBlock(scope: !668, file: !1, line: 1080, column: 51)
!676 = !DILocation(line: 1081, column: 11, scope: !675)
!677 = !DILocation(line: 1081, column: 23, scope: !675)
!678 = !DILocation(line: 1081, column: 28, scope: !675)
!679 = !DILocation(line: 1082, column: 8, scope: !680)
!680 = distinct !DILexicalBlock(scope: !675, file: !1, line: 1082, column: 8)
!681 = !DILocation(line: 1082, column: 44, scope: !680)
!682 = !DILocation(line: 1082, column: 8, scope: !675)
!683 = !DILocation(line: 1084, column: 9, scope: !684)
!684 = distinct !DILexicalBlock(scope: !680, file: !1, line: 1082, column: 49)
!685 = !DILocation(line: 1084, column: 16, scope: !684)
!686 = !DILocation(line: 1084, column: 28, scope: !684)
!687 = !DILocation(line: 1085, column: 11, scope: !684)
!688 = !DILocation(line: 1085, column: 18, scope: !684)
!689 = !DILocation(line: 1085, column: 30, scope: !684)
!690 = !DILocation(line: 1085, column: 9, scope: !684)
!691 = !DILocation(line: 1085, column: 37, scope: !684)
!692 = !DILocation(line: 1084, column: 7, scope: !684)
!693 = !DILocation(line: 1086, column: 5, scope: !684)
!694 = !DILocation(line: 1086, column: 12, scope: !695)
!695 = !DILexicalBlockFile(scope: !684, file: !1, discriminator: 1)
!696 = !DILocation(line: 1086, column: 17, scope: !695)
!697 = !DILocation(line: 1086, column: 24, scope: !695)
!698 = !DILocation(line: 1086, column: 36, scope: !695)
!699 = !DILocation(line: 1086, column: 14, scope: !695)
!700 = !DILocation(line: 1086, column: 38, scope: !695)
!701 = !DILocation(line: 1086, column: 42, scope: !702)
!702 = !DILexicalBlockFile(scope: !684, file: !1, discriminator: 2)
!703 = !DILocation(line: 1086, column: 41, scope: !702)
!704 = !DILocation(line: 1086, column: 44, scope: !702)
!705 = !DILocation(line: 1086, column: 5, scope: !706)
!706 = !DILexicalBlockFile(scope: !684, file: !1, discriminator: 3)
!707 = !DILocation(line: 1087, column: 6, scope: !684)
!708 = !DILocation(line: 1086, column: 5, scope: !709)
!709 = !DILexicalBlockFile(scope: !684, file: !1, discriminator: 4)
!710 = !DILocation(line: 1088, column: 9, scope: !711)
!711 = distinct !DILexicalBlock(scope: !684, file: !1, line: 1088, column: 9)
!712 = !DILocation(line: 1088, column: 14, scope: !711)
!713 = !DILocation(line: 1088, column: 21, scope: !711)
!714 = !DILocation(line: 1088, column: 33, scope: !711)
!715 = !DILocation(line: 1088, column: 11, scope: !711)
!716 = !DILocation(line: 1088, column: 9, scope: !684)
!717 = !DILocation(line: 1089, column: 6, scope: !711)
!718 = !DILocation(line: 1091, column: 11, scope: !684)
!719 = !DILocation(line: 1091, column: 15, scope: !684)
!720 = !DILocation(line: 1091, column: 22, scope: !684)
!721 = !DILocation(line: 1091, column: 34, scope: !684)
!722 = !DILocation(line: 1091, column: 13, scope: !684)
!723 = !DILocation(line: 1091, column: 36, scope: !684)
!724 = !DILocation(line: 1090, column: 5, scope: !684)
!725 = !DILocation(line: 1090, column: 12, scope: !684)
!726 = !DILocation(line: 1090, column: 24, scope: !684)
!727 = !DILocation(line: 1091, column: 9, scope: !684)
!728 = !DILocation(line: 1092, column: 4, scope: !684)
!729 = !DILocation(line: 1093, column: 3, scope: !675)
!730 = !DILocation(line: 1094, column: 8, scope: !731)
!731 = distinct !DILexicalBlock(scope: !660, file: !1, line: 1094, column: 7)
!732 = !DILocation(line: 1094, column: 15, scope: !731)
!733 = !DILocation(line: 1094, column: 27, scope: !731)
!734 = !DILocation(line: 1094, column: 7, scope: !660)
!735 = !DILocation(line: 1095, column: 13, scope: !736)
!736 = distinct !DILexicalBlock(scope: !731, file: !1, line: 1094, column: 33)
!737 = !DILocation(line: 1096, column: 19, scope: !736)
!738 = !DILocation(line: 1096, column: 22, scope: !736)
!739 = !DILocation(line: 1096, column: 29, scope: !736)
!740 = !DILocation(line: 1096, column: 36, scope: !736)
!741 = !DILocation(line: 1096, column: 43, scope: !736)
!742 = !DILocation(line: 1096, column: 8, scope: !736)
!743 = !DILocation(line: 1096, column: 6, scope: !736)
!744 = !DILocation(line: 1098, column: 8, scope: !745)
!745 = distinct !DILexicalBlock(scope: !736, file: !1, line: 1098, column: 8)
!746 = !DILocation(line: 1098, column: 17, scope: !745)
!747 = !DILocation(line: 1098, column: 8, scope: !736)
!748 = !DILocation(line: 1099, column: 13, scope: !745)
!749 = !DILocation(line: 1099, column: 5, scope: !745)
!750 = !DILocation(line: 1100, column: 3, scope: !736)
!751 = !DILocation(line: 1101, column: 23, scope: !660)
!752 = !DILocation(line: 1101, column: 30, scope: !660)
!753 = !DILocation(line: 1101, column: 42, scope: !660)
!754 = !DILocation(line: 1101, column: 3, scope: !660)
!755 = !DILocation(line: 1101, column: 10, scope: !660)
!756 = !DILocation(line: 1101, column: 21, scope: !660)
!757 = !DILocation(line: 1077, column: 2, scope: !758)
!758 = !DILexicalBlockFile(scope: !661, file: !1, discriminator: 1)
!759 = !DILocation(line: 1103, column: 1, scope: !374)
!760 = !DILocalVariable(name: "a", arg: 1, scope: !430, file: !1, line: 1690, type: !4)
!761 = !DILocation(line: 1690, column: 32, scope: !430)
!762 = !DILocalVariable(name: "buff", arg: 2, scope: !430, file: !1, line: 1690, type: !64)
!763 = !DILocation(line: 1690, column: 48, scope: !430)
!764 = !DILocalVariable(name: "size", arg: 3, scope: !430, file: !1, line: 1690, type: !65)
!765 = !DILocation(line: 1690, column: 62, scope: !430)
!766 = !DILocalVariable(name: "offset", arg: 4, scope: !430, file: !1, line: 1691, type: !66)
!767 = !DILocation(line: 1691, column: 14, scope: !430)
!768 = !DILocalVariable(name: "bytes_to_read", scope: !430, file: !1, line: 1693, type: !45)
!769 = !DILocation(line: 1693, column: 9, scope: !430)
!770 = !DILocalVariable(name: "bytes_read", scope: !430, file: !1, line: 1694, type: !38)
!771 = !DILocation(line: 1694, column: 10, scope: !430)
!772 = !DILocalVariable(name: "mtree", scope: !430, file: !1, line: 1695, type: !291)
!773 = !DILocation(line: 1695, column: 16, scope: !430)
!774 = !DILocation(line: 1697, column: 27, scope: !430)
!775 = !DILocation(line: 1697, column: 30, scope: !430)
!776 = !DILocation(line: 1697, column: 38, scope: !430)
!777 = !DILocation(line: 1697, column: 10, scope: !430)
!778 = !DILocation(line: 1697, column: 8, scope: !430)
!779 = !DILocation(line: 1698, column: 6, scope: !780)
!780 = distinct !DILexicalBlock(scope: !430, file: !1, line: 1698, column: 6)
!781 = !DILocation(line: 1698, column: 13, scope: !780)
!782 = !DILocation(line: 1698, column: 16, scope: !780)
!783 = !DILocation(line: 1698, column: 6, scope: !430)
!784 = !DILocation(line: 1699, column: 4, scope: !785)
!785 = distinct !DILexicalBlock(scope: !780, file: !1, line: 1698, column: 21)
!786 = !DILocation(line: 1699, column: 9, scope: !785)
!787 = !DILocation(line: 1700, column: 4, scope: !785)
!788 = !DILocation(line: 1700, column: 11, scope: !785)
!789 = !DILocation(line: 1701, column: 4, scope: !785)
!790 = !DILocation(line: 1701, column: 9, scope: !785)
!791 = !DILocation(line: 1702, column: 3, scope: !785)
!792 = !DILocation(line: 1704, column: 6, scope: !793)
!793 = distinct !DILexicalBlock(scope: !430, file: !1, line: 1704, column: 6)
!794 = !DILocation(line: 1704, column: 13, scope: !793)
!795 = !DILocation(line: 1704, column: 18, scope: !793)
!796 = !DILocation(line: 1704, column: 6, scope: !430)
!797 = !DILocation(line: 1705, column: 3, scope: !798)
!798 = distinct !DILexicalBlock(scope: !793, file: !1, line: 1704, column: 27)
!799 = !DILocation(line: 1705, column: 10, scope: !798)
!800 = !DILocation(line: 1705, column: 19, scope: !798)
!801 = !DILocation(line: 1706, column: 24, scope: !798)
!802 = !DILocation(line: 1706, column: 31, scope: !798)
!803 = !DILocation(line: 1706, column: 17, scope: !798)
!804 = !DILocation(line: 1706, column: 3, scope: !798)
!805 = !DILocation(line: 1706, column: 10, scope: !798)
!806 = !DILocation(line: 1706, column: 15, scope: !798)
!807 = !DILocation(line: 1707, column: 7, scope: !808)
!808 = distinct !DILexicalBlock(scope: !798, file: !1, line: 1707, column: 7)
!809 = !DILocation(line: 1707, column: 14, scope: !808)
!810 = !DILocation(line: 1707, column: 19, scope: !808)
!811 = !DILocation(line: 1707, column: 7, scope: !798)
!812 = !DILocation(line: 1708, column: 23, scope: !813)
!813 = distinct !DILexicalBlock(scope: !808, file: !1, line: 1707, column: 28)
!814 = !DILocation(line: 1708, column: 26, scope: !813)
!815 = !DILocation(line: 1708, column: 4, scope: !813)
!816 = !DILocation(line: 1710, column: 4, scope: !813)
!817 = !DILocation(line: 1712, column: 2, scope: !798)
!818 = !DILocation(line: 1714, column: 10, scope: !430)
!819 = !DILocation(line: 1714, column: 17, scope: !430)
!820 = !DILocation(line: 1714, column: 3, scope: !430)
!821 = !DILocation(line: 1714, column: 8, scope: !430)
!822 = !DILocation(line: 1715, column: 12, scope: !430)
!823 = !DILocation(line: 1715, column: 19, scope: !430)
!824 = !DILocation(line: 1715, column: 3, scope: !430)
!825 = !DILocation(line: 1715, column: 10, scope: !430)
!826 = !DILocation(line: 1716, column: 15, scope: !827)
!827 = distinct !DILexicalBlock(scope: !430, file: !1, line: 1716, column: 6)
!828 = !DILocation(line: 1716, column: 22, scope: !827)
!829 = !DILocation(line: 1716, column: 33, scope: !827)
!830 = !DILocation(line: 1716, column: 40, scope: !827)
!831 = !DILocation(line: 1716, column: 51, scope: !827)
!832 = !DILocation(line: 1716, column: 58, scope: !827)
!833 = !DILocation(line: 1716, column: 49, scope: !827)
!834 = !DILocation(line: 1716, column: 31, scope: !827)
!835 = !DILocation(line: 1716, column: 6, scope: !430)
!836 = !DILocation(line: 1717, column: 28, scope: !827)
!837 = !DILocation(line: 1717, column: 35, scope: !827)
!838 = !DILocation(line: 1717, column: 46, scope: !827)
!839 = !DILocation(line: 1717, column: 53, scope: !827)
!840 = !DILocation(line: 1717, column: 44, scope: !827)
!841 = !DILocation(line: 1717, column: 17, scope: !827)
!842 = !DILocation(line: 1717, column: 3, scope: !827)
!843 = !DILocation(line: 1719, column: 19, scope: !827)
!844 = !DILocation(line: 1719, column: 26, scope: !827)
!845 = !DILocation(line: 1719, column: 17, scope: !827)
!846 = !DILocation(line: 1720, column: 20, scope: !430)
!847 = !DILocation(line: 1720, column: 27, scope: !430)
!848 = !DILocation(line: 1720, column: 31, scope: !430)
!849 = !DILocation(line: 1720, column: 38, scope: !430)
!850 = !DILocation(line: 1720, column: 44, scope: !430)
!851 = !DILocation(line: 1720, column: 15, scope: !430)
!852 = !DILocation(line: 1720, column: 13, scope: !430)
!853 = !DILocation(line: 1721, column: 6, scope: !854)
!854 = distinct !DILexicalBlock(scope: !430, file: !1, line: 1721, column: 6)
!855 = !DILocation(line: 1721, column: 17, scope: !854)
!856 = !DILocation(line: 1721, column: 6, scope: !430)
!857 = !DILocation(line: 1722, column: 22, scope: !858)
!858 = distinct !DILexicalBlock(scope: !854, file: !1, line: 1721, column: 22)
!859 = !DILocation(line: 1722, column: 25, scope: !858)
!860 = !DILocation(line: 1722, column: 34, scope: !858)
!861 = !DILocation(line: 1722, column: 3, scope: !862)
!862 = !DILexicalBlockFile(scope: !858, file: !1, discriminator: 1)
!863 = !DILocation(line: 1723, column: 3, scope: !858)
!864 = !DILocation(line: 1725, column: 6, scope: !865)
!865 = distinct !DILexicalBlock(scope: !430, file: !1, line: 1725, column: 6)
!866 = !DILocation(line: 1725, column: 17, scope: !865)
!867 = !DILocation(line: 1725, column: 6, scope: !430)
!868 = !DILocation(line: 1726, column: 4, scope: !869)
!869 = distinct !DILexicalBlock(scope: !865, file: !1, line: 1725, column: 23)
!870 = !DILocation(line: 1726, column: 9, scope: !869)
!871 = !DILocation(line: 1727, column: 3, scope: !869)
!872 = !DILocation(line: 1729, column: 19, scope: !430)
!873 = !DILocation(line: 1729, column: 2, scope: !430)
!874 = !DILocation(line: 1729, column: 9, scope: !430)
!875 = !DILocation(line: 1729, column: 16, scope: !430)
!876 = !DILocation(line: 1730, column: 10, scope: !430)
!877 = !DILocation(line: 1730, column: 3, scope: !430)
!878 = !DILocation(line: 1730, column: 8, scope: !430)
!879 = !DILocation(line: 1731, column: 2, scope: !430)
!880 = !DILocation(line: 1732, column: 1, scope: !430)
!881 = !DILocalVariable(name: "a", arg: 1, scope: !431, file: !1, line: 1736, type: !4)
!882 = !DILocation(line: 1736, column: 27, scope: !431)
!883 = !DILocalVariable(name: "mtree", scope: !431, file: !1, line: 1738, type: !291)
!884 = !DILocation(line: 1738, column: 16, scope: !431)
!885 = !DILocation(line: 1740, column: 27, scope: !431)
!886 = !DILocation(line: 1740, column: 30, scope: !431)
!887 = !DILocation(line: 1740, column: 38, scope: !431)
!888 = !DILocation(line: 1740, column: 10, scope: !431)
!889 = !DILocation(line: 1740, column: 8, scope: !431)
!890 = !DILocation(line: 1741, column: 6, scope: !891)
!891 = distinct !DILexicalBlock(scope: !431, file: !1, line: 1741, column: 6)
!892 = !DILocation(line: 1741, column: 13, scope: !891)
!893 = !DILocation(line: 1741, column: 16, scope: !891)
!894 = !DILocation(line: 1741, column: 6, scope: !431)
!895 = !DILocation(line: 1742, column: 9, scope: !896)
!896 = distinct !DILexicalBlock(scope: !891, file: !1, line: 1741, column: 22)
!897 = !DILocation(line: 1742, column: 16, scope: !896)
!898 = !DILocation(line: 1742, column: 3, scope: !896)
!899 = !DILocation(line: 1743, column: 3, scope: !896)
!900 = !DILocation(line: 1743, column: 10, scope: !896)
!901 = !DILocation(line: 1743, column: 13, scope: !896)
!902 = !DILocation(line: 1744, column: 2, scope: !896)
!903 = !DILocation(line: 1745, column: 2, scope: !431)
!904 = !DILocalVariable(name: "a", arg: 1, scope: !345, file: !1, line: 249, type: !4)
!905 = !DILocation(line: 249, column: 30, scope: !345)
!906 = !DILocalVariable(name: "mtree", scope: !345, file: !1, line: 251, type: !291)
!907 = !DILocation(line: 251, column: 16, scope: !345)
!908 = !DILocalVariable(name: "p", scope: !345, file: !1, line: 252, type: !302)
!909 = !DILocation(line: 252, column: 22, scope: !345)
!910 = !DILocalVariable(name: "q", scope: !345, file: !1, line: 252, type: !302)
!911 = !DILocation(line: 252, column: 26, scope: !345)
!912 = !DILocation(line: 254, column: 27, scope: !345)
!913 = !DILocation(line: 254, column: 30, scope: !345)
!914 = !DILocation(line: 254, column: 38, scope: !345)
!915 = !DILocation(line: 254, column: 10, scope: !345)
!916 = !DILocation(line: 254, column: 8, scope: !345)
!917 = !DILocation(line: 256, column: 6, scope: !345)
!918 = !DILocation(line: 256, column: 13, scope: !345)
!919 = !DILocation(line: 256, column: 4, scope: !345)
!920 = !DILocation(line: 257, column: 2, scope: !345)
!921 = !DILocation(line: 257, column: 9, scope: !922)
!922 = !DILexicalBlockFile(scope: !345, file: !1, discriminator: 1)
!923 = !DILocation(line: 257, column: 11, scope: !922)
!924 = !DILocation(line: 257, column: 2, scope: !922)
!925 = !DILocation(line: 258, column: 7, scope: !926)
!926 = distinct !DILexicalBlock(scope: !345, file: !1, line: 257, column: 20)
!927 = !DILocation(line: 258, column: 10, scope: !926)
!928 = !DILocation(line: 258, column: 5, scope: !926)
!929 = !DILocation(line: 259, column: 8, scope: !926)
!930 = !DILocation(line: 259, column: 11, scope: !926)
!931 = !DILocation(line: 259, column: 3, scope: !926)
!932 = !DILocation(line: 260, column: 16, scope: !926)
!933 = !DILocation(line: 260, column: 19, scope: !926)
!934 = !DILocation(line: 260, column: 3, scope: !926)
!935 = !DILocation(line: 261, column: 8, scope: !926)
!936 = !DILocation(line: 261, column: 3, scope: !926)
!937 = !DILocation(line: 262, column: 7, scope: !926)
!938 = !DILocation(line: 262, column: 5, scope: !926)
!939 = !DILocation(line: 257, column: 2, scope: !940)
!940 = !DILexicalBlockFile(scope: !345, file: !1, discriminator: 2)
!941 = !DILocation(line: 264, column: 23, scope: !345)
!942 = !DILocation(line: 264, column: 30, scope: !345)
!943 = !DILocation(line: 264, column: 2, scope: !345)
!944 = !DILocation(line: 265, column: 23, scope: !345)
!945 = !DILocation(line: 265, column: 30, scope: !345)
!946 = !DILocation(line: 265, column: 2, scope: !345)
!947 = !DILocation(line: 266, column: 23, scope: !345)
!948 = !DILocation(line: 266, column: 30, scope: !345)
!949 = !DILocation(line: 266, column: 2, scope: !345)
!950 = !DILocation(line: 267, column: 34, scope: !345)
!951 = !DILocation(line: 267, column: 41, scope: !345)
!952 = !DILocation(line: 267, column: 2, scope: !345)
!953 = !DILocation(line: 269, column: 7, scope: !345)
!954 = !DILocation(line: 269, column: 14, scope: !345)
!955 = !DILocation(line: 269, column: 2, scope: !345)
!956 = !DILocation(line: 270, column: 7, scope: !345)
!957 = !DILocation(line: 270, column: 2, scope: !345)
!958 = !DILocation(line: 271, column: 3, scope: !345)
!959 = !DILocation(line: 271, column: 6, scope: !345)
!960 = !DILocation(line: 271, column: 14, scope: !345)
!961 = !DILocation(line: 271, column: 20, scope: !345)
!962 = !DILocation(line: 272, column: 2, scope: !345)
!963 = !DILocalVariable(name: "head", arg: 1, scope: !346, file: !1, line: 211, type: !307)
!964 = !DILocation(line: 211, column: 35, scope: !346)
!965 = !DILocalVariable(name: "next", scope: !346, file: !1, line: 213, type: !307)
!966 = !DILocation(line: 213, column: 23, scope: !346)
!967 = !DILocation(line: 215, column: 2, scope: !346)
!968 = !DILocation(line: 215, column: 9, scope: !969)
!969 = !DILexicalBlockFile(scope: !970, file: !1, discriminator: 1)
!970 = distinct !DILexicalBlock(scope: !971, file: !1, line: 215, column: 2)
!971 = distinct !DILexicalBlock(scope: !346, file: !1, line: 215, column: 2)
!972 = !DILocation(line: 215, column: 14, scope: !969)
!973 = !DILocation(line: 215, column: 2, scope: !969)
!974 = !DILocation(line: 216, column: 10, scope: !975)
!975 = distinct !DILexicalBlock(scope: !970, file: !1, line: 215, column: 36)
!976 = !DILocation(line: 216, column: 16, scope: !975)
!977 = !DILocation(line: 216, column: 8, scope: !975)
!978 = !DILocation(line: 217, column: 8, scope: !975)
!979 = !DILocation(line: 217, column: 14, scope: !975)
!980 = !DILocation(line: 217, column: 3, scope: !975)
!981 = !DILocation(line: 218, column: 8, scope: !975)
!982 = !DILocation(line: 218, column: 3, scope: !975)
!983 = !DILocation(line: 219, column: 2, scope: !975)
!984 = !DILocation(line: 215, column: 30, scope: !985)
!985 = !DILexicalBlockFile(scope: !970, file: !1, discriminator: 2)
!986 = !DILocation(line: 215, column: 28, scope: !985)
!987 = !DILocation(line: 215, column: 2, scope: !985)
!988 = !DILocation(line: 220, column: 1, scope: !346)
!989 = !DILocalVariable(name: "a", arg: 1, scope: !350, file: !1, line: 635, type: !4)
!990 = !DILocation(line: 635, column: 34, scope: !350)
!991 = !DILocalVariable(name: "is_form_d", arg: 2, scope: !350, file: !1, line: 635, type: !353)
!992 = !DILocation(line: 635, column: 42, scope: !350)
!993 = !DILocalVariable(name: "p", scope: !350, file: !1, line: 637, type: !80)
!994 = !DILocation(line: 637, column: 14, scope: !350)
!995 = !DILocalVariable(name: "avail", scope: !350, file: !1, line: 638, type: !38)
!996 = !DILocation(line: 638, column: 10, scope: !350)
!997 = !DILocalVariable(name: "ravail", scope: !350, file: !1, line: 638, type: !38)
!998 = !DILocation(line: 638, column: 17, scope: !350)
!999 = !DILocalVariable(name: "detected_bytes", scope: !350, file: !1, line: 639, type: !38)
!1000 = !DILocation(line: 639, column: 10, scope: !350)
!1001 = !DILocalVariable(name: "len", scope: !350, file: !1, line: 639, type: !38)
!1002 = !DILocation(line: 639, column: 30, scope: !350)
!1003 = !DILocalVariable(name: "nl", scope: !350, file: !1, line: 639, type: !38)
!1004 = !DILocation(line: 639, column: 35, scope: !350)
!1005 = !DILocalVariable(name: "entry_cnt", scope: !350, file: !1, line: 640, type: !23)
!1006 = !DILocation(line: 640, column: 6, scope: !350)
!1007 = !DILocalVariable(name: "multiline", scope: !350, file: !1, line: 640, type: !23)
!1008 = !DILocation(line: 640, column: 21, scope: !350)
!1009 = !DILocalVariable(name: "form_D", scope: !350, file: !1, line: 641, type: !23)
!1010 = !DILocation(line: 641, column: 6, scope: !350)
!1011 = !DILocation(line: 644, column: 6, scope: !1012)
!1012 = distinct !DILexicalBlock(scope: !350, file: !1, line: 644, column: 6)
!1013 = !DILocation(line: 644, column: 16, scope: !1012)
!1014 = !DILocation(line: 644, column: 6, scope: !350)
!1015 = !DILocation(line: 645, column: 4, scope: !1012)
!1016 = !DILocation(line: 645, column: 14, scope: !1012)
!1017 = !DILocation(line: 645, column: 3, scope: !1012)
!1018 = !DILocation(line: 646, column: 27, scope: !350)
!1019 = !DILocation(line: 646, column: 6, scope: !350)
!1020 = !DILocation(line: 646, column: 4, scope: !350)
!1021 = !DILocation(line: 647, column: 6, scope: !1022)
!1022 = distinct !DILexicalBlock(scope: !350, file: !1, line: 647, column: 6)
!1023 = !DILocation(line: 647, column: 8, scope: !1022)
!1024 = !DILocation(line: 647, column: 6, scope: !350)
!1025 = !DILocation(line: 648, column: 3, scope: !1022)
!1026 = !DILocation(line: 649, column: 11, scope: !350)
!1027 = !DILocation(line: 649, column: 9, scope: !350)
!1028 = !DILocation(line: 650, column: 2, scope: !350)
!1029 = !DILocation(line: 651, column: 19, scope: !1030)
!1030 = distinct !DILexicalBlock(scope: !1031, file: !1, line: 650, column: 11)
!1031 = distinct !DILexicalBlock(scope: !1032, file: !1, line: 650, column: 2)
!1032 = distinct !DILexicalBlock(scope: !350, file: !1, line: 650, column: 2)
!1033 = !DILocation(line: 651, column: 9, scope: !1030)
!1034 = !DILocation(line: 651, column: 7, scope: !1030)
!1035 = !DILocation(line: 654, column: 7, scope: !1036)
!1036 = distinct !DILexicalBlock(scope: !1030, file: !1, line: 654, column: 7)
!1037 = !DILocation(line: 654, column: 11, scope: !1036)
!1038 = !DILocation(line: 654, column: 16, scope: !1036)
!1039 = !DILocation(line: 654, column: 19, scope: !1040)
!1040 = !DILexicalBlockFile(scope: !1036, file: !1, discriminator: 1)
!1041 = !DILocation(line: 654, column: 22, scope: !1040)
!1042 = !DILocation(line: 654, column: 7, scope: !1040)
!1043 = !DILocation(line: 655, column: 4, scope: !1036)
!1044 = !DILocation(line: 656, column: 8, scope: !1045)
!1045 = distinct !DILexicalBlock(scope: !1030, file: !1, line: 656, column: 7)
!1046 = !DILocation(line: 656, column: 7, scope: !1030)
!1047 = !DILocation(line: 659, column: 4, scope: !1048)
!1048 = distinct !DILexicalBlock(scope: !1045, file: !1, line: 656, column: 19)
!1049 = !DILocation(line: 659, column: 11, scope: !1050)
!1050 = !DILexicalBlockFile(scope: !1048, file: !1, discriminator: 1)
!1051 = !DILocation(line: 659, column: 15, scope: !1050)
!1052 = !DILocation(line: 659, column: 19, scope: !1050)
!1053 = !DILocation(line: 659, column: 24, scope: !1054)
!1054 = !DILexicalBlockFile(scope: !1048, file: !1, discriminator: 2)
!1055 = !DILocation(line: 659, column: 23, scope: !1054)
!1056 = !DILocation(line: 659, column: 26, scope: !1054)
!1057 = !DILocation(line: 659, column: 33, scope: !1054)
!1058 = !DILocation(line: 659, column: 37, scope: !1059)
!1059 = !DILexicalBlockFile(scope: !1048, file: !1, discriminator: 3)
!1060 = !DILocation(line: 659, column: 36, scope: !1059)
!1061 = !DILocation(line: 659, column: 39, scope: !1059)
!1062 = !DILocation(line: 659, column: 33, scope: !1059)
!1063 = !DILocation(line: 659, column: 4, scope: !1064)
!1064 = !DILexicalBlockFile(scope: !1048, file: !1, discriminator: 4)
!1065 = !DILocation(line: 660, column: 5, scope: !1066)
!1066 = distinct !DILexicalBlock(scope: !1048, file: !1, line: 659, column: 49)
!1067 = !DILocation(line: 661, column: 5, scope: !1066)
!1068 = !DILocation(line: 662, column: 5, scope: !1066)
!1069 = !DILocation(line: 659, column: 4, scope: !1070)
!1070 = !DILexicalBlockFile(scope: !1048, file: !1, discriminator: 5)
!1071 = !DILocation(line: 665, column: 8, scope: !1072)
!1072 = distinct !DILexicalBlock(scope: !1048, file: !1, line: 665, column: 8)
!1073 = !DILocation(line: 665, column: 13, scope: !1072)
!1074 = !DILocation(line: 665, column: 20, scope: !1072)
!1075 = !DILocation(line: 665, column: 23, scope: !1076)
!1076 = !DILexicalBlockFile(scope: !1072, file: !1, discriminator: 1)
!1077 = !DILocation(line: 665, column: 28, scope: !1076)
!1078 = !DILocation(line: 665, column: 36, scope: !1076)
!1079 = !DILocation(line: 665, column: 39, scope: !1080)
!1080 = !DILexicalBlockFile(scope: !1072, file: !1, discriminator: 2)
!1081 = !DILocation(line: 665, column: 44, scope: !1080)
!1082 = !DILocation(line: 665, column: 8, scope: !1080)
!1083 = !DILocation(line: 666, column: 10, scope: !1084)
!1084 = distinct !DILexicalBlock(scope: !1072, file: !1, line: 665, column: 53)
!1085 = !DILocation(line: 666, column: 7, scope: !1084)
!1086 = !DILocation(line: 667, column: 14, scope: !1084)
!1087 = !DILocation(line: 667, column: 11, scope: !1084)
!1088 = !DILocation(line: 668, column: 5, scope: !1084)
!1089 = !DILocation(line: 670, column: 3, scope: !1048)
!1090 = !DILocation(line: 673, column: 25, scope: !1091)
!1091 = distinct !DILexicalBlock(scope: !1092, file: !1, line: 673, column: 8)
!1092 = distinct !DILexicalBlock(scope: !1045, file: !1, line: 670, column: 10)
!1093 = !DILocation(line: 673, column: 28, scope: !1091)
!1094 = !DILocation(line: 673, column: 8, scope: !1091)
!1095 = !DILocation(line: 673, column: 39, scope: !1091)
!1096 = !DILocation(line: 673, column: 8, scope: !1092)
!1097 = !DILocation(line: 674, column: 5, scope: !1091)
!1098 = !DILocation(line: 675, column: 8, scope: !1099)
!1099 = distinct !DILexicalBlock(scope: !1092, file: !1, line: 675, column: 8)
!1100 = !DILocation(line: 675, column: 18, scope: !1099)
!1101 = !DILocation(line: 675, column: 8, scope: !1092)
!1102 = !DILocation(line: 676, column: 23, scope: !1099)
!1103 = !DILocation(line: 676, column: 20, scope: !1099)
!1104 = !DILocation(line: 676, column: 5, scope: !1099)
!1105 = !DILocation(line: 677, column: 10, scope: !1106)
!1106 = distinct !DILexicalBlock(scope: !1092, file: !1, line: 677, column: 8)
!1107 = !DILocation(line: 677, column: 14, scope: !1106)
!1108 = !DILocation(line: 677, column: 13, scope: !1106)
!1109 = !DILocation(line: 677, column: 16, scope: !1106)
!1110 = !DILocation(line: 677, column: 8, scope: !1106)
!1111 = !DILocation(line: 677, column: 20, scope: !1106)
!1112 = !DILocation(line: 677, column: 8, scope: !1092)
!1113 = !DILocation(line: 678, column: 9, scope: !1114)
!1114 = distinct !DILexicalBlock(scope: !1115, file: !1, line: 678, column: 9)
!1115 = distinct !DILexicalBlock(scope: !1106, file: !1, line: 677, column: 29)
!1116 = !DILocation(line: 678, column: 19, scope: !1114)
!1117 = !DILocation(line: 678, column: 24, scope: !1114)
!1118 = !DILocation(line: 679, column: 9, scope: !1114)
!1119 = !DILocation(line: 679, column: 21, scope: !1114)
!1120 = !DILocation(line: 678, column: 9, scope: !1121)
!1121 = !DILexicalBlockFile(scope: !1115, file: !1, discriminator: 1)
!1122 = !DILocation(line: 680, column: 6, scope: !1114)
!1123 = !DILocation(line: 681, column: 15, scope: !1115)
!1124 = !DILocation(line: 682, column: 4, scope: !1115)
!1125 = !DILocation(line: 683, column: 9, scope: !1092)
!1126 = !DILocation(line: 683, column: 6, scope: !1092)
!1127 = !DILocation(line: 684, column: 13, scope: !1092)
!1128 = !DILocation(line: 684, column: 10, scope: !1092)
!1129 = !DILocation(line: 685, column: 4, scope: !1092)
!1130 = !DILocation(line: 687, column: 7, scope: !1131)
!1131 = distinct !DILexicalBlock(scope: !1030, file: !1, line: 687, column: 7)
!1132 = !DILocation(line: 687, column: 12, scope: !1131)
!1133 = !DILocation(line: 687, column: 7, scope: !1030)
!1134 = !DILocalVariable(name: "last_is_path", scope: !1135, file: !1, line: 688, type: !23)
!1135 = distinct !DILexicalBlock(scope: !1131, file: !1, line: 687, column: 20)
!1136 = !DILocation(line: 688, column: 8, scope: !1135)
!1137 = !DILocalVariable(name: "keywords", scope: !1135, file: !1, line: 688, type: !23)
!1138 = !DILocation(line: 688, column: 22, scope: !1135)
!1139 = !DILocation(line: 690, column: 25, scope: !1135)
!1140 = !DILocation(line: 690, column: 28, scope: !1135)
!1141 = !DILocation(line: 690, column: 33, scope: !1135)
!1142 = !DILocation(line: 690, column: 15, scope: !1135)
!1143 = !DILocation(line: 690, column: 13, scope: !1135)
!1144 = !DILocation(line: 691, column: 8, scope: !1145)
!1145 = distinct !DILexicalBlock(scope: !1135, file: !1, line: 691, column: 8)
!1146 = !DILocation(line: 691, column: 17, scope: !1145)
!1147 = !DILocation(line: 691, column: 8, scope: !1135)
!1148 = !DILocation(line: 692, column: 23, scope: !1149)
!1149 = distinct !DILexicalBlock(scope: !1145, file: !1, line: 691, column: 23)
!1150 = !DILocation(line: 692, column: 20, scope: !1149)
!1151 = !DILocation(line: 693, column: 9, scope: !1152)
!1152 = distinct !DILexicalBlock(scope: !1149, file: !1, line: 693, column: 9)
!1153 = !DILocation(line: 693, column: 16, scope: !1152)
!1154 = !DILocation(line: 693, column: 9, scope: !1149)
!1155 = !DILocation(line: 694, column: 10, scope: !1156)
!1156 = distinct !DILexicalBlock(scope: !1157, file: !1, line: 694, column: 10)
!1157 = distinct !DILexicalBlock(scope: !1152, file: !1, line: 693, column: 22)
!1158 = !DILocation(line: 694, column: 10, scope: !1157)
!1159 = !DILocation(line: 695, column: 14, scope: !1156)
!1160 = !DILocation(line: 695, column: 7, scope: !1156)
!1161 = !DILocation(line: 696, column: 15, scope: !1162)
!1162 = distinct !DILexicalBlock(scope: !1156, file: !1, line: 696, column: 15)
!1163 = !DILocation(line: 696, column: 24, scope: !1162)
!1164 = !DILocation(line: 696, column: 15, scope: !1156)
!1165 = !DILocation(line: 698, column: 14, scope: !1162)
!1166 = !DILocation(line: 698, column: 7, scope: !1162)
!1167 = !DILocation(line: 699, column: 5, scope: !1157)
!1168 = !DILocation(line: 699, column: 16, scope: !1169)
!1169 = !DILexicalBlockFile(scope: !1170, file: !1, discriminator: 1)
!1170 = distinct !DILexicalBlock(scope: !1152, file: !1, line: 699, column: 16)
!1171 = !DILocation(line: 699, column: 23, scope: !1169)
!1172 = !DILocation(line: 700, column: 11, scope: !1173)
!1173 = distinct !DILexicalBlock(scope: !1174, file: !1, line: 700, column: 10)
!1174 = distinct !DILexicalBlock(scope: !1170, file: !1, line: 699, column: 29)
!1175 = !DILocation(line: 700, column: 24, scope: !1173)
!1176 = !DILocation(line: 700, column: 27, scope: !1177)
!1177 = !DILexicalBlockFile(scope: !1173, file: !1, discriminator: 1)
!1178 = !DILocation(line: 700, column: 36, scope: !1177)
!1179 = !DILocation(line: 700, column: 10, scope: !1177)
!1180 = !DILocation(line: 704, column: 7, scope: !1173)
!1181 = !DILocation(line: 705, column: 5, scope: !1174)
!1182 = !DILocation(line: 706, column: 10, scope: !1183)
!1183 = distinct !DILexicalBlock(scope: !1149, file: !1, line: 706, column: 9)
!1184 = !DILocation(line: 706, column: 23, scope: !1183)
!1185 = !DILocation(line: 706, column: 28, scope: !1186)
!1186 = !DILexicalBlockFile(scope: !1183, file: !1, discriminator: 1)
!1187 = !DILocation(line: 706, column: 32, scope: !1186)
!1188 = !DILocation(line: 706, column: 31, scope: !1186)
!1189 = !DILocation(line: 706, column: 34, scope: !1186)
!1190 = !DILocation(line: 706, column: 26, scope: !1186)
!1191 = !DILocation(line: 706, column: 38, scope: !1186)
!1192 = !DILocation(line: 706, column: 9, scope: !1186)
!1193 = !DILocation(line: 708, column: 16, scope: !1183)
!1194 = !DILocation(line: 708, column: 6, scope: !1183)
!1195 = !DILocation(line: 713, column: 10, scope: !1196)
!1196 = distinct !DILexicalBlock(scope: !1197, file: !1, line: 713, column: 10)
!1197 = distinct !DILexicalBlock(scope: !1183, file: !1, line: 709, column: 10)
!1198 = !DILocation(line: 713, column: 22, scope: !1196)
!1199 = !DILocation(line: 713, column: 10, scope: !1197)
!1200 = !DILocation(line: 714, column: 7, scope: !1196)
!1201 = !DILocation(line: 716, column: 4, scope: !1149)
!1202 = !DILocation(line: 717, column: 5, scope: !1145)
!1203 = !DILocation(line: 718, column: 3, scope: !1135)
!1204 = !DILocation(line: 718, column: 14, scope: !1205)
!1205 = !DILexicalBlockFile(scope: !1206, file: !1, discriminator: 1)
!1206 = distinct !DILexicalBlock(scope: !1131, file: !1, line: 718, column: 14)
!1207 = !DILocation(line: 718, column: 18, scope: !1205)
!1208 = !DILocation(line: 718, column: 22, scope: !1205)
!1209 = !DILocation(line: 718, column: 33, scope: !1210)
!1210 = !DILexicalBlockFile(scope: !1206, file: !1, discriminator: 2)
!1211 = !DILocation(line: 718, column: 25, scope: !1210)
!1212 = !DILocation(line: 718, column: 47, scope: !1210)
!1213 = !DILocation(line: 718, column: 14, scope: !1210)
!1214 = !DILocation(line: 719, column: 25, scope: !1215)
!1215 = distinct !DILexicalBlock(scope: !1216, file: !1, line: 719, column: 8)
!1216 = distinct !DILexicalBlock(scope: !1206, file: !1, line: 718, column: 53)
!1217 = !DILocation(line: 719, column: 26, scope: !1215)
!1218 = !DILocation(line: 719, column: 30, scope: !1215)
!1219 = !DILocation(line: 719, column: 33, scope: !1215)
!1220 = !DILocation(line: 719, column: 8, scope: !1215)
!1221 = !DILocation(line: 719, column: 43, scope: !1215)
!1222 = !DILocation(line: 719, column: 8, scope: !1216)
!1223 = !DILocation(line: 720, column: 5, scope: !1215)
!1224 = !DILocation(line: 722, column: 10, scope: !1225)
!1225 = distinct !DILexicalBlock(scope: !1216, file: !1, line: 722, column: 8)
!1226 = !DILocation(line: 722, column: 14, scope: !1225)
!1227 = !DILocation(line: 722, column: 13, scope: !1225)
!1228 = !DILocation(line: 722, column: 16, scope: !1225)
!1229 = !DILocation(line: 722, column: 8, scope: !1225)
!1230 = !DILocation(line: 722, column: 20, scope: !1225)
!1231 = !DILocation(line: 722, column: 8, scope: !1216)
!1232 = !DILocation(line: 723, column: 15, scope: !1225)
!1233 = !DILocation(line: 723, column: 5, scope: !1225)
!1234 = !DILocation(line: 724, column: 3, scope: !1216)
!1235 = !DILocation(line: 724, column: 14, scope: !1236)
!1236 = !DILexicalBlockFile(scope: !1237, file: !1, discriminator: 1)
!1237 = distinct !DILexicalBlock(scope: !1206, file: !1, line: 724, column: 14)
!1238 = !DILocation(line: 724, column: 18, scope: !1236)
!1239 = !DILocation(line: 724, column: 22, scope: !1236)
!1240 = !DILocation(line: 724, column: 33, scope: !1241)
!1241 = !DILexicalBlockFile(scope: !1237, file: !1, discriminator: 2)
!1242 = !DILocation(line: 724, column: 25, scope: !1241)
!1243 = !DILocation(line: 724, column: 49, scope: !1241)
!1244 = !DILocation(line: 724, column: 14, scope: !1241)
!1245 = !DILocation(line: 725, column: 25, scope: !1246)
!1246 = distinct !DILexicalBlock(scope: !1247, file: !1, line: 725, column: 8)
!1247 = distinct !DILexicalBlock(scope: !1237, file: !1, line: 724, column: 55)
!1248 = !DILocation(line: 725, column: 26, scope: !1246)
!1249 = !DILocation(line: 725, column: 30, scope: !1246)
!1250 = !DILocation(line: 725, column: 33, scope: !1246)
!1251 = !DILocation(line: 725, column: 8, scope: !1246)
!1252 = !DILocation(line: 725, column: 43, scope: !1246)
!1253 = !DILocation(line: 725, column: 8, scope: !1247)
!1254 = !DILocation(line: 726, column: 5, scope: !1246)
!1255 = !DILocation(line: 728, column: 10, scope: !1256)
!1256 = distinct !DILexicalBlock(scope: !1247, file: !1, line: 728, column: 8)
!1257 = !DILocation(line: 728, column: 14, scope: !1256)
!1258 = !DILocation(line: 728, column: 13, scope: !1256)
!1259 = !DILocation(line: 728, column: 16, scope: !1256)
!1260 = !DILocation(line: 728, column: 8, scope: !1256)
!1261 = !DILocation(line: 728, column: 20, scope: !1256)
!1262 = !DILocation(line: 728, column: 8, scope: !1247)
!1263 = !DILocation(line: 729, column: 15, scope: !1256)
!1264 = !DILocation(line: 729, column: 5, scope: !1256)
!1265 = !DILocation(line: 730, column: 3, scope: !1247)
!1266 = !DILocation(line: 731, column: 4, scope: !1237)
!1267 = !DILocation(line: 734, column: 8, scope: !1030)
!1268 = !DILocation(line: 734, column: 5, scope: !1030)
!1269 = !DILocation(line: 735, column: 12, scope: !1030)
!1270 = !DILocation(line: 735, column: 9, scope: !1030)
!1271 = !DILocation(line: 650, column: 2, scope: !1272)
!1272 = !DILexicalBlockFile(scope: !1031, file: !1, discriminator: 1)
!1273 = !DILocation(line: 737, column: 6, scope: !1274)
!1274 = distinct !DILexicalBlock(scope: !350, file: !1, line: 737, column: 6)
!1275 = !DILocation(line: 737, column: 16, scope: !1274)
!1276 = !DILocation(line: 737, column: 33, scope: !1274)
!1277 = !DILocation(line: 737, column: 37, scope: !1278)
!1278 = !DILexicalBlockFile(scope: !1274, file: !1, discriminator: 1)
!1279 = !DILocation(line: 737, column: 47, scope: !1278)
!1280 = !DILocation(line: 737, column: 51, scope: !1278)
!1281 = !DILocation(line: 737, column: 54, scope: !1282)
!1282 = !DILexicalBlockFile(scope: !1274, file: !1, discriminator: 2)
!1283 = !DILocation(line: 737, column: 58, scope: !1282)
!1284 = !DILocation(line: 737, column: 6, scope: !1282)
!1285 = !DILocation(line: 738, column: 7, scope: !1286)
!1286 = distinct !DILexicalBlock(scope: !1287, file: !1, line: 738, column: 7)
!1287 = distinct !DILexicalBlock(scope: !1274, file: !1, line: 737, column: 65)
!1288 = !DILocation(line: 738, column: 17, scope: !1286)
!1289 = !DILocation(line: 738, column: 7, scope: !1287)
!1290 = !DILocation(line: 739, column: 8, scope: !1291)
!1291 = distinct !DILexicalBlock(scope: !1292, file: !1, line: 739, column: 8)
!1292 = distinct !DILexicalBlock(scope: !1286, file: !1, line: 738, column: 26)
!1293 = !DILocation(line: 739, column: 15, scope: !1291)
!1294 = !DILocation(line: 739, column: 8, scope: !1292)
!1295 = !DILocation(line: 740, column: 6, scope: !1291)
!1296 = !DILocation(line: 740, column: 16, scope: !1291)
!1297 = !DILocation(line: 740, column: 5, scope: !1291)
!1298 = !DILocation(line: 741, column: 3, scope: !1292)
!1299 = !DILocation(line: 742, column: 3, scope: !1287)
!1300 = !DILocation(line: 745, column: 2, scope: !350)
!1301 = !DILocation(line: 746, column: 1, scope: !350)
!1302 = !DILocalVariable(name: "a", arg: 1, scope: !354, file: !1, line: 319, type: !4)
!1303 = !DILocation(line: 319, column: 32, scope: !354)
!1304 = !DILocalVariable(name: "b", arg: 2, scope: !354, file: !1, line: 320, type: !357)
!1305 = !DILocation(line: 320, column: 18, scope: !354)
!1306 = !DILocalVariable(name: "avail", arg: 3, scope: !354, file: !1, line: 320, type: !358)
!1307 = !DILocation(line: 320, column: 30, scope: !354)
!1308 = !DILocalVariable(name: "ravail", arg: 4, scope: !354, file: !1, line: 320, type: !358)
!1309 = !DILocation(line: 320, column: 46, scope: !354)
!1310 = !DILocalVariable(name: "nl", arg: 5, scope: !354, file: !1, line: 320, type: !358)
!1311 = !DILocation(line: 320, column: 63, scope: !354)
!1312 = !DILocalVariable(name: "len", scope: !354, file: !1, line: 322, type: !38)
!1313 = !DILocation(line: 322, column: 10, scope: !354)
!1314 = !DILocalVariable(name: "quit", scope: !354, file: !1, line: 323, type: !23)
!1315 = !DILocation(line: 323, column: 6, scope: !354)
!1316 = !DILocation(line: 325, column: 7, scope: !354)
!1317 = !DILocation(line: 326, column: 7, scope: !1318)
!1318 = distinct !DILexicalBlock(scope: !354, file: !1, line: 326, column: 6)
!1319 = !DILocation(line: 326, column: 6, scope: !1318)
!1320 = !DILocation(line: 326, column: 13, scope: !1318)
!1321 = !DILocation(line: 326, column: 6, scope: !354)
!1322 = !DILocation(line: 327, column: 4, scope: !1323)
!1323 = distinct !DILexicalBlock(scope: !1318, file: !1, line: 326, column: 19)
!1324 = !DILocation(line: 327, column: 7, scope: !1323)
!1325 = !DILocation(line: 328, column: 7, scope: !1323)
!1326 = !DILocation(line: 329, column: 2, scope: !1323)
!1327 = !DILocation(line: 330, column: 24, scope: !1318)
!1328 = !DILocation(line: 330, column: 23, scope: !1318)
!1329 = !DILocation(line: 330, column: 28, scope: !1318)
!1330 = !DILocation(line: 330, column: 27, scope: !1318)
!1331 = !DILocation(line: 330, column: 35, scope: !1318)
!1332 = !DILocation(line: 330, column: 9, scope: !1318)
!1333 = !DILocation(line: 330, column: 7, scope: !1318)
!1334 = !DILocation(line: 334, column: 2, scope: !354)
!1335 = !DILocation(line: 334, column: 10, scope: !1336)
!1336 = !DILexicalBlockFile(scope: !354, file: !1, discriminator: 1)
!1337 = !DILocation(line: 334, column: 9, scope: !1336)
!1338 = !DILocation(line: 334, column: 13, scope: !1336)
!1339 = !DILocation(line: 334, column: 18, scope: !1336)
!1340 = !DILocation(line: 334, column: 21, scope: !1341)
!1341 = !DILexicalBlockFile(scope: !354, file: !1, discriminator: 2)
!1342 = !DILocation(line: 334, column: 29, scope: !1341)
!1343 = !DILocation(line: 334, column: 28, scope: !1341)
!1344 = !DILocation(line: 334, column: 25, scope: !1341)
!1345 = !DILocation(line: 334, column: 35, scope: !1341)
!1346 = !DILocation(line: 334, column: 39, scope: !1347)
!1347 = !DILexicalBlockFile(scope: !354, file: !1, discriminator: 3)
!1348 = !DILocation(line: 334, column: 38, scope: !1347)
!1349 = !DILocation(line: 334, column: 2, scope: !1350)
!1350 = !DILexicalBlockFile(scope: !354, file: !1, discriminator: 4)
!1351 = !DILocalVariable(name: "diff", scope: !1352, file: !1, line: 335, type: !38)
!1352 = distinct !DILexicalBlock(scope: !354, file: !1, line: 334, column: 45)
!1353 = !DILocation(line: 335, column: 11, scope: !1352)
!1354 = !DILocation(line: 335, column: 19, scope: !1352)
!1355 = !DILocation(line: 335, column: 18, scope: !1352)
!1356 = !DILocation(line: 335, column: 29, scope: !1352)
!1357 = !DILocation(line: 335, column: 28, scope: !1352)
!1358 = !DILocation(line: 335, column: 26, scope: !1352)
!1359 = !DILocalVariable(name: "nbytes_req", scope: !1352, file: !1, line: 336, type: !45)
!1360 = !DILocation(line: 336, column: 10, scope: !1352)
!1361 = !DILocation(line: 336, column: 25, scope: !1352)
!1362 = !DILocation(line: 336, column: 24, scope: !1352)
!1363 = !DILocation(line: 336, column: 31, scope: !1352)
!1364 = !DILocation(line: 336, column: 38, scope: !1352)
!1365 = !DILocalVariable(name: "tested", scope: !1352, file: !1, line: 337, type: !38)
!1366 = !DILocation(line: 337, column: 11, scope: !1352)
!1367 = !DILocation(line: 341, column: 7, scope: !1368)
!1368 = distinct !DILexicalBlock(scope: !1352, file: !1, line: 341, column: 7)
!1369 = !DILocation(line: 341, column: 29, scope: !1368)
!1370 = !DILocation(line: 341, column: 28, scope: !1368)
!1371 = !DILocation(line: 341, column: 36, scope: !1368)
!1372 = !DILocation(line: 341, column: 18, scope: !1368)
!1373 = !DILocation(line: 341, column: 7, scope: !1352)
!1374 = !DILocation(line: 342, column: 15, scope: !1368)
!1375 = !DILocation(line: 342, column: 4, scope: !1368)
!1376 = !DILocation(line: 344, column: 29, scope: !1352)
!1377 = !DILocation(line: 344, column: 32, scope: !1352)
!1378 = !DILocation(line: 344, column: 44, scope: !1352)
!1379 = !DILocation(line: 344, column: 8, scope: !1352)
!1380 = !DILocation(line: 344, column: 4, scope: !1352)
!1381 = !DILocation(line: 344, column: 6, scope: !1352)
!1382 = !DILocation(line: 345, column: 8, scope: !1383)
!1383 = distinct !DILexicalBlock(scope: !1352, file: !1, line: 345, column: 7)
!1384 = !DILocation(line: 345, column: 7, scope: !1383)
!1385 = !DILocation(line: 345, column: 10, scope: !1383)
!1386 = !DILocation(line: 345, column: 7, scope: !1352)
!1387 = !DILocation(line: 346, column: 9, scope: !1388)
!1388 = distinct !DILexicalBlock(scope: !1389, file: !1, line: 346, column: 8)
!1389 = distinct !DILexicalBlock(scope: !1383, file: !1, line: 345, column: 19)
!1390 = !DILocation(line: 346, column: 8, scope: !1388)
!1391 = !DILocation(line: 346, column: 20, scope: !1388)
!1392 = !DILocation(line: 346, column: 19, scope: !1388)
!1393 = !DILocation(line: 346, column: 16, scope: !1388)
!1394 = !DILocation(line: 346, column: 8, scope: !1389)
!1395 = !DILocation(line: 347, column: 5, scope: !1388)
!1396 = !DILocation(line: 349, column: 30, scope: !1389)
!1397 = !DILocation(line: 349, column: 34, scope: !1389)
!1398 = !DILocation(line: 349, column: 33, scope: !1389)
!1399 = !DILocation(line: 349, column: 41, scope: !1389)
!1400 = !DILocation(line: 349, column: 9, scope: !1389)
!1401 = !DILocation(line: 349, column: 5, scope: !1389)
!1402 = !DILocation(line: 349, column: 7, scope: !1389)
!1403 = !DILocation(line: 350, column: 9, scope: !1389)
!1404 = !DILocation(line: 351, column: 3, scope: !1389)
!1405 = !DILocation(line: 352, column: 14, scope: !1352)
!1406 = !DILocation(line: 352, column: 13, scope: !1352)
!1407 = !DILocation(line: 352, column: 4, scope: !1352)
!1408 = !DILocation(line: 352, column: 11, scope: !1352)
!1409 = !DILocation(line: 353, column: 9, scope: !1352)
!1410 = !DILocation(line: 353, column: 4, scope: !1352)
!1411 = !DILocation(line: 353, column: 6, scope: !1352)
!1412 = !DILocation(line: 354, column: 13, scope: !1352)
!1413 = !DILocation(line: 354, column: 4, scope: !1352)
!1414 = !DILocation(line: 354, column: 10, scope: !1352)
!1415 = !DILocation(line: 355, column: 12, scope: !1352)
!1416 = !DILocation(line: 355, column: 10, scope: !1352)
!1417 = !DILocation(line: 356, column: 24, scope: !1352)
!1418 = !DILocation(line: 356, column: 23, scope: !1352)
!1419 = !DILocation(line: 356, column: 28, scope: !1352)
!1420 = !DILocation(line: 356, column: 26, scope: !1352)
!1421 = !DILocation(line: 356, column: 34, scope: !1352)
!1422 = !DILocation(line: 356, column: 33, scope: !1352)
!1423 = !DILocation(line: 356, column: 42, scope: !1352)
!1424 = !DILocation(line: 356, column: 40, scope: !1352)
!1425 = !DILocation(line: 356, column: 47, scope: !1352)
!1426 = !DILocation(line: 356, column: 9, scope: !1352)
!1427 = !DILocation(line: 356, column: 7, scope: !1352)
!1428 = !DILocation(line: 357, column: 7, scope: !1429)
!1429 = distinct !DILexicalBlock(scope: !1352, file: !1, line: 357, column: 7)
!1430 = !DILocation(line: 357, column: 11, scope: !1429)
!1431 = !DILocation(line: 357, column: 7, scope: !1352)
!1432 = !DILocation(line: 358, column: 11, scope: !1429)
!1433 = !DILocation(line: 358, column: 8, scope: !1429)
!1434 = !DILocation(line: 358, column: 4, scope: !1429)
!1435 = !DILocation(line: 334, column: 2, scope: !1436)
!1436 = !DILexicalBlockFile(scope: !354, file: !1, discriminator: 5)
!1437 = !DILocation(line: 360, column: 10, scope: !354)
!1438 = !DILocation(line: 360, column: 2, scope: !354)
!1439 = !DILocation(line: 361, column: 1, scope: !354)
!1440 = !DILocalVariable(name: "p", arg: 1, scope: !362, file: !1, line: 469, type: !80)
!1441 = !DILocation(line: 469, column: 30, scope: !362)
!1442 = !DILocalVariable(name: "len", arg: 2, scope: !362, file: !1, line: 469, type: !38)
!1443 = !DILocation(line: 469, column: 42, scope: !362)
!1444 = !DILocalVariable(name: "unset", arg: 3, scope: !362, file: !1, line: 469, type: !23)
!1445 = !DILocation(line: 469, column: 51, scope: !362)
!1446 = !DILocalVariable(name: "last_is_path", arg: 4, scope: !362, file: !1, line: 469, type: !23)
!1447 = !DILocation(line: 469, column: 62, scope: !362)
!1448 = !DILocalVariable(name: "l", scope: !362, file: !1, line: 471, type: !23)
!1449 = !DILocation(line: 471, column: 6, scope: !362)
!1450 = !DILocalVariable(name: "keycnt", scope: !362, file: !1, line: 472, type: !23)
!1451 = !DILocation(line: 472, column: 6, scope: !362)
!1452 = !DILocation(line: 474, column: 2, scope: !362)
!1453 = !DILocation(line: 474, column: 9, scope: !1454)
!1454 = !DILexicalBlockFile(scope: !362, file: !1, discriminator: 1)
!1455 = !DILocation(line: 474, column: 13, scope: !1454)
!1456 = !DILocation(line: 474, column: 17, scope: !1454)
!1457 = !DILocation(line: 474, column: 21, scope: !1458)
!1458 = !DILexicalBlockFile(scope: !362, file: !1, discriminator: 2)
!1459 = !DILocation(line: 474, column: 20, scope: !1458)
!1460 = !DILocation(line: 474, column: 17, scope: !1458)
!1461 = !DILocation(line: 474, column: 2, scope: !1462)
!1462 = !DILexicalBlockFile(scope: !362, file: !1, discriminator: 3)
!1463 = !DILocalVariable(name: "blank", scope: !1464, file: !1, line: 475, type: !23)
!1464 = distinct !DILexicalBlock(scope: !362, file: !1, line: 474, column: 24)
!1465 = !DILocation(line: 475, column: 7, scope: !1464)
!1466 = !DILocation(line: 478, column: 3, scope: !1464)
!1467 = !DILocation(line: 478, column: 10, scope: !1468)
!1468 = !DILexicalBlockFile(scope: !1464, file: !1, discriminator: 1)
!1469 = !DILocation(line: 478, column: 14, scope: !1468)
!1470 = !DILocation(line: 478, column: 17, scope: !1468)
!1471 = !DILocation(line: 478, column: 22, scope: !1472)
!1472 = !DILexicalBlockFile(scope: !1464, file: !1, discriminator: 2)
!1473 = !DILocation(line: 478, column: 21, scope: !1472)
!1474 = !DILocation(line: 478, column: 24, scope: !1472)
!1475 = !DILocation(line: 478, column: 31, scope: !1472)
!1476 = !DILocation(line: 478, column: 35, scope: !1477)
!1477 = !DILexicalBlockFile(scope: !1464, file: !1, discriminator: 3)
!1478 = !DILocation(line: 478, column: 34, scope: !1477)
!1479 = !DILocation(line: 478, column: 37, scope: !1477)
!1480 = !DILocation(line: 478, column: 31, scope: !1477)
!1481 = !DILocation(line: 478, column: 3, scope: !1482)
!1482 = !DILexicalBlockFile(scope: !1464, file: !1, discriminator: 4)
!1483 = !DILocation(line: 479, column: 4, scope: !1484)
!1484 = distinct !DILexicalBlock(scope: !1464, file: !1, line: 478, column: 47)
!1485 = !DILocation(line: 480, column: 4, scope: !1484)
!1486 = !DILocation(line: 481, column: 10, scope: !1484)
!1487 = !DILocation(line: 478, column: 3, scope: !1488)
!1488 = !DILexicalBlockFile(scope: !1464, file: !1, discriminator: 5)
!1489 = !DILocation(line: 483, column: 8, scope: !1490)
!1490 = distinct !DILexicalBlock(scope: !1464, file: !1, line: 483, column: 7)
!1491 = !DILocation(line: 483, column: 7, scope: !1490)
!1492 = !DILocation(line: 483, column: 10, scope: !1490)
!1493 = !DILocation(line: 483, column: 18, scope: !1490)
!1494 = !DILocation(line: 483, column: 22, scope: !1495)
!1495 = !DILexicalBlockFile(scope: !1490, file: !1, discriminator: 1)
!1496 = !DILocation(line: 483, column: 21, scope: !1495)
!1497 = !DILocation(line: 483, column: 24, scope: !1495)
!1498 = !DILocation(line: 483, column: 7, scope: !1495)
!1499 = !DILocation(line: 484, column: 4, scope: !1490)
!1500 = !DILocation(line: 485, column: 7, scope: !1501)
!1501 = distinct !DILexicalBlock(scope: !1464, file: !1, line: 485, column: 7)
!1502 = !DILocation(line: 485, column: 12, scope: !1501)
!1503 = !DILocation(line: 485, column: 20, scope: !1501)
!1504 = !DILocation(line: 485, column: 24, scope: !1505)
!1505 = !DILexicalBlockFile(scope: !1501, file: !1, discriminator: 1)
!1506 = !DILocation(line: 485, column: 29, scope: !1505)
!1507 = !DILocation(line: 485, column: 37, scope: !1505)
!1508 = !DILocation(line: 485, column: 40, scope: !1509)
!1509 = !DILexicalBlockFile(scope: !1501, file: !1, discriminator: 2)
!1510 = !DILocation(line: 485, column: 45, scope: !1509)
!1511 = !DILocation(line: 485, column: 7, scope: !1509)
!1512 = !DILocation(line: 486, column: 4, scope: !1501)
!1513 = !DILocation(line: 487, column: 8, scope: !1514)
!1514 = distinct !DILexicalBlock(scope: !1464, file: !1, line: 487, column: 7)
!1515 = !DILocation(line: 487, column: 14, scope: !1514)
!1516 = !DILocation(line: 487, column: 18, scope: !1517)
!1517 = !DILexicalBlockFile(scope: !1514, file: !1, discriminator: 1)
!1518 = !DILocation(line: 487, column: 7, scope: !1517)
!1519 = !DILocation(line: 488, column: 4, scope: !1514)
!1520 = !DILocation(line: 489, column: 7, scope: !1521)
!1521 = distinct !DILexicalBlock(scope: !1464, file: !1, line: 489, column: 7)
!1522 = !DILocation(line: 489, column: 20, scope: !1521)
!1523 = !DILocation(line: 489, column: 23, scope: !1524)
!1524 = !DILexicalBlockFile(scope: !1521, file: !1, discriminator: 1)
!1525 = !DILocation(line: 489, column: 27, scope: !1524)
!1526 = !DILocation(line: 489, column: 7, scope: !1524)
!1527 = !DILocation(line: 490, column: 13, scope: !1521)
!1528 = !DILocation(line: 490, column: 5, scope: !1521)
!1529 = !DILocation(line: 492, column: 7, scope: !1530)
!1530 = distinct !DILexicalBlock(scope: !1464, file: !1, line: 492, column: 7)
!1531 = !DILocation(line: 492, column: 7, scope: !1464)
!1532 = !DILocation(line: 493, column: 19, scope: !1533)
!1533 = distinct !DILexicalBlock(scope: !1530, file: !1, line: 492, column: 14)
!1534 = !DILocation(line: 493, column: 29, scope: !1533)
!1535 = !DILocation(line: 493, column: 8, scope: !1533)
!1536 = !DILocation(line: 493, column: 6, scope: !1533)
!1537 = !DILocation(line: 494, column: 8, scope: !1538)
!1538 = distinct !DILexicalBlock(scope: !1533, file: !1, line: 494, column: 8)
!1539 = !DILocation(line: 494, column: 10, scope: !1538)
!1540 = !DILocation(line: 494, column: 8, scope: !1533)
!1541 = !DILocation(line: 495, column: 5, scope: !1538)
!1542 = !DILocation(line: 496, column: 3, scope: !1533)
!1543 = !DILocation(line: 498, column: 19, scope: !1464)
!1544 = !DILocation(line: 498, column: 22, scope: !1464)
!1545 = !DILocation(line: 498, column: 7, scope: !1464)
!1546 = !DILocation(line: 498, column: 5, scope: !1464)
!1547 = !DILocation(line: 499, column: 7, scope: !1548)
!1548 = distinct !DILexicalBlock(scope: !1464, file: !1, line: 499, column: 7)
!1549 = !DILocation(line: 499, column: 9, scope: !1548)
!1550 = !DILocation(line: 499, column: 7, scope: !1464)
!1551 = !DILocation(line: 500, column: 4, scope: !1548)
!1552 = !DILocation(line: 501, column: 8, scope: !1464)
!1553 = !DILocation(line: 501, column: 5, scope: !1464)
!1554 = !DILocation(line: 502, column: 10, scope: !1464)
!1555 = !DILocation(line: 502, column: 7, scope: !1464)
!1556 = !DILocation(line: 503, column: 9, scope: !1464)
!1557 = !DILocation(line: 506, column: 8, scope: !1558)
!1558 = distinct !DILexicalBlock(scope: !1464, file: !1, line: 506, column: 7)
!1559 = !DILocation(line: 506, column: 7, scope: !1558)
!1560 = !DILocation(line: 506, column: 10, scope: !1558)
!1561 = !DILocation(line: 506, column: 7, scope: !1464)
!1562 = !DILocalVariable(name: "value", scope: !1563, file: !1, line: 507, type: !23)
!1563 = distinct !DILexicalBlock(scope: !1558, file: !1, line: 506, column: 18)
!1564 = !DILocation(line: 507, column: 8, scope: !1563)
!1565 = !DILocation(line: 508, column: 4, scope: !1563)
!1566 = !DILocation(line: 509, column: 4, scope: !1563)
!1567 = !DILocation(line: 510, column: 4, scope: !1563)
!1568 = !DILocation(line: 510, column: 11, scope: !1569)
!1569 = !DILexicalBlockFile(scope: !1563, file: !1, discriminator: 1)
!1570 = !DILocation(line: 510, column: 15, scope: !1569)
!1571 = !DILocation(line: 510, column: 19, scope: !1569)
!1572 = !DILocation(line: 510, column: 23, scope: !1573)
!1573 = !DILexicalBlockFile(scope: !1563, file: !1, discriminator: 2)
!1574 = !DILocation(line: 510, column: 22, scope: !1573)
!1575 = !DILocation(line: 510, column: 25, scope: !1573)
!1576 = !DILocation(line: 510, column: 32, scope: !1573)
!1577 = !DILocation(line: 510, column: 36, scope: !1578)
!1578 = !DILexicalBlockFile(scope: !1563, file: !1, discriminator: 3)
!1579 = !DILocation(line: 510, column: 35, scope: !1578)
!1580 = !DILocation(line: 510, column: 38, scope: !1578)
!1581 = !DILocation(line: 510, column: 4, scope: !1582)
!1582 = !DILexicalBlockFile(scope: !1563, file: !1, discriminator: 4)
!1583 = !DILocation(line: 511, column: 5, scope: !1584)
!1584 = distinct !DILexicalBlock(scope: !1563, file: !1, line: 510, column: 47)
!1585 = !DILocation(line: 512, column: 5, scope: !1584)
!1586 = !DILocation(line: 513, column: 11, scope: !1584)
!1587 = !DILocation(line: 510, column: 4, scope: !1588)
!1588 = !DILexicalBlockFile(scope: !1563, file: !1, discriminator: 5)
!1589 = !DILocation(line: 517, column: 9, scope: !1590)
!1590 = distinct !DILexicalBlock(scope: !1563, file: !1, line: 517, column: 8)
!1591 = !DILocation(line: 517, column: 15, scope: !1590)
!1592 = !DILocation(line: 517, column: 18, scope: !1593)
!1593 = !DILexicalBlockFile(scope: !1590, file: !1, discriminator: 1)
!1594 = !DILocation(line: 517, column: 24, scope: !1593)
!1595 = !DILocation(line: 517, column: 8, scope: !1593)
!1596 = !DILocation(line: 518, column: 5, scope: !1590)
!1597 = !DILocation(line: 519, column: 3, scope: !1563)
!1598 = !DILocation(line: 474, column: 2, scope: !1599)
!1599 = !DILexicalBlockFile(scope: !362, file: !1, discriminator: 4)
!1600 = !DILocation(line: 521, column: 10, scope: !362)
!1601 = !DILocation(line: 521, column: 2, scope: !362)
!1602 = !DILocation(line: 522, column: 1, scope: !362)
!1603 = !DILocalVariable(name: "p", arg: 1, scope: !371, file: !1, line: 525, type: !80)
!1604 = !DILocation(line: 525, column: 23, scope: !371)
!1605 = !DILocalVariable(name: "len", arg: 2, scope: !371, file: !1, line: 525, type: !38)
!1606 = !DILocation(line: 525, column: 34, scope: !371)
!1607 = !DILocalVariable(name: "nl", arg: 3, scope: !371, file: !1, line: 525, type: !38)
!1608 = !DILocation(line: 525, column: 47, scope: !371)
!1609 = !DILocalVariable(name: "last_is_path", arg: 4, scope: !371, file: !1, line: 525, type: !353)
!1610 = !DILocation(line: 525, column: 56, scope: !371)
!1611 = !DILocalVariable(name: "f", scope: !371, file: !1, line: 527, type: !23)
!1612 = !DILocation(line: 527, column: 6, scope: !371)
!1613 = !DILocalVariable(name: "ll", scope: !371, file: !1, line: 552, type: !38)
!1614 = !DILocation(line: 552, column: 10, scope: !371)
!1615 = !DILocalVariable(name: "pp", scope: !371, file: !1, line: 553, type: !80)
!1616 = !DILocation(line: 553, column: 14, scope: !371)
!1617 = !DILocation(line: 553, column: 19, scope: !371)
!1618 = !DILocalVariable(name: "pp_end", scope: !371, file: !1, line: 554, type: !1619)
!1619 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !80)
!1620 = !DILocation(line: 554, column: 21, scope: !371)
!1621 = !DILocation(line: 554, column: 30, scope: !371)
!1622 = !DILocation(line: 554, column: 35, scope: !371)
!1623 = !DILocation(line: 554, column: 33, scope: !371)
!1624 = !DILocation(line: 556, column: 3, scope: !371)
!1625 = !DILocation(line: 556, column: 16, scope: !371)
!1626 = !DILocation(line: 560, column: 2, scope: !371)
!1627 = !DILocation(line: 560, column: 8, scope: !1628)
!1628 = !DILexicalBlockFile(scope: !1629, file: !1, discriminator: 1)
!1629 = distinct !DILexicalBlock(scope: !1630, file: !1, line: 560, column: 2)
!1630 = distinct !DILexicalBlock(scope: !371, file: !1, line: 560, column: 2)
!1631 = !DILocation(line: 560, column: 13, scope: !1628)
!1632 = !DILocation(line: 560, column: 11, scope: !1628)
!1633 = !DILocation(line: 560, column: 2, scope: !1628)
!1634 = !DILocation(line: 561, column: 42, scope: !1635)
!1635 = distinct !DILexicalBlock(scope: !1636, file: !1, line: 561, column: 7)
!1636 = distinct !DILexicalBlock(scope: !1629, file: !1, line: 560, column: 27)
!1637 = !DILocation(line: 561, column: 18, scope: !1635)
!1638 = !DILocation(line: 561, column: 8, scope: !1635)
!1639 = !DILocation(line: 561, column: 7, scope: !1636)
!1640 = !DILocation(line: 562, column: 9, scope: !1641)
!1641 = distinct !DILexicalBlock(scope: !1642, file: !1, line: 562, column: 8)
!1642 = distinct !DILexicalBlock(scope: !1635, file: !1, line: 561, column: 47)
!1643 = !DILocation(line: 562, column: 8, scope: !1641)
!1644 = !DILocation(line: 562, column: 12, scope: !1641)
!1645 = !DILocation(line: 562, column: 19, scope: !1641)
!1646 = !DILocation(line: 562, column: 23, scope: !1647)
!1647 = !DILexicalBlockFile(scope: !1641, file: !1, discriminator: 1)
!1648 = !DILocation(line: 562, column: 22, scope: !1647)
!1649 = !DILocation(line: 562, column: 26, scope: !1647)
!1650 = !DILocation(line: 562, column: 34, scope: !1647)
!1651 = !DILocation(line: 562, column: 38, scope: !1652)
!1652 = !DILexicalBlockFile(scope: !1641, file: !1, discriminator: 2)
!1653 = !DILocation(line: 562, column: 37, scope: !1652)
!1654 = !DILocation(line: 562, column: 41, scope: !1652)
!1655 = !DILocation(line: 563, column: 8, scope: !1641)
!1656 = !DILocation(line: 563, column: 12, scope: !1647)
!1657 = !DILocation(line: 563, column: 11, scope: !1647)
!1658 = !DILocation(line: 563, column: 15, scope: !1647)
!1659 = !DILocation(line: 562, column: 8, scope: !1660)
!1660 = !DILexicalBlockFile(scope: !1642, file: !1, discriminator: 3)
!1661 = !DILocation(line: 564, column: 7, scope: !1641)
!1662 = !DILocation(line: 564, column: 5, scope: !1641)
!1663 = !DILocation(line: 565, column: 4, scope: !1642)
!1664 = !DILocation(line: 567, column: 5, scope: !1636)
!1665 = !DILocation(line: 568, column: 2, scope: !1636)
!1666 = !DILocation(line: 560, column: 21, scope: !1667)
!1667 = !DILexicalBlockFile(scope: !1629, file: !1, discriminator: 2)
!1668 = !DILocation(line: 560, column: 2, scope: !1667)
!1669 = !DILocation(line: 569, column: 7, scope: !371)
!1670 = !DILocation(line: 569, column: 16, scope: !371)
!1671 = !DILocation(line: 569, column: 14, scope: !371)
!1672 = !DILocation(line: 569, column: 5, scope: !371)
!1673 = !DILocation(line: 574, column: 6, scope: !1674)
!1674 = distinct !DILexicalBlock(scope: !371, file: !1, line: 574, column: 6)
!1675 = !DILocation(line: 574, column: 8, scope: !1674)
!1676 = !DILocation(line: 574, column: 6, scope: !371)
!1677 = !DILocalVariable(name: "pb", scope: !1678, file: !1, line: 575, type: !80)
!1678 = distinct !DILexicalBlock(scope: !1674, file: !1, line: 574, column: 14)
!1679 = !DILocation(line: 575, column: 15, scope: !1678)
!1680 = !DILocation(line: 575, column: 20, scope: !1678)
!1681 = !DILocation(line: 575, column: 24, scope: !1678)
!1682 = !DILocation(line: 575, column: 22, scope: !1678)
!1683 = !DILocation(line: 575, column: 30, scope: !1678)
!1684 = !DILocation(line: 575, column: 28, scope: !1678)
!1685 = !DILocalVariable(name: "name_len", scope: !1678, file: !1, line: 576, type: !23)
!1686 = !DILocation(line: 576, column: 7, scope: !1678)
!1687 = !DILocalVariable(name: "slash", scope: !1678, file: !1, line: 577, type: !23)
!1688 = !DILocation(line: 577, column: 7, scope: !1678)
!1689 = !DILocation(line: 580, column: 7, scope: !1690)
!1690 = distinct !DILexicalBlock(scope: !1678, file: !1, line: 580, column: 7)
!1691 = !DILocation(line: 580, column: 9, scope: !1690)
!1692 = !DILocation(line: 580, column: 15, scope: !1690)
!1693 = !DILocation(line: 580, column: 12, scope: !1690)
!1694 = !DILocation(line: 580, column: 17, scope: !1690)
!1695 = !DILocation(line: 581, column: 7, scope: !1690)
!1696 = !DILocation(line: 581, column: 14, scope: !1690)
!1697 = !DILocation(line: 581, column: 22, scope: !1690)
!1698 = !DILocation(line: 581, column: 26, scope: !1699)
!1699 = !DILexicalBlockFile(scope: !1690, file: !1, discriminator: 1)
!1700 = !DILocation(line: 581, column: 33, scope: !1699)
!1701 = !DILocation(line: 581, column: 40, scope: !1699)
!1702 = !DILocation(line: 581, column: 43, scope: !1703)
!1703 = !DILexicalBlockFile(scope: !1690, file: !1, discriminator: 2)
!1704 = !DILocation(line: 581, column: 50, scope: !1703)
!1705 = !DILocation(line: 580, column: 7, scope: !1706)
!1706 = !DILexicalBlockFile(scope: !1678, file: !1, discriminator: 1)
!1707 = !DILocation(line: 582, column: 4, scope: !1690)
!1708 = !DILocation(line: 583, column: 7, scope: !1709)
!1709 = distinct !DILexicalBlock(scope: !1678, file: !1, line: 583, column: 7)
!1710 = !DILocation(line: 583, column: 9, scope: !1709)
!1711 = !DILocation(line: 583, column: 15, scope: !1709)
!1712 = !DILocation(line: 583, column: 12, scope: !1709)
!1713 = !DILocation(line: 583, column: 17, scope: !1709)
!1714 = !DILocation(line: 583, column: 20, scope: !1715)
!1715 = !DILexicalBlockFile(scope: !1709, file: !1, discriminator: 1)
!1716 = !DILocation(line: 583, column: 27, scope: !1715)
!1717 = !DILocation(line: 583, column: 7, scope: !1715)
!1718 = !DILocation(line: 584, column: 4, scope: !1709)
!1719 = !DILocation(line: 586, column: 9, scope: !1678)
!1720 = !DILocation(line: 587, column: 3, scope: !1678)
!1721 = !DILocation(line: 587, column: 10, scope: !1706)
!1722 = !DILocation(line: 587, column: 15, scope: !1706)
!1723 = !DILocation(line: 587, column: 12, scope: !1706)
!1724 = !DILocation(line: 587, column: 20, scope: !1706)
!1725 = !DILocation(line: 587, column: 24, scope: !1726)
!1726 = !DILexicalBlockFile(scope: !1678, file: !1, discriminator: 2)
!1727 = !DILocation(line: 587, column: 23, scope: !1726)
!1728 = !DILocation(line: 587, column: 27, scope: !1726)
!1729 = !DILocation(line: 587, column: 34, scope: !1726)
!1730 = !DILocation(line: 587, column: 38, scope: !1731)
!1731 = !DILexicalBlockFile(scope: !1678, file: !1, discriminator: 3)
!1732 = !DILocation(line: 587, column: 37, scope: !1731)
!1733 = !DILocation(line: 587, column: 41, scope: !1731)
!1734 = !DILocation(line: 587, column: 3, scope: !1735)
!1735 = !DILexicalBlockFile(scope: !1678, file: !1, discriminator: 4)
!1736 = !DILocation(line: 588, column: 43, scope: !1737)
!1737 = distinct !DILexicalBlock(scope: !1738, file: !1, line: 588, column: 8)
!1738 = distinct !DILexicalBlock(scope: !1678, file: !1, line: 587, column: 50)
!1739 = !DILocation(line: 588, column: 19, scope: !1737)
!1740 = !DILocation(line: 588, column: 9, scope: !1737)
!1741 = !DILocation(line: 588, column: 8, scope: !1738)
!1742 = !DILocation(line: 589, column: 5, scope: !1737)
!1743 = !DILocation(line: 590, column: 12, scope: !1738)
!1744 = !DILocation(line: 593, column: 9, scope: !1745)
!1745 = distinct !DILexicalBlock(scope: !1738, file: !1, line: 593, column: 8)
!1746 = !DILocation(line: 593, column: 8, scope: !1745)
!1747 = !DILocation(line: 593, column: 12, scope: !1745)
!1748 = !DILocation(line: 593, column: 8, scope: !1738)
!1749 = !DILocation(line: 594, column: 11, scope: !1745)
!1750 = !DILocation(line: 594, column: 5, scope: !1745)
!1751 = !DILocation(line: 587, column: 3, scope: !1752)
!1752 = !DILexicalBlockFile(scope: !1678, file: !1, discriminator: 5)
!1753 = !DILocation(line: 596, column: 7, scope: !1754)
!1754 = distinct !DILexicalBlock(scope: !1678, file: !1, line: 596, column: 7)
!1755 = !DILocation(line: 596, column: 16, scope: !1754)
!1756 = !DILocation(line: 596, column: 21, scope: !1754)
!1757 = !DILocation(line: 596, column: 24, scope: !1758)
!1758 = !DILexicalBlockFile(scope: !1754, file: !1, discriminator: 1)
!1759 = !DILocation(line: 596, column: 30, scope: !1758)
!1760 = !DILocation(line: 596, column: 7, scope: !1758)
!1761 = !DILocation(line: 597, column: 4, scope: !1754)
!1762 = !DILocation(line: 600, column: 7, scope: !1763)
!1763 = distinct !DILexicalBlock(scope: !1678, file: !1, line: 600, column: 7)
!1764 = !DILocation(line: 600, column: 13, scope: !1763)
!1765 = !DILocation(line: 600, column: 7, scope: !1678)
!1766 = !DILocation(line: 601, column: 4, scope: !1763)
!1767 = !DILocation(line: 602, column: 8, scope: !1678)
!1768 = !DILocation(line: 602, column: 14, scope: !1678)
!1769 = !DILocation(line: 602, column: 12, scope: !1678)
!1770 = !DILocation(line: 602, column: 19, scope: !1678)
!1771 = !DILocation(line: 602, column: 17, scope: !1678)
!1772 = !DILocation(line: 602, column: 6, scope: !1678)
!1773 = !DILocation(line: 603, column: 8, scope: !1678)
!1774 = !DILocation(line: 603, column: 6, scope: !1678)
!1775 = !DILocation(line: 604, column: 4, scope: !1678)
!1776 = !DILocation(line: 604, column: 17, scope: !1678)
!1777 = !DILocation(line: 605, column: 2, scope: !1678)
!1778 = !DILocation(line: 607, column: 27, scope: !371)
!1779 = !DILocation(line: 607, column: 31, scope: !371)
!1780 = !DILocation(line: 607, column: 39, scope: !371)
!1781 = !DILocation(line: 607, column: 38, scope: !371)
!1782 = !DILocation(line: 607, column: 10, scope: !371)
!1783 = !DILocation(line: 607, column: 2, scope: !371)
!1784 = !DILocation(line: 608, column: 1, scope: !371)
!1785 = !DILocalVariable(name: "b", arg: 1, scope: !359, file: !1, line: 276, type: !80)
!1786 = !DILocation(line: 276, column: 27, scope: !359)
!1787 = !DILocalVariable(name: "avail", arg: 2, scope: !359, file: !1, line: 276, type: !38)
!1788 = !DILocation(line: 276, column: 38, scope: !359)
!1789 = !DILocalVariable(name: "nlsize", arg: 3, scope: !359, file: !1, line: 276, type: !358)
!1790 = !DILocation(line: 276, column: 54, scope: !359)
!1791 = !DILocalVariable(name: "len", scope: !359, file: !1, line: 278, type: !38)
!1792 = !DILocation(line: 278, column: 10, scope: !359)
!1793 = !DILocation(line: 280, column: 6, scope: !359)
!1794 = !DILocation(line: 281, column: 2, scope: !359)
!1795 = !DILocation(line: 281, column: 9, scope: !1796)
!1796 = !DILexicalBlockFile(scope: !359, file: !1, discriminator: 1)
!1797 = !DILocation(line: 281, column: 15, scope: !1796)
!1798 = !DILocation(line: 281, column: 13, scope: !1796)
!1799 = !DILocation(line: 281, column: 2, scope: !1796)
!1800 = !DILocation(line: 282, column: 12, scope: !1801)
!1801 = distinct !DILexicalBlock(scope: !359, file: !1, line: 281, column: 22)
!1802 = !DILocation(line: 282, column: 11, scope: !1801)
!1803 = !DILocation(line: 282, column: 3, scope: !1801)
!1804 = !DILocation(line: 284, column: 8, scope: !1805)
!1805 = distinct !DILexicalBlock(scope: !1806, file: !1, line: 284, column: 8)
!1806 = distinct !DILexicalBlock(scope: !1801, file: !1, line: 282, column: 15)
!1807 = !DILocation(line: 284, column: 15, scope: !1805)
!1808 = !DILocation(line: 284, column: 8, scope: !1806)
!1809 = !DILocation(line: 285, column: 6, scope: !1805)
!1810 = !DILocation(line: 285, column: 13, scope: !1805)
!1811 = !DILocation(line: 285, column: 5, scope: !1805)
!1812 = !DILocation(line: 286, column: 4, scope: !1806)
!1813 = !DILocation(line: 288, column: 8, scope: !1814)
!1814 = distinct !DILexicalBlock(scope: !1806, file: !1, line: 288, column: 8)
!1815 = !DILocation(line: 288, column: 14, scope: !1814)
!1816 = !DILocation(line: 288, column: 13, scope: !1814)
!1817 = !DILocation(line: 288, column: 18, scope: !1814)
!1818 = !DILocation(line: 288, column: 22, scope: !1814)
!1819 = !DILocation(line: 288, column: 25, scope: !1820)
!1820 = !DILexicalBlockFile(scope: !1814, file: !1, discriminator: 1)
!1821 = !DILocation(line: 288, column: 30, scope: !1820)
!1822 = !DILocation(line: 288, column: 8, scope: !1820)
!1823 = !DILocation(line: 289, column: 9, scope: !1824)
!1824 = distinct !DILexicalBlock(scope: !1825, file: !1, line: 289, column: 9)
!1825 = distinct !DILexicalBlock(scope: !1814, file: !1, line: 288, column: 39)
!1826 = !DILocation(line: 289, column: 16, scope: !1824)
!1827 = !DILocation(line: 289, column: 9, scope: !1825)
!1828 = !DILocation(line: 290, column: 7, scope: !1824)
!1829 = !DILocation(line: 290, column: 14, scope: !1824)
!1830 = !DILocation(line: 290, column: 6, scope: !1824)
!1831 = !DILocation(line: 291, column: 13, scope: !1825)
!1832 = !DILocation(line: 291, column: 16, scope: !1825)
!1833 = !DILocation(line: 291, column: 5, scope: !1825)
!1834 = !DILocation(line: 288, column: 33, scope: !1835)
!1835 = !DILexicalBlockFile(scope: !1814, file: !1, discriminator: 2)
!1836 = !DILocation(line: 295, column: 8, scope: !1837)
!1837 = distinct !DILexicalBlock(scope: !1806, file: !1, line: 295, column: 8)
!1838 = !DILocation(line: 295, column: 15, scope: !1837)
!1839 = !DILocation(line: 295, column: 8, scope: !1806)
!1840 = !DILocation(line: 296, column: 6, scope: !1837)
!1841 = !DILocation(line: 296, column: 13, scope: !1837)
!1842 = !DILocation(line: 296, column: 5, scope: !1837)
!1843 = !DILocation(line: 297, column: 12, scope: !1806)
!1844 = !DILocation(line: 297, column: 15, scope: !1806)
!1845 = !DILocation(line: 297, column: 4, scope: !1806)
!1846 = !DILocation(line: 299, column: 5, scope: !1806)
!1847 = !DILocation(line: 300, column: 7, scope: !1806)
!1848 = !DILocation(line: 301, column: 4, scope: !1806)
!1849 = !DILocation(line: 281, column: 2, scope: !1850)
!1850 = !DILexicalBlockFile(scope: !359, file: !1, discriminator: 2)
!1851 = !DILocation(line: 304, column: 6, scope: !1852)
!1852 = distinct !DILexicalBlock(scope: !359, file: !1, line: 304, column: 6)
!1853 = !DILocation(line: 304, column: 13, scope: !1852)
!1854 = !DILocation(line: 304, column: 6, scope: !359)
!1855 = !DILocation(line: 305, column: 4, scope: !1852)
!1856 = !DILocation(line: 305, column: 11, scope: !1852)
!1857 = !DILocation(line: 305, column: 3, scope: !1852)
!1858 = !DILocation(line: 306, column: 10, scope: !359)
!1859 = !DILocation(line: 306, column: 2, scope: !359)
!1860 = !DILocation(line: 307, column: 1, scope: !359)
!1861 = !DILocalVariable(name: "p", arg: 1, scope: !365, file: !1, line: 369, type: !80)
!1862 = !DILocation(line: 369, column: 24, scope: !365)
!1863 = !DILocalVariable(name: "key", arg: 2, scope: !365, file: !1, line: 369, type: !80)
!1864 = !DILocation(line: 369, column: 39, scope: !365)
!1865 = !DILocalVariable(name: "len", arg: 3, scope: !365, file: !1, line: 369, type: !38)
!1866 = !DILocation(line: 369, column: 52, scope: !365)
!1867 = !DILocalVariable(name: "match_len", scope: !365, file: !1, line: 371, type: !23)
!1868 = !DILocation(line: 371, column: 6, scope: !365)
!1869 = !DILocation(line: 373, column: 2, scope: !365)
!1870 = !DILocation(line: 373, column: 9, scope: !1871)
!1871 = !DILexicalBlockFile(scope: !365, file: !1, discriminator: 1)
!1872 = !DILocation(line: 373, column: 13, scope: !1871)
!1873 = !DILocation(line: 373, column: 17, scope: !1871)
!1874 = !DILocation(line: 373, column: 21, scope: !1875)
!1875 = !DILexicalBlockFile(scope: !365, file: !1, discriminator: 2)
!1876 = !DILocation(line: 373, column: 20, scope: !1875)
!1877 = !DILocation(line: 373, column: 23, scope: !1875)
!1878 = !DILocation(line: 373, column: 27, scope: !1879)
!1879 = !DILexicalBlockFile(scope: !365, file: !1, discriminator: 3)
!1880 = !DILocation(line: 373, column: 26, scope: !1879)
!1881 = !DILocation(line: 373, column: 23, scope: !1879)
!1882 = !DILocation(line: 373, column: 2, scope: !1883)
!1883 = !DILexicalBlockFile(scope: !365, file: !1, discriminator: 4)
!1884 = !DILocation(line: 374, column: 8, scope: !1885)
!1885 = distinct !DILexicalBlock(scope: !1886, file: !1, line: 374, column: 7)
!1886 = distinct !DILexicalBlock(scope: !365, file: !1, line: 373, column: 32)
!1887 = !DILocation(line: 374, column: 7, scope: !1885)
!1888 = !DILocation(line: 374, column: 14, scope: !1885)
!1889 = !DILocation(line: 374, column: 13, scope: !1885)
!1890 = !DILocation(line: 374, column: 10, scope: !1885)
!1891 = !DILocation(line: 374, column: 7, scope: !1886)
!1892 = !DILocation(line: 375, column: 4, scope: !1893)
!1893 = distinct !DILexicalBlock(scope: !1885, file: !1, line: 374, column: 19)
!1894 = !DILocation(line: 376, column: 4, scope: !1893)
!1895 = !DILocation(line: 377, column: 4, scope: !1893)
!1896 = !DILocation(line: 378, column: 4, scope: !1893)
!1897 = !DILocation(line: 379, column: 4, scope: !1893)
!1898 = !DILocation(line: 381, column: 3, scope: !1886)
!1899 = !DILocation(line: 383, column: 7, scope: !1900)
!1900 = distinct !DILexicalBlock(scope: !365, file: !1, line: 383, column: 6)
!1901 = !DILocation(line: 383, column: 6, scope: !1900)
!1902 = !DILocation(line: 383, column: 11, scope: !1900)
!1903 = !DILocation(line: 383, column: 6, scope: !365)
!1904 = !DILocation(line: 384, column: 3, scope: !1900)
!1905 = !DILocation(line: 387, column: 6, scope: !1906)
!1906 = distinct !DILexicalBlock(scope: !365, file: !1, line: 387, column: 6)
!1907 = !DILocation(line: 387, column: 11, scope: !1906)
!1908 = !DILocation(line: 387, column: 18, scope: !1906)
!1909 = !DILocation(line: 387, column: 21, scope: !1910)
!1910 = !DILexicalBlockFile(scope: !1906, file: !1, discriminator: 1)
!1911 = !DILocation(line: 387, column: 26, scope: !1910)
!1912 = !DILocation(line: 387, column: 33, scope: !1910)
!1913 = !DILocation(line: 387, column: 36, scope: !1914)
!1914 = !DILexicalBlockFile(scope: !1906, file: !1, discriminator: 2)
!1915 = !DILocation(line: 387, column: 41, scope: !1914)
!1916 = !DILocation(line: 387, column: 49, scope: !1914)
!1917 = !DILocation(line: 388, column: 6, scope: !1906)
!1918 = !DILocation(line: 388, column: 11, scope: !1906)
!1919 = !DILocation(line: 388, column: 19, scope: !1906)
!1920 = !DILocation(line: 388, column: 22, scope: !1910)
!1921 = !DILocation(line: 388, column: 27, scope: !1910)
!1922 = !DILocation(line: 388, column: 35, scope: !1910)
!1923 = !DILocation(line: 389, column: 6, scope: !1906)
!1924 = !DILocation(line: 389, column: 11, scope: !1906)
!1925 = !DILocation(line: 389, column: 19, scope: !1906)
!1926 = !DILocation(line: 389, column: 23, scope: !1910)
!1927 = !DILocation(line: 389, column: 28, scope: !1910)
!1928 = !DILocation(line: 389, column: 36, scope: !1910)
!1929 = !DILocation(line: 389, column: 39, scope: !1914)
!1930 = !DILocation(line: 389, column: 44, scope: !1914)
!1931 = !DILocation(line: 387, column: 6, scope: !1879)
!1932 = !DILocation(line: 390, column: 11, scope: !1906)
!1933 = !DILocation(line: 390, column: 3, scope: !1906)
!1934 = !DILocation(line: 391, column: 2, scope: !365)
!1935 = !DILocation(line: 392, column: 1, scope: !365)
!1936 = !DILocalVariable(name: "p", arg: 1, scope: !368, file: !1, line: 400, type: !80)
!1937 = !DILocation(line: 400, column: 25, scope: !368)
!1938 = !DILocalVariable(name: "len", arg: 2, scope: !368, file: !1, line: 400, type: !38)
!1939 = !DILocation(line: 400, column: 37, scope: !368)
!1940 = !DILocalVariable(name: "keys", scope: !368, file: !1, line: 436, type: !357)
!1941 = !DILocation(line: 436, column: 15, scope: !368)
!1942 = !DILocalVariable(name: "i", scope: !368, file: !1, line: 437, type: !23)
!1943 = !DILocation(line: 437, column: 6, scope: !368)
!1944 = !DILocation(line: 439, column: 11, scope: !368)
!1945 = !DILocation(line: 439, column: 10, scope: !368)
!1946 = !DILocation(line: 439, column: 2, scope: !368)
!1947 = !DILocation(line: 440, column: 17, scope: !1948)
!1948 = distinct !DILexicalBlock(scope: !368, file: !1, line: 439, column: 14)
!1949 = !DILocation(line: 440, column: 27, scope: !1948)
!1950 = !DILocation(line: 441, column: 27, scope: !1948)
!1951 = !DILocation(line: 441, column: 38, scope: !1948)
!1952 = !DILocation(line: 442, column: 17, scope: !1948)
!1953 = !DILocation(line: 442, column: 27, scope: !1948)
!1954 = !DILocation(line: 443, column: 27, scope: !1948)
!1955 = !DILocation(line: 443, column: 38, scope: !1948)
!1956 = !DILocation(line: 444, column: 17, scope: !1948)
!1957 = !DILocation(line: 444, column: 27, scope: !1948)
!1958 = !DILocation(line: 445, column: 27, scope: !1948)
!1959 = !DILocation(line: 445, column: 38, scope: !1948)
!1960 = !DILocation(line: 446, column: 17, scope: !1948)
!1961 = !DILocation(line: 446, column: 27, scope: !1948)
!1962 = !DILocation(line: 447, column: 17, scope: !1948)
!1963 = !DILocation(line: 447, column: 27, scope: !1948)
!1964 = !DILocation(line: 448, column: 17, scope: !1948)
!1965 = !DILocation(line: 448, column: 27, scope: !1948)
!1966 = !DILocation(line: 449, column: 17, scope: !1948)
!1967 = !DILocation(line: 449, column: 27, scope: !1948)
!1968 = !DILocation(line: 450, column: 11, scope: !1948)
!1969 = !DILocation(line: 453, column: 9, scope: !1970)
!1970 = distinct !DILexicalBlock(scope: !368, file: !1, line: 453, column: 2)
!1971 = !DILocation(line: 453, column: 7, scope: !1970)
!1972 = !DILocation(line: 453, column: 19, scope: !1973)
!1973 = !DILexicalBlockFile(scope: !1974, file: !1, discriminator: 1)
!1974 = distinct !DILexicalBlock(scope: !1970, file: !1, line: 453, column: 2)
!1975 = !DILocation(line: 453, column: 14, scope: !1973)
!1976 = !DILocation(line: 453, column: 22, scope: !1973)
!1977 = !DILocation(line: 453, column: 2, scope: !1973)
!1978 = !DILocalVariable(name: "l", scope: !1979, file: !1, line: 454, type: !23)
!1979 = distinct !DILexicalBlock(scope: !1974, file: !1, line: 453, column: 36)
!1980 = !DILocation(line: 454, column: 7, scope: !1979)
!1981 = !DILocation(line: 454, column: 22, scope: !1979)
!1982 = !DILocation(line: 454, column: 30, scope: !1979)
!1983 = !DILocation(line: 454, column: 25, scope: !1979)
!1984 = !DILocation(line: 454, column: 34, scope: !1979)
!1985 = !DILocation(line: 454, column: 11, scope: !1979)
!1986 = !DILocation(line: 455, column: 7, scope: !1987)
!1987 = distinct !DILexicalBlock(scope: !1979, file: !1, line: 455, column: 7)
!1988 = !DILocation(line: 455, column: 9, scope: !1987)
!1989 = !DILocation(line: 455, column: 7, scope: !1979)
!1990 = !DILocation(line: 456, column: 12, scope: !1987)
!1991 = !DILocation(line: 456, column: 4, scope: !1987)
!1992 = !DILocation(line: 457, column: 2, scope: !1979)
!1993 = !DILocation(line: 453, column: 32, scope: !1994)
!1994 = !DILexicalBlockFile(scope: !1974, file: !1, discriminator: 2)
!1995 = !DILocation(line: 453, column: 2, scope: !1994)
!1996 = !DILocation(line: 458, column: 2, scope: !368)
!1997 = !DILocation(line: 459, column: 1, scope: !368)
!1998 = !DILocalVariable(name: "a", arg: 1, scope: !375, file: !1, line: 981, type: !4)
!1999 = !DILocation(line: 981, column: 33, scope: !375)
!2000 = !DILocalVariable(name: "mtree", arg: 2, scope: !375, file: !1, line: 981, type: !291)
!2001 = !DILocation(line: 981, column: 50, scope: !375)
!2002 = !DILocalVariable(name: "len", scope: !375, file: !1, line: 983, type: !38)
!2003 = !DILocation(line: 983, column: 10, scope: !375)
!2004 = !DILocalVariable(name: "counter", scope: !375, file: !1, line: 984, type: !2005)
!2005 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintmax_t", file: !53, line: 135, baseType: !47)
!2006 = !DILocation(line: 984, column: 12, scope: !375)
!2007 = !DILocalVariable(name: "p", scope: !375, file: !1, line: 985, type: !95)
!2008 = !DILocation(line: 985, column: 8, scope: !375)
!2009 = !DILocalVariable(name: "global", scope: !375, file: !1, line: 986, type: !307)
!2010 = !DILocation(line: 986, column: 23, scope: !375)
!2011 = !DILocalVariable(name: "last_entry", scope: !375, file: !1, line: 987, type: !302)
!2012 = !DILocation(line: 987, column: 22, scope: !375)
!2013 = !DILocalVariable(name: "r", scope: !375, file: !1, line: 988, type: !23)
!2014 = !DILocation(line: 988, column: 6, scope: !375)
!2015 = !DILocalVariable(name: "is_form_d", scope: !375, file: !1, line: 988, type: !23)
!2016 = !DILocation(line: 988, column: 9, scope: !375)
!2017 = !DILocation(line: 990, column: 2, scope: !375)
!2018 = !DILocation(line: 990, column: 9, scope: !375)
!2019 = !DILocation(line: 990, column: 24, scope: !375)
!2020 = !DILocation(line: 991, column: 2, scope: !375)
!2021 = !DILocation(line: 991, column: 9, scope: !375)
!2022 = !DILocation(line: 991, column: 29, scope: !375)
!2023 = !DILocation(line: 993, column: 9, scope: !375)
!2024 = !DILocation(line: 994, column: 13, scope: !375)
!2025 = !DILocation(line: 996, column: 20, scope: !375)
!2026 = !DILocation(line: 996, column: 8, scope: !375)
!2027 = !DILocation(line: 998, column: 15, scope: !2028)
!2028 = distinct !DILexicalBlock(scope: !375, file: !1, line: 998, column: 2)
!2029 = !DILocation(line: 998, column: 7, scope: !2028)
!2030 = !DILocation(line: 999, column: 18, scope: !2031)
!2031 = distinct !DILexicalBlock(scope: !2032, file: !1, line: 998, column: 33)
!2032 = distinct !DILexicalBlock(scope: !2028, file: !1, line: 998, column: 2)
!2033 = !DILocation(line: 999, column: 21, scope: !2031)
!2034 = !DILocation(line: 999, column: 9, scope: !2031)
!2035 = !DILocation(line: 999, column: 7, scope: !2031)
!2036 = !DILocation(line: 1000, column: 7, scope: !2037)
!2037 = distinct !DILexicalBlock(scope: !2031, file: !1, line: 1000, column: 7)
!2038 = !DILocation(line: 1000, column: 11, scope: !2037)
!2039 = !DILocation(line: 1000, column: 7, scope: !2031)
!2040 = !DILocation(line: 1001, column: 24, scope: !2041)
!2041 = distinct !DILexicalBlock(scope: !2037, file: !1, line: 1000, column: 17)
!2042 = !DILocation(line: 1001, column: 31, scope: !2041)
!2043 = !DILocation(line: 1001, column: 4, scope: !2041)
!2044 = !DILocation(line: 1001, column: 11, scope: !2041)
!2045 = !DILocation(line: 1001, column: 22, scope: !2041)
!2046 = !DILocation(line: 1002, column: 17, scope: !2041)
!2047 = !DILocation(line: 1002, column: 4, scope: !2041)
!2048 = !DILocation(line: 1003, column: 4, scope: !2041)
!2049 = !DILocation(line: 1005, column: 7, scope: !2050)
!2050 = distinct !DILexicalBlock(scope: !2031, file: !1, line: 1005, column: 7)
!2051 = !DILocation(line: 1005, column: 11, scope: !2050)
!2052 = !DILocation(line: 1005, column: 7, scope: !2031)
!2053 = !DILocation(line: 1006, column: 17, scope: !2054)
!2054 = distinct !DILexicalBlock(scope: !2050, file: !1, line: 1005, column: 16)
!2055 = !DILocation(line: 1006, column: 4, scope: !2054)
!2056 = !DILocation(line: 1007, column: 17, scope: !2054)
!2057 = !DILocation(line: 1007, column: 12, scope: !2054)
!2058 = !DILocation(line: 1007, column: 4, scope: !2054)
!2059 = !DILocation(line: 1010, column: 3, scope: !2031)
!2060 = !DILocation(line: 1010, column: 11, scope: !2061)
!2061 = !DILexicalBlockFile(scope: !2031, file: !1, discriminator: 1)
!2062 = !DILocation(line: 1010, column: 10, scope: !2061)
!2063 = !DILocation(line: 1010, column: 13, scope: !2061)
!2064 = !DILocation(line: 1010, column: 20, scope: !2061)
!2065 = !DILocation(line: 1010, column: 24, scope: !2066)
!2066 = !DILexicalBlockFile(scope: !2031, file: !1, discriminator: 2)
!2067 = !DILocation(line: 1010, column: 23, scope: !2066)
!2068 = !DILocation(line: 1010, column: 26, scope: !2066)
!2069 = !DILocation(line: 1010, column: 20, scope: !2066)
!2070 = !DILocation(line: 1010, column: 3, scope: !2071)
!2071 = !DILexicalBlockFile(scope: !2031, file: !1, discriminator: 3)
!2072 = !DILocation(line: 1011, column: 4, scope: !2073)
!2073 = distinct !DILexicalBlock(scope: !2031, file: !1, line: 1010, column: 35)
!2074 = !DILocation(line: 1012, column: 4, scope: !2073)
!2075 = !DILocation(line: 1010, column: 3, scope: !2076)
!2076 = !DILexicalBlockFile(scope: !2031, file: !1, discriminator: 4)
!2077 = !DILocation(line: 1015, column: 8, scope: !2078)
!2078 = distinct !DILexicalBlock(scope: !2031, file: !1, line: 1015, column: 7)
!2079 = !DILocation(line: 1015, column: 7, scope: !2078)
!2080 = !DILocation(line: 1015, column: 10, scope: !2078)
!2081 = !DILocation(line: 1015, column: 7, scope: !2031)
!2082 = !DILocation(line: 1016, column: 4, scope: !2078)
!2083 = !DILocation(line: 1017, column: 8, scope: !2084)
!2084 = distinct !DILexicalBlock(scope: !2031, file: !1, line: 1017, column: 7)
!2085 = !DILocation(line: 1017, column: 7, scope: !2084)
!2086 = !DILocation(line: 1017, column: 10, scope: !2084)
!2087 = !DILocation(line: 1017, column: 18, scope: !2084)
!2088 = !DILocation(line: 1017, column: 22, scope: !2089)
!2089 = !DILexicalBlockFile(scope: !2084, file: !1, discriminator: 1)
!2090 = !DILocation(line: 1017, column: 21, scope: !2089)
!2091 = !DILocation(line: 1017, column: 24, scope: !2089)
!2092 = !DILocation(line: 1017, column: 32, scope: !2089)
!2093 = !DILocation(line: 1017, column: 36, scope: !2094)
!2094 = !DILexicalBlockFile(scope: !2084, file: !1, discriminator: 2)
!2095 = !DILocation(line: 1017, column: 35, scope: !2094)
!2096 = !DILocation(line: 1017, column: 38, scope: !2094)
!2097 = !DILocation(line: 1017, column: 7, scope: !2094)
!2098 = !DILocation(line: 1018, column: 4, scope: !2084)
!2099 = !DILocation(line: 1019, column: 8, scope: !2100)
!2100 = distinct !DILexicalBlock(scope: !2031, file: !1, line: 1019, column: 7)
!2101 = !DILocation(line: 1019, column: 7, scope: !2100)
!2102 = !DILocation(line: 1019, column: 10, scope: !2100)
!2103 = !DILocation(line: 1019, column: 7, scope: !2031)
!2104 = !DILocation(line: 1020, column: 26, scope: !2105)
!2105 = distinct !DILexicalBlock(scope: !2100, file: !1, line: 1019, column: 18)
!2106 = !DILocation(line: 1020, column: 29, scope: !2105)
!2107 = !DILocation(line: 1020, column: 45, scope: !2105)
!2108 = !DILocation(line: 1020, column: 48, scope: !2105)
!2109 = !DILocation(line: 1021, column: 21, scope: !2105)
!2110 = !DILocation(line: 1020, column: 8, scope: !2105)
!2111 = !DILocation(line: 1020, column: 6, scope: !2105)
!2112 = !DILocation(line: 1022, column: 3, scope: !2105)
!2113 = !DILocation(line: 1022, column: 14, scope: !2114)
!2114 = !DILexicalBlockFile(scope: !2115, file: !1, discriminator: 1)
!2115 = distinct !DILexicalBlock(scope: !2100, file: !1, line: 1022, column: 14)
!2116 = !DILocation(line: 1022, column: 18, scope: !2114)
!2117 = !DILocation(line: 1022, column: 22, scope: !2114)
!2118 = !DILocation(line: 1022, column: 33, scope: !2119)
!2119 = !DILexicalBlockFile(scope: !2115, file: !1, discriminator: 2)
!2120 = !DILocation(line: 1022, column: 25, scope: !2119)
!2121 = !DILocation(line: 1022, column: 47, scope: !2119)
!2122 = !DILocation(line: 1022, column: 14, scope: !2119)
!2123 = !DILocation(line: 1023, column: 8, scope: !2124)
!2124 = distinct !DILexicalBlock(scope: !2125, file: !1, line: 1023, column: 8)
!2125 = distinct !DILexicalBlock(scope: !2115, file: !1, line: 1022, column: 53)
!2126 = !DILocation(line: 1023, column: 13, scope: !2124)
!2127 = !DILocation(line: 1023, column: 20, scope: !2124)
!2128 = !DILocation(line: 1023, column: 23, scope: !2129)
!2129 = !DILexicalBlockFile(scope: !2124, file: !1, discriminator: 1)
!2130 = !DILocation(line: 1023, column: 28, scope: !2129)
!2131 = !DILocation(line: 1023, column: 8, scope: !2129)
!2132 = !DILocation(line: 1024, column: 5, scope: !2124)
!2133 = !DILocation(line: 1025, column: 27, scope: !2125)
!2134 = !DILocation(line: 1025, column: 39, scope: !2125)
!2135 = !DILocation(line: 1025, column: 8, scope: !2125)
!2136 = !DILocation(line: 1025, column: 6, scope: !2125)
!2137 = !DILocation(line: 1026, column: 3, scope: !2125)
!2138 = !DILocation(line: 1026, column: 14, scope: !2139)
!2139 = !DILexicalBlockFile(scope: !2140, file: !1, discriminator: 1)
!2140 = distinct !DILexicalBlock(scope: !2115, file: !1, line: 1026, column: 14)
!2141 = !DILocation(line: 1026, column: 18, scope: !2139)
!2142 = !DILocation(line: 1026, column: 22, scope: !2139)
!2143 = !DILocation(line: 1026, column: 33, scope: !2144)
!2144 = !DILexicalBlockFile(scope: !2140, file: !1, discriminator: 2)
!2145 = !DILocation(line: 1026, column: 25, scope: !2144)
!2146 = !DILocation(line: 1026, column: 49, scope: !2144)
!2147 = !DILocation(line: 1026, column: 14, scope: !2144)
!2148 = !DILocation(line: 1027, column: 8, scope: !2149)
!2149 = distinct !DILexicalBlock(scope: !2150, file: !1, line: 1027, column: 8)
!2150 = distinct !DILexicalBlock(scope: !2140, file: !1, line: 1026, column: 55)
!2151 = !DILocation(line: 1027, column: 13, scope: !2149)
!2152 = !DILocation(line: 1027, column: 20, scope: !2149)
!2153 = !DILocation(line: 1027, column: 23, scope: !2154)
!2154 = !DILexicalBlockFile(scope: !2149, file: !1, discriminator: 1)
!2155 = !DILocation(line: 1027, column: 28, scope: !2154)
!2156 = !DILocation(line: 1027, column: 8, scope: !2154)
!2157 = !DILocation(line: 1028, column: 5, scope: !2149)
!2158 = !DILocation(line: 1029, column: 29, scope: !2150)
!2159 = !DILocation(line: 1029, column: 41, scope: !2150)
!2160 = !DILocation(line: 1029, column: 8, scope: !2150)
!2161 = !DILocation(line: 1029, column: 6, scope: !2150)
!2162 = !DILocation(line: 1030, column: 3, scope: !2150)
!2163 = !DILocation(line: 1031, column: 4, scope: !2140)
!2164 = !DILocation(line: 1033, column: 7, scope: !2165)
!2165 = distinct !DILexicalBlock(scope: !2031, file: !1, line: 1033, column: 7)
!2166 = !DILocation(line: 1033, column: 9, scope: !2165)
!2167 = !DILocation(line: 1033, column: 7, scope: !2031)
!2168 = !DILocation(line: 1034, column: 17, scope: !2169)
!2169 = distinct !DILexicalBlock(scope: !2165, file: !1, line: 1033, column: 24)
!2170 = !DILocation(line: 1034, column: 4, scope: !2169)
!2171 = !DILocation(line: 1035, column: 11, scope: !2169)
!2172 = !DILocation(line: 1035, column: 4, scope: !2169)
!2173 = !DILocation(line: 1037, column: 2, scope: !2031)
!2174 = !DILocation(line: 998, column: 22, scope: !2175)
!2175 = !DILexicalBlockFile(scope: !2032, file: !1, discriminator: 1)
!2176 = !DILocation(line: 998, column: 2, scope: !2175)
!2177 = !DILocation(line: 1039, column: 21, scope: !375)
!2178 = !DILocation(line: 1039, column: 24, scope: !375)
!2179 = !DILocation(line: 1040, column: 30, scope: !375)
!2180 = !DILocation(line: 1039, column: 2, scope: !375)
!2181 = !DILocation(line: 1041, column: 15, scope: !375)
!2182 = !DILocation(line: 1041, column: 2, scope: !375)
!2183 = !DILocation(line: 1042, column: 2, scope: !375)
!2184 = !DILocation(line: 1043, column: 1, scope: !375)
!2185 = !DILocalVariable(name: "a", arg: 1, scope: !403, file: !1, line: 1111, type: !4)
!2186 = !DILocation(line: 1111, column: 33, scope: !403)
!2187 = !DILocalVariable(name: "entry", arg: 2, scope: !403, file: !1, line: 1111, type: !30)
!2188 = !DILocation(line: 1111, column: 58, scope: !403)
!2189 = !DILocalVariable(name: "mtree", arg: 3, scope: !403, file: !1, line: 1112, type: !291)
!2190 = !DILocation(line: 1112, column: 19, scope: !403)
!2191 = !DILocalVariable(name: "mentry", arg: 4, scope: !403, file: !1, line: 1112, type: !302)
!2192 = !DILocation(line: 1112, column: 46, scope: !403)
!2193 = !DILocalVariable(name: "use_next", arg: 5, scope: !403, file: !1, line: 1112, type: !353)
!2194 = !DILocation(line: 1112, column: 59, scope: !403)
!2195 = !DILocalVariable(name: "path", scope: !403, file: !1, line: 1114, type: !80)
!2196 = !DILocation(line: 1114, column: 14, scope: !403)
!2197 = !DILocalVariable(name: "st_storage", scope: !403, file: !1, line: 1115, type: !2198)
!2198 = !DICompositeType(tag: DW_TAG_structure_type, name: "stat", file: !2199, line: 46, size: 1152, align: 64, elements: !2200)
!2199 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/stat.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2200 = !{!2201, !2202, !2204, !2206, !2207, !2209, !2211, !2212, !2213, !2215, !2217, !2219, !2225, !2226, !2227}
!2201 = !DIDerivedType(tag: DW_TAG_member, name: "st_dev", scope: !2198, file: !2199, line: 48, baseType: !340, size: 64, align: 64)
!2202 = !DIDerivedType(tag: DW_TAG_member, name: "st_ino", scope: !2198, file: !2199, line: 53, baseType: !2203, size: 64, align: 64, offset: 64)
!2203 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ino_t", file: !41, line: 127, baseType: !47)
!2204 = !DIDerivedType(tag: DW_TAG_member, name: "st_nlink", scope: !2198, file: !2199, line: 61, baseType: !2205, size: 64, align: 64, offset: 128)
!2205 = !DIDerivedType(tag: DW_TAG_typedef, name: "__nlink_t", file: !41, line: 130, baseType: !47)
!2206 = !DIDerivedType(tag: DW_TAG_member, name: "st_mode", scope: !2198, file: !2199, line: 62, baseType: !335, size: 32, align: 32, offset: 192)
!2207 = !DIDerivedType(tag: DW_TAG_member, name: "st_uid", scope: !2198, file: !2199, line: 64, baseType: !2208, size: 32, align: 32, offset: 224)
!2208 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uid_t", file: !41, line: 125, baseType: !13)
!2209 = !DIDerivedType(tag: DW_TAG_member, name: "st_gid", scope: !2198, file: !2199, line: 65, baseType: !2210, size: 32, align: 32, offset: 256)
!2210 = !DIDerivedType(tag: DW_TAG_typedef, name: "__gid_t", file: !41, line: 126, baseType: !13)
!2211 = !DIDerivedType(tag: DW_TAG_member, name: "__pad0", scope: !2198, file: !2199, line: 67, baseType: !23, size: 32, align: 32, offset: 288)
!2212 = !DIDerivedType(tag: DW_TAG_member, name: "st_rdev", scope: !2198, file: !2199, line: 69, baseType: !340, size: 64, align: 64, offset: 320)
!2213 = !DIDerivedType(tag: DW_TAG_member, name: "st_size", scope: !2198, file: !2199, line: 74, baseType: !2214, size: 64, align: 64, offset: 384)
!2214 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off_t", file: !41, line: 131, baseType: !42)
!2215 = !DIDerivedType(tag: DW_TAG_member, name: "st_blksize", scope: !2198, file: !2199, line: 78, baseType: !2216, size: 64, align: 64, offset: 448)
!2216 = !DIDerivedType(tag: DW_TAG_typedef, name: "__blksize_t", file: !41, line: 153, baseType: !42)
!2217 = !DIDerivedType(tag: DW_TAG_member, name: "st_blocks", scope: !2198, file: !2199, line: 80, baseType: !2218, size: 64, align: 64, offset: 512)
!2218 = !DIDerivedType(tag: DW_TAG_typedef, name: "__blkcnt_t", file: !41, line: 158, baseType: !42)
!2219 = !DIDerivedType(tag: DW_TAG_member, name: "st_atim", scope: !2198, file: !2199, line: 91, baseType: !2220, size: 128, align: 64, offset: 576)
!2220 = !DICompositeType(tag: DW_TAG_structure_type, name: "timespec", file: !337, line: 120, size: 128, align: 64, elements: !2221)
!2221 = !{!2222, !2223}
!2222 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !2220, file: !337, line: 122, baseType: !338, size: 64, align: 64)
!2223 = !DIDerivedType(tag: DW_TAG_member, name: "tv_nsec", scope: !2220, file: !337, line: 123, baseType: !2224, size: 64, align: 64, offset: 64)
!2224 = !DIDerivedType(tag: DW_TAG_typedef, name: "__syscall_slong_t", file: !41, line: 175, baseType: !42)
!2225 = !DIDerivedType(tag: DW_TAG_member, name: "st_mtim", scope: !2198, file: !2199, line: 92, baseType: !2220, size: 128, align: 64, offset: 704)
!2226 = !DIDerivedType(tag: DW_TAG_member, name: "st_ctim", scope: !2198, file: !2199, line: 93, baseType: !2220, size: 128, align: 64, offset: 832)
!2227 = !DIDerivedType(tag: DW_TAG_member, name: "__glibc_reserved", scope: !2198, file: !2199, line: 106, baseType: !2228, size: 192, align: 64, offset: 960)
!2228 = !DICompositeType(tag: DW_TAG_array_type, baseType: !2224, size: 192, align: 64, elements: !439)
!2229 = !DILocation(line: 1115, column: 14, scope: !403)
!2230 = !DILocalVariable(name: "st", scope: !403, file: !1, line: 1115, type: !2231)
!2231 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !2198, size: 64, align: 64)
!2232 = !DILocation(line: 1115, column: 27, scope: !403)
!2233 = !DILocalVariable(name: "mp", scope: !403, file: !1, line: 1116, type: !302)
!2234 = !DILocation(line: 1116, column: 22, scope: !403)
!2235 = !DILocalVariable(name: "sparse_entry", scope: !403, file: !1, line: 1117, type: !30)
!2236 = !DILocation(line: 1117, column: 24, scope: !403)
!2237 = !DILocalVariable(name: "r", scope: !403, file: !1, line: 1118, type: !23)
!2238 = !DILocation(line: 1118, column: 6, scope: !403)
!2239 = !DILocalVariable(name: "r1", scope: !403, file: !1, line: 1118, type: !23)
!2240 = !DILocation(line: 1118, column: 22, scope: !403)
!2241 = !DILocalVariable(name: "parsed_kws", scope: !403, file: !1, line: 1118, type: !23)
!2242 = !DILocation(line: 1118, column: 26, scope: !403)
!2243 = !DILocation(line: 1120, column: 2, scope: !403)
!2244 = !DILocation(line: 1120, column: 10, scope: !403)
!2245 = !DILocation(line: 1120, column: 15, scope: !403)
!2246 = !DILocation(line: 1123, column: 29, scope: !403)
!2247 = !DILocation(line: 1123, column: 2, scope: !403)
!2248 = !DILocation(line: 1124, column: 25, scope: !403)
!2249 = !DILocation(line: 1124, column: 2, scope: !403)
!2250 = !DILocation(line: 1125, column: 2, scope: !403)
!2251 = !DILocation(line: 1128, column: 13, scope: !403)
!2252 = !DILocation(line: 1129, column: 17, scope: !403)
!2253 = !DILocation(line: 1129, column: 20, scope: !403)
!2254 = !DILocation(line: 1129, column: 27, scope: !403)
!2255 = !DILocation(line: 1129, column: 34, scope: !403)
!2256 = !DILocation(line: 1129, column: 6, scope: !403)
!2257 = !DILocation(line: 1129, column: 4, scope: !403)
!2258 = !DILocation(line: 1131, column: 6, scope: !2259)
!2259 = distinct !DILexicalBlock(scope: !403, file: !1, line: 1131, column: 6)
!2260 = !DILocation(line: 1131, column: 14, scope: !2259)
!2261 = !DILocation(line: 1131, column: 6, scope: !403)
!2262 = !DILocation(line: 1132, column: 31, scope: !2263)
!2263 = distinct !DILexicalBlock(scope: !2259, file: !1, line: 1131, column: 20)
!2264 = !DILocation(line: 1132, column: 38, scope: !2263)
!2265 = !DILocation(line: 1132, column: 46, scope: !2263)
!2266 = !DILocation(line: 1132, column: 3, scope: !2263)
!2267 = !DILocation(line: 1143, column: 13, scope: !2268)
!2268 = distinct !DILexicalBlock(scope: !2263, file: !1, line: 1143, column: 3)
!2269 = !DILocation(line: 1143, column: 21, scope: !2268)
!2270 = !DILocation(line: 1143, column: 11, scope: !2268)
!2271 = !DILocation(line: 1143, column: 8, scope: !2268)
!2272 = !DILocation(line: 1143, column: 37, scope: !2273)
!2273 = !DILexicalBlockFile(scope: !2274, file: !1, discriminator: 1)
!2274 = distinct !DILexicalBlock(scope: !2268, file: !1, line: 1143, column: 3)
!2275 = !DILocation(line: 1143, column: 40, scope: !2273)
!2276 = !DILocation(line: 1143, column: 3, scope: !2273)
!2277 = !DILocation(line: 1144, column: 8, scope: !2278)
!2278 = distinct !DILexicalBlock(scope: !2279, file: !1, line: 1144, column: 8)
!2279 = distinct !DILexicalBlock(scope: !2274, file: !1, line: 1143, column: 74)
!2280 = !DILocation(line: 1144, column: 12, scope: !2278)
!2281 = !DILocation(line: 1144, column: 17, scope: !2278)
!2282 = !DILocation(line: 1144, column: 21, scope: !2283)
!2283 = !DILexicalBlockFile(scope: !2278, file: !1, discriminator: 1)
!2284 = !DILocation(line: 1144, column: 25, scope: !2283)
!2285 = !DILocation(line: 1145, column: 6, scope: !2278)
!2286 = !DILocation(line: 1145, column: 9, scope: !2283)
!2287 = !DILocation(line: 1145, column: 17, scope: !2283)
!2288 = !DILocation(line: 1145, column: 30, scope: !2283)
!2289 = !DILocation(line: 1145, column: 34, scope: !2283)
!2290 = !DILocation(line: 1145, column: 27, scope: !2283)
!2291 = !DILocation(line: 1146, column: 6, scope: !2278)
!2292 = !DILocation(line: 1146, column: 16, scope: !2283)
!2293 = !DILocation(line: 1146, column: 24, scope: !2283)
!2294 = !DILocation(line: 1146, column: 30, scope: !2283)
!2295 = !DILocation(line: 1146, column: 34, scope: !2283)
!2296 = !DILocation(line: 1146, column: 9, scope: !2283)
!2297 = !DILocation(line: 1146, column: 40, scope: !2283)
!2298 = !DILocation(line: 1144, column: 8, scope: !2299)
!2299 = !DILexicalBlockFile(scope: !2279, file: !1, discriminator: 2)
!2300 = !DILocation(line: 1148, column: 5, scope: !2301)
!2301 = distinct !DILexicalBlock(scope: !2278, file: !1, line: 1146, column: 46)
!2302 = !DILocation(line: 1148, column: 9, scope: !2301)
!2303 = !DILocation(line: 1148, column: 14, scope: !2301)
!2304 = !DILocation(line: 1149, column: 21, scope: !2301)
!2305 = !DILocation(line: 1149, column: 24, scope: !2301)
!2306 = !DILocation(line: 1149, column: 31, scope: !2301)
!2307 = !DILocation(line: 1149, column: 38, scope: !2301)
!2308 = !DILocation(line: 1149, column: 10, scope: !2301)
!2309 = !DILocation(line: 1149, column: 8, scope: !2301)
!2310 = !DILocation(line: 1151, column: 9, scope: !2311)
!2311 = distinct !DILexicalBlock(scope: !2301, file: !1, line: 1151, column: 9)
!2312 = !DILocation(line: 1151, column: 14, scope: !2311)
!2313 = !DILocation(line: 1151, column: 12, scope: !2311)
!2314 = !DILocation(line: 1151, column: 9, scope: !2301)
!2315 = !DILocation(line: 1152, column: 10, scope: !2311)
!2316 = !DILocation(line: 1152, column: 8, scope: !2311)
!2317 = !DILocation(line: 1152, column: 6, scope: !2311)
!2318 = !DILocation(line: 1153, column: 4, scope: !2301)
!2319 = !DILocation(line: 1154, column: 3, scope: !2279)
!2320 = !DILocation(line: 1143, column: 54, scope: !2321)
!2321 = !DILexicalBlockFile(scope: !2274, file: !1, discriminator: 2)
!2322 = !DILocation(line: 1143, column: 58, scope: !2321)
!2323 = !DILocation(line: 1143, column: 52, scope: !2321)
!2324 = !DILocation(line: 1143, column: 3, scope: !2321)
!2325 = !DILocation(line: 1155, column: 2, scope: !2263)
!2326 = !DILocalVariable(name: "n", scope: !2327, file: !1, line: 1161, type: !45)
!2327 = distinct !DILexicalBlock(scope: !2259, file: !1, line: 1155, column: 9)
!2328 = !DILocation(line: 1161, column: 10, scope: !2327)
!2329 = !DILocation(line: 1161, column: 14, scope: !2327)
!2330 = !DILocation(line: 1162, column: 7, scope: !2331)
!2331 = distinct !DILexicalBlock(scope: !2327, file: !1, line: 1162, column: 7)
!2332 = !DILocation(line: 1162, column: 9, scope: !2331)
!2333 = !DILocation(line: 1162, column: 7, scope: !2327)
!2334 = !DILocation(line: 1163, column: 20, scope: !2331)
!2335 = !DILocation(line: 1163, column: 27, scope: !2331)
!2336 = !DILocation(line: 1163, column: 4, scope: !2331)
!2337 = !DILocation(line: 1164, column: 19, scope: !2327)
!2338 = !DILocation(line: 1164, column: 26, scope: !2327)
!2339 = !DILocation(line: 1164, column: 39, scope: !2327)
!2340 = !DILocation(line: 1164, column: 47, scope: !2327)
!2341 = !DILocation(line: 1164, column: 3, scope: !2327)
!2342 = !DILocation(line: 1165, column: 31, scope: !2327)
!2343 = !DILocation(line: 1165, column: 38, scope: !2327)
!2344 = !DILocation(line: 1165, column: 45, scope: !2327)
!2345 = !DILocation(line: 1165, column: 57, scope: !2327)
!2346 = !DILocation(line: 1165, column: 3, scope: !2327)
!2347 = !DILocation(line: 1166, column: 30, scope: !2348)
!2348 = distinct !DILexicalBlock(scope: !2327, file: !1, line: 1166, column: 7)
!2349 = !DILocation(line: 1166, column: 7, scope: !2348)
!2350 = !DILocation(line: 1166, column: 37, scope: !2348)
!2351 = !DILocation(line: 1166, column: 7, scope: !2327)
!2352 = !DILocation(line: 1167, column: 32, scope: !2348)
!2353 = !DILocation(line: 1167, column: 4, scope: !2348)
!2354 = !DILocation(line: 1167, column: 11, scope: !2348)
!2355 = !DILocation(line: 1167, column: 23, scope: !2348)
!2356 = !DILocation(line: 1167, column: 30, scope: !2348)
!2357 = !DILocation(line: 1170, column: 6, scope: !2358)
!2358 = distinct !DILexicalBlock(scope: !403, file: !1, line: 1170, column: 6)
!2359 = !DILocation(line: 1170, column: 13, scope: !2358)
!2360 = !DILocation(line: 1170, column: 6, scope: !403)
!2361 = !DILocation(line: 1182, column: 3, scope: !2362)
!2362 = distinct !DILexicalBlock(scope: !2358, file: !1, line: 1170, column: 22)
!2363 = !DILocation(line: 1182, column: 10, scope: !2362)
!2364 = !DILocation(line: 1182, column: 13, scope: !2362)
!2365 = !DILocation(line: 1183, column: 7, scope: !2366)
!2366 = distinct !DILexicalBlock(scope: !2362, file: !1, line: 1183, column: 7)
!2367 = !DILocation(line: 1183, column: 45, scope: !2366)
!2368 = !DILocation(line: 1183, column: 7, scope: !2362)
!2369 = !DILocation(line: 1184, column: 11, scope: !2366)
!2370 = !DILocation(line: 1184, column: 18, scope: !2366)
!2371 = !DILocation(line: 1184, column: 32, scope: !2366)
!2372 = !DILocation(line: 1184, column: 9, scope: !2366)
!2373 = !DILocation(line: 1184, column: 4, scope: !2366)
!2374 = !DILocation(line: 1186, column: 34, scope: !2366)
!2375 = !DILocation(line: 1186, column: 11, scope: !2366)
!2376 = !DILocation(line: 1186, column: 9, scope: !2366)
!2377 = !DILocation(line: 1188, column: 30, scope: !2378)
!2378 = distinct !DILexicalBlock(scope: !2362, file: !1, line: 1188, column: 7)
!2379 = !DILocation(line: 1188, column: 7, scope: !2378)
!2380 = !DILocation(line: 1188, column: 37, scope: !2378)
!2381 = !DILocation(line: 1188, column: 49, scope: !2378)
!2382 = !DILocation(line: 1189, column: 28, scope: !2378)
!2383 = !DILocation(line: 1189, column: 5, scope: !2378)
!2384 = !DILocation(line: 1189, column: 35, scope: !2378)
!2385 = !DILocation(line: 1188, column: 7, scope: !2386)
!2386 = !DILexicalBlockFile(scope: !2362, file: !1, discriminator: 1)
!2387 = !DILocation(line: 1190, column: 21, scope: !2388)
!2388 = distinct !DILexicalBlock(scope: !2378, file: !1, line: 1189, column: 48)
!2389 = !DILocation(line: 1190, column: 16, scope: !2388)
!2390 = !DILocation(line: 1190, column: 4, scope: !2388)
!2391 = !DILocation(line: 1190, column: 11, scope: !2388)
!2392 = !DILocation(line: 1190, column: 14, scope: !2388)
!2393 = !DILocation(line: 1191, column: 34, scope: !2388)
!2394 = !DILocation(line: 1191, column: 41, scope: !2388)
!2395 = !DILocation(line: 1191, column: 4, scope: !2388)
!2396 = !DILocation(line: 1192, column: 8, scope: !2397)
!2397 = distinct !DILexicalBlock(scope: !2388, file: !1, line: 1192, column: 8)
!2398 = !DILocation(line: 1192, column: 15, scope: !2397)
!2399 = !DILocation(line: 1192, column: 18, scope: !2397)
!2400 = !DILocation(line: 1192, column: 24, scope: !2397)
!2401 = !DILocation(line: 1193, column: 6, scope: !2397)
!2402 = !DILocation(line: 1193, column: 12, scope: !2397)
!2403 = !DILocation(line: 1193, column: 22, scope: !2397)
!2404 = !DILocation(line: 1194, column: 6, scope: !2397)
!2405 = !DILocation(line: 1194, column: 44, scope: !2397)
!2406 = !DILocation(line: 1192, column: 8, scope: !2407)
!2407 = !DILexicalBlockFile(scope: !2388, file: !1, discriminator: 1)
!2408 = !DILocation(line: 1195, column: 24, scope: !2409)
!2409 = distinct !DILexicalBlock(scope: !2397, file: !1, line: 1194, column: 50)
!2410 = !DILocation(line: 1195, column: 27, scope: !2409)
!2411 = !DILocation(line: 1195, column: 36, scope: !2409)
!2412 = !DILocation(line: 1196, column: 24, scope: !2409)
!2413 = !DILocation(line: 1195, column: 5, scope: !2414)
!2414 = !DILexicalBlockFile(scope: !2409, file: !1, discriminator: 1)
!2415 = !DILocation(line: 1197, column: 7, scope: !2409)
!2416 = !DILocation(line: 1198, column: 4, scope: !2409)
!2417 = !DILocation(line: 1199, column: 3, scope: !2388)
!2418 = !DILocation(line: 1201, column: 6, scope: !2362)
!2419 = !DILocation(line: 1202, column: 7, scope: !2420)
!2420 = distinct !DILexicalBlock(scope: !2362, file: !1, line: 1202, column: 7)
!2421 = !DILocation(line: 1202, column: 14, scope: !2420)
!2422 = !DILocation(line: 1202, column: 17, scope: !2420)
!2423 = !DILocation(line: 1202, column: 7, scope: !2362)
!2424 = !DILocation(line: 1203, column: 14, scope: !2425)
!2425 = distinct !DILexicalBlock(scope: !2426, file: !1, line: 1203, column: 8)
!2426 = distinct !DILexicalBlock(scope: !2420, file: !1, line: 1202, column: 23)
!2427 = !DILocation(line: 1203, column: 21, scope: !2425)
!2428 = !DILocation(line: 1203, column: 25, scope: !2425)
!2429 = !DILocation(line: 1203, column: 8, scope: !2425)
!2430 = !DILocation(line: 1203, column: 29, scope: !2425)
!2431 = !DILocation(line: 1203, column: 8, scope: !2426)
!2432 = !DILocation(line: 1204, column: 24, scope: !2433)
!2433 = distinct !DILexicalBlock(scope: !2425, file: !1, line: 1203, column: 36)
!2434 = !DILocation(line: 1204, column: 27, scope: !2433)
!2435 = !DILocation(line: 1204, column: 36, scope: !2433)
!2436 = !DILocation(line: 1205, column: 29, scope: !2433)
!2437 = !DILocation(line: 1204, column: 5, scope: !2438)
!2438 = !DILexicalBlockFile(scope: !2433, file: !1, discriminator: 1)
!2439 = !DILocation(line: 1206, column: 7, scope: !2433)
!2440 = !DILocation(line: 1208, column: 11, scope: !2433)
!2441 = !DILocation(line: 1208, column: 18, scope: !2433)
!2442 = !DILocation(line: 1208, column: 5, scope: !2433)
!2443 = !DILocation(line: 1209, column: 5, scope: !2433)
!2444 = !DILocation(line: 1209, column: 12, scope: !2433)
!2445 = !DILocation(line: 1209, column: 15, scope: !2433)
!2446 = !DILocation(line: 1210, column: 8, scope: !2433)
!2447 = !DILocation(line: 1211, column: 4, scope: !2433)
!2448 = !DILocation(line: 1212, column: 3, scope: !2426)
!2449 = !DILocation(line: 1212, column: 20, scope: !2450)
!2450 = !DILexicalBlockFile(scope: !2451, file: !1, discriminator: 1)
!2451 = distinct !DILexicalBlock(scope: !2420, file: !1, line: 1212, column: 14)
!2452 = !DILocation(line: 1212, column: 26, scope: !2450)
!2453 = !DILocation(line: 1212, column: 14, scope: !2450)
!2454 = !DILocation(line: 1212, column: 30, scope: !2450)
!2455 = !DILocation(line: 1213, column: 7, scope: !2456)
!2456 = distinct !DILexicalBlock(scope: !2451, file: !1, line: 1212, column: 37)
!2457 = !DILocation(line: 1214, column: 3, scope: !2456)
!2458 = !DILocation(line: 1220, column: 7, scope: !2459)
!2459 = distinct !DILexicalBlock(scope: !2362, file: !1, line: 1220, column: 7)
!2460 = !DILocation(line: 1220, column: 10, scope: !2459)
!2461 = !DILocation(line: 1220, column: 7, scope: !2362)
!2462 = !DILocation(line: 1221, column: 10, scope: !2463)
!2463 = distinct !DILexicalBlock(scope: !2464, file: !1, line: 1221, column: 8)
!2464 = distinct !DILexicalBlock(scope: !2459, file: !1, line: 1220, column: 19)
!2465 = !DILocation(line: 1221, column: 14, scope: !2463)
!2466 = !DILocation(line: 1221, column: 22, scope: !2463)
!2467 = !DILocation(line: 1221, column: 32, scope: !2463)
!2468 = !DILocation(line: 1221, column: 43, scope: !2463)
!2469 = !DILocation(line: 1222, column: 33, scope: !2463)
!2470 = !DILocation(line: 1222, column: 10, scope: !2463)
!2471 = !DILocation(line: 1222, column: 40, scope: !2463)
!2472 = !DILocation(line: 1224, column: 6, scope: !2463)
!2473 = !DILocation(line: 1224, column: 10, scope: !2474)
!2474 = !DILexicalBlockFile(scope: !2463, file: !1, discriminator: 1)
!2475 = !DILocation(line: 1224, column: 14, scope: !2474)
!2476 = !DILocation(line: 1224, column: 22, scope: !2474)
!2477 = !DILocation(line: 1224, column: 32, scope: !2474)
!2478 = !DILocation(line: 1224, column: 43, scope: !2474)
!2479 = !DILocation(line: 1225, column: 33, scope: !2463)
!2480 = !DILocation(line: 1225, column: 10, scope: !2463)
!2481 = !DILocation(line: 1225, column: 40, scope: !2463)
!2482 = !DILocation(line: 1228, column: 6, scope: !2463)
!2483 = !DILocation(line: 1228, column: 10, scope: !2474)
!2484 = !DILocation(line: 1228, column: 14, scope: !2474)
!2485 = !DILocation(line: 1228, column: 22, scope: !2474)
!2486 = !DILocation(line: 1228, column: 34, scope: !2474)
!2487 = !DILocation(line: 1228, column: 46, scope: !2474)
!2488 = !DILocation(line: 1229, column: 33, scope: !2463)
!2489 = !DILocation(line: 1229, column: 10, scope: !2463)
!2490 = !DILocation(line: 1229, column: 40, scope: !2463)
!2491 = !DILocation(line: 1232, column: 6, scope: !2463)
!2492 = !DILocation(line: 1232, column: 10, scope: !2474)
!2493 = !DILocation(line: 1232, column: 14, scope: !2474)
!2494 = !DILocation(line: 1232, column: 22, scope: !2474)
!2495 = !DILocation(line: 1232, column: 32, scope: !2474)
!2496 = !DILocation(line: 1232, column: 43, scope: !2474)
!2497 = !DILocation(line: 1233, column: 33, scope: !2463)
!2498 = !DILocation(line: 1233, column: 10, scope: !2463)
!2499 = !DILocation(line: 1233, column: 40, scope: !2463)
!2500 = !DILocation(line: 1236, column: 6, scope: !2463)
!2501 = !DILocation(line: 1236, column: 10, scope: !2474)
!2502 = !DILocation(line: 1236, column: 14, scope: !2474)
!2503 = !DILocation(line: 1236, column: 22, scope: !2474)
!2504 = !DILocation(line: 1236, column: 32, scope: !2474)
!2505 = !DILocation(line: 1236, column: 43, scope: !2474)
!2506 = !DILocation(line: 1237, column: 33, scope: !2463)
!2507 = !DILocation(line: 1237, column: 10, scope: !2463)
!2508 = !DILocation(line: 1237, column: 40, scope: !2463)
!2509 = !DILocation(line: 1239, column: 6, scope: !2463)
!2510 = !DILocation(line: 1239, column: 10, scope: !2474)
!2511 = !DILocation(line: 1239, column: 14, scope: !2474)
!2512 = !DILocation(line: 1239, column: 22, scope: !2474)
!2513 = !DILocation(line: 1239, column: 32, scope: !2474)
!2514 = !DILocation(line: 1239, column: 43, scope: !2474)
!2515 = !DILocation(line: 1240, column: 33, scope: !2463)
!2516 = !DILocation(line: 1240, column: 10, scope: !2463)
!2517 = !DILocation(line: 1240, column: 40, scope: !2463)
!2518 = !DILocation(line: 1242, column: 6, scope: !2463)
!2519 = !DILocation(line: 1242, column: 10, scope: !2474)
!2520 = !DILocation(line: 1242, column: 14, scope: !2474)
!2521 = !DILocation(line: 1242, column: 22, scope: !2474)
!2522 = !DILocation(line: 1242, column: 32, scope: !2474)
!2523 = !DILocation(line: 1242, column: 43, scope: !2474)
!2524 = !DILocation(line: 1243, column: 33, scope: !2463)
!2525 = !DILocation(line: 1243, column: 10, scope: !2463)
!2526 = !DILocation(line: 1243, column: 40, scope: !2463)
!2527 = !DILocation(line: 1221, column: 8, scope: !2528)
!2528 = !DILexicalBlockFile(scope: !2464, file: !1, discriminator: 1)
!2529 = !DILocation(line: 1247, column: 4, scope: !2530)
!2530 = distinct !DILexicalBlock(scope: !2463, file: !1, line: 1245, column: 6)
!2531 = !DILocation(line: 1249, column: 9, scope: !2532)
!2532 = distinct !DILexicalBlock(scope: !2533, file: !1, line: 1249, column: 9)
!2533 = distinct !DILexicalBlock(scope: !2463, file: !1, line: 1247, column: 11)
!2534 = !DILocation(line: 1249, column: 16, scope: !2532)
!2535 = !DILocation(line: 1249, column: 19, scope: !2532)
!2536 = !DILocation(line: 1249, column: 9, scope: !2533)
!2537 = !DILocation(line: 1250, column: 12, scope: !2532)
!2538 = !DILocation(line: 1250, column: 19, scope: !2532)
!2539 = !DILocation(line: 1250, column: 6, scope: !2532)
!2540 = !DILocation(line: 1251, column: 5, scope: !2533)
!2541 = !DILocation(line: 1251, column: 12, scope: !2533)
!2542 = !DILocation(line: 1251, column: 15, scope: !2533)
!2543 = !DILocation(line: 1252, column: 9, scope: !2544)
!2544 = distinct !DILexicalBlock(scope: !2533, file: !1, line: 1252, column: 9)
!2545 = !DILocation(line: 1252, column: 20, scope: !2544)
!2546 = !DILocation(line: 1252, column: 9, scope: !2533)
!2547 = !DILocation(line: 1255, column: 7, scope: !2548)
!2548 = distinct !DILexicalBlock(scope: !2544, file: !1, line: 1252, column: 42)
!2549 = !DILocation(line: 1255, column: 16, scope: !2548)
!2550 = !DILocation(line: 1256, column: 5, scope: !2548)
!2551 = !DILocation(line: 1256, column: 16, scope: !2552)
!2552 = !DILexicalBlockFile(scope: !2553, file: !1, discriminator: 1)
!2553 = distinct !DILexicalBlock(scope: !2544, file: !1, line: 1256, column: 16)
!2554 = !DILocation(line: 1256, column: 18, scope: !2552)
!2555 = !DILocation(line: 1257, column: 25, scope: !2556)
!2556 = distinct !DILexicalBlock(scope: !2553, file: !1, line: 1256, column: 33)
!2557 = !DILocation(line: 1257, column: 28, scope: !2556)
!2558 = !DILocation(line: 1261, column: 33, scope: !2556)
!2559 = !DILocation(line: 1261, column: 10, scope: !2556)
!2560 = !DILocation(line: 1257, column: 6, scope: !2556)
!2561 = !DILocation(line: 1262, column: 8, scope: !2556)
!2562 = !DILocation(line: 1263, column: 5, scope: !2556)
!2563 = !DILocation(line: 1264, column: 13, scope: !2533)
!2564 = !DILocation(line: 1264, column: 5, scope: !2533)
!2565 = !DILocation(line: 1266, column: 3, scope: !2464)
!2566 = !DILocation(line: 1274, column: 7, scope: !2567)
!2567 = distinct !DILexicalBlock(scope: !2362, file: !1, line: 1274, column: 7)
!2568 = !DILocation(line: 1274, column: 10, scope: !2567)
!2569 = !DILocation(line: 1274, column: 7, scope: !2362)
!2570 = !DILocation(line: 1275, column: 10, scope: !2571)
!2571 = distinct !DILexicalBlock(scope: !2572, file: !1, line: 1275, column: 8)
!2572 = distinct !DILexicalBlock(scope: !2567, file: !1, line: 1274, column: 19)
!2573 = !DILocation(line: 1275, column: 21, scope: !2571)
!2574 = !DILocation(line: 1275, column: 41, scope: !2571)
!2575 = !DILocation(line: 1275, column: 46, scope: !2571)
!2576 = !DILocation(line: 1276, column: 6, scope: !2571)
!2577 = !DILocation(line: 1276, column: 17, scope: !2571)
!2578 = !DILocation(line: 1276, column: 39, scope: !2571)
!2579 = !DILocation(line: 1276, column: 45, scope: !2571)
!2580 = !DILocation(line: 1277, column: 29, scope: !2571)
!2581 = !DILocation(line: 1277, column: 6, scope: !2571)
!2582 = !DILocation(line: 1277, column: 36, scope: !2571)
!2583 = !DILocation(line: 1277, column: 48, scope: !2571)
!2584 = !DILocation(line: 1278, column: 29, scope: !2571)
!2585 = !DILocation(line: 1278, column: 6, scope: !2571)
!2586 = !DILocation(line: 1278, column: 36, scope: !2571)
!2587 = !DILocation(line: 1275, column: 8, scope: !2588)
!2588 = !DILexicalBlockFile(scope: !2572, file: !1, discriminator: 1)
!2589 = !DILocation(line: 1279, column: 28, scope: !2571)
!2590 = !DILocation(line: 1279, column: 35, scope: !2571)
!2591 = !DILocation(line: 1279, column: 39, scope: !2571)
!2592 = !DILocation(line: 1279, column: 5, scope: !2571)
!2593 = !DILocation(line: 1280, column: 9, scope: !2594)
!2594 = distinct !DILexicalBlock(scope: !2572, file: !1, line: 1280, column: 8)
!2595 = !DILocation(line: 1280, column: 20, scope: !2594)
!2596 = !DILocation(line: 1281, column: 5, scope: !2594)
!2597 = !DILocation(line: 1281, column: 10, scope: !2594)
!2598 = !DILocation(line: 1282, column: 9, scope: !2594)
!2599 = !DILocation(line: 1282, column: 20, scope: !2594)
!2600 = !DILocation(line: 1282, column: 42, scope: !2594)
!2601 = !DILocation(line: 1280, column: 8, scope: !2588)
!2602 = !DILocation(line: 1283, column: 27, scope: !2594)
!2603 = !DILocation(line: 1283, column: 34, scope: !2594)
!2604 = !DILocation(line: 1283, column: 38, scope: !2594)
!2605 = !DILocation(line: 1283, column: 5, scope: !2594)
!2606 = !DILocation(line: 1284, column: 9, scope: !2607)
!2607 = distinct !DILexicalBlock(scope: !2572, file: !1, line: 1284, column: 8)
!2608 = !DILocation(line: 1284, column: 20, scope: !2607)
!2609 = !DILocation(line: 1285, column: 5, scope: !2607)
!2610 = !DILocation(line: 1285, column: 10, scope: !2607)
!2611 = !DILocation(line: 1286, column: 9, scope: !2607)
!2612 = !DILocation(line: 1286, column: 20, scope: !2607)
!2613 = !DILocation(line: 1286, column: 42, scope: !2607)
!2614 = !DILocation(line: 1284, column: 8, scope: !2588)
!2615 = !DILocation(line: 1287, column: 27, scope: !2607)
!2616 = !DILocation(line: 1287, column: 34, scope: !2607)
!2617 = !DILocation(line: 1287, column: 38, scope: !2607)
!2618 = !DILocation(line: 1287, column: 5, scope: !2607)
!2619 = !DILocation(line: 1288, column: 9, scope: !2620)
!2620 = distinct !DILexicalBlock(scope: !2572, file: !1, line: 1288, column: 8)
!2621 = !DILocation(line: 1288, column: 20, scope: !2620)
!2622 = !DILocation(line: 1288, column: 39, scope: !2620)
!2623 = !DILocation(line: 1288, column: 44, scope: !2620)
!2624 = !DILocation(line: 1289, column: 9, scope: !2620)
!2625 = !DILocation(line: 1289, column: 20, scope: !2620)
!2626 = !DILocation(line: 1289, column: 42, scope: !2620)
!2627 = !DILocation(line: 1288, column: 8, scope: !2588)
!2628 = !DILocation(line: 1294, column: 29, scope: !2629)
!2629 = distinct !DILexicalBlock(scope: !2620, file: !1, line: 1289, column: 48)
!2630 = !DILocation(line: 1294, column: 36, scope: !2629)
!2631 = !DILocation(line: 1294, column: 40, scope: !2629)
!2632 = !DILocation(line: 1295, column: 7, scope: !2629)
!2633 = !DILocation(line: 1295, column: 11, scope: !2629)
!2634 = !DILocation(line: 1295, column: 19, scope: !2629)
!2635 = !DILocation(line: 1294, column: 5, scope: !2629)
!2636 = !DILocation(line: 1308, column: 4, scope: !2629)
!2637 = !DILocation(line: 1309, column: 9, scope: !2638)
!2638 = distinct !DILexicalBlock(scope: !2572, file: !1, line: 1309, column: 8)
!2639 = !DILocation(line: 1309, column: 20, scope: !2638)
!2640 = !DILocation(line: 1309, column: 39, scope: !2638)
!2641 = !DILocation(line: 1309, column: 44, scope: !2638)
!2642 = !DILocation(line: 1310, column: 9, scope: !2638)
!2643 = !DILocation(line: 1310, column: 20, scope: !2638)
!2644 = !DILocation(line: 1310, column: 42, scope: !2638)
!2645 = !DILocation(line: 1309, column: 8, scope: !2588)
!2646 = !DILocation(line: 1311, column: 29, scope: !2638)
!2647 = !DILocation(line: 1311, column: 36, scope: !2638)
!2648 = !DILocation(line: 1311, column: 40, scope: !2638)
!2649 = !DILocation(line: 1311, column: 5, scope: !2638)
!2650 = !DILocation(line: 1312, column: 9, scope: !2651)
!2651 = distinct !DILexicalBlock(scope: !2572, file: !1, line: 1312, column: 8)
!2652 = !DILocation(line: 1312, column: 20, scope: !2651)
!2653 = !DILocation(line: 1312, column: 38, scope: !2651)
!2654 = !DILocation(line: 1312, column: 43, scope: !2651)
!2655 = !DILocation(line: 1313, column: 9, scope: !2651)
!2656 = !DILocation(line: 1313, column: 20, scope: !2651)
!2657 = !DILocation(line: 1313, column: 42, scope: !2651)
!2658 = !DILocation(line: 1312, column: 8, scope: !2588)
!2659 = !DILocation(line: 1314, column: 28, scope: !2651)
!2660 = !DILocation(line: 1314, column: 35, scope: !2651)
!2661 = !DILocation(line: 1314, column: 39, scope: !2651)
!2662 = !DILocation(line: 1314, column: 5, scope: !2651)
!2663 = !DILocation(line: 1315, column: 9, scope: !2664)
!2664 = distinct !DILexicalBlock(scope: !2572, file: !1, line: 1315, column: 8)
!2665 = !DILocation(line: 1315, column: 20, scope: !2664)
!2666 = !DILocation(line: 1315, column: 38, scope: !2664)
!2667 = !DILocation(line: 1315, column: 43, scope: !2664)
!2668 = !DILocation(line: 1316, column: 9, scope: !2664)
!2669 = !DILocation(line: 1316, column: 20, scope: !2664)
!2670 = !DILocation(line: 1316, column: 42, scope: !2664)
!2671 = !DILocation(line: 1315, column: 8, scope: !2588)
!2672 = !DILocation(line: 1317, column: 28, scope: !2664)
!2673 = !DILocation(line: 1317, column: 35, scope: !2664)
!2674 = !DILocation(line: 1317, column: 39, scope: !2664)
!2675 = !DILocation(line: 1317, column: 5, scope: !2664)
!2676 = !DILocation(line: 1318, column: 26, scope: !2572)
!2677 = !DILocation(line: 1318, column: 33, scope: !2572)
!2678 = !DILocation(line: 1318, column: 37, scope: !2572)
!2679 = !DILocation(line: 1318, column: 4, scope: !2572)
!2680 = !DILocation(line: 1319, column: 26, scope: !2572)
!2681 = !DILocation(line: 1319, column: 33, scope: !2572)
!2682 = !DILocation(line: 1319, column: 37, scope: !2572)
!2683 = !DILocation(line: 1319, column: 4, scope: !2572)
!2684 = !DILocation(line: 1321, column: 26, scope: !2572)
!2685 = !DILocation(line: 1321, column: 33, scope: !2572)
!2686 = !DILocation(line: 1321, column: 4, scope: !2572)
!2687 = !DILocation(line: 1323, column: 3, scope: !2572)
!2688 = !DILocation(line: 1323, column: 14, scope: !2689)
!2689 = !DILexicalBlockFile(scope: !2690, file: !1, discriminator: 1)
!2690 = distinct !DILexicalBlock(scope: !2567, file: !1, line: 1323, column: 14)
!2691 = !DILocation(line: 1323, column: 25, scope: !2689)
!2692 = !DILocation(line: 1329, column: 5, scope: !2693)
!2693 = distinct !DILexicalBlock(scope: !2690, file: !1, line: 1323, column: 47)
!2694 = !DILocation(line: 1329, column: 14, scope: !2693)
!2695 = !DILocation(line: 1330, column: 4, scope: !2693)
!2696 = !DILocation(line: 1332, column: 2, scope: !2362)
!2697 = !DILocation(line: 1334, column: 39, scope: !403)
!2698 = !DILocation(line: 1334, column: 20, scope: !403)
!2699 = !DILocation(line: 1334, column: 2, scope: !403)
!2700 = !DILocation(line: 1334, column: 9, scope: !403)
!2701 = !DILocation(line: 1334, column: 18, scope: !403)
!2702 = !DILocation(line: 1335, column: 2, scope: !403)
!2703 = !DILocation(line: 1335, column: 9, scope: !403)
!2704 = !DILocation(line: 1335, column: 16, scope: !403)
!2705 = !DILocation(line: 1337, column: 9, scope: !403)
!2706 = !DILocation(line: 1337, column: 2, scope: !403)
!2707 = !DILocation(line: 1338, column: 1, scope: !403)
!2708 = !DILocalVariable(name: "a", arg: 1, scope: !378, file: !1, line: 1958, type: !4)
!2709 = !DILocation(line: 1958, column: 31, scope: !378)
!2710 = !DILocalVariable(name: "mtree", arg: 2, scope: !378, file: !1, line: 1958, type: !291)
!2711 = !DILocation(line: 1958, column: 48, scope: !378)
!2712 = !DILocalVariable(name: "start", arg: 3, scope: !378, file: !1, line: 1958, type: !381)
!2713 = !DILocation(line: 1958, column: 62, scope: !378)
!2714 = !DILocalVariable(name: "limit", arg: 4, scope: !378, file: !1, line: 1959, type: !38)
!2715 = !DILocation(line: 1959, column: 13, scope: !378)
!2716 = !DILocalVariable(name: "bytes_read", scope: !378, file: !1, line: 1961, type: !38)
!2717 = !DILocation(line: 1961, column: 10, scope: !378)
!2718 = !DILocalVariable(name: "total_size", scope: !378, file: !1, line: 1962, type: !38)
!2719 = !DILocation(line: 1962, column: 10, scope: !378)
!2720 = !DILocalVariable(name: "find_off", scope: !378, file: !1, line: 1963, type: !38)
!2721 = !DILocation(line: 1963, column: 10, scope: !378)
!2722 = !DILocalVariable(name: "t", scope: !378, file: !1, line: 1964, type: !43)
!2723 = !DILocation(line: 1964, column: 14, scope: !378)
!2724 = !DILocalVariable(name: "nl", scope: !378, file: !1, line: 1965, type: !122)
!2725 = !DILocation(line: 1965, column: 8, scope: !378)
!2726 = !DILocalVariable(name: "u", scope: !378, file: !1, line: 1966, type: !95)
!2727 = !DILocation(line: 1966, column: 8, scope: !378)
!2728 = !DILocation(line: 1969, column: 2, scope: !378)
!2729 = !DILocation(line: 1971, column: 28, scope: !2730)
!2730 = distinct !DILexicalBlock(scope: !2731, file: !1, line: 1969, column: 11)
!2731 = distinct !DILexicalBlock(scope: !2732, file: !1, line: 1969, column: 2)
!2732 = distinct !DILexicalBlock(scope: !378, file: !1, line: 1969, column: 2)
!2733 = !DILocation(line: 1971, column: 7, scope: !2730)
!2734 = !DILocation(line: 1971, column: 5, scope: !2730)
!2735 = !DILocation(line: 1972, column: 7, scope: !2736)
!2736 = distinct !DILexicalBlock(scope: !2730, file: !1, line: 1972, column: 7)
!2737 = !DILocation(line: 1972, column: 9, scope: !2736)
!2738 = !DILocation(line: 1972, column: 7, scope: !2730)
!2739 = !DILocation(line: 1973, column: 4, scope: !2736)
!2740 = !DILocation(line: 1974, column: 7, scope: !2741)
!2741 = distinct !DILexicalBlock(scope: !2730, file: !1, line: 1974, column: 7)
!2742 = !DILocation(line: 1974, column: 18, scope: !2741)
!2743 = !DILocation(line: 1974, column: 7, scope: !2730)
!2744 = !DILocation(line: 1975, column: 4, scope: !2741)
!2745 = !DILocation(line: 1976, column: 15, scope: !2730)
!2746 = !DILocation(line: 1976, column: 24, scope: !2730)
!2747 = !DILocation(line: 1976, column: 8, scope: !2730)
!2748 = !DILocation(line: 1976, column: 6, scope: !2730)
!2749 = !DILocation(line: 1978, column: 7, scope: !2750)
!2750 = distinct !DILexicalBlock(scope: !2730, file: !1, line: 1978, column: 7)
!2751 = !DILocation(line: 1978, column: 10, scope: !2750)
!2752 = !DILocation(line: 1978, column: 7, scope: !2730)
!2753 = !DILocation(line: 1979, column: 32, scope: !2754)
!2754 = distinct !DILexicalBlock(scope: !2750, file: !1, line: 1978, column: 19)
!2755 = !DILocation(line: 1979, column: 53, scope: !2754)
!2756 = !DILocation(line: 1979, column: 36, scope: !2754)
!2757 = !DILocation(line: 1979, column: 56, scope: !2754)
!2758 = !DILocation(line: 1979, column: 15, scope: !2754)
!2759 = !DILocation(line: 1980, column: 3, scope: !2754)
!2760 = !DILocation(line: 1981, column: 7, scope: !2761)
!2761 = distinct !DILexicalBlock(scope: !2730, file: !1, line: 1981, column: 7)
!2762 = !DILocation(line: 1981, column: 20, scope: !2761)
!2763 = !DILocation(line: 1981, column: 18, scope: !2761)
!2764 = !DILocation(line: 1981, column: 31, scope: !2761)
!2765 = !DILocation(line: 1981, column: 37, scope: !2761)
!2766 = !DILocation(line: 1981, column: 35, scope: !2761)
!2767 = !DILocation(line: 1981, column: 7, scope: !2730)
!2768 = !DILocation(line: 1982, column: 23, scope: !2769)
!2769 = distinct !DILexicalBlock(scope: !2761, file: !1, line: 1981, column: 44)
!2770 = !DILocation(line: 1982, column: 26, scope: !2769)
!2771 = !DILocation(line: 1982, column: 4, scope: !2769)
!2772 = !DILocation(line: 1985, column: 4, scope: !2769)
!2773 = !DILocation(line: 1987, column: 30, scope: !2774)
!2774 = distinct !DILexicalBlock(scope: !2730, file: !1, line: 1987, column: 7)
!2775 = !DILocation(line: 1987, column: 37, scope: !2774)
!2776 = !DILocation(line: 1988, column: 4, scope: !2774)
!2777 = !DILocation(line: 1988, column: 17, scope: !2774)
!2778 = !DILocation(line: 1988, column: 15, scope: !2774)
!2779 = !DILocation(line: 1988, column: 28, scope: !2774)
!2780 = !DILocation(line: 1987, column: 7, scope: !2774)
!2781 = !DILocation(line: 1988, column: 33, scope: !2774)
!2782 = !DILocation(line: 1987, column: 7, scope: !2730)
!2783 = !DILocation(line: 1989, column: 23, scope: !2784)
!2784 = distinct !DILexicalBlock(scope: !2774, file: !1, line: 1988, column: 42)
!2785 = !DILocation(line: 1989, column: 26, scope: !2784)
!2786 = !DILocation(line: 1989, column: 4, scope: !2784)
!2787 = !DILocation(line: 1991, column: 4, scope: !2784)
!2788 = !DILocation(line: 1994, column: 10, scope: !2730)
!2789 = !DILocation(line: 1994, column: 17, scope: !2730)
!2790 = !DILocation(line: 1994, column: 22, scope: !2730)
!2791 = !DILocation(line: 1994, column: 26, scope: !2730)
!2792 = !DILocation(line: 1994, column: 24, scope: !2730)
!2793 = !DILocation(line: 1994, column: 38, scope: !2730)
!2794 = !DILocation(line: 1994, column: 41, scope: !2730)
!2795 = !DILocation(line: 1994, column: 3, scope: !2730)
!2796 = !DILocation(line: 1995, column: 26, scope: !2730)
!2797 = !DILocation(line: 1995, column: 29, scope: !2730)
!2798 = !DILocation(line: 1995, column: 3, scope: !2730)
!2799 = !DILocation(line: 1996, column: 17, scope: !2730)
!2800 = !DILocation(line: 1996, column: 14, scope: !2730)
!2801 = !DILocation(line: 1997, column: 17, scope: !2730)
!2802 = !DILocation(line: 1997, column: 3, scope: !2730)
!2803 = !DILocation(line: 1997, column: 10, scope: !2730)
!2804 = !DILocation(line: 1997, column: 15, scope: !2730)
!2805 = !DILocation(line: 1997, column: 29, scope: !2730)
!2806 = !DILocation(line: 1999, column: 12, scope: !2807)
!2807 = distinct !DILexicalBlock(scope: !2730, file: !1, line: 1999, column: 3)
!2808 = !DILocation(line: 1999, column: 19, scope: !2807)
!2809 = !DILocation(line: 1999, column: 24, scope: !2807)
!2810 = !DILocation(line: 1999, column: 28, scope: !2807)
!2811 = !DILocation(line: 1999, column: 26, scope: !2807)
!2812 = !DILocation(line: 1999, column: 10, scope: !2807)
!2813 = !DILocation(line: 1999, column: 8, scope: !2807)
!2814 = !DILocation(line: 1999, column: 39, scope: !2815)
!2815 = !DILexicalBlockFile(scope: !2816, file: !1, discriminator: 1)
!2816 = distinct !DILexicalBlock(scope: !2807, file: !1, line: 1999, column: 3)
!2817 = !DILocation(line: 1999, column: 38, scope: !2815)
!2818 = !DILocation(line: 1999, column: 3, scope: !2815)
!2819 = !DILocation(line: 2000, column: 8, scope: !2820)
!2820 = distinct !DILexicalBlock(scope: !2821, file: !1, line: 2000, column: 8)
!2821 = distinct !DILexicalBlock(scope: !2816, file: !1, line: 1999, column: 47)
!2822 = !DILocation(line: 2000, column: 13, scope: !2820)
!2823 = !DILocation(line: 2000, column: 8, scope: !2821)
!2824 = !DILocation(line: 2002, column: 14, scope: !2825)
!2825 = distinct !DILexicalBlock(scope: !2820, file: !1, line: 2000, column: 22)
!2826 = !DILocation(line: 2002, column: 21, scope: !2825)
!2827 = !DILocation(line: 2002, column: 26, scope: !2825)
!2828 = !DILocation(line: 2002, column: 6, scope: !2825)
!2829 = !DILocation(line: 2002, column: 12, scope: !2825)
!2830 = !DILocation(line: 2003, column: 12, scope: !2825)
!2831 = !DILocation(line: 2003, column: 5, scope: !2825)
!2832 = !DILocation(line: 2004, column: 15, scope: !2833)
!2833 = distinct !DILexicalBlock(scope: !2820, file: !1, line: 2004, column: 15)
!2834 = !DILocation(line: 2004, column: 20, scope: !2833)
!2835 = !DILocation(line: 2004, column: 15, scope: !2820)
!2836 = !DILocation(line: 2006, column: 9, scope: !2837)
!2837 = distinct !DILexicalBlock(scope: !2838, file: !1, line: 2006, column: 9)
!2838 = distinct !DILexicalBlock(scope: !2833, file: !1, line: 2004, column: 28)
!2839 = !DILocation(line: 2006, column: 12, scope: !2837)
!2840 = !DILocation(line: 2006, column: 9, scope: !2838)
!2841 = !DILocation(line: 2008, column: 6, scope: !2842)
!2842 = distinct !DILexicalBlock(scope: !2837, file: !1, line: 2006, column: 21)
!2843 = !DILocation(line: 2010, column: 4, scope: !2838)
!2844 = !DILocation(line: 2010, column: 15, scope: !2845)
!2845 = !DILexicalBlockFile(scope: !2846, file: !1, discriminator: 1)
!2846 = distinct !DILexicalBlock(scope: !2833, file: !1, line: 2010, column: 15)
!2847 = !DILocation(line: 2010, column: 20, scope: !2845)
!2848 = !DILocation(line: 2011, column: 9, scope: !2849)
!2849 = distinct !DILexicalBlock(scope: !2850, file: !1, line: 2011, column: 9)
!2850 = distinct !DILexicalBlock(scope: !2846, file: !1, line: 2010, column: 29)
!2851 = !DILocation(line: 2011, column: 14, scope: !2849)
!2852 = !DILocation(line: 2011, column: 9, scope: !2850)
!2853 = !DILocation(line: 2013, column: 17, scope: !2854)
!2854 = distinct !DILexicalBlock(scope: !2849, file: !1, line: 2011, column: 23)
!2855 = !DILocation(line: 2014, column: 20, scope: !2854)
!2856 = !DILocation(line: 2014, column: 6, scope: !2854)
!2857 = !DILocation(line: 2014, column: 13, scope: !2854)
!2858 = !DILocation(line: 2014, column: 18, scope: !2854)
!2859 = !DILocation(line: 2014, column: 32, scope: !2854)
!2860 = !DILocation(line: 2015, column: 6, scope: !2854)
!2861 = !DILocation(line: 2016, column: 16, scope: !2862)
!2862 = distinct !DILexicalBlock(scope: !2849, file: !1, line: 2016, column: 16)
!2863 = !DILocation(line: 2016, column: 21, scope: !2862)
!2864 = !DILocation(line: 2016, column: 16, scope: !2849)
!2865 = !DILocation(line: 2018, column: 6, scope: !2866)
!2866 = distinct !DILexicalBlock(scope: !2862, file: !1, line: 2016, column: 30)
!2867 = !DILocation(line: 2019, column: 5, scope: !2866)
!2868 = !DILocation(line: 2020, column: 4, scope: !2850)
!2869 = !DILocation(line: 2021, column: 3, scope: !2821)
!2870 = !DILocation(line: 1999, column: 42, scope: !2871)
!2871 = !DILexicalBlockFile(scope: !2816, file: !1, discriminator: 2)
!2872 = !DILocation(line: 1999, column: 3, scope: !2871)
!2873 = !DILocation(line: 2022, column: 14, scope: !2730)
!2874 = !DILocation(line: 2022, column: 18, scope: !2730)
!2875 = !DILocation(line: 2022, column: 25, scope: !2730)
!2876 = !DILocation(line: 2022, column: 30, scope: !2730)
!2877 = !DILocation(line: 2022, column: 16, scope: !2730)
!2878 = !DILocation(line: 2022, column: 12, scope: !2730)
!2879 = !DILocation(line: 1969, column: 2, scope: !2880)
!2880 = !DILexicalBlockFile(scope: !2731, file: !1, discriminator: 1)
!2881 = !DILocation(line: 2024, column: 1, scope: !378)
!2882 = !DILocalVariable(name: "a", arg: 1, scope: !382, file: !1, line: 866, type: !4)
!2883 = !DILocation(line: 866, column: 40, scope: !382)
!2884 = !DILocalVariable(name: "mtree", arg: 2, scope: !382, file: !1, line: 866, type: !291)
!2885 = !DILocation(line: 866, column: 57, scope: !382)
!2886 = !DILocalVariable(name: "global", arg: 3, scope: !382, file: !1, line: 867, type: !385)
!2887 = !DILocation(line: 867, column: 27, scope: !382)
!2888 = !DILocalVariable(name: "line", arg: 4, scope: !382, file: !1, line: 867, type: !80)
!2889 = !DILocation(line: 867, column: 47, scope: !382)
!2890 = !DILocalVariable(name: "line_len", arg: 5, scope: !382, file: !1, line: 867, type: !38)
!2891 = !DILocation(line: 867, column: 61, scope: !382)
!2892 = !DILocalVariable(name: "last_entry", arg: 6, scope: !382, file: !1, line: 868, type: !386)
!2893 = !DILocation(line: 868, column: 26, scope: !382)
!2894 = !DILocalVariable(name: "is_form_d", arg: 7, scope: !382, file: !1, line: 868, type: !23)
!2895 = !DILocation(line: 868, column: 42, scope: !382)
!2896 = !DILocalVariable(name: "entry", scope: !382, file: !1, line: 870, type: !302)
!2897 = !DILocation(line: 870, column: 22, scope: !382)
!2898 = !DILocalVariable(name: "ht_iter", scope: !382, file: !1, line: 870, type: !302)
!2899 = !DILocation(line: 870, column: 30, scope: !382)
!2900 = !DILocalVariable(name: "iter", scope: !382, file: !1, line: 871, type: !307)
!2901 = !DILocation(line: 871, column: 23, scope: !382)
!2902 = !DILocalVariable(name: "next", scope: !382, file: !1, line: 872, type: !80)
!2903 = !DILocation(line: 872, column: 14, scope: !382)
!2904 = !DILocalVariable(name: "eq", scope: !382, file: !1, line: 872, type: !80)
!2905 = !DILocation(line: 872, column: 21, scope: !382)
!2906 = !DILocalVariable(name: "name", scope: !382, file: !1, line: 872, type: !80)
!2907 = !DILocation(line: 872, column: 26, scope: !382)
!2908 = !DILocalVariable(name: "end", scope: !382, file: !1, line: 872, type: !80)
!2909 = !DILocation(line: 872, column: 33, scope: !382)
!2910 = !DILocalVariable(name: "name_len", scope: !382, file: !1, line: 873, type: !45)
!2911 = !DILocation(line: 873, column: 9, scope: !382)
!2912 = !DILocalVariable(name: "len", scope: !382, file: !1, line: 873, type: !45)
!2913 = !DILocation(line: 873, column: 19, scope: !382)
!2914 = !DILocalVariable(name: "r", scope: !382, file: !1, line: 874, type: !23)
!2915 = !DILocation(line: 874, column: 6, scope: !382)
!2916 = !DILocalVariable(name: "i", scope: !382, file: !1, line: 874, type: !23)
!2917 = !DILocation(line: 874, column: 9, scope: !382)
!2918 = !DILocalVariable(name: "ht_idx", scope: !382, file: !1, line: 875, type: !13)
!2919 = !DILocation(line: 875, column: 15, scope: !382)
!2920 = !DILocation(line: 877, column: 15, scope: !2921)
!2921 = distinct !DILexicalBlock(scope: !382, file: !1, line: 877, column: 6)
!2922 = !DILocation(line: 877, column: 13, scope: !2921)
!2923 = !DILocation(line: 877, column: 39, scope: !2921)
!2924 = !DILocation(line: 877, column: 6, scope: !382)
!2925 = !DILocation(line: 878, column: 22, scope: !2926)
!2926 = distinct !DILexicalBlock(scope: !2921, file: !1, line: 877, column: 48)
!2927 = !DILocation(line: 878, column: 25, scope: !2926)
!2928 = !DILocation(line: 878, column: 34, scope: !2926)
!2929 = !DILocation(line: 878, column: 3, scope: !2930)
!2930 = !DILexicalBlockFile(scope: !2926, file: !1, discriminator: 1)
!2931 = !DILocation(line: 879, column: 3, scope: !2926)
!2932 = !DILocation(line: 881, column: 2, scope: !382)
!2933 = !DILocation(line: 881, column: 9, scope: !382)
!2934 = !DILocation(line: 881, column: 14, scope: !382)
!2935 = !DILocation(line: 882, column: 2, scope: !382)
!2936 = !DILocation(line: 882, column: 9, scope: !382)
!2937 = !DILocation(line: 882, column: 17, scope: !382)
!2938 = !DILocation(line: 883, column: 2, scope: !382)
!2939 = !DILocation(line: 883, column: 9, scope: !382)
!2940 = !DILocation(line: 883, column: 14, scope: !382)
!2941 = !DILocation(line: 884, column: 2, scope: !382)
!2942 = !DILocation(line: 884, column: 9, scope: !382)
!2943 = !DILocation(line: 884, column: 14, scope: !382)
!2944 = !DILocation(line: 885, column: 2, scope: !382)
!2945 = !DILocation(line: 885, column: 9, scope: !382)
!2946 = !DILocation(line: 885, column: 14, scope: !382)
!2947 = !DILocation(line: 886, column: 2, scope: !382)
!2948 = !DILocation(line: 886, column: 9, scope: !382)
!2949 = !DILocation(line: 886, column: 19, scope: !382)
!2950 = !DILocation(line: 887, column: 2, scope: !382)
!2951 = !DILocation(line: 887, column: 9, scope: !382)
!2952 = !DILocation(line: 887, column: 24, scope: !382)
!2953 = !DILocation(line: 890, column: 7, scope: !2954)
!2954 = distinct !DILexicalBlock(scope: !382, file: !1, line: 890, column: 6)
!2955 = !DILocation(line: 890, column: 6, scope: !2954)
!2956 = !DILocation(line: 890, column: 18, scope: !2954)
!2957 = !DILocation(line: 890, column: 6, scope: !382)
!2958 = !DILocation(line: 891, column: 20, scope: !2954)
!2959 = !DILocation(line: 891, column: 3, scope: !2954)
!2960 = !DILocation(line: 891, column: 10, scope: !2954)
!2961 = !DILocation(line: 891, column: 18, scope: !2954)
!2962 = !DILocation(line: 893, column: 25, scope: !2954)
!2963 = !DILocation(line: 893, column: 5, scope: !2954)
!2964 = !DILocation(line: 893, column: 4, scope: !2954)
!2965 = !DILocation(line: 893, column: 18, scope: !2954)
!2966 = !DILocation(line: 893, column: 23, scope: !2954)
!2967 = !DILocation(line: 894, column: 16, scope: !382)
!2968 = !DILocation(line: 894, column: 3, scope: !382)
!2969 = !DILocation(line: 894, column: 14, scope: !382)
!2970 = !DILocation(line: 896, column: 6, scope: !2971)
!2971 = distinct !DILexicalBlock(scope: !382, file: !1, line: 896, column: 6)
!2972 = !DILocation(line: 896, column: 6, scope: !382)
!2973 = !DILocation(line: 899, column: 3, scope: !2974)
!2974 = distinct !DILexicalBlock(scope: !2971, file: !1, line: 896, column: 17)
!2975 = !DILocation(line: 899, column: 10, scope: !2976)
!2976 = !DILexicalBlockFile(scope: !2974, file: !1, discriminator: 1)
!2977 = !DILocation(line: 899, column: 19, scope: !2976)
!2978 = !DILocation(line: 899, column: 3, scope: !2976)
!2979 = !DILocalVariable(name: "last_character", scope: !2980, file: !1, line: 900, type: !82)
!2980 = distinct !DILexicalBlock(scope: !2974, file: !1, line: 899, column: 24)
!2981 = !DILocation(line: 900, column: 9, scope: !2980)
!2982 = !DILocation(line: 900, column: 31, scope: !2980)
!2983 = !DILocation(line: 900, column: 40, scope: !2980)
!2984 = !DILocation(line: 900, column: 26, scope: !2980)
!2985 = !DILocation(line: 901, column: 8, scope: !2986)
!2986 = distinct !DILexicalBlock(scope: !2980, file: !1, line: 901, column: 8)
!2987 = !DILocation(line: 901, column: 23, scope: !2986)
!2988 = !DILocation(line: 902, column: 8, scope: !2986)
!2989 = !DILocation(line: 902, column: 11, scope: !2990)
!2990 = !DILexicalBlockFile(scope: !2986, file: !1, discriminator: 1)
!2991 = !DILocation(line: 902, column: 26, scope: !2990)
!2992 = !DILocation(line: 903, column: 8, scope: !2986)
!2993 = !DILocation(line: 903, column: 11, scope: !2990)
!2994 = !DILocation(line: 903, column: 26, scope: !2990)
!2995 = !DILocation(line: 904, column: 8, scope: !2986)
!2996 = !DILocation(line: 904, column: 11, scope: !2990)
!2997 = !DILocation(line: 904, column: 26, scope: !2990)
!2998 = !DILocation(line: 901, column: 8, scope: !2999)
!2999 = !DILexicalBlockFile(scope: !2980, file: !1, discriminator: 1)
!3000 = !DILocation(line: 905, column: 13, scope: !3001)
!3001 = distinct !DILexicalBlock(scope: !2986, file: !1, line: 904, column: 34)
!3002 = !DILocation(line: 906, column: 4, scope: !3001)
!3003 = !DILocation(line: 907, column: 5, scope: !3004)
!3004 = distinct !DILexicalBlock(scope: !2986, file: !1, line: 906, column: 11)
!3005 = !DILocation(line: 899, column: 3, scope: !3006)
!3006 = !DILexicalBlockFile(scope: !2974, file: !1, discriminator: 2)
!3007 = !DILocation(line: 911, column: 10, scope: !2974)
!3008 = !DILocation(line: 911, column: 8, scope: !2974)
!3009 = !DILocation(line: 912, column: 10, scope: !3010)
!3010 = distinct !DILexicalBlock(scope: !2974, file: !1, line: 912, column: 3)
!3011 = !DILocation(line: 912, column: 8, scope: !3010)
!3012 = !DILocation(line: 912, column: 15, scope: !3013)
!3013 = !DILexicalBlockFile(scope: !3014, file: !1, discriminator: 1)
!3014 = distinct !DILexicalBlock(scope: !3010, file: !1, line: 912, column: 3)
!3015 = !DILocation(line: 912, column: 19, scope: !3013)
!3016 = !DILocation(line: 912, column: 17, scope: !3013)
!3017 = !DILocation(line: 912, column: 3, scope: !3013)
!3018 = !DILocation(line: 913, column: 13, scope: !3019)
!3019 = distinct !DILexicalBlock(scope: !3020, file: !1, line: 913, column: 8)
!3020 = distinct !DILexicalBlock(scope: !3014, file: !1, line: 912, column: 34)
!3021 = !DILocation(line: 913, column: 8, scope: !3019)
!3022 = !DILocation(line: 913, column: 16, scope: !3019)
!3023 = !DILocation(line: 914, column: 8, scope: !3019)
!3024 = !DILocation(line: 914, column: 16, scope: !3025)
!3025 = !DILexicalBlockFile(scope: !3019, file: !1, discriminator: 1)
!3026 = !DILocation(line: 914, column: 11, scope: !3025)
!3027 = !DILocation(line: 914, column: 19, scope: !3025)
!3028 = !DILocation(line: 915, column: 8, scope: !3019)
!3029 = !DILocation(line: 915, column: 16, scope: !3025)
!3030 = !DILocation(line: 915, column: 11, scope: !3025)
!3031 = !DILocation(line: 915, column: 19, scope: !3025)
!3032 = !DILocation(line: 916, column: 8, scope: !3019)
!3033 = !DILocation(line: 916, column: 16, scope: !3025)
!3034 = !DILocation(line: 916, column: 11, scope: !3025)
!3035 = !DILocation(line: 916, column: 19, scope: !3025)
!3036 = !DILocation(line: 913, column: 8, scope: !3037)
!3037 = !DILexicalBlockFile(scope: !3020, file: !1, discriminator: 1)
!3038 = !DILocation(line: 917, column: 12, scope: !3039)
!3039 = distinct !DILexicalBlock(scope: !3019, file: !1, line: 916, column: 27)
!3040 = !DILocation(line: 917, column: 19, scope: !3039)
!3041 = !DILocation(line: 917, column: 17, scope: !3039)
!3042 = !DILocation(line: 917, column: 21, scope: !3039)
!3043 = !DILocation(line: 917, column: 10, scope: !3039)
!3044 = !DILocation(line: 918, column: 4, scope: !3039)
!3045 = !DILocation(line: 919, column: 3, scope: !3020)
!3046 = !DILocation(line: 912, column: 30, scope: !3047)
!3047 = !DILexicalBlockFile(scope: !3014, file: !1, discriminator: 2)
!3048 = !DILocation(line: 912, column: 3, scope: !3047)
!3049 = !DILocation(line: 920, column: 14, scope: !2974)
!3050 = !DILocation(line: 920, column: 21, scope: !2974)
!3051 = !DILocation(line: 920, column: 19, scope: !2974)
!3052 = !DILocation(line: 920, column: 32, scope: !2974)
!3053 = !DILocation(line: 920, column: 30, scope: !2974)
!3054 = !DILocation(line: 920, column: 12, scope: !2974)
!3055 = !DILocation(line: 921, column: 9, scope: !2974)
!3056 = !DILocation(line: 921, column: 7, scope: !2974)
!3057 = !DILocation(line: 922, column: 2, scope: !2974)
!3058 = !DILocation(line: 924, column: 22, scope: !3059)
!3059 = distinct !DILexicalBlock(scope: !2971, file: !1, line: 922, column: 9)
!3060 = !DILocation(line: 924, column: 14, scope: !3059)
!3061 = !DILocation(line: 924, column: 12, scope: !3059)
!3062 = !DILocation(line: 925, column: 10, scope: !3059)
!3063 = !DILocation(line: 925, column: 8, scope: !3059)
!3064 = !DILocation(line: 926, column: 11, scope: !3059)
!3065 = !DILocation(line: 926, column: 8, scope: !3059)
!3066 = !DILocation(line: 927, column: 9, scope: !3059)
!3067 = !DILocation(line: 927, column: 16, scope: !3059)
!3068 = !DILocation(line: 927, column: 14, scope: !3059)
!3069 = !DILocation(line: 927, column: 7, scope: !3059)
!3070 = !DILocation(line: 932, column: 28, scope: !3071)
!3071 = distinct !DILexicalBlock(scope: !382, file: !1, line: 932, column: 6)
!3072 = !DILocation(line: 932, column: 37, scope: !3071)
!3073 = !DILocation(line: 932, column: 21, scope: !3071)
!3074 = !DILocation(line: 932, column: 7, scope: !3071)
!3075 = !DILocation(line: 932, column: 14, scope: !3071)
!3076 = !DILocation(line: 932, column: 19, scope: !3071)
!3077 = !DILocation(line: 932, column: 43, scope: !3071)
!3078 = !DILocation(line: 932, column: 6, scope: !382)
!3079 = !DILocation(line: 933, column: 22, scope: !3080)
!3080 = distinct !DILexicalBlock(scope: !3071, file: !1, line: 932, column: 52)
!3081 = !DILocation(line: 933, column: 25, scope: !3080)
!3082 = !DILocation(line: 933, column: 34, scope: !3080)
!3083 = !DILocation(line: 933, column: 3, scope: !3084)
!3084 = !DILexicalBlockFile(scope: !3080, file: !1, discriminator: 1)
!3085 = !DILocation(line: 934, column: 3, scope: !3080)
!3086 = !DILocation(line: 937, column: 9, scope: !382)
!3087 = !DILocation(line: 937, column: 16, scope: !382)
!3088 = !DILocation(line: 937, column: 22, scope: !382)
!3089 = !DILocation(line: 937, column: 28, scope: !382)
!3090 = !DILocation(line: 937, column: 2, scope: !382)
!3091 = !DILocation(line: 938, column: 14, scope: !382)
!3092 = !DILocation(line: 938, column: 2, scope: !382)
!3093 = !DILocation(line: 938, column: 9, scope: !382)
!3094 = !DILocation(line: 938, column: 24, scope: !382)
!3095 = !DILocation(line: 939, column: 16, scope: !382)
!3096 = !DILocation(line: 939, column: 23, scope: !382)
!3097 = !DILocation(line: 939, column: 29, scope: !382)
!3098 = !DILocation(line: 939, column: 2, scope: !382)
!3099 = !DILocation(line: 940, column: 26, scope: !382)
!3100 = !DILocation(line: 940, column: 33, scope: !382)
!3101 = !DILocation(line: 940, column: 21, scope: !382)
!3102 = !DILocation(line: 940, column: 2, scope: !382)
!3103 = !DILocation(line: 940, column: 9, scope: !382)
!3104 = !DILocation(line: 940, column: 19, scope: !382)
!3105 = !DILocation(line: 942, column: 11, scope: !382)
!3106 = !DILocation(line: 942, column: 18, scope: !382)
!3107 = !DILocation(line: 942, column: 28, scope: !382)
!3108 = !DILocation(line: 942, column: 9, scope: !382)
!3109 = !DILocation(line: 943, column: 40, scope: !3110)
!3110 = distinct !DILexicalBlock(scope: !382, file: !1, line: 943, column: 6)
!3111 = !DILocation(line: 943, column: 17, scope: !3110)
!3112 = !DILocation(line: 943, column: 24, scope: !3110)
!3113 = !DILocation(line: 943, column: 15, scope: !3110)
!3114 = !DILocation(line: 943, column: 49, scope: !3110)
!3115 = !DILocation(line: 943, column: 6, scope: !382)
!3116 = !DILocation(line: 944, column: 3, scope: !3117)
!3117 = distinct !DILexicalBlock(scope: !3110, file: !1, line: 943, column: 58)
!3118 = !DILocation(line: 944, column: 10, scope: !3119)
!3119 = !DILexicalBlockFile(scope: !3117, file: !1, discriminator: 1)
!3120 = !DILocation(line: 944, column: 19, scope: !3119)
!3121 = !DILocation(line: 944, column: 3, scope: !3119)
!3122 = !DILocation(line: 945, column: 14, scope: !3117)
!3123 = !DILocation(line: 945, column: 23, scope: !3117)
!3124 = !DILocation(line: 945, column: 12, scope: !3117)
!3125 = !DILocation(line: 944, column: 3, scope: !3126)
!3126 = !DILexicalBlockFile(scope: !3117, file: !1, discriminator: 2)
!3127 = !DILocation(line: 946, column: 29, scope: !3117)
!3128 = !DILocation(line: 946, column: 3, scope: !3117)
!3129 = !DILocation(line: 946, column: 12, scope: !3117)
!3130 = !DILocation(line: 946, column: 27, scope: !3117)
!3131 = !DILocation(line: 947, column: 2, scope: !3117)
!3132 = !DILocation(line: 948, column: 36, scope: !3133)
!3133 = distinct !DILexicalBlock(scope: !3110, file: !1, line: 947, column: 9)
!3134 = !DILocation(line: 948, column: 26, scope: !3133)
!3135 = !DILocation(line: 948, column: 3, scope: !3133)
!3136 = !DILocation(line: 948, column: 10, scope: !3133)
!3137 = !DILocation(line: 948, column: 34, scope: !3133)
!3138 = !DILocation(line: 951, column: 15, scope: !3139)
!3139 = distinct !DILexicalBlock(scope: !382, file: !1, line: 951, column: 2)
!3140 = !DILocation(line: 951, column: 14, scope: !3139)
!3141 = !DILocation(line: 951, column: 12, scope: !3139)
!3142 = !DILocation(line: 951, column: 7, scope: !3139)
!3143 = !DILocation(line: 951, column: 23, scope: !3144)
!3144 = !DILexicalBlockFile(scope: !3145, file: !1, discriminator: 1)
!3145 = distinct !DILexicalBlock(scope: !3139, file: !1, line: 951, column: 2)
!3146 = !DILocation(line: 951, column: 28, scope: !3144)
!3147 = !DILocation(line: 951, column: 2, scope: !3144)
!3148 = !DILocation(line: 952, column: 18, scope: !3149)
!3149 = distinct !DILexicalBlock(scope: !3145, file: !1, line: 951, column: 56)
!3150 = !DILocation(line: 952, column: 22, scope: !3149)
!3151 = !DILocation(line: 952, column: 29, scope: !3149)
!3152 = !DILocation(line: 952, column: 38, scope: !3149)
!3153 = !DILocation(line: 952, column: 44, scope: !3149)
!3154 = !DILocation(line: 953, column: 14, scope: !3149)
!3155 = !DILocation(line: 953, column: 20, scope: !3149)
!3156 = !DILocation(line: 953, column: 7, scope: !3149)
!3157 = !DILocation(line: 952, column: 7, scope: !3149)
!3158 = !DILocation(line: 952, column: 5, scope: !3149)
!3159 = !DILocation(line: 954, column: 7, scope: !3160)
!3160 = distinct !DILexicalBlock(scope: !3149, file: !1, line: 954, column: 7)
!3161 = !DILocation(line: 954, column: 9, scope: !3160)
!3162 = !DILocation(line: 954, column: 7, scope: !3149)
!3163 = !DILocation(line: 955, column: 12, scope: !3160)
!3164 = !DILocation(line: 955, column: 4, scope: !3160)
!3165 = !DILocation(line: 956, column: 2, scope: !3149)
!3166 = !DILocation(line: 951, column: 44, scope: !3167)
!3167 = !DILexicalBlockFile(scope: !3145, file: !1, discriminator: 2)
!3168 = !DILocation(line: 951, column: 50, scope: !3167)
!3169 = !DILocation(line: 951, column: 42, scope: !3167)
!3170 = !DILocation(line: 951, column: 2, scope: !3167)
!3171 = !DILocation(line: 958, column: 2, scope: !382)
!3172 = !DILocation(line: 959, column: 10, scope: !3173)
!3173 = distinct !DILexicalBlock(scope: !3174, file: !1, line: 958, column: 11)
!3174 = distinct !DILexicalBlock(scope: !3175, file: !1, line: 958, column: 2)
!3175 = distinct !DILexicalBlock(scope: !382, file: !1, line: 958, column: 2)
!3176 = !DILocation(line: 959, column: 24, scope: !3173)
!3177 = !DILocation(line: 959, column: 17, scope: !3173)
!3178 = !DILocation(line: 959, column: 15, scope: !3173)
!3179 = !DILocation(line: 959, column: 8, scope: !3173)
!3180 = !DILocation(line: 960, column: 8, scope: !3181)
!3181 = distinct !DILexicalBlock(scope: !3173, file: !1, line: 960, column: 7)
!3182 = !DILocation(line: 960, column: 7, scope: !3181)
!3183 = !DILocation(line: 960, column: 13, scope: !3181)
!3184 = !DILocation(line: 960, column: 7, scope: !3173)
!3185 = !DILocation(line: 961, column: 4, scope: !3181)
!3186 = !DILocation(line: 962, column: 7, scope: !3187)
!3187 = distinct !DILexicalBlock(scope: !3173, file: !1, line: 962, column: 7)
!3188 = !DILocation(line: 962, column: 15, scope: !3187)
!3189 = !DILocation(line: 962, column: 12, scope: !3187)
!3190 = !DILocation(line: 962, column: 7, scope: !3173)
!3191 = !DILocation(line: 963, column: 4, scope: !3187)
!3192 = !DILocation(line: 964, column: 10, scope: !3173)
!3193 = !DILocation(line: 964, column: 8, scope: !3173)
!3194 = !DILocation(line: 965, column: 10, scope: !3173)
!3195 = !DILocation(line: 965, column: 25, scope: !3173)
!3196 = !DILocation(line: 965, column: 17, scope: !3173)
!3197 = !DILocation(line: 965, column: 15, scope: !3173)
!3198 = !DILocation(line: 965, column: 8, scope: !3173)
!3199 = !DILocation(line: 966, column: 15, scope: !3173)
!3200 = !DILocation(line: 966, column: 8, scope: !3173)
!3201 = !DILocation(line: 966, column: 6, scope: !3173)
!3202 = !DILocation(line: 967, column: 7, scope: !3203)
!3203 = distinct !DILexicalBlock(scope: !3173, file: !1, line: 967, column: 7)
!3204 = !DILocation(line: 967, column: 10, scope: !3203)
!3205 = !DILocation(line: 967, column: 18, scope: !3203)
!3206 = !DILocation(line: 967, column: 21, scope: !3207)
!3207 = !DILexicalBlockFile(scope: !3203, file: !1, discriminator: 1)
!3208 = !DILocation(line: 967, column: 26, scope: !3207)
!3209 = !DILocation(line: 967, column: 24, scope: !3207)
!3210 = !DILocation(line: 967, column: 7, scope: !3207)
!3211 = !DILocation(line: 968, column: 10, scope: !3203)
!3212 = !DILocation(line: 968, column: 17, scope: !3203)
!3213 = !DILocation(line: 968, column: 15, scope: !3203)
!3214 = !DILocation(line: 968, column: 8, scope: !3203)
!3215 = !DILocation(line: 968, column: 4, scope: !3203)
!3216 = !DILocation(line: 970, column: 10, scope: !3203)
!3217 = !DILocation(line: 970, column: 15, scope: !3203)
!3218 = !DILocation(line: 970, column: 13, scope: !3203)
!3219 = !DILocation(line: 970, column: 8, scope: !3203)
!3220 = !DILocation(line: 972, column: 18, scope: !3173)
!3221 = !DILocation(line: 972, column: 25, scope: !3173)
!3222 = !DILocation(line: 972, column: 34, scope: !3173)
!3223 = !DILocation(line: 972, column: 40, scope: !3173)
!3224 = !DILocation(line: 972, column: 3, scope: !3173)
!3225 = !DILocation(line: 973, column: 18, scope: !3173)
!3226 = !DILocation(line: 973, column: 22, scope: !3173)
!3227 = !DILocation(line: 973, column: 29, scope: !3173)
!3228 = !DILocation(line: 973, column: 38, scope: !3173)
!3229 = !DILocation(line: 973, column: 44, scope: !3173)
!3230 = !DILocation(line: 973, column: 51, scope: !3173)
!3231 = !DILocation(line: 973, column: 49, scope: !3173)
!3232 = !DILocation(line: 973, column: 7, scope: !3173)
!3233 = !DILocation(line: 973, column: 5, scope: !3173)
!3234 = !DILocation(line: 974, column: 7, scope: !3235)
!3235 = distinct !DILexicalBlock(scope: !3173, file: !1, line: 974, column: 7)
!3236 = !DILocation(line: 974, column: 9, scope: !3235)
!3237 = !DILocation(line: 974, column: 7, scope: !3173)
!3238 = !DILocation(line: 975, column: 12, scope: !3235)
!3239 = !DILocation(line: 975, column: 4, scope: !3235)
!3240 = !DILocation(line: 976, column: 10, scope: !3173)
!3241 = !DILocation(line: 976, column: 8, scope: !3173)
!3242 = !DILocation(line: 958, column: 2, scope: !3243)
!3243 = !DILexicalBlockFile(scope: !3174, file: !1, discriminator: 1)
!3244 = !DILocation(line: 978, column: 1, scope: !382)
!3245 = !DILocalVariable(name: "a", arg: 1, scope: !399, file: !1, line: 805, type: !4)
!3246 = !DILocation(line: 805, column: 41, scope: !399)
!3247 = !DILocalVariable(name: "global", arg: 2, scope: !399, file: !1, line: 806, type: !385)
!3248 = !DILocation(line: 806, column: 27, scope: !399)
!3249 = !DILocalVariable(name: "line", arg: 3, scope: !399, file: !1, line: 806, type: !80)
!3250 = !DILocation(line: 806, column: 47, scope: !399)
!3251 = !DILocalVariable(name: "next", scope: !399, file: !1, line: 808, type: !80)
!3252 = !DILocation(line: 808, column: 14, scope: !399)
!3253 = !DILocalVariable(name: "eq", scope: !399, file: !1, line: 808, type: !80)
!3254 = !DILocation(line: 808, column: 21, scope: !399)
!3255 = !DILocalVariable(name: "len", scope: !399, file: !1, line: 809, type: !45)
!3256 = !DILocation(line: 809, column: 9, scope: !399)
!3257 = !DILocalVariable(name: "r", scope: !399, file: !1, line: 810, type: !23)
!3258 = !DILocation(line: 810, column: 6, scope: !399)
!3259 = !DILocation(line: 812, column: 7, scope: !399)
!3260 = !DILocation(line: 813, column: 2, scope: !399)
!3261 = !DILocation(line: 814, column: 10, scope: !3262)
!3262 = distinct !DILexicalBlock(scope: !3263, file: !1, line: 813, column: 11)
!3263 = distinct !DILexicalBlock(scope: !3264, file: !1, line: 813, column: 2)
!3264 = distinct !DILexicalBlock(scope: !399, file: !1, line: 813, column: 2)
!3265 = !DILocation(line: 814, column: 24, scope: !3262)
!3266 = !DILocation(line: 814, column: 17, scope: !3262)
!3267 = !DILocation(line: 814, column: 15, scope: !3262)
!3268 = !DILocation(line: 814, column: 8, scope: !3262)
!3269 = !DILocation(line: 815, column: 8, scope: !3270)
!3270 = distinct !DILexicalBlock(scope: !3262, file: !1, line: 815, column: 7)
!3271 = !DILocation(line: 815, column: 7, scope: !3270)
!3272 = !DILocation(line: 815, column: 13, scope: !3270)
!3273 = !DILocation(line: 815, column: 7, scope: !3262)
!3274 = !DILocation(line: 816, column: 4, scope: !3270)
!3275 = !DILocation(line: 817, column: 10, scope: !3262)
!3276 = !DILocation(line: 817, column: 8, scope: !3262)
!3277 = !DILocation(line: 818, column: 10, scope: !3262)
!3278 = !DILocation(line: 818, column: 25, scope: !3262)
!3279 = !DILocation(line: 818, column: 17, scope: !3262)
!3280 = !DILocation(line: 818, column: 15, scope: !3262)
!3281 = !DILocation(line: 818, column: 8, scope: !3262)
!3282 = !DILocation(line: 819, column: 15, scope: !3262)
!3283 = !DILocation(line: 819, column: 8, scope: !3262)
!3284 = !DILocation(line: 819, column: 6, scope: !3262)
!3285 = !DILocation(line: 820, column: 7, scope: !3286)
!3286 = distinct !DILexicalBlock(scope: !3262, file: !1, line: 820, column: 7)
!3287 = !DILocation(line: 820, column: 12, scope: !3286)
!3288 = !DILocation(line: 820, column: 10, scope: !3286)
!3289 = !DILocation(line: 820, column: 7, scope: !3262)
!3290 = !DILocation(line: 821, column: 10, scope: !3286)
!3291 = !DILocation(line: 821, column: 17, scope: !3286)
!3292 = !DILocation(line: 821, column: 15, scope: !3286)
!3293 = !DILocation(line: 821, column: 8, scope: !3286)
!3294 = !DILocation(line: 821, column: 4, scope: !3286)
!3295 = !DILocation(line: 823, column: 10, scope: !3286)
!3296 = !DILocation(line: 823, column: 15, scope: !3286)
!3297 = !DILocation(line: 823, column: 13, scope: !3286)
!3298 = !DILocation(line: 823, column: 8, scope: !3286)
!3299 = !DILocation(line: 825, column: 17, scope: !3262)
!3300 = !DILocation(line: 825, column: 25, scope: !3262)
!3301 = !DILocation(line: 825, column: 31, scope: !3262)
!3302 = !DILocation(line: 825, column: 3, scope: !3262)
!3303 = !DILocation(line: 826, column: 18, scope: !3262)
!3304 = !DILocation(line: 826, column: 21, scope: !3262)
!3305 = !DILocation(line: 826, column: 29, scope: !3262)
!3306 = !DILocation(line: 826, column: 35, scope: !3262)
!3307 = !DILocation(line: 826, column: 42, scope: !3262)
!3308 = !DILocation(line: 826, column: 40, scope: !3262)
!3309 = !DILocation(line: 826, column: 7, scope: !3262)
!3310 = !DILocation(line: 826, column: 5, scope: !3262)
!3311 = !DILocation(line: 827, column: 7, scope: !3312)
!3312 = distinct !DILexicalBlock(scope: !3262, file: !1, line: 827, column: 7)
!3313 = !DILocation(line: 827, column: 9, scope: !3312)
!3314 = !DILocation(line: 827, column: 7, scope: !3262)
!3315 = !DILocation(line: 828, column: 12, scope: !3312)
!3316 = !DILocation(line: 828, column: 4, scope: !3312)
!3317 = !DILocation(line: 829, column: 10, scope: !3262)
!3318 = !DILocation(line: 829, column: 8, scope: !3262)
!3319 = !DILocation(line: 813, column: 2, scope: !3320)
!3320 = !DILexicalBlockFile(scope: !3263, file: !1, discriminator: 1)
!3321 = !DILocation(line: 831, column: 1, scope: !399)
!3322 = !DILocalVariable(name: "a", arg: 1, scope: !402, file: !1, line: 834, type: !4)
!3323 = !DILocation(line: 834, column: 43, scope: !402)
!3324 = !DILocalVariable(name: "global", arg: 2, scope: !402, file: !1, line: 835, type: !385)
!3325 = !DILocation(line: 835, column: 27, scope: !402)
!3326 = !DILocalVariable(name: "line", arg: 3, scope: !402, file: !1, line: 835, type: !80)
!3327 = !DILocation(line: 835, column: 47, scope: !402)
!3328 = !DILocalVariable(name: "next", scope: !402, file: !1, line: 837, type: !80)
!3329 = !DILocation(line: 837, column: 14, scope: !402)
!3330 = !DILocalVariable(name: "len", scope: !402, file: !1, line: 838, type: !45)
!3331 = !DILocation(line: 838, column: 9, scope: !402)
!3332 = !DILocation(line: 840, column: 7, scope: !402)
!3333 = !DILocation(line: 841, column: 13, scope: !3334)
!3334 = distinct !DILexicalBlock(scope: !402, file: !1, line: 841, column: 6)
!3335 = !DILocation(line: 841, column: 6, scope: !3334)
!3336 = !DILocation(line: 841, column: 24, scope: !3334)
!3337 = !DILocation(line: 841, column: 6, scope: !402)
!3338 = !DILocation(line: 842, column: 22, scope: !3339)
!3339 = distinct !DILexicalBlock(scope: !3334, file: !1, line: 841, column: 33)
!3340 = !DILocation(line: 842, column: 25, scope: !3339)
!3341 = !DILocation(line: 842, column: 3, scope: !3339)
!3342 = !DILocation(line: 844, column: 3, scope: !3339)
!3343 = !DILocation(line: 847, column: 2, scope: !402)
!3344 = !DILocation(line: 848, column: 10, scope: !3345)
!3345 = distinct !DILexicalBlock(scope: !3346, file: !1, line: 847, column: 11)
!3346 = distinct !DILexicalBlock(scope: !3347, file: !1, line: 847, column: 2)
!3347 = distinct !DILexicalBlock(scope: !402, file: !1, line: 847, column: 2)
!3348 = !DILocation(line: 848, column: 24, scope: !3345)
!3349 = !DILocation(line: 848, column: 17, scope: !3345)
!3350 = !DILocation(line: 848, column: 15, scope: !3345)
!3351 = !DILocation(line: 848, column: 8, scope: !3345)
!3352 = !DILocation(line: 849, column: 8, scope: !3353)
!3353 = distinct !DILexicalBlock(scope: !3345, file: !1, line: 849, column: 7)
!3354 = !DILocation(line: 849, column: 7, scope: !3353)
!3355 = !DILocation(line: 849, column: 13, scope: !3353)
!3356 = !DILocation(line: 849, column: 7, scope: !3345)
!3357 = !DILocation(line: 850, column: 4, scope: !3353)
!3358 = !DILocation(line: 851, column: 10, scope: !3345)
!3359 = !DILocation(line: 851, column: 8, scope: !3345)
!3360 = !DILocation(line: 852, column: 17, scope: !3345)
!3361 = !DILocation(line: 852, column: 9, scope: !3345)
!3362 = !DILocation(line: 852, column: 7, scope: !3345)
!3363 = !DILocation(line: 854, column: 7, scope: !3364)
!3364 = distinct !DILexicalBlock(scope: !3345, file: !1, line: 854, column: 7)
!3365 = !DILocation(line: 854, column: 11, scope: !3364)
!3366 = !DILocation(line: 854, column: 16, scope: !3364)
!3367 = !DILocation(line: 854, column: 27, scope: !3368)
!3368 = !DILexicalBlockFile(scope: !3364, file: !1, discriminator: 1)
!3369 = !DILocation(line: 854, column: 19, scope: !3368)
!3370 = !DILocation(line: 854, column: 43, scope: !3368)
!3371 = !DILocation(line: 854, column: 7, scope: !3368)
!3372 = !DILocation(line: 855, column: 18, scope: !3373)
!3373 = distinct !DILexicalBlock(scope: !3364, file: !1, line: 854, column: 49)
!3374 = !DILocation(line: 855, column: 17, scope: !3373)
!3375 = !DILocation(line: 855, column: 4, scope: !3373)
!3376 = !DILocation(line: 856, column: 5, scope: !3373)
!3377 = !DILocation(line: 856, column: 12, scope: !3373)
!3378 = !DILocation(line: 857, column: 3, scope: !3373)
!3379 = !DILocation(line: 858, column: 18, scope: !3380)
!3380 = distinct !DILexicalBlock(scope: !3364, file: !1, line: 857, column: 10)
!3381 = !DILocation(line: 858, column: 26, scope: !3380)
!3382 = !DILocation(line: 858, column: 32, scope: !3380)
!3383 = !DILocation(line: 858, column: 4, scope: !3380)
!3384 = !DILocation(line: 861, column: 11, scope: !3345)
!3385 = !DILocation(line: 861, column: 8, scope: !3345)
!3386 = !DILocation(line: 847, column: 2, scope: !3387)
!3387 = !DILexicalBlockFile(scope: !3346, file: !1, discriminator: 1)
!3388 = !DILocation(line: 863, column: 1, scope: !402)
!3389 = !DILocalVariable(name: "src", arg: 1, scope: !387, file: !1, line: 1753, type: !95)
!3390 = !DILocation(line: 1753, column: 21, scope: !387)
!3391 = !DILocalVariable(name: "mentry", arg: 2, scope: !387, file: !1, line: 1753, type: !302)
!3392 = !DILocation(line: 1753, column: 46, scope: !387)
!3393 = !DILocalVariable(name: "dest", scope: !387, file: !1, line: 1755, type: !95)
!3394 = !DILocation(line: 1755, column: 8, scope: !387)
!3395 = !DILocation(line: 1755, column: 15, scope: !387)
!3396 = !DILocalVariable(name: "c", scope: !387, file: !1, line: 1756, type: !82)
!3397 = !DILocation(line: 1756, column: 7, scope: !387)
!3398 = !DILocation(line: 1758, column: 6, scope: !3399)
!3399 = distinct !DILexicalBlock(scope: !387, file: !1, line: 1758, column: 6)
!3400 = !DILocation(line: 1758, column: 13, scope: !3399)
!3401 = !DILocation(line: 1758, column: 21, scope: !3399)
!3402 = !DILocation(line: 1758, column: 31, scope: !3403)
!3403 = !DILexicalBlockFile(scope: !3399, file: !1, discriminator: 1)
!3404 = !DILocation(line: 1758, column: 24, scope: !3403)
!3405 = !DILocation(line: 1758, column: 41, scope: !3403)
!3406 = !DILocation(line: 1758, column: 6, scope: !3403)
!3407 = !DILocation(line: 1759, column: 3, scope: !3399)
!3408 = !DILocation(line: 1759, column: 11, scope: !3399)
!3409 = !DILocation(line: 1759, column: 16, scope: !3399)
!3410 = !DILocation(line: 1761, column: 2, scope: !387)
!3411 = !DILocation(line: 1761, column: 10, scope: !3412)
!3412 = !DILexicalBlockFile(scope: !387, file: !1, discriminator: 1)
!3413 = !DILocation(line: 1761, column: 9, scope: !3412)
!3414 = !DILocation(line: 1761, column: 14, scope: !3412)
!3415 = !DILocation(line: 1761, column: 2, scope: !3412)
!3416 = !DILocation(line: 1762, column: 11, scope: !3417)
!3417 = distinct !DILexicalBlock(scope: !387, file: !1, line: 1761, column: 23)
!3418 = !DILocation(line: 1762, column: 7, scope: !3417)
!3419 = !DILocation(line: 1762, column: 5, scope: !3417)
!3420 = !DILocation(line: 1763, column: 7, scope: !3421)
!3421 = distinct !DILexicalBlock(scope: !3417, file: !1, line: 1763, column: 7)
!3422 = !DILocation(line: 1763, column: 9, scope: !3421)
!3423 = !DILocation(line: 1763, column: 16, scope: !3421)
!3424 = !DILocation(line: 1763, column: 19, scope: !3425)
!3425 = !DILexicalBlockFile(scope: !3421, file: !1, discriminator: 1)
!3426 = !DILocation(line: 1763, column: 26, scope: !3425)
!3427 = !DILocation(line: 1763, column: 7, scope: !3425)
!3428 = !DILocation(line: 1764, column: 4, scope: !3421)
!3429 = !DILocation(line: 1764, column: 12, scope: !3421)
!3430 = !DILocation(line: 1764, column: 17, scope: !3421)
!3431 = !DILocation(line: 1765, column: 7, scope: !3432)
!3432 = distinct !DILexicalBlock(scope: !3417, file: !1, line: 1765, column: 7)
!3433 = !DILocation(line: 1765, column: 9, scope: !3432)
!3434 = !DILocation(line: 1765, column: 7, scope: !3417)
!3435 = !DILocation(line: 1766, column: 12, scope: !3436)
!3436 = distinct !DILexicalBlock(scope: !3432, file: !1, line: 1765, column: 18)
!3437 = !DILocation(line: 1766, column: 4, scope: !3436)
!3438 = !DILocation(line: 1768, column: 9, scope: !3439)
!3439 = distinct !DILexicalBlock(scope: !3440, file: !1, line: 1768, column: 9)
!3440 = distinct !DILexicalBlock(scope: !3436, file: !1, line: 1766, column: 20)
!3441 = !DILocation(line: 1768, column: 16, scope: !3439)
!3442 = !DILocation(line: 1768, column: 22, scope: !3439)
!3443 = !DILocation(line: 1768, column: 25, scope: !3444)
!3444 = !DILexicalBlockFile(scope: !3439, file: !1, discriminator: 1)
!3445 = !DILocation(line: 1768, column: 32, scope: !3444)
!3446 = !DILocation(line: 1768, column: 9, scope: !3444)
!3447 = !DILocation(line: 1769, column: 8, scope: !3448)
!3448 = distinct !DILexicalBlock(scope: !3439, file: !1, line: 1768, column: 39)
!3449 = !DILocation(line: 1770, column: 6, scope: !3448)
!3450 = !DILocation(line: 1771, column: 6, scope: !3448)
!3451 = !DILocation(line: 1768, column: 34, scope: !3452)
!3452 = !DILexicalBlockFile(scope: !3439, file: !1, discriminator: 2)
!3453 = !DILocation(line: 1777, column: 9, scope: !3454)
!3454 = distinct !DILexicalBlock(scope: !3440, file: !1, line: 1777, column: 9)
!3455 = !DILocation(line: 1777, column: 16, scope: !3454)
!3456 = !DILocation(line: 1777, column: 23, scope: !3454)
!3457 = !DILocation(line: 1777, column: 26, scope: !3458)
!3458 = !DILexicalBlockFile(scope: !3454, file: !1, discriminator: 1)
!3459 = !DILocation(line: 1777, column: 33, scope: !3458)
!3460 = !DILocation(line: 1777, column: 40, scope: !3458)
!3461 = !DILocation(line: 1778, column: 9, scope: !3454)
!3462 = !DILocation(line: 1778, column: 16, scope: !3454)
!3463 = !DILocation(line: 1778, column: 23, scope: !3454)
!3464 = !DILocation(line: 1778, column: 26, scope: !3458)
!3465 = !DILocation(line: 1778, column: 33, scope: !3458)
!3466 = !DILocation(line: 1777, column: 9, scope: !3467)
!3467 = !DILexicalBlockFile(scope: !3440, file: !1, discriminator: 2)
!3468 = !DILocation(line: 1779, column: 11, scope: !3469)
!3469 = distinct !DILexicalBlock(scope: !3454, file: !1, line: 1778, column: 41)
!3470 = !DILocation(line: 1779, column: 18, scope: !3469)
!3471 = !DILocation(line: 1779, column: 25, scope: !3469)
!3472 = !DILocation(line: 1779, column: 10, scope: !3469)
!3473 = !DILocation(line: 1779, column: 8, scope: !3469)
!3474 = !DILocation(line: 1780, column: 12, scope: !3469)
!3475 = !DILocation(line: 1780, column: 19, scope: !3469)
!3476 = !DILocation(line: 1780, column: 26, scope: !3469)
!3477 = !DILocation(line: 1780, column: 8, scope: !3469)
!3478 = !DILocation(line: 1781, column: 12, scope: !3469)
!3479 = !DILocation(line: 1781, column: 19, scope: !3469)
!3480 = !DILocation(line: 1781, column: 8, scope: !3469)
!3481 = !DILocation(line: 1782, column: 10, scope: !3469)
!3482 = !DILocation(line: 1783, column: 5, scope: !3469)
!3483 = !DILocation(line: 1784, column: 5, scope: !3440)
!3484 = !DILocation(line: 1786, column: 7, scope: !3440)
!3485 = !DILocation(line: 1787, column: 5, scope: !3440)
!3486 = !DILocation(line: 1788, column: 5, scope: !3440)
!3487 = !DILocation(line: 1790, column: 7, scope: !3440)
!3488 = !DILocation(line: 1791, column: 5, scope: !3440)
!3489 = !DILocation(line: 1792, column: 5, scope: !3440)
!3490 = !DILocation(line: 1794, column: 7, scope: !3440)
!3491 = !DILocation(line: 1795, column: 5, scope: !3440)
!3492 = !DILocation(line: 1796, column: 5, scope: !3440)
!3493 = !DILocation(line: 1798, column: 7, scope: !3440)
!3494 = !DILocation(line: 1799, column: 5, scope: !3440)
!3495 = !DILocation(line: 1800, column: 5, scope: !3440)
!3496 = !DILocation(line: 1802, column: 7, scope: !3440)
!3497 = !DILocation(line: 1803, column: 5, scope: !3440)
!3498 = !DILocation(line: 1804, column: 5, scope: !3440)
!3499 = !DILocation(line: 1806, column: 7, scope: !3440)
!3500 = !DILocation(line: 1807, column: 5, scope: !3440)
!3501 = !DILocation(line: 1808, column: 5, scope: !3440)
!3502 = !DILocation(line: 1810, column: 7, scope: !3440)
!3503 = !DILocation(line: 1811, column: 5, scope: !3440)
!3504 = !DILocation(line: 1812, column: 5, scope: !3440)
!3505 = !DILocation(line: 1814, column: 7, scope: !3440)
!3506 = !DILocation(line: 1815, column: 5, scope: !3440)
!3507 = !DILocation(line: 1816, column: 5, scope: !3440)
!3508 = !DILocation(line: 1818, column: 7, scope: !3440)
!3509 = !DILocation(line: 1819, column: 5, scope: !3440)
!3510 = !DILocation(line: 1820, column: 5, scope: !3440)
!3511 = !DILocation(line: 1822, column: 3, scope: !3436)
!3512 = !DILocation(line: 1823, column: 13, scope: !3417)
!3513 = !DILocation(line: 1823, column: 8, scope: !3417)
!3514 = !DILocation(line: 1823, column: 11, scope: !3417)
!3515 = !DILocation(line: 1761, column: 2, scope: !3516)
!3516 = !DILexicalBlockFile(scope: !387, file: !1, discriminator: 2)
!3517 = !DILocation(line: 1825, column: 3, scope: !387)
!3518 = !DILocation(line: 1825, column: 8, scope: !387)
!3519 = !DILocation(line: 1826, column: 1, scope: !387)
!3520 = !DILocalVariable(name: "p", arg: 1, scope: !390, file: !1, line: 2027, type: !80)
!3521 = !DILocation(line: 2027, column: 18, scope: !390)
!3522 = !DILocalVariable(name: "g", scope: !390, file: !1, line: 2031, type: !13)
!3523 = !DILocation(line: 2031, column: 11, scope: !390)
!3524 = !DILocalVariable(name: "h", scope: !390, file: !1, line: 2031, type: !13)
!3525 = !DILocation(line: 2031, column: 14, scope: !390)
!3526 = !DILocation(line: 2032, column: 2, scope: !390)
!3527 = !DILocation(line: 2032, column: 10, scope: !3528)
!3528 = !DILexicalBlockFile(scope: !390, file: !1, discriminator: 1)
!3529 = !DILocation(line: 2032, column: 9, scope: !3528)
!3530 = !DILocation(line: 2032, column: 12, scope: !3528)
!3531 = !DILocation(line: 2032, column: 2, scope: !3528)
!3532 = !DILocation(line: 2033, column: 8, scope: !3533)
!3533 = distinct !DILexicalBlock(scope: !390, file: !1, line: 2032, column: 21)
!3534 = !DILocation(line: 2033, column: 10, scope: !3533)
!3535 = !DILocation(line: 2033, column: 20, scope: !3533)
!3536 = !DILocation(line: 2033, column: 18, scope: !3533)
!3537 = !DILocation(line: 2033, column: 16, scope: !3533)
!3538 = !DILocation(line: 2033, column: 5, scope: !3533)
!3539 = !DILocation(line: 2034, column: 12, scope: !3540)
!3540 = distinct !DILexicalBlock(scope: !3533, file: !1, line: 2034, column: 7)
!3541 = !DILocation(line: 2034, column: 14, scope: !3540)
!3542 = !DILocation(line: 2034, column: 10, scope: !3540)
!3543 = !DILocation(line: 2034, column: 28, scope: !3540)
!3544 = !DILocation(line: 2034, column: 7, scope: !3533)
!3545 = !DILocation(line: 2035, column: 9, scope: !3546)
!3546 = distinct !DILexicalBlock(scope: !3540, file: !1, line: 2034, column: 34)
!3547 = !DILocation(line: 2035, column: 11, scope: !3546)
!3548 = !DILocation(line: 2035, column: 6, scope: !3546)
!3549 = !DILocation(line: 2036, column: 6, scope: !3546)
!3550 = !DILocation(line: 2037, column: 3, scope: !3546)
!3551 = !DILocation(line: 2032, column: 2, scope: !3552)
!3552 = !DILexicalBlockFile(scope: !390, file: !1, discriminator: 2)
!3553 = !DILocation(line: 2039, column: 9, scope: !390)
!3554 = !DILocation(line: 2039, column: 2, scope: !390)
!3555 = !DILocalVariable(name: "a", arg: 1, scope: !393, file: !1, line: 760, type: !4)
!3556 = !DILocation(line: 760, column: 33, scope: !393)
!3557 = !DILocalVariable(name: "global", arg: 2, scope: !393, file: !1, line: 760, type: !385)
!3558 = !DILocation(line: 760, column: 58, scope: !393)
!3559 = !DILocalVariable(name: "value", arg: 3, scope: !393, file: !1, line: 761, type: !80)
!3560 = !DILocation(line: 761, column: 17, scope: !393)
!3561 = !DILocalVariable(name: "len", arg: 4, scope: !393, file: !1, line: 761, type: !45)
!3562 = !DILocation(line: 761, column: 31, scope: !393)
!3563 = !DILocalVariable(name: "opt", scope: !393, file: !1, line: 763, type: !307)
!3564 = !DILocation(line: 763, column: 23, scope: !393)
!3565 = !DILocation(line: 765, column: 13, scope: !3566)
!3566 = distinct !DILexicalBlock(scope: !393, file: !1, line: 765, column: 6)
!3567 = !DILocation(line: 765, column: 11, scope: !3566)
!3568 = !DILocation(line: 765, column: 35, scope: !3566)
!3569 = !DILocation(line: 765, column: 6, scope: !393)
!3570 = !DILocation(line: 766, column: 22, scope: !3571)
!3571 = distinct !DILexicalBlock(scope: !3566, file: !1, line: 765, column: 44)
!3572 = !DILocation(line: 766, column: 25, scope: !3571)
!3573 = !DILocation(line: 766, column: 34, scope: !3571)
!3574 = !DILocation(line: 766, column: 3, scope: !3575)
!3575 = !DILexicalBlockFile(scope: !3571, file: !1, discriminator: 1)
!3576 = !DILocation(line: 767, column: 3, scope: !3571)
!3577 = !DILocation(line: 769, column: 27, scope: !3578)
!3578 = distinct !DILexicalBlock(scope: !393, file: !1, line: 769, column: 6)
!3579 = !DILocation(line: 769, column: 31, scope: !3578)
!3580 = !DILocation(line: 769, column: 20, scope: !3578)
!3581 = !DILocation(line: 769, column: 7, scope: !3578)
!3582 = !DILocation(line: 769, column: 12, scope: !3578)
!3583 = !DILocation(line: 769, column: 18, scope: !3578)
!3584 = !DILocation(line: 769, column: 37, scope: !3578)
!3585 = !DILocation(line: 769, column: 6, scope: !393)
!3586 = !DILocation(line: 770, column: 8, scope: !3587)
!3587 = distinct !DILexicalBlock(scope: !3578, file: !1, line: 769, column: 46)
!3588 = !DILocation(line: 770, column: 3, scope: !3587)
!3589 = !DILocation(line: 771, column: 22, scope: !3587)
!3590 = !DILocation(line: 771, column: 25, scope: !3587)
!3591 = !DILocation(line: 771, column: 34, scope: !3587)
!3592 = !DILocation(line: 771, column: 3, scope: !3593)
!3593 = !DILexicalBlockFile(scope: !3587, file: !1, discriminator: 1)
!3594 = !DILocation(line: 772, column: 3, scope: !3587)
!3595 = !DILocation(line: 774, column: 9, scope: !393)
!3596 = !DILocation(line: 774, column: 14, scope: !393)
!3597 = !DILocation(line: 774, column: 21, scope: !393)
!3598 = !DILocation(line: 774, column: 28, scope: !393)
!3599 = !DILocation(line: 774, column: 2, scope: !393)
!3600 = !DILocation(line: 775, column: 13, scope: !393)
!3601 = !DILocation(line: 775, column: 2, scope: !393)
!3602 = !DILocation(line: 775, column: 7, scope: !393)
!3603 = !DILocation(line: 775, column: 18, scope: !393)
!3604 = !DILocation(line: 776, column: 15, scope: !393)
!3605 = !DILocation(line: 776, column: 14, scope: !393)
!3606 = !DILocation(line: 776, column: 2, scope: !393)
!3607 = !DILocation(line: 776, column: 7, scope: !393)
!3608 = !DILocation(line: 776, column: 12, scope: !393)
!3609 = !DILocation(line: 777, column: 12, scope: !393)
!3610 = !DILocation(line: 777, column: 3, scope: !393)
!3611 = !DILocation(line: 777, column: 10, scope: !393)
!3612 = !DILocation(line: 778, column: 2, scope: !393)
!3613 = !DILocation(line: 779, column: 1, scope: !393)
!3614 = !DILocalVariable(name: "global", arg: 1, scope: !396, file: !1, line: 782, type: !385)
!3615 = !DILocation(line: 782, column: 37, scope: !396)
!3616 = !DILocalVariable(name: "value", arg: 2, scope: !396, file: !1, line: 782, type: !80)
!3617 = !DILocation(line: 782, column: 57, scope: !396)
!3618 = !DILocalVariable(name: "len", arg: 3, scope: !396, file: !1, line: 782, type: !45)
!3619 = !DILocation(line: 782, column: 71, scope: !396)
!3620 = !DILocalVariable(name: "iter", scope: !396, file: !1, line: 784, type: !307)
!3621 = !DILocation(line: 784, column: 23, scope: !396)
!3622 = !DILocalVariable(name: "last", scope: !396, file: !1, line: 784, type: !307)
!3623 = !DILocation(line: 784, column: 30, scope: !396)
!3624 = !DILocation(line: 786, column: 7, scope: !396)
!3625 = !DILocation(line: 787, column: 15, scope: !3626)
!3626 = distinct !DILexicalBlock(scope: !396, file: !1, line: 787, column: 2)
!3627 = !DILocation(line: 787, column: 14, scope: !3626)
!3628 = !DILocation(line: 787, column: 12, scope: !3626)
!3629 = !DILocation(line: 787, column: 7, scope: !3626)
!3630 = !DILocation(line: 787, column: 23, scope: !3631)
!3631 = !DILexicalBlockFile(scope: !3632, file: !1, discriminator: 1)
!3632 = distinct !DILexicalBlock(scope: !3626, file: !1, line: 787, column: 2)
!3633 = !DILocation(line: 787, column: 28, scope: !3631)
!3634 = !DILocation(line: 787, column: 2, scope: !3631)
!3635 = !DILocation(line: 788, column: 15, scope: !3636)
!3636 = distinct !DILexicalBlock(scope: !3637, file: !1, line: 788, column: 7)
!3637 = distinct !DILexicalBlock(scope: !3632, file: !1, line: 787, column: 69)
!3638 = !DILocation(line: 788, column: 21, scope: !3636)
!3639 = !DILocation(line: 788, column: 28, scope: !3636)
!3640 = !DILocation(line: 788, column: 35, scope: !3636)
!3641 = !DILocation(line: 788, column: 7, scope: !3636)
!3642 = !DILocation(line: 788, column: 40, scope: !3636)
!3643 = !DILocation(line: 788, column: 45, scope: !3636)
!3644 = !DILocation(line: 789, column: 20, scope: !3636)
!3645 = !DILocation(line: 789, column: 8, scope: !3636)
!3646 = !DILocation(line: 789, column: 14, scope: !3636)
!3647 = !DILocation(line: 789, column: 25, scope: !3636)
!3648 = !DILocation(line: 789, column: 33, scope: !3636)
!3649 = !DILocation(line: 790, column: 20, scope: !3636)
!3650 = !DILocation(line: 790, column: 8, scope: !3636)
!3651 = !DILocation(line: 790, column: 14, scope: !3636)
!3652 = !DILocation(line: 790, column: 25, scope: !3636)
!3653 = !DILocation(line: 788, column: 7, scope: !3654)
!3654 = !DILexicalBlockFile(scope: !3637, file: !1, discriminator: 1)
!3655 = !DILocation(line: 791, column: 4, scope: !3636)
!3656 = !DILocation(line: 792, column: 2, scope: !3637)
!3657 = !DILocation(line: 787, column: 44, scope: !3658)
!3658 = !DILexicalBlockFile(scope: !3632, file: !1, discriminator: 2)
!3659 = !DILocation(line: 787, column: 42, scope: !3658)
!3660 = !DILocation(line: 787, column: 57, scope: !3658)
!3661 = !DILocation(line: 787, column: 63, scope: !3658)
!3662 = !DILocation(line: 787, column: 55, scope: !3658)
!3663 = !DILocation(line: 787, column: 2, scope: !3658)
!3664 = !DILocation(line: 793, column: 6, scope: !3665)
!3665 = distinct !DILexicalBlock(scope: !396, file: !1, line: 793, column: 6)
!3666 = !DILocation(line: 793, column: 11, scope: !3665)
!3667 = !DILocation(line: 793, column: 6, scope: !396)
!3668 = !DILocation(line: 794, column: 3, scope: !3665)
!3669 = !DILocation(line: 795, column: 6, scope: !3670)
!3670 = distinct !DILexicalBlock(scope: !396, file: !1, line: 795, column: 6)
!3671 = !DILocation(line: 795, column: 11, scope: !3670)
!3672 = !DILocation(line: 795, column: 6, scope: !396)
!3673 = !DILocation(line: 796, column: 13, scope: !3670)
!3674 = !DILocation(line: 796, column: 19, scope: !3670)
!3675 = !DILocation(line: 796, column: 4, scope: !3670)
!3676 = !DILocation(line: 796, column: 11, scope: !3670)
!3677 = !DILocation(line: 796, column: 3, scope: !3670)
!3678 = !DILocation(line: 798, column: 16, scope: !3670)
!3679 = !DILocation(line: 798, column: 22, scope: !3670)
!3680 = !DILocation(line: 798, column: 3, scope: !3670)
!3681 = !DILocation(line: 798, column: 9, scope: !3670)
!3682 = !DILocation(line: 798, column: 14, scope: !3670)
!3683 = !DILocation(line: 800, column: 7, scope: !396)
!3684 = !DILocation(line: 800, column: 13, scope: !396)
!3685 = !DILocation(line: 800, column: 2, scope: !396)
!3686 = !DILocation(line: 801, column: 7, scope: !396)
!3687 = !DILocation(line: 801, column: 2, scope: !396)
!3688 = !DILocation(line: 802, column: 1, scope: !396)
!3689 = !DILocation(line: 802, column: 1, scope: !3690)
!3690 = !DILexicalBlockFile(scope: !396, file: !1, discriminator: 1)
!3691 = !DILocalVariable(name: "a", arg: 1, scope: !406, file: !1, line: 1344, type: !4)
!3692 = !DILocation(line: 1344, column: 33, scope: !406)
!3693 = !DILocalVariable(name: "entry", arg: 2, scope: !406, file: !1, line: 1344, type: !30)
!3694 = !DILocation(line: 1344, column: 58, scope: !406)
!3695 = !DILocalVariable(name: "mtree", arg: 3, scope: !406, file: !1, line: 1345, type: !291)
!3696 = !DILocation(line: 1345, column: 19, scope: !406)
!3697 = !DILocalVariable(name: "mp", arg: 4, scope: !406, file: !1, line: 1345, type: !302)
!3698 = !DILocation(line: 1345, column: 46, scope: !406)
!3699 = !DILocalVariable(name: "parsed_kws", arg: 5, scope: !406, file: !1, line: 1345, type: !353)
!3700 = !DILocation(line: 1345, column: 55, scope: !406)
!3701 = !DILocalVariable(name: "iter", scope: !406, file: !1, line: 1347, type: !307)
!3702 = !DILocation(line: 1347, column: 23, scope: !406)
!3703 = !DILocalVariable(name: "r", scope: !406, file: !1, line: 1348, type: !23)
!3704 = !DILocation(line: 1348, column: 6, scope: !406)
!3705 = !DILocalVariable(name: "r1", scope: !406, file: !1, line: 1348, type: !23)
!3706 = !DILocation(line: 1348, column: 22, scope: !406)
!3707 = !DILocation(line: 1350, column: 14, scope: !3708)
!3708 = distinct !DILexicalBlock(scope: !406, file: !1, line: 1350, column: 2)
!3709 = !DILocation(line: 1350, column: 18, scope: !3708)
!3710 = !DILocation(line: 1350, column: 12, scope: !3708)
!3711 = !DILocation(line: 1350, column: 7, scope: !3708)
!3712 = !DILocation(line: 1350, column: 27, scope: !3713)
!3713 = !DILexicalBlockFile(scope: !3714, file: !1, discriminator: 1)
!3714 = distinct !DILexicalBlock(scope: !3708, file: !1, line: 1350, column: 2)
!3715 = !DILocation(line: 1350, column: 32, scope: !3713)
!3716 = !DILocation(line: 1350, column: 2, scope: !3713)
!3717 = !DILocation(line: 1351, column: 22, scope: !3718)
!3718 = distinct !DILexicalBlock(scope: !3714, file: !1, line: 1350, column: 60)
!3719 = !DILocation(line: 1351, column: 25, scope: !3718)
!3720 = !DILocation(line: 1351, column: 32, scope: !3718)
!3721 = !DILocation(line: 1351, column: 39, scope: !3718)
!3722 = !DILocation(line: 1351, column: 45, scope: !3718)
!3723 = !DILocation(line: 1351, column: 8, scope: !3718)
!3724 = !DILocation(line: 1351, column: 6, scope: !3718)
!3725 = !DILocation(line: 1352, column: 7, scope: !3726)
!3726 = distinct !DILexicalBlock(scope: !3718, file: !1, line: 1352, column: 7)
!3727 = !DILocation(line: 1352, column: 12, scope: !3726)
!3728 = !DILocation(line: 1352, column: 10, scope: !3726)
!3729 = !DILocation(line: 1352, column: 7, scope: !3718)
!3730 = !DILocation(line: 1353, column: 8, scope: !3726)
!3731 = !DILocation(line: 1353, column: 6, scope: !3726)
!3732 = !DILocation(line: 1353, column: 4, scope: !3726)
!3733 = !DILocation(line: 1354, column: 2, scope: !3718)
!3734 = !DILocation(line: 1350, column: 48, scope: !3735)
!3735 = !DILexicalBlockFile(scope: !3714, file: !1, discriminator: 2)
!3736 = !DILocation(line: 1350, column: 54, scope: !3735)
!3737 = !DILocation(line: 1350, column: 46, scope: !3735)
!3738 = !DILocation(line: 1350, column: 2, scope: !3735)
!3739 = !DILocation(line: 1355, column: 6, scope: !3740)
!3740 = distinct !DILexicalBlock(scope: !406, file: !1, line: 1355, column: 6)
!3741 = !DILocation(line: 1355, column: 8, scope: !3740)
!3742 = !DILocation(line: 1355, column: 22, scope: !3740)
!3743 = !DILocation(line: 1355, column: 27, scope: !3744)
!3744 = !DILexicalBlockFile(scope: !3740, file: !1, discriminator: 1)
!3745 = !DILocation(line: 1355, column: 26, scope: !3744)
!3746 = !DILocation(line: 1355, column: 38, scope: !3744)
!3747 = !DILocation(line: 1355, column: 56, scope: !3744)
!3748 = !DILocation(line: 1355, column: 6, scope: !3744)
!3749 = !DILocation(line: 1356, column: 22, scope: !3750)
!3750 = distinct !DILexicalBlock(scope: !3740, file: !1, line: 1355, column: 62)
!3751 = !DILocation(line: 1356, column: 25, scope: !3750)
!3752 = !DILocation(line: 1356, column: 3, scope: !3750)
!3753 = !DILocation(line: 1358, column: 3, scope: !3750)
!3754 = !DILocation(line: 1360, column: 10, scope: !406)
!3755 = !DILocation(line: 1360, column: 2, scope: !406)
!3756 = !DILocation(line: 1361, column: 1, scope: !406)
!3757 = !DILocalVariable(name: "a", arg: 1, scope: !407, file: !1, line: 1447, type: !4)
!3758 = !DILocation(line: 1447, column: 36, scope: !407)
!3759 = !DILocalVariable(name: "mtree", arg: 2, scope: !407, file: !1, line: 1447, type: !291)
!3760 = !DILocation(line: 1447, column: 53, scope: !407)
!3761 = !DILocalVariable(name: "entry", arg: 3, scope: !407, file: !1, line: 1448, type: !30)
!3762 = !DILocation(line: 1448, column: 27, scope: !407)
!3763 = !DILocalVariable(name: "opt", arg: 4, scope: !407, file: !1, line: 1448, type: !307)
!3764 = !DILocation(line: 1448, column: 55, scope: !407)
!3765 = !DILocalVariable(name: "parsed_kws", arg: 5, scope: !407, file: !1, line: 1448, type: !353)
!3766 = !DILocation(line: 1448, column: 65, scope: !407)
!3767 = !DILocalVariable(name: "val", scope: !407, file: !1, line: 1450, type: !95)
!3768 = !DILocation(line: 1450, column: 8, scope: !407)
!3769 = !DILocalVariable(name: "key", scope: !407, file: !1, line: 1450, type: !95)
!3770 = !DILocation(line: 1450, column: 14, scope: !407)
!3771 = !DILocation(line: 1452, column: 8, scope: !407)
!3772 = !DILocation(line: 1452, column: 13, scope: !407)
!3773 = !DILocation(line: 1452, column: 6, scope: !407)
!3774 = !DILocation(line: 1454, column: 7, scope: !3775)
!3775 = distinct !DILexicalBlock(scope: !407, file: !1, line: 1454, column: 6)
!3776 = !DILocation(line: 1454, column: 6, scope: !3775)
!3777 = !DILocation(line: 1454, column: 11, scope: !3775)
!3778 = !DILocation(line: 1454, column: 6, scope: !407)
!3779 = !DILocation(line: 1455, column: 3, scope: !3775)
!3780 = !DILocation(line: 1457, column: 13, scope: !3781)
!3781 = distinct !DILexicalBlock(scope: !407, file: !1, line: 1457, column: 6)
!3782 = !DILocation(line: 1457, column: 6, scope: !3781)
!3783 = !DILocation(line: 1457, column: 30, scope: !3781)
!3784 = !DILocation(line: 1457, column: 6, scope: !407)
!3785 = !DILocation(line: 1458, column: 4, scope: !3786)
!3786 = distinct !DILexicalBlock(scope: !3781, file: !1, line: 1457, column: 36)
!3787 = !DILocation(line: 1458, column: 15, scope: !3786)
!3788 = !DILocation(line: 1459, column: 3, scope: !3786)
!3789 = !DILocation(line: 1461, column: 13, scope: !3790)
!3790 = distinct !DILexicalBlock(scope: !407, file: !1, line: 1461, column: 6)
!3791 = !DILocation(line: 1461, column: 6, scope: !3790)
!3792 = !DILocation(line: 1461, column: 30, scope: !3790)
!3793 = !DILocation(line: 1461, column: 6, scope: !407)
!3794 = !DILocation(line: 1462, column: 4, scope: !3795)
!3795 = distinct !DILexicalBlock(scope: !3790, file: !1, line: 1461, column: 36)
!3796 = !DILocation(line: 1462, column: 15, scope: !3795)
!3797 = !DILocation(line: 1463, column: 3, scope: !3795)
!3798 = !DILocation(line: 1465, column: 13, scope: !3799)
!3799 = distinct !DILexicalBlock(scope: !407, file: !1, line: 1465, column: 6)
!3800 = !DILocation(line: 1465, column: 6, scope: !3799)
!3801 = !DILocation(line: 1465, column: 28, scope: !3799)
!3802 = !DILocation(line: 1465, column: 6, scope: !407)
!3803 = !DILocation(line: 1471, column: 3, scope: !3804)
!3804 = distinct !DILexicalBlock(scope: !3799, file: !1, line: 1465, column: 34)
!3805 = !DILocation(line: 1474, column: 15, scope: !407)
!3806 = !DILocation(line: 1474, column: 8, scope: !407)
!3807 = !DILocation(line: 1474, column: 6, scope: !407)
!3808 = !DILocation(line: 1475, column: 6, scope: !3809)
!3809 = distinct !DILexicalBlock(scope: !407, file: !1, line: 1475, column: 6)
!3810 = !DILocation(line: 1475, column: 10, scope: !3809)
!3811 = !DILocation(line: 1475, column: 6, scope: !407)
!3812 = !DILocation(line: 1476, column: 22, scope: !3813)
!3813 = distinct !DILexicalBlock(scope: !3809, file: !1, line: 1475, column: 19)
!3814 = !DILocation(line: 1476, column: 25, scope: !3813)
!3815 = !DILocation(line: 1477, column: 42, scope: !3813)
!3816 = !DILocation(line: 1477, column: 47, scope: !3813)
!3817 = !DILocation(line: 1476, column: 3, scope: !3813)
!3818 = !DILocation(line: 1478, column: 3, scope: !3813)
!3819 = !DILocation(line: 1481, column: 3, scope: !407)
!3820 = !DILocation(line: 1481, column: 7, scope: !407)
!3821 = !DILocation(line: 1482, column: 2, scope: !407)
!3822 = !DILocation(line: 1484, column: 10, scope: !407)
!3823 = !DILocation(line: 1484, column: 2, scope: !407)
!3824 = !DILocation(line: 1486, column: 14, scope: !3825)
!3825 = distinct !DILexicalBlock(scope: !3826, file: !1, line: 1486, column: 7)
!3826 = distinct !DILexicalBlock(scope: !407, file: !1, line: 1484, column: 18)
!3827 = !DILocation(line: 1486, column: 7, scope: !3825)
!3828 = !DILocation(line: 1486, column: 30, scope: !3825)
!3829 = !DILocation(line: 1487, column: 7, scope: !3825)
!3830 = !DILocation(line: 1487, column: 17, scope: !3831)
!3831 = !DILexicalBlockFile(scope: !3825, file: !1, discriminator: 1)
!3832 = !DILocation(line: 1487, column: 10, scope: !3831)
!3833 = !DILocation(line: 1487, column: 34, scope: !3831)
!3834 = !DILocation(line: 1486, column: 7, scope: !3835)
!3835 = !DILexicalBlockFile(scope: !3826, file: !1, discriminator: 1)
!3836 = !DILocation(line: 1488, column: 18, scope: !3837)
!3837 = distinct !DILexicalBlock(scope: !3825, file: !1, line: 1487, column: 40)
!3838 = !DILocation(line: 1488, column: 4, scope: !3837)
!3839 = !DILocation(line: 1489, column: 4, scope: !3837)
!3840 = !DILocation(line: 1489, column: 4, scope: !3841)
!3841 = !DILexicalBlockFile(scope: !3837, file: !1, discriminator: 1)
!3842 = !DILocation(line: 1489, column: 4, scope: !3843)
!3843 = !DILexicalBlockFile(scope: !3837, file: !1, discriminator: 2)
!3844 = !DILocation(line: 1489, column: 4, scope: !3845)
!3845 = !DILexicalBlockFile(scope: !3837, file: !1, discriminator: 3)
!3846 = !DILocation(line: 1490, column: 4, scope: !3837)
!3847 = !DILocation(line: 1492, column: 14, scope: !3848)
!3848 = distinct !DILexicalBlock(scope: !3826, file: !1, line: 1492, column: 7)
!3849 = !DILocation(line: 1492, column: 7, scope: !3848)
!3850 = !DILocation(line: 1492, column: 28, scope: !3848)
!3851 = !DILocation(line: 1492, column: 7, scope: !3826)
!3852 = !DILocation(line: 1493, column: 4, scope: !3848)
!3853 = !DILocation(line: 1492, column: 31, scope: !3854)
!3854 = !DILexicalBlockFile(scope: !3848, file: !1, discriminator: 1)
!3855 = !DILocation(line: 1495, column: 14, scope: !3856)
!3856 = distinct !DILexicalBlock(scope: !3826, file: !1, line: 1495, column: 7)
!3857 = !DILocation(line: 1495, column: 7, scope: !3856)
!3858 = !DILocation(line: 1495, column: 29, scope: !3856)
!3859 = !DILocation(line: 1495, column: 7, scope: !3826)
!3860 = !DILocalVariable(name: "r", scope: !3861, file: !1, line: 1498, type: !23)
!3861 = distinct !DILexicalBlock(scope: !3856, file: !1, line: 1495, column: 35)
!3862 = !DILocation(line: 1498, column: 8, scope: !3861)
!3863 = !DILocalVariable(name: "dev", scope: !3861, file: !1, line: 1499, type: !339)
!3864 = !DILocation(line: 1499, column: 10, scope: !3861)
!3865 = !DILocation(line: 1501, column: 5, scope: !3861)
!3866 = !DILocation(line: 1501, column: 16, scope: !3861)
!3867 = !DILocation(line: 1502, column: 28, scope: !3861)
!3868 = !DILocation(line: 1502, column: 31, scope: !3861)
!3869 = !DILocation(line: 1502, column: 40, scope: !3861)
!3870 = !DILocation(line: 1502, column: 8, scope: !3861)
!3871 = !DILocation(line: 1502, column: 6, scope: !3861)
!3872 = !DILocation(line: 1503, column: 8, scope: !3873)
!3873 = distinct !DILexicalBlock(scope: !3861, file: !1, line: 1503, column: 8)
!3874 = !DILocation(line: 1503, column: 10, scope: !3873)
!3875 = !DILocation(line: 1503, column: 8, scope: !3861)
!3876 = !DILocation(line: 1504, column: 28, scope: !3873)
!3877 = !DILocation(line: 1504, column: 35, scope: !3873)
!3878 = !DILocation(line: 1504, column: 5, scope: !3873)
!3879 = !DILocation(line: 1505, column: 11, scope: !3861)
!3880 = !DILocation(line: 1505, column: 4, scope: !3861)
!3881 = !DILocation(line: 1495, column: 32, scope: !3882)
!3882 = !DILexicalBlockFile(scope: !3856, file: !1, discriminator: 1)
!3883 = !DILocation(line: 1508, column: 14, scope: !3884)
!3884 = distinct !DILexicalBlock(scope: !3826, file: !1, line: 1508, column: 7)
!3885 = !DILocation(line: 1508, column: 7, scope: !3884)
!3886 = !DILocation(line: 1508, column: 28, scope: !3884)
!3887 = !DILocation(line: 1508, column: 7, scope: !3826)
!3888 = !DILocation(line: 1509, column: 5, scope: !3889)
!3889 = distinct !DILexicalBlock(scope: !3884, file: !1, line: 1508, column: 34)
!3890 = !DILocation(line: 1509, column: 16, scope: !3889)
!3891 = !DILocation(line: 1510, column: 35, scope: !3889)
!3892 = !DILocation(line: 1510, column: 42, scope: !3889)
!3893 = !DILocation(line: 1510, column: 4, scope: !3889)
!3894 = !DILocation(line: 1511, column: 4, scope: !3889)
!3895 = !DILocation(line: 1508, column: 31, scope: !3896)
!3896 = !DILexicalBlockFile(scope: !3884, file: !1, discriminator: 1)
!3897 = !DILocation(line: 1514, column: 14, scope: !3898)
!3898 = distinct !DILexicalBlock(scope: !3826, file: !1, line: 1514, column: 7)
!3899 = !DILocation(line: 1514, column: 7, scope: !3898)
!3900 = !DILocation(line: 1514, column: 26, scope: !3898)
!3901 = !DILocation(line: 1514, column: 7, scope: !3826)
!3902 = !DILocation(line: 1515, column: 5, scope: !3903)
!3903 = distinct !DILexicalBlock(scope: !3898, file: !1, line: 1514, column: 32)
!3904 = !DILocation(line: 1515, column: 16, scope: !3903)
!3905 = !DILocation(line: 1516, column: 26, scope: !3903)
!3906 = !DILocation(line: 1516, column: 33, scope: !3903)
!3907 = !DILocation(line: 1516, column: 4, scope: !3908)
!3908 = !DILexicalBlockFile(scope: !3903, file: !1, discriminator: 1)
!3909 = !DILocation(line: 1517, column: 4, scope: !3903)
!3910 = !DILocation(line: 1519, column: 14, scope: !3911)
!3911 = distinct !DILexicalBlock(scope: !3826, file: !1, line: 1519, column: 7)
!3912 = !DILocation(line: 1519, column: 7, scope: !3911)
!3913 = !DILocation(line: 1519, column: 28, scope: !3911)
!3914 = !DILocation(line: 1519, column: 7, scope: !3826)
!3915 = !DILocation(line: 1520, column: 5, scope: !3916)
!3916 = distinct !DILexicalBlock(scope: !3911, file: !1, line: 1519, column: 34)
!3917 = !DILocation(line: 1520, column: 16, scope: !3916)
!3918 = !DILocation(line: 1521, column: 29, scope: !3916)
!3919 = !DILocation(line: 1521, column: 36, scope: !3916)
!3920 = !DILocation(line: 1521, column: 4, scope: !3916)
!3921 = !DILocation(line: 1522, column: 4, scope: !3916)
!3922 = !DILocation(line: 1519, column: 31, scope: !3923)
!3923 = !DILexicalBlockFile(scope: !3911, file: !1, discriminator: 1)
!3924 = !DILocation(line: 1525, column: 14, scope: !3925)
!3925 = distinct !DILexicalBlock(scope: !3826, file: !1, line: 1525, column: 7)
!3926 = !DILocation(line: 1525, column: 7, scope: !3925)
!3927 = !DILocation(line: 1525, column: 28, scope: !3925)
!3928 = !DILocation(line: 1525, column: 7, scope: !3826)
!3929 = !DILocation(line: 1526, column: 26, scope: !3930)
!3930 = distinct !DILexicalBlock(scope: !3925, file: !1, line: 1525, column: 34)
!3931 = !DILocation(line: 1526, column: 33, scope: !3930)
!3932 = !DILocation(line: 1526, column: 4, scope: !3933)
!3933 = !DILexicalBlockFile(scope: !3930, file: !1, discriminator: 1)
!3934 = !DILocation(line: 1527, column: 4, scope: !3930)
!3935 = !DILocation(line: 1525, column: 31, scope: !3936)
!3936 = !DILexicalBlockFile(scope: !3925, file: !1, discriminator: 1)
!3937 = !DILocation(line: 1530, column: 14, scope: !3938)
!3938 = distinct !DILexicalBlock(scope: !3826, file: !1, line: 1530, column: 7)
!3939 = !DILocation(line: 1530, column: 7, scope: !3938)
!3940 = !DILocation(line: 1530, column: 27, scope: !3938)
!3941 = !DILocation(line: 1530, column: 7, scope: !3826)
!3942 = !DILocation(line: 1531, column: 31, scope: !3943)
!3943 = distinct !DILexicalBlock(scope: !3938, file: !1, line: 1530, column: 33)
!3944 = !DILocation(line: 1531, column: 38, scope: !3943)
!3945 = !DILocation(line: 1531, column: 4, scope: !3943)
!3946 = !DILocation(line: 1532, column: 4, scope: !3943)
!3947 = !DILocation(line: 1530, column: 30, scope: !3948)
!3948 = !DILexicalBlockFile(scope: !3938, file: !1, discriminator: 1)
!3949 = !DILocation(line: 1535, column: 14, scope: !3950)
!3950 = distinct !DILexicalBlock(scope: !3826, file: !1, line: 1535, column: 7)
!3951 = !DILocation(line: 1535, column: 7, scope: !3950)
!3952 = !DILocation(line: 1535, column: 26, scope: !3950)
!3953 = !DILocation(line: 1535, column: 31, scope: !3950)
!3954 = !DILocation(line: 1535, column: 41, scope: !3955)
!3955 = !DILexicalBlockFile(scope: !3950, file: !1, discriminator: 1)
!3956 = !DILocation(line: 1535, column: 34, scope: !3955)
!3957 = !DILocation(line: 1535, column: 59, scope: !3955)
!3958 = !DILocation(line: 1535, column: 7, scope: !3955)
!3959 = !DILocation(line: 1536, column: 4, scope: !3950)
!3960 = !DILocation(line: 1537, column: 14, scope: !3961)
!3961 = distinct !DILexicalBlock(scope: !3826, file: !1, line: 1537, column: 7)
!3962 = !DILocation(line: 1537, column: 7, scope: !3961)
!3963 = !DILocation(line: 1537, column: 27, scope: !3961)
!3964 = !DILocation(line: 1537, column: 7, scope: !3826)
!3965 = !DILocation(line: 1538, column: 8, scope: !3966)
!3966 = distinct !DILexicalBlock(scope: !3967, file: !1, line: 1538, column: 8)
!3967 = distinct !DILexicalBlock(scope: !3961, file: !1, line: 1537, column: 33)
!3968 = !DILocation(line: 1538, column: 15, scope: !3966)
!3969 = !DILocation(line: 1538, column: 22, scope: !3966)
!3970 = !DILocation(line: 1538, column: 25, scope: !3971)
!3971 = !DILexicalBlockFile(scope: !3966, file: !1, discriminator: 1)
!3972 = !DILocation(line: 1538, column: 32, scope: !3971)
!3973 = !DILocation(line: 1538, column: 8, scope: !3971)
!3974 = !DILocation(line: 1539, column: 6, scope: !3975)
!3975 = distinct !DILexicalBlock(scope: !3966, file: !1, line: 1538, column: 40)
!3976 = !DILocation(line: 1539, column: 17, scope: !3975)
!3977 = !DILocation(line: 1540, column: 28, scope: !3975)
!3978 = !DILocation(line: 1541, column: 17, scope: !3975)
!3979 = !DILocation(line: 1541, column: 9, scope: !3975)
!3980 = !DILocation(line: 1540, column: 5, scope: !3975)
!3981 = !DILocation(line: 1542, column: 4, scope: !3975)
!3982 = !DILocation(line: 1543, column: 24, scope: !3983)
!3983 = distinct !DILexicalBlock(scope: !3966, file: !1, line: 1542, column: 11)
!3984 = !DILocation(line: 1543, column: 27, scope: !3983)
!3985 = !DILocation(line: 1545, column: 45, scope: !3983)
!3986 = !DILocation(line: 1543, column: 5, scope: !3983)
!3987 = !DILocation(line: 1546, column: 5, scope: !3983)
!3988 = !DILocation(line: 1548, column: 4, scope: !3967)
!3989 = !DILocation(line: 1537, column: 30, scope: !3990)
!3990 = !DILexicalBlockFile(scope: !3961, file: !1, discriminator: 1)
!3991 = !DILocation(line: 1551, column: 14, scope: !3992)
!3992 = distinct !DILexicalBlock(scope: !3826, file: !1, line: 1551, column: 7)
!3993 = !DILocation(line: 1551, column: 7, scope: !3992)
!3994 = !DILocation(line: 1551, column: 28, scope: !3992)
!3995 = !DILocation(line: 1551, column: 7, scope: !3826)
!3996 = !DILocation(line: 1552, column: 5, scope: !3997)
!3997 = distinct !DILexicalBlock(scope: !3992, file: !1, line: 1551, column: 34)
!3998 = !DILocation(line: 1552, column: 16, scope: !3997)
!3999 = !DILocation(line: 1553, column: 28, scope: !3997)
!4000 = !DILocation(line: 1554, column: 19, scope: !3997)
!4001 = !DILocation(line: 1554, column: 5, scope: !3997)
!4002 = !DILocation(line: 1553, column: 4, scope: !3997)
!4003 = !DILocation(line: 1555, column: 4, scope: !3997)
!4004 = !DILocation(line: 1551, column: 31, scope: !4005)
!4005 = !DILexicalBlockFile(scope: !3992, file: !1, discriminator: 1)
!4006 = !DILocation(line: 1558, column: 14, scope: !4007)
!4007 = distinct !DILexicalBlock(scope: !3826, file: !1, line: 1558, column: 7)
!4008 = !DILocation(line: 1558, column: 7, scope: !4007)
!4009 = !DILocation(line: 1558, column: 32, scope: !4007)
!4010 = !DILocation(line: 1558, column: 7, scope: !3826)
!4011 = !DILocalVariable(name: "r", scope: !4012, file: !1, line: 1561, type: !23)
!4012 = distinct !DILexicalBlock(scope: !4007, file: !1, line: 1558, column: 38)
!4013 = !DILocation(line: 1561, column: 8, scope: !4012)
!4014 = !DILocalVariable(name: "dev", scope: !4012, file: !1, line: 1562, type: !339)
!4015 = !DILocation(line: 1562, column: 10, scope: !4012)
!4016 = !DILocation(line: 1564, column: 28, scope: !4012)
!4017 = !DILocation(line: 1564, column: 31, scope: !4012)
!4018 = !DILocation(line: 1564, column: 40, scope: !4012)
!4019 = !DILocation(line: 1564, column: 8, scope: !4012)
!4020 = !DILocation(line: 1564, column: 6, scope: !4012)
!4021 = !DILocation(line: 1565, column: 8, scope: !4022)
!4022 = distinct !DILexicalBlock(scope: !4012, file: !1, line: 1565, column: 8)
!4023 = !DILocation(line: 1565, column: 10, scope: !4022)
!4024 = !DILocation(line: 1565, column: 8, scope: !4012)
!4025 = !DILocation(line: 1566, column: 27, scope: !4022)
!4026 = !DILocation(line: 1566, column: 34, scope: !4022)
!4027 = !DILocation(line: 1566, column: 5, scope: !4022)
!4028 = !DILocation(line: 1567, column: 11, scope: !4012)
!4029 = !DILocation(line: 1567, column: 4, scope: !4012)
!4030 = !DILocation(line: 1569, column: 14, scope: !4031)
!4031 = distinct !DILexicalBlock(scope: !3826, file: !1, line: 1569, column: 7)
!4032 = !DILocation(line: 1569, column: 7, scope: !4031)
!4033 = !DILocation(line: 1569, column: 29, scope: !4031)
!4034 = !DILocation(line: 1569, column: 34, scope: !4031)
!4035 = !DILocation(line: 1570, column: 14, scope: !4031)
!4036 = !DILocation(line: 1570, column: 7, scope: !4031)
!4037 = !DILocation(line: 1570, column: 35, scope: !4031)
!4038 = !DILocation(line: 1569, column: 7, scope: !3835)
!4039 = !DILocation(line: 1571, column: 4, scope: !4031)
!4040 = !DILocation(line: 1570, column: 38, scope: !4041)
!4041 = !DILexicalBlockFile(scope: !4031, file: !1, discriminator: 1)
!4042 = !DILocation(line: 1573, column: 14, scope: !4043)
!4043 = distinct !DILexicalBlock(scope: !3826, file: !1, line: 1573, column: 7)
!4044 = !DILocation(line: 1573, column: 7, scope: !4043)
!4045 = !DILocation(line: 1573, column: 27, scope: !4043)
!4046 = !DILocation(line: 1573, column: 32, scope: !4043)
!4047 = !DILocation(line: 1573, column: 42, scope: !4048)
!4048 = !DILexicalBlockFile(scope: !4043, file: !1, discriminator: 1)
!4049 = !DILocation(line: 1573, column: 35, scope: !4048)
!4050 = !DILocation(line: 1573, column: 61, scope: !4048)
!4051 = !DILocation(line: 1573, column: 7, scope: !4048)
!4052 = !DILocation(line: 1574, column: 4, scope: !4043)
!4053 = !DILocation(line: 1575, column: 14, scope: !4054)
!4054 = distinct !DILexicalBlock(scope: !3826, file: !1, line: 1575, column: 7)
!4055 = !DILocation(line: 1575, column: 7, scope: !4054)
!4056 = !DILocation(line: 1575, column: 29, scope: !4054)
!4057 = !DILocation(line: 1575, column: 34, scope: !4054)
!4058 = !DILocation(line: 1576, column: 14, scope: !4054)
!4059 = !DILocation(line: 1576, column: 7, scope: !4054)
!4060 = !DILocation(line: 1576, column: 35, scope: !4054)
!4061 = !DILocation(line: 1575, column: 7, scope: !3835)
!4062 = !DILocation(line: 1577, column: 4, scope: !4054)
!4063 = !DILocation(line: 1578, column: 14, scope: !4064)
!4064 = distinct !DILexicalBlock(scope: !3826, file: !1, line: 1578, column: 7)
!4065 = !DILocation(line: 1578, column: 7, scope: !4064)
!4066 = !DILocation(line: 1578, column: 29, scope: !4064)
!4067 = !DILocation(line: 1578, column: 34, scope: !4064)
!4068 = !DILocation(line: 1579, column: 14, scope: !4064)
!4069 = !DILocation(line: 1579, column: 7, scope: !4064)
!4070 = !DILocation(line: 1579, column: 35, scope: !4064)
!4071 = !DILocation(line: 1578, column: 7, scope: !3835)
!4072 = !DILocation(line: 1580, column: 4, scope: !4064)
!4073 = !DILocation(line: 1581, column: 14, scope: !4074)
!4074 = distinct !DILexicalBlock(scope: !3826, file: !1, line: 1581, column: 7)
!4075 = !DILocation(line: 1581, column: 7, scope: !4074)
!4076 = !DILocation(line: 1581, column: 29, scope: !4074)
!4077 = !DILocation(line: 1581, column: 34, scope: !4074)
!4078 = !DILocation(line: 1582, column: 14, scope: !4074)
!4079 = !DILocation(line: 1582, column: 7, scope: !4074)
!4080 = !DILocation(line: 1582, column: 35, scope: !4074)
!4081 = !DILocation(line: 1581, column: 7, scope: !3835)
!4082 = !DILocation(line: 1583, column: 4, scope: !4074)
!4083 = !DILocation(line: 1584, column: 14, scope: !4084)
!4084 = distinct !DILexicalBlock(scope: !3826, file: !1, line: 1584, column: 7)
!4085 = !DILocation(line: 1584, column: 7, scope: !4084)
!4086 = !DILocation(line: 1584, column: 27, scope: !4084)
!4087 = !DILocation(line: 1584, column: 7, scope: !3826)
!4088 = !DILocation(line: 1585, column: 27, scope: !4089)
!4089 = distinct !DILexicalBlock(scope: !4084, file: !1, line: 1584, column: 33)
!4090 = !DILocation(line: 1585, column: 34, scope: !4089)
!4091 = !DILocation(line: 1585, column: 4, scope: !4092)
!4092 = !DILexicalBlockFile(scope: !4089, file: !1, discriminator: 1)
!4093 = !DILocation(line: 1586, column: 4, scope: !4089)
!4094 = !DILocation(line: 1584, column: 30, scope: !4095)
!4095 = !DILexicalBlockFile(scope: !4084, file: !1, discriminator: 1)
!4096 = !DILocation(line: 1589, column: 14, scope: !4097)
!4097 = distinct !DILexicalBlock(scope: !3826, file: !1, line: 1589, column: 7)
!4098 = !DILocation(line: 1589, column: 7, scope: !4097)
!4099 = !DILocation(line: 1589, column: 27, scope: !4097)
!4100 = !DILocation(line: 1589, column: 7, scope: !3826)
!4101 = !DILocation(line: 1595, column: 4, scope: !4102)
!4102 = distinct !DILexicalBlock(scope: !4097, file: !1, line: 1589, column: 33)
!4103 = !DILocation(line: 1597, column: 14, scope: !4104)
!4104 = distinct !DILexicalBlock(scope: !3826, file: !1, line: 1597, column: 7)
!4105 = !DILocation(line: 1597, column: 7, scope: !4104)
!4106 = !DILocation(line: 1597, column: 27, scope: !4104)
!4107 = !DILocation(line: 1597, column: 7, scope: !3826)
!4108 = !DILocalVariable(name: "m", scope: !4109, file: !1, line: 1598, type: !52)
!4109 = distinct !DILexicalBlock(scope: !4104, file: !1, line: 1597, column: 33)
!4110 = !DILocation(line: 1598, column: 12, scope: !4109)
!4111 = !DILocalVariable(name: "my_time_t_max", scope: !4109, file: !1, line: 1599, type: !52)
!4112 = !DILocation(line: 1599, column: 12, scope: !4109)
!4113 = !DILocation(line: 1599, column: 28, scope: !4109)
!4114 = !DILocalVariable(name: "my_time_t_min", scope: !4109, file: !1, line: 1600, type: !52)
!4115 = !DILocation(line: 1600, column: 12, scope: !4109)
!4116 = !DILocation(line: 1600, column: 28, scope: !4109)
!4117 = !DILocalVariable(name: "ns", scope: !4109, file: !1, line: 1601, type: !42)
!4118 = !DILocation(line: 1601, column: 9, scope: !4109)
!4119 = !DILocation(line: 1603, column: 5, scope: !4109)
!4120 = !DILocation(line: 1603, column: 16, scope: !4109)
!4121 = !DILocation(line: 1604, column: 8, scope: !4109)
!4122 = !DILocation(line: 1604, column: 6, scope: !4109)
!4123 = !DILocation(line: 1608, column: 9, scope: !4124)
!4124 = distinct !DILexicalBlock(scope: !4109, file: !1, line: 1608, column: 8)
!4125 = !DILocation(line: 1608, column: 8, scope: !4124)
!4126 = !DILocation(line: 1608, column: 13, scope: !4124)
!4127 = !DILocation(line: 1608, column: 8, scope: !4109)
!4128 = !DILocation(line: 1609, column: 5, scope: !4129)
!4129 = distinct !DILexicalBlock(scope: !4124, file: !1, line: 1608, column: 21)
!4130 = !DILocation(line: 1610, column: 16, scope: !4129)
!4131 = !DILocation(line: 1610, column: 8, scope: !4129)
!4132 = !DILocation(line: 1611, column: 9, scope: !4133)
!4133 = distinct !DILexicalBlock(scope: !4129, file: !1, line: 1611, column: 9)
!4134 = !DILocation(line: 1611, column: 12, scope: !4133)
!4135 = !DILocation(line: 1611, column: 9, scope: !4129)
!4136 = !DILocation(line: 1612, column: 9, scope: !4133)
!4137 = !DILocation(line: 1612, column: 6, scope: !4133)
!4138 = !DILocation(line: 1613, column: 14, scope: !4139)
!4139 = distinct !DILexicalBlock(scope: !4133, file: !1, line: 1613, column: 14)
!4140 = !DILocation(line: 1613, column: 17, scope: !4139)
!4141 = !DILocation(line: 1613, column: 14, scope: !4133)
!4142 = !DILocation(line: 1614, column: 9, scope: !4139)
!4143 = !DILocation(line: 1614, column: 6, scope: !4139)
!4144 = !DILocation(line: 1615, column: 4, scope: !4129)
!4145 = !DILocation(line: 1616, column: 8, scope: !4146)
!4146 = distinct !DILexicalBlock(scope: !4109, file: !1, line: 1616, column: 8)
!4147 = !DILocation(line: 1616, column: 12, scope: !4146)
!4148 = !DILocation(line: 1616, column: 10, scope: !4146)
!4149 = !DILocation(line: 1616, column: 8, scope: !4109)
!4150 = !DILocation(line: 1617, column: 9, scope: !4146)
!4151 = !DILocation(line: 1617, column: 7, scope: !4146)
!4152 = !DILocation(line: 1617, column: 5, scope: !4146)
!4153 = !DILocation(line: 1618, column: 13, scope: !4154)
!4154 = distinct !DILexicalBlock(scope: !4146, file: !1, line: 1618, column: 13)
!4155 = !DILocation(line: 1618, column: 17, scope: !4154)
!4156 = !DILocation(line: 1618, column: 15, scope: !4154)
!4157 = !DILocation(line: 1618, column: 13, scope: !4146)
!4158 = !DILocation(line: 1619, column: 9, scope: !4154)
!4159 = !DILocation(line: 1619, column: 7, scope: !4154)
!4160 = !DILocation(line: 1619, column: 5, scope: !4154)
!4161 = !DILocation(line: 1620, column: 28, scope: !4109)
!4162 = !DILocation(line: 1620, column: 43, scope: !4109)
!4163 = !DILocation(line: 1620, column: 46, scope: !4109)
!4164 = !DILocation(line: 1620, column: 4, scope: !4109)
!4165 = !DILocation(line: 1621, column: 4, scope: !4109)
!4166 = !DILocation(line: 1623, column: 14, scope: !4167)
!4167 = distinct !DILexicalBlock(scope: !3826, file: !1, line: 1623, column: 7)
!4168 = !DILocation(line: 1623, column: 7, scope: !4167)
!4169 = !DILocation(line: 1623, column: 27, scope: !4167)
!4170 = !DILocation(line: 1623, column: 7, scope: !3826)
!4171 = !DILocation(line: 1624, column: 12, scope: !4172)
!4172 = distinct !DILexicalBlock(scope: !4167, file: !1, line: 1623, column: 33)
!4173 = !DILocation(line: 1624, column: 4, scope: !4172)
!4174 = !DILocation(line: 1626, column: 16, scope: !4175)
!4175 = distinct !DILexicalBlock(scope: !4176, file: !1, line: 1626, column: 9)
!4176 = distinct !DILexicalBlock(scope: !4172, file: !1, line: 1624, column: 20)
!4177 = !DILocation(line: 1626, column: 9, scope: !4175)
!4178 = !DILocation(line: 1626, column: 30, scope: !4175)
!4179 = !DILocation(line: 1626, column: 9, scope: !4176)
!4180 = !DILocation(line: 1627, column: 33, scope: !4181)
!4181 = distinct !DILexicalBlock(scope: !4175, file: !1, line: 1626, column: 36)
!4182 = !DILocation(line: 1627, column: 6, scope: !4181)
!4183 = !DILocation(line: 1628, column: 6, scope: !4181)
!4184 = !DILocation(line: 1626, column: 33, scope: !4185)
!4185 = !DILexicalBlockFile(scope: !4175, file: !1, discriminator: 1)
!4186 = !DILocation(line: 1631, column: 16, scope: !4187)
!4187 = distinct !DILexicalBlock(scope: !4176, file: !1, line: 1631, column: 9)
!4188 = !DILocation(line: 1631, column: 9, scope: !4187)
!4189 = !DILocation(line: 1631, column: 29, scope: !4187)
!4190 = !DILocation(line: 1631, column: 9, scope: !4176)
!4191 = !DILocation(line: 1632, column: 33, scope: !4192)
!4192 = distinct !DILexicalBlock(scope: !4187, file: !1, line: 1631, column: 35)
!4193 = !DILocation(line: 1632, column: 6, scope: !4192)
!4194 = !DILocation(line: 1634, column: 6, scope: !4192)
!4195 = !DILocation(line: 1631, column: 32, scope: !4196)
!4196 = !DILexicalBlockFile(scope: !4187, file: !1, discriminator: 1)
!4197 = !DILocation(line: 1637, column: 16, scope: !4198)
!4198 = distinct !DILexicalBlock(scope: !4176, file: !1, line: 1637, column: 9)
!4199 = !DILocation(line: 1637, column: 9, scope: !4198)
!4200 = !DILocation(line: 1637, column: 28, scope: !4198)
!4201 = !DILocation(line: 1637, column: 9, scope: !4176)
!4202 = !DILocation(line: 1638, column: 33, scope: !4203)
!4203 = distinct !DILexicalBlock(scope: !4198, file: !1, line: 1637, column: 34)
!4204 = !DILocation(line: 1638, column: 6, scope: !4203)
!4205 = !DILocation(line: 1640, column: 6, scope: !4203)
!4206 = !DILocation(line: 1637, column: 31, scope: !4207)
!4207 = !DILexicalBlockFile(scope: !4198, file: !1, discriminator: 1)
!4208 = !DILocation(line: 1643, column: 16, scope: !4209)
!4209 = distinct !DILexicalBlock(scope: !4176, file: !1, line: 1643, column: 9)
!4210 = !DILocation(line: 1643, column: 9, scope: !4209)
!4211 = !DILocation(line: 1643, column: 29, scope: !4209)
!4212 = !DILocation(line: 1643, column: 9, scope: !4176)
!4213 = !DILocation(line: 1644, column: 33, scope: !4214)
!4214 = distinct !DILexicalBlock(scope: !4209, file: !1, line: 1643, column: 35)
!4215 = !DILocation(line: 1644, column: 6, scope: !4214)
!4216 = !DILocation(line: 1646, column: 6, scope: !4214)
!4217 = !DILocation(line: 1648, column: 16, scope: !4218)
!4218 = distinct !DILexicalBlock(scope: !4176, file: !1, line: 1648, column: 9)
!4219 = !DILocation(line: 1648, column: 9, scope: !4218)
!4220 = !DILocation(line: 1648, column: 29, scope: !4218)
!4221 = !DILocation(line: 1648, column: 9, scope: !4176)
!4222 = !DILocation(line: 1649, column: 33, scope: !4223)
!4223 = distinct !DILexicalBlock(scope: !4218, file: !1, line: 1648, column: 35)
!4224 = !DILocation(line: 1649, column: 6, scope: !4223)
!4225 = !DILocation(line: 1651, column: 6, scope: !4223)
!4226 = !DILocation(line: 1648, column: 32, scope: !4227)
!4227 = !DILexicalBlockFile(scope: !4218, file: !1, discriminator: 1)
!4228 = !DILocation(line: 1654, column: 16, scope: !4229)
!4229 = distinct !DILexicalBlock(scope: !4176, file: !1, line: 1654, column: 9)
!4230 = !DILocation(line: 1654, column: 9, scope: !4229)
!4231 = !DILocation(line: 1654, column: 29, scope: !4229)
!4232 = !DILocation(line: 1654, column: 9, scope: !4176)
!4233 = !DILocation(line: 1655, column: 33, scope: !4234)
!4234 = distinct !DILexicalBlock(scope: !4229, file: !1, line: 1654, column: 35)
!4235 = !DILocation(line: 1655, column: 6, scope: !4234)
!4236 = !DILocation(line: 1657, column: 6, scope: !4234)
!4237 = !DILocation(line: 1654, column: 32, scope: !4238)
!4238 = !DILexicalBlockFile(scope: !4229, file: !1, discriminator: 1)
!4239 = !DILocation(line: 1660, column: 24, scope: !4176)
!4240 = !DILocation(line: 1660, column: 27, scope: !4176)
!4241 = !DILocation(line: 1663, column: 30, scope: !4176)
!4242 = !DILocation(line: 1660, column: 5, scope: !4176)
!4243 = !DILocation(line: 1664, column: 32, scope: !4176)
!4244 = !DILocation(line: 1664, column: 5, scope: !4176)
!4245 = !DILocation(line: 1665, column: 5, scope: !4176)
!4246 = !DILocation(line: 1667, column: 5, scope: !4172)
!4247 = !DILocation(line: 1667, column: 16, scope: !4172)
!4248 = !DILocation(line: 1668, column: 4, scope: !4172)
!4249 = !DILocation(line: 1623, column: 30, scope: !4250)
!4250 = !DILexicalBlockFile(scope: !4167, file: !1, discriminator: 1)
!4251 = !DILocation(line: 1671, column: 14, scope: !4252)
!4252 = distinct !DILexicalBlock(scope: !3826, file: !1, line: 1671, column: 7)
!4253 = !DILocation(line: 1671, column: 7, scope: !4252)
!4254 = !DILocation(line: 1671, column: 26, scope: !4252)
!4255 = !DILocation(line: 1671, column: 7, scope: !3826)
!4256 = !DILocation(line: 1672, column: 5, scope: !4257)
!4257 = distinct !DILexicalBlock(scope: !4252, file: !1, line: 1671, column: 32)
!4258 = !DILocation(line: 1672, column: 16, scope: !4257)
!4259 = !DILocation(line: 1673, column: 26, scope: !4257)
!4260 = !DILocation(line: 1673, column: 33, scope: !4257)
!4261 = !DILocation(line: 1673, column: 4, scope: !4262)
!4262 = !DILexicalBlockFile(scope: !4257, file: !1, discriminator: 1)
!4263 = !DILocation(line: 1674, column: 4, scope: !4257)
!4264 = !DILocation(line: 1676, column: 14, scope: !4265)
!4265 = distinct !DILexicalBlock(scope: !3826, file: !1, line: 1676, column: 7)
!4266 = !DILocation(line: 1676, column: 7, scope: !4265)
!4267 = !DILocation(line: 1676, column: 28, scope: !4265)
!4268 = !DILocation(line: 1676, column: 7, scope: !3826)
!4269 = !DILocation(line: 1677, column: 5, scope: !4270)
!4270 = distinct !DILexicalBlock(scope: !4265, file: !1, line: 1676, column: 34)
!4271 = !DILocation(line: 1677, column: 16, scope: !4270)
!4272 = !DILocation(line: 1678, column: 29, scope: !4270)
!4273 = !DILocation(line: 1678, column: 36, scope: !4270)
!4274 = !DILocation(line: 1678, column: 4, scope: !4270)
!4275 = !DILocation(line: 1679, column: 4, scope: !4270)
!4276 = !DILocation(line: 1676, column: 31, scope: !4277)
!4277 = !DILexicalBlockFile(scope: !4265, file: !1, discriminator: 1)
!4278 = !DILocation(line: 1682, column: 22, scope: !3826)
!4279 = !DILocation(line: 1682, column: 25, scope: !3826)
!4280 = !DILocation(line: 1683, column: 33, scope: !3826)
!4281 = !DILocation(line: 1683, column: 38, scope: !3826)
!4282 = !DILocation(line: 1682, column: 3, scope: !3826)
!4283 = !DILocation(line: 1684, column: 3, scope: !3826)
!4284 = !DILocation(line: 1686, column: 2, scope: !407)
!4285 = !DILocation(line: 1687, column: 1, scope: !407)
!4286 = !DILocalVariable(name: "pdev", arg: 1, scope: !410, file: !1, line: 1387, type: !413)
!4287 = !DILocation(line: 1387, column: 21, scope: !410)
!4288 = !DILocalVariable(name: "a", arg: 2, scope: !410, file: !1, line: 1387, type: !24)
!4289 = !DILocation(line: 1387, column: 43, scope: !410)
!4290 = !DILocalVariable(name: "val", arg: 3, scope: !410, file: !1, line: 1387, type: !95)
!4291 = !DILocation(line: 1387, column: 52, scope: !410)
!4292 = !DILocalVariable(name: "numbers", scope: !410, file: !1, line: 1390, type: !4293)
!4293 = !DICompositeType(tag: DW_TAG_array_type, baseType: !47, size: 192, align: 64, elements: !439)
!4294 = !DILocation(line: 1390, column: 16, scope: !410)
!4295 = !DILocalVariable(name: "p", scope: !410, file: !1, line: 1391, type: !95)
!4296 = !DILocation(line: 1391, column: 8, scope: !410)
!4297 = !DILocalVariable(name: "dev", scope: !410, file: !1, line: 1391, type: !95)
!4298 = !DILocation(line: 1391, column: 12, scope: !410)
!4299 = !DILocalVariable(name: "argc", scope: !410, file: !1, line: 1392, type: !23)
!4300 = !DILocation(line: 1392, column: 6, scope: !410)
!4301 = !DILocalVariable(name: "pack", scope: !410, file: !1, line: 1393, type: !4302)
!4302 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !4303, size: 64, align: 64)
!4303 = !DIDerivedType(tag: DW_TAG_typedef, name: "pack_t", file: !4304, line: 37, baseType: !4305)
!4304 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_pack_dev.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!4305 = !DISubroutineType(types: !4306)
!4306 = !{!339, !23, !4307, !357}
!4307 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !47, size: 64, align: 64)
!4308 = !DILocation(line: 1393, column: 10, scope: !410)
!4309 = !DILocalVariable(name: "result", scope: !410, file: !1, line: 1394, type: !339)
!4310 = !DILocation(line: 1394, column: 8, scope: !410)
!4311 = !DILocalVariable(name: "error", scope: !410, file: !1, line: 1395, type: !80)
!4312 = !DILocation(line: 1395, column: 14, scope: !410)
!4313 = !DILocation(line: 1397, column: 9, scope: !410)
!4314 = !DILocation(line: 1397, column: 2, scope: !410)
!4315 = !DILocation(line: 1398, column: 20, scope: !4316)
!4316 = distinct !DILexicalBlock(scope: !410, file: !1, line: 1398, column: 6)
!4317 = !DILocation(line: 1398, column: 13, scope: !4316)
!4318 = !DILocation(line: 1398, column: 11, scope: !4316)
!4319 = !DILocation(line: 1398, column: 31, scope: !4316)
!4320 = !DILocation(line: 1398, column: 6, scope: !410)
!4321 = !DILocation(line: 1403, column: 7, scope: !4322)
!4322 = distinct !DILexicalBlock(scope: !4316, file: !1, line: 1398, column: 40)
!4323 = !DILocation(line: 1403, column: 10, scope: !4322)
!4324 = !DILocation(line: 1404, column: 25, scope: !4325)
!4325 = distinct !DILexicalBlock(scope: !4322, file: !1, line: 1404, column: 7)
!4326 = !DILocation(line: 1404, column: 15, scope: !4325)
!4327 = !DILocation(line: 1404, column: 13, scope: !4325)
!4328 = !DILocation(line: 1404, column: 31, scope: !4325)
!4329 = !DILocation(line: 1404, column: 7, scope: !4322)
!4330 = !DILocation(line: 1405, column: 22, scope: !4331)
!4331 = distinct !DILexicalBlock(scope: !4325, file: !1, line: 1404, column: 40)
!4332 = !DILocation(line: 1406, column: 31, scope: !4331)
!4333 = !DILocation(line: 1405, column: 4, scope: !4331)
!4334 = !DILocation(line: 1407, column: 4, scope: !4331)
!4335 = !DILocation(line: 1409, column: 8, scope: !4322)
!4336 = !DILocation(line: 1410, column: 3, scope: !4322)
!4337 = !DILocation(line: 1410, column: 15, scope: !4338)
!4338 = !DILexicalBlockFile(scope: !4322, file: !1, discriminator: 1)
!4339 = !DILocation(line: 1410, column: 13, scope: !4338)
!4340 = !DILocation(line: 1410, column: 37, scope: !4338)
!4341 = !DILocation(line: 1410, column: 3, scope: !4338)
!4342 = !DILocation(line: 1411, column: 9, scope: !4343)
!4343 = distinct !DILexicalBlock(scope: !4344, file: !1, line: 1411, column: 8)
!4344 = distinct !DILexicalBlock(scope: !4322, file: !1, line: 1410, column: 46)
!4345 = !DILocation(line: 1411, column: 8, scope: !4343)
!4346 = !DILocation(line: 1411, column: 11, scope: !4343)
!4347 = !DILocation(line: 1411, column: 8, scope: !4344)
!4348 = !DILocation(line: 1412, column: 23, scope: !4349)
!4349 = distinct !DILexicalBlock(scope: !4343, file: !1, line: 1411, column: 20)
!4350 = !DILocation(line: 1412, column: 5, scope: !4349)
!4351 = !DILocation(line: 1414, column: 5, scope: !4349)
!4352 = !DILocation(line: 1416, column: 8, scope: !4353)
!4353 = distinct !DILexicalBlock(scope: !4344, file: !1, line: 1416, column: 8)
!4354 = !DILocation(line: 1416, column: 13, scope: !4353)
!4355 = !DILocation(line: 1416, column: 8, scope: !4344)
!4356 = !DILocation(line: 1417, column: 23, scope: !4357)
!4357 = distinct !DILexicalBlock(scope: !4353, file: !1, line: 1416, column: 31)
!4358 = !DILocation(line: 1417, column: 5, scope: !4357)
!4359 = !DILocation(line: 1419, column: 5, scope: !4357)
!4360 = !DILocation(line: 1421, column: 37, scope: !4344)
!4361 = !DILocation(line: 1421, column: 16, scope: !4344)
!4362 = !DILocation(line: 1421, column: 4, scope: !4344)
!4363 = !DILocation(line: 1421, column: 20, scope: !4344)
!4364 = !DILocation(line: 1410, column: 3, scope: !4365)
!4365 = !DILexicalBlockFile(scope: !4322, file: !1, discriminator: 2)
!4366 = !DILocation(line: 1423, column: 7, scope: !4367)
!4367 = distinct !DILexicalBlock(scope: !4322, file: !1, line: 1423, column: 7)
!4368 = !DILocation(line: 1423, column: 12, scope: !4367)
!4369 = !DILocation(line: 1423, column: 7, scope: !4322)
!4370 = !DILocation(line: 1424, column: 22, scope: !4371)
!4371 = distinct !DILexicalBlock(scope: !4367, file: !1, line: 1423, column: 17)
!4372 = !DILocation(line: 1424, column: 4, scope: !4371)
!4373 = !DILocation(line: 1426, column: 4, scope: !4371)
!4374 = !DILocation(line: 1428, column: 14, scope: !4322)
!4375 = !DILocation(line: 1428, column: 20, scope: !4322)
!4376 = !DILocation(line: 1428, column: 26, scope: !4322)
!4377 = !DILocation(line: 1428, column: 12, scope: !4322)
!4378 = !DILocation(line: 1428, column: 10, scope: !4322)
!4379 = !DILocation(line: 1429, column: 7, scope: !4380)
!4380 = distinct !DILexicalBlock(scope: !4322, file: !1, line: 1429, column: 7)
!4381 = !DILocation(line: 1429, column: 13, scope: !4380)
!4382 = !DILocation(line: 1429, column: 7, scope: !4322)
!4383 = !DILocation(line: 1430, column: 22, scope: !4384)
!4384 = distinct !DILexicalBlock(scope: !4380, file: !1, line: 1429, column: 22)
!4385 = !DILocation(line: 1431, column: 14, scope: !4384)
!4386 = !DILocation(line: 1430, column: 4, scope: !4384)
!4387 = !DILocation(line: 1432, column: 4, scope: !4384)
!4388 = !DILocation(line: 1434, column: 2, scope: !4322)
!4389 = !DILocation(line: 1436, column: 19, scope: !4390)
!4390 = distinct !DILexicalBlock(scope: !4316, file: !1, line: 1434, column: 9)
!4391 = !DILocation(line: 1436, column: 10, scope: !4390)
!4392 = !DILocation(line: 1438, column: 10, scope: !410)
!4393 = !DILocation(line: 1438, column: 3, scope: !410)
!4394 = !DILocation(line: 1438, column: 8, scope: !410)
!4395 = !DILocation(line: 1439, column: 2, scope: !410)
!4396 = !DILocation(line: 1441, column: 1, scope: !410)
!4397 = !DILocalVariable(name: "p", arg: 1, scope: !424, file: !1, line: 1862, type: !381)
!4398 = !DILocation(line: 1862, column: 21, scope: !424)
!4399 = !DILocalVariable(name: "l", scope: !424, file: !1, line: 1864, type: !52)
!4400 = !DILocation(line: 1864, column: 10, scope: !424)
!4401 = !DILocalVariable(name: "limit", scope: !424, file: !1, line: 1864, type: !52)
!4402 = !DILocation(line: 1864, column: 13, scope: !424)
!4403 = !DILocalVariable(name: "last_digit_limit", scope: !424, file: !1, line: 1864, type: !52)
!4404 = !DILocation(line: 1864, column: 20, scope: !424)
!4405 = !DILocalVariable(name: "base", scope: !424, file: !1, line: 1865, type: !23)
!4406 = !DILocation(line: 1865, column: 6, scope: !424)
!4407 = !DILocalVariable(name: "digit", scope: !424, file: !1, line: 1865, type: !23)
!4408 = !DILocation(line: 1865, column: 12, scope: !424)
!4409 = !DILocalVariable(name: "sign", scope: !424, file: !1, line: 1865, type: !23)
!4410 = !DILocation(line: 1865, column: 19, scope: !424)
!4411 = !DILocation(line: 1867, column: 7, scope: !424)
!4412 = !DILocation(line: 1869, column: 8, scope: !4413)
!4413 = distinct !DILexicalBlock(scope: !424, file: !1, line: 1869, column: 6)
!4414 = !DILocation(line: 1869, column: 7, scope: !4413)
!4415 = !DILocation(line: 1869, column: 6, scope: !4413)
!4416 = !DILocation(line: 1869, column: 10, scope: !4413)
!4417 = !DILocation(line: 1869, column: 6, scope: !424)
!4418 = !DILocation(line: 1870, column: 8, scope: !4419)
!4419 = distinct !DILexicalBlock(scope: !4413, file: !1, line: 1869, column: 18)
!4420 = !DILocation(line: 1871, column: 41, scope: !4419)
!4421 = !DILocation(line: 1871, column: 39, scope: !4419)
!4422 = !DILocation(line: 1871, column: 9, scope: !4419)
!4423 = !DILocation(line: 1872, column: 52, scope: !4419)
!4424 = !DILocation(line: 1872, column: 50, scope: !4419)
!4425 = !DILocation(line: 1872, column: 20, scope: !4419)
!4426 = !DILocation(line: 1873, column: 7, scope: !4419)
!4427 = !DILocation(line: 1873, column: 3, scope: !4419)
!4428 = !DILocation(line: 1874, column: 2, scope: !4419)
!4429 = !DILocation(line: 1875, column: 8, scope: !4430)
!4430 = distinct !DILexicalBlock(scope: !4413, file: !1, line: 1874, column: 9)
!4431 = !DILocation(line: 1876, column: 23, scope: !4430)
!4432 = !DILocation(line: 1876, column: 21, scope: !4430)
!4433 = !DILocation(line: 1876, column: 9, scope: !4430)
!4434 = !DILocation(line: 1877, column: 34, scope: !4430)
!4435 = !DILocation(line: 1877, column: 32, scope: !4430)
!4436 = !DILocation(line: 1877, column: 20, scope: !4430)
!4437 = !DILocation(line: 1880, column: 4, scope: !424)
!4438 = !DILocation(line: 1881, column: 12, scope: !424)
!4439 = !DILocation(line: 1881, column: 11, scope: !424)
!4440 = !DILocation(line: 1881, column: 10, scope: !424)
!4441 = !DILocation(line: 1881, column: 14, scope: !424)
!4442 = !DILocation(line: 1881, column: 8, scope: !424)
!4443 = !DILocation(line: 1882, column: 2, scope: !424)
!4444 = !DILocation(line: 1882, column: 9, scope: !4445)
!4445 = !DILexicalBlockFile(scope: !424, file: !1, discriminator: 1)
!4446 = !DILocation(line: 1882, column: 15, scope: !4445)
!4447 = !DILocation(line: 1882, column: 20, scope: !4445)
!4448 = !DILocation(line: 1882, column: 23, scope: !4449)
!4449 = !DILexicalBlockFile(scope: !424, file: !1, discriminator: 2)
!4450 = !DILocation(line: 1882, column: 31, scope: !4449)
!4451 = !DILocation(line: 1882, column: 29, scope: !4449)
!4452 = !DILocation(line: 1882, column: 2, scope: !4453)
!4453 = !DILexicalBlockFile(scope: !424, file: !1, discriminator: 3)
!4454 = !DILocation(line: 1883, column: 7, scope: !4455)
!4455 = distinct !DILexicalBlock(scope: !4456, file: !1, line: 1883, column: 7)
!4456 = distinct !DILexicalBlock(scope: !424, file: !1, line: 1882, column: 37)
!4457 = !DILocation(line: 1883, column: 11, scope: !4455)
!4458 = !DILocation(line: 1883, column: 9, scope: !4455)
!4459 = !DILocation(line: 1883, column: 17, scope: !4455)
!4460 = !DILocation(line: 1883, column: 21, scope: !4461)
!4461 = !DILexicalBlockFile(scope: !4455, file: !1, discriminator: 1)
!4462 = !DILocation(line: 1883, column: 26, scope: !4461)
!4463 = !DILocation(line: 1883, column: 23, scope: !4461)
!4464 = !DILocation(line: 1883, column: 32, scope: !4461)
!4465 = !DILocation(line: 1883, column: 35, scope: !4466)
!4466 = !DILexicalBlockFile(scope: !4455, file: !1, discriminator: 2)
!4467 = !DILocation(line: 1883, column: 43, scope: !4466)
!4468 = !DILocation(line: 1883, column: 41, scope: !4466)
!4469 = !DILocation(line: 1883, column: 7, scope: !4466)
!4470 = !DILocation(line: 1884, column: 12, scope: !4455)
!4471 = !DILocation(line: 1884, column: 17, scope: !4455)
!4472 = !DILocation(line: 1884, column: 11, scope: !4455)
!4473 = !DILocation(line: 1884, column: 4, scope: !4455)
!4474 = !DILocation(line: 1885, column: 8, scope: !4456)
!4475 = !DILocation(line: 1885, column: 12, scope: !4456)
!4476 = !DILocation(line: 1885, column: 10, scope: !4456)
!4477 = !DILocation(line: 1885, column: 20, scope: !4456)
!4478 = !DILocation(line: 1885, column: 18, scope: !4456)
!4479 = !DILocation(line: 1885, column: 5, scope: !4456)
!4480 = !DILocation(line: 1886, column: 16, scope: !4456)
!4481 = !DILocation(line: 1886, column: 12, scope: !4456)
!4482 = !DILocation(line: 1886, column: 11, scope: !4456)
!4483 = !DILocation(line: 1886, column: 19, scope: !4456)
!4484 = !DILocation(line: 1886, column: 9, scope: !4456)
!4485 = !DILocation(line: 1882, column: 2, scope: !4486)
!4486 = !DILexicalBlockFile(scope: !424, file: !1, discriminator: 4)
!4487 = !DILocation(line: 1888, column: 10, scope: !424)
!4488 = !DILocation(line: 1888, column: 15, scope: !424)
!4489 = !DILocation(line: 1888, column: 9, scope: !424)
!4490 = !DILocation(line: 1888, column: 23, scope: !4445)
!4491 = !DILocation(line: 1888, column: 22, scope: !4445)
!4492 = !DILocation(line: 1888, column: 9, scope: !4445)
!4493 = !DILocation(line: 1888, column: 27, scope: !4449)
!4494 = !DILocation(line: 1888, column: 9, scope: !4449)
!4495 = !DILocation(line: 1888, column: 9, scope: !4453)
!4496 = !DILocation(line: 1888, column: 2, scope: !4453)
!4497 = !DILocation(line: 1889, column: 1, scope: !424)
!4498 = !DILocalVariable(name: "p", arg: 1, scope: !425, file: !1, line: 1834, type: !381)
!4499 = !DILocation(line: 1834, column: 20, scope: !425)
!4500 = !DILocalVariable(name: "l", scope: !425, file: !1, line: 1836, type: !52)
!4501 = !DILocation(line: 1836, column: 10, scope: !425)
!4502 = !DILocalVariable(name: "limit", scope: !425, file: !1, line: 1836, type: !52)
!4503 = !DILocation(line: 1836, column: 13, scope: !425)
!4504 = !DILocalVariable(name: "last_digit_limit", scope: !425, file: !1, line: 1836, type: !52)
!4505 = !DILocation(line: 1836, column: 20, scope: !425)
!4506 = !DILocalVariable(name: "digit", scope: !425, file: !1, line: 1837, type: !23)
!4507 = !DILocation(line: 1837, column: 6, scope: !425)
!4508 = !DILocalVariable(name: "base", scope: !425, file: !1, line: 1837, type: !23)
!4509 = !DILocation(line: 1837, column: 13, scope: !425)
!4510 = !DILocation(line: 1839, column: 7, scope: !425)
!4511 = !DILocation(line: 1840, column: 22, scope: !425)
!4512 = !DILocation(line: 1840, column: 20, scope: !425)
!4513 = !DILocation(line: 1840, column: 8, scope: !425)
!4514 = !DILocation(line: 1841, column: 33, scope: !425)
!4515 = !DILocation(line: 1841, column: 31, scope: !425)
!4516 = !DILocation(line: 1841, column: 19, scope: !425)
!4517 = !DILocation(line: 1843, column: 4, scope: !425)
!4518 = !DILocation(line: 1844, column: 12, scope: !425)
!4519 = !DILocation(line: 1844, column: 11, scope: !425)
!4520 = !DILocation(line: 1844, column: 10, scope: !425)
!4521 = !DILocation(line: 1844, column: 14, scope: !425)
!4522 = !DILocation(line: 1844, column: 8, scope: !425)
!4523 = !DILocation(line: 1845, column: 2, scope: !425)
!4524 = !DILocation(line: 1845, column: 9, scope: !4525)
!4525 = !DILexicalBlockFile(scope: !425, file: !1, discriminator: 1)
!4526 = !DILocation(line: 1845, column: 15, scope: !4525)
!4527 = !DILocation(line: 1845, column: 20, scope: !4525)
!4528 = !DILocation(line: 1845, column: 23, scope: !4529)
!4529 = !DILexicalBlockFile(scope: !425, file: !1, discriminator: 2)
!4530 = !DILocation(line: 1845, column: 31, scope: !4529)
!4531 = !DILocation(line: 1845, column: 29, scope: !4529)
!4532 = !DILocation(line: 1845, column: 2, scope: !4533)
!4533 = !DILexicalBlockFile(scope: !425, file: !1, discriminator: 3)
!4534 = !DILocation(line: 1846, column: 7, scope: !4535)
!4535 = distinct !DILexicalBlock(scope: !4536, file: !1, line: 1846, column: 7)
!4536 = distinct !DILexicalBlock(scope: !425, file: !1, line: 1845, column: 37)
!4537 = !DILocation(line: 1846, column: 9, scope: !4535)
!4538 = !DILocation(line: 1846, column: 8, scope: !4535)
!4539 = !DILocation(line: 1846, column: 15, scope: !4535)
!4540 = !DILocation(line: 1846, column: 19, scope: !4541)
!4541 = !DILexicalBlockFile(scope: !4535, file: !1, discriminator: 1)
!4542 = !DILocation(line: 1846, column: 24, scope: !4541)
!4543 = !DILocation(line: 1846, column: 21, scope: !4541)
!4544 = !DILocation(line: 1846, column: 30, scope: !4541)
!4545 = !DILocation(line: 1846, column: 33, scope: !4546)
!4546 = !DILexicalBlockFile(scope: !4535, file: !1, discriminator: 2)
!4547 = !DILocation(line: 1846, column: 41, scope: !4546)
!4548 = !DILocation(line: 1846, column: 39, scope: !4546)
!4549 = !DILocation(line: 1846, column: 7, scope: !4546)
!4550 = !DILocation(line: 1847, column: 6, scope: !4551)
!4551 = distinct !DILexicalBlock(scope: !4535, file: !1, line: 1846, column: 60)
!4552 = !DILocation(line: 1848, column: 4, scope: !4551)
!4553 = !DILocation(line: 1850, column: 8, scope: !4536)
!4554 = !DILocation(line: 1850, column: 12, scope: !4536)
!4555 = !DILocation(line: 1850, column: 10, scope: !4536)
!4556 = !DILocation(line: 1850, column: 20, scope: !4536)
!4557 = !DILocation(line: 1850, column: 18, scope: !4536)
!4558 = !DILocation(line: 1850, column: 5, scope: !4536)
!4559 = !DILocation(line: 1851, column: 16, scope: !4536)
!4560 = !DILocation(line: 1851, column: 12, scope: !4536)
!4561 = !DILocation(line: 1851, column: 11, scope: !4536)
!4562 = !DILocation(line: 1851, column: 19, scope: !4536)
!4563 = !DILocation(line: 1851, column: 9, scope: !4536)
!4564 = !DILocation(line: 1845, column: 2, scope: !4565)
!4565 = !DILexicalBlockFile(scope: !425, file: !1, discriminator: 4)
!4566 = !DILocation(line: 1853, column: 10, scope: !425)
!4567 = !DILocation(line: 1853, column: 2, scope: !425)
!4568 = !DILocation(line: 159, column: 4, scope: !4569)
!4569 = distinct !DILexicalBlock(scope: !4570, file: !1, line: 158, column: 42)
!4570 = distinct !DILexicalBlock(scope: !4571, file: !1, line: 158, column: 7)
!4571 = distinct !DILexicalBlock(scope: !4572, file: !1, line: 155, column: 9)
!4572 = distinct !DILexicalBlock(scope: !426, file: !1, line: 152, column: 6)
!4573 = !DILocation(line: 179, column: 4, scope: !4574)
!4574 = distinct !DILexicalBlock(scope: !4575, file: !1, line: 178, column: 42)
!4575 = distinct !DILexicalBlock(scope: !4576, file: !1, line: 178, column: 7)
!4576 = distinct !DILexicalBlock(scope: !4577, file: !1, line: 176, column: 9)
!4577 = distinct !DILexicalBlock(scope: !429, file: !1, line: 173, column: 6)
!4578 = !DILocalVariable(name: "sp", arg: 1, scope: !414, file: !1, line: 1373, type: !381)
!4579 = !DILocation(line: 1373, column: 18, scope: !414)
!4580 = !DILocalVariable(name: "sep", arg: 2, scope: !414, file: !1, line: 1373, type: !80)
!4581 = !DILocation(line: 1373, column: 34, scope: !414)
!4582 = !DILocalVariable(name: "p", scope: !414, file: !1, line: 1375, type: !95)
!4583 = !DILocation(line: 1375, column: 8, scope: !414)
!4584 = !DILocalVariable(name: "s", scope: !414, file: !1, line: 1375, type: !95)
!4585 = !DILocation(line: 1375, column: 12, scope: !414)
!4586 = !DILocation(line: 1376, column: 6, scope: !4587)
!4587 = distinct !DILexicalBlock(scope: !414, file: !1, line: 1376, column: 6)
!4588 = !DILocation(line: 1376, column: 9, scope: !4587)
!4589 = !DILocation(line: 1376, column: 17, scope: !4587)
!4590 = !DILocation(line: 1376, column: 21, scope: !4591)
!4591 = !DILexicalBlockFile(scope: !4587, file: !1, discriminator: 1)
!4592 = !DILocation(line: 1376, column: 20, scope: !4591)
!4593 = !DILocation(line: 1376, column: 24, scope: !4591)
!4594 = !DILocation(line: 1376, column: 32, scope: !4591)
!4595 = !DILocation(line: 1376, column: 37, scope: !4596)
!4596 = !DILexicalBlockFile(scope: !4587, file: !1, discriminator: 2)
!4597 = !DILocation(line: 1376, column: 36, scope: !4596)
!4598 = !DILocation(line: 1376, column: 35, scope: !4596)
!4599 = !DILocation(line: 1376, column: 40, scope: !4596)
!4600 = !DILocation(line: 1376, column: 6, scope: !4596)
!4601 = !DILocation(line: 1377, column: 3, scope: !4587)
!4602 = !DILocation(line: 1378, column: 7, scope: !414)
!4603 = !DILocation(line: 1378, column: 6, scope: !414)
!4604 = !DILocation(line: 1378, column: 4, scope: !414)
!4605 = !DILocation(line: 1379, column: 6, scope: !414)
!4606 = !DILocation(line: 1379, column: 18, scope: !414)
!4607 = !DILocation(line: 1379, column: 21, scope: !414)
!4608 = !DILocation(line: 1379, column: 10, scope: !414)
!4609 = !DILocation(line: 1379, column: 8, scope: !414)
!4610 = !DILocation(line: 1379, column: 4, scope: !414)
!4611 = !DILocation(line: 1380, column: 7, scope: !4612)
!4612 = distinct !DILexicalBlock(scope: !414, file: !1, line: 1380, column: 6)
!4613 = !DILocation(line: 1380, column: 6, scope: !4612)
!4614 = !DILocation(line: 1380, column: 9, scope: !4612)
!4615 = !DILocation(line: 1380, column: 6, scope: !414)
!4616 = !DILocation(line: 1381, column: 5, scope: !4612)
!4617 = !DILocation(line: 1381, column: 8, scope: !4612)
!4618 = !DILocation(line: 1381, column: 3, scope: !4612)
!4619 = !DILocation(line: 1382, column: 8, scope: !414)
!4620 = !DILocation(line: 1382, column: 3, scope: !414)
!4621 = !DILocation(line: 1382, column: 6, scope: !414)
!4622 = !DILocation(line: 1383, column: 9, scope: !414)
!4623 = !DILocation(line: 1383, column: 2, scope: !414)
!4624 = !DILocation(line: 1384, column: 1, scope: !414)
!4625 = !DILocalVariable(name: "p", arg: 1, scope: !417, file: !1, line: 1941, type: !381)
!4626 = !DILocation(line: 1941, column: 19, scope: !417)
!4627 = !DILocation(line: 1943, column: 8, scope: !4628)
!4628 = distinct !DILexicalBlock(scope: !417, file: !1, line: 1943, column: 6)
!4629 = !DILocation(line: 1943, column: 7, scope: !4628)
!4630 = !DILocation(line: 1943, column: 6, scope: !4628)
!4631 = !DILocation(line: 1943, column: 10, scope: !4628)
!4632 = !DILocation(line: 1943, column: 6, scope: !417)
!4633 = !DILocation(line: 1944, column: 23, scope: !4628)
!4634 = !DILocation(line: 1944, column: 10, scope: !4628)
!4635 = !DILocation(line: 1944, column: 3, scope: !4628)
!4636 = !DILocation(line: 1945, column: 8, scope: !4637)
!4637 = distinct !DILexicalBlock(scope: !417, file: !1, line: 1945, column: 6)
!4638 = !DILocation(line: 1945, column: 7, scope: !4637)
!4639 = !DILocation(line: 1945, column: 6, scope: !4637)
!4640 = !DILocation(line: 1945, column: 14, scope: !4637)
!4641 = !DILocation(line: 1945, column: 21, scope: !4637)
!4642 = !DILocation(line: 1945, column: 26, scope: !4643)
!4643 = !DILexicalBlockFile(scope: !4637, file: !1, discriminator: 1)
!4644 = !DILocation(line: 1945, column: 25, scope: !4643)
!4645 = !DILocation(line: 1945, column: 24, scope: !4643)
!4646 = !DILocation(line: 1945, column: 32, scope: !4643)
!4647 = !DILocation(line: 1945, column: 6, scope: !4643)
!4648 = !DILocation(line: 1946, column: 4, scope: !4649)
!4649 = distinct !DILexicalBlock(scope: !4637, file: !1, line: 1945, column: 40)
!4650 = !DILocation(line: 1946, column: 6, scope: !4649)
!4651 = !DILocation(line: 1947, column: 23, scope: !4649)
!4652 = !DILocation(line: 1947, column: 10, scope: !4649)
!4653 = !DILocation(line: 1947, column: 3, scope: !4649)
!4654 = !DILocation(line: 1949, column: 21, scope: !417)
!4655 = !DILocation(line: 1949, column: 9, scope: !417)
!4656 = !DILocation(line: 1949, column: 2, scope: !417)
!4657 = !DILocation(line: 1950, column: 1, scope: !417)
!4658 = !DILocalVariable(name: "p", arg: 1, scope: !420, file: !1, line: 1911, type: !381)
!4659 = !DILocation(line: 1911, column: 21, scope: !420)
!4660 = !DILocalVariable(name: "l", scope: !420, file: !1, line: 1913, type: !52)
!4661 = !DILocation(line: 1913, column: 10, scope: !420)
!4662 = !DILocalVariable(name: "limit", scope: !420, file: !1, line: 1913, type: !52)
!4663 = !DILocation(line: 1913, column: 13, scope: !420)
!4664 = !DILocalVariable(name: "last_digit_limit", scope: !420, file: !1, line: 1913, type: !52)
!4665 = !DILocation(line: 1913, column: 20, scope: !420)
!4666 = !DILocalVariable(name: "base", scope: !420, file: !1, line: 1914, type: !23)
!4667 = !DILocation(line: 1914, column: 6, scope: !420)
!4668 = !DILocalVariable(name: "digit", scope: !420, file: !1, line: 1914, type: !23)
!4669 = !DILocation(line: 1914, column: 12, scope: !420)
!4670 = !DILocalVariable(name: "sign", scope: !420, file: !1, line: 1914, type: !23)
!4671 = !DILocation(line: 1914, column: 19, scope: !420)
!4672 = !DILocation(line: 1916, column: 7, scope: !420)
!4673 = !DILocation(line: 1918, column: 8, scope: !4674)
!4674 = distinct !DILexicalBlock(scope: !420, file: !1, line: 1918, column: 6)
!4675 = !DILocation(line: 1918, column: 7, scope: !4674)
!4676 = !DILocation(line: 1918, column: 6, scope: !4674)
!4677 = !DILocation(line: 1918, column: 10, scope: !4674)
!4678 = !DILocation(line: 1918, column: 6, scope: !420)
!4679 = !DILocation(line: 1919, column: 8, scope: !4680)
!4680 = distinct !DILexicalBlock(scope: !4674, file: !1, line: 1918, column: 18)
!4681 = !DILocation(line: 1920, column: 41, scope: !4680)
!4682 = !DILocation(line: 1920, column: 39, scope: !4680)
!4683 = !DILocation(line: 1920, column: 9, scope: !4680)
!4684 = !DILocation(line: 1921, column: 52, scope: !4680)
!4685 = !DILocation(line: 1921, column: 50, scope: !4680)
!4686 = !DILocation(line: 1921, column: 20, scope: !4680)
!4687 = !DILocation(line: 1922, column: 7, scope: !4680)
!4688 = !DILocation(line: 1922, column: 3, scope: !4680)
!4689 = !DILocation(line: 1923, column: 2, scope: !4680)
!4690 = !DILocation(line: 1924, column: 8, scope: !4691)
!4691 = distinct !DILexicalBlock(scope: !4674, file: !1, line: 1923, column: 9)
!4692 = !DILocation(line: 1925, column: 23, scope: !4691)
!4693 = !DILocation(line: 1925, column: 21, scope: !4691)
!4694 = !DILocation(line: 1925, column: 9, scope: !4691)
!4695 = !DILocation(line: 1926, column: 34, scope: !4691)
!4696 = !DILocation(line: 1926, column: 32, scope: !4691)
!4697 = !DILocation(line: 1926, column: 20, scope: !4691)
!4698 = !DILocation(line: 1929, column: 4, scope: !420)
!4699 = !DILocation(line: 1930, column: 21, scope: !420)
!4700 = !DILocation(line: 1930, column: 20, scope: !420)
!4701 = !DILocation(line: 1930, column: 19, scope: !420)
!4702 = !DILocation(line: 1930, column: 10, scope: !420)
!4703 = !DILocation(line: 1930, column: 8, scope: !420)
!4704 = !DILocation(line: 1931, column: 2, scope: !420)
!4705 = !DILocation(line: 1931, column: 9, scope: !4706)
!4706 = !DILexicalBlockFile(scope: !420, file: !1, discriminator: 1)
!4707 = !DILocation(line: 1931, column: 15, scope: !4706)
!4708 = !DILocation(line: 1931, column: 20, scope: !4706)
!4709 = !DILocation(line: 1931, column: 23, scope: !4710)
!4710 = !DILexicalBlockFile(scope: !420, file: !1, discriminator: 2)
!4711 = !DILocation(line: 1931, column: 31, scope: !4710)
!4712 = !DILocation(line: 1931, column: 29, scope: !4710)
!4713 = !DILocation(line: 1931, column: 2, scope: !4714)
!4714 = !DILexicalBlockFile(scope: !420, file: !1, discriminator: 3)
!4715 = !DILocation(line: 1932, column: 7, scope: !4716)
!4716 = distinct !DILexicalBlock(scope: !4717, file: !1, line: 1932, column: 7)
!4717 = distinct !DILexicalBlock(scope: !420, file: !1, line: 1931, column: 37)
!4718 = !DILocation(line: 1932, column: 11, scope: !4716)
!4719 = !DILocation(line: 1932, column: 9, scope: !4716)
!4720 = !DILocation(line: 1932, column: 17, scope: !4716)
!4721 = !DILocation(line: 1932, column: 21, scope: !4722)
!4722 = !DILexicalBlockFile(scope: !4716, file: !1, discriminator: 1)
!4723 = !DILocation(line: 1932, column: 26, scope: !4722)
!4724 = !DILocation(line: 1932, column: 23, scope: !4722)
!4725 = !DILocation(line: 1932, column: 32, scope: !4722)
!4726 = !DILocation(line: 1932, column: 35, scope: !4727)
!4727 = !DILexicalBlockFile(scope: !4716, file: !1, discriminator: 2)
!4728 = !DILocation(line: 1932, column: 43, scope: !4727)
!4729 = !DILocation(line: 1932, column: 41, scope: !4727)
!4730 = !DILocation(line: 1932, column: 7, scope: !4727)
!4731 = !DILocation(line: 1933, column: 12, scope: !4716)
!4732 = !DILocation(line: 1933, column: 17, scope: !4716)
!4733 = !DILocation(line: 1933, column: 11, scope: !4716)
!4734 = !DILocation(line: 1933, column: 4, scope: !4716)
!4735 = !DILocation(line: 1934, column: 8, scope: !4717)
!4736 = !DILocation(line: 1934, column: 12, scope: !4717)
!4737 = !DILocation(line: 1934, column: 10, scope: !4717)
!4738 = !DILocation(line: 1934, column: 20, scope: !4717)
!4739 = !DILocation(line: 1934, column: 18, scope: !4717)
!4740 = !DILocation(line: 1934, column: 5, scope: !4717)
!4741 = !DILocation(line: 1935, column: 25, scope: !4717)
!4742 = !DILocation(line: 1935, column: 21, scope: !4717)
!4743 = !DILocation(line: 1935, column: 20, scope: !4717)
!4744 = !DILocation(line: 1935, column: 11, scope: !4717)
!4745 = !DILocation(line: 1935, column: 9, scope: !4717)
!4746 = !DILocation(line: 1931, column: 2, scope: !4747)
!4747 = !DILexicalBlockFile(scope: !420, file: !1, discriminator: 4)
!4748 = !DILocation(line: 1937, column: 10, scope: !420)
!4749 = !DILocation(line: 1937, column: 15, scope: !420)
!4750 = !DILocation(line: 1937, column: 9, scope: !420)
!4751 = !DILocation(line: 1937, column: 23, scope: !4706)
!4752 = !DILocation(line: 1937, column: 22, scope: !4706)
!4753 = !DILocation(line: 1937, column: 9, scope: !4706)
!4754 = !DILocation(line: 1937, column: 27, scope: !4710)
!4755 = !DILocation(line: 1937, column: 9, scope: !4710)
!4756 = !DILocation(line: 1937, column: 9, scope: !4714)
!4757 = !DILocation(line: 1937, column: 2, scope: !4714)
!4758 = !DILocation(line: 1938, column: 1, scope: !420)
!4759 = !DILocalVariable(name: "c", arg: 1, scope: !421, file: !1, line: 1893, type: !82)
!4760 = !DILocation(line: 1893, column: 15, scope: !421)
!4761 = !DILocation(line: 1895, column: 6, scope: !4762)
!4762 = distinct !DILexicalBlock(scope: !421, file: !1, line: 1895, column: 6)
!4763 = !DILocation(line: 1895, column: 8, scope: !4762)
!4764 = !DILocation(line: 1895, column: 15, scope: !4762)
!4765 = !DILocation(line: 1895, column: 18, scope: !4766)
!4766 = !DILexicalBlockFile(scope: !4762, file: !1, discriminator: 1)
!4767 = !DILocation(line: 1895, column: 20, scope: !4766)
!4768 = !DILocation(line: 1895, column: 6, scope: !4766)
!4769 = !DILocation(line: 1896, column: 10, scope: !4762)
!4770 = !DILocation(line: 1896, column: 12, scope: !4762)
!4771 = !DILocation(line: 1896, column: 3, scope: !4762)
!4772 = !DILocation(line: 1897, column: 11, scope: !4773)
!4773 = distinct !DILexicalBlock(scope: !4762, file: !1, line: 1897, column: 11)
!4774 = !DILocation(line: 1897, column: 13, scope: !4773)
!4775 = !DILocation(line: 1897, column: 20, scope: !4773)
!4776 = !DILocation(line: 1897, column: 23, scope: !4777)
!4777 = !DILexicalBlockFile(scope: !4773, file: !1, discriminator: 1)
!4778 = !DILocation(line: 1897, column: 25, scope: !4777)
!4779 = !DILocation(line: 1897, column: 11, scope: !4777)
!4780 = !DILocation(line: 1898, column: 10, scope: !4773)
!4781 = !DILocation(line: 1898, column: 12, scope: !4773)
!4782 = !DILocation(line: 1898, column: 3, scope: !4773)
!4783 = !DILocation(line: 1899, column: 11, scope: !4784)
!4784 = distinct !DILexicalBlock(scope: !4773, file: !1, line: 1899, column: 11)
!4785 = !DILocation(line: 1899, column: 13, scope: !4784)
!4786 = !DILocation(line: 1899, column: 20, scope: !4784)
!4787 = !DILocation(line: 1899, column: 23, scope: !4788)
!4788 = !DILexicalBlockFile(scope: !4784, file: !1, discriminator: 1)
!4789 = !DILocation(line: 1899, column: 25, scope: !4788)
!4790 = !DILocation(line: 1899, column: 11, scope: !4788)
!4791 = !DILocation(line: 1900, column: 10, scope: !4784)
!4792 = !DILocation(line: 1900, column: 12, scope: !4784)
!4793 = !DILocation(line: 1900, column: 3, scope: !4784)
!4794 = !DILocation(line: 1902, column: 3, scope: !4784)
!4795 = !DILocation(line: 1903, column: 1, scope: !421)
