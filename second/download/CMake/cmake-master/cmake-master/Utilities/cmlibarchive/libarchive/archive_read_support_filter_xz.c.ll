; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_support_filter_xz.c'
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
%struct.private_data = type { %struct.lzma_stream, i8*, i64, i64, i8, i8, i8, i32, i64, i64 }
%struct.lzma_stream = type { i8*, i64, i64, i8*, i64, i64, %struct.lzma_allocator*, %struct.lzma_internal_s*, i8*, i8*, i8*, i8*, i64, i64, i64, i64, i32, i32 }
%struct.lzma_allocator = type { i8* (i8*, i64, i64)*, void (i8*, i8*)*, i8* }
%struct.lzma_internal_s = type opaque
%struct.lzma_filter = type { i64, i8* }

@.str = private unnamed_addr constant [31 x i8] c"archive_read_support_filter_xz\00", align 1
@.str.1 = private unnamed_addr constant [3 x i8] c"xz\00", align 1
@.str.2 = private unnamed_addr constant [33 x i8] c"archive_read_support_filter_lzma\00", align 1
@.str.3 = private unnamed_addr constant [5 x i8] c"lzma\00", align 1
@.str.4 = private unnamed_addr constant [33 x i8] c"archive_read_support_filter_lzip\00", align 1
@.str.5 = private unnamed_addr constant [5 x i8] c"lzip\00", align 1
@.str.6 = private unnamed_addr constant [7 x i8] c"\FD7zXZ\00\00", align 1
@.str.7 = private unnamed_addr constant [5 x i8] c"LZIP\00", align 1
@xz_lzma_bidder_init.out_block_size = internal constant i64 65536, align 8
@.str.8 = private unnamed_addr constant [41 x i8] c"Can't allocate data for xz decompression\00", align 1
@.str.9 = private unnamed_addr constant [16 x i8] c"truncated input\00", align 1
@.str.10 = private unnamed_addr constant [35 x i8] c"Lzip: Remaining data is less bytes\00", align 1
@.str.11 = private unnamed_addr constant [18 x i8] c"Lzip: CRC32 error\00", align 1
@.str.12 = private unnamed_addr constant [30 x i8] c"Lzip: Uncompressed size error\00", align 1
@.str.13 = private unnamed_addr constant [24 x i8] c"Lzip: Member size error\00", align 1
@.str.14 = private unnamed_addr constant [43 x i8] c"Lzma library error: Cannot allocate memory\00", align 1
@.str.15 = private unnamed_addr constant [34 x i8] c"Lzma library error: Out of memory\00", align 1
@.str.16 = private unnamed_addr constant [42 x i8] c"Lzma library error: format not recognized\00", align 1
@.str.17 = private unnamed_addr constant [36 x i8] c"Lzma library error: Invalid options\00", align 1
@.str.18 = private unnamed_addr constant [41 x i8] c"Lzma library error: Corrupted input data\00", align 1
@.str.19 = private unnamed_addr constant [45 x i8] c"Lzma library error:  No progress is possible\00", align 1
@.str.20 = private unnamed_addr constant [42 x i8] c"Lzma decompression failed:  Unknown error\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_read_support_compression_xz(%struct.archive* %a) #0 !dbg !377 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !415, metadata !416), !dbg !417
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !418
  %call = call i32 @archive_read_support_filter_xz(%struct.archive* %0), !dbg !419
  ret i32 %call, !dbg !420
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define i32 @archive_read_support_filter_xz(%struct.archive* %_a) #0 !dbg !379 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_read*, align 8
  %bidder = alloca %struct.archive_read_filter_bidder*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !421, metadata !416), !dbg !422
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !423, metadata !416), !dbg !424
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !425
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !426
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !424
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter_bidder** %bidder, metadata !427, metadata !416), !dbg !428
  br label %do.body, !dbg !429

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !430, metadata !416), !dbg !432
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !433
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 14594245, i32 1, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str, i32 0, i32 0)), !dbg !433
  store i32 %call, i32* %magic_test, align 4, !dbg !433
  %3 = load i32, i32* %magic_test, align 4, !dbg !433
  %cmp = icmp eq i32 %3, -30, !dbg !433
  br i1 %cmp, label %if.then, label %if.end, !dbg !433

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !435
  br label %return, !dbg !435

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !438

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !440
  %call1 = call i32 @__archive_read_get_bidder(%struct.archive_read* %4, %struct.archive_read_filter_bidder** %bidder), !dbg !442
  %cmp2 = icmp ne i32 %call1, 0, !dbg !443
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !444

if.then3:                                         ; preds = %do.end
  store i32 -30, i32* %retval, align 4, !dbg !445
  br label %return, !dbg !445

if.end4:                                          ; preds = %do.end
  %5 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !446
  %data = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %5, i32 0, i32 0, !dbg !447
  store i8* null, i8** %data, align 8, !dbg !448
  %6 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !449
  %name = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %6, i32 0, i32 1, !dbg !450
  store i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.1, i32 0, i32 0), i8** %name, align 8, !dbg !451
  %7 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !452
  %bid = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %7, i32 0, i32 2, !dbg !453
  store i32 (%struct.archive_read_filter_bidder*, %struct.archive_read_filter*)* @xz_bidder_bid, i32 (%struct.archive_read_filter_bidder*, %struct.archive_read_filter*)** %bid, align 8, !dbg !454
  %8 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !455
  %init = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %8, i32 0, i32 3, !dbg !456
  store i32 (%struct.archive_read_filter*)* @xz_bidder_init, i32 (%struct.archive_read_filter*)** %init, align 8, !dbg !457
  %9 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !458
  %options = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %9, i32 0, i32 4, !dbg !459
  store i32 (%struct.archive_read_filter_bidder*, i8*, i8*)* null, i32 (%struct.archive_read_filter_bidder*, i8*, i8*)** %options, align 8, !dbg !460
  %10 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !461
  %free = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %10, i32 0, i32 5, !dbg !462
  store i32 (%struct.archive_read_filter_bidder*)* null, i32 (%struct.archive_read_filter_bidder*)** %free, align 8, !dbg !463
  store i32 0, i32* %retval, align 4, !dbg !464
  br label %return, !dbg !464

return:                                           ; preds = %if.end4, %if.then3, %if.then
  %11 = load i32, i32* %retval, align 4, !dbg !465
  ret i32 %11, !dbg !465
}

declare i32 @__archive_check_magic(%struct.archive*, i32, i32, i8*) #2

declare i32 @__archive_read_get_bidder(%struct.archive_read*, %struct.archive_read_filter_bidder**) #2

; Function Attrs: nounwind uwtable
define internal i32 @xz_bidder_bid(%struct.archive_read_filter_bidder* %self, %struct.archive_read_filter* %filter) #0 !dbg !384 {
entry:
  %retval = alloca i32, align 4
  %self.addr = alloca %struct.archive_read_filter_bidder*, align 8
  %filter.addr = alloca %struct.archive_read_filter*, align 8
  %buffer = alloca i8*, align 8
  %avail = alloca i64, align 8
  store %struct.archive_read_filter_bidder* %self, %struct.archive_read_filter_bidder** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter_bidder** %self.addr, metadata !466, metadata !416), !dbg !467
  store %struct.archive_read_filter* %filter, %struct.archive_read_filter** %filter.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %filter.addr, metadata !468, metadata !416), !dbg !469
  call void @llvm.dbg.declare(metadata i8** %buffer, metadata !470, metadata !416), !dbg !471
  call void @llvm.dbg.declare(metadata i64* %avail, metadata !472, metadata !416), !dbg !473
  %0 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %self.addr, align 8, !dbg !474
  %1 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !475
  %call = call i8* @__archive_read_filter_ahead(%struct.archive_read_filter* %1, i64 6, i64* %avail), !dbg !476
  store i8* %call, i8** %buffer, align 8, !dbg !477
  %2 = load i8*, i8** %buffer, align 8, !dbg !478
  %cmp = icmp eq i8* %2, null, !dbg !480
  br i1 %cmp, label %if.then, label %if.end, !dbg !481

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !482
  br label %return, !dbg !482

if.end:                                           ; preds = %entry
  %3 = load i8*, i8** %buffer, align 8, !dbg !483
  %call1 = call i32 @memcmp(i8* %3, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.6, i32 0, i32 0), i64 6) #6, !dbg !485
  %cmp2 = icmp ne i32 %call1, 0, !dbg !486
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !487

if.then3:                                         ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !488
  br label %return, !dbg !488

if.end4:                                          ; preds = %if.end
  store i32 48, i32* %retval, align 4, !dbg !489
  br label %return, !dbg !489

return:                                           ; preds = %if.end4, %if.then3, %if.then
  %4 = load i32, i32* %retval, align 4, !dbg !490
  ret i32 %4, !dbg !490
}

; Function Attrs: nounwind uwtable
define internal i32 @xz_bidder_init(%struct.archive_read_filter* %self) #0 !dbg !395 {
entry:
  %self.addr = alloca %struct.archive_read_filter*, align 8
  store %struct.archive_read_filter* %self, %struct.archive_read_filter** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %self.addr, metadata !491, metadata !416), !dbg !492
  %0 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !493
  %code = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %0, i32 0, i32 12, !dbg !494
  store i32 6, i32* %code, align 8, !dbg !495
  %1 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !496
  %name = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %1, i32 0, i32 11, !dbg !497
  store i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.1, i32 0, i32 0), i8** %name, align 8, !dbg !498
  %2 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !499
  %call = call i32 @xz_lzma_bidder_init(%struct.archive_read_filter* %2), !dbg !500
  ret i32 %call, !dbg !501
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_support_compression_lzma(%struct.archive* %a) #0 !dbg !380 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !502, metadata !416), !dbg !503
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !504
  %call = call i32 @archive_read_support_filter_lzma(%struct.archive* %0), !dbg !505
  ret i32 %call, !dbg !506
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_support_filter_lzma(%struct.archive* %_a) #0 !dbg !381 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_read*, align 8
  %bidder = alloca %struct.archive_read_filter_bidder*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !507, metadata !416), !dbg !508
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !509, metadata !416), !dbg !510
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !511
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !512
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !510
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter_bidder** %bidder, metadata !513, metadata !416), !dbg !514
  br label %do.body, !dbg !515

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !516, metadata !416), !dbg !518
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !519
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 14594245, i32 1, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.2, i32 0, i32 0)), !dbg !519
  store i32 %call, i32* %magic_test, align 4, !dbg !519
  %3 = load i32, i32* %magic_test, align 4, !dbg !519
  %cmp = icmp eq i32 %3, -30, !dbg !519
  br i1 %cmp, label %if.then, label %if.end, !dbg !519

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !521
  br label %return, !dbg !521

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !524

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !526
  %call1 = call i32 @__archive_read_get_bidder(%struct.archive_read* %4, %struct.archive_read_filter_bidder** %bidder), !dbg !528
  %cmp2 = icmp ne i32 %call1, 0, !dbg !529
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !530

if.then3:                                         ; preds = %do.end
  store i32 -30, i32* %retval, align 4, !dbg !531
  br label %return, !dbg !531

if.end4:                                          ; preds = %do.end
  %5 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !532
  %data = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %5, i32 0, i32 0, !dbg !533
  store i8* null, i8** %data, align 8, !dbg !534
  %6 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !535
  %name = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %6, i32 0, i32 1, !dbg !536
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.3, i32 0, i32 0), i8** %name, align 8, !dbg !537
  %7 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !538
  %bid = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %7, i32 0, i32 2, !dbg !539
  store i32 (%struct.archive_read_filter_bidder*, %struct.archive_read_filter*)* @lzma_bidder_bid, i32 (%struct.archive_read_filter_bidder*, %struct.archive_read_filter*)** %bid, align 8, !dbg !540
  %8 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !541
  %init = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %8, i32 0, i32 3, !dbg !542
  store i32 (%struct.archive_read_filter*)* @lzma_bidder_init, i32 (%struct.archive_read_filter*)** %init, align 8, !dbg !543
  %9 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !544
  %options = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %9, i32 0, i32 4, !dbg !545
  store i32 (%struct.archive_read_filter_bidder*, i8*, i8*)* null, i32 (%struct.archive_read_filter_bidder*, i8*, i8*)** %options, align 8, !dbg !546
  %10 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !547
  %free = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %10, i32 0, i32 5, !dbg !548
  store i32 (%struct.archive_read_filter_bidder*)* null, i32 (%struct.archive_read_filter_bidder*)** %free, align 8, !dbg !549
  store i32 0, i32* %retval, align 4, !dbg !550
  br label %return, !dbg !550

return:                                           ; preds = %if.end4, %if.then3, %if.then
  %11 = load i32, i32* %retval, align 4, !dbg !551
  ret i32 %11, !dbg !551
}

; Function Attrs: nounwind uwtable
define internal i32 @lzma_bidder_bid(%struct.archive_read_filter_bidder* %self, %struct.archive_read_filter* %filter) #0 !dbg !385 {
entry:
  %retval = alloca i32, align 4
  %self.addr = alloca %struct.archive_read_filter_bidder*, align 8
  %filter.addr = alloca %struct.archive_read_filter*, align 8
  %buffer = alloca i8*, align 8
  %avail = alloca i64, align 8
  %dicsize = alloca i32, align 4
  %uncompressed_size = alloca i64, align 8
  %bits_checked = alloca i32, align 4
  store %struct.archive_read_filter_bidder* %self, %struct.archive_read_filter_bidder** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter_bidder** %self.addr, metadata !552, metadata !416), !dbg !553
  store %struct.archive_read_filter* %filter, %struct.archive_read_filter** %filter.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %filter.addr, metadata !554, metadata !416), !dbg !555
  call void @llvm.dbg.declare(metadata i8** %buffer, metadata !556, metadata !416), !dbg !557
  call void @llvm.dbg.declare(metadata i64* %avail, metadata !558, metadata !416), !dbg !559
  call void @llvm.dbg.declare(metadata i32* %dicsize, metadata !560, metadata !416), !dbg !561
  call void @llvm.dbg.declare(metadata i64* %uncompressed_size, metadata !562, metadata !416), !dbg !563
  call void @llvm.dbg.declare(metadata i32* %bits_checked, metadata !564, metadata !416), !dbg !565
  %0 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %self.addr, align 8, !dbg !566
  %1 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !567
  %call = call i8* @__archive_read_filter_ahead(%struct.archive_read_filter* %1, i64 14, i64* %avail), !dbg !568
  store i8* %call, i8** %buffer, align 8, !dbg !569
  %2 = load i8*, i8** %buffer, align 8, !dbg !570
  %cmp = icmp eq i8* %2, null, !dbg !572
  br i1 %cmp, label %if.then, label %if.end, !dbg !573

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !574
  br label %return, !dbg !574

if.end:                                           ; preds = %entry
  store i32 0, i32* %bits_checked, align 4, !dbg !575
  %3 = load i8*, i8** %buffer, align 8, !dbg !576
  %arrayidx = getelementptr inbounds i8, i8* %3, i64 0, !dbg !576
  %4 = load i8, i8* %arrayidx, align 1, !dbg !576
  %conv = zext i8 %4 to i32, !dbg !576
  %cmp1 = icmp sgt i32 %conv, 224, !dbg !578
  br i1 %cmp1, label %if.then3, label %if.end4, !dbg !579

if.then3:                                         ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !580
  br label %return, !dbg !580

if.end4:                                          ; preds = %if.end
  %5 = load i8*, i8** %buffer, align 8, !dbg !581
  %arrayidx5 = getelementptr inbounds i8, i8* %5, i64 0, !dbg !581
  %6 = load i8, i8* %arrayidx5, align 1, !dbg !581
  %conv6 = zext i8 %6 to i32, !dbg !581
  %cmp7 = icmp eq i32 %conv6, 93, !dbg !583
  br i1 %cmp7, label %if.then13, label %lor.lhs.false, !dbg !584

lor.lhs.false:                                    ; preds = %if.end4
  %7 = load i8*, i8** %buffer, align 8, !dbg !585
  %arrayidx9 = getelementptr inbounds i8, i8* %7, i64 0, !dbg !585
  %8 = load i8, i8* %arrayidx9, align 1, !dbg !585
  %conv10 = zext i8 %8 to i32, !dbg !585
  %cmp11 = icmp eq i32 %conv10, 94, !dbg !587
  br i1 %cmp11, label %if.then13, label %if.end14, !dbg !588

if.then13:                                        ; preds = %lor.lhs.false, %if.end4
  %9 = load i32, i32* %bits_checked, align 4, !dbg !589
  %add = add nsw i32 %9, 8, !dbg !589
  store i32 %add, i32* %bits_checked, align 4, !dbg !589
  br label %if.end14, !dbg !590

if.end14:                                         ; preds = %if.then13, %lor.lhs.false
  %10 = load i8*, i8** %buffer, align 8, !dbg !591
  %add.ptr = getelementptr inbounds i8, i8* %10, i64 5, !dbg !592
  %call15 = call i64 @archive_le64dec(i8* %add.ptr), !dbg !593
  store i64 %call15, i64* %uncompressed_size, align 8, !dbg !594
  %11 = load i64, i64* %uncompressed_size, align 8, !dbg !595
  %cmp16 = icmp eq i64 %11, -1, !dbg !597
  br i1 %cmp16, label %if.then18, label %if.end20, !dbg !598

if.then18:                                        ; preds = %if.end14
  %12 = load i32, i32* %bits_checked, align 4, !dbg !599
  %add19 = add nsw i32 %12, 64, !dbg !599
  store i32 %add19, i32* %bits_checked, align 4, !dbg !599
  br label %if.end20, !dbg !600

if.end20:                                         ; preds = %if.then18, %if.end14
  %13 = load i8*, i8** %buffer, align 8, !dbg !601
  %add.ptr21 = getelementptr inbounds i8, i8* %13, i64 1, !dbg !602
  %call22 = call i32 @archive_le32dec(i8* %add.ptr21), !dbg !603
  store i32 %call22, i32* %dicsize, align 4, !dbg !604
  %14 = load i32, i32* %dicsize, align 4, !dbg !605
  switch i32 %14, label %sw.default [
    i32 4096, label %sw.bb
    i32 8192, label %sw.bb
    i32 16384, label %sw.bb
    i32 32768, label %sw.bb
    i32 65536, label %sw.bb
    i32 131072, label %sw.bb
    i32 262144, label %sw.bb
    i32 524288, label %sw.bb
    i32 1048576, label %sw.bb
    i32 2097152, label %sw.bb
    i32 4194304, label %sw.bb
    i32 8388608, label %sw.bb
    i32 16777216, label %sw.bb
    i32 33554432, label %sw.bb
    i32 67108864, label %sw.bb
    i32 134217728, label %sw.bb
  ], !dbg !606

sw.bb:                                            ; preds = %if.end20, %if.end20, %if.end20, %if.end20, %if.end20, %if.end20, %if.end20, %if.end20, %if.end20, %if.end20, %if.end20, %if.end20, %if.end20, %if.end20, %if.end20, %if.end20
  %15 = load i32, i32* %bits_checked, align 4, !dbg !607
  %add23 = add nsw i32 %15, 32, !dbg !607
  store i32 %add23, i32* %bits_checked, align 4, !dbg !607
  br label %sw.epilog, !dbg !609

sw.default:                                       ; preds = %if.end20
  %16 = load i32, i32* %dicsize, align 4, !dbg !610
  %cmp24 = icmp ule i32 %16, 66060288, !dbg !612
  br i1 %cmp24, label %land.lhs.true, label %if.end36, !dbg !613

land.lhs.true:                                    ; preds = %sw.default
  %17 = load i32, i32* %dicsize, align 4, !dbg !614
  %cmp26 = icmp uge i32 %17, 3145728, !dbg !616
  br i1 %cmp26, label %land.lhs.true28, label %if.end36, !dbg !617

land.lhs.true28:                                  ; preds = %land.lhs.true
  %18 = load i32, i32* %dicsize, align 4, !dbg !618
  %and = and i32 %18, 1048575, !dbg !619
  %cmp29 = icmp eq i32 %and, 0, !dbg !620
  br i1 %cmp29, label %land.lhs.true31, label %if.end36, !dbg !621

land.lhs.true31:                                  ; preds = %land.lhs.true28
  %19 = load i32, i32* %bits_checked, align 4, !dbg !622
  %cmp32 = icmp eq i32 %19, 72, !dbg !623
  br i1 %cmp32, label %if.then34, label %if.end36, !dbg !624

if.then34:                                        ; preds = %land.lhs.true31
  %20 = load i32, i32* %bits_checked, align 4, !dbg !626
  %add35 = add nsw i32 %20, 32, !dbg !626
  store i32 %add35, i32* %bits_checked, align 4, !dbg !626
  br label %sw.epilog, !dbg !628

if.end36:                                         ; preds = %land.lhs.true31, %land.lhs.true28, %land.lhs.true, %sw.default
  store i32 0, i32* %retval, align 4, !dbg !629
  br label %return, !dbg !629

sw.epilog:                                        ; preds = %if.then34, %sw.bb
  %21 = load i32, i32* %bits_checked, align 4, !dbg !630
  store i32 %21, i32* %retval, align 4, !dbg !631
  br label %return, !dbg !631

return:                                           ; preds = %sw.epilog, %if.end36, %if.then3, %if.then
  %22 = load i32, i32* %retval, align 4, !dbg !632
  ret i32 %22, !dbg !632
}

; Function Attrs: nounwind uwtable
define internal i32 @lzma_bidder_init(%struct.archive_read_filter* %self) #0 !dbg !407 {
entry:
  %self.addr = alloca %struct.archive_read_filter*, align 8
  store %struct.archive_read_filter* %self, %struct.archive_read_filter** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %self.addr, metadata !633, metadata !416), !dbg !634
  %0 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !635
  %code = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %0, i32 0, i32 12, !dbg !636
  store i32 5, i32* %code, align 8, !dbg !637
  %1 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !638
  %name = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %1, i32 0, i32 11, !dbg !639
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.3, i32 0, i32 0), i8** %name, align 8, !dbg !640
  %2 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !641
  %call = call i32 @xz_lzma_bidder_init(%struct.archive_read_filter* %2), !dbg !642
  ret i32 %call, !dbg !643
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_support_compression_lzip(%struct.archive* %a) #0 !dbg !382 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !644, metadata !416), !dbg !645
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !646
  %call = call i32 @archive_read_support_filter_lzip(%struct.archive* %0), !dbg !647
  ret i32 %call, !dbg !648
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_support_filter_lzip(%struct.archive* %_a) #0 !dbg !383 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_read*, align 8
  %bidder = alloca %struct.archive_read_filter_bidder*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !649, metadata !416), !dbg !650
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !651, metadata !416), !dbg !652
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !653
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !654
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !652
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter_bidder** %bidder, metadata !655, metadata !416), !dbg !656
  br label %do.body, !dbg !657

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !658, metadata !416), !dbg !660
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !661
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 14594245, i32 1, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.4, i32 0, i32 0)), !dbg !661
  store i32 %call, i32* %magic_test, align 4, !dbg !661
  %3 = load i32, i32* %magic_test, align 4, !dbg !661
  %cmp = icmp eq i32 %3, -30, !dbg !661
  br i1 %cmp, label %if.then, label %if.end, !dbg !661

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !663
  br label %return, !dbg !663

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !666

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !668
  %call1 = call i32 @__archive_read_get_bidder(%struct.archive_read* %4, %struct.archive_read_filter_bidder** %bidder), !dbg !670
  %cmp2 = icmp ne i32 %call1, 0, !dbg !671
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !672

if.then3:                                         ; preds = %do.end
  store i32 -30, i32* %retval, align 4, !dbg !673
  br label %return, !dbg !673

if.end4:                                          ; preds = %do.end
  %5 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !674
  %data = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %5, i32 0, i32 0, !dbg !675
  store i8* null, i8** %data, align 8, !dbg !676
  %6 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !677
  %name = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %6, i32 0, i32 1, !dbg !678
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.5, i32 0, i32 0), i8** %name, align 8, !dbg !679
  %7 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !680
  %bid = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %7, i32 0, i32 2, !dbg !681
  store i32 (%struct.archive_read_filter_bidder*, %struct.archive_read_filter*)* @lzip_bidder_bid, i32 (%struct.archive_read_filter_bidder*, %struct.archive_read_filter*)** %bid, align 8, !dbg !682
  %8 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !683
  %init = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %8, i32 0, i32 3, !dbg !684
  store i32 (%struct.archive_read_filter*)* @lzip_bidder_init, i32 (%struct.archive_read_filter*)** %init, align 8, !dbg !685
  %9 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !686
  %options = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %9, i32 0, i32 4, !dbg !687
  store i32 (%struct.archive_read_filter_bidder*, i8*, i8*)* null, i32 (%struct.archive_read_filter_bidder*, i8*, i8*)** %options, align 8, !dbg !688
  %10 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !689
  %free = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %10, i32 0, i32 5, !dbg !690
  store i32 (%struct.archive_read_filter_bidder*)* null, i32 (%struct.archive_read_filter_bidder*)** %free, align 8, !dbg !691
  store i32 0, i32* %retval, align 4, !dbg !692
  br label %return, !dbg !692

return:                                           ; preds = %if.end4, %if.then3, %if.then
  %11 = load i32, i32* %retval, align 4, !dbg !693
  ret i32 %11, !dbg !693
}

; Function Attrs: nounwind uwtable
define internal i32 @lzip_bidder_bid(%struct.archive_read_filter_bidder* %self, %struct.archive_read_filter* %filter) #0 !dbg !393 {
entry:
  %self.addr = alloca %struct.archive_read_filter_bidder*, align 8
  %filter.addr = alloca %struct.archive_read_filter*, align 8
  store %struct.archive_read_filter_bidder* %self, %struct.archive_read_filter_bidder** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter_bidder** %self.addr, metadata !694, metadata !416), !dbg !695
  store %struct.archive_read_filter* %filter, %struct.archive_read_filter** %filter.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %filter.addr, metadata !696, metadata !416), !dbg !697
  %0 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %self.addr, align 8, !dbg !698
  %1 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !699
  %call = call i32 @lzip_has_member(%struct.archive_read_filter* %1), !dbg !700
  ret i32 %call, !dbg !701
}

