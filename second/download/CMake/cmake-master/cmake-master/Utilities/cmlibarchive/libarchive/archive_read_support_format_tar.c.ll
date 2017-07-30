; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_support_format_tar.c'
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
%struct.tar = type { %struct.archive_string, %struct.archive_string, %struct.archive_string, %struct.archive_string, %struct.archive_string, %struct.archive_string, %struct.archive_string, %struct.archive_string, %struct.archive_string, %struct.archive_string, %struct.archive_string, i32, i32, i64, i64, i64, i64, i64, i32, %struct.sparse_block*, %struct.sparse_block*, i64, i64, i32, i32, i8, %struct.archive_string, %struct.archive_string_conv*, %struct.archive_string_conv*, %struct.archive_string_conv*, %struct.archive_string_conv*, i32, i32, i32, i32 }
%struct.sparse_block = type { %struct.sparse_block*, i64, i64, i32 }
%struct.archive_entry_header_ustar = type { [100 x i8], [8 x i8], [8 x i8], [8 x i8], [12 x i8], [12 x i8], [8 x i8], [1 x i8], [100 x i8], [6 x i8], [2 x i8], [32 x i8], [32 x i8], [8 x i8], [8 x i8], [155 x i8] }
%struct.archive_entry_header_gnutar = type { [100 x i8], [8 x i8], [8 x i8], [8 x i8], [12 x i8], [12 x i8], [8 x i8], [1 x i8], [100 x i8], [8 x i8], [32 x i8], [32 x i8], [8 x i8], [8 x i8], [12 x i8], [12 x i8], [12 x i8], [4 x i8], [1 x i8], [4 x %struct.gnu_sparse], [1 x i8], [12 x i8] }
%struct.gnu_sparse = type { [12 x i8], [12 x i8] }
%struct.archive_acl = type { i32, %struct.archive_acl_entry*, %struct.archive_acl_entry*, i32, i32*, i8*, i32 }
%struct.archive_acl_entry = type { %struct.archive_acl_entry*, i32, i32, i32, i32, %struct.archive_mstring }
%struct.archive_mstring = type { %struct.archive_string, %struct.archive_string, %struct.archive_wstring, %struct.archive_string, i32 }
%struct.archive_wstring = type { i32*, i64, i64 }
%struct.extended = type { [21 x %struct.gnu_sparse], [1 x i8], [7 x i8] }

@.str = private unnamed_addr constant [35 x i8] c"archive_read_support_format_gnutar\00", align 1
@.str.1 = private unnamed_addr constant [32 x i8] c"archive_read_support_format_tar\00", align 1
@.str.2 = private unnamed_addr constant [24 x i8] c"Can't allocate tar data\00", align 1
@.str.3 = private unnamed_addr constant [4 x i8] c"tar\00", align 1
@.str.4 = private unnamed_addr constant [7 x i8] c"ustar\00\00", align 1
@.str.5 = private unnamed_addr constant [3 x i8] c"00\00", align 1
@.str.6 = private unnamed_addr constant [7 x i8] c"ustar \00", align 1
@.str.7 = private unnamed_addr constant [3 x i8] c" \00\00", align 1
@.str.8 = private unnamed_addr constant [10 x i8] c"compat-2x\00", align 1
@.str.9 = private unnamed_addr constant [11 x i8] c"hdrcharset\00", align 1
@.str.10 = private unnamed_addr constant [50 x i8] c"tar: hdrcharset option needs a character-set name\00", align 1
@.str.11 = private unnamed_addr constant [8 x i8] c"mac-ext\00", align 1
@.str.12 = private unnamed_addr constant [27 x i8] c"read_concatenated_archives\00", align 1
@archive_read_format_tar_read_header.default_inode = internal global i32 0, align 4
@archive_read_format_tar_read_header.default_dev = internal global i32 0, align 4
@.str.13 = private unnamed_addr constant [22 x i8] c"Truncated tar archive\00", align 1
@.str.14 = private unnamed_addr constant [20 x i8] c"Damaged tar archive\00", align 1
@.str.15 = private unnamed_addr constant [25 x i8] c"Too many special headers\00", align 1
@.str.16 = private unnamed_addr constant [12 x i8] c"Solaris tar\00", align 1
@.str.17 = private unnamed_addr constant [29 x i8] c"POSIX pax interchange format\00", align 1
@.str.18 = private unnamed_addr constant [43 x i8] c"POSIX pax interchange format (Sun variant)\00", align 1
@.str.19 = private unnamed_addr constant [9 x i8] c"ustar  \00\00", align 1
@.str.20 = private unnamed_addr constant [15 x i8] c"GNU tar format\00", align 1
@.str.21 = private unnamed_addr constant [6 x i8] c"ustar\00", align 1
@.str.22 = private unnamed_addr constant [19 x i8] c"POSIX ustar format\00", align 1
@.str.23 = private unnamed_addr constant [16 x i8] c"tar (non-POSIX)\00", align 1
@.str.24 = private unnamed_addr constant [36 x i8] c"Unrecognized GNU sparse file format\00", align 1
@.str.25 = private unnamed_addr constant [48 x i8] c"Malformed Solaris ACL attribute (invalid digit)\00", align 1
@.str.26 = private unnamed_addr constant [50 x i8] c"Malformed Solaris ACL attribute (count too large)\00", align 1
@.str.27 = private unnamed_addr constant [54 x i8] c"Malformed Solaris ACL attribute (unsupported type %o)\00", align 1
@.str.28 = private unnamed_addr constant [48 x i8] c"Malformed Solaris ACL attribute (body overflow)\00", align 1
@.str.29 = private unnamed_addr constant [6 x i8] c"UTF-8\00", align 1
@.str.30 = private unnamed_addr constant [30 x i8] c"Can't allocate memory for ACL\00", align 1
@.str.31 = private unnamed_addr constant [45 x i8] c"Malformed Solaris ACL attribute (unparsable)\00", align 1
@.str.32 = private unnamed_addr constant [25 x i8] c"Special header too large\00", align 1
@.str.33 = private unnamed_addr constant [10 x i8] c"No memory\00", align 1
@.str.34 = private unnamed_addr constant [9 x i8] c"Pathname\00", align 1
@.str.35 = private unnamed_addr constant [29 x i8] c"Can't allocate memory for %s\00", align 1
@.str.36 = private unnamed_addr constant [49 x i8] c"%s can't be converted from %s to current locale.\00", align 1
@.str.37 = private unnamed_addr constant [43 x i8] c"Ignoring malformed pax extended attributes\00", align 1
@.str.38 = private unnamed_addr constant [39 x i8] c"Rejecting pax extended attribute > 1MB\00", align 1
@.str.39 = private unnamed_addr constant [42 x i8] c"Ignoring malformed pax extended attribute\00", align 1
@.str.40 = private unnamed_addr constant [32 x i8] c"Invalid pax extended attributes\00", align 1
@.str.41 = private unnamed_addr constant [6 x i8] c"Gname\00", align 1
@.str.42 = private unnamed_addr constant [9 x i8] c"Linkname\00", align 1
@.str.43 = private unnamed_addr constant [6 x i8] c"Uname\00", align 1
@.str.44 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.45 = private unnamed_addr constant [11 x i8] c"GNU.sparse\00", align 1
@.str.46 = private unnamed_addr constant [34 x i8] c"Non-regular file cannot be sparse\00", align 1
@.str.47 = private unnamed_addr constant [21 x i8] c"GNU.sparse.numblocks\00", align 1
@.str.48 = private unnamed_addr constant [18 x i8] c"GNU.sparse.offset\00", align 1
@.str.49 = private unnamed_addr constant [20 x i8] c"GNU.sparse.numbytes\00", align 1
@.str.50 = private unnamed_addr constant [16 x i8] c"GNU.sparse.size\00", align 1
@.str.51 = private unnamed_addr constant [15 x i8] c"GNU.sparse.map\00", align 1
@.str.52 = private unnamed_addr constant [17 x i8] c"GNU.sparse.major\00", align 1
@.str.53 = private unnamed_addr constant [17 x i8] c"GNU.sparse.minor\00", align 1
@.str.54 = private unnamed_addr constant [16 x i8] c"GNU.sparse.name\00", align 1
@.str.55 = private unnamed_addr constant [20 x i8] c"GNU.sparse.realsize\00", align 1
@.str.56 = private unnamed_addr constant [24 x i8] c"LIBARCHIVE.creationtime\00", align 1
@.str.57 = private unnamed_addr constant [18 x i8] c"LIBARCHIVE.xattr.\00", align 1
@.str.58 = private unnamed_addr constant [18 x i8] c"SCHILY.acl.access\00", align 1
@.str.59 = private unnamed_addr constant [19 x i8] c"SCHILY.acl.default\00", align 1
@.str.60 = private unnamed_addr constant [15 x i8] c"SCHILY.acl.ace\00", align 1
@.str.61 = private unnamed_addr constant [16 x i8] c"SCHILY.devmajor\00", align 1
@.str.62 = private unnamed_addr constant [16 x i8] c"SCHILY.devminor\00", align 1
@.str.63 = private unnamed_addr constant [14 x i8] c"SCHILY.fflags\00", align 1
@.str.64 = private unnamed_addr constant [11 x i8] c"SCHILY.dev\00", align 1
@.str.65 = private unnamed_addr constant [11 x i8] c"SCHILY.ino\00", align 1
@.str.66 = private unnamed_addr constant [13 x i8] c"SCHILY.nlink\00", align 1
@.str.67 = private unnamed_addr constant [16 x i8] c"SCHILY.realsize\00", align 1
@.str.68 = private unnamed_addr constant [14 x i8] c"SCHILY.xattr.\00", align 1
@.str.69 = private unnamed_addr constant [14 x i8] c"SUN.holesdata\00", align 1
@.str.70 = private unnamed_addr constant [27 x i8] c"Parse error: SUN.holesdata\00", align 1
@.str.71 = private unnamed_addr constant [6 x i8] c"atime\00", align 1
@.str.72 = private unnamed_addr constant [6 x i8] c"ctime\00", align 1
@.str.73 = private unnamed_addr constant [8 x i8] c"charset\00", align 1
@.str.74 = private unnamed_addr constant [8 x i8] c"comment\00", align 1
@.str.75 = private unnamed_addr constant [4 x i8] c"gid\00", align 1
@.str.76 = private unnamed_addr constant [6 x i8] c"gname\00", align 1
@.str.77 = private unnamed_addr constant [7 x i8] c"BINARY\00", align 1
@.str.78 = private unnamed_addr constant [24 x i8] c"ISO-IR 10646 2000 UTF-8\00", align 1
@.str.79 = private unnamed_addr constant [9 x i8] c"linkpath\00", align 1
@.str.80 = private unnamed_addr constant [6 x i8] c"mtime\00", align 1
@.str.81 = private unnamed_addr constant [5 x i8] c"path\00", align 1
@.str.82 = private unnamed_addr constant [5 x i8] c"size\00", align 1
@.str.83 = private unnamed_addr constant [4 x i8] c"uid\00", align 1
@.str.84 = private unnamed_addr constant [6 x i8] c"uname\00", align 1
@base64_decode.digits = internal constant [64 x i8] c"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/", align 16
@base64_decode.decode_table = internal global [128 x i8] zeroinitializer, align 16
@.str.85 = private unnamed_addr constant [21 x i8] c"Unknown ACL type: %d\00", align 1
@.str.86 = private unnamed_addr constant [6 x i8] c"%s %s\00", align 1
@.str.87 = private unnamed_addr constant [27 x i8] c"Can't allocate memory for \00", align 1
@.str.88 = private unnamed_addr constant [14 x i8] c"Parse error: \00", align 1
@.str.89 = private unnamed_addr constant [28 x i8] c"Tar entry has negative size\00", align 1
@.str.90 = private unnamed_addr constant [24 x i8] c"Tar entry size overflow\00", align 1
@.str.91 = private unnamed_addr constant [62 x i8] c"Truncated tar archive detected while reading sparse file data\00", align 1
@.str.92 = private unnamed_addr constant [14 x i8] c"Line too long\00", align 1
@.str.93 = private unnamed_addr constant [30 x i8] c"Can't allocate working buffer\00", align 1
@.str.94 = private unnamed_addr constant [14 x i8] c"Out of memory\00", align 1
@.str.95 = private unnamed_addr constant [26 x i8] c"Malformed sparse map data\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_read_support_format_gnutar(%struct.archive* %a) #0 !dbg !439 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !562, metadata !563), !dbg !564
  br label %do.body, !dbg !565

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !566, metadata !563), !dbg !568
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !569
  %call = call i32 @__archive_check_magic(%struct.archive* %0, i32 14594245, i32 1, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str, i32 0, i32 0)), !dbg !569
  store i32 %call, i32* %magic_test, align 4, !dbg !569
  %1 = load i32, i32* %magic_test, align 4, !dbg !569
  %cmp = icmp eq i32 %1, -30, !dbg !569
  br i1 %cmp, label %if.then, label %if.end, !dbg !569

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !571
  br label %return, !dbg !571

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !574

do.end:                                           ; preds = %if.end
  %2 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !576
  %call1 = call i32 @archive_read_support_format_tar(%struct.archive* %2), !dbg !577
  store i32 %call1, i32* %retval, align 4, !dbg !578
  br label %return, !dbg !578

return:                                           ; preds = %do.end, %if.then
  %3 = load i32, i32* %retval, align 4, !dbg !579
  ret i32 %3, !dbg !579
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @__archive_check_magic(%struct.archive*, i32, i32, i8*) #2

; Function Attrs: nounwind uwtable
define i32 @archive_read_support_format_tar(%struct.archive* %_a) #0 !dbg !440 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_read*, align 8
  %tar = alloca %struct.tar*, align 8
  %r = alloca i32, align 4
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !580, metadata !563), !dbg !581
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !582, metadata !563), !dbg !583
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !584
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !585
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !583
  call void @llvm.dbg.declare(metadata %struct.tar** %tar, metadata !586, metadata !563), !dbg !587
  call void @llvm.dbg.declare(metadata i32* %r, metadata !588, metadata !563), !dbg !589
  br label %do.body, !dbg !590

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !591, metadata !563), !dbg !593
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !594
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 14594245, i32 1, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.1, i32 0, i32 0)), !dbg !594
  store i32 %call, i32* %magic_test, align 4, !dbg !594
  %3 = load i32, i32* %magic_test, align 4, !dbg !594
  %cmp = icmp eq i32 %3, -30, !dbg !594
  br i1 %cmp, label %if.then, label %if.end, !dbg !594

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !596
  br label %return, !dbg !596

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !599

do.end:                                           ; preds = %if.end
  %call1 = call noalias i8* @calloc(i64 1, i64 440) #7, !dbg !601
  %4 = bitcast i8* %call1 to %struct.tar*, !dbg !602
  store %struct.tar* %4, %struct.tar** %tar, align 8, !dbg !603
  %5 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !604
  %cmp2 = icmp eq %struct.tar* %5, null, !dbg !606
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !607

if.then3:                                         ; preds = %do.end
  %6 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !608
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %6, i32 0, i32 0, !dbg !610
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.2, i32 0, i32 0)), !dbg !611
  store i32 -30, i32* %retval, align 4, !dbg !612
  br label %return, !dbg !612

if.end4:                                          ; preds = %do.end
  %7 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !613
  %8 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !614
  %9 = bitcast %struct.tar* %8 to i8*, !dbg !614
  %call5 = call i32 @__archive_read_register_format(%struct.archive_read* %7, i8* %9, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.3, i32 0, i32 0), i32 (%struct.archive_read*, i32)* @archive_read_format_tar_bid, i32 (%struct.archive_read*, i8*, i8*)* @archive_read_format_tar_options, i32 (%struct.archive_read*, %struct.archive_entry*)* @archive_read_format_tar_read_header, i32 (%struct.archive_read*, i8**, i64*, i64*)* @archive_read_format_tar_read_data, i32 (%struct.archive_read*)* @archive_read_format_tar_skip, i64 (%struct.archive_read*, i64, i32)* null, i32 (%struct.archive_read*)* @archive_read_format_tar_cleanup, i32 (%struct.archive_read*)* null, i32 (%struct.archive_read*)* null), !dbg !615
  store i32 %call5, i32* %r, align 4, !dbg !616
  %10 = load i32, i32* %r, align 4, !dbg !617
  %cmp6 = icmp ne i32 %10, 0, !dbg !619
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !620

if.then7:                                         ; preds = %if.end4
  %11 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !621
  %12 = bitcast %struct.tar* %11 to i8*, !dbg !621
  call void @free(i8* %12) #7, !dbg !622
  br label %if.end8, !dbg !622

if.end8:                                          ; preds = %if.then7, %if.end4
  store i32 0, i32* %retval, align 4, !dbg !623
  br label %return, !dbg !623

return:                                           ; preds = %if.end8, %if.then3, %if.then
  %13 = load i32, i32* %retval, align 4, !dbg !624
  ret i32 %13, !dbg !624
}

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #3

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

declare i32 @__archive_read_register_format(%struct.archive_read*, i8*, i8*, i32 (%struct.archive_read*, i32)*, i32 (%struct.archive_read*, i8*, i8*)*, i32 (%struct.archive_read*, %struct.archive_entry*)*, i32 (%struct.archive_read*, i8**, i64*, i64*)*, i32 (%struct.archive_read*)*, i64 (%struct.archive_read*, i64, i32)*, i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)*) #2

; Function Attrs: nounwind uwtable
define internal i32 @archive_read_format_tar_bid(%struct.archive_read* %a, i32 %best_bid) #0 !dbg !445 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %best_bid.addr = alloca i32, align 4
  %bid = alloca i32, align 4
  %h = alloca i8*, align 8
  %header = alloca %struct.archive_entry_header_ustar*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !625, metadata !563), !dbg !626
  store i32 %best_bid, i32* %best_bid.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %best_bid.addr, metadata !627, metadata !563), !dbg !628
  call void @llvm.dbg.declare(metadata i32* %bid, metadata !629, metadata !563), !dbg !630
  call void @llvm.dbg.declare(metadata i8** %h, metadata !631, metadata !563), !dbg !632
  call void @llvm.dbg.declare(metadata %struct.archive_entry_header_ustar** %header, metadata !633, metadata !563), !dbg !634
  %0 = load i32, i32* %best_bid.addr, align 4, !dbg !635
  store i32 0, i32* %bid, align 4, !dbg !636
  %1 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !637
  %call = call i8* @__archive_read_ahead(%struct.archive_read* %1, i64 512, i64* null), !dbg !638
  store i8* %call, i8** %h, align 8, !dbg !639
  %2 = load i8*, i8** %h, align 8, !dbg !640
  %cmp = icmp eq i8* %2, null, !dbg !642
  br i1 %cmp, label %if.then, label %if.end, !dbg !643

if.then:                                          ; preds = %entry
  store i32 -1, i32* %retval, align 4, !dbg !644
  br label %return, !dbg !644

if.end:                                           ; preds = %entry
  %3 = load i8*, i8** %h, align 8, !dbg !645
  %arrayidx = getelementptr inbounds i8, i8* %3, i64 0, !dbg !645
  %4 = load i8, i8* %arrayidx, align 1, !dbg !645
  %conv = sext i8 %4 to i32, !dbg !645
  %cmp1 = icmp eq i32 %conv, 0, !dbg !647
  br i1 %cmp1, label %land.lhs.true, label %if.end5, !dbg !648

land.lhs.true:                                    ; preds = %if.end
  %5 = load i8*, i8** %h, align 8, !dbg !649
  %call3 = call i32 @archive_block_is_null(i8* %5), !dbg !651
  %tobool = icmp ne i32 %call3, 0, !dbg !651
  br i1 %tobool, label %if.then4, label %if.end5, !dbg !652

if.then4:                                         ; preds = %land.lhs.true
  store i32 10, i32* %retval, align 4, !dbg !653
  br label %return, !dbg !653

if.end5:                                          ; preds = %land.lhs.true, %if.end
  %6 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !655
  %7 = load i8*, i8** %h, align 8, !dbg !657
  %call6 = call i32 @checksum(%struct.archive_read* %6, i8* %7), !dbg !658
  %tobool7 = icmp ne i32 %call6, 0, !dbg !658
  br i1 %tobool7, label %if.end9, label %if.then8, !dbg !659

if.then8:                                         ; preds = %if.end5
  store i32 0, i32* %retval, align 4, !dbg !660
  br label %return, !dbg !660

if.end9:                                          ; preds = %if.end5
  %8 = load i32, i32* %bid, align 4, !dbg !661
  %add = add nsw i32 %8, 48, !dbg !661
  store i32 %add, i32* %bid, align 4, !dbg !661
  %9 = load i8*, i8** %h, align 8, !dbg !662
  %10 = bitcast i8* %9 to %struct.archive_entry_header_ustar*, !dbg !663
  store %struct.archive_entry_header_ustar* %10, %struct.archive_entry_header_ustar** %header, align 8, !dbg !664
  %11 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !665
  %magic = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %11, i32 0, i32 9, !dbg !667
  %arraydecay = getelementptr inbounds [6 x i8], [6 x i8]* %magic, i32 0, i32 0, !dbg !665
  %call10 = call i32 @memcmp(i8* %arraydecay, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.4, i32 0, i32 0), i64 6) #8, !dbg !668
  %cmp11 = icmp eq i32 %call10, 0, !dbg !669
  br i1 %cmp11, label %land.lhs.true13, label %if.end20, !dbg !670

land.lhs.true13:                                  ; preds = %if.end9
  %12 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !671
  %version = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %12, i32 0, i32 10, !dbg !673
  %arraydecay14 = getelementptr inbounds [2 x i8], [2 x i8]* %version, i32 0, i32 0, !dbg !671
  %call15 = call i32 @memcmp(i8* %arraydecay14, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.5, i32 0, i32 0), i64 2) #8, !dbg !674
  %cmp16 = icmp eq i32 %call15, 0, !dbg !675
  br i1 %cmp16, label %if.then18, label %if.end20, !dbg !676

if.then18:                                        ; preds = %land.lhs.true13
  %13 = load i32, i32* %bid, align 4, !dbg !678
  %add19 = add nsw i32 %13, 56, !dbg !678
  store i32 %add19, i32* %bid, align 4, !dbg !678
  br label %if.end20, !dbg !679

if.end20:                                         ; preds = %if.then18, %land.lhs.true13, %if.end9
  %14 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !680
  %magic21 = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %14, i32 0, i32 9, !dbg !682
  %arraydecay22 = getelementptr inbounds [6 x i8], [6 x i8]* %magic21, i32 0, i32 0, !dbg !680
  %call23 = call i32 @memcmp(i8* %arraydecay22, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.6, i32 0, i32 0), i64 6) #8, !dbg !683
  %cmp24 = icmp eq i32 %call23, 0, !dbg !684
  br i1 %cmp24, label %land.lhs.true26, label %if.end34, !dbg !685

land.lhs.true26:                                  ; preds = %if.end20
  %15 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !686
  %version27 = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %15, i32 0, i32 10, !dbg !688
  %arraydecay28 = getelementptr inbounds [2 x i8], [2 x i8]* %version27, i32 0, i32 0, !dbg !686
  %call29 = call i32 @memcmp(i8* %arraydecay28, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.7, i32 0, i32 0), i64 2) #8, !dbg !689
  %cmp30 = icmp eq i32 %call29, 0, !dbg !690
  br i1 %cmp30, label %if.then32, label %if.end34, !dbg !691

if.then32:                                        ; preds = %land.lhs.true26
  %16 = load i32, i32* %bid, align 4, !dbg !692
  %add33 = add nsw i32 %16, 56, !dbg !692
  store i32 %add33, i32* %bid, align 4, !dbg !692
  br label %if.end34, !dbg !693

if.end34:                                         ; preds = %if.then32, %land.lhs.true26, %if.end20
  %17 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !694
  %typeflag = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %17, i32 0, i32 7, !dbg !696
  %arrayidx35 = getelementptr inbounds [1 x i8], [1 x i8]* %typeflag, i64 0, i64 0, !dbg !694
  %18 = load i8, i8* %arrayidx35, align 1, !dbg !694
  %conv36 = sext i8 %18 to i32, !dbg !694
  %cmp37 = icmp ne i32 %conv36, 0, !dbg !697
  br i1 %cmp37, label %land.lhs.true39, label %if.end76, !dbg !698

land.lhs.true39:                                  ; preds = %if.end34
  %19 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !699
  %typeflag40 = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %19, i32 0, i32 7, !dbg !700
  %arrayidx41 = getelementptr inbounds [1 x i8], [1 x i8]* %typeflag40, i64 0, i64 0, !dbg !699
  %20 = load i8, i8* %arrayidx41, align 1, !dbg !699
  %conv42 = sext i8 %20 to i32, !dbg !699
  %cmp43 = icmp sge i32 %conv42, 48, !dbg !701
  br i1 %cmp43, label %land.lhs.true45, label %land.lhs.true51, !dbg !702

land.lhs.true45:                                  ; preds = %land.lhs.true39
  %21 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !703
  %typeflag46 = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %21, i32 0, i32 7, !dbg !705
  %arrayidx47 = getelementptr inbounds [1 x i8], [1 x i8]* %typeflag46, i64 0, i64 0, !dbg !703
  %22 = load i8, i8* %arrayidx47, align 1, !dbg !703
  %conv48 = sext i8 %22 to i32, !dbg !703
  %cmp49 = icmp sle i32 %conv48, 57, !dbg !706
  br i1 %cmp49, label %if.end76, label %land.lhs.true51, !dbg !707

land.lhs.true51:                                  ; preds = %land.lhs.true45, %land.lhs.true39
  %23 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !708
  %typeflag52 = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %23, i32 0, i32 7, !dbg !709
  %arrayidx53 = getelementptr inbounds [1 x i8], [1 x i8]* %typeflag52, i64 0, i64 0, !dbg !708
  %24 = load i8, i8* %arrayidx53, align 1, !dbg !708
  %conv54 = sext i8 %24 to i32, !dbg !708
  %cmp55 = icmp sge i32 %conv54, 65, !dbg !710
  br i1 %cmp55, label %land.lhs.true57, label %land.lhs.true63, !dbg !711

land.lhs.true57:                                  ; preds = %land.lhs.true51
  %25 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !712
  %typeflag58 = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %25, i32 0, i32 7, !dbg !713
  %arrayidx59 = getelementptr inbounds [1 x i8], [1 x i8]* %typeflag58, i64 0, i64 0, !dbg !712
  %26 = load i8, i8* %arrayidx59, align 1, !dbg !712
  %conv60 = sext i8 %26 to i32, !dbg !712
  %cmp61 = icmp sle i32 %conv60, 90, !dbg !714
  br i1 %cmp61, label %if.end76, label %land.lhs.true63, !dbg !715

land.lhs.true63:                                  ; preds = %land.lhs.true57, %land.lhs.true51
  %27 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !716
  %typeflag64 = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %27, i32 0, i32 7, !dbg !717
  %arrayidx65 = getelementptr inbounds [1 x i8], [1 x i8]* %typeflag64, i64 0, i64 0, !dbg !716
  %28 = load i8, i8* %arrayidx65, align 1, !dbg !716
  %conv66 = sext i8 %28 to i32, !dbg !716
  %cmp67 = icmp sge i32 %conv66, 97, !dbg !718
  br i1 %cmp67, label %land.lhs.true69, label %if.then75, !dbg !719

land.lhs.true69:                                  ; preds = %land.lhs.true63
  %29 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !720
  %typeflag70 = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %29, i32 0, i32 7, !dbg !721
  %arrayidx71 = getelementptr inbounds [1 x i8], [1 x i8]* %typeflag70, i64 0, i64 0, !dbg !720
  %30 = load i8, i8* %arrayidx71, align 1, !dbg !720
  %conv72 = sext i8 %30 to i32, !dbg !720
  %cmp73 = icmp sle i32 %conv72, 122, !dbg !722
  br i1 %cmp73, label %if.end76, label %if.then75, !dbg !723

if.then75:                                        ; preds = %land.lhs.true69, %land.lhs.true63
  store i32 0, i32* %retval, align 4, !dbg !724
  br label %return, !dbg !724

if.end76:                                         ; preds = %land.lhs.true69, %land.lhs.true57, %land.lhs.true45, %if.end34
  %31 = load i32, i32* %bid, align 4, !dbg !725
  %add77 = add nsw i32 %31, 2, !dbg !725
  store i32 %add77, i32* %bid, align 4, !dbg !725
  %32 = load i32, i32* %bid, align 4, !dbg !726
  %cmp78 = icmp sgt i32 %32, 0, !dbg !728
  br i1 %cmp78, label %land.lhs.true80, label %if.end115, !dbg !729

land.lhs.true80:                                  ; preds = %if.end76
  %33 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !730
  %mode = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %33, i32 0, i32 1, !dbg !731
  %arraydecay81 = getelementptr inbounds [8 x i8], [8 x i8]* %mode, i32 0, i32 0, !dbg !730
  %call82 = call i32 @validate_number_field(i8* %arraydecay81, i64 8), !dbg !732
  %cmp83 = icmp eq i32 %call82, 0, !dbg !733
  br i1 %cmp83, label %if.then114, label %lor.lhs.false, !dbg !734

lor.lhs.false:                                    ; preds = %land.lhs.true80
  %34 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !735
  %uid = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %34, i32 0, i32 2, !dbg !737
  %arraydecay85 = getelementptr inbounds [8 x i8], [8 x i8]* %uid, i32 0, i32 0, !dbg !735
  %call86 = call i32 @validate_number_field(i8* %arraydecay85, i64 8), !dbg !738
  %cmp87 = icmp eq i32 %call86, 0, !dbg !739
  br i1 %cmp87, label %if.then114, label %lor.lhs.false89, !dbg !740

lor.lhs.false89:                                  ; preds = %lor.lhs.false
  %35 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !741
  %gid = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %35, i32 0, i32 3, !dbg !742
  %arraydecay90 = getelementptr inbounds [8 x i8], [8 x i8]* %gid, i32 0, i32 0, !dbg !741
  %call91 = call i32 @validate_number_field(i8* %arraydecay90, i64 8), !dbg !743
  %cmp92 = icmp eq i32 %call91, 0, !dbg !744
  br i1 %cmp92, label %if.then114, label %lor.lhs.false94, !dbg !745

lor.lhs.false94:                                  ; preds = %lor.lhs.false89
  %36 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !746
  %mtime = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %36, i32 0, i32 5, !dbg !747
  %arraydecay95 = getelementptr inbounds [12 x i8], [12 x i8]* %mtime, i32 0, i32 0, !dbg !746
  %call96 = call i32 @validate_number_field(i8* %arraydecay95, i64 12), !dbg !748
  %cmp97 = icmp eq i32 %call96, 0, !dbg !749
  br i1 %cmp97, label %if.then114, label %lor.lhs.false99, !dbg !750

lor.lhs.false99:                                  ; preds = %lor.lhs.false94
  %37 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !751
  %size = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %37, i32 0, i32 4, !dbg !752
  %arraydecay100 = getelementptr inbounds [12 x i8], [12 x i8]* %size, i32 0, i32 0, !dbg !751
  %call101 = call i32 @validate_number_field(i8* %arraydecay100, i64 12), !dbg !753
  %cmp102 = icmp eq i32 %call101, 0, !dbg !754
  br i1 %cmp102, label %if.then114, label %lor.lhs.false104, !dbg !755

lor.lhs.false104:                                 ; preds = %lor.lhs.false99
  %38 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !756
  %rdevmajor = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %38, i32 0, i32 13, !dbg !757
  %arraydecay105 = getelementptr inbounds [8 x i8], [8 x i8]* %rdevmajor, i32 0, i32 0, !dbg !756
  %call106 = call i32 @validate_number_field(i8* %arraydecay105, i64 8), !dbg !758
  %cmp107 = icmp eq i32 %call106, 0, !dbg !759
  br i1 %cmp107, label %if.then114, label %lor.lhs.false109, !dbg !760

lor.lhs.false109:                                 ; preds = %lor.lhs.false104
  %39 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !761
  %rdevminor = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %39, i32 0, i32 14, !dbg !762
  %arraydecay110 = getelementptr inbounds [8 x i8], [8 x i8]* %rdevminor, i32 0, i32 0, !dbg !761
  %call111 = call i32 @validate_number_field(i8* %arraydecay110, i64 8), !dbg !763
  %cmp112 = icmp eq i32 %call111, 0, !dbg !764
  br i1 %cmp112, label %if.then114, label %if.end115, !dbg !765

if.then114:                                       ; preds = %lor.lhs.false109, %lor.lhs.false104, %lor.lhs.false99, %lor.lhs.false94, %lor.lhs.false89, %lor.lhs.false, %land.lhs.true80
  store i32 0, i32* %bid, align 4, !dbg !766
  br label %if.end115, !dbg !768

if.end115:                                        ; preds = %if.then114, %lor.lhs.false109, %if.end76
  %40 = load i32, i32* %bid, align 4, !dbg !769
  store i32 %40, i32* %retval, align 4, !dbg !770
  br label %return, !dbg !770

return:                                           ; preds = %if.end115, %if.then75, %if.then8, %if.then4, %if.then
  %41 = load i32, i32* %retval, align 4, !dbg !771
  ret i32 %41, !dbg !771
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_read_format_tar_options(%struct.archive_read* %a, i8* %key, i8* %val) #0 !dbg !463 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %key.addr = alloca i8*, align 8
  %val.addr = alloca i8*, align 8
  %tar = alloca %struct.tar*, align 8
  %ret = alloca i32, align 4
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !772, metadata !563), !dbg !773
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !774, metadata !563), !dbg !775
  store i8* %val, i8** %val.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %val.addr, metadata !776, metadata !563), !dbg !777
  call void @llvm.dbg.declare(metadata %struct.tar** %tar, metadata !778, metadata !563), !dbg !779
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !780, metadata !563), !dbg !781
  store i32 -25, i32* %ret, align 4, !dbg !781
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !782
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 13, !dbg !783
  %1 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !783
  %data = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %1, i32 0, i32 0, !dbg !784
  %2 = load i8*, i8** %data, align 8, !dbg !784
  %3 = bitcast i8* %2 to %struct.tar*, !dbg !785
  store %struct.tar* %3, %struct.tar** %tar, align 8, !dbg !786
  %4 = load i8*, i8** %key.addr, align 8, !dbg !787
  %call = call i32 @strcmp(i8* %4, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.8, i32 0, i32 0)) #8, !dbg !789
  %cmp = icmp eq i32 %call, 0, !dbg !790
  br i1 %cmp, label %if.then, label %if.else, !dbg !791

if.then:                                          ; preds = %entry
  %5 = load i8*, i8** %val.addr, align 8, !dbg !792
  %cmp1 = icmp ne i8* %5, null, !dbg !794
  br i1 %cmp1, label %land.rhs, label %land.end, !dbg !795

land.rhs:                                         ; preds = %if.then
  %6 = load i8*, i8** %val.addr, align 8, !dbg !796
  %arrayidx = getelementptr inbounds i8, i8* %6, i64 0, !dbg !796
  %7 = load i8, i8* %arrayidx, align 1, !dbg !796
  %conv = sext i8 %7 to i32, !dbg !796
  %cmp2 = icmp ne i32 %conv, 0, !dbg !798
  br label %land.end

land.end:                                         ; preds = %land.rhs, %if.then
  %8 = phi i1 [ false, %if.then ], [ %cmp2, %land.rhs ]
  %land.ext = zext i1 %8 to i32, !dbg !799
  %9 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !801
  %compat_2x = getelementptr inbounds %struct.tar, %struct.tar* %9, i32 0, i32 32, !dbg !802
  store i32 %land.ext, i32* %compat_2x, align 4, !dbg !803
  %10 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !804
  %compat_2x4 = getelementptr inbounds %struct.tar, %struct.tar* %10, i32 0, i32 32, !dbg !805
  %11 = load i32, i32* %compat_2x4, align 4, !dbg !805
  %12 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !806
  %init_default_conversion = getelementptr inbounds %struct.tar, %struct.tar* %12, i32 0, i32 31, !dbg !807
  store i32 %11, i32* %init_default_conversion, align 8, !dbg !808
  store i32 0, i32* %retval, align 4, !dbg !809
  br label %return, !dbg !809

if.else:                                          ; preds = %entry
  %13 = load i8*, i8** %key.addr, align 8, !dbg !810
  %call5 = call i32 @strcmp(i8* %13, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.9, i32 0, i32 0)) #8, !dbg !812
  %cmp6 = icmp eq i32 %call5, 0, !dbg !813
  br i1 %cmp6, label %if.then8, label %if.else25, !dbg !814

if.then8:                                         ; preds = %if.else
  %14 = load i8*, i8** %val.addr, align 8, !dbg !815
  %cmp9 = icmp eq i8* %14, null, !dbg !818
  br i1 %cmp9, label %if.then15, label %lor.lhs.false, !dbg !819

lor.lhs.false:                                    ; preds = %if.then8
  %15 = load i8*, i8** %val.addr, align 8, !dbg !820
  %arrayidx11 = getelementptr inbounds i8, i8* %15, i64 0, !dbg !820
  %16 = load i8, i8* %arrayidx11, align 1, !dbg !820
  %conv12 = sext i8 %16 to i32, !dbg !820
  %cmp13 = icmp eq i32 %conv12, 0, !dbg !822
  br i1 %cmp13, label %if.then15, label %if.else16, !dbg !823

if.then15:                                        ; preds = %lor.lhs.false, %if.then8
  %17 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !824
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %17, i32 0, i32 0, !dbg !825
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 -1, i8* getelementptr inbounds ([50 x i8], [50 x i8]* @.str.10, i32 0, i32 0)), !dbg !826
  br label %if.end24, !dbg !826

if.else16:                                        ; preds = %lor.lhs.false
  %18 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !827
  %archive17 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %18, i32 0, i32 0, !dbg !829
  %19 = load i8*, i8** %val.addr, align 8, !dbg !830
  %call18 = call %struct.archive_string_conv* @archive_string_conversion_from_charset(%struct.archive* %archive17, i8* %19, i32 0), !dbg !831
  %20 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !832
  %opt_sconv = getelementptr inbounds %struct.tar, %struct.tar* %20, i32 0, i32 27, !dbg !833
  store %struct.archive_string_conv* %call18, %struct.archive_string_conv** %opt_sconv, align 8, !dbg !834
  %21 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !835
  %opt_sconv19 = getelementptr inbounds %struct.tar, %struct.tar* %21, i32 0, i32 27, !dbg !837
  %22 = load %struct.archive_string_conv*, %struct.archive_string_conv** %opt_sconv19, align 8, !dbg !837
  %cmp20 = icmp ne %struct.archive_string_conv* %22, null, !dbg !838
  br i1 %cmp20, label %if.then22, label %if.else23, !dbg !839

if.then22:                                        ; preds = %if.else16
  store i32 0, i32* %ret, align 4, !dbg !840
  br label %if.end, !dbg !841

if.else23:                                        ; preds = %if.else16
  store i32 -30, i32* %ret, align 4, !dbg !842
  br label %if.end

if.end:                                           ; preds = %if.else23, %if.then22
  br label %if.end24

if.end24:                                         ; preds = %if.end, %if.then15
  %23 = load i32, i32* %ret, align 4, !dbg !843
  store i32 %23, i32* %retval, align 4, !dbg !844
  br label %return, !dbg !844

if.else25:                                        ; preds = %if.else
  %24 = load i8*, i8** %key.addr, align 8, !dbg !845
  %call26 = call i32 @strcmp(i8* %24, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.11, i32 0, i32 0)) #8, !dbg !847
  %cmp27 = icmp eq i32 %call26, 0, !dbg !848
  br i1 %cmp27, label %if.then29, label %if.else39, !dbg !849

if.then29:                                        ; preds = %if.else25
  %25 = load i8*, i8** %val.addr, align 8, !dbg !850
  %cmp30 = icmp ne i8* %25, null, !dbg !852
  br i1 %cmp30, label %land.rhs32, label %land.end37, !dbg !853

land.rhs32:                                       ; preds = %if.then29
  %26 = load i8*, i8** %val.addr, align 8, !dbg !854
  %arrayidx33 = getelementptr inbounds i8, i8* %26, i64 0, !dbg !854
  %27 = load i8, i8* %arrayidx33, align 1, !dbg !854
  %conv34 = sext i8 %27 to i32, !dbg !854
  %cmp35 = icmp ne i32 %conv34, 0, !dbg !856
  br label %land.end37

land.end37:                                       ; preds = %land.rhs32, %if.then29
  %28 = phi i1 [ false, %if.then29 ], [ %cmp35, %land.rhs32 ]
  %land.ext38 = zext i1 %28 to i32, !dbg !857
  %29 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !859
  %process_mac_extensions = getelementptr inbounds %struct.tar, %struct.tar* %29, i32 0, i32 33, !dbg !860
  store i32 %land.ext38, i32* %process_mac_extensions, align 8, !dbg !861
  store i32 0, i32* %retval, align 4, !dbg !862
  br label %return, !dbg !862

if.else39:                                        ; preds = %if.else25
  %30 = load i8*, i8** %key.addr, align 8, !dbg !863
  %call40 = call i32 @strcmp(i8* %30, i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.12, i32 0, i32 0)) #8, !dbg !865
  %cmp41 = icmp eq i32 %call40, 0, !dbg !866
  br i1 %cmp41, label %if.then43, label %if.end53, !dbg !867

if.then43:                                        ; preds = %if.else39
  %31 = load i8*, i8** %val.addr, align 8, !dbg !868
  %cmp44 = icmp ne i8* %31, null, !dbg !870
  br i1 %cmp44, label %land.rhs46, label %land.end51, !dbg !871

land.rhs46:                                       ; preds = %if.then43
  %32 = load i8*, i8** %val.addr, align 8, !dbg !872
  %arrayidx47 = getelementptr inbounds i8, i8* %32, i64 0, !dbg !872
  %33 = load i8, i8* %arrayidx47, align 1, !dbg !872
  %conv48 = sext i8 %33 to i32, !dbg !872
  %cmp49 = icmp ne i32 %conv48, 0, !dbg !874
  br label %land.end51

land.end51:                                       ; preds = %land.rhs46, %if.then43
  %34 = phi i1 [ false, %if.then43 ], [ %cmp49, %land.rhs46 ]
  %land.ext52 = zext i1 %34 to i32, !dbg !875
  %35 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !877
  %read_concatenated_archives = getelementptr inbounds %struct.tar, %struct.tar* %35, i32 0, i32 34, !dbg !878
  store i32 %land.ext52, i32* %read_concatenated_archives, align 4, !dbg !879
  store i32 0, i32* %retval, align 4, !dbg !880
  br label %return, !dbg !880

if.end53:                                         ; preds = %if.else39
  br label %if.end54

if.end54:                                         ; preds = %if.end53
  br label %if.end55

if.end55:                                         ; preds = %if.end54
  br label %if.end56

if.end56:                                         ; preds = %if.end55
  store i32 -20, i32* %retval, align 4, !dbg !881
  br label %return, !dbg !881

return:                                           ; preds = %if.end56, %land.end51, %land.end37, %if.end24, %land.end
  %36 = load i32, i32* %retval, align 4, !dbg !882
  ret i32 %36, !dbg !882
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_read_format_tar_read_header(%struct.archive_read* %a, %struct.archive_entry* %entry1) #0 !dbg !464 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %tar = alloca %struct.tar*, align 8
  %p = alloca i8*, align 8
  %wp = alloca i32*, align 8
  %r = alloca i32, align 4
  %l = alloca i64, align 8
  %unconsumed = alloca i64, align 8
  %sb = alloca %struct.sparse_block*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !883, metadata !563), !dbg !884
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !885, metadata !563), !dbg !886
  call void @llvm.dbg.declare(metadata %struct.tar** %tar, metadata !887, metadata !563), !dbg !888
  call void @llvm.dbg.declare(metadata i8** %p, metadata !889, metadata !563), !dbg !890
  call void @llvm.dbg.declare(metadata i32** %wp, metadata !891, metadata !563), !dbg !895
  call void @llvm.dbg.declare(metadata i32* %r, metadata !896, metadata !563), !dbg !897
  call void @llvm.dbg.declare(metadata i64* %l, metadata !898, metadata !563), !dbg !899
  call void @llvm.dbg.declare(metadata i64* %unconsumed, metadata !900, metadata !563), !dbg !901
  store i64 0, i64* %unconsumed, align 8, !dbg !901
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !902
  %1 = load i32, i32* @archive_read_format_tar_read_header.default_dev, align 4, !dbg !903
  %add = add nsw i32 1, %1, !dbg !904
  %conv = sext i32 %add to i64, !dbg !905
  call void @archive_entry_set_dev(%struct.archive_entry* %0, i64 %conv), !dbg !906
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !907
  %3 = load i32, i32* @archive_read_format_tar_read_header.default_inode, align 4, !dbg !908
  %inc = add nsw i32 %3, 1, !dbg !908
  store i32 %inc, i32* @archive_read_format_tar_read_header.default_inode, align 4, !dbg !908
  %conv2 = sext i32 %inc to i64, !dbg !908
  call void @archive_entry_set_ino(%struct.archive_entry* %2, i64 %conv2), !dbg !909
  %4 = load i32, i32* @archive_read_format_tar_read_header.default_inode, align 4, !dbg !910
  %cmp = icmp sge i32 %4, 65535, !dbg !912
  br i1 %cmp, label %if.then, label %if.end, !dbg !913

if.then:                                          ; preds = %entry
  %5 = load i32, i32* @archive_read_format_tar_read_header.default_dev, align 4, !dbg !914
  %inc4 = add nsw i32 %5, 1, !dbg !914
  store i32 %inc4, i32* @archive_read_format_tar_read_header.default_dev, align 4, !dbg !914
  store i32 0, i32* @archive_read_format_tar_read_header.default_inode, align 4, !dbg !916
  br label %if.end, !dbg !917

if.end:                                           ; preds = %if.then, %entry
  %6 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !918
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %6, i32 0, i32 13, !dbg !919
  %7 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !919
  %data = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %7, i32 0, i32 0, !dbg !920
  %8 = load i8*, i8** %data, align 8, !dbg !920
  %9 = bitcast i8* %8 to %struct.tar*, !dbg !921
  store %struct.tar* %9, %struct.tar** %tar, align 8, !dbg !922
  %10 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !923
  %entry_offset = getelementptr inbounds %struct.tar, %struct.tar* %10, i32 0, i32 14, !dbg !924
  store i64 0, i64* %entry_offset, align 8, !dbg !925
  %11 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !926
  call void @gnu_clear_sparse_list(%struct.tar* %11), !dbg !927
  %12 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !928
  %realsize = getelementptr inbounds %struct.tar, %struct.tar* %12, i32 0, i32 17, !dbg !929
  store i64 -1, i64* %realsize, align 8, !dbg !930
  %13 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !931
  %opt_sconv = getelementptr inbounds %struct.tar, %struct.tar* %13, i32 0, i32 27, !dbg !932
  %14 = load %struct.archive_string_conv*, %struct.archive_string_conv** %opt_sconv, align 8, !dbg !932
  %15 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !933
  %sconv = getelementptr inbounds %struct.tar, %struct.tar* %15, i32 0, i32 28, !dbg !934
  store %struct.archive_string_conv* %14, %struct.archive_string_conv** %sconv, align 8, !dbg !935
  %16 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !936
  %sconv5 = getelementptr inbounds %struct.tar, %struct.tar* %16, i32 0, i32 28, !dbg !938
  %17 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv5, align 8, !dbg !938
  %cmp6 = icmp eq %struct.archive_string_conv* %17, null, !dbg !939
  br i1 %cmp6, label %if.then8, label %if.end14, !dbg !940

if.then8:                                         ; preds = %if.end
  %18 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !941
  %init_default_conversion = getelementptr inbounds %struct.tar, %struct.tar* %18, i32 0, i32 31, !dbg !944
  %19 = load i32, i32* %init_default_conversion, align 8, !dbg !944
  %tobool = icmp ne i32 %19, 0, !dbg !941
  br i1 %tobool, label %if.end11, label %if.then9, !dbg !945

if.then9:                                         ; preds = %if.then8
  %20 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !946
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %20, i32 0, i32 0, !dbg !948
  %call = call %struct.archive_string_conv* @archive_string_default_conversion_for_read(%struct.archive* %archive), !dbg !949
  %21 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !950
  %sconv_default = getelementptr inbounds %struct.tar, %struct.tar* %21, i32 0, i32 30, !dbg !951
  store %struct.archive_string_conv* %call, %struct.archive_string_conv** %sconv_default, align 8, !dbg !952
  %22 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !953
  %init_default_conversion10 = getelementptr inbounds %struct.tar, %struct.tar* %22, i32 0, i32 31, !dbg !954
  store i32 1, i32* %init_default_conversion10, align 8, !dbg !955
  br label %if.end11, !dbg !956

if.end11:                                         ; preds = %if.then9, %if.then8
  %23 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !957
  %sconv_default12 = getelementptr inbounds %struct.tar, %struct.tar* %23, i32 0, i32 30, !dbg !958
  %24 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv_default12, align 8, !dbg !958
  %25 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !959
  %sconv13 = getelementptr inbounds %struct.tar, %struct.tar* %25, i32 0, i32 28, !dbg !960
  store %struct.archive_string_conv* %24, %struct.archive_string_conv** %sconv13, align 8, !dbg !961
  br label %if.end14, !dbg !962

if.end14:                                         ; preds = %if.end11, %if.end
  %26 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !963
  %27 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !964
  %28 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !965
  %call15 = call i32 @tar_read_header(%struct.archive_read* %26, %struct.tar* %27, %struct.archive_entry* %28, i64* %unconsumed), !dbg !966
  store i32 %call15, i32* %r, align 4, !dbg !967
  %29 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !968
  call void @tar_flush_unconsumed(%struct.archive_read* %29, i64* %unconsumed), !dbg !969
  %30 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !970
  %sparse_list = getelementptr inbounds %struct.tar, %struct.tar* %30, i32 0, i32 19, !dbg !972
  %31 = load %struct.sparse_block*, %struct.sparse_block** %sparse_list, align 8, !dbg !972
  %cmp16 = icmp eq %struct.sparse_block* %31, null, !dbg !973
  br i1 %cmp16, label %if.then18, label %if.else, !dbg !974

if.then18:                                        ; preds = %if.end14
  %32 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !975
  %33 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !978
  %34 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !979
  %entry_bytes_remaining = getelementptr inbounds %struct.tar, %struct.tar* %34, i32 0, i32 13, !dbg !980
  %35 = load i64, i64* %entry_bytes_remaining, align 8, !dbg !980
  %call19 = call i32 @gnu_add_sparse_entry(%struct.archive_read* %32, %struct.tar* %33, i64 0, i64 %35), !dbg !981
  %cmp20 = icmp ne i32 %call19, 0, !dbg !982
  br i1 %cmp20, label %if.then22, label %if.end23, !dbg !983

if.then22:                                        ; preds = %if.then18
  store i32 -30, i32* %retval, align 4, !dbg !984
  br label %return, !dbg !984

if.end23:                                         ; preds = %if.then18
  br label %if.end30, !dbg !985

if.else:                                          ; preds = %if.end14
  call void @llvm.dbg.declare(metadata %struct.sparse_block** %sb, metadata !986, metadata !563), !dbg !988
  %36 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !989
  %sparse_list24 = getelementptr inbounds %struct.tar, %struct.tar* %36, i32 0, i32 19, !dbg !991
  %37 = load %struct.sparse_block*, %struct.sparse_block** %sparse_list24, align 8, !dbg !991
  store %struct.sparse_block* %37, %struct.sparse_block** %sb, align 8, !dbg !992
  br label %for.cond, !dbg !993

for.cond:                                         ; preds = %for.inc, %if.else
  %38 = load %struct.sparse_block*, %struct.sparse_block** %sb, align 8, !dbg !994
  %cmp25 = icmp ne %struct.sparse_block* %38, null, !dbg !997
  br i1 %cmp25, label %for.body, label %for.end, !dbg !998

for.body:                                         ; preds = %for.cond
  %39 = load %struct.sparse_block*, %struct.sparse_block** %sb, align 8, !dbg !999
  %hole = getelementptr inbounds %struct.sparse_block, %struct.sparse_block* %39, i32 0, i32 3, !dbg !1002
  %40 = load i32, i32* %hole, align 8, !dbg !1002
  %tobool27 = icmp ne i32 %40, 0, !dbg !999
  br i1 %tobool27, label %if.end29, label %if.then28, !dbg !1003

if.then28:                                        ; preds = %for.body
  %41 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1004
  %42 = load %struct.sparse_block*, %struct.sparse_block** %sb, align 8, !dbg !1005
  %offset = getelementptr inbounds %struct.sparse_block, %struct.sparse_block* %42, i32 0, i32 1, !dbg !1006
  %43 = load i64, i64* %offset, align 8, !dbg !1006
  %44 = load %struct.sparse_block*, %struct.sparse_block** %sb, align 8, !dbg !1007
  %remaining = getelementptr inbounds %struct.sparse_block, %struct.sparse_block* %44, i32 0, i32 2, !dbg !1008
  %45 = load i64, i64* %remaining, align 8, !dbg !1008
  call void @archive_entry_sparse_add_entry(%struct.archive_entry* %41, i64 %43, i64 %45), !dbg !1009
  br label %if.end29, !dbg !1009

if.end29:                                         ; preds = %if.then28, %for.body
  br label %for.inc, !dbg !1010

for.inc:                                          ; preds = %if.end29
  %46 = load %struct.sparse_block*, %struct.sparse_block** %sb, align 8, !dbg !1011
  %next = getelementptr inbounds %struct.sparse_block, %struct.sparse_block* %46, i32 0, i32 0, !dbg !1013
  %47 = load %struct.sparse_block*, %struct.sparse_block** %next, align 8, !dbg !1013
  store %struct.sparse_block* %47, %struct.sparse_block** %sb, align 8, !dbg !1014
  br label %for.cond, !dbg !1015

for.end:                                          ; preds = %for.cond
  br label %if.end30

if.end30:                                         ; preds = %for.end, %if.end23
  %48 = load i32, i32* %r, align 4, !dbg !1016
  %cmp31 = icmp eq i32 %48, 0, !dbg !1018
  br i1 %cmp31, label %land.lhs.true, label %if.end67, !dbg !1019

land.lhs.true:                                    ; preds = %if.end30
  %49 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1020
  %call33 = call i32 @archive_entry_filetype(%struct.archive_entry* %49), !dbg !1022
  %cmp34 = icmp eq i32 %call33, 32768, !dbg !1023
  br i1 %cmp34, label %if.then36, label %if.end67, !dbg !1024

if.then36:                                        ; preds = %land.lhs.true
  %50 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1025
  %call37 = call i32* @archive_entry_pathname_w(%struct.archive_entry* %50), !dbg !1028
  store i32* %call37, i32** %wp, align 8, !dbg !1029
  %cmp38 = icmp ne i32* %call37, null, !dbg !1030
  br i1 %cmp38, label %if.then40, label %if.else49, !dbg !1031

if.then40:                                        ; preds = %if.then36
  %51 = load i32*, i32** %wp, align 8, !dbg !1032
  %call41 = call i64 @wcslen(i32* %51) #8, !dbg !1034
  store i64 %call41, i64* %l, align 8, !dbg !1035
  %52 = load i64, i64* %l, align 8, !dbg !1036
  %cmp42 = icmp ugt i64 %52, 0, !dbg !1038
  br i1 %cmp42, label %land.lhs.true44, label %if.end48, !dbg !1039

land.lhs.true44:                                  ; preds = %if.then40
  %53 = load i64, i64* %l, align 8, !dbg !1040
  %sub = sub i64 %53, 1, !dbg !1042
  %54 = load i32*, i32** %wp, align 8, !dbg !1043
  %arrayidx = getelementptr inbounds i32, i32* %54, i64 %sub, !dbg !1043
  %55 = load i32, i32* %arrayidx, align 4, !dbg !1043
  %cmp45 = icmp eq i32 %55, 47, !dbg !1044
  br i1 %cmp45, label %if.then47, label %if.end48, !dbg !1045

if.then47:                                        ; preds = %land.lhs.true44
  %56 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1046
  call void @archive_entry_set_filetype(%struct.archive_entry* %56, i32 16384), !dbg !1048
  br label %if.end48, !dbg !1049

if.end48:                                         ; preds = %if.then47, %land.lhs.true44, %if.then40
  br label %if.end66, !dbg !1050

if.else49:                                        ; preds = %if.then36
  %57 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1051
  %call50 = call i8* @archive_entry_pathname(%struct.archive_entry* %57), !dbg !1054
  store i8* %call50, i8** %p, align 8, !dbg !1055
  %cmp51 = icmp ne i8* %call50, null, !dbg !1056
  br i1 %cmp51, label %if.then53, label %if.end65, !dbg !1057

if.then53:                                        ; preds = %if.else49
  %58 = load i8*, i8** %p, align 8, !dbg !1058
  %call54 = call i64 @strlen(i8* %58) #8, !dbg !1060
  store i64 %call54, i64* %l, align 8, !dbg !1061
  %59 = load i64, i64* %l, align 8, !dbg !1062
  %cmp55 = icmp ugt i64 %59, 0, !dbg !1064
  br i1 %cmp55, label %land.lhs.true57, label %if.end64, !dbg !1065

land.lhs.true57:                                  ; preds = %if.then53
  %60 = load i64, i64* %l, align 8, !dbg !1066
  %sub58 = sub i64 %60, 1, !dbg !1068
  %61 = load i8*, i8** %p, align 8, !dbg !1069
  %arrayidx59 = getelementptr inbounds i8, i8* %61, i64 %sub58, !dbg !1069
  %62 = load i8, i8* %arrayidx59, align 1, !dbg !1069
  %conv60 = sext i8 %62 to i32, !dbg !1069
  %cmp61 = icmp eq i32 %conv60, 47, !dbg !1070
  br i1 %cmp61, label %if.then63, label %if.end64, !dbg !1071

if.then63:                                        ; preds = %land.lhs.true57
  %63 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1072
  call void @archive_entry_set_filetype(%struct.archive_entry* %63, i32 16384), !dbg !1074
  br label %if.end64, !dbg !1075

if.end64:                                         ; preds = %if.then63, %land.lhs.true57, %if.then53
  br label %if.end65, !dbg !1076

if.end65:                                         ; preds = %if.end64, %if.else49
  br label %if.end66

if.end66:                                         ; preds = %if.end65, %if.end48
  br label %if.end67, !dbg !1077

if.end67:                                         ; preds = %if.end66, %land.lhs.true, %if.end30
  %64 = load i32, i32* %r, align 4, !dbg !1078
  store i32 %64, i32* %retval, align 4, !dbg !1079
  br label %return, !dbg !1079

return:                                           ; preds = %if.end67, %if.then22
  %65 = load i32, i32* %retval, align 4, !dbg !1080
  ret i32 %65, !dbg !1080
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_read_format_tar_read_data(%struct.archive_read* %a, i8** %buff, i64* %size, i64* %offset) #0 !dbg !546 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %buff.addr = alloca i8**, align 8
  %size.addr = alloca i64*, align 8
  %offset.addr = alloca i64*, align 8
  %bytes_read = alloca i64, align 8
  %tar = alloca %struct.tar*, align 8
  %p = alloca %struct.sparse_block*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !1081, metadata !563), !dbg !1082
  store i8** %buff, i8*** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %buff.addr, metadata !1083, metadata !563), !dbg !1084
  store i64* %size, i64** %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %size.addr, metadata !1085, metadata !563), !dbg !1086
  store i64* %offset, i64** %offset.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %offset.addr, metadata !1087, metadata !563), !dbg !1088
  call void @llvm.dbg.declare(metadata i64* %bytes_read, metadata !1089, metadata !563), !dbg !1090
  call void @llvm.dbg.declare(metadata %struct.tar** %tar, metadata !1091, metadata !563), !dbg !1092
  call void @llvm.dbg.declare(metadata %struct.sparse_block** %p, metadata !1093, metadata !563), !dbg !1094
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1095
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 13, !dbg !1096
  %1 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !1096
  %data = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %1, i32 0, i32 0, !dbg !1097
  %2 = load i8*, i8** %data, align 8, !dbg !1097
  %3 = bitcast i8* %2 to %struct.tar*, !dbg !1098
  store %struct.tar* %3, %struct.tar** %tar, align 8, !dbg !1099
  br label %for.cond, !dbg !1100

for.cond:                                         ; preds = %if.end48, %entry
  br label %while.cond, !dbg !1101

while.cond:                                       ; preds = %while.body, %for.cond
  %4 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1105
  %sparse_list = getelementptr inbounds %struct.tar, %struct.tar* %4, i32 0, i32 19, !dbg !1107
  %5 = load %struct.sparse_block*, %struct.sparse_block** %sparse_list, align 8, !dbg !1107
  %cmp = icmp ne %struct.sparse_block* %5, null, !dbg !1108
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !1109

land.rhs:                                         ; preds = %while.cond
  %6 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1110
  %sparse_list1 = getelementptr inbounds %struct.tar, %struct.tar* %6, i32 0, i32 19, !dbg !1111
  %7 = load %struct.sparse_block*, %struct.sparse_block** %sparse_list1, align 8, !dbg !1111
  %remaining = getelementptr inbounds %struct.sparse_block, %struct.sparse_block* %7, i32 0, i32 2, !dbg !1112
  %8 = load i64, i64* %remaining, align 8, !dbg !1112
  %cmp2 = icmp eq i64 %8, 0, !dbg !1113
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond
  %9 = phi i1 [ false, %while.cond ], [ %cmp2, %land.rhs ]
  br i1 %9, label %while.body, label %while.end, !dbg !1114

while.body:                                       ; preds = %land.end
  %10 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1116
  %sparse_list3 = getelementptr inbounds %struct.tar, %struct.tar* %10, i32 0, i32 19, !dbg !1118
  %11 = load %struct.sparse_block*, %struct.sparse_block** %sparse_list3, align 8, !dbg !1118
  store %struct.sparse_block* %11, %struct.sparse_block** %p, align 8, !dbg !1119
  %12 = load %struct.sparse_block*, %struct.sparse_block** %p, align 8, !dbg !1120
  %next = getelementptr inbounds %struct.sparse_block, %struct.sparse_block* %12, i32 0, i32 0, !dbg !1121
  %13 = load %struct.sparse_block*, %struct.sparse_block** %next, align 8, !dbg !1121
  %14 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1122
  %sparse_list4 = getelementptr inbounds %struct.tar, %struct.tar* %14, i32 0, i32 19, !dbg !1123
  store %struct.sparse_block* %13, %struct.sparse_block** %sparse_list4, align 8, !dbg !1124
  %15 = load %struct.sparse_block*, %struct.sparse_block** %p, align 8, !dbg !1125
  %16 = bitcast %struct.sparse_block* %15 to i8*, !dbg !1125
  call void @free(i8* %16) #7, !dbg !1126
  br label %while.cond, !dbg !1127

while.end:                                        ; preds = %land.end
  %17 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1129
  %entry_bytes_unconsumed = getelementptr inbounds %struct.tar, %struct.tar* %17, i32 0, i32 16, !dbg !1131
  %18 = load i64, i64* %entry_bytes_unconsumed, align 8, !dbg !1131
  %tobool = icmp ne i64 %18, 0, !dbg !1129
  br i1 %tobool, label %if.then, label %if.end, !dbg !1132

if.then:                                          ; preds = %while.end
  %19 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1133
  %20 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1135
  %entry_bytes_unconsumed5 = getelementptr inbounds %struct.tar, %struct.tar* %20, i32 0, i32 16, !dbg !1136
  %21 = load i64, i64* %entry_bytes_unconsumed5, align 8, !dbg !1136
  %call = call i64 @__archive_read_consume(%struct.archive_read* %19, i64 %21), !dbg !1137
  %22 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1138
  %entry_bytes_unconsumed6 = getelementptr inbounds %struct.tar, %struct.tar* %22, i32 0, i32 16, !dbg !1139
  store i64 0, i64* %entry_bytes_unconsumed6, align 8, !dbg !1140
  br label %if.end, !dbg !1141

if.end:                                           ; preds = %if.then, %while.end
  %23 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1142
  %sparse_list7 = getelementptr inbounds %struct.tar, %struct.tar* %23, i32 0, i32 19, !dbg !1144
  %24 = load %struct.sparse_block*, %struct.sparse_block** %sparse_list7, align 8, !dbg !1144
  %cmp8 = icmp eq %struct.sparse_block* %24, null, !dbg !1145
  br i1 %cmp8, label %if.then10, label %lor.lhs.false, !dbg !1146

lor.lhs.false:                                    ; preds = %if.end
  %25 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1147
  %entry_bytes_remaining = getelementptr inbounds %struct.tar, %struct.tar* %25, i32 0, i32 13, !dbg !1148
  %26 = load i64, i64* %entry_bytes_remaining, align 8, !dbg !1148
  %cmp9 = icmp eq i64 %26, 0, !dbg !1149
  br i1 %cmp9, label %if.then10, label %if.end16, !dbg !1150

if.then10:                                        ; preds = %lor.lhs.false, %if.end
  %27 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1151
  %28 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1154
  %entry_padding = getelementptr inbounds %struct.tar, %struct.tar* %28, i32 0, i32 15, !dbg !1155
  %29 = load i64, i64* %entry_padding, align 8, !dbg !1155
  %call11 = call i64 @__archive_read_consume(%struct.archive_read* %27, i64 %29), !dbg !1156
  %cmp12 = icmp slt i64 %call11, 0, !dbg !1157
  br i1 %cmp12, label %if.then13, label %if.end14, !dbg !1158

if.then13:                                        ; preds = %if.then10
  store i32 -30, i32* %retval, align 4, !dbg !1159
  br label %return, !dbg !1159

if.end14:                                         ; preds = %if.then10
  %30 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1160
  %entry_padding15 = getelementptr inbounds %struct.tar, %struct.tar* %30, i32 0, i32 15, !dbg !1161
  store i64 0, i64* %entry_padding15, align 8, !dbg !1162
  %31 = load i8**, i8*** %buff.addr, align 8, !dbg !1163
  store i8* null, i8** %31, align 8, !dbg !1164
  %32 = load i64*, i64** %size.addr, align 8, !dbg !1165
  store i64 0, i64* %32, align 8, !dbg !1166
  %33 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1167
  %realsize = getelementptr inbounds %struct.tar, %struct.tar* %33, i32 0, i32 17, !dbg !1168
  %34 = load i64, i64* %realsize, align 8, !dbg !1168
  %35 = load i64*, i64** %offset.addr, align 8, !dbg !1169
  store i64 %34, i64* %35, align 8, !dbg !1170
  store i32 1, i32* %retval, align 4, !dbg !1171
  br label %return, !dbg !1171

if.end16:                                         ; preds = %lor.lhs.false
  %36 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1172
  %call17 = call i8* @__archive_read_ahead(%struct.archive_read* %36, i64 1, i64* %bytes_read), !dbg !1173
  %37 = load i8**, i8*** %buff.addr, align 8, !dbg !1174
  store i8* %call17, i8** %37, align 8, !dbg !1175
  %38 = load i64, i64* %bytes_read, align 8, !dbg !1176
  %cmp18 = icmp slt i64 %38, 0, !dbg !1178
  br i1 %cmp18, label %if.then19, label %if.end20, !dbg !1179

if.then19:                                        ; preds = %if.end16
  store i32 -30, i32* %retval, align 4, !dbg !1180
  br label %return, !dbg !1180

if.end20:                                         ; preds = %if.end16
  %39 = load i8**, i8*** %buff.addr, align 8, !dbg !1181
  %40 = load i8*, i8** %39, align 8, !dbg !1183
  %cmp21 = icmp eq i8* %40, null, !dbg !1184
  br i1 %cmp21, label %if.then22, label %if.end23, !dbg !1185

if.then22:                                        ; preds = %if.end20
  %41 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1186
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %41, i32 0, i32 0, !dbg !1188
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 -1, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.13, i32 0, i32 0)), !dbg !1189
  store i32 -30, i32* %retval, align 4, !dbg !1190
  br label %return, !dbg !1190

if.end23:                                         ; preds = %if.end20
  %42 = load i64, i64* %bytes_read, align 8, !dbg !1191
  %43 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1193
  %entry_bytes_remaining24 = getelementptr inbounds %struct.tar, %struct.tar* %43, i32 0, i32 13, !dbg !1194
  %44 = load i64, i64* %entry_bytes_remaining24, align 8, !dbg !1194
  %cmp25 = icmp sgt i64 %42, %44, !dbg !1195
  br i1 %cmp25, label %if.then26, label %if.end28, !dbg !1196

if.then26:                                        ; preds = %if.end23
  %45 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1197
  %entry_bytes_remaining27 = getelementptr inbounds %struct.tar, %struct.tar* %45, i32 0, i32 13, !dbg !1198
  %46 = load i64, i64* %entry_bytes_remaining27, align 8, !dbg !1198
  store i64 %46, i64* %bytes_read, align 8, !dbg !1199
  br label %if.end28, !dbg !1200

if.end28:                                         ; preds = %if.then26, %if.end23
  %47 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1201
  %sparse_list29 = getelementptr inbounds %struct.tar, %struct.tar* %47, i32 0, i32 19, !dbg !1203
  %48 = load %struct.sparse_block*, %struct.sparse_block** %sparse_list29, align 8, !dbg !1203
  %remaining30 = getelementptr inbounds %struct.sparse_block, %struct.sparse_block* %48, i32 0, i32 2, !dbg !1204
  %49 = load i64, i64* %remaining30, align 8, !dbg !1204
  %50 = load i64, i64* %bytes_read, align 8, !dbg !1205
  %cmp31 = icmp slt i64 %49, %50, !dbg !1206
  br i1 %cmp31, label %if.then32, label %if.end35, !dbg !1207

if.then32:                                        ; preds = %if.end28
  %51 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1208
  %sparse_list33 = getelementptr inbounds %struct.tar, %struct.tar* %51, i32 0, i32 19, !dbg !1209
  %52 = load %struct.sparse_block*, %struct.sparse_block** %sparse_list33, align 8, !dbg !1209
  %remaining34 = getelementptr inbounds %struct.sparse_block, %struct.sparse_block* %52, i32 0, i32 2, !dbg !1210
  %53 = load i64, i64* %remaining34, align 8, !dbg !1210
  store i64 %53, i64* %bytes_read, align 8, !dbg !1211
  br label %if.end35, !dbg !1212

if.end35:                                         ; preds = %if.then32, %if.end28
  %54 = load i64, i64* %bytes_read, align 8, !dbg !1213
  %55 = load i64*, i64** %size.addr, align 8, !dbg !1214
  store i64 %54, i64* %55, align 8, !dbg !1215
  %56 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1216
  %sparse_list36 = getelementptr inbounds %struct.tar, %struct.tar* %56, i32 0, i32 19, !dbg !1217
  %57 = load %struct.sparse_block*, %struct.sparse_block** %sparse_list36, align 8, !dbg !1217
  %offset37 = getelementptr inbounds %struct.sparse_block, %struct.sparse_block* %57, i32 0, i32 1, !dbg !1218
  %58 = load i64, i64* %offset37, align 8, !dbg !1218
  %59 = load i64*, i64** %offset.addr, align 8, !dbg !1219
  store i64 %58, i64* %59, align 8, !dbg !1220
  %60 = load i64, i64* %bytes_read, align 8, !dbg !1221
  %61 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1222
  %sparse_list38 = getelementptr inbounds %struct.tar, %struct.tar* %61, i32 0, i32 19, !dbg !1223
  %62 = load %struct.sparse_block*, %struct.sparse_block** %sparse_list38, align 8, !dbg !1223
  %remaining39 = getelementptr inbounds %struct.sparse_block, %struct.sparse_block* %62, i32 0, i32 2, !dbg !1224
  %63 = load i64, i64* %remaining39, align 8, !dbg !1225
  %sub = sub nsw i64 %63, %60, !dbg !1225
  store i64 %sub, i64* %remaining39, align 8, !dbg !1225
  %64 = load i64, i64* %bytes_read, align 8, !dbg !1226
  %65 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1227
  %sparse_list40 = getelementptr inbounds %struct.tar, %struct.tar* %65, i32 0, i32 19, !dbg !1228
  %66 = load %struct.sparse_block*, %struct.sparse_block** %sparse_list40, align 8, !dbg !1228
  %offset41 = getelementptr inbounds %struct.sparse_block, %struct.sparse_block* %66, i32 0, i32 1, !dbg !1229
  %67 = load i64, i64* %offset41, align 8, !dbg !1230
  %add = add nsw i64 %67, %64, !dbg !1230
  store i64 %add, i64* %offset41, align 8, !dbg !1230
  %68 = load i64, i64* %bytes_read, align 8, !dbg !1231
  %69 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1232
  %entry_bytes_remaining42 = getelementptr inbounds %struct.tar, %struct.tar* %69, i32 0, i32 13, !dbg !1233
  %70 = load i64, i64* %entry_bytes_remaining42, align 8, !dbg !1234
  %sub43 = sub nsw i64 %70, %68, !dbg !1234
  store i64 %sub43, i64* %entry_bytes_remaining42, align 8, !dbg !1234
  %71 = load i64, i64* %bytes_read, align 8, !dbg !1235
  %72 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1236
  %entry_bytes_unconsumed44 = getelementptr inbounds %struct.tar, %struct.tar* %72, i32 0, i32 16, !dbg !1237
  store i64 %71, i64* %entry_bytes_unconsumed44, align 8, !dbg !1238
  %73 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1239
  %sparse_list45 = getelementptr inbounds %struct.tar, %struct.tar* %73, i32 0, i32 19, !dbg !1241
  %74 = load %struct.sparse_block*, %struct.sparse_block** %sparse_list45, align 8, !dbg !1241
  %hole = getelementptr inbounds %struct.sparse_block, %struct.sparse_block* %74, i32 0, i32 3, !dbg !1242
  %75 = load i32, i32* %hole, align 8, !dbg !1242
  %tobool46 = icmp ne i32 %75, 0, !dbg !1239
  br i1 %tobool46, label %if.end48, label %if.then47, !dbg !1243

if.then47:                                        ; preds = %if.end35
  store i32 0, i32* %retval, align 4, !dbg !1244
  br label %return, !dbg !1244

if.end48:                                         ; preds = %if.end35
  br label %for.cond, !dbg !1245

return:                                           ; preds = %if.then47, %if.then22, %if.then19, %if.end14, %if.then13
  %76 = load i32, i32* %retval, align 4, !dbg !1247
  ret i32 %76, !dbg !1247
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_read_format_tar_skip(%struct.archive_read* %a) #0 !dbg !547 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %bytes_skipped = alloca i64, align 8
  %request = alloca i64, align 8
  %p = alloca %struct.sparse_block*, align 8
  %tar = alloca %struct.tar*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !1248, metadata !563), !dbg !1249
  call void @llvm.dbg.declare(metadata i64* %bytes_skipped, metadata !1250, metadata !563), !dbg !1251
  call void @llvm.dbg.declare(metadata i64* %request, metadata !1252, metadata !563), !dbg !1253
  call void @llvm.dbg.declare(metadata %struct.sparse_block** %p, metadata !1254, metadata !563), !dbg !1255
  call void @llvm.dbg.declare(metadata %struct.tar** %tar, metadata !1256, metadata !563), !dbg !1257
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1258
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 13, !dbg !1259
  %1 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !1259
  %data = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %1, i32 0, i32 0, !dbg !1260
  %2 = load i8*, i8** %data, align 8, !dbg !1260
  %3 = bitcast i8* %2 to %struct.tar*, !dbg !1261
  store %struct.tar* %3, %struct.tar** %tar, align 8, !dbg !1262
  store i64 0, i64* %request, align 8, !dbg !1263
  %4 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1264
  %sparse_list = getelementptr inbounds %struct.tar, %struct.tar* %4, i32 0, i32 19, !dbg !1266
  %5 = load %struct.sparse_block*, %struct.sparse_block** %sparse_list, align 8, !dbg !1266
  store %struct.sparse_block* %5, %struct.sparse_block** %p, align 8, !dbg !1267
  br label %for.cond, !dbg !1268

for.cond:                                         ; preds = %for.inc, %entry
  %6 = load %struct.sparse_block*, %struct.sparse_block** %p, align 8, !dbg !1269
  %cmp = icmp ne %struct.sparse_block* %6, null, !dbg !1272
  br i1 %cmp, label %for.body, label %for.end, !dbg !1273

for.body:                                         ; preds = %for.cond
  %7 = load %struct.sparse_block*, %struct.sparse_block** %p, align 8, !dbg !1274
  %hole = getelementptr inbounds %struct.sparse_block, %struct.sparse_block* %7, i32 0, i32 3, !dbg !1277
  %8 = load i32, i32* %hole, align 8, !dbg !1277
  %tobool = icmp ne i32 %8, 0, !dbg !1274
  br i1 %tobool, label %if.end4, label %if.then, !dbg !1278

if.then:                                          ; preds = %for.body
  %9 = load %struct.sparse_block*, %struct.sparse_block** %p, align 8, !dbg !1279
  %remaining = getelementptr inbounds %struct.sparse_block, %struct.sparse_block* %9, i32 0, i32 2, !dbg !1282
  %10 = load i64, i64* %remaining, align 8, !dbg !1282
  %11 = load i64, i64* %request, align 8, !dbg !1283
  %sub = sub nsw i64 9223372036854775807, %11, !dbg !1284
  %cmp1 = icmp sge i64 %10, %sub, !dbg !1285
  br i1 %cmp1, label %if.then2, label %if.end, !dbg !1286

if.then2:                                         ; preds = %if.then
  store i32 -30, i32* %retval, align 4, !dbg !1287
  br label %return, !dbg !1287

if.end:                                           ; preds = %if.then
  %12 = load %struct.sparse_block*, %struct.sparse_block** %p, align 8, !dbg !1289
  %remaining3 = getelementptr inbounds %struct.sparse_block, %struct.sparse_block* %12, i32 0, i32 2, !dbg !1290
  %13 = load i64, i64* %remaining3, align 8, !dbg !1290
  %14 = load i64, i64* %request, align 8, !dbg !1291
  %add = add nsw i64 %14, %13, !dbg !1291
  store i64 %add, i64* %request, align 8, !dbg !1291
  br label %if.end4, !dbg !1292

if.end4:                                          ; preds = %if.end, %for.body
  br label %for.inc, !dbg !1293

for.inc:                                          ; preds = %if.end4
  %15 = load %struct.sparse_block*, %struct.sparse_block** %p, align 8, !dbg !1294
  %next = getelementptr inbounds %struct.sparse_block, %struct.sparse_block* %15, i32 0, i32 0, !dbg !1296
  %16 = load %struct.sparse_block*, %struct.sparse_block** %next, align 8, !dbg !1296
  store %struct.sparse_block* %16, %struct.sparse_block** %p, align 8, !dbg !1297
  br label %for.cond, !dbg !1298

for.end:                                          ; preds = %for.cond
  %17 = load i64, i64* %request, align 8, !dbg !1299
  %18 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1301
  %entry_bytes_remaining = getelementptr inbounds %struct.tar, %struct.tar* %18, i32 0, i32 13, !dbg !1302
  %19 = load i64, i64* %entry_bytes_remaining, align 8, !dbg !1302
  %cmp5 = icmp sgt i64 %17, %19, !dbg !1303
  br i1 %cmp5, label %if.then6, label %if.end8, !dbg !1304

if.then6:                                         ; preds = %for.end
  %20 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1305
  %entry_bytes_remaining7 = getelementptr inbounds %struct.tar, %struct.tar* %20, i32 0, i32 13, !dbg !1306
  %21 = load i64, i64* %entry_bytes_remaining7, align 8, !dbg !1306
  store i64 %21, i64* %request, align 8, !dbg !1307
  br label %if.end8, !dbg !1308

if.end8:                                          ; preds = %if.then6, %for.end
  %22 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1309
  %entry_padding = getelementptr inbounds %struct.tar, %struct.tar* %22, i32 0, i32 15, !dbg !1310
  %23 = load i64, i64* %entry_padding, align 8, !dbg !1310
  %24 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1311
  %entry_bytes_unconsumed = getelementptr inbounds %struct.tar, %struct.tar* %24, i32 0, i32 16, !dbg !1312
  %25 = load i64, i64* %entry_bytes_unconsumed, align 8, !dbg !1312
  %add9 = add nsw i64 %23, %25, !dbg !1313
  %26 = load i64, i64* %request, align 8, !dbg !1314
  %add10 = add nsw i64 %26, %add9, !dbg !1314
  store i64 %add10, i64* %request, align 8, !dbg !1314
  %27 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1315
  %28 = load i64, i64* %request, align 8, !dbg !1316
  %call = call i64 @__archive_read_consume(%struct.archive_read* %27, i64 %28), !dbg !1317
  store i64 %call, i64* %bytes_skipped, align 8, !dbg !1318
  %29 = load i64, i64* %bytes_skipped, align 8, !dbg !1319
  %cmp11 = icmp slt i64 %29, 0, !dbg !1321
  br i1 %cmp11, label %if.then12, label %if.end13, !dbg !1322

if.then12:                                        ; preds = %if.end8
  store i32 -30, i32* %retval, align 4, !dbg !1323
  br label %return, !dbg !1323

if.end13:                                         ; preds = %if.end8
  %30 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1324
  %entry_bytes_remaining14 = getelementptr inbounds %struct.tar, %struct.tar* %30, i32 0, i32 13, !dbg !1325
  store i64 0, i64* %entry_bytes_remaining14, align 8, !dbg !1326
  %31 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1327
  %entry_bytes_unconsumed15 = getelementptr inbounds %struct.tar, %struct.tar* %31, i32 0, i32 16, !dbg !1328
  store i64 0, i64* %entry_bytes_unconsumed15, align 8, !dbg !1329
  %32 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1330
  %entry_padding16 = getelementptr inbounds %struct.tar, %struct.tar* %32, i32 0, i32 15, !dbg !1331
  store i64 0, i64* %entry_padding16, align 8, !dbg !1332
  %33 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1333
  call void @gnu_clear_sparse_list(%struct.tar* %33), !dbg !1334
  store i32 0, i32* %retval, align 4, !dbg !1335
  br label %return, !dbg !1335

return:                                           ; preds = %if.end13, %if.then12, %if.then2
  %34 = load i32, i32* %retval, align 4, !dbg !1336
  ret i32 %34, !dbg !1336
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_read_format_tar_cleanup(%struct.archive_read* %a) #0 !dbg !441 {
entry:
  %a.addr = alloca %struct.archive_read*, align 8
  %tar = alloca %struct.tar*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !1337, metadata !563), !dbg !1338
  call void @llvm.dbg.declare(metadata %struct.tar** %tar, metadata !1339, metadata !563), !dbg !1340
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1341
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 13, !dbg !1342
  %1 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !1342
  %data = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %1, i32 0, i32 0, !dbg !1343
  %2 = load i8*, i8** %data, align 8, !dbg !1343
  %3 = bitcast i8* %2 to %struct.tar*, !dbg !1344
  store %struct.tar* %3, %struct.tar** %tar, align 8, !dbg !1345
  %4 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1346
  call void @gnu_clear_sparse_list(%struct.tar* %4), !dbg !1347
  %5 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1348
  %acl_text = getelementptr inbounds %struct.tar, %struct.tar* %5, i32 0, i32 0, !dbg !1349
  call void @archive_string_free(%struct.archive_string* %acl_text), !dbg !1350
  %6 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1351
  %entry_pathname = getelementptr inbounds %struct.tar, %struct.tar* %6, i32 0, i32 1, !dbg !1352
  call void @archive_string_free(%struct.archive_string* %entry_pathname), !dbg !1353
  %7 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1354
  %entry_pathname_override = getelementptr inbounds %struct.tar, %struct.tar* %7, i32 0, i32 2, !dbg !1355
  call void @archive_string_free(%struct.archive_string* %entry_pathname_override), !dbg !1356
  %8 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1357
  %entry_linkpath = getelementptr inbounds %struct.tar, %struct.tar* %8, i32 0, i32 3, !dbg !1358
  call void @archive_string_free(%struct.archive_string* %entry_linkpath), !dbg !1359
  %9 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1360
  %entry_uname = getelementptr inbounds %struct.tar, %struct.tar* %9, i32 0, i32 4, !dbg !1361
  call void @archive_string_free(%struct.archive_string* %entry_uname), !dbg !1362
  %10 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1363
  %entry_gname = getelementptr inbounds %struct.tar, %struct.tar* %10, i32 0, i32 5, !dbg !1364
  call void @archive_string_free(%struct.archive_string* %entry_gname), !dbg !1365
  %11 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1366
  %line = getelementptr inbounds %struct.tar, %struct.tar* %11, i32 0, i32 10, !dbg !1367
  call void @archive_string_free(%struct.archive_string* %line), !dbg !1368
  %12 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1369
  %pax_global = getelementptr inbounds %struct.tar, %struct.tar* %12, i32 0, i32 9, !dbg !1370
  call void @archive_string_free(%struct.archive_string* %pax_global), !dbg !1371
  %13 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1372
  %pax_header = getelementptr inbounds %struct.tar, %struct.tar* %13, i32 0, i32 8, !dbg !1373
  call void @archive_string_free(%struct.archive_string* %pax_header), !dbg !1374
  %14 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1375
  %longname = getelementptr inbounds %struct.tar, %struct.tar* %14, i32 0, i32 7, !dbg !1376
  call void @archive_string_free(%struct.archive_string* %longname), !dbg !1377
  %15 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1378
  %longlink = getelementptr inbounds %struct.tar, %struct.tar* %15, i32 0, i32 6, !dbg !1379
  call void @archive_string_free(%struct.archive_string* %longlink), !dbg !1380
  %16 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1381
  %localname = getelementptr inbounds %struct.tar, %struct.tar* %16, i32 0, i32 26, !dbg !1382
  call void @archive_string_free(%struct.archive_string* %localname), !dbg !1383
  %17 = load %struct.tar*, %struct.tar** %tar, align 8, !dbg !1384
  %18 = bitcast %struct.tar* %17 to i8*, !dbg !1384
  call void @free(i8* %18) #7, !dbg !1385
  %19 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1386
  %format1 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %19, i32 0, i32 13, !dbg !1387
  %20 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format1, align 8, !dbg !1387
  %data2 = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %20, i32 0, i32 0, !dbg !1388
  store i8* null, i8** %data2, align 8, !dbg !1389
  ret i32 0, !dbg !1390
}

; Function Attrs: nounwind
declare void @free(i8*) #3

; Function Attrs: nounwind uwtable
define internal void @gnu_clear_sparse_list(%struct.tar* %tar) #0 !dbg !442 {
entry:
  %tar.addr = alloca %struct.tar*, align 8
  %p = alloca %struct.sparse_block*, align 8
  store %struct.tar* %tar, %struct.tar** %tar.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tar** %tar.addr, metadata !1391, metadata !563), !dbg !1392
  call void @llvm.dbg.declare(metadata %struct.sparse_block** %p, metadata !1393, metadata !563), !dbg !1394
  br label %while.cond, !dbg !1395

while.cond:                                       ; preds = %while.body, %entry
  %0 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !1396
  %sparse_list = getelementptr inbounds %struct.tar, %struct.tar* %0, i32 0, i32 19, !dbg !1398
  %1 = load %struct.sparse_block*, %struct.sparse_block** %sparse_list, align 8, !dbg !1398
  %cmp = icmp ne %struct.sparse_block* %1, null, !dbg !1399
  br i1 %cmp, label %while.body, label %while.end, !dbg !1400

while.body:                                       ; preds = %while.cond
  %2 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !1401
  %sparse_list1 = getelementptr inbounds %struct.tar, %struct.tar* %2, i32 0, i32 19, !dbg !1403
  %3 = load %struct.sparse_block*, %struct.sparse_block** %sparse_list1, align 8, !dbg !1403
  store %struct.sparse_block* %3, %struct.sparse_block** %p, align 8, !dbg !1404
  %4 = load %struct.sparse_block*, %struct.sparse_block** %p, align 8, !dbg !1405
  %next = getelementptr inbounds %struct.sparse_block, %struct.sparse_block* %4, i32 0, i32 0, !dbg !1406
  %5 = load %struct.sparse_block*, %struct.sparse_block** %next, align 8, !dbg !1406
  %6 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !1407
  %sparse_list2 = getelementptr inbounds %struct.tar, %struct.tar* %6, i32 0, i32 19, !dbg !1408
  store %struct.sparse_block* %5, %struct.sparse_block** %sparse_list2, align 8, !dbg !1409
  %7 = load %struct.sparse_block*, %struct.sparse_block** %p, align 8, !dbg !1410
  %8 = bitcast %struct.sparse_block* %7 to i8*, !dbg !1410
  call void @free(i8* %8) #7, !dbg !1411
  br label %while.cond, !dbg !1412

while.end:                                        ; preds = %while.cond
  %9 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !1414
  %sparse_last = getelementptr inbounds %struct.tar, %struct.tar* %9, i32 0, i32 20, !dbg !1415
  store %struct.sparse_block* null, %struct.sparse_block** %sparse_last, align 8, !dbg !1416
  ret void, !dbg !1417
}

declare void @archive_string_free(%struct.archive_string*) #2

declare i8* @__archive_read_ahead(%struct.archive_read*, i64, i64*) #2

; Function Attrs: nounwind uwtable
define internal i32 @archive_block_is_null(i8* %p) #0 !dbg !446 {
entry:
  %retval = alloca i32, align 4
  %p.addr = alloca i8*, align 8
  %i = alloca i32, align 4
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !1418, metadata !563), !dbg !1419
  call void @llvm.dbg.declare(metadata i32* %i, metadata !1420, metadata !563), !dbg !1421
  store i32 0, i32* %i, align 4, !dbg !1422
  br label %for.cond, !dbg !1424

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, i32* %i, align 4, !dbg !1425
  %cmp = icmp ult i32 %0, 512, !dbg !1428
  br i1 %cmp, label %for.body, label %for.end, !dbg !1429

for.body:                                         ; preds = %for.cond
  %1 = load i8*, i8** %p.addr, align 8, !dbg !1430
  %incdec.ptr = getelementptr inbounds i8, i8* %1, i32 1, !dbg !1430
  store i8* %incdec.ptr, i8** %p.addr, align 8, !dbg !1430
  %2 = load i8, i8* %1, align 1, !dbg !1432
  %tobool = icmp ne i8 %2, 0, !dbg !1432
  br i1 %tobool, label %if.then, label %if.end, !dbg !1433

if.then:                                          ; preds = %for.body
  store i32 0, i32* %retval, align 4, !dbg !1434
  br label %return, !dbg !1434

if.end:                                           ; preds = %for.body
  br label %for.inc, !dbg !1435

for.inc:                                          ; preds = %if.end
  %3 = load i32, i32* %i, align 4, !dbg !1437
  %inc = add i32 %3, 1, !dbg !1437
  store i32 %inc, i32* %i, align 4, !dbg !1437
  br label %for.cond, !dbg !1439

for.end:                                          ; preds = %for.cond
  store i32 1, i32* %retval, align 4, !dbg !1440
  br label %return, !dbg !1440

return:                                           ; preds = %for.end, %if.then
  %4 = load i32, i32* %retval, align 4, !dbg !1441
  ret i32 %4, !dbg !1441
}

; Function Attrs: nounwind uwtable
define internal i32 @checksum(%struct.archive_read* %a, i8* %h) #0 !dbg !449 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %h.addr = alloca i8*, align 8
  %bytes = alloca i8*, align 8
  %header = alloca %struct.archive_entry_header_ustar*, align 8
  %check = alloca i32, align 4
  %sum = alloca i32, align 4
  %i = alloca i64, align 8
  %c = alloca i8, align 1
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !1442, metadata !563), !dbg !1443
  store i8* %h, i8** %h.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %h.addr, metadata !1444, metadata !563), !dbg !1445
  call void @llvm.dbg.declare(metadata i8** %bytes, metadata !1446, metadata !563), !dbg !1447
  call void @llvm.dbg.declare(metadata %struct.archive_entry_header_ustar** %header, metadata !1448, metadata !563), !dbg !1449
  call void @llvm.dbg.declare(metadata i32* %check, metadata !1450, metadata !563), !dbg !1451
  call void @llvm.dbg.declare(metadata i32* %sum, metadata !1452, metadata !563), !dbg !1453
  call void @llvm.dbg.declare(metadata i64* %i, metadata !1454, metadata !563), !dbg !1455
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1456
  %1 = load i8*, i8** %h.addr, align 8, !dbg !1457
  store i8* %1, i8** %bytes, align 8, !dbg !1458
  %2 = load i8*, i8** %h.addr, align 8, !dbg !1459
  %3 = bitcast i8* %2 to %struct.archive_entry_header_ustar*, !dbg !1460
  store %struct.archive_entry_header_ustar* %3, %struct.archive_entry_header_ustar** %header, align 8, !dbg !1461
  store i64 0, i64* %i, align 8, !dbg !1462
  br label %for.cond, !dbg !1464

for.cond:                                         ; preds = %for.inc, %entry
  %4 = load i64, i64* %i, align 8, !dbg !1465
  %cmp = icmp ult i64 %4, 8, !dbg !1468
  br i1 %cmp, label %for.body, label %for.end, !dbg !1469

for.body:                                         ; preds = %for.cond
  call void @llvm.dbg.declare(metadata i8* %c, metadata !1470, metadata !563), !dbg !1472
  %5 = load i64, i64* %i, align 8, !dbg !1473
  %6 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !1474
  %checksum = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %6, i32 0, i32 6, !dbg !1475
  %arrayidx = getelementptr inbounds [8 x i8], [8 x i8]* %checksum, i64 0, i64 %5, !dbg !1474
  %7 = load i8, i8* %arrayidx, align 1, !dbg !1474
  store i8 %7, i8* %c, align 1, !dbg !1472
  %8 = load i8, i8* %c, align 1, !dbg !1476
  %conv = sext i8 %8 to i32, !dbg !1476
  %cmp1 = icmp ne i32 %conv, 32, !dbg !1478
  br i1 %cmp1, label %land.lhs.true, label %if.end, !dbg !1479

land.lhs.true:                                    ; preds = %for.body
  %9 = load i8, i8* %c, align 1, !dbg !1480
  %conv3 = sext i8 %9 to i32, !dbg !1480
  %cmp4 = icmp ne i32 %conv3, 0, !dbg !1482
  br i1 %cmp4, label %land.lhs.true6, label %if.end, !dbg !1483

land.lhs.true6:                                   ; preds = %land.lhs.true
  %10 = load i8, i8* %c, align 1, !dbg !1484
  %conv7 = sext i8 %10 to i32, !dbg !1484
  %cmp8 = icmp slt i32 %conv7, 48, !dbg !1486
  br i1 %cmp8, label %if.then, label %lor.lhs.false, !dbg !1487

lor.lhs.false:                                    ; preds = %land.lhs.true6
  %11 = load i8, i8* %c, align 1, !dbg !1488
  %conv10 = sext i8 %11 to i32, !dbg !1488
  %cmp11 = icmp sgt i32 %conv10, 55, !dbg !1490
  br i1 %cmp11, label %if.then, label %if.end, !dbg !1491

if.then:                                          ; preds = %lor.lhs.false, %land.lhs.true6
  store i32 0, i32* %retval, align 4, !dbg !1492
  br label %return, !dbg !1492

if.end:                                           ; preds = %lor.lhs.false, %land.lhs.true, %for.body
  br label %for.inc, !dbg !1493

for.inc:                                          ; preds = %if.end
  %12 = load i64, i64* %i, align 8, !dbg !1494
  %inc = add i64 %12, 1, !dbg !1494
  store i64 %inc, i64* %i, align 8, !dbg !1494
  br label %for.cond, !dbg !1496

for.end:                                          ; preds = %for.cond
  %13 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !1497
  %checksum13 = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %13, i32 0, i32 6, !dbg !1498
  %arraydecay = getelementptr inbounds [8 x i8], [8 x i8]* %checksum13, i32 0, i32 0, !dbg !1497
  %call = call i64 @tar_atol(i8* %arraydecay, i64 8), !dbg !1499
  %conv14 = trunc i64 %call to i32, !dbg !1500
  store i32 %conv14, i32* %sum, align 4, !dbg !1501
  store i32 0, i32* %check, align 4, !dbg !1502
  store i64 0, i64* %i, align 8, !dbg !1503
  br label %for.cond15, !dbg !1505

for.cond15:                                       ; preds = %for.inc21, %for.end
  %14 = load i64, i64* %i, align 8, !dbg !1506
  %cmp16 = icmp ult i64 %14, 148, !dbg !1509
  br i1 %cmp16, label %for.body18, label %for.end23, !dbg !1510

for.body18:                                       ; preds = %for.cond15
  %15 = load i64, i64* %i, align 8, !dbg !1511
  %16 = load i8*, i8** %bytes, align 8, !dbg !1512
  %arrayidx19 = getelementptr inbounds i8, i8* %16, i64 %15, !dbg !1512
  %17 = load i8, i8* %arrayidx19, align 1, !dbg !1512
  %conv20 = zext i8 %17 to i32, !dbg !1513
  %18 = load i32, i32* %check, align 4, !dbg !1514
  %add = add nsw i32 %18, %conv20, !dbg !1514
  store i32 %add, i32* %check, align 4, !dbg !1514
  br label %for.inc21, !dbg !1515

for.inc21:                                        ; preds = %for.body18
  %19 = load i64, i64* %i, align 8, !dbg !1516
  %inc22 = add i64 %19, 1, !dbg !1516
  store i64 %inc22, i64* %i, align 8, !dbg !1516
  br label %for.cond15, !dbg !1518

for.end23:                                        ; preds = %for.cond15
  br label %for.cond24, !dbg !1519

for.cond24:                                       ; preds = %for.inc29, %for.end23
  %20 = load i64, i64* %i, align 8, !dbg !1520
  %cmp25 = icmp ult i64 %20, 156, !dbg !1524
  br i1 %cmp25, label %for.body27, label %for.end31, !dbg !1525

for.body27:                                       ; preds = %for.cond24
  %21 = load i32, i32* %check, align 4, !dbg !1526
  %add28 = add nsw i32 %21, 32, !dbg !1526
  store i32 %add28, i32* %check, align 4, !dbg !1526
  br label %for.inc29, !dbg !1527

for.inc29:                                        ; preds = %for.body27
  %22 = load i64, i64* %i, align 8, !dbg !1528
  %inc30 = add i64 %22, 1, !dbg !1528
  store i64 %inc30, i64* %i, align 8, !dbg !1528
  br label %for.cond24, !dbg !1530

for.end31:                                        ; preds = %for.cond24
  br label %for.cond32, !dbg !1531

for.cond32:                                       ; preds = %for.inc39, %for.end31
  %23 = load i64, i64* %i, align 8, !dbg !1532
  %cmp33 = icmp ult i64 %23, 512, !dbg !1536
  br i1 %cmp33, label %for.body35, label %for.end41, !dbg !1537

for.body35:                                       ; preds = %for.cond32
  %24 = load i64, i64* %i, align 8, !dbg !1538
  %25 = load i8*, i8** %bytes, align 8, !dbg !1539
  %arrayidx36 = getelementptr inbounds i8, i8* %25, i64 %24, !dbg !1539
  %26 = load i8, i8* %arrayidx36, align 1, !dbg !1539
  %conv37 = zext i8 %26 to i32, !dbg !1540
  %27 = load i32, i32* %check, align 4, !dbg !1541
  %add38 = add nsw i32 %27, %conv37, !dbg !1541
  store i32 %add38, i32* %check, align 4, !dbg !1541
  br label %for.inc39, !dbg !1542

for.inc39:                                        ; preds = %for.body35
  %28 = load i64, i64* %i, align 8, !dbg !1543
  %inc40 = add i64 %28, 1, !dbg !1543
  store i64 %inc40, i64* %i, align 8, !dbg !1543
  br label %for.cond32, !dbg !1545

for.end41:                                        ; preds = %for.cond32
  %29 = load i32, i32* %sum, align 4, !dbg !1546
  %30 = load i32, i32* %check, align 4, !dbg !1548
  %cmp42 = icmp eq i32 %29, %30, !dbg !1549
  br i1 %cmp42, label %if.then44, label %if.end45, !dbg !1550

if.then44:                                        ; preds = %for.end41
  store i32 1, i32* %retval, align 4, !dbg !1551
  br label %return, !dbg !1551

if.end45:                                         ; preds = %for.end41
  store i32 0, i32* %check, align 4, !dbg !1552
  store i64 0, i64* %i, align 8, !dbg !1553
  br label %for.cond46, !dbg !1555

for.cond46:                                       ; preds = %for.inc53, %if.end45
  %31 = load i64, i64* %i, align 8, !dbg !1556
  %cmp47 = icmp ult i64 %31, 148, !dbg !1559
  br i1 %cmp47, label %for.body49, label %for.end55, !dbg !1560

for.body49:                                       ; preds = %for.cond46
  %32 = load i64, i64* %i, align 8, !dbg !1561
  %33 = load i8*, i8** %bytes, align 8, !dbg !1562
  %arrayidx50 = getelementptr inbounds i8, i8* %33, i64 %32, !dbg !1562
  %34 = load i8, i8* %arrayidx50, align 1, !dbg !1562
  %conv51 = sext i8 %34 to i32, !dbg !1563
  %35 = load i32, i32* %check, align 4, !dbg !1564
  %add52 = add nsw i32 %35, %conv51, !dbg !1564
  store i32 %add52, i32* %check, align 4, !dbg !1564
  br label %for.inc53, !dbg !1565

for.inc53:                                        ; preds = %for.body49
  %36 = load i64, i64* %i, align 8, !dbg !1566
  %inc54 = add i64 %36, 1, !dbg !1566
  store i64 %inc54, i64* %i, align 8, !dbg !1566
  br label %for.cond46, !dbg !1568

for.end55:                                        ; preds = %for.cond46
  br label %for.cond56, !dbg !1569

for.cond56:                                       ; preds = %for.inc61, %for.end55
  %37 = load i64, i64* %i, align 8, !dbg !1570
  %cmp57 = icmp ult i64 %37, 156, !dbg !1574
  br i1 %cmp57, label %for.body59, label %for.end63, !dbg !1575

for.body59:                                       ; preds = %for.cond56
  %38 = load i32, i32* %check, align 4, !dbg !1576
  %add60 = add nsw i32 %38, 32, !dbg !1576
  store i32 %add60, i32* %check, align 4, !dbg !1576
  br label %for.inc61, !dbg !1577

for.inc61:                                        ; preds = %for.body59
  %39 = load i64, i64* %i, align 8, !dbg !1578
  %inc62 = add i64 %39, 1, !dbg !1578
  store i64 %inc62, i64* %i, align 8, !dbg !1578
  br label %for.cond56, !dbg !1580

for.end63:                                        ; preds = %for.cond56
  br label %for.cond64, !dbg !1581

for.cond64:                                       ; preds = %for.inc71, %for.end63
  %40 = load i64, i64* %i, align 8, !dbg !1582
  %cmp65 = icmp ult i64 %40, 512, !dbg !1586
  br i1 %cmp65, label %for.body67, label %for.end73, !dbg !1587

for.body67:                                       ; preds = %for.cond64
  %41 = load i64, i64* %i, align 8, !dbg !1588
  %42 = load i8*, i8** %bytes, align 8, !dbg !1589
  %arrayidx68 = getelementptr inbounds i8, i8* %42, i64 %41, !dbg !1589
  %43 = load i8, i8* %arrayidx68, align 1, !dbg !1589
  %conv69 = sext i8 %43 to i32, !dbg !1590
  %44 = load i32, i32* %check, align 4, !dbg !1591
  %add70 = add nsw i32 %44, %conv69, !dbg !1591
  store i32 %add70, i32* %check, align 4, !dbg !1591
  br label %for.inc71, !dbg !1592

for.inc71:                                        ; preds = %for.body67
  %45 = load i64, i64* %i, align 8, !dbg !1593
  %inc72 = add i64 %45, 1, !dbg !1593
  store i64 %inc72, i64* %i, align 8, !dbg !1593
  br label %for.cond64, !dbg !1595

for.end73:                                        ; preds = %for.cond64
  %46 = load i32, i32* %sum, align 4, !dbg !1596
  %47 = load i32, i32* %check, align 4, !dbg !1598
  %cmp74 = icmp eq i32 %46, %47, !dbg !1599
  br i1 %cmp74, label %if.then76, label %if.end77, !dbg !1600

if.then76:                                        ; preds = %for.end73
  store i32 1, i32* %retval, align 4, !dbg !1601
  br label %return, !dbg !1601

if.end77:                                         ; preds = %for.end73
  store i32 0, i32* %retval, align 4, !dbg !1602
  br label %return, !dbg !1602

return:                                           ; preds = %if.end77, %if.then76, %if.then44, %if.then
  %48 = load i32, i32* %retval, align 4, !dbg !1603
  ret i32 %48, !dbg !1603
}

; Function Attrs: nounwind readonly
declare i32 @memcmp(i8*, i8*, i64) #4

; Function Attrs: nounwind uwtable
define internal i32 @validate_number_field(i8* %p_field, i64 %i_size) #0 !dbg !460 {
entry:
  %retval = alloca i32, align 4
  %p_field.addr = alloca i8*, align 8
  %i_size.addr = alloca i64, align 8
  %marker = alloca i8, align 1
  %i = alloca i64, align 8
  store i8* %p_field, i8** %p_field.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p_field.addr, metadata !1604, metadata !563), !dbg !1605
  store i64 %i_size, i64* %i_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %i_size.addr, metadata !1606, metadata !563), !dbg !1607
  call void @llvm.dbg.declare(metadata i8* %marker, metadata !1608, metadata !563), !dbg !1609
  %0 = load i8*, i8** %p_field.addr, align 8, !dbg !1610
  %arrayidx = getelementptr inbounds i8, i8* %0, i64 0, !dbg !1610
  %1 = load i8, i8* %arrayidx, align 1, !dbg !1610
  store i8 %1, i8* %marker, align 1, !dbg !1609
  %2 = load i8, i8* %marker, align 1, !dbg !1611
  %conv = zext i8 %2 to i32, !dbg !1611
  %cmp = icmp eq i32 %conv, 128, !dbg !1613
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !1614

lor.lhs.false:                                    ; preds = %entry
  %3 = load i8, i8* %marker, align 1, !dbg !1615
  %conv2 = zext i8 %3 to i32, !dbg !1615
  %cmp3 = icmp eq i32 %conv2, 255, !dbg !1617
  br i1 %cmp3, label %if.then, label %lor.lhs.false5, !dbg !1618

lor.lhs.false5:                                   ; preds = %lor.lhs.false
  %4 = load i8, i8* %marker, align 1, !dbg !1619
  %conv6 = zext i8 %4 to i32, !dbg !1619
  %cmp7 = icmp eq i32 %conv6, 0, !dbg !1621
  br i1 %cmp7, label %if.then, label %if.else, !dbg !1622

if.then:                                          ; preds = %lor.lhs.false5, %lor.lhs.false, %entry
  store i32 1, i32* %retval, align 4, !dbg !1623
  br label %return, !dbg !1623

if.else:                                          ; preds = %lor.lhs.false5
  call void @llvm.dbg.declare(metadata i64* %i, metadata !1625, metadata !563), !dbg !1627
  store i64 0, i64* %i, align 8, !dbg !1627
  br label %while.cond, !dbg !1628

while.cond:                                       ; preds = %while.body, %if.else
  %5 = load i64, i64* %i, align 8, !dbg !1629
  %6 = load i64, i64* %i_size.addr, align 8, !dbg !1631
  %cmp9 = icmp ult i64 %5, %6, !dbg !1632
  br i1 %cmp9, label %land.rhs, label %land.end, !dbg !1633

land.rhs:                                         ; preds = %while.cond
  %7 = load i64, i64* %i, align 8, !dbg !1634
  %8 = load i8*, i8** %p_field.addr, align 8, !dbg !1636
  %arrayidx11 = getelementptr inbounds i8, i8* %8, i64 %7, !dbg !1636
  %9 = load i8, i8* %arrayidx11, align 1, !dbg !1636
  %conv12 = sext i8 %9 to i32, !dbg !1636
  %cmp13 = icmp eq i32 %conv12, 32, !dbg !1637
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond
  %10 = phi i1 [ false, %while.cond ], [ %cmp13, %land.rhs ]
  br i1 %10, label %while.body, label %while.end, !dbg !1638

while.body:                                       ; preds = %land.end
  %11 = load i64, i64* %i, align 8, !dbg !1640
  %inc = add i64 %11, 1, !dbg !1640
  store i64 %inc, i64* %i, align 8, !dbg !1640
  br label %while.cond, !dbg !1642

while.end:                                        ; preds = %land.end
  br label %while.cond15, !dbg !1644

while.cond15:                                     ; preds = %while.body28, %while.end
  %12 = load i64, i64* %i, align 8, !dbg !1645
  %13 = load i64, i64* %i_size.addr, align 8, !dbg !1646
  %cmp16 = icmp ult i64 %12, %13, !dbg !1647
  br i1 %cmp16, label %land.lhs.true, label %land.end27, !dbg !1648

land.lhs.true:                                    ; preds = %while.cond15
  %14 = load i64, i64* %i, align 8, !dbg !1649
  %15 = load i8*, i8** %p_field.addr, align 8, !dbg !1650
  %arrayidx18 = getelementptr inbounds i8, i8* %15, i64 %14, !dbg !1650
  %16 = load i8, i8* %arrayidx18, align 1, !dbg !1650
  %conv19 = sext i8 %16 to i32, !dbg !1650
  %cmp20 = icmp sge i32 %conv19, 48, !dbg !1651
  br i1 %cmp20, label %land.rhs22, label %land.end27, !dbg !1652

land.rhs22:                                       ; preds = %land.lhs.true
  %17 = load i64, i64* %i, align 8, !dbg !1653
  %18 = load i8*, i8** %p_field.addr, align 8, !dbg !1654
  %arrayidx23 = getelementptr inbounds i8, i8* %18, i64 %17, !dbg !1654
  %19 = load i8, i8* %arrayidx23, align 1, !dbg !1654
  %conv24 = sext i8 %19 to i32, !dbg !1654
  %cmp25 = icmp sle i32 %conv24, 55, !dbg !1655
  br label %land.end27

land.end27:                                       ; preds = %land.rhs22, %land.lhs.true, %while.cond15
  %20 = phi i1 [ false, %land.lhs.true ], [ false, %while.cond15 ], [ %cmp25, %land.rhs22 ]
  br i1 %20, label %while.body28, label %while.end30, !dbg !1656

while.body28:                                     ; preds = %land.end27
  %21 = load i64, i64* %i, align 8, !dbg !1657
  %inc29 = add i64 %21, 1, !dbg !1657
  store i64 %inc29, i64* %i, align 8, !dbg !1657
  br label %while.cond15, !dbg !1659

while.end30:                                      ; preds = %land.end27
  br label %while.cond31, !dbg !1661

while.cond31:                                     ; preds = %if.end, %while.end30
  %22 = load i64, i64* %i, align 8, !dbg !1662
  %23 = load i64, i64* %i_size.addr, align 8, !dbg !1663
  %cmp32 = icmp ult i64 %22, %23, !dbg !1664
  br i1 %cmp32, label %while.body34, label %while.end46, !dbg !1665

while.body34:                                     ; preds = %while.cond31
  %24 = load i64, i64* %i, align 8, !dbg !1666
  %25 = load i8*, i8** %p_field.addr, align 8, !dbg !1669
  %arrayidx35 = getelementptr inbounds i8, i8* %25, i64 %24, !dbg !1669
  %26 = load i8, i8* %arrayidx35, align 1, !dbg !1669
  %conv36 = sext i8 %26 to i32, !dbg !1669
  %cmp37 = icmp ne i32 %conv36, 32, !dbg !1670
  br i1 %cmp37, label %land.lhs.true39, label %if.end, !dbg !1671

land.lhs.true39:                                  ; preds = %while.body34
  %27 = load i64, i64* %i, align 8, !dbg !1672
  %28 = load i8*, i8** %p_field.addr, align 8, !dbg !1674
  %arrayidx40 = getelementptr inbounds i8, i8* %28, i64 %27, !dbg !1674
  %29 = load i8, i8* %arrayidx40, align 1, !dbg !1674
  %conv41 = sext i8 %29 to i32, !dbg !1674
  %cmp42 = icmp ne i32 %conv41, 0, !dbg !1675
  br i1 %cmp42, label %if.then44, label %if.end, !dbg !1676

if.then44:                                        ; preds = %land.lhs.true39
  store i32 0, i32* %retval, align 4, !dbg !1677
  br label %return, !dbg !1677

if.end:                                           ; preds = %land.lhs.true39, %while.body34
  %30 = load i64, i64* %i, align 8, !dbg !1679
  %inc45 = add i64 %30, 1, !dbg !1679
  store i64 %inc45, i64* %i, align 8, !dbg !1679
  br label %while.cond31, !dbg !1680

while.end46:                                      ; preds = %while.cond31
  store i32 1, i32* %retval, align 4, !dbg !1681
  br label %return, !dbg !1681

return:                                           ; preds = %while.end46, %if.then44, %if.then
  %31 = load i32, i32* %retval, align 4, !dbg !1682
  ret i32 %31, !dbg !1682
}

; Function Attrs: nounwind uwtable
define internal i64 @tar_atol(i8* %p, i64 %char_cnt) #0 !dbg !452 {
entry:
  %retval = alloca i64, align 8
  %p.addr = alloca i8*, align 8
  %char_cnt.addr = alloca i64, align 8
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !1683, metadata !563), !dbg !1684
  store i64 %char_cnt, i64* %char_cnt.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %char_cnt.addr, metadata !1685, metadata !563), !dbg !1686
  %0 = load i8*, i8** %p.addr, align 8, !dbg !1687
  %1 = load i8, i8* %0, align 1, !dbg !1689
  %conv = sext i8 %1 to i32, !dbg !1689
  %and = and i32 %conv, 128, !dbg !1690
  %tobool = icmp ne i32 %and, 0, !dbg !1690
  br i1 %tobool, label %if.then, label %if.end, !dbg !1691

if.then:                                          ; preds = %entry
  %2 = load i8*, i8** %p.addr, align 8, !dbg !1692
  %3 = load i64, i64* %char_cnt.addr, align 8, !dbg !1693
  %call = call i64 @tar_atol256(i8* %2, i64 %3), !dbg !1694
  store i64 %call, i64* %retval, align 8, !dbg !1695
  br label %return, !dbg !1695

if.end:                                           ; preds = %entry
  %4 = load i8*, i8** %p.addr, align 8, !dbg !1696
  %5 = load i64, i64* %char_cnt.addr, align 8, !dbg !1697
  %call1 = call i64 @tar_atol8(i8* %4, i64 %5), !dbg !1698
  store i64 %call1, i64* %retval, align 8, !dbg !1699
  br label %return, !dbg !1699

return:                                           ; preds = %if.end, %if.then
  %6 = load i64, i64* %retval, align 8, !dbg !1700
  ret i64 %6, !dbg !1700
}

; Function Attrs: nounwind uwtable
define internal i64 @tar_atol256(i8* %_p, i64 %char_cnt) #0 !dbg !455 {
entry:
  %retval = alloca i64, align 8
  %_p.addr = alloca i8*, align 8
  %char_cnt.addr = alloca i64, align 8
  %l = alloca i64, align 8
  %p = alloca i8*, align 8
  %c = alloca i8, align 1
  %neg = alloca i8, align 1
  store i8* %_p, i8** %_p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %_p.addr, metadata !1701, metadata !563), !dbg !1702
  store i64 %char_cnt, i64* %char_cnt.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %char_cnt.addr, metadata !1703, metadata !563), !dbg !1704
  call void @llvm.dbg.declare(metadata i64* %l, metadata !1705, metadata !563), !dbg !1707
  call void @llvm.dbg.declare(metadata i8** %p, metadata !1708, metadata !563), !dbg !1709
  %0 = load i8*, i8** %_p.addr, align 8, !dbg !1710
  store i8* %0, i8** %p, align 8, !dbg !1709
  call void @llvm.dbg.declare(metadata i8* %c, metadata !1711, metadata !563), !dbg !1712
  call void @llvm.dbg.declare(metadata i8* %neg, metadata !1713, metadata !563), !dbg !1714
  %1 = load i8*, i8** %p, align 8, !dbg !1715
  %2 = load i8, i8* %1, align 1, !dbg !1716
  store i8 %2, i8* %c, align 1, !dbg !1717
  %3 = load i8, i8* %c, align 1, !dbg !1718
  %conv = zext i8 %3 to i32, !dbg !1718
  %and = and i32 %conv, 64, !dbg !1720
  %tobool = icmp ne i32 %and, 0, !dbg !1720
  br i1 %tobool, label %if.then, label %if.else, !dbg !1721

if.then:                                          ; preds = %entry
  store i8 -1, i8* %neg, align 1, !dbg !1722
  %4 = load i8, i8* %c, align 1, !dbg !1724
  %conv1 = zext i8 %4 to i32, !dbg !1724
  %or = or i32 %conv1, 128, !dbg !1724
  %conv2 = trunc i32 %or to i8, !dbg !1724
  store i8 %conv2, i8* %c, align 1, !dbg !1724
  store i64 -1, i64* %l, align 8, !dbg !1725
  br label %if.end, !dbg !1726

if.else:                                          ; preds = %entry
  store i8 0, i8* %neg, align 1, !dbg !1727
  %5 = load i8, i8* %c, align 1, !dbg !1729
  %conv3 = zext i8 %5 to i32, !dbg !1729
  %and4 = and i32 %conv3, 127, !dbg !1729
  %conv5 = trunc i32 %and4 to i8, !dbg !1729
  store i8 %conv5, i8* %c, align 1, !dbg !1729
  store i64 0, i64* %l, align 8, !dbg !1730
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  br label %while.cond, !dbg !1731

while.cond:                                       ; preds = %if.end14, %if.end
  %6 = load i64, i64* %char_cnt.addr, align 8, !dbg !1732
  %cmp = icmp ugt i64 %6, 8, !dbg !1734
  br i1 %cmp, label %while.body, label %while.end, !dbg !1735

while.body:                                       ; preds = %while.cond
  %7 = load i64, i64* %char_cnt.addr, align 8, !dbg !1736
  %dec = add i64 %7, -1, !dbg !1736
  store i64 %dec, i64* %char_cnt.addr, align 8, !dbg !1736
  %8 = load i8, i8* %c, align 1, !dbg !1738
  %conv7 = zext i8 %8 to i32, !dbg !1738
  %9 = load i8, i8* %neg, align 1, !dbg !1740
  %conv8 = zext i8 %9 to i32, !dbg !1740
  %cmp9 = icmp ne i32 %conv7, %conv8, !dbg !1741
  br i1 %cmp9, label %if.then11, label %if.end14, !dbg !1742

if.then11:                                        ; preds = %while.body
  %10 = load i8, i8* %neg, align 1, !dbg !1743
  %conv12 = zext i8 %10 to i32, !dbg !1743
  %tobool13 = icmp ne i32 %conv12, 0, !dbg !1743
  %cond = select i1 %tobool13, i64 -9223372036854775808, i64 9223372036854775807, !dbg !1743
  store i64 %cond, i64* %retval, align 8, !dbg !1744
  br label %return, !dbg !1744

if.end14:                                         ; preds = %while.body
  %11 = load i8*, i8** %p, align 8, !dbg !1745
  %incdec.ptr = getelementptr inbounds i8, i8* %11, i32 1, !dbg !1745
  store i8* %incdec.ptr, i8** %p, align 8, !dbg !1745
  %12 = load i8, i8* %incdec.ptr, align 1, !dbg !1746
  store i8 %12, i8* %c, align 1, !dbg !1747
  br label %while.cond, !dbg !1748

while.end:                                        ; preds = %while.cond
  %13 = load i8, i8* %c, align 1, !dbg !1750
  %conv15 = zext i8 %13 to i32, !dbg !1750
  %14 = load i8, i8* %neg, align 1, !dbg !1752
  %conv16 = zext i8 %14 to i32, !dbg !1752
  %xor = xor i32 %conv15, %conv16, !dbg !1753
  %and17 = and i32 %xor, 128, !dbg !1754
  %tobool18 = icmp ne i32 %and17, 0, !dbg !1754
  br i1 %tobool18, label %if.then19, label %if.end23, !dbg !1755

if.then19:                                        ; preds = %while.end
  %15 = load i8, i8* %neg, align 1, !dbg !1756
  %conv20 = zext i8 %15 to i32, !dbg !1756
  %tobool21 = icmp ne i32 %conv20, 0, !dbg !1756
  %cond22 = select i1 %tobool21, i64 -9223372036854775808, i64 9223372036854775807, !dbg !1756
  store i64 %cond22, i64* %retval, align 8, !dbg !1758
  br label %return, !dbg !1758

if.end23:                                         ; preds = %while.end
  br label %while.cond24, !dbg !1759

while.cond24:                                     ; preds = %while.body28, %if.end23
  %16 = load i64, i64* %char_cnt.addr, align 8, !dbg !1760
  %dec25 = add i64 %16, -1, !dbg !1760
  store i64 %dec25, i64* %char_cnt.addr, align 8, !dbg !1760
  %cmp26 = icmp ugt i64 %dec25, 0, !dbg !1761
  br i1 %cmp26, label %while.body28, label %while.end32, !dbg !1762

while.body28:                                     ; preds = %while.cond24
  %17 = load i64, i64* %l, align 8, !dbg !1763
  %shl = shl i64 %17, 8, !dbg !1765
  %18 = load i8, i8* %c, align 1, !dbg !1766
  %conv29 = zext i8 %18 to i64, !dbg !1766
  %or30 = or i64 %shl, %conv29, !dbg !1767
  store i64 %or30, i64* %l, align 8, !dbg !1768
  %19 = load i8*, i8** %p, align 8, !dbg !1769
  %incdec.ptr31 = getelementptr inbounds i8, i8* %19, i32 1, !dbg !1769
  store i8* %incdec.ptr31, i8** %p, align 8, !dbg !1769
  %20 = load i8, i8* %incdec.ptr31, align 1, !dbg !1770
  store i8 %20, i8* %c, align 1, !dbg !1771
  br label %while.cond24, !dbg !1772

while.end32:                                      ; preds = %while.cond24
  %21 = load i64, i64* %l, align 8, !dbg !1773
  %shl33 = shl i64 %21, 8, !dbg !1774
  %22 = load i8, i8* %c, align 1, !dbg !1775
  %conv34 = zext i8 %22 to i64, !dbg !1775
  %or35 = or i64 %shl33, %conv34, !dbg !1776
  store i64 %or35, i64* %l, align 8, !dbg !1777
  %23 = load i64, i64* %l, align 8, !dbg !1778
  store i64 %23, i64* %retval, align 8, !dbg !1779
  br label %return, !dbg !1779

return:                                           ; preds = %while.end32, %if.then19, %if.then11
  %24 = load i64, i64* %retval, align 8, !dbg !1780
  ret i64 %24, !dbg !1780
}

; Function Attrs: nounwind uwtable
define internal i64 @tar_atol8(i8* %p, i64 %char_cnt) #0 !dbg !456 {
entry:
  %p.addr = alloca i8*, align 8
  %char_cnt.addr = alloca i64, align 8
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !1781, metadata !563), !dbg !1782
  store i64 %char_cnt, i64* %char_cnt.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %char_cnt.addr, metadata !1783, metadata !563), !dbg !1784
  %0 = load i8*, i8** %p.addr, align 8, !dbg !1785
  %1 = load i64, i64* %char_cnt.addr, align 8, !dbg !1786
  %call = call i64 @tar_atol_base_n(i8* %0, i64 %1, i32 8), !dbg !1787
  ret i64 %call, !dbg !1788
}

; Function Attrs: nounwind uwtable
define internal i64 @tar_atol_base_n(i8* %p, i64 %char_cnt, i32 %base) #0 !dbg !457 {
entry:
  %retval = alloca i64, align 8
  %p.addr = alloca i8*, align 8
  %char_cnt.addr = alloca i64, align 8
  %base.addr = alloca i32, align 4
  %l = alloca i64, align 8
  %maxval = alloca i64, align 8
  %limit = alloca i64, align 8
  %last_digit_limit = alloca i64, align 8
  %digit = alloca i32, align 4
  %sign = alloca i32, align 4
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !1789, metadata !563), !dbg !1790
  store i64 %char_cnt, i64* %char_cnt.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %char_cnt.addr, metadata !1791, metadata !563), !dbg !1792
  store i32 %base, i32* %base.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %base.addr, metadata !1793, metadata !563), !dbg !1794
  call void @llvm.dbg.declare(metadata i64* %l, metadata !1795, metadata !563), !dbg !1796
  call void @llvm.dbg.declare(metadata i64* %maxval, metadata !1797, metadata !563), !dbg !1798
  call void @llvm.dbg.declare(metadata i64* %limit, metadata !1799, metadata !563), !dbg !1800
  call void @llvm.dbg.declare(metadata i64* %last_digit_limit, metadata !1801, metadata !563), !dbg !1802
  call void @llvm.dbg.declare(metadata i32* %digit, metadata !1803, metadata !563), !dbg !1804
  call void @llvm.dbg.declare(metadata i32* %sign, metadata !1805, metadata !563), !dbg !1806
  store i64 9223372036854775807, i64* %maxval, align 8, !dbg !1807
  %0 = load i32, i32* %base.addr, align 4, !dbg !1808
  %conv = sext i32 %0 to i64, !dbg !1808
  %div = sdiv i64 9223372036854775807, %conv, !dbg !1809
  store i64 %div, i64* %limit, align 8, !dbg !1810
  %1 = load i32, i32* %base.addr, align 4, !dbg !1811
  %conv1 = sext i32 %1 to i64, !dbg !1811
  %rem = srem i64 9223372036854775807, %conv1, !dbg !1812
  store i64 %rem, i64* %last_digit_limit, align 8, !dbg !1813
  br label %while.cond, !dbg !1814

while.cond:                                       ; preds = %while.body, %entry
  %2 = load i64, i64* %char_cnt.addr, align 8, !dbg !1815
  %cmp = icmp ne i64 %2, 0, !dbg !1817
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !1818

land.rhs:                                         ; preds = %while.cond
  %3 = load i8*, i8** %p.addr, align 8, !dbg !1819
  %4 = load i8, i8* %3, align 1, !dbg !1821
  %conv3 = sext i8 %4 to i32, !dbg !1821
  %cmp4 = icmp eq i32 %conv3, 32, !dbg !1822
  br i1 %cmp4, label %lor.end, label %lor.rhs, !dbg !1823

lor.rhs:                                          ; preds = %land.rhs
  %5 = load i8*, i8** %p.addr, align 8, !dbg !1824
  %6 = load i8, i8* %5, align 1, !dbg !1826
  %conv6 = sext i8 %6 to i32, !dbg !1826
  %cmp7 = icmp eq i32 %conv6, 9, !dbg !1827
  br label %lor.end, !dbg !1828

lor.end:                                          ; preds = %lor.rhs, %land.rhs
  %7 = phi i1 [ true, %land.rhs ], [ %cmp7, %lor.rhs ]
  br label %land.end

land.end:                                         ; preds = %lor.end, %while.cond
  %8 = phi i1 [ false, %while.cond ], [ %7, %lor.end ]
  br i1 %8, label %while.body, label %while.end, !dbg !1829

while.body:                                       ; preds = %land.end
  %9 = load i8*, i8** %p.addr, align 8, !dbg !1831
  %incdec.ptr = getelementptr inbounds i8, i8* %9, i32 1, !dbg !1831
  store i8* %incdec.ptr, i8** %p.addr, align 8, !dbg !1831
  %10 = load i64, i64* %char_cnt.addr, align 8, !dbg !1833
  %dec = add i64 %10, -1, !dbg !1833
  store i64 %dec, i64* %char_cnt.addr, align 8, !dbg !1833
  br label %while.cond, !dbg !1834

while.end:                                        ; preds = %land.end
  store i32 1, i32* %sign, align 4, !dbg !1836
  %11 = load i64, i64* %char_cnt.addr, align 8, !dbg !1837
  %cmp9 = icmp ne i64 %11, 0, !dbg !1839
  br i1 %cmp9, label %land.lhs.true, label %if.end, !dbg !1840

land.lhs.true:                                    ; preds = %while.end
  %12 = load i8*, i8** %p.addr, align 8, !dbg !1841
  %13 = load i8, i8* %12, align 1, !dbg !1843
  %conv11 = sext i8 %13 to i32, !dbg !1843
  %cmp12 = icmp eq i32 %conv11, 45, !dbg !1844
  br i1 %cmp12, label %if.then, label %if.end, !dbg !1845

if.then:                                          ; preds = %land.lhs.true
  store i32 -1, i32* %sign, align 4, !dbg !1846
  %14 = load i8*, i8** %p.addr, align 8, !dbg !1848
  %incdec.ptr14 = getelementptr inbounds i8, i8* %14, i32 1, !dbg !1848
  store i8* %incdec.ptr14, i8** %p.addr, align 8, !dbg !1848
  %15 = load i64, i64* %char_cnt.addr, align 8, !dbg !1849
  %dec15 = add i64 %15, -1, !dbg !1849
  store i64 %dec15, i64* %char_cnt.addr, align 8, !dbg !1849
  store i64 -9223372036854775808, i64* %maxval, align 8, !dbg !1850
  %16 = load i32, i32* %base.addr, align 4, !dbg !1851
  %conv16 = sext i32 %16 to i64, !dbg !1851
  %div17 = sdiv i64 -9223372036854775808, %conv16, !dbg !1852
  %sub = sub nsw i64 0, %div17, !dbg !1853
  store i64 %sub, i64* %limit, align 8, !dbg !1854
  %17 = load i32, i32* %base.addr, align 4, !dbg !1855
  %conv18 = sext i32 %17 to i64, !dbg !1855
  %rem19 = srem i64 -9223372036854775808, %conv18, !dbg !1856
  store i64 %rem19, i64* %last_digit_limit, align 8, !dbg !1857
  br label %if.end, !dbg !1858

if.end:                                           ; preds = %if.then, %land.lhs.true, %while.end
  store i64 0, i64* %l, align 8, !dbg !1859
  %18 = load i64, i64* %char_cnt.addr, align 8, !dbg !1860
  %cmp20 = icmp ne i64 %18, 0, !dbg !1862
  br i1 %cmp20, label %if.then22, label %if.end53, !dbg !1863

if.then22:                                        ; preds = %if.end
  %19 = load i8*, i8** %p.addr, align 8, !dbg !1864
  %20 = load i8, i8* %19, align 1, !dbg !1866
  %conv23 = sext i8 %20 to i32, !dbg !1866
  %sub24 = sub nsw i32 %conv23, 48, !dbg !1867
  store i32 %sub24, i32* %digit, align 4, !dbg !1868
  br label %while.cond25, !dbg !1869

while.cond25:                                     ; preds = %if.end45, %if.then22
  %21 = load i32, i32* %digit, align 4, !dbg !1870
  %cmp26 = icmp sge i32 %21, 0, !dbg !1872
  br i1 %cmp26, label %land.lhs.true28, label %land.end34, !dbg !1873

land.lhs.true28:                                  ; preds = %while.cond25
  %22 = load i32, i32* %digit, align 4, !dbg !1874
  %23 = load i32, i32* %base.addr, align 4, !dbg !1876
  %cmp29 = icmp slt i32 %22, %23, !dbg !1877
  br i1 %cmp29, label %land.rhs31, label %land.end34, !dbg !1878

land.rhs31:                                       ; preds = %land.lhs.true28
  %24 = load i64, i64* %char_cnt.addr, align 8, !dbg !1879
  %cmp32 = icmp ne i64 %24, 0, !dbg !1881
  br label %land.end34

land.end34:                                       ; preds = %land.rhs31, %land.lhs.true28, %while.cond25
  %25 = phi i1 [ false, %land.lhs.true28 ], [ false, %while.cond25 ], [ %cmp32, %land.rhs31 ]
  br i1 %25, label %while.body35, label %while.end52, !dbg !1882

while.body35:                                     ; preds = %land.end34
  %26 = load i64, i64* %l, align 8, !dbg !1884
  %27 = load i64, i64* %limit, align 8, !dbg !1887
  %cmp36 = icmp sgt i64 %26, %27, !dbg !1888
  br i1 %cmp36, label %if.then44, label %lor.lhs.false, !dbg !1889

lor.lhs.false:                                    ; preds = %while.body35
  %28 = load i64, i64* %l, align 8, !dbg !1890
  %29 = load i64, i64* %limit, align 8, !dbg !1892
  %cmp38 = icmp eq i64 %28, %29, !dbg !1893
  br i1 %cmp38, label %land.lhs.true40, label %if.end45, !dbg !1894

land.lhs.true40:                                  ; preds = %lor.lhs.false
  %30 = load i32, i32* %digit, align 4, !dbg !1895
  %conv41 = sext i32 %30 to i64, !dbg !1895
  %31 = load i64, i64* %last_digit_limit, align 8, !dbg !1897
  %cmp42 = icmp sgt i64 %conv41, %31, !dbg !1898
  br i1 %cmp42, label %if.then44, label %if.end45, !dbg !1899

if.then44:                                        ; preds = %land.lhs.true40, %while.body35
  %32 = load i64, i64* %maxval, align 8, !dbg !1900
  store i64 %32, i64* %retval, align 8, !dbg !1902
  br label %return, !dbg !1902

if.end45:                                         ; preds = %land.lhs.true40, %lor.lhs.false
  %33 = load i64, i64* %l, align 8, !dbg !1903
  %34 = load i32, i32* %base.addr, align 4, !dbg !1904
  %conv46 = sext i32 %34 to i64, !dbg !1904
  %mul = mul nsw i64 %33, %conv46, !dbg !1905
  %35 = load i32, i32* %digit, align 4, !dbg !1906
  %conv47 = sext i32 %35 to i64, !dbg !1906
  %add = add nsw i64 %mul, %conv47, !dbg !1907
  store i64 %add, i64* %l, align 8, !dbg !1908
  %36 = load i8*, i8** %p.addr, align 8, !dbg !1909
  %incdec.ptr48 = getelementptr inbounds i8, i8* %36, i32 1, !dbg !1909
  store i8* %incdec.ptr48, i8** %p.addr, align 8, !dbg !1909
  %37 = load i8, i8* %incdec.ptr48, align 1, !dbg !1910
  %conv49 = sext i8 %37 to i32, !dbg !1910
  %sub50 = sub nsw i32 %conv49, 48, !dbg !1911
  store i32 %sub50, i32* %digit, align 4, !dbg !1912
  %38 = load i64, i64* %char_cnt.addr, align 8, !dbg !1913
  %dec51 = add i64 %38, -1, !dbg !1913
  store i64 %dec51, i64* %char_cnt.addr, align 8, !dbg !1913
  br label %while.cond25, !dbg !1914

while.end52:                                      ; preds = %land.end34
  br label %if.end53, !dbg !1916

if.end53:                                         ; preds = %while.end52, %if.end
  %39 = load i32, i32* %sign, align 4, !dbg !1917
  %cmp54 = icmp slt i32 %39, 0, !dbg !1918
  br i1 %cmp54, label %cond.true, label %cond.false, !dbg !1919

cond.true:                                        ; preds = %if.end53
  %40 = load i64, i64* %l, align 8, !dbg !1920
  %sub56 = sub nsw i64 0, %40, !dbg !1921
  br label %cond.end, !dbg !1922

cond.false:                                       ; preds = %if.end53
  %41 = load i64, i64* %l, align 8, !dbg !1923
  br label %cond.end, !dbg !1924

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ %sub56, %cond.true ], [ %41, %cond.false ], !dbg !1925
  store i64 %cond, i64* %retval, align 8, !dbg !1926
  br label %return, !dbg !1926

return:                                           ; preds = %cond.end, %if.then44
  %42 = load i64, i64* %retval, align 8, !dbg !1927
  ret i64 %42, !dbg !1927
}

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #4

declare %struct.archive_string_conv* @archive_string_conversion_from_charset(%struct.archive*, i8*, i32) #2

declare void @archive_entry_set_dev(%struct.archive_entry*, i64) #2

declare void @archive_entry_set_ino(%struct.archive_entry*, i64) #2

declare %struct.archive_string_conv* @archive_string_default_conversion_for_read(%struct.archive*) #2

; Function Attrs: nounwind uwtable
define internal i32 @tar_read_header(%struct.archive_read* %a, %struct.tar* %tar, %struct.archive_entry* %entry1, i64* %unconsumed) #0 !dbg !465 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %tar.addr = alloca %struct.tar*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %unconsumed.addr = alloca i64*, align 8
  %bytes = alloca i64, align 8
  %err = alloca i32, align 4
  %h = alloca i8*, align 8
  %header = alloca %struct.archive_entry_header_ustar*, align 8
  %gnuheader = alloca %struct.archive_entry_header_gnutar*, align 8
  %err2 = alloca i32, align 4
  %bytes_read = alloca i64, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !1928, metadata !563), !dbg !1929
  store %struct.tar* %tar, %struct.tar** %tar.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tar** %tar.addr, metadata !1930, metadata !563), !dbg !1931
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1932, metadata !563), !dbg !1933
  store i64* %unconsumed, i64** %unconsumed.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %unconsumed.addr, metadata !1934, metadata !563), !dbg !1935
  call void @llvm.dbg.declare(metadata i64* %bytes, metadata !1936, metadata !563), !dbg !1937
  call void @llvm.dbg.declare(metadata i32* %err, metadata !1938, metadata !563), !dbg !1939
  call void @llvm.dbg.declare(metadata i8** %h, metadata !1940, metadata !563), !dbg !1941
  call void @llvm.dbg.declare(metadata %struct.archive_entry_header_ustar** %header, metadata !1942, metadata !563), !dbg !1943
  call void @llvm.dbg.declare(metadata %struct.archive_entry_header_gnutar** %gnuheader, metadata !1944, metadata !563), !dbg !1945
  br label %for.cond, !dbg !1946

for.cond:                                         ; preds = %if.end40, %entry
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1947
  %1 = load i64*, i64** %unconsumed.addr, align 8, !dbg !1951
  call void @tar_flush_unconsumed(%struct.archive_read* %0, i64* %1), !dbg !1952
  %2 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1953
  %call = call i8* @__archive_read_ahead(%struct.archive_read* %2, i64 512, i64* %bytes), !dbg !1954
  store i8* %call, i8** %h, align 8, !dbg !1955
  %3 = load i64, i64* %bytes, align 8, !dbg !1956
  %cmp = icmp slt i64 %3, 0, !dbg !1958
  br i1 %cmp, label %if.then, label %if.end, !dbg !1959

if.then:                                          ; preds = %for.cond
  %4 = load i64, i64* %bytes, align 8, !dbg !1960
  %conv = trunc i64 %4 to i32, !dbg !1961
  store i32 %conv, i32* %retval, align 4, !dbg !1962
  br label %return, !dbg !1962

if.end:                                           ; preds = %for.cond
  %5 = load i64, i64* %bytes, align 8, !dbg !1963
  %cmp2 = icmp eq i64 %5, 0, !dbg !1965
  br i1 %cmp2, label %if.then4, label %if.end5, !dbg !1966

if.then4:                                         ; preds = %if.end
  store i32 1, i32* %retval, align 4, !dbg !1967
  br label %return, !dbg !1967

if.end5:                                          ; preds = %if.end
  %6 = load i64, i64* %bytes, align 8, !dbg !1969
  %cmp6 = icmp slt i64 %6, 512, !dbg !1971
  br i1 %cmp6, label %if.then8, label %if.end9, !dbg !1972

if.then8:                                         ; preds = %if.end5
  %7 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1973
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %7, i32 0, i32 0, !dbg !1975
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 84, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.13, i32 0, i32 0)), !dbg !1976
  store i32 -30, i32* %retval, align 4, !dbg !1977
  br label %return, !dbg !1977

if.end9:                                          ; preds = %if.end5
  %8 = load i64*, i64** %unconsumed.addr, align 8, !dbg !1978
  store i64 512, i64* %8, align 8, !dbg !1979
  %9 = load i8*, i8** %h, align 8, !dbg !1980
  %arrayidx = getelementptr inbounds i8, i8* %9, i64 0, !dbg !1980
  %10 = load i8, i8* %arrayidx, align 1, !dbg !1980
  %conv10 = sext i8 %10 to i32, !dbg !1980
  %cmp11 = icmp ne i32 %conv10, 0, !dbg !1982
  br i1 %cmp11, label %if.then14, label %lor.lhs.false, !dbg !1983

lor.lhs.false:                                    ; preds = %if.end9
  %11 = load i8*, i8** %h, align 8, !dbg !1984
  %call13 = call i32 @archive_block_is_null(i8* %11), !dbg !1986
  %tobool = icmp ne i32 %call13, 0, !dbg !1986
  br i1 %tobool, label %if.end15, label %if.then14, !dbg !1987

if.then14:                                        ; preds = %lor.lhs.false, %if.end9
  br label %for.end, !dbg !1988

if.end15:                                         ; preds = %lor.lhs.false
  %12 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1989
  %archive16 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %12, i32 0, i32 0, !dbg !1991
  %archive_format_name = getelementptr inbounds %struct.archive, %struct.archive* %archive16, i32 0, i32 4, !dbg !1992
  %13 = load i8*, i8** %archive_format_name, align 8, !dbg !1992
  %cmp17 = icmp eq i8* %13, null, !dbg !1993
  br i1 %cmp17, label %if.then19, label %if.end23, !dbg !1994

if.then19:                                        ; preds = %if.end15
  %14 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1995
  %archive20 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %14, i32 0, i32 0, !dbg !1997
  %archive_format = getelementptr inbounds %struct.archive, %struct.archive* %archive20, i32 0, i32 3, !dbg !1998
  store i32 196608, i32* %archive_format, align 8, !dbg !1999
  %15 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2000
  %archive21 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %15, i32 0, i32 0, !dbg !2001
  %archive_format_name22 = getelementptr inbounds %struct.archive, %struct.archive* %archive21, i32 0, i32 4, !dbg !2002
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.3, i32 0, i32 0), i8** %archive_format_name22, align 8, !dbg !2003
  br label %if.end23, !dbg !2004

if.end23:                                         ; preds = %if.then19, %if.end15
  %16 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2005
  %read_concatenated_archives = getelementptr inbounds %struct.tar, %struct.tar* %16, i32 0, i32 34, !dbg !2007
  %17 = load i32, i32* %read_concatenated_archives, align 4, !dbg !2007
  %tobool24 = icmp ne i32 %17, 0, !dbg !2005
  br i1 %tobool24, label %if.end40, label %if.then25, !dbg !2008

if.then25:                                        ; preds = %if.end23
  %18 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2009
  %19 = load i64*, i64** %unconsumed.addr, align 8, !dbg !2011
  call void @tar_flush_unconsumed(%struct.archive_read* %18, i64* %19), !dbg !2012
  %20 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2013
  %call26 = call i8* @__archive_read_ahead(%struct.archive_read* %20, i64 512, i64* null), !dbg !2014
  store i8* %call26, i8** %h, align 8, !dbg !2015
  %21 = load i8*, i8** %h, align 8, !dbg !2016
  %cmp27 = icmp ne i8* %21, null, !dbg !2018
  br i1 %cmp27, label %land.lhs.true, label %if.end38, !dbg !2019

land.lhs.true:                                    ; preds = %if.then25
  %22 = load i8*, i8** %h, align 8, !dbg !2020
  %arrayidx29 = getelementptr inbounds i8, i8* %22, i64 0, !dbg !2020
  %23 = load i8, i8* %arrayidx29, align 1, !dbg !2020
  %conv30 = sext i8 %23 to i32, !dbg !2020
  %cmp31 = icmp eq i32 %conv30, 0, !dbg !2022
  br i1 %cmp31, label %land.lhs.true33, label %if.end38, !dbg !2023

land.lhs.true33:                                  ; preds = %land.lhs.true
  %24 = load i8*, i8** %h, align 8, !dbg !2024
  %call34 = call i32 @archive_block_is_null(i8* %24), !dbg !2026
  %tobool35 = icmp ne i32 %call34, 0, !dbg !2026
  br i1 %tobool35, label %if.then36, label %if.end38, !dbg !2027

if.then36:                                        ; preds = %land.lhs.true33
  %25 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2028
  %call37 = call i64 @__archive_read_consume(%struct.archive_read* %25, i64 512), !dbg !2029
  br label %if.end38, !dbg !2029

if.end38:                                         ; preds = %if.then36, %land.lhs.true33, %land.lhs.true, %if.then25
  %26 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2030
  %archive39 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %26, i32 0, i32 0, !dbg !2031
  call void @archive_clear_error(%struct.archive* %archive39), !dbg !2032
  store i32 1, i32* %retval, align 4, !dbg !2033
  br label %return, !dbg !2033

if.end40:                                         ; preds = %if.end23
  br label %for.cond, !dbg !2034

for.end:                                          ; preds = %if.then14
  %27 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2036
  %28 = load i8*, i8** %h, align 8, !dbg !2038
  %call41 = call i32 @checksum(%struct.archive_read* %27, i8* %28), !dbg !2039
  %tobool42 = icmp ne i32 %call41, 0, !dbg !2039
  br i1 %tobool42, label %if.end45, label %if.then43, !dbg !2040

if.then43:                                        ; preds = %for.end
  %29 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2041
  %30 = load i64*, i64** %unconsumed.addr, align 8, !dbg !2043
  call void @tar_flush_unconsumed(%struct.archive_read* %29, i64* %30), !dbg !2044
  %31 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2045
  %archive44 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %31, i32 0, i32 0, !dbg !2046
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive44, i32 22, i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.14, i32 0, i32 0)), !dbg !2047
  store i32 -10, i32* %retval, align 4, !dbg !2048
  br label %return, !dbg !2048

if.end45:                                         ; preds = %for.end
  %32 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2049
  %header_recursion_depth = getelementptr inbounds %struct.tar, %struct.tar* %32, i32 0, i32 12, !dbg !2051
  %33 = load i32, i32* %header_recursion_depth, align 4, !dbg !2052
  %inc = add nsw i32 %33, 1, !dbg !2052
  store i32 %inc, i32* %header_recursion_depth, align 4, !dbg !2052
  %cmp46 = icmp sgt i32 %inc, 32, !dbg !2053
  br i1 %cmp46, label %if.then48, label %if.end50, !dbg !2054

if.then48:                                        ; preds = %if.end45
  %34 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2055
  %35 = load i64*, i64** %unconsumed.addr, align 8, !dbg !2057
  call void @tar_flush_unconsumed(%struct.archive_read* %34, i64* %35), !dbg !2058
  %36 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2059
  %archive49 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %36, i32 0, i32 0, !dbg !2060
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive49, i32 22, i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.15, i32 0, i32 0)), !dbg !2061
  store i32 -20, i32* %retval, align 4, !dbg !2062
  br label %return, !dbg !2062

if.end50:                                         ; preds = %if.end45
  %37 = load i8*, i8** %h, align 8, !dbg !2063
  %38 = bitcast i8* %37 to %struct.archive_entry_header_ustar*, !dbg !2064
  store %struct.archive_entry_header_ustar* %38, %struct.archive_entry_header_ustar** %header, align 8, !dbg !2065
  %39 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !2066
  %typeflag = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %39, i32 0, i32 7, !dbg !2067
  %arrayidx51 = getelementptr inbounds [1 x i8], [1 x i8]* %typeflag, i64 0, i64 0, !dbg !2066
  %40 = load i8, i8* %arrayidx51, align 1, !dbg !2066
  %conv52 = sext i8 %40 to i32, !dbg !2066
  switch i32 %conv52, label %sw.default [
    i32 65, label %sw.bb
    i32 103, label %sw.bb58
    i32 75, label %sw.bb68
    i32 76, label %sw.bb70
    i32 86, label %sw.bb72
    i32 88, label %sw.bb74
    i32 120, label %sw.bb80
  ], !dbg !2068

sw.bb:                                            ; preds = %if.end50
  %41 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2069
  %archive53 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %41, i32 0, i32 0, !dbg !2071
  %archive_format54 = getelementptr inbounds %struct.archive, %struct.archive* %archive53, i32 0, i32 3, !dbg !2072
  store i32 196610, i32* %archive_format54, align 8, !dbg !2073
  %42 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2074
  %archive55 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %42, i32 0, i32 0, !dbg !2075
  %archive_format_name56 = getelementptr inbounds %struct.archive, %struct.archive* %archive55, i32 0, i32 4, !dbg !2076
  store i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.16, i32 0, i32 0), i8** %archive_format_name56, align 8, !dbg !2077
  %43 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2078
  %44 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2079
  %45 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2080
  %46 = load i8*, i8** %h, align 8, !dbg !2081
  %47 = load i64*, i64** %unconsumed.addr, align 8, !dbg !2082
  %call57 = call i32 @header_Solaris_ACL(%struct.archive_read* %43, %struct.tar* %44, %struct.archive_entry* %45, i8* %46, i64* %47), !dbg !2083
  store i32 %call57, i32* %err, align 4, !dbg !2084
  br label %sw.epilog, !dbg !2085

sw.bb58:                                          ; preds = %if.end50
  %48 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2086
  %archive59 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %48, i32 0, i32 0, !dbg !2087
  %archive_format60 = getelementptr inbounds %struct.archive, %struct.archive* %archive59, i32 0, i32 3, !dbg !2088
  store i32 196610, i32* %archive_format60, align 8, !dbg !2089
  %49 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2090
  %archive61 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %49, i32 0, i32 0, !dbg !2091
  %archive_format_name62 = getelementptr inbounds %struct.archive, %struct.archive* %archive61, i32 0, i32 4, !dbg !2092
  store i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.17, i32 0, i32 0), i8** %archive_format_name62, align 8, !dbg !2093
  %50 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2094
  %51 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2095
  %52 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2096
  %53 = load i8*, i8** %h, align 8, !dbg !2097
  %54 = load i64*, i64** %unconsumed.addr, align 8, !dbg !2098
  %call63 = call i32 @header_pax_global(%struct.archive_read* %50, %struct.tar* %51, %struct.archive_entry* %52, i8* %53, i64* %54), !dbg !2099
  store i32 %call63, i32* %err, align 4, !dbg !2100
  %55 = load i32, i32* %err, align 4, !dbg !2101
  %cmp64 = icmp eq i32 %55, 1, !dbg !2103
  br i1 %cmp64, label %if.then66, label %if.end67, !dbg !2104

if.then66:                                        ; preds = %sw.bb58
  %56 = load i32, i32* %err, align 4, !dbg !2105
  store i32 %56, i32* %retval, align 4, !dbg !2106
  br label %return, !dbg !2106

if.end67:                                         ; preds = %sw.bb58
  br label %sw.epilog, !dbg !2107

sw.bb68:                                          ; preds = %if.end50
  %57 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2108
  %58 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2109
  %59 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2110
  %60 = load i8*, i8** %h, align 8, !dbg !2111
  %61 = load i64*, i64** %unconsumed.addr, align 8, !dbg !2112
  %call69 = call i32 @header_longlink(%struct.archive_read* %57, %struct.tar* %58, %struct.archive_entry* %59, i8* %60, i64* %61), !dbg !2113
  store i32 %call69, i32* %err, align 4, !dbg !2114
  br label %sw.epilog, !dbg !2115

sw.bb70:                                          ; preds = %if.end50
  %62 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2116
  %63 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2117
  %64 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2118
  %65 = load i8*, i8** %h, align 8, !dbg !2119
  %66 = load i64*, i64** %unconsumed.addr, align 8, !dbg !2120
  %call71 = call i32 @header_longname(%struct.archive_read* %62, %struct.tar* %63, %struct.archive_entry* %64, i8* %65, i64* %66), !dbg !2121
  store i32 %call71, i32* %err, align 4, !dbg !2122
  br label %sw.epilog, !dbg !2123

sw.bb72:                                          ; preds = %if.end50
  %67 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2124
  %68 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2125
  %69 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2126
  %70 = load i8*, i8** %h, align 8, !dbg !2127
  %71 = load i64*, i64** %unconsumed.addr, align 8, !dbg !2128
  %call73 = call i32 @header_volume(%struct.archive_read* %67, %struct.tar* %68, %struct.archive_entry* %69, i8* %70, i64* %71), !dbg !2129
  store i32 %call73, i32* %err, align 4, !dbg !2130
  br label %sw.epilog, !dbg !2131

sw.bb74:                                          ; preds = %if.end50
  %72 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2132
  %archive75 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %72, i32 0, i32 0, !dbg !2133
  %archive_format76 = getelementptr inbounds %struct.archive, %struct.archive* %archive75, i32 0, i32 3, !dbg !2134
  store i32 196610, i32* %archive_format76, align 8, !dbg !2135
  %73 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2136
  %archive77 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %73, i32 0, i32 0, !dbg !2137
  %archive_format_name78 = getelementptr inbounds %struct.archive, %struct.archive* %archive77, i32 0, i32 4, !dbg !2138
  store i8* getelementptr inbounds ([43 x i8], [43 x i8]* @.str.18, i32 0, i32 0), i8** %archive_format_name78, align 8, !dbg !2139
  %74 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2140
  %75 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2141
  %76 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2142
  %77 = load i8*, i8** %h, align 8, !dbg !2143
  %78 = load i64*, i64** %unconsumed.addr, align 8, !dbg !2144
  %call79 = call i32 @header_pax_extensions(%struct.archive_read* %74, %struct.tar* %75, %struct.archive_entry* %76, i8* %77, i64* %78), !dbg !2145
  store i32 %call79, i32* %err, align 4, !dbg !2146
  br label %sw.epilog, !dbg !2147

sw.bb80:                                          ; preds = %if.end50
  %79 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2148
  %archive81 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %79, i32 0, i32 0, !dbg !2149
  %archive_format82 = getelementptr inbounds %struct.archive, %struct.archive* %archive81, i32 0, i32 3, !dbg !2150
  store i32 196610, i32* %archive_format82, align 8, !dbg !2151
  %80 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2152
  %archive83 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %80, i32 0, i32 0, !dbg !2153
  %archive_format_name84 = getelementptr inbounds %struct.archive, %struct.archive* %archive83, i32 0, i32 4, !dbg !2154
  store i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.17, i32 0, i32 0), i8** %archive_format_name84, align 8, !dbg !2155
  %81 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2156
  %82 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2157
  %83 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2158
  %84 = load i8*, i8** %h, align 8, !dbg !2159
  %85 = load i64*, i64** %unconsumed.addr, align 8, !dbg !2160
  %call85 = call i32 @header_pax_extensions(%struct.archive_read* %81, %struct.tar* %82, %struct.archive_entry* %83, i8* %84, i64* %85), !dbg !2161
  store i32 %call85, i32* %err, align 4, !dbg !2162
  br label %sw.epilog, !dbg !2163

sw.default:                                       ; preds = %if.end50
  %86 = load i8*, i8** %h, align 8, !dbg !2164
  %87 = bitcast i8* %86 to %struct.archive_entry_header_gnutar*, !dbg !2165
  store %struct.archive_entry_header_gnutar* %87, %struct.archive_entry_header_gnutar** %gnuheader, align 8, !dbg !2166
  %88 = load %struct.archive_entry_header_gnutar*, %struct.archive_entry_header_gnutar** %gnuheader, align 8, !dbg !2167
  %magic = getelementptr inbounds %struct.archive_entry_header_gnutar, %struct.archive_entry_header_gnutar* %88, i32 0, i32 9, !dbg !2169
  %arraydecay = getelementptr inbounds [8 x i8], [8 x i8]* %magic, i32 0, i32 0, !dbg !2167
  %call86 = call i32 @memcmp(i8* %arraydecay, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.19, i32 0, i32 0), i64 8) #8, !dbg !2170
  %cmp87 = icmp eq i32 %call86, 0, !dbg !2171
  br i1 %cmp87, label %if.then89, label %if.else, !dbg !2172

if.then89:                                        ; preds = %sw.default
  %89 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2173
  %archive90 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %89, i32 0, i32 0, !dbg !2175
  %archive_format91 = getelementptr inbounds %struct.archive, %struct.archive* %archive90, i32 0, i32 3, !dbg !2176
  store i32 196612, i32* %archive_format91, align 8, !dbg !2177
  %90 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2178
  %archive92 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %90, i32 0, i32 0, !dbg !2179
  %archive_format_name93 = getelementptr inbounds %struct.archive, %struct.archive* %archive92, i32 0, i32 4, !dbg !2180
  store i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.20, i32 0, i32 0), i8** %archive_format_name93, align 8, !dbg !2181
  %91 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2182
  %92 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2183
  %93 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2184
  %94 = load i8*, i8** %h, align 8, !dbg !2185
  %95 = load i64*, i64** %unconsumed.addr, align 8, !dbg !2186
  %call94 = call i32 @header_gnutar(%struct.archive_read* %91, %struct.tar* %92, %struct.archive_entry* %93, i8* %94, i64* %95), !dbg !2187
  store i32 %call94, i32* %err, align 4, !dbg !2188
  br label %if.end119, !dbg !2189

if.else:                                          ; preds = %sw.default
  %96 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !2190
  %magic95 = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %96, i32 0, i32 9, !dbg !2193
  %arraydecay96 = getelementptr inbounds [6 x i8], [6 x i8]* %magic95, i32 0, i32 0, !dbg !2190
  %call97 = call i32 @memcmp(i8* %arraydecay96, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.21, i32 0, i32 0), i64 5) #8, !dbg !2194
  %cmp98 = icmp eq i32 %call97, 0, !dbg !2195
  br i1 %cmp98, label %if.then100, label %if.else112, !dbg !2194

if.then100:                                       ; preds = %if.else
  %97 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2196
  %archive101 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %97, i32 0, i32 0, !dbg !2199
  %archive_format102 = getelementptr inbounds %struct.archive, %struct.archive* %archive101, i32 0, i32 3, !dbg !2200
  %98 = load i32, i32* %archive_format102, align 8, !dbg !2200
  %cmp103 = icmp ne i32 %98, 196610, !dbg !2201
  br i1 %cmp103, label %if.then105, label %if.end110, !dbg !2202

if.then105:                                       ; preds = %if.then100
  %99 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2203
  %archive106 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %99, i32 0, i32 0, !dbg !2205
  %archive_format107 = getelementptr inbounds %struct.archive, %struct.archive* %archive106, i32 0, i32 3, !dbg !2206
  store i32 196609, i32* %archive_format107, align 8, !dbg !2207
  %100 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2208
  %archive108 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %100, i32 0, i32 0, !dbg !2209
  %archive_format_name109 = getelementptr inbounds %struct.archive, %struct.archive* %archive108, i32 0, i32 4, !dbg !2210
  store i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.22, i32 0, i32 0), i8** %archive_format_name109, align 8, !dbg !2211
  br label %if.end110, !dbg !2212

if.end110:                                        ; preds = %if.then105, %if.then100
  %101 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2213
  %102 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2214
  %103 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2215
  %104 = load i8*, i8** %h, align 8, !dbg !2216
  %call111 = call i32 @header_ustar(%struct.archive_read* %101, %struct.tar* %102, %struct.archive_entry* %103, i8* %104), !dbg !2217
  store i32 %call111, i32* %err, align 4, !dbg !2218
  br label %if.end118, !dbg !2219

if.else112:                                       ; preds = %if.else
  %105 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2220
  %archive113 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %105, i32 0, i32 0, !dbg !2222
  %archive_format114 = getelementptr inbounds %struct.archive, %struct.archive* %archive113, i32 0, i32 3, !dbg !2223
  store i32 196608, i32* %archive_format114, align 8, !dbg !2224
  %106 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2225
  %archive115 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %106, i32 0, i32 0, !dbg !2226
  %archive_format_name116 = getelementptr inbounds %struct.archive, %struct.archive* %archive115, i32 0, i32 4, !dbg !2227
  store i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.23, i32 0, i32 0), i8** %archive_format_name116, align 8, !dbg !2228
  %107 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2229
  %108 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2230
  %109 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2231
  %110 = load i8*, i8** %h, align 8, !dbg !2232
  %call117 = call i32 @header_old_tar(%struct.archive_read* %107, %struct.tar* %108, %struct.archive_entry* %109, i8* %110), !dbg !2233
  store i32 %call117, i32* %err, align 4, !dbg !2234
  br label %if.end118

if.end118:                                        ; preds = %if.else112, %if.end110
  br label %if.end119

if.end119:                                        ; preds = %if.end118, %if.then89
  br label %sw.epilog, !dbg !2235

sw.epilog:                                        ; preds = %if.end119, %sw.bb80, %sw.bb74, %sw.bb72, %sw.bb70, %sw.bb68, %if.end67, %sw.bb
  %111 = load i32, i32* %err, align 4, !dbg !2236
  %cmp120 = icmp eq i32 %111, -30, !dbg !2238
  br i1 %cmp120, label %if.then122, label %if.end123, !dbg !2239

if.then122:                                       ; preds = %sw.epilog
  %112 = load i32, i32* %err, align 4, !dbg !2240
  store i32 %112, i32* %retval, align 4, !dbg !2241
  br label %return, !dbg !2241

if.end123:                                        ; preds = %sw.epilog
  %113 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2242
  %114 = load i64*, i64** %unconsumed.addr, align 8, !dbg !2243
  call void @tar_flush_unconsumed(%struct.archive_read* %113, i64* %114), !dbg !2244
  store i8* null, i8** %h, align 8, !dbg !2245
  store %struct.archive_entry_header_ustar* null, %struct.archive_entry_header_ustar** %header, align 8, !dbg !2246
  %115 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2247
  %header_recursion_depth124 = getelementptr inbounds %struct.tar, %struct.tar* %115, i32 0, i32 12, !dbg !2248
  %116 = load i32, i32* %header_recursion_depth124, align 4, !dbg !2249
  %dec = add nsw i32 %116, -1, !dbg !2249
  store i32 %dec, i32* %header_recursion_depth124, align 4, !dbg !2249
  %117 = load i32, i32* %err, align 4, !dbg !2250
  %cmp125 = icmp eq i32 %117, -20, !dbg !2252
  br i1 %cmp125, label %land.lhs.true130, label %lor.lhs.false127, !dbg !2253

lor.lhs.false127:                                 ; preds = %if.end123
  %118 = load i32, i32* %err, align 4, !dbg !2254
  %cmp128 = icmp eq i32 %118, 0, !dbg !2256
  br i1 %cmp128, label %land.lhs.true130, label %if.end142, !dbg !2257

land.lhs.true130:                                 ; preds = %lor.lhs.false127, %if.end123
  %119 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2258
  %header_recursion_depth131 = getelementptr inbounds %struct.tar, %struct.tar* %119, i32 0, i32 12, !dbg !2259
  %120 = load i32, i32* %header_recursion_depth131, align 4, !dbg !2259
  %cmp132 = icmp eq i32 %120, 0, !dbg !2260
  br i1 %cmp132, label %land.lhs.true134, label %if.end142, !dbg !2261

land.lhs.true134:                                 ; preds = %land.lhs.true130
  %121 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2262
  %process_mac_extensions = getelementptr inbounds %struct.tar, %struct.tar* %121, i32 0, i32 33, !dbg !2263
  %122 = load i32, i32* %process_mac_extensions, align 8, !dbg !2263
  %tobool135 = icmp ne i32 %122, 0, !dbg !2262
  br i1 %tobool135, label %if.then136, label %if.end142, !dbg !2264

if.then136:                                       ; preds = %land.lhs.true134
  call void @llvm.dbg.declare(metadata i32* %err2, metadata !2266, metadata !563), !dbg !2268
  %123 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2269
  %124 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2270
  %125 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2271
  %126 = load i8*, i8** %h, align 8, !dbg !2272
  %127 = load i64*, i64** %unconsumed.addr, align 8, !dbg !2273
  %call137 = call i32 @read_mac_metadata_blob(%struct.archive_read* %123, %struct.tar* %124, %struct.archive_entry* %125, i8* %126, i64* %127), !dbg !2274
  store i32 %call137, i32* %err2, align 4, !dbg !2268
  %128 = load i32, i32* %err2, align 4, !dbg !2275
  %129 = load i32, i32* %err, align 4, !dbg !2277
  %cmp138 = icmp slt i32 %128, %129, !dbg !2278
  br i1 %cmp138, label %if.then140, label %if.end141, !dbg !2279

if.then140:                                       ; preds = %if.then136
  %130 = load i32, i32* %err2, align 4, !dbg !2280
  store i32 %130, i32* %err, align 4, !dbg !2281
  br label %if.end141, !dbg !2282

if.end141:                                        ; preds = %if.then140, %if.then136
  br label %if.end142, !dbg !2283

if.end142:                                        ; preds = %if.end141, %land.lhs.true134, %land.lhs.true130, %lor.lhs.false127
  %131 = load i32, i32* %err, align 4, !dbg !2284
  %cmp143 = icmp eq i32 %131, -20, !dbg !2286
  br i1 %cmp143, label %if.then148, label %lor.lhs.false145, !dbg !2287

lor.lhs.false145:                                 ; preds = %if.end142
  %132 = load i32, i32* %err, align 4, !dbg !2288
  %cmp146 = icmp eq i32 %132, 0, !dbg !2290
  br i1 %cmp146, label %if.then148, label %if.end169, !dbg !2291

if.then148:                                       ; preds = %lor.lhs.false145, %if.end142
  %133 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2292
  %sparse_gnu_pending = getelementptr inbounds %struct.tar, %struct.tar* %133, i32 0, i32 25, !dbg !2295
  %134 = load i8, i8* %sparse_gnu_pending, align 8, !dbg !2295
  %tobool149 = icmp ne i8 %134, 0, !dbg !2292
  br i1 %tobool149, label %if.then150, label %if.end168, !dbg !2296

if.then150:                                       ; preds = %if.then148
  %135 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2297
  %sparse_gnu_major = getelementptr inbounds %struct.tar, %struct.tar* %135, i32 0, i32 23, !dbg !2300
  %136 = load i32, i32* %sparse_gnu_major, align 8, !dbg !2300
  %cmp151 = icmp eq i32 %136, 1, !dbg !2301
  br i1 %cmp151, label %land.lhs.true153, label %if.else164, !dbg !2302

land.lhs.true153:                                 ; preds = %if.then150
  %137 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2303
  %sparse_gnu_minor = getelementptr inbounds %struct.tar, %struct.tar* %137, i32 0, i32 24, !dbg !2304
  %138 = load i32, i32* %sparse_gnu_minor, align 4, !dbg !2304
  %cmp154 = icmp eq i32 %138, 0, !dbg !2305
  br i1 %cmp154, label %if.then156, label %if.else164, !dbg !2306

if.then156:                                       ; preds = %land.lhs.true153
  call void @llvm.dbg.declare(metadata i64* %bytes_read, metadata !2308, metadata !563), !dbg !2310
  %139 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2311
  %sparse_gnu_pending157 = getelementptr inbounds %struct.tar, %struct.tar* %139, i32 0, i32 25, !dbg !2312
  store i8 0, i8* %sparse_gnu_pending157, align 8, !dbg !2313
  %140 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2314
  %141 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2315
  %142 = load i64*, i64** %unconsumed.addr, align 8, !dbg !2316
  %call158 = call i64 @gnu_sparse_10_read(%struct.archive_read* %140, %struct.tar* %141, i64* %142), !dbg !2317
  store i64 %call158, i64* %bytes_read, align 8, !dbg !2318
  %143 = load i64, i64* %bytes_read, align 8, !dbg !2319
  %cmp159 = icmp slt i64 %143, 0, !dbg !2321
  br i1 %cmp159, label %if.then161, label %if.end163, !dbg !2322

if.then161:                                       ; preds = %if.then156
  %144 = load i64, i64* %bytes_read, align 8, !dbg !2323
  %conv162 = trunc i64 %144 to i32, !dbg !2324
  store i32 %conv162, i32* %retval, align 4, !dbg !2325
  br label %return, !dbg !2325

if.end163:                                        ; preds = %if.then156
  %145 = load i64, i64* %bytes_read, align 8, !dbg !2326
  %146 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2327
  %entry_bytes_remaining = getelementptr inbounds %struct.tar, %struct.tar* %146, i32 0, i32 13, !dbg !2328
  %147 = load i64, i64* %entry_bytes_remaining, align 8, !dbg !2329
  %sub = sub nsw i64 %147, %145, !dbg !2329
  store i64 %sub, i64* %entry_bytes_remaining, align 8, !dbg !2329
  br label %if.end166, !dbg !2330

if.else164:                                       ; preds = %land.lhs.true153, %if.then150
  %148 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2331
  %archive165 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %148, i32 0, i32 0, !dbg !2333
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive165, i32 -1, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.24, i32 0, i32 0)), !dbg !2334
  store i32 -20, i32* %retval, align 4, !dbg !2335
  br label %return, !dbg !2335

if.end166:                                        ; preds = %if.end163
  %149 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2336
  %sparse_gnu_pending167 = getelementptr inbounds %struct.tar, %struct.tar* %149, i32 0, i32 25, !dbg !2337
  store i8 0, i8* %sparse_gnu_pending167, align 8, !dbg !2338
  br label %if.end168, !dbg !2339

if.end168:                                        ; preds = %if.end166, %if.then148
  %150 = load i32, i32* %err, align 4, !dbg !2340
  store i32 %150, i32* %retval, align 4, !dbg !2341
  br label %return, !dbg !2341

if.end169:                                        ; preds = %lor.lhs.false145
  %151 = load i32, i32* %err, align 4, !dbg !2342
  %cmp170 = icmp eq i32 %151, 1, !dbg !2344
  br i1 %cmp170, label %if.then172, label %if.end174, !dbg !2345

if.then172:                                       ; preds = %if.end169
  %152 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2346
  %archive173 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %152, i32 0, i32 0, !dbg !2347
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive173, i32 22, i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.14, i32 0, i32 0)), !dbg !2348
  br label %if.end174, !dbg !2348

if.end174:                                        ; preds = %if.then172, %if.end169
  store i32 -30, i32* %retval, align 4, !dbg !2349
  br label %return, !dbg !2349

return:                                           ; preds = %if.end174, %if.end168, %if.else164, %if.then161, %if.then122, %if.then66, %if.then48, %if.then43, %if.end38, %if.then8, %if.then4, %if.then
  %153 = load i32, i32* %retval, align 4, !dbg !2350
  ret i32 %153, !dbg !2350
}

; Function Attrs: nounwind uwtable
define internal void @tar_flush_unconsumed(%struct.archive_read* %a, i64* %unconsumed) #0 !dbg !540 {
entry:
  %a.addr = alloca %struct.archive_read*, align 8
  %unconsumed.addr = alloca i64*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !2351, metadata !563), !dbg !2352
  store i64* %unconsumed, i64** %unconsumed.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %unconsumed.addr, metadata !2353, metadata !563), !dbg !2354
  %0 = load i64*, i64** %unconsumed.addr, align 8, !dbg !2355
  %1 = load i64, i64* %0, align 8, !dbg !2357
  %tobool = icmp ne i64 %1, 0, !dbg !2357
  br i1 %tobool, label %if.then, label %if.end, !dbg !2358

if.then:                                          ; preds = %entry
  %2 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2359
  %3 = load i64*, i64** %unconsumed.addr, align 8, !dbg !2361
  %4 = load i64, i64* %3, align 8, !dbg !2362
  %call = call i64 @__archive_read_consume(%struct.archive_read* %2, i64 %4), !dbg !2363
  %5 = load i64*, i64** %unconsumed.addr, align 8, !dbg !2364
  store i64 0, i64* %5, align 8, !dbg !2365
  br label %if.end, !dbg !2366

if.end:                                           ; preds = %if.then, %entry
  ret void, !dbg !2367
}

; Function Attrs: nounwind uwtable
define internal i32 @gnu_add_sparse_entry(%struct.archive_read* %a, %struct.tar* %tar, i64 %offset, i64 %remaining) #0 !dbg !543 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %tar.addr = alloca %struct.tar*, align 8
  %offset.addr = alloca i64, align 8
  %remaining.addr = alloca i64, align 8
  %p = alloca %struct.sparse_block*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !2368, metadata !563), !dbg !2369
  store %struct.tar* %tar, %struct.tar** %tar.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tar** %tar.addr, metadata !2370, metadata !563), !dbg !2371
  store i64 %offset, i64* %offset.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %offset.addr, metadata !2372, metadata !563), !dbg !2373
  store i64 %remaining, i64* %remaining.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %remaining.addr, metadata !2374, metadata !563), !dbg !2375
  call void @llvm.dbg.declare(metadata %struct.sparse_block** %p, metadata !2376, metadata !563), !dbg !2377
  %call = call noalias i8* @calloc(i64 1, i64 32) #7, !dbg !2378
  %0 = bitcast i8* %call to %struct.sparse_block*, !dbg !2379
  store %struct.sparse_block* %0, %struct.sparse_block** %p, align 8, !dbg !2380
  %1 = load %struct.sparse_block*, %struct.sparse_block** %p, align 8, !dbg !2381
  %cmp = icmp eq %struct.sparse_block* %1, null, !dbg !2383
  br i1 %cmp, label %if.then, label %if.end, !dbg !2384

if.then:                                          ; preds = %entry
  %2 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2385
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %2, i32 0, i32 0, !dbg !2387
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.94, i32 0, i32 0)), !dbg !2388
  store i32 -30, i32* %retval, align 4, !dbg !2389
  br label %return, !dbg !2389

if.end:                                           ; preds = %entry
  %3 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2390
  %sparse_last = getelementptr inbounds %struct.tar, %struct.tar* %3, i32 0, i32 20, !dbg !2392
  %4 = load %struct.sparse_block*, %struct.sparse_block** %sparse_last, align 8, !dbg !2392
  %cmp1 = icmp ne %struct.sparse_block* %4, null, !dbg !2393
  br i1 %cmp1, label %if.then2, label %if.else, !dbg !2394

if.then2:                                         ; preds = %if.end
  %5 = load %struct.sparse_block*, %struct.sparse_block** %p, align 8, !dbg !2395
  %6 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2396
  %sparse_last3 = getelementptr inbounds %struct.tar, %struct.tar* %6, i32 0, i32 20, !dbg !2397
  %7 = load %struct.sparse_block*, %struct.sparse_block** %sparse_last3, align 8, !dbg !2397
  %next = getelementptr inbounds %struct.sparse_block, %struct.sparse_block* %7, i32 0, i32 0, !dbg !2398
  store %struct.sparse_block* %5, %struct.sparse_block** %next, align 8, !dbg !2399
  br label %if.end4, !dbg !2396

if.else:                                          ; preds = %if.end
  %8 = load %struct.sparse_block*, %struct.sparse_block** %p, align 8, !dbg !2400
  %9 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2401
  %sparse_list = getelementptr inbounds %struct.tar, %struct.tar* %9, i32 0, i32 19, !dbg !2402
  store %struct.sparse_block* %8, %struct.sparse_block** %sparse_list, align 8, !dbg !2403
  br label %if.end4

if.end4:                                          ; preds = %if.else, %if.then2
  %10 = load %struct.sparse_block*, %struct.sparse_block** %p, align 8, !dbg !2404
  %11 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2405
  %sparse_last5 = getelementptr inbounds %struct.tar, %struct.tar* %11, i32 0, i32 20, !dbg !2406
  store %struct.sparse_block* %10, %struct.sparse_block** %sparse_last5, align 8, !dbg !2407
  %12 = load i64, i64* %remaining.addr, align 8, !dbg !2408
  %cmp6 = icmp slt i64 %12, 0, !dbg !2410
  br i1 %cmp6, label %if.then8, label %lor.lhs.false, !dbg !2411

lor.lhs.false:                                    ; preds = %if.end4
  %13 = load i64, i64* %offset.addr, align 8, !dbg !2412
  %cmp7 = icmp slt i64 %13, 0, !dbg !2414
  br i1 %cmp7, label %if.then8, label %if.end10, !dbg !2415

if.then8:                                         ; preds = %lor.lhs.false, %if.end4
  %14 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2416
  %archive9 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %14, i32 0, i32 0, !dbg !2418
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive9, i32 -1, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.95, i32 0, i32 0)), !dbg !2419
  store i32 -30, i32* %retval, align 4, !dbg !2420
  br label %return, !dbg !2420

if.end10:                                         ; preds = %lor.lhs.false
  %15 = load i64, i64* %offset.addr, align 8, !dbg !2421
  %16 = load %struct.sparse_block*, %struct.sparse_block** %p, align 8, !dbg !2422
  %offset11 = getelementptr inbounds %struct.sparse_block, %struct.sparse_block* %16, i32 0, i32 1, !dbg !2423
  store i64 %15, i64* %offset11, align 8, !dbg !2424
  %17 = load i64, i64* %remaining.addr, align 8, !dbg !2425
  %18 = load %struct.sparse_block*, %struct.sparse_block** %p, align 8, !dbg !2426
  %remaining12 = getelementptr inbounds %struct.sparse_block, %struct.sparse_block* %18, i32 0, i32 2, !dbg !2427
  store i64 %17, i64* %remaining12, align 8, !dbg !2428
  store i32 0, i32* %retval, align 4, !dbg !2429
  br label %return, !dbg !2429

return:                                           ; preds = %if.end10, %if.then8, %if.then
  %19 = load i32, i32* %retval, align 4, !dbg !2430
  ret i32 %19, !dbg !2430
}

declare void @archive_entry_sparse_add_entry(%struct.archive_entry*, i64, i64) #2

declare i32 @archive_entry_filetype(%struct.archive_entry*) #2

declare i32* @archive_entry_pathname_w(%struct.archive_entry*) #2

; Function Attrs: nounwind readonly
declare i64 @wcslen(i32*) #4

declare void @archive_entry_set_filetype(%struct.archive_entry*, i32) #2

declare i8* @archive_entry_pathname(%struct.archive_entry*) #2

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #4

declare i64 @__archive_read_consume(%struct.archive_read*, i64) #2

declare void @archive_clear_error(%struct.archive*) #2

; Function Attrs: nounwind uwtable
define internal i32 @header_Solaris_ACL(%struct.archive_read* %a, %struct.tar* %tar, %struct.archive_entry* %entry1, i8* %h, i64* %unconsumed) #0 !dbg !468 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %tar.addr = alloca %struct.tar*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %h.addr = alloca i8*, align 8
  %unconsumed.addr = alloca i64*, align 8
  %header = alloca %struct.archive_entry_header_ustar*, align 8
  %size = alloca i64, align 8
  %err = alloca i32, align 4
  %acl_type = alloca i32, align 4
  %type = alloca i64, align 8
  %acl = alloca i8*, align 8
  %p = alloca i8*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !2431, metadata !563), !dbg !2432
  store %struct.tar* %tar, %struct.tar** %tar.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tar** %tar.addr, metadata !2433, metadata !563), !dbg !2434
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2435, metadata !563), !dbg !2436
  store i8* %h, i8** %h.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %h.addr, metadata !2437, metadata !563), !dbg !2438
  store i64* %unconsumed, i64** %unconsumed.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %unconsumed.addr, metadata !2439, metadata !563), !dbg !2440
  call void @llvm.dbg.declare(metadata %struct.archive_entry_header_ustar** %header, metadata !2441, metadata !563), !dbg !2442
  call void @llvm.dbg.declare(metadata i64* %size, metadata !2443, metadata !563), !dbg !2444
  call void @llvm.dbg.declare(metadata i32* %err, metadata !2445, metadata !563), !dbg !2446
  call void @llvm.dbg.declare(metadata i32* %acl_type, metadata !2447, metadata !563), !dbg !2448
  call void @llvm.dbg.declare(metadata i64* %type, metadata !2449, metadata !563), !dbg !2450
  call void @llvm.dbg.declare(metadata i8** %acl, metadata !2451, metadata !563), !dbg !2452
  call void @llvm.dbg.declare(metadata i8** %p, metadata !2453, metadata !563), !dbg !2454
  %0 = load i8*, i8** %h.addr, align 8, !dbg !2455
  %1 = bitcast i8* %0 to %struct.archive_entry_header_ustar*, !dbg !2456
  store %struct.archive_entry_header_ustar* %1, %struct.archive_entry_header_ustar** %header, align 8, !dbg !2457
  %2 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !2458
  %size2 = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %2, i32 0, i32 4, !dbg !2459
  %arraydecay = getelementptr inbounds [12 x i8], [12 x i8]* %size2, i32 0, i32 0, !dbg !2458
  %call = call i64 @tar_atol(i8* %arraydecay, i64 12), !dbg !2460
  store i64 %call, i64* %size, align 8, !dbg !2461
  %3 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2462
  %4 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2463
  %5 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2464
  %acl_text = getelementptr inbounds %struct.tar, %struct.tar* %5, i32 0, i32 0, !dbg !2465
  %6 = load i8*, i8** %h.addr, align 8, !dbg !2466
  %7 = load i64*, i64** %unconsumed.addr, align 8, !dbg !2467
  %call3 = call i32 @read_body_to_string(%struct.archive_read* %3, %struct.tar* %4, %struct.archive_string* %acl_text, i8* %6, i64* %7), !dbg !2468
  store i32 %call3, i32* %err, align 4, !dbg !2469
  %8 = load i32, i32* %err, align 4, !dbg !2470
  %cmp = icmp ne i32 %8, 0, !dbg !2472
  br i1 %cmp, label %if.then, label %if.end, !dbg !2473

if.then:                                          ; preds = %entry
  %9 = load i32, i32* %err, align 4, !dbg !2474
  store i32 %9, i32* %retval, align 4, !dbg !2475
  br label %return, !dbg !2475

if.end:                                           ; preds = %entry
  %10 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2476
  %11 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2477
  %12 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2478
  %13 = load i64*, i64** %unconsumed.addr, align 8, !dbg !2479
  %call4 = call i32 @tar_read_header(%struct.archive_read* %10, %struct.tar* %11, %struct.archive_entry* %12, i64* %13), !dbg !2480
  store i32 %call4, i32* %err, align 4, !dbg !2481
  %14 = load i32, i32* %err, align 4, !dbg !2482
  %cmp5 = icmp ne i32 %14, 0, !dbg !2484
  br i1 %cmp5, label %land.lhs.true, label %if.end8, !dbg !2485

land.lhs.true:                                    ; preds = %if.end
  %15 = load i32, i32* %err, align 4, !dbg !2486
  %cmp6 = icmp ne i32 %15, -20, !dbg !2488
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !2489

if.then7:                                         ; preds = %land.lhs.true
  %16 = load i32, i32* %err, align 4, !dbg !2490
  store i32 %16, i32* %retval, align 4, !dbg !2491
  br label %return, !dbg !2491

if.end8:                                          ; preds = %land.lhs.true, %if.end
  %17 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2492
  %acl_text9 = getelementptr inbounds %struct.tar, %struct.tar* %17, i32 0, i32 0, !dbg !2493
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %acl_text9, i32 0, i32 0, !dbg !2494
  %18 = load i8*, i8** %s, align 8, !dbg !2494
  store i8* %18, i8** %acl, align 8, !dbg !2495
  store i8* %18, i8** %p, align 8, !dbg !2496
  store i64 0, i64* %type, align 8, !dbg !2497
  br label %while.cond, !dbg !2498

while.cond:                                       ; preds = %if.end28, %if.end8
  %19 = load i8*, i8** %p, align 8, !dbg !2499
  %20 = load i8, i8* %19, align 1, !dbg !2501
  %conv = sext i8 %20 to i32, !dbg !2501
  %cmp10 = icmp ne i32 %conv, 0, !dbg !2502
  br i1 %cmp10, label %land.rhs, label %land.end, !dbg !2503

land.rhs:                                         ; preds = %while.cond
  %21 = load i8*, i8** %p, align 8, !dbg !2504
  %22 = load i8*, i8** %acl, align 8, !dbg !2506
  %23 = load i64, i64* %size, align 8, !dbg !2507
  %add.ptr = getelementptr inbounds i8, i8* %22, i64 %23, !dbg !2508
  %cmp12 = icmp ult i8* %21, %add.ptr, !dbg !2509
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond
  %24 = phi i1 [ false, %while.cond ], [ %cmp12, %land.rhs ]
  br i1 %24, label %while.body, label %while.end, !dbg !2510

while.body:                                       ; preds = %land.end
  %25 = load i8*, i8** %p, align 8, !dbg !2512
  %26 = load i8, i8* %25, align 1, !dbg !2515
  %conv14 = sext i8 %26 to i32, !dbg !2515
  %cmp15 = icmp slt i32 %conv14, 48, !dbg !2516
  br i1 %cmp15, label %if.then20, label %lor.lhs.false, !dbg !2517

lor.lhs.false:                                    ; preds = %while.body
  %27 = load i8*, i8** %p, align 8, !dbg !2518
  %28 = load i8, i8* %27, align 1, !dbg !2520
  %conv17 = sext i8 %28 to i32, !dbg !2520
  %cmp18 = icmp sgt i32 %conv17, 55, !dbg !2521
  br i1 %cmp18, label %if.then20, label %if.end21, !dbg !2522

if.then20:                                        ; preds = %lor.lhs.false, %while.body
  %29 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2523
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %29, i32 0, i32 0, !dbg !2525
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 -1, i8* getelementptr inbounds ([48 x i8], [48 x i8]* @.str.25, i32 0, i32 0)), !dbg !2526
  store i32 -20, i32* %retval, align 4, !dbg !2527
  br label %return, !dbg !2527

if.end21:                                         ; preds = %lor.lhs.false
  %30 = load i64, i64* %type, align 8, !dbg !2528
  %shl = shl i64 %30, 3, !dbg !2528
  store i64 %shl, i64* %type, align 8, !dbg !2528
  %31 = load i8*, i8** %p, align 8, !dbg !2529
  %32 = load i8, i8* %31, align 1, !dbg !2530
  %conv22 = sext i8 %32 to i32, !dbg !2530
  %sub = sub nsw i32 %conv22, 48, !dbg !2531
  %conv23 = sext i32 %sub to i64, !dbg !2530
  %33 = load i64, i64* %type, align 8, !dbg !2532
  %add = add nsw i64 %33, %conv23, !dbg !2532
  store i64 %add, i64* %type, align 8, !dbg !2532
  %34 = load i64, i64* %type, align 8, !dbg !2533
  %cmp24 = icmp sgt i64 %34, 16777215, !dbg !2535
  br i1 %cmp24, label %if.then26, label %if.end28, !dbg !2536

if.then26:                                        ; preds = %if.end21
  %35 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2537
  %archive27 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %35, i32 0, i32 0, !dbg !2539
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive27, i32 -1, i8* getelementptr inbounds ([50 x i8], [50 x i8]* @.str.26, i32 0, i32 0)), !dbg !2540
  store i32 -20, i32* %retval, align 4, !dbg !2541
  br label %return, !dbg !2541

if.end28:                                         ; preds = %if.end21
  %36 = load i8*, i8** %p, align 8, !dbg !2542
  %incdec.ptr = getelementptr inbounds i8, i8* %36, i32 1, !dbg !2542
  store i8* %incdec.ptr, i8** %p, align 8, !dbg !2542
  br label %while.cond, !dbg !2543

while.end:                                        ; preds = %land.end
  %37 = load i64, i64* %type, align 8, !dbg !2545
  %conv29 = trunc i64 %37 to i32, !dbg !2546
  %and = and i32 %conv29, -262144, !dbg !2547
  switch i32 %and, label %sw.default [
    i32 262144, label %sw.bb
    i32 786432, label %sw.bb30
  ], !dbg !2548

sw.bb:                                            ; preds = %while.end
  store i32 256, i32* %acl_type, align 4, !dbg !2549
  br label %sw.epilog, !dbg !2551

sw.bb30:                                          ; preds = %while.end
  store i32 15360, i32* %acl_type, align 4, !dbg !2552
  br label %sw.epilog, !dbg !2553

sw.default:                                       ; preds = %while.end
  %38 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2554
  %archive31 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %38, i32 0, i32 0, !dbg !2555
  %39 = load i64, i64* %type, align 8, !dbg !2556
  %conv32 = trunc i64 %39 to i32, !dbg !2557
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive31, i32 -1, i8* getelementptr inbounds ([54 x i8], [54 x i8]* @.str.27, i32 0, i32 0), i32 %conv32), !dbg !2558
  store i32 -20, i32* %retval, align 4, !dbg !2559
  br label %return, !dbg !2559

sw.epilog:                                        ; preds = %sw.bb30, %sw.bb
  %40 = load i8*, i8** %p, align 8, !dbg !2560
  %incdec.ptr33 = getelementptr inbounds i8, i8* %40, i32 1, !dbg !2560
  store i8* %incdec.ptr33, i8** %p, align 8, !dbg !2560
  %41 = load i8*, i8** %p, align 8, !dbg !2561
  %42 = load i8*, i8** %acl, align 8, !dbg !2563
  %43 = load i64, i64* %size, align 8, !dbg !2564
  %add.ptr34 = getelementptr inbounds i8, i8* %42, i64 %43, !dbg !2565
  %cmp35 = icmp uge i8* %41, %add.ptr34, !dbg !2566
  br i1 %cmp35, label %if.then37, label %if.end39, !dbg !2567

if.then37:                                        ; preds = %sw.epilog
  %44 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2568
  %archive38 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %44, i32 0, i32 0, !dbg !2570
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive38, i32 -1, i8* getelementptr inbounds ([48 x i8], [48 x i8]* @.str.28, i32 0, i32 0)), !dbg !2571
  store i32 -20, i32* %retval, align 4, !dbg !2572
  br label %return, !dbg !2572

if.end39:                                         ; preds = %sw.epilog
  %45 = load i8*, i8** %p, align 8, !dbg !2573
  %46 = load i8*, i8** %acl, align 8, !dbg !2574
  %sub.ptr.lhs.cast = ptrtoint i8* %45 to i64, !dbg !2575
  %sub.ptr.rhs.cast = ptrtoint i8* %46 to i64, !dbg !2575
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !2575
  %47 = load i64, i64* %size, align 8, !dbg !2576
  %sub40 = sub i64 %47, %sub.ptr.sub, !dbg !2576
  store i64 %sub40, i64* %size, align 8, !dbg !2576
  %48 = load i8*, i8** %p, align 8, !dbg !2577
  store i8* %48, i8** %acl, align 8, !dbg !2578
  br label %while.cond41, !dbg !2579

while.cond41:                                     ; preds = %while.body50, %if.end39
  %49 = load i8*, i8** %p, align 8, !dbg !2580
  %50 = load i8, i8* %49, align 1, !dbg !2581
  %conv42 = sext i8 %50 to i32, !dbg !2581
  %cmp43 = icmp ne i32 %conv42, 0, !dbg !2582
  br i1 %cmp43, label %land.rhs45, label %land.end49, !dbg !2583

land.rhs45:                                       ; preds = %while.cond41
  %51 = load i8*, i8** %p, align 8, !dbg !2584
  %52 = load i8*, i8** %acl, align 8, !dbg !2585
  %53 = load i64, i64* %size, align 8, !dbg !2586
  %add.ptr46 = getelementptr inbounds i8, i8* %52, i64 %53, !dbg !2587
  %cmp47 = icmp ult i8* %51, %add.ptr46, !dbg !2588
  br label %land.end49

land.end49:                                       ; preds = %land.rhs45, %while.cond41
  %54 = phi i1 [ false, %while.cond41 ], [ %cmp47, %land.rhs45 ]
  br i1 %54, label %while.body50, label %while.end52, !dbg !2589

while.body50:                                     ; preds = %land.end49
  %55 = load i8*, i8** %p, align 8, !dbg !2590
  %incdec.ptr51 = getelementptr inbounds i8, i8* %55, i32 1, !dbg !2590
  store i8* %incdec.ptr51, i8** %p, align 8, !dbg !2590
  br label %while.cond41, !dbg !2591

while.end52:                                      ; preds = %land.end49
  %56 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2592
  %sconv_acl = getelementptr inbounds %struct.tar, %struct.tar* %56, i32 0, i32 29, !dbg !2594
  %57 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv_acl, align 8, !dbg !2594
  %cmp53 = icmp eq %struct.archive_string_conv* %57, null, !dbg !2595
  br i1 %cmp53, label %if.then55, label %if.end64, !dbg !2596

if.then55:                                        ; preds = %while.end52
  %58 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2597
  %archive56 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %58, i32 0, i32 0, !dbg !2599
  %call57 = call %struct.archive_string_conv* @archive_string_conversion_from_charset(%struct.archive* %archive56, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.29, i32 0, i32 0), i32 1), !dbg !2600
  %59 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2601
  %sconv_acl58 = getelementptr inbounds %struct.tar, %struct.tar* %59, i32 0, i32 29, !dbg !2602
  store %struct.archive_string_conv* %call57, %struct.archive_string_conv** %sconv_acl58, align 8, !dbg !2603
  %60 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2604
  %sconv_acl59 = getelementptr inbounds %struct.tar, %struct.tar* %60, i32 0, i32 29, !dbg !2606
  %61 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv_acl59, align 8, !dbg !2606
  %cmp60 = icmp eq %struct.archive_string_conv* %61, null, !dbg !2607
  br i1 %cmp60, label %if.then62, label %if.end63, !dbg !2608

if.then62:                                        ; preds = %if.then55
  store i32 -30, i32* %retval, align 4, !dbg !2609
  br label %return, !dbg !2609

if.end63:                                         ; preds = %if.then55
  br label %if.end64, !dbg !2610

if.end64:                                         ; preds = %if.end63, %while.end52
  %62 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2611
  %localname = getelementptr inbounds %struct.tar, %struct.tar* %62, i32 0, i32 26, !dbg !2611
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %localname, i32 0, i32 1, !dbg !2611
  store i64 0, i64* %length, align 8, !dbg !2611
  %63 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2611
  %localname65 = getelementptr inbounds %struct.tar, %struct.tar* %63, i32 0, i32 26, !dbg !2611
  %64 = load i8*, i8** %acl, align 8, !dbg !2611
  %65 = load i8*, i8** %p, align 8, !dbg !2611
  %66 = load i8*, i8** %acl, align 8, !dbg !2611
  %sub.ptr.lhs.cast66 = ptrtoint i8* %65 to i64, !dbg !2611
  %sub.ptr.rhs.cast67 = ptrtoint i8* %66 to i64, !dbg !2611
  %sub.ptr.sub68 = sub i64 %sub.ptr.lhs.cast66, %sub.ptr.rhs.cast67, !dbg !2611
  %call69 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %localname65, i8* %64, i64 %sub.ptr.sub68), !dbg !2611
  %67 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2612
  %call70 = call %struct.archive_acl* @archive_entry_acl(%struct.archive_entry* %67), !dbg !2613
  %68 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2614
  %localname71 = getelementptr inbounds %struct.tar, %struct.tar* %68, i32 0, i32 26, !dbg !2615
  %s72 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %localname71, i32 0, i32 0, !dbg !2616
  %69 = load i8*, i8** %s72, align 8, !dbg !2616
  %70 = load i32, i32* %acl_type, align 4, !dbg !2617
  %71 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2618
  %sconv_acl73 = getelementptr inbounds %struct.tar, %struct.tar* %71, i32 0, i32 29, !dbg !2619
  %72 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv_acl73, align 8, !dbg !2619
  %call74 = call i32 @archive_acl_from_text_l(%struct.archive_acl* %call70, i8* %69, i32 %70, %struct.archive_string_conv* %72), !dbg !2620
  store i32 %call74, i32* %err, align 4, !dbg !2621
  %73 = load i32, i32* %err, align 4, !dbg !2622
  %cmp75 = icmp ne i32 %73, 0, !dbg !2624
  br i1 %cmp75, label %if.then77, label %if.end85, !dbg !2625

if.then77:                                        ; preds = %if.end64
  %call78 = call i32* @__errno_location() #1, !dbg !2626
  %74 = load i32, i32* %call78, align 4, !dbg !2626
  %cmp79 = icmp eq i32 %74, 12, !dbg !2629
  br i1 %cmp79, label %if.then81, label %if.else, !dbg !2630

if.then81:                                        ; preds = %if.then77
  %75 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2631
  %archive82 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %75, i32 0, i32 0, !dbg !2633
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive82, i32 12, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.30, i32 0, i32 0)), !dbg !2634
  br label %if.end84, !dbg !2635

if.else:                                          ; preds = %if.then77
  %76 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2636
  %archive83 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %76, i32 0, i32 0, !dbg !2637
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive83, i32 -1, i8* getelementptr inbounds ([45 x i8], [45 x i8]* @.str.31, i32 0, i32 0)), !dbg !2638
  br label %if.end84

if.end84:                                         ; preds = %if.else, %if.then81
  br label %if.end85, !dbg !2639

if.end85:                                         ; preds = %if.end84, %if.end64
  %77 = load i32, i32* %err, align 4, !dbg !2640
  store i32 %77, i32* %retval, align 4, !dbg !2641
  br label %return, !dbg !2641

return:                                           ; preds = %if.end85, %if.then62, %if.then37, %sw.default, %if.then26, %if.then20, %if.then7, %if.then
  %78 = load i32, i32* %retval, align 4, !dbg !2642
  ret i32 %78, !dbg !2642
}

; Function Attrs: nounwind uwtable
define internal i32 @header_pax_global(%struct.archive_read* %a, %struct.tar* %tar, %struct.archive_entry* %entry1, i8* %h, i64* %unconsumed) #0 !dbg !475 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %tar.addr = alloca %struct.tar*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %h.addr = alloca i8*, align 8
  %unconsumed.addr = alloca i64*, align 8
  %err = alloca i32, align 4
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !2643, metadata !563), !dbg !2644
  store %struct.tar* %tar, %struct.tar** %tar.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tar** %tar.addr, metadata !2645, metadata !563), !dbg !2646
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2647, metadata !563), !dbg !2648
  store i8* %h, i8** %h.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %h.addr, metadata !2649, metadata !563), !dbg !2650
  store i64* %unconsumed, i64** %unconsumed.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %unconsumed.addr, metadata !2651, metadata !563), !dbg !2652
  call void @llvm.dbg.declare(metadata i32* %err, metadata !2653, metadata !563), !dbg !2654
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2655
  %1 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2656
  %2 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2657
  %pax_global = getelementptr inbounds %struct.tar, %struct.tar* %2, i32 0, i32 9, !dbg !2658
  %3 = load i8*, i8** %h.addr, align 8, !dbg !2659
  %4 = load i64*, i64** %unconsumed.addr, align 8, !dbg !2660
  %call = call i32 @read_body_to_string(%struct.archive_read* %0, %struct.tar* %1, %struct.archive_string* %pax_global, i8* %3, i64* %4), !dbg !2661
  store i32 %call, i32* %err, align 4, !dbg !2662
  %5 = load i32, i32* %err, align 4, !dbg !2663
  %cmp = icmp ne i32 %5, 0, !dbg !2665
  br i1 %cmp, label %if.then, label %if.end, !dbg !2666

if.then:                                          ; preds = %entry
  %6 = load i32, i32* %err, align 4, !dbg !2667
  store i32 %6, i32* %retval, align 4, !dbg !2668
  br label %return, !dbg !2668

if.end:                                           ; preds = %entry
  %7 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2669
  %8 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2670
  %9 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2671
  %10 = load i64*, i64** %unconsumed.addr, align 8, !dbg !2672
  %call2 = call i32 @tar_read_header(%struct.archive_read* %7, %struct.tar* %8, %struct.archive_entry* %9, i64* %10), !dbg !2673
  store i32 %call2, i32* %err, align 4, !dbg !2674
  %11 = load i32, i32* %err, align 4, !dbg !2675
  store i32 %11, i32* %retval, align 4, !dbg !2676
  br label %return, !dbg !2676

return:                                           ; preds = %if.end, %if.then
  %12 = load i32, i32* %retval, align 4, !dbg !2677
  ret i32 %12, !dbg !2677
}

; Function Attrs: nounwind uwtable
define internal i32 @header_longlink(%struct.archive_read* %a, %struct.tar* %tar, %struct.archive_entry* %entry1, i8* %h, i64* %unconsumed) #0 !dbg !476 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %tar.addr = alloca %struct.tar*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %h.addr = alloca i8*, align 8
  %unconsumed.addr = alloca i64*, align 8
  %err = alloca i32, align 4
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !2678, metadata !563), !dbg !2679
  store %struct.tar* %tar, %struct.tar** %tar.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tar** %tar.addr, metadata !2680, metadata !563), !dbg !2681
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2682, metadata !563), !dbg !2683
  store i8* %h, i8** %h.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %h.addr, metadata !2684, metadata !563), !dbg !2685
  store i64* %unconsumed, i64** %unconsumed.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %unconsumed.addr, metadata !2686, metadata !563), !dbg !2687
  call void @llvm.dbg.declare(metadata i32* %err, metadata !2688, metadata !563), !dbg !2689
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2690
  %1 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2691
  %2 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2692
  %longlink = getelementptr inbounds %struct.tar, %struct.tar* %2, i32 0, i32 6, !dbg !2693
  %3 = load i8*, i8** %h.addr, align 8, !dbg !2694
  %4 = load i64*, i64** %unconsumed.addr, align 8, !dbg !2695
  %call = call i32 @read_body_to_string(%struct.archive_read* %0, %struct.tar* %1, %struct.archive_string* %longlink, i8* %3, i64* %4), !dbg !2696
  store i32 %call, i32* %err, align 4, !dbg !2697
  %5 = load i32, i32* %err, align 4, !dbg !2698
  %cmp = icmp ne i32 %5, 0, !dbg !2700
  br i1 %cmp, label %if.then, label %if.end, !dbg !2701

if.then:                                          ; preds = %entry
  %6 = load i32, i32* %err, align 4, !dbg !2702
  store i32 %6, i32* %retval, align 4, !dbg !2703
  br label %return, !dbg !2703

if.end:                                           ; preds = %entry
  %7 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2704
  %8 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2705
  %9 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2706
  %10 = load i64*, i64** %unconsumed.addr, align 8, !dbg !2707
  %call2 = call i32 @tar_read_header(%struct.archive_read* %7, %struct.tar* %8, %struct.archive_entry* %9, i64* %10), !dbg !2708
  store i32 %call2, i32* %err, align 4, !dbg !2709
  %11 = load i32, i32* %err, align 4, !dbg !2710
  %cmp3 = icmp ne i32 %11, 0, !dbg !2712
  br i1 %cmp3, label %land.lhs.true, label %if.end6, !dbg !2713

land.lhs.true:                                    ; preds = %if.end
  %12 = load i32, i32* %err, align 4, !dbg !2714
  %cmp4 = icmp ne i32 %12, -20, !dbg !2716
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !2717

if.then5:                                         ; preds = %land.lhs.true
  %13 = load i32, i32* %err, align 4, !dbg !2718
  store i32 %13, i32* %retval, align 4, !dbg !2719
  br label %return, !dbg !2719

if.end6:                                          ; preds = %land.lhs.true, %if.end
  %14 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2720
  %15 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2721
  %longlink7 = getelementptr inbounds %struct.tar, %struct.tar* %15, i32 0, i32 6, !dbg !2722
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %longlink7, i32 0, i32 0, !dbg !2723
  %16 = load i8*, i8** %s, align 8, !dbg !2723
  call void @archive_entry_copy_link(%struct.archive_entry* %14, i8* %16), !dbg !2724
  store i32 0, i32* %retval, align 4, !dbg !2725
  br label %return, !dbg !2725

return:                                           ; preds = %if.end6, %if.then5, %if.then
  %17 = load i32, i32* %retval, align 4, !dbg !2726
  ret i32 %17, !dbg !2726
}

; Function Attrs: nounwind uwtable
define internal i32 @header_longname(%struct.archive_read* %a, %struct.tar* %tar, %struct.archive_entry* %entry1, i8* %h, i64* %unconsumed) #0 !dbg !477 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %tar.addr = alloca %struct.tar*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %h.addr = alloca i8*, align 8
  %unconsumed.addr = alloca i64*, align 8
  %err = alloca i32, align 4
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !2727, metadata !563), !dbg !2728
  store %struct.tar* %tar, %struct.tar** %tar.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tar** %tar.addr, metadata !2729, metadata !563), !dbg !2730
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2731, metadata !563), !dbg !2732
  store i8* %h, i8** %h.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %h.addr, metadata !2733, metadata !563), !dbg !2734
  store i64* %unconsumed, i64** %unconsumed.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %unconsumed.addr, metadata !2735, metadata !563), !dbg !2736
  call void @llvm.dbg.declare(metadata i32* %err, metadata !2737, metadata !563), !dbg !2738
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2739
  %1 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2740
  %2 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2741
  %longname = getelementptr inbounds %struct.tar, %struct.tar* %2, i32 0, i32 7, !dbg !2742
  %3 = load i8*, i8** %h.addr, align 8, !dbg !2743
  %4 = load i64*, i64** %unconsumed.addr, align 8, !dbg !2744
  %call = call i32 @read_body_to_string(%struct.archive_read* %0, %struct.tar* %1, %struct.archive_string* %longname, i8* %3, i64* %4), !dbg !2745
  store i32 %call, i32* %err, align 4, !dbg !2746
  %5 = load i32, i32* %err, align 4, !dbg !2747
  %cmp = icmp ne i32 %5, 0, !dbg !2749
  br i1 %cmp, label %if.then, label %if.end, !dbg !2750

if.then:                                          ; preds = %entry
  %6 = load i32, i32* %err, align 4, !dbg !2751
  store i32 %6, i32* %retval, align 4, !dbg !2752
  br label %return, !dbg !2752

if.end:                                           ; preds = %entry
  %7 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2753
  %8 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2754
  %9 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2755
  %10 = load i64*, i64** %unconsumed.addr, align 8, !dbg !2756
  %call2 = call i32 @tar_read_header(%struct.archive_read* %7, %struct.tar* %8, %struct.archive_entry* %9, i64* %10), !dbg !2757
  store i32 %call2, i32* %err, align 4, !dbg !2758
  %11 = load i32, i32* %err, align 4, !dbg !2759
  %cmp3 = icmp ne i32 %11, 0, !dbg !2761
  br i1 %cmp3, label %land.lhs.true, label %if.end6, !dbg !2762

land.lhs.true:                                    ; preds = %if.end
  %12 = load i32, i32* %err, align 4, !dbg !2763
  %cmp4 = icmp ne i32 %12, -20, !dbg !2765
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !2766

if.then5:                                         ; preds = %land.lhs.true
  %13 = load i32, i32* %err, align 4, !dbg !2767
  store i32 %13, i32* %retval, align 4, !dbg !2768
  br label %return, !dbg !2768

if.end6:                                          ; preds = %land.lhs.true, %if.end
  %14 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2769
  %15 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2771
  %longname7 = getelementptr inbounds %struct.tar, %struct.tar* %15, i32 0, i32 7, !dbg !2772
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %longname7, i32 0, i32 0, !dbg !2773
  %16 = load i8*, i8** %s, align 8, !dbg !2773
  %17 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2774
  %longname8 = getelementptr inbounds %struct.tar, %struct.tar* %17, i32 0, i32 7, !dbg !2774
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %longname8, i32 0, i32 1, !dbg !2774
  %18 = load i64, i64* %length, align 8, !dbg !2774
  %19 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2775
  %sconv = getelementptr inbounds %struct.tar, %struct.tar* %19, i32 0, i32 28, !dbg !2776
  %20 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !2776
  %call9 = call i32 @_archive_entry_copy_pathname_l(%struct.archive_entry* %14, i8* %16, i64 %18, %struct.archive_string_conv* %20), !dbg !2777
  %cmp10 = icmp ne i32 %call9, 0, !dbg !2778
  br i1 %cmp10, label %if.then11, label %if.end14, !dbg !2779

if.then11:                                        ; preds = %if.end6
  %21 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2780
  %22 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2781
  %sconv12 = getelementptr inbounds %struct.tar, %struct.tar* %22, i32 0, i32 28, !dbg !2782
  %23 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv12, align 8, !dbg !2782
  %call13 = call i32 @set_conversion_failed_error(%struct.archive_read* %21, %struct.archive_string_conv* %23, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.34, i32 0, i32 0)), !dbg !2783
  store i32 %call13, i32* %err, align 4, !dbg !2784
  br label %if.end14, !dbg !2785

if.end14:                                         ; preds = %if.then11, %if.end6
  %24 = load i32, i32* %err, align 4, !dbg !2786
  store i32 %24, i32* %retval, align 4, !dbg !2787
  br label %return, !dbg !2787

return:                                           ; preds = %if.end14, %if.then5, %if.then
  %25 = load i32, i32* %retval, align 4, !dbg !2788
  ret i32 %25, !dbg !2788
}

; Function Attrs: nounwind uwtable
define internal i32 @header_volume(%struct.archive_read* %a, %struct.tar* %tar, %struct.archive_entry* %entry1, i8* %h, i64* %unconsumed) #0 !dbg !481 {
entry:
  %a.addr = alloca %struct.archive_read*, align 8
  %tar.addr = alloca %struct.tar*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %h.addr = alloca i8*, align 8
  %unconsumed.addr = alloca i64*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !2789, metadata !563), !dbg !2790
  store %struct.tar* %tar, %struct.tar** %tar.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tar** %tar.addr, metadata !2791, metadata !563), !dbg !2792
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2793, metadata !563), !dbg !2794
  store i8* %h, i8** %h.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %h.addr, metadata !2795, metadata !563), !dbg !2796
  store i64* %unconsumed, i64** %unconsumed.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %unconsumed.addr, metadata !2797, metadata !563), !dbg !2798
  %0 = load i8*, i8** %h.addr, align 8, !dbg !2799
  %1 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2800
  %2 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2801
  %3 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2802
  %4 = load i64*, i64** %unconsumed.addr, align 8, !dbg !2803
  %call = call i32 @tar_read_header(%struct.archive_read* %1, %struct.tar* %2, %struct.archive_entry* %3, i64* %4), !dbg !2804
  ret i32 %call, !dbg !2805
}

; Function Attrs: nounwind uwtable
define internal i32 @header_pax_extensions(%struct.archive_read* %a, %struct.tar* %tar, %struct.archive_entry* %entry1, i8* %h, i64* %unconsumed) #0 !dbg !482 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %tar.addr = alloca %struct.tar*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %h.addr = alloca i8*, align 8
  %unconsumed.addr = alloca i64*, align 8
  %err = alloca i32, align 4
  %err2 = alloca i32, align 4
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !2806, metadata !563), !dbg !2807
  store %struct.tar* %tar, %struct.tar** %tar.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tar** %tar.addr, metadata !2808, metadata !563), !dbg !2809
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2810, metadata !563), !dbg !2811
  store i8* %h, i8** %h.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %h.addr, metadata !2812, metadata !563), !dbg !2813
  store i64* %unconsumed, i64** %unconsumed.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %unconsumed.addr, metadata !2814, metadata !563), !dbg !2815
  call void @llvm.dbg.declare(metadata i32* %err, metadata !2816, metadata !563), !dbg !2817
  call void @llvm.dbg.declare(metadata i32* %err2, metadata !2818, metadata !563), !dbg !2819
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2820
  %1 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2821
  %2 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2822
  %pax_header = getelementptr inbounds %struct.tar, %struct.tar* %2, i32 0, i32 8, !dbg !2823
  %3 = load i8*, i8** %h.addr, align 8, !dbg !2824
  %4 = load i64*, i64** %unconsumed.addr, align 8, !dbg !2825
  %call = call i32 @read_body_to_string(%struct.archive_read* %0, %struct.tar* %1, %struct.archive_string* %pax_header, i8* %3, i64* %4), !dbg !2826
  store i32 %call, i32* %err, align 4, !dbg !2827
  %5 = load i32, i32* %err, align 4, !dbg !2828
  %cmp = icmp ne i32 %5, 0, !dbg !2830
  br i1 %cmp, label %if.then, label %if.end, !dbg !2831

if.then:                                          ; preds = %entry
  %6 = load i32, i32* %err, align 4, !dbg !2832
  store i32 %6, i32* %retval, align 4, !dbg !2833
  br label %return, !dbg !2833

if.end:                                           ; preds = %entry
  %7 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2834
  %8 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2835
  %9 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2836
  %10 = load i64*, i64** %unconsumed.addr, align 8, !dbg !2837
  %call2 = call i32 @tar_read_header(%struct.archive_read* %7, %struct.tar* %8, %struct.archive_entry* %9, i64* %10), !dbg !2838
  store i32 %call2, i32* %err, align 4, !dbg !2839
  %11 = load i32, i32* %err, align 4, !dbg !2840
  %cmp3 = icmp ne i32 %11, 0, !dbg !2842
  br i1 %cmp3, label %land.lhs.true, label %if.end6, !dbg !2843

land.lhs.true:                                    ; preds = %if.end
  %12 = load i32, i32* %err, align 4, !dbg !2844
  %cmp4 = icmp ne i32 %12, -20, !dbg !2846
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !2847

if.then5:                                         ; preds = %land.lhs.true
  %13 = load i32, i32* %err, align 4, !dbg !2848
  store i32 %13, i32* %retval, align 4, !dbg !2849
  br label %return, !dbg !2849

if.end6:                                          ; preds = %land.lhs.true, %if.end
  %14 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2850
  %15 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2851
  %16 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2852
  %17 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2853
  %pax_header7 = getelementptr inbounds %struct.tar, %struct.tar* %17, i32 0, i32 8, !dbg !2854
  %call8 = call i32 @pax_header(%struct.archive_read* %14, %struct.tar* %15, %struct.archive_entry* %16, %struct.archive_string* %pax_header7), !dbg !2855
  store i32 %call8, i32* %err2, align 4, !dbg !2856
  %18 = load i32, i32* %err, align 4, !dbg !2857
  %19 = load i32, i32* %err2, align 4, !dbg !2857
  %cmp9 = icmp slt i32 %18, %19, !dbg !2857
  br i1 %cmp9, label %cond.true, label %cond.false, !dbg !2857

cond.true:                                        ; preds = %if.end6
  %20 = load i32, i32* %err, align 4, !dbg !2858
  br label %cond.end, !dbg !2858

cond.false:                                       ; preds = %if.end6
  %21 = load i32, i32* %err2, align 4, !dbg !2860
  br label %cond.end, !dbg !2860

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ %20, %cond.true ], [ %21, %cond.false ], !dbg !2862
  store i32 %cond, i32* %err, align 4, !dbg !2864
  %22 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2865
  %entry_bytes_remaining = getelementptr inbounds %struct.tar, %struct.tar* %22, i32 0, i32 13, !dbg !2866
  %23 = load i64, i64* %entry_bytes_remaining, align 8, !dbg !2866
  %sub = sub nsw i64 0, %23, !dbg !2867
  %and = and i64 511, %sub, !dbg !2868
  %24 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2869
  %entry_padding = getelementptr inbounds %struct.tar, %struct.tar* %24, i32 0, i32 15, !dbg !2870
  store i64 %and, i64* %entry_padding, align 8, !dbg !2871
  %25 = load i32, i32* %err, align 4, !dbg !2872
  store i32 %25, i32* %retval, align 4, !dbg !2873
  br label %return, !dbg !2873

return:                                           ; preds = %cond.end, %if.then5, %if.then
  %26 = load i32, i32* %retval, align 4, !dbg !2874
  ret i32 %26, !dbg !2874
}

; Function Attrs: nounwind uwtable
define internal i32 @header_gnutar(%struct.archive_read* %a, %struct.tar* %tar, %struct.archive_entry* %entry1, i8* %h, i64* %unconsumed) #0 !dbg !518 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %tar.addr = alloca %struct.tar*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %h.addr = alloca i8*, align 8
  %unconsumed.addr = alloca i64*, align 8
  %header = alloca %struct.archive_entry_header_gnutar*, align 8
  %t = alloca i64, align 8
  %err = alloca i32, align 4
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !2875, metadata !563), !dbg !2876
  store %struct.tar* %tar, %struct.tar** %tar.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tar** %tar.addr, metadata !2877, metadata !563), !dbg !2878
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2879, metadata !563), !dbg !2880
  store i8* %h, i8** %h.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %h.addr, metadata !2881, metadata !563), !dbg !2882
  store i64* %unconsumed, i64** %unconsumed.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %unconsumed.addr, metadata !2883, metadata !563), !dbg !2884
  call void @llvm.dbg.declare(metadata %struct.archive_entry_header_gnutar** %header, metadata !2885, metadata !563), !dbg !2886
  call void @llvm.dbg.declare(metadata i64* %t, metadata !2887, metadata !563), !dbg !2888
  call void @llvm.dbg.declare(metadata i32* %err, metadata !2889, metadata !563), !dbg !2890
  store i32 0, i32* %err, align 4, !dbg !2890
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2891
  %1 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2892
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2893
  %3 = load i8*, i8** %h.addr, align 8, !dbg !2894
  %call = call i32 @header_common(%struct.archive_read* %0, %struct.tar* %1, %struct.archive_entry* %2, i8* %3), !dbg !2895
  store i32 %call, i32* %err, align 4, !dbg !2896
  %4 = load i32, i32* %err, align 4, !dbg !2897
  %cmp = icmp eq i32 %4, -30, !dbg !2899
  br i1 %cmp, label %if.then, label %if.end, !dbg !2900

if.then:                                          ; preds = %entry
  %5 = load i32, i32* %err, align 4, !dbg !2901
  store i32 %5, i32* %retval, align 4, !dbg !2902
  br label %return, !dbg !2902

if.end:                                           ; preds = %entry
  %6 = load i8*, i8** %h.addr, align 8, !dbg !2903
  %7 = bitcast i8* %6 to %struct.archive_entry_header_gnutar*, !dbg !2904
  store %struct.archive_entry_header_gnutar* %7, %struct.archive_entry_header_gnutar** %header, align 8, !dbg !2905
  %8 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2906
  %9 = load %struct.archive_entry_header_gnutar*, %struct.archive_entry_header_gnutar** %header, align 8, !dbg !2908
  %name = getelementptr inbounds %struct.archive_entry_header_gnutar, %struct.archive_entry_header_gnutar* %9, i32 0, i32 0, !dbg !2909
  %arraydecay = getelementptr inbounds [100 x i8], [100 x i8]* %name, i32 0, i32 0, !dbg !2908
  %10 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2910
  %sconv = getelementptr inbounds %struct.tar, %struct.tar* %10, i32 0, i32 28, !dbg !2911
  %11 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !2911
  %call2 = call i32 @_archive_entry_copy_pathname_l(%struct.archive_entry* %8, i8* %arraydecay, i64 100, %struct.archive_string_conv* %11), !dbg !2912
  %cmp3 = icmp ne i32 %call2, 0, !dbg !2913
  br i1 %cmp3, label %if.then4, label %if.end10, !dbg !2914

if.then4:                                         ; preds = %if.end
  %12 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2915
  %13 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2917
  %sconv5 = getelementptr inbounds %struct.tar, %struct.tar* %13, i32 0, i32 28, !dbg !2918
  %14 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv5, align 8, !dbg !2918
  %call6 = call i32 @set_conversion_failed_error(%struct.archive_read* %12, %struct.archive_string_conv* %14, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.34, i32 0, i32 0)), !dbg !2919
  store i32 %call6, i32* %err, align 4, !dbg !2920
  %15 = load i32, i32* %err, align 4, !dbg !2921
  %cmp7 = icmp eq i32 %15, -30, !dbg !2923
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !2924

if.then8:                                         ; preds = %if.then4
  %16 = load i32, i32* %err, align 4, !dbg !2925
  store i32 %16, i32* %retval, align 4, !dbg !2926
  br label %return, !dbg !2926

if.end9:                                          ; preds = %if.then4
  br label %if.end10, !dbg !2927

if.end10:                                         ; preds = %if.end9, %if.end
  %17 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2928
  %18 = load %struct.archive_entry_header_gnutar*, %struct.archive_entry_header_gnutar** %header, align 8, !dbg !2930
  %uname = getelementptr inbounds %struct.archive_entry_header_gnutar, %struct.archive_entry_header_gnutar* %18, i32 0, i32 10, !dbg !2931
  %arraydecay11 = getelementptr inbounds [32 x i8], [32 x i8]* %uname, i32 0, i32 0, !dbg !2930
  %19 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2932
  %sconv12 = getelementptr inbounds %struct.tar, %struct.tar* %19, i32 0, i32 28, !dbg !2933
  %20 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv12, align 8, !dbg !2933
  %call13 = call i32 @_archive_entry_copy_uname_l(%struct.archive_entry* %17, i8* %arraydecay11, i64 32, %struct.archive_string_conv* %20), !dbg !2934
  %cmp14 = icmp ne i32 %call13, 0, !dbg !2935
  br i1 %cmp14, label %if.then15, label %if.end21, !dbg !2936

if.then15:                                        ; preds = %if.end10
  %21 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2937
  %22 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2939
  %sconv16 = getelementptr inbounds %struct.tar, %struct.tar* %22, i32 0, i32 28, !dbg !2940
  %23 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv16, align 8, !dbg !2940
  %call17 = call i32 @set_conversion_failed_error(%struct.archive_read* %21, %struct.archive_string_conv* %23, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.43, i32 0, i32 0)), !dbg !2941
  store i32 %call17, i32* %err, align 4, !dbg !2942
  %24 = load i32, i32* %err, align 4, !dbg !2943
  %cmp18 = icmp eq i32 %24, -30, !dbg !2945
  br i1 %cmp18, label %if.then19, label %if.end20, !dbg !2946

if.then19:                                        ; preds = %if.then15
  %25 = load i32, i32* %err, align 4, !dbg !2947
  store i32 %25, i32* %retval, align 4, !dbg !2948
  br label %return, !dbg !2948

if.end20:                                         ; preds = %if.then15
  br label %if.end21, !dbg !2949

if.end21:                                         ; preds = %if.end20, %if.end10
  %26 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2950
  %27 = load %struct.archive_entry_header_gnutar*, %struct.archive_entry_header_gnutar** %header, align 8, !dbg !2952
  %gname = getelementptr inbounds %struct.archive_entry_header_gnutar, %struct.archive_entry_header_gnutar* %27, i32 0, i32 11, !dbg !2953
  %arraydecay22 = getelementptr inbounds [32 x i8], [32 x i8]* %gname, i32 0, i32 0, !dbg !2952
  %28 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2954
  %sconv23 = getelementptr inbounds %struct.tar, %struct.tar* %28, i32 0, i32 28, !dbg !2955
  %29 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv23, align 8, !dbg !2955
  %call24 = call i32 @_archive_entry_copy_gname_l(%struct.archive_entry* %26, i8* %arraydecay22, i64 32, %struct.archive_string_conv* %29), !dbg !2956
  %cmp25 = icmp ne i32 %call24, 0, !dbg !2957
  br i1 %cmp25, label %if.then26, label %if.end32, !dbg !2958

if.then26:                                        ; preds = %if.end21
  %30 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2959
  %31 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2961
  %sconv27 = getelementptr inbounds %struct.tar, %struct.tar* %31, i32 0, i32 28, !dbg !2962
  %32 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv27, align 8, !dbg !2962
  %call28 = call i32 @set_conversion_failed_error(%struct.archive_read* %30, %struct.archive_string_conv* %32, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.41, i32 0, i32 0)), !dbg !2963
  store i32 %call28, i32* %err, align 4, !dbg !2964
  %33 = load i32, i32* %err, align 4, !dbg !2965
  %cmp29 = icmp eq i32 %33, -30, !dbg !2967
  br i1 %cmp29, label %if.then30, label %if.end31, !dbg !2968

if.then30:                                        ; preds = %if.then26
  %34 = load i32, i32* %err, align 4, !dbg !2969
  store i32 %34, i32* %retval, align 4, !dbg !2970
  br label %return, !dbg !2970

if.end31:                                         ; preds = %if.then26
  br label %if.end32, !dbg !2971

if.end32:                                         ; preds = %if.end31, %if.end21
  %35 = load %struct.archive_entry_header_gnutar*, %struct.archive_entry_header_gnutar** %header, align 8, !dbg !2972
  %typeflag = getelementptr inbounds %struct.archive_entry_header_gnutar, %struct.archive_entry_header_gnutar* %35, i32 0, i32 7, !dbg !2974
  %arrayidx = getelementptr inbounds [1 x i8], [1 x i8]* %typeflag, i64 0, i64 0, !dbg !2972
  %36 = load i8, i8* %arrayidx, align 1, !dbg !2972
  %conv = sext i8 %36 to i32, !dbg !2972
  %cmp33 = icmp eq i32 %conv, 51, !dbg !2975
  br i1 %cmp33, label %if.then40, label %lor.lhs.false, !dbg !2976

lor.lhs.false:                                    ; preds = %if.end32
  %37 = load %struct.archive_entry_header_gnutar*, %struct.archive_entry_header_gnutar** %header, align 8, !dbg !2977
  %typeflag35 = getelementptr inbounds %struct.archive_entry_header_gnutar, %struct.archive_entry_header_gnutar* %37, i32 0, i32 7, !dbg !2979
  %arrayidx36 = getelementptr inbounds [1 x i8], [1 x i8]* %typeflag35, i64 0, i64 0, !dbg !2977
  %38 = load i8, i8* %arrayidx36, align 1, !dbg !2977
  %conv37 = sext i8 %38 to i32, !dbg !2977
  %cmp38 = icmp eq i32 %conv37, 52, !dbg !2980
  br i1 %cmp38, label %if.then40, label %if.else, !dbg !2981

if.then40:                                        ; preds = %lor.lhs.false, %if.end32
  %39 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2982
  %40 = load %struct.archive_entry_header_gnutar*, %struct.archive_entry_header_gnutar** %header, align 8, !dbg !2984
  %rdevmajor = getelementptr inbounds %struct.archive_entry_header_gnutar, %struct.archive_entry_header_gnutar* %40, i32 0, i32 12, !dbg !2985
  %arraydecay41 = getelementptr inbounds [8 x i8], [8 x i8]* %rdevmajor, i32 0, i32 0, !dbg !2984
  %call42 = call i64 @tar_atol(i8* %arraydecay41, i64 8), !dbg !2986
  call void @archive_entry_set_rdevmajor(%struct.archive_entry* %39, i64 %call42), !dbg !2987
  %41 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2988
  %42 = load %struct.archive_entry_header_gnutar*, %struct.archive_entry_header_gnutar** %header, align 8, !dbg !2989
  %rdevminor = getelementptr inbounds %struct.archive_entry_header_gnutar, %struct.archive_entry_header_gnutar* %42, i32 0, i32 13, !dbg !2990
  %arraydecay43 = getelementptr inbounds [8 x i8], [8 x i8]* %rdevminor, i32 0, i32 0, !dbg !2989
  %call44 = call i64 @tar_atol(i8* %arraydecay43, i64 8), !dbg !2991
  call void @archive_entry_set_rdevminor(%struct.archive_entry* %41, i64 %call44), !dbg !2992
  br label %if.end45, !dbg !2993

if.else:                                          ; preds = %lor.lhs.false
  %43 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2994
  call void @archive_entry_set_rdev(%struct.archive_entry* %43, i64 0), !dbg !2995
  br label %if.end45

if.end45:                                         ; preds = %if.else, %if.then40
  %44 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !2996
  %entry_bytes_remaining = getelementptr inbounds %struct.tar, %struct.tar* %44, i32 0, i32 13, !dbg !2997
  %45 = load i64, i64* %entry_bytes_remaining, align 8, !dbg !2997
  %sub = sub nsw i64 0, %45, !dbg !2998
  %and = and i64 511, %sub, !dbg !2999
  %46 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3000
  %entry_padding = getelementptr inbounds %struct.tar, %struct.tar* %46, i32 0, i32 15, !dbg !3001
  store i64 %and, i64* %entry_padding, align 8, !dbg !3002
  %47 = load %struct.archive_entry_header_gnutar*, %struct.archive_entry_header_gnutar** %header, align 8, !dbg !3003
  %atime = getelementptr inbounds %struct.archive_entry_header_gnutar, %struct.archive_entry_header_gnutar* %47, i32 0, i32 14, !dbg !3004
  %arraydecay46 = getelementptr inbounds [12 x i8], [12 x i8]* %atime, i32 0, i32 0, !dbg !3003
  %call47 = call i64 @tar_atol(i8* %arraydecay46, i64 12), !dbg !3005
  store i64 %call47, i64* %t, align 8, !dbg !3006
  %48 = load i64, i64* %t, align 8, !dbg !3007
  %cmp48 = icmp sgt i64 %48, 0, !dbg !3009
  br i1 %cmp48, label %if.then50, label %if.end51, !dbg !3010

if.then50:                                        ; preds = %if.end45
  %49 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3011
  %50 = load i64, i64* %t, align 8, !dbg !3012
  call void @archive_entry_set_atime(%struct.archive_entry* %49, i64 %50, i64 0), !dbg !3013
  br label %if.end51, !dbg !3013

if.end51:                                         ; preds = %if.then50, %if.end45
  %51 = load %struct.archive_entry_header_gnutar*, %struct.archive_entry_header_gnutar** %header, align 8, !dbg !3014
  %ctime = getelementptr inbounds %struct.archive_entry_header_gnutar, %struct.archive_entry_header_gnutar* %51, i32 0, i32 15, !dbg !3015
  %arraydecay52 = getelementptr inbounds [12 x i8], [12 x i8]* %ctime, i32 0, i32 0, !dbg !3014
  %call53 = call i64 @tar_atol(i8* %arraydecay52, i64 12), !dbg !3016
  store i64 %call53, i64* %t, align 8, !dbg !3017
  %52 = load i64, i64* %t, align 8, !dbg !3018
  %cmp54 = icmp sgt i64 %52, 0, !dbg !3020
  br i1 %cmp54, label %if.then56, label %if.end57, !dbg !3021

if.then56:                                        ; preds = %if.end51
  %53 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3022
  %54 = load i64, i64* %t, align 8, !dbg !3023
  call void @archive_entry_set_ctime(%struct.archive_entry* %53, i64 %54, i64 0), !dbg !3024
  br label %if.end57, !dbg !3024

if.end57:                                         ; preds = %if.then56, %if.end51
  %55 = load %struct.archive_entry_header_gnutar*, %struct.archive_entry_header_gnutar** %header, align 8, !dbg !3025
  %realsize = getelementptr inbounds %struct.archive_entry_header_gnutar, %struct.archive_entry_header_gnutar* %55, i32 0, i32 21, !dbg !3027
  %arrayidx58 = getelementptr inbounds [12 x i8], [12 x i8]* %realsize, i64 0, i64 0, !dbg !3025
  %56 = load i8, i8* %arrayidx58, align 1, !dbg !3025
  %conv59 = sext i8 %56 to i32, !dbg !3025
  %cmp60 = icmp ne i32 %conv59, 0, !dbg !3028
  br i1 %cmp60, label %if.then62, label %if.end68, !dbg !3029

if.then62:                                        ; preds = %if.end57
  %57 = load %struct.archive_entry_header_gnutar*, %struct.archive_entry_header_gnutar** %header, align 8, !dbg !3030
  %realsize63 = getelementptr inbounds %struct.archive_entry_header_gnutar, %struct.archive_entry_header_gnutar* %57, i32 0, i32 21, !dbg !3032
  %arraydecay64 = getelementptr inbounds [12 x i8], [12 x i8]* %realsize63, i32 0, i32 0, !dbg !3030
  %call65 = call i64 @tar_atol(i8* %arraydecay64, i64 12), !dbg !3033
  %58 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3034
  %realsize66 = getelementptr inbounds %struct.tar, %struct.tar* %58, i32 0, i32 17, !dbg !3035
  store i64 %call65, i64* %realsize66, align 8, !dbg !3036
  %59 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3037
  %60 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3038
  %realsize67 = getelementptr inbounds %struct.tar, %struct.tar* %60, i32 0, i32 17, !dbg !3039
  %61 = load i64, i64* %realsize67, align 8, !dbg !3039
  call void @archive_entry_set_size(%struct.archive_entry* %59, i64 %61), !dbg !3040
  br label %if.end68, !dbg !3041

if.end68:                                         ; preds = %if.then62, %if.end57
  %62 = load %struct.archive_entry_header_gnutar*, %struct.archive_entry_header_gnutar** %header, align 8, !dbg !3042
  %sparse = getelementptr inbounds %struct.archive_entry_header_gnutar, %struct.archive_entry_header_gnutar* %62, i32 0, i32 19, !dbg !3044
  %arrayidx69 = getelementptr inbounds [4 x %struct.gnu_sparse], [4 x %struct.gnu_sparse]* %sparse, i64 0, i64 0, !dbg !3042
  %offset = getelementptr inbounds %struct.gnu_sparse, %struct.gnu_sparse* %arrayidx69, i32 0, i32 0, !dbg !3045
  %arrayidx70 = getelementptr inbounds [12 x i8], [12 x i8]* %offset, i64 0, i64 0, !dbg !3042
  %63 = load i8, i8* %arrayidx70, align 1, !dbg !3042
  %conv71 = sext i8 %63 to i32, !dbg !3042
  %cmp72 = icmp ne i32 %conv71, 0, !dbg !3046
  br i1 %cmp72, label %if.then74, label %if.else80, !dbg !3047

if.then74:                                        ; preds = %if.end68
  %64 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3048
  %65 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3051
  %66 = load %struct.archive_entry_header_gnutar*, %struct.archive_entry_header_gnutar** %header, align 8, !dbg !3052
  %67 = load i64*, i64** %unconsumed.addr, align 8, !dbg !3053
  %call75 = call i32 @gnu_sparse_old_read(%struct.archive_read* %64, %struct.tar* %65, %struct.archive_entry_header_gnutar* %66, i64* %67), !dbg !3054
  %cmp76 = icmp ne i32 %call75, 0, !dbg !3055
  br i1 %cmp76, label %if.then78, label %if.end79, !dbg !3056

if.then78:                                        ; preds = %if.then74
  store i32 -30, i32* %retval, align 4, !dbg !3057
  br label %return, !dbg !3057

if.end79:                                         ; preds = %if.then74
  br label %if.end87, !dbg !3058

if.else80:                                        ; preds = %if.end68
  %68 = load %struct.archive_entry_header_gnutar*, %struct.archive_entry_header_gnutar** %header, align 8, !dbg !3059
  %isextended = getelementptr inbounds %struct.archive_entry_header_gnutar, %struct.archive_entry_header_gnutar* %68, i32 0, i32 20, !dbg !3062
  %arrayidx81 = getelementptr inbounds [1 x i8], [1 x i8]* %isextended, i64 0, i64 0, !dbg !3059
  %69 = load i8, i8* %arrayidx81, align 1, !dbg !3059
  %conv82 = sext i8 %69 to i32, !dbg !3059
  %cmp83 = icmp ne i32 %conv82, 0, !dbg !3063
  br i1 %cmp83, label %if.then85, label %if.end86, !dbg !3064

if.then85:                                        ; preds = %if.else80
  br label %if.end86, !dbg !3065

if.end86:                                         ; preds = %if.then85, %if.else80
  br label %if.end87

if.end87:                                         ; preds = %if.end86, %if.end79
  %70 = load i32, i32* %err, align 4, !dbg !3067
  store i32 %70, i32* %retval, align 4, !dbg !3068
  br label %return, !dbg !3068

return:                                           ; preds = %if.end87, %if.then78, %if.then30, %if.then19, %if.then8, %if.then
  %71 = load i32, i32* %retval, align 4, !dbg !3069
  ret i32 %71, !dbg !3069
}

; Function Attrs: nounwind uwtable
define internal i32 @header_ustar(%struct.archive_read* %a, %struct.tar* %tar, %struct.archive_entry* %entry1, i8* %h) #0 !dbg !527 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %tar.addr = alloca %struct.tar*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %h.addr = alloca i8*, align 8
  %header = alloca %struct.archive_entry_header_ustar*, align 8
  %as = alloca %struct.archive_string*, align 8
  %err = alloca i32, align 4
  %r = alloca i32, align 4
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !3070, metadata !563), !dbg !3071
  store %struct.tar* %tar, %struct.tar** %tar.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tar** %tar.addr, metadata !3072, metadata !563), !dbg !3073
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3074, metadata !563), !dbg !3075
  store i8* %h, i8** %h.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %h.addr, metadata !3076, metadata !563), !dbg !3077
  call void @llvm.dbg.declare(metadata %struct.archive_entry_header_ustar** %header, metadata !3078, metadata !563), !dbg !3079
  call void @llvm.dbg.declare(metadata %struct.archive_string** %as, metadata !3080, metadata !563), !dbg !3081
  call void @llvm.dbg.declare(metadata i32* %err, metadata !3082, metadata !563), !dbg !3083
  store i32 0, i32* %err, align 4, !dbg !3083
  call void @llvm.dbg.declare(metadata i32* %r, metadata !3084, metadata !563), !dbg !3085
  %0 = load i8*, i8** %h.addr, align 8, !dbg !3086
  %1 = bitcast i8* %0 to %struct.archive_entry_header_ustar*, !dbg !3087
  store %struct.archive_entry_header_ustar* %1, %struct.archive_entry_header_ustar** %header, align 8, !dbg !3088
  %2 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3089
  %entry_pathname = getelementptr inbounds %struct.tar, %struct.tar* %2, i32 0, i32 1, !dbg !3090
  store %struct.archive_string* %entry_pathname, %struct.archive_string** %as, align 8, !dbg !3091
  %3 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !3092
  %prefix = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %3, i32 0, i32 15, !dbg !3094
  %arrayidx = getelementptr inbounds [155 x i8], [155 x i8]* %prefix, i64 0, i64 0, !dbg !3092
  %4 = load i8, i8* %arrayidx, align 1, !dbg !3092
  %tobool = icmp ne i8 %4, 0, !dbg !3092
  br i1 %tobool, label %if.then, label %if.else, !dbg !3095

if.then:                                          ; preds = %entry
  %5 = load %struct.archive_string*, %struct.archive_string** %as, align 8, !dbg !3096
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %5, i32 0, i32 1, !dbg !3096
  store i64 0, i64* %length, align 8, !dbg !3096
  %6 = load %struct.archive_string*, %struct.archive_string** %as, align 8, !dbg !3096
  %7 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !3096
  %prefix2 = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %7, i32 0, i32 15, !dbg !3096
  %arraydecay = getelementptr inbounds [155 x i8], [155 x i8]* %prefix2, i32 0, i32 0, !dbg !3096
  %call = call %struct.archive_string* @archive_strncat(%struct.archive_string* %6, i8* %arraydecay, i64 155), !dbg !3096
  %8 = load %struct.archive_string*, %struct.archive_string** %as, align 8, !dbg !3098
  %length3 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %8, i32 0, i32 1, !dbg !3098
  %9 = load i64, i64* %length3, align 8, !dbg !3098
  %sub = sub i64 %9, 1, !dbg !3100
  %10 = load %struct.archive_string*, %struct.archive_string** %as, align 8, !dbg !3101
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %10, i32 0, i32 0, !dbg !3102
  %11 = load i8*, i8** %s, align 8, !dbg !3102
  %arrayidx4 = getelementptr inbounds i8, i8* %11, i64 %sub, !dbg !3101
  %12 = load i8, i8* %arrayidx4, align 1, !dbg !3101
  %conv = sext i8 %12 to i32, !dbg !3101
  %cmp = icmp ne i32 %conv, 47, !dbg !3103
  br i1 %cmp, label %if.then6, label %if.end, !dbg !3104

if.then6:                                         ; preds = %if.then
  %13 = load %struct.archive_string*, %struct.archive_string** %as, align 8, !dbg !3105
  %call7 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %13, i8 signext 47), !dbg !3106
  br label %if.end, !dbg !3106

if.end:                                           ; preds = %if.then6, %if.then
  %14 = load %struct.archive_string*, %struct.archive_string** %as, align 8, !dbg !3107
  %15 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !3108
  %name = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %15, i32 0, i32 0, !dbg !3109
  %arraydecay8 = getelementptr inbounds [100 x i8], [100 x i8]* %name, i32 0, i32 0, !dbg !3108
  %call9 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %14, i8* %arraydecay8, i64 100), !dbg !3110
  br label %if.end14, !dbg !3111

if.else:                                          ; preds = %entry
  %16 = load %struct.archive_string*, %struct.archive_string** %as, align 8, !dbg !3112
  %length10 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %16, i32 0, i32 1, !dbg !3112
  store i64 0, i64* %length10, align 8, !dbg !3112
  %17 = load %struct.archive_string*, %struct.archive_string** %as, align 8, !dbg !3112
  %18 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !3112
  %name11 = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %18, i32 0, i32 0, !dbg !3112
  %arraydecay12 = getelementptr inbounds [100 x i8], [100 x i8]* %name11, i32 0, i32 0, !dbg !3112
  %call13 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %17, i8* %arraydecay12, i64 100), !dbg !3112
  br label %if.end14

if.end14:                                         ; preds = %if.else, %if.end
  %19 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3114
  %20 = load %struct.archive_string*, %struct.archive_string** %as, align 8, !dbg !3116
  %s15 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %20, i32 0, i32 0, !dbg !3117
  %21 = load i8*, i8** %s15, align 8, !dbg !3117
  %22 = load %struct.archive_string*, %struct.archive_string** %as, align 8, !dbg !3118
  %length16 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %22, i32 0, i32 1, !dbg !3118
  %23 = load i64, i64* %length16, align 8, !dbg !3118
  %24 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3119
  %sconv = getelementptr inbounds %struct.tar, %struct.tar* %24, i32 0, i32 28, !dbg !3120
  %25 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !3120
  %call17 = call i32 @_archive_entry_copy_pathname_l(%struct.archive_entry* %19, i8* %21, i64 %23, %struct.archive_string_conv* %25), !dbg !3121
  %cmp18 = icmp ne i32 %call17, 0, !dbg !3122
  br i1 %cmp18, label %if.then20, label %if.end27, !dbg !3123

if.then20:                                        ; preds = %if.end14
  %26 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3124
  %27 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3126
  %sconv21 = getelementptr inbounds %struct.tar, %struct.tar* %27, i32 0, i32 28, !dbg !3127
  %28 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv21, align 8, !dbg !3127
  %call22 = call i32 @set_conversion_failed_error(%struct.archive_read* %26, %struct.archive_string_conv* %28, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.34, i32 0, i32 0)), !dbg !3128
  store i32 %call22, i32* %err, align 4, !dbg !3129
  %29 = load i32, i32* %err, align 4, !dbg !3130
  %cmp23 = icmp eq i32 %29, -30, !dbg !3132
  br i1 %cmp23, label %if.then25, label %if.end26, !dbg !3133

if.then25:                                        ; preds = %if.then20
  %30 = load i32, i32* %err, align 4, !dbg !3134
  store i32 %30, i32* %retval, align 4, !dbg !3135
  br label %return, !dbg !3135

if.end26:                                         ; preds = %if.then20
  br label %if.end27, !dbg !3136

if.end27:                                         ; preds = %if.end26, %if.end14
  %31 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3137
  %32 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3138
  %33 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3139
  %34 = load i8*, i8** %h.addr, align 8, !dbg !3140
  %call28 = call i32 @header_common(%struct.archive_read* %31, %struct.tar* %32, %struct.archive_entry* %33, i8* %34), !dbg !3141
  store i32 %call28, i32* %r, align 4, !dbg !3142
  %35 = load i32, i32* %r, align 4, !dbg !3143
  %cmp29 = icmp eq i32 %35, -30, !dbg !3145
  br i1 %cmp29, label %if.then31, label %if.end32, !dbg !3146

if.then31:                                        ; preds = %if.end27
  %36 = load i32, i32* %r, align 4, !dbg !3147
  store i32 %36, i32* %retval, align 4, !dbg !3148
  br label %return, !dbg !3148

if.end32:                                         ; preds = %if.end27
  %37 = load i32, i32* %r, align 4, !dbg !3149
  %38 = load i32, i32* %err, align 4, !dbg !3151
  %cmp33 = icmp slt i32 %37, %38, !dbg !3152
  br i1 %cmp33, label %if.then35, label %if.end36, !dbg !3153

if.then35:                                        ; preds = %if.end32
  %39 = load i32, i32* %r, align 4, !dbg !3154
  store i32 %39, i32* %err, align 4, !dbg !3155
  br label %if.end36, !dbg !3156

if.end36:                                         ; preds = %if.then35, %if.end32
  %40 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3157
  %41 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !3159
  %uname = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %41, i32 0, i32 11, !dbg !3160
  %arraydecay37 = getelementptr inbounds [32 x i8], [32 x i8]* %uname, i32 0, i32 0, !dbg !3159
  %42 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3161
  %sconv38 = getelementptr inbounds %struct.tar, %struct.tar* %42, i32 0, i32 28, !dbg !3162
  %43 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv38, align 8, !dbg !3162
  %call39 = call i32 @_archive_entry_copy_uname_l(%struct.archive_entry* %40, i8* %arraydecay37, i64 32, %struct.archive_string_conv* %43), !dbg !3163
  %cmp40 = icmp ne i32 %call39, 0, !dbg !3164
  br i1 %cmp40, label %if.then42, label %if.end49, !dbg !3165

if.then42:                                        ; preds = %if.end36
  %44 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3166
  %45 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3168
  %sconv43 = getelementptr inbounds %struct.tar, %struct.tar* %45, i32 0, i32 28, !dbg !3169
  %46 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv43, align 8, !dbg !3169
  %call44 = call i32 @set_conversion_failed_error(%struct.archive_read* %44, %struct.archive_string_conv* %46, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.43, i32 0, i32 0)), !dbg !3170
  store i32 %call44, i32* %err, align 4, !dbg !3171
  %47 = load i32, i32* %err, align 4, !dbg !3172
  %cmp45 = icmp eq i32 %47, -30, !dbg !3174
  br i1 %cmp45, label %if.then47, label %if.end48, !dbg !3175

if.then47:                                        ; preds = %if.then42
  %48 = load i32, i32* %err, align 4, !dbg !3176
  store i32 %48, i32* %retval, align 4, !dbg !3177
  br label %return, !dbg !3177

if.end48:                                         ; preds = %if.then42
  br label %if.end49, !dbg !3178

if.end49:                                         ; preds = %if.end48, %if.end36
  %49 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3179
  %50 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !3181
  %gname = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %50, i32 0, i32 12, !dbg !3182
  %arraydecay50 = getelementptr inbounds [32 x i8], [32 x i8]* %gname, i32 0, i32 0, !dbg !3181
  %51 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3183
  %sconv51 = getelementptr inbounds %struct.tar, %struct.tar* %51, i32 0, i32 28, !dbg !3184
  %52 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv51, align 8, !dbg !3184
  %call52 = call i32 @_archive_entry_copy_gname_l(%struct.archive_entry* %49, i8* %arraydecay50, i64 32, %struct.archive_string_conv* %52), !dbg !3185
  %cmp53 = icmp ne i32 %call52, 0, !dbg !3186
  br i1 %cmp53, label %if.then55, label %if.end62, !dbg !3187

if.then55:                                        ; preds = %if.end49
  %53 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3188
  %54 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3190
  %sconv56 = getelementptr inbounds %struct.tar, %struct.tar* %54, i32 0, i32 28, !dbg !3191
  %55 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv56, align 8, !dbg !3191
  %call57 = call i32 @set_conversion_failed_error(%struct.archive_read* %53, %struct.archive_string_conv* %55, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.41, i32 0, i32 0)), !dbg !3192
  store i32 %call57, i32* %err, align 4, !dbg !3193
  %56 = load i32, i32* %err, align 4, !dbg !3194
  %cmp58 = icmp eq i32 %56, -30, !dbg !3196
  br i1 %cmp58, label %if.then60, label %if.end61, !dbg !3197

if.then60:                                        ; preds = %if.then55
  %57 = load i32, i32* %err, align 4, !dbg !3198
  store i32 %57, i32* %retval, align 4, !dbg !3199
  br label %return, !dbg !3199

if.end61:                                         ; preds = %if.then55
  br label %if.end62, !dbg !3200

if.end62:                                         ; preds = %if.end61, %if.end49
  %58 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !3201
  %typeflag = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %58, i32 0, i32 7, !dbg !3203
  %arrayidx63 = getelementptr inbounds [1 x i8], [1 x i8]* %typeflag, i64 0, i64 0, !dbg !3201
  %59 = load i8, i8* %arrayidx63, align 1, !dbg !3201
  %conv64 = sext i8 %59 to i32, !dbg !3201
  %cmp65 = icmp eq i32 %conv64, 51, !dbg !3204
  br i1 %cmp65, label %if.then72, label %lor.lhs.false, !dbg !3205

lor.lhs.false:                                    ; preds = %if.end62
  %60 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !3206
  %typeflag67 = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %60, i32 0, i32 7, !dbg !3208
  %arrayidx68 = getelementptr inbounds [1 x i8], [1 x i8]* %typeflag67, i64 0, i64 0, !dbg !3206
  %61 = load i8, i8* %arrayidx68, align 1, !dbg !3206
  %conv69 = sext i8 %61 to i32, !dbg !3206
  %cmp70 = icmp eq i32 %conv69, 52, !dbg !3209
  br i1 %cmp70, label %if.then72, label %if.end77, !dbg !3210

if.then72:                                        ; preds = %lor.lhs.false, %if.end62
  %62 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3211
  %63 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !3213
  %rdevmajor = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %63, i32 0, i32 13, !dbg !3214
  %arraydecay73 = getelementptr inbounds [8 x i8], [8 x i8]* %rdevmajor, i32 0, i32 0, !dbg !3213
  %call74 = call i64 @tar_atol(i8* %arraydecay73, i64 8), !dbg !3215
  call void @archive_entry_set_rdevmajor(%struct.archive_entry* %62, i64 %call74), !dbg !3216
  %64 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3217
  %65 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !3218
  %rdevminor = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %65, i32 0, i32 14, !dbg !3219
  %arraydecay75 = getelementptr inbounds [8 x i8], [8 x i8]* %rdevminor, i32 0, i32 0, !dbg !3218
  %call76 = call i64 @tar_atol(i8* %arraydecay75, i64 8), !dbg !3220
  call void @archive_entry_set_rdevminor(%struct.archive_entry* %64, i64 %call76), !dbg !3221
  br label %if.end77, !dbg !3222

if.end77:                                         ; preds = %if.then72, %lor.lhs.false
  %66 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3223
  %entry_bytes_remaining = getelementptr inbounds %struct.tar, %struct.tar* %66, i32 0, i32 13, !dbg !3224
  %67 = load i64, i64* %entry_bytes_remaining, align 8, !dbg !3224
  %sub78 = sub nsw i64 0, %67, !dbg !3225
  %and = and i64 511, %sub78, !dbg !3226
  %68 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3227
  %entry_padding = getelementptr inbounds %struct.tar, %struct.tar* %68, i32 0, i32 15, !dbg !3228
  store i64 %and, i64* %entry_padding, align 8, !dbg !3229
  %69 = load i32, i32* %err, align 4, !dbg !3230
  store i32 %69, i32* %retval, align 4, !dbg !3231
  br label %return, !dbg !3231

return:                                           ; preds = %if.end77, %if.then60, %if.then47, %if.then31, %if.then25
  %70 = load i32, i32* %retval, align 4, !dbg !3232
  ret i32 %70, !dbg !3232
}

; Function Attrs: nounwind uwtable
define internal i32 @header_old_tar(%struct.archive_read* %a, %struct.tar* %tar, %struct.archive_entry* %entry1, i8* %h) #0 !dbg !528 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %tar.addr = alloca %struct.tar*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %h.addr = alloca i8*, align 8
  %header = alloca %struct.archive_entry_header_ustar*, align 8
  %err = alloca i32, align 4
  %err2 = alloca i32, align 4
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !3233, metadata !563), !dbg !3234
  store %struct.tar* %tar, %struct.tar** %tar.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tar** %tar.addr, metadata !3235, metadata !563), !dbg !3236
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3237, metadata !563), !dbg !3238
  store i8* %h, i8** %h.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %h.addr, metadata !3239, metadata !563), !dbg !3240
  call void @llvm.dbg.declare(metadata %struct.archive_entry_header_ustar** %header, metadata !3241, metadata !563), !dbg !3242
  call void @llvm.dbg.declare(metadata i32* %err, metadata !3243, metadata !563), !dbg !3244
  store i32 0, i32* %err, align 4, !dbg !3244
  call void @llvm.dbg.declare(metadata i32* %err2, metadata !3245, metadata !563), !dbg !3246
  %0 = load i8*, i8** %h.addr, align 8, !dbg !3247
  %1 = bitcast i8* %0 to %struct.archive_entry_header_ustar*, !dbg !3248
  store %struct.archive_entry_header_ustar* %1, %struct.archive_entry_header_ustar** %header, align 8, !dbg !3249
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3250
  %3 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !3252
  %name = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %3, i32 0, i32 0, !dbg !3253
  %arraydecay = getelementptr inbounds [100 x i8], [100 x i8]* %name, i32 0, i32 0, !dbg !3252
  %4 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3254
  %sconv = getelementptr inbounds %struct.tar, %struct.tar* %4, i32 0, i32 28, !dbg !3255
  %5 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !3255
  %call = call i32 @_archive_entry_copy_pathname_l(%struct.archive_entry* %2, i8* %arraydecay, i64 100, %struct.archive_string_conv* %5), !dbg !3256
  %cmp = icmp ne i32 %call, 0, !dbg !3257
  br i1 %cmp, label %if.then, label %if.end6, !dbg !3258

if.then:                                          ; preds = %entry
  %6 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3259
  %7 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3261
  %sconv2 = getelementptr inbounds %struct.tar, %struct.tar* %7, i32 0, i32 28, !dbg !3262
  %8 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv2, align 8, !dbg !3262
  %call3 = call i32 @set_conversion_failed_error(%struct.archive_read* %6, %struct.archive_string_conv* %8, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.34, i32 0, i32 0)), !dbg !3263
  store i32 %call3, i32* %err, align 4, !dbg !3264
  %9 = load i32, i32* %err, align 4, !dbg !3265
  %cmp4 = icmp eq i32 %9, -30, !dbg !3267
  br i1 %cmp4, label %if.then5, label %if.end, !dbg !3268

if.then5:                                         ; preds = %if.then
  %10 = load i32, i32* %err, align 4, !dbg !3269
  store i32 %10, i32* %retval, align 4, !dbg !3270
  br label %return, !dbg !3270

if.end:                                           ; preds = %if.then
  br label %if.end6, !dbg !3271

if.end6:                                          ; preds = %if.end, %entry
  %11 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3272
  %12 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3273
  %13 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3274
  %14 = load i8*, i8** %h.addr, align 8, !dbg !3275
  %call7 = call i32 @header_common(%struct.archive_read* %11, %struct.tar* %12, %struct.archive_entry* %13, i8* %14), !dbg !3276
  store i32 %call7, i32* %err2, align 4, !dbg !3277
  %15 = load i32, i32* %err, align 4, !dbg !3278
  %16 = load i32, i32* %err2, align 4, !dbg !3280
  %cmp8 = icmp sgt i32 %15, %16, !dbg !3281
  br i1 %cmp8, label %if.then9, label %if.end10, !dbg !3282

if.then9:                                         ; preds = %if.end6
  %17 = load i32, i32* %err2, align 4, !dbg !3283
  store i32 %17, i32* %err, align 4, !dbg !3284
  br label %if.end10, !dbg !3285

if.end10:                                         ; preds = %if.then9, %if.end6
  %18 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3286
  %entry_bytes_remaining = getelementptr inbounds %struct.tar, %struct.tar* %18, i32 0, i32 13, !dbg !3287
  %19 = load i64, i64* %entry_bytes_remaining, align 8, !dbg !3287
  %sub = sub nsw i64 0, %19, !dbg !3288
  %and = and i64 511, %sub, !dbg !3289
  %20 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3290
  %entry_padding = getelementptr inbounds %struct.tar, %struct.tar* %20, i32 0, i32 15, !dbg !3291
  store i64 %and, i64* %entry_padding, align 8, !dbg !3292
  %21 = load i32, i32* %err, align 4, !dbg !3293
  store i32 %21, i32* %retval, align 4, !dbg !3294
  br label %return, !dbg !3294

return:                                           ; preds = %if.end10, %if.then5
  %22 = load i32, i32* %retval, align 4, !dbg !3295
  ret i32 %22, !dbg !3295
}

; Function Attrs: nounwind uwtable
define internal i32 @read_mac_metadata_blob(%struct.archive_read* %a, %struct.tar* %tar, %struct.archive_entry* %entry1, i8* %h, i64* %unconsumed) #0 !dbg !529 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %tar.addr = alloca %struct.tar*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %h.addr = alloca i8*, align 8
  %unconsumed.addr = alloca i64*, align 8
  %size = alloca i64, align 8
  %data = alloca i8*, align 8
  %p = alloca i8*, align 8
  %name = alloca i8*, align 8
  %wp = alloca i32*, align 8
  %wname = alloca i32*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !3296, metadata !563), !dbg !3297
  store %struct.tar* %tar, %struct.tar** %tar.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tar** %tar.addr, metadata !3298, metadata !563), !dbg !3299
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3300, metadata !563), !dbg !3301
  store i8* %h, i8** %h.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %h.addr, metadata !3302, metadata !563), !dbg !3303
  store i64* %unconsumed, i64** %unconsumed.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %unconsumed.addr, metadata !3304, metadata !563), !dbg !3305
  call void @llvm.dbg.declare(metadata i64* %size, metadata !3306, metadata !563), !dbg !3307
  call void @llvm.dbg.declare(metadata i8** %data, metadata !3308, metadata !563), !dbg !3309
  call void @llvm.dbg.declare(metadata i8** %p, metadata !3310, metadata !563), !dbg !3311
  call void @llvm.dbg.declare(metadata i8** %name, metadata !3312, metadata !563), !dbg !3313
  call void @llvm.dbg.declare(metadata i32** %wp, metadata !3314, metadata !563), !dbg !3315
  call void @llvm.dbg.declare(metadata i32** %wname, metadata !3316, metadata !563), !dbg !3317
  %0 = load i8*, i8** %h.addr, align 8, !dbg !3318
  %1 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3319
  %call = call i32* @archive_entry_pathname_w(%struct.archive_entry* %1), !dbg !3320
  store i32* %call, i32** %wp, align 8, !dbg !3321
  store i32* %call, i32** %wname, align 8, !dbg !3322
  %2 = load i32*, i32** %wp, align 8, !dbg !3323
  %cmp = icmp ne i32* %2, null, !dbg !3325
  br i1 %cmp, label %if.then, label %if.else, !dbg !3326

if.then:                                          ; preds = %entry
  br label %for.cond, !dbg !3327

for.cond:                                         ; preds = %for.inc, %if.then
  %3 = load i32*, i32** %wp, align 8, !dbg !3329
  %4 = load i32, i32* %3, align 4, !dbg !3333
  %cmp2 = icmp ne i32 %4, 0, !dbg !3334
  br i1 %cmp2, label %for.body, label %for.end, !dbg !3335

for.body:                                         ; preds = %for.cond
  %5 = load i32*, i32** %wp, align 8, !dbg !3336
  %arrayidx = getelementptr inbounds i32, i32* %5, i64 0, !dbg !3336
  %6 = load i32, i32* %arrayidx, align 4, !dbg !3336
  %cmp3 = icmp eq i32 %6, 47, !dbg !3339
  br i1 %cmp3, label %land.lhs.true, label %if.end, !dbg !3340

land.lhs.true:                                    ; preds = %for.body
  %7 = load i32*, i32** %wp, align 8, !dbg !3341
  %arrayidx4 = getelementptr inbounds i32, i32* %7, i64 1, !dbg !3341
  %8 = load i32, i32* %arrayidx4, align 4, !dbg !3341
  %cmp5 = icmp ne i32 %8, 0, !dbg !3343
  br i1 %cmp5, label %if.then6, label %if.end, !dbg !3344

if.then6:                                         ; preds = %land.lhs.true
  %9 = load i32*, i32** %wp, align 8, !dbg !3345
  %add.ptr = getelementptr inbounds i32, i32* %9, i64 1, !dbg !3346
  store i32* %add.ptr, i32** %wname, align 8, !dbg !3347
  br label %if.end, !dbg !3348

if.end:                                           ; preds = %if.then6, %land.lhs.true, %for.body
  br label %for.inc, !dbg !3349

for.inc:                                          ; preds = %if.end
  %10 = load i32*, i32** %wp, align 8, !dbg !3350
  %incdec.ptr = getelementptr inbounds i32, i32* %10, i32 1, !dbg !3350
  store i32* %incdec.ptr, i32** %wp, align 8, !dbg !3350
  br label %for.cond, !dbg !3352

for.end:                                          ; preds = %for.cond
  %11 = load i32*, i32** %wname, align 8, !dbg !3353
  %arrayidx7 = getelementptr inbounds i32, i32* %11, i64 0, !dbg !3353
  %12 = load i32, i32* %arrayidx7, align 4, !dbg !3353
  %cmp8 = icmp ne i32 %12, 46, !dbg !3355
  br i1 %cmp8, label %if.then14, label %lor.lhs.false, !dbg !3356

lor.lhs.false:                                    ; preds = %for.end
  %13 = load i32*, i32** %wname, align 8, !dbg !3357
  %arrayidx9 = getelementptr inbounds i32, i32* %13, i64 1, !dbg !3357
  %14 = load i32, i32* %arrayidx9, align 4, !dbg !3357
  %cmp10 = icmp ne i32 %14, 95, !dbg !3359
  br i1 %cmp10, label %if.then14, label %lor.lhs.false11, !dbg !3360

lor.lhs.false11:                                  ; preds = %lor.lhs.false
  %15 = load i32*, i32** %wname, align 8, !dbg !3361
  %arrayidx12 = getelementptr inbounds i32, i32* %15, i64 2, !dbg !3361
  %16 = load i32, i32* %arrayidx12, align 4, !dbg !3361
  %cmp13 = icmp eq i32 %16, 0, !dbg !3363
  br i1 %cmp13, label %if.then14, label %if.end15, !dbg !3364

if.then14:                                        ; preds = %lor.lhs.false11, %lor.lhs.false, %for.end
  store i32 0, i32* %retval, align 4, !dbg !3365
  br label %return, !dbg !3365

if.end15:                                         ; preds = %lor.lhs.false11
  br label %if.end55, !dbg !3366

if.else:                                          ; preds = %entry
  %17 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3367
  %call16 = call i8* @archive_entry_pathname(%struct.archive_entry* %17), !dbg !3369
  store i8* %call16, i8** %p, align 8, !dbg !3370
  store i8* %call16, i8** %name, align 8, !dbg !3371
  %18 = load i8*, i8** %p, align 8, !dbg !3372
  %cmp17 = icmp eq i8* %18, null, !dbg !3374
  br i1 %cmp17, label %if.then18, label %if.end19, !dbg !3375

if.then18:                                        ; preds = %if.else
  store i32 -25, i32* %retval, align 4, !dbg !3376
  br label %return, !dbg !3376

if.end19:                                         ; preds = %if.else
  br label %for.cond20, !dbg !3377

for.cond20:                                       ; preds = %for.inc36, %if.end19
  %19 = load i8*, i8** %p, align 8, !dbg !3378
  %20 = load i8, i8* %19, align 1, !dbg !3382
  %conv = sext i8 %20 to i32, !dbg !3382
  %cmp21 = icmp ne i32 %conv, 0, !dbg !3383
  br i1 %cmp21, label %for.body23, label %for.end38, !dbg !3384

for.body23:                                       ; preds = %for.cond20
  %21 = load i8*, i8** %p, align 8, !dbg !3385
  %arrayidx24 = getelementptr inbounds i8, i8* %21, i64 0, !dbg !3385
  %22 = load i8, i8* %arrayidx24, align 1, !dbg !3385
  %conv25 = sext i8 %22 to i32, !dbg !3385
  %cmp26 = icmp eq i32 %conv25, 47, !dbg !3388
  br i1 %cmp26, label %land.lhs.true28, label %if.end35, !dbg !3389

land.lhs.true28:                                  ; preds = %for.body23
  %23 = load i8*, i8** %p, align 8, !dbg !3390
  %arrayidx29 = getelementptr inbounds i8, i8* %23, i64 1, !dbg !3390
  %24 = load i8, i8* %arrayidx29, align 1, !dbg !3390
  %conv30 = sext i8 %24 to i32, !dbg !3390
  %cmp31 = icmp ne i32 %conv30, 0, !dbg !3392
  br i1 %cmp31, label %if.then33, label %if.end35, !dbg !3393

if.then33:                                        ; preds = %land.lhs.true28
  %25 = load i8*, i8** %p, align 8, !dbg !3394
  %add.ptr34 = getelementptr inbounds i8, i8* %25, i64 1, !dbg !3395
  store i8* %add.ptr34, i8** %name, align 8, !dbg !3396
  br label %if.end35, !dbg !3397

if.end35:                                         ; preds = %if.then33, %land.lhs.true28, %for.body23
  br label %for.inc36, !dbg !3398

for.inc36:                                        ; preds = %if.end35
  %26 = load i8*, i8** %p, align 8, !dbg !3399
  %incdec.ptr37 = getelementptr inbounds i8, i8* %26, i32 1, !dbg !3399
  store i8* %incdec.ptr37, i8** %p, align 8, !dbg !3399
  br label %for.cond20, !dbg !3401

for.end38:                                        ; preds = %for.cond20
  %27 = load i8*, i8** %name, align 8, !dbg !3402
  %arrayidx39 = getelementptr inbounds i8, i8* %27, i64 0, !dbg !3402
  %28 = load i8, i8* %arrayidx39, align 1, !dbg !3402
  %conv40 = sext i8 %28 to i32, !dbg !3402
  %cmp41 = icmp ne i32 %conv40, 46, !dbg !3404
  br i1 %cmp41, label %if.then53, label %lor.lhs.false43, !dbg !3405

lor.lhs.false43:                                  ; preds = %for.end38
  %29 = load i8*, i8** %name, align 8, !dbg !3406
  %arrayidx44 = getelementptr inbounds i8, i8* %29, i64 1, !dbg !3406
  %30 = load i8, i8* %arrayidx44, align 1, !dbg !3406
  %conv45 = sext i8 %30 to i32, !dbg !3406
  %cmp46 = icmp ne i32 %conv45, 95, !dbg !3408
  br i1 %cmp46, label %if.then53, label %lor.lhs.false48, !dbg !3409

lor.lhs.false48:                                  ; preds = %lor.lhs.false43
  %31 = load i8*, i8** %name, align 8, !dbg !3410
  %arrayidx49 = getelementptr inbounds i8, i8* %31, i64 2, !dbg !3410
  %32 = load i8, i8* %arrayidx49, align 1, !dbg !3410
  %conv50 = sext i8 %32 to i32, !dbg !3410
  %cmp51 = icmp eq i32 %conv50, 0, !dbg !3412
  br i1 %cmp51, label %if.then53, label %if.end54, !dbg !3413

if.then53:                                        ; preds = %lor.lhs.false48, %lor.lhs.false43, %for.end38
  store i32 0, i32* %retval, align 4, !dbg !3414
  br label %return, !dbg !3414

if.end54:                                         ; preds = %lor.lhs.false48
  br label %if.end55

if.end55:                                         ; preds = %if.end54, %if.end15
  %33 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3415
  %call56 = call i64 @archive_entry_size(%struct.archive_entry* %33), !dbg !3416
  store i64 %call56, i64* %size, align 8, !dbg !3417
  %34 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3418
  %35 = load i64, i64* %size, align 8, !dbg !3419
  %call57 = call i8* @__archive_read_ahead(%struct.archive_read* %34, i64 %35, i64* null), !dbg !3420
  store i8* %call57, i8** %data, align 8, !dbg !3421
  %36 = load i8*, i8** %data, align 8, !dbg !3422
  %cmp58 = icmp eq i8* %36, null, !dbg !3424
  br i1 %cmp58, label %if.then60, label %if.end61, !dbg !3425

if.then60:                                        ; preds = %if.end55
  %37 = load i64*, i64** %unconsumed.addr, align 8, !dbg !3426
  store i64 0, i64* %37, align 8, !dbg !3428
  store i32 -30, i32* %retval, align 4, !dbg !3429
  br label %return, !dbg !3429

if.end61:                                         ; preds = %if.end55
  %38 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3430
  %39 = load i8*, i8** %data, align 8, !dbg !3431
  %40 = load i64, i64* %size, align 8, !dbg !3432
  call void @archive_entry_copy_mac_metadata(%struct.archive_entry* %38, i8* %39, i64 %40), !dbg !3433
  %41 = load i64, i64* %size, align 8, !dbg !3434
  %add = add nsw i64 %41, 511, !dbg !3435
  %and = and i64 %add, -512, !dbg !3436
  %42 = load i64*, i64** %unconsumed.addr, align 8, !dbg !3437
  store i64 %and, i64* %42, align 8, !dbg !3438
  %43 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3439
  %44 = load i64*, i64** %unconsumed.addr, align 8, !dbg !3440
  call void @tar_flush_unconsumed(%struct.archive_read* %43, i64* %44), !dbg !3441
  %45 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3442
  %46 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3443
  %47 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3444
  %48 = load i64*, i64** %unconsumed.addr, align 8, !dbg !3445
  %call62 = call i32 @tar_read_header(%struct.archive_read* %45, %struct.tar* %46, %struct.archive_entry* %47, i64* %48), !dbg !3446
  store i32 %call62, i32* %retval, align 4, !dbg !3447
  br label %return, !dbg !3447

return:                                           ; preds = %if.end61, %if.then60, %if.then53, %if.then18, %if.then14
  %49 = load i32, i32* %retval, align 4, !dbg !3448
  ret i32 %49, !dbg !3448
}

; Function Attrs: nounwind uwtable
define internal i64 @gnu_sparse_10_read(%struct.archive_read* %a, %struct.tar* %tar, i64* %unconsumed) #0 !dbg !530 {
entry:
  %retval = alloca i64, align 8
  %a.addr = alloca %struct.archive_read*, align 8
  %tar.addr = alloca %struct.tar*, align 8
  %unconsumed.addr = alloca i64*, align 8
  %bytes_read = alloca i64, align 8
  %entries = alloca i32, align 4
  %offset = alloca i64, align 8
  %size = alloca i64, align 8
  %to_skip = alloca i64, align 8
  %remaining = alloca i64, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !3449, metadata !563), !dbg !3450
  store %struct.tar* %tar, %struct.tar** %tar.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tar** %tar.addr, metadata !3451, metadata !563), !dbg !3452
  store i64* %unconsumed, i64** %unconsumed.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %unconsumed.addr, metadata !3453, metadata !563), !dbg !3454
  call void @llvm.dbg.declare(metadata i64* %bytes_read, metadata !3455, metadata !563), !dbg !3456
  call void @llvm.dbg.declare(metadata i32* %entries, metadata !3457, metadata !563), !dbg !3458
  call void @llvm.dbg.declare(metadata i64* %offset, metadata !3459, metadata !563), !dbg !3460
  call void @llvm.dbg.declare(metadata i64* %size, metadata !3461, metadata !563), !dbg !3462
  call void @llvm.dbg.declare(metadata i64* %to_skip, metadata !3463, metadata !563), !dbg !3464
  call void @llvm.dbg.declare(metadata i64* %remaining, metadata !3465, metadata !563), !dbg !3466
  %0 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3467
  call void @gnu_clear_sparse_list(%struct.tar* %0), !dbg !3468
  %1 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3469
  %entry_bytes_remaining = getelementptr inbounds %struct.tar, %struct.tar* %1, i32 0, i32 13, !dbg !3470
  %2 = load i64, i64* %entry_bytes_remaining, align 8, !dbg !3470
  store i64 %2, i64* %remaining, align 8, !dbg !3471
  %3 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3472
  %4 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3473
  %5 = load i64*, i64** %unconsumed.addr, align 8, !dbg !3474
  %call = call i64 @gnu_sparse_10_atol(%struct.archive_read* %3, %struct.tar* %4, i64* %remaining, i64* %5), !dbg !3475
  %conv = trunc i64 %call to i32, !dbg !3476
  store i32 %conv, i32* %entries, align 4, !dbg !3477
  %6 = load i32, i32* %entries, align 4, !dbg !3478
  %cmp = icmp slt i32 %6, 0, !dbg !3480
  br i1 %cmp, label %if.then, label %if.end, !dbg !3481

if.then:                                          ; preds = %entry
  store i64 -30, i64* %retval, align 8, !dbg !3482
  br label %return, !dbg !3482

if.end:                                           ; preds = %entry
  br label %while.cond, !dbg !3483

while.cond:                                       ; preds = %if.end18, %if.end
  %7 = load i32, i32* %entries, align 4, !dbg !3484
  %dec = add nsw i32 %7, -1, !dbg !3484
  store i32 %dec, i32* %entries, align 4, !dbg !3484
  %cmp2 = icmp sgt i32 %7, 0, !dbg !3486
  br i1 %cmp2, label %while.body, label %while.end, !dbg !3487

while.body:                                       ; preds = %while.cond
  %8 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3488
  %9 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3490
  %10 = load i64*, i64** %unconsumed.addr, align 8, !dbg !3491
  %call4 = call i64 @gnu_sparse_10_atol(%struct.archive_read* %8, %struct.tar* %9, i64* %remaining, i64* %10), !dbg !3492
  store i64 %call4, i64* %offset, align 8, !dbg !3493
  %11 = load i64, i64* %offset, align 8, !dbg !3494
  %cmp5 = icmp slt i64 %11, 0, !dbg !3496
  br i1 %cmp5, label %if.then7, label %if.end8, !dbg !3497

if.then7:                                         ; preds = %while.body
  store i64 -30, i64* %retval, align 8, !dbg !3498
  br label %return, !dbg !3498

if.end8:                                          ; preds = %while.body
  %12 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3499
  %13 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3500
  %14 = load i64*, i64** %unconsumed.addr, align 8, !dbg !3501
  %call9 = call i64 @gnu_sparse_10_atol(%struct.archive_read* %12, %struct.tar* %13, i64* %remaining, i64* %14), !dbg !3502
  store i64 %call9, i64* %size, align 8, !dbg !3503
  %15 = load i64, i64* %size, align 8, !dbg !3504
  %cmp10 = icmp slt i64 %15, 0, !dbg !3506
  br i1 %cmp10, label %if.then12, label %if.end13, !dbg !3507

if.then12:                                        ; preds = %if.end8
  store i64 -30, i64* %retval, align 8, !dbg !3508
  br label %return, !dbg !3508

if.end13:                                         ; preds = %if.end8
  %16 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3509
  %17 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3511
  %18 = load i64, i64* %offset, align 8, !dbg !3512
  %19 = load i64, i64* %size, align 8, !dbg !3513
  %call14 = call i32 @gnu_add_sparse_entry(%struct.archive_read* %16, %struct.tar* %17, i64 %18, i64 %19), !dbg !3514
  %cmp15 = icmp ne i32 %call14, 0, !dbg !3515
  br i1 %cmp15, label %if.then17, label %if.end18, !dbg !3516

if.then17:                                        ; preds = %if.end13
  store i64 -30, i64* %retval, align 8, !dbg !3517
  br label %return, !dbg !3517

if.end18:                                         ; preds = %if.end13
  br label %while.cond, !dbg !3518

while.end:                                        ; preds = %while.cond
  %20 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3520
  %21 = load i64*, i64** %unconsumed.addr, align 8, !dbg !3521
  call void @tar_flush_unconsumed(%struct.archive_read* %20, i64* %21), !dbg !3522
  %22 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3523
  %entry_bytes_remaining19 = getelementptr inbounds %struct.tar, %struct.tar* %22, i32 0, i32 13, !dbg !3524
  %23 = load i64, i64* %entry_bytes_remaining19, align 8, !dbg !3524
  %24 = load i64, i64* %remaining, align 8, !dbg !3525
  %sub = sub nsw i64 %23, %24, !dbg !3526
  store i64 %sub, i64* %bytes_read, align 8, !dbg !3527
  %25 = load i64, i64* %bytes_read, align 8, !dbg !3528
  %sub20 = sub nsw i64 0, %25, !dbg !3529
  %and = and i64 511, %sub20, !dbg !3530
  store i64 %and, i64* %to_skip, align 8, !dbg !3531
  %26 = load i64, i64* %to_skip, align 8, !dbg !3532
  %27 = load i64, i64* %remaining, align 8, !dbg !3534
  %cmp21 = icmp sgt i64 %26, %27, !dbg !3535
  br i1 %cmp21, label %if.then23, label %if.end24, !dbg !3536

if.then23:                                        ; preds = %while.end
  store i64 -30, i64* %retval, align 8, !dbg !3537
  br label %return, !dbg !3537

if.end24:                                         ; preds = %while.end
  %28 = load i64, i64* %to_skip, align 8, !dbg !3538
  %29 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3540
  %30 = load i64, i64* %to_skip, align 8, !dbg !3541
  %call25 = call i64 @__archive_read_consume(%struct.archive_read* %29, i64 %30), !dbg !3542
  %cmp26 = icmp ne i64 %28, %call25, !dbg !3543
  br i1 %cmp26, label %if.then28, label %if.end29, !dbg !3544

if.then28:                                        ; preds = %if.end24
  store i64 -30, i64* %retval, align 8, !dbg !3545
  br label %return, !dbg !3545

if.end29:                                         ; preds = %if.end24
  %31 = load i64, i64* %bytes_read, align 8, !dbg !3546
  %32 = load i64, i64* %to_skip, align 8, !dbg !3547
  %add = add nsw i64 %31, %32, !dbg !3548
  store i64 %add, i64* %retval, align 8, !dbg !3549
  br label %return, !dbg !3549

return:                                           ; preds = %if.end29, %if.then28, %if.then23, %if.then17, %if.then12, %if.then7, %if.then
  %33 = load i64, i64* %retval, align 8, !dbg !3550
  ret i64 %33, !dbg !3550
}

; Function Attrs: nounwind uwtable
define internal i32 @read_body_to_string(%struct.archive_read* %a, %struct.tar* %tar, %struct.archive_string* %as, i8* %h, i64* %unconsumed) #0 !dbg !471 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %tar.addr = alloca %struct.tar*, align 8
  %as.addr = alloca %struct.archive_string*, align 8
  %h.addr = alloca i8*, align 8
  %unconsumed.addr = alloca i64*, align 8
  %size = alloca i64, align 8
  %header = alloca %struct.archive_entry_header_ustar*, align 8
  %src = alloca i8*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !3551, metadata !563), !dbg !3552
  store %struct.tar* %tar, %struct.tar** %tar.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tar** %tar.addr, metadata !3553, metadata !563), !dbg !3554
  store %struct.archive_string* %as, %struct.archive_string** %as.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string** %as.addr, metadata !3555, metadata !563), !dbg !3556
  store i8* %h, i8** %h.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %h.addr, metadata !3557, metadata !563), !dbg !3558
  store i64* %unconsumed, i64** %unconsumed.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %unconsumed.addr, metadata !3559, metadata !563), !dbg !3560
  call void @llvm.dbg.declare(metadata i64* %size, metadata !3561, metadata !563), !dbg !3562
  call void @llvm.dbg.declare(metadata %struct.archive_entry_header_ustar** %header, metadata !3563, metadata !563), !dbg !3564
  call void @llvm.dbg.declare(metadata i8** %src, metadata !3565, metadata !563), !dbg !3566
  %0 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3567
  %1 = load i8*, i8** %h.addr, align 8, !dbg !3568
  %2 = bitcast i8* %1 to %struct.archive_entry_header_ustar*, !dbg !3569
  store %struct.archive_entry_header_ustar* %2, %struct.archive_entry_header_ustar** %header, align 8, !dbg !3570
  %3 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !3571
  %size1 = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %3, i32 0, i32 4, !dbg !3572
  %arraydecay = getelementptr inbounds [12 x i8], [12 x i8]* %size1, i32 0, i32 0, !dbg !3571
  %call = call i64 @tar_atol(i8* %arraydecay, i64 12), !dbg !3573
  store i64 %call, i64* %size, align 8, !dbg !3574
  %4 = load i64, i64* %size, align 8, !dbg !3575
  %cmp = icmp sgt i64 %4, 1048576, !dbg !3577
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !3578

lor.lhs.false:                                    ; preds = %entry
  %5 = load i64, i64* %size, align 8, !dbg !3579
  %cmp2 = icmp slt i64 %5, 0, !dbg !3581
  br i1 %cmp2, label %if.then, label %if.end, !dbg !3582

if.then:                                          ; preds = %lor.lhs.false, %entry
  %6 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3583
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %6, i32 0, i32 0, !dbg !3585
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 22, i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.32, i32 0, i32 0)), !dbg !3586
  store i32 -30, i32* %retval, align 4, !dbg !3587
  br label %return, !dbg !3587

if.end:                                           ; preds = %lor.lhs.false
  %7 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !3588
  %8 = load i64, i64* %size, align 8, !dbg !3590
  %add = add i64 %8, 1, !dbg !3591
  %call3 = call %struct.archive_string* @archive_string_ensure(%struct.archive_string* %7, i64 %add), !dbg !3592
  %cmp4 = icmp eq %struct.archive_string* %call3, null, !dbg !3593
  br i1 %cmp4, label %if.then5, label %if.end7, !dbg !3594

if.then5:                                         ; preds = %if.end
  %9 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3595
  %archive6 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %9, i32 0, i32 0, !dbg !3597
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive6, i32 12, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.33, i32 0, i32 0)), !dbg !3598
  store i32 -30, i32* %retval, align 4, !dbg !3599
  br label %return, !dbg !3599

if.end7:                                          ; preds = %if.end
  %10 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3600
  %11 = load i64*, i64** %unconsumed.addr, align 8, !dbg !3601
  call void @tar_flush_unconsumed(%struct.archive_read* %10, i64* %11), !dbg !3602
  %12 = load i64, i64* %size, align 8, !dbg !3603
  %add8 = add nsw i64 %12, 511, !dbg !3604
  %and = and i64 %add8, -512, !dbg !3605
  %13 = load i64*, i64** %unconsumed.addr, align 8, !dbg !3606
  store i64 %and, i64* %13, align 8, !dbg !3607
  %14 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3608
  %15 = load i64*, i64** %unconsumed.addr, align 8, !dbg !3609
  %16 = load i64, i64* %15, align 8, !dbg !3610
  %call9 = call i8* @__archive_read_ahead(%struct.archive_read* %14, i64 %16, i64* null), !dbg !3611
  store i8* %call9, i8** %src, align 8, !dbg !3612
  %17 = load i8*, i8** %src, align 8, !dbg !3613
  %cmp10 = icmp eq i8* %17, null, !dbg !3615
  br i1 %cmp10, label %if.then11, label %if.end12, !dbg !3616

if.then11:                                        ; preds = %if.end7
  %18 = load i64*, i64** %unconsumed.addr, align 8, !dbg !3617
  store i64 0, i64* %18, align 8, !dbg !3619
  store i32 -30, i32* %retval, align 4, !dbg !3620
  br label %return, !dbg !3620

if.end12:                                         ; preds = %if.end7
  %19 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !3621
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %19, i32 0, i32 0, !dbg !3622
  %20 = load i8*, i8** %s, align 8, !dbg !3622
  %21 = load i8*, i8** %src, align 8, !dbg !3623
  %22 = load i64, i64* %size, align 8, !dbg !3624
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %20, i8* %21, i64 %22, i32 1, i1 false), !dbg !3625
  %23 = load i64, i64* %size, align 8, !dbg !3626
  %24 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !3627
  %s13 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %24, i32 0, i32 0, !dbg !3628
  %25 = load i8*, i8** %s13, align 8, !dbg !3628
  %arrayidx = getelementptr inbounds i8, i8* %25, i64 %23, !dbg !3627
  store i8 0, i8* %arrayidx, align 1, !dbg !3629
  %26 = load i64, i64* %size, align 8, !dbg !3630
  %27 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !3631
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %27, i32 0, i32 1, !dbg !3632
  store i64 %26, i64* %length, align 8, !dbg !3633
  store i32 0, i32* %retval, align 4, !dbg !3634
  br label %return, !dbg !3634

return:                                           ; preds = %if.end12, %if.then11, %if.then5, %if.then
  %28 = load i32, i32* %retval, align 4, !dbg !3635
  ret i32 %28, !dbg !3635
}

declare %struct.archive_string* @archive_strncat(%struct.archive_string*, i8*, i64) #2

declare i32 @archive_acl_from_text_l(%struct.archive_acl*, i8*, i32, %struct.archive_string_conv*) #2

declare %struct.archive_acl* @archive_entry_acl(%struct.archive_entry*) #2

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #5

declare %struct.archive_string* @archive_string_ensure(%struct.archive_string*, i64) #2

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #6

declare void @archive_entry_copy_link(%struct.archive_entry*, i8*) #2

declare i32 @_archive_entry_copy_pathname_l(%struct.archive_entry*, i8*, i64, %struct.archive_string_conv*) #2

; Function Attrs: nounwind uwtable
define internal i32 @set_conversion_failed_error(%struct.archive_read* %a, %struct.archive_string_conv* %sconv, i8* %name) #0 !dbg !478 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %sconv.addr = alloca %struct.archive_string_conv*, align 8
  %name.addr = alloca i8*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !3636, metadata !563), !dbg !3637
  store %struct.archive_string_conv* %sconv, %struct.archive_string_conv** %sconv.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string_conv** %sconv.addr, metadata !3638, metadata !563), !dbg !3639
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !3640, metadata !563), !dbg !3641
  %call = call i32* @__errno_location() #1, !dbg !3642
  %0 = load i32, i32* %call, align 4, !dbg !3642
  %cmp = icmp eq i32 %0, 12, !dbg !3644
  br i1 %cmp, label %if.then, label %if.end, !dbg !3645

if.then:                                          ; preds = %entry
  %1 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3646
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %1, i32 0, i32 0, !dbg !3648
  %2 = load i8*, i8** %name.addr, align 8, !dbg !3649
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.35, i32 0, i32 0), i8* %2), !dbg !3650
  store i32 -30, i32* %retval, align 4, !dbg !3651
  br label %return, !dbg !3651

if.end:                                           ; preds = %entry
  %3 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3652
  %archive1 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %3, i32 0, i32 0, !dbg !3653
  %4 = load i8*, i8** %name.addr, align 8, !dbg !3654
  %5 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv.addr, align 8, !dbg !3655
  %call2 = call i8* @archive_string_conversion_charset_name(%struct.archive_string_conv* %5), !dbg !3656
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive1, i32 84, i8* getelementptr inbounds ([49 x i8], [49 x i8]* @.str.36, i32 0, i32 0), i8* %4, i8* %call2), !dbg !3657
  store i32 -20, i32* %retval, align 4, !dbg !3658
  br label %return, !dbg !3658

return:                                           ; preds = %if.end, %if.then
  %6 = load i32, i32* %retval, align 4, !dbg !3659
  ret i32 %6, !dbg !3659
}

declare i8* @archive_string_conversion_charset_name(%struct.archive_string_conv*) #2

; Function Attrs: nounwind uwtable
define internal i32 @pax_header(%struct.archive_read* %a, %struct.tar* %tar, %struct.archive_entry* %entry1, %struct.archive_string* %in_as) #0 !dbg !483 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %tar.addr = alloca %struct.tar*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %in_as.addr = alloca %struct.archive_string*, align 8
  %attr_length = alloca i64, align 8
  %l = alloca i64, align 8
  %line_length = alloca i64, align 8
  %value_length = alloca i64, align 8
  %p = alloca i8*, align 8
  %key = alloca i8*, align 8
  %value = alloca i8*, align 8
  %as = alloca %struct.archive_string*, align 8
  %sconv = alloca %struct.archive_string_conv*, align 8
  %err = alloca i32, align 4
  %err2 = alloca i32, align 4
  %attr = alloca i8*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !3660, metadata !563), !dbg !3661
  store %struct.tar* %tar, %struct.tar** %tar.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tar** %tar.addr, metadata !3662, metadata !563), !dbg !3663
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3664, metadata !563), !dbg !3665
  store %struct.archive_string* %in_as, %struct.archive_string** %in_as.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string** %in_as.addr, metadata !3666, metadata !563), !dbg !3667
  call void @llvm.dbg.declare(metadata i64* %attr_length, metadata !3668, metadata !563), !dbg !3669
  call void @llvm.dbg.declare(metadata i64* %l, metadata !3670, metadata !563), !dbg !3671
  call void @llvm.dbg.declare(metadata i64* %line_length, metadata !3672, metadata !563), !dbg !3673
  call void @llvm.dbg.declare(metadata i64* %value_length, metadata !3674, metadata !563), !dbg !3675
  call void @llvm.dbg.declare(metadata i8** %p, metadata !3676, metadata !563), !dbg !3677
  call void @llvm.dbg.declare(metadata i8** %key, metadata !3678, metadata !563), !dbg !3679
  call void @llvm.dbg.declare(metadata i8** %value, metadata !3680, metadata !563), !dbg !3681
  call void @llvm.dbg.declare(metadata %struct.archive_string** %as, metadata !3682, metadata !563), !dbg !3683
  call void @llvm.dbg.declare(metadata %struct.archive_string_conv** %sconv, metadata !3684, metadata !563), !dbg !3685
  call void @llvm.dbg.declare(metadata i32* %err, metadata !3686, metadata !563), !dbg !3687
  call void @llvm.dbg.declare(metadata i32* %err2, metadata !3688, metadata !563), !dbg !3689
  call void @llvm.dbg.declare(metadata i8** %attr, metadata !3690, metadata !563), !dbg !3691
  %0 = load %struct.archive_string*, %struct.archive_string** %in_as.addr, align 8, !dbg !3692
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %0, i32 0, i32 0, !dbg !3693
  %1 = load i8*, i8** %s, align 8, !dbg !3693
  store i8* %1, i8** %attr, align 8, !dbg !3691
  %2 = load %struct.archive_string*, %struct.archive_string** %in_as.addr, align 8, !dbg !3694
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %2, i32 0, i32 1, !dbg !3695
  %3 = load i64, i64* %length, align 8, !dbg !3695
  store i64 %3, i64* %attr_length, align 8, !dbg !3696
  %4 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3697
  %pax_hdrcharset_binary = getelementptr inbounds %struct.tar, %struct.tar* %4, i32 0, i32 11, !dbg !3698
  store i32 0, i32* %pax_hdrcharset_binary, align 8, !dbg !3699
  %5 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3700
  %entry_gname = getelementptr inbounds %struct.tar, %struct.tar* %5, i32 0, i32 5, !dbg !3700
  %length2 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %entry_gname, i32 0, i32 1, !dbg !3700
  store i64 0, i64* %length2, align 8, !dbg !3700
  %6 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3701
  %entry_linkpath = getelementptr inbounds %struct.tar, %struct.tar* %6, i32 0, i32 3, !dbg !3701
  %length3 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %entry_linkpath, i32 0, i32 1, !dbg !3701
  store i64 0, i64* %length3, align 8, !dbg !3701
  %7 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3702
  %entry_pathname = getelementptr inbounds %struct.tar, %struct.tar* %7, i32 0, i32 1, !dbg !3702
  %length4 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %entry_pathname, i32 0, i32 1, !dbg !3702
  store i64 0, i64* %length4, align 8, !dbg !3702
  %8 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3703
  %entry_pathname_override = getelementptr inbounds %struct.tar, %struct.tar* %8, i32 0, i32 2, !dbg !3703
  %length5 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %entry_pathname_override, i32 0, i32 1, !dbg !3703
  store i64 0, i64* %length5, align 8, !dbg !3703
  %9 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3704
  %entry_uname = getelementptr inbounds %struct.tar, %struct.tar* %9, i32 0, i32 4, !dbg !3704
  %length6 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %entry_uname, i32 0, i32 1, !dbg !3704
  store i64 0, i64* %length6, align 8, !dbg !3704
  store i32 0, i32* %err, align 4, !dbg !3705
  br label %while.cond, !dbg !3706

while.cond:                                       ; preds = %cond.end, %entry
  %10 = load i64, i64* %attr_length, align 8, !dbg !3707
  %cmp = icmp ugt i64 %10, 0, !dbg !3709
  br i1 %cmp, label %while.body, label %while.end74, !dbg !3710

while.body:                                       ; preds = %while.cond
  store i64 0, i64* %line_length, align 8, !dbg !3711
  %11 = load i64, i64* %attr_length, align 8, !dbg !3713
  store i64 %11, i64* %l, align 8, !dbg !3714
  %12 = load i8*, i8** %attr, align 8, !dbg !3715
  store i8* %12, i8** %p, align 8, !dbg !3716
  br label %while.cond7, !dbg !3717

while.cond7:                                      ; preds = %if.end26, %while.body
  %13 = load i64, i64* %l, align 8, !dbg !3718
  %cmp8 = icmp ugt i64 %13, 0, !dbg !3720
  br i1 %cmp8, label %while.body9, label %while.end, !dbg !3721

while.body9:                                      ; preds = %while.cond7
  %14 = load i8*, i8** %p, align 8, !dbg !3722
  %15 = load i8, i8* %14, align 1, !dbg !3725
  %conv = sext i8 %15 to i32, !dbg !3725
  %cmp10 = icmp eq i32 %conv, 32, !dbg !3726
  br i1 %cmp10, label %if.then, label %if.end, !dbg !3727

if.then:                                          ; preds = %while.body9
  %16 = load i8*, i8** %p, align 8, !dbg !3728
  %incdec.ptr = getelementptr inbounds i8, i8* %16, i32 1, !dbg !3728
  store i8* %incdec.ptr, i8** %p, align 8, !dbg !3728
  %17 = load i64, i64* %l, align 8, !dbg !3730
  %dec = add i64 %17, -1, !dbg !3730
  store i64 %dec, i64* %l, align 8, !dbg !3730
  br label %while.end, !dbg !3731

if.end:                                           ; preds = %while.body9
  %18 = load i8*, i8** %p, align 8, !dbg !3732
  %19 = load i8, i8* %18, align 1, !dbg !3734
  %conv12 = sext i8 %19 to i32, !dbg !3734
  %cmp13 = icmp slt i32 %conv12, 48, !dbg !3735
  br i1 %cmp13, label %if.then18, label %lor.lhs.false, !dbg !3736

lor.lhs.false:                                    ; preds = %if.end
  %20 = load i8*, i8** %p, align 8, !dbg !3737
  %21 = load i8, i8* %20, align 1, !dbg !3739
  %conv15 = sext i8 %21 to i32, !dbg !3739
  %cmp16 = icmp sgt i32 %conv15, 57, !dbg !3740
  br i1 %cmp16, label %if.then18, label %if.end19, !dbg !3741

if.then18:                                        ; preds = %lor.lhs.false, %if.end
  %22 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3742
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %22, i32 0, i32 0, !dbg !3744
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 -1, i8* getelementptr inbounds ([43 x i8], [43 x i8]* @.str.37, i32 0, i32 0)), !dbg !3745
  store i32 -20, i32* %retval, align 4, !dbg !3746
  br label %return, !dbg !3746

if.end19:                                         ; preds = %lor.lhs.false
  %23 = load i64, i64* %line_length, align 8, !dbg !3747
  %mul = mul i64 %23, 10, !dbg !3747
  store i64 %mul, i64* %line_length, align 8, !dbg !3747
  %24 = load i8*, i8** %p, align 8, !dbg !3748
  %25 = load i8, i8* %24, align 1, !dbg !3749
  %conv20 = sext i8 %25 to i32, !dbg !3749
  %sub = sub nsw i32 %conv20, 48, !dbg !3750
  %conv21 = sext i32 %sub to i64, !dbg !3749
  %26 = load i64, i64* %line_length, align 8, !dbg !3751
  %add = add i64 %26, %conv21, !dbg !3751
  store i64 %add, i64* %line_length, align 8, !dbg !3751
  %27 = load i64, i64* %line_length, align 8, !dbg !3752
  %cmp22 = icmp ugt i64 %27, 999999, !dbg !3754
  br i1 %cmp22, label %if.then24, label %if.end26, !dbg !3755

if.then24:                                        ; preds = %if.end19
  %28 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3756
  %archive25 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %28, i32 0, i32 0, !dbg !3758
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive25, i32 -1, i8* getelementptr inbounds ([39 x i8], [39 x i8]* @.str.38, i32 0, i32 0)), !dbg !3759
  store i32 -20, i32* %retval, align 4, !dbg !3760
  br label %return, !dbg !3760

if.end26:                                         ; preds = %if.end19
  %29 = load i8*, i8** %p, align 8, !dbg !3761
  %incdec.ptr27 = getelementptr inbounds i8, i8* %29, i32 1, !dbg !3761
  store i8* %incdec.ptr27, i8** %p, align 8, !dbg !3761
  %30 = load i64, i64* %l, align 8, !dbg !3762
  %dec28 = add i64 %30, -1, !dbg !3762
  store i64 %dec28, i64* %l, align 8, !dbg !3762
  br label %while.cond7, !dbg !3763

while.end:                                        ; preds = %if.then, %while.cond7
  %31 = load i64, i64* %line_length, align 8, !dbg !3765
  %32 = load i64, i64* %attr_length, align 8, !dbg !3767
  %cmp29 = icmp ugt i64 %31, %32, !dbg !3768
  br i1 %cmp29, label %if.then39, label %lor.lhs.false31, !dbg !3769

lor.lhs.false31:                                  ; preds = %while.end
  %33 = load i64, i64* %line_length, align 8, !dbg !3770
  %cmp32 = icmp ult i64 %33, 1, !dbg !3772
  br i1 %cmp32, label %if.then39, label %lor.lhs.false34, !dbg !3773

lor.lhs.false34:                                  ; preds = %lor.lhs.false31
  %34 = load i64, i64* %line_length, align 8, !dbg !3774
  %sub35 = sub i64 %34, 1, !dbg !3775
  %35 = load i8*, i8** %attr, align 8, !dbg !3776
  %arrayidx = getelementptr inbounds i8, i8* %35, i64 %sub35, !dbg !3776
  %36 = load i8, i8* %arrayidx, align 1, !dbg !3776
  %conv36 = sext i8 %36 to i32, !dbg !3776
  %cmp37 = icmp ne i32 %conv36, 10, !dbg !3777
  br i1 %cmp37, label %if.then39, label %if.end41, !dbg !3778

if.then39:                                        ; preds = %lor.lhs.false34, %lor.lhs.false31, %while.end
  %37 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3779
  %archive40 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %37, i32 0, i32 0, !dbg !3781
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive40, i32 -1, i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.39, i32 0, i32 0)), !dbg !3782
  store i32 -20, i32* %retval, align 4, !dbg !3783
  br label %return, !dbg !3783

if.end41:                                         ; preds = %lor.lhs.false34
  %38 = load i64, i64* %line_length, align 8, !dbg !3784
  %sub42 = sub i64 %38, 1, !dbg !3785
  %39 = load i8*, i8** %attr, align 8, !dbg !3786
  %arrayidx43 = getelementptr inbounds i8, i8* %39, i64 %sub42, !dbg !3786
  store i8 0, i8* %arrayidx43, align 1, !dbg !3787
  %40 = load i8*, i8** %p, align 8, !dbg !3788
  store i8* %40, i8** %key, align 8, !dbg !3789
  %41 = load i8*, i8** %key, align 8, !dbg !3790
  %arrayidx44 = getelementptr inbounds i8, i8* %41, i64 0, !dbg !3790
  %42 = load i8, i8* %arrayidx44, align 1, !dbg !3790
  %conv45 = sext i8 %42 to i32, !dbg !3790
  %cmp46 = icmp eq i32 %conv45, 61, !dbg !3792
  br i1 %cmp46, label %if.then48, label %if.end49, !dbg !3793

if.then48:                                        ; preds = %if.end41
  store i32 -1, i32* %retval, align 4, !dbg !3794
  br label %return, !dbg !3794

if.end49:                                         ; preds = %if.end41
  br label %while.cond50, !dbg !3795

while.cond50:                                     ; preds = %while.body55, %if.end49
  %43 = load i8*, i8** %p, align 8, !dbg !3796
  %44 = load i8, i8* %43, align 1, !dbg !3797
  %conv51 = sext i8 %44 to i32, !dbg !3797
  %tobool = icmp ne i32 %conv51, 0, !dbg !3797
  br i1 %tobool, label %land.rhs, label %land.end, !dbg !3798

land.rhs:                                         ; preds = %while.cond50
  %45 = load i8*, i8** %p, align 8, !dbg !3799
  %46 = load i8, i8* %45, align 1, !dbg !3800
  %conv52 = sext i8 %46 to i32, !dbg !3800
  %cmp53 = icmp ne i32 %conv52, 61, !dbg !3801
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond50
  %47 = phi i1 [ false, %while.cond50 ], [ %cmp53, %land.rhs ]
  br i1 %47, label %while.body55, label %while.end57, !dbg !3802

while.body55:                                     ; preds = %land.end
  %48 = load i8*, i8** %p, align 8, !dbg !3804
  %incdec.ptr56 = getelementptr inbounds i8, i8* %48, i32 1, !dbg !3804
  store i8* %incdec.ptr56, i8** %p, align 8, !dbg !3804
  br label %while.cond50, !dbg !3805

while.end57:                                      ; preds = %land.end
  %49 = load i8*, i8** %p, align 8, !dbg !3807
  %50 = load i8, i8* %49, align 1, !dbg !3809
  %conv58 = sext i8 %50 to i32, !dbg !3809
  %cmp59 = icmp eq i32 %conv58, 0, !dbg !3810
  br i1 %cmp59, label %if.then61, label %if.end63, !dbg !3811

if.then61:                                        ; preds = %while.end57
  %51 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3812
  %archive62 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %51, i32 0, i32 0, !dbg !3814
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive62, i32 -1, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.40, i32 0, i32 0)), !dbg !3815
  store i32 -20, i32* %retval, align 4, !dbg !3816
  br label %return, !dbg !3816

if.end63:                                         ; preds = %while.end57
  %52 = load i8*, i8** %p, align 8, !dbg !3817
  store i8 0, i8* %52, align 1, !dbg !3818
  %53 = load i8*, i8** %p, align 8, !dbg !3819
  %add.ptr = getelementptr inbounds i8, i8* %53, i64 1, !dbg !3820
  store i8* %add.ptr, i8** %value, align 8, !dbg !3821
  %54 = load i8*, i8** %attr, align 8, !dbg !3822
  %55 = load i64, i64* %line_length, align 8, !dbg !3823
  %add.ptr64 = getelementptr inbounds i8, i8* %54, i64 %55, !dbg !3824
  %add.ptr65 = getelementptr inbounds i8, i8* %add.ptr64, i64 -1, !dbg !3825
  %56 = load i8*, i8** %value, align 8, !dbg !3826
  %sub.ptr.lhs.cast = ptrtoint i8* %add.ptr65 to i64, !dbg !3827
  %sub.ptr.rhs.cast = ptrtoint i8* %56 to i64, !dbg !3827
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !3827
  store i64 %sub.ptr.sub, i64* %value_length, align 8, !dbg !3828
  %57 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3829
  %58 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3830
  %59 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3831
  %60 = load i8*, i8** %key, align 8, !dbg !3832
  %61 = load i8*, i8** %value, align 8, !dbg !3833
  %62 = load i64, i64* %value_length, align 8, !dbg !3834
  %call = call i32 @pax_attribute(%struct.archive_read* %57, %struct.tar* %58, %struct.archive_entry* %59, i8* %60, i8* %61, i64 %62), !dbg !3835
  store i32 %call, i32* %err2, align 4, !dbg !3836
  %63 = load i32, i32* %err2, align 4, !dbg !3837
  %cmp66 = icmp eq i32 %63, -30, !dbg !3839
  br i1 %cmp66, label %if.then68, label %if.end69, !dbg !3840

if.then68:                                        ; preds = %if.end63
  %64 = load i32, i32* %err2, align 4, !dbg !3841
  store i32 %64, i32* %retval, align 4, !dbg !3842
  br label %return, !dbg !3842

if.end69:                                         ; preds = %if.end63
  %65 = load i32, i32* %err, align 4, !dbg !3843
  %66 = load i32, i32* %err2, align 4, !dbg !3843
  %cmp70 = icmp slt i32 %65, %66, !dbg !3843
  br i1 %cmp70, label %cond.true, label %cond.false, !dbg !3843

cond.true:                                        ; preds = %if.end69
  %67 = load i32, i32* %err, align 4, !dbg !3844
  br label %cond.end, !dbg !3844

cond.false:                                       ; preds = %if.end69
  %68 = load i32, i32* %err2, align 4, !dbg !3845
  br label %cond.end, !dbg !3845

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ %67, %cond.true ], [ %68, %cond.false ], !dbg !3846
  store i32 %cond, i32* %err, align 4, !dbg !3847
  %69 = load i64, i64* %line_length, align 8, !dbg !3848
  %70 = load i8*, i8** %attr, align 8, !dbg !3849
  %add.ptr72 = getelementptr inbounds i8, i8* %70, i64 %69, !dbg !3849
  store i8* %add.ptr72, i8** %attr, align 8, !dbg !3849
  %71 = load i64, i64* %line_length, align 8, !dbg !3850
  %72 = load i64, i64* %attr_length, align 8, !dbg !3851
  %sub73 = sub i64 %72, %71, !dbg !3851
  store i64 %sub73, i64* %attr_length, align 8, !dbg !3851
  br label %while.cond, !dbg !3852

while.end74:                                      ; preds = %while.cond
  %73 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3854
  %pax_hdrcharset_binary75 = getelementptr inbounds %struct.tar, %struct.tar* %73, i32 0, i32 11, !dbg !3856
  %74 = load i32, i32* %pax_hdrcharset_binary75, align 8, !dbg !3856
  %tobool76 = icmp ne i32 %74, 0, !dbg !3854
  br i1 %tobool76, label %if.then77, label %if.else, !dbg !3857

if.then77:                                        ; preds = %while.end74
  %75 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3858
  %opt_sconv = getelementptr inbounds %struct.tar, %struct.tar* %75, i32 0, i32 27, !dbg !3859
  %76 = load %struct.archive_string_conv*, %struct.archive_string_conv** %opt_sconv, align 8, !dbg !3859
  store %struct.archive_string_conv* %76, %struct.archive_string_conv** %sconv, align 8, !dbg !3860
  br label %if.end87, !dbg !3861

if.else:                                          ; preds = %while.end74
  %77 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3862
  %archive78 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %77, i32 0, i32 0, !dbg !3864
  %call79 = call %struct.archive_string_conv* @archive_string_conversion_from_charset(%struct.archive* %archive78, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.29, i32 0, i32 0), i32 1), !dbg !3865
  store %struct.archive_string_conv* %call79, %struct.archive_string_conv** %sconv, align 8, !dbg !3866
  %78 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !3867
  %cmp80 = icmp eq %struct.archive_string_conv* %78, null, !dbg !3869
  br i1 %cmp80, label %if.then82, label %if.end83, !dbg !3870

if.then82:                                        ; preds = %if.else
  store i32 -30, i32* %retval, align 4, !dbg !3871
  br label %return, !dbg !3871

if.end83:                                         ; preds = %if.else
  %79 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3872
  %compat_2x = getelementptr inbounds %struct.tar, %struct.tar* %79, i32 0, i32 32, !dbg !3874
  %80 = load i32, i32* %compat_2x, align 4, !dbg !3874
  %tobool84 = icmp ne i32 %80, 0, !dbg !3872
  br i1 %tobool84, label %if.then85, label %if.end86, !dbg !3875

if.then85:                                        ; preds = %if.end83
  %81 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !3876
  call void @archive_string_conversion_set_opt(%struct.archive_string_conv* %81, i32 1), !dbg !3877
  br label %if.end86, !dbg !3877

if.end86:                                         ; preds = %if.then85, %if.end83
  br label %if.end87

if.end87:                                         ; preds = %if.end86, %if.then77
  %82 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3878
  %entry_gname88 = getelementptr inbounds %struct.tar, %struct.tar* %82, i32 0, i32 5, !dbg !3878
  %length89 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %entry_gname88, i32 0, i32 1, !dbg !3878
  %83 = load i64, i64* %length89, align 8, !dbg !3878
  %cmp90 = icmp ugt i64 %83, 0, !dbg !3880
  br i1 %cmp90, label %if.then92, label %if.end109, !dbg !3881

if.then92:                                        ; preds = %if.end87
  %84 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3882
  %85 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3885
  %entry_gname93 = getelementptr inbounds %struct.tar, %struct.tar* %85, i32 0, i32 5, !dbg !3886
  %s94 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %entry_gname93, i32 0, i32 0, !dbg !3887
  %86 = load i8*, i8** %s94, align 8, !dbg !3887
  %87 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3888
  %entry_gname95 = getelementptr inbounds %struct.tar, %struct.tar* %87, i32 0, i32 5, !dbg !3888
  %length96 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %entry_gname95, i32 0, i32 1, !dbg !3888
  %88 = load i64, i64* %length96, align 8, !dbg !3888
  %89 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !3889
  %call97 = call i32 @_archive_entry_copy_gname_l(%struct.archive_entry* %84, i8* %86, i64 %88, %struct.archive_string_conv* %89), !dbg !3890
  %cmp98 = icmp ne i32 %call97, 0, !dbg !3891
  br i1 %cmp98, label %if.then100, label %if.end108, !dbg !3892

if.then100:                                       ; preds = %if.then92
  %90 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3893
  %91 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !3895
  %call101 = call i32 @set_conversion_failed_error(%struct.archive_read* %90, %struct.archive_string_conv* %91, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.41, i32 0, i32 0)), !dbg !3896
  store i32 %call101, i32* %err, align 4, !dbg !3897
  %92 = load i32, i32* %err, align 4, !dbg !3898
  %cmp102 = icmp eq i32 %92, -30, !dbg !3900
  br i1 %cmp102, label %if.then104, label %if.end105, !dbg !3901

if.then104:                                       ; preds = %if.then100
  %93 = load i32, i32* %err, align 4, !dbg !3902
  store i32 %93, i32* %retval, align 4, !dbg !3903
  br label %return, !dbg !3903

if.end105:                                        ; preds = %if.then100
  %94 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3904
  %95 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3905
  %entry_gname106 = getelementptr inbounds %struct.tar, %struct.tar* %95, i32 0, i32 5, !dbg !3906
  %s107 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %entry_gname106, i32 0, i32 0, !dbg !3907
  %96 = load i8*, i8** %s107, align 8, !dbg !3907
  call void @archive_entry_copy_gname(%struct.archive_entry* %94, i8* %96), !dbg !3908
  br label %if.end108, !dbg !3909

if.end108:                                        ; preds = %if.end105, %if.then92
  br label %if.end109, !dbg !3910

if.end109:                                        ; preds = %if.end108, %if.end87
  %97 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3911
  %entry_linkpath110 = getelementptr inbounds %struct.tar, %struct.tar* %97, i32 0, i32 3, !dbg !3911
  %length111 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %entry_linkpath110, i32 0, i32 1, !dbg !3911
  %98 = load i64, i64* %length111, align 8, !dbg !3911
  %cmp112 = icmp ugt i64 %98, 0, !dbg !3913
  br i1 %cmp112, label %if.then114, label %if.end131, !dbg !3914

if.then114:                                       ; preds = %if.end109
  %99 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3915
  %100 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3918
  %entry_linkpath115 = getelementptr inbounds %struct.tar, %struct.tar* %100, i32 0, i32 3, !dbg !3919
  %s116 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %entry_linkpath115, i32 0, i32 0, !dbg !3920
  %101 = load i8*, i8** %s116, align 8, !dbg !3920
  %102 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3921
  %entry_linkpath117 = getelementptr inbounds %struct.tar, %struct.tar* %102, i32 0, i32 3, !dbg !3921
  %length118 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %entry_linkpath117, i32 0, i32 1, !dbg !3921
  %103 = load i64, i64* %length118, align 8, !dbg !3921
  %104 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !3922
  %call119 = call i32 @_archive_entry_copy_link_l(%struct.archive_entry* %99, i8* %101, i64 %103, %struct.archive_string_conv* %104), !dbg !3923
  %cmp120 = icmp ne i32 %call119, 0, !dbg !3924
  br i1 %cmp120, label %if.then122, label %if.end130, !dbg !3925

if.then122:                                       ; preds = %if.then114
  %105 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3926
  %106 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !3928
  %call123 = call i32 @set_conversion_failed_error(%struct.archive_read* %105, %struct.archive_string_conv* %106, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.42, i32 0, i32 0)), !dbg !3929
  store i32 %call123, i32* %err, align 4, !dbg !3930
  %107 = load i32, i32* %err, align 4, !dbg !3931
  %cmp124 = icmp eq i32 %107, -30, !dbg !3933
  br i1 %cmp124, label %if.then126, label %if.end127, !dbg !3934

if.then126:                                       ; preds = %if.then122
  %108 = load i32, i32* %err, align 4, !dbg !3935
  store i32 %108, i32* %retval, align 4, !dbg !3936
  br label %return, !dbg !3936

if.end127:                                        ; preds = %if.then122
  %109 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3937
  %110 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3938
  %entry_linkpath128 = getelementptr inbounds %struct.tar, %struct.tar* %110, i32 0, i32 3, !dbg !3939
  %s129 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %entry_linkpath128, i32 0, i32 0, !dbg !3940
  %111 = load i8*, i8** %s129, align 8, !dbg !3940
  call void @archive_entry_copy_link(%struct.archive_entry* %109, i8* %111), !dbg !3941
  br label %if.end130, !dbg !3942

if.end130:                                        ; preds = %if.end127, %if.then114
  br label %if.end131, !dbg !3943

if.end131:                                        ; preds = %if.end130, %if.end109
  store %struct.archive_string* null, %struct.archive_string** %as, align 8, !dbg !3944
  %112 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3945
  %entry_pathname_override132 = getelementptr inbounds %struct.tar, %struct.tar* %112, i32 0, i32 2, !dbg !3945
  %length133 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %entry_pathname_override132, i32 0, i32 1, !dbg !3945
  %113 = load i64, i64* %length133, align 8, !dbg !3945
  %cmp134 = icmp ugt i64 %113, 0, !dbg !3947
  br i1 %cmp134, label %if.then136, label %if.else138, !dbg !3948

if.then136:                                       ; preds = %if.end131
  %114 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3949
  %entry_pathname_override137 = getelementptr inbounds %struct.tar, %struct.tar* %114, i32 0, i32 2, !dbg !3950
  store %struct.archive_string* %entry_pathname_override137, %struct.archive_string** %as, align 8, !dbg !3951
  br label %if.end146, !dbg !3952

if.else138:                                       ; preds = %if.end131
  %115 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3953
  %entry_pathname139 = getelementptr inbounds %struct.tar, %struct.tar* %115, i32 0, i32 1, !dbg !3953
  %length140 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %entry_pathname139, i32 0, i32 1, !dbg !3953
  %116 = load i64, i64* %length140, align 8, !dbg !3953
  %cmp141 = icmp ugt i64 %116, 0, !dbg !3955
  br i1 %cmp141, label %if.then143, label %if.end145, !dbg !3956

if.then143:                                       ; preds = %if.else138
  %117 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3957
  %entry_pathname144 = getelementptr inbounds %struct.tar, %struct.tar* %117, i32 0, i32 1, !dbg !3958
  store %struct.archive_string* %entry_pathname144, %struct.archive_string** %as, align 8, !dbg !3959
  br label %if.end145, !dbg !3960

if.end145:                                        ; preds = %if.then143, %if.else138
  br label %if.end146

if.end146:                                        ; preds = %if.end145, %if.then136
  %118 = load %struct.archive_string*, %struct.archive_string** %as, align 8, !dbg !3961
  %cmp147 = icmp ne %struct.archive_string* %118, null, !dbg !3963
  br i1 %cmp147, label %if.then149, label %if.end163, !dbg !3964

if.then149:                                       ; preds = %if.end146
  %119 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3965
  %120 = load %struct.archive_string*, %struct.archive_string** %as, align 8, !dbg !3968
  %s150 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %120, i32 0, i32 0, !dbg !3969
  %121 = load i8*, i8** %s150, align 8, !dbg !3969
  %122 = load %struct.archive_string*, %struct.archive_string** %as, align 8, !dbg !3970
  %length151 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %122, i32 0, i32 1, !dbg !3970
  %123 = load i64, i64* %length151, align 8, !dbg !3970
  %124 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !3971
  %call152 = call i32 @_archive_entry_copy_pathname_l(%struct.archive_entry* %119, i8* %121, i64 %123, %struct.archive_string_conv* %124), !dbg !3972
  %cmp153 = icmp ne i32 %call152, 0, !dbg !3973
  br i1 %cmp153, label %if.then155, label %if.end162, !dbg !3974

if.then155:                                       ; preds = %if.then149
  %125 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3975
  %126 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !3977
  %call156 = call i32 @set_conversion_failed_error(%struct.archive_read* %125, %struct.archive_string_conv* %126, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.34, i32 0, i32 0)), !dbg !3978
  store i32 %call156, i32* %err, align 4, !dbg !3979
  %127 = load i32, i32* %err, align 4, !dbg !3980
  %cmp157 = icmp eq i32 %127, -30, !dbg !3982
  br i1 %cmp157, label %if.then159, label %if.end160, !dbg !3983

if.then159:                                       ; preds = %if.then155
  %128 = load i32, i32* %err, align 4, !dbg !3984
  store i32 %128, i32* %retval, align 4, !dbg !3985
  br label %return, !dbg !3985

if.end160:                                        ; preds = %if.then155
  %129 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3986
  %130 = load %struct.archive_string*, %struct.archive_string** %as, align 8, !dbg !3987
  %s161 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %130, i32 0, i32 0, !dbg !3988
  %131 = load i8*, i8** %s161, align 8, !dbg !3988
  call void @archive_entry_copy_pathname(%struct.archive_entry* %129, i8* %131), !dbg !3989
  br label %if.end162, !dbg !3990

if.end162:                                        ; preds = %if.end160, %if.then149
  br label %if.end163, !dbg !3991

if.end163:                                        ; preds = %if.end162, %if.end146
  %132 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3992
  %entry_uname164 = getelementptr inbounds %struct.tar, %struct.tar* %132, i32 0, i32 4, !dbg !3992
  %length165 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %entry_uname164, i32 0, i32 1, !dbg !3992
  %133 = load i64, i64* %length165, align 8, !dbg !3992
  %cmp166 = icmp ugt i64 %133, 0, !dbg !3994
  br i1 %cmp166, label %if.then168, label %if.end185, !dbg !3995

if.then168:                                       ; preds = %if.end163
  %134 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3996
  %135 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !3999
  %entry_uname169 = getelementptr inbounds %struct.tar, %struct.tar* %135, i32 0, i32 4, !dbg !4000
  %s170 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %entry_uname169, i32 0, i32 0, !dbg !4001
  %136 = load i8*, i8** %s170, align 8, !dbg !4001
  %137 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4002
  %entry_uname171 = getelementptr inbounds %struct.tar, %struct.tar* %137, i32 0, i32 4, !dbg !4002
  %length172 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %entry_uname171, i32 0, i32 1, !dbg !4002
  %138 = load i64, i64* %length172, align 8, !dbg !4002
  %139 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !4003
  %call173 = call i32 @_archive_entry_copy_uname_l(%struct.archive_entry* %134, i8* %136, i64 %138, %struct.archive_string_conv* %139), !dbg !4004
  %cmp174 = icmp ne i32 %call173, 0, !dbg !4005
  br i1 %cmp174, label %if.then176, label %if.end184, !dbg !4006

if.then176:                                       ; preds = %if.then168
  %140 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !4007
  %141 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !4009
  %call177 = call i32 @set_conversion_failed_error(%struct.archive_read* %140, %struct.archive_string_conv* %141, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.43, i32 0, i32 0)), !dbg !4010
  store i32 %call177, i32* %err, align 4, !dbg !4011
  %142 = load i32, i32* %err, align 4, !dbg !4012
  %cmp178 = icmp eq i32 %142, -30, !dbg !4014
  br i1 %cmp178, label %if.then180, label %if.end181, !dbg !4015

if.then180:                                       ; preds = %if.then176
  %143 = load i32, i32* %err, align 4, !dbg !4016
  store i32 %143, i32* %retval, align 4, !dbg !4017
  br label %return, !dbg !4017

if.end181:                                        ; preds = %if.then176
  %144 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4018
  %145 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4019
  %entry_uname182 = getelementptr inbounds %struct.tar, %struct.tar* %145, i32 0, i32 4, !dbg !4020
  %s183 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %entry_uname182, i32 0, i32 0, !dbg !4021
  %146 = load i8*, i8** %s183, align 8, !dbg !4021
  call void @archive_entry_copy_uname(%struct.archive_entry* %144, i8* %146), !dbg !4022
  br label %if.end184, !dbg !4023

if.end184:                                        ; preds = %if.end181, %if.then168
  br label %if.end185, !dbg !4024

if.end185:                                        ; preds = %if.end184, %if.end163
  %147 = load i32, i32* %err, align 4, !dbg !4025
  store i32 %147, i32* %retval, align 4, !dbg !4026
  br label %return, !dbg !4026

return:                                           ; preds = %if.end185, %if.then180, %if.then159, %if.then126, %if.then104, %if.then82, %if.then68, %if.then61, %if.then48, %if.then39, %if.then24, %if.then18
  %148 = load i32, i32* %retval, align 4, !dbg !4027
  ret i32 %148, !dbg !4027
}

; Function Attrs: nounwind uwtable
define internal i32 @pax_attribute(%struct.archive_read* %a, %struct.tar* %tar, %struct.archive_entry* %entry1, i8* %key, i8* %value, i64 %value_length) #0 !dbg !486 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %tar.addr = alloca %struct.tar*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %key.addr = alloca i8*, align 8
  %value.addr = alloca i8*, align 8
  %value_length.addr = alloca i64, align 8
  %s = alloca i64, align 8
  %n = alloca i64, align 8
  %err = alloca i32, align 4
  %r = alloca i32, align 4
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !4028, metadata !563), !dbg !4029
  store %struct.tar* %tar, %struct.tar** %tar.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tar** %tar.addr, metadata !4030, metadata !563), !dbg !4031
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !4032, metadata !563), !dbg !4033
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !4034, metadata !563), !dbg !4035
  store i8* %value, i8** %value.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %value.addr, metadata !4036, metadata !563), !dbg !4037
  store i64 %value_length, i64* %value_length.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %value_length.addr, metadata !4038, metadata !563), !dbg !4039
  call void @llvm.dbg.declare(metadata i64* %s, metadata !4040, metadata !563), !dbg !4041
  call void @llvm.dbg.declare(metadata i64* %n, metadata !4042, metadata !563), !dbg !4043
  call void @llvm.dbg.declare(metadata i32* %err, metadata !4044, metadata !563), !dbg !4045
  store i32 0, i32* %err, align 4, !dbg !4045
  call void @llvm.dbg.declare(metadata i32* %r, metadata !4046, metadata !563), !dbg !4047
  %0 = load i8*, i8** %value.addr, align 8, !dbg !4048
  %cmp = icmp eq i8* %0, null, !dbg !4050
  br i1 %cmp, label %if.then, label %if.end, !dbg !4051

if.then:                                          ; preds = %entry
  store i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.44, i32 0, i32 0), i8** %value.addr, align 8, !dbg !4052
  br label %if.end, !dbg !4053

if.end:                                           ; preds = %if.then, %entry
  %1 = load i8*, i8** %key.addr, align 8, !dbg !4054
  %arrayidx = getelementptr inbounds i8, i8* %1, i64 0, !dbg !4054
  %2 = load i8, i8* %arrayidx, align 1, !dbg !4054
  %conv = sext i8 %2 to i32, !dbg !4054
  switch i32 %conv, label %sw.epilog [
    i32 71, label %sw.bb
    i32 76, label %sw.bb113
    i32 83, label %sw.bb125
    i32 97, label %sw.bb238
    i32 99, label %sw.bb244
    i32 103, label %sw.bb262
    i32 104, label %sw.bb286
    i32 108, label %sw.bb304
    i32 109, label %sw.bb320
    i32 112, label %sw.bb326
    i32 114, label %sw.bb342
    i32 115, label %sw.bb343
    i32 117, label %sw.bb359
  ], !dbg !4055

sw.bb:                                            ; preds = %if.end
  %3 = load i8*, i8** %key.addr, align 8, !dbg !4056
  %call = call i32 @strncmp(i8* %3, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.45, i32 0, i32 0), i64 10) #8, !dbg !4059
  %cmp2 = icmp eq i32 %call, 0, !dbg !4060
  br i1 %cmp2, label %land.lhs.true, label %if.end5, !dbg !4061

land.lhs.true:                                    ; preds = %sw.bb
  %4 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4062
  %sparse_allowed = getelementptr inbounds %struct.tar, %struct.tar* %4, i32 0, i32 18, !dbg !4063
  %5 = load i32, i32* %sparse_allowed, align 8, !dbg !4063
  %tobool = icmp ne i32 %5, 0, !dbg !4062
  br i1 %tobool, label %if.end5, label %if.then4, !dbg !4064

if.then4:                                         ; preds = %land.lhs.true
  %6 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !4066
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %6, i32 0, i32 0, !dbg !4068
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 -1, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.46, i32 0, i32 0)), !dbg !4069
  store i32 -30, i32* %retval, align 4, !dbg !4070
  br label %return, !dbg !4070

if.end5:                                          ; preds = %land.lhs.true, %sw.bb
  %7 = load i8*, i8** %key.addr, align 8, !dbg !4071
  %call6 = call i32 @strcmp(i8* %7, i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.47, i32 0, i32 0)) #8, !dbg !4073
  %cmp7 = icmp eq i32 %call6, 0, !dbg !4074
  br i1 %cmp7, label %if.then9, label %if.end10, !dbg !4075

if.then9:                                         ; preds = %if.end5
  %8 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4076
  %sparse_offset = getelementptr inbounds %struct.tar, %struct.tar* %8, i32 0, i32 21, !dbg !4078
  store i64 -1, i64* %sparse_offset, align 8, !dbg !4079
  %9 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4080
  %sparse_numbytes = getelementptr inbounds %struct.tar, %struct.tar* %9, i32 0, i32 22, !dbg !4081
  store i64 -1, i64* %sparse_numbytes, align 8, !dbg !4082
  %10 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4083
  %sparse_gnu_major = getelementptr inbounds %struct.tar, %struct.tar* %10, i32 0, i32 23, !dbg !4084
  store i32 0, i32* %sparse_gnu_major, align 8, !dbg !4085
  %11 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4086
  %sparse_gnu_minor = getelementptr inbounds %struct.tar, %struct.tar* %11, i32 0, i32 24, !dbg !4087
  store i32 0, i32* %sparse_gnu_minor, align 4, !dbg !4088
  br label %if.end10, !dbg !4089

if.end10:                                         ; preds = %if.then9, %if.end5
  %12 = load i8*, i8** %key.addr, align 8, !dbg !4090
  %call11 = call i32 @strcmp(i8* %12, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.48, i32 0, i32 0)) #8, !dbg !4092
  %cmp12 = icmp eq i32 %call11, 0, !dbg !4093
  br i1 %cmp12, label %if.then14, label %if.end32, !dbg !4094

if.then14:                                        ; preds = %if.end10
  %13 = load i8*, i8** %value.addr, align 8, !dbg !4095
  %14 = load i8*, i8** %value.addr, align 8, !dbg !4097
  %call15 = call i64 @strlen(i8* %14) #8, !dbg !4098
  %call16 = call i64 @tar_atol10(i8* %13, i64 %call15), !dbg !4099
  %15 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4101
  %sparse_offset17 = getelementptr inbounds %struct.tar, %struct.tar* %15, i32 0, i32 21, !dbg !4102
  store i64 %call16, i64* %sparse_offset17, align 8, !dbg !4103
  %16 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4104
  %sparse_numbytes18 = getelementptr inbounds %struct.tar, %struct.tar* %16, i32 0, i32 22, !dbg !4106
  %17 = load i64, i64* %sparse_numbytes18, align 8, !dbg !4106
  %cmp19 = icmp ne i64 %17, -1, !dbg !4107
  br i1 %cmp19, label %if.then21, label %if.end31, !dbg !4108

if.then21:                                        ; preds = %if.then14
  %18 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !4109
  %19 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4112
  %20 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4113
  %sparse_offset22 = getelementptr inbounds %struct.tar, %struct.tar* %20, i32 0, i32 21, !dbg !4114
  %21 = load i64, i64* %sparse_offset22, align 8, !dbg !4114
  %22 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4115
  %sparse_numbytes23 = getelementptr inbounds %struct.tar, %struct.tar* %22, i32 0, i32 22, !dbg !4116
  %23 = load i64, i64* %sparse_numbytes23, align 8, !dbg !4116
  %call24 = call i32 @gnu_add_sparse_entry(%struct.archive_read* %18, %struct.tar* %19, i64 %21, i64 %23), !dbg !4117
  %cmp25 = icmp ne i32 %call24, 0, !dbg !4118
  br i1 %cmp25, label %if.then27, label %if.end28, !dbg !4119

if.then27:                                        ; preds = %if.then21
  store i32 -30, i32* %retval, align 4, !dbg !4120
  br label %return, !dbg !4120

if.end28:                                         ; preds = %if.then21
  %24 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4121
  %sparse_offset29 = getelementptr inbounds %struct.tar, %struct.tar* %24, i32 0, i32 21, !dbg !4122
  store i64 -1, i64* %sparse_offset29, align 8, !dbg !4123
  %25 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4124
  %sparse_numbytes30 = getelementptr inbounds %struct.tar, %struct.tar* %25, i32 0, i32 22, !dbg !4125
  store i64 -1, i64* %sparse_numbytes30, align 8, !dbg !4126
  br label %if.end31, !dbg !4127

if.end31:                                         ; preds = %if.end28, %if.then14
  br label %if.end32, !dbg !4128

if.end32:                                         ; preds = %if.end31, %if.end10
  %26 = load i8*, i8** %key.addr, align 8, !dbg !4129
  %call33 = call i32 @strcmp(i8* %26, i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.49, i32 0, i32 0)) #8, !dbg !4131
  %cmp34 = icmp eq i32 %call33, 0, !dbg !4132
  br i1 %cmp34, label %if.then36, label %if.end54, !dbg !4133

if.then36:                                        ; preds = %if.end32
  %27 = load i8*, i8** %value.addr, align 8, !dbg !4134
  %28 = load i8*, i8** %value.addr, align 8, !dbg !4136
  %call37 = call i64 @strlen(i8* %28) #8, !dbg !4137
  %call38 = call i64 @tar_atol10(i8* %27, i64 %call37), !dbg !4138
  %29 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4140
  %sparse_numbytes39 = getelementptr inbounds %struct.tar, %struct.tar* %29, i32 0, i32 22, !dbg !4141
  store i64 %call38, i64* %sparse_numbytes39, align 8, !dbg !4142
  %30 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4143
  %sparse_numbytes40 = getelementptr inbounds %struct.tar, %struct.tar* %30, i32 0, i32 22, !dbg !4145
  %31 = load i64, i64* %sparse_numbytes40, align 8, !dbg !4145
  %cmp41 = icmp ne i64 %31, -1, !dbg !4146
  br i1 %cmp41, label %if.then43, label %if.end53, !dbg !4147

if.then43:                                        ; preds = %if.then36
  %32 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !4148
  %33 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4151
  %34 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4152
  %sparse_offset44 = getelementptr inbounds %struct.tar, %struct.tar* %34, i32 0, i32 21, !dbg !4153
  %35 = load i64, i64* %sparse_offset44, align 8, !dbg !4153
  %36 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4154
  %sparse_numbytes45 = getelementptr inbounds %struct.tar, %struct.tar* %36, i32 0, i32 22, !dbg !4155
  %37 = load i64, i64* %sparse_numbytes45, align 8, !dbg !4155
  %call46 = call i32 @gnu_add_sparse_entry(%struct.archive_read* %32, %struct.tar* %33, i64 %35, i64 %37), !dbg !4156
  %cmp47 = icmp ne i32 %call46, 0, !dbg !4157
  br i1 %cmp47, label %if.then49, label %if.end50, !dbg !4158

if.then49:                                        ; preds = %if.then43
  store i32 -30, i32* %retval, align 4, !dbg !4159
  br label %return, !dbg !4159

if.end50:                                         ; preds = %if.then43
  %38 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4160
  %sparse_offset51 = getelementptr inbounds %struct.tar, %struct.tar* %38, i32 0, i32 21, !dbg !4161
  store i64 -1, i64* %sparse_offset51, align 8, !dbg !4162
  %39 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4163
  %sparse_numbytes52 = getelementptr inbounds %struct.tar, %struct.tar* %39, i32 0, i32 22, !dbg !4164
  store i64 -1, i64* %sparse_numbytes52, align 8, !dbg !4165
  br label %if.end53, !dbg !4166

if.end53:                                         ; preds = %if.end50, %if.then36
  br label %if.end54, !dbg !4167

if.end54:                                         ; preds = %if.end53, %if.end32
  %40 = load i8*, i8** %key.addr, align 8, !dbg !4168
  %call55 = call i32 @strcmp(i8* %40, i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.50, i32 0, i32 0)) #8, !dbg !4170
  %cmp56 = icmp eq i32 %call55, 0, !dbg !4171
  br i1 %cmp56, label %if.then58, label %if.end62, !dbg !4172

if.then58:                                        ; preds = %if.end54
  %41 = load i8*, i8** %value.addr, align 8, !dbg !4173
  %42 = load i8*, i8** %value.addr, align 8, !dbg !4175
  %call59 = call i64 @strlen(i8* %42) #8, !dbg !4176
  %call60 = call i64 @tar_atol10(i8* %41, i64 %call59), !dbg !4177
  %43 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4179
  %realsize = getelementptr inbounds %struct.tar, %struct.tar* %43, i32 0, i32 17, !dbg !4180
  store i64 %call60, i64* %realsize, align 8, !dbg !4181
  %44 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4182
  %45 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4183
  %realsize61 = getelementptr inbounds %struct.tar, %struct.tar* %45, i32 0, i32 17, !dbg !4184
  %46 = load i64, i64* %realsize61, align 8, !dbg !4184
  call void @archive_entry_set_size(%struct.archive_entry* %44, i64 %46), !dbg !4185
  br label %if.end62, !dbg !4186

if.end62:                                         ; preds = %if.then58, %if.end54
  %47 = load i8*, i8** %key.addr, align 8, !dbg !4187
  %call63 = call i32 @strcmp(i8* %47, i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.51, i32 0, i32 0)) #8, !dbg !4189
  %cmp64 = icmp eq i32 %call63, 0, !dbg !4190
  br i1 %cmp64, label %if.then66, label %if.end74, !dbg !4191

if.then66:                                        ; preds = %if.end62
  %48 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4192
  %sparse_gnu_major67 = getelementptr inbounds %struct.tar, %struct.tar* %48, i32 0, i32 23, !dbg !4194
  store i32 0, i32* %sparse_gnu_major67, align 8, !dbg !4195
  %49 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4196
  %sparse_gnu_minor68 = getelementptr inbounds %struct.tar, %struct.tar* %49, i32 0, i32 24, !dbg !4197
  store i32 1, i32* %sparse_gnu_minor68, align 4, !dbg !4198
  %50 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !4199
  %51 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4201
  %52 = load i8*, i8** %value.addr, align 8, !dbg !4202
  %call69 = call i32 @gnu_sparse_01_parse(%struct.archive_read* %50, %struct.tar* %51, i8* %52), !dbg !4203
  %cmp70 = icmp ne i32 %call69, 0, !dbg !4204
  br i1 %cmp70, label %if.then72, label %if.end73, !dbg !4205

if.then72:                                        ; preds = %if.then66
  store i32 -20, i32* %retval, align 4, !dbg !4206
  br label %return, !dbg !4206

if.end73:                                         ; preds = %if.then66
  br label %if.end74, !dbg !4207

if.end74:                                         ; preds = %if.end73, %if.end62
  %53 = load i8*, i8** %key.addr, align 8, !dbg !4208
  %call75 = call i32 @strcmp(i8* %53, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.52, i32 0, i32 0)) #8, !dbg !4210
  %cmp76 = icmp eq i32 %call75, 0, !dbg !4211
  br i1 %cmp76, label %if.then78, label %if.end83, !dbg !4212

if.then78:                                        ; preds = %if.end74
  %54 = load i8*, i8** %value.addr, align 8, !dbg !4213
  %55 = load i8*, i8** %value.addr, align 8, !dbg !4215
  %call79 = call i64 @strlen(i8* %55) #8, !dbg !4216
  %call80 = call i64 @tar_atol10(i8* %54, i64 %call79), !dbg !4217
  %conv81 = trunc i64 %call80 to i32, !dbg !4219
  %56 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4220
  %sparse_gnu_major82 = getelementptr inbounds %struct.tar, %struct.tar* %56, i32 0, i32 23, !dbg !4221
  store i32 %conv81, i32* %sparse_gnu_major82, align 8, !dbg !4222
  %57 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4223
  %sparse_gnu_pending = getelementptr inbounds %struct.tar, %struct.tar* %57, i32 0, i32 25, !dbg !4224
  store i8 1, i8* %sparse_gnu_pending, align 8, !dbg !4225
  br label %if.end83, !dbg !4226

if.end83:                                         ; preds = %if.then78, %if.end74
  %58 = load i8*, i8** %key.addr, align 8, !dbg !4227
  %call84 = call i32 @strcmp(i8* %58, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.53, i32 0, i32 0)) #8, !dbg !4229
  %cmp85 = icmp eq i32 %call84, 0, !dbg !4230
  br i1 %cmp85, label %if.then87, label %if.end93, !dbg !4231

if.then87:                                        ; preds = %if.end83
  %59 = load i8*, i8** %value.addr, align 8, !dbg !4232
  %60 = load i8*, i8** %value.addr, align 8, !dbg !4234
  %call88 = call i64 @strlen(i8* %60) #8, !dbg !4235
  %call89 = call i64 @tar_atol10(i8* %59, i64 %call88), !dbg !4236
  %conv90 = trunc i64 %call89 to i32, !dbg !4238
  %61 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4239
  %sparse_gnu_minor91 = getelementptr inbounds %struct.tar, %struct.tar* %61, i32 0, i32 24, !dbg !4240
  store i32 %conv90, i32* %sparse_gnu_minor91, align 4, !dbg !4241
  %62 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4242
  %sparse_gnu_pending92 = getelementptr inbounds %struct.tar, %struct.tar* %62, i32 0, i32 25, !dbg !4243
  store i8 1, i8* %sparse_gnu_pending92, align 8, !dbg !4244
  br label %if.end93, !dbg !4245

if.end93:                                         ; preds = %if.then87, %if.end83
  %63 = load i8*, i8** %key.addr, align 8, !dbg !4246
  %call94 = call i32 @strcmp(i8* %63, i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.54, i32 0, i32 0)) #8, !dbg !4248
  %cmp95 = icmp eq i32 %call94, 0, !dbg !4249
  br i1 %cmp95, label %if.then97, label %if.end103, !dbg !4250

if.then97:                                        ; preds = %if.end93
  %64 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4251
  %entry_pathname_override = getelementptr inbounds %struct.tar, %struct.tar* %64, i32 0, i32 2, !dbg !4251
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %entry_pathname_override, i32 0, i32 1, !dbg !4251
  store i64 0, i64* %length, align 8, !dbg !4251
  %65 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4251
  %entry_pathname_override98 = getelementptr inbounds %struct.tar, %struct.tar* %65, i32 0, i32 2, !dbg !4251
  %66 = load i8*, i8** %value.addr, align 8, !dbg !4251
  %67 = load i8*, i8** %value.addr, align 8, !dbg !4251
  %cmp99 = icmp eq i8* %67, null, !dbg !4251
  br i1 %cmp99, label %cond.true, label %cond.false, !dbg !4251

cond.true:                                        ; preds = %if.then97
  br label %cond.end, !dbg !4253

cond.false:                                       ; preds = %if.then97
  %68 = load i8*, i8** %value.addr, align 8, !dbg !4255
  %call101 = call i64 @strlen(i8* %68) #8, !dbg !4255
  br label %cond.end, !dbg !4255

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ 0, %cond.true ], [ %call101, %cond.false ], !dbg !4257
  %call102 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %entry_pathname_override98, i8* %66, i64 %cond), !dbg !4257
  br label %if.end103, !dbg !4259

if.end103:                                        ; preds = %cond.end, %if.end93
  %69 = load i8*, i8** %key.addr, align 8, !dbg !4260
  %call104 = call i32 @strcmp(i8* %69, i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.55, i32 0, i32 0)) #8, !dbg !4262
  %cmp105 = icmp eq i32 %call104, 0, !dbg !4263
  br i1 %cmp105, label %if.then107, label %if.end112, !dbg !4264

if.then107:                                       ; preds = %if.end103
  %70 = load i8*, i8** %value.addr, align 8, !dbg !4265
  %71 = load i8*, i8** %value.addr, align 8, !dbg !4267
  %call108 = call i64 @strlen(i8* %71) #8, !dbg !4268
  %call109 = call i64 @tar_atol10(i8* %70, i64 %call108), !dbg !4269
  %72 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4271
  %realsize110 = getelementptr inbounds %struct.tar, %struct.tar* %72, i32 0, i32 17, !dbg !4272
  store i64 %call109, i64* %realsize110, align 8, !dbg !4273
  %73 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4274
  %74 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4275
  %realsize111 = getelementptr inbounds %struct.tar, %struct.tar* %74, i32 0, i32 17, !dbg !4276
  %75 = load i64, i64* %realsize111, align 8, !dbg !4276
  call void @archive_entry_set_size(%struct.archive_entry* %73, i64 %75), !dbg !4277
  br label %if.end112, !dbg !4278

if.end112:                                        ; preds = %if.then107, %if.end103
  br label %sw.epilog, !dbg !4279

sw.bb113:                                         ; preds = %if.end
  %76 = load i8*, i8** %key.addr, align 8, !dbg !4280
  %call114 = call i32 @strcmp(i8* %76, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.56, i32 0, i32 0)) #8, !dbg !4282
  %cmp115 = icmp eq i32 %call114, 0, !dbg !4283
  br i1 %cmp115, label %if.then117, label %if.end118, !dbg !4284

if.then117:                                       ; preds = %sw.bb113
  %77 = load i8*, i8** %value.addr, align 8, !dbg !4285
  call void @pax_time(i8* %77, i64* %s, i64* %n), !dbg !4287
  %78 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4288
  %79 = load i64, i64* %s, align 8, !dbg !4289
  %80 = load i64, i64* %n, align 8, !dbg !4290
  call void @archive_entry_set_birthtime(%struct.archive_entry* %78, i64 %79, i64 %80), !dbg !4291
  br label %if.end118, !dbg !4292

if.end118:                                        ; preds = %if.then117, %sw.bb113
  %81 = load i8*, i8** %key.addr, align 8, !dbg !4293
  %call119 = call i32 @memcmp(i8* %81, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.57, i32 0, i32 0), i64 17) #8, !dbg !4295
  %cmp120 = icmp eq i32 %call119, 0, !dbg !4296
  br i1 %cmp120, label %if.then122, label %if.end124, !dbg !4297

if.then122:                                       ; preds = %if.end118
  %82 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4298
  %83 = load i8*, i8** %key.addr, align 8, !dbg !4299
  %84 = load i8*, i8** %value.addr, align 8, !dbg !4300
  %call123 = call i32 @pax_attribute_xattr(%struct.archive_entry* %82, i8* %83, i8* %84), !dbg !4301
  br label %if.end124, !dbg !4301

if.end124:                                        ; preds = %if.then122, %if.end118
  br label %sw.epilog, !dbg !4302

sw.bb125:                                         ; preds = %if.end
  %85 = load i8*, i8** %key.addr, align 8, !dbg !4303
  %call126 = call i32 @strcmp(i8* %85, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.58, i32 0, i32 0)) #8, !dbg !4305
  %cmp127 = icmp eq i32 %call126, 0, !dbg !4306
  br i1 %cmp127, label %if.then129, label %if.else, !dbg !4307

if.then129:                                       ; preds = %sw.bb125
  %86 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !4308
  %87 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4310
  %88 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4311
  %89 = load i8*, i8** %value.addr, align 8, !dbg !4312
  %call130 = call i32 @pax_attribute_acl(%struct.archive_read* %86, %struct.tar* %87, %struct.archive_entry* %88, i8* %89, i32 256), !dbg !4313
  store i32 %call130, i32* %r, align 4, !dbg !4314
  %90 = load i32, i32* %r, align 4, !dbg !4315
  %cmp131 = icmp eq i32 %90, -30, !dbg !4317
  br i1 %cmp131, label %if.then133, label %if.end134, !dbg !4318

if.then133:                                       ; preds = %if.then129
  %91 = load i32, i32* %r, align 4, !dbg !4319
  store i32 %91, i32* %retval, align 4, !dbg !4320
  br label %return, !dbg !4320

if.end134:                                        ; preds = %if.then129
  br label %if.end237, !dbg !4321

if.else:                                          ; preds = %sw.bb125
  %92 = load i8*, i8** %key.addr, align 8, !dbg !4322
  %call135 = call i32 @strcmp(i8* %92, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.59, i32 0, i32 0)) #8, !dbg !4325
  %cmp136 = icmp eq i32 %call135, 0, !dbg !4326
  br i1 %cmp136, label %if.then138, label %if.else144, !dbg !4325

if.then138:                                       ; preds = %if.else
  %93 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !4327
  %94 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4329
  %95 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4330
  %96 = load i8*, i8** %value.addr, align 8, !dbg !4331
  %call139 = call i32 @pax_attribute_acl(%struct.archive_read* %93, %struct.tar* %94, %struct.archive_entry* %95, i8* %96, i32 512), !dbg !4332
  store i32 %call139, i32* %r, align 4, !dbg !4333
  %97 = load i32, i32* %r, align 4, !dbg !4334
  %cmp140 = icmp eq i32 %97, -30, !dbg !4336
  br i1 %cmp140, label %if.then142, label %if.end143, !dbg !4337

if.then142:                                       ; preds = %if.then138
  %98 = load i32, i32* %r, align 4, !dbg !4338
  store i32 %98, i32* %retval, align 4, !dbg !4339
  br label %return, !dbg !4339

if.end143:                                        ; preds = %if.then138
  br label %if.end236, !dbg !4340

if.else144:                                       ; preds = %if.else
  %99 = load i8*, i8** %key.addr, align 8, !dbg !4341
  %call145 = call i32 @strcmp(i8* %99, i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.60, i32 0, i32 0)) #8, !dbg !4344
  %cmp146 = icmp eq i32 %call145, 0, !dbg !4345
  br i1 %cmp146, label %if.then148, label %if.else154, !dbg !4344

if.then148:                                       ; preds = %if.else144
  %100 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !4346
  %101 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4348
  %102 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4349
  %103 = load i8*, i8** %value.addr, align 8, !dbg !4350
  %call149 = call i32 @pax_attribute_acl(%struct.archive_read* %100, %struct.tar* %101, %struct.archive_entry* %102, i8* %103, i32 15360), !dbg !4351
  store i32 %call149, i32* %r, align 4, !dbg !4352
  %104 = load i32, i32* %r, align 4, !dbg !4353
  %cmp150 = icmp eq i32 %104, -30, !dbg !4355
  br i1 %cmp150, label %if.then152, label %if.end153, !dbg !4356

if.then152:                                       ; preds = %if.then148
  %105 = load i32, i32* %r, align 4, !dbg !4357
  store i32 %105, i32* %retval, align 4, !dbg !4358
  br label %return, !dbg !4358

if.end153:                                        ; preds = %if.then148
  br label %if.end235, !dbg !4359

if.else154:                                       ; preds = %if.else144
  %106 = load i8*, i8** %key.addr, align 8, !dbg !4360
  %call155 = call i32 @strcmp(i8* %106, i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.61, i32 0, i32 0)) #8, !dbg !4363
  %cmp156 = icmp eq i32 %call155, 0, !dbg !4364
  br i1 %cmp156, label %if.then158, label %if.else161, !dbg !4363

if.then158:                                       ; preds = %if.else154
  %107 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4365
  %108 = load i8*, i8** %value.addr, align 8, !dbg !4367
  %109 = load i8*, i8** %value.addr, align 8, !dbg !4368
  %call159 = call i64 @strlen(i8* %109) #8, !dbg !4369
  %call160 = call i64 @tar_atol10(i8* %108, i64 %call159), !dbg !4370
  call void @archive_entry_set_rdevmajor(%struct.archive_entry* %107, i64 %call160), !dbg !4372
  br label %if.end234, !dbg !4373

if.else161:                                       ; preds = %if.else154
  %110 = load i8*, i8** %key.addr, align 8, !dbg !4374
  %call162 = call i32 @strcmp(i8* %110, i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.62, i32 0, i32 0)) #8, !dbg !4377
  %cmp163 = icmp eq i32 %call162, 0, !dbg !4378
  br i1 %cmp163, label %if.then165, label %if.else168, !dbg !4377

if.then165:                                       ; preds = %if.else161
  %111 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4379
  %112 = load i8*, i8** %value.addr, align 8, !dbg !4381
  %113 = load i8*, i8** %value.addr, align 8, !dbg !4382
  %call166 = call i64 @strlen(i8* %113) #8, !dbg !4383
  %call167 = call i64 @tar_atol10(i8* %112, i64 %call166), !dbg !4384
  call void @archive_entry_set_rdevminor(%struct.archive_entry* %111, i64 %call167), !dbg !4386
  br label %if.end233, !dbg !4387

if.else168:                                       ; preds = %if.else161
  %114 = load i8*, i8** %key.addr, align 8, !dbg !4388
  %call169 = call i32 @strcmp(i8* %114, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.63, i32 0, i32 0)) #8, !dbg !4391
  %cmp170 = icmp eq i32 %call169, 0, !dbg !4392
  br i1 %cmp170, label %if.then172, label %if.else174, !dbg !4391

if.then172:                                       ; preds = %if.else168
  %115 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4393
  %116 = load i8*, i8** %value.addr, align 8, !dbg !4395
  %call173 = call i8* @archive_entry_copy_fflags_text(%struct.archive_entry* %115, i8* %116), !dbg !4396
  br label %if.end232, !dbg !4397

if.else174:                                       ; preds = %if.else168
  %117 = load i8*, i8** %key.addr, align 8, !dbg !4398
  %call175 = call i32 @strcmp(i8* %117, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.64, i32 0, i32 0)) #8, !dbg !4401
  %cmp176 = icmp eq i32 %call175, 0, !dbg !4402
  br i1 %cmp176, label %if.then178, label %if.else181, !dbg !4401

if.then178:                                       ; preds = %if.else174
  %118 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4403
  %119 = load i8*, i8** %value.addr, align 8, !dbg !4405
  %120 = load i8*, i8** %value.addr, align 8, !dbg !4406
  %call179 = call i64 @strlen(i8* %120) #8, !dbg !4407
  %call180 = call i64 @tar_atol10(i8* %119, i64 %call179), !dbg !4408
  call void @archive_entry_set_dev(%struct.archive_entry* %118, i64 %call180), !dbg !4410
  br label %if.end231, !dbg !4411

if.else181:                                       ; preds = %if.else174
  %121 = load i8*, i8** %key.addr, align 8, !dbg !4412
  %call182 = call i32 @strcmp(i8* %121, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.65, i32 0, i32 0)) #8, !dbg !4415
  %cmp183 = icmp eq i32 %call182, 0, !dbg !4416
  br i1 %cmp183, label %if.then185, label %if.else188, !dbg !4415

if.then185:                                       ; preds = %if.else181
  %122 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4417
  %123 = load i8*, i8** %value.addr, align 8, !dbg !4419
  %124 = load i8*, i8** %value.addr, align 8, !dbg !4420
  %call186 = call i64 @strlen(i8* %124) #8, !dbg !4421
  %call187 = call i64 @tar_atol10(i8* %123, i64 %call186), !dbg !4422
  call void @archive_entry_set_ino(%struct.archive_entry* %122, i64 %call187), !dbg !4424
  br label %if.end230, !dbg !4425

if.else188:                                       ; preds = %if.else181
  %125 = load i8*, i8** %key.addr, align 8, !dbg !4426
  %call189 = call i32 @strcmp(i8* %125, i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.66, i32 0, i32 0)) #8, !dbg !4429
  %cmp190 = icmp eq i32 %call189, 0, !dbg !4430
  br i1 %cmp190, label %if.then192, label %if.else196, !dbg !4429

if.then192:                                       ; preds = %if.else188
  %126 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4431
  %127 = load i8*, i8** %value.addr, align 8, !dbg !4433
  %128 = load i8*, i8** %value.addr, align 8, !dbg !4434
  %call193 = call i64 @strlen(i8* %128) #8, !dbg !4435
  %call194 = call i64 @tar_atol10(i8* %127, i64 %call193), !dbg !4436
  %conv195 = trunc i64 %call194 to i32, !dbg !4438
  call void @archive_entry_set_nlink(%struct.archive_entry* %126, i32 %conv195), !dbg !4439
  br label %if.end229, !dbg !4440

if.else196:                                       ; preds = %if.else188
  %129 = load i8*, i8** %key.addr, align 8, !dbg !4441
  %call197 = call i32 @strcmp(i8* %129, i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.67, i32 0, i32 0)) #8, !dbg !4444
  %cmp198 = icmp eq i32 %call197, 0, !dbg !4445
  br i1 %cmp198, label %if.then200, label %if.else205, !dbg !4444

if.then200:                                       ; preds = %if.else196
  %130 = load i8*, i8** %value.addr, align 8, !dbg !4446
  %131 = load i8*, i8** %value.addr, align 8, !dbg !4448
  %call201 = call i64 @strlen(i8* %131) #8, !dbg !4449
  %call202 = call i64 @tar_atol10(i8* %130, i64 %call201), !dbg !4450
  %132 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4452
  %realsize203 = getelementptr inbounds %struct.tar, %struct.tar* %132, i32 0, i32 17, !dbg !4453
  store i64 %call202, i64* %realsize203, align 8, !dbg !4454
  %133 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4455
  %134 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4456
  %realsize204 = getelementptr inbounds %struct.tar, %struct.tar* %134, i32 0, i32 17, !dbg !4457
  %135 = load i64, i64* %realsize204, align 8, !dbg !4457
  call void @archive_entry_set_size(%struct.archive_entry* %133, i64 %135), !dbg !4458
  br label %if.end228, !dbg !4459

if.else205:                                       ; preds = %if.else196
  %136 = load i8*, i8** %key.addr, align 8, !dbg !4460
  %call206 = call i32 @strncmp(i8* %136, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.68, i32 0, i32 0), i64 13) #8, !dbg !4463
  %cmp207 = icmp eq i32 %call206, 0, !dbg !4464
  br i1 %cmp207, label %if.then209, label %if.else211, !dbg !4463

if.then209:                                       ; preds = %if.else205
  %137 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4465
  %138 = load i8*, i8** %key.addr, align 8, !dbg !4467
  %139 = load i8*, i8** %value.addr, align 8, !dbg !4468
  %140 = load i64, i64* %value_length.addr, align 8, !dbg !4469
  %call210 = call i32 @pax_attribute_schily_xattr(%struct.archive_entry* %137, i8* %138, i8* %139, i64 %140), !dbg !4470
  br label %if.end227, !dbg !4471

if.else211:                                       ; preds = %if.else205
  %141 = load i8*, i8** %key.addr, align 8, !dbg !4472
  %call212 = call i32 @strcmp(i8* %141, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.69, i32 0, i32 0)) #8, !dbg !4475
  %cmp213 = icmp eq i32 %call212, 0, !dbg !4476
  br i1 %cmp213, label %if.then215, label %if.end226, !dbg !4475

if.then215:                                       ; preds = %if.else211
  %142 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !4477
  %143 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4479
  %144 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4480
  %145 = load i8*, i8** %value.addr, align 8, !dbg !4481
  %call216 = call i32 @solaris_sparse_parse(%struct.archive_read* %142, %struct.tar* %143, %struct.archive_entry* %144, i8* %145), !dbg !4482
  store i32 %call216, i32* %r, align 4, !dbg !4483
  %146 = load i32, i32* %r, align 4, !dbg !4484
  %147 = load i32, i32* %err, align 4, !dbg !4486
  %cmp217 = icmp slt i32 %146, %147, !dbg !4487
  br i1 %cmp217, label %if.then219, label %if.end225, !dbg !4488

if.then219:                                       ; preds = %if.then215
  %148 = load i32, i32* %r, align 4, !dbg !4489
  %cmp220 = icmp eq i32 %148, -30, !dbg !4492
  br i1 %cmp220, label %if.then222, label %if.end223, !dbg !4493

if.then222:                                       ; preds = %if.then219
  %149 = load i32, i32* %r, align 4, !dbg !4494
  store i32 %149, i32* %retval, align 4, !dbg !4495
  br label %return, !dbg !4495

if.end223:                                        ; preds = %if.then219
  %150 = load i32, i32* %r, align 4, !dbg !4496
  store i32 %150, i32* %err, align 4, !dbg !4497
  %151 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !4498
  %archive224 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %151, i32 0, i32 0, !dbg !4499
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive224, i32 -1, i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.70, i32 0, i32 0)), !dbg !4500
  br label %if.end225, !dbg !4501

if.end225:                                        ; preds = %if.end223, %if.then215
  br label %if.end226, !dbg !4502

if.end226:                                        ; preds = %if.end225, %if.else211
  br label %if.end227

if.end227:                                        ; preds = %if.end226, %if.then209
  br label %if.end228

if.end228:                                        ; preds = %if.end227, %if.then200
  br label %if.end229

if.end229:                                        ; preds = %if.end228, %if.then192
  br label %if.end230

if.end230:                                        ; preds = %if.end229, %if.then185
  br label %if.end231

if.end231:                                        ; preds = %if.end230, %if.then178
  br label %if.end232

if.end232:                                        ; preds = %if.end231, %if.then172
  br label %if.end233

if.end233:                                        ; preds = %if.end232, %if.then165
  br label %if.end234

if.end234:                                        ; preds = %if.end233, %if.then158
  br label %if.end235

if.end235:                                        ; preds = %if.end234, %if.end153
  br label %if.end236

if.end236:                                        ; preds = %if.end235, %if.end143
  br label %if.end237

if.end237:                                        ; preds = %if.end236, %if.end134
  br label %sw.epilog, !dbg !4503

sw.bb238:                                         ; preds = %if.end
  %152 = load i8*, i8** %key.addr, align 8, !dbg !4504
  %call239 = call i32 @strcmp(i8* %152, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.71, i32 0, i32 0)) #8, !dbg !4506
  %cmp240 = icmp eq i32 %call239, 0, !dbg !4507
  br i1 %cmp240, label %if.then242, label %if.end243, !dbg !4508

if.then242:                                       ; preds = %sw.bb238
  %153 = load i8*, i8** %value.addr, align 8, !dbg !4509
  call void @pax_time(i8* %153, i64* %s, i64* %n), !dbg !4511
  %154 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4512
  %155 = load i64, i64* %s, align 8, !dbg !4513
  %156 = load i64, i64* %n, align 8, !dbg !4514
  call void @archive_entry_set_atime(%struct.archive_entry* %154, i64 %155, i64 %156), !dbg !4515
  br label %if.end243, !dbg !4516

if.end243:                                        ; preds = %if.then242, %sw.bb238
  br label %sw.epilog, !dbg !4517

sw.bb244:                                         ; preds = %if.end
  %157 = load i8*, i8** %key.addr, align 8, !dbg !4518
  %call245 = call i32 @strcmp(i8* %157, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.72, i32 0, i32 0)) #8, !dbg !4520
  %cmp246 = icmp eq i32 %call245, 0, !dbg !4521
  br i1 %cmp246, label %if.then248, label %if.else249, !dbg !4522

if.then248:                                       ; preds = %sw.bb244
  %158 = load i8*, i8** %value.addr, align 8, !dbg !4523
  call void @pax_time(i8* %158, i64* %s, i64* %n), !dbg !4525
  %159 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4526
  %160 = load i64, i64* %s, align 8, !dbg !4527
  %161 = load i64, i64* %n, align 8, !dbg !4528
  call void @archive_entry_set_ctime(%struct.archive_entry* %159, i64 %160, i64 %161), !dbg !4529
  br label %if.end261, !dbg !4530

if.else249:                                       ; preds = %sw.bb244
  %162 = load i8*, i8** %key.addr, align 8, !dbg !4531
  %call250 = call i32 @strcmp(i8* %162, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.73, i32 0, i32 0)) #8, !dbg !4534
  %cmp251 = icmp eq i32 %call250, 0, !dbg !4535
  br i1 %cmp251, label %if.then253, label %if.else254, !dbg !4534

if.then253:                                       ; preds = %if.else249
  br label %if.end260, !dbg !4536

if.else254:                                       ; preds = %if.else249
  %163 = load i8*, i8** %key.addr, align 8, !dbg !4538
  %call255 = call i32 @strcmp(i8* %163, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.74, i32 0, i32 0)) #8, !dbg !4541
  %cmp256 = icmp eq i32 %call255, 0, !dbg !4542
  br i1 %cmp256, label %if.then258, label %if.end259, !dbg !4541

if.then258:                                       ; preds = %if.else254
  br label %if.end259, !dbg !4543

if.end259:                                        ; preds = %if.then258, %if.else254
  br label %if.end260

if.end260:                                        ; preds = %if.end259, %if.then253
  br label %if.end261

if.end261:                                        ; preds = %if.end260, %if.then248
  br label %sw.epilog, !dbg !4545

sw.bb262:                                         ; preds = %if.end
  %164 = load i8*, i8** %key.addr, align 8, !dbg !4546
  %call263 = call i32 @strcmp(i8* %164, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.75, i32 0, i32 0)) #8, !dbg !4548
  %cmp264 = icmp eq i32 %call263, 0, !dbg !4549
  br i1 %cmp264, label %if.then266, label %if.else269, !dbg !4550

if.then266:                                       ; preds = %sw.bb262
  %165 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4551
  %166 = load i8*, i8** %value.addr, align 8, !dbg !4553
  %167 = load i8*, i8** %value.addr, align 8, !dbg !4554
  %call267 = call i64 @strlen(i8* %167) #8, !dbg !4555
  %call268 = call i64 @tar_atol10(i8* %166, i64 %call267), !dbg !4556
  call void @archive_entry_set_gid(%struct.archive_entry* %165, i64 %call268), !dbg !4558
  br label %if.end285, !dbg !4559

if.else269:                                       ; preds = %sw.bb262
  %168 = load i8*, i8** %key.addr, align 8, !dbg !4560
  %call270 = call i32 @strcmp(i8* %168, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.76, i32 0, i32 0)) #8, !dbg !4563
  %cmp271 = icmp eq i32 %call270, 0, !dbg !4564
  br i1 %cmp271, label %if.then273, label %if.end284, !dbg !4563

if.then273:                                       ; preds = %if.else269
  %169 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4565
  %entry_gname = getelementptr inbounds %struct.tar, %struct.tar* %169, i32 0, i32 5, !dbg !4565
  %length274 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %entry_gname, i32 0, i32 1, !dbg !4565
  store i64 0, i64* %length274, align 8, !dbg !4565
  %170 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4565
  %entry_gname275 = getelementptr inbounds %struct.tar, %struct.tar* %170, i32 0, i32 5, !dbg !4565
  %171 = load i8*, i8** %value.addr, align 8, !dbg !4565
  %172 = load i8*, i8** %value.addr, align 8, !dbg !4565
  %cmp276 = icmp eq i8* %172, null, !dbg !4565
  br i1 %cmp276, label %cond.true278, label %cond.false279, !dbg !4565

cond.true278:                                     ; preds = %if.then273
  br label %cond.end281, !dbg !4567

cond.false279:                                    ; preds = %if.then273
  %173 = load i8*, i8** %value.addr, align 8, !dbg !4569
  %call280 = call i64 @strlen(i8* %173) #8, !dbg !4569
  br label %cond.end281, !dbg !4569

cond.end281:                                      ; preds = %cond.false279, %cond.true278
  %cond282 = phi i64 [ 0, %cond.true278 ], [ %call280, %cond.false279 ], !dbg !4571
  %call283 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %entry_gname275, i8* %171, i64 %cond282), !dbg !4571
  br label %if.end284, !dbg !4573

if.end284:                                        ; preds = %cond.end281, %if.else269
  br label %if.end285

if.end285:                                        ; preds = %if.end284, %if.then266
  br label %sw.epilog, !dbg !4574

sw.bb286:                                         ; preds = %if.end
  %174 = load i8*, i8** %key.addr, align 8, !dbg !4575
  %call287 = call i32 @strcmp(i8* %174, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.9, i32 0, i32 0)) #8, !dbg !4577
  %cmp288 = icmp eq i32 %call287, 0, !dbg !4578
  br i1 %cmp288, label %if.then290, label %if.end303, !dbg !4579

if.then290:                                       ; preds = %sw.bb286
  %175 = load i8*, i8** %value.addr, align 8, !dbg !4580
  %call291 = call i32 @strcmp(i8* %175, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.77, i32 0, i32 0)) #8, !dbg !4583
  %cmp292 = icmp eq i32 %call291, 0, !dbg !4584
  br i1 %cmp292, label %if.then294, label %if.else295, !dbg !4585

if.then294:                                       ; preds = %if.then290
  %176 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4586
  %pax_hdrcharset_binary = getelementptr inbounds %struct.tar, %struct.tar* %176, i32 0, i32 11, !dbg !4587
  store i32 1, i32* %pax_hdrcharset_binary, align 8, !dbg !4588
  br label %if.end302, !dbg !4586

if.else295:                                       ; preds = %if.then290
  %177 = load i8*, i8** %value.addr, align 8, !dbg !4589
  %call296 = call i32 @strcmp(i8* %177, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.78, i32 0, i32 0)) #8, !dbg !4591
  %cmp297 = icmp eq i32 %call296, 0, !dbg !4592
  br i1 %cmp297, label %if.then299, label %if.end301, !dbg !4593

if.then299:                                       ; preds = %if.else295
  %178 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4594
  %pax_hdrcharset_binary300 = getelementptr inbounds %struct.tar, %struct.tar* %178, i32 0, i32 11, !dbg !4595
  store i32 0, i32* %pax_hdrcharset_binary300, align 8, !dbg !4596
  br label %if.end301, !dbg !4594

if.end301:                                        ; preds = %if.then299, %if.else295
  br label %if.end302

if.end302:                                        ; preds = %if.end301, %if.then294
  br label %if.end303, !dbg !4597

if.end303:                                        ; preds = %if.end302, %sw.bb286
  br label %sw.epilog, !dbg !4598

sw.bb304:                                         ; preds = %if.end
  %179 = load i8*, i8** %key.addr, align 8, !dbg !4599
  %call305 = call i32 @strcmp(i8* %179, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.79, i32 0, i32 0)) #8, !dbg !4601
  %cmp306 = icmp eq i32 %call305, 0, !dbg !4602
  br i1 %cmp306, label %if.then308, label %if.end319, !dbg !4603

if.then308:                                       ; preds = %sw.bb304
  %180 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4604
  %entry_linkpath = getelementptr inbounds %struct.tar, %struct.tar* %180, i32 0, i32 3, !dbg !4604
  %length309 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %entry_linkpath, i32 0, i32 1, !dbg !4604
  store i64 0, i64* %length309, align 8, !dbg !4604
  %181 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4604
  %entry_linkpath310 = getelementptr inbounds %struct.tar, %struct.tar* %181, i32 0, i32 3, !dbg !4604
  %182 = load i8*, i8** %value.addr, align 8, !dbg !4604
  %183 = load i8*, i8** %value.addr, align 8, !dbg !4604
  %cmp311 = icmp eq i8* %183, null, !dbg !4604
  br i1 %cmp311, label %cond.true313, label %cond.false314, !dbg !4604

cond.true313:                                     ; preds = %if.then308
  br label %cond.end316, !dbg !4606

cond.false314:                                    ; preds = %if.then308
  %184 = load i8*, i8** %value.addr, align 8, !dbg !4608
  %call315 = call i64 @strlen(i8* %184) #8, !dbg !4608
  br label %cond.end316, !dbg !4608

cond.end316:                                      ; preds = %cond.false314, %cond.true313
  %cond317 = phi i64 [ 0, %cond.true313 ], [ %call315, %cond.false314 ], !dbg !4610
  %call318 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %entry_linkpath310, i8* %182, i64 %cond317), !dbg !4610
  br label %if.end319, !dbg !4612

if.end319:                                        ; preds = %cond.end316, %sw.bb304
  br label %sw.epilog, !dbg !4613

sw.bb320:                                         ; preds = %if.end
  %185 = load i8*, i8** %key.addr, align 8, !dbg !4614
  %call321 = call i32 @strcmp(i8* %185, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.80, i32 0, i32 0)) #8, !dbg !4616
  %cmp322 = icmp eq i32 %call321, 0, !dbg !4617
  br i1 %cmp322, label %if.then324, label %if.end325, !dbg !4618

if.then324:                                       ; preds = %sw.bb320
  %186 = load i8*, i8** %value.addr, align 8, !dbg !4619
  call void @pax_time(i8* %186, i64* %s, i64* %n), !dbg !4621
  %187 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4622
  %188 = load i64, i64* %s, align 8, !dbg !4623
  %189 = load i64, i64* %n, align 8, !dbg !4624
  call void @archive_entry_set_mtime(%struct.archive_entry* %187, i64 %188, i64 %189), !dbg !4625
  br label %if.end325, !dbg !4626

if.end325:                                        ; preds = %if.then324, %sw.bb320
  br label %sw.epilog, !dbg !4627

sw.bb326:                                         ; preds = %if.end
  %190 = load i8*, i8** %key.addr, align 8, !dbg !4628
  %call327 = call i32 @strcmp(i8* %190, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.81, i32 0, i32 0)) #8, !dbg !4630
  %cmp328 = icmp eq i32 %call327, 0, !dbg !4631
  br i1 %cmp328, label %if.then330, label %if.end341, !dbg !4632

if.then330:                                       ; preds = %sw.bb326
  %191 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4633
  %entry_pathname = getelementptr inbounds %struct.tar, %struct.tar* %191, i32 0, i32 1, !dbg !4633
  %length331 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %entry_pathname, i32 0, i32 1, !dbg !4633
  store i64 0, i64* %length331, align 8, !dbg !4633
  %192 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4633
  %entry_pathname332 = getelementptr inbounds %struct.tar, %struct.tar* %192, i32 0, i32 1, !dbg !4633
  %193 = load i8*, i8** %value.addr, align 8, !dbg !4633
  %194 = load i8*, i8** %value.addr, align 8, !dbg !4633
  %cmp333 = icmp eq i8* %194, null, !dbg !4633
  br i1 %cmp333, label %cond.true335, label %cond.false336, !dbg !4633

cond.true335:                                     ; preds = %if.then330
  br label %cond.end338, !dbg !4635

cond.false336:                                    ; preds = %if.then330
  %195 = load i8*, i8** %value.addr, align 8, !dbg !4637
  %call337 = call i64 @strlen(i8* %195) #8, !dbg !4637
  br label %cond.end338, !dbg !4637

cond.end338:                                      ; preds = %cond.false336, %cond.true335
  %cond339 = phi i64 [ 0, %cond.true335 ], [ %call337, %cond.false336 ], !dbg !4639
  %call340 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %entry_pathname332, i8* %193, i64 %cond339), !dbg !4639
  br label %if.end341, !dbg !4641

if.end341:                                        ; preds = %cond.end338, %sw.bb326
  br label %sw.epilog, !dbg !4642

sw.bb342:                                         ; preds = %if.end
  br label %sw.epilog, !dbg !4643

sw.bb343:                                         ; preds = %if.end
  %196 = load i8*, i8** %key.addr, align 8, !dbg !4644
  %call344 = call i32 @strcmp(i8* %196, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.82, i32 0, i32 0)) #8, !dbg !4646
  %cmp345 = icmp eq i32 %call344, 0, !dbg !4647
  br i1 %cmp345, label %if.then347, label %if.end358, !dbg !4648

if.then347:                                       ; preds = %sw.bb343
  %197 = load i8*, i8** %value.addr, align 8, !dbg !4649
  %198 = load i8*, i8** %value.addr, align 8, !dbg !4651
  %call348 = call i64 @strlen(i8* %198) #8, !dbg !4652
  %call349 = call i64 @tar_atol10(i8* %197, i64 %call348), !dbg !4653
  %199 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4655
  %entry_bytes_remaining = getelementptr inbounds %struct.tar, %struct.tar* %199, i32 0, i32 13, !dbg !4656
  store i64 %call349, i64* %entry_bytes_remaining, align 8, !dbg !4657
  %200 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4658
  %realsize350 = getelementptr inbounds %struct.tar, %struct.tar* %200, i32 0, i32 17, !dbg !4660
  %201 = load i64, i64* %realsize350, align 8, !dbg !4660
  %cmp351 = icmp slt i64 %201, 0, !dbg !4661
  br i1 %cmp351, label %if.then353, label %if.end357, !dbg !4662

if.then353:                                       ; preds = %if.then347
  %202 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4663
  %203 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4665
  %entry_bytes_remaining354 = getelementptr inbounds %struct.tar, %struct.tar* %203, i32 0, i32 13, !dbg !4666
  %204 = load i64, i64* %entry_bytes_remaining354, align 8, !dbg !4666
  call void @archive_entry_set_size(%struct.archive_entry* %202, i64 %204), !dbg !4667
  %205 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4668
  %entry_bytes_remaining355 = getelementptr inbounds %struct.tar, %struct.tar* %205, i32 0, i32 13, !dbg !4669
  %206 = load i64, i64* %entry_bytes_remaining355, align 8, !dbg !4669
  %207 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4670
  %realsize356 = getelementptr inbounds %struct.tar, %struct.tar* %207, i32 0, i32 17, !dbg !4671
  store i64 %206, i64* %realsize356, align 8, !dbg !4672
  br label %if.end357, !dbg !4673

if.end357:                                        ; preds = %if.then353, %if.then347
  br label %if.end358, !dbg !4674

if.end358:                                        ; preds = %if.end357, %sw.bb343
  br label %sw.epilog, !dbg !4675

sw.bb359:                                         ; preds = %if.end
  %208 = load i8*, i8** %key.addr, align 8, !dbg !4676
  %call360 = call i32 @strcmp(i8* %208, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.83, i32 0, i32 0)) #8, !dbg !4678
  %cmp361 = icmp eq i32 %call360, 0, !dbg !4679
  br i1 %cmp361, label %if.then363, label %if.else366, !dbg !4680

if.then363:                                       ; preds = %sw.bb359
  %209 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4681
  %210 = load i8*, i8** %value.addr, align 8, !dbg !4683
  %211 = load i8*, i8** %value.addr, align 8, !dbg !4684
  %call364 = call i64 @strlen(i8* %211) #8, !dbg !4685
  %call365 = call i64 @tar_atol10(i8* %210, i64 %call364), !dbg !4686
  call void @archive_entry_set_uid(%struct.archive_entry* %209, i64 %call365), !dbg !4688
  br label %if.end382, !dbg !4689

if.else366:                                       ; preds = %sw.bb359
  %212 = load i8*, i8** %key.addr, align 8, !dbg !4690
  %call367 = call i32 @strcmp(i8* %212, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.84, i32 0, i32 0)) #8, !dbg !4693
  %cmp368 = icmp eq i32 %call367, 0, !dbg !4694
  br i1 %cmp368, label %if.then370, label %if.end381, !dbg !4693

if.then370:                                       ; preds = %if.else366
  %213 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4695
  %entry_uname = getelementptr inbounds %struct.tar, %struct.tar* %213, i32 0, i32 4, !dbg !4695
  %length371 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %entry_uname, i32 0, i32 1, !dbg !4695
  store i64 0, i64* %length371, align 8, !dbg !4695
  %214 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4695
  %entry_uname372 = getelementptr inbounds %struct.tar, %struct.tar* %214, i32 0, i32 4, !dbg !4695
  %215 = load i8*, i8** %value.addr, align 8, !dbg !4695
  %216 = load i8*, i8** %value.addr, align 8, !dbg !4695
  %cmp373 = icmp eq i8* %216, null, !dbg !4695
  br i1 %cmp373, label %cond.true375, label %cond.false376, !dbg !4695

cond.true375:                                     ; preds = %if.then370
  br label %cond.end378, !dbg !4697

cond.false376:                                    ; preds = %if.then370
  %217 = load i8*, i8** %value.addr, align 8, !dbg !4699
  %call377 = call i64 @strlen(i8* %217) #8, !dbg !4699
  br label %cond.end378, !dbg !4699

cond.end378:                                      ; preds = %cond.false376, %cond.true375
  %cond379 = phi i64 [ 0, %cond.true375 ], [ %call377, %cond.false376 ], !dbg !4701
  %call380 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %entry_uname372, i8* %215, i64 %cond379), !dbg !4701
  br label %if.end381, !dbg !4703

if.end381:                                        ; preds = %cond.end378, %if.else366
  br label %if.end382

if.end382:                                        ; preds = %if.end381, %if.then363
  br label %sw.epilog, !dbg !4704

sw.epilog:                                        ; preds = %if.end, %if.end382, %if.end358, %sw.bb342, %if.end341, %if.end325, %if.end319, %if.end303, %if.end285, %if.end261, %if.end243, %if.end237, %if.end124, %if.end112
  %218 = load i32, i32* %err, align 4, !dbg !4705
  store i32 %218, i32* %retval, align 4, !dbg !4706
  br label %return, !dbg !4706

return:                                           ; preds = %sw.epilog, %if.then222, %if.then152, %if.then142, %if.then133, %if.then72, %if.then49, %if.then27, %if.then4
  %219 = load i32, i32* %retval, align 4, !dbg !4707
  ret i32 %219, !dbg !4707
}

declare void @archive_string_conversion_set_opt(%struct.archive_string_conv*, i32) #2

declare i32 @_archive_entry_copy_gname_l(%struct.archive_entry*, i8*, i64, %struct.archive_string_conv*) #2

declare void @archive_entry_copy_gname(%struct.archive_entry*, i8*) #2

declare i32 @_archive_entry_copy_link_l(%struct.archive_entry*, i8*, i64, %struct.archive_string_conv*) #2

declare void @archive_entry_copy_pathname(%struct.archive_entry*, i8*) #2

declare i32 @_archive_entry_copy_uname_l(%struct.archive_entry*, i8*, i64, %struct.archive_string_conv*) #2

declare void @archive_entry_copy_uname(%struct.archive_entry*, i8*) #2

; Function Attrs: nounwind readonly
declare i32 @strncmp(i8*, i8*, i64) #4

; Function Attrs: nounwind uwtable
define internal i64 @tar_atol10(i8* %p, i64 %char_cnt) #0 !dbg !489 {
entry:
  %p.addr = alloca i8*, align 8
  %char_cnt.addr = alloca i64, align 8
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !4708, metadata !563), !dbg !4709
  store i64 %char_cnt, i64* %char_cnt.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %char_cnt.addr, metadata !4710, metadata !563), !dbg !4711
  %0 = load i8*, i8** %p.addr, align 8, !dbg !4712
  %1 = load i64, i64* %char_cnt.addr, align 8, !dbg !4713
  %call = call i64 @tar_atol_base_n(i8* %0, i64 %1, i32 10), !dbg !4714
  ret i64 %call, !dbg !4715
}

declare void @archive_entry_set_size(%struct.archive_entry*, i64) #2

; Function Attrs: nounwind uwtable
define internal i32 @gnu_sparse_01_parse(%struct.archive_read* %a, %struct.tar* %tar, i8* %p) #0 !dbg !490 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %tar.addr = alloca %struct.tar*, align 8
  %p.addr = alloca i8*, align 8
  %e = alloca i8*, align 8
  %offset = alloca i64, align 8
  %size = alloca i64, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !4716, metadata !563), !dbg !4717
  store %struct.tar* %tar, %struct.tar** %tar.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tar** %tar.addr, metadata !4718, metadata !563), !dbg !4719
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !4720, metadata !563), !dbg !4721
  call void @llvm.dbg.declare(metadata i8** %e, metadata !4722, metadata !563), !dbg !4723
  call void @llvm.dbg.declare(metadata i64* %offset, metadata !4724, metadata !563), !dbg !4725
  store i64 -1, i64* %offset, align 8, !dbg !4725
  call void @llvm.dbg.declare(metadata i64* %size, metadata !4726, metadata !563), !dbg !4727
  store i64 -1, i64* %size, align 8, !dbg !4727
  br label %for.cond, !dbg !4728

for.cond:                                         ; preds = %if.end36, %entry
  %0 = load i8*, i8** %p.addr, align 8, !dbg !4729
  store i8* %0, i8** %e, align 8, !dbg !4733
  br label %while.cond, !dbg !4734

while.cond:                                       ; preds = %if.end, %for.cond
  %1 = load i8*, i8** %e, align 8, !dbg !4735
  %2 = load i8, i8* %1, align 1, !dbg !4737
  %conv = sext i8 %2 to i32, !dbg !4737
  %cmp = icmp ne i32 %conv, 0, !dbg !4738
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !4739

land.rhs:                                         ; preds = %while.cond
  %3 = load i8*, i8** %e, align 8, !dbg !4740
  %4 = load i8, i8* %3, align 1, !dbg !4742
  %conv2 = sext i8 %4 to i32, !dbg !4742
  %cmp3 = icmp ne i32 %conv2, 44, !dbg !4743
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond
  %5 = phi i1 [ false, %while.cond ], [ %cmp3, %land.rhs ]
  br i1 %5, label %while.body, label %while.end, !dbg !4744

while.body:                                       ; preds = %land.end
  %6 = load i8*, i8** %e, align 8, !dbg !4746
  %7 = load i8, i8* %6, align 1, !dbg !4749
  %conv5 = sext i8 %7 to i32, !dbg !4749
  %cmp6 = icmp slt i32 %conv5, 48, !dbg !4750
  br i1 %cmp6, label %if.then, label %lor.lhs.false, !dbg !4751

lor.lhs.false:                                    ; preds = %while.body
  %8 = load i8*, i8** %e, align 8, !dbg !4752
  %9 = load i8, i8* %8, align 1, !dbg !4754
  %conv8 = sext i8 %9 to i32, !dbg !4754
  %cmp9 = icmp sgt i32 %conv8, 57, !dbg !4755
  br i1 %cmp9, label %if.then, label %if.end, !dbg !4756

if.then:                                          ; preds = %lor.lhs.false, %while.body
  store i32 -20, i32* %retval, align 4, !dbg !4757
  br label %return, !dbg !4757

if.end:                                           ; preds = %lor.lhs.false
  %10 = load i8*, i8** %e, align 8, !dbg !4758
  %incdec.ptr = getelementptr inbounds i8, i8* %10, i32 1, !dbg !4758
  store i8* %incdec.ptr, i8** %e, align 8, !dbg !4758
  br label %while.cond, !dbg !4759

while.end:                                        ; preds = %land.end
  %11 = load i64, i64* %offset, align 8, !dbg !4761
  %cmp11 = icmp slt i64 %11, 0, !dbg !4763
  br i1 %cmp11, label %if.then13, label %if.else, !dbg !4764

if.then13:                                        ; preds = %while.end
  %12 = load i8*, i8** %p.addr, align 8, !dbg !4765
  %13 = load i8*, i8** %e, align 8, !dbg !4767
  %14 = load i8*, i8** %p.addr, align 8, !dbg !4768
  %sub.ptr.lhs.cast = ptrtoint i8* %13 to i64, !dbg !4769
  %sub.ptr.rhs.cast = ptrtoint i8* %14 to i64, !dbg !4769
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !4769
  %call = call i64 @tar_atol10(i8* %12, i64 %sub.ptr.sub), !dbg !4770
  store i64 %call, i64* %offset, align 8, !dbg !4771
  %15 = load i64, i64* %offset, align 8, !dbg !4772
  %cmp14 = icmp slt i64 %15, 0, !dbg !4774
  br i1 %cmp14, label %if.then16, label %if.end17, !dbg !4775

if.then16:                                        ; preds = %if.then13
  store i32 -20, i32* %retval, align 4, !dbg !4776
  br label %return, !dbg !4776

if.end17:                                         ; preds = %if.then13
  br label %if.end31, !dbg !4777

if.else:                                          ; preds = %while.end
  %16 = load i8*, i8** %p.addr, align 8, !dbg !4778
  %17 = load i8*, i8** %e, align 8, !dbg !4780
  %18 = load i8*, i8** %p.addr, align 8, !dbg !4781
  %sub.ptr.lhs.cast18 = ptrtoint i8* %17 to i64, !dbg !4782
  %sub.ptr.rhs.cast19 = ptrtoint i8* %18 to i64, !dbg !4782
  %sub.ptr.sub20 = sub i64 %sub.ptr.lhs.cast18, %sub.ptr.rhs.cast19, !dbg !4782
  %call21 = call i64 @tar_atol10(i8* %16, i64 %sub.ptr.sub20), !dbg !4783
  store i64 %call21, i64* %size, align 8, !dbg !4784
  %19 = load i64, i64* %size, align 8, !dbg !4785
  %cmp22 = icmp slt i64 %19, 0, !dbg !4787
  br i1 %cmp22, label %if.then24, label %if.end25, !dbg !4788

if.then24:                                        ; preds = %if.else
  store i32 -20, i32* %retval, align 4, !dbg !4789
  br label %return, !dbg !4789

if.end25:                                         ; preds = %if.else
  %20 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !4790
  %21 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !4792
  %22 = load i64, i64* %offset, align 8, !dbg !4793
  %23 = load i64, i64* %size, align 8, !dbg !4794
  %call26 = call i32 @gnu_add_sparse_entry(%struct.archive_read* %20, %struct.tar* %21, i64 %22, i64 %23), !dbg !4795
  %cmp27 = icmp ne i32 %call26, 0, !dbg !4796
  br i1 %cmp27, label %if.then29, label %if.end30, !dbg !4797

if.then29:                                        ; preds = %if.end25
  store i32 -30, i32* %retval, align 4, !dbg !4798
  br label %return, !dbg !4798

if.end30:                                         ; preds = %if.end25
  store i64 -1, i64* %offset, align 8, !dbg !4799
  br label %if.end31

if.end31:                                         ; preds = %if.end30, %if.end17
  %24 = load i8*, i8** %e, align 8, !dbg !4800
  %25 = load i8, i8* %24, align 1, !dbg !4802
  %conv32 = sext i8 %25 to i32, !dbg !4802
  %cmp33 = icmp eq i32 %conv32, 0, !dbg !4803
  br i1 %cmp33, label %if.then35, label %if.end36, !dbg !4804

if.then35:                                        ; preds = %if.end31
  store i32 0, i32* %retval, align 4, !dbg !4805
  br label %return, !dbg !4805

if.end36:                                         ; preds = %if.end31
  %26 = load i8*, i8** %e, align 8, !dbg !4806
  %add.ptr = getelementptr inbounds i8, i8* %26, i64 1, !dbg !4807
  store i8* %add.ptr, i8** %p.addr, align 8, !dbg !4808
  br label %for.cond, !dbg !4809

return:                                           ; preds = %if.then35, %if.then29, %if.then24, %if.then16, %if.then
  %27 = load i32, i32* %retval, align 4, !dbg !4811
  ret i32 %27, !dbg !4811
}

; Function Attrs: nounwind uwtable
define internal void @pax_time(i8* %p, i64* %ps, i64* %pn) #0 !dbg !493 {
entry:
  %p.addr = alloca i8*, align 8
  %ps.addr = alloca i64*, align 8
  %pn.addr = alloca i64*, align 8
  %digit = alloca i8, align 1
  %s = alloca i64, align 8
  %l = alloca i64, align 8
  %sign = alloca i32, align 4
  %limit = alloca i64, align 8
  %last_digit_limit = alloca i64, align 8
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !4812, metadata !563), !dbg !4813
  store i64* %ps, i64** %ps.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %ps.addr, metadata !4814, metadata !563), !dbg !4815
  store i64* %pn, i64** %pn.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %pn.addr, metadata !4816, metadata !563), !dbg !4817
  call void @llvm.dbg.declare(metadata i8* %digit, metadata !4818, metadata !563), !dbg !4819
  call void @llvm.dbg.declare(metadata i64* %s, metadata !4820, metadata !563), !dbg !4821
  call void @llvm.dbg.declare(metadata i64* %l, metadata !4822, metadata !563), !dbg !4823
  call void @llvm.dbg.declare(metadata i32* %sign, metadata !4824, metadata !563), !dbg !4825
  call void @llvm.dbg.declare(metadata i64* %limit, metadata !4826, metadata !563), !dbg !4827
  call void @llvm.dbg.declare(metadata i64* %last_digit_limit, metadata !4828, metadata !563), !dbg !4829
  store i64 922337203685477580, i64* %limit, align 8, !dbg !4830
  store i64 7, i64* %last_digit_limit, align 8, !dbg !4831
  store i64 0, i64* %s, align 8, !dbg !4832
  store i32 1, i32* %sign, align 4, !dbg !4833
  %0 = load i8*, i8** %p.addr, align 8, !dbg !4834
  %1 = load i8, i8* %0, align 1, !dbg !4836
  %conv = sext i8 %1 to i32, !dbg !4836
  %cmp = icmp eq i32 %conv, 45, !dbg !4837
  br i1 %cmp, label %if.then, label %if.end, !dbg !4838

if.then:                                          ; preds = %entry
  store i32 -1, i32* %sign, align 4, !dbg !4839
  %2 = load i8*, i8** %p.addr, align 8, !dbg !4841
  %incdec.ptr = getelementptr inbounds i8, i8* %2, i32 1, !dbg !4841
  store i8* %incdec.ptr, i8** %p.addr, align 8, !dbg !4841
  br label %if.end, !dbg !4842

if.end:                                           ; preds = %if.then, %entry
  br label %while.cond, !dbg !4843

while.cond:                                       ; preds = %if.end18, %if.end
  %3 = load i8*, i8** %p.addr, align 8, !dbg !4844
  %4 = load i8, i8* %3, align 1, !dbg !4846
  %conv2 = sext i8 %4 to i32, !dbg !4846
  %cmp3 = icmp sge i32 %conv2, 48, !dbg !4847
  br i1 %cmp3, label %land.rhs, label %land.end, !dbg !4848

land.rhs:                                         ; preds = %while.cond
  %5 = load i8*, i8** %p.addr, align 8, !dbg !4849
  %6 = load i8, i8* %5, align 1, !dbg !4851
  %conv5 = sext i8 %6 to i32, !dbg !4851
  %cmp6 = icmp sle i32 %conv5, 57, !dbg !4852
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond
  %7 = phi i1 [ false, %while.cond ], [ %cmp6, %land.rhs ]
  br i1 %7, label %while.body, label %while.end, !dbg !4853

while.body:                                       ; preds = %land.end
  %8 = load i8*, i8** %p.addr, align 8, !dbg !4855
  %9 = load i8, i8* %8, align 1, !dbg !4857
  %conv8 = sext i8 %9 to i32, !dbg !4857
  %sub = sub nsw i32 %conv8, 48, !dbg !4858
  %conv9 = trunc i32 %sub to i8, !dbg !4857
  store i8 %conv9, i8* %digit, align 1, !dbg !4859
  %10 = load i64, i64* %s, align 8, !dbg !4860
  %11 = load i64, i64* %limit, align 8, !dbg !4862
  %cmp10 = icmp sgt i64 %10, %11, !dbg !4863
  br i1 %cmp10, label %if.then17, label %lor.lhs.false, !dbg !4864

lor.lhs.false:                                    ; preds = %while.body
  %12 = load i64, i64* %s, align 8, !dbg !4865
  %13 = load i64, i64* %limit, align 8, !dbg !4866
  %cmp12 = icmp eq i64 %12, %13, !dbg !4867
  br i1 %cmp12, label %land.lhs.true, label %if.end18, !dbg !4868

land.lhs.true:                                    ; preds = %lor.lhs.false
  %14 = load i8, i8* %digit, align 1, !dbg !4869
  %conv14 = sext i8 %14 to i64, !dbg !4869
  %15 = load i64, i64* %last_digit_limit, align 8, !dbg !4871
  %cmp15 = icmp sgt i64 %conv14, %15, !dbg !4872
  br i1 %cmp15, label %if.then17, label %if.end18, !dbg !4873

if.then17:                                        ; preds = %land.lhs.true, %while.body
  store i64 9223372036854775807, i64* %s, align 8, !dbg !4875
  br label %while.end, !dbg !4877

if.end18:                                         ; preds = %land.lhs.true, %lor.lhs.false
  %16 = load i64, i64* %s, align 8, !dbg !4878
  %mul = mul nsw i64 %16, 10, !dbg !4879
  %17 = load i8, i8* %digit, align 1, !dbg !4880
  %conv19 = sext i8 %17 to i64, !dbg !4880
  %add = add nsw i64 %mul, %conv19, !dbg !4881
  store i64 %add, i64* %s, align 8, !dbg !4882
  %18 = load i8*, i8** %p.addr, align 8, !dbg !4883
  %incdec.ptr20 = getelementptr inbounds i8, i8* %18, i32 1, !dbg !4883
  store i8* %incdec.ptr20, i8** %p.addr, align 8, !dbg !4883
  br label %while.cond, !dbg !4884

while.end:                                        ; preds = %if.then17, %land.end
  %19 = load i64, i64* %s, align 8, !dbg !4886
  %20 = load i32, i32* %sign, align 4, !dbg !4887
  %conv21 = sext i32 %20 to i64, !dbg !4887
  %mul22 = mul nsw i64 %19, %conv21, !dbg !4888
  %21 = load i64*, i64** %ps.addr, align 8, !dbg !4889
  store i64 %mul22, i64* %21, align 8, !dbg !4890
  %22 = load i64*, i64** %pn.addr, align 8, !dbg !4891
  store i64 0, i64* %22, align 8, !dbg !4892
  %23 = load i8*, i8** %p.addr, align 8, !dbg !4893
  %24 = load i8, i8* %23, align 1, !dbg !4895
  %conv23 = sext i8 %24 to i32, !dbg !4895
  %cmp24 = icmp ne i32 %conv23, 46, !dbg !4896
  br i1 %cmp24, label %if.then26, label %if.end27, !dbg !4897

if.then26:                                        ; preds = %while.end
  br label %do.end, !dbg !4898

if.end27:                                         ; preds = %while.end
  store i64 100000000, i64* %l, align 8, !dbg !4899
  br label %do.body, !dbg !4900

do.body:                                          ; preds = %do.cond, %if.end27
  %25 = load i8*, i8** %p.addr, align 8, !dbg !4901
  %incdec.ptr28 = getelementptr inbounds i8, i8* %25, i32 1, !dbg !4901
  store i8* %incdec.ptr28, i8** %p.addr, align 8, !dbg !4901
  %26 = load i8*, i8** %p.addr, align 8, !dbg !4903
  %27 = load i8, i8* %26, align 1, !dbg !4905
  %conv29 = sext i8 %27 to i32, !dbg !4905
  %cmp30 = icmp sge i32 %conv29, 48, !dbg !4906
  br i1 %cmp30, label %land.lhs.true32, label %if.else, !dbg !4907

land.lhs.true32:                                  ; preds = %do.body
  %28 = load i8*, i8** %p.addr, align 8, !dbg !4908
  %29 = load i8, i8* %28, align 1, !dbg !4910
  %conv33 = sext i8 %29 to i32, !dbg !4910
  %cmp34 = icmp sle i32 %conv33, 57, !dbg !4911
  br i1 %cmp34, label %if.then36, label %if.else, !dbg !4912

if.then36:                                        ; preds = %land.lhs.true32
  %30 = load i8*, i8** %p.addr, align 8, !dbg !4913
  %31 = load i8, i8* %30, align 1, !dbg !4914
  %conv37 = sext i8 %31 to i32, !dbg !4914
  %sub38 = sub nsw i32 %conv37, 48, !dbg !4915
  %conv39 = sext i32 %sub38 to i64, !dbg !4916
  %32 = load i64, i64* %l, align 8, !dbg !4917
  %mul40 = mul i64 %conv39, %32, !dbg !4918
  %33 = load i64*, i64** %pn.addr, align 8, !dbg !4919
  %34 = load i64, i64* %33, align 8, !dbg !4920
  %add41 = add i64 %34, %mul40, !dbg !4920
  store i64 %add41, i64* %33, align 8, !dbg !4920
  br label %if.end42, !dbg !4921

if.else:                                          ; preds = %land.lhs.true32, %do.body
  br label %do.end, !dbg !4922

if.end42:                                         ; preds = %if.then36
  br label %do.cond, !dbg !4923

do.cond:                                          ; preds = %if.end42
  %35 = load i64, i64* %l, align 8, !dbg !4924
  %div = udiv i64 %35, 10, !dbg !4924
  store i64 %div, i64* %l, align 8, !dbg !4924
  %tobool = icmp ne i64 %div, 0, !dbg !4925
  br i1 %tobool, label %do.body, label %do.end, !dbg !4925

do.end:                                           ; preds = %if.then26, %do.cond, %if.else
  ret void, !dbg !4926
}

declare void @archive_entry_set_birthtime(%struct.archive_entry*, i64, i64) #2

; Function Attrs: nounwind uwtable
define internal i32 @pax_attribute_xattr(%struct.archive_entry* %entry1, i8* %name, i8* %value) #0 !dbg !497 {
entry:
  %retval = alloca i32, align 4
  %entry.addr = alloca %struct.archive_entry*, align 8
  %name.addr = alloca i8*, align 8
  %value.addr = alloca i8*, align 8
  %name_decoded = alloca i8*, align 8
  %value_decoded = alloca i8*, align 8
  %value_len = alloca i64, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !4927, metadata !563), !dbg !4928
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !4929, metadata !563), !dbg !4930
  store i8* %value, i8** %value.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %value.addr, metadata !4931, metadata !563), !dbg !4932
  call void @llvm.dbg.declare(metadata i8** %name_decoded, metadata !4933, metadata !563), !dbg !4934
  call void @llvm.dbg.declare(metadata i8** %value_decoded, metadata !4935, metadata !563), !dbg !4936
  call void @llvm.dbg.declare(metadata i64* %value_len, metadata !4937, metadata !563), !dbg !4938
  %0 = load i8*, i8** %name.addr, align 8, !dbg !4939
  %call = call i64 @strlen(i8* %0) #8, !dbg !4941
  %cmp = icmp ult i64 %call, 18, !dbg !4942
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !4943

lor.lhs.false:                                    ; preds = %entry
  %1 = load i8*, i8** %name.addr, align 8, !dbg !4944
  %call2 = call i32 @memcmp(i8* %1, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.57, i32 0, i32 0), i64 17) #8, !dbg !4946
  %cmp3 = icmp ne i32 %call2, 0, !dbg !4947
  br i1 %cmp3, label %if.then, label %if.end, !dbg !4948

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 3, i32* %retval, align 4, !dbg !4949
  br label %return, !dbg !4949

if.end:                                           ; preds = %lor.lhs.false
  %2 = load i8*, i8** %name.addr, align 8, !dbg !4950
  %add.ptr = getelementptr inbounds i8, i8* %2, i64 17, !dbg !4950
  store i8* %add.ptr, i8** %name.addr, align 8, !dbg !4950
  %3 = load i8*, i8** %name.addr, align 8, !dbg !4951
  %call4 = call i8* @url_decode(i8* %3), !dbg !4952
  store i8* %call4, i8** %name_decoded, align 8, !dbg !4953
  %4 = load i8*, i8** %name_decoded, align 8, !dbg !4954
  %cmp5 = icmp eq i8* %4, null, !dbg !4956
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !4957

if.then6:                                         ; preds = %if.end
  store i32 2, i32* %retval, align 4, !dbg !4958
  br label %return, !dbg !4958

if.end7:                                          ; preds = %if.end
  %5 = load i8*, i8** %value.addr, align 8, !dbg !4959
  %6 = load i8*, i8** %value.addr, align 8, !dbg !4960
  %call8 = call i64 @strlen(i8* %6) #8, !dbg !4961
  %call9 = call i8* @base64_decode(i8* %5, i64 %call8, i64* %value_len), !dbg !4962
  store i8* %call9, i8** %value_decoded, align 8, !dbg !4964
  %7 = load i8*, i8** %value_decoded, align 8, !dbg !4965
  %cmp10 = icmp eq i8* %7, null, !dbg !4967
  br i1 %cmp10, label %if.then11, label %if.end12, !dbg !4968

if.then11:                                        ; preds = %if.end7
  %8 = load i8*, i8** %name_decoded, align 8, !dbg !4969
  call void @free(i8* %8) #7, !dbg !4971
  store i32 1, i32* %retval, align 4, !dbg !4972
  br label %return, !dbg !4972

if.end12:                                         ; preds = %if.end7
  %9 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !4973
  %10 = load i8*, i8** %name_decoded, align 8, !dbg !4974
  %11 = load i8*, i8** %value_decoded, align 8, !dbg !4975
  %12 = load i64, i64* %value_len, align 8, !dbg !4976
  call void @archive_entry_xattr_add_entry(%struct.archive_entry* %9, i8* %10, i8* %11, i64 %12), !dbg !4977
  %13 = load i8*, i8** %name_decoded, align 8, !dbg !4978
  call void @free(i8* %13) #7, !dbg !4979
  %14 = load i8*, i8** %value_decoded, align 8, !dbg !4980
  call void @free(i8* %14) #7, !dbg !4981
  store i32 0, i32* %retval, align 4, !dbg !4982
  br label %return, !dbg !4982

return:                                           ; preds = %if.end12, %if.then11, %if.then6, %if.then
  %15 = load i32, i32* %retval, align 4, !dbg !4983
  ret i32 %15, !dbg !4983
}

; Function Attrs: nounwind uwtable
define internal i32 @pax_attribute_acl(%struct.archive_read* %a, %struct.tar* %tar, %struct.archive_entry* %entry1, i8* %value, i32 %type) #0 !dbg !509 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %tar.addr = alloca %struct.tar*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %value.addr = alloca i8*, align 8
  %type.addr = alloca i32, align 4
  %r = alloca i32, align 4
  %errstr = alloca i8*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !4984, metadata !563), !dbg !4985
  store %struct.tar* %tar, %struct.tar** %tar.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tar** %tar.addr, metadata !4986, metadata !563), !dbg !4987
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !4988, metadata !563), !dbg !4989
  store i8* %value, i8** %value.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %value.addr, metadata !4990, metadata !563), !dbg !4991
  store i32 %type, i32* %type.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %type.addr, metadata !4992, metadata !563), !dbg !4993
  call void @llvm.dbg.declare(metadata i32* %r, metadata !4994, metadata !563), !dbg !4995
  call void @llvm.dbg.declare(metadata i8** %errstr, metadata !4996, metadata !563), !dbg !4997
  %0 = load i32, i32* %type.addr, align 4, !dbg !4998
  switch i32 %0, label %sw.default [
    i32 256, label %sw.bb
    i32 512, label %sw.bb2
    i32 15360, label %sw.bb3
  ], !dbg !4999

sw.bb:                                            ; preds = %entry
  store i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.58, i32 0, i32 0), i8** %errstr, align 8, !dbg !5000
  br label %sw.epilog, !dbg !5002

sw.bb2:                                           ; preds = %entry
  store i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.59, i32 0, i32 0), i8** %errstr, align 8, !dbg !5003
  br label %sw.epilog, !dbg !5004

sw.bb3:                                           ; preds = %entry
  store i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.60, i32 0, i32 0), i8** %errstr, align 8, !dbg !5005
  br label %sw.epilog, !dbg !5006

sw.default:                                       ; preds = %entry
  %1 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !5007
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %1, i32 0, i32 0, !dbg !5008
  %2 = load i32, i32* %type.addr, align 4, !dbg !5009
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 -1, i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.85, i32 0, i32 0), i32 %2), !dbg !5010
  store i32 -30, i32* %retval, align 4, !dbg !5011
  br label %return, !dbg !5011

sw.epilog:                                        ; preds = %sw.bb3, %sw.bb2, %sw.bb
  %3 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !5012
  %sconv_acl = getelementptr inbounds %struct.tar, %struct.tar* %3, i32 0, i32 29, !dbg !5014
  %4 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv_acl, align 8, !dbg !5014
  %cmp = icmp eq %struct.archive_string_conv* %4, null, !dbg !5015
  br i1 %cmp, label %if.then, label %if.end9, !dbg !5016

if.then:                                          ; preds = %sw.epilog
  %5 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !5017
  %archive4 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %5, i32 0, i32 0, !dbg !5019
  %call = call %struct.archive_string_conv* @archive_string_conversion_from_charset(%struct.archive* %archive4, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.29, i32 0, i32 0), i32 1), !dbg !5020
  %6 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !5021
  %sconv_acl5 = getelementptr inbounds %struct.tar, %struct.tar* %6, i32 0, i32 29, !dbg !5022
  store %struct.archive_string_conv* %call, %struct.archive_string_conv** %sconv_acl5, align 8, !dbg !5023
  %7 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !5024
  %sconv_acl6 = getelementptr inbounds %struct.tar, %struct.tar* %7, i32 0, i32 29, !dbg !5026
  %8 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv_acl6, align 8, !dbg !5026
  %cmp7 = icmp eq %struct.archive_string_conv* %8, null, !dbg !5027
  br i1 %cmp7, label %if.then8, label %if.end, !dbg !5028

if.then8:                                         ; preds = %if.then
  store i32 -30, i32* %retval, align 4, !dbg !5029
  br label %return, !dbg !5029

if.end:                                           ; preds = %if.then
  br label %if.end9, !dbg !5030

if.end9:                                          ; preds = %if.end, %sw.epilog
  %9 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !5031
  %call10 = call %struct.archive_acl* @archive_entry_acl(%struct.archive_entry* %9), !dbg !5032
  %10 = load i8*, i8** %value.addr, align 8, !dbg !5033
  %11 = load i32, i32* %type.addr, align 4, !dbg !5034
  %12 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !5035
  %sconv_acl11 = getelementptr inbounds %struct.tar, %struct.tar* %12, i32 0, i32 29, !dbg !5036
  %13 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv_acl11, align 8, !dbg !5036
  %call12 = call i32 @archive_acl_from_text_l(%struct.archive_acl* %call10, i8* %10, i32 %11, %struct.archive_string_conv* %13), !dbg !5037
  store i32 %call12, i32* %r, align 4, !dbg !5039
  %14 = load i32, i32* %r, align 4, !dbg !5040
  %cmp13 = icmp ne i32 %14, 0, !dbg !5042
  br i1 %cmp13, label %if.then14, label %if.end20, !dbg !5043

if.then14:                                        ; preds = %if.end9
  %15 = load i32, i32* %r, align 4, !dbg !5044
  %cmp15 = icmp eq i32 %15, -30, !dbg !5047
  br i1 %cmp15, label %if.then16, label %if.end18, !dbg !5048

if.then16:                                        ; preds = %if.then14
  %16 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !5049
  %archive17 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %16, i32 0, i32 0, !dbg !5051
  %17 = load i8*, i8** %errstr, align 8, !dbg !5052
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive17, i32 12, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.86, i32 0, i32 0), i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.87, i32 0, i32 0), i8* %17), !dbg !5053
  %18 = load i32, i32* %r, align 4, !dbg !5054
  store i32 %18, i32* %retval, align 4, !dbg !5055
  br label %return, !dbg !5055

if.end18:                                         ; preds = %if.then14
  %19 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !5056
  %archive19 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %19, i32 0, i32 0, !dbg !5057
  %20 = load i8*, i8** %errstr, align 8, !dbg !5058
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive19, i32 -1, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.86, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.88, i32 0, i32 0), i8* %20), !dbg !5059
  br label %if.end20, !dbg !5060

if.end20:                                         ; preds = %if.end18, %if.end9
  %21 = load i32, i32* %r, align 4, !dbg !5061
  store i32 %21, i32* %retval, align 4, !dbg !5062
  br label %return, !dbg !5062

return:                                           ; preds = %if.end20, %if.then16, %if.then8, %sw.default
  %22 = load i32, i32* %retval, align 4, !dbg !5063
  ret i32 %22, !dbg !5063
}

declare void @archive_entry_set_rdevmajor(%struct.archive_entry*, i64) #2

declare void @archive_entry_set_rdevminor(%struct.archive_entry*, i64) #2

declare i8* @archive_entry_copy_fflags_text(%struct.archive_entry*, i8*) #2

declare void @archive_entry_set_nlink(%struct.archive_entry*, i32) #2

; Function Attrs: nounwind uwtable
define internal i32 @pax_attribute_schily_xattr(%struct.archive_entry* %entry1, i8* %name, i8* %value, i64 %value_length) #0 !dbg !512 {
entry:
  %retval = alloca i32, align 4
  %entry.addr = alloca %struct.archive_entry*, align 8
  %name.addr = alloca i8*, align 8
  %value.addr = alloca i8*, align 8
  %value_length.addr = alloca i64, align 8
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !5064, metadata !563), !dbg !5065
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !5066, metadata !563), !dbg !5067
  store i8* %value, i8** %value.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %value.addr, metadata !5068, metadata !563), !dbg !5069
  store i64 %value_length, i64* %value_length.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %value_length.addr, metadata !5070, metadata !563), !dbg !5071
  %0 = load i8*, i8** %name.addr, align 8, !dbg !5072
  %call = call i64 @strlen(i8* %0) #8, !dbg !5074
  %cmp = icmp ult i64 %call, 14, !dbg !5075
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !5076

lor.lhs.false:                                    ; preds = %entry
  %1 = load i8*, i8** %name.addr, align 8, !dbg !5077
  %call2 = call i32 @memcmp(i8* %1, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.68, i32 0, i32 0), i64 13) #8, !dbg !5079
  %cmp3 = icmp ne i32 %call2, 0, !dbg !5080
  br i1 %cmp3, label %if.then, label %if.end, !dbg !5081

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 1, i32* %retval, align 4, !dbg !5082
  br label %return, !dbg !5082

if.end:                                           ; preds = %lor.lhs.false
  %2 = load i8*, i8** %name.addr, align 8, !dbg !5083
  %add.ptr = getelementptr inbounds i8, i8* %2, i64 13, !dbg !5083
  store i8* %add.ptr, i8** %name.addr, align 8, !dbg !5083
  %3 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !5084
  %4 = load i8*, i8** %name.addr, align 8, !dbg !5085
  %5 = load i8*, i8** %value.addr, align 8, !dbg !5086
  %6 = load i64, i64* %value_length.addr, align 8, !dbg !5087
  call void @archive_entry_xattr_add_entry(%struct.archive_entry* %3, i8* %4, i8* %5, i64 %6), !dbg !5088
  store i32 0, i32* %retval, align 4, !dbg !5089
  br label %return, !dbg !5089

return:                                           ; preds = %if.end, %if.then
  %7 = load i32, i32* %retval, align 4, !dbg !5090
  ret i32 %7, !dbg !5090
}

; Function Attrs: nounwind uwtable
define internal i32 @solaris_sparse_parse(%struct.archive_read* %a, %struct.tar* %tar, %struct.archive_entry* %entry1, i8* %p) #0 !dbg !515 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %tar.addr = alloca %struct.tar*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %p.addr = alloca i8*, align 8
  %e = alloca i8*, align 8
  %start = alloca i64, align 8
  %end = alloca i64, align 8
  %hole = alloca i32, align 4
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !5091, metadata !563), !dbg !5092
  store %struct.tar* %tar, %struct.tar** %tar.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tar** %tar.addr, metadata !5093, metadata !563), !dbg !5094
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !5095, metadata !563), !dbg !5096
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !5097, metadata !563), !dbg !5098
  call void @llvm.dbg.declare(metadata i8** %e, metadata !5099, metadata !563), !dbg !5100
  call void @llvm.dbg.declare(metadata i64* %start, metadata !5101, metadata !563), !dbg !5102
  call void @llvm.dbg.declare(metadata i64* %end, metadata !5103, metadata !563), !dbg !5104
  call void @llvm.dbg.declare(metadata i32* %hole, metadata !5105, metadata !563), !dbg !5106
  store i32 1, i32* %hole, align 4, !dbg !5106
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !5107
  store i64 0, i64* %end, align 8, !dbg !5108
  %1 = load i8*, i8** %p.addr, align 8, !dbg !5109
  %2 = load i8, i8* %1, align 1, !dbg !5111
  %conv = sext i8 %2 to i32, !dbg !5111
  %cmp = icmp eq i32 %conv, 32, !dbg !5112
  br i1 %cmp, label %if.then, label %if.else, !dbg !5113

if.then:                                          ; preds = %entry
  %3 = load i8*, i8** %p.addr, align 8, !dbg !5114
  %incdec.ptr = getelementptr inbounds i8, i8* %3, i32 1, !dbg !5114
  store i8* %incdec.ptr, i8** %p.addr, align 8, !dbg !5114
  br label %if.end, !dbg !5115

if.else:                                          ; preds = %entry
  store i32 -20, i32* %retval, align 4, !dbg !5116
  br label %return, !dbg !5116

if.end:                                           ; preds = %if.then
  br label %for.cond, !dbg !5117

for.cond:                                         ; preds = %if.end36, %if.end
  %4 = load i8*, i8** %p.addr, align 8, !dbg !5118
  store i8* %4, i8** %e, align 8, !dbg !5122
  br label %while.cond, !dbg !5123

while.cond:                                       ; preds = %if.end16, %for.cond
  %5 = load i8*, i8** %e, align 8, !dbg !5124
  %6 = load i8, i8* %5, align 1, !dbg !5126
  %conv3 = sext i8 %6 to i32, !dbg !5126
  %cmp4 = icmp ne i32 %conv3, 0, !dbg !5127
  br i1 %cmp4, label %land.rhs, label %land.end, !dbg !5128

land.rhs:                                         ; preds = %while.cond
  %7 = load i8*, i8** %e, align 8, !dbg !5129
  %8 = load i8, i8* %7, align 1, !dbg !5131
  %conv6 = sext i8 %8 to i32, !dbg !5131
  %cmp7 = icmp ne i32 %conv6, 32, !dbg !5132
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond
  %9 = phi i1 [ false, %while.cond ], [ %cmp7, %land.rhs ]
  br i1 %9, label %while.body, label %while.end, !dbg !5133

while.body:                                       ; preds = %land.end
  %10 = load i8*, i8** %e, align 8, !dbg !5135
  %11 = load i8, i8* %10, align 1, !dbg !5138
  %conv9 = sext i8 %11 to i32, !dbg !5138
  %cmp10 = icmp slt i32 %conv9, 48, !dbg !5139
  br i1 %cmp10, label %if.then15, label %lor.lhs.false, !dbg !5140

lor.lhs.false:                                    ; preds = %while.body
  %12 = load i8*, i8** %e, align 8, !dbg !5141
  %13 = load i8, i8* %12, align 1, !dbg !5143
  %conv12 = sext i8 %13 to i32, !dbg !5143
  %cmp13 = icmp sgt i32 %conv12, 57, !dbg !5144
  br i1 %cmp13, label %if.then15, label %if.end16, !dbg !5145

if.then15:                                        ; preds = %lor.lhs.false, %while.body
  store i32 -20, i32* %retval, align 4, !dbg !5146
  br label %return, !dbg !5146

if.end16:                                         ; preds = %lor.lhs.false
  %14 = load i8*, i8** %e, align 8, !dbg !5147
  %incdec.ptr17 = getelementptr inbounds i8, i8* %14, i32 1, !dbg !5147
  store i8* %incdec.ptr17, i8** %e, align 8, !dbg !5147
  br label %while.cond, !dbg !5148

while.end:                                        ; preds = %land.end
  %15 = load i64, i64* %end, align 8, !dbg !5150
  store i64 %15, i64* %start, align 8, !dbg !5151
  %16 = load i8*, i8** %p.addr, align 8, !dbg !5152
  %17 = load i8*, i8** %e, align 8, !dbg !5153
  %18 = load i8*, i8** %p.addr, align 8, !dbg !5154
  %sub.ptr.lhs.cast = ptrtoint i8* %17 to i64, !dbg !5155
  %sub.ptr.rhs.cast = ptrtoint i8* %18 to i64, !dbg !5155
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !5155
  %call = call i64 @tar_atol10(i8* %16, i64 %sub.ptr.sub), !dbg !5156
  store i64 %call, i64* %end, align 8, !dbg !5157
  %19 = load i64, i64* %end, align 8, !dbg !5158
  %cmp18 = icmp slt i64 %19, 0, !dbg !5160
  br i1 %cmp18, label %if.then20, label %if.end21, !dbg !5161

if.then20:                                        ; preds = %while.end
  store i32 -20, i32* %retval, align 4, !dbg !5162
  br label %return, !dbg !5162

if.end21:                                         ; preds = %while.end
  %20 = load i64, i64* %start, align 8, !dbg !5163
  %21 = load i64, i64* %end, align 8, !dbg !5165
  %cmp22 = icmp slt i64 %20, %21, !dbg !5166
  br i1 %cmp22, label %if.then24, label %if.end31, !dbg !5167

if.then24:                                        ; preds = %if.end21
  %22 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !5168
  %23 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !5171
  %24 = load i64, i64* %start, align 8, !dbg !5172
  %25 = load i64, i64* %end, align 8, !dbg !5173
  %26 = load i64, i64* %start, align 8, !dbg !5174
  %sub = sub nsw i64 %25, %26, !dbg !5175
  %call25 = call i32 @gnu_add_sparse_entry(%struct.archive_read* %22, %struct.tar* %23, i64 %24, i64 %sub), !dbg !5176
  %cmp26 = icmp ne i32 %call25, 0, !dbg !5177
  br i1 %cmp26, label %if.then28, label %if.end29, !dbg !5178

if.then28:                                        ; preds = %if.then24
  store i32 -30, i32* %retval, align 4, !dbg !5179
  br label %return, !dbg !5179

if.end29:                                         ; preds = %if.then24
  %27 = load i32, i32* %hole, align 4, !dbg !5180
  %28 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !5181
  %sparse_last = getelementptr inbounds %struct.tar, %struct.tar* %28, i32 0, i32 20, !dbg !5182
  %29 = load %struct.sparse_block*, %struct.sparse_block** %sparse_last, align 8, !dbg !5182
  %hole30 = getelementptr inbounds %struct.sparse_block, %struct.sparse_block* %29, i32 0, i32 3, !dbg !5183
  store i32 %27, i32* %hole30, align 8, !dbg !5184
  br label %if.end31, !dbg !5185

if.end31:                                         ; preds = %if.end29, %if.end21
  %30 = load i8*, i8** %e, align 8, !dbg !5186
  %31 = load i8, i8* %30, align 1, !dbg !5188
  %conv32 = sext i8 %31 to i32, !dbg !5188
  %cmp33 = icmp eq i32 %conv32, 0, !dbg !5189
  br i1 %cmp33, label %if.then35, label %if.end36, !dbg !5190

if.then35:                                        ; preds = %if.end31
  store i32 0, i32* %retval, align 4, !dbg !5191
  br label %return, !dbg !5191

if.end36:                                         ; preds = %if.end31
  %32 = load i8*, i8** %e, align 8, !dbg !5192
  %add.ptr = getelementptr inbounds i8, i8* %32, i64 1, !dbg !5193
  store i8* %add.ptr, i8** %p.addr, align 8, !dbg !5194
  %33 = load i32, i32* %hole, align 4, !dbg !5195
  %cmp37 = icmp eq i32 %33, 0, !dbg !5196
  %conv38 = zext i1 %cmp37 to i32, !dbg !5196
  store i32 %conv38, i32* %hole, align 4, !dbg !5197
  br label %for.cond, !dbg !5198

return:                                           ; preds = %if.then35, %if.then28, %if.then20, %if.then15, %if.else
  %34 = load i32, i32* %retval, align 4, !dbg !5200
  ret i32 %34, !dbg !5200
}

declare void @archive_entry_set_atime(%struct.archive_entry*, i64, i64) #2

declare void @archive_entry_set_ctime(%struct.archive_entry*, i64, i64) #2

declare void @archive_entry_set_gid(%struct.archive_entry*, i64) #2

declare void @archive_entry_set_mtime(%struct.archive_entry*, i64, i64) #2

declare void @archive_entry_set_uid(%struct.archive_entry*, i64) #2

; Function Attrs: nounwind uwtable
define internal i8* @url_decode(i8* %in) #0 !dbg !500 {
entry:
  %retval = alloca i8*, align 8
  %in.addr = alloca i8*, align 8
  %out = alloca i8*, align 8
  %d = alloca i8*, align 8
  %s = alloca i8*, align 8
  %digit1 = alloca i32, align 4
  %digit2 = alloca i32, align 4
  store i8* %in, i8** %in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %in.addr, metadata !5201, metadata !563), !dbg !5202
  call void @llvm.dbg.declare(metadata i8** %out, metadata !5203, metadata !563), !dbg !5204
  call void @llvm.dbg.declare(metadata i8** %d, metadata !5205, metadata !563), !dbg !5206
  call void @llvm.dbg.declare(metadata i8** %s, metadata !5207, metadata !563), !dbg !5208
  %0 = load i8*, i8** %in.addr, align 8, !dbg !5209
  %call = call i64 @strlen(i8* %0) #8, !dbg !5210
  %add = add i64 %call, 1, !dbg !5211
  %call1 = call noalias i8* @malloc(i64 %add) #7, !dbg !5212
  store i8* %call1, i8** %out, align 8, !dbg !5214
  %1 = load i8*, i8** %out, align 8, !dbg !5215
  %cmp = icmp eq i8* %1, null, !dbg !5217
  br i1 %cmp, label %if.then, label %if.end, !dbg !5218

if.then:                                          ; preds = %entry
  store i8* null, i8** %retval, align 8, !dbg !5219
  br label %return, !dbg !5219

if.end:                                           ; preds = %entry
  %2 = load i8*, i8** %in.addr, align 8, !dbg !5220
  store i8* %2, i8** %s, align 8, !dbg !5222
  %3 = load i8*, i8** %out, align 8, !dbg !5223
  store i8* %3, i8** %d, align 8, !dbg !5224
  br label %for.cond, !dbg !5225

for.cond:                                         ; preds = %if.end31, %if.then28, %if.end
  %4 = load i8*, i8** %s, align 8, !dbg !5226
  %5 = load i8, i8* %4, align 1, !dbg !5229
  %conv = sext i8 %5 to i32, !dbg !5229
  %cmp2 = icmp ne i32 %conv, 0, !dbg !5230
  br i1 %cmp2, label %for.body, label %for.end, !dbg !5231

for.body:                                         ; preds = %for.cond
  %6 = load i8*, i8** %s, align 8, !dbg !5232
  %arrayidx = getelementptr inbounds i8, i8* %6, i64 0, !dbg !5232
  %7 = load i8, i8* %arrayidx, align 1, !dbg !5232
  %conv4 = sext i8 %7 to i32, !dbg !5232
  %cmp5 = icmp eq i32 %conv4, 37, !dbg !5235
  br i1 %cmp5, label %land.lhs.true, label %if.end31, !dbg !5236

land.lhs.true:                                    ; preds = %for.body
  %8 = load i8*, i8** %s, align 8, !dbg !5237
  %arrayidx7 = getelementptr inbounds i8, i8* %8, i64 1, !dbg !5237
  %9 = load i8, i8* %arrayidx7, align 1, !dbg !5237
  %conv8 = sext i8 %9 to i32, !dbg !5237
  %cmp9 = icmp ne i32 %conv8, 0, !dbg !5239
  br i1 %cmp9, label %land.lhs.true11, label %if.end31, !dbg !5240

land.lhs.true11:                                  ; preds = %land.lhs.true
  %10 = load i8*, i8** %s, align 8, !dbg !5241
  %arrayidx12 = getelementptr inbounds i8, i8* %10, i64 2, !dbg !5241
  %11 = load i8, i8* %arrayidx12, align 1, !dbg !5241
  %conv13 = sext i8 %11 to i32, !dbg !5241
  %cmp14 = icmp ne i32 %conv13, 0, !dbg !5243
  br i1 %cmp14, label %if.then16, label %if.end31, !dbg !5244

if.then16:                                        ; preds = %land.lhs.true11
  call void @llvm.dbg.declare(metadata i32* %digit1, metadata !5245, metadata !563), !dbg !5247
  %12 = load i8*, i8** %s, align 8, !dbg !5248
  %arrayidx17 = getelementptr inbounds i8, i8* %12, i64 1, !dbg !5248
  %13 = load i8, i8* %arrayidx17, align 1, !dbg !5248
  %conv18 = sext i8 %13 to i32, !dbg !5248
  %call19 = call i32 @tohex(i32 %conv18), !dbg !5249
  store i32 %call19, i32* %digit1, align 4, !dbg !5247
  call void @llvm.dbg.declare(metadata i32* %digit2, metadata !5250, metadata !563), !dbg !5251
  %14 = load i8*, i8** %s, align 8, !dbg !5252
  %arrayidx20 = getelementptr inbounds i8, i8* %14, i64 2, !dbg !5252
  %15 = load i8, i8* %arrayidx20, align 1, !dbg !5252
  %conv21 = sext i8 %15 to i32, !dbg !5252
  %call22 = call i32 @tohex(i32 %conv21), !dbg !5253
  store i32 %call22, i32* %digit2, align 4, !dbg !5251
  %16 = load i32, i32* %digit1, align 4, !dbg !5254
  %cmp23 = icmp sge i32 %16, 0, !dbg !5256
  br i1 %cmp23, label %land.lhs.true25, label %if.end30, !dbg !5257

land.lhs.true25:                                  ; preds = %if.then16
  %17 = load i32, i32* %digit2, align 4, !dbg !5258
  %cmp26 = icmp sge i32 %17, 0, !dbg !5260
  br i1 %cmp26, label %if.then28, label %if.end30, !dbg !5261

if.then28:                                        ; preds = %land.lhs.true25
  %18 = load i8*, i8** %s, align 8, !dbg !5262
  %add.ptr = getelementptr inbounds i8, i8* %18, i64 3, !dbg !5262
  store i8* %add.ptr, i8** %s, align 8, !dbg !5262
  %19 = load i32, i32* %digit1, align 4, !dbg !5264
  %shl = shl i32 %19, 4, !dbg !5265
  %20 = load i32, i32* %digit2, align 4, !dbg !5266
  %or = or i32 %shl, %20, !dbg !5267
  %conv29 = trunc i32 %or to i8, !dbg !5268
  %21 = load i8*, i8** %d, align 8, !dbg !5269
  %incdec.ptr = getelementptr inbounds i8, i8* %21, i32 1, !dbg !5269
  store i8* %incdec.ptr, i8** %d, align 8, !dbg !5269
  store i8 %conv29, i8* %21, align 1, !dbg !5270
  br label %for.cond, !dbg !5271

if.end30:                                         ; preds = %land.lhs.true25, %if.then16
  br label %if.end31, !dbg !5272

if.end31:                                         ; preds = %if.end30, %land.lhs.true11, %land.lhs.true, %for.body
  %22 = load i8*, i8** %s, align 8, !dbg !5273
  %incdec.ptr32 = getelementptr inbounds i8, i8* %22, i32 1, !dbg !5273
  store i8* %incdec.ptr32, i8** %s, align 8, !dbg !5273
  %23 = load i8, i8* %22, align 1, !dbg !5274
  %24 = load i8*, i8** %d, align 8, !dbg !5275
  %incdec.ptr33 = getelementptr inbounds i8, i8* %24, i32 1, !dbg !5275
  store i8* %incdec.ptr33, i8** %d, align 8, !dbg !5275
  store i8 %23, i8* %24, align 1, !dbg !5276
  br label %for.cond, !dbg !5277

for.end:                                          ; preds = %for.cond
  %25 = load i8*, i8** %d, align 8, !dbg !5279
  store i8 0, i8* %25, align 1, !dbg !5280
  %26 = load i8*, i8** %out, align 8, !dbg !5281
  store i8* %26, i8** %retval, align 8, !dbg !5282
  br label %return, !dbg !5282

return:                                           ; preds = %for.end, %if.then
  %27 = load i8*, i8** %retval, align 8, !dbg !5283
  ret i8* %27, !dbg !5283
}

; Function Attrs: nounwind uwtable
define internal i8* @base64_decode(i8* %s, i64 %len, i64* %out_len) #0 !dbg !506 {
entry:
  %retval = alloca i8*, align 8
  %s.addr = alloca i8*, align 8
  %len.addr = alloca i64, align 8
  %out_len.addr = alloca i64*, align 8
  %out = alloca i8*, align 8
  %d = alloca i8*, align 8
  %src = alloca i8*, align 8
  %i = alloca i32, align 4
  %v = alloca i32, align 4
  %group_size = alloca i32, align 4
  store i8* %s, i8** %s.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %s.addr, metadata !5284, metadata !563), !dbg !5285
  store i64 %len, i64* %len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %len.addr, metadata !5286, metadata !563), !dbg !5287
  store i64* %out_len, i64** %out_len.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %out_len.addr, metadata !5288, metadata !563), !dbg !5289
  call void @llvm.dbg.declare(metadata i8** %out, metadata !5290, metadata !563), !dbg !5291
  call void @llvm.dbg.declare(metadata i8** %d, metadata !5292, metadata !563), !dbg !5293
  call void @llvm.dbg.declare(metadata i8** %src, metadata !5294, metadata !563), !dbg !5295
  %0 = load i8*, i8** %s.addr, align 8, !dbg !5296
  store i8* %0, i8** %src, align 8, !dbg !5295
  %1 = load i8, i8* getelementptr inbounds ([64 x i8], [64 x i8]* @base64_decode.digits, i64 0, i64 1), align 1, !dbg !5297
  %idxprom = zext i8 %1 to i64, !dbg !5299
  %arrayidx = getelementptr inbounds [128 x i8], [128 x i8]* @base64_decode.decode_table, i64 0, i64 %idxprom, !dbg !5299
  %2 = load i8, i8* %arrayidx, align 1, !dbg !5299
  %conv = zext i8 %2 to i32, !dbg !5299
  %cmp = icmp ne i32 %conv, 1, !dbg !5300
  br i1 %cmp, label %if.then, label %if.end, !dbg !5301

if.then:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %i, metadata !5302, metadata !563), !dbg !5304
  call void @llvm.memset.p0i8.i64(i8* getelementptr inbounds ([128 x i8], [128 x i8]* @base64_decode.decode_table, i32 0, i32 0), i8 -1, i64 128, i32 16, i1 false), !dbg !5305
  store i32 0, i32* %i, align 4, !dbg !5306
  br label %for.cond, !dbg !5308

for.cond:                                         ; preds = %for.inc, %if.then
  %3 = load i32, i32* %i, align 4, !dbg !5309
  %conv2 = zext i32 %3 to i64, !dbg !5309
  %cmp3 = icmp ult i64 %conv2, 64, !dbg !5312
  br i1 %cmp3, label %for.body, label %for.end, !dbg !5313

for.body:                                         ; preds = %for.cond
  %4 = load i32, i32* %i, align 4, !dbg !5314
  %conv5 = trunc i32 %4 to i8, !dbg !5314
  %5 = load i32, i32* %i, align 4, !dbg !5315
  %idxprom6 = zext i32 %5 to i64, !dbg !5316
  %arrayidx7 = getelementptr inbounds [64 x i8], [64 x i8]* @base64_decode.digits, i64 0, i64 %idxprom6, !dbg !5316
  %6 = load i8, i8* %arrayidx7, align 1, !dbg !5316
  %idxprom8 = zext i8 %6 to i64, !dbg !5317
  %arrayidx9 = getelementptr inbounds [128 x i8], [128 x i8]* @base64_decode.decode_table, i64 0, i64 %idxprom8, !dbg !5317
  store i8 %conv5, i8* %arrayidx9, align 1, !dbg !5318
  br label %for.inc, !dbg !5317

for.inc:                                          ; preds = %for.body
  %7 = load i32, i32* %i, align 4, !dbg !5319
  %inc = add i32 %7, 1, !dbg !5319
  store i32 %inc, i32* %i, align 4, !dbg !5319
  br label %for.cond, !dbg !5321

for.end:                                          ; preds = %for.cond
  br label %if.end, !dbg !5322

if.end:                                           ; preds = %for.end, %entry
  %8 = load i64, i64* %len.addr, align 8, !dbg !5323
  %9 = load i64, i64* %len.addr, align 8, !dbg !5324
  %div = udiv i64 %9, 4, !dbg !5325
  %sub = sub i64 %8, %div, !dbg !5326
  %add = add i64 %sub, 1, !dbg !5327
  %call = call noalias i8* @malloc(i64 %add) #7, !dbg !5328
  store i8* %call, i8** %out, align 8, !dbg !5329
  %10 = load i8*, i8** %out, align 8, !dbg !5330
  %cmp10 = icmp eq i8* %10, null, !dbg !5332
  br i1 %cmp10, label %if.then12, label %if.end13, !dbg !5333

if.then12:                                        ; preds = %if.end
  %11 = load i64*, i64** %out_len.addr, align 8, !dbg !5334
  store i64 0, i64* %11, align 8, !dbg !5336
  store i8* null, i8** %retval, align 8, !dbg !5337
  br label %return, !dbg !5337

if.end13:                                         ; preds = %if.end
  %12 = load i8*, i8** %out, align 8, !dbg !5338
  store i8* %12, i8** %d, align 8, !dbg !5339
  br label %while.cond, !dbg !5340

while.cond:                                       ; preds = %sw.epilog, %if.end13
  %13 = load i64, i64* %len.addr, align 8, !dbg !5341
  %cmp14 = icmp ugt i64 %13, 0, !dbg !5343
  br i1 %cmp14, label %while.body, label %while.end67, !dbg !5344

while.body:                                       ; preds = %while.cond
  call void @llvm.dbg.declare(metadata i32* %v, metadata !5345, metadata !563), !dbg !5347
  store i32 0, i32* %v, align 4, !dbg !5347
  call void @llvm.dbg.declare(metadata i32* %group_size, metadata !5348, metadata !563), !dbg !5349
  store i32 0, i32* %group_size, align 4, !dbg !5349
  br label %while.cond16, !dbg !5350

while.cond16:                                     ; preds = %if.end44, %if.then43, %while.body
  %14 = load i32, i32* %group_size, align 4, !dbg !5351
  %cmp17 = icmp slt i32 %14, 4, !dbg !5353
  br i1 %cmp17, label %land.rhs, label %land.end, !dbg !5354

land.rhs:                                         ; preds = %while.cond16
  %15 = load i64, i64* %len.addr, align 8, !dbg !5355
  %cmp19 = icmp ugt i64 %15, 0, !dbg !5357
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond16
  %16 = phi i1 [ false, %while.cond16 ], [ %cmp19, %land.rhs ]
  br i1 %16, label %while.body21, label %while.end, !dbg !5358

while.body21:                                     ; preds = %land.end
  %17 = load i8*, i8** %src, align 8, !dbg !5360
  %18 = load i8, i8* %17, align 1, !dbg !5363
  %conv22 = zext i8 %18 to i32, !dbg !5363
  %cmp23 = icmp eq i32 %conv22, 61, !dbg !5364
  br i1 %cmp23, label %if.then28, label %lor.lhs.false, !dbg !5365

lor.lhs.false:                                    ; preds = %while.body21
  %19 = load i8*, i8** %src, align 8, !dbg !5366
  %20 = load i8, i8* %19, align 1, !dbg !5368
  %conv25 = zext i8 %20 to i32, !dbg !5368
  %cmp26 = icmp eq i32 %conv25, 95, !dbg !5369
  br i1 %cmp26, label %if.then28, label %if.end29, !dbg !5370

if.then28:                                        ; preds = %lor.lhs.false, %while.body21
  store i64 0, i64* %len.addr, align 8, !dbg !5371
  br label %while.end, !dbg !5373

if.end29:                                         ; preds = %lor.lhs.false
  %21 = load i8*, i8** %src, align 8, !dbg !5374
  %22 = load i8, i8* %21, align 1, !dbg !5376
  %conv30 = zext i8 %22 to i32, !dbg !5376
  %cmp31 = icmp sgt i32 %conv30, 127, !dbg !5377
  br i1 %cmp31, label %if.then43, label %lor.lhs.false33, !dbg !5378

lor.lhs.false33:                                  ; preds = %if.end29
  %23 = load i8*, i8** %src, align 8, !dbg !5379
  %24 = load i8, i8* %23, align 1, !dbg !5381
  %conv34 = zext i8 %24 to i32, !dbg !5381
  %cmp35 = icmp slt i32 %conv34, 32, !dbg !5382
  br i1 %cmp35, label %if.then43, label %lor.lhs.false37, !dbg !5383

lor.lhs.false37:                                  ; preds = %lor.lhs.false33
  %25 = load i8*, i8** %src, align 8, !dbg !5384
  %26 = load i8, i8* %25, align 1, !dbg !5385
  %idxprom38 = zext i8 %26 to i64, !dbg !5386
  %arrayidx39 = getelementptr inbounds [128 x i8], [128 x i8]* @base64_decode.decode_table, i64 0, i64 %idxprom38, !dbg !5386
  %27 = load i8, i8* %arrayidx39, align 1, !dbg !5386
  %conv40 = zext i8 %27 to i32, !dbg !5386
  %cmp41 = icmp eq i32 %conv40, 255, !dbg !5387
  br i1 %cmp41, label %if.then43, label %if.end44, !dbg !5388

if.then43:                                        ; preds = %lor.lhs.false37, %lor.lhs.false33, %if.end29
  %28 = load i64, i64* %len.addr, align 8, !dbg !5390
  %dec = add i64 %28, -1, !dbg !5390
  store i64 %dec, i64* %len.addr, align 8, !dbg !5390
  %29 = load i8*, i8** %src, align 8, !dbg !5392
  %incdec.ptr = getelementptr inbounds i8, i8* %29, i32 1, !dbg !5392
  store i8* %incdec.ptr, i8** %src, align 8, !dbg !5392
  br label %while.cond16, !dbg !5393

if.end44:                                         ; preds = %lor.lhs.false37
  %30 = load i32, i32* %v, align 4, !dbg !5394
  %shl = shl i32 %30, 6, !dbg !5394
  store i32 %shl, i32* %v, align 4, !dbg !5394
  %31 = load i8*, i8** %src, align 8, !dbg !5395
  %incdec.ptr45 = getelementptr inbounds i8, i8* %31, i32 1, !dbg !5395
  store i8* %incdec.ptr45, i8** %src, align 8, !dbg !5395
  %32 = load i8, i8* %31, align 1, !dbg !5396
  %idxprom46 = zext i8 %32 to i64, !dbg !5397
  %arrayidx47 = getelementptr inbounds [128 x i8], [128 x i8]* @base64_decode.decode_table, i64 0, i64 %idxprom46, !dbg !5397
  %33 = load i8, i8* %arrayidx47, align 1, !dbg !5397
  %conv48 = zext i8 %33 to i32, !dbg !5397
  %34 = load i32, i32* %v, align 4, !dbg !5398
  %or = or i32 %34, %conv48, !dbg !5398
  store i32 %or, i32* %v, align 4, !dbg !5398
  %35 = load i64, i64* %len.addr, align 8, !dbg !5399
  %dec49 = add i64 %35, -1, !dbg !5399
  store i64 %dec49, i64* %len.addr, align 8, !dbg !5399
  %36 = load i32, i32* %group_size, align 4, !dbg !5400
  %inc50 = add nsw i32 %36, 1, !dbg !5400
  store i32 %inc50, i32* %group_size, align 4, !dbg !5400
  br label %while.cond16, !dbg !5401

while.end:                                        ; preds = %if.then28, %land.end
  %37 = load i32, i32* %group_size, align 4, !dbg !5403
  %sub51 = sub nsw i32 4, %37, !dbg !5404
  %mul = mul nsw i32 6, %sub51, !dbg !5405
  %38 = load i32, i32* %v, align 4, !dbg !5406
  %shl52 = shl i32 %38, %mul, !dbg !5406
  store i32 %shl52, i32* %v, align 4, !dbg !5406
  %39 = load i32, i32* %group_size, align 4, !dbg !5407
  switch i32 %39, label %sw.epilog [
    i32 4, label %sw.bb
    i32 3, label %sw.bb55
    i32 2, label %sw.bb59
    i32 1, label %sw.bb64
  ], !dbg !5408

sw.bb:                                            ; preds = %while.end
  %40 = load i32, i32* %v, align 4, !dbg !5409
  %and = and i32 %40, 255, !dbg !5411
  %conv53 = trunc i32 %and to i8, !dbg !5409
  %41 = load i8*, i8** %d, align 8, !dbg !5412
  %arrayidx54 = getelementptr inbounds i8, i8* %41, i64 2, !dbg !5412
  store i8 %conv53, i8* %arrayidx54, align 1, !dbg !5413
  br label %sw.bb55, !dbg !5412

sw.bb55:                                          ; preds = %while.end, %sw.bb
  %42 = load i32, i32* %v, align 4, !dbg !5414
  %shr = ashr i32 %42, 8, !dbg !5415
  %and56 = and i32 %shr, 255, !dbg !5416
  %conv57 = trunc i32 %and56 to i8, !dbg !5417
  %43 = load i8*, i8** %d, align 8, !dbg !5418
  %arrayidx58 = getelementptr inbounds i8, i8* %43, i64 1, !dbg !5418
  store i8 %conv57, i8* %arrayidx58, align 1, !dbg !5419
  br label %sw.bb59, !dbg !5418

sw.bb59:                                          ; preds = %while.end, %sw.bb55
  %44 = load i32, i32* %v, align 4, !dbg !5420
  %shr60 = ashr i32 %44, 16, !dbg !5421
  %and61 = and i32 %shr60, 255, !dbg !5422
  %conv62 = trunc i32 %and61 to i8, !dbg !5423
  %45 = load i8*, i8** %d, align 8, !dbg !5424
  %arrayidx63 = getelementptr inbounds i8, i8* %45, i64 0, !dbg !5424
  store i8 %conv62, i8* %arrayidx63, align 1, !dbg !5425
  br label %sw.epilog, !dbg !5426

sw.bb64:                                          ; preds = %while.end
  br label %sw.epilog, !dbg !5427

sw.epilog:                                        ; preds = %while.end, %sw.bb64, %sw.bb59
  %46 = load i32, i32* %group_size, align 4, !dbg !5428
  %mul65 = mul nsw i32 %46, 3, !dbg !5429
  %div66 = sdiv i32 %mul65, 4, !dbg !5430
  %47 = load i8*, i8** %d, align 8, !dbg !5431
  %idx.ext = sext i32 %div66 to i64, !dbg !5431
  %add.ptr = getelementptr inbounds i8, i8* %47, i64 %idx.ext, !dbg !5431
  store i8* %add.ptr, i8** %d, align 8, !dbg !5431
  br label %while.cond, !dbg !5432

while.end67:                                      ; preds = %while.cond
  %48 = load i8*, i8** %d, align 8, !dbg !5434
  %49 = load i8*, i8** %out, align 8, !dbg !5435
  %sub.ptr.lhs.cast = ptrtoint i8* %48 to i64, !dbg !5436
  %sub.ptr.rhs.cast = ptrtoint i8* %49 to i64, !dbg !5436
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !5436
  %50 = load i64*, i64** %out_len.addr, align 8, !dbg !5437
  store i64 %sub.ptr.sub, i64* %50, align 8, !dbg !5438
  %51 = load i8*, i8** %out, align 8, !dbg !5439
  store i8* %51, i8** %retval, align 8, !dbg !5440
  br label %return, !dbg !5440

return:                                           ; preds = %while.end67, %if.then12
  %52 = load i8*, i8** %retval, align 8, !dbg !5441
  ret i8* %52, !dbg !5441
}

declare void @archive_entry_xattr_add_entry(%struct.archive_entry*, i8*, i8*, i64) #2

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #3

; Function Attrs: nounwind uwtable
define internal i32 @tohex(i32 %c) #0 !dbg !503 {
entry:
  %retval = alloca i32, align 4
  %c.addr = alloca i32, align 4
  store i32 %c, i32* %c.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %c.addr, metadata !5442, metadata !563), !dbg !5443
  %0 = load i32, i32* %c.addr, align 4, !dbg !5444
  %cmp = icmp sge i32 %0, 48, !dbg !5446
  br i1 %cmp, label %land.lhs.true, label %if.else, !dbg !5447

land.lhs.true:                                    ; preds = %entry
  %1 = load i32, i32* %c.addr, align 4, !dbg !5448
  %cmp1 = icmp sle i32 %1, 57, !dbg !5450
  br i1 %cmp1, label %if.then, label %if.else, !dbg !5451

if.then:                                          ; preds = %land.lhs.true
  %2 = load i32, i32* %c.addr, align 4, !dbg !5452
  %sub = sub nsw i32 %2, 48, !dbg !5453
  store i32 %sub, i32* %retval, align 4, !dbg !5454
  br label %return, !dbg !5454

if.else:                                          ; preds = %land.lhs.true, %entry
  %3 = load i32, i32* %c.addr, align 4, !dbg !5455
  %cmp2 = icmp sge i32 %3, 65, !dbg !5457
  br i1 %cmp2, label %land.lhs.true3, label %if.else7, !dbg !5458

land.lhs.true3:                                   ; preds = %if.else
  %4 = load i32, i32* %c.addr, align 4, !dbg !5459
  %cmp4 = icmp sle i32 %4, 70, !dbg !5461
  br i1 %cmp4, label %if.then5, label %if.else7, !dbg !5462

if.then5:                                         ; preds = %land.lhs.true3
  %5 = load i32, i32* %c.addr, align 4, !dbg !5463
  %sub6 = sub nsw i32 %5, 65, !dbg !5464
  %add = add nsw i32 %sub6, 10, !dbg !5465
  store i32 %add, i32* %retval, align 4, !dbg !5466
  br label %return, !dbg !5466

if.else7:                                         ; preds = %land.lhs.true3, %if.else
  %6 = load i32, i32* %c.addr, align 4, !dbg !5467
  %cmp8 = icmp sge i32 %6, 97, !dbg !5469
  br i1 %cmp8, label %land.lhs.true9, label %if.else14, !dbg !5470

land.lhs.true9:                                   ; preds = %if.else7
  %7 = load i32, i32* %c.addr, align 4, !dbg !5471
  %cmp10 = icmp sle i32 %7, 102, !dbg !5473
  br i1 %cmp10, label %if.then11, label %if.else14, !dbg !5474

if.then11:                                        ; preds = %land.lhs.true9
  %8 = load i32, i32* %c.addr, align 4, !dbg !5475
  %sub12 = sub nsw i32 %8, 97, !dbg !5476
  %add13 = add nsw i32 %sub12, 10, !dbg !5477
  store i32 %add13, i32* %retval, align 4, !dbg !5478
  br label %return, !dbg !5478

if.else14:                                        ; preds = %land.lhs.true9, %if.else7
  store i32 -1, i32* %retval, align 4, !dbg !5479
  br label %return, !dbg !5479

return:                                           ; preds = %if.else14, %if.then11, %if.then5, %if.then
  %9 = load i32, i32* %retval, align 4, !dbg !5480
  ret i32 %9, !dbg !5480
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #6

; Function Attrs: nounwind uwtable
define internal i32 @header_common(%struct.archive_read* %a, %struct.tar* %tar, %struct.archive_entry* %entry1, i8* %h) #0 !dbg !519 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %tar.addr = alloca %struct.tar*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %h.addr = alloca i8*, align 8
  %header = alloca %struct.archive_entry_header_ustar*, align 8
  %tartype = alloca i8, align 1
  %err = alloca i32, align 4
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !5481, metadata !563), !dbg !5482
  store %struct.tar* %tar, %struct.tar** %tar.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tar** %tar.addr, metadata !5483, metadata !563), !dbg !5484
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !5485, metadata !563), !dbg !5486
  store i8* %h, i8** %h.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %h.addr, metadata !5487, metadata !563), !dbg !5488
  call void @llvm.dbg.declare(metadata %struct.archive_entry_header_ustar** %header, metadata !5489, metadata !563), !dbg !5490
  call void @llvm.dbg.declare(metadata i8* %tartype, metadata !5491, metadata !563), !dbg !5492
  call void @llvm.dbg.declare(metadata i32* %err, metadata !5493, metadata !563), !dbg !5494
  store i32 0, i32* %err, align 4, !dbg !5494
  %0 = load i8*, i8** %h.addr, align 8, !dbg !5495
  %1 = bitcast i8* %0 to %struct.archive_entry_header_ustar*, !dbg !5496
  store %struct.archive_entry_header_ustar* %1, %struct.archive_entry_header_ustar** %header, align 8, !dbg !5497
  %2 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !5498
  %linkname = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %2, i32 0, i32 8, !dbg !5500
  %arrayidx = getelementptr inbounds [100 x i8], [100 x i8]* %linkname, i64 0, i64 0, !dbg !5498
  %3 = load i8, i8* %arrayidx, align 1, !dbg !5498
  %tobool = icmp ne i8 %3, 0, !dbg !5498
  br i1 %tobool, label %if.then, label %if.else, !dbg !5501

if.then:                                          ; preds = %entry
  %4 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !5502
  %entry_linkpath = getelementptr inbounds %struct.tar, %struct.tar* %4, i32 0, i32 3, !dbg !5502
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %entry_linkpath, i32 0, i32 1, !dbg !5502
  store i64 0, i64* %length, align 8, !dbg !5502
  %5 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !5502
  %entry_linkpath2 = getelementptr inbounds %struct.tar, %struct.tar* %5, i32 0, i32 3, !dbg !5502
  %6 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !5502
  %linkname3 = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %6, i32 0, i32 8, !dbg !5502
  %arraydecay = getelementptr inbounds [100 x i8], [100 x i8]* %linkname3, i32 0, i32 0, !dbg !5502
  %call = call %struct.archive_string* @archive_strncat(%struct.archive_string* %entry_linkpath2, i8* %arraydecay, i64 100), !dbg !5502
  br label %if.end, !dbg !5502

if.else:                                          ; preds = %entry
  %7 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !5503
  %entry_linkpath4 = getelementptr inbounds %struct.tar, %struct.tar* %7, i32 0, i32 3, !dbg !5503
  %length5 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %entry_linkpath4, i32 0, i32 1, !dbg !5503
  store i64 0, i64* %length5, align 8, !dbg !5503
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %8 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !5504
  %9 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !5505
  %mode = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %9, i32 0, i32 1, !dbg !5506
  %arraydecay6 = getelementptr inbounds [8 x i8], [8 x i8]* %mode, i32 0, i32 0, !dbg !5505
  %call7 = call i64 @tar_atol(i8* %arraydecay6, i64 8), !dbg !5507
  %conv = trunc i64 %call7 to i32, !dbg !5508
  call void @archive_entry_set_mode(%struct.archive_entry* %8, i32 %conv), !dbg !5509
  %10 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !5510
  %11 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !5511
  %uid = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %11, i32 0, i32 2, !dbg !5512
  %arraydecay8 = getelementptr inbounds [8 x i8], [8 x i8]* %uid, i32 0, i32 0, !dbg !5511
  %call9 = call i64 @tar_atol(i8* %arraydecay8, i64 8), !dbg !5513
  call void @archive_entry_set_uid(%struct.archive_entry* %10, i64 %call9), !dbg !5514
  %12 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !5516
  %13 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !5517
  %gid = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %13, i32 0, i32 3, !dbg !5518
  %arraydecay10 = getelementptr inbounds [8 x i8], [8 x i8]* %gid, i32 0, i32 0, !dbg !5517
  %call11 = call i64 @tar_atol(i8* %arraydecay10, i64 8), !dbg !5519
  call void @archive_entry_set_gid(%struct.archive_entry* %12, i64 %call11), !dbg !5520
  %14 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !5521
  %size = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %14, i32 0, i32 4, !dbg !5522
  %arraydecay12 = getelementptr inbounds [12 x i8], [12 x i8]* %size, i32 0, i32 0, !dbg !5521
  %call13 = call i64 @tar_atol(i8* %arraydecay12, i64 12), !dbg !5523
  %15 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !5524
  %entry_bytes_remaining = getelementptr inbounds %struct.tar, %struct.tar* %15, i32 0, i32 13, !dbg !5525
  store i64 %call13, i64* %entry_bytes_remaining, align 8, !dbg !5526
  %16 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !5527
  %entry_bytes_remaining14 = getelementptr inbounds %struct.tar, %struct.tar* %16, i32 0, i32 13, !dbg !5529
  %17 = load i64, i64* %entry_bytes_remaining14, align 8, !dbg !5529
  %cmp = icmp slt i64 %17, 0, !dbg !5530
  br i1 %cmp, label %if.then16, label %if.end18, !dbg !5531

if.then16:                                        ; preds = %if.end
  %18 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !5532
  %entry_bytes_remaining17 = getelementptr inbounds %struct.tar, %struct.tar* %18, i32 0, i32 13, !dbg !5534
  store i64 0, i64* %entry_bytes_remaining17, align 8, !dbg !5535
  %19 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !5536
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %19, i32 0, i32 0, !dbg !5537
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 -1, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.89, i32 0, i32 0)), !dbg !5538
  store i32 -30, i32* %retval, align 4, !dbg !5539
  br label %return, !dbg !5539

if.end18:                                         ; preds = %if.end
  %20 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !5540
  %entry_bytes_remaining19 = getelementptr inbounds %struct.tar, %struct.tar* %20, i32 0, i32 13, !dbg !5542
  %21 = load i64, i64* %entry_bytes_remaining19, align 8, !dbg !5542
  %cmp20 = icmp eq i64 %21, 9223372036854775807, !dbg !5543
  br i1 %cmp20, label %if.then22, label %if.end25, !dbg !5544

if.then22:                                        ; preds = %if.end18
  %22 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !5545
  %entry_bytes_remaining23 = getelementptr inbounds %struct.tar, %struct.tar* %22, i32 0, i32 13, !dbg !5547
  store i64 0, i64* %entry_bytes_remaining23, align 8, !dbg !5548
  %23 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !5549
  %archive24 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %23, i32 0, i32 0, !dbg !5550
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive24, i32 -1, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.90, i32 0, i32 0)), !dbg !5551
  store i32 -30, i32* %retval, align 4, !dbg !5552
  br label %return, !dbg !5552

if.end25:                                         ; preds = %if.end18
  %24 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !5553
  %entry_bytes_remaining26 = getelementptr inbounds %struct.tar, %struct.tar* %24, i32 0, i32 13, !dbg !5554
  %25 = load i64, i64* %entry_bytes_remaining26, align 8, !dbg !5554
  %26 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !5555
  %realsize = getelementptr inbounds %struct.tar, %struct.tar* %26, i32 0, i32 17, !dbg !5556
  store i64 %25, i64* %realsize, align 8, !dbg !5557
  %27 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !5558
  %28 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !5559
  %entry_bytes_remaining27 = getelementptr inbounds %struct.tar, %struct.tar* %28, i32 0, i32 13, !dbg !5560
  %29 = load i64, i64* %entry_bytes_remaining27, align 8, !dbg !5560
  call void @archive_entry_set_size(%struct.archive_entry* %27, i64 %29), !dbg !5561
  %30 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !5562
  %31 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !5563
  %mtime = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %31, i32 0, i32 5, !dbg !5564
  %arraydecay28 = getelementptr inbounds [12 x i8], [12 x i8]* %mtime, i32 0, i32 0, !dbg !5563
  %call29 = call i64 @tar_atol(i8* %arraydecay28, i64 12), !dbg !5565
  call void @archive_entry_set_mtime(%struct.archive_entry* %30, i64 %call29, i64 0), !dbg !5566
  %32 = load %struct.archive_entry_header_ustar*, %struct.archive_entry_header_ustar** %header, align 8, !dbg !5567
  %typeflag = getelementptr inbounds %struct.archive_entry_header_ustar, %struct.archive_entry_header_ustar* %32, i32 0, i32 7, !dbg !5568
  %arrayidx30 = getelementptr inbounds [1 x i8], [1 x i8]* %typeflag, i64 0, i64 0, !dbg !5567
  %33 = load i8, i8* %arrayidx30, align 1, !dbg !5567
  store i8 %33, i8* %tartype, align 1, !dbg !5569
  %34 = load i8, i8* %tartype, align 1, !dbg !5570
  %conv31 = sext i8 %34 to i32, !dbg !5570
  switch i32 %conv31, label %sw.default [
    i32 49, label %sw.bb
    i32 50, label %sw.bb81
    i32 51, label %sw.bb99
    i32 52, label %sw.bb101
    i32 53, label %sw.bb103
    i32 54, label %sw.bb105
    i32 68, label %sw.bb107
    i32 77, label %sw.bb108
    i32 78, label %sw.bb109
    i32 83, label %sw.bb110
    i32 48, label %sw.bb110
  ], !dbg !5571

sw.bb:                                            ; preds = %if.end25
  %35 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !5572
  %36 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !5575
  %entry_linkpath32 = getelementptr inbounds %struct.tar, %struct.tar* %36, i32 0, i32 3, !dbg !5576
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %entry_linkpath32, i32 0, i32 0, !dbg !5577
  %37 = load i8*, i8** %s, align 8, !dbg !5577
  %38 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !5578
  %entry_linkpath33 = getelementptr inbounds %struct.tar, %struct.tar* %38, i32 0, i32 3, !dbg !5578
  %length34 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %entry_linkpath33, i32 0, i32 1, !dbg !5578
  %39 = load i64, i64* %length34, align 8, !dbg !5578
  %40 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !5579
  %sconv = getelementptr inbounds %struct.tar, %struct.tar* %40, i32 0, i32 28, !dbg !5580
  %41 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !5580
  %call35 = call i32 @_archive_entry_copy_hardlink_l(%struct.archive_entry* %35, i8* %37, i64 %39, %struct.archive_string_conv* %41), !dbg !5581
  %cmp36 = icmp ne i32 %call35, 0, !dbg !5582
  br i1 %cmp36, label %if.then38, label %if.end45, !dbg !5583

if.then38:                                        ; preds = %sw.bb
  %42 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !5584
  %43 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !5586
  %sconv39 = getelementptr inbounds %struct.tar, %struct.tar* %43, i32 0, i32 28, !dbg !5587
  %44 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv39, align 8, !dbg !5587
  %call40 = call i32 @set_conversion_failed_error(%struct.archive_read* %42, %struct.archive_string_conv* %44, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.42, i32 0, i32 0)), !dbg !5588
  store i32 %call40, i32* %err, align 4, !dbg !5589
  %45 = load i32, i32* %err, align 4, !dbg !5590
  %cmp41 = icmp eq i32 %45, -30, !dbg !5592
  br i1 %cmp41, label %if.then43, label %if.end44, !dbg !5593

if.then43:                                        ; preds = %if.then38
  %46 = load i32, i32* %err, align 4, !dbg !5594
  store i32 %46, i32* %retval, align 4, !dbg !5595
  br label %return, !dbg !5595

if.end44:                                         ; preds = %if.then38
  br label %if.end45, !dbg !5596

if.end45:                                         ; preds = %if.end44, %sw.bb
  %47 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !5597
  %call46 = call i64 @archive_entry_size(%struct.archive_entry* %47), !dbg !5599
  %cmp47 = icmp sgt i64 %call46, 0, !dbg !5600
  br i1 %cmp47, label %if.then49, label %if.end50, !dbg !5601

if.then49:                                        ; preds = %if.end45
  %48 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !5602
  call void @archive_entry_set_filetype(%struct.archive_entry* %48, i32 32768), !dbg !5603
  br label %if.end50, !dbg !5603

if.end50:                                         ; preds = %if.then49, %if.end45
  %49 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !5604
  %call51 = call i64 @archive_entry_size(%struct.archive_entry* %49), !dbg !5606
  %cmp52 = icmp eq i64 %call51, 0, !dbg !5607
  br i1 %cmp52, label %if.then54, label %if.else55, !dbg !5608

if.then54:                                        ; preds = %if.end50
  br label %if.end80, !dbg !5609

if.else55:                                        ; preds = %if.end50
  %50 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !5611
  %archive56 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %50, i32 0, i32 0, !dbg !5614
  %archive_format = getelementptr inbounds %struct.archive, %struct.archive* %archive56, i32 0, i32 3, !dbg !5615
  %51 = load i32, i32* %archive_format, align 8, !dbg !5615
  %cmp57 = icmp eq i32 %51, 196610, !dbg !5616
  br i1 %cmp57, label %if.then59, label %if.else60, !dbg !5611

if.then59:                                        ; preds = %if.else55
  br label %if.end79, !dbg !5617

if.else60:                                        ; preds = %if.else55
  %52 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !5619
  %archive61 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %52, i32 0, i32 0, !dbg !5622
  %archive_format62 = getelementptr inbounds %struct.archive, %struct.archive* %archive61, i32 0, i32 3, !dbg !5623
  %53 = load i32, i32* %archive_format62, align 8, !dbg !5623
  %cmp63 = icmp eq i32 %53, 196608, !dbg !5624
  br i1 %cmp63, label %if.then69, label %lor.lhs.false, !dbg !5625

lor.lhs.false:                                    ; preds = %if.else60
  %54 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !5626
  %archive65 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %54, i32 0, i32 0, !dbg !5627
  %archive_format66 = getelementptr inbounds %struct.archive, %struct.archive* %archive65, i32 0, i32 3, !dbg !5628
  %55 = load i32, i32* %archive_format66, align 8, !dbg !5628
  %cmp67 = icmp eq i32 %55, 196612, !dbg !5629
  br i1 %cmp67, label %if.then69, label %if.else71, !dbg !5630

if.then69:                                        ; preds = %lor.lhs.false, %if.else60
  %56 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !5632
  call void @archive_entry_set_size(%struct.archive_entry* %56, i64 0), !dbg !5634
  %57 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !5635
  %entry_bytes_remaining70 = getelementptr inbounds %struct.tar, %struct.tar* %57, i32 0, i32 13, !dbg !5636
  store i64 0, i64* %entry_bytes_remaining70, align 8, !dbg !5637
  br label %if.end78, !dbg !5638

if.else71:                                        ; preds = %lor.lhs.false
  %58 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !5639
  %call72 = call i32 @archive_read_format_tar_bid(%struct.archive_read* %58, i32 50), !dbg !5642
  %cmp73 = icmp sgt i32 %call72, 50, !dbg !5643
  br i1 %cmp73, label %if.then75, label %if.end77, !dbg !5642

if.then75:                                        ; preds = %if.else71
  %59 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !5644
  call void @archive_entry_set_size(%struct.archive_entry* %59, i64 0), !dbg !5646
  %60 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !5647
  %entry_bytes_remaining76 = getelementptr inbounds %struct.tar, %struct.tar* %60, i32 0, i32 13, !dbg !5648
  store i64 0, i64* %entry_bytes_remaining76, align 8, !dbg !5649
  br label %if.end77, !dbg !5650

if.end77:                                         ; preds = %if.then75, %if.else71
  br label %if.end78

if.end78:                                         ; preds = %if.end77, %if.then69
  br label %if.end79

if.end79:                                         ; preds = %if.end78, %if.then59
  br label %if.end80

if.end80:                                         ; preds = %if.end79, %if.then54
  br label %sw.epilog, !dbg !5651

sw.bb81:                                          ; preds = %if.end25
  %61 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !5652
  call void @archive_entry_set_filetype(%struct.archive_entry* %61, i32 40960), !dbg !5653
  %62 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !5654
  call void @archive_entry_set_size(%struct.archive_entry* %62, i64 0), !dbg !5655
  %63 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !5656
  %entry_bytes_remaining82 = getelementptr inbounds %struct.tar, %struct.tar* %63, i32 0, i32 13, !dbg !5657
  store i64 0, i64* %entry_bytes_remaining82, align 8, !dbg !5658
  %64 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !5659
  %65 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !5661
  %entry_linkpath83 = getelementptr inbounds %struct.tar, %struct.tar* %65, i32 0, i32 3, !dbg !5662
  %s84 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %entry_linkpath83, i32 0, i32 0, !dbg !5663
  %66 = load i8*, i8** %s84, align 8, !dbg !5663
  %67 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !5664
  %entry_linkpath85 = getelementptr inbounds %struct.tar, %struct.tar* %67, i32 0, i32 3, !dbg !5664
  %length86 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %entry_linkpath85, i32 0, i32 1, !dbg !5664
  %68 = load i64, i64* %length86, align 8, !dbg !5664
  %69 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !5665
  %sconv87 = getelementptr inbounds %struct.tar, %struct.tar* %69, i32 0, i32 28, !dbg !5666
  %70 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv87, align 8, !dbg !5666
  %call88 = call i32 @_archive_entry_copy_symlink_l(%struct.archive_entry* %64, i8* %66, i64 %68, %struct.archive_string_conv* %70), !dbg !5667
  %cmp89 = icmp ne i32 %call88, 0, !dbg !5668
  br i1 %cmp89, label %if.then91, label %if.end98, !dbg !5669

if.then91:                                        ; preds = %sw.bb81
  %71 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !5670
  %72 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !5672
  %sconv92 = getelementptr inbounds %struct.tar, %struct.tar* %72, i32 0, i32 28, !dbg !5673
  %73 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv92, align 8, !dbg !5673
  %call93 = call i32 @set_conversion_failed_error(%struct.archive_read* %71, %struct.archive_string_conv* %73, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.42, i32 0, i32 0)), !dbg !5674
  store i32 %call93, i32* %err, align 4, !dbg !5675
  %74 = load i32, i32* %err, align 4, !dbg !5676
  %cmp94 = icmp eq i32 %74, -30, !dbg !5678
  br i1 %cmp94, label %if.then96, label %if.end97, !dbg !5679

if.then96:                                        ; preds = %if.then91
  %75 = load i32, i32* %err, align 4, !dbg !5680
  store i32 %75, i32* %retval, align 4, !dbg !5681
  br label %return, !dbg !5681

if.end97:                                         ; preds = %if.then91
  br label %if.end98, !dbg !5682

if.end98:                                         ; preds = %if.end97, %sw.bb81
  br label %sw.epilog, !dbg !5683

sw.bb99:                                          ; preds = %if.end25
  %76 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !5684
  call void @archive_entry_set_filetype(%struct.archive_entry* %76, i32 8192), !dbg !5685
  %77 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !5686
  call void @archive_entry_set_size(%struct.archive_entry* %77, i64 0), !dbg !5687
  %78 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !5688
  %entry_bytes_remaining100 = getelementptr inbounds %struct.tar, %struct.tar* %78, i32 0, i32 13, !dbg !5689
  store i64 0, i64* %entry_bytes_remaining100, align 8, !dbg !5690
  br label %sw.epilog, !dbg !5691

sw.bb101:                                         ; preds = %if.end25
  %79 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !5692
  call void @archive_entry_set_filetype(%struct.archive_entry* %79, i32 24576), !dbg !5693
  %80 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !5694
  call void @archive_entry_set_size(%struct.archive_entry* %80, i64 0), !dbg !5695
  %81 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !5696
  %entry_bytes_remaining102 = getelementptr inbounds %struct.tar, %struct.tar* %81, i32 0, i32 13, !dbg !5697
  store i64 0, i64* %entry_bytes_remaining102, align 8, !dbg !5698
  br label %sw.epilog, !dbg !5699

sw.bb103:                                         ; preds = %if.end25
  %82 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !5700
  call void @archive_entry_set_filetype(%struct.archive_entry* %82, i32 16384), !dbg !5701
  %83 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !5702
  call void @archive_entry_set_size(%struct.archive_entry* %83, i64 0), !dbg !5703
  %84 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !5704
  %entry_bytes_remaining104 = getelementptr inbounds %struct.tar, %struct.tar* %84, i32 0, i32 13, !dbg !5705
  store i64 0, i64* %entry_bytes_remaining104, align 8, !dbg !5706
  br label %sw.epilog, !dbg !5707

sw.bb105:                                         ; preds = %if.end25
  %85 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !5708
  call void @archive_entry_set_filetype(%struct.archive_entry* %85, i32 4096), !dbg !5709
  %86 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !5710
  call void @archive_entry_set_size(%struct.archive_entry* %86, i64 0), !dbg !5711
  %87 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !5712
  %entry_bytes_remaining106 = getelementptr inbounds %struct.tar, %struct.tar* %87, i32 0, i32 13, !dbg !5713
  store i64 0, i64* %entry_bytes_remaining106, align 8, !dbg !5714
  br label %sw.epilog, !dbg !5715

sw.bb107:                                         ; preds = %if.end25
  %88 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !5716
  call void @archive_entry_set_filetype(%struct.archive_entry* %88, i32 16384), !dbg !5717
  br label %sw.epilog, !dbg !5718

sw.bb108:                                         ; preds = %if.end25
  br label %sw.epilog, !dbg !5719

sw.bb109:                                         ; preds = %if.end25
  %89 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !5720
  call void @archive_entry_set_filetype(%struct.archive_entry* %89, i32 32768), !dbg !5721
  br label %sw.epilog, !dbg !5722

sw.bb110:                                         ; preds = %if.end25, %if.end25
  %90 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !5723
  %sparse_allowed = getelementptr inbounds %struct.tar, %struct.tar* %90, i32 0, i32 18, !dbg !5724
  store i32 1, i32* %sparse_allowed, align 8, !dbg !5725
  br label %sw.default, !dbg !5723

sw.default:                                       ; preds = %if.end25, %sw.bb110
  %91 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !5726
  call void @archive_entry_set_filetype(%struct.archive_entry* %91, i32 32768), !dbg !5727
  br label %sw.epilog, !dbg !5728

sw.epilog:                                        ; preds = %sw.default, %sw.bb109, %sw.bb108, %sw.bb107, %sw.bb105, %sw.bb103, %sw.bb101, %sw.bb99, %if.end98, %if.end80
  %92 = load i32, i32* %err, align 4, !dbg !5729
  store i32 %92, i32* %retval, align 4, !dbg !5730
  br label %return, !dbg !5730

return:                                           ; preds = %sw.epilog, %if.then96, %if.then43, %if.then22, %if.then16
  %93 = load i32, i32* %retval, align 4, !dbg !5731
  ret i32 %93, !dbg !5731
}

declare void @archive_entry_set_rdev(%struct.archive_entry*, i64) #2

; Function Attrs: nounwind uwtable
define internal i32 @gnu_sparse_old_read(%struct.archive_read* %a, %struct.tar* %tar, %struct.archive_entry_header_gnutar* %header, i64* %unconsumed) #0 !dbg !425 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %tar.addr = alloca %struct.tar*, align 8
  %header.addr = alloca %struct.archive_entry_header_gnutar*, align 8
  %unconsumed.addr = alloca i64*, align 8
  %bytes_read = alloca i64, align 8
  %data = alloca i8*, align 8
  %ext = alloca %struct.extended*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !5732, metadata !563), !dbg !5733
  store %struct.tar* %tar, %struct.tar** %tar.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tar** %tar.addr, metadata !5734, metadata !563), !dbg !5735
  store %struct.archive_entry_header_gnutar* %header, %struct.archive_entry_header_gnutar** %header.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry_header_gnutar** %header.addr, metadata !5736, metadata !563), !dbg !5737
  store i64* %unconsumed, i64** %unconsumed.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %unconsumed.addr, metadata !5738, metadata !563), !dbg !5739
  call void @llvm.dbg.declare(metadata i64* %bytes_read, metadata !5740, metadata !563), !dbg !5741
  call void @llvm.dbg.declare(metadata i8** %data, metadata !5742, metadata !563), !dbg !5743
  call void @llvm.dbg.declare(metadata %struct.extended** %ext, metadata !5744, metadata !563), !dbg !5745
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !5746
  %1 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !5748
  %2 = load %struct.archive_entry_header_gnutar*, %struct.archive_entry_header_gnutar** %header.addr, align 8, !dbg !5749
  %sparse = getelementptr inbounds %struct.archive_entry_header_gnutar, %struct.archive_entry_header_gnutar* %2, i32 0, i32 19, !dbg !5750
  %arraydecay = getelementptr inbounds [4 x %struct.gnu_sparse], [4 x %struct.gnu_sparse]* %sparse, i32 0, i32 0, !dbg !5749
  %call = call i32 @gnu_sparse_old_parse(%struct.archive_read* %0, %struct.tar* %1, %struct.gnu_sparse* %arraydecay, i32 4), !dbg !5751
  %cmp = icmp ne i32 %call, 0, !dbg !5752
  br i1 %cmp, label %if.then, label %if.end, !dbg !5753

if.then:                                          ; preds = %entry
  store i32 -30, i32* %retval, align 4, !dbg !5754
  br label %return, !dbg !5754

if.end:                                           ; preds = %entry
  %3 = load %struct.archive_entry_header_gnutar*, %struct.archive_entry_header_gnutar** %header.addr, align 8, !dbg !5755
  %isextended = getelementptr inbounds %struct.archive_entry_header_gnutar, %struct.archive_entry_header_gnutar* %3, i32 0, i32 20, !dbg !5757
  %arrayidx = getelementptr inbounds [1 x i8], [1 x i8]* %isextended, i64 0, i64 0, !dbg !5755
  %4 = load i8, i8* %arrayidx, align 1, !dbg !5755
  %conv = sext i8 %4 to i32, !dbg !5755
  %cmp1 = icmp eq i32 %conv, 0, !dbg !5758
  br i1 %cmp1, label %if.then3, label %if.end4, !dbg !5759

if.then3:                                         ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !5760
  br label %return, !dbg !5760

if.end4:                                          ; preds = %if.end
  br label %do.body, !dbg !5761

do.body:                                          ; preds = %do.cond, %if.end4
  %5 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !5762
  %6 = load i64*, i64** %unconsumed.addr, align 8, !dbg !5764
  call void @tar_flush_unconsumed(%struct.archive_read* %5, i64* %6), !dbg !5765
  %7 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !5766
  %call5 = call i8* @__archive_read_ahead(%struct.archive_read* %7, i64 512, i64* %bytes_read), !dbg !5767
  store i8* %call5, i8** %data, align 8, !dbg !5768
  %8 = load i64, i64* %bytes_read, align 8, !dbg !5769
  %cmp6 = icmp slt i64 %8, 0, !dbg !5771
  br i1 %cmp6, label %if.then8, label %if.end9, !dbg !5772

if.then8:                                         ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !5773
  br label %return, !dbg !5773

if.end9:                                          ; preds = %do.body
  %9 = load i64, i64* %bytes_read, align 8, !dbg !5774
  %cmp10 = icmp slt i64 %9, 512, !dbg !5776
  br i1 %cmp10, label %if.then12, label %if.end13, !dbg !5777

if.then12:                                        ; preds = %if.end9
  %10 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !5778
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %10, i32 0, i32 0, !dbg !5780
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 84, i8* getelementptr inbounds ([62 x i8], [62 x i8]* @.str.91, i32 0, i32 0)), !dbg !5781
  store i32 -30, i32* %retval, align 4, !dbg !5782
  br label %return, !dbg !5782

if.end13:                                         ; preds = %if.end9
  %11 = load i64*, i64** %unconsumed.addr, align 8, !dbg !5783
  store i64 512, i64* %11, align 8, !dbg !5784
  %12 = load i8*, i8** %data, align 8, !dbg !5785
  %13 = bitcast i8* %12 to %struct.extended*, !dbg !5786
  store %struct.extended* %13, %struct.extended** %ext, align 8, !dbg !5787
  %14 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !5788
  %15 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !5790
  %16 = load %struct.extended*, %struct.extended** %ext, align 8, !dbg !5791
  %sparse14 = getelementptr inbounds %struct.extended, %struct.extended* %16, i32 0, i32 0, !dbg !5792
  %arraydecay15 = getelementptr inbounds [21 x %struct.gnu_sparse], [21 x %struct.gnu_sparse]* %sparse14, i32 0, i32 0, !dbg !5791
  %call16 = call i32 @gnu_sparse_old_parse(%struct.archive_read* %14, %struct.tar* %15, %struct.gnu_sparse* %arraydecay15, i32 21), !dbg !5793
  %cmp17 = icmp ne i32 %call16, 0, !dbg !5794
  br i1 %cmp17, label %if.then19, label %if.end20, !dbg !5795

if.then19:                                        ; preds = %if.end13
  store i32 -30, i32* %retval, align 4, !dbg !5796
  br label %return, !dbg !5796

if.end20:                                         ; preds = %if.end13
  br label %do.cond, !dbg !5797

do.cond:                                          ; preds = %if.end20
  %17 = load %struct.extended*, %struct.extended** %ext, align 8, !dbg !5798
  %isextended21 = getelementptr inbounds %struct.extended, %struct.extended* %17, i32 0, i32 1, !dbg !5800
  %arrayidx22 = getelementptr inbounds [1 x i8], [1 x i8]* %isextended21, i64 0, i64 0, !dbg !5798
  %18 = load i8, i8* %arrayidx22, align 1, !dbg !5798
  %conv23 = sext i8 %18 to i32, !dbg !5798
  %cmp24 = icmp ne i32 %conv23, 0, !dbg !5801
  br i1 %cmp24, label %do.body, label %do.end, !dbg !5802

do.end:                                           ; preds = %do.cond
  %19 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !5803
  %sparse_list = getelementptr inbounds %struct.tar, %struct.tar* %19, i32 0, i32 19, !dbg !5805
  %20 = load %struct.sparse_block*, %struct.sparse_block** %sparse_list, align 8, !dbg !5805
  %cmp26 = icmp ne %struct.sparse_block* %20, null, !dbg !5806
  br i1 %cmp26, label %if.then28, label %if.end30, !dbg !5807

if.then28:                                        ; preds = %do.end
  %21 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !5808
  %sparse_list29 = getelementptr inbounds %struct.tar, %struct.tar* %21, i32 0, i32 19, !dbg !5809
  %22 = load %struct.sparse_block*, %struct.sparse_block** %sparse_list29, align 8, !dbg !5809
  %offset = getelementptr inbounds %struct.sparse_block, %struct.sparse_block* %22, i32 0, i32 1, !dbg !5810
  %23 = load i64, i64* %offset, align 8, !dbg !5810
  %24 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !5811
  %entry_offset = getelementptr inbounds %struct.tar, %struct.tar* %24, i32 0, i32 14, !dbg !5812
  store i64 %23, i64* %entry_offset, align 8, !dbg !5813
  br label %if.end30, !dbg !5811

if.end30:                                         ; preds = %if.then28, %do.end
  store i32 0, i32* %retval, align 4, !dbg !5814
  br label %return, !dbg !5814

return:                                           ; preds = %if.end30, %if.then19, %if.then12, %if.then8, %if.then3, %if.then
  %25 = load i32, i32* %retval, align 4, !dbg !5815
  ret i32 %25, !dbg !5815
}

declare void @archive_entry_set_mode(%struct.archive_entry*, i32) #2

declare i32 @_archive_entry_copy_hardlink_l(%struct.archive_entry*, i8*, i64, %struct.archive_string_conv*) #2

declare i64 @archive_entry_size(%struct.archive_entry*) #2

declare i32 @_archive_entry_copy_symlink_l(%struct.archive_entry*, i8*, i64, %struct.archive_string_conv*) #2

; Function Attrs: nounwind uwtable
define internal i32 @gnu_sparse_old_parse(%struct.archive_read* %a, %struct.tar* %tar, %struct.gnu_sparse* %sparse, i32 %length) #0 !dbg !522 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %tar.addr = alloca %struct.tar*, align 8
  %sparse.addr = alloca %struct.gnu_sparse*, align 8
  %length.addr = alloca i32, align 4
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !5816, metadata !563), !dbg !5817
  store %struct.tar* %tar, %struct.tar** %tar.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tar** %tar.addr, metadata !5818, metadata !563), !dbg !5819
  store %struct.gnu_sparse* %sparse, %struct.gnu_sparse** %sparse.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.gnu_sparse** %sparse.addr, metadata !5820, metadata !563), !dbg !5821
  store i32 %length, i32* %length.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %length.addr, metadata !5822, metadata !563), !dbg !5823
  br label %while.cond, !dbg !5824

while.cond:                                       ; preds = %if.end, %entry
  %0 = load i32, i32* %length.addr, align 4, !dbg !5825
  %cmp = icmp sgt i32 %0, 0, !dbg !5827
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !5828

land.rhs:                                         ; preds = %while.cond
  %1 = load %struct.gnu_sparse*, %struct.gnu_sparse** %sparse.addr, align 8, !dbg !5829
  %offset = getelementptr inbounds %struct.gnu_sparse, %struct.gnu_sparse* %1, i32 0, i32 0, !dbg !5831
  %arrayidx = getelementptr inbounds [12 x i8], [12 x i8]* %offset, i64 0, i64 0, !dbg !5829
  %2 = load i8, i8* %arrayidx, align 1, !dbg !5829
  %conv = sext i8 %2 to i32, !dbg !5829
  %cmp1 = icmp ne i32 %conv, 0, !dbg !5832
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond
  %3 = phi i1 [ false, %while.cond ], [ %cmp1, %land.rhs ]
  br i1 %3, label %while.body, label %while.end, !dbg !5833

while.body:                                       ; preds = %land.end
  %4 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !5835
  %5 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !5838
  %6 = load %struct.gnu_sparse*, %struct.gnu_sparse** %sparse.addr, align 8, !dbg !5839
  %offset3 = getelementptr inbounds %struct.gnu_sparse, %struct.gnu_sparse* %6, i32 0, i32 0, !dbg !5840
  %arraydecay = getelementptr inbounds [12 x i8], [12 x i8]* %offset3, i32 0, i32 0, !dbg !5839
  %call = call i64 @tar_atol(i8* %arraydecay, i64 12), !dbg !5841
  %7 = load %struct.gnu_sparse*, %struct.gnu_sparse** %sparse.addr, align 8, !dbg !5842
  %numbytes = getelementptr inbounds %struct.gnu_sparse, %struct.gnu_sparse* %7, i32 0, i32 1, !dbg !5843
  %arraydecay4 = getelementptr inbounds [12 x i8], [12 x i8]* %numbytes, i32 0, i32 0, !dbg !5842
  %call5 = call i64 @tar_atol(i8* %arraydecay4, i64 12), !dbg !5844
  %call6 = call i32 @gnu_add_sparse_entry(%struct.archive_read* %4, %struct.tar* %5, i64 %call, i64 %call5), !dbg !5845
  %cmp7 = icmp ne i32 %call6, 0, !dbg !5846
  br i1 %cmp7, label %if.then, label %if.end, !dbg !5847

if.then:                                          ; preds = %while.body
  store i32 -30, i32* %retval, align 4, !dbg !5848
  br label %return, !dbg !5848

if.end:                                           ; preds = %while.body
  %8 = load %struct.gnu_sparse*, %struct.gnu_sparse** %sparse.addr, align 8, !dbg !5849
  %incdec.ptr = getelementptr inbounds %struct.gnu_sparse, %struct.gnu_sparse* %8, i32 1, !dbg !5849
  store %struct.gnu_sparse* %incdec.ptr, %struct.gnu_sparse** %sparse.addr, align 8, !dbg !5849
  %9 = load i32, i32* %length.addr, align 4, !dbg !5850
  %dec = add nsw i32 %9, -1, !dbg !5850
  store i32 %dec, i32* %length.addr, align 4, !dbg !5850
  br label %while.cond, !dbg !5851

while.end:                                        ; preds = %land.end
  store i32 0, i32* %retval, align 4, !dbg !5853
  br label %return, !dbg !5853

return:                                           ; preds = %while.end, %if.then
  %10 = load i32, i32* %retval, align 4, !dbg !5854
  ret i32 %10, !dbg !5854
}

declare %struct.archive_string* @archive_strappend_char(%struct.archive_string*, i8 signext) #2

declare void @archive_entry_copy_mac_metadata(%struct.archive_entry*, i8*, i64) #2

; Function Attrs: nounwind uwtable
define internal i64 @gnu_sparse_10_atol(%struct.archive_read* %a, %struct.tar* %tar, i64* %remaining, i64* %unconsumed) #0 !dbg !533 {
entry:
  %retval = alloca i64, align 8
  %a.addr = alloca %struct.archive_read*, align 8
  %tar.addr = alloca %struct.tar*, align 8
  %remaining.addr = alloca i64*, align 8
  %unconsumed.addr = alloca i64*, align 8
  %l = alloca i64, align 8
  %limit = alloca i64, align 8
  %last_digit_limit = alloca i64, align 8
  %p = alloca i8*, align 8
  %bytes_read = alloca i64, align 8
  %base = alloca i32, align 4
  %digit = alloca i32, align 4
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !5855, metadata !563), !dbg !5856
  store %struct.tar* %tar, %struct.tar** %tar.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tar** %tar.addr, metadata !5857, metadata !563), !dbg !5858
  store i64* %remaining, i64** %remaining.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %remaining.addr, metadata !5859, metadata !563), !dbg !5860
  store i64* %unconsumed, i64** %unconsumed.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %unconsumed.addr, metadata !5861, metadata !563), !dbg !5862
  call void @llvm.dbg.declare(metadata i64* %l, metadata !5863, metadata !563), !dbg !5864
  call void @llvm.dbg.declare(metadata i64* %limit, metadata !5865, metadata !563), !dbg !5866
  call void @llvm.dbg.declare(metadata i64* %last_digit_limit, metadata !5867, metadata !563), !dbg !5868
  call void @llvm.dbg.declare(metadata i8** %p, metadata !5869, metadata !563), !dbg !5870
  call void @llvm.dbg.declare(metadata i64* %bytes_read, metadata !5871, metadata !563), !dbg !5872
  call void @llvm.dbg.declare(metadata i32* %base, metadata !5873, metadata !563), !dbg !5874
  call void @llvm.dbg.declare(metadata i32* %digit, metadata !5875, metadata !563), !dbg !5876
  store i32 10, i32* %base, align 4, !dbg !5877
  %0 = load i32, i32* %base, align 4, !dbg !5878
  %conv = sext i32 %0 to i64, !dbg !5878
  %div = sdiv i64 9223372036854775807, %conv, !dbg !5879
  store i64 %div, i64* %limit, align 8, !dbg !5880
  %1 = load i32, i32* %base, align 4, !dbg !5881
  %conv1 = sext i32 %1 to i64, !dbg !5881
  %rem = srem i64 9223372036854775807, %conv1, !dbg !5882
  store i64 %rem, i64* %last_digit_limit, align 8, !dbg !5883
  br label %do.body, !dbg !5884

do.body:                                          ; preds = %do.cond, %entry
  %2 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !5885
  %3 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !5887
  %4 = load i64*, i64** %remaining.addr, align 8, !dbg !5888
  %5 = load i64, i64* %4, align 8, !dbg !5888
  %cmp = icmp slt i64 %5, 100, !dbg !5888
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !5888

cond.true:                                        ; preds = %do.body
  %6 = load i64*, i64** %remaining.addr, align 8, !dbg !5889
  %7 = load i64, i64* %6, align 8, !dbg !5889
  br label %cond.end, !dbg !5889

cond.false:                                       ; preds = %do.body
  br label %cond.end, !dbg !5891

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ %7, %cond.true ], [ 100, %cond.false ], !dbg !5893
  %8 = load i64*, i64** %unconsumed.addr, align 8, !dbg !5895
  %call = call i64 @readline(%struct.archive_read* %2, %struct.tar* %3, i8** %p, i64 %cond, i64* %8), !dbg !5896
  store i64 %call, i64* %bytes_read, align 8, !dbg !5897
  %9 = load i64, i64* %bytes_read, align 8, !dbg !5898
  %cmp3 = icmp sle i64 %9, 0, !dbg !5900
  br i1 %cmp3, label %if.then, label %if.end, !dbg !5901

if.then:                                          ; preds = %cond.end
  store i64 -30, i64* %retval, align 8, !dbg !5902
  br label %return, !dbg !5902

if.end:                                           ; preds = %cond.end
  %10 = load i64, i64* %bytes_read, align 8, !dbg !5903
  %11 = load i64*, i64** %remaining.addr, align 8, !dbg !5904
  %12 = load i64, i64* %11, align 8, !dbg !5905
  %sub = sub nsw i64 %12, %10, !dbg !5905
  store i64 %sub, i64* %11, align 8, !dbg !5905
  br label %do.cond, !dbg !5906

do.cond:                                          ; preds = %if.end
  %13 = load i8*, i8** %p, align 8, !dbg !5907
  %arrayidx = getelementptr inbounds i8, i8* %13, i64 0, !dbg !5907
  %14 = load i8, i8* %arrayidx, align 1, !dbg !5907
  %conv5 = sext i8 %14 to i32, !dbg !5907
  %cmp6 = icmp eq i32 %conv5, 35, !dbg !5909
  br i1 %cmp6, label %do.body, label %do.end, !dbg !5910

do.end:                                           ; preds = %do.cond
  store i64 0, i64* %l, align 8, !dbg !5911
  br label %while.cond, !dbg !5912

while.cond:                                       ; preds = %if.end37, %do.end
  %15 = load i64, i64* %bytes_read, align 8, !dbg !5913
  %cmp8 = icmp sgt i64 %15, 0, !dbg !5914
  br i1 %cmp8, label %while.body, label %while.end, !dbg !5915

while.body:                                       ; preds = %while.cond
  %16 = load i8*, i8** %p, align 8, !dbg !5916
  %17 = load i8, i8* %16, align 1, !dbg !5919
  %conv10 = sext i8 %17 to i32, !dbg !5919
  %cmp11 = icmp eq i32 %conv10, 10, !dbg !5920
  br i1 %cmp11, label %if.then13, label %if.end14, !dbg !5921

if.then13:                                        ; preds = %while.body
  %18 = load i64, i64* %l, align 8, !dbg !5922
  store i64 %18, i64* %retval, align 8, !dbg !5923
  br label %return, !dbg !5923

if.end14:                                         ; preds = %while.body
  %19 = load i8*, i8** %p, align 8, !dbg !5924
  %20 = load i8, i8* %19, align 1, !dbg !5926
  %conv15 = sext i8 %20 to i32, !dbg !5926
  %cmp16 = icmp slt i32 %conv15, 48, !dbg !5927
  br i1 %cmp16, label %if.then21, label %lor.lhs.false, !dbg !5928

lor.lhs.false:                                    ; preds = %if.end14
  %21 = load i8*, i8** %p, align 8, !dbg !5929
  %22 = load i8, i8* %21, align 1, !dbg !5931
  %conv18 = sext i8 %22 to i32, !dbg !5931
  %23 = load i32, i32* %base, align 4, !dbg !5932
  %add = add nsw i32 48, %23, !dbg !5933
  %cmp19 = icmp sge i32 %conv18, %add, !dbg !5934
  br i1 %cmp19, label %if.then21, label %if.end22, !dbg !5935

if.then21:                                        ; preds = %lor.lhs.false, %if.end14
  store i64 -20, i64* %retval, align 8, !dbg !5936
  br label %return, !dbg !5936

if.end22:                                         ; preds = %lor.lhs.false
  %24 = load i8*, i8** %p, align 8, !dbg !5937
  %25 = load i8, i8* %24, align 1, !dbg !5938
  %conv23 = sext i8 %25 to i32, !dbg !5938
  %sub24 = sub nsw i32 %conv23, 48, !dbg !5939
  store i32 %sub24, i32* %digit, align 4, !dbg !5940
  %26 = load i64, i64* %l, align 8, !dbg !5941
  %27 = load i64, i64* %limit, align 8, !dbg !5943
  %cmp25 = icmp sgt i64 %26, %27, !dbg !5944
  br i1 %cmp25, label %if.then33, label %lor.lhs.false27, !dbg !5945

lor.lhs.false27:                                  ; preds = %if.end22
  %28 = load i64, i64* %l, align 8, !dbg !5946
  %29 = load i64, i64* %limit, align 8, !dbg !5948
  %cmp28 = icmp eq i64 %28, %29, !dbg !5949
  br i1 %cmp28, label %land.lhs.true, label %if.else, !dbg !5950

land.lhs.true:                                    ; preds = %lor.lhs.false27
  %30 = load i32, i32* %digit, align 4, !dbg !5951
  %conv30 = sext i32 %30 to i64, !dbg !5951
  %31 = load i64, i64* %last_digit_limit, align 8, !dbg !5953
  %cmp31 = icmp sgt i64 %conv30, %31, !dbg !5954
  br i1 %cmp31, label %if.then33, label %if.else, !dbg !5955

if.then33:                                        ; preds = %land.lhs.true, %if.end22
  store i64 9223372036854775807, i64* %l, align 8, !dbg !5956
  br label %if.end37, !dbg !5957

if.else:                                          ; preds = %land.lhs.true, %lor.lhs.false27
  %32 = load i64, i64* %l, align 8, !dbg !5958
  %33 = load i32, i32* %base, align 4, !dbg !5959
  %conv34 = sext i32 %33 to i64, !dbg !5959
  %mul = mul nsw i64 %32, %conv34, !dbg !5960
  %34 = load i32, i32* %digit, align 4, !dbg !5961
  %conv35 = sext i32 %34 to i64, !dbg !5961
  %add36 = add nsw i64 %mul, %conv35, !dbg !5962
  store i64 %add36, i64* %l, align 8, !dbg !5963
  br label %if.end37

if.end37:                                         ; preds = %if.else, %if.then33
  %35 = load i8*, i8** %p, align 8, !dbg !5964
  %incdec.ptr = getelementptr inbounds i8, i8* %35, i32 1, !dbg !5964
  store i8* %incdec.ptr, i8** %p, align 8, !dbg !5964
  %36 = load i64, i64* %bytes_read, align 8, !dbg !5965
  %dec = add nsw i64 %36, -1, !dbg !5965
  store i64 %dec, i64* %bytes_read, align 8, !dbg !5965
  br label %while.cond, !dbg !5966

while.end:                                        ; preds = %while.cond
  store i64 -20, i64* %retval, align 8, !dbg !5968
  br label %return, !dbg !5968

return:                                           ; preds = %while.end, %if.then21, %if.then13, %if.then
  %37 = load i64, i64* %retval, align 8, !dbg !5969
  ret i64 %37, !dbg !5969
}

; Function Attrs: nounwind uwtable
define internal i64 @readline(%struct.archive_read* %a, %struct.tar* %tar, i8** %start, i64 %limit, i64* %unconsumed) #0 !dbg !536 {
entry:
  %retval = alloca i64, align 8
  %a.addr = alloca %struct.archive_read*, align 8
  %tar.addr = alloca %struct.tar*, align 8
  %start.addr = alloca i8**, align 8
  %limit.addr = alloca i64, align 8
  %unconsumed.addr = alloca i64*, align 8
  %bytes_read = alloca i64, align 8
  %total_size = alloca i64, align 8
  %t = alloca i8*, align 8
  %s = alloca i8*, align 8
  %p = alloca i8*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !5970, metadata !563), !dbg !5971
  store %struct.tar* %tar, %struct.tar** %tar.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tar** %tar.addr, metadata !5972, metadata !563), !dbg !5973
  store i8** %start, i8*** %start.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %start.addr, metadata !5974, metadata !563), !dbg !5975
  store i64 %limit, i64* %limit.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %limit.addr, metadata !5976, metadata !563), !dbg !5977
  store i64* %unconsumed, i64** %unconsumed.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %unconsumed.addr, metadata !5978, metadata !563), !dbg !5979
  call void @llvm.dbg.declare(metadata i64* %bytes_read, metadata !5980, metadata !563), !dbg !5981
  call void @llvm.dbg.declare(metadata i64* %total_size, metadata !5982, metadata !563), !dbg !5983
  store i64 0, i64* %total_size, align 8, !dbg !5983
  call void @llvm.dbg.declare(metadata i8** %t, metadata !5984, metadata !563), !dbg !5985
  call void @llvm.dbg.declare(metadata i8** %s, metadata !5986, metadata !563), !dbg !5987
  call void @llvm.dbg.declare(metadata i8** %p, metadata !5988, metadata !563), !dbg !5989
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !5990
  %1 = load i64*, i64** %unconsumed.addr, align 8, !dbg !5991
  call void @tar_flush_unconsumed(%struct.archive_read* %0, i64* %1), !dbg !5992
  %2 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !5993
  %call = call i8* @__archive_read_ahead(%struct.archive_read* %2, i64 1, i64* %bytes_read), !dbg !5994
  store i8* %call, i8** %t, align 8, !dbg !5995
  %3 = load i64, i64* %bytes_read, align 8, !dbg !5996
  %cmp = icmp sle i64 %3, 0, !dbg !5998
  br i1 %cmp, label %if.then, label %if.end, !dbg !5999

if.then:                                          ; preds = %entry
  store i64 -30, i64* %retval, align 8, !dbg !6000
  br label %return, !dbg !6000

if.end:                                           ; preds = %entry
  %4 = load i8*, i8** %t, align 8, !dbg !6001
  store i8* %4, i8** %s, align 8, !dbg !6002
  %5 = load i8*, i8** %t, align 8, !dbg !6003
  %6 = load i64, i64* %bytes_read, align 8, !dbg !6004
  %call1 = call i8* @memchr(i8* %5, i32 10, i64 %6) #8, !dbg !6005
  store i8* %call1, i8** %p, align 8, !dbg !6006
  %7 = load i8*, i8** %p, align 8, !dbg !6007
  %cmp2 = icmp ne i8* %7, null, !dbg !6009
  br i1 %cmp2, label %if.then3, label %if.end7, !dbg !6010

if.then3:                                         ; preds = %if.end
  %8 = load i8*, i8** %p, align 8, !dbg !6011
  %add.ptr = getelementptr inbounds i8, i8* %8, i64 1, !dbg !6013
  %9 = load i8*, i8** %s, align 8, !dbg !6014
  %sub.ptr.lhs.cast = ptrtoint i8* %add.ptr to i64, !dbg !6015
  %sub.ptr.rhs.cast = ptrtoint i8* %9 to i64, !dbg !6015
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !6015
  store i64 %sub.ptr.sub, i64* %bytes_read, align 8, !dbg !6016
  %10 = load i64, i64* %bytes_read, align 8, !dbg !6017
  %11 = load i64, i64* %limit.addr, align 8, !dbg !6019
  %cmp4 = icmp sgt i64 %10, %11, !dbg !6020
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !6021

if.then5:                                         ; preds = %if.then3
  %12 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !6022
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %12, i32 0, i32 0, !dbg !6024
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 84, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.92, i32 0, i32 0)), !dbg !6025
  store i64 -30, i64* %retval, align 8, !dbg !6026
  br label %return, !dbg !6026

if.end6:                                          ; preds = %if.then3
  %13 = load i64, i64* %bytes_read, align 8, !dbg !6027
  %14 = load i64*, i64** %unconsumed.addr, align 8, !dbg !6028
  store i64 %13, i64* %14, align 8, !dbg !6029
  %15 = load i8*, i8** %s, align 8, !dbg !6030
  %16 = load i8**, i8*** %start.addr, align 8, !dbg !6031
  store i8* %15, i8** %16, align 8, !dbg !6032
  %17 = load i64, i64* %bytes_read, align 8, !dbg !6033
  store i64 %17, i64* %retval, align 8, !dbg !6034
  br label %return, !dbg !6034

if.end7:                                          ; preds = %if.end
  %18 = load i64, i64* %bytes_read, align 8, !dbg !6035
  %19 = load i64*, i64** %unconsumed.addr, align 8, !dbg !6036
  store i64 %18, i64* %19, align 8, !dbg !6037
  br label %for.cond, !dbg !6038

for.cond:                                         ; preds = %if.end38, %if.end7
  %20 = load i64, i64* %total_size, align 8, !dbg !6039
  %21 = load i64, i64* %bytes_read, align 8, !dbg !6044
  %add = add nsw i64 %20, %21, !dbg !6045
  %22 = load i64, i64* %limit.addr, align 8, !dbg !6046
  %cmp8 = icmp sgt i64 %add, %22, !dbg !6047
  br i1 %cmp8, label %if.then9, label %if.end11, !dbg !6048

if.then9:                                         ; preds = %for.cond
  %23 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !6049
  %archive10 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %23, i32 0, i32 0, !dbg !6051
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive10, i32 84, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.92, i32 0, i32 0)), !dbg !6052
  store i64 -30, i64* %retval, align 8, !dbg !6053
  br label %return, !dbg !6053

if.end11:                                         ; preds = %for.cond
  %24 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !6054
  %line = getelementptr inbounds %struct.tar, %struct.tar* %24, i32 0, i32 10, !dbg !6056
  %25 = load i64, i64* %total_size, align 8, !dbg !6057
  %26 = load i64, i64* %bytes_read, align 8, !dbg !6058
  %add12 = add nsw i64 %25, %26, !dbg !6059
  %call13 = call %struct.archive_string* @archive_string_ensure(%struct.archive_string* %line, i64 %add12), !dbg !6060
  %cmp14 = icmp eq %struct.archive_string* %call13, null, !dbg !6061
  br i1 %cmp14, label %if.then15, label %if.end17, !dbg !6062

if.then15:                                        ; preds = %if.end11
  %27 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !6063
  %archive16 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %27, i32 0, i32 0, !dbg !6065
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive16, i32 12, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.93, i32 0, i32 0)), !dbg !6066
  store i64 -30, i64* %retval, align 8, !dbg !6067
  br label %return, !dbg !6067

if.end17:                                         ; preds = %if.end11
  %28 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !6068
  %line18 = getelementptr inbounds %struct.tar, %struct.tar* %28, i32 0, i32 10, !dbg !6069
  %s19 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %line18, i32 0, i32 0, !dbg !6070
  %29 = load i8*, i8** %s19, align 8, !dbg !6070
  %30 = load i64, i64* %total_size, align 8, !dbg !6071
  %add.ptr20 = getelementptr inbounds i8, i8* %29, i64 %30, !dbg !6072
  %31 = load i8*, i8** %t, align 8, !dbg !6073
  %32 = load i64, i64* %bytes_read, align 8, !dbg !6074
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %add.ptr20, i8* %31, i64 %32, i32 1, i1 false), !dbg !6075
  %33 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !6076
  %34 = load i64*, i64** %unconsumed.addr, align 8, !dbg !6077
  call void @tar_flush_unconsumed(%struct.archive_read* %33, i64* %34), !dbg !6078
  %35 = load i64, i64* %bytes_read, align 8, !dbg !6079
  %36 = load i64, i64* %total_size, align 8, !dbg !6080
  %add21 = add nsw i64 %36, %35, !dbg !6080
  store i64 %add21, i64* %total_size, align 8, !dbg !6080
  %37 = load i8*, i8** %p, align 8, !dbg !6081
  %cmp22 = icmp ne i8* %37, null, !dbg !6083
  br i1 %cmp22, label %if.then23, label %if.end26, !dbg !6084

if.then23:                                        ; preds = %if.end17
  %38 = load %struct.tar*, %struct.tar** %tar.addr, align 8, !dbg !6085
  %line24 = getelementptr inbounds %struct.tar, %struct.tar* %38, i32 0, i32 10, !dbg !6087
  %s25 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %line24, i32 0, i32 0, !dbg !6088
  %39 = load i8*, i8** %s25, align 8, !dbg !6088
  %40 = load i8**, i8*** %start.addr, align 8, !dbg !6089
  store i8* %39, i8** %40, align 8, !dbg !6090
  %41 = load i64, i64* %total_size, align 8, !dbg !6091
  store i64 %41, i64* %retval, align 8, !dbg !6092
  br label %return, !dbg !6092

if.end26:                                         ; preds = %if.end17
  %42 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !6093
  %call27 = call i8* @__archive_read_ahead(%struct.archive_read* %42, i64 1, i64* %bytes_read), !dbg !6094
  store i8* %call27, i8** %t, align 8, !dbg !6095
  %43 = load i64, i64* %bytes_read, align 8, !dbg !6096
  %cmp28 = icmp sle i64 %43, 0, !dbg !6098
  br i1 %cmp28, label %if.then29, label %if.end30, !dbg !6099

if.then29:                                        ; preds = %if.end26
  store i64 -30, i64* %retval, align 8, !dbg !6100
  br label %return, !dbg !6100

if.end30:                                         ; preds = %if.end26
  %44 = load i8*, i8** %t, align 8, !dbg !6101
  store i8* %44, i8** %s, align 8, !dbg !6102
  %45 = load i8*, i8** %t, align 8, !dbg !6103
  %46 = load i64, i64* %bytes_read, align 8, !dbg !6104
  %call31 = call i8* @memchr(i8* %45, i32 10, i64 %46) #8, !dbg !6105
  store i8* %call31, i8** %p, align 8, !dbg !6106
  %47 = load i8*, i8** %p, align 8, !dbg !6107
  %cmp32 = icmp ne i8* %47, null, !dbg !6109
  br i1 %cmp32, label %if.then33, label %if.end38, !dbg !6110

if.then33:                                        ; preds = %if.end30
  %48 = load i8*, i8** %p, align 8, !dbg !6111
  %add.ptr34 = getelementptr inbounds i8, i8* %48, i64 1, !dbg !6113
  %49 = load i8*, i8** %s, align 8, !dbg !6114
  %sub.ptr.lhs.cast35 = ptrtoint i8* %add.ptr34 to i64, !dbg !6115
  %sub.ptr.rhs.cast36 = ptrtoint i8* %49 to i64, !dbg !6115
  %sub.ptr.sub37 = sub i64 %sub.ptr.lhs.cast35, %sub.ptr.rhs.cast36, !dbg !6115
  store i64 %sub.ptr.sub37, i64* %bytes_read, align 8, !dbg !6116
  br label %if.end38, !dbg !6117

if.end38:                                         ; preds = %if.then33, %if.end30
  %50 = load i64, i64* %bytes_read, align 8, !dbg !6118
  %51 = load i64*, i64** %unconsumed.addr, align 8, !dbg !6119
  store i64 %50, i64* %51, align 8, !dbg !6120
  br label %for.cond, !dbg !6121

return:                                           ; preds = %if.then29, %if.then23, %if.then15, %if.then9, %if.end6, %if.then5, %if.then
  %52 = load i64, i64* %retval, align 8, !dbg !6123
  ret i64 %52, !dbg !6123
}

; Function Attrs: nounwind readonly
declare i8* @memchr(i8*, i32, i64) #4

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
!llvm.module.flags = !{!559, !560}
!llvm.ident = !{!561}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !438, globals: !548)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_support_format_tar.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !291, !122, !336, !380, !23, !382, !383, !52, !384, !386, !45, !420, !13, !95, !422, !38, !80, !314}
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
!292 = !DICompositeType(tag: DW_TAG_structure_type, name: "tar", file: !1, line: 120, size: 3520, align: 64, elements: !293)
!293 = !{!294, !295, !296, !297, !298, !299, !300, !301, !302, !303, !304, !305, !306, !307, !308, !309, !310, !311, !312, !313, !321, !322, !323, !324, !325, !326, !327, !328, !329, !330, !331, !332, !333, !334, !335}
!294 = !DIDerivedType(tag: DW_TAG_member, name: "acl_text", scope: !292, file: !1, line: 121, baseType: !91, size: 192, align: 64)
!295 = !DIDerivedType(tag: DW_TAG_member, name: "entry_pathname", scope: !292, file: !1, line: 122, baseType: !91, size: 192, align: 64, offset: 192)
!296 = !DIDerivedType(tag: DW_TAG_member, name: "entry_pathname_override", scope: !292, file: !1, line: 124, baseType: !91, size: 192, align: 64, offset: 384)
!297 = !DIDerivedType(tag: DW_TAG_member, name: "entry_linkpath", scope: !292, file: !1, line: 125, baseType: !91, size: 192, align: 64, offset: 576)
!298 = !DIDerivedType(tag: DW_TAG_member, name: "entry_uname", scope: !292, file: !1, line: 126, baseType: !91, size: 192, align: 64, offset: 768)
!299 = !DIDerivedType(tag: DW_TAG_member, name: "entry_gname", scope: !292, file: !1, line: 127, baseType: !91, size: 192, align: 64, offset: 960)
!300 = !DIDerivedType(tag: DW_TAG_member, name: "longlink", scope: !292, file: !1, line: 128, baseType: !91, size: 192, align: 64, offset: 1152)
!301 = !DIDerivedType(tag: DW_TAG_member, name: "longname", scope: !292, file: !1, line: 129, baseType: !91, size: 192, align: 64, offset: 1344)
!302 = !DIDerivedType(tag: DW_TAG_member, name: "pax_header", scope: !292, file: !1, line: 130, baseType: !91, size: 192, align: 64, offset: 1536)
!303 = !DIDerivedType(tag: DW_TAG_member, name: "pax_global", scope: !292, file: !1, line: 131, baseType: !91, size: 192, align: 64, offset: 1728)
!304 = !DIDerivedType(tag: DW_TAG_member, name: "line", scope: !292, file: !1, line: 132, baseType: !91, size: 192, align: 64, offset: 1920)
!305 = !DIDerivedType(tag: DW_TAG_member, name: "pax_hdrcharset_binary", scope: !292, file: !1, line: 133, baseType: !23, size: 32, align: 32, offset: 2112)
!306 = !DIDerivedType(tag: DW_TAG_member, name: "header_recursion_depth", scope: !292, file: !1, line: 134, baseType: !23, size: 32, align: 32, offset: 2144)
!307 = !DIDerivedType(tag: DW_TAG_member, name: "entry_bytes_remaining", scope: !292, file: !1, line: 135, baseType: !52, size: 64, align: 64, offset: 2176)
!308 = !DIDerivedType(tag: DW_TAG_member, name: "entry_offset", scope: !292, file: !1, line: 136, baseType: !52, size: 64, align: 64, offset: 2240)
!309 = !DIDerivedType(tag: DW_TAG_member, name: "entry_padding", scope: !292, file: !1, line: 137, baseType: !52, size: 64, align: 64, offset: 2304)
!310 = !DIDerivedType(tag: DW_TAG_member, name: "entry_bytes_unconsumed", scope: !292, file: !1, line: 138, baseType: !52, size: 64, align: 64, offset: 2368)
!311 = !DIDerivedType(tag: DW_TAG_member, name: "realsize", scope: !292, file: !1, line: 139, baseType: !52, size: 64, align: 64, offset: 2432)
!312 = !DIDerivedType(tag: DW_TAG_member, name: "sparse_allowed", scope: !292, file: !1, line: 140, baseType: !23, size: 32, align: 32, offset: 2496)
!313 = !DIDerivedType(tag: DW_TAG_member, name: "sparse_list", scope: !292, file: !1, line: 141, baseType: !314, size: 64, align: 64, offset: 2560)
!314 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !315, size: 64, align: 64)
!315 = !DICompositeType(tag: DW_TAG_structure_type, name: "sparse_block", file: !1, line: 113, size: 256, align: 64, elements: !316)
!316 = !{!317, !318, !319, !320}
!317 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !315, file: !1, line: 114, baseType: !314, size: 64, align: 64)
!318 = !DIDerivedType(tag: DW_TAG_member, name: "offset", scope: !315, file: !1, line: 115, baseType: !52, size: 64, align: 64, offset: 64)
!319 = !DIDerivedType(tag: DW_TAG_member, name: "remaining", scope: !315, file: !1, line: 116, baseType: !52, size: 64, align: 64, offset: 128)
!320 = !DIDerivedType(tag: DW_TAG_member, name: "hole", scope: !315, file: !1, line: 117, baseType: !23, size: 32, align: 32, offset: 192)
!321 = !DIDerivedType(tag: DW_TAG_member, name: "sparse_last", scope: !292, file: !1, line: 142, baseType: !314, size: 64, align: 64, offset: 2624)
!322 = !DIDerivedType(tag: DW_TAG_member, name: "sparse_offset", scope: !292, file: !1, line: 143, baseType: !52, size: 64, align: 64, offset: 2688)
!323 = !DIDerivedType(tag: DW_TAG_member, name: "sparse_numbytes", scope: !292, file: !1, line: 144, baseType: !52, size: 64, align: 64, offset: 2752)
!324 = !DIDerivedType(tag: DW_TAG_member, name: "sparse_gnu_major", scope: !292, file: !1, line: 145, baseType: !23, size: 32, align: 32, offset: 2816)
!325 = !DIDerivedType(tag: DW_TAG_member, name: "sparse_gnu_minor", scope: !292, file: !1, line: 146, baseType: !23, size: 32, align: 32, offset: 2848)
!326 = !DIDerivedType(tag: DW_TAG_member, name: "sparse_gnu_pending", scope: !292, file: !1, line: 147, baseType: !82, size: 8, align: 8, offset: 2880)
!327 = !DIDerivedType(tag: DW_TAG_member, name: "localname", scope: !292, file: !1, line: 149, baseType: !91, size: 192, align: 64, offset: 2944)
!328 = !DIDerivedType(tag: DW_TAG_member, name: "opt_sconv", scope: !292, file: !1, line: 150, baseType: !102, size: 64, align: 64, offset: 3136)
!329 = !DIDerivedType(tag: DW_TAG_member, name: "sconv", scope: !292, file: !1, line: 151, baseType: !102, size: 64, align: 64, offset: 3200)
!330 = !DIDerivedType(tag: DW_TAG_member, name: "sconv_acl", scope: !292, file: !1, line: 152, baseType: !102, size: 64, align: 64, offset: 3264)
!331 = !DIDerivedType(tag: DW_TAG_member, name: "sconv_default", scope: !292, file: !1, line: 153, baseType: !102, size: 64, align: 64, offset: 3328)
!332 = !DIDerivedType(tag: DW_TAG_member, name: "init_default_conversion", scope: !292, file: !1, line: 154, baseType: !23, size: 32, align: 32, offset: 3392)
!333 = !DIDerivedType(tag: DW_TAG_member, name: "compat_2x", scope: !292, file: !1, line: 155, baseType: !23, size: 32, align: 32, offset: 3424)
!334 = !DIDerivedType(tag: DW_TAG_member, name: "process_mac_extensions", scope: !292, file: !1, line: 156, baseType: !23, size: 32, align: 32, offset: 3456)
!335 = !DIDerivedType(tag: DW_TAG_member, name: "read_concatenated_archives", scope: !292, file: !1, line: 157, baseType: !23, size: 32, align: 32, offset: 3488)
!336 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !337, size: 64, align: 64)
!337 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !338)
!338 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_entry_header_ustar", file: !1, line: 54, size: 4000, align: 8, elements: !339)
!339 = !{!340, !344, !348, !349, !350, !354, !355, !356, !360, !361, !365, !369, !373, !374, !375, !376}
!340 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !338, file: !1, line: 55, baseType: !341, size: 800, align: 8)
!341 = !DICompositeType(tag: DW_TAG_array_type, baseType: !82, size: 800, align: 8, elements: !342)
!342 = !{!343}
!343 = !DISubrange(count: 100)
!344 = !DIDerivedType(tag: DW_TAG_member, name: "mode", scope: !338, file: !1, line: 56, baseType: !345, size: 64, align: 8, offset: 800)
!345 = !DICompositeType(tag: DW_TAG_array_type, baseType: !82, size: 64, align: 8, elements: !346)
!346 = !{!347}
!347 = !DISubrange(count: 8)
!348 = !DIDerivedType(tag: DW_TAG_member, name: "uid", scope: !338, file: !1, line: 57, baseType: !345, size: 64, align: 8, offset: 864)
!349 = !DIDerivedType(tag: DW_TAG_member, name: "gid", scope: !338, file: !1, line: 58, baseType: !345, size: 64, align: 8, offset: 928)
!350 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !338, file: !1, line: 59, baseType: !351, size: 96, align: 8, offset: 992)
!351 = !DICompositeType(tag: DW_TAG_array_type, baseType: !82, size: 96, align: 8, elements: !352)
!352 = !{!353}
!353 = !DISubrange(count: 12)
!354 = !DIDerivedType(tag: DW_TAG_member, name: "mtime", scope: !338, file: !1, line: 60, baseType: !351, size: 96, align: 8, offset: 1088)
!355 = !DIDerivedType(tag: DW_TAG_member, name: "checksum", scope: !338, file: !1, line: 61, baseType: !345, size: 64, align: 8, offset: 1184)
!356 = !DIDerivedType(tag: DW_TAG_member, name: "typeflag", scope: !338, file: !1, line: 62, baseType: !357, size: 8, align: 8, offset: 1248)
!357 = !DICompositeType(tag: DW_TAG_array_type, baseType: !82, size: 8, align: 8, elements: !358)
!358 = !{!359}
!359 = !DISubrange(count: 1)
!360 = !DIDerivedType(tag: DW_TAG_member, name: "linkname", scope: !338, file: !1, line: 63, baseType: !341, size: 800, align: 8, offset: 1256)
!361 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !338, file: !1, line: 64, baseType: !362, size: 48, align: 8, offset: 2056)
!362 = !DICompositeType(tag: DW_TAG_array_type, baseType: !82, size: 48, align: 8, elements: !363)
!363 = !{!364}
!364 = !DISubrange(count: 6)
!365 = !DIDerivedType(tag: DW_TAG_member, name: "version", scope: !338, file: !1, line: 65, baseType: !366, size: 16, align: 8, offset: 2104)
!366 = !DICompositeType(tag: DW_TAG_array_type, baseType: !82, size: 16, align: 8, elements: !367)
!367 = !{!368}
!368 = !DISubrange(count: 2)
!369 = !DIDerivedType(tag: DW_TAG_member, name: "uname", scope: !338, file: !1, line: 66, baseType: !370, size: 256, align: 8, offset: 2120)
!370 = !DICompositeType(tag: DW_TAG_array_type, baseType: !82, size: 256, align: 8, elements: !371)
!371 = !{!372}
!372 = !DISubrange(count: 32)
!373 = !DIDerivedType(tag: DW_TAG_member, name: "gname", scope: !338, file: !1, line: 67, baseType: !370, size: 256, align: 8, offset: 2376)
!374 = !DIDerivedType(tag: DW_TAG_member, name: "rdevmajor", scope: !338, file: !1, line: 68, baseType: !345, size: 64, align: 8, offset: 2632)
!375 = !DIDerivedType(tag: DW_TAG_member, name: "rdevminor", scope: !338, file: !1, line: 69, baseType: !345, size: 64, align: 8, offset: 2696)
!376 = !DIDerivedType(tag: DW_TAG_member, name: "prefix", scope: !338, file: !1, line: 70, baseType: !377, size: 1240, align: 8, offset: 2760)
!377 = !DICompositeType(tag: DW_TAG_array_type, baseType: !82, size: 1240, align: 8, elements: !378)
!378 = !{!379}
!379 = !DISubrange(count: 155)
!380 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !381, size: 64, align: 64)
!381 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !382)
!382 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!383 = !DIBasicType(name: "signed char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!384 = !DIDerivedType(tag: DW_TAG_typedef, name: "mode_t", file: !39, line: 70, baseType: !385)
!385 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !41, line: 129, baseType: !13)
!386 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !387, size: 64, align: 64)
!387 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !388)
!388 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_entry_header_gnutar", file: !1, line: 81, size: 3960, align: 8, elements: !389)
!389 = !{!390, !391, !392, !393, !394, !395, !396, !397, !398, !399, !400, !401, !402, !403, !404, !405, !406, !407, !411, !412, !418, !419}
!390 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !388, file: !1, line: 82, baseType: !341, size: 800, align: 8)
!391 = !DIDerivedType(tag: DW_TAG_member, name: "mode", scope: !388, file: !1, line: 83, baseType: !345, size: 64, align: 8, offset: 800)
!392 = !DIDerivedType(tag: DW_TAG_member, name: "uid", scope: !388, file: !1, line: 84, baseType: !345, size: 64, align: 8, offset: 864)
!393 = !DIDerivedType(tag: DW_TAG_member, name: "gid", scope: !388, file: !1, line: 85, baseType: !345, size: 64, align: 8, offset: 928)
!394 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !388, file: !1, line: 86, baseType: !351, size: 96, align: 8, offset: 992)
!395 = !DIDerivedType(tag: DW_TAG_member, name: "mtime", scope: !388, file: !1, line: 87, baseType: !351, size: 96, align: 8, offset: 1088)
!396 = !DIDerivedType(tag: DW_TAG_member, name: "checksum", scope: !388, file: !1, line: 88, baseType: !345, size: 64, align: 8, offset: 1184)
!397 = !DIDerivedType(tag: DW_TAG_member, name: "typeflag", scope: !388, file: !1, line: 89, baseType: !357, size: 8, align: 8, offset: 1248)
!398 = !DIDerivedType(tag: DW_TAG_member, name: "linkname", scope: !388, file: !1, line: 90, baseType: !341, size: 800, align: 8, offset: 1256)
!399 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !388, file: !1, line: 91, baseType: !345, size: 64, align: 8, offset: 2056)
!400 = !DIDerivedType(tag: DW_TAG_member, name: "uname", scope: !388, file: !1, line: 92, baseType: !370, size: 256, align: 8, offset: 2120)
!401 = !DIDerivedType(tag: DW_TAG_member, name: "gname", scope: !388, file: !1, line: 93, baseType: !370, size: 256, align: 8, offset: 2376)
!402 = !DIDerivedType(tag: DW_TAG_member, name: "rdevmajor", scope: !388, file: !1, line: 94, baseType: !345, size: 64, align: 8, offset: 2632)
!403 = !DIDerivedType(tag: DW_TAG_member, name: "rdevminor", scope: !388, file: !1, line: 95, baseType: !345, size: 64, align: 8, offset: 2696)
!404 = !DIDerivedType(tag: DW_TAG_member, name: "atime", scope: !388, file: !1, line: 96, baseType: !351, size: 96, align: 8, offset: 2760)
!405 = !DIDerivedType(tag: DW_TAG_member, name: "ctime", scope: !388, file: !1, line: 97, baseType: !351, size: 96, align: 8, offset: 2856)
!406 = !DIDerivedType(tag: DW_TAG_member, name: "offset", scope: !388, file: !1, line: 98, baseType: !351, size: 96, align: 8, offset: 2952)
!407 = !DIDerivedType(tag: DW_TAG_member, name: "longnames", scope: !388, file: !1, line: 99, baseType: !408, size: 32, align: 8, offset: 3048)
!408 = !DICompositeType(tag: DW_TAG_array_type, baseType: !82, size: 32, align: 8, elements: !409)
!409 = !{!410}
!410 = !DISubrange(count: 4)
!411 = !DIDerivedType(tag: DW_TAG_member, name: "unused", scope: !388, file: !1, line: 100, baseType: !357, size: 8, align: 8, offset: 3080)
!412 = !DIDerivedType(tag: DW_TAG_member, name: "sparse", scope: !388, file: !1, line: 101, baseType: !413, size: 768, align: 8, offset: 3088)
!413 = !DICompositeType(tag: DW_TAG_array_type, baseType: !414, size: 768, align: 8, elements: !409)
!414 = !DICompositeType(tag: DW_TAG_structure_type, name: "gnu_sparse", file: !1, line: 76, size: 192, align: 8, elements: !415)
!415 = !{!416, !417}
!416 = !DIDerivedType(tag: DW_TAG_member, name: "offset", scope: !414, file: !1, line: 77, baseType: !351, size: 96, align: 8)
!417 = !DIDerivedType(tag: DW_TAG_member, name: "numbytes", scope: !414, file: !1, line: 78, baseType: !351, size: 96, align: 8, offset: 96)
!418 = !DIDerivedType(tag: DW_TAG_member, name: "isextended", scope: !388, file: !1, line: 102, baseType: !357, size: 8, align: 8, offset: 3856)
!419 = !DIDerivedType(tag: DW_TAG_member, name: "realsize", scope: !388, file: !1, line: 103, baseType: !351, size: 96, align: 8, offset: 3864)
!420 = !DIDerivedType(tag: DW_TAG_typedef, name: "dev_t", file: !39, line: 60, baseType: !421)
!421 = !DIDerivedType(tag: DW_TAG_typedef, name: "__dev_t", file: !41, line: 124, baseType: !47)
!422 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !423, size: 64, align: 64)
!423 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !424)
!424 = !DICompositeType(tag: DW_TAG_structure_type, name: "extended", scope: !425, file: !1, line: 2280, size: 4096, align: 8, elements: !428)
!425 = distinct !DISubprogram(name: "gnu_sparse_old_read", scope: !1, file: !1, line: 2275, type: !426, isLocal: true, isDefinition: true, scopeLine: 2277, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!426 = !DISubroutineType(types: !427)
!427 = !{!23, !4, !291, !386, !65}
!428 = !{!429, !433, !434}
!429 = !DIDerivedType(tag: DW_TAG_member, name: "sparse", scope: !424, file: !1, line: 2281, baseType: !430, size: 4032, align: 8)
!430 = !DICompositeType(tag: DW_TAG_array_type, baseType: !414, size: 4032, align: 8, elements: !431)
!431 = !{!432}
!432 = !DISubrange(count: 21)
!433 = !DIDerivedType(tag: DW_TAG_member, name: "isextended", scope: !424, file: !1, line: 2282, baseType: !357, size: 8, align: 8, offset: 4032)
!434 = !DIDerivedType(tag: DW_TAG_member, name: "padding", scope: !424, file: !1, line: 2283, baseType: !435, size: 56, align: 8, offset: 4040)
!435 = !DICompositeType(tag: DW_TAG_array_type, baseType: !82, size: 56, align: 8, elements: !436)
!436 = !{!437}
!437 = !DISubrange(count: 7)
!438 = !{!439, !440, !441, !442, !445, !446, !449, !452, !455, !456, !457, !460, !463, !464, !465, !468, !471, !475, !476, !477, !478, !481, !482, !483, !486, !489, !490, !493, !497, !500, !503, !506, !509, !512, !515, !518, !519, !425, !522, !527, !528, !529, !530, !533, !536, !540, !543, !546, !547}
!439 = distinct !DISubprogram(name: "archive_read_support_format_gnutar", scope: !1, file: !1, line: 234, type: !21, isLocal: false, isDefinition: true, scopeLine: 235, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!440 = distinct !DISubprogram(name: "archive_read_support_format_tar", scope: !1, file: !1, line: 243, type: !21, isLocal: false, isDefinition: true, scopeLine: 244, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!441 = distinct !DISubprogram(name: "archive_read_format_tar_cleanup", scope: !1, file: !1, line: 280, type: !251, isLocal: true, isDefinition: true, scopeLine: 281, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!442 = distinct !DISubprogram(name: "gnu_clear_sparse_list", scope: !1, file: !1, line: 2250, type: !443, isLocal: true, isDefinition: true, scopeLine: 2251, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!443 = !DISubroutineType(types: !444)
!444 = !{null, !291}
!445 = distinct !DISubprogram(name: "archive_read_format_tar_bid", scope: !1, file: !1, line: 356, type: !235, isLocal: true, isDefinition: true, scopeLine: 357, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!446 = distinct !DISubprogram(name: "archive_block_is_null", scope: !1, file: !1, line: 928, type: !447, isLocal: true, isDefinition: true, scopeLine: 929, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!447 = !DISubroutineType(types: !448)
!448 = !{!23, !80}
!449 = distinct !DISubprogram(name: "checksum", scope: !1, file: !1, line: 873, type: !450, isLocal: true, isDefinition: true, scopeLine: 874, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!450 = !DISubroutineType(types: !451)
!451 = !{!23, !4, !43}
!452 = distinct !DISubprogram(name: "tar_atol", scope: !1, file: !1, line: 2561, type: !453, isLocal: true, isDefinition: true, scopeLine: 2562, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!453 = !DISubroutineType(types: !454)
!454 = !{!52, !80, !45}
!455 = distinct !DISubprogram(name: "tar_atol256", scope: !1, file: !1, line: 2644, type: !453, isLocal: true, isDefinition: true, scopeLine: 2645, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!456 = distinct !DISubprogram(name: "tar_atol8", scope: !1, file: !1, line: 2622, type: !453, isLocal: true, isDefinition: true, scopeLine: 2623, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!457 = distinct !DISubprogram(name: "tar_atol_base_n", scope: !1, file: !1, line: 2578, type: !458, isLocal: true, isDefinition: true, scopeLine: 2579, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!458 = !DISubroutineType(types: !459)
!459 = !{!52, !80, !45, !23}
!460 = distinct !DISubprogram(name: "validate_number_field", scope: !1, file: !1, line: 327, type: !461, isLocal: true, isDefinition: true, scopeLine: 328, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!461 = !DISubroutineType(types: !462)
!462 = !{!23, !80, !45}
!463 = distinct !DISubprogram(name: "archive_read_format_tar_options", scope: !1, file: !1, line: 424, type: !239, isLocal: true, isDefinition: true, scopeLine: 426, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!464 = distinct !DISubprogram(name: "archive_read_format_tar_read_header", scope: !1, file: !1, line: 492, type: !243, isLocal: true, isDefinition: true, scopeLine: 494, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!465 = distinct !DISubprogram(name: "tar_read_header", scope: !1, file: !1, line: 691, type: !466, isLocal: true, isDefinition: true, scopeLine: 693, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!466 = !DISubroutineType(types: !467)
!467 = !{!23, !4, !291, !30, !65}
!468 = distinct !DISubprogram(name: "header_Solaris_ACL", scope: !1, file: !1, line: 942, type: !469, isLocal: true, isDefinition: true, scopeLine: 944, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!469 = !DISubroutineType(types: !470)
!470 = !{!23, !4, !291, !30, !43, !65}
!471 = distinct !DISubprogram(name: "read_body_to_string", scope: !1, file: !1, line: 1114, type: !472, isLocal: true, isDefinition: true, scopeLine: 1116, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!472 = !DISubroutineType(types: !473)
!473 = !{!23, !4, !291, !474, !43, !65}
!474 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !91, size: 64, align: 64)
!475 = distinct !DISubprogram(name: "header_pax_global", scope: !1, file: !1, line: 1451, type: !469, isLocal: true, isDefinition: true, scopeLine: 1453, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!476 = distinct !DISubprogram(name: "header_longlink", scope: !1, file: !1, line: 1043, type: !469, isLocal: true, isDefinition: true, scopeLine: 1045, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!477 = distinct !DISubprogram(name: "header_longname", scope: !1, file: !1, line: 1078, type: !469, isLocal: true, isDefinition: true, scopeLine: 1080, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!478 = distinct !DISubprogram(name: "set_conversion_failed_error", scope: !1, file: !1, line: 1060, type: !479, isLocal: true, isDefinition: true, scopeLine: 1062, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!479 = !DISubroutineType(types: !480)
!480 = !{!23, !4, !102, !80}
!481 = distinct !DISubprogram(name: "header_volume", scope: !1, file: !1, line: 1101, type: !469, isLocal: true, isDefinition: true, scopeLine: 1103, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!482 = distinct !DISubprogram(name: "header_pax_extensions", scope: !1, file: !1, line: 1464, type: !469, isLocal: true, isDefinition: true, scopeLine: 1466, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!483 = distinct !DISubprogram(name: "pax_header", scope: !1, file: !1, line: 1568, type: !484, isLocal: true, isDefinition: true, scopeLine: 1570, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!484 = !DISubroutineType(types: !485)
!485 = !{!23, !4, !291, !30, !474}
!486 = distinct !DISubprogram(name: "pax_attribute", scope: !1, file: !1, line: 1845, type: !487, isLocal: true, isDefinition: true, scopeLine: 1847, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!487 = !DISubroutineType(types: !488)
!488 = !{!23, !4, !291, !30, !80, !80, !45}
!489 = distinct !DISubprogram(name: "tar_atol10", scope: !1, file: !1, line: 2628, type: !453, isLocal: true, isDefinition: true, scopeLine: 2629, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!490 = distinct !DISubprogram(name: "gnu_sparse_01_parse", scope: !1, file: !1, line: 2356, type: !491, isLocal: true, isDefinition: true, scopeLine: 2357, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!491 = !DISubroutineType(types: !492)
!492 = !{!23, !4, !291, !80}
!493 = distinct !DISubprogram(name: "pax_time", scope: !1, file: !1, line: 2091, type: !494, isLocal: true, isDefinition: true, scopeLine: 2092, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!494 = !DISubroutineType(types: !495)
!495 = !{null, !80, !66, !496}
!496 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !42, size: 64, align: 64)
!497 = distinct !DISubprogram(name: "pax_attribute_xattr", scope: !1, file: !1, line: 1739, type: !498, isLocal: true, isDefinition: true, scopeLine: 1741, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!498 = !DISubroutineType(types: !499)
!499 = !{!23, !30, !80, !80}
!500 = distinct !DISubprogram(name: "url_decode", scope: !1, file: !1, line: 2840, type: !501, isLocal: true, isDefinition: true, scopeLine: 2841, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!501 = !DISubroutineType(types: !502)
!502 = !{!95, !80}
!503 = distinct !DISubprogram(name: "tohex", scope: !1, file: !1, line: 2869, type: !504, isLocal: true, isDefinition: true, scopeLine: 2870, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!504 = !DISubroutineType(types: !505)
!505 = !{!23, !23}
!506 = distinct !DISubprogram(name: "base64_decode", scope: !1, file: !1, line: 2768, type: !507, isLocal: true, isDefinition: true, scopeLine: 2769, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!507 = !DISubroutineType(types: !508)
!508 = !{!95, !80, !45, !65}
!509 = distinct !DISubprogram(name: "pax_attribute_acl", scope: !1, file: !1, line: 1786, type: !510, isLocal: true, isDefinition: true, scopeLine: 1788, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!510 = !DISubroutineType(types: !511)
!511 = !{!23, !4, !291, !30, !80, !23}
!512 = distinct !DISubprogram(name: "pax_attribute_schily_xattr", scope: !1, file: !1, line: 1772, type: !513, isLocal: true, isDefinition: true, scopeLine: 1774, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!513 = !DISubroutineType(types: !514)
!514 = !{!23, !30, !80, !80, !45}
!515 = distinct !DISubprogram(name: "solaris_sparse_parse", scope: !1, file: !1, line: 2505, type: !516, isLocal: true, isDefinition: true, scopeLine: 2507, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!516 = !DISubroutineType(types: !517)
!517 = !{!23, !4, !291, !30, !80}
!518 = distinct !DISubprogram(name: "header_gnutar", scope: !1, file: !1, line: 2141, type: !469, isLocal: true, isDefinition: true, scopeLine: 2143, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!519 = distinct !DISubprogram(name: "header_common", scope: !1, file: !1, line: 1163, type: !520, isLocal: true, isDefinition: true, scopeLine: 1165, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!520 = !DISubroutineType(types: !521)
!521 = !{!23, !4, !291, !30, !43}
!522 = distinct !DISubprogram(name: "gnu_sparse_old_parse", scope: !1, file: !1, line: 2314, type: !523, isLocal: true, isDefinition: true, scopeLine: 2316, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!523 = !DISubroutineType(types: !524)
!524 = !{!23, !4, !291, !525, !23}
!525 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !526, size: 64, align: 64)
!526 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !414)
!527 = distinct !DISubprogram(name: "header_ustar", scope: !1, file: !1, line: 1500, type: !520, isLocal: true, isDefinition: true, scopeLine: 1502, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!528 = distinct !DISubprogram(name: "header_old_tar", scope: !1, file: !1, line: 1352, type: !520, isLocal: true, isDefinition: true, scopeLine: 1354, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!529 = distinct !DISubprogram(name: "read_mac_metadata_blob", scope: !1, file: !1, line: 1381, type: !469, isLocal: true, isDefinition: true, scopeLine: 1383, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!530 = distinct !DISubprogram(name: "gnu_sparse_10_read", scope: !1, file: !1, line: 2458, type: !531, isLocal: true, isDefinition: true, scopeLine: 2459, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!531 = !DISubroutineType(types: !532)
!532 = !{!38, !4, !291, !65}
!533 = distinct !DISubprogram(name: "gnu_sparse_10_atol", scope: !1, file: !1, line: 2411, type: !534, isLocal: true, isDefinition: true, scopeLine: 2413, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!534 = !DISubroutineType(types: !535)
!535 = !{!52, !4, !291, !66, !65}
!536 = distinct !DISubprogram(name: "readline", scope: !1, file: !1, line: 2693, type: !537, isLocal: true, isDefinition: true, scopeLine: 2695, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!537 = !DISubroutineType(types: !538)
!538 = !{!38, !4, !291, !539, !38, !65}
!539 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !80, size: 64, align: 64)
!540 = distinct !DISubprogram(name: "tar_flush_unconsumed", scope: !1, file: !1, line: 469, type: !541, isLocal: true, isDefinition: true, scopeLine: 470, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!541 = !DISubroutineType(types: !542)
!542 = !{null, !4, !65}
!543 = distinct !DISubprogram(name: "gnu_add_sparse_entry", scope: !1, file: !1, line: 2225, type: !544, isLocal: true, isDefinition: true, scopeLine: 2227, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!544 = !DISubroutineType(types: !545)
!545 = !{!23, !4, !291, !52, !52}
!546 = distinct !DISubprogram(name: "archive_read_format_tar_read_data", scope: !1, file: !1, line: 586, type: !247, isLocal: true, isDefinition: true, scopeLine: 588, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!547 = distinct !DISubprogram(name: "archive_read_format_tar_skip", scope: !1, file: !1, line: 649, type: !251, isLocal: true, isDefinition: true, scopeLine: 650, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!548 = !{!549, !550, !551, !555}
!549 = !DIGlobalVariable(name: "default_inode", scope: !464, file: !1, line: 509, type: !23, isLocal: true, isDefinition: true, variable: i32* @archive_read_format_tar_read_header.default_inode)
!550 = !DIGlobalVariable(name: "default_dev", scope: !464, file: !1, line: 510, type: !23, isLocal: true, isDefinition: true, variable: i32* @archive_read_format_tar_read_header.default_dev)
!551 = !DIGlobalVariable(name: "digits", scope: !506, file: !1, line: 2770, type: !552, isLocal: true, isDefinition: true, variable: [64 x i8]* @base64_decode.digits)
!552 = !DICompositeType(tag: DW_TAG_array_type, baseType: !381, size: 512, align: 8, elements: !553)
!553 = !{!554}
!554 = !DISubrange(count: 64)
!555 = !DIGlobalVariable(name: "decode_table", scope: !506, file: !1, line: 2776, type: !556, isLocal: true, isDefinition: true, variable: [128 x i8]* @base64_decode.decode_table)
!556 = !DICompositeType(tag: DW_TAG_array_type, baseType: !382, size: 1024, align: 8, elements: !557)
!557 = !{!558}
!558 = !DISubrange(count: 128)
!559 = !{i32 2, !"Dwarf Version", i32 4}
!560 = !{i32 2, !"Debug Info Version", i32 3}
!561 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!562 = !DILocalVariable(name: "a", arg: 1, scope: !439, file: !1, line: 234, type: !24)
!563 = !DIExpression()
!564 = !DILocation(line: 234, column: 52, scope: !439)
!565 = !DILocation(line: 236, column: 2, scope: !439)
!566 = !DILocalVariable(name: "magic_test", scope: !567, file: !1, line: 236, type: !23)
!567 = distinct !DILexicalBlock(scope: !439, file: !1, line: 236, column: 2)
!568 = !DILocation(line: 236, column: 2, scope: !567)
!569 = !DILocation(line: 236, column: 2, scope: !570)
!570 = !DILexicalBlockFile(scope: !567, file: !1, discriminator: 1)
!571 = !DILocation(line: 236, column: 2, scope: !572)
!572 = !DILexicalBlockFile(scope: !573, file: !1, discriminator: 2)
!573 = distinct !DILexicalBlock(scope: !567, file: !1, line: 236, column: 2)
!574 = !DILocation(line: 236, column: 2, scope: !575)
!575 = !DILexicalBlockFile(scope: !567, file: !1, discriminator: 3)
!576 = !DILocation(line: 238, column: 42, scope: !439)
!577 = !DILocation(line: 238, column: 10, scope: !439)
!578 = !DILocation(line: 238, column: 2, scope: !439)
!579 = !DILocation(line: 239, column: 1, scope: !439)
!580 = !DILocalVariable(name: "_a", arg: 1, scope: !440, file: !1, line: 243, type: !24)
!581 = !DILocation(line: 243, column: 49, scope: !440)
!582 = !DILocalVariable(name: "a", scope: !440, file: !1, line: 245, type: !4)
!583 = !DILocation(line: 245, column: 23, scope: !440)
!584 = !DILocation(line: 245, column: 50, scope: !440)
!585 = !DILocation(line: 245, column: 27, scope: !440)
!586 = !DILocalVariable(name: "tar", scope: !440, file: !1, line: 246, type: !291)
!587 = !DILocation(line: 246, column: 14, scope: !440)
!588 = !DILocalVariable(name: "r", scope: !440, file: !1, line: 247, type: !23)
!589 = !DILocation(line: 247, column: 6, scope: !440)
!590 = !DILocation(line: 249, column: 2, scope: !440)
!591 = !DILocalVariable(name: "magic_test", scope: !592, file: !1, line: 249, type: !23)
!592 = distinct !DILexicalBlock(scope: !440, file: !1, line: 249, column: 2)
!593 = !DILocation(line: 249, column: 2, scope: !592)
!594 = !DILocation(line: 249, column: 2, scope: !595)
!595 = !DILexicalBlockFile(scope: !592, file: !1, discriminator: 1)
!596 = !DILocation(line: 249, column: 2, scope: !597)
!597 = !DILexicalBlockFile(scope: !598, file: !1, discriminator: 2)
!598 = distinct !DILexicalBlock(scope: !592, file: !1, line: 249, column: 2)
!599 = !DILocation(line: 249, column: 2, scope: !600)
!600 = !DILexicalBlockFile(scope: !592, file: !1, discriminator: 3)
!601 = !DILocation(line: 252, column: 22, scope: !440)
!602 = !DILocation(line: 252, column: 8, scope: !440)
!603 = !DILocation(line: 252, column: 6, scope: !440)
!604 = !DILocation(line: 257, column: 6, scope: !605)
!605 = distinct !DILexicalBlock(scope: !440, file: !1, line: 257, column: 6)
!606 = !DILocation(line: 257, column: 10, scope: !605)
!607 = !DILocation(line: 257, column: 6, scope: !440)
!608 = !DILocation(line: 258, column: 22, scope: !609)
!609 = distinct !DILexicalBlock(scope: !605, file: !1, line: 257, column: 19)
!610 = !DILocation(line: 258, column: 25, scope: !609)
!611 = !DILocation(line: 258, column: 3, scope: !609)
!612 = !DILocation(line: 260, column: 3, scope: !609)
!613 = !DILocation(line: 263, column: 37, scope: !440)
!614 = !DILocation(line: 263, column: 40, scope: !440)
!615 = !DILocation(line: 263, column: 6, scope: !440)
!616 = !DILocation(line: 263, column: 4, scope: !440)
!617 = !DILocation(line: 274, column: 6, scope: !618)
!618 = distinct !DILexicalBlock(scope: !440, file: !1, line: 274, column: 6)
!619 = !DILocation(line: 274, column: 8, scope: !618)
!620 = !DILocation(line: 274, column: 6, scope: !440)
!621 = !DILocation(line: 275, column: 8, scope: !618)
!622 = !DILocation(line: 275, column: 3, scope: !618)
!623 = !DILocation(line: 276, column: 2, scope: !440)
!624 = !DILocation(line: 277, column: 1, scope: !440)
!625 = !DILocalVariable(name: "a", arg: 1, scope: !445, file: !1, line: 356, type: !4)
!626 = !DILocation(line: 356, column: 50, scope: !445)
!627 = !DILocalVariable(name: "best_bid", arg: 2, scope: !445, file: !1, line: 356, type: !23)
!628 = !DILocation(line: 356, column: 57, scope: !445)
!629 = !DILocalVariable(name: "bid", scope: !445, file: !1, line: 358, type: !23)
!630 = !DILocation(line: 358, column: 6, scope: !445)
!631 = !DILocalVariable(name: "h", scope: !445, file: !1, line: 359, type: !80)
!632 = !DILocation(line: 359, column: 14, scope: !445)
!633 = !DILocalVariable(name: "header", scope: !445, file: !1, line: 360, type: !336)
!634 = !DILocation(line: 360, column: 43, scope: !445)
!635 = !DILocation(line: 362, column: 8, scope: !445)
!636 = !DILocation(line: 364, column: 6, scope: !445)
!637 = !DILocation(line: 367, column: 27, scope: !445)
!638 = !DILocation(line: 367, column: 6, scope: !445)
!639 = !DILocation(line: 367, column: 4, scope: !445)
!640 = !DILocation(line: 368, column: 6, scope: !641)
!641 = distinct !DILexicalBlock(scope: !445, file: !1, line: 368, column: 6)
!642 = !DILocation(line: 368, column: 8, scope: !641)
!643 = !DILocation(line: 368, column: 6, scope: !445)
!644 = !DILocation(line: 369, column: 3, scope: !641)
!645 = !DILocation(line: 372, column: 6, scope: !646)
!646 = distinct !DILexicalBlock(scope: !445, file: !1, line: 372, column: 6)
!647 = !DILocation(line: 372, column: 11, scope: !646)
!648 = !DILocation(line: 372, column: 16, scope: !646)
!649 = !DILocation(line: 372, column: 41, scope: !650)
!650 = !DILexicalBlockFile(scope: !646, file: !1, discriminator: 1)
!651 = !DILocation(line: 372, column: 19, scope: !650)
!652 = !DILocation(line: 372, column: 6, scope: !650)
!653 = !DILocation(line: 378, column: 3, scope: !654)
!654 = distinct !DILexicalBlock(scope: !646, file: !1, line: 372, column: 45)
!655 = !DILocation(line: 382, column: 16, scope: !656)
!656 = distinct !DILexicalBlock(scope: !445, file: !1, line: 382, column: 6)
!657 = !DILocation(line: 382, column: 19, scope: !656)
!658 = !DILocation(line: 382, column: 7, scope: !656)
!659 = !DILocation(line: 382, column: 6, scope: !445)
!660 = !DILocation(line: 383, column: 3, scope: !656)
!661 = !DILocation(line: 384, column: 6, scope: !445)
!662 = !DILocation(line: 386, column: 54, scope: !445)
!663 = !DILocation(line: 386, column: 11, scope: !445)
!664 = !DILocation(line: 386, column: 9, scope: !445)
!665 = !DILocation(line: 389, column: 14, scope: !666)
!666 = distinct !DILexicalBlock(scope: !445, file: !1, line: 389, column: 6)
!667 = !DILocation(line: 389, column: 22, scope: !666)
!668 = !DILocation(line: 389, column: 7, scope: !666)
!669 = !DILocation(line: 389, column: 43, scope: !666)
!670 = !DILocation(line: 390, column: 6, scope: !666)
!671 = !DILocation(line: 390, column: 17, scope: !672)
!672 = !DILexicalBlockFile(scope: !666, file: !1, discriminator: 1)
!673 = !DILocation(line: 390, column: 25, scope: !672)
!674 = !DILocation(line: 390, column: 10, scope: !672)
!675 = !DILocation(line: 390, column: 43, scope: !672)
!676 = !DILocation(line: 389, column: 6, scope: !677)
!677 = !DILexicalBlockFile(scope: !445, file: !1, discriminator: 1)
!678 = !DILocation(line: 391, column: 7, scope: !666)
!679 = !DILocation(line: 391, column: 3, scope: !666)
!680 = !DILocation(line: 394, column: 14, scope: !681)
!681 = distinct !DILexicalBlock(scope: !445, file: !1, line: 394, column: 6)
!682 = !DILocation(line: 394, column: 22, scope: !681)
!683 = !DILocation(line: 394, column: 7, scope: !681)
!684 = !DILocation(line: 394, column: 42, scope: !681)
!685 = !DILocation(line: 395, column: 6, scope: !681)
!686 = !DILocation(line: 395, column: 17, scope: !687)
!687 = !DILexicalBlockFile(scope: !681, file: !1, discriminator: 1)
!688 = !DILocation(line: 395, column: 25, scope: !687)
!689 = !DILocation(line: 395, column: 10, scope: !687)
!690 = !DILocation(line: 395, column: 44, scope: !687)
!691 = !DILocation(line: 394, column: 6, scope: !677)
!692 = !DILocation(line: 396, column: 7, scope: !681)
!693 = !DILocation(line: 396, column: 3, scope: !681)
!694 = !DILocation(line: 399, column: 6, scope: !695)
!695 = distinct !DILexicalBlock(scope: !445, file: !1, line: 399, column: 6)
!696 = !DILocation(line: 399, column: 14, scope: !695)
!697 = !DILocation(line: 399, column: 26, scope: !695)
!698 = !DILocation(line: 399, column: 31, scope: !695)
!699 = !DILocation(line: 400, column: 9, scope: !695)
!700 = !DILocation(line: 400, column: 17, scope: !695)
!701 = !DILocation(line: 400, column: 29, scope: !695)
!702 = !DILocation(line: 400, column: 36, scope: !695)
!703 = !DILocation(line: 400, column: 39, scope: !704)
!704 = !DILexicalBlockFile(scope: !695, file: !1, discriminator: 1)
!705 = !DILocation(line: 400, column: 47, scope: !704)
!706 = !DILocation(line: 400, column: 59, scope: !704)
!707 = !DILocation(line: 400, column: 67, scope: !704)
!708 = !DILocation(line: 401, column: 9, scope: !695)
!709 = !DILocation(line: 401, column: 17, scope: !695)
!710 = !DILocation(line: 401, column: 29, scope: !695)
!711 = !DILocation(line: 401, column: 36, scope: !695)
!712 = !DILocation(line: 401, column: 39, scope: !704)
!713 = !DILocation(line: 401, column: 47, scope: !704)
!714 = !DILocation(line: 401, column: 59, scope: !704)
!715 = !DILocation(line: 401, column: 67, scope: !704)
!716 = !DILocation(line: 402, column: 9, scope: !695)
!717 = !DILocation(line: 402, column: 17, scope: !695)
!718 = !DILocation(line: 402, column: 29, scope: !695)
!719 = !DILocation(line: 402, column: 36, scope: !695)
!720 = !DILocation(line: 402, column: 39, scope: !704)
!721 = !DILocation(line: 402, column: 47, scope: !704)
!722 = !DILocation(line: 402, column: 59, scope: !704)
!723 = !DILocation(line: 399, column: 6, scope: !677)
!724 = !DILocation(line: 403, column: 3, scope: !695)
!725 = !DILocation(line: 404, column: 6, scope: !445)
!726 = !DILocation(line: 409, column: 6, scope: !727)
!727 = distinct !DILexicalBlock(scope: !445, file: !1, line: 409, column: 6)
!728 = !DILocation(line: 409, column: 10, scope: !727)
!729 = !DILocation(line: 409, column: 14, scope: !727)
!730 = !DILocation(line: 410, column: 28, scope: !727)
!731 = !DILocation(line: 410, column: 36, scope: !727)
!732 = !DILocation(line: 410, column: 6, scope: !727)
!733 = !DILocation(line: 410, column: 64, scope: !727)
!734 = !DILocation(line: 411, column: 6, scope: !727)
!735 = !DILocation(line: 411, column: 31, scope: !736)
!736 = !DILexicalBlockFile(scope: !727, file: !1, discriminator: 1)
!737 = !DILocation(line: 411, column: 39, scope: !736)
!738 = !DILocation(line: 411, column: 9, scope: !736)
!739 = !DILocation(line: 411, column: 65, scope: !736)
!740 = !DILocation(line: 412, column: 6, scope: !727)
!741 = !DILocation(line: 412, column: 31, scope: !736)
!742 = !DILocation(line: 412, column: 39, scope: !736)
!743 = !DILocation(line: 412, column: 9, scope: !736)
!744 = !DILocation(line: 412, column: 65, scope: !736)
!745 = !DILocation(line: 413, column: 6, scope: !727)
!746 = !DILocation(line: 413, column: 31, scope: !736)
!747 = !DILocation(line: 413, column: 39, scope: !736)
!748 = !DILocation(line: 413, column: 9, scope: !736)
!749 = !DILocation(line: 413, column: 69, scope: !736)
!750 = !DILocation(line: 414, column: 6, scope: !727)
!751 = !DILocation(line: 414, column: 31, scope: !736)
!752 = !DILocation(line: 414, column: 39, scope: !736)
!753 = !DILocation(line: 414, column: 9, scope: !736)
!754 = !DILocation(line: 414, column: 67, scope: !736)
!755 = !DILocation(line: 415, column: 6, scope: !727)
!756 = !DILocation(line: 415, column: 31, scope: !736)
!757 = !DILocation(line: 415, column: 39, scope: !736)
!758 = !DILocation(line: 415, column: 9, scope: !736)
!759 = !DILocation(line: 415, column: 77, scope: !736)
!760 = !DILocation(line: 416, column: 6, scope: !727)
!761 = !DILocation(line: 416, column: 31, scope: !736)
!762 = !DILocation(line: 416, column: 39, scope: !736)
!763 = !DILocation(line: 416, column: 9, scope: !736)
!764 = !DILocation(line: 416, column: 77, scope: !736)
!765 = !DILocation(line: 409, column: 6, scope: !677)
!766 = !DILocation(line: 417, column: 7, scope: !767)
!767 = distinct !DILexicalBlock(scope: !727, file: !1, line: 416, column: 84)
!768 = !DILocation(line: 418, column: 2, scope: !767)
!769 = !DILocation(line: 420, column: 10, scope: !445)
!770 = !DILocation(line: 420, column: 2, scope: !445)
!771 = !DILocation(line: 421, column: 1, scope: !445)
!772 = !DILocalVariable(name: "a", arg: 1, scope: !463, file: !1, line: 424, type: !4)
!773 = !DILocation(line: 424, column: 54, scope: !463)
!774 = !DILocalVariable(name: "key", arg: 2, scope: !463, file: !1, line: 425, type: !80)
!775 = !DILocation(line: 425, column: 17, scope: !463)
!776 = !DILocalVariable(name: "val", arg: 3, scope: !463, file: !1, line: 425, type: !80)
!777 = !DILocation(line: 425, column: 34, scope: !463)
!778 = !DILocalVariable(name: "tar", scope: !463, file: !1, line: 427, type: !291)
!779 = !DILocation(line: 427, column: 14, scope: !463)
!780 = !DILocalVariable(name: "ret", scope: !463, file: !1, line: 428, type: !23)
!781 = !DILocation(line: 428, column: 6, scope: !463)
!782 = !DILocation(line: 430, column: 23, scope: !463)
!783 = !DILocation(line: 430, column: 26, scope: !463)
!784 = !DILocation(line: 430, column: 34, scope: !463)
!785 = !DILocation(line: 430, column: 8, scope: !463)
!786 = !DILocation(line: 430, column: 6, scope: !463)
!787 = !DILocation(line: 431, column: 13, scope: !788)
!788 = distinct !DILexicalBlock(scope: !463, file: !1, line: 431, column: 6)
!789 = !DILocation(line: 431, column: 6, scope: !788)
!790 = !DILocation(line: 431, column: 32, scope: !788)
!791 = !DILocation(line: 431, column: 6, scope: !463)
!792 = !DILocation(line: 433, column: 21, scope: !793)
!793 = distinct !DILexicalBlock(scope: !788, file: !1, line: 431, column: 38)
!794 = !DILocation(line: 433, column: 25, scope: !793)
!795 = !DILocation(line: 433, column: 33, scope: !793)
!796 = !DILocation(line: 433, column: 36, scope: !797)
!797 = !DILexicalBlockFile(scope: !793, file: !1, discriminator: 1)
!798 = !DILocation(line: 433, column: 43, scope: !797)
!799 = !DILocation(line: 433, column: 33, scope: !800)
!800 = !DILexicalBlockFile(scope: !793, file: !1, discriminator: 2)
!801 = !DILocation(line: 433, column: 3, scope: !800)
!802 = !DILocation(line: 433, column: 8, scope: !800)
!803 = !DILocation(line: 433, column: 18, scope: !800)
!804 = !DILocation(line: 434, column: 34, scope: !793)
!805 = !DILocation(line: 434, column: 39, scope: !793)
!806 = !DILocation(line: 434, column: 3, scope: !793)
!807 = !DILocation(line: 434, column: 8, scope: !793)
!808 = !DILocation(line: 434, column: 32, scope: !793)
!809 = !DILocation(line: 435, column: 3, scope: !793)
!810 = !DILocation(line: 436, column: 20, scope: !811)
!811 = distinct !DILexicalBlock(scope: !788, file: !1, line: 436, column: 13)
!812 = !DILocation(line: 436, column: 13, scope: !811)
!813 = !DILocation(line: 436, column: 40, scope: !811)
!814 = !DILocation(line: 436, column: 13, scope: !788)
!815 = !DILocation(line: 437, column: 7, scope: !816)
!816 = distinct !DILexicalBlock(scope: !817, file: !1, line: 437, column: 7)
!817 = distinct !DILexicalBlock(scope: !811, file: !1, line: 436, column: 46)
!818 = !DILocation(line: 437, column: 11, scope: !816)
!819 = !DILocation(line: 437, column: 19, scope: !816)
!820 = !DILocation(line: 437, column: 22, scope: !821)
!821 = !DILexicalBlockFile(scope: !816, file: !1, discriminator: 1)
!822 = !DILocation(line: 437, column: 29, scope: !821)
!823 = !DILocation(line: 437, column: 7, scope: !821)
!824 = !DILocation(line: 438, column: 23, scope: !816)
!825 = !DILocation(line: 438, column: 26, scope: !816)
!826 = !DILocation(line: 438, column: 4, scope: !816)
!827 = !DILocation(line: 443, column: 6, scope: !828)
!828 = distinct !DILexicalBlock(scope: !816, file: !1, line: 440, column: 8)
!829 = !DILocation(line: 443, column: 9, scope: !828)
!830 = !DILocation(line: 443, column: 18, scope: !828)
!831 = !DILocation(line: 442, column: 8, scope: !828)
!832 = !DILocation(line: 441, column: 4, scope: !828)
!833 = !DILocation(line: 441, column: 9, scope: !828)
!834 = !DILocation(line: 441, column: 19, scope: !828)
!835 = !DILocation(line: 444, column: 8, scope: !836)
!836 = distinct !DILexicalBlock(scope: !828, file: !1, line: 444, column: 8)
!837 = !DILocation(line: 444, column: 13, scope: !836)
!838 = !DILocation(line: 444, column: 23, scope: !836)
!839 = !DILocation(line: 444, column: 8, scope: !828)
!840 = !DILocation(line: 445, column: 9, scope: !836)
!841 = !DILocation(line: 445, column: 5, scope: !836)
!842 = !DILocation(line: 447, column: 9, scope: !836)
!843 = !DILocation(line: 449, column: 11, scope: !817)
!844 = !DILocation(line: 449, column: 3, scope: !817)
!845 = !DILocation(line: 450, column: 20, scope: !846)
!846 = distinct !DILexicalBlock(scope: !811, file: !1, line: 450, column: 13)
!847 = !DILocation(line: 450, column: 13, scope: !846)
!848 = !DILocation(line: 450, column: 36, scope: !846)
!849 = !DILocation(line: 450, column: 13, scope: !811)
!850 = !DILocation(line: 451, column: 34, scope: !851)
!851 = distinct !DILexicalBlock(scope: !846, file: !1, line: 450, column: 42)
!852 = !DILocation(line: 451, column: 38, scope: !851)
!853 = !DILocation(line: 451, column: 46, scope: !851)
!854 = !DILocation(line: 451, column: 49, scope: !855)
!855 = !DILexicalBlockFile(scope: !851, file: !1, discriminator: 1)
!856 = !DILocation(line: 451, column: 56, scope: !855)
!857 = !DILocation(line: 451, column: 46, scope: !858)
!858 = !DILexicalBlockFile(scope: !851, file: !1, discriminator: 2)
!859 = !DILocation(line: 451, column: 3, scope: !858)
!860 = !DILocation(line: 451, column: 8, scope: !858)
!861 = !DILocation(line: 451, column: 31, scope: !858)
!862 = !DILocation(line: 452, column: 3, scope: !851)
!863 = !DILocation(line: 453, column: 20, scope: !864)
!864 = distinct !DILexicalBlock(scope: !846, file: !1, line: 453, column: 13)
!865 = !DILocation(line: 453, column: 13, scope: !864)
!866 = !DILocation(line: 453, column: 55, scope: !864)
!867 = !DILocation(line: 453, column: 13, scope: !846)
!868 = !DILocation(line: 454, column: 38, scope: !869)
!869 = distinct !DILexicalBlock(scope: !864, file: !1, line: 453, column: 61)
!870 = !DILocation(line: 454, column: 42, scope: !869)
!871 = !DILocation(line: 454, column: 50, scope: !869)
!872 = !DILocation(line: 454, column: 53, scope: !873)
!873 = !DILexicalBlockFile(scope: !869, file: !1, discriminator: 1)
!874 = !DILocation(line: 454, column: 60, scope: !873)
!875 = !DILocation(line: 454, column: 50, scope: !876)
!876 = !DILexicalBlockFile(scope: !869, file: !1, discriminator: 2)
!877 = !DILocation(line: 454, column: 3, scope: !876)
!878 = !DILocation(line: 454, column: 8, scope: !876)
!879 = !DILocation(line: 454, column: 35, scope: !876)
!880 = !DILocation(line: 455, column: 3, scope: !869)
!881 = !DILocation(line: 461, column: 2, scope: !463)
!882 = !DILocation(line: 462, column: 1, scope: !463)
!883 = !DILocalVariable(name: "a", arg: 1, scope: !464, file: !1, line: 492, type: !4)
!884 = !DILocation(line: 492, column: 58, scope: !464)
!885 = !DILocalVariable(name: "entry", arg: 2, scope: !464, file: !1, line: 493, type: !30)
!886 = !DILocation(line: 493, column: 27, scope: !464)
!887 = !DILocalVariable(name: "tar", scope: !464, file: !1, line: 511, type: !291)
!888 = !DILocation(line: 511, column: 14, scope: !464)
!889 = !DILocalVariable(name: "p", scope: !464, file: !1, line: 512, type: !80)
!890 = !DILocation(line: 512, column: 14, scope: !464)
!891 = !DILocalVariable(name: "wp", scope: !464, file: !1, line: 513, type: !892)
!892 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !893, size: 64, align: 64)
!893 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !894)
!894 = !DIDerivedType(tag: DW_TAG_typedef, name: "wchar_t", file: !46, line: 90, baseType: !23)
!895 = !DILocation(line: 513, column: 17, scope: !464)
!896 = !DILocalVariable(name: "r", scope: !464, file: !1, line: 514, type: !23)
!897 = !DILocation(line: 514, column: 6, scope: !464)
!898 = !DILocalVariable(name: "l", scope: !464, file: !1, line: 515, type: !45)
!899 = !DILocation(line: 515, column: 9, scope: !464)
!900 = !DILocalVariable(name: "unconsumed", scope: !464, file: !1, line: 515, type: !45)
!901 = !DILocation(line: 515, column: 12, scope: !464)
!902 = !DILocation(line: 518, column: 24, scope: !464)
!903 = !DILocation(line: 518, column: 35, scope: !464)
!904 = !DILocation(line: 518, column: 33, scope: !464)
!905 = !DILocation(line: 518, column: 31, scope: !464)
!906 = !DILocation(line: 518, column: 2, scope: !464)
!907 = !DILocation(line: 519, column: 24, scope: !464)
!908 = !DILocation(line: 519, column: 31, scope: !464)
!909 = !DILocation(line: 519, column: 2, scope: !464)
!910 = !DILocation(line: 521, column: 6, scope: !911)
!911 = distinct !DILexicalBlock(scope: !464, file: !1, line: 521, column: 6)
!912 = !DILocation(line: 521, column: 20, scope: !911)
!913 = !DILocation(line: 521, column: 6, scope: !464)
!914 = !DILocation(line: 522, column: 3, scope: !915)
!915 = distinct !DILexicalBlock(scope: !911, file: !1, line: 521, column: 31)
!916 = !DILocation(line: 523, column: 17, scope: !915)
!917 = !DILocation(line: 524, column: 2, scope: !915)
!918 = !DILocation(line: 526, column: 23, scope: !464)
!919 = !DILocation(line: 526, column: 26, scope: !464)
!920 = !DILocation(line: 526, column: 34, scope: !464)
!921 = !DILocation(line: 526, column: 8, scope: !464)
!922 = !DILocation(line: 526, column: 6, scope: !464)
!923 = !DILocation(line: 527, column: 2, scope: !464)
!924 = !DILocation(line: 527, column: 7, scope: !464)
!925 = !DILocation(line: 527, column: 20, scope: !464)
!926 = !DILocation(line: 528, column: 24, scope: !464)
!927 = !DILocation(line: 528, column: 2, scope: !464)
!928 = !DILocation(line: 529, column: 2, scope: !464)
!929 = !DILocation(line: 529, column: 7, scope: !464)
!930 = !DILocation(line: 529, column: 16, scope: !464)
!931 = !DILocation(line: 532, column: 15, scope: !464)
!932 = !DILocation(line: 532, column: 20, scope: !464)
!933 = !DILocation(line: 532, column: 2, scope: !464)
!934 = !DILocation(line: 532, column: 7, scope: !464)
!935 = !DILocation(line: 532, column: 13, scope: !464)
!936 = !DILocation(line: 533, column: 6, scope: !937)
!937 = distinct !DILexicalBlock(scope: !464, file: !1, line: 533, column: 6)
!938 = !DILocation(line: 533, column: 11, scope: !937)
!939 = !DILocation(line: 533, column: 17, scope: !937)
!940 = !DILocation(line: 533, column: 6, scope: !464)
!941 = !DILocation(line: 534, column: 8, scope: !942)
!942 = distinct !DILexicalBlock(scope: !943, file: !1, line: 534, column: 7)
!943 = distinct !DILexicalBlock(scope: !937, file: !1, line: 533, column: 26)
!944 = !DILocation(line: 534, column: 13, scope: !942)
!945 = !DILocation(line: 534, column: 7, scope: !943)
!946 = !DILocation(line: 536, column: 53, scope: !947)
!947 = distinct !DILexicalBlock(scope: !942, file: !1, line: 534, column: 38)
!948 = !DILocation(line: 536, column: 56, scope: !947)
!949 = !DILocation(line: 536, column: 8, scope: !947)
!950 = !DILocation(line: 535, column: 4, scope: !947)
!951 = !DILocation(line: 535, column: 9, scope: !947)
!952 = !DILocation(line: 535, column: 23, scope: !947)
!953 = !DILocation(line: 537, column: 4, scope: !947)
!954 = !DILocation(line: 537, column: 9, scope: !947)
!955 = !DILocation(line: 537, column: 33, scope: !947)
!956 = !DILocation(line: 538, column: 3, scope: !947)
!957 = !DILocation(line: 539, column: 16, scope: !943)
!958 = !DILocation(line: 539, column: 21, scope: !943)
!959 = !DILocation(line: 539, column: 3, scope: !943)
!960 = !DILocation(line: 539, column: 8, scope: !943)
!961 = !DILocation(line: 539, column: 14, scope: !943)
!962 = !DILocation(line: 540, column: 2, scope: !943)
!963 = !DILocation(line: 542, column: 22, scope: !464)
!964 = !DILocation(line: 542, column: 25, scope: !464)
!965 = !DILocation(line: 542, column: 30, scope: !464)
!966 = !DILocation(line: 542, column: 6, scope: !464)
!967 = !DILocation(line: 542, column: 4, scope: !464)
!968 = !DILocation(line: 544, column: 23, scope: !464)
!969 = !DILocation(line: 544, column: 2, scope: !464)
!970 = !DILocation(line: 550, column: 6, scope: !971)
!971 = distinct !DILexicalBlock(scope: !464, file: !1, line: 550, column: 6)
!972 = !DILocation(line: 550, column: 11, scope: !971)
!973 = !DILocation(line: 550, column: 23, scope: !971)
!974 = !DILocation(line: 550, column: 6, scope: !464)
!975 = !DILocation(line: 551, column: 28, scope: !976)
!976 = distinct !DILexicalBlock(scope: !977, file: !1, line: 551, column: 7)
!977 = distinct !DILexicalBlock(scope: !971, file: !1, line: 550, column: 32)
!978 = !DILocation(line: 551, column: 31, scope: !976)
!979 = !DILocation(line: 551, column: 39, scope: !976)
!980 = !DILocation(line: 551, column: 44, scope: !976)
!981 = !DILocation(line: 551, column: 7, scope: !976)
!982 = !DILocation(line: 552, column: 7, scope: !976)
!983 = !DILocation(line: 551, column: 7, scope: !977)
!984 = !DILocation(line: 553, column: 4, scope: !976)
!985 = !DILocation(line: 554, column: 2, scope: !977)
!986 = !DILocalVariable(name: "sb", scope: !987, file: !1, line: 555, type: !314)
!987 = distinct !DILexicalBlock(scope: !971, file: !1, line: 554, column: 9)
!988 = !DILocation(line: 555, column: 24, scope: !987)
!989 = !DILocation(line: 557, column: 13, scope: !990)
!990 = distinct !DILexicalBlock(scope: !987, file: !1, line: 557, column: 3)
!991 = !DILocation(line: 557, column: 18, scope: !990)
!992 = !DILocation(line: 557, column: 11, scope: !990)
!993 = !DILocation(line: 557, column: 8, scope: !990)
!994 = !DILocation(line: 557, column: 31, scope: !995)
!995 = !DILexicalBlockFile(scope: !996, file: !1, discriminator: 1)
!996 = distinct !DILexicalBlock(scope: !990, file: !1, line: 557, column: 3)
!997 = !DILocation(line: 557, column: 34, scope: !995)
!998 = !DILocation(line: 557, column: 3, scope: !995)
!999 = !DILocation(line: 558, column: 9, scope: !1000)
!1000 = distinct !DILexicalBlock(scope: !1001, file: !1, line: 558, column: 8)
!1001 = distinct !DILexicalBlock(scope: !996, file: !1, line: 557, column: 58)
!1002 = !DILocation(line: 558, column: 13, scope: !1000)
!1003 = !DILocation(line: 558, column: 8, scope: !1001)
!1004 = !DILocation(line: 559, column: 36, scope: !1000)
!1005 = !DILocation(line: 560, column: 9, scope: !1000)
!1006 = !DILocation(line: 560, column: 13, scope: !1000)
!1007 = !DILocation(line: 560, column: 21, scope: !1000)
!1008 = !DILocation(line: 560, column: 25, scope: !1000)
!1009 = !DILocation(line: 559, column: 5, scope: !1000)
!1010 = !DILocation(line: 561, column: 3, scope: !1001)
!1011 = !DILocation(line: 557, column: 48, scope: !1012)
!1012 = !DILexicalBlockFile(scope: !996, file: !1, discriminator: 2)
!1013 = !DILocation(line: 557, column: 52, scope: !1012)
!1014 = !DILocation(line: 557, column: 46, scope: !1012)
!1015 = !DILocation(line: 557, column: 3, scope: !1012)
!1016 = !DILocation(line: 564, column: 6, scope: !1017)
!1017 = distinct !DILexicalBlock(scope: !464, file: !1, line: 564, column: 6)
!1018 = !DILocation(line: 564, column: 8, scope: !1017)
!1019 = !DILocation(line: 564, column: 22, scope: !1017)
!1020 = !DILocation(line: 564, column: 48, scope: !1021)
!1021 = !DILexicalBlockFile(scope: !1017, file: !1, discriminator: 1)
!1022 = !DILocation(line: 564, column: 25, scope: !1021)
!1023 = !DILocation(line: 564, column: 55, scope: !1021)
!1024 = !DILocation(line: 564, column: 6, scope: !1021)
!1025 = !DILocation(line: 570, column: 38, scope: !1026)
!1026 = distinct !DILexicalBlock(scope: !1027, file: !1, line: 570, column: 7)
!1027 = distinct !DILexicalBlock(scope: !1017, file: !1, line: 564, column: 68)
!1028 = !DILocation(line: 570, column: 13, scope: !1026)
!1029 = !DILocation(line: 570, column: 11, scope: !1026)
!1030 = !DILocation(line: 570, column: 46, scope: !1026)
!1031 = !DILocation(line: 570, column: 7, scope: !1027)
!1032 = !DILocation(line: 571, column: 15, scope: !1033)
!1033 = distinct !DILexicalBlock(scope: !1026, file: !1, line: 570, column: 55)
!1034 = !DILocation(line: 571, column: 8, scope: !1033)
!1035 = !DILocation(line: 571, column: 6, scope: !1033)
!1036 = !DILocation(line: 572, column: 8, scope: !1037)
!1037 = distinct !DILexicalBlock(scope: !1033, file: !1, line: 572, column: 8)
!1038 = !DILocation(line: 572, column: 10, scope: !1037)
!1039 = !DILocation(line: 572, column: 14, scope: !1037)
!1040 = !DILocation(line: 572, column: 20, scope: !1041)
!1041 = !DILexicalBlockFile(scope: !1037, file: !1, discriminator: 1)
!1042 = !DILocation(line: 572, column: 22, scope: !1041)
!1043 = !DILocation(line: 572, column: 17, scope: !1041)
!1044 = !DILocation(line: 572, column: 27, scope: !1041)
!1045 = !DILocation(line: 572, column: 8, scope: !1041)
!1046 = !DILocation(line: 573, column: 32, scope: !1047)
!1047 = distinct !DILexicalBlock(scope: !1037, file: !1, line: 572, column: 36)
!1048 = !DILocation(line: 573, column: 5, scope: !1047)
!1049 = !DILocation(line: 574, column: 4, scope: !1047)
!1050 = !DILocation(line: 575, column: 3, scope: !1033)
!1051 = !DILocation(line: 575, column: 42, scope: !1052)
!1052 = !DILexicalBlockFile(scope: !1053, file: !1, discriminator: 1)
!1053 = distinct !DILexicalBlock(scope: !1026, file: !1, line: 575, column: 14)
!1054 = !DILocation(line: 575, column: 19, scope: !1052)
!1055 = !DILocation(line: 575, column: 17, scope: !1052)
!1056 = !DILocation(line: 575, column: 50, scope: !1052)
!1057 = !DILocation(line: 575, column: 14, scope: !1052)
!1058 = !DILocation(line: 576, column: 15, scope: !1059)
!1059 = distinct !DILexicalBlock(scope: !1053, file: !1, line: 575, column: 59)
!1060 = !DILocation(line: 576, column: 8, scope: !1059)
!1061 = !DILocation(line: 576, column: 6, scope: !1059)
!1062 = !DILocation(line: 577, column: 8, scope: !1063)
!1063 = distinct !DILexicalBlock(scope: !1059, file: !1, line: 577, column: 8)
!1064 = !DILocation(line: 577, column: 10, scope: !1063)
!1065 = !DILocation(line: 577, column: 14, scope: !1063)
!1066 = !DILocation(line: 577, column: 19, scope: !1067)
!1067 = !DILexicalBlockFile(scope: !1063, file: !1, discriminator: 1)
!1068 = !DILocation(line: 577, column: 21, scope: !1067)
!1069 = !DILocation(line: 577, column: 17, scope: !1067)
!1070 = !DILocation(line: 577, column: 26, scope: !1067)
!1071 = !DILocation(line: 577, column: 8, scope: !1067)
!1072 = !DILocation(line: 578, column: 32, scope: !1073)
!1073 = distinct !DILexicalBlock(scope: !1063, file: !1, line: 577, column: 34)
!1074 = !DILocation(line: 578, column: 5, scope: !1073)
!1075 = !DILocation(line: 579, column: 4, scope: !1073)
!1076 = !DILocation(line: 580, column: 3, scope: !1059)
!1077 = !DILocation(line: 581, column: 2, scope: !1027)
!1078 = !DILocation(line: 582, column: 10, scope: !464)
!1079 = !DILocation(line: 582, column: 2, scope: !464)
!1080 = !DILocation(line: 583, column: 1, scope: !464)
!1081 = !DILocalVariable(name: "a", arg: 1, scope: !546, file: !1, line: 586, type: !4)
!1082 = !DILocation(line: 586, column: 56, scope: !546)
!1083 = !DILocalVariable(name: "buff", arg: 2, scope: !546, file: !1, line: 587, type: !64)
!1084 = !DILocation(line: 587, column: 18, scope: !546)
!1085 = !DILocalVariable(name: "size", arg: 3, scope: !546, file: !1, line: 587, type: !65)
!1086 = !DILocation(line: 587, column: 32, scope: !546)
!1087 = !DILocalVariable(name: "offset", arg: 4, scope: !546, file: !1, line: 587, type: !66)
!1088 = !DILocation(line: 587, column: 47, scope: !546)
!1089 = !DILocalVariable(name: "bytes_read", scope: !546, file: !1, line: 589, type: !38)
!1090 = !DILocation(line: 589, column: 10, scope: !546)
!1091 = !DILocalVariable(name: "tar", scope: !546, file: !1, line: 590, type: !291)
!1092 = !DILocation(line: 590, column: 14, scope: !546)
!1093 = !DILocalVariable(name: "p", scope: !546, file: !1, line: 591, type: !314)
!1094 = !DILocation(line: 591, column: 23, scope: !546)
!1095 = !DILocation(line: 593, column: 23, scope: !546)
!1096 = !DILocation(line: 593, column: 26, scope: !546)
!1097 = !DILocation(line: 593, column: 34, scope: !546)
!1098 = !DILocation(line: 593, column: 8, scope: !546)
!1099 = !DILocation(line: 593, column: 6, scope: !546)
!1100 = !DILocation(line: 595, column: 2, scope: !546)
!1101 = !DILocation(line: 597, column: 3, scope: !1102)
!1102 = distinct !DILexicalBlock(scope: !1103, file: !1, line: 595, column: 11)
!1103 = distinct !DILexicalBlock(scope: !1104, file: !1, line: 595, column: 2)
!1104 = distinct !DILexicalBlock(scope: !546, file: !1, line: 595, column: 2)
!1105 = !DILocation(line: 597, column: 10, scope: !1106)
!1106 = !DILexicalBlockFile(scope: !1102, file: !1, discriminator: 1)
!1107 = !DILocation(line: 597, column: 15, scope: !1106)
!1108 = !DILocation(line: 597, column: 27, scope: !1106)
!1109 = !DILocation(line: 597, column: 35, scope: !1106)
!1110 = !DILocation(line: 598, column: 7, scope: !1102)
!1111 = !DILocation(line: 598, column: 12, scope: !1102)
!1112 = !DILocation(line: 598, column: 25, scope: !1102)
!1113 = !DILocation(line: 598, column: 35, scope: !1102)
!1114 = !DILocation(line: 597, column: 3, scope: !1115)
!1115 = !DILexicalBlockFile(scope: !1102, file: !1, discriminator: 2)
!1116 = !DILocation(line: 599, column: 8, scope: !1117)
!1117 = distinct !DILexicalBlock(scope: !1102, file: !1, line: 598, column: 41)
!1118 = !DILocation(line: 599, column: 13, scope: !1117)
!1119 = !DILocation(line: 599, column: 6, scope: !1117)
!1120 = !DILocation(line: 600, column: 23, scope: !1117)
!1121 = !DILocation(line: 600, column: 26, scope: !1117)
!1122 = !DILocation(line: 600, column: 4, scope: !1117)
!1123 = !DILocation(line: 600, column: 9, scope: !1117)
!1124 = !DILocation(line: 600, column: 21, scope: !1117)
!1125 = !DILocation(line: 601, column: 9, scope: !1117)
!1126 = !DILocation(line: 601, column: 4, scope: !1117)
!1127 = !DILocation(line: 597, column: 3, scope: !1128)
!1128 = !DILexicalBlockFile(scope: !1102, file: !1, discriminator: 3)
!1129 = !DILocation(line: 604, column: 7, scope: !1130)
!1130 = distinct !DILexicalBlock(scope: !1102, file: !1, line: 604, column: 7)
!1131 = !DILocation(line: 604, column: 12, scope: !1130)
!1132 = !DILocation(line: 604, column: 7, scope: !1102)
!1133 = !DILocation(line: 605, column: 27, scope: !1134)
!1134 = distinct !DILexicalBlock(scope: !1130, file: !1, line: 604, column: 36)
!1135 = !DILocation(line: 605, column: 30, scope: !1134)
!1136 = !DILocation(line: 605, column: 35, scope: !1134)
!1137 = !DILocation(line: 605, column: 4, scope: !1134)
!1138 = !DILocation(line: 606, column: 4, scope: !1134)
!1139 = !DILocation(line: 606, column: 9, scope: !1134)
!1140 = !DILocation(line: 606, column: 32, scope: !1134)
!1141 = !DILocation(line: 607, column: 3, scope: !1134)
!1142 = !DILocation(line: 610, column: 7, scope: !1143)
!1143 = distinct !DILexicalBlock(scope: !1102, file: !1, line: 610, column: 7)
!1144 = !DILocation(line: 610, column: 12, scope: !1143)
!1145 = !DILocation(line: 610, column: 24, scope: !1143)
!1146 = !DILocation(line: 610, column: 32, scope: !1143)
!1147 = !DILocation(line: 611, column: 7, scope: !1143)
!1148 = !DILocation(line: 611, column: 12, scope: !1143)
!1149 = !DILocation(line: 611, column: 34, scope: !1143)
!1150 = !DILocation(line: 610, column: 7, scope: !1106)
!1151 = !DILocation(line: 612, column: 31, scope: !1152)
!1152 = distinct !DILexicalBlock(scope: !1153, file: !1, line: 612, column: 8)
!1153 = distinct !DILexicalBlock(scope: !1143, file: !1, line: 611, column: 40)
!1154 = !DILocation(line: 612, column: 34, scope: !1152)
!1155 = !DILocation(line: 612, column: 39, scope: !1152)
!1156 = !DILocation(line: 612, column: 8, scope: !1152)
!1157 = !DILocation(line: 612, column: 54, scope: !1152)
!1158 = !DILocation(line: 612, column: 8, scope: !1153)
!1159 = !DILocation(line: 613, column: 5, scope: !1152)
!1160 = !DILocation(line: 614, column: 4, scope: !1153)
!1161 = !DILocation(line: 614, column: 9, scope: !1153)
!1162 = !DILocation(line: 614, column: 23, scope: !1153)
!1163 = !DILocation(line: 615, column: 5, scope: !1153)
!1164 = !DILocation(line: 615, column: 10, scope: !1153)
!1165 = !DILocation(line: 616, column: 5, scope: !1153)
!1166 = !DILocation(line: 616, column: 10, scope: !1153)
!1167 = !DILocation(line: 617, column: 14, scope: !1153)
!1168 = !DILocation(line: 617, column: 19, scope: !1153)
!1169 = !DILocation(line: 617, column: 5, scope: !1153)
!1170 = !DILocation(line: 617, column: 12, scope: !1153)
!1171 = !DILocation(line: 618, column: 4, scope: !1153)
!1172 = !DILocation(line: 621, column: 32, scope: !1102)
!1173 = !DILocation(line: 621, column: 11, scope: !1102)
!1174 = !DILocation(line: 621, column: 4, scope: !1102)
!1175 = !DILocation(line: 621, column: 9, scope: !1102)
!1176 = !DILocation(line: 622, column: 7, scope: !1177)
!1177 = distinct !DILexicalBlock(scope: !1102, file: !1, line: 622, column: 7)
!1178 = !DILocation(line: 622, column: 18, scope: !1177)
!1179 = !DILocation(line: 622, column: 7, scope: !1102)
!1180 = !DILocation(line: 623, column: 4, scope: !1177)
!1181 = !DILocation(line: 624, column: 8, scope: !1182)
!1182 = distinct !DILexicalBlock(scope: !1102, file: !1, line: 624, column: 7)
!1183 = !DILocation(line: 624, column: 7, scope: !1182)
!1184 = !DILocation(line: 624, column: 13, scope: !1182)
!1185 = !DILocation(line: 624, column: 7, scope: !1102)
!1186 = !DILocation(line: 625, column: 23, scope: !1187)
!1187 = distinct !DILexicalBlock(scope: !1182, file: !1, line: 624, column: 22)
!1188 = !DILocation(line: 625, column: 26, scope: !1187)
!1189 = !DILocation(line: 625, column: 4, scope: !1187)
!1190 = !DILocation(line: 627, column: 4, scope: !1187)
!1191 = !DILocation(line: 629, column: 7, scope: !1192)
!1192 = distinct !DILexicalBlock(scope: !1102, file: !1, line: 629, column: 7)
!1193 = !DILocation(line: 629, column: 20, scope: !1192)
!1194 = !DILocation(line: 629, column: 25, scope: !1192)
!1195 = !DILocation(line: 629, column: 18, scope: !1192)
!1196 = !DILocation(line: 629, column: 7, scope: !1102)
!1197 = !DILocation(line: 630, column: 26, scope: !1192)
!1198 = !DILocation(line: 630, column: 31, scope: !1192)
!1199 = !DILocation(line: 630, column: 15, scope: !1192)
!1200 = !DILocation(line: 630, column: 4, scope: !1192)
!1201 = !DILocation(line: 633, column: 7, scope: !1202)
!1202 = distinct !DILexicalBlock(scope: !1102, file: !1, line: 633, column: 7)
!1203 = !DILocation(line: 633, column: 12, scope: !1202)
!1204 = !DILocation(line: 633, column: 25, scope: !1202)
!1205 = !DILocation(line: 633, column: 37, scope: !1202)
!1206 = !DILocation(line: 633, column: 35, scope: !1202)
!1207 = !DILocation(line: 633, column: 7, scope: !1102)
!1208 = !DILocation(line: 634, column: 26, scope: !1202)
!1209 = !DILocation(line: 634, column: 31, scope: !1202)
!1210 = !DILocation(line: 634, column: 44, scope: !1202)
!1211 = !DILocation(line: 634, column: 15, scope: !1202)
!1212 = !DILocation(line: 634, column: 4, scope: !1202)
!1213 = !DILocation(line: 635, column: 11, scope: !1102)
!1214 = !DILocation(line: 635, column: 4, scope: !1102)
!1215 = !DILocation(line: 635, column: 9, scope: !1102)
!1216 = !DILocation(line: 636, column: 13, scope: !1102)
!1217 = !DILocation(line: 636, column: 18, scope: !1102)
!1218 = !DILocation(line: 636, column: 31, scope: !1102)
!1219 = !DILocation(line: 636, column: 4, scope: !1102)
!1220 = !DILocation(line: 636, column: 11, scope: !1102)
!1221 = !DILocation(line: 637, column: 34, scope: !1102)
!1222 = !DILocation(line: 637, column: 3, scope: !1102)
!1223 = !DILocation(line: 637, column: 8, scope: !1102)
!1224 = !DILocation(line: 637, column: 21, scope: !1102)
!1225 = !DILocation(line: 637, column: 31, scope: !1102)
!1226 = !DILocation(line: 638, column: 31, scope: !1102)
!1227 = !DILocation(line: 638, column: 3, scope: !1102)
!1228 = !DILocation(line: 638, column: 8, scope: !1102)
!1229 = !DILocation(line: 638, column: 21, scope: !1102)
!1230 = !DILocation(line: 638, column: 28, scope: !1102)
!1231 = !DILocation(line: 639, column: 33, scope: !1102)
!1232 = !DILocation(line: 639, column: 3, scope: !1102)
!1233 = !DILocation(line: 639, column: 8, scope: !1102)
!1234 = !DILocation(line: 639, column: 30, scope: !1102)
!1235 = !DILocation(line: 640, column: 33, scope: !1102)
!1236 = !DILocation(line: 640, column: 3, scope: !1102)
!1237 = !DILocation(line: 640, column: 8, scope: !1102)
!1238 = !DILocation(line: 640, column: 31, scope: !1102)
!1239 = !DILocation(line: 642, column: 8, scope: !1240)
!1240 = distinct !DILexicalBlock(scope: !1102, file: !1, line: 642, column: 7)
!1241 = !DILocation(line: 642, column: 13, scope: !1240)
!1242 = !DILocation(line: 642, column: 26, scope: !1240)
!1243 = !DILocation(line: 642, column: 7, scope: !1102)
!1244 = !DILocation(line: 643, column: 4, scope: !1240)
!1245 = !DILocation(line: 595, column: 2, scope: !1246)
!1246 = !DILexicalBlockFile(scope: !1103, file: !1, discriminator: 1)
!1247 = !DILocation(line: 646, column: 1, scope: !546)
!1248 = !DILocalVariable(name: "a", arg: 1, scope: !547, file: !1, line: 649, type: !4)
!1249 = !DILocation(line: 649, column: 51, scope: !547)
!1250 = !DILocalVariable(name: "bytes_skipped", scope: !547, file: !1, line: 651, type: !52)
!1251 = !DILocation(line: 651, column: 10, scope: !547)
!1252 = !DILocalVariable(name: "request", scope: !547, file: !1, line: 652, type: !52)
!1253 = !DILocation(line: 652, column: 10, scope: !547)
!1254 = !DILocalVariable(name: "p", scope: !547, file: !1, line: 653, type: !314)
!1255 = !DILocation(line: 653, column: 23, scope: !547)
!1256 = !DILocalVariable(name: "tar", scope: !547, file: !1, line: 654, type: !291)
!1257 = !DILocation(line: 654, column: 14, scope: !547)
!1258 = !DILocation(line: 656, column: 23, scope: !547)
!1259 = !DILocation(line: 656, column: 26, scope: !547)
!1260 = !DILocation(line: 656, column: 34, scope: !547)
!1261 = !DILocation(line: 656, column: 8, scope: !547)
!1262 = !DILocation(line: 656, column: 6, scope: !547)
!1263 = !DILocation(line: 659, column: 10, scope: !547)
!1264 = !DILocation(line: 660, column: 11, scope: !1265)
!1265 = distinct !DILexicalBlock(scope: !547, file: !1, line: 660, column: 2)
!1266 = !DILocation(line: 660, column: 16, scope: !1265)
!1267 = !DILocation(line: 660, column: 9, scope: !1265)
!1268 = !DILocation(line: 660, column: 7, scope: !1265)
!1269 = !DILocation(line: 660, column: 29, scope: !1270)
!1270 = !DILexicalBlockFile(scope: !1271, file: !1, discriminator: 1)
!1271 = distinct !DILexicalBlock(scope: !1265, file: !1, line: 660, column: 2)
!1272 = !DILocation(line: 660, column: 31, scope: !1270)
!1273 = !DILocation(line: 660, column: 2, scope: !1270)
!1274 = !DILocation(line: 661, column: 8, scope: !1275)
!1275 = distinct !DILexicalBlock(scope: !1276, file: !1, line: 661, column: 7)
!1276 = distinct !DILexicalBlock(scope: !1271, file: !1, line: 660, column: 53)
!1277 = !DILocation(line: 661, column: 11, scope: !1275)
!1278 = !DILocation(line: 661, column: 7, scope: !1276)
!1279 = !DILocation(line: 662, column: 8, scope: !1280)
!1280 = distinct !DILexicalBlock(scope: !1281, file: !1, line: 662, column: 8)
!1281 = distinct !DILexicalBlock(scope: !1275, file: !1, line: 661, column: 17)
!1282 = !DILocation(line: 662, column: 11, scope: !1280)
!1283 = !DILocation(line: 662, column: 36, scope: !1280)
!1284 = !DILocation(line: 662, column: 34, scope: !1280)
!1285 = !DILocation(line: 662, column: 21, scope: !1280)
!1286 = !DILocation(line: 662, column: 8, scope: !1281)
!1287 = !DILocation(line: 663, column: 5, scope: !1288)
!1288 = distinct !DILexicalBlock(scope: !1280, file: !1, line: 662, column: 45)
!1289 = !DILocation(line: 665, column: 15, scope: !1281)
!1290 = !DILocation(line: 665, column: 18, scope: !1281)
!1291 = !DILocation(line: 665, column: 12, scope: !1281)
!1292 = !DILocation(line: 666, column: 3, scope: !1281)
!1293 = !DILocation(line: 667, column: 2, scope: !1276)
!1294 = !DILocation(line: 660, column: 44, scope: !1295)
!1295 = !DILexicalBlockFile(scope: !1271, file: !1, discriminator: 2)
!1296 = !DILocation(line: 660, column: 47, scope: !1295)
!1297 = !DILocation(line: 660, column: 42, scope: !1295)
!1298 = !DILocation(line: 660, column: 2, scope: !1295)
!1299 = !DILocation(line: 668, column: 6, scope: !1300)
!1300 = distinct !DILexicalBlock(scope: !547, file: !1, line: 668, column: 6)
!1301 = !DILocation(line: 668, column: 16, scope: !1300)
!1302 = !DILocation(line: 668, column: 21, scope: !1300)
!1303 = !DILocation(line: 668, column: 14, scope: !1300)
!1304 = !DILocation(line: 668, column: 6, scope: !547)
!1305 = !DILocation(line: 669, column: 13, scope: !1300)
!1306 = !DILocation(line: 669, column: 18, scope: !1300)
!1307 = !DILocation(line: 669, column: 11, scope: !1300)
!1308 = !DILocation(line: 669, column: 3, scope: !1300)
!1309 = !DILocation(line: 670, column: 13, scope: !547)
!1310 = !DILocation(line: 670, column: 18, scope: !547)
!1311 = !DILocation(line: 670, column: 34, scope: !547)
!1312 = !DILocation(line: 670, column: 39, scope: !547)
!1313 = !DILocation(line: 670, column: 32, scope: !547)
!1314 = !DILocation(line: 670, column: 10, scope: !547)
!1315 = !DILocation(line: 672, column: 41, scope: !547)
!1316 = !DILocation(line: 672, column: 44, scope: !547)
!1317 = !DILocation(line: 672, column: 18, scope: !547)
!1318 = !DILocation(line: 672, column: 16, scope: !547)
!1319 = !DILocation(line: 673, column: 6, scope: !1320)
!1320 = distinct !DILexicalBlock(scope: !547, file: !1, line: 673, column: 6)
!1321 = !DILocation(line: 673, column: 20, scope: !1320)
!1322 = !DILocation(line: 673, column: 6, scope: !547)
!1323 = !DILocation(line: 674, column: 3, scope: !1320)
!1324 = !DILocation(line: 676, column: 2, scope: !547)
!1325 = !DILocation(line: 676, column: 7, scope: !547)
!1326 = !DILocation(line: 676, column: 29, scope: !547)
!1327 = !DILocation(line: 677, column: 2, scope: !547)
!1328 = !DILocation(line: 677, column: 7, scope: !547)
!1329 = !DILocation(line: 677, column: 30, scope: !547)
!1330 = !DILocation(line: 678, column: 2, scope: !547)
!1331 = !DILocation(line: 678, column: 7, scope: !547)
!1332 = !DILocation(line: 678, column: 21, scope: !547)
!1333 = !DILocation(line: 681, column: 24, scope: !547)
!1334 = !DILocation(line: 681, column: 2, scope: !547)
!1335 = !DILocation(line: 683, column: 2, scope: !547)
!1336 = !DILocation(line: 684, column: 1, scope: !547)
!1337 = !DILocalVariable(name: "a", arg: 1, scope: !441, file: !1, line: 280, type: !4)
!1338 = !DILocation(line: 280, column: 54, scope: !441)
!1339 = !DILocalVariable(name: "tar", scope: !441, file: !1, line: 282, type: !291)
!1340 = !DILocation(line: 282, column: 14, scope: !441)
!1341 = !DILocation(line: 284, column: 23, scope: !441)
!1342 = !DILocation(line: 284, column: 26, scope: !441)
!1343 = !DILocation(line: 284, column: 34, scope: !441)
!1344 = !DILocation(line: 284, column: 8, scope: !441)
!1345 = !DILocation(line: 284, column: 6, scope: !441)
!1346 = !DILocation(line: 285, column: 24, scope: !441)
!1347 = !DILocation(line: 285, column: 2, scope: !441)
!1348 = !DILocation(line: 286, column: 23, scope: !441)
!1349 = !DILocation(line: 286, column: 28, scope: !441)
!1350 = !DILocation(line: 286, column: 2, scope: !441)
!1351 = !DILocation(line: 287, column: 23, scope: !441)
!1352 = !DILocation(line: 287, column: 28, scope: !441)
!1353 = !DILocation(line: 287, column: 2, scope: !441)
!1354 = !DILocation(line: 288, column: 23, scope: !441)
!1355 = !DILocation(line: 288, column: 28, scope: !441)
!1356 = !DILocation(line: 288, column: 2, scope: !441)
!1357 = !DILocation(line: 289, column: 23, scope: !441)
!1358 = !DILocation(line: 289, column: 28, scope: !441)
!1359 = !DILocation(line: 289, column: 2, scope: !441)
!1360 = !DILocation(line: 290, column: 23, scope: !441)
!1361 = !DILocation(line: 290, column: 28, scope: !441)
!1362 = !DILocation(line: 290, column: 2, scope: !441)
!1363 = !DILocation(line: 291, column: 23, scope: !441)
!1364 = !DILocation(line: 291, column: 28, scope: !441)
!1365 = !DILocation(line: 291, column: 2, scope: !441)
!1366 = !DILocation(line: 292, column: 23, scope: !441)
!1367 = !DILocation(line: 292, column: 28, scope: !441)
!1368 = !DILocation(line: 292, column: 2, scope: !441)
!1369 = !DILocation(line: 293, column: 23, scope: !441)
!1370 = !DILocation(line: 293, column: 28, scope: !441)
!1371 = !DILocation(line: 293, column: 2, scope: !441)
!1372 = !DILocation(line: 294, column: 23, scope: !441)
!1373 = !DILocation(line: 294, column: 28, scope: !441)
!1374 = !DILocation(line: 294, column: 2, scope: !441)
!1375 = !DILocation(line: 295, column: 23, scope: !441)
!1376 = !DILocation(line: 295, column: 28, scope: !441)
!1377 = !DILocation(line: 295, column: 2, scope: !441)
!1378 = !DILocation(line: 296, column: 23, scope: !441)
!1379 = !DILocation(line: 296, column: 28, scope: !441)
!1380 = !DILocation(line: 296, column: 2, scope: !441)
!1381 = !DILocation(line: 297, column: 23, scope: !441)
!1382 = !DILocation(line: 297, column: 28, scope: !441)
!1383 = !DILocation(line: 297, column: 2, scope: !441)
!1384 = !DILocation(line: 298, column: 7, scope: !441)
!1385 = !DILocation(line: 298, column: 2, scope: !441)
!1386 = !DILocation(line: 299, column: 3, scope: !441)
!1387 = !DILocation(line: 299, column: 6, scope: !441)
!1388 = !DILocation(line: 299, column: 14, scope: !441)
!1389 = !DILocation(line: 299, column: 20, scope: !441)
!1390 = !DILocation(line: 300, column: 2, scope: !441)
!1391 = !DILocalVariable(name: "tar", arg: 1, scope: !442, file: !1, line: 2250, type: !291)
!1392 = !DILocation(line: 2250, column: 35, scope: !442)
!1393 = !DILocalVariable(name: "p", scope: !442, file: !1, line: 2252, type: !314)
!1394 = !DILocation(line: 2252, column: 23, scope: !442)
!1395 = !DILocation(line: 2254, column: 2, scope: !442)
!1396 = !DILocation(line: 2254, column: 9, scope: !1397)
!1397 = !DILexicalBlockFile(scope: !442, file: !1, discriminator: 1)
!1398 = !DILocation(line: 2254, column: 14, scope: !1397)
!1399 = !DILocation(line: 2254, column: 26, scope: !1397)
!1400 = !DILocation(line: 2254, column: 2, scope: !1397)
!1401 = !DILocation(line: 2255, column: 7, scope: !1402)
!1402 = distinct !DILexicalBlock(scope: !442, file: !1, line: 2254, column: 35)
!1403 = !DILocation(line: 2255, column: 12, scope: !1402)
!1404 = !DILocation(line: 2255, column: 5, scope: !1402)
!1405 = !DILocation(line: 2256, column: 22, scope: !1402)
!1406 = !DILocation(line: 2256, column: 25, scope: !1402)
!1407 = !DILocation(line: 2256, column: 3, scope: !1402)
!1408 = !DILocation(line: 2256, column: 8, scope: !1402)
!1409 = !DILocation(line: 2256, column: 20, scope: !1402)
!1410 = !DILocation(line: 2257, column: 8, scope: !1402)
!1411 = !DILocation(line: 2257, column: 3, scope: !1402)
!1412 = !DILocation(line: 2254, column: 2, scope: !1413)
!1413 = !DILexicalBlockFile(scope: !442, file: !1, discriminator: 2)
!1414 = !DILocation(line: 2259, column: 2, scope: !442)
!1415 = !DILocation(line: 2259, column: 7, scope: !442)
!1416 = !DILocation(line: 2259, column: 19, scope: !442)
!1417 = !DILocation(line: 2260, column: 1, scope: !442)
!1418 = !DILocalVariable(name: "p", arg: 1, scope: !446, file: !1, line: 928, type: !80)
!1419 = !DILocation(line: 928, column: 35, scope: !446)
!1420 = !DILocalVariable(name: "i", scope: !446, file: !1, line: 930, type: !13)
!1421 = !DILocation(line: 930, column: 11, scope: !446)
!1422 = !DILocation(line: 932, column: 9, scope: !1423)
!1423 = distinct !DILexicalBlock(scope: !446, file: !1, line: 932, column: 2)
!1424 = !DILocation(line: 932, column: 7, scope: !1423)
!1425 = !DILocation(line: 932, column: 14, scope: !1426)
!1426 = !DILexicalBlockFile(scope: !1427, file: !1, discriminator: 1)
!1427 = distinct !DILexicalBlock(scope: !1423, file: !1, line: 932, column: 2)
!1428 = !DILocation(line: 932, column: 16, scope: !1426)
!1429 = !DILocation(line: 932, column: 2, scope: !1426)
!1430 = !DILocation(line: 933, column: 9, scope: !1431)
!1431 = distinct !DILexicalBlock(scope: !1427, file: !1, line: 933, column: 7)
!1432 = !DILocation(line: 933, column: 7, scope: !1431)
!1433 = !DILocation(line: 933, column: 7, scope: !1427)
!1434 = !DILocation(line: 934, column: 4, scope: !1431)
!1435 = !DILocation(line: 933, column: 9, scope: !1436)
!1436 = !DILexicalBlockFile(scope: !1431, file: !1, discriminator: 1)
!1437 = !DILocation(line: 932, column: 24, scope: !1438)
!1438 = !DILexicalBlockFile(scope: !1427, file: !1, discriminator: 2)
!1439 = !DILocation(line: 932, column: 2, scope: !1438)
!1440 = !DILocation(line: 935, column: 2, scope: !446)
!1441 = !DILocation(line: 936, column: 1, scope: !446)
!1442 = !DILocalVariable(name: "a", arg: 1, scope: !449, file: !1, line: 873, type: !4)
!1443 = !DILocation(line: 873, column: 31, scope: !449)
!1444 = !DILocalVariable(name: "h", arg: 2, scope: !449, file: !1, line: 873, type: !43)
!1445 = !DILocation(line: 873, column: 46, scope: !449)
!1446 = !DILocalVariable(name: "bytes", scope: !449, file: !1, line: 875, type: !380)
!1447 = !DILocation(line: 875, column: 23, scope: !449)
!1448 = !DILocalVariable(name: "header", scope: !449, file: !1, line: 876, type: !336)
!1449 = !DILocation(line: 876, column: 43, scope: !449)
!1450 = !DILocalVariable(name: "check", scope: !449, file: !1, line: 877, type: !23)
!1451 = !DILocation(line: 877, column: 6, scope: !449)
!1452 = !DILocalVariable(name: "sum", scope: !449, file: !1, line: 877, type: !23)
!1453 = !DILocation(line: 877, column: 13, scope: !449)
!1454 = !DILocalVariable(name: "i", scope: !449, file: !1, line: 878, type: !45)
!1455 = !DILocation(line: 878, column: 9, scope: !449)
!1456 = !DILocation(line: 880, column: 8, scope: !449)
!1457 = !DILocation(line: 881, column: 33, scope: !449)
!1458 = !DILocation(line: 881, column: 8, scope: !449)
!1459 = !DILocation(line: 882, column: 54, scope: !449)
!1460 = !DILocation(line: 882, column: 11, scope: !449)
!1461 = !DILocation(line: 882, column: 9, scope: !449)
!1462 = !DILocation(line: 885, column: 9, scope: !1463)
!1463 = distinct !DILexicalBlock(scope: !449, file: !1, line: 885, column: 2)
!1464 = !DILocation(line: 885, column: 7, scope: !1463)
!1465 = !DILocation(line: 885, column: 14, scope: !1466)
!1466 = !DILexicalBlockFile(scope: !1467, file: !1, discriminator: 1)
!1467 = distinct !DILexicalBlock(scope: !1463, file: !1, line: 885, column: 2)
!1468 = !DILocation(line: 885, column: 16, scope: !1466)
!1469 = !DILocation(line: 885, column: 2, scope: !1466)
!1470 = !DILocalVariable(name: "c", scope: !1471, file: !1, line: 886, type: !82)
!1471 = distinct !DILexicalBlock(scope: !1467, file: !1, line: 885, column: 49)
!1472 = !DILocation(line: 886, column: 8, scope: !1471)
!1473 = !DILocation(line: 886, column: 29, scope: !1471)
!1474 = !DILocation(line: 886, column: 12, scope: !1471)
!1475 = !DILocation(line: 886, column: 20, scope: !1471)
!1476 = !DILocation(line: 887, column: 7, scope: !1477)
!1477 = distinct !DILexicalBlock(scope: !1471, file: !1, line: 887, column: 7)
!1478 = !DILocation(line: 887, column: 9, scope: !1477)
!1479 = !DILocation(line: 887, column: 16, scope: !1477)
!1480 = !DILocation(line: 887, column: 19, scope: !1481)
!1481 = !DILexicalBlockFile(scope: !1477, file: !1, discriminator: 1)
!1482 = !DILocation(line: 887, column: 21, scope: !1481)
!1483 = !DILocation(line: 887, column: 29, scope: !1481)
!1484 = !DILocation(line: 887, column: 33, scope: !1485)
!1485 = !DILexicalBlockFile(scope: !1477, file: !1, discriminator: 2)
!1486 = !DILocation(line: 887, column: 35, scope: !1485)
!1487 = !DILocation(line: 887, column: 41, scope: !1485)
!1488 = !DILocation(line: 887, column: 44, scope: !1489)
!1489 = !DILexicalBlockFile(scope: !1477, file: !1, discriminator: 3)
!1490 = !DILocation(line: 887, column: 46, scope: !1489)
!1491 = !DILocation(line: 887, column: 7, scope: !1489)
!1492 = !DILocation(line: 888, column: 4, scope: !1477)
!1493 = !DILocation(line: 889, column: 2, scope: !1471)
!1494 = !DILocation(line: 885, column: 44, scope: !1495)
!1495 = !DILexicalBlockFile(scope: !1467, file: !1, discriminator: 2)
!1496 = !DILocation(line: 885, column: 2, scope: !1495)
!1497 = !DILocation(line: 895, column: 22, scope: !449)
!1498 = !DILocation(line: 895, column: 30, scope: !449)
!1499 = !DILocation(line: 895, column: 13, scope: !449)
!1500 = !DILocation(line: 895, column: 8, scope: !449)
!1501 = !DILocation(line: 895, column: 6, scope: !449)
!1502 = !DILocation(line: 896, column: 8, scope: !449)
!1503 = !DILocation(line: 897, column: 9, scope: !1504)
!1504 = distinct !DILexicalBlock(scope: !449, file: !1, line: 897, column: 2)
!1505 = !DILocation(line: 897, column: 7, scope: !1504)
!1506 = !DILocation(line: 897, column: 14, scope: !1507)
!1507 = !DILexicalBlockFile(scope: !1508, file: !1, discriminator: 1)
!1508 = distinct !DILexicalBlock(scope: !1504, file: !1, line: 897, column: 2)
!1509 = !DILocation(line: 897, column: 16, scope: !1507)
!1510 = !DILocation(line: 897, column: 2, scope: !1507)
!1511 = !DILocation(line: 898, column: 33, scope: !1508)
!1512 = !DILocation(line: 898, column: 27, scope: !1508)
!1513 = !DILocation(line: 898, column: 12, scope: !1508)
!1514 = !DILocation(line: 898, column: 9, scope: !1508)
!1515 = !DILocation(line: 898, column: 3, scope: !1508)
!1516 = !DILocation(line: 897, column: 24, scope: !1517)
!1517 = !DILexicalBlockFile(scope: !1508, file: !1, discriminator: 2)
!1518 = !DILocation(line: 897, column: 2, scope: !1517)
!1519 = !DILocation(line: 899, column: 2, scope: !449)
!1520 = !DILocation(line: 899, column: 9, scope: !1521)
!1521 = !DILexicalBlockFile(scope: !1522, file: !1, discriminator: 1)
!1522 = distinct !DILexicalBlock(scope: !1523, file: !1, line: 899, column: 2)
!1523 = distinct !DILexicalBlock(scope: !449, file: !1, line: 899, column: 2)
!1524 = !DILocation(line: 899, column: 11, scope: !1521)
!1525 = !DILocation(line: 899, column: 2, scope: !1521)
!1526 = !DILocation(line: 900, column: 9, scope: !1522)
!1527 = !DILocation(line: 900, column: 3, scope: !1522)
!1528 = !DILocation(line: 899, column: 19, scope: !1529)
!1529 = !DILexicalBlockFile(scope: !1522, file: !1, discriminator: 2)
!1530 = !DILocation(line: 899, column: 2, scope: !1529)
!1531 = !DILocation(line: 901, column: 2, scope: !449)
!1532 = !DILocation(line: 901, column: 9, scope: !1533)
!1533 = !DILexicalBlockFile(scope: !1534, file: !1, discriminator: 1)
!1534 = distinct !DILexicalBlock(scope: !1535, file: !1, line: 901, column: 2)
!1535 = distinct !DILexicalBlock(scope: !449, file: !1, line: 901, column: 2)
!1536 = !DILocation(line: 901, column: 11, scope: !1533)
!1537 = !DILocation(line: 901, column: 2, scope: !1533)
!1538 = !DILocation(line: 902, column: 33, scope: !1534)
!1539 = !DILocation(line: 902, column: 27, scope: !1534)
!1540 = !DILocation(line: 902, column: 12, scope: !1534)
!1541 = !DILocation(line: 902, column: 9, scope: !1534)
!1542 = !DILocation(line: 902, column: 3, scope: !1534)
!1543 = !DILocation(line: 901, column: 19, scope: !1544)
!1544 = !DILexicalBlockFile(scope: !1534, file: !1, discriminator: 2)
!1545 = !DILocation(line: 901, column: 2, scope: !1544)
!1546 = !DILocation(line: 903, column: 6, scope: !1547)
!1547 = distinct !DILexicalBlock(scope: !449, file: !1, line: 903, column: 6)
!1548 = !DILocation(line: 903, column: 13, scope: !1547)
!1549 = !DILocation(line: 903, column: 10, scope: !1547)
!1550 = !DILocation(line: 903, column: 6, scope: !449)
!1551 = !DILocation(line: 904, column: 3, scope: !1547)
!1552 = !DILocation(line: 911, column: 8, scope: !449)
!1553 = !DILocation(line: 912, column: 9, scope: !1554)
!1554 = distinct !DILexicalBlock(scope: !449, file: !1, line: 912, column: 2)
!1555 = !DILocation(line: 912, column: 7, scope: !1554)
!1556 = !DILocation(line: 912, column: 14, scope: !1557)
!1557 = !DILexicalBlockFile(scope: !1558, file: !1, discriminator: 1)
!1558 = distinct !DILexicalBlock(scope: !1554, file: !1, line: 912, column: 2)
!1559 = !DILocation(line: 912, column: 16, scope: !1557)
!1560 = !DILocation(line: 912, column: 2, scope: !1557)
!1561 = !DILocation(line: 913, column: 31, scope: !1558)
!1562 = !DILocation(line: 913, column: 25, scope: !1558)
!1563 = !DILocation(line: 913, column: 12, scope: !1558)
!1564 = !DILocation(line: 913, column: 9, scope: !1558)
!1565 = !DILocation(line: 913, column: 3, scope: !1558)
!1566 = !DILocation(line: 912, column: 24, scope: !1567)
!1567 = !DILexicalBlockFile(scope: !1558, file: !1, discriminator: 2)
!1568 = !DILocation(line: 912, column: 2, scope: !1567)
!1569 = !DILocation(line: 914, column: 2, scope: !449)
!1570 = !DILocation(line: 914, column: 9, scope: !1571)
!1571 = !DILexicalBlockFile(scope: !1572, file: !1, discriminator: 1)
!1572 = distinct !DILexicalBlock(scope: !1573, file: !1, line: 914, column: 2)
!1573 = distinct !DILexicalBlock(scope: !449, file: !1, line: 914, column: 2)
!1574 = !DILocation(line: 914, column: 11, scope: !1571)
!1575 = !DILocation(line: 914, column: 2, scope: !1571)
!1576 = !DILocation(line: 915, column: 9, scope: !1572)
!1577 = !DILocation(line: 915, column: 3, scope: !1572)
!1578 = !DILocation(line: 914, column: 19, scope: !1579)
!1579 = !DILexicalBlockFile(scope: !1572, file: !1, discriminator: 2)
!1580 = !DILocation(line: 914, column: 2, scope: !1579)
!1581 = !DILocation(line: 916, column: 2, scope: !449)
!1582 = !DILocation(line: 916, column: 9, scope: !1583)
!1583 = !DILexicalBlockFile(scope: !1584, file: !1, discriminator: 1)
!1584 = distinct !DILexicalBlock(scope: !1585, file: !1, line: 916, column: 2)
!1585 = distinct !DILexicalBlock(scope: !449, file: !1, line: 916, column: 2)
!1586 = !DILocation(line: 916, column: 11, scope: !1583)
!1587 = !DILocation(line: 916, column: 2, scope: !1583)
!1588 = !DILocation(line: 917, column: 31, scope: !1584)
!1589 = !DILocation(line: 917, column: 25, scope: !1584)
!1590 = !DILocation(line: 917, column: 12, scope: !1584)
!1591 = !DILocation(line: 917, column: 9, scope: !1584)
!1592 = !DILocation(line: 917, column: 3, scope: !1584)
!1593 = !DILocation(line: 916, column: 19, scope: !1594)
!1594 = !DILexicalBlockFile(scope: !1584, file: !1, discriminator: 2)
!1595 = !DILocation(line: 916, column: 2, scope: !1594)
!1596 = !DILocation(line: 918, column: 6, scope: !1597)
!1597 = distinct !DILexicalBlock(scope: !449, file: !1, line: 918, column: 6)
!1598 = !DILocation(line: 918, column: 13, scope: !1597)
!1599 = !DILocation(line: 918, column: 10, scope: !1597)
!1600 = !DILocation(line: 918, column: 6, scope: !449)
!1601 = !DILocation(line: 919, column: 3, scope: !1597)
!1602 = !DILocation(line: 921, column: 2, scope: !449)
!1603 = !DILocation(line: 922, column: 1, scope: !449)
!1604 = !DILocalVariable(name: "p_field", arg: 1, scope: !460, file: !1, line: 327, type: !80)
!1605 = !DILocation(line: 327, column: 35, scope: !460)
!1606 = !DILocalVariable(name: "i_size", arg: 2, scope: !460, file: !1, line: 327, type: !45)
!1607 = !DILocation(line: 327, column: 51, scope: !460)
!1608 = !DILocalVariable(name: "marker", scope: !460, file: !1, line: 329, type: !382)
!1609 = !DILocation(line: 329, column: 16, scope: !460)
!1610 = !DILocation(line: 329, column: 40, scope: !460)
!1611 = !DILocation(line: 330, column: 6, scope: !1612)
!1612 = distinct !DILexicalBlock(scope: !460, file: !1, line: 330, column: 6)
!1613 = !DILocation(line: 330, column: 13, scope: !1612)
!1614 = !DILocation(line: 330, column: 20, scope: !1612)
!1615 = !DILocation(line: 330, column: 23, scope: !1616)
!1616 = !DILexicalBlockFile(scope: !1612, file: !1, discriminator: 1)
!1617 = !DILocation(line: 330, column: 30, scope: !1616)
!1618 = !DILocation(line: 330, column: 37, scope: !1616)
!1619 = !DILocation(line: 330, column: 40, scope: !1620)
!1620 = !DILexicalBlockFile(scope: !1612, file: !1, discriminator: 2)
!1621 = !DILocation(line: 330, column: 47, scope: !1620)
!1622 = !DILocation(line: 330, column: 6, scope: !1620)
!1623 = !DILocation(line: 332, column: 3, scope: !1624)
!1624 = distinct !DILexicalBlock(scope: !1612, file: !1, line: 330, column: 53)
!1625 = !DILocalVariable(name: "i", scope: !1626, file: !1, line: 335, type: !45)
!1626 = distinct !DILexicalBlock(scope: !1612, file: !1, line: 333, column: 9)
!1627 = !DILocation(line: 335, column: 10, scope: !1626)
!1628 = !DILocation(line: 337, column: 3, scope: !1626)
!1629 = !DILocation(line: 337, column: 10, scope: !1630)
!1630 = !DILexicalBlockFile(scope: !1626, file: !1, discriminator: 1)
!1631 = !DILocation(line: 337, column: 14, scope: !1630)
!1632 = !DILocation(line: 337, column: 12, scope: !1630)
!1633 = !DILocation(line: 337, column: 21, scope: !1630)
!1634 = !DILocation(line: 337, column: 32, scope: !1635)
!1635 = !DILexicalBlockFile(scope: !1626, file: !1, discriminator: 2)
!1636 = !DILocation(line: 337, column: 24, scope: !1635)
!1637 = !DILocation(line: 337, column: 35, scope: !1635)
!1638 = !DILocation(line: 337, column: 3, scope: !1639)
!1639 = !DILexicalBlockFile(scope: !1626, file: !1, discriminator: 3)
!1640 = !DILocation(line: 338, column: 4, scope: !1641)
!1641 = distinct !DILexicalBlock(scope: !1626, file: !1, line: 337, column: 43)
!1642 = !DILocation(line: 337, column: 3, scope: !1643)
!1643 = !DILexicalBlockFile(scope: !1626, file: !1, discriminator: 4)
!1644 = !DILocation(line: 341, column: 3, scope: !1626)
!1645 = !DILocation(line: 341, column: 10, scope: !1630)
!1646 = !DILocation(line: 341, column: 14, scope: !1630)
!1647 = !DILocation(line: 341, column: 12, scope: !1630)
!1648 = !DILocation(line: 341, column: 21, scope: !1630)
!1649 = !DILocation(line: 341, column: 32, scope: !1635)
!1650 = !DILocation(line: 341, column: 24, scope: !1635)
!1651 = !DILocation(line: 341, column: 35, scope: !1635)
!1652 = !DILocation(line: 341, column: 42, scope: !1635)
!1653 = !DILocation(line: 341, column: 53, scope: !1639)
!1654 = !DILocation(line: 341, column: 45, scope: !1639)
!1655 = !DILocation(line: 341, column: 56, scope: !1639)
!1656 = !DILocation(line: 341, column: 3, scope: !1643)
!1657 = !DILocation(line: 342, column: 4, scope: !1658)
!1658 = distinct !DILexicalBlock(scope: !1626, file: !1, line: 341, column: 64)
!1659 = !DILocation(line: 341, column: 3, scope: !1660)
!1660 = !DILexicalBlockFile(scope: !1626, file: !1, discriminator: 5)
!1661 = !DILocation(line: 345, column: 3, scope: !1626)
!1662 = !DILocation(line: 345, column: 10, scope: !1630)
!1663 = !DILocation(line: 345, column: 14, scope: !1630)
!1664 = !DILocation(line: 345, column: 12, scope: !1630)
!1665 = !DILocation(line: 345, column: 3, scope: !1630)
!1666 = !DILocation(line: 346, column: 16, scope: !1667)
!1667 = distinct !DILexicalBlock(scope: !1668, file: !1, line: 346, column: 8)
!1668 = distinct !DILexicalBlock(scope: !1626, file: !1, line: 345, column: 22)
!1669 = !DILocation(line: 346, column: 8, scope: !1667)
!1670 = !DILocation(line: 346, column: 19, scope: !1667)
!1671 = !DILocation(line: 346, column: 26, scope: !1667)
!1672 = !DILocation(line: 346, column: 37, scope: !1673)
!1673 = !DILexicalBlockFile(scope: !1667, file: !1, discriminator: 1)
!1674 = !DILocation(line: 346, column: 29, scope: !1673)
!1675 = !DILocation(line: 346, column: 40, scope: !1673)
!1676 = !DILocation(line: 346, column: 8, scope: !1673)
!1677 = !DILocation(line: 347, column: 5, scope: !1678)
!1678 = distinct !DILexicalBlock(scope: !1667, file: !1, line: 346, column: 46)
!1679 = !DILocation(line: 349, column: 4, scope: !1668)
!1680 = !DILocation(line: 345, column: 3, scope: !1635)
!1681 = !DILocation(line: 351, column: 3, scope: !1626)
!1682 = !DILocation(line: 353, column: 1, scope: !460)
!1683 = !DILocalVariable(name: "p", arg: 1, scope: !452, file: !1, line: 2561, type: !80)
!1684 = !DILocation(line: 2561, column: 22, scope: !452)
!1685 = !DILocalVariable(name: "char_cnt", arg: 2, scope: !452, file: !1, line: 2561, type: !45)
!1686 = !DILocation(line: 2561, column: 32, scope: !452)
!1687 = !DILocation(line: 2567, column: 7, scope: !1688)
!1688 = distinct !DILexicalBlock(scope: !452, file: !1, line: 2567, column: 6)
!1689 = !DILocation(line: 2567, column: 6, scope: !1688)
!1690 = !DILocation(line: 2567, column: 9, scope: !1688)
!1691 = !DILocation(line: 2567, column: 6, scope: !452)
!1692 = !DILocation(line: 2568, column: 23, scope: !1688)
!1693 = !DILocation(line: 2568, column: 26, scope: !1688)
!1694 = !DILocation(line: 2568, column: 11, scope: !1688)
!1695 = !DILocation(line: 2568, column: 3, scope: !1688)
!1696 = !DILocation(line: 2569, column: 20, scope: !452)
!1697 = !DILocation(line: 2569, column: 23, scope: !452)
!1698 = !DILocation(line: 2569, column: 10, scope: !452)
!1699 = !DILocation(line: 2569, column: 2, scope: !452)
!1700 = !DILocation(line: 2570, column: 1, scope: !452)
!1701 = !DILocalVariable(name: "_p", arg: 1, scope: !455, file: !1, line: 2644, type: !80)
!1702 = !DILocation(line: 2644, column: 25, scope: !455)
!1703 = !DILocalVariable(name: "char_cnt", arg: 2, scope: !455, file: !1, line: 2644, type: !45)
!1704 = !DILocation(line: 2644, column: 36, scope: !455)
!1705 = !DILocalVariable(name: "l", scope: !455, file: !1, line: 2646, type: !1706)
!1706 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !53, line: 55, baseType: !47)
!1707 = !DILocation(line: 2646, column: 11, scope: !455)
!1708 = !DILocalVariable(name: "p", scope: !455, file: !1, line: 2647, type: !380)
!1709 = !DILocation(line: 2647, column: 23, scope: !455)
!1710 = !DILocation(line: 2647, column: 50, scope: !455)
!1711 = !DILocalVariable(name: "c", scope: !455, file: !1, line: 2648, type: !382)
!1712 = !DILocation(line: 2648, column: 16, scope: !455)
!1713 = !DILocalVariable(name: "neg", scope: !455, file: !1, line: 2648, type: !382)
!1714 = !DILocation(line: 2648, column: 19, scope: !455)
!1715 = !DILocation(line: 2651, column: 7, scope: !455)
!1716 = !DILocation(line: 2651, column: 6, scope: !455)
!1717 = !DILocation(line: 2651, column: 4, scope: !455)
!1718 = !DILocation(line: 2652, column: 6, scope: !1719)
!1719 = distinct !DILexicalBlock(scope: !455, file: !1, line: 2652, column: 6)
!1720 = !DILocation(line: 2652, column: 8, scope: !1719)
!1721 = !DILocation(line: 2652, column: 6, scope: !455)
!1722 = !DILocation(line: 2653, column: 7, scope: !1723)
!1723 = distinct !DILexicalBlock(scope: !1719, file: !1, line: 2652, column: 16)
!1724 = !DILocation(line: 2654, column: 5, scope: !1723)
!1725 = !DILocation(line: 2655, column: 5, scope: !1723)
!1726 = !DILocation(line: 2656, column: 2, scope: !1723)
!1727 = !DILocation(line: 2657, column: 7, scope: !1728)
!1728 = distinct !DILexicalBlock(scope: !1719, file: !1, line: 2656, column: 9)
!1729 = !DILocation(line: 2658, column: 5, scope: !1728)
!1730 = !DILocation(line: 2659, column: 5, scope: !1728)
!1731 = !DILocation(line: 2664, column: 2, scope: !455)
!1732 = !DILocation(line: 2664, column: 9, scope: !1733)
!1733 = !DILexicalBlockFile(scope: !455, file: !1, discriminator: 1)
!1734 = !DILocation(line: 2664, column: 18, scope: !1733)
!1735 = !DILocation(line: 2664, column: 2, scope: !1733)
!1736 = !DILocation(line: 2665, column: 3, scope: !1737)
!1737 = distinct !DILexicalBlock(scope: !455, file: !1, line: 2664, column: 37)
!1738 = !DILocation(line: 2666, column: 7, scope: !1739)
!1739 = distinct !DILexicalBlock(scope: !1737, file: !1, line: 2666, column: 7)
!1740 = !DILocation(line: 2666, column: 12, scope: !1739)
!1741 = !DILocation(line: 2666, column: 9, scope: !1739)
!1742 = !DILocation(line: 2666, column: 7, scope: !1737)
!1743 = !DILocation(line: 2667, column: 11, scope: !1739)
!1744 = !DILocation(line: 2667, column: 4, scope: !1739)
!1745 = !DILocation(line: 2668, column: 8, scope: !1737)
!1746 = !DILocation(line: 2668, column: 7, scope: !1737)
!1747 = !DILocation(line: 2668, column: 5, scope: !1737)
!1748 = !DILocation(line: 2664, column: 2, scope: !1749)
!1749 = !DILexicalBlockFile(scope: !455, file: !1, discriminator: 2)
!1750 = !DILocation(line: 2672, column: 7, scope: !1751)
!1751 = distinct !DILexicalBlock(scope: !455, file: !1, line: 2672, column: 6)
!1752 = !DILocation(line: 2672, column: 11, scope: !1751)
!1753 = !DILocation(line: 2672, column: 9, scope: !1751)
!1754 = !DILocation(line: 2672, column: 16, scope: !1751)
!1755 = !DILocation(line: 2672, column: 6, scope: !455)
!1756 = !DILocation(line: 2673, column: 10, scope: !1757)
!1757 = distinct !DILexicalBlock(scope: !1751, file: !1, line: 2672, column: 24)
!1758 = !DILocation(line: 2673, column: 3, scope: !1757)
!1759 = !DILocation(line: 2677, column: 2, scope: !455)
!1760 = !DILocation(line: 2677, column: 9, scope: !1733)
!1761 = !DILocation(line: 2677, column: 20, scope: !1733)
!1762 = !DILocation(line: 2677, column: 2, scope: !1733)
!1763 = !DILocation(line: 2678, column: 8, scope: !1764)
!1764 = distinct !DILexicalBlock(scope: !455, file: !1, line: 2677, column: 25)
!1765 = !DILocation(line: 2678, column: 10, scope: !1764)
!1766 = !DILocation(line: 2678, column: 18, scope: !1764)
!1767 = !DILocation(line: 2678, column: 16, scope: !1764)
!1768 = !DILocation(line: 2678, column: 5, scope: !1764)
!1769 = !DILocation(line: 2679, column: 8, scope: !1764)
!1770 = !DILocation(line: 2679, column: 7, scope: !1764)
!1771 = !DILocation(line: 2679, column: 5, scope: !1764)
!1772 = !DILocation(line: 2677, column: 2, scope: !1749)
!1773 = !DILocation(line: 2681, column: 7, scope: !455)
!1774 = !DILocation(line: 2681, column: 9, scope: !455)
!1775 = !DILocation(line: 2681, column: 17, scope: !455)
!1776 = !DILocation(line: 2681, column: 15, scope: !455)
!1777 = !DILocation(line: 2681, column: 4, scope: !455)
!1778 = !DILocation(line: 2683, column: 19, scope: !455)
!1779 = !DILocation(line: 2683, column: 2, scope: !455)
!1780 = !DILocation(line: 2684, column: 1, scope: !455)
!1781 = !DILocalVariable(name: "p", arg: 1, scope: !456, file: !1, line: 2622, type: !80)
!1782 = !DILocation(line: 2622, column: 23, scope: !456)
!1783 = !DILocalVariable(name: "char_cnt", arg: 2, scope: !456, file: !1, line: 2622, type: !45)
!1784 = !DILocation(line: 2622, column: 33, scope: !456)
!1785 = !DILocation(line: 2624, column: 25, scope: !456)
!1786 = !DILocation(line: 2624, column: 28, scope: !456)
!1787 = !DILocation(line: 2624, column: 9, scope: !456)
!1788 = !DILocation(line: 2624, column: 2, scope: !456)
!1789 = !DILocalVariable(name: "p", arg: 1, scope: !457, file: !1, line: 2578, type: !80)
!1790 = !DILocation(line: 2578, column: 29, scope: !457)
!1791 = !DILocalVariable(name: "char_cnt", arg: 2, scope: !457, file: !1, line: 2578, type: !45)
!1792 = !DILocation(line: 2578, column: 39, scope: !457)
!1793 = !DILocalVariable(name: "base", arg: 3, scope: !457, file: !1, line: 2578, type: !23)
!1794 = !DILocation(line: 2578, column: 53, scope: !457)
!1795 = !DILocalVariable(name: "l", scope: !457, file: !1, line: 2580, type: !52)
!1796 = !DILocation(line: 2580, column: 10, scope: !457)
!1797 = !DILocalVariable(name: "maxval", scope: !457, file: !1, line: 2580, type: !52)
!1798 = !DILocation(line: 2580, column: 13, scope: !457)
!1799 = !DILocalVariable(name: "limit", scope: !457, file: !1, line: 2580, type: !52)
!1800 = !DILocation(line: 2580, column: 21, scope: !457)
!1801 = !DILocalVariable(name: "last_digit_limit", scope: !457, file: !1, line: 2580, type: !52)
!1802 = !DILocation(line: 2580, column: 28, scope: !457)
!1803 = !DILocalVariable(name: "digit", scope: !457, file: !1, line: 2581, type: !23)
!1804 = !DILocation(line: 2581, column: 6, scope: !457)
!1805 = !DILocalVariable(name: "sign", scope: !457, file: !1, line: 2581, type: !23)
!1806 = !DILocation(line: 2581, column: 13, scope: !457)
!1807 = !DILocation(line: 2583, column: 9, scope: !457)
!1808 = !DILocation(line: 2584, column: 22, scope: !457)
!1809 = !DILocation(line: 2584, column: 20, scope: !457)
!1810 = !DILocation(line: 2584, column: 8, scope: !457)
!1811 = !DILocation(line: 2585, column: 33, scope: !457)
!1812 = !DILocation(line: 2585, column: 31, scope: !457)
!1813 = !DILocation(line: 2585, column: 19, scope: !457)
!1814 = !DILocation(line: 2590, column: 2, scope: !457)
!1815 = !DILocation(line: 2590, column: 9, scope: !1816)
!1816 = !DILexicalBlockFile(scope: !457, file: !1, discriminator: 1)
!1817 = !DILocation(line: 2590, column: 18, scope: !1816)
!1818 = !DILocation(line: 2590, column: 23, scope: !1816)
!1819 = !DILocation(line: 2590, column: 28, scope: !1820)
!1820 = !DILexicalBlockFile(scope: !457, file: !1, discriminator: 2)
!1821 = !DILocation(line: 2590, column: 27, scope: !1820)
!1822 = !DILocation(line: 2590, column: 30, scope: !1820)
!1823 = !DILocation(line: 2590, column: 37, scope: !1820)
!1824 = !DILocation(line: 2590, column: 41, scope: !1825)
!1825 = !DILexicalBlockFile(scope: !457, file: !1, discriminator: 3)
!1826 = !DILocation(line: 2590, column: 40, scope: !1825)
!1827 = !DILocation(line: 2590, column: 43, scope: !1825)
!1828 = !DILocation(line: 2590, column: 37, scope: !1825)
!1829 = !DILocation(line: 2590, column: 2, scope: !1830)
!1830 = !DILexicalBlockFile(scope: !457, file: !1, discriminator: 4)
!1831 = !DILocation(line: 2591, column: 4, scope: !1832)
!1832 = distinct !DILexicalBlock(scope: !457, file: !1, line: 2590, column: 53)
!1833 = !DILocation(line: 2592, column: 11, scope: !1832)
!1834 = !DILocation(line: 2590, column: 2, scope: !1835)
!1835 = !DILexicalBlockFile(scope: !457, file: !1, discriminator: 5)
!1836 = !DILocation(line: 2595, column: 7, scope: !457)
!1837 = !DILocation(line: 2596, column: 6, scope: !1838)
!1838 = distinct !DILexicalBlock(scope: !457, file: !1, line: 2596, column: 6)
!1839 = !DILocation(line: 2596, column: 15, scope: !1838)
!1840 = !DILocation(line: 2596, column: 20, scope: !1838)
!1841 = !DILocation(line: 2596, column: 24, scope: !1842)
!1842 = !DILexicalBlockFile(scope: !1838, file: !1, discriminator: 1)
!1843 = !DILocation(line: 2596, column: 23, scope: !1842)
!1844 = !DILocation(line: 2596, column: 26, scope: !1842)
!1845 = !DILocation(line: 2596, column: 6, scope: !1842)
!1846 = !DILocation(line: 2597, column: 8, scope: !1847)
!1847 = distinct !DILexicalBlock(scope: !1838, file: !1, line: 2596, column: 34)
!1848 = !DILocation(line: 2598, column: 4, scope: !1847)
!1849 = !DILocation(line: 2599, column: 11, scope: !1847)
!1850 = !DILocation(line: 2601, column: 10, scope: !1847)
!1851 = !DILocation(line: 2602, column: 25, scope: !1847)
!1852 = !DILocation(line: 2602, column: 23, scope: !1847)
!1853 = !DILocation(line: 2602, column: 11, scope: !1847)
!1854 = !DILocation(line: 2602, column: 9, scope: !1847)
!1855 = !DILocation(line: 2603, column: 34, scope: !1847)
!1856 = !DILocation(line: 2603, column: 32, scope: !1847)
!1857 = !DILocation(line: 2603, column: 20, scope: !1847)
!1858 = !DILocation(line: 2604, column: 2, scope: !1847)
!1859 = !DILocation(line: 2606, column: 4, scope: !457)
!1860 = !DILocation(line: 2607, column: 6, scope: !1861)
!1861 = distinct !DILexicalBlock(scope: !457, file: !1, line: 2607, column: 6)
!1862 = !DILocation(line: 2607, column: 15, scope: !1861)
!1863 = !DILocation(line: 2607, column: 6, scope: !457)
!1864 = !DILocation(line: 2608, column: 12, scope: !1865)
!1865 = distinct !DILexicalBlock(scope: !1861, file: !1, line: 2607, column: 21)
!1866 = !DILocation(line: 2608, column: 11, scope: !1865)
!1867 = !DILocation(line: 2608, column: 14, scope: !1865)
!1868 = !DILocation(line: 2608, column: 9, scope: !1865)
!1869 = !DILocation(line: 2609, column: 3, scope: !1865)
!1870 = !DILocation(line: 2609, column: 10, scope: !1871)
!1871 = !DILexicalBlockFile(scope: !1865, file: !1, discriminator: 1)
!1872 = !DILocation(line: 2609, column: 16, scope: !1871)
!1873 = !DILocation(line: 2609, column: 21, scope: !1871)
!1874 = !DILocation(line: 2609, column: 24, scope: !1875)
!1875 = !DILexicalBlockFile(scope: !1865, file: !1, discriminator: 2)
!1876 = !DILocation(line: 2609, column: 32, scope: !1875)
!1877 = !DILocation(line: 2609, column: 30, scope: !1875)
!1878 = !DILocation(line: 2609, column: 38, scope: !1875)
!1879 = !DILocation(line: 2609, column: 41, scope: !1880)
!1880 = !DILexicalBlockFile(scope: !1865, file: !1, discriminator: 3)
!1881 = !DILocation(line: 2609, column: 50, scope: !1880)
!1882 = !DILocation(line: 2609, column: 3, scope: !1883)
!1883 = !DILexicalBlockFile(scope: !1865, file: !1, discriminator: 4)
!1884 = !DILocation(line: 2610, column: 8, scope: !1885)
!1885 = distinct !DILexicalBlock(scope: !1886, file: !1, line: 2610, column: 8)
!1886 = distinct !DILexicalBlock(scope: !1865, file: !1, line: 2609, column: 56)
!1887 = !DILocation(line: 2610, column: 10, scope: !1885)
!1888 = !DILocation(line: 2610, column: 9, scope: !1885)
!1889 = !DILocation(line: 2610, column: 16, scope: !1885)
!1890 = !DILocation(line: 2610, column: 20, scope: !1891)
!1891 = !DILexicalBlockFile(scope: !1885, file: !1, discriminator: 1)
!1892 = !DILocation(line: 2610, column: 25, scope: !1891)
!1893 = !DILocation(line: 2610, column: 22, scope: !1891)
!1894 = !DILocation(line: 2610, column: 31, scope: !1891)
!1895 = !DILocation(line: 2610, column: 34, scope: !1896)
!1896 = !DILexicalBlockFile(scope: !1885, file: !1, discriminator: 2)
!1897 = !DILocation(line: 2610, column: 42, scope: !1896)
!1898 = !DILocation(line: 2610, column: 40, scope: !1896)
!1899 = !DILocation(line: 2610, column: 8, scope: !1896)
!1900 = !DILocation(line: 2611, column: 12, scope: !1901)
!1901 = distinct !DILexicalBlock(scope: !1885, file: !1, line: 2610, column: 61)
!1902 = !DILocation(line: 2611, column: 5, scope: !1901)
!1903 = !DILocation(line: 2613, column: 9, scope: !1886)
!1904 = !DILocation(line: 2613, column: 13, scope: !1886)
!1905 = !DILocation(line: 2613, column: 11, scope: !1886)
!1906 = !DILocation(line: 2613, column: 21, scope: !1886)
!1907 = !DILocation(line: 2613, column: 19, scope: !1886)
!1908 = !DILocation(line: 2613, column: 6, scope: !1886)
!1909 = !DILocation(line: 2614, column: 13, scope: !1886)
!1910 = !DILocation(line: 2614, column: 12, scope: !1886)
!1911 = !DILocation(line: 2614, column: 17, scope: !1886)
!1912 = !DILocation(line: 2614, column: 10, scope: !1886)
!1913 = !DILocation(line: 2615, column: 12, scope: !1886)
!1914 = !DILocation(line: 2609, column: 3, scope: !1915)
!1915 = !DILexicalBlockFile(scope: !1865, file: !1, discriminator: 5)
!1916 = !DILocation(line: 2617, column: 2, scope: !1865)
!1917 = !DILocation(line: 2618, column: 10, scope: !457)
!1918 = !DILocation(line: 2618, column: 15, scope: !457)
!1919 = !DILocation(line: 2618, column: 9, scope: !457)
!1920 = !DILocation(line: 2618, column: 23, scope: !1816)
!1921 = !DILocation(line: 2618, column: 22, scope: !1816)
!1922 = !DILocation(line: 2618, column: 9, scope: !1816)
!1923 = !DILocation(line: 2618, column: 27, scope: !1820)
!1924 = !DILocation(line: 2618, column: 9, scope: !1820)
!1925 = !DILocation(line: 2618, column: 9, scope: !1825)
!1926 = !DILocation(line: 2618, column: 2, scope: !1825)
!1927 = !DILocation(line: 2619, column: 1, scope: !457)
!1928 = !DILocalVariable(name: "a", arg: 1, scope: !465, file: !1, line: 691, type: !4)
!1929 = !DILocation(line: 691, column: 38, scope: !465)
!1930 = !DILocalVariable(name: "tar", arg: 2, scope: !465, file: !1, line: 691, type: !291)
!1931 = !DILocation(line: 691, column: 53, scope: !465)
!1932 = !DILocalVariable(name: "entry", arg: 3, scope: !465, file: !1, line: 692, type: !30)
!1933 = !DILocation(line: 692, column: 27, scope: !465)
!1934 = !DILocalVariable(name: "unconsumed", arg: 4, scope: !465, file: !1, line: 692, type: !65)
!1935 = !DILocation(line: 692, column: 42, scope: !465)
!1936 = !DILocalVariable(name: "bytes", scope: !465, file: !1, line: 694, type: !38)
!1937 = !DILocation(line: 694, column: 10, scope: !465)
!1938 = !DILocalVariable(name: "err", scope: !465, file: !1, line: 695, type: !23)
!1939 = !DILocation(line: 695, column: 6, scope: !465)
!1940 = !DILocalVariable(name: "h", scope: !465, file: !1, line: 696, type: !80)
!1941 = !DILocation(line: 696, column: 14, scope: !465)
!1942 = !DILocalVariable(name: "header", scope: !465, file: !1, line: 697, type: !336)
!1943 = !DILocation(line: 697, column: 43, scope: !465)
!1944 = !DILocalVariable(name: "gnuheader", scope: !465, file: !1, line: 698, type: !386)
!1945 = !DILocation(line: 698, column: 44, scope: !465)
!1946 = !DILocation(line: 701, column: 2, scope: !465)
!1947 = !DILocation(line: 702, column: 24, scope: !1948)
!1948 = distinct !DILexicalBlock(scope: !1949, file: !1, line: 701, column: 11)
!1949 = distinct !DILexicalBlock(scope: !1950, file: !1, line: 701, column: 2)
!1950 = distinct !DILexicalBlock(scope: !465, file: !1, line: 701, column: 2)
!1951 = !DILocation(line: 702, column: 27, scope: !1948)
!1952 = !DILocation(line: 702, column: 3, scope: !1948)
!1953 = !DILocation(line: 705, column: 28, scope: !1948)
!1954 = !DILocation(line: 705, column: 7, scope: !1948)
!1955 = !DILocation(line: 705, column: 5, scope: !1948)
!1956 = !DILocation(line: 706, column: 7, scope: !1957)
!1957 = distinct !DILexicalBlock(scope: !1948, file: !1, line: 706, column: 7)
!1958 = !DILocation(line: 706, column: 13, scope: !1957)
!1959 = !DILocation(line: 706, column: 7, scope: !1948)
!1960 = !DILocation(line: 707, column: 17, scope: !1957)
!1961 = !DILocation(line: 707, column: 12, scope: !1957)
!1962 = !DILocation(line: 707, column: 4, scope: !1957)
!1963 = !DILocation(line: 708, column: 7, scope: !1964)
!1964 = distinct !DILexicalBlock(scope: !1948, file: !1, line: 708, column: 7)
!1965 = !DILocation(line: 708, column: 13, scope: !1964)
!1966 = !DILocation(line: 708, column: 7, scope: !1948)
!1967 = !DILocation(line: 710, column: 4, scope: !1968)
!1968 = distinct !DILexicalBlock(scope: !1964, file: !1, line: 708, column: 19)
!1969 = !DILocation(line: 712, column: 7, scope: !1970)
!1970 = distinct !DILexicalBlock(scope: !1948, file: !1, line: 712, column: 7)
!1971 = !DILocation(line: 712, column: 13, scope: !1970)
!1972 = !DILocation(line: 712, column: 7, scope: !1948)
!1973 = !DILocation(line: 713, column: 23, scope: !1974)
!1974 = distinct !DILexicalBlock(scope: !1970, file: !1, line: 712, column: 20)
!1975 = !DILocation(line: 713, column: 26, scope: !1974)
!1976 = !DILocation(line: 713, column: 4, scope: !1974)
!1977 = !DILocation(line: 716, column: 4, scope: !1974)
!1978 = !DILocation(line: 718, column: 4, scope: !1948)
!1979 = !DILocation(line: 718, column: 15, scope: !1948)
!1980 = !DILocation(line: 721, column: 7, scope: !1981)
!1981 = distinct !DILexicalBlock(scope: !1948, file: !1, line: 721, column: 7)
!1982 = !DILocation(line: 721, column: 12, scope: !1981)
!1983 = !DILocation(line: 721, column: 17, scope: !1981)
!1984 = !DILocation(line: 721, column: 43, scope: !1985)
!1985 = !DILexicalBlockFile(scope: !1981, file: !1, discriminator: 1)
!1986 = !DILocation(line: 721, column: 21, scope: !1985)
!1987 = !DILocation(line: 721, column: 7, scope: !1985)
!1988 = !DILocation(line: 722, column: 4, scope: !1981)
!1989 = !DILocation(line: 725, column: 7, scope: !1990)
!1990 = distinct !DILexicalBlock(scope: !1948, file: !1, line: 725, column: 7)
!1991 = !DILocation(line: 725, column: 10, scope: !1990)
!1992 = !DILocation(line: 725, column: 18, scope: !1990)
!1993 = !DILocation(line: 725, column: 38, scope: !1990)
!1994 = !DILocation(line: 725, column: 7, scope: !1948)
!1995 = !DILocation(line: 726, column: 4, scope: !1996)
!1996 = distinct !DILexicalBlock(scope: !1990, file: !1, line: 725, column: 47)
!1997 = !DILocation(line: 726, column: 7, scope: !1996)
!1998 = !DILocation(line: 726, column: 15, scope: !1996)
!1999 = !DILocation(line: 726, column: 30, scope: !1996)
!2000 = !DILocation(line: 727, column: 4, scope: !1996)
!2001 = !DILocation(line: 727, column: 7, scope: !1996)
!2002 = !DILocation(line: 727, column: 15, scope: !1996)
!2003 = !DILocation(line: 727, column: 35, scope: !1996)
!2004 = !DILocation(line: 728, column: 3, scope: !1996)
!2005 = !DILocation(line: 730, column: 8, scope: !2006)
!2006 = distinct !DILexicalBlock(scope: !1948, file: !1, line: 730, column: 7)
!2007 = !DILocation(line: 730, column: 13, scope: !2006)
!2008 = !DILocation(line: 730, column: 7, scope: !1948)
!2009 = !DILocation(line: 732, column: 25, scope: !2010)
!2010 = distinct !DILexicalBlock(scope: !2006, file: !1, line: 730, column: 41)
!2011 = !DILocation(line: 732, column: 28, scope: !2010)
!2012 = !DILocation(line: 732, column: 4, scope: !2010)
!2013 = !DILocation(line: 733, column: 29, scope: !2010)
!2014 = !DILocation(line: 733, column: 8, scope: !2010)
!2015 = !DILocation(line: 733, column: 6, scope: !2010)
!2016 = !DILocation(line: 734, column: 8, scope: !2017)
!2017 = distinct !DILexicalBlock(scope: !2010, file: !1, line: 734, column: 8)
!2018 = !DILocation(line: 734, column: 10, scope: !2017)
!2019 = !DILocation(line: 734, column: 18, scope: !2017)
!2020 = !DILocation(line: 734, column: 21, scope: !2021)
!2021 = !DILexicalBlockFile(scope: !2017, file: !1, discriminator: 1)
!2022 = !DILocation(line: 734, column: 26, scope: !2021)
!2023 = !DILocation(line: 734, column: 31, scope: !2021)
!2024 = !DILocation(line: 734, column: 56, scope: !2025)
!2025 = !DILexicalBlockFile(scope: !2017, file: !1, discriminator: 2)
!2026 = !DILocation(line: 734, column: 34, scope: !2025)
!2027 = !DILocation(line: 734, column: 8, scope: !2025)
!2028 = !DILocation(line: 735, column: 28, scope: !2017)
!2029 = !DILocation(line: 735, column: 5, scope: !2017)
!2030 = !DILocation(line: 736, column: 25, scope: !2010)
!2031 = !DILocation(line: 736, column: 28, scope: !2010)
!2032 = !DILocation(line: 736, column: 4, scope: !2010)
!2033 = !DILocation(line: 737, column: 4, scope: !2010)
!2034 = !DILocation(line: 701, column: 2, scope: !2035)
!2035 = !DILexicalBlockFile(scope: !1949, file: !1, discriminator: 1)
!2036 = !DILocation(line: 753, column: 16, scope: !2037)
!2037 = distinct !DILexicalBlock(scope: !465, file: !1, line: 753, column: 6)
!2038 = !DILocation(line: 753, column: 19, scope: !2037)
!2039 = !DILocation(line: 753, column: 7, scope: !2037)
!2040 = !DILocation(line: 753, column: 6, scope: !465)
!2041 = !DILocation(line: 754, column: 24, scope: !2042)
!2042 = distinct !DILexicalBlock(scope: !2037, file: !1, line: 753, column: 23)
!2043 = !DILocation(line: 754, column: 27, scope: !2042)
!2044 = !DILocation(line: 754, column: 3, scope: !2042)
!2045 = !DILocation(line: 755, column: 22, scope: !2042)
!2046 = !DILocation(line: 755, column: 25, scope: !2042)
!2047 = !DILocation(line: 755, column: 3, scope: !2042)
!2048 = !DILocation(line: 756, column: 3, scope: !2042)
!2049 = !DILocation(line: 759, column: 8, scope: !2050)
!2050 = distinct !DILexicalBlock(scope: !465, file: !1, line: 759, column: 6)
!2051 = !DILocation(line: 759, column: 13, scope: !2050)
!2052 = !DILocation(line: 759, column: 6, scope: !2050)
!2053 = !DILocation(line: 759, column: 36, scope: !2050)
!2054 = !DILocation(line: 759, column: 6, scope: !465)
!2055 = !DILocation(line: 760, column: 24, scope: !2056)
!2056 = distinct !DILexicalBlock(scope: !2050, file: !1, line: 759, column: 42)
!2057 = !DILocation(line: 760, column: 27, scope: !2056)
!2058 = !DILocation(line: 760, column: 3, scope: !2056)
!2059 = !DILocation(line: 761, column: 22, scope: !2056)
!2060 = !DILocation(line: 761, column: 25, scope: !2056)
!2061 = !DILocation(line: 761, column: 3, scope: !2056)
!2062 = !DILocation(line: 762, column: 3, scope: !2056)
!2063 = !DILocation(line: 766, column: 54, scope: !465)
!2064 = !DILocation(line: 766, column: 11, scope: !465)
!2065 = !DILocation(line: 766, column: 9, scope: !465)
!2066 = !DILocation(line: 768, column: 9, scope: !465)
!2067 = !DILocation(line: 768, column: 17, scope: !465)
!2068 = !DILocation(line: 768, column: 2, scope: !465)
!2069 = !DILocation(line: 770, column: 3, scope: !2070)
!2070 = distinct !DILexicalBlock(scope: !465, file: !1, line: 768, column: 30)
!2071 = !DILocation(line: 770, column: 6, scope: !2070)
!2072 = !DILocation(line: 770, column: 14, scope: !2070)
!2073 = !DILocation(line: 770, column: 29, scope: !2070)
!2074 = !DILocation(line: 771, column: 3, scope: !2070)
!2075 = !DILocation(line: 771, column: 6, scope: !2070)
!2076 = !DILocation(line: 771, column: 14, scope: !2070)
!2077 = !DILocation(line: 771, column: 34, scope: !2070)
!2078 = !DILocation(line: 772, column: 28, scope: !2070)
!2079 = !DILocation(line: 772, column: 31, scope: !2070)
!2080 = !DILocation(line: 772, column: 36, scope: !2070)
!2081 = !DILocation(line: 772, column: 43, scope: !2070)
!2082 = !DILocation(line: 772, column: 46, scope: !2070)
!2083 = !DILocation(line: 772, column: 9, scope: !2070)
!2084 = !DILocation(line: 772, column: 7, scope: !2070)
!2085 = !DILocation(line: 773, column: 3, scope: !2070)
!2086 = !DILocation(line: 775, column: 3, scope: !2070)
!2087 = !DILocation(line: 775, column: 6, scope: !2070)
!2088 = !DILocation(line: 775, column: 14, scope: !2070)
!2089 = !DILocation(line: 775, column: 29, scope: !2070)
!2090 = !DILocation(line: 776, column: 3, scope: !2070)
!2091 = !DILocation(line: 776, column: 6, scope: !2070)
!2092 = !DILocation(line: 776, column: 14, scope: !2070)
!2093 = !DILocation(line: 776, column: 34, scope: !2070)
!2094 = !DILocation(line: 777, column: 27, scope: !2070)
!2095 = !DILocation(line: 777, column: 30, scope: !2070)
!2096 = !DILocation(line: 777, column: 35, scope: !2070)
!2097 = !DILocation(line: 777, column: 42, scope: !2070)
!2098 = !DILocation(line: 777, column: 45, scope: !2070)
!2099 = !DILocation(line: 777, column: 9, scope: !2070)
!2100 = !DILocation(line: 777, column: 7, scope: !2070)
!2101 = !DILocation(line: 778, column: 7, scope: !2102)
!2102 = distinct !DILexicalBlock(scope: !2070, file: !1, line: 778, column: 7)
!2103 = !DILocation(line: 778, column: 11, scope: !2102)
!2104 = !DILocation(line: 778, column: 7, scope: !2070)
!2105 = !DILocation(line: 779, column: 12, scope: !2102)
!2106 = !DILocation(line: 779, column: 4, scope: !2102)
!2107 = !DILocation(line: 780, column: 3, scope: !2070)
!2108 = !DILocation(line: 782, column: 25, scope: !2070)
!2109 = !DILocation(line: 782, column: 28, scope: !2070)
!2110 = !DILocation(line: 782, column: 33, scope: !2070)
!2111 = !DILocation(line: 782, column: 40, scope: !2070)
!2112 = !DILocation(line: 782, column: 43, scope: !2070)
!2113 = !DILocation(line: 782, column: 9, scope: !2070)
!2114 = !DILocation(line: 782, column: 7, scope: !2070)
!2115 = !DILocation(line: 783, column: 3, scope: !2070)
!2116 = !DILocation(line: 785, column: 25, scope: !2070)
!2117 = !DILocation(line: 785, column: 28, scope: !2070)
!2118 = !DILocation(line: 785, column: 33, scope: !2070)
!2119 = !DILocation(line: 785, column: 40, scope: !2070)
!2120 = !DILocation(line: 785, column: 43, scope: !2070)
!2121 = !DILocation(line: 785, column: 9, scope: !2070)
!2122 = !DILocation(line: 785, column: 7, scope: !2070)
!2123 = !DILocation(line: 786, column: 3, scope: !2070)
!2124 = !DILocation(line: 788, column: 23, scope: !2070)
!2125 = !DILocation(line: 788, column: 26, scope: !2070)
!2126 = !DILocation(line: 788, column: 31, scope: !2070)
!2127 = !DILocation(line: 788, column: 38, scope: !2070)
!2128 = !DILocation(line: 788, column: 41, scope: !2070)
!2129 = !DILocation(line: 788, column: 9, scope: !2070)
!2130 = !DILocation(line: 788, column: 7, scope: !2070)
!2131 = !DILocation(line: 789, column: 3, scope: !2070)
!2132 = !DILocation(line: 791, column: 3, scope: !2070)
!2133 = !DILocation(line: 791, column: 6, scope: !2070)
!2134 = !DILocation(line: 791, column: 14, scope: !2070)
!2135 = !DILocation(line: 791, column: 29, scope: !2070)
!2136 = !DILocation(line: 792, column: 3, scope: !2070)
!2137 = !DILocation(line: 792, column: 6, scope: !2070)
!2138 = !DILocation(line: 792, column: 14, scope: !2070)
!2139 = !DILocation(line: 792, column: 34, scope: !2070)
!2140 = !DILocation(line: 794, column: 31, scope: !2070)
!2141 = !DILocation(line: 794, column: 34, scope: !2070)
!2142 = !DILocation(line: 794, column: 39, scope: !2070)
!2143 = !DILocation(line: 794, column: 46, scope: !2070)
!2144 = !DILocation(line: 794, column: 49, scope: !2070)
!2145 = !DILocation(line: 794, column: 9, scope: !2070)
!2146 = !DILocation(line: 794, column: 7, scope: !2070)
!2147 = !DILocation(line: 795, column: 3, scope: !2070)
!2148 = !DILocation(line: 797, column: 3, scope: !2070)
!2149 = !DILocation(line: 797, column: 6, scope: !2070)
!2150 = !DILocation(line: 797, column: 14, scope: !2070)
!2151 = !DILocation(line: 797, column: 29, scope: !2070)
!2152 = !DILocation(line: 798, column: 3, scope: !2070)
!2153 = !DILocation(line: 798, column: 6, scope: !2070)
!2154 = !DILocation(line: 798, column: 14, scope: !2070)
!2155 = !DILocation(line: 798, column: 34, scope: !2070)
!2156 = !DILocation(line: 799, column: 31, scope: !2070)
!2157 = !DILocation(line: 799, column: 34, scope: !2070)
!2158 = !DILocation(line: 799, column: 39, scope: !2070)
!2159 = !DILocation(line: 799, column: 46, scope: !2070)
!2160 = !DILocation(line: 799, column: 49, scope: !2070)
!2161 = !DILocation(line: 799, column: 9, scope: !2070)
!2162 = !DILocation(line: 799, column: 7, scope: !2070)
!2163 = !DILocation(line: 800, column: 3, scope: !2070)
!2164 = !DILocation(line: 802, column: 59, scope: !2070)
!2165 = !DILocation(line: 802, column: 15, scope: !2070)
!2166 = !DILocation(line: 802, column: 13, scope: !2070)
!2167 = !DILocation(line: 803, column: 14, scope: !2168)
!2168 = distinct !DILexicalBlock(scope: !2070, file: !1, line: 803, column: 7)
!2169 = !DILocation(line: 803, column: 25, scope: !2168)
!2170 = !DILocation(line: 803, column: 7, scope: !2168)
!2171 = !DILocation(line: 803, column: 48, scope: !2168)
!2172 = !DILocation(line: 803, column: 7, scope: !2070)
!2173 = !DILocation(line: 804, column: 4, scope: !2174)
!2174 = distinct !DILexicalBlock(scope: !2168, file: !1, line: 803, column: 54)
!2175 = !DILocation(line: 804, column: 7, scope: !2174)
!2176 = !DILocation(line: 804, column: 15, scope: !2174)
!2177 = !DILocation(line: 804, column: 30, scope: !2174)
!2178 = !DILocation(line: 805, column: 4, scope: !2174)
!2179 = !DILocation(line: 805, column: 7, scope: !2174)
!2180 = !DILocation(line: 805, column: 15, scope: !2174)
!2181 = !DILocation(line: 805, column: 35, scope: !2174)
!2182 = !DILocation(line: 806, column: 24, scope: !2174)
!2183 = !DILocation(line: 806, column: 27, scope: !2174)
!2184 = !DILocation(line: 806, column: 32, scope: !2174)
!2185 = !DILocation(line: 806, column: 39, scope: !2174)
!2186 = !DILocation(line: 806, column: 42, scope: !2174)
!2187 = !DILocation(line: 806, column: 10, scope: !2174)
!2188 = !DILocation(line: 806, column: 8, scope: !2174)
!2189 = !DILocation(line: 807, column: 3, scope: !2174)
!2190 = !DILocation(line: 807, column: 21, scope: !2191)
!2191 = !DILexicalBlockFile(scope: !2192, file: !1, discriminator: 1)
!2192 = distinct !DILexicalBlock(scope: !2168, file: !1, line: 807, column: 14)
!2193 = !DILocation(line: 807, column: 29, scope: !2191)
!2194 = !DILocation(line: 807, column: 14, scope: !2191)
!2195 = !DILocation(line: 807, column: 48, scope: !2191)
!2196 = !DILocation(line: 808, column: 8, scope: !2197)
!2197 = distinct !DILexicalBlock(scope: !2198, file: !1, line: 808, column: 8)
!2198 = distinct !DILexicalBlock(scope: !2192, file: !1, line: 807, column: 54)
!2199 = !DILocation(line: 808, column: 11, scope: !2197)
!2200 = !DILocation(line: 808, column: 19, scope: !2197)
!2201 = !DILocation(line: 808, column: 34, scope: !2197)
!2202 = !DILocation(line: 808, column: 8, scope: !2198)
!2203 = !DILocation(line: 809, column: 5, scope: !2204)
!2204 = distinct !DILexicalBlock(scope: !2197, file: !1, line: 808, column: 73)
!2205 = !DILocation(line: 809, column: 8, scope: !2204)
!2206 = !DILocation(line: 809, column: 16, scope: !2204)
!2207 = !DILocation(line: 809, column: 31, scope: !2204)
!2208 = !DILocation(line: 810, column: 5, scope: !2204)
!2209 = !DILocation(line: 810, column: 8, scope: !2204)
!2210 = !DILocation(line: 810, column: 16, scope: !2204)
!2211 = !DILocation(line: 810, column: 36, scope: !2204)
!2212 = !DILocation(line: 811, column: 4, scope: !2204)
!2213 = !DILocation(line: 812, column: 23, scope: !2198)
!2214 = !DILocation(line: 812, column: 26, scope: !2198)
!2215 = !DILocation(line: 812, column: 31, scope: !2198)
!2216 = !DILocation(line: 812, column: 38, scope: !2198)
!2217 = !DILocation(line: 812, column: 10, scope: !2198)
!2218 = !DILocation(line: 812, column: 8, scope: !2198)
!2219 = !DILocation(line: 813, column: 3, scope: !2198)
!2220 = !DILocation(line: 814, column: 4, scope: !2221)
!2221 = distinct !DILexicalBlock(scope: !2192, file: !1, line: 813, column: 10)
!2222 = !DILocation(line: 814, column: 7, scope: !2221)
!2223 = !DILocation(line: 814, column: 15, scope: !2221)
!2224 = !DILocation(line: 814, column: 30, scope: !2221)
!2225 = !DILocation(line: 815, column: 4, scope: !2221)
!2226 = !DILocation(line: 815, column: 7, scope: !2221)
!2227 = !DILocation(line: 815, column: 15, scope: !2221)
!2228 = !DILocation(line: 815, column: 35, scope: !2221)
!2229 = !DILocation(line: 816, column: 25, scope: !2221)
!2230 = !DILocation(line: 816, column: 28, scope: !2221)
!2231 = !DILocation(line: 816, column: 33, scope: !2221)
!2232 = !DILocation(line: 816, column: 40, scope: !2221)
!2233 = !DILocation(line: 816, column: 10, scope: !2221)
!2234 = !DILocation(line: 816, column: 8, scope: !2221)
!2235 = !DILocation(line: 818, column: 2, scope: !2070)
!2236 = !DILocation(line: 819, column: 6, scope: !2237)
!2237 = distinct !DILexicalBlock(scope: !465, file: !1, line: 819, column: 6)
!2238 = !DILocation(line: 819, column: 10, scope: !2237)
!2239 = !DILocation(line: 819, column: 6, scope: !465)
!2240 = !DILocation(line: 820, column: 11, scope: !2237)
!2241 = !DILocation(line: 820, column: 3, scope: !2237)
!2242 = !DILocation(line: 822, column: 23, scope: !465)
!2243 = !DILocation(line: 822, column: 26, scope: !465)
!2244 = !DILocation(line: 822, column: 2, scope: !465)
!2245 = !DILocation(line: 824, column: 4, scope: !465)
!2246 = !DILocation(line: 825, column: 9, scope: !465)
!2247 = !DILocation(line: 827, column: 4, scope: !465)
!2248 = !DILocation(line: 827, column: 9, scope: !465)
!2249 = !DILocation(line: 827, column: 2, scope: !465)
!2250 = !DILocation(line: 832, column: 7, scope: !2251)
!2251 = distinct !DILexicalBlock(scope: !465, file: !1, line: 832, column: 6)
!2252 = !DILocation(line: 832, column: 11, scope: !2251)
!2253 = !DILocation(line: 832, column: 27, scope: !2251)
!2254 = !DILocation(line: 832, column: 30, scope: !2255)
!2255 = !DILexicalBlockFile(scope: !2251, file: !1, discriminator: 1)
!2256 = !DILocation(line: 832, column: 34, scope: !2255)
!2257 = !DILocation(line: 832, column: 49, scope: !2255)
!2258 = !DILocation(line: 833, column: 6, scope: !2251)
!2259 = !DILocation(line: 833, column: 11, scope: !2251)
!2260 = !DILocation(line: 833, column: 34, scope: !2251)
!2261 = !DILocation(line: 833, column: 39, scope: !2251)
!2262 = !DILocation(line: 834, column: 6, scope: !2251)
!2263 = !DILocation(line: 834, column: 11, scope: !2251)
!2264 = !DILocation(line: 832, column: 6, scope: !2265)
!2265 = !DILexicalBlockFile(scope: !465, file: !1, discriminator: 2)
!2266 = !DILocalVariable(name: "err2", scope: !2267, file: !1, line: 835, type: !23)
!2267 = distinct !DILexicalBlock(scope: !2251, file: !1, line: 834, column: 35)
!2268 = !DILocation(line: 835, column: 7, scope: !2267)
!2269 = !DILocation(line: 835, column: 37, scope: !2267)
!2270 = !DILocation(line: 835, column: 40, scope: !2267)
!2271 = !DILocation(line: 835, column: 45, scope: !2267)
!2272 = !DILocation(line: 835, column: 52, scope: !2267)
!2273 = !DILocation(line: 835, column: 55, scope: !2267)
!2274 = !DILocation(line: 835, column: 14, scope: !2267)
!2275 = !DILocation(line: 836, column: 7, scope: !2276)
!2276 = distinct !DILexicalBlock(scope: !2267, file: !1, line: 836, column: 7)
!2277 = !DILocation(line: 836, column: 14, scope: !2276)
!2278 = !DILocation(line: 836, column: 12, scope: !2276)
!2279 = !DILocation(line: 836, column: 7, scope: !2267)
!2280 = !DILocation(line: 837, column: 10, scope: !2276)
!2281 = !DILocation(line: 837, column: 8, scope: !2276)
!2282 = !DILocation(line: 837, column: 4, scope: !2276)
!2283 = !DILocation(line: 838, column: 2, scope: !2267)
!2284 = !DILocation(line: 841, column: 6, scope: !2285)
!2285 = distinct !DILexicalBlock(scope: !465, file: !1, line: 841, column: 6)
!2286 = !DILocation(line: 841, column: 10, scope: !2285)
!2287 = !DILocation(line: 841, column: 26, scope: !2285)
!2288 = !DILocation(line: 841, column: 29, scope: !2289)
!2289 = !DILexicalBlockFile(scope: !2285, file: !1, discriminator: 1)
!2290 = !DILocation(line: 841, column: 33, scope: !2289)
!2291 = !DILocation(line: 841, column: 6, scope: !2289)
!2292 = !DILocation(line: 842, column: 7, scope: !2293)
!2293 = distinct !DILexicalBlock(scope: !2294, file: !1, line: 842, column: 7)
!2294 = distinct !DILexicalBlock(scope: !2285, file: !1, line: 841, column: 48)
!2295 = !DILocation(line: 842, column: 12, scope: !2293)
!2296 = !DILocation(line: 842, column: 7, scope: !2294)
!2297 = !DILocation(line: 843, column: 8, scope: !2298)
!2298 = distinct !DILexicalBlock(scope: !2299, file: !1, line: 843, column: 8)
!2299 = distinct !DILexicalBlock(scope: !2293, file: !1, line: 842, column: 32)
!2300 = !DILocation(line: 843, column: 13, scope: !2298)
!2301 = !DILocation(line: 843, column: 30, scope: !2298)
!2302 = !DILocation(line: 843, column: 35, scope: !2298)
!2303 = !DILocation(line: 844, column: 8, scope: !2298)
!2304 = !DILocation(line: 844, column: 13, scope: !2298)
!2305 = !DILocation(line: 844, column: 30, scope: !2298)
!2306 = !DILocation(line: 843, column: 8, scope: !2307)
!2307 = !DILexicalBlockFile(scope: !2299, file: !1, discriminator: 1)
!2308 = !DILocalVariable(name: "bytes_read", scope: !2309, file: !1, line: 845, type: !38)
!2309 = distinct !DILexicalBlock(scope: !2298, file: !1, line: 844, column: 36)
!2310 = !DILocation(line: 845, column: 13, scope: !2309)
!2311 = !DILocation(line: 847, column: 5, scope: !2309)
!2312 = !DILocation(line: 847, column: 10, scope: !2309)
!2313 = !DILocation(line: 847, column: 29, scope: !2309)
!2314 = !DILocation(line: 849, column: 37, scope: !2309)
!2315 = !DILocation(line: 849, column: 40, scope: !2309)
!2316 = !DILocation(line: 849, column: 45, scope: !2309)
!2317 = !DILocation(line: 849, column: 18, scope: !2309)
!2318 = !DILocation(line: 849, column: 16, scope: !2309)
!2319 = !DILocation(line: 850, column: 9, scope: !2320)
!2320 = distinct !DILexicalBlock(scope: !2309, file: !1, line: 850, column: 9)
!2321 = !DILocation(line: 850, column: 20, scope: !2320)
!2322 = !DILocation(line: 850, column: 9, scope: !2309)
!2323 = !DILocation(line: 851, column: 19, scope: !2320)
!2324 = !DILocation(line: 851, column: 14, scope: !2320)
!2325 = !DILocation(line: 851, column: 6, scope: !2320)
!2326 = !DILocation(line: 852, column: 35, scope: !2309)
!2327 = !DILocation(line: 852, column: 5, scope: !2309)
!2328 = !DILocation(line: 852, column: 10, scope: !2309)
!2329 = !DILocation(line: 852, column: 32, scope: !2309)
!2330 = !DILocation(line: 853, column: 4, scope: !2309)
!2331 = !DILocation(line: 854, column: 24, scope: !2332)
!2332 = distinct !DILexicalBlock(scope: !2298, file: !1, line: 853, column: 11)
!2333 = !DILocation(line: 854, column: 27, scope: !2332)
!2334 = !DILocation(line: 854, column: 5, scope: !2332)
!2335 = !DILocation(line: 857, column: 5, scope: !2332)
!2336 = !DILocation(line: 859, column: 4, scope: !2299)
!2337 = !DILocation(line: 859, column: 9, scope: !2299)
!2338 = !DILocation(line: 859, column: 28, scope: !2299)
!2339 = !DILocation(line: 860, column: 3, scope: !2299)
!2340 = !DILocation(line: 861, column: 11, scope: !2294)
!2341 = !DILocation(line: 861, column: 3, scope: !2294)
!2342 = !DILocation(line: 863, column: 6, scope: !2343)
!2343 = distinct !DILexicalBlock(scope: !465, file: !1, line: 863, column: 6)
!2344 = !DILocation(line: 863, column: 10, scope: !2343)
!2345 = !DILocation(line: 863, column: 6, scope: !465)
!2346 = !DILocation(line: 865, column: 22, scope: !2343)
!2347 = !DILocation(line: 865, column: 25, scope: !2343)
!2348 = !DILocation(line: 865, column: 3, scope: !2343)
!2349 = !DILocation(line: 866, column: 2, scope: !465)
!2350 = !DILocation(line: 867, column: 1, scope: !465)
!2351 = !DILocalVariable(name: "a", arg: 1, scope: !540, file: !1, line: 469, type: !4)
!2352 = !DILocation(line: 469, column: 43, scope: !540)
!2353 = !DILocalVariable(name: "unconsumed", arg: 2, scope: !540, file: !1, line: 469, type: !65)
!2354 = !DILocation(line: 469, column: 54, scope: !540)
!2355 = !DILocation(line: 471, column: 7, scope: !2356)
!2356 = distinct !DILexicalBlock(scope: !540, file: !1, line: 471, column: 6)
!2357 = !DILocation(line: 471, column: 6, scope: !2356)
!2358 = !DILocation(line: 471, column: 6, scope: !540)
!2359 = !DILocation(line: 481, column: 26, scope: !2360)
!2360 = distinct !DILexicalBlock(scope: !2356, file: !1, line: 471, column: 19)
!2361 = !DILocation(line: 481, column: 30, scope: !2360)
!2362 = !DILocation(line: 481, column: 29, scope: !2360)
!2363 = !DILocation(line: 481, column: 3, scope: !2360)
!2364 = !DILocation(line: 482, column: 4, scope: !2360)
!2365 = !DILocation(line: 482, column: 15, scope: !2360)
!2366 = !DILocation(line: 483, column: 2, scope: !2360)
!2367 = !DILocation(line: 484, column: 1, scope: !540)
!2368 = !DILocalVariable(name: "a", arg: 1, scope: !543, file: !1, line: 2225, type: !4)
!2369 = !DILocation(line: 2225, column: 43, scope: !543)
!2370 = !DILocalVariable(name: "tar", arg: 2, scope: !543, file: !1, line: 2225, type: !291)
!2371 = !DILocation(line: 2225, column: 58, scope: !543)
!2372 = !DILocalVariable(name: "offset", arg: 3, scope: !543, file: !1, line: 2226, type: !52)
!2373 = !DILocation(line: 2226, column: 13, scope: !543)
!2374 = !DILocalVariable(name: "remaining", arg: 4, scope: !543, file: !1, line: 2226, type: !52)
!2375 = !DILocation(line: 2226, column: 29, scope: !543)
!2376 = !DILocalVariable(name: "p", scope: !543, file: !1, line: 2228, type: !314)
!2377 = !DILocation(line: 2228, column: 23, scope: !543)
!2378 = !DILocation(line: 2230, column: 29, scope: !543)
!2379 = !DILocation(line: 2230, column: 6, scope: !543)
!2380 = !DILocation(line: 2230, column: 4, scope: !543)
!2381 = !DILocation(line: 2231, column: 6, scope: !2382)
!2382 = distinct !DILexicalBlock(scope: !543, file: !1, line: 2231, column: 6)
!2383 = !DILocation(line: 2231, column: 8, scope: !2382)
!2384 = !DILocation(line: 2231, column: 6, scope: !543)
!2385 = !DILocation(line: 2232, column: 22, scope: !2386)
!2386 = distinct !DILexicalBlock(scope: !2382, file: !1, line: 2231, column: 17)
!2387 = !DILocation(line: 2232, column: 25, scope: !2386)
!2388 = !DILocation(line: 2232, column: 3, scope: !2386)
!2389 = !DILocation(line: 2233, column: 3, scope: !2386)
!2390 = !DILocation(line: 2235, column: 6, scope: !2391)
!2391 = distinct !DILexicalBlock(scope: !543, file: !1, line: 2235, column: 6)
!2392 = !DILocation(line: 2235, column: 11, scope: !2391)
!2393 = !DILocation(line: 2235, column: 23, scope: !2391)
!2394 = !DILocation(line: 2235, column: 6, scope: !543)
!2395 = !DILocation(line: 2236, column: 28, scope: !2391)
!2396 = !DILocation(line: 2236, column: 3, scope: !2391)
!2397 = !DILocation(line: 2236, column: 8, scope: !2391)
!2398 = !DILocation(line: 2236, column: 21, scope: !2391)
!2399 = !DILocation(line: 2236, column: 26, scope: !2391)
!2400 = !DILocation(line: 2238, column: 22, scope: !2391)
!2401 = !DILocation(line: 2238, column: 3, scope: !2391)
!2402 = !DILocation(line: 2238, column: 8, scope: !2391)
!2403 = !DILocation(line: 2238, column: 20, scope: !2391)
!2404 = !DILocation(line: 2239, column: 21, scope: !543)
!2405 = !DILocation(line: 2239, column: 2, scope: !543)
!2406 = !DILocation(line: 2239, column: 7, scope: !543)
!2407 = !DILocation(line: 2239, column: 19, scope: !543)
!2408 = !DILocation(line: 2240, column: 6, scope: !2409)
!2409 = distinct !DILexicalBlock(scope: !543, file: !1, line: 2240, column: 6)
!2410 = !DILocation(line: 2240, column: 16, scope: !2409)
!2411 = !DILocation(line: 2240, column: 20, scope: !2409)
!2412 = !DILocation(line: 2240, column: 23, scope: !2413)
!2413 = !DILexicalBlockFile(scope: !2409, file: !1, discriminator: 1)
!2414 = !DILocation(line: 2240, column: 30, scope: !2413)
!2415 = !DILocation(line: 2240, column: 6, scope: !2413)
!2416 = !DILocation(line: 2241, column: 22, scope: !2417)
!2417 = distinct !DILexicalBlock(scope: !2409, file: !1, line: 2240, column: 35)
!2418 = !DILocation(line: 2241, column: 25, scope: !2417)
!2419 = !DILocation(line: 2241, column: 3, scope: !2417)
!2420 = !DILocation(line: 2242, column: 3, scope: !2417)
!2421 = !DILocation(line: 2244, column: 14, scope: !543)
!2422 = !DILocation(line: 2244, column: 2, scope: !543)
!2423 = !DILocation(line: 2244, column: 5, scope: !543)
!2424 = !DILocation(line: 2244, column: 12, scope: !543)
!2425 = !DILocation(line: 2245, column: 17, scope: !543)
!2426 = !DILocation(line: 2245, column: 2, scope: !543)
!2427 = !DILocation(line: 2245, column: 5, scope: !543)
!2428 = !DILocation(line: 2245, column: 15, scope: !543)
!2429 = !DILocation(line: 2246, column: 2, scope: !543)
!2430 = !DILocation(line: 2247, column: 1, scope: !543)
!2431 = !DILocalVariable(name: "a", arg: 1, scope: !468, file: !1, line: 942, type: !4)
!2432 = !DILocation(line: 942, column: 41, scope: !468)
!2433 = !DILocalVariable(name: "tar", arg: 2, scope: !468, file: !1, line: 942, type: !291)
!2434 = !DILocation(line: 942, column: 56, scope: !468)
!2435 = !DILocalVariable(name: "entry", arg: 3, scope: !468, file: !1, line: 943, type: !30)
!2436 = !DILocation(line: 943, column: 27, scope: !468)
!2437 = !DILocalVariable(name: "h", arg: 4, scope: !468, file: !1, line: 943, type: !43)
!2438 = !DILocation(line: 943, column: 46, scope: !468)
!2439 = !DILocalVariable(name: "unconsumed", arg: 5, scope: !468, file: !1, line: 943, type: !65)
!2440 = !DILocation(line: 943, column: 57, scope: !468)
!2441 = !DILocalVariable(name: "header", scope: !468, file: !1, line: 945, type: !336)
!2442 = !DILocation(line: 945, column: 43, scope: !468)
!2443 = !DILocalVariable(name: "size", scope: !468, file: !1, line: 946, type: !45)
!2444 = !DILocation(line: 946, column: 9, scope: !468)
!2445 = !DILocalVariable(name: "err", scope: !468, file: !1, line: 947, type: !23)
!2446 = !DILocation(line: 947, column: 6, scope: !468)
!2447 = !DILocalVariable(name: "acl_type", scope: !468, file: !1, line: 947, type: !23)
!2448 = !DILocation(line: 947, column: 11, scope: !468)
!2449 = !DILocalVariable(name: "type", scope: !468, file: !1, line: 948, type: !52)
!2450 = !DILocation(line: 948, column: 10, scope: !468)
!2451 = !DILocalVariable(name: "acl", scope: !468, file: !1, line: 949, type: !95)
!2452 = !DILocation(line: 949, column: 8, scope: !468)
!2453 = !DILocalVariable(name: "p", scope: !468, file: !1, line: 949, type: !95)
!2454 = !DILocation(line: 949, column: 14, scope: !468)
!2455 = !DILocation(line: 955, column: 54, scope: !468)
!2456 = !DILocation(line: 955, column: 11, scope: !468)
!2457 = !DILocation(line: 955, column: 9, scope: !468)
!2458 = !DILocation(line: 956, column: 26, scope: !468)
!2459 = !DILocation(line: 956, column: 34, scope: !468)
!2460 = !DILocation(line: 956, column: 17, scope: !468)
!2461 = !DILocation(line: 956, column: 7, scope: !468)
!2462 = !DILocation(line: 957, column: 28, scope: !468)
!2463 = !DILocation(line: 957, column: 31, scope: !468)
!2464 = !DILocation(line: 957, column: 38, scope: !468)
!2465 = !DILocation(line: 957, column: 43, scope: !468)
!2466 = !DILocation(line: 957, column: 54, scope: !468)
!2467 = !DILocation(line: 957, column: 57, scope: !468)
!2468 = !DILocation(line: 957, column: 8, scope: !468)
!2469 = !DILocation(line: 957, column: 6, scope: !468)
!2470 = !DILocation(line: 958, column: 6, scope: !2471)
!2471 = distinct !DILexicalBlock(scope: !468, file: !1, line: 958, column: 6)
!2472 = !DILocation(line: 958, column: 10, scope: !2471)
!2473 = !DILocation(line: 958, column: 6, scope: !468)
!2474 = !DILocation(line: 959, column: 11, scope: !2471)
!2475 = !DILocation(line: 959, column: 3, scope: !2471)
!2476 = !DILocation(line: 962, column: 24, scope: !468)
!2477 = !DILocation(line: 962, column: 27, scope: !468)
!2478 = !DILocation(line: 962, column: 32, scope: !468)
!2479 = !DILocation(line: 962, column: 39, scope: !468)
!2480 = !DILocation(line: 962, column: 8, scope: !468)
!2481 = !DILocation(line: 962, column: 6, scope: !468)
!2482 = !DILocation(line: 963, column: 7, scope: !2483)
!2483 = distinct !DILexicalBlock(scope: !468, file: !1, line: 963, column: 6)
!2484 = !DILocation(line: 963, column: 11, scope: !2483)
!2485 = !DILocation(line: 963, column: 26, scope: !2483)
!2486 = !DILocation(line: 963, column: 30, scope: !2487)
!2487 = !DILexicalBlockFile(scope: !2483, file: !1, discriminator: 1)
!2488 = !DILocation(line: 963, column: 34, scope: !2487)
!2489 = !DILocation(line: 963, column: 6, scope: !2487)
!2490 = !DILocation(line: 964, column: 11, scope: !2483)
!2491 = !DILocation(line: 964, column: 3, scope: !2483)
!2492 = !DILocation(line: 972, column: 12, scope: !468)
!2493 = !DILocation(line: 972, column: 17, scope: !468)
!2494 = !DILocation(line: 972, column: 26, scope: !468)
!2495 = !DILocation(line: 972, column: 10, scope: !468)
!2496 = !DILocation(line: 972, column: 4, scope: !468)
!2497 = !DILocation(line: 973, column: 7, scope: !468)
!2498 = !DILocation(line: 974, column: 2, scope: !468)
!2499 = !DILocation(line: 974, column: 10, scope: !2500)
!2500 = !DILexicalBlockFile(scope: !468, file: !1, discriminator: 1)
!2501 = !DILocation(line: 974, column: 9, scope: !2500)
!2502 = !DILocation(line: 974, column: 12, scope: !2500)
!2503 = !DILocation(line: 974, column: 20, scope: !2500)
!2504 = !DILocation(line: 974, column: 23, scope: !2505)
!2505 = !DILexicalBlockFile(scope: !468, file: !1, discriminator: 2)
!2506 = !DILocation(line: 974, column: 27, scope: !2505)
!2507 = !DILocation(line: 974, column: 33, scope: !2505)
!2508 = !DILocation(line: 974, column: 31, scope: !2505)
!2509 = !DILocation(line: 974, column: 25, scope: !2505)
!2510 = !DILocation(line: 974, column: 2, scope: !2511)
!2511 = !DILexicalBlockFile(scope: !468, file: !1, discriminator: 3)
!2512 = !DILocation(line: 975, column: 8, scope: !2513)
!2513 = distinct !DILexicalBlock(scope: !2514, file: !1, line: 975, column: 7)
!2514 = distinct !DILexicalBlock(scope: !468, file: !1, line: 974, column: 39)
!2515 = !DILocation(line: 975, column: 7, scope: !2513)
!2516 = !DILocation(line: 975, column: 10, scope: !2513)
!2517 = !DILocation(line: 975, column: 16, scope: !2513)
!2518 = !DILocation(line: 975, column: 20, scope: !2519)
!2519 = !DILexicalBlockFile(scope: !2513, file: !1, discriminator: 1)
!2520 = !DILocation(line: 975, column: 19, scope: !2519)
!2521 = !DILocation(line: 975, column: 22, scope: !2519)
!2522 = !DILocation(line: 975, column: 7, scope: !2519)
!2523 = !DILocation(line: 976, column: 23, scope: !2524)
!2524 = distinct !DILexicalBlock(scope: !2513, file: !1, line: 975, column: 29)
!2525 = !DILocation(line: 976, column: 26, scope: !2524)
!2526 = !DILocation(line: 976, column: 4, scope: !2524)
!2527 = !DILocation(line: 978, column: 4, scope: !2524)
!2528 = !DILocation(line: 980, column: 8, scope: !2514)
!2529 = !DILocation(line: 981, column: 12, scope: !2514)
!2530 = !DILocation(line: 981, column: 11, scope: !2514)
!2531 = !DILocation(line: 981, column: 14, scope: !2514)
!2532 = !DILocation(line: 981, column: 8, scope: !2514)
!2533 = !DILocation(line: 982, column: 7, scope: !2534)
!2534 = distinct !DILexicalBlock(scope: !2514, file: !1, line: 982, column: 7)
!2535 = !DILocation(line: 982, column: 12, scope: !2534)
!2536 = !DILocation(line: 982, column: 7, scope: !2514)
!2537 = !DILocation(line: 983, column: 23, scope: !2538)
!2538 = distinct !DILexicalBlock(scope: !2534, file: !1, line: 982, column: 25)
!2539 = !DILocation(line: 983, column: 26, scope: !2538)
!2540 = !DILocation(line: 983, column: 4, scope: !2538)
!2541 = !DILocation(line: 985, column: 4, scope: !2538)
!2542 = !DILocation(line: 987, column: 4, scope: !2514)
!2543 = !DILocation(line: 974, column: 2, scope: !2544)
!2544 = !DILexicalBlockFile(scope: !468, file: !1, discriminator: 4)
!2545 = !DILocation(line: 989, column: 15, scope: !468)
!2546 = !DILocation(line: 989, column: 10, scope: !468)
!2547 = !DILocation(line: 989, column: 20, scope: !468)
!2548 = !DILocation(line: 989, column: 2, scope: !468)
!2549 = !DILocation(line: 992, column: 12, scope: !2550)
!2550 = distinct !DILexicalBlock(scope: !468, file: !1, line: 989, column: 32)
!2551 = !DILocation(line: 993, column: 3, scope: !2550)
!2552 = !DILocation(line: 996, column: 12, scope: !2550)
!2553 = !DILocation(line: 997, column: 3, scope: !2550)
!2554 = !DILocation(line: 999, column: 22, scope: !2550)
!2555 = !DILocation(line: 999, column: 25, scope: !2550)
!2556 = !DILocation(line: 1001, column: 12, scope: !2550)
!2557 = !DILocation(line: 1001, column: 7, scope: !2550)
!2558 = !DILocation(line: 999, column: 3, scope: !2550)
!2559 = !DILocation(line: 1002, column: 3, scope: !2550)
!2560 = !DILocation(line: 1004, column: 3, scope: !468)
!2561 = !DILocation(line: 1006, column: 6, scope: !2562)
!2562 = distinct !DILexicalBlock(scope: !468, file: !1, line: 1006, column: 6)
!2563 = !DILocation(line: 1006, column: 11, scope: !2562)
!2564 = !DILocation(line: 1006, column: 17, scope: !2562)
!2565 = !DILocation(line: 1006, column: 15, scope: !2562)
!2566 = !DILocation(line: 1006, column: 8, scope: !2562)
!2567 = !DILocation(line: 1006, column: 6, scope: !468)
!2568 = !DILocation(line: 1007, column: 22, scope: !2569)
!2569 = distinct !DILexicalBlock(scope: !2562, file: !1, line: 1006, column: 23)
!2570 = !DILocation(line: 1007, column: 25, scope: !2569)
!2571 = !DILocation(line: 1007, column: 3, scope: !2569)
!2572 = !DILocation(line: 1009, column: 3, scope: !2569)
!2573 = !DILocation(line: 1013, column: 11, scope: !468)
!2574 = !DILocation(line: 1013, column: 15, scope: !468)
!2575 = !DILocation(line: 1013, column: 13, scope: !468)
!2576 = !DILocation(line: 1013, column: 7, scope: !468)
!2577 = !DILocation(line: 1014, column: 8, scope: !468)
!2578 = !DILocation(line: 1014, column: 6, scope: !468)
!2579 = !DILocation(line: 1016, column: 2, scope: !468)
!2580 = !DILocation(line: 1016, column: 10, scope: !2500)
!2581 = !DILocation(line: 1016, column: 9, scope: !2500)
!2582 = !DILocation(line: 1016, column: 12, scope: !2500)
!2583 = !DILocation(line: 1016, column: 20, scope: !2500)
!2584 = !DILocation(line: 1016, column: 23, scope: !2505)
!2585 = !DILocation(line: 1016, column: 27, scope: !2505)
!2586 = !DILocation(line: 1016, column: 33, scope: !2505)
!2587 = !DILocation(line: 1016, column: 31, scope: !2505)
!2588 = !DILocation(line: 1016, column: 25, scope: !2505)
!2589 = !DILocation(line: 1016, column: 2, scope: !2511)
!2590 = !DILocation(line: 1017, column: 4, scope: !468)
!2591 = !DILocation(line: 1016, column: 2, scope: !2544)
!2592 = !DILocation(line: 1019, column: 6, scope: !2593)
!2593 = distinct !DILexicalBlock(scope: !468, file: !1, line: 1019, column: 6)
!2594 = !DILocation(line: 1019, column: 11, scope: !2593)
!2595 = !DILocation(line: 1019, column: 21, scope: !2593)
!2596 = !DILocation(line: 1019, column: 6, scope: !468)
!2597 = !DILocation(line: 1021, column: 9, scope: !2598)
!2598 = distinct !DILexicalBlock(scope: !2593, file: !1, line: 1019, column: 30)
!2599 = !DILocation(line: 1021, column: 12, scope: !2598)
!2600 = !DILocation(line: 1020, column: 20, scope: !2598)
!2601 = !DILocation(line: 1020, column: 3, scope: !2598)
!2602 = !DILocation(line: 1020, column: 8, scope: !2598)
!2603 = !DILocation(line: 1020, column: 18, scope: !2598)
!2604 = !DILocation(line: 1022, column: 7, scope: !2605)
!2605 = distinct !DILexicalBlock(scope: !2598, file: !1, line: 1022, column: 7)
!2606 = !DILocation(line: 1022, column: 12, scope: !2605)
!2607 = !DILocation(line: 1022, column: 22, scope: !2605)
!2608 = !DILocation(line: 1022, column: 7, scope: !2598)
!2609 = !DILocation(line: 1023, column: 4, scope: !2605)
!2610 = !DILocation(line: 1024, column: 2, scope: !2598)
!2611 = !DILocation(line: 1025, column: 2, scope: !468)
!2612 = !DILocation(line: 1026, column: 50, scope: !468)
!2613 = !DILocation(line: 1026, column: 32, scope: !468)
!2614 = !DILocation(line: 1027, column: 6, scope: !468)
!2615 = !DILocation(line: 1027, column: 11, scope: !468)
!2616 = !DILocation(line: 1027, column: 21, scope: !468)
!2617 = !DILocation(line: 1027, column: 24, scope: !468)
!2618 = !DILocation(line: 1027, column: 34, scope: !468)
!2619 = !DILocation(line: 1027, column: 39, scope: !468)
!2620 = !DILocation(line: 1026, column: 8, scope: !2500)
!2621 = !DILocation(line: 1026, column: 6, scope: !468)
!2622 = !DILocation(line: 1028, column: 6, scope: !2623)
!2623 = distinct !DILexicalBlock(scope: !468, file: !1, line: 1028, column: 6)
!2624 = !DILocation(line: 1028, column: 10, scope: !2623)
!2625 = !DILocation(line: 1028, column: 6, scope: !468)
!2626 = !DILocation(line: 1029, column: 7, scope: !2627)
!2627 = distinct !DILexicalBlock(scope: !2628, file: !1, line: 1029, column: 7)
!2628 = distinct !DILexicalBlock(scope: !2623, file: !1, line: 1028, column: 25)
!2629 = !DILocation(line: 1029, column: 13, scope: !2627)
!2630 = !DILocation(line: 1029, column: 7, scope: !2628)
!2631 = !DILocation(line: 1030, column: 23, scope: !2632)
!2632 = distinct !DILexicalBlock(scope: !2627, file: !1, line: 1029, column: 24)
!2633 = !DILocation(line: 1030, column: 26, scope: !2632)
!2634 = !DILocation(line: 1030, column: 4, scope: !2632)
!2635 = !DILocation(line: 1032, column: 3, scope: !2632)
!2636 = !DILocation(line: 1033, column: 23, scope: !2627)
!2637 = !DILocation(line: 1033, column: 26, scope: !2627)
!2638 = !DILocation(line: 1033, column: 4, scope: !2627)
!2639 = !DILocation(line: 1035, column: 2, scope: !2628)
!2640 = !DILocation(line: 1036, column: 10, scope: !468)
!2641 = !DILocation(line: 1036, column: 2, scope: !468)
!2642 = !DILocation(line: 1037, column: 1, scope: !468)
!2643 = !DILocalVariable(name: "a", arg: 1, scope: !475, file: !1, line: 1451, type: !4)
!2644 = !DILocation(line: 1451, column: 40, scope: !475)
!2645 = !DILocalVariable(name: "tar", arg: 2, scope: !475, file: !1, line: 1451, type: !291)
!2646 = !DILocation(line: 1451, column: 55, scope: !475)
!2647 = !DILocalVariable(name: "entry", arg: 3, scope: !475, file: !1, line: 1452, type: !30)
!2648 = !DILocation(line: 1452, column: 27, scope: !475)
!2649 = !DILocalVariable(name: "h", arg: 4, scope: !475, file: !1, line: 1452, type: !43)
!2650 = !DILocation(line: 1452, column: 46, scope: !475)
!2651 = !DILocalVariable(name: "unconsumed", arg: 5, scope: !475, file: !1, line: 1452, type: !65)
!2652 = !DILocation(line: 1452, column: 57, scope: !475)
!2653 = !DILocalVariable(name: "err", scope: !475, file: !1, line: 1454, type: !23)
!2654 = !DILocation(line: 1454, column: 6, scope: !475)
!2655 = !DILocation(line: 1456, column: 28, scope: !475)
!2656 = !DILocation(line: 1456, column: 31, scope: !475)
!2657 = !DILocation(line: 1456, column: 38, scope: !475)
!2658 = !DILocation(line: 1456, column: 43, scope: !475)
!2659 = !DILocation(line: 1456, column: 56, scope: !475)
!2660 = !DILocation(line: 1456, column: 59, scope: !475)
!2661 = !DILocation(line: 1456, column: 8, scope: !475)
!2662 = !DILocation(line: 1456, column: 6, scope: !475)
!2663 = !DILocation(line: 1457, column: 6, scope: !2664)
!2664 = distinct !DILexicalBlock(scope: !475, file: !1, line: 1457, column: 6)
!2665 = !DILocation(line: 1457, column: 10, scope: !2664)
!2666 = !DILocation(line: 1457, column: 6, scope: !475)
!2667 = !DILocation(line: 1458, column: 11, scope: !2664)
!2668 = !DILocation(line: 1458, column: 3, scope: !2664)
!2669 = !DILocation(line: 1459, column: 24, scope: !475)
!2670 = !DILocation(line: 1459, column: 27, scope: !475)
!2671 = !DILocation(line: 1459, column: 32, scope: !475)
!2672 = !DILocation(line: 1459, column: 39, scope: !475)
!2673 = !DILocation(line: 1459, column: 8, scope: !475)
!2674 = !DILocation(line: 1459, column: 6, scope: !475)
!2675 = !DILocation(line: 1460, column: 10, scope: !475)
!2676 = !DILocation(line: 1460, column: 2, scope: !475)
!2677 = !DILocation(line: 1461, column: 1, scope: !475)
!2678 = !DILocalVariable(name: "a", arg: 1, scope: !476, file: !1, line: 1043, type: !4)
!2679 = !DILocation(line: 1043, column: 38, scope: !476)
!2680 = !DILocalVariable(name: "tar", arg: 2, scope: !476, file: !1, line: 1043, type: !291)
!2681 = !DILocation(line: 1043, column: 53, scope: !476)
!2682 = !DILocalVariable(name: "entry", arg: 3, scope: !476, file: !1, line: 1044, type: !30)
!2683 = !DILocation(line: 1044, column: 27, scope: !476)
!2684 = !DILocalVariable(name: "h", arg: 4, scope: !476, file: !1, line: 1044, type: !43)
!2685 = !DILocation(line: 1044, column: 46, scope: !476)
!2686 = !DILocalVariable(name: "unconsumed", arg: 5, scope: !476, file: !1, line: 1044, type: !65)
!2687 = !DILocation(line: 1044, column: 57, scope: !476)
!2688 = !DILocalVariable(name: "err", scope: !476, file: !1, line: 1046, type: !23)
!2689 = !DILocation(line: 1046, column: 6, scope: !476)
!2690 = !DILocation(line: 1048, column: 28, scope: !476)
!2691 = !DILocation(line: 1048, column: 31, scope: !476)
!2692 = !DILocation(line: 1048, column: 38, scope: !476)
!2693 = !DILocation(line: 1048, column: 43, scope: !476)
!2694 = !DILocation(line: 1048, column: 54, scope: !476)
!2695 = !DILocation(line: 1048, column: 57, scope: !476)
!2696 = !DILocation(line: 1048, column: 8, scope: !476)
!2697 = !DILocation(line: 1048, column: 6, scope: !476)
!2698 = !DILocation(line: 1049, column: 6, scope: !2699)
!2699 = distinct !DILexicalBlock(scope: !476, file: !1, line: 1049, column: 6)
!2700 = !DILocation(line: 1049, column: 10, scope: !2699)
!2701 = !DILocation(line: 1049, column: 6, scope: !476)
!2702 = !DILocation(line: 1050, column: 11, scope: !2699)
!2703 = !DILocation(line: 1050, column: 3, scope: !2699)
!2704 = !DILocation(line: 1051, column: 24, scope: !476)
!2705 = !DILocation(line: 1051, column: 27, scope: !476)
!2706 = !DILocation(line: 1051, column: 32, scope: !476)
!2707 = !DILocation(line: 1051, column: 39, scope: !476)
!2708 = !DILocation(line: 1051, column: 8, scope: !476)
!2709 = !DILocation(line: 1051, column: 6, scope: !476)
!2710 = !DILocation(line: 1052, column: 7, scope: !2711)
!2711 = distinct !DILexicalBlock(scope: !476, file: !1, line: 1052, column: 6)
!2712 = !DILocation(line: 1052, column: 11, scope: !2711)
!2713 = !DILocation(line: 1052, column: 26, scope: !2711)
!2714 = !DILocation(line: 1052, column: 30, scope: !2715)
!2715 = !DILexicalBlockFile(scope: !2711, file: !1, discriminator: 1)
!2716 = !DILocation(line: 1052, column: 34, scope: !2715)
!2717 = !DILocation(line: 1052, column: 6, scope: !2715)
!2718 = !DILocation(line: 1053, column: 11, scope: !2711)
!2719 = !DILocation(line: 1053, column: 3, scope: !2711)
!2720 = !DILocation(line: 1055, column: 26, scope: !476)
!2721 = !DILocation(line: 1055, column: 33, scope: !476)
!2722 = !DILocation(line: 1055, column: 38, scope: !476)
!2723 = !DILocation(line: 1055, column: 47, scope: !476)
!2724 = !DILocation(line: 1055, column: 2, scope: !476)
!2725 = !DILocation(line: 1056, column: 2, scope: !476)
!2726 = !DILocation(line: 1057, column: 1, scope: !476)
!2727 = !DILocalVariable(name: "a", arg: 1, scope: !477, file: !1, line: 1078, type: !4)
!2728 = !DILocation(line: 1078, column: 38, scope: !477)
!2729 = !DILocalVariable(name: "tar", arg: 2, scope: !477, file: !1, line: 1078, type: !291)
!2730 = !DILocation(line: 1078, column: 53, scope: !477)
!2731 = !DILocalVariable(name: "entry", arg: 3, scope: !477, file: !1, line: 1079, type: !30)
!2732 = !DILocation(line: 1079, column: 27, scope: !477)
!2733 = !DILocalVariable(name: "h", arg: 4, scope: !477, file: !1, line: 1079, type: !43)
!2734 = !DILocation(line: 1079, column: 46, scope: !477)
!2735 = !DILocalVariable(name: "unconsumed", arg: 5, scope: !477, file: !1, line: 1079, type: !65)
!2736 = !DILocation(line: 1079, column: 57, scope: !477)
!2737 = !DILocalVariable(name: "err", scope: !477, file: !1, line: 1081, type: !23)
!2738 = !DILocation(line: 1081, column: 6, scope: !477)
!2739 = !DILocation(line: 1083, column: 28, scope: !477)
!2740 = !DILocation(line: 1083, column: 31, scope: !477)
!2741 = !DILocation(line: 1083, column: 38, scope: !477)
!2742 = !DILocation(line: 1083, column: 43, scope: !477)
!2743 = !DILocation(line: 1083, column: 54, scope: !477)
!2744 = !DILocation(line: 1083, column: 57, scope: !477)
!2745 = !DILocation(line: 1083, column: 8, scope: !477)
!2746 = !DILocation(line: 1083, column: 6, scope: !477)
!2747 = !DILocation(line: 1084, column: 6, scope: !2748)
!2748 = distinct !DILexicalBlock(scope: !477, file: !1, line: 1084, column: 6)
!2749 = !DILocation(line: 1084, column: 10, scope: !2748)
!2750 = !DILocation(line: 1084, column: 6, scope: !477)
!2751 = !DILocation(line: 1085, column: 11, scope: !2748)
!2752 = !DILocation(line: 1085, column: 3, scope: !2748)
!2753 = !DILocation(line: 1087, column: 24, scope: !477)
!2754 = !DILocation(line: 1087, column: 27, scope: !477)
!2755 = !DILocation(line: 1087, column: 32, scope: !477)
!2756 = !DILocation(line: 1087, column: 39, scope: !477)
!2757 = !DILocation(line: 1087, column: 8, scope: !477)
!2758 = !DILocation(line: 1087, column: 6, scope: !477)
!2759 = !DILocation(line: 1088, column: 7, scope: !2760)
!2760 = distinct !DILexicalBlock(scope: !477, file: !1, line: 1088, column: 6)
!2761 = !DILocation(line: 1088, column: 11, scope: !2760)
!2762 = !DILocation(line: 1088, column: 26, scope: !2760)
!2763 = !DILocation(line: 1088, column: 30, scope: !2764)
!2764 = !DILexicalBlockFile(scope: !2760, file: !1, discriminator: 1)
!2765 = !DILocation(line: 1088, column: 34, scope: !2764)
!2766 = !DILocation(line: 1088, column: 6, scope: !2764)
!2767 = !DILocation(line: 1089, column: 11, scope: !2760)
!2768 = !DILocation(line: 1089, column: 3, scope: !2760)
!2769 = !DILocation(line: 1090, column: 36, scope: !2770)
!2770 = distinct !DILexicalBlock(scope: !477, file: !1, line: 1090, column: 6)
!2771 = !DILocation(line: 1090, column: 43, scope: !2770)
!2772 = !DILocation(line: 1090, column: 48, scope: !2770)
!2773 = !DILocation(line: 1090, column: 57, scope: !2770)
!2774 = !DILocation(line: 1091, column: 6, scope: !2770)
!2775 = !DILocation(line: 1091, column: 40, scope: !2770)
!2776 = !DILocation(line: 1091, column: 45, scope: !2770)
!2777 = !DILocation(line: 1090, column: 6, scope: !2770)
!2778 = !DILocation(line: 1091, column: 52, scope: !2770)
!2779 = !DILocation(line: 1090, column: 6, scope: !477)
!2780 = !DILocation(line: 1092, column: 37, scope: !2770)
!2781 = !DILocation(line: 1092, column: 40, scope: !2770)
!2782 = !DILocation(line: 1092, column: 45, scope: !2770)
!2783 = !DILocation(line: 1092, column: 9, scope: !2770)
!2784 = !DILocation(line: 1092, column: 7, scope: !2770)
!2785 = !DILocation(line: 1092, column: 3, scope: !2770)
!2786 = !DILocation(line: 1093, column: 10, scope: !477)
!2787 = !DILocation(line: 1093, column: 2, scope: !477)
!2788 = !DILocation(line: 1094, column: 1, scope: !477)
!2789 = !DILocalVariable(name: "a", arg: 1, scope: !481, file: !1, line: 1101, type: !4)
!2790 = !DILocation(line: 1101, column: 36, scope: !481)
!2791 = !DILocalVariable(name: "tar", arg: 2, scope: !481, file: !1, line: 1101, type: !291)
!2792 = !DILocation(line: 1101, column: 51, scope: !481)
!2793 = !DILocalVariable(name: "entry", arg: 3, scope: !481, file: !1, line: 1102, type: !30)
!2794 = !DILocation(line: 1102, column: 27, scope: !481)
!2795 = !DILocalVariable(name: "h", arg: 4, scope: !481, file: !1, line: 1102, type: !43)
!2796 = !DILocation(line: 1102, column: 46, scope: !481)
!2797 = !DILocalVariable(name: "unconsumed", arg: 5, scope: !481, file: !1, line: 1102, type: !65)
!2798 = !DILocation(line: 1102, column: 57, scope: !481)
!2799 = !DILocation(line: 1104, column: 8, scope: !481)
!2800 = !DILocation(line: 1107, column: 26, scope: !481)
!2801 = !DILocation(line: 1107, column: 29, scope: !481)
!2802 = !DILocation(line: 1107, column: 34, scope: !481)
!2803 = !DILocation(line: 1107, column: 41, scope: !481)
!2804 = !DILocation(line: 1107, column: 10, scope: !481)
!2805 = !DILocation(line: 1107, column: 2, scope: !481)
!2806 = !DILocalVariable(name: "a", arg: 1, scope: !482, file: !1, line: 1464, type: !4)
!2807 = !DILocation(line: 1464, column: 44, scope: !482)
!2808 = !DILocalVariable(name: "tar", arg: 2, scope: !482, file: !1, line: 1464, type: !291)
!2809 = !DILocation(line: 1464, column: 59, scope: !482)
!2810 = !DILocalVariable(name: "entry", arg: 3, scope: !482, file: !1, line: 1465, type: !30)
!2811 = !DILocation(line: 1465, column: 27, scope: !482)
!2812 = !DILocalVariable(name: "h", arg: 4, scope: !482, file: !1, line: 1465, type: !43)
!2813 = !DILocation(line: 1465, column: 46, scope: !482)
!2814 = !DILocalVariable(name: "unconsumed", arg: 5, scope: !482, file: !1, line: 1465, type: !65)
!2815 = !DILocation(line: 1465, column: 57, scope: !482)
!2816 = !DILocalVariable(name: "err", scope: !482, file: !1, line: 1467, type: !23)
!2817 = !DILocation(line: 1467, column: 6, scope: !482)
!2818 = !DILocalVariable(name: "err2", scope: !482, file: !1, line: 1467, type: !23)
!2819 = !DILocation(line: 1467, column: 11, scope: !482)
!2820 = !DILocation(line: 1469, column: 28, scope: !482)
!2821 = !DILocation(line: 1469, column: 31, scope: !482)
!2822 = !DILocation(line: 1469, column: 38, scope: !482)
!2823 = !DILocation(line: 1469, column: 43, scope: !482)
!2824 = !DILocation(line: 1469, column: 56, scope: !482)
!2825 = !DILocation(line: 1469, column: 59, scope: !482)
!2826 = !DILocation(line: 1469, column: 8, scope: !482)
!2827 = !DILocation(line: 1469, column: 6, scope: !482)
!2828 = !DILocation(line: 1470, column: 6, scope: !2829)
!2829 = distinct !DILexicalBlock(scope: !482, file: !1, line: 1470, column: 6)
!2830 = !DILocation(line: 1470, column: 10, scope: !2829)
!2831 = !DILocation(line: 1470, column: 6, scope: !482)
!2832 = !DILocation(line: 1471, column: 11, scope: !2829)
!2833 = !DILocation(line: 1471, column: 3, scope: !2829)
!2834 = !DILocation(line: 1474, column: 24, scope: !482)
!2835 = !DILocation(line: 1474, column: 27, scope: !482)
!2836 = !DILocation(line: 1474, column: 32, scope: !482)
!2837 = !DILocation(line: 1474, column: 39, scope: !482)
!2838 = !DILocation(line: 1474, column: 8, scope: !482)
!2839 = !DILocation(line: 1474, column: 6, scope: !482)
!2840 = !DILocation(line: 1475, column: 7, scope: !2841)
!2841 = distinct !DILexicalBlock(scope: !482, file: !1, line: 1475, column: 6)
!2842 = !DILocation(line: 1475, column: 11, scope: !2841)
!2843 = !DILocation(line: 1475, column: 26, scope: !2841)
!2844 = !DILocation(line: 1475, column: 30, scope: !2845)
!2845 = !DILexicalBlockFile(scope: !2841, file: !1, discriminator: 1)
!2846 = !DILocation(line: 1475, column: 34, scope: !2845)
!2847 = !DILocation(line: 1475, column: 6, scope: !2845)
!2848 = !DILocation(line: 1476, column: 11, scope: !2841)
!2849 = !DILocation(line: 1476, column: 3, scope: !2841)
!2850 = !DILocation(line: 1488, column: 20, scope: !482)
!2851 = !DILocation(line: 1488, column: 23, scope: !482)
!2852 = !DILocation(line: 1488, column: 28, scope: !482)
!2853 = !DILocation(line: 1488, column: 36, scope: !482)
!2854 = !DILocation(line: 1488, column: 41, scope: !482)
!2855 = !DILocation(line: 1488, column: 9, scope: !482)
!2856 = !DILocation(line: 1488, column: 7, scope: !482)
!2857 = !DILocation(line: 1489, column: 9, scope: !482)
!2858 = !DILocation(line: 1489, column: 9, scope: !2859)
!2859 = !DILexicalBlockFile(scope: !482, file: !1, discriminator: 1)
!2860 = !DILocation(line: 1489, column: 9, scope: !2861)
!2861 = !DILexicalBlockFile(scope: !482, file: !1, discriminator: 2)
!2862 = !DILocation(line: 1489, column: 9, scope: !2863)
!2863 = !DILexicalBlockFile(scope: !482, file: !1, discriminator: 3)
!2864 = !DILocation(line: 1489, column: 6, scope: !2863)
!2865 = !DILocation(line: 1490, column: 33, scope: !482)
!2866 = !DILocation(line: 1490, column: 38, scope: !482)
!2867 = !DILocation(line: 1490, column: 32, scope: !482)
!2868 = !DILocation(line: 1490, column: 29, scope: !482)
!2869 = !DILocation(line: 1490, column: 2, scope: !482)
!2870 = !DILocation(line: 1490, column: 7, scope: !482)
!2871 = !DILocation(line: 1490, column: 21, scope: !482)
!2872 = !DILocation(line: 1491, column: 10, scope: !482)
!2873 = !DILocation(line: 1491, column: 2, scope: !482)
!2874 = !DILocation(line: 1492, column: 1, scope: !482)
!2875 = !DILocalVariable(name: "a", arg: 1, scope: !518, file: !1, line: 2141, type: !4)
!2876 = !DILocation(line: 2141, column: 36, scope: !518)
!2877 = !DILocalVariable(name: "tar", arg: 2, scope: !518, file: !1, line: 2141, type: !291)
!2878 = !DILocation(line: 2141, column: 51, scope: !518)
!2879 = !DILocalVariable(name: "entry", arg: 3, scope: !518, file: !1, line: 2142, type: !30)
!2880 = !DILocation(line: 2142, column: 27, scope: !518)
!2881 = !DILocalVariable(name: "h", arg: 4, scope: !518, file: !1, line: 2142, type: !43)
!2882 = !DILocation(line: 2142, column: 46, scope: !518)
!2883 = !DILocalVariable(name: "unconsumed", arg: 5, scope: !518, file: !1, line: 2142, type: !65)
!2884 = !DILocation(line: 2142, column: 57, scope: !518)
!2885 = !DILocalVariable(name: "header", scope: !518, file: !1, line: 2144, type: !386)
!2886 = !DILocation(line: 2144, column: 44, scope: !518)
!2887 = !DILocalVariable(name: "t", scope: !518, file: !1, line: 2145, type: !52)
!2888 = !DILocation(line: 2145, column: 10, scope: !518)
!2889 = !DILocalVariable(name: "err", scope: !518, file: !1, line: 2146, type: !23)
!2890 = !DILocation(line: 2146, column: 6, scope: !518)
!2891 = !DILocation(line: 2155, column: 22, scope: !518)
!2892 = !DILocation(line: 2155, column: 25, scope: !518)
!2893 = !DILocation(line: 2155, column: 30, scope: !518)
!2894 = !DILocation(line: 2155, column: 37, scope: !518)
!2895 = !DILocation(line: 2155, column: 8, scope: !518)
!2896 = !DILocation(line: 2155, column: 6, scope: !518)
!2897 = !DILocation(line: 2156, column: 6, scope: !2898)
!2898 = distinct !DILexicalBlock(scope: !518, file: !1, line: 2156, column: 6)
!2899 = !DILocation(line: 2156, column: 10, scope: !2898)
!2900 = !DILocation(line: 2156, column: 6, scope: !518)
!2901 = !DILocation(line: 2157, column: 11, scope: !2898)
!2902 = !DILocation(line: 2157, column: 3, scope: !2898)
!2903 = !DILocation(line: 2160, column: 55, scope: !518)
!2904 = !DILocation(line: 2160, column: 11, scope: !518)
!2905 = !DILocation(line: 2160, column: 9, scope: !518)
!2906 = !DILocation(line: 2161, column: 36, scope: !2907)
!2907 = distinct !DILexicalBlock(scope: !518, file: !1, line: 2161, column: 6)
!2908 = !DILocation(line: 2162, column: 6, scope: !2907)
!2909 = !DILocation(line: 2162, column: 14, scope: !2907)
!2910 = !DILocation(line: 2162, column: 42, scope: !2907)
!2911 = !DILocation(line: 2162, column: 47, scope: !2907)
!2912 = !DILocation(line: 2161, column: 6, scope: !2907)
!2913 = !DILocation(line: 2162, column: 54, scope: !2907)
!2914 = !DILocation(line: 2161, column: 6, scope: !518)
!2915 = !DILocation(line: 2163, column: 37, scope: !2916)
!2916 = distinct !DILexicalBlock(scope: !2907, file: !1, line: 2162, column: 60)
!2917 = !DILocation(line: 2163, column: 40, scope: !2916)
!2918 = !DILocation(line: 2163, column: 45, scope: !2916)
!2919 = !DILocation(line: 2163, column: 9, scope: !2916)
!2920 = !DILocation(line: 2163, column: 7, scope: !2916)
!2921 = !DILocation(line: 2164, column: 7, scope: !2922)
!2922 = distinct !DILexicalBlock(scope: !2916, file: !1, line: 2164, column: 7)
!2923 = !DILocation(line: 2164, column: 11, scope: !2922)
!2924 = !DILocation(line: 2164, column: 7, scope: !2916)
!2925 = !DILocation(line: 2165, column: 12, scope: !2922)
!2926 = !DILocation(line: 2165, column: 4, scope: !2922)
!2927 = !DILocation(line: 2166, column: 2, scope: !2916)
!2928 = !DILocation(line: 2172, column: 33, scope: !2929)
!2929 = distinct !DILexicalBlock(scope: !518, file: !1, line: 2172, column: 6)
!2930 = !DILocation(line: 2173, column: 6, scope: !2929)
!2931 = !DILocation(line: 2173, column: 14, scope: !2929)
!2932 = !DILocation(line: 2173, column: 44, scope: !2929)
!2933 = !DILocation(line: 2173, column: 49, scope: !2929)
!2934 = !DILocation(line: 2172, column: 6, scope: !2929)
!2935 = !DILocation(line: 2173, column: 56, scope: !2929)
!2936 = !DILocation(line: 2172, column: 6, scope: !518)
!2937 = !DILocation(line: 2174, column: 37, scope: !2938)
!2938 = distinct !DILexicalBlock(scope: !2929, file: !1, line: 2173, column: 62)
!2939 = !DILocation(line: 2174, column: 40, scope: !2938)
!2940 = !DILocation(line: 2174, column: 45, scope: !2938)
!2941 = !DILocation(line: 2174, column: 9, scope: !2938)
!2942 = !DILocation(line: 2174, column: 7, scope: !2938)
!2943 = !DILocation(line: 2175, column: 7, scope: !2944)
!2944 = distinct !DILexicalBlock(scope: !2938, file: !1, line: 2175, column: 7)
!2945 = !DILocation(line: 2175, column: 11, scope: !2944)
!2946 = !DILocation(line: 2175, column: 7, scope: !2938)
!2947 = !DILocation(line: 2176, column: 12, scope: !2944)
!2948 = !DILocation(line: 2176, column: 4, scope: !2944)
!2949 = !DILocation(line: 2177, column: 2, scope: !2938)
!2950 = !DILocation(line: 2179, column: 33, scope: !2951)
!2951 = distinct !DILexicalBlock(scope: !518, file: !1, line: 2179, column: 6)
!2952 = !DILocation(line: 2180, column: 6, scope: !2951)
!2953 = !DILocation(line: 2180, column: 14, scope: !2951)
!2954 = !DILocation(line: 2180, column: 44, scope: !2951)
!2955 = !DILocation(line: 2180, column: 49, scope: !2951)
!2956 = !DILocation(line: 2179, column: 6, scope: !2951)
!2957 = !DILocation(line: 2180, column: 56, scope: !2951)
!2958 = !DILocation(line: 2179, column: 6, scope: !518)
!2959 = !DILocation(line: 2181, column: 37, scope: !2960)
!2960 = distinct !DILexicalBlock(scope: !2951, file: !1, line: 2180, column: 62)
!2961 = !DILocation(line: 2181, column: 40, scope: !2960)
!2962 = !DILocation(line: 2181, column: 45, scope: !2960)
!2963 = !DILocation(line: 2181, column: 9, scope: !2960)
!2964 = !DILocation(line: 2181, column: 7, scope: !2960)
!2965 = !DILocation(line: 2182, column: 7, scope: !2966)
!2966 = distinct !DILexicalBlock(scope: !2960, file: !1, line: 2182, column: 7)
!2967 = !DILocation(line: 2182, column: 11, scope: !2966)
!2968 = !DILocation(line: 2182, column: 7, scope: !2960)
!2969 = !DILocation(line: 2183, column: 12, scope: !2966)
!2970 = !DILocation(line: 2183, column: 4, scope: !2966)
!2971 = !DILocation(line: 2184, column: 2, scope: !2960)
!2972 = !DILocation(line: 2187, column: 6, scope: !2973)
!2973 = distinct !DILexicalBlock(scope: !518, file: !1, line: 2187, column: 6)
!2974 = !DILocation(line: 2187, column: 14, scope: !2973)
!2975 = !DILocation(line: 2187, column: 26, scope: !2973)
!2976 = !DILocation(line: 2187, column: 33, scope: !2973)
!2977 = !DILocation(line: 2187, column: 36, scope: !2978)
!2978 = !DILexicalBlockFile(scope: !2973, file: !1, discriminator: 1)
!2979 = !DILocation(line: 2187, column: 44, scope: !2978)
!2980 = !DILocation(line: 2187, column: 56, scope: !2978)
!2981 = !DILocation(line: 2187, column: 6, scope: !2978)
!2982 = !DILocation(line: 2188, column: 31, scope: !2983)
!2983 = distinct !DILexicalBlock(scope: !2973, file: !1, line: 2187, column: 64)
!2984 = !DILocation(line: 2189, column: 16, scope: !2983)
!2985 = !DILocation(line: 2189, column: 24, scope: !2983)
!2986 = !DILocation(line: 2189, column: 7, scope: !2983)
!2987 = !DILocation(line: 2188, column: 3, scope: !2983)
!2988 = !DILocation(line: 2190, column: 31, scope: !2983)
!2989 = !DILocation(line: 2191, column: 16, scope: !2983)
!2990 = !DILocation(line: 2191, column: 24, scope: !2983)
!2991 = !DILocation(line: 2191, column: 7, scope: !2983)
!2992 = !DILocation(line: 2190, column: 3, scope: !2983)
!2993 = !DILocation(line: 2192, column: 2, scope: !2983)
!2994 = !DILocation(line: 2193, column: 26, scope: !2973)
!2995 = !DILocation(line: 2193, column: 3, scope: !2973)
!2996 = !DILocation(line: 2195, column: 33, scope: !518)
!2997 = !DILocation(line: 2195, column: 38, scope: !518)
!2998 = !DILocation(line: 2195, column: 32, scope: !518)
!2999 = !DILocation(line: 2195, column: 29, scope: !518)
!3000 = !DILocation(line: 2195, column: 2, scope: !518)
!3001 = !DILocation(line: 2195, column: 7, scope: !518)
!3002 = !DILocation(line: 2195, column: 21, scope: !518)
!3003 = !DILocation(line: 2198, column: 15, scope: !518)
!3004 = !DILocation(line: 2198, column: 23, scope: !518)
!3005 = !DILocation(line: 2198, column: 6, scope: !518)
!3006 = !DILocation(line: 2198, column: 4, scope: !518)
!3007 = !DILocation(line: 2199, column: 6, scope: !3008)
!3008 = distinct !DILexicalBlock(scope: !518, file: !1, line: 2199, column: 6)
!3009 = !DILocation(line: 2199, column: 8, scope: !3008)
!3010 = !DILocation(line: 2199, column: 6, scope: !518)
!3011 = !DILocation(line: 2200, column: 27, scope: !3008)
!3012 = !DILocation(line: 2200, column: 34, scope: !3008)
!3013 = !DILocation(line: 2200, column: 3, scope: !3008)
!3014 = !DILocation(line: 2201, column: 15, scope: !518)
!3015 = !DILocation(line: 2201, column: 23, scope: !518)
!3016 = !DILocation(line: 2201, column: 6, scope: !518)
!3017 = !DILocation(line: 2201, column: 4, scope: !518)
!3018 = !DILocation(line: 2202, column: 6, scope: !3019)
!3019 = distinct !DILexicalBlock(scope: !518, file: !1, line: 2202, column: 6)
!3020 = !DILocation(line: 2202, column: 8, scope: !3019)
!3021 = !DILocation(line: 2202, column: 6, scope: !518)
!3022 = !DILocation(line: 2203, column: 27, scope: !3019)
!3023 = !DILocation(line: 2203, column: 34, scope: !3019)
!3024 = !DILocation(line: 2203, column: 3, scope: !3019)
!3025 = !DILocation(line: 2205, column: 6, scope: !3026)
!3026 = distinct !DILexicalBlock(scope: !518, file: !1, line: 2205, column: 6)
!3027 = !DILocation(line: 2205, column: 14, scope: !3026)
!3028 = !DILocation(line: 2205, column: 26, scope: !3026)
!3029 = !DILocation(line: 2205, column: 6, scope: !518)
!3030 = !DILocation(line: 2207, column: 18, scope: !3031)
!3031 = distinct !DILexicalBlock(scope: !3026, file: !1, line: 2205, column: 32)
!3032 = !DILocation(line: 2207, column: 26, scope: !3031)
!3033 = !DILocation(line: 2207, column: 9, scope: !3031)
!3034 = !DILocation(line: 2206, column: 3, scope: !3031)
!3035 = !DILocation(line: 2206, column: 8, scope: !3031)
!3036 = !DILocation(line: 2207, column: 7, scope: !3031)
!3037 = !DILocation(line: 2208, column: 26, scope: !3031)
!3038 = !DILocation(line: 2208, column: 33, scope: !3031)
!3039 = !DILocation(line: 2208, column: 38, scope: !3031)
!3040 = !DILocation(line: 2208, column: 3, scope: !3031)
!3041 = !DILocation(line: 2209, column: 2, scope: !3031)
!3042 = !DILocation(line: 2211, column: 6, scope: !3043)
!3043 = distinct !DILexicalBlock(scope: !518, file: !1, line: 2211, column: 6)
!3044 = !DILocation(line: 2211, column: 14, scope: !3043)
!3045 = !DILocation(line: 2211, column: 24, scope: !3043)
!3046 = !DILocation(line: 2211, column: 34, scope: !3043)
!3047 = !DILocation(line: 2211, column: 6, scope: !518)
!3048 = !DILocation(line: 2212, column: 27, scope: !3049)
!3049 = distinct !DILexicalBlock(scope: !3050, file: !1, line: 2212, column: 7)
!3050 = distinct !DILexicalBlock(scope: !3043, file: !1, line: 2211, column: 40)
!3051 = !DILocation(line: 2212, column: 30, scope: !3049)
!3052 = !DILocation(line: 2212, column: 35, scope: !3049)
!3053 = !DILocation(line: 2212, column: 43, scope: !3049)
!3054 = !DILocation(line: 2212, column: 7, scope: !3049)
!3055 = !DILocation(line: 2213, column: 7, scope: !3049)
!3056 = !DILocation(line: 2212, column: 7, scope: !3050)
!3057 = !DILocation(line: 2214, column: 4, scope: !3049)
!3058 = !DILocation(line: 2215, column: 2, scope: !3050)
!3059 = !DILocation(line: 2216, column: 7, scope: !3060)
!3060 = distinct !DILexicalBlock(scope: !3061, file: !1, line: 2216, column: 7)
!3061 = distinct !DILexicalBlock(scope: !3043, file: !1, line: 2215, column: 9)
!3062 = !DILocation(line: 2216, column: 15, scope: !3060)
!3063 = !DILocation(line: 2216, column: 29, scope: !3060)
!3064 = !DILocation(line: 2216, column: 7, scope: !3061)
!3065 = !DILocation(line: 2218, column: 3, scope: !3066)
!3066 = distinct !DILexicalBlock(scope: !3060, file: !1, line: 2216, column: 35)
!3067 = !DILocation(line: 2221, column: 10, scope: !518)
!3068 = !DILocation(line: 2221, column: 2, scope: !518)
!3069 = !DILocation(line: 2222, column: 1, scope: !518)
!3070 = !DILocalVariable(name: "a", arg: 1, scope: !527, file: !1, line: 1500, type: !4)
!3071 = !DILocation(line: 1500, column: 35, scope: !527)
!3072 = !DILocalVariable(name: "tar", arg: 2, scope: !527, file: !1, line: 1500, type: !291)
!3073 = !DILocation(line: 1500, column: 50, scope: !527)
!3074 = !DILocalVariable(name: "entry", arg: 3, scope: !527, file: !1, line: 1501, type: !30)
!3075 = !DILocation(line: 1501, column: 27, scope: !527)
!3076 = !DILocalVariable(name: "h", arg: 4, scope: !527, file: !1, line: 1501, type: !43)
!3077 = !DILocation(line: 1501, column: 46, scope: !527)
!3078 = !DILocalVariable(name: "header", scope: !527, file: !1, line: 1503, type: !336)
!3079 = !DILocation(line: 1503, column: 43, scope: !527)
!3080 = !DILocalVariable(name: "as", scope: !527, file: !1, line: 1504, type: !474)
!3081 = !DILocation(line: 1504, column: 25, scope: !527)
!3082 = !DILocalVariable(name: "err", scope: !527, file: !1, line: 1505, type: !23)
!3083 = !DILocation(line: 1505, column: 6, scope: !527)
!3084 = !DILocalVariable(name: "r", scope: !527, file: !1, line: 1505, type: !23)
!3085 = !DILocation(line: 1505, column: 24, scope: !527)
!3086 = !DILocation(line: 1507, column: 54, scope: !527)
!3087 = !DILocation(line: 1507, column: 11, scope: !527)
!3088 = !DILocation(line: 1507, column: 9, scope: !527)
!3089 = !DILocation(line: 1510, column: 9, scope: !527)
!3090 = !DILocation(line: 1510, column: 14, scope: !527)
!3091 = !DILocation(line: 1510, column: 5, scope: !527)
!3092 = !DILocation(line: 1511, column: 6, scope: !3093)
!3093 = distinct !DILexicalBlock(scope: !527, file: !1, line: 1511, column: 6)
!3094 = !DILocation(line: 1511, column: 14, scope: !3093)
!3095 = !DILocation(line: 1511, column: 6, scope: !527)
!3096 = !DILocation(line: 1512, column: 3, scope: !3097)
!3097 = distinct !DILexicalBlock(scope: !3093, file: !1, line: 1511, column: 25)
!3098 = !DILocation(line: 1513, column: 13, scope: !3099)
!3099 = distinct !DILexicalBlock(scope: !3097, file: !1, line: 1513, column: 7)
!3100 = !DILocation(line: 1513, column: 32, scope: !3099)
!3101 = !DILocation(line: 1513, column: 7, scope: !3099)
!3102 = !DILocation(line: 1513, column: 11, scope: !3099)
!3103 = !DILocation(line: 1513, column: 37, scope: !3099)
!3104 = !DILocation(line: 1513, column: 7, scope: !3097)
!3105 = !DILocation(line: 1514, column: 27, scope: !3099)
!3106 = !DILocation(line: 1514, column: 4, scope: !3099)
!3107 = !DILocation(line: 1515, column: 19, scope: !3097)
!3108 = !DILocation(line: 1515, column: 23, scope: !3097)
!3109 = !DILocation(line: 1515, column: 31, scope: !3097)
!3110 = !DILocation(line: 1515, column: 3, scope: !3097)
!3111 = !DILocation(line: 1516, column: 2, scope: !3097)
!3112 = !DILocation(line: 1517, column: 3, scope: !3113)
!3113 = distinct !DILexicalBlock(scope: !3093, file: !1, line: 1516, column: 9)
!3114 = !DILocation(line: 1519, column: 36, scope: !3115)
!3115 = distinct !DILexicalBlock(scope: !527, file: !1, line: 1519, column: 6)
!3116 = !DILocation(line: 1519, column: 43, scope: !3115)
!3117 = !DILocation(line: 1519, column: 47, scope: !3115)
!3118 = !DILocation(line: 1519, column: 50, scope: !3115)
!3119 = !DILocation(line: 1520, column: 6, scope: !3115)
!3120 = !DILocation(line: 1520, column: 11, scope: !3115)
!3121 = !DILocation(line: 1519, column: 6, scope: !3115)
!3122 = !DILocation(line: 1520, column: 18, scope: !3115)
!3123 = !DILocation(line: 1519, column: 6, scope: !527)
!3124 = !DILocation(line: 1521, column: 37, scope: !3125)
!3125 = distinct !DILexicalBlock(scope: !3115, file: !1, line: 1520, column: 24)
!3126 = !DILocation(line: 1521, column: 40, scope: !3125)
!3127 = !DILocation(line: 1521, column: 45, scope: !3125)
!3128 = !DILocation(line: 1521, column: 9, scope: !3125)
!3129 = !DILocation(line: 1521, column: 7, scope: !3125)
!3130 = !DILocation(line: 1522, column: 7, scope: !3131)
!3131 = distinct !DILexicalBlock(scope: !3125, file: !1, line: 1522, column: 7)
!3132 = !DILocation(line: 1522, column: 11, scope: !3131)
!3133 = !DILocation(line: 1522, column: 7, scope: !3125)
!3134 = !DILocation(line: 1523, column: 12, scope: !3131)
!3135 = !DILocation(line: 1523, column: 4, scope: !3131)
!3136 = !DILocation(line: 1524, column: 2, scope: !3125)
!3137 = !DILocation(line: 1527, column: 20, scope: !527)
!3138 = !DILocation(line: 1527, column: 23, scope: !527)
!3139 = !DILocation(line: 1527, column: 28, scope: !527)
!3140 = !DILocation(line: 1527, column: 35, scope: !527)
!3141 = !DILocation(line: 1527, column: 6, scope: !527)
!3142 = !DILocation(line: 1527, column: 4, scope: !527)
!3143 = !DILocation(line: 1528, column: 6, scope: !3144)
!3144 = distinct !DILexicalBlock(scope: !527, file: !1, line: 1528, column: 6)
!3145 = !DILocation(line: 1528, column: 8, scope: !3144)
!3146 = !DILocation(line: 1528, column: 6, scope: !527)
!3147 = !DILocation(line: 1529, column: 11, scope: !3144)
!3148 = !DILocation(line: 1529, column: 3, scope: !3144)
!3149 = !DILocation(line: 1530, column: 6, scope: !3150)
!3150 = distinct !DILexicalBlock(scope: !527, file: !1, line: 1530, column: 6)
!3151 = !DILocation(line: 1530, column: 10, scope: !3150)
!3152 = !DILocation(line: 1530, column: 8, scope: !3150)
!3153 = !DILocation(line: 1530, column: 6, scope: !527)
!3154 = !DILocation(line: 1531, column: 9, scope: !3150)
!3155 = !DILocation(line: 1531, column: 7, scope: !3150)
!3156 = !DILocation(line: 1531, column: 3, scope: !3150)
!3157 = !DILocation(line: 1534, column: 33, scope: !3158)
!3158 = distinct !DILexicalBlock(scope: !527, file: !1, line: 1534, column: 6)
!3159 = !DILocation(line: 1535, column: 6, scope: !3158)
!3160 = !DILocation(line: 1535, column: 14, scope: !3158)
!3161 = !DILocation(line: 1535, column: 44, scope: !3158)
!3162 = !DILocation(line: 1535, column: 49, scope: !3158)
!3163 = !DILocation(line: 1534, column: 6, scope: !3158)
!3164 = !DILocation(line: 1535, column: 56, scope: !3158)
!3165 = !DILocation(line: 1534, column: 6, scope: !527)
!3166 = !DILocation(line: 1536, column: 37, scope: !3167)
!3167 = distinct !DILexicalBlock(scope: !3158, file: !1, line: 1535, column: 62)
!3168 = !DILocation(line: 1536, column: 40, scope: !3167)
!3169 = !DILocation(line: 1536, column: 45, scope: !3167)
!3170 = !DILocation(line: 1536, column: 9, scope: !3167)
!3171 = !DILocation(line: 1536, column: 7, scope: !3167)
!3172 = !DILocation(line: 1537, column: 7, scope: !3173)
!3173 = distinct !DILexicalBlock(scope: !3167, file: !1, line: 1537, column: 7)
!3174 = !DILocation(line: 1537, column: 11, scope: !3173)
!3175 = !DILocation(line: 1537, column: 7, scope: !3167)
!3176 = !DILocation(line: 1538, column: 12, scope: !3173)
!3177 = !DILocation(line: 1538, column: 4, scope: !3173)
!3178 = !DILocation(line: 1539, column: 2, scope: !3167)
!3179 = !DILocation(line: 1541, column: 33, scope: !3180)
!3180 = distinct !DILexicalBlock(scope: !527, file: !1, line: 1541, column: 6)
!3181 = !DILocation(line: 1542, column: 6, scope: !3180)
!3182 = !DILocation(line: 1542, column: 14, scope: !3180)
!3183 = !DILocation(line: 1542, column: 44, scope: !3180)
!3184 = !DILocation(line: 1542, column: 49, scope: !3180)
!3185 = !DILocation(line: 1541, column: 6, scope: !3180)
!3186 = !DILocation(line: 1542, column: 56, scope: !3180)
!3187 = !DILocation(line: 1541, column: 6, scope: !527)
!3188 = !DILocation(line: 1543, column: 37, scope: !3189)
!3189 = distinct !DILexicalBlock(scope: !3180, file: !1, line: 1542, column: 62)
!3190 = !DILocation(line: 1543, column: 40, scope: !3189)
!3191 = !DILocation(line: 1543, column: 45, scope: !3189)
!3192 = !DILocation(line: 1543, column: 9, scope: !3189)
!3193 = !DILocation(line: 1543, column: 7, scope: !3189)
!3194 = !DILocation(line: 1544, column: 7, scope: !3195)
!3195 = distinct !DILexicalBlock(scope: !3189, file: !1, line: 1544, column: 7)
!3196 = !DILocation(line: 1544, column: 11, scope: !3195)
!3197 = !DILocation(line: 1544, column: 7, scope: !3189)
!3198 = !DILocation(line: 1545, column: 12, scope: !3195)
!3199 = !DILocation(line: 1545, column: 4, scope: !3195)
!3200 = !DILocation(line: 1546, column: 2, scope: !3189)
!3201 = !DILocation(line: 1549, column: 6, scope: !3202)
!3202 = distinct !DILexicalBlock(scope: !527, file: !1, line: 1549, column: 6)
!3203 = !DILocation(line: 1549, column: 14, scope: !3202)
!3204 = !DILocation(line: 1549, column: 26, scope: !3202)
!3205 = !DILocation(line: 1549, column: 33, scope: !3202)
!3206 = !DILocation(line: 1549, column: 36, scope: !3207)
!3207 = !DILexicalBlockFile(scope: !3202, file: !1, discriminator: 1)
!3208 = !DILocation(line: 1549, column: 44, scope: !3207)
!3209 = !DILocation(line: 1549, column: 56, scope: !3207)
!3210 = !DILocation(line: 1549, column: 6, scope: !3207)
!3211 = !DILocation(line: 1550, column: 31, scope: !3212)
!3212 = distinct !DILexicalBlock(scope: !3202, file: !1, line: 1549, column: 64)
!3213 = !DILocation(line: 1551, column: 16, scope: !3212)
!3214 = !DILocation(line: 1551, column: 24, scope: !3212)
!3215 = !DILocation(line: 1551, column: 7, scope: !3212)
!3216 = !DILocation(line: 1550, column: 3, scope: !3212)
!3217 = !DILocation(line: 1552, column: 31, scope: !3212)
!3218 = !DILocation(line: 1553, column: 16, scope: !3212)
!3219 = !DILocation(line: 1553, column: 24, scope: !3212)
!3220 = !DILocation(line: 1553, column: 7, scope: !3212)
!3221 = !DILocation(line: 1552, column: 3, scope: !3212)
!3222 = !DILocation(line: 1554, column: 2, scope: !3212)
!3223 = !DILocation(line: 1556, column: 33, scope: !527)
!3224 = !DILocation(line: 1556, column: 38, scope: !527)
!3225 = !DILocation(line: 1556, column: 32, scope: !527)
!3226 = !DILocation(line: 1556, column: 29, scope: !527)
!3227 = !DILocation(line: 1556, column: 2, scope: !527)
!3228 = !DILocation(line: 1556, column: 7, scope: !527)
!3229 = !DILocation(line: 1556, column: 21, scope: !527)
!3230 = !DILocation(line: 1558, column: 10, scope: !527)
!3231 = !DILocation(line: 1558, column: 2, scope: !527)
!3232 = !DILocation(line: 1559, column: 1, scope: !527)
!3233 = !DILocalVariable(name: "a", arg: 1, scope: !528, file: !1, line: 1352, type: !4)
!3234 = !DILocation(line: 1352, column: 37, scope: !528)
!3235 = !DILocalVariable(name: "tar", arg: 2, scope: !528, file: !1, line: 1352, type: !291)
!3236 = !DILocation(line: 1352, column: 52, scope: !528)
!3237 = !DILocalVariable(name: "entry", arg: 3, scope: !528, file: !1, line: 1353, type: !30)
!3238 = !DILocation(line: 1353, column: 27, scope: !528)
!3239 = !DILocalVariable(name: "h", arg: 4, scope: !528, file: !1, line: 1353, type: !43)
!3240 = !DILocation(line: 1353, column: 46, scope: !528)
!3241 = !DILocalVariable(name: "header", scope: !528, file: !1, line: 1355, type: !336)
!3242 = !DILocation(line: 1355, column: 43, scope: !528)
!3243 = !DILocalVariable(name: "err", scope: !528, file: !1, line: 1356, type: !23)
!3244 = !DILocation(line: 1356, column: 6, scope: !528)
!3245 = !DILocalVariable(name: "err2", scope: !528, file: !1, line: 1356, type: !23)
!3246 = !DILocation(line: 1356, column: 24, scope: !528)
!3247 = !DILocation(line: 1359, column: 54, scope: !528)
!3248 = !DILocation(line: 1359, column: 11, scope: !528)
!3249 = !DILocation(line: 1359, column: 9, scope: !528)
!3250 = !DILocation(line: 1360, column: 36, scope: !3251)
!3251 = distinct !DILexicalBlock(scope: !528, file: !1, line: 1360, column: 6)
!3252 = !DILocation(line: 1361, column: 6, scope: !3251)
!3253 = !DILocation(line: 1361, column: 14, scope: !3251)
!3254 = !DILocation(line: 1361, column: 42, scope: !3251)
!3255 = !DILocation(line: 1361, column: 47, scope: !3251)
!3256 = !DILocation(line: 1360, column: 6, scope: !3251)
!3257 = !DILocation(line: 1361, column: 54, scope: !3251)
!3258 = !DILocation(line: 1360, column: 6, scope: !528)
!3259 = !DILocation(line: 1362, column: 37, scope: !3260)
!3260 = distinct !DILexicalBlock(scope: !3251, file: !1, line: 1361, column: 60)
!3261 = !DILocation(line: 1362, column: 40, scope: !3260)
!3262 = !DILocation(line: 1362, column: 45, scope: !3260)
!3263 = !DILocation(line: 1362, column: 9, scope: !3260)
!3264 = !DILocation(line: 1362, column: 7, scope: !3260)
!3265 = !DILocation(line: 1363, column: 7, scope: !3266)
!3266 = distinct !DILexicalBlock(scope: !3260, file: !1, line: 1363, column: 7)
!3267 = !DILocation(line: 1363, column: 11, scope: !3266)
!3268 = !DILocation(line: 1363, column: 7, scope: !3260)
!3269 = !DILocation(line: 1364, column: 12, scope: !3266)
!3270 = !DILocation(line: 1364, column: 4, scope: !3266)
!3271 = !DILocation(line: 1365, column: 2, scope: !3260)
!3272 = !DILocation(line: 1368, column: 23, scope: !528)
!3273 = !DILocation(line: 1368, column: 26, scope: !528)
!3274 = !DILocation(line: 1368, column: 31, scope: !528)
!3275 = !DILocation(line: 1368, column: 38, scope: !528)
!3276 = !DILocation(line: 1368, column: 9, scope: !528)
!3277 = !DILocation(line: 1368, column: 7, scope: !528)
!3278 = !DILocation(line: 1369, column: 6, scope: !3279)
!3279 = distinct !DILexicalBlock(scope: !528, file: !1, line: 1369, column: 6)
!3280 = !DILocation(line: 1369, column: 12, scope: !3279)
!3281 = !DILocation(line: 1369, column: 10, scope: !3279)
!3282 = !DILocation(line: 1369, column: 6, scope: !528)
!3283 = !DILocation(line: 1370, column: 9, scope: !3279)
!3284 = !DILocation(line: 1370, column: 7, scope: !3279)
!3285 = !DILocation(line: 1370, column: 3, scope: !3279)
!3286 = !DILocation(line: 1372, column: 33, scope: !528)
!3287 = !DILocation(line: 1372, column: 38, scope: !528)
!3288 = !DILocation(line: 1372, column: 32, scope: !528)
!3289 = !DILocation(line: 1372, column: 29, scope: !528)
!3290 = !DILocation(line: 1372, column: 2, scope: !528)
!3291 = !DILocation(line: 1372, column: 7, scope: !528)
!3292 = !DILocation(line: 1372, column: 21, scope: !528)
!3293 = !DILocation(line: 1373, column: 10, scope: !528)
!3294 = !DILocation(line: 1373, column: 2, scope: !528)
!3295 = !DILocation(line: 1374, column: 1, scope: !528)
!3296 = !DILocalVariable(name: "a", arg: 1, scope: !529, file: !1, line: 1381, type: !4)
!3297 = !DILocation(line: 1381, column: 45, scope: !529)
!3298 = !DILocalVariable(name: "tar", arg: 2, scope: !529, file: !1, line: 1381, type: !291)
!3299 = !DILocation(line: 1381, column: 60, scope: !529)
!3300 = !DILocalVariable(name: "entry", arg: 3, scope: !529, file: !1, line: 1382, type: !30)
!3301 = !DILocation(line: 1382, column: 27, scope: !529)
!3302 = !DILocalVariable(name: "h", arg: 4, scope: !529, file: !1, line: 1382, type: !43)
!3303 = !DILocation(line: 1382, column: 46, scope: !529)
!3304 = !DILocalVariable(name: "unconsumed", arg: 5, scope: !529, file: !1, line: 1382, type: !65)
!3305 = !DILocation(line: 1382, column: 57, scope: !529)
!3306 = !DILocalVariable(name: "size", scope: !529, file: !1, line: 1384, type: !52)
!3307 = !DILocation(line: 1384, column: 10, scope: !529)
!3308 = !DILocalVariable(name: "data", scope: !529, file: !1, line: 1385, type: !43)
!3309 = !DILocation(line: 1385, column: 14, scope: !529)
!3310 = !DILocalVariable(name: "p", scope: !529, file: !1, line: 1386, type: !80)
!3311 = !DILocation(line: 1386, column: 14, scope: !529)
!3312 = !DILocalVariable(name: "name", scope: !529, file: !1, line: 1386, type: !80)
!3313 = !DILocation(line: 1386, column: 18, scope: !529)
!3314 = !DILocalVariable(name: "wp", scope: !529, file: !1, line: 1387, type: !892)
!3315 = !DILocation(line: 1387, column: 17, scope: !529)
!3316 = !DILocalVariable(name: "wname", scope: !529, file: !1, line: 1387, type: !892)
!3317 = !DILocation(line: 1387, column: 22, scope: !529)
!3318 = !DILocation(line: 1389, column: 8, scope: !529)
!3319 = !DILocation(line: 1391, column: 40, scope: !529)
!3320 = !DILocation(line: 1391, column: 15, scope: !529)
!3321 = !DILocation(line: 1391, column: 13, scope: !529)
!3322 = !DILocation(line: 1391, column: 8, scope: !529)
!3323 = !DILocation(line: 1392, column: 6, scope: !3324)
!3324 = distinct !DILexicalBlock(scope: !529, file: !1, line: 1392, column: 6)
!3325 = !DILocation(line: 1392, column: 9, scope: !3324)
!3326 = !DILocation(line: 1392, column: 6, scope: !529)
!3327 = !DILocation(line: 1394, column: 3, scope: !3328)
!3328 = distinct !DILexicalBlock(scope: !3324, file: !1, line: 1392, column: 18)
!3329 = !DILocation(line: 1394, column: 11, scope: !3330)
!3330 = !DILexicalBlockFile(scope: !3331, file: !1, discriminator: 1)
!3331 = distinct !DILexicalBlock(scope: !3332, file: !1, line: 1394, column: 3)
!3332 = distinct !DILexicalBlock(scope: !3328, file: !1, line: 1394, column: 3)
!3333 = !DILocation(line: 1394, column: 10, scope: !3330)
!3334 = !DILocation(line: 1394, column: 14, scope: !3330)
!3335 = !DILocation(line: 1394, column: 3, scope: !3330)
!3336 = !DILocation(line: 1395, column: 8, scope: !3337)
!3337 = distinct !DILexicalBlock(scope: !3338, file: !1, line: 1395, column: 8)
!3338 = distinct !DILexicalBlock(scope: !3331, file: !1, line: 1394, column: 30)
!3339 = !DILocation(line: 1395, column: 14, scope: !3337)
!3340 = !DILocation(line: 1395, column: 21, scope: !3337)
!3341 = !DILocation(line: 1395, column: 24, scope: !3342)
!3342 = !DILexicalBlockFile(scope: !3337, file: !1, discriminator: 1)
!3343 = !DILocation(line: 1395, column: 30, scope: !3342)
!3344 = !DILocation(line: 1395, column: 8, scope: !3342)
!3345 = !DILocation(line: 1396, column: 13, scope: !3337)
!3346 = !DILocation(line: 1396, column: 16, scope: !3337)
!3347 = !DILocation(line: 1396, column: 11, scope: !3337)
!3348 = !DILocation(line: 1396, column: 5, scope: !3337)
!3349 = !DILocation(line: 1397, column: 3, scope: !3338)
!3350 = !DILocation(line: 1394, column: 24, scope: !3351)
!3351 = !DILexicalBlockFile(scope: !3331, file: !1, discriminator: 2)
!3352 = !DILocation(line: 1394, column: 3, scope: !3351)
!3353 = !DILocation(line: 1402, column: 7, scope: !3354)
!3354 = distinct !DILexicalBlock(scope: !3328, file: !1, line: 1402, column: 7)
!3355 = !DILocation(line: 1402, column: 16, scope: !3354)
!3356 = !DILocation(line: 1402, column: 24, scope: !3354)
!3357 = !DILocation(line: 1402, column: 27, scope: !3358)
!3358 = !DILexicalBlockFile(scope: !3354, file: !1, discriminator: 1)
!3359 = !DILocation(line: 1402, column: 36, scope: !3358)
!3360 = !DILocation(line: 1402, column: 44, scope: !3358)
!3361 = !DILocation(line: 1402, column: 47, scope: !3362)
!3362 = !DILexicalBlockFile(scope: !3354, file: !1, discriminator: 2)
!3363 = !DILocation(line: 1402, column: 56, scope: !3362)
!3364 = !DILocation(line: 1402, column: 7, scope: !3362)
!3365 = !DILocation(line: 1403, column: 4, scope: !3354)
!3366 = !DILocation(line: 1404, column: 2, scope: !3328)
!3367 = !DILocation(line: 1406, column: 37, scope: !3368)
!3368 = distinct !DILexicalBlock(scope: !3324, file: !1, line: 1404, column: 9)
!3369 = !DILocation(line: 1406, column: 14, scope: !3368)
!3370 = !DILocation(line: 1406, column: 12, scope: !3368)
!3371 = !DILocation(line: 1406, column: 8, scope: !3368)
!3372 = !DILocation(line: 1407, column: 7, scope: !3373)
!3373 = distinct !DILexicalBlock(scope: !3368, file: !1, line: 1407, column: 7)
!3374 = !DILocation(line: 1407, column: 9, scope: !3373)
!3375 = !DILocation(line: 1407, column: 7, scope: !3368)
!3376 = !DILocation(line: 1408, column: 4, scope: !3373)
!3377 = !DILocation(line: 1409, column: 3, scope: !3368)
!3378 = !DILocation(line: 1409, column: 11, scope: !3379)
!3379 = !DILexicalBlockFile(scope: !3380, file: !1, discriminator: 1)
!3380 = distinct !DILexicalBlock(scope: !3381, file: !1, line: 1409, column: 3)
!3381 = distinct !DILexicalBlock(scope: !3368, file: !1, line: 1409, column: 3)
!3382 = !DILocation(line: 1409, column: 10, scope: !3379)
!3383 = !DILocation(line: 1409, column: 13, scope: !3379)
!3384 = !DILocation(line: 1409, column: 3, scope: !3379)
!3385 = !DILocation(line: 1410, column: 8, scope: !3386)
!3386 = distinct !DILexicalBlock(scope: !3387, file: !1, line: 1410, column: 8)
!3387 = distinct !DILexicalBlock(scope: !3380, file: !1, line: 1409, column: 27)
!3388 = !DILocation(line: 1410, column: 13, scope: !3386)
!3389 = !DILocation(line: 1410, column: 20, scope: !3386)
!3390 = !DILocation(line: 1410, column: 23, scope: !3391)
!3391 = !DILexicalBlockFile(scope: !3386, file: !1, discriminator: 1)
!3392 = !DILocation(line: 1410, column: 28, scope: !3391)
!3393 = !DILocation(line: 1410, column: 8, scope: !3391)
!3394 = !DILocation(line: 1411, column: 12, scope: !3386)
!3395 = !DILocation(line: 1411, column: 14, scope: !3386)
!3396 = !DILocation(line: 1411, column: 10, scope: !3386)
!3397 = !DILocation(line: 1411, column: 5, scope: !3386)
!3398 = !DILocation(line: 1412, column: 3, scope: !3387)
!3399 = !DILocation(line: 1409, column: 22, scope: !3400)
!3400 = !DILexicalBlockFile(scope: !3380, file: !1, discriminator: 2)
!3401 = !DILocation(line: 1409, column: 3, scope: !3400)
!3402 = !DILocation(line: 1417, column: 7, scope: !3403)
!3403 = distinct !DILexicalBlock(scope: !3368, file: !1, line: 1417, column: 7)
!3404 = !DILocation(line: 1417, column: 15, scope: !3403)
!3405 = !DILocation(line: 1417, column: 22, scope: !3403)
!3406 = !DILocation(line: 1417, column: 25, scope: !3407)
!3407 = !DILexicalBlockFile(scope: !3403, file: !1, discriminator: 1)
!3408 = !DILocation(line: 1417, column: 33, scope: !3407)
!3409 = !DILocation(line: 1417, column: 40, scope: !3407)
!3410 = !DILocation(line: 1417, column: 43, scope: !3411)
!3411 = !DILexicalBlockFile(scope: !3403, file: !1, discriminator: 2)
!3412 = !DILocation(line: 1417, column: 51, scope: !3411)
!3413 = !DILocation(line: 1417, column: 7, scope: !3411)
!3414 = !DILocation(line: 1418, column: 4, scope: !3403)
!3415 = !DILocation(line: 1422, column: 28, scope: !529)
!3416 = !DILocation(line: 1422, column: 9, scope: !529)
!3417 = !DILocation(line: 1422, column: 7, scope: !529)
!3418 = !DILocation(line: 1436, column: 30, scope: !529)
!3419 = !DILocation(line: 1436, column: 41, scope: !529)
!3420 = !DILocation(line: 1436, column: 9, scope: !529)
!3421 = !DILocation(line: 1436, column: 7, scope: !529)
!3422 = !DILocation(line: 1437, column: 6, scope: !3423)
!3423 = distinct !DILexicalBlock(scope: !529, file: !1, line: 1437, column: 6)
!3424 = !DILocation(line: 1437, column: 11, scope: !3423)
!3425 = !DILocation(line: 1437, column: 6, scope: !529)
!3426 = !DILocation(line: 1438, column: 4, scope: !3427)
!3427 = distinct !DILexicalBlock(scope: !3423, file: !1, line: 1437, column: 20)
!3428 = !DILocation(line: 1438, column: 15, scope: !3427)
!3429 = !DILocation(line: 1439, column: 3, scope: !3427)
!3430 = !DILocation(line: 1441, column: 34, scope: !529)
!3431 = !DILocation(line: 1441, column: 41, scope: !529)
!3432 = !DILocation(line: 1441, column: 55, scope: !529)
!3433 = !DILocation(line: 1441, column: 2, scope: !529)
!3434 = !DILocation(line: 1442, column: 26, scope: !529)
!3435 = !DILocation(line: 1442, column: 31, scope: !529)
!3436 = !DILocation(line: 1442, column: 38, scope: !529)
!3437 = !DILocation(line: 1442, column: 3, scope: !529)
!3438 = !DILocation(line: 1442, column: 14, scope: !529)
!3439 = !DILocation(line: 1443, column: 23, scope: !529)
!3440 = !DILocation(line: 1443, column: 26, scope: !529)
!3441 = !DILocation(line: 1443, column: 2, scope: !529)
!3442 = !DILocation(line: 1444, column: 26, scope: !529)
!3443 = !DILocation(line: 1444, column: 29, scope: !529)
!3444 = !DILocation(line: 1444, column: 34, scope: !529)
!3445 = !DILocation(line: 1444, column: 41, scope: !529)
!3446 = !DILocation(line: 1444, column: 10, scope: !529)
!3447 = !DILocation(line: 1444, column: 2, scope: !529)
!3448 = !DILocation(line: 1445, column: 1, scope: !529)
!3449 = !DILocalVariable(name: "a", arg: 1, scope: !530, file: !1, line: 2458, type: !4)
!3450 = !DILocation(line: 2458, column: 41, scope: !530)
!3451 = !DILocalVariable(name: "tar", arg: 2, scope: !530, file: !1, line: 2458, type: !291)
!3452 = !DILocation(line: 2458, column: 56, scope: !530)
!3453 = !DILocalVariable(name: "unconsumed", arg: 3, scope: !530, file: !1, line: 2458, type: !65)
!3454 = !DILocation(line: 2458, column: 69, scope: !530)
!3455 = !DILocalVariable(name: "bytes_read", scope: !530, file: !1, line: 2460, type: !38)
!3456 = !DILocation(line: 2460, column: 10, scope: !530)
!3457 = !DILocalVariable(name: "entries", scope: !530, file: !1, line: 2461, type: !23)
!3458 = !DILocation(line: 2461, column: 6, scope: !530)
!3459 = !DILocalVariable(name: "offset", scope: !530, file: !1, line: 2462, type: !52)
!3460 = !DILocation(line: 2462, column: 10, scope: !530)
!3461 = !DILocalVariable(name: "size", scope: !530, file: !1, line: 2462, type: !52)
!3462 = !DILocation(line: 2462, column: 18, scope: !530)
!3463 = !DILocalVariable(name: "to_skip", scope: !530, file: !1, line: 2462, type: !52)
!3464 = !DILocation(line: 2462, column: 24, scope: !530)
!3465 = !DILocalVariable(name: "remaining", scope: !530, file: !1, line: 2462, type: !52)
!3466 = !DILocation(line: 2462, column: 33, scope: !530)
!3467 = !DILocation(line: 2465, column: 24, scope: !530)
!3468 = !DILocation(line: 2465, column: 2, scope: !530)
!3469 = !DILocation(line: 2467, column: 14, scope: !530)
!3470 = !DILocation(line: 2467, column: 19, scope: !530)
!3471 = !DILocation(line: 2467, column: 12, scope: !530)
!3472 = !DILocation(line: 2470, column: 36, scope: !530)
!3473 = !DILocation(line: 2470, column: 39, scope: !530)
!3474 = !DILocation(line: 2470, column: 56, scope: !530)
!3475 = !DILocation(line: 2470, column: 17, scope: !530)
!3476 = !DILocation(line: 2470, column: 12, scope: !530)
!3477 = !DILocation(line: 2470, column: 10, scope: !530)
!3478 = !DILocation(line: 2471, column: 6, scope: !3479)
!3479 = distinct !DILexicalBlock(scope: !530, file: !1, line: 2471, column: 6)
!3480 = !DILocation(line: 2471, column: 14, scope: !3479)
!3481 = !DILocation(line: 2471, column: 6, scope: !530)
!3482 = !DILocation(line: 2472, column: 3, scope: !3479)
!3483 = !DILocation(line: 2474, column: 2, scope: !530)
!3484 = !DILocation(line: 2474, column: 16, scope: !3485)
!3485 = !DILexicalBlockFile(scope: !530, file: !1, discriminator: 1)
!3486 = !DILocation(line: 2474, column: 19, scope: !3485)
!3487 = !DILocation(line: 2474, column: 2, scope: !3485)
!3488 = !DILocation(line: 2476, column: 31, scope: !3489)
!3489 = distinct !DILexicalBlock(scope: !530, file: !1, line: 2474, column: 24)
!3490 = !DILocation(line: 2476, column: 34, scope: !3489)
!3491 = !DILocation(line: 2476, column: 51, scope: !3489)
!3492 = !DILocation(line: 2476, column: 12, scope: !3489)
!3493 = !DILocation(line: 2476, column: 10, scope: !3489)
!3494 = !DILocation(line: 2477, column: 7, scope: !3495)
!3495 = distinct !DILexicalBlock(scope: !3489, file: !1, line: 2477, column: 7)
!3496 = !DILocation(line: 2477, column: 14, scope: !3495)
!3497 = !DILocation(line: 2477, column: 7, scope: !3489)
!3498 = !DILocation(line: 2478, column: 4, scope: !3495)
!3499 = !DILocation(line: 2479, column: 29, scope: !3489)
!3500 = !DILocation(line: 2479, column: 32, scope: !3489)
!3501 = !DILocation(line: 2479, column: 49, scope: !3489)
!3502 = !DILocation(line: 2479, column: 10, scope: !3489)
!3503 = !DILocation(line: 2479, column: 8, scope: !3489)
!3504 = !DILocation(line: 2480, column: 7, scope: !3505)
!3505 = distinct !DILexicalBlock(scope: !3489, file: !1, line: 2480, column: 7)
!3506 = !DILocation(line: 2480, column: 12, scope: !3505)
!3507 = !DILocation(line: 2480, column: 7, scope: !3489)
!3508 = !DILocation(line: 2481, column: 4, scope: !3505)
!3509 = !DILocation(line: 2483, column: 28, scope: !3510)
!3510 = distinct !DILexicalBlock(scope: !3489, file: !1, line: 2483, column: 7)
!3511 = !DILocation(line: 2483, column: 31, scope: !3510)
!3512 = !DILocation(line: 2483, column: 36, scope: !3510)
!3513 = !DILocation(line: 2483, column: 44, scope: !3510)
!3514 = !DILocation(line: 2483, column: 7, scope: !3510)
!3515 = !DILocation(line: 2483, column: 50, scope: !3510)
!3516 = !DILocation(line: 2483, column: 7, scope: !3489)
!3517 = !DILocation(line: 2484, column: 4, scope: !3510)
!3518 = !DILocation(line: 2474, column: 2, scope: !3519)
!3519 = !DILexicalBlockFile(scope: !530, file: !1, discriminator: 2)
!3520 = !DILocation(line: 2487, column: 23, scope: !530)
!3521 = !DILocation(line: 2487, column: 26, scope: !530)
!3522 = !DILocation(line: 2487, column: 2, scope: !530)
!3523 = !DILocation(line: 2488, column: 25, scope: !530)
!3524 = !DILocation(line: 2488, column: 30, scope: !530)
!3525 = !DILocation(line: 2488, column: 54, scope: !530)
!3526 = !DILocation(line: 2488, column: 52, scope: !530)
!3527 = !DILocation(line: 2488, column: 13, scope: !530)
!3528 = !DILocation(line: 2489, column: 21, scope: !530)
!3529 = !DILocation(line: 2489, column: 20, scope: !530)
!3530 = !DILocation(line: 2489, column: 18, scope: !530)
!3531 = !DILocation(line: 2489, column: 10, scope: !530)
!3532 = !DILocation(line: 2491, column: 6, scope: !3533)
!3533 = distinct !DILexicalBlock(scope: !530, file: !1, line: 2491, column: 6)
!3534 = !DILocation(line: 2491, column: 16, scope: !3533)
!3535 = !DILocation(line: 2491, column: 14, scope: !3533)
!3536 = !DILocation(line: 2491, column: 6, scope: !530)
!3537 = !DILocation(line: 2492, column: 3, scope: !3533)
!3538 = !DILocation(line: 2493, column: 6, scope: !3539)
!3539 = distinct !DILexicalBlock(scope: !530, file: !1, line: 2493, column: 6)
!3540 = !DILocation(line: 2493, column: 40, scope: !3539)
!3541 = !DILocation(line: 2493, column: 43, scope: !3539)
!3542 = !DILocation(line: 2493, column: 17, scope: !3539)
!3543 = !DILocation(line: 2493, column: 14, scope: !3539)
!3544 = !DILocation(line: 2493, column: 6, scope: !530)
!3545 = !DILocation(line: 2494, column: 3, scope: !3539)
!3546 = !DILocation(line: 2495, column: 20, scope: !530)
!3547 = !DILocation(line: 2495, column: 33, scope: !530)
!3548 = !DILocation(line: 2495, column: 31, scope: !530)
!3549 = !DILocation(line: 2495, column: 2, scope: !530)
!3550 = !DILocation(line: 2496, column: 1, scope: !530)
!3551 = !DILocalVariable(name: "a", arg: 1, scope: !471, file: !1, line: 1114, type: !4)
!3552 = !DILocation(line: 1114, column: 42, scope: !471)
!3553 = !DILocalVariable(name: "tar", arg: 2, scope: !471, file: !1, line: 1114, type: !291)
!3554 = !DILocation(line: 1114, column: 57, scope: !471)
!3555 = !DILocalVariable(name: "as", arg: 3, scope: !471, file: !1, line: 1115, type: !474)
!3556 = !DILocation(line: 1115, column: 28, scope: !471)
!3557 = !DILocalVariable(name: "h", arg: 4, scope: !471, file: !1, line: 1115, type: !43)
!3558 = !DILocation(line: 1115, column: 44, scope: !471)
!3559 = !DILocalVariable(name: "unconsumed", arg: 5, scope: !471, file: !1, line: 1115, type: !65)
!3560 = !DILocation(line: 1115, column: 55, scope: !471)
!3561 = !DILocalVariable(name: "size", scope: !471, file: !1, line: 1117, type: !52)
!3562 = !DILocation(line: 1117, column: 10, scope: !471)
!3563 = !DILocalVariable(name: "header", scope: !471, file: !1, line: 1118, type: !336)
!3564 = !DILocation(line: 1118, column: 43, scope: !471)
!3565 = !DILocalVariable(name: "src", scope: !471, file: !1, line: 1119, type: !43)
!3566 = !DILocation(line: 1119, column: 14, scope: !471)
!3567 = !DILocation(line: 1121, column: 8, scope: !471)
!3568 = !DILocation(line: 1122, column: 54, scope: !471)
!3569 = !DILocation(line: 1122, column: 11, scope: !471)
!3570 = !DILocation(line: 1122, column: 9, scope: !471)
!3571 = !DILocation(line: 1123, column: 19, scope: !471)
!3572 = !DILocation(line: 1123, column: 27, scope: !471)
!3573 = !DILocation(line: 1123, column: 10, scope: !471)
!3574 = !DILocation(line: 1123, column: 8, scope: !471)
!3575 = !DILocation(line: 1124, column: 7, scope: !3576)
!3576 = distinct !DILexicalBlock(scope: !471, file: !1, line: 1124, column: 6)
!3577 = !DILocation(line: 1124, column: 12, scope: !3576)
!3578 = !DILocation(line: 1124, column: 23, scope: !3576)
!3579 = !DILocation(line: 1124, column: 27, scope: !3580)
!3580 = !DILexicalBlockFile(scope: !3576, file: !1, discriminator: 1)
!3581 = !DILocation(line: 1124, column: 32, scope: !3580)
!3582 = !DILocation(line: 1124, column: 6, scope: !3580)
!3583 = !DILocation(line: 1125, column: 22, scope: !3584)
!3584 = distinct !DILexicalBlock(scope: !3576, file: !1, line: 1124, column: 38)
!3585 = !DILocation(line: 1125, column: 25, scope: !3584)
!3586 = !DILocation(line: 1125, column: 3, scope: !3584)
!3587 = !DILocation(line: 1127, column: 3, scope: !3584)
!3588 = !DILocation(line: 1131, column: 28, scope: !3589)
!3589 = distinct !DILexicalBlock(scope: !471, file: !1, line: 1131, column: 6)
!3590 = !DILocation(line: 1131, column: 40, scope: !3589)
!3591 = !DILocation(line: 1131, column: 44, scope: !3589)
!3592 = !DILocation(line: 1131, column: 6, scope: !3589)
!3593 = !DILocation(line: 1131, column: 48, scope: !3589)
!3594 = !DILocation(line: 1131, column: 6, scope: !471)
!3595 = !DILocation(line: 1132, column: 22, scope: !3596)
!3596 = distinct !DILexicalBlock(scope: !3589, file: !1, line: 1131, column: 57)
!3597 = !DILocation(line: 1132, column: 25, scope: !3596)
!3598 = !DILocation(line: 1132, column: 3, scope: !3596)
!3599 = !DILocation(line: 1134, column: 3, scope: !3596)
!3600 = !DILocation(line: 1137, column: 23, scope: !471)
!3601 = !DILocation(line: 1137, column: 26, scope: !471)
!3602 = !DILocation(line: 1137, column: 2, scope: !471)
!3603 = !DILocation(line: 1140, column: 26, scope: !471)
!3604 = !DILocation(line: 1140, column: 31, scope: !471)
!3605 = !DILocation(line: 1140, column: 38, scope: !471)
!3606 = !DILocation(line: 1140, column: 3, scope: !471)
!3607 = !DILocation(line: 1140, column: 14, scope: !471)
!3608 = !DILocation(line: 1141, column: 29, scope: !471)
!3609 = !DILocation(line: 1141, column: 33, scope: !471)
!3610 = !DILocation(line: 1141, column: 32, scope: !471)
!3611 = !DILocation(line: 1141, column: 8, scope: !471)
!3612 = !DILocation(line: 1141, column: 6, scope: !471)
!3613 = !DILocation(line: 1142, column: 6, scope: !3614)
!3614 = distinct !DILexicalBlock(scope: !471, file: !1, line: 1142, column: 6)
!3615 = !DILocation(line: 1142, column: 10, scope: !3614)
!3616 = !DILocation(line: 1142, column: 6, scope: !471)
!3617 = !DILocation(line: 1143, column: 4, scope: !3618)
!3618 = distinct !DILexicalBlock(scope: !3614, file: !1, line: 1142, column: 19)
!3619 = !DILocation(line: 1143, column: 15, scope: !3618)
!3620 = !DILocation(line: 1144, column: 3, scope: !3618)
!3621 = !DILocation(line: 1146, column: 9, scope: !471)
!3622 = !DILocation(line: 1146, column: 13, scope: !471)
!3623 = !DILocation(line: 1146, column: 16, scope: !471)
!3624 = !DILocation(line: 1146, column: 29, scope: !471)
!3625 = !DILocation(line: 1146, column: 2, scope: !471)
!3626 = !DILocation(line: 1147, column: 8, scope: !471)
!3627 = !DILocation(line: 1147, column: 2, scope: !471)
!3628 = !DILocation(line: 1147, column: 6, scope: !471)
!3629 = !DILocation(line: 1147, column: 14, scope: !471)
!3630 = !DILocation(line: 1148, column: 23, scope: !471)
!3631 = !DILocation(line: 1148, column: 2, scope: !471)
!3632 = !DILocation(line: 1148, column: 6, scope: !471)
!3633 = !DILocation(line: 1148, column: 13, scope: !471)
!3634 = !DILocation(line: 1149, column: 2, scope: !471)
!3635 = !DILocation(line: 1150, column: 1, scope: !471)
!3636 = !DILocalVariable(name: "a", arg: 1, scope: !478, file: !1, line: 1060, type: !4)
!3637 = !DILocation(line: 1060, column: 50, scope: !478)
!3638 = !DILocalVariable(name: "sconv", arg: 2, scope: !478, file: !1, line: 1061, type: !102)
!3639 = !DILocation(line: 1061, column: 33, scope: !478)
!3640 = !DILocalVariable(name: "name", arg: 3, scope: !478, file: !1, line: 1061, type: !80)
!3641 = !DILocation(line: 1061, column: 52, scope: !478)
!3642 = !DILocation(line: 1063, column: 6, scope: !3643)
!3643 = distinct !DILexicalBlock(scope: !478, file: !1, line: 1063, column: 6)
!3644 = !DILocation(line: 1063, column: 12, scope: !3643)
!3645 = !DILocation(line: 1063, column: 6, scope: !478)
!3646 = !DILocation(line: 1064, column: 22, scope: !3647)
!3647 = distinct !DILexicalBlock(scope: !3643, file: !1, line: 1063, column: 23)
!3648 = !DILocation(line: 1064, column: 25, scope: !3647)
!3649 = !DILocation(line: 1065, column: 39, scope: !3647)
!3650 = !DILocation(line: 1064, column: 3, scope: !3647)
!3651 = !DILocation(line: 1066, column: 3, scope: !3647)
!3652 = !DILocation(line: 1068, column: 21, scope: !478)
!3653 = !DILocation(line: 1068, column: 24, scope: !478)
!3654 = !DILocation(line: 1070, column: 6, scope: !478)
!3655 = !DILocation(line: 1070, column: 51, scope: !478)
!3656 = !DILocation(line: 1070, column: 12, scope: !478)
!3657 = !DILocation(line: 1068, column: 2, scope: !478)
!3658 = !DILocation(line: 1071, column: 2, scope: !478)
!3659 = !DILocation(line: 1072, column: 1, scope: !478)
!3660 = !DILocalVariable(name: "a", arg: 1, scope: !483, file: !1, line: 1568, type: !4)
!3661 = !DILocation(line: 1568, column: 33, scope: !483)
!3662 = !DILocalVariable(name: "tar", arg: 2, scope: !483, file: !1, line: 1568, type: !291)
!3663 = !DILocation(line: 1568, column: 48, scope: !483)
!3664 = !DILocalVariable(name: "entry", arg: 3, scope: !483, file: !1, line: 1569, type: !30)
!3665 = !DILocation(line: 1569, column: 27, scope: !483)
!3666 = !DILocalVariable(name: "in_as", arg: 4, scope: !483, file: !1, line: 1569, type: !474)
!3667 = !DILocation(line: 1569, column: 57, scope: !483)
!3668 = !DILocalVariable(name: "attr_length", scope: !483, file: !1, line: 1571, type: !45)
!3669 = !DILocation(line: 1571, column: 9, scope: !483)
!3670 = !DILocalVariable(name: "l", scope: !483, file: !1, line: 1571, type: !45)
!3671 = !DILocation(line: 1571, column: 22, scope: !483)
!3672 = !DILocalVariable(name: "line_length", scope: !483, file: !1, line: 1571, type: !45)
!3673 = !DILocation(line: 1571, column: 25, scope: !483)
!3674 = !DILocalVariable(name: "value_length", scope: !483, file: !1, line: 1571, type: !45)
!3675 = !DILocation(line: 1571, column: 38, scope: !483)
!3676 = !DILocalVariable(name: "p", scope: !483, file: !1, line: 1572, type: !95)
!3677 = !DILocation(line: 1572, column: 8, scope: !483)
!3678 = !DILocalVariable(name: "key", scope: !483, file: !1, line: 1573, type: !95)
!3679 = !DILocation(line: 1573, column: 8, scope: !483)
!3680 = !DILocalVariable(name: "value", scope: !483, file: !1, line: 1573, type: !95)
!3681 = !DILocation(line: 1573, column: 14, scope: !483)
!3682 = !DILocalVariable(name: "as", scope: !483, file: !1, line: 1574, type: !474)
!3683 = !DILocation(line: 1574, column: 25, scope: !483)
!3684 = !DILocalVariable(name: "sconv", scope: !483, file: !1, line: 1575, type: !102)
!3685 = !DILocation(line: 1575, column: 30, scope: !483)
!3686 = !DILocalVariable(name: "err", scope: !483, file: !1, line: 1576, type: !23)
!3687 = !DILocation(line: 1576, column: 6, scope: !483)
!3688 = !DILocalVariable(name: "err2", scope: !483, file: !1, line: 1576, type: !23)
!3689 = !DILocation(line: 1576, column: 11, scope: !483)
!3690 = !DILocalVariable(name: "attr", scope: !483, file: !1, line: 1577, type: !95)
!3691 = !DILocation(line: 1577, column: 8, scope: !483)
!3692 = !DILocation(line: 1577, column: 15, scope: !483)
!3693 = !DILocation(line: 1577, column: 22, scope: !483)
!3694 = !DILocation(line: 1579, column: 16, scope: !483)
!3695 = !DILocation(line: 1579, column: 23, scope: !483)
!3696 = !DILocation(line: 1579, column: 14, scope: !483)
!3697 = !DILocation(line: 1580, column: 2, scope: !483)
!3698 = !DILocation(line: 1580, column: 7, scope: !483)
!3699 = !DILocation(line: 1580, column: 29, scope: !483)
!3700 = !DILocation(line: 1581, column: 2, scope: !483)
!3701 = !DILocation(line: 1582, column: 2, scope: !483)
!3702 = !DILocation(line: 1583, column: 2, scope: !483)
!3703 = !DILocation(line: 1584, column: 2, scope: !483)
!3704 = !DILocation(line: 1585, column: 2, scope: !483)
!3705 = !DILocation(line: 1586, column: 6, scope: !483)
!3706 = !DILocation(line: 1587, column: 2, scope: !483)
!3707 = !DILocation(line: 1587, column: 9, scope: !3708)
!3708 = !DILexicalBlockFile(scope: !483, file: !1, discriminator: 1)
!3709 = !DILocation(line: 1587, column: 21, scope: !3708)
!3710 = !DILocation(line: 1587, column: 2, scope: !3708)
!3711 = !DILocation(line: 1589, column: 15, scope: !3712)
!3712 = distinct !DILexicalBlock(scope: !483, file: !1, line: 1587, column: 26)
!3713 = !DILocation(line: 1590, column: 7, scope: !3712)
!3714 = !DILocation(line: 1590, column: 5, scope: !3712)
!3715 = !DILocation(line: 1591, column: 7, scope: !3712)
!3716 = !DILocation(line: 1591, column: 5, scope: !3712)
!3717 = !DILocation(line: 1592, column: 3, scope: !3712)
!3718 = !DILocation(line: 1592, column: 10, scope: !3719)
!3719 = !DILexicalBlockFile(scope: !3712, file: !1, discriminator: 1)
!3720 = !DILocation(line: 1592, column: 11, scope: !3719)
!3721 = !DILocation(line: 1592, column: 3, scope: !3719)
!3722 = !DILocation(line: 1593, column: 9, scope: !3723)
!3723 = distinct !DILexicalBlock(scope: !3724, file: !1, line: 1593, column: 8)
!3724 = distinct !DILexicalBlock(scope: !3712, file: !1, line: 1592, column: 15)
!3725 = !DILocation(line: 1593, column: 8, scope: !3723)
!3726 = !DILocation(line: 1593, column: 11, scope: !3723)
!3727 = !DILocation(line: 1593, column: 8, scope: !3724)
!3728 = !DILocation(line: 1594, column: 6, scope: !3729)
!3729 = distinct !DILexicalBlock(scope: !3723, file: !1, line: 1593, column: 19)
!3730 = !DILocation(line: 1595, column: 6, scope: !3729)
!3731 = !DILocation(line: 1596, column: 5, scope: !3729)
!3732 = !DILocation(line: 1598, column: 9, scope: !3733)
!3733 = distinct !DILexicalBlock(scope: !3724, file: !1, line: 1598, column: 8)
!3734 = !DILocation(line: 1598, column: 8, scope: !3733)
!3735 = !DILocation(line: 1598, column: 11, scope: !3733)
!3736 = !DILocation(line: 1598, column: 17, scope: !3733)
!3737 = !DILocation(line: 1598, column: 21, scope: !3738)
!3738 = !DILexicalBlockFile(scope: !3733, file: !1, discriminator: 1)
!3739 = !DILocation(line: 1598, column: 20, scope: !3738)
!3740 = !DILocation(line: 1598, column: 23, scope: !3738)
!3741 = !DILocation(line: 1598, column: 8, scope: !3738)
!3742 = !DILocation(line: 1599, column: 24, scope: !3743)
!3743 = distinct !DILexicalBlock(scope: !3733, file: !1, line: 1598, column: 30)
!3744 = !DILocation(line: 1599, column: 27, scope: !3743)
!3745 = !DILocation(line: 1599, column: 5, scope: !3743)
!3746 = !DILocation(line: 1601, column: 5, scope: !3743)
!3747 = !DILocation(line: 1603, column: 16, scope: !3724)
!3748 = !DILocation(line: 1604, column: 20, scope: !3724)
!3749 = !DILocation(line: 1604, column: 19, scope: !3724)
!3750 = !DILocation(line: 1604, column: 22, scope: !3724)
!3751 = !DILocation(line: 1604, column: 16, scope: !3724)
!3752 = !DILocation(line: 1605, column: 8, scope: !3753)
!3753 = distinct !DILexicalBlock(scope: !3724, file: !1, line: 1605, column: 8)
!3754 = !DILocation(line: 1605, column: 20, scope: !3753)
!3755 = !DILocation(line: 1605, column: 8, scope: !3724)
!3756 = !DILocation(line: 1606, column: 24, scope: !3757)
!3757 = distinct !DILexicalBlock(scope: !3753, file: !1, line: 1605, column: 30)
!3758 = !DILocation(line: 1606, column: 27, scope: !3757)
!3759 = !DILocation(line: 1606, column: 5, scope: !3757)
!3760 = !DILocation(line: 1608, column: 5, scope: !3757)
!3761 = !DILocation(line: 1610, column: 5, scope: !3724)
!3762 = !DILocation(line: 1611, column: 5, scope: !3724)
!3763 = !DILocation(line: 1592, column: 3, scope: !3764)
!3764 = !DILexicalBlockFile(scope: !3712, file: !1, discriminator: 2)
!3765 = !DILocation(line: 1619, column: 7, scope: !3766)
!3766 = distinct !DILexicalBlock(scope: !3712, file: !1, line: 1619, column: 7)
!3767 = !DILocation(line: 1619, column: 21, scope: !3766)
!3768 = !DILocation(line: 1619, column: 19, scope: !3766)
!3769 = !DILocation(line: 1620, column: 7, scope: !3766)
!3770 = !DILocation(line: 1620, column: 10, scope: !3771)
!3771 = !DILexicalBlockFile(scope: !3766, file: !1, discriminator: 1)
!3772 = !DILocation(line: 1620, column: 22, scope: !3771)
!3773 = !DILocation(line: 1621, column: 7, scope: !3766)
!3774 = !DILocation(line: 1621, column: 15, scope: !3771)
!3775 = !DILocation(line: 1621, column: 27, scope: !3771)
!3776 = !DILocation(line: 1621, column: 10, scope: !3771)
!3777 = !DILocation(line: 1621, column: 32, scope: !3771)
!3778 = !DILocation(line: 1619, column: 7, scope: !3719)
!3779 = !DILocation(line: 1623, column: 23, scope: !3780)
!3780 = distinct !DILexicalBlock(scope: !3766, file: !1, line: 1622, column: 3)
!3781 = !DILocation(line: 1623, column: 26, scope: !3780)
!3782 = !DILocation(line: 1623, column: 4, scope: !3780)
!3783 = !DILocation(line: 1625, column: 4, scope: !3780)
!3784 = !DILocation(line: 1629, column: 8, scope: !3712)
!3785 = !DILocation(line: 1629, column: 20, scope: !3712)
!3786 = !DILocation(line: 1629, column: 3, scope: !3712)
!3787 = !DILocation(line: 1629, column: 25, scope: !3712)
!3788 = !DILocation(line: 1632, column: 9, scope: !3712)
!3789 = !DILocation(line: 1632, column: 7, scope: !3712)
!3790 = !DILocation(line: 1633, column: 7, scope: !3791)
!3791 = distinct !DILexicalBlock(scope: !3712, file: !1, line: 1633, column: 7)
!3792 = !DILocation(line: 1633, column: 14, scope: !3791)
!3793 = !DILocation(line: 1633, column: 7, scope: !3712)
!3794 = !DILocation(line: 1634, column: 4, scope: !3791)
!3795 = !DILocation(line: 1635, column: 3, scope: !3712)
!3796 = !DILocation(line: 1635, column: 11, scope: !3719)
!3797 = !DILocation(line: 1635, column: 10, scope: !3719)
!3798 = !DILocation(line: 1635, column: 13, scope: !3719)
!3799 = !DILocation(line: 1635, column: 17, scope: !3764)
!3800 = !DILocation(line: 1635, column: 16, scope: !3764)
!3801 = !DILocation(line: 1635, column: 19, scope: !3764)
!3802 = !DILocation(line: 1635, column: 3, scope: !3803)
!3803 = !DILexicalBlockFile(scope: !3712, file: !1, discriminator: 3)
!3804 = !DILocation(line: 1636, column: 4, scope: !3712)
!3805 = !DILocation(line: 1635, column: 3, scope: !3806)
!3806 = !DILexicalBlockFile(scope: !3712, file: !1, discriminator: 4)
!3807 = !DILocation(line: 1637, column: 8, scope: !3808)
!3808 = distinct !DILexicalBlock(scope: !3712, file: !1, line: 1637, column: 7)
!3809 = !DILocation(line: 1637, column: 7, scope: !3808)
!3810 = !DILocation(line: 1637, column: 10, scope: !3808)
!3811 = !DILocation(line: 1637, column: 7, scope: !3712)
!3812 = !DILocation(line: 1638, column: 23, scope: !3813)
!3813 = distinct !DILexicalBlock(scope: !3808, file: !1, line: 1637, column: 19)
!3814 = !DILocation(line: 1638, column: 26, scope: !3813)
!3815 = !DILocation(line: 1638, column: 4, scope: !3813)
!3816 = !DILocation(line: 1640, column: 4, scope: !3813)
!3817 = !DILocation(line: 1642, column: 4, scope: !3712)
!3818 = !DILocation(line: 1642, column: 6, scope: !3712)
!3819 = !DILocation(line: 1644, column: 11, scope: !3712)
!3820 = !DILocation(line: 1644, column: 13, scope: !3712)
!3821 = !DILocation(line: 1644, column: 9, scope: !3712)
!3822 = !DILocation(line: 1647, column: 18, scope: !3712)
!3823 = !DILocation(line: 1647, column: 25, scope: !3712)
!3824 = !DILocation(line: 1647, column: 23, scope: !3712)
!3825 = !DILocation(line: 1647, column: 37, scope: !3712)
!3826 = !DILocation(line: 1647, column: 43, scope: !3712)
!3827 = !DILocation(line: 1647, column: 41, scope: !3712)
!3828 = !DILocation(line: 1647, column: 16, scope: !3712)
!3829 = !DILocation(line: 1650, column: 24, scope: !3712)
!3830 = !DILocation(line: 1650, column: 27, scope: !3712)
!3831 = !DILocation(line: 1650, column: 32, scope: !3712)
!3832 = !DILocation(line: 1650, column: 39, scope: !3712)
!3833 = !DILocation(line: 1650, column: 44, scope: !3712)
!3834 = !DILocation(line: 1650, column: 51, scope: !3712)
!3835 = !DILocation(line: 1650, column: 10, scope: !3712)
!3836 = !DILocation(line: 1650, column: 8, scope: !3712)
!3837 = !DILocation(line: 1651, column: 7, scope: !3838)
!3838 = distinct !DILexicalBlock(scope: !3712, file: !1, line: 1651, column: 7)
!3839 = !DILocation(line: 1651, column: 12, scope: !3838)
!3840 = !DILocation(line: 1651, column: 7, scope: !3712)
!3841 = !DILocation(line: 1652, column: 12, scope: !3838)
!3842 = !DILocation(line: 1652, column: 4, scope: !3838)
!3843 = !DILocation(line: 1653, column: 9, scope: !3712)
!3844 = !DILocation(line: 1653, column: 9, scope: !3719)
!3845 = !DILocation(line: 1653, column: 9, scope: !3764)
!3846 = !DILocation(line: 1653, column: 9, scope: !3803)
!3847 = !DILocation(line: 1653, column: 7, scope: !3803)
!3848 = !DILocation(line: 1656, column: 11, scope: !3712)
!3849 = !DILocation(line: 1656, column: 8, scope: !3712)
!3850 = !DILocation(line: 1657, column: 18, scope: !3712)
!3851 = !DILocation(line: 1657, column: 15, scope: !3712)
!3852 = !DILocation(line: 1587, column: 2, scope: !3853)
!3853 = !DILexicalBlockFile(scope: !483, file: !1, discriminator: 2)
!3854 = !DILocation(line: 1669, column: 6, scope: !3855)
!3855 = distinct !DILexicalBlock(scope: !483, file: !1, line: 1669, column: 6)
!3856 = !DILocation(line: 1669, column: 11, scope: !3855)
!3857 = !DILocation(line: 1669, column: 6, scope: !483)
!3858 = !DILocation(line: 1670, column: 11, scope: !3855)
!3859 = !DILocation(line: 1670, column: 16, scope: !3855)
!3860 = !DILocation(line: 1670, column: 9, scope: !3855)
!3861 = !DILocation(line: 1670, column: 3, scope: !3855)
!3862 = !DILocation(line: 1673, column: 9, scope: !3863)
!3863 = distinct !DILexicalBlock(scope: !3855, file: !1, line: 1671, column: 7)
!3864 = !DILocation(line: 1673, column: 12, scope: !3863)
!3865 = !DILocation(line: 1672, column: 11, scope: !3863)
!3866 = !DILocation(line: 1672, column: 9, scope: !3863)
!3867 = !DILocation(line: 1674, column: 7, scope: !3868)
!3868 = distinct !DILexicalBlock(scope: !3863, file: !1, line: 1674, column: 7)
!3869 = !DILocation(line: 1674, column: 13, scope: !3868)
!3870 = !DILocation(line: 1674, column: 7, scope: !3863)
!3871 = !DILocation(line: 1675, column: 4, scope: !3868)
!3872 = !DILocation(line: 1676, column: 7, scope: !3873)
!3873 = distinct !DILexicalBlock(scope: !3863, file: !1, line: 1676, column: 7)
!3874 = !DILocation(line: 1676, column: 12, scope: !3873)
!3875 = !DILocation(line: 1676, column: 7, scope: !3863)
!3876 = !DILocation(line: 1677, column: 38, scope: !3873)
!3877 = !DILocation(line: 1677, column: 4, scope: !3873)
!3878 = !DILocation(line: 1681, column: 6, scope: !3879)
!3879 = distinct !DILexicalBlock(scope: !483, file: !1, line: 1681, column: 6)
!3880 = !DILocation(line: 1681, column: 42, scope: !3879)
!3881 = !DILocation(line: 1681, column: 6, scope: !483)
!3882 = !DILocation(line: 1682, column: 34, scope: !3883)
!3883 = distinct !DILexicalBlock(scope: !3884, file: !1, line: 1682, column: 7)
!3884 = distinct !DILexicalBlock(scope: !3879, file: !1, line: 1681, column: 47)
!3885 = !DILocation(line: 1682, column: 41, scope: !3883)
!3886 = !DILocation(line: 1682, column: 46, scope: !3883)
!3887 = !DILocation(line: 1682, column: 58, scope: !3883)
!3888 = !DILocation(line: 1683, column: 7, scope: !3883)
!3889 = !DILocation(line: 1683, column: 44, scope: !3883)
!3890 = !DILocation(line: 1682, column: 7, scope: !3883)
!3891 = !DILocation(line: 1683, column: 51, scope: !3883)
!3892 = !DILocation(line: 1682, column: 7, scope: !3884)
!3893 = !DILocation(line: 1684, column: 38, scope: !3894)
!3894 = distinct !DILexicalBlock(scope: !3883, file: !1, line: 1683, column: 57)
!3895 = !DILocation(line: 1684, column: 41, scope: !3894)
!3896 = !DILocation(line: 1684, column: 10, scope: !3894)
!3897 = !DILocation(line: 1684, column: 8, scope: !3894)
!3898 = !DILocation(line: 1685, column: 8, scope: !3899)
!3899 = distinct !DILexicalBlock(scope: !3894, file: !1, line: 1685, column: 8)
!3900 = !DILocation(line: 1685, column: 12, scope: !3899)
!3901 = !DILocation(line: 1685, column: 8, scope: !3894)
!3902 = !DILocation(line: 1686, column: 13, scope: !3899)
!3903 = !DILocation(line: 1686, column: 5, scope: !3899)
!3904 = !DILocation(line: 1688, column: 29, scope: !3894)
!3905 = !DILocation(line: 1688, column: 36, scope: !3894)
!3906 = !DILocation(line: 1688, column: 41, scope: !3894)
!3907 = !DILocation(line: 1688, column: 53, scope: !3894)
!3908 = !DILocation(line: 1688, column: 4, scope: !3894)
!3909 = !DILocation(line: 1689, column: 3, scope: !3894)
!3910 = !DILocation(line: 1690, column: 2, scope: !3884)
!3911 = !DILocation(line: 1691, column: 6, scope: !3912)
!3912 = distinct !DILexicalBlock(scope: !483, file: !1, line: 1691, column: 6)
!3913 = !DILocation(line: 1691, column: 45, scope: !3912)
!3914 = !DILocation(line: 1691, column: 6, scope: !483)
!3915 = !DILocation(line: 1692, column: 33, scope: !3916)
!3916 = distinct !DILexicalBlock(scope: !3917, file: !1, line: 1692, column: 7)
!3917 = distinct !DILexicalBlock(scope: !3912, file: !1, line: 1691, column: 50)
!3918 = !DILocation(line: 1692, column: 40, scope: !3916)
!3919 = !DILocation(line: 1692, column: 45, scope: !3916)
!3920 = !DILocation(line: 1692, column: 60, scope: !3916)
!3921 = !DILocation(line: 1693, column: 7, scope: !3916)
!3922 = !DILocation(line: 1693, column: 47, scope: !3916)
!3923 = !DILocation(line: 1692, column: 7, scope: !3916)
!3924 = !DILocation(line: 1693, column: 54, scope: !3916)
!3925 = !DILocation(line: 1692, column: 7, scope: !3917)
!3926 = !DILocation(line: 1694, column: 38, scope: !3927)
!3927 = distinct !DILexicalBlock(scope: !3916, file: !1, line: 1693, column: 60)
!3928 = !DILocation(line: 1694, column: 41, scope: !3927)
!3929 = !DILocation(line: 1694, column: 10, scope: !3927)
!3930 = !DILocation(line: 1694, column: 8, scope: !3927)
!3931 = !DILocation(line: 1695, column: 8, scope: !3932)
!3932 = distinct !DILexicalBlock(scope: !3927, file: !1, line: 1695, column: 8)
!3933 = !DILocation(line: 1695, column: 12, scope: !3932)
!3934 = !DILocation(line: 1695, column: 8, scope: !3927)
!3935 = !DILocation(line: 1696, column: 13, scope: !3932)
!3936 = !DILocation(line: 1696, column: 5, scope: !3932)
!3937 = !DILocation(line: 1698, column: 28, scope: !3927)
!3938 = !DILocation(line: 1698, column: 35, scope: !3927)
!3939 = !DILocation(line: 1698, column: 40, scope: !3927)
!3940 = !DILocation(line: 1698, column: 55, scope: !3927)
!3941 = !DILocation(line: 1698, column: 4, scope: !3927)
!3942 = !DILocation(line: 1699, column: 3, scope: !3927)
!3943 = !DILocation(line: 1700, column: 2, scope: !3917)
!3944 = !DILocation(line: 1710, column: 5, scope: !483)
!3945 = !DILocation(line: 1711, column: 6, scope: !3946)
!3946 = distinct !DILexicalBlock(scope: !483, file: !1, line: 1711, column: 6)
!3947 = !DILocation(line: 1711, column: 54, scope: !3946)
!3948 = !DILocation(line: 1711, column: 6, scope: !483)
!3949 = !DILocation(line: 1712, column: 10, scope: !3946)
!3950 = !DILocation(line: 1712, column: 15, scope: !3946)
!3951 = !DILocation(line: 1712, column: 6, scope: !3946)
!3952 = !DILocation(line: 1712, column: 3, scope: !3946)
!3953 = !DILocation(line: 1713, column: 11, scope: !3954)
!3954 = distinct !DILexicalBlock(scope: !3946, file: !1, line: 1713, column: 11)
!3955 = !DILocation(line: 1713, column: 50, scope: !3954)
!3956 = !DILocation(line: 1713, column: 11, scope: !3946)
!3957 = !DILocation(line: 1714, column: 10, scope: !3954)
!3958 = !DILocation(line: 1714, column: 15, scope: !3954)
!3959 = !DILocation(line: 1714, column: 6, scope: !3954)
!3960 = !DILocation(line: 1714, column: 3, scope: !3954)
!3961 = !DILocation(line: 1715, column: 6, scope: !3962)
!3962 = distinct !DILexicalBlock(scope: !483, file: !1, line: 1715, column: 6)
!3963 = !DILocation(line: 1715, column: 9, scope: !3962)
!3964 = !DILocation(line: 1715, column: 6, scope: !483)
!3965 = !DILocation(line: 1716, column: 37, scope: !3966)
!3966 = distinct !DILexicalBlock(scope: !3967, file: !1, line: 1716, column: 7)
!3967 = distinct !DILexicalBlock(scope: !3962, file: !1, line: 1715, column: 18)
!3968 = !DILocation(line: 1716, column: 44, scope: !3966)
!3969 = !DILocation(line: 1716, column: 48, scope: !3966)
!3970 = !DILocation(line: 1717, column: 7, scope: !3966)
!3971 = !DILocation(line: 1717, column: 27, scope: !3966)
!3972 = !DILocation(line: 1716, column: 7, scope: !3966)
!3973 = !DILocation(line: 1717, column: 34, scope: !3966)
!3974 = !DILocation(line: 1716, column: 7, scope: !3967)
!3975 = !DILocation(line: 1718, column: 38, scope: !3976)
!3976 = distinct !DILexicalBlock(scope: !3966, file: !1, line: 1717, column: 40)
!3977 = !DILocation(line: 1718, column: 41, scope: !3976)
!3978 = !DILocation(line: 1718, column: 10, scope: !3976)
!3979 = !DILocation(line: 1718, column: 8, scope: !3976)
!3980 = !DILocation(line: 1719, column: 8, scope: !3981)
!3981 = distinct !DILexicalBlock(scope: !3976, file: !1, line: 1719, column: 8)
!3982 = !DILocation(line: 1719, column: 12, scope: !3981)
!3983 = !DILocation(line: 1719, column: 8, scope: !3976)
!3984 = !DILocation(line: 1720, column: 13, scope: !3981)
!3985 = !DILocation(line: 1720, column: 5, scope: !3981)
!3986 = !DILocation(line: 1722, column: 32, scope: !3976)
!3987 = !DILocation(line: 1722, column: 39, scope: !3976)
!3988 = !DILocation(line: 1722, column: 43, scope: !3976)
!3989 = !DILocation(line: 1722, column: 4, scope: !3976)
!3990 = !DILocation(line: 1723, column: 3, scope: !3976)
!3991 = !DILocation(line: 1724, column: 2, scope: !3967)
!3992 = !DILocation(line: 1725, column: 6, scope: !3993)
!3993 = distinct !DILexicalBlock(scope: !483, file: !1, line: 1725, column: 6)
!3994 = !DILocation(line: 1725, column: 42, scope: !3993)
!3995 = !DILocation(line: 1725, column: 6, scope: !483)
!3996 = !DILocation(line: 1726, column: 34, scope: !3997)
!3997 = distinct !DILexicalBlock(scope: !3998, file: !1, line: 1726, column: 7)
!3998 = distinct !DILexicalBlock(scope: !3993, file: !1, line: 1725, column: 47)
!3999 = !DILocation(line: 1726, column: 41, scope: !3997)
!4000 = !DILocation(line: 1726, column: 46, scope: !3997)
!4001 = !DILocation(line: 1726, column: 58, scope: !3997)
!4002 = !DILocation(line: 1727, column: 7, scope: !3997)
!4003 = !DILocation(line: 1727, column: 44, scope: !3997)
!4004 = !DILocation(line: 1726, column: 7, scope: !3997)
!4005 = !DILocation(line: 1727, column: 51, scope: !3997)
!4006 = !DILocation(line: 1726, column: 7, scope: !3998)
!4007 = !DILocation(line: 1728, column: 38, scope: !4008)
!4008 = distinct !DILexicalBlock(scope: !3997, file: !1, line: 1727, column: 57)
!4009 = !DILocation(line: 1728, column: 41, scope: !4008)
!4010 = !DILocation(line: 1728, column: 10, scope: !4008)
!4011 = !DILocation(line: 1728, column: 8, scope: !4008)
!4012 = !DILocation(line: 1729, column: 8, scope: !4013)
!4013 = distinct !DILexicalBlock(scope: !4008, file: !1, line: 1729, column: 8)
!4014 = !DILocation(line: 1729, column: 12, scope: !4013)
!4015 = !DILocation(line: 1729, column: 8, scope: !4008)
!4016 = !DILocation(line: 1730, column: 13, scope: !4013)
!4017 = !DILocation(line: 1730, column: 5, scope: !4013)
!4018 = !DILocation(line: 1732, column: 29, scope: !4008)
!4019 = !DILocation(line: 1732, column: 36, scope: !4008)
!4020 = !DILocation(line: 1732, column: 41, scope: !4008)
!4021 = !DILocation(line: 1732, column: 53, scope: !4008)
!4022 = !DILocation(line: 1732, column: 4, scope: !4008)
!4023 = !DILocation(line: 1733, column: 3, scope: !4008)
!4024 = !DILocation(line: 1734, column: 2, scope: !3998)
!4025 = !DILocation(line: 1735, column: 10, scope: !483)
!4026 = !DILocation(line: 1735, column: 2, scope: !483)
!4027 = !DILocation(line: 1736, column: 1, scope: !483)
!4028 = !DILocalVariable(name: "a", arg: 1, scope: !486, file: !1, line: 1845, type: !4)
!4029 = !DILocation(line: 1845, column: 36, scope: !486)
!4030 = !DILocalVariable(name: "tar", arg: 2, scope: !486, file: !1, line: 1845, type: !291)
!4031 = !DILocation(line: 1845, column: 51, scope: !486)
!4032 = !DILocalVariable(name: "entry", arg: 3, scope: !486, file: !1, line: 1846, type: !30)
!4033 = !DILocation(line: 1846, column: 27, scope: !486)
!4034 = !DILocalVariable(name: "key", arg: 4, scope: !486, file: !1, line: 1846, type: !80)
!4035 = !DILocation(line: 1846, column: 46, scope: !486)
!4036 = !DILocalVariable(name: "value", arg: 5, scope: !486, file: !1, line: 1846, type: !80)
!4037 = !DILocation(line: 1846, column: 63, scope: !486)
!4038 = !DILocalVariable(name: "value_length", arg: 6, scope: !486, file: !1, line: 1846, type: !45)
!4039 = !DILocation(line: 1846, column: 77, scope: !486)
!4040 = !DILocalVariable(name: "s", scope: !486, file: !1, line: 1848, type: !52)
!4041 = !DILocation(line: 1848, column: 10, scope: !486)
!4042 = !DILocalVariable(name: "n", scope: !486, file: !1, line: 1849, type: !42)
!4043 = !DILocation(line: 1849, column: 7, scope: !486)
!4044 = !DILocalVariable(name: "err", scope: !486, file: !1, line: 1850, type: !23)
!4045 = !DILocation(line: 1850, column: 6, scope: !486)
!4046 = !DILocalVariable(name: "r", scope: !486, file: !1, line: 1850, type: !23)
!4047 = !DILocation(line: 1850, column: 24, scope: !486)
!4048 = !DILocation(line: 1852, column: 6, scope: !4049)
!4049 = distinct !DILexicalBlock(scope: !486, file: !1, line: 1852, column: 6)
!4050 = !DILocation(line: 1852, column: 12, scope: !4049)
!4051 = !DILocation(line: 1852, column: 6, scope: !486)
!4052 = !DILocation(line: 1853, column: 9, scope: !4049)
!4053 = !DILocation(line: 1853, column: 3, scope: !4049)
!4054 = !DILocation(line: 1855, column: 10, scope: !486)
!4055 = !DILocation(line: 1855, column: 2, scope: !486)
!4056 = !DILocation(line: 1858, column: 15, scope: !4057)
!4057 = distinct !DILexicalBlock(scope: !4058, file: !1, line: 1858, column: 7)
!4058 = distinct !DILexicalBlock(scope: !486, file: !1, line: 1855, column: 18)
!4059 = !DILocation(line: 1858, column: 7, scope: !4057)
!4060 = !DILocation(line: 1858, column: 38, scope: !4057)
!4061 = !DILocation(line: 1858, column: 43, scope: !4057)
!4062 = !DILocation(line: 1859, column: 8, scope: !4057)
!4063 = !DILocation(line: 1859, column: 13, scope: !4057)
!4064 = !DILocation(line: 1858, column: 7, scope: !4065)
!4065 = !DILexicalBlockFile(scope: !4058, file: !1, discriminator: 1)
!4066 = !DILocation(line: 1860, column: 23, scope: !4067)
!4067 = distinct !DILexicalBlock(scope: !4057, file: !1, line: 1859, column: 29)
!4068 = !DILocation(line: 1860, column: 26, scope: !4067)
!4069 = !DILocation(line: 1860, column: 4, scope: !4067)
!4070 = !DILocation(line: 1862, column: 4, scope: !4067)
!4071 = !DILocation(line: 1866, column: 14, scope: !4072)
!4072 = distinct !DILexicalBlock(scope: !4058, file: !1, line: 1866, column: 7)
!4073 = !DILocation(line: 1866, column: 7, scope: !4072)
!4074 = !DILocation(line: 1866, column: 43, scope: !4072)
!4075 = !DILocation(line: 1866, column: 7, scope: !4058)
!4076 = !DILocation(line: 1867, column: 4, scope: !4077)
!4077 = distinct !DILexicalBlock(scope: !4072, file: !1, line: 1866, column: 49)
!4078 = !DILocation(line: 1867, column: 9, scope: !4077)
!4079 = !DILocation(line: 1867, column: 23, scope: !4077)
!4080 = !DILocation(line: 1868, column: 4, scope: !4077)
!4081 = !DILocation(line: 1868, column: 9, scope: !4077)
!4082 = !DILocation(line: 1868, column: 25, scope: !4077)
!4083 = !DILocation(line: 1869, column: 4, scope: !4077)
!4084 = !DILocation(line: 1869, column: 9, scope: !4077)
!4085 = !DILocation(line: 1869, column: 26, scope: !4077)
!4086 = !DILocation(line: 1870, column: 4, scope: !4077)
!4087 = !DILocation(line: 1870, column: 9, scope: !4077)
!4088 = !DILocation(line: 1870, column: 26, scope: !4077)
!4089 = !DILocation(line: 1871, column: 3, scope: !4077)
!4090 = !DILocation(line: 1872, column: 14, scope: !4091)
!4091 = distinct !DILexicalBlock(scope: !4058, file: !1, line: 1872, column: 7)
!4092 = !DILocation(line: 1872, column: 7, scope: !4091)
!4093 = !DILocation(line: 1872, column: 40, scope: !4091)
!4094 = !DILocation(line: 1872, column: 7, scope: !4058)
!4095 = !DILocation(line: 1873, column: 36, scope: !4096)
!4096 = distinct !DILexicalBlock(scope: !4091, file: !1, line: 1872, column: 46)
!4097 = !DILocation(line: 1873, column: 50, scope: !4096)
!4098 = !DILocation(line: 1873, column: 43, scope: !4096)
!4099 = !DILocation(line: 1873, column: 25, scope: !4100)
!4100 = !DILexicalBlockFile(scope: !4096, file: !1, discriminator: 1)
!4101 = !DILocation(line: 1873, column: 4, scope: !4096)
!4102 = !DILocation(line: 1873, column: 9, scope: !4096)
!4103 = !DILocation(line: 1873, column: 23, scope: !4096)
!4104 = !DILocation(line: 1874, column: 8, scope: !4105)
!4105 = distinct !DILexicalBlock(scope: !4096, file: !1, line: 1874, column: 8)
!4106 = !DILocation(line: 1874, column: 13, scope: !4105)
!4107 = !DILocation(line: 1874, column: 29, scope: !4105)
!4108 = !DILocation(line: 1874, column: 8, scope: !4096)
!4109 = !DILocation(line: 1875, column: 30, scope: !4110)
!4110 = distinct !DILexicalBlock(scope: !4111, file: !1, line: 1875, column: 9)
!4111 = distinct !DILexicalBlock(scope: !4105, file: !1, line: 1874, column: 36)
!4112 = !DILocation(line: 1875, column: 33, scope: !4110)
!4113 = !DILocation(line: 1876, column: 9, scope: !4110)
!4114 = !DILocation(line: 1876, column: 14, scope: !4110)
!4115 = !DILocation(line: 1876, column: 29, scope: !4110)
!4116 = !DILocation(line: 1876, column: 34, scope: !4110)
!4117 = !DILocation(line: 1875, column: 9, scope: !4110)
!4118 = !DILocation(line: 1877, column: 9, scope: !4110)
!4119 = !DILocation(line: 1875, column: 9, scope: !4111)
!4120 = !DILocation(line: 1878, column: 6, scope: !4110)
!4121 = !DILocation(line: 1879, column: 5, scope: !4111)
!4122 = !DILocation(line: 1879, column: 10, scope: !4111)
!4123 = !DILocation(line: 1879, column: 24, scope: !4111)
!4124 = !DILocation(line: 1880, column: 5, scope: !4111)
!4125 = !DILocation(line: 1880, column: 10, scope: !4111)
!4126 = !DILocation(line: 1880, column: 26, scope: !4111)
!4127 = !DILocation(line: 1881, column: 4, scope: !4111)
!4128 = !DILocation(line: 1882, column: 3, scope: !4096)
!4129 = !DILocation(line: 1883, column: 14, scope: !4130)
!4130 = distinct !DILexicalBlock(scope: !4058, file: !1, line: 1883, column: 7)
!4131 = !DILocation(line: 1883, column: 7, scope: !4130)
!4132 = !DILocation(line: 1883, column: 42, scope: !4130)
!4133 = !DILocation(line: 1883, column: 7, scope: !4058)
!4134 = !DILocation(line: 1884, column: 38, scope: !4135)
!4135 = distinct !DILexicalBlock(scope: !4130, file: !1, line: 1883, column: 48)
!4136 = !DILocation(line: 1884, column: 52, scope: !4135)
!4137 = !DILocation(line: 1884, column: 45, scope: !4135)
!4138 = !DILocation(line: 1884, column: 27, scope: !4139)
!4139 = !DILexicalBlockFile(scope: !4135, file: !1, discriminator: 1)
!4140 = !DILocation(line: 1884, column: 4, scope: !4135)
!4141 = !DILocation(line: 1884, column: 9, scope: !4135)
!4142 = !DILocation(line: 1884, column: 25, scope: !4135)
!4143 = !DILocation(line: 1885, column: 8, scope: !4144)
!4144 = distinct !DILexicalBlock(scope: !4135, file: !1, line: 1885, column: 8)
!4145 = !DILocation(line: 1885, column: 13, scope: !4144)
!4146 = !DILocation(line: 1885, column: 29, scope: !4144)
!4147 = !DILocation(line: 1885, column: 8, scope: !4135)
!4148 = !DILocation(line: 1886, column: 30, scope: !4149)
!4149 = distinct !DILexicalBlock(scope: !4150, file: !1, line: 1886, column: 9)
!4150 = distinct !DILexicalBlock(scope: !4144, file: !1, line: 1885, column: 36)
!4151 = !DILocation(line: 1886, column: 33, scope: !4149)
!4152 = !DILocation(line: 1887, column: 9, scope: !4149)
!4153 = !DILocation(line: 1887, column: 14, scope: !4149)
!4154 = !DILocation(line: 1887, column: 29, scope: !4149)
!4155 = !DILocation(line: 1887, column: 34, scope: !4149)
!4156 = !DILocation(line: 1886, column: 9, scope: !4149)
!4157 = !DILocation(line: 1888, column: 9, scope: !4149)
!4158 = !DILocation(line: 1886, column: 9, scope: !4150)
!4159 = !DILocation(line: 1889, column: 6, scope: !4149)
!4160 = !DILocation(line: 1890, column: 5, scope: !4150)
!4161 = !DILocation(line: 1890, column: 10, scope: !4150)
!4162 = !DILocation(line: 1890, column: 24, scope: !4150)
!4163 = !DILocation(line: 1891, column: 5, scope: !4150)
!4164 = !DILocation(line: 1891, column: 10, scope: !4150)
!4165 = !DILocation(line: 1891, column: 26, scope: !4150)
!4166 = !DILocation(line: 1892, column: 4, scope: !4150)
!4167 = !DILocation(line: 1893, column: 3, scope: !4135)
!4168 = !DILocation(line: 1894, column: 14, scope: !4169)
!4169 = distinct !DILexicalBlock(scope: !4058, file: !1, line: 1894, column: 7)
!4170 = !DILocation(line: 1894, column: 7, scope: !4169)
!4171 = !DILocation(line: 1894, column: 38, scope: !4169)
!4172 = !DILocation(line: 1894, column: 7, scope: !4058)
!4173 = !DILocation(line: 1895, column: 31, scope: !4174)
!4174 = distinct !DILexicalBlock(scope: !4169, file: !1, line: 1894, column: 44)
!4175 = !DILocation(line: 1895, column: 45, scope: !4174)
!4176 = !DILocation(line: 1895, column: 38, scope: !4174)
!4177 = !DILocation(line: 1895, column: 20, scope: !4178)
!4178 = !DILexicalBlockFile(scope: !4174, file: !1, discriminator: 1)
!4179 = !DILocation(line: 1895, column: 4, scope: !4174)
!4180 = !DILocation(line: 1895, column: 9, scope: !4174)
!4181 = !DILocation(line: 1895, column: 18, scope: !4174)
!4182 = !DILocation(line: 1896, column: 27, scope: !4174)
!4183 = !DILocation(line: 1896, column: 34, scope: !4174)
!4184 = !DILocation(line: 1896, column: 39, scope: !4174)
!4185 = !DILocation(line: 1896, column: 4, scope: !4174)
!4186 = !DILocation(line: 1897, column: 3, scope: !4174)
!4187 = !DILocation(line: 1900, column: 14, scope: !4188)
!4188 = distinct !DILexicalBlock(scope: !4058, file: !1, line: 1900, column: 7)
!4189 = !DILocation(line: 1900, column: 7, scope: !4188)
!4190 = !DILocation(line: 1900, column: 37, scope: !4188)
!4191 = !DILocation(line: 1900, column: 7, scope: !4058)
!4192 = !DILocation(line: 1901, column: 4, scope: !4193)
!4193 = distinct !DILexicalBlock(scope: !4188, file: !1, line: 1900, column: 43)
!4194 = !DILocation(line: 1901, column: 9, scope: !4193)
!4195 = !DILocation(line: 1901, column: 26, scope: !4193)
!4196 = !DILocation(line: 1902, column: 4, scope: !4193)
!4197 = !DILocation(line: 1902, column: 9, scope: !4193)
!4198 = !DILocation(line: 1902, column: 26, scope: !4193)
!4199 = !DILocation(line: 1903, column: 28, scope: !4200)
!4200 = distinct !DILexicalBlock(scope: !4193, file: !1, line: 1903, column: 8)
!4201 = !DILocation(line: 1903, column: 31, scope: !4200)
!4202 = !DILocation(line: 1903, column: 36, scope: !4200)
!4203 = !DILocation(line: 1903, column: 8, scope: !4200)
!4204 = !DILocation(line: 1903, column: 43, scope: !4200)
!4205 = !DILocation(line: 1903, column: 8, scope: !4193)
!4206 = !DILocation(line: 1904, column: 5, scope: !4200)
!4207 = !DILocation(line: 1905, column: 3, scope: !4193)
!4208 = !DILocation(line: 1908, column: 14, scope: !4209)
!4209 = distinct !DILexicalBlock(scope: !4058, file: !1, line: 1908, column: 7)
!4210 = !DILocation(line: 1908, column: 7, scope: !4209)
!4211 = !DILocation(line: 1908, column: 39, scope: !4209)
!4212 = !DILocation(line: 1908, column: 7, scope: !4058)
!4213 = !DILocation(line: 1909, column: 44, scope: !4214)
!4214 = distinct !DILexicalBlock(scope: !4209, file: !1, line: 1908, column: 45)
!4215 = !DILocation(line: 1909, column: 58, scope: !4214)
!4216 = !DILocation(line: 1909, column: 51, scope: !4214)
!4217 = !DILocation(line: 1909, column: 33, scope: !4218)
!4218 = !DILexicalBlockFile(scope: !4214, file: !1, discriminator: 1)
!4219 = !DILocation(line: 1909, column: 28, scope: !4214)
!4220 = !DILocation(line: 1909, column: 4, scope: !4214)
!4221 = !DILocation(line: 1909, column: 9, scope: !4214)
!4222 = !DILocation(line: 1909, column: 26, scope: !4214)
!4223 = !DILocation(line: 1910, column: 4, scope: !4214)
!4224 = !DILocation(line: 1910, column: 9, scope: !4214)
!4225 = !DILocation(line: 1910, column: 28, scope: !4214)
!4226 = !DILocation(line: 1911, column: 3, scope: !4214)
!4227 = !DILocation(line: 1912, column: 14, scope: !4228)
!4228 = distinct !DILexicalBlock(scope: !4058, file: !1, line: 1912, column: 7)
!4229 = !DILocation(line: 1912, column: 7, scope: !4228)
!4230 = !DILocation(line: 1912, column: 39, scope: !4228)
!4231 = !DILocation(line: 1912, column: 7, scope: !4058)
!4232 = !DILocation(line: 1913, column: 44, scope: !4233)
!4233 = distinct !DILexicalBlock(scope: !4228, file: !1, line: 1912, column: 45)
!4234 = !DILocation(line: 1913, column: 58, scope: !4233)
!4235 = !DILocation(line: 1913, column: 51, scope: !4233)
!4236 = !DILocation(line: 1913, column: 33, scope: !4237)
!4237 = !DILexicalBlockFile(scope: !4233, file: !1, discriminator: 1)
!4238 = !DILocation(line: 1913, column: 28, scope: !4233)
!4239 = !DILocation(line: 1913, column: 4, scope: !4233)
!4240 = !DILocation(line: 1913, column: 9, scope: !4233)
!4241 = !DILocation(line: 1913, column: 26, scope: !4233)
!4242 = !DILocation(line: 1914, column: 4, scope: !4233)
!4243 = !DILocation(line: 1914, column: 9, scope: !4233)
!4244 = !DILocation(line: 1914, column: 28, scope: !4233)
!4245 = !DILocation(line: 1915, column: 3, scope: !4233)
!4246 = !DILocation(line: 1916, column: 14, scope: !4247)
!4247 = distinct !DILexicalBlock(scope: !4058, file: !1, line: 1916, column: 7)
!4248 = !DILocation(line: 1916, column: 7, scope: !4247)
!4249 = !DILocation(line: 1916, column: 38, scope: !4247)
!4250 = !DILocation(line: 1916, column: 7, scope: !4058)
!4251 = !DILocation(line: 1923, column: 4, scope: !4252)
!4252 = distinct !DILexicalBlock(scope: !4247, file: !1, line: 1916, column: 44)
!4253 = !DILocation(line: 1923, column: 4, scope: !4254)
!4254 = !DILexicalBlockFile(scope: !4252, file: !1, discriminator: 1)
!4255 = !DILocation(line: 1923, column: 4, scope: !4256)
!4256 = !DILexicalBlockFile(scope: !4252, file: !1, discriminator: 2)
!4257 = !DILocation(line: 1923, column: 4, scope: !4258)
!4258 = !DILexicalBlockFile(scope: !4252, file: !1, discriminator: 3)
!4259 = !DILocation(line: 1924, column: 3, scope: !4252)
!4260 = !DILocation(line: 1925, column: 14, scope: !4261)
!4261 = distinct !DILexicalBlock(scope: !4058, file: !1, line: 1925, column: 7)
!4262 = !DILocation(line: 1925, column: 7, scope: !4261)
!4263 = !DILocation(line: 1925, column: 42, scope: !4261)
!4264 = !DILocation(line: 1925, column: 7, scope: !4058)
!4265 = !DILocation(line: 1926, column: 31, scope: !4266)
!4266 = distinct !DILexicalBlock(scope: !4261, file: !1, line: 1925, column: 48)
!4267 = !DILocation(line: 1926, column: 45, scope: !4266)
!4268 = !DILocation(line: 1926, column: 38, scope: !4266)
!4269 = !DILocation(line: 1926, column: 20, scope: !4270)
!4270 = !DILexicalBlockFile(scope: !4266, file: !1, discriminator: 1)
!4271 = !DILocation(line: 1926, column: 4, scope: !4266)
!4272 = !DILocation(line: 1926, column: 9, scope: !4266)
!4273 = !DILocation(line: 1926, column: 18, scope: !4266)
!4274 = !DILocation(line: 1927, column: 27, scope: !4266)
!4275 = !DILocation(line: 1927, column: 34, scope: !4266)
!4276 = !DILocation(line: 1927, column: 39, scope: !4266)
!4277 = !DILocation(line: 1927, column: 4, scope: !4266)
!4278 = !DILocation(line: 1928, column: 3, scope: !4266)
!4279 = !DILocation(line: 1929, column: 3, scope: !4058)
!4280 = !DILocation(line: 1937, column: 14, scope: !4281)
!4281 = distinct !DILexicalBlock(scope: !4058, file: !1, line: 1937, column: 7)
!4282 = !DILocation(line: 1937, column: 7, scope: !4281)
!4283 = !DILocation(line: 1937, column: 46, scope: !4281)
!4284 = !DILocation(line: 1937, column: 7, scope: !4058)
!4285 = !DILocation(line: 1938, column: 13, scope: !4286)
!4286 = distinct !DILexicalBlock(scope: !4281, file: !1, line: 1937, column: 52)
!4287 = !DILocation(line: 1938, column: 4, scope: !4286)
!4288 = !DILocation(line: 1939, column: 32, scope: !4286)
!4289 = !DILocation(line: 1939, column: 39, scope: !4286)
!4290 = !DILocation(line: 1939, column: 42, scope: !4286)
!4291 = !DILocation(line: 1939, column: 4, scope: !4286)
!4292 = !DILocation(line: 1940, column: 3, scope: !4286)
!4293 = !DILocation(line: 1941, column: 14, scope: !4294)
!4294 = distinct !DILexicalBlock(scope: !4058, file: !1, line: 1941, column: 7)
!4295 = !DILocation(line: 1941, column: 7, scope: !4294)
!4296 = !DILocation(line: 1941, column: 44, scope: !4294)
!4297 = !DILocation(line: 1941, column: 7, scope: !4058)
!4298 = !DILocation(line: 1942, column: 24, scope: !4294)
!4299 = !DILocation(line: 1942, column: 31, scope: !4294)
!4300 = !DILocation(line: 1942, column: 36, scope: !4294)
!4301 = !DILocation(line: 1942, column: 4, scope: !4294)
!4302 = !DILocation(line: 1943, column: 3, scope: !4058)
!4303 = !DILocation(line: 1946, column: 14, scope: !4304)
!4304 = distinct !DILexicalBlock(scope: !4058, file: !1, line: 1946, column: 7)
!4305 = !DILocation(line: 1946, column: 7, scope: !4304)
!4306 = !DILocation(line: 1946, column: 40, scope: !4304)
!4307 = !DILocation(line: 1946, column: 7, scope: !4058)
!4308 = !DILocation(line: 1947, column: 26, scope: !4309)
!4309 = distinct !DILexicalBlock(scope: !4304, file: !1, line: 1946, column: 46)
!4310 = !DILocation(line: 1947, column: 29, scope: !4309)
!4311 = !DILocation(line: 1947, column: 34, scope: !4309)
!4312 = !DILocation(line: 1947, column: 41, scope: !4309)
!4313 = !DILocation(line: 1947, column: 8, scope: !4309)
!4314 = !DILocation(line: 1947, column: 6, scope: !4309)
!4315 = !DILocation(line: 1949, column: 8, scope: !4316)
!4316 = distinct !DILexicalBlock(scope: !4309, file: !1, line: 1949, column: 8)
!4317 = !DILocation(line: 1949, column: 10, scope: !4316)
!4318 = !DILocation(line: 1949, column: 8, scope: !4309)
!4319 = !DILocation(line: 1950, column: 13, scope: !4316)
!4320 = !DILocation(line: 1950, column: 5, scope: !4316)
!4321 = !DILocation(line: 1951, column: 3, scope: !4309)
!4322 = !DILocation(line: 1951, column: 21, scope: !4323)
!4323 = !DILexicalBlockFile(scope: !4324, file: !1, discriminator: 1)
!4324 = distinct !DILexicalBlock(scope: !4304, file: !1, line: 1951, column: 14)
!4325 = !DILocation(line: 1951, column: 14, scope: !4323)
!4326 = !DILocation(line: 1951, column: 48, scope: !4323)
!4327 = !DILocation(line: 1952, column: 26, scope: !4328)
!4328 = distinct !DILexicalBlock(scope: !4324, file: !1, line: 1951, column: 54)
!4329 = !DILocation(line: 1952, column: 29, scope: !4328)
!4330 = !DILocation(line: 1952, column: 34, scope: !4328)
!4331 = !DILocation(line: 1952, column: 41, scope: !4328)
!4332 = !DILocation(line: 1952, column: 8, scope: !4328)
!4333 = !DILocation(line: 1952, column: 6, scope: !4328)
!4334 = !DILocation(line: 1954, column: 8, scope: !4335)
!4335 = distinct !DILexicalBlock(scope: !4328, file: !1, line: 1954, column: 8)
!4336 = !DILocation(line: 1954, column: 10, scope: !4335)
!4337 = !DILocation(line: 1954, column: 8, scope: !4328)
!4338 = !DILocation(line: 1955, column: 13, scope: !4335)
!4339 = !DILocation(line: 1955, column: 5, scope: !4335)
!4340 = !DILocation(line: 1956, column: 3, scope: !4328)
!4341 = !DILocation(line: 1956, column: 21, scope: !4342)
!4342 = !DILexicalBlockFile(scope: !4343, file: !1, discriminator: 1)
!4343 = distinct !DILexicalBlock(scope: !4324, file: !1, line: 1956, column: 14)
!4344 = !DILocation(line: 1956, column: 14, scope: !4342)
!4345 = !DILocation(line: 1956, column: 44, scope: !4342)
!4346 = !DILocation(line: 1957, column: 26, scope: !4347)
!4347 = distinct !DILexicalBlock(scope: !4343, file: !1, line: 1956, column: 50)
!4348 = !DILocation(line: 1957, column: 29, scope: !4347)
!4349 = !DILocation(line: 1957, column: 34, scope: !4347)
!4350 = !DILocation(line: 1957, column: 41, scope: !4347)
!4351 = !DILocation(line: 1957, column: 8, scope: !4347)
!4352 = !DILocation(line: 1957, column: 6, scope: !4347)
!4353 = !DILocation(line: 1959, column: 8, scope: !4354)
!4354 = distinct !DILexicalBlock(scope: !4347, file: !1, line: 1959, column: 8)
!4355 = !DILocation(line: 1959, column: 10, scope: !4354)
!4356 = !DILocation(line: 1959, column: 8, scope: !4347)
!4357 = !DILocation(line: 1960, column: 13, scope: !4354)
!4358 = !DILocation(line: 1960, column: 5, scope: !4354)
!4359 = !DILocation(line: 1961, column: 3, scope: !4347)
!4360 = !DILocation(line: 1961, column: 21, scope: !4361)
!4361 = !DILexicalBlockFile(scope: !4362, file: !1, discriminator: 1)
!4362 = distinct !DILexicalBlock(scope: !4343, file: !1, line: 1961, column: 14)
!4363 = !DILocation(line: 1961, column: 14, scope: !4361)
!4364 = !DILocation(line: 1961, column: 45, scope: !4361)
!4365 = !DILocation(line: 1962, column: 32, scope: !4366)
!4366 = distinct !DILexicalBlock(scope: !4362, file: !1, line: 1961, column: 51)
!4367 = !DILocation(line: 1963, column: 26, scope: !4366)
!4368 = !DILocation(line: 1963, column: 40, scope: !4366)
!4369 = !DILocation(line: 1963, column: 33, scope: !4366)
!4370 = !DILocation(line: 1963, column: 15, scope: !4371)
!4371 = !DILexicalBlockFile(scope: !4366, file: !1, discriminator: 1)
!4372 = !DILocation(line: 1962, column: 4, scope: !4366)
!4373 = !DILocation(line: 1964, column: 3, scope: !4366)
!4374 = !DILocation(line: 1964, column: 21, scope: !4375)
!4375 = !DILexicalBlockFile(scope: !4376, file: !1, discriminator: 1)
!4376 = distinct !DILexicalBlock(scope: !4362, file: !1, line: 1964, column: 14)
!4377 = !DILocation(line: 1964, column: 14, scope: !4375)
!4378 = !DILocation(line: 1964, column: 45, scope: !4375)
!4379 = !DILocation(line: 1965, column: 32, scope: !4380)
!4380 = distinct !DILexicalBlock(scope: !4376, file: !1, line: 1964, column: 51)
!4381 = !DILocation(line: 1966, column: 26, scope: !4380)
!4382 = !DILocation(line: 1966, column: 40, scope: !4380)
!4383 = !DILocation(line: 1966, column: 33, scope: !4380)
!4384 = !DILocation(line: 1966, column: 15, scope: !4385)
!4385 = !DILexicalBlockFile(scope: !4380, file: !1, discriminator: 1)
!4386 = !DILocation(line: 1965, column: 4, scope: !4380)
!4387 = !DILocation(line: 1967, column: 3, scope: !4380)
!4388 = !DILocation(line: 1967, column: 21, scope: !4389)
!4389 = !DILexicalBlockFile(scope: !4390, file: !1, discriminator: 1)
!4390 = distinct !DILexicalBlock(scope: !4376, file: !1, line: 1967, column: 14)
!4391 = !DILocation(line: 1967, column: 14, scope: !4389)
!4392 = !DILocation(line: 1967, column: 43, scope: !4389)
!4393 = !DILocation(line: 1968, column: 35, scope: !4394)
!4394 = distinct !DILexicalBlock(scope: !4390, file: !1, line: 1967, column: 49)
!4395 = !DILocation(line: 1968, column: 42, scope: !4394)
!4396 = !DILocation(line: 1968, column: 4, scope: !4394)
!4397 = !DILocation(line: 1969, column: 3, scope: !4394)
!4398 = !DILocation(line: 1969, column: 21, scope: !4399)
!4399 = !DILexicalBlockFile(scope: !4400, file: !1, discriminator: 1)
!4400 = distinct !DILexicalBlock(scope: !4390, file: !1, line: 1969, column: 14)
!4401 = !DILocation(line: 1969, column: 14, scope: !4399)
!4402 = !DILocation(line: 1969, column: 40, scope: !4399)
!4403 = !DILocation(line: 1970, column: 26, scope: !4404)
!4404 = distinct !DILexicalBlock(scope: !4400, file: !1, line: 1969, column: 46)
!4405 = !DILocation(line: 1971, column: 26, scope: !4404)
!4406 = !DILocation(line: 1971, column: 40, scope: !4404)
!4407 = !DILocation(line: 1971, column: 33, scope: !4404)
!4408 = !DILocation(line: 1971, column: 15, scope: !4409)
!4409 = !DILexicalBlockFile(scope: !4404, file: !1, discriminator: 1)
!4410 = !DILocation(line: 1970, column: 4, scope: !4404)
!4411 = !DILocation(line: 1972, column: 3, scope: !4404)
!4412 = !DILocation(line: 1972, column: 21, scope: !4413)
!4413 = !DILexicalBlockFile(scope: !4414, file: !1, discriminator: 1)
!4414 = distinct !DILexicalBlock(scope: !4400, file: !1, line: 1972, column: 14)
!4415 = !DILocation(line: 1972, column: 14, scope: !4413)
!4416 = !DILocation(line: 1972, column: 40, scope: !4413)
!4417 = !DILocation(line: 1973, column: 26, scope: !4418)
!4418 = distinct !DILexicalBlock(scope: !4414, file: !1, line: 1972, column: 46)
!4419 = !DILocation(line: 1974, column: 19, scope: !4418)
!4420 = !DILocation(line: 1974, column: 33, scope: !4418)
!4421 = !DILocation(line: 1974, column: 26, scope: !4418)
!4422 = !DILocation(line: 1974, column: 8, scope: !4423)
!4423 = !DILexicalBlockFile(scope: !4418, file: !1, discriminator: 1)
!4424 = !DILocation(line: 1973, column: 4, scope: !4418)
!4425 = !DILocation(line: 1975, column: 3, scope: !4418)
!4426 = !DILocation(line: 1975, column: 21, scope: !4427)
!4427 = !DILexicalBlockFile(scope: !4428, file: !1, discriminator: 1)
!4428 = distinct !DILexicalBlock(scope: !4414, file: !1, line: 1975, column: 14)
!4429 = !DILocation(line: 1975, column: 14, scope: !4427)
!4430 = !DILocation(line: 1975, column: 42, scope: !4427)
!4431 = !DILocation(line: 1976, column: 28, scope: !4432)
!4432 = distinct !DILexicalBlock(scope: !4428, file: !1, line: 1975, column: 48)
!4433 = !DILocation(line: 1977, column: 19, scope: !4432)
!4434 = !DILocation(line: 1977, column: 33, scope: !4432)
!4435 = !DILocation(line: 1977, column: 26, scope: !4432)
!4436 = !DILocation(line: 1977, column: 8, scope: !4437)
!4437 = !DILexicalBlockFile(scope: !4432, file: !1, discriminator: 1)
!4438 = !DILocation(line: 1976, column: 35, scope: !4432)
!4439 = !DILocation(line: 1976, column: 4, scope: !4432)
!4440 = !DILocation(line: 1978, column: 3, scope: !4432)
!4441 = !DILocation(line: 1978, column: 21, scope: !4442)
!4442 = !DILexicalBlockFile(scope: !4443, file: !1, discriminator: 1)
!4443 = distinct !DILexicalBlock(scope: !4428, file: !1, line: 1978, column: 14)
!4444 = !DILocation(line: 1978, column: 14, scope: !4442)
!4445 = !DILocation(line: 1978, column: 45, scope: !4442)
!4446 = !DILocation(line: 1979, column: 31, scope: !4447)
!4447 = distinct !DILexicalBlock(scope: !4443, file: !1, line: 1978, column: 51)
!4448 = !DILocation(line: 1979, column: 45, scope: !4447)
!4449 = !DILocation(line: 1979, column: 38, scope: !4447)
!4450 = !DILocation(line: 1979, column: 20, scope: !4451)
!4451 = !DILexicalBlockFile(scope: !4447, file: !1, discriminator: 1)
!4452 = !DILocation(line: 1979, column: 4, scope: !4447)
!4453 = !DILocation(line: 1979, column: 9, scope: !4447)
!4454 = !DILocation(line: 1979, column: 18, scope: !4447)
!4455 = !DILocation(line: 1980, column: 27, scope: !4447)
!4456 = !DILocation(line: 1980, column: 34, scope: !4447)
!4457 = !DILocation(line: 1980, column: 39, scope: !4447)
!4458 = !DILocation(line: 1980, column: 4, scope: !4447)
!4459 = !DILocation(line: 1981, column: 3, scope: !4447)
!4460 = !DILocation(line: 1981, column: 22, scope: !4461)
!4461 = !DILexicalBlockFile(scope: !4462, file: !1, discriminator: 1)
!4462 = distinct !DILexicalBlock(scope: !4443, file: !1, line: 1981, column: 14)
!4463 = !DILocation(line: 1981, column: 14, scope: !4461)
!4464 = !DILocation(line: 1981, column: 48, scope: !4461)
!4465 = !DILocation(line: 1982, column: 31, scope: !4466)
!4466 = distinct !DILexicalBlock(scope: !4462, file: !1, line: 1981, column: 54)
!4467 = !DILocation(line: 1982, column: 38, scope: !4466)
!4468 = !DILocation(line: 1982, column: 43, scope: !4466)
!4469 = !DILocation(line: 1983, column: 8, scope: !4466)
!4470 = !DILocation(line: 1982, column: 4, scope: !4466)
!4471 = !DILocation(line: 1984, column: 3, scope: !4466)
!4472 = !DILocation(line: 1984, column: 21, scope: !4473)
!4473 = !DILexicalBlockFile(scope: !4474, file: !1, discriminator: 1)
!4474 = distinct !DILexicalBlock(scope: !4462, file: !1, line: 1984, column: 14)
!4475 = !DILocation(line: 1984, column: 14, scope: !4473)
!4476 = !DILocation(line: 1984, column: 43, scope: !4473)
!4477 = !DILocation(line: 1986, column: 29, scope: !4478)
!4478 = distinct !DILexicalBlock(scope: !4474, file: !1, line: 1984, column: 49)
!4479 = !DILocation(line: 1986, column: 32, scope: !4478)
!4480 = !DILocation(line: 1986, column: 37, scope: !4478)
!4481 = !DILocation(line: 1986, column: 44, scope: !4478)
!4482 = !DILocation(line: 1986, column: 8, scope: !4478)
!4483 = !DILocation(line: 1986, column: 6, scope: !4478)
!4484 = !DILocation(line: 1987, column: 8, scope: !4485)
!4485 = distinct !DILexicalBlock(scope: !4478, file: !1, line: 1987, column: 8)
!4486 = !DILocation(line: 1987, column: 12, scope: !4485)
!4487 = !DILocation(line: 1987, column: 10, scope: !4485)
!4488 = !DILocation(line: 1987, column: 8, scope: !4478)
!4489 = !DILocation(line: 1988, column: 9, scope: !4490)
!4490 = distinct !DILexicalBlock(scope: !4491, file: !1, line: 1988, column: 9)
!4491 = distinct !DILexicalBlock(scope: !4485, file: !1, line: 1987, column: 17)
!4492 = !DILocation(line: 1988, column: 11, scope: !4490)
!4493 = !DILocation(line: 1988, column: 9, scope: !4491)
!4494 = !DILocation(line: 1989, column: 14, scope: !4490)
!4495 = !DILocation(line: 1989, column: 6, scope: !4490)
!4496 = !DILocation(line: 1990, column: 11, scope: !4491)
!4497 = !DILocation(line: 1990, column: 9, scope: !4491)
!4498 = !DILocation(line: 1991, column: 24, scope: !4491)
!4499 = !DILocation(line: 1991, column: 27, scope: !4491)
!4500 = !DILocation(line: 1991, column: 5, scope: !4491)
!4501 = !DILocation(line: 1994, column: 4, scope: !4491)
!4502 = !DILocation(line: 1995, column: 3, scope: !4478)
!4503 = !DILocation(line: 1996, column: 3, scope: !4058)
!4504 = !DILocation(line: 1998, column: 14, scope: !4505)
!4505 = distinct !DILexicalBlock(scope: !4058, file: !1, line: 1998, column: 7)
!4506 = !DILocation(line: 1998, column: 7, scope: !4505)
!4507 = !DILocation(line: 1998, column: 28, scope: !4505)
!4508 = !DILocation(line: 1998, column: 7, scope: !4058)
!4509 = !DILocation(line: 1999, column: 13, scope: !4510)
!4510 = distinct !DILexicalBlock(scope: !4505, file: !1, line: 1998, column: 34)
!4511 = !DILocation(line: 1999, column: 4, scope: !4510)
!4512 = !DILocation(line: 2000, column: 28, scope: !4510)
!4513 = !DILocation(line: 2000, column: 35, scope: !4510)
!4514 = !DILocation(line: 2000, column: 38, scope: !4510)
!4515 = !DILocation(line: 2000, column: 4, scope: !4510)
!4516 = !DILocation(line: 2001, column: 3, scope: !4510)
!4517 = !DILocation(line: 2002, column: 3, scope: !4058)
!4518 = !DILocation(line: 2004, column: 14, scope: !4519)
!4519 = distinct !DILexicalBlock(scope: !4058, file: !1, line: 2004, column: 7)
!4520 = !DILocation(line: 2004, column: 7, scope: !4519)
!4521 = !DILocation(line: 2004, column: 28, scope: !4519)
!4522 = !DILocation(line: 2004, column: 7, scope: !4058)
!4523 = !DILocation(line: 2005, column: 13, scope: !4524)
!4524 = distinct !DILexicalBlock(scope: !4519, file: !1, line: 2004, column: 34)
!4525 = !DILocation(line: 2005, column: 4, scope: !4524)
!4526 = !DILocation(line: 2006, column: 28, scope: !4524)
!4527 = !DILocation(line: 2006, column: 35, scope: !4524)
!4528 = !DILocation(line: 2006, column: 38, scope: !4524)
!4529 = !DILocation(line: 2006, column: 4, scope: !4524)
!4530 = !DILocation(line: 2007, column: 3, scope: !4524)
!4531 = !DILocation(line: 2007, column: 21, scope: !4532)
!4532 = !DILexicalBlockFile(scope: !4533, file: !1, discriminator: 1)
!4533 = distinct !DILexicalBlock(scope: !4519, file: !1, line: 2007, column: 14)
!4534 = !DILocation(line: 2007, column: 14, scope: !4532)
!4535 = !DILocation(line: 2007, column: 37, scope: !4532)
!4536 = !DILocation(line: 2009, column: 3, scope: !4537)
!4537 = distinct !DILexicalBlock(scope: !4533, file: !1, line: 2007, column: 43)
!4538 = !DILocation(line: 2009, column: 21, scope: !4539)
!4539 = !DILexicalBlockFile(scope: !4540, file: !1, discriminator: 1)
!4540 = distinct !DILexicalBlock(scope: !4533, file: !1, line: 2009, column: 14)
!4541 = !DILocation(line: 2009, column: 14, scope: !4539)
!4542 = !DILocation(line: 2009, column: 37, scope: !4539)
!4543 = !DILocation(line: 2011, column: 3, scope: !4544)
!4544 = distinct !DILexicalBlock(scope: !4540, file: !1, line: 2009, column: 43)
!4545 = !DILocation(line: 2012, column: 3, scope: !4058)
!4546 = !DILocation(line: 2014, column: 14, scope: !4547)
!4547 = distinct !DILexicalBlock(scope: !4058, file: !1, line: 2014, column: 7)
!4548 = !DILocation(line: 2014, column: 7, scope: !4547)
!4549 = !DILocation(line: 2014, column: 26, scope: !4547)
!4550 = !DILocation(line: 2014, column: 7, scope: !4058)
!4551 = !DILocation(line: 2015, column: 26, scope: !4552)
!4552 = distinct !DILexicalBlock(scope: !4547, file: !1, line: 2014, column: 32)
!4553 = !DILocation(line: 2016, column: 19, scope: !4552)
!4554 = !DILocation(line: 2016, column: 33, scope: !4552)
!4555 = !DILocation(line: 2016, column: 26, scope: !4552)
!4556 = !DILocation(line: 2016, column: 8, scope: !4557)
!4557 = !DILexicalBlockFile(scope: !4552, file: !1, discriminator: 1)
!4558 = !DILocation(line: 2015, column: 4, scope: !4552)
!4559 = !DILocation(line: 2017, column: 3, scope: !4552)
!4560 = !DILocation(line: 2017, column: 21, scope: !4561)
!4561 = !DILexicalBlockFile(scope: !4562, file: !1, discriminator: 1)
!4562 = distinct !DILexicalBlock(scope: !4547, file: !1, line: 2017, column: 14)
!4563 = !DILocation(line: 2017, column: 14, scope: !4561)
!4564 = !DILocation(line: 2017, column: 35, scope: !4561)
!4565 = !DILocation(line: 2018, column: 4, scope: !4566)
!4566 = distinct !DILexicalBlock(scope: !4562, file: !1, line: 2017, column: 41)
!4567 = !DILocation(line: 2018, column: 4, scope: !4568)
!4568 = !DILexicalBlockFile(scope: !4566, file: !1, discriminator: 1)
!4569 = !DILocation(line: 2018, column: 4, scope: !4570)
!4570 = !DILexicalBlockFile(scope: !4566, file: !1, discriminator: 2)
!4571 = !DILocation(line: 2018, column: 4, scope: !4572)
!4572 = !DILexicalBlockFile(scope: !4566, file: !1, discriminator: 3)
!4573 = !DILocation(line: 2019, column: 3, scope: !4566)
!4574 = !DILocation(line: 2020, column: 3, scope: !4058)
!4575 = !DILocation(line: 2022, column: 14, scope: !4576)
!4576 = distinct !DILexicalBlock(scope: !4058, file: !1, line: 2022, column: 7)
!4577 = !DILocation(line: 2022, column: 7, scope: !4576)
!4578 = !DILocation(line: 2022, column: 33, scope: !4576)
!4579 = !DILocation(line: 2022, column: 7, scope: !4058)
!4580 = !DILocation(line: 2023, column: 15, scope: !4581)
!4581 = distinct !DILexicalBlock(scope: !4582, file: !1, line: 2023, column: 8)
!4582 = distinct !DILexicalBlock(scope: !4576, file: !1, line: 2022, column: 39)
!4583 = !DILocation(line: 2023, column: 8, scope: !4581)
!4584 = !DILocation(line: 2023, column: 32, scope: !4581)
!4585 = !DILocation(line: 2023, column: 8, scope: !4582)
!4586 = !DILocation(line: 2025, column: 5, scope: !4581)
!4587 = !DILocation(line: 2025, column: 10, scope: !4581)
!4588 = !DILocation(line: 2025, column: 32, scope: !4581)
!4589 = !DILocation(line: 2026, column: 20, scope: !4590)
!4590 = distinct !DILexicalBlock(scope: !4581, file: !1, line: 2026, column: 13)
!4591 = !DILocation(line: 2026, column: 13, scope: !4590)
!4592 = !DILocation(line: 2026, column: 54, scope: !4590)
!4593 = !DILocation(line: 2026, column: 13, scope: !4581)
!4594 = !DILocation(line: 2027, column: 5, scope: !4590)
!4595 = !DILocation(line: 2027, column: 10, scope: !4590)
!4596 = !DILocation(line: 2027, column: 32, scope: !4590)
!4597 = !DILocation(line: 2028, column: 3, scope: !4582)
!4598 = !DILocation(line: 2029, column: 3, scope: !4058)
!4599 = !DILocation(line: 2032, column: 14, scope: !4600)
!4600 = distinct !DILexicalBlock(scope: !4058, file: !1, line: 2032, column: 7)
!4601 = !DILocation(line: 2032, column: 7, scope: !4600)
!4602 = !DILocation(line: 2032, column: 31, scope: !4600)
!4603 = !DILocation(line: 2032, column: 7, scope: !4058)
!4604 = !DILocation(line: 2033, column: 4, scope: !4605)
!4605 = distinct !DILexicalBlock(scope: !4600, file: !1, line: 2032, column: 37)
!4606 = !DILocation(line: 2033, column: 4, scope: !4607)
!4607 = !DILexicalBlockFile(scope: !4605, file: !1, discriminator: 1)
!4608 = !DILocation(line: 2033, column: 4, scope: !4609)
!4609 = !DILexicalBlockFile(scope: !4605, file: !1, discriminator: 2)
!4610 = !DILocation(line: 2033, column: 4, scope: !4611)
!4611 = !DILexicalBlockFile(scope: !4605, file: !1, discriminator: 3)
!4612 = !DILocation(line: 2034, column: 3, scope: !4605)
!4613 = !DILocation(line: 2035, column: 3, scope: !4058)
!4614 = !DILocation(line: 2037, column: 14, scope: !4615)
!4615 = distinct !DILexicalBlock(scope: !4058, file: !1, line: 2037, column: 7)
!4616 = !DILocation(line: 2037, column: 7, scope: !4615)
!4617 = !DILocation(line: 2037, column: 28, scope: !4615)
!4618 = !DILocation(line: 2037, column: 7, scope: !4058)
!4619 = !DILocation(line: 2038, column: 13, scope: !4620)
!4620 = distinct !DILexicalBlock(scope: !4615, file: !1, line: 2037, column: 34)
!4621 = !DILocation(line: 2038, column: 4, scope: !4620)
!4622 = !DILocation(line: 2039, column: 28, scope: !4620)
!4623 = !DILocation(line: 2039, column: 35, scope: !4620)
!4624 = !DILocation(line: 2039, column: 38, scope: !4620)
!4625 = !DILocation(line: 2039, column: 4, scope: !4620)
!4626 = !DILocation(line: 2040, column: 3, scope: !4620)
!4627 = !DILocation(line: 2041, column: 3, scope: !4058)
!4628 = !DILocation(line: 2043, column: 14, scope: !4629)
!4629 = distinct !DILexicalBlock(scope: !4058, file: !1, line: 2043, column: 7)
!4630 = !DILocation(line: 2043, column: 7, scope: !4629)
!4631 = !DILocation(line: 2043, column: 27, scope: !4629)
!4632 = !DILocation(line: 2043, column: 7, scope: !4058)
!4633 = !DILocation(line: 2044, column: 4, scope: !4634)
!4634 = distinct !DILexicalBlock(scope: !4629, file: !1, line: 2043, column: 33)
!4635 = !DILocation(line: 2044, column: 4, scope: !4636)
!4636 = !DILexicalBlockFile(scope: !4634, file: !1, discriminator: 1)
!4637 = !DILocation(line: 2044, column: 4, scope: !4638)
!4638 = !DILexicalBlockFile(scope: !4634, file: !1, discriminator: 2)
!4639 = !DILocation(line: 2044, column: 4, scope: !4640)
!4640 = !DILexicalBlockFile(scope: !4634, file: !1, discriminator: 3)
!4641 = !DILocation(line: 2045, column: 3, scope: !4634)
!4642 = !DILocation(line: 2046, column: 3, scope: !4058)
!4643 = !DILocation(line: 2049, column: 3, scope: !4058)
!4644 = !DILocation(line: 2053, column: 14, scope: !4645)
!4645 = distinct !DILexicalBlock(scope: !4058, file: !1, line: 2053, column: 7)
!4646 = !DILocation(line: 2053, column: 7, scope: !4645)
!4647 = !DILocation(line: 2053, column: 27, scope: !4645)
!4648 = !DILocation(line: 2053, column: 7, scope: !4058)
!4649 = !DILocation(line: 2056, column: 21, scope: !4650)
!4650 = distinct !DILexicalBlock(scope: !4645, file: !1, line: 2053, column: 33)
!4651 = !DILocation(line: 2056, column: 35, scope: !4650)
!4652 = !DILocation(line: 2056, column: 28, scope: !4650)
!4653 = !DILocation(line: 2056, column: 10, scope: !4654)
!4654 = !DILexicalBlockFile(scope: !4650, file: !1, discriminator: 1)
!4655 = !DILocation(line: 2055, column: 4, scope: !4650)
!4656 = !DILocation(line: 2055, column: 9, scope: !4650)
!4657 = !DILocation(line: 2056, column: 8, scope: !4650)
!4658 = !DILocation(line: 2065, column: 8, scope: !4659)
!4659 = distinct !DILexicalBlock(scope: !4650, file: !1, line: 2065, column: 8)
!4660 = !DILocation(line: 2065, column: 13, scope: !4659)
!4661 = !DILocation(line: 2065, column: 22, scope: !4659)
!4662 = !DILocation(line: 2065, column: 8, scope: !4650)
!4663 = !DILocation(line: 2066, column: 28, scope: !4664)
!4664 = distinct !DILexicalBlock(scope: !4659, file: !1, line: 2065, column: 27)
!4665 = !DILocation(line: 2067, column: 9, scope: !4664)
!4666 = !DILocation(line: 2067, column: 14, scope: !4664)
!4667 = !DILocation(line: 2066, column: 5, scope: !4664)
!4668 = !DILocation(line: 2069, column: 11, scope: !4664)
!4669 = !DILocation(line: 2069, column: 16, scope: !4664)
!4670 = !DILocation(line: 2068, column: 5, scope: !4664)
!4671 = !DILocation(line: 2068, column: 10, scope: !4664)
!4672 = !DILocation(line: 2069, column: 9, scope: !4664)
!4673 = !DILocation(line: 2070, column: 4, scope: !4664)
!4674 = !DILocation(line: 2071, column: 3, scope: !4650)
!4675 = !DILocation(line: 2072, column: 3, scope: !4058)
!4676 = !DILocation(line: 2074, column: 14, scope: !4677)
!4677 = distinct !DILexicalBlock(scope: !4058, file: !1, line: 2074, column: 7)
!4678 = !DILocation(line: 2074, column: 7, scope: !4677)
!4679 = !DILocation(line: 2074, column: 26, scope: !4677)
!4680 = !DILocation(line: 2074, column: 7, scope: !4058)
!4681 = !DILocation(line: 2075, column: 26, scope: !4682)
!4682 = distinct !DILexicalBlock(scope: !4677, file: !1, line: 2074, column: 32)
!4683 = !DILocation(line: 2076, column: 19, scope: !4682)
!4684 = !DILocation(line: 2076, column: 33, scope: !4682)
!4685 = !DILocation(line: 2076, column: 26, scope: !4682)
!4686 = !DILocation(line: 2076, column: 8, scope: !4687)
!4687 = !DILexicalBlockFile(scope: !4682, file: !1, discriminator: 1)
!4688 = !DILocation(line: 2075, column: 4, scope: !4682)
!4689 = !DILocation(line: 2077, column: 3, scope: !4682)
!4690 = !DILocation(line: 2077, column: 21, scope: !4691)
!4691 = !DILexicalBlockFile(scope: !4692, file: !1, discriminator: 1)
!4692 = distinct !DILexicalBlock(scope: !4677, file: !1, line: 2077, column: 14)
!4693 = !DILocation(line: 2077, column: 14, scope: !4691)
!4694 = !DILocation(line: 2077, column: 35, scope: !4691)
!4695 = !DILocation(line: 2078, column: 4, scope: !4696)
!4696 = distinct !DILexicalBlock(scope: !4692, file: !1, line: 2077, column: 41)
!4697 = !DILocation(line: 2078, column: 4, scope: !4698)
!4698 = !DILexicalBlockFile(scope: !4696, file: !1, discriminator: 1)
!4699 = !DILocation(line: 2078, column: 4, scope: !4700)
!4700 = !DILexicalBlockFile(scope: !4696, file: !1, discriminator: 2)
!4701 = !DILocation(line: 2078, column: 4, scope: !4702)
!4702 = !DILexicalBlockFile(scope: !4696, file: !1, discriminator: 3)
!4703 = !DILocation(line: 2079, column: 3, scope: !4696)
!4704 = !DILocation(line: 2080, column: 3, scope: !4058)
!4705 = !DILocation(line: 2082, column: 10, scope: !486)
!4706 = !DILocation(line: 2082, column: 2, scope: !486)
!4707 = !DILocation(line: 2083, column: 1, scope: !486)
!4708 = !DILocalVariable(name: "p", arg: 1, scope: !489, file: !1, line: 2628, type: !80)
!4709 = !DILocation(line: 2628, column: 24, scope: !489)
!4710 = !DILocalVariable(name: "char_cnt", arg: 2, scope: !489, file: !1, line: 2628, type: !45)
!4711 = !DILocation(line: 2628, column: 34, scope: !489)
!4712 = !DILocation(line: 2630, column: 25, scope: !489)
!4713 = !DILocation(line: 2630, column: 28, scope: !489)
!4714 = !DILocation(line: 2630, column: 9, scope: !489)
!4715 = !DILocation(line: 2630, column: 2, scope: !489)
!4716 = !DILocalVariable(name: "a", arg: 1, scope: !490, file: !1, line: 2356, type: !4)
!4717 = !DILocation(line: 2356, column: 42, scope: !490)
!4718 = !DILocalVariable(name: "tar", arg: 2, scope: !490, file: !1, line: 2356, type: !291)
!4719 = !DILocation(line: 2356, column: 57, scope: !490)
!4720 = !DILocalVariable(name: "p", arg: 3, scope: !490, file: !1, line: 2356, type: !80)
!4721 = !DILocation(line: 2356, column: 74, scope: !490)
!4722 = !DILocalVariable(name: "e", scope: !490, file: !1, line: 2358, type: !80)
!4723 = !DILocation(line: 2358, column: 14, scope: !490)
!4724 = !DILocalVariable(name: "offset", scope: !490, file: !1, line: 2359, type: !52)
!4725 = !DILocation(line: 2359, column: 10, scope: !490)
!4726 = !DILocalVariable(name: "size", scope: !490, file: !1, line: 2359, type: !52)
!4727 = !DILocation(line: 2359, column: 23, scope: !490)
!4728 = !DILocation(line: 2361, column: 2, scope: !490)
!4729 = !DILocation(line: 2362, column: 7, scope: !4730)
!4730 = distinct !DILexicalBlock(scope: !4731, file: !1, line: 2361, column: 11)
!4731 = distinct !DILexicalBlock(scope: !4732, file: !1, line: 2361, column: 2)
!4732 = distinct !DILexicalBlock(scope: !490, file: !1, line: 2361, column: 2)
!4733 = !DILocation(line: 2362, column: 5, scope: !4730)
!4734 = !DILocation(line: 2363, column: 3, scope: !4730)
!4735 = !DILocation(line: 2363, column: 11, scope: !4736)
!4736 = !DILexicalBlockFile(scope: !4730, file: !1, discriminator: 1)
!4737 = !DILocation(line: 2363, column: 10, scope: !4736)
!4738 = !DILocation(line: 2363, column: 13, scope: !4736)
!4739 = !DILocation(line: 2363, column: 21, scope: !4736)
!4740 = !DILocation(line: 2363, column: 25, scope: !4741)
!4741 = !DILexicalBlockFile(scope: !4730, file: !1, discriminator: 2)
!4742 = !DILocation(line: 2363, column: 24, scope: !4741)
!4743 = !DILocation(line: 2363, column: 27, scope: !4741)
!4744 = !DILocation(line: 2363, column: 3, scope: !4745)
!4745 = !DILexicalBlockFile(scope: !4730, file: !1, discriminator: 3)
!4746 = !DILocation(line: 2364, column: 9, scope: !4747)
!4747 = distinct !DILexicalBlock(scope: !4748, file: !1, line: 2364, column: 8)
!4748 = distinct !DILexicalBlock(scope: !4730, file: !1, line: 2363, column: 35)
!4749 = !DILocation(line: 2364, column: 8, scope: !4747)
!4750 = !DILocation(line: 2364, column: 11, scope: !4747)
!4751 = !DILocation(line: 2364, column: 17, scope: !4747)
!4752 = !DILocation(line: 2364, column: 21, scope: !4753)
!4753 = !DILexicalBlockFile(scope: !4747, file: !1, discriminator: 1)
!4754 = !DILocation(line: 2364, column: 20, scope: !4753)
!4755 = !DILocation(line: 2364, column: 23, scope: !4753)
!4756 = !DILocation(line: 2364, column: 8, scope: !4753)
!4757 = !DILocation(line: 2365, column: 5, scope: !4747)
!4758 = !DILocation(line: 2366, column: 5, scope: !4748)
!4759 = !DILocation(line: 2363, column: 3, scope: !4760)
!4760 = !DILexicalBlockFile(scope: !4730, file: !1, discriminator: 4)
!4761 = !DILocation(line: 2368, column: 7, scope: !4762)
!4762 = distinct !DILexicalBlock(scope: !4730, file: !1, line: 2368, column: 7)
!4763 = !DILocation(line: 2368, column: 14, scope: !4762)
!4764 = !DILocation(line: 2368, column: 7, scope: !4730)
!4765 = !DILocation(line: 2369, column: 24, scope: !4766)
!4766 = distinct !DILexicalBlock(scope: !4762, file: !1, line: 2368, column: 19)
!4767 = !DILocation(line: 2369, column: 27, scope: !4766)
!4768 = !DILocation(line: 2369, column: 31, scope: !4766)
!4769 = !DILocation(line: 2369, column: 29, scope: !4766)
!4770 = !DILocation(line: 2369, column: 13, scope: !4766)
!4771 = !DILocation(line: 2369, column: 11, scope: !4766)
!4772 = !DILocation(line: 2370, column: 8, scope: !4773)
!4773 = distinct !DILexicalBlock(scope: !4766, file: !1, line: 2370, column: 8)
!4774 = !DILocation(line: 2370, column: 15, scope: !4773)
!4775 = !DILocation(line: 2370, column: 8, scope: !4766)
!4776 = !DILocation(line: 2371, column: 5, scope: !4773)
!4777 = !DILocation(line: 2372, column: 3, scope: !4766)
!4778 = !DILocation(line: 2373, column: 22, scope: !4779)
!4779 = distinct !DILexicalBlock(scope: !4762, file: !1, line: 2372, column: 10)
!4780 = !DILocation(line: 2373, column: 25, scope: !4779)
!4781 = !DILocation(line: 2373, column: 29, scope: !4779)
!4782 = !DILocation(line: 2373, column: 27, scope: !4779)
!4783 = !DILocation(line: 2373, column: 11, scope: !4779)
!4784 = !DILocation(line: 2373, column: 9, scope: !4779)
!4785 = !DILocation(line: 2374, column: 8, scope: !4786)
!4786 = distinct !DILexicalBlock(scope: !4779, file: !1, line: 2374, column: 8)
!4787 = !DILocation(line: 2374, column: 13, scope: !4786)
!4788 = !DILocation(line: 2374, column: 8, scope: !4779)
!4789 = !DILocation(line: 2375, column: 5, scope: !4786)
!4790 = !DILocation(line: 2376, column: 29, scope: !4791)
!4791 = distinct !DILexicalBlock(scope: !4779, file: !1, line: 2376, column: 8)
!4792 = !DILocation(line: 2376, column: 32, scope: !4791)
!4793 = !DILocation(line: 2376, column: 37, scope: !4791)
!4794 = !DILocation(line: 2376, column: 45, scope: !4791)
!4795 = !DILocation(line: 2376, column: 8, scope: !4791)
!4796 = !DILocation(line: 2377, column: 8, scope: !4791)
!4797 = !DILocation(line: 2376, column: 8, scope: !4779)
!4798 = !DILocation(line: 2378, column: 5, scope: !4791)
!4799 = !DILocation(line: 2379, column: 11, scope: !4779)
!4800 = !DILocation(line: 2381, column: 8, scope: !4801)
!4801 = distinct !DILexicalBlock(scope: !4730, file: !1, line: 2381, column: 7)
!4802 = !DILocation(line: 2381, column: 7, scope: !4801)
!4803 = !DILocation(line: 2381, column: 10, scope: !4801)
!4804 = !DILocation(line: 2381, column: 7, scope: !4730)
!4805 = !DILocation(line: 2382, column: 4, scope: !4801)
!4806 = !DILocation(line: 2383, column: 7, scope: !4730)
!4807 = !DILocation(line: 2383, column: 9, scope: !4730)
!4808 = !DILocation(line: 2383, column: 5, scope: !4730)
!4809 = !DILocation(line: 2361, column: 2, scope: !4810)
!4810 = !DILexicalBlockFile(scope: !4731, file: !1, discriminator: 1)
!4811 = !DILocation(line: 2385, column: 1, scope: !490)
!4812 = !DILocalVariable(name: "p", arg: 1, scope: !493, file: !1, line: 2091, type: !80)
!4813 = !DILocation(line: 2091, column: 22, scope: !493)
!4814 = !DILocalVariable(name: "ps", arg: 2, scope: !493, file: !1, line: 2091, type: !66)
!4815 = !DILocation(line: 2091, column: 34, scope: !493)
!4816 = !DILocalVariable(name: "pn", arg: 3, scope: !493, file: !1, line: 2091, type: !496)
!4817 = !DILocation(line: 2091, column: 44, scope: !493)
!4818 = !DILocalVariable(name: "digit", scope: !493, file: !1, line: 2093, type: !82)
!4819 = !DILocation(line: 2093, column: 7, scope: !493)
!4820 = !DILocalVariable(name: "s", scope: !493, file: !1, line: 2094, type: !52)
!4821 = !DILocation(line: 2094, column: 10, scope: !493)
!4822 = !DILocalVariable(name: "l", scope: !493, file: !1, line: 2095, type: !47)
!4823 = !DILocation(line: 2095, column: 16, scope: !493)
!4824 = !DILocalVariable(name: "sign", scope: !493, file: !1, line: 2096, type: !23)
!4825 = !DILocation(line: 2096, column: 6, scope: !493)
!4826 = !DILocalVariable(name: "limit", scope: !493, file: !1, line: 2097, type: !52)
!4827 = !DILocation(line: 2097, column: 10, scope: !493)
!4828 = !DILocalVariable(name: "last_digit_limit", scope: !493, file: !1, line: 2097, type: !52)
!4829 = !DILocation(line: 2097, column: 17, scope: !493)
!4830 = !DILocation(line: 2099, column: 8, scope: !493)
!4831 = !DILocation(line: 2100, column: 19, scope: !493)
!4832 = !DILocation(line: 2102, column: 4, scope: !493)
!4833 = !DILocation(line: 2103, column: 7, scope: !493)
!4834 = !DILocation(line: 2104, column: 7, scope: !4835)
!4835 = distinct !DILexicalBlock(scope: !493, file: !1, line: 2104, column: 6)
!4836 = !DILocation(line: 2104, column: 6, scope: !4835)
!4837 = !DILocation(line: 2104, column: 9, scope: !4835)
!4838 = !DILocation(line: 2104, column: 6, scope: !493)
!4839 = !DILocation(line: 2105, column: 8, scope: !4840)
!4840 = distinct !DILexicalBlock(scope: !4835, file: !1, line: 2104, column: 17)
!4841 = !DILocation(line: 2106, column: 4, scope: !4840)
!4842 = !DILocation(line: 2107, column: 2, scope: !4840)
!4843 = !DILocation(line: 2108, column: 2, scope: !493)
!4844 = !DILocation(line: 2108, column: 10, scope: !4845)
!4845 = !DILexicalBlockFile(scope: !493, file: !1, discriminator: 1)
!4846 = !DILocation(line: 2108, column: 9, scope: !4845)
!4847 = !DILocation(line: 2108, column: 12, scope: !4845)
!4848 = !DILocation(line: 2108, column: 19, scope: !4845)
!4849 = !DILocation(line: 2108, column: 23, scope: !4850)
!4850 = !DILexicalBlockFile(scope: !493, file: !1, discriminator: 2)
!4851 = !DILocation(line: 2108, column: 22, scope: !4850)
!4852 = !DILocation(line: 2108, column: 25, scope: !4850)
!4853 = !DILocation(line: 2108, column: 2, scope: !4854)
!4854 = !DILexicalBlockFile(scope: !493, file: !1, discriminator: 3)
!4855 = !DILocation(line: 2109, column: 12, scope: !4856)
!4856 = distinct !DILexicalBlock(scope: !493, file: !1, line: 2108, column: 33)
!4857 = !DILocation(line: 2109, column: 11, scope: !4856)
!4858 = !DILocation(line: 2109, column: 14, scope: !4856)
!4859 = !DILocation(line: 2109, column: 9, scope: !4856)
!4860 = !DILocation(line: 2110, column: 7, scope: !4861)
!4861 = distinct !DILexicalBlock(scope: !4856, file: !1, line: 2110, column: 7)
!4862 = !DILocation(line: 2110, column: 11, scope: !4861)
!4863 = !DILocation(line: 2110, column: 9, scope: !4861)
!4864 = !DILocation(line: 2110, column: 17, scope: !4861)
!4865 = !DILocation(line: 2111, column: 8, scope: !4861)
!4866 = !DILocation(line: 2111, column: 13, scope: !4861)
!4867 = !DILocation(line: 2111, column: 10, scope: !4861)
!4868 = !DILocation(line: 2111, column: 19, scope: !4861)
!4869 = !DILocation(line: 2111, column: 22, scope: !4870)
!4870 = !DILexicalBlockFile(scope: !4861, file: !1, discriminator: 1)
!4871 = !DILocation(line: 2111, column: 30, scope: !4870)
!4872 = !DILocation(line: 2111, column: 28, scope: !4870)
!4873 = !DILocation(line: 2110, column: 7, scope: !4874)
!4874 = !DILexicalBlockFile(scope: !4856, file: !1, discriminator: 1)
!4875 = !DILocation(line: 2112, column: 6, scope: !4876)
!4876 = distinct !DILexicalBlock(scope: !4861, file: !1, line: 2111, column: 49)
!4877 = !DILocation(line: 2113, column: 4, scope: !4876)
!4878 = !DILocation(line: 2115, column: 8, scope: !4856)
!4879 = !DILocation(line: 2115, column: 10, scope: !4856)
!4880 = !DILocation(line: 2115, column: 18, scope: !4856)
!4881 = !DILocation(line: 2115, column: 16, scope: !4856)
!4882 = !DILocation(line: 2115, column: 5, scope: !4856)
!4883 = !DILocation(line: 2116, column: 3, scope: !4856)
!4884 = !DILocation(line: 2108, column: 2, scope: !4885)
!4885 = !DILexicalBlockFile(scope: !493, file: !1, discriminator: 4)
!4886 = !DILocation(line: 2119, column: 8, scope: !493)
!4887 = !DILocation(line: 2119, column: 12, scope: !493)
!4888 = !DILocation(line: 2119, column: 10, scope: !493)
!4889 = !DILocation(line: 2119, column: 3, scope: !493)
!4890 = !DILocation(line: 2119, column: 6, scope: !493)
!4891 = !DILocation(line: 2122, column: 3, scope: !493)
!4892 = !DILocation(line: 2122, column: 6, scope: !493)
!4893 = !DILocation(line: 2124, column: 7, scope: !4894)
!4894 = distinct !DILexicalBlock(scope: !493, file: !1, line: 2124, column: 6)
!4895 = !DILocation(line: 2124, column: 6, scope: !4894)
!4896 = !DILocation(line: 2124, column: 9, scope: !4894)
!4897 = !DILocation(line: 2124, column: 6, scope: !493)
!4898 = !DILocation(line: 2125, column: 3, scope: !4894)
!4899 = !DILocation(line: 2127, column: 4, scope: !493)
!4900 = !DILocation(line: 2128, column: 2, scope: !493)
!4901 = !DILocation(line: 2129, column: 3, scope: !4902)
!4902 = distinct !DILexicalBlock(scope: !493, file: !1, line: 2128, column: 5)
!4903 = !DILocation(line: 2130, column: 8, scope: !4904)
!4904 = distinct !DILexicalBlock(scope: !4902, file: !1, line: 2130, column: 7)
!4905 = !DILocation(line: 2130, column: 7, scope: !4904)
!4906 = !DILocation(line: 2130, column: 10, scope: !4904)
!4907 = !DILocation(line: 2130, column: 17, scope: !4904)
!4908 = !DILocation(line: 2130, column: 21, scope: !4909)
!4909 = !DILexicalBlockFile(scope: !4904, file: !1, discriminator: 1)
!4910 = !DILocation(line: 2130, column: 20, scope: !4909)
!4911 = !DILocation(line: 2130, column: 23, scope: !4909)
!4912 = !DILocation(line: 2130, column: 7, scope: !4909)
!4913 = !DILocation(line: 2131, column: 13, scope: !4904)
!4914 = !DILocation(line: 2131, column: 12, scope: !4904)
!4915 = !DILocation(line: 2131, column: 15, scope: !4904)
!4916 = !DILocation(line: 2131, column: 11, scope: !4904)
!4917 = !DILocation(line: 2131, column: 24, scope: !4904)
!4918 = !DILocation(line: 2131, column: 22, scope: !4904)
!4919 = !DILocation(line: 2131, column: 5, scope: !4904)
!4920 = !DILocation(line: 2131, column: 8, scope: !4904)
!4921 = !DILocation(line: 2131, column: 4, scope: !4904)
!4922 = !DILocation(line: 2133, column: 4, scope: !4904)
!4923 = !DILocation(line: 2134, column: 2, scope: !4902)
!4924 = !DILocation(line: 2134, column: 13, scope: !4845)
!4925 = !DILocation(line: 2134, column: 2, scope: !4845)
!4926 = !DILocation(line: 2135, column: 1, scope: !493)
!4927 = !DILocalVariable(name: "entry", arg: 1, scope: !497, file: !1, line: 1739, type: !30)
!4928 = !DILocation(line: 1739, column: 43, scope: !497)
!4929 = !DILocalVariable(name: "name", arg: 2, scope: !497, file: !1, line: 1740, type: !80)
!4930 = !DILocation(line: 1740, column: 14, scope: !497)
!4931 = !DILocalVariable(name: "value", arg: 3, scope: !497, file: !1, line: 1740, type: !80)
!4932 = !DILocation(line: 1740, column: 32, scope: !497)
!4933 = !DILocalVariable(name: "name_decoded", scope: !497, file: !1, line: 1742, type: !95)
!4934 = !DILocation(line: 1742, column: 8, scope: !497)
!4935 = !DILocalVariable(name: "value_decoded", scope: !497, file: !1, line: 1743, type: !122)
!4936 = !DILocation(line: 1743, column: 8, scope: !497)
!4937 = !DILocalVariable(name: "value_len", scope: !497, file: !1, line: 1744, type: !45)
!4938 = !DILocation(line: 1744, column: 9, scope: !497)
!4939 = !DILocation(line: 1746, column: 13, scope: !4940)
!4940 = distinct !DILexicalBlock(scope: !497, file: !1, line: 1746, column: 6)
!4941 = !DILocation(line: 1746, column: 6, scope: !4940)
!4942 = !DILocation(line: 1746, column: 19, scope: !4940)
!4943 = !DILocation(line: 1746, column: 24, scope: !4940)
!4944 = !DILocation(line: 1746, column: 35, scope: !4945)
!4945 = !DILexicalBlockFile(scope: !4940, file: !1, discriminator: 1)
!4946 = !DILocation(line: 1746, column: 28, scope: !4945)
!4947 = !DILocation(line: 1746, column: 67, scope: !4945)
!4948 = !DILocation(line: 1746, column: 6, scope: !4945)
!4949 = !DILocation(line: 1747, column: 3, scope: !4940)
!4950 = !DILocation(line: 1749, column: 7, scope: !497)
!4951 = !DILocation(line: 1752, column: 28, scope: !497)
!4952 = !DILocation(line: 1752, column: 17, scope: !497)
!4953 = !DILocation(line: 1752, column: 15, scope: !497)
!4954 = !DILocation(line: 1753, column: 6, scope: !4955)
!4955 = distinct !DILexicalBlock(scope: !497, file: !1, line: 1753, column: 6)
!4956 = !DILocation(line: 1753, column: 19, scope: !4955)
!4957 = !DILocation(line: 1753, column: 6, scope: !497)
!4958 = !DILocation(line: 1754, column: 3, scope: !4955)
!4959 = !DILocation(line: 1757, column: 32, scope: !497)
!4960 = !DILocation(line: 1757, column: 46, scope: !497)
!4961 = !DILocation(line: 1757, column: 39, scope: !497)
!4962 = !DILocation(line: 1757, column: 18, scope: !4963)
!4963 = !DILexicalBlockFile(scope: !497, file: !1, discriminator: 1)
!4964 = !DILocation(line: 1757, column: 16, scope: !497)
!4965 = !DILocation(line: 1758, column: 6, scope: !4966)
!4966 = distinct !DILexicalBlock(scope: !497, file: !1, line: 1758, column: 6)
!4967 = !DILocation(line: 1758, column: 20, scope: !4966)
!4968 = !DILocation(line: 1758, column: 6, scope: !497)
!4969 = !DILocation(line: 1759, column: 8, scope: !4970)
!4970 = distinct !DILexicalBlock(scope: !4966, file: !1, line: 1758, column: 29)
!4971 = !DILocation(line: 1759, column: 3, scope: !4970)
!4972 = !DILocation(line: 1760, column: 3, scope: !4970)
!4973 = !DILocation(line: 1763, column: 32, scope: !497)
!4974 = !DILocation(line: 1763, column: 39, scope: !497)
!4975 = !DILocation(line: 1764, column: 3, scope: !497)
!4976 = !DILocation(line: 1764, column: 18, scope: !497)
!4977 = !DILocation(line: 1763, column: 2, scope: !497)
!4978 = !DILocation(line: 1766, column: 7, scope: !497)
!4979 = !DILocation(line: 1766, column: 2, scope: !497)
!4980 = !DILocation(line: 1767, column: 7, scope: !497)
!4981 = !DILocation(line: 1767, column: 2, scope: !497)
!4982 = !DILocation(line: 1768, column: 2, scope: !497)
!4983 = !DILocation(line: 1769, column: 1, scope: !497)
!4984 = !DILocalVariable(name: "a", arg: 1, scope: !509, file: !1, line: 1786, type: !4)
!4985 = !DILocation(line: 1786, column: 40, scope: !509)
!4986 = !DILocalVariable(name: "tar", arg: 2, scope: !509, file: !1, line: 1786, type: !291)
!4987 = !DILocation(line: 1786, column: 55, scope: !509)
!4988 = !DILocalVariable(name: "entry", arg: 3, scope: !509, file: !1, line: 1787, type: !30)
!4989 = !DILocation(line: 1787, column: 27, scope: !509)
!4990 = !DILocalVariable(name: "value", arg: 4, scope: !509, file: !1, line: 1787, type: !80)
!4991 = !DILocation(line: 1787, column: 46, scope: !509)
!4992 = !DILocalVariable(name: "type", arg: 5, scope: !509, file: !1, line: 1787, type: !23)
!4993 = !DILocation(line: 1787, column: 57, scope: !509)
!4994 = !DILocalVariable(name: "r", scope: !509, file: !1, line: 1789, type: !23)
!4995 = !DILocation(line: 1789, column: 6, scope: !509)
!4996 = !DILocalVariable(name: "errstr", scope: !509, file: !1, line: 1790, type: !80)
!4997 = !DILocation(line: 1790, column: 14, scope: !509)
!4998 = !DILocation(line: 1792, column: 10, scope: !509)
!4999 = !DILocation(line: 1792, column: 2, scope: !509)
!5000 = !DILocation(line: 1794, column: 10, scope: !5001)
!5001 = distinct !DILexicalBlock(scope: !509, file: !1, line: 1792, column: 16)
!5002 = !DILocation(line: 1795, column: 3, scope: !5001)
!5003 = !DILocation(line: 1797, column: 10, scope: !5001)
!5004 = !DILocation(line: 1798, column: 3, scope: !5001)
!5005 = !DILocation(line: 1800, column: 10, scope: !5001)
!5006 = !DILocation(line: 1801, column: 3, scope: !5001)
!5007 = !DILocation(line: 1803, column: 22, scope: !5001)
!5008 = !DILocation(line: 1803, column: 25, scope: !5001)
!5009 = !DILocation(line: 1804, column: 31, scope: !5001)
!5010 = !DILocation(line: 1803, column: 3, scope: !5001)
!5011 = !DILocation(line: 1805, column: 3, scope: !5001)
!5012 = !DILocation(line: 1808, column: 6, scope: !5013)
!5013 = distinct !DILexicalBlock(scope: !509, file: !1, line: 1808, column: 6)
!5014 = !DILocation(line: 1808, column: 11, scope: !5013)
!5015 = !DILocation(line: 1808, column: 21, scope: !5013)
!5016 = !DILocation(line: 1808, column: 6, scope: !509)
!5017 = !DILocation(line: 1811, column: 6, scope: !5018)
!5018 = distinct !DILexicalBlock(scope: !5013, file: !1, line: 1808, column: 30)
!5019 = !DILocation(line: 1811, column: 9, scope: !5018)
!5020 = !DILocation(line: 1810, column: 7, scope: !5018)
!5021 = !DILocation(line: 1809, column: 3, scope: !5018)
!5022 = !DILocation(line: 1809, column: 8, scope: !5018)
!5023 = !DILocation(line: 1809, column: 18, scope: !5018)
!5024 = !DILocation(line: 1812, column: 7, scope: !5025)
!5025 = distinct !DILexicalBlock(scope: !5018, file: !1, line: 1812, column: 7)
!5026 = !DILocation(line: 1812, column: 12, scope: !5025)
!5027 = !DILocation(line: 1812, column: 22, scope: !5025)
!5028 = !DILocation(line: 1812, column: 7, scope: !5018)
!5029 = !DILocation(line: 1813, column: 4, scope: !5025)
!5030 = !DILocation(line: 1814, column: 2, scope: !5018)
!5031 = !DILocation(line: 1816, column: 48, scope: !509)
!5032 = !DILocation(line: 1816, column: 30, scope: !509)
!5033 = !DILocation(line: 1816, column: 56, scope: !509)
!5034 = !DILocation(line: 1816, column: 63, scope: !509)
!5035 = !DILocation(line: 1817, column: 6, scope: !509)
!5036 = !DILocation(line: 1817, column: 11, scope: !509)
!5037 = !DILocation(line: 1816, column: 6, scope: !5038)
!5038 = !DILexicalBlockFile(scope: !509, file: !1, discriminator: 1)
!5039 = !DILocation(line: 1816, column: 4, scope: !509)
!5040 = !DILocation(line: 1818, column: 6, scope: !5041)
!5041 = distinct !DILexicalBlock(scope: !509, file: !1, line: 1818, column: 6)
!5042 = !DILocation(line: 1818, column: 8, scope: !5041)
!5043 = !DILocation(line: 1818, column: 6, scope: !509)
!5044 = !DILocation(line: 1819, column: 7, scope: !5045)
!5045 = distinct !DILexicalBlock(scope: !5046, file: !1, line: 1819, column: 7)
!5046 = distinct !DILexicalBlock(scope: !5041, file: !1, line: 1818, column: 23)
!5047 = !DILocation(line: 1819, column: 9, scope: !5045)
!5048 = !DILocation(line: 1819, column: 7, scope: !5046)
!5049 = !DILocation(line: 1820, column: 23, scope: !5050)
!5050 = distinct !DILexicalBlock(scope: !5045, file: !1, line: 1819, column: 27)
!5051 = !DILocation(line: 1820, column: 26, scope: !5050)
!5052 = !DILocation(line: 1822, column: 8, scope: !5050)
!5053 = !DILocation(line: 1820, column: 4, scope: !5050)
!5054 = !DILocation(line: 1823, column: 12, scope: !5050)
!5055 = !DILocation(line: 1823, column: 4, scope: !5050)
!5056 = !DILocation(line: 1825, column: 22, scope: !5046)
!5057 = !DILocation(line: 1825, column: 25, scope: !5046)
!5058 = !DILocation(line: 1826, column: 53, scope: !5046)
!5059 = !DILocation(line: 1825, column: 3, scope: !5046)
!5060 = !DILocation(line: 1827, column: 2, scope: !5046)
!5061 = !DILocation(line: 1828, column: 10, scope: !509)
!5062 = !DILocation(line: 1828, column: 2, scope: !509)
!5063 = !DILocation(line: 1829, column: 1, scope: !509)
!5064 = !DILocalVariable(name: "entry", arg: 1, scope: !512, file: !1, line: 1772, type: !30)
!5065 = !DILocation(line: 1772, column: 50, scope: !512)
!5066 = !DILocalVariable(name: "name", arg: 2, scope: !512, file: !1, line: 1773, type: !80)
!5067 = !DILocation(line: 1773, column: 14, scope: !512)
!5068 = !DILocalVariable(name: "value", arg: 3, scope: !512, file: !1, line: 1773, type: !80)
!5069 = !DILocation(line: 1773, column: 32, scope: !512)
!5070 = !DILocalVariable(name: "value_length", arg: 4, scope: !512, file: !1, line: 1773, type: !45)
!5071 = !DILocation(line: 1773, column: 46, scope: !512)
!5072 = !DILocation(line: 1775, column: 13, scope: !5073)
!5073 = distinct !DILexicalBlock(scope: !512, file: !1, line: 1775, column: 6)
!5074 = !DILocation(line: 1775, column: 6, scope: !5073)
!5075 = !DILocation(line: 1775, column: 19, scope: !5073)
!5076 = !DILocation(line: 1775, column: 24, scope: !5073)
!5077 = !DILocation(line: 1775, column: 35, scope: !5078)
!5078 = !DILexicalBlockFile(scope: !5073, file: !1, discriminator: 1)
!5079 = !DILocation(line: 1775, column: 28, scope: !5078)
!5080 = !DILocation(line: 1775, column: 63, scope: !5078)
!5081 = !DILocation(line: 1775, column: 6, scope: !5078)
!5082 = !DILocation(line: 1776, column: 3, scope: !5073)
!5083 = !DILocation(line: 1778, column: 7, scope: !512)
!5084 = !DILocation(line: 1780, column: 32, scope: !512)
!5085 = !DILocation(line: 1780, column: 39, scope: !512)
!5086 = !DILocation(line: 1780, column: 45, scope: !512)
!5087 = !DILocation(line: 1780, column: 52, scope: !512)
!5088 = !DILocation(line: 1780, column: 2, scope: !512)
!5089 = !DILocation(line: 1782, column: 2, scope: !512)
!5090 = !DILocation(line: 1783, column: 1, scope: !512)
!5091 = !DILocalVariable(name: "a", arg: 1, scope: !515, file: !1, line: 2505, type: !4)
!5092 = !DILocation(line: 2505, column: 43, scope: !515)
!5093 = !DILocalVariable(name: "tar", arg: 2, scope: !515, file: !1, line: 2505, type: !291)
!5094 = !DILocation(line: 2505, column: 58, scope: !515)
!5095 = !DILocalVariable(name: "entry", arg: 3, scope: !515, file: !1, line: 2506, type: !30)
!5096 = !DILocation(line: 2506, column: 27, scope: !515)
!5097 = !DILocalVariable(name: "p", arg: 4, scope: !515, file: !1, line: 2506, type: !80)
!5098 = !DILocation(line: 2506, column: 46, scope: !515)
!5099 = !DILocalVariable(name: "e", scope: !515, file: !1, line: 2508, type: !80)
!5100 = !DILocation(line: 2508, column: 14, scope: !515)
!5101 = !DILocalVariable(name: "start", scope: !515, file: !1, line: 2509, type: !52)
!5102 = !DILocation(line: 2509, column: 10, scope: !515)
!5103 = !DILocalVariable(name: "end", scope: !515, file: !1, line: 2509, type: !52)
!5104 = !DILocation(line: 2509, column: 17, scope: !515)
!5105 = !DILocalVariable(name: "hole", scope: !515, file: !1, line: 2510, type: !23)
!5106 = !DILocation(line: 2510, column: 6, scope: !515)
!5107 = !DILocation(line: 2512, column: 8, scope: !515)
!5108 = !DILocation(line: 2514, column: 6, scope: !515)
!5109 = !DILocation(line: 2515, column: 7, scope: !5110)
!5110 = distinct !DILexicalBlock(scope: !515, file: !1, line: 2515, column: 6)
!5111 = !DILocation(line: 2515, column: 6, scope: !5110)
!5112 = !DILocation(line: 2515, column: 9, scope: !5110)
!5113 = !DILocation(line: 2515, column: 6, scope: !515)
!5114 = !DILocation(line: 2516, column: 4, scope: !5110)
!5115 = !DILocation(line: 2516, column: 3, scope: !5110)
!5116 = !DILocation(line: 2518, column: 3, scope: !5110)
!5117 = !DILocation(line: 2519, column: 2, scope: !515)
!5118 = !DILocation(line: 2520, column: 7, scope: !5119)
!5119 = distinct !DILexicalBlock(scope: !5120, file: !1, line: 2519, column: 11)
!5120 = distinct !DILexicalBlock(scope: !5121, file: !1, line: 2519, column: 2)
!5121 = distinct !DILexicalBlock(scope: !515, file: !1, line: 2519, column: 2)
!5122 = !DILocation(line: 2520, column: 5, scope: !5119)
!5123 = !DILocation(line: 2521, column: 3, scope: !5119)
!5124 = !DILocation(line: 2521, column: 11, scope: !5125)
!5125 = !DILexicalBlockFile(scope: !5119, file: !1, discriminator: 1)
!5126 = !DILocation(line: 2521, column: 10, scope: !5125)
!5127 = !DILocation(line: 2521, column: 13, scope: !5125)
!5128 = !DILocation(line: 2521, column: 21, scope: !5125)
!5129 = !DILocation(line: 2521, column: 25, scope: !5130)
!5130 = !DILexicalBlockFile(scope: !5119, file: !1, discriminator: 2)
!5131 = !DILocation(line: 2521, column: 24, scope: !5130)
!5132 = !DILocation(line: 2521, column: 27, scope: !5130)
!5133 = !DILocation(line: 2521, column: 3, scope: !5134)
!5134 = !DILexicalBlockFile(scope: !5119, file: !1, discriminator: 3)
!5135 = !DILocation(line: 2522, column: 9, scope: !5136)
!5136 = distinct !DILexicalBlock(scope: !5137, file: !1, line: 2522, column: 8)
!5137 = distinct !DILexicalBlock(scope: !5119, file: !1, line: 2521, column: 35)
!5138 = !DILocation(line: 2522, column: 8, scope: !5136)
!5139 = !DILocation(line: 2522, column: 11, scope: !5136)
!5140 = !DILocation(line: 2522, column: 17, scope: !5136)
!5141 = !DILocation(line: 2522, column: 21, scope: !5142)
!5142 = !DILexicalBlockFile(scope: !5136, file: !1, discriminator: 1)
!5143 = !DILocation(line: 2522, column: 20, scope: !5142)
!5144 = !DILocation(line: 2522, column: 23, scope: !5142)
!5145 = !DILocation(line: 2522, column: 8, scope: !5142)
!5146 = !DILocation(line: 2523, column: 5, scope: !5136)
!5147 = !DILocation(line: 2524, column: 5, scope: !5137)
!5148 = !DILocation(line: 2521, column: 3, scope: !5149)
!5149 = !DILexicalBlockFile(scope: !5119, file: !1, discriminator: 4)
!5150 = !DILocation(line: 2526, column: 11, scope: !5119)
!5151 = !DILocation(line: 2526, column: 9, scope: !5119)
!5152 = !DILocation(line: 2527, column: 20, scope: !5119)
!5153 = !DILocation(line: 2527, column: 23, scope: !5119)
!5154 = !DILocation(line: 2527, column: 27, scope: !5119)
!5155 = !DILocation(line: 2527, column: 25, scope: !5119)
!5156 = !DILocation(line: 2527, column: 9, scope: !5119)
!5157 = !DILocation(line: 2527, column: 7, scope: !5119)
!5158 = !DILocation(line: 2528, column: 7, scope: !5159)
!5159 = distinct !DILexicalBlock(scope: !5119, file: !1, line: 2528, column: 7)
!5160 = !DILocation(line: 2528, column: 11, scope: !5159)
!5161 = !DILocation(line: 2528, column: 7, scope: !5119)
!5162 = !DILocation(line: 2529, column: 4, scope: !5159)
!5163 = !DILocation(line: 2530, column: 7, scope: !5164)
!5164 = distinct !DILexicalBlock(scope: !5119, file: !1, line: 2530, column: 7)
!5165 = !DILocation(line: 2530, column: 15, scope: !5164)
!5166 = !DILocation(line: 2530, column: 13, scope: !5164)
!5167 = !DILocation(line: 2530, column: 7, scope: !5119)
!5168 = !DILocation(line: 2531, column: 29, scope: !5169)
!5169 = distinct !DILexicalBlock(scope: !5170, file: !1, line: 2531, column: 8)
!5170 = distinct !DILexicalBlock(scope: !5164, file: !1, line: 2530, column: 20)
!5171 = !DILocation(line: 2531, column: 32, scope: !5169)
!5172 = !DILocation(line: 2531, column: 37, scope: !5169)
!5173 = !DILocation(line: 2532, column: 8, scope: !5169)
!5174 = !DILocation(line: 2532, column: 14, scope: !5169)
!5175 = !DILocation(line: 2532, column: 12, scope: !5169)
!5176 = !DILocation(line: 2531, column: 8, scope: !5169)
!5177 = !DILocation(line: 2532, column: 21, scope: !5169)
!5178 = !DILocation(line: 2531, column: 8, scope: !5170)
!5179 = !DILocation(line: 2533, column: 5, scope: !5169)
!5180 = !DILocation(line: 2534, column: 29, scope: !5170)
!5181 = !DILocation(line: 2534, column: 4, scope: !5170)
!5182 = !DILocation(line: 2534, column: 9, scope: !5170)
!5183 = !DILocation(line: 2534, column: 22, scope: !5170)
!5184 = !DILocation(line: 2534, column: 27, scope: !5170)
!5185 = !DILocation(line: 2535, column: 3, scope: !5170)
!5186 = !DILocation(line: 2536, column: 8, scope: !5187)
!5187 = distinct !DILexicalBlock(scope: !5119, file: !1, line: 2536, column: 7)
!5188 = !DILocation(line: 2536, column: 7, scope: !5187)
!5189 = !DILocation(line: 2536, column: 10, scope: !5187)
!5190 = !DILocation(line: 2536, column: 7, scope: !5119)
!5191 = !DILocation(line: 2537, column: 4, scope: !5187)
!5192 = !DILocation(line: 2538, column: 7, scope: !5119)
!5193 = !DILocation(line: 2538, column: 9, scope: !5119)
!5194 = !DILocation(line: 2538, column: 5, scope: !5119)
!5195 = !DILocation(line: 2539, column: 10, scope: !5119)
!5196 = !DILocation(line: 2539, column: 15, scope: !5119)
!5197 = !DILocation(line: 2539, column: 8, scope: !5119)
!5198 = !DILocation(line: 2519, column: 2, scope: !5199)
!5199 = !DILexicalBlockFile(scope: !5120, file: !1, discriminator: 1)
!5200 = !DILocation(line: 2541, column: 1, scope: !515)
!5201 = !DILocalVariable(name: "in", arg: 1, scope: !500, file: !1, line: 2840, type: !80)
!5202 = !DILocation(line: 2840, column: 24, scope: !500)
!5203 = !DILocalVariable(name: "out", scope: !500, file: !1, line: 2842, type: !95)
!5204 = !DILocation(line: 2842, column: 8, scope: !500)
!5205 = !DILocalVariable(name: "d", scope: !500, file: !1, line: 2842, type: !95)
!5206 = !DILocation(line: 2842, column: 14, scope: !500)
!5207 = !DILocalVariable(name: "s", scope: !500, file: !1, line: 2843, type: !80)
!5208 = !DILocation(line: 2843, column: 14, scope: !500)
!5209 = !DILocation(line: 2845, column: 30, scope: !500)
!5210 = !DILocation(line: 2845, column: 23, scope: !500)
!5211 = !DILocation(line: 2845, column: 34, scope: !500)
!5212 = !DILocation(line: 2845, column: 16, scope: !5213)
!5213 = !DILexicalBlockFile(scope: !500, file: !1, discriminator: 1)
!5214 = !DILocation(line: 2845, column: 6, scope: !500)
!5215 = !DILocation(line: 2846, column: 6, scope: !5216)
!5216 = distinct !DILexicalBlock(scope: !500, file: !1, line: 2846, column: 6)
!5217 = !DILocation(line: 2846, column: 10, scope: !5216)
!5218 = !DILocation(line: 2846, column: 6, scope: !500)
!5219 = !DILocation(line: 2847, column: 3, scope: !5216)
!5220 = !DILocation(line: 2848, column: 11, scope: !5221)
!5221 = distinct !DILexicalBlock(scope: !500, file: !1, line: 2848, column: 2)
!5222 = !DILocation(line: 2848, column: 9, scope: !5221)
!5223 = !DILocation(line: 2848, column: 19, scope: !5221)
!5224 = !DILocation(line: 2848, column: 17, scope: !5221)
!5225 = !DILocation(line: 2848, column: 7, scope: !5221)
!5226 = !DILocation(line: 2848, column: 25, scope: !5227)
!5227 = !DILexicalBlockFile(scope: !5228, file: !1, discriminator: 1)
!5228 = distinct !DILexicalBlock(scope: !5221, file: !1, line: 2848, column: 2)
!5229 = !DILocation(line: 2848, column: 24, scope: !5227)
!5230 = !DILocation(line: 2848, column: 27, scope: !5227)
!5231 = !DILocation(line: 2848, column: 2, scope: !5227)
!5232 = !DILocation(line: 2849, column: 7, scope: !5233)
!5233 = distinct !DILexicalBlock(scope: !5234, file: !1, line: 2849, column: 7)
!5234 = distinct !DILexicalBlock(scope: !5228, file: !1, line: 2848, column: 38)
!5235 = !DILocation(line: 2849, column: 12, scope: !5233)
!5236 = !DILocation(line: 2849, column: 19, scope: !5233)
!5237 = !DILocation(line: 2849, column: 22, scope: !5238)
!5238 = !DILexicalBlockFile(scope: !5233, file: !1, discriminator: 1)
!5239 = !DILocation(line: 2849, column: 27, scope: !5238)
!5240 = !DILocation(line: 2849, column: 35, scope: !5238)
!5241 = !DILocation(line: 2849, column: 38, scope: !5242)
!5242 = !DILexicalBlockFile(scope: !5233, file: !1, discriminator: 2)
!5243 = !DILocation(line: 2849, column: 43, scope: !5242)
!5244 = !DILocation(line: 2849, column: 7, scope: !5242)
!5245 = !DILocalVariable(name: "digit1", scope: !5246, file: !1, line: 2851, type: !23)
!5246 = distinct !DILexicalBlock(scope: !5233, file: !1, line: 2849, column: 52)
!5247 = !DILocation(line: 2851, column: 8, scope: !5246)
!5248 = !DILocation(line: 2851, column: 23, scope: !5246)
!5249 = !DILocation(line: 2851, column: 17, scope: !5246)
!5250 = !DILocalVariable(name: "digit2", scope: !5246, file: !1, line: 2852, type: !23)
!5251 = !DILocation(line: 2852, column: 8, scope: !5246)
!5252 = !DILocation(line: 2852, column: 23, scope: !5246)
!5253 = !DILocation(line: 2852, column: 17, scope: !5246)
!5254 = !DILocation(line: 2853, column: 8, scope: !5255)
!5255 = distinct !DILexicalBlock(scope: !5246, file: !1, line: 2853, column: 8)
!5256 = !DILocation(line: 2853, column: 15, scope: !5255)
!5257 = !DILocation(line: 2853, column: 20, scope: !5255)
!5258 = !DILocation(line: 2853, column: 23, scope: !5259)
!5259 = !DILexicalBlockFile(scope: !5255, file: !1, discriminator: 1)
!5260 = !DILocation(line: 2853, column: 30, scope: !5259)
!5261 = !DILocation(line: 2853, column: 8, scope: !5259)
!5262 = !DILocation(line: 2855, column: 7, scope: !5263)
!5263 = distinct !DILexicalBlock(scope: !5255, file: !1, line: 2853, column: 36)
!5264 = !DILocation(line: 2857, column: 14, scope: !5263)
!5265 = !DILocation(line: 2857, column: 21, scope: !5263)
!5266 = !DILocation(line: 2857, column: 29, scope: !5263)
!5267 = !DILocation(line: 2857, column: 27, scope: !5263)
!5268 = !DILocation(line: 2857, column: 12, scope: !5263)
!5269 = !DILocation(line: 2857, column: 7, scope: !5263)
!5270 = !DILocation(line: 2857, column: 10, scope: !5263)
!5271 = !DILocation(line: 2858, column: 5, scope: !5263)
!5272 = !DILocation(line: 2861, column: 3, scope: !5246)
!5273 = !DILocation(line: 2862, column: 12, scope: !5234)
!5274 = !DILocation(line: 2862, column: 10, scope: !5234)
!5275 = !DILocation(line: 2862, column: 5, scope: !5234)
!5276 = !DILocation(line: 2862, column: 8, scope: !5234)
!5277 = !DILocation(line: 2848, column: 2, scope: !5278)
!5278 = !DILexicalBlockFile(scope: !5228, file: !1, discriminator: 2)
!5279 = !DILocation(line: 2864, column: 3, scope: !500)
!5280 = !DILocation(line: 2864, column: 5, scope: !500)
!5281 = !DILocation(line: 2865, column: 10, scope: !500)
!5282 = !DILocation(line: 2865, column: 2, scope: !500)
!5283 = !DILocation(line: 2866, column: 1, scope: !500)
!5284 = !DILocalVariable(name: "s", arg: 1, scope: !506, file: !1, line: 2768, type: !80)
!5285 = !DILocation(line: 2768, column: 27, scope: !506)
!5286 = !DILocalVariable(name: "len", arg: 2, scope: !506, file: !1, line: 2768, type: !45)
!5287 = !DILocation(line: 2768, column: 37, scope: !506)
!5288 = !DILocalVariable(name: "out_len", arg: 3, scope: !506, file: !1, line: 2768, type: !65)
!5289 = !DILocation(line: 2768, column: 50, scope: !506)
!5290 = !DILocalVariable(name: "out", scope: !506, file: !1, line: 2777, type: !95)
!5291 = !DILocation(line: 2777, column: 8, scope: !506)
!5292 = !DILocalVariable(name: "d", scope: !506, file: !1, line: 2777, type: !95)
!5293 = !DILocation(line: 2777, column: 14, scope: !506)
!5294 = !DILocalVariable(name: "src", scope: !506, file: !1, line: 2778, type: !380)
!5295 = !DILocation(line: 2778, column: 23, scope: !506)
!5296 = !DILocation(line: 2778, column: 52, scope: !506)
!5297 = !DILocation(line: 2781, column: 19, scope: !5298)
!5298 = distinct !DILexicalBlock(scope: !506, file: !1, line: 2781, column: 6)
!5299 = !DILocation(line: 2781, column: 6, scope: !5298)
!5300 = !DILocation(line: 2781, column: 30, scope: !5298)
!5301 = !DILocation(line: 2781, column: 6, scope: !506)
!5302 = !DILocalVariable(name: "i", scope: !5303, file: !1, line: 2782, type: !13)
!5303 = distinct !DILexicalBlock(scope: !5298, file: !1, line: 2781, column: 36)
!5304 = !DILocation(line: 2782, column: 12, scope: !5303)
!5305 = !DILocation(line: 2783, column: 3, scope: !5303)
!5306 = !DILocation(line: 2784, column: 10, scope: !5307)
!5307 = distinct !DILexicalBlock(scope: !5303, file: !1, line: 2784, column: 3)
!5308 = !DILocation(line: 2784, column: 8, scope: !5307)
!5309 = !DILocation(line: 2784, column: 15, scope: !5310)
!5310 = !DILexicalBlockFile(scope: !5311, file: !1, discriminator: 1)
!5311 = distinct !DILexicalBlock(scope: !5307, file: !1, line: 2784, column: 3)
!5312 = !DILocation(line: 2784, column: 17, scope: !5310)
!5313 = !DILocation(line: 2784, column: 3, scope: !5310)
!5314 = !DILocation(line: 2785, column: 30, scope: !5311)
!5315 = !DILocation(line: 2785, column: 24, scope: !5311)
!5316 = !DILocation(line: 2785, column: 17, scope: !5311)
!5317 = !DILocation(line: 2785, column: 4, scope: !5311)
!5318 = !DILocation(line: 2785, column: 28, scope: !5311)
!5319 = !DILocation(line: 2784, column: 36, scope: !5320)
!5320 = !DILexicalBlockFile(scope: !5311, file: !1, discriminator: 2)
!5321 = !DILocation(line: 2784, column: 3, scope: !5320)
!5322 = !DILocation(line: 2786, column: 2, scope: !5303)
!5323 = !DILocation(line: 2790, column: 23, scope: !506)
!5324 = !DILocation(line: 2790, column: 29, scope: !506)
!5325 = !DILocation(line: 2790, column: 33, scope: !506)
!5326 = !DILocation(line: 2790, column: 27, scope: !506)
!5327 = !DILocation(line: 2790, column: 37, scope: !506)
!5328 = !DILocation(line: 2790, column: 16, scope: !506)
!5329 = !DILocation(line: 2790, column: 6, scope: !506)
!5330 = !DILocation(line: 2791, column: 6, scope: !5331)
!5331 = distinct !DILexicalBlock(scope: !506, file: !1, line: 2791, column: 6)
!5332 = !DILocation(line: 2791, column: 10, scope: !5331)
!5333 = !DILocation(line: 2791, column: 6, scope: !506)
!5334 = !DILocation(line: 2792, column: 4, scope: !5335)
!5335 = distinct !DILexicalBlock(scope: !5331, file: !1, line: 2791, column: 19)
!5336 = !DILocation(line: 2792, column: 12, scope: !5335)
!5337 = !DILocation(line: 2793, column: 3, scope: !5335)
!5338 = !DILocation(line: 2795, column: 6, scope: !506)
!5339 = !DILocation(line: 2795, column: 4, scope: !506)
!5340 = !DILocation(line: 2797, column: 2, scope: !506)
!5341 = !DILocation(line: 2797, column: 9, scope: !5342)
!5342 = !DILexicalBlockFile(scope: !506, file: !1, discriminator: 1)
!5343 = !DILocation(line: 2797, column: 13, scope: !5342)
!5344 = !DILocation(line: 2797, column: 2, scope: !5342)
!5345 = !DILocalVariable(name: "v", scope: !5346, file: !1, line: 2799, type: !23)
!5346 = distinct !DILexicalBlock(scope: !506, file: !1, line: 2797, column: 18)
!5347 = !DILocation(line: 2799, column: 7, scope: !5346)
!5348 = !DILocalVariable(name: "group_size", scope: !5346, file: !1, line: 2800, type: !23)
!5349 = !DILocation(line: 2800, column: 7, scope: !5346)
!5350 = !DILocation(line: 2801, column: 3, scope: !5346)
!5351 = !DILocation(line: 2801, column: 10, scope: !5352)
!5352 = !DILexicalBlockFile(scope: !5346, file: !1, discriminator: 1)
!5353 = !DILocation(line: 2801, column: 21, scope: !5352)
!5354 = !DILocation(line: 2801, column: 25, scope: !5352)
!5355 = !DILocation(line: 2801, column: 28, scope: !5356)
!5356 = !DILexicalBlockFile(scope: !5346, file: !1, discriminator: 2)
!5357 = !DILocation(line: 2801, column: 32, scope: !5356)
!5358 = !DILocation(line: 2801, column: 3, scope: !5359)
!5359 = !DILexicalBlockFile(scope: !5346, file: !1, discriminator: 3)
!5360 = !DILocation(line: 2803, column: 9, scope: !5361)
!5361 = distinct !DILexicalBlock(scope: !5362, file: !1, line: 2803, column: 8)
!5362 = distinct !DILexicalBlock(scope: !5346, file: !1, line: 2801, column: 37)
!5363 = !DILocation(line: 2803, column: 8, scope: !5361)
!5364 = !DILocation(line: 2803, column: 13, scope: !5361)
!5365 = !DILocation(line: 2803, column: 20, scope: !5361)
!5366 = !DILocation(line: 2803, column: 24, scope: !5367)
!5367 = !DILexicalBlockFile(scope: !5361, file: !1, discriminator: 1)
!5368 = !DILocation(line: 2803, column: 23, scope: !5367)
!5369 = !DILocation(line: 2803, column: 28, scope: !5367)
!5370 = !DILocation(line: 2803, column: 8, scope: !5367)
!5371 = !DILocation(line: 2804, column: 9, scope: !5372)
!5372 = distinct !DILexicalBlock(scope: !5361, file: !1, line: 2803, column: 36)
!5373 = !DILocation(line: 2805, column: 5, scope: !5372)
!5374 = !DILocation(line: 2808, column: 9, scope: !5375)
!5375 = distinct !DILexicalBlock(scope: !5362, file: !1, line: 2808, column: 8)
!5376 = !DILocation(line: 2808, column: 8, scope: !5375)
!5377 = !DILocation(line: 2808, column: 13, scope: !5375)
!5378 = !DILocation(line: 2808, column: 19, scope: !5375)
!5379 = !DILocation(line: 2808, column: 23, scope: !5380)
!5380 = !DILexicalBlockFile(scope: !5375, file: !1, discriminator: 1)
!5381 = !DILocation(line: 2808, column: 22, scope: !5380)
!5382 = !DILocation(line: 2808, column: 27, scope: !5380)
!5383 = !DILocation(line: 2809, column: 8, scope: !5375)
!5384 = !DILocation(line: 2809, column: 25, scope: !5380)
!5385 = !DILocation(line: 2809, column: 24, scope: !5380)
!5386 = !DILocation(line: 2809, column: 11, scope: !5380)
!5387 = !DILocation(line: 2809, column: 30, scope: !5380)
!5388 = !DILocation(line: 2808, column: 8, scope: !5389)
!5389 = !DILexicalBlockFile(scope: !5362, file: !1, discriminator: 2)
!5390 = !DILocation(line: 2810, column: 8, scope: !5391)
!5391 = distinct !DILexicalBlock(scope: !5375, file: !1, line: 2809, column: 39)
!5392 = !DILocation(line: 2811, column: 8, scope: !5391)
!5393 = !DILocation(line: 2812, column: 5, scope: !5391)
!5394 = !DILocation(line: 2814, column: 6, scope: !5362)
!5395 = !DILocation(line: 2815, column: 26, scope: !5362)
!5396 = !DILocation(line: 2815, column: 22, scope: !5362)
!5397 = !DILocation(line: 2815, column: 9, scope: !5362)
!5398 = !DILocation(line: 2815, column: 6, scope: !5362)
!5399 = !DILocation(line: 2816, column: 8, scope: !5362)
!5400 = !DILocation(line: 2817, column: 14, scope: !5362)
!5401 = !DILocation(line: 2801, column: 3, scope: !5402)
!5402 = !DILexicalBlockFile(scope: !5346, file: !1, discriminator: 4)
!5403 = !DILocation(line: 2820, column: 18, scope: !5346)
!5404 = !DILocation(line: 2820, column: 16, scope: !5346)
!5405 = !DILocation(line: 2820, column: 11, scope: !5346)
!5406 = !DILocation(line: 2820, column: 5, scope: !5346)
!5407 = !DILocation(line: 2822, column: 11, scope: !5346)
!5408 = !DILocation(line: 2822, column: 3, scope: !5346)
!5409 = !DILocation(line: 2823, column: 18, scope: !5410)
!5410 = distinct !DILexicalBlock(scope: !5346, file: !1, line: 2822, column: 23)
!5411 = !DILocation(line: 2823, column: 20, scope: !5410)
!5412 = !DILocation(line: 2823, column: 11, scope: !5410)
!5413 = !DILocation(line: 2823, column: 16, scope: !5410)
!5414 = !DILocation(line: 2825, column: 19, scope: !5410)
!5415 = !DILocation(line: 2825, column: 21, scope: !5410)
!5416 = !DILocation(line: 2825, column: 27, scope: !5410)
!5417 = !DILocation(line: 2825, column: 18, scope: !5410)
!5418 = !DILocation(line: 2825, column: 11, scope: !5410)
!5419 = !DILocation(line: 2825, column: 16, scope: !5410)
!5420 = !DILocation(line: 2827, column: 19, scope: !5410)
!5421 = !DILocation(line: 2827, column: 21, scope: !5410)
!5422 = !DILocation(line: 2827, column: 28, scope: !5410)
!5423 = !DILocation(line: 2827, column: 18, scope: !5410)
!5424 = !DILocation(line: 2827, column: 11, scope: !5410)
!5425 = !DILocation(line: 2827, column: 16, scope: !5410)
!5426 = !DILocation(line: 2828, column: 4, scope: !5410)
!5427 = !DILocation(line: 2830, column: 4, scope: !5410)
!5428 = !DILocation(line: 2832, column: 8, scope: !5346)
!5429 = !DILocation(line: 2832, column: 19, scope: !5346)
!5430 = !DILocation(line: 2832, column: 23, scope: !5346)
!5431 = !DILocation(line: 2832, column: 5, scope: !5346)
!5432 = !DILocation(line: 2797, column: 2, scope: !5433)
!5433 = !DILexicalBlockFile(scope: !506, file: !1, discriminator: 2)
!5434 = !DILocation(line: 2835, column: 13, scope: !506)
!5435 = !DILocation(line: 2835, column: 17, scope: !506)
!5436 = !DILocation(line: 2835, column: 15, scope: !506)
!5437 = !DILocation(line: 2835, column: 3, scope: !506)
!5438 = !DILocation(line: 2835, column: 11, scope: !506)
!5439 = !DILocation(line: 2836, column: 10, scope: !506)
!5440 = !DILocation(line: 2836, column: 2, scope: !506)
!5441 = !DILocation(line: 2837, column: 1, scope: !506)
!5442 = !DILocalVariable(name: "c", arg: 1, scope: !503, file: !1, line: 2869, type: !23)
!5443 = !DILocation(line: 2869, column: 11, scope: !503)
!5444 = !DILocation(line: 2871, column: 6, scope: !5445)
!5445 = distinct !DILexicalBlock(scope: !503, file: !1, line: 2871, column: 6)
!5446 = !DILocation(line: 2871, column: 8, scope: !5445)
!5447 = !DILocation(line: 2871, column: 15, scope: !5445)
!5448 = !DILocation(line: 2871, column: 18, scope: !5449)
!5449 = !DILexicalBlockFile(scope: !5445, file: !1, discriminator: 1)
!5450 = !DILocation(line: 2871, column: 20, scope: !5449)
!5451 = !DILocation(line: 2871, column: 6, scope: !5449)
!5452 = !DILocation(line: 2872, column: 11, scope: !5445)
!5453 = !DILocation(line: 2872, column: 13, scope: !5445)
!5454 = !DILocation(line: 2872, column: 3, scope: !5445)
!5455 = !DILocation(line: 2873, column: 11, scope: !5456)
!5456 = distinct !DILexicalBlock(scope: !5445, file: !1, line: 2873, column: 11)
!5457 = !DILocation(line: 2873, column: 13, scope: !5456)
!5458 = !DILocation(line: 2873, column: 20, scope: !5456)
!5459 = !DILocation(line: 2873, column: 23, scope: !5460)
!5460 = !DILexicalBlockFile(scope: !5456, file: !1, discriminator: 1)
!5461 = !DILocation(line: 2873, column: 25, scope: !5460)
!5462 = !DILocation(line: 2873, column: 11, scope: !5460)
!5463 = !DILocation(line: 2874, column: 11, scope: !5456)
!5464 = !DILocation(line: 2874, column: 13, scope: !5456)
!5465 = !DILocation(line: 2874, column: 19, scope: !5456)
!5466 = !DILocation(line: 2874, column: 3, scope: !5456)
!5467 = !DILocation(line: 2875, column: 11, scope: !5468)
!5468 = distinct !DILexicalBlock(scope: !5456, file: !1, line: 2875, column: 11)
!5469 = !DILocation(line: 2875, column: 13, scope: !5468)
!5470 = !DILocation(line: 2875, column: 20, scope: !5468)
!5471 = !DILocation(line: 2875, column: 23, scope: !5472)
!5472 = !DILexicalBlockFile(scope: !5468, file: !1, discriminator: 1)
!5473 = !DILocation(line: 2875, column: 25, scope: !5472)
!5474 = !DILocation(line: 2875, column: 11, scope: !5472)
!5475 = !DILocation(line: 2876, column: 11, scope: !5468)
!5476 = !DILocation(line: 2876, column: 13, scope: !5468)
!5477 = !DILocation(line: 2876, column: 19, scope: !5468)
!5478 = !DILocation(line: 2876, column: 3, scope: !5468)
!5479 = !DILocation(line: 2878, column: 3, scope: !5468)
!5480 = !DILocation(line: 2879, column: 1, scope: !503)
!5481 = !DILocalVariable(name: "a", arg: 1, scope: !519, file: !1, line: 1163, type: !4)
!5482 = !DILocation(line: 1163, column: 36, scope: !519)
!5483 = !DILocalVariable(name: "tar", arg: 2, scope: !519, file: !1, line: 1163, type: !291)
!5484 = !DILocation(line: 1163, column: 51, scope: !519)
!5485 = !DILocalVariable(name: "entry", arg: 3, scope: !519, file: !1, line: 1164, type: !30)
!5486 = !DILocation(line: 1164, column: 27, scope: !519)
!5487 = !DILocalVariable(name: "h", arg: 4, scope: !519, file: !1, line: 1164, type: !43)
!5488 = !DILocation(line: 1164, column: 46, scope: !519)
!5489 = !DILocalVariable(name: "header", scope: !519, file: !1, line: 1166, type: !336)
!5490 = !DILocation(line: 1166, column: 43, scope: !519)
!5491 = !DILocalVariable(name: "tartype", scope: !519, file: !1, line: 1167, type: !82)
!5492 = !DILocation(line: 1167, column: 7, scope: !519)
!5493 = !DILocalVariable(name: "err", scope: !519, file: !1, line: 1168, type: !23)
!5494 = !DILocation(line: 1168, column: 10, scope: !519)
!5495 = !DILocation(line: 1170, column: 54, scope: !519)
!5496 = !DILocation(line: 1170, column: 11, scope: !519)
!5497 = !DILocation(line: 1170, column: 9, scope: !519)
!5498 = !DILocation(line: 1171, column: 6, scope: !5499)
!5499 = distinct !DILexicalBlock(scope: !519, file: !1, line: 1171, column: 6)
!5500 = !DILocation(line: 1171, column: 14, scope: !5499)
!5501 = !DILocation(line: 1171, column: 6, scope: !519)
!5502 = !DILocation(line: 1172, column: 3, scope: !5499)
!5503 = !DILocation(line: 1175, column: 3, scope: !5499)
!5504 = !DILocation(line: 1178, column: 25, scope: !519)
!5505 = !DILocation(line: 1179, column: 20, scope: !519)
!5506 = !DILocation(line: 1179, column: 28, scope: !519)
!5507 = !DILocation(line: 1179, column: 11, scope: !519)
!5508 = !DILocation(line: 1179, column: 3, scope: !519)
!5509 = !DILocation(line: 1178, column: 2, scope: !519)
!5510 = !DILocation(line: 1180, column: 24, scope: !519)
!5511 = !DILocation(line: 1180, column: 40, scope: !519)
!5512 = !DILocation(line: 1180, column: 48, scope: !519)
!5513 = !DILocation(line: 1180, column: 31, scope: !519)
!5514 = !DILocation(line: 1180, column: 2, scope: !5515)
!5515 = !DILexicalBlockFile(scope: !519, file: !1, discriminator: 1)
!5516 = !DILocation(line: 1181, column: 24, scope: !519)
!5517 = !DILocation(line: 1181, column: 40, scope: !519)
!5518 = !DILocation(line: 1181, column: 48, scope: !519)
!5519 = !DILocation(line: 1181, column: 31, scope: !519)
!5520 = !DILocation(line: 1181, column: 2, scope: !5515)
!5521 = !DILocation(line: 1182, column: 40, scope: !519)
!5522 = !DILocation(line: 1182, column: 48, scope: !519)
!5523 = !DILocation(line: 1182, column: 31, scope: !519)
!5524 = !DILocation(line: 1182, column: 2, scope: !519)
!5525 = !DILocation(line: 1182, column: 7, scope: !519)
!5526 = !DILocation(line: 1182, column: 29, scope: !519)
!5527 = !DILocation(line: 1183, column: 6, scope: !5528)
!5528 = distinct !DILexicalBlock(scope: !519, file: !1, line: 1183, column: 6)
!5529 = !DILocation(line: 1183, column: 11, scope: !5528)
!5530 = !DILocation(line: 1183, column: 33, scope: !5528)
!5531 = !DILocation(line: 1183, column: 6, scope: !519)
!5532 = !DILocation(line: 1184, column: 3, scope: !5533)
!5533 = distinct !DILexicalBlock(scope: !5528, file: !1, line: 1183, column: 38)
!5534 = !DILocation(line: 1184, column: 8, scope: !5533)
!5535 = !DILocation(line: 1184, column: 30, scope: !5533)
!5536 = !DILocation(line: 1185, column: 22, scope: !5533)
!5537 = !DILocation(line: 1185, column: 25, scope: !5533)
!5538 = !DILocation(line: 1185, column: 3, scope: !5533)
!5539 = !DILocation(line: 1187, column: 3, scope: !5533)
!5540 = !DILocation(line: 1189, column: 6, scope: !5541)
!5541 = distinct !DILexicalBlock(scope: !519, file: !1, line: 1189, column: 6)
!5542 = !DILocation(line: 1189, column: 11, scope: !5541)
!5543 = !DILocation(line: 1189, column: 33, scope: !5541)
!5544 = !DILocation(line: 1189, column: 6, scope: !519)
!5545 = !DILocation(line: 1191, column: 3, scope: !5546)
!5546 = distinct !DILexicalBlock(scope: !5541, file: !1, line: 1189, column: 47)
!5547 = !DILocation(line: 1191, column: 8, scope: !5546)
!5548 = !DILocation(line: 1191, column: 30, scope: !5546)
!5549 = !DILocation(line: 1192, column: 22, scope: !5546)
!5550 = !DILocation(line: 1192, column: 25, scope: !5546)
!5551 = !DILocation(line: 1192, column: 3, scope: !5546)
!5552 = !DILocation(line: 1194, column: 3, scope: !5546)
!5553 = !DILocation(line: 1196, column: 18, scope: !519)
!5554 = !DILocation(line: 1196, column: 23, scope: !519)
!5555 = !DILocation(line: 1196, column: 2, scope: !519)
!5556 = !DILocation(line: 1196, column: 7, scope: !519)
!5557 = !DILocation(line: 1196, column: 16, scope: !519)
!5558 = !DILocation(line: 1197, column: 25, scope: !519)
!5559 = !DILocation(line: 1197, column: 32, scope: !519)
!5560 = !DILocation(line: 1197, column: 37, scope: !519)
!5561 = !DILocation(line: 1197, column: 2, scope: !519)
!5562 = !DILocation(line: 1198, column: 26, scope: !519)
!5563 = !DILocation(line: 1198, column: 42, scope: !519)
!5564 = !DILocation(line: 1198, column: 50, scope: !519)
!5565 = !DILocation(line: 1198, column: 33, scope: !519)
!5566 = !DILocation(line: 1198, column: 2, scope: !5515)
!5567 = !DILocation(line: 1201, column: 12, scope: !519)
!5568 = !DILocation(line: 1201, column: 20, scope: !519)
!5569 = !DILocation(line: 1201, column: 10, scope: !519)
!5570 = !DILocation(line: 1203, column: 10, scope: !519)
!5571 = !DILocation(line: 1203, column: 2, scope: !519)
!5572 = !DILocation(line: 1205, column: 37, scope: !5573)
!5573 = distinct !DILexicalBlock(scope: !5574, file: !1, line: 1205, column: 7)
!5574 = distinct !DILexicalBlock(scope: !519, file: !1, line: 1203, column: 19)
!5575 = !DILocation(line: 1205, column: 44, scope: !5573)
!5576 = !DILocation(line: 1205, column: 49, scope: !5573)
!5577 = !DILocation(line: 1205, column: 64, scope: !5573)
!5578 = !DILocation(line: 1206, column: 7, scope: !5573)
!5579 = !DILocation(line: 1206, column: 47, scope: !5573)
!5580 = !DILocation(line: 1206, column: 52, scope: !5573)
!5581 = !DILocation(line: 1205, column: 7, scope: !5573)
!5582 = !DILocation(line: 1206, column: 59, scope: !5573)
!5583 = !DILocation(line: 1205, column: 7, scope: !5574)
!5584 = !DILocation(line: 1207, column: 38, scope: !5585)
!5585 = distinct !DILexicalBlock(scope: !5573, file: !1, line: 1206, column: 65)
!5586 = !DILocation(line: 1207, column: 41, scope: !5585)
!5587 = !DILocation(line: 1207, column: 46, scope: !5585)
!5588 = !DILocation(line: 1207, column: 10, scope: !5585)
!5589 = !DILocation(line: 1207, column: 8, scope: !5585)
!5590 = !DILocation(line: 1209, column: 8, scope: !5591)
!5591 = distinct !DILexicalBlock(scope: !5585, file: !1, line: 1209, column: 8)
!5592 = !DILocation(line: 1209, column: 12, scope: !5591)
!5593 = !DILocation(line: 1209, column: 8, scope: !5585)
!5594 = !DILocation(line: 1210, column: 13, scope: !5591)
!5595 = !DILocation(line: 1210, column: 5, scope: !5591)
!5596 = !DILocation(line: 1211, column: 3, scope: !5585)
!5597 = !DILocation(line: 1221, column: 26, scope: !5598)
!5598 = distinct !DILexicalBlock(scope: !5574, file: !1, line: 1221, column: 7)
!5599 = !DILocation(line: 1221, column: 7, scope: !5598)
!5600 = !DILocation(line: 1221, column: 33, scope: !5598)
!5601 = !DILocation(line: 1221, column: 7, scope: !5574)
!5602 = !DILocation(line: 1222, column: 31, scope: !5598)
!5603 = !DILocation(line: 1222, column: 4, scope: !5598)
!5604 = !DILocation(line: 1237, column: 26, scope: !5605)
!5605 = distinct !DILexicalBlock(scope: !5574, file: !1, line: 1237, column: 7)
!5606 = !DILocation(line: 1237, column: 7, scope: !5605)
!5607 = !DILocation(line: 1237, column: 33, scope: !5605)
!5608 = !DILocation(line: 1237, column: 7, scope: !5574)
!5609 = !DILocation(line: 1239, column: 3, scope: !5610)
!5610 = distinct !DILexicalBlock(scope: !5605, file: !1, line: 1237, column: 39)
!5611 = !DILocation(line: 1239, column: 15, scope: !5612)
!5612 = !DILexicalBlockFile(scope: !5613, file: !1, discriminator: 1)
!5613 = distinct !DILexicalBlock(scope: !5605, file: !1, line: 1239, column: 15)
!5614 = !DILocation(line: 1239, column: 18, scope: !5612)
!5615 = !DILocation(line: 1239, column: 26, scope: !5612)
!5616 = !DILocation(line: 1240, column: 7, scope: !5613)
!5617 = !DILocation(line: 1242, column: 3, scope: !5618)
!5618 = distinct !DILexicalBlock(scope: !5613, file: !1, line: 1240, column: 46)
!5619 = !DILocation(line: 1242, column: 14, scope: !5620)
!5620 = !DILexicalBlockFile(scope: !5621, file: !1, discriminator: 1)
!5621 = distinct !DILexicalBlock(scope: !5613, file: !1, line: 1242, column: 14)
!5622 = !DILocation(line: 1242, column: 17, scope: !5620)
!5623 = !DILocation(line: 1242, column: 25, scope: !5620)
!5624 = !DILocation(line: 1242, column: 40, scope: !5620)
!5625 = !DILocation(line: 1243, column: 7, scope: !5621)
!5626 = !DILocation(line: 1243, column: 10, scope: !5620)
!5627 = !DILocation(line: 1243, column: 13, scope: !5620)
!5628 = !DILocation(line: 1243, column: 21, scope: !5620)
!5629 = !DILocation(line: 1243, column: 36, scope: !5620)
!5630 = !DILocation(line: 1242, column: 14, scope: !5631)
!5631 = !DILexicalBlockFile(scope: !5613, file: !1, discriminator: 2)
!5632 = !DILocation(line: 1246, column: 27, scope: !5633)
!5633 = distinct !DILexicalBlock(scope: !5621, file: !1, line: 1244, column: 3)
!5634 = !DILocation(line: 1246, column: 4, scope: !5633)
!5635 = !DILocation(line: 1247, column: 4, scope: !5633)
!5636 = !DILocation(line: 1247, column: 9, scope: !5633)
!5637 = !DILocation(line: 1247, column: 31, scope: !5633)
!5638 = !DILocation(line: 1248, column: 3, scope: !5633)
!5639 = !DILocation(line: 1248, column: 42, scope: !5640)
!5640 = !DILexicalBlockFile(scope: !5641, file: !1, discriminator: 1)
!5641 = distinct !DILexicalBlock(scope: !5621, file: !1, line: 1248, column: 14)
!5642 = !DILocation(line: 1248, column: 14, scope: !5640)
!5643 = !DILocation(line: 1248, column: 49, scope: !5640)
!5644 = !DILocation(line: 1255, column: 27, scope: !5645)
!5645 = distinct !DILexicalBlock(scope: !5641, file: !1, line: 1248, column: 55)
!5646 = !DILocation(line: 1255, column: 4, scope: !5645)
!5647 = !DILocation(line: 1256, column: 4, scope: !5645)
!5648 = !DILocation(line: 1256, column: 9, scope: !5645)
!5649 = !DILocation(line: 1256, column: 31, scope: !5645)
!5650 = !DILocation(line: 1257, column: 3, scope: !5645)
!5651 = !DILocation(line: 1268, column: 3, scope: !5574)
!5652 = !DILocation(line: 1270, column: 30, scope: !5574)
!5653 = !DILocation(line: 1270, column: 3, scope: !5574)
!5654 = !DILocation(line: 1271, column: 26, scope: !5574)
!5655 = !DILocation(line: 1271, column: 3, scope: !5574)
!5656 = !DILocation(line: 1272, column: 3, scope: !5574)
!5657 = !DILocation(line: 1272, column: 8, scope: !5574)
!5658 = !DILocation(line: 1272, column: 30, scope: !5574)
!5659 = !DILocation(line: 1273, column: 36, scope: !5660)
!5660 = distinct !DILexicalBlock(scope: !5574, file: !1, line: 1273, column: 7)
!5661 = !DILocation(line: 1273, column: 43, scope: !5660)
!5662 = !DILocation(line: 1273, column: 48, scope: !5660)
!5663 = !DILocation(line: 1273, column: 63, scope: !5660)
!5664 = !DILocation(line: 1274, column: 7, scope: !5660)
!5665 = !DILocation(line: 1274, column: 47, scope: !5660)
!5666 = !DILocation(line: 1274, column: 52, scope: !5660)
!5667 = !DILocation(line: 1273, column: 7, scope: !5660)
!5668 = !DILocation(line: 1274, column: 59, scope: !5660)
!5669 = !DILocation(line: 1273, column: 7, scope: !5574)
!5670 = !DILocation(line: 1275, column: 38, scope: !5671)
!5671 = distinct !DILexicalBlock(scope: !5660, file: !1, line: 1274, column: 65)
!5672 = !DILocation(line: 1275, column: 41, scope: !5671)
!5673 = !DILocation(line: 1275, column: 46, scope: !5671)
!5674 = !DILocation(line: 1275, column: 10, scope: !5671)
!5675 = !DILocation(line: 1275, column: 8, scope: !5671)
!5676 = !DILocation(line: 1277, column: 8, scope: !5677)
!5677 = distinct !DILexicalBlock(scope: !5671, file: !1, line: 1277, column: 8)
!5678 = !DILocation(line: 1277, column: 12, scope: !5677)
!5679 = !DILocation(line: 1277, column: 8, scope: !5671)
!5680 = !DILocation(line: 1278, column: 13, scope: !5677)
!5681 = !DILocation(line: 1278, column: 5, scope: !5677)
!5682 = !DILocation(line: 1279, column: 3, scope: !5671)
!5683 = !DILocation(line: 1280, column: 3, scope: !5574)
!5684 = !DILocation(line: 1282, column: 30, scope: !5574)
!5685 = !DILocation(line: 1282, column: 3, scope: !5574)
!5686 = !DILocation(line: 1283, column: 26, scope: !5574)
!5687 = !DILocation(line: 1283, column: 3, scope: !5574)
!5688 = !DILocation(line: 1284, column: 3, scope: !5574)
!5689 = !DILocation(line: 1284, column: 8, scope: !5574)
!5690 = !DILocation(line: 1284, column: 30, scope: !5574)
!5691 = !DILocation(line: 1285, column: 3, scope: !5574)
!5692 = !DILocation(line: 1287, column: 30, scope: !5574)
!5693 = !DILocation(line: 1287, column: 3, scope: !5574)
!5694 = !DILocation(line: 1288, column: 26, scope: !5574)
!5695 = !DILocation(line: 1288, column: 3, scope: !5574)
!5696 = !DILocation(line: 1289, column: 3, scope: !5574)
!5697 = !DILocation(line: 1289, column: 8, scope: !5574)
!5698 = !DILocation(line: 1289, column: 30, scope: !5574)
!5699 = !DILocation(line: 1290, column: 3, scope: !5574)
!5700 = !DILocation(line: 1292, column: 30, scope: !5574)
!5701 = !DILocation(line: 1292, column: 3, scope: !5574)
!5702 = !DILocation(line: 1293, column: 26, scope: !5574)
!5703 = !DILocation(line: 1293, column: 3, scope: !5574)
!5704 = !DILocation(line: 1294, column: 3, scope: !5574)
!5705 = !DILocation(line: 1294, column: 8, scope: !5574)
!5706 = !DILocation(line: 1294, column: 30, scope: !5574)
!5707 = !DILocation(line: 1295, column: 3, scope: !5574)
!5708 = !DILocation(line: 1297, column: 30, scope: !5574)
!5709 = !DILocation(line: 1297, column: 3, scope: !5574)
!5710 = !DILocation(line: 1298, column: 26, scope: !5574)
!5711 = !DILocation(line: 1298, column: 3, scope: !5574)
!5712 = !DILocation(line: 1299, column: 3, scope: !5574)
!5713 = !DILocation(line: 1299, column: 8, scope: !5574)
!5714 = !DILocation(line: 1299, column: 30, scope: !5574)
!5715 = !DILocation(line: 1300, column: 3, scope: !5574)
!5716 = !DILocation(line: 1307, column: 30, scope: !5574)
!5717 = !DILocation(line: 1307, column: 3, scope: !5574)
!5718 = !DILocation(line: 1308, column: 3, scope: !5574)
!5719 = !DILocation(line: 1316, column: 3, scope: !5574)
!5720 = !DILocation(line: 1321, column: 30, scope: !5574)
!5721 = !DILocation(line: 1321, column: 3, scope: !5574)
!5722 = !DILocation(line: 1322, column: 3, scope: !5574)
!5723 = !DILocation(line: 1335, column: 3, scope: !5574)
!5724 = !DILocation(line: 1335, column: 8, scope: !5574)
!5725 = !DILocation(line: 1335, column: 23, scope: !5574)
!5726 = !DILocation(line: 1342, column: 30, scope: !5574)
!5727 = !DILocation(line: 1342, column: 3, scope: !5574)
!5728 = !DILocation(line: 1343, column: 3, scope: !5574)
!5729 = !DILocation(line: 1345, column: 10, scope: !519)
!5730 = !DILocation(line: 1345, column: 2, scope: !519)
!5731 = !DILocation(line: 1346, column: 1, scope: !519)
!5732 = !DILocalVariable(name: "a", arg: 1, scope: !425, file: !1, line: 2275, type: !4)
!5733 = !DILocation(line: 2275, column: 42, scope: !425)
!5734 = !DILocalVariable(name: "tar", arg: 2, scope: !425, file: !1, line: 2275, type: !291)
!5735 = !DILocation(line: 2275, column: 57, scope: !425)
!5736 = !DILocalVariable(name: "header", arg: 3, scope: !425, file: !1, line: 2276, type: !386)
!5737 = !DILocation(line: 2276, column: 47, scope: !425)
!5738 = !DILocalVariable(name: "unconsumed", arg: 4, scope: !425, file: !1, line: 2276, type: !65)
!5739 = !DILocation(line: 2276, column: 63, scope: !425)
!5740 = !DILocalVariable(name: "bytes_read", scope: !425, file: !1, line: 2278, type: !38)
!5741 = !DILocation(line: 2278, column: 10, scope: !425)
!5742 = !DILocalVariable(name: "data", scope: !425, file: !1, line: 2279, type: !43)
!5743 = !DILocation(line: 2279, column: 14, scope: !425)
!5744 = !DILocalVariable(name: "ext", scope: !425, file: !1, line: 2285, type: !422)
!5745 = !DILocation(line: 2285, column: 25, scope: !425)
!5746 = !DILocation(line: 2287, column: 27, scope: !5747)
!5747 = distinct !DILexicalBlock(scope: !425, file: !1, line: 2287, column: 6)
!5748 = !DILocation(line: 2287, column: 30, scope: !5747)
!5749 = !DILocation(line: 2287, column: 35, scope: !5747)
!5750 = !DILocation(line: 2287, column: 43, scope: !5747)
!5751 = !DILocation(line: 2287, column: 6, scope: !5747)
!5752 = !DILocation(line: 2287, column: 54, scope: !5747)
!5753 = !DILocation(line: 2287, column: 6, scope: !425)
!5754 = !DILocation(line: 2288, column: 3, scope: !5747)
!5755 = !DILocation(line: 2289, column: 6, scope: !5756)
!5756 = distinct !DILexicalBlock(scope: !425, file: !1, line: 2289, column: 6)
!5757 = !DILocation(line: 2289, column: 14, scope: !5756)
!5758 = !DILocation(line: 2289, column: 28, scope: !5756)
!5759 = !DILocation(line: 2289, column: 6, scope: !425)
!5760 = !DILocation(line: 2290, column: 3, scope: !5756)
!5761 = !DILocation(line: 2292, column: 2, scope: !425)
!5762 = !DILocation(line: 2293, column: 24, scope: !5763)
!5763 = distinct !DILexicalBlock(scope: !425, file: !1, line: 2292, column: 5)
!5764 = !DILocation(line: 2293, column: 27, scope: !5763)
!5765 = !DILocation(line: 2293, column: 3, scope: !5763)
!5766 = !DILocation(line: 2294, column: 31, scope: !5763)
!5767 = !DILocation(line: 2294, column: 10, scope: !5763)
!5768 = !DILocation(line: 2294, column: 8, scope: !5763)
!5769 = !DILocation(line: 2295, column: 7, scope: !5770)
!5770 = distinct !DILexicalBlock(scope: !5763, file: !1, line: 2295, column: 7)
!5771 = !DILocation(line: 2295, column: 18, scope: !5770)
!5772 = !DILocation(line: 2295, column: 7, scope: !5763)
!5773 = !DILocation(line: 2296, column: 4, scope: !5770)
!5774 = !DILocation(line: 2297, column: 7, scope: !5775)
!5775 = distinct !DILexicalBlock(scope: !5763, file: !1, line: 2297, column: 7)
!5776 = !DILocation(line: 2297, column: 18, scope: !5775)
!5777 = !DILocation(line: 2297, column: 7, scope: !5763)
!5778 = !DILocation(line: 2298, column: 23, scope: !5779)
!5779 = distinct !DILexicalBlock(scope: !5775, file: !1, line: 2297, column: 25)
!5780 = !DILocation(line: 2298, column: 26, scope: !5779)
!5781 = !DILocation(line: 2298, column: 4, scope: !5779)
!5782 = !DILocation(line: 2301, column: 4, scope: !5779)
!5783 = !DILocation(line: 2303, column: 4, scope: !5763)
!5784 = !DILocation(line: 2303, column: 15, scope: !5763)
!5785 = !DILocation(line: 2304, column: 34, scope: !5763)
!5786 = !DILocation(line: 2304, column: 9, scope: !5763)
!5787 = !DILocation(line: 2304, column: 7, scope: !5763)
!5788 = !DILocation(line: 2305, column: 28, scope: !5789)
!5789 = distinct !DILexicalBlock(scope: !5763, file: !1, line: 2305, column: 7)
!5790 = !DILocation(line: 2305, column: 31, scope: !5789)
!5791 = !DILocation(line: 2305, column: 36, scope: !5789)
!5792 = !DILocation(line: 2305, column: 41, scope: !5789)
!5793 = !DILocation(line: 2305, column: 7, scope: !5789)
!5794 = !DILocation(line: 2305, column: 53, scope: !5789)
!5795 = !DILocation(line: 2305, column: 7, scope: !5763)
!5796 = !DILocation(line: 2306, column: 4, scope: !5789)
!5797 = !DILocation(line: 2307, column: 2, scope: !5763)
!5798 = !DILocation(line: 2307, column: 11, scope: !5799)
!5799 = !DILexicalBlockFile(scope: !425, file: !1, discriminator: 1)
!5800 = !DILocation(line: 2307, column: 16, scope: !5799)
!5801 = !DILocation(line: 2307, column: 30, scope: !5799)
!5802 = !DILocation(line: 2307, column: 2, scope: !5799)
!5803 = !DILocation(line: 2308, column: 6, scope: !5804)
!5804 = distinct !DILexicalBlock(scope: !425, file: !1, line: 2308, column: 6)
!5805 = !DILocation(line: 2308, column: 11, scope: !5804)
!5806 = !DILocation(line: 2308, column: 23, scope: !5804)
!5807 = !DILocation(line: 2308, column: 6, scope: !425)
!5808 = !DILocation(line: 2309, column: 23, scope: !5804)
!5809 = !DILocation(line: 2309, column: 28, scope: !5804)
!5810 = !DILocation(line: 2309, column: 41, scope: !5804)
!5811 = !DILocation(line: 2309, column: 3, scope: !5804)
!5812 = !DILocation(line: 2309, column: 8, scope: !5804)
!5813 = !DILocation(line: 2309, column: 21, scope: !5804)
!5814 = !DILocation(line: 2310, column: 2, scope: !425)
!5815 = !DILocation(line: 2311, column: 1, scope: !425)
!5816 = !DILocalVariable(name: "a", arg: 1, scope: !522, file: !1, line: 2314, type: !4)
!5817 = !DILocation(line: 2314, column: 43, scope: !522)
!5818 = !DILocalVariable(name: "tar", arg: 2, scope: !522, file: !1, line: 2314, type: !291)
!5819 = !DILocation(line: 2314, column: 58, scope: !522)
!5820 = !DILocalVariable(name: "sparse", arg: 3, scope: !522, file: !1, line: 2315, type: !525)
!5821 = !DILocation(line: 2315, column: 30, scope: !522)
!5822 = !DILocalVariable(name: "length", arg: 4, scope: !522, file: !1, line: 2315, type: !23)
!5823 = !DILocation(line: 2315, column: 42, scope: !522)
!5824 = !DILocation(line: 2317, column: 2, scope: !522)
!5825 = !DILocation(line: 2317, column: 9, scope: !5826)
!5826 = !DILexicalBlockFile(scope: !522, file: !1, discriminator: 1)
!5827 = !DILocation(line: 2317, column: 16, scope: !5826)
!5828 = !DILocation(line: 2317, column: 20, scope: !5826)
!5829 = !DILocation(line: 2317, column: 23, scope: !5830)
!5830 = !DILexicalBlockFile(scope: !522, file: !1, discriminator: 2)
!5831 = !DILocation(line: 2317, column: 31, scope: !5830)
!5832 = !DILocation(line: 2317, column: 41, scope: !5830)
!5833 = !DILocation(line: 2317, column: 2, scope: !5834)
!5834 = !DILexicalBlockFile(scope: !522, file: !1, discriminator: 3)
!5835 = !DILocation(line: 2318, column: 28, scope: !5836)
!5836 = distinct !DILexicalBlock(scope: !5837, file: !1, line: 2318, column: 7)
!5837 = distinct !DILexicalBlock(scope: !522, file: !1, line: 2317, column: 47)
!5838 = !DILocation(line: 2318, column: 31, scope: !5836)
!5839 = !DILocation(line: 2319, column: 16, scope: !5836)
!5840 = !DILocation(line: 2319, column: 24, scope: !5836)
!5841 = !DILocation(line: 2319, column: 7, scope: !5836)
!5842 = !DILocation(line: 2320, column: 16, scope: !5836)
!5843 = !DILocation(line: 2320, column: 24, scope: !5836)
!5844 = !DILocation(line: 2320, column: 7, scope: !5836)
!5845 = !DILocation(line: 2318, column: 7, scope: !5836)
!5846 = !DILocation(line: 2321, column: 7, scope: !5836)
!5847 = !DILocation(line: 2318, column: 7, scope: !5837)
!5848 = !DILocation(line: 2322, column: 4, scope: !5836)
!5849 = !DILocation(line: 2323, column: 9, scope: !5837)
!5850 = !DILocation(line: 2324, column: 9, scope: !5837)
!5851 = !DILocation(line: 2317, column: 2, scope: !5852)
!5852 = !DILexicalBlockFile(scope: !522, file: !1, discriminator: 4)
!5853 = !DILocation(line: 2326, column: 2, scope: !522)
!5854 = !DILocation(line: 2327, column: 1, scope: !522)
!5855 = !DILocalVariable(name: "a", arg: 1, scope: !533, file: !1, line: 2411, type: !4)
!5856 = !DILocation(line: 2411, column: 41, scope: !533)
!5857 = !DILocalVariable(name: "tar", arg: 2, scope: !533, file: !1, line: 2411, type: !291)
!5858 = !DILocation(line: 2411, column: 56, scope: !533)
!5859 = !DILocalVariable(name: "remaining", arg: 3, scope: !533, file: !1, line: 2412, type: !66)
!5860 = !DILocation(line: 2412, column: 14, scope: !533)
!5861 = !DILocalVariable(name: "unconsumed", arg: 4, scope: !533, file: !1, line: 2412, type: !65)
!5862 = !DILocation(line: 2412, column: 33, scope: !533)
!5863 = !DILocalVariable(name: "l", scope: !533, file: !1, line: 2414, type: !52)
!5864 = !DILocation(line: 2414, column: 10, scope: !533)
!5865 = !DILocalVariable(name: "limit", scope: !533, file: !1, line: 2414, type: !52)
!5866 = !DILocation(line: 2414, column: 13, scope: !533)
!5867 = !DILocalVariable(name: "last_digit_limit", scope: !533, file: !1, line: 2414, type: !52)
!5868 = !DILocation(line: 2414, column: 20, scope: !533)
!5869 = !DILocalVariable(name: "p", scope: !533, file: !1, line: 2415, type: !80)
!5870 = !DILocation(line: 2415, column: 14, scope: !533)
!5871 = !DILocalVariable(name: "bytes_read", scope: !533, file: !1, line: 2416, type: !38)
!5872 = !DILocation(line: 2416, column: 10, scope: !533)
!5873 = !DILocalVariable(name: "base", scope: !533, file: !1, line: 2417, type: !23)
!5874 = !DILocation(line: 2417, column: 6, scope: !533)
!5875 = !DILocalVariable(name: "digit", scope: !533, file: !1, line: 2417, type: !23)
!5876 = !DILocation(line: 2417, column: 12, scope: !533)
!5877 = !DILocation(line: 2419, column: 7, scope: !533)
!5878 = !DILocation(line: 2420, column: 22, scope: !533)
!5879 = !DILocation(line: 2420, column: 20, scope: !533)
!5880 = !DILocation(line: 2420, column: 8, scope: !533)
!5881 = !DILocation(line: 2421, column: 33, scope: !533)
!5882 = !DILocation(line: 2421, column: 31, scope: !533)
!5883 = !DILocation(line: 2421, column: 19, scope: !533)
!5884 = !DILocation(line: 2427, column: 2, scope: !533)
!5885 = !DILocation(line: 2428, column: 25, scope: !5886)
!5886 = distinct !DILexicalBlock(scope: !533, file: !1, line: 2427, column: 5)
!5887 = !DILocation(line: 2428, column: 28, scope: !5886)
!5888 = !DILocation(line: 2429, column: 13, scope: !5886)
!5889 = !DILocation(line: 2429, column: 13, scope: !5890)
!5890 = !DILexicalBlockFile(scope: !5886, file: !1, discriminator: 1)
!5891 = !DILocation(line: 2429, column: 13, scope: !5892)
!5892 = !DILexicalBlockFile(scope: !5886, file: !1, discriminator: 2)
!5893 = !DILocation(line: 2429, column: 13, scope: !5894)
!5894 = !DILexicalBlockFile(scope: !5886, file: !1, discriminator: 3)
!5895 = !DILocation(line: 2429, column: 39, scope: !5894)
!5896 = !DILocation(line: 2428, column: 16, scope: !5890)
!5897 = !DILocation(line: 2428, column: 14, scope: !5890)
!5898 = !DILocation(line: 2430, column: 7, scope: !5899)
!5899 = distinct !DILexicalBlock(scope: !5886, file: !1, line: 2430, column: 7)
!5900 = !DILocation(line: 2430, column: 18, scope: !5899)
!5901 = !DILocation(line: 2430, column: 7, scope: !5886)
!5902 = !DILocation(line: 2431, column: 4, scope: !5899)
!5903 = !DILocation(line: 2432, column: 17, scope: !5886)
!5904 = !DILocation(line: 2432, column: 4, scope: !5886)
!5905 = !DILocation(line: 2432, column: 14, scope: !5886)
!5906 = !DILocation(line: 2433, column: 2, scope: !5886)
!5907 = !DILocation(line: 2433, column: 11, scope: !5908)
!5908 = !DILexicalBlockFile(scope: !533, file: !1, discriminator: 1)
!5909 = !DILocation(line: 2433, column: 16, scope: !5908)
!5910 = !DILocation(line: 2433, column: 2, scope: !5908)
!5911 = !DILocation(line: 2435, column: 4, scope: !533)
!5912 = !DILocation(line: 2436, column: 2, scope: !533)
!5913 = !DILocation(line: 2436, column: 9, scope: !5908)
!5914 = !DILocation(line: 2436, column: 20, scope: !5908)
!5915 = !DILocation(line: 2436, column: 2, scope: !5908)
!5916 = !DILocation(line: 2437, column: 8, scope: !5917)
!5917 = distinct !DILexicalBlock(scope: !5918, file: !1, line: 2437, column: 7)
!5918 = distinct !DILexicalBlock(scope: !533, file: !1, line: 2436, column: 25)
!5919 = !DILocation(line: 2437, column: 7, scope: !5917)
!5920 = !DILocation(line: 2437, column: 10, scope: !5917)
!5921 = !DILocation(line: 2437, column: 7, scope: !5918)
!5922 = !DILocation(line: 2438, column: 12, scope: !5917)
!5923 = !DILocation(line: 2438, column: 4, scope: !5917)
!5924 = !DILocation(line: 2439, column: 8, scope: !5925)
!5925 = distinct !DILexicalBlock(scope: !5918, file: !1, line: 2439, column: 7)
!5926 = !DILocation(line: 2439, column: 7, scope: !5925)
!5927 = !DILocation(line: 2439, column: 10, scope: !5925)
!5928 = !DILocation(line: 2439, column: 16, scope: !5925)
!5929 = !DILocation(line: 2439, column: 20, scope: !5930)
!5930 = !DILexicalBlockFile(scope: !5925, file: !1, discriminator: 1)
!5931 = !DILocation(line: 2439, column: 19, scope: !5930)
!5932 = !DILocation(line: 2439, column: 31, scope: !5930)
!5933 = !DILocation(line: 2439, column: 29, scope: !5930)
!5934 = !DILocation(line: 2439, column: 22, scope: !5930)
!5935 = !DILocation(line: 2439, column: 7, scope: !5930)
!5936 = !DILocation(line: 2440, column: 4, scope: !5925)
!5937 = !DILocation(line: 2441, column: 12, scope: !5918)
!5938 = !DILocation(line: 2441, column: 11, scope: !5918)
!5939 = !DILocation(line: 2441, column: 14, scope: !5918)
!5940 = !DILocation(line: 2441, column: 9, scope: !5918)
!5941 = !DILocation(line: 2442, column: 7, scope: !5942)
!5942 = distinct !DILexicalBlock(scope: !5918, file: !1, line: 2442, column: 7)
!5943 = !DILocation(line: 2442, column: 11, scope: !5942)
!5944 = !DILocation(line: 2442, column: 9, scope: !5942)
!5945 = !DILocation(line: 2442, column: 17, scope: !5942)
!5946 = !DILocation(line: 2442, column: 21, scope: !5947)
!5947 = !DILexicalBlockFile(scope: !5942, file: !1, discriminator: 1)
!5948 = !DILocation(line: 2442, column: 26, scope: !5947)
!5949 = !DILocation(line: 2442, column: 23, scope: !5947)
!5950 = !DILocation(line: 2442, column: 32, scope: !5947)
!5951 = !DILocation(line: 2442, column: 35, scope: !5952)
!5952 = !DILexicalBlockFile(scope: !5942, file: !1, discriminator: 2)
!5953 = !DILocation(line: 2442, column: 43, scope: !5952)
!5954 = !DILocation(line: 2442, column: 41, scope: !5952)
!5955 = !DILocation(line: 2442, column: 7, scope: !5952)
!5956 = !DILocation(line: 2443, column: 6, scope: !5942)
!5957 = !DILocation(line: 2443, column: 4, scope: !5942)
!5958 = !DILocation(line: 2445, column: 9, scope: !5942)
!5959 = !DILocation(line: 2445, column: 13, scope: !5942)
!5960 = !DILocation(line: 2445, column: 11, scope: !5942)
!5961 = !DILocation(line: 2445, column: 21, scope: !5942)
!5962 = !DILocation(line: 2445, column: 19, scope: !5942)
!5963 = !DILocation(line: 2445, column: 6, scope: !5942)
!5964 = !DILocation(line: 2446, column: 4, scope: !5918)
!5965 = !DILocation(line: 2447, column: 13, scope: !5918)
!5966 = !DILocation(line: 2436, column: 2, scope: !5967)
!5967 = !DILexicalBlockFile(scope: !533, file: !1, discriminator: 2)
!5968 = !DILocation(line: 2450, column: 2, scope: !533)
!5969 = !DILocation(line: 2451, column: 1, scope: !533)
!5970 = !DILocalVariable(name: "a", arg: 1, scope: !536, file: !1, line: 2693, type: !4)
!5971 = !DILocation(line: 2693, column: 31, scope: !536)
!5972 = !DILocalVariable(name: "tar", arg: 2, scope: !536, file: !1, line: 2693, type: !291)
!5973 = !DILocation(line: 2693, column: 46, scope: !536)
!5974 = !DILocalVariable(name: "start", arg: 3, scope: !536, file: !1, line: 2693, type: !539)
!5975 = !DILocation(line: 2693, column: 64, scope: !536)
!5976 = !DILocalVariable(name: "limit", arg: 4, scope: !536, file: !1, line: 2694, type: !38)
!5977 = !DILocation(line: 2694, column: 13, scope: !536)
!5978 = !DILocalVariable(name: "unconsumed", arg: 5, scope: !536, file: !1, line: 2694, type: !65)
!5979 = !DILocation(line: 2694, column: 28, scope: !536)
!5980 = !DILocalVariable(name: "bytes_read", scope: !536, file: !1, line: 2696, type: !38)
!5981 = !DILocation(line: 2696, column: 10, scope: !536)
!5982 = !DILocalVariable(name: "total_size", scope: !536, file: !1, line: 2697, type: !38)
!5983 = !DILocation(line: 2697, column: 10, scope: !536)
!5984 = !DILocalVariable(name: "t", scope: !536, file: !1, line: 2698, type: !43)
!5985 = !DILocation(line: 2698, column: 14, scope: !536)
!5986 = !DILocalVariable(name: "s", scope: !536, file: !1, line: 2699, type: !80)
!5987 = !DILocation(line: 2699, column: 14, scope: !536)
!5988 = !DILocalVariable(name: "p", scope: !536, file: !1, line: 2700, type: !122)
!5989 = !DILocation(line: 2700, column: 8, scope: !536)
!5990 = !DILocation(line: 2702, column: 23, scope: !536)
!5991 = !DILocation(line: 2702, column: 26, scope: !536)
!5992 = !DILocation(line: 2702, column: 2, scope: !536)
!5993 = !DILocation(line: 2704, column: 27, scope: !536)
!5994 = !DILocation(line: 2704, column: 6, scope: !536)
!5995 = !DILocation(line: 2704, column: 4, scope: !536)
!5996 = !DILocation(line: 2705, column: 6, scope: !5997)
!5997 = distinct !DILexicalBlock(scope: !536, file: !1, line: 2705, column: 6)
!5998 = !DILocation(line: 2705, column: 17, scope: !5997)
!5999 = !DILocation(line: 2705, column: 6, scope: !536)
!6000 = !DILocation(line: 2706, column: 3, scope: !5997)
!6001 = !DILocation(line: 2707, column: 6, scope: !536)
!6002 = !DILocation(line: 2707, column: 4, scope: !536)
!6003 = !DILocation(line: 2708, column: 13, scope: !536)
!6004 = !DILocation(line: 2708, column: 22, scope: !536)
!6005 = !DILocation(line: 2708, column: 6, scope: !536)
!6006 = !DILocation(line: 2708, column: 4, scope: !536)
!6007 = !DILocation(line: 2710, column: 6, scope: !6008)
!6008 = distinct !DILexicalBlock(scope: !536, file: !1, line: 2710, column: 6)
!6009 = !DILocation(line: 2710, column: 8, scope: !6008)
!6010 = !DILocation(line: 2710, column: 6, scope: !536)
!6011 = !DILocation(line: 2711, column: 35, scope: !6012)
!6012 = distinct !DILexicalBlock(scope: !6008, file: !1, line: 2710, column: 17)
!6013 = !DILocation(line: 2711, column: 18, scope: !6012)
!6014 = !DILocation(line: 2711, column: 40, scope: !6012)
!6015 = !DILocation(line: 2711, column: 38, scope: !6012)
!6016 = !DILocation(line: 2711, column: 14, scope: !6012)
!6017 = !DILocation(line: 2712, column: 7, scope: !6018)
!6018 = distinct !DILexicalBlock(scope: !6012, file: !1, line: 2712, column: 7)
!6019 = !DILocation(line: 2712, column: 20, scope: !6018)
!6020 = !DILocation(line: 2712, column: 18, scope: !6018)
!6021 = !DILocation(line: 2712, column: 7, scope: !6012)
!6022 = !DILocation(line: 2713, column: 23, scope: !6023)
!6023 = distinct !DILexicalBlock(scope: !6018, file: !1, line: 2712, column: 27)
!6024 = !DILocation(line: 2713, column: 26, scope: !6023)
!6025 = !DILocation(line: 2713, column: 4, scope: !6023)
!6026 = !DILocation(line: 2716, column: 4, scope: !6023)
!6027 = !DILocation(line: 2718, column: 17, scope: !6012)
!6028 = !DILocation(line: 2718, column: 4, scope: !6012)
!6029 = !DILocation(line: 2718, column: 15, scope: !6012)
!6030 = !DILocation(line: 2719, column: 12, scope: !6012)
!6031 = !DILocation(line: 2719, column: 4, scope: !6012)
!6032 = !DILocation(line: 2719, column: 10, scope: !6012)
!6033 = !DILocation(line: 2720, column: 11, scope: !6012)
!6034 = !DILocation(line: 2720, column: 3, scope: !6012)
!6035 = !DILocation(line: 2722, column: 16, scope: !536)
!6036 = !DILocation(line: 2722, column: 3, scope: !536)
!6037 = !DILocation(line: 2722, column: 14, scope: !536)
!6038 = !DILocation(line: 2724, column: 2, scope: !536)
!6039 = !DILocation(line: 2725, column: 7, scope: !6040)
!6040 = distinct !DILexicalBlock(scope: !6041, file: !1, line: 2725, column: 7)
!6041 = distinct !DILexicalBlock(scope: !6042, file: !1, line: 2724, column: 11)
!6042 = distinct !DILexicalBlock(scope: !6043, file: !1, line: 2724, column: 2)
!6043 = distinct !DILexicalBlock(scope: !536, file: !1, line: 2724, column: 2)
!6044 = !DILocation(line: 2725, column: 20, scope: !6040)
!6045 = !DILocation(line: 2725, column: 18, scope: !6040)
!6046 = !DILocation(line: 2725, column: 33, scope: !6040)
!6047 = !DILocation(line: 2725, column: 31, scope: !6040)
!6048 = !DILocation(line: 2725, column: 7, scope: !6041)
!6049 = !DILocation(line: 2726, column: 23, scope: !6050)
!6050 = distinct !DILexicalBlock(scope: !6040, file: !1, line: 2725, column: 40)
!6051 = !DILocation(line: 2726, column: 26, scope: !6050)
!6052 = !DILocation(line: 2726, column: 4, scope: !6050)
!6053 = !DILocation(line: 2729, column: 4, scope: !6050)
!6054 = !DILocation(line: 2731, column: 30, scope: !6055)
!6055 = distinct !DILexicalBlock(scope: !6041, file: !1, line: 2731, column: 7)
!6056 = !DILocation(line: 2731, column: 35, scope: !6055)
!6057 = !DILocation(line: 2731, column: 41, scope: !6055)
!6058 = !DILocation(line: 2731, column: 54, scope: !6055)
!6059 = !DILocation(line: 2731, column: 52, scope: !6055)
!6060 = !DILocation(line: 2731, column: 7, scope: !6055)
!6061 = !DILocation(line: 2731, column: 66, scope: !6055)
!6062 = !DILocation(line: 2731, column: 7, scope: !6041)
!6063 = !DILocation(line: 2732, column: 23, scope: !6064)
!6064 = distinct !DILexicalBlock(scope: !6055, file: !1, line: 2731, column: 75)
!6065 = !DILocation(line: 2732, column: 26, scope: !6064)
!6066 = !DILocation(line: 2732, column: 4, scope: !6064)
!6067 = !DILocation(line: 2734, column: 4, scope: !6064)
!6068 = !DILocation(line: 2736, column: 10, scope: !6041)
!6069 = !DILocation(line: 2736, column: 15, scope: !6041)
!6070 = !DILocation(line: 2736, column: 20, scope: !6041)
!6071 = !DILocation(line: 2736, column: 24, scope: !6041)
!6072 = !DILocation(line: 2736, column: 22, scope: !6041)
!6073 = !DILocation(line: 2736, column: 36, scope: !6041)
!6074 = !DILocation(line: 2736, column: 39, scope: !6041)
!6075 = !DILocation(line: 2736, column: 3, scope: !6041)
!6076 = !DILocation(line: 2737, column: 24, scope: !6041)
!6077 = !DILocation(line: 2737, column: 27, scope: !6041)
!6078 = !DILocation(line: 2737, column: 3, scope: !6041)
!6079 = !DILocation(line: 2738, column: 17, scope: !6041)
!6080 = !DILocation(line: 2738, column: 14, scope: !6041)
!6081 = !DILocation(line: 2740, column: 7, scope: !6082)
!6082 = distinct !DILexicalBlock(scope: !6041, file: !1, line: 2740, column: 7)
!6083 = !DILocation(line: 2740, column: 9, scope: !6082)
!6084 = !DILocation(line: 2740, column: 7, scope: !6041)
!6085 = !DILocation(line: 2741, column: 13, scope: !6086)
!6086 = distinct !DILexicalBlock(scope: !6082, file: !1, line: 2740, column: 18)
!6087 = !DILocation(line: 2741, column: 18, scope: !6086)
!6088 = !DILocation(line: 2741, column: 23, scope: !6086)
!6089 = !DILocation(line: 2741, column: 5, scope: !6086)
!6090 = !DILocation(line: 2741, column: 11, scope: !6086)
!6091 = !DILocation(line: 2742, column: 12, scope: !6086)
!6092 = !DILocation(line: 2742, column: 4, scope: !6086)
!6093 = !DILocation(line: 2745, column: 28, scope: !6041)
!6094 = !DILocation(line: 2745, column: 7, scope: !6041)
!6095 = !DILocation(line: 2745, column: 5, scope: !6041)
!6096 = !DILocation(line: 2746, column: 7, scope: !6097)
!6097 = distinct !DILexicalBlock(scope: !6041, file: !1, line: 2746, column: 7)
!6098 = !DILocation(line: 2746, column: 18, scope: !6097)
!6099 = !DILocation(line: 2746, column: 7, scope: !6041)
!6100 = !DILocation(line: 2747, column: 4, scope: !6097)
!6101 = !DILocation(line: 2748, column: 7, scope: !6041)
!6102 = !DILocation(line: 2748, column: 5, scope: !6041)
!6103 = !DILocation(line: 2749, column: 14, scope: !6041)
!6104 = !DILocation(line: 2749, column: 23, scope: !6041)
!6105 = !DILocation(line: 2749, column: 7, scope: !6041)
!6106 = !DILocation(line: 2749, column: 5, scope: !6041)
!6107 = !DILocation(line: 2751, column: 7, scope: !6108)
!6108 = distinct !DILexicalBlock(scope: !6041, file: !1, line: 2751, column: 7)
!6109 = !DILocation(line: 2751, column: 9, scope: !6108)
!6110 = !DILocation(line: 2751, column: 7, scope: !6041)
!6111 = !DILocation(line: 2752, column: 36, scope: !6112)
!6112 = distinct !DILexicalBlock(scope: !6108, file: !1, line: 2751, column: 18)
!6113 = !DILocation(line: 2752, column: 19, scope: !6112)
!6114 = !DILocation(line: 2752, column: 41, scope: !6112)
!6115 = !DILocation(line: 2752, column: 39, scope: !6112)
!6116 = !DILocation(line: 2752, column: 15, scope: !6112)
!6117 = !DILocation(line: 2753, column: 3, scope: !6112)
!6118 = !DILocation(line: 2754, column: 17, scope: !6041)
!6119 = !DILocation(line: 2754, column: 4, scope: !6041)
!6120 = !DILocation(line: 2754, column: 15, scope: !6041)
!6121 = !DILocation(line: 2724, column: 2, scope: !6122)
!6122 = !DILexicalBlockFile(scope: !6042, file: !1, discriminator: 1)
!6123 = !DILocation(line: 2756, column: 1, scope: !536)
