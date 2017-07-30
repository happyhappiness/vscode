; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_support_format_lha.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%union.anon = type { i32 }
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
%struct.lha = type { i64, i64, i64, i16, i64, i8, [3 x i8], i64, i64, i32, i64, i64, i64, i64, i64, i64, i32, i64, i64, %struct.archive_string, %struct.archive_string, i16, i16, %struct.archive_string_conv*, %struct.archive_string_conv*, %struct.archive_string, %struct.archive_string, %struct.archive_wstring, i8, i8, i8, i8, i8, i8, i8, [64 x i8], %struct.lzh_stream }
%struct.archive_wstring = type { i32*, i64, i64 }
%struct.lzh_stream = type { i8*, i32, i64, i8*, i32, i64, %struct.lzh_dec* }
%struct.lzh_dec = type { i32, i32, i32, i8*, i32, i32, i32, %struct.lzh_br, %struct.huffman, %struct.huffman, i32, i32, i32, i32, i32, i32, i32, i32 }
%struct.lzh_br = type { i64, i32 }
%struct.huffman = type { i32, i32, i32, [17 x i32], i8*, i32, i32, i32, i32, i32, i16*, %struct.htree_t* }
%struct.htree_t = type { i16, i16 }
%struct.tm = type { i32, i32, i32, i32, i32, i32, i32, i32, i32, i64, i8* }

@.str = private unnamed_addr constant [32 x i8] c"archive_read_support_format_lha\00", align 1
@.str.1 = private unnamed_addr constant [24 x i8] c"Can't allocate lha data\00", align 1
@.str.2 = private unnamed_addr constant [4 x i8] c"lha\00", align 1
@.str.3 = private unnamed_addr constant [11 x i8] c"hdrcharset\00", align 1
@.str.4 = private unnamed_addr constant [50 x i8] c"lha: hdrcharset option needs a character-set name\00", align 1
@.str.5 = private unnamed_addr constant [13 x i8] c"Bad LHa file\00", align 1
@.str.6 = private unnamed_addr constant [4 x i8] c"lhd\00", align 1
@.str.7 = private unnamed_addr constant [4 x i8] c"lh0\00", align 1
@.str.8 = private unnamed_addr constant [4 x i8] c"lz4\00", align 1
@.str.9 = private unnamed_addr constant [32 x i8] c"Unsupported LHa header level %d\00", align 1
@.str.10 = private unnamed_addr constant [21 x i8] c"Unknown symlink-name\00", align 1
@.str.11 = private unnamed_addr constant [35 x i8] c"Can't allocate memory for Pathname\00", align 1
@.str.12 = private unnamed_addr constant [56 x i8] c"Pathname cannot be converted from %s to current locale.\00", align 1
@.str.13 = private unnamed_addr constant [35 x i8] c"Can't allocate memory for Linkname\00", align 1
@.str.14 = private unnamed_addr constant [56 x i8] c"Linkname cannot be converted from %s to current locale.\00", align 1
@.str.15 = private unnamed_addr constant [13 x i8] c"lha -%c%c%c-\00", align 1
@lha_crc16_init.crc16init = internal global i32 0, align 4
@crc16tbl = internal global [2 x [256 x i16]] zeroinitializer, align 16
@.str.16 = private unnamed_addr constant [21 x i8] c"Truncated LHa header\00", align 1
@.str.17 = private unnamed_addr constant [29 x i8] c"Couldn't find out LHa header\00", align 1
@.str.18 = private unnamed_addr constant [19 x i8] c"Invalid LHa header\00", align 1
@.str.19 = private unnamed_addr constant [21 x i8] c"LHa header sum error\00", align 1
@lha_read_file_extended_header.zeros = internal constant [2 x i8] zeroinitializer, align 1
@.str.20 = private unnamed_addr constant [6 x i8] c"UTF-8\00", align 1
@.str.21 = private unnamed_addr constant [5 x i8] c"CP%d\00", align 1
@.str.22 = private unnamed_addr constant [28 x i8] c"Invalid extended LHa header\00", align 1
@lha_crc16.u = internal constant %union.anon { i32 16909060 }, align 4
@.str.23 = private unnamed_addr constant [24 x i8] c"Invalid LHa header size\00", align 1
@.str.24 = private unnamed_addr constant [21 x i8] c"LHa header CRC error\00", align 1
@.str.25 = private unnamed_addr constant [19 x i8] c"LHa data CRC error\00", align 1
@.str.26 = private unnamed_addr constant [44 x i8] c"Unsupported lzh compression method -%c%c%c-\00", align 1
@.str.27 = private unnamed_addr constant [47 x i8] c"Couldn't allocate memory for lzh decompression\00", align 1
@.str.28 = private unnamed_addr constant [24 x i8] c"Truncated LHa file body\00", align 1
@.str.29 = private unnamed_addr constant [13 x i8] c"Bad lzh data\00", align 1
@cache_masks = internal constant [20 x i16] [i16 0, i16 1, i16 3, i16 7, i16 15, i16 31, i16 63, i16 127, i16 255, i16 511, i16 1023, i16 2047, i16 4095, i16 8191, i16 16383, i16 32767, i16 -1, i16 -1, i16 -1, i16 -1], align 16
@bitlen_tbl = internal global [1024 x i8] c"\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\07\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\08\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\09\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0A\0B\0B\0B\0B\0B\0B\0B\0B\0B\0B\0B\0B\0B\0B\0B\0B\0B\0B\0B\0B\0B\0B\0B\0B\0B\0B\0B\0B\0B\0B\0B\0B\0C\0C\0C\0C\0C\0C\0C\0C\0C\0C\0C\0C\0C\0C\0C\0C\0D\0D\0D\0D\0D\0D\0D\0D\0E\0E\0E\0E\0F\0F\10\00", align 16
@.str.30 = private unnamed_addr constant [24 x i8] c"Truncated LHa file data\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_read_support_format_lha(%struct.archive* %_a) #0 !dbg !419 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_read*, align 8
  %lha = alloca %struct.lha*, align 8
  %r = alloca i32, align 4
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !547, metadata !548), !dbg !549
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !550, metadata !548), !dbg !551
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !552
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !553
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !551
  call void @llvm.dbg.declare(metadata %struct.lha** %lha, metadata !554, metadata !548), !dbg !555
  call void @llvm.dbg.declare(metadata i32* %r, metadata !556, metadata !548), !dbg !557
  br label %do.body, !dbg !558

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !559, metadata !548), !dbg !561
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !562
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 14594245, i32 1, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str, i32 0, i32 0)), !dbg !562
  store i32 %call, i32* %magic_test, align 4, !dbg !562
  %3 = load i32, i32* %magic_test, align 4, !dbg !562
  %cmp = icmp eq i32 %3, -30, !dbg !562
  br i1 %cmp, label %if.then, label %if.end, !dbg !562

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !564
  br label %return, !dbg !564

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !567

do.end:                                           ; preds = %if.end
  %call1 = call noalias i8* @calloc(i64 1, i64 416) #8, !dbg !569
  %4 = bitcast i8* %call1 to %struct.lha*, !dbg !570
  store %struct.lha* %4, %struct.lha** %lha, align 8, !dbg !571
  %5 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !572
  %cmp2 = icmp eq %struct.lha* %5, null, !dbg !574
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !575

if.then3:                                         ; preds = %do.end
  %6 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !576
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %6, i32 0, i32 0, !dbg !578
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.1, i32 0, i32 0)), !dbg !579
  store i32 -30, i32* %retval, align 4, !dbg !580
  br label %return, !dbg !580

if.end4:                                          ; preds = %do.end
  br label %do.body5, !dbg !581

do.body5:                                         ; preds = %if.end4
  %7 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !582
  %ws = getelementptr inbounds %struct.lha, %struct.lha* %7, i32 0, i32 27, !dbg !582
  %s = getelementptr inbounds %struct.archive_wstring, %struct.archive_wstring* %ws, i32 0, i32 0, !dbg !582
  store i32* null, i32** %s, align 8, !dbg !582
  %8 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !582
  %ws6 = getelementptr inbounds %struct.lha, %struct.lha* %8, i32 0, i32 27, !dbg !582
  %length = getelementptr inbounds %struct.archive_wstring, %struct.archive_wstring* %ws6, i32 0, i32 1, !dbg !582
  store i64 0, i64* %length, align 8, !dbg !582
  %9 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !582
  %ws7 = getelementptr inbounds %struct.lha, %struct.lha* %9, i32 0, i32 27, !dbg !582
  %buffer_length = getelementptr inbounds %struct.archive_wstring, %struct.archive_wstring* %ws7, i32 0, i32 2, !dbg !582
  store i64 0, i64* %buffer_length, align 8, !dbg !582
  br label %do.end8, !dbg !582

do.end8:                                          ; preds = %do.body5
  %10 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !585
  %11 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !586
  %12 = bitcast %struct.lha* %11 to i8*, !dbg !586
  %call9 = call i32 @__archive_read_register_format(%struct.archive_read* %10, i8* %12, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.2, i32 0, i32 0), i32 (%struct.archive_read*, i32)* @archive_read_format_lha_bid, i32 (%struct.archive_read*, i8*, i8*)* @archive_read_format_lha_options, i32 (%struct.archive_read*, %struct.archive_entry*)* @archive_read_format_lha_read_header, i32 (%struct.archive_read*, i8**, i64*, i64*)* @archive_read_format_lha_read_data, i32 (%struct.archive_read*)* @archive_read_format_lha_read_data_skip, i64 (%struct.archive_read*, i64, i32)* null, i32 (%struct.archive_read*)* @archive_read_format_lha_cleanup, i32 (%struct.archive_read*)* null, i32 (%struct.archive_read*)* null), !dbg !587
  store i32 %call9, i32* %r, align 4, !dbg !588
  %13 = load i32, i32* %r, align 4, !dbg !589
  %cmp10 = icmp ne i32 %13, 0, !dbg !591
  br i1 %cmp10, label %if.then11, label %if.end12, !dbg !592

if.then11:                                        ; preds = %do.end8
  %14 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !593
  %15 = bitcast %struct.lha* %14 to i8*, !dbg !593
  call void @free(i8* %15) #8, !dbg !594
  br label %if.end12, !dbg !594

if.end12:                                         ; preds = %if.then11, %do.end8
  store i32 0, i32* %retval, align 4, !dbg !595
  br label %return, !dbg !595

return:                                           ; preds = %if.end12, %if.then3, %if.then
  %16 = load i32, i32* %retval, align 4, !dbg !596
  ret i32 %16, !dbg !596
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @__archive_check_magic(%struct.archive*, i32, i32, i8*) #2

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #3

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

declare i32 @__archive_read_register_format(%struct.archive_read*, i8*, i8*, i32 (%struct.archive_read*, i32)*, i32 (%struct.archive_read*, i8*, i8*)*, i32 (%struct.archive_read*, %struct.archive_entry*)*, i32 (%struct.archive_read*, i8**, i64*, i64*)*, i32 (%struct.archive_read*)*, i64 (%struct.archive_read*, i64, i32)*, i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)*) #2

; Function Attrs: nounwind uwtable
define internal i32 @archive_read_format_lha_bid(%struct.archive_read* %a, i32 %best_bid) #0 !dbg !420 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %best_bid.addr = alloca i32, align 4
  %p = alloca i8*, align 8
  %buff = alloca i8*, align 8
  %bytes_avail = alloca i64, align 8
  %offset = alloca i64, align 8
  %window = alloca i64, align 8
  %next = alloca i64, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !597, metadata !548), !dbg !598
  store i32 %best_bid, i32* %best_bid.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %best_bid.addr, metadata !599, metadata !548), !dbg !600
  call void @llvm.dbg.declare(metadata i8** %p, metadata !601, metadata !548), !dbg !602
  call void @llvm.dbg.declare(metadata i8** %buff, metadata !603, metadata !548), !dbg !604
  call void @llvm.dbg.declare(metadata i64* %bytes_avail, metadata !605, metadata !548), !dbg !606
  call void @llvm.dbg.declare(metadata i64* %offset, metadata !607, metadata !548), !dbg !608
  call void @llvm.dbg.declare(metadata i64* %window, metadata !609, metadata !548), !dbg !610
  call void @llvm.dbg.declare(metadata i64* %next, metadata !611, metadata !548), !dbg !612
  %0 = load i32, i32* %best_bid.addr, align 4, !dbg !613
  %cmp = icmp sgt i32 %0, 30, !dbg !615
  br i1 %cmp, label %if.then, label %if.end, !dbg !616

if.then:                                          ; preds = %entry
  store i32 -1, i32* %retval, align 4, !dbg !617
  br label %return, !dbg !617

if.end:                                           ; preds = %entry
  %1 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !618
  %call = call i8* @__archive_read_ahead(%struct.archive_read* %1, i64 22, i64* null), !dbg !620
  store i8* %call, i8** %p, align 8, !dbg !621
  %cmp1 = icmp eq i8* %call, null, !dbg !622
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !623

if.then2:                                         ; preds = %if.end
  store i32 -1, i32* %retval, align 4, !dbg !624
  br label %return, !dbg !624

if.end3:                                          ; preds = %if.end
  %2 = load i8*, i8** %p, align 8, !dbg !625
  %call4 = call i64 @lha_check_header_format(i8* %2), !dbg !627
  %cmp5 = icmp eq i64 %call4, 0, !dbg !628
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !629

if.then6:                                         ; preds = %if.end3
  store i32 30, i32* %retval, align 4, !dbg !630
  br label %return, !dbg !630

if.end7:                                          ; preds = %if.end3
  %3 = load i8*, i8** %p, align 8, !dbg !631
  %arrayidx = getelementptr inbounds i8, i8* %3, i64 0, !dbg !631
  %4 = load i8, i8* %arrayidx, align 1, !dbg !631
  %conv = sext i8 %4 to i32, !dbg !631
  %cmp8 = icmp eq i32 %conv, 77, !dbg !633
  br i1 %cmp8, label %land.lhs.true, label %if.end39, !dbg !634

land.lhs.true:                                    ; preds = %if.end7
  %5 = load i8*, i8** %p, align 8, !dbg !635
  %arrayidx10 = getelementptr inbounds i8, i8* %5, i64 1, !dbg !635
  %6 = load i8, i8* %arrayidx10, align 1, !dbg !635
  %conv11 = sext i8 %6 to i32, !dbg !635
  %cmp12 = icmp eq i32 %conv11, 90, !dbg !637
  br i1 %cmp12, label %if.then14, label %if.end39, !dbg !638

if.then14:                                        ; preds = %land.lhs.true
  store i64 0, i64* %offset, align 8, !dbg !639
  store i64 4096, i64* %window, align 8, !dbg !641
  br label %while.cond, !dbg !642

while.cond:                                       ; preds = %while.end, %if.end24, %if.then14
  %7 = load i64, i64* %offset, align 8, !dbg !643
  %cmp15 = icmp slt i64 %7, 20480, !dbg !645
  br i1 %cmp15, label %while.body, label %while.end38, !dbg !646

while.body:                                       ; preds = %while.cond
  %8 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !647
  %9 = load i64, i64* %offset, align 8, !dbg !649
  %10 = load i64, i64* %window, align 8, !dbg !650
  %add = add nsw i64 %9, %10, !dbg !651
  %call17 = call i8* @__archive_read_ahead(%struct.archive_read* %8, i64 %add, i64* %bytes_avail), !dbg !652
  store i8* %call17, i8** %buff, align 8, !dbg !653
  %11 = load i8*, i8** %buff, align 8, !dbg !654
  %cmp18 = icmp eq i8* %11, null, !dbg !656
  br i1 %cmp18, label %if.then20, label %if.end25, !dbg !657

if.then20:                                        ; preds = %while.body
  %12 = load i64, i64* %window, align 8, !dbg !658
  %shr = ashr i64 %12, 1, !dbg !658
  store i64 %shr, i64* %window, align 8, !dbg !658
  %13 = load i64, i64* %window, align 8, !dbg !660
  %cmp21 = icmp slt i64 %13, 25, !dbg !662
  br i1 %cmp21, label %if.then23, label %if.end24, !dbg !663

if.then23:                                        ; preds = %if.then20
  store i32 0, i32* %retval, align 4, !dbg !664
  br label %return, !dbg !664

if.end24:                                         ; preds = %if.then20
  br label %while.cond, !dbg !665

if.end25:                                         ; preds = %while.body
  %14 = load i8*, i8** %buff, align 8, !dbg !666
  %15 = load i64, i64* %offset, align 8, !dbg !667
  %add.ptr = getelementptr inbounds i8, i8* %14, i64 %15, !dbg !668
  store i8* %add.ptr, i8** %p, align 8, !dbg !669
  br label %while.cond26, !dbg !670

while.cond26:                                     ; preds = %if.end36, %if.end25
  %16 = load i8*, i8** %p, align 8, !dbg !671
  %add.ptr27 = getelementptr inbounds i8, i8* %16, i64 22, !dbg !673
  %17 = load i8*, i8** %buff, align 8, !dbg !674
  %18 = load i64, i64* %bytes_avail, align 8, !dbg !675
  %add.ptr28 = getelementptr inbounds i8, i8* %17, i64 %18, !dbg !676
  %cmp29 = icmp ult i8* %add.ptr27, %add.ptr28, !dbg !677
  br i1 %cmp29, label %while.body31, label %while.end, !dbg !678

while.body31:                                     ; preds = %while.cond26
  %19 = load i8*, i8** %p, align 8, !dbg !679
  %call32 = call i64 @lha_check_header_format(i8* %19), !dbg !682
  store i64 %call32, i64* %next, align 8, !dbg !683
  %cmp33 = icmp eq i64 %call32, 0, !dbg !684
  br i1 %cmp33, label %if.then35, label %if.end36, !dbg !685

if.then35:                                        ; preds = %while.body31
  store i32 30, i32* %retval, align 4, !dbg !686
  br label %return, !dbg !686

if.end36:                                         ; preds = %while.body31
  %20 = load i64, i64* %next, align 8, !dbg !687
  %21 = load i8*, i8** %p, align 8, !dbg !688
  %add.ptr37 = getelementptr inbounds i8, i8* %21, i64 %20, !dbg !688
  store i8* %add.ptr37, i8** %p, align 8, !dbg !688
  br label %while.cond26, !dbg !689

while.end:                                        ; preds = %while.cond26
  %22 = load i8*, i8** %p, align 8, !dbg !691
  %23 = load i8*, i8** %buff, align 8, !dbg !692
  %sub.ptr.lhs.cast = ptrtoint i8* %22 to i64, !dbg !693
  %sub.ptr.rhs.cast = ptrtoint i8* %23 to i64, !dbg !693
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !693
  store i64 %sub.ptr.sub, i64* %offset, align 8, !dbg !694
  br label %while.cond, !dbg !695

while.end38:                                      ; preds = %while.cond
  br label %if.end39, !dbg !697

if.end39:                                         ; preds = %while.end38, %land.lhs.true, %if.end7
  store i32 0, i32* %retval, align 4, !dbg !698
  br label %return, !dbg !698

return:                                           ; preds = %if.end39, %if.then35, %if.then23, %if.then6, %if.then2, %if.then
  %24 = load i32, i32* %retval, align 4, !dbg !699
  ret i32 %24, !dbg !699
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_read_format_lha_options(%struct.archive_read* %a, i8* %key, i8* %val) #0 !dbg !424 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %key.addr = alloca i8*, align 8
  %val.addr = alloca i8*, align 8
  %lha = alloca %struct.lha*, align 8
  %ret = alloca i32, align 4
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !700, metadata !548), !dbg !701
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !702, metadata !548), !dbg !703
  store i8* %val, i8** %val.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %val.addr, metadata !704, metadata !548), !dbg !705
  call void @llvm.dbg.declare(metadata %struct.lha** %lha, metadata !706, metadata !548), !dbg !707
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !708, metadata !548), !dbg !709
  store i32 -25, i32* %ret, align 4, !dbg !709
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !710
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 13, !dbg !711
  %1 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !711
  %data = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %1, i32 0, i32 0, !dbg !712
  %2 = load i8*, i8** %data, align 8, !dbg !712
  %3 = bitcast i8* %2 to %struct.lha*, !dbg !713
  store %struct.lha* %3, %struct.lha** %lha, align 8, !dbg !714
  %4 = load i8*, i8** %key.addr, align 8, !dbg !715
  %call = call i32 @strcmp(i8* %4, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.3, i32 0, i32 0)) #9, !dbg !717
  %cmp = icmp eq i32 %call, 0, !dbg !718
  br i1 %cmp, label %if.then, label %if.end13, !dbg !719

if.then:                                          ; preds = %entry
  %5 = load i8*, i8** %val.addr, align 8, !dbg !720
  %cmp1 = icmp eq i8* %5, null, !dbg !723
  br i1 %cmp1, label %if.then4, label %lor.lhs.false, !dbg !724

lor.lhs.false:                                    ; preds = %if.then
  %6 = load i8*, i8** %val.addr, align 8, !dbg !725
  %arrayidx = getelementptr inbounds i8, i8* %6, i64 0, !dbg !725
  %7 = load i8, i8* %arrayidx, align 1, !dbg !725
  %conv = sext i8 %7 to i32, !dbg !725
  %cmp2 = icmp eq i32 %conv, 0, !dbg !727
  br i1 %cmp2, label %if.then4, label %if.else, !dbg !728

if.then4:                                         ; preds = %lor.lhs.false, %if.then
  %8 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !729
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %8, i32 0, i32 0, !dbg !730
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 -1, i8* getelementptr inbounds ([50 x i8], [50 x i8]* @.str.4, i32 0, i32 0)), !dbg !731
  br label %if.end12, !dbg !731

if.else:                                          ; preds = %lor.lhs.false
  %9 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !732
  %archive5 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %9, i32 0, i32 0, !dbg !734
  %10 = load i8*, i8** %val.addr, align 8, !dbg !735
  %call6 = call %struct.archive_string_conv* @archive_string_conversion_from_charset(%struct.archive* %archive5, i8* %10, i32 0), !dbg !736
  %11 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !737
  %opt_sconv = getelementptr inbounds %struct.lha, %struct.lha* %11, i32 0, i32 24, !dbg !738
  store %struct.archive_string_conv* %call6, %struct.archive_string_conv** %opt_sconv, align 8, !dbg !739
  %12 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !740
  %opt_sconv7 = getelementptr inbounds %struct.lha, %struct.lha* %12, i32 0, i32 24, !dbg !742
  %13 = load %struct.archive_string_conv*, %struct.archive_string_conv** %opt_sconv7, align 8, !dbg !742
  %cmp8 = icmp ne %struct.archive_string_conv* %13, null, !dbg !743
  br i1 %cmp8, label %if.then10, label %if.else11, !dbg !744

if.then10:                                        ; preds = %if.else
  store i32 0, i32* %ret, align 4, !dbg !745
  br label %if.end, !dbg !746

if.else11:                                        ; preds = %if.else
  store i32 -30, i32* %ret, align 4, !dbg !747
  br label %if.end

if.end:                                           ; preds = %if.else11, %if.then10
  br label %if.end12

if.end12:                                         ; preds = %if.end, %if.then4
  %14 = load i32, i32* %ret, align 4, !dbg !748
  store i32 %14, i32* %retval, align 4, !dbg !749
  br label %return, !dbg !749

if.end13:                                         ; preds = %entry
  store i32 -20, i32* %retval, align 4, !dbg !750
  br label %return, !dbg !750

return:                                           ; preds = %if.end13, %if.end12
  %15 = load i32, i32* %retval, align 4, !dbg !751
  ret i32 %15, !dbg !751
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_read_format_lha_read_header(%struct.archive_read* %a, %struct.archive_entry* %entry1) #0 !dbg !425 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %linkname = alloca %struct.archive_string, align 8
  %pathname = alloca %struct.archive_string, align 8
  %lha = alloca %struct.lha*, align 8
  %p = alloca i8*, align 8
  %signature = alloca i8*, align 8
  %err = alloca i32, align 4
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !752, metadata !548), !dbg !753
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !754, metadata !548), !dbg !755
  call void @llvm.dbg.declare(metadata %struct.archive_string* %linkname, metadata !756, metadata !548), !dbg !757
  call void @llvm.dbg.declare(metadata %struct.archive_string* %pathname, metadata !758, metadata !548), !dbg !759
  call void @llvm.dbg.declare(metadata %struct.lha** %lha, metadata !760, metadata !548), !dbg !761
  call void @llvm.dbg.declare(metadata i8** %p, metadata !762, metadata !548), !dbg !763
  call void @llvm.dbg.declare(metadata i8** %signature, metadata !764, metadata !548), !dbg !765
  call void @llvm.dbg.declare(metadata i32* %err, metadata !766, metadata !548), !dbg !767
  call void @lha_crc16_init(), !dbg !768
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !769
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 0, !dbg !770
  %archive_format = getelementptr inbounds %struct.archive, %struct.archive* %archive, i32 0, i32 3, !dbg !771
  store i32 720896, i32* %archive_format, align 8, !dbg !772
  %1 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !773
  %archive2 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %1, i32 0, i32 0, !dbg !775
  %archive_format_name = getelementptr inbounds %struct.archive, %struct.archive* %archive2, i32 0, i32 4, !dbg !776
  %2 = load i8*, i8** %archive_format_name, align 8, !dbg !776
  %cmp = icmp eq i8* %2, null, !dbg !777
  br i1 %cmp, label %if.then, label %if.end, !dbg !778

if.then:                                          ; preds = %entry
  %3 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !779
  %archive3 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %3, i32 0, i32 0, !dbg !780
  %archive_format_name4 = getelementptr inbounds %struct.archive, %struct.archive* %archive3, i32 0, i32 4, !dbg !781
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.2, i32 0, i32 0), i8** %archive_format_name4, align 8, !dbg !782
  br label %if.end, !dbg !779

if.end:                                           ; preds = %if.then, %entry
  %4 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !783
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %4, i32 0, i32 13, !dbg !784
  %5 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !784
  %data = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %5, i32 0, i32 0, !dbg !785
  %6 = load i8*, i8** %data, align 8, !dbg !785
  %7 = bitcast i8* %6 to %struct.lha*, !dbg !786
  store %struct.lha* %7, %struct.lha** %lha, align 8, !dbg !787
  %8 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !788
  %decompress_init = getelementptr inbounds %struct.lha, %struct.lha* %8, i32 0, i32 31, !dbg !789
  store i8 0, i8* %decompress_init, align 1, !dbg !790
  %9 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !791
  %end_of_entry = getelementptr inbounds %struct.lha, %struct.lha* %9, i32 0, i32 32, !dbg !792
  store i8 0, i8* %end_of_entry, align 4, !dbg !793
  %10 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !794
  %end_of_entry_cleanup = getelementptr inbounds %struct.lha, %struct.lha* %10, i32 0, i32 33, !dbg !795
  store i8 0, i8* %end_of_entry_cleanup, align 1, !dbg !796
  %11 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !797
  %entry_unconsumed = getelementptr inbounds %struct.lha, %struct.lha* %11, i32 0, i32 2, !dbg !798
  store i64 0, i64* %entry_unconsumed, align 8, !dbg !799
  %12 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !800
  %call = call i8* @__archive_read_ahead(%struct.archive_read* %12, i64 22, i64* null), !dbg !802
  store i8* %call, i8** %p, align 8, !dbg !803
  %cmp5 = icmp eq i8* %call, null, !dbg !804
  br i1 %cmp5, label %if.then6, label %if.end14, !dbg !805

if.then6:                                         ; preds = %if.end
  %13 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !806
  %call7 = call i8* @__archive_read_ahead(%struct.archive_read* %13, i64 1, i64* null), !dbg !808
  store i8* %call7, i8** %signature, align 8, !dbg !809
  %14 = load i8*, i8** %signature, align 8, !dbg !810
  %cmp8 = icmp eq i8* %14, null, !dbg !812
  br i1 %cmp8, label %if.then11, label %lor.lhs.false, !dbg !813

lor.lhs.false:                                    ; preds = %if.then6
  %15 = load i8*, i8** %signature, align 8, !dbg !814
  %arrayidx = getelementptr inbounds i8, i8* %15, i64 0, !dbg !814
  %16 = load i8, i8* %arrayidx, align 1, !dbg !814
  %conv = sext i8 %16 to i32, !dbg !814
  %cmp9 = icmp eq i32 %conv, 0, !dbg !816
  br i1 %cmp9, label %if.then11, label %if.end12, !dbg !817

if.then11:                                        ; preds = %lor.lhs.false, %if.then6
  store i32 1, i32* %retval, align 4, !dbg !818
  br label %return, !dbg !818

if.end12:                                         ; preds = %lor.lhs.false
  %17 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !819
  %call13 = call i32 @truncated_error(%struct.archive_read* %17), !dbg !820
  store i32 %call13, i32* %retval, align 4, !dbg !821
  br label %return, !dbg !821

if.end14:                                         ; preds = %if.end
  %18 = load i8*, i8** %p, align 8, !dbg !822
  store i8* %18, i8** %signature, align 8, !dbg !823
  %19 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !824
  %found_first_header = getelementptr inbounds %struct.lha, %struct.lha* %19, i32 0, i32 29, !dbg !826
  %20 = load i8, i8* %found_first_header, align 1, !dbg !826
  %conv15 = sext i8 %20 to i32, !dbg !824
  %cmp16 = icmp eq i32 %conv15, 0, !dbg !827
  br i1 %cmp16, label %land.lhs.true, label %if.end39, !dbg !828

land.lhs.true:                                    ; preds = %if.end14
  %21 = load i8*, i8** %signature, align 8, !dbg !829
  %arrayidx18 = getelementptr inbounds i8, i8* %21, i64 0, !dbg !829
  %22 = load i8, i8* %arrayidx18, align 1, !dbg !829
  %conv19 = sext i8 %22 to i32, !dbg !829
  %cmp20 = icmp eq i32 %conv19, 77, !dbg !830
  br i1 %cmp20, label %land.lhs.true22, label %if.end39, !dbg !831

land.lhs.true22:                                  ; preds = %land.lhs.true
  %23 = load i8*, i8** %signature, align 8, !dbg !832
  %arrayidx23 = getelementptr inbounds i8, i8* %23, i64 1, !dbg !832
  %24 = load i8, i8* %arrayidx23, align 1, !dbg !832
  %conv24 = sext i8 %24 to i32, !dbg !832
  %cmp25 = icmp eq i32 %conv24, 90, !dbg !834
  br i1 %cmp25, label %if.then27, label %if.end39, !dbg !835

if.then27:                                        ; preds = %land.lhs.true22
  %25 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !837
  %call28 = call i32 @lha_skip_sfx(%struct.archive_read* %25), !dbg !839
  store i32 %call28, i32* %err, align 4, !dbg !840
  %26 = load i32, i32* %err, align 4, !dbg !841
  %cmp29 = icmp slt i32 %26, -20, !dbg !843
  br i1 %cmp29, label %if.then31, label %if.end32, !dbg !844

if.then31:                                        ; preds = %if.then27
  %27 = load i32, i32* %err, align 4, !dbg !845
  store i32 %27, i32* %retval, align 4, !dbg !846
  br label %return, !dbg !846

if.end32:                                         ; preds = %if.then27
  %28 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !847
  %call33 = call i8* @__archive_read_ahead(%struct.archive_read* %28, i64 1, i64* null), !dbg !849
  store i8* %call33, i8** %p, align 8, !dbg !850
  %cmp34 = icmp eq i8* %call33, null, !dbg !851
  br i1 %cmp34, label %if.then36, label %if.end38, !dbg !852

if.then36:                                        ; preds = %if.end32
  %29 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !853
  %call37 = call i32 @truncated_error(%struct.archive_read* %29), !dbg !854
  store i32 %call37, i32* %retval, align 4, !dbg !855
  br label %return, !dbg !855

if.end38:                                         ; preds = %if.end32
  %30 = load i8*, i8** %p, align 8, !dbg !856
  store i8* %30, i8** %signature, align 8, !dbg !857
  br label %if.end39, !dbg !858

if.end39:                                         ; preds = %if.end38, %land.lhs.true22, %land.lhs.true, %if.end14
  %31 = load i8*, i8** %signature, align 8, !dbg !859
  %arrayidx40 = getelementptr inbounds i8, i8* %31, i64 0, !dbg !859
  %32 = load i8, i8* %arrayidx40, align 1, !dbg !859
  %conv41 = sext i8 %32 to i32, !dbg !859
  %cmp42 = icmp eq i32 %conv41, 0, !dbg !861
  br i1 %cmp42, label %if.then44, label %if.end45, !dbg !862

if.then44:                                        ; preds = %if.end39
  store i32 1, i32* %retval, align 4, !dbg !863
  br label %return, !dbg !863

if.end45:                                         ; preds = %if.end39
  %33 = load i8*, i8** %p, align 8, !dbg !864
  %call46 = call i64 @lha_check_header_format(i8* %33), !dbg !866
  %cmp47 = icmp ne i64 %call46, 0, !dbg !867
  br i1 %cmp47, label %if.then49, label %if.end51, !dbg !868

if.then49:                                        ; preds = %if.end45
  %34 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !869
  %archive50 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %34, i32 0, i32 0, !dbg !871
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive50, i32 84, i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.5, i32 0, i32 0)), !dbg !872
  store i32 -30, i32* %retval, align 4, !dbg !873
  br label %return, !dbg !873

if.end51:                                         ; preds = %if.end45
  %35 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !874
  %found_first_header52 = getelementptr inbounds %struct.lha, %struct.lha* %35, i32 0, i32 29, !dbg !875
  store i8 1, i8* %found_first_header52, align 1, !dbg !876
  %36 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !877
  %header_size = getelementptr inbounds %struct.lha, %struct.lha* %36, i32 0, i32 4, !dbg !878
  store i64 0, i64* %header_size, align 8, !dbg !879
  %37 = load i8*, i8** %p, align 8, !dbg !880
  %arrayidx53 = getelementptr inbounds i8, i8* %37, i64 20, !dbg !880
  %38 = load i8, i8* %arrayidx53, align 1, !dbg !880
  %39 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !881
  %level = getelementptr inbounds %struct.lha, %struct.lha* %39, i32 0, i32 5, !dbg !882
  store i8 %38, i8* %level, align 8, !dbg !883
  %40 = load i8*, i8** %p, align 8, !dbg !884
  %arrayidx54 = getelementptr inbounds i8, i8* %40, i64 3, !dbg !884
  %41 = load i8, i8* %arrayidx54, align 1, !dbg !884
  %42 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !885
  %method = getelementptr inbounds %struct.lha, %struct.lha* %42, i32 0, i32 6, !dbg !886
  %arrayidx55 = getelementptr inbounds [3 x i8], [3 x i8]* %method, i64 0, i64 0, !dbg !885
  store i8 %41, i8* %arrayidx55, align 1, !dbg !887
  %43 = load i8*, i8** %p, align 8, !dbg !888
  %arrayidx56 = getelementptr inbounds i8, i8* %43, i64 4, !dbg !888
  %44 = load i8, i8* %arrayidx56, align 1, !dbg !888
  %45 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !889
  %method57 = getelementptr inbounds %struct.lha, %struct.lha* %45, i32 0, i32 6, !dbg !890
  %arrayidx58 = getelementptr inbounds [3 x i8], [3 x i8]* %method57, i64 0, i64 1, !dbg !889
  store i8 %44, i8* %arrayidx58, align 1, !dbg !891
  %46 = load i8*, i8** %p, align 8, !dbg !892
  %arrayidx59 = getelementptr inbounds i8, i8* %46, i64 5, !dbg !892
  %47 = load i8, i8* %arrayidx59, align 1, !dbg !892
  %48 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !893
  %method60 = getelementptr inbounds %struct.lha, %struct.lha* %48, i32 0, i32 6, !dbg !894
  %arrayidx61 = getelementptr inbounds [3 x i8], [3 x i8]* %method60, i64 0, i64 2, !dbg !893
  store i8 %47, i8* %arrayidx61, align 1, !dbg !895
  %49 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !896
  %method62 = getelementptr inbounds %struct.lha, %struct.lha* %49, i32 0, i32 6, !dbg !898
  %arraydecay = getelementptr inbounds [3 x i8], [3 x i8]* %method62, i32 0, i32 0, !dbg !896
  %call63 = call i32 @memcmp(i8* %arraydecay, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.6, i32 0, i32 0), i64 3) #9, !dbg !899
  %cmp64 = icmp eq i32 %call63, 0, !dbg !900
  br i1 %cmp64, label %if.then66, label %if.else, !dbg !901

if.then66:                                        ; preds = %if.end51
  %50 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !902
  %directory = getelementptr inbounds %struct.lha, %struct.lha* %50, i32 0, i32 30, !dbg !903
  store i8 1, i8* %directory, align 2, !dbg !904
  br label %if.end68, !dbg !902

if.else:                                          ; preds = %if.end51
  %51 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !905
  %directory67 = getelementptr inbounds %struct.lha, %struct.lha* %51, i32 0, i32 30, !dbg !906
  store i8 0, i8* %directory67, align 2, !dbg !907
  br label %if.end68

if.end68:                                         ; preds = %if.else, %if.then66
  %52 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !908
  %method69 = getelementptr inbounds %struct.lha, %struct.lha* %52, i32 0, i32 6, !dbg !910
  %arraydecay70 = getelementptr inbounds [3 x i8], [3 x i8]* %method69, i32 0, i32 0, !dbg !908
  %call71 = call i32 @memcmp(i8* %arraydecay70, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.7, i32 0, i32 0), i64 3) #9, !dbg !911
  %cmp72 = icmp eq i32 %call71, 0, !dbg !912
  br i1 %cmp72, label %if.then80, label %lor.lhs.false74, !dbg !913

lor.lhs.false74:                                  ; preds = %if.end68
  %53 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !914
  %method75 = getelementptr inbounds %struct.lha, %struct.lha* %53, i32 0, i32 6, !dbg !915
  %arraydecay76 = getelementptr inbounds [3 x i8], [3 x i8]* %method75, i32 0, i32 0, !dbg !914
  %call77 = call i32 @memcmp(i8* %arraydecay76, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.8, i32 0, i32 0), i64 3) #9, !dbg !916
  %cmp78 = icmp eq i32 %call77, 0, !dbg !917
  br i1 %cmp78, label %if.then80, label %if.else81, !dbg !918

if.then80:                                        ; preds = %lor.lhs.false74, %if.end68
  %54 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !919
  %entry_is_compressed = getelementptr inbounds %struct.lha, %struct.lha* %54, i32 0, i32 34, !dbg !920
  store i8 0, i8* %entry_is_compressed, align 2, !dbg !921
  br label %if.end83, !dbg !919

if.else81:                                        ; preds = %lor.lhs.false74
  %55 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !922
  %entry_is_compressed82 = getelementptr inbounds %struct.lha, %struct.lha* %55, i32 0, i32 34, !dbg !923
  store i8 1, i8* %entry_is_compressed82, align 2, !dbg !924
  br label %if.end83

if.end83:                                         ; preds = %if.else81, %if.then80
  %56 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !925
  %compsize = getelementptr inbounds %struct.lha, %struct.lha* %56, i32 0, i32 7, !dbg !926
  store i64 0, i64* %compsize, align 8, !dbg !927
  %57 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !928
  %origsize = getelementptr inbounds %struct.lha, %struct.lha* %57, i32 0, i32 8, !dbg !929
  store i64 0, i64* %origsize, align 8, !dbg !930
  %58 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !931
  %setflag = getelementptr inbounds %struct.lha, %struct.lha* %58, i32 0, i32 9, !dbg !932
  store i32 0, i32* %setflag, align 8, !dbg !933
  %59 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !934
  %birthtime = getelementptr inbounds %struct.lha, %struct.lha* %59, i32 0, i32 10, !dbg !935
  store i64 0, i64* %birthtime, align 8, !dbg !936
  %60 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !937
  %birthtime_tv_nsec = getelementptr inbounds %struct.lha, %struct.lha* %60, i32 0, i32 11, !dbg !938
  store i64 0, i64* %birthtime_tv_nsec, align 8, !dbg !939
  %61 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !940
  %mtime = getelementptr inbounds %struct.lha, %struct.lha* %61, i32 0, i32 12, !dbg !941
  store i64 0, i64* %mtime, align 8, !dbg !942
  %62 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !943
  %mtime_tv_nsec = getelementptr inbounds %struct.lha, %struct.lha* %62, i32 0, i32 13, !dbg !944
  store i64 0, i64* %mtime_tv_nsec, align 8, !dbg !945
  %63 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !946
  %atime = getelementptr inbounds %struct.lha, %struct.lha* %63, i32 0, i32 14, !dbg !947
  store i64 0, i64* %atime, align 8, !dbg !948
  %64 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !949
  %atime_tv_nsec = getelementptr inbounds %struct.lha, %struct.lha* %64, i32 0, i32 15, !dbg !950
  store i64 0, i64* %atime_tv_nsec, align 8, !dbg !951
  %65 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !952
  %directory84 = getelementptr inbounds %struct.lha, %struct.lha* %65, i32 0, i32 30, !dbg !953
  %66 = load i8, i8* %directory84, align 2, !dbg !953
  %conv85 = sext i8 %66 to i32, !dbg !954
  %tobool = icmp ne i32 %conv85, 0, !dbg !954
  %cond = select i1 %tobool, i32 511, i32 438, !dbg !954
  %67 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !955
  %mode = getelementptr inbounds %struct.lha, %struct.lha* %67, i32 0, i32 16, !dbg !956
  store i32 %cond, i32* %mode, align 8, !dbg !957
  %68 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !958
  %uid = getelementptr inbounds %struct.lha, %struct.lha* %68, i32 0, i32 17, !dbg !959
  store i64 0, i64* %uid, align 8, !dbg !960
  %69 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !961
  %gid = getelementptr inbounds %struct.lha, %struct.lha* %69, i32 0, i32 18, !dbg !962
  store i64 0, i64* %gid, align 8, !dbg !963
  %70 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !964
  %dirname = getelementptr inbounds %struct.lha, %struct.lha* %70, i32 0, i32 25, !dbg !964
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %dirname, i32 0, i32 1, !dbg !964
  store i64 0, i64* %length, align 8, !dbg !964
  %71 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !965
  %filename = getelementptr inbounds %struct.lha, %struct.lha* %71, i32 0, i32 26, !dbg !965
  %length86 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %filename, i32 0, i32 1, !dbg !965
  store i64 0, i64* %length86, align 8, !dbg !965
  %72 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !966
  %dos_attr = getelementptr inbounds %struct.lha, %struct.lha* %72, i32 0, i32 28, !dbg !967
  store i8 0, i8* %dos_attr, align 8, !dbg !968
  %73 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !969
  %opt_sconv = getelementptr inbounds %struct.lha, %struct.lha* %73, i32 0, i32 24, !dbg !971
  %74 = load %struct.archive_string_conv*, %struct.archive_string_conv** %opt_sconv, align 8, !dbg !971
  %cmp87 = icmp ne %struct.archive_string_conv* %74, null, !dbg !972
  br i1 %cmp87, label %if.then89, label %if.else91, !dbg !973

if.then89:                                        ; preds = %if.end83
  %75 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !974
  %opt_sconv90 = getelementptr inbounds %struct.lha, %struct.lha* %75, i32 0, i32 24, !dbg !975
  %76 = load %struct.archive_string_conv*, %struct.archive_string_conv** %opt_sconv90, align 8, !dbg !975
  %77 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !976
  %sconv = getelementptr inbounds %struct.lha, %struct.lha* %77, i32 0, i32 23, !dbg !977
  store %struct.archive_string_conv* %76, %struct.archive_string_conv** %sconv, align 8, !dbg !978
  br label %if.end93, !dbg !976

if.else91:                                        ; preds = %if.end83
  %78 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !979
  %sconv92 = getelementptr inbounds %struct.lha, %struct.lha* %78, i32 0, i32 23, !dbg !980
  store %struct.archive_string_conv* null, %struct.archive_string_conv** %sconv92, align 8, !dbg !981
  br label %if.end93

if.end93:                                         ; preds = %if.else91, %if.then89
  %79 = load i8*, i8** %p, align 8, !dbg !982
  %arrayidx94 = getelementptr inbounds i8, i8* %79, i64 20, !dbg !982
  %80 = load i8, i8* %arrayidx94, align 1, !dbg !982
  %conv95 = zext i8 %80 to i32, !dbg !982
  switch i32 %conv95, label %sw.default [
    i32 0, label %sw.bb
    i32 1, label %sw.bb97
    i32 2, label %sw.bb99
    i32 3, label %sw.bb101
  ], !dbg !983

sw.bb:                                            ; preds = %if.end93
  %81 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !984
  %82 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !986
  %call96 = call i32 @lha_read_file_header_0(%struct.archive_read* %81, %struct.lha* %82), !dbg !987
  store i32 %call96, i32* %err, align 4, !dbg !988
  br label %sw.epilog, !dbg !989

sw.bb97:                                          ; preds = %if.end93
  %83 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !990
  %84 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !991
  %call98 = call i32 @lha_read_file_header_1(%struct.archive_read* %83, %struct.lha* %84), !dbg !992
  store i32 %call98, i32* %err, align 4, !dbg !993
  br label %sw.epilog, !dbg !994

sw.bb99:                                          ; preds = %if.end93
  %85 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !995
  %86 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !996
  %call100 = call i32 @lha_read_file_header_2(%struct.archive_read* %85, %struct.lha* %86), !dbg !997
  store i32 %call100, i32* %err, align 4, !dbg !998
  br label %sw.epilog, !dbg !999

sw.bb101:                                         ; preds = %if.end93
  %87 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1000
  %88 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1001
  %call102 = call i32 @lha_read_file_header_3(%struct.archive_read* %87, %struct.lha* %88), !dbg !1002
  store i32 %call102, i32* %err, align 4, !dbg !1003
  br label %sw.epilog, !dbg !1004

sw.default:                                       ; preds = %if.end93
  %89 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1005
  %archive103 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %89, i32 0, i32 0, !dbg !1006
  %90 = load i8*, i8** %p, align 8, !dbg !1007
  %arrayidx104 = getelementptr inbounds i8, i8* %90, i64 20, !dbg !1007
  %91 = load i8, i8* %arrayidx104, align 1, !dbg !1007
  %conv105 = zext i8 %91 to i32, !dbg !1007
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive103, i32 84, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.9, i32 0, i32 0), i32 %conv105), !dbg !1008
  store i32 -30, i32* %err, align 4, !dbg !1009
  br label %sw.epilog, !dbg !1010

sw.epilog:                                        ; preds = %sw.default, %sw.bb101, %sw.bb99, %sw.bb97, %sw.bb
  %92 = load i32, i32* %err, align 4, !dbg !1011
  %cmp106 = icmp slt i32 %92, -20, !dbg !1013
  br i1 %cmp106, label %if.then108, label %if.end109, !dbg !1014

if.then108:                                       ; preds = %sw.epilog
  %93 = load i32, i32* %err, align 4, !dbg !1015
  store i32 %93, i32* %retval, align 4, !dbg !1016
  br label %return, !dbg !1016

if.end109:                                        ; preds = %sw.epilog
  %94 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1017
  %directory110 = getelementptr inbounds %struct.lha, %struct.lha* %94, i32 0, i32 30, !dbg !1019
  %95 = load i8, i8* %directory110, align 2, !dbg !1019
  %tobool111 = icmp ne i8 %95, 0, !dbg !1017
  br i1 %tobool111, label %if.end119, label %land.lhs.true112, !dbg !1020

land.lhs.true112:                                 ; preds = %if.end109
  %96 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1021
  %filename113 = getelementptr inbounds %struct.lha, %struct.lha* %96, i32 0, i32 26, !dbg !1021
  %length114 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %filename113, i32 0, i32 1, !dbg !1021
  %97 = load i64, i64* %length114, align 8, !dbg !1021
  %cmp115 = icmp eq i64 %97, 0, !dbg !1023
  br i1 %cmp115, label %if.then117, label %if.end119, !dbg !1024

if.then117:                                       ; preds = %land.lhs.true112
  %98 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1025
  %call118 = call i32 @truncated_error(%struct.archive_read* %98), !dbg !1026
  store i32 %call118, i32* %retval, align 4, !dbg !1027
  br label %return, !dbg !1027

if.end119:                                        ; preds = %land.lhs.true112, %if.end109
  %99 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1028
  %dirname120 = getelementptr inbounds %struct.lha, %struct.lha* %99, i32 0, i32 25, !dbg !1029
  %100 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1030
  %filename121 = getelementptr inbounds %struct.lha, %struct.lha* %100, i32 0, i32 26, !dbg !1031
  call void @archive_string_concat(%struct.archive_string* %dirname120, %struct.archive_string* %filename121), !dbg !1032
  br label %do.body, !dbg !1033

do.body:                                          ; preds = %if.end119
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %pathname, i32 0, i32 0, !dbg !1034
  store i8* null, i8** %s, align 8, !dbg !1034
  %length122 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %pathname, i32 0, i32 1, !dbg !1034
  store i64 0, i64* %length122, align 8, !dbg !1034
  %buffer_length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %pathname, i32 0, i32 2, !dbg !1034
  store i64 0, i64* %buffer_length, align 8, !dbg !1034
  br label %do.end, !dbg !1034

do.end:                                           ; preds = %do.body
  br label %do.body123, !dbg !1037

do.body123:                                       ; preds = %do.end
  %s124 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %linkname, i32 0, i32 0, !dbg !1038
  store i8* null, i8** %s124, align 8, !dbg !1038
  %length125 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %linkname, i32 0, i32 1, !dbg !1038
  store i64 0, i64* %length125, align 8, !dbg !1038
  %buffer_length126 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %linkname, i32 0, i32 2, !dbg !1038
  store i64 0, i64* %buffer_length126, align 8, !dbg !1038
  br label %do.end127, !dbg !1038

do.end127:                                        ; preds = %do.body123
  %length128 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %pathname, i32 0, i32 1, !dbg !1041
  store i64 0, i64* %length128, align 8, !dbg !1041
  %101 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1041
  %dirname129 = getelementptr inbounds %struct.lha, %struct.lha* %101, i32 0, i32 25, !dbg !1041
  call void @archive_string_concat(%struct.archive_string* %pathname, %struct.archive_string* %dirname129), !dbg !1041
  %102 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1042
  %mode130 = getelementptr inbounds %struct.lha, %struct.lha* %102, i32 0, i32 16, !dbg !1044
  %103 = load i32, i32* %mode130, align 8, !dbg !1044
  %and = and i32 %103, 61440, !dbg !1045
  %cmp131 = icmp eq i32 %and, 40960, !dbg !1046
  br i1 %cmp131, label %if.then133, label %if.else139, !dbg !1047

if.then133:                                       ; preds = %do.end127
  %call134 = call i32 @lha_parse_linkname(%struct.archive_string* %linkname, %struct.archive_string* %pathname), !dbg !1048
  %tobool135 = icmp ne i32 %call134, 0, !dbg !1048
  br i1 %tobool135, label %if.end138, label %if.then136, !dbg !1051

if.then136:                                       ; preds = %if.then133
  %104 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1052
  %archive137 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %104, i32 0, i32 0, !dbg !1054
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive137, i32 84, i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.10, i32 0, i32 0)), !dbg !1055
  call void @archive_string_free(%struct.archive_string* %pathname), !dbg !1056
  call void @archive_string_free(%struct.archive_string* %linkname), !dbg !1057
  store i32 -25, i32* %retval, align 4, !dbg !1058
  br label %return, !dbg !1058

if.end138:                                        ; preds = %if.then133
  br label %if.end147, !dbg !1059

if.else139:                                       ; preds = %do.end127
  %105 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1060
  %mode140 = getelementptr inbounds %struct.lha, %struct.lha* %105, i32 0, i32 16, !dbg !1062
  %106 = load i32, i32* %mode140, align 8, !dbg !1062
  %and141 = and i32 %106, -61441, !dbg !1063
  %107 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1064
  %directory142 = getelementptr inbounds %struct.lha, %struct.lha* %107, i32 0, i32 30, !dbg !1065
  %108 = load i8, i8* %directory142, align 2, !dbg !1065
  %conv143 = sext i8 %108 to i32, !dbg !1066
  %tobool144 = icmp ne i32 %conv143, 0, !dbg !1066
  %cond145 = select i1 %tobool144, i32 16384, i32 32768, !dbg !1066
  %or = or i32 %and141, %cond145, !dbg !1067
  %109 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1068
  %mode146 = getelementptr inbounds %struct.lha, %struct.lha* %109, i32 0, i32 16, !dbg !1069
  store i32 %or, i32* %mode146, align 8, !dbg !1070
  br label %if.end147

if.end147:                                        ; preds = %if.else139, %if.end138
  %110 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1071
  %setflag148 = getelementptr inbounds %struct.lha, %struct.lha* %110, i32 0, i32 9, !dbg !1073
  %111 = load i32, i32* %setflag148, align 8, !dbg !1073
  %and149 = and i32 %111, 4, !dbg !1074
  %cmp150 = icmp eq i32 %and149, 0, !dbg !1075
  br i1 %cmp150, label %land.lhs.true152, label %if.end161, !dbg !1076

land.lhs.true152:                                 ; preds = %if.end147
  %112 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1077
  %dos_attr153 = getelementptr inbounds %struct.lha, %struct.lha* %112, i32 0, i32 28, !dbg !1078
  %113 = load i8, i8* %dos_attr153, align 8, !dbg !1078
  %conv154 = zext i8 %113 to i32, !dbg !1077
  %and155 = and i32 %conv154, 1, !dbg !1079
  %cmp156 = icmp ne i32 %and155, 0, !dbg !1080
  br i1 %cmp156, label %if.then158, label %if.end161, !dbg !1081

if.then158:                                       ; preds = %land.lhs.true152
  %114 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1082
  %mode159 = getelementptr inbounds %struct.lha, %struct.lha* %114, i32 0, i32 16, !dbg !1083
  %115 = load i32, i32* %mode159, align 8, !dbg !1084
  %and160 = and i32 %115, -147, !dbg !1084
  store i32 %and160, i32* %mode159, align 8, !dbg !1084
  br label %if.end161, !dbg !1082

if.end161:                                        ; preds = %if.then158, %land.lhs.true152, %if.end147
  %116 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1085
  %s162 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %pathname, i32 0, i32 0, !dbg !1087
  %117 = load i8*, i8** %s162, align 8, !dbg !1087
  %length163 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %pathname, i32 0, i32 1, !dbg !1088
  %118 = load i64, i64* %length163, align 8, !dbg !1088
  %119 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1089
  %sconv164 = getelementptr inbounds %struct.lha, %struct.lha* %119, i32 0, i32 23, !dbg !1090
  %120 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv164, align 8, !dbg !1090
  %call165 = call i32 @_archive_entry_copy_pathname_l(%struct.archive_entry* %116, i8* %117, i64 %118, %struct.archive_string_conv* %120), !dbg !1091
  %cmp166 = icmp ne i32 %call165, 0, !dbg !1092
  br i1 %cmp166, label %if.then168, label %if.end178, !dbg !1093

if.then168:                                       ; preds = %if.end161
  %call169 = call i32* @__errno_location() #1, !dbg !1094
  %121 = load i32, i32* %call169, align 4, !dbg !1094
  %cmp170 = icmp eq i32 %121, 12, !dbg !1097
  br i1 %cmp170, label %if.then172, label %if.end174, !dbg !1098

if.then172:                                       ; preds = %if.then168
  %122 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1099
  %archive173 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %122, i32 0, i32 0, !dbg !1101
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive173, i32 12, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.11, i32 0, i32 0)), !dbg !1102
  store i32 -30, i32* %retval, align 4, !dbg !1103
  br label %return, !dbg !1103

if.end174:                                        ; preds = %if.then168
  %123 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1104
  %archive175 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %123, i32 0, i32 0, !dbg !1105
  %124 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1106
  %sconv176 = getelementptr inbounds %struct.lha, %struct.lha* %124, i32 0, i32 23, !dbg !1107
  %125 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv176, align 8, !dbg !1107
  %call177 = call i8* @archive_string_conversion_charset_name(%struct.archive_string_conv* %125), !dbg !1108
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive175, i32 84, i8* getelementptr inbounds ([56 x i8], [56 x i8]* @.str.12, i32 0, i32 0), i8* %call177), !dbg !1109
  store i32 -20, i32* %err, align 4, !dbg !1110
  br label %if.end178, !dbg !1111

if.end178:                                        ; preds = %if.end174, %if.end161
  call void @archive_string_free(%struct.archive_string* %pathname), !dbg !1112
  %length179 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %linkname, i32 0, i32 1, !dbg !1113
  %126 = load i64, i64* %length179, align 8, !dbg !1113
  %cmp180 = icmp ugt i64 %126, 0, !dbg !1115
  br i1 %cmp180, label %if.then182, label %if.else200, !dbg !1116

if.then182:                                       ; preds = %if.end178
  %127 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1117
  %s183 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %linkname, i32 0, i32 0, !dbg !1120
  %128 = load i8*, i8** %s183, align 8, !dbg !1120
  %length184 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %linkname, i32 0, i32 1, !dbg !1121
  %129 = load i64, i64* %length184, align 8, !dbg !1121
  %130 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1122
  %sconv185 = getelementptr inbounds %struct.lha, %struct.lha* %130, i32 0, i32 23, !dbg !1123
  %131 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv185, align 8, !dbg !1123
  %call186 = call i32 @_archive_entry_copy_symlink_l(%struct.archive_entry* %127, i8* %128, i64 %129, %struct.archive_string_conv* %131), !dbg !1124
  %cmp187 = icmp ne i32 %call186, 0, !dbg !1125
  br i1 %cmp187, label %if.then189, label %if.end199, !dbg !1126

if.then189:                                       ; preds = %if.then182
  %call190 = call i32* @__errno_location() #1, !dbg !1127
  %132 = load i32, i32* %call190, align 4, !dbg !1127
  %cmp191 = icmp eq i32 %132, 12, !dbg !1130
  br i1 %cmp191, label %if.then193, label %if.end195, !dbg !1131

if.then193:                                       ; preds = %if.then189
  %133 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1132
  %archive194 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %133, i32 0, i32 0, !dbg !1134
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive194, i32 12, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.13, i32 0, i32 0)), !dbg !1135
  store i32 -30, i32* %retval, align 4, !dbg !1136
  br label %return, !dbg !1136

if.end195:                                        ; preds = %if.then189
  %134 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1137
  %archive196 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %134, i32 0, i32 0, !dbg !1138
  %135 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1139
  %sconv197 = getelementptr inbounds %struct.lha, %struct.lha* %135, i32 0, i32 23, !dbg !1140
  %136 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv197, align 8, !dbg !1140
  %call198 = call i8* @archive_string_conversion_charset_name(%struct.archive_string_conv* %136), !dbg !1141
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive196, i32 84, i8* getelementptr inbounds ([56 x i8], [56 x i8]* @.str.14, i32 0, i32 0), i8* %call198), !dbg !1142
  store i32 -20, i32* %err, align 4, !dbg !1143
  br label %if.end199, !dbg !1144

if.end199:                                        ; preds = %if.end195, %if.then182
  br label %if.end201, !dbg !1145

if.else200:                                       ; preds = %if.end178
  %137 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1146
  call void @archive_entry_set_symlink(%struct.archive_entry* %137, i8* null), !dbg !1147
  br label %if.end201

if.end201:                                        ; preds = %if.else200, %if.end199
  call void @archive_string_free(%struct.archive_string* %linkname), !dbg !1148
  %138 = load i8*, i8** %p, align 8, !dbg !1149
  %arrayidx202 = getelementptr inbounds i8, i8* %138, i64 20, !dbg !1149
  %139 = load i8, i8* %arrayidx202, align 1, !dbg !1149
  %conv203 = zext i8 %139 to i32, !dbg !1149
  %cmp204 = icmp eq i32 %conv203, 0, !dbg !1151
  br i1 %cmp204, label %if.then206, label %if.end207, !dbg !1152

if.then206:                                       ; preds = %if.end201
  %140 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1153
  %141 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1154
  call void @lha_replace_path_separator(%struct.lha* %140, %struct.archive_entry* %141), !dbg !1155
  br label %if.end207, !dbg !1155

if.end207:                                        ; preds = %if.then206, %if.end201
  %142 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1156
  %143 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1157
  %mode208 = getelementptr inbounds %struct.lha, %struct.lha* %143, i32 0, i32 16, !dbg !1158
  %144 = load i32, i32* %mode208, align 8, !dbg !1158
  call void @archive_entry_set_mode(%struct.archive_entry* %142, i32 %144), !dbg !1159
  %145 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1160
  %146 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1161
  %uid209 = getelementptr inbounds %struct.lha, %struct.lha* %146, i32 0, i32 17, !dbg !1162
  %147 = load i64, i64* %uid209, align 8, !dbg !1162
  call void @archive_entry_set_uid(%struct.archive_entry* %145, i64 %147), !dbg !1163
  %148 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1164
  %149 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1165
  %gid210 = getelementptr inbounds %struct.lha, %struct.lha* %149, i32 0, i32 18, !dbg !1166
  %150 = load i64, i64* %gid210, align 8, !dbg !1166
  call void @archive_entry_set_gid(%struct.archive_entry* %148, i64 %150), !dbg !1167
  %151 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1168
  %uname = getelementptr inbounds %struct.lha, %struct.lha* %151, i32 0, i32 19, !dbg !1168
  %length211 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %uname, i32 0, i32 1, !dbg !1168
  %152 = load i64, i64* %length211, align 8, !dbg !1168
  %cmp212 = icmp ugt i64 %152, 0, !dbg !1170
  br i1 %cmp212, label %if.then214, label %if.end217, !dbg !1171

if.then214:                                       ; preds = %if.end207
  %153 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1172
  %154 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1173
  %uname215 = getelementptr inbounds %struct.lha, %struct.lha* %154, i32 0, i32 19, !dbg !1174
  %s216 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %uname215, i32 0, i32 0, !dbg !1175
  %155 = load i8*, i8** %s216, align 8, !dbg !1175
  call void @archive_entry_set_uname(%struct.archive_entry* %153, i8* %155), !dbg !1176
  br label %if.end217, !dbg !1176

if.end217:                                        ; preds = %if.then214, %if.end207
  %156 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1177
  %gname = getelementptr inbounds %struct.lha, %struct.lha* %156, i32 0, i32 20, !dbg !1177
  %length218 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %gname, i32 0, i32 1, !dbg !1177
  %157 = load i64, i64* %length218, align 8, !dbg !1177
  %cmp219 = icmp ugt i64 %157, 0, !dbg !1179
  br i1 %cmp219, label %if.then221, label %if.end224, !dbg !1180

if.then221:                                       ; preds = %if.end217
  %158 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1181
  %159 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1182
  %gname222 = getelementptr inbounds %struct.lha, %struct.lha* %159, i32 0, i32 20, !dbg !1183
  %s223 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %gname222, i32 0, i32 0, !dbg !1184
  %160 = load i8*, i8** %s223, align 8, !dbg !1184
  call void @archive_entry_set_gname(%struct.archive_entry* %158, i8* %160), !dbg !1185
  br label %if.end224, !dbg !1185

if.end224:                                        ; preds = %if.then221, %if.end217
  %161 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1186
  %setflag225 = getelementptr inbounds %struct.lha, %struct.lha* %161, i32 0, i32 9, !dbg !1188
  %162 = load i32, i32* %setflag225, align 8, !dbg !1188
  %and226 = and i32 %162, 1, !dbg !1189
  %tobool227 = icmp ne i32 %and226, 0, !dbg !1189
  br i1 %tobool227, label %if.then228, label %if.else233, !dbg !1190

if.then228:                                       ; preds = %if.end224
  %163 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1191
  %164 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1193
  %birthtime229 = getelementptr inbounds %struct.lha, %struct.lha* %164, i32 0, i32 10, !dbg !1194
  %165 = load i64, i64* %birthtime229, align 8, !dbg !1194
  %166 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1195
  %birthtime_tv_nsec230 = getelementptr inbounds %struct.lha, %struct.lha* %166, i32 0, i32 11, !dbg !1196
  %167 = load i64, i64* %birthtime_tv_nsec230, align 8, !dbg !1196
  call void @archive_entry_set_birthtime(%struct.archive_entry* %163, i64 %165, i64 %167), !dbg !1197
  %168 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1198
  %169 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1199
  %birthtime231 = getelementptr inbounds %struct.lha, %struct.lha* %169, i32 0, i32 10, !dbg !1200
  %170 = load i64, i64* %birthtime231, align 8, !dbg !1200
  %171 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1201
  %birthtime_tv_nsec232 = getelementptr inbounds %struct.lha, %struct.lha* %171, i32 0, i32 11, !dbg !1202
  %172 = load i64, i64* %birthtime_tv_nsec232, align 8, !dbg !1202
  call void @archive_entry_set_ctime(%struct.archive_entry* %168, i64 %170, i64 %172), !dbg !1203
  br label %if.end234, !dbg !1204

if.else233:                                       ; preds = %if.end224
  %173 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1205
  call void @archive_entry_unset_birthtime(%struct.archive_entry* %173), !dbg !1207
  %174 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1208
  call void @archive_entry_unset_ctime(%struct.archive_entry* %174), !dbg !1209
  br label %if.end234

if.end234:                                        ; preds = %if.else233, %if.then228
  %175 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1210
  %176 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1211
  %mtime235 = getelementptr inbounds %struct.lha, %struct.lha* %176, i32 0, i32 12, !dbg !1212
  %177 = load i64, i64* %mtime235, align 8, !dbg !1212
  %178 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1213
  %mtime_tv_nsec236 = getelementptr inbounds %struct.lha, %struct.lha* %178, i32 0, i32 13, !dbg !1214
  %179 = load i64, i64* %mtime_tv_nsec236, align 8, !dbg !1214
  call void @archive_entry_set_mtime(%struct.archive_entry* %175, i64 %177, i64 %179), !dbg !1215
  %180 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1216
  %setflag237 = getelementptr inbounds %struct.lha, %struct.lha* %180, i32 0, i32 9, !dbg !1218
  %181 = load i32, i32* %setflag237, align 8, !dbg !1218
  %and238 = and i32 %181, 2, !dbg !1219
  %tobool239 = icmp ne i32 %and238, 0, !dbg !1219
  br i1 %tobool239, label %if.then240, label %if.else243, !dbg !1220

if.then240:                                       ; preds = %if.end234
  %182 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1221
  %183 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1222
  %atime241 = getelementptr inbounds %struct.lha, %struct.lha* %183, i32 0, i32 14, !dbg !1223
  %184 = load i64, i64* %atime241, align 8, !dbg !1223
  %185 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1224
  %atime_tv_nsec242 = getelementptr inbounds %struct.lha, %struct.lha* %185, i32 0, i32 15, !dbg !1225
  %186 = load i64, i64* %atime_tv_nsec242, align 8, !dbg !1225
  call void @archive_entry_set_atime(%struct.archive_entry* %182, i64 %184, i64 %186), !dbg !1226
  br label %if.end244, !dbg !1226

if.else243:                                       ; preds = %if.end234
  %187 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1227
  call void @archive_entry_unset_atime(%struct.archive_entry* %187), !dbg !1228
  br label %if.end244

if.end244:                                        ; preds = %if.else243, %if.then240
  %188 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1229
  %directory245 = getelementptr inbounds %struct.lha, %struct.lha* %188, i32 0, i32 30, !dbg !1231
  %189 = load i8, i8* %directory245, align 2, !dbg !1231
  %conv246 = sext i8 %189 to i32, !dbg !1229
  %tobool247 = icmp ne i32 %conv246, 0, !dbg !1229
  br i1 %tobool247, label %if.then252, label %lor.lhs.false248, !dbg !1232

lor.lhs.false248:                                 ; preds = %if.end244
  %190 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1233
  %call249 = call i8* @archive_entry_symlink(%struct.archive_entry* %190), !dbg !1235
  %cmp250 = icmp ne i8* %call249, null, !dbg !1236
  br i1 %cmp250, label %if.then252, label %if.else253, !dbg !1237

if.then252:                                       ; preds = %lor.lhs.false248, %if.end244
  %191 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1238
  call void @archive_entry_unset_size(%struct.archive_entry* %191), !dbg !1239
  br label %if.end255, !dbg !1239

if.else253:                                       ; preds = %lor.lhs.false248
  %192 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1240
  %193 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1241
  %origsize254 = getelementptr inbounds %struct.lha, %struct.lha* %193, i32 0, i32 8, !dbg !1242
  %194 = load i64, i64* %origsize254, align 8, !dbg !1242
  call void @archive_entry_set_size(%struct.archive_entry* %192, i64 %194), !dbg !1243
  br label %if.end255

if.end255:                                        ; preds = %if.else253, %if.then252
  %195 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1244
  %compsize256 = getelementptr inbounds %struct.lha, %struct.lha* %195, i32 0, i32 7, !dbg !1245
  %196 = load i64, i64* %compsize256, align 8, !dbg !1245
  %197 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1246
  %entry_bytes_remaining = getelementptr inbounds %struct.lha, %struct.lha* %197, i32 0, i32 1, !dbg !1247
  store i64 %196, i64* %entry_bytes_remaining, align 8, !dbg !1248
  %198 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1249
  %entry_offset = getelementptr inbounds %struct.lha, %struct.lha* %198, i32 0, i32 0, !dbg !1250
  store i64 0, i64* %entry_offset, align 8, !dbg !1251
  %199 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1252
  %entry_crc_calculated = getelementptr inbounds %struct.lha, %struct.lha* %199, i32 0, i32 3, !dbg !1253
  store i16 0, i16* %entry_crc_calculated, align 8, !dbg !1254
  %200 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1255
  %directory257 = getelementptr inbounds %struct.lha, %struct.lha* %200, i32 0, i32 30, !dbg !1257
  %201 = load i8, i8* %directory257, align 2, !dbg !1257
  %conv258 = sext i8 %201 to i32, !dbg !1255
  %tobool259 = icmp ne i32 %conv258, 0, !dbg !1255
  br i1 %tobool259, label %if.then264, label %lor.lhs.false260, !dbg !1258

lor.lhs.false260:                                 ; preds = %if.end255
  %202 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1259
  %compsize261 = getelementptr inbounds %struct.lha, %struct.lha* %202, i32 0, i32 7, !dbg !1261
  %203 = load i64, i64* %compsize261, align 8, !dbg !1261
  %cmp262 = icmp eq i64 %203, 0, !dbg !1262
  br i1 %cmp262, label %if.then264, label %if.end266, !dbg !1263

if.then264:                                       ; preds = %lor.lhs.false260, %if.end255
  %204 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1264
  %end_of_entry265 = getelementptr inbounds %struct.lha, %struct.lha* %204, i32 0, i32 32, !dbg !1265
  store i8 1, i8* %end_of_entry265, align 4, !dbg !1266
  br label %if.end266, !dbg !1264

if.end266:                                        ; preds = %if.then264, %lor.lhs.false260
  %205 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1267
  %format_name = getelementptr inbounds %struct.lha, %struct.lha* %205, i32 0, i32 35, !dbg !1268
  %arraydecay267 = getelementptr inbounds [64 x i8], [64 x i8]* %format_name, i32 0, i32 0, !dbg !1267
  %206 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1269
  %method268 = getelementptr inbounds %struct.lha, %struct.lha* %206, i32 0, i32 6, !dbg !1270
  %arrayidx269 = getelementptr inbounds [3 x i8], [3 x i8]* %method268, i64 0, i64 0, !dbg !1269
  %207 = load i8, i8* %arrayidx269, align 1, !dbg !1269
  %conv270 = sext i8 %207 to i32, !dbg !1269
  %208 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1271
  %method271 = getelementptr inbounds %struct.lha, %struct.lha* %208, i32 0, i32 6, !dbg !1272
  %arrayidx272 = getelementptr inbounds [3 x i8], [3 x i8]* %method271, i64 0, i64 1, !dbg !1271
  %209 = load i8, i8* %arrayidx272, align 1, !dbg !1271
  %conv273 = sext i8 %209 to i32, !dbg !1271
  %210 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1273
  %method274 = getelementptr inbounds %struct.lha, %struct.lha* %210, i32 0, i32 6, !dbg !1274
  %arrayidx275 = getelementptr inbounds [3 x i8], [3 x i8]* %method274, i64 0, i64 2, !dbg !1273
  %211 = load i8, i8* %arrayidx275, align 1, !dbg !1273
  %conv276 = sext i8 %211 to i32, !dbg !1273
  %call277 = call i32 (i8*, i8*, ...) @sprintf(i8* %arraydecay267, i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.15, i32 0, i32 0), i32 %conv270, i32 %conv273, i32 %conv276) #8, !dbg !1275
  %212 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1276
  %format_name278 = getelementptr inbounds %struct.lha, %struct.lha* %212, i32 0, i32 35, !dbg !1277
  %arraydecay279 = getelementptr inbounds [64 x i8], [64 x i8]* %format_name278, i32 0, i32 0, !dbg !1276
  %213 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1278
  %archive280 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %213, i32 0, i32 0, !dbg !1279
  %archive_format_name281 = getelementptr inbounds %struct.archive, %struct.archive* %archive280, i32 0, i32 4, !dbg !1280
  store i8* %arraydecay279, i8** %archive_format_name281, align 8, !dbg !1281
  %214 = load i32, i32* %err, align 4, !dbg !1282
  store i32 %214, i32* %retval, align 4, !dbg !1283
  br label %return, !dbg !1283

return:                                           ; preds = %if.end266, %if.then193, %if.then172, %if.then136, %if.then117, %if.then108, %if.then49, %if.then44, %if.then36, %if.then31, %if.end12, %if.then11
  %215 = load i32, i32* %retval, align 4, !dbg !1284
  ret i32 %215, !dbg !1284
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_read_format_lha_read_data(%struct.archive_read* %a, i8** %buff, i64* %size, i64* %offset) #0 !dbg !470 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %buff.addr = alloca i8**, align 8
  %size.addr = alloca i64*, align 8
  %offset.addr = alloca i64*, align 8
  %lha = alloca %struct.lha*, align 8
  %r = alloca i32, align 4
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !1285, metadata !548), !dbg !1286
  store i8** %buff, i8*** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %buff.addr, metadata !1287, metadata !548), !dbg !1288
  store i64* %size, i64** %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %size.addr, metadata !1289, metadata !548), !dbg !1290
  store i64* %offset, i64** %offset.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %offset.addr, metadata !1291, metadata !548), !dbg !1292
  call void @llvm.dbg.declare(metadata %struct.lha** %lha, metadata !1293, metadata !548), !dbg !1294
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1295
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 13, !dbg !1296
  %1 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !1296
  %data = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %1, i32 0, i32 0, !dbg !1297
  %2 = load i8*, i8** %data, align 8, !dbg !1297
  %3 = bitcast i8* %2 to %struct.lha*, !dbg !1298
  store %struct.lha* %3, %struct.lha** %lha, align 8, !dbg !1294
  call void @llvm.dbg.declare(metadata i32* %r, metadata !1299, metadata !548), !dbg !1300
  %4 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1301
  %entry_unconsumed = getelementptr inbounds %struct.lha, %struct.lha* %4, i32 0, i32 2, !dbg !1303
  %5 = load i64, i64* %entry_unconsumed, align 8, !dbg !1303
  %tobool = icmp ne i64 %5, 0, !dbg !1301
  br i1 %tobool, label %if.then, label %if.end, !dbg !1304

if.then:                                          ; preds = %entry
  %6 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1305
  %7 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1307
  %entry_unconsumed1 = getelementptr inbounds %struct.lha, %struct.lha* %7, i32 0, i32 2, !dbg !1308
  %8 = load i64, i64* %entry_unconsumed1, align 8, !dbg !1308
  %call = call i64 @__archive_read_consume(%struct.archive_read* %6, i64 %8), !dbg !1309
  %9 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1310
  %entry_unconsumed2 = getelementptr inbounds %struct.lha, %struct.lha* %9, i32 0, i32 2, !dbg !1311
  store i64 0, i64* %entry_unconsumed2, align 8, !dbg !1312
  br label %if.end, !dbg !1313

if.end:                                           ; preds = %if.then, %entry
  %10 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1314
  %end_of_entry = getelementptr inbounds %struct.lha, %struct.lha* %10, i32 0, i32 32, !dbg !1316
  %11 = load i8, i8* %end_of_entry, align 4, !dbg !1316
  %tobool3 = icmp ne i8 %11, 0, !dbg !1314
  br i1 %tobool3, label %if.then4, label %if.end6, !dbg !1317

if.then4:                                         ; preds = %if.end
  %12 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1318
  %entry_offset = getelementptr inbounds %struct.lha, %struct.lha* %12, i32 0, i32 0, !dbg !1320
  %13 = load i64, i64* %entry_offset, align 8, !dbg !1320
  %14 = load i64*, i64** %offset.addr, align 8, !dbg !1321
  store i64 %13, i64* %14, align 8, !dbg !1322
  %15 = load i64*, i64** %size.addr, align 8, !dbg !1323
  store i64 0, i64* %15, align 8, !dbg !1324
  %16 = load i8**, i8*** %buff.addr, align 8, !dbg !1325
  store i8* null, i8** %16, align 8, !dbg !1326
  %17 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1327
  %call5 = call i32 @lha_end_of_entry(%struct.archive_read* %17), !dbg !1328
  store i32 %call5, i32* %retval, align 4, !dbg !1329
  br label %return, !dbg !1329

if.end6:                                          ; preds = %if.end
  %18 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1330
  %entry_is_compressed = getelementptr inbounds %struct.lha, %struct.lha* %18, i32 0, i32 34, !dbg !1332
  %19 = load i8, i8* %entry_is_compressed, align 2, !dbg !1332
  %tobool7 = icmp ne i8 %19, 0, !dbg !1330
  br i1 %tobool7, label %if.then8, label %if.else, !dbg !1333

if.then8:                                         ; preds = %if.end6
  %20 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1334
  %21 = load i8**, i8*** %buff.addr, align 8, !dbg !1335
  %22 = load i64*, i64** %size.addr, align 8, !dbg !1336
  %23 = load i64*, i64** %offset.addr, align 8, !dbg !1337
  %call9 = call i32 @lha_read_data_lzh(%struct.archive_read* %20, i8** %21, i64* %22, i64* %23), !dbg !1338
  store i32 %call9, i32* %r, align 4, !dbg !1339
  br label %if.end11, !dbg !1340

if.else:                                          ; preds = %if.end6
  %24 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1341
  %25 = load i8**, i8*** %buff.addr, align 8, !dbg !1342
  %26 = load i64*, i64** %size.addr, align 8, !dbg !1343
  %27 = load i64*, i64** %offset.addr, align 8, !dbg !1344
  %call10 = call i32 @lha_read_data_none(%struct.archive_read* %24, i8** %25, i64* %26, i64* %27), !dbg !1345
  store i32 %call10, i32* %r, align 4, !dbg !1346
  br label %if.end11

if.end11:                                         ; preds = %if.else, %if.then8
  %28 = load i32, i32* %r, align 4, !dbg !1347
  store i32 %28, i32* %retval, align 4, !dbg !1348
  br label %return, !dbg !1348

return:                                           ; preds = %if.end11, %if.then4
  %29 = load i32, i32* %retval, align 4, !dbg !1349
  ret i32 %29, !dbg !1349
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_read_format_lha_read_data_skip(%struct.archive_read* %a) #0 !dbg !509 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %lha = alloca %struct.lha*, align 8
  %bytes_skipped = alloca i64, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !1350, metadata !548), !dbg !1351
  call void @llvm.dbg.declare(metadata %struct.lha** %lha, metadata !1352, metadata !548), !dbg !1353
  call void @llvm.dbg.declare(metadata i64* %bytes_skipped, metadata !1354, metadata !548), !dbg !1355
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1356
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 13, !dbg !1357
  %1 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !1357
  %data = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %1, i32 0, i32 0, !dbg !1358
  %2 = load i8*, i8** %data, align 8, !dbg !1358
  %3 = bitcast i8* %2 to %struct.lha*, !dbg !1359
  store %struct.lha* %3, %struct.lha** %lha, align 8, !dbg !1360
  %4 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1361
  %entry_unconsumed = getelementptr inbounds %struct.lha, %struct.lha* %4, i32 0, i32 2, !dbg !1363
  %5 = load i64, i64* %entry_unconsumed, align 8, !dbg !1363
  %tobool = icmp ne i64 %5, 0, !dbg !1361
  br i1 %tobool, label %if.then, label %if.end, !dbg !1364

if.then:                                          ; preds = %entry
  %6 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1365
  %7 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1367
  %entry_unconsumed1 = getelementptr inbounds %struct.lha, %struct.lha* %7, i32 0, i32 2, !dbg !1368
  %8 = load i64, i64* %entry_unconsumed1, align 8, !dbg !1368
  %call = call i64 @__archive_read_consume(%struct.archive_read* %6, i64 %8), !dbg !1369
  %9 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1370
  %entry_unconsumed2 = getelementptr inbounds %struct.lha, %struct.lha* %9, i32 0, i32 2, !dbg !1371
  store i64 0, i64* %entry_unconsumed2, align 8, !dbg !1372
  br label %if.end, !dbg !1373

if.end:                                           ; preds = %if.then, %entry
  %10 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1374
  %end_of_entry_cleanup = getelementptr inbounds %struct.lha, %struct.lha* %10, i32 0, i32 33, !dbg !1376
  %11 = load i8, i8* %end_of_entry_cleanup, align 1, !dbg !1376
  %tobool3 = icmp ne i8 %11, 0, !dbg !1374
  br i1 %tobool3, label %if.then4, label %if.end5, !dbg !1377

if.then4:                                         ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !1378
  br label %return, !dbg !1378

if.end5:                                          ; preds = %if.end
  %12 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1379
  %13 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1380
  %entry_bytes_remaining = getelementptr inbounds %struct.lha, %struct.lha* %13, i32 0, i32 1, !dbg !1381
  %14 = load i64, i64* %entry_bytes_remaining, align 8, !dbg !1381
  %call6 = call i64 @__archive_read_consume(%struct.archive_read* %12, i64 %14), !dbg !1382
  store i64 %call6, i64* %bytes_skipped, align 8, !dbg !1383
  %15 = load i64, i64* %bytes_skipped, align 8, !dbg !1384
  %cmp = icmp slt i64 %15, 0, !dbg !1386
  br i1 %cmp, label %if.then7, label %if.end8, !dbg !1387

if.then7:                                         ; preds = %if.end5
  store i32 -30, i32* %retval, align 4, !dbg !1388
  br label %return, !dbg !1388

if.end8:                                          ; preds = %if.end5
  %16 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1389
  %end_of_entry = getelementptr inbounds %struct.lha, %struct.lha* %16, i32 0, i32 32, !dbg !1390
  store i8 1, i8* %end_of_entry, align 4, !dbg !1391
  %17 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1392
  %end_of_entry_cleanup9 = getelementptr inbounds %struct.lha, %struct.lha* %17, i32 0, i32 33, !dbg !1393
  store i8 1, i8* %end_of_entry_cleanup9, align 1, !dbg !1394
  store i32 0, i32* %retval, align 4, !dbg !1395
  br label %return, !dbg !1395

return:                                           ; preds = %if.end8, %if.then7, %if.then4
  %18 = load i32, i32* %retval, align 4, !dbg !1396
  ret i32 %18, !dbg !1396
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_read_format_lha_cleanup(%struct.archive_read* %a) #0 !dbg !510 {
entry:
  %a.addr = alloca %struct.archive_read*, align 8
  %lha = alloca %struct.lha*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !1397, metadata !548), !dbg !1398
  call void @llvm.dbg.declare(metadata %struct.lha** %lha, metadata !1399, metadata !548), !dbg !1400
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1401
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 13, !dbg !1402
  %1 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !1402
  %data = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %1, i32 0, i32 0, !dbg !1403
  %2 = load i8*, i8** %data, align 8, !dbg !1403
  %3 = bitcast i8* %2 to %struct.lha*, !dbg !1404
  store %struct.lha* %3, %struct.lha** %lha, align 8, !dbg !1400
  %4 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1405
  %strm = getelementptr inbounds %struct.lha, %struct.lha* %4, i32 0, i32 36, !dbg !1406
  call void @lzh_decode_free(%struct.lzh_stream* %strm), !dbg !1407
  %5 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1408
  %dirname = getelementptr inbounds %struct.lha, %struct.lha* %5, i32 0, i32 25, !dbg !1409
  call void @archive_string_free(%struct.archive_string* %dirname), !dbg !1410
  %6 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1411
  %filename = getelementptr inbounds %struct.lha, %struct.lha* %6, i32 0, i32 26, !dbg !1412
  call void @archive_string_free(%struct.archive_string* %filename), !dbg !1413
  %7 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1414
  %uname = getelementptr inbounds %struct.lha, %struct.lha* %7, i32 0, i32 19, !dbg !1415
  call void @archive_string_free(%struct.archive_string* %uname), !dbg !1416
  %8 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1417
  %gname = getelementptr inbounds %struct.lha, %struct.lha* %8, i32 0, i32 20, !dbg !1418
  call void @archive_string_free(%struct.archive_string* %gname), !dbg !1419
  %9 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1420
  %ws = getelementptr inbounds %struct.lha, %struct.lha* %9, i32 0, i32 27, !dbg !1421
  call void @archive_wstring_free(%struct.archive_wstring* %ws), !dbg !1422
  %10 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !1423
  %11 = bitcast %struct.lha* %10 to i8*, !dbg !1423
  call void @free(i8* %11) #8, !dbg !1424
  %12 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1425
  %format1 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %12, i32 0, i32 13, !dbg !1426
  %13 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format1, align 8, !dbg !1426
  %data2 = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %13, i32 0, i32 0, !dbg !1427
  store i8* null, i8** %data2, align 8, !dbg !1428
  ret i32 0, !dbg !1429
}

; Function Attrs: nounwind
declare void @free(i8*) #3

declare i8* @__archive_read_ahead(%struct.archive_read*, i64, i64*) #2

; Function Attrs: nounwind uwtable
define internal i64 @lha_check_header_format(i8* %h) #0 !dbg !421 {
entry:
  %retval = alloca i64, align 8
  %h.addr = alloca i8*, align 8
  %p = alloca i8*, align 8
  %next_skip_bytes = alloca i64, align 8
  store i8* %h, i8** %h.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %h.addr, metadata !1430, metadata !548), !dbg !1431
  call void @llvm.dbg.declare(metadata i8** %p, metadata !1432, metadata !548), !dbg !1433
  %0 = load i8*, i8** %h.addr, align 8, !dbg !1434
  store i8* %0, i8** %p, align 8, !dbg !1433
  call void @llvm.dbg.declare(metadata i64* %next_skip_bytes, metadata !1435, metadata !548), !dbg !1436
  %1 = load i8*, i8** %p, align 8, !dbg !1437
  %arrayidx = getelementptr inbounds i8, i8* %1, i64 5, !dbg !1437
  %2 = load i8, i8* %arrayidx, align 1, !dbg !1437
  %conv = zext i8 %2 to i32, !dbg !1437
  switch i32 %conv, label %sw.default [
    i32 48, label %sw.bb
    i32 49, label %sw.bb
    i32 50, label %sw.bb
    i32 51, label %sw.bb
    i32 52, label %sw.bb
    i32 53, label %sw.bb
    i32 54, label %sw.bb
    i32 55, label %sw.bb
    i32 100, label %sw.bb
    i32 115, label %sw.bb
    i32 104, label %sw.bb75
    i32 122, label %sw.bb76
    i32 108, label %sw.bb77
    i32 45, label %sw.bb78
  ], !dbg !1438

sw.bb:                                            ; preds = %entry, %entry, %entry, %entry, %entry, %entry, %entry, %entry, %entry, %entry
  store i64 4, i64* %next_skip_bytes, align 8, !dbg !1439
  %3 = load i8*, i8** %p, align 8, !dbg !1441
  %arrayidx1 = getelementptr inbounds i8, i8* %3, i64 0, !dbg !1441
  %4 = load i8, i8* %arrayidx1, align 1, !dbg !1441
  %conv2 = zext i8 %4 to i32, !dbg !1441
  %cmp = icmp eq i32 %conv2, 0, !dbg !1443
  br i1 %cmp, label %if.then, label %if.end, !dbg !1444

if.then:                                          ; preds = %sw.bb
  br label %sw.epilog, !dbg !1445

if.end:                                           ; preds = %sw.bb
  %5 = load i8*, i8** %p, align 8, !dbg !1446
  %arrayidx4 = getelementptr inbounds i8, i8* %5, i64 2, !dbg !1446
  %6 = load i8, i8* %arrayidx4, align 1, !dbg !1446
  %conv5 = zext i8 %6 to i32, !dbg !1446
  %cmp6 = icmp ne i32 %conv5, 45, !dbg !1448
  br i1 %cmp6, label %if.then17, label %lor.lhs.false, !dbg !1449

lor.lhs.false:                                    ; preds = %if.end
  %7 = load i8*, i8** %p, align 8, !dbg !1450
  %arrayidx8 = getelementptr inbounds i8, i8* %7, i64 3, !dbg !1450
  %8 = load i8, i8* %arrayidx8, align 1, !dbg !1450
  %conv9 = zext i8 %8 to i32, !dbg !1450
  %cmp10 = icmp ne i32 %conv9, 108, !dbg !1452
  br i1 %cmp10, label %if.then17, label %lor.lhs.false12, !dbg !1453

lor.lhs.false12:                                  ; preds = %lor.lhs.false
  %9 = load i8*, i8** %p, align 8, !dbg !1454
  %arrayidx13 = getelementptr inbounds i8, i8* %9, i64 6, !dbg !1454
  %10 = load i8, i8* %arrayidx13, align 1, !dbg !1454
  %conv14 = zext i8 %10 to i32, !dbg !1454
  %cmp15 = icmp ne i32 %conv14, 45, !dbg !1455
  br i1 %cmp15, label %if.then17, label %if.end18, !dbg !1456

if.then17:                                        ; preds = %lor.lhs.false12, %lor.lhs.false, %if.end
  br label %sw.epilog, !dbg !1458

if.end18:                                         ; preds = %lor.lhs.false12
  %11 = load i8*, i8** %p, align 8, !dbg !1459
  %arrayidx19 = getelementptr inbounds i8, i8* %11, i64 4, !dbg !1459
  %12 = load i8, i8* %arrayidx19, align 1, !dbg !1459
  %conv20 = zext i8 %12 to i32, !dbg !1459
  %cmp21 = icmp eq i32 %conv20, 104, !dbg !1461
  br i1 %cmp21, label %if.then23, label %if.end46, !dbg !1462

if.then23:                                        ; preds = %if.end18
  %13 = load i8*, i8** %p, align 8, !dbg !1463
  %arrayidx24 = getelementptr inbounds i8, i8* %13, i64 5, !dbg !1463
  %14 = load i8, i8* %arrayidx24, align 1, !dbg !1463
  %conv25 = zext i8 %14 to i32, !dbg !1463
  %cmp26 = icmp eq i32 %conv25, 115, !dbg !1466
  br i1 %cmp26, label %if.then28, label %if.end29, !dbg !1467

if.then28:                                        ; preds = %if.then23
  br label %sw.epilog, !dbg !1468

if.end29:                                         ; preds = %if.then23
  %15 = load i8*, i8** %p, align 8, !dbg !1469
  %arrayidx30 = getelementptr inbounds i8, i8* %15, i64 20, !dbg !1469
  %16 = load i8, i8* %arrayidx30, align 1, !dbg !1469
  %conv31 = zext i8 %16 to i32, !dbg !1469
  %cmp32 = icmp eq i32 %conv31, 0, !dbg !1471
  br i1 %cmp32, label %if.then34, label %if.end35, !dbg !1472

if.then34:                                        ; preds = %if.end29
  store i64 0, i64* %retval, align 8, !dbg !1473
  br label %return, !dbg !1473

if.end35:                                         ; preds = %if.end29
  %17 = load i8*, i8** %p, align 8, !dbg !1474
  %arrayidx36 = getelementptr inbounds i8, i8* %17, i64 20, !dbg !1474
  %18 = load i8, i8* %arrayidx36, align 1, !dbg !1474
  %conv37 = zext i8 %18 to i32, !dbg !1474
  %cmp38 = icmp sle i32 %conv37, 3, !dbg !1476
  br i1 %cmp38, label %land.lhs.true, label %if.end45, !dbg !1477

land.lhs.true:                                    ; preds = %if.end35
  %19 = load i8*, i8** %p, align 8, !dbg !1478
  %arrayidx40 = getelementptr inbounds i8, i8* %19, i64 19, !dbg !1478
  %20 = load i8, i8* %arrayidx40, align 1, !dbg !1478
  %conv41 = zext i8 %20 to i32, !dbg !1478
  %cmp42 = icmp eq i32 %conv41, 32, !dbg !1480
  br i1 %cmp42, label %if.then44, label %if.end45, !dbg !1481

if.then44:                                        ; preds = %land.lhs.true
  store i64 0, i64* %retval, align 8, !dbg !1482
  br label %return, !dbg !1482

if.end45:                                         ; preds = %land.lhs.true, %if.end35
  br label %if.end46, !dbg !1483

if.end46:                                         ; preds = %if.end45, %if.end18
  %21 = load i8*, i8** %p, align 8, !dbg !1484
  %arrayidx47 = getelementptr inbounds i8, i8* %21, i64 4, !dbg !1484
  %22 = load i8, i8* %arrayidx47, align 1, !dbg !1484
  %conv48 = zext i8 %22 to i32, !dbg !1484
  %cmp49 = icmp eq i32 %conv48, 122, !dbg !1486
  br i1 %cmp49, label %if.then51, label %if.end74, !dbg !1487

if.then51:                                        ; preds = %if.end46
  %23 = load i8*, i8** %p, align 8, !dbg !1488
  %arrayidx52 = getelementptr inbounds i8, i8* %23, i64 20, !dbg !1488
  %24 = load i8, i8* %arrayidx52, align 1, !dbg !1488
  %conv53 = zext i8 %24 to i32, !dbg !1488
  %cmp54 = icmp ne i32 %conv53, 0, !dbg !1491
  br i1 %cmp54, label %if.then56, label %if.end57, !dbg !1492

if.then56:                                        ; preds = %if.then51
  br label %sw.epilog, !dbg !1493

if.end57:                                         ; preds = %if.then51
  %25 = load i8*, i8** %p, align 8, !dbg !1494
  %arrayidx58 = getelementptr inbounds i8, i8* %25, i64 5, !dbg !1494
  %26 = load i8, i8* %arrayidx58, align 1, !dbg !1494
  %conv59 = zext i8 %26 to i32, !dbg !1494
  %cmp60 = icmp eq i32 %conv59, 115, !dbg !1496
  br i1 %cmp60, label %if.then72, label %lor.lhs.false62, !dbg !1497

lor.lhs.false62:                                  ; preds = %if.end57
  %27 = load i8*, i8** %p, align 8, !dbg !1498
  %arrayidx63 = getelementptr inbounds i8, i8* %27, i64 5, !dbg !1498
  %28 = load i8, i8* %arrayidx63, align 1, !dbg !1498
  %conv64 = zext i8 %28 to i32, !dbg !1498
  %cmp65 = icmp eq i32 %conv64, 52, !dbg !1500
  br i1 %cmp65, label %if.then72, label %lor.lhs.false67, !dbg !1501

lor.lhs.false67:                                  ; preds = %lor.lhs.false62
  %29 = load i8*, i8** %p, align 8, !dbg !1502
  %arrayidx68 = getelementptr inbounds i8, i8* %29, i64 5, !dbg !1502
  %30 = load i8, i8* %arrayidx68, align 1, !dbg !1502
  %conv69 = zext i8 %30 to i32, !dbg !1502
  %cmp70 = icmp eq i32 %conv69, 53, !dbg !1503
  br i1 %cmp70, label %if.then72, label %if.end73, !dbg !1504

if.then72:                                        ; preds = %lor.lhs.false67, %lor.lhs.false62, %if.end57
  store i64 0, i64* %retval, align 8, !dbg !1506
  br label %return, !dbg !1506

if.end73:                                         ; preds = %lor.lhs.false67
  br label %if.end74, !dbg !1507

if.end74:                                         ; preds = %if.end73, %if.end46
  br label %sw.epilog, !dbg !1508

sw.bb75:                                          ; preds = %entry
  store i64 1, i64* %next_skip_bytes, align 8, !dbg !1509
  br label %sw.epilog, !dbg !1510

sw.bb76:                                          ; preds = %entry
  store i64 1, i64* %next_skip_bytes, align 8, !dbg !1511
  br label %sw.epilog, !dbg !1512

sw.bb77:                                          ; preds = %entry
  store i64 2, i64* %next_skip_bytes, align 8, !dbg !1513
  br label %sw.epilog, !dbg !1514

sw.bb78:                                          ; preds = %entry
  store i64 3, i64* %next_skip_bytes, align 8, !dbg !1515
  br label %sw.epilog, !dbg !1516

sw.default:                                       ; preds = %entry
  store i64 4, i64* %next_skip_bytes, align 8, !dbg !1517
  br label %sw.epilog, !dbg !1518

sw.epilog:                                        ; preds = %sw.default, %sw.bb78, %sw.bb77, %sw.bb76, %sw.bb75, %if.end74, %if.then56, %if.then28, %if.then17, %if.then
  %31 = load i64, i64* %next_skip_bytes, align 8, !dbg !1519
  store i64 %31, i64* %retval, align 8, !dbg !1520
  br label %return, !dbg !1520

return:                                           ; preds = %sw.epilog, %if.then72, %if.then44, %if.then34
  %32 = load i64, i64* %retval, align 8, !dbg !1521
  ret i64 %32, !dbg !1521
}

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #4

declare %struct.archive_string_conv* @archive_string_conversion_from_charset(%struct.archive*, i8*, i32) #2

; Function Attrs: nounwind uwtable
define internal void @lha_crc16_init() #0 !dbg !426 {
entry:
  %i = alloca i32, align 4
  %j = alloca i32, align 4
  %crc = alloca i16, align 2
  call void @llvm.dbg.declare(metadata i32* %i, metadata !1522, metadata !548), !dbg !1523
  %0 = load i32, i32* @lha_crc16_init.crc16init, align 4, !dbg !1524
  %tobool = icmp ne i32 %0, 0, !dbg !1524
  br i1 %tobool, label %if.then, label %if.end, !dbg !1526

if.then:                                          ; preds = %entry
  br label %for.end30, !dbg !1527

if.end:                                           ; preds = %entry
  store i32 1, i32* @lha_crc16_init.crc16init, align 4, !dbg !1528
  store i32 0, i32* %i, align 4, !dbg !1529
  br label %for.cond, !dbg !1531

for.cond:                                         ; preds = %for.inc7, %if.end
  %1 = load i32, i32* %i, align 4, !dbg !1532
  %cmp = icmp ult i32 %1, 256, !dbg !1535
  br i1 %cmp, label %for.body, label %for.end8, !dbg !1536

for.body:                                         ; preds = %for.cond
  call void @llvm.dbg.declare(metadata i32* %j, metadata !1537, metadata !548), !dbg !1539
  call void @llvm.dbg.declare(metadata i16* %crc, metadata !1540, metadata !548), !dbg !1541
  %2 = load i32, i32* %i, align 4, !dbg !1542
  %conv = trunc i32 %2 to i16, !dbg !1543
  store i16 %conv, i16* %crc, align 2, !dbg !1541
  store i32 8, i32* %j, align 4, !dbg !1544
  br label %for.cond1, !dbg !1546

for.cond1:                                        ; preds = %for.inc, %for.body
  %3 = load i32, i32* %j, align 4, !dbg !1547
  %tobool2 = icmp ne i32 %3, 0, !dbg !1550
  br i1 %tobool2, label %for.body3, label %for.end, !dbg !1550

for.body3:                                        ; preds = %for.cond1
  %4 = load i16, i16* %crc, align 2, !dbg !1551
  %conv4 = zext i16 %4 to i32, !dbg !1551
  %shr = ashr i32 %conv4, 1, !dbg !1552
  %5 = load i16, i16* %crc, align 2, !dbg !1553
  %conv5 = zext i16 %5 to i32, !dbg !1553
  %and = and i32 %conv5, 1, !dbg !1554
  %mul = mul nsw i32 %and, 40961, !dbg !1555
  %xor = xor i32 %shr, %mul, !dbg !1556
  %conv6 = trunc i32 %xor to i16, !dbg !1557
  store i16 %conv6, i16* %crc, align 2, !dbg !1558
  br label %for.inc, !dbg !1559

for.inc:                                          ; preds = %for.body3
  %6 = load i32, i32* %j, align 4, !dbg !1560
  %dec = add i32 %6, -1, !dbg !1560
  store i32 %dec, i32* %j, align 4, !dbg !1560
  br label %for.cond1, !dbg !1562

for.end:                                          ; preds = %for.cond1
  %7 = load i16, i16* %crc, align 2, !dbg !1563
  %8 = load i32, i32* %i, align 4, !dbg !1564
  %idxprom = zext i32 %8 to i64, !dbg !1565
  %arrayidx = getelementptr inbounds [256 x i16], [256 x i16]* getelementptr inbounds ([2 x [256 x i16]], [2 x [256 x i16]]* @crc16tbl, i64 0, i64 0), i64 0, i64 %idxprom, !dbg !1565
  store i16 %7, i16* %arrayidx, align 2, !dbg !1566
  br label %for.inc7, !dbg !1567

for.inc7:                                         ; preds = %for.end
  %9 = load i32, i32* %i, align 4, !dbg !1568
  %inc = add i32 %9, 1, !dbg !1568
  store i32 %inc, i32* %i, align 4, !dbg !1568
  br label %for.cond, !dbg !1570

for.end8:                                         ; preds = %for.cond
  store i32 0, i32* %i, align 4, !dbg !1571
  br label %for.cond9, !dbg !1573

for.cond9:                                        ; preds = %for.inc28, %for.end8
  %10 = load i32, i32* %i, align 4, !dbg !1574
  %cmp10 = icmp ult i32 %10, 256, !dbg !1577
  br i1 %cmp10, label %for.body12, label %for.end30, !dbg !1578

for.body12:                                       ; preds = %for.cond9
  %11 = load i32, i32* %i, align 4, !dbg !1579
  %idxprom13 = zext i32 %11 to i64, !dbg !1581
  %arrayidx14 = getelementptr inbounds [256 x i16], [256 x i16]* getelementptr inbounds ([2 x [256 x i16]], [2 x [256 x i16]]* @crc16tbl, i64 0, i64 0), i64 0, i64 %idxprom13, !dbg !1581
  %12 = load i16, i16* %arrayidx14, align 2, !dbg !1581
  %conv15 = zext i16 %12 to i32, !dbg !1581
  %shr16 = ashr i32 %conv15, 8, !dbg !1582
  %13 = load i32, i32* %i, align 4, !dbg !1583
  %idxprom17 = zext i32 %13 to i64, !dbg !1584
  %arrayidx18 = getelementptr inbounds [256 x i16], [256 x i16]* getelementptr inbounds ([2 x [256 x i16]], [2 x [256 x i16]]* @crc16tbl, i64 0, i64 0), i64 0, i64 %idxprom17, !dbg !1584
  %14 = load i16, i16* %arrayidx18, align 2, !dbg !1584
  %conv19 = zext i16 %14 to i32, !dbg !1584
  %and20 = and i32 %conv19, 255, !dbg !1585
  %idxprom21 = sext i32 %and20 to i64, !dbg !1586
  %arrayidx22 = getelementptr inbounds [256 x i16], [256 x i16]* getelementptr inbounds ([2 x [256 x i16]], [2 x [256 x i16]]* @crc16tbl, i64 0, i64 0), i64 0, i64 %idxprom21, !dbg !1586
  %15 = load i16, i16* %arrayidx22, align 2, !dbg !1586
  %conv23 = zext i16 %15 to i32, !dbg !1586
  %xor24 = xor i32 %shr16, %conv23, !dbg !1587
  %conv25 = trunc i32 %xor24 to i16, !dbg !1588
  %16 = load i32, i32* %i, align 4, !dbg !1589
  %idxprom26 = zext i32 %16 to i64, !dbg !1590
  %arrayidx27 = getelementptr inbounds [256 x i16], [256 x i16]* getelementptr inbounds ([2 x [256 x i16]], [2 x [256 x i16]]* @crc16tbl, i64 0, i64 1), i64 0, i64 %idxprom26, !dbg !1590
  store i16 %conv25, i16* %arrayidx27, align 2, !dbg !1591
  br label %for.inc28, !dbg !1592

for.inc28:                                        ; preds = %for.body12
  %17 = load i32, i32* %i, align 4, !dbg !1593
  %inc29 = add i32 %17, 1, !dbg !1593
  store i32 %inc29, i32* %i, align 4, !dbg !1593
  br label %for.cond9, !dbg !1595

for.end30:                                        ; preds = %if.then, %for.cond9
  ret void, !dbg !1596
}

; Function Attrs: nounwind uwtable
define internal i32 @truncated_error(%struct.archive_read* %a) #0 !dbg !429 {
entry:
  %a.addr = alloca %struct.archive_read*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !1597, metadata !548), !dbg !1598
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1599
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 0, !dbg !1600
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 84, i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.16, i32 0, i32 0)), !dbg !1601
  ret i32 -30, !dbg !1602
}

; Function Attrs: nounwind uwtable
define internal i32 @lha_skip_sfx(%struct.archive_read* %a) #0 !dbg !430 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %h = alloca i8*, align 8
  %p = alloca i8*, align 8
  %q = alloca i8*, align 8
  %next = alloca i64, align 8
  %skip = alloca i64, align 8
  %bytes = alloca i64, align 8
  %window = alloca i64, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !1603, metadata !548), !dbg !1604
  call void @llvm.dbg.declare(metadata i8** %h, metadata !1605, metadata !548), !dbg !1606
  call void @llvm.dbg.declare(metadata i8** %p, metadata !1607, metadata !548), !dbg !1608
  call void @llvm.dbg.declare(metadata i8** %q, metadata !1609, metadata !548), !dbg !1610
  call void @llvm.dbg.declare(metadata i64* %next, metadata !1611, metadata !548), !dbg !1612
  call void @llvm.dbg.declare(metadata i64* %skip, metadata !1613, metadata !548), !dbg !1614
  call void @llvm.dbg.declare(metadata i64* %bytes, metadata !1615, metadata !548), !dbg !1616
  call void @llvm.dbg.declare(metadata i64* %window, metadata !1617, metadata !548), !dbg !1618
  store i64 4096, i64* %window, align 8, !dbg !1619
  br label %for.cond, !dbg !1620

for.cond:                                         ; preds = %while.end, %if.end, %entry
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1621
  %1 = load i64, i64* %window, align 8, !dbg !1625
  %call = call i8* @__archive_read_ahead(%struct.archive_read* %0, i64 %1, i64* %bytes), !dbg !1626
  store i8* %call, i8** %h, align 8, !dbg !1627
  %2 = load i8*, i8** %h, align 8, !dbg !1628
  %cmp = icmp eq i8* %2, null, !dbg !1630
  br i1 %cmp, label %if.then, label %if.end3, !dbg !1631

if.then:                                          ; preds = %for.cond
  %3 = load i64, i64* %window, align 8, !dbg !1632
  %shr = ashr i64 %3, 1, !dbg !1632
  store i64 %shr, i64* %window, align 8, !dbg !1632
  %4 = load i64, i64* %window, align 8, !dbg !1634
  %cmp1 = icmp slt i64 %4, 25, !dbg !1636
  br i1 %cmp1, label %if.then2, label %if.end, !dbg !1637

if.then2:                                         ; preds = %if.then
  br label %fatal, !dbg !1638

if.end:                                           ; preds = %if.then
  br label %for.cond, !dbg !1639

if.end3:                                          ; preds = %for.cond
  %5 = load i64, i64* %bytes, align 8, !dbg !1640
  %cmp4 = icmp slt i64 %5, 22, !dbg !1642
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !1643

if.then5:                                         ; preds = %if.end3
  br label %fatal, !dbg !1644

if.end6:                                          ; preds = %if.end3
  %6 = load i8*, i8** %h, align 8, !dbg !1645
  store i8* %6, i8** %p, align 8, !dbg !1646
  %7 = load i8*, i8** %p, align 8, !dbg !1647
  %8 = load i64, i64* %bytes, align 8, !dbg !1648
  %add.ptr = getelementptr inbounds i8, i8* %7, i64 %8, !dbg !1649
  store i8* %add.ptr, i8** %q, align 8, !dbg !1650
  br label %while.cond, !dbg !1651

while.cond:                                       ; preds = %if.end13, %if.end6
  %9 = load i8*, i8** %p, align 8, !dbg !1652
  %add.ptr7 = getelementptr inbounds i8, i8* %9, i64 22, !dbg !1654
  %10 = load i8*, i8** %q, align 8, !dbg !1655
  %cmp8 = icmp ult i8* %add.ptr7, %10, !dbg !1656
  br i1 %cmp8, label %while.body, label %while.end, !dbg !1657

while.body:                                       ; preds = %while.cond
  %11 = load i8*, i8** %p, align 8, !dbg !1658
  %call9 = call i64 @lha_check_header_format(i8* %11), !dbg !1661
  store i64 %call9, i64* %next, align 8, !dbg !1662
  %cmp10 = icmp eq i64 %call9, 0, !dbg !1663
  br i1 %cmp10, label %if.then11, label %if.end13, !dbg !1664

if.then11:                                        ; preds = %while.body
  %12 = load i8*, i8** %p, align 8, !dbg !1665
  %13 = load i8*, i8** %h, align 8, !dbg !1667
  %sub.ptr.lhs.cast = ptrtoint i8* %12 to i64, !dbg !1668
  %sub.ptr.rhs.cast = ptrtoint i8* %13 to i64, !dbg !1668
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !1668
  store i64 %sub.ptr.sub, i64* %skip, align 8, !dbg !1669
  %14 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1670
  %15 = load i64, i64* %skip, align 8, !dbg !1671
  %call12 = call i64 @__archive_read_consume(%struct.archive_read* %14, i64 %15), !dbg !1672
  store i32 0, i32* %retval, align 4, !dbg !1673
  br label %return, !dbg !1673

if.end13:                                         ; preds = %while.body
  %16 = load i64, i64* %next, align 8, !dbg !1674
  %17 = load i8*, i8** %p, align 8, !dbg !1675
  %add.ptr14 = getelementptr inbounds i8, i8* %17, i64 %16, !dbg !1675
  store i8* %add.ptr14, i8** %p, align 8, !dbg !1675
  br label %while.cond, !dbg !1676

while.end:                                        ; preds = %while.cond
  %18 = load i8*, i8** %p, align 8, !dbg !1678
  %19 = load i8*, i8** %h, align 8, !dbg !1679
  %sub.ptr.lhs.cast15 = ptrtoint i8* %18 to i64, !dbg !1680
  %sub.ptr.rhs.cast16 = ptrtoint i8* %19 to i64, !dbg !1680
  %sub.ptr.sub17 = sub i64 %sub.ptr.lhs.cast15, %sub.ptr.rhs.cast16, !dbg !1680
  store i64 %sub.ptr.sub17, i64* %skip, align 8, !dbg !1681
  %20 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1682
  %21 = load i64, i64* %skip, align 8, !dbg !1683
  %call18 = call i64 @__archive_read_consume(%struct.archive_read* %20, i64 %21), !dbg !1684
  br label %for.cond, !dbg !1685

fatal:                                            ; preds = %if.then5, %if.then2
  %22 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1687
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %22, i32 0, i32 0, !dbg !1688
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 84, i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.17, i32 0, i32 0)), !dbg !1689
  store i32 -30, i32* %retval, align 4, !dbg !1690
  br label %return, !dbg !1690

return:                                           ; preds = %fatal, %if.then11
  %23 = load i32, i32* %retval, align 4, !dbg !1691
  ret i32 %23, !dbg !1691
}

; Function Attrs: nounwind readonly
declare i32 @memcmp(i8*, i8*, i64) #4

; Function Attrs: nounwind uwtable
define internal i32 @lha_read_file_header_0(%struct.archive_read* %a, %struct.lha* %lha) #0 !dbg !431 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %lha.addr = alloca %struct.lha*, align 8
  %p = alloca i8*, align 8
  %extdsize = alloca i32, align 4
  %namelen = alloca i32, align 4
  %headersum = alloca i8, align 1
  %sum_calculated = alloca i8, align 1
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !1692, metadata !548), !dbg !1693
  store %struct.lha* %lha, %struct.lha** %lha.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lha** %lha.addr, metadata !1694, metadata !548), !dbg !1695
  call void @llvm.dbg.declare(metadata i8** %p, metadata !1696, metadata !548), !dbg !1697
  call void @llvm.dbg.declare(metadata i32* %extdsize, metadata !1698, metadata !548), !dbg !1699
  call void @llvm.dbg.declare(metadata i32* %namelen, metadata !1700, metadata !548), !dbg !1701
  call void @llvm.dbg.declare(metadata i8* %headersum, metadata !1702, metadata !548), !dbg !1703
  call void @llvm.dbg.declare(metadata i8* %sum_calculated, metadata !1704, metadata !548), !dbg !1705
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1706
  %call = call i8* @__archive_read_ahead(%struct.archive_read* %0, i64 24, i64* null), !dbg !1708
  store i8* %call, i8** %p, align 8, !dbg !1709
  %cmp = icmp eq i8* %call, null, !dbg !1710
  br i1 %cmp, label %if.then, label %if.end, !dbg !1711

if.then:                                          ; preds = %entry
  %1 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1712
  %call1 = call i32 @truncated_error(%struct.archive_read* %1), !dbg !1713
  store i32 %call1, i32* %retval, align 4, !dbg !1714
  br label %return, !dbg !1714

if.end:                                           ; preds = %entry
  %2 = load i8*, i8** %p, align 8, !dbg !1715
  %arrayidx = getelementptr inbounds i8, i8* %2, i64 0, !dbg !1715
  %3 = load i8, i8* %arrayidx, align 1, !dbg !1715
  %conv = zext i8 %3 to i32, !dbg !1715
  %add = add nsw i32 %conv, 2, !dbg !1716
  %conv2 = sext i32 %add to i64, !dbg !1715
  %4 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !1717
  %header_size = getelementptr inbounds %struct.lha, %struct.lha* %4, i32 0, i32 4, !dbg !1718
  store i64 %conv2, i64* %header_size, align 8, !dbg !1719
  %5 = load i8*, i8** %p, align 8, !dbg !1720
  %arrayidx3 = getelementptr inbounds i8, i8* %5, i64 1, !dbg !1720
  %6 = load i8, i8* %arrayidx3, align 1, !dbg !1720
  store i8 %6, i8* %headersum, align 1, !dbg !1721
  %7 = load i8*, i8** %p, align 8, !dbg !1722
  %add.ptr = getelementptr inbounds i8, i8* %7, i64 7, !dbg !1723
  %call4 = call i32 @archive_le32dec(i8* %add.ptr), !dbg !1724
  %conv5 = zext i32 %call4 to i64, !dbg !1724
  %8 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !1725
  %compsize = getelementptr inbounds %struct.lha, %struct.lha* %8, i32 0, i32 7, !dbg !1726
  store i64 %conv5, i64* %compsize, align 8, !dbg !1727
  %9 = load i8*, i8** %p, align 8, !dbg !1728
  %add.ptr6 = getelementptr inbounds i8, i8* %9, i64 11, !dbg !1729
  %call7 = call i32 @archive_le32dec(i8* %add.ptr6), !dbg !1730
  %conv8 = zext i32 %call7 to i64, !dbg !1730
  %10 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !1731
  %origsize = getelementptr inbounds %struct.lha, %struct.lha* %10, i32 0, i32 8, !dbg !1732
  store i64 %conv8, i64* %origsize, align 8, !dbg !1733
  %11 = load i8*, i8** %p, align 8, !dbg !1734
  %add.ptr9 = getelementptr inbounds i8, i8* %11, i64 15, !dbg !1735
  %call10 = call i64 @lha_dos_time(i8* %add.ptr9), !dbg !1736
  %12 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !1737
  %mtime = getelementptr inbounds %struct.lha, %struct.lha* %12, i32 0, i32 12, !dbg !1738
  store i64 %call10, i64* %mtime, align 8, !dbg !1739
  %13 = load i8*, i8** %p, align 8, !dbg !1740
  %arrayidx11 = getelementptr inbounds i8, i8* %13, i64 21, !dbg !1740
  %14 = load i8, i8* %arrayidx11, align 1, !dbg !1740
  %conv12 = zext i8 %14 to i32, !dbg !1740
  store i32 %conv12, i32* %namelen, align 4, !dbg !1741
  %15 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !1742
  %header_size13 = getelementptr inbounds %struct.lha, %struct.lha* %15, i32 0, i32 4, !dbg !1743
  %16 = load i64, i64* %header_size13, align 8, !dbg !1743
  %conv14 = trunc i64 %16 to i32, !dbg !1744
  %sub = sub nsw i32 %conv14, 24, !dbg !1745
  %17 = load i32, i32* %namelen, align 4, !dbg !1746
  %sub15 = sub nsw i32 %sub, %17, !dbg !1747
  store i32 %sub15, i32* %extdsize, align 4, !dbg !1748
  %18 = load i32, i32* %namelen, align 4, !dbg !1749
  %cmp16 = icmp sgt i32 %18, 221, !dbg !1751
  br i1 %cmp16, label %land.lhs.true, label %lor.lhs.false, !dbg !1752

lor.lhs.false:                                    ; preds = %if.end
  %19 = load i32, i32* %extdsize, align 4, !dbg !1753
  %cmp18 = icmp slt i32 %19, 0, !dbg !1755
  br i1 %cmp18, label %land.lhs.true, label %if.end23, !dbg !1756

land.lhs.true:                                    ; preds = %lor.lhs.false, %if.end
  %20 = load i32, i32* %extdsize, align 4, !dbg !1757
  %cmp20 = icmp ne i32 %20, -2, !dbg !1759
  br i1 %cmp20, label %if.then22, label %if.end23, !dbg !1760

if.then22:                                        ; preds = %land.lhs.true
  %21 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1761
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %21, i32 0, i32 0, !dbg !1763
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 84, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.18, i32 0, i32 0)), !dbg !1764
  store i32 -30, i32* %retval, align 4, !dbg !1765
  br label %return, !dbg !1765

if.end23:                                         ; preds = %land.lhs.true, %lor.lhs.false
  %22 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1766
  %23 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !1768
  %header_size24 = getelementptr inbounds %struct.lha, %struct.lha* %23, i32 0, i32 4, !dbg !1769
  %24 = load i64, i64* %header_size24, align 8, !dbg !1769
  %call25 = call i8* @__archive_read_ahead(%struct.archive_read* %22, i64 %24, i64* null), !dbg !1770
  store i8* %call25, i8** %p, align 8, !dbg !1771
  %cmp26 = icmp eq i8* %call25, null, !dbg !1772
  br i1 %cmp26, label %if.then28, label %if.end30, !dbg !1773

if.then28:                                        ; preds = %if.end23
  %25 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1774
  %call29 = call i32 @truncated_error(%struct.archive_read* %25), !dbg !1775
  store i32 %call29, i32* %retval, align 4, !dbg !1776
  br label %return, !dbg !1776

if.end30:                                         ; preds = %if.end23
  %26 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !1777
  %filename = getelementptr inbounds %struct.lha, %struct.lha* %26, i32 0, i32 26, !dbg !1777
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %filename, i32 0, i32 1, !dbg !1777
  store i64 0, i64* %length, align 8, !dbg !1777
  %27 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !1777
  %filename31 = getelementptr inbounds %struct.lha, %struct.lha* %27, i32 0, i32 26, !dbg !1777
  %28 = load i8*, i8** %p, align 8, !dbg !1777
  %add.ptr32 = getelementptr inbounds i8, i8* %28, i64 22, !dbg !1777
  %29 = load i32, i32* %namelen, align 4, !dbg !1777
  %conv33 = sext i32 %29 to i64, !dbg !1777
  %call34 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %filename31, i8* %add.ptr32, i64 %conv33), !dbg !1777
  %30 = load i32, i32* %extdsize, align 4, !dbg !1778
  %cmp35 = icmp sge i32 %30, 0, !dbg !1780
  br i1 %cmp35, label %if.then37, label %if.end41, !dbg !1781

if.then37:                                        ; preds = %if.end30
  %31 = load i8*, i8** %p, align 8, !dbg !1782
  %add.ptr38 = getelementptr inbounds i8, i8* %31, i64 22, !dbg !1784
  %32 = load i32, i32* %namelen, align 4, !dbg !1785
  %idx.ext = sext i32 %32 to i64, !dbg !1786
  %add.ptr39 = getelementptr inbounds i8, i8* %add.ptr38, i64 %idx.ext, !dbg !1786
  %call40 = call zeroext i16 @archive_le16dec(i8* %add.ptr39), !dbg !1787
  %33 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !1788
  %crc = getelementptr inbounds %struct.lha, %struct.lha* %33, i32 0, i32 22, !dbg !1789
  store i16 %call40, i16* %crc, align 2, !dbg !1790
  %34 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !1791
  %setflag = getelementptr inbounds %struct.lha, %struct.lha* %34, i32 0, i32 9, !dbg !1792
  %35 = load i32, i32* %setflag, align 8, !dbg !1793
  %or = or i32 %35, 8, !dbg !1793
  store i32 %or, i32* %setflag, align 8, !dbg !1793
  br label %if.end41, !dbg !1794

if.end41:                                         ; preds = %if.then37, %if.end30
  %36 = load i8*, i8** %p, align 8, !dbg !1795
  %37 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !1796
  %header_size42 = getelementptr inbounds %struct.lha, %struct.lha* %37, i32 0, i32 4, !dbg !1797
  %38 = load i64, i64* %header_size42, align 8, !dbg !1797
  %sub43 = sub i64 %38, 2, !dbg !1798
  %call44 = call zeroext i8 @lha_calcsum(i8 zeroext 0, i8* %36, i32 2, i64 %sub43), !dbg !1799
  store i8 %call44, i8* %sum_calculated, align 1, !dbg !1800
  %39 = load i32, i32* %extdsize, align 4, !dbg !1801
  %cmp45 = icmp sgt i32 %39, 0, !dbg !1803
  br i1 %cmp45, label %if.then47, label %if.end76, !dbg !1804

if.then47:                                        ; preds = %if.end41
  %40 = load i32, i32* %namelen, align 4, !dbg !1805
  %add48 = add nsw i32 22, %40, !dbg !1807
  %add49 = add nsw i32 %add48, 2, !dbg !1808
  %41 = load i8*, i8** %p, align 8, !dbg !1809
  %idx.ext50 = sext i32 %add49 to i64, !dbg !1809
  %add.ptr51 = getelementptr inbounds i8, i8* %41, i64 %idx.ext50, !dbg !1809
  store i8* %add.ptr51, i8** %p, align 8, !dbg !1809
  %42 = load i8*, i8** %p, align 8, !dbg !1810
  %arrayidx52 = getelementptr inbounds i8, i8* %42, i64 0, !dbg !1810
  %43 = load i8, i8* %arrayidx52, align 1, !dbg !1810
  %conv53 = zext i8 %43 to i32, !dbg !1810
  %cmp54 = icmp eq i32 %conv53, 85, !dbg !1812
  br i1 %cmp54, label %land.lhs.true56, label %if.end75, !dbg !1813

land.lhs.true56:                                  ; preds = %if.then47
  %44 = load i32, i32* %extdsize, align 4, !dbg !1814
  %cmp57 = icmp eq i32 %44, 12, !dbg !1816
  br i1 %cmp57, label %if.then59, label %if.end75, !dbg !1817

if.then59:                                        ; preds = %land.lhs.true56
  %45 = load i8*, i8** %p, align 8, !dbg !1818
  %arrayidx60 = getelementptr inbounds i8, i8* %45, i64 2, !dbg !1818
  %call61 = call i32 @archive_le32dec(i8* %arrayidx60), !dbg !1820
  %conv62 = zext i32 %call61 to i64, !dbg !1820
  %46 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !1821
  %mtime63 = getelementptr inbounds %struct.lha, %struct.lha* %46, i32 0, i32 12, !dbg !1822
  store i64 %conv62, i64* %mtime63, align 8, !dbg !1823
  %47 = load i8*, i8** %p, align 8, !dbg !1824
  %arrayidx64 = getelementptr inbounds i8, i8* %47, i64 6, !dbg !1824
  %call65 = call zeroext i16 @archive_le16dec(i8* %arrayidx64), !dbg !1825
  %conv66 = zext i16 %call65 to i32, !dbg !1825
  %48 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !1826
  %mode = getelementptr inbounds %struct.lha, %struct.lha* %48, i32 0, i32 16, !dbg !1827
  store i32 %conv66, i32* %mode, align 8, !dbg !1828
  %49 = load i8*, i8** %p, align 8, !dbg !1829
  %arrayidx67 = getelementptr inbounds i8, i8* %49, i64 8, !dbg !1829
  %call68 = call zeroext i16 @archive_le16dec(i8* %arrayidx67), !dbg !1830
  %conv69 = zext i16 %call68 to i64, !dbg !1830
  %50 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !1831
  %uid = getelementptr inbounds %struct.lha, %struct.lha* %50, i32 0, i32 17, !dbg !1832
  store i64 %conv69, i64* %uid, align 8, !dbg !1833
  %51 = load i8*, i8** %p, align 8, !dbg !1834
  %arrayidx70 = getelementptr inbounds i8, i8* %51, i64 10, !dbg !1834
  %call71 = call zeroext i16 @archive_le16dec(i8* %arrayidx70), !dbg !1835
  %conv72 = zext i16 %call71 to i64, !dbg !1835
  %52 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !1836
  %gid = getelementptr inbounds %struct.lha, %struct.lha* %52, i32 0, i32 18, !dbg !1837
  store i64 %conv72, i64* %gid, align 8, !dbg !1838
  %53 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !1839
  %setflag73 = getelementptr inbounds %struct.lha, %struct.lha* %53, i32 0, i32 9, !dbg !1840
  %54 = load i32, i32* %setflag73, align 8, !dbg !1841
  %or74 = or i32 %54, 4, !dbg !1841
  store i32 %or74, i32* %setflag73, align 8, !dbg !1841
  br label %if.end75, !dbg !1842

if.end75:                                         ; preds = %if.then59, %land.lhs.true56, %if.then47
  br label %if.end76, !dbg !1843

if.end76:                                         ; preds = %if.end75, %if.end41
  %55 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1844
  %56 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !1845
  %header_size77 = getelementptr inbounds %struct.lha, %struct.lha* %56, i32 0, i32 4, !dbg !1846
  %57 = load i64, i64* %header_size77, align 8, !dbg !1846
  %call78 = call i64 @__archive_read_consume(%struct.archive_read* %55, i64 %57), !dbg !1847
  %58 = load i8, i8* %sum_calculated, align 1, !dbg !1848
  %conv79 = zext i8 %58 to i32, !dbg !1848
  %59 = load i8, i8* %headersum, align 1, !dbg !1850
  %conv80 = zext i8 %59 to i32, !dbg !1850
  %cmp81 = icmp ne i32 %conv79, %conv80, !dbg !1851
  br i1 %cmp81, label %if.then83, label %if.end85, !dbg !1852

if.then83:                                        ; preds = %if.end76
  %60 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1853
  %archive84 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %60, i32 0, i32 0, !dbg !1855
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive84, i32 -1, i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.19, i32 0, i32 0)), !dbg !1856
  store i32 -30, i32* %retval, align 4, !dbg !1857
  br label %return, !dbg !1857

if.end85:                                         ; preds = %if.end76
  store i32 0, i32* %retval, align 4, !dbg !1858
  br label %return, !dbg !1858

return:                                           ; preds = %if.end85, %if.then83, %if.then28, %if.then22, %if.then
  %61 = load i32, i32* %retval, align 4, !dbg !1859
  ret i32 %61, !dbg !1859
}

; Function Attrs: nounwind uwtable
define internal i32 @lha_read_file_header_1(%struct.archive_read* %a, %struct.lha* %lha) #0 !dbg !447 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %lha.addr = alloca %struct.lha*, align 8
  %p = alloca i8*, align 8
  %extdsize = alloca i64, align 8
  %i = alloca i32, align 4
  %err = alloca i32, align 4
  %err2 = alloca i32, align 4
  %namelen = alloca i32, align 4
  %padding = alloca i32, align 4
  %headersum = alloca i8, align 1
  %sum_calculated = alloca i8, align 1
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !1860, metadata !548), !dbg !1861
  store %struct.lha* %lha, %struct.lha** %lha.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lha** %lha.addr, metadata !1862, metadata !548), !dbg !1863
  call void @llvm.dbg.declare(metadata i8** %p, metadata !1864, metadata !548), !dbg !1865
  call void @llvm.dbg.declare(metadata i64* %extdsize, metadata !1866, metadata !548), !dbg !1867
  call void @llvm.dbg.declare(metadata i32* %i, metadata !1868, metadata !548), !dbg !1869
  call void @llvm.dbg.declare(metadata i32* %err, metadata !1870, metadata !548), !dbg !1871
  call void @llvm.dbg.declare(metadata i32* %err2, metadata !1872, metadata !548), !dbg !1873
  call void @llvm.dbg.declare(metadata i32* %namelen, metadata !1874, metadata !548), !dbg !1875
  call void @llvm.dbg.declare(metadata i32* %padding, metadata !1876, metadata !548), !dbg !1877
  call void @llvm.dbg.declare(metadata i8* %headersum, metadata !1878, metadata !548), !dbg !1879
  call void @llvm.dbg.declare(metadata i8* %sum_calculated, metadata !1880, metadata !548), !dbg !1881
  store i32 0, i32* %err, align 4, !dbg !1882
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1883
  %call = call i8* @__archive_read_ahead(%struct.archive_read* %0, i64 27, i64* null), !dbg !1885
  store i8* %call, i8** %p, align 8, !dbg !1886
  %cmp = icmp eq i8* %call, null, !dbg !1887
  br i1 %cmp, label %if.then, label %if.end, !dbg !1888

if.then:                                          ; preds = %entry
  %1 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1889
  %call1 = call i32 @truncated_error(%struct.archive_read* %1), !dbg !1890
  store i32 %call1, i32* %retval, align 4, !dbg !1891
  br label %return, !dbg !1891

if.end:                                           ; preds = %entry
  %2 = load i8*, i8** %p, align 8, !dbg !1892
  %arrayidx = getelementptr inbounds i8, i8* %2, i64 0, !dbg !1892
  %3 = load i8, i8* %arrayidx, align 1, !dbg !1892
  %conv = zext i8 %3 to i32, !dbg !1892
  %add = add nsw i32 %conv, 2, !dbg !1893
  %conv2 = sext i32 %add to i64, !dbg !1892
  %4 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !1894
  %header_size = getelementptr inbounds %struct.lha, %struct.lha* %4, i32 0, i32 4, !dbg !1895
  store i64 %conv2, i64* %header_size, align 8, !dbg !1896
  %5 = load i8*, i8** %p, align 8, !dbg !1897
  %arrayidx3 = getelementptr inbounds i8, i8* %5, i64 1, !dbg !1897
  %6 = load i8, i8* %arrayidx3, align 1, !dbg !1897
  store i8 %6, i8* %headersum, align 1, !dbg !1898
  %7 = load i8*, i8** %p, align 8, !dbg !1899
  %add.ptr = getelementptr inbounds i8, i8* %7, i64 7, !dbg !1900
  %call4 = call i32 @archive_le32dec(i8* %add.ptr), !dbg !1901
  %conv5 = zext i32 %call4 to i64, !dbg !1901
  %8 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !1902
  %compsize = getelementptr inbounds %struct.lha, %struct.lha* %8, i32 0, i32 7, !dbg !1903
  store i64 %conv5, i64* %compsize, align 8, !dbg !1904
  %9 = load i8*, i8** %p, align 8, !dbg !1905
  %add.ptr6 = getelementptr inbounds i8, i8* %9, i64 11, !dbg !1906
  %call7 = call i32 @archive_le32dec(i8* %add.ptr6), !dbg !1907
  %conv8 = zext i32 %call7 to i64, !dbg !1907
  %10 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !1908
  %origsize = getelementptr inbounds %struct.lha, %struct.lha* %10, i32 0, i32 8, !dbg !1909
  store i64 %conv8, i64* %origsize, align 8, !dbg !1910
  %11 = load i8*, i8** %p, align 8, !dbg !1911
  %add.ptr9 = getelementptr inbounds i8, i8* %11, i64 15, !dbg !1912
  %call10 = call i64 @lha_dos_time(i8* %add.ptr9), !dbg !1913
  %12 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !1914
  %mtime = getelementptr inbounds %struct.lha, %struct.lha* %12, i32 0, i32 12, !dbg !1915
  store i64 %call10, i64* %mtime, align 8, !dbg !1916
  %13 = load i8*, i8** %p, align 8, !dbg !1917
  %arrayidx11 = getelementptr inbounds i8, i8* %13, i64 21, !dbg !1917
  %14 = load i8, i8* %arrayidx11, align 1, !dbg !1917
  %conv12 = zext i8 %14 to i32, !dbg !1917
  store i32 %conv12, i32* %namelen, align 4, !dbg !1918
  %15 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !1919
  %header_size13 = getelementptr inbounds %struct.lha, %struct.lha* %15, i32 0, i32 4, !dbg !1920
  %16 = load i64, i64* %header_size13, align 8, !dbg !1920
  %conv14 = trunc i64 %16 to i32, !dbg !1921
  %sub = sub nsw i32 %conv14, 27, !dbg !1922
  %17 = load i32, i32* %namelen, align 4, !dbg !1923
  %sub15 = sub nsw i32 %sub, %17, !dbg !1924
  store i32 %sub15, i32* %padding, align 4, !dbg !1925
  %18 = load i32, i32* %namelen, align 4, !dbg !1926
  %cmp16 = icmp sgt i32 %18, 230, !dbg !1928
  br i1 %cmp16, label %if.then20, label %lor.lhs.false, !dbg !1929

lor.lhs.false:                                    ; preds = %if.end
  %19 = load i32, i32* %padding, align 4, !dbg !1930
  %cmp18 = icmp slt i32 %19, 0, !dbg !1932
  br i1 %cmp18, label %if.then20, label %if.end21, !dbg !1933

if.then20:                                        ; preds = %lor.lhs.false, %if.end
  br label %invalid, !dbg !1934

if.end21:                                         ; preds = %lor.lhs.false
  %20 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1935
  %21 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !1937
  %header_size22 = getelementptr inbounds %struct.lha, %struct.lha* %21, i32 0, i32 4, !dbg !1938
  %22 = load i64, i64* %header_size22, align 8, !dbg !1938
  %call23 = call i8* @__archive_read_ahead(%struct.archive_read* %20, i64 %22, i64* null), !dbg !1939
  store i8* %call23, i8** %p, align 8, !dbg !1940
  %cmp24 = icmp eq i8* %call23, null, !dbg !1941
  br i1 %cmp24, label %if.then26, label %if.end28, !dbg !1942

if.then26:                                        ; preds = %if.end21
  %23 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1943
  %call27 = call i32 @truncated_error(%struct.archive_read* %23), !dbg !1944
  store i32 %call27, i32* %retval, align 4, !dbg !1945
  br label %return, !dbg !1945

if.end28:                                         ; preds = %if.end21
  store i32 0, i32* %i, align 4, !dbg !1946
  br label %for.cond, !dbg !1948

for.cond:                                         ; preds = %for.inc, %if.end28
  %24 = load i32, i32* %i, align 4, !dbg !1949
  %25 = load i32, i32* %namelen, align 4, !dbg !1952
  %cmp29 = icmp slt i32 %24, %25, !dbg !1953
  br i1 %cmp29, label %for.body, label %for.end, !dbg !1954

for.body:                                         ; preds = %for.cond
  %26 = load i32, i32* %i, align 4, !dbg !1955
  %add31 = add nsw i32 %26, 22, !dbg !1958
  %idxprom = sext i32 %add31 to i64, !dbg !1959
  %27 = load i8*, i8** %p, align 8, !dbg !1959
  %arrayidx32 = getelementptr inbounds i8, i8* %27, i64 %idxprom, !dbg !1959
  %28 = load i8, i8* %arrayidx32, align 1, !dbg !1959
  %conv33 = zext i8 %28 to i32, !dbg !1959
  %cmp34 = icmp eq i32 %conv33, 255, !dbg !1960
  br i1 %cmp34, label %if.then36, label %if.end37, !dbg !1961

if.then36:                                        ; preds = %for.body
  br label %invalid, !dbg !1962

if.end37:                                         ; preds = %for.body
  br label %for.inc, !dbg !1963

for.inc:                                          ; preds = %if.end37
  %29 = load i32, i32* %i, align 4, !dbg !1964
  %inc = add nsw i32 %29, 1, !dbg !1964
  store i32 %inc, i32* %i, align 4, !dbg !1964
  br label %for.cond, !dbg !1966

for.end:                                          ; preds = %for.cond
  %30 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !1967
  %filename = getelementptr inbounds %struct.lha, %struct.lha* %30, i32 0, i32 26, !dbg !1967
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %filename, i32 0, i32 1, !dbg !1967
  store i64 0, i64* %length, align 8, !dbg !1967
  %31 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !1967
  %filename38 = getelementptr inbounds %struct.lha, %struct.lha* %31, i32 0, i32 26, !dbg !1967
  %32 = load i8*, i8** %p, align 8, !dbg !1967
  %add.ptr39 = getelementptr inbounds i8, i8* %32, i64 22, !dbg !1967
  %33 = load i32, i32* %namelen, align 4, !dbg !1967
  %conv40 = sext i32 %33 to i64, !dbg !1967
  %call41 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %filename38, i8* %add.ptr39, i64 %conv40), !dbg !1967
  %34 = load i8*, i8** %p, align 8, !dbg !1968
  %add.ptr42 = getelementptr inbounds i8, i8* %34, i64 22, !dbg !1969
  %35 = load i32, i32* %namelen, align 4, !dbg !1970
  %idx.ext = sext i32 %35 to i64, !dbg !1971
  %add.ptr43 = getelementptr inbounds i8, i8* %add.ptr42, i64 %idx.ext, !dbg !1971
  %call44 = call zeroext i16 @archive_le16dec(i8* %add.ptr43), !dbg !1972
  %36 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !1973
  %crc = getelementptr inbounds %struct.lha, %struct.lha* %36, i32 0, i32 22, !dbg !1974
  store i16 %call44, i16* %crc, align 2, !dbg !1975
  %37 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !1976
  %setflag = getelementptr inbounds %struct.lha, %struct.lha* %37, i32 0, i32 9, !dbg !1977
  %38 = load i32, i32* %setflag, align 8, !dbg !1978
  %or = or i32 %38, 8, !dbg !1978
  store i32 %or, i32* %setflag, align 8, !dbg !1978
  %39 = load i8*, i8** %p, align 8, !dbg !1979
  %40 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !1980
  %header_size45 = getelementptr inbounds %struct.lha, %struct.lha* %40, i32 0, i32 4, !dbg !1981
  %41 = load i64, i64* %header_size45, align 8, !dbg !1981
  %sub46 = sub i64 %41, 2, !dbg !1982
  %call47 = call zeroext i8 @lha_calcsum(i8 zeroext 0, i8* %39, i32 2, i64 %sub46), !dbg !1983
  store i8 %call47, i8* %sum_calculated, align 1, !dbg !1984
  %42 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1985
  %43 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !1986
  %header_size48 = getelementptr inbounds %struct.lha, %struct.lha* %43, i32 0, i32 4, !dbg !1987
  %44 = load i64, i64* %header_size48, align 8, !dbg !1987
  %sub49 = sub i64 %44, 2, !dbg !1988
  %call50 = call i64 @__archive_read_consume(%struct.archive_read* %42, i64 %sub49), !dbg !1989
  %45 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1990
  %46 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !1991
  %47 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !1992
  %compsize51 = getelementptr inbounds %struct.lha, %struct.lha* %47, i32 0, i32 7, !dbg !1993
  %48 = load i64, i64* %compsize51, align 8, !dbg !1993
  %add52 = add nsw i64 %48, 2, !dbg !1994
  %call53 = call i32 @lha_read_file_extended_header(%struct.archive_read* %45, %struct.lha* %46, i16* null, i32 2, i64 %add52, i64* %extdsize), !dbg !1995
  store i32 %call53, i32* %err2, align 4, !dbg !1996
  %49 = load i32, i32* %err2, align 4, !dbg !1997
  %cmp54 = icmp slt i32 %49, -20, !dbg !1999
  br i1 %cmp54, label %if.then56, label %if.end57, !dbg !2000

if.then56:                                        ; preds = %for.end
  %50 = load i32, i32* %err2, align 4, !dbg !2001
  store i32 %50, i32* %retval, align 4, !dbg !2002
  br label %return, !dbg !2002

if.end57:                                         ; preds = %for.end
  %51 = load i32, i32* %err2, align 4, !dbg !2003
  %52 = load i32, i32* %err, align 4, !dbg !2005
  %cmp58 = icmp slt i32 %51, %52, !dbg !2006
  br i1 %cmp58, label %if.then60, label %if.end61, !dbg !2007

if.then60:                                        ; preds = %if.end57
  %53 = load i32, i32* %err2, align 4, !dbg !2008
  store i32 %53, i32* %err, align 4, !dbg !2009
  br label %if.end61, !dbg !2010

if.end61:                                         ; preds = %if.then60, %if.end57
  %54 = load i64, i64* %extdsize, align 8, !dbg !2011
  %sub62 = sub i64 %54, 2, !dbg !2012
  %55 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2013
  %compsize63 = getelementptr inbounds %struct.lha, %struct.lha* %55, i32 0, i32 7, !dbg !2014
  %56 = load i64, i64* %compsize63, align 8, !dbg !2015
  %sub64 = sub i64 %56, %sub62, !dbg !2015
  store i64 %sub64, i64* %compsize63, align 8, !dbg !2015
  %57 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2016
  %compsize65 = getelementptr inbounds %struct.lha, %struct.lha* %57, i32 0, i32 7, !dbg !2018
  %58 = load i64, i64* %compsize65, align 8, !dbg !2018
  %cmp66 = icmp slt i64 %58, 0, !dbg !2019
  br i1 %cmp66, label %if.then68, label %if.end69, !dbg !2020

if.then68:                                        ; preds = %if.end61
  br label %invalid, !dbg !2021

if.end69:                                         ; preds = %if.end61
  %59 = load i8, i8* %sum_calculated, align 1, !dbg !2022
  %conv70 = zext i8 %59 to i32, !dbg !2022
  %60 = load i8, i8* %headersum, align 1, !dbg !2024
  %conv71 = zext i8 %60 to i32, !dbg !2024
  %cmp72 = icmp ne i32 %conv70, %conv71, !dbg !2025
  br i1 %cmp72, label %if.then74, label %if.end75, !dbg !2026

if.then74:                                        ; preds = %if.end69
  %61 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2027
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %61, i32 0, i32 0, !dbg !2029
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 -1, i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.19, i32 0, i32 0)), !dbg !2030
  store i32 -30, i32* %retval, align 4, !dbg !2031
  br label %return, !dbg !2031

if.end75:                                         ; preds = %if.end69
  %62 = load i32, i32* %err, align 4, !dbg !2032
  store i32 %62, i32* %retval, align 4, !dbg !2033
  br label %return, !dbg !2033

invalid:                                          ; preds = %if.then68, %if.then36, %if.then20
  %63 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2034
  %archive76 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %63, i32 0, i32 0, !dbg !2035
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive76, i32 84, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.18, i32 0, i32 0)), !dbg !2036
  store i32 -30, i32* %retval, align 4, !dbg !2037
  br label %return, !dbg !2037

return:                                           ; preds = %invalid, %if.end75, %if.then74, %if.then56, %if.then26, %if.then
  %64 = load i32, i32* %retval, align 4, !dbg !2038
  ret i32 %64, !dbg !2038
}

; Function Attrs: nounwind uwtable
define internal i32 @lha_read_file_header_2(%struct.archive_read* %a, %struct.lha* %lha) #0 !dbg !461 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %lha.addr = alloca %struct.lha*, align 8
  %p = alloca i8*, align 8
  %extdsize = alloca i64, align 8
  %err = alloca i32, align 4
  %padding = alloca i32, align 4
  %header_crc = alloca i16, align 2
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !2039, metadata !548), !dbg !2040
  store %struct.lha* %lha, %struct.lha** %lha.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lha** %lha.addr, metadata !2041, metadata !548), !dbg !2042
  call void @llvm.dbg.declare(metadata i8** %p, metadata !2043, metadata !548), !dbg !2044
  call void @llvm.dbg.declare(metadata i64* %extdsize, metadata !2045, metadata !548), !dbg !2046
  call void @llvm.dbg.declare(metadata i32* %err, metadata !2047, metadata !548), !dbg !2048
  call void @llvm.dbg.declare(metadata i32* %padding, metadata !2049, metadata !548), !dbg !2050
  call void @llvm.dbg.declare(metadata i16* %header_crc, metadata !2051, metadata !548), !dbg !2052
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2053
  %call = call i8* @__archive_read_ahead(%struct.archive_read* %0, i64 24, i64* null), !dbg !2055
  store i8* %call, i8** %p, align 8, !dbg !2056
  %cmp = icmp eq i8* %call, null, !dbg !2057
  br i1 %cmp, label %if.then, label %if.end, !dbg !2058

if.then:                                          ; preds = %entry
  %1 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2059
  %call1 = call i32 @truncated_error(%struct.archive_read* %1), !dbg !2060
  store i32 %call1, i32* %retval, align 4, !dbg !2061
  br label %return, !dbg !2061

if.end:                                           ; preds = %entry
  %2 = load i8*, i8** %p, align 8, !dbg !2062
  %add.ptr = getelementptr inbounds i8, i8* %2, i64 0, !dbg !2063
  %call2 = call zeroext i16 @archive_le16dec(i8* %add.ptr), !dbg !2064
  %conv = zext i16 %call2 to i64, !dbg !2064
  %3 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2065
  %header_size = getelementptr inbounds %struct.lha, %struct.lha* %3, i32 0, i32 4, !dbg !2066
  store i64 %conv, i64* %header_size, align 8, !dbg !2067
  %4 = load i8*, i8** %p, align 8, !dbg !2068
  %add.ptr3 = getelementptr inbounds i8, i8* %4, i64 7, !dbg !2069
  %call4 = call i32 @archive_le32dec(i8* %add.ptr3), !dbg !2070
  %conv5 = zext i32 %call4 to i64, !dbg !2070
  %5 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2071
  %compsize = getelementptr inbounds %struct.lha, %struct.lha* %5, i32 0, i32 7, !dbg !2072
  store i64 %conv5, i64* %compsize, align 8, !dbg !2073
  %6 = load i8*, i8** %p, align 8, !dbg !2074
  %add.ptr6 = getelementptr inbounds i8, i8* %6, i64 11, !dbg !2075
  %call7 = call i32 @archive_le32dec(i8* %add.ptr6), !dbg !2076
  %conv8 = zext i32 %call7 to i64, !dbg !2076
  %7 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2077
  %origsize = getelementptr inbounds %struct.lha, %struct.lha* %7, i32 0, i32 8, !dbg !2078
  store i64 %conv8, i64* %origsize, align 8, !dbg !2079
  %8 = load i8*, i8** %p, align 8, !dbg !2080
  %add.ptr9 = getelementptr inbounds i8, i8* %8, i64 15, !dbg !2081
  %call10 = call i32 @archive_le32dec(i8* %add.ptr9), !dbg !2082
  %conv11 = zext i32 %call10 to i64, !dbg !2082
  %9 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2083
  %mtime = getelementptr inbounds %struct.lha, %struct.lha* %9, i32 0, i32 12, !dbg !2084
  store i64 %conv11, i64* %mtime, align 8, !dbg !2085
  %10 = load i8*, i8** %p, align 8, !dbg !2086
  %add.ptr12 = getelementptr inbounds i8, i8* %10, i64 21, !dbg !2087
  %call13 = call zeroext i16 @archive_le16dec(i8* %add.ptr12), !dbg !2088
  %11 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2089
  %crc = getelementptr inbounds %struct.lha, %struct.lha* %11, i32 0, i32 22, !dbg !2090
  store i16 %call13, i16* %crc, align 2, !dbg !2091
  %12 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2092
  %setflag = getelementptr inbounds %struct.lha, %struct.lha* %12, i32 0, i32 9, !dbg !2093
  %13 = load i32, i32* %setflag, align 8, !dbg !2094
  %or = or i32 %13, 8, !dbg !2094
  store i32 %or, i32* %setflag, align 8, !dbg !2094
  %14 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2095
  %header_size14 = getelementptr inbounds %struct.lha, %struct.lha* %14, i32 0, i32 4, !dbg !2097
  %15 = load i64, i64* %header_size14, align 8, !dbg !2097
  %cmp15 = icmp ult i64 %15, 24, !dbg !2098
  br i1 %cmp15, label %if.then17, label %if.end18, !dbg !2099

if.then17:                                        ; preds = %if.end
  %16 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2100
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %16, i32 0, i32 0, !dbg !2102
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 84, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.23, i32 0, i32 0)), !dbg !2103
  store i32 -30, i32* %retval, align 4, !dbg !2104
  br label %return, !dbg !2104

if.end18:                                         ; preds = %if.end
  %17 = load i8*, i8** %p, align 8, !dbg !2105
  %call19 = call zeroext i16 @lha_crc16(i16 zeroext 0, i8* %17, i64 24), !dbg !2106
  store i16 %call19, i16* %header_crc, align 2, !dbg !2107
  %18 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2108
  %call20 = call i64 @__archive_read_consume(%struct.archive_read* %18, i64 24), !dbg !2109
  %19 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2110
  %20 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2111
  %21 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2112
  %header_size21 = getelementptr inbounds %struct.lha, %struct.lha* %21, i32 0, i32 4, !dbg !2113
  %22 = load i64, i64* %header_size21, align 8, !dbg !2113
  %sub = sub i64 %22, 24, !dbg !2114
  %call22 = call i32 @lha_read_file_extended_header(%struct.archive_read* %19, %struct.lha* %20, i16* %header_crc, i32 2, i64 %sub, i64* %extdsize), !dbg !2115
  store i32 %call22, i32* %err, align 4, !dbg !2116
  %23 = load i32, i32* %err, align 4, !dbg !2117
  %cmp23 = icmp slt i32 %23, -20, !dbg !2119
  br i1 %cmp23, label %if.then25, label %if.end26, !dbg !2120

if.then25:                                        ; preds = %if.end18
  %24 = load i32, i32* %err, align 4, !dbg !2121
  store i32 %24, i32* %retval, align 4, !dbg !2122
  br label %return, !dbg !2122

if.end26:                                         ; preds = %if.end18
  %25 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2123
  %header_size27 = getelementptr inbounds %struct.lha, %struct.lha* %25, i32 0, i32 4, !dbg !2124
  %26 = load i64, i64* %header_size27, align 8, !dbg !2124
  %conv28 = trunc i64 %26 to i32, !dbg !2125
  %27 = load i64, i64* %extdsize, align 8, !dbg !2126
  %add = add i64 24, %27, !dbg !2127
  %conv29 = trunc i64 %add to i32, !dbg !2128
  %sub30 = sub nsw i32 %conv28, %conv29, !dbg !2129
  store i32 %sub30, i32* %padding, align 4, !dbg !2130
  %28 = load i32, i32* %padding, align 4, !dbg !2131
  %cmp31 = icmp sgt i32 %28, 0, !dbg !2133
  br i1 %cmp31, label %if.then33, label %if.end45, !dbg !2134

if.then33:                                        ; preds = %if.end26
  %29 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2135
  %30 = load i32, i32* %padding, align 4, !dbg !2138
  %conv34 = sext i32 %30 to i64, !dbg !2138
  %call35 = call i8* @__archive_read_ahead(%struct.archive_read* %29, i64 %conv34, i64* null), !dbg !2139
  store i8* %call35, i8** %p, align 8, !dbg !2140
  %cmp36 = icmp eq i8* %call35, null, !dbg !2141
  br i1 %cmp36, label %if.then38, label %if.end40, !dbg !2142

if.then38:                                        ; preds = %if.then33
  %31 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2143
  %call39 = call i32 @truncated_error(%struct.archive_read* %31), !dbg !2144
  store i32 %call39, i32* %retval, align 4, !dbg !2145
  br label %return, !dbg !2145

if.end40:                                         ; preds = %if.then33
  %32 = load i16, i16* %header_crc, align 2, !dbg !2146
  %33 = load i8*, i8** %p, align 8, !dbg !2147
  %34 = load i32, i32* %padding, align 4, !dbg !2148
  %conv41 = sext i32 %34 to i64, !dbg !2148
  %call42 = call zeroext i16 @lha_crc16(i16 zeroext %32, i8* %33, i64 %conv41), !dbg !2149
  store i16 %call42, i16* %header_crc, align 2, !dbg !2150
  %35 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2151
  %36 = load i32, i32* %padding, align 4, !dbg !2152
  %conv43 = sext i32 %36 to i64, !dbg !2152
  %call44 = call i64 @__archive_read_consume(%struct.archive_read* %35, i64 %conv43), !dbg !2153
  br label %if.end45, !dbg !2154

if.end45:                                         ; preds = %if.end40, %if.end26
  %37 = load i16, i16* %header_crc, align 2, !dbg !2155
  %conv46 = zext i16 %37 to i32, !dbg !2155
  %38 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2157
  %header_crc47 = getelementptr inbounds %struct.lha, %struct.lha* %38, i32 0, i32 21, !dbg !2158
  %39 = load i16, i16* %header_crc47, align 8, !dbg !2158
  %conv48 = zext i16 %39 to i32, !dbg !2157
  %cmp49 = icmp ne i32 %conv46, %conv48, !dbg !2159
  br i1 %cmp49, label %if.then51, label %if.end53, !dbg !2160

if.then51:                                        ; preds = %if.end45
  %40 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2161
  %archive52 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %40, i32 0, i32 0, !dbg !2163
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive52, i32 84, i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.24, i32 0, i32 0)), !dbg !2164
  store i32 -30, i32* %retval, align 4, !dbg !2165
  br label %return, !dbg !2165

if.end53:                                         ; preds = %if.end45
  %41 = load i32, i32* %err, align 4, !dbg !2166
  store i32 %41, i32* %retval, align 4, !dbg !2167
  br label %return, !dbg !2167

return:                                           ; preds = %if.end53, %if.then51, %if.then38, %if.then25, %if.then17, %if.then
  %42 = load i32, i32* %retval, align 4, !dbg !2168
  ret i32 %42, !dbg !2168
}

; Function Attrs: nounwind uwtable
define internal i32 @lha_read_file_header_3(%struct.archive_read* %a, %struct.lha* %lha) #0 !dbg !462 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %lha.addr = alloca %struct.lha*, align 8
  %p = alloca i8*, align 8
  %extdsize = alloca i64, align 8
  %err = alloca i32, align 4
  %header_crc = alloca i16, align 2
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !2169, metadata !548), !dbg !2170
  store %struct.lha* %lha, %struct.lha** %lha.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lha** %lha.addr, metadata !2171, metadata !548), !dbg !2172
  call void @llvm.dbg.declare(metadata i8** %p, metadata !2173, metadata !548), !dbg !2174
  call void @llvm.dbg.declare(metadata i64* %extdsize, metadata !2175, metadata !548), !dbg !2176
  call void @llvm.dbg.declare(metadata i32* %err, metadata !2177, metadata !548), !dbg !2178
  call void @llvm.dbg.declare(metadata i16* %header_crc, metadata !2179, metadata !548), !dbg !2180
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2181
  %call = call i8* @__archive_read_ahead(%struct.archive_read* %0, i64 28, i64* null), !dbg !2183
  store i8* %call, i8** %p, align 8, !dbg !2184
  %cmp = icmp eq i8* %call, null, !dbg !2185
  br i1 %cmp, label %if.then, label %if.end, !dbg !2186

if.then:                                          ; preds = %entry
  %1 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2187
  %call1 = call i32 @truncated_error(%struct.archive_read* %1), !dbg !2188
  store i32 %call1, i32* %retval, align 4, !dbg !2189
  br label %return, !dbg !2189

if.end:                                           ; preds = %entry
  %2 = load i8*, i8** %p, align 8, !dbg !2190
  %add.ptr = getelementptr inbounds i8, i8* %2, i64 0, !dbg !2192
  %call2 = call zeroext i16 @archive_le16dec(i8* %add.ptr), !dbg !2193
  %conv = zext i16 %call2 to i32, !dbg !2193
  %cmp3 = icmp ne i32 %conv, 4, !dbg !2194
  br i1 %cmp3, label %if.then5, label %if.end6, !dbg !2195

if.then5:                                         ; preds = %if.end
  br label %invalid, !dbg !2196

if.end6:                                          ; preds = %if.end
  %3 = load i8*, i8** %p, align 8, !dbg !2197
  %add.ptr7 = getelementptr inbounds i8, i8* %3, i64 24, !dbg !2198
  %call8 = call i32 @archive_le32dec(i8* %add.ptr7), !dbg !2199
  %conv9 = zext i32 %call8 to i64, !dbg !2199
  %4 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2200
  %header_size = getelementptr inbounds %struct.lha, %struct.lha* %4, i32 0, i32 4, !dbg !2201
  store i64 %conv9, i64* %header_size, align 8, !dbg !2202
  %5 = load i8*, i8** %p, align 8, !dbg !2203
  %add.ptr10 = getelementptr inbounds i8, i8* %5, i64 7, !dbg !2204
  %call11 = call i32 @archive_le32dec(i8* %add.ptr10), !dbg !2205
  %conv12 = zext i32 %call11 to i64, !dbg !2205
  %6 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2206
  %compsize = getelementptr inbounds %struct.lha, %struct.lha* %6, i32 0, i32 7, !dbg !2207
  store i64 %conv12, i64* %compsize, align 8, !dbg !2208
  %7 = load i8*, i8** %p, align 8, !dbg !2209
  %add.ptr13 = getelementptr inbounds i8, i8* %7, i64 11, !dbg !2210
  %call14 = call i32 @archive_le32dec(i8* %add.ptr13), !dbg !2211
  %conv15 = zext i32 %call14 to i64, !dbg !2211
  %8 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2212
  %origsize = getelementptr inbounds %struct.lha, %struct.lha* %8, i32 0, i32 8, !dbg !2213
  store i64 %conv15, i64* %origsize, align 8, !dbg !2214
  %9 = load i8*, i8** %p, align 8, !dbg !2215
  %add.ptr16 = getelementptr inbounds i8, i8* %9, i64 15, !dbg !2216
  %call17 = call i32 @archive_le32dec(i8* %add.ptr16), !dbg !2217
  %conv18 = zext i32 %call17 to i64, !dbg !2217
  %10 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2218
  %mtime = getelementptr inbounds %struct.lha, %struct.lha* %10, i32 0, i32 12, !dbg !2219
  store i64 %conv18, i64* %mtime, align 8, !dbg !2220
  %11 = load i8*, i8** %p, align 8, !dbg !2221
  %add.ptr19 = getelementptr inbounds i8, i8* %11, i64 21, !dbg !2222
  %call20 = call zeroext i16 @archive_le16dec(i8* %add.ptr19), !dbg !2223
  %12 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2224
  %crc = getelementptr inbounds %struct.lha, %struct.lha* %12, i32 0, i32 22, !dbg !2225
  store i16 %call20, i16* %crc, align 2, !dbg !2226
  %13 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2227
  %setflag = getelementptr inbounds %struct.lha, %struct.lha* %13, i32 0, i32 9, !dbg !2228
  %14 = load i32, i32* %setflag, align 8, !dbg !2229
  %or = or i32 %14, 8, !dbg !2229
  store i32 %or, i32* %setflag, align 8, !dbg !2229
  %15 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2230
  %header_size21 = getelementptr inbounds %struct.lha, %struct.lha* %15, i32 0, i32 4, !dbg !2232
  %16 = load i64, i64* %header_size21, align 8, !dbg !2232
  %cmp22 = icmp ult i64 %16, 32, !dbg !2233
  br i1 %cmp22, label %if.then24, label %if.end25, !dbg !2234

if.then24:                                        ; preds = %if.end6
  br label %invalid, !dbg !2235

if.end25:                                         ; preds = %if.end6
  %17 = load i8*, i8** %p, align 8, !dbg !2236
  %call26 = call zeroext i16 @lha_crc16(i16 zeroext 0, i8* %17, i64 28), !dbg !2237
  store i16 %call26, i16* %header_crc, align 2, !dbg !2238
  %18 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2239
  %call27 = call i64 @__archive_read_consume(%struct.archive_read* %18, i64 28), !dbg !2240
  %19 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2241
  %20 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2242
  %21 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2243
  %header_size28 = getelementptr inbounds %struct.lha, %struct.lha* %21, i32 0, i32 4, !dbg !2244
  %22 = load i64, i64* %header_size28, align 8, !dbg !2244
  %sub = sub i64 %22, 28, !dbg !2245
  %call29 = call i32 @lha_read_file_extended_header(%struct.archive_read* %19, %struct.lha* %20, i16* %header_crc, i32 4, i64 %sub, i64* %extdsize), !dbg !2246
  store i32 %call29, i32* %err, align 4, !dbg !2247
  %23 = load i32, i32* %err, align 4, !dbg !2248
  %cmp30 = icmp slt i32 %23, -20, !dbg !2250
  br i1 %cmp30, label %if.then32, label %if.end33, !dbg !2251

if.then32:                                        ; preds = %if.end25
  %24 = load i32, i32* %err, align 4, !dbg !2252
  store i32 %24, i32* %retval, align 4, !dbg !2253
  br label %return, !dbg !2253

if.end33:                                         ; preds = %if.end25
  %25 = load i16, i16* %header_crc, align 2, !dbg !2254
  %conv34 = zext i16 %25 to i32, !dbg !2254
  %26 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2256
  %header_crc35 = getelementptr inbounds %struct.lha, %struct.lha* %26, i32 0, i32 21, !dbg !2257
  %27 = load i16, i16* %header_crc35, align 8, !dbg !2257
  %conv36 = zext i16 %27 to i32, !dbg !2256
  %cmp37 = icmp ne i32 %conv34, %conv36, !dbg !2258
  br i1 %cmp37, label %if.then39, label %if.end40, !dbg !2259

if.then39:                                        ; preds = %if.end33
  %28 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2260
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %28, i32 0, i32 0, !dbg !2262
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 84, i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.24, i32 0, i32 0)), !dbg !2263
  store i32 -30, i32* %retval, align 4, !dbg !2264
  br label %return, !dbg !2264

if.end40:                                         ; preds = %if.end33
  %29 = load i32, i32* %err, align 4, !dbg !2265
  store i32 %29, i32* %retval, align 4, !dbg !2266
  br label %return, !dbg !2266

invalid:                                          ; preds = %if.then24, %if.then5
  %30 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2267
  %archive41 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %30, i32 0, i32 0, !dbg !2268
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive41, i32 84, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.18, i32 0, i32 0)), !dbg !2269
  store i32 -30, i32* %retval, align 4, !dbg !2270
  br label %return, !dbg !2270

return:                                           ; preds = %invalid, %if.end40, %if.then39, %if.then32, %if.then
  %31 = load i32, i32* %retval, align 4, !dbg !2271
  ret i32 %31, !dbg !2271
}

declare void @archive_string_concat(%struct.archive_string*, %struct.archive_string*) #2

; Function Attrs: nounwind uwtable
define internal i32 @lha_parse_linkname(%struct.archive_string* %linkname, %struct.archive_string* %pathname) #0 !dbg !463 {
entry:
  %retval = alloca i32, align 4
  %linkname.addr = alloca %struct.archive_string*, align 8
  %pathname.addr = alloca %struct.archive_string*, align 8
  %linkptr = alloca i8*, align 8
  %symlen = alloca i64, align 8
  store %struct.archive_string* %linkname, %struct.archive_string** %linkname.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string** %linkname.addr, metadata !2272, metadata !548), !dbg !2273
  store %struct.archive_string* %pathname, %struct.archive_string** %pathname.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string** %pathname.addr, metadata !2274, metadata !548), !dbg !2275
  call void @llvm.dbg.declare(metadata i8** %linkptr, metadata !2276, metadata !548), !dbg !2277
  call void @llvm.dbg.declare(metadata i64* %symlen, metadata !2278, metadata !548), !dbg !2279
  %0 = load %struct.archive_string*, %struct.archive_string** %pathname.addr, align 8, !dbg !2280
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %0, i32 0, i32 0, !dbg !2281
  %1 = load i8*, i8** %s, align 8, !dbg !2281
  %call = call i8* @strchr(i8* %1, i32 124) #9, !dbg !2282
  store i8* %call, i8** %linkptr, align 8, !dbg !2283
  %2 = load i8*, i8** %linkptr, align 8, !dbg !2284
  %cmp = icmp ne i8* %2, null, !dbg !2286
  br i1 %cmp, label %if.then, label %if.end, !dbg !2287

if.then:                                          ; preds = %entry
  %3 = load i8*, i8** %linkptr, align 8, !dbg !2288
  %add.ptr = getelementptr inbounds i8, i8* %3, i64 1, !dbg !2290
  %call1 = call i64 @strlen(i8* %add.ptr) #9, !dbg !2291
  store i64 %call1, i64* %symlen, align 8, !dbg !2292
  %4 = load %struct.archive_string*, %struct.archive_string** %linkname.addr, align 8, !dbg !2293
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %4, i32 0, i32 1, !dbg !2293
  store i64 0, i64* %length, align 8, !dbg !2293
  %5 = load %struct.archive_string*, %struct.archive_string** %linkname.addr, align 8, !dbg !2293
  %6 = load i8*, i8** %linkptr, align 8, !dbg !2293
  %add.ptr2 = getelementptr inbounds i8, i8* %6, i64 1, !dbg !2293
  %7 = load i64, i64* %symlen, align 8, !dbg !2293
  %call3 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %5, i8* %add.ptr2, i64 %7), !dbg !2293
  %8 = load i8*, i8** %linkptr, align 8, !dbg !2294
  store i8 0, i8* %8, align 1, !dbg !2295
  %9 = load %struct.archive_string*, %struct.archive_string** %pathname.addr, align 8, !dbg !2296
  %s4 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %9, i32 0, i32 0, !dbg !2297
  %10 = load i8*, i8** %s4, align 8, !dbg !2297
  %call5 = call i64 @strlen(i8* %10) #9, !dbg !2298
  %11 = load %struct.archive_string*, %struct.archive_string** %pathname.addr, align 8, !dbg !2299
  %length6 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %11, i32 0, i32 1, !dbg !2300
  store i64 %call5, i64* %length6, align 8, !dbg !2301
  store i32 1, i32* %retval, align 4, !dbg !2302
  br label %return, !dbg !2302

if.end:                                           ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !2303
  br label %return, !dbg !2303

return:                                           ; preds = %if.end, %if.then
  %12 = load i32, i32* %retval, align 4, !dbg !2304
  ret i32 %12, !dbg !2304
}

declare void @archive_string_free(%struct.archive_string*) #2

declare i32 @_archive_entry_copy_pathname_l(%struct.archive_entry*, i8*, i64, %struct.archive_string_conv*) #2

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #5

declare i8* @archive_string_conversion_charset_name(%struct.archive_string_conv*) #2

declare i32 @_archive_entry_copy_symlink_l(%struct.archive_entry*, i8*, i64, %struct.archive_string_conv*) #2

declare void @archive_entry_set_symlink(%struct.archive_entry*, i8*) #2

; Function Attrs: nounwind uwtable
define internal void @lha_replace_path_separator(%struct.lha* %lha, %struct.archive_entry* %entry1) #0 !dbg !467 {
entry:
  %lha.addr = alloca %struct.lha*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %wp = alloca i32*, align 8
  %i = alloca i64, align 8
  store %struct.lha* %lha, %struct.lha** %lha.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lha** %lha.addr, metadata !2305, metadata !548), !dbg !2306
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2307, metadata !548), !dbg !2308
  call void @llvm.dbg.declare(metadata i32** %wp, metadata !2309, metadata !548), !dbg !2312
  call void @llvm.dbg.declare(metadata i64* %i, metadata !2313, metadata !548), !dbg !2314
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2315
  %call = call i32* @archive_entry_pathname_w(%struct.archive_entry* %0), !dbg !2317
  store i32* %call, i32** %wp, align 8, !dbg !2318
  %cmp = icmp ne i32* %call, null, !dbg !2319
  br i1 %cmp, label %if.then, label %if.end17, !dbg !2320

if.then:                                          ; preds = %entry
  %1 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2321
  %ws = getelementptr inbounds %struct.lha, %struct.lha* %1, i32 0, i32 27, !dbg !2321
  %length = getelementptr inbounds %struct.archive_wstring, %struct.archive_wstring* %ws, i32 0, i32 1, !dbg !2321
  store i64 0, i64* %length, align 8, !dbg !2321
  %2 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2321
  %ws2 = getelementptr inbounds %struct.lha, %struct.lha* %2, i32 0, i32 27, !dbg !2321
  %3 = load i32*, i32** %wp, align 8, !dbg !2321
  %4 = load i32*, i32** %wp, align 8, !dbg !2321
  %cmp3 = icmp eq i32* %4, null, !dbg !2321
  br i1 %cmp3, label %cond.true, label %cond.false, !dbg !2321

cond.true:                                        ; preds = %if.then
  br label %cond.end, !dbg !2323

cond.false:                                       ; preds = %if.then
  %5 = load i32*, i32** %wp, align 8, !dbg !2325
  %call4 = call i64 @wcslen(i32* %5) #9, !dbg !2325
  br label %cond.end, !dbg !2325

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ 0, %cond.true ], [ %call4, %cond.false ], !dbg !2327
  %call5 = call %struct.archive_wstring* @archive_wstrncat(%struct.archive_wstring* %ws2, i32* %3, i64 %cond), !dbg !2327
  store i64 0, i64* %i, align 8, !dbg !2329
  br label %for.cond, !dbg !2331

for.cond:                                         ; preds = %for.inc, %cond.end
  %6 = load i64, i64* %i, align 8, !dbg !2332
  %7 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2335
  %ws6 = getelementptr inbounds %struct.lha, %struct.lha* %7, i32 0, i32 27, !dbg !2335
  %length7 = getelementptr inbounds %struct.archive_wstring, %struct.archive_wstring* %ws6, i32 0, i32 1, !dbg !2335
  %8 = load i64, i64* %length7, align 8, !dbg !2335
  %cmp8 = icmp ult i64 %6, %8, !dbg !2336
  br i1 %cmp8, label %for.body, label %for.end, !dbg !2337

for.body:                                         ; preds = %for.cond
  %9 = load i64, i64* %i, align 8, !dbg !2338
  %10 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2341
  %ws9 = getelementptr inbounds %struct.lha, %struct.lha* %10, i32 0, i32 27, !dbg !2342
  %s = getelementptr inbounds %struct.archive_wstring, %struct.archive_wstring* %ws9, i32 0, i32 0, !dbg !2343
  %11 = load i32*, i32** %s, align 8, !dbg !2343
  %arrayidx = getelementptr inbounds i32, i32* %11, i64 %9, !dbg !2341
  %12 = load i32, i32* %arrayidx, align 4, !dbg !2341
  %cmp10 = icmp eq i32 %12, 92, !dbg !2344
  br i1 %cmp10, label %if.then11, label %if.end, !dbg !2345

if.then11:                                        ; preds = %for.body
  %13 = load i64, i64* %i, align 8, !dbg !2346
  %14 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2347
  %ws12 = getelementptr inbounds %struct.lha, %struct.lha* %14, i32 0, i32 27, !dbg !2348
  %s13 = getelementptr inbounds %struct.archive_wstring, %struct.archive_wstring* %ws12, i32 0, i32 0, !dbg !2349
  %15 = load i32*, i32** %s13, align 8, !dbg !2349
  %arrayidx14 = getelementptr inbounds i32, i32* %15, i64 %13, !dbg !2347
  store i32 47, i32* %arrayidx14, align 4, !dbg !2350
  br label %if.end, !dbg !2347

if.end:                                           ; preds = %if.then11, %for.body
  br label %for.inc, !dbg !2351

for.inc:                                          ; preds = %if.end
  %16 = load i64, i64* %i, align 8, !dbg !2352
  %inc = add i64 %16, 1, !dbg !2352
  store i64 %inc, i64* %i, align 8, !dbg !2352
  br label %for.cond, !dbg !2354

for.end:                                          ; preds = %for.cond
  %17 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2355
  %18 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2356
  %ws15 = getelementptr inbounds %struct.lha, %struct.lha* %18, i32 0, i32 27, !dbg !2357
  %s16 = getelementptr inbounds %struct.archive_wstring, %struct.archive_wstring* %ws15, i32 0, i32 0, !dbg !2358
  %19 = load i32*, i32** %s16, align 8, !dbg !2358
  call void @archive_entry_copy_pathname_w(%struct.archive_entry* %17, i32* %19), !dbg !2359
  br label %if.end17, !dbg !2360

if.end17:                                         ; preds = %for.end, %entry
  %20 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2361
  %call18 = call i32* @archive_entry_symlink_w(%struct.archive_entry* %20), !dbg !2363
  store i32* %call18, i32** %wp, align 8, !dbg !2364
  %cmp19 = icmp ne i32* %call18, null, !dbg !2365
  br i1 %cmp19, label %if.then20, label %if.end50, !dbg !2366

if.then20:                                        ; preds = %if.end17
  %21 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2367
  %ws21 = getelementptr inbounds %struct.lha, %struct.lha* %21, i32 0, i32 27, !dbg !2367
  %length22 = getelementptr inbounds %struct.archive_wstring, %struct.archive_wstring* %ws21, i32 0, i32 1, !dbg !2367
  store i64 0, i64* %length22, align 8, !dbg !2367
  %22 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2367
  %ws23 = getelementptr inbounds %struct.lha, %struct.lha* %22, i32 0, i32 27, !dbg !2367
  %23 = load i32*, i32** %wp, align 8, !dbg !2367
  %24 = load i32*, i32** %wp, align 8, !dbg !2367
  %cmp24 = icmp eq i32* %24, null, !dbg !2367
  br i1 %cmp24, label %cond.true25, label %cond.false26, !dbg !2367

cond.true25:                                      ; preds = %if.then20
  br label %cond.end28, !dbg !2369

cond.false26:                                     ; preds = %if.then20
  %25 = load i32*, i32** %wp, align 8, !dbg !2371
  %call27 = call i64 @wcslen(i32* %25) #9, !dbg !2371
  br label %cond.end28, !dbg !2371

cond.end28:                                       ; preds = %cond.false26, %cond.true25
  %cond29 = phi i64 [ 0, %cond.true25 ], [ %call27, %cond.false26 ], !dbg !2373
  %call30 = call %struct.archive_wstring* @archive_wstrncat(%struct.archive_wstring* %ws23, i32* %23, i64 %cond29), !dbg !2373
  store i64 0, i64* %i, align 8, !dbg !2375
  br label %for.cond31, !dbg !2377

for.cond31:                                       ; preds = %for.inc45, %cond.end28
  %26 = load i64, i64* %i, align 8, !dbg !2378
  %27 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2381
  %ws32 = getelementptr inbounds %struct.lha, %struct.lha* %27, i32 0, i32 27, !dbg !2381
  %length33 = getelementptr inbounds %struct.archive_wstring, %struct.archive_wstring* %ws32, i32 0, i32 1, !dbg !2381
  %28 = load i64, i64* %length33, align 8, !dbg !2381
  %cmp34 = icmp ult i64 %26, %28, !dbg !2382
  br i1 %cmp34, label %for.body35, label %for.end47, !dbg !2383

for.body35:                                       ; preds = %for.cond31
  %29 = load i64, i64* %i, align 8, !dbg !2384
  %30 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2387
  %ws36 = getelementptr inbounds %struct.lha, %struct.lha* %30, i32 0, i32 27, !dbg !2388
  %s37 = getelementptr inbounds %struct.archive_wstring, %struct.archive_wstring* %ws36, i32 0, i32 0, !dbg !2389
  %31 = load i32*, i32** %s37, align 8, !dbg !2389
  %arrayidx38 = getelementptr inbounds i32, i32* %31, i64 %29, !dbg !2387
  %32 = load i32, i32* %arrayidx38, align 4, !dbg !2387
  %cmp39 = icmp eq i32 %32, 92, !dbg !2390
  br i1 %cmp39, label %if.then40, label %if.end44, !dbg !2391

if.then40:                                        ; preds = %for.body35
  %33 = load i64, i64* %i, align 8, !dbg !2392
  %34 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2393
  %ws41 = getelementptr inbounds %struct.lha, %struct.lha* %34, i32 0, i32 27, !dbg !2394
  %s42 = getelementptr inbounds %struct.archive_wstring, %struct.archive_wstring* %ws41, i32 0, i32 0, !dbg !2395
  %35 = load i32*, i32** %s42, align 8, !dbg !2395
  %arrayidx43 = getelementptr inbounds i32, i32* %35, i64 %33, !dbg !2393
  store i32 47, i32* %arrayidx43, align 4, !dbg !2396
  br label %if.end44, !dbg !2393

if.end44:                                         ; preds = %if.then40, %for.body35
  br label %for.inc45, !dbg !2397

for.inc45:                                        ; preds = %if.end44
  %36 = load i64, i64* %i, align 8, !dbg !2398
  %inc46 = add i64 %36, 1, !dbg !2398
  store i64 %inc46, i64* %i, align 8, !dbg !2398
  br label %for.cond31, !dbg !2400

for.end47:                                        ; preds = %for.cond31
  %37 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2401
  %38 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2402
  %ws48 = getelementptr inbounds %struct.lha, %struct.lha* %38, i32 0, i32 27, !dbg !2403
  %s49 = getelementptr inbounds %struct.archive_wstring, %struct.archive_wstring* %ws48, i32 0, i32 0, !dbg !2404
  %39 = load i32*, i32** %s49, align 8, !dbg !2404
  call void @archive_entry_copy_symlink_w(%struct.archive_entry* %37, i32* %39), !dbg !2405
  br label %if.end50, !dbg !2406

if.end50:                                         ; preds = %for.end47, %if.end17
  ret void, !dbg !2407
}

declare void @archive_entry_set_mode(%struct.archive_entry*, i32) #2

declare void @archive_entry_set_uid(%struct.archive_entry*, i64) #2

declare void @archive_entry_set_gid(%struct.archive_entry*, i64) #2

declare void @archive_entry_set_uname(%struct.archive_entry*, i8*) #2

declare void @archive_entry_set_gname(%struct.archive_entry*, i8*) #2

declare void @archive_entry_set_birthtime(%struct.archive_entry*, i64, i64) #2

declare void @archive_entry_set_ctime(%struct.archive_entry*, i64, i64) #2

declare void @archive_entry_unset_birthtime(%struct.archive_entry*) #2

declare void @archive_entry_unset_ctime(%struct.archive_entry*) #2

declare void @archive_entry_set_mtime(%struct.archive_entry*, i64, i64) #2

declare void @archive_entry_set_atime(%struct.archive_entry*, i64, i64) #2

declare void @archive_entry_unset_atime(%struct.archive_entry*) #2

declare i8* @archive_entry_symlink(%struct.archive_entry*) #2

declare void @archive_entry_unset_size(%struct.archive_entry*) #2

declare void @archive_entry_set_size(%struct.archive_entry*, i64) #2

; Function Attrs: nounwind
declare i32 @sprintf(i8*, i8*, ...) #3

declare i64 @__archive_read_consume(%struct.archive_read*, i64) #2

; Function Attrs: inlinehint nounwind uwtable
define internal i32 @archive_le32dec(i8* %pp) #6 !dbg !434 {
entry:
  %pp.addr = alloca i8*, align 8
  %p = alloca i8*, align 8
  %p3 = alloca i32, align 4
  %p2 = alloca i32, align 4
  %p1 = alloca i32, align 4
  %p0 = alloca i32, align 4
  store i8* %pp, i8** %pp.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %pp.addr, metadata !2408, metadata !548), !dbg !2409
  call void @llvm.dbg.declare(metadata i8** %p, metadata !2410, metadata !548), !dbg !2411
  %0 = load i8*, i8** %pp.addr, align 8, !dbg !2412
  store i8* %0, i8** %p, align 8, !dbg !2411
  call void @llvm.dbg.declare(metadata i32* %p3, metadata !2413, metadata !548), !dbg !2414
  %1 = load i8*, i8** %p, align 8, !dbg !2415
  %arrayidx = getelementptr inbounds i8, i8* %1, i64 3, !dbg !2415
  %2 = load i8, i8* %arrayidx, align 1, !dbg !2415
  %conv = zext i8 %2 to i32, !dbg !2415
  store i32 %conv, i32* %p3, align 4, !dbg !2414
  call void @llvm.dbg.declare(metadata i32* %p2, metadata !2416, metadata !548), !dbg !2417
  %3 = load i8*, i8** %p, align 8, !dbg !2418
  %arrayidx1 = getelementptr inbounds i8, i8* %3, i64 2, !dbg !2418
  %4 = load i8, i8* %arrayidx1, align 1, !dbg !2418
  %conv2 = zext i8 %4 to i32, !dbg !2418
  store i32 %conv2, i32* %p2, align 4, !dbg !2417
  call void @llvm.dbg.declare(metadata i32* %p1, metadata !2419, metadata !548), !dbg !2420
  %5 = load i8*, i8** %p, align 8, !dbg !2421
  %arrayidx3 = getelementptr inbounds i8, i8* %5, i64 1, !dbg !2421
  %6 = load i8, i8* %arrayidx3, align 1, !dbg !2421
  %conv4 = zext i8 %6 to i32, !dbg !2421
  store i32 %conv4, i32* %p1, align 4, !dbg !2420
  call void @llvm.dbg.declare(metadata i32* %p0, metadata !2422, metadata !548), !dbg !2423
  %7 = load i8*, i8** %p, align 8, !dbg !2424
  %arrayidx5 = getelementptr inbounds i8, i8* %7, i64 0, !dbg !2424
  %8 = load i8, i8* %arrayidx5, align 1, !dbg !2424
  %conv6 = zext i8 %8 to i32, !dbg !2424
  store i32 %conv6, i32* %p0, align 4, !dbg !2423
  %9 = load i32, i32* %p3, align 4, !dbg !2425
  %shl = shl i32 %9, 24, !dbg !2426
  %10 = load i32, i32* %p2, align 4, !dbg !2427
  %shl7 = shl i32 %10, 16, !dbg !2428
  %or = or i32 %shl, %shl7, !dbg !2429
  %11 = load i32, i32* %p1, align 4, !dbg !2430
  %shl8 = shl i32 %11, 8, !dbg !2431
  %or9 = or i32 %or, %shl8, !dbg !2432
  %12 = load i32, i32* %p0, align 4, !dbg !2433
  %or10 = or i32 %or9, %12, !dbg !2434
  ret i32 %or10, !dbg !2435
}

; Function Attrs: nounwind uwtable
define internal i64 @lha_dos_time(i8* %p) #0 !dbg !438 {
entry:
  %p.addr = alloca i8*, align 8
  %msTime = alloca i32, align 4
  %msDate = alloca i32, align 4
  %ts = alloca %struct.tm, align 8
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !2436, metadata !548), !dbg !2437
  call void @llvm.dbg.declare(metadata i32* %msTime, metadata !2438, metadata !548), !dbg !2439
  call void @llvm.dbg.declare(metadata i32* %msDate, metadata !2440, metadata !548), !dbg !2441
  call void @llvm.dbg.declare(metadata %struct.tm* %ts, metadata !2442, metadata !548), !dbg !2456
  %0 = load i8*, i8** %p.addr, align 8, !dbg !2457
  %call = call zeroext i16 @archive_le16dec(i8* %0), !dbg !2458
  %conv = zext i16 %call to i32, !dbg !2458
  store i32 %conv, i32* %msTime, align 4, !dbg !2459
  %1 = load i8*, i8** %p.addr, align 8, !dbg !2460
  %add.ptr = getelementptr inbounds i8, i8* %1, i64 2, !dbg !2461
  %call1 = call zeroext i16 @archive_le16dec(i8* %add.ptr), !dbg !2462
  %conv2 = zext i16 %call1 to i32, !dbg !2462
  store i32 %conv2, i32* %msDate, align 4, !dbg !2463
  %2 = bitcast %struct.tm* %ts to i8*, !dbg !2464
  call void @llvm.memset.p0i8.i64(i8* %2, i8 0, i64 56, i32 8, i1 false), !dbg !2464
  %3 = load i32, i32* %msDate, align 4, !dbg !2465
  %shr = ashr i32 %3, 9, !dbg !2466
  %and = and i32 %shr, 127, !dbg !2467
  %add = add nsw i32 %and, 80, !dbg !2468
  %tm_year = getelementptr inbounds %struct.tm, %struct.tm* %ts, i32 0, i32 5, !dbg !2469
  store i32 %add, i32* %tm_year, align 4, !dbg !2470
  %4 = load i32, i32* %msDate, align 4, !dbg !2471
  %shr3 = ashr i32 %4, 5, !dbg !2472
  %and4 = and i32 %shr3, 15, !dbg !2473
  %sub = sub nsw i32 %and4, 1, !dbg !2474
  %tm_mon = getelementptr inbounds %struct.tm, %struct.tm* %ts, i32 0, i32 4, !dbg !2475
  store i32 %sub, i32* %tm_mon, align 8, !dbg !2476
  %5 = load i32, i32* %msDate, align 4, !dbg !2477
  %and5 = and i32 %5, 31, !dbg !2478
  %tm_mday = getelementptr inbounds %struct.tm, %struct.tm* %ts, i32 0, i32 3, !dbg !2479
  store i32 %and5, i32* %tm_mday, align 4, !dbg !2480
  %6 = load i32, i32* %msTime, align 4, !dbg !2481
  %shr6 = ashr i32 %6, 11, !dbg !2482
  %and7 = and i32 %shr6, 31, !dbg !2483
  %tm_hour = getelementptr inbounds %struct.tm, %struct.tm* %ts, i32 0, i32 2, !dbg !2484
  store i32 %and7, i32* %tm_hour, align 8, !dbg !2485
  %7 = load i32, i32* %msTime, align 4, !dbg !2486
  %shr8 = ashr i32 %7, 5, !dbg !2487
  %and9 = and i32 %shr8, 63, !dbg !2488
  %tm_min = getelementptr inbounds %struct.tm, %struct.tm* %ts, i32 0, i32 1, !dbg !2489
  store i32 %and9, i32* %tm_min, align 4, !dbg !2490
  %8 = load i32, i32* %msTime, align 4, !dbg !2491
  %shl = shl i32 %8, 1, !dbg !2492
  %and10 = and i32 %shl, 62, !dbg !2493
  %tm_sec = getelementptr inbounds %struct.tm, %struct.tm* %ts, i32 0, i32 0, !dbg !2494
  store i32 %and10, i32* %tm_sec, align 8, !dbg !2495
  %tm_isdst = getelementptr inbounds %struct.tm, %struct.tm* %ts, i32 0, i32 8, !dbg !2496
  store i32 -1, i32* %tm_isdst, align 8, !dbg !2497
  %call11 = call i64 @mktime(%struct.tm* %ts) #8, !dbg !2498
  ret i64 %call11, !dbg !2499
}

declare %struct.archive_string* @archive_strncat(%struct.archive_string*, i8*, i64) #2

; Function Attrs: inlinehint nounwind uwtable
define internal zeroext i16 @archive_le16dec(i8* %pp) #6 !dbg !441 {
entry:
  %pp.addr = alloca i8*, align 8
  %p = alloca i8*, align 8
  %p1 = alloca i32, align 4
  %p0 = alloca i32, align 4
  store i8* %pp, i8** %pp.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %pp.addr, metadata !2500, metadata !548), !dbg !2501
  call void @llvm.dbg.declare(metadata i8** %p, metadata !2502, metadata !548), !dbg !2503
  %0 = load i8*, i8** %pp.addr, align 8, !dbg !2504
  store i8* %0, i8** %p, align 8, !dbg !2503
  call void @llvm.dbg.declare(metadata i32* %p1, metadata !2505, metadata !548), !dbg !2506
  %1 = load i8*, i8** %p, align 8, !dbg !2507
  %arrayidx = getelementptr inbounds i8, i8* %1, i64 1, !dbg !2507
  %2 = load i8, i8* %arrayidx, align 1, !dbg !2507
  %conv = zext i8 %2 to i32, !dbg !2507
  store i32 %conv, i32* %p1, align 4, !dbg !2506
  call void @llvm.dbg.declare(metadata i32* %p0, metadata !2508, metadata !548), !dbg !2509
  %3 = load i8*, i8** %p, align 8, !dbg !2510
  %arrayidx1 = getelementptr inbounds i8, i8* %3, i64 0, !dbg !2510
  %4 = load i8, i8* %arrayidx1, align 1, !dbg !2510
  %conv2 = zext i8 %4 to i32, !dbg !2510
  store i32 %conv2, i32* %p0, align 4, !dbg !2509
  %5 = load i32, i32* %p1, align 4, !dbg !2511
  %shl = shl i32 %5, 8, !dbg !2512
  %6 = load i32, i32* %p0, align 4, !dbg !2513
  %or = or i32 %shl, %6, !dbg !2514
  %conv3 = trunc i32 %or to i16, !dbg !2515
  ret i16 %conv3, !dbg !2516
}

; Function Attrs: nounwind uwtable
define internal zeroext i8 @lha_calcsum(i8 zeroext %sum, i8* %pp, i32 %offset, i64 %size) #0 !dbg !444 {
entry:
  %sum.addr = alloca i8, align 1
  %pp.addr = alloca i8*, align 8
  %offset.addr = alloca i32, align 4
  %size.addr = alloca i64, align 8
  %p = alloca i8*, align 8
  store i8 %sum, i8* %sum.addr, align 1
  call void @llvm.dbg.declare(metadata i8* %sum.addr, metadata !2517, metadata !548), !dbg !2518
  store i8* %pp, i8** %pp.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %pp.addr, metadata !2519, metadata !548), !dbg !2520
  store i32 %offset, i32* %offset.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %offset.addr, metadata !2521, metadata !548), !dbg !2522
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !2523, metadata !548), !dbg !2524
  call void @llvm.dbg.declare(metadata i8** %p, metadata !2525, metadata !548), !dbg !2526
  %0 = load i8*, i8** %pp.addr, align 8, !dbg !2527
  store i8* %0, i8** %p, align 8, !dbg !2526
  %1 = load i32, i32* %offset.addr, align 4, !dbg !2528
  %2 = load i8*, i8** %p, align 8, !dbg !2529
  %idx.ext = sext i32 %1 to i64, !dbg !2529
  %add.ptr = getelementptr inbounds i8, i8* %2, i64 %idx.ext, !dbg !2529
  store i8* %add.ptr, i8** %p, align 8, !dbg !2529
  br label %for.cond, !dbg !2530

for.cond:                                         ; preds = %for.inc, %entry
  %3 = load i64, i64* %size.addr, align 8, !dbg !2531
  %cmp = icmp ugt i64 %3, 0, !dbg !2535
  br i1 %cmp, label %for.body, label %for.end, !dbg !2536

for.body:                                         ; preds = %for.cond
  %4 = load i8*, i8** %p, align 8, !dbg !2537
  %incdec.ptr = getelementptr inbounds i8, i8* %4, i32 1, !dbg !2537
  store i8* %incdec.ptr, i8** %p, align 8, !dbg !2537
  %5 = load i8, i8* %4, align 1, !dbg !2538
  %conv = zext i8 %5 to i32, !dbg !2538
  %6 = load i8, i8* %sum.addr, align 1, !dbg !2539
  %conv1 = zext i8 %6 to i32, !dbg !2539
  %add = add nsw i32 %conv1, %conv, !dbg !2539
  %conv2 = trunc i32 %add to i8, !dbg !2539
  store i8 %conv2, i8* %sum.addr, align 1, !dbg !2539
  br label %for.inc, !dbg !2540

for.inc:                                          ; preds = %for.body
  %7 = load i64, i64* %size.addr, align 8, !dbg !2541
  %dec = add i64 %7, -1, !dbg !2541
  store i64 %dec, i64* %size.addr, align 8, !dbg !2541
  br label %for.cond, !dbg !2543

for.end:                                          ; preds = %for.cond
  %8 = load i8, i8* %sum.addr, align 1, !dbg !2544
  ret i8 %8, !dbg !2545
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #7

; Function Attrs: nounwind
declare i64 @mktime(%struct.tm*) #3

; Function Attrs: nounwind uwtable
define internal i32 @lha_read_file_extended_header(%struct.archive_read* %a, %struct.lha* %lha, i16* %crc, i32 %sizefield_length, i64 %limitsize, i64* %total_size) #0 !dbg !448 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %lha.addr = alloca %struct.lha*, align 8
  %crc.addr = alloca i16*, align 8
  %sizefield_length.addr = alloca i32, align 4
  %limitsize.addr = alloca i64, align 8
  %total_size.addr = alloca i64*, align 8
  %h = alloca i8*, align 8
  %extdheader = alloca i8*, align 8
  %extdsize = alloca i64, align 8
  %datasize = alloca i64, align 8
  %i = alloca i32, align 4
  %extdtype = alloca i8, align 1
  %cp = alloca %struct.archive_string, align 8
  %charset = alloca i8*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !2546, metadata !548), !dbg !2547
  store %struct.lha* %lha, %struct.lha** %lha.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lha** %lha.addr, metadata !2548, metadata !548), !dbg !2549
  store i16* %crc, i16** %crc.addr, align 8
  call void @llvm.dbg.declare(metadata i16** %crc.addr, metadata !2550, metadata !548), !dbg !2551
  store i32 %sizefield_length, i32* %sizefield_length.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %sizefield_length.addr, metadata !2552, metadata !548), !dbg !2553
  store i64 %limitsize, i64* %limitsize.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %limitsize.addr, metadata !2554, metadata !548), !dbg !2555
  store i64* %total_size, i64** %total_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %total_size.addr, metadata !2556, metadata !548), !dbg !2557
  call void @llvm.dbg.declare(metadata i8** %h, metadata !2558, metadata !548), !dbg !2559
  call void @llvm.dbg.declare(metadata i8** %extdheader, metadata !2560, metadata !548), !dbg !2561
  call void @llvm.dbg.declare(metadata i64* %extdsize, metadata !2562, metadata !548), !dbg !2563
  call void @llvm.dbg.declare(metadata i64* %datasize, metadata !2564, metadata !548), !dbg !2565
  call void @llvm.dbg.declare(metadata i32* %i, metadata !2566, metadata !548), !dbg !2567
  call void @llvm.dbg.declare(metadata i8* %extdtype, metadata !2568, metadata !548), !dbg !2569
  %0 = load i32, i32* %sizefield_length.addr, align 4, !dbg !2570
  %conv = sext i32 %0 to i64, !dbg !2570
  %1 = load i64*, i64** %total_size.addr, align 8, !dbg !2571
  store i64 %conv, i64* %1, align 8, !dbg !2572
  br label %for.cond, !dbg !2573

for.cond:                                         ; preds = %sw.epilog271, %entry
  %2 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2574
  %3 = load i32, i32* %sizefield_length.addr, align 4, !dbg !2579
  %conv1 = sext i32 %3 to i64, !dbg !2579
  %call = call i8* @__archive_read_ahead(%struct.archive_read* %2, i64 %conv1, i64* null), !dbg !2580
  store i8* %call, i8** %h, align 8, !dbg !2581
  %cmp = icmp eq i8* %call, null, !dbg !2582
  br i1 %cmp, label %if.then, label %if.end, !dbg !2583

if.then:                                          ; preds = %for.cond
  %4 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2584
  %call3 = call i32 @truncated_error(%struct.archive_read* %4), !dbg !2585
  store i32 %call3, i32* %retval, align 4, !dbg !2586
  br label %return, !dbg !2586

if.end:                                           ; preds = %for.cond
  %5 = load i32, i32* %sizefield_length.addr, align 4, !dbg !2587
  %conv4 = sext i32 %5 to i64, !dbg !2587
  %cmp5 = icmp eq i64 %conv4, 2, !dbg !2589
  br i1 %cmp5, label %if.then7, label %if.else, !dbg !2590

if.then7:                                         ; preds = %if.end
  %6 = load i8*, i8** %h, align 8, !dbg !2591
  %call8 = call zeroext i16 @archive_le16dec(i8* %6), !dbg !2592
  %conv9 = zext i16 %call8 to i64, !dbg !2592
  store i64 %conv9, i64* %extdsize, align 8, !dbg !2593
  br label %if.end12, !dbg !2594

if.else:                                          ; preds = %if.end
  %7 = load i8*, i8** %h, align 8, !dbg !2595
  %call10 = call i32 @archive_le32dec(i8* %7), !dbg !2596
  %conv11 = zext i32 %call10 to i64, !dbg !2596
  store i64 %conv11, i64* %extdsize, align 8, !dbg !2597
  br label %if.end12

if.end12:                                         ; preds = %if.else, %if.then7
  %8 = load i64, i64* %extdsize, align 8, !dbg !2598
  %cmp13 = icmp eq i64 %8, 0, !dbg !2600
  br i1 %cmp13, label %if.then15, label %if.end24, !dbg !2601

if.then15:                                        ; preds = %if.end12
  %9 = load i16*, i16** %crc.addr, align 8, !dbg !2602
  %cmp16 = icmp ne i16* %9, null, !dbg !2605
  br i1 %cmp16, label %if.then18, label %if.end21, !dbg !2606

if.then18:                                        ; preds = %if.then15
  %10 = load i16*, i16** %crc.addr, align 8, !dbg !2607
  %11 = load i16, i16* %10, align 2, !dbg !2608
  %12 = load i8*, i8** %h, align 8, !dbg !2609
  %13 = load i32, i32* %sizefield_length.addr, align 4, !dbg !2610
  %conv19 = sext i32 %13 to i64, !dbg !2610
  %call20 = call zeroext i16 @lha_crc16(i16 zeroext %11, i8* %12, i64 %conv19), !dbg !2611
  %14 = load i16*, i16** %crc.addr, align 8, !dbg !2612
  store i16 %call20, i16* %14, align 2, !dbg !2613
  br label %if.end21, !dbg !2614

if.end21:                                         ; preds = %if.then18, %if.then15
  %15 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2615
  %16 = load i32, i32* %sizefield_length.addr, align 4, !dbg !2616
  %conv22 = sext i32 %16 to i64, !dbg !2616
  %call23 = call i64 @__archive_read_consume(%struct.archive_read* %15, i64 %conv22), !dbg !2617
  store i32 0, i32* %retval, align 4, !dbg !2618
  br label %return, !dbg !2618

if.end24:                                         ; preds = %if.end12
  %17 = load i64*, i64** %total_size.addr, align 8, !dbg !2619
  %18 = load i64, i64* %17, align 8, !dbg !2621
  %19 = load i64, i64* %extdsize, align 8, !dbg !2622
  %add = add i64 %18, %19, !dbg !2623
  %20 = load i64, i64* %limitsize.addr, align 8, !dbg !2624
  %cmp25 = icmp ugt i64 %add, %20, !dbg !2625
  br i1 %cmp25, label %if.then30, label %lor.lhs.false, !dbg !2626

lor.lhs.false:                                    ; preds = %if.end24
  %21 = load i64, i64* %extdsize, align 8, !dbg !2627
  %22 = load i32, i32* %sizefield_length.addr, align 4, !dbg !2628
  %conv27 = sext i32 %22 to i64, !dbg !2629
  %cmp28 = icmp ule i64 %21, %conv27, !dbg !2630
  br i1 %cmp28, label %if.then30, label %if.end31, !dbg !2631

if.then30:                                        ; preds = %lor.lhs.false, %if.end24
  br label %invalid, !dbg !2633

if.end31:                                         ; preds = %lor.lhs.false
  %23 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2634
  %24 = load i64, i64* %extdsize, align 8, !dbg !2636
  %call32 = call i8* @__archive_read_ahead(%struct.archive_read* %23, i64 %24, i64* null), !dbg !2637
  store i8* %call32, i8** %h, align 8, !dbg !2638
  %cmp33 = icmp eq i8* %call32, null, !dbg !2639
  br i1 %cmp33, label %if.then35, label %if.end37, !dbg !2640

if.then35:                                        ; preds = %if.end31
  %25 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2641
  %call36 = call i32 @truncated_error(%struct.archive_read* %25), !dbg !2642
  store i32 %call36, i32* %retval, align 4, !dbg !2643
  br label %return, !dbg !2643

if.end37:                                         ; preds = %if.end31
  %26 = load i64, i64* %extdsize, align 8, !dbg !2644
  %27 = load i64*, i64** %total_size.addr, align 8, !dbg !2645
  %28 = load i64, i64* %27, align 8, !dbg !2646
  %add38 = add i64 %28, %26, !dbg !2646
  store i64 %add38, i64* %27, align 8, !dbg !2646
  %29 = load i8*, i8** %h, align 8, !dbg !2647
  store i8* %29, i8** %extdheader, align 8, !dbg !2648
  %30 = load i32, i32* %sizefield_length.addr, align 4, !dbg !2649
  %idxprom = sext i32 %30 to i64, !dbg !2650
  %31 = load i8*, i8** %extdheader, align 8, !dbg !2650
  %arrayidx = getelementptr inbounds i8, i8* %31, i64 %idxprom, !dbg !2650
  %32 = load i8, i8* %arrayidx, align 1, !dbg !2650
  store i8 %32, i8* %extdtype, align 1, !dbg !2651
  %33 = load i64, i64* %extdsize, align 8, !dbg !2652
  %34 = load i32, i32* %sizefield_length.addr, align 4, !dbg !2653
  %add39 = add nsw i32 1, %34, !dbg !2654
  %conv40 = sext i32 %add39 to i64, !dbg !2655
  %sub = sub i64 %33, %conv40, !dbg !2656
  store i64 %sub, i64* %datasize, align 8, !dbg !2657
  %35 = load i32, i32* %sizefield_length.addr, align 4, !dbg !2658
  %add41 = add nsw i32 %35, 1, !dbg !2659
  %36 = load i8*, i8** %extdheader, align 8, !dbg !2660
  %idx.ext = sext i32 %add41 to i64, !dbg !2660
  %add.ptr = getelementptr inbounds i8, i8* %36, i64 %idx.ext, !dbg !2660
  store i8* %add.ptr, i8** %extdheader, align 8, !dbg !2660
  %37 = load i16*, i16** %crc.addr, align 8, !dbg !2661
  %cmp42 = icmp ne i16* %37, null, !dbg !2663
  br i1 %cmp42, label %land.lhs.true, label %if.end49, !dbg !2664

land.lhs.true:                                    ; preds = %if.end37
  %38 = load i8, i8* %extdtype, align 1, !dbg !2665
  %conv44 = zext i8 %38 to i32, !dbg !2665
  %cmp45 = icmp ne i32 %conv44, 0, !dbg !2667
  br i1 %cmp45, label %if.then47, label %if.end49, !dbg !2668

if.then47:                                        ; preds = %land.lhs.true
  %39 = load i16*, i16** %crc.addr, align 8, !dbg !2669
  %40 = load i16, i16* %39, align 2, !dbg !2670
  %41 = load i8*, i8** %h, align 8, !dbg !2671
  %42 = load i64, i64* %extdsize, align 8, !dbg !2672
  %call48 = call zeroext i16 @lha_crc16(i16 zeroext %40, i8* %41, i64 %42), !dbg !2673
  %43 = load i16*, i16** %crc.addr, align 8, !dbg !2674
  store i16 %call48, i16* %43, align 2, !dbg !2675
  br label %if.end49, !dbg !2676

if.end49:                                         ; preds = %if.then47, %land.lhs.true, %if.end37
  %44 = load i8, i8* %extdtype, align 1, !dbg !2677
  %conv50 = zext i8 %44 to i32, !dbg !2677
  switch i32 %conv50, label %sw.default270 [
    i32 0, label %sw.bb
    i32 1, label %sw.bb66
    i32 2, label %sw.bb81
    i32 64, label %sw.bb123
    i32 65, label %sw.bb131
    i32 66, label %sw.bb144
    i32 70, label %sw.bb152
    i32 80, label %sw.bb169
    i32 81, label %sw.bb178
    i32 82, label %sw.bb188
    i32 83, label %sw.bb196
    i32 84, label %sw.bb204
    i32 127, label %sw.bb212
    i32 255, label %sw.bb244
    i32 67, label %sw.bb269
    i32 68, label %sw.bb269
    i32 69, label %sw.bb269
  ], !dbg !2678

sw.bb:                                            ; preds = %if.end49
  %45 = load i64, i64* %datasize, align 8, !dbg !2679
  %cmp51 = icmp uge i64 %45, 2, !dbg !2682
  br i1 %cmp51, label %if.then53, label %if.end65, !dbg !2683

if.then53:                                        ; preds = %sw.bb
  %46 = load i8*, i8** %extdheader, align 8, !dbg !2684
  %call54 = call zeroext i16 @archive_le16dec(i8* %46), !dbg !2686
  %47 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2687
  %header_crc = getelementptr inbounds %struct.lha, %struct.lha* %47, i32 0, i32 21, !dbg !2688
  store i16 %call54, i16* %header_crc, align 8, !dbg !2689
  %48 = load i16*, i16** %crc.addr, align 8, !dbg !2690
  %cmp55 = icmp ne i16* %48, null, !dbg !2692
  br i1 %cmp55, label %if.then57, label %if.end64, !dbg !2693

if.then57:                                        ; preds = %if.then53
  %49 = load i16*, i16** %crc.addr, align 8, !dbg !2694
  %50 = load i16, i16* %49, align 2, !dbg !2696
  %51 = load i8*, i8** %h, align 8, !dbg !2697
  %52 = load i64, i64* %extdsize, align 8, !dbg !2698
  %53 = load i64, i64* %datasize, align 8, !dbg !2699
  %sub58 = sub i64 %52, %53, !dbg !2700
  %call59 = call zeroext i16 @lha_crc16(i16 zeroext %50, i8* %51, i64 %sub58), !dbg !2701
  %54 = load i16*, i16** %crc.addr, align 8, !dbg !2702
  store i16 %call59, i16* %54, align 2, !dbg !2703
  %55 = load i16*, i16** %crc.addr, align 8, !dbg !2704
  %56 = load i16, i16* %55, align 2, !dbg !2705
  %call60 = call zeroext i16 @lha_crc16(i16 zeroext %56, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @lha_read_file_extended_header.zeros, i32 0, i32 0), i64 2), !dbg !2706
  %57 = load i16*, i16** %crc.addr, align 8, !dbg !2707
  store i16 %call60, i16* %57, align 2, !dbg !2708
  %58 = load i16*, i16** %crc.addr, align 8, !dbg !2709
  %59 = load i16, i16* %58, align 2, !dbg !2710
  %60 = load i8*, i8** %extdheader, align 8, !dbg !2711
  %add.ptr61 = getelementptr inbounds i8, i8* %60, i64 2, !dbg !2712
  %61 = load i64, i64* %datasize, align 8, !dbg !2713
  %sub62 = sub i64 %61, 2, !dbg !2714
  %call63 = call zeroext i16 @lha_crc16(i16 zeroext %59, i8* %add.ptr61, i64 %sub62), !dbg !2715
  %62 = load i16*, i16** %crc.addr, align 8, !dbg !2716
  store i16 %call63, i16* %62, align 2, !dbg !2717
  br label %if.end64, !dbg !2718

if.end64:                                         ; preds = %if.then57, %if.then53
  br label %if.end65, !dbg !2719

if.end65:                                         ; preds = %if.end64, %sw.bb
  br label %sw.epilog271, !dbg !2720

sw.bb66:                                          ; preds = %if.end49
  %63 = load i64, i64* %datasize, align 8, !dbg !2721
  %cmp67 = icmp eq i64 %63, 0, !dbg !2723
  br i1 %cmp67, label %if.then69, label %if.end70, !dbg !2724

if.then69:                                        ; preds = %sw.bb66
  %64 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2725
  %filename = getelementptr inbounds %struct.lha, %struct.lha* %64, i32 0, i32 26, !dbg !2725
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %filename, i32 0, i32 1, !dbg !2725
  store i64 0, i64* %length, align 8, !dbg !2725
  br label %sw.epilog271, !dbg !2727

if.end70:                                         ; preds = %sw.bb66
  %65 = load i8*, i8** %extdheader, align 8, !dbg !2728
  %arrayidx71 = getelementptr inbounds i8, i8* %65, i64 0, !dbg !2728
  %66 = load i8, i8* %arrayidx71, align 1, !dbg !2728
  %conv72 = zext i8 %66 to i32, !dbg !2728
  %cmp73 = icmp eq i32 %conv72, 0, !dbg !2730
  br i1 %cmp73, label %if.then75, label %if.end76, !dbg !2731

if.then75:                                        ; preds = %if.end70
  br label %invalid, !dbg !2732

if.end76:                                         ; preds = %if.end70
  %67 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2733
  %filename77 = getelementptr inbounds %struct.lha, %struct.lha* %67, i32 0, i32 26, !dbg !2733
  %length78 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %filename77, i32 0, i32 1, !dbg !2733
  store i64 0, i64* %length78, align 8, !dbg !2733
  %68 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2733
  %filename79 = getelementptr inbounds %struct.lha, %struct.lha* %68, i32 0, i32 26, !dbg !2733
  %69 = load i8*, i8** %extdheader, align 8, !dbg !2733
  %70 = load i64, i64* %datasize, align 8, !dbg !2733
  %call80 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %filename79, i8* %69, i64 %70), !dbg !2733
  br label %sw.epilog271, !dbg !2734

sw.bb81:                                          ; preds = %if.end49
  %71 = load i64, i64* %datasize, align 8, !dbg !2735
  %cmp82 = icmp eq i64 %71, 0, !dbg !2737
  br i1 %cmp82, label %if.then89, label %lor.lhs.false84, !dbg !2738

lor.lhs.false84:                                  ; preds = %sw.bb81
  %72 = load i8*, i8** %extdheader, align 8, !dbg !2739
  %arrayidx85 = getelementptr inbounds i8, i8* %72, i64 0, !dbg !2739
  %73 = load i8, i8* %arrayidx85, align 1, !dbg !2739
  %conv86 = zext i8 %73 to i32, !dbg !2739
  %cmp87 = icmp eq i32 %conv86, 0, !dbg !2741
  br i1 %cmp87, label %if.then89, label %if.end90, !dbg !2742

if.then89:                                        ; preds = %lor.lhs.false84, %sw.bb81
  br label %invalid, !dbg !2743

if.end90:                                         ; preds = %lor.lhs.false84
  %74 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2744
  %dirname = getelementptr inbounds %struct.lha, %struct.lha* %74, i32 0, i32 25, !dbg !2744
  %length91 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %dirname, i32 0, i32 1, !dbg !2744
  store i64 0, i64* %length91, align 8, !dbg !2744
  %75 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2744
  %dirname92 = getelementptr inbounds %struct.lha, %struct.lha* %75, i32 0, i32 25, !dbg !2744
  %76 = load i8*, i8** %extdheader, align 8, !dbg !2744
  %77 = load i64, i64* %datasize, align 8, !dbg !2744
  %call93 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %dirname92, i8* %76, i64 %77), !dbg !2744
  store i32 0, i32* %i, align 4, !dbg !2745
  br label %for.cond94, !dbg !2747

for.cond94:                                       ; preds = %for.inc, %if.end90
  %78 = load i32, i32* %i, align 4, !dbg !2748
  %conv95 = zext i32 %78 to i64, !dbg !2748
  %79 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2751
  %dirname96 = getelementptr inbounds %struct.lha, %struct.lha* %79, i32 0, i32 25, !dbg !2752
  %length97 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %dirname96, i32 0, i32 1, !dbg !2753
  %80 = load i64, i64* %length97, align 8, !dbg !2753
  %cmp98 = icmp ult i64 %conv95, %80, !dbg !2754
  br i1 %cmp98, label %for.body, label %for.end, !dbg !2755

for.body:                                         ; preds = %for.cond94
  %81 = load i32, i32* %i, align 4, !dbg !2756
  %idxprom100 = zext i32 %81 to i64, !dbg !2759
  %82 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2759
  %dirname101 = getelementptr inbounds %struct.lha, %struct.lha* %82, i32 0, i32 25, !dbg !2760
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %dirname101, i32 0, i32 0, !dbg !2761
  %83 = load i8*, i8** %s, align 8, !dbg !2761
  %arrayidx102 = getelementptr inbounds i8, i8* %83, i64 %idxprom100, !dbg !2759
  %84 = load i8, i8* %arrayidx102, align 1, !dbg !2759
  %conv103 = zext i8 %84 to i32, !dbg !2762
  %cmp104 = icmp eq i32 %conv103, 255, !dbg !2763
  br i1 %cmp104, label %if.then106, label %if.end111, !dbg !2764

if.then106:                                       ; preds = %for.body
  %85 = load i32, i32* %i, align 4, !dbg !2765
  %idxprom107 = zext i32 %85 to i64, !dbg !2766
  %86 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2766
  %dirname108 = getelementptr inbounds %struct.lha, %struct.lha* %86, i32 0, i32 25, !dbg !2767
  %s109 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %dirname108, i32 0, i32 0, !dbg !2768
  %87 = load i8*, i8** %s109, align 8, !dbg !2768
  %arrayidx110 = getelementptr inbounds i8, i8* %87, i64 %idxprom107, !dbg !2766
  store i8 47, i8* %arrayidx110, align 1, !dbg !2769
  br label %if.end111, !dbg !2766

if.end111:                                        ; preds = %if.then106, %for.body
  br label %for.inc, !dbg !2770

for.inc:                                          ; preds = %if.end111
  %88 = load i32, i32* %i, align 4, !dbg !2771
  %inc = add i32 %88, 1, !dbg !2771
  store i32 %inc, i32* %i, align 4, !dbg !2771
  br label %for.cond94, !dbg !2773

for.end:                                          ; preds = %for.cond94
  %89 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2774
  %dirname112 = getelementptr inbounds %struct.lha, %struct.lha* %89, i32 0, i32 25, !dbg !2776
  %length113 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %dirname112, i32 0, i32 1, !dbg !2777
  %90 = load i64, i64* %length113, align 8, !dbg !2777
  %sub114 = sub i64 %90, 1, !dbg !2778
  %91 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2779
  %dirname115 = getelementptr inbounds %struct.lha, %struct.lha* %91, i32 0, i32 25, !dbg !2780
  %s116 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %dirname115, i32 0, i32 0, !dbg !2781
  %92 = load i8*, i8** %s116, align 8, !dbg !2781
  %arrayidx117 = getelementptr inbounds i8, i8* %92, i64 %sub114, !dbg !2779
  %93 = load i8, i8* %arrayidx117, align 1, !dbg !2779
  %conv118 = sext i8 %93 to i32, !dbg !2779
  %cmp119 = icmp ne i32 %conv118, 47, !dbg !2782
  br i1 %cmp119, label %if.then121, label %if.end122, !dbg !2783

if.then121:                                       ; preds = %for.end
  br label %invalid, !dbg !2784

if.end122:                                        ; preds = %for.end
  br label %sw.epilog271, !dbg !2785

sw.bb123:                                         ; preds = %if.end49
  %94 = load i64, i64* %datasize, align 8, !dbg !2786
  %cmp124 = icmp eq i64 %94, 2, !dbg !2788
  br i1 %cmp124, label %if.then126, label %if.end130, !dbg !2789

if.then126:                                       ; preds = %sw.bb123
  %95 = load i8*, i8** %extdheader, align 8, !dbg !2790
  %call127 = call zeroext i16 @archive_le16dec(i8* %95), !dbg !2791
  %conv128 = zext i16 %call127 to i32, !dbg !2791
  %and = and i32 %conv128, 255, !dbg !2792
  %conv129 = trunc i32 %and to i8, !dbg !2793
  %96 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2794
  %dos_attr = getelementptr inbounds %struct.lha, %struct.lha* %96, i32 0, i32 28, !dbg !2795
  store i8 %conv129, i8* %dos_attr, align 8, !dbg !2796
  br label %if.end130, !dbg !2794

if.end130:                                        ; preds = %if.then126, %sw.bb123
  br label %sw.epilog271, !dbg !2797

sw.bb131:                                         ; preds = %if.end49
  %97 = load i64, i64* %datasize, align 8, !dbg !2798
  %cmp132 = icmp eq i64 %97, 24, !dbg !2800
  br i1 %cmp132, label %if.then134, label %if.end143, !dbg !2801

if.then134:                                       ; preds = %sw.bb131
  %98 = load i8*, i8** %extdheader, align 8, !dbg !2802
  %call135 = call i64 @archive_le64dec(i8* %98), !dbg !2804
  %99 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2805
  %birthtime_tv_nsec = getelementptr inbounds %struct.lha, %struct.lha* %99, i32 0, i32 11, !dbg !2806
  %call136 = call i64 @lha_win_time(i64 %call135, i64* %birthtime_tv_nsec), !dbg !2807
  %100 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2808
  %birthtime = getelementptr inbounds %struct.lha, %struct.lha* %100, i32 0, i32 10, !dbg !2809
  store i64 %call136, i64* %birthtime, align 8, !dbg !2810
  %101 = load i8*, i8** %extdheader, align 8, !dbg !2811
  %add.ptr137 = getelementptr inbounds i8, i8* %101, i64 8, !dbg !2811
  store i8* %add.ptr137, i8** %extdheader, align 8, !dbg !2811
  %102 = load i8*, i8** %extdheader, align 8, !dbg !2812
  %call138 = call i64 @archive_le64dec(i8* %102), !dbg !2813
  %103 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2814
  %mtime_tv_nsec = getelementptr inbounds %struct.lha, %struct.lha* %103, i32 0, i32 13, !dbg !2815
  %call139 = call i64 @lha_win_time(i64 %call138, i64* %mtime_tv_nsec), !dbg !2816
  %104 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2817
  %mtime = getelementptr inbounds %struct.lha, %struct.lha* %104, i32 0, i32 12, !dbg !2818
  store i64 %call139, i64* %mtime, align 8, !dbg !2819
  %105 = load i8*, i8** %extdheader, align 8, !dbg !2820
  %add.ptr140 = getelementptr inbounds i8, i8* %105, i64 8, !dbg !2820
  store i8* %add.ptr140, i8** %extdheader, align 8, !dbg !2820
  %106 = load i8*, i8** %extdheader, align 8, !dbg !2821
  %call141 = call i64 @archive_le64dec(i8* %106), !dbg !2822
  %107 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2823
  %atime_tv_nsec = getelementptr inbounds %struct.lha, %struct.lha* %107, i32 0, i32 15, !dbg !2824
  %call142 = call i64 @lha_win_time(i64 %call141, i64* %atime_tv_nsec), !dbg !2825
  %108 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2826
  %atime = getelementptr inbounds %struct.lha, %struct.lha* %108, i32 0, i32 14, !dbg !2827
  store i64 %call142, i64* %atime, align 8, !dbg !2828
  %109 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2829
  %setflag = getelementptr inbounds %struct.lha, %struct.lha* %109, i32 0, i32 9, !dbg !2830
  %110 = load i32, i32* %setflag, align 8, !dbg !2831
  %or = or i32 %110, 3, !dbg !2831
  store i32 %or, i32* %setflag, align 8, !dbg !2831
  br label %if.end143, !dbg !2832

if.end143:                                        ; preds = %if.then134, %sw.bb131
  br label %sw.epilog271, !dbg !2833

sw.bb144:                                         ; preds = %if.end49
  %111 = load i64, i64* %datasize, align 8, !dbg !2834
  %cmp145 = icmp eq i64 %111, 16, !dbg !2836
  br i1 %cmp145, label %if.then147, label %if.end151, !dbg !2837

if.then147:                                       ; preds = %sw.bb144
  %112 = load i8*, i8** %extdheader, align 8, !dbg !2838
  %call148 = call i64 @archive_le64dec(i8* %112), !dbg !2840
  %113 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2841
  %compsize = getelementptr inbounds %struct.lha, %struct.lha* %113, i32 0, i32 7, !dbg !2842
  store i64 %call148, i64* %compsize, align 8, !dbg !2843
  %114 = load i8*, i8** %extdheader, align 8, !dbg !2844
  %add.ptr149 = getelementptr inbounds i8, i8* %114, i64 8, !dbg !2844
  store i8* %add.ptr149, i8** %extdheader, align 8, !dbg !2844
  %115 = load i8*, i8** %extdheader, align 8, !dbg !2845
  %call150 = call i64 @archive_le64dec(i8* %115), !dbg !2846
  %116 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2847
  %origsize = getelementptr inbounds %struct.lha, %struct.lha* %116, i32 0, i32 8, !dbg !2848
  store i64 %call150, i64* %origsize, align 8, !dbg !2849
  br label %if.end151, !dbg !2850

if.end151:                                        ; preds = %if.then147, %sw.bb144
  br label %sw.epilog271, !dbg !2851

sw.bb152:                                         ; preds = %if.end49
  %117 = load i64, i64* %datasize, align 8, !dbg !2852
  %cmp153 = icmp eq i64 %117, 4, !dbg !2854
  br i1 %cmp153, label %if.then155, label %if.end168, !dbg !2855

if.then155:                                       ; preds = %sw.bb152
  call void @llvm.dbg.declare(metadata %struct.archive_string* %cp, metadata !2856, metadata !548), !dbg !2858
  call void @llvm.dbg.declare(metadata i8** %charset, metadata !2859, metadata !548), !dbg !2860
  br label %do.body, !dbg !2861

do.body:                                          ; preds = %if.then155
  %s156 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %cp, i32 0, i32 0, !dbg !2862
  store i8* null, i8** %s156, align 8, !dbg !2862
  %length157 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %cp, i32 0, i32 1, !dbg !2862
  store i64 0, i64* %length157, align 8, !dbg !2862
  %buffer_length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %cp, i32 0, i32 2, !dbg !2862
  store i64 0, i64* %buffer_length, align 8, !dbg !2862
  br label %do.end, !dbg !2862

do.end:                                           ; preds = %do.body
  %118 = load i8*, i8** %extdheader, align 8, !dbg !2865
  %call158 = call i32 @archive_le32dec(i8* %118), !dbg !2866
  switch i32 %call158, label %sw.default [
    i32 65001, label %sw.bb159
  ], !dbg !2867

sw.bb159:                                         ; preds = %do.end
  store i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.20, i32 0, i32 0), i8** %charset, align 8, !dbg !2868
  br label %sw.epilog, !dbg !2870

sw.default:                                       ; preds = %do.end
  %119 = load i8*, i8** %extdheader, align 8, !dbg !2871
  %call160 = call i32 @archive_le32dec(i8* %119), !dbg !2872
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %cp, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.21, i32 0, i32 0), i32 %call160), !dbg !2873
  %s161 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %cp, i32 0, i32 0, !dbg !2874
  %120 = load i8*, i8** %s161, align 8, !dbg !2874
  store i8* %120, i8** %charset, align 8, !dbg !2875
  br label %sw.epilog, !dbg !2876

sw.epilog:                                        ; preds = %sw.default, %sw.bb159
  %121 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2877
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %121, i32 0, i32 0, !dbg !2878
  %122 = load i8*, i8** %charset, align 8, !dbg !2879
  %call162 = call %struct.archive_string_conv* @archive_string_conversion_from_charset(%struct.archive* %archive, i8* %122, i32 1), !dbg !2880
  %123 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2881
  %sconv = getelementptr inbounds %struct.lha, %struct.lha* %123, i32 0, i32 23, !dbg !2882
  store %struct.archive_string_conv* %call162, %struct.archive_string_conv** %sconv, align 8, !dbg !2883
  call void @archive_string_free(%struct.archive_string* %cp), !dbg !2884
  %124 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2885
  %sconv163 = getelementptr inbounds %struct.lha, %struct.lha* %124, i32 0, i32 23, !dbg !2887
  %125 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv163, align 8, !dbg !2887
  %cmp164 = icmp eq %struct.archive_string_conv* %125, null, !dbg !2888
  br i1 %cmp164, label %if.then166, label %if.end167, !dbg !2889

if.then166:                                       ; preds = %sw.epilog
  store i32 -30, i32* %retval, align 4, !dbg !2890
  br label %return, !dbg !2890

if.end167:                                        ; preds = %sw.epilog
  br label %if.end168, !dbg !2891

if.end168:                                        ; preds = %if.end167, %sw.bb152
  br label %sw.epilog271, !dbg !2892

sw.bb169:                                         ; preds = %if.end49
  %126 = load i64, i64* %datasize, align 8, !dbg !2893
  %cmp170 = icmp eq i64 %126, 2, !dbg !2895
  br i1 %cmp170, label %if.then172, label %if.end177, !dbg !2896

if.then172:                                       ; preds = %sw.bb169
  %127 = load i8*, i8** %extdheader, align 8, !dbg !2897
  %call173 = call zeroext i16 @archive_le16dec(i8* %127), !dbg !2899
  %conv174 = zext i16 %call173 to i32, !dbg !2899
  %128 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2900
  %mode = getelementptr inbounds %struct.lha, %struct.lha* %128, i32 0, i32 16, !dbg !2901
  store i32 %conv174, i32* %mode, align 8, !dbg !2902
  %129 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2903
  %setflag175 = getelementptr inbounds %struct.lha, %struct.lha* %129, i32 0, i32 9, !dbg !2904
  %130 = load i32, i32* %setflag175, align 8, !dbg !2905
  %or176 = or i32 %130, 4, !dbg !2905
  store i32 %or176, i32* %setflag175, align 8, !dbg !2905
  br label %if.end177, !dbg !2906

if.end177:                                        ; preds = %if.then172, %sw.bb169
  br label %sw.epilog271, !dbg !2907

sw.bb178:                                         ; preds = %if.end49
  %131 = load i64, i64* %datasize, align 8, !dbg !2908
  %cmp179 = icmp eq i64 %131, 4, !dbg !2910
  br i1 %cmp179, label %if.then181, label %if.end187, !dbg !2911

if.then181:                                       ; preds = %sw.bb178
  %132 = load i8*, i8** %extdheader, align 8, !dbg !2912
  %call182 = call zeroext i16 @archive_le16dec(i8* %132), !dbg !2914
  %conv183 = zext i16 %call182 to i64, !dbg !2914
  %133 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2915
  %gid = getelementptr inbounds %struct.lha, %struct.lha* %133, i32 0, i32 18, !dbg !2916
  store i64 %conv183, i64* %gid, align 8, !dbg !2917
  %134 = load i8*, i8** %extdheader, align 8, !dbg !2918
  %add.ptr184 = getelementptr inbounds i8, i8* %134, i64 2, !dbg !2919
  %call185 = call zeroext i16 @archive_le16dec(i8* %add.ptr184), !dbg !2920
  %conv186 = zext i16 %call185 to i64, !dbg !2920
  %135 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2921
  %uid = getelementptr inbounds %struct.lha, %struct.lha* %135, i32 0, i32 17, !dbg !2922
  store i64 %conv186, i64* %uid, align 8, !dbg !2923
  br label %if.end187, !dbg !2924

if.end187:                                        ; preds = %if.then181, %sw.bb178
  br label %sw.epilog271, !dbg !2925

sw.bb188:                                         ; preds = %if.end49
  %136 = load i64, i64* %datasize, align 8, !dbg !2926
  %cmp189 = icmp ugt i64 %136, 0, !dbg !2928
  br i1 %cmp189, label %if.then191, label %if.end195, !dbg !2929

if.then191:                                       ; preds = %sw.bb188
  %137 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2930
  %gname = getelementptr inbounds %struct.lha, %struct.lha* %137, i32 0, i32 20, !dbg !2930
  %length192 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %gname, i32 0, i32 1, !dbg !2930
  store i64 0, i64* %length192, align 8, !dbg !2930
  %138 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2930
  %gname193 = getelementptr inbounds %struct.lha, %struct.lha* %138, i32 0, i32 20, !dbg !2930
  %139 = load i8*, i8** %extdheader, align 8, !dbg !2930
  %140 = load i64, i64* %datasize, align 8, !dbg !2930
  %call194 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %gname193, i8* %139, i64 %140), !dbg !2930
  br label %if.end195, !dbg !2930

if.end195:                                        ; preds = %if.then191, %sw.bb188
  br label %sw.epilog271, !dbg !2931

sw.bb196:                                         ; preds = %if.end49
  %141 = load i64, i64* %datasize, align 8, !dbg !2932
  %cmp197 = icmp ugt i64 %141, 0, !dbg !2934
  br i1 %cmp197, label %if.then199, label %if.end203, !dbg !2935

if.then199:                                       ; preds = %sw.bb196
  %142 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2936
  %uname = getelementptr inbounds %struct.lha, %struct.lha* %142, i32 0, i32 19, !dbg !2936
  %length200 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %uname, i32 0, i32 1, !dbg !2936
  store i64 0, i64* %length200, align 8, !dbg !2936
  %143 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2936
  %uname201 = getelementptr inbounds %struct.lha, %struct.lha* %143, i32 0, i32 19, !dbg !2936
  %144 = load i8*, i8** %extdheader, align 8, !dbg !2936
  %145 = load i64, i64* %datasize, align 8, !dbg !2936
  %call202 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %uname201, i8* %144, i64 %145), !dbg !2936
  br label %if.end203, !dbg !2936

if.end203:                                        ; preds = %if.then199, %sw.bb196
  br label %sw.epilog271, !dbg !2937

sw.bb204:                                         ; preds = %if.end49
  %146 = load i64, i64* %datasize, align 8, !dbg !2938
  %cmp205 = icmp eq i64 %146, 4, !dbg !2940
  br i1 %cmp205, label %if.then207, label %if.end211, !dbg !2941

if.then207:                                       ; preds = %sw.bb204
  %147 = load i8*, i8** %extdheader, align 8, !dbg !2942
  %call208 = call i32 @archive_le32dec(i8* %147), !dbg !2943
  %conv209 = zext i32 %call208 to i64, !dbg !2943
  %148 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2944
  %mtime210 = getelementptr inbounds %struct.lha, %struct.lha* %148, i32 0, i32 12, !dbg !2945
  store i64 %conv209, i64* %mtime210, align 8, !dbg !2946
  br label %if.end211, !dbg !2944

if.end211:                                        ; preds = %if.then207, %sw.bb204
  br label %sw.epilog271, !dbg !2947

sw.bb212:                                         ; preds = %if.end49
  %149 = load i64, i64* %datasize, align 8, !dbg !2948
  %cmp213 = icmp eq i64 %149, 16, !dbg !2950
  br i1 %cmp213, label %if.then215, label %if.end243, !dbg !2951

if.then215:                                       ; preds = %sw.bb212
  %150 = load i8*, i8** %extdheader, align 8, !dbg !2952
  %call216 = call zeroext i16 @archive_le16dec(i8* %150), !dbg !2954
  %conv217 = zext i16 %call216 to i32, !dbg !2954
  %and218 = and i32 %conv217, 255, !dbg !2955
  %conv219 = trunc i32 %and218 to i8, !dbg !2956
  %151 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2957
  %dos_attr220 = getelementptr inbounds %struct.lha, %struct.lha* %151, i32 0, i32 28, !dbg !2958
  store i8 %conv219, i8* %dos_attr220, align 8, !dbg !2959
  %152 = load i8*, i8** %extdheader, align 8, !dbg !2960
  %add.ptr221 = getelementptr inbounds i8, i8* %152, i64 2, !dbg !2961
  %call222 = call zeroext i16 @archive_le16dec(i8* %add.ptr221), !dbg !2962
  %conv223 = zext i16 %call222 to i32, !dbg !2962
  %153 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2963
  %mode224 = getelementptr inbounds %struct.lha, %struct.lha* %153, i32 0, i32 16, !dbg !2964
  store i32 %conv223, i32* %mode224, align 8, !dbg !2965
  %154 = load i8*, i8** %extdheader, align 8, !dbg !2966
  %add.ptr225 = getelementptr inbounds i8, i8* %154, i64 4, !dbg !2967
  %call226 = call zeroext i16 @archive_le16dec(i8* %add.ptr225), !dbg !2968
  %conv227 = zext i16 %call226 to i64, !dbg !2968
  %155 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2969
  %gid228 = getelementptr inbounds %struct.lha, %struct.lha* %155, i32 0, i32 18, !dbg !2970
  store i64 %conv227, i64* %gid228, align 8, !dbg !2971
  %156 = load i8*, i8** %extdheader, align 8, !dbg !2972
  %add.ptr229 = getelementptr inbounds i8, i8* %156, i64 6, !dbg !2973
  %call230 = call zeroext i16 @archive_le16dec(i8* %add.ptr229), !dbg !2974
  %conv231 = zext i16 %call230 to i64, !dbg !2974
  %157 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2975
  %uid232 = getelementptr inbounds %struct.lha, %struct.lha* %157, i32 0, i32 17, !dbg !2976
  store i64 %conv231, i64* %uid232, align 8, !dbg !2977
  %158 = load i8*, i8** %extdheader, align 8, !dbg !2978
  %add.ptr233 = getelementptr inbounds i8, i8* %158, i64 8, !dbg !2979
  %call234 = call i32 @archive_le32dec(i8* %add.ptr233), !dbg !2980
  %conv235 = zext i32 %call234 to i64, !dbg !2980
  %159 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2981
  %birthtime236 = getelementptr inbounds %struct.lha, %struct.lha* %159, i32 0, i32 10, !dbg !2982
  store i64 %conv235, i64* %birthtime236, align 8, !dbg !2983
  %160 = load i8*, i8** %extdheader, align 8, !dbg !2984
  %add.ptr237 = getelementptr inbounds i8, i8* %160, i64 12, !dbg !2985
  %call238 = call i32 @archive_le32dec(i8* %add.ptr237), !dbg !2986
  %conv239 = zext i32 %call238 to i64, !dbg !2986
  %161 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2987
  %atime240 = getelementptr inbounds %struct.lha, %struct.lha* %161, i32 0, i32 14, !dbg !2988
  store i64 %conv239, i64* %atime240, align 8, !dbg !2989
  %162 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !2990
  %setflag241 = getelementptr inbounds %struct.lha, %struct.lha* %162, i32 0, i32 9, !dbg !2991
  %163 = load i32, i32* %setflag241, align 8, !dbg !2992
  %or242 = or i32 %163, 7, !dbg !2992
  store i32 %or242, i32* %setflag241, align 8, !dbg !2992
  br label %if.end243, !dbg !2993

if.end243:                                        ; preds = %if.then215, %sw.bb212
  br label %sw.epilog271, !dbg !2994

sw.bb244:                                         ; preds = %if.end49
  %164 = load i64, i64* %datasize, align 8, !dbg !2995
  %cmp245 = icmp eq i64 %164, 20, !dbg !2997
  br i1 %cmp245, label %if.then247, label %if.end268, !dbg !2998

if.then247:                                       ; preds = %sw.bb244
  %165 = load i8*, i8** %extdheader, align 8, !dbg !2999
  %call248 = call i32 @archive_le32dec(i8* %165), !dbg !3001
  %166 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !3002
  %mode249 = getelementptr inbounds %struct.lha, %struct.lha* %166, i32 0, i32 16, !dbg !3003
  store i32 %call248, i32* %mode249, align 8, !dbg !3004
  %167 = load i8*, i8** %extdheader, align 8, !dbg !3005
  %add.ptr250 = getelementptr inbounds i8, i8* %167, i64 4, !dbg !3006
  %call251 = call i32 @archive_le32dec(i8* %add.ptr250), !dbg !3007
  %conv252 = zext i32 %call251 to i64, !dbg !3007
  %168 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !3008
  %gid253 = getelementptr inbounds %struct.lha, %struct.lha* %168, i32 0, i32 18, !dbg !3009
  store i64 %conv252, i64* %gid253, align 8, !dbg !3010
  %169 = load i8*, i8** %extdheader, align 8, !dbg !3011
  %add.ptr254 = getelementptr inbounds i8, i8* %169, i64 8, !dbg !3012
  %call255 = call i32 @archive_le32dec(i8* %add.ptr254), !dbg !3013
  %conv256 = zext i32 %call255 to i64, !dbg !3013
  %170 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !3014
  %uid257 = getelementptr inbounds %struct.lha, %struct.lha* %170, i32 0, i32 17, !dbg !3015
  store i64 %conv256, i64* %uid257, align 8, !dbg !3016
  %171 = load i8*, i8** %extdheader, align 8, !dbg !3017
  %add.ptr258 = getelementptr inbounds i8, i8* %171, i64 12, !dbg !3018
  %call259 = call i32 @archive_le32dec(i8* %add.ptr258), !dbg !3019
  %conv260 = zext i32 %call259 to i64, !dbg !3019
  %172 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !3020
  %birthtime261 = getelementptr inbounds %struct.lha, %struct.lha* %172, i32 0, i32 10, !dbg !3021
  store i64 %conv260, i64* %birthtime261, align 8, !dbg !3022
  %173 = load i8*, i8** %extdheader, align 8, !dbg !3023
  %add.ptr262 = getelementptr inbounds i8, i8* %173, i64 16, !dbg !3024
  %call263 = call i32 @archive_le32dec(i8* %add.ptr262), !dbg !3025
  %conv264 = zext i32 %call263 to i64, !dbg !3025
  %174 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !3026
  %atime265 = getelementptr inbounds %struct.lha, %struct.lha* %174, i32 0, i32 14, !dbg !3027
  store i64 %conv264, i64* %atime265, align 8, !dbg !3028
  %175 = load %struct.lha*, %struct.lha** %lha.addr, align 8, !dbg !3029
  %setflag266 = getelementptr inbounds %struct.lha, %struct.lha* %175, i32 0, i32 9, !dbg !3030
  %176 = load i32, i32* %setflag266, align 8, !dbg !3031
  %or267 = or i32 %176, 7, !dbg !3031
  store i32 %or267, i32* %setflag266, align 8, !dbg !3031
  br label %if.end268, !dbg !3032

if.end268:                                        ; preds = %if.then247, %sw.bb244
  br label %sw.epilog271, !dbg !3033

sw.bb269:                                         ; preds = %if.end49, %if.end49, %if.end49
  br label %sw.default270, !dbg !3034

sw.default270:                                    ; preds = %if.end49, %sw.bb269
  br label %sw.epilog271, !dbg !3036

sw.epilog271:                                     ; preds = %sw.default270, %if.end268, %if.end243, %if.end211, %if.end203, %if.end195, %if.end187, %if.end177, %if.end168, %if.end151, %if.end143, %if.end130, %if.end122, %if.end76, %if.then69, %if.end65
  %177 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3037
  %178 = load i64, i64* %extdsize, align 8, !dbg !3038
  %call272 = call i64 @__archive_read_consume(%struct.archive_read* %177, i64 %178), !dbg !3039
  br label %for.cond, !dbg !3040

invalid:                                          ; preds = %if.then121, %if.then89, %if.then75, %if.then30
  %179 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3042
  %archive273 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %179, i32 0, i32 0, !dbg !3043
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive273, i32 84, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.22, i32 0, i32 0)), !dbg !3044
  store i32 -30, i32* %retval, align 4, !dbg !3045
  br label %return, !dbg !3045

return:                                           ; preds = %invalid, %if.then166, %if.then35, %if.end21, %if.then
  %180 = load i32, i32* %retval, align 4, !dbg !3046
  ret i32 %180, !dbg !3046
}

; Function Attrs: nounwind uwtable
define internal zeroext i16 @lha_crc16(i16 zeroext %crc, i8* %pp, i64 %len) #0 !dbg !451 {
entry:
  %retval = alloca i16, align 2
  %crc.addr = alloca i16, align 2
  %pp.addr = alloca i8*, align 8
  %len.addr = alloca i64, align 8
  %p = alloca i8*, align 8
  %buff = alloca i16*, align 8
  store i16 %crc, i16* %crc.addr, align 2
  call void @llvm.dbg.declare(metadata i16* %crc.addr, metadata !3047, metadata !548), !dbg !3048
  store i8* %pp, i8** %pp.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %pp.addr, metadata !3049, metadata !548), !dbg !3050
  store i64 %len, i64* %len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %len.addr, metadata !3051, metadata !548), !dbg !3052
  call void @llvm.dbg.declare(metadata i8** %p, metadata !3053, metadata !548), !dbg !3054
  %0 = load i8*, i8** %pp.addr, align 8, !dbg !3055
  store i8* %0, i8** %p, align 8, !dbg !3054
  call void @llvm.dbg.declare(metadata i16** %buff, metadata !3056, metadata !548), !dbg !3057
  %1 = load i64, i64* %len.addr, align 8, !dbg !3058
  %cmp = icmp eq i64 %1, 0, !dbg !3060
  br i1 %cmp, label %if.then, label %if.end, !dbg !3061

if.then:                                          ; preds = %entry
  %2 = load i16, i16* %crc.addr, align 2, !dbg !3062
  store i16 %2, i16* %retval, align 2, !dbg !3063
  br label %return, !dbg !3063

if.end:                                           ; preds = %entry
  %3 = load i8*, i8** %p, align 8, !dbg !3064
  %4 = ptrtoint i8* %3 to i64, !dbg !3066
  %and = and i64 %4, 1, !dbg !3067
  %tobool = icmp ne i64 %and, 0, !dbg !3067
  br i1 %tobool, label %if.then1, label %if.end8, !dbg !3068

if.then1:                                         ; preds = %if.end
  %5 = load i16, i16* %crc.addr, align 2, !dbg !3069
  %conv = zext i16 %5 to i32, !dbg !3069
  %shr = ashr i32 %conv, 8, !dbg !3071
  %6 = load i16, i16* %crc.addr, align 2, !dbg !3072
  %conv2 = zext i16 %6 to i32, !dbg !3072
  %7 = load i8*, i8** %p, align 8, !dbg !3073
  %incdec.ptr = getelementptr inbounds i8, i8* %7, i32 1, !dbg !3073
  store i8* %incdec.ptr, i8** %p, align 8, !dbg !3073
  %8 = load i8, i8* %7, align 1, !dbg !3074
  %conv3 = zext i8 %8 to i32, !dbg !3074
  %xor = xor i32 %conv2, %conv3, !dbg !3075
  %and4 = and i32 %xor, 255, !dbg !3076
  %idxprom = sext i32 %and4 to i64, !dbg !3077
  %arrayidx = getelementptr inbounds [256 x i16], [256 x i16]* getelementptr inbounds ([2 x [256 x i16]], [2 x [256 x i16]]* @crc16tbl, i64 0, i64 0), i64 0, i64 %idxprom, !dbg !3077
  %9 = load i16, i16* %arrayidx, align 2, !dbg !3077
  %conv5 = zext i16 %9 to i32, !dbg !3077
  %xor6 = xor i32 %shr, %conv5, !dbg !3078
  %conv7 = trunc i32 %xor6 to i16, !dbg !3079
  store i16 %conv7, i16* %crc.addr, align 2, !dbg !3080
  %10 = load i64, i64* %len.addr, align 8, !dbg !3081
  %dec = add i64 %10, -1, !dbg !3081
  store i64 %dec, i64* %len.addr, align 8, !dbg !3081
  br label %if.end8, !dbg !3082

if.end8:                                          ; preds = %if.then1, %if.end
  %11 = load i8*, i8** %p, align 8, !dbg !3083
  %12 = bitcast i8* %11 to i16*, !dbg !3084
  store i16* %12, i16** %buff, align 8, !dbg !3085
  br label %for.cond, !dbg !3086

for.cond:                                         ; preds = %for.inc, %if.end8
  %13 = load i64, i64* %len.addr, align 8, !dbg !3087
  %cmp9 = icmp uge i64 %13, 8, !dbg !3091
  br i1 %cmp9, label %for.body, label %for.end, !dbg !3092

for.body:                                         ; preds = %for.cond
  br label %do.body, !dbg !3093

do.body:                                          ; preds = %for.body
  %14 = load i8, i8* getelementptr inbounds ([4 x i8], [4 x i8]* bitcast (%union.anon* @lha_crc16.u to [4 x i8]*), i64 0, i64 0), align 4, !dbg !3095
  %conv11 = sext i8 %14 to i32, !dbg !3095
  %cmp12 = icmp eq i32 %conv11, 1, !dbg !3095
  br i1 %cmp12, label %if.then14, label %if.else, !dbg !3095

if.then14:                                        ; preds = %do.body
  %15 = load i16*, i16** %buff, align 8, !dbg !3099
  %16 = load i16, i16* %15, align 2, !dbg !3099
  %17 = call i16 @llvm.bswap.i16(i16 %16), !dbg !3099
  %conv15 = zext i16 %17 to i32, !dbg !3099
  %18 = load i16, i16* %crc.addr, align 2, !dbg !3099
  %conv16 = zext i16 %18 to i32, !dbg !3099
  %xor17 = xor i32 %conv16, %conv15, !dbg !3099
  %conv18 = trunc i32 %xor17 to i16, !dbg !3099
  store i16 %conv18, i16* %crc.addr, align 2, !dbg !3099
  %19 = load i16*, i16** %buff, align 8, !dbg !3099
  %incdec.ptr19 = getelementptr inbounds i16, i16* %19, i32 1, !dbg !3099
  store i16* %incdec.ptr19, i16** %buff, align 8, !dbg !3099
  br label %if.end25, !dbg !3099

if.else:                                          ; preds = %do.body
  %20 = load i16*, i16** %buff, align 8, !dbg !3102
  %incdec.ptr20 = getelementptr inbounds i16, i16* %20, i32 1, !dbg !3102
  store i16* %incdec.ptr20, i16** %buff, align 8, !dbg !3102
  %21 = load i16, i16* %20, align 2, !dbg !3102
  %conv21 = zext i16 %21 to i32, !dbg !3102
  %22 = load i16, i16* %crc.addr, align 2, !dbg !3102
  %conv22 = zext i16 %22 to i32, !dbg !3102
  %xor23 = xor i32 %conv22, %conv21, !dbg !3102
  %conv24 = trunc i32 %xor23 to i16, !dbg !3102
  store i16 %conv24, i16* %crc.addr, align 2, !dbg !3102
  br label %if.end25

if.end25:                                         ; preds = %if.else, %if.then14
  %23 = load i16, i16* %crc.addr, align 2, !dbg !3104
  %conv26 = zext i16 %23 to i32, !dbg !3104
  %and27 = and i32 %conv26, 255, !dbg !3104
  %idxprom28 = sext i32 %and27 to i64, !dbg !3104
  %arrayidx29 = getelementptr inbounds [256 x i16], [256 x i16]* getelementptr inbounds ([2 x [256 x i16]], [2 x [256 x i16]]* @crc16tbl, i64 0, i64 1), i64 0, i64 %idxprom28, !dbg !3104
  %24 = load i16, i16* %arrayidx29, align 2, !dbg !3104
  %conv30 = zext i16 %24 to i32, !dbg !3104
  %25 = load i16, i16* %crc.addr, align 2, !dbg !3104
  %conv31 = zext i16 %25 to i32, !dbg !3104
  %shr32 = ashr i32 %conv31, 8, !dbg !3104
  %idxprom33 = sext i32 %shr32 to i64, !dbg !3104
  %arrayidx34 = getelementptr inbounds [256 x i16], [256 x i16]* getelementptr inbounds ([2 x [256 x i16]], [2 x [256 x i16]]* @crc16tbl, i64 0, i64 0), i64 0, i64 %idxprom33, !dbg !3104
  %26 = load i16, i16* %arrayidx34, align 2, !dbg !3104
  %conv35 = zext i16 %26 to i32, !dbg !3104
  %xor36 = xor i32 %conv30, %conv35, !dbg !3104
  %conv37 = trunc i32 %xor36 to i16, !dbg !3104
  store i16 %conv37, i16* %crc.addr, align 2, !dbg !3104
  br label %do.end, !dbg !3104

do.end:                                           ; preds = %if.end25
  br label %do.body38, !dbg !3106

do.body38:                                        ; preds = %do.end
  %27 = load i8, i8* getelementptr inbounds ([4 x i8], [4 x i8]* bitcast (%union.anon* @lha_crc16.u to [4 x i8]*), i64 0, i64 0), align 4, !dbg !3107
  %conv39 = sext i8 %27 to i32, !dbg !3107
  %cmp40 = icmp eq i32 %conv39, 1, !dbg !3107
  br i1 %cmp40, label %if.then42, label %if.else48, !dbg !3107

if.then42:                                        ; preds = %do.body38
  %28 = load i16*, i16** %buff, align 8, !dbg !3111
  %29 = load i16, i16* %28, align 2, !dbg !3111
  %30 = call i16 @llvm.bswap.i16(i16 %29), !dbg !3111
  %conv43 = zext i16 %30 to i32, !dbg !3111
  %31 = load i16, i16* %crc.addr, align 2, !dbg !3111
  %conv44 = zext i16 %31 to i32, !dbg !3111
  %xor45 = xor i32 %conv44, %conv43, !dbg !3111
  %conv46 = trunc i32 %xor45 to i16, !dbg !3111
  store i16 %conv46, i16* %crc.addr, align 2, !dbg !3111
  %32 = load i16*, i16** %buff, align 8, !dbg !3111
  %incdec.ptr47 = getelementptr inbounds i16, i16* %32, i32 1, !dbg !3111
  store i16* %incdec.ptr47, i16** %buff, align 8, !dbg !3111
  br label %if.end54, !dbg !3111

if.else48:                                        ; preds = %do.body38
  %33 = load i16*, i16** %buff, align 8, !dbg !3114
  %incdec.ptr49 = getelementptr inbounds i16, i16* %33, i32 1, !dbg !3114
  store i16* %incdec.ptr49, i16** %buff, align 8, !dbg !3114
  %34 = load i16, i16* %33, align 2, !dbg !3114
  %conv50 = zext i16 %34 to i32, !dbg !3114
  %35 = load i16, i16* %crc.addr, align 2, !dbg !3114
  %conv51 = zext i16 %35 to i32, !dbg !3114
  %xor52 = xor i32 %conv51, %conv50, !dbg !3114
  %conv53 = trunc i32 %xor52 to i16, !dbg !3114
  store i16 %conv53, i16* %crc.addr, align 2, !dbg !3114
  br label %if.end54

if.end54:                                         ; preds = %if.else48, %if.then42
  %36 = load i16, i16* %crc.addr, align 2, !dbg !3116
  %conv55 = zext i16 %36 to i32, !dbg !3116
  %and56 = and i32 %conv55, 255, !dbg !3116
  %idxprom57 = sext i32 %and56 to i64, !dbg !3116
  %arrayidx58 = getelementptr inbounds [256 x i16], [256 x i16]* getelementptr inbounds ([2 x [256 x i16]], [2 x [256 x i16]]* @crc16tbl, i64 0, i64 1), i64 0, i64 %idxprom57, !dbg !3116
  %37 = load i16, i16* %arrayidx58, align 2, !dbg !3116
  %conv59 = zext i16 %37 to i32, !dbg !3116
  %38 = load i16, i16* %crc.addr, align 2, !dbg !3116
  %conv60 = zext i16 %38 to i32, !dbg !3116
  %shr61 = ashr i32 %conv60, 8, !dbg !3116
  %idxprom62 = sext i32 %shr61 to i64, !dbg !3116
  %arrayidx63 = getelementptr inbounds [256 x i16], [256 x i16]* getelementptr inbounds ([2 x [256 x i16]], [2 x [256 x i16]]* @crc16tbl, i64 0, i64 0), i64 0, i64 %idxprom62, !dbg !3116
  %39 = load i16, i16* %arrayidx63, align 2, !dbg !3116
  %conv64 = zext i16 %39 to i32, !dbg !3116
  %xor65 = xor i32 %conv59, %conv64, !dbg !3116
  %conv66 = trunc i32 %xor65 to i16, !dbg !3116
  store i16 %conv66, i16* %crc.addr, align 2, !dbg !3116
  br label %do.end67, !dbg !3116

do.end67:                                         ; preds = %if.end54
  br label %do.body68, !dbg !3118

do.body68:                                        ; preds = %do.end67
  %40 = load i8, i8* getelementptr inbounds ([4 x i8], [4 x i8]* bitcast (%union.anon* @lha_crc16.u to [4 x i8]*), i64 0, i64 0), align 4, !dbg !3119
  %conv69 = sext i8 %40 to i32, !dbg !3119
  %cmp70 = icmp eq i32 %conv69, 1, !dbg !3119
  br i1 %cmp70, label %if.then72, label %if.else78, !dbg !3119

if.then72:                                        ; preds = %do.body68
  %41 = load i16*, i16** %buff, align 8, !dbg !3123
  %42 = load i16, i16* %41, align 2, !dbg !3123
  %43 = call i16 @llvm.bswap.i16(i16 %42), !dbg !3123
  %conv73 = zext i16 %43 to i32, !dbg !3123
  %44 = load i16, i16* %crc.addr, align 2, !dbg !3123
  %conv74 = zext i16 %44 to i32, !dbg !3123
  %xor75 = xor i32 %conv74, %conv73, !dbg !3123
  %conv76 = trunc i32 %xor75 to i16, !dbg !3123
  store i16 %conv76, i16* %crc.addr, align 2, !dbg !3123
  %45 = load i16*, i16** %buff, align 8, !dbg !3123
  %incdec.ptr77 = getelementptr inbounds i16, i16* %45, i32 1, !dbg !3123
  store i16* %incdec.ptr77, i16** %buff, align 8, !dbg !3123
  br label %if.end84, !dbg !3123

if.else78:                                        ; preds = %do.body68
  %46 = load i16*, i16** %buff, align 8, !dbg !3126
  %incdec.ptr79 = getelementptr inbounds i16, i16* %46, i32 1, !dbg !3126
  store i16* %incdec.ptr79, i16** %buff, align 8, !dbg !3126
  %47 = load i16, i16* %46, align 2, !dbg !3126
  %conv80 = zext i16 %47 to i32, !dbg !3126
  %48 = load i16, i16* %crc.addr, align 2, !dbg !3126
  %conv81 = zext i16 %48 to i32, !dbg !3126
  %xor82 = xor i32 %conv81, %conv80, !dbg !3126
  %conv83 = trunc i32 %xor82 to i16, !dbg !3126
  store i16 %conv83, i16* %crc.addr, align 2, !dbg !3126
  br label %if.end84

if.end84:                                         ; preds = %if.else78, %if.then72
  %49 = load i16, i16* %crc.addr, align 2, !dbg !3128
  %conv85 = zext i16 %49 to i32, !dbg !3128
  %and86 = and i32 %conv85, 255, !dbg !3128
  %idxprom87 = sext i32 %and86 to i64, !dbg !3128
  %arrayidx88 = getelementptr inbounds [256 x i16], [256 x i16]* getelementptr inbounds ([2 x [256 x i16]], [2 x [256 x i16]]* @crc16tbl, i64 0, i64 1), i64 0, i64 %idxprom87, !dbg !3128
  %50 = load i16, i16* %arrayidx88, align 2, !dbg !3128
  %conv89 = zext i16 %50 to i32, !dbg !3128
  %51 = load i16, i16* %crc.addr, align 2, !dbg !3128
  %conv90 = zext i16 %51 to i32, !dbg !3128
  %shr91 = ashr i32 %conv90, 8, !dbg !3128
  %idxprom92 = sext i32 %shr91 to i64, !dbg !3128
  %arrayidx93 = getelementptr inbounds [256 x i16], [256 x i16]* getelementptr inbounds ([2 x [256 x i16]], [2 x [256 x i16]]* @crc16tbl, i64 0, i64 0), i64 0, i64 %idxprom92, !dbg !3128
  %52 = load i16, i16* %arrayidx93, align 2, !dbg !3128
  %conv94 = zext i16 %52 to i32, !dbg !3128
  %xor95 = xor i32 %conv89, %conv94, !dbg !3128
  %conv96 = trunc i32 %xor95 to i16, !dbg !3128
  store i16 %conv96, i16* %crc.addr, align 2, !dbg !3128
  br label %do.end97, !dbg !3128

do.end97:                                         ; preds = %if.end84
  br label %do.body98, !dbg !3130

do.body98:                                        ; preds = %do.end97
  %53 = load i8, i8* getelementptr inbounds ([4 x i8], [4 x i8]* bitcast (%union.anon* @lha_crc16.u to [4 x i8]*), i64 0, i64 0), align 4, !dbg !3131
  %conv99 = sext i8 %53 to i32, !dbg !3131
  %cmp100 = icmp eq i32 %conv99, 1, !dbg !3131
  br i1 %cmp100, label %if.then102, label %if.else108, !dbg !3131

if.then102:                                       ; preds = %do.body98
  %54 = load i16*, i16** %buff, align 8, !dbg !3135
  %55 = load i16, i16* %54, align 2, !dbg !3135
  %56 = call i16 @llvm.bswap.i16(i16 %55), !dbg !3135
  %conv103 = zext i16 %56 to i32, !dbg !3135
  %57 = load i16, i16* %crc.addr, align 2, !dbg !3135
  %conv104 = zext i16 %57 to i32, !dbg !3135
  %xor105 = xor i32 %conv104, %conv103, !dbg !3135
  %conv106 = trunc i32 %xor105 to i16, !dbg !3135
  store i16 %conv106, i16* %crc.addr, align 2, !dbg !3135
  %58 = load i16*, i16** %buff, align 8, !dbg !3135
  %incdec.ptr107 = getelementptr inbounds i16, i16* %58, i32 1, !dbg !3135
  store i16* %incdec.ptr107, i16** %buff, align 8, !dbg !3135
  br label %if.end114, !dbg !3135

if.else108:                                       ; preds = %do.body98
  %59 = load i16*, i16** %buff, align 8, !dbg !3138
  %incdec.ptr109 = getelementptr inbounds i16, i16* %59, i32 1, !dbg !3138
  store i16* %incdec.ptr109, i16** %buff, align 8, !dbg !3138
  %60 = load i16, i16* %59, align 2, !dbg !3138
  %conv110 = zext i16 %60 to i32, !dbg !3138
  %61 = load i16, i16* %crc.addr, align 2, !dbg !3138
  %conv111 = zext i16 %61 to i32, !dbg !3138
  %xor112 = xor i32 %conv111, %conv110, !dbg !3138
  %conv113 = trunc i32 %xor112 to i16, !dbg !3138
  store i16 %conv113, i16* %crc.addr, align 2, !dbg !3138
  br label %if.end114

if.end114:                                        ; preds = %if.else108, %if.then102
  %62 = load i16, i16* %crc.addr, align 2, !dbg !3140
  %conv115 = zext i16 %62 to i32, !dbg !3140
  %and116 = and i32 %conv115, 255, !dbg !3140
  %idxprom117 = sext i32 %and116 to i64, !dbg !3140
  %arrayidx118 = getelementptr inbounds [256 x i16], [256 x i16]* getelementptr inbounds ([2 x [256 x i16]], [2 x [256 x i16]]* @crc16tbl, i64 0, i64 1), i64 0, i64 %idxprom117, !dbg !3140
  %63 = load i16, i16* %arrayidx118, align 2, !dbg !3140
  %conv119 = zext i16 %63 to i32, !dbg !3140
  %64 = load i16, i16* %crc.addr, align 2, !dbg !3140
  %conv120 = zext i16 %64 to i32, !dbg !3140
  %shr121 = ashr i32 %conv120, 8, !dbg !3140
  %idxprom122 = sext i32 %shr121 to i64, !dbg !3140
  %arrayidx123 = getelementptr inbounds [256 x i16], [256 x i16]* getelementptr inbounds ([2 x [256 x i16]], [2 x [256 x i16]]* @crc16tbl, i64 0, i64 0), i64 0, i64 %idxprom122, !dbg !3140
  %65 = load i16, i16* %arrayidx123, align 2, !dbg !3140
  %conv124 = zext i16 %65 to i32, !dbg !3140
  %xor125 = xor i32 %conv119, %conv124, !dbg !3140
  %conv126 = trunc i32 %xor125 to i16, !dbg !3140
  store i16 %conv126, i16* %crc.addr, align 2, !dbg !3140
  br label %do.end127, !dbg !3140

do.end127:                                        ; preds = %if.end114
  br label %for.inc, !dbg !3142

for.inc:                                          ; preds = %do.end127
  %66 = load i64, i64* %len.addr, align 8, !dbg !3143
  %sub = sub i64 %66, 8, !dbg !3143
  store i64 %sub, i64* %len.addr, align 8, !dbg !3143
  br label %for.cond, !dbg !3145

for.end:                                          ; preds = %for.cond
  %67 = load i16*, i16** %buff, align 8, !dbg !3146
  %68 = bitcast i16* %67 to i8*, !dbg !3147
  store i8* %68, i8** %p, align 8, !dbg !3148
  br label %for.cond128, !dbg !3149

for.cond128:                                      ; preds = %for.inc143, %for.end
  %69 = load i64, i64* %len.addr, align 8, !dbg !3150
  %tobool129 = icmp ne i64 %69, 0, !dbg !3154
  br i1 %tobool129, label %for.body130, label %for.end145, !dbg !3154

for.body130:                                      ; preds = %for.cond128
  %70 = load i16, i16* %crc.addr, align 2, !dbg !3155
  %conv131 = zext i16 %70 to i32, !dbg !3155
  %shr132 = ashr i32 %conv131, 8, !dbg !3157
  %71 = load i16, i16* %crc.addr, align 2, !dbg !3158
  %conv133 = zext i16 %71 to i32, !dbg !3158
  %72 = load i8*, i8** %p, align 8, !dbg !3159
  %incdec.ptr134 = getelementptr inbounds i8, i8* %72, i32 1, !dbg !3159
  store i8* %incdec.ptr134, i8** %p, align 8, !dbg !3159
  %73 = load i8, i8* %72, align 1, !dbg !3160
  %conv135 = zext i8 %73 to i32, !dbg !3160
  %xor136 = xor i32 %conv133, %conv135, !dbg !3161
  %and137 = and i32 %xor136, 255, !dbg !3162
  %idxprom138 = sext i32 %and137 to i64, !dbg !3163
  %arrayidx139 = getelementptr inbounds [256 x i16], [256 x i16]* getelementptr inbounds ([2 x [256 x i16]], [2 x [256 x i16]]* @crc16tbl, i64 0, i64 0), i64 0, i64 %idxprom138, !dbg !3163
  %74 = load i16, i16* %arrayidx139, align 2, !dbg !3163
  %conv140 = zext i16 %74 to i32, !dbg !3163
  %xor141 = xor i32 %shr132, %conv140, !dbg !3164
  %conv142 = trunc i32 %xor141 to i16, !dbg !3165
  store i16 %conv142, i16* %crc.addr, align 2, !dbg !3166
  br label %for.inc143, !dbg !3167

for.inc143:                                       ; preds = %for.body130
  %75 = load i64, i64* %len.addr, align 8, !dbg !3168
  %dec144 = add i64 %75, -1, !dbg !3168
  store i64 %dec144, i64* %len.addr, align 8, !dbg !3168
  br label %for.cond128, !dbg !3170

for.end145:                                       ; preds = %for.cond128
  %76 = load i16, i16* %crc.addr, align 2, !dbg !3171
  store i16 %76, i16* %retval, align 2, !dbg !3172
  br label %return, !dbg !3172

return:                                           ; preds = %for.end145, %if.then
  %77 = load i16, i16* %retval, align 2, !dbg !3173
  ret i16 %77, !dbg !3173
}

; Function Attrs: nounwind uwtable
define internal i64 @lha_win_time(i64 %wintime, i64* %ns) #0 !dbg !454 {
entry:
  %retval = alloca i64, align 8
  %wintime.addr = alloca i64, align 8
  %ns.addr = alloca i64*, align 8
  store i64 %wintime, i64* %wintime.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %wintime.addr, metadata !3174, metadata !548), !dbg !3175
  store i64* %ns, i64** %ns.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %ns.addr, metadata !3176, metadata !548), !dbg !3177
  %0 = load i64, i64* %wintime.addr, align 8, !dbg !3178
  %cmp = icmp uge i64 %0, 116444736000000000, !dbg !3180
  br i1 %cmp, label %if.then, label %if.else, !dbg !3181

if.then:                                          ; preds = %entry
  %1 = load i64, i64* %wintime.addr, align 8, !dbg !3182
  %sub = sub i64 %1, 116444736000000000, !dbg !3182
  store i64 %sub, i64* %wintime.addr, align 8, !dbg !3182
  %2 = load i64*, i64** %ns.addr, align 8, !dbg !3184
  %cmp1 = icmp ne i64* %2, null, !dbg !3186
  br i1 %cmp1, label %if.then2, label %if.end, !dbg !3187

if.then2:                                         ; preds = %if.then
  %3 = load i64, i64* %wintime.addr, align 8, !dbg !3188
  %rem = urem i64 %3, 10000000, !dbg !3189
  %mul = mul nsw i64 %rem, 100, !dbg !3190
  %4 = load i64*, i64** %ns.addr, align 8, !dbg !3191
  store i64 %mul, i64* %4, align 8, !dbg !3192
  br label %if.end, !dbg !3193

if.end:                                           ; preds = %if.then2, %if.then
  %5 = load i64, i64* %wintime.addr, align 8, !dbg !3194
  %div = udiv i64 %5, 10000000, !dbg !3195
  store i64 %div, i64* %retval, align 8, !dbg !3196
  br label %return, !dbg !3196

if.else:                                          ; preds = %entry
  %6 = load i64*, i64** %ns.addr, align 8, !dbg !3197
  %cmp3 = icmp ne i64* %6, null, !dbg !3200
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !3201

if.then4:                                         ; preds = %if.else
  %7 = load i64*, i64** %ns.addr, align 8, !dbg !3202
  store i64 0, i64* %7, align 8, !dbg !3203
  br label %if.end5, !dbg !3204

if.end5:                                          ; preds = %if.then4, %if.else
  store i64 0, i64* %retval, align 8, !dbg !3205
  br label %return, !dbg !3205

return:                                           ; preds = %if.end5, %if.end
  %8 = load i64, i64* %retval, align 8, !dbg !3206
  ret i64 %8, !dbg !3206
}

; Function Attrs: inlinehint nounwind uwtable
define internal i64 @archive_le64dec(i8* %pp) #6 !dbg !458 {
entry:
  %pp.addr = alloca i8*, align 8
  %p = alloca i8*, align 8
  store i8* %pp, i8** %pp.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %pp.addr, metadata !3207, metadata !548), !dbg !3208
  call void @llvm.dbg.declare(metadata i8** %p, metadata !3209, metadata !548), !dbg !3210
  %0 = load i8*, i8** %pp.addr, align 8, !dbg !3211
  store i8* %0, i8** %p, align 8, !dbg !3210
  %1 = load i8*, i8** %p, align 8, !dbg !3212
  %add.ptr = getelementptr inbounds i8, i8* %1, i64 4, !dbg !3213
  %call = call i32 @archive_le32dec(i8* %add.ptr), !dbg !3214
  %conv = zext i32 %call to i64, !dbg !3215
  %shl = shl i64 %conv, 32, !dbg !3216
  %2 = load i8*, i8** %p, align 8, !dbg !3217
  %call1 = call i32 @archive_le32dec(i8* %2), !dbg !3218
  %conv2 = zext i32 %call1 to i64, !dbg !3220
  %or = or i64 %shl, %conv2, !dbg !3221
  ret i64 %or, !dbg !3222
}

declare void @archive_string_sprintf(%struct.archive_string*, i8*, ...) #2

; Function Attrs: nounwind readnone
declare i16 @llvm.bswap.i16(i16) #1

; Function Attrs: nounwind readonly
declare i8* @strchr(i8*, i32) #4

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #4

declare i32* @archive_entry_pathname_w(%struct.archive_entry*) #2

declare %struct.archive_wstring* @archive_wstrncat(%struct.archive_wstring*, i32*, i64) #2

; Function Attrs: nounwind readonly
declare i64 @wcslen(i32*) #4

declare void @archive_entry_copy_pathname_w(%struct.archive_entry*, i32*) #2

declare i32* @archive_entry_symlink_w(%struct.archive_entry*) #2

declare void @archive_entry_copy_symlink_w(%struct.archive_entry*, i32*) #2

; Function Attrs: nounwind uwtable
define internal i32 @lha_end_of_entry(%struct.archive_read* %a) #0 !dbg !471 {
entry:
  %a.addr = alloca %struct.archive_read*, align 8
  %lha = alloca %struct.lha*, align 8
  %r = alloca i32, align 4
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !3223, metadata !548), !dbg !3224
  call void @llvm.dbg.declare(metadata %struct.lha** %lha, metadata !3225, metadata !548), !dbg !3226
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3227
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 13, !dbg !3228
  %1 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !3228
  %data = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %1, i32 0, i32 0, !dbg !3229
  %2 = load i8*, i8** %data, align 8, !dbg !3229
  %3 = bitcast i8* %2 to %struct.lha*, !dbg !3230
  store %struct.lha* %3, %struct.lha** %lha, align 8, !dbg !3226
  call void @llvm.dbg.declare(metadata i32* %r, metadata !3231, metadata !548), !dbg !3232
  store i32 1, i32* %r, align 4, !dbg !3232
  %4 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3233
  %end_of_entry_cleanup = getelementptr inbounds %struct.lha, %struct.lha* %4, i32 0, i32 33, !dbg !3235
  %5 = load i8, i8* %end_of_entry_cleanup, align 1, !dbg !3235
  %tobool = icmp ne i8 %5, 0, !dbg !3233
  br i1 %tobool, label %if.end6, label %if.then, !dbg !3236

if.then:                                          ; preds = %entry
  %6 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3237
  %setflag = getelementptr inbounds %struct.lha, %struct.lha* %6, i32 0, i32 9, !dbg !3240
  %7 = load i32, i32* %setflag, align 8, !dbg !3240
  %and = and i32 %7, 8, !dbg !3241
  %tobool1 = icmp ne i32 %and, 0, !dbg !3241
  br i1 %tobool1, label %land.lhs.true, label %if.end, !dbg !3242

land.lhs.true:                                    ; preds = %if.then
  %8 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3243
  %crc = getelementptr inbounds %struct.lha, %struct.lha* %8, i32 0, i32 22, !dbg !3244
  %9 = load i16, i16* %crc, align 2, !dbg !3244
  %conv = zext i16 %9 to i32, !dbg !3243
  %10 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3245
  %entry_crc_calculated = getelementptr inbounds %struct.lha, %struct.lha* %10, i32 0, i32 3, !dbg !3246
  %11 = load i16, i16* %entry_crc_calculated, align 8, !dbg !3246
  %conv2 = zext i16 %11 to i32, !dbg !3245
  %cmp = icmp ne i32 %conv, %conv2, !dbg !3247
  br i1 %cmp, label %if.then4, label %if.end, !dbg !3248

if.then4:                                         ; preds = %land.lhs.true
  %12 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3250
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %12, i32 0, i32 0, !dbg !3252
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 -1, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.25, i32 0, i32 0)), !dbg !3253
  store i32 -20, i32* %r, align 4, !dbg !3254
  br label %if.end, !dbg !3255

if.end:                                           ; preds = %if.then4, %land.lhs.true, %if.then
  %13 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3256
  %end_of_entry_cleanup5 = getelementptr inbounds %struct.lha, %struct.lha* %13, i32 0, i32 33, !dbg !3257
  store i8 1, i8* %end_of_entry_cleanup5, align 1, !dbg !3258
  br label %if.end6, !dbg !3259

if.end6:                                          ; preds = %if.end, %entry
  %14 = load i32, i32* %r, align 4, !dbg !3260
  ret i32 %14, !dbg !3261
}

; Function Attrs: nounwind uwtable
define internal i32 @lha_read_data_lzh(%struct.archive_read* %a, i8** %buff, i64* %size, i64* %offset) #0 !dbg !472 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %buff.addr = alloca i8**, align 8
  %size.addr = alloca i64*, align 8
  %offset.addr = alloca i64*, align 8
  %lha = alloca %struct.lha*, align 8
  %bytes_avail = alloca i64, align 8
  %r = alloca i32, align 4
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !3262, metadata !548), !dbg !3263
  store i8** %buff, i8*** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %buff.addr, metadata !3264, metadata !548), !dbg !3265
  store i64* %size, i64** %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %size.addr, metadata !3266, metadata !548), !dbg !3267
  store i64* %offset, i64** %offset.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %offset.addr, metadata !3268, metadata !548), !dbg !3269
  call void @llvm.dbg.declare(metadata %struct.lha** %lha, metadata !3270, metadata !548), !dbg !3271
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3272
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 13, !dbg !3273
  %1 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !3273
  %data = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %1, i32 0, i32 0, !dbg !3274
  %2 = load i8*, i8** %data, align 8, !dbg !3274
  %3 = bitcast i8* %2 to %struct.lha*, !dbg !3275
  store %struct.lha* %3, %struct.lha** %lha, align 8, !dbg !3271
  call void @llvm.dbg.declare(metadata i64* %bytes_avail, metadata !3276, metadata !548), !dbg !3277
  call void @llvm.dbg.declare(metadata i32* %r, metadata !3278, metadata !548), !dbg !3279
  %4 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3280
  %decompress_init = getelementptr inbounds %struct.lha, %struct.lha* %4, i32 0, i32 31, !dbg !3282
  %5 = load i8, i8* %decompress_init, align 1, !dbg !3282
  %tobool = icmp ne i8 %5, 0, !dbg !3280
  br i1 %tobool, label %if.end, label %if.then, !dbg !3283

if.then:                                          ; preds = %entry
  %6 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3284
  %strm = getelementptr inbounds %struct.lha, %struct.lha* %6, i32 0, i32 36, !dbg !3286
  %7 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3287
  %method = getelementptr inbounds %struct.lha, %struct.lha* %7, i32 0, i32 6, !dbg !3288
  %arraydecay = getelementptr inbounds [3 x i8], [3 x i8]* %method, i32 0, i32 0, !dbg !3287
  %call = call i32 @lzh_decode_init(%struct.lzh_stream* %strm, i8* %arraydecay), !dbg !3289
  store i32 %call, i32* %r, align 4, !dbg !3290
  %8 = load i32, i32* %r, align 4, !dbg !3291
  switch i32 %8, label %sw.default [
    i32 0, label %sw.bb
    i32 -25, label %sw.bb1
  ], !dbg !3292

sw.bb:                                            ; preds = %if.then
  br label %sw.epilog, !dbg !3293

sw.bb1:                                           ; preds = %if.then
  %9 = load i8**, i8*** %buff.addr, align 8, !dbg !3295
  store i8* null, i8** %9, align 8, !dbg !3296
  %10 = load i64*, i64** %size.addr, align 8, !dbg !3297
  store i64 0, i64* %10, align 8, !dbg !3298
  %11 = load i64*, i64** %offset.addr, align 8, !dbg !3299
  store i64 0, i64* %11, align 8, !dbg !3300
  %12 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3301
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %12, i32 0, i32 0, !dbg !3302
  %13 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3303
  %method2 = getelementptr inbounds %struct.lha, %struct.lha* %13, i32 0, i32 6, !dbg !3304
  %arrayidx = getelementptr inbounds [3 x i8], [3 x i8]* %method2, i64 0, i64 0, !dbg !3303
  %14 = load i8, i8* %arrayidx, align 1, !dbg !3303
  %conv = sext i8 %14 to i32, !dbg !3303
  %15 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3305
  %method3 = getelementptr inbounds %struct.lha, %struct.lha* %15, i32 0, i32 6, !dbg !3306
  %arrayidx4 = getelementptr inbounds [3 x i8], [3 x i8]* %method3, i64 0, i64 1, !dbg !3305
  %16 = load i8, i8* %arrayidx4, align 1, !dbg !3305
  %conv5 = sext i8 %16 to i32, !dbg !3305
  %17 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3307
  %method6 = getelementptr inbounds %struct.lha, %struct.lha* %17, i32 0, i32 6, !dbg !3308
  %arrayidx7 = getelementptr inbounds [3 x i8], [3 x i8]* %method6, i64 0, i64 2, !dbg !3307
  %18 = load i8, i8* %arrayidx7, align 1, !dbg !3307
  %conv8 = sext i8 %18 to i32, !dbg !3307
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 84, i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.26, i32 0, i32 0), i32 %conv, i32 %conv5, i32 %conv8), !dbg !3309
  %19 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3310
  %call9 = call i32 @archive_read_format_lha_read_data_skip(%struct.archive_read* %19), !dbg !3311
  store i32 -20, i32* %retval, align 4, !dbg !3312
  br label %return, !dbg !3312

sw.default:                                       ; preds = %if.then
  %20 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3313
  %archive10 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %20, i32 0, i32 0, !dbg !3314
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive10, i32 12, i8* getelementptr inbounds ([47 x i8], [47 x i8]* @.str.27, i32 0, i32 0)), !dbg !3315
  store i32 -30, i32* %retval, align 4, !dbg !3316
  br label %return, !dbg !3316

sw.epilog:                                        ; preds = %sw.bb
  %21 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3317
  %decompress_init11 = getelementptr inbounds %struct.lha, %struct.lha* %21, i32 0, i32 31, !dbg !3318
  store i8 1, i8* %decompress_init11, align 1, !dbg !3319
  %22 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3320
  %strm12 = getelementptr inbounds %struct.lha, %struct.lha* %22, i32 0, i32 36, !dbg !3321
  %avail_out = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %strm12, i32 0, i32 4, !dbg !3322
  store i32 0, i32* %avail_out, align 8, !dbg !3323
  %23 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3324
  %strm13 = getelementptr inbounds %struct.lha, %struct.lha* %23, i32 0, i32 36, !dbg !3325
  %total_out = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %strm13, i32 0, i32 5, !dbg !3326
  store i64 0, i64* %total_out, align 8, !dbg !3327
  br label %if.end, !dbg !3328

if.end:                                           ; preds = %sw.epilog, %entry
  %24 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3329
  %call14 = call i8* @__archive_read_ahead(%struct.archive_read* %24, i64 1, i64* %bytes_avail), !dbg !3330
  %25 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3331
  %strm15 = getelementptr inbounds %struct.lha, %struct.lha* %25, i32 0, i32 36, !dbg !3332
  %next_in = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %strm15, i32 0, i32 0, !dbg !3333
  store i8* %call14, i8** %next_in, align 8, !dbg !3334
  %26 = load i64, i64* %bytes_avail, align 8, !dbg !3335
  %cmp = icmp sle i64 %26, 0, !dbg !3337
  br i1 %cmp, label %if.then17, label %if.end19, !dbg !3338

if.then17:                                        ; preds = %if.end
  %27 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3339
  %archive18 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %27, i32 0, i32 0, !dbg !3341
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive18, i32 84, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.28, i32 0, i32 0)), !dbg !3342
  store i32 -30, i32* %retval, align 4, !dbg !3343
  br label %return, !dbg !3343

if.end19:                                         ; preds = %if.end
  %28 = load i64, i64* %bytes_avail, align 8, !dbg !3344
  %29 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3346
  %entry_bytes_remaining = getelementptr inbounds %struct.lha, %struct.lha* %29, i32 0, i32 1, !dbg !3347
  %30 = load i64, i64* %entry_bytes_remaining, align 8, !dbg !3347
  %cmp20 = icmp sgt i64 %28, %30, !dbg !3348
  br i1 %cmp20, label %if.then22, label %if.end24, !dbg !3349

if.then22:                                        ; preds = %if.end19
  %31 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3350
  %entry_bytes_remaining23 = getelementptr inbounds %struct.lha, %struct.lha* %31, i32 0, i32 1, !dbg !3351
  %32 = load i64, i64* %entry_bytes_remaining23, align 8, !dbg !3351
  store i64 %32, i64* %bytes_avail, align 8, !dbg !3352
  br label %if.end24, !dbg !3353

if.end24:                                         ; preds = %if.then22, %if.end19
  %33 = load i64, i64* %bytes_avail, align 8, !dbg !3354
  %conv25 = trunc i64 %33 to i32, !dbg !3355
  %34 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3356
  %strm26 = getelementptr inbounds %struct.lha, %struct.lha* %34, i32 0, i32 36, !dbg !3357
  %avail_in = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %strm26, i32 0, i32 1, !dbg !3358
  store i32 %conv25, i32* %avail_in, align 8, !dbg !3359
  %35 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3360
  %strm27 = getelementptr inbounds %struct.lha, %struct.lha* %35, i32 0, i32 36, !dbg !3361
  %total_in = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %strm27, i32 0, i32 2, !dbg !3362
  store i64 0, i64* %total_in, align 8, !dbg !3363
  %36 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3364
  %strm28 = getelementptr inbounds %struct.lha, %struct.lha* %36, i32 0, i32 36, !dbg !3365
  %avail_out29 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %strm28, i32 0, i32 4, !dbg !3366
  store i32 0, i32* %avail_out29, align 8, !dbg !3367
  %37 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3368
  %strm30 = getelementptr inbounds %struct.lha, %struct.lha* %37, i32 0, i32 36, !dbg !3369
  %38 = load i64, i64* %bytes_avail, align 8, !dbg !3370
  %39 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3371
  %entry_bytes_remaining31 = getelementptr inbounds %struct.lha, %struct.lha* %39, i32 0, i32 1, !dbg !3372
  %40 = load i64, i64* %entry_bytes_remaining31, align 8, !dbg !3372
  %cmp32 = icmp eq i64 %38, %40, !dbg !3373
  %conv33 = zext i1 %cmp32 to i32, !dbg !3373
  %call34 = call i32 @lzh_decode(%struct.lzh_stream* %strm30, i32 %conv33), !dbg !3374
  store i32 %call34, i32* %r, align 4, !dbg !3375
  %41 = load i32, i32* %r, align 4, !dbg !3376
  switch i32 %41, label %sw.default37 [
    i32 0, label %sw.bb35
    i32 1, label %sw.bb36
  ], !dbg !3377

sw.bb35:                                          ; preds = %if.end24
  br label %sw.epilog39, !dbg !3378

sw.bb36:                                          ; preds = %if.end24
  %42 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3380
  %end_of_entry = getelementptr inbounds %struct.lha, %struct.lha* %42, i32 0, i32 32, !dbg !3381
  store i8 1, i8* %end_of_entry, align 4, !dbg !3382
  br label %sw.epilog39, !dbg !3383

sw.default37:                                     ; preds = %if.end24
  %43 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3384
  %archive38 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %43, i32 0, i32 0, !dbg !3385
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive38, i32 -1, i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.29, i32 0, i32 0)), !dbg !3386
  store i32 -25, i32* %retval, align 4, !dbg !3387
  br label %return, !dbg !3387

sw.epilog39:                                      ; preds = %sw.bb36, %sw.bb35
  %44 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3388
  %strm40 = getelementptr inbounds %struct.lha, %struct.lha* %44, i32 0, i32 36, !dbg !3389
  %total_in41 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %strm40, i32 0, i32 2, !dbg !3390
  %45 = load i64, i64* %total_in41, align 8, !dbg !3390
  %46 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3391
  %entry_unconsumed = getelementptr inbounds %struct.lha, %struct.lha* %46, i32 0, i32 2, !dbg !3392
  store i64 %45, i64* %entry_unconsumed, align 8, !dbg !3393
  %47 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3394
  %strm42 = getelementptr inbounds %struct.lha, %struct.lha* %47, i32 0, i32 36, !dbg !3395
  %total_in43 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %strm42, i32 0, i32 2, !dbg !3396
  %48 = load i64, i64* %total_in43, align 8, !dbg !3396
  %49 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3397
  %entry_bytes_remaining44 = getelementptr inbounds %struct.lha, %struct.lha* %49, i32 0, i32 1, !dbg !3398
  %50 = load i64, i64* %entry_bytes_remaining44, align 8, !dbg !3399
  %sub = sub nsw i64 %50, %48, !dbg !3399
  store i64 %sub, i64* %entry_bytes_remaining44, align 8, !dbg !3399
  %51 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3400
  %strm45 = getelementptr inbounds %struct.lha, %struct.lha* %51, i32 0, i32 36, !dbg !3402
  %avail_out46 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %strm45, i32 0, i32 4, !dbg !3403
  %52 = load i32, i32* %avail_out46, align 8, !dbg !3403
  %tobool47 = icmp ne i32 %52, 0, !dbg !3400
  br i1 %tobool47, label %if.then48, label %if.else, !dbg !3404

if.then48:                                        ; preds = %sw.epilog39
  %53 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3405
  %entry_offset = getelementptr inbounds %struct.lha, %struct.lha* %53, i32 0, i32 0, !dbg !3407
  %54 = load i64, i64* %entry_offset, align 8, !dbg !3407
  %55 = load i64*, i64** %offset.addr, align 8, !dbg !3408
  store i64 %54, i64* %55, align 8, !dbg !3409
  %56 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3410
  %strm49 = getelementptr inbounds %struct.lha, %struct.lha* %56, i32 0, i32 36, !dbg !3411
  %avail_out50 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %strm49, i32 0, i32 4, !dbg !3412
  %57 = load i32, i32* %avail_out50, align 8, !dbg !3412
  %conv51 = sext i32 %57 to i64, !dbg !3410
  %58 = load i64*, i64** %size.addr, align 8, !dbg !3413
  store i64 %conv51, i64* %58, align 8, !dbg !3414
  %59 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3415
  %strm52 = getelementptr inbounds %struct.lha, %struct.lha* %59, i32 0, i32 36, !dbg !3416
  %ref_ptr = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %strm52, i32 0, i32 3, !dbg !3417
  %60 = load i8*, i8** %ref_ptr, align 8, !dbg !3417
  %61 = load i8**, i8*** %buff.addr, align 8, !dbg !3418
  store i8* %60, i8** %61, align 8, !dbg !3419
  %62 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3420
  %entry_crc_calculated = getelementptr inbounds %struct.lha, %struct.lha* %62, i32 0, i32 3, !dbg !3421
  %63 = load i16, i16* %entry_crc_calculated, align 8, !dbg !3421
  %64 = load i8**, i8*** %buff.addr, align 8, !dbg !3422
  %65 = load i8*, i8** %64, align 8, !dbg !3423
  %66 = load i64*, i64** %size.addr, align 8, !dbg !3424
  %67 = load i64, i64* %66, align 8, !dbg !3425
  %call53 = call zeroext i16 @lha_crc16(i16 zeroext %63, i8* %65, i64 %67), !dbg !3426
  %68 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3427
  %entry_crc_calculated54 = getelementptr inbounds %struct.lha, %struct.lha* %68, i32 0, i32 3, !dbg !3428
  store i16 %call53, i16* %entry_crc_calculated54, align 8, !dbg !3429
  %69 = load i64*, i64** %size.addr, align 8, !dbg !3430
  %70 = load i64, i64* %69, align 8, !dbg !3431
  %71 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3432
  %entry_offset55 = getelementptr inbounds %struct.lha, %struct.lha* %71, i32 0, i32 0, !dbg !3433
  %72 = load i64, i64* %entry_offset55, align 8, !dbg !3434
  %add = add i64 %72, %70, !dbg !3434
  store i64 %add, i64* %entry_offset55, align 8, !dbg !3434
  br label %if.end62, !dbg !3435

if.else:                                          ; preds = %sw.epilog39
  %73 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3436
  %entry_offset56 = getelementptr inbounds %struct.lha, %struct.lha* %73, i32 0, i32 0, !dbg !3438
  %74 = load i64, i64* %entry_offset56, align 8, !dbg !3438
  %75 = load i64*, i64** %offset.addr, align 8, !dbg !3439
  store i64 %74, i64* %75, align 8, !dbg !3440
  %76 = load i64*, i64** %size.addr, align 8, !dbg !3441
  store i64 0, i64* %76, align 8, !dbg !3442
  %77 = load i8**, i8*** %buff.addr, align 8, !dbg !3443
  store i8* null, i8** %77, align 8, !dbg !3444
  %78 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3445
  %end_of_entry57 = getelementptr inbounds %struct.lha, %struct.lha* %78, i32 0, i32 32, !dbg !3447
  %79 = load i8, i8* %end_of_entry57, align 4, !dbg !3447
  %tobool58 = icmp ne i8 %79, 0, !dbg !3445
  br i1 %tobool58, label %if.then59, label %if.end61, !dbg !3448

if.then59:                                        ; preds = %if.else
  %80 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3449
  %call60 = call i32 @lha_end_of_entry(%struct.archive_read* %80), !dbg !3450
  store i32 %call60, i32* %retval, align 4, !dbg !3451
  br label %return, !dbg !3451

if.end61:                                         ; preds = %if.else
  br label %if.end62

if.end62:                                         ; preds = %if.end61, %if.then48
  store i32 0, i32* %retval, align 4, !dbg !3452
  br label %return, !dbg !3452

return:                                           ; preds = %if.end62, %if.then59, %sw.default37, %if.then17, %sw.default, %sw.bb1
  %81 = load i32, i32* %retval, align 4, !dbg !3453
  ret i32 %81, !dbg !3453
}

; Function Attrs: nounwind uwtable
define internal i32 @lha_read_data_none(%struct.archive_read* %a, i8** %buff, i64* %size, i64* %offset) #0 !dbg !508 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %buff.addr = alloca i8**, align 8
  %size.addr = alloca i64*, align 8
  %offset.addr = alloca i64*, align 8
  %lha = alloca %struct.lha*, align 8
  %bytes_avail = alloca i64, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !3454, metadata !548), !dbg !3455
  store i8** %buff, i8*** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %buff.addr, metadata !3456, metadata !548), !dbg !3457
  store i64* %size, i64** %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %size.addr, metadata !3458, metadata !548), !dbg !3459
  store i64* %offset, i64** %offset.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %offset.addr, metadata !3460, metadata !548), !dbg !3461
  call void @llvm.dbg.declare(metadata %struct.lha** %lha, metadata !3462, metadata !548), !dbg !3463
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3464
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 13, !dbg !3465
  %1 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !3465
  %data = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %1, i32 0, i32 0, !dbg !3466
  %2 = load i8*, i8** %data, align 8, !dbg !3466
  %3 = bitcast i8* %2 to %struct.lha*, !dbg !3467
  store %struct.lha* %3, %struct.lha** %lha, align 8, !dbg !3463
  call void @llvm.dbg.declare(metadata i64* %bytes_avail, metadata !3468, metadata !548), !dbg !3469
  %4 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3470
  %entry_bytes_remaining = getelementptr inbounds %struct.lha, %struct.lha* %4, i32 0, i32 1, !dbg !3472
  %5 = load i64, i64* %entry_bytes_remaining, align 8, !dbg !3472
  %cmp = icmp eq i64 %5, 0, !dbg !3473
  br i1 %cmp, label %if.then, label %if.end, !dbg !3474

if.then:                                          ; preds = %entry
  %6 = load i8**, i8*** %buff.addr, align 8, !dbg !3475
  store i8* null, i8** %6, align 8, !dbg !3477
  %7 = load i64*, i64** %size.addr, align 8, !dbg !3478
  store i64 0, i64* %7, align 8, !dbg !3479
  %8 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3480
  %entry_offset = getelementptr inbounds %struct.lha, %struct.lha* %8, i32 0, i32 0, !dbg !3481
  %9 = load i64, i64* %entry_offset, align 8, !dbg !3481
  %10 = load i64*, i64** %offset.addr, align 8, !dbg !3482
  store i64 %9, i64* %10, align 8, !dbg !3483
  %11 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3484
  %end_of_entry = getelementptr inbounds %struct.lha, %struct.lha* %11, i32 0, i32 32, !dbg !3485
  store i8 1, i8* %end_of_entry, align 4, !dbg !3486
  store i32 0, i32* %retval, align 4, !dbg !3487
  br label %return, !dbg !3487

if.end:                                           ; preds = %entry
  %12 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3488
  %call = call i8* @__archive_read_ahead(%struct.archive_read* %12, i64 1, i64* %bytes_avail), !dbg !3489
  %13 = load i8**, i8*** %buff.addr, align 8, !dbg !3490
  store i8* %call, i8** %13, align 8, !dbg !3491
  %14 = load i64, i64* %bytes_avail, align 8, !dbg !3492
  %cmp1 = icmp sle i64 %14, 0, !dbg !3494
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !3495

if.then2:                                         ; preds = %if.end
  %15 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !3496
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %15, i32 0, i32 0, !dbg !3498
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 84, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.30, i32 0, i32 0)), !dbg !3499
  store i32 -30, i32* %retval, align 4, !dbg !3500
  br label %return, !dbg !3500

if.end3:                                          ; preds = %if.end
  %16 = load i64, i64* %bytes_avail, align 8, !dbg !3501
  %17 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3503
  %entry_bytes_remaining4 = getelementptr inbounds %struct.lha, %struct.lha* %17, i32 0, i32 1, !dbg !3504
  %18 = load i64, i64* %entry_bytes_remaining4, align 8, !dbg !3504
  %cmp5 = icmp sgt i64 %16, %18, !dbg !3505
  br i1 %cmp5, label %if.then6, label %if.end8, !dbg !3506

if.then6:                                         ; preds = %if.end3
  %19 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3507
  %entry_bytes_remaining7 = getelementptr inbounds %struct.lha, %struct.lha* %19, i32 0, i32 1, !dbg !3508
  %20 = load i64, i64* %entry_bytes_remaining7, align 8, !dbg !3508
  store i64 %20, i64* %bytes_avail, align 8, !dbg !3509
  br label %if.end8, !dbg !3510

if.end8:                                          ; preds = %if.then6, %if.end3
  %21 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3511
  %entry_crc_calculated = getelementptr inbounds %struct.lha, %struct.lha* %21, i32 0, i32 3, !dbg !3512
  %22 = load i16, i16* %entry_crc_calculated, align 8, !dbg !3512
  %23 = load i8**, i8*** %buff.addr, align 8, !dbg !3513
  %24 = load i8*, i8** %23, align 8, !dbg !3514
  %25 = load i64, i64* %bytes_avail, align 8, !dbg !3515
  %call9 = call zeroext i16 @lha_crc16(i16 zeroext %22, i8* %24, i64 %25), !dbg !3516
  %26 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3517
  %entry_crc_calculated10 = getelementptr inbounds %struct.lha, %struct.lha* %26, i32 0, i32 3, !dbg !3518
  store i16 %call9, i16* %entry_crc_calculated10, align 8, !dbg !3519
  %27 = load i64, i64* %bytes_avail, align 8, !dbg !3520
  %28 = load i64*, i64** %size.addr, align 8, !dbg !3521
  store i64 %27, i64* %28, align 8, !dbg !3522
  %29 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3523
  %entry_offset11 = getelementptr inbounds %struct.lha, %struct.lha* %29, i32 0, i32 0, !dbg !3524
  %30 = load i64, i64* %entry_offset11, align 8, !dbg !3524
  %31 = load i64*, i64** %offset.addr, align 8, !dbg !3525
  store i64 %30, i64* %31, align 8, !dbg !3526
  %32 = load i64, i64* %bytes_avail, align 8, !dbg !3527
  %33 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3528
  %entry_offset12 = getelementptr inbounds %struct.lha, %struct.lha* %33, i32 0, i32 0, !dbg !3529
  %34 = load i64, i64* %entry_offset12, align 8, !dbg !3530
  %add = add nsw i64 %34, %32, !dbg !3530
  store i64 %add, i64* %entry_offset12, align 8, !dbg !3530
  %35 = load i64, i64* %bytes_avail, align 8, !dbg !3531
  %36 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3532
  %entry_bytes_remaining13 = getelementptr inbounds %struct.lha, %struct.lha* %36, i32 0, i32 1, !dbg !3533
  %37 = load i64, i64* %entry_bytes_remaining13, align 8, !dbg !3534
  %sub = sub nsw i64 %37, %35, !dbg !3534
  store i64 %sub, i64* %entry_bytes_remaining13, align 8, !dbg !3534
  %38 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3535
  %entry_bytes_remaining14 = getelementptr inbounds %struct.lha, %struct.lha* %38, i32 0, i32 1, !dbg !3537
  %39 = load i64, i64* %entry_bytes_remaining14, align 8, !dbg !3537
  %cmp15 = icmp eq i64 %39, 0, !dbg !3538
  br i1 %cmp15, label %if.then16, label %if.end18, !dbg !3539

if.then16:                                        ; preds = %if.end8
  %40 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3540
  %end_of_entry17 = getelementptr inbounds %struct.lha, %struct.lha* %40, i32 0, i32 32, !dbg !3541
  store i8 1, i8* %end_of_entry17, align 4, !dbg !3542
  br label %if.end18, !dbg !3540

if.end18:                                         ; preds = %if.then16, %if.end8
  %41 = load i64, i64* %bytes_avail, align 8, !dbg !3543
  %42 = load %struct.lha*, %struct.lha** %lha, align 8, !dbg !3544
  %entry_unconsumed = getelementptr inbounds %struct.lha, %struct.lha* %42, i32 0, i32 2, !dbg !3545
  store i64 %41, i64* %entry_unconsumed, align 8, !dbg !3546
  store i32 0, i32* %retval, align 4, !dbg !3547
  br label %return, !dbg !3547

return:                                           ; preds = %if.end18, %if.then2, %if.then
  %43 = load i32, i32* %retval, align 4, !dbg !3548
  ret i32 %43, !dbg !3548
}

; Function Attrs: nounwind uwtable
define internal i32 @lzh_decode_init(%struct.lzh_stream* %strm, i8* %method) #0 !dbg !473 {
entry:
  %retval = alloca i32, align 4
  %strm.addr = alloca %struct.lzh_stream*, align 8
  %method.addr = alloca i8*, align 8
  %ds = alloca %struct.lzh_dec*, align 8
  %w_bits = alloca i32, align 4
  %w_size = alloca i32, align 4
  store %struct.lzh_stream* %strm, %struct.lzh_stream** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzh_stream** %strm.addr, metadata !3549, metadata !548), !dbg !3550
  store i8* %method, i8** %method.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %method.addr, metadata !3551, metadata !548), !dbg !3552
  call void @llvm.dbg.declare(metadata %struct.lzh_dec** %ds, metadata !3553, metadata !548), !dbg !3554
  call void @llvm.dbg.declare(metadata i32* %w_bits, metadata !3555, metadata !548), !dbg !3556
  call void @llvm.dbg.declare(metadata i32* %w_size, metadata !3557, metadata !548), !dbg !3558
  %0 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !3559
  %ds1 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %0, i32 0, i32 6, !dbg !3561
  %1 = load %struct.lzh_dec*, %struct.lzh_dec** %ds1, align 8, !dbg !3561
  %cmp = icmp eq %struct.lzh_dec* %1, null, !dbg !3562
  br i1 %cmp, label %if.then, label %if.end6, !dbg !3563

if.then:                                          ; preds = %entry
  %call = call noalias i8* @calloc(i64 1, i64 344) #8, !dbg !3564
  %2 = bitcast i8* %call to %struct.lzh_dec*, !dbg !3564
  %3 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !3566
  %ds2 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %3, i32 0, i32 6, !dbg !3567
  store %struct.lzh_dec* %2, %struct.lzh_dec** %ds2, align 8, !dbg !3568
  %4 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !3569
  %ds3 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %4, i32 0, i32 6, !dbg !3571
  %5 = load %struct.lzh_dec*, %struct.lzh_dec** %ds3, align 8, !dbg !3571
  %cmp4 = icmp eq %struct.lzh_dec* %5, null, !dbg !3572
  br i1 %cmp4, label %if.then5, label %if.end, !dbg !3573

if.then5:                                         ; preds = %if.then
  store i32 -30, i32* %retval, align 4, !dbg !3574
  br label %return, !dbg !3574

if.end:                                           ; preds = %if.then
  br label %if.end6, !dbg !3575

if.end6:                                          ; preds = %if.end, %entry
  %6 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !3576
  %ds7 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %6, i32 0, i32 6, !dbg !3577
  %7 = load %struct.lzh_dec*, %struct.lzh_dec** %ds7, align 8, !dbg !3577
  store %struct.lzh_dec* %7, %struct.lzh_dec** %ds, align 8, !dbg !3578
  %8 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3579
  %error = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %8, i32 0, i32 17, !dbg !3580
  store i32 -25, i32* %error, align 4, !dbg !3581
  %9 = load i8*, i8** %method.addr, align 8, !dbg !3582
  %cmp8 = icmp eq i8* %9, null, !dbg !3584
  br i1 %cmp8, label %if.then16, label %lor.lhs.false, !dbg !3585

lor.lhs.false:                                    ; preds = %if.end6
  %10 = load i8*, i8** %method.addr, align 8, !dbg !3586
  %arrayidx = getelementptr inbounds i8, i8* %10, i64 0, !dbg !3586
  %11 = load i8, i8* %arrayidx, align 1, !dbg !3586
  %conv = sext i8 %11 to i32, !dbg !3586
  %cmp9 = icmp ne i32 %conv, 108, !dbg !3588
  br i1 %cmp9, label %if.then16, label %lor.lhs.false11, !dbg !3589

lor.lhs.false11:                                  ; preds = %lor.lhs.false
  %12 = load i8*, i8** %method.addr, align 8, !dbg !3590
  %arrayidx12 = getelementptr inbounds i8, i8* %12, i64 1, !dbg !3590
  %13 = load i8, i8* %arrayidx12, align 1, !dbg !3590
  %conv13 = sext i8 %13 to i32, !dbg !3590
  %cmp14 = icmp ne i32 %conv13, 104, !dbg !3592
  br i1 %cmp14, label %if.then16, label %if.end17, !dbg !3593

if.then16:                                        ; preds = %lor.lhs.false11, %lor.lhs.false, %if.end6
  store i32 -25, i32* %retval, align 4, !dbg !3594
  br label %return, !dbg !3594

if.end17:                                         ; preds = %lor.lhs.false11
  %14 = load i8*, i8** %method.addr, align 8, !dbg !3595
  %arrayidx18 = getelementptr inbounds i8, i8* %14, i64 2, !dbg !3595
  %15 = load i8, i8* %arrayidx18, align 1, !dbg !3595
  %conv19 = sext i8 %15 to i32, !dbg !3595
  switch i32 %conv19, label %sw.default [
    i32 53, label %sw.bb
    i32 54, label %sw.bb20
    i32 55, label %sw.bb21
  ], !dbg !3596

sw.bb:                                            ; preds = %if.end17
  store i32 13, i32* %w_bits, align 4, !dbg !3597
  br label %sw.epilog, !dbg !3599

sw.bb20:                                          ; preds = %if.end17
  store i32 15, i32* %w_bits, align 4, !dbg !3600
  br label %sw.epilog, !dbg !3601

sw.bb21:                                          ; preds = %if.end17
  store i32 16, i32* %w_bits, align 4, !dbg !3602
  br label %sw.epilog, !dbg !3603

sw.default:                                       ; preds = %if.end17
  store i32 -25, i32* %retval, align 4, !dbg !3604
  br label %return, !dbg !3604

sw.epilog:                                        ; preds = %sw.bb21, %sw.bb20, %sw.bb
  %16 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3605
  %error22 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %16, i32 0, i32 17, !dbg !3606
  store i32 -30, i32* %error22, align 4, !dbg !3607
  %17 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3608
  %w_size23 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %17, i32 0, i32 1, !dbg !3609
  store i32 131072, i32* %w_size23, align 4, !dbg !3610
  %18 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3611
  %w_size24 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %18, i32 0, i32 1, !dbg !3612
  %19 = load i32, i32* %w_size24, align 4, !dbg !3612
  %sub = sub nsw i32 %19, 1, !dbg !3613
  %20 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3614
  %w_mask = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %20, i32 0, i32 2, !dbg !3615
  store i32 %sub, i32* %w_mask, align 8, !dbg !3616
  %21 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3617
  %w_buff = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %21, i32 0, i32 3, !dbg !3619
  %22 = load i8*, i8** %w_buff, align 8, !dbg !3619
  %cmp25 = icmp eq i8* %22, null, !dbg !3620
  br i1 %cmp25, label %if.then27, label %if.end37, !dbg !3621

if.then27:                                        ; preds = %sw.epilog
  %23 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3622
  %w_size28 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %23, i32 0, i32 1, !dbg !3624
  %24 = load i32, i32* %w_size28, align 4, !dbg !3624
  %conv29 = sext i32 %24 to i64, !dbg !3622
  %call30 = call noalias i8* @malloc(i64 %conv29) #8, !dbg !3625
  %25 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3626
  %w_buff31 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %25, i32 0, i32 3, !dbg !3627
  store i8* %call30, i8** %w_buff31, align 8, !dbg !3628
  %26 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3629
  %w_buff32 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %26, i32 0, i32 3, !dbg !3631
  %27 = load i8*, i8** %w_buff32, align 8, !dbg !3631
  %cmp33 = icmp eq i8* %27, null, !dbg !3632
  br i1 %cmp33, label %if.then35, label %if.end36, !dbg !3633

if.then35:                                        ; preds = %if.then27
  store i32 -30, i32* %retval, align 4, !dbg !3634
  br label %return, !dbg !3634

if.end36:                                         ; preds = %if.then27
  br label %if.end37, !dbg !3635

if.end37:                                         ; preds = %if.end36, %sw.epilog
  %28 = load i32, i32* %w_bits, align 4, !dbg !3636
  %shl = shl i32 1, %28, !dbg !3637
  store i32 %shl, i32* %w_size, align 4, !dbg !3638
  %29 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3639
  %w_buff38 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %29, i32 0, i32 3, !dbg !3640
  %30 = load i8*, i8** %w_buff38, align 8, !dbg !3640
  %31 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3641
  %w_size39 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %31, i32 0, i32 1, !dbg !3642
  %32 = load i32, i32* %w_size39, align 4, !dbg !3642
  %idx.ext = sext i32 %32 to i64, !dbg !3643
  %add.ptr = getelementptr inbounds i8, i8* %30, i64 %idx.ext, !dbg !3643
  %33 = load i32, i32* %w_size, align 4, !dbg !3644
  %idx.ext40 = sext i32 %33 to i64, !dbg !3645
  %idx.neg = sub i64 0, %idx.ext40, !dbg !3645
  %add.ptr41 = getelementptr inbounds i8, i8* %add.ptr, i64 %idx.neg, !dbg !3645
  %34 = load i32, i32* %w_size, align 4, !dbg !3646
  %conv42 = sext i32 %34 to i64, !dbg !3646
  call void @llvm.memset.p0i8.i64(i8* %add.ptr41, i8 32, i64 %conv42, i32 1, i1 false), !dbg !3647
  %35 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3648
  %w_pos = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %35, i32 0, i32 4, !dbg !3649
  store i32 0, i32* %w_pos, align 8, !dbg !3650
  %36 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3651
  %state = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %36, i32 0, i32 0, !dbg !3652
  store i32 0, i32* %state, align 8, !dbg !3653
  %37 = load i32, i32* %w_bits, align 4, !dbg !3654
  %add = add nsw i32 %37, 1, !dbg !3655
  %38 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3656
  %pos_pt_len_size = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %38, i32 0, i32 11, !dbg !3657
  store i32 %add, i32* %pos_pt_len_size, align 4, !dbg !3658
  %39 = load i32, i32* %w_bits, align 4, !dbg !3659
  %cmp43 = icmp eq i32 %39, 15, !dbg !3660
  br i1 %cmp43, label %lor.end, label %lor.rhs, !dbg !3661

lor.rhs:                                          ; preds = %if.end37
  %40 = load i32, i32* %w_bits, align 4, !dbg !3662
  %cmp45 = icmp eq i32 %40, 16, !dbg !3664
  br label %lor.end, !dbg !3665

lor.end:                                          ; preds = %lor.rhs, %if.end37
  %41 = phi i1 [ true, %if.end37 ], [ %cmp45, %lor.rhs ]
  %cond = select i1 %41, i32 5, i32 4, !dbg !3666
  %42 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3668
  %pos_pt_len_bits = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %42, i32 0, i32 12, !dbg !3669
  store i32 %cond, i32* %pos_pt_len_bits, align 8, !dbg !3670
  %43 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3671
  %literal_pt_len_size = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %43, i32 0, i32 13, !dbg !3672
  store i32 19, i32* %literal_pt_len_size, align 4, !dbg !3673
  %44 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3674
  %literal_pt_len_bits = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %44, i32 0, i32 14, !dbg !3675
  store i32 5, i32* %literal_pt_len_bits, align 8, !dbg !3676
  %45 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3677
  %br = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %45, i32 0, i32 7, !dbg !3678
  %cache_buffer = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %br, i32 0, i32 0, !dbg !3679
  store i64 0, i64* %cache_buffer, align 8, !dbg !3680
  %46 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3681
  %br47 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %46, i32 0, i32 7, !dbg !3682
  %cache_avail = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %br47, i32 0, i32 1, !dbg !3683
  store i32 0, i32* %cache_avail, align 8, !dbg !3684
  %47 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3685
  %lt = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %47, i32 0, i32 8, !dbg !3687
  %call48 = call i32 @lzh_huffman_init(%struct.huffman* %lt, i64 510, i32 16), !dbg !3688
  %cmp49 = icmp ne i32 %call48, 0, !dbg !3689
  br i1 %cmp49, label %if.then51, label %if.end52, !dbg !3690

if.then51:                                        ; preds = %lor.end
  store i32 -30, i32* %retval, align 4, !dbg !3691
  br label %return, !dbg !3691

if.end52:                                         ; preds = %lor.end
  %48 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3692
  %lt53 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %48, i32 0, i32 8, !dbg !3693
  %len_bits = getelementptr inbounds %struct.huffman, %struct.huffman* %lt53, i32 0, i32 2, !dbg !3694
  store i32 9, i32* %len_bits, align 8, !dbg !3695
  %49 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3696
  %pt = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %49, i32 0, i32 9, !dbg !3698
  %call54 = call i32 @lzh_huffman_init(%struct.huffman* %pt, i64 19, i32 16), !dbg !3699
  %cmp55 = icmp ne i32 %call54, 0, !dbg !3700
  br i1 %cmp55, label %if.then57, label %if.end58, !dbg !3701

if.then57:                                        ; preds = %if.end52
  store i32 -30, i32* %retval, align 4, !dbg !3702
  br label %return, !dbg !3702

if.end58:                                         ; preds = %if.end52
  %50 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3703
  %error59 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %50, i32 0, i32 17, !dbg !3704
  store i32 0, i32* %error59, align 4, !dbg !3705
  store i32 0, i32* %retval, align 4, !dbg !3706
  br label %return, !dbg !3706

return:                                           ; preds = %if.end58, %if.then57, %if.then51, %if.then35, %sw.default, %if.then16, %if.then5
  %51 = load i32, i32* %retval, align 4, !dbg !3707
  ret i32 %51, !dbg !3707
}

; Function Attrs: nounwind uwtable
define internal i32 @lzh_decode(%struct.lzh_stream* %strm, i32 %last) #0 !dbg !481 {
entry:
  %retval = alloca i32, align 4
  %strm.addr = alloca %struct.lzh_stream*, align 8
  %last.addr = alloca i32, align 4
  %ds = alloca %struct.lzh_dec*, align 8
  %avail_in = alloca i32, align 4
  %r = alloca i32, align 4
  store %struct.lzh_stream* %strm, %struct.lzh_stream** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzh_stream** %strm.addr, metadata !3708, metadata !548), !dbg !3709
  store i32 %last, i32* %last.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %last.addr, metadata !3710, metadata !548), !dbg !3711
  call void @llvm.dbg.declare(metadata %struct.lzh_dec** %ds, metadata !3712, metadata !548), !dbg !3713
  %0 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !3714
  %ds1 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %0, i32 0, i32 6, !dbg !3715
  %1 = load %struct.lzh_dec*, %struct.lzh_dec** %ds1, align 8, !dbg !3715
  store %struct.lzh_dec* %1, %struct.lzh_dec** %ds, align 8, !dbg !3713
  call void @llvm.dbg.declare(metadata i32* %avail_in, metadata !3716, metadata !548), !dbg !3717
  call void @llvm.dbg.declare(metadata i32* %r, metadata !3718, metadata !548), !dbg !3719
  %2 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3720
  %error = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %2, i32 0, i32 17, !dbg !3722
  %3 = load i32, i32* %error, align 4, !dbg !3722
  %tobool = icmp ne i32 %3, 0, !dbg !3720
  br i1 %tobool, label %if.then, label %if.end, !dbg !3723

if.then:                                          ; preds = %entry
  %4 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3724
  %error2 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %4, i32 0, i32 17, !dbg !3725
  %5 = load i32, i32* %error2, align 4, !dbg !3725
  store i32 %5, i32* %retval, align 4, !dbg !3726
  br label %return, !dbg !3726

if.end:                                           ; preds = %entry
  %6 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !3727
  %avail_in3 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %6, i32 0, i32 1, !dbg !3728
  %7 = load i32, i32* %avail_in3, align 8, !dbg !3728
  store i32 %7, i32* %avail_in, align 4, !dbg !3729
  br label %do.body, !dbg !3730

do.body:                                          ; preds = %do.cond, %if.end
  %8 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3731
  %state = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %8, i32 0, i32 0, !dbg !3734
  %9 = load i32, i32* %state, align 8, !dbg !3734
  %cmp = icmp slt i32 %9, 9, !dbg !3735
  br i1 %cmp, label %if.then4, label %if.else, !dbg !3736

if.then4:                                         ; preds = %do.body
  %10 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !3737
  %11 = load i32, i32* %last.addr, align 4, !dbg !3738
  %call = call i32 @lzh_read_blocks(%struct.lzh_stream* %10, i32 %11), !dbg !3739
  store i32 %call, i32* %r, align 4, !dbg !3740
  br label %if.end6, !dbg !3741

if.else:                                          ; preds = %do.body
  %12 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !3742
  %13 = load i32, i32* %last.addr, align 4, !dbg !3743
  %call5 = call i32 @lzh_decode_blocks(%struct.lzh_stream* %12, i32 %13), !dbg !3744
  store i32 %call5, i32* %r, align 4, !dbg !3745
  br label %if.end6

if.end6:                                          ; preds = %if.else, %if.then4
  br label %do.cond, !dbg !3746

do.cond:                                          ; preds = %if.end6
  %14 = load i32, i32* %r, align 4, !dbg !3747
  %cmp7 = icmp eq i32 %14, 100, !dbg !3749
  br i1 %cmp7, label %do.body, label %do.end, !dbg !3750

do.end:                                           ; preds = %do.cond
  %15 = load i32, i32* %avail_in, align 4, !dbg !3751
  %16 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !3752
  %avail_in8 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %16, i32 0, i32 1, !dbg !3753
  %17 = load i32, i32* %avail_in8, align 8, !dbg !3753
  %sub = sub nsw i32 %15, %17, !dbg !3754
  %conv = sext i32 %sub to i64, !dbg !3751
  %18 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !3755
  %total_in = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %18, i32 0, i32 2, !dbg !3756
  %19 = load i64, i64* %total_in, align 8, !dbg !3757
  %add = add nsw i64 %19, %conv, !dbg !3757
  store i64 %add, i64* %total_in, align 8, !dbg !3757
  %20 = load i32, i32* %r, align 4, !dbg !3758
  store i32 %20, i32* %retval, align 4, !dbg !3759
  br label %return, !dbg !3759

return:                                           ; preds = %do.end, %if.then
  %21 = load i32, i32* %retval, align 4, !dbg !3760
  ret i32 %21, !dbg !3760
}

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #3

; Function Attrs: nounwind uwtable
define internal i32 @lzh_huffman_init(%struct.huffman* %hf, i64 %len_size, i32 %tbl_bits) #0 !dbg !477 {
entry:
  %retval = alloca i32, align 4
  %hf.addr = alloca %struct.huffman*, align 8
  %len_size.addr = alloca i64, align 8
  %tbl_bits.addr = alloca i32, align 4
  %bits = alloca i32, align 4
  store %struct.huffman* %hf, %struct.huffman** %hf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.huffman** %hf.addr, metadata !3761, metadata !548), !dbg !3762
  store i64 %len_size, i64* %len_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %len_size.addr, metadata !3763, metadata !548), !dbg !3764
  store i32 %tbl_bits, i32* %tbl_bits.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tbl_bits.addr, metadata !3765, metadata !548), !dbg !3766
  call void @llvm.dbg.declare(metadata i32* %bits, metadata !3767, metadata !548), !dbg !3768
  %0 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !3769
  %bitlen = getelementptr inbounds %struct.huffman, %struct.huffman* %0, i32 0, i32 4, !dbg !3771
  %1 = load i8*, i8** %bitlen, align 8, !dbg !3771
  %cmp = icmp eq i8* %1, null, !dbg !3772
  br i1 %cmp, label %if.then, label %if.end5, !dbg !3773

if.then:                                          ; preds = %entry
  %2 = load i64, i64* %len_size.addr, align 8, !dbg !3774
  %mul = mul i64 %2, 1, !dbg !3776
  %call = call noalias i8* @malloc(i64 %mul) #8, !dbg !3777
  %3 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !3778
  %bitlen1 = getelementptr inbounds %struct.huffman, %struct.huffman* %3, i32 0, i32 4, !dbg !3779
  store i8* %call, i8** %bitlen1, align 8, !dbg !3780
  %4 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !3781
  %bitlen2 = getelementptr inbounds %struct.huffman, %struct.huffman* %4, i32 0, i32 4, !dbg !3783
  %5 = load i8*, i8** %bitlen2, align 8, !dbg !3783
  %cmp3 = icmp eq i8* %5, null, !dbg !3784
  br i1 %cmp3, label %if.then4, label %if.end, !dbg !3785

if.then4:                                         ; preds = %if.then
  store i32 -30, i32* %retval, align 4, !dbg !3786
  br label %return, !dbg !3786

if.end:                                           ; preds = %if.then
  br label %if.end5, !dbg !3787

if.end5:                                          ; preds = %if.end, %entry
  %6 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !3788
  %tbl = getelementptr inbounds %struct.huffman, %struct.huffman* %6, i32 0, i32 10, !dbg !3790
  %7 = load i16*, i16** %tbl, align 8, !dbg !3790
  %cmp6 = icmp eq i16* %7, null, !dbg !3791
  br i1 %cmp6, label %if.then7, label %if.end18, !dbg !3792

if.then7:                                         ; preds = %if.end5
  %8 = load i32, i32* %tbl_bits.addr, align 4, !dbg !3793
  %cmp8 = icmp slt i32 %8, 10, !dbg !3796
  br i1 %cmp8, label %if.then9, label %if.else, !dbg !3797

if.then9:                                         ; preds = %if.then7
  %9 = load i32, i32* %tbl_bits.addr, align 4, !dbg !3798
  store i32 %9, i32* %bits, align 4, !dbg !3799
  br label %if.end10, !dbg !3800

if.else:                                          ; preds = %if.then7
  store i32 10, i32* %bits, align 4, !dbg !3801
  br label %if.end10

if.end10:                                         ; preds = %if.else, %if.then9
  %10 = load i32, i32* %bits, align 4, !dbg !3802
  %sh_prom = zext i32 %10 to i64, !dbg !3803
  %shl = shl i64 1, %sh_prom, !dbg !3803
  %mul11 = mul i64 %shl, 2, !dbg !3804
  %call12 = call noalias i8* @malloc(i64 %mul11) #8, !dbg !3805
  %11 = bitcast i8* %call12 to i16*, !dbg !3805
  %12 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !3806
  %tbl13 = getelementptr inbounds %struct.huffman, %struct.huffman* %12, i32 0, i32 10, !dbg !3807
  store i16* %11, i16** %tbl13, align 8, !dbg !3808
  %13 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !3809
  %tbl14 = getelementptr inbounds %struct.huffman, %struct.huffman* %13, i32 0, i32 10, !dbg !3811
  %14 = load i16*, i16** %tbl14, align 8, !dbg !3811
  %cmp15 = icmp eq i16* %14, null, !dbg !3812
  br i1 %cmp15, label %if.then16, label %if.end17, !dbg !3813

if.then16:                                        ; preds = %if.end10
  store i32 -30, i32* %retval, align 4, !dbg !3814
  br label %return, !dbg !3814

if.end17:                                         ; preds = %if.end10
  br label %if.end18, !dbg !3815

if.end18:                                         ; preds = %if.end17, %if.end5
  %15 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !3816
  %tree = getelementptr inbounds %struct.huffman, %struct.huffman* %15, i32 0, i32 11, !dbg !3818
  %16 = load %struct.htree_t*, %struct.htree_t** %tree, align 8, !dbg !3818
  %cmp19 = icmp eq %struct.htree_t* %16, null, !dbg !3819
  br i1 %cmp19, label %land.lhs.true, label %if.end32, !dbg !3820

land.lhs.true:                                    ; preds = %if.end18
  %17 = load i32, i32* %tbl_bits.addr, align 4, !dbg !3821
  %cmp20 = icmp sgt i32 %17, 10, !dbg !3823
  br i1 %cmp20, label %if.then21, label %if.end32, !dbg !3824

if.then21:                                        ; preds = %land.lhs.true
  %18 = load i32, i32* %tbl_bits.addr, align 4, !dbg !3825
  %sub = sub nsw i32 %18, 10, !dbg !3827
  %add = add nsw i32 %sub, 4, !dbg !3828
  %shl22 = shl i32 1, %add, !dbg !3829
  %19 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !3830
  %tree_avail = getelementptr inbounds %struct.huffman, %struct.huffman* %19, i32 0, i32 9, !dbg !3831
  store i32 %shl22, i32* %tree_avail, align 8, !dbg !3832
  %20 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !3833
  %tree_avail23 = getelementptr inbounds %struct.huffman, %struct.huffman* %20, i32 0, i32 9, !dbg !3834
  %21 = load i32, i32* %tree_avail23, align 8, !dbg !3834
  %conv = sext i32 %21 to i64, !dbg !3833
  %mul24 = mul i64 %conv, 4, !dbg !3835
  %call25 = call noalias i8* @malloc(i64 %mul24) #8, !dbg !3836
  %22 = bitcast i8* %call25 to %struct.htree_t*, !dbg !3836
  %23 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !3837
  %tree26 = getelementptr inbounds %struct.huffman, %struct.huffman* %23, i32 0, i32 11, !dbg !3838
  store %struct.htree_t* %22, %struct.htree_t** %tree26, align 8, !dbg !3839
  %24 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !3840
  %tree27 = getelementptr inbounds %struct.huffman, %struct.huffman* %24, i32 0, i32 11, !dbg !3842
  %25 = load %struct.htree_t*, %struct.htree_t** %tree27, align 8, !dbg !3842
  %cmp28 = icmp eq %struct.htree_t* %25, null, !dbg !3843
  br i1 %cmp28, label %if.then30, label %if.end31, !dbg !3844

if.then30:                                        ; preds = %if.then21
  store i32 -30, i32* %retval, align 4, !dbg !3845
  br label %return, !dbg !3845

if.end31:                                         ; preds = %if.then21
  br label %if.end32, !dbg !3846

if.end32:                                         ; preds = %if.end31, %land.lhs.true, %if.end18
  %26 = load i64, i64* %len_size.addr, align 8, !dbg !3847
  %conv33 = trunc i64 %26 to i32, !dbg !3848
  %27 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !3849
  %len_size34 = getelementptr inbounds %struct.huffman, %struct.huffman* %27, i32 0, i32 0, !dbg !3850
  store i32 %conv33, i32* %len_size34, align 8, !dbg !3851
  %28 = load i32, i32* %tbl_bits.addr, align 4, !dbg !3852
  %29 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !3853
  %tbl_bits35 = getelementptr inbounds %struct.huffman, %struct.huffman* %29, i32 0, i32 7, !dbg !3854
  store i32 %28, i32* %tbl_bits35, align 8, !dbg !3855
  store i32 0, i32* %retval, align 4, !dbg !3856
  br label %return, !dbg !3856

return:                                           ; preds = %if.end32, %if.then30, %if.then16, %if.then4
  %30 = load i32, i32* %retval, align 4, !dbg !3857
  ret i32 %30, !dbg !3857
}

; Function Attrs: nounwind uwtable
define internal i32 @lzh_read_blocks(%struct.lzh_stream* %strm, i32 %last) #0 !dbg !484 {
entry:
  %retval = alloca i32, align 4
  %strm.addr = alloca %struct.lzh_stream*, align 8
  %last.addr = alloca i32, align 4
  %ds = alloca %struct.lzh_dec*, align 8
  %br = alloca %struct.lzh_br*, align 8
  %c = alloca i32, align 4
  %i = alloca i32, align 4
  %rbits = alloca i32, align 4
  %n = alloca i32, align 4
  store %struct.lzh_stream* %strm, %struct.lzh_stream** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzh_stream** %strm.addr, metadata !3858, metadata !548), !dbg !3859
  store i32 %last, i32* %last.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %last.addr, metadata !3860, metadata !548), !dbg !3861
  call void @llvm.dbg.declare(metadata %struct.lzh_dec** %ds, metadata !3862, metadata !548), !dbg !3863
  %0 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !3864
  %ds1 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %0, i32 0, i32 6, !dbg !3865
  %1 = load %struct.lzh_dec*, %struct.lzh_dec** %ds1, align 8, !dbg !3865
  store %struct.lzh_dec* %1, %struct.lzh_dec** %ds, align 8, !dbg !3863
  call void @llvm.dbg.declare(metadata %struct.lzh_br** %br, metadata !3866, metadata !548), !dbg !3867
  %2 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3868
  %br2 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %2, i32 0, i32 7, !dbg !3869
  store %struct.lzh_br* %br2, %struct.lzh_br** %br, align 8, !dbg !3867
  call void @llvm.dbg.declare(metadata i32* %c, metadata !3870, metadata !548), !dbg !3871
  store i32 0, i32* %c, align 4, !dbg !3871
  call void @llvm.dbg.declare(metadata i32* %i, metadata !3872, metadata !548), !dbg !3873
  call void @llvm.dbg.declare(metadata i32* %rbits, metadata !3874, metadata !548), !dbg !3875
  br label %for.cond, !dbg !3876

for.cond:                                         ; preds = %sw.epilog, %entry
  %3 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3877
  %state = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %3, i32 0, i32 0, !dbg !3881
  %4 = load i32, i32* %state, align 8, !dbg !3881
  switch i32 %4, label %sw.epilog [
    i32 0, label %sw.bb
    i32 1, label %sw.bb27
    i32 2, label %sw.bb66
    i32 3, label %sw.bb146
    i32 4, label %sw.bb204
    i32 5, label %sw.bb235
    i32 6, label %sw.bb276
    i32 7, label %sw.bb342
    i32 8, label %sw.bb503
    i32 9, label %sw.bb511
  ], !dbg !3882

sw.bb:                                            ; preds = %for.cond
  %5 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !3883
  %cache_avail = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %5, i32 0, i32 1, !dbg !3883
  %6 = load i32, i32* %cache_avail, align 8, !dbg !3883
  %cmp = icmp sge i32 %6, 16, !dbg !3883
  br i1 %cmp, label %if.end14, label %lor.lhs.false, !dbg !3883

lor.lhs.false:                                    ; preds = %sw.bb
  %7 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !3886
  %8 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !3886
  %call = call i32 @lzh_br_fillup(%struct.lzh_stream* %7, %struct.lzh_br* %8), !dbg !3886
  %tobool = icmp ne i32 %call, 0, !dbg !3886
  br i1 %tobool, label %if.end14, label %if.then, !dbg !3888

if.then:                                          ; preds = %lor.lhs.false
  %9 = load i32, i32* %last.addr, align 4, !dbg !3889
  %tobool3 = icmp ne i32 %9, 0, !dbg !3889
  br i1 %tobool3, label %if.end, label %if.then4, !dbg !3892

if.then4:                                         ; preds = %if.then
  store i32 0, i32* %retval, align 4, !dbg !3893
  br label %return, !dbg !3893

if.end:                                           ; preds = %if.then
  %10 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !3894
  %cache_avail5 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %10, i32 0, i32 1, !dbg !3894
  %11 = load i32, i32* %cache_avail5, align 8, !dbg !3894
  %cmp6 = icmp sge i32 %11, 8, !dbg !3894
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !3896

if.then7:                                         ; preds = %if.end
  br label %failed, !dbg !3897

if.end8:                                          ; preds = %if.end
  %12 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3899
  %w_pos = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %12, i32 0, i32 4, !dbg !3901
  %13 = load i32, i32* %w_pos, align 8, !dbg !3901
  %cmp9 = icmp sgt i32 %13, 0, !dbg !3902
  br i1 %cmp9, label %if.then10, label %if.end13, !dbg !3903

if.then10:                                        ; preds = %if.end8
  %14 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !3904
  %15 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3906
  %w_pos11 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %15, i32 0, i32 4, !dbg !3907
  %16 = load i32, i32* %w_pos11, align 8, !dbg !3907
  %conv = sext i32 %16 to i64, !dbg !3906
  call void @lzh_emit_window(%struct.lzh_stream* %14, i64 %conv), !dbg !3908
  %17 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3909
  %w_pos12 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %17, i32 0, i32 4, !dbg !3910
  store i32 0, i32* %w_pos12, align 8, !dbg !3911
  store i32 0, i32* %retval, align 4, !dbg !3912
  br label %return, !dbg !3912

if.end13:                                         ; preds = %if.end8
  store i32 1, i32* %retval, align 4, !dbg !3913
  br label %return, !dbg !3913

if.end14:                                         ; preds = %lor.lhs.false, %sw.bb
  %18 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !3914
  %cache_buffer = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %18, i32 0, i32 0, !dbg !3914
  %19 = load i64, i64* %cache_buffer, align 8, !dbg !3914
  %20 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !3914
  %cache_avail15 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %20, i32 0, i32 1, !dbg !3914
  %21 = load i32, i32* %cache_avail15, align 8, !dbg !3914
  %sub = sub nsw i32 %21, 16, !dbg !3914
  %sh_prom = zext i32 %sub to i64, !dbg !3914
  %shr = lshr i64 %19, %sh_prom, !dbg !3914
  %conv16 = trunc i64 %shr to i16, !dbg !3914
  %conv17 = zext i16 %conv16 to i32, !dbg !3914
  %22 = load i16, i16* getelementptr inbounds ([20 x i16], [20 x i16]* @cache_masks, i64 0, i64 16), align 16, !dbg !3914
  %conv18 = zext i16 %22 to i32, !dbg !3914
  %and = and i32 %conv17, %conv18, !dbg !3914
  %23 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3915
  %blocks_avail = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %23, i32 0, i32 10, !dbg !3916
  store i32 %and, i32* %blocks_avail, align 8, !dbg !3917
  %24 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3918
  %blocks_avail19 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %24, i32 0, i32 10, !dbg !3920
  %25 = load i32, i32* %blocks_avail19, align 8, !dbg !3920
  %cmp20 = icmp eq i32 %25, 0, !dbg !3921
  br i1 %cmp20, label %if.then22, label %if.end23, !dbg !3922

if.then22:                                        ; preds = %if.end14
  br label %failed, !dbg !3923

if.end23:                                         ; preds = %if.end14
  %26 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !3924
  %cache_avail24 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %26, i32 0, i32 1, !dbg !3924
  %27 = load i32, i32* %cache_avail24, align 8, !dbg !3924
  %sub25 = sub nsw i32 %27, 16, !dbg !3924
  store i32 %sub25, i32* %cache_avail24, align 8, !dbg !3924
  %28 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3925
  %literal_pt_len_size = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %28, i32 0, i32 13, !dbg !3926
  %29 = load i32, i32* %literal_pt_len_size, align 4, !dbg !3926
  %30 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3927
  %pt = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %30, i32 0, i32 9, !dbg !3928
  %len_size = getelementptr inbounds %struct.huffman, %struct.huffman* %pt, i32 0, i32 0, !dbg !3929
  store i32 %29, i32* %len_size, align 8, !dbg !3930
  %31 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3931
  %literal_pt_len_bits = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %31, i32 0, i32 14, !dbg !3932
  %32 = load i32, i32* %literal_pt_len_bits, align 8, !dbg !3932
  %33 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3933
  %pt26 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %33, i32 0, i32 9, !dbg !3934
  %len_bits = getelementptr inbounds %struct.huffman, %struct.huffman* %pt26, i32 0, i32 2, !dbg !3935
  store i32 %32, i32* %len_bits, align 8, !dbg !3936
  %34 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3937
  %reading_position = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %34, i32 0, i32 15, !dbg !3938
  store i32 0, i32* %reading_position, align 4, !dbg !3939
  br label %sw.bb27, !dbg !3937

sw.bb27:                                          ; preds = %for.cond, %if.end23
  %35 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !3940
  %cache_avail28 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %35, i32 0, i32 1, !dbg !3940
  %36 = load i32, i32* %cache_avail28, align 8, !dbg !3940
  %37 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3940
  %pt29 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %37, i32 0, i32 9, !dbg !3940
  %len_bits30 = getelementptr inbounds %struct.huffman, %struct.huffman* %pt29, i32 0, i32 2, !dbg !3940
  %38 = load i32, i32* %len_bits30, align 8, !dbg !3940
  %cmp31 = icmp sge i32 %36, %38, !dbg !3940
  br i1 %cmp31, label %if.end47, label %lor.lhs.false33, !dbg !3940

lor.lhs.false33:                                  ; preds = %sw.bb27
  %39 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !3942
  %40 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !3942
  %call34 = call i32 @lzh_br_fillup(%struct.lzh_stream* %39, %struct.lzh_br* %40), !dbg !3942
  %tobool35 = icmp ne i32 %call34, 0, !dbg !3942
  br i1 %tobool35, label %if.end47, label %lor.lhs.false36, !dbg !3942

lor.lhs.false36:                                  ; preds = %lor.lhs.false33
  %41 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !3944
  %cache_avail37 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %41, i32 0, i32 1, !dbg !3944
  %42 = load i32, i32* %cache_avail37, align 8, !dbg !3944
  %43 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3944
  %pt38 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %43, i32 0, i32 9, !dbg !3944
  %len_bits39 = getelementptr inbounds %struct.huffman, %struct.huffman* %pt38, i32 0, i32 2, !dbg !3944
  %44 = load i32, i32* %len_bits39, align 8, !dbg !3944
  %cmp40 = icmp sge i32 %42, %44, !dbg !3944
  br i1 %cmp40, label %if.end47, label %if.then42, !dbg !3946

if.then42:                                        ; preds = %lor.lhs.false36
  %45 = load i32, i32* %last.addr, align 4, !dbg !3947
  %tobool43 = icmp ne i32 %45, 0, !dbg !3947
  br i1 %tobool43, label %if.then44, label %if.end45, !dbg !3950

if.then44:                                        ; preds = %if.then42
  br label %failed, !dbg !3951

if.end45:                                         ; preds = %if.then42
  %46 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3952
  %state46 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %46, i32 0, i32 0, !dbg !3953
  store i32 1, i32* %state46, align 8, !dbg !3954
  store i32 0, i32* %retval, align 4, !dbg !3955
  br label %return, !dbg !3955

if.end47:                                         ; preds = %lor.lhs.false36, %lor.lhs.false33, %sw.bb27
  %47 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !3956
  %cache_buffer48 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %47, i32 0, i32 0, !dbg !3956
  %48 = load i64, i64* %cache_buffer48, align 8, !dbg !3956
  %49 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !3956
  %cache_avail49 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %49, i32 0, i32 1, !dbg !3956
  %50 = load i32, i32* %cache_avail49, align 8, !dbg !3956
  %51 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3956
  %pt50 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %51, i32 0, i32 9, !dbg !3956
  %len_bits51 = getelementptr inbounds %struct.huffman, %struct.huffman* %pt50, i32 0, i32 2, !dbg !3956
  %52 = load i32, i32* %len_bits51, align 8, !dbg !3956
  %sub52 = sub nsw i32 %50, %52, !dbg !3956
  %sh_prom53 = zext i32 %sub52 to i64, !dbg !3956
  %shr54 = lshr i64 %48, %sh_prom53, !dbg !3956
  %conv55 = trunc i64 %shr54 to i16, !dbg !3956
  %conv56 = zext i16 %conv55 to i32, !dbg !3956
  %53 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3956
  %pt57 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %53, i32 0, i32 9, !dbg !3956
  %len_bits58 = getelementptr inbounds %struct.huffman, %struct.huffman* %pt57, i32 0, i32 2, !dbg !3956
  %54 = load i32, i32* %len_bits58, align 8, !dbg !3956
  %idxprom = sext i32 %54 to i64, !dbg !3956
  %arrayidx = getelementptr inbounds [20 x i16], [20 x i16]* @cache_masks, i64 0, i64 %idxprom, !dbg !3956
  %55 = load i16, i16* %arrayidx, align 2, !dbg !3956
  %conv59 = zext i16 %55 to i32, !dbg !3956
  %and60 = and i32 %conv56, %conv59, !dbg !3956
  %56 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3957
  %pt61 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %56, i32 0, i32 9, !dbg !3958
  %len_avail = getelementptr inbounds %struct.huffman, %struct.huffman* %pt61, i32 0, i32 1, !dbg !3959
  store i32 %and60, i32* %len_avail, align 4, !dbg !3960
  %57 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3961
  %pt62 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %57, i32 0, i32 9, !dbg !3961
  %len_bits63 = getelementptr inbounds %struct.huffman, %struct.huffman* %pt62, i32 0, i32 2, !dbg !3961
  %58 = load i32, i32* %len_bits63, align 8, !dbg !3961
  %59 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !3961
  %cache_avail64 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %59, i32 0, i32 1, !dbg !3961
  %60 = load i32, i32* %cache_avail64, align 8, !dbg !3961
  %sub65 = sub nsw i32 %60, %58, !dbg !3961
  store i32 %sub65, i32* %cache_avail64, align 8, !dbg !3961
  br label %sw.bb66, !dbg !3961

sw.bb66:                                          ; preds = %for.cond, %if.end47
  %61 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3962
  %pt67 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %61, i32 0, i32 9, !dbg !3964
  %len_avail68 = getelementptr inbounds %struct.huffman, %struct.huffman* %pt67, i32 0, i32 1, !dbg !3965
  %62 = load i32, i32* %len_avail68, align 4, !dbg !3965
  %cmp69 = icmp eq i32 %62, 0, !dbg !3966
  br i1 %cmp69, label %if.then71, label %if.else123, !dbg !3967

if.then71:                                        ; preds = %sw.bb66
  %63 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !3968
  %cache_avail72 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %63, i32 0, i32 1, !dbg !3968
  %64 = load i32, i32* %cache_avail72, align 8, !dbg !3968
  %65 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3968
  %pt73 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %65, i32 0, i32 9, !dbg !3968
  %len_bits74 = getelementptr inbounds %struct.huffman, %struct.huffman* %pt73, i32 0, i32 2, !dbg !3968
  %66 = load i32, i32* %len_bits74, align 8, !dbg !3968
  %cmp75 = icmp sge i32 %64, %66, !dbg !3968
  br i1 %cmp75, label %if.end91, label %lor.lhs.false77, !dbg !3968

lor.lhs.false77:                                  ; preds = %if.then71
  %67 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !3971
  %68 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !3971
  %call78 = call i32 @lzh_br_fillup(%struct.lzh_stream* %67, %struct.lzh_br* %68), !dbg !3971
  %tobool79 = icmp ne i32 %call78, 0, !dbg !3971
  br i1 %tobool79, label %if.end91, label %lor.lhs.false80, !dbg !3971

lor.lhs.false80:                                  ; preds = %lor.lhs.false77
  %69 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !3973
  %cache_avail81 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %69, i32 0, i32 1, !dbg !3973
  %70 = load i32, i32* %cache_avail81, align 8, !dbg !3973
  %71 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3973
  %pt82 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %71, i32 0, i32 9, !dbg !3973
  %len_bits83 = getelementptr inbounds %struct.huffman, %struct.huffman* %pt82, i32 0, i32 2, !dbg !3973
  %72 = load i32, i32* %len_bits83, align 8, !dbg !3973
  %cmp84 = icmp sge i32 %70, %72, !dbg !3973
  br i1 %cmp84, label %if.end91, label %if.then86, !dbg !3975

if.then86:                                        ; preds = %lor.lhs.false80
  %73 = load i32, i32* %last.addr, align 4, !dbg !3976
  %tobool87 = icmp ne i32 %73, 0, !dbg !3976
  br i1 %tobool87, label %if.then88, label %if.end89, !dbg !3979

if.then88:                                        ; preds = %if.then86
  br label %failed, !dbg !3980

if.end89:                                         ; preds = %if.then86
  %74 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3981
  %state90 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %74, i32 0, i32 0, !dbg !3982
  store i32 2, i32* %state90, align 8, !dbg !3983
  store i32 0, i32* %retval, align 4, !dbg !3984
  br label %return, !dbg !3984

if.end91:                                         ; preds = %lor.lhs.false80, %lor.lhs.false77, %if.then71
  %75 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3985
  %pt92 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %75, i32 0, i32 9, !dbg !3987
  %76 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !3988
  %cache_buffer93 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %76, i32 0, i32 0, !dbg !3988
  %77 = load i64, i64* %cache_buffer93, align 8, !dbg !3988
  %78 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !3988
  %cache_avail94 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %78, i32 0, i32 1, !dbg !3988
  %79 = load i32, i32* %cache_avail94, align 8, !dbg !3988
  %80 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3988
  %pt95 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %80, i32 0, i32 9, !dbg !3988
  %len_bits96 = getelementptr inbounds %struct.huffman, %struct.huffman* %pt95, i32 0, i32 2, !dbg !3988
  %81 = load i32, i32* %len_bits96, align 8, !dbg !3988
  %sub97 = sub nsw i32 %79, %81, !dbg !3988
  %sh_prom98 = zext i32 %sub97 to i64, !dbg !3988
  %shr99 = lshr i64 %77, %sh_prom98, !dbg !3988
  %conv100 = trunc i64 %shr99 to i16, !dbg !3988
  %conv101 = zext i16 %conv100 to i32, !dbg !3988
  %82 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3988
  %pt102 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %82, i32 0, i32 9, !dbg !3988
  %len_bits103 = getelementptr inbounds %struct.huffman, %struct.huffman* %pt102, i32 0, i32 2, !dbg !3988
  %83 = load i32, i32* %len_bits103, align 8, !dbg !3988
  %idxprom104 = sext i32 %83 to i64, !dbg !3988
  %arrayidx105 = getelementptr inbounds [20 x i16], [20 x i16]* @cache_masks, i64 0, i64 %idxprom104, !dbg !3988
  %84 = load i16, i16* %arrayidx105, align 2, !dbg !3988
  %conv106 = zext i16 %84 to i32, !dbg !3988
  %and107 = and i32 %conv101, %conv106, !dbg !3988
  %conv108 = trunc i32 %and107 to i16, !dbg !3988
  %call109 = call i32 @lzh_make_fake_table(%struct.huffman* %pt92, i16 zeroext %conv108), !dbg !3989
  %tobool110 = icmp ne i32 %call109, 0, !dbg !3989
  br i1 %tobool110, label %if.end112, label %if.then111, !dbg !3990

if.then111:                                       ; preds = %if.end91
  br label %failed, !dbg !3991

if.end112:                                        ; preds = %if.end91
  %85 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3992
  %pt113 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %85, i32 0, i32 9, !dbg !3992
  %len_bits114 = getelementptr inbounds %struct.huffman, %struct.huffman* %pt113, i32 0, i32 2, !dbg !3992
  %86 = load i32, i32* %len_bits114, align 8, !dbg !3992
  %87 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !3992
  %cache_avail115 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %87, i32 0, i32 1, !dbg !3992
  %88 = load i32, i32* %cache_avail115, align 8, !dbg !3992
  %sub116 = sub nsw i32 %88, %86, !dbg !3992
  store i32 %sub116, i32* %cache_avail115, align 8, !dbg !3992
  %89 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3993
  %reading_position117 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %89, i32 0, i32 15, !dbg !3995
  %90 = load i32, i32* %reading_position117, align 4, !dbg !3995
  %tobool118 = icmp ne i32 %90, 0, !dbg !3993
  br i1 %tobool118, label %if.then119, label %if.else, !dbg !3996

if.then119:                                       ; preds = %if.end112
  %91 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !3997
  %state120 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %91, i32 0, i32 0, !dbg !3998
  store i32 9, i32* %state120, align 8, !dbg !3999
  br label %if.end122, !dbg !3997

if.else:                                          ; preds = %if.end112
  %92 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4000
  %state121 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %92, i32 0, i32 0, !dbg !4001
  store i32 5, i32* %state121, align 8, !dbg !4002
  br label %if.end122

if.end122:                                        ; preds = %if.else, %if.then119
  br label %sw.epilog, !dbg !4003

if.else123:                                       ; preds = %sw.bb66
  %93 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4004
  %pt124 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %93, i32 0, i32 9, !dbg !4006
  %len_avail125 = getelementptr inbounds %struct.huffman, %struct.huffman* %pt124, i32 0, i32 1, !dbg !4007
  %94 = load i32, i32* %len_avail125, align 4, !dbg !4007
  %95 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4008
  %pt126 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %95, i32 0, i32 9, !dbg !4009
  %len_size127 = getelementptr inbounds %struct.huffman, %struct.huffman* %pt126, i32 0, i32 0, !dbg !4010
  %96 = load i32, i32* %len_size127, align 8, !dbg !4010
  %cmp128 = icmp sgt i32 %94, %96, !dbg !4011
  br i1 %cmp128, label %if.then130, label %if.end131, !dbg !4012

if.then130:                                       ; preds = %if.else123
  br label %failed, !dbg !4013

if.end131:                                        ; preds = %if.else123
  br label %if.end132

if.end132:                                        ; preds = %if.end131
  %97 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4014
  %loop = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %97, i32 0, i32 16, !dbg !4015
  store i32 0, i32* %loop, align 8, !dbg !4016
  %98 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4017
  %pt133 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %98, i32 0, i32 9, !dbg !4018
  %freq = getelementptr inbounds %struct.huffman, %struct.huffman* %pt133, i32 0, i32 3, !dbg !4019
  %arraydecay = getelementptr inbounds [17 x i32], [17 x i32]* %freq, i32 0, i32 0, !dbg !4020
  %99 = bitcast i32* %arraydecay to i8*, !dbg !4020
  call void @llvm.memset.p0i8.i64(i8* %99, i8 0, i64 68, i32 4, i1 false), !dbg !4020
  %100 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4021
  %pt134 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %100, i32 0, i32 9, !dbg !4023
  %len_avail135 = getelementptr inbounds %struct.huffman, %struct.huffman* %pt134, i32 0, i32 1, !dbg !4024
  %101 = load i32, i32* %len_avail135, align 4, !dbg !4024
  %cmp136 = icmp slt i32 %101, 3, !dbg !4025
  br i1 %cmp136, label %if.then143, label %lor.lhs.false138, !dbg !4026

lor.lhs.false138:                                 ; preds = %if.end132
  %102 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4027
  %pt139 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %102, i32 0, i32 9, !dbg !4028
  %len_size140 = getelementptr inbounds %struct.huffman, %struct.huffman* %pt139, i32 0, i32 0, !dbg !4029
  %103 = load i32, i32* %len_size140, align 8, !dbg !4029
  %104 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4030
  %pos_pt_len_size = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %104, i32 0, i32 11, !dbg !4031
  %105 = load i32, i32* %pos_pt_len_size, align 4, !dbg !4031
  %cmp141 = icmp eq i32 %103, %105, !dbg !4032
  br i1 %cmp141, label %if.then143, label %if.end145, !dbg !4033

if.then143:                                       ; preds = %lor.lhs.false138, %if.end132
  %106 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4035
  %state144 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %106, i32 0, i32 0, !dbg !4037
  store i32 4, i32* %state144, align 8, !dbg !4038
  br label %sw.epilog, !dbg !4039

if.end145:                                        ; preds = %lor.lhs.false138
  br label %sw.bb146, !dbg !4040

sw.bb146:                                         ; preds = %for.cond, %if.end145
  %107 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !4042
  %108 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4043
  %loop147 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %108, i32 0, i32 16, !dbg !4044
  %109 = load i32, i32* %loop147, align 8, !dbg !4044
  %call148 = call i32 @lzh_read_pt_bitlen(%struct.lzh_stream* %107, i32 %109, i32 3), !dbg !4045
  %110 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4046
  %loop149 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %110, i32 0, i32 16, !dbg !4047
  store i32 %call148, i32* %loop149, align 8, !dbg !4048
  %111 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4049
  %loop150 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %111, i32 0, i32 16, !dbg !4051
  %112 = load i32, i32* %loop150, align 8, !dbg !4051
  %cmp151 = icmp slt i32 %112, 3, !dbg !4052
  br i1 %cmp151, label %if.then153, label %if.end162, !dbg !4053

if.then153:                                       ; preds = %sw.bb146
  %113 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4054
  %loop154 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %113, i32 0, i32 16, !dbg !4057
  %114 = load i32, i32* %loop154, align 8, !dbg !4057
  %cmp155 = icmp slt i32 %114, 0, !dbg !4058
  br i1 %cmp155, label %if.then159, label %lor.lhs.false157, !dbg !4059

lor.lhs.false157:                                 ; preds = %if.then153
  %115 = load i32, i32* %last.addr, align 4, !dbg !4060
  %tobool158 = icmp ne i32 %115, 0, !dbg !4060
  br i1 %tobool158, label %if.then159, label %if.end160, !dbg !4062

if.then159:                                       ; preds = %lor.lhs.false157, %if.then153
  br label %failed, !dbg !4063

if.end160:                                        ; preds = %lor.lhs.false157
  %116 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4064
  %state161 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %116, i32 0, i32 0, !dbg !4065
  store i32 3, i32* %state161, align 8, !dbg !4066
  store i32 0, i32* %retval, align 4, !dbg !4067
  br label %return, !dbg !4067

if.end162:                                        ; preds = %sw.bb146
  %117 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !4068
  %cache_avail163 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %117, i32 0, i32 1, !dbg !4068
  %118 = load i32, i32* %cache_avail163, align 8, !dbg !4068
  %cmp164 = icmp sge i32 %118, 2, !dbg !4068
  br i1 %cmp164, label %if.end178, label %lor.lhs.false166, !dbg !4068

lor.lhs.false166:                                 ; preds = %if.end162
  %119 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !4070
  %120 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !4070
  %call167 = call i32 @lzh_br_fillup(%struct.lzh_stream* %119, %struct.lzh_br* %120), !dbg !4070
  %tobool168 = icmp ne i32 %call167, 0, !dbg !4070
  br i1 %tobool168, label %if.end178, label %lor.lhs.false169, !dbg !4070

lor.lhs.false169:                                 ; preds = %lor.lhs.false166
  %121 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !4072
  %cache_avail170 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %121, i32 0, i32 1, !dbg !4072
  %122 = load i32, i32* %cache_avail170, align 8, !dbg !4072
  %cmp171 = icmp sge i32 %122, 2, !dbg !4072
  br i1 %cmp171, label %if.end178, label %if.then173, !dbg !4074

if.then173:                                       ; preds = %lor.lhs.false169
  %123 = load i32, i32* %last.addr, align 4, !dbg !4075
  %tobool174 = icmp ne i32 %123, 0, !dbg !4075
  br i1 %tobool174, label %if.then175, label %if.end176, !dbg !4078

if.then175:                                       ; preds = %if.then173
  br label %failed, !dbg !4079

if.end176:                                        ; preds = %if.then173
  %124 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4080
  %state177 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %124, i32 0, i32 0, !dbg !4081
  store i32 3, i32* %state177, align 8, !dbg !4082
  store i32 0, i32* %retval, align 4, !dbg !4083
  br label %return, !dbg !4083

if.end178:                                        ; preds = %lor.lhs.false169, %lor.lhs.false166, %if.end162
  %125 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !4084
  %cache_buffer179 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %125, i32 0, i32 0, !dbg !4084
  %126 = load i64, i64* %cache_buffer179, align 8, !dbg !4084
  %127 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !4084
  %cache_avail180 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %127, i32 0, i32 1, !dbg !4084
  %128 = load i32, i32* %cache_avail180, align 8, !dbg !4084
  %sub181 = sub nsw i32 %128, 2, !dbg !4084
  %sh_prom182 = zext i32 %sub181 to i64, !dbg !4084
  %shr183 = lshr i64 %126, %sh_prom182, !dbg !4084
  %conv184 = trunc i64 %shr183 to i16, !dbg !4084
  %conv185 = zext i16 %conv184 to i32, !dbg !4084
  %129 = load i16, i16* getelementptr inbounds ([20 x i16], [20 x i16]* @cache_masks, i64 0, i64 2), align 4, !dbg !4084
  %conv186 = zext i16 %129 to i32, !dbg !4084
  %and187 = and i32 %conv185, %conv186, !dbg !4084
  store i32 %and187, i32* %c, align 4, !dbg !4085
  %130 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !4086
  %cache_avail188 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %130, i32 0, i32 1, !dbg !4086
  %131 = load i32, i32* %cache_avail188, align 8, !dbg !4086
  %sub189 = sub nsw i32 %131, 2, !dbg !4086
  store i32 %sub189, i32* %cache_avail188, align 8, !dbg !4086
  %132 = load i32, i32* %c, align 4, !dbg !4087
  %133 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4089
  %pt190 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %133, i32 0, i32 9, !dbg !4090
  %len_avail191 = getelementptr inbounds %struct.huffman, %struct.huffman* %pt190, i32 0, i32 1, !dbg !4091
  %134 = load i32, i32* %len_avail191, align 4, !dbg !4091
  %sub192 = sub nsw i32 %134, 3, !dbg !4092
  %cmp193 = icmp sgt i32 %132, %sub192, !dbg !4093
  br i1 %cmp193, label %if.then195, label %if.end196, !dbg !4094

if.then195:                                       ; preds = %if.end178
  br label %failed, !dbg !4095

if.end196:                                        ; preds = %if.end178
  store i32 3, i32* %i, align 4, !dbg !4096
  br label %for.cond197, !dbg !4098

for.cond197:                                      ; preds = %for.body, %if.end196
  %135 = load i32, i32* %c, align 4, !dbg !4099
  %dec = add nsw i32 %135, -1, !dbg !4099
  store i32 %dec, i32* %c, align 4, !dbg !4099
  %cmp198 = icmp sgt i32 %135, 0, !dbg !4102
  br i1 %cmp198, label %for.body, label %for.end, !dbg !4103

for.body:                                         ; preds = %for.cond197
  %136 = load i32, i32* %i, align 4, !dbg !4104
  %inc = add nsw i32 %136, 1, !dbg !4104
  store i32 %inc, i32* %i, align 4, !dbg !4104
  %idxprom200 = sext i32 %136 to i64, !dbg !4105
  %137 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4105
  %pt201 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %137, i32 0, i32 9, !dbg !4106
  %bitlen = getelementptr inbounds %struct.huffman, %struct.huffman* %pt201, i32 0, i32 4, !dbg !4107
  %138 = load i8*, i8** %bitlen, align 8, !dbg !4107
  %arrayidx202 = getelementptr inbounds i8, i8* %138, i64 %idxprom200, !dbg !4105
  store i8 0, i8* %arrayidx202, align 1, !dbg !4108
  br label %for.cond197, !dbg !4109

for.end:                                          ; preds = %for.cond197
  %139 = load i32, i32* %i, align 4, !dbg !4111
  %140 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4112
  %loop203 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %140, i32 0, i32 16, !dbg !4113
  store i32 %139, i32* %loop203, align 8, !dbg !4114
  br label %sw.bb204, !dbg !4112

sw.bb204:                                         ; preds = %for.cond, %for.end
  %141 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !4115
  %142 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4116
  %loop205 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %142, i32 0, i32 16, !dbg !4117
  %143 = load i32, i32* %loop205, align 8, !dbg !4117
  %144 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4118
  %pt206 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %144, i32 0, i32 9, !dbg !4119
  %len_avail207 = getelementptr inbounds %struct.huffman, %struct.huffman* %pt206, i32 0, i32 1, !dbg !4120
  %145 = load i32, i32* %len_avail207, align 4, !dbg !4120
  %call208 = call i32 @lzh_read_pt_bitlen(%struct.lzh_stream* %141, i32 %143, i32 %145), !dbg !4121
  %146 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4122
  %loop209 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %146, i32 0, i32 16, !dbg !4123
  store i32 %call208, i32* %loop209, align 8, !dbg !4124
  %147 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4125
  %loop210 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %147, i32 0, i32 16, !dbg !4127
  %148 = load i32, i32* %loop210, align 8, !dbg !4127
  %149 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4128
  %pt211 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %149, i32 0, i32 9, !dbg !4129
  %len_avail212 = getelementptr inbounds %struct.huffman, %struct.huffman* %pt211, i32 0, i32 1, !dbg !4130
  %150 = load i32, i32* %len_avail212, align 4, !dbg !4130
  %cmp213 = icmp slt i32 %148, %150, !dbg !4131
  br i1 %cmp213, label %if.then215, label %if.end224, !dbg !4132

if.then215:                                       ; preds = %sw.bb204
  %151 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4133
  %loop216 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %151, i32 0, i32 16, !dbg !4136
  %152 = load i32, i32* %loop216, align 8, !dbg !4136
  %cmp217 = icmp slt i32 %152, 0, !dbg !4137
  br i1 %cmp217, label %if.then221, label %lor.lhs.false219, !dbg !4138

lor.lhs.false219:                                 ; preds = %if.then215
  %153 = load i32, i32* %last.addr, align 4, !dbg !4139
  %tobool220 = icmp ne i32 %153, 0, !dbg !4139
  br i1 %tobool220, label %if.then221, label %if.end222, !dbg !4141

if.then221:                                       ; preds = %lor.lhs.false219, %if.then215
  br label %failed, !dbg !4142

if.end222:                                        ; preds = %lor.lhs.false219
  %154 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4143
  %state223 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %154, i32 0, i32 0, !dbg !4144
  store i32 4, i32* %state223, align 8, !dbg !4145
  store i32 0, i32* %retval, align 4, !dbg !4146
  br label %return, !dbg !4146

if.end224:                                        ; preds = %sw.bb204
  %155 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4147
  %pt225 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %155, i32 0, i32 9, !dbg !4149
  %call226 = call i32 @lzh_make_huffman_table(%struct.huffman* %pt225), !dbg !4150
  %tobool227 = icmp ne i32 %call226, 0, !dbg !4150
  br i1 %tobool227, label %if.end229, label %if.then228, !dbg !4151

if.then228:                                       ; preds = %if.end224
  br label %failed, !dbg !4152

if.end229:                                        ; preds = %if.end224
  %156 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4153
  %reading_position230 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %156, i32 0, i32 15, !dbg !4155
  %157 = load i32, i32* %reading_position230, align 4, !dbg !4155
  %tobool231 = icmp ne i32 %157, 0, !dbg !4153
  br i1 %tobool231, label %if.then232, label %if.end234, !dbg !4156

if.then232:                                       ; preds = %if.end229
  %158 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4157
  %state233 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %158, i32 0, i32 0, !dbg !4159
  store i32 9, i32* %state233, align 8, !dbg !4160
  br label %sw.epilog, !dbg !4161

if.end234:                                        ; preds = %if.end229
  br label %sw.bb235, !dbg !4162

sw.bb235:                                         ; preds = %for.cond, %if.end234
  %159 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !4164
  %cache_avail236 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %159, i32 0, i32 1, !dbg !4164
  %160 = load i32, i32* %cache_avail236, align 8, !dbg !4164
  %161 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4164
  %lt = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %161, i32 0, i32 8, !dbg !4164
  %len_bits237 = getelementptr inbounds %struct.huffman, %struct.huffman* %lt, i32 0, i32 2, !dbg !4164
  %162 = load i32, i32* %len_bits237, align 8, !dbg !4164
  %cmp238 = icmp sge i32 %160, %162, !dbg !4164
  br i1 %cmp238, label %if.end254, label %lor.lhs.false240, !dbg !4164

lor.lhs.false240:                                 ; preds = %sw.bb235
  %163 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !4166
  %164 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !4166
  %call241 = call i32 @lzh_br_fillup(%struct.lzh_stream* %163, %struct.lzh_br* %164), !dbg !4166
  %tobool242 = icmp ne i32 %call241, 0, !dbg !4166
  br i1 %tobool242, label %if.end254, label %lor.lhs.false243, !dbg !4166

lor.lhs.false243:                                 ; preds = %lor.lhs.false240
  %165 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !4168
  %cache_avail244 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %165, i32 0, i32 1, !dbg !4168
  %166 = load i32, i32* %cache_avail244, align 8, !dbg !4168
  %167 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4168
  %lt245 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %167, i32 0, i32 8, !dbg !4168
  %len_bits246 = getelementptr inbounds %struct.huffman, %struct.huffman* %lt245, i32 0, i32 2, !dbg !4168
  %168 = load i32, i32* %len_bits246, align 8, !dbg !4168
  %cmp247 = icmp sge i32 %166, %168, !dbg !4168
  br i1 %cmp247, label %if.end254, label %if.then249, !dbg !4170

if.then249:                                       ; preds = %lor.lhs.false243
  %169 = load i32, i32* %last.addr, align 4, !dbg !4171
  %tobool250 = icmp ne i32 %169, 0, !dbg !4171
  br i1 %tobool250, label %if.then251, label %if.end252, !dbg !4174

if.then251:                                       ; preds = %if.then249
  br label %failed, !dbg !4175

if.end252:                                        ; preds = %if.then249
  %170 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4176
  %state253 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %170, i32 0, i32 0, !dbg !4177
  store i32 5, i32* %state253, align 8, !dbg !4178
  store i32 0, i32* %retval, align 4, !dbg !4179
  br label %return, !dbg !4179

if.end254:                                        ; preds = %lor.lhs.false243, %lor.lhs.false240, %sw.bb235
  %171 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !4180
  %cache_buffer255 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %171, i32 0, i32 0, !dbg !4180
  %172 = load i64, i64* %cache_buffer255, align 8, !dbg !4180
  %173 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !4180
  %cache_avail256 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %173, i32 0, i32 1, !dbg !4180
  %174 = load i32, i32* %cache_avail256, align 8, !dbg !4180
  %175 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4180
  %lt257 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %175, i32 0, i32 8, !dbg !4180
  %len_bits258 = getelementptr inbounds %struct.huffman, %struct.huffman* %lt257, i32 0, i32 2, !dbg !4180
  %176 = load i32, i32* %len_bits258, align 8, !dbg !4180
  %sub259 = sub nsw i32 %174, %176, !dbg !4180
  %sh_prom260 = zext i32 %sub259 to i64, !dbg !4180
  %shr261 = lshr i64 %172, %sh_prom260, !dbg !4180
  %conv262 = trunc i64 %shr261 to i16, !dbg !4180
  %conv263 = zext i16 %conv262 to i32, !dbg !4180
  %177 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4180
  %lt264 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %177, i32 0, i32 8, !dbg !4180
  %len_bits265 = getelementptr inbounds %struct.huffman, %struct.huffman* %lt264, i32 0, i32 2, !dbg !4180
  %178 = load i32, i32* %len_bits265, align 8, !dbg !4180
  %idxprom266 = sext i32 %178 to i64, !dbg !4180
  %arrayidx267 = getelementptr inbounds [20 x i16], [20 x i16]* @cache_masks, i64 0, i64 %idxprom266, !dbg !4180
  %179 = load i16, i16* %arrayidx267, align 2, !dbg !4180
  %conv268 = zext i16 %179 to i32, !dbg !4180
  %and269 = and i32 %conv263, %conv268, !dbg !4180
  %180 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4181
  %lt270 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %180, i32 0, i32 8, !dbg !4182
  %len_avail271 = getelementptr inbounds %struct.huffman, %struct.huffman* %lt270, i32 0, i32 1, !dbg !4183
  store i32 %and269, i32* %len_avail271, align 4, !dbg !4184
  %181 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4185
  %lt272 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %181, i32 0, i32 8, !dbg !4185
  %len_bits273 = getelementptr inbounds %struct.huffman, %struct.huffman* %lt272, i32 0, i32 2, !dbg !4185
  %182 = load i32, i32* %len_bits273, align 8, !dbg !4185
  %183 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !4185
  %cache_avail274 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %183, i32 0, i32 1, !dbg !4185
  %184 = load i32, i32* %cache_avail274, align 8, !dbg !4185
  %sub275 = sub nsw i32 %184, %182, !dbg !4185
  store i32 %sub275, i32* %cache_avail274, align 8, !dbg !4185
  br label %sw.bb276, !dbg !4185

sw.bb276:                                         ; preds = %for.cond, %if.end254
  %185 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4186
  %lt277 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %185, i32 0, i32 8, !dbg !4188
  %len_avail278 = getelementptr inbounds %struct.huffman, %struct.huffman* %lt277, i32 0, i32 1, !dbg !4189
  %186 = load i32, i32* %len_avail278, align 4, !dbg !4189
  %cmp279 = icmp eq i32 %186, 0, !dbg !4190
  br i1 %cmp279, label %if.then281, label %if.else328, !dbg !4191

if.then281:                                       ; preds = %sw.bb276
  %187 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !4192
  %cache_avail282 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %187, i32 0, i32 1, !dbg !4192
  %188 = load i32, i32* %cache_avail282, align 8, !dbg !4192
  %189 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4192
  %lt283 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %189, i32 0, i32 8, !dbg !4192
  %len_bits284 = getelementptr inbounds %struct.huffman, %struct.huffman* %lt283, i32 0, i32 2, !dbg !4192
  %190 = load i32, i32* %len_bits284, align 8, !dbg !4192
  %cmp285 = icmp sge i32 %188, %190, !dbg !4192
  br i1 %cmp285, label %if.end301, label %lor.lhs.false287, !dbg !4192

lor.lhs.false287:                                 ; preds = %if.then281
  %191 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !4195
  %192 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !4195
  %call288 = call i32 @lzh_br_fillup(%struct.lzh_stream* %191, %struct.lzh_br* %192), !dbg !4195
  %tobool289 = icmp ne i32 %call288, 0, !dbg !4195
  br i1 %tobool289, label %if.end301, label %lor.lhs.false290, !dbg !4195

lor.lhs.false290:                                 ; preds = %lor.lhs.false287
  %193 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !4197
  %cache_avail291 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %193, i32 0, i32 1, !dbg !4197
  %194 = load i32, i32* %cache_avail291, align 8, !dbg !4197
  %195 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4197
  %lt292 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %195, i32 0, i32 8, !dbg !4197
  %len_bits293 = getelementptr inbounds %struct.huffman, %struct.huffman* %lt292, i32 0, i32 2, !dbg !4197
  %196 = load i32, i32* %len_bits293, align 8, !dbg !4197
  %cmp294 = icmp sge i32 %194, %196, !dbg !4197
  br i1 %cmp294, label %if.end301, label %if.then296, !dbg !4199

if.then296:                                       ; preds = %lor.lhs.false290
  %197 = load i32, i32* %last.addr, align 4, !dbg !4200
  %tobool297 = icmp ne i32 %197, 0, !dbg !4200
  br i1 %tobool297, label %if.then298, label %if.end299, !dbg !4203

if.then298:                                       ; preds = %if.then296
  br label %failed, !dbg !4204

if.end299:                                        ; preds = %if.then296
  %198 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4205
  %state300 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %198, i32 0, i32 0, !dbg !4206
  store i32 6, i32* %state300, align 8, !dbg !4207
  store i32 0, i32* %retval, align 4, !dbg !4208
  br label %return, !dbg !4208

if.end301:                                        ; preds = %lor.lhs.false290, %lor.lhs.false287, %if.then281
  %199 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4209
  %lt302 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %199, i32 0, i32 8, !dbg !4211
  %200 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !4212
  %cache_buffer303 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %200, i32 0, i32 0, !dbg !4212
  %201 = load i64, i64* %cache_buffer303, align 8, !dbg !4212
  %202 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !4212
  %cache_avail304 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %202, i32 0, i32 1, !dbg !4212
  %203 = load i32, i32* %cache_avail304, align 8, !dbg !4212
  %204 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4212
  %lt305 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %204, i32 0, i32 8, !dbg !4212
  %len_bits306 = getelementptr inbounds %struct.huffman, %struct.huffman* %lt305, i32 0, i32 2, !dbg !4212
  %205 = load i32, i32* %len_bits306, align 8, !dbg !4212
  %sub307 = sub nsw i32 %203, %205, !dbg !4212
  %sh_prom308 = zext i32 %sub307 to i64, !dbg !4212
  %shr309 = lshr i64 %201, %sh_prom308, !dbg !4212
  %conv310 = trunc i64 %shr309 to i16, !dbg !4212
  %conv311 = zext i16 %conv310 to i32, !dbg !4212
  %206 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4212
  %lt312 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %206, i32 0, i32 8, !dbg !4212
  %len_bits313 = getelementptr inbounds %struct.huffman, %struct.huffman* %lt312, i32 0, i32 2, !dbg !4212
  %207 = load i32, i32* %len_bits313, align 8, !dbg !4212
  %idxprom314 = sext i32 %207 to i64, !dbg !4212
  %arrayidx315 = getelementptr inbounds [20 x i16], [20 x i16]* @cache_masks, i64 0, i64 %idxprom314, !dbg !4212
  %208 = load i16, i16* %arrayidx315, align 2, !dbg !4212
  %conv316 = zext i16 %208 to i32, !dbg !4212
  %and317 = and i32 %conv311, %conv316, !dbg !4212
  %conv318 = trunc i32 %and317 to i16, !dbg !4212
  %call319 = call i32 @lzh_make_fake_table(%struct.huffman* %lt302, i16 zeroext %conv318), !dbg !4213
  %tobool320 = icmp ne i32 %call319, 0, !dbg !4213
  br i1 %tobool320, label %if.end322, label %if.then321, !dbg !4214

if.then321:                                       ; preds = %if.end301
  br label %failed, !dbg !4215

if.end322:                                        ; preds = %if.end301
  %209 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4216
  %lt323 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %209, i32 0, i32 8, !dbg !4216
  %len_bits324 = getelementptr inbounds %struct.huffman, %struct.huffman* %lt323, i32 0, i32 2, !dbg !4216
  %210 = load i32, i32* %len_bits324, align 8, !dbg !4216
  %211 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !4216
  %cache_avail325 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %211, i32 0, i32 1, !dbg !4216
  %212 = load i32, i32* %cache_avail325, align 8, !dbg !4216
  %sub326 = sub nsw i32 %212, %210, !dbg !4216
  store i32 %sub326, i32* %cache_avail325, align 8, !dbg !4216
  %213 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4217
  %state327 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %213, i32 0, i32 0, !dbg !4218
  store i32 8, i32* %state327, align 8, !dbg !4219
  br label %sw.epilog, !dbg !4220

if.else328:                                       ; preds = %sw.bb276
  %214 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4221
  %lt329 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %214, i32 0, i32 8, !dbg !4223
  %len_avail330 = getelementptr inbounds %struct.huffman, %struct.huffman* %lt329, i32 0, i32 1, !dbg !4224
  %215 = load i32, i32* %len_avail330, align 4, !dbg !4224
  %216 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4225
  %lt331 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %216, i32 0, i32 8, !dbg !4226
  %len_size332 = getelementptr inbounds %struct.huffman, %struct.huffman* %lt331, i32 0, i32 0, !dbg !4227
  %217 = load i32, i32* %len_size332, align 8, !dbg !4227
  %cmp333 = icmp sgt i32 %215, %217, !dbg !4228
  br i1 %cmp333, label %if.then335, label %if.end336, !dbg !4229

if.then335:                                       ; preds = %if.else328
  br label %failed, !dbg !4230

if.end336:                                        ; preds = %if.else328
  br label %if.end337

if.end337:                                        ; preds = %if.end336
  %218 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4231
  %loop338 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %218, i32 0, i32 16, !dbg !4232
  store i32 0, i32* %loop338, align 8, !dbg !4233
  %219 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4234
  %lt339 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %219, i32 0, i32 8, !dbg !4235
  %freq340 = getelementptr inbounds %struct.huffman, %struct.huffman* %lt339, i32 0, i32 3, !dbg !4236
  %arraydecay341 = getelementptr inbounds [17 x i32], [17 x i32]* %freq340, i32 0, i32 0, !dbg !4237
  %220 = bitcast i32* %arraydecay341 to i8*, !dbg !4237
  call void @llvm.memset.p0i8.i64(i8* %220, i8 0, i64 68, i32 4, i1 false), !dbg !4237
  br label %sw.bb342, !dbg !4237

sw.bb342:                                         ; preds = %for.cond, %if.end337
  %221 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4238
  %loop343 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %221, i32 0, i32 16, !dbg !4239
  %222 = load i32, i32* %loop343, align 8, !dbg !4239
  store i32 %222, i32* %i, align 4, !dbg !4240
  br label %while.cond, !dbg !4241

while.cond:                                       ; preds = %if.end492, %sw.bb342
  %223 = load i32, i32* %i, align 4, !dbg !4242
  %224 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4243
  %lt344 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %224, i32 0, i32 8, !dbg !4244
  %len_avail345 = getelementptr inbounds %struct.huffman, %struct.huffman* %lt344, i32 0, i32 1, !dbg !4245
  %225 = load i32, i32* %len_avail345, align 4, !dbg !4245
  %cmp346 = icmp slt i32 %223, %225, !dbg !4246
  br i1 %cmp346, label %while.body, label %while.end, !dbg !4247

while.body:                                       ; preds = %while.cond
  %226 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !4248
  %cache_avail348 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %226, i32 0, i32 1, !dbg !4248
  %227 = load i32, i32* %cache_avail348, align 8, !dbg !4248
  %228 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4248
  %pt349 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %228, i32 0, i32 9, !dbg !4248
  %max_bits = getelementptr inbounds %struct.huffman, %struct.huffman* %pt349, i32 0, i32 5, !dbg !4248
  %229 = load i32, i32* %max_bits, align 8, !dbg !4248
  %cmp350 = icmp sge i32 %227, %229, !dbg !4248
  br i1 %cmp350, label %if.end367, label %lor.lhs.false352, !dbg !4248

lor.lhs.false352:                                 ; preds = %while.body
  %230 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !4251
  %231 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !4251
  %call353 = call i32 @lzh_br_fillup(%struct.lzh_stream* %230, %struct.lzh_br* %231), !dbg !4251
  %tobool354 = icmp ne i32 %call353, 0, !dbg !4251
  br i1 %tobool354, label %if.end367, label %lor.lhs.false355, !dbg !4251

lor.lhs.false355:                                 ; preds = %lor.lhs.false352
  %232 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !4253
  %cache_avail356 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %232, i32 0, i32 1, !dbg !4253
  %233 = load i32, i32* %cache_avail356, align 8, !dbg !4253
  %234 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4253
  %pt357 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %234, i32 0, i32 9, !dbg !4253
  %max_bits358 = getelementptr inbounds %struct.huffman, %struct.huffman* %pt357, i32 0, i32 5, !dbg !4253
  %235 = load i32, i32* %max_bits358, align 8, !dbg !4253
  %cmp359 = icmp sge i32 %233, %235, !dbg !4253
  br i1 %cmp359, label %if.end367, label %if.then361, !dbg !4255

if.then361:                                       ; preds = %lor.lhs.false355
  %236 = load i32, i32* %last.addr, align 4, !dbg !4256
  %tobool362 = icmp ne i32 %236, 0, !dbg !4256
  br i1 %tobool362, label %if.then363, label %if.end364, !dbg !4259

if.then363:                                       ; preds = %if.then361
  br label %failed, !dbg !4260

if.end364:                                        ; preds = %if.then361
  %237 = load i32, i32* %i, align 4, !dbg !4261
  %238 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4262
  %loop365 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %238, i32 0, i32 16, !dbg !4263
  store i32 %237, i32* %loop365, align 8, !dbg !4264
  %239 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4265
  %state366 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %239, i32 0, i32 0, !dbg !4266
  store i32 7, i32* %state366, align 8, !dbg !4267
  store i32 0, i32* %retval, align 4, !dbg !4268
  br label %return, !dbg !4268

if.end367:                                        ; preds = %lor.lhs.false355, %lor.lhs.false352, %while.body
  %240 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !4269
  %cache_buffer368 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %240, i32 0, i32 0, !dbg !4269
  %241 = load i64, i64* %cache_buffer368, align 8, !dbg !4269
  %242 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !4269
  %cache_avail369 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %242, i32 0, i32 1, !dbg !4269
  %243 = load i32, i32* %cache_avail369, align 8, !dbg !4269
  %244 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4269
  %pt370 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %244, i32 0, i32 9, !dbg !4269
  %max_bits371 = getelementptr inbounds %struct.huffman, %struct.huffman* %pt370, i32 0, i32 5, !dbg !4269
  %245 = load i32, i32* %max_bits371, align 8, !dbg !4269
  %sub372 = sub nsw i32 %243, %245, !dbg !4269
  %sh_prom373 = zext i32 %sub372 to i64, !dbg !4269
  %shr374 = lshr i64 %241, %sh_prom373, !dbg !4269
  %conv375 = trunc i64 %shr374 to i16, !dbg !4269
  %conv376 = zext i16 %conv375 to i32, !dbg !4269
  %246 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4269
  %pt377 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %246, i32 0, i32 9, !dbg !4269
  %max_bits378 = getelementptr inbounds %struct.huffman, %struct.huffman* %pt377, i32 0, i32 5, !dbg !4269
  %247 = load i32, i32* %max_bits378, align 8, !dbg !4269
  %idxprom379 = sext i32 %247 to i64, !dbg !4269
  %arrayidx380 = getelementptr inbounds [20 x i16], [20 x i16]* @cache_masks, i64 0, i64 %idxprom379, !dbg !4269
  %248 = load i16, i16* %arrayidx380, align 2, !dbg !4269
  %conv381 = zext i16 %248 to i32, !dbg !4269
  %and382 = and i32 %conv376, %conv381, !dbg !4269
  store i32 %and382, i32* %rbits, align 4, !dbg !4270
  %249 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4271
  %pt383 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %249, i32 0, i32 9, !dbg !4272
  %250 = load i32, i32* %rbits, align 4, !dbg !4273
  %call384 = call i32 @lzh_decode_huffman(%struct.huffman* %pt383, i32 %250), !dbg !4274
  store i32 %call384, i32* %c, align 4, !dbg !4275
  %251 = load i32, i32* %c, align 4, !dbg !4276
  %cmp385 = icmp sgt i32 %251, 2, !dbg !4278
  br i1 %cmp385, label %if.then387, label %if.else407, !dbg !4279

if.then387:                                       ; preds = %if.end367
  %252 = load i32, i32* %c, align 4, !dbg !4280
  %idxprom388 = sext i32 %252 to i64, !dbg !4280
  %253 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4280
  %pt389 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %253, i32 0, i32 9, !dbg !4280
  %bitlen390 = getelementptr inbounds %struct.huffman, %struct.huffman* %pt389, i32 0, i32 4, !dbg !4280
  %254 = load i8*, i8** %bitlen390, align 8, !dbg !4280
  %arrayidx391 = getelementptr inbounds i8, i8* %254, i64 %idxprom388, !dbg !4280
  %255 = load i8, i8* %arrayidx391, align 1, !dbg !4280
  %conv392 = zext i8 %255 to i32, !dbg !4280
  %256 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !4280
  %cache_avail393 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %256, i32 0, i32 1, !dbg !4280
  %257 = load i32, i32* %cache_avail393, align 8, !dbg !4280
  %sub394 = sub nsw i32 %257, %conv392, !dbg !4280
  store i32 %sub394, i32* %cache_avail393, align 8, !dbg !4280
  %258 = load i32, i32* %c, align 4, !dbg !4282
  %sub395 = sub nsw i32 %258, 2, !dbg !4282
  store i32 %sub395, i32* %c, align 4, !dbg !4282
  %259 = load i32, i32* %c, align 4, !dbg !4283
  %idxprom396 = sext i32 %259 to i64, !dbg !4284
  %260 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4284
  %lt397 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %260, i32 0, i32 8, !dbg !4285
  %freq398 = getelementptr inbounds %struct.huffman, %struct.huffman* %lt397, i32 0, i32 3, !dbg !4286
  %arrayidx399 = getelementptr inbounds [17 x i32], [17 x i32]* %freq398, i64 0, i64 %idxprom396, !dbg !4284
  %261 = load i32, i32* %arrayidx399, align 4, !dbg !4287
  %inc400 = add nsw i32 %261, 1, !dbg !4287
  store i32 %inc400, i32* %arrayidx399, align 4, !dbg !4287
  %262 = load i32, i32* %c, align 4, !dbg !4288
  %conv401 = trunc i32 %262 to i8, !dbg !4288
  %263 = load i32, i32* %i, align 4, !dbg !4289
  %inc402 = add nsw i32 %263, 1, !dbg !4289
  store i32 %inc402, i32* %i, align 4, !dbg !4289
  %idxprom403 = sext i32 %263 to i64, !dbg !4290
  %264 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4290
  %lt404 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %264, i32 0, i32 8, !dbg !4291
  %bitlen405 = getelementptr inbounds %struct.huffman, %struct.huffman* %lt404, i32 0, i32 4, !dbg !4292
  %265 = load i8*, i8** %bitlen405, align 8, !dbg !4292
  %arrayidx406 = getelementptr inbounds i8, i8* %265, i64 %idxprom403, !dbg !4290
  store i8 %conv401, i8* %arrayidx406, align 1, !dbg !4293
  br label %if.end492, !dbg !4294

if.else407:                                       ; preds = %if.end367
  %266 = load i32, i32* %c, align 4, !dbg !4295
  %cmp408 = icmp eq i32 %266, 0, !dbg !4298
  br i1 %cmp408, label %if.then410, label %if.else423, !dbg !4295

if.then410:                                       ; preds = %if.else407
  %267 = load i32, i32* %c, align 4, !dbg !4299
  %idxprom411 = sext i32 %267 to i64, !dbg !4299
  %268 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4299
  %pt412 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %268, i32 0, i32 9, !dbg !4299
  %bitlen413 = getelementptr inbounds %struct.huffman, %struct.huffman* %pt412, i32 0, i32 4, !dbg !4299
  %269 = load i8*, i8** %bitlen413, align 8, !dbg !4299
  %arrayidx414 = getelementptr inbounds i8, i8* %269, i64 %idxprom411, !dbg !4299
  %270 = load i8, i8* %arrayidx414, align 1, !dbg !4299
  %conv415 = zext i8 %270 to i32, !dbg !4299
  %271 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !4299
  %cache_avail416 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %271, i32 0, i32 1, !dbg !4299
  %272 = load i32, i32* %cache_avail416, align 8, !dbg !4299
  %sub417 = sub nsw i32 %272, %conv415, !dbg !4299
  store i32 %sub417, i32* %cache_avail416, align 8, !dbg !4299
  %273 = load i32, i32* %i, align 4, !dbg !4301
  %inc418 = add nsw i32 %273, 1, !dbg !4301
  store i32 %inc418, i32* %i, align 4, !dbg !4301
  %idxprom419 = sext i32 %273 to i64, !dbg !4302
  %274 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4302
  %lt420 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %274, i32 0, i32 8, !dbg !4303
  %bitlen421 = getelementptr inbounds %struct.huffman, %struct.huffman* %lt420, i32 0, i32 4, !dbg !4304
  %275 = load i8*, i8** %bitlen421, align 8, !dbg !4304
  %arrayidx422 = getelementptr inbounds i8, i8* %275, i64 %idxprom419, !dbg !4302
  store i8 0, i8* %arrayidx422, align 1, !dbg !4305
  br label %if.end491, !dbg !4306

if.else423:                                       ; preds = %if.else407
  call void @llvm.dbg.declare(metadata i32* %n, metadata !4307, metadata !548), !dbg !4309
  %276 = load i32, i32* %c, align 4, !dbg !4310
  %cmp424 = icmp eq i32 %276, 1, !dbg !4311
  %cond = select i1 %cmp424, i32 4, i32 9, !dbg !4312
  store i32 %cond, i32* %n, align 4, !dbg !4309
  %277 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !4313
  %cache_avail426 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %277, i32 0, i32 1, !dbg !4313
  %278 = load i32, i32* %cache_avail426, align 8, !dbg !4313
  %279 = load i32, i32* %c, align 4, !dbg !4313
  %idxprom427 = sext i32 %279 to i64, !dbg !4313
  %280 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4313
  %pt428 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %280, i32 0, i32 9, !dbg !4313
  %bitlen429 = getelementptr inbounds %struct.huffman, %struct.huffman* %pt428, i32 0, i32 4, !dbg !4313
  %281 = load i8*, i8** %bitlen429, align 8, !dbg !4313
  %arrayidx430 = getelementptr inbounds i8, i8* %281, i64 %idxprom427, !dbg !4313
  %282 = load i8, i8* %arrayidx430, align 1, !dbg !4313
  %conv431 = zext i8 %282 to i32, !dbg !4313
  %283 = load i32, i32* %n, align 4, !dbg !4313
  %add = add nsw i32 %conv431, %283, !dbg !4313
  %cmp432 = icmp sge i32 %278, %add, !dbg !4313
  br i1 %cmp432, label %if.end453, label %lor.lhs.false434, !dbg !4313

lor.lhs.false434:                                 ; preds = %if.else423
  %284 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !4315
  %285 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !4315
  %call435 = call i32 @lzh_br_fillup(%struct.lzh_stream* %284, %struct.lzh_br* %285), !dbg !4315
  %tobool436 = icmp ne i32 %call435, 0, !dbg !4315
  br i1 %tobool436, label %if.end453, label %lor.lhs.false437, !dbg !4315

lor.lhs.false437:                                 ; preds = %lor.lhs.false434
  %286 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !4317
  %cache_avail438 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %286, i32 0, i32 1, !dbg !4317
  %287 = load i32, i32* %cache_avail438, align 8, !dbg !4317
  %288 = load i32, i32* %c, align 4, !dbg !4317
  %idxprom439 = sext i32 %288 to i64, !dbg !4317
  %289 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4317
  %pt440 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %289, i32 0, i32 9, !dbg !4317
  %bitlen441 = getelementptr inbounds %struct.huffman, %struct.huffman* %pt440, i32 0, i32 4, !dbg !4317
  %290 = load i8*, i8** %bitlen441, align 8, !dbg !4317
  %arrayidx442 = getelementptr inbounds i8, i8* %290, i64 %idxprom439, !dbg !4317
  %291 = load i8, i8* %arrayidx442, align 1, !dbg !4317
  %conv443 = zext i8 %291 to i32, !dbg !4317
  %292 = load i32, i32* %n, align 4, !dbg !4317
  %add444 = add nsw i32 %conv443, %292, !dbg !4317
  %cmp445 = icmp sge i32 %287, %add444, !dbg !4317
  br i1 %cmp445, label %if.end453, label %if.then447, !dbg !4319

if.then447:                                       ; preds = %lor.lhs.false437
  %293 = load i32, i32* %last.addr, align 4, !dbg !4320
  %tobool448 = icmp ne i32 %293, 0, !dbg !4320
  br i1 %tobool448, label %if.then449, label %if.end450, !dbg !4323

if.then449:                                       ; preds = %if.then447
  br label %failed, !dbg !4324

if.end450:                                        ; preds = %if.then447
  %294 = load i32, i32* %i, align 4, !dbg !4325
  %295 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4326
  %loop451 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %295, i32 0, i32 16, !dbg !4327
  store i32 %294, i32* %loop451, align 8, !dbg !4328
  %296 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4329
  %state452 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %296, i32 0, i32 0, !dbg !4330
  store i32 7, i32* %state452, align 8, !dbg !4331
  store i32 0, i32* %retval, align 4, !dbg !4332
  br label %return, !dbg !4332

if.end453:                                        ; preds = %lor.lhs.false437, %lor.lhs.false434, %if.else423
  %297 = load i32, i32* %c, align 4, !dbg !4333
  %idxprom454 = sext i32 %297 to i64, !dbg !4333
  %298 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4333
  %pt455 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %298, i32 0, i32 9, !dbg !4333
  %bitlen456 = getelementptr inbounds %struct.huffman, %struct.huffman* %pt455, i32 0, i32 4, !dbg !4333
  %299 = load i8*, i8** %bitlen456, align 8, !dbg !4333
  %arrayidx457 = getelementptr inbounds i8, i8* %299, i64 %idxprom454, !dbg !4333
  %300 = load i8, i8* %arrayidx457, align 1, !dbg !4333
  %conv458 = zext i8 %300 to i32, !dbg !4333
  %301 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !4333
  %cache_avail459 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %301, i32 0, i32 1, !dbg !4333
  %302 = load i32, i32* %cache_avail459, align 8, !dbg !4333
  %sub460 = sub nsw i32 %302, %conv458, !dbg !4333
  store i32 %sub460, i32* %cache_avail459, align 8, !dbg !4333
  %303 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !4334
  %cache_buffer461 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %303, i32 0, i32 0, !dbg !4334
  %304 = load i64, i64* %cache_buffer461, align 8, !dbg !4334
  %305 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !4334
  %cache_avail462 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %305, i32 0, i32 1, !dbg !4334
  %306 = load i32, i32* %cache_avail462, align 8, !dbg !4334
  %307 = load i32, i32* %n, align 4, !dbg !4334
  %sub463 = sub nsw i32 %306, %307, !dbg !4334
  %sh_prom464 = zext i32 %sub463 to i64, !dbg !4334
  %shr465 = lshr i64 %304, %sh_prom464, !dbg !4334
  %conv466 = trunc i64 %shr465 to i16, !dbg !4334
  %conv467 = zext i16 %conv466 to i32, !dbg !4334
  %308 = load i32, i32* %n, align 4, !dbg !4334
  %idxprom468 = sext i32 %308 to i64, !dbg !4334
  %arrayidx469 = getelementptr inbounds [20 x i16], [20 x i16]* @cache_masks, i64 0, i64 %idxprom468, !dbg !4334
  %309 = load i16, i16* %arrayidx469, align 2, !dbg !4334
  %conv470 = zext i16 %309 to i32, !dbg !4334
  %and471 = and i32 %conv467, %conv470, !dbg !4334
  store i32 %and471, i32* %c, align 4, !dbg !4335
  %310 = load i32, i32* %n, align 4, !dbg !4336
  %311 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !4336
  %cache_avail472 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %311, i32 0, i32 1, !dbg !4336
  %312 = load i32, i32* %cache_avail472, align 8, !dbg !4336
  %sub473 = sub nsw i32 %312, %310, !dbg !4336
  store i32 %sub473, i32* %cache_avail472, align 8, !dbg !4336
  %313 = load i32, i32* %n, align 4, !dbg !4337
  %cmp474 = icmp eq i32 %313, 4, !dbg !4338
  %cond476 = select i1 %cmp474, i32 3, i32 20, !dbg !4339
  %314 = load i32, i32* %c, align 4, !dbg !4340
  %add477 = add nsw i32 %314, %cond476, !dbg !4340
  store i32 %add477, i32* %c, align 4, !dbg !4340
  %315 = load i32, i32* %i, align 4, !dbg !4341
  %316 = load i32, i32* %c, align 4, !dbg !4343
  %add478 = add nsw i32 %315, %316, !dbg !4344
  %317 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4345
  %lt479 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %317, i32 0, i32 8, !dbg !4346
  %len_avail480 = getelementptr inbounds %struct.huffman, %struct.huffman* %lt479, i32 0, i32 1, !dbg !4347
  %318 = load i32, i32* %len_avail480, align 4, !dbg !4347
  %cmp481 = icmp sgt i32 %add478, %318, !dbg !4348
  br i1 %cmp481, label %if.then483, label %if.end484, !dbg !4349

if.then483:                                       ; preds = %if.end453
  br label %failed, !dbg !4350

if.end484:                                        ; preds = %if.end453
  %319 = load i32, i32* %i, align 4, !dbg !4351
  %idxprom485 = sext i32 %319 to i64, !dbg !4352
  %320 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4352
  %lt486 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %320, i32 0, i32 8, !dbg !4353
  %bitlen487 = getelementptr inbounds %struct.huffman, %struct.huffman* %lt486, i32 0, i32 4, !dbg !4354
  %321 = load i8*, i8** %bitlen487, align 8, !dbg !4354
  %arrayidx488 = getelementptr inbounds i8, i8* %321, i64 %idxprom485, !dbg !4352
  %322 = load i32, i32* %c, align 4, !dbg !4355
  %conv489 = sext i32 %322 to i64, !dbg !4355
  call void @llvm.memset.p0i8.i64(i8* %arrayidx488, i8 0, i64 %conv489, i32 1, i1 false), !dbg !4356
  %323 = load i32, i32* %c, align 4, !dbg !4357
  %324 = load i32, i32* %i, align 4, !dbg !4358
  %add490 = add nsw i32 %324, %323, !dbg !4358
  store i32 %add490, i32* %i, align 4, !dbg !4358
  br label %if.end491

if.end491:                                        ; preds = %if.end484, %if.then410
  br label %if.end492

if.end492:                                        ; preds = %if.end491, %if.then387
  br label %while.cond, !dbg !4359

while.end:                                        ; preds = %while.cond
  %325 = load i32, i32* %i, align 4, !dbg !4361
  %326 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4363
  %lt493 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %326, i32 0, i32 8, !dbg !4364
  %len_avail494 = getelementptr inbounds %struct.huffman, %struct.huffman* %lt493, i32 0, i32 1, !dbg !4365
  %327 = load i32, i32* %len_avail494, align 4, !dbg !4365
  %cmp495 = icmp sgt i32 %325, %327, !dbg !4366
  br i1 %cmp495, label %if.then501, label %lor.lhs.false497, !dbg !4367

lor.lhs.false497:                                 ; preds = %while.end
  %328 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4368
  %lt498 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %328, i32 0, i32 8, !dbg !4369
  %call499 = call i32 @lzh_make_huffman_table(%struct.huffman* %lt498), !dbg !4370
  %tobool500 = icmp ne i32 %call499, 0, !dbg !4370
  br i1 %tobool500, label %if.end502, label %if.then501, !dbg !4371

if.then501:                                       ; preds = %lor.lhs.false497, %while.end
  br label %failed, !dbg !4372

if.end502:                                        ; preds = %lor.lhs.false497
  br label %sw.bb503, !dbg !4373

sw.bb503:                                         ; preds = %for.cond, %if.end502
  %329 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4375
  %pos_pt_len_size504 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %329, i32 0, i32 11, !dbg !4376
  %330 = load i32, i32* %pos_pt_len_size504, align 4, !dbg !4376
  %331 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4377
  %pt505 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %331, i32 0, i32 9, !dbg !4378
  %len_size506 = getelementptr inbounds %struct.huffman, %struct.huffman* %pt505, i32 0, i32 0, !dbg !4379
  store i32 %330, i32* %len_size506, align 8, !dbg !4380
  %332 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4381
  %pos_pt_len_bits = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %332, i32 0, i32 12, !dbg !4382
  %333 = load i32, i32* %pos_pt_len_bits, align 8, !dbg !4382
  %334 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4383
  %pt507 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %334, i32 0, i32 9, !dbg !4384
  %len_bits508 = getelementptr inbounds %struct.huffman, %struct.huffman* %pt507, i32 0, i32 2, !dbg !4385
  store i32 %333, i32* %len_bits508, align 8, !dbg !4386
  %335 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4387
  %reading_position509 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %335, i32 0, i32 15, !dbg !4388
  store i32 1, i32* %reading_position509, align 4, !dbg !4389
  %336 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4390
  %state510 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %336, i32 0, i32 0, !dbg !4391
  store i32 1, i32* %state510, align 8, !dbg !4392
  br label %sw.epilog, !dbg !4393

sw.bb511:                                         ; preds = %for.cond
  store i32 100, i32* %retval, align 4, !dbg !4394
  br label %return, !dbg !4394

sw.epilog:                                        ; preds = %for.cond, %sw.bb503, %if.end322, %if.then232, %if.then143, %if.end122
  br label %for.cond, !dbg !4395

failed:                                           ; preds = %if.then501, %if.then483, %if.then449, %if.then363, %if.then335, %if.then321, %if.then298, %if.then251, %if.then228, %if.then221, %if.then195, %if.then175, %if.then159, %if.then130, %if.then111, %if.then88, %if.then44, %if.then22, %if.then7
  %337 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4397
  %error = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %337, i32 0, i32 17, !dbg !4398
  store i32 -25, i32* %error, align 4, !dbg !4399
  store i32 -25, i32* %retval, align 4, !dbg !4400
  br label %return, !dbg !4400

return:                                           ; preds = %failed, %sw.bb511, %if.end450, %if.end364, %if.end299, %if.end252, %if.end222, %if.end176, %if.end160, %if.end89, %if.end45, %if.end13, %if.then10, %if.then4
  %338 = load i32, i32* %retval, align 4, !dbg !4401
  ret i32 %338, !dbg !4401
}

; Function Attrs: nounwind uwtable
define internal i32 @lzh_decode_blocks(%struct.lzh_stream* %strm, i32 %last) #0 !dbg !507 {
entry:
  %retval = alloca i32, align 4
  %strm.addr = alloca %struct.lzh_stream*, align 8
  %last.addr = alloca i32, align 4
  %ds = alloca %struct.lzh_dec*, align 8
  %bre = alloca %struct.lzh_br, align 8
  %lt = alloca %struct.huffman*, align 8
  %pt = alloca %struct.huffman*, align 8
  %w_buff = alloca i8*, align 8
  %lt_bitlen = alloca i8*, align 8
  %pt_bitlen = alloca i8*, align 8
  %blocks_avail = alloca i32, align 4
  %c = alloca i32, align 4
  %copy_len = alloca i32, align 4
  %copy_pos = alloca i32, align 4
  %w_pos = alloca i32, align 4
  %w_mask = alloca i32, align 4
  %w_size = alloca i32, align 4
  %lt_max_bits = alloca i32, align 4
  %pt_max_bits = alloca i32, align 4
  %state = alloca i32, align 4
  %p = alloca i32, align 4
  %l = alloca i32, align 4
  %s = alloca i8*, align 8
  %d = alloca i8*, align 8
  %li = alloca i32, align 4
  store %struct.lzh_stream* %strm, %struct.lzh_stream** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzh_stream** %strm.addr, metadata !4402, metadata !548), !dbg !4403
  store i32 %last, i32* %last.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %last.addr, metadata !4404, metadata !548), !dbg !4405
  call void @llvm.dbg.declare(metadata %struct.lzh_dec** %ds, metadata !4406, metadata !548), !dbg !4407
  %0 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !4408
  %ds1 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %0, i32 0, i32 6, !dbg !4409
  %1 = load %struct.lzh_dec*, %struct.lzh_dec** %ds1, align 8, !dbg !4409
  store %struct.lzh_dec* %1, %struct.lzh_dec** %ds, align 8, !dbg !4407
  call void @llvm.dbg.declare(metadata %struct.lzh_br* %bre, metadata !4410, metadata !548), !dbg !4411
  %2 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4412
  %br = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %2, i32 0, i32 7, !dbg !4413
  %3 = bitcast %struct.lzh_br* %bre to i8*, !dbg !4413
  %4 = bitcast %struct.lzh_br* %br to i8*, !dbg !4413
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %3, i8* %4, i64 16, i32 8, i1 false), !dbg !4413
  call void @llvm.dbg.declare(metadata %struct.huffman** %lt, metadata !4414, metadata !548), !dbg !4415
  %5 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4416
  %lt2 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %5, i32 0, i32 8, !dbg !4417
  store %struct.huffman* %lt2, %struct.huffman** %lt, align 8, !dbg !4415
  call void @llvm.dbg.declare(metadata %struct.huffman** %pt, metadata !4418, metadata !548), !dbg !4419
  %6 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4420
  %pt3 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %6, i32 0, i32 9, !dbg !4421
  store %struct.huffman* %pt3, %struct.huffman** %pt, align 8, !dbg !4419
  call void @llvm.dbg.declare(metadata i8** %w_buff, metadata !4422, metadata !548), !dbg !4423
  %7 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4424
  %w_buff4 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %7, i32 0, i32 3, !dbg !4425
  %8 = load i8*, i8** %w_buff4, align 8, !dbg !4425
  store i8* %8, i8** %w_buff, align 8, !dbg !4423
  call void @llvm.dbg.declare(metadata i8** %lt_bitlen, metadata !4426, metadata !548), !dbg !4427
  %9 = load %struct.huffman*, %struct.huffman** %lt, align 8, !dbg !4428
  %bitlen = getelementptr inbounds %struct.huffman, %struct.huffman* %9, i32 0, i32 4, !dbg !4429
  %10 = load i8*, i8** %bitlen, align 8, !dbg !4429
  store i8* %10, i8** %lt_bitlen, align 8, !dbg !4427
  call void @llvm.dbg.declare(metadata i8** %pt_bitlen, metadata !4430, metadata !548), !dbg !4431
  %11 = load %struct.huffman*, %struct.huffman** %pt, align 8, !dbg !4432
  %bitlen5 = getelementptr inbounds %struct.huffman, %struct.huffman* %11, i32 0, i32 4, !dbg !4433
  %12 = load i8*, i8** %bitlen5, align 8, !dbg !4433
  store i8* %12, i8** %pt_bitlen, align 8, !dbg !4431
  call void @llvm.dbg.declare(metadata i32* %blocks_avail, metadata !4434, metadata !548), !dbg !4435
  %13 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4436
  %blocks_avail6 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %13, i32 0, i32 10, !dbg !4437
  %14 = load i32, i32* %blocks_avail6, align 8, !dbg !4437
  store i32 %14, i32* %blocks_avail, align 4, !dbg !4435
  call void @llvm.dbg.declare(metadata i32* %c, metadata !4438, metadata !548), !dbg !4439
  store i32 0, i32* %c, align 4, !dbg !4439
  call void @llvm.dbg.declare(metadata i32* %copy_len, metadata !4440, metadata !548), !dbg !4441
  %15 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4442
  %copy_len7 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %15, i32 0, i32 6, !dbg !4443
  %16 = load i32, i32* %copy_len7, align 8, !dbg !4443
  store i32 %16, i32* %copy_len, align 4, !dbg !4441
  call void @llvm.dbg.declare(metadata i32* %copy_pos, metadata !4444, metadata !548), !dbg !4445
  %17 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4446
  %copy_pos8 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %17, i32 0, i32 5, !dbg !4447
  %18 = load i32, i32* %copy_pos8, align 4, !dbg !4447
  store i32 %18, i32* %copy_pos, align 4, !dbg !4445
  call void @llvm.dbg.declare(metadata i32* %w_pos, metadata !4448, metadata !548), !dbg !4449
  %19 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4450
  %w_pos9 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %19, i32 0, i32 4, !dbg !4451
  %20 = load i32, i32* %w_pos9, align 8, !dbg !4451
  store i32 %20, i32* %w_pos, align 4, !dbg !4449
  call void @llvm.dbg.declare(metadata i32* %w_mask, metadata !4452, metadata !548), !dbg !4453
  %21 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4454
  %w_mask10 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %21, i32 0, i32 2, !dbg !4455
  %22 = load i32, i32* %w_mask10, align 8, !dbg !4455
  store i32 %22, i32* %w_mask, align 4, !dbg !4453
  call void @llvm.dbg.declare(metadata i32* %w_size, metadata !4456, metadata !548), !dbg !4457
  %23 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4458
  %w_size11 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %23, i32 0, i32 1, !dbg !4459
  %24 = load i32, i32* %w_size11, align 4, !dbg !4459
  store i32 %24, i32* %w_size, align 4, !dbg !4457
  call void @llvm.dbg.declare(metadata i32* %lt_max_bits, metadata !4460, metadata !548), !dbg !4461
  %25 = load %struct.huffman*, %struct.huffman** %lt, align 8, !dbg !4462
  %max_bits = getelementptr inbounds %struct.huffman, %struct.huffman* %25, i32 0, i32 5, !dbg !4463
  %26 = load i32, i32* %max_bits, align 8, !dbg !4463
  store i32 %26, i32* %lt_max_bits, align 4, !dbg !4461
  call void @llvm.dbg.declare(metadata i32* %pt_max_bits, metadata !4464, metadata !548), !dbg !4465
  %27 = load %struct.huffman*, %struct.huffman** %pt, align 8, !dbg !4466
  %max_bits12 = getelementptr inbounds %struct.huffman, %struct.huffman* %27, i32 0, i32 5, !dbg !4467
  %28 = load i32, i32* %max_bits12, align 8, !dbg !4467
  store i32 %28, i32* %pt_max_bits, align 4, !dbg !4465
  call void @llvm.dbg.declare(metadata i32* %state, metadata !4468, metadata !548), !dbg !4469
  %29 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4470
  %state13 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %29, i32 0, i32 0, !dbg !4471
  %30 = load i32, i32* %state13, align 8, !dbg !4471
  store i32 %30, i32* %state, align 4, !dbg !4469
  br label %for.cond, !dbg !4472

for.cond:                                         ; preds = %sw.epilog, %entry
  %31 = load i32, i32* %state, align 4, !dbg !4473
  switch i32 %31, label %sw.epilog [
    i32 9, label %sw.bb
    i32 10, label %sw.bb72
    i32 11, label %sw.bb129
    i32 12, label %sw.bb170
  ], !dbg !4477

sw.bb:                                            ; preds = %for.cond
  br label %for.cond14, !dbg !4478

for.cond14:                                       ; preds = %if.end70, %sw.bb
  %32 = load i32, i32* %blocks_avail, align 4, !dbg !4480
  %cmp = icmp eq i32 %32, 0, !dbg !4485
  br i1 %cmp, label %if.then, label %if.end, !dbg !4486

if.then:                                          ; preds = %for.cond14
  %33 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4487
  %state15 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %33, i32 0, i32 0, !dbg !4489
  store i32 0, i32* %state15, align 8, !dbg !4490
  %34 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4491
  %br16 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %34, i32 0, i32 7, !dbg !4492
  %35 = bitcast %struct.lzh_br* %br16 to i8*, !dbg !4493
  %36 = bitcast %struct.lzh_br* %bre to i8*, !dbg !4493
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %35, i8* %36, i64 16, i32 8, i1 false), !dbg !4493
  %37 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4494
  %blocks_avail17 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %37, i32 0, i32 10, !dbg !4495
  store i32 0, i32* %blocks_avail17, align 8, !dbg !4496
  %38 = load i32, i32* %w_pos, align 4, !dbg !4497
  %39 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4498
  %w_pos18 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %39, i32 0, i32 4, !dbg !4499
  store i32 %38, i32* %w_pos18, align 8, !dbg !4500
  %40 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4501
  %copy_pos19 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %40, i32 0, i32 5, !dbg !4502
  store i32 0, i32* %copy_pos19, align 4, !dbg !4503
  store i32 100, i32* %retval, align 4, !dbg !4504
  br label %return, !dbg !4504

if.end:                                           ; preds = %for.cond14
  %cache_avail = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %bre, i32 0, i32 1, !dbg !4505
  %41 = load i32, i32* %cache_avail, align 8, !dbg !4505
  %42 = load i32, i32* %lt_max_bits, align 4, !dbg !4505
  %cmp20 = icmp sge i32 %41, %42, !dbg !4505
  br i1 %cmp20, label %if.else, label %lor.lhs.false, !dbg !4505

lor.lhs.false:                                    ; preds = %if.end
  %43 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !4507
  %call = call i32 @lzh_br_fillup(%struct.lzh_stream* %43, %struct.lzh_br* %bre), !dbg !4507
  %tobool = icmp ne i32 %call, 0, !dbg !4507
  br i1 %tobool, label %if.else, label %lor.lhs.false21, !dbg !4507

lor.lhs.false21:                                  ; preds = %lor.lhs.false
  %cache_avail22 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %bre, i32 0, i32 1, !dbg !4509
  %44 = load i32, i32* %cache_avail22, align 8, !dbg !4509
  %45 = load i32, i32* %lt_max_bits, align 4, !dbg !4509
  %cmp23 = icmp sge i32 %44, %45, !dbg !4509
  br i1 %cmp23, label %if.else, label %if.then24, !dbg !4511

if.then24:                                        ; preds = %lor.lhs.false21
  %46 = load i32, i32* %last.addr, align 4, !dbg !4512
  %tobool25 = icmp ne i32 %46, 0, !dbg !4512
  br i1 %tobool25, label %if.end27, label %if.then26, !dbg !4515

if.then26:                                        ; preds = %if.then24
  br label %next_data, !dbg !4516

if.end27:                                         ; preds = %if.then24
  %47 = load %struct.huffman*, %struct.huffman** %lt, align 8, !dbg !4517
  %cache_buffer = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %bre, i32 0, i32 0, !dbg !4518
  %48 = load i64, i64* %cache_buffer, align 8, !dbg !4518
  %49 = load i32, i32* %lt_max_bits, align 4, !dbg !4518
  %cache_avail28 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %bre, i32 0, i32 1, !dbg !4518
  %50 = load i32, i32* %cache_avail28, align 8, !dbg !4518
  %sub = sub nsw i32 %49, %50, !dbg !4518
  %sh_prom = zext i32 %sub to i64, !dbg !4518
  %shl = shl i64 %48, %sh_prom, !dbg !4518
  %conv = trunc i64 %shl to i16, !dbg !4518
  %conv29 = zext i16 %conv to i32, !dbg !4518
  %51 = load i32, i32* %lt_max_bits, align 4, !dbg !4518
  %idxprom = sext i32 %51 to i64, !dbg !4518
  %arrayidx = getelementptr inbounds [20 x i16], [20 x i16]* @cache_masks, i64 0, i64 %idxprom, !dbg !4518
  %52 = load i16, i16* %arrayidx, align 2, !dbg !4518
  %conv30 = zext i16 %52 to i32, !dbg !4518
  %and = and i32 %conv29, %conv30, !dbg !4518
  %call31 = call i32 @lzh_decode_huffman(%struct.huffman* %47, i32 %and), !dbg !4519
  store i32 %call31, i32* %c, align 4, !dbg !4520
  %53 = load i32, i32* %c, align 4, !dbg !4521
  %idxprom32 = sext i32 %53 to i64, !dbg !4521
  %54 = load i8*, i8** %lt_bitlen, align 8, !dbg !4521
  %arrayidx33 = getelementptr inbounds i8, i8* %54, i64 %idxprom32, !dbg !4521
  %55 = load i8, i8* %arrayidx33, align 1, !dbg !4521
  %conv34 = zext i8 %55 to i32, !dbg !4521
  %cache_avail35 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %bre, i32 0, i32 1, !dbg !4521
  %56 = load i32, i32* %cache_avail35, align 8, !dbg !4521
  %sub36 = sub nsw i32 %56, %conv34, !dbg !4521
  store i32 %sub36, i32* %cache_avail35, align 8, !dbg !4521
  %cache_avail37 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %bre, i32 0, i32 1, !dbg !4522
  %57 = load i32, i32* %cache_avail37, align 8, !dbg !4522
  %cmp38 = icmp sge i32 %57, 0, !dbg !4522
  br i1 %cmp38, label %if.end41, label %if.then40, !dbg !4524

if.then40:                                        ; preds = %if.end27
  br label %failed, !dbg !4525

if.end41:                                         ; preds = %if.end27
  br label %if.end58, !dbg !4526

if.else:                                          ; preds = %lor.lhs.false21, %lor.lhs.false, %if.end
  %58 = load %struct.huffman*, %struct.huffman** %lt, align 8, !dbg !4527
  %cache_buffer42 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %bre, i32 0, i32 0, !dbg !4529
  %59 = load i64, i64* %cache_buffer42, align 8, !dbg !4529
  %cache_avail43 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %bre, i32 0, i32 1, !dbg !4529
  %60 = load i32, i32* %cache_avail43, align 8, !dbg !4529
  %61 = load i32, i32* %lt_max_bits, align 4, !dbg !4529
  %sub44 = sub nsw i32 %60, %61, !dbg !4529
  %sh_prom45 = zext i32 %sub44 to i64, !dbg !4529
  %shr = lshr i64 %59, %sh_prom45, !dbg !4529
  %conv46 = trunc i64 %shr to i16, !dbg !4529
  %conv47 = zext i16 %conv46 to i32, !dbg !4529
  %62 = load i32, i32* %lt_max_bits, align 4, !dbg !4529
  %idxprom48 = sext i32 %62 to i64, !dbg !4529
  %arrayidx49 = getelementptr inbounds [20 x i16], [20 x i16]* @cache_masks, i64 0, i64 %idxprom48, !dbg !4529
  %63 = load i16, i16* %arrayidx49, align 2, !dbg !4529
  %conv50 = zext i16 %63 to i32, !dbg !4529
  %and51 = and i32 %conv47, %conv50, !dbg !4529
  %call52 = call i32 @lzh_decode_huffman(%struct.huffman* %58, i32 %and51), !dbg !4530
  store i32 %call52, i32* %c, align 4, !dbg !4531
  %64 = load i32, i32* %c, align 4, !dbg !4532
  %idxprom53 = sext i32 %64 to i64, !dbg !4532
  %65 = load i8*, i8** %lt_bitlen, align 8, !dbg !4532
  %arrayidx54 = getelementptr inbounds i8, i8* %65, i64 %idxprom53, !dbg !4532
  %66 = load i8, i8* %arrayidx54, align 1, !dbg !4532
  %conv55 = zext i8 %66 to i32, !dbg !4532
  %cache_avail56 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %bre, i32 0, i32 1, !dbg !4532
  %67 = load i32, i32* %cache_avail56, align 8, !dbg !4532
  %sub57 = sub nsw i32 %67, %conv55, !dbg !4532
  store i32 %sub57, i32* %cache_avail56, align 8, !dbg !4532
  br label %if.end58

if.end58:                                         ; preds = %if.else, %if.end41
  %68 = load i32, i32* %blocks_avail, align 4, !dbg !4533
  %dec = add nsw i32 %68, -1, !dbg !4533
  store i32 %dec, i32* %blocks_avail, align 4, !dbg !4533
  %69 = load i32, i32* %c, align 4, !dbg !4534
  %cmp59 = icmp sgt i32 %69, 255, !dbg !4536
  br i1 %cmp59, label %if.then61, label %if.end62, !dbg !4537

if.then61:                                        ; preds = %if.end58
  br label %for.end, !dbg !4538

if.end62:                                         ; preds = %if.end58
  %70 = load i32, i32* %c, align 4, !dbg !4539
  %conv63 = trunc i32 %70 to i8, !dbg !4539
  %71 = load i32, i32* %w_pos, align 4, !dbg !4540
  %idxprom64 = sext i32 %71 to i64, !dbg !4541
  %72 = load i8*, i8** %w_buff, align 8, !dbg !4541
  %arrayidx65 = getelementptr inbounds i8, i8* %72, i64 %idxprom64, !dbg !4541
  store i8 %conv63, i8* %arrayidx65, align 1, !dbg !4542
  %73 = load i32, i32* %w_pos, align 4, !dbg !4543
  %inc = add nsw i32 %73, 1, !dbg !4543
  store i32 %inc, i32* %w_pos, align 4, !dbg !4543
  %74 = load i32, i32* %w_size, align 4, !dbg !4545
  %cmp66 = icmp sge i32 %inc, %74, !dbg !4546
  br i1 %cmp66, label %if.then68, label %if.end70, !dbg !4547

if.then68:                                        ; preds = %if.end62
  store i32 0, i32* %w_pos, align 4, !dbg !4548
  %75 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !4550
  %76 = load i32, i32* %w_size, align 4, !dbg !4551
  %conv69 = sext i32 %76 to i64, !dbg !4551
  call void @lzh_emit_window(%struct.lzh_stream* %75, i64 %conv69), !dbg !4552
  br label %next_data, !dbg !4553

if.end70:                                         ; preds = %if.end62
  br label %for.cond14, !dbg !4554

for.end:                                          ; preds = %if.then61
  %77 = load i32, i32* %c, align 4, !dbg !4556
  %sub71 = sub nsw i32 %77, 256, !dbg !4557
  %add = add nsw i32 %sub71, 3, !dbg !4558
  store i32 %add, i32* %copy_len, align 4, !dbg !4559
  br label %sw.bb72, !dbg !4560

sw.bb72:                                          ; preds = %for.cond, %for.end
  %cache_avail73 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %bre, i32 0, i32 1, !dbg !4561
  %78 = load i32, i32* %cache_avail73, align 8, !dbg !4561
  %79 = load i32, i32* %pt_max_bits, align 4, !dbg !4561
  %cmp74 = icmp sge i32 %78, %79, !dbg !4561
  br i1 %cmp74, label %if.else110, label %lor.lhs.false76, !dbg !4561

lor.lhs.false76:                                  ; preds = %sw.bb72
  %80 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !4563
  %call77 = call i32 @lzh_br_fillup(%struct.lzh_stream* %80, %struct.lzh_br* %bre), !dbg !4563
  %tobool78 = icmp ne i32 %call77, 0, !dbg !4563
  br i1 %tobool78, label %if.else110, label %lor.lhs.false79, !dbg !4563

lor.lhs.false79:                                  ; preds = %lor.lhs.false76
  %cache_avail80 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %bre, i32 0, i32 1, !dbg !4565
  %81 = load i32, i32* %cache_avail80, align 8, !dbg !4565
  %82 = load i32, i32* %pt_max_bits, align 4, !dbg !4565
  %cmp81 = icmp sge i32 %81, %82, !dbg !4565
  br i1 %cmp81, label %if.else110, label %if.then83, !dbg !4567

if.then83:                                        ; preds = %lor.lhs.false79
  %83 = load i32, i32* %last.addr, align 4, !dbg !4568
  %tobool84 = icmp ne i32 %83, 0, !dbg !4568
  br i1 %tobool84, label %if.end87, label %if.then85, !dbg !4571

if.then85:                                        ; preds = %if.then83
  store i32 10, i32* %state, align 4, !dbg !4572
  %84 = load i32, i32* %copy_len, align 4, !dbg !4574
  %85 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4575
  %copy_len86 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %85, i32 0, i32 6, !dbg !4576
  store i32 %84, i32* %copy_len86, align 8, !dbg !4577
  br label %next_data, !dbg !4578

if.end87:                                         ; preds = %if.then83
  %86 = load %struct.huffman*, %struct.huffman** %pt, align 8, !dbg !4579
  %cache_buffer88 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %bre, i32 0, i32 0, !dbg !4580
  %87 = load i64, i64* %cache_buffer88, align 8, !dbg !4580
  %88 = load i32, i32* %pt_max_bits, align 4, !dbg !4580
  %cache_avail89 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %bre, i32 0, i32 1, !dbg !4580
  %89 = load i32, i32* %cache_avail89, align 8, !dbg !4580
  %sub90 = sub nsw i32 %88, %89, !dbg !4580
  %sh_prom91 = zext i32 %sub90 to i64, !dbg !4580
  %shl92 = shl i64 %87, %sh_prom91, !dbg !4580
  %conv93 = trunc i64 %shl92 to i16, !dbg !4580
  %conv94 = zext i16 %conv93 to i32, !dbg !4580
  %90 = load i32, i32* %pt_max_bits, align 4, !dbg !4580
  %idxprom95 = sext i32 %90 to i64, !dbg !4580
  %arrayidx96 = getelementptr inbounds [20 x i16], [20 x i16]* @cache_masks, i64 0, i64 %idxprom95, !dbg !4580
  %91 = load i16, i16* %arrayidx96, align 2, !dbg !4580
  %conv97 = zext i16 %91 to i32, !dbg !4580
  %and98 = and i32 %conv94, %conv97, !dbg !4580
  %call99 = call i32 @lzh_decode_huffman(%struct.huffman* %86, i32 %and98), !dbg !4581
  store i32 %call99, i32* %copy_pos, align 4, !dbg !4582
  %92 = load i32, i32* %copy_pos, align 4, !dbg !4583
  %idxprom100 = sext i32 %92 to i64, !dbg !4583
  %93 = load i8*, i8** %pt_bitlen, align 8, !dbg !4583
  %arrayidx101 = getelementptr inbounds i8, i8* %93, i64 %idxprom100, !dbg !4583
  %94 = load i8, i8* %arrayidx101, align 1, !dbg !4583
  %conv102 = zext i8 %94 to i32, !dbg !4583
  %cache_avail103 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %bre, i32 0, i32 1, !dbg !4583
  %95 = load i32, i32* %cache_avail103, align 8, !dbg !4583
  %sub104 = sub nsw i32 %95, %conv102, !dbg !4583
  store i32 %sub104, i32* %cache_avail103, align 8, !dbg !4583
  %cache_avail105 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %bre, i32 0, i32 1, !dbg !4584
  %96 = load i32, i32* %cache_avail105, align 8, !dbg !4584
  %cmp106 = icmp sge i32 %96, 0, !dbg !4584
  br i1 %cmp106, label %if.end109, label %if.then108, !dbg !4586

if.then108:                                       ; preds = %if.end87
  br label %failed, !dbg !4587

if.end109:                                        ; preds = %if.end87
  br label %if.end128, !dbg !4588

if.else110:                                       ; preds = %lor.lhs.false79, %lor.lhs.false76, %sw.bb72
  %97 = load %struct.huffman*, %struct.huffman** %pt, align 8, !dbg !4589
  %cache_buffer111 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %bre, i32 0, i32 0, !dbg !4591
  %98 = load i64, i64* %cache_buffer111, align 8, !dbg !4591
  %cache_avail112 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %bre, i32 0, i32 1, !dbg !4591
  %99 = load i32, i32* %cache_avail112, align 8, !dbg !4591
  %100 = load i32, i32* %pt_max_bits, align 4, !dbg !4591
  %sub113 = sub nsw i32 %99, %100, !dbg !4591
  %sh_prom114 = zext i32 %sub113 to i64, !dbg !4591
  %shr115 = lshr i64 %98, %sh_prom114, !dbg !4591
  %conv116 = trunc i64 %shr115 to i16, !dbg !4591
  %conv117 = zext i16 %conv116 to i32, !dbg !4591
  %101 = load i32, i32* %pt_max_bits, align 4, !dbg !4591
  %idxprom118 = sext i32 %101 to i64, !dbg !4591
  %arrayidx119 = getelementptr inbounds [20 x i16], [20 x i16]* @cache_masks, i64 0, i64 %idxprom118, !dbg !4591
  %102 = load i16, i16* %arrayidx119, align 2, !dbg !4591
  %conv120 = zext i16 %102 to i32, !dbg !4591
  %and121 = and i32 %conv117, %conv120, !dbg !4591
  %call122 = call i32 @lzh_decode_huffman(%struct.huffman* %97, i32 %and121), !dbg !4592
  store i32 %call122, i32* %copy_pos, align 4, !dbg !4593
  %103 = load i32, i32* %copy_pos, align 4, !dbg !4594
  %idxprom123 = sext i32 %103 to i64, !dbg !4594
  %104 = load i8*, i8** %pt_bitlen, align 8, !dbg !4594
  %arrayidx124 = getelementptr inbounds i8, i8* %104, i64 %idxprom123, !dbg !4594
  %105 = load i8, i8* %arrayidx124, align 1, !dbg !4594
  %conv125 = zext i8 %105 to i32, !dbg !4594
  %cache_avail126 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %bre, i32 0, i32 1, !dbg !4594
  %106 = load i32, i32* %cache_avail126, align 8, !dbg !4594
  %sub127 = sub nsw i32 %106, %conv125, !dbg !4594
  store i32 %sub127, i32* %cache_avail126, align 8, !dbg !4594
  br label %if.end128

if.end128:                                        ; preds = %if.else110, %if.end109
  br label %sw.bb129, !dbg !4595

sw.bb129:                                         ; preds = %for.cond, %if.end128
  %107 = load i32, i32* %copy_pos, align 4, !dbg !4597
  %cmp130 = icmp sgt i32 %107, 1, !dbg !4599
  br i1 %cmp130, label %if.then132, label %if.end166, !dbg !4600

if.then132:                                       ; preds = %sw.bb129
  call void @llvm.dbg.declare(metadata i32* %p, metadata !4601, metadata !548), !dbg !4603
  %108 = load i32, i32* %copy_pos, align 4, !dbg !4604
  %sub133 = sub nsw i32 %108, 1, !dbg !4605
  store i32 %sub133, i32* %p, align 4, !dbg !4603
  %cache_avail134 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %bre, i32 0, i32 1, !dbg !4606
  %109 = load i32, i32* %cache_avail134, align 8, !dbg !4606
  %110 = load i32, i32* %p, align 4, !dbg !4606
  %cmp135 = icmp sge i32 %109, %110, !dbg !4606
  br i1 %cmp135, label %if.end150, label %lor.lhs.false137, !dbg !4606

lor.lhs.false137:                                 ; preds = %if.then132
  %111 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !4608
  %call138 = call i32 @lzh_br_fillup(%struct.lzh_stream* %111, %struct.lzh_br* %bre), !dbg !4608
  %tobool139 = icmp ne i32 %call138, 0, !dbg !4608
  br i1 %tobool139, label %if.end150, label %lor.lhs.false140, !dbg !4608

lor.lhs.false140:                                 ; preds = %lor.lhs.false137
  %cache_avail141 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %bre, i32 0, i32 1, !dbg !4610
  %112 = load i32, i32* %cache_avail141, align 8, !dbg !4610
  %113 = load i32, i32* %p, align 4, !dbg !4610
  %cmp142 = icmp sge i32 %112, %113, !dbg !4610
  br i1 %cmp142, label %if.end150, label %if.then144, !dbg !4612

if.then144:                                       ; preds = %lor.lhs.false140
  %114 = load i32, i32* %last.addr, align 4, !dbg !4613
  %tobool145 = icmp ne i32 %114, 0, !dbg !4613
  br i1 %tobool145, label %if.then146, label %if.end147, !dbg !4616

if.then146:                                       ; preds = %if.then144
  br label %failed, !dbg !4617

if.end147:                                        ; preds = %if.then144
  store i32 11, i32* %state, align 4, !dbg !4618
  %115 = load i32, i32* %copy_len, align 4, !dbg !4619
  %116 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4620
  %copy_len148 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %116, i32 0, i32 6, !dbg !4621
  store i32 %115, i32* %copy_len148, align 8, !dbg !4622
  %117 = load i32, i32* %copy_pos, align 4, !dbg !4623
  %118 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4624
  %copy_pos149 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %118, i32 0, i32 5, !dbg !4625
  store i32 %117, i32* %copy_pos149, align 4, !dbg !4626
  br label %next_data, !dbg !4627

if.end150:                                        ; preds = %lor.lhs.false140, %lor.lhs.false137, %if.then132
  %119 = load i32, i32* %p, align 4, !dbg !4628
  %shl151 = shl i32 1, %119, !dbg !4629
  %cache_buffer152 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %bre, i32 0, i32 0, !dbg !4630
  %120 = load i64, i64* %cache_buffer152, align 8, !dbg !4630
  %cache_avail153 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %bre, i32 0, i32 1, !dbg !4630
  %121 = load i32, i32* %cache_avail153, align 8, !dbg !4630
  %122 = load i32, i32* %p, align 4, !dbg !4630
  %sub154 = sub nsw i32 %121, %122, !dbg !4630
  %sh_prom155 = zext i32 %sub154 to i64, !dbg !4630
  %shr156 = lshr i64 %120, %sh_prom155, !dbg !4630
  %conv157 = trunc i64 %shr156 to i16, !dbg !4630
  %conv158 = zext i16 %conv157 to i32, !dbg !4630
  %123 = load i32, i32* %p, align 4, !dbg !4630
  %idxprom159 = sext i32 %123 to i64, !dbg !4630
  %arrayidx160 = getelementptr inbounds [20 x i16], [20 x i16]* @cache_masks, i64 0, i64 %idxprom159, !dbg !4630
  %124 = load i16, i16* %arrayidx160, align 2, !dbg !4630
  %conv161 = zext i16 %124 to i32, !dbg !4630
  %and162 = and i32 %conv158, %conv161, !dbg !4630
  %add163 = add nsw i32 %shl151, %and162, !dbg !4631
  store i32 %add163, i32* %copy_pos, align 4, !dbg !4632
  %125 = load i32, i32* %p, align 4, !dbg !4633
  %cache_avail164 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %bre, i32 0, i32 1, !dbg !4633
  %126 = load i32, i32* %cache_avail164, align 8, !dbg !4633
  %sub165 = sub nsw i32 %126, %125, !dbg !4633
  store i32 %sub165, i32* %cache_avail164, align 8, !dbg !4633
  br label %if.end166, !dbg !4634

if.end166:                                        ; preds = %if.end150, %sw.bb129
  %127 = load i32, i32* %w_pos, align 4, !dbg !4635
  %128 = load i32, i32* %copy_pos, align 4, !dbg !4636
  %sub167 = sub nsw i32 %127, %128, !dbg !4637
  %sub168 = sub nsw i32 %sub167, 1, !dbg !4638
  %129 = load i32, i32* %w_mask, align 4, !dbg !4639
  %and169 = and i32 %sub168, %129, !dbg !4640
  store i32 %and169, i32* %copy_pos, align 4, !dbg !4641
  br label %sw.bb170, !dbg !4642

sw.bb170:                                         ; preds = %for.cond, %if.end166
  br label %for.cond171, !dbg !4643

for.cond171:                                      ; preds = %if.end248, %sw.bb170
  call void @llvm.dbg.declare(metadata i32* %l, metadata !4644, metadata !548), !dbg !4648
  %130 = load i32, i32* %copy_len, align 4, !dbg !4649
  store i32 %130, i32* %l, align 4, !dbg !4650
  %131 = load i32, i32* %copy_pos, align 4, !dbg !4651
  %132 = load i32, i32* %w_pos, align 4, !dbg !4653
  %cmp172 = icmp sgt i32 %131, %132, !dbg !4654
  br i1 %cmp172, label %if.then174, label %if.else181, !dbg !4655

if.then174:                                       ; preds = %for.cond171
  %133 = load i32, i32* %l, align 4, !dbg !4656
  %134 = load i32, i32* %w_size, align 4, !dbg !4659
  %135 = load i32, i32* %copy_pos, align 4, !dbg !4660
  %sub175 = sub nsw i32 %134, %135, !dbg !4661
  %cmp176 = icmp sgt i32 %133, %sub175, !dbg !4662
  br i1 %cmp176, label %if.then178, label %if.end180, !dbg !4663

if.then178:                                       ; preds = %if.then174
  %136 = load i32, i32* %w_size, align 4, !dbg !4664
  %137 = load i32, i32* %copy_pos, align 4, !dbg !4665
  %sub179 = sub nsw i32 %136, %137, !dbg !4666
  store i32 %sub179, i32* %l, align 4, !dbg !4667
  br label %if.end180, !dbg !4668

if.end180:                                        ; preds = %if.then178, %if.then174
  br label %if.end188, !dbg !4669

if.else181:                                       ; preds = %for.cond171
  %138 = load i32, i32* %l, align 4, !dbg !4670
  %139 = load i32, i32* %w_size, align 4, !dbg !4673
  %140 = load i32, i32* %w_pos, align 4, !dbg !4674
  %sub182 = sub nsw i32 %139, %140, !dbg !4675
  %cmp183 = icmp sgt i32 %138, %sub182, !dbg !4676
  br i1 %cmp183, label %if.then185, label %if.end187, !dbg !4677

if.then185:                                       ; preds = %if.else181
  %141 = load i32, i32* %w_size, align 4, !dbg !4678
  %142 = load i32, i32* %w_pos, align 4, !dbg !4679
  %sub186 = sub nsw i32 %141, %142, !dbg !4680
  store i32 %sub186, i32* %l, align 4, !dbg !4681
  br label %if.end187, !dbg !4682

if.end187:                                        ; preds = %if.then185, %if.else181
  br label %if.end188

if.end188:                                        ; preds = %if.end187, %if.end180
  %143 = load i32, i32* %copy_pos, align 4, !dbg !4683
  %144 = load i32, i32* %l, align 4, !dbg !4685
  %add189 = add nsw i32 %143, %144, !dbg !4686
  %145 = load i32, i32* %w_pos, align 4, !dbg !4687
  %cmp190 = icmp slt i32 %add189, %145, !dbg !4688
  br i1 %cmp190, label %if.then196, label %lor.lhs.false192, !dbg !4689

lor.lhs.false192:                                 ; preds = %if.end188
  %146 = load i32, i32* %w_pos, align 4, !dbg !4690
  %147 = load i32, i32* %l, align 4, !dbg !4692
  %add193 = add nsw i32 %146, %147, !dbg !4693
  %148 = load i32, i32* %copy_pos, align 4, !dbg !4694
  %cmp194 = icmp slt i32 %add193, %148, !dbg !4695
  br i1 %cmp194, label %if.then196, label %if.else200, !dbg !4696

if.then196:                                       ; preds = %lor.lhs.false192, %if.end188
  %149 = load i8*, i8** %w_buff, align 8, !dbg !4698
  %150 = load i32, i32* %w_pos, align 4, !dbg !4700
  %idx.ext = sext i32 %150 to i64, !dbg !4701
  %add.ptr = getelementptr inbounds i8, i8* %149, i64 %idx.ext, !dbg !4701
  %151 = load i8*, i8** %w_buff, align 8, !dbg !4702
  %152 = load i32, i32* %copy_pos, align 4, !dbg !4703
  %idx.ext197 = sext i32 %152 to i64, !dbg !4704
  %add.ptr198 = getelementptr inbounds i8, i8* %151, i64 %idx.ext197, !dbg !4704
  %153 = load i32, i32* %l, align 4, !dbg !4705
  %conv199 = sext i32 %153 to i64, !dbg !4705
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %add.ptr, i8* %add.ptr198, i64 %conv199, i32 1, i1 false), !dbg !4706
  br label %if.end228, !dbg !4707

if.else200:                                       ; preds = %lor.lhs.false192
  call void @llvm.dbg.declare(metadata i8** %s, metadata !4708, metadata !548), !dbg !4710
  call void @llvm.dbg.declare(metadata i8** %d, metadata !4711, metadata !548), !dbg !4712
  call void @llvm.dbg.declare(metadata i32* %li, metadata !4713, metadata !548), !dbg !4714
  %154 = load i8*, i8** %w_buff, align 8, !dbg !4715
  %155 = load i32, i32* %w_pos, align 4, !dbg !4716
  %idx.ext201 = sext i32 %155 to i64, !dbg !4717
  %add.ptr202 = getelementptr inbounds i8, i8* %154, i64 %idx.ext201, !dbg !4717
  store i8* %add.ptr202, i8** %d, align 8, !dbg !4718
  %156 = load i8*, i8** %w_buff, align 8, !dbg !4719
  %157 = load i32, i32* %copy_pos, align 4, !dbg !4720
  %idx.ext203 = sext i32 %157 to i64, !dbg !4721
  %add.ptr204 = getelementptr inbounds i8, i8* %156, i64 %idx.ext203, !dbg !4721
  store i8* %add.ptr204, i8** %s, align 8, !dbg !4722
  store i32 0, i32* %li, align 4, !dbg !4723
  br label %for.cond205, !dbg !4725

for.cond205:                                      ; preds = %for.body, %if.else200
  %158 = load i32, i32* %li, align 4, !dbg !4726
  %159 = load i32, i32* %l, align 4, !dbg !4729
  %sub206 = sub nsw i32 %159, 1, !dbg !4730
  %cmp207 = icmp slt i32 %158, %sub206, !dbg !4731
  br i1 %cmp207, label %for.body, label %for.end219, !dbg !4732

for.body:                                         ; preds = %for.cond205
  %160 = load i32, i32* %li, align 4, !dbg !4733
  %idxprom209 = sext i32 %160 to i64, !dbg !4735
  %161 = load i8*, i8** %s, align 8, !dbg !4735
  %arrayidx210 = getelementptr inbounds i8, i8* %161, i64 %idxprom209, !dbg !4735
  %162 = load i8, i8* %arrayidx210, align 1, !dbg !4735
  %163 = load i32, i32* %li, align 4, !dbg !4736
  %idxprom211 = sext i32 %163 to i64, !dbg !4737
  %164 = load i8*, i8** %d, align 8, !dbg !4737
  %arrayidx212 = getelementptr inbounds i8, i8* %164, i64 %idxprom211, !dbg !4737
  store i8 %162, i8* %arrayidx212, align 1, !dbg !4738
  %165 = load i32, i32* %li, align 4, !dbg !4739
  %inc213 = add nsw i32 %165, 1, !dbg !4739
  store i32 %inc213, i32* %li, align 4, !dbg !4739
  %166 = load i32, i32* %li, align 4, !dbg !4740
  %idxprom214 = sext i32 %166 to i64, !dbg !4741
  %167 = load i8*, i8** %s, align 8, !dbg !4741
  %arrayidx215 = getelementptr inbounds i8, i8* %167, i64 %idxprom214, !dbg !4741
  %168 = load i8, i8* %arrayidx215, align 1, !dbg !4741
  %169 = load i32, i32* %li, align 4, !dbg !4742
  %idxprom216 = sext i32 %169 to i64, !dbg !4743
  %170 = load i8*, i8** %d, align 8, !dbg !4743
  %arrayidx217 = getelementptr inbounds i8, i8* %170, i64 %idxprom216, !dbg !4743
  store i8 %168, i8* %arrayidx217, align 1, !dbg !4744
  %171 = load i32, i32* %li, align 4, !dbg !4745
  %inc218 = add nsw i32 %171, 1, !dbg !4745
  store i32 %inc218, i32* %li, align 4, !dbg !4745
  br label %for.cond205, !dbg !4746

for.end219:                                       ; preds = %for.cond205
  %172 = load i32, i32* %li, align 4, !dbg !4748
  %173 = load i32, i32* %l, align 4, !dbg !4750
  %cmp220 = icmp slt i32 %172, %173, !dbg !4751
  br i1 %cmp220, label %if.then222, label %if.end227, !dbg !4752

if.then222:                                       ; preds = %for.end219
  %174 = load i32, i32* %li, align 4, !dbg !4753
  %idxprom223 = sext i32 %174 to i64, !dbg !4754
  %175 = load i8*, i8** %s, align 8, !dbg !4754
  %arrayidx224 = getelementptr inbounds i8, i8* %175, i64 %idxprom223, !dbg !4754
  %176 = load i8, i8* %arrayidx224, align 1, !dbg !4754
  %177 = load i32, i32* %li, align 4, !dbg !4755
  %idxprom225 = sext i32 %177 to i64, !dbg !4756
  %178 = load i8*, i8** %d, align 8, !dbg !4756
  %arrayidx226 = getelementptr inbounds i8, i8* %178, i64 %idxprom225, !dbg !4756
  store i8 %176, i8* %arrayidx226, align 1, !dbg !4757
  br label %if.end227, !dbg !4756

if.end227:                                        ; preds = %if.then222, %for.end219
  br label %if.end228

if.end228:                                        ; preds = %if.end227, %if.then196
  %179 = load i32, i32* %l, align 4, !dbg !4758
  %180 = load i32, i32* %w_pos, align 4, !dbg !4759
  %add229 = add nsw i32 %180, %179, !dbg !4759
  store i32 %add229, i32* %w_pos, align 4, !dbg !4759
  %181 = load i32, i32* %w_pos, align 4, !dbg !4760
  %182 = load i32, i32* %w_size, align 4, !dbg !4762
  %cmp230 = icmp eq i32 %181, %182, !dbg !4763
  br i1 %cmp230, label %if.then232, label %if.end244, !dbg !4764

if.then232:                                       ; preds = %if.end228
  store i32 0, i32* %w_pos, align 4, !dbg !4765
  %183 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !4767
  %184 = load i32, i32* %w_size, align 4, !dbg !4768
  %conv233 = sext i32 %184 to i64, !dbg !4768
  call void @lzh_emit_window(%struct.lzh_stream* %183, i64 %conv233), !dbg !4769
  %185 = load i32, i32* %copy_len, align 4, !dbg !4770
  %186 = load i32, i32* %l, align 4, !dbg !4772
  %cmp234 = icmp sle i32 %185, %186, !dbg !4773
  br i1 %cmp234, label %if.then236, label %if.else237, !dbg !4774

if.then236:                                       ; preds = %if.then232
  store i32 9, i32* %state, align 4, !dbg !4775
  br label %if.end243, !dbg !4776

if.else237:                                       ; preds = %if.then232
  store i32 12, i32* %state, align 4, !dbg !4777
  %187 = load i32, i32* %copy_len, align 4, !dbg !4779
  %188 = load i32, i32* %l, align 4, !dbg !4780
  %sub238 = sub nsw i32 %187, %188, !dbg !4781
  %189 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4782
  %copy_len239 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %189, i32 0, i32 6, !dbg !4783
  store i32 %sub238, i32* %copy_len239, align 8, !dbg !4784
  %190 = load i32, i32* %copy_pos, align 4, !dbg !4785
  %191 = load i32, i32* %l, align 4, !dbg !4786
  %add240 = add nsw i32 %190, %191, !dbg !4787
  %192 = load i32, i32* %w_mask, align 4, !dbg !4788
  %and241 = and i32 %add240, %192, !dbg !4789
  %193 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4790
  %copy_pos242 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %193, i32 0, i32 5, !dbg !4791
  store i32 %and241, i32* %copy_pos242, align 4, !dbg !4792
  br label %if.end243

if.end243:                                        ; preds = %if.else237, %if.then236
  br label %next_data, !dbg !4793

if.end244:                                        ; preds = %if.end228
  %194 = load i32, i32* %copy_len, align 4, !dbg !4794
  %195 = load i32, i32* %l, align 4, !dbg !4796
  %cmp245 = icmp sle i32 %194, %195, !dbg !4797
  br i1 %cmp245, label %if.then247, label %if.end248, !dbg !4798

if.then247:                                       ; preds = %if.end244
  br label %for.end252, !dbg !4799

if.end248:                                        ; preds = %if.end244
  %196 = load i32, i32* %l, align 4, !dbg !4800
  %197 = load i32, i32* %copy_len, align 4, !dbg !4801
  %sub249 = sub nsw i32 %197, %196, !dbg !4801
  store i32 %sub249, i32* %copy_len, align 4, !dbg !4801
  %198 = load i32, i32* %copy_pos, align 4, !dbg !4802
  %199 = load i32, i32* %l, align 4, !dbg !4803
  %add250 = add nsw i32 %198, %199, !dbg !4804
  %200 = load i32, i32* %w_mask, align 4, !dbg !4805
  %and251 = and i32 %add250, %200, !dbg !4806
  store i32 %and251, i32* %copy_pos, align 4, !dbg !4807
  br label %for.cond171, !dbg !4808

for.end252:                                       ; preds = %if.then247
  store i32 9, i32* %state, align 4, !dbg !4810
  br label %sw.epilog, !dbg !4811

sw.epilog:                                        ; preds = %for.cond, %for.end252
  br label %for.cond, !dbg !4812

failed:                                           ; preds = %if.then146, %if.then108, %if.then40
  %201 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4814
  %error = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %201, i32 0, i32 17, !dbg !4815
  store i32 -25, i32* %error, align 4, !dbg !4816
  store i32 -25, i32* %retval, align 4, !dbg !4817
  br label %return, !dbg !4817

next_data:                                        ; preds = %if.end243, %if.end147, %if.then85, %if.then68, %if.then26
  %202 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4818
  %br253 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %202, i32 0, i32 7, !dbg !4819
  %203 = bitcast %struct.lzh_br* %br253 to i8*, !dbg !4820
  %204 = bitcast %struct.lzh_br* %bre to i8*, !dbg !4820
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %203, i8* %204, i64 16, i32 8, i1 false), !dbg !4820
  %205 = load i32, i32* %blocks_avail, align 4, !dbg !4821
  %206 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4822
  %blocks_avail254 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %206, i32 0, i32 10, !dbg !4823
  store i32 %205, i32* %blocks_avail254, align 8, !dbg !4824
  %207 = load i32, i32* %state, align 4, !dbg !4825
  %208 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4826
  %state255 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %208, i32 0, i32 0, !dbg !4827
  store i32 %207, i32* %state255, align 8, !dbg !4828
  %209 = load i32, i32* %w_pos, align 4, !dbg !4829
  %210 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !4830
  %w_pos256 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %210, i32 0, i32 4, !dbg !4831
  store i32 %209, i32* %w_pos256, align 8, !dbg !4832
  store i32 0, i32* %retval, align 4, !dbg !4833
  br label %return, !dbg !4833

return:                                           ; preds = %next_data, %failed, %if.then
  %211 = load i32, i32* %retval, align 4, !dbg !4834
  ret i32 %211, !dbg !4834
}

; Function Attrs: nounwind uwtable
define internal i32 @lzh_br_fillup(%struct.lzh_stream* %strm, %struct.lzh_br* %br) #0 !dbg !485 {
entry:
  %retval = alloca i32, align 4
  %strm.addr = alloca %struct.lzh_stream*, align 8
  %br.addr = alloca %struct.lzh_br*, align 8
  %n = alloca i32, align 4
  %x = alloca i32, align 4
  store %struct.lzh_stream* %strm, %struct.lzh_stream** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzh_stream** %strm.addr, metadata !4835, metadata !548), !dbg !4836
  store %struct.lzh_br* %br, %struct.lzh_br** %br.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzh_br** %br.addr, metadata !4837, metadata !548), !dbg !4838
  call void @llvm.dbg.declare(metadata i32* %n, metadata !4839, metadata !548), !dbg !4840
  %0 = load %struct.lzh_br*, %struct.lzh_br** %br.addr, align 8, !dbg !4841
  %cache_avail = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %0, i32 0, i32 1, !dbg !4842
  %1 = load i32, i32* %cache_avail, align 8, !dbg !4842
  %conv = sext i32 %1 to i64, !dbg !4841
  %sub = sub i64 64, %conv, !dbg !4843
  %conv1 = trunc i64 %sub to i32, !dbg !4844
  store i32 %conv1, i32* %n, align 4, !dbg !4840
  br label %for.cond, !dbg !4845

for.cond:                                         ; preds = %if.end141, %entry
  call void @llvm.dbg.declare(metadata i32* %x, metadata !4846, metadata !548), !dbg !4851
  %2 = load i32, i32* %n, align 4, !dbg !4852
  %shr = ashr i32 %2, 3, !dbg !4853
  store i32 %shr, i32* %x, align 4, !dbg !4851
  %3 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !4854
  %avail_in = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %3, i32 0, i32 1, !dbg !4856
  %4 = load i32, i32* %avail_in, align 8, !dbg !4856
  %5 = load i32, i32* %x, align 4, !dbg !4857
  %cmp = icmp sge i32 %4, %5, !dbg !4858
  br i1 %cmp, label %if.then, label %if.end, !dbg !4859

if.then:                                          ; preds = %for.cond
  %6 = load i32, i32* %x, align 4, !dbg !4860
  switch i32 %6, label %sw.default [
    i32 8, label %sw.bb
    i32 7, label %sw.bb45
    i32 6, label %sw.bb93
    i32 0, label %sw.bb136
  ], !dbg !4862

sw.bb:                                            ; preds = %if.then
  %7 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !4863
  %next_in = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %7, i32 0, i32 0, !dbg !4865
  %8 = load i8*, i8** %next_in, align 8, !dbg !4865
  %arrayidx = getelementptr inbounds i8, i8* %8, i64 0, !dbg !4863
  %9 = load i8, i8* %arrayidx, align 1, !dbg !4863
  %conv3 = zext i8 %9 to i64, !dbg !4866
  %shl = shl i64 %conv3, 56, !dbg !4867
  %10 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !4868
  %next_in4 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %10, i32 0, i32 0, !dbg !4869
  %11 = load i8*, i8** %next_in4, align 8, !dbg !4869
  %arrayidx5 = getelementptr inbounds i8, i8* %11, i64 1, !dbg !4868
  %12 = load i8, i8* %arrayidx5, align 1, !dbg !4868
  %conv6 = zext i8 %12 to i64, !dbg !4870
  %shl7 = shl i64 %conv6, 48, !dbg !4871
  %or = or i64 %shl, %shl7, !dbg !4872
  %13 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !4873
  %next_in8 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %13, i32 0, i32 0, !dbg !4874
  %14 = load i8*, i8** %next_in8, align 8, !dbg !4874
  %arrayidx9 = getelementptr inbounds i8, i8* %14, i64 2, !dbg !4873
  %15 = load i8, i8* %arrayidx9, align 1, !dbg !4873
  %conv10 = zext i8 %15 to i64, !dbg !4875
  %shl11 = shl i64 %conv10, 40, !dbg !4876
  %or12 = or i64 %or, %shl11, !dbg !4877
  %16 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !4878
  %next_in13 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %16, i32 0, i32 0, !dbg !4879
  %17 = load i8*, i8** %next_in13, align 8, !dbg !4879
  %arrayidx14 = getelementptr inbounds i8, i8* %17, i64 3, !dbg !4878
  %18 = load i8, i8* %arrayidx14, align 1, !dbg !4878
  %conv15 = zext i8 %18 to i64, !dbg !4880
  %shl16 = shl i64 %conv15, 32, !dbg !4881
  %or17 = or i64 %or12, %shl16, !dbg !4882
  %19 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !4883
  %next_in18 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %19, i32 0, i32 0, !dbg !4884
  %20 = load i8*, i8** %next_in18, align 8, !dbg !4884
  %arrayidx19 = getelementptr inbounds i8, i8* %20, i64 4, !dbg !4883
  %21 = load i8, i8* %arrayidx19, align 1, !dbg !4883
  %conv20 = zext i8 %21 to i32, !dbg !4885
  %shl21 = shl i32 %conv20, 24, !dbg !4886
  %conv22 = zext i32 %shl21 to i64, !dbg !4887
  %or23 = or i64 %or17, %conv22, !dbg !4888
  %22 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !4889
  %next_in24 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %22, i32 0, i32 0, !dbg !4890
  %23 = load i8*, i8** %next_in24, align 8, !dbg !4890
  %arrayidx25 = getelementptr inbounds i8, i8* %23, i64 5, !dbg !4889
  %24 = load i8, i8* %arrayidx25, align 1, !dbg !4889
  %conv26 = zext i8 %24 to i32, !dbg !4891
  %shl27 = shl i32 %conv26, 16, !dbg !4892
  %conv28 = zext i32 %shl27 to i64, !dbg !4893
  %or29 = or i64 %or23, %conv28, !dbg !4894
  %25 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !4895
  %next_in30 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %25, i32 0, i32 0, !dbg !4896
  %26 = load i8*, i8** %next_in30, align 8, !dbg !4896
  %arrayidx31 = getelementptr inbounds i8, i8* %26, i64 6, !dbg !4895
  %27 = load i8, i8* %arrayidx31, align 1, !dbg !4895
  %conv32 = zext i8 %27 to i32, !dbg !4897
  %shl33 = shl i32 %conv32, 8, !dbg !4898
  %conv34 = zext i32 %shl33 to i64, !dbg !4899
  %or35 = or i64 %or29, %conv34, !dbg !4900
  %28 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !4901
  %next_in36 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %28, i32 0, i32 0, !dbg !4902
  %29 = load i8*, i8** %next_in36, align 8, !dbg !4902
  %arrayidx37 = getelementptr inbounds i8, i8* %29, i64 7, !dbg !4901
  %30 = load i8, i8* %arrayidx37, align 1, !dbg !4901
  %conv38 = zext i8 %30 to i32, !dbg !4903
  %conv39 = zext i32 %conv38 to i64, !dbg !4903
  %or40 = or i64 %or35, %conv39, !dbg !4904
  %31 = load %struct.lzh_br*, %struct.lzh_br** %br.addr, align 8, !dbg !4905
  %cache_buffer = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %31, i32 0, i32 0, !dbg !4906
  store i64 %or40, i64* %cache_buffer, align 8, !dbg !4907
  %32 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !4908
  %next_in41 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %32, i32 0, i32 0, !dbg !4909
  %33 = load i8*, i8** %next_in41, align 8, !dbg !4910
  %add.ptr = getelementptr inbounds i8, i8* %33, i64 8, !dbg !4910
  store i8* %add.ptr, i8** %next_in41, align 8, !dbg !4910
  %34 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !4911
  %avail_in42 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %34, i32 0, i32 1, !dbg !4912
  %35 = load i32, i32* %avail_in42, align 8, !dbg !4913
  %sub43 = sub nsw i32 %35, 8, !dbg !4913
  store i32 %sub43, i32* %avail_in42, align 8, !dbg !4913
  %36 = load %struct.lzh_br*, %struct.lzh_br** %br.addr, align 8, !dbg !4914
  %cache_avail44 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %36, i32 0, i32 1, !dbg !4915
  %37 = load i32, i32* %cache_avail44, align 8, !dbg !4916
  %add = add nsw i32 %37, 64, !dbg !4916
  store i32 %add, i32* %cache_avail44, align 8, !dbg !4916
  store i32 1, i32* %retval, align 4, !dbg !4917
  br label %return, !dbg !4917

sw.bb45:                                          ; preds = %if.then
  %38 = load %struct.lzh_br*, %struct.lzh_br** %br.addr, align 8, !dbg !4918
  %cache_buffer46 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %38, i32 0, i32 0, !dbg !4919
  %39 = load i64, i64* %cache_buffer46, align 8, !dbg !4919
  %shl47 = shl i64 %39, 56, !dbg !4920
  %40 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !4921
  %next_in48 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %40, i32 0, i32 0, !dbg !4922
  %41 = load i8*, i8** %next_in48, align 8, !dbg !4922
  %arrayidx49 = getelementptr inbounds i8, i8* %41, i64 0, !dbg !4921
  %42 = load i8, i8* %arrayidx49, align 1, !dbg !4921
  %conv50 = zext i8 %42 to i64, !dbg !4923
  %shl51 = shl i64 %conv50, 48, !dbg !4924
  %or52 = or i64 %shl47, %shl51, !dbg !4925
  %43 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !4926
  %next_in53 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %43, i32 0, i32 0, !dbg !4927
  %44 = load i8*, i8** %next_in53, align 8, !dbg !4927
  %arrayidx54 = getelementptr inbounds i8, i8* %44, i64 1, !dbg !4926
  %45 = load i8, i8* %arrayidx54, align 1, !dbg !4926
  %conv55 = zext i8 %45 to i64, !dbg !4928
  %shl56 = shl i64 %conv55, 40, !dbg !4929
  %or57 = or i64 %or52, %shl56, !dbg !4930
  %46 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !4931
  %next_in58 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %46, i32 0, i32 0, !dbg !4932
  %47 = load i8*, i8** %next_in58, align 8, !dbg !4932
  %arrayidx59 = getelementptr inbounds i8, i8* %47, i64 2, !dbg !4931
  %48 = load i8, i8* %arrayidx59, align 1, !dbg !4931
  %conv60 = zext i8 %48 to i64, !dbg !4933
  %shl61 = shl i64 %conv60, 32, !dbg !4934
  %or62 = or i64 %or57, %shl61, !dbg !4935
  %49 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !4936
  %next_in63 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %49, i32 0, i32 0, !dbg !4937
  %50 = load i8*, i8** %next_in63, align 8, !dbg !4937
  %arrayidx64 = getelementptr inbounds i8, i8* %50, i64 3, !dbg !4936
  %51 = load i8, i8* %arrayidx64, align 1, !dbg !4936
  %conv65 = zext i8 %51 to i32, !dbg !4938
  %shl66 = shl i32 %conv65, 24, !dbg !4939
  %conv67 = zext i32 %shl66 to i64, !dbg !4940
  %or68 = or i64 %or62, %conv67, !dbg !4941
  %52 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !4942
  %next_in69 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %52, i32 0, i32 0, !dbg !4943
  %53 = load i8*, i8** %next_in69, align 8, !dbg !4943
  %arrayidx70 = getelementptr inbounds i8, i8* %53, i64 4, !dbg !4942
  %54 = load i8, i8* %arrayidx70, align 1, !dbg !4942
  %conv71 = zext i8 %54 to i32, !dbg !4944
  %shl72 = shl i32 %conv71, 16, !dbg !4945
  %conv73 = zext i32 %shl72 to i64, !dbg !4946
  %or74 = or i64 %or68, %conv73, !dbg !4947
  %55 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !4948
  %next_in75 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %55, i32 0, i32 0, !dbg !4949
  %56 = load i8*, i8** %next_in75, align 8, !dbg !4949
  %arrayidx76 = getelementptr inbounds i8, i8* %56, i64 5, !dbg !4948
  %57 = load i8, i8* %arrayidx76, align 1, !dbg !4948
  %conv77 = zext i8 %57 to i32, !dbg !4950
  %shl78 = shl i32 %conv77, 8, !dbg !4951
  %conv79 = zext i32 %shl78 to i64, !dbg !4952
  %or80 = or i64 %or74, %conv79, !dbg !4953
  %58 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !4954
  %next_in81 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %58, i32 0, i32 0, !dbg !4955
  %59 = load i8*, i8** %next_in81, align 8, !dbg !4955
  %arrayidx82 = getelementptr inbounds i8, i8* %59, i64 6, !dbg !4954
  %60 = load i8, i8* %arrayidx82, align 1, !dbg !4954
  %conv83 = zext i8 %60 to i32, !dbg !4956
  %conv84 = zext i32 %conv83 to i64, !dbg !4956
  %or85 = or i64 %or80, %conv84, !dbg !4957
  %61 = load %struct.lzh_br*, %struct.lzh_br** %br.addr, align 8, !dbg !4958
  %cache_buffer86 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %61, i32 0, i32 0, !dbg !4959
  store i64 %or85, i64* %cache_buffer86, align 8, !dbg !4960
  %62 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !4961
  %next_in87 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %62, i32 0, i32 0, !dbg !4962
  %63 = load i8*, i8** %next_in87, align 8, !dbg !4963
  %add.ptr88 = getelementptr inbounds i8, i8* %63, i64 7, !dbg !4963
  store i8* %add.ptr88, i8** %next_in87, align 8, !dbg !4963
  %64 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !4964
  %avail_in89 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %64, i32 0, i32 1, !dbg !4965
  %65 = load i32, i32* %avail_in89, align 8, !dbg !4966
  %sub90 = sub nsw i32 %65, 7, !dbg !4966
  store i32 %sub90, i32* %avail_in89, align 8, !dbg !4966
  %66 = load %struct.lzh_br*, %struct.lzh_br** %br.addr, align 8, !dbg !4967
  %cache_avail91 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %66, i32 0, i32 1, !dbg !4968
  %67 = load i32, i32* %cache_avail91, align 8, !dbg !4969
  %add92 = add nsw i32 %67, 56, !dbg !4969
  store i32 %add92, i32* %cache_avail91, align 8, !dbg !4969
  store i32 1, i32* %retval, align 4, !dbg !4970
  br label %return, !dbg !4970

sw.bb93:                                          ; preds = %if.then
  %68 = load %struct.lzh_br*, %struct.lzh_br** %br.addr, align 8, !dbg !4971
  %cache_buffer94 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %68, i32 0, i32 0, !dbg !4972
  %69 = load i64, i64* %cache_buffer94, align 8, !dbg !4972
  %shl95 = shl i64 %69, 48, !dbg !4973
  %70 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !4974
  %next_in96 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %70, i32 0, i32 0, !dbg !4975
  %71 = load i8*, i8** %next_in96, align 8, !dbg !4975
  %arrayidx97 = getelementptr inbounds i8, i8* %71, i64 0, !dbg !4974
  %72 = load i8, i8* %arrayidx97, align 1, !dbg !4974
  %conv98 = zext i8 %72 to i64, !dbg !4976
  %shl99 = shl i64 %conv98, 40, !dbg !4977
  %or100 = or i64 %shl95, %shl99, !dbg !4978
  %73 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !4979
  %next_in101 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %73, i32 0, i32 0, !dbg !4980
  %74 = load i8*, i8** %next_in101, align 8, !dbg !4980
  %arrayidx102 = getelementptr inbounds i8, i8* %74, i64 1, !dbg !4979
  %75 = load i8, i8* %arrayidx102, align 1, !dbg !4979
  %conv103 = zext i8 %75 to i64, !dbg !4981
  %shl104 = shl i64 %conv103, 32, !dbg !4982
  %or105 = or i64 %or100, %shl104, !dbg !4983
  %76 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !4984
  %next_in106 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %76, i32 0, i32 0, !dbg !4985
  %77 = load i8*, i8** %next_in106, align 8, !dbg !4985
  %arrayidx107 = getelementptr inbounds i8, i8* %77, i64 2, !dbg !4984
  %78 = load i8, i8* %arrayidx107, align 1, !dbg !4984
  %conv108 = zext i8 %78 to i32, !dbg !4986
  %shl109 = shl i32 %conv108, 24, !dbg !4987
  %conv110 = zext i32 %shl109 to i64, !dbg !4988
  %or111 = or i64 %or105, %conv110, !dbg !4989
  %79 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !4990
  %next_in112 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %79, i32 0, i32 0, !dbg !4991
  %80 = load i8*, i8** %next_in112, align 8, !dbg !4991
  %arrayidx113 = getelementptr inbounds i8, i8* %80, i64 3, !dbg !4990
  %81 = load i8, i8* %arrayidx113, align 1, !dbg !4990
  %conv114 = zext i8 %81 to i32, !dbg !4992
  %shl115 = shl i32 %conv114, 16, !dbg !4993
  %conv116 = zext i32 %shl115 to i64, !dbg !4994
  %or117 = or i64 %or111, %conv116, !dbg !4995
  %82 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !4996
  %next_in118 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %82, i32 0, i32 0, !dbg !4997
  %83 = load i8*, i8** %next_in118, align 8, !dbg !4997
  %arrayidx119 = getelementptr inbounds i8, i8* %83, i64 4, !dbg !4996
  %84 = load i8, i8* %arrayidx119, align 1, !dbg !4996
  %conv120 = zext i8 %84 to i32, !dbg !4998
  %shl121 = shl i32 %conv120, 8, !dbg !4999
  %conv122 = zext i32 %shl121 to i64, !dbg !5000
  %or123 = or i64 %or117, %conv122, !dbg !5001
  %85 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !5002
  %next_in124 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %85, i32 0, i32 0, !dbg !5003
  %86 = load i8*, i8** %next_in124, align 8, !dbg !5003
  %arrayidx125 = getelementptr inbounds i8, i8* %86, i64 5, !dbg !5002
  %87 = load i8, i8* %arrayidx125, align 1, !dbg !5002
  %conv126 = zext i8 %87 to i32, !dbg !5004
  %conv127 = zext i32 %conv126 to i64, !dbg !5004
  %or128 = or i64 %or123, %conv127, !dbg !5005
  %88 = load %struct.lzh_br*, %struct.lzh_br** %br.addr, align 8, !dbg !5006
  %cache_buffer129 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %88, i32 0, i32 0, !dbg !5007
  store i64 %or128, i64* %cache_buffer129, align 8, !dbg !5008
  %89 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !5009
  %next_in130 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %89, i32 0, i32 0, !dbg !5010
  %90 = load i8*, i8** %next_in130, align 8, !dbg !5011
  %add.ptr131 = getelementptr inbounds i8, i8* %90, i64 6, !dbg !5011
  store i8* %add.ptr131, i8** %next_in130, align 8, !dbg !5011
  %91 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !5012
  %avail_in132 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %91, i32 0, i32 1, !dbg !5013
  %92 = load i32, i32* %avail_in132, align 8, !dbg !5014
  %sub133 = sub nsw i32 %92, 6, !dbg !5014
  store i32 %sub133, i32* %avail_in132, align 8, !dbg !5014
  %93 = load %struct.lzh_br*, %struct.lzh_br** %br.addr, align 8, !dbg !5015
  %cache_avail134 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %93, i32 0, i32 1, !dbg !5016
  %94 = load i32, i32* %cache_avail134, align 8, !dbg !5017
  %add135 = add nsw i32 %94, 48, !dbg !5017
  store i32 %add135, i32* %cache_avail134, align 8, !dbg !5017
  store i32 1, i32* %retval, align 4, !dbg !5018
  br label %return, !dbg !5018

sw.bb136:                                         ; preds = %if.then
  store i32 1, i32* %retval, align 4, !dbg !5019
  br label %return, !dbg !5019

sw.default:                                       ; preds = %if.then
  br label %sw.epilog, !dbg !5020

sw.epilog:                                        ; preds = %sw.default
  br label %if.end, !dbg !5021

if.end:                                           ; preds = %sw.epilog, %for.cond
  %95 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !5022
  %avail_in137 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %95, i32 0, i32 1, !dbg !5024
  %96 = load i32, i32* %avail_in137, align 8, !dbg !5024
  %cmp138 = icmp eq i32 %96, 0, !dbg !5025
  br i1 %cmp138, label %if.then140, label %if.end141, !dbg !5026

if.then140:                                       ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !5027
  br label %return, !dbg !5027

if.end141:                                        ; preds = %if.end
  %97 = load %struct.lzh_br*, %struct.lzh_br** %br.addr, align 8, !dbg !5029
  %cache_buffer142 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %97, i32 0, i32 0, !dbg !5030
  %98 = load i64, i64* %cache_buffer142, align 8, !dbg !5030
  %shl143 = shl i64 %98, 8, !dbg !5031
  %99 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !5032
  %next_in144 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %99, i32 0, i32 0, !dbg !5033
  %100 = load i8*, i8** %next_in144, align 8, !dbg !5034
  %incdec.ptr = getelementptr inbounds i8, i8* %100, i32 1, !dbg !5034
  store i8* %incdec.ptr, i8** %next_in144, align 8, !dbg !5034
  %101 = load i8, i8* %100, align 1, !dbg !5035
  %conv145 = zext i8 %101 to i64, !dbg !5035
  %or146 = or i64 %shl143, %conv145, !dbg !5036
  %102 = load %struct.lzh_br*, %struct.lzh_br** %br.addr, align 8, !dbg !5037
  %cache_buffer147 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %102, i32 0, i32 0, !dbg !5038
  store i64 %or146, i64* %cache_buffer147, align 8, !dbg !5039
  %103 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !5040
  %avail_in148 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %103, i32 0, i32 1, !dbg !5041
  %104 = load i32, i32* %avail_in148, align 8, !dbg !5042
  %dec = add nsw i32 %104, -1, !dbg !5042
  store i32 %dec, i32* %avail_in148, align 8, !dbg !5042
  %105 = load %struct.lzh_br*, %struct.lzh_br** %br.addr, align 8, !dbg !5043
  %cache_avail149 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %105, i32 0, i32 1, !dbg !5044
  %106 = load i32, i32* %cache_avail149, align 8, !dbg !5045
  %add150 = add nsw i32 %106, 8, !dbg !5045
  store i32 %add150, i32* %cache_avail149, align 8, !dbg !5045
  %107 = load i32, i32* %n, align 4, !dbg !5046
  %sub151 = sub nsw i32 %107, 8, !dbg !5046
  store i32 %sub151, i32* %n, align 4, !dbg !5046
  br label %for.cond, !dbg !5047

return:                                           ; preds = %if.then140, %sw.bb136, %sw.bb93, %sw.bb45, %sw.bb
  %108 = load i32, i32* %retval, align 4, !dbg !5049
  ret i32 %108, !dbg !5049
}

; Function Attrs: nounwind uwtable
define internal void @lzh_emit_window(%struct.lzh_stream* %strm, i64 %s) #0 !dbg !489 {
entry:
  %strm.addr = alloca %struct.lzh_stream*, align 8
  %s.addr = alloca i64, align 8
  store %struct.lzh_stream* %strm, %struct.lzh_stream** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzh_stream** %strm.addr, metadata !5050, metadata !548), !dbg !5051
  store i64 %s, i64* %s.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %s.addr, metadata !5052, metadata !548), !dbg !5053
  %0 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !5054
  %ds = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %0, i32 0, i32 6, !dbg !5055
  %1 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !5055
  %w_buff = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %1, i32 0, i32 3, !dbg !5056
  %2 = load i8*, i8** %w_buff, align 8, !dbg !5056
  %3 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !5057
  %ref_ptr = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %3, i32 0, i32 3, !dbg !5058
  store i8* %2, i8** %ref_ptr, align 8, !dbg !5059
  %4 = load i64, i64* %s.addr, align 8, !dbg !5060
  %conv = trunc i64 %4 to i32, !dbg !5061
  %5 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !5062
  %avail_out = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %5, i32 0, i32 4, !dbg !5063
  store i32 %conv, i32* %avail_out, align 8, !dbg !5064
  %6 = load i64, i64* %s.addr, align 8, !dbg !5065
  %7 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !5066
  %total_out = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %7, i32 0, i32 5, !dbg !5067
  %8 = load i64, i64* %total_out, align 8, !dbg !5068
  %add = add i64 %8, %6, !dbg !5068
  store i64 %add, i64* %total_out, align 8, !dbg !5068
  ret void, !dbg !5069
}

; Function Attrs: nounwind uwtable
define internal i32 @lzh_make_fake_table(%struct.huffman* %hf, i16 zeroext %c) #0 !dbg !492 {
entry:
  %retval = alloca i32, align 4
  %hf.addr = alloca %struct.huffman*, align 8
  %c.addr = alloca i16, align 2
  store %struct.huffman* %hf, %struct.huffman** %hf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.huffman** %hf.addr, metadata !5070, metadata !548), !dbg !5071
  store i16 %c, i16* %c.addr, align 2
  call void @llvm.dbg.declare(metadata i16* %c.addr, metadata !5072, metadata !548), !dbg !5073
  %0 = load i16, i16* %c.addr, align 2, !dbg !5074
  %conv = zext i16 %0 to i32, !dbg !5074
  %1 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5076
  %len_size = getelementptr inbounds %struct.huffman, %struct.huffman* %1, i32 0, i32 0, !dbg !5077
  %2 = load i32, i32* %len_size, align 8, !dbg !5077
  %cmp = icmp sge i32 %conv, %2, !dbg !5078
  br i1 %cmp, label %if.then, label %if.end, !dbg !5079

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !5080
  br label %return, !dbg !5080

if.end:                                           ; preds = %entry
  %3 = load i16, i16* %c.addr, align 2, !dbg !5081
  %4 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5082
  %tbl = getelementptr inbounds %struct.huffman, %struct.huffman* %4, i32 0, i32 10, !dbg !5083
  %5 = load i16*, i16** %tbl, align 8, !dbg !5083
  %arrayidx = getelementptr inbounds i16, i16* %5, i64 0, !dbg !5082
  store i16 %3, i16* %arrayidx, align 2, !dbg !5084
  %6 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5085
  %max_bits = getelementptr inbounds %struct.huffman, %struct.huffman* %6, i32 0, i32 5, !dbg !5086
  store i32 0, i32* %max_bits, align 8, !dbg !5087
  %7 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5088
  %shift_bits = getelementptr inbounds %struct.huffman, %struct.huffman* %7, i32 0, i32 6, !dbg !5089
  store i32 0, i32* %shift_bits, align 4, !dbg !5090
  %8 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5091
  %tbl2 = getelementptr inbounds %struct.huffman, %struct.huffman* %8, i32 0, i32 10, !dbg !5092
  %9 = load i16*, i16** %tbl2, align 8, !dbg !5092
  %arrayidx3 = getelementptr inbounds i16, i16* %9, i64 0, !dbg !5091
  %10 = load i16, i16* %arrayidx3, align 2, !dbg !5091
  %idxprom = zext i16 %10 to i64, !dbg !5093
  %11 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5093
  %bitlen = getelementptr inbounds %struct.huffman, %struct.huffman* %11, i32 0, i32 4, !dbg !5094
  %12 = load i8*, i8** %bitlen, align 8, !dbg !5094
  %arrayidx4 = getelementptr inbounds i8, i8* %12, i64 %idxprom, !dbg !5093
  store i8 0, i8* %arrayidx4, align 1, !dbg !5095
  store i32 1, i32* %retval, align 4, !dbg !5096
  br label %return, !dbg !5096

return:                                           ; preds = %if.end, %if.then
  %13 = load i32, i32* %retval, align 4, !dbg !5097
  ret i32 %13, !dbg !5097
}

; Function Attrs: nounwind uwtable
define internal i32 @lzh_read_pt_bitlen(%struct.lzh_stream* %strm, i32 %start, i32 %end) #0 !dbg !495 {
entry:
  %retval = alloca i32, align 4
  %strm.addr = alloca %struct.lzh_stream*, align 8
  %start.addr = alloca i32, align 4
  %end.addr = alloca i32, align 4
  %ds = alloca %struct.lzh_dec*, align 8
  %br = alloca %struct.lzh_br*, align 8
  %c = alloca i32, align 4
  %i = alloca i32, align 4
  store %struct.lzh_stream* %strm, %struct.lzh_stream** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzh_stream** %strm.addr, metadata !5098, metadata !548), !dbg !5099
  store i32 %start, i32* %start.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %start.addr, metadata !5100, metadata !548), !dbg !5101
  store i32 %end, i32* %end.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %end.addr, metadata !5102, metadata !548), !dbg !5103
  call void @llvm.dbg.declare(metadata %struct.lzh_dec** %ds, metadata !5104, metadata !548), !dbg !5105
  %0 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !5106
  %ds1 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %0, i32 0, i32 6, !dbg !5107
  %1 = load %struct.lzh_dec*, %struct.lzh_dec** %ds1, align 8, !dbg !5107
  store %struct.lzh_dec* %1, %struct.lzh_dec** %ds, align 8, !dbg !5105
  call void @llvm.dbg.declare(metadata %struct.lzh_br** %br, metadata !5108, metadata !548), !dbg !5109
  %2 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !5110
  %br2 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %2, i32 0, i32 7, !dbg !5111
  store %struct.lzh_br* %br2, %struct.lzh_br** %br, align 8, !dbg !5109
  call void @llvm.dbg.declare(metadata i32* %c, metadata !5112, metadata !548), !dbg !5113
  call void @llvm.dbg.declare(metadata i32* %i, metadata !5114, metadata !548), !dbg !5115
  %3 = load i32, i32* %start.addr, align 4, !dbg !5116
  store i32 %3, i32* %i, align 4, !dbg !5118
  br label %for.cond, !dbg !5119

for.cond:                                         ; preds = %if.end45, %entry
  %4 = load i32, i32* %i, align 4, !dbg !5120
  %5 = load i32, i32* %end.addr, align 4, !dbg !5123
  %cmp = icmp slt i32 %4, %5, !dbg !5124
  br i1 %cmp, label %for.body, label %for.end, !dbg !5125

for.body:                                         ; preds = %for.cond
  %6 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !5126
  %cache_avail = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %6, i32 0, i32 1, !dbg !5126
  %7 = load i32, i32* %cache_avail, align 8, !dbg !5126
  %cmp3 = icmp sge i32 %7, 3, !dbg !5126
  br i1 %cmp3, label %if.end, label %lor.lhs.false, !dbg !5126

lor.lhs.false:                                    ; preds = %for.body
  %8 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !5129
  %9 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !5129
  %call = call i32 @lzh_br_fillup(%struct.lzh_stream* %8, %struct.lzh_br* %9), !dbg !5129
  %tobool = icmp ne i32 %call, 0, !dbg !5129
  br i1 %tobool, label %if.end, label %lor.lhs.false4, !dbg !5129

lor.lhs.false4:                                   ; preds = %lor.lhs.false
  %10 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !5131
  %cache_avail5 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %10, i32 0, i32 1, !dbg !5131
  %11 = load i32, i32* %cache_avail5, align 8, !dbg !5131
  %cmp6 = icmp sge i32 %11, 3, !dbg !5131
  br i1 %cmp6, label %if.end, label %if.then, !dbg !5133

if.then:                                          ; preds = %lor.lhs.false4
  %12 = load i32, i32* %i, align 4, !dbg !5134
  store i32 %12, i32* %retval, align 4, !dbg !5135
  br label %return, !dbg !5135

if.end:                                           ; preds = %lor.lhs.false4, %lor.lhs.false, %for.body
  %13 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !5136
  %cache_buffer = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %13, i32 0, i32 0, !dbg !5136
  %14 = load i64, i64* %cache_buffer, align 8, !dbg !5136
  %15 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !5136
  %cache_avail7 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %15, i32 0, i32 1, !dbg !5136
  %16 = load i32, i32* %cache_avail7, align 8, !dbg !5136
  %sub = sub nsw i32 %16, 3, !dbg !5136
  %sh_prom = zext i32 %sub to i64, !dbg !5136
  %shr = lshr i64 %14, %sh_prom, !dbg !5136
  %conv = trunc i64 %shr to i16, !dbg !5136
  %conv8 = zext i16 %conv to i32, !dbg !5136
  %17 = load i16, i16* getelementptr inbounds ([20 x i16], [20 x i16]* @cache_masks, i64 0, i64 3), align 2, !dbg !5136
  %conv9 = zext i16 %17 to i32, !dbg !5136
  %and = and i32 %conv8, %conv9, !dbg !5136
  store i32 %and, i32* %c, align 4, !dbg !5138
  %cmp10 = icmp eq i32 %and, 7, !dbg !5139
  br i1 %cmp10, label %if.then12, label %if.else42, !dbg !5140

if.then12:                                        ; preds = %if.end
  %18 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !5141
  %cache_avail13 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %18, i32 0, i32 1, !dbg !5141
  %19 = load i32, i32* %cache_avail13, align 8, !dbg !5141
  %cmp14 = icmp sge i32 %19, 13, !dbg !5141
  br i1 %cmp14, label %if.end24, label %lor.lhs.false16, !dbg !5141

lor.lhs.false16:                                  ; preds = %if.then12
  %20 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !5144
  %21 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !5144
  %call17 = call i32 @lzh_br_fillup(%struct.lzh_stream* %20, %struct.lzh_br* %21), !dbg !5144
  %tobool18 = icmp ne i32 %call17, 0, !dbg !5144
  br i1 %tobool18, label %if.end24, label %lor.lhs.false19, !dbg !5144

lor.lhs.false19:                                  ; preds = %lor.lhs.false16
  %22 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !5146
  %cache_avail20 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %22, i32 0, i32 1, !dbg !5146
  %23 = load i32, i32* %cache_avail20, align 8, !dbg !5146
  %cmp21 = icmp sge i32 %23, 13, !dbg !5146
  br i1 %cmp21, label %if.end24, label %if.then23, !dbg !5148

if.then23:                                        ; preds = %lor.lhs.false19
  %24 = load i32, i32* %i, align 4, !dbg !5149
  store i32 %24, i32* %retval, align 4, !dbg !5150
  br label %return, !dbg !5150

if.end24:                                         ; preds = %lor.lhs.false19, %lor.lhs.false16, %if.then12
  %25 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !5151
  %cache_buffer25 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %25, i32 0, i32 0, !dbg !5151
  %26 = load i64, i64* %cache_buffer25, align 8, !dbg !5151
  %27 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !5151
  %cache_avail26 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %27, i32 0, i32 1, !dbg !5151
  %28 = load i32, i32* %cache_avail26, align 8, !dbg !5151
  %sub27 = sub nsw i32 %28, 13, !dbg !5151
  %sh_prom28 = zext i32 %sub27 to i64, !dbg !5151
  %shr29 = lshr i64 %26, %sh_prom28, !dbg !5151
  %conv30 = trunc i64 %shr29 to i16, !dbg !5151
  %conv31 = zext i16 %conv30 to i32, !dbg !5151
  %29 = load i16, i16* getelementptr inbounds ([20 x i16], [20 x i16]* @cache_masks, i64 0, i64 13), align 2, !dbg !5151
  %conv32 = zext i16 %29 to i32, !dbg !5151
  %and33 = and i32 %conv31, %conv32, !dbg !5151
  %and34 = and i32 %and33, 1023, !dbg !5152
  %idxprom = sext i32 %and34 to i64, !dbg !5153
  %arrayidx = getelementptr inbounds [1024 x i8], [1024 x i8]* @bitlen_tbl, i64 0, i64 %idxprom, !dbg !5153
  %30 = load i8, i8* %arrayidx, align 1, !dbg !5153
  %conv35 = sext i8 %30 to i32, !dbg !5153
  store i32 %conv35, i32* %c, align 4, !dbg !5154
  %31 = load i32, i32* %c, align 4, !dbg !5155
  %tobool36 = icmp ne i32 %31, 0, !dbg !5155
  br i1 %tobool36, label %if.then37, label %if.else, !dbg !5157

if.then37:                                        ; preds = %if.end24
  %32 = load i32, i32* %c, align 4, !dbg !5158
  %sub38 = sub nsw i32 %32, 3, !dbg !5158
  %33 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !5158
  %cache_avail39 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %33, i32 0, i32 1, !dbg !5158
  %34 = load i32, i32* %cache_avail39, align 8, !dbg !5158
  %sub40 = sub nsw i32 %34, %sub38, !dbg !5158
  store i32 %sub40, i32* %cache_avail39, align 8, !dbg !5158
  br label %if.end41, !dbg !5158

if.else:                                          ; preds = %if.end24
  store i32 -1, i32* %retval, align 4, !dbg !5159
  br label %return, !dbg !5159

if.end41:                                         ; preds = %if.then37
  br label %if.end45, !dbg !5160

if.else42:                                        ; preds = %if.end
  %35 = load %struct.lzh_br*, %struct.lzh_br** %br, align 8, !dbg !5161
  %cache_avail43 = getelementptr inbounds %struct.lzh_br, %struct.lzh_br* %35, i32 0, i32 1, !dbg !5161
  %36 = load i32, i32* %cache_avail43, align 8, !dbg !5161
  %sub44 = sub nsw i32 %36, 3, !dbg !5161
  store i32 %sub44, i32* %cache_avail43, align 8, !dbg !5161
  br label %if.end45

if.end45:                                         ; preds = %if.else42, %if.end41
  %37 = load i32, i32* %c, align 4, !dbg !5162
  %conv46 = trunc i32 %37 to i8, !dbg !5162
  %38 = load i32, i32* %i, align 4, !dbg !5163
  %inc = add nsw i32 %38, 1, !dbg !5163
  store i32 %inc, i32* %i, align 4, !dbg !5163
  %idxprom47 = sext i32 %38 to i64, !dbg !5164
  %39 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !5164
  %pt = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %39, i32 0, i32 9, !dbg !5165
  %bitlen = getelementptr inbounds %struct.huffman, %struct.huffman* %pt, i32 0, i32 4, !dbg !5166
  %40 = load i8*, i8** %bitlen, align 8, !dbg !5166
  %arrayidx48 = getelementptr inbounds i8, i8* %40, i64 %idxprom47, !dbg !5164
  store i8 %conv46, i8* %arrayidx48, align 1, !dbg !5167
  %41 = load i32, i32* %c, align 4, !dbg !5168
  %idxprom49 = sext i32 %41 to i64, !dbg !5169
  %42 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !5169
  %pt50 = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %42, i32 0, i32 9, !dbg !5170
  %freq = getelementptr inbounds %struct.huffman, %struct.huffman* %pt50, i32 0, i32 3, !dbg !5171
  %arrayidx51 = getelementptr inbounds [17 x i32], [17 x i32]* %freq, i64 0, i64 %idxprom49, !dbg !5169
  %43 = load i32, i32* %arrayidx51, align 4, !dbg !5172
  %inc52 = add nsw i32 %43, 1, !dbg !5172
  store i32 %inc52, i32* %arrayidx51, align 4, !dbg !5172
  br label %for.cond, !dbg !5173

for.end:                                          ; preds = %for.cond
  %44 = load i32, i32* %i, align 4, !dbg !5175
  store i32 %44, i32* %retval, align 4, !dbg !5176
  br label %return, !dbg !5176

return:                                           ; preds = %for.end, %if.else, %if.then23, %if.then
  %45 = load i32, i32* %retval, align 4, !dbg !5177
  ret i32 %45, !dbg !5177
}

; Function Attrs: nounwind uwtable
define internal i32 @lzh_make_huffman_table(%struct.huffman* %hf) #0 !dbg !498 {
entry:
  %retval = alloca i32, align 4
  %hf.addr = alloca %struct.huffman*, align 8
  %tbl = alloca i16*, align 8
  %bitlen = alloca i8*, align 8
  %bitptn = alloca [17 x i32], align 16
  %weight = alloca [17 x i32], align 16
  %i = alloca i32, align 4
  %maxbits = alloca i32, align 4
  %ptn = alloca i32, align 4
  %tbl_size = alloca i32, align 4
  %w = alloca i32, align 4
  %diffbits = alloca i32, align 4
  %len_avail = alloca i32, align 4
  %ebits = alloca i32, align 4
  %htbl_max = alloca i32, align 4
  %p = alloca i16*, align 8
  %p61 = alloca i16*, align 8
  %len = alloca i32, align 4
  %cnt = alloca i32, align 4
  %bit = alloca i16, align 2
  %extlen = alloca i32, align 4
  %ht = alloca %struct.htree_t*, align 8
  %pc = alloca i16*, align 8
  store %struct.huffman* %hf, %struct.huffman** %hf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.huffman** %hf.addr, metadata !5178, metadata !548), !dbg !5179
  call void @llvm.dbg.declare(metadata i16** %tbl, metadata !5180, metadata !548), !dbg !5181
  call void @llvm.dbg.declare(metadata i8** %bitlen, metadata !5182, metadata !548), !dbg !5183
  call void @llvm.dbg.declare(metadata [17 x i32]* %bitptn, metadata !5184, metadata !548), !dbg !5185
  call void @llvm.dbg.declare(metadata [17 x i32]* %weight, metadata !5186, metadata !548), !dbg !5187
  call void @llvm.dbg.declare(metadata i32* %i, metadata !5188, metadata !548), !dbg !5189
  call void @llvm.dbg.declare(metadata i32* %maxbits, metadata !5190, metadata !548), !dbg !5191
  store i32 0, i32* %maxbits, align 4, !dbg !5191
  call void @llvm.dbg.declare(metadata i32* %ptn, metadata !5192, metadata !548), !dbg !5193
  call void @llvm.dbg.declare(metadata i32* %tbl_size, metadata !5194, metadata !548), !dbg !5195
  call void @llvm.dbg.declare(metadata i32* %w, metadata !5196, metadata !548), !dbg !5197
  call void @llvm.dbg.declare(metadata i32* %diffbits, metadata !5198, metadata !548), !dbg !5199
  call void @llvm.dbg.declare(metadata i32* %len_avail, metadata !5200, metadata !548), !dbg !5201
  store i32 0, i32* %ptn, align 4, !dbg !5202
  store i32 1, i32* %i, align 4, !dbg !5203
  store i32 32768, i32* %w, align 4, !dbg !5205
  br label %for.cond, !dbg !5206

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, i32* %i, align 4, !dbg !5207
  %cmp = icmp sle i32 %0, 16, !dbg !5210
  br i1 %cmp, label %for.body, label %for.end, !dbg !5211

for.body:                                         ; preds = %for.cond
  %1 = load i32, i32* %ptn, align 4, !dbg !5212
  %2 = load i32, i32* %i, align 4, !dbg !5214
  %idxprom = sext i32 %2 to i64, !dbg !5215
  %arrayidx = getelementptr inbounds [17 x i32], [17 x i32]* %bitptn, i64 0, i64 %idxprom, !dbg !5215
  store i32 %1, i32* %arrayidx, align 4, !dbg !5216
  %3 = load i32, i32* %w, align 4, !dbg !5217
  %4 = load i32, i32* %i, align 4, !dbg !5218
  %idxprom1 = sext i32 %4 to i64, !dbg !5219
  %arrayidx2 = getelementptr inbounds [17 x i32], [17 x i32]* %weight, i64 0, i64 %idxprom1, !dbg !5219
  store i32 %3, i32* %arrayidx2, align 4, !dbg !5220
  %5 = load i32, i32* %i, align 4, !dbg !5221
  %idxprom3 = sext i32 %5 to i64, !dbg !5223
  %6 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5223
  %freq = getelementptr inbounds %struct.huffman, %struct.huffman* %6, i32 0, i32 3, !dbg !5224
  %arrayidx4 = getelementptr inbounds [17 x i32], [17 x i32]* %freq, i64 0, i64 %idxprom3, !dbg !5223
  %7 = load i32, i32* %arrayidx4, align 4, !dbg !5223
  %tobool = icmp ne i32 %7, 0, !dbg !5223
  br i1 %tobool, label %if.then, label %if.end, !dbg !5225

if.then:                                          ; preds = %for.body
  %8 = load i32, i32* %i, align 4, !dbg !5226
  %idxprom5 = sext i32 %8 to i64, !dbg !5228
  %9 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5228
  %freq6 = getelementptr inbounds %struct.huffman, %struct.huffman* %9, i32 0, i32 3, !dbg !5229
  %arrayidx7 = getelementptr inbounds [17 x i32], [17 x i32]* %freq6, i64 0, i64 %idxprom5, !dbg !5228
  %10 = load i32, i32* %arrayidx7, align 4, !dbg !5228
  %11 = load i32, i32* %w, align 4, !dbg !5230
  %mul = mul nsw i32 %10, %11, !dbg !5231
  %12 = load i32, i32* %ptn, align 4, !dbg !5232
  %add = add nsw i32 %12, %mul, !dbg !5232
  store i32 %add, i32* %ptn, align 4, !dbg !5232
  %13 = load i32, i32* %i, align 4, !dbg !5233
  store i32 %13, i32* %maxbits, align 4, !dbg !5234
  br label %if.end, !dbg !5235

if.end:                                           ; preds = %if.then, %for.body
  br label %for.inc, !dbg !5236

for.inc:                                          ; preds = %if.end
  %14 = load i32, i32* %i, align 4, !dbg !5237
  %inc = add nsw i32 %14, 1, !dbg !5237
  store i32 %inc, i32* %i, align 4, !dbg !5237
  %15 = load i32, i32* %w, align 4, !dbg !5239
  %shr = ashr i32 %15, 1, !dbg !5239
  store i32 %shr, i32* %w, align 4, !dbg !5239
  br label %for.cond, !dbg !5240

for.end:                                          ; preds = %for.cond
  %16 = load i32, i32* %ptn, align 4, !dbg !5241
  %cmp8 = icmp ne i32 %16, 65536, !dbg !5243
  br i1 %cmp8, label %if.then10, label %lor.lhs.false, !dbg !5244

lor.lhs.false:                                    ; preds = %for.end
  %17 = load i32, i32* %maxbits, align 4, !dbg !5245
  %18 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5247
  %tbl_bits = getelementptr inbounds %struct.huffman, %struct.huffman* %18, i32 0, i32 7, !dbg !5248
  %19 = load i32, i32* %tbl_bits, align 8, !dbg !5248
  %cmp9 = icmp sgt i32 %17, %19, !dbg !5249
  br i1 %cmp9, label %if.then10, label %if.end11, !dbg !5250

if.then10:                                        ; preds = %lor.lhs.false, %for.end
  store i32 0, i32* %retval, align 4, !dbg !5251
  br label %return, !dbg !5251

if.end11:                                         ; preds = %lor.lhs.false
  %20 = load i32, i32* %maxbits, align 4, !dbg !5252
  %21 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5253
  %max_bits = getelementptr inbounds %struct.huffman, %struct.huffman* %21, i32 0, i32 5, !dbg !5254
  store i32 %20, i32* %max_bits, align 8, !dbg !5255
  %22 = load i32, i32* %maxbits, align 4, !dbg !5256
  %cmp12 = icmp slt i32 %22, 16, !dbg !5258
  br i1 %cmp12, label %if.then13, label %if.end26, !dbg !5259

if.then13:                                        ; preds = %if.end11
  call void @llvm.dbg.declare(metadata i32* %ebits, metadata !5260, metadata !548), !dbg !5262
  %23 = load i32, i32* %maxbits, align 4, !dbg !5263
  %sub = sub nsw i32 16, %23, !dbg !5264
  store i32 %sub, i32* %ebits, align 4, !dbg !5262
  store i32 1, i32* %i, align 4, !dbg !5265
  br label %for.cond14, !dbg !5267

for.cond14:                                       ; preds = %for.inc23, %if.then13
  %24 = load i32, i32* %i, align 4, !dbg !5268
  %25 = load i32, i32* %maxbits, align 4, !dbg !5271
  %cmp15 = icmp sle i32 %24, %25, !dbg !5272
  br i1 %cmp15, label %for.body16, label %for.end25, !dbg !5273

for.body16:                                       ; preds = %for.cond14
  %26 = load i32, i32* %ebits, align 4, !dbg !5274
  %27 = load i32, i32* %i, align 4, !dbg !5276
  %idxprom17 = sext i32 %27 to i64, !dbg !5277
  %arrayidx18 = getelementptr inbounds [17 x i32], [17 x i32]* %bitptn, i64 0, i64 %idxprom17, !dbg !5277
  %28 = load i32, i32* %arrayidx18, align 4, !dbg !5278
  %shr19 = ashr i32 %28, %26, !dbg !5278
  store i32 %shr19, i32* %arrayidx18, align 4, !dbg !5278
  %29 = load i32, i32* %ebits, align 4, !dbg !5279
  %30 = load i32, i32* %i, align 4, !dbg !5280
  %idxprom20 = sext i32 %30 to i64, !dbg !5281
  %arrayidx21 = getelementptr inbounds [17 x i32], [17 x i32]* %weight, i64 0, i64 %idxprom20, !dbg !5281
  %31 = load i32, i32* %arrayidx21, align 4, !dbg !5282
  %shr22 = ashr i32 %31, %29, !dbg !5282
  store i32 %shr22, i32* %arrayidx21, align 4, !dbg !5282
  br label %for.inc23, !dbg !5283

for.inc23:                                        ; preds = %for.body16
  %32 = load i32, i32* %i, align 4, !dbg !5284
  %inc24 = add nsw i32 %32, 1, !dbg !5284
  store i32 %inc24, i32* %i, align 4, !dbg !5284
  br label %for.cond14, !dbg !5286

for.end25:                                        ; preds = %for.cond14
  br label %if.end26, !dbg !5287

if.end26:                                         ; preds = %for.end25, %if.end11
  %33 = load i32, i32* %maxbits, align 4, !dbg !5288
  %cmp27 = icmp sgt i32 %33, 10, !dbg !5290
  br i1 %cmp27, label %if.then28, label %if.else, !dbg !5291

if.then28:                                        ; preds = %if.end26
  call void @llvm.dbg.declare(metadata i32* %htbl_max, metadata !5292, metadata !548), !dbg !5294
  call void @llvm.dbg.declare(metadata i16** %p, metadata !5295, metadata !548), !dbg !5296
  %34 = load i32, i32* %maxbits, align 4, !dbg !5297
  %sub29 = sub nsw i32 %34, 10, !dbg !5298
  store i32 %sub29, i32* %diffbits, align 4, !dbg !5299
  store i32 1, i32* %i, align 4, !dbg !5300
  br label %for.cond30, !dbg !5302

for.cond30:                                       ; preds = %for.inc39, %if.then28
  %35 = load i32, i32* %i, align 4, !dbg !5303
  %cmp31 = icmp sle i32 %35, 10, !dbg !5306
  br i1 %cmp31, label %for.body32, label %for.end41, !dbg !5307

for.body32:                                       ; preds = %for.cond30
  %36 = load i32, i32* %diffbits, align 4, !dbg !5308
  %37 = load i32, i32* %i, align 4, !dbg !5310
  %idxprom33 = sext i32 %37 to i64, !dbg !5311
  %arrayidx34 = getelementptr inbounds [17 x i32], [17 x i32]* %bitptn, i64 0, i64 %idxprom33, !dbg !5311
  %38 = load i32, i32* %arrayidx34, align 4, !dbg !5312
  %shr35 = ashr i32 %38, %36, !dbg !5312
  store i32 %shr35, i32* %arrayidx34, align 4, !dbg !5312
  %39 = load i32, i32* %diffbits, align 4, !dbg !5313
  %40 = load i32, i32* %i, align 4, !dbg !5314
  %idxprom36 = sext i32 %40 to i64, !dbg !5315
  %arrayidx37 = getelementptr inbounds [17 x i32], [17 x i32]* %weight, i64 0, i64 %idxprom36, !dbg !5315
  %41 = load i32, i32* %arrayidx37, align 4, !dbg !5316
  %shr38 = ashr i32 %41, %39, !dbg !5316
  store i32 %shr38, i32* %arrayidx37, align 4, !dbg !5316
  br label %for.inc39, !dbg !5317

for.inc39:                                        ; preds = %for.body32
  %42 = load i32, i32* %i, align 4, !dbg !5318
  %inc40 = add nsw i32 %42, 1, !dbg !5318
  store i32 %inc40, i32* %i, align 4, !dbg !5318
  br label %for.cond30, !dbg !5320

for.end41:                                        ; preds = %for.cond30
  %arrayidx42 = getelementptr inbounds [17 x i32], [17 x i32]* %bitptn, i64 0, i64 10, !dbg !5321
  %43 = load i32, i32* %arrayidx42, align 8, !dbg !5321
  %arrayidx43 = getelementptr inbounds [17 x i32], [17 x i32]* %weight, i64 0, i64 10, !dbg !5322
  %44 = load i32, i32* %arrayidx43, align 8, !dbg !5322
  %45 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5323
  %freq44 = getelementptr inbounds %struct.huffman, %struct.huffman* %45, i32 0, i32 3, !dbg !5324
  %arrayidx45 = getelementptr inbounds [17 x i32], [17 x i32]* %freq44, i64 0, i64 10, !dbg !5323
  %46 = load i32, i32* %arrayidx45, align 4, !dbg !5323
  %mul46 = mul nsw i32 %44, %46, !dbg !5325
  %add47 = add nsw i32 %43, %mul46, !dbg !5326
  store i32 %add47, i32* %htbl_max, align 4, !dbg !5327
  %47 = load i32, i32* %htbl_max, align 4, !dbg !5328
  %idxprom48 = zext i32 %47 to i64, !dbg !5329
  %48 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5329
  %tbl49 = getelementptr inbounds %struct.huffman, %struct.huffman* %48, i32 0, i32 10, !dbg !5330
  %49 = load i16*, i16** %tbl49, align 8, !dbg !5330
  %arrayidx50 = getelementptr inbounds i16, i16* %49, i64 %idxprom48, !dbg !5329
  store i16* %arrayidx50, i16** %p, align 8, !dbg !5331
  br label %while.cond, !dbg !5332

while.cond:                                       ; preds = %while.body, %for.end41
  %50 = load i16*, i16** %p, align 8, !dbg !5333
  %51 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5335
  %tbl51 = getelementptr inbounds %struct.huffman, %struct.huffman* %51, i32 0, i32 10, !dbg !5336
  %52 = load i16*, i16** %tbl51, align 8, !dbg !5336
  %arrayidx52 = getelementptr inbounds i16, i16* %52, i64 1024, !dbg !5335
  %cmp53 = icmp ult i16* %50, %arrayidx52, !dbg !5337
  br i1 %cmp53, label %while.body, label %while.end, !dbg !5338

while.body:                                       ; preds = %while.cond
  %53 = load i16*, i16** %p, align 8, !dbg !5339
  %incdec.ptr = getelementptr inbounds i16, i16* %53, i32 1, !dbg !5339
  store i16* %incdec.ptr, i16** %p, align 8, !dbg !5339
  store i16 0, i16* %53, align 2, !dbg !5340
  br label %while.cond, !dbg !5341

while.end:                                        ; preds = %while.cond
  br label %if.end54, !dbg !5343

if.else:                                          ; preds = %if.end26
  store i32 0, i32* %diffbits, align 4, !dbg !5344
  br label %if.end54

if.end54:                                         ; preds = %if.else, %while.end
  %54 = load i32, i32* %diffbits, align 4, !dbg !5345
  %55 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5346
  %shift_bits = getelementptr inbounds %struct.huffman, %struct.huffman* %55, i32 0, i32 6, !dbg !5347
  store i32 %54, i32* %shift_bits, align 4, !dbg !5348
  store i32 1024, i32* %tbl_size, align 4, !dbg !5349
  %56 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5350
  %tbl55 = getelementptr inbounds %struct.huffman, %struct.huffman* %56, i32 0, i32 10, !dbg !5351
  %57 = load i16*, i16** %tbl55, align 8, !dbg !5351
  store i16* %57, i16** %tbl, align 8, !dbg !5352
  %58 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5353
  %bitlen56 = getelementptr inbounds %struct.huffman, %struct.huffman* %58, i32 0, i32 4, !dbg !5354
  %59 = load i8*, i8** %bitlen56, align 8, !dbg !5354
  store i8* %59, i8** %bitlen, align 8, !dbg !5355
  %60 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5356
  %len_avail57 = getelementptr inbounds %struct.huffman, %struct.huffman* %60, i32 0, i32 1, !dbg !5357
  %61 = load i32, i32* %len_avail57, align 4, !dbg !5357
  store i32 %61, i32* %len_avail, align 4, !dbg !5358
  %62 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5359
  %tree_used = getelementptr inbounds %struct.huffman, %struct.huffman* %62, i32 0, i32 8, !dbg !5360
  store i32 0, i32* %tree_used, align 4, !dbg !5361
  store i32 0, i32* %i, align 4, !dbg !5362
  br label %for.cond58, !dbg !5364

for.cond58:                                       ; preds = %for.inc292, %if.end54
  %63 = load i32, i32* %i, align 4, !dbg !5365
  %64 = load i32, i32* %len_avail, align 4, !dbg !5368
  %cmp59 = icmp slt i32 %63, %64, !dbg !5369
  br i1 %cmp59, label %for.body60, label %for.end294, !dbg !5370

for.body60:                                       ; preds = %for.cond58
  call void @llvm.dbg.declare(metadata i16** %p61, metadata !5371, metadata !548), !dbg !5373
  call void @llvm.dbg.declare(metadata i32* %len, metadata !5374, metadata !548), !dbg !5375
  call void @llvm.dbg.declare(metadata i32* %cnt, metadata !5376, metadata !548), !dbg !5377
  call void @llvm.dbg.declare(metadata i16* %bit, metadata !5378, metadata !548), !dbg !5379
  call void @llvm.dbg.declare(metadata i32* %extlen, metadata !5380, metadata !548), !dbg !5381
  call void @llvm.dbg.declare(metadata %struct.htree_t** %ht, metadata !5382, metadata !548), !dbg !5383
  %65 = load i32, i32* %i, align 4, !dbg !5384
  %idxprom62 = sext i32 %65 to i64, !dbg !5386
  %66 = load i8*, i8** %bitlen, align 8, !dbg !5386
  %arrayidx63 = getelementptr inbounds i8, i8* %66, i64 %idxprom62, !dbg !5386
  %67 = load i8, i8* %arrayidx63, align 1, !dbg !5386
  %conv = zext i8 %67 to i32, !dbg !5386
  %cmp64 = icmp eq i32 %conv, 0, !dbg !5387
  br i1 %cmp64, label %if.then66, label %if.end67, !dbg !5388

if.then66:                                        ; preds = %for.body60
  br label %for.inc292, !dbg !5389

if.end67:                                         ; preds = %for.body60
  %68 = load i32, i32* %i, align 4, !dbg !5390
  %idxprom68 = sext i32 %68 to i64, !dbg !5391
  %69 = load i8*, i8** %bitlen, align 8, !dbg !5391
  %arrayidx69 = getelementptr inbounds i8, i8* %69, i64 %idxprom68, !dbg !5391
  %70 = load i8, i8* %arrayidx69, align 1, !dbg !5391
  %conv70 = zext i8 %70 to i32, !dbg !5391
  store i32 %conv70, i32* %len, align 4, !dbg !5392
  %71 = load i32, i32* %len, align 4, !dbg !5393
  %idxprom71 = sext i32 %71 to i64, !dbg !5394
  %arrayidx72 = getelementptr inbounds [17 x i32], [17 x i32]* %bitptn, i64 0, i64 %idxprom71, !dbg !5394
  %72 = load i32, i32* %arrayidx72, align 4, !dbg !5394
  store i32 %72, i32* %ptn, align 4, !dbg !5395
  %73 = load i32, i32* %len, align 4, !dbg !5396
  %idxprom73 = sext i32 %73 to i64, !dbg !5397
  %arrayidx74 = getelementptr inbounds [17 x i32], [17 x i32]* %weight, i64 0, i64 %idxprom73, !dbg !5397
  %74 = load i32, i32* %arrayidx74, align 4, !dbg !5397
  store i32 %74, i32* %cnt, align 4, !dbg !5398
  %75 = load i32, i32* %len, align 4, !dbg !5399
  %cmp75 = icmp sle i32 %75, 10, !dbg !5401
  br i1 %cmp75, label %if.then77, label %if.end152, !dbg !5402

if.then77:                                        ; preds = %if.end67
  %76 = load i32, i32* %ptn, align 4, !dbg !5403
  %77 = load i32, i32* %cnt, align 4, !dbg !5406
  %add78 = add nsw i32 %76, %77, !dbg !5407
  %78 = load i32, i32* %len, align 4, !dbg !5408
  %idxprom79 = sext i32 %78 to i64, !dbg !5409
  %arrayidx80 = getelementptr inbounds [17 x i32], [17 x i32]* %bitptn, i64 0, i64 %idxprom79, !dbg !5409
  store i32 %add78, i32* %arrayidx80, align 4, !dbg !5410
  %79 = load i32, i32* %tbl_size, align 4, !dbg !5411
  %cmp81 = icmp sgt i32 %add78, %79, !dbg !5412
  br i1 %cmp81, label %if.then83, label %if.end84, !dbg !5413

if.then83:                                        ; preds = %if.then77
  store i32 0, i32* %retval, align 4, !dbg !5414
  br label %return, !dbg !5414

if.end84:                                         ; preds = %if.then77
  %80 = load i32, i32* %ptn, align 4, !dbg !5415
  %idxprom85 = sext i32 %80 to i64, !dbg !5416
  %81 = load i16*, i16** %tbl, align 8, !dbg !5416
  %arrayidx86 = getelementptr inbounds i16, i16* %81, i64 %idxprom85, !dbg !5416
  store i16* %arrayidx86, i16** %p61, align 8, !dbg !5417
  %82 = load i32, i32* %cnt, align 4, !dbg !5418
  %cmp87 = icmp sgt i32 %82, 7, !dbg !5420
  br i1 %cmp87, label %if.then89, label %if.else131, !dbg !5421

if.then89:                                        ; preds = %if.end84
  call void @llvm.dbg.declare(metadata i16** %pc, metadata !5422, metadata !548), !dbg !5424
  %83 = load i32, i32* %cnt, align 4, !dbg !5425
  %sub90 = sub nsw i32 %83, 8, !dbg !5425
  store i32 %sub90, i32* %cnt, align 4, !dbg !5425
  %84 = load i32, i32* %cnt, align 4, !dbg !5426
  %idxprom91 = sext i32 %84 to i64, !dbg !5427
  %85 = load i16*, i16** %p61, align 8, !dbg !5427
  %arrayidx92 = getelementptr inbounds i16, i16* %85, i64 %idxprom91, !dbg !5427
  store i16* %arrayidx92, i16** %pc, align 8, !dbg !5428
  %86 = load i32, i32* %i, align 4, !dbg !5429
  %conv93 = trunc i32 %86 to i16, !dbg !5430
  %87 = load i16*, i16** %pc, align 8, !dbg !5431
  %arrayidx94 = getelementptr inbounds i16, i16* %87, i64 0, !dbg !5431
  store i16 %conv93, i16* %arrayidx94, align 2, !dbg !5432
  %88 = load i32, i32* %i, align 4, !dbg !5433
  %conv95 = trunc i32 %88 to i16, !dbg !5434
  %89 = load i16*, i16** %pc, align 8, !dbg !5435
  %arrayidx96 = getelementptr inbounds i16, i16* %89, i64 1, !dbg !5435
  store i16 %conv95, i16* %arrayidx96, align 2, !dbg !5436
  %90 = load i32, i32* %i, align 4, !dbg !5437
  %conv97 = trunc i32 %90 to i16, !dbg !5438
  %91 = load i16*, i16** %pc, align 8, !dbg !5439
  %arrayidx98 = getelementptr inbounds i16, i16* %91, i64 2, !dbg !5439
  store i16 %conv97, i16* %arrayidx98, align 2, !dbg !5440
  %92 = load i32, i32* %i, align 4, !dbg !5441
  %conv99 = trunc i32 %92 to i16, !dbg !5442
  %93 = load i16*, i16** %pc, align 8, !dbg !5443
  %arrayidx100 = getelementptr inbounds i16, i16* %93, i64 3, !dbg !5443
  store i16 %conv99, i16* %arrayidx100, align 2, !dbg !5444
  %94 = load i32, i32* %i, align 4, !dbg !5445
  %conv101 = trunc i32 %94 to i16, !dbg !5446
  %95 = load i16*, i16** %pc, align 8, !dbg !5447
  %arrayidx102 = getelementptr inbounds i16, i16* %95, i64 4, !dbg !5447
  store i16 %conv101, i16* %arrayidx102, align 2, !dbg !5448
  %96 = load i32, i32* %i, align 4, !dbg !5449
  %conv103 = trunc i32 %96 to i16, !dbg !5450
  %97 = load i16*, i16** %pc, align 8, !dbg !5451
  %arrayidx104 = getelementptr inbounds i16, i16* %97, i64 5, !dbg !5451
  store i16 %conv103, i16* %arrayidx104, align 2, !dbg !5452
  %98 = load i32, i32* %i, align 4, !dbg !5453
  %conv105 = trunc i32 %98 to i16, !dbg !5454
  %99 = load i16*, i16** %pc, align 8, !dbg !5455
  %arrayidx106 = getelementptr inbounds i16, i16* %99, i64 6, !dbg !5455
  store i16 %conv105, i16* %arrayidx106, align 2, !dbg !5456
  %100 = load i32, i32* %i, align 4, !dbg !5457
  %conv107 = trunc i32 %100 to i16, !dbg !5458
  %101 = load i16*, i16** %pc, align 8, !dbg !5459
  %arrayidx108 = getelementptr inbounds i16, i16* %101, i64 7, !dbg !5459
  store i16 %conv107, i16* %arrayidx108, align 2, !dbg !5460
  %102 = load i32, i32* %cnt, align 4, !dbg !5461
  %cmp109 = icmp sgt i32 %102, 7, !dbg !5463
  br i1 %cmp109, label %if.then111, label %if.end125, !dbg !5464

if.then111:                                       ; preds = %if.then89
  %103 = load i32, i32* %cnt, align 4, !dbg !5465
  %sub112 = sub nsw i32 %103, 8, !dbg !5465
  store i32 %sub112, i32* %cnt, align 4, !dbg !5465
  %104 = load i32, i32* %cnt, align 4, !dbg !5467
  %idxprom113 = sext i32 %104 to i64, !dbg !5468
  %105 = load i16*, i16** %p61, align 8, !dbg !5468
  %arrayidx114 = getelementptr inbounds i16, i16* %105, i64 %idxprom113, !dbg !5468
  %106 = bitcast i16* %arrayidx114 to i8*, !dbg !5469
  %107 = load i16*, i16** %pc, align 8, !dbg !5470
  %108 = bitcast i16* %107 to i8*, !dbg !5469
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %106, i8* %108, i64 16, i32 2, i1 false), !dbg !5469
  %109 = load i32, i32* %cnt, align 4, !dbg !5471
  %idxprom115 = sext i32 %109 to i64, !dbg !5472
  %110 = load i16*, i16** %p61, align 8, !dbg !5472
  %arrayidx116 = getelementptr inbounds i16, i16* %110, i64 %idxprom115, !dbg !5472
  store i16* %arrayidx116, i16** %pc, align 8, !dbg !5473
  br label %while.cond117, !dbg !5474

while.cond117:                                    ; preds = %while.body120, %if.then111
  %111 = load i32, i32* %cnt, align 4, !dbg !5475
  %cmp118 = icmp sgt i32 %111, 15, !dbg !5477
  br i1 %cmp118, label %while.body120, label %while.end124, !dbg !5478

while.body120:                                    ; preds = %while.cond117
  %112 = load i32, i32* %cnt, align 4, !dbg !5479
  %sub121 = sub nsw i32 %112, 16, !dbg !5479
  store i32 %sub121, i32* %cnt, align 4, !dbg !5479
  %113 = load i32, i32* %cnt, align 4, !dbg !5481
  %idxprom122 = sext i32 %113 to i64, !dbg !5482
  %114 = load i16*, i16** %p61, align 8, !dbg !5482
  %arrayidx123 = getelementptr inbounds i16, i16* %114, i64 %idxprom122, !dbg !5482
  %115 = bitcast i16* %arrayidx123 to i8*, !dbg !5483
  %116 = load i16*, i16** %pc, align 8, !dbg !5484
  %117 = bitcast i16* %116 to i8*, !dbg !5483
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %115, i8* %117, i64 32, i32 2, i1 false), !dbg !5483
  br label %while.cond117, !dbg !5485

while.end124:                                     ; preds = %while.cond117
  br label %if.end125, !dbg !5487

if.end125:                                        ; preds = %while.end124, %if.then89
  %118 = load i32, i32* %cnt, align 4, !dbg !5488
  %tobool126 = icmp ne i32 %118, 0, !dbg !5488
  br i1 %tobool126, label %if.then127, label %if.end130, !dbg !5490

if.then127:                                       ; preds = %if.end125
  %119 = load i16*, i16** %p61, align 8, !dbg !5491
  %120 = bitcast i16* %119 to i8*, !dbg !5492
  %121 = load i16*, i16** %pc, align 8, !dbg !5493
  %122 = bitcast i16* %121 to i8*, !dbg !5492
  %123 = load i32, i32* %cnt, align 4, !dbg !5494
  %conv128 = sext i32 %123 to i64, !dbg !5494
  %mul129 = mul i64 %conv128, 2, !dbg !5495
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %120, i8* %122, i64 %mul129, i32 2, i1 false), !dbg !5492
  br label %if.end130, !dbg !5492

if.end130:                                        ; preds = %if.then127, %if.end125
  br label %if.end151, !dbg !5496

if.else131:                                       ; preds = %if.end84
  br label %while.cond132, !dbg !5497

while.cond132:                                    ; preds = %while.body135, %if.else131
  %124 = load i32, i32* %cnt, align 4, !dbg !5499
  %cmp133 = icmp sgt i32 %124, 1, !dbg !5501
  br i1 %cmp133, label %while.body135, label %while.end143, !dbg !5502

while.body135:                                    ; preds = %while.cond132
  %125 = load i32, i32* %i, align 4, !dbg !5503
  %conv136 = trunc i32 %125 to i16, !dbg !5505
  %126 = load i32, i32* %cnt, align 4, !dbg !5506
  %dec = add nsw i32 %126, -1, !dbg !5506
  store i32 %dec, i32* %cnt, align 4, !dbg !5506
  %idxprom137 = sext i32 %dec to i64, !dbg !5507
  %127 = load i16*, i16** %p61, align 8, !dbg !5507
  %arrayidx138 = getelementptr inbounds i16, i16* %127, i64 %idxprom137, !dbg !5507
  store i16 %conv136, i16* %arrayidx138, align 2, !dbg !5508
  %128 = load i32, i32* %i, align 4, !dbg !5509
  %conv139 = trunc i32 %128 to i16, !dbg !5510
  %129 = load i32, i32* %cnt, align 4, !dbg !5511
  %dec140 = add nsw i32 %129, -1, !dbg !5511
  store i32 %dec140, i32* %cnt, align 4, !dbg !5511
  %idxprom141 = sext i32 %dec140 to i64, !dbg !5512
  %130 = load i16*, i16** %p61, align 8, !dbg !5512
  %arrayidx142 = getelementptr inbounds i16, i16* %130, i64 %idxprom141, !dbg !5512
  store i16 %conv139, i16* %arrayidx142, align 2, !dbg !5513
  br label %while.cond132, !dbg !5514

while.end143:                                     ; preds = %while.cond132
  %131 = load i32, i32* %cnt, align 4, !dbg !5516
  %tobool144 = icmp ne i32 %131, 0, !dbg !5516
  br i1 %tobool144, label %if.then145, label %if.end150, !dbg !5518

if.then145:                                       ; preds = %while.end143
  %132 = load i32, i32* %i, align 4, !dbg !5519
  %conv146 = trunc i32 %132 to i16, !dbg !5520
  %133 = load i32, i32* %cnt, align 4, !dbg !5521
  %dec147 = add nsw i32 %133, -1, !dbg !5521
  store i32 %dec147, i32* %cnt, align 4, !dbg !5521
  %idxprom148 = sext i32 %dec147 to i64, !dbg !5522
  %134 = load i16*, i16** %p61, align 8, !dbg !5522
  %arrayidx149 = getelementptr inbounds i16, i16* %134, i64 %idxprom148, !dbg !5522
  store i16 %conv146, i16* %arrayidx149, align 2, !dbg !5523
  br label %if.end150, !dbg !5522

if.end150:                                        ; preds = %if.then145, %while.end143
  br label %if.end151

if.end151:                                        ; preds = %if.end150, %if.end130
  br label %for.inc292, !dbg !5524

if.end152:                                        ; preds = %if.end67
  %135 = load i32, i32* %ptn, align 4, !dbg !5525
  %136 = load i32, i32* %cnt, align 4, !dbg !5526
  %add153 = add nsw i32 %135, %136, !dbg !5527
  %137 = load i32, i32* %len, align 4, !dbg !5528
  %idxprom154 = sext i32 %137 to i64, !dbg !5529
  %arrayidx155 = getelementptr inbounds [17 x i32], [17 x i32]* %bitptn, i64 0, i64 %idxprom154, !dbg !5529
  store i32 %add153, i32* %arrayidx155, align 4, !dbg !5530
  %138 = load i32, i32* %diffbits, align 4, !dbg !5531
  %sub156 = sub nsw i32 %138, 1, !dbg !5532
  %shl = shl i32 1, %sub156, !dbg !5533
  %conv157 = trunc i32 %shl to i16, !dbg !5534
  store i16 %conv157, i16* %bit, align 2, !dbg !5535
  %139 = load i32, i32* %len, align 4, !dbg !5536
  %sub158 = sub nsw i32 %139, 10, !dbg !5537
  store i32 %sub158, i32* %extlen, align 4, !dbg !5538
  %140 = load i32, i32* %ptn, align 4, !dbg !5539
  %141 = load i32, i32* %diffbits, align 4, !dbg !5540
  %shr159 = ashr i32 %140, %141, !dbg !5541
  %idxprom160 = sext i32 %shr159 to i64, !dbg !5542
  %142 = load i16*, i16** %tbl, align 8, !dbg !5542
  %arrayidx161 = getelementptr inbounds i16, i16* %142, i64 %idxprom160, !dbg !5542
  store i16* %arrayidx161, i16** %p61, align 8, !dbg !5543
  %143 = load i16*, i16** %p61, align 8, !dbg !5544
  %144 = load i16, i16* %143, align 2, !dbg !5546
  %conv162 = zext i16 %144 to i32, !dbg !5546
  %cmp163 = icmp eq i32 %conv162, 0, !dbg !5547
  br i1 %cmp163, label %if.then165, label %if.else178, !dbg !5548

if.then165:                                       ; preds = %if.end152
  %145 = load i32, i32* %len_avail, align 4, !dbg !5549
  %146 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5551
  %tree_used166 = getelementptr inbounds %struct.huffman, %struct.huffman* %146, i32 0, i32 8, !dbg !5552
  %147 = load i32, i32* %tree_used166, align 4, !dbg !5552
  %add167 = add nsw i32 %145, %147, !dbg !5553
  %conv168 = trunc i32 %add167 to i16, !dbg !5549
  %148 = load i16*, i16** %p61, align 8, !dbg !5554
  store i16 %conv168, i16* %148, align 2, !dbg !5555
  %149 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5556
  %tree_used169 = getelementptr inbounds %struct.huffman, %struct.huffman* %149, i32 0, i32 8, !dbg !5557
  %150 = load i32, i32* %tree_used169, align 4, !dbg !5558
  %inc170 = add nsw i32 %150, 1, !dbg !5558
  store i32 %inc170, i32* %tree_used169, align 4, !dbg !5558
  %idxprom171 = sext i32 %150 to i64, !dbg !5559
  %151 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5559
  %tree = getelementptr inbounds %struct.huffman, %struct.huffman* %151, i32 0, i32 11, !dbg !5560
  %152 = load %struct.htree_t*, %struct.htree_t** %tree, align 8, !dbg !5560
  %arrayidx172 = getelementptr inbounds %struct.htree_t, %struct.htree_t* %152, i64 %idxprom171, !dbg !5559
  store %struct.htree_t* %arrayidx172, %struct.htree_t** %ht, align 8, !dbg !5561
  %153 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5562
  %tree_used173 = getelementptr inbounds %struct.huffman, %struct.huffman* %153, i32 0, i32 8, !dbg !5564
  %154 = load i32, i32* %tree_used173, align 4, !dbg !5564
  %155 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5565
  %tree_avail = getelementptr inbounds %struct.huffman, %struct.huffman* %155, i32 0, i32 9, !dbg !5566
  %156 = load i32, i32* %tree_avail, align 8, !dbg !5566
  %cmp174 = icmp sgt i32 %154, %156, !dbg !5567
  br i1 %cmp174, label %if.then176, label %if.end177, !dbg !5568

if.then176:                                       ; preds = %if.then165
  store i32 0, i32* %retval, align 4, !dbg !5569
  br label %return, !dbg !5569

if.end177:                                        ; preds = %if.then165
  %157 = load %struct.htree_t*, %struct.htree_t** %ht, align 8, !dbg !5570
  %left = getelementptr inbounds %struct.htree_t, %struct.htree_t* %157, i32 0, i32 0, !dbg !5571
  store i16 0, i16* %left, align 2, !dbg !5572
  %158 = load %struct.htree_t*, %struct.htree_t** %ht, align 8, !dbg !5573
  %right = getelementptr inbounds %struct.htree_t, %struct.htree_t* %158, i32 0, i32 1, !dbg !5574
  store i16 0, i16* %right, align 2, !dbg !5575
  br label %if.end195, !dbg !5576

if.else178:                                       ; preds = %if.end152
  %159 = load i16*, i16** %p61, align 8, !dbg !5577
  %160 = load i16, i16* %159, align 2, !dbg !5580
  %conv179 = zext i16 %160 to i32, !dbg !5580
  %161 = load i32, i32* %len_avail, align 4, !dbg !5581
  %cmp180 = icmp slt i32 %conv179, %161, !dbg !5582
  br i1 %cmp180, label %if.then188, label %lor.lhs.false182, !dbg !5583

lor.lhs.false182:                                 ; preds = %if.else178
  %162 = load i16*, i16** %p61, align 8, !dbg !5584
  %163 = load i16, i16* %162, align 2, !dbg !5585
  %conv183 = zext i16 %163 to i32, !dbg !5585
  %164 = load i32, i32* %len_avail, align 4, !dbg !5586
  %165 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5587
  %tree_used184 = getelementptr inbounds %struct.huffman, %struct.huffman* %165, i32 0, i32 8, !dbg !5588
  %166 = load i32, i32* %tree_used184, align 4, !dbg !5588
  %add185 = add nsw i32 %164, %166, !dbg !5589
  %cmp186 = icmp sge i32 %conv183, %add185, !dbg !5590
  br i1 %cmp186, label %if.then188, label %if.end189, !dbg !5591

if.then188:                                       ; preds = %lor.lhs.false182, %if.else178
  store i32 0, i32* %retval, align 4, !dbg !5593
  br label %return, !dbg !5593

if.end189:                                        ; preds = %lor.lhs.false182
  %167 = load i16*, i16** %p61, align 8, !dbg !5594
  %168 = load i16, i16* %167, align 2, !dbg !5595
  %conv190 = zext i16 %168 to i32, !dbg !5595
  %169 = load i32, i32* %len_avail, align 4, !dbg !5596
  %sub191 = sub nsw i32 %conv190, %169, !dbg !5597
  %idxprom192 = sext i32 %sub191 to i64, !dbg !5598
  %170 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5598
  %tree193 = getelementptr inbounds %struct.huffman, %struct.huffman* %170, i32 0, i32 11, !dbg !5599
  %171 = load %struct.htree_t*, %struct.htree_t** %tree193, align 8, !dbg !5599
  %arrayidx194 = getelementptr inbounds %struct.htree_t, %struct.htree_t* %171, i64 %idxprom192, !dbg !5598
  store %struct.htree_t* %arrayidx194, %struct.htree_t** %ht, align 8, !dbg !5600
  br label %if.end195

if.end195:                                        ; preds = %if.end189, %if.end177
  br label %while.cond196, !dbg !5601

while.cond196:                                    ; preds = %if.end265, %if.end195
  %172 = load i32, i32* %extlen, align 4, !dbg !5602
  %dec197 = add nsw i32 %172, -1, !dbg !5602
  store i32 %dec197, i32* %extlen, align 4, !dbg !5602
  %cmp198 = icmp sgt i32 %dec197, 0, !dbg !5604
  br i1 %cmp198, label %while.body200, label %while.end269, !dbg !5605

while.body200:                                    ; preds = %while.cond196
  %173 = load i32, i32* %ptn, align 4, !dbg !5606
  %174 = load i16, i16* %bit, align 2, !dbg !5609
  %conv201 = zext i16 %174 to i32, !dbg !5609
  %and = and i32 %173, %conv201, !dbg !5610
  %tobool202 = icmp ne i32 %and, 0, !dbg !5610
  br i1 %tobool202, label %if.then203, label %if.else234, !dbg !5611

if.then203:                                       ; preds = %while.body200
  %175 = load %struct.htree_t*, %struct.htree_t** %ht, align 8, !dbg !5612
  %left204 = getelementptr inbounds %struct.htree_t, %struct.htree_t* %175, i32 0, i32 0, !dbg !5615
  %176 = load i16, i16* %left204, align 2, !dbg !5615
  %conv205 = zext i16 %176 to i32, !dbg !5612
  %177 = load i32, i32* %len_avail, align 4, !dbg !5616
  %cmp206 = icmp slt i32 %conv205, %177, !dbg !5617
  br i1 %cmp206, label %if.then208, label %if.else226, !dbg !5618

if.then208:                                       ; preds = %if.then203
  %178 = load i32, i32* %len_avail, align 4, !dbg !5619
  %179 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5621
  %tree_used209 = getelementptr inbounds %struct.huffman, %struct.huffman* %179, i32 0, i32 8, !dbg !5622
  %180 = load i32, i32* %tree_used209, align 4, !dbg !5622
  %add210 = add nsw i32 %178, %180, !dbg !5623
  %conv211 = trunc i32 %add210 to i16, !dbg !5619
  %181 = load %struct.htree_t*, %struct.htree_t** %ht, align 8, !dbg !5624
  %left212 = getelementptr inbounds %struct.htree_t, %struct.htree_t* %181, i32 0, i32 0, !dbg !5625
  store i16 %conv211, i16* %left212, align 2, !dbg !5626
  %182 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5627
  %tree_used213 = getelementptr inbounds %struct.huffman, %struct.huffman* %182, i32 0, i32 8, !dbg !5628
  %183 = load i32, i32* %tree_used213, align 4, !dbg !5629
  %inc214 = add nsw i32 %183, 1, !dbg !5629
  store i32 %inc214, i32* %tree_used213, align 4, !dbg !5629
  %idxprom215 = sext i32 %183 to i64, !dbg !5630
  %184 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5630
  %tree216 = getelementptr inbounds %struct.huffman, %struct.huffman* %184, i32 0, i32 11, !dbg !5631
  %185 = load %struct.htree_t*, %struct.htree_t** %tree216, align 8, !dbg !5631
  %arrayidx217 = getelementptr inbounds %struct.htree_t, %struct.htree_t* %185, i64 %idxprom215, !dbg !5630
  store %struct.htree_t* %arrayidx217, %struct.htree_t** %ht, align 8, !dbg !5632
  %186 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5633
  %tree_used218 = getelementptr inbounds %struct.huffman, %struct.huffman* %186, i32 0, i32 8, !dbg !5635
  %187 = load i32, i32* %tree_used218, align 4, !dbg !5635
  %188 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5636
  %tree_avail219 = getelementptr inbounds %struct.huffman, %struct.huffman* %188, i32 0, i32 9, !dbg !5637
  %189 = load i32, i32* %tree_avail219, align 8, !dbg !5637
  %cmp220 = icmp sgt i32 %187, %189, !dbg !5638
  br i1 %cmp220, label %if.then222, label %if.end223, !dbg !5639

if.then222:                                       ; preds = %if.then208
  store i32 0, i32* %retval, align 4, !dbg !5640
  br label %return, !dbg !5640

if.end223:                                        ; preds = %if.then208
  %190 = load %struct.htree_t*, %struct.htree_t** %ht, align 8, !dbg !5641
  %left224 = getelementptr inbounds %struct.htree_t, %struct.htree_t* %190, i32 0, i32 0, !dbg !5642
  store i16 0, i16* %left224, align 2, !dbg !5643
  %191 = load %struct.htree_t*, %struct.htree_t** %ht, align 8, !dbg !5644
  %right225 = getelementptr inbounds %struct.htree_t, %struct.htree_t* %191, i32 0, i32 1, !dbg !5645
  store i16 0, i16* %right225, align 2, !dbg !5646
  br label %if.end233, !dbg !5647

if.else226:                                       ; preds = %if.then203
  %192 = load %struct.htree_t*, %struct.htree_t** %ht, align 8, !dbg !5648
  %left227 = getelementptr inbounds %struct.htree_t, %struct.htree_t* %192, i32 0, i32 0, !dbg !5650
  %193 = load i16, i16* %left227, align 2, !dbg !5650
  %conv228 = zext i16 %193 to i32, !dbg !5648
  %194 = load i32, i32* %len_avail, align 4, !dbg !5651
  %sub229 = sub nsw i32 %conv228, %194, !dbg !5652
  %idxprom230 = sext i32 %sub229 to i64, !dbg !5653
  %195 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5653
  %tree231 = getelementptr inbounds %struct.huffman, %struct.huffman* %195, i32 0, i32 11, !dbg !5654
  %196 = load %struct.htree_t*, %struct.htree_t** %tree231, align 8, !dbg !5654
  %arrayidx232 = getelementptr inbounds %struct.htree_t, %struct.htree_t* %196, i64 %idxprom230, !dbg !5653
  store %struct.htree_t* %arrayidx232, %struct.htree_t** %ht, align 8, !dbg !5655
  br label %if.end233

if.end233:                                        ; preds = %if.else226, %if.end223
  br label %if.end265, !dbg !5656

if.else234:                                       ; preds = %while.body200
  %197 = load %struct.htree_t*, %struct.htree_t** %ht, align 8, !dbg !5657
  %right235 = getelementptr inbounds %struct.htree_t, %struct.htree_t* %197, i32 0, i32 1, !dbg !5660
  %198 = load i16, i16* %right235, align 2, !dbg !5660
  %conv236 = zext i16 %198 to i32, !dbg !5657
  %199 = load i32, i32* %len_avail, align 4, !dbg !5661
  %cmp237 = icmp slt i32 %conv236, %199, !dbg !5662
  br i1 %cmp237, label %if.then239, label %if.else257, !dbg !5663

if.then239:                                       ; preds = %if.else234
  %200 = load i32, i32* %len_avail, align 4, !dbg !5664
  %201 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5666
  %tree_used240 = getelementptr inbounds %struct.huffman, %struct.huffman* %201, i32 0, i32 8, !dbg !5667
  %202 = load i32, i32* %tree_used240, align 4, !dbg !5667
  %add241 = add nsw i32 %200, %202, !dbg !5668
  %conv242 = trunc i32 %add241 to i16, !dbg !5664
  %203 = load %struct.htree_t*, %struct.htree_t** %ht, align 8, !dbg !5669
  %right243 = getelementptr inbounds %struct.htree_t, %struct.htree_t* %203, i32 0, i32 1, !dbg !5670
  store i16 %conv242, i16* %right243, align 2, !dbg !5671
  %204 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5672
  %tree_used244 = getelementptr inbounds %struct.huffman, %struct.huffman* %204, i32 0, i32 8, !dbg !5673
  %205 = load i32, i32* %tree_used244, align 4, !dbg !5674
  %inc245 = add nsw i32 %205, 1, !dbg !5674
  store i32 %inc245, i32* %tree_used244, align 4, !dbg !5674
  %idxprom246 = sext i32 %205 to i64, !dbg !5675
  %206 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5675
  %tree247 = getelementptr inbounds %struct.huffman, %struct.huffman* %206, i32 0, i32 11, !dbg !5676
  %207 = load %struct.htree_t*, %struct.htree_t** %tree247, align 8, !dbg !5676
  %arrayidx248 = getelementptr inbounds %struct.htree_t, %struct.htree_t* %207, i64 %idxprom246, !dbg !5675
  store %struct.htree_t* %arrayidx248, %struct.htree_t** %ht, align 8, !dbg !5677
  %208 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5678
  %tree_used249 = getelementptr inbounds %struct.huffman, %struct.huffman* %208, i32 0, i32 8, !dbg !5680
  %209 = load i32, i32* %tree_used249, align 4, !dbg !5680
  %210 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5681
  %tree_avail250 = getelementptr inbounds %struct.huffman, %struct.huffman* %210, i32 0, i32 9, !dbg !5682
  %211 = load i32, i32* %tree_avail250, align 8, !dbg !5682
  %cmp251 = icmp sgt i32 %209, %211, !dbg !5683
  br i1 %cmp251, label %if.then253, label %if.end254, !dbg !5684

if.then253:                                       ; preds = %if.then239
  store i32 0, i32* %retval, align 4, !dbg !5685
  br label %return, !dbg !5685

if.end254:                                        ; preds = %if.then239
  %212 = load %struct.htree_t*, %struct.htree_t** %ht, align 8, !dbg !5686
  %left255 = getelementptr inbounds %struct.htree_t, %struct.htree_t* %212, i32 0, i32 0, !dbg !5687
  store i16 0, i16* %left255, align 2, !dbg !5688
  %213 = load %struct.htree_t*, %struct.htree_t** %ht, align 8, !dbg !5689
  %right256 = getelementptr inbounds %struct.htree_t, %struct.htree_t* %213, i32 0, i32 1, !dbg !5690
  store i16 0, i16* %right256, align 2, !dbg !5691
  br label %if.end264, !dbg !5692

if.else257:                                       ; preds = %if.else234
  %214 = load %struct.htree_t*, %struct.htree_t** %ht, align 8, !dbg !5693
  %right258 = getelementptr inbounds %struct.htree_t, %struct.htree_t* %214, i32 0, i32 1, !dbg !5695
  %215 = load i16, i16* %right258, align 2, !dbg !5695
  %conv259 = zext i16 %215 to i32, !dbg !5693
  %216 = load i32, i32* %len_avail, align 4, !dbg !5696
  %sub260 = sub nsw i32 %conv259, %216, !dbg !5697
  %idxprom261 = sext i32 %sub260 to i64, !dbg !5698
  %217 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5698
  %tree262 = getelementptr inbounds %struct.huffman, %struct.huffman* %217, i32 0, i32 11, !dbg !5699
  %218 = load %struct.htree_t*, %struct.htree_t** %tree262, align 8, !dbg !5699
  %arrayidx263 = getelementptr inbounds %struct.htree_t, %struct.htree_t* %218, i64 %idxprom261, !dbg !5698
  store %struct.htree_t* %arrayidx263, %struct.htree_t** %ht, align 8, !dbg !5700
  br label %if.end264

if.end264:                                        ; preds = %if.else257, %if.end254
  br label %if.end265

if.end265:                                        ; preds = %if.end264, %if.end233
  %219 = load i16, i16* %bit, align 2, !dbg !5701
  %conv266 = zext i16 %219 to i32, !dbg !5701
  %shr267 = ashr i32 %conv266, 1, !dbg !5701
  %conv268 = trunc i32 %shr267 to i16, !dbg !5701
  store i16 %conv268, i16* %bit, align 2, !dbg !5701
  br label %while.cond196, !dbg !5702

while.end269:                                     ; preds = %while.cond196
  %220 = load i32, i32* %ptn, align 4, !dbg !5704
  %221 = load i16, i16* %bit, align 2, !dbg !5706
  %conv270 = zext i16 %221 to i32, !dbg !5706
  %and271 = and i32 %220, %conv270, !dbg !5707
  %tobool272 = icmp ne i32 %and271, 0, !dbg !5707
  br i1 %tobool272, label %if.then273, label %if.else282, !dbg !5708

if.then273:                                       ; preds = %while.end269
  %222 = load %struct.htree_t*, %struct.htree_t** %ht, align 8, !dbg !5709
  %left274 = getelementptr inbounds %struct.htree_t, %struct.htree_t* %222, i32 0, i32 0, !dbg !5712
  %223 = load i16, i16* %left274, align 2, !dbg !5712
  %conv275 = zext i16 %223 to i32, !dbg !5709
  %cmp276 = icmp ne i32 %conv275, 0, !dbg !5713
  br i1 %cmp276, label %if.then278, label %if.end279, !dbg !5714

if.then278:                                       ; preds = %if.then273
  store i32 0, i32* %retval, align 4, !dbg !5715
  br label %return, !dbg !5715

if.end279:                                        ; preds = %if.then273
  %224 = load i32, i32* %i, align 4, !dbg !5716
  %conv280 = trunc i32 %224 to i16, !dbg !5717
  %225 = load %struct.htree_t*, %struct.htree_t** %ht, align 8, !dbg !5718
  %left281 = getelementptr inbounds %struct.htree_t, %struct.htree_t* %225, i32 0, i32 0, !dbg !5719
  store i16 %conv280, i16* %left281, align 2, !dbg !5720
  br label %if.end291, !dbg !5721

if.else282:                                       ; preds = %while.end269
  %226 = load %struct.htree_t*, %struct.htree_t** %ht, align 8, !dbg !5722
  %right283 = getelementptr inbounds %struct.htree_t, %struct.htree_t* %226, i32 0, i32 1, !dbg !5725
  %227 = load i16, i16* %right283, align 2, !dbg !5725
  %conv284 = zext i16 %227 to i32, !dbg !5722
  %cmp285 = icmp ne i32 %conv284, 0, !dbg !5726
  br i1 %cmp285, label %if.then287, label %if.end288, !dbg !5727

if.then287:                                       ; preds = %if.else282
  store i32 0, i32* %retval, align 4, !dbg !5728
  br label %return, !dbg !5728

if.end288:                                        ; preds = %if.else282
  %228 = load i32, i32* %i, align 4, !dbg !5729
  %conv289 = trunc i32 %228 to i16, !dbg !5730
  %229 = load %struct.htree_t*, %struct.htree_t** %ht, align 8, !dbg !5731
  %right290 = getelementptr inbounds %struct.htree_t, %struct.htree_t* %229, i32 0, i32 1, !dbg !5732
  store i16 %conv289, i16* %right290, align 2, !dbg !5733
  br label %if.end291

if.end291:                                        ; preds = %if.end288, %if.end279
  br label %for.inc292, !dbg !5734

for.inc292:                                       ; preds = %if.end291, %if.end151, %if.then66
  %230 = load i32, i32* %i, align 4, !dbg !5735
  %inc293 = add nsw i32 %230, 1, !dbg !5735
  store i32 %inc293, i32* %i, align 4, !dbg !5735
  br label %for.cond58, !dbg !5737

for.end294:                                       ; preds = %for.cond58
  store i32 1, i32* %retval, align 4, !dbg !5738
  br label %return, !dbg !5738

return:                                           ; preds = %for.end294, %if.then287, %if.then278, %if.then253, %if.then222, %if.then188, %if.then176, %if.then83, %if.then10
  %231 = load i32, i32* %retval, align 4, !dbg !5739
  ret i32 %231, !dbg !5739
}

; Function Attrs: inlinehint nounwind uwtable
define internal i32 @lzh_decode_huffman(%struct.huffman* %hf, i32 %rbits) #6 !dbg !501 {
entry:
  %retval = alloca i32, align 4
  %hf.addr = alloca %struct.huffman*, align 8
  %rbits.addr = alloca i32, align 4
  %c = alloca i32, align 4
  store %struct.huffman* %hf, %struct.huffman** %hf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.huffman** %hf.addr, metadata !5740, metadata !548), !dbg !5741
  store i32 %rbits, i32* %rbits.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %rbits.addr, metadata !5742, metadata !548), !dbg !5743
  call void @llvm.dbg.declare(metadata i32* %c, metadata !5744, metadata !548), !dbg !5745
  %0 = load i32, i32* %rbits.addr, align 4, !dbg !5746
  %1 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5747
  %shift_bits = getelementptr inbounds %struct.huffman, %struct.huffman* %1, i32 0, i32 6, !dbg !5748
  %2 = load i32, i32* %shift_bits, align 4, !dbg !5748
  %shr = lshr i32 %0, %2, !dbg !5749
  %idxprom = zext i32 %shr to i64, !dbg !5750
  %3 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5750
  %tbl = getelementptr inbounds %struct.huffman, %struct.huffman* %3, i32 0, i32 10, !dbg !5751
  %4 = load i16*, i16** %tbl, align 8, !dbg !5751
  %arrayidx = getelementptr inbounds i16, i16* %4, i64 %idxprom, !dbg !5750
  %5 = load i16, i16* %arrayidx, align 2, !dbg !5750
  %conv = zext i16 %5 to i32, !dbg !5750
  store i32 %conv, i32* %c, align 4, !dbg !5752
  %6 = load i32, i32* %c, align 4, !dbg !5753
  %7 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5755
  %len_avail = getelementptr inbounds %struct.huffman, %struct.huffman* %7, i32 0, i32 1, !dbg !5756
  %8 = load i32, i32* %len_avail, align 4, !dbg !5756
  %cmp = icmp slt i32 %6, %8, !dbg !5757
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !5758

lor.lhs.false:                                    ; preds = %entry
  %9 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5759
  %len_avail2 = getelementptr inbounds %struct.huffman, %struct.huffman* %9, i32 0, i32 1, !dbg !5761
  %10 = load i32, i32* %len_avail2, align 4, !dbg !5761
  %cmp3 = icmp eq i32 %10, 0, !dbg !5762
  br i1 %cmp3, label %if.then, label %if.end, !dbg !5763

if.then:                                          ; preds = %lor.lhs.false, %entry
  %11 = load i32, i32* %c, align 4, !dbg !5764
  store i32 %11, i32* %retval, align 4, !dbg !5765
  br label %return, !dbg !5765

if.end:                                           ; preds = %lor.lhs.false
  %12 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5766
  %13 = load i32, i32* %rbits.addr, align 4, !dbg !5767
  %14 = load i32, i32* %c, align 4, !dbg !5768
  %call = call i32 @lzh_decode_huffman_tree(%struct.huffman* %12, i32 %13, i32 %14), !dbg !5769
  store i32 %call, i32* %retval, align 4, !dbg !5770
  br label %return, !dbg !5770

return:                                           ; preds = %if.end, %if.then
  %15 = load i32, i32* %retval, align 4, !dbg !5771
  ret i32 %15, !dbg !5771
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #7

; Function Attrs: nounwind uwtable
define internal i32 @lzh_decode_huffman_tree(%struct.huffman* %hf, i32 %rbits, i32 %c) #0 !dbg !504 {
entry:
  %retval = alloca i32, align 4
  %hf.addr = alloca %struct.huffman*, align 8
  %rbits.addr = alloca i32, align 4
  %c.addr = alloca i32, align 4
  %ht = alloca %struct.htree_t*, align 8
  %extlen = alloca i32, align 4
  store %struct.huffman* %hf, %struct.huffman** %hf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.huffman** %hf.addr, metadata !5772, metadata !548), !dbg !5773
  store i32 %rbits, i32* %rbits.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %rbits.addr, metadata !5774, metadata !548), !dbg !5775
  store i32 %c, i32* %c.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %c.addr, metadata !5776, metadata !548), !dbg !5777
  call void @llvm.dbg.declare(metadata %struct.htree_t** %ht, metadata !5778, metadata !548), !dbg !5779
  call void @llvm.dbg.declare(metadata i32* %extlen, metadata !5780, metadata !548), !dbg !5781
  %0 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5782
  %tree = getelementptr inbounds %struct.huffman, %struct.huffman* %0, i32 0, i32 11, !dbg !5783
  %1 = load %struct.htree_t*, %struct.htree_t** %tree, align 8, !dbg !5783
  store %struct.htree_t* %1, %struct.htree_t** %ht, align 8, !dbg !5784
  %2 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5785
  %shift_bits = getelementptr inbounds %struct.huffman, %struct.huffman* %2, i32 0, i32 6, !dbg !5786
  %3 = load i32, i32* %shift_bits, align 4, !dbg !5786
  store i32 %3, i32* %extlen, align 4, !dbg !5787
  br label %while.cond, !dbg !5788

while.cond:                                       ; preds = %if.end8, %entry
  %4 = load i32, i32* %c.addr, align 4, !dbg !5789
  %5 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5791
  %len_avail = getelementptr inbounds %struct.huffman, %struct.huffman* %5, i32 0, i32 1, !dbg !5792
  %6 = load i32, i32* %len_avail, align 4, !dbg !5792
  %cmp = icmp sge i32 %4, %6, !dbg !5793
  br i1 %cmp, label %while.body, label %while.end, !dbg !5794

while.body:                                       ; preds = %while.cond
  %7 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5795
  %len_avail1 = getelementptr inbounds %struct.huffman, %struct.huffman* %7, i32 0, i32 1, !dbg !5797
  %8 = load i32, i32* %len_avail1, align 4, !dbg !5797
  %9 = load i32, i32* %c.addr, align 4, !dbg !5798
  %sub = sub nsw i32 %9, %8, !dbg !5798
  store i32 %sub, i32* %c.addr, align 4, !dbg !5798
  %10 = load i32, i32* %extlen, align 4, !dbg !5799
  %dec = add nsw i32 %10, -1, !dbg !5799
  store i32 %dec, i32* %extlen, align 4, !dbg !5799
  %cmp2 = icmp sle i32 %10, 0, !dbg !5801
  br i1 %cmp2, label %if.then, label %lor.lhs.false, !dbg !5802

lor.lhs.false:                                    ; preds = %while.body
  %11 = load i32, i32* %c.addr, align 4, !dbg !5803
  %12 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5805
  %tree_used = getelementptr inbounds %struct.huffman, %struct.huffman* %12, i32 0, i32 8, !dbg !5806
  %13 = load i32, i32* %tree_used, align 4, !dbg !5806
  %cmp3 = icmp sge i32 %11, %13, !dbg !5807
  br i1 %cmp3, label %if.then, label %if.end, !dbg !5808

if.then:                                          ; preds = %lor.lhs.false, %while.body
  store i32 0, i32* %retval, align 4, !dbg !5809
  br label %return, !dbg !5809

if.end:                                           ; preds = %lor.lhs.false
  %14 = load i32, i32* %rbits.addr, align 4, !dbg !5810
  %15 = load i32, i32* %extlen, align 4, !dbg !5812
  %shl = shl i32 1, %15, !dbg !5813
  %and = and i32 %14, %shl, !dbg !5814
  %tobool = icmp ne i32 %and, 0, !dbg !5814
  br i1 %tobool, label %if.then4, label %if.else, !dbg !5815

if.then4:                                         ; preds = %if.end
  %16 = load i32, i32* %c.addr, align 4, !dbg !5816
  %idxprom = sext i32 %16 to i64, !dbg !5817
  %17 = load %struct.htree_t*, %struct.htree_t** %ht, align 8, !dbg !5817
  %arrayidx = getelementptr inbounds %struct.htree_t, %struct.htree_t* %17, i64 %idxprom, !dbg !5817
  %left = getelementptr inbounds %struct.htree_t, %struct.htree_t* %arrayidx, i32 0, i32 0, !dbg !5818
  %18 = load i16, i16* %left, align 2, !dbg !5818
  %conv = zext i16 %18 to i32, !dbg !5817
  store i32 %conv, i32* %c.addr, align 4, !dbg !5819
  br label %if.end8, !dbg !5820

if.else:                                          ; preds = %if.end
  %19 = load i32, i32* %c.addr, align 4, !dbg !5821
  %idxprom5 = sext i32 %19 to i64, !dbg !5822
  %20 = load %struct.htree_t*, %struct.htree_t** %ht, align 8, !dbg !5822
  %arrayidx6 = getelementptr inbounds %struct.htree_t, %struct.htree_t* %20, i64 %idxprom5, !dbg !5822
  %right = getelementptr inbounds %struct.htree_t, %struct.htree_t* %arrayidx6, i32 0, i32 1, !dbg !5823
  %21 = load i16, i16* %right, align 2, !dbg !5823
  %conv7 = zext i16 %21 to i32, !dbg !5822
  store i32 %conv7, i32* %c.addr, align 4, !dbg !5824
  br label %if.end8

if.end8:                                          ; preds = %if.else, %if.then4
  br label %while.cond, !dbg !5825

while.end:                                        ; preds = %while.cond
  %22 = load i32, i32* %c.addr, align 4, !dbg !5827
  store i32 %22, i32* %retval, align 4, !dbg !5828
  br label %return, !dbg !5828

return:                                           ; preds = %while.end, %if.then
  %23 = load i32, i32* %retval, align 4, !dbg !5829
  ret i32 %23, !dbg !5829
}

; Function Attrs: nounwind uwtable
define internal void @lzh_decode_free(%struct.lzh_stream* %strm) #0 !dbg !511 {
entry:
  %strm.addr = alloca %struct.lzh_stream*, align 8
  store %struct.lzh_stream* %strm, %struct.lzh_stream** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzh_stream** %strm.addr, metadata !5830, metadata !548), !dbg !5831
  %0 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !5832
  %ds = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %0, i32 0, i32 6, !dbg !5834
  %1 = load %struct.lzh_dec*, %struct.lzh_dec** %ds, align 8, !dbg !5834
  %cmp = icmp eq %struct.lzh_dec* %1, null, !dbg !5835
  br i1 %cmp, label %if.then, label %if.end, !dbg !5836

if.then:                                          ; preds = %entry
  br label %return, !dbg !5837

if.end:                                           ; preds = %entry
  %2 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !5838
  %ds1 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %2, i32 0, i32 6, !dbg !5839
  %3 = load %struct.lzh_dec*, %struct.lzh_dec** %ds1, align 8, !dbg !5839
  %w_buff = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %3, i32 0, i32 3, !dbg !5840
  %4 = load i8*, i8** %w_buff, align 8, !dbg !5840
  call void @free(i8* %4) #8, !dbg !5841
  %5 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !5842
  %ds2 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %5, i32 0, i32 6, !dbg !5843
  %6 = load %struct.lzh_dec*, %struct.lzh_dec** %ds2, align 8, !dbg !5843
  %lt = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %6, i32 0, i32 8, !dbg !5844
  call void @lzh_huffman_free(%struct.huffman* %lt), !dbg !5845
  %7 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !5846
  %ds3 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %7, i32 0, i32 6, !dbg !5847
  %8 = load %struct.lzh_dec*, %struct.lzh_dec** %ds3, align 8, !dbg !5847
  %pt = getelementptr inbounds %struct.lzh_dec, %struct.lzh_dec* %8, i32 0, i32 9, !dbg !5848
  call void @lzh_huffman_free(%struct.huffman* %pt), !dbg !5849
  %9 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !5850
  %ds4 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %9, i32 0, i32 6, !dbg !5851
  %10 = load %struct.lzh_dec*, %struct.lzh_dec** %ds4, align 8, !dbg !5851
  %11 = bitcast %struct.lzh_dec* %10 to i8*, !dbg !5850
  call void @free(i8* %11) #8, !dbg !5852
  %12 = load %struct.lzh_stream*, %struct.lzh_stream** %strm.addr, align 8, !dbg !5853
  %ds5 = getelementptr inbounds %struct.lzh_stream, %struct.lzh_stream* %12, i32 0, i32 6, !dbg !5854
  store %struct.lzh_dec* null, %struct.lzh_dec** %ds5, align 8, !dbg !5855
  br label %return, !dbg !5856

return:                                           ; preds = %if.end, %if.then
  ret void, !dbg !5857
}

declare void @archive_wstring_free(%struct.archive_wstring*) #2

; Function Attrs: nounwind uwtable
define internal void @lzh_huffman_free(%struct.huffman* %hf) #0 !dbg !514 {
entry:
  %hf.addr = alloca %struct.huffman*, align 8
  store %struct.huffman* %hf, %struct.huffman** %hf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.huffman** %hf.addr, metadata !5859, metadata !548), !dbg !5860
  %0 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5861
  %bitlen = getelementptr inbounds %struct.huffman, %struct.huffman* %0, i32 0, i32 4, !dbg !5862
  %1 = load i8*, i8** %bitlen, align 8, !dbg !5862
  call void @free(i8* %1) #8, !dbg !5863
  %2 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5864
  %tbl = getelementptr inbounds %struct.huffman, %struct.huffman* %2, i32 0, i32 10, !dbg !5865
  %3 = load i16*, i16** %tbl, align 8, !dbg !5865
  %4 = bitcast i16* %3 to i8*, !dbg !5864
  call void @free(i8* %4) #8, !dbg !5866
  %5 = load %struct.huffman*, %struct.huffman** %hf.addr, align 8, !dbg !5867
  %tree = getelementptr inbounds %struct.huffman, %struct.huffman* %5, i32 0, i32 11, !dbg !5868
  %6 = load %struct.htree_t*, %struct.htree_t** %tree, align 8, !dbg !5868
  %7 = bitcast %struct.htree_t* %6 to i8*, !dbg !5867
  call void @free(i8* %7) #8, !dbg !5869
  ret void, !dbg !5870
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { inlinehint nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { argmemonly nounwind }
attributes #8 = { nounwind }
attributes #9 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!544, !545}
!llvm.ident = !{!546}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !418, globals: !517)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_support_format_lha.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !292, !123, !80, !321, !299, !23, !356, !45, !379, !303, !414, !415, !42, !38, !417}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !5, size: 64, align: 64)
!5 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read", file: !6, line: 159, size: 20288, align: 64, elements: !7)
!6 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!7 = !{!8, !111, !112, !113, !114, !115, !159, !223, !224, !225, !226, !227, !228, !261, !263, !273, !274}
!8 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !5, file: !6, line: 160, baseType: !9, size: 1280, align: 64)
!9 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !10, line: 89, size: 1280, align: 64, elements: !11)
!10 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!11 = !{!12, !14, !15, !83, !84, !85, !86, !87, !88, !89, !90, !98, !99, !100, !101, !105, !106, !107, !108, !109, !110}
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
!103 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string_conv", file: !104, line: 36, flags: DIFlagFwdDecl)
!104 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_entry_locale.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!105 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_block", scope: !9, file: !10, line: 127, baseType: !80, size: 64, align: 64, offset: 896)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_offset", scope: !9, file: !10, line: 128, baseType: !52, size: 64, align: 64, offset: 960)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_output_offset", scope: !9, file: !10, line: 129, baseType: !52, size: 64, align: 64, offset: 1024)
!108 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_remaining", scope: !9, file: !10, line: 130, baseType: !45, size: 64, align: 64, offset: 1088)
!109 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_is_posix_read", scope: !9, file: !10, line: 137, baseType: !82, size: 8, align: 8, offset: 1152)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_requested", scope: !9, file: !10, line: 138, baseType: !45, size: 64, align: 64, offset: 1216)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "entry", scope: !5, file: !6, line: 162, baseType: !30, size: 64, align: 64, offset: 1280)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_set", scope: !5, file: !6, line: 165, baseType: !23, size: 32, align: 32, offset: 1344)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_dev", scope: !5, file: !6, line: 166, baseType: !52, size: 64, align: 64, offset: 1408)
!114 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_ino", scope: !5, file: !6, line: 167, baseType: !52, size: 64, align: 64, offset: 1472)
!115 = !DIDerivedType(tag: DW_TAG_member, name: "client", scope: !5, file: !6, line: 170, baseType: !116, size: 576, align: 64, offset: 1536)
!116 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_client", file: !6, line: 134, size: 576, align: 64, elements: !117)
!117 = !{!118, !124, !130, !136, !141, !144, !149, !150, !151, !152}
!118 = !DIDerivedType(tag: DW_TAG_member, name: "opener", scope: !116, file: !6, line: 135, baseType: !119, size: 64, align: 64)
!119 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !120, size: 64, align: 64)
!120 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_open_callback", file: !32, line: 241, baseType: !121)
!121 = !DISubroutineType(types: !122)
!122 = !{!23, !24, !123}
!123 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!124 = !DIDerivedType(tag: DW_TAG_member, name: "reader", scope: !116, file: !6, line: 136, baseType: !125, size: 64, align: 64, offset: 64)
!125 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !126, size: 64, align: 64)
!126 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_read_callback", file: !32, line: 218, baseType: !127)
!127 = !DISubroutineType(types: !128)
!128 = !{!129, !24, !123, !64}
!129 = !DIDerivedType(tag: DW_TAG_typedef, name: "la_ssize_t", file: !32, line: 95, baseType: !38)
!130 = !DIDerivedType(tag: DW_TAG_member, name: "skipper", scope: !116, file: !6, line: 137, baseType: !131, size: 64, align: 64, offset: 128)
!131 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !132, size: 64, align: 64)
!132 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_skip_callback", file: !32, line: 226, baseType: !133)
!133 = !DISubroutineType(types: !134)
!134 = !{!135, !24, !123, !135}
!135 = !DIDerivedType(tag: DW_TAG_typedef, name: "la_int64_t", file: !32, line: 73, baseType: !52)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "seeker", scope: !116, file: !6, line: 138, baseType: !137, size: 64, align: 64, offset: 192)
!137 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !138, size: 64, align: 64)
!138 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_seek_callback", file: !32, line: 233, baseType: !139)
!139 = !DISubroutineType(types: !140)
!140 = !{!135, !24, !123, !135, !23}
!141 = !DIDerivedType(tag: DW_TAG_member, name: "closer", scope: !116, file: !6, line: 139, baseType: !142, size: 64, align: 64, offset: 256)
!142 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !143, size: 64, align: 64)
!143 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_close_callback", file: !32, line: 243, baseType: !121)
!144 = !DIDerivedType(tag: DW_TAG_member, name: "switcher", scope: !116, file: !6, line: 140, baseType: !145, size: 64, align: 64, offset: 320)
!145 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !146, size: 64, align: 64)
!146 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_switch_callback", file: !32, line: 249, baseType: !147)
!147 = !DISubroutineType(types: !148)
!148 = !{!23, !24, !123, !123}
!149 = !DIDerivedType(tag: DW_TAG_member, name: "nodes", scope: !116, file: !6, line: 141, baseType: !13, size: 32, align: 32, offset: 384)
!150 = !DIDerivedType(tag: DW_TAG_member, name: "cursor", scope: !116, file: !6, line: 142, baseType: !13, size: 32, align: 32, offset: 416)
!151 = !DIDerivedType(tag: DW_TAG_member, name: "position", scope: !116, file: !6, line: 143, baseType: !52, size: 64, align: 64, offset: 448)
!152 = !DIDerivedType(tag: DW_TAG_member, name: "dataset", scope: !116, file: !6, line: 144, baseType: !153, size: 64, align: 64, offset: 512)
!153 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !154, size: 64, align: 64)
!154 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_data_node", file: !6, line: 129, size: 192, align: 64, elements: !155)
!155 = !{!156, !157, !158}
!156 = !DIDerivedType(tag: DW_TAG_member, name: "begin_position", scope: !154, file: !6, line: 130, baseType: !52, size: 64, align: 64)
!157 = !DIDerivedType(tag: DW_TAG_member, name: "total_size", scope: !154, file: !6, line: 131, baseType: !52, size: 64, align: 64, offset: 64)
!158 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !154, file: !6, line: 132, baseType: !123, size: 64, align: 64, offset: 128)
!159 = !DIDerivedType(tag: DW_TAG_member, name: "bidders", scope: !5, file: !6, line: 173, baseType: !160, size: 6144, align: 64, offset: 2112)
!160 = !DICompositeType(tag: DW_TAG_array_type, baseType: !161, size: 6144, align: 64, elements: !221)
!161 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_filter_bidder", file: !6, line: 60, size: 384, align: 64, elements: !162)
!162 = !{!163, !164, !165, !212, !213, !217}
!163 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !161, file: !6, line: 62, baseType: !123, size: 64, align: 64)
!164 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !161, file: !6, line: 64, baseType: !80, size: 64, align: 64, offset: 64)
!165 = !DIDerivedType(tag: DW_TAG_member, name: "bid", scope: !161, file: !6, line: 66, baseType: !166, size: 64, align: 64, offset: 128)
!166 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !167, size: 64, align: 64)
!167 = !DISubroutineType(types: !168)
!168 = !{!23, !169, !170}
!169 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !161, size: 64, align: 64)
!170 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !171, size: 64, align: 64)
!171 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_filter", file: !6, line: 82, size: 1408, align: 64, elements: !172)
!172 = !{!173, !174, !175, !176, !177, !181, !185, !189, !193, !194, !198, !199, !200, !201, !202, !203, !204, !205, !206, !207, !208, !209, !210, !211}
!173 = !DIDerivedType(tag: DW_TAG_member, name: "position", scope: !171, file: !6, line: 83, baseType: !52, size: 64, align: 64)
!174 = !DIDerivedType(tag: DW_TAG_member, name: "bidder", scope: !171, file: !6, line: 86, baseType: !169, size: 64, align: 64, offset: 64)
!175 = !DIDerivedType(tag: DW_TAG_member, name: "upstream", scope: !171, file: !6, line: 87, baseType: !170, size: 64, align: 64, offset: 128)
!176 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !171, file: !6, line: 88, baseType: !4, size: 64, align: 64, offset: 192)
!177 = !DIDerivedType(tag: DW_TAG_member, name: "open", scope: !171, file: !6, line: 90, baseType: !178, size: 64, align: 64, offset: 256)
!178 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !179, size: 64, align: 64)
!179 = !DISubroutineType(types: !180)
!180 = !{!23, !170}
!181 = !DIDerivedType(tag: DW_TAG_member, name: "read", scope: !171, file: !6, line: 92, baseType: !182, size: 64, align: 64, offset: 320)
!182 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !183, size: 64, align: 64)
!183 = !DISubroutineType(types: !184)
!184 = !{!38, !170, !64}
!185 = !DIDerivedType(tag: DW_TAG_member, name: "skip", scope: !171, file: !6, line: 94, baseType: !186, size: 64, align: 64, offset: 384)
!186 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !187, size: 64, align: 64)
!187 = !DISubroutineType(types: !188)
!188 = !{!52, !170, !52}
!189 = !DIDerivedType(tag: DW_TAG_member, name: "seek", scope: !171, file: !6, line: 96, baseType: !190, size: 64, align: 64, offset: 448)
!190 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !191, size: 64, align: 64)
!191 = !DISubroutineType(types: !192)
!192 = !{!52, !170, !52, !23}
!193 = !DIDerivedType(tag: DW_TAG_member, name: "close", scope: !171, file: !6, line: 98, baseType: !178, size: 64, align: 64, offset: 512)
!194 = !DIDerivedType(tag: DW_TAG_member, name: "sswitch", scope: !171, file: !6, line: 100, baseType: !195, size: 64, align: 64, offset: 576)
!195 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !196, size: 64, align: 64)
!196 = !DISubroutineType(types: !197)
!197 = !{!23, !170, !13}
!198 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !171, file: !6, line: 102, baseType: !123, size: 64, align: 64, offset: 640)
!199 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !171, file: !6, line: 104, baseType: !80, size: 64, align: 64, offset: 704)
!200 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !171, file: !6, line: 105, baseType: !23, size: 32, align: 32, offset: 768)
!201 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !171, file: !6, line: 108, baseType: !95, size: 64, align: 64, offset: 832)
!202 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_size", scope: !171, file: !6, line: 109, baseType: !45, size: 64, align: 64, offset: 896)
!203 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !171, file: !6, line: 110, baseType: !95, size: 64, align: 64, offset: 960)
!204 = !DIDerivedType(tag: DW_TAG_member, name: "avail", scope: !171, file: !6, line: 111, baseType: !45, size: 64, align: 64, offset: 1024)
!205 = !DIDerivedType(tag: DW_TAG_member, name: "client_buff", scope: !171, file: !6, line: 112, baseType: !43, size: 64, align: 64, offset: 1088)
!206 = !DIDerivedType(tag: DW_TAG_member, name: "client_total", scope: !171, file: !6, line: 113, baseType: !45, size: 64, align: 64, offset: 1152)
!207 = !DIDerivedType(tag: DW_TAG_member, name: "client_next", scope: !171, file: !6, line: 114, baseType: !80, size: 64, align: 64, offset: 1216)
!208 = !DIDerivedType(tag: DW_TAG_member, name: "client_avail", scope: !171, file: !6, line: 115, baseType: !45, size: 64, align: 64, offset: 1280)
!209 = !DIDerivedType(tag: DW_TAG_member, name: "end_of_file", scope: !171, file: !6, line: 116, baseType: !82, size: 8, align: 8, offset: 1344)
!210 = !DIDerivedType(tag: DW_TAG_member, name: "closed", scope: !171, file: !6, line: 117, baseType: !82, size: 8, align: 8, offset: 1352)
!211 = !DIDerivedType(tag: DW_TAG_member, name: "fatal", scope: !171, file: !6, line: 118, baseType: !82, size: 8, align: 8, offset: 1360)
!212 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !161, file: !6, line: 69, baseType: !178, size: 64, align: 64, offset: 192)
!213 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !161, file: !6, line: 71, baseType: !214, size: 64, align: 64, offset: 256)
!214 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !215, size: 64, align: 64)
!215 = !DISubroutineType(types: !216)
!216 = !{!23, !169, !80, !80}
!217 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !161, file: !6, line: 74, baseType: !218, size: 64, align: 64, offset: 320)
!218 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !219, size: 64, align: 64)
!219 = !DISubroutineType(types: !220)
!220 = !{!23, !169}
!221 = !{!222}
!222 = !DISubrange(count: 16)
!223 = !DIDerivedType(tag: DW_TAG_member, name: "filter", scope: !5, file: !6, line: 176, baseType: !170, size: 64, align: 64, offset: 8256)
!224 = !DIDerivedType(tag: DW_TAG_member, name: "bypass_filter_bidding", scope: !5, file: !6, line: 179, baseType: !23, size: 32, align: 32, offset: 8320)
!225 = !DIDerivedType(tag: DW_TAG_member, name: "header_position", scope: !5, file: !6, line: 182, baseType: !52, size: 64, align: 64, offset: 8384)
!226 = !DIDerivedType(tag: DW_TAG_member, name: "data_start_node", scope: !5, file: !6, line: 185, baseType: !13, size: 32, align: 32, offset: 8448)
!227 = !DIDerivedType(tag: DW_TAG_member, name: "data_end_node", scope: !5, file: !6, line: 186, baseType: !13, size: 32, align: 32, offset: 8480)
!228 = !DIDerivedType(tag: DW_TAG_member, name: "formats", scope: !5, file: !6, line: 209, baseType: !229, size: 11264, align: 64, offset: 8512)
!229 = !DICompositeType(tag: DW_TAG_array_type, baseType: !230, size: 11264, align: 64, elements: !221)
!230 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_format_descriptor", file: !6, line: 196, size: 704, align: 64, elements: !231)
!231 = !{!232, !233, !234, !238, !242, !246, !250, !254, !258, !259, !260}
!232 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !230, file: !6, line: 197, baseType: !123, size: 64, align: 64)
!233 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !230, file: !6, line: 198, baseType: !80, size: 64, align: 64, offset: 64)
!234 = !DIDerivedType(tag: DW_TAG_member, name: "bid", scope: !230, file: !6, line: 199, baseType: !235, size: 64, align: 64, offset: 128)
!235 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !236, size: 64, align: 64)
!236 = !DISubroutineType(types: !237)
!237 = !{!23, !4, !23}
!238 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !230, file: !6, line: 200, baseType: !239, size: 64, align: 64, offset: 192)
!239 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !240, size: 64, align: 64)
!240 = !DISubroutineType(types: !241)
!241 = !{!23, !4, !80, !80}
!242 = !DIDerivedType(tag: DW_TAG_member, name: "read_header", scope: !230, file: !6, line: 202, baseType: !243, size: 64, align: 64, offset: 256)
!243 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !244, size: 64, align: 64)
!244 = !DISubroutineType(types: !245)
!245 = !{!23, !4, !30}
!246 = !DIDerivedType(tag: DW_TAG_member, name: "read_data", scope: !230, file: !6, line: 203, baseType: !247, size: 64, align: 64, offset: 320)
!247 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !248, size: 64, align: 64)
!248 = !DISubroutineType(types: !249)
!249 = !{!23, !4, !64, !65, !66}
!250 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_skip", scope: !230, file: !6, line: 204, baseType: !251, size: 64, align: 64, offset: 384)
!251 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !252, size: 64, align: 64)
!252 = !DISubroutineType(types: !253)
!253 = !{!23, !4}
!254 = !DIDerivedType(tag: DW_TAG_member, name: "seek_data", scope: !230, file: !6, line: 205, baseType: !255, size: 64, align: 64, offset: 448)
!255 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !256, size: 64, align: 64)
!256 = !DISubroutineType(types: !257)
!257 = !{!52, !4, !52, !23}
!258 = !DIDerivedType(tag: DW_TAG_member, name: "cleanup", scope: !230, file: !6, line: 206, baseType: !251, size: 64, align: 64, offset: 512)
!259 = !DIDerivedType(tag: DW_TAG_member, name: "format_capabilties", scope: !230, file: !6, line: 207, baseType: !251, size: 64, align: 64, offset: 576)
!260 = !DIDerivedType(tag: DW_TAG_member, name: "has_encrypted_entries", scope: !230, file: !6, line: 208, baseType: !251, size: 64, align: 64, offset: 640)
!261 = !DIDerivedType(tag: DW_TAG_member, name: "format", scope: !5, file: !6, line: 210, baseType: !262, size: 64, align: 64, offset: 19776)
!262 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !230, size: 64, align: 64)
!263 = !DIDerivedType(tag: DW_TAG_member, name: "extract", scope: !5, file: !6, line: 215, baseType: !264, size: 64, align: 64, offset: 19840)
!264 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !265, size: 64, align: 64)
!265 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_extract", file: !6, line: 151, size: 192, align: 64, elements: !266)
!266 = !{!267, !268, !272}
!267 = !DIDerivedType(tag: DW_TAG_member, name: "ad", scope: !265, file: !6, line: 152, baseType: !24, size: 64, align: 64)
!268 = !DIDerivedType(tag: DW_TAG_member, name: "extract_progress", scope: !265, file: !6, line: 155, baseType: !269, size: 64, align: 64, offset: 64)
!269 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !270, size: 64, align: 64)
!270 = !DISubroutineType(types: !271)
!271 = !{null, !123}
!272 = !DIDerivedType(tag: DW_TAG_member, name: "extract_progress_user_data", scope: !265, file: !6, line: 156, baseType: !123, size: 64, align: 64, offset: 128)
!273 = !DIDerivedType(tag: DW_TAG_member, name: "cleanup_archive_extract", scope: !5, file: !6, line: 216, baseType: !251, size: 64, align: 64, offset: 19904)
!274 = !DIDerivedType(tag: DW_TAG_member, name: "passphrases", scope: !5, file: !6, line: 227, baseType: !275, size: 320, align: 64, offset: 19968)
!275 = !DICompositeType(tag: DW_TAG_structure_type, scope: !5, file: !6, line: 221, size: 320, align: 64, elements: !276)
!276 = !{!277, !283, !285, !286, !291}
!277 = !DIDerivedType(tag: DW_TAG_member, name: "first", scope: !275, file: !6, line: 222, baseType: !278, size: 64, align: 64)
!278 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !279, size: 64, align: 64)
!279 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_passphrase", file: !6, line: 146, size: 128, align: 64, elements: !280)
!280 = !{!281, !282}
!281 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase", scope: !279, file: !6, line: 147, baseType: !95, size: 64, align: 64)
!282 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !279, file: !6, line: 148, baseType: !278, size: 64, align: 64, offset: 64)
!283 = !DIDerivedType(tag: DW_TAG_member, name: "last", scope: !275, file: !6, line: 223, baseType: !284, size: 64, align: 64, offset: 64)
!284 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !278, size: 64, align: 64)
!285 = !DIDerivedType(tag: DW_TAG_member, name: "candidate", scope: !275, file: !6, line: 224, baseType: !23, size: 32, align: 32, offset: 128)
!286 = !DIDerivedType(tag: DW_TAG_member, name: "callback", scope: !275, file: !6, line: 225, baseType: !287, size: 64, align: 64, offset: 192)
!287 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !288, size: 64, align: 64)
!288 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_passphrase_callback", file: !32, line: 256, baseType: !289)
!289 = !DISubroutineType(types: !290)
!290 = !{!80, !24, !123}
!291 = !DIDerivedType(tag: DW_TAG_member, name: "client_data", scope: !275, file: !6, line: 226, baseType: !123, size: 64, align: 64, offset: 256)
!292 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !293, size: 64, align: 64)
!293 = !DICompositeType(tag: DW_TAG_structure_type, name: "lha", file: !1, line: 148, size: 3328, align: 64, elements: !294)
!294 = !{!295, !296, !297, !298, !301, !302, !304, !308, !309, !310, !311, !315, !316, !317, !318, !319, !320, !323, !324, !325, !326, !327, !328, !329, !330, !331, !332, !333, !341, !342, !343, !344, !345, !346, !347, !348, !352}
!295 = !DIDerivedType(tag: DW_TAG_member, name: "entry_offset", scope: !293, file: !1, line: 150, baseType: !52, size: 64, align: 64)
!296 = !DIDerivedType(tag: DW_TAG_member, name: "entry_bytes_remaining", scope: !293, file: !1, line: 151, baseType: !52, size: 64, align: 64, offset: 64)
!297 = !DIDerivedType(tag: DW_TAG_member, name: "entry_unconsumed", scope: !293, file: !1, line: 152, baseType: !52, size: 64, align: 64, offset: 128)
!298 = !DIDerivedType(tag: DW_TAG_member, name: "entry_crc_calculated", scope: !293, file: !1, line: 153, baseType: !299, size: 16, align: 16, offset: 192)
!299 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint16_t", file: !53, line: 49, baseType: !300)
!300 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!301 = !DIDerivedType(tag: DW_TAG_member, name: "header_size", scope: !293, file: !1, line: 155, baseType: !45, size: 64, align: 64, offset: 256)
!302 = !DIDerivedType(tag: DW_TAG_member, name: "level", scope: !293, file: !1, line: 156, baseType: !303, size: 8, align: 8, offset: 320)
!303 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!304 = !DIDerivedType(tag: DW_TAG_member, name: "method", scope: !293, file: !1, line: 157, baseType: !305, size: 24, align: 8, offset: 328)
!305 = !DICompositeType(tag: DW_TAG_array_type, baseType: !82, size: 24, align: 8, elements: !306)
!306 = !{!307}
!307 = !DISubrange(count: 3)
!308 = !DIDerivedType(tag: DW_TAG_member, name: "compsize", scope: !293, file: !1, line: 158, baseType: !52, size: 64, align: 64, offset: 384)
!309 = !DIDerivedType(tag: DW_TAG_member, name: "origsize", scope: !293, file: !1, line: 159, baseType: !52, size: 64, align: 64, offset: 448)
!310 = !DIDerivedType(tag: DW_TAG_member, name: "setflag", scope: !293, file: !1, line: 160, baseType: !23, size: 32, align: 32, offset: 512)
!311 = !DIDerivedType(tag: DW_TAG_member, name: "birthtime", scope: !293, file: !1, line: 165, baseType: !312, size: 64, align: 64, offset: 576)
!312 = !DIDerivedType(tag: DW_TAG_typedef, name: "time_t", file: !313, line: 75, baseType: !314)
!313 = !DIFile(filename: "/usr/include/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!314 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !41, line: 139, baseType: !42)
!315 = !DIDerivedType(tag: DW_TAG_member, name: "birthtime_tv_nsec", scope: !293, file: !1, line: 166, baseType: !42, size: 64, align: 64, offset: 640)
!316 = !DIDerivedType(tag: DW_TAG_member, name: "mtime", scope: !293, file: !1, line: 167, baseType: !312, size: 64, align: 64, offset: 704)
!317 = !DIDerivedType(tag: DW_TAG_member, name: "mtime_tv_nsec", scope: !293, file: !1, line: 168, baseType: !42, size: 64, align: 64, offset: 768)
!318 = !DIDerivedType(tag: DW_TAG_member, name: "atime", scope: !293, file: !1, line: 169, baseType: !312, size: 64, align: 64, offset: 832)
!319 = !DIDerivedType(tag: DW_TAG_member, name: "atime_tv_nsec", scope: !293, file: !1, line: 170, baseType: !42, size: 64, align: 64, offset: 896)
!320 = !DIDerivedType(tag: DW_TAG_member, name: "mode", scope: !293, file: !1, line: 171, baseType: !321, size: 32, align: 32, offset: 960)
!321 = !DIDerivedType(tag: DW_TAG_typedef, name: "mode_t", file: !39, line: 70, baseType: !322)
!322 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !41, line: 129, baseType: !13)
!323 = !DIDerivedType(tag: DW_TAG_member, name: "uid", scope: !293, file: !1, line: 172, baseType: !52, size: 64, align: 64, offset: 1024)
!324 = !DIDerivedType(tag: DW_TAG_member, name: "gid", scope: !293, file: !1, line: 173, baseType: !52, size: 64, align: 64, offset: 1088)
!325 = !DIDerivedType(tag: DW_TAG_member, name: "uname", scope: !293, file: !1, line: 174, baseType: !91, size: 192, align: 64, offset: 1152)
!326 = !DIDerivedType(tag: DW_TAG_member, name: "gname", scope: !293, file: !1, line: 175, baseType: !91, size: 192, align: 64, offset: 1344)
!327 = !DIDerivedType(tag: DW_TAG_member, name: "header_crc", scope: !293, file: !1, line: 176, baseType: !299, size: 16, align: 16, offset: 1536)
!328 = !DIDerivedType(tag: DW_TAG_member, name: "crc", scope: !293, file: !1, line: 177, baseType: !299, size: 16, align: 16, offset: 1552)
!329 = !DIDerivedType(tag: DW_TAG_member, name: "sconv", scope: !293, file: !1, line: 178, baseType: !102, size: 64, align: 64, offset: 1600)
!330 = !DIDerivedType(tag: DW_TAG_member, name: "opt_sconv", scope: !293, file: !1, line: 179, baseType: !102, size: 64, align: 64, offset: 1664)
!331 = !DIDerivedType(tag: DW_TAG_member, name: "dirname", scope: !293, file: !1, line: 181, baseType: !91, size: 192, align: 64, offset: 1728)
!332 = !DIDerivedType(tag: DW_TAG_member, name: "filename", scope: !293, file: !1, line: 182, baseType: !91, size: 192, align: 64, offset: 1920)
!333 = !DIDerivedType(tag: DW_TAG_member, name: "ws", scope: !293, file: !1, line: 183, baseType: !334, size: 192, align: 64, offset: 2112)
!334 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_wstring", file: !92, line: 64, size: 192, align: 64, elements: !335)
!335 = !{!336, !339, !340}
!336 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !334, file: !92, line: 65, baseType: !337, size: 64, align: 64)
!337 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !338, size: 64, align: 64)
!338 = !DIDerivedType(tag: DW_TAG_typedef, name: "wchar_t", file: !46, line: 90, baseType: !23)
!339 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !334, file: !92, line: 66, baseType: !45, size: 64, align: 64, offset: 64)
!340 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !334, file: !92, line: 67, baseType: !45, size: 64, align: 64, offset: 128)
!341 = !DIDerivedType(tag: DW_TAG_member, name: "dos_attr", scope: !293, file: !1, line: 185, baseType: !303, size: 8, align: 8, offset: 2304)
!342 = !DIDerivedType(tag: DW_TAG_member, name: "found_first_header", scope: !293, file: !1, line: 188, baseType: !82, size: 8, align: 8, offset: 2312)
!343 = !DIDerivedType(tag: DW_TAG_member, name: "directory", scope: !293, file: !1, line: 190, baseType: !82, size: 8, align: 8, offset: 2320)
!344 = !DIDerivedType(tag: DW_TAG_member, name: "decompress_init", scope: !293, file: !1, line: 193, baseType: !82, size: 8, align: 8, offset: 2328)
!345 = !DIDerivedType(tag: DW_TAG_member, name: "end_of_entry", scope: !293, file: !1, line: 194, baseType: !82, size: 8, align: 8, offset: 2336)
!346 = !DIDerivedType(tag: DW_TAG_member, name: "end_of_entry_cleanup", scope: !293, file: !1, line: 195, baseType: !82, size: 8, align: 8, offset: 2344)
!347 = !DIDerivedType(tag: DW_TAG_member, name: "entry_is_compressed", scope: !293, file: !1, line: 196, baseType: !82, size: 8, align: 8, offset: 2352)
!348 = !DIDerivedType(tag: DW_TAG_member, name: "format_name", scope: !293, file: !1, line: 198, baseType: !349, size: 512, align: 8, offset: 2360)
!349 = !DICompositeType(tag: DW_TAG_array_type, baseType: !82, size: 512, align: 8, elements: !350)
!350 = !{!351}
!351 = !DISubrange(count: 64)
!352 = !DIDerivedType(tag: DW_TAG_member, name: "strm", scope: !293, file: !1, line: 200, baseType: !353, size: 448, align: 64, offset: 2880)
!353 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzh_stream", file: !1, line: 138, size: 448, align: 64, elements: !354)
!354 = !{!355, !358, !359, !360, !361, !362, !363}
!355 = !DIDerivedType(tag: DW_TAG_member, name: "next_in", scope: !353, file: !1, line: 139, baseType: !356, size: 64, align: 64)
!356 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !357, size: 64, align: 64)
!357 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !303)
!358 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in", scope: !353, file: !1, line: 140, baseType: !23, size: 32, align: 32, offset: 64)
!359 = !DIDerivedType(tag: DW_TAG_member, name: "total_in", scope: !353, file: !1, line: 141, baseType: !52, size: 64, align: 64, offset: 128)
!360 = !DIDerivedType(tag: DW_TAG_member, name: "ref_ptr", scope: !353, file: !1, line: 142, baseType: !356, size: 64, align: 64, offset: 192)
!361 = !DIDerivedType(tag: DW_TAG_member, name: "avail_out", scope: !353, file: !1, line: 143, baseType: !23, size: 32, align: 32, offset: 256)
!362 = !DIDerivedType(tag: DW_TAG_member, name: "total_out", scope: !353, file: !1, line: 144, baseType: !52, size: 64, align: 64, offset: 320)
!363 = !DIDerivedType(tag: DW_TAG_member, name: "ds", scope: !353, file: !1, line: 145, baseType: !364, size: 64, align: 64, offset: 384)
!364 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !365, size: 64, align: 64)
!365 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzh_dec", file: !1, line: 66, size: 2752, align: 64, elements: !366)
!366 = !{!367, !368, !369, !370, !372, !373, !374, !375, !381, !405, !406, !407, !408, !409, !410, !411, !412, !413}
!367 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !365, file: !1, line: 68, baseType: !23, size: 32, align: 32)
!368 = !DIDerivedType(tag: DW_TAG_member, name: "w_size", scope: !365, file: !1, line: 74, baseType: !23, size: 32, align: 32, offset: 32)
!369 = !DIDerivedType(tag: DW_TAG_member, name: "w_mask", scope: !365, file: !1, line: 75, baseType: !23, size: 32, align: 32, offset: 64)
!370 = !DIDerivedType(tag: DW_TAG_member, name: "w_buff", scope: !365, file: !1, line: 77, baseType: !371, size: 64, align: 64, offset: 128)
!371 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !303, size: 64, align: 64)
!372 = !DIDerivedType(tag: DW_TAG_member, name: "w_pos", scope: !365, file: !1, line: 79, baseType: !23, size: 32, align: 32, offset: 192)
!373 = !DIDerivedType(tag: DW_TAG_member, name: "copy_pos", scope: !365, file: !1, line: 81, baseType: !23, size: 32, align: 32, offset: 224)
!374 = !DIDerivedType(tag: DW_TAG_member, name: "copy_len", scope: !365, file: !1, line: 84, baseType: !23, size: 32, align: 32, offset: 256)
!375 = !DIDerivedType(tag: DW_TAG_member, name: "br", scope: !365, file: !1, line: 96, baseType: !376, size: 128, align: 64, offset: 320)
!376 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzh_br", file: !1, line: 89, size: 128, align: 64, elements: !377)
!377 = !{!378, !380}
!378 = !DIDerivedType(tag: DW_TAG_member, name: "cache_buffer", scope: !376, file: !1, line: 93, baseType: !379, size: 64, align: 64)
!379 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !53, line: 55, baseType: !47)
!380 = !DIDerivedType(tag: DW_TAG_member, name: "cache_avail", scope: !376, file: !1, line: 95, baseType: !23, size: 32, align: 32, offset: 64)
!381 = !DIDerivedType(tag: DW_TAG_member, name: "lt", scope: !365, file: !1, line: 126, baseType: !382, size: 1024, align: 64, offset: 448)
!382 = !DICompositeType(tag: DW_TAG_structure_type, name: "huffman", file: !1, line: 101, size: 1024, align: 64, elements: !383)
!383 = !{!384, !385, !386, !387, !391, !392, !393, !394, !395, !396, !397, !399}
!384 = !DIDerivedType(tag: DW_TAG_member, name: "len_size", scope: !382, file: !1, line: 102, baseType: !23, size: 32, align: 32)
!385 = !DIDerivedType(tag: DW_TAG_member, name: "len_avail", scope: !382, file: !1, line: 103, baseType: !23, size: 32, align: 32, offset: 32)
!386 = !DIDerivedType(tag: DW_TAG_member, name: "len_bits", scope: !382, file: !1, line: 104, baseType: !23, size: 32, align: 32, offset: 64)
!387 = !DIDerivedType(tag: DW_TAG_member, name: "freq", scope: !382, file: !1, line: 105, baseType: !388, size: 544, align: 32, offset: 96)
!388 = !DICompositeType(tag: DW_TAG_array_type, baseType: !23, size: 544, align: 32, elements: !389)
!389 = !{!390}
!390 = !DISubrange(count: 17)
!391 = !DIDerivedType(tag: DW_TAG_member, name: "bitlen", scope: !382, file: !1, line: 106, baseType: !371, size: 64, align: 64, offset: 640)
!392 = !DIDerivedType(tag: DW_TAG_member, name: "max_bits", scope: !382, file: !1, line: 114, baseType: !23, size: 32, align: 32, offset: 704)
!393 = !DIDerivedType(tag: DW_TAG_member, name: "shift_bits", scope: !382, file: !1, line: 115, baseType: !23, size: 32, align: 32, offset: 736)
!394 = !DIDerivedType(tag: DW_TAG_member, name: "tbl_bits", scope: !382, file: !1, line: 116, baseType: !23, size: 32, align: 32, offset: 768)
!395 = !DIDerivedType(tag: DW_TAG_member, name: "tree_used", scope: !382, file: !1, line: 117, baseType: !23, size: 32, align: 32, offset: 800)
!396 = !DIDerivedType(tag: DW_TAG_member, name: "tree_avail", scope: !382, file: !1, line: 118, baseType: !23, size: 32, align: 32, offset: 832)
!397 = !DIDerivedType(tag: DW_TAG_member, name: "tbl", scope: !382, file: !1, line: 120, baseType: !398, size: 64, align: 64, offset: 896)
!398 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !299, size: 64, align: 64)
!399 = !DIDerivedType(tag: DW_TAG_member, name: "tree", scope: !382, file: !1, line: 125, baseType: !400, size: 64, align: 64, offset: 960)
!400 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !401, size: 64, align: 64)
!401 = !DICompositeType(tag: DW_TAG_structure_type, name: "htree_t", file: !1, line: 122, size: 32, align: 16, elements: !402)
!402 = !{!403, !404}
!403 = !DIDerivedType(tag: DW_TAG_member, name: "left", scope: !401, file: !1, line: 123, baseType: !299, size: 16, align: 16)
!404 = !DIDerivedType(tag: DW_TAG_member, name: "right", scope: !401, file: !1, line: 124, baseType: !299, size: 16, align: 16, offset: 16)
!405 = !DIDerivedType(tag: DW_TAG_member, name: "pt", scope: !365, file: !1, line: 126, baseType: !382, size: 1024, align: 64, offset: 1472)
!406 = !DIDerivedType(tag: DW_TAG_member, name: "blocks_avail", scope: !365, file: !1, line: 128, baseType: !23, size: 32, align: 32, offset: 2496)
!407 = !DIDerivedType(tag: DW_TAG_member, name: "pos_pt_len_size", scope: !365, file: !1, line: 129, baseType: !23, size: 32, align: 32, offset: 2528)
!408 = !DIDerivedType(tag: DW_TAG_member, name: "pos_pt_len_bits", scope: !365, file: !1, line: 130, baseType: !23, size: 32, align: 32, offset: 2560)
!409 = !DIDerivedType(tag: DW_TAG_member, name: "literal_pt_len_size", scope: !365, file: !1, line: 131, baseType: !23, size: 32, align: 32, offset: 2592)
!410 = !DIDerivedType(tag: DW_TAG_member, name: "literal_pt_len_bits", scope: !365, file: !1, line: 132, baseType: !23, size: 32, align: 32, offset: 2624)
!411 = !DIDerivedType(tag: DW_TAG_member, name: "reading_position", scope: !365, file: !1, line: 133, baseType: !23, size: 32, align: 32, offset: 2656)
!412 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !365, file: !1, line: 134, baseType: !23, size: 32, align: 32, offset: 2688)
!413 = !DIDerivedType(tag: DW_TAG_member, name: "error", scope: !365, file: !1, line: 135, baseType: !23, size: 32, align: 32, offset: 2720)
!414 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !53, line: 122, baseType: !47)
!415 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !416, size: 64, align: 64)
!416 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !299)
!417 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !53, line: 51, baseType: !13)
!418 = !{!419, !420, !421, !424, !425, !426, !429, !430, !431, !434, !438, !441, !444, !447, !448, !451, !454, !458, !461, !462, !463, !467, !470, !471, !472, !473, !477, !481, !484, !485, !489, !492, !495, !498, !501, !504, !507, !508, !509, !510, !511, !514}
!419 = distinct !DISubprogram(name: "archive_read_support_format_lha", scope: !1, file: !1, line: 257, type: !21, isLocal: false, isDefinition: true, scopeLine: 258, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!420 = distinct !DISubprogram(name: "archive_read_format_lha_bid", scope: !1, file: !1, line: 346, type: !236, isLocal: true, isDefinition: true, scopeLine: 347, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!421 = distinct !DISubprogram(name: "lha_check_header_format", scope: !1, file: !1, line: 293, type: !422, isLocal: true, isDefinition: true, scopeLine: 294, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!422 = !DISubroutineType(types: !423)
!423 = !{!45, !43}
!424 = distinct !DISubprogram(name: "archive_read_format_lha_options", scope: !1, file: !1, line: 391, type: !240, isLocal: true, isDefinition: true, scopeLine: 393, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!425 = distinct !DISubprogram(name: "archive_read_format_lha_read_header", scope: !1, file: !1, line: 473, type: !244, isLocal: true, isDefinition: true, scopeLine: 475, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!426 = distinct !DISubprogram(name: "lha_crc16_init", scope: !1, file: !1, line: 1668, type: !427, isLocal: true, isDefinition: true, scopeLine: 1669, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!427 = !DISubroutineType(types: !428)
!428 = !{null}
!429 = distinct !DISubprogram(name: "truncated_error", scope: !1, file: !1, line: 465, type: !252, isLocal: true, isDefinition: true, scopeLine: 466, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!430 = distinct !DISubprogram(name: "lha_skip_sfx", scope: !1, file: !1, line: 421, type: !252, isLocal: true, isDefinition: true, scopeLine: 422, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!431 = distinct !DISubprogram(name: "lha_read_file_header_0", scope: !1, file: !1, line: 781, type: !432, isLocal: true, isDefinition: true, scopeLine: 782, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!432 = !DISubroutineType(types: !433)
!433 = !{!23, !4, !292}
!434 = distinct !DISubprogram(name: "archive_le32dec", scope: !435, file: !435, line: 115, type: !436, isLocal: true, isDefinition: true, scopeLine: 116, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!435 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_endian.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!436 = !DISubroutineType(types: !437)
!437 = !{!417, !43}
!438 = distinct !DISubprogram(name: "lha_dos_time", scope: !1, file: !1, line: 1618, type: !439, isLocal: true, isDefinition: true, scopeLine: 1619, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!439 = !DISubroutineType(types: !440)
!440 = !{!312, !356}
!441 = distinct !DISubprogram(name: "archive_le16dec", scope: !435, file: !435, line: 101, type: !442, isLocal: true, isDefinition: true, scopeLine: 102, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!442 = !DISubroutineType(types: !443)
!443 = !{!299, !43}
!444 = distinct !DISubprogram(name: "lha_calcsum", scope: !1, file: !1, line: 1656, type: !445, isLocal: true, isDefinition: true, scopeLine: 1657, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!445 = !DISubroutineType(types: !446)
!446 = !{!303, !303, !43, !23, !45}
!447 = distinct !DISubprogram(name: "lha_read_file_header_1", scope: !1, file: !1, line: 875, type: !432, isLocal: true, isDefinition: true, scopeLine: 876, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!448 = distinct !DISubprogram(name: "lha_read_file_extended_header", scope: !1, file: !1, line: 1107, type: !449, isLocal: true, isDefinition: true, scopeLine: 1109, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!449 = !DISubroutineType(types: !450)
!450 = !{!23, !4, !292, !398, !23, !45, !65}
!451 = distinct !DISubprogram(name: "lha_crc16", scope: !1, file: !1, line: 1692, type: !452, isLocal: true, isDefinition: true, scopeLine: 1693, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!452 = !DISubroutineType(types: !453)
!453 = !{!299, !299, !43, !45}
!454 = distinct !DISubprogram(name: "lha_win_time", scope: !1, file: !1, line: 1639, type: !455, isLocal: true, isDefinition: true, scopeLine: 1640, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!455 = !DISubroutineType(types: !456)
!456 = !{!312, !379, !457}
!457 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !42, size: 64, align: 64)
!458 = distinct !DISubprogram(name: "archive_le64dec", scope: !435, file: !435, line: 131, type: !459, isLocal: true, isDefinition: true, scopeLine: 132, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!459 = !DISubroutineType(types: !460)
!460 = !{!379, !43}
!461 = distinct !DISubprogram(name: "lha_read_file_header_2", scope: !1, file: !1, line: 971, type: !432, isLocal: true, isDefinition: true, scopeLine: 972, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!462 = distinct !DISubprogram(name: "lha_read_file_header_3", scope: !1, file: !1, line: 1050, type: !432, isLocal: true, isDefinition: true, scopeLine: 1051, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!463 = distinct !DISubprogram(name: "lha_parse_linkname", scope: !1, file: !1, line: 1597, type: !464, isLocal: true, isDefinition: true, scopeLine: 1599, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!464 = !DISubroutineType(types: !465)
!465 = !{!23, !466, !466}
!466 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !91, size: 64, align: 64)
!467 = distinct !DISubprogram(name: "lha_replace_path_separator", scope: !1, file: !1, line: 725, type: !468, isLocal: true, isDefinition: true, scopeLine: 726, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!468 = !DISubroutineType(types: !469)
!469 = !{null, !292, !30}
!470 = distinct !DISubprogram(name: "archive_read_format_lha_read_data", scope: !1, file: !1, line: 1368, type: !248, isLocal: true, isDefinition: true, scopeLine: 1370, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!471 = distinct !DISubprogram(name: "lha_end_of_entry", scope: !1, file: !1, line: 1348, type: !252, isLocal: true, isDefinition: true, scopeLine: 1349, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!472 = distinct !DISubprogram(name: "lha_read_data_lzh", scope: !1, file: !1, line: 1448, type: !248, isLocal: true, isDefinition: true, scopeLine: 1450, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!473 = distinct !DISubprogram(name: "lzh_decode_init", scope: !1, file: !1, line: 1764, type: !474, isLocal: true, isDefinition: true, scopeLine: 1765, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!474 = !DISubroutineType(types: !475)
!475 = !{!23, !476, !80}
!476 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !353, size: 64, align: 64)
!477 = distinct !DISubprogram(name: "lzh_huffman_init", scope: !1, file: !1, line: 2446, type: !478, isLocal: true, isDefinition: true, scopeLine: 2447, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!478 = !DISubroutineType(types: !479)
!479 = !{!23, !480, !45, !23}
!480 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !382, size: 64, align: 64)
!481 = distinct !DISubprogram(name: "lzh_decode", scope: !1, file: !1, line: 1992, type: !482, isLocal: true, isDefinition: true, scopeLine: 1993, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!482 = !DISubroutineType(types: !483)
!483 = !{!23, !476, !23}
!484 = distinct !DISubprogram(name: "lzh_read_blocks", scope: !1, file: !1, line: 2021, type: !482, isLocal: true, isDefinition: true, scopeLine: 2022, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!485 = distinct !DISubprogram(name: "lzh_br_fillup", scope: !1, file: !1, line: 1885, type: !486, isLocal: true, isDefinition: true, scopeLine: 1886, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!486 = !DISubroutineType(types: !487)
!487 = !{!23, !476, !488}
!488 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !376, size: 64, align: 64)
!489 = distinct !DISubprogram(name: "lzh_emit_window", scope: !1, file: !1, line: 2013, type: !490, isLocal: true, isDefinition: true, scopeLine: 2014, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!490 = !DISubroutineType(types: !491)
!491 = !{null, !476, !45}
!492 = distinct !DISubprogram(name: "lzh_make_fake_table", scope: !1, file: !1, line: 2588, type: !493, isLocal: true, isDefinition: true, scopeLine: 2589, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!493 = !DISubroutineType(types: !494)
!494 = !{!23, !480, !299}
!495 = distinct !DISubprogram(name: "lzh_read_pt_bitlen", scope: !1, file: !1, line: 2550, type: !496, isLocal: true, isDefinition: true, scopeLine: 2551, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!496 = !DISubroutineType(types: !497)
!497 = !{!23, !476, !23, !23}
!498 = distinct !DISubprogram(name: "lzh_make_huffman_table", scope: !1, file: !1, line: 2603, type: !499, isLocal: true, isDefinition: true, scopeLine: 2604, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!499 = !DISubroutineType(types: !500)
!500 = !{!23, !480}
!501 = distinct !DISubprogram(name: "lzh_decode_huffman", scope: !1, file: !1, line: 2804, type: !502, isLocal: true, isDefinition: true, scopeLine: 2805, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!502 = !DISubroutineType(types: !503)
!503 = !{!23, !480, !13}
!504 = distinct !DISubprogram(name: "lzh_decode_huffman_tree", scope: !1, file: !1, line: 2784, type: !505, isLocal: true, isDefinition: true, scopeLine: 2785, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!505 = !DISubroutineType(types: !506)
!506 = !{!23, !480, !13, !23}
!507 = distinct !DISubprogram(name: "lzh_decode_blocks", scope: !1, file: !1, line: 2256, type: !482, isLocal: true, isDefinition: true, scopeLine: 2257, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!508 = distinct !DISubprogram(name: "lha_read_data_none", scope: !1, file: !1, line: 1401, type: !248, isLocal: true, isDefinition: true, scopeLine: 1403, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!509 = distinct !DISubprogram(name: "archive_read_format_lha_read_data_skip", scope: !1, file: !1, line: 1540, type: !252, isLocal: true, isDefinition: true, scopeLine: 1541, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!510 = distinct !DISubprogram(name: "archive_read_format_lha_cleanup", scope: !1, file: !1, line: 1571, type: !252, isLocal: true, isDefinition: true, scopeLine: 1572, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!511 = distinct !DISubprogram(name: "lzh_decode_free", scope: !1, file: !1, line: 1828, type: !512, isLocal: true, isDefinition: true, scopeLine: 1829, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!512 = !DISubroutineType(types: !513)
!513 = !{null, !476}
!514 = distinct !DISubprogram(name: "lzh_huffman_free", scope: !1, file: !1, line: 2476, type: !515, isLocal: true, isDefinition: true, scopeLine: 2477, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!515 = !DISubroutineType(types: !516)
!516 = !{null, !480}
!517 = !{!518, !519, !524, !527, !536, !540}
!518 = !DIGlobalVariable(name: "crc16init", scope: !426, file: !1, line: 1671, type: !23, isLocal: true, isDefinition: true, variable: i32* @lha_crc16_init.crc16init)
!519 = !DIGlobalVariable(name: "crc16tbl", scope: !0, file: !1, line: 1666, type: !520, isLocal: true, isDefinition: true, variable: [2 x [256 x i16]]* @crc16tbl)
!520 = !DICompositeType(tag: DW_TAG_array_type, baseType: !299, size: 8192, align: 16, elements: !521)
!521 = !{!522, !523}
!522 = !DISubrange(count: 2)
!523 = !DISubrange(count: 256)
!524 = !DIGlobalVariable(name: "zeros", scope: !448, file: !1, line: 1184, type: !525, isLocal: true, isDefinition: true, variable: [2 x i8]* @lha_read_file_extended_header.zeros)
!525 = !DICompositeType(tag: DW_TAG_array_type, baseType: !81, size: 16, align: 8, elements: !526)
!526 = !{!522}
!527 = !DIGlobalVariable(name: "u", scope: !451, file: !1, line: 1699, type: !528, isLocal: true, isDefinition: true, variable: %union.anon* @lha_crc16.u)
!528 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !529)
!529 = !DICompositeType(tag: DW_TAG_union_type, scope: !451, file: !1, line: 1696, size: 32, align: 32, elements: !530)
!530 = !{!531, !532}
!531 = !DIDerivedType(tag: DW_TAG_member, name: "i", scope: !529, file: !1, line: 1697, baseType: !417, size: 32, align: 32)
!532 = !DIDerivedType(tag: DW_TAG_member, name: "c", scope: !529, file: !1, line: 1698, baseType: !533, size: 32, align: 8)
!533 = !DICompositeType(tag: DW_TAG_array_type, baseType: !82, size: 32, align: 8, elements: !534)
!534 = !{!535}
!535 = !DISubrange(count: 4)
!536 = !DIGlobalVariable(name: "cache_masks", scope: !0, file: !1, line: 1869, type: !537, isLocal: true, isDefinition: true, variable: [20 x i16]* @cache_masks)
!537 = !DICompositeType(tag: DW_TAG_array_type, baseType: !416, size: 320, align: 16, elements: !538)
!538 = !{!539}
!539 = !DISubrange(count: 20)
!540 = !DIGlobalVariable(name: "bitlen_tbl", scope: !0, file: !1, line: 2483, type: !541, isLocal: true, isDefinition: true, variable: [1024 x i8]* @bitlen_tbl)
!541 = !DICompositeType(tag: DW_TAG_array_type, baseType: !82, size: 8192, align: 8, elements: !542)
!542 = !{!543}
!543 = !DISubrange(count: 1024)
!544 = !{i32 2, !"Dwarf Version", i32 4}
!545 = !{i32 2, !"Debug Info Version", i32 3}
!546 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!547 = !DILocalVariable(name: "_a", arg: 1, scope: !419, file: !1, line: 257, type: !24)
!548 = !DIExpression()
!549 = !DILocation(line: 257, column: 49, scope: !419)
!550 = !DILocalVariable(name: "a", scope: !419, file: !1, line: 259, type: !4)
!551 = !DILocation(line: 259, column: 23, scope: !419)
!552 = !DILocation(line: 259, column: 50, scope: !419)
!553 = !DILocation(line: 259, column: 27, scope: !419)
!554 = !DILocalVariable(name: "lha", scope: !419, file: !1, line: 260, type: !292)
!555 = !DILocation(line: 260, column: 14, scope: !419)
!556 = !DILocalVariable(name: "r", scope: !419, file: !1, line: 261, type: !23)
!557 = !DILocation(line: 261, column: 6, scope: !419)
!558 = !DILocation(line: 263, column: 2, scope: !419)
!559 = !DILocalVariable(name: "magic_test", scope: !560, file: !1, line: 263, type: !23)
!560 = distinct !DILexicalBlock(scope: !419, file: !1, line: 263, column: 2)
!561 = !DILocation(line: 263, column: 2, scope: !560)
!562 = !DILocation(line: 263, column: 2, scope: !563)
!563 = !DILexicalBlockFile(scope: !560, file: !1, discriminator: 1)
!564 = !DILocation(line: 263, column: 2, scope: !565)
!565 = !DILexicalBlockFile(scope: !566, file: !1, discriminator: 2)
!566 = distinct !DILexicalBlock(scope: !560, file: !1, line: 263, column: 2)
!567 = !DILocation(line: 263, column: 2, scope: !568)
!568 = !DILexicalBlockFile(scope: !560, file: !1, discriminator: 3)
!569 = !DILocation(line: 266, column: 22, scope: !419)
!570 = !DILocation(line: 266, column: 8, scope: !419)
!571 = !DILocation(line: 266, column: 6, scope: !419)
!572 = !DILocation(line: 267, column: 6, scope: !573)
!573 = distinct !DILexicalBlock(scope: !419, file: !1, line: 267, column: 6)
!574 = !DILocation(line: 267, column: 10, scope: !573)
!575 = !DILocation(line: 267, column: 6, scope: !419)
!576 = !DILocation(line: 268, column: 22, scope: !577)
!577 = distinct !DILexicalBlock(scope: !573, file: !1, line: 267, column: 19)
!578 = !DILocation(line: 268, column: 25, scope: !577)
!579 = !DILocation(line: 268, column: 3, scope: !577)
!580 = !DILocation(line: 270, column: 3, scope: !577)
!581 = !DILocation(line: 272, column: 2, scope: !419)
!582 = !DILocation(line: 272, column: 2, scope: !583)
!583 = !DILexicalBlockFile(scope: !584, file: !1, discriminator: 1)
!584 = distinct !DILexicalBlock(scope: !419, file: !1, line: 272, column: 2)
!585 = !DILocation(line: 274, column: 37, scope: !419)
!586 = !DILocation(line: 275, column: 6, scope: !419)
!587 = !DILocation(line: 274, column: 6, scope: !419)
!588 = !DILocation(line: 274, column: 4, scope: !419)
!589 = !DILocation(line: 287, column: 6, scope: !590)
!590 = distinct !DILexicalBlock(scope: !419, file: !1, line: 287, column: 6)
!591 = !DILocation(line: 287, column: 8, scope: !590)
!592 = !DILocation(line: 287, column: 6, scope: !419)
!593 = !DILocation(line: 288, column: 8, scope: !590)
!594 = !DILocation(line: 288, column: 3, scope: !590)
!595 = !DILocation(line: 289, column: 2, scope: !419)
!596 = !DILocation(line: 290, column: 1, scope: !419)
!597 = !DILocalVariable(name: "a", arg: 1, scope: !420, file: !1, line: 346, type: !4)
!598 = !DILocation(line: 346, column: 50, scope: !420)
!599 = !DILocalVariable(name: "best_bid", arg: 2, scope: !420, file: !1, line: 346, type: !23)
!600 = !DILocation(line: 346, column: 57, scope: !420)
!601 = !DILocalVariable(name: "p", scope: !420, file: !1, line: 348, type: !80)
!602 = !DILocation(line: 348, column: 14, scope: !420)
!603 = !DILocalVariable(name: "buff", scope: !420, file: !1, line: 349, type: !43)
!604 = !DILocation(line: 349, column: 14, scope: !420)
!605 = !DILocalVariable(name: "bytes_avail", scope: !420, file: !1, line: 350, type: !38)
!606 = !DILocation(line: 350, column: 10, scope: !420)
!607 = !DILocalVariable(name: "offset", scope: !420, file: !1, line: 350, type: !38)
!608 = !DILocation(line: 350, column: 23, scope: !420)
!609 = !DILocalVariable(name: "window", scope: !420, file: !1, line: 350, type: !38)
!610 = !DILocation(line: 350, column: 31, scope: !420)
!611 = !DILocalVariable(name: "next", scope: !420, file: !1, line: 351, type: !45)
!612 = !DILocation(line: 351, column: 9, scope: !420)
!613 = !DILocation(line: 355, column: 6, scope: !614)
!614 = distinct !DILexicalBlock(scope: !420, file: !1, line: 355, column: 6)
!615 = !DILocation(line: 355, column: 15, scope: !614)
!616 = !DILocation(line: 355, column: 6, scope: !420)
!617 = !DILocation(line: 356, column: 3, scope: !614)
!618 = !DILocation(line: 358, column: 32, scope: !619)
!619 = distinct !DILexicalBlock(scope: !420, file: !1, line: 358, column: 6)
!620 = !DILocation(line: 358, column: 11, scope: !619)
!621 = !DILocation(line: 358, column: 9, scope: !619)
!622 = !DILocation(line: 358, column: 50, scope: !619)
!623 = !DILocation(line: 358, column: 6, scope: !420)
!624 = !DILocation(line: 359, column: 3, scope: !619)
!625 = !DILocation(line: 361, column: 30, scope: !626)
!626 = distinct !DILexicalBlock(scope: !420, file: !1, line: 361, column: 6)
!627 = !DILocation(line: 361, column: 6, scope: !626)
!628 = !DILocation(line: 361, column: 33, scope: !626)
!629 = !DILocation(line: 361, column: 6, scope: !420)
!630 = !DILocation(line: 362, column: 3, scope: !626)
!631 = !DILocation(line: 364, column: 6, scope: !632)
!632 = distinct !DILexicalBlock(scope: !420, file: !1, line: 364, column: 6)
!633 = !DILocation(line: 364, column: 11, scope: !632)
!634 = !DILocation(line: 364, column: 18, scope: !632)
!635 = !DILocation(line: 364, column: 21, scope: !636)
!636 = !DILexicalBlockFile(scope: !632, file: !1, discriminator: 1)
!637 = !DILocation(line: 364, column: 26, scope: !636)
!638 = !DILocation(line: 364, column: 6, scope: !636)
!639 = !DILocation(line: 366, column: 10, scope: !640)
!640 = distinct !DILexicalBlock(scope: !632, file: !1, line: 364, column: 34)
!641 = !DILocation(line: 367, column: 10, scope: !640)
!642 = !DILocation(line: 368, column: 3, scope: !640)
!643 = !DILocation(line: 368, column: 10, scope: !644)
!644 = !DILexicalBlockFile(scope: !640, file: !1, discriminator: 1)
!645 = !DILocation(line: 368, column: 17, scope: !644)
!646 = !DILocation(line: 368, column: 3, scope: !644)
!647 = !DILocation(line: 369, column: 32, scope: !648)
!648 = distinct !DILexicalBlock(scope: !640, file: !1, line: 368, column: 32)
!649 = !DILocation(line: 369, column: 35, scope: !648)
!650 = !DILocation(line: 369, column: 44, scope: !648)
!651 = !DILocation(line: 369, column: 42, scope: !648)
!652 = !DILocation(line: 369, column: 11, scope: !648)
!653 = !DILocation(line: 369, column: 9, scope: !648)
!654 = !DILocation(line: 371, column: 8, scope: !655)
!655 = distinct !DILexicalBlock(scope: !648, file: !1, line: 371, column: 8)
!656 = !DILocation(line: 371, column: 13, scope: !655)
!657 = !DILocation(line: 371, column: 8, scope: !648)
!658 = !DILocation(line: 373, column: 12, scope: !659)
!659 = distinct !DILexicalBlock(scope: !655, file: !1, line: 371, column: 22)
!660 = !DILocation(line: 374, column: 9, scope: !661)
!661 = distinct !DILexicalBlock(scope: !659, file: !1, line: 374, column: 9)
!662 = !DILocation(line: 374, column: 16, scope: !661)
!663 = !DILocation(line: 374, column: 9, scope: !659)
!664 = !DILocation(line: 375, column: 6, scope: !661)
!665 = !DILocation(line: 376, column: 5, scope: !659)
!666 = !DILocation(line: 378, column: 22, scope: !648)
!667 = !DILocation(line: 378, column: 29, scope: !648)
!668 = !DILocation(line: 378, column: 27, scope: !648)
!669 = !DILocation(line: 378, column: 6, scope: !648)
!670 = !DILocation(line: 379, column: 4, scope: !648)
!671 = !DILocation(line: 379, column: 11, scope: !672)
!672 = !DILexicalBlockFile(scope: !648, file: !1, discriminator: 1)
!673 = !DILocation(line: 379, column: 13, scope: !672)
!674 = !DILocation(line: 379, column: 38, scope: !672)
!675 = !DILocation(line: 379, column: 45, scope: !672)
!676 = !DILocation(line: 379, column: 43, scope: !672)
!677 = !DILocation(line: 379, column: 22, scope: !672)
!678 = !DILocation(line: 379, column: 4, scope: !672)
!679 = !DILocation(line: 380, column: 41, scope: !680)
!680 = distinct !DILexicalBlock(scope: !681, file: !1, line: 380, column: 9)
!681 = distinct !DILexicalBlock(scope: !648, file: !1, line: 379, column: 58)
!682 = !DILocation(line: 380, column: 17, scope: !680)
!683 = !DILocation(line: 380, column: 15, scope: !680)
!684 = !DILocation(line: 380, column: 45, scope: !680)
!685 = !DILocation(line: 380, column: 9, scope: !681)
!686 = !DILocation(line: 381, column: 6, scope: !680)
!687 = !DILocation(line: 382, column: 10, scope: !681)
!688 = !DILocation(line: 382, column: 7, scope: !681)
!689 = !DILocation(line: 379, column: 4, scope: !690)
!690 = !DILexicalBlockFile(scope: !648, file: !1, discriminator: 2)
!691 = !DILocation(line: 384, column: 13, scope: !648)
!692 = !DILocation(line: 384, column: 31, scope: !648)
!693 = !DILocation(line: 384, column: 15, scope: !648)
!694 = !DILocation(line: 384, column: 11, scope: !648)
!695 = !DILocation(line: 368, column: 3, scope: !696)
!696 = !DILexicalBlockFile(scope: !640, file: !1, discriminator: 2)
!697 = !DILocation(line: 386, column: 2, scope: !640)
!698 = !DILocation(line: 387, column: 2, scope: !420)
!699 = !DILocation(line: 388, column: 1, scope: !420)
!700 = !DILocalVariable(name: "a", arg: 1, scope: !424, file: !1, line: 391, type: !4)
!701 = !DILocation(line: 391, column: 54, scope: !424)
!702 = !DILocalVariable(name: "key", arg: 2, scope: !424, file: !1, line: 392, type: !80)
!703 = !DILocation(line: 392, column: 17, scope: !424)
!704 = !DILocalVariable(name: "val", arg: 3, scope: !424, file: !1, line: 392, type: !80)
!705 = !DILocation(line: 392, column: 34, scope: !424)
!706 = !DILocalVariable(name: "lha", scope: !424, file: !1, line: 394, type: !292)
!707 = !DILocation(line: 394, column: 14, scope: !424)
!708 = !DILocalVariable(name: "ret", scope: !424, file: !1, line: 395, type: !23)
!709 = !DILocation(line: 395, column: 6, scope: !424)
!710 = !DILocation(line: 397, column: 23, scope: !424)
!711 = !DILocation(line: 397, column: 26, scope: !424)
!712 = !DILocation(line: 397, column: 34, scope: !424)
!713 = !DILocation(line: 397, column: 8, scope: !424)
!714 = !DILocation(line: 397, column: 6, scope: !424)
!715 = !DILocation(line: 398, column: 13, scope: !716)
!716 = distinct !DILexicalBlock(scope: !424, file: !1, line: 398, column: 6)
!717 = !DILocation(line: 398, column: 6, scope: !716)
!718 = !DILocation(line: 398, column: 33, scope: !716)
!719 = !DILocation(line: 398, column: 6, scope: !424)
!720 = !DILocation(line: 399, column: 7, scope: !721)
!721 = distinct !DILexicalBlock(scope: !722, file: !1, line: 399, column: 7)
!722 = distinct !DILexicalBlock(scope: !716, file: !1, line: 398, column: 39)
!723 = !DILocation(line: 399, column: 11, scope: !721)
!724 = !DILocation(line: 399, column: 19, scope: !721)
!725 = !DILocation(line: 399, column: 22, scope: !726)
!726 = !DILexicalBlockFile(scope: !721, file: !1, discriminator: 1)
!727 = !DILocation(line: 399, column: 29, scope: !726)
!728 = !DILocation(line: 399, column: 7, scope: !726)
!729 = !DILocation(line: 400, column: 23, scope: !721)
!730 = !DILocation(line: 400, column: 26, scope: !721)
!731 = !DILocation(line: 400, column: 4, scope: !721)
!732 = !DILocation(line: 405, column: 6, scope: !733)
!733 = distinct !DILexicalBlock(scope: !721, file: !1, line: 402, column: 8)
!734 = !DILocation(line: 405, column: 9, scope: !733)
!735 = !DILocation(line: 405, column: 18, scope: !733)
!736 = !DILocation(line: 404, column: 8, scope: !733)
!737 = !DILocation(line: 403, column: 4, scope: !733)
!738 = !DILocation(line: 403, column: 9, scope: !733)
!739 = !DILocation(line: 403, column: 19, scope: !733)
!740 = !DILocation(line: 406, column: 8, scope: !741)
!741 = distinct !DILexicalBlock(scope: !733, file: !1, line: 406, column: 8)
!742 = !DILocation(line: 406, column: 13, scope: !741)
!743 = !DILocation(line: 406, column: 23, scope: !741)
!744 = !DILocation(line: 406, column: 8, scope: !733)
!745 = !DILocation(line: 407, column: 9, scope: !741)
!746 = !DILocation(line: 407, column: 5, scope: !741)
!747 = !DILocation(line: 409, column: 9, scope: !741)
!748 = !DILocation(line: 411, column: 11, scope: !722)
!749 = !DILocation(line: 411, column: 3, scope: !722)
!750 = !DILocation(line: 417, column: 2, scope: !424)
!751 = !DILocation(line: 418, column: 1, scope: !424)
!752 = !DILocalVariable(name: "a", arg: 1, scope: !425, file: !1, line: 473, type: !4)
!753 = !DILocation(line: 473, column: 58, scope: !425)
!754 = !DILocalVariable(name: "entry", arg: 2, scope: !425, file: !1, line: 474, type: !30)
!755 = !DILocation(line: 474, column: 27, scope: !425)
!756 = !DILocalVariable(name: "linkname", scope: !425, file: !1, line: 476, type: !91)
!757 = !DILocation(line: 476, column: 24, scope: !425)
!758 = !DILocalVariable(name: "pathname", scope: !425, file: !1, line: 477, type: !91)
!759 = !DILocation(line: 477, column: 24, scope: !425)
!760 = !DILocalVariable(name: "lha", scope: !425, file: !1, line: 478, type: !292)
!761 = !DILocation(line: 478, column: 14, scope: !425)
!762 = !DILocalVariable(name: "p", scope: !425, file: !1, line: 479, type: !356)
!763 = !DILocation(line: 479, column: 23, scope: !425)
!764 = !DILocalVariable(name: "signature", scope: !425, file: !1, line: 480, type: !80)
!765 = !DILocation(line: 480, column: 14, scope: !425)
!766 = !DILocalVariable(name: "err", scope: !425, file: !1, line: 481, type: !23)
!767 = !DILocation(line: 481, column: 6, scope: !425)
!768 = !DILocation(line: 483, column: 2, scope: !425)
!769 = !DILocation(line: 485, column: 2, scope: !425)
!770 = !DILocation(line: 485, column: 5, scope: !425)
!771 = !DILocation(line: 485, column: 13, scope: !425)
!772 = !DILocation(line: 485, column: 28, scope: !425)
!773 = !DILocation(line: 486, column: 6, scope: !774)
!774 = distinct !DILexicalBlock(scope: !425, file: !1, line: 486, column: 6)
!775 = !DILocation(line: 486, column: 9, scope: !774)
!776 = !DILocation(line: 486, column: 17, scope: !774)
!777 = !DILocation(line: 486, column: 37, scope: !774)
!778 = !DILocation(line: 486, column: 6, scope: !425)
!779 = !DILocation(line: 487, column: 3, scope: !774)
!780 = !DILocation(line: 487, column: 6, scope: !774)
!781 = !DILocation(line: 487, column: 14, scope: !774)
!782 = !DILocation(line: 487, column: 34, scope: !774)
!783 = !DILocation(line: 489, column: 23, scope: !425)
!784 = !DILocation(line: 489, column: 26, scope: !425)
!785 = !DILocation(line: 489, column: 34, scope: !425)
!786 = !DILocation(line: 489, column: 8, scope: !425)
!787 = !DILocation(line: 489, column: 6, scope: !425)
!788 = !DILocation(line: 490, column: 2, scope: !425)
!789 = !DILocation(line: 490, column: 7, scope: !425)
!790 = !DILocation(line: 490, column: 23, scope: !425)
!791 = !DILocation(line: 491, column: 2, scope: !425)
!792 = !DILocation(line: 491, column: 7, scope: !425)
!793 = !DILocation(line: 491, column: 20, scope: !425)
!794 = !DILocation(line: 492, column: 2, scope: !425)
!795 = !DILocation(line: 492, column: 7, scope: !425)
!796 = !DILocation(line: 492, column: 28, scope: !425)
!797 = !DILocation(line: 493, column: 2, scope: !425)
!798 = !DILocation(line: 493, column: 7, scope: !425)
!799 = !DILocation(line: 493, column: 24, scope: !425)
!800 = !DILocation(line: 495, column: 32, scope: !801)
!801 = distinct !DILexicalBlock(scope: !425, file: !1, line: 495, column: 6)
!802 = !DILocation(line: 495, column: 11, scope: !801)
!803 = !DILocation(line: 495, column: 9, scope: !801)
!804 = !DILocation(line: 495, column: 50, scope: !801)
!805 = !DILocation(line: 495, column: 6, scope: !425)
!806 = !DILocation(line: 500, column: 36, scope: !807)
!807 = distinct !DILexicalBlock(scope: !801, file: !1, line: 495, column: 59)
!808 = !DILocation(line: 500, column: 15, scope: !807)
!809 = !DILocation(line: 500, column: 13, scope: !807)
!810 = !DILocation(line: 501, column: 7, scope: !811)
!811 = distinct !DILexicalBlock(scope: !807, file: !1, line: 501, column: 7)
!812 = !DILocation(line: 501, column: 17, scope: !811)
!813 = !DILocation(line: 501, column: 25, scope: !811)
!814 = !DILocation(line: 501, column: 28, scope: !815)
!815 = !DILexicalBlockFile(scope: !811, file: !1, discriminator: 1)
!816 = !DILocation(line: 501, column: 41, scope: !815)
!817 = !DILocation(line: 501, column: 7, scope: !815)
!818 = !DILocation(line: 502, column: 4, scope: !811)
!819 = !DILocation(line: 503, column: 27, scope: !807)
!820 = !DILocation(line: 503, column: 11, scope: !807)
!821 = !DILocation(line: 503, column: 3, scope: !807)
!822 = !DILocation(line: 506, column: 28, scope: !425)
!823 = !DILocation(line: 506, column: 12, scope: !425)
!824 = !DILocation(line: 507, column: 6, scope: !825)
!825 = distinct !DILexicalBlock(scope: !425, file: !1, line: 507, column: 6)
!826 = !DILocation(line: 507, column: 11, scope: !825)
!827 = !DILocation(line: 507, column: 30, scope: !825)
!828 = !DILocation(line: 507, column: 35, scope: !825)
!829 = !DILocation(line: 508, column: 6, scope: !825)
!830 = !DILocation(line: 508, column: 19, scope: !825)
!831 = !DILocation(line: 508, column: 26, scope: !825)
!832 = !DILocation(line: 508, column: 29, scope: !833)
!833 = !DILexicalBlockFile(scope: !825, file: !1, discriminator: 1)
!834 = !DILocation(line: 508, column: 42, scope: !833)
!835 = !DILocation(line: 507, column: 6, scope: !836)
!836 = !DILexicalBlockFile(scope: !425, file: !1, discriminator: 1)
!837 = !DILocation(line: 510, column: 22, scope: !838)
!838 = distinct !DILexicalBlock(scope: !825, file: !1, line: 508, column: 50)
!839 = !DILocation(line: 510, column: 9, scope: !838)
!840 = !DILocation(line: 510, column: 7, scope: !838)
!841 = !DILocation(line: 511, column: 7, scope: !842)
!842 = distinct !DILexicalBlock(scope: !838, file: !1, line: 511, column: 7)
!843 = !DILocation(line: 511, column: 11, scope: !842)
!844 = !DILocation(line: 511, column: 7, scope: !838)
!845 = !DILocation(line: 512, column: 12, scope: !842)
!846 = !DILocation(line: 512, column: 4, scope: !842)
!847 = !DILocation(line: 514, column: 33, scope: !848)
!848 = distinct !DILexicalBlock(scope: !838, file: !1, line: 514, column: 7)
!849 = !DILocation(line: 514, column: 12, scope: !848)
!850 = !DILocation(line: 514, column: 10, scope: !848)
!851 = !DILocation(line: 514, column: 55, scope: !848)
!852 = !DILocation(line: 514, column: 7, scope: !838)
!853 = !DILocation(line: 515, column: 28, scope: !848)
!854 = !DILocation(line: 515, column: 12, scope: !848)
!855 = !DILocation(line: 515, column: 4, scope: !848)
!856 = !DILocation(line: 516, column: 29, scope: !838)
!857 = !DILocation(line: 516, column: 13, scope: !838)
!858 = !DILocation(line: 517, column: 2, scope: !838)
!859 = !DILocation(line: 519, column: 6, scope: !860)
!860 = distinct !DILexicalBlock(scope: !425, file: !1, line: 519, column: 6)
!861 = !DILocation(line: 519, column: 19, scope: !860)
!862 = !DILocation(line: 519, column: 6, scope: !425)
!863 = !DILocation(line: 520, column: 3, scope: !860)
!864 = !DILocation(line: 525, column: 30, scope: !865)
!865 = distinct !DILexicalBlock(scope: !425, file: !1, line: 525, column: 6)
!866 = !DILocation(line: 525, column: 6, scope: !865)
!867 = !DILocation(line: 525, column: 33, scope: !865)
!868 = !DILocation(line: 525, column: 6, scope: !425)
!869 = !DILocation(line: 526, column: 22, scope: !870)
!870 = distinct !DILexicalBlock(scope: !865, file: !1, line: 525, column: 39)
!871 = !DILocation(line: 526, column: 25, scope: !870)
!872 = !DILocation(line: 526, column: 3, scope: !870)
!873 = !DILocation(line: 528, column: 3, scope: !870)
!874 = !DILocation(line: 532, column: 2, scope: !425)
!875 = !DILocation(line: 532, column: 7, scope: !425)
!876 = !DILocation(line: 532, column: 26, scope: !425)
!877 = !DILocation(line: 534, column: 2, scope: !425)
!878 = !DILocation(line: 534, column: 7, scope: !425)
!879 = !DILocation(line: 534, column: 19, scope: !425)
!880 = !DILocation(line: 535, column: 15, scope: !425)
!881 = !DILocation(line: 535, column: 2, scope: !425)
!882 = !DILocation(line: 535, column: 7, scope: !425)
!883 = !DILocation(line: 535, column: 13, scope: !425)
!884 = !DILocation(line: 536, column: 19, scope: !425)
!885 = !DILocation(line: 536, column: 2, scope: !425)
!886 = !DILocation(line: 536, column: 7, scope: !425)
!887 = !DILocation(line: 536, column: 17, scope: !425)
!888 = !DILocation(line: 537, column: 19, scope: !425)
!889 = !DILocation(line: 537, column: 2, scope: !425)
!890 = !DILocation(line: 537, column: 7, scope: !425)
!891 = !DILocation(line: 537, column: 17, scope: !425)
!892 = !DILocation(line: 538, column: 19, scope: !425)
!893 = !DILocation(line: 538, column: 2, scope: !425)
!894 = !DILocation(line: 538, column: 7, scope: !425)
!895 = !DILocation(line: 538, column: 17, scope: !425)
!896 = !DILocation(line: 539, column: 13, scope: !897)
!897 = distinct !DILexicalBlock(scope: !425, file: !1, line: 539, column: 6)
!898 = !DILocation(line: 539, column: 18, scope: !897)
!899 = !DILocation(line: 539, column: 6, scope: !897)
!900 = !DILocation(line: 539, column: 36, scope: !897)
!901 = !DILocation(line: 539, column: 6, scope: !425)
!902 = !DILocation(line: 540, column: 3, scope: !897)
!903 = !DILocation(line: 540, column: 8, scope: !897)
!904 = !DILocation(line: 540, column: 18, scope: !897)
!905 = !DILocation(line: 542, column: 3, scope: !897)
!906 = !DILocation(line: 542, column: 8, scope: !897)
!907 = !DILocation(line: 542, column: 18, scope: !897)
!908 = !DILocation(line: 543, column: 13, scope: !909)
!909 = distinct !DILexicalBlock(scope: !425, file: !1, line: 543, column: 6)
!910 = !DILocation(line: 543, column: 18, scope: !909)
!911 = !DILocation(line: 543, column: 6, scope: !909)
!912 = !DILocation(line: 543, column: 36, scope: !909)
!913 = !DILocation(line: 543, column: 41, scope: !909)
!914 = !DILocation(line: 544, column: 13, scope: !909)
!915 = !DILocation(line: 544, column: 18, scope: !909)
!916 = !DILocation(line: 544, column: 6, scope: !909)
!917 = !DILocation(line: 544, column: 36, scope: !909)
!918 = !DILocation(line: 543, column: 6, scope: !836)
!919 = !DILocation(line: 545, column: 3, scope: !909)
!920 = !DILocation(line: 545, column: 8, scope: !909)
!921 = !DILocation(line: 545, column: 28, scope: !909)
!922 = !DILocation(line: 547, column: 3, scope: !909)
!923 = !DILocation(line: 547, column: 8, scope: !909)
!924 = !DILocation(line: 547, column: 28, scope: !909)
!925 = !DILocation(line: 549, column: 2, scope: !425)
!926 = !DILocation(line: 549, column: 7, scope: !425)
!927 = !DILocation(line: 549, column: 16, scope: !425)
!928 = !DILocation(line: 550, column: 2, scope: !425)
!929 = !DILocation(line: 550, column: 7, scope: !425)
!930 = !DILocation(line: 550, column: 16, scope: !425)
!931 = !DILocation(line: 551, column: 2, scope: !425)
!932 = !DILocation(line: 551, column: 7, scope: !425)
!933 = !DILocation(line: 551, column: 15, scope: !425)
!934 = !DILocation(line: 552, column: 2, scope: !425)
!935 = !DILocation(line: 552, column: 7, scope: !425)
!936 = !DILocation(line: 552, column: 17, scope: !425)
!937 = !DILocation(line: 553, column: 2, scope: !425)
!938 = !DILocation(line: 553, column: 7, scope: !425)
!939 = !DILocation(line: 553, column: 25, scope: !425)
!940 = !DILocation(line: 554, column: 2, scope: !425)
!941 = !DILocation(line: 554, column: 7, scope: !425)
!942 = !DILocation(line: 554, column: 13, scope: !425)
!943 = !DILocation(line: 555, column: 2, scope: !425)
!944 = !DILocation(line: 555, column: 7, scope: !425)
!945 = !DILocation(line: 555, column: 21, scope: !425)
!946 = !DILocation(line: 556, column: 2, scope: !425)
!947 = !DILocation(line: 556, column: 7, scope: !425)
!948 = !DILocation(line: 556, column: 13, scope: !425)
!949 = !DILocation(line: 557, column: 2, scope: !425)
!950 = !DILocation(line: 557, column: 7, scope: !425)
!951 = !DILocation(line: 557, column: 21, scope: !425)
!952 = !DILocation(line: 558, column: 15, scope: !425)
!953 = !DILocation(line: 558, column: 20, scope: !425)
!954 = !DILocation(line: 558, column: 14, scope: !425)
!955 = !DILocation(line: 558, column: 2, scope: !425)
!956 = !DILocation(line: 558, column: 7, scope: !425)
!957 = !DILocation(line: 558, column: 12, scope: !425)
!958 = !DILocation(line: 559, column: 2, scope: !425)
!959 = !DILocation(line: 559, column: 7, scope: !425)
!960 = !DILocation(line: 559, column: 11, scope: !425)
!961 = !DILocation(line: 560, column: 2, scope: !425)
!962 = !DILocation(line: 560, column: 7, scope: !425)
!963 = !DILocation(line: 560, column: 11, scope: !425)
!964 = !DILocation(line: 561, column: 2, scope: !425)
!965 = !DILocation(line: 562, column: 2, scope: !425)
!966 = !DILocation(line: 563, column: 2, scope: !425)
!967 = !DILocation(line: 563, column: 7, scope: !425)
!968 = !DILocation(line: 563, column: 16, scope: !425)
!969 = !DILocation(line: 564, column: 6, scope: !970)
!970 = distinct !DILexicalBlock(scope: !425, file: !1, line: 564, column: 6)
!971 = !DILocation(line: 564, column: 11, scope: !970)
!972 = !DILocation(line: 564, column: 21, scope: !970)
!973 = !DILocation(line: 564, column: 6, scope: !425)
!974 = !DILocation(line: 565, column: 16, scope: !970)
!975 = !DILocation(line: 565, column: 21, scope: !970)
!976 = !DILocation(line: 565, column: 3, scope: !970)
!977 = !DILocation(line: 565, column: 8, scope: !970)
!978 = !DILocation(line: 565, column: 14, scope: !970)
!979 = !DILocation(line: 567, column: 3, scope: !970)
!980 = !DILocation(line: 567, column: 8, scope: !970)
!981 = !DILocation(line: 567, column: 14, scope: !970)
!982 = !DILocation(line: 569, column: 10, scope: !425)
!983 = !DILocation(line: 569, column: 2, scope: !425)
!984 = !DILocation(line: 571, column: 32, scope: !985)
!985 = distinct !DILexicalBlock(scope: !425, file: !1, line: 569, column: 29)
!986 = !DILocation(line: 571, column: 35, scope: !985)
!987 = !DILocation(line: 571, column: 9, scope: !985)
!988 = !DILocation(line: 571, column: 7, scope: !985)
!989 = !DILocation(line: 572, column: 3, scope: !985)
!990 = !DILocation(line: 574, column: 32, scope: !985)
!991 = !DILocation(line: 574, column: 35, scope: !985)
!992 = !DILocation(line: 574, column: 9, scope: !985)
!993 = !DILocation(line: 574, column: 7, scope: !985)
!994 = !DILocation(line: 575, column: 3, scope: !985)
!995 = !DILocation(line: 577, column: 32, scope: !985)
!996 = !DILocation(line: 577, column: 35, scope: !985)
!997 = !DILocation(line: 577, column: 9, scope: !985)
!998 = !DILocation(line: 577, column: 7, scope: !985)
!999 = !DILocation(line: 578, column: 3, scope: !985)
!1000 = !DILocation(line: 580, column: 32, scope: !985)
!1001 = !DILocation(line: 580, column: 35, scope: !985)
!1002 = !DILocation(line: 580, column: 9, scope: !985)
!1003 = !DILocation(line: 580, column: 7, scope: !985)
!1004 = !DILocation(line: 581, column: 3, scope: !985)
!1005 = !DILocation(line: 583, column: 22, scope: !985)
!1006 = !DILocation(line: 583, column: 25, scope: !985)
!1007 = !DILocation(line: 584, column: 42, scope: !985)
!1008 = !DILocation(line: 583, column: 3, scope: !985)
!1009 = !DILocation(line: 585, column: 7, scope: !985)
!1010 = !DILocation(line: 586, column: 3, scope: !985)
!1011 = !DILocation(line: 588, column: 6, scope: !1012)
!1012 = distinct !DILexicalBlock(scope: !425, file: !1, line: 588, column: 6)
!1013 = !DILocation(line: 588, column: 10, scope: !1012)
!1014 = !DILocation(line: 588, column: 6, scope: !425)
!1015 = !DILocation(line: 589, column: 11, scope: !1012)
!1016 = !DILocation(line: 589, column: 3, scope: !1012)
!1017 = !DILocation(line: 592, column: 7, scope: !1018)
!1018 = distinct !DILexicalBlock(scope: !425, file: !1, line: 592, column: 6)
!1019 = !DILocation(line: 592, column: 12, scope: !1018)
!1020 = !DILocation(line: 592, column: 22, scope: !1018)
!1021 = !DILocation(line: 592, column: 25, scope: !1022)
!1022 = !DILexicalBlockFile(scope: !1018, file: !1, discriminator: 1)
!1023 = !DILocation(line: 592, column: 56, scope: !1022)
!1024 = !DILocation(line: 592, column: 6, scope: !1022)
!1025 = !DILocation(line: 594, column: 27, scope: !1018)
!1026 = !DILocation(line: 594, column: 11, scope: !1018)
!1027 = !DILocation(line: 594, column: 3, scope: !1018)
!1028 = !DILocation(line: 599, column: 25, scope: !425)
!1029 = !DILocation(line: 599, column: 30, scope: !425)
!1030 = !DILocation(line: 599, column: 40, scope: !425)
!1031 = !DILocation(line: 599, column: 45, scope: !425)
!1032 = !DILocation(line: 599, column: 2, scope: !425)
!1033 = !DILocation(line: 600, column: 2, scope: !425)
!1034 = !DILocation(line: 600, column: 2, scope: !1035)
!1035 = !DILexicalBlockFile(scope: !1036, file: !1, discriminator: 1)
!1036 = distinct !DILexicalBlock(scope: !425, file: !1, line: 600, column: 2)
!1037 = !DILocation(line: 601, column: 2, scope: !425)
!1038 = !DILocation(line: 601, column: 2, scope: !1039)
!1039 = !DILexicalBlockFile(scope: !1040, file: !1, discriminator: 1)
!1040 = distinct !DILexicalBlock(scope: !425, file: !1, line: 601, column: 2)
!1041 = !DILocation(line: 602, column: 2, scope: !425)
!1042 = !DILocation(line: 604, column: 7, scope: !1043)
!1043 = distinct !DILexicalBlock(scope: !425, file: !1, line: 604, column: 6)
!1044 = !DILocation(line: 604, column: 12, scope: !1043)
!1045 = !DILocation(line: 604, column: 17, scope: !1043)
!1046 = !DILocation(line: 604, column: 28, scope: !1043)
!1047 = !DILocation(line: 604, column: 6, scope: !425)
!1048 = !DILocation(line: 608, column: 8, scope: !1049)
!1049 = distinct !DILexicalBlock(scope: !1050, file: !1, line: 608, column: 7)
!1050 = distinct !DILexicalBlock(scope: !1043, file: !1, line: 604, column: 41)
!1051 = !DILocation(line: 608, column: 7, scope: !1050)
!1052 = !DILocation(line: 610, column: 23, scope: !1053)
!1053 = distinct !DILexicalBlock(scope: !1049, file: !1, line: 608, column: 50)
!1054 = !DILocation(line: 610, column: 26, scope: !1053)
!1055 = !DILocation(line: 610, column: 4, scope: !1053)
!1056 = !DILocation(line: 613, column: 4, scope: !1053)
!1057 = !DILocation(line: 614, column: 4, scope: !1053)
!1058 = !DILocation(line: 615, column: 4, scope: !1053)
!1059 = !DILocation(line: 617, column: 2, scope: !1050)
!1060 = !DILocation(line: 622, column: 16, scope: !1061)
!1061 = distinct !DILexicalBlock(scope: !1043, file: !1, line: 617, column: 9)
!1062 = !DILocation(line: 622, column: 21, scope: !1061)
!1063 = !DILocation(line: 622, column: 26, scope: !1061)
!1064 = !DILocation(line: 623, column: 9, scope: !1061)
!1065 = !DILocation(line: 623, column: 14, scope: !1061)
!1066 = !DILocation(line: 623, column: 8, scope: !1061)
!1067 = !DILocation(line: 622, column: 38, scope: !1061)
!1068 = !DILocation(line: 622, column: 3, scope: !1061)
!1069 = !DILocation(line: 622, column: 8, scope: !1061)
!1070 = !DILocation(line: 622, column: 13, scope: !1061)
!1071 = !DILocation(line: 625, column: 7, scope: !1072)
!1072 = distinct !DILexicalBlock(scope: !425, file: !1, line: 625, column: 6)
!1073 = !DILocation(line: 625, column: 12, scope: !1072)
!1074 = !DILocation(line: 625, column: 20, scope: !1072)
!1075 = !DILocation(line: 625, column: 40, scope: !1072)
!1076 = !DILocation(line: 625, column: 45, scope: !1072)
!1077 = !DILocation(line: 626, column: 7, scope: !1072)
!1078 = !DILocation(line: 626, column: 12, scope: !1072)
!1079 = !DILocation(line: 626, column: 21, scope: !1072)
!1080 = !DILocation(line: 626, column: 26, scope: !1072)
!1081 = !DILocation(line: 625, column: 6, scope: !836)
!1082 = !DILocation(line: 627, column: 3, scope: !1072)
!1083 = !DILocation(line: 627, column: 8, scope: !1072)
!1084 = !DILocation(line: 627, column: 13, scope: !1072)
!1085 = !DILocation(line: 632, column: 36, scope: !1086)
!1086 = distinct !DILexicalBlock(scope: !425, file: !1, line: 632, column: 6)
!1087 = !DILocation(line: 632, column: 52, scope: !1086)
!1088 = !DILocation(line: 633, column: 15, scope: !1086)
!1089 = !DILocation(line: 633, column: 23, scope: !1086)
!1090 = !DILocation(line: 633, column: 28, scope: !1086)
!1091 = !DILocation(line: 632, column: 6, scope: !1086)
!1092 = !DILocation(line: 633, column: 35, scope: !1086)
!1093 = !DILocation(line: 632, column: 6, scope: !425)
!1094 = !DILocation(line: 634, column: 7, scope: !1095)
!1095 = distinct !DILexicalBlock(scope: !1096, file: !1, line: 634, column: 7)
!1096 = distinct !DILexicalBlock(scope: !1086, file: !1, line: 633, column: 41)
!1097 = !DILocation(line: 634, column: 13, scope: !1095)
!1098 = !DILocation(line: 634, column: 7, scope: !1096)
!1099 = !DILocation(line: 635, column: 23, scope: !1100)
!1100 = distinct !DILexicalBlock(scope: !1095, file: !1, line: 634, column: 24)
!1101 = !DILocation(line: 635, column: 26, scope: !1100)
!1102 = !DILocation(line: 635, column: 4, scope: !1100)
!1103 = !DILocation(line: 637, column: 4, scope: !1100)
!1104 = !DILocation(line: 639, column: 22, scope: !1096)
!1105 = !DILocation(line: 639, column: 25, scope: !1096)
!1106 = !DILocation(line: 643, column: 46, scope: !1096)
!1107 = !DILocation(line: 643, column: 51, scope: !1096)
!1108 = !DILocation(line: 643, column: 7, scope: !1096)
!1109 = !DILocation(line: 639, column: 3, scope: !1096)
!1110 = !DILocation(line: 644, column: 7, scope: !1096)
!1111 = !DILocation(line: 645, column: 2, scope: !1096)
!1112 = !DILocation(line: 646, column: 2, scope: !425)
!1113 = !DILocation(line: 647, column: 6, scope: !1114)
!1114 = distinct !DILexicalBlock(scope: !425, file: !1, line: 647, column: 6)
!1115 = !DILocation(line: 647, column: 32, scope: !1114)
!1116 = !DILocation(line: 647, column: 6, scope: !425)
!1117 = !DILocation(line: 648, column: 36, scope: !1118)
!1118 = distinct !DILexicalBlock(scope: !1119, file: !1, line: 648, column: 7)
!1119 = distinct !DILexicalBlock(scope: !1114, file: !1, line: 647, column: 37)
!1120 = !DILocation(line: 648, column: 52, scope: !1118)
!1121 = !DILocation(line: 649, column: 16, scope: !1118)
!1122 = !DILocation(line: 649, column: 24, scope: !1118)
!1123 = !DILocation(line: 649, column: 29, scope: !1118)
!1124 = !DILocation(line: 648, column: 7, scope: !1118)
!1125 = !DILocation(line: 649, column: 36, scope: !1118)
!1126 = !DILocation(line: 648, column: 7, scope: !1119)
!1127 = !DILocation(line: 650, column: 8, scope: !1128)
!1128 = distinct !DILexicalBlock(scope: !1129, file: !1, line: 650, column: 8)
!1129 = distinct !DILexicalBlock(scope: !1118, file: !1, line: 649, column: 42)
!1130 = !DILocation(line: 650, column: 14, scope: !1128)
!1131 = !DILocation(line: 650, column: 8, scope: !1129)
!1132 = !DILocation(line: 651, column: 24, scope: !1133)
!1133 = distinct !DILexicalBlock(scope: !1128, file: !1, line: 650, column: 25)
!1134 = !DILocation(line: 651, column: 27, scope: !1133)
!1135 = !DILocation(line: 651, column: 5, scope: !1133)
!1136 = !DILocation(line: 653, column: 5, scope: !1133)
!1137 = !DILocation(line: 655, column: 23, scope: !1129)
!1138 = !DILocation(line: 655, column: 26, scope: !1129)
!1139 = !DILocation(line: 659, column: 47, scope: !1129)
!1140 = !DILocation(line: 659, column: 52, scope: !1129)
!1141 = !DILocation(line: 659, column: 8, scope: !1129)
!1142 = !DILocation(line: 655, column: 4, scope: !1129)
!1143 = !DILocation(line: 660, column: 8, scope: !1129)
!1144 = !DILocation(line: 661, column: 3, scope: !1129)
!1145 = !DILocation(line: 662, column: 2, scope: !1119)
!1146 = !DILocation(line: 663, column: 29, scope: !1114)
!1147 = !DILocation(line: 663, column: 3, scope: !1114)
!1148 = !DILocation(line: 664, column: 2, scope: !425)
!1149 = !DILocation(line: 670, column: 6, scope: !1150)
!1150 = distinct !DILexicalBlock(scope: !425, file: !1, line: 670, column: 6)
!1151 = !DILocation(line: 670, column: 24, scope: !1150)
!1152 = !DILocation(line: 670, column: 6, scope: !425)
!1153 = !DILocation(line: 671, column: 30, scope: !1150)
!1154 = !DILocation(line: 671, column: 35, scope: !1150)
!1155 = !DILocation(line: 671, column: 3, scope: !1150)
!1156 = !DILocation(line: 673, column: 25, scope: !425)
!1157 = !DILocation(line: 673, column: 32, scope: !425)
!1158 = !DILocation(line: 673, column: 37, scope: !425)
!1159 = !DILocation(line: 673, column: 2, scope: !425)
!1160 = !DILocation(line: 674, column: 24, scope: !425)
!1161 = !DILocation(line: 674, column: 31, scope: !425)
!1162 = !DILocation(line: 674, column: 36, scope: !425)
!1163 = !DILocation(line: 674, column: 2, scope: !425)
!1164 = !DILocation(line: 675, column: 24, scope: !425)
!1165 = !DILocation(line: 675, column: 31, scope: !425)
!1166 = !DILocation(line: 675, column: 36, scope: !425)
!1167 = !DILocation(line: 675, column: 2, scope: !425)
!1168 = !DILocation(line: 676, column: 6, scope: !1169)
!1169 = distinct !DILexicalBlock(scope: !425, file: !1, line: 676, column: 6)
!1170 = !DILocation(line: 676, column: 34, scope: !1169)
!1171 = !DILocation(line: 676, column: 6, scope: !425)
!1172 = !DILocation(line: 677, column: 27, scope: !1169)
!1173 = !DILocation(line: 677, column: 34, scope: !1169)
!1174 = !DILocation(line: 677, column: 39, scope: !1169)
!1175 = !DILocation(line: 677, column: 45, scope: !1169)
!1176 = !DILocation(line: 677, column: 3, scope: !1169)
!1177 = !DILocation(line: 678, column: 6, scope: !1178)
!1178 = distinct !DILexicalBlock(scope: !425, file: !1, line: 678, column: 6)
!1179 = !DILocation(line: 678, column: 34, scope: !1178)
!1180 = !DILocation(line: 678, column: 6, scope: !425)
!1181 = !DILocation(line: 679, column: 27, scope: !1178)
!1182 = !DILocation(line: 679, column: 34, scope: !1178)
!1183 = !DILocation(line: 679, column: 39, scope: !1178)
!1184 = !DILocation(line: 679, column: 45, scope: !1178)
!1185 = !DILocation(line: 679, column: 3, scope: !1178)
!1186 = !DILocation(line: 680, column: 6, scope: !1187)
!1187 = distinct !DILexicalBlock(scope: !425, file: !1, line: 680, column: 6)
!1188 = !DILocation(line: 680, column: 11, scope: !1187)
!1189 = !DILocation(line: 680, column: 19, scope: !1187)
!1190 = !DILocation(line: 680, column: 6, scope: !425)
!1191 = !DILocation(line: 681, column: 31, scope: !1192)
!1192 = distinct !DILexicalBlock(scope: !1187, file: !1, line: 680, column: 39)
!1193 = !DILocation(line: 681, column: 38, scope: !1192)
!1194 = !DILocation(line: 681, column: 43, scope: !1192)
!1195 = !DILocation(line: 682, column: 7, scope: !1192)
!1196 = !DILocation(line: 682, column: 12, scope: !1192)
!1197 = !DILocation(line: 681, column: 3, scope: !1192)
!1198 = !DILocation(line: 683, column: 27, scope: !1192)
!1199 = !DILocation(line: 683, column: 34, scope: !1192)
!1200 = !DILocation(line: 683, column: 39, scope: !1192)
!1201 = !DILocation(line: 684, column: 7, scope: !1192)
!1202 = !DILocation(line: 684, column: 12, scope: !1192)
!1203 = !DILocation(line: 683, column: 3, scope: !1192)
!1204 = !DILocation(line: 685, column: 2, scope: !1192)
!1205 = !DILocation(line: 686, column: 33, scope: !1206)
!1206 = distinct !DILexicalBlock(scope: !1187, file: !1, line: 685, column: 9)
!1207 = !DILocation(line: 686, column: 3, scope: !1206)
!1208 = !DILocation(line: 687, column: 29, scope: !1206)
!1209 = !DILocation(line: 687, column: 3, scope: !1206)
!1210 = !DILocation(line: 689, column: 26, scope: !425)
!1211 = !DILocation(line: 689, column: 33, scope: !425)
!1212 = !DILocation(line: 689, column: 38, scope: !425)
!1213 = !DILocation(line: 689, column: 45, scope: !425)
!1214 = !DILocation(line: 689, column: 50, scope: !425)
!1215 = !DILocation(line: 689, column: 2, scope: !425)
!1216 = !DILocation(line: 690, column: 6, scope: !1217)
!1217 = distinct !DILexicalBlock(scope: !425, file: !1, line: 690, column: 6)
!1218 = !DILocation(line: 690, column: 11, scope: !1217)
!1219 = !DILocation(line: 690, column: 19, scope: !1217)
!1220 = !DILocation(line: 690, column: 6, scope: !425)
!1221 = !DILocation(line: 691, column: 27, scope: !1217)
!1222 = !DILocation(line: 691, column: 34, scope: !1217)
!1223 = !DILocation(line: 691, column: 39, scope: !1217)
!1224 = !DILocation(line: 692, column: 7, scope: !1217)
!1225 = !DILocation(line: 692, column: 12, scope: !1217)
!1226 = !DILocation(line: 691, column: 3, scope: !1217)
!1227 = !DILocation(line: 694, column: 29, scope: !1217)
!1228 = !DILocation(line: 694, column: 3, scope: !1217)
!1229 = !DILocation(line: 695, column: 6, scope: !1230)
!1230 = distinct !DILexicalBlock(scope: !425, file: !1, line: 695, column: 6)
!1231 = !DILocation(line: 695, column: 11, scope: !1230)
!1232 = !DILocation(line: 695, column: 21, scope: !1230)
!1233 = !DILocation(line: 695, column: 46, scope: !1234)
!1234 = !DILexicalBlockFile(scope: !1230, file: !1, discriminator: 1)
!1235 = !DILocation(line: 695, column: 24, scope: !1234)
!1236 = !DILocation(line: 695, column: 53, scope: !1234)
!1237 = !DILocation(line: 695, column: 6, scope: !1234)
!1238 = !DILocation(line: 696, column: 28, scope: !1230)
!1239 = !DILocation(line: 696, column: 3, scope: !1230)
!1240 = !DILocation(line: 698, column: 26, scope: !1230)
!1241 = !DILocation(line: 698, column: 33, scope: !1230)
!1242 = !DILocation(line: 698, column: 38, scope: !1230)
!1243 = !DILocation(line: 698, column: 3, scope: !1230)
!1244 = !DILocation(line: 703, column: 31, scope: !425)
!1245 = !DILocation(line: 703, column: 36, scope: !425)
!1246 = !DILocation(line: 703, column: 2, scope: !425)
!1247 = !DILocation(line: 703, column: 7, scope: !425)
!1248 = !DILocation(line: 703, column: 29, scope: !425)
!1249 = !DILocation(line: 704, column: 2, scope: !425)
!1250 = !DILocation(line: 704, column: 7, scope: !425)
!1251 = !DILocation(line: 704, column: 20, scope: !425)
!1252 = !DILocation(line: 705, column: 2, scope: !425)
!1253 = !DILocation(line: 705, column: 7, scope: !425)
!1254 = !DILocation(line: 705, column: 28, scope: !425)
!1255 = !DILocation(line: 710, column: 6, scope: !1256)
!1256 = distinct !DILexicalBlock(scope: !425, file: !1, line: 710, column: 6)
!1257 = !DILocation(line: 710, column: 11, scope: !1256)
!1258 = !DILocation(line: 710, column: 21, scope: !1256)
!1259 = !DILocation(line: 710, column: 24, scope: !1260)
!1260 = !DILexicalBlockFile(scope: !1256, file: !1, discriminator: 1)
!1261 = !DILocation(line: 710, column: 29, scope: !1260)
!1262 = !DILocation(line: 710, column: 38, scope: !1260)
!1263 = !DILocation(line: 710, column: 6, scope: !1260)
!1264 = !DILocation(line: 711, column: 3, scope: !1256)
!1265 = !DILocation(line: 711, column: 8, scope: !1256)
!1266 = !DILocation(line: 711, column: 21, scope: !1256)
!1267 = !DILocation(line: 713, column: 10, scope: !425)
!1268 = !DILocation(line: 713, column: 15, scope: !425)
!1269 = !DILocation(line: 714, column: 6, scope: !425)
!1270 = !DILocation(line: 714, column: 11, scope: !425)
!1271 = !DILocation(line: 714, column: 22, scope: !425)
!1272 = !DILocation(line: 714, column: 27, scope: !425)
!1273 = !DILocation(line: 714, column: 38, scope: !425)
!1274 = !DILocation(line: 714, column: 43, scope: !425)
!1275 = !DILocation(line: 713, column: 2, scope: !425)
!1276 = !DILocation(line: 715, column: 35, scope: !425)
!1277 = !DILocation(line: 715, column: 40, scope: !425)
!1278 = !DILocation(line: 715, column: 2, scope: !425)
!1279 = !DILocation(line: 715, column: 5, scope: !425)
!1280 = !DILocation(line: 715, column: 13, scope: !425)
!1281 = !DILocation(line: 715, column: 33, scope: !425)
!1282 = !DILocation(line: 717, column: 10, scope: !425)
!1283 = !DILocation(line: 717, column: 2, scope: !425)
!1284 = !DILocation(line: 718, column: 1, scope: !425)
!1285 = !DILocalVariable(name: "a", arg: 1, scope: !470, file: !1, line: 1368, type: !4)
!1286 = !DILocation(line: 1368, column: 56, scope: !470)
!1287 = !DILocalVariable(name: "buff", arg: 2, scope: !470, file: !1, line: 1369, type: !64)
!1288 = !DILocation(line: 1369, column: 18, scope: !470)
!1289 = !DILocalVariable(name: "size", arg: 3, scope: !470, file: !1, line: 1369, type: !65)
!1290 = !DILocation(line: 1369, column: 32, scope: !470)
!1291 = !DILocalVariable(name: "offset", arg: 4, scope: !470, file: !1, line: 1369, type: !66)
!1292 = !DILocation(line: 1369, column: 47, scope: !470)
!1293 = !DILocalVariable(name: "lha", scope: !470, file: !1, line: 1371, type: !292)
!1294 = !DILocation(line: 1371, column: 14, scope: !470)
!1295 = !DILocation(line: 1371, column: 35, scope: !470)
!1296 = !DILocation(line: 1371, column: 38, scope: !470)
!1297 = !DILocation(line: 1371, column: 46, scope: !470)
!1298 = !DILocation(line: 1371, column: 20, scope: !470)
!1299 = !DILocalVariable(name: "r", scope: !470, file: !1, line: 1372, type: !23)
!1300 = !DILocation(line: 1372, column: 6, scope: !470)
!1301 = !DILocation(line: 1374, column: 6, scope: !1302)
!1302 = distinct !DILexicalBlock(scope: !470, file: !1, line: 1374, column: 6)
!1303 = !DILocation(line: 1374, column: 11, scope: !1302)
!1304 = !DILocation(line: 1374, column: 6, scope: !470)
!1305 = !DILocation(line: 1376, column: 26, scope: !1306)
!1306 = distinct !DILexicalBlock(scope: !1302, file: !1, line: 1374, column: 29)
!1307 = !DILocation(line: 1376, column: 29, scope: !1306)
!1308 = !DILocation(line: 1376, column: 34, scope: !1306)
!1309 = !DILocation(line: 1376, column: 3, scope: !1306)
!1310 = !DILocation(line: 1377, column: 3, scope: !1306)
!1311 = !DILocation(line: 1377, column: 8, scope: !1306)
!1312 = !DILocation(line: 1377, column: 25, scope: !1306)
!1313 = !DILocation(line: 1378, column: 2, scope: !1306)
!1314 = !DILocation(line: 1379, column: 6, scope: !1315)
!1315 = distinct !DILexicalBlock(scope: !470, file: !1, line: 1379, column: 6)
!1316 = !DILocation(line: 1379, column: 11, scope: !1315)
!1317 = !DILocation(line: 1379, column: 6, scope: !470)
!1318 = !DILocation(line: 1380, column: 13, scope: !1319)
!1319 = distinct !DILexicalBlock(scope: !1315, file: !1, line: 1379, column: 25)
!1320 = !DILocation(line: 1380, column: 18, scope: !1319)
!1321 = !DILocation(line: 1380, column: 4, scope: !1319)
!1322 = !DILocation(line: 1380, column: 11, scope: !1319)
!1323 = !DILocation(line: 1381, column: 4, scope: !1319)
!1324 = !DILocation(line: 1381, column: 9, scope: !1319)
!1325 = !DILocation(line: 1382, column: 4, scope: !1319)
!1326 = !DILocation(line: 1382, column: 9, scope: !1319)
!1327 = !DILocation(line: 1383, column: 28, scope: !1319)
!1328 = !DILocation(line: 1383, column: 11, scope: !1319)
!1329 = !DILocation(line: 1383, column: 3, scope: !1319)
!1330 = !DILocation(line: 1386, column: 6, scope: !1331)
!1331 = distinct !DILexicalBlock(scope: !470, file: !1, line: 1386, column: 6)
!1332 = !DILocation(line: 1386, column: 11, scope: !1331)
!1333 = !DILocation(line: 1386, column: 6, scope: !470)
!1334 = !DILocation(line: 1387, column: 26, scope: !1331)
!1335 = !DILocation(line: 1387, column: 29, scope: !1331)
!1336 = !DILocation(line: 1387, column: 35, scope: !1331)
!1337 = !DILocation(line: 1387, column: 41, scope: !1331)
!1338 = !DILocation(line: 1387, column: 8, scope: !1331)
!1339 = !DILocation(line: 1387, column: 5, scope: !1331)
!1340 = !DILocation(line: 1387, column: 3, scope: !1331)
!1341 = !DILocation(line: 1390, column: 27, scope: !1331)
!1342 = !DILocation(line: 1390, column: 30, scope: !1331)
!1343 = !DILocation(line: 1390, column: 36, scope: !1331)
!1344 = !DILocation(line: 1390, column: 42, scope: !1331)
!1345 = !DILocation(line: 1390, column: 8, scope: !1331)
!1346 = !DILocation(line: 1390, column: 5, scope: !1331)
!1347 = !DILocation(line: 1391, column: 10, scope: !470)
!1348 = !DILocation(line: 1391, column: 2, scope: !470)
!1349 = !DILocation(line: 1392, column: 1, scope: !470)
!1350 = !DILocalVariable(name: "a", arg: 1, scope: !509, file: !1, line: 1540, type: !4)
!1351 = !DILocation(line: 1540, column: 61, scope: !509)
!1352 = !DILocalVariable(name: "lha", scope: !509, file: !1, line: 1542, type: !292)
!1353 = !DILocation(line: 1542, column: 14, scope: !509)
!1354 = !DILocalVariable(name: "bytes_skipped", scope: !509, file: !1, line: 1543, type: !52)
!1355 = !DILocation(line: 1543, column: 10, scope: !509)
!1356 = !DILocation(line: 1545, column: 23, scope: !509)
!1357 = !DILocation(line: 1545, column: 26, scope: !509)
!1358 = !DILocation(line: 1545, column: 34, scope: !509)
!1359 = !DILocation(line: 1545, column: 8, scope: !509)
!1360 = !DILocation(line: 1545, column: 6, scope: !509)
!1361 = !DILocation(line: 1547, column: 6, scope: !1362)
!1362 = distinct !DILexicalBlock(scope: !509, file: !1, line: 1547, column: 6)
!1363 = !DILocation(line: 1547, column: 11, scope: !1362)
!1364 = !DILocation(line: 1547, column: 6, scope: !509)
!1365 = !DILocation(line: 1549, column: 26, scope: !1366)
!1366 = distinct !DILexicalBlock(scope: !1362, file: !1, line: 1547, column: 29)
!1367 = !DILocation(line: 1549, column: 29, scope: !1366)
!1368 = !DILocation(line: 1549, column: 34, scope: !1366)
!1369 = !DILocation(line: 1549, column: 3, scope: !1366)
!1370 = !DILocation(line: 1550, column: 3, scope: !1366)
!1371 = !DILocation(line: 1550, column: 8, scope: !1366)
!1372 = !DILocation(line: 1550, column: 25, scope: !1366)
!1373 = !DILocation(line: 1551, column: 2, scope: !1366)
!1374 = !DILocation(line: 1554, column: 6, scope: !1375)
!1375 = distinct !DILexicalBlock(scope: !509, file: !1, line: 1554, column: 6)
!1376 = !DILocation(line: 1554, column: 11, scope: !1375)
!1377 = !DILocation(line: 1554, column: 6, scope: !509)
!1378 = !DILocation(line: 1555, column: 3, scope: !1375)
!1379 = !DILocation(line: 1561, column: 41, scope: !509)
!1380 = !DILocation(line: 1561, column: 44, scope: !509)
!1381 = !DILocation(line: 1561, column: 49, scope: !509)
!1382 = !DILocation(line: 1561, column: 18, scope: !509)
!1383 = !DILocation(line: 1561, column: 16, scope: !509)
!1384 = !DILocation(line: 1562, column: 6, scope: !1385)
!1385 = distinct !DILexicalBlock(scope: !509, file: !1, line: 1562, column: 6)
!1386 = !DILocation(line: 1562, column: 20, scope: !1385)
!1387 = !DILocation(line: 1562, column: 6, scope: !509)
!1388 = !DILocation(line: 1563, column: 3, scope: !1385)
!1389 = !DILocation(line: 1566, column: 30, scope: !509)
!1390 = !DILocation(line: 1566, column: 35, scope: !509)
!1391 = !DILocation(line: 1566, column: 48, scope: !509)
!1392 = !DILocation(line: 1566, column: 2, scope: !509)
!1393 = !DILocation(line: 1566, column: 7, scope: !509)
!1394 = !DILocation(line: 1566, column: 28, scope: !509)
!1395 = !DILocation(line: 1567, column: 2, scope: !509)
!1396 = !DILocation(line: 1568, column: 1, scope: !509)
!1397 = !DILocalVariable(name: "a", arg: 1, scope: !510, file: !1, line: 1571, type: !4)
!1398 = !DILocation(line: 1571, column: 54, scope: !510)
!1399 = !DILocalVariable(name: "lha", scope: !510, file: !1, line: 1573, type: !292)
!1400 = !DILocation(line: 1573, column: 14, scope: !510)
!1401 = !DILocation(line: 1573, column: 35, scope: !510)
!1402 = !DILocation(line: 1573, column: 38, scope: !510)
!1403 = !DILocation(line: 1573, column: 46, scope: !510)
!1404 = !DILocation(line: 1573, column: 20, scope: !510)
!1405 = !DILocation(line: 1575, column: 20, scope: !510)
!1406 = !DILocation(line: 1575, column: 25, scope: !510)
!1407 = !DILocation(line: 1575, column: 2, scope: !510)
!1408 = !DILocation(line: 1576, column: 24, scope: !510)
!1409 = !DILocation(line: 1576, column: 29, scope: !510)
!1410 = !DILocation(line: 1576, column: 2, scope: !510)
!1411 = !DILocation(line: 1577, column: 24, scope: !510)
!1412 = !DILocation(line: 1577, column: 29, scope: !510)
!1413 = !DILocation(line: 1577, column: 2, scope: !510)
!1414 = !DILocation(line: 1578, column: 24, scope: !510)
!1415 = !DILocation(line: 1578, column: 29, scope: !510)
!1416 = !DILocation(line: 1578, column: 2, scope: !510)
!1417 = !DILocation(line: 1579, column: 24, scope: !510)
!1418 = !DILocation(line: 1579, column: 29, scope: !510)
!1419 = !DILocation(line: 1579, column: 2, scope: !510)
!1420 = !DILocation(line: 1580, column: 25, scope: !510)
!1421 = !DILocation(line: 1580, column: 30, scope: !510)
!1422 = !DILocation(line: 1580, column: 2, scope: !510)
!1423 = !DILocation(line: 1581, column: 7, scope: !510)
!1424 = !DILocation(line: 1581, column: 2, scope: !510)
!1425 = !DILocation(line: 1582, column: 3, scope: !510)
!1426 = !DILocation(line: 1582, column: 6, scope: !510)
!1427 = !DILocation(line: 1582, column: 14, scope: !510)
!1428 = !DILocation(line: 1582, column: 20, scope: !510)
!1429 = !DILocation(line: 1583, column: 2, scope: !510)
!1430 = !DILocalVariable(name: "h", arg: 1, scope: !421, file: !1, line: 293, type: !43)
!1431 = !DILocation(line: 293, column: 37, scope: !421)
!1432 = !DILocalVariable(name: "p", scope: !421, file: !1, line: 295, type: !356)
!1433 = !DILocation(line: 295, column: 23, scope: !421)
!1434 = !DILocation(line: 295, column: 27, scope: !421)
!1435 = !DILocalVariable(name: "next_skip_bytes", scope: !421, file: !1, line: 296, type: !45)
!1436 = !DILocation(line: 296, column: 9, scope: !421)
!1437 = !DILocation(line: 298, column: 10, scope: !421)
!1438 = !DILocation(line: 298, column: 2, scope: !421)
!1439 = !DILocation(line: 307, column: 19, scope: !1440)
!1440 = distinct !DILexicalBlock(scope: !421, file: !1, line: 298, column: 32)
!1441 = !DILocation(line: 310, column: 7, scope: !1442)
!1442 = distinct !DILexicalBlock(scope: !1440, file: !1, line: 310, column: 7)
!1443 = !DILocation(line: 310, column: 12, scope: !1442)
!1444 = !DILocation(line: 310, column: 7, scope: !1440)
!1445 = !DILocation(line: 311, column: 4, scope: !1442)
!1446 = !DILocation(line: 312, column: 7, scope: !1447)
!1447 = distinct !DILexicalBlock(scope: !1440, file: !1, line: 312, column: 7)
!1448 = !DILocation(line: 312, column: 26, scope: !1447)
!1449 = !DILocation(line: 312, column: 33, scope: !1447)
!1450 = !DILocation(line: 312, column: 36, scope: !1451)
!1451 = !DILexicalBlockFile(scope: !1447, file: !1, discriminator: 1)
!1452 = !DILocation(line: 312, column: 57, scope: !1451)
!1453 = !DILocation(line: 313, column: 7, scope: !1447)
!1454 = !DILocation(line: 313, column: 11, scope: !1451)
!1455 = !DILocation(line: 313, column: 32, scope: !1451)
!1456 = !DILocation(line: 312, column: 7, scope: !1457)
!1457 = !DILexicalBlockFile(scope: !1440, file: !1, discriminator: 2)
!1458 = !DILocation(line: 314, column: 4, scope: !1447)
!1459 = !DILocation(line: 316, column: 7, scope: !1460)
!1460 = distinct !DILexicalBlock(scope: !1440, file: !1, line: 316, column: 7)
!1461 = !DILocation(line: 316, column: 28, scope: !1460)
!1462 = !DILocation(line: 316, column: 7, scope: !1440)
!1463 = !DILocation(line: 318, column: 8, scope: !1464)
!1464 = distinct !DILexicalBlock(scope: !1465, file: !1, line: 318, column: 8)
!1465 = distinct !DILexicalBlock(scope: !1460, file: !1, line: 316, column: 36)
!1466 = !DILocation(line: 318, column: 29, scope: !1464)
!1467 = !DILocation(line: 318, column: 8, scope: !1465)
!1468 = !DILocation(line: 319, column: 5, scope: !1464)
!1469 = !DILocation(line: 320, column: 8, scope: !1470)
!1470 = distinct !DILexicalBlock(scope: !1465, file: !1, line: 320, column: 8)
!1471 = !DILocation(line: 320, column: 26, scope: !1470)
!1472 = !DILocation(line: 320, column: 8, scope: !1465)
!1473 = !DILocation(line: 321, column: 5, scope: !1470)
!1474 = !DILocation(line: 322, column: 8, scope: !1475)
!1475 = distinct !DILexicalBlock(scope: !1465, file: !1, line: 322, column: 8)
!1476 = !DILocation(line: 322, column: 26, scope: !1475)
!1477 = !DILocation(line: 322, column: 31, scope: !1475)
!1478 = !DILocation(line: 322, column: 34, scope: !1479)
!1479 = !DILexicalBlockFile(scope: !1475, file: !1, discriminator: 1)
!1480 = !DILocation(line: 322, column: 51, scope: !1479)
!1481 = !DILocation(line: 322, column: 8, scope: !1479)
!1482 = !DILocation(line: 323, column: 5, scope: !1475)
!1483 = !DILocation(line: 324, column: 3, scope: !1465)
!1484 = !DILocation(line: 325, column: 7, scope: !1485)
!1485 = distinct !DILexicalBlock(scope: !1440, file: !1, line: 325, column: 7)
!1486 = !DILocation(line: 325, column: 28, scope: !1485)
!1487 = !DILocation(line: 325, column: 7, scope: !1440)
!1488 = !DILocation(line: 327, column: 8, scope: !1489)
!1489 = distinct !DILexicalBlock(scope: !1490, file: !1, line: 327, column: 8)
!1490 = distinct !DILexicalBlock(scope: !1485, file: !1, line: 325, column: 36)
!1491 = !DILocation(line: 327, column: 26, scope: !1489)
!1492 = !DILocation(line: 327, column: 8, scope: !1490)
!1493 = !DILocation(line: 328, column: 5, scope: !1489)
!1494 = !DILocation(line: 329, column: 8, scope: !1495)
!1495 = distinct !DILexicalBlock(scope: !1490, file: !1, line: 329, column: 8)
!1496 = !DILocation(line: 329, column: 29, scope: !1495)
!1497 = !DILocation(line: 330, column: 8, scope: !1495)
!1498 = !DILocation(line: 330, column: 11, scope: !1499)
!1499 = !DILexicalBlockFile(scope: !1495, file: !1, discriminator: 1)
!1500 = !DILocation(line: 330, column: 32, scope: !1499)
!1501 = !DILocation(line: 331, column: 8, scope: !1495)
!1502 = !DILocation(line: 331, column: 11, scope: !1499)
!1503 = !DILocation(line: 331, column: 32, scope: !1499)
!1504 = !DILocation(line: 329, column: 8, scope: !1505)
!1505 = !DILexicalBlockFile(scope: !1490, file: !1, discriminator: 1)
!1506 = !DILocation(line: 332, column: 5, scope: !1495)
!1507 = !DILocation(line: 333, column: 3, scope: !1490)
!1508 = !DILocation(line: 334, column: 3, scope: !1440)
!1509 = !DILocation(line: 335, column: 28, scope: !1440)
!1510 = !DILocation(line: 335, column: 33, scope: !1440)
!1511 = !DILocation(line: 336, column: 28, scope: !1440)
!1512 = !DILocation(line: 336, column: 33, scope: !1440)
!1513 = !DILocation(line: 337, column: 28, scope: !1440)
!1514 = !DILocation(line: 337, column: 33, scope: !1440)
!1515 = !DILocation(line: 338, column: 28, scope: !1440)
!1516 = !DILocation(line: 338, column: 33, scope: !1440)
!1517 = !DILocation(line: 339, column: 28, scope: !1440)
!1518 = !DILocation(line: 339, column: 33, scope: !1440)
!1519 = !DILocation(line: 342, column: 10, scope: !421)
!1520 = !DILocation(line: 342, column: 2, scope: !421)
!1521 = !DILocation(line: 343, column: 1, scope: !421)
!1522 = !DILocalVariable(name: "i", scope: !426, file: !1, line: 1670, type: !13)
!1523 = !DILocation(line: 1670, column: 15, scope: !426)
!1524 = !DILocation(line: 1673, column: 6, scope: !1525)
!1525 = distinct !DILexicalBlock(scope: !426, file: !1, line: 1673, column: 6)
!1526 = !DILocation(line: 1673, column: 6, scope: !426)
!1527 = !DILocation(line: 1674, column: 3, scope: !1525)
!1528 = !DILocation(line: 1675, column: 12, scope: !426)
!1529 = !DILocation(line: 1677, column: 9, scope: !1530)
!1530 = distinct !DILexicalBlock(scope: !426, file: !1, line: 1677, column: 2)
!1531 = !DILocation(line: 1677, column: 7, scope: !1530)
!1532 = !DILocation(line: 1677, column: 14, scope: !1533)
!1533 = !DILexicalBlockFile(scope: !1534, file: !1, discriminator: 1)
!1534 = distinct !DILexicalBlock(scope: !1530, file: !1, line: 1677, column: 2)
!1535 = !DILocation(line: 1677, column: 16, scope: !1533)
!1536 = !DILocation(line: 1677, column: 2, scope: !1533)
!1537 = !DILocalVariable(name: "j", scope: !1538, file: !1, line: 1678, type: !13)
!1538 = distinct !DILexicalBlock(scope: !1534, file: !1, line: 1677, column: 28)
!1539 = !DILocation(line: 1678, column: 16, scope: !1538)
!1540 = !DILocalVariable(name: "crc", scope: !1538, file: !1, line: 1679, type: !299)
!1541 = !DILocation(line: 1679, column: 12, scope: !1538)
!1542 = !DILocation(line: 1679, column: 28, scope: !1538)
!1543 = !DILocation(line: 1679, column: 18, scope: !1538)
!1544 = !DILocation(line: 1680, column: 10, scope: !1545)
!1545 = distinct !DILexicalBlock(scope: !1538, file: !1, line: 1680, column: 3)
!1546 = !DILocation(line: 1680, column: 8, scope: !1545)
!1547 = !DILocation(line: 1680, column: 15, scope: !1548)
!1548 = !DILexicalBlockFile(scope: !1549, file: !1, discriminator: 1)
!1549 = distinct !DILexicalBlock(scope: !1545, file: !1, line: 1680, column: 3)
!1550 = !DILocation(line: 1680, column: 3, scope: !1548)
!1551 = !DILocation(line: 1681, column: 11, scope: !1549)
!1552 = !DILocation(line: 1681, column: 15, scope: !1549)
!1553 = !DILocation(line: 1681, column: 25, scope: !1549)
!1554 = !DILocation(line: 1681, column: 29, scope: !1549)
!1555 = !DILocation(line: 1681, column: 34, scope: !1549)
!1556 = !DILocation(line: 1681, column: 21, scope: !1549)
!1557 = !DILocation(line: 1681, column: 10, scope: !1549)
!1558 = !DILocation(line: 1681, column: 8, scope: !1549)
!1559 = !DILocation(line: 1681, column: 4, scope: !1549)
!1560 = !DILocation(line: 1680, column: 19, scope: !1561)
!1561 = !DILexicalBlockFile(scope: !1549, file: !1, discriminator: 2)
!1562 = !DILocation(line: 1680, column: 3, scope: !1561)
!1563 = !DILocation(line: 1682, column: 20, scope: !1538)
!1564 = !DILocation(line: 1682, column: 15, scope: !1538)
!1565 = !DILocation(line: 1682, column: 3, scope: !1538)
!1566 = !DILocation(line: 1682, column: 18, scope: !1538)
!1567 = !DILocation(line: 1683, column: 2, scope: !1538)
!1568 = !DILocation(line: 1677, column: 24, scope: !1569)
!1569 = !DILexicalBlockFile(scope: !1534, file: !1, discriminator: 2)
!1570 = !DILocation(line: 1677, column: 2, scope: !1569)
!1571 = !DILocation(line: 1685, column: 9, scope: !1572)
!1572 = distinct !DILexicalBlock(scope: !426, file: !1, line: 1685, column: 2)
!1573 = !DILocation(line: 1685, column: 7, scope: !1572)
!1574 = !DILocation(line: 1685, column: 14, scope: !1575)
!1575 = !DILexicalBlockFile(scope: !1576, file: !1, discriminator: 1)
!1576 = distinct !DILexicalBlock(scope: !1572, file: !1, line: 1685, column: 2)
!1577 = !DILocation(line: 1685, column: 16, scope: !1575)
!1578 = !DILocation(line: 1685, column: 2, scope: !1575)
!1579 = !DILocation(line: 1686, column: 33, scope: !1580)
!1580 = distinct !DILexicalBlock(scope: !1576, file: !1, line: 1685, column: 28)
!1581 = !DILocation(line: 1686, column: 21, scope: !1580)
!1582 = !DILocation(line: 1686, column: 36, scope: !1580)
!1583 = !DILocation(line: 1687, column: 30, scope: !1580)
!1584 = !DILocation(line: 1687, column: 18, scope: !1580)
!1585 = !DILocation(line: 1687, column: 33, scope: !1580)
!1586 = !DILocation(line: 1687, column: 6, scope: !1580)
!1587 = !DILocation(line: 1687, column: 4, scope: !1580)
!1588 = !DILocation(line: 1686, column: 20, scope: !1580)
!1589 = !DILocation(line: 1686, column: 15, scope: !1580)
!1590 = !DILocation(line: 1686, column: 3, scope: !1580)
!1591 = !DILocation(line: 1686, column: 18, scope: !1580)
!1592 = !DILocation(line: 1688, column: 2, scope: !1580)
!1593 = !DILocation(line: 1685, column: 24, scope: !1594)
!1594 = !DILexicalBlockFile(scope: !1576, file: !1, discriminator: 2)
!1595 = !DILocation(line: 1685, column: 2, scope: !1594)
!1596 = !DILocation(line: 1689, column: 1, scope: !426)
!1597 = !DILocalVariable(name: "a", arg: 1, scope: !429, file: !1, line: 465, type: !4)
!1598 = !DILocation(line: 465, column: 38, scope: !429)
!1599 = !DILocation(line: 467, column: 21, scope: !429)
!1600 = !DILocation(line: 467, column: 24, scope: !429)
!1601 = !DILocation(line: 467, column: 2, scope: !429)
!1602 = !DILocation(line: 469, column: 2, scope: !429)
!1603 = !DILocalVariable(name: "a", arg: 1, scope: !430, file: !1, line: 421, type: !4)
!1604 = !DILocation(line: 421, column: 35, scope: !430)
!1605 = !DILocalVariable(name: "h", scope: !430, file: !1, line: 423, type: !43)
!1606 = !DILocation(line: 423, column: 14, scope: !430)
!1607 = !DILocalVariable(name: "p", scope: !430, file: !1, line: 424, type: !80)
!1608 = !DILocation(line: 424, column: 14, scope: !430)
!1609 = !DILocalVariable(name: "q", scope: !430, file: !1, line: 424, type: !80)
!1610 = !DILocation(line: 424, column: 18, scope: !430)
!1611 = !DILocalVariable(name: "next", scope: !430, file: !1, line: 425, type: !45)
!1612 = !DILocation(line: 425, column: 9, scope: !430)
!1613 = !DILocalVariable(name: "skip", scope: !430, file: !1, line: 425, type: !45)
!1614 = !DILocation(line: 425, column: 15, scope: !430)
!1615 = !DILocalVariable(name: "bytes", scope: !430, file: !1, line: 426, type: !38)
!1616 = !DILocation(line: 426, column: 10, scope: !430)
!1617 = !DILocalVariable(name: "window", scope: !430, file: !1, line: 426, type: !38)
!1618 = !DILocation(line: 426, column: 17, scope: !430)
!1619 = !DILocation(line: 428, column: 9, scope: !430)
!1620 = !DILocation(line: 429, column: 2, scope: !430)
!1621 = !DILocation(line: 430, column: 28, scope: !1622)
!1622 = distinct !DILexicalBlock(scope: !1623, file: !1, line: 429, column: 11)
!1623 = distinct !DILexicalBlock(scope: !1624, file: !1, line: 429, column: 2)
!1624 = distinct !DILexicalBlock(scope: !430, file: !1, line: 429, column: 2)
!1625 = !DILocation(line: 430, column: 31, scope: !1622)
!1626 = !DILocation(line: 430, column: 7, scope: !1622)
!1627 = !DILocation(line: 430, column: 5, scope: !1622)
!1628 = !DILocation(line: 431, column: 7, scope: !1629)
!1629 = distinct !DILexicalBlock(scope: !1622, file: !1, line: 431, column: 7)
!1630 = !DILocation(line: 431, column: 9, scope: !1629)
!1631 = !DILocation(line: 431, column: 7, scope: !1622)
!1632 = !DILocation(line: 433, column: 11, scope: !1633)
!1633 = distinct !DILexicalBlock(scope: !1629, file: !1, line: 431, column: 18)
!1634 = !DILocation(line: 434, column: 8, scope: !1635)
!1635 = distinct !DILexicalBlock(scope: !1633, file: !1, line: 434, column: 8)
!1636 = !DILocation(line: 434, column: 15, scope: !1635)
!1637 = !DILocation(line: 434, column: 8, scope: !1633)
!1638 = !DILocation(line: 435, column: 5, scope: !1635)
!1639 = !DILocation(line: 436, column: 4, scope: !1633)
!1640 = !DILocation(line: 438, column: 7, scope: !1641)
!1641 = distinct !DILexicalBlock(scope: !1622, file: !1, line: 438, column: 7)
!1642 = !DILocation(line: 438, column: 13, scope: !1641)
!1643 = !DILocation(line: 438, column: 7, scope: !1622)
!1644 = !DILocation(line: 439, column: 4, scope: !1641)
!1645 = !DILocation(line: 440, column: 7, scope: !1622)
!1646 = !DILocation(line: 440, column: 5, scope: !1622)
!1647 = !DILocation(line: 441, column: 7, scope: !1622)
!1648 = !DILocation(line: 441, column: 11, scope: !1622)
!1649 = !DILocation(line: 441, column: 9, scope: !1622)
!1650 = !DILocation(line: 441, column: 5, scope: !1622)
!1651 = !DILocation(line: 447, column: 3, scope: !1622)
!1652 = !DILocation(line: 447, column: 10, scope: !1653)
!1653 = !DILexicalBlockFile(scope: !1622, file: !1, discriminator: 1)
!1654 = !DILocation(line: 447, column: 12, scope: !1653)
!1655 = !DILocation(line: 447, column: 23, scope: !1653)
!1656 = !DILocation(line: 447, column: 21, scope: !1653)
!1657 = !DILocation(line: 447, column: 3, scope: !1653)
!1658 = !DILocation(line: 448, column: 40, scope: !1659)
!1659 = distinct !DILexicalBlock(scope: !1660, file: !1, line: 448, column: 8)
!1660 = distinct !DILexicalBlock(scope: !1622, file: !1, line: 447, column: 26)
!1661 = !DILocation(line: 448, column: 16, scope: !1659)
!1662 = !DILocation(line: 448, column: 14, scope: !1659)
!1663 = !DILocation(line: 448, column: 44, scope: !1659)
!1664 = !DILocation(line: 448, column: 8, scope: !1660)
!1665 = !DILocation(line: 449, column: 12, scope: !1666)
!1666 = distinct !DILexicalBlock(scope: !1659, file: !1, line: 448, column: 50)
!1667 = !DILocation(line: 449, column: 30, scope: !1666)
!1668 = !DILocation(line: 449, column: 14, scope: !1666)
!1669 = !DILocation(line: 449, column: 10, scope: !1666)
!1670 = !DILocation(line: 450, column: 28, scope: !1666)
!1671 = !DILocation(line: 450, column: 31, scope: !1666)
!1672 = !DILocation(line: 450, column: 5, scope: !1666)
!1673 = !DILocation(line: 451, column: 5, scope: !1666)
!1674 = !DILocation(line: 453, column: 9, scope: !1660)
!1675 = !DILocation(line: 453, column: 6, scope: !1660)
!1676 = !DILocation(line: 447, column: 3, scope: !1677)
!1677 = !DILexicalBlockFile(scope: !1622, file: !1, discriminator: 2)
!1678 = !DILocation(line: 455, column: 10, scope: !1622)
!1679 = !DILocation(line: 455, column: 28, scope: !1622)
!1680 = !DILocation(line: 455, column: 12, scope: !1622)
!1681 = !DILocation(line: 455, column: 8, scope: !1622)
!1682 = !DILocation(line: 456, column: 26, scope: !1622)
!1683 = !DILocation(line: 456, column: 29, scope: !1622)
!1684 = !DILocation(line: 456, column: 3, scope: !1622)
!1685 = !DILocation(line: 429, column: 2, scope: !1686)
!1686 = !DILexicalBlockFile(scope: !1623, file: !1, discriminator: 1)
!1687 = !DILocation(line: 459, column: 21, scope: !430)
!1688 = !DILocation(line: 459, column: 24, scope: !430)
!1689 = !DILocation(line: 459, column: 2, scope: !430)
!1690 = !DILocation(line: 461, column: 2, scope: !430)
!1691 = !DILocation(line: 462, column: 1, scope: !430)
!1692 = !DILocalVariable(name: "a", arg: 1, scope: !431, file: !1, line: 781, type: !4)
!1693 = !DILocation(line: 781, column: 45, scope: !431)
!1694 = !DILocalVariable(name: "lha", arg: 2, scope: !431, file: !1, line: 781, type: !292)
!1695 = !DILocation(line: 781, column: 60, scope: !431)
!1696 = !DILocalVariable(name: "p", scope: !431, file: !1, line: 783, type: !356)
!1697 = !DILocation(line: 783, column: 23, scope: !431)
!1698 = !DILocalVariable(name: "extdsize", scope: !431, file: !1, line: 784, type: !23)
!1699 = !DILocation(line: 784, column: 6, scope: !431)
!1700 = !DILocalVariable(name: "namelen", scope: !431, file: !1, line: 784, type: !23)
!1701 = !DILocation(line: 784, column: 16, scope: !431)
!1702 = !DILocalVariable(name: "headersum", scope: !431, file: !1, line: 785, type: !303)
!1703 = !DILocation(line: 785, column: 16, scope: !431)
!1704 = !DILocalVariable(name: "sum_calculated", scope: !431, file: !1, line: 785, type: !303)
!1705 = !DILocation(line: 785, column: 27, scope: !431)
!1706 = !DILocation(line: 787, column: 32, scope: !1707)
!1707 = distinct !DILexicalBlock(scope: !431, file: !1, line: 787, column: 6)
!1708 = !DILocation(line: 787, column: 11, scope: !1707)
!1709 = !DILocation(line: 787, column: 9, scope: !1707)
!1710 = !DILocation(line: 787, column: 57, scope: !1707)
!1711 = !DILocation(line: 787, column: 6, scope: !431)
!1712 = !DILocation(line: 788, column: 27, scope: !1707)
!1713 = !DILocation(line: 788, column: 11, scope: !1707)
!1714 = !DILocation(line: 788, column: 3, scope: !1707)
!1715 = !DILocation(line: 789, column: 21, scope: !431)
!1716 = !DILocation(line: 789, column: 46, scope: !431)
!1717 = !DILocation(line: 789, column: 2, scope: !431)
!1718 = !DILocation(line: 789, column: 7, scope: !431)
!1719 = !DILocation(line: 789, column: 19, scope: !431)
!1720 = !DILocation(line: 790, column: 14, scope: !431)
!1721 = !DILocation(line: 790, column: 12, scope: !431)
!1722 = !DILocation(line: 791, column: 34, scope: !431)
!1723 = !DILocation(line: 791, column: 36, scope: !431)
!1724 = !DILocation(line: 791, column: 18, scope: !431)
!1725 = !DILocation(line: 791, column: 2, scope: !431)
!1726 = !DILocation(line: 791, column: 7, scope: !431)
!1727 = !DILocation(line: 791, column: 16, scope: !431)
!1728 = !DILocation(line: 792, column: 34, scope: !431)
!1729 = !DILocation(line: 792, column: 36, scope: !431)
!1730 = !DILocation(line: 792, column: 18, scope: !431)
!1731 = !DILocation(line: 792, column: 2, scope: !431)
!1732 = !DILocation(line: 792, column: 7, scope: !431)
!1733 = !DILocation(line: 792, column: 16, scope: !431)
!1734 = !DILocation(line: 793, column: 28, scope: !431)
!1735 = !DILocation(line: 793, column: 30, scope: !431)
!1736 = !DILocation(line: 793, column: 15, scope: !431)
!1737 = !DILocation(line: 793, column: 2, scope: !431)
!1738 = !DILocation(line: 793, column: 7, scope: !431)
!1739 = !DILocation(line: 793, column: 13, scope: !431)
!1740 = !DILocation(line: 794, column: 12, scope: !431)
!1741 = !DILocation(line: 794, column: 10, scope: !431)
!1742 = !DILocation(line: 795, column: 18, scope: !431)
!1743 = !DILocation(line: 795, column: 23, scope: !431)
!1744 = !DILocation(line: 795, column: 13, scope: !431)
!1745 = !DILocation(line: 795, column: 35, scope: !431)
!1746 = !DILocation(line: 795, column: 53, scope: !431)
!1747 = !DILocation(line: 795, column: 51, scope: !431)
!1748 = !DILocation(line: 795, column: 11, scope: !431)
!1749 = !DILocation(line: 796, column: 7, scope: !1750)
!1750 = distinct !DILexicalBlock(scope: !431, file: !1, line: 796, column: 6)
!1751 = !DILocation(line: 796, column: 15, scope: !1750)
!1752 = !DILocation(line: 796, column: 21, scope: !1750)
!1753 = !DILocation(line: 796, column: 24, scope: !1754)
!1754 = !DILexicalBlockFile(scope: !1750, file: !1, discriminator: 1)
!1755 = !DILocation(line: 796, column: 33, scope: !1754)
!1756 = !DILocation(line: 796, column: 38, scope: !1754)
!1757 = !DILocation(line: 796, column: 41, scope: !1758)
!1758 = !DILexicalBlockFile(scope: !1750, file: !1, discriminator: 2)
!1759 = !DILocation(line: 796, column: 50, scope: !1758)
!1760 = !DILocation(line: 796, column: 6, scope: !1758)
!1761 = !DILocation(line: 797, column: 22, scope: !1762)
!1762 = distinct !DILexicalBlock(scope: !1750, file: !1, line: 796, column: 57)
!1763 = !DILocation(line: 797, column: 25, scope: !1762)
!1764 = !DILocation(line: 797, column: 3, scope: !1762)
!1765 = !DILocation(line: 799, column: 3, scope: !1762)
!1766 = !DILocation(line: 801, column: 32, scope: !1767)
!1767 = distinct !DILexicalBlock(scope: !431, file: !1, line: 801, column: 6)
!1768 = !DILocation(line: 801, column: 35, scope: !1767)
!1769 = !DILocation(line: 801, column: 40, scope: !1767)
!1770 = !DILocation(line: 801, column: 11, scope: !1767)
!1771 = !DILocation(line: 801, column: 9, scope: !1767)
!1772 = !DILocation(line: 801, column: 60, scope: !1767)
!1773 = !DILocation(line: 801, column: 6, scope: !431)
!1774 = !DILocation(line: 802, column: 27, scope: !1767)
!1775 = !DILocation(line: 802, column: 11, scope: !1767)
!1776 = !DILocation(line: 802, column: 3, scope: !1767)
!1777 = !DILocation(line: 804, column: 2, scope: !431)
!1778 = !DILocation(line: 806, column: 6, scope: !1779)
!1779 = distinct !DILexicalBlock(scope: !431, file: !1, line: 806, column: 6)
!1780 = !DILocation(line: 806, column: 15, scope: !1779)
!1781 = !DILocation(line: 806, column: 6, scope: !431)
!1782 = !DILocation(line: 807, column: 30, scope: !1783)
!1783 = distinct !DILexicalBlock(scope: !1779, file: !1, line: 806, column: 21)
!1784 = !DILocation(line: 807, column: 32, scope: !1783)
!1785 = !DILocation(line: 807, column: 56, scope: !1783)
!1786 = !DILocation(line: 807, column: 54, scope: !1783)
!1787 = !DILocation(line: 807, column: 14, scope: !1783)
!1788 = !DILocation(line: 807, column: 3, scope: !1783)
!1789 = !DILocation(line: 807, column: 8, scope: !1783)
!1790 = !DILocation(line: 807, column: 12, scope: !1783)
!1791 = !DILocation(line: 808, column: 3, scope: !1783)
!1792 = !DILocation(line: 808, column: 8, scope: !1783)
!1793 = !DILocation(line: 808, column: 16, scope: !1783)
!1794 = !DILocation(line: 809, column: 2, scope: !1783)
!1795 = !DILocation(line: 810, column: 34, scope: !431)
!1796 = !DILocation(line: 810, column: 40, scope: !431)
!1797 = !DILocation(line: 810, column: 45, scope: !431)
!1798 = !DILocation(line: 810, column: 57, scope: !431)
!1799 = !DILocation(line: 810, column: 19, scope: !431)
!1800 = !DILocation(line: 810, column: 17, scope: !431)
!1801 = !DILocation(line: 813, column: 6, scope: !1802)
!1802 = distinct !DILexicalBlock(scope: !431, file: !1, line: 813, column: 6)
!1803 = !DILocation(line: 813, column: 15, scope: !1802)
!1804 = !DILocation(line: 813, column: 6, scope: !431)
!1805 = !DILocation(line: 817, column: 30, scope: !1806)
!1806 = distinct !DILexicalBlock(scope: !1802, file: !1, line: 813, column: 20)
!1807 = !DILocation(line: 817, column: 28, scope: !1806)
!1808 = !DILocation(line: 817, column: 38, scope: !1806)
!1809 = !DILocation(line: 817, column: 5, scope: !1806)
!1810 = !DILocation(line: 818, column: 7, scope: !1811)
!1811 = distinct !DILexicalBlock(scope: !1806, file: !1, line: 818, column: 7)
!1812 = !DILocation(line: 818, column: 12, scope: !1811)
!1813 = !DILocation(line: 818, column: 19, scope: !1811)
!1814 = !DILocation(line: 818, column: 22, scope: !1815)
!1815 = !DILexicalBlockFile(scope: !1811, file: !1, discriminator: 1)
!1816 = !DILocation(line: 818, column: 31, scope: !1815)
!1817 = !DILocation(line: 818, column: 7, scope: !1815)
!1818 = !DILocation(line: 820, column: 34, scope: !1819)
!1819 = distinct !DILexicalBlock(scope: !1811, file: !1, line: 818, column: 38)
!1820 = !DILocation(line: 820, column: 17, scope: !1819)
!1821 = !DILocation(line: 820, column: 4, scope: !1819)
!1822 = !DILocation(line: 820, column: 9, scope: !1819)
!1823 = !DILocation(line: 820, column: 15, scope: !1819)
!1824 = !DILocation(line: 821, column: 33, scope: !1819)
!1825 = !DILocation(line: 821, column: 16, scope: !1819)
!1826 = !DILocation(line: 821, column: 4, scope: !1819)
!1827 = !DILocation(line: 821, column: 9, scope: !1819)
!1828 = !DILocation(line: 821, column: 14, scope: !1819)
!1829 = !DILocation(line: 822, column: 32, scope: !1819)
!1830 = !DILocation(line: 822, column: 15, scope: !1819)
!1831 = !DILocation(line: 822, column: 4, scope: !1819)
!1832 = !DILocation(line: 822, column: 9, scope: !1819)
!1833 = !DILocation(line: 822, column: 13, scope: !1819)
!1834 = !DILocation(line: 823, column: 32, scope: !1819)
!1835 = !DILocation(line: 823, column: 15, scope: !1819)
!1836 = !DILocation(line: 823, column: 4, scope: !1819)
!1837 = !DILocation(line: 823, column: 9, scope: !1819)
!1838 = !DILocation(line: 823, column: 13, scope: !1819)
!1839 = !DILocation(line: 824, column: 4, scope: !1819)
!1840 = !DILocation(line: 824, column: 9, scope: !1819)
!1841 = !DILocation(line: 824, column: 17, scope: !1819)
!1842 = !DILocation(line: 825, column: 3, scope: !1819)
!1843 = !DILocation(line: 826, column: 2, scope: !1806)
!1844 = !DILocation(line: 827, column: 25, scope: !431)
!1845 = !DILocation(line: 827, column: 28, scope: !431)
!1846 = !DILocation(line: 827, column: 33, scope: !431)
!1847 = !DILocation(line: 827, column: 2, scope: !431)
!1848 = !DILocation(line: 829, column: 6, scope: !1849)
!1849 = distinct !DILexicalBlock(scope: !431, file: !1, line: 829, column: 6)
!1850 = !DILocation(line: 829, column: 24, scope: !1849)
!1851 = !DILocation(line: 829, column: 21, scope: !1849)
!1852 = !DILocation(line: 829, column: 6, scope: !431)
!1853 = !DILocation(line: 830, column: 22, scope: !1854)
!1854 = distinct !DILexicalBlock(scope: !1849, file: !1, line: 829, column: 35)
!1855 = !DILocation(line: 830, column: 25, scope: !1854)
!1856 = !DILocation(line: 830, column: 3, scope: !1854)
!1857 = !DILocation(line: 832, column: 3, scope: !1854)
!1858 = !DILocation(line: 835, column: 2, scope: !431)
!1859 = !DILocation(line: 836, column: 1, scope: !431)
!1860 = !DILocalVariable(name: "a", arg: 1, scope: !447, file: !1, line: 875, type: !4)
!1861 = !DILocation(line: 875, column: 45, scope: !447)
!1862 = !DILocalVariable(name: "lha", arg: 2, scope: !447, file: !1, line: 875, type: !292)
!1863 = !DILocation(line: 875, column: 60, scope: !447)
!1864 = !DILocalVariable(name: "p", scope: !447, file: !1, line: 877, type: !356)
!1865 = !DILocation(line: 877, column: 23, scope: !447)
!1866 = !DILocalVariable(name: "extdsize", scope: !447, file: !1, line: 878, type: !45)
!1867 = !DILocation(line: 878, column: 9, scope: !447)
!1868 = !DILocalVariable(name: "i", scope: !447, file: !1, line: 879, type: !23)
!1869 = !DILocation(line: 879, column: 6, scope: !447)
!1870 = !DILocalVariable(name: "err", scope: !447, file: !1, line: 879, type: !23)
!1871 = !DILocation(line: 879, column: 9, scope: !447)
!1872 = !DILocalVariable(name: "err2", scope: !447, file: !1, line: 879, type: !23)
!1873 = !DILocation(line: 879, column: 14, scope: !447)
!1874 = !DILocalVariable(name: "namelen", scope: !447, file: !1, line: 880, type: !23)
!1875 = !DILocation(line: 880, column: 6, scope: !447)
!1876 = !DILocalVariable(name: "padding", scope: !447, file: !1, line: 880, type: !23)
!1877 = !DILocation(line: 880, column: 15, scope: !447)
!1878 = !DILocalVariable(name: "headersum", scope: !447, file: !1, line: 881, type: !303)
!1879 = !DILocation(line: 881, column: 16, scope: !447)
!1880 = !DILocalVariable(name: "sum_calculated", scope: !447, file: !1, line: 881, type: !303)
!1881 = !DILocation(line: 881, column: 27, scope: !447)
!1882 = !DILocation(line: 883, column: 6, scope: !447)
!1883 = !DILocation(line: 885, column: 32, scope: !1884)
!1884 = distinct !DILexicalBlock(scope: !447, file: !1, line: 885, column: 6)
!1885 = !DILocation(line: 885, column: 11, scope: !1884)
!1886 = !DILocation(line: 885, column: 9, scope: !1884)
!1887 = !DILocation(line: 885, column: 57, scope: !1884)
!1888 = !DILocation(line: 885, column: 6, scope: !447)
!1889 = !DILocation(line: 886, column: 27, scope: !1884)
!1890 = !DILocation(line: 886, column: 11, scope: !1884)
!1891 = !DILocation(line: 886, column: 3, scope: !1884)
!1892 = !DILocation(line: 888, column: 21, scope: !447)
!1893 = !DILocation(line: 888, column: 46, scope: !447)
!1894 = !DILocation(line: 888, column: 2, scope: !447)
!1895 = !DILocation(line: 888, column: 7, scope: !447)
!1896 = !DILocation(line: 888, column: 19, scope: !447)
!1897 = !DILocation(line: 889, column: 14, scope: !447)
!1898 = !DILocation(line: 889, column: 12, scope: !447)
!1899 = !DILocation(line: 891, column: 34, scope: !447)
!1900 = !DILocation(line: 891, column: 36, scope: !447)
!1901 = !DILocation(line: 891, column: 18, scope: !447)
!1902 = !DILocation(line: 891, column: 2, scope: !447)
!1903 = !DILocation(line: 891, column: 7, scope: !447)
!1904 = !DILocation(line: 891, column: 16, scope: !447)
!1905 = !DILocation(line: 892, column: 34, scope: !447)
!1906 = !DILocation(line: 892, column: 36, scope: !447)
!1907 = !DILocation(line: 892, column: 18, scope: !447)
!1908 = !DILocation(line: 892, column: 2, scope: !447)
!1909 = !DILocation(line: 892, column: 7, scope: !447)
!1910 = !DILocation(line: 892, column: 16, scope: !447)
!1911 = !DILocation(line: 893, column: 28, scope: !447)
!1912 = !DILocation(line: 893, column: 30, scope: !447)
!1913 = !DILocation(line: 893, column: 15, scope: !447)
!1914 = !DILocation(line: 893, column: 2, scope: !447)
!1915 = !DILocation(line: 893, column: 7, scope: !447)
!1916 = !DILocation(line: 893, column: 13, scope: !447)
!1917 = !DILocation(line: 894, column: 12, scope: !447)
!1918 = !DILocation(line: 894, column: 10, scope: !447)
!1919 = !DILocation(line: 896, column: 18, scope: !447)
!1920 = !DILocation(line: 896, column: 23, scope: !447)
!1921 = !DILocation(line: 896, column: 13, scope: !447)
!1922 = !DILocation(line: 896, column: 36, scope: !447)
!1923 = !DILocation(line: 896, column: 54, scope: !447)
!1924 = !DILocation(line: 896, column: 52, scope: !447)
!1925 = !DILocation(line: 896, column: 10, scope: !447)
!1926 = !DILocation(line: 898, column: 6, scope: !1927)
!1927 = distinct !DILexicalBlock(scope: !447, file: !1, line: 898, column: 6)
!1928 = !DILocation(line: 898, column: 14, scope: !1927)
!1929 = !DILocation(line: 898, column: 20, scope: !1927)
!1930 = !DILocation(line: 898, column: 23, scope: !1931)
!1931 = !DILexicalBlockFile(scope: !1927, file: !1, discriminator: 1)
!1932 = !DILocation(line: 898, column: 31, scope: !1931)
!1933 = !DILocation(line: 898, column: 6, scope: !1931)
!1934 = !DILocation(line: 899, column: 3, scope: !1927)
!1935 = !DILocation(line: 901, column: 32, scope: !1936)
!1936 = distinct !DILexicalBlock(scope: !447, file: !1, line: 901, column: 6)
!1937 = !DILocation(line: 901, column: 35, scope: !1936)
!1938 = !DILocation(line: 901, column: 40, scope: !1936)
!1939 = !DILocation(line: 901, column: 11, scope: !1936)
!1940 = !DILocation(line: 901, column: 9, scope: !1936)
!1941 = !DILocation(line: 901, column: 60, scope: !1936)
!1942 = !DILocation(line: 901, column: 6, scope: !447)
!1943 = !DILocation(line: 902, column: 27, scope: !1936)
!1944 = !DILocation(line: 902, column: 11, scope: !1936)
!1945 = !DILocation(line: 902, column: 3, scope: !1936)
!1946 = !DILocation(line: 904, column: 9, scope: !1947)
!1947 = distinct !DILexicalBlock(scope: !447, file: !1, line: 904, column: 2)
!1948 = !DILocation(line: 904, column: 7, scope: !1947)
!1949 = !DILocation(line: 904, column: 14, scope: !1950)
!1950 = !DILexicalBlockFile(scope: !1951, file: !1, discriminator: 1)
!1951 = distinct !DILexicalBlock(scope: !1947, file: !1, line: 904, column: 2)
!1952 = !DILocation(line: 904, column: 18, scope: !1950)
!1953 = !DILocation(line: 904, column: 16, scope: !1950)
!1954 = !DILocation(line: 904, column: 2, scope: !1950)
!1955 = !DILocation(line: 905, column: 9, scope: !1956)
!1956 = distinct !DILexicalBlock(scope: !1957, file: !1, line: 905, column: 7)
!1957 = distinct !DILexicalBlock(scope: !1951, file: !1, line: 904, column: 32)
!1958 = !DILocation(line: 905, column: 11, scope: !1956)
!1959 = !DILocation(line: 905, column: 7, scope: !1956)
!1960 = !DILocation(line: 905, column: 34, scope: !1956)
!1961 = !DILocation(line: 905, column: 7, scope: !1957)
!1962 = !DILocation(line: 906, column: 4, scope: !1956)
!1963 = !DILocation(line: 907, column: 2, scope: !1957)
!1964 = !DILocation(line: 904, column: 28, scope: !1965)
!1965 = !DILexicalBlockFile(scope: !1951, file: !1, discriminator: 2)
!1966 = !DILocation(line: 904, column: 2, scope: !1965)
!1967 = !DILocation(line: 908, column: 2, scope: !447)
!1968 = !DILocation(line: 909, column: 29, scope: !447)
!1969 = !DILocation(line: 909, column: 31, scope: !447)
!1970 = !DILocation(line: 909, column: 55, scope: !447)
!1971 = !DILocation(line: 909, column: 53, scope: !447)
!1972 = !DILocation(line: 909, column: 13, scope: !447)
!1973 = !DILocation(line: 909, column: 2, scope: !447)
!1974 = !DILocation(line: 909, column: 7, scope: !447)
!1975 = !DILocation(line: 909, column: 11, scope: !447)
!1976 = !DILocation(line: 910, column: 2, scope: !447)
!1977 = !DILocation(line: 910, column: 7, scope: !447)
!1978 = !DILocation(line: 910, column: 15, scope: !447)
!1979 = !DILocation(line: 912, column: 34, scope: !447)
!1980 = !DILocation(line: 912, column: 40, scope: !447)
!1981 = !DILocation(line: 912, column: 45, scope: !447)
!1982 = !DILocation(line: 912, column: 57, scope: !447)
!1983 = !DILocation(line: 912, column: 19, scope: !447)
!1984 = !DILocation(line: 912, column: 17, scope: !447)
!1985 = !DILocation(line: 915, column: 25, scope: !447)
!1986 = !DILocation(line: 915, column: 28, scope: !447)
!1987 = !DILocation(line: 915, column: 33, scope: !447)
!1988 = !DILocation(line: 915, column: 45, scope: !447)
!1989 = !DILocation(line: 915, column: 2, scope: !447)
!1990 = !DILocation(line: 918, column: 39, scope: !447)
!1991 = !DILocation(line: 918, column: 42, scope: !447)
!1992 = !DILocation(line: 919, column: 15, scope: !447)
!1993 = !DILocation(line: 919, column: 20, scope: !447)
!1994 = !DILocation(line: 919, column: 29, scope: !447)
!1995 = !DILocation(line: 918, column: 9, scope: !447)
!1996 = !DILocation(line: 918, column: 7, scope: !447)
!1997 = !DILocation(line: 920, column: 6, scope: !1998)
!1998 = distinct !DILexicalBlock(scope: !447, file: !1, line: 920, column: 6)
!1999 = !DILocation(line: 920, column: 11, scope: !1998)
!2000 = !DILocation(line: 920, column: 6, scope: !447)
!2001 = !DILocation(line: 921, column: 11, scope: !1998)
!2002 = !DILocation(line: 921, column: 3, scope: !1998)
!2003 = !DILocation(line: 922, column: 6, scope: !2004)
!2004 = distinct !DILexicalBlock(scope: !447, file: !1, line: 922, column: 6)
!2005 = !DILocation(line: 922, column: 13, scope: !2004)
!2006 = !DILocation(line: 922, column: 11, scope: !2004)
!2007 = !DILocation(line: 922, column: 6, scope: !447)
!2008 = !DILocation(line: 923, column: 9, scope: !2004)
!2009 = !DILocation(line: 923, column: 7, scope: !2004)
!2010 = !DILocation(line: 923, column: 3, scope: !2004)
!2011 = !DILocation(line: 925, column: 19, scope: !447)
!2012 = !DILocation(line: 925, column: 28, scope: !447)
!2013 = !DILocation(line: 925, column: 2, scope: !447)
!2014 = !DILocation(line: 925, column: 7, scope: !447)
!2015 = !DILocation(line: 925, column: 16, scope: !447)
!2016 = !DILocation(line: 927, column: 6, scope: !2017)
!2017 = distinct !DILexicalBlock(scope: !447, file: !1, line: 927, column: 6)
!2018 = !DILocation(line: 927, column: 11, scope: !2017)
!2019 = !DILocation(line: 927, column: 20, scope: !2017)
!2020 = !DILocation(line: 927, column: 6, scope: !447)
!2021 = !DILocation(line: 928, column: 3, scope: !2017)
!2022 = !DILocation(line: 930, column: 6, scope: !2023)
!2023 = distinct !DILexicalBlock(scope: !447, file: !1, line: 930, column: 6)
!2024 = !DILocation(line: 930, column: 24, scope: !2023)
!2025 = !DILocation(line: 930, column: 21, scope: !2023)
!2026 = !DILocation(line: 930, column: 6, scope: !447)
!2027 = !DILocation(line: 931, column: 22, scope: !2028)
!2028 = distinct !DILexicalBlock(scope: !2023, file: !1, line: 930, column: 35)
!2029 = !DILocation(line: 931, column: 25, scope: !2028)
!2030 = !DILocation(line: 931, column: 3, scope: !2028)
!2031 = !DILocation(line: 933, column: 3, scope: !2028)
!2032 = !DILocation(line: 935, column: 10, scope: !447)
!2033 = !DILocation(line: 935, column: 2, scope: !447)
!2034 = !DILocation(line: 937, column: 21, scope: !447)
!2035 = !DILocation(line: 937, column: 24, scope: !447)
!2036 = !DILocation(line: 937, column: 2, scope: !447)
!2037 = !DILocation(line: 939, column: 2, scope: !447)
!2038 = !DILocation(line: 940, column: 1, scope: !447)
!2039 = !DILocalVariable(name: "a", arg: 1, scope: !461, file: !1, line: 971, type: !4)
!2040 = !DILocation(line: 971, column: 45, scope: !461)
!2041 = !DILocalVariable(name: "lha", arg: 2, scope: !461, file: !1, line: 971, type: !292)
!2042 = !DILocation(line: 971, column: 60, scope: !461)
!2043 = !DILocalVariable(name: "p", scope: !461, file: !1, line: 973, type: !356)
!2044 = !DILocation(line: 973, column: 23, scope: !461)
!2045 = !DILocalVariable(name: "extdsize", scope: !461, file: !1, line: 974, type: !45)
!2046 = !DILocation(line: 974, column: 9, scope: !461)
!2047 = !DILocalVariable(name: "err", scope: !461, file: !1, line: 975, type: !23)
!2048 = !DILocation(line: 975, column: 6, scope: !461)
!2049 = !DILocalVariable(name: "padding", scope: !461, file: !1, line: 975, type: !23)
!2050 = !DILocation(line: 975, column: 11, scope: !461)
!2051 = !DILocalVariable(name: "header_crc", scope: !461, file: !1, line: 976, type: !299)
!2052 = !DILocation(line: 976, column: 11, scope: !461)
!2053 = !DILocation(line: 978, column: 32, scope: !2054)
!2054 = distinct !DILexicalBlock(scope: !461, file: !1, line: 978, column: 6)
!2055 = !DILocation(line: 978, column: 11, scope: !2054)
!2056 = !DILocation(line: 978, column: 9, scope: !2054)
!2057 = !DILocation(line: 978, column: 57, scope: !2054)
!2058 = !DILocation(line: 978, column: 6, scope: !461)
!2059 = !DILocation(line: 979, column: 27, scope: !2054)
!2060 = !DILocation(line: 979, column: 11, scope: !2054)
!2061 = !DILocation(line: 979, column: 3, scope: !2054)
!2062 = !DILocation(line: 981, column: 36, scope: !461)
!2063 = !DILocation(line: 981, column: 38, scope: !461)
!2064 = !DILocation(line: 981, column: 20, scope: !461)
!2065 = !DILocation(line: 981, column: 2, scope: !461)
!2066 = !DILocation(line: 981, column: 7, scope: !461)
!2067 = !DILocation(line: 981, column: 19, scope: !461)
!2068 = !DILocation(line: 982, column: 34, scope: !461)
!2069 = !DILocation(line: 982, column: 36, scope: !461)
!2070 = !DILocation(line: 982, column: 18, scope: !461)
!2071 = !DILocation(line: 982, column: 2, scope: !461)
!2072 = !DILocation(line: 982, column: 7, scope: !461)
!2073 = !DILocation(line: 982, column: 16, scope: !461)
!2074 = !DILocation(line: 983, column: 34, scope: !461)
!2075 = !DILocation(line: 983, column: 36, scope: !461)
!2076 = !DILocation(line: 983, column: 18, scope: !461)
!2077 = !DILocation(line: 983, column: 2, scope: !461)
!2078 = !DILocation(line: 983, column: 7, scope: !461)
!2079 = !DILocation(line: 983, column: 16, scope: !461)
!2080 = !DILocation(line: 984, column: 31, scope: !461)
!2081 = !DILocation(line: 984, column: 33, scope: !461)
!2082 = !DILocation(line: 984, column: 15, scope: !461)
!2083 = !DILocation(line: 984, column: 2, scope: !461)
!2084 = !DILocation(line: 984, column: 7, scope: !461)
!2085 = !DILocation(line: 984, column: 13, scope: !461)
!2086 = !DILocation(line: 985, column: 29, scope: !461)
!2087 = !DILocation(line: 985, column: 31, scope: !461)
!2088 = !DILocation(line: 985, column: 13, scope: !461)
!2089 = !DILocation(line: 985, column: 2, scope: !461)
!2090 = !DILocation(line: 985, column: 7, scope: !461)
!2091 = !DILocation(line: 985, column: 11, scope: !461)
!2092 = !DILocation(line: 986, column: 2, scope: !461)
!2093 = !DILocation(line: 986, column: 7, scope: !461)
!2094 = !DILocation(line: 986, column: 15, scope: !461)
!2095 = !DILocation(line: 988, column: 6, scope: !2096)
!2096 = distinct !DILexicalBlock(scope: !461, file: !1, line: 988, column: 6)
!2097 = !DILocation(line: 988, column: 11, scope: !2096)
!2098 = !DILocation(line: 988, column: 23, scope: !2096)
!2099 = !DILocation(line: 988, column: 6, scope: !461)
!2100 = !DILocation(line: 989, column: 22, scope: !2101)
!2101 = distinct !DILexicalBlock(scope: !2096, file: !1, line: 988, column: 40)
!2102 = !DILocation(line: 989, column: 25, scope: !2101)
!2103 = !DILocation(line: 989, column: 3, scope: !2101)
!2104 = !DILocation(line: 991, column: 3, scope: !2101)
!2105 = !DILocation(line: 994, column: 28, scope: !461)
!2106 = !DILocation(line: 994, column: 15, scope: !461)
!2107 = !DILocation(line: 994, column: 13, scope: !461)
!2108 = !DILocation(line: 995, column: 25, scope: !461)
!2109 = !DILocation(line: 995, column: 2, scope: !461)
!2110 = !DILocation(line: 998, column: 38, scope: !461)
!2111 = !DILocation(line: 998, column: 41, scope: !461)
!2112 = !DILocation(line: 999, column: 5, scope: !461)
!2113 = !DILocation(line: 999, column: 10, scope: !461)
!2114 = !DILocation(line: 999, column: 22, scope: !461)
!2115 = !DILocation(line: 998, column: 8, scope: !461)
!2116 = !DILocation(line: 998, column: 6, scope: !461)
!2117 = !DILocation(line: 1000, column: 6, scope: !2118)
!2118 = distinct !DILexicalBlock(scope: !461, file: !1, line: 1000, column: 6)
!2119 = !DILocation(line: 1000, column: 10, scope: !2118)
!2120 = !DILocation(line: 1000, column: 6, scope: !461)
!2121 = !DILocation(line: 1001, column: 11, scope: !2118)
!2122 = !DILocation(line: 1001, column: 3, scope: !2118)
!2123 = !DILocation(line: 1004, column: 17, scope: !461)
!2124 = !DILocation(line: 1004, column: 22, scope: !461)
!2125 = !DILocation(line: 1004, column: 12, scope: !461)
!2126 = !DILocation(line: 1004, column: 58, scope: !461)
!2127 = !DILocation(line: 1004, column: 56, scope: !461)
!2128 = !DILocation(line: 1004, column: 36, scope: !461)
!2129 = !DILocation(line: 1004, column: 34, scope: !461)
!2130 = !DILocation(line: 1004, column: 10, scope: !461)
!2131 = !DILocation(line: 1005, column: 6, scope: !2132)
!2132 = distinct !DILexicalBlock(scope: !461, file: !1, line: 1005, column: 6)
!2133 = !DILocation(line: 1005, column: 14, scope: !2132)
!2134 = !DILocation(line: 1005, column: 6, scope: !461)
!2135 = !DILocation(line: 1006, column: 33, scope: !2136)
!2136 = distinct !DILexicalBlock(scope: !2137, file: !1, line: 1006, column: 7)
!2137 = distinct !DILexicalBlock(scope: !2132, file: !1, line: 1005, column: 19)
!2138 = !DILocation(line: 1006, column: 36, scope: !2136)
!2139 = !DILocation(line: 1006, column: 12, scope: !2136)
!2140 = !DILocation(line: 1006, column: 10, scope: !2136)
!2141 = !DILocation(line: 1006, column: 52, scope: !2136)
!2142 = !DILocation(line: 1006, column: 7, scope: !2137)
!2143 = !DILocation(line: 1007, column: 28, scope: !2136)
!2144 = !DILocation(line: 1007, column: 12, scope: !2136)
!2145 = !DILocation(line: 1007, column: 4, scope: !2136)
!2146 = !DILocation(line: 1008, column: 26, scope: !2137)
!2147 = !DILocation(line: 1008, column: 38, scope: !2137)
!2148 = !DILocation(line: 1008, column: 41, scope: !2137)
!2149 = !DILocation(line: 1008, column: 16, scope: !2137)
!2150 = !DILocation(line: 1008, column: 14, scope: !2137)
!2151 = !DILocation(line: 1009, column: 26, scope: !2137)
!2152 = !DILocation(line: 1009, column: 29, scope: !2137)
!2153 = !DILocation(line: 1009, column: 3, scope: !2137)
!2154 = !DILocation(line: 1010, column: 2, scope: !2137)
!2155 = !DILocation(line: 1012, column: 6, scope: !2156)
!2156 = distinct !DILexicalBlock(scope: !461, file: !1, line: 1012, column: 6)
!2157 = !DILocation(line: 1012, column: 20, scope: !2156)
!2158 = !DILocation(line: 1012, column: 25, scope: !2156)
!2159 = !DILocation(line: 1012, column: 17, scope: !2156)
!2160 = !DILocation(line: 1012, column: 6, scope: !461)
!2161 = !DILocation(line: 1013, column: 22, scope: !2162)
!2162 = distinct !DILexicalBlock(scope: !2156, file: !1, line: 1012, column: 37)
!2163 = !DILocation(line: 1013, column: 25, scope: !2162)
!2164 = !DILocation(line: 1013, column: 3, scope: !2162)
!2165 = !DILocation(line: 1015, column: 3, scope: !2162)
!2166 = !DILocation(line: 1017, column: 10, scope: !461)
!2167 = !DILocation(line: 1017, column: 2, scope: !461)
!2168 = !DILocation(line: 1018, column: 1, scope: !461)
!2169 = !DILocalVariable(name: "a", arg: 1, scope: !462, file: !1, line: 1050, type: !4)
!2170 = !DILocation(line: 1050, column: 45, scope: !462)
!2171 = !DILocalVariable(name: "lha", arg: 2, scope: !462, file: !1, line: 1050, type: !292)
!2172 = !DILocation(line: 1050, column: 60, scope: !462)
!2173 = !DILocalVariable(name: "p", scope: !462, file: !1, line: 1052, type: !356)
!2174 = !DILocation(line: 1052, column: 23, scope: !462)
!2175 = !DILocalVariable(name: "extdsize", scope: !462, file: !1, line: 1053, type: !45)
!2176 = !DILocation(line: 1053, column: 9, scope: !462)
!2177 = !DILocalVariable(name: "err", scope: !462, file: !1, line: 1054, type: !23)
!2178 = !DILocation(line: 1054, column: 6, scope: !462)
!2179 = !DILocalVariable(name: "header_crc", scope: !462, file: !1, line: 1055, type: !299)
!2180 = !DILocation(line: 1055, column: 11, scope: !462)
!2181 = !DILocation(line: 1057, column: 32, scope: !2182)
!2182 = distinct !DILexicalBlock(scope: !462, file: !1, line: 1057, column: 6)
!2183 = !DILocation(line: 1057, column: 11, scope: !2182)
!2184 = !DILocation(line: 1057, column: 9, scope: !2182)
!2185 = !DILocation(line: 1057, column: 57, scope: !2182)
!2186 = !DILocation(line: 1057, column: 6, scope: !462)
!2187 = !DILocation(line: 1058, column: 27, scope: !2182)
!2188 = !DILocation(line: 1058, column: 11, scope: !2182)
!2189 = !DILocation(line: 1058, column: 3, scope: !2182)
!2190 = !DILocation(line: 1060, column: 22, scope: !2191)
!2191 = distinct !DILexicalBlock(scope: !462, file: !1, line: 1060, column: 6)
!2192 = !DILocation(line: 1060, column: 24, scope: !2191)
!2193 = !DILocation(line: 1060, column: 6, scope: !2191)
!2194 = !DILocation(line: 1060, column: 47, scope: !2191)
!2195 = !DILocation(line: 1060, column: 6, scope: !462)
!2196 = !DILocation(line: 1061, column: 3, scope: !2191)
!2197 = !DILocation(line: 1062, column: 36, scope: !462)
!2198 = !DILocation(line: 1062, column: 38, scope: !462)
!2199 = !DILocation(line: 1062, column: 20, scope: !462)
!2200 = !DILocation(line: 1062, column: 2, scope: !462)
!2201 = !DILocation(line: 1062, column: 7, scope: !462)
!2202 = !DILocation(line: 1062, column: 19, scope: !462)
!2203 = !DILocation(line: 1063, column: 34, scope: !462)
!2204 = !DILocation(line: 1063, column: 36, scope: !462)
!2205 = !DILocation(line: 1063, column: 18, scope: !462)
!2206 = !DILocation(line: 1063, column: 2, scope: !462)
!2207 = !DILocation(line: 1063, column: 7, scope: !462)
!2208 = !DILocation(line: 1063, column: 16, scope: !462)
!2209 = !DILocation(line: 1064, column: 34, scope: !462)
!2210 = !DILocation(line: 1064, column: 36, scope: !462)
!2211 = !DILocation(line: 1064, column: 18, scope: !462)
!2212 = !DILocation(line: 1064, column: 2, scope: !462)
!2213 = !DILocation(line: 1064, column: 7, scope: !462)
!2214 = !DILocation(line: 1064, column: 16, scope: !462)
!2215 = !DILocation(line: 1065, column: 31, scope: !462)
!2216 = !DILocation(line: 1065, column: 33, scope: !462)
!2217 = !DILocation(line: 1065, column: 15, scope: !462)
!2218 = !DILocation(line: 1065, column: 2, scope: !462)
!2219 = !DILocation(line: 1065, column: 7, scope: !462)
!2220 = !DILocation(line: 1065, column: 13, scope: !462)
!2221 = !DILocation(line: 1066, column: 29, scope: !462)
!2222 = !DILocation(line: 1066, column: 31, scope: !462)
!2223 = !DILocation(line: 1066, column: 13, scope: !462)
!2224 = !DILocation(line: 1066, column: 2, scope: !462)
!2225 = !DILocation(line: 1066, column: 7, scope: !462)
!2226 = !DILocation(line: 1066, column: 11, scope: !462)
!2227 = !DILocation(line: 1067, column: 2, scope: !462)
!2228 = !DILocation(line: 1067, column: 7, scope: !462)
!2229 = !DILocation(line: 1067, column: 15, scope: !462)
!2230 = !DILocation(line: 1069, column: 6, scope: !2231)
!2231 = distinct !DILexicalBlock(scope: !462, file: !1, line: 1069, column: 6)
!2232 = !DILocation(line: 1069, column: 11, scope: !2231)
!2233 = !DILocation(line: 1069, column: 23, scope: !2231)
!2234 = !DILocation(line: 1069, column: 6, scope: !462)
!2235 = !DILocation(line: 1070, column: 3, scope: !2231)
!2236 = !DILocation(line: 1071, column: 28, scope: !462)
!2237 = !DILocation(line: 1071, column: 15, scope: !462)
!2238 = !DILocation(line: 1071, column: 13, scope: !462)
!2239 = !DILocation(line: 1072, column: 25, scope: !462)
!2240 = !DILocation(line: 1072, column: 2, scope: !462)
!2241 = !DILocation(line: 1075, column: 38, scope: !462)
!2242 = !DILocation(line: 1075, column: 41, scope: !462)
!2243 = !DILocation(line: 1076, column: 5, scope: !462)
!2244 = !DILocation(line: 1076, column: 10, scope: !462)
!2245 = !DILocation(line: 1076, column: 22, scope: !462)
!2246 = !DILocation(line: 1075, column: 8, scope: !462)
!2247 = !DILocation(line: 1075, column: 6, scope: !462)
!2248 = !DILocation(line: 1077, column: 6, scope: !2249)
!2249 = distinct !DILexicalBlock(scope: !462, file: !1, line: 1077, column: 6)
!2250 = !DILocation(line: 1077, column: 10, scope: !2249)
!2251 = !DILocation(line: 1077, column: 6, scope: !462)
!2252 = !DILocation(line: 1078, column: 11, scope: !2249)
!2253 = !DILocation(line: 1078, column: 3, scope: !2249)
!2254 = !DILocation(line: 1080, column: 6, scope: !2255)
!2255 = distinct !DILexicalBlock(scope: !462, file: !1, line: 1080, column: 6)
!2256 = !DILocation(line: 1080, column: 20, scope: !2255)
!2257 = !DILocation(line: 1080, column: 25, scope: !2255)
!2258 = !DILocation(line: 1080, column: 17, scope: !2255)
!2259 = !DILocation(line: 1080, column: 6, scope: !462)
!2260 = !DILocation(line: 1081, column: 22, scope: !2261)
!2261 = distinct !DILexicalBlock(scope: !2255, file: !1, line: 1080, column: 37)
!2262 = !DILocation(line: 1081, column: 25, scope: !2261)
!2263 = !DILocation(line: 1081, column: 3, scope: !2261)
!2264 = !DILocation(line: 1083, column: 3, scope: !2261)
!2265 = !DILocation(line: 1085, column: 10, scope: !462)
!2266 = !DILocation(line: 1085, column: 2, scope: !462)
!2267 = !DILocation(line: 1087, column: 21, scope: !462)
!2268 = !DILocation(line: 1087, column: 24, scope: !462)
!2269 = !DILocation(line: 1087, column: 2, scope: !462)
!2270 = !DILocation(line: 1089, column: 2, scope: !462)
!2271 = !DILocation(line: 1090, column: 1, scope: !462)
!2272 = !DILocalVariable(name: "linkname", arg: 1, scope: !463, file: !1, line: 1597, type: !466)
!2273 = !DILocation(line: 1597, column: 43, scope: !463)
!2274 = !DILocalVariable(name: "pathname", arg: 2, scope: !463, file: !1, line: 1598, type: !466)
!2275 = !DILocation(line: 1598, column: 28, scope: !463)
!2276 = !DILocalVariable(name: "linkptr", scope: !463, file: !1, line: 1600, type: !95)
!2277 = !DILocation(line: 1600, column: 9, scope: !463)
!2278 = !DILocalVariable(name: "symlen", scope: !463, file: !1, line: 1601, type: !45)
!2279 = !DILocation(line: 1601, column: 10, scope: !463)
!2280 = !DILocation(line: 1603, column: 19, scope: !463)
!2281 = !DILocation(line: 1603, column: 29, scope: !463)
!2282 = !DILocation(line: 1603, column: 12, scope: !463)
!2283 = !DILocation(line: 1603, column: 10, scope: !463)
!2284 = !DILocation(line: 1604, column: 6, scope: !2285)
!2285 = distinct !DILexicalBlock(scope: !463, file: !1, line: 1604, column: 6)
!2286 = !DILocation(line: 1604, column: 14, scope: !2285)
!2287 = !DILocation(line: 1604, column: 6, scope: !463)
!2288 = !DILocation(line: 1605, column: 19, scope: !2289)
!2289 = distinct !DILexicalBlock(scope: !2285, file: !1, line: 1604, column: 23)
!2290 = !DILocation(line: 1605, column: 27, scope: !2289)
!2291 = !DILocation(line: 1605, column: 12, scope: !2289)
!2292 = !DILocation(line: 1605, column: 10, scope: !2289)
!2293 = !DILocation(line: 1606, column: 3, scope: !2289)
!2294 = !DILocation(line: 1608, column: 4, scope: !2289)
!2295 = !DILocation(line: 1608, column: 12, scope: !2289)
!2296 = !DILocation(line: 1609, column: 29, scope: !2289)
!2297 = !DILocation(line: 1609, column: 39, scope: !2289)
!2298 = !DILocation(line: 1609, column: 22, scope: !2289)
!2299 = !DILocation(line: 1609, column: 3, scope: !2289)
!2300 = !DILocation(line: 1609, column: 13, scope: !2289)
!2301 = !DILocation(line: 1609, column: 20, scope: !2289)
!2302 = !DILocation(line: 1611, column: 3, scope: !2289)
!2303 = !DILocation(line: 1613, column: 2, scope: !463)
!2304 = !DILocation(line: 1614, column: 1, scope: !463)
!2305 = !DILocalVariable(name: "lha", arg: 1, scope: !467, file: !1, line: 725, type: !292)
!2306 = !DILocation(line: 725, column: 40, scope: !467)
!2307 = !DILocalVariable(name: "entry", arg: 2, scope: !467, file: !1, line: 725, type: !30)
!2308 = !DILocation(line: 725, column: 67, scope: !467)
!2309 = !DILocalVariable(name: "wp", scope: !467, file: !1, line: 727, type: !2310)
!2310 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !2311, size: 64, align: 64)
!2311 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !338)
!2312 = !DILocation(line: 727, column: 17, scope: !467)
!2313 = !DILocalVariable(name: "i", scope: !467, file: !1, line: 728, type: !45)
!2314 = !DILocation(line: 728, column: 9, scope: !467)
!2315 = !DILocation(line: 730, column: 37, scope: !2316)
!2316 = distinct !DILexicalBlock(scope: !467, file: !1, line: 730, column: 6)
!2317 = !DILocation(line: 730, column: 12, scope: !2316)
!2318 = !DILocation(line: 730, column: 10, scope: !2316)
!2319 = !DILocation(line: 730, column: 45, scope: !2316)
!2320 = !DILocation(line: 730, column: 6, scope: !467)
!2321 = !DILocation(line: 731, column: 3, scope: !2322)
!2322 = distinct !DILexicalBlock(scope: !2316, file: !1, line: 730, column: 54)
!2323 = !DILocation(line: 731, column: 3, scope: !2324)
!2324 = !DILexicalBlockFile(scope: !2322, file: !1, discriminator: 1)
!2325 = !DILocation(line: 731, column: 3, scope: !2326)
!2326 = !DILexicalBlockFile(scope: !2322, file: !1, discriminator: 2)
!2327 = !DILocation(line: 731, column: 3, scope: !2328)
!2328 = !DILexicalBlockFile(scope: !2322, file: !1, discriminator: 3)
!2329 = !DILocation(line: 732, column: 10, scope: !2330)
!2330 = distinct !DILexicalBlock(scope: !2322, file: !1, line: 732, column: 3)
!2331 = !DILocation(line: 732, column: 8, scope: !2330)
!2332 = !DILocation(line: 732, column: 15, scope: !2333)
!2333 = !DILexicalBlockFile(scope: !2334, file: !1, discriminator: 1)
!2334 = distinct !DILexicalBlock(scope: !2330, file: !1, line: 732, column: 3)
!2335 = !DILocation(line: 732, column: 19, scope: !2333)
!2336 = !DILocation(line: 732, column: 17, scope: !2333)
!2337 = !DILocation(line: 732, column: 3, scope: !2333)
!2338 = !DILocation(line: 733, column: 18, scope: !2339)
!2339 = distinct !DILexicalBlock(scope: !2340, file: !1, line: 733, column: 8)
!2340 = distinct !DILexicalBlock(scope: !2334, file: !1, line: 732, column: 52)
!2341 = !DILocation(line: 733, column: 8, scope: !2339)
!2342 = !DILocation(line: 733, column: 13, scope: !2339)
!2343 = !DILocation(line: 733, column: 16, scope: !2339)
!2344 = !DILocation(line: 733, column: 21, scope: !2339)
!2345 = !DILocation(line: 733, column: 8, scope: !2340)
!2346 = !DILocation(line: 734, column: 15, scope: !2339)
!2347 = !DILocation(line: 734, column: 5, scope: !2339)
!2348 = !DILocation(line: 734, column: 10, scope: !2339)
!2349 = !DILocation(line: 734, column: 13, scope: !2339)
!2350 = !DILocation(line: 734, column: 18, scope: !2339)
!2351 = !DILocation(line: 735, column: 3, scope: !2340)
!2352 = !DILocation(line: 732, column: 48, scope: !2353)
!2353 = !DILexicalBlockFile(scope: !2334, file: !1, discriminator: 2)
!2354 = !DILocation(line: 732, column: 3, scope: !2353)
!2355 = !DILocation(line: 736, column: 33, scope: !2322)
!2356 = !DILocation(line: 736, column: 40, scope: !2322)
!2357 = !DILocation(line: 736, column: 45, scope: !2322)
!2358 = !DILocation(line: 736, column: 48, scope: !2322)
!2359 = !DILocation(line: 736, column: 3, scope: !2322)
!2360 = !DILocation(line: 737, column: 2, scope: !2322)
!2361 = !DILocation(line: 739, column: 36, scope: !2362)
!2362 = distinct !DILexicalBlock(scope: !467, file: !1, line: 739, column: 6)
!2363 = !DILocation(line: 739, column: 12, scope: !2362)
!2364 = !DILocation(line: 739, column: 10, scope: !2362)
!2365 = !DILocation(line: 739, column: 44, scope: !2362)
!2366 = !DILocation(line: 739, column: 6, scope: !467)
!2367 = !DILocation(line: 740, column: 3, scope: !2368)
!2368 = distinct !DILexicalBlock(scope: !2362, file: !1, line: 739, column: 53)
!2369 = !DILocation(line: 740, column: 3, scope: !2370)
!2370 = !DILexicalBlockFile(scope: !2368, file: !1, discriminator: 1)
!2371 = !DILocation(line: 740, column: 3, scope: !2372)
!2372 = !DILexicalBlockFile(scope: !2368, file: !1, discriminator: 2)
!2373 = !DILocation(line: 740, column: 3, scope: !2374)
!2374 = !DILexicalBlockFile(scope: !2368, file: !1, discriminator: 3)
!2375 = !DILocation(line: 741, column: 10, scope: !2376)
!2376 = distinct !DILexicalBlock(scope: !2368, file: !1, line: 741, column: 3)
!2377 = !DILocation(line: 741, column: 8, scope: !2376)
!2378 = !DILocation(line: 741, column: 15, scope: !2379)
!2379 = !DILexicalBlockFile(scope: !2380, file: !1, discriminator: 1)
!2380 = distinct !DILexicalBlock(scope: !2376, file: !1, line: 741, column: 3)
!2381 = !DILocation(line: 741, column: 19, scope: !2379)
!2382 = !DILocation(line: 741, column: 17, scope: !2379)
!2383 = !DILocation(line: 741, column: 3, scope: !2379)
!2384 = !DILocation(line: 742, column: 18, scope: !2385)
!2385 = distinct !DILexicalBlock(scope: !2386, file: !1, line: 742, column: 8)
!2386 = distinct !DILexicalBlock(scope: !2380, file: !1, line: 741, column: 52)
!2387 = !DILocation(line: 742, column: 8, scope: !2385)
!2388 = !DILocation(line: 742, column: 13, scope: !2385)
!2389 = !DILocation(line: 742, column: 16, scope: !2385)
!2390 = !DILocation(line: 742, column: 21, scope: !2385)
!2391 = !DILocation(line: 742, column: 8, scope: !2386)
!2392 = !DILocation(line: 743, column: 15, scope: !2385)
!2393 = !DILocation(line: 743, column: 5, scope: !2385)
!2394 = !DILocation(line: 743, column: 10, scope: !2385)
!2395 = !DILocation(line: 743, column: 13, scope: !2385)
!2396 = !DILocation(line: 743, column: 18, scope: !2385)
!2397 = !DILocation(line: 744, column: 3, scope: !2386)
!2398 = !DILocation(line: 741, column: 48, scope: !2399)
!2399 = !DILexicalBlockFile(scope: !2380, file: !1, discriminator: 2)
!2400 = !DILocation(line: 741, column: 3, scope: !2399)
!2401 = !DILocation(line: 745, column: 32, scope: !2368)
!2402 = !DILocation(line: 745, column: 39, scope: !2368)
!2403 = !DILocation(line: 745, column: 44, scope: !2368)
!2404 = !DILocation(line: 745, column: 47, scope: !2368)
!2405 = !DILocation(line: 745, column: 3, scope: !2368)
!2406 = !DILocation(line: 746, column: 2, scope: !2368)
!2407 = !DILocation(line: 747, column: 1, scope: !467)
!2408 = !DILocalVariable(name: "pp", arg: 1, scope: !434, file: !435, line: 115, type: !43)
!2409 = !DILocation(line: 115, column: 29, scope: !434)
!2410 = !DILocalVariable(name: "p", scope: !434, file: !435, line: 117, type: !356)
!2411 = !DILocation(line: 117, column: 23, scope: !434)
!2412 = !DILocation(line: 117, column: 50, scope: !434)
!2413 = !DILocalVariable(name: "p3", scope: !434, file: !435, line: 122, type: !13)
!2414 = !DILocation(line: 122, column: 15, scope: !434)
!2415 = !DILocation(line: 122, column: 20, scope: !434)
!2416 = !DILocalVariable(name: "p2", scope: !434, file: !435, line: 123, type: !13)
!2417 = !DILocation(line: 123, column: 15, scope: !434)
!2418 = !DILocation(line: 123, column: 20, scope: !434)
!2419 = !DILocalVariable(name: "p1", scope: !434, file: !435, line: 124, type: !13)
!2420 = !DILocation(line: 124, column: 15, scope: !434)
!2421 = !DILocation(line: 124, column: 20, scope: !434)
!2422 = !DILocalVariable(name: "p0", scope: !434, file: !435, line: 125, type: !13)
!2423 = !DILocation(line: 125, column: 15, scope: !434)
!2424 = !DILocation(line: 125, column: 20, scope: !434)
!2425 = !DILocation(line: 127, column: 11, scope: !434)
!2426 = !DILocation(line: 127, column: 14, scope: !434)
!2427 = !DILocation(line: 127, column: 24, scope: !434)
!2428 = !DILocation(line: 127, column: 27, scope: !434)
!2429 = !DILocation(line: 127, column: 21, scope: !434)
!2430 = !DILocation(line: 127, column: 37, scope: !434)
!2431 = !DILocation(line: 127, column: 40, scope: !434)
!2432 = !DILocation(line: 127, column: 34, scope: !434)
!2433 = !DILocation(line: 127, column: 48, scope: !434)
!2434 = !DILocation(line: 127, column: 46, scope: !434)
!2435 = !DILocation(line: 127, column: 2, scope: !434)
!2436 = !DILocalVariable(name: "p", arg: 1, scope: !438, file: !1, line: 1618, type: !356)
!2437 = !DILocation(line: 1618, column: 35, scope: !438)
!2438 = !DILocalVariable(name: "msTime", scope: !438, file: !1, line: 1620, type: !23)
!2439 = !DILocation(line: 1620, column: 6, scope: !438)
!2440 = !DILocalVariable(name: "msDate", scope: !438, file: !1, line: 1620, type: !23)
!2441 = !DILocation(line: 1620, column: 14, scope: !438)
!2442 = !DILocalVariable(name: "ts", scope: !438, file: !1, line: 1621, type: !2443)
!2443 = !DICompositeType(tag: DW_TAG_structure_type, name: "tm", file: !313, line: 133, size: 448, align: 64, elements: !2444)
!2444 = !{!2445, !2446, !2447, !2448, !2449, !2450, !2451, !2452, !2453, !2454, !2455}
!2445 = !DIDerivedType(tag: DW_TAG_member, name: "tm_sec", scope: !2443, file: !313, line: 135, baseType: !23, size: 32, align: 32)
!2446 = !DIDerivedType(tag: DW_TAG_member, name: "tm_min", scope: !2443, file: !313, line: 136, baseType: !23, size: 32, align: 32, offset: 32)
!2447 = !DIDerivedType(tag: DW_TAG_member, name: "tm_hour", scope: !2443, file: !313, line: 137, baseType: !23, size: 32, align: 32, offset: 64)
!2448 = !DIDerivedType(tag: DW_TAG_member, name: "tm_mday", scope: !2443, file: !313, line: 138, baseType: !23, size: 32, align: 32, offset: 96)
!2449 = !DIDerivedType(tag: DW_TAG_member, name: "tm_mon", scope: !2443, file: !313, line: 139, baseType: !23, size: 32, align: 32, offset: 128)
!2450 = !DIDerivedType(tag: DW_TAG_member, name: "tm_year", scope: !2443, file: !313, line: 140, baseType: !23, size: 32, align: 32, offset: 160)
!2451 = !DIDerivedType(tag: DW_TAG_member, name: "tm_wday", scope: !2443, file: !313, line: 141, baseType: !23, size: 32, align: 32, offset: 192)
!2452 = !DIDerivedType(tag: DW_TAG_member, name: "tm_yday", scope: !2443, file: !313, line: 142, baseType: !23, size: 32, align: 32, offset: 224)
!2453 = !DIDerivedType(tag: DW_TAG_member, name: "tm_isdst", scope: !2443, file: !313, line: 143, baseType: !23, size: 32, align: 32, offset: 256)
!2454 = !DIDerivedType(tag: DW_TAG_member, name: "tm_gmtoff", scope: !2443, file: !313, line: 146, baseType: !42, size: 64, align: 64, offset: 320)
!2455 = !DIDerivedType(tag: DW_TAG_member, name: "tm_zone", scope: !2443, file: !313, line: 147, baseType: !80, size: 64, align: 64, offset: 384)
!2456 = !DILocation(line: 1621, column: 12, scope: !438)
!2457 = !DILocation(line: 1623, column: 27, scope: !438)
!2458 = !DILocation(line: 1623, column: 11, scope: !438)
!2459 = !DILocation(line: 1623, column: 9, scope: !438)
!2460 = !DILocation(line: 1624, column: 27, scope: !438)
!2461 = !DILocation(line: 1624, column: 28, scope: !438)
!2462 = !DILocation(line: 1624, column: 11, scope: !438)
!2463 = !DILocation(line: 1624, column: 9, scope: !438)
!2464 = !DILocation(line: 1626, column: 2, scope: !438)
!2465 = !DILocation(line: 1627, column: 17, scope: !438)
!2466 = !DILocation(line: 1627, column: 24, scope: !438)
!2467 = !DILocation(line: 1627, column: 30, scope: !438)
!2468 = !DILocation(line: 1627, column: 38, scope: !438)
!2469 = !DILocation(line: 1627, column: 5, scope: !438)
!2470 = !DILocation(line: 1627, column: 13, scope: !438)
!2471 = !DILocation(line: 1628, column: 16, scope: !438)
!2472 = !DILocation(line: 1628, column: 23, scope: !438)
!2473 = !DILocation(line: 1628, column: 29, scope: !438)
!2474 = !DILocation(line: 1628, column: 37, scope: !438)
!2475 = !DILocation(line: 1628, column: 5, scope: !438)
!2476 = !DILocation(line: 1628, column: 12, scope: !438)
!2477 = !DILocation(line: 1629, column: 15, scope: !438)
!2478 = !DILocation(line: 1629, column: 22, scope: !438)
!2479 = !DILocation(line: 1629, column: 5, scope: !438)
!2480 = !DILocation(line: 1629, column: 13, scope: !438)
!2481 = !DILocation(line: 1630, column: 16, scope: !438)
!2482 = !DILocation(line: 1630, column: 23, scope: !438)
!2483 = !DILocation(line: 1630, column: 30, scope: !438)
!2484 = !DILocation(line: 1630, column: 5, scope: !438)
!2485 = !DILocation(line: 1630, column: 13, scope: !438)
!2486 = !DILocation(line: 1631, column: 15, scope: !438)
!2487 = !DILocation(line: 1631, column: 22, scope: !438)
!2488 = !DILocation(line: 1631, column: 28, scope: !438)
!2489 = !DILocation(line: 1631, column: 5, scope: !438)
!2490 = !DILocation(line: 1631, column: 12, scope: !438)
!2491 = !DILocation(line: 1632, column: 15, scope: !438)
!2492 = !DILocation(line: 1632, column: 22, scope: !438)
!2493 = !DILocation(line: 1632, column: 28, scope: !438)
!2494 = !DILocation(line: 1632, column: 5, scope: !438)
!2495 = !DILocation(line: 1632, column: 12, scope: !438)
!2496 = !DILocation(line: 1633, column: 5, scope: !438)
!2497 = !DILocation(line: 1633, column: 14, scope: !438)
!2498 = !DILocation(line: 1634, column: 10, scope: !438)
!2499 = !DILocation(line: 1634, column: 2, scope: !438)
!2500 = !DILocalVariable(name: "pp", arg: 1, scope: !441, file: !435, line: 101, type: !43)
!2501 = !DILocation(line: 101, column: 29, scope: !441)
!2502 = !DILocalVariable(name: "p", scope: !441, file: !435, line: 103, type: !356)
!2503 = !DILocation(line: 103, column: 23, scope: !441)
!2504 = !DILocation(line: 103, column: 50, scope: !441)
!2505 = !DILocalVariable(name: "p1", scope: !441, file: !435, line: 108, type: !13)
!2506 = !DILocation(line: 108, column: 15, scope: !441)
!2507 = !DILocation(line: 108, column: 20, scope: !441)
!2508 = !DILocalVariable(name: "p0", scope: !441, file: !435, line: 109, type: !13)
!2509 = !DILocation(line: 109, column: 15, scope: !441)
!2510 = !DILocation(line: 109, column: 20, scope: !441)
!2511 = !DILocation(line: 111, column: 11, scope: !441)
!2512 = !DILocation(line: 111, column: 14, scope: !441)
!2513 = !DILocation(line: 111, column: 22, scope: !441)
!2514 = !DILocation(line: 111, column: 20, scope: !441)
!2515 = !DILocation(line: 111, column: 9, scope: !441)
!2516 = !DILocation(line: 111, column: 2, scope: !441)
!2517 = !DILocalVariable(name: "sum", arg: 1, scope: !444, file: !1, line: 1656, type: !303)
!2518 = !DILocation(line: 1656, column: 27, scope: !444)
!2519 = !DILocalVariable(name: "pp", arg: 2, scope: !444, file: !1, line: 1656, type: !43)
!2520 = !DILocation(line: 1656, column: 44, scope: !444)
!2521 = !DILocalVariable(name: "offset", arg: 3, scope: !444, file: !1, line: 1656, type: !23)
!2522 = !DILocation(line: 1656, column: 52, scope: !444)
!2523 = !DILocalVariable(name: "size", arg: 4, scope: !444, file: !1, line: 1656, type: !45)
!2524 = !DILocation(line: 1656, column: 67, scope: !444)
!2525 = !DILocalVariable(name: "p", scope: !444, file: !1, line: 1658, type: !356)
!2526 = !DILocation(line: 1658, column: 23, scope: !444)
!2527 = !DILocation(line: 1658, column: 50, scope: !444)
!2528 = !DILocation(line: 1660, column: 7, scope: !444)
!2529 = !DILocation(line: 1660, column: 4, scope: !444)
!2530 = !DILocation(line: 1661, column: 2, scope: !444)
!2531 = !DILocation(line: 1661, column: 8, scope: !2532)
!2532 = !DILexicalBlockFile(scope: !2533, file: !1, discriminator: 1)
!2533 = distinct !DILexicalBlock(scope: !2534, file: !1, line: 1661, column: 2)
!2534 = distinct !DILexicalBlock(scope: !444, file: !1, line: 1661, column: 2)
!2535 = !DILocation(line: 1661, column: 13, scope: !2532)
!2536 = !DILocation(line: 1661, column: 2, scope: !2532)
!2537 = !DILocation(line: 1662, column: 12, scope: !2533)
!2538 = !DILocation(line: 1662, column: 10, scope: !2533)
!2539 = !DILocation(line: 1662, column: 7, scope: !2533)
!2540 = !DILocation(line: 1662, column: 3, scope: !2533)
!2541 = !DILocation(line: 1661, column: 18, scope: !2542)
!2542 = !DILexicalBlockFile(scope: !2533, file: !1, discriminator: 2)
!2543 = !DILocation(line: 1661, column: 2, scope: !2542)
!2544 = !DILocation(line: 1663, column: 10, scope: !444)
!2545 = !DILocation(line: 1663, column: 2, scope: !444)
!2546 = !DILocalVariable(name: "a", arg: 1, scope: !448, file: !1, line: 1107, type: !4)
!2547 = !DILocation(line: 1107, column: 52, scope: !448)
!2548 = !DILocalVariable(name: "lha", arg: 2, scope: !448, file: !1, line: 1107, type: !292)
!2549 = !DILocation(line: 1107, column: 67, scope: !448)
!2550 = !DILocalVariable(name: "crc", arg: 3, scope: !448, file: !1, line: 1108, type: !398)
!2551 = !DILocation(line: 1108, column: 15, scope: !448)
!2552 = !DILocalVariable(name: "sizefield_length", arg: 4, scope: !448, file: !1, line: 1108, type: !23)
!2553 = !DILocation(line: 1108, column: 24, scope: !448)
!2554 = !DILocalVariable(name: "limitsize", arg: 5, scope: !448, file: !1, line: 1108, type: !45)
!2555 = !DILocation(line: 1108, column: 49, scope: !448)
!2556 = !DILocalVariable(name: "total_size", arg: 6, scope: !448, file: !1, line: 1108, type: !65)
!2557 = !DILocation(line: 1108, column: 68, scope: !448)
!2558 = !DILocalVariable(name: "h", scope: !448, file: !1, line: 1110, type: !43)
!2559 = !DILocation(line: 1110, column: 14, scope: !448)
!2560 = !DILocalVariable(name: "extdheader", scope: !448, file: !1, line: 1111, type: !356)
!2561 = !DILocation(line: 1111, column: 23, scope: !448)
!2562 = !DILocalVariable(name: "extdsize", scope: !448, file: !1, line: 1112, type: !45)
!2563 = !DILocation(line: 1112, column: 9, scope: !448)
!2564 = !DILocalVariable(name: "datasize", scope: !448, file: !1, line: 1113, type: !45)
!2565 = !DILocation(line: 1113, column: 9, scope: !448)
!2566 = !DILocalVariable(name: "i", scope: !448, file: !1, line: 1114, type: !13)
!2567 = !DILocation(line: 1114, column: 15, scope: !448)
!2568 = !DILocalVariable(name: "extdtype", scope: !448, file: !1, line: 1115, type: !303)
!2569 = !DILocation(line: 1115, column: 16, scope: !448)
!2570 = !DILocation(line: 1135, column: 16, scope: !448)
!2571 = !DILocation(line: 1135, column: 3, scope: !448)
!2572 = !DILocation(line: 1135, column: 14, scope: !448)
!2573 = !DILocation(line: 1137, column: 2, scope: !448)
!2574 = !DILocation(line: 1140, column: 28, scope: !2575)
!2575 = distinct !DILexicalBlock(scope: !2576, file: !1, line: 1139, column: 7)
!2576 = distinct !DILexicalBlock(scope: !2577, file: !1, line: 1137, column: 11)
!2577 = distinct !DILexicalBlock(scope: !2578, file: !1, line: 1137, column: 2)
!2578 = distinct !DILexicalBlock(scope: !448, file: !1, line: 1137, column: 2)
!2579 = !DILocation(line: 1140, column: 31, scope: !2575)
!2580 = !DILocation(line: 1140, column: 7, scope: !2575)
!2581 = !DILocation(line: 1139, column: 10, scope: !2575)
!2582 = !DILocation(line: 1140, column: 56, scope: !2575)
!2583 = !DILocation(line: 1139, column: 7, scope: !2576)
!2584 = !DILocation(line: 1141, column: 28, scope: !2575)
!2585 = !DILocation(line: 1141, column: 12, scope: !2575)
!2586 = !DILocation(line: 1141, column: 4, scope: !2575)
!2587 = !DILocation(line: 1144, column: 7, scope: !2588)
!2588 = distinct !DILexicalBlock(scope: !2576, file: !1, line: 1144, column: 7)
!2589 = !DILocation(line: 1144, column: 24, scope: !2588)
!2590 = !DILocation(line: 1144, column: 7, scope: !2576)
!2591 = !DILocation(line: 1145, column: 31, scope: !2588)
!2592 = !DILocation(line: 1145, column: 15, scope: !2588)
!2593 = !DILocation(line: 1145, column: 13, scope: !2588)
!2594 = !DILocation(line: 1145, column: 4, scope: !2588)
!2595 = !DILocation(line: 1147, column: 31, scope: !2588)
!2596 = !DILocation(line: 1147, column: 15, scope: !2588)
!2597 = !DILocation(line: 1147, column: 13, scope: !2588)
!2598 = !DILocation(line: 1148, column: 7, scope: !2599)
!2599 = distinct !DILexicalBlock(scope: !2576, file: !1, line: 1148, column: 7)
!2600 = !DILocation(line: 1148, column: 16, scope: !2599)
!2601 = !DILocation(line: 1148, column: 7, scope: !2576)
!2602 = !DILocation(line: 1150, column: 8, scope: !2603)
!2603 = distinct !DILexicalBlock(scope: !2604, file: !1, line: 1150, column: 8)
!2604 = distinct !DILexicalBlock(scope: !2599, file: !1, line: 1148, column: 22)
!2605 = !DILocation(line: 1150, column: 12, scope: !2603)
!2606 = !DILocation(line: 1150, column: 8, scope: !2604)
!2607 = !DILocation(line: 1151, column: 23, scope: !2603)
!2608 = !DILocation(line: 1151, column: 22, scope: !2603)
!2609 = !DILocation(line: 1151, column: 28, scope: !2603)
!2610 = !DILocation(line: 1151, column: 31, scope: !2603)
!2611 = !DILocation(line: 1151, column: 12, scope: !2603)
!2612 = !DILocation(line: 1151, column: 6, scope: !2603)
!2613 = !DILocation(line: 1151, column: 10, scope: !2603)
!2614 = !DILocation(line: 1151, column: 5, scope: !2603)
!2615 = !DILocation(line: 1152, column: 27, scope: !2604)
!2616 = !DILocation(line: 1152, column: 30, scope: !2604)
!2617 = !DILocation(line: 1152, column: 4, scope: !2604)
!2618 = !DILocation(line: 1153, column: 4, scope: !2604)
!2619 = !DILocation(line: 1157, column: 19, scope: !2620)
!2620 = distinct !DILexicalBlock(scope: !2576, file: !1, line: 1157, column: 7)
!2621 = !DILocation(line: 1157, column: 18, scope: !2620)
!2622 = !DILocation(line: 1157, column: 32, scope: !2620)
!2623 = !DILocation(line: 1157, column: 30, scope: !2620)
!2624 = !DILocation(line: 1158, column: 19, scope: !2620)
!2625 = !DILocation(line: 1157, column: 42, scope: !2620)
!2626 = !DILocation(line: 1158, column: 29, scope: !2620)
!2627 = !DILocation(line: 1159, column: 7, scope: !2620)
!2628 = !DILocation(line: 1159, column: 27, scope: !2620)
!2629 = !DILocation(line: 1159, column: 19, scope: !2620)
!2630 = !DILocation(line: 1159, column: 16, scope: !2620)
!2631 = !DILocation(line: 1157, column: 7, scope: !2632)
!2632 = !DILexicalBlockFile(scope: !2576, file: !1, discriminator: 1)
!2633 = !DILocation(line: 1160, column: 4, scope: !2620)
!2634 = !DILocation(line: 1163, column: 33, scope: !2635)
!2635 = distinct !DILexicalBlock(scope: !2576, file: !1, line: 1163, column: 7)
!2636 = !DILocation(line: 1163, column: 36, scope: !2635)
!2637 = !DILocation(line: 1163, column: 12, scope: !2635)
!2638 = !DILocation(line: 1163, column: 10, scope: !2635)
!2639 = !DILocation(line: 1163, column: 53, scope: !2635)
!2640 = !DILocation(line: 1163, column: 7, scope: !2576)
!2641 = !DILocation(line: 1164, column: 28, scope: !2635)
!2642 = !DILocation(line: 1164, column: 12, scope: !2635)
!2643 = !DILocation(line: 1164, column: 4, scope: !2635)
!2644 = !DILocation(line: 1165, column: 18, scope: !2576)
!2645 = !DILocation(line: 1165, column: 4, scope: !2576)
!2646 = !DILocation(line: 1165, column: 15, scope: !2576)
!2647 = !DILocation(line: 1167, column: 39, scope: !2576)
!2648 = !DILocation(line: 1167, column: 14, scope: !2576)
!2649 = !DILocation(line: 1169, column: 25, scope: !2576)
!2650 = !DILocation(line: 1169, column: 14, scope: !2576)
!2651 = !DILocation(line: 1169, column: 12, scope: !2576)
!2652 = !DILocation(line: 1171, column: 14, scope: !2576)
!2653 = !DILocation(line: 1171, column: 30, scope: !2576)
!2654 = !DILocation(line: 1171, column: 28, scope: !2576)
!2655 = !DILocation(line: 1171, column: 25, scope: !2576)
!2656 = !DILocation(line: 1171, column: 23, scope: !2576)
!2657 = !DILocation(line: 1171, column: 12, scope: !2576)
!2658 = !DILocation(line: 1173, column: 17, scope: !2576)
!2659 = !DILocation(line: 1173, column: 34, scope: !2576)
!2660 = !DILocation(line: 1173, column: 14, scope: !2576)
!2661 = !DILocation(line: 1175, column: 7, scope: !2662)
!2662 = distinct !DILexicalBlock(scope: !2576, file: !1, line: 1175, column: 7)
!2663 = !DILocation(line: 1175, column: 11, scope: !2662)
!2664 = !DILocation(line: 1175, column: 19, scope: !2662)
!2665 = !DILocation(line: 1175, column: 22, scope: !2666)
!2666 = !DILexicalBlockFile(scope: !2662, file: !1, discriminator: 1)
!2667 = !DILocation(line: 1175, column: 31, scope: !2666)
!2668 = !DILocation(line: 1175, column: 7, scope: !2666)
!2669 = !DILocation(line: 1176, column: 22, scope: !2662)
!2670 = !DILocation(line: 1176, column: 21, scope: !2662)
!2671 = !DILocation(line: 1176, column: 27, scope: !2662)
!2672 = !DILocation(line: 1176, column: 30, scope: !2662)
!2673 = !DILocation(line: 1176, column: 11, scope: !2662)
!2674 = !DILocation(line: 1176, column: 5, scope: !2662)
!2675 = !DILocation(line: 1176, column: 9, scope: !2662)
!2676 = !DILocation(line: 1176, column: 4, scope: !2662)
!2677 = !DILocation(line: 1177, column: 11, scope: !2576)
!2678 = !DILocation(line: 1177, column: 3, scope: !2576)
!2679 = !DILocation(line: 1181, column: 8, scope: !2680)
!2680 = distinct !DILexicalBlock(scope: !2681, file: !1, line: 1181, column: 8)
!2681 = distinct !DILexicalBlock(scope: !2576, file: !1, line: 1177, column: 21)
!2682 = !DILocation(line: 1181, column: 17, scope: !2680)
!2683 = !DILocation(line: 1181, column: 8, scope: !2681)
!2684 = !DILocation(line: 1182, column: 39, scope: !2685)
!2685 = distinct !DILexicalBlock(scope: !2680, file: !1, line: 1181, column: 23)
!2686 = !DILocation(line: 1182, column: 23, scope: !2685)
!2687 = !DILocation(line: 1182, column: 5, scope: !2685)
!2688 = !DILocation(line: 1182, column: 10, scope: !2685)
!2689 = !DILocation(line: 1182, column: 21, scope: !2685)
!2690 = !DILocation(line: 1183, column: 9, scope: !2691)
!2691 = distinct !DILexicalBlock(scope: !2685, file: !1, line: 1183, column: 9)
!2692 = !DILocation(line: 1183, column: 13, scope: !2691)
!2693 = !DILocation(line: 1183, column: 9, scope: !2685)
!2694 = !DILocation(line: 1185, column: 24, scope: !2695)
!2695 = distinct !DILexicalBlock(scope: !2691, file: !1, line: 1183, column: 22)
!2696 = !DILocation(line: 1185, column: 23, scope: !2695)
!2697 = !DILocation(line: 1185, column: 29, scope: !2695)
!2698 = !DILocation(line: 1186, column: 10, scope: !2695)
!2699 = !DILocation(line: 1186, column: 21, scope: !2695)
!2700 = !DILocation(line: 1186, column: 19, scope: !2695)
!2701 = !DILocation(line: 1185, column: 13, scope: !2695)
!2702 = !DILocation(line: 1185, column: 7, scope: !2695)
!2703 = !DILocation(line: 1185, column: 11, scope: !2695)
!2704 = !DILocation(line: 1188, column: 24, scope: !2695)
!2705 = !DILocation(line: 1188, column: 23, scope: !2695)
!2706 = !DILocation(line: 1188, column: 13, scope: !2695)
!2707 = !DILocation(line: 1188, column: 7, scope: !2695)
!2708 = !DILocation(line: 1188, column: 11, scope: !2695)
!2709 = !DILocation(line: 1189, column: 24, scope: !2695)
!2710 = !DILocation(line: 1189, column: 23, scope: !2695)
!2711 = !DILocation(line: 1190, column: 10, scope: !2695)
!2712 = !DILocation(line: 1190, column: 20, scope: !2695)
!2713 = !DILocation(line: 1190, column: 24, scope: !2695)
!2714 = !DILocation(line: 1190, column: 33, scope: !2695)
!2715 = !DILocation(line: 1189, column: 13, scope: !2695)
!2716 = !DILocation(line: 1189, column: 7, scope: !2695)
!2717 = !DILocation(line: 1189, column: 11, scope: !2695)
!2718 = !DILocation(line: 1191, column: 5, scope: !2695)
!2719 = !DILocation(line: 1192, column: 4, scope: !2685)
!2720 = !DILocation(line: 1193, column: 4, scope: !2681)
!2721 = !DILocation(line: 1195, column: 8, scope: !2722)
!2722 = distinct !DILexicalBlock(scope: !2681, file: !1, line: 1195, column: 8)
!2723 = !DILocation(line: 1195, column: 17, scope: !2722)
!2724 = !DILocation(line: 1195, column: 8, scope: !2681)
!2725 = !DILocation(line: 1197, column: 5, scope: !2726)
!2726 = distinct !DILexicalBlock(scope: !2722, file: !1, line: 1195, column: 23)
!2727 = !DILocation(line: 1198, column: 5, scope: !2726)
!2728 = !DILocation(line: 1200, column: 8, scope: !2729)
!2729 = distinct !DILexicalBlock(scope: !2681, file: !1, line: 1200, column: 8)
!2730 = !DILocation(line: 1200, column: 22, scope: !2729)
!2731 = !DILocation(line: 1200, column: 8, scope: !2681)
!2732 = !DILocation(line: 1201, column: 5, scope: !2729)
!2733 = !DILocation(line: 1202, column: 4, scope: !2681)
!2734 = !DILocation(line: 1204, column: 4, scope: !2681)
!2735 = !DILocation(line: 1206, column: 8, scope: !2736)
!2736 = distinct !DILexicalBlock(scope: !2681, file: !1, line: 1206, column: 8)
!2737 = !DILocation(line: 1206, column: 17, scope: !2736)
!2738 = !DILocation(line: 1206, column: 22, scope: !2736)
!2739 = !DILocation(line: 1206, column: 25, scope: !2740)
!2740 = !DILexicalBlockFile(scope: !2736, file: !1, discriminator: 1)
!2741 = !DILocation(line: 1206, column: 39, scope: !2740)
!2742 = !DILocation(line: 1206, column: 8, scope: !2740)
!2743 = !DILocation(line: 1208, column: 5, scope: !2736)
!2744 = !DILocation(line: 1210, column: 4, scope: !2681)
!2745 = !DILocation(line: 1216, column: 11, scope: !2746)
!2746 = distinct !DILexicalBlock(scope: !2681, file: !1, line: 1216, column: 4)
!2747 = !DILocation(line: 1216, column: 9, scope: !2746)
!2748 = !DILocation(line: 1216, column: 16, scope: !2749)
!2749 = !DILexicalBlockFile(scope: !2750, file: !1, discriminator: 1)
!2750 = distinct !DILexicalBlock(scope: !2746, file: !1, line: 1216, column: 4)
!2751 = !DILocation(line: 1216, column: 20, scope: !2749)
!2752 = !DILocation(line: 1216, column: 25, scope: !2749)
!2753 = !DILocation(line: 1216, column: 33, scope: !2749)
!2754 = !DILocation(line: 1216, column: 18, scope: !2749)
!2755 = !DILocation(line: 1216, column: 4, scope: !2749)
!2756 = !DILocation(line: 1217, column: 39, scope: !2757)
!2757 = distinct !DILexicalBlock(scope: !2758, file: !1, line: 1217, column: 9)
!2758 = distinct !DILexicalBlock(scope: !2750, file: !1, line: 1216, column: 46)
!2759 = !DILocation(line: 1217, column: 24, scope: !2757)
!2760 = !DILocation(line: 1217, column: 29, scope: !2757)
!2761 = !DILocation(line: 1217, column: 37, scope: !2757)
!2762 = !DILocation(line: 1217, column: 9, scope: !2757)
!2763 = !DILocation(line: 1217, column: 42, scope: !2757)
!2764 = !DILocation(line: 1217, column: 9, scope: !2758)
!2765 = !DILocation(line: 1218, column: 21, scope: !2757)
!2766 = !DILocation(line: 1218, column: 6, scope: !2757)
!2767 = !DILocation(line: 1218, column: 11, scope: !2757)
!2768 = !DILocation(line: 1218, column: 19, scope: !2757)
!2769 = !DILocation(line: 1218, column: 24, scope: !2757)
!2770 = !DILocation(line: 1219, column: 4, scope: !2758)
!2771 = !DILocation(line: 1216, column: 42, scope: !2772)
!2772 = !DILexicalBlockFile(scope: !2750, file: !1, discriminator: 2)
!2773 = !DILocation(line: 1216, column: 4, scope: !2772)
!2774 = !DILocation(line: 1221, column: 23, scope: !2775)
!2775 = distinct !DILexicalBlock(scope: !2681, file: !1, line: 1221, column: 8)
!2776 = !DILocation(line: 1221, column: 28, scope: !2775)
!2777 = !DILocation(line: 1221, column: 36, scope: !2775)
!2778 = !DILocation(line: 1221, column: 42, scope: !2775)
!2779 = !DILocation(line: 1221, column: 8, scope: !2775)
!2780 = !DILocation(line: 1221, column: 13, scope: !2775)
!2781 = !DILocation(line: 1221, column: 21, scope: !2775)
!2782 = !DILocation(line: 1221, column: 46, scope: !2775)
!2783 = !DILocation(line: 1221, column: 8, scope: !2681)
!2784 = !DILocation(line: 1223, column: 5, scope: !2775)
!2785 = !DILocation(line: 1224, column: 4, scope: !2681)
!2786 = !DILocation(line: 1226, column: 8, scope: !2787)
!2787 = distinct !DILexicalBlock(scope: !2681, file: !1, line: 1226, column: 8)
!2788 = !DILocation(line: 1226, column: 17, scope: !2787)
!2789 = !DILocation(line: 1226, column: 8, scope: !2681)
!2790 = !DILocation(line: 1228, column: 26, scope: !2787)
!2791 = !DILocation(line: 1228, column: 10, scope: !2787)
!2792 = !DILocation(line: 1228, column: 38, scope: !2787)
!2793 = !DILocation(line: 1227, column: 21, scope: !2787)
!2794 = !DILocation(line: 1227, column: 5, scope: !2787)
!2795 = !DILocation(line: 1227, column: 10, scope: !2787)
!2796 = !DILocation(line: 1227, column: 19, scope: !2787)
!2797 = !DILocation(line: 1229, column: 4, scope: !2681)
!2798 = !DILocation(line: 1231, column: 8, scope: !2799)
!2799 = distinct !DILexicalBlock(scope: !2681, file: !1, line: 1231, column: 8)
!2800 = !DILocation(line: 1231, column: 17, scope: !2799)
!2801 = !DILocation(line: 1231, column: 8, scope: !2681)
!2802 = !DILocation(line: 1233, column: 25, scope: !2803)
!2803 = distinct !DILexicalBlock(scope: !2799, file: !1, line: 1231, column: 44)
!2804 = !DILocation(line: 1233, column: 9, scope: !2803)
!2805 = !DILocation(line: 1234, column: 10, scope: !2803)
!2806 = !DILocation(line: 1234, column: 15, scope: !2803)
!2807 = !DILocation(line: 1232, column: 22, scope: !2803)
!2808 = !DILocation(line: 1232, column: 5, scope: !2803)
!2809 = !DILocation(line: 1232, column: 10, scope: !2803)
!2810 = !DILocation(line: 1232, column: 20, scope: !2803)
!2811 = !DILocation(line: 1235, column: 16, scope: !2803)
!2812 = !DILocation(line: 1237, column: 25, scope: !2803)
!2813 = !DILocation(line: 1237, column: 9, scope: !2803)
!2814 = !DILocation(line: 1238, column: 10, scope: !2803)
!2815 = !DILocation(line: 1238, column: 15, scope: !2803)
!2816 = !DILocation(line: 1236, column: 18, scope: !2803)
!2817 = !DILocation(line: 1236, column: 5, scope: !2803)
!2818 = !DILocation(line: 1236, column: 10, scope: !2803)
!2819 = !DILocation(line: 1236, column: 16, scope: !2803)
!2820 = !DILocation(line: 1239, column: 16, scope: !2803)
!2821 = !DILocation(line: 1241, column: 25, scope: !2803)
!2822 = !DILocation(line: 1241, column: 9, scope: !2803)
!2823 = !DILocation(line: 1242, column: 10, scope: !2803)
!2824 = !DILocation(line: 1242, column: 15, scope: !2803)
!2825 = !DILocation(line: 1240, column: 18, scope: !2803)
!2826 = !DILocation(line: 1240, column: 5, scope: !2803)
!2827 = !DILocation(line: 1240, column: 10, scope: !2803)
!2828 = !DILocation(line: 1240, column: 16, scope: !2803)
!2829 = !DILocation(line: 1243, column: 5, scope: !2803)
!2830 = !DILocation(line: 1243, column: 10, scope: !2803)
!2831 = !DILocation(line: 1243, column: 18, scope: !2803)
!2832 = !DILocation(line: 1245, column: 4, scope: !2803)
!2833 = !DILocation(line: 1246, column: 4, scope: !2681)
!2834 = !DILocation(line: 1248, column: 8, scope: !2835)
!2835 = distinct !DILexicalBlock(scope: !2681, file: !1, line: 1248, column: 8)
!2836 = !DILocation(line: 1248, column: 17, scope: !2835)
!2837 = !DILocation(line: 1248, column: 8, scope: !2681)
!2838 = !DILocation(line: 1249, column: 37, scope: !2839)
!2839 = distinct !DILexicalBlock(scope: !2835, file: !1, line: 1248, column: 42)
!2840 = !DILocation(line: 1249, column: 21, scope: !2839)
!2841 = !DILocation(line: 1249, column: 5, scope: !2839)
!2842 = !DILocation(line: 1249, column: 10, scope: !2839)
!2843 = !DILocation(line: 1249, column: 19, scope: !2839)
!2844 = !DILocation(line: 1250, column: 16, scope: !2839)
!2845 = !DILocation(line: 1251, column: 37, scope: !2839)
!2846 = !DILocation(line: 1251, column: 21, scope: !2839)
!2847 = !DILocation(line: 1251, column: 5, scope: !2839)
!2848 = !DILocation(line: 1251, column: 10, scope: !2839)
!2849 = !DILocation(line: 1251, column: 19, scope: !2839)
!2850 = !DILocation(line: 1252, column: 4, scope: !2839)
!2851 = !DILocation(line: 1253, column: 4, scope: !2681)
!2852 = !DILocation(line: 1258, column: 8, scope: !2853)
!2853 = distinct !DILexicalBlock(scope: !2681, file: !1, line: 1258, column: 8)
!2854 = !DILocation(line: 1258, column: 17, scope: !2853)
!2855 = !DILocation(line: 1258, column: 8, scope: !2681)
!2856 = !DILocalVariable(name: "cp", scope: !2857, file: !1, line: 1259, type: !91)
!2857 = distinct !DILexicalBlock(scope: !2853, file: !1, line: 1258, column: 38)
!2858 = !DILocation(line: 1259, column: 27, scope: !2857)
!2859 = !DILocalVariable(name: "charset", scope: !2857, file: !1, line: 1260, type: !80)
!2860 = !DILocation(line: 1260, column: 17, scope: !2857)
!2861 = !DILocation(line: 1262, column: 5, scope: !2857)
!2862 = !DILocation(line: 1262, column: 5, scope: !2863)
!2863 = !DILexicalBlockFile(scope: !2864, file: !1, discriminator: 1)
!2864 = distinct !DILexicalBlock(scope: !2857, file: !1, line: 1262, column: 5)
!2865 = !DILocation(line: 1263, column: 29, scope: !2857)
!2866 = !DILocation(line: 1263, column: 13, scope: !2857)
!2867 = !DILocation(line: 1263, column: 5, scope: !2857)
!2868 = !DILocation(line: 1265, column: 14, scope: !2869)
!2869 = distinct !DILexicalBlock(scope: !2857, file: !1, line: 1263, column: 42)
!2870 = !DILocation(line: 1266, column: 6, scope: !2869)
!2871 = !DILocation(line: 1269, column: 31, scope: !2869)
!2872 = !DILocation(line: 1269, column: 15, scope: !2869)
!2873 = !DILocation(line: 1268, column: 6, scope: !2869)
!2874 = !DILocation(line: 1270, column: 19, scope: !2869)
!2875 = !DILocation(line: 1270, column: 14, scope: !2869)
!2876 = !DILocation(line: 1271, column: 6, scope: !2869)
!2877 = !DILocation(line: 1275, column: 8, scope: !2857)
!2878 = !DILocation(line: 1275, column: 11, scope: !2857)
!2879 = !DILocation(line: 1275, column: 21, scope: !2857)
!2880 = !DILocation(line: 1274, column: 9, scope: !2857)
!2881 = !DILocation(line: 1273, column: 5, scope: !2857)
!2882 = !DILocation(line: 1273, column: 10, scope: !2857)
!2883 = !DILocation(line: 1273, column: 16, scope: !2857)
!2884 = !DILocation(line: 1276, column: 5, scope: !2857)
!2885 = !DILocation(line: 1277, column: 9, scope: !2886)
!2886 = distinct !DILexicalBlock(scope: !2857, file: !1, line: 1277, column: 9)
!2887 = !DILocation(line: 1277, column: 14, scope: !2886)
!2888 = !DILocation(line: 1277, column: 20, scope: !2886)
!2889 = !DILocation(line: 1277, column: 9, scope: !2857)
!2890 = !DILocation(line: 1278, column: 6, scope: !2886)
!2891 = !DILocation(line: 1279, column: 4, scope: !2857)
!2892 = !DILocation(line: 1280, column: 4, scope: !2681)
!2893 = !DILocation(line: 1282, column: 8, scope: !2894)
!2894 = distinct !DILexicalBlock(scope: !2681, file: !1, line: 1282, column: 8)
!2895 = !DILocation(line: 1282, column: 17, scope: !2894)
!2896 = !DILocation(line: 1282, column: 8, scope: !2681)
!2897 = !DILocation(line: 1283, column: 33, scope: !2898)
!2898 = distinct !DILexicalBlock(scope: !2894, file: !1, line: 1282, column: 38)
!2899 = !DILocation(line: 1283, column: 17, scope: !2898)
!2900 = !DILocation(line: 1283, column: 5, scope: !2898)
!2901 = !DILocation(line: 1283, column: 10, scope: !2898)
!2902 = !DILocation(line: 1283, column: 15, scope: !2898)
!2903 = !DILocation(line: 1284, column: 5, scope: !2898)
!2904 = !DILocation(line: 1284, column: 10, scope: !2898)
!2905 = !DILocation(line: 1284, column: 18, scope: !2898)
!2906 = !DILocation(line: 1285, column: 4, scope: !2898)
!2907 = !DILocation(line: 1286, column: 4, scope: !2681)
!2908 = !DILocation(line: 1288, column: 8, scope: !2909)
!2909 = distinct !DILexicalBlock(scope: !2681, file: !1, line: 1288, column: 8)
!2910 = !DILocation(line: 1288, column: 17, scope: !2909)
!2911 = !DILocation(line: 1288, column: 8, scope: !2681)
!2912 = !DILocation(line: 1289, column: 32, scope: !2913)
!2913 = distinct !DILexicalBlock(scope: !2909, file: !1, line: 1288, column: 44)
!2914 = !DILocation(line: 1289, column: 16, scope: !2913)
!2915 = !DILocation(line: 1289, column: 5, scope: !2913)
!2916 = !DILocation(line: 1289, column: 10, scope: !2913)
!2917 = !DILocation(line: 1289, column: 14, scope: !2913)
!2918 = !DILocation(line: 1290, column: 32, scope: !2913)
!2919 = !DILocation(line: 1290, column: 42, scope: !2913)
!2920 = !DILocation(line: 1290, column: 16, scope: !2913)
!2921 = !DILocation(line: 1290, column: 5, scope: !2913)
!2922 = !DILocation(line: 1290, column: 10, scope: !2913)
!2923 = !DILocation(line: 1290, column: 14, scope: !2913)
!2924 = !DILocation(line: 1291, column: 4, scope: !2913)
!2925 = !DILocation(line: 1292, column: 4, scope: !2681)
!2926 = !DILocation(line: 1294, column: 8, scope: !2927)
!2927 = distinct !DILexicalBlock(scope: !2681, file: !1, line: 1294, column: 8)
!2928 = !DILocation(line: 1294, column: 17, scope: !2927)
!2929 = !DILocation(line: 1294, column: 8, scope: !2681)
!2930 = !DILocation(line: 1295, column: 5, scope: !2927)
!2931 = !DILocation(line: 1297, column: 4, scope: !2681)
!2932 = !DILocation(line: 1299, column: 8, scope: !2933)
!2933 = distinct !DILexicalBlock(scope: !2681, file: !1, line: 1299, column: 8)
!2934 = !DILocation(line: 1299, column: 17, scope: !2933)
!2935 = !DILocation(line: 1299, column: 8, scope: !2681)
!2936 = !DILocation(line: 1300, column: 5, scope: !2933)
!2937 = !DILocation(line: 1302, column: 4, scope: !2681)
!2938 = !DILocation(line: 1304, column: 8, scope: !2939)
!2939 = distinct !DILexicalBlock(scope: !2681, file: !1, line: 1304, column: 8)
!2940 = !DILocation(line: 1304, column: 17, scope: !2939)
!2941 = !DILocation(line: 1304, column: 8, scope: !2681)
!2942 = !DILocation(line: 1305, column: 34, scope: !2939)
!2943 = !DILocation(line: 1305, column: 18, scope: !2939)
!2944 = !DILocation(line: 1305, column: 5, scope: !2939)
!2945 = !DILocation(line: 1305, column: 10, scope: !2939)
!2946 = !DILocation(line: 1305, column: 16, scope: !2939)
!2947 = !DILocation(line: 1306, column: 4, scope: !2681)
!2948 = !DILocation(line: 1309, column: 8, scope: !2949)
!2949 = distinct !DILexicalBlock(scope: !2681, file: !1, line: 1309, column: 8)
!2950 = !DILocation(line: 1309, column: 17, scope: !2949)
!2951 = !DILocation(line: 1309, column: 8, scope: !2681)
!2952 = !DILocation(line: 1311, column: 26, scope: !2953)
!2953 = distinct !DILexicalBlock(scope: !2949, file: !1, line: 1309, column: 24)
!2954 = !DILocation(line: 1311, column: 10, scope: !2953)
!2955 = !DILocation(line: 1311, column: 38, scope: !2953)
!2956 = !DILocation(line: 1310, column: 21, scope: !2953)
!2957 = !DILocation(line: 1310, column: 5, scope: !2953)
!2958 = !DILocation(line: 1310, column: 10, scope: !2953)
!2959 = !DILocation(line: 1310, column: 19, scope: !2953)
!2960 = !DILocation(line: 1312, column: 33, scope: !2953)
!2961 = !DILocation(line: 1312, column: 43, scope: !2953)
!2962 = !DILocation(line: 1312, column: 17, scope: !2953)
!2963 = !DILocation(line: 1312, column: 5, scope: !2953)
!2964 = !DILocation(line: 1312, column: 10, scope: !2953)
!2965 = !DILocation(line: 1312, column: 15, scope: !2953)
!2966 = !DILocation(line: 1313, column: 32, scope: !2953)
!2967 = !DILocation(line: 1313, column: 42, scope: !2953)
!2968 = !DILocation(line: 1313, column: 16, scope: !2953)
!2969 = !DILocation(line: 1313, column: 5, scope: !2953)
!2970 = !DILocation(line: 1313, column: 10, scope: !2953)
!2971 = !DILocation(line: 1313, column: 14, scope: !2953)
!2972 = !DILocation(line: 1314, column: 32, scope: !2953)
!2973 = !DILocation(line: 1314, column: 42, scope: !2953)
!2974 = !DILocation(line: 1314, column: 16, scope: !2953)
!2975 = !DILocation(line: 1314, column: 5, scope: !2953)
!2976 = !DILocation(line: 1314, column: 10, scope: !2953)
!2977 = !DILocation(line: 1314, column: 14, scope: !2953)
!2978 = !DILocation(line: 1315, column: 38, scope: !2953)
!2979 = !DILocation(line: 1315, column: 48, scope: !2953)
!2980 = !DILocation(line: 1315, column: 22, scope: !2953)
!2981 = !DILocation(line: 1315, column: 5, scope: !2953)
!2982 = !DILocation(line: 1315, column: 10, scope: !2953)
!2983 = !DILocation(line: 1315, column: 20, scope: !2953)
!2984 = !DILocation(line: 1316, column: 34, scope: !2953)
!2985 = !DILocation(line: 1316, column: 44, scope: !2953)
!2986 = !DILocation(line: 1316, column: 18, scope: !2953)
!2987 = !DILocation(line: 1316, column: 5, scope: !2953)
!2988 = !DILocation(line: 1316, column: 10, scope: !2953)
!2989 = !DILocation(line: 1316, column: 16, scope: !2953)
!2990 = !DILocation(line: 1317, column: 5, scope: !2953)
!2991 = !DILocation(line: 1317, column: 10, scope: !2953)
!2992 = !DILocation(line: 1317, column: 18, scope: !2953)
!2993 = !DILocation(line: 1319, column: 4, scope: !2953)
!2994 = !DILocation(line: 1320, column: 4, scope: !2681)
!2995 = !DILocation(line: 1322, column: 8, scope: !2996)
!2996 = distinct !DILexicalBlock(scope: !2681, file: !1, line: 1322, column: 8)
!2997 = !DILocation(line: 1322, column: 17, scope: !2996)
!2998 = !DILocation(line: 1322, column: 8, scope: !2681)
!2999 = !DILocation(line: 1323, column: 41, scope: !3000)
!3000 = distinct !DILexicalBlock(scope: !2996, file: !1, line: 1322, column: 24)
!3001 = !DILocation(line: 1323, column: 25, scope: !3000)
!3002 = !DILocation(line: 1323, column: 5, scope: !3000)
!3003 = !DILocation(line: 1323, column: 10, scope: !3000)
!3004 = !DILocation(line: 1323, column: 15, scope: !3000)
!3005 = !DILocation(line: 1324, column: 32, scope: !3000)
!3006 = !DILocation(line: 1324, column: 42, scope: !3000)
!3007 = !DILocation(line: 1324, column: 16, scope: !3000)
!3008 = !DILocation(line: 1324, column: 5, scope: !3000)
!3009 = !DILocation(line: 1324, column: 10, scope: !3000)
!3010 = !DILocation(line: 1324, column: 14, scope: !3000)
!3011 = !DILocation(line: 1325, column: 32, scope: !3000)
!3012 = !DILocation(line: 1325, column: 42, scope: !3000)
!3013 = !DILocation(line: 1325, column: 16, scope: !3000)
!3014 = !DILocation(line: 1325, column: 5, scope: !3000)
!3015 = !DILocation(line: 1325, column: 10, scope: !3000)
!3016 = !DILocation(line: 1325, column: 14, scope: !3000)
!3017 = !DILocation(line: 1326, column: 38, scope: !3000)
!3018 = !DILocation(line: 1326, column: 48, scope: !3000)
!3019 = !DILocation(line: 1326, column: 22, scope: !3000)
!3020 = !DILocation(line: 1326, column: 5, scope: !3000)
!3021 = !DILocation(line: 1326, column: 10, scope: !3000)
!3022 = !DILocation(line: 1326, column: 20, scope: !3000)
!3023 = !DILocation(line: 1327, column: 34, scope: !3000)
!3024 = !DILocation(line: 1327, column: 44, scope: !3000)
!3025 = !DILocation(line: 1327, column: 18, scope: !3000)
!3026 = !DILocation(line: 1327, column: 5, scope: !3000)
!3027 = !DILocation(line: 1327, column: 10, scope: !3000)
!3028 = !DILocation(line: 1327, column: 16, scope: !3000)
!3029 = !DILocation(line: 1328, column: 5, scope: !3000)
!3030 = !DILocation(line: 1328, column: 10, scope: !3000)
!3031 = !DILocation(line: 1328, column: 18, scope: !3000)
!3032 = !DILocation(line: 1330, column: 4, scope: !3000)
!3033 = !DILocation(line: 1331, column: 4, scope: !2681)
!3034 = !DILocation(line: 1331, column: 4, scope: !3035)
!3035 = !DILexicalBlockFile(scope: !2681, file: !1, discriminator: 1)
!3036 = !DILocation(line: 1336, column: 4, scope: !2681)
!3037 = !DILocation(line: 1339, column: 26, scope: !2576)
!3038 = !DILocation(line: 1339, column: 29, scope: !2576)
!3039 = !DILocation(line: 1339, column: 3, scope: !2576)
!3040 = !DILocation(line: 1137, column: 2, scope: !3041)
!3041 = !DILexicalBlockFile(scope: !2577, file: !1, discriminator: 1)
!3042 = !DILocation(line: 1342, column: 21, scope: !448)
!3043 = !DILocation(line: 1342, column: 24, scope: !448)
!3044 = !DILocation(line: 1342, column: 2, scope: !448)
!3045 = !DILocation(line: 1344, column: 2, scope: !448)
!3046 = !DILocation(line: 1345, column: 1, scope: !448)
!3047 = !DILocalVariable(name: "crc", arg: 1, scope: !451, file: !1, line: 1692, type: !299)
!3048 = !DILocation(line: 1692, column: 20, scope: !451)
!3049 = !DILocalVariable(name: "pp", arg: 2, scope: !451, file: !1, line: 1692, type: !43)
!3050 = !DILocation(line: 1692, column: 37, scope: !451)
!3051 = !DILocalVariable(name: "len", arg: 3, scope: !451, file: !1, line: 1692, type: !45)
!3052 = !DILocation(line: 1692, column: 48, scope: !451)
!3053 = !DILocalVariable(name: "p", scope: !451, file: !1, line: 1694, type: !356)
!3054 = !DILocation(line: 1694, column: 23, scope: !451)
!3055 = !DILocation(line: 1694, column: 50, scope: !451)
!3056 = !DILocalVariable(name: "buff", scope: !451, file: !1, line: 1695, type: !415)
!3057 = !DILocation(line: 1695, column: 18, scope: !451)
!3058 = !DILocation(line: 1701, column: 6, scope: !3059)
!3059 = distinct !DILexicalBlock(scope: !451, file: !1, line: 1701, column: 6)
!3060 = !DILocation(line: 1701, column: 10, scope: !3059)
!3061 = !DILocation(line: 1701, column: 6, scope: !451)
!3062 = !DILocation(line: 1702, column: 10, scope: !3059)
!3063 = !DILocation(line: 1702, column: 3, scope: !3059)
!3064 = !DILocation(line: 1705, column: 18, scope: !3065)
!3065 = distinct !DILexicalBlock(scope: !451, file: !1, line: 1705, column: 6)
!3066 = !DILocation(line: 1705, column: 7, scope: !3065)
!3067 = !DILocation(line: 1705, column: 21, scope: !3065)
!3068 = !DILocation(line: 1705, column: 6, scope: !451)
!3069 = !DILocation(line: 1706, column: 10, scope: !3070)
!3070 = distinct !DILexicalBlock(scope: !3065, file: !1, line: 1705, column: 39)
!3071 = !DILocation(line: 1706, column: 14, scope: !3070)
!3072 = !DILocation(line: 1706, column: 35, scope: !3070)
!3073 = !DILocation(line: 1706, column: 43, scope: !3070)
!3074 = !DILocation(line: 1706, column: 41, scope: !3070)
!3075 = !DILocation(line: 1706, column: 39, scope: !3070)
!3076 = !DILocation(line: 1706, column: 47, scope: !3070)
!3077 = !DILocation(line: 1706, column: 22, scope: !3070)
!3078 = !DILocation(line: 1706, column: 20, scope: !3070)
!3079 = !DILocation(line: 1706, column: 9, scope: !3070)
!3080 = !DILocation(line: 1706, column: 7, scope: !3070)
!3081 = !DILocation(line: 1707, column: 6, scope: !3070)
!3082 = !DILocation(line: 1708, column: 2, scope: !3070)
!3083 = !DILocation(line: 1709, column: 27, scope: !451)
!3084 = !DILocation(line: 1709, column: 9, scope: !451)
!3085 = !DILocation(line: 1709, column: 7, scope: !451)
!3086 = !DILocation(line: 1715, column: 2, scope: !451)
!3087 = !DILocation(line: 1715, column: 8, scope: !3088)
!3088 = !DILexicalBlockFile(scope: !3089, file: !1, discriminator: 1)
!3089 = distinct !DILexicalBlock(scope: !3090, file: !1, line: 1715, column: 2)
!3090 = distinct !DILexicalBlock(scope: !451, file: !1, line: 1715, column: 2)
!3091 = !DILocation(line: 1715, column: 12, scope: !3088)
!3092 = !DILocation(line: 1715, column: 2, scope: !3088)
!3093 = !DILocation(line: 1740, column: 3, scope: !3094)
!3094 = distinct !DILexicalBlock(scope: !3089, file: !1, line: 1715, column: 28)
!3095 = !DILocation(line: 1740, column: 3, scope: !3096)
!3096 = !DILexicalBlockFile(scope: !3097, file: !1, discriminator: 1)
!3097 = distinct !DILexicalBlock(scope: !3098, file: !1, line: 1740, column: 3)
!3098 = distinct !DILexicalBlock(scope: !3094, file: !1, line: 1740, column: 3)
!3099 = !DILocation(line: 1740, column: 3, scope: !3100)
!3100 = !DILexicalBlockFile(scope: !3101, file: !1, discriminator: 2)
!3101 = distinct !DILexicalBlock(scope: !3097, file: !1, line: 1740, column: 3)
!3102 = !DILocation(line: 1740, column: 3, scope: !3103)
!3103 = !DILexicalBlockFile(scope: !3097, file: !1, discriminator: 3)
!3104 = !DILocation(line: 1740, column: 3, scope: !3105)
!3105 = !DILexicalBlockFile(scope: !3098, file: !1, discriminator: 4)
!3106 = !DILocation(line: 1741, column: 3, scope: !3094)
!3107 = !DILocation(line: 1741, column: 3, scope: !3108)
!3108 = !DILexicalBlockFile(scope: !3109, file: !1, discriminator: 1)
!3109 = distinct !DILexicalBlock(scope: !3110, file: !1, line: 1741, column: 3)
!3110 = distinct !DILexicalBlock(scope: !3094, file: !1, line: 1741, column: 3)
!3111 = !DILocation(line: 1741, column: 3, scope: !3112)
!3112 = !DILexicalBlockFile(scope: !3113, file: !1, discriminator: 2)
!3113 = distinct !DILexicalBlock(scope: !3109, file: !1, line: 1741, column: 3)
!3114 = !DILocation(line: 1741, column: 3, scope: !3115)
!3115 = !DILexicalBlockFile(scope: !3109, file: !1, discriminator: 3)
!3116 = !DILocation(line: 1741, column: 3, scope: !3117)
!3117 = !DILexicalBlockFile(scope: !3110, file: !1, discriminator: 4)
!3118 = !DILocation(line: 1742, column: 3, scope: !3094)
!3119 = !DILocation(line: 1742, column: 3, scope: !3120)
!3120 = !DILexicalBlockFile(scope: !3121, file: !1, discriminator: 1)
!3121 = distinct !DILexicalBlock(scope: !3122, file: !1, line: 1742, column: 3)
!3122 = distinct !DILexicalBlock(scope: !3094, file: !1, line: 1742, column: 3)
!3123 = !DILocation(line: 1742, column: 3, scope: !3124)
!3124 = !DILexicalBlockFile(scope: !3125, file: !1, discriminator: 2)
!3125 = distinct !DILexicalBlock(scope: !3121, file: !1, line: 1742, column: 3)
!3126 = !DILocation(line: 1742, column: 3, scope: !3127)
!3127 = !DILexicalBlockFile(scope: !3121, file: !1, discriminator: 3)
!3128 = !DILocation(line: 1742, column: 3, scope: !3129)
!3129 = !DILexicalBlockFile(scope: !3122, file: !1, discriminator: 4)
!3130 = !DILocation(line: 1743, column: 3, scope: !3094)
!3131 = !DILocation(line: 1743, column: 3, scope: !3132)
!3132 = !DILexicalBlockFile(scope: !3133, file: !1, discriminator: 1)
!3133 = distinct !DILexicalBlock(scope: !3134, file: !1, line: 1743, column: 3)
!3134 = distinct !DILexicalBlock(scope: !3094, file: !1, line: 1743, column: 3)
!3135 = !DILocation(line: 1743, column: 3, scope: !3136)
!3136 = !DILexicalBlockFile(scope: !3137, file: !1, discriminator: 2)
!3137 = distinct !DILexicalBlock(scope: !3133, file: !1, line: 1743, column: 3)
!3138 = !DILocation(line: 1743, column: 3, scope: !3139)
!3139 = !DILexicalBlockFile(scope: !3133, file: !1, discriminator: 3)
!3140 = !DILocation(line: 1743, column: 3, scope: !3141)
!3141 = !DILexicalBlockFile(scope: !3134, file: !1, discriminator: 4)
!3142 = !DILocation(line: 1746, column: 2, scope: !3094)
!3143 = !DILocation(line: 1715, column: 22, scope: !3144)
!3144 = !DILexicalBlockFile(scope: !3089, file: !1, discriminator: 2)
!3145 = !DILocation(line: 1715, column: 2, scope: !3144)
!3146 = !DILocation(line: 1748, column: 29, scope: !451)
!3147 = !DILocation(line: 1748, column: 6, scope: !451)
!3148 = !DILocation(line: 1748, column: 4, scope: !451)
!3149 = !DILocation(line: 1749, column: 2, scope: !451)
!3150 = !DILocation(line: 1749, column: 8, scope: !3151)
!3151 = !DILexicalBlockFile(scope: !3152, file: !1, discriminator: 1)
!3152 = distinct !DILexicalBlock(scope: !3153, file: !1, line: 1749, column: 2)
!3153 = distinct !DILexicalBlock(scope: !451, file: !1, line: 1749, column: 2)
!3154 = !DILocation(line: 1749, column: 2, scope: !3151)
!3155 = !DILocation(line: 1750, column: 10, scope: !3156)
!3156 = distinct !DILexicalBlock(scope: !3152, file: !1, line: 1749, column: 20)
!3157 = !DILocation(line: 1750, column: 14, scope: !3156)
!3158 = !DILocation(line: 1750, column: 35, scope: !3156)
!3159 = !DILocation(line: 1750, column: 43, scope: !3156)
!3160 = !DILocation(line: 1750, column: 41, scope: !3156)
!3161 = !DILocation(line: 1750, column: 39, scope: !3156)
!3162 = !DILocation(line: 1750, column: 47, scope: !3156)
!3163 = !DILocation(line: 1750, column: 22, scope: !3156)
!3164 = !DILocation(line: 1750, column: 20, scope: !3156)
!3165 = !DILocation(line: 1750, column: 9, scope: !3156)
!3166 = !DILocation(line: 1750, column: 7, scope: !3156)
!3167 = !DILocation(line: 1751, column: 2, scope: !3156)
!3168 = !DILocation(line: 1749, column: 16, scope: !3169)
!3169 = !DILexicalBlockFile(scope: !3152, file: !1, discriminator: 2)
!3170 = !DILocation(line: 1749, column: 2, scope: !3169)
!3171 = !DILocation(line: 1752, column: 9, scope: !451)
!3172 = !DILocation(line: 1752, column: 2, scope: !451)
!3173 = !DILocation(line: 1753, column: 1, scope: !451)
!3174 = !DILocalVariable(name: "wintime", arg: 1, scope: !454, file: !1, line: 1639, type: !379)
!3175 = !DILocation(line: 1639, column: 23, scope: !454)
!3176 = !DILocalVariable(name: "ns", arg: 2, scope: !454, file: !1, line: 1639, type: !457)
!3177 = !DILocation(line: 1639, column: 38, scope: !454)
!3178 = !DILocation(line: 1643, column: 6, scope: !3179)
!3179 = distinct !DILexicalBlock(scope: !454, file: !1, line: 1643, column: 6)
!3180 = !DILocation(line: 1643, column: 14, scope: !3179)
!3181 = !DILocation(line: 1643, column: 6, scope: !454)
!3182 = !DILocation(line: 1644, column: 11, scope: !3183)
!3183 = distinct !DILexicalBlock(scope: !3179, file: !1, line: 1643, column: 28)
!3184 = !DILocation(line: 1645, column: 7, scope: !3185)
!3185 = distinct !DILexicalBlock(scope: !3183, file: !1, line: 1645, column: 7)
!3186 = !DILocation(line: 1645, column: 10, scope: !3185)
!3187 = !DILocation(line: 1645, column: 7, scope: !3183)
!3188 = !DILocation(line: 1646, column: 17, scope: !3185)
!3189 = !DILocation(line: 1646, column: 25, scope: !3185)
!3190 = !DILocation(line: 1646, column: 37, scope: !3185)
!3191 = !DILocation(line: 1646, column: 5, scope: !3185)
!3192 = !DILocation(line: 1646, column: 8, scope: !3185)
!3193 = !DILocation(line: 1646, column: 4, scope: !3185)
!3194 = !DILocation(line: 1647, column: 11, scope: !3183)
!3195 = !DILocation(line: 1647, column: 19, scope: !3183)
!3196 = !DILocation(line: 1647, column: 3, scope: !3183)
!3197 = !DILocation(line: 1649, column: 7, scope: !3198)
!3198 = distinct !DILexicalBlock(scope: !3199, file: !1, line: 1649, column: 7)
!3199 = distinct !DILexicalBlock(scope: !3179, file: !1, line: 1648, column: 9)
!3200 = !DILocation(line: 1649, column: 10, scope: !3198)
!3201 = !DILocation(line: 1649, column: 7, scope: !3199)
!3202 = !DILocation(line: 1650, column: 5, scope: !3198)
!3203 = !DILocation(line: 1650, column: 8, scope: !3198)
!3204 = !DILocation(line: 1650, column: 4, scope: !3198)
!3205 = !DILocation(line: 1651, column: 3, scope: !3199)
!3206 = !DILocation(line: 1653, column: 1, scope: !454)
!3207 = !DILocalVariable(name: "pp", arg: 1, scope: !458, file: !435, line: 131, type: !43)
!3208 = !DILocation(line: 131, column: 29, scope: !458)
!3209 = !DILocalVariable(name: "p", scope: !458, file: !435, line: 133, type: !356)
!3210 = !DILocation(line: 133, column: 23, scope: !458)
!3211 = !DILocation(line: 133, column: 50, scope: !458)
!3212 = !DILocation(line: 135, column: 37, scope: !458)
!3213 = !DILocation(line: 135, column: 39, scope: !458)
!3214 = !DILocation(line: 135, column: 21, scope: !458)
!3215 = !DILocation(line: 135, column: 11, scope: !458)
!3216 = !DILocation(line: 135, column: 44, scope: !458)
!3217 = !DILocation(line: 135, column: 69, scope: !458)
!3218 = !DILocation(line: 135, column: 53, scope: !3219)
!3219 = !DILexicalBlockFile(scope: !458, file: !435, discriminator: 1)
!3220 = !DILocation(line: 135, column: 53, scope: !458)
!3221 = !DILocation(line: 135, column: 51, scope: !458)
!3222 = !DILocation(line: 135, column: 2, scope: !458)
!3223 = !DILocalVariable(name: "a", arg: 1, scope: !471, file: !1, line: 1348, type: !4)
!3224 = !DILocation(line: 1348, column: 39, scope: !471)
!3225 = !DILocalVariable(name: "lha", scope: !471, file: !1, line: 1350, type: !292)
!3226 = !DILocation(line: 1350, column: 14, scope: !471)
!3227 = !DILocation(line: 1350, column: 35, scope: !471)
!3228 = !DILocation(line: 1350, column: 38, scope: !471)
!3229 = !DILocation(line: 1350, column: 46, scope: !471)
!3230 = !DILocation(line: 1350, column: 20, scope: !471)
!3231 = !DILocalVariable(name: "r", scope: !471, file: !1, line: 1351, type: !23)
!3232 = !DILocation(line: 1351, column: 6, scope: !471)
!3233 = !DILocation(line: 1353, column: 7, scope: !3234)
!3234 = distinct !DILexicalBlock(scope: !471, file: !1, line: 1353, column: 6)
!3235 = !DILocation(line: 1353, column: 12, scope: !3234)
!3236 = !DILocation(line: 1353, column: 6, scope: !471)
!3237 = !DILocation(line: 1354, column: 8, scope: !3238)
!3238 = distinct !DILexicalBlock(scope: !3239, file: !1, line: 1354, column: 7)
!3239 = distinct !DILexicalBlock(scope: !3234, file: !1, line: 1353, column: 34)
!3240 = !DILocation(line: 1354, column: 13, scope: !3238)
!3241 = !DILocation(line: 1354, column: 21, scope: !3238)
!3242 = !DILocation(line: 1354, column: 35, scope: !3238)
!3243 = !DILocation(line: 1355, column: 7, scope: !3238)
!3244 = !DILocation(line: 1355, column: 12, scope: !3238)
!3245 = !DILocation(line: 1355, column: 19, scope: !3238)
!3246 = !DILocation(line: 1355, column: 24, scope: !3238)
!3247 = !DILocation(line: 1355, column: 16, scope: !3238)
!3248 = !DILocation(line: 1354, column: 7, scope: !3249)
!3249 = !DILexicalBlockFile(scope: !3239, file: !1, discriminator: 1)
!3250 = !DILocation(line: 1356, column: 23, scope: !3251)
!3251 = distinct !DILexicalBlock(scope: !3238, file: !1, line: 1355, column: 46)
!3252 = !DILocation(line: 1356, column: 26, scope: !3251)
!3253 = !DILocation(line: 1356, column: 4, scope: !3251)
!3254 = !DILocation(line: 1358, column: 6, scope: !3251)
!3255 = !DILocation(line: 1359, column: 3, scope: !3251)
!3256 = !DILocation(line: 1362, column: 3, scope: !3239)
!3257 = !DILocation(line: 1362, column: 8, scope: !3239)
!3258 = !DILocation(line: 1362, column: 29, scope: !3239)
!3259 = !DILocation(line: 1363, column: 2, scope: !3239)
!3260 = !DILocation(line: 1364, column: 10, scope: !471)
!3261 = !DILocation(line: 1364, column: 2, scope: !471)
!3262 = !DILocalVariable(name: "a", arg: 1, scope: !472, file: !1, line: 1448, type: !4)
!3263 = !DILocation(line: 1448, column: 40, scope: !472)
!3264 = !DILocalVariable(name: "buff", arg: 2, scope: !472, file: !1, line: 1448, type: !64)
!3265 = !DILocation(line: 1448, column: 56, scope: !472)
!3266 = !DILocalVariable(name: "size", arg: 3, scope: !472, file: !1, line: 1449, type: !65)
!3267 = !DILocation(line: 1449, column: 13, scope: !472)
!3268 = !DILocalVariable(name: "offset", arg: 4, scope: !472, file: !1, line: 1449, type: !66)
!3269 = !DILocation(line: 1449, column: 28, scope: !472)
!3270 = !DILocalVariable(name: "lha", scope: !472, file: !1, line: 1451, type: !292)
!3271 = !DILocation(line: 1451, column: 14, scope: !472)
!3272 = !DILocation(line: 1451, column: 35, scope: !472)
!3273 = !DILocation(line: 1451, column: 38, scope: !472)
!3274 = !DILocation(line: 1451, column: 46, scope: !472)
!3275 = !DILocation(line: 1451, column: 20, scope: !472)
!3276 = !DILocalVariable(name: "bytes_avail", scope: !472, file: !1, line: 1452, type: !38)
!3277 = !DILocation(line: 1452, column: 10, scope: !472)
!3278 = !DILocalVariable(name: "r", scope: !472, file: !1, line: 1453, type: !23)
!3279 = !DILocation(line: 1453, column: 6, scope: !472)
!3280 = !DILocation(line: 1456, column: 7, scope: !3281)
!3281 = distinct !DILexicalBlock(scope: !472, file: !1, line: 1456, column: 6)
!3282 = !DILocation(line: 1456, column: 12, scope: !3281)
!3283 = !DILocation(line: 1456, column: 6, scope: !472)
!3284 = !DILocation(line: 1457, column: 25, scope: !3285)
!3285 = distinct !DILexicalBlock(scope: !3281, file: !1, line: 1456, column: 29)
!3286 = !DILocation(line: 1457, column: 30, scope: !3285)
!3287 = !DILocation(line: 1457, column: 37, scope: !3285)
!3288 = !DILocation(line: 1457, column: 42, scope: !3285)
!3289 = !DILocation(line: 1457, column: 7, scope: !3285)
!3290 = !DILocation(line: 1457, column: 5, scope: !3285)
!3291 = !DILocation(line: 1458, column: 11, scope: !3285)
!3292 = !DILocation(line: 1458, column: 3, scope: !3285)
!3293 = !DILocation(line: 1460, column: 4, scope: !3294)
!3294 = distinct !DILexicalBlock(scope: !3285, file: !1, line: 1458, column: 14)
!3295 = !DILocation(line: 1463, column: 5, scope: !3294)
!3296 = !DILocation(line: 1463, column: 10, scope: !3294)
!3297 = !DILocation(line: 1464, column: 5, scope: !3294)
!3298 = !DILocation(line: 1464, column: 10, scope: !3294)
!3299 = !DILocation(line: 1465, column: 5, scope: !3294)
!3300 = !DILocation(line: 1465, column: 12, scope: !3294)
!3301 = !DILocation(line: 1466, column: 23, scope: !3294)
!3302 = !DILocation(line: 1466, column: 26, scope: !3294)
!3303 = !DILocation(line: 1469, column: 8, scope: !3294)
!3304 = !DILocation(line: 1469, column: 13, scope: !3294)
!3305 = !DILocation(line: 1469, column: 24, scope: !3294)
!3306 = !DILocation(line: 1469, column: 29, scope: !3294)
!3307 = !DILocation(line: 1469, column: 40, scope: !3294)
!3308 = !DILocation(line: 1469, column: 45, scope: !3294)
!3309 = !DILocation(line: 1466, column: 4, scope: !3294)
!3310 = !DILocation(line: 1471, column: 43, scope: !3294)
!3311 = !DILocation(line: 1471, column: 4, scope: !3294)
!3312 = !DILocation(line: 1472, column: 4, scope: !3294)
!3313 = !DILocation(line: 1474, column: 23, scope: !3294)
!3314 = !DILocation(line: 1474, column: 26, scope: !3294)
!3315 = !DILocation(line: 1474, column: 4, scope: !3294)
!3316 = !DILocation(line: 1477, column: 4, scope: !3294)
!3317 = !DILocation(line: 1480, column: 3, scope: !3285)
!3318 = !DILocation(line: 1480, column: 8, scope: !3285)
!3319 = !DILocation(line: 1480, column: 24, scope: !3285)
!3320 = !DILocation(line: 1481, column: 3, scope: !3285)
!3321 = !DILocation(line: 1481, column: 8, scope: !3285)
!3322 = !DILocation(line: 1481, column: 13, scope: !3285)
!3323 = !DILocation(line: 1481, column: 23, scope: !3285)
!3324 = !DILocation(line: 1482, column: 3, scope: !3285)
!3325 = !DILocation(line: 1482, column: 8, scope: !3285)
!3326 = !DILocation(line: 1482, column: 13, scope: !3285)
!3327 = !DILocation(line: 1482, column: 23, scope: !3285)
!3328 = !DILocation(line: 1483, column: 2, scope: !3285)
!3329 = !DILocation(line: 1491, column: 43, scope: !472)
!3330 = !DILocation(line: 1491, column: 22, scope: !472)
!3331 = !DILocation(line: 1491, column: 2, scope: !472)
!3332 = !DILocation(line: 1491, column: 7, scope: !472)
!3333 = !DILocation(line: 1491, column: 12, scope: !472)
!3334 = !DILocation(line: 1491, column: 20, scope: !472)
!3335 = !DILocation(line: 1492, column: 6, scope: !3336)
!3336 = distinct !DILexicalBlock(scope: !472, file: !1, line: 1492, column: 6)
!3337 = !DILocation(line: 1492, column: 18, scope: !3336)
!3338 = !DILocation(line: 1492, column: 6, scope: !472)
!3339 = !DILocation(line: 1493, column: 22, scope: !3340)
!3340 = distinct !DILexicalBlock(scope: !3336, file: !1, line: 1492, column: 24)
!3341 = !DILocation(line: 1493, column: 25, scope: !3340)
!3342 = !DILocation(line: 1493, column: 3, scope: !3340)
!3343 = !DILocation(line: 1495, column: 3, scope: !3340)
!3344 = !DILocation(line: 1497, column: 6, scope: !3345)
!3345 = distinct !DILexicalBlock(scope: !472, file: !1, line: 1497, column: 6)
!3346 = !DILocation(line: 1497, column: 20, scope: !3345)
!3347 = !DILocation(line: 1497, column: 25, scope: !3345)
!3348 = !DILocation(line: 1497, column: 18, scope: !3345)
!3349 = !DILocation(line: 1497, column: 6, scope: !472)
!3350 = !DILocation(line: 1498, column: 26, scope: !3345)
!3351 = !DILocation(line: 1498, column: 31, scope: !3345)
!3352 = !DILocation(line: 1498, column: 15, scope: !3345)
!3353 = !DILocation(line: 1498, column: 3, scope: !3345)
!3354 = !DILocation(line: 1500, column: 28, scope: !472)
!3355 = !DILocation(line: 1500, column: 23, scope: !472)
!3356 = !DILocation(line: 1500, column: 2, scope: !472)
!3357 = !DILocation(line: 1500, column: 7, scope: !472)
!3358 = !DILocation(line: 1500, column: 12, scope: !472)
!3359 = !DILocation(line: 1500, column: 21, scope: !472)
!3360 = !DILocation(line: 1501, column: 2, scope: !472)
!3361 = !DILocation(line: 1501, column: 7, scope: !472)
!3362 = !DILocation(line: 1501, column: 12, scope: !472)
!3363 = !DILocation(line: 1501, column: 21, scope: !472)
!3364 = !DILocation(line: 1502, column: 2, scope: !472)
!3365 = !DILocation(line: 1502, column: 7, scope: !472)
!3366 = !DILocation(line: 1502, column: 12, scope: !472)
!3367 = !DILocation(line: 1502, column: 22, scope: !472)
!3368 = !DILocation(line: 1504, column: 19, scope: !472)
!3369 = !DILocation(line: 1504, column: 24, scope: !472)
!3370 = !DILocation(line: 1504, column: 31, scope: !472)
!3371 = !DILocation(line: 1504, column: 46, scope: !472)
!3372 = !DILocation(line: 1504, column: 51, scope: !472)
!3373 = !DILocation(line: 1504, column: 43, scope: !472)
!3374 = !DILocation(line: 1504, column: 6, scope: !472)
!3375 = !DILocation(line: 1504, column: 4, scope: !472)
!3376 = !DILocation(line: 1505, column: 10, scope: !472)
!3377 = !DILocation(line: 1505, column: 2, scope: !472)
!3378 = !DILocation(line: 1507, column: 3, scope: !3379)
!3379 = distinct !DILexicalBlock(scope: !472, file: !1, line: 1505, column: 13)
!3380 = !DILocation(line: 1509, column: 3, scope: !3379)
!3381 = !DILocation(line: 1509, column: 8, scope: !3379)
!3382 = !DILocation(line: 1509, column: 21, scope: !3379)
!3383 = !DILocation(line: 1510, column: 3, scope: !3379)
!3384 = !DILocation(line: 1512, column: 22, scope: !3379)
!3385 = !DILocation(line: 1512, column: 25, scope: !3379)
!3386 = !DILocation(line: 1512, column: 3, scope: !3379)
!3387 = !DILocation(line: 1514, column: 3, scope: !3379)
!3388 = !DILocation(line: 1516, column: 26, scope: !472)
!3389 = !DILocation(line: 1516, column: 31, scope: !472)
!3390 = !DILocation(line: 1516, column: 36, scope: !472)
!3391 = !DILocation(line: 1516, column: 2, scope: !472)
!3392 = !DILocation(line: 1516, column: 7, scope: !472)
!3393 = !DILocation(line: 1516, column: 24, scope: !472)
!3394 = !DILocation(line: 1517, column: 32, scope: !472)
!3395 = !DILocation(line: 1517, column: 37, scope: !472)
!3396 = !DILocation(line: 1517, column: 42, scope: !472)
!3397 = !DILocation(line: 1517, column: 2, scope: !472)
!3398 = !DILocation(line: 1517, column: 7, scope: !472)
!3399 = !DILocation(line: 1517, column: 29, scope: !472)
!3400 = !DILocation(line: 1519, column: 6, scope: !3401)
!3401 = distinct !DILexicalBlock(scope: !472, file: !1, line: 1519, column: 6)
!3402 = !DILocation(line: 1519, column: 11, scope: !3401)
!3403 = !DILocation(line: 1519, column: 16, scope: !3401)
!3404 = !DILocation(line: 1519, column: 6, scope: !472)
!3405 = !DILocation(line: 1520, column: 13, scope: !3406)
!3406 = distinct !DILexicalBlock(scope: !3401, file: !1, line: 1519, column: 27)
!3407 = !DILocation(line: 1520, column: 18, scope: !3406)
!3408 = !DILocation(line: 1520, column: 4, scope: !3406)
!3409 = !DILocation(line: 1520, column: 11, scope: !3406)
!3410 = !DILocation(line: 1521, column: 11, scope: !3406)
!3411 = !DILocation(line: 1521, column: 16, scope: !3406)
!3412 = !DILocation(line: 1521, column: 21, scope: !3406)
!3413 = !DILocation(line: 1521, column: 4, scope: !3406)
!3414 = !DILocation(line: 1521, column: 9, scope: !3406)
!3415 = !DILocation(line: 1522, column: 11, scope: !3406)
!3416 = !DILocation(line: 1522, column: 16, scope: !3406)
!3417 = !DILocation(line: 1522, column: 21, scope: !3406)
!3418 = !DILocation(line: 1522, column: 4, scope: !3406)
!3419 = !DILocation(line: 1522, column: 9, scope: !3406)
!3420 = !DILocation(line: 1524, column: 17, scope: !3406)
!3421 = !DILocation(line: 1524, column: 22, scope: !3406)
!3422 = !DILocation(line: 1524, column: 45, scope: !3406)
!3423 = !DILocation(line: 1524, column: 44, scope: !3406)
!3424 = !DILocation(line: 1524, column: 52, scope: !3406)
!3425 = !DILocation(line: 1524, column: 51, scope: !3406)
!3426 = !DILocation(line: 1524, column: 7, scope: !3406)
!3427 = !DILocation(line: 1523, column: 3, scope: !3406)
!3428 = !DILocation(line: 1523, column: 8, scope: !3406)
!3429 = !DILocation(line: 1523, column: 29, scope: !3406)
!3430 = !DILocation(line: 1525, column: 25, scope: !3406)
!3431 = !DILocation(line: 1525, column: 24, scope: !3406)
!3432 = !DILocation(line: 1525, column: 3, scope: !3406)
!3433 = !DILocation(line: 1525, column: 8, scope: !3406)
!3434 = !DILocation(line: 1525, column: 21, scope: !3406)
!3435 = !DILocation(line: 1526, column: 2, scope: !3406)
!3436 = !DILocation(line: 1527, column: 13, scope: !3437)
!3437 = distinct !DILexicalBlock(scope: !3401, file: !1, line: 1526, column: 9)
!3438 = !DILocation(line: 1527, column: 18, scope: !3437)
!3439 = !DILocation(line: 1527, column: 4, scope: !3437)
!3440 = !DILocation(line: 1527, column: 11, scope: !3437)
!3441 = !DILocation(line: 1528, column: 4, scope: !3437)
!3442 = !DILocation(line: 1528, column: 9, scope: !3437)
!3443 = !DILocation(line: 1529, column: 4, scope: !3437)
!3444 = !DILocation(line: 1529, column: 9, scope: !3437)
!3445 = !DILocation(line: 1530, column: 7, scope: !3446)
!3446 = distinct !DILexicalBlock(scope: !3437, file: !1, line: 1530, column: 7)
!3447 = !DILocation(line: 1530, column: 12, scope: !3446)
!3448 = !DILocation(line: 1530, column: 7, scope: !3437)
!3449 = !DILocation(line: 1531, column: 29, scope: !3446)
!3450 = !DILocation(line: 1531, column: 12, scope: !3446)
!3451 = !DILocation(line: 1531, column: 4, scope: !3446)
!3452 = !DILocation(line: 1533, column: 2, scope: !472)
!3453 = !DILocation(line: 1534, column: 1, scope: !472)
!3454 = !DILocalVariable(name: "a", arg: 1, scope: !508, file: !1, line: 1401, type: !4)
!3455 = !DILocation(line: 1401, column: 41, scope: !508)
!3456 = !DILocalVariable(name: "buff", arg: 2, scope: !508, file: !1, line: 1401, type: !64)
!3457 = !DILocation(line: 1401, column: 57, scope: !508)
!3458 = !DILocalVariable(name: "size", arg: 3, scope: !508, file: !1, line: 1402, type: !65)
!3459 = !DILocation(line: 1402, column: 13, scope: !508)
!3460 = !DILocalVariable(name: "offset", arg: 4, scope: !508, file: !1, line: 1402, type: !66)
!3461 = !DILocation(line: 1402, column: 28, scope: !508)
!3462 = !DILocalVariable(name: "lha", scope: !508, file: !1, line: 1404, type: !292)
!3463 = !DILocation(line: 1404, column: 14, scope: !508)
!3464 = !DILocation(line: 1404, column: 35, scope: !508)
!3465 = !DILocation(line: 1404, column: 38, scope: !508)
!3466 = !DILocation(line: 1404, column: 46, scope: !508)
!3467 = !DILocation(line: 1404, column: 20, scope: !508)
!3468 = !DILocalVariable(name: "bytes_avail", scope: !508, file: !1, line: 1405, type: !38)
!3469 = !DILocation(line: 1405, column: 10, scope: !508)
!3470 = !DILocation(line: 1407, column: 6, scope: !3471)
!3471 = distinct !DILexicalBlock(scope: !508, file: !1, line: 1407, column: 6)
!3472 = !DILocation(line: 1407, column: 11, scope: !3471)
!3473 = !DILocation(line: 1407, column: 33, scope: !3471)
!3474 = !DILocation(line: 1407, column: 6, scope: !508)
!3475 = !DILocation(line: 1408, column: 4, scope: !3476)
!3476 = distinct !DILexicalBlock(scope: !3471, file: !1, line: 1407, column: 39)
!3477 = !DILocation(line: 1408, column: 9, scope: !3476)
!3478 = !DILocation(line: 1409, column: 4, scope: !3476)
!3479 = !DILocation(line: 1409, column: 9, scope: !3476)
!3480 = !DILocation(line: 1410, column: 13, scope: !3476)
!3481 = !DILocation(line: 1410, column: 18, scope: !3476)
!3482 = !DILocation(line: 1410, column: 4, scope: !3476)
!3483 = !DILocation(line: 1410, column: 11, scope: !3476)
!3484 = !DILocation(line: 1411, column: 3, scope: !3476)
!3485 = !DILocation(line: 1411, column: 8, scope: !3476)
!3486 = !DILocation(line: 1411, column: 21, scope: !3476)
!3487 = !DILocation(line: 1412, column: 3, scope: !3476)
!3488 = !DILocation(line: 1420, column: 31, scope: !508)
!3489 = !DILocation(line: 1420, column: 10, scope: !508)
!3490 = !DILocation(line: 1420, column: 3, scope: !508)
!3491 = !DILocation(line: 1420, column: 8, scope: !508)
!3492 = !DILocation(line: 1421, column: 6, scope: !3493)
!3493 = distinct !DILexicalBlock(scope: !508, file: !1, line: 1421, column: 6)
!3494 = !DILocation(line: 1421, column: 18, scope: !3493)
!3495 = !DILocation(line: 1421, column: 6, scope: !508)
!3496 = !DILocation(line: 1422, column: 22, scope: !3497)
!3497 = distinct !DILexicalBlock(scope: !3493, file: !1, line: 1421, column: 24)
!3498 = !DILocation(line: 1422, column: 25, scope: !3497)
!3499 = !DILocation(line: 1422, column: 3, scope: !3497)
!3500 = !DILocation(line: 1424, column: 3, scope: !3497)
!3501 = !DILocation(line: 1426, column: 6, scope: !3502)
!3502 = distinct !DILexicalBlock(scope: !508, file: !1, line: 1426, column: 6)
!3503 = !DILocation(line: 1426, column: 20, scope: !3502)
!3504 = !DILocation(line: 1426, column: 25, scope: !3502)
!3505 = !DILocation(line: 1426, column: 18, scope: !3502)
!3506 = !DILocation(line: 1426, column: 6, scope: !508)
!3507 = !DILocation(line: 1427, column: 26, scope: !3502)
!3508 = !DILocation(line: 1427, column: 31, scope: !3502)
!3509 = !DILocation(line: 1427, column: 15, scope: !3502)
!3510 = !DILocation(line: 1427, column: 3, scope: !3502)
!3511 = !DILocation(line: 1429, column: 16, scope: !508)
!3512 = !DILocation(line: 1429, column: 21, scope: !508)
!3513 = !DILocation(line: 1429, column: 44, scope: !508)
!3514 = !DILocation(line: 1429, column: 43, scope: !508)
!3515 = !DILocation(line: 1429, column: 50, scope: !508)
!3516 = !DILocation(line: 1429, column: 6, scope: !508)
!3517 = !DILocation(line: 1428, column: 2, scope: !508)
!3518 = !DILocation(line: 1428, column: 7, scope: !508)
!3519 = !DILocation(line: 1428, column: 28, scope: !508)
!3520 = !DILocation(line: 1430, column: 10, scope: !508)
!3521 = !DILocation(line: 1430, column: 3, scope: !508)
!3522 = !DILocation(line: 1430, column: 8, scope: !508)
!3523 = !DILocation(line: 1431, column: 12, scope: !508)
!3524 = !DILocation(line: 1431, column: 17, scope: !508)
!3525 = !DILocation(line: 1431, column: 3, scope: !508)
!3526 = !DILocation(line: 1431, column: 10, scope: !508)
!3527 = !DILocation(line: 1432, column: 23, scope: !508)
!3528 = !DILocation(line: 1432, column: 2, scope: !508)
!3529 = !DILocation(line: 1432, column: 7, scope: !508)
!3530 = !DILocation(line: 1432, column: 20, scope: !508)
!3531 = !DILocation(line: 1433, column: 32, scope: !508)
!3532 = !DILocation(line: 1433, column: 2, scope: !508)
!3533 = !DILocation(line: 1433, column: 7, scope: !508)
!3534 = !DILocation(line: 1433, column: 29, scope: !508)
!3535 = !DILocation(line: 1434, column: 6, scope: !3536)
!3536 = distinct !DILexicalBlock(scope: !508, file: !1, line: 1434, column: 6)
!3537 = !DILocation(line: 1434, column: 11, scope: !3536)
!3538 = !DILocation(line: 1434, column: 33, scope: !3536)
!3539 = !DILocation(line: 1434, column: 6, scope: !508)
!3540 = !DILocation(line: 1435, column: 3, scope: !3536)
!3541 = !DILocation(line: 1435, column: 8, scope: !3536)
!3542 = !DILocation(line: 1435, column: 21, scope: !3536)
!3543 = !DILocation(line: 1436, column: 26, scope: !508)
!3544 = !DILocation(line: 1436, column: 2, scope: !508)
!3545 = !DILocation(line: 1436, column: 7, scope: !508)
!3546 = !DILocation(line: 1436, column: 24, scope: !508)
!3547 = !DILocation(line: 1437, column: 2, scope: !508)
!3548 = !DILocation(line: 1438, column: 1, scope: !508)
!3549 = !DILocalVariable(name: "strm", arg: 1, scope: !473, file: !1, line: 1764, type: !476)
!3550 = !DILocation(line: 1764, column: 36, scope: !473)
!3551 = !DILocalVariable(name: "method", arg: 2, scope: !473, file: !1, line: 1764, type: !80)
!3552 = !DILocation(line: 1764, column: 54, scope: !473)
!3553 = !DILocalVariable(name: "ds", scope: !473, file: !1, line: 1766, type: !364)
!3554 = !DILocation(line: 1766, column: 18, scope: !473)
!3555 = !DILocalVariable(name: "w_bits", scope: !473, file: !1, line: 1767, type: !23)
!3556 = !DILocation(line: 1767, column: 6, scope: !473)
!3557 = !DILocalVariable(name: "w_size", scope: !473, file: !1, line: 1767, type: !23)
!3558 = !DILocation(line: 1767, column: 14, scope: !473)
!3559 = !DILocation(line: 1769, column: 6, scope: !3560)
!3560 = distinct !DILexicalBlock(scope: !473, file: !1, line: 1769, column: 6)
!3561 = !DILocation(line: 1769, column: 12, scope: !3560)
!3562 = !DILocation(line: 1769, column: 15, scope: !3560)
!3563 = !DILocation(line: 1769, column: 6, scope: !473)
!3564 = !DILocation(line: 1770, column: 14, scope: !3565)
!3565 = distinct !DILexicalBlock(scope: !3560, file: !1, line: 1769, column: 24)
!3566 = !DILocation(line: 1770, column: 3, scope: !3565)
!3567 = !DILocation(line: 1770, column: 9, scope: !3565)
!3568 = !DILocation(line: 1770, column: 12, scope: !3565)
!3569 = !DILocation(line: 1771, column: 7, scope: !3570)
!3570 = distinct !DILexicalBlock(scope: !3565, file: !1, line: 1771, column: 7)
!3571 = !DILocation(line: 1771, column: 13, scope: !3570)
!3572 = !DILocation(line: 1771, column: 16, scope: !3570)
!3573 = !DILocation(line: 1771, column: 7, scope: !3565)
!3574 = !DILocation(line: 1772, column: 4, scope: !3570)
!3575 = !DILocation(line: 1773, column: 2, scope: !3565)
!3576 = !DILocation(line: 1774, column: 7, scope: !473)
!3577 = !DILocation(line: 1774, column: 13, scope: !473)
!3578 = !DILocation(line: 1774, column: 5, scope: !473)
!3579 = !DILocation(line: 1775, column: 2, scope: !473)
!3580 = !DILocation(line: 1775, column: 6, scope: !473)
!3581 = !DILocation(line: 1775, column: 12, scope: !473)
!3582 = !DILocation(line: 1776, column: 6, scope: !3583)
!3583 = distinct !DILexicalBlock(scope: !473, file: !1, line: 1776, column: 6)
!3584 = !DILocation(line: 1776, column: 13, scope: !3583)
!3585 = !DILocation(line: 1776, column: 21, scope: !3583)
!3586 = !DILocation(line: 1776, column: 24, scope: !3587)
!3587 = !DILexicalBlockFile(scope: !3583, file: !1, discriminator: 1)
!3588 = !DILocation(line: 1776, column: 34, scope: !3587)
!3589 = !DILocation(line: 1776, column: 41, scope: !3587)
!3590 = !DILocation(line: 1776, column: 44, scope: !3591)
!3591 = !DILexicalBlockFile(scope: !3583, file: !1, discriminator: 2)
!3592 = !DILocation(line: 1776, column: 54, scope: !3591)
!3593 = !DILocation(line: 1776, column: 6, scope: !3591)
!3594 = !DILocation(line: 1777, column: 3, scope: !3583)
!3595 = !DILocation(line: 1778, column: 10, scope: !473)
!3596 = !DILocation(line: 1778, column: 2, scope: !473)
!3597 = !DILocation(line: 1780, column: 10, scope: !3598)
!3598 = distinct !DILexicalBlock(scope: !473, file: !1, line: 1778, column: 21)
!3599 = !DILocation(line: 1781, column: 3, scope: !3598)
!3600 = !DILocation(line: 1783, column: 10, scope: !3598)
!3601 = !DILocation(line: 1784, column: 3, scope: !3598)
!3602 = !DILocation(line: 1786, column: 10, scope: !3598)
!3603 = !DILocation(line: 1787, column: 3, scope: !3598)
!3604 = !DILocation(line: 1789, column: 3, scope: !3598)
!3605 = !DILocation(line: 1791, column: 2, scope: !473)
!3606 = !DILocation(line: 1791, column: 6, scope: !473)
!3607 = !DILocation(line: 1791, column: 12, scope: !473)
!3608 = !DILocation(line: 1794, column: 2, scope: !473)
!3609 = !DILocation(line: 1794, column: 6, scope: !473)
!3610 = !DILocation(line: 1794, column: 13, scope: !473)
!3611 = !DILocation(line: 1795, column: 15, scope: !473)
!3612 = !DILocation(line: 1795, column: 19, scope: !473)
!3613 = !DILocation(line: 1795, column: 26, scope: !473)
!3614 = !DILocation(line: 1795, column: 2, scope: !473)
!3615 = !DILocation(line: 1795, column: 6, scope: !473)
!3616 = !DILocation(line: 1795, column: 13, scope: !473)
!3617 = !DILocation(line: 1796, column: 6, scope: !3618)
!3618 = distinct !DILexicalBlock(scope: !473, file: !1, line: 1796, column: 6)
!3619 = !DILocation(line: 1796, column: 10, scope: !3618)
!3620 = !DILocation(line: 1796, column: 17, scope: !3618)
!3621 = !DILocation(line: 1796, column: 6, scope: !473)
!3622 = !DILocation(line: 1797, column: 23, scope: !3623)
!3623 = distinct !DILexicalBlock(scope: !3618, file: !1, line: 1796, column: 26)
!3624 = !DILocation(line: 1797, column: 27, scope: !3623)
!3625 = !DILocation(line: 1797, column: 16, scope: !3623)
!3626 = !DILocation(line: 1797, column: 3, scope: !3623)
!3627 = !DILocation(line: 1797, column: 7, scope: !3623)
!3628 = !DILocation(line: 1797, column: 14, scope: !3623)
!3629 = !DILocation(line: 1798, column: 7, scope: !3630)
!3630 = distinct !DILexicalBlock(scope: !3623, file: !1, line: 1798, column: 7)
!3631 = !DILocation(line: 1798, column: 11, scope: !3630)
!3632 = !DILocation(line: 1798, column: 18, scope: !3630)
!3633 = !DILocation(line: 1798, column: 7, scope: !3623)
!3634 = !DILocation(line: 1799, column: 4, scope: !3630)
!3635 = !DILocation(line: 1800, column: 2, scope: !3623)
!3636 = !DILocation(line: 1801, column: 17, scope: !473)
!3637 = !DILocation(line: 1801, column: 14, scope: !473)
!3638 = !DILocation(line: 1801, column: 9, scope: !473)
!3639 = !DILocation(line: 1802, column: 9, scope: !473)
!3640 = !DILocation(line: 1802, column: 13, scope: !473)
!3641 = !DILocation(line: 1802, column: 22, scope: !473)
!3642 = !DILocation(line: 1802, column: 26, scope: !473)
!3643 = !DILocation(line: 1802, column: 20, scope: !473)
!3644 = !DILocation(line: 1802, column: 35, scope: !473)
!3645 = !DILocation(line: 1802, column: 33, scope: !473)
!3646 = !DILocation(line: 1802, column: 49, scope: !473)
!3647 = !DILocation(line: 1802, column: 2, scope: !473)
!3648 = !DILocation(line: 1803, column: 2, scope: !473)
!3649 = !DILocation(line: 1803, column: 6, scope: !473)
!3650 = !DILocation(line: 1803, column: 12, scope: !473)
!3651 = !DILocation(line: 1804, column: 2, scope: !473)
!3652 = !DILocation(line: 1804, column: 6, scope: !473)
!3653 = !DILocation(line: 1804, column: 12, scope: !473)
!3654 = !DILocation(line: 1805, column: 24, scope: !473)
!3655 = !DILocation(line: 1805, column: 31, scope: !473)
!3656 = !DILocation(line: 1805, column: 2, scope: !473)
!3657 = !DILocation(line: 1805, column: 6, scope: !473)
!3658 = !DILocation(line: 1805, column: 22, scope: !473)
!3659 = !DILocation(line: 1806, column: 25, scope: !473)
!3660 = !DILocation(line: 1806, column: 32, scope: !473)
!3661 = !DILocation(line: 1806, column: 38, scope: !473)
!3662 = !DILocation(line: 1806, column: 41, scope: !3663)
!3663 = !DILexicalBlockFile(scope: !473, file: !1, discriminator: 1)
!3664 = !DILocation(line: 1806, column: 48, scope: !3663)
!3665 = !DILocation(line: 1806, column: 38, scope: !3663)
!3666 = !DILocation(line: 1806, column: 24, scope: !3667)
!3667 = !DILexicalBlockFile(scope: !473, file: !1, discriminator: 2)
!3668 = !DILocation(line: 1806, column: 2, scope: !3667)
!3669 = !DILocation(line: 1806, column: 6, scope: !3667)
!3670 = !DILocation(line: 1806, column: 22, scope: !3667)
!3671 = !DILocation(line: 1807, column: 2, scope: !473)
!3672 = !DILocation(line: 1807, column: 6, scope: !473)
!3673 = !DILocation(line: 1807, column: 26, scope: !473)
!3674 = !DILocation(line: 1808, column: 2, scope: !473)
!3675 = !DILocation(line: 1808, column: 6, scope: !473)
!3676 = !DILocation(line: 1808, column: 26, scope: !473)
!3677 = !DILocation(line: 1809, column: 2, scope: !473)
!3678 = !DILocation(line: 1809, column: 6, scope: !473)
!3679 = !DILocation(line: 1809, column: 9, scope: !473)
!3680 = !DILocation(line: 1809, column: 22, scope: !473)
!3681 = !DILocation(line: 1810, column: 2, scope: !473)
!3682 = !DILocation(line: 1810, column: 6, scope: !473)
!3683 = !DILocation(line: 1810, column: 9, scope: !473)
!3684 = !DILocation(line: 1810, column: 21, scope: !473)
!3685 = !DILocation(line: 1812, column: 25, scope: !3686)
!3686 = distinct !DILexicalBlock(scope: !473, file: !1, line: 1812, column: 6)
!3687 = !DILocation(line: 1812, column: 29, scope: !3686)
!3688 = !DILocation(line: 1812, column: 6, scope: !3686)
!3689 = !DILocation(line: 1813, column: 6, scope: !3686)
!3690 = !DILocation(line: 1812, column: 6, scope: !473)
!3691 = !DILocation(line: 1814, column: 3, scope: !3686)
!3692 = !DILocation(line: 1815, column: 2, scope: !473)
!3693 = !DILocation(line: 1815, column: 6, scope: !473)
!3694 = !DILocation(line: 1815, column: 9, scope: !473)
!3695 = !DILocation(line: 1815, column: 18, scope: !473)
!3696 = !DILocation(line: 1816, column: 25, scope: !3697)
!3697 = distinct !DILexicalBlock(scope: !473, file: !1, line: 1816, column: 6)
!3698 = !DILocation(line: 1816, column: 29, scope: !3697)
!3699 = !DILocation(line: 1816, column: 6, scope: !3697)
!3700 = !DILocation(line: 1817, column: 6, scope: !3697)
!3701 = !DILocation(line: 1816, column: 6, scope: !473)
!3702 = !DILocation(line: 1818, column: 3, scope: !3697)
!3703 = !DILocation(line: 1819, column: 2, scope: !473)
!3704 = !DILocation(line: 1819, column: 6, scope: !473)
!3705 = !DILocation(line: 1819, column: 12, scope: !473)
!3706 = !DILocation(line: 1821, column: 2, scope: !473)
!3707 = !DILocation(line: 1822, column: 1, scope: !473)
!3708 = !DILocalVariable(name: "strm", arg: 1, scope: !481, file: !1, line: 1992, type: !476)
!3709 = !DILocation(line: 1992, column: 31, scope: !481)
!3710 = !DILocalVariable(name: "last", arg: 2, scope: !481, file: !1, line: 1992, type: !23)
!3711 = !DILocation(line: 1992, column: 41, scope: !481)
!3712 = !DILocalVariable(name: "ds", scope: !481, file: !1, line: 1994, type: !364)
!3713 = !DILocation(line: 1994, column: 18, scope: !481)
!3714 = !DILocation(line: 1994, column: 23, scope: !481)
!3715 = !DILocation(line: 1994, column: 29, scope: !481)
!3716 = !DILocalVariable(name: "avail_in", scope: !481, file: !1, line: 1995, type: !23)
!3717 = !DILocation(line: 1995, column: 6, scope: !481)
!3718 = !DILocalVariable(name: "r", scope: !481, file: !1, line: 1996, type: !23)
!3719 = !DILocation(line: 1996, column: 6, scope: !481)
!3720 = !DILocation(line: 1998, column: 6, scope: !3721)
!3721 = distinct !DILexicalBlock(scope: !481, file: !1, line: 1998, column: 6)
!3722 = !DILocation(line: 1998, column: 10, scope: !3721)
!3723 = !DILocation(line: 1998, column: 6, scope: !481)
!3724 = !DILocation(line: 1999, column: 11, scope: !3721)
!3725 = !DILocation(line: 1999, column: 15, scope: !3721)
!3726 = !DILocation(line: 1999, column: 3, scope: !3721)
!3727 = !DILocation(line: 2001, column: 13, scope: !481)
!3728 = !DILocation(line: 2001, column: 19, scope: !481)
!3729 = !DILocation(line: 2001, column: 11, scope: !481)
!3730 = !DILocation(line: 2002, column: 2, scope: !481)
!3731 = !DILocation(line: 2003, column: 7, scope: !3732)
!3732 = distinct !DILexicalBlock(scope: !3733, file: !1, line: 2003, column: 7)
!3733 = distinct !DILexicalBlock(scope: !481, file: !1, line: 2002, column: 5)
!3734 = !DILocation(line: 2003, column: 11, scope: !3732)
!3735 = !DILocation(line: 2003, column: 17, scope: !3732)
!3736 = !DILocation(line: 2003, column: 7, scope: !3733)
!3737 = !DILocation(line: 2004, column: 24, scope: !3732)
!3738 = !DILocation(line: 2004, column: 30, scope: !3732)
!3739 = !DILocation(line: 2004, column: 8, scope: !3732)
!3740 = !DILocation(line: 2004, column: 6, scope: !3732)
!3741 = !DILocation(line: 2004, column: 4, scope: !3732)
!3742 = !DILocation(line: 2006, column: 26, scope: !3732)
!3743 = !DILocation(line: 2006, column: 32, scope: !3732)
!3744 = !DILocation(line: 2006, column: 8, scope: !3732)
!3745 = !DILocation(line: 2006, column: 6, scope: !3732)
!3746 = !DILocation(line: 2007, column: 2, scope: !3733)
!3747 = !DILocation(line: 2007, column: 11, scope: !3748)
!3748 = !DILexicalBlockFile(scope: !481, file: !1, discriminator: 1)
!3749 = !DILocation(line: 2007, column: 13, scope: !3748)
!3750 = !DILocation(line: 2007, column: 2, scope: !3748)
!3751 = !DILocation(line: 2008, column: 20, scope: !481)
!3752 = !DILocation(line: 2008, column: 31, scope: !481)
!3753 = !DILocation(line: 2008, column: 37, scope: !481)
!3754 = !DILocation(line: 2008, column: 29, scope: !481)
!3755 = !DILocation(line: 2008, column: 2, scope: !481)
!3756 = !DILocation(line: 2008, column: 8, scope: !481)
!3757 = !DILocation(line: 2008, column: 17, scope: !481)
!3758 = !DILocation(line: 2009, column: 10, scope: !481)
!3759 = !DILocation(line: 2009, column: 2, scope: !481)
!3760 = !DILocation(line: 2010, column: 1, scope: !481)
!3761 = !DILocalVariable(name: "hf", arg: 1, scope: !477, file: !1, line: 2446, type: !480)
!3762 = !DILocation(line: 2446, column: 34, scope: !477)
!3763 = !DILocalVariable(name: "len_size", arg: 2, scope: !477, file: !1, line: 2446, type: !45)
!3764 = !DILocation(line: 2446, column: 45, scope: !477)
!3765 = !DILocalVariable(name: "tbl_bits", arg: 3, scope: !477, file: !1, line: 2446, type: !23)
!3766 = !DILocation(line: 2446, column: 59, scope: !477)
!3767 = !DILocalVariable(name: "bits", scope: !477, file: !1, line: 2448, type: !23)
!3768 = !DILocation(line: 2448, column: 6, scope: !477)
!3769 = !DILocation(line: 2450, column: 6, scope: !3770)
!3770 = distinct !DILexicalBlock(scope: !477, file: !1, line: 2450, column: 6)
!3771 = !DILocation(line: 2450, column: 10, scope: !3770)
!3772 = !DILocation(line: 2450, column: 17, scope: !3770)
!3773 = !DILocation(line: 2450, column: 6, scope: !477)
!3774 = !DILocation(line: 2451, column: 23, scope: !3775)
!3775 = distinct !DILexicalBlock(scope: !3770, file: !1, line: 2450, column: 26)
!3776 = !DILocation(line: 2451, column: 32, scope: !3775)
!3777 = !DILocation(line: 2451, column: 16, scope: !3775)
!3778 = !DILocation(line: 2451, column: 3, scope: !3775)
!3779 = !DILocation(line: 2451, column: 7, scope: !3775)
!3780 = !DILocation(line: 2451, column: 14, scope: !3775)
!3781 = !DILocation(line: 2452, column: 7, scope: !3782)
!3782 = distinct !DILexicalBlock(scope: !3775, file: !1, line: 2452, column: 7)
!3783 = !DILocation(line: 2452, column: 11, scope: !3782)
!3784 = !DILocation(line: 2452, column: 18, scope: !3782)
!3785 = !DILocation(line: 2452, column: 7, scope: !3775)
!3786 = !DILocation(line: 2453, column: 4, scope: !3782)
!3787 = !DILocation(line: 2454, column: 2, scope: !3775)
!3788 = !DILocation(line: 2455, column: 6, scope: !3789)
!3789 = distinct !DILexicalBlock(scope: !477, file: !1, line: 2455, column: 6)
!3790 = !DILocation(line: 2455, column: 10, scope: !3789)
!3791 = !DILocation(line: 2455, column: 14, scope: !3789)
!3792 = !DILocation(line: 2455, column: 6, scope: !477)
!3793 = !DILocation(line: 2456, column: 7, scope: !3794)
!3794 = distinct !DILexicalBlock(scope: !3795, file: !1, line: 2456, column: 7)
!3795 = distinct !DILexicalBlock(scope: !3789, file: !1, line: 2455, column: 23)
!3796 = !DILocation(line: 2456, column: 16, scope: !3794)
!3797 = !DILocation(line: 2456, column: 7, scope: !3795)
!3798 = !DILocation(line: 2457, column: 11, scope: !3794)
!3799 = !DILocation(line: 2457, column: 9, scope: !3794)
!3800 = !DILocation(line: 2457, column: 4, scope: !3794)
!3801 = !DILocation(line: 2459, column: 9, scope: !3794)
!3802 = !DILocation(line: 2460, column: 34, scope: !3795)
!3803 = !DILocation(line: 2460, column: 31, scope: !3795)
!3804 = !DILocation(line: 2460, column: 40, scope: !3795)
!3805 = !DILocation(line: 2460, column: 13, scope: !3795)
!3806 = !DILocation(line: 2460, column: 3, scope: !3795)
!3807 = !DILocation(line: 2460, column: 7, scope: !3795)
!3808 = !DILocation(line: 2460, column: 11, scope: !3795)
!3809 = !DILocation(line: 2461, column: 7, scope: !3810)
!3810 = distinct !DILexicalBlock(scope: !3795, file: !1, line: 2461, column: 7)
!3811 = !DILocation(line: 2461, column: 11, scope: !3810)
!3812 = !DILocation(line: 2461, column: 15, scope: !3810)
!3813 = !DILocation(line: 2461, column: 7, scope: !3795)
!3814 = !DILocation(line: 2462, column: 4, scope: !3810)
!3815 = !DILocation(line: 2463, column: 2, scope: !3795)
!3816 = !DILocation(line: 2464, column: 6, scope: !3817)
!3817 = distinct !DILexicalBlock(scope: !477, file: !1, line: 2464, column: 6)
!3818 = !DILocation(line: 2464, column: 10, scope: !3817)
!3819 = !DILocation(line: 2464, column: 15, scope: !3817)
!3820 = !DILocation(line: 2464, column: 23, scope: !3817)
!3821 = !DILocation(line: 2464, column: 26, scope: !3822)
!3822 = !DILexicalBlockFile(scope: !3817, file: !1, discriminator: 1)
!3823 = !DILocation(line: 2464, column: 35, scope: !3822)
!3824 = !DILocation(line: 2464, column: 6, scope: !3822)
!3825 = !DILocation(line: 2465, column: 26, scope: !3826)
!3826 = distinct !DILexicalBlock(scope: !3817, file: !1, line: 2464, column: 48)
!3827 = !DILocation(line: 2465, column: 35, scope: !3826)
!3828 = !DILocation(line: 2465, column: 47, scope: !3826)
!3829 = !DILocation(line: 2465, column: 22, scope: !3826)
!3830 = !DILocation(line: 2465, column: 3, scope: !3826)
!3831 = !DILocation(line: 2465, column: 7, scope: !3826)
!3832 = !DILocation(line: 2465, column: 18, scope: !3826)
!3833 = !DILocation(line: 2466, column: 21, scope: !3826)
!3834 = !DILocation(line: 2466, column: 25, scope: !3826)
!3835 = !DILocation(line: 2466, column: 36, scope: !3826)
!3836 = !DILocation(line: 2466, column: 14, scope: !3826)
!3837 = !DILocation(line: 2466, column: 3, scope: !3826)
!3838 = !DILocation(line: 2466, column: 7, scope: !3826)
!3839 = !DILocation(line: 2466, column: 12, scope: !3826)
!3840 = !DILocation(line: 2467, column: 7, scope: !3841)
!3841 = distinct !DILexicalBlock(scope: !3826, file: !1, line: 2467, column: 7)
!3842 = !DILocation(line: 2467, column: 11, scope: !3841)
!3843 = !DILocation(line: 2467, column: 16, scope: !3841)
!3844 = !DILocation(line: 2467, column: 7, scope: !3826)
!3845 = !DILocation(line: 2468, column: 4, scope: !3841)
!3846 = !DILocation(line: 2469, column: 2, scope: !3826)
!3847 = !DILocation(line: 2470, column: 22, scope: !477)
!3848 = !DILocation(line: 2470, column: 17, scope: !477)
!3849 = !DILocation(line: 2470, column: 2, scope: !477)
!3850 = !DILocation(line: 2470, column: 6, scope: !477)
!3851 = !DILocation(line: 2470, column: 15, scope: !477)
!3852 = !DILocation(line: 2471, column: 17, scope: !477)
!3853 = !DILocation(line: 2471, column: 2, scope: !477)
!3854 = !DILocation(line: 2471, column: 6, scope: !477)
!3855 = !DILocation(line: 2471, column: 15, scope: !477)
!3856 = !DILocation(line: 2472, column: 2, scope: !477)
!3857 = !DILocation(line: 2473, column: 1, scope: !477)
!3858 = !DILocalVariable(name: "strm", arg: 1, scope: !484, file: !1, line: 2021, type: !476)
!3859 = !DILocation(line: 2021, column: 36, scope: !484)
!3860 = !DILocalVariable(name: "last", arg: 2, scope: !484, file: !1, line: 2021, type: !23)
!3861 = !DILocation(line: 2021, column: 46, scope: !484)
!3862 = !DILocalVariable(name: "ds", scope: !484, file: !1, line: 2023, type: !364)
!3863 = !DILocation(line: 2023, column: 18, scope: !484)
!3864 = !DILocation(line: 2023, column: 23, scope: !484)
!3865 = !DILocation(line: 2023, column: 29, scope: !484)
!3866 = !DILocalVariable(name: "br", scope: !484, file: !1, line: 2024, type: !488)
!3867 = !DILocation(line: 2024, column: 17, scope: !484)
!3868 = !DILocation(line: 2024, column: 24, scope: !484)
!3869 = !DILocation(line: 2024, column: 28, scope: !484)
!3870 = !DILocalVariable(name: "c", scope: !484, file: !1, line: 2025, type: !23)
!3871 = !DILocation(line: 2025, column: 6, scope: !484)
!3872 = !DILocalVariable(name: "i", scope: !484, file: !1, line: 2025, type: !23)
!3873 = !DILocation(line: 2025, column: 13, scope: !484)
!3874 = !DILocalVariable(name: "rbits", scope: !484, file: !1, line: 2026, type: !13)
!3875 = !DILocation(line: 2026, column: 11, scope: !484)
!3876 = !DILocation(line: 2028, column: 2, scope: !484)
!3877 = !DILocation(line: 2029, column: 11, scope: !3878)
!3878 = distinct !DILexicalBlock(scope: !3879, file: !1, line: 2028, column: 11)
!3879 = distinct !DILexicalBlock(scope: !3880, file: !1, line: 2028, column: 2)
!3880 = distinct !DILexicalBlock(scope: !484, file: !1, line: 2028, column: 2)
!3881 = !DILocation(line: 2029, column: 15, scope: !3878)
!3882 = !DILocation(line: 2029, column: 3, scope: !3878)
!3883 = !DILocation(line: 2038, column: 9, scope: !3884)
!3884 = distinct !DILexicalBlock(scope: !3885, file: !1, line: 2038, column: 8)
!3885 = distinct !DILexicalBlock(scope: !3878, file: !1, line: 2029, column: 22)
!3886 = !DILocation(line: 2038, column: 9, scope: !3887)
!3887 = !DILexicalBlockFile(scope: !3884, file: !1, discriminator: 1)
!3888 = !DILocation(line: 2038, column: 8, scope: !3887)
!3889 = !DILocation(line: 2039, column: 10, scope: !3890)
!3890 = distinct !DILexicalBlock(scope: !3891, file: !1, line: 2039, column: 9)
!3891 = distinct !DILexicalBlock(scope: !3884, file: !1, line: 2038, column: 44)
!3892 = !DILocation(line: 2039, column: 9, scope: !3891)
!3893 = !DILocation(line: 2041, column: 6, scope: !3890)
!3894 = !DILocation(line: 2042, column: 9, scope: !3895)
!3895 = distinct !DILexicalBlock(scope: !3891, file: !1, line: 2042, column: 9)
!3896 = !DILocation(line: 2042, column: 9, scope: !3891)
!3897 = !DILocation(line: 2049, column: 6, scope: !3898)
!3898 = distinct !DILexicalBlock(scope: !3895, file: !1, line: 2042, column: 28)
!3899 = !DILocation(line: 2051, column: 9, scope: !3900)
!3900 = distinct !DILexicalBlock(scope: !3891, file: !1, line: 2051, column: 9)
!3901 = !DILocation(line: 2051, column: 13, scope: !3900)
!3902 = !DILocation(line: 2051, column: 19, scope: !3900)
!3903 = !DILocation(line: 2051, column: 9, scope: !3891)
!3904 = !DILocation(line: 2052, column: 22, scope: !3905)
!3905 = distinct !DILexicalBlock(scope: !3900, file: !1, line: 2051, column: 24)
!3906 = !DILocation(line: 2052, column: 28, scope: !3905)
!3907 = !DILocation(line: 2052, column: 32, scope: !3905)
!3908 = !DILocation(line: 2052, column: 6, scope: !3905)
!3909 = !DILocation(line: 2053, column: 6, scope: !3905)
!3910 = !DILocation(line: 2053, column: 10, scope: !3905)
!3911 = !DILocation(line: 2053, column: 16, scope: !3905)
!3912 = !DILocation(line: 2054, column: 6, scope: !3905)
!3913 = !DILocation(line: 2058, column: 5, scope: !3891)
!3914 = !DILocation(line: 2060, column: 23, scope: !3885)
!3915 = !DILocation(line: 2060, column: 4, scope: !3885)
!3916 = !DILocation(line: 2060, column: 8, scope: !3885)
!3917 = !DILocation(line: 2060, column: 21, scope: !3885)
!3918 = !DILocation(line: 2061, column: 8, scope: !3919)
!3919 = distinct !DILexicalBlock(scope: !3885, file: !1, line: 2061, column: 8)
!3920 = !DILocation(line: 2061, column: 12, scope: !3919)
!3921 = !DILocation(line: 2061, column: 25, scope: !3919)
!3922 = !DILocation(line: 2061, column: 8, scope: !3885)
!3923 = !DILocation(line: 2062, column: 5, scope: !3919)
!3924 = !DILocation(line: 2063, column: 4, scope: !3885)
!3925 = !DILocation(line: 2068, column: 22, scope: !3885)
!3926 = !DILocation(line: 2068, column: 26, scope: !3885)
!3927 = !DILocation(line: 2068, column: 4, scope: !3885)
!3928 = !DILocation(line: 2068, column: 8, scope: !3885)
!3929 = !DILocation(line: 2068, column: 11, scope: !3885)
!3930 = !DILocation(line: 2068, column: 20, scope: !3885)
!3931 = !DILocation(line: 2069, column: 22, scope: !3885)
!3932 = !DILocation(line: 2069, column: 26, scope: !3885)
!3933 = !DILocation(line: 2069, column: 4, scope: !3885)
!3934 = !DILocation(line: 2069, column: 8, scope: !3885)
!3935 = !DILocation(line: 2069, column: 11, scope: !3885)
!3936 = !DILocation(line: 2069, column: 20, scope: !3885)
!3937 = !DILocation(line: 2070, column: 4, scope: !3885)
!3938 = !DILocation(line: 2070, column: 8, scope: !3885)
!3939 = !DILocation(line: 2070, column: 25, scope: !3885)
!3940 = !DILocation(line: 2076, column: 9, scope: !3941)
!3941 = distinct !DILexicalBlock(scope: !3885, file: !1, line: 2076, column: 8)
!3942 = !DILocation(line: 2076, column: 9, scope: !3943)
!3943 = !DILexicalBlockFile(scope: !3941, file: !1, discriminator: 1)
!3944 = !DILocation(line: 2076, column: 9, scope: !3945)
!3945 = !DILexicalBlockFile(scope: !3941, file: !1, discriminator: 2)
!3946 = !DILocation(line: 2076, column: 8, scope: !3945)
!3947 = !DILocation(line: 2077, column: 9, scope: !3948)
!3948 = distinct !DILexicalBlock(scope: !3949, file: !1, line: 2077, column: 9)
!3949 = distinct !DILexicalBlock(scope: !3941, file: !1, line: 2076, column: 55)
!3950 = !DILocation(line: 2077, column: 9, scope: !3949)
!3951 = !DILocation(line: 2078, column: 6, scope: !3948)
!3952 = !DILocation(line: 2079, column: 5, scope: !3949)
!3953 = !DILocation(line: 2079, column: 9, scope: !3949)
!3954 = !DILocation(line: 2079, column: 15, scope: !3949)
!3955 = !DILocation(line: 2080, column: 5, scope: !3949)
!3956 = !DILocation(line: 2082, column: 23, scope: !3885)
!3957 = !DILocation(line: 2082, column: 4, scope: !3885)
!3958 = !DILocation(line: 2082, column: 8, scope: !3885)
!3959 = !DILocation(line: 2082, column: 11, scope: !3885)
!3960 = !DILocation(line: 2082, column: 21, scope: !3885)
!3961 = !DILocation(line: 2083, column: 4, scope: !3885)
!3962 = !DILocation(line: 2086, column: 8, scope: !3963)
!3963 = distinct !DILexicalBlock(scope: !3885, file: !1, line: 2086, column: 8)
!3964 = !DILocation(line: 2086, column: 12, scope: !3963)
!3965 = !DILocation(line: 2086, column: 15, scope: !3963)
!3966 = !DILocation(line: 2086, column: 25, scope: !3963)
!3967 = !DILocation(line: 2086, column: 8, scope: !3885)
!3968 = !DILocation(line: 2088, column: 10, scope: !3969)
!3969 = distinct !DILexicalBlock(scope: !3970, file: !1, line: 2088, column: 9)
!3970 = distinct !DILexicalBlock(scope: !3963, file: !1, line: 2086, column: 31)
!3971 = !DILocation(line: 2088, column: 10, scope: !3972)
!3972 = !DILexicalBlockFile(scope: !3969, file: !1, discriminator: 1)
!3973 = !DILocation(line: 2088, column: 10, scope: !3974)
!3974 = !DILexicalBlockFile(scope: !3969, file: !1, discriminator: 2)
!3975 = !DILocation(line: 2088, column: 9, scope: !3974)
!3976 = !DILocation(line: 2090, column: 10, scope: !3977)
!3977 = distinct !DILexicalBlock(scope: !3978, file: !1, line: 2090, column: 10)
!3978 = distinct !DILexicalBlock(scope: !3969, file: !1, line: 2089, column: 27)
!3979 = !DILocation(line: 2090, column: 10, scope: !3978)
!3980 = !DILocation(line: 2091, column: 7, scope: !3977)
!3981 = !DILocation(line: 2092, column: 6, scope: !3978)
!3982 = !DILocation(line: 2092, column: 10, scope: !3978)
!3983 = !DILocation(line: 2092, column: 16, scope: !3978)
!3984 = !DILocation(line: 2093, column: 6, scope: !3978)
!3985 = !DILocation(line: 2095, column: 32, scope: !3986)
!3986 = distinct !DILexicalBlock(scope: !3970, file: !1, line: 2095, column: 9)
!3987 = !DILocation(line: 2095, column: 36, scope: !3986)
!3988 = !DILocation(line: 2096, column: 9, scope: !3986)
!3989 = !DILocation(line: 2095, column: 10, scope: !3986)
!3990 = !DILocation(line: 2095, column: 9, scope: !3970)
!3991 = !DILocation(line: 2097, column: 6, scope: !3986)
!3992 = !DILocation(line: 2098, column: 5, scope: !3970)
!3993 = !DILocation(line: 2099, column: 9, scope: !3994)
!3994 = distinct !DILexicalBlock(scope: !3970, file: !1, line: 2099, column: 9)
!3995 = !DILocation(line: 2099, column: 13, scope: !3994)
!3996 = !DILocation(line: 2099, column: 9, scope: !3970)
!3997 = !DILocation(line: 2100, column: 6, scope: !3994)
!3998 = !DILocation(line: 2100, column: 10, scope: !3994)
!3999 = !DILocation(line: 2100, column: 16, scope: !3994)
!4000 = !DILocation(line: 2102, column: 6, scope: !3994)
!4001 = !DILocation(line: 2102, column: 10, scope: !3994)
!4002 = !DILocation(line: 2102, column: 16, scope: !3994)
!4003 = !DILocation(line: 2103, column: 5, scope: !3970)
!4004 = !DILocation(line: 2104, column: 15, scope: !4005)
!4005 = distinct !DILexicalBlock(scope: !3963, file: !1, line: 2104, column: 15)
!4006 = !DILocation(line: 2104, column: 19, scope: !4005)
!4007 = !DILocation(line: 2104, column: 22, scope: !4005)
!4008 = !DILocation(line: 2104, column: 34, scope: !4005)
!4009 = !DILocation(line: 2104, column: 38, scope: !4005)
!4010 = !DILocation(line: 2104, column: 41, scope: !4005)
!4011 = !DILocation(line: 2104, column: 32, scope: !4005)
!4012 = !DILocation(line: 2104, column: 15, scope: !3963)
!4013 = !DILocation(line: 2105, column: 5, scope: !4005)
!4014 = !DILocation(line: 2106, column: 4, scope: !3885)
!4015 = !DILocation(line: 2106, column: 8, scope: !3885)
!4016 = !DILocation(line: 2106, column: 13, scope: !3885)
!4017 = !DILocation(line: 2107, column: 11, scope: !3885)
!4018 = !DILocation(line: 2107, column: 15, scope: !3885)
!4019 = !DILocation(line: 2107, column: 18, scope: !3885)
!4020 = !DILocation(line: 2107, column: 4, scope: !3885)
!4021 = !DILocation(line: 2108, column: 8, scope: !4022)
!4022 = distinct !DILexicalBlock(scope: !3885, file: !1, line: 2108, column: 8)
!4023 = !DILocation(line: 2108, column: 12, scope: !4022)
!4024 = !DILocation(line: 2108, column: 15, scope: !4022)
!4025 = !DILocation(line: 2108, column: 25, scope: !4022)
!4026 = !DILocation(line: 2108, column: 29, scope: !4022)
!4027 = !DILocation(line: 2109, column: 8, scope: !4022)
!4028 = !DILocation(line: 2109, column: 12, scope: !4022)
!4029 = !DILocation(line: 2109, column: 15, scope: !4022)
!4030 = !DILocation(line: 2109, column: 27, scope: !4022)
!4031 = !DILocation(line: 2109, column: 31, scope: !4022)
!4032 = !DILocation(line: 2109, column: 24, scope: !4022)
!4033 = !DILocation(line: 2108, column: 8, scope: !4034)
!4034 = !DILexicalBlockFile(scope: !3885, file: !1, discriminator: 1)
!4035 = !DILocation(line: 2110, column: 5, scope: !4036)
!4036 = distinct !DILexicalBlock(scope: !4022, file: !1, line: 2109, column: 48)
!4037 = !DILocation(line: 2110, column: 9, scope: !4036)
!4038 = !DILocation(line: 2110, column: 15, scope: !4036)
!4039 = !DILocation(line: 2111, column: 5, scope: !4036)
!4040 = !DILocation(line: 2109, column: 31, scope: !4041)
!4041 = !DILexicalBlockFile(scope: !4022, file: !1, discriminator: 1)
!4042 = !DILocation(line: 2115, column: 34, scope: !3885)
!4043 = !DILocation(line: 2115, column: 40, scope: !3885)
!4044 = !DILocation(line: 2115, column: 44, scope: !3885)
!4045 = !DILocation(line: 2115, column: 15, scope: !3885)
!4046 = !DILocation(line: 2115, column: 4, scope: !3885)
!4047 = !DILocation(line: 2115, column: 8, scope: !3885)
!4048 = !DILocation(line: 2115, column: 13, scope: !3885)
!4049 = !DILocation(line: 2116, column: 8, scope: !4050)
!4050 = distinct !DILexicalBlock(scope: !3885, file: !1, line: 2116, column: 8)
!4051 = !DILocation(line: 2116, column: 12, scope: !4050)
!4052 = !DILocation(line: 2116, column: 17, scope: !4050)
!4053 = !DILocation(line: 2116, column: 8, scope: !3885)
!4054 = !DILocation(line: 2117, column: 9, scope: !4055)
!4055 = distinct !DILexicalBlock(scope: !4056, file: !1, line: 2117, column: 9)
!4056 = distinct !DILexicalBlock(scope: !4050, file: !1, line: 2116, column: 22)
!4057 = !DILocation(line: 2117, column: 13, scope: !4055)
!4058 = !DILocation(line: 2117, column: 18, scope: !4055)
!4059 = !DILocation(line: 2117, column: 22, scope: !4055)
!4060 = !DILocation(line: 2117, column: 25, scope: !4061)
!4061 = !DILexicalBlockFile(scope: !4055, file: !1, discriminator: 1)
!4062 = !DILocation(line: 2117, column: 9, scope: !4061)
!4063 = !DILocation(line: 2118, column: 6, scope: !4055)
!4064 = !DILocation(line: 2120, column: 5, scope: !4056)
!4065 = !DILocation(line: 2120, column: 9, scope: !4056)
!4066 = !DILocation(line: 2120, column: 15, scope: !4056)
!4067 = !DILocation(line: 2121, column: 5, scope: !4056)
!4068 = !DILocation(line: 2124, column: 9, scope: !4069)
!4069 = distinct !DILexicalBlock(scope: !3885, file: !1, line: 2124, column: 8)
!4070 = !DILocation(line: 2124, column: 9, scope: !4071)
!4071 = !DILexicalBlockFile(scope: !4069, file: !1, discriminator: 1)
!4072 = !DILocation(line: 2124, column: 9, scope: !4073)
!4073 = !DILexicalBlockFile(scope: !4069, file: !1, discriminator: 2)
!4074 = !DILocation(line: 2124, column: 8, scope: !4073)
!4075 = !DILocation(line: 2125, column: 9, scope: !4076)
!4076 = distinct !DILexicalBlock(scope: !4077, file: !1, line: 2125, column: 9)
!4077 = distinct !DILexicalBlock(scope: !4069, file: !1, line: 2124, column: 41)
!4078 = !DILocation(line: 2125, column: 9, scope: !4077)
!4079 = !DILocation(line: 2126, column: 6, scope: !4076)
!4080 = !DILocation(line: 2127, column: 5, scope: !4077)
!4081 = !DILocation(line: 2127, column: 9, scope: !4077)
!4082 = !DILocation(line: 2127, column: 15, scope: !4077)
!4083 = !DILocation(line: 2128, column: 5, scope: !4077)
!4084 = !DILocation(line: 2130, column: 8, scope: !3885)
!4085 = !DILocation(line: 2130, column: 6, scope: !3885)
!4086 = !DILocation(line: 2131, column: 4, scope: !3885)
!4087 = !DILocation(line: 2132, column: 8, scope: !4088)
!4088 = distinct !DILexicalBlock(scope: !3885, file: !1, line: 2132, column: 8)
!4089 = !DILocation(line: 2132, column: 12, scope: !4088)
!4090 = !DILocation(line: 2132, column: 16, scope: !4088)
!4091 = !DILocation(line: 2132, column: 19, scope: !4088)
!4092 = !DILocation(line: 2132, column: 29, scope: !4088)
!4093 = !DILocation(line: 2132, column: 10, scope: !4088)
!4094 = !DILocation(line: 2132, column: 8, scope: !3885)
!4095 = !DILocation(line: 2133, column: 5, scope: !4088)
!4096 = !DILocation(line: 2134, column: 11, scope: !4097)
!4097 = distinct !DILexicalBlock(scope: !3885, file: !1, line: 2134, column: 4)
!4098 = !DILocation(line: 2134, column: 9, scope: !4097)
!4099 = !DILocation(line: 2134, column: 17, scope: !4100)
!4100 = !DILexicalBlockFile(scope: !4101, file: !1, discriminator: 1)
!4101 = distinct !DILexicalBlock(scope: !4097, file: !1, line: 2134, column: 4)
!4102 = !DILocation(line: 2134, column: 20, scope: !4100)
!4103 = !DILocation(line: 2134, column: 4, scope: !4100)
!4104 = !DILocation(line: 2135, column: 20, scope: !4101)
!4105 = !DILocation(line: 2135, column: 5, scope: !4101)
!4106 = !DILocation(line: 2135, column: 9, scope: !4101)
!4107 = !DILocation(line: 2135, column: 12, scope: !4101)
!4108 = !DILocation(line: 2135, column: 24, scope: !4101)
!4109 = !DILocation(line: 2134, column: 4, scope: !4110)
!4110 = !DILexicalBlockFile(scope: !4101, file: !1, discriminator: 2)
!4111 = !DILocation(line: 2136, column: 15, scope: !3885)
!4112 = !DILocation(line: 2136, column: 4, scope: !3885)
!4113 = !DILocation(line: 2136, column: 8, scope: !3885)
!4114 = !DILocation(line: 2136, column: 13, scope: !3885)
!4115 = !DILocation(line: 2139, column: 34, scope: !3885)
!4116 = !DILocation(line: 2139, column: 40, scope: !3885)
!4117 = !DILocation(line: 2139, column: 44, scope: !3885)
!4118 = !DILocation(line: 2140, column: 8, scope: !3885)
!4119 = !DILocation(line: 2140, column: 12, scope: !3885)
!4120 = !DILocation(line: 2140, column: 15, scope: !3885)
!4121 = !DILocation(line: 2139, column: 15, scope: !3885)
!4122 = !DILocation(line: 2139, column: 4, scope: !3885)
!4123 = !DILocation(line: 2139, column: 8, scope: !3885)
!4124 = !DILocation(line: 2139, column: 13, scope: !3885)
!4125 = !DILocation(line: 2141, column: 8, scope: !4126)
!4126 = distinct !DILexicalBlock(scope: !3885, file: !1, line: 2141, column: 8)
!4127 = !DILocation(line: 2141, column: 12, scope: !4126)
!4128 = !DILocation(line: 2141, column: 19, scope: !4126)
!4129 = !DILocation(line: 2141, column: 23, scope: !4126)
!4130 = !DILocation(line: 2141, column: 26, scope: !4126)
!4131 = !DILocation(line: 2141, column: 17, scope: !4126)
!4132 = !DILocation(line: 2141, column: 8, scope: !3885)
!4133 = !DILocation(line: 2142, column: 9, scope: !4134)
!4134 = distinct !DILexicalBlock(scope: !4135, file: !1, line: 2142, column: 9)
!4135 = distinct !DILexicalBlock(scope: !4126, file: !1, line: 2141, column: 37)
!4136 = !DILocation(line: 2142, column: 13, scope: !4134)
!4137 = !DILocation(line: 2142, column: 18, scope: !4134)
!4138 = !DILocation(line: 2142, column: 22, scope: !4134)
!4139 = !DILocation(line: 2142, column: 25, scope: !4140)
!4140 = !DILexicalBlockFile(scope: !4134, file: !1, discriminator: 1)
!4141 = !DILocation(line: 2142, column: 9, scope: !4140)
!4142 = !DILocation(line: 2143, column: 6, scope: !4134)
!4143 = !DILocation(line: 2145, column: 5, scope: !4135)
!4144 = !DILocation(line: 2145, column: 9, scope: !4135)
!4145 = !DILocation(line: 2145, column: 15, scope: !4135)
!4146 = !DILocation(line: 2146, column: 5, scope: !4135)
!4147 = !DILocation(line: 2148, column: 34, scope: !4148)
!4148 = distinct !DILexicalBlock(scope: !3885, file: !1, line: 2148, column: 8)
!4149 = !DILocation(line: 2148, column: 38, scope: !4148)
!4150 = !DILocation(line: 2148, column: 9, scope: !4148)
!4151 = !DILocation(line: 2148, column: 8, scope: !3885)
!4152 = !DILocation(line: 2149, column: 5, scope: !4148)
!4153 = !DILocation(line: 2150, column: 8, scope: !4154)
!4154 = distinct !DILexicalBlock(scope: !3885, file: !1, line: 2150, column: 8)
!4155 = !DILocation(line: 2150, column: 12, scope: !4154)
!4156 = !DILocation(line: 2150, column: 8, scope: !3885)
!4157 = !DILocation(line: 2151, column: 5, scope: !4158)
!4158 = distinct !DILexicalBlock(scope: !4154, file: !1, line: 2150, column: 30)
!4159 = !DILocation(line: 2151, column: 9, scope: !4158)
!4160 = !DILocation(line: 2151, column: 15, scope: !4158)
!4161 = !DILocation(line: 2152, column: 5, scope: !4158)
!4162 = !DILocation(line: 2150, column: 12, scope: !4163)
!4163 = !DILexicalBlockFile(scope: !4154, file: !1, discriminator: 1)
!4164 = !DILocation(line: 2156, column: 9, scope: !4165)
!4165 = distinct !DILexicalBlock(scope: !3885, file: !1, line: 2156, column: 8)
!4166 = !DILocation(line: 2156, column: 9, scope: !4167)
!4167 = !DILexicalBlockFile(scope: !4165, file: !1, discriminator: 1)
!4168 = !DILocation(line: 2156, column: 9, scope: !4169)
!4169 = !DILexicalBlockFile(scope: !4165, file: !1, discriminator: 2)
!4170 = !DILocation(line: 2156, column: 8, scope: !4169)
!4171 = !DILocation(line: 2157, column: 9, scope: !4172)
!4172 = distinct !DILexicalBlock(scope: !4173, file: !1, line: 2157, column: 9)
!4173 = distinct !DILexicalBlock(scope: !4165, file: !1, line: 2156, column: 55)
!4174 = !DILocation(line: 2157, column: 9, scope: !4173)
!4175 = !DILocation(line: 2158, column: 6, scope: !4172)
!4176 = !DILocation(line: 2159, column: 5, scope: !4173)
!4177 = !DILocation(line: 2159, column: 9, scope: !4173)
!4178 = !DILocation(line: 2159, column: 15, scope: !4173)
!4179 = !DILocation(line: 2160, column: 5, scope: !4173)
!4180 = !DILocation(line: 2162, column: 23, scope: !3885)
!4181 = !DILocation(line: 2162, column: 4, scope: !3885)
!4182 = !DILocation(line: 2162, column: 8, scope: !3885)
!4183 = !DILocation(line: 2162, column: 11, scope: !3885)
!4184 = !DILocation(line: 2162, column: 21, scope: !3885)
!4185 = !DILocation(line: 2163, column: 4, scope: !3885)
!4186 = !DILocation(line: 2166, column: 8, scope: !4187)
!4187 = distinct !DILexicalBlock(scope: !3885, file: !1, line: 2166, column: 8)
!4188 = !DILocation(line: 2166, column: 12, scope: !4187)
!4189 = !DILocation(line: 2166, column: 15, scope: !4187)
!4190 = !DILocation(line: 2166, column: 25, scope: !4187)
!4191 = !DILocation(line: 2166, column: 8, scope: !3885)
!4192 = !DILocation(line: 2168, column: 10, scope: !4193)
!4193 = distinct !DILexicalBlock(scope: !4194, file: !1, line: 2168, column: 9)
!4194 = distinct !DILexicalBlock(scope: !4187, file: !1, line: 2166, column: 31)
!4195 = !DILocation(line: 2168, column: 10, scope: !4196)
!4196 = !DILexicalBlockFile(scope: !4193, file: !1, discriminator: 1)
!4197 = !DILocation(line: 2168, column: 10, scope: !4198)
!4198 = !DILexicalBlockFile(scope: !4193, file: !1, discriminator: 2)
!4199 = !DILocation(line: 2168, column: 9, scope: !4198)
!4200 = !DILocation(line: 2170, column: 10, scope: !4201)
!4201 = distinct !DILexicalBlock(scope: !4202, file: !1, line: 2170, column: 10)
!4202 = distinct !DILexicalBlock(scope: !4193, file: !1, line: 2169, column: 27)
!4203 = !DILocation(line: 2170, column: 10, scope: !4202)
!4204 = !DILocation(line: 2171, column: 7, scope: !4201)
!4205 = !DILocation(line: 2172, column: 6, scope: !4202)
!4206 = !DILocation(line: 2172, column: 10, scope: !4202)
!4207 = !DILocation(line: 2172, column: 16, scope: !4202)
!4208 = !DILocation(line: 2173, column: 6, scope: !4202)
!4209 = !DILocation(line: 2175, column: 32, scope: !4210)
!4210 = distinct !DILexicalBlock(scope: !4194, file: !1, line: 2175, column: 9)
!4211 = !DILocation(line: 2175, column: 36, scope: !4210)
!4212 = !DILocation(line: 2176, column: 9, scope: !4210)
!4213 = !DILocation(line: 2175, column: 10, scope: !4210)
!4214 = !DILocation(line: 2175, column: 9, scope: !4194)
!4215 = !DILocation(line: 2177, column: 6, scope: !4210)
!4216 = !DILocation(line: 2178, column: 5, scope: !4194)
!4217 = !DILocation(line: 2179, column: 5, scope: !4194)
!4218 = !DILocation(line: 2179, column: 9, scope: !4194)
!4219 = !DILocation(line: 2179, column: 15, scope: !4194)
!4220 = !DILocation(line: 2180, column: 5, scope: !4194)
!4221 = !DILocation(line: 2181, column: 15, scope: !4222)
!4222 = distinct !DILexicalBlock(scope: !4187, file: !1, line: 2181, column: 15)
!4223 = !DILocation(line: 2181, column: 19, scope: !4222)
!4224 = !DILocation(line: 2181, column: 22, scope: !4222)
!4225 = !DILocation(line: 2181, column: 34, scope: !4222)
!4226 = !DILocation(line: 2181, column: 38, scope: !4222)
!4227 = !DILocation(line: 2181, column: 41, scope: !4222)
!4228 = !DILocation(line: 2181, column: 32, scope: !4222)
!4229 = !DILocation(line: 2181, column: 15, scope: !4187)
!4230 = !DILocation(line: 2182, column: 5, scope: !4222)
!4231 = !DILocation(line: 2183, column: 4, scope: !3885)
!4232 = !DILocation(line: 2183, column: 8, scope: !3885)
!4233 = !DILocation(line: 2183, column: 13, scope: !3885)
!4234 = !DILocation(line: 2184, column: 11, scope: !3885)
!4235 = !DILocation(line: 2184, column: 15, scope: !3885)
!4236 = !DILocation(line: 2184, column: 18, scope: !3885)
!4237 = !DILocation(line: 2184, column: 4, scope: !3885)
!4238 = !DILocation(line: 2187, column: 8, scope: !3885)
!4239 = !DILocation(line: 2187, column: 12, scope: !3885)
!4240 = !DILocation(line: 2187, column: 6, scope: !3885)
!4241 = !DILocation(line: 2188, column: 4, scope: !3885)
!4242 = !DILocation(line: 2188, column: 11, scope: !4034)
!4243 = !DILocation(line: 2188, column: 15, scope: !4034)
!4244 = !DILocation(line: 2188, column: 19, scope: !4034)
!4245 = !DILocation(line: 2188, column: 22, scope: !4034)
!4246 = !DILocation(line: 2188, column: 13, scope: !4034)
!4247 = !DILocation(line: 2188, column: 4, scope: !4034)
!4248 = !DILocation(line: 2189, column: 10, scope: !4249)
!4249 = distinct !DILexicalBlock(scope: !4250, file: !1, line: 2189, column: 9)
!4250 = distinct !DILexicalBlock(scope: !3885, file: !1, line: 2188, column: 33)
!4251 = !DILocation(line: 2189, column: 10, scope: !4252)
!4252 = !DILexicalBlockFile(scope: !4249, file: !1, discriminator: 1)
!4253 = !DILocation(line: 2189, column: 10, scope: !4254)
!4254 = !DILexicalBlockFile(scope: !4249, file: !1, discriminator: 2)
!4255 = !DILocation(line: 2189, column: 9, scope: !4254)
!4256 = !DILocation(line: 2191, column: 10, scope: !4257)
!4257 = distinct !DILexicalBlock(scope: !4258, file: !1, line: 2191, column: 10)
!4258 = distinct !DILexicalBlock(scope: !4249, file: !1, line: 2190, column: 27)
!4259 = !DILocation(line: 2191, column: 10, scope: !4258)
!4260 = !DILocation(line: 2192, column: 7, scope: !4257)
!4261 = !DILocation(line: 2193, column: 17, scope: !4258)
!4262 = !DILocation(line: 2193, column: 6, scope: !4258)
!4263 = !DILocation(line: 2193, column: 10, scope: !4258)
!4264 = !DILocation(line: 2193, column: 15, scope: !4258)
!4265 = !DILocation(line: 2194, column: 6, scope: !4258)
!4266 = !DILocation(line: 2194, column: 10, scope: !4258)
!4267 = !DILocation(line: 2194, column: 16, scope: !4258)
!4268 = !DILocation(line: 2195, column: 6, scope: !4258)
!4269 = !DILocation(line: 2197, column: 13, scope: !4250)
!4270 = !DILocation(line: 2197, column: 11, scope: !4250)
!4271 = !DILocation(line: 2198, column: 30, scope: !4250)
!4272 = !DILocation(line: 2198, column: 34, scope: !4250)
!4273 = !DILocation(line: 2198, column: 39, scope: !4250)
!4274 = !DILocation(line: 2198, column: 9, scope: !4250)
!4275 = !DILocation(line: 2198, column: 7, scope: !4250)
!4276 = !DILocation(line: 2199, column: 9, scope: !4277)
!4277 = distinct !DILexicalBlock(scope: !4250, file: !1, line: 2199, column: 9)
!4278 = !DILocation(line: 2199, column: 11, scope: !4277)
!4279 = !DILocation(line: 2199, column: 9, scope: !4250)
!4280 = !DILocation(line: 2205, column: 6, scope: !4281)
!4281 = distinct !DILexicalBlock(scope: !4277, file: !1, line: 2199, column: 16)
!4282 = !DILocation(line: 2206, column: 8, scope: !4281)
!4283 = !DILocation(line: 2207, column: 18, scope: !4281)
!4284 = !DILocation(line: 2207, column: 6, scope: !4281)
!4285 = !DILocation(line: 2207, column: 10, scope: !4281)
!4286 = !DILocation(line: 2207, column: 13, scope: !4281)
!4287 = !DILocation(line: 2207, column: 20, scope: !4281)
!4288 = !DILocation(line: 2208, column: 27, scope: !4281)
!4289 = !DILocation(line: 2208, column: 21, scope: !4281)
!4290 = !DILocation(line: 2208, column: 6, scope: !4281)
!4291 = !DILocation(line: 2208, column: 10, scope: !4281)
!4292 = !DILocation(line: 2208, column: 13, scope: !4281)
!4293 = !DILocation(line: 2208, column: 25, scope: !4281)
!4294 = !DILocation(line: 2209, column: 5, scope: !4281)
!4295 = !DILocation(line: 2209, column: 16, scope: !4296)
!4296 = !DILexicalBlockFile(scope: !4297, file: !1, discriminator: 1)
!4297 = distinct !DILexicalBlock(scope: !4277, file: !1, line: 2209, column: 16)
!4298 = !DILocation(line: 2209, column: 18, scope: !4296)
!4299 = !DILocation(line: 2210, column: 6, scope: !4300)
!4300 = distinct !DILexicalBlock(scope: !4297, file: !1, line: 2209, column: 24)
!4301 = !DILocation(line: 2211, column: 21, scope: !4300)
!4302 = !DILocation(line: 2211, column: 6, scope: !4300)
!4303 = !DILocation(line: 2211, column: 10, scope: !4300)
!4304 = !DILocation(line: 2211, column: 13, scope: !4300)
!4305 = !DILocation(line: 2211, column: 25, scope: !4300)
!4306 = !DILocation(line: 2212, column: 5, scope: !4300)
!4307 = !DILocalVariable(name: "n", scope: !4308, file: !1, line: 2214, type: !23)
!4308 = distinct !DILexicalBlock(scope: !4297, file: !1, line: 2212, column: 12)
!4309 = !DILocation(line: 2214, column: 10, scope: !4308)
!4310 = !DILocation(line: 2214, column: 15, scope: !4308)
!4311 = !DILocation(line: 2214, column: 17, scope: !4308)
!4312 = !DILocation(line: 2214, column: 14, scope: !4308)
!4313 = !DILocation(line: 2215, column: 11, scope: !4314)
!4314 = distinct !DILexicalBlock(scope: !4308, file: !1, line: 2215, column: 10)
!4315 = !DILocation(line: 2215, column: 11, scope: !4316)
!4316 = !DILexicalBlockFile(scope: !4314, file: !1, discriminator: 1)
!4317 = !DILocation(line: 2215, column: 11, scope: !4318)
!4318 = !DILexicalBlockFile(scope: !4314, file: !1, discriminator: 2)
!4319 = !DILocation(line: 2215, column: 10, scope: !4318)
!4320 = !DILocation(line: 2217, column: 11, scope: !4321)
!4321 = distinct !DILexicalBlock(scope: !4322, file: !1, line: 2217, column: 11)
!4322 = distinct !DILexicalBlock(scope: !4314, file: !1, line: 2216, column: 34)
!4323 = !DILocation(line: 2217, column: 11, scope: !4322)
!4324 = !DILocation(line: 2218, column: 8, scope: !4321)
!4325 = !DILocation(line: 2219, column: 18, scope: !4322)
!4326 = !DILocation(line: 2219, column: 7, scope: !4322)
!4327 = !DILocation(line: 2219, column: 11, scope: !4322)
!4328 = !DILocation(line: 2219, column: 16, scope: !4322)
!4329 = !DILocation(line: 2220, column: 7, scope: !4322)
!4330 = !DILocation(line: 2220, column: 11, scope: !4322)
!4331 = !DILocation(line: 2220, column: 17, scope: !4322)
!4332 = !DILocation(line: 2221, column: 7, scope: !4322)
!4333 = !DILocation(line: 2223, column: 6, scope: !4308)
!4334 = !DILocation(line: 2224, column: 10, scope: !4308)
!4335 = !DILocation(line: 2224, column: 8, scope: !4308)
!4336 = !DILocation(line: 2225, column: 6, scope: !4308)
!4337 = !DILocation(line: 2226, column: 12, scope: !4308)
!4338 = !DILocation(line: 2226, column: 14, scope: !4308)
!4339 = !DILocation(line: 2226, column: 11, scope: !4308)
!4340 = !DILocation(line: 2226, column: 8, scope: !4308)
!4341 = !DILocation(line: 2227, column: 10, scope: !4342)
!4342 = distinct !DILexicalBlock(scope: !4308, file: !1, line: 2227, column: 10)
!4343 = !DILocation(line: 2227, column: 14, scope: !4342)
!4344 = !DILocation(line: 2227, column: 12, scope: !4342)
!4345 = !DILocation(line: 2227, column: 18, scope: !4342)
!4346 = !DILocation(line: 2227, column: 22, scope: !4342)
!4347 = !DILocation(line: 2227, column: 25, scope: !4342)
!4348 = !DILocation(line: 2227, column: 16, scope: !4342)
!4349 = !DILocation(line: 2227, column: 10, scope: !4308)
!4350 = !DILocation(line: 2228, column: 7, scope: !4342)
!4351 = !DILocation(line: 2229, column: 29, scope: !4308)
!4352 = !DILocation(line: 2229, column: 15, scope: !4308)
!4353 = !DILocation(line: 2229, column: 19, scope: !4308)
!4354 = !DILocation(line: 2229, column: 22, scope: !4308)
!4355 = !DILocation(line: 2229, column: 37, scope: !4308)
!4356 = !DILocation(line: 2229, column: 6, scope: !4308)
!4357 = !DILocation(line: 2230, column: 11, scope: !4308)
!4358 = !DILocation(line: 2230, column: 8, scope: !4308)
!4359 = !DILocation(line: 2188, column: 4, scope: !4360)
!4360 = !DILexicalBlockFile(scope: !3885, file: !1, discriminator: 2)
!4361 = !DILocation(line: 2233, column: 8, scope: !4362)
!4362 = distinct !DILexicalBlock(scope: !3885, file: !1, line: 2233, column: 8)
!4363 = !DILocation(line: 2233, column: 12, scope: !4362)
!4364 = !DILocation(line: 2233, column: 16, scope: !4362)
!4365 = !DILocation(line: 2233, column: 19, scope: !4362)
!4366 = !DILocation(line: 2233, column: 10, scope: !4362)
!4367 = !DILocation(line: 2233, column: 29, scope: !4362)
!4368 = !DILocation(line: 2234, column: 34, scope: !4362)
!4369 = !DILocation(line: 2234, column: 38, scope: !4362)
!4370 = !DILocation(line: 2234, column: 9, scope: !4362)
!4371 = !DILocation(line: 2233, column: 8, scope: !4034)
!4372 = !DILocation(line: 2235, column: 5, scope: !4362)
!4373 = !DILocation(line: 2234, column: 41, scope: !4374)
!4374 = !DILexicalBlockFile(scope: !4362, file: !1, discriminator: 1)
!4375 = !DILocation(line: 2242, column: 22, scope: !3885)
!4376 = !DILocation(line: 2242, column: 26, scope: !3885)
!4377 = !DILocation(line: 2242, column: 4, scope: !3885)
!4378 = !DILocation(line: 2242, column: 8, scope: !3885)
!4379 = !DILocation(line: 2242, column: 11, scope: !3885)
!4380 = !DILocation(line: 2242, column: 20, scope: !3885)
!4381 = !DILocation(line: 2243, column: 22, scope: !3885)
!4382 = !DILocation(line: 2243, column: 26, scope: !3885)
!4383 = !DILocation(line: 2243, column: 4, scope: !3885)
!4384 = !DILocation(line: 2243, column: 8, scope: !3885)
!4385 = !DILocation(line: 2243, column: 11, scope: !3885)
!4386 = !DILocation(line: 2243, column: 20, scope: !3885)
!4387 = !DILocation(line: 2244, column: 4, scope: !3885)
!4388 = !DILocation(line: 2244, column: 8, scope: !3885)
!4389 = !DILocation(line: 2244, column: 25, scope: !3885)
!4390 = !DILocation(line: 2245, column: 4, scope: !3885)
!4391 = !DILocation(line: 2245, column: 8, scope: !3885)
!4392 = !DILocation(line: 2245, column: 14, scope: !3885)
!4393 = !DILocation(line: 2246, column: 4, scope: !3885)
!4394 = !DILocation(line: 2248, column: 4, scope: !3885)
!4395 = !DILocation(line: 2028, column: 2, scope: !4396)
!4396 = !DILexicalBlockFile(scope: !3879, file: !1, discriminator: 1)
!4397 = !DILocation(line: 2252, column: 10, scope: !484)
!4398 = !DILocation(line: 2252, column: 14, scope: !484)
!4399 = !DILocation(line: 2252, column: 20, scope: !484)
!4400 = !DILocation(line: 2252, column: 2, scope: !484)
!4401 = !DILocation(line: 2253, column: 1, scope: !484)
!4402 = !DILocalVariable(name: "strm", arg: 1, scope: !507, file: !1, line: 2256, type: !476)
!4403 = !DILocation(line: 2256, column: 38, scope: !507)
!4404 = !DILocalVariable(name: "last", arg: 2, scope: !507, file: !1, line: 2256, type: !23)
!4405 = !DILocation(line: 2256, column: 48, scope: !507)
!4406 = !DILocalVariable(name: "ds", scope: !507, file: !1, line: 2258, type: !364)
!4407 = !DILocation(line: 2258, column: 18, scope: !507)
!4408 = !DILocation(line: 2258, column: 23, scope: !507)
!4409 = !DILocation(line: 2258, column: 29, scope: !507)
!4410 = !DILocalVariable(name: "bre", scope: !507, file: !1, line: 2259, type: !376)
!4411 = !DILocation(line: 2259, column: 16, scope: !507)
!4412 = !DILocation(line: 2259, column: 22, scope: !507)
!4413 = !DILocation(line: 2259, column: 26, scope: !507)
!4414 = !DILocalVariable(name: "lt", scope: !507, file: !1, line: 2260, type: !480)
!4415 = !DILocation(line: 2260, column: 18, scope: !507)
!4416 = !DILocation(line: 2260, column: 25, scope: !507)
!4417 = !DILocation(line: 2260, column: 29, scope: !507)
!4418 = !DILocalVariable(name: "pt", scope: !507, file: !1, line: 2261, type: !480)
!4419 = !DILocation(line: 2261, column: 18, scope: !507)
!4420 = !DILocation(line: 2261, column: 25, scope: !507)
!4421 = !DILocation(line: 2261, column: 29, scope: !507)
!4422 = !DILocalVariable(name: "w_buff", scope: !507, file: !1, line: 2262, type: !371)
!4423 = !DILocation(line: 2262, column: 17, scope: !507)
!4424 = !DILocation(line: 2262, column: 26, scope: !507)
!4425 = !DILocation(line: 2262, column: 30, scope: !507)
!4426 = !DILocalVariable(name: "lt_bitlen", scope: !507, file: !1, line: 2263, type: !371)
!4427 = !DILocation(line: 2263, column: 17, scope: !507)
!4428 = !DILocation(line: 2263, column: 29, scope: !507)
!4429 = !DILocation(line: 2263, column: 33, scope: !507)
!4430 = !DILocalVariable(name: "pt_bitlen", scope: !507, file: !1, line: 2264, type: !371)
!4431 = !DILocation(line: 2264, column: 17, scope: !507)
!4432 = !DILocation(line: 2264, column: 29, scope: !507)
!4433 = !DILocation(line: 2264, column: 33, scope: !507)
!4434 = !DILocalVariable(name: "blocks_avail", scope: !507, file: !1, line: 2265, type: !23)
!4435 = !DILocation(line: 2265, column: 6, scope: !507)
!4436 = !DILocation(line: 2265, column: 21, scope: !507)
!4437 = !DILocation(line: 2265, column: 25, scope: !507)
!4438 = !DILocalVariable(name: "c", scope: !507, file: !1, line: 2265, type: !23)
!4439 = !DILocation(line: 2265, column: 39, scope: !507)
!4440 = !DILocalVariable(name: "copy_len", scope: !507, file: !1, line: 2266, type: !23)
!4441 = !DILocation(line: 2266, column: 6, scope: !507)
!4442 = !DILocation(line: 2266, column: 17, scope: !507)
!4443 = !DILocation(line: 2266, column: 21, scope: !507)
!4444 = !DILocalVariable(name: "copy_pos", scope: !507, file: !1, line: 2266, type: !23)
!4445 = !DILocation(line: 2266, column: 31, scope: !507)
!4446 = !DILocation(line: 2266, column: 42, scope: !507)
!4447 = !DILocation(line: 2266, column: 46, scope: !507)
!4448 = !DILocalVariable(name: "w_pos", scope: !507, file: !1, line: 2267, type: !23)
!4449 = !DILocation(line: 2267, column: 6, scope: !507)
!4450 = !DILocation(line: 2267, column: 14, scope: !507)
!4451 = !DILocation(line: 2267, column: 18, scope: !507)
!4452 = !DILocalVariable(name: "w_mask", scope: !507, file: !1, line: 2267, type: !23)
!4453 = !DILocation(line: 2267, column: 25, scope: !507)
!4454 = !DILocation(line: 2267, column: 34, scope: !507)
!4455 = !DILocation(line: 2267, column: 38, scope: !507)
!4456 = !DILocalVariable(name: "w_size", scope: !507, file: !1, line: 2267, type: !23)
!4457 = !DILocation(line: 2267, column: 46, scope: !507)
!4458 = !DILocation(line: 2267, column: 55, scope: !507)
!4459 = !DILocation(line: 2267, column: 59, scope: !507)
!4460 = !DILocalVariable(name: "lt_max_bits", scope: !507, file: !1, line: 2268, type: !23)
!4461 = !DILocation(line: 2268, column: 6, scope: !507)
!4462 = !DILocation(line: 2268, column: 20, scope: !507)
!4463 = !DILocation(line: 2268, column: 24, scope: !507)
!4464 = !DILocalVariable(name: "pt_max_bits", scope: !507, file: !1, line: 2268, type: !23)
!4465 = !DILocation(line: 2268, column: 34, scope: !507)
!4466 = !DILocation(line: 2268, column: 48, scope: !507)
!4467 = !DILocation(line: 2268, column: 52, scope: !507)
!4468 = !DILocalVariable(name: "state", scope: !507, file: !1, line: 2269, type: !23)
!4469 = !DILocation(line: 2269, column: 6, scope: !507)
!4470 = !DILocation(line: 2269, column: 14, scope: !507)
!4471 = !DILocation(line: 2269, column: 18, scope: !507)
!4472 = !DILocation(line: 2271, column: 2, scope: !507)
!4473 = !DILocation(line: 2272, column: 11, scope: !4474)
!4474 = distinct !DILexicalBlock(scope: !4475, file: !1, line: 2271, column: 11)
!4475 = distinct !DILexicalBlock(scope: !4476, file: !1, line: 2271, column: 2)
!4476 = distinct !DILexicalBlock(scope: !507, file: !1, line: 2271, column: 2)
!4477 = !DILocation(line: 2272, column: 3, scope: !4474)
!4478 = !DILocation(line: 2274, column: 4, scope: !4479)
!4479 = distinct !DILexicalBlock(scope: !4474, file: !1, line: 2272, column: 18)
!4480 = !DILocation(line: 2275, column: 9, scope: !4481)
!4481 = distinct !DILexicalBlock(scope: !4482, file: !1, line: 2275, column: 9)
!4482 = distinct !DILexicalBlock(scope: !4483, file: !1, line: 2274, column: 13)
!4483 = distinct !DILexicalBlock(scope: !4484, file: !1, line: 2274, column: 4)
!4484 = distinct !DILexicalBlock(scope: !4479, file: !1, line: 2274, column: 4)
!4485 = !DILocation(line: 2275, column: 22, scope: !4481)
!4486 = !DILocation(line: 2275, column: 9, scope: !4482)
!4487 = !DILocation(line: 2278, column: 6, scope: !4488)
!4488 = distinct !DILexicalBlock(scope: !4481, file: !1, line: 2275, column: 28)
!4489 = !DILocation(line: 2278, column: 10, scope: !4488)
!4490 = !DILocation(line: 2278, column: 16, scope: !4488)
!4491 = !DILocation(line: 2279, column: 6, scope: !4488)
!4492 = !DILocation(line: 2279, column: 10, scope: !4488)
!4493 = !DILocation(line: 2279, column: 15, scope: !4488)
!4494 = !DILocation(line: 2280, column: 6, scope: !4488)
!4495 = !DILocation(line: 2280, column: 10, scope: !4488)
!4496 = !DILocation(line: 2280, column: 23, scope: !4488)
!4497 = !DILocation(line: 2281, column: 18, scope: !4488)
!4498 = !DILocation(line: 2281, column: 6, scope: !4488)
!4499 = !DILocation(line: 2281, column: 10, scope: !4488)
!4500 = !DILocation(line: 2281, column: 16, scope: !4488)
!4501 = !DILocation(line: 2282, column: 6, scope: !4488)
!4502 = !DILocation(line: 2282, column: 10, scope: !4488)
!4503 = !DILocation(line: 2282, column: 19, scope: !4488)
!4504 = !DILocation(line: 2283, column: 6, scope: !4488)
!4505 = !DILocation(line: 2293, column: 10, scope: !4506)
!4506 = distinct !DILexicalBlock(scope: !4482, file: !1, line: 2293, column: 9)
!4507 = !DILocation(line: 2293, column: 10, scope: !4508)
!4508 = !DILexicalBlockFile(scope: !4506, file: !1, discriminator: 1)
!4509 = !DILocation(line: 2293, column: 10, scope: !4510)
!4510 = !DILexicalBlockFile(scope: !4506, file: !1, discriminator: 2)
!4511 = !DILocation(line: 2293, column: 9, scope: !4510)
!4512 = !DILocation(line: 2295, column: 11, scope: !4513)
!4513 = distinct !DILexicalBlock(scope: !4514, file: !1, line: 2295, column: 10)
!4514 = distinct !DILexicalBlock(scope: !4506, file: !1, line: 2294, column: 23)
!4515 = !DILocation(line: 2295, column: 10, scope: !4514)
!4516 = !DILocation(line: 2296, column: 7, scope: !4513)
!4517 = !DILocation(line: 2302, column: 29, scope: !4514)
!4518 = !DILocation(line: 2303, column: 12, scope: !4514)
!4519 = !DILocation(line: 2302, column: 10, scope: !4514)
!4520 = !DILocation(line: 2302, column: 8, scope: !4514)
!4521 = !DILocation(line: 2305, column: 6, scope: !4514)
!4522 = !DILocation(line: 2306, column: 11, scope: !4523)
!4523 = distinct !DILexicalBlock(scope: !4514, file: !1, line: 2306, column: 10)
!4524 = !DILocation(line: 2306, column: 10, scope: !4514)
!4525 = !DILocation(line: 2307, column: 7, scope: !4523)
!4526 = !DILocation(line: 2308, column: 5, scope: !4514)
!4527 = !DILocation(line: 2309, column: 29, scope: !4528)
!4528 = distinct !DILexicalBlock(scope: !4506, file: !1, line: 2308, column: 12)
!4529 = !DILocation(line: 2310, column: 12, scope: !4528)
!4530 = !DILocation(line: 2309, column: 10, scope: !4528)
!4531 = !DILocation(line: 2309, column: 8, scope: !4528)
!4532 = !DILocation(line: 2311, column: 6, scope: !4528)
!4533 = !DILocation(line: 2313, column: 17, scope: !4482)
!4534 = !DILocation(line: 2314, column: 9, scope: !4535)
!4535 = distinct !DILexicalBlock(scope: !4482, file: !1, line: 2314, column: 9)
!4536 = !DILocation(line: 2314, column: 11, scope: !4535)
!4537 = !DILocation(line: 2314, column: 9, scope: !4482)
!4538 = !DILocation(line: 2316, column: 6, scope: !4535)
!4539 = !DILocation(line: 2322, column: 21, scope: !4482)
!4540 = !DILocation(line: 2322, column: 12, scope: !4482)
!4541 = !DILocation(line: 2322, column: 5, scope: !4482)
!4542 = !DILocation(line: 2322, column: 19, scope: !4482)
!4543 = !DILocation(line: 2323, column: 9, scope: !4544)
!4544 = distinct !DILexicalBlock(scope: !4482, file: !1, line: 2323, column: 9)
!4545 = !DILocation(line: 2323, column: 20, scope: !4544)
!4546 = !DILocation(line: 2323, column: 17, scope: !4544)
!4547 = !DILocation(line: 2323, column: 9, scope: !4482)
!4548 = !DILocation(line: 2324, column: 12, scope: !4549)
!4549 = distinct !DILexicalBlock(scope: !4544, file: !1, line: 2323, column: 28)
!4550 = !DILocation(line: 2325, column: 22, scope: !4549)
!4551 = !DILocation(line: 2325, column: 28, scope: !4549)
!4552 = !DILocation(line: 2325, column: 6, scope: !4549)
!4553 = !DILocation(line: 2326, column: 6, scope: !4549)
!4554 = !DILocation(line: 2274, column: 4, scope: !4555)
!4555 = !DILexicalBlockFile(scope: !4483, file: !1, discriminator: 1)
!4556 = !DILocation(line: 2332, column: 15, scope: !4479)
!4557 = !DILocation(line: 2332, column: 17, scope: !4479)
!4558 = !DILocation(line: 2332, column: 35, scope: !4479)
!4559 = !DILocation(line: 2332, column: 13, scope: !4479)
!4560 = !DILocation(line: 2332, column: 4, scope: !4479)
!4561 = !DILocation(line: 2338, column: 9, scope: !4562)
!4562 = distinct !DILexicalBlock(scope: !4479, file: !1, line: 2338, column: 8)
!4563 = !DILocation(line: 2338, column: 9, scope: !4564)
!4564 = !DILexicalBlockFile(scope: !4562, file: !1, discriminator: 1)
!4565 = !DILocation(line: 2338, column: 9, scope: !4566)
!4566 = !DILexicalBlockFile(scope: !4562, file: !1, discriminator: 2)
!4567 = !DILocation(line: 2338, column: 8, scope: !4566)
!4568 = !DILocation(line: 2339, column: 10, scope: !4569)
!4569 = distinct !DILexicalBlock(scope: !4570, file: !1, line: 2339, column: 9)
!4570 = distinct !DILexicalBlock(scope: !4562, file: !1, line: 2338, column: 53)
!4571 = !DILocation(line: 2339, column: 9, scope: !4570)
!4572 = !DILocation(line: 2340, column: 12, scope: !4573)
!4573 = distinct !DILexicalBlock(scope: !4569, file: !1, line: 2339, column: 16)
!4574 = !DILocation(line: 2341, column: 21, scope: !4573)
!4575 = !DILocation(line: 2341, column: 6, scope: !4573)
!4576 = !DILocation(line: 2341, column: 10, scope: !4573)
!4577 = !DILocation(line: 2341, column: 19, scope: !4573)
!4578 = !DILocation(line: 2342, column: 6, scope: !4573)
!4579 = !DILocation(line: 2344, column: 35, scope: !4570)
!4580 = !DILocation(line: 2345, column: 9, scope: !4570)
!4581 = !DILocation(line: 2344, column: 16, scope: !4570)
!4582 = !DILocation(line: 2344, column: 14, scope: !4570)
!4583 = !DILocation(line: 2346, column: 5, scope: !4570)
!4584 = !DILocation(line: 2347, column: 10, scope: !4585)
!4585 = distinct !DILexicalBlock(scope: !4570, file: !1, line: 2347, column: 9)
!4586 = !DILocation(line: 2347, column: 9, scope: !4570)
!4587 = !DILocation(line: 2348, column: 6, scope: !4585)
!4588 = !DILocation(line: 2349, column: 4, scope: !4570)
!4589 = !DILocation(line: 2350, column: 35, scope: !4590)
!4590 = distinct !DILexicalBlock(scope: !4562, file: !1, line: 2349, column: 11)
!4591 = !DILocation(line: 2351, column: 9, scope: !4590)
!4592 = !DILocation(line: 2350, column: 16, scope: !4590)
!4593 = !DILocation(line: 2350, column: 14, scope: !4590)
!4594 = !DILocation(line: 2352, column: 5, scope: !4590)
!4595 = !DILocation(line: 2338, column: 9, scope: !4596)
!4596 = !DILexicalBlockFile(scope: !4562, file: !1, discriminator: 3)
!4597 = !DILocation(line: 2356, column: 8, scope: !4598)
!4598 = distinct !DILexicalBlock(scope: !4479, file: !1, line: 2356, column: 8)
!4599 = !DILocation(line: 2356, column: 17, scope: !4598)
!4600 = !DILocation(line: 2356, column: 8, scope: !4479)
!4601 = !DILocalVariable(name: "p", scope: !4602, file: !1, line: 2359, type: !23)
!4602 = distinct !DILexicalBlock(scope: !4598, file: !1, line: 2356, column: 22)
!4603 = !DILocation(line: 2359, column: 9, scope: !4602)
!4604 = !DILocation(line: 2359, column: 13, scope: !4602)
!4605 = !DILocation(line: 2359, column: 22, scope: !4602)
!4606 = !DILocation(line: 2360, column: 10, scope: !4607)
!4607 = distinct !DILexicalBlock(scope: !4602, file: !1, line: 2360, column: 9)
!4608 = !DILocation(line: 2360, column: 10, scope: !4609)
!4609 = !DILexicalBlockFile(scope: !4607, file: !1, discriminator: 1)
!4610 = !DILocation(line: 2360, column: 10, scope: !4611)
!4611 = !DILexicalBlockFile(scope: !4607, file: !1, discriminator: 2)
!4612 = !DILocation(line: 2360, column: 9, scope: !4611)
!4613 = !DILocation(line: 2361, column: 10, scope: !4614)
!4614 = distinct !DILexicalBlock(scope: !4615, file: !1, line: 2361, column: 10)
!4615 = distinct !DILexicalBlock(scope: !4607, file: !1, line: 2360, column: 44)
!4616 = !DILocation(line: 2361, column: 10, scope: !4615)
!4617 = !DILocation(line: 2362, column: 7, scope: !4614)
!4618 = !DILocation(line: 2363, column: 12, scope: !4615)
!4619 = !DILocation(line: 2364, column: 21, scope: !4615)
!4620 = !DILocation(line: 2364, column: 6, scope: !4615)
!4621 = !DILocation(line: 2364, column: 10, scope: !4615)
!4622 = !DILocation(line: 2364, column: 19, scope: !4615)
!4623 = !DILocation(line: 2365, column: 21, scope: !4615)
!4624 = !DILocation(line: 2365, column: 6, scope: !4615)
!4625 = !DILocation(line: 2365, column: 10, scope: !4615)
!4626 = !DILocation(line: 2365, column: 19, scope: !4615)
!4627 = !DILocation(line: 2366, column: 6, scope: !4615)
!4628 = !DILocation(line: 2368, column: 22, scope: !4602)
!4629 = !DILocation(line: 2368, column: 19, scope: !4602)
!4630 = !DILocation(line: 2368, column: 27, scope: !4602)
!4631 = !DILocation(line: 2368, column: 25, scope: !4602)
!4632 = !DILocation(line: 2368, column: 14, scope: !4602)
!4633 = !DILocation(line: 2369, column: 5, scope: !4602)
!4634 = !DILocation(line: 2370, column: 4, scope: !4602)
!4635 = !DILocation(line: 2374, column: 16, scope: !4479)
!4636 = !DILocation(line: 2374, column: 24, scope: !4479)
!4637 = !DILocation(line: 2374, column: 22, scope: !4479)
!4638 = !DILocation(line: 2374, column: 33, scope: !4479)
!4639 = !DILocation(line: 2374, column: 40, scope: !4479)
!4640 = !DILocation(line: 2374, column: 38, scope: !4479)
!4641 = !DILocation(line: 2374, column: 13, scope: !4479)
!4642 = !DILocation(line: 2374, column: 4, scope: !4479)
!4643 = !DILocation(line: 2381, column: 4, scope: !4479)
!4644 = !DILocalVariable(name: "l", scope: !4645, file: !1, line: 2382, type: !23)
!4645 = distinct !DILexicalBlock(scope: !4646, file: !1, line: 2381, column: 13)
!4646 = distinct !DILexicalBlock(scope: !4647, file: !1, line: 2381, column: 4)
!4647 = distinct !DILexicalBlock(scope: !4479, file: !1, line: 2381, column: 4)
!4648 = !DILocation(line: 2382, column: 9, scope: !4645)
!4649 = !DILocation(line: 2384, column: 9, scope: !4645)
!4650 = !DILocation(line: 2384, column: 7, scope: !4645)
!4651 = !DILocation(line: 2385, column: 9, scope: !4652)
!4652 = distinct !DILexicalBlock(scope: !4645, file: !1, line: 2385, column: 9)
!4653 = !DILocation(line: 2385, column: 20, scope: !4652)
!4654 = !DILocation(line: 2385, column: 18, scope: !4652)
!4655 = !DILocation(line: 2385, column: 9, scope: !4645)
!4656 = !DILocation(line: 2386, column: 10, scope: !4657)
!4657 = distinct !DILexicalBlock(scope: !4658, file: !1, line: 2386, column: 10)
!4658 = distinct !DILexicalBlock(scope: !4652, file: !1, line: 2385, column: 27)
!4659 = !DILocation(line: 2386, column: 14, scope: !4657)
!4660 = !DILocation(line: 2386, column: 23, scope: !4657)
!4661 = !DILocation(line: 2386, column: 21, scope: !4657)
!4662 = !DILocation(line: 2386, column: 12, scope: !4657)
!4663 = !DILocation(line: 2386, column: 10, scope: !4658)
!4664 = !DILocation(line: 2387, column: 11, scope: !4657)
!4665 = !DILocation(line: 2387, column: 20, scope: !4657)
!4666 = !DILocation(line: 2387, column: 18, scope: !4657)
!4667 = !DILocation(line: 2387, column: 9, scope: !4657)
!4668 = !DILocation(line: 2387, column: 7, scope: !4657)
!4669 = !DILocation(line: 2388, column: 5, scope: !4658)
!4670 = !DILocation(line: 2389, column: 10, scope: !4671)
!4671 = distinct !DILexicalBlock(scope: !4672, file: !1, line: 2389, column: 10)
!4672 = distinct !DILexicalBlock(scope: !4652, file: !1, line: 2388, column: 12)
!4673 = !DILocation(line: 2389, column: 14, scope: !4671)
!4674 = !DILocation(line: 2389, column: 23, scope: !4671)
!4675 = !DILocation(line: 2389, column: 21, scope: !4671)
!4676 = !DILocation(line: 2389, column: 12, scope: !4671)
!4677 = !DILocation(line: 2389, column: 10, scope: !4672)
!4678 = !DILocation(line: 2390, column: 11, scope: !4671)
!4679 = !DILocation(line: 2390, column: 20, scope: !4671)
!4680 = !DILocation(line: 2390, column: 18, scope: !4671)
!4681 = !DILocation(line: 2390, column: 9, scope: !4671)
!4682 = !DILocation(line: 2390, column: 7, scope: !4671)
!4683 = !DILocation(line: 2392, column: 10, scope: !4684)
!4684 = distinct !DILexicalBlock(scope: !4645, file: !1, line: 2392, column: 9)
!4685 = !DILocation(line: 2392, column: 21, scope: !4684)
!4686 = !DILocation(line: 2392, column: 19, scope: !4684)
!4687 = !DILocation(line: 2392, column: 25, scope: !4684)
!4688 = !DILocation(line: 2392, column: 23, scope: !4684)
!4689 = !DILocation(line: 2393, column: 9, scope: !4684)
!4690 = !DILocation(line: 2393, column: 13, scope: !4691)
!4691 = !DILexicalBlockFile(scope: !4684, file: !1, discriminator: 1)
!4692 = !DILocation(line: 2393, column: 21, scope: !4691)
!4693 = !DILocation(line: 2393, column: 19, scope: !4691)
!4694 = !DILocation(line: 2393, column: 25, scope: !4691)
!4695 = !DILocation(line: 2393, column: 23, scope: !4691)
!4696 = !DILocation(line: 2392, column: 9, scope: !4697)
!4697 = !DILexicalBlockFile(scope: !4645, file: !1, discriminator: 1)
!4698 = !DILocation(line: 2395, column: 13, scope: !4699)
!4699 = distinct !DILexicalBlock(scope: !4684, file: !1, line: 2393, column: 36)
!4700 = !DILocation(line: 2395, column: 22, scope: !4699)
!4701 = !DILocation(line: 2395, column: 20, scope: !4699)
!4702 = !DILocation(line: 2396, column: 10, scope: !4699)
!4703 = !DILocation(line: 2396, column: 19, scope: !4699)
!4704 = !DILocation(line: 2396, column: 17, scope: !4699)
!4705 = !DILocation(line: 2396, column: 29, scope: !4699)
!4706 = !DILocation(line: 2395, column: 6, scope: !4699)
!4707 = !DILocation(line: 2397, column: 5, scope: !4699)
!4708 = !DILocalVariable(name: "s", scope: !4709, file: !1, line: 2398, type: !356)
!4709 = distinct !DILexicalBlock(scope: !4684, file: !1, line: 2397, column: 12)
!4710 = !DILocation(line: 2398, column: 27, scope: !4709)
!4711 = !DILocalVariable(name: "d", scope: !4709, file: !1, line: 2399, type: !371)
!4712 = !DILocation(line: 2399, column: 21, scope: !4709)
!4713 = !DILocalVariable(name: "li", scope: !4709, file: !1, line: 2400, type: !23)
!4714 = !DILocation(line: 2400, column: 10, scope: !4709)
!4715 = !DILocation(line: 2402, column: 10, scope: !4709)
!4716 = !DILocation(line: 2402, column: 19, scope: !4709)
!4717 = !DILocation(line: 2402, column: 17, scope: !4709)
!4718 = !DILocation(line: 2402, column: 8, scope: !4709)
!4719 = !DILocation(line: 2403, column: 10, scope: !4709)
!4720 = !DILocation(line: 2403, column: 19, scope: !4709)
!4721 = !DILocation(line: 2403, column: 17, scope: !4709)
!4722 = !DILocation(line: 2403, column: 8, scope: !4709)
!4723 = !DILocation(line: 2404, column: 14, scope: !4724)
!4724 = distinct !DILexicalBlock(scope: !4709, file: !1, line: 2404, column: 6)
!4725 = !DILocation(line: 2404, column: 11, scope: !4724)
!4726 = !DILocation(line: 2404, column: 19, scope: !4727)
!4727 = !DILexicalBlockFile(scope: !4728, file: !1, discriminator: 1)
!4728 = distinct !DILexicalBlock(scope: !4724, file: !1, line: 2404, column: 6)
!4729 = !DILocation(line: 2404, column: 24, scope: !4727)
!4730 = !DILocation(line: 2404, column: 25, scope: !4727)
!4731 = !DILocation(line: 2404, column: 22, scope: !4727)
!4732 = !DILocation(line: 2404, column: 6, scope: !4727)
!4733 = !DILocation(line: 2405, column: 17, scope: !4734)
!4734 = distinct !DILexicalBlock(scope: !4728, file: !1, line: 2404, column: 30)
!4735 = !DILocation(line: 2405, column: 15, scope: !4734)
!4736 = !DILocation(line: 2405, column: 9, scope: !4734)
!4737 = !DILocation(line: 2405, column: 7, scope: !4734)
!4738 = !DILocation(line: 2405, column: 13, scope: !4734)
!4739 = !DILocation(line: 2405, column: 23, scope: !4734)
!4740 = !DILocation(line: 2406, column: 17, scope: !4734)
!4741 = !DILocation(line: 2406, column: 15, scope: !4734)
!4742 = !DILocation(line: 2406, column: 9, scope: !4734)
!4743 = !DILocation(line: 2406, column: 7, scope: !4734)
!4744 = !DILocation(line: 2406, column: 13, scope: !4734)
!4745 = !DILocation(line: 2406, column: 23, scope: !4734)
!4746 = !DILocation(line: 2404, column: 6, scope: !4747)
!4747 = !DILexicalBlockFile(scope: !4728, file: !1, discriminator: 2)
!4748 = !DILocation(line: 2408, column: 10, scope: !4749)
!4749 = distinct !DILexicalBlock(scope: !4709, file: !1, line: 2408, column: 10)
!4750 = !DILocation(line: 2408, column: 15, scope: !4749)
!4751 = !DILocation(line: 2408, column: 13, scope: !4749)
!4752 = !DILocation(line: 2408, column: 10, scope: !4709)
!4753 = !DILocation(line: 2409, column: 17, scope: !4749)
!4754 = !DILocation(line: 2409, column: 15, scope: !4749)
!4755 = !DILocation(line: 2409, column: 9, scope: !4749)
!4756 = !DILocation(line: 2409, column: 7, scope: !4749)
!4757 = !DILocation(line: 2409, column: 13, scope: !4749)
!4758 = !DILocation(line: 2411, column: 14, scope: !4645)
!4759 = !DILocation(line: 2411, column: 11, scope: !4645)
!4760 = !DILocation(line: 2412, column: 9, scope: !4761)
!4761 = distinct !DILexicalBlock(scope: !4645, file: !1, line: 2412, column: 9)
!4762 = !DILocation(line: 2412, column: 18, scope: !4761)
!4763 = !DILocation(line: 2412, column: 15, scope: !4761)
!4764 = !DILocation(line: 2412, column: 9, scope: !4645)
!4765 = !DILocation(line: 2413, column: 12, scope: !4766)
!4766 = distinct !DILexicalBlock(scope: !4761, file: !1, line: 2412, column: 26)
!4767 = !DILocation(line: 2414, column: 22, scope: !4766)
!4768 = !DILocation(line: 2414, column: 28, scope: !4766)
!4769 = !DILocation(line: 2414, column: 6, scope: !4766)
!4770 = !DILocation(line: 2415, column: 10, scope: !4771)
!4771 = distinct !DILexicalBlock(scope: !4766, file: !1, line: 2415, column: 10)
!4772 = !DILocation(line: 2415, column: 22, scope: !4771)
!4773 = !DILocation(line: 2415, column: 19, scope: !4771)
!4774 = !DILocation(line: 2415, column: 10, scope: !4766)
!4775 = !DILocation(line: 2416, column: 13, scope: !4771)
!4776 = !DILocation(line: 2416, column: 7, scope: !4771)
!4777 = !DILocation(line: 2418, column: 13, scope: !4778)
!4778 = distinct !DILexicalBlock(scope: !4771, file: !1, line: 2417, column: 11)
!4779 = !DILocation(line: 2419, column: 22, scope: !4778)
!4780 = !DILocation(line: 2419, column: 33, scope: !4778)
!4781 = !DILocation(line: 2419, column: 31, scope: !4778)
!4782 = !DILocation(line: 2419, column: 7, scope: !4778)
!4783 = !DILocation(line: 2419, column: 11, scope: !4778)
!4784 = !DILocation(line: 2419, column: 20, scope: !4778)
!4785 = !DILocation(line: 2421, column: 12, scope: !4778)
!4786 = !DILocation(line: 2421, column: 23, scope: !4778)
!4787 = !DILocation(line: 2421, column: 21, scope: !4778)
!4788 = !DILocation(line: 2421, column: 28, scope: !4778)
!4789 = !DILocation(line: 2421, column: 26, scope: !4778)
!4790 = !DILocation(line: 2420, column: 7, scope: !4778)
!4791 = !DILocation(line: 2420, column: 11, scope: !4778)
!4792 = !DILocation(line: 2420, column: 20, scope: !4778)
!4793 = !DILocation(line: 2423, column: 6, scope: !4766)
!4794 = !DILocation(line: 2425, column: 9, scope: !4795)
!4795 = distinct !DILexicalBlock(scope: !4645, file: !1, line: 2425, column: 9)
!4796 = !DILocation(line: 2425, column: 21, scope: !4795)
!4797 = !DILocation(line: 2425, column: 18, scope: !4795)
!4798 = !DILocation(line: 2425, column: 9, scope: !4645)
!4799 = !DILocation(line: 2427, column: 6, scope: !4795)
!4800 = !DILocation(line: 2428, column: 17, scope: !4645)
!4801 = !DILocation(line: 2428, column: 14, scope: !4645)
!4802 = !DILocation(line: 2429, column: 17, scope: !4645)
!4803 = !DILocation(line: 2429, column: 28, scope: !4645)
!4804 = !DILocation(line: 2429, column: 26, scope: !4645)
!4805 = !DILocation(line: 2429, column: 33, scope: !4645)
!4806 = !DILocation(line: 2429, column: 31, scope: !4645)
!4807 = !DILocation(line: 2429, column: 14, scope: !4645)
!4808 = !DILocation(line: 2381, column: 4, scope: !4809)
!4809 = !DILexicalBlockFile(scope: !4646, file: !1, discriminator: 1)
!4810 = !DILocation(line: 2431, column: 10, scope: !4479)
!4811 = !DILocation(line: 2432, column: 4, scope: !4479)
!4812 = !DILocation(line: 2271, column: 2, scope: !4813)
!4813 = !DILexicalBlockFile(scope: !4475, file: !1, discriminator: 1)
!4814 = !DILocation(line: 2436, column: 10, scope: !507)
!4815 = !DILocation(line: 2436, column: 14, scope: !507)
!4816 = !DILocation(line: 2436, column: 20, scope: !507)
!4817 = !DILocation(line: 2436, column: 2, scope: !507)
!4818 = !DILocation(line: 2438, column: 2, scope: !507)
!4819 = !DILocation(line: 2438, column: 6, scope: !507)
!4820 = !DILocation(line: 2438, column: 11, scope: !507)
!4821 = !DILocation(line: 2439, column: 21, scope: !507)
!4822 = !DILocation(line: 2439, column: 2, scope: !507)
!4823 = !DILocation(line: 2439, column: 6, scope: !507)
!4824 = !DILocation(line: 2439, column: 19, scope: !507)
!4825 = !DILocation(line: 2440, column: 14, scope: !507)
!4826 = !DILocation(line: 2440, column: 2, scope: !507)
!4827 = !DILocation(line: 2440, column: 6, scope: !507)
!4828 = !DILocation(line: 2440, column: 12, scope: !507)
!4829 = !DILocation(line: 2441, column: 14, scope: !507)
!4830 = !DILocation(line: 2441, column: 2, scope: !507)
!4831 = !DILocation(line: 2441, column: 6, scope: !507)
!4832 = !DILocation(line: 2441, column: 12, scope: !507)
!4833 = !DILocation(line: 2442, column: 2, scope: !507)
!4834 = !DILocation(line: 2443, column: 1, scope: !507)
!4835 = !DILocalVariable(name: "strm", arg: 1, scope: !485, file: !1, line: 1885, type: !476)
!4836 = !DILocation(line: 1885, column: 34, scope: !485)
!4837 = !DILocalVariable(name: "br", arg: 2, scope: !485, file: !1, line: 1885, type: !488)
!4838 = !DILocation(line: 1885, column: 55, scope: !485)
!4839 = !DILocalVariable(name: "n", scope: !485, file: !1, line: 1887, type: !23)
!4840 = !DILocation(line: 1887, column: 6, scope: !485)
!4841 = !DILocation(line: 1887, column: 23, scope: !485)
!4842 = !DILocation(line: 1887, column: 27, scope: !485)
!4843 = !DILocation(line: 1887, column: 21, scope: !485)
!4844 = !DILocation(line: 1887, column: 10, scope: !485)
!4845 = !DILocation(line: 1889, column: 2, scope: !485)
!4846 = !DILocalVariable(name: "x", scope: !4847, file: !1, line: 1890, type: !4850)
!4847 = distinct !DILexicalBlock(scope: !4848, file: !1, line: 1889, column: 11)
!4848 = distinct !DILexicalBlock(scope: !4849, file: !1, line: 1889, column: 2)
!4849 = distinct !DILexicalBlock(scope: !485, file: !1, line: 1889, column: 2)
!4850 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !23)
!4851 = !DILocation(line: 1890, column: 13, scope: !4847)
!4852 = !DILocation(line: 1890, column: 17, scope: !4847)
!4853 = !DILocation(line: 1890, column: 19, scope: !4847)
!4854 = !DILocation(line: 1891, column: 7, scope: !4855)
!4855 = distinct !DILexicalBlock(scope: !4847, file: !1, line: 1891, column: 7)
!4856 = !DILocation(line: 1891, column: 13, scope: !4855)
!4857 = !DILocation(line: 1891, column: 25, scope: !4855)
!4858 = !DILocation(line: 1891, column: 22, scope: !4855)
!4859 = !DILocation(line: 1891, column: 7, scope: !4847)
!4860 = !DILocation(line: 1892, column: 12, scope: !4861)
!4861 = distinct !DILexicalBlock(scope: !4855, file: !1, line: 1891, column: 28)
!4862 = !DILocation(line: 1892, column: 4, scope: !4861)
!4863 = !DILocation(line: 1895, column: 20, scope: !4864)
!4864 = distinct !DILexicalBlock(scope: !4861, file: !1, line: 1892, column: 15)
!4865 = !DILocation(line: 1895, column: 26, scope: !4864)
!4866 = !DILocation(line: 1895, column: 10, scope: !4864)
!4867 = !DILocation(line: 1895, column: 38, scope: !4864)
!4868 = !DILocation(line: 1896, column: 20, scope: !4864)
!4869 = !DILocation(line: 1896, column: 26, scope: !4864)
!4870 = !DILocation(line: 1896, column: 10, scope: !4864)
!4871 = !DILocation(line: 1896, column: 38, scope: !4864)
!4872 = !DILocation(line: 1895, column: 44, scope: !4864)
!4873 = !DILocation(line: 1897, column: 20, scope: !4864)
!4874 = !DILocation(line: 1897, column: 26, scope: !4864)
!4875 = !DILocation(line: 1897, column: 10, scope: !4864)
!4876 = !DILocation(line: 1897, column: 38, scope: !4864)
!4877 = !DILocation(line: 1896, column: 44, scope: !4864)
!4878 = !DILocation(line: 1898, column: 20, scope: !4864)
!4879 = !DILocation(line: 1898, column: 26, scope: !4864)
!4880 = !DILocation(line: 1898, column: 10, scope: !4864)
!4881 = !DILocation(line: 1898, column: 38, scope: !4864)
!4882 = !DILocation(line: 1897, column: 44, scope: !4864)
!4883 = !DILocation(line: 1899, column: 20, scope: !4864)
!4884 = !DILocation(line: 1899, column: 26, scope: !4864)
!4885 = !DILocation(line: 1899, column: 10, scope: !4864)
!4886 = !DILocation(line: 1899, column: 38, scope: !4864)
!4887 = !DILocation(line: 1899, column: 9, scope: !4864)
!4888 = !DILocation(line: 1898, column: 44, scope: !4864)
!4889 = !DILocation(line: 1900, column: 20, scope: !4864)
!4890 = !DILocation(line: 1900, column: 26, scope: !4864)
!4891 = !DILocation(line: 1900, column: 10, scope: !4864)
!4892 = !DILocation(line: 1900, column: 38, scope: !4864)
!4893 = !DILocation(line: 1900, column: 9, scope: !4864)
!4894 = !DILocation(line: 1899, column: 44, scope: !4864)
!4895 = !DILocation(line: 1901, column: 20, scope: !4864)
!4896 = !DILocation(line: 1901, column: 26, scope: !4864)
!4897 = !DILocation(line: 1901, column: 10, scope: !4864)
!4898 = !DILocation(line: 1901, column: 38, scope: !4864)
!4899 = !DILocation(line: 1901, column: 9, scope: !4864)
!4900 = !DILocation(line: 1900, column: 44, scope: !4864)
!4901 = !DILocation(line: 1902, column: 20, scope: !4864)
!4902 = !DILocation(line: 1902, column: 26, scope: !4864)
!4903 = !DILocation(line: 1902, column: 10, scope: !4864)
!4904 = !DILocation(line: 1901, column: 43, scope: !4864)
!4905 = !DILocation(line: 1894, column: 5, scope: !4864)
!4906 = !DILocation(line: 1894, column: 9, scope: !4864)
!4907 = !DILocation(line: 1894, column: 22, scope: !4864)
!4908 = !DILocation(line: 1903, column: 5, scope: !4864)
!4909 = !DILocation(line: 1903, column: 11, scope: !4864)
!4910 = !DILocation(line: 1903, column: 19, scope: !4864)
!4911 = !DILocation(line: 1904, column: 5, scope: !4864)
!4912 = !DILocation(line: 1904, column: 11, scope: !4864)
!4913 = !DILocation(line: 1904, column: 20, scope: !4864)
!4914 = !DILocation(line: 1905, column: 5, scope: !4864)
!4915 = !DILocation(line: 1905, column: 9, scope: !4864)
!4916 = !DILocation(line: 1905, column: 21, scope: !4864)
!4917 = !DILocation(line: 1906, column: 5, scope: !4864)
!4918 = !DILocation(line: 1909, column: 10, scope: !4864)
!4919 = !DILocation(line: 1909, column: 14, scope: !4864)
!4920 = !DILocation(line: 1909, column: 27, scope: !4864)
!4921 = !DILocation(line: 1910, column: 20, scope: !4864)
!4922 = !DILocation(line: 1910, column: 26, scope: !4864)
!4923 = !DILocation(line: 1910, column: 10, scope: !4864)
!4924 = !DILocation(line: 1910, column: 38, scope: !4864)
!4925 = !DILocation(line: 1909, column: 34, scope: !4864)
!4926 = !DILocation(line: 1911, column: 20, scope: !4864)
!4927 = !DILocation(line: 1911, column: 26, scope: !4864)
!4928 = !DILocation(line: 1911, column: 10, scope: !4864)
!4929 = !DILocation(line: 1911, column: 38, scope: !4864)
!4930 = !DILocation(line: 1910, column: 44, scope: !4864)
!4931 = !DILocation(line: 1912, column: 20, scope: !4864)
!4932 = !DILocation(line: 1912, column: 26, scope: !4864)
!4933 = !DILocation(line: 1912, column: 10, scope: !4864)
!4934 = !DILocation(line: 1912, column: 38, scope: !4864)
!4935 = !DILocation(line: 1911, column: 44, scope: !4864)
!4936 = !DILocation(line: 1913, column: 20, scope: !4864)
!4937 = !DILocation(line: 1913, column: 26, scope: !4864)
!4938 = !DILocation(line: 1913, column: 10, scope: !4864)
!4939 = !DILocation(line: 1913, column: 38, scope: !4864)
!4940 = !DILocation(line: 1913, column: 9, scope: !4864)
!4941 = !DILocation(line: 1912, column: 44, scope: !4864)
!4942 = !DILocation(line: 1914, column: 20, scope: !4864)
!4943 = !DILocation(line: 1914, column: 26, scope: !4864)
!4944 = !DILocation(line: 1914, column: 10, scope: !4864)
!4945 = !DILocation(line: 1914, column: 38, scope: !4864)
!4946 = !DILocation(line: 1914, column: 9, scope: !4864)
!4947 = !DILocation(line: 1913, column: 44, scope: !4864)
!4948 = !DILocation(line: 1915, column: 20, scope: !4864)
!4949 = !DILocation(line: 1915, column: 26, scope: !4864)
!4950 = !DILocation(line: 1915, column: 10, scope: !4864)
!4951 = !DILocation(line: 1915, column: 38, scope: !4864)
!4952 = !DILocation(line: 1915, column: 9, scope: !4864)
!4953 = !DILocation(line: 1914, column: 44, scope: !4864)
!4954 = !DILocation(line: 1916, column: 20, scope: !4864)
!4955 = !DILocation(line: 1916, column: 26, scope: !4864)
!4956 = !DILocation(line: 1916, column: 10, scope: !4864)
!4957 = !DILocation(line: 1915, column: 43, scope: !4864)
!4958 = !DILocation(line: 1908, column: 5, scope: !4864)
!4959 = !DILocation(line: 1908, column: 9, scope: !4864)
!4960 = !DILocation(line: 1908, column: 22, scope: !4864)
!4961 = !DILocation(line: 1917, column: 5, scope: !4864)
!4962 = !DILocation(line: 1917, column: 11, scope: !4864)
!4963 = !DILocation(line: 1917, column: 19, scope: !4864)
!4964 = !DILocation(line: 1918, column: 5, scope: !4864)
!4965 = !DILocation(line: 1918, column: 11, scope: !4864)
!4966 = !DILocation(line: 1918, column: 20, scope: !4864)
!4967 = !DILocation(line: 1919, column: 5, scope: !4864)
!4968 = !DILocation(line: 1919, column: 9, scope: !4864)
!4969 = !DILocation(line: 1919, column: 21, scope: !4864)
!4970 = !DILocation(line: 1920, column: 5, scope: !4864)
!4971 = !DILocation(line: 1923, column: 10, scope: !4864)
!4972 = !DILocation(line: 1923, column: 14, scope: !4864)
!4973 = !DILocation(line: 1923, column: 27, scope: !4864)
!4974 = !DILocation(line: 1924, column: 20, scope: !4864)
!4975 = !DILocation(line: 1924, column: 26, scope: !4864)
!4976 = !DILocation(line: 1924, column: 10, scope: !4864)
!4977 = !DILocation(line: 1924, column: 38, scope: !4864)
!4978 = !DILocation(line: 1923, column: 34, scope: !4864)
!4979 = !DILocation(line: 1925, column: 20, scope: !4864)
!4980 = !DILocation(line: 1925, column: 26, scope: !4864)
!4981 = !DILocation(line: 1925, column: 10, scope: !4864)
!4982 = !DILocation(line: 1925, column: 38, scope: !4864)
!4983 = !DILocation(line: 1924, column: 44, scope: !4864)
!4984 = !DILocation(line: 1926, column: 20, scope: !4864)
!4985 = !DILocation(line: 1926, column: 26, scope: !4864)
!4986 = !DILocation(line: 1926, column: 10, scope: !4864)
!4987 = !DILocation(line: 1926, column: 38, scope: !4864)
!4988 = !DILocation(line: 1926, column: 9, scope: !4864)
!4989 = !DILocation(line: 1925, column: 44, scope: !4864)
!4990 = !DILocation(line: 1927, column: 20, scope: !4864)
!4991 = !DILocation(line: 1927, column: 26, scope: !4864)
!4992 = !DILocation(line: 1927, column: 10, scope: !4864)
!4993 = !DILocation(line: 1927, column: 38, scope: !4864)
!4994 = !DILocation(line: 1927, column: 9, scope: !4864)
!4995 = !DILocation(line: 1926, column: 44, scope: !4864)
!4996 = !DILocation(line: 1928, column: 20, scope: !4864)
!4997 = !DILocation(line: 1928, column: 26, scope: !4864)
!4998 = !DILocation(line: 1928, column: 10, scope: !4864)
!4999 = !DILocation(line: 1928, column: 38, scope: !4864)
!5000 = !DILocation(line: 1928, column: 9, scope: !4864)
!5001 = !DILocation(line: 1927, column: 44, scope: !4864)
!5002 = !DILocation(line: 1929, column: 20, scope: !4864)
!5003 = !DILocation(line: 1929, column: 26, scope: !4864)
!5004 = !DILocation(line: 1929, column: 10, scope: !4864)
!5005 = !DILocation(line: 1928, column: 43, scope: !4864)
!5006 = !DILocation(line: 1922, column: 5, scope: !4864)
!5007 = !DILocation(line: 1922, column: 9, scope: !4864)
!5008 = !DILocation(line: 1922, column: 22, scope: !4864)
!5009 = !DILocation(line: 1930, column: 5, scope: !4864)
!5010 = !DILocation(line: 1930, column: 11, scope: !4864)
!5011 = !DILocation(line: 1930, column: 19, scope: !4864)
!5012 = !DILocation(line: 1931, column: 5, scope: !4864)
!5013 = !DILocation(line: 1931, column: 11, scope: !4864)
!5014 = !DILocation(line: 1931, column: 20, scope: !4864)
!5015 = !DILocation(line: 1932, column: 5, scope: !4864)
!5016 = !DILocation(line: 1932, column: 9, scope: !4864)
!5017 = !DILocation(line: 1932, column: 21, scope: !4864)
!5018 = !DILocation(line: 1933, column: 5, scope: !4864)
!5019 = !DILocation(line: 1937, column: 5, scope: !4864)
!5020 = !DILocation(line: 1939, column: 5, scope: !4864)
!5021 = !DILocation(line: 1941, column: 3, scope: !4861)
!5022 = !DILocation(line: 1942, column: 7, scope: !5023)
!5023 = distinct !DILexicalBlock(scope: !4847, file: !1, line: 1942, column: 7)
!5024 = !DILocation(line: 1942, column: 13, scope: !5023)
!5025 = !DILocation(line: 1942, column: 22, scope: !5023)
!5026 = !DILocation(line: 1942, column: 7, scope: !4847)
!5027 = !DILocation(line: 1945, column: 4, scope: !5028)
!5028 = distinct !DILexicalBlock(scope: !5023, file: !1, line: 1942, column: 28)
!5029 = !DILocation(line: 1948, column: 7, scope: !4847)
!5030 = !DILocation(line: 1948, column: 11, scope: !4847)
!5031 = !DILocation(line: 1948, column: 24, scope: !4847)
!5032 = !DILocation(line: 1948, column: 33, scope: !4847)
!5033 = !DILocation(line: 1948, column: 39, scope: !4847)
!5034 = !DILocation(line: 1948, column: 46, scope: !4847)
!5035 = !DILocation(line: 1948, column: 32, scope: !4847)
!5036 = !DILocation(line: 1948, column: 30, scope: !4847)
!5037 = !DILocation(line: 1947, column: 3, scope: !4847)
!5038 = !DILocation(line: 1947, column: 7, scope: !4847)
!5039 = !DILocation(line: 1947, column: 20, scope: !4847)
!5040 = !DILocation(line: 1949, column: 3, scope: !4847)
!5041 = !DILocation(line: 1949, column: 9, scope: !4847)
!5042 = !DILocation(line: 1949, column: 17, scope: !4847)
!5043 = !DILocation(line: 1950, column: 3, scope: !4847)
!5044 = !DILocation(line: 1950, column: 7, scope: !4847)
!5045 = !DILocation(line: 1950, column: 19, scope: !4847)
!5046 = !DILocation(line: 1951, column: 5, scope: !4847)
!5047 = !DILocation(line: 1889, column: 2, scope: !5048)
!5048 = !DILexicalBlockFile(scope: !4848, file: !1, discriminator: 1)
!5049 = !DILocation(line: 1953, column: 1, scope: !485)
!5050 = !DILocalVariable(name: "strm", arg: 1, scope: !489, file: !1, line: 2013, type: !476)
!5051 = !DILocation(line: 2013, column: 36, scope: !489)
!5052 = !DILocalVariable(name: "s", arg: 2, scope: !489, file: !1, line: 2013, type: !45)
!5053 = !DILocation(line: 2013, column: 49, scope: !489)
!5054 = !DILocation(line: 2015, column: 18, scope: !489)
!5055 = !DILocation(line: 2015, column: 24, scope: !489)
!5056 = !DILocation(line: 2015, column: 28, scope: !489)
!5057 = !DILocation(line: 2015, column: 2, scope: !489)
!5058 = !DILocation(line: 2015, column: 8, scope: !489)
!5059 = !DILocation(line: 2015, column: 16, scope: !489)
!5060 = !DILocation(line: 2016, column: 25, scope: !489)
!5061 = !DILocation(line: 2016, column: 20, scope: !489)
!5062 = !DILocation(line: 2016, column: 2, scope: !489)
!5063 = !DILocation(line: 2016, column: 8, scope: !489)
!5064 = !DILocation(line: 2016, column: 18, scope: !489)
!5065 = !DILocation(line: 2017, column: 21, scope: !489)
!5066 = !DILocation(line: 2017, column: 2, scope: !489)
!5067 = !DILocation(line: 2017, column: 8, scope: !489)
!5068 = !DILocation(line: 2017, column: 18, scope: !489)
!5069 = !DILocation(line: 2018, column: 1, scope: !489)
!5070 = !DILocalVariable(name: "hf", arg: 1, scope: !492, file: !1, line: 2588, type: !480)
!5071 = !DILocation(line: 2588, column: 37, scope: !492)
!5072 = !DILocalVariable(name: "c", arg: 2, scope: !492, file: !1, line: 2588, type: !299)
!5073 = !DILocation(line: 2588, column: 50, scope: !492)
!5074 = !DILocation(line: 2590, column: 6, scope: !5075)
!5075 = distinct !DILexicalBlock(scope: !492, file: !1, line: 2590, column: 6)
!5076 = !DILocation(line: 2590, column: 11, scope: !5075)
!5077 = !DILocation(line: 2590, column: 15, scope: !5075)
!5078 = !DILocation(line: 2590, column: 8, scope: !5075)
!5079 = !DILocation(line: 2590, column: 6, scope: !492)
!5080 = !DILocation(line: 2591, column: 3, scope: !5075)
!5081 = !DILocation(line: 2592, column: 15, scope: !492)
!5082 = !DILocation(line: 2592, column: 2, scope: !492)
!5083 = !DILocation(line: 2592, column: 6, scope: !492)
!5084 = !DILocation(line: 2592, column: 13, scope: !492)
!5085 = !DILocation(line: 2593, column: 2, scope: !492)
!5086 = !DILocation(line: 2593, column: 6, scope: !492)
!5087 = !DILocation(line: 2593, column: 15, scope: !492)
!5088 = !DILocation(line: 2594, column: 2, scope: !492)
!5089 = !DILocation(line: 2594, column: 6, scope: !492)
!5090 = !DILocation(line: 2594, column: 17, scope: !492)
!5091 = !DILocation(line: 2595, column: 13, scope: !492)
!5092 = !DILocation(line: 2595, column: 17, scope: !492)
!5093 = !DILocation(line: 2595, column: 2, scope: !492)
!5094 = !DILocation(line: 2595, column: 6, scope: !492)
!5095 = !DILocation(line: 2595, column: 25, scope: !492)
!5096 = !DILocation(line: 2596, column: 2, scope: !492)
!5097 = !DILocation(line: 2597, column: 1, scope: !492)
!5098 = !DILocalVariable(name: "strm", arg: 1, scope: !495, file: !1, line: 2550, type: !476)
!5099 = !DILocation(line: 2550, column: 39, scope: !495)
!5100 = !DILocalVariable(name: "start", arg: 2, scope: !495, file: !1, line: 2550, type: !23)
!5101 = !DILocation(line: 2550, column: 49, scope: !495)
!5102 = !DILocalVariable(name: "end", arg: 3, scope: !495, file: !1, line: 2550, type: !23)
!5103 = !DILocation(line: 2550, column: 60, scope: !495)
!5104 = !DILocalVariable(name: "ds", scope: !495, file: !1, line: 2552, type: !364)
!5105 = !DILocation(line: 2552, column: 18, scope: !495)
!5106 = !DILocation(line: 2552, column: 23, scope: !495)
!5107 = !DILocation(line: 2552, column: 29, scope: !495)
!5108 = !DILocalVariable(name: "br", scope: !495, file: !1, line: 2553, type: !488)
!5109 = !DILocation(line: 2553, column: 17, scope: !495)
!5110 = !DILocation(line: 2553, column: 24, scope: !495)
!5111 = !DILocation(line: 2553, column: 28, scope: !495)
!5112 = !DILocalVariable(name: "c", scope: !495, file: !1, line: 2554, type: !23)
!5113 = !DILocation(line: 2554, column: 6, scope: !495)
!5114 = !DILocalVariable(name: "i", scope: !495, file: !1, line: 2554, type: !23)
!5115 = !DILocation(line: 2554, column: 9, scope: !495)
!5116 = !DILocation(line: 2556, column: 11, scope: !5117)
!5117 = distinct !DILexicalBlock(scope: !495, file: !1, line: 2556, column: 2)
!5118 = !DILocation(line: 2556, column: 9, scope: !5117)
!5119 = !DILocation(line: 2556, column: 7, scope: !5117)
!5120 = !DILocation(line: 2556, column: 18, scope: !5121)
!5121 = !DILexicalBlockFile(scope: !5122, file: !1, discriminator: 1)
!5122 = distinct !DILexicalBlock(scope: !5117, file: !1, line: 2556, column: 2)
!5123 = !DILocation(line: 2556, column: 22, scope: !5121)
!5124 = !DILocation(line: 2556, column: 20, scope: !5121)
!5125 = !DILocation(line: 2556, column: 2, scope: !5121)
!5126 = !DILocation(line: 2569, column: 8, scope: !5127)
!5127 = distinct !DILexicalBlock(scope: !5128, file: !1, line: 2569, column: 7)
!5128 = distinct !DILexicalBlock(scope: !5122, file: !1, line: 2556, column: 29)
!5129 = !DILocation(line: 2569, column: 8, scope: !5130)
!5130 = !DILexicalBlockFile(scope: !5127, file: !1, discriminator: 1)
!5131 = !DILocation(line: 2569, column: 8, scope: !5132)
!5132 = !DILexicalBlockFile(scope: !5127, file: !1, discriminator: 2)
!5133 = !DILocation(line: 2569, column: 7, scope: !5132)
!5134 = !DILocation(line: 2570, column: 12, scope: !5127)
!5135 = !DILocation(line: 2570, column: 4, scope: !5127)
!5136 = !DILocation(line: 2571, column: 12, scope: !5137)
!5137 = distinct !DILexicalBlock(scope: !5128, file: !1, line: 2571, column: 7)
!5138 = !DILocation(line: 2571, column: 10, scope: !5137)
!5139 = !DILocation(line: 2571, column: 32, scope: !5137)
!5140 = !DILocation(line: 2571, column: 7, scope: !5128)
!5141 = !DILocation(line: 2572, column: 9, scope: !5142)
!5142 = distinct !DILexicalBlock(scope: !5143, file: !1, line: 2572, column: 8)
!5143 = distinct !DILexicalBlock(scope: !5137, file: !1, line: 2571, column: 38)
!5144 = !DILocation(line: 2572, column: 9, scope: !5145)
!5145 = !DILexicalBlockFile(scope: !5142, file: !1, discriminator: 1)
!5146 = !DILocation(line: 2572, column: 9, scope: !5147)
!5147 = !DILexicalBlockFile(scope: !5142, file: !1, discriminator: 2)
!5148 = !DILocation(line: 2572, column: 8, scope: !5147)
!5149 = !DILocation(line: 2573, column: 13, scope: !5142)
!5150 = !DILocation(line: 2573, column: 5, scope: !5142)
!5151 = !DILocation(line: 2574, column: 19, scope: !5143)
!5152 = !DILocation(line: 2574, column: 39, scope: !5143)
!5153 = !DILocation(line: 2574, column: 8, scope: !5143)
!5154 = !DILocation(line: 2574, column: 6, scope: !5143)
!5155 = !DILocation(line: 2575, column: 8, scope: !5156)
!5156 = distinct !DILexicalBlock(scope: !5143, file: !1, line: 2575, column: 8)
!5157 = !DILocation(line: 2575, column: 8, scope: !5143)
!5158 = !DILocation(line: 2576, column: 5, scope: !5156)
!5159 = !DILocation(line: 2578, column: 5, scope: !5156)
!5160 = !DILocation(line: 2579, column: 3, scope: !5143)
!5161 = !DILocation(line: 2580, column: 4, scope: !5137)
!5162 = !DILocation(line: 2581, column: 24, scope: !5128)
!5163 = !DILocation(line: 2581, column: 18, scope: !5128)
!5164 = !DILocation(line: 2581, column: 3, scope: !5128)
!5165 = !DILocation(line: 2581, column: 7, scope: !5128)
!5166 = !DILocation(line: 2581, column: 10, scope: !5128)
!5167 = !DILocation(line: 2581, column: 22, scope: !5128)
!5168 = !DILocation(line: 2582, column: 15, scope: !5128)
!5169 = !DILocation(line: 2582, column: 3, scope: !5128)
!5170 = !DILocation(line: 2582, column: 7, scope: !5128)
!5171 = !DILocation(line: 2582, column: 10, scope: !5128)
!5172 = !DILocation(line: 2582, column: 17, scope: !5128)
!5173 = !DILocation(line: 2556, column: 2, scope: !5174)
!5174 = !DILexicalBlockFile(scope: !5122, file: !1, discriminator: 2)
!5175 = !DILocation(line: 2584, column: 10, scope: !495)
!5176 = !DILocation(line: 2584, column: 2, scope: !495)
!5177 = !DILocation(line: 2585, column: 1, scope: !495)
!5178 = !DILocalVariable(name: "hf", arg: 1, scope: !498, file: !1, line: 2603, type: !480)
!5179 = !DILocation(line: 2603, column: 40, scope: !498)
!5180 = !DILocalVariable(name: "tbl", scope: !498, file: !1, line: 2605, type: !398)
!5181 = !DILocation(line: 2605, column: 12, scope: !498)
!5182 = !DILocalVariable(name: "bitlen", scope: !498, file: !1, line: 2606, type: !356)
!5183 = !DILocation(line: 2606, column: 23, scope: !498)
!5184 = !DILocalVariable(name: "bitptn", scope: !498, file: !1, line: 2607, type: !388)
!5185 = !DILocation(line: 2607, column: 6, scope: !498)
!5186 = !DILocalVariable(name: "weight", scope: !498, file: !1, line: 2607, type: !388)
!5187 = !DILocation(line: 2607, column: 18, scope: !498)
!5188 = !DILocalVariable(name: "i", scope: !498, file: !1, line: 2608, type: !23)
!5189 = !DILocation(line: 2608, column: 6, scope: !498)
!5190 = !DILocalVariable(name: "maxbits", scope: !498, file: !1, line: 2608, type: !23)
!5191 = !DILocation(line: 2608, column: 9, scope: !498)
!5192 = !DILocalVariable(name: "ptn", scope: !498, file: !1, line: 2608, type: !23)
!5193 = !DILocation(line: 2608, column: 22, scope: !498)
!5194 = !DILocalVariable(name: "tbl_size", scope: !498, file: !1, line: 2608, type: !23)
!5195 = !DILocation(line: 2608, column: 27, scope: !498)
!5196 = !DILocalVariable(name: "w", scope: !498, file: !1, line: 2608, type: !23)
!5197 = !DILocation(line: 2608, column: 37, scope: !498)
!5198 = !DILocalVariable(name: "diffbits", scope: !498, file: !1, line: 2609, type: !23)
!5199 = !DILocation(line: 2609, column: 6, scope: !498)
!5200 = !DILocalVariable(name: "len_avail", scope: !498, file: !1, line: 2609, type: !23)
!5201 = !DILocation(line: 2609, column: 16, scope: !498)
!5202 = !DILocation(line: 2614, column: 6, scope: !498)
!5203 = !DILocation(line: 2615, column: 9, scope: !5204)
!5204 = distinct !DILexicalBlock(scope: !498, file: !1, line: 2615, column: 2)
!5205 = !DILocation(line: 2615, column: 16, scope: !5204)
!5206 = !DILocation(line: 2615, column: 7, scope: !5204)
!5207 = !DILocation(line: 2615, column: 27, scope: !5208)
!5208 = !DILexicalBlockFile(scope: !5209, file: !1, discriminator: 1)
!5209 = distinct !DILexicalBlock(scope: !5204, file: !1, line: 2615, column: 2)
!5210 = !DILocation(line: 2615, column: 29, scope: !5208)
!5211 = !DILocation(line: 2615, column: 2, scope: !5208)
!5212 = !DILocation(line: 2616, column: 15, scope: !5213)
!5213 = distinct !DILexicalBlock(scope: !5209, file: !1, line: 2615, column: 50)
!5214 = !DILocation(line: 2616, column: 10, scope: !5213)
!5215 = !DILocation(line: 2616, column: 3, scope: !5213)
!5216 = !DILocation(line: 2616, column: 13, scope: !5213)
!5217 = !DILocation(line: 2617, column: 15, scope: !5213)
!5218 = !DILocation(line: 2617, column: 10, scope: !5213)
!5219 = !DILocation(line: 2617, column: 3, scope: !5213)
!5220 = !DILocation(line: 2617, column: 13, scope: !5213)
!5221 = !DILocation(line: 2618, column: 16, scope: !5222)
!5222 = distinct !DILexicalBlock(scope: !5213, file: !1, line: 2618, column: 7)
!5223 = !DILocation(line: 2618, column: 7, scope: !5222)
!5224 = !DILocation(line: 2618, column: 11, scope: !5222)
!5225 = !DILocation(line: 2618, column: 7, scope: !5213)
!5226 = !DILocation(line: 2619, column: 20, scope: !5227)
!5227 = distinct !DILexicalBlock(scope: !5222, file: !1, line: 2618, column: 20)
!5228 = !DILocation(line: 2619, column: 11, scope: !5227)
!5229 = !DILocation(line: 2619, column: 15, scope: !5227)
!5230 = !DILocation(line: 2619, column: 25, scope: !5227)
!5231 = !DILocation(line: 2619, column: 23, scope: !5227)
!5232 = !DILocation(line: 2619, column: 8, scope: !5227)
!5233 = !DILocation(line: 2620, column: 14, scope: !5227)
!5234 = !DILocation(line: 2620, column: 12, scope: !5227)
!5235 = !DILocation(line: 2621, column: 3, scope: !5227)
!5236 = !DILocation(line: 2622, column: 2, scope: !5213)
!5237 = !DILocation(line: 2615, column: 37, scope: !5238)
!5238 = !DILexicalBlockFile(scope: !5209, file: !1, discriminator: 2)
!5239 = !DILocation(line: 2615, column: 43, scope: !5238)
!5240 = !DILocation(line: 2615, column: 2, scope: !5238)
!5241 = !DILocation(line: 2623, column: 6, scope: !5242)
!5242 = distinct !DILexicalBlock(scope: !498, file: !1, line: 2623, column: 6)
!5243 = !DILocation(line: 2623, column: 10, scope: !5242)
!5244 = !DILocation(line: 2623, column: 21, scope: !5242)
!5245 = !DILocation(line: 2623, column: 24, scope: !5246)
!5246 = !DILexicalBlockFile(scope: !5242, file: !1, discriminator: 1)
!5247 = !DILocation(line: 2623, column: 34, scope: !5246)
!5248 = !DILocation(line: 2623, column: 38, scope: !5246)
!5249 = !DILocation(line: 2623, column: 32, scope: !5246)
!5250 = !DILocation(line: 2623, column: 6, scope: !5246)
!5251 = !DILocation(line: 2624, column: 3, scope: !5242)
!5252 = !DILocation(line: 2626, column: 17, scope: !498)
!5253 = !DILocation(line: 2626, column: 2, scope: !498)
!5254 = !DILocation(line: 2626, column: 6, scope: !498)
!5255 = !DILocation(line: 2626, column: 15, scope: !498)
!5256 = !DILocation(line: 2633, column: 6, scope: !5257)
!5257 = distinct !DILexicalBlock(scope: !498, file: !1, line: 2633, column: 6)
!5258 = !DILocation(line: 2633, column: 14, scope: !5257)
!5259 = !DILocation(line: 2633, column: 6, scope: !498)
!5260 = !DILocalVariable(name: "ebits", scope: !5261, file: !1, line: 2634, type: !23)
!5261 = distinct !DILexicalBlock(scope: !5257, file: !1, line: 2633, column: 20)
!5262 = !DILocation(line: 2634, column: 7, scope: !5261)
!5263 = !DILocation(line: 2634, column: 20, scope: !5261)
!5264 = !DILocation(line: 2634, column: 18, scope: !5261)
!5265 = !DILocation(line: 2635, column: 10, scope: !5266)
!5266 = distinct !DILexicalBlock(scope: !5261, file: !1, line: 2635, column: 3)
!5267 = !DILocation(line: 2635, column: 8, scope: !5266)
!5268 = !DILocation(line: 2635, column: 15, scope: !5269)
!5269 = !DILexicalBlockFile(scope: !5270, file: !1, discriminator: 1)
!5270 = distinct !DILexicalBlock(scope: !5266, file: !1, line: 2635, column: 3)
!5271 = !DILocation(line: 2635, column: 20, scope: !5269)
!5272 = !DILocation(line: 2635, column: 17, scope: !5269)
!5273 = !DILocation(line: 2635, column: 3, scope: !5269)
!5274 = !DILocation(line: 2636, column: 18, scope: !5275)
!5275 = distinct !DILexicalBlock(scope: !5270, file: !1, line: 2635, column: 34)
!5276 = !DILocation(line: 2636, column: 11, scope: !5275)
!5277 = !DILocation(line: 2636, column: 4, scope: !5275)
!5278 = !DILocation(line: 2636, column: 14, scope: !5275)
!5279 = !DILocation(line: 2637, column: 18, scope: !5275)
!5280 = !DILocation(line: 2637, column: 11, scope: !5275)
!5281 = !DILocation(line: 2637, column: 4, scope: !5275)
!5282 = !DILocation(line: 2637, column: 14, scope: !5275)
!5283 = !DILocation(line: 2638, column: 3, scope: !5275)
!5284 = !DILocation(line: 2635, column: 30, scope: !5285)
!5285 = !DILexicalBlockFile(scope: !5270, file: !1, discriminator: 2)
!5286 = !DILocation(line: 2635, column: 3, scope: !5285)
!5287 = !DILocation(line: 2639, column: 2, scope: !5261)
!5288 = !DILocation(line: 2640, column: 6, scope: !5289)
!5289 = distinct !DILexicalBlock(scope: !498, file: !1, line: 2640, column: 6)
!5290 = !DILocation(line: 2640, column: 14, scope: !5289)
!5291 = !DILocation(line: 2640, column: 6, scope: !498)
!5292 = !DILocalVariable(name: "htbl_max", scope: !5293, file: !1, line: 2641, type: !13)
!5293 = distinct !DILexicalBlock(scope: !5289, file: !1, line: 2640, column: 27)
!5294 = !DILocation(line: 2641, column: 12, scope: !5293)
!5295 = !DILocalVariable(name: "p", scope: !5293, file: !1, line: 2642, type: !398)
!5296 = !DILocation(line: 2642, column: 13, scope: !5293)
!5297 = !DILocation(line: 2644, column: 14, scope: !5293)
!5298 = !DILocation(line: 2644, column: 22, scope: !5293)
!5299 = !DILocation(line: 2644, column: 12, scope: !5293)
!5300 = !DILocation(line: 2645, column: 10, scope: !5301)
!5301 = distinct !DILexicalBlock(scope: !5293, file: !1, line: 2645, column: 3)
!5302 = !DILocation(line: 2645, column: 8, scope: !5301)
!5303 = !DILocation(line: 2645, column: 15, scope: !5304)
!5304 = !DILexicalBlockFile(scope: !5305, file: !1, discriminator: 1)
!5305 = distinct !DILexicalBlock(scope: !5301, file: !1, line: 2645, column: 3)
!5306 = !DILocation(line: 2645, column: 17, scope: !5304)
!5307 = !DILocation(line: 2645, column: 3, scope: !5304)
!5308 = !DILocation(line: 2646, column: 18, scope: !5309)
!5309 = distinct !DILexicalBlock(scope: !5305, file: !1, line: 2645, column: 36)
!5310 = !DILocation(line: 2646, column: 11, scope: !5309)
!5311 = !DILocation(line: 2646, column: 4, scope: !5309)
!5312 = !DILocation(line: 2646, column: 14, scope: !5309)
!5313 = !DILocation(line: 2647, column: 18, scope: !5309)
!5314 = !DILocation(line: 2647, column: 11, scope: !5309)
!5315 = !DILocation(line: 2647, column: 4, scope: !5309)
!5316 = !DILocation(line: 2647, column: 14, scope: !5309)
!5317 = !DILocation(line: 2648, column: 3, scope: !5309)
!5318 = !DILocation(line: 2645, column: 32, scope: !5319)
!5319 = !DILexicalBlockFile(scope: !5305, file: !1, discriminator: 2)
!5320 = !DILocation(line: 2645, column: 3, scope: !5319)
!5321 = !DILocation(line: 2649, column: 14, scope: !5293)
!5322 = !DILocation(line: 2650, column: 7, scope: !5293)
!5323 = !DILocation(line: 2650, column: 27, scope: !5293)
!5324 = !DILocation(line: 2650, column: 31, scope: !5293)
!5325 = !DILocation(line: 2650, column: 25, scope: !5293)
!5326 = !DILocation(line: 2649, column: 32, scope: !5293)
!5327 = !DILocation(line: 2649, column: 12, scope: !5293)
!5328 = !DILocation(line: 2651, column: 17, scope: !5293)
!5329 = !DILocation(line: 2651, column: 9, scope: !5293)
!5330 = !DILocation(line: 2651, column: 13, scope: !5293)
!5331 = !DILocation(line: 2651, column: 5, scope: !5293)
!5332 = !DILocation(line: 2652, column: 3, scope: !5293)
!5333 = !DILocation(line: 2652, column: 10, scope: !5334)
!5334 = !DILexicalBlockFile(scope: !5293, file: !1, discriminator: 1)
!5335 = !DILocation(line: 2652, column: 15, scope: !5334)
!5336 = !DILocation(line: 2652, column: 19, scope: !5334)
!5337 = !DILocation(line: 2652, column: 12, scope: !5334)
!5338 = !DILocation(line: 2652, column: 3, scope: !5334)
!5339 = !DILocation(line: 2653, column: 6, scope: !5293)
!5340 = !DILocation(line: 2653, column: 9, scope: !5293)
!5341 = !DILocation(line: 2652, column: 3, scope: !5342)
!5342 = !DILexicalBlockFile(scope: !5293, file: !1, discriminator: 2)
!5343 = !DILocation(line: 2654, column: 2, scope: !5293)
!5344 = !DILocation(line: 2655, column: 12, scope: !5289)
!5345 = !DILocation(line: 2656, column: 19, scope: !498)
!5346 = !DILocation(line: 2656, column: 2, scope: !498)
!5347 = !DILocation(line: 2656, column: 6, scope: !498)
!5348 = !DILocation(line: 2656, column: 17, scope: !498)
!5349 = !DILocation(line: 2661, column: 11, scope: !498)
!5350 = !DILocation(line: 2662, column: 8, scope: !498)
!5351 = !DILocation(line: 2662, column: 12, scope: !498)
!5352 = !DILocation(line: 2662, column: 6, scope: !498)
!5353 = !DILocation(line: 2663, column: 11, scope: !498)
!5354 = !DILocation(line: 2663, column: 15, scope: !498)
!5355 = !DILocation(line: 2663, column: 9, scope: !498)
!5356 = !DILocation(line: 2664, column: 14, scope: !498)
!5357 = !DILocation(line: 2664, column: 18, scope: !498)
!5358 = !DILocation(line: 2664, column: 12, scope: !498)
!5359 = !DILocation(line: 2665, column: 2, scope: !498)
!5360 = !DILocation(line: 2665, column: 6, scope: !498)
!5361 = !DILocation(line: 2665, column: 16, scope: !498)
!5362 = !DILocation(line: 2666, column: 9, scope: !5363)
!5363 = distinct !DILexicalBlock(scope: !498, file: !1, line: 2666, column: 2)
!5364 = !DILocation(line: 2666, column: 7, scope: !5363)
!5365 = !DILocation(line: 2666, column: 14, scope: !5366)
!5366 = !DILexicalBlockFile(scope: !5367, file: !1, discriminator: 1)
!5367 = distinct !DILexicalBlock(scope: !5363, file: !1, line: 2666, column: 2)
!5368 = !DILocation(line: 2666, column: 18, scope: !5366)
!5369 = !DILocation(line: 2666, column: 16, scope: !5366)
!5370 = !DILocation(line: 2666, column: 2, scope: !5366)
!5371 = !DILocalVariable(name: "p", scope: !5372, file: !1, line: 2667, type: !398)
!5372 = distinct !DILexicalBlock(scope: !5367, file: !1, line: 2666, column: 34)
!5373 = !DILocation(line: 2667, column: 13, scope: !5372)
!5374 = !DILocalVariable(name: "len", scope: !5372, file: !1, line: 2668, type: !23)
!5375 = !DILocation(line: 2668, column: 7, scope: !5372)
!5376 = !DILocalVariable(name: "cnt", scope: !5372, file: !1, line: 2668, type: !23)
!5377 = !DILocation(line: 2668, column: 12, scope: !5372)
!5378 = !DILocalVariable(name: "bit", scope: !5372, file: !1, line: 2669, type: !299)
!5379 = !DILocation(line: 2669, column: 12, scope: !5372)
!5380 = !DILocalVariable(name: "extlen", scope: !5372, file: !1, line: 2670, type: !23)
!5381 = !DILocation(line: 2670, column: 7, scope: !5372)
!5382 = !DILocalVariable(name: "ht", scope: !5372, file: !1, line: 2671, type: !400)
!5383 = !DILocation(line: 2671, column: 19, scope: !5372)
!5384 = !DILocation(line: 2673, column: 14, scope: !5385)
!5385 = distinct !DILexicalBlock(scope: !5372, file: !1, line: 2673, column: 7)
!5386 = !DILocation(line: 2673, column: 7, scope: !5385)
!5387 = !DILocation(line: 2673, column: 17, scope: !5385)
!5388 = !DILocation(line: 2673, column: 7, scope: !5372)
!5389 = !DILocation(line: 2674, column: 4, scope: !5385)
!5390 = !DILocation(line: 2676, column: 16, scope: !5372)
!5391 = !DILocation(line: 2676, column: 9, scope: !5372)
!5392 = !DILocation(line: 2676, column: 7, scope: !5372)
!5393 = !DILocation(line: 2677, column: 16, scope: !5372)
!5394 = !DILocation(line: 2677, column: 9, scope: !5372)
!5395 = !DILocation(line: 2677, column: 7, scope: !5372)
!5396 = !DILocation(line: 2678, column: 16, scope: !5372)
!5397 = !DILocation(line: 2678, column: 9, scope: !5372)
!5398 = !DILocation(line: 2678, column: 7, scope: !5372)
!5399 = !DILocation(line: 2679, column: 7, scope: !5400)
!5400 = distinct !DILexicalBlock(scope: !5372, file: !1, line: 2679, column: 7)
!5401 = !DILocation(line: 2679, column: 11, scope: !5400)
!5402 = !DILocation(line: 2679, column: 7, scope: !5372)
!5403 = !DILocation(line: 2681, column: 23, scope: !5404)
!5404 = distinct !DILexicalBlock(scope: !5405, file: !1, line: 2681, column: 8)
!5405 = distinct !DILexicalBlock(scope: !5400, file: !1, line: 2679, column: 25)
!5406 = !DILocation(line: 2681, column: 29, scope: !5404)
!5407 = !DILocation(line: 2681, column: 27, scope: !5404)
!5408 = !DILocation(line: 2681, column: 16, scope: !5404)
!5409 = !DILocation(line: 2681, column: 9, scope: !5404)
!5410 = !DILocation(line: 2681, column: 21, scope: !5404)
!5411 = !DILocation(line: 2681, column: 36, scope: !5404)
!5412 = !DILocation(line: 2681, column: 34, scope: !5404)
!5413 = !DILocation(line: 2681, column: 8, scope: !5405)
!5414 = !DILocation(line: 2682, column: 5, scope: !5404)
!5415 = !DILocation(line: 2684, column: 14, scope: !5405)
!5416 = !DILocation(line: 2684, column: 10, scope: !5405)
!5417 = !DILocation(line: 2684, column: 6, scope: !5405)
!5418 = !DILocation(line: 2685, column: 8, scope: !5419)
!5419 = distinct !DILexicalBlock(scope: !5405, file: !1, line: 2685, column: 8)
!5420 = !DILocation(line: 2685, column: 12, scope: !5419)
!5421 = !DILocation(line: 2685, column: 8, scope: !5405)
!5422 = !DILocalVariable(name: "pc", scope: !5423, file: !1, line: 2686, type: !398)
!5423 = distinct !DILexicalBlock(scope: !5419, file: !1, line: 2685, column: 17)
!5424 = !DILocation(line: 2686, column: 15, scope: !5423)
!5425 = !DILocation(line: 2688, column: 9, scope: !5423)
!5426 = !DILocation(line: 2689, column: 13, scope: !5423)
!5427 = !DILocation(line: 2689, column: 11, scope: !5423)
!5428 = !DILocation(line: 2689, column: 8, scope: !5423)
!5429 = !DILocation(line: 2690, column: 23, scope: !5423)
!5430 = !DILocation(line: 2690, column: 13, scope: !5423)
!5431 = !DILocation(line: 2690, column: 5, scope: !5423)
!5432 = !DILocation(line: 2690, column: 11, scope: !5423)
!5433 = !DILocation(line: 2691, column: 23, scope: !5423)
!5434 = !DILocation(line: 2691, column: 13, scope: !5423)
!5435 = !DILocation(line: 2691, column: 5, scope: !5423)
!5436 = !DILocation(line: 2691, column: 11, scope: !5423)
!5437 = !DILocation(line: 2692, column: 23, scope: !5423)
!5438 = !DILocation(line: 2692, column: 13, scope: !5423)
!5439 = !DILocation(line: 2692, column: 5, scope: !5423)
!5440 = !DILocation(line: 2692, column: 11, scope: !5423)
!5441 = !DILocation(line: 2693, column: 23, scope: !5423)
!5442 = !DILocation(line: 2693, column: 13, scope: !5423)
!5443 = !DILocation(line: 2693, column: 5, scope: !5423)
!5444 = !DILocation(line: 2693, column: 11, scope: !5423)
!5445 = !DILocation(line: 2694, column: 23, scope: !5423)
!5446 = !DILocation(line: 2694, column: 13, scope: !5423)
!5447 = !DILocation(line: 2694, column: 5, scope: !5423)
!5448 = !DILocation(line: 2694, column: 11, scope: !5423)
!5449 = !DILocation(line: 2695, column: 23, scope: !5423)
!5450 = !DILocation(line: 2695, column: 13, scope: !5423)
!5451 = !DILocation(line: 2695, column: 5, scope: !5423)
!5452 = !DILocation(line: 2695, column: 11, scope: !5423)
!5453 = !DILocation(line: 2696, column: 23, scope: !5423)
!5454 = !DILocation(line: 2696, column: 13, scope: !5423)
!5455 = !DILocation(line: 2696, column: 5, scope: !5423)
!5456 = !DILocation(line: 2696, column: 11, scope: !5423)
!5457 = !DILocation(line: 2697, column: 23, scope: !5423)
!5458 = !DILocation(line: 2697, column: 13, scope: !5423)
!5459 = !DILocation(line: 2697, column: 5, scope: !5423)
!5460 = !DILocation(line: 2697, column: 11, scope: !5423)
!5461 = !DILocation(line: 2698, column: 9, scope: !5462)
!5462 = distinct !DILexicalBlock(scope: !5423, file: !1, line: 2698, column: 9)
!5463 = !DILocation(line: 2698, column: 13, scope: !5462)
!5464 = !DILocation(line: 2698, column: 9, scope: !5423)
!5465 = !DILocation(line: 2699, column: 10, scope: !5466)
!5466 = distinct !DILexicalBlock(scope: !5462, file: !1, line: 2698, column: 18)
!5467 = !DILocation(line: 2700, column: 16, scope: !5466)
!5468 = !DILocation(line: 2700, column: 14, scope: !5466)
!5469 = !DILocation(line: 2700, column: 6, scope: !5466)
!5470 = !DILocation(line: 2700, column: 22, scope: !5466)
!5471 = !DILocation(line: 2702, column: 14, scope: !5466)
!5472 = !DILocation(line: 2702, column: 12, scope: !5466)
!5473 = !DILocation(line: 2702, column: 9, scope: !5466)
!5474 = !DILocation(line: 2703, column: 6, scope: !5466)
!5475 = !DILocation(line: 2703, column: 13, scope: !5476)
!5476 = !DILexicalBlockFile(scope: !5466, file: !1, discriminator: 1)
!5477 = !DILocation(line: 2703, column: 17, scope: !5476)
!5478 = !DILocation(line: 2703, column: 6, scope: !5476)
!5479 = !DILocation(line: 2704, column: 11, scope: !5480)
!5480 = distinct !DILexicalBlock(scope: !5466, file: !1, line: 2703, column: 23)
!5481 = !DILocation(line: 2705, column: 17, scope: !5480)
!5482 = !DILocation(line: 2705, column: 15, scope: !5480)
!5483 = !DILocation(line: 2705, column: 7, scope: !5480)
!5484 = !DILocation(line: 2705, column: 23, scope: !5480)
!5485 = !DILocation(line: 2703, column: 6, scope: !5486)
!5486 = !DILexicalBlockFile(scope: !5466, file: !1, discriminator: 2)
!5487 = !DILocation(line: 2708, column: 5, scope: !5466)
!5488 = !DILocation(line: 2709, column: 9, scope: !5489)
!5489 = distinct !DILexicalBlock(scope: !5423, file: !1, line: 2709, column: 9)
!5490 = !DILocation(line: 2709, column: 9, scope: !5423)
!5491 = !DILocation(line: 2710, column: 13, scope: !5489)
!5492 = !DILocation(line: 2710, column: 6, scope: !5489)
!5493 = !DILocation(line: 2710, column: 16, scope: !5489)
!5494 = !DILocation(line: 2710, column: 20, scope: !5489)
!5495 = !DILocation(line: 2710, column: 24, scope: !5489)
!5496 = !DILocation(line: 2711, column: 4, scope: !5423)
!5497 = !DILocation(line: 2712, column: 5, scope: !5498)
!5498 = distinct !DILexicalBlock(scope: !5419, file: !1, line: 2711, column: 11)
!5499 = !DILocation(line: 2712, column: 12, scope: !5500)
!5500 = !DILexicalBlockFile(scope: !5498, file: !1, discriminator: 1)
!5501 = !DILocation(line: 2712, column: 16, scope: !5500)
!5502 = !DILocation(line: 2712, column: 5, scope: !5500)
!5503 = !DILocation(line: 2713, column: 27, scope: !5504)
!5504 = distinct !DILexicalBlock(scope: !5498, file: !1, line: 2712, column: 21)
!5505 = !DILocation(line: 2713, column: 17, scope: !5504)
!5506 = !DILocation(line: 2713, column: 8, scope: !5504)
!5507 = !DILocation(line: 2713, column: 6, scope: !5504)
!5508 = !DILocation(line: 2713, column: 15, scope: !5504)
!5509 = !DILocation(line: 2714, column: 27, scope: !5504)
!5510 = !DILocation(line: 2714, column: 17, scope: !5504)
!5511 = !DILocation(line: 2714, column: 8, scope: !5504)
!5512 = !DILocation(line: 2714, column: 6, scope: !5504)
!5513 = !DILocation(line: 2714, column: 15, scope: !5504)
!5514 = !DILocation(line: 2712, column: 5, scope: !5515)
!5515 = !DILexicalBlockFile(scope: !5498, file: !1, discriminator: 2)
!5516 = !DILocation(line: 2716, column: 9, scope: !5517)
!5517 = distinct !DILexicalBlock(scope: !5498, file: !1, line: 2716, column: 9)
!5518 = !DILocation(line: 2716, column: 9, scope: !5498)
!5519 = !DILocation(line: 2717, column: 27, scope: !5517)
!5520 = !DILocation(line: 2717, column: 17, scope: !5517)
!5521 = !DILocation(line: 2717, column: 8, scope: !5517)
!5522 = !DILocation(line: 2717, column: 6, scope: !5517)
!5523 = !DILocation(line: 2717, column: 15, scope: !5517)
!5524 = !DILocation(line: 2719, column: 4, scope: !5405)
!5525 = !DILocation(line: 2726, column: 17, scope: !5372)
!5526 = !DILocation(line: 2726, column: 23, scope: !5372)
!5527 = !DILocation(line: 2726, column: 21, scope: !5372)
!5528 = !DILocation(line: 2726, column: 10, scope: !5372)
!5529 = !DILocation(line: 2726, column: 3, scope: !5372)
!5530 = !DILocation(line: 2726, column: 15, scope: !5372)
!5531 = !DILocation(line: 2727, column: 16, scope: !5372)
!5532 = !DILocation(line: 2727, column: 25, scope: !5372)
!5533 = !DILocation(line: 2727, column: 12, scope: !5372)
!5534 = !DILocation(line: 2727, column: 9, scope: !5372)
!5535 = !DILocation(line: 2727, column: 7, scope: !5372)
!5536 = !DILocation(line: 2728, column: 12, scope: !5372)
!5537 = !DILocation(line: 2728, column: 16, scope: !5372)
!5538 = !DILocation(line: 2728, column: 10, scope: !5372)
!5539 = !DILocation(line: 2730, column: 13, scope: !5372)
!5540 = !DILocation(line: 2730, column: 20, scope: !5372)
!5541 = !DILocation(line: 2730, column: 17, scope: !5372)
!5542 = !DILocation(line: 2730, column: 9, scope: !5372)
!5543 = !DILocation(line: 2730, column: 5, scope: !5372)
!5544 = !DILocation(line: 2731, column: 8, scope: !5545)
!5545 = distinct !DILexicalBlock(scope: !5372, file: !1, line: 2731, column: 7)
!5546 = !DILocation(line: 2731, column: 7, scope: !5545)
!5547 = !DILocation(line: 2731, column: 10, scope: !5545)
!5548 = !DILocation(line: 2731, column: 7, scope: !5372)
!5549 = !DILocation(line: 2732, column: 9, scope: !5550)
!5550 = distinct !DILexicalBlock(scope: !5545, file: !1, line: 2731, column: 16)
!5551 = !DILocation(line: 2732, column: 21, scope: !5550)
!5552 = !DILocation(line: 2732, column: 25, scope: !5550)
!5553 = !DILocation(line: 2732, column: 19, scope: !5550)
!5554 = !DILocation(line: 2732, column: 5, scope: !5550)
!5555 = !DILocation(line: 2732, column: 7, scope: !5550)
!5556 = !DILocation(line: 2733, column: 20, scope: !5550)
!5557 = !DILocation(line: 2733, column: 24, scope: !5550)
!5558 = !DILocation(line: 2733, column: 33, scope: !5550)
!5559 = !DILocation(line: 2733, column: 11, scope: !5550)
!5560 = !DILocation(line: 2733, column: 15, scope: !5550)
!5561 = !DILocation(line: 2733, column: 7, scope: !5550)
!5562 = !DILocation(line: 2734, column: 8, scope: !5563)
!5563 = distinct !DILexicalBlock(scope: !5550, file: !1, line: 2734, column: 8)
!5564 = !DILocation(line: 2734, column: 12, scope: !5563)
!5565 = !DILocation(line: 2734, column: 24, scope: !5563)
!5566 = !DILocation(line: 2734, column: 28, scope: !5563)
!5567 = !DILocation(line: 2734, column: 22, scope: !5563)
!5568 = !DILocation(line: 2734, column: 8, scope: !5550)
!5569 = !DILocation(line: 2735, column: 5, scope: !5563)
!5570 = !DILocation(line: 2736, column: 4, scope: !5550)
!5571 = !DILocation(line: 2736, column: 8, scope: !5550)
!5572 = !DILocation(line: 2736, column: 13, scope: !5550)
!5573 = !DILocation(line: 2737, column: 4, scope: !5550)
!5574 = !DILocation(line: 2737, column: 8, scope: !5550)
!5575 = !DILocation(line: 2737, column: 14, scope: !5550)
!5576 = !DILocation(line: 2738, column: 3, scope: !5550)
!5577 = !DILocation(line: 2739, column: 9, scope: !5578)
!5578 = distinct !DILexicalBlock(scope: !5579, file: !1, line: 2739, column: 8)
!5579 = distinct !DILexicalBlock(scope: !5545, file: !1, line: 2738, column: 10)
!5580 = !DILocation(line: 2739, column: 8, scope: !5578)
!5581 = !DILocation(line: 2739, column: 13, scope: !5578)
!5582 = !DILocation(line: 2739, column: 11, scope: !5578)
!5583 = !DILocation(line: 2739, column: 23, scope: !5578)
!5584 = !DILocation(line: 2740, column: 9, scope: !5578)
!5585 = !DILocation(line: 2740, column: 8, scope: !5578)
!5586 = !DILocation(line: 2740, column: 15, scope: !5578)
!5587 = !DILocation(line: 2740, column: 27, scope: !5578)
!5588 = !DILocation(line: 2740, column: 31, scope: !5578)
!5589 = !DILocation(line: 2740, column: 25, scope: !5578)
!5590 = !DILocation(line: 2740, column: 11, scope: !5578)
!5591 = !DILocation(line: 2739, column: 8, scope: !5592)
!5592 = !DILexicalBlockFile(scope: !5579, file: !1, discriminator: 1)
!5593 = !DILocation(line: 2741, column: 5, scope: !5578)
!5594 = !DILocation(line: 2742, column: 21, scope: !5579)
!5595 = !DILocation(line: 2742, column: 20, scope: !5579)
!5596 = !DILocation(line: 2742, column: 25, scope: !5579)
!5597 = !DILocation(line: 2742, column: 23, scope: !5579)
!5598 = !DILocation(line: 2742, column: 11, scope: !5579)
!5599 = !DILocation(line: 2742, column: 15, scope: !5579)
!5600 = !DILocation(line: 2742, column: 7, scope: !5579)
!5601 = !DILocation(line: 2744, column: 3, scope: !5372)
!5602 = !DILocation(line: 2744, column: 10, scope: !5603)
!5603 = !DILexicalBlockFile(scope: !5372, file: !1, discriminator: 1)
!5604 = !DILocation(line: 2744, column: 19, scope: !5603)
!5605 = !DILocation(line: 2744, column: 3, scope: !5603)
!5606 = !DILocation(line: 2745, column: 8, scope: !5607)
!5607 = distinct !DILexicalBlock(scope: !5608, file: !1, line: 2745, column: 8)
!5608 = distinct !DILexicalBlock(scope: !5372, file: !1, line: 2744, column: 24)
!5609 = !DILocation(line: 2745, column: 14, scope: !5607)
!5610 = !DILocation(line: 2745, column: 12, scope: !5607)
!5611 = !DILocation(line: 2745, column: 8, scope: !5608)
!5612 = !DILocation(line: 2746, column: 9, scope: !5613)
!5613 = distinct !DILexicalBlock(scope: !5614, file: !1, line: 2746, column: 9)
!5614 = distinct !DILexicalBlock(scope: !5607, file: !1, line: 2745, column: 19)
!5615 = !DILocation(line: 2746, column: 13, scope: !5613)
!5616 = !DILocation(line: 2746, column: 20, scope: !5613)
!5617 = !DILocation(line: 2746, column: 18, scope: !5613)
!5618 = !DILocation(line: 2746, column: 9, scope: !5614)
!5619 = !DILocation(line: 2747, column: 17, scope: !5620)
!5620 = distinct !DILexicalBlock(scope: !5613, file: !1, line: 2746, column: 31)
!5621 = !DILocation(line: 2747, column: 29, scope: !5620)
!5622 = !DILocation(line: 2747, column: 33, scope: !5620)
!5623 = !DILocation(line: 2747, column: 27, scope: !5620)
!5624 = !DILocation(line: 2747, column: 6, scope: !5620)
!5625 = !DILocation(line: 2747, column: 10, scope: !5620)
!5626 = !DILocation(line: 2747, column: 15, scope: !5620)
!5627 = !DILocation(line: 2748, column: 22, scope: !5620)
!5628 = !DILocation(line: 2748, column: 26, scope: !5620)
!5629 = !DILocation(line: 2748, column: 35, scope: !5620)
!5630 = !DILocation(line: 2748, column: 13, scope: !5620)
!5631 = !DILocation(line: 2748, column: 17, scope: !5620)
!5632 = !DILocation(line: 2748, column: 9, scope: !5620)
!5633 = !DILocation(line: 2749, column: 10, scope: !5634)
!5634 = distinct !DILexicalBlock(scope: !5620, file: !1, line: 2749, column: 10)
!5635 = !DILocation(line: 2749, column: 14, scope: !5634)
!5636 = !DILocation(line: 2749, column: 26, scope: !5634)
!5637 = !DILocation(line: 2749, column: 30, scope: !5634)
!5638 = !DILocation(line: 2749, column: 24, scope: !5634)
!5639 = !DILocation(line: 2749, column: 10, scope: !5620)
!5640 = !DILocation(line: 2750, column: 7, scope: !5634)
!5641 = !DILocation(line: 2751, column: 6, scope: !5620)
!5642 = !DILocation(line: 2751, column: 10, scope: !5620)
!5643 = !DILocation(line: 2751, column: 15, scope: !5620)
!5644 = !DILocation(line: 2752, column: 6, scope: !5620)
!5645 = !DILocation(line: 2752, column: 10, scope: !5620)
!5646 = !DILocation(line: 2752, column: 16, scope: !5620)
!5647 = !DILocation(line: 2753, column: 5, scope: !5620)
!5648 = !DILocation(line: 2754, column: 22, scope: !5649)
!5649 = distinct !DILexicalBlock(scope: !5613, file: !1, line: 2753, column: 12)
!5650 = !DILocation(line: 2754, column: 26, scope: !5649)
!5651 = !DILocation(line: 2754, column: 33, scope: !5649)
!5652 = !DILocation(line: 2754, column: 31, scope: !5649)
!5653 = !DILocation(line: 2754, column: 13, scope: !5649)
!5654 = !DILocation(line: 2754, column: 17, scope: !5649)
!5655 = !DILocation(line: 2754, column: 9, scope: !5649)
!5656 = !DILocation(line: 2756, column: 4, scope: !5614)
!5657 = !DILocation(line: 2757, column: 9, scope: !5658)
!5658 = distinct !DILexicalBlock(scope: !5659, file: !1, line: 2757, column: 9)
!5659 = distinct !DILexicalBlock(scope: !5607, file: !1, line: 2756, column: 11)
!5660 = !DILocation(line: 2757, column: 13, scope: !5658)
!5661 = !DILocation(line: 2757, column: 21, scope: !5658)
!5662 = !DILocation(line: 2757, column: 19, scope: !5658)
!5663 = !DILocation(line: 2757, column: 9, scope: !5659)
!5664 = !DILocation(line: 2758, column: 18, scope: !5665)
!5665 = distinct !DILexicalBlock(scope: !5658, file: !1, line: 2757, column: 32)
!5666 = !DILocation(line: 2758, column: 30, scope: !5665)
!5667 = !DILocation(line: 2758, column: 34, scope: !5665)
!5668 = !DILocation(line: 2758, column: 28, scope: !5665)
!5669 = !DILocation(line: 2758, column: 6, scope: !5665)
!5670 = !DILocation(line: 2758, column: 10, scope: !5665)
!5671 = !DILocation(line: 2758, column: 16, scope: !5665)
!5672 = !DILocation(line: 2759, column: 22, scope: !5665)
!5673 = !DILocation(line: 2759, column: 26, scope: !5665)
!5674 = !DILocation(line: 2759, column: 35, scope: !5665)
!5675 = !DILocation(line: 2759, column: 13, scope: !5665)
!5676 = !DILocation(line: 2759, column: 17, scope: !5665)
!5677 = !DILocation(line: 2759, column: 9, scope: !5665)
!5678 = !DILocation(line: 2760, column: 10, scope: !5679)
!5679 = distinct !DILexicalBlock(scope: !5665, file: !1, line: 2760, column: 10)
!5680 = !DILocation(line: 2760, column: 14, scope: !5679)
!5681 = !DILocation(line: 2760, column: 26, scope: !5679)
!5682 = !DILocation(line: 2760, column: 30, scope: !5679)
!5683 = !DILocation(line: 2760, column: 24, scope: !5679)
!5684 = !DILocation(line: 2760, column: 10, scope: !5665)
!5685 = !DILocation(line: 2761, column: 7, scope: !5679)
!5686 = !DILocation(line: 2762, column: 6, scope: !5665)
!5687 = !DILocation(line: 2762, column: 10, scope: !5665)
!5688 = !DILocation(line: 2762, column: 15, scope: !5665)
!5689 = !DILocation(line: 2763, column: 6, scope: !5665)
!5690 = !DILocation(line: 2763, column: 10, scope: !5665)
!5691 = !DILocation(line: 2763, column: 16, scope: !5665)
!5692 = !DILocation(line: 2764, column: 5, scope: !5665)
!5693 = !DILocation(line: 2765, column: 22, scope: !5694)
!5694 = distinct !DILexicalBlock(scope: !5658, file: !1, line: 2764, column: 12)
!5695 = !DILocation(line: 2765, column: 26, scope: !5694)
!5696 = !DILocation(line: 2765, column: 34, scope: !5694)
!5697 = !DILocation(line: 2765, column: 32, scope: !5694)
!5698 = !DILocation(line: 2765, column: 13, scope: !5694)
!5699 = !DILocation(line: 2765, column: 17, scope: !5694)
!5700 = !DILocation(line: 2765, column: 9, scope: !5694)
!5701 = !DILocation(line: 2768, column: 8, scope: !5608)
!5702 = !DILocation(line: 2744, column: 3, scope: !5703)
!5703 = !DILexicalBlockFile(scope: !5372, file: !1, discriminator: 2)
!5704 = !DILocation(line: 2770, column: 7, scope: !5705)
!5705 = distinct !DILexicalBlock(scope: !5372, file: !1, line: 2770, column: 7)
!5706 = !DILocation(line: 2770, column: 13, scope: !5705)
!5707 = !DILocation(line: 2770, column: 11, scope: !5705)
!5708 = !DILocation(line: 2770, column: 7, scope: !5372)
!5709 = !DILocation(line: 2771, column: 8, scope: !5710)
!5710 = distinct !DILexicalBlock(scope: !5711, file: !1, line: 2771, column: 8)
!5711 = distinct !DILexicalBlock(scope: !5705, file: !1, line: 2770, column: 18)
!5712 = !DILocation(line: 2771, column: 12, scope: !5710)
!5713 = !DILocation(line: 2771, column: 17, scope: !5710)
!5714 = !DILocation(line: 2771, column: 8, scope: !5711)
!5715 = !DILocation(line: 2772, column: 5, scope: !5710)
!5716 = !DILocation(line: 2773, column: 25, scope: !5711)
!5717 = !DILocation(line: 2773, column: 15, scope: !5711)
!5718 = !DILocation(line: 2773, column: 4, scope: !5711)
!5719 = !DILocation(line: 2773, column: 8, scope: !5711)
!5720 = !DILocation(line: 2773, column: 13, scope: !5711)
!5721 = !DILocation(line: 2774, column: 3, scope: !5711)
!5722 = !DILocation(line: 2775, column: 8, scope: !5723)
!5723 = distinct !DILexicalBlock(scope: !5724, file: !1, line: 2775, column: 8)
!5724 = distinct !DILexicalBlock(scope: !5705, file: !1, line: 2774, column: 10)
!5725 = !DILocation(line: 2775, column: 12, scope: !5723)
!5726 = !DILocation(line: 2775, column: 18, scope: !5723)
!5727 = !DILocation(line: 2775, column: 8, scope: !5724)
!5728 = !DILocation(line: 2776, column: 5, scope: !5723)
!5729 = !DILocation(line: 2777, column: 26, scope: !5724)
!5730 = !DILocation(line: 2777, column: 16, scope: !5724)
!5731 = !DILocation(line: 2777, column: 4, scope: !5724)
!5732 = !DILocation(line: 2777, column: 8, scope: !5724)
!5733 = !DILocation(line: 2777, column: 14, scope: !5724)
!5734 = !DILocation(line: 2779, column: 2, scope: !5372)
!5735 = !DILocation(line: 2666, column: 30, scope: !5736)
!5736 = !DILexicalBlockFile(scope: !5367, file: !1, discriminator: 2)
!5737 = !DILocation(line: 2666, column: 2, scope: !5736)
!5738 = !DILocation(line: 2780, column: 2, scope: !498)
!5739 = !DILocation(line: 2781, column: 1, scope: !498)
!5740 = !DILocalVariable(name: "hf", arg: 1, scope: !501, file: !1, line: 2804, type: !480)
!5741 = !DILocation(line: 2804, column: 36, scope: !501)
!5742 = !DILocalVariable(name: "rbits", arg: 2, scope: !501, file: !1, line: 2804, type: !13)
!5743 = !DILocation(line: 2804, column: 49, scope: !501)
!5744 = !DILocalVariable(name: "c", scope: !501, file: !1, line: 2806, type: !23)
!5745 = !DILocation(line: 2806, column: 6, scope: !501)
!5746 = !DILocation(line: 2811, column: 14, scope: !501)
!5747 = !DILocation(line: 2811, column: 23, scope: !501)
!5748 = !DILocation(line: 2811, column: 27, scope: !501)
!5749 = !DILocation(line: 2811, column: 20, scope: !501)
!5750 = !DILocation(line: 2811, column: 6, scope: !501)
!5751 = !DILocation(line: 2811, column: 10, scope: !501)
!5752 = !DILocation(line: 2811, column: 4, scope: !501)
!5753 = !DILocation(line: 2812, column: 6, scope: !5754)
!5754 = distinct !DILexicalBlock(scope: !501, file: !1, line: 2812, column: 6)
!5755 = !DILocation(line: 2812, column: 10, scope: !5754)
!5756 = !DILocation(line: 2812, column: 14, scope: !5754)
!5757 = !DILocation(line: 2812, column: 8, scope: !5754)
!5758 = !DILocation(line: 2812, column: 24, scope: !5754)
!5759 = !DILocation(line: 2812, column: 27, scope: !5760)
!5760 = !DILexicalBlockFile(scope: !5754, file: !1, discriminator: 1)
!5761 = !DILocation(line: 2812, column: 31, scope: !5760)
!5762 = !DILocation(line: 2812, column: 41, scope: !5760)
!5763 = !DILocation(line: 2812, column: 6, scope: !5760)
!5764 = !DILocation(line: 2813, column: 11, scope: !5754)
!5765 = !DILocation(line: 2813, column: 3, scope: !5754)
!5766 = !DILocation(line: 2815, column: 34, scope: !501)
!5767 = !DILocation(line: 2815, column: 38, scope: !501)
!5768 = !DILocation(line: 2815, column: 45, scope: !501)
!5769 = !DILocation(line: 2815, column: 10, scope: !501)
!5770 = !DILocation(line: 2815, column: 2, scope: !501)
!5771 = !DILocation(line: 2816, column: 1, scope: !501)
!5772 = !DILocalVariable(name: "hf", arg: 1, scope: !504, file: !1, line: 2784, type: !480)
!5773 = !DILocation(line: 2784, column: 41, scope: !504)
!5774 = !DILocalVariable(name: "rbits", arg: 2, scope: !504, file: !1, line: 2784, type: !13)
!5775 = !DILocation(line: 2784, column: 54, scope: !504)
!5776 = !DILocalVariable(name: "c", arg: 3, scope: !504, file: !1, line: 2784, type: !23)
!5777 = !DILocation(line: 2784, column: 65, scope: !504)
!5778 = !DILocalVariable(name: "ht", scope: !504, file: !1, line: 2786, type: !400)
!5779 = !DILocation(line: 2786, column: 18, scope: !504)
!5780 = !DILocalVariable(name: "extlen", scope: !504, file: !1, line: 2787, type: !23)
!5781 = !DILocation(line: 2787, column: 6, scope: !504)
!5782 = !DILocation(line: 2789, column: 7, scope: !504)
!5783 = !DILocation(line: 2789, column: 11, scope: !504)
!5784 = !DILocation(line: 2789, column: 5, scope: !504)
!5785 = !DILocation(line: 2790, column: 11, scope: !504)
!5786 = !DILocation(line: 2790, column: 15, scope: !504)
!5787 = !DILocation(line: 2790, column: 9, scope: !504)
!5788 = !DILocation(line: 2791, column: 2, scope: !504)
!5789 = !DILocation(line: 2791, column: 9, scope: !5790)
!5790 = !DILexicalBlockFile(scope: !504, file: !1, discriminator: 1)
!5791 = !DILocation(line: 2791, column: 14, scope: !5790)
!5792 = !DILocation(line: 2791, column: 18, scope: !5790)
!5793 = !DILocation(line: 2791, column: 11, scope: !5790)
!5794 = !DILocation(line: 2791, column: 2, scope: !5790)
!5795 = !DILocation(line: 2792, column: 8, scope: !5796)
!5796 = distinct !DILexicalBlock(scope: !504, file: !1, line: 2791, column: 29)
!5797 = !DILocation(line: 2792, column: 12, scope: !5796)
!5798 = !DILocation(line: 2792, column: 5, scope: !5796)
!5799 = !DILocation(line: 2793, column: 13, scope: !5800)
!5800 = distinct !DILexicalBlock(scope: !5796, file: !1, line: 2793, column: 7)
!5801 = !DILocation(line: 2793, column: 16, scope: !5800)
!5802 = !DILocation(line: 2793, column: 21, scope: !5800)
!5803 = !DILocation(line: 2793, column: 24, scope: !5804)
!5804 = !DILexicalBlockFile(scope: !5800, file: !1, discriminator: 1)
!5805 = !DILocation(line: 2793, column: 29, scope: !5804)
!5806 = !DILocation(line: 2793, column: 33, scope: !5804)
!5807 = !DILocation(line: 2793, column: 26, scope: !5804)
!5808 = !DILocation(line: 2793, column: 7, scope: !5804)
!5809 = !DILocation(line: 2794, column: 4, scope: !5800)
!5810 = !DILocation(line: 2795, column: 7, scope: !5811)
!5811 = distinct !DILexicalBlock(scope: !5796, file: !1, line: 2795, column: 7)
!5812 = !DILocation(line: 2795, column: 22, scope: !5811)
!5813 = !DILocation(line: 2795, column: 19, scope: !5811)
!5814 = !DILocation(line: 2795, column: 13, scope: !5811)
!5815 = !DILocation(line: 2795, column: 7, scope: !5796)
!5816 = !DILocation(line: 2796, column: 11, scope: !5811)
!5817 = !DILocation(line: 2796, column: 8, scope: !5811)
!5818 = !DILocation(line: 2796, column: 14, scope: !5811)
!5819 = !DILocation(line: 2796, column: 6, scope: !5811)
!5820 = !DILocation(line: 2796, column: 4, scope: !5811)
!5821 = !DILocation(line: 2798, column: 11, scope: !5811)
!5822 = !DILocation(line: 2798, column: 8, scope: !5811)
!5823 = !DILocation(line: 2798, column: 14, scope: !5811)
!5824 = !DILocation(line: 2798, column: 6, scope: !5811)
!5825 = !DILocation(line: 2791, column: 2, scope: !5826)
!5826 = !DILexicalBlockFile(scope: !504, file: !1, discriminator: 2)
!5827 = !DILocation(line: 2800, column: 10, scope: !504)
!5828 = !DILocation(line: 2800, column: 2, scope: !504)
!5829 = !DILocation(line: 2801, column: 1, scope: !504)
!5830 = !DILocalVariable(name: "strm", arg: 1, scope: !511, file: !1, line: 1828, type: !476)
!5831 = !DILocation(line: 1828, column: 36, scope: !511)
!5832 = !DILocation(line: 1831, column: 6, scope: !5833)
!5833 = distinct !DILexicalBlock(scope: !511, file: !1, line: 1831, column: 6)
!5834 = !DILocation(line: 1831, column: 12, scope: !5833)
!5835 = !DILocation(line: 1831, column: 15, scope: !5833)
!5836 = !DILocation(line: 1831, column: 6, scope: !511)
!5837 = !DILocation(line: 1832, column: 3, scope: !5833)
!5838 = !DILocation(line: 1833, column: 7, scope: !511)
!5839 = !DILocation(line: 1833, column: 13, scope: !511)
!5840 = !DILocation(line: 1833, column: 17, scope: !511)
!5841 = !DILocation(line: 1833, column: 2, scope: !511)
!5842 = !DILocation(line: 1834, column: 21, scope: !511)
!5843 = !DILocation(line: 1834, column: 27, scope: !511)
!5844 = !DILocation(line: 1834, column: 31, scope: !511)
!5845 = !DILocation(line: 1834, column: 2, scope: !511)
!5846 = !DILocation(line: 1835, column: 21, scope: !511)
!5847 = !DILocation(line: 1835, column: 27, scope: !511)
!5848 = !DILocation(line: 1835, column: 31, scope: !511)
!5849 = !DILocation(line: 1835, column: 2, scope: !511)
!5850 = !DILocation(line: 1836, column: 7, scope: !511)
!5851 = !DILocation(line: 1836, column: 13, scope: !511)
!5852 = !DILocation(line: 1836, column: 2, scope: !511)
!5853 = !DILocation(line: 1837, column: 2, scope: !511)
!5854 = !DILocation(line: 1837, column: 8, scope: !511)
!5855 = !DILocation(line: 1837, column: 11, scope: !511)
!5856 = !DILocation(line: 1838, column: 1, scope: !511)
!5857 = !DILocation(line: 1838, column: 1, scope: !5858)
!5858 = !DILexicalBlockFile(scope: !511, file: !1, discriminator: 1)
!5859 = !DILocalVariable(name: "hf", arg: 1, scope: !514, file: !1, line: 2476, type: !480)
!5860 = !DILocation(line: 2476, column: 34, scope: !514)
!5861 = !DILocation(line: 2478, column: 7, scope: !514)
!5862 = !DILocation(line: 2478, column: 11, scope: !514)
!5863 = !DILocation(line: 2478, column: 2, scope: !514)
!5864 = !DILocation(line: 2479, column: 7, scope: !514)
!5865 = !DILocation(line: 2479, column: 11, scope: !514)
!5866 = !DILocation(line: 2479, column: 2, scope: !514)
!5867 = !DILocation(line: 2480, column: 7, scope: !514)
!5868 = !DILocation(line: 2480, column: 11, scope: !514)
!5869 = !DILocation(line: 2480, column: 2, scope: !514)
!5870 = !DILocation(line: 2481, column: 1, scope: !514)