; Function Attrs: nounwind uwtable
define internal i32 @lzip_bidder_init(%struct.archive_read_filter* %self) #0 !dbg !408 {
entry:
  %self.addr = alloca %struct.archive_read_filter*, align 8
  store %struct.archive_read_filter* %self, %struct.archive_read_filter** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %self.addr, metadata !702, metadata !416), !dbg !703
  %0 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !704
  %code = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %0, i32 0, i32 12, !dbg !705
  store i32 9, i32* %code, align 8, !dbg !706
  %1 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !707
  %name = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %1, i32 0, i32 11, !dbg !708
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.5, i32 0, i32 0), i8** %name, align 8, !dbg !709
  %2 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !710
  %call = call i32 @xz_lzma_bidder_init(%struct.archive_read_filter* %2), !dbg !711
  ret i32 %call, !dbg !712
}

declare i8* @__archive_read_filter_ahead(%struct.archive_read_filter*, i64, i64*) #2

; Function Attrs: nounwind readonly
declare i32 @memcmp(i8*, i8*, i64) #3

; Function Attrs: inlinehint nounwind uwtable
define internal i64 @archive_le64dec(i8* %pp) #4 !dbg !386 {
entry:
  %pp.addr = alloca i8*, align 8
  %p = alloca i8*, align 8
  store i8* %pp, i8** %pp.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %pp.addr, metadata !713, metadata !416), !dbg !714
  call void @llvm.dbg.declare(metadata i8** %p, metadata !715, metadata !416), !dbg !716
  %0 = load i8*, i8** %pp.addr, align 8, !dbg !717
  store i8* %0, i8** %p, align 8, !dbg !716
  %1 = load i8*, i8** %p, align 8, !dbg !718
  %add.ptr = getelementptr inbounds i8, i8* %1, i64 4, !dbg !719
  %call = call i32 @archive_le32dec(i8* %add.ptr), !dbg !720
  %conv = zext i32 %call to i64, !dbg !721
  %shl = shl i64 %conv, 32, !dbg !722
  %2 = load i8*, i8** %p, align 8, !dbg !723
  %call1 = call i32 @archive_le32dec(i8* %2), !dbg !724
  %conv2 = zext i32 %call1 to i64, !dbg !726
  %or = or i64 %shl, %conv2, !dbg !727
  ret i64 %or, !dbg !728
}

; Function Attrs: inlinehint nounwind uwtable
define internal i32 @archive_le32dec(i8* %pp) #4 !dbg !390 {
entry:
  %pp.addr = alloca i8*, align 8
  %p = alloca i8*, align 8
  %p3 = alloca i32, align 4
  %p2 = alloca i32, align 4
  %p1 = alloca i32, align 4
  %p0 = alloca i32, align 4
  store i8* %pp, i8** %pp.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %pp.addr, metadata !729, metadata !416), !dbg !730
  call void @llvm.dbg.declare(metadata i8** %p, metadata !731, metadata !416), !dbg !732
  %0 = load i8*, i8** %pp.addr, align 8, !dbg !733
  store i8* %0, i8** %p, align 8, !dbg !732
  call void @llvm.dbg.declare(metadata i32* %p3, metadata !734, metadata !416), !dbg !735
  %1 = load i8*, i8** %p, align 8, !dbg !736
  %arrayidx = getelementptr inbounds i8, i8* %1, i64 3, !dbg !736
  %2 = load i8, i8* %arrayidx, align 1, !dbg !736
  %conv = zext i8 %2 to i32, !dbg !736
  store i32 %conv, i32* %p3, align 4, !dbg !735
  call void @llvm.dbg.declare(metadata i32* %p2, metadata !737, metadata !416), !dbg !738
  %3 = load i8*, i8** %p, align 8, !dbg !739
  %arrayidx1 = getelementptr inbounds i8, i8* %3, i64 2, !dbg !739
  %4 = load i8, i8* %arrayidx1, align 1, !dbg !739
  %conv2 = zext i8 %4 to i32, !dbg !739
  store i32 %conv2, i32* %p2, align 4, !dbg !738
  call void @llvm.dbg.declare(metadata i32* %p1, metadata !740, metadata !416), !dbg !741
  %5 = load i8*, i8** %p, align 8, !dbg !742
  %arrayidx3 = getelementptr inbounds i8, i8* %5, i64 1, !dbg !742
  %6 = load i8, i8* %arrayidx3, align 1, !dbg !742
  %conv4 = zext i8 %6 to i32, !dbg !742
  store i32 %conv4, i32* %p1, align 4, !dbg !741
  call void @llvm.dbg.declare(metadata i32* %p0, metadata !743, metadata !416), !dbg !744
  %7 = load i8*, i8** %p, align 8, !dbg !745
  %arrayidx5 = getelementptr inbounds i8, i8* %7, i64 0, !dbg !745
  %8 = load i8, i8* %arrayidx5, align 1, !dbg !745
  %conv6 = zext i8 %8 to i32, !dbg !745
  store i32 %conv6, i32* %p0, align 4, !dbg !744
  %9 = load i32, i32* %p3, align 4, !dbg !746
  %shl = shl i32 %9, 24, !dbg !747
  %10 = load i32, i32* %p2, align 4, !dbg !748
  %shl7 = shl i32 %10, 16, !dbg !749
  %or = or i32 %shl, %shl7, !dbg !750
  %11 = load i32, i32* %p1, align 4, !dbg !751
  %shl8 = shl i32 %11, 8, !dbg !752
  %or9 = or i32 %or, %shl8, !dbg !753
  %12 = load i32, i32* %p0, align 4, !dbg !754
  %or10 = or i32 %or9, %12, !dbg !755
  ret i32 %or10, !dbg !756
}

; Function Attrs: nounwind uwtable
define internal i32 @lzip_has_member(%struct.archive_read_filter* %filter) #0 !dbg !394 {
entry:
  %retval = alloca i32, align 4
  %filter.addr = alloca %struct.archive_read_filter*, align 8
  %buffer = alloca i8*, align 8
  %avail = alloca i64, align 8
  %bits_checked = alloca i32, align 4
  %log2dic = alloca i32, align 4
  store %struct.archive_read_filter* %filter, %struct.archive_read_filter** %filter.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %filter.addr, metadata !757, metadata !416), !dbg !758
  call void @llvm.dbg.declare(metadata i8** %buffer, metadata !759, metadata !416), !dbg !760
  call void @llvm.dbg.declare(metadata i64* %avail, metadata !761, metadata !416), !dbg !762
  call void @llvm.dbg.declare(metadata i32* %bits_checked, metadata !763, metadata !416), !dbg !764
  call void @llvm.dbg.declare(metadata i32* %log2dic, metadata !765, metadata !416), !dbg !766
  %0 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !767
  %call = call i8* @__archive_read_filter_ahead(%struct.archive_read_filter* %0, i64 6, i64* %avail), !dbg !768
  store i8* %call, i8** %buffer, align 8, !dbg !769
  %1 = load i8*, i8** %buffer, align 8, !dbg !770
  %cmp = icmp eq i8* %1, null, !dbg !772
  br i1 %cmp, label %if.then, label %if.end, !dbg !773

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !774
  br label %return, !dbg !774

if.end:                                           ; preds = %entry
  store i32 0, i32* %bits_checked, align 4, !dbg !775
  %2 = load i8*, i8** %buffer, align 8, !dbg !776
  %call1 = call i32 @memcmp(i8* %2, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.7, i32 0, i32 0), i64 4) #6, !dbg !778
  %cmp2 = icmp ne i32 %call1, 0, !dbg !779
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !780

if.then3:                                         ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !781
  br label %return, !dbg !781

if.end4:                                          ; preds = %if.end
  %3 = load i32, i32* %bits_checked, align 4, !dbg !782
  %add = add nsw i32 %3, 32, !dbg !782
  store i32 %add, i32* %bits_checked, align 4, !dbg !782
  %4 = load i8*, i8** %buffer, align 8, !dbg !783
  %arrayidx = getelementptr inbounds i8, i8* %4, i64 4, !dbg !783
  %5 = load i8, i8* %arrayidx, align 1, !dbg !783
  %conv = zext i8 %5 to i32, !dbg !783
  %cmp5 = icmp ne i32 %conv, 0, !dbg !785
  br i1 %cmp5, label %land.lhs.true, label %if.end12, !dbg !786

land.lhs.true:                                    ; preds = %if.end4
  %6 = load i8*, i8** %buffer, align 8, !dbg !787
  %arrayidx7 = getelementptr inbounds i8, i8* %6, i64 4, !dbg !787
  %7 = load i8, i8* %arrayidx7, align 1, !dbg !787
  %conv8 = zext i8 %7 to i32, !dbg !787
  %cmp9 = icmp ne i32 %conv8, 1, !dbg !789
  br i1 %cmp9, label %if.then11, label %if.end12, !dbg !790

if.then11:                                        ; preds = %land.lhs.true
  store i32 0, i32* %retval, align 4, !dbg !791
  br label %return, !dbg !791

if.end12:                                         ; preds = %land.lhs.true, %if.end4
  %8 = load i32, i32* %bits_checked, align 4, !dbg !792
  %add13 = add nsw i32 %8, 8, !dbg !792
  store i32 %add13, i32* %bits_checked, align 4, !dbg !792
  %9 = load i8*, i8** %buffer, align 8, !dbg !793
  %arrayidx14 = getelementptr inbounds i8, i8* %9, i64 5, !dbg !793
  %10 = load i8, i8* %arrayidx14, align 1, !dbg !793
  %conv15 = zext i8 %10 to i32, !dbg !793
  %and = and i32 %conv15, 31, !dbg !794
  store i32 %and, i32* %log2dic, align 4, !dbg !795
  %11 = load i32, i32* %log2dic, align 4, !dbg !796
  %cmp16 = icmp slt i32 %11, 12, !dbg !798
  br i1 %cmp16, label %if.then20, label %lor.lhs.false, !dbg !799

lor.lhs.false:                                    ; preds = %if.end12
  %12 = load i32, i32* %log2dic, align 4, !dbg !800
  %cmp18 = icmp sgt i32 %12, 27, !dbg !802
  br i1 %cmp18, label %if.then20, label %if.end21, !dbg !803

if.then20:                                        ; preds = %lor.lhs.false, %if.end12
  store i32 0, i32* %retval, align 4, !dbg !804
  br label %return, !dbg !804

if.end21:                                         ; preds = %lor.lhs.false
  %13 = load i32, i32* %bits_checked, align 4, !dbg !805
  %add22 = add nsw i32 %13, 8, !dbg !805
  store i32 %add22, i32* %bits_checked, align 4, !dbg !805
  %14 = load i32, i32* %bits_checked, align 4, !dbg !806
  store i32 %14, i32* %retval, align 4, !dbg !807
  br label %return, !dbg !807

return:                                           ; preds = %if.end21, %if.then20, %if.then11, %if.then3, %if.then
  %15 = load i32, i32* %retval, align 4, !dbg !808
  ret i32 %15, !dbg !808
}

; Function Attrs: nounwind uwtable
define internal i32 @xz_lzma_bidder_init(%struct.archive_read_filter* %self) #0 !dbg !396 {
entry:
  %retval = alloca i32, align 4
  %self.addr = alloca %struct.archive_read_filter*, align 8
  %out_block = alloca i8*, align 8
  %state = alloca %struct.private_data*, align 8
  %ret = alloca i32, align 4
  store %struct.archive_read_filter* %self, %struct.archive_read_filter** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %self.addr, metadata !809, metadata !416), !dbg !810
  call void @llvm.dbg.declare(metadata i8** %out_block, metadata !811, metadata !416), !dbg !812
  call void @llvm.dbg.declare(metadata %struct.private_data** %state, metadata !813, metadata !416), !dbg !814
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !815, metadata !416), !dbg !816
  %call = call noalias i8* @calloc(i64 184, i64 1) #7, !dbg !817
  %0 = bitcast i8* %call to %struct.private_data*, !dbg !818
  store %struct.private_data* %0, %struct.private_data** %state, align 8, !dbg !819
  %call1 = call noalias i8* @malloc(i64 65536) #7, !dbg !820
  store i8* %call1, i8** %out_block, align 8, !dbg !821
  %1 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !822
  %cmp = icmp eq %struct.private_data* %1, null, !dbg !824
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !825

lor.lhs.false:                                    ; preds = %entry
  %2 = load i8*, i8** %out_block, align 8, !dbg !826
  %cmp2 = icmp eq i8* %2, null, !dbg !828
  br i1 %cmp2, label %if.then, label %if.end, !dbg !829

if.then:                                          ; preds = %lor.lhs.false, %entry
  %3 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !830
  %archive = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %3, i32 0, i32 3, !dbg !832
  %4 = load %struct.archive_read*, %struct.archive_read** %archive, align 8, !dbg !832
  %archive3 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %4, i32 0, i32 0, !dbg !833
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive3, i32 12, i8* getelementptr inbounds ([41 x i8], [41 x i8]* @.str.8, i32 0, i32 0)), !dbg !834
  %5 = load i8*, i8** %out_block, align 8, !dbg !835
  call void @free(i8* %5) #7, !dbg !836
  %6 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !837
  %7 = bitcast %struct.private_data* %6 to i8*, !dbg !837
  call void @free(i8* %7) #7, !dbg !838
  store i32 -30, i32* %retval, align 4, !dbg !839
  br label %return, !dbg !839

if.end:                                           ; preds = %lor.lhs.false
  %8 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !840
  %9 = bitcast %struct.private_data* %8 to i8*, !dbg !840
  %10 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !841
  %data = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %10, i32 0, i32 10, !dbg !842
  store i8* %9, i8** %data, align 8, !dbg !843
  %11 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !844
  %out_block_size = getelementptr inbounds %struct.private_data, %struct.private_data* %11, i32 0, i32 2, !dbg !845
  store i64 65536, i64* %out_block_size, align 8, !dbg !846
  %12 = load i8*, i8** %out_block, align 8, !dbg !847
  %13 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !848
  %out_block4 = getelementptr inbounds %struct.private_data, %struct.private_data* %13, i32 0, i32 1, !dbg !849
  store i8* %12, i8** %out_block4, align 8, !dbg !850
  %14 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !851
  %read = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %14, i32 0, i32 5, !dbg !852
  store i64 (%struct.archive_read_filter*, i8**)* @xz_filter_read, i64 (%struct.archive_read_filter*, i8**)** %read, align 8, !dbg !853
  %15 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !854
  %skip = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %15, i32 0, i32 6, !dbg !855
  store i64 (%struct.archive_read_filter*, i64)* null, i64 (%struct.archive_read_filter*, i64)** %skip, align 8, !dbg !856
  %16 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !857
  %close = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %16, i32 0, i32 8, !dbg !858
  store i32 (%struct.archive_read_filter*)* @xz_filter_close, i32 (%struct.archive_read_filter*)** %close, align 8, !dbg !859
  %17 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !860
  %stream = getelementptr inbounds %struct.private_data, %struct.private_data* %17, i32 0, i32 0, !dbg !861
  %avail_in = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %stream, i32 0, i32 1, !dbg !862
  store i64 0, i64* %avail_in, align 8, !dbg !863
  %18 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !864
  %out_block5 = getelementptr inbounds %struct.private_data, %struct.private_data* %18, i32 0, i32 1, !dbg !865
  %19 = load i8*, i8** %out_block5, align 8, !dbg !865
  %20 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !866
  %stream6 = getelementptr inbounds %struct.private_data, %struct.private_data* %20, i32 0, i32 0, !dbg !867
  %next_out = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %stream6, i32 0, i32 3, !dbg !868
  store i8* %19, i8** %next_out, align 8, !dbg !869
  %21 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !870
  %out_block_size7 = getelementptr inbounds %struct.private_data, %struct.private_data* %21, i32 0, i32 2, !dbg !871
  %22 = load i64, i64* %out_block_size7, align 8, !dbg !871
  %23 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !872
  %stream8 = getelementptr inbounds %struct.private_data, %struct.private_data* %23, i32 0, i32 0, !dbg !873
  %avail_out = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %stream8, i32 0, i32 4, !dbg !874
  store i64 %22, i64* %avail_out, align 8, !dbg !875
  %24 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !876
  %crc32 = getelementptr inbounds %struct.private_data, %struct.private_data* %24, i32 0, i32 7, !dbg !877
  store i32 0, i32* %crc32, align 4, !dbg !878
  %25 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !879
  %code = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %25, i32 0, i32 12, !dbg !881
  %26 = load i32, i32* %code, align 8, !dbg !881
  %cmp9 = icmp eq i32 %26, 9, !dbg !882
  br i1 %cmp9, label %if.then10, label %if.else, !dbg !883

if.then10:                                        ; preds = %if.end
  %27 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !884
  %in_stream = getelementptr inbounds %struct.private_data, %struct.private_data* %27, i32 0, i32 5, !dbg !886
  store i8 0, i8* %in_stream, align 1, !dbg !887
  store i32 0, i32* %retval, align 4, !dbg !888
  br label %return, !dbg !888

if.else:                                          ; preds = %if.end
  %28 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !889
  %in_stream11 = getelementptr inbounds %struct.private_data, %struct.private_data* %28, i32 0, i32 5, !dbg !890
  store i8 1, i8* %in_stream11, align 1, !dbg !891
  br label %if.end12

if.end12:                                         ; preds = %if.else
  %29 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !892
  %code13 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %29, i32 0, i32 12, !dbg !894
  %30 = load i32, i32* %code13, align 8, !dbg !894
  %cmp14 = icmp eq i32 %30, 6, !dbg !895
  br i1 %cmp14, label %if.then15, label %if.else18, !dbg !896

if.then15:                                        ; preds = %if.end12
  %31 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !897
  %stream16 = getelementptr inbounds %struct.private_data, %struct.private_data* %31, i32 0, i32 0, !dbg !898
  %call17 = call i32 @lzma_stream_decoder(%struct.lzma_stream* %stream16, i64 -1, i32 8) #7, !dbg !899
  store i32 %call17, i32* %ret, align 4, !dbg !900
  br label %if.end21, !dbg !901

if.else18:                                        ; preds = %if.end12
  %32 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !902
  %stream19 = getelementptr inbounds %struct.private_data, %struct.private_data* %32, i32 0, i32 0, !dbg !903
  %call20 = call i32 @lzma_alone_decoder(%struct.lzma_stream* %stream19, i64 -1) #7, !dbg !904
  store i32 %call20, i32* %ret, align 4, !dbg !905
  br label %if.end21

if.end21:                                         ; preds = %if.else18, %if.then15
  %33 = load i32, i32* %ret, align 4, !dbg !906
  %cmp22 = icmp eq i32 %33, 0, !dbg !908
  br i1 %cmp22, label %if.then23, label %if.end24, !dbg !909

if.then23:                                        ; preds = %if.end21
  store i32 0, i32* %retval, align 4, !dbg !910
  br label %return, !dbg !910

if.end24:                                         ; preds = %if.end21
  %34 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !911
  %35 = load i32, i32* %ret, align 4, !dbg !912
  call void @set_error(%struct.archive_read_filter* %34, i32 %35), !dbg !913
  %36 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !914
  %out_block25 = getelementptr inbounds %struct.private_data, %struct.private_data* %36, i32 0, i32 1, !dbg !915
  %37 = load i8*, i8** %out_block25, align 8, !dbg !915
  call void @free(i8* %37) #7, !dbg !916
  %38 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !917
  %39 = bitcast %struct.private_data* %38 to i8*, !dbg !917
  call void @free(i8* %39) #7, !dbg !918
  %40 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !919
  %data26 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %40, i32 0, i32 10, !dbg !920
  store i8* null, i8** %data26, align 8, !dbg !921
  store i32 -30, i32* %retval, align 4, !dbg !922
  br label %return, !dbg !922

return:                                           ; preds = %if.end24, %if.then23, %if.then10, %if.then
  %41 = load i32, i32* %retval, align 4, !dbg !923
  ret i32 %41, !dbg !923
}

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #5

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #5

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

; Function Attrs: nounwind
declare void @free(i8*) #5

; Function Attrs: nounwind uwtable
define internal i64 @xz_filter_read(%struct.archive_read_filter* %self, i8** %p) #0 !dbg !397 {
entry:
  %retval = alloca i64, align 8
  %self.addr = alloca %struct.archive_read_filter*, align 8
  %p.addr = alloca i8**, align 8
  %state = alloca %struct.private_data*, align 8
  %decompressed = alloca i64, align 8
  %avail_in = alloca i64, align 8
  %ret = alloca i32, align 4
  store %struct.archive_read_filter* %self, %struct.archive_read_filter** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %self.addr, metadata !924, metadata !416), !dbg !925
  store i8** %p, i8*** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %p.addr, metadata !926, metadata !416), !dbg !927
  call void @llvm.dbg.declare(metadata %struct.private_data** %state, metadata !928, metadata !416), !dbg !929
  call void @llvm.dbg.declare(metadata i64* %decompressed, metadata !930, metadata !416), !dbg !931
  call void @llvm.dbg.declare(metadata i64* %avail_in, metadata !932, metadata !416), !dbg !933
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !934, metadata !416), !dbg !935
  %0 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !936
  %data = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %0, i32 0, i32 10, !dbg !937
  %1 = load i8*, i8** %data, align 8, !dbg !937
  %2 = bitcast i8* %1 to %struct.private_data*, !dbg !938
  store %struct.private_data* %2, %struct.private_data** %state, align 8, !dbg !939
  %3 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !940
  %out_block = getelementptr inbounds %struct.private_data, %struct.private_data* %3, i32 0, i32 1, !dbg !941
  %4 = load i8*, i8** %out_block, align 8, !dbg !941
  %5 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !942
  %stream = getelementptr inbounds %struct.private_data, %struct.private_data* %5, i32 0, i32 0, !dbg !943
  %next_out = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %stream, i32 0, i32 3, !dbg !944
  store i8* %4, i8** %next_out, align 8, !dbg !945
  %6 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !946
  %out_block_size = getelementptr inbounds %struct.private_data, %struct.private_data* %6, i32 0, i32 2, !dbg !947
  %7 = load i64, i64* %out_block_size, align 8, !dbg !947
  %8 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !948
  %stream1 = getelementptr inbounds %struct.private_data, %struct.private_data* %8, i32 0, i32 0, !dbg !949
  %avail_out = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %stream1, i32 0, i32 4, !dbg !950
  store i64 %7, i64* %avail_out, align 8, !dbg !951
  br label %while.cond, !dbg !952

while.cond:                                       ; preds = %sw.epilog, %entry
  %9 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !953
  %stream2 = getelementptr inbounds %struct.private_data, %struct.private_data* %9, i32 0, i32 0, !dbg !955
  %avail_out3 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %stream2, i32 0, i32 4, !dbg !956
  %10 = load i64, i64* %avail_out3, align 8, !dbg !956
  %cmp = icmp ugt i64 %10, 0, !dbg !957
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !958

land.rhs:                                         ; preds = %while.cond
  %11 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !959
  %eof = getelementptr inbounds %struct.private_data, %struct.private_data* %11, i32 0, i32 4, !dbg !961
  %12 = load i8, i8* %eof, align 8, !dbg !961
  %tobool = icmp ne i8 %12, 0, !dbg !962
  %lnot = xor i1 %tobool, true, !dbg !962
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond
  %13 = phi i1 [ false, %while.cond ], [ %lnot, %land.rhs ]
  br i1 %13, label %while.body, label %while.end, !dbg !963

while.body:                                       ; preds = %land.end
  %14 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !965
  %in_stream = getelementptr inbounds %struct.private_data, %struct.private_data* %14, i32 0, i32 5, !dbg !968
  %15 = load i8, i8* %in_stream, align 1, !dbg !968
  %tobool4 = icmp ne i8 %15, 0, !dbg !965
  br i1 %tobool4, label %if.end8, label %if.then, !dbg !969

if.then:                                          ; preds = %while.body
  %16 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !970
  %call = call i32 @lzip_init(%struct.archive_read_filter* %16), !dbg !972
  store i32 %call, i32* %ret, align 4, !dbg !973
  %17 = load i32, i32* %ret, align 4, !dbg !974
  %cmp5 = icmp ne i32 %17, 0, !dbg !976
  br i1 %cmp5, label %if.then6, label %if.end, !dbg !977

if.then6:                                         ; preds = %if.then
  %18 = load i32, i32* %ret, align 4, !dbg !978
  %conv = sext i32 %18 to i64, !dbg !979
  store i64 %conv, i64* %retval, align 8, !dbg !980
  br label %return, !dbg !980

if.end:                                           ; preds = %if.then
  %19 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !981
  %in_stream7 = getelementptr inbounds %struct.private_data, %struct.private_data* %19, i32 0, i32 5, !dbg !982
  store i8 1, i8* %in_stream7, align 1, !dbg !983
  br label %if.end8, !dbg !984

if.end8:                                          ; preds = %if.end, %while.body
  %20 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !985
  %upstream = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %20, i32 0, i32 2, !dbg !986
  %21 = load %struct.archive_read_filter*, %struct.archive_read_filter** %upstream, align 8, !dbg !986
  %call9 = call i8* @__archive_read_filter_ahead(%struct.archive_read_filter* %21, i64 1, i64* %avail_in), !dbg !987
  %22 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !988
  %stream10 = getelementptr inbounds %struct.private_data, %struct.private_data* %22, i32 0, i32 0, !dbg !989
  %next_in = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %stream10, i32 0, i32 0, !dbg !990
  store i8* %call9, i8** %next_in, align 8, !dbg !991
  %23 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !992
  %stream11 = getelementptr inbounds %struct.private_data, %struct.private_data* %23, i32 0, i32 0, !dbg !994
  %next_in12 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %stream11, i32 0, i32 0, !dbg !995
  %24 = load i8*, i8** %next_in12, align 8, !dbg !995
  %cmp13 = icmp eq i8* %24, null, !dbg !996
  br i1 %cmp13, label %land.lhs.true, label %if.end19, !dbg !997

land.lhs.true:                                    ; preds = %if.end8
  %25 = load i64, i64* %avail_in, align 8, !dbg !998
  %cmp15 = icmp slt i64 %25, 0, !dbg !1000
  br i1 %cmp15, label %if.then17, label %if.end19, !dbg !1001

if.then17:                                        ; preds = %land.lhs.true
  %26 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1002
  %archive = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %26, i32 0, i32 3, !dbg !1004
  %27 = load %struct.archive_read*, %struct.archive_read** %archive, align 8, !dbg !1004
  %archive18 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %27, i32 0, i32 0, !dbg !1005
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive18, i32 -1, i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.9, i32 0, i32 0)), !dbg !1006
  store i64 -30, i64* %retval, align 8, !dbg !1007
  br label %return, !dbg !1007

if.end19:                                         ; preds = %land.lhs.true, %if.end8
  %28 = load i64, i64* %avail_in, align 8, !dbg !1008
  %29 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1009
  %stream20 = getelementptr inbounds %struct.private_data, %struct.private_data* %29, i32 0, i32 0, !dbg !1010
  %avail_in21 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %stream20, i32 0, i32 1, !dbg !1011
  store i64 %28, i64* %avail_in21, align 8, !dbg !1012
  %30 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1013
  %stream22 = getelementptr inbounds %struct.private_data, %struct.private_data* %30, i32 0, i32 0, !dbg !1014
  %31 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1015
  %stream23 = getelementptr inbounds %struct.private_data, %struct.private_data* %31, i32 0, i32 0, !dbg !1016
  %avail_in24 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %stream23, i32 0, i32 1, !dbg !1017
  %32 = load i64, i64* %avail_in24, align 8, !dbg !1017
  %cmp25 = icmp eq i64 %32, 0, !dbg !1018
  %cond = select i1 %cmp25, i32 3, i32 0, !dbg !1019
  %call27 = call i32 @lzma_code(%struct.lzma_stream* %stream22, i32 %cond) #7, !dbg !1020
  store i32 %call27, i32* %ret, align 4, !dbg !1021
  %33 = load i32, i32* %ret, align 4, !dbg !1022
  switch i32 %33, label %sw.default [
    i32 1, label %sw.bb
    i32 0, label %sw.bb29
  ], !dbg !1023

sw.bb:                                            ; preds = %if.end19
  %34 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1024
  %eof28 = getelementptr inbounds %struct.private_data, %struct.private_data* %34, i32 0, i32 4, !dbg !1026
  store i8 1, i8* %eof28, align 8, !dbg !1027
  br label %sw.bb29, !dbg !1024

sw.bb29:                                          ; preds = %if.end19, %sw.bb
  %35 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1028
  %upstream30 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %35, i32 0, i32 2, !dbg !1029
  %36 = load %struct.archive_read_filter*, %struct.archive_read_filter** %upstream30, align 8, !dbg !1029
  %37 = load i64, i64* %avail_in, align 8, !dbg !1030
  %38 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1031
  %stream31 = getelementptr inbounds %struct.private_data, %struct.private_data* %38, i32 0, i32 0, !dbg !1032
  %avail_in32 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %stream31, i32 0, i32 1, !dbg !1033
  %39 = load i64, i64* %avail_in32, align 8, !dbg !1033
  %sub = sub i64 %37, %39, !dbg !1034
  %call33 = call i64 @__archive_read_filter_consume(%struct.archive_read_filter* %36, i64 %sub), !dbg !1035
  %40 = load i64, i64* %avail_in, align 8, !dbg !1036
  %41 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1037
  %stream34 = getelementptr inbounds %struct.private_data, %struct.private_data* %41, i32 0, i32 0, !dbg !1038
  %avail_in35 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %stream34, i32 0, i32 1, !dbg !1039
  %42 = load i64, i64* %avail_in35, align 8, !dbg !1039
  %sub36 = sub i64 %40, %42, !dbg !1040
  %43 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1041
  %member_in = getelementptr inbounds %struct.private_data, %struct.private_data* %43, i32 0, i32 8, !dbg !1042
  %44 = load i64, i64* %member_in, align 8, !dbg !1043
  %add = add i64 %44, %sub36, !dbg !1043
  store i64 %add, i64* %member_in, align 8, !dbg !1043
  br label %sw.epilog, !dbg !1044

sw.default:                                       ; preds = %if.end19
  %45 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1045
  %46 = load i32, i32* %ret, align 4, !dbg !1046
  call void @set_error(%struct.archive_read_filter* %45, i32 %46), !dbg !1047
  store i64 -30, i64* %retval, align 8, !dbg !1048
  br label %return, !dbg !1048

sw.epilog:                                        ; preds = %sw.bb29
  br label %while.cond, !dbg !1049

while.end:                                        ; preds = %land.end
  %47 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1051
  %stream37 = getelementptr inbounds %struct.private_data, %struct.private_data* %47, i32 0, i32 0, !dbg !1052
  %next_out38 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %stream37, i32 0, i32 3, !dbg !1053
  %48 = load i8*, i8** %next_out38, align 8, !dbg !1053
  %49 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1054
  %out_block39 = getelementptr inbounds %struct.private_data, %struct.private_data* %49, i32 0, i32 1, !dbg !1055
  %50 = load i8*, i8** %out_block39, align 8, !dbg !1055
  %sub.ptr.lhs.cast = ptrtoint i8* %48 to i64, !dbg !1056
  %sub.ptr.rhs.cast = ptrtoint i8* %50 to i64, !dbg !1056
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !1056
  store i64 %sub.ptr.sub, i64* %decompressed, align 8, !dbg !1057
  %51 = load i64, i64* %decompressed, align 8, !dbg !1058
  %52 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1059
  %total_out = getelementptr inbounds %struct.private_data, %struct.private_data* %52, i32 0, i32 3, !dbg !1060
  %53 = load i64, i64* %total_out, align 8, !dbg !1061
  %add40 = add i64 %53, %51, !dbg !1061
  store i64 %add40, i64* %total_out, align 8, !dbg !1061
  %54 = load i64, i64* %decompressed, align 8, !dbg !1062
  %55 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1063
  %member_out = getelementptr inbounds %struct.private_data, %struct.private_data* %55, i32 0, i32 9, !dbg !1064
  %56 = load i64, i64* %member_out, align 8, !dbg !1065
  %add41 = add i64 %56, %54, !dbg !1065
  store i64 %add41, i64* %member_out, align 8, !dbg !1065
  %57 = load i64, i64* %decompressed, align 8, !dbg !1066
  %cmp42 = icmp eq i64 %57, 0, !dbg !1068
  br i1 %cmp42, label %if.then44, label %if.else, !dbg !1069

if.then44:                                        ; preds = %while.end
  %58 = load i8**, i8*** %p.addr, align 8, !dbg !1070
  store i8* null, i8** %58, align 8, !dbg !1071
  br label %if.end63, !dbg !1072

if.else:                                          ; preds = %while.end
  %59 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1073
  %out_block45 = getelementptr inbounds %struct.private_data, %struct.private_data* %59, i32 0, i32 1, !dbg !1075
  %60 = load i8*, i8** %out_block45, align 8, !dbg !1075
  %61 = load i8**, i8*** %p.addr, align 8, !dbg !1076
  store i8* %60, i8** %61, align 8, !dbg !1077
  %62 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1078
  %code = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %62, i32 0, i32 12, !dbg !1080
  %63 = load i32, i32* %code, align 8, !dbg !1080
  %cmp46 = icmp eq i32 %63, 9, !dbg !1081
  br i1 %cmp46, label %if.then48, label %if.end62, !dbg !1082

if.then48:                                        ; preds = %if.else
  %64 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1083
  %out_block49 = getelementptr inbounds %struct.private_data, %struct.private_data* %64, i32 0, i32 1, !dbg !1085
  %65 = load i8*, i8** %out_block49, align 8, !dbg !1085
  %66 = load i64, i64* %decompressed, align 8, !dbg !1086
  %67 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1087
  %crc32 = getelementptr inbounds %struct.private_data, %struct.private_data* %67, i32 0, i32 7, !dbg !1088
  %68 = load i32, i32* %crc32, align 4, !dbg !1088
  %call50 = call i32 @lzma_crc32(i8* %65, i64 %66, i32 %68) #6, !dbg !1089
  %69 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1090
  %crc3251 = getelementptr inbounds %struct.private_data, %struct.private_data* %69, i32 0, i32 7, !dbg !1091
  store i32 %call50, i32* %crc3251, align 4, !dbg !1092
  %70 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1093
  %eof52 = getelementptr inbounds %struct.private_data, %struct.private_data* %70, i32 0, i32 4, !dbg !1095
  %71 = load i8, i8* %eof52, align 8, !dbg !1095
  %tobool53 = icmp ne i8 %71, 0, !dbg !1093
  br i1 %tobool53, label %if.then54, label %if.end61, !dbg !1096

if.then54:                                        ; preds = %if.then48
  %72 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1097
  %call55 = call i32 @lzip_tail(%struct.archive_read_filter* %72), !dbg !1099
  store i32 %call55, i32* %ret, align 4, !dbg !1100
  %73 = load i32, i32* %ret, align 4, !dbg !1101
  %cmp56 = icmp ne i32 %73, 0, !dbg !1103
  br i1 %cmp56, label %if.then58, label %if.end60, !dbg !1104

if.then58:                                        ; preds = %if.then54
  %74 = load i32, i32* %ret, align 4, !dbg !1105
  %conv59 = sext i32 %74 to i64, !dbg !1106
  store i64 %conv59, i64* %retval, align 8, !dbg !1107
  br label %return, !dbg !1107

if.end60:                                         ; preds = %if.then54
  br label %if.end61, !dbg !1108

if.end61:                                         ; preds = %if.end60, %if.then48
  br label %if.end62, !dbg !1109

if.end62:                                         ; preds = %if.end61, %if.else
  br label %if.end63

if.end63:                                         ; preds = %if.end62, %if.then44
  %75 = load i64, i64* %decompressed, align 8, !dbg !1110
  store i64 %75, i64* %retval, align 8, !dbg !1111
  br label %return, !dbg !1111

return:                                           ; preds = %if.end63, %if.then58, %sw.default, %if.then17, %if.then6
  %76 = load i64, i64* %retval, align 8, !dbg !1112
  ret i64 %76, !dbg !1112
}

; Function Attrs: nounwind uwtable
define internal i32 @xz_filter_close(%struct.archive_read_filter* %self) #0 !dbg !403 {
entry:
  %self.addr = alloca %struct.archive_read_filter*, align 8
  %state = alloca %struct.private_data*, align 8
  store %struct.archive_read_filter* %self, %struct.archive_read_filter** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %self.addr, metadata !1113, metadata !416), !dbg !1114
  call void @llvm.dbg.declare(metadata %struct.private_data** %state, metadata !1115, metadata !416), !dbg !1116
  %0 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1117
  %data = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %0, i32 0, i32 10, !dbg !1118
  %1 = load i8*, i8** %data, align 8, !dbg !1118
  %2 = bitcast i8* %1 to %struct.private_data*, !dbg !1119
  store %struct.private_data* %2, %struct.private_data** %state, align 8, !dbg !1120
  %3 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1121
  %stream = getelementptr inbounds %struct.private_data, %struct.private_data* %3, i32 0, i32 0, !dbg !1122
  call void @lzma_end(%struct.lzma_stream* %stream) #7, !dbg !1123
  %4 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1124
  %out_block = getelementptr inbounds %struct.private_data, %struct.private_data* %4, i32 0, i32 1, !dbg !1125
  %5 = load i8*, i8** %out_block, align 8, !dbg !1125
  call void @free(i8* %5) #7, !dbg !1126
  %6 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1127
  %7 = bitcast %struct.private_data* %6 to i8*, !dbg !1127
  call void @free(i8* %7) #7, !dbg !1128
  ret i32 0, !dbg !1129
}

; Function Attrs: nounwind
declare i32 @lzma_stream_decoder(%struct.lzma_stream*, i64, i32) #5

; Function Attrs: nounwind
declare i32 @lzma_alone_decoder(%struct.lzma_stream*, i64) #5

; Function Attrs: nounwind uwtable
define internal void @set_error(%struct.archive_read_filter* %self, i32 %ret) #0 !dbg !404 {
entry:
  %self.addr = alloca %struct.archive_read_filter*, align 8
  %ret.addr = alloca i32, align 4
  store %struct.archive_read_filter* %self, %struct.archive_read_filter** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %self.addr, metadata !1130, metadata !416), !dbg !1131
  store i32 %ret, i32* %ret.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %ret.addr, metadata !1132, metadata !416), !dbg !1133
  %0 = load i32, i32* %ret.addr, align 4, !dbg !1134
  switch i32 %0, label %sw.default [
    i32 1, label %sw.bb
    i32 0, label %sw.bb
    i32 5, label %sw.bb1
    i32 6, label %sw.bb3
    i32 7, label %sw.bb6
    i32 8, label %sw.bb9
    i32 9, label %sw.bb12
    i32 10, label %sw.bb15
  ], !dbg !1135

sw.bb:                                            ; preds = %entry, %entry
  br label %sw.epilog, !dbg !1136

sw.bb1:                                           ; preds = %entry
  %1 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1138
  %archive = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %1, i32 0, i32 3, !dbg !1139
  %2 = load %struct.archive_read*, %struct.archive_read** %archive, align 8, !dbg !1139
  %archive2 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %2, i32 0, i32 0, !dbg !1140
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive2, i32 12, i8* getelementptr inbounds ([43 x i8], [43 x i8]* @.str.14, i32 0, i32 0)), !dbg !1141
  br label %sw.epilog, !dbg !1142

sw.bb3:                                           ; preds = %entry
  %3 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1143
  %archive4 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %3, i32 0, i32 3, !dbg !1144
  %4 = load %struct.archive_read*, %struct.archive_read** %archive4, align 8, !dbg !1144
  %archive5 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %4, i32 0, i32 0, !dbg !1145
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive5, i32 12, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.15, i32 0, i32 0)), !dbg !1146
  br label %sw.epilog, !dbg !1147

sw.bb6:                                           ; preds = %entry
  %5 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1148
  %archive7 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %5, i32 0, i32 3, !dbg !1149
  %6 = load %struct.archive_read*, %struct.archive_read** %archive7, align 8, !dbg !1149
  %archive8 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %6, i32 0, i32 0, !dbg !1150
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive8, i32 -1, i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.16, i32 0, i32 0)), !dbg !1151
  br label %sw.epilog, !dbg !1152

sw.bb9:                                           ; preds = %entry
  %7 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1153
  %archive10 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %7, i32 0, i32 3, !dbg !1154
  %8 = load %struct.archive_read*, %struct.archive_read** %archive10, align 8, !dbg !1154
  %archive11 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %8, i32 0, i32 0, !dbg !1155
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive11, i32 -1, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.17, i32 0, i32 0)), !dbg !1156
  br label %sw.epilog, !dbg !1157

sw.bb12:                                          ; preds = %entry
  %9 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1158
  %archive13 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %9, i32 0, i32 3, !dbg !1159
  %10 = load %struct.archive_read*, %struct.archive_read** %archive13, align 8, !dbg !1159
  %archive14 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %10, i32 0, i32 0, !dbg !1160
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive14, i32 -1, i8* getelementptr inbounds ([41 x i8], [41 x i8]* @.str.18, i32 0, i32 0)), !dbg !1161
  br label %sw.epilog, !dbg !1162

sw.bb15:                                          ; preds = %entry
  %11 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1163
  %archive16 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %11, i32 0, i32 3, !dbg !1164
  %12 = load %struct.archive_read*, %struct.archive_read** %archive16, align 8, !dbg !1164
  %archive17 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %12, i32 0, i32 0, !dbg !1165
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive17, i32 -1, i8* getelementptr inbounds ([45 x i8], [45 x i8]* @.str.19, i32 0, i32 0)), !dbg !1166
  br label %sw.epilog, !dbg !1167

sw.default:                                       ; preds = %entry
  %13 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1168
  %archive18 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %13, i32 0, i32 3, !dbg !1169
  %14 = load %struct.archive_read*, %struct.archive_read** %archive18, align 8, !dbg !1169
  %archive19 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %14, i32 0, i32 0, !dbg !1170
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive19, i32 -1, i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.20, i32 0, i32 0)), !dbg !1171
  br label %sw.epilog, !dbg !1172

sw.epilog:                                        ; preds = %sw.default, %sw.bb15, %sw.bb12, %sw.bb9, %sw.bb6, %sw.bb3, %sw.bb1, %sw.bb
  ret void, !dbg !1173
}

; Function Attrs: nounwind uwtable
define internal i32 @lzip_init(%struct.archive_read_filter* %self) #0 !dbg !398 {
entry:
  %retval = alloca i32, align 4
  %self.addr = alloca %struct.archive_read_filter*, align 8
  %state = alloca %struct.private_data*, align 8
  %h = alloca i8*, align 8
  %filters = alloca [2 x %struct.lzma_filter], align 16
  %props = alloca [5 x i8], align 1
  %avail_in = alloca i64, align 8
  %dicsize = alloca i32, align 4
  %log2dic = alloca i32, align 4
  %ret = alloca i32, align 4
  store %struct.archive_read_filter* %self, %struct.archive_read_filter** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %self.addr, metadata !1174, metadata !416), !dbg !1175
  call void @llvm.dbg.declare(metadata %struct.private_data** %state, metadata !1176, metadata !416), !dbg !1177
  call void @llvm.dbg.declare(metadata i8** %h, metadata !1178, metadata !416), !dbg !1179
  call void @llvm.dbg.declare(metadata [2 x %struct.lzma_filter]* %filters, metadata !1180, metadata !416), !dbg !1192
  call void @llvm.dbg.declare(metadata [5 x i8]* %props, metadata !1193, metadata !416), !dbg !1197
  call void @llvm.dbg.declare(metadata i64* %avail_in, metadata !1198, metadata !416), !dbg !1199
  call void @llvm.dbg.declare(metadata i32* %dicsize, metadata !1200, metadata !416), !dbg !1201
  call void @llvm.dbg.declare(metadata i32* %log2dic, metadata !1202, metadata !416), !dbg !1203
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !1204, metadata !416), !dbg !1205
  %0 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1206
  %data = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %0, i32 0, i32 10, !dbg !1207
  %1 = load i8*, i8** %data, align 8, !dbg !1207
  %2 = bitcast i8* %1 to %struct.private_data*, !dbg !1208
  store %struct.private_data* %2, %struct.private_data** %state, align 8, !dbg !1209
  %3 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1210
  %upstream = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %3, i32 0, i32 2, !dbg !1211
  %4 = load %struct.archive_read_filter*, %struct.archive_read_filter** %upstream, align 8, !dbg !1211
  %call = call i8* @__archive_read_filter_ahead(%struct.archive_read_filter* %4, i64 6, i64* %avail_in), !dbg !1212
  store i8* %call, i8** %h, align 8, !dbg !1213
  %5 = load i8*, i8** %h, align 8, !dbg !1214
  %cmp = icmp eq i8* %5, null, !dbg !1216
  br i1 %cmp, label %if.then, label %if.end, !dbg !1217

if.then:                                          ; preds = %entry
  store i32 -30, i32* %retval, align 4, !dbg !1218
  br label %return, !dbg !1218

if.end:                                           ; preds = %entry
  %6 = load i8*, i8** %h, align 8, !dbg !1219
  %arrayidx = getelementptr inbounds i8, i8* %6, i64 4, !dbg !1219
  %7 = load i8, i8* %arrayidx, align 1, !dbg !1219
  %8 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1220
  %lzip_ver = getelementptr inbounds %struct.private_data, %struct.private_data* %8, i32 0, i32 6, !dbg !1221
  store i8 %7, i8* %lzip_ver, align 2, !dbg !1222
  %arrayidx1 = getelementptr inbounds [5 x i8], [5 x i8]* %props, i64 0, i64 0, !dbg !1223
  store i8 93, i8* %arrayidx1, align 1, !dbg !1224
  %9 = load i8*, i8** %h, align 8, !dbg !1225
  %arrayidx2 = getelementptr inbounds i8, i8* %9, i64 5, !dbg !1225
  %10 = load i8, i8* %arrayidx2, align 1, !dbg !1225
  %conv = zext i8 %10 to i32, !dbg !1225
  %and = and i32 %conv, 31, !dbg !1226
  store i32 %and, i32* %log2dic, align 4, !dbg !1227
  %11 = load i32, i32* %log2dic, align 4, !dbg !1228
  %cmp3 = icmp slt i32 %11, 12, !dbg !1230
  br i1 %cmp3, label %if.then7, label %lor.lhs.false, !dbg !1231

lor.lhs.false:                                    ; preds = %if.end
  %12 = load i32, i32* %log2dic, align 4, !dbg !1232
  %cmp5 = icmp sgt i32 %12, 27, !dbg !1234
  br i1 %cmp5, label %if.then7, label %if.end8, !dbg !1235

if.then7:                                         ; preds = %lor.lhs.false, %if.end
  store i32 -30, i32* %retval, align 4, !dbg !1236
  br label %return, !dbg !1236

if.end8:                                          ; preds = %lor.lhs.false
  %13 = load i32, i32* %log2dic, align 4, !dbg !1237
  %shl = shl i32 1, %13, !dbg !1238
  store i32 %shl, i32* %dicsize, align 4, !dbg !1239
  %14 = load i32, i32* %log2dic, align 4, !dbg !1240
  %cmp9 = icmp sgt i32 %14, 12, !dbg !1242
  br i1 %cmp9, label %if.then11, label %if.end14, !dbg !1243

if.then11:                                        ; preds = %if.end8
  %15 = load i32, i32* %dicsize, align 4, !dbg !1244
  %div = udiv i32 %15, 16, !dbg !1245
  %16 = load i8*, i8** %h, align 8, !dbg !1246
  %arrayidx12 = getelementptr inbounds i8, i8* %16, i64 5, !dbg !1246
  %17 = load i8, i8* %arrayidx12, align 1, !dbg !1246
  %conv13 = zext i8 %17 to i32, !dbg !1246
  %shr = ashr i32 %conv13, 5, !dbg !1247
  %mul = mul i32 %div, %shr, !dbg !1248
  %18 = load i32, i32* %dicsize, align 4, !dbg !1249
  %sub = sub i32 %18, %mul, !dbg !1249
  store i32 %sub, i32* %dicsize, align 4, !dbg !1249
  br label %if.end14, !dbg !1250

if.end14:                                         ; preds = %if.then11, %if.end8
  %arraydecay = getelementptr inbounds [5 x i8], [5 x i8]* %props, i32 0, i32 0, !dbg !1251
  %add.ptr = getelementptr inbounds i8, i8* %arraydecay, i64 1, !dbg !1252
  %19 = load i32, i32* %dicsize, align 4, !dbg !1253
  call void @archive_le32enc(i8* %add.ptr, i32 %19), !dbg !1254
  %20 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1255
  %upstream15 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %20, i32 0, i32 2, !dbg !1256
  %21 = load %struct.archive_read_filter*, %struct.archive_read_filter** %upstream15, align 8, !dbg !1256
  %call16 = call i64 @__archive_read_filter_consume(%struct.archive_read_filter* %21, i64 6), !dbg !1257
  %22 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1258
  %member_in = getelementptr inbounds %struct.private_data, %struct.private_data* %22, i32 0, i32 8, !dbg !1259
  store i64 6, i64* %member_in, align 8, !dbg !1260
  %arrayidx17 = getelementptr inbounds [2 x %struct.lzma_filter], [2 x %struct.lzma_filter]* %filters, i64 0, i64 0, !dbg !1261
  %id = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx17, i32 0, i32 0, !dbg !1262
  store i64 4611686018427387905, i64* %id, align 16, !dbg !1263
  %arrayidx18 = getelementptr inbounds [2 x %struct.lzma_filter], [2 x %struct.lzma_filter]* %filters, i64 0, i64 0, !dbg !1264
  %options = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx18, i32 0, i32 1, !dbg !1265
  store i8* null, i8** %options, align 8, !dbg !1266
  %arrayidx19 = getelementptr inbounds [2 x %struct.lzma_filter], [2 x %struct.lzma_filter]* %filters, i64 0, i64 1, !dbg !1267
  %id20 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx19, i32 0, i32 0, !dbg !1268
  store i64 -1, i64* %id20, align 16, !dbg !1269
  %arrayidx21 = getelementptr inbounds [2 x %struct.lzma_filter], [2 x %struct.lzma_filter]* %filters, i64 0, i64 1, !dbg !1270
  %options22 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx21, i32 0, i32 1, !dbg !1271
  store i8* null, i8** %options22, align 8, !dbg !1272
  %arrayidx23 = getelementptr inbounds [2 x %struct.lzma_filter], [2 x %struct.lzma_filter]* %filters, i64 0, i64 0, !dbg !1273
  %arraydecay24 = getelementptr inbounds [5 x i8], [5 x i8]* %props, i32 0, i32 0, !dbg !1274
  %call25 = call i32 @lzma_properties_decode(%struct.lzma_filter* %arrayidx23, %struct.lzma_allocator* null, i8* %arraydecay24, i64 5) #7, !dbg !1275
  store i32 %call25, i32* %ret, align 4, !dbg !1276
  %23 = load i32, i32* %ret, align 4, !dbg !1277
  %cmp26 = icmp ne i32 %23, 0, !dbg !1279
  br i1 %cmp26, label %if.then28, label %if.end29, !dbg !1280

if.then28:                                        ; preds = %if.end14
  %24 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1281
  %25 = load i32, i32* %ret, align 4, !dbg !1283
  call void @set_error(%struct.archive_read_filter* %24, i32 %25), !dbg !1284
  store i32 -30, i32* %retval, align 4, !dbg !1285
  br label %return, !dbg !1285

if.end29:                                         ; preds = %if.end14
  %26 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1286
  %stream = getelementptr inbounds %struct.private_data, %struct.private_data* %26, i32 0, i32 0, !dbg !1287
  %arraydecay30 = getelementptr inbounds [2 x %struct.lzma_filter], [2 x %struct.lzma_filter]* %filters, i32 0, i32 0, !dbg !1288
  %call31 = call i32 @lzma_raw_decoder(%struct.lzma_stream* %stream, %struct.lzma_filter* %arraydecay30) #7, !dbg !1289
  store i32 %call31, i32* %ret, align 4, !dbg !1290
  %arrayidx32 = getelementptr inbounds [2 x %struct.lzma_filter], [2 x %struct.lzma_filter]* %filters, i64 0, i64 0, !dbg !1291
  %options33 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %arrayidx32, i32 0, i32 1, !dbg !1292
  %27 = load i8*, i8** %options33, align 8, !dbg !1292
  call void @free(i8* %27) #7, !dbg !1293
  %28 = load i32, i32* %ret, align 4, !dbg !1294
  %cmp34 = icmp ne i32 %28, 0, !dbg !1296
  br i1 %cmp34, label %if.then36, label %if.end37, !dbg !1297

if.then36:                                        ; preds = %if.end29
  %29 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1298
  %30 = load i32, i32* %ret, align 4, !dbg !1300
  call void @set_error(%struct.archive_read_filter* %29, i32 %30), !dbg !1301
  store i32 -30, i32* %retval, align 4, !dbg !1302
  br label %return, !dbg !1302

if.end37:                                         ; preds = %if.end29
  store i32 0, i32* %retval, align 4, !dbg !1303
  br label %return, !dbg !1303

return:                                           ; preds = %if.end37, %if.then36, %if.then28, %if.then7, %if.then
  %31 = load i32, i32* %retval, align 4, !dbg !1304
  ret i32 %31, !dbg !1304
}

; Function Attrs: nounwind
declare i32 @lzma_code(%struct.lzma_stream*, i32) #5

declare i64 @__archive_read_filter_consume(%struct.archive_read_filter*, i64) #2

; Function Attrs: nounwind readonly
declare i32 @lzma_crc32(i8*, i64, i32) #3

; Function Attrs: nounwind uwtable
define internal i32 @lzip_tail(%struct.archive_read_filter* %self) #0 !dbg !402 {
entry:
  %retval = alloca i32, align 4
  %self.addr = alloca %struct.archive_read_filter*, align 8
  %state = alloca %struct.private_data*, align 8
  %f = alloca i8*, align 8
  %avail_in = alloca i64, align 8
  %tail = alloca i32, align 4
  store %struct.archive_read_filter* %self, %struct.archive_read_filter** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %self.addr, metadata !1305, metadata !416), !dbg !1306
  call void @llvm.dbg.declare(metadata %struct.private_data** %state, metadata !1307, metadata !416), !dbg !1308
  call void @llvm.dbg.declare(metadata i8** %f, metadata !1309, metadata !416), !dbg !1310
  call void @llvm.dbg.declare(metadata i64* %avail_in, metadata !1311, metadata !416), !dbg !1312
  call void @llvm.dbg.declare(metadata i32* %tail, metadata !1313, metadata !416), !dbg !1314
  %0 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1315
  %data = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %0, i32 0, i32 10, !dbg !1316
  %1 = load i8*, i8** %data, align 8, !dbg !1316
  %2 = bitcast i8* %1 to %struct.private_data*, !dbg !1317
  store %struct.private_data* %2, %struct.private_data** %state, align 8, !dbg !1318
  %3 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1319
  %lzip_ver = getelementptr inbounds %struct.private_data, %struct.private_data* %3, i32 0, i32 6, !dbg !1321
  %4 = load i8, i8* %lzip_ver, align 2, !dbg !1321
  %conv = sext i8 %4 to i32, !dbg !1319
  %cmp = icmp eq i32 %conv, 0, !dbg !1322
  br i1 %cmp, label %if.then, label %if.else, !dbg !1323

if.then:                                          ; preds = %entry
  store i32 12, i32* %tail, align 4, !dbg !1324
  br label %if.end, !dbg !1325

if.else:                                          ; preds = %entry
  store i32 20, i32* %tail, align 4, !dbg !1326
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %5 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1327
  %upstream = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %5, i32 0, i32 2, !dbg !1328
  %6 = load %struct.archive_read_filter*, %struct.archive_read_filter** %upstream, align 8, !dbg !1328
  %7 = load i32, i32* %tail, align 4, !dbg !1329
  %conv2 = sext i32 %7 to i64, !dbg !1329
  %call = call i8* @__archive_read_filter_ahead(%struct.archive_read_filter* %6, i64 %conv2, i64* %avail_in), !dbg !1330
  store i8* %call, i8** %f, align 8, !dbg !1331
  %8 = load i8*, i8** %f, align 8, !dbg !1332
  %cmp3 = icmp eq i8* %8, null, !dbg !1334
  br i1 %cmp3, label %land.lhs.true, label %if.end8, !dbg !1335

land.lhs.true:                                    ; preds = %if.end
  %9 = load i64, i64* %avail_in, align 8, !dbg !1336
  %cmp5 = icmp slt i64 %9, 0, !dbg !1338
  br i1 %cmp5, label %if.then7, label %if.end8, !dbg !1339

if.then7:                                         ; preds = %land.lhs.true
  store i32 -30, i32* %retval, align 4, !dbg !1340
  br label %return, !dbg !1340

if.end8:                                          ; preds = %land.lhs.true, %if.end
  %10 = load i8*, i8** %f, align 8, !dbg !1341
  %cmp9 = icmp eq i8* %10, null, !dbg !1343
  br i1 %cmp9, label %if.then14, label %lor.lhs.false, !dbg !1344

lor.lhs.false:                                    ; preds = %if.end8
  %11 = load i64, i64* %avail_in, align 8, !dbg !1345
  %12 = load i32, i32* %tail, align 4, !dbg !1347
  %conv11 = sext i32 %12 to i64, !dbg !1347
  %cmp12 = icmp slt i64 %11, %conv11, !dbg !1348
  br i1 %cmp12, label %if.then14, label %if.end16, !dbg !1349

if.then14:                                        ; preds = %lor.lhs.false, %if.end8
  %13 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1350
  %archive = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %13, i32 0, i32 3, !dbg !1352
  %14 = load %struct.archive_read*, %struct.archive_read** %archive, align 8, !dbg !1352
  %archive15 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %14, i32 0, i32 0, !dbg !1353
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive15, i32 -1, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.10, i32 0, i32 0)), !dbg !1354
  store i32 -25, i32* %retval, align 4, !dbg !1355
  br label %return, !dbg !1355

if.end16:                                         ; preds = %lor.lhs.false
  %15 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1356
  %crc32 = getelementptr inbounds %struct.private_data, %struct.private_data* %15, i32 0, i32 7, !dbg !1358
  %16 = load i32, i32* %crc32, align 4, !dbg !1358
  %17 = load i8*, i8** %f, align 8, !dbg !1359
  %call17 = call i32 @archive_le32dec(i8* %17), !dbg !1360
  %cmp18 = icmp ne i32 %16, %call17, !dbg !1361
  br i1 %cmp18, label %if.then20, label %if.end23, !dbg !1362

if.then20:                                        ; preds = %if.end16
  %18 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1363
  %archive21 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %18, i32 0, i32 3, !dbg !1365
  %19 = load %struct.archive_read*, %struct.archive_read** %archive21, align 8, !dbg !1365
  %archive22 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %19, i32 0, i32 0, !dbg !1366
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive22, i32 -1, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.11, i32 0, i32 0)), !dbg !1367
  store i32 -25, i32* %retval, align 4, !dbg !1368
  br label %return, !dbg !1368

if.end23:                                         ; preds = %if.end16
  %20 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1369
  %member_out = getelementptr inbounds %struct.private_data, %struct.private_data* %20, i32 0, i32 9, !dbg !1371
  %21 = load i64, i64* %member_out, align 8, !dbg !1371
  %22 = load i8*, i8** %f, align 8, !dbg !1372
  %add.ptr = getelementptr inbounds i8, i8* %22, i64 4, !dbg !1373
  %call24 = call i64 @archive_le64dec(i8* %add.ptr), !dbg !1374
  %cmp25 = icmp ne i64 %21, %call24, !dbg !1375
  br i1 %cmp25, label %if.then27, label %if.end30, !dbg !1376

if.then27:                                        ; preds = %if.end23
  %23 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1377
  %archive28 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %23, i32 0, i32 3, !dbg !1379
  %24 = load %struct.archive_read*, %struct.archive_read** %archive28, align 8, !dbg !1379
  %archive29 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %24, i32 0, i32 0, !dbg !1380
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive29, i32 -1, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.12, i32 0, i32 0)), !dbg !1381
  store i32 -25, i32* %retval, align 4, !dbg !1382
  br label %return, !dbg !1382

if.end30:                                         ; preds = %if.end23
  %25 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1383
  %lzip_ver31 = getelementptr inbounds %struct.private_data, %struct.private_data* %25, i32 0, i32 6, !dbg !1385
  %26 = load i8, i8* %lzip_ver31, align 2, !dbg !1385
  %conv32 = sext i8 %26 to i32, !dbg !1383
  %cmp33 = icmp eq i32 %conv32, 1, !dbg !1386
  br i1 %cmp33, label %land.lhs.true35, label %if.end44, !dbg !1387

land.lhs.true35:                                  ; preds = %if.end30
  %27 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1388
  %member_in = getelementptr inbounds %struct.private_data, %struct.private_data* %27, i32 0, i32 8, !dbg !1389
  %28 = load i64, i64* %member_in, align 8, !dbg !1389
  %29 = load i32, i32* %tail, align 4, !dbg !1390
  %conv36 = sext i32 %29 to i64, !dbg !1390
  %add = add i64 %28, %conv36, !dbg !1391
  %30 = load i8*, i8** %f, align 8, !dbg !1392
  %add.ptr37 = getelementptr inbounds i8, i8* %30, i64 12, !dbg !1393
  %call38 = call i64 @archive_le64dec(i8* %add.ptr37), !dbg !1394
  %cmp39 = icmp ne i64 %add, %call38, !dbg !1395
  br i1 %cmp39, label %if.then41, label %if.end44, !dbg !1396

if.then41:                                        ; preds = %land.lhs.true35
  %31 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1398
  %archive42 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %31, i32 0, i32 3, !dbg !1400
  %32 = load %struct.archive_read*, %struct.archive_read** %archive42, align 8, !dbg !1400
  %archive43 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %32, i32 0, i32 0, !dbg !1401
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive43, i32 -1, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.13, i32 0, i32 0)), !dbg !1402
  store i32 -25, i32* %retval, align 4, !dbg !1403
  br label %return, !dbg !1403

if.end44:                                         ; preds = %land.lhs.true35, %if.end30
  %33 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1404
  %upstream45 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %33, i32 0, i32 2, !dbg !1405
  %34 = load %struct.archive_read_filter*, %struct.archive_read_filter** %upstream45, align 8, !dbg !1405
  %35 = load i32, i32* %tail, align 4, !dbg !1406
  %conv46 = sext i32 %35 to i64, !dbg !1406
  %call47 = call i64 @__archive_read_filter_consume(%struct.archive_read_filter* %34, i64 %conv46), !dbg !1407
  %36 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !1408
  %upstream48 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %36, i32 0, i32 2, !dbg !1410
  %37 = load %struct.archive_read_filter*, %struct.archive_read_filter** %upstream48, align 8, !dbg !1410
  %call49 = call i32 @lzip_has_member(%struct.archive_read_filter* %37), !dbg !1411
  %cmp50 = icmp ne i32 %call49, 0, !dbg !1412
  br i1 %cmp50, label %if.then52, label %if.end56, !dbg !1413

if.then52:                                        ; preds = %if.end44
  %38 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1414
  %in_stream = getelementptr inbounds %struct.private_data, %struct.private_data* %38, i32 0, i32 5, !dbg !1416
  store i8 0, i8* %in_stream, align 1, !dbg !1417
  %39 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1418
  %crc3253 = getelementptr inbounds %struct.private_data, %struct.private_data* %39, i32 0, i32 7, !dbg !1419
  store i32 0, i32* %crc3253, align 4, !dbg !1420
  %40 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1421
  %member_out54 = getelementptr inbounds %struct.private_data, %struct.private_data* %40, i32 0, i32 9, !dbg !1422
  store i64 0, i64* %member_out54, align 8, !dbg !1423
  %41 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1424
  %member_in55 = getelementptr inbounds %struct.private_data, %struct.private_data* %41, i32 0, i32 8, !dbg !1425
  store i64 0, i64* %member_in55, align 8, !dbg !1426
  %42 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1427
  %eof = getelementptr inbounds %struct.private_data, %struct.private_data* %42, i32 0, i32 4, !dbg !1428
  store i8 0, i8* %eof, align 8, !dbg !1429
  br label %if.end56, !dbg !1430

if.end56:                                         ; preds = %if.then52, %if.end44
  store i32 0, i32* %retval, align 4, !dbg !1431
  br label %return, !dbg !1431

return:                                           ; preds = %if.end56, %if.then41, %if.then27, %if.then20, %if.then14, %if.then7
  %43 = load i32, i32* %retval, align 4, !dbg !1432
  ret i32 %43, !dbg !1432
}

; Function Attrs: inlinehint nounwind uwtable
define internal void @archive_le32enc(i8* %pp, i32 %u) #4 !dbg !399 {
entry:
  %pp.addr = alloca i8*, align 8
  %u.addr = alloca i32, align 4
  %p = alloca i8*, align 8
  store i8* %pp, i8** %pp.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %pp.addr, metadata !1433, metadata !416), !dbg !1434
  store i32 %u, i32* %u.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %u.addr, metadata !1435, metadata !416), !dbg !1436
  call void @llvm.dbg.declare(metadata i8** %p, metadata !1437, metadata !416), !dbg !1438
  %0 = load i8*, i8** %pp.addr, align 8, !dbg !1439
  store i8* %0, i8** %p, align 8, !dbg !1438
  %1 = load i32, i32* %u.addr, align 4, !dbg !1440
  %and = and i32 %1, 255, !dbg !1441
  %conv = trunc i32 %and to i8, !dbg !1440
  %2 = load i8*, i8** %p, align 8, !dbg !1442
  %arrayidx = getelementptr inbounds i8, i8* %2, i64 0, !dbg !1442
  store i8 %conv, i8* %arrayidx, align 1, !dbg !1443
  %3 = load i32, i32* %u.addr, align 4, !dbg !1444
  %shr = lshr i32 %3, 8, !dbg !1445
  %and1 = and i32 %shr, 255, !dbg !1446
  %conv2 = trunc i32 %and1 to i8, !dbg !1447
  %4 = load i8*, i8** %p, align 8, !dbg !1448
  %arrayidx3 = getelementptr inbounds i8, i8* %4, i64 1, !dbg !1448
  store i8 %conv2, i8* %arrayidx3, align 1, !dbg !1449
  %5 = load i32, i32* %u.addr, align 4, !dbg !1450
  %shr4 = lshr i32 %5, 16, !dbg !1451
  %and5 = and i32 %shr4, 255, !dbg !1452
  %conv6 = trunc i32 %and5 to i8, !dbg !1453
  %6 = load i8*, i8** %p, align 8, !dbg !1454
  %arrayidx7 = getelementptr inbounds i8, i8* %6, i64 2, !dbg !1454
  store i8 %conv6, i8* %arrayidx7, align 1, !dbg !1455
  %7 = load i32, i32* %u.addr, align 4, !dbg !1456
  %shr8 = lshr i32 %7, 24, !dbg !1457
  %and9 = and i32 %shr8, 255, !dbg !1458
  %conv10 = trunc i32 %and9 to i8, !dbg !1459
  %8 = load i8*, i8** %p, align 8, !dbg !1460
  %arrayidx11 = getelementptr inbounds i8, i8* %8, i64 3, !dbg !1460
  store i8 %conv10, i8* %arrayidx11, align 1, !dbg !1461
  ret void, !dbg !1462
}

; Function Attrs: nounwind
declare i32 @lzma_properties_decode(%struct.lzma_filter*, %struct.lzma_allocator*, i8*, i64) #5

; Function Attrs: nounwind
declare i32 @lzma_raw_decoder(%struct.lzma_stream*, %struct.lzma_filter*) #5

; Function Attrs: nounwind
declare void @lzma_end(%struct.lzma_stream*) #5

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { inlinehint nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind readonly }
attributes #7 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!412, !413}
!llvm.ident = !{!414}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !27, subprograms: !376, globals: !409)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_support_filter_xz.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{!3, !7, !21}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 44, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/base.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!5 = !{!6}
!6 = !DIEnumerator(name: "LZMA_RESERVED_ENUM", value: 0)
!7 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 57, size: 32, align: 32, elements: !8)
!8 = !{!9, !10, !11, !12, !13, !14, !15, !16, !17, !18, !19, !20}
!9 = !DIEnumerator(name: "LZMA_OK", value: 0)
!10 = !DIEnumerator(name: "LZMA_STREAM_END", value: 1)
!11 = !DIEnumerator(name: "LZMA_NO_CHECK", value: 2)
!12 = !DIEnumerator(name: "LZMA_UNSUPPORTED_CHECK", value: 3)
!13 = !DIEnumerator(name: "LZMA_GET_CHECK", value: 4)
!14 = !DIEnumerator(name: "LZMA_MEM_ERROR", value: 5)
!15 = !DIEnumerator(name: "LZMA_MEMLIMIT_ERROR", value: 6)
!16 = !DIEnumerator(name: "LZMA_FORMAT_ERROR", value: 7)
!17 = !DIEnumerator(name: "LZMA_OPTIONS_ERROR", value: 8)
!18 = !DIEnumerator(name: "LZMA_DATA_ERROR", value: 9)
!19 = !DIEnumerator(name: "LZMA_BUF_ERROR", value: 10)
!20 = !DIEnumerator(name: "LZMA_PROG_ERROR", value: 11)
!21 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 250, size: 32, align: 32, elements: !22)
!22 = !{!23, !24, !25, !26}
!23 = !DIEnumerator(name: "LZMA_RUN", value: 0)
!24 = !DIEnumerator(name: "LZMA_SYNC_FLUSH", value: 1)
!25 = !DIEnumerator(name: "LZMA_FULL_FLUSH", value: 2)
!26 = !DIEnumerator(name: "LZMA_FINISH", value: 3)
!27 = !{!28, !146, !315, !316, !319, !366}
!28 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !29, size: 64, align: 64)
!29 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read", file: !30, line: 159, size: 20288, align: 64, elements: !31)
!30 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!31 = !{!32, !134, !135, !136, !137, !138, !182, !246, !247, !248, !249, !250, !251, !284, !286, !296, !297}
!32 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !29, file: !30, line: 160, baseType: !33, size: 1280, align: 64)
!33 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !34, line: 89, size: 1280, align: 64, elements: !35)
!34 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!35 = !{!36, !38, !39, !107, !108, !109, !110, !111, !112, !113, !114, !122, !123, !124, !125, !128, !129, !130, !131, !132, !133}
!36 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !33, file: !34, line: 96, baseType: !37, size: 32, align: 32)
!37 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!38 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !33, file: !34, line: 97, baseType: !37, size: 32, align: 32, offset: 32)
!39 = !DIDerivedType(tag: DW_TAG_member, name: "vtable", scope: !33, file: !34, line: 103, baseType: !40, size: 64, align: 64, offset: 64)
!40 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !41, size: 64, align: 64)
!41 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_vtable", file: !34, line: 63, size: 832, align: 64, elements: !42)
!42 = !{!43, !49, !50, !57, !58, !72, !78, !83, !84, !91, !92, !96, !100}
!43 = !DIDerivedType(tag: DW_TAG_member, name: "archive_close", scope: !41, file: !34, line: 64, baseType: !44, size: 64, align: 64)
!44 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !45, size: 64, align: 64)
!45 = !DISubroutineType(types: !46)
!46 = !{!47, !48}
!47 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!48 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !33, size: 64, align: 64)
!49 = !DIDerivedType(tag: DW_TAG_member, name: "archive_free", scope: !41, file: !34, line: 65, baseType: !44, size: 64, align: 64, offset: 64)
!50 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_header", scope: !41, file: !34, line: 66, baseType: !51, size: 64, align: 64, offset: 128)
!51 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !52, size: 64, align: 64)
!52 = !DISubroutineType(types: !53)
!53 = !{!47, !48, !54}
!54 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !55, size: 64, align: 64)
!55 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_entry", file: !56, line: 180, flags: DIFlagFwdDecl)
!56 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!57 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_finish_entry", scope: !41, file: !34, line: 68, baseType: !44, size: 64, align: 64, offset: 192)
!58 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data", scope: !41, file: !34, line: 69, baseType: !59, size: 64, align: 64, offset: 256)
!59 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !60, size: 64, align: 64)
!60 = !DISubroutineType(types: !61)
!61 = !{!62, !48, !67, !69}
!62 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !63, line: 102, baseType: !64)
!63 = !DIFile(filename: "/usr/include/stdio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!64 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !65, line: 172, baseType: !66)
!65 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!66 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!67 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !68, size: 64, align: 64)
!68 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!69 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !70, line: 62, baseType: !71)
!70 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!71 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!72 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data_block", scope: !41, file: !34, line: 71, baseType: !73, size: 64, align: 64, offset: 320)
!73 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !74, size: 64, align: 64)
!74 = !DISubroutineType(types: !75)
!75 = !{!62, !48, !67, !69, !76}
!76 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !77, line: 40, baseType: !66)
!77 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!78 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header", scope: !41, file: !34, line: 74, baseType: !79, size: 64, align: 64, offset: 384)
!79 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !80, size: 64, align: 64)
!80 = !DISubroutineType(types: !81)
!81 = !{!47, !48, !82}
!82 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !54, size: 64, align: 64)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header2", scope: !41, file: !34, line: 76, baseType: !51, size: 64, align: 64, offset: 448)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_data_block", scope: !41, file: !34, line: 78, baseType: !85, size: 64, align: 64, offset: 512)
!85 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !86, size: 64, align: 64)
!86 = !DISubroutineType(types: !87)
!87 = !{!47, !48, !88, !89, !90}
!88 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !67, size: 64, align: 64)
!89 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !69, size: 64, align: 64)
!90 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !76, size: 64, align: 64)
!91 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_count", scope: !41, file: !34, line: 81, baseType: !44, size: 64, align: 64, offset: 576)
!92 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_bytes", scope: !41, file: !34, line: 82, baseType: !93, size: 64, align: 64, offset: 640)
!93 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !94, size: 64, align: 64)
!94 = !DISubroutineType(types: !95)
!95 = !{!76, !48, !47}
!96 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_code", scope: !41, file: !34, line: 83, baseType: !97, size: 64, align: 64, offset: 704)
!97 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !98, size: 64, align: 64)
!98 = !DISubroutineType(types: !99)
!99 = !{!47, !48, !47}
!100 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_name", scope: !41, file: !34, line: 84, baseType: !101, size: 64, align: 64, offset: 768)
!101 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !102, size: 64, align: 64)
!102 = !DISubroutineType(types: !103)
!103 = !{!104, !48, !47}
!104 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !105, size: 64, align: 64)
!105 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !106)
!106 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format", scope: !33, file: !34, line: 105, baseType: !47, size: 32, align: 32, offset: 128)
!108 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format_name", scope: !33, file: !34, line: 106, baseType: !104, size: 64, align: 64, offset: 192)
!109 = !DIDerivedType(tag: DW_TAG_member, name: "compression_code", scope: !33, file: !34, line: 108, baseType: !47, size: 32, align: 32, offset: 256)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "compression_name", scope: !33, file: !34, line: 109, baseType: !104, size: 64, align: 64, offset: 320)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "file_count", scope: !33, file: !34, line: 112, baseType: !47, size: 32, align: 32, offset: 384)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "archive_error_number", scope: !33, file: !34, line: 114, baseType: !47, size: 32, align: 32, offset: 416)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "error", scope: !33, file: !34, line: 115, baseType: !104, size: 64, align: 64, offset: 448)
!114 = !DIDerivedType(tag: DW_TAG_member, name: "error_string", scope: !33, file: !34, line: 116, baseType: !115, size: 192, align: 64, offset: 512)
!115 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string", file: !116, line: 58, size: 192, align: 64, elements: !117)
!116 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_string.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!117 = !{!118, !120, !121}
!118 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !115, file: !116, line: 59, baseType: !119, size: 64, align: 64)
!119 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !106, size: 64, align: 64)
!120 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !115, file: !116, line: 60, baseType: !69, size: 64, align: 64, offset: 64)
!121 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !115, file: !116, line: 61, baseType: !69, size: 64, align: 64, offset: 128)
!122 = !DIDerivedType(tag: DW_TAG_member, name: "current_code", scope: !33, file: !34, line: 118, baseType: !119, size: 64, align: 64, offset: 704)
!123 = !DIDerivedType(tag: DW_TAG_member, name: "current_codepage", scope: !33, file: !34, line: 119, baseType: !37, size: 32, align: 32, offset: 768)
!124 = !DIDerivedType(tag: DW_TAG_member, name: "current_oemcp", scope: !33, file: !34, line: 120, baseType: !37, size: 32, align: 32, offset: 800)
!125 = !DIDerivedType(tag: DW_TAG_member, name: "sconv", scope: !33, file: !34, line: 121, baseType: !126, size: 64, align: 64, offset: 832)
!126 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !127, size: 64, align: 64)
!127 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string_conv", file: !116, line: 70, flags: DIFlagFwdDecl)
!128 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_block", scope: !33, file: !34, line: 127, baseType: !104, size: 64, align: 64, offset: 896)
!129 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_offset", scope: !33, file: !34, line: 128, baseType: !76, size: 64, align: 64, offset: 960)
!130 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_output_offset", scope: !33, file: !34, line: 129, baseType: !76, size: 64, align: 64, offset: 1024)
!131 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_remaining", scope: !33, file: !34, line: 130, baseType: !69, size: 64, align: 64, offset: 1088)
!132 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_is_posix_read", scope: !33, file: !34, line: 137, baseType: !106, size: 8, align: 8, offset: 1152)
!133 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_requested", scope: !33, file: !34, line: 138, baseType: !69, size: 64, align: 64, offset: 1216)
!134 = !DIDerivedType(tag: DW_TAG_member, name: "entry", scope: !29, file: !30, line: 162, baseType: !54, size: 64, align: 64, offset: 1280)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_set", scope: !29, file: !30, line: 165, baseType: !47, size: 32, align: 32, offset: 1344)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_dev", scope: !29, file: !30, line: 166, baseType: !76, size: 64, align: 64, offset: 1408)
!137 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_ino", scope: !29, file: !30, line: 167, baseType: !76, size: 64, align: 64, offset: 1472)
!138 = !DIDerivedType(tag: DW_TAG_member, name: "client", scope: !29, file: !30, line: 170, baseType: !139, size: 576, align: 64, offset: 1536)
!139 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_client", file: !30, line: 134, size: 576, align: 64, elements: !140)
!140 = !{!141, !147, !153, !159, !164, !167, !172, !173, !174, !175}
!141 = !DIDerivedType(tag: DW_TAG_member, name: "opener", scope: !139, file: !30, line: 135, baseType: !142, size: 64, align: 64)
!142 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !143, size: 64, align: 64)
!143 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_open_callback", file: !56, line: 241, baseType: !144)
!144 = !DISubroutineType(types: !145)
!145 = !{!47, !48, !146}
!146 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!147 = !DIDerivedType(tag: DW_TAG_member, name: "reader", scope: !139, file: !30, line: 136, baseType: !148, size: 64, align: 64, offset: 64)
!148 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !149, size: 64, align: 64)
!149 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_read_callback", file: !56, line: 218, baseType: !150)
!150 = !DISubroutineType(types: !151)
!151 = !{!152, !48, !146, !88}
!152 = !DIDerivedType(tag: DW_TAG_typedef, name: "la_ssize_t", file: !56, line: 95, baseType: !62)
!153 = !DIDerivedType(tag: DW_TAG_member, name: "skipper", scope: !139, file: !30, line: 137, baseType: !154, size: 64, align: 64, offset: 128)
!154 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !155, size: 64, align: 64)
!155 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_skip_callback", file: !56, line: 226, baseType: !156)
!156 = !DISubroutineType(types: !157)
!157 = !{!158, !48, !146, !158}
!158 = !DIDerivedType(tag: DW_TAG_typedef, name: "la_int64_t", file: !56, line: 73, baseType: !76)
!159 = !DIDerivedType(tag: DW_TAG_member, name: "seeker", scope: !139, file: !30, line: 138, baseType: !160, size: 64, align: 64, offset: 192)
!160 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !161, size: 64, align: 64)
!161 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_seek_callback", file: !56, line: 233, baseType: !162)
!162 = !DISubroutineType(types: !163)
!163 = !{!158, !48, !146, !158, !47}
!164 = !DIDerivedType(tag: DW_TAG_member, name: "closer", scope: !139, file: !30, line: 139, baseType: !165, size: 64, align: 64, offset: 256)
!165 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !166, size: 64, align: 64)
!166 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_close_callback", file: !56, line: 243, baseType: !144)
!167 = !DIDerivedType(tag: DW_TAG_member, name: "switcher", scope: !139, file: !30, line: 140, baseType: !168, size: 64, align: 64, offset: 320)
!168 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !169, size: 64, align: 64)
!169 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_switch_callback", file: !56, line: 249, baseType: !170)
!170 = !DISubroutineType(types: !171)
!171 = !{!47, !48, !146, !146}
!172 = !DIDerivedType(tag: DW_TAG_member, name: "nodes", scope: !139, file: !30, line: 141, baseType: !37, size: 32, align: 32, offset: 384)
!173 = !DIDerivedType(tag: DW_TAG_member, name: "cursor", scope: !139, file: !30, line: 142, baseType: !37, size: 32, align: 32, offset: 416)
!174 = !DIDerivedType(tag: DW_TAG_member, name: "position", scope: !139, file: !30, line: 143, baseType: !76, size: 64, align: 64, offset: 448)
!175 = !DIDerivedType(tag: DW_TAG_member, name: "dataset", scope: !139, file: !30, line: 144, baseType: !176, size: 64, align: 64, offset: 512)
!176 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !177, size: 64, align: 64)
!177 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_data_node", file: !30, line: 129, size: 192, align: 64, elements: !178)
!178 = !{!179, !180, !181}
!179 = !DIDerivedType(tag: DW_TAG_member, name: "begin_position", scope: !177, file: !30, line: 130, baseType: !76, size: 64, align: 64)
!180 = !DIDerivedType(tag: DW_TAG_member, name: "total_size", scope: !177, file: !30, line: 131, baseType: !76, size: 64, align: 64, offset: 64)
!181 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !177, file: !30, line: 132, baseType: !146, size: 64, align: 64, offset: 128)
!182 = !DIDerivedType(tag: DW_TAG_member, name: "bidders", scope: !29, file: !30, line: 173, baseType: !183, size: 6144, align: 64, offset: 2112)
!183 = !DICompositeType(tag: DW_TAG_array_type, baseType: !184, size: 6144, align: 64, elements: !244)
!184 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_filter_bidder", file: !30, line: 60, size: 384, align: 64, elements: !185)
!185 = !{!186, !187, !188, !235, !236, !240}
!186 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !184, file: !30, line: 62, baseType: !146, size: 64, align: 64)
!187 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !184, file: !30, line: 64, baseType: !104, size: 64, align: 64, offset: 64)
!188 = !DIDerivedType(tag: DW_TAG_member, name: "bid", scope: !184, file: !30, line: 66, baseType: !189, size: 64, align: 64, offset: 128)
!189 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !190, size: 64, align: 64)
!190 = !DISubroutineType(types: !191)
!191 = !{!47, !192, !193}
!192 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !184, size: 64, align: 64)
!193 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !194, size: 64, align: 64)
!194 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_filter", file: !30, line: 82, size: 1408, align: 64, elements: !195)
!195 = !{!196, !197, !198, !199, !200, !204, !208, !212, !216, !217, !221, !222, !223, !224, !225, !226, !227, !228, !229, !230, !231, !232, !233, !234}
!196 = !DIDerivedType(tag: DW_TAG_member, name: "position", scope: !194, file: !30, line: 83, baseType: !76, size: 64, align: 64)
!197 = !DIDerivedType(tag: DW_TAG_member, name: "bidder", scope: !194, file: !30, line: 86, baseType: !192, size: 64, align: 64, offset: 64)
!198 = !DIDerivedType(tag: DW_TAG_member, name: "upstream", scope: !194, file: !30, line: 87, baseType: !193, size: 64, align: 64, offset: 128)
!199 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !194, file: !30, line: 88, baseType: !28, size: 64, align: 64, offset: 192)
!200 = !DIDerivedType(tag: DW_TAG_member, name: "open", scope: !194, file: !30, line: 90, baseType: !201, size: 64, align: 64, offset: 256)
!201 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !202, size: 64, align: 64)
!202 = !DISubroutineType(types: !203)
!203 = !{!47, !193}
!204 = !DIDerivedType(tag: DW_TAG_member, name: "read", scope: !194, file: !30, line: 92, baseType: !205, size: 64, align: 64, offset: 320)
!205 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !206, size: 64, align: 64)
!206 = !DISubroutineType(types: !207)
!207 = !{!62, !193, !88}
!208 = !DIDerivedType(tag: DW_TAG_member, name: "skip", scope: !194, file: !30, line: 94, baseType: !209, size: 64, align: 64, offset: 384)
!209 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !210, size: 64, align: 64)
!210 = !DISubroutineType(types: !211)
!211 = !{!76, !193, !76}
!212 = !DIDerivedType(tag: DW_TAG_member, name: "seek", scope: !194, file: !30, line: 96, baseType: !213, size: 64, align: 64, offset: 448)
!213 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !214, size: 64, align: 64)
!214 = !DISubroutineType(types: !215)
!215 = !{!76, !193, !76, !47}
!216 = !DIDerivedType(tag: DW_TAG_member, name: "close", scope: !194, file: !30, line: 98, baseType: !201, size: 64, align: 64, offset: 512)
!217 = !DIDerivedType(tag: DW_TAG_member, name: "sswitch", scope: !194, file: !30, line: 100, baseType: !218, size: 64, align: 64, offset: 576)
!218 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !219, size: 64, align: 64)
!219 = !DISubroutineType(types: !220)
!220 = !{!47, !193, !37}
!221 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !194, file: !30, line: 102, baseType: !146, size: 64, align: 64, offset: 640)
!222 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !194, file: !30, line: 104, baseType: !104, size: 64, align: 64, offset: 704)
!223 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !194, file: !30, line: 105, baseType: !47, size: 32, align: 32, offset: 768)
!224 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !194, file: !30, line: 108, baseType: !119, size: 64, align: 64, offset: 832)
!225 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_size", scope: !194, file: !30, line: 109, baseType: !69, size: 64, align: 64, offset: 896)
!226 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !194, file: !30, line: 110, baseType: !119, size: 64, align: 64, offset: 960)
!227 = !DIDerivedType(tag: DW_TAG_member, name: "avail", scope: !194, file: !30, line: 111, baseType: !69, size: 64, align: 64, offset: 1024)
!228 = !DIDerivedType(tag: DW_TAG_member, name: "client_buff", scope: !194, file: !30, line: 112, baseType: !67, size: 64, align: 64, offset: 1088)
!229 = !DIDerivedType(tag: DW_TAG_member, name: "client_total", scope: !194, file: !30, line: 113, baseType: !69, size: 64, align: 64, offset: 1152)
!230 = !DIDerivedType(tag: DW_TAG_member, name: "client_next", scope: !194, file: !30, line: 114, baseType: !104, size: 64, align: 64, offset: 1216)
!231 = !DIDerivedType(tag: DW_TAG_member, name: "client_avail", scope: !194, file: !30, line: 115, baseType: !69, size: 64, align: 64, offset: 1280)
!232 = !DIDerivedType(tag: DW_TAG_member, name: "end_of_file", scope: !194, file: !30, line: 116, baseType: !106, size: 8, align: 8, offset: 1344)
!233 = !DIDerivedType(tag: DW_TAG_member, name: "closed", scope: !194, file: !30, line: 117, baseType: !106, size: 8, align: 8, offset: 1352)
!234 = !DIDerivedType(tag: DW_TAG_member, name: "fatal", scope: !194, file: !30, line: 118, baseType: !106, size: 8, align: 8, offset: 1360)
!235 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !184, file: !30, line: 69, baseType: !201, size: 64, align: 64, offset: 192)
!236 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !184, file: !30, line: 71, baseType: !237, size: 64, align: 64, offset: 256)
!237 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !238, size: 64, align: 64)
!238 = !DISubroutineType(types: !239)
!239 = !{!47, !192, !104, !104}
!240 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !184, file: !30, line: 74, baseType: !241, size: 64, align: 64, offset: 320)
!241 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !242, size: 64, align: 64)
!242 = !DISubroutineType(types: !243)
!243 = !{!47, !192}
!244 = !{!245}
!245 = !DISubrange(count: 16)
!246 = !DIDerivedType(tag: DW_TAG_member, name: "filter", scope: !29, file: !30, line: 176, baseType: !193, size: 64, align: 64, offset: 8256)
!247 = !DIDerivedType(tag: DW_TAG_member, name: "bypass_filter_bidding", scope: !29, file: !30, line: 179, baseType: !47, size: 32, align: 32, offset: 8320)
!248 = !DIDerivedType(tag: DW_TAG_member, name: "header_position", scope: !29, file: !30, line: 182, baseType: !76, size: 64, align: 64, offset: 8384)
!249 = !DIDerivedType(tag: DW_TAG_member, name: "data_start_node", scope: !29, file: !30, line: 185, baseType: !37, size: 32, align: 32, offset: 8448)
!250 = !DIDerivedType(tag: DW_TAG_member, name: "data_end_node", scope: !29, file: !30, line: 186, baseType: !37, size: 32, align: 32, offset: 8480)
!251 = !DIDerivedType(tag: DW_TAG_member, name: "formats", scope: !29, file: !30, line: 209, baseType: !252, size: 11264, align: 64, offset: 8512)
!252 = !DICompositeType(tag: DW_TAG_array_type, baseType: !253, size: 11264, align: 64, elements: !244)
!253 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_format_descriptor", file: !30, line: 196, size: 704, align: 64, elements: !254)
!254 = !{!255, !256, !257, !261, !265, !269, !273, !277, !281, !282, !283}
!255 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !253, file: !30, line: 197, baseType: !146, size: 64, align: 64)
!256 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !253, file: !30, line: 198, baseType: !104, size: 64, align: 64, offset: 64)
!257 = !DIDerivedType(tag: DW_TAG_member, name: "bid", scope: !253, file: !30, line: 199, baseType: !258, size: 64, align: 64, offset: 128)
!258 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !259, size: 64, align: 64)
!259 = !DISubroutineType(types: !260)
!260 = !{!47, !28, !47}
!261 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !253, file: !30, line: 200, baseType: !262, size: 64, align: 64, offset: 192)
!262 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !263, size: 64, align: 64)
!263 = !DISubroutineType(types: !264)
!264 = !{!47, !28, !104, !104}
!265 = !DIDerivedType(tag: DW_TAG_member, name: "read_header", scope: !253, file: !30, line: 202, baseType: !266, size: 64, align: 64, offset: 256)
!266 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !267, size: 64, align: 64)
!267 = !DISubroutineType(types: !268)
!268 = !{!47, !28, !54}
!269 = !DIDerivedType(tag: DW_TAG_member, name: "read_data", scope: !253, file: !30, line: 203, baseType: !270, size: 64, align: 64, offset: 320)
!270 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !271, size: 64, align: 64)
!271 = !DISubroutineType(types: !272)
!272 = !{!47, !28, !88, !89, !90}
!273 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_skip", scope: !253, file: !30, line: 204, baseType: !274, size: 64, align: 64, offset: 384)
!274 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !275, size: 64, align: 64)
!275 = !DISubroutineType(types: !276)
!276 = !{!47, !28}
!277 = !DIDerivedType(tag: DW_TAG_member, name: "seek_data", scope: !253, file: !30, line: 205, baseType: !278, size: 64, align: 64, offset: 448)
!278 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !279, size: 64, align: 64)
!279 = !DISubroutineType(types: !280)
!280 = !{!76, !28, !76, !47}
!281 = !DIDerivedType(tag: DW_TAG_member, name: "cleanup", scope: !253, file: !30, line: 206, baseType: !274, size: 64, align: 64, offset: 512)
!282 = !DIDerivedType(tag: DW_TAG_member, name: "format_capabilties", scope: !253, file: !30, line: 207, baseType: !274, size: 64, align: 64, offset: 576)
!283 = !DIDerivedType(tag: DW_TAG_member, name: "has_encrypted_entries", scope: !253, file: !30, line: 208, baseType: !274, size: 64, align: 64, offset: 640)
!284 = !DIDerivedType(tag: DW_TAG_member, name: "format", scope: !29, file: !30, line: 210, baseType: !285, size: 64, align: 64, offset: 19776)
!285 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !253, size: 64, align: 64)
!286 = !DIDerivedType(tag: DW_TAG_member, name: "extract", scope: !29, file: !30, line: 215, baseType: !287, size: 64, align: 64, offset: 19840)
!287 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !288, size: 64, align: 64)
!288 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_extract", file: !30, line: 151, size: 192, align: 64, elements: !289)
!289 = !{!290, !291, !295}
!290 = !DIDerivedType(tag: DW_TAG_member, name: "ad", scope: !288, file: !30, line: 152, baseType: !48, size: 64, align: 64)
!291 = !DIDerivedType(tag: DW_TAG_member, name: "extract_progress", scope: !288, file: !30, line: 155, baseType: !292, size: 64, align: 64, offset: 64)
!292 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !293, size: 64, align: 64)
!293 = !DISubroutineType(types: !294)
!294 = !{null, !146}
!295 = !DIDerivedType(tag: DW_TAG_member, name: "extract_progress_user_data", scope: !288, file: !30, line: 156, baseType: !146, size: 64, align: 64, offset: 128)
!296 = !DIDerivedType(tag: DW_TAG_member, name: "cleanup_archive_extract", scope: !29, file: !30, line: 216, baseType: !274, size: 64, align: 64, offset: 19904)
!297 = !DIDerivedType(tag: DW_TAG_member, name: "passphrases", scope: !29, file: !30, line: 227, baseType: !298, size: 320, align: 64, offset: 19968)
!298 = !DICompositeType(tag: DW_TAG_structure_type, scope: !29, file: !30, line: 221, size: 320, align: 64, elements: !299)
!299 = !{!300, !306, !308, !309, !314}
!300 = !DIDerivedType(tag: DW_TAG_member, name: "first", scope: !298, file: !30, line: 222, baseType: !301, size: 64, align: 64)
!301 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !302, size: 64, align: 64)
!302 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_passphrase", file: !30, line: 146, size: 128, align: 64, elements: !303)
!303 = !{!304, !305}
!304 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase", scope: !302, file: !30, line: 147, baseType: !119, size: 64, align: 64)
!305 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !302, file: !30, line: 148, baseType: !301, size: 64, align: 64, offset: 64)
!306 = !DIDerivedType(tag: DW_TAG_member, name: "last", scope: !298, file: !30, line: 223, baseType: !307, size: 64, align: 64, offset: 64)
!307 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !301, size: 64, align: 64)
!308 = !DIDerivedType(tag: DW_TAG_member, name: "candidate", scope: !298, file: !30, line: 224, baseType: !47, size: 32, align: 32, offset: 128)
!309 = !DIDerivedType(tag: DW_TAG_member, name: "callback", scope: !298, file: !30, line: 225, baseType: !310, size: 64, align: 64, offset: 192)
!310 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !311, size: 64, align: 64)
!311 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_passphrase_callback", file: !56, line: 256, baseType: !312)
!312 = !DISubroutineType(types: !313)
!313 = !{!104, !48, !146}
!314 = !DIDerivedType(tag: DW_TAG_member, name: "client_data", scope: !298, file: !30, line: 226, baseType: !146, size: 64, align: 64, offset: 256)
!315 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !77, line: 55, baseType: !71)
!316 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !317, size: 64, align: 64)
!317 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !318)
!318 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!319 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !320, size: 64, align: 64)
!320 = !DICompositeType(tag: DW_TAG_structure_type, name: "private_data", file: !1, line: 55, size: 1472, align: 64, elements: !321)
!321 = !{!322, !365, !367, !368, !369, !370, !371, !372, !374, !375}
!322 = !DIDerivedType(tag: DW_TAG_member, name: "stream", scope: !320, file: !1, line: 56, baseType: !323, size: 1088, align: 64)
!323 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_stream", file: !4, line: 490, baseType: !324)
!324 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 453, size: 1088, align: 64, elements: !325)
!325 = !{!326, !330, !331, !332, !334, !335, !336, !350, !354, !355, !356, !357, !358, !359, !360, !361, !362, !364}
!326 = !DIDerivedType(tag: DW_TAG_member, name: "next_in", scope: !324, file: !4, line: 454, baseType: !327, size: 64, align: 64)
!327 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !328, size: 64, align: 64)
!328 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !329)
!329 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !77, line: 48, baseType: !318)
!330 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in", scope: !324, file: !4, line: 455, baseType: !69, size: 64, align: 64, offset: 64)
!331 = !DIDerivedType(tag: DW_TAG_member, name: "total_in", scope: !324, file: !4, line: 456, baseType: !315, size: 64, align: 64, offset: 128)
!332 = !DIDerivedType(tag: DW_TAG_member, name: "next_out", scope: !324, file: !4, line: 458, baseType: !333, size: 64, align: 64, offset: 192)
!333 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !329, size: 64, align: 64)
!334 = !DIDerivedType(tag: DW_TAG_member, name: "avail_out", scope: !324, file: !4, line: 459, baseType: !69, size: 64, align: 64, offset: 256)
!335 = !DIDerivedType(tag: DW_TAG_member, name: "total_out", scope: !324, file: !4, line: 460, baseType: !315, size: 64, align: 64, offset: 320)
!336 = !DIDerivedType(tag: DW_TAG_member, name: "allocator", scope: !324, file: !4, line: 468, baseType: !337, size: 64, align: 64, offset: 384)
!337 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !338, size: 64, align: 64)
!338 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_allocator", file: !4, line: 403, baseType: !339)
!339 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 341, size: 192, align: 64, elements: !340)
!340 = !{!341, !345, !349}
!341 = !DIDerivedType(tag: DW_TAG_member, name: "alloc", scope: !339, file: !4, line: 376, baseType: !342, size: 64, align: 64)
!342 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !343, size: 64, align: 64)
!343 = !DISubroutineType(types: !344)
!344 = !{!146, !146, !69, !69}
!345 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !339, file: !4, line: 390, baseType: !346, size: 64, align: 64, offset: 64)
!346 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !347, size: 64, align: 64)
!347 = !DISubroutineType(types: !348)
!348 = !{null, !146, !146}
!349 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !339, file: !4, line: 401, baseType: !146, size: 64, align: 64, offset: 128)
!350 = !DIDerivedType(tag: DW_TAG_member, name: "internal", scope: !324, file: !4, line: 471, baseType: !351, size: 64, align: 64, offset: 448)
!351 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !352, size: 64, align: 64)
!352 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_internal", file: !4, line: 411, baseType: !353)
!353 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_internal_s", file: !4, line: 411, flags: DIFlagFwdDecl)
!354 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !324, file: !4, line: 479, baseType: !146, size: 64, align: 64, offset: 512)
!355 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !324, file: !4, line: 480, baseType: !146, size: 64, align: 64, offset: 576)
!356 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr3", scope: !324, file: !4, line: 481, baseType: !146, size: 64, align: 64, offset: 640)
!357 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr4", scope: !324, file: !4, line: 482, baseType: !146, size: 64, align: 64, offset: 704)
!358 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !324, file: !4, line: 483, baseType: !315, size: 64, align: 64, offset: 768)
!359 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !324, file: !4, line: 484, baseType: !315, size: 64, align: 64, offset: 832)
!360 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int3", scope: !324, file: !4, line: 485, baseType: !69, size: 64, align: 64, offset: 896)
!361 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int4", scope: !324, file: !4, line: 486, baseType: !69, size: 64, align: 64, offset: 960)
!362 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !324, file: !4, line: 487, baseType: !363, size: 32, align: 32, offset: 1024)
!363 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_reserved_enum", file: !4, line: 46, baseType: !3)
!364 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !324, file: !4, line: 488, baseType: !363, size: 32, align: 32, offset: 1056)
!365 = !DIDerivedType(tag: DW_TAG_member, name: "out_block", scope: !320, file: !1, line: 57, baseType: !366, size: 64, align: 64, offset: 1088)
!366 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !318, size: 64, align: 64)
!367 = !DIDerivedType(tag: DW_TAG_member, name: "out_block_size", scope: !320, file: !1, line: 58, baseType: !69, size: 64, align: 64, offset: 1152)
!368 = !DIDerivedType(tag: DW_TAG_member, name: "total_out", scope: !320, file: !1, line: 59, baseType: !76, size: 64, align: 64, offset: 1216)
!369 = !DIDerivedType(tag: DW_TAG_member, name: "eof", scope: !320, file: !1, line: 60, baseType: !106, size: 8, align: 8, offset: 1280)
!370 = !DIDerivedType(tag: DW_TAG_member, name: "in_stream", scope: !320, file: !1, line: 61, baseType: !106, size: 8, align: 8, offset: 1288)
!371 = !DIDerivedType(tag: DW_TAG_member, name: "lzip_ver", scope: !320, file: !1, line: 64, baseType: !106, size: 8, align: 8, offset: 1296)
!372 = !DIDerivedType(tag: DW_TAG_member, name: "crc32", scope: !320, file: !1, line: 65, baseType: !373, size: 32, align: 32, offset: 1312)
!373 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !77, line: 51, baseType: !37)
!374 = !DIDerivedType(tag: DW_TAG_member, name: "member_in", scope: !320, file: !1, line: 66, baseType: !76, size: 64, align: 64, offset: 1344)
!375 = !DIDerivedType(tag: DW_TAG_member, name: "member_out", scope: !320, file: !1, line: 67, baseType: !76, size: 64, align: 64, offset: 1408)
!376 = !{!377, !379, !380, !381, !382, !383, !384, !385, !386, !390, !393, !394, !395, !396, !397, !398, !399, !402, !403, !404, !407, !408}
!377 = distinct !DISubprogram(name: "archive_read_support_compression_xz", scope: !1, file: !1, line: 105, type: !45, isLocal: false, isDefinition: true, scopeLine: 106, flags: DIFlagPrototyped, isOptimized: false, variables: !378)
!378 = !{}
!379 = distinct !DISubprogram(name: "archive_read_support_filter_xz", scope: !1, file: !1, line: 112, type: !45, isLocal: false, isDefinition: true, scopeLine: 113, flags: DIFlagPrototyped, isOptimized: false, variables: !378)
!380 = distinct !DISubprogram(name: "archive_read_support_compression_lzma", scope: !1, file: !1, line: 140, type: !45, isLocal: false, isDefinition: true, scopeLine: 141, flags: DIFlagPrototyped, isOptimized: false, variables: !378)
!381 = distinct !DISubprogram(name: "archive_read_support_filter_lzma", scope: !1, file: !1, line: 147, type: !45, isLocal: false, isDefinition: true, scopeLine: 148, flags: DIFlagPrototyped, isOptimized: false, variables: !378)
!382 = distinct !DISubprogram(name: "archive_read_support_compression_lzip", scope: !1, file: !1, line: 176, type: !45, isLocal: false, isDefinition: true, scopeLine: 177, flags: DIFlagPrototyped, isOptimized: false, variables: !378)
!383 = distinct !DISubprogram(name: "archive_read_support_filter_lzip", scope: !1, file: !1, line: 183, type: !45, isLocal: false, isDefinition: true, scopeLine: 184, flags: DIFlagPrototyped, isOptimized: false, variables: !378)
!384 = distinct !DISubprogram(name: "xz_bidder_bid", scope: !1, file: !1, line: 213, type: !190, isLocal: true, isDefinition: true, scopeLine: 215, flags: DIFlagPrototyped, isOptimized: false, variables: !378)
!385 = distinct !DISubprogram(name: "lzma_bidder_bid", scope: !1, file: !1, line: 247, type: !190, isLocal: true, isDefinition: true, scopeLine: 249, flags: DIFlagPrototyped, isOptimized: false, variables: !378)
!386 = distinct !DISubprogram(name: "archive_le64dec", scope: !387, file: !387, line: 131, type: !388, isLocal: true, isDefinition: true, scopeLine: 132, flags: DIFlagPrototyped, isOptimized: false, variables: !378)
!387 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_endian.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!388 = !DISubroutineType(types: !389)
!389 = !{!315, !67}
!390 = distinct !DISubprogram(name: "archive_le32dec", scope: !387, file: !387, line: 115, type: !391, isLocal: true, isDefinition: true, scopeLine: 116, flags: DIFlagPrototyped, isOptimized: false, variables: !378)
!391 = !DISubroutineType(types: !392)
!392 = !{!373, !67}
!393 = distinct !DISubprogram(name: "lzip_bidder_bid", scope: !1, file: !1, line: 388, type: !190, isLocal: true, isDefinition: true, scopeLine: 390, flags: DIFlagPrototyped, isOptimized: false, variables: !378)
!394 = distinct !DISubprogram(name: "lzip_has_member", scope: !1, file: !1, line: 354, type: !202, isLocal: true, isDefinition: true, scopeLine: 355, flags: DIFlagPrototyped, isOptimized: false, variables: !378)
!395 = distinct !DISubprogram(name: "xz_bidder_init", scope: !1, file: !1, line: 402, type: !202, isLocal: true, isDefinition: true, scopeLine: 403, flags: DIFlagPrototyped, isOptimized: false, variables: !378)
!396 = distinct !DISubprogram(name: "xz_lzma_bidder_init", scope: !1, file: !1, line: 477, type: !202, isLocal: true, isDefinition: true, scopeLine: 478, flags: DIFlagPrototyped, isOptimized: false, variables: !378)
!397 = distinct !DISubprogram(name: "xz_filter_read", scope: !1, file: !1, line: 657, type: !206, isLocal: true, isDefinition: true, scopeLine: 658, flags: DIFlagPrototyped, isOptimized: false, variables: !378)
!398 = distinct !DISubprogram(name: "lzip_init", scope: !1, file: !1, line: 540, type: !202, isLocal: true, isDefinition: true, scopeLine: 541, flags: DIFlagPrototyped, isOptimized: false, variables: !378)
!399 = distinct !DISubprogram(name: "archive_le32enc", scope: !387, file: !387, line: 177, type: !400, isLocal: true, isDefinition: true, scopeLine: 178, flags: DIFlagPrototyped, isOptimized: false, variables: !378)
!400 = !DISubroutineType(types: !401)
!401 = !{null, !146, !373}
!402 = distinct !DISubprogram(name: "lzip_tail", scope: !1, file: !1, line: 596, type: !202, isLocal: true, isDefinition: true, scopeLine: 597, flags: DIFlagPrototyped, isOptimized: false, variables: !378)
!403 = distinct !DISubprogram(name: "xz_filter_close", scope: !1, file: !1, line: 734, type: !202, isLocal: true, isDefinition: true, scopeLine: 735, flags: DIFlagPrototyped, isOptimized: false, variables: !378)
!404 = distinct !DISubprogram(name: "set_error", scope: !1, file: !1, line: 429, type: !405, isLocal: true, isDefinition: true, scopeLine: 430, flags: DIFlagPrototyped, isOptimized: false, variables: !378)
!405 = !DISubroutineType(types: !406)
!406 = !{null, !193, !47}
!407 = distinct !DISubprogram(name: "lzma_bidder_init", scope: !1, file: !1, line: 410, type: !202, isLocal: true, isDefinition: true, scopeLine: 411, flags: DIFlagPrototyped, isOptimized: false, variables: !378)
!408 = distinct !DISubprogram(name: "lzip_bidder_init", scope: !1, file: !1, line: 418, type: !202, isLocal: true, isDefinition: true, scopeLine: 419, flags: DIFlagPrototyped, isOptimized: false, variables: !378)
!409 = !{!410}
!410 = !DIGlobalVariable(name: "out_block_size", scope: !396, file: !1, line: 479, type: !411, isLocal: true, isDefinition: true, variable: i64* @xz_lzma_bidder_init.out_block_size)
!411 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !69)
!412 = !{i32 2, !"Dwarf Version", i32 4}
!413 = !{i32 2, !"Debug Info Version", i32 3}
!414 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!415 = !DILocalVariable(name: "a", arg: 1, scope: !377, file: !1, line: 105, type: !48)
!416 = !DIExpression()
!417 = !DILocation(line: 105, column: 53, scope: !377)
!418 = !DILocation(line: 107, column: 40, scope: !377)
!419 = !DILocation(line: 107, column: 9, scope: !377)
!420 = !DILocation(line: 107, column: 2, scope: !377)
!421 = !DILocalVariable(name: "_a", arg: 1, scope: !379, file: !1, line: 112, type: !48)
!422 = !DILocation(line: 112, column: 48, scope: !379)
!423 = !DILocalVariable(name: "a", scope: !379, file: !1, line: 114, type: !28)
!424 = !DILocation(line: 114, column: 23, scope: !379)
!425 = !DILocation(line: 114, column: 50, scope: !379)
!426 = !DILocation(line: 114, column: 27, scope: !379)
!427 = !DILocalVariable(name: "bidder", scope: !379, file: !1, line: 115, type: !192)
!428 = !DILocation(line: 115, column: 37, scope: !379)
!429 = !DILocation(line: 117, column: 2, scope: !379)
!430 = !DILocalVariable(name: "magic_test", scope: !431, file: !1, line: 117, type: !47)
!431 = distinct !DILexicalBlock(scope: !379, file: !1, line: 117, column: 2)
!432 = !DILocation(line: 117, column: 2, scope: !431)
!433 = !DILocation(line: 117, column: 2, scope: !434)
!434 = !DILexicalBlockFile(scope: !431, file: !1, discriminator: 1)
!435 = !DILocation(line: 117, column: 2, scope: !436)
!436 = !DILexicalBlockFile(scope: !437, file: !1, discriminator: 2)
!437 = distinct !DILexicalBlock(scope: !431, file: !1, line: 117, column: 2)
!438 = !DILocation(line: 117, column: 2, scope: !439)
!439 = !DILexicalBlockFile(scope: !431, file: !1, discriminator: 3)
!440 = !DILocation(line: 120, column: 32, scope: !441)
!441 = distinct !DILexicalBlock(scope: !379, file: !1, line: 120, column: 6)
!442 = !DILocation(line: 120, column: 6, scope: !441)
!443 = !DILocation(line: 120, column: 44, scope: !441)
!444 = !DILocation(line: 120, column: 6, scope: !379)
!445 = !DILocation(line: 121, column: 3, scope: !441)
!446 = !DILocation(line: 123, column: 2, scope: !379)
!447 = !DILocation(line: 123, column: 10, scope: !379)
!448 = !DILocation(line: 123, column: 15, scope: !379)
!449 = !DILocation(line: 124, column: 2, scope: !379)
!450 = !DILocation(line: 124, column: 10, scope: !379)
!451 = !DILocation(line: 124, column: 15, scope: !379)
!452 = !DILocation(line: 125, column: 2, scope: !379)
!453 = !DILocation(line: 125, column: 10, scope: !379)
!454 = !DILocation(line: 125, column: 14, scope: !379)
!455 = !DILocation(line: 126, column: 2, scope: !379)
!456 = !DILocation(line: 126, column: 10, scope: !379)
!457 = !DILocation(line: 126, column: 15, scope: !379)
!458 = !DILocation(line: 127, column: 2, scope: !379)
!459 = !DILocation(line: 127, column: 10, scope: !379)
!460 = !DILocation(line: 127, column: 18, scope: !379)
!461 = !DILocation(line: 128, column: 2, scope: !379)
!462 = !DILocation(line: 128, column: 10, scope: !379)
!463 = !DILocation(line: 128, column: 15, scope: !379)
!464 = !DILocation(line: 130, column: 2, scope: !379)
!465 = !DILocation(line: 136, column: 1, scope: !379)
!466 = !DILocalVariable(name: "self", arg: 1, scope: !384, file: !1, line: 213, type: !192)
!467 = !DILocation(line: 213, column: 50, scope: !384)
!468 = !DILocalVariable(name: "filter", arg: 2, scope: !384, file: !1, line: 214, type: !193)
!469 = !DILocation(line: 214, column: 33, scope: !384)
!470 = !DILocalVariable(name: "buffer", scope: !384, file: !1, line: 216, type: !316)
!471 = !DILocation(line: 216, column: 23, scope: !384)
!472 = !DILocalVariable(name: "avail", scope: !384, file: !1, line: 217, type: !62)
!473 = !DILocation(line: 217, column: 10, scope: !384)
!474 = !DILocation(line: 219, column: 8, scope: !384)
!475 = !DILocation(line: 221, column: 39, scope: !384)
!476 = !DILocation(line: 221, column: 11, scope: !384)
!477 = !DILocation(line: 221, column: 9, scope: !384)
!478 = !DILocation(line: 222, column: 6, scope: !479)
!479 = distinct !DILexicalBlock(scope: !384, file: !1, line: 222, column: 6)
!480 = !DILocation(line: 222, column: 13, scope: !479)
!481 = !DILocation(line: 222, column: 6, scope: !384)
!482 = !DILocation(line: 223, column: 3, scope: !479)
!483 = !DILocation(line: 228, column: 13, scope: !484)
!484 = distinct !DILexicalBlock(scope: !384, file: !1, line: 228, column: 6)
!485 = !DILocation(line: 228, column: 6, scope: !484)
!486 = !DILocation(line: 228, column: 52, scope: !484)
!487 = !DILocation(line: 228, column: 6, scope: !384)
!488 = !DILocation(line: 229, column: 3, scope: !484)
!489 = !DILocation(line: 231, column: 2, scope: !384)
!490 = !DILocation(line: 232, column: 1, scope: !384)
!491 = !DILocalVariable(name: "self", arg: 1, scope: !395, file: !1, line: 402, type: !193)
!492 = !DILocation(line: 402, column: 44, scope: !395)
!493 = !DILocation(line: 404, column: 2, scope: !395)
!494 = !DILocation(line: 404, column: 8, scope: !395)
!495 = !DILocation(line: 404, column: 13, scope: !395)
!496 = !DILocation(line: 405, column: 2, scope: !395)
!497 = !DILocation(line: 405, column: 8, scope: !395)
!498 = !DILocation(line: 405, column: 13, scope: !395)
!499 = !DILocation(line: 406, column: 30, scope: !395)
!500 = !DILocation(line: 406, column: 10, scope: !395)
!501 = !DILocation(line: 406, column: 2, scope: !395)
!502 = !DILocalVariable(name: "a", arg: 1, scope: !380, file: !1, line: 140, type: !48)
!503 = !DILocation(line: 140, column: 55, scope: !380)
!504 = !DILocation(line: 142, column: 42, scope: !380)
!505 = !DILocation(line: 142, column: 9, scope: !380)
!506 = !DILocation(line: 142, column: 2, scope: !380)
!507 = !DILocalVariable(name: "_a", arg: 1, scope: !381, file: !1, line: 147, type: !48)
!508 = !DILocation(line: 147, column: 50, scope: !381)
!509 = !DILocalVariable(name: "a", scope: !381, file: !1, line: 149, type: !28)
!510 = !DILocation(line: 149, column: 23, scope: !381)
!511 = !DILocation(line: 149, column: 50, scope: !381)
!512 = !DILocation(line: 149, column: 27, scope: !381)
!513 = !DILocalVariable(name: "bidder", scope: !381, file: !1, line: 150, type: !192)
!514 = !DILocation(line: 150, column: 37, scope: !381)
!515 = !DILocation(line: 152, column: 2, scope: !381)
!516 = !DILocalVariable(name: "magic_test", scope: !517, file: !1, line: 152, type: !47)
!517 = distinct !DILexicalBlock(scope: !381, file: !1, line: 152, column: 2)
!518 = !DILocation(line: 152, column: 2, scope: !517)
!519 = !DILocation(line: 152, column: 2, scope: !520)
!520 = !DILexicalBlockFile(scope: !517, file: !1, discriminator: 1)
!521 = !DILocation(line: 152, column: 2, scope: !522)
!522 = !DILexicalBlockFile(scope: !523, file: !1, discriminator: 2)
!523 = distinct !DILexicalBlock(scope: !517, file: !1, line: 152, column: 2)
!524 = !DILocation(line: 152, column: 2, scope: !525)
!525 = !DILexicalBlockFile(scope: !517, file: !1, discriminator: 3)
!526 = !DILocation(line: 155, column: 32, scope: !527)
!527 = distinct !DILexicalBlock(scope: !381, file: !1, line: 155, column: 6)
!528 = !DILocation(line: 155, column: 6, scope: !527)
!529 = !DILocation(line: 155, column: 44, scope: !527)
!530 = !DILocation(line: 155, column: 6, scope: !381)
!531 = !DILocation(line: 156, column: 3, scope: !527)
!532 = !DILocation(line: 158, column: 2, scope: !381)
!533 = !DILocation(line: 158, column: 10, scope: !381)
!534 = !DILocation(line: 158, column: 15, scope: !381)
!535 = !DILocation(line: 159, column: 2, scope: !381)
!536 = !DILocation(line: 159, column: 10, scope: !381)
!537 = !DILocation(line: 159, column: 15, scope: !381)
!538 = !DILocation(line: 160, column: 2, scope: !381)
!539 = !DILocation(line: 160, column: 10, scope: !381)
!540 = !DILocation(line: 160, column: 14, scope: !381)
!541 = !DILocation(line: 161, column: 2, scope: !381)
!542 = !DILocation(line: 161, column: 10, scope: !381)
!543 = !DILocation(line: 161, column: 15, scope: !381)
!544 = !DILocation(line: 162, column: 2, scope: !381)
!545 = !DILocation(line: 162, column: 10, scope: !381)
!546 = !DILocation(line: 162, column: 18, scope: !381)
!547 = !DILocation(line: 163, column: 2, scope: !381)
!548 = !DILocation(line: 163, column: 10, scope: !381)
!549 = !DILocation(line: 163, column: 15, scope: !381)
!550 = !DILocation(line: 165, column: 2, scope: !381)
!551 = !DILocation(line: 171, column: 1, scope: !381)
!552 = !DILocalVariable(name: "self", arg: 1, scope: !385, file: !1, line: 247, type: !192)
!553 = !DILocation(line: 247, column: 52, scope: !385)
!554 = !DILocalVariable(name: "filter", arg: 2, scope: !385, file: !1, line: 248, type: !193)
!555 = !DILocation(line: 248, column: 33, scope: !385)
!556 = !DILocalVariable(name: "buffer", scope: !385, file: !1, line: 250, type: !316)
!557 = !DILocation(line: 250, column: 23, scope: !385)
!558 = !DILocalVariable(name: "avail", scope: !385, file: !1, line: 251, type: !62)
!559 = !DILocation(line: 251, column: 10, scope: !385)
!560 = !DILocalVariable(name: "dicsize", scope: !385, file: !1, line: 252, type: !373)
!561 = !DILocation(line: 252, column: 11, scope: !385)
!562 = !DILocalVariable(name: "uncompressed_size", scope: !385, file: !1, line: 253, type: !315)
!563 = !DILocation(line: 253, column: 11, scope: !385)
!564 = !DILocalVariable(name: "bits_checked", scope: !385, file: !1, line: 254, type: !47)
!565 = !DILocation(line: 254, column: 6, scope: !385)
!566 = !DILocation(line: 256, column: 8, scope: !385)
!567 = !DILocation(line: 258, column: 39, scope: !385)
!568 = !DILocation(line: 258, column: 11, scope: !385)
!569 = !DILocation(line: 258, column: 9, scope: !385)
!570 = !DILocation(line: 259, column: 6, scope: !571)
!571 = distinct !DILexicalBlock(scope: !385, file: !1, line: 259, column: 6)
!572 = !DILocation(line: 259, column: 13, scope: !571)
!573 = !DILocation(line: 259, column: 6, scope: !385)
!574 = !DILocation(line: 260, column: 3, scope: !571)
!575 = !DILocation(line: 278, column: 15, scope: !385)
!576 = !DILocation(line: 279, column: 6, scope: !577)
!577 = distinct !DILexicalBlock(scope: !385, file: !1, line: 279, column: 6)
!578 = !DILocation(line: 279, column: 16, scope: !577)
!579 = !DILocation(line: 279, column: 6, scope: !385)
!580 = !DILocation(line: 280, column: 3, scope: !577)
!581 = !DILocation(line: 282, column: 6, scope: !582)
!582 = distinct !DILexicalBlock(scope: !385, file: !1, line: 282, column: 6)
!583 = !DILocation(line: 282, column: 16, scope: !582)
!584 = !DILocation(line: 282, column: 24, scope: !582)
!585 = !DILocation(line: 282, column: 27, scope: !586)
!586 = !DILexicalBlockFile(scope: !582, file: !1, discriminator: 1)
!587 = !DILocation(line: 282, column: 37, scope: !586)
!588 = !DILocation(line: 282, column: 6, scope: !586)
!589 = !DILocation(line: 283, column: 16, scope: !582)
!590 = !DILocation(line: 283, column: 3, scope: !582)
!591 = !DILocation(line: 289, column: 38, scope: !385)
!592 = !DILocation(line: 289, column: 44, scope: !385)
!593 = !DILocation(line: 289, column: 22, scope: !385)
!594 = !DILocation(line: 289, column: 20, scope: !385)
!595 = !DILocation(line: 290, column: 6, scope: !596)
!596 = distinct !DILexicalBlock(scope: !385, file: !1, line: 290, column: 6)
!597 = !DILocation(line: 290, column: 24, scope: !596)
!598 = !DILocation(line: 290, column: 6, scope: !385)
!599 = !DILocation(line: 291, column: 16, scope: !596)
!600 = !DILocation(line: 291, column: 3, scope: !596)
!601 = !DILocation(line: 300, column: 28, scope: !385)
!602 = !DILocation(line: 300, column: 34, scope: !385)
!603 = !DILocation(line: 300, column: 12, scope: !385)
!604 = !DILocation(line: 300, column: 10, scope: !385)
!605 = !DILocation(line: 301, column: 10, scope: !385)
!606 = !DILocation(line: 301, column: 2, scope: !385)
!607 = !DILocation(line: 327, column: 16, scope: !608)
!608 = distinct !DILexicalBlock(scope: !385, file: !1, line: 301, column: 19)
!609 = !DILocation(line: 328, column: 3, scope: !608)
!610 = !DILocation(line: 335, column: 7, scope: !611)
!611 = distinct !DILexicalBlock(scope: !608, file: !1, line: 335, column: 7)
!612 = !DILocation(line: 335, column: 15, scope: !611)
!613 = !DILocation(line: 335, column: 29, scope: !611)
!614 = !DILocation(line: 335, column: 32, scope: !615)
!615 = !DILexicalBlockFile(scope: !611, file: !1, discriminator: 1)
!616 = !DILocation(line: 335, column: 40, scope: !615)
!617 = !DILocation(line: 335, column: 54, scope: !615)
!618 = !DILocation(line: 336, column: 8, scope: !611)
!619 = !DILocation(line: 336, column: 16, scope: !611)
!620 = !DILocation(line: 336, column: 33, scope: !611)
!621 = !DILocation(line: 336, column: 38, scope: !611)
!622 = !DILocation(line: 337, column: 7, scope: !611)
!623 = !DILocation(line: 337, column: 20, scope: !611)
!624 = !DILocation(line: 335, column: 7, scope: !625)
!625 = !DILexicalBlockFile(scope: !608, file: !1, discriminator: 2)
!626 = !DILocation(line: 338, column: 17, scope: !627)
!627 = distinct !DILexicalBlock(scope: !611, file: !1, line: 337, column: 31)
!628 = !DILocation(line: 339, column: 4, scope: !627)
!629 = !DILocation(line: 344, column: 3, scope: !608)
!630 = !DILocation(line: 350, column: 10, scope: !385)
!631 = !DILocation(line: 350, column: 2, scope: !385)
!632 = !DILocation(line: 351, column: 1, scope: !385)
!633 = !DILocalVariable(name: "self", arg: 1, scope: !407, file: !1, line: 410, type: !193)
!634 = !DILocation(line: 410, column: 46, scope: !407)
!635 = !DILocation(line: 412, column: 2, scope: !407)
!636 = !DILocation(line: 412, column: 8, scope: !407)
!637 = !DILocation(line: 412, column: 13, scope: !407)
!638 = !DILocation(line: 413, column: 2, scope: !407)
!639 = !DILocation(line: 413, column: 8, scope: !407)
!640 = !DILocation(line: 413, column: 13, scope: !407)
!641 = !DILocation(line: 414, column: 30, scope: !407)
!642 = !DILocation(line: 414, column: 10, scope: !407)
!643 = !DILocation(line: 414, column: 2, scope: !407)
!644 = !DILocalVariable(name: "a", arg: 1, scope: !382, file: !1, line: 176, type: !48)
!645 = !DILocation(line: 176, column: 55, scope: !382)
!646 = !DILocation(line: 178, column: 42, scope: !382)
!647 = !DILocation(line: 178, column: 9, scope: !382)
!648 = !DILocation(line: 178, column: 2, scope: !382)
!649 = !DILocalVariable(name: "_a", arg: 1, scope: !383, file: !1, line: 183, type: !48)
!650 = !DILocation(line: 183, column: 50, scope: !383)
!651 = !DILocalVariable(name: "a", scope: !383, file: !1, line: 185, type: !28)
!652 = !DILocation(line: 185, column: 23, scope: !383)
!653 = !DILocation(line: 185, column: 50, scope: !383)
!654 = !DILocation(line: 185, column: 27, scope: !383)
!655 = !DILocalVariable(name: "bidder", scope: !383, file: !1, line: 186, type: !192)
!656 = !DILocation(line: 186, column: 37, scope: !383)
!657 = !DILocation(line: 188, column: 2, scope: !383)
!658 = !DILocalVariable(name: "magic_test", scope: !659, file: !1, line: 188, type: !47)
!659 = distinct !DILexicalBlock(scope: !383, file: !1, line: 188, column: 2)
!660 = !DILocation(line: 188, column: 2, scope: !659)
!661 = !DILocation(line: 188, column: 2, scope: !662)
!662 = !DILexicalBlockFile(scope: !659, file: !1, discriminator: 1)
!663 = !DILocation(line: 188, column: 2, scope: !664)
!664 = !DILexicalBlockFile(scope: !665, file: !1, discriminator: 2)
!665 = distinct !DILexicalBlock(scope: !659, file: !1, line: 188, column: 2)
!666 = !DILocation(line: 188, column: 2, scope: !667)
!667 = !DILexicalBlockFile(scope: !659, file: !1, discriminator: 3)
!668 = !DILocation(line: 191, column: 32, scope: !669)
!669 = distinct !DILexicalBlock(scope: !383, file: !1, line: 191, column: 6)
!670 = !DILocation(line: 191, column: 6, scope: !669)
!671 = !DILocation(line: 191, column: 44, scope: !669)
!672 = !DILocation(line: 191, column: 6, scope: !383)
!673 = !DILocation(line: 192, column: 3, scope: !669)
!674 = !DILocation(line: 194, column: 2, scope: !383)
!675 = !DILocation(line: 194, column: 10, scope: !383)
!676 = !DILocation(line: 194, column: 15, scope: !383)
!677 = !DILocation(line: 195, column: 2, scope: !383)
!678 = !DILocation(line: 195, column: 10, scope: !383)
!679 = !DILocation(line: 195, column: 15, scope: !383)
!680 = !DILocation(line: 196, column: 2, scope: !383)
!681 = !DILocation(line: 196, column: 10, scope: !383)
!682 = !DILocation(line: 196, column: 14, scope: !383)
!683 = !DILocation(line: 197, column: 2, scope: !383)
!684 = !DILocation(line: 197, column: 10, scope: !383)
!685 = !DILocation(line: 197, column: 15, scope: !383)
!686 = !DILocation(line: 198, column: 2, scope: !383)
!687 = !DILocation(line: 198, column: 10, scope: !383)
!688 = !DILocation(line: 198, column: 18, scope: !383)
!689 = !DILocation(line: 199, column: 2, scope: !383)
!690 = !DILocation(line: 199, column: 10, scope: !383)
!691 = !DILocation(line: 199, column: 15, scope: !383)
!692 = !DILocation(line: 201, column: 2, scope: !383)
!693 = !DILocation(line: 207, column: 1, scope: !383)
!694 = !DILocalVariable(name: "self", arg: 1, scope: !393, file: !1, line: 388, type: !192)
!695 = !DILocation(line: 388, column: 52, scope: !393)
!696 = !DILocalVariable(name: "filter", arg: 2, scope: !393, file: !1, line: 389, type: !193)
!697 = !DILocation(line: 389, column: 33, scope: !393)
!698 = !DILocation(line: 392, column: 8, scope: !393)
!699 = !DILocation(line: 393, column: 26, scope: !393)
!700 = !DILocation(line: 393, column: 10, scope: !393)
!701 = !DILocation(line: 393, column: 2, scope: !393)
!702 = !DILocalVariable(name: "self", arg: 1, scope: !408, file: !1, line: 418, type: !193)
!703 = !DILocation(line: 418, column: 46, scope: !408)
!704 = !DILocation(line: 420, column: 2, scope: !408)
!705 = !DILocation(line: 420, column: 8, scope: !408)
!706 = !DILocation(line: 420, column: 13, scope: !408)
!707 = !DILocation(line: 421, column: 2, scope: !408)
!708 = !DILocation(line: 421, column: 8, scope: !408)
!709 = !DILocation(line: 421, column: 13, scope: !408)
!710 = !DILocation(line: 422, column: 30, scope: !408)
!711 = !DILocation(line: 422, column: 10, scope: !408)
!712 = !DILocation(line: 422, column: 2, scope: !408)
!713 = !DILocalVariable(name: "pp", arg: 1, scope: !386, file: !387, line: 131, type: !67)
!714 = !DILocation(line: 131, column: 29, scope: !386)
!715 = !DILocalVariable(name: "p", scope: !386, file: !387, line: 133, type: !316)
!716 = !DILocation(line: 133, column: 23, scope: !386)
!717 = !DILocation(line: 133, column: 50, scope: !386)
!718 = !DILocation(line: 135, column: 37, scope: !386)
!719 = !DILocation(line: 135, column: 39, scope: !386)
!720 = !DILocation(line: 135, column: 21, scope: !386)
!721 = !DILocation(line: 135, column: 11, scope: !386)
!722 = !DILocation(line: 135, column: 44, scope: !386)
!723 = !DILocation(line: 135, column: 69, scope: !386)
!724 = !DILocation(line: 135, column: 53, scope: !725)
!725 = !DILexicalBlockFile(scope: !386, file: !387, discriminator: 1)
!726 = !DILocation(line: 135, column: 53, scope: !386)
!727 = !DILocation(line: 135, column: 51, scope: !386)
!728 = !DILocation(line: 135, column: 2, scope: !386)
!729 = !DILocalVariable(name: "pp", arg: 1, scope: !390, file: !387, line: 115, type: !67)
!730 = !DILocation(line: 115, column: 29, scope: !390)
!731 = !DILocalVariable(name: "p", scope: !390, file: !387, line: 117, type: !316)
!732 = !DILocation(line: 117, column: 23, scope: !390)
!733 = !DILocation(line: 117, column: 50, scope: !390)
!734 = !DILocalVariable(name: "p3", scope: !390, file: !387, line: 122, type: !37)
!735 = !DILocation(line: 122, column: 15, scope: !390)
!736 = !DILocation(line: 122, column: 20, scope: !390)
!737 = !DILocalVariable(name: "p2", scope: !390, file: !387, line: 123, type: !37)
!738 = !DILocation(line: 123, column: 15, scope: !390)
!739 = !DILocation(line: 123, column: 20, scope: !390)
!740 = !DILocalVariable(name: "p1", scope: !390, file: !387, line: 124, type: !37)
!741 = !DILocation(line: 124, column: 15, scope: !390)
!742 = !DILocation(line: 124, column: 20, scope: !390)
!743 = !DILocalVariable(name: "p0", scope: !390, file: !387, line: 125, type: !37)
!744 = !DILocation(line: 125, column: 15, scope: !390)
!745 = !DILocation(line: 125, column: 20, scope: !390)
!746 = !DILocation(line: 127, column: 11, scope: !390)
!747 = !DILocation(line: 127, column: 14, scope: !390)
!748 = !DILocation(line: 127, column: 24, scope: !390)
!749 = !DILocation(line: 127, column: 27, scope: !390)
!750 = !DILocation(line: 127, column: 21, scope: !390)
!751 = !DILocation(line: 127, column: 37, scope: !390)
!752 = !DILocation(line: 127, column: 40, scope: !390)
!753 = !DILocation(line: 127, column: 34, scope: !390)
!754 = !DILocation(line: 127, column: 48, scope: !390)
!755 = !DILocation(line: 127, column: 46, scope: !390)
!756 = !DILocation(line: 127, column: 2, scope: !390)
!757 = !DILocalVariable(name: "filter", arg: 1, scope: !394, file: !1, line: 354, type: !193)
!758 = !DILocation(line: 354, column: 45, scope: !394)
!759 = !DILocalVariable(name: "buffer", scope: !394, file: !1, line: 356, type: !316)
!760 = !DILocation(line: 356, column: 23, scope: !394)
!761 = !DILocalVariable(name: "avail", scope: !394, file: !1, line: 357, type: !62)
!762 = !DILocation(line: 357, column: 10, scope: !394)
!763 = !DILocalVariable(name: "bits_checked", scope: !394, file: !1, line: 358, type: !47)
!764 = !DILocation(line: 358, column: 6, scope: !394)
!765 = !DILocalVariable(name: "log2dic", scope: !394, file: !1, line: 359, type: !47)
!766 = !DILocation(line: 359, column: 6, scope: !394)
!767 = !DILocation(line: 361, column: 39, scope: !394)
!768 = !DILocation(line: 361, column: 11, scope: !394)
!769 = !DILocation(line: 361, column: 9, scope: !394)
!770 = !DILocation(line: 362, column: 6, scope: !771)
!771 = distinct !DILexicalBlock(scope: !394, file: !1, line: 362, column: 6)
!772 = !DILocation(line: 362, column: 13, scope: !771)
!773 = !DILocation(line: 362, column: 6, scope: !394)
!774 = !DILocation(line: 363, column: 3, scope: !771)
!775 = !DILocation(line: 368, column: 15, scope: !394)
!776 = !DILocation(line: 369, column: 13, scope: !777)
!777 = distinct !DILexicalBlock(scope: !394, file: !1, line: 369, column: 6)
!778 = !DILocation(line: 369, column: 6, scope: !777)
!779 = !DILocation(line: 369, column: 32, scope: !777)
!780 = !DILocation(line: 369, column: 6, scope: !394)
!781 = !DILocation(line: 370, column: 3, scope: !777)
!782 = !DILocation(line: 371, column: 15, scope: !394)
!783 = !DILocation(line: 374, column: 6, scope: !784)
!784 = distinct !DILexicalBlock(scope: !394, file: !1, line: 374, column: 6)
!785 = !DILocation(line: 374, column: 16, scope: !784)
!786 = !DILocation(line: 374, column: 21, scope: !784)
!787 = !DILocation(line: 374, column: 24, scope: !788)
!788 = !DILexicalBlockFile(scope: !784, file: !1, discriminator: 1)
!789 = !DILocation(line: 374, column: 34, scope: !788)
!790 = !DILocation(line: 374, column: 6, scope: !788)
!791 = !DILocation(line: 375, column: 3, scope: !784)
!792 = !DILocation(line: 376, column: 15, scope: !394)
!793 = !DILocation(line: 379, column: 12, scope: !394)
!794 = !DILocation(line: 379, column: 22, scope: !394)
!795 = !DILocation(line: 379, column: 10, scope: !394)
!796 = !DILocation(line: 380, column: 6, scope: !797)
!797 = distinct !DILexicalBlock(scope: !394, file: !1, line: 380, column: 6)
!798 = !DILocation(line: 380, column: 14, scope: !797)
!799 = !DILocation(line: 380, column: 19, scope: !797)
!800 = !DILocation(line: 380, column: 22, scope: !801)
!801 = !DILexicalBlockFile(scope: !797, file: !1, discriminator: 1)
!802 = !DILocation(line: 380, column: 30, scope: !801)
!803 = !DILocation(line: 380, column: 6, scope: !801)
!804 = !DILocation(line: 381, column: 3, scope: !797)
!805 = !DILocation(line: 382, column: 15, scope: !394)
!806 = !DILocation(line: 384, column: 10, scope: !394)
!807 = !DILocation(line: 384, column: 2, scope: !394)
!808 = !DILocation(line: 385, column: 1, scope: !394)
!809 = !DILocalVariable(name: "self", arg: 1, scope: !396, file: !1, line: 477, type: !193)
!810 = !DILocation(line: 477, column: 49, scope: !396)
!811 = !DILocalVariable(name: "out_block", scope: !396, file: !1, line: 480, type: !146)
!812 = !DILocation(line: 480, column: 8, scope: !396)
!813 = !DILocalVariable(name: "state", scope: !396, file: !1, line: 481, type: !319)
!814 = !DILocation(line: 481, column: 23, scope: !396)
!815 = !DILocalVariable(name: "ret", scope: !396, file: !1, line: 482, type: !47)
!816 = !DILocation(line: 482, column: 6, scope: !396)
!817 = !DILocation(line: 484, column: 33, scope: !396)
!818 = !DILocation(line: 484, column: 10, scope: !396)
!819 = !DILocation(line: 484, column: 8, scope: !396)
!820 = !DILocation(line: 485, column: 31, scope: !396)
!821 = !DILocation(line: 485, column: 12, scope: !396)
!822 = !DILocation(line: 486, column: 6, scope: !823)
!823 = distinct !DILexicalBlock(scope: !396, file: !1, line: 486, column: 6)
!824 = !DILocation(line: 486, column: 12, scope: !823)
!825 = !DILocation(line: 486, column: 20, scope: !823)
!826 = !DILocation(line: 486, column: 23, scope: !827)
!827 = !DILexicalBlockFile(scope: !823, file: !1, discriminator: 1)
!828 = !DILocation(line: 486, column: 33, scope: !827)
!829 = !DILocation(line: 486, column: 6, scope: !827)
!830 = !DILocation(line: 487, column: 22, scope: !831)
!831 = distinct !DILexicalBlock(scope: !823, file: !1, line: 486, column: 42)
!832 = !DILocation(line: 487, column: 28, scope: !831)
!833 = !DILocation(line: 487, column: 37, scope: !831)
!834 = !DILocation(line: 487, column: 3, scope: !831)
!835 = !DILocation(line: 489, column: 8, scope: !831)
!836 = !DILocation(line: 489, column: 3, scope: !831)
!837 = !DILocation(line: 490, column: 8, scope: !831)
!838 = !DILocation(line: 490, column: 3, scope: !831)
!839 = !DILocation(line: 491, column: 3, scope: !831)
!840 = !DILocation(line: 494, column: 15, scope: !396)
!841 = !DILocation(line: 494, column: 2, scope: !396)
!842 = !DILocation(line: 494, column: 8, scope: !396)
!843 = !DILocation(line: 494, column: 13, scope: !396)
!844 = !DILocation(line: 495, column: 2, scope: !396)
!845 = !DILocation(line: 495, column: 9, scope: !396)
!846 = !DILocation(line: 495, column: 24, scope: !396)
!847 = !DILocation(line: 496, column: 21, scope: !396)
!848 = !DILocation(line: 496, column: 2, scope: !396)
!849 = !DILocation(line: 496, column: 9, scope: !396)
!850 = !DILocation(line: 496, column: 19, scope: !396)
!851 = !DILocation(line: 497, column: 2, scope: !396)
!852 = !DILocation(line: 497, column: 8, scope: !396)
!853 = !DILocation(line: 497, column: 13, scope: !396)
!854 = !DILocation(line: 498, column: 2, scope: !396)
!855 = !DILocation(line: 498, column: 8, scope: !396)
!856 = !DILocation(line: 498, column: 13, scope: !396)
!857 = !DILocation(line: 499, column: 2, scope: !396)
!858 = !DILocation(line: 499, column: 8, scope: !396)
!859 = !DILocation(line: 499, column: 14, scope: !396)
!860 = !DILocation(line: 501, column: 2, scope: !396)
!861 = !DILocation(line: 501, column: 9, scope: !396)
!862 = !DILocation(line: 501, column: 16, scope: !396)
!863 = !DILocation(line: 501, column: 25, scope: !396)
!864 = !DILocation(line: 503, column: 27, scope: !396)
!865 = !DILocation(line: 503, column: 34, scope: !396)
!866 = !DILocation(line: 503, column: 2, scope: !396)
!867 = !DILocation(line: 503, column: 9, scope: !396)
!868 = !DILocation(line: 503, column: 16, scope: !396)
!869 = !DILocation(line: 503, column: 25, scope: !396)
!870 = !DILocation(line: 504, column: 28, scope: !396)
!871 = !DILocation(line: 504, column: 35, scope: !396)
!872 = !DILocation(line: 504, column: 2, scope: !396)
!873 = !DILocation(line: 504, column: 9, scope: !396)
!874 = !DILocation(line: 504, column: 16, scope: !396)
!875 = !DILocation(line: 504, column: 26, scope: !396)
!876 = !DILocation(line: 506, column: 2, scope: !396)
!877 = !DILocation(line: 506, column: 9, scope: !396)
!878 = !DILocation(line: 506, column: 15, scope: !396)
!879 = !DILocation(line: 507, column: 6, scope: !880)
!880 = distinct !DILexicalBlock(scope: !396, file: !1, line: 507, column: 6)
!881 = !DILocation(line: 507, column: 12, scope: !880)
!882 = !DILocation(line: 507, column: 17, scope: !880)
!883 = !DILocation(line: 507, column: 6, scope: !396)
!884 = !DILocation(line: 513, column: 3, scope: !885)
!885 = distinct !DILexicalBlock(scope: !880, file: !1, line: 507, column: 41)
!886 = !DILocation(line: 513, column: 10, scope: !885)
!887 = !DILocation(line: 513, column: 20, scope: !885)
!888 = !DILocation(line: 514, column: 3, scope: !885)
!889 = !DILocation(line: 516, column: 3, scope: !880)
!890 = !DILocation(line: 516, column: 10, scope: !880)
!891 = !DILocation(line: 516, column: 20, scope: !880)
!892 = !DILocation(line: 519, column: 6, scope: !893)
!893 = distinct !DILexicalBlock(scope: !396, file: !1, line: 519, column: 6)
!894 = !DILocation(line: 519, column: 12, scope: !893)
!895 = !DILocation(line: 519, column: 17, scope: !893)
!896 = !DILocation(line: 519, column: 6, scope: !396)
!897 = !DILocation(line: 520, column: 31, scope: !893)
!898 = !DILocation(line: 520, column: 38, scope: !893)
!899 = !DILocation(line: 520, column: 9, scope: !893)
!900 = !DILocation(line: 520, column: 7, scope: !893)
!901 = !DILocation(line: 520, column: 3, scope: !893)
!902 = !DILocation(line: 524, column: 30, scope: !893)
!903 = !DILocation(line: 524, column: 37, scope: !893)
!904 = !DILocation(line: 524, column: 9, scope: !893)
!905 = !DILocation(line: 524, column: 7, scope: !893)
!906 = !DILocation(line: 527, column: 6, scope: !907)
!907 = distinct !DILexicalBlock(scope: !396, file: !1, line: 527, column: 6)
!908 = !DILocation(line: 527, column: 10, scope: !907)
!909 = !DILocation(line: 527, column: 6, scope: !396)
!910 = !DILocation(line: 528, column: 3, scope: !907)
!911 = !DILocation(line: 531, column: 12, scope: !396)
!912 = !DILocation(line: 531, column: 18, scope: !396)
!913 = !DILocation(line: 531, column: 2, scope: !396)
!914 = !DILocation(line: 533, column: 7, scope: !396)
!915 = !DILocation(line: 533, column: 14, scope: !396)
!916 = !DILocation(line: 533, column: 2, scope: !396)
!917 = !DILocation(line: 534, column: 7, scope: !396)
!918 = !DILocation(line: 534, column: 2, scope: !396)
!919 = !DILocation(line: 535, column: 2, scope: !396)
!920 = !DILocation(line: 535, column: 8, scope: !396)
!921 = !DILocation(line: 535, column: 13, scope: !396)
!922 = !DILocation(line: 536, column: 2, scope: !396)
!923 = !DILocation(line: 537, column: 1, scope: !396)
!924 = !DILocalVariable(name: "self", arg: 1, scope: !397, file: !1, line: 657, type: !193)
!925 = !DILocation(line: 657, column: 44, scope: !397)
!926 = !DILocalVariable(name: "p", arg: 2, scope: !397, file: !1, line: 657, type: !88)
!927 = !DILocation(line: 657, column: 63, scope: !397)
!928 = !DILocalVariable(name: "state", scope: !397, file: !1, line: 659, type: !319)
!929 = !DILocation(line: 659, column: 23, scope: !397)
!930 = !DILocalVariable(name: "decompressed", scope: !397, file: !1, line: 660, type: !69)
!931 = !DILocation(line: 660, column: 9, scope: !397)
!932 = !DILocalVariable(name: "avail_in", scope: !397, file: !1, line: 661, type: !62)
!933 = !DILocation(line: 661, column: 10, scope: !397)
!934 = !DILocalVariable(name: "ret", scope: !397, file: !1, line: 662, type: !47)
!935 = !DILocation(line: 662, column: 6, scope: !397)
!936 = !DILocation(line: 664, column: 33, scope: !397)
!937 = !DILocation(line: 664, column: 39, scope: !397)
!938 = !DILocation(line: 664, column: 10, scope: !397)
!939 = !DILocation(line: 664, column: 8, scope: !397)
!940 = !DILocation(line: 667, column: 27, scope: !397)
!941 = !DILocation(line: 667, column: 34, scope: !397)
!942 = !DILocation(line: 667, column: 2, scope: !397)
!943 = !DILocation(line: 667, column: 9, scope: !397)
!944 = !DILocation(line: 667, column: 16, scope: !397)
!945 = !DILocation(line: 667, column: 25, scope: !397)
!946 = !DILocation(line: 668, column: 28, scope: !397)
!947 = !DILocation(line: 668, column: 35, scope: !397)
!948 = !DILocation(line: 668, column: 2, scope: !397)
!949 = !DILocation(line: 668, column: 9, scope: !397)
!950 = !DILocation(line: 668, column: 16, scope: !397)
!951 = !DILocation(line: 668, column: 26, scope: !397)
!952 = !DILocation(line: 671, column: 2, scope: !397)
!953 = !DILocation(line: 671, column: 9, scope: !954)
!954 = !DILexicalBlockFile(scope: !397, file: !1, discriminator: 1)
!955 = !DILocation(line: 671, column: 16, scope: !954)
!956 = !DILocation(line: 671, column: 23, scope: !954)
!957 = !DILocation(line: 671, column: 33, scope: !954)
!958 = !DILocation(line: 671, column: 37, scope: !954)
!959 = !DILocation(line: 671, column: 41, scope: !960)
!960 = !DILexicalBlockFile(scope: !397, file: !1, discriminator: 2)
!961 = !DILocation(line: 671, column: 48, scope: !960)
!962 = !DILocation(line: 671, column: 40, scope: !960)
!963 = !DILocation(line: 671, column: 2, scope: !964)
!964 = !DILexicalBlockFile(scope: !397, file: !1, discriminator: 3)
!965 = !DILocation(line: 672, column: 8, scope: !966)
!966 = distinct !DILexicalBlock(scope: !967, file: !1, line: 672, column: 7)
!967 = distinct !DILexicalBlock(scope: !397, file: !1, line: 671, column: 53)
!968 = !DILocation(line: 672, column: 15, scope: !966)
!969 = !DILocation(line: 672, column: 7, scope: !967)
!970 = !DILocation(line: 676, column: 20, scope: !971)
!971 = distinct !DILexicalBlock(scope: !966, file: !1, line: 672, column: 26)
!972 = !DILocation(line: 676, column: 10, scope: !971)
!973 = !DILocation(line: 676, column: 8, scope: !971)
!974 = !DILocation(line: 677, column: 8, scope: !975)
!975 = distinct !DILexicalBlock(scope: !971, file: !1, line: 677, column: 8)
!976 = !DILocation(line: 677, column: 12, scope: !975)
!977 = !DILocation(line: 677, column: 8, scope: !971)
!978 = !DILocation(line: 678, column: 13, scope: !975)
!979 = !DILocation(line: 678, column: 12, scope: !975)
!980 = !DILocation(line: 678, column: 5, scope: !975)
!981 = !DILocation(line: 679, column: 4, scope: !971)
!982 = !DILocation(line: 679, column: 11, scope: !971)
!983 = !DILocation(line: 679, column: 21, scope: !971)
!984 = !DILocation(line: 680, column: 3, scope: !971)
!985 = !DILocation(line: 682, column: 35, scope: !967)
!986 = !DILocation(line: 682, column: 41, scope: !967)
!987 = !DILocation(line: 682, column: 7, scope: !967)
!988 = !DILocation(line: 681, column: 3, scope: !967)
!989 = !DILocation(line: 681, column: 10, scope: !967)
!990 = !DILocation(line: 681, column: 17, scope: !967)
!991 = !DILocation(line: 681, column: 25, scope: !967)
!992 = !DILocation(line: 683, column: 7, scope: !993)
!993 = distinct !DILexicalBlock(scope: !967, file: !1, line: 683, column: 7)
!994 = !DILocation(line: 683, column: 14, scope: !993)
!995 = !DILocation(line: 683, column: 21, scope: !993)
!996 = !DILocation(line: 683, column: 29, scope: !993)
!997 = !DILocation(line: 683, column: 37, scope: !993)
!998 = !DILocation(line: 683, column: 40, scope: !999)
!999 = !DILexicalBlockFile(scope: !993, file: !1, discriminator: 1)
!1000 = !DILocation(line: 683, column: 49, scope: !999)
!1001 = !DILocation(line: 683, column: 7, scope: !999)
!1002 = !DILocation(line: 684, column: 23, scope: !1003)
!1003 = distinct !DILexicalBlock(scope: !993, file: !1, line: 683, column: 54)
!1004 = !DILocation(line: 684, column: 29, scope: !1003)
!1005 = !DILocation(line: 684, column: 38, scope: !1003)
!1006 = !DILocation(line: 684, column: 4, scope: !1003)
!1007 = !DILocation(line: 687, column: 4, scope: !1003)
!1008 = !DILocation(line: 689, column: 28, scope: !967)
!1009 = !DILocation(line: 689, column: 3, scope: !967)
!1010 = !DILocation(line: 689, column: 10, scope: !967)
!1011 = !DILocation(line: 689, column: 17, scope: !967)
!1012 = !DILocation(line: 689, column: 26, scope: !967)
!1013 = !DILocation(line: 692, column: 21, scope: !967)
!1014 = !DILocation(line: 692, column: 28, scope: !967)
!1015 = !DILocation(line: 693, column: 8, scope: !967)
!1016 = !DILocation(line: 693, column: 15, scope: !967)
!1017 = !DILocation(line: 693, column: 22, scope: !967)
!1018 = !DILocation(line: 693, column: 31, scope: !967)
!1019 = !DILocation(line: 693, column: 7, scope: !967)
!1020 = !DILocation(line: 692, column: 9, scope: !967)
!1021 = !DILocation(line: 692, column: 7, scope: !967)
!1022 = !DILocation(line: 694, column: 11, scope: !967)
!1023 = !DILocation(line: 694, column: 3, scope: !967)
!1024 = !DILocation(line: 696, column: 4, scope: !1025)
!1025 = distinct !DILexicalBlock(scope: !967, file: !1, line: 694, column: 16)
!1026 = !DILocation(line: 696, column: 11, scope: !1025)
!1027 = !DILocation(line: 696, column: 15, scope: !1025)
!1028 = !DILocation(line: 699, column: 34, scope: !1025)
!1029 = !DILocation(line: 699, column: 40, scope: !1025)
!1030 = !DILocation(line: 700, column: 8, scope: !1025)
!1031 = !DILocation(line: 700, column: 19, scope: !1025)
!1032 = !DILocation(line: 700, column: 26, scope: !1025)
!1033 = !DILocation(line: 700, column: 33, scope: !1025)
!1034 = !DILocation(line: 700, column: 17, scope: !1025)
!1035 = !DILocation(line: 699, column: 4, scope: !1025)
!1036 = !DILocation(line: 702, column: 8, scope: !1025)
!1037 = !DILocation(line: 702, column: 19, scope: !1025)
!1038 = !DILocation(line: 702, column: 26, scope: !1025)
!1039 = !DILocation(line: 702, column: 33, scope: !1025)
!1040 = !DILocation(line: 702, column: 17, scope: !1025)
!1041 = !DILocation(line: 701, column: 4, scope: !1025)
!1042 = !DILocation(line: 701, column: 11, scope: !1025)
!1043 = !DILocation(line: 701, column: 21, scope: !1025)
!1044 = !DILocation(line: 703, column: 4, scope: !1025)
!1045 = !DILocation(line: 705, column: 14, scope: !1025)
!1046 = !DILocation(line: 705, column: 20, scope: !1025)
!1047 = !DILocation(line: 705, column: 4, scope: !1025)
!1048 = !DILocation(line: 706, column: 4, scope: !1025)
!1049 = !DILocation(line: 671, column: 2, scope: !1050)
!1050 = !DILexicalBlockFile(scope: !397, file: !1, discriminator: 4)
!1051 = !DILocation(line: 710, column: 17, scope: !397)
!1052 = !DILocation(line: 710, column: 24, scope: !397)
!1053 = !DILocation(line: 710, column: 31, scope: !397)
!1054 = !DILocation(line: 710, column: 42, scope: !397)
!1055 = !DILocation(line: 710, column: 49, scope: !397)
!1056 = !DILocation(line: 710, column: 40, scope: !397)
!1057 = !DILocation(line: 710, column: 15, scope: !397)
!1058 = !DILocation(line: 711, column: 22, scope: !397)
!1059 = !DILocation(line: 711, column: 2, scope: !397)
!1060 = !DILocation(line: 711, column: 9, scope: !397)
!1061 = !DILocation(line: 711, column: 19, scope: !397)
!1062 = !DILocation(line: 712, column: 23, scope: !397)
!1063 = !DILocation(line: 712, column: 2, scope: !397)
!1064 = !DILocation(line: 712, column: 9, scope: !397)
!1065 = !DILocation(line: 712, column: 20, scope: !397)
!1066 = !DILocation(line: 713, column: 6, scope: !1067)
!1067 = distinct !DILexicalBlock(scope: !397, file: !1, line: 713, column: 6)
!1068 = !DILocation(line: 713, column: 19, scope: !1067)
!1069 = !DILocation(line: 713, column: 6, scope: !397)
!1070 = !DILocation(line: 714, column: 4, scope: !1067)
!1071 = !DILocation(line: 714, column: 6, scope: !1067)
!1072 = !DILocation(line: 714, column: 3, scope: !1067)
!1073 = !DILocation(line: 716, column: 8, scope: !1074)
!1074 = distinct !DILexicalBlock(scope: !1067, file: !1, line: 715, column: 7)
!1075 = !DILocation(line: 716, column: 15, scope: !1074)
!1076 = !DILocation(line: 716, column: 4, scope: !1074)
!1077 = !DILocation(line: 716, column: 6, scope: !1074)
!1078 = !DILocation(line: 717, column: 7, scope: !1079)
!1079 = distinct !DILexicalBlock(scope: !1074, file: !1, line: 717, column: 7)
!1080 = !DILocation(line: 717, column: 13, scope: !1079)
!1081 = !DILocation(line: 717, column: 18, scope: !1079)
!1082 = !DILocation(line: 717, column: 7, scope: !1074)
!1083 = !DILocation(line: 718, column: 30, scope: !1084)
!1084 = distinct !DILexicalBlock(scope: !1079, file: !1, line: 717, column: 42)
!1085 = !DILocation(line: 718, column: 37, scope: !1084)
!1086 = !DILocation(line: 719, column: 8, scope: !1084)
!1087 = !DILocation(line: 719, column: 22, scope: !1084)
!1088 = !DILocation(line: 719, column: 29, scope: !1084)
!1089 = !DILocation(line: 718, column: 19, scope: !1084)
!1090 = !DILocation(line: 718, column: 4, scope: !1084)
!1091 = !DILocation(line: 718, column: 11, scope: !1084)
!1092 = !DILocation(line: 718, column: 17, scope: !1084)
!1093 = !DILocation(line: 720, column: 8, scope: !1094)
!1094 = distinct !DILexicalBlock(scope: !1084, file: !1, line: 720, column: 8)
!1095 = !DILocation(line: 720, column: 15, scope: !1094)
!1096 = !DILocation(line: 720, column: 8, scope: !1084)
!1097 = !DILocation(line: 721, column: 21, scope: !1098)
!1098 = distinct !DILexicalBlock(scope: !1094, file: !1, line: 720, column: 20)
!1099 = !DILocation(line: 721, column: 11, scope: !1098)
!1100 = !DILocation(line: 721, column: 9, scope: !1098)
!1101 = !DILocation(line: 722, column: 9, scope: !1102)
!1102 = distinct !DILexicalBlock(scope: !1098, file: !1, line: 722, column: 9)
!1103 = !DILocation(line: 722, column: 13, scope: !1102)
!1104 = !DILocation(line: 722, column: 9, scope: !1098)
!1105 = !DILocation(line: 723, column: 14, scope: !1102)
!1106 = !DILocation(line: 723, column: 13, scope: !1102)
!1107 = !DILocation(line: 723, column: 6, scope: !1102)
!1108 = !DILocation(line: 724, column: 4, scope: !1098)
!1109 = !DILocation(line: 725, column: 3, scope: !1084)
!1110 = !DILocation(line: 727, column: 10, scope: !397)
!1111 = !DILocation(line: 727, column: 2, scope: !397)
!1112 = !DILocation(line: 728, column: 1, scope: !397)
!1113 = !DILocalVariable(name: "self", arg: 1, scope: !403, file: !1, line: 734, type: !193)
!1114 = !DILocation(line: 734, column: 45, scope: !403)
!1115 = !DILocalVariable(name: "state", scope: !403, file: !1, line: 736, type: !319)
!1116 = !DILocation(line: 736, column: 23, scope: !403)
!1117 = !DILocation(line: 738, column: 33, scope: !403)
!1118 = !DILocation(line: 738, column: 39, scope: !403)
!1119 = !DILocation(line: 738, column: 10, scope: !403)
!1120 = !DILocation(line: 738, column: 8, scope: !403)
!1121 = !DILocation(line: 739, column: 13, scope: !403)
!1122 = !DILocation(line: 739, column: 20, scope: !403)
!1123 = !DILocation(line: 739, column: 2, scope: !403)
!1124 = !DILocation(line: 740, column: 7, scope: !403)
!1125 = !DILocation(line: 740, column: 14, scope: !403)
!1126 = !DILocation(line: 740, column: 2, scope: !403)
!1127 = !DILocation(line: 741, column: 7, scope: !403)
!1128 = !DILocation(line: 741, column: 2, scope: !403)
!1129 = !DILocation(line: 742, column: 2, scope: !403)
!1130 = !DILocalVariable(name: "self", arg: 1, scope: !404, file: !1, line: 429, type: !193)
!1131 = !DILocation(line: 429, column: 39, scope: !404)
!1132 = !DILocalVariable(name: "ret", arg: 2, scope: !404, file: !1, line: 429, type: !47)
!1133 = !DILocation(line: 429, column: 49, scope: !404)
!1134 = !DILocation(line: 432, column: 10, scope: !404)
!1135 = !DILocation(line: 432, column: 2, scope: !404)
!1136 = !DILocation(line: 435, column: 3, scope: !1137)
!1137 = distinct !DILexicalBlock(scope: !404, file: !1, line: 432, column: 15)
!1138 = !DILocation(line: 437, column: 22, scope: !1137)
!1139 = !DILocation(line: 437, column: 28, scope: !1137)
!1140 = !DILocation(line: 437, column: 37, scope: !1137)
!1141 = !DILocation(line: 437, column: 3, scope: !1137)
!1142 = !DILocation(line: 439, column: 3, scope: !1137)
!1143 = !DILocation(line: 441, column: 22, scope: !1137)
!1144 = !DILocation(line: 441, column: 28, scope: !1137)
!1145 = !DILocation(line: 441, column: 37, scope: !1137)
!1146 = !DILocation(line: 441, column: 3, scope: !1137)
!1147 = !DILocation(line: 443, column: 3, scope: !1137)
!1148 = !DILocation(line: 445, column: 22, scope: !1137)
!1149 = !DILocation(line: 445, column: 28, scope: !1137)
!1150 = !DILocation(line: 445, column: 37, scope: !1137)
!1151 = !DILocation(line: 445, column: 3, scope: !1137)
!1152 = !DILocation(line: 448, column: 3, scope: !1137)
!1153 = !DILocation(line: 450, column: 22, scope: !1137)
!1154 = !DILocation(line: 450, column: 28, scope: !1137)
!1155 = !DILocation(line: 450, column: 37, scope: !1137)
!1156 = !DILocation(line: 450, column: 3, scope: !1137)
!1157 = !DILocation(line: 453, column: 3, scope: !1137)
!1158 = !DILocation(line: 455, column: 22, scope: !1137)
!1159 = !DILocation(line: 455, column: 28, scope: !1137)
!1160 = !DILocation(line: 455, column: 37, scope: !1137)
!1161 = !DILocation(line: 455, column: 3, scope: !1137)
!1162 = !DILocation(line: 458, column: 3, scope: !1137)
!1163 = !DILocation(line: 460, column: 22, scope: !1137)
!1164 = !DILocation(line: 460, column: 28, scope: !1137)
!1165 = !DILocation(line: 460, column: 37, scope: !1137)
!1166 = !DILocation(line: 460, column: 3, scope: !1137)
!1167 = !DILocation(line: 463, column: 3, scope: !1137)
!1168 = !DILocation(line: 466, column: 22, scope: !1137)
!1169 = !DILocation(line: 466, column: 28, scope: !1137)
!1170 = !DILocation(line: 466, column: 37, scope: !1137)
!1171 = !DILocation(line: 466, column: 3, scope: !1137)
!1172 = !DILocation(line: 469, column: 3, scope: !1137)
!1173 = !DILocation(line: 471, column: 1, scope: !404)
!1174 = !DILocalVariable(name: "self", arg: 1, scope: !398, file: !1, line: 540, type: !193)
!1175 = !DILocation(line: 540, column: 39, scope: !398)
!1176 = !DILocalVariable(name: "state", scope: !398, file: !1, line: 542, type: !319)
!1177 = !DILocation(line: 542, column: 23, scope: !398)
!1178 = !DILocalVariable(name: "h", scope: !398, file: !1, line: 543, type: !316)
!1179 = !DILocation(line: 543, column: 23, scope: !398)
!1180 = !DILocalVariable(name: "filters", scope: !398, file: !1, line: 544, type: !1181)
!1181 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1182, size: 256, align: 64, elements: !1190)
!1182 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter", file: !1183, line: 65, baseType: !1184)
!1183 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/filter.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!1184 = !DICompositeType(tag: DW_TAG_structure_type, file: !1183, line: 43, size: 128, align: 64, elements: !1185)
!1185 = !{!1186, !1189}
!1186 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !1184, file: !1183, line: 54, baseType: !1187, size: 64, align: 64)
!1187 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !1188, line: 63, baseType: !315)
!1188 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!1189 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !1184, file: !1183, line: 63, baseType: !146, size: 64, align: 64, offset: 64)
!1190 = !{!1191}
!1191 = !DISubrange(count: 2)
!1192 = !DILocation(line: 544, column: 14, scope: !398)
!1193 = !DILocalVariable(name: "props", scope: !398, file: !1, line: 545, type: !1194)
!1194 = !DICompositeType(tag: DW_TAG_array_type, baseType: !318, size: 40, align: 8, elements: !1195)
!1195 = !{!1196}
!1196 = !DISubrange(count: 5)
!1197 = !DILocation(line: 545, column: 16, scope: !398)
!1198 = !DILocalVariable(name: "avail_in", scope: !398, file: !1, line: 546, type: !62)
!1199 = !DILocation(line: 546, column: 10, scope: !398)
!1200 = !DILocalVariable(name: "dicsize", scope: !398, file: !1, line: 547, type: !373)
!1201 = !DILocation(line: 547, column: 11, scope: !398)
!1202 = !DILocalVariable(name: "log2dic", scope: !398, file: !1, line: 548, type: !47)
!1203 = !DILocation(line: 548, column: 6, scope: !398)
!1204 = !DILocalVariable(name: "ret", scope: !398, file: !1, line: 548, type: !47)
!1205 = !DILocation(line: 548, column: 15, scope: !398)
!1206 = !DILocation(line: 550, column: 33, scope: !398)
!1207 = !DILocation(line: 550, column: 39, scope: !398)
!1208 = !DILocation(line: 550, column: 10, scope: !398)
!1209 = !DILocation(line: 550, column: 8, scope: !398)
!1210 = !DILocation(line: 551, column: 34, scope: !398)
!1211 = !DILocation(line: 551, column: 40, scope: !398)
!1212 = !DILocation(line: 551, column: 6, scope: !398)
!1213 = !DILocation(line: 551, column: 4, scope: !398)
!1214 = !DILocation(line: 552, column: 6, scope: !1215)
!1215 = distinct !DILexicalBlock(scope: !398, file: !1, line: 552, column: 6)
!1216 = !DILocation(line: 552, column: 8, scope: !1215)
!1217 = !DILocation(line: 552, column: 6, scope: !398)
!1218 = !DILocation(line: 553, column: 3, scope: !1215)
!1219 = !DILocation(line: 556, column: 20, scope: !398)
!1220 = !DILocation(line: 556, column: 2, scope: !398)
!1221 = !DILocation(line: 556, column: 9, scope: !398)
!1222 = !DILocation(line: 556, column: 18, scope: !398)
!1223 = !DILocation(line: 561, column: 2, scope: !398)
!1224 = !DILocation(line: 561, column: 11, scope: !398)
!1225 = !DILocation(line: 564, column: 12, scope: !398)
!1226 = !DILocation(line: 564, column: 17, scope: !398)
!1227 = !DILocation(line: 564, column: 10, scope: !398)
!1228 = !DILocation(line: 565, column: 6, scope: !1229)
!1229 = distinct !DILexicalBlock(scope: !398, file: !1, line: 565, column: 6)
!1230 = !DILocation(line: 565, column: 14, scope: !1229)
!1231 = !DILocation(line: 565, column: 19, scope: !1229)
!1232 = !DILocation(line: 565, column: 22, scope: !1233)
!1233 = !DILexicalBlockFile(scope: !1229, file: !1, discriminator: 1)
!1234 = !DILocation(line: 565, column: 30, scope: !1233)
!1235 = !DILocation(line: 565, column: 6, scope: !1233)
!1236 = !DILocation(line: 566, column: 3, scope: !1229)
!1237 = !DILocation(line: 567, column: 18, scope: !398)
!1238 = !DILocation(line: 567, column: 15, scope: !398)
!1239 = !DILocation(line: 567, column: 10, scope: !398)
!1240 = !DILocation(line: 568, column: 6, scope: !1241)
!1241 = distinct !DILexicalBlock(scope: !398, file: !1, line: 568, column: 6)
!1242 = !DILocation(line: 568, column: 14, scope: !1241)
!1243 = !DILocation(line: 568, column: 6, scope: !398)
!1244 = !DILocation(line: 569, column: 15, scope: !1241)
!1245 = !DILocation(line: 569, column: 23, scope: !1241)
!1246 = !DILocation(line: 569, column: 32, scope: !1241)
!1247 = !DILocation(line: 569, column: 37, scope: !1241)
!1248 = !DILocation(line: 569, column: 29, scope: !1241)
!1249 = !DILocation(line: 569, column: 11, scope: !1241)
!1250 = !DILocation(line: 569, column: 3, scope: !1241)
!1251 = !DILocation(line: 570, column: 18, scope: !398)
!1252 = !DILocation(line: 570, column: 23, scope: !398)
!1253 = !DILocation(line: 570, column: 27, scope: !398)
!1254 = !DILocation(line: 570, column: 2, scope: !398)
!1255 = !DILocation(line: 573, column: 32, scope: !398)
!1256 = !DILocation(line: 573, column: 38, scope: !398)
!1257 = !DILocation(line: 573, column: 2, scope: !398)
!1258 = !DILocation(line: 574, column: 2, scope: !398)
!1259 = !DILocation(line: 574, column: 9, scope: !398)
!1260 = !DILocation(line: 574, column: 19, scope: !398)
!1261 = !DILocation(line: 576, column: 2, scope: !398)
!1262 = !DILocation(line: 576, column: 13, scope: !398)
!1263 = !DILocation(line: 576, column: 16, scope: !398)
!1264 = !DILocation(line: 577, column: 2, scope: !398)
!1265 = !DILocation(line: 577, column: 13, scope: !398)
!1266 = !DILocation(line: 577, column: 21, scope: !398)
!1267 = !DILocation(line: 578, column: 2, scope: !398)
!1268 = !DILocation(line: 578, column: 13, scope: !398)
!1269 = !DILocation(line: 578, column: 16, scope: !398)
!1270 = !DILocation(line: 579, column: 2, scope: !398)
!1271 = !DILocation(line: 579, column: 13, scope: !398)
!1272 = !DILocation(line: 579, column: 21, scope: !398)
!1273 = !DILocation(line: 581, column: 32, scope: !398)
!1274 = !DILocation(line: 581, column: 50, scope: !398)
!1275 = !DILocation(line: 581, column: 8, scope: !398)
!1276 = !DILocation(line: 581, column: 6, scope: !398)
!1277 = !DILocation(line: 582, column: 6, scope: !1278)
!1278 = distinct !DILexicalBlock(scope: !398, file: !1, line: 582, column: 6)
!1279 = !DILocation(line: 582, column: 10, scope: !1278)
!1280 = !DILocation(line: 582, column: 6, scope: !398)
!1281 = !DILocation(line: 583, column: 13, scope: !1282)
!1282 = distinct !DILexicalBlock(scope: !1278, file: !1, line: 582, column: 22)
!1283 = !DILocation(line: 583, column: 19, scope: !1282)
!1284 = !DILocation(line: 583, column: 3, scope: !1282)
!1285 = !DILocation(line: 584, column: 3, scope: !1282)
!1286 = !DILocation(line: 586, column: 27, scope: !398)
!1287 = !DILocation(line: 586, column: 34, scope: !398)
!1288 = !DILocation(line: 586, column: 43, scope: !398)
!1289 = !DILocation(line: 586, column: 8, scope: !398)
!1290 = !DILocation(line: 586, column: 6, scope: !398)
!1291 = !DILocation(line: 587, column: 7, scope: !398)
!1292 = !DILocation(line: 587, column: 18, scope: !398)
!1293 = !DILocation(line: 587, column: 2, scope: !398)
!1294 = !DILocation(line: 588, column: 6, scope: !1295)
!1295 = distinct !DILexicalBlock(scope: !398, file: !1, line: 588, column: 6)
!1296 = !DILocation(line: 588, column: 10, scope: !1295)
!1297 = !DILocation(line: 588, column: 6, scope: !398)
!1298 = !DILocation(line: 589, column: 13, scope: !1299)
!1299 = distinct !DILexicalBlock(scope: !1295, file: !1, line: 588, column: 22)
!1300 = !DILocation(line: 589, column: 19, scope: !1299)
!1301 = !DILocation(line: 589, column: 3, scope: !1299)
!1302 = !DILocation(line: 590, column: 3, scope: !1299)
!1303 = !DILocation(line: 592, column: 2, scope: !398)
!1304 = !DILocation(line: 593, column: 1, scope: !398)
!1305 = !DILocalVariable(name: "self", arg: 1, scope: !402, file: !1, line: 596, type: !193)
!1306 = !DILocation(line: 596, column: 39, scope: !402)
!1307 = !DILocalVariable(name: "state", scope: !402, file: !1, line: 598, type: !319)
!1308 = !DILocation(line: 598, column: 23, scope: !402)
!1309 = !DILocalVariable(name: "f", scope: !402, file: !1, line: 599, type: !316)
!1310 = !DILocation(line: 599, column: 23, scope: !402)
!1311 = !DILocalVariable(name: "avail_in", scope: !402, file: !1, line: 600, type: !62)
!1312 = !DILocation(line: 600, column: 10, scope: !402)
!1313 = !DILocalVariable(name: "tail", scope: !402, file: !1, line: 601, type: !47)
!1314 = !DILocation(line: 601, column: 6, scope: !402)
!1315 = !DILocation(line: 603, column: 33, scope: !402)
!1316 = !DILocation(line: 603, column: 39, scope: !402)
!1317 = !DILocation(line: 603, column: 10, scope: !402)
!1318 = !DILocation(line: 603, column: 8, scope: !402)
!1319 = !DILocation(line: 604, column: 6, scope: !1320)
!1320 = distinct !DILexicalBlock(scope: !402, file: !1, line: 604, column: 6)
!1321 = !DILocation(line: 604, column: 13, scope: !1320)
!1322 = !DILocation(line: 604, column: 22, scope: !1320)
!1323 = !DILocation(line: 604, column: 6, scope: !402)
!1324 = !DILocation(line: 605, column: 8, scope: !1320)
!1325 = !DILocation(line: 605, column: 3, scope: !1320)
!1326 = !DILocation(line: 607, column: 8, scope: !1320)
!1327 = !DILocation(line: 608, column: 34, scope: !402)
!1328 = !DILocation(line: 608, column: 40, scope: !402)
!1329 = !DILocation(line: 608, column: 50, scope: !402)
!1330 = !DILocation(line: 608, column: 6, scope: !402)
!1331 = !DILocation(line: 608, column: 4, scope: !402)
!1332 = !DILocation(line: 609, column: 6, scope: !1333)
!1333 = distinct !DILexicalBlock(scope: !402, file: !1, line: 609, column: 6)
!1334 = !DILocation(line: 609, column: 8, scope: !1333)
!1335 = !DILocation(line: 609, column: 16, scope: !1333)
!1336 = !DILocation(line: 609, column: 19, scope: !1337)
!1337 = !DILexicalBlockFile(scope: !1333, file: !1, discriminator: 1)
!1338 = !DILocation(line: 609, column: 28, scope: !1337)
!1339 = !DILocation(line: 609, column: 6, scope: !1337)
!1340 = !DILocation(line: 610, column: 3, scope: !1333)
!1341 = !DILocation(line: 611, column: 6, scope: !1342)
!1342 = distinct !DILexicalBlock(scope: !402, file: !1, line: 611, column: 6)
!1343 = !DILocation(line: 611, column: 8, scope: !1342)
!1344 = !DILocation(line: 611, column: 16, scope: !1342)
!1345 = !DILocation(line: 611, column: 19, scope: !1346)
!1346 = !DILexicalBlockFile(scope: !1342, file: !1, discriminator: 1)
!1347 = !DILocation(line: 611, column: 30, scope: !1346)
!1348 = !DILocation(line: 611, column: 28, scope: !1346)
!1349 = !DILocation(line: 611, column: 6, scope: !1346)
!1350 = !DILocation(line: 612, column: 22, scope: !1351)
!1351 = distinct !DILexicalBlock(scope: !1342, file: !1, line: 611, column: 36)
!1352 = !DILocation(line: 612, column: 28, scope: !1351)
!1353 = !DILocation(line: 612, column: 37, scope: !1351)
!1354 = !DILocation(line: 612, column: 3, scope: !1351)
!1355 = !DILocation(line: 614, column: 3, scope: !1351)
!1356 = !DILocation(line: 619, column: 6, scope: !1357)
!1357 = distinct !DILexicalBlock(scope: !402, file: !1, line: 619, column: 6)
!1358 = !DILocation(line: 619, column: 13, scope: !1357)
!1359 = !DILocation(line: 619, column: 38, scope: !1357)
!1360 = !DILocation(line: 619, column: 22, scope: !1357)
!1361 = !DILocation(line: 619, column: 19, scope: !1357)
!1362 = !DILocation(line: 619, column: 6, scope: !402)
!1363 = !DILocation(line: 620, column: 22, scope: !1364)
!1364 = distinct !DILexicalBlock(scope: !1357, file: !1, line: 619, column: 42)
!1365 = !DILocation(line: 620, column: 28, scope: !1364)
!1366 = !DILocation(line: 620, column: 37, scope: !1364)
!1367 = !DILocation(line: 620, column: 3, scope: !1364)
!1368 = !DILocation(line: 622, column: 3, scope: !1364)
!1369 = !DILocation(line: 626, column: 16, scope: !1370)
!1370 = distinct !DILexicalBlock(scope: !402, file: !1, line: 626, column: 6)
!1371 = !DILocation(line: 626, column: 23, scope: !1370)
!1372 = !DILocation(line: 626, column: 53, scope: !1370)
!1373 = !DILocation(line: 626, column: 55, scope: !1370)
!1374 = !DILocation(line: 626, column: 37, scope: !1370)
!1375 = !DILocation(line: 626, column: 34, scope: !1370)
!1376 = !DILocation(line: 626, column: 6, scope: !402)
!1377 = !DILocation(line: 627, column: 22, scope: !1378)
!1378 = distinct !DILexicalBlock(scope: !1370, file: !1, line: 626, column: 61)
!1379 = !DILocation(line: 627, column: 28, scope: !1378)
!1380 = !DILocation(line: 627, column: 37, scope: !1378)
!1381 = !DILocation(line: 627, column: 3, scope: !1378)
!1382 = !DILocation(line: 629, column: 3, scope: !1378)
!1383 = !DILocation(line: 633, column: 6, scope: !1384)
!1384 = distinct !DILexicalBlock(scope: !402, file: !1, line: 633, column: 6)
!1385 = !DILocation(line: 633, column: 13, scope: !1384)
!1386 = !DILocation(line: 633, column: 22, scope: !1384)
!1387 = !DILocation(line: 633, column: 27, scope: !1384)
!1388 = !DILocation(line: 634, column: 16, scope: !1384)
!1389 = !DILocation(line: 634, column: 23, scope: !1384)
!1390 = !DILocation(line: 634, column: 35, scope: !1384)
!1391 = !DILocation(line: 634, column: 33, scope: !1384)
!1392 = !DILocation(line: 634, column: 59, scope: !1384)
!1393 = !DILocation(line: 634, column: 61, scope: !1384)
!1394 = !DILocation(line: 634, column: 43, scope: !1384)
!1395 = !DILocation(line: 634, column: 40, scope: !1384)
!1396 = !DILocation(line: 633, column: 6, scope: !1397)
!1397 = !DILexicalBlockFile(scope: !402, file: !1, discriminator: 1)
!1398 = !DILocation(line: 635, column: 22, scope: !1399)
!1399 = distinct !DILexicalBlock(scope: !1384, file: !1, line: 634, column: 68)
!1400 = !DILocation(line: 635, column: 28, scope: !1399)
!1401 = !DILocation(line: 635, column: 37, scope: !1399)
!1402 = !DILocation(line: 635, column: 3, scope: !1399)
!1403 = !DILocation(line: 637, column: 3, scope: !1399)
!1404 = !DILocation(line: 639, column: 32, scope: !402)
!1405 = !DILocation(line: 639, column: 38, scope: !402)
!1406 = !DILocation(line: 639, column: 48, scope: !402)
!1407 = !DILocation(line: 639, column: 2, scope: !402)
!1408 = !DILocation(line: 643, column: 22, scope: !1409)
!1409 = distinct !DILexicalBlock(scope: !402, file: !1, line: 643, column: 6)
!1410 = !DILocation(line: 643, column: 28, scope: !1409)
!1411 = !DILocation(line: 643, column: 6, scope: !1409)
!1412 = !DILocation(line: 643, column: 38, scope: !1409)
!1413 = !DILocation(line: 643, column: 6, scope: !402)
!1414 = !DILocation(line: 644, column: 3, scope: !1415)
!1415 = distinct !DILexicalBlock(scope: !1409, file: !1, line: 643, column: 44)
!1416 = !DILocation(line: 644, column: 10, scope: !1415)
!1417 = !DILocation(line: 644, column: 20, scope: !1415)
!1418 = !DILocation(line: 645, column: 3, scope: !1415)
!1419 = !DILocation(line: 645, column: 10, scope: !1415)
!1420 = !DILocation(line: 645, column: 16, scope: !1415)
!1421 = !DILocation(line: 646, column: 3, scope: !1415)
!1422 = !DILocation(line: 646, column: 10, scope: !1415)
!1423 = !DILocation(line: 646, column: 21, scope: !1415)
!1424 = !DILocation(line: 647, column: 3, scope: !1415)
!1425 = !DILocation(line: 647, column: 10, scope: !1415)
!1426 = !DILocation(line: 647, column: 20, scope: !1415)
!1427 = !DILocation(line: 648, column: 3, scope: !1415)
!1428 = !DILocation(line: 648, column: 10, scope: !1415)
!1429 = !DILocation(line: 648, column: 14, scope: !1415)
!1430 = !DILocation(line: 649, column: 2, scope: !1415)
!1431 = !DILocation(line: 650, column: 2, scope: !402)
!1432 = !DILocation(line: 651, column: 1, scope: !402)
!1433 = !DILocalVariable(name: "pp", arg: 1, scope: !399, file: !387, line: 177, type: !146)
!1434 = !DILocation(line: 177, column: 23, scope: !399)
!1435 = !DILocalVariable(name: "u", arg: 2, scope: !399, file: !387, line: 177, type: !373)
!1436 = !DILocation(line: 177, column: 36, scope: !399)
!1437 = !DILocalVariable(name: "p", scope: !399, file: !387, line: 179, type: !366)
!1438 = !DILocation(line: 179, column: 17, scope: !399)
!1439 = !DILocation(line: 179, column: 38, scope: !399)
!1440 = !DILocation(line: 181, column: 9, scope: !399)
!1441 = !DILocation(line: 181, column: 11, scope: !399)
!1442 = !DILocation(line: 181, column: 2, scope: !399)
!1443 = !DILocation(line: 181, column: 7, scope: !399)
!1444 = !DILocation(line: 182, column: 10, scope: !399)
!1445 = !DILocation(line: 182, column: 12, scope: !399)
!1446 = !DILocation(line: 182, column: 18, scope: !399)
!1447 = !DILocation(line: 182, column: 9, scope: !399)
!1448 = !DILocation(line: 182, column: 2, scope: !399)
!1449 = !DILocation(line: 182, column: 7, scope: !399)
!1450 = !DILocation(line: 183, column: 10, scope: !399)
!1451 = !DILocation(line: 183, column: 12, scope: !399)
!1452 = !DILocation(line: 183, column: 19, scope: !399)
!1453 = !DILocation(line: 183, column: 9, scope: !399)
!1454 = !DILocation(line: 183, column: 2, scope: !399)
!1455 = !DILocation(line: 183, column: 7, scope: !399)
!1456 = !DILocation(line: 184, column: 10, scope: !399)
!1457 = !DILocation(line: 184, column: 12, scope: !399)
!1458 = !DILocation(line: 184, column: 19, scope: !399)
!1459 = !DILocation(line: 184, column: 9, scope: !399)
!1460 = !DILocation(line: 184, column: 2, scope: !399)
!1461 = !DILocation(line: 184, column: 7, scope: !399)
!1462 = !DILocation(line: 185, column: 1, scope: !399)
