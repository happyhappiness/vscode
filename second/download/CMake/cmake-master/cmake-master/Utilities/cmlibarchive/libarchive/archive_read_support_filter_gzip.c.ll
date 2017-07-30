; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_support_filter_gzip.c'
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
%struct.private_data = type { %struct.z_stream_s, i8, i8*, i64, i64, i64, i8 }
%struct.z_stream_s = type { i8*, i32, i64, i8*, i32, i64, i8*, %struct.internal_state*, i8* (i8*, i32, i32)*, void (i8*, i8*)*, i8*, i32, i64, i64 }
%struct.internal_state = type { i32 }

@.str = private unnamed_addr constant [33 x i8] c"archive_read_support_filter_gzip\00", align 1
@.str.1 = private unnamed_addr constant [5 x i8] c"gzip\00", align 1
@.str.2 = private unnamed_addr constant [4 x i8] c"\1F\8B\08\00", align 1
@gzip_bidder_init.out_block_size = internal constant i64 65536, align 8
@.str.3 = private unnamed_addr constant [43 x i8] c"Can't allocate data for gzip decompression\00", align 1
@.str.4 = private unnamed_addr constant [21 x i8] c"truncated gzip input\00", align 1
@.str.5 = private unnamed_addr constant [26 x i8] c"gzip decompression failed\00", align 1
@.str.6 = private unnamed_addr constant [6 x i8] c"1.2.3\00", align 1
@.str.7 = private unnamed_addr constant [73 x i8] c"Internal error initializing compression library: invalid setup parameter\00", align 1
@.str.8 = private unnamed_addr constant [63 x i8] c"Internal error initializing compression library: out of memory\00", align 1
@.str.9 = private unnamed_addr constant [73 x i8] c"Internal error initializing compression library: invalid library version\00", align 1
@.str.10 = private unnamed_addr constant [64 x i8] c"Internal error initializing compression library:  Zlib error %d\00", align 1
@.str.11 = private unnamed_addr constant [37 x i8] c"Failed to clean up gzip decompressor\00", align 1
@.str.12 = private unnamed_addr constant [35 x i8] c"Failed to clean up gzip compressor\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_read_support_compression_gzip(%struct.archive* %a) #0 !dbg !342 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !360, metadata !361), !dbg !362
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !363
  %call = call i32 @archive_read_support_filter_gzip(%struct.archive* %0), !dbg !364
  ret i32 %call, !dbg !365
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define i32 @archive_read_support_filter_gzip(%struct.archive* %_a) #0 !dbg !343 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_read*, align 8
  %bidder = alloca %struct.archive_read_filter_bidder*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !366, metadata !361), !dbg !367
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !368, metadata !361), !dbg !369
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !370
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !371
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !369
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter_bidder** %bidder, metadata !372, metadata !361), !dbg !373
  br label %do.body, !dbg !374

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !375, metadata !361), !dbg !377
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !378
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 14594245, i32 1, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str, i32 0, i32 0)), !dbg !378
  store i32 %call, i32* %magic_test, align 4, !dbg !378
  %3 = load i32, i32* %magic_test, align 4, !dbg !378
  %cmp = icmp eq i32 %3, -30, !dbg !378
  br i1 %cmp, label %if.then, label %if.end, !dbg !378

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !380
  br label %return, !dbg !380

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !383

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !385
  %call1 = call i32 @__archive_read_get_bidder(%struct.archive_read* %4, %struct.archive_read_filter_bidder** %bidder), !dbg !387
  %cmp2 = icmp ne i32 %call1, 0, !dbg !388
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !389

if.then3:                                         ; preds = %do.end
  store i32 -30, i32* %retval, align 4, !dbg !390
  br label %return, !dbg !390

if.end4:                                          ; preds = %do.end
  %5 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !391
  %data = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %5, i32 0, i32 0, !dbg !392
  store i8* null, i8** %data, align 8, !dbg !393
  %6 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !394
  %name = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %6, i32 0, i32 1, !dbg !395
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.1, i32 0, i32 0), i8** %name, align 8, !dbg !396
  %7 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !397
  %bid = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %7, i32 0, i32 2, !dbg !398
  store i32 (%struct.archive_read_filter_bidder*, %struct.archive_read_filter*)* @gzip_bidder_bid, i32 (%struct.archive_read_filter_bidder*, %struct.archive_read_filter*)** %bid, align 8, !dbg !399
  %8 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !400
  %init = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %8, i32 0, i32 3, !dbg !401
  store i32 (%struct.archive_read_filter*)* @gzip_bidder_init, i32 (%struct.archive_read_filter*)** %init, align 8, !dbg !402
  %9 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !403
  %options = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %9, i32 0, i32 4, !dbg !404
  store i32 (%struct.archive_read_filter_bidder*, i8*, i8*)* null, i32 (%struct.archive_read_filter_bidder*, i8*, i8*)** %options, align 8, !dbg !405
  %10 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !406
  %free = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %10, i32 0, i32 5, !dbg !407
  store i32 (%struct.archive_read_filter_bidder*)* null, i32 (%struct.archive_read_filter_bidder*)** %free, align 8, !dbg !408
  store i32 0, i32* %retval, align 4, !dbg !409
  br label %return, !dbg !409

return:                                           ; preds = %if.end4, %if.then3, %if.then
  %11 = load i32, i32* %retval, align 4, !dbg !410
  ret i32 %11, !dbg !410
}

declare i32 @__archive_check_magic(%struct.archive*, i32, i32, i8*) #2

declare i32 @__archive_read_get_bidder(%struct.archive_read*, %struct.archive_read_filter_bidder**) #2

; Function Attrs: nounwind uwtable
define internal i32 @gzip_bidder_bid(%struct.archive_read_filter_bidder* %self, %struct.archive_read_filter* %filter) #0 !dbg !344 {
entry:
  %retval = alloca i32, align 4
  %self.addr = alloca %struct.archive_read_filter_bidder*, align 8
  %filter.addr = alloca %struct.archive_read_filter*, align 8
  %bits_checked = alloca i32, align 4
  store %struct.archive_read_filter_bidder* %self, %struct.archive_read_filter_bidder** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter_bidder** %self.addr, metadata !411, metadata !361), !dbg !412
  store %struct.archive_read_filter* %filter, %struct.archive_read_filter** %filter.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %filter.addr, metadata !413, metadata !361), !dbg !414
  call void @llvm.dbg.declare(metadata i32* %bits_checked, metadata !415, metadata !361), !dbg !416
  %0 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %self.addr, align 8, !dbg !417
  %1 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !418
  %call = call i64 @peek_at_header(%struct.archive_read_filter* %1, i32* %bits_checked), !dbg !420
  %tobool = icmp ne i64 %call, 0, !dbg !420
  br i1 %tobool, label %if.then, label %if.end, !dbg !421

if.then:                                          ; preds = %entry
  %2 = load i32, i32* %bits_checked, align 4, !dbg !422
  store i32 %2, i32* %retval, align 4, !dbg !423
  br label %return, !dbg !423

if.end:                                           ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !424
  br label %return, !dbg !424

return:                                           ; preds = %if.end, %if.then
  %3 = load i32, i32* %retval, align 4, !dbg !425
  ret i32 %3, !dbg !425
}

; Function Attrs: nounwind uwtable
define internal i32 @gzip_bidder_init(%struct.archive_read_filter* %self) #0 !dbg !349 {
entry:
  %retval = alloca i32, align 4
  %self.addr = alloca %struct.archive_read_filter*, align 8
  %state = alloca %struct.private_data*, align 8
  %out_block = alloca i8*, align 8
  store %struct.archive_read_filter* %self, %struct.archive_read_filter** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %self.addr, metadata !426, metadata !361), !dbg !427
  call void @llvm.dbg.declare(metadata %struct.private_data** %state, metadata !428, metadata !361), !dbg !429
  call void @llvm.dbg.declare(metadata i8** %out_block, metadata !430, metadata !361), !dbg !431
  %0 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !432
  %code = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %0, i32 0, i32 12, !dbg !433
  store i32 1, i32* %code, align 8, !dbg !434
  %1 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !435
  %name = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %1, i32 0, i32 11, !dbg !436
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.1, i32 0, i32 0), i8** %name, align 8, !dbg !437
  %call = call noalias i8* @calloc(i64 160, i64 1) #5, !dbg !438
  %2 = bitcast i8* %call to %struct.private_data*, !dbg !439
  store %struct.private_data* %2, %struct.private_data** %state, align 8, !dbg !440
  %call1 = call noalias i8* @malloc(i64 65536) #5, !dbg !441
  store i8* %call1, i8** %out_block, align 8, !dbg !442
  %3 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !443
  %cmp = icmp eq %struct.private_data* %3, null, !dbg !445
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !446

lor.lhs.false:                                    ; preds = %entry
  %4 = load i8*, i8** %out_block, align 8, !dbg !447
  %cmp2 = icmp eq i8* %4, null, !dbg !449
  br i1 %cmp2, label %if.then, label %if.end, !dbg !450

if.then:                                          ; preds = %lor.lhs.false, %entry
  %5 = load i8*, i8** %out_block, align 8, !dbg !451
  call void @free(i8* %5) #5, !dbg !453
  %6 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !454
  %7 = bitcast %struct.private_data* %6 to i8*, !dbg !454
  call void @free(i8* %7) #5, !dbg !455
  %8 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !456
  %archive = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %8, i32 0, i32 3, !dbg !457
  %9 = load %struct.archive_read*, %struct.archive_read** %archive, align 8, !dbg !457
  %archive3 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %9, i32 0, i32 0, !dbg !458
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive3, i32 12, i8* getelementptr inbounds ([43 x i8], [43 x i8]* @.str.3, i32 0, i32 0)), !dbg !459
  store i32 -30, i32* %retval, align 4, !dbg !460
  br label %return, !dbg !460

if.end:                                           ; preds = %lor.lhs.false
  %10 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !461
  %11 = bitcast %struct.private_data* %10 to i8*, !dbg !461
  %12 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !462
  %data = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %12, i32 0, i32 10, !dbg !463
  store i8* %11, i8** %data, align 8, !dbg !464
  %13 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !465
  %out_block_size = getelementptr inbounds %struct.private_data, %struct.private_data* %13, i32 0, i32 3, !dbg !466
  store i64 65536, i64* %out_block_size, align 8, !dbg !467
  %14 = load i8*, i8** %out_block, align 8, !dbg !468
  %15 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !469
  %out_block4 = getelementptr inbounds %struct.private_data, %struct.private_data* %15, i32 0, i32 2, !dbg !470
  store i8* %14, i8** %out_block4, align 8, !dbg !471
  %16 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !472
  %read = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %16, i32 0, i32 5, !dbg !473
  store i64 (%struct.archive_read_filter*, i8**)* @gzip_filter_read, i64 (%struct.archive_read_filter*, i8**)** %read, align 8, !dbg !474
  %17 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !475
  %skip = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %17, i32 0, i32 6, !dbg !476
  store i64 (%struct.archive_read_filter*, i64)* null, i64 (%struct.archive_read_filter*, i64)** %skip, align 8, !dbg !477
  %18 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !478
  %close = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %18, i32 0, i32 8, !dbg !479
  store i32 (%struct.archive_read_filter*)* @gzip_filter_close, i32 (%struct.archive_read_filter*)** %close, align 8, !dbg !480
  %19 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !481
  %in_stream = getelementptr inbounds %struct.private_data, %struct.private_data* %19, i32 0, i32 1, !dbg !482
  store i8 0, i8* %in_stream, align 8, !dbg !483
  store i32 0, i32* %retval, align 4, !dbg !484
  br label %return, !dbg !484

return:                                           ; preds = %if.end, %if.then
  %20 = load i32, i32* %retval, align 4, !dbg !485
  ret i32 %20, !dbg !485
}

; Function Attrs: nounwind uwtable
define internal i64 @peek_at_header(%struct.archive_read_filter* %filter, i32* %pbits) #0 !dbg !345 {
entry:
  %retval = alloca i64, align 8
  %filter.addr = alloca %struct.archive_read_filter*, align 8
  %pbits.addr = alloca i32*, align 8
  %p = alloca i8*, align 8
  %avail = alloca i64, align 8
  %len = alloca i64, align 8
  %bits = alloca i32, align 4
  %header_flags = alloca i32, align 4
  store %struct.archive_read_filter* %filter, %struct.archive_read_filter** %filter.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %filter.addr, metadata !486, metadata !361), !dbg !487
  store i32* %pbits, i32** %pbits.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %pbits.addr, metadata !488, metadata !361), !dbg !489
  call void @llvm.dbg.declare(metadata i8** %p, metadata !490, metadata !361), !dbg !493
  call void @llvm.dbg.declare(metadata i64* %avail, metadata !494, metadata !361), !dbg !495
  call void @llvm.dbg.declare(metadata i64* %len, metadata !496, metadata !361), !dbg !497
  call void @llvm.dbg.declare(metadata i32* %bits, metadata !498, metadata !361), !dbg !499
  store i32 0, i32* %bits, align 4, !dbg !499
  call void @llvm.dbg.declare(metadata i32* %header_flags, metadata !500, metadata !361), !dbg !501
  store i64 10, i64* %len, align 8, !dbg !502
  %0 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !503
  %1 = load i64, i64* %len, align 8, !dbg !504
  %call = call i8* @__archive_read_filter_ahead(%struct.archive_read_filter* %0, i64 %1, i64* %avail), !dbg !505
  store i8* %call, i8** %p, align 8, !dbg !506
  %2 = load i8*, i8** %p, align 8, !dbg !507
  %cmp = icmp eq i8* %2, null, !dbg !509
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !510

lor.lhs.false:                                    ; preds = %entry
  %3 = load i64, i64* %avail, align 8, !dbg !511
  %cmp1 = icmp eq i64 %3, 0, !dbg !513
  br i1 %cmp1, label %if.then, label %if.end, !dbg !514

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i64 0, i64* %retval, align 8, !dbg !515
  br label %return, !dbg !515

if.end:                                           ; preds = %lor.lhs.false
  %4 = load i8*, i8** %p, align 8, !dbg !516
  %call2 = call i32 @memcmp(i8* %4, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.2, i32 0, i32 0), i64 3) #6, !dbg !518
  %cmp3 = icmp ne i32 %call2, 0, !dbg !519
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !520

if.then4:                                         ; preds = %if.end
  store i64 0, i64* %retval, align 8, !dbg !521
  br label %return, !dbg !521

if.end5:                                          ; preds = %if.end
  %5 = load i32, i32* %bits, align 4, !dbg !522
  %add = add nsw i32 %5, 24, !dbg !522
  store i32 %add, i32* %bits, align 4, !dbg !522
  %6 = load i8*, i8** %p, align 8, !dbg !523
  %arrayidx = getelementptr inbounds i8, i8* %6, i64 3, !dbg !523
  %7 = load i8, i8* %arrayidx, align 1, !dbg !523
  %conv = zext i8 %7 to i32, !dbg !523
  %and = and i32 %conv, 224, !dbg !525
  %cmp6 = icmp ne i32 %and, 0, !dbg !526
  br i1 %cmp6, label %if.then8, label %if.end9, !dbg !527

if.then8:                                         ; preds = %if.end5
  store i64 0, i64* %retval, align 8, !dbg !528
  br label %return, !dbg !528

if.end9:                                          ; preds = %if.end5
  %8 = load i32, i32* %bits, align 4, !dbg !529
  %add10 = add nsw i32 %8, 3, !dbg !529
  store i32 %add10, i32* %bits, align 4, !dbg !529
  %9 = load i8*, i8** %p, align 8, !dbg !530
  %arrayidx11 = getelementptr inbounds i8, i8* %9, i64 3, !dbg !530
  %10 = load i8, i8* %arrayidx11, align 1, !dbg !530
  %conv12 = zext i8 %10 to i32, !dbg !530
  store i32 %conv12, i32* %header_flags, align 4, !dbg !531
  %11 = load i32, i32* %header_flags, align 4, !dbg !532
  %and13 = and i32 %11, 4, !dbg !534
  %tobool = icmp ne i32 %and13, 0, !dbg !534
  br i1 %tobool, label %if.then14, label %if.end29, !dbg !535

if.then14:                                        ; preds = %if.end9
  %12 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !536
  %13 = load i64, i64* %len, align 8, !dbg !538
  %add15 = add nsw i64 %13, 2, !dbg !539
  %call16 = call i8* @__archive_read_filter_ahead(%struct.archive_read_filter* %12, i64 %add15, i64* %avail), !dbg !540
  store i8* %call16, i8** %p, align 8, !dbg !541
  %14 = load i8*, i8** %p, align 8, !dbg !542
  %cmp17 = icmp eq i8* %14, null, !dbg !544
  br i1 %cmp17, label %if.then19, label %if.end20, !dbg !545

if.then19:                                        ; preds = %if.then14
  store i64 0, i64* %retval, align 8, !dbg !546
  br label %return, !dbg !546

if.end20:                                         ; preds = %if.then14
  %15 = load i64, i64* %len, align 8, !dbg !547
  %add21 = add nsw i64 %15, 1, !dbg !548
  %16 = load i8*, i8** %p, align 8, !dbg !549
  %arrayidx22 = getelementptr inbounds i8, i8* %16, i64 %add21, !dbg !549
  %17 = load i8, i8* %arrayidx22, align 1, !dbg !549
  %conv23 = zext i8 %17 to i32, !dbg !550
  %shl = shl i32 %conv23, 8, !dbg !551
  %18 = load i64, i64* %len, align 8, !dbg !552
  %19 = load i8*, i8** %p, align 8, !dbg !553
  %arrayidx24 = getelementptr inbounds i8, i8* %19, i64 %18, !dbg !553
  %20 = load i8, i8* %arrayidx24, align 1, !dbg !553
  %conv25 = zext i8 %20 to i32, !dbg !554
  %or = or i32 %shl, %conv25, !dbg !555
  %conv26 = sext i32 %or to i64, !dbg !556
  %21 = load i64, i64* %len, align 8, !dbg !557
  %add27 = add nsw i64 %21, %conv26, !dbg !557
  store i64 %add27, i64* %len, align 8, !dbg !557
  %22 = load i64, i64* %len, align 8, !dbg !558
  %add28 = add nsw i64 %22, 2, !dbg !558
  store i64 %add28, i64* %len, align 8, !dbg !558
  br label %if.end29, !dbg !559

if.end29:                                         ; preds = %if.end20, %if.end9
  %23 = load i32, i32* %header_flags, align 4, !dbg !560
  %and30 = and i32 %23, 8, !dbg !562
  %tobool31 = icmp ne i32 %and30, 0, !dbg !562
  br i1 %tobool31, label %if.then32, label %if.end46, !dbg !563

if.then32:                                        ; preds = %if.end29
  br label %do.body, !dbg !564

do.body:                                          ; preds = %do.cond, %if.then32
  %24 = load i64, i64* %len, align 8, !dbg !566
  %inc = add nsw i64 %24, 1, !dbg !566
  store i64 %inc, i64* %len, align 8, !dbg !566
  %25 = load i64, i64* %avail, align 8, !dbg !568
  %26 = load i64, i64* %len, align 8, !dbg !570
  %cmp33 = icmp slt i64 %25, %26, !dbg !571
  br i1 %cmp33, label %if.then35, label %if.end37, !dbg !572

if.then35:                                        ; preds = %do.body
  %27 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !573
  %28 = load i64, i64* %len, align 8, !dbg !574
  %call36 = call i8* @__archive_read_filter_ahead(%struct.archive_read_filter* %27, i64 %28, i64* %avail), !dbg !575
  store i8* %call36, i8** %p, align 8, !dbg !576
  br label %if.end37, !dbg !577

if.end37:                                         ; preds = %if.then35, %do.body
  %29 = load i8*, i8** %p, align 8, !dbg !578
  %cmp38 = icmp eq i8* %29, null, !dbg !580
  br i1 %cmp38, label %if.then40, label %if.end41, !dbg !581

if.then40:                                        ; preds = %if.end37
  store i64 0, i64* %retval, align 8, !dbg !582
  br label %return, !dbg !582

if.end41:                                         ; preds = %if.end37
  br label %do.cond, !dbg !583

do.cond:                                          ; preds = %if.end41
  %30 = load i64, i64* %len, align 8, !dbg !584
  %sub = sub nsw i64 %30, 1, !dbg !586
  %31 = load i8*, i8** %p, align 8, !dbg !587
  %arrayidx42 = getelementptr inbounds i8, i8* %31, i64 %sub, !dbg !587
  %32 = load i8, i8* %arrayidx42, align 1, !dbg !587
  %conv43 = zext i8 %32 to i32, !dbg !587
  %cmp44 = icmp ne i32 %conv43, 0, !dbg !588
  br i1 %cmp44, label %do.body, label %do.end, !dbg !589

do.end:                                           ; preds = %do.cond
  br label %if.end46, !dbg !590

if.end46:                                         ; preds = %do.end, %if.end29
  %33 = load i32, i32* %header_flags, align 4, !dbg !591
  %and47 = and i32 %33, 16, !dbg !593
  %tobool48 = icmp ne i32 %and47, 0, !dbg !593
  br i1 %tobool48, label %if.then49, label %if.end68, !dbg !594

if.then49:                                        ; preds = %if.end46
  br label %do.body50, !dbg !595

do.body50:                                        ; preds = %do.cond61, %if.then49
  %34 = load i64, i64* %len, align 8, !dbg !597
  %inc51 = add nsw i64 %34, 1, !dbg !597
  store i64 %inc51, i64* %len, align 8, !dbg !597
  %35 = load i64, i64* %avail, align 8, !dbg !599
  %36 = load i64, i64* %len, align 8, !dbg !601
  %cmp52 = icmp slt i64 %35, %36, !dbg !602
  br i1 %cmp52, label %if.then54, label %if.end56, !dbg !603

if.then54:                                        ; preds = %do.body50
  %37 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !604
  %38 = load i64, i64* %len, align 8, !dbg !605
  %call55 = call i8* @__archive_read_filter_ahead(%struct.archive_read_filter* %37, i64 %38, i64* %avail), !dbg !606
  store i8* %call55, i8** %p, align 8, !dbg !607
  br label %if.end56, !dbg !608

if.end56:                                         ; preds = %if.then54, %do.body50
  %39 = load i8*, i8** %p, align 8, !dbg !609
  %cmp57 = icmp eq i8* %39, null, !dbg !611
  br i1 %cmp57, label %if.then59, label %if.end60, !dbg !612

if.then59:                                        ; preds = %if.end56
  store i64 0, i64* %retval, align 8, !dbg !613
  br label %return, !dbg !613

if.end60:                                         ; preds = %if.end56
  br label %do.cond61, !dbg !614

do.cond61:                                        ; preds = %if.end60
  %40 = load i64, i64* %len, align 8, !dbg !615
  %sub62 = sub nsw i64 %40, 1, !dbg !617
  %41 = load i8*, i8** %p, align 8, !dbg !618
  %arrayidx63 = getelementptr inbounds i8, i8* %41, i64 %sub62, !dbg !618
  %42 = load i8, i8* %arrayidx63, align 1, !dbg !618
  %conv64 = zext i8 %42 to i32, !dbg !618
  %cmp65 = icmp ne i32 %conv64, 0, !dbg !619
  br i1 %cmp65, label %do.body50, label %do.end67, !dbg !620

do.end67:                                         ; preds = %do.cond61
  br label %if.end68, !dbg !621

if.end68:                                         ; preds = %do.end67, %if.end46
  %43 = load i32, i32* %header_flags, align 4, !dbg !622
  %and69 = and i32 %43, 2, !dbg !624
  %tobool70 = icmp ne i32 %and69, 0, !dbg !624
  br i1 %tobool70, label %if.then71, label %if.end79, !dbg !625

if.then71:                                        ; preds = %if.end68
  %44 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !626
  %45 = load i64, i64* %len, align 8, !dbg !628
  %add72 = add nsw i64 %45, 2, !dbg !629
  %call73 = call i8* @__archive_read_filter_ahead(%struct.archive_read_filter* %44, i64 %add72, i64* %avail), !dbg !630
  store i8* %call73, i8** %p, align 8, !dbg !631
  %46 = load i8*, i8** %p, align 8, !dbg !632
  %cmp74 = icmp eq i8* %46, null, !dbg !634
  br i1 %cmp74, label %if.then76, label %if.end77, !dbg !635

if.then76:                                        ; preds = %if.then71
  store i64 0, i64* %retval, align 8, !dbg !636
  br label %return, !dbg !636

if.end77:                                         ; preds = %if.then71
  %47 = load i64, i64* %len, align 8, !dbg !637
  %add78 = add nsw i64 %47, 2, !dbg !637
  store i64 %add78, i64* %len, align 8, !dbg !637
  br label %if.end79, !dbg !638

if.end79:                                         ; preds = %if.end77, %if.end68
  %48 = load i32*, i32** %pbits.addr, align 8, !dbg !639
  %cmp80 = icmp ne i32* %48, null, !dbg !641
  br i1 %cmp80, label %if.then82, label %if.end83, !dbg !642

if.then82:                                        ; preds = %if.end79
  %49 = load i32, i32* %bits, align 4, !dbg !643
  %50 = load i32*, i32** %pbits.addr, align 8, !dbg !644
  store i32 %49, i32* %50, align 4, !dbg !645
  br label %if.end83, !dbg !646

if.end83:                                         ; preds = %if.then82, %if.end79
  %51 = load i64, i64* %len, align 8, !dbg !647
  store i64 %51, i64* %retval, align 8, !dbg !648
  br label %return, !dbg !648

return:                                           ; preds = %if.end83, %if.then76, %if.then59, %if.then40, %if.then19, %if.then8, %if.then4, %if.then
  %52 = load i64, i64* %retval, align 8, !dbg !649
  ret i64 %52, !dbg !649
}

declare i8* @__archive_read_filter_ahead(%struct.archive_read_filter*, i64, i64*) #2

; Function Attrs: nounwind readonly
declare i32 @memcmp(i8*, i8*, i64) #3

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #4

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #4

; Function Attrs: nounwind
declare void @free(i8*) #4

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

; Function Attrs: nounwind uwtable
define internal i64 @gzip_filter_read(%struct.archive_read_filter* %self, i8** %p) #0 !dbg !350 {
entry:
  %retval = alloca i64, align 8
  %self.addr = alloca %struct.archive_read_filter*, align 8
  %p.addr = alloca i8**, align 8
  %state = alloca %struct.private_data*, align 8
  %decompressed = alloca i64, align 8
  %avail_in = alloca i64, align 8
  %ret = alloca i32, align 4
  store %struct.archive_read_filter* %self, %struct.archive_read_filter** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %self.addr, metadata !650, metadata !361), !dbg !651
  store i8** %p, i8*** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %p.addr, metadata !652, metadata !361), !dbg !653
  call void @llvm.dbg.declare(metadata %struct.private_data** %state, metadata !654, metadata !361), !dbg !655
  call void @llvm.dbg.declare(metadata i64* %decompressed, metadata !656, metadata !361), !dbg !657
  call void @llvm.dbg.declare(metadata i64* %avail_in, metadata !658, metadata !361), !dbg !659
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !660, metadata !361), !dbg !661
  %0 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !662
  %data = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %0, i32 0, i32 10, !dbg !663
  %1 = load i8*, i8** %data, align 8, !dbg !663
  %2 = bitcast i8* %1 to %struct.private_data*, !dbg !664
  store %struct.private_data* %2, %struct.private_data** %state, align 8, !dbg !665
  %3 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !666
  %out_block = getelementptr inbounds %struct.private_data, %struct.private_data* %3, i32 0, i32 2, !dbg !667
  %4 = load i8*, i8** %out_block, align 8, !dbg !667
  %5 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !668
  %stream = getelementptr inbounds %struct.private_data, %struct.private_data* %5, i32 0, i32 0, !dbg !669
  %next_out = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream, i32 0, i32 3, !dbg !670
  store i8* %4, i8** %next_out, align 8, !dbg !671
  %6 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !672
  %out_block_size = getelementptr inbounds %struct.private_data, %struct.private_data* %6, i32 0, i32 3, !dbg !673
  %7 = load i64, i64* %out_block_size, align 8, !dbg !673
  %conv = trunc i64 %7 to i32, !dbg !674
  %8 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !675
  %stream1 = getelementptr inbounds %struct.private_data, %struct.private_data* %8, i32 0, i32 0, !dbg !676
  %avail_out = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream1, i32 0, i32 4, !dbg !677
  store i32 %conv, i32* %avail_out, align 8, !dbg !678
  br label %while.cond, !dbg !679

while.cond:                                       ; preds = %sw.epilog, %entry
  %9 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !680
  %stream2 = getelementptr inbounds %struct.private_data, %struct.private_data* %9, i32 0, i32 0, !dbg !682
  %avail_out3 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream2, i32 0, i32 4, !dbg !683
  %10 = load i32, i32* %avail_out3, align 8, !dbg !683
  %cmp = icmp ugt i32 %10, 0, !dbg !684
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !685

land.rhs:                                         ; preds = %while.cond
  %11 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !686
  %eof = getelementptr inbounds %struct.private_data, %struct.private_data* %11, i32 0, i32 6, !dbg !688
  %12 = load i8, i8* %eof, align 8, !dbg !688
  %tobool = icmp ne i8 %12, 0, !dbg !689
  %lnot = xor i1 %tobool, true, !dbg !689
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond
  %13 = phi i1 [ false, %while.cond ], [ %lnot, %land.rhs ]
  br i1 %13, label %while.body, label %while.end, !dbg !690

while.body:                                       ; preds = %land.end
  %14 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !692
  %in_stream = getelementptr inbounds %struct.private_data, %struct.private_data* %14, i32 0, i32 1, !dbg !695
  %15 = load i8, i8* %in_stream, align 8, !dbg !695
  %tobool5 = icmp ne i8 %15, 0, !dbg !692
  br i1 %tobool5, label %if.end15, label %if.then, !dbg !696

if.then:                                          ; preds = %while.body
  %16 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !697
  %call = call i32 @consume_header(%struct.archive_read_filter* %16), !dbg !699
  store i32 %call, i32* %ret, align 4, !dbg !700
  %17 = load i32, i32* %ret, align 4, !dbg !701
  %cmp6 = icmp eq i32 %17, 1, !dbg !703
  br i1 %cmp6, label %if.then8, label %if.end, !dbg !704

if.then8:                                         ; preds = %if.then
  %18 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !705
  %eof9 = getelementptr inbounds %struct.private_data, %struct.private_data* %18, i32 0, i32 6, !dbg !707
  store i8 1, i8* %eof9, align 8, !dbg !708
  br label %while.end, !dbg !709

if.end:                                           ; preds = %if.then
  %19 = load i32, i32* %ret, align 4, !dbg !710
  %cmp10 = icmp slt i32 %19, 0, !dbg !712
  br i1 %cmp10, label %if.then12, label %if.end14, !dbg !713

if.then12:                                        ; preds = %if.end
  %20 = load i32, i32* %ret, align 4, !dbg !714
  %conv13 = sext i32 %20 to i64, !dbg !715
  store i64 %conv13, i64* %retval, align 8, !dbg !716
  br label %return, !dbg !716

if.end14:                                         ; preds = %if.end
  br label %if.end15, !dbg !717

if.end15:                                         ; preds = %if.end14, %while.body
  %21 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !718
  %upstream = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %21, i32 0, i32 2, !dbg !719
  %22 = load %struct.archive_read_filter*, %struct.archive_read_filter** %upstream, align 8, !dbg !719
  %call16 = call i8* @__archive_read_filter_ahead(%struct.archive_read_filter* %22, i64 1, i64* %avail_in), !dbg !720
  %23 = ptrtoint i8* %call16 to i64, !dbg !721
  %24 = inttoptr i64 %23 to i8*, !dbg !722
  %25 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !723
  %stream17 = getelementptr inbounds %struct.private_data, %struct.private_data* %25, i32 0, i32 0, !dbg !724
  %next_in = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream17, i32 0, i32 0, !dbg !725
  store i8* %24, i8** %next_in, align 8, !dbg !726
  %26 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !727
  %stream18 = getelementptr inbounds %struct.private_data, %struct.private_data* %26, i32 0, i32 0, !dbg !729
  %next_in19 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream18, i32 0, i32 0, !dbg !730
  %27 = load i8*, i8** %next_in19, align 8, !dbg !730
  %cmp20 = icmp eq i8* %27, null, !dbg !731
  br i1 %cmp20, label %if.then22, label %if.end24, !dbg !732

if.then22:                                        ; preds = %if.end15
  %28 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !733
  %archive = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %28, i32 0, i32 3, !dbg !735
  %29 = load %struct.archive_read*, %struct.archive_read** %archive, align 8, !dbg !735
  %archive23 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %29, i32 0, i32 0, !dbg !736
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive23, i32 -1, i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.4, i32 0, i32 0)), !dbg !737
  store i64 -30, i64* %retval, align 8, !dbg !738
  br label %return, !dbg !738

if.end24:                                         ; preds = %if.end15
  %30 = load i64, i64* %avail_in, align 8, !dbg !739
  %conv25 = trunc i64 %30 to i32, !dbg !740
  %31 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !741
  %stream26 = getelementptr inbounds %struct.private_data, %struct.private_data* %31, i32 0, i32 0, !dbg !742
  %avail_in27 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream26, i32 0, i32 1, !dbg !743
  store i32 %conv25, i32* %avail_in27, align 8, !dbg !744
  %32 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !745
  %stream28 = getelementptr inbounds %struct.private_data, %struct.private_data* %32, i32 0, i32 0, !dbg !746
  %call29 = call i32 @cm_zlib_inflate(%struct.z_stream_s* %stream28, i32 0), !dbg !747
  store i32 %call29, i32* %ret, align 4, !dbg !748
  %33 = load i32, i32* %ret, align 4, !dbg !749
  switch i32 %33, label %sw.default [
    i32 0, label %sw.bb
    i32 1, label %sw.bb35
  ], !dbg !750

sw.bb:                                            ; preds = %if.end24
  %34 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !751
  %upstream30 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %34, i32 0, i32 2, !dbg !753
  %35 = load %struct.archive_read_filter*, %struct.archive_read_filter** %upstream30, align 8, !dbg !753
  %36 = load i64, i64* %avail_in, align 8, !dbg !754
  %37 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !755
  %stream31 = getelementptr inbounds %struct.private_data, %struct.private_data* %37, i32 0, i32 0, !dbg !756
  %avail_in32 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream31, i32 0, i32 1, !dbg !757
  %38 = load i32, i32* %avail_in32, align 8, !dbg !757
  %conv33 = zext i32 %38 to i64, !dbg !755
  %sub = sub nsw i64 %36, %conv33, !dbg !758
  %call34 = call i64 @__archive_read_filter_consume(%struct.archive_read_filter* %35, i64 %sub), !dbg !759
  br label %sw.epilog, !dbg !760

sw.bb35:                                          ; preds = %if.end24
  %39 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !761
  %upstream36 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %39, i32 0, i32 2, !dbg !762
  %40 = load %struct.archive_read_filter*, %struct.archive_read_filter** %upstream36, align 8, !dbg !762
  %41 = load i64, i64* %avail_in, align 8, !dbg !763
  %42 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !764
  %stream37 = getelementptr inbounds %struct.private_data, %struct.private_data* %42, i32 0, i32 0, !dbg !765
  %avail_in38 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream37, i32 0, i32 1, !dbg !766
  %43 = load i32, i32* %avail_in38, align 8, !dbg !766
  %conv39 = zext i32 %43 to i64, !dbg !764
  %sub40 = sub nsw i64 %41, %conv39, !dbg !767
  %call41 = call i64 @__archive_read_filter_consume(%struct.archive_read_filter* %40, i64 %sub40), !dbg !768
  %44 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !769
  %call42 = call i32 @consume_trailer(%struct.archive_read_filter* %44), !dbg !770
  store i32 %call42, i32* %ret, align 4, !dbg !771
  %45 = load i32, i32* %ret, align 4, !dbg !772
  %cmp43 = icmp slt i32 %45, 0, !dbg !774
  br i1 %cmp43, label %if.then45, label %if.end47, !dbg !775

if.then45:                                        ; preds = %sw.bb35
  %46 = load i32, i32* %ret, align 4, !dbg !776
  %conv46 = sext i32 %46 to i64, !dbg !777
  store i64 %conv46, i64* %retval, align 8, !dbg !778
  br label %return, !dbg !778

if.end47:                                         ; preds = %sw.bb35
  br label %sw.epilog, !dbg !779

sw.default:                                       ; preds = %if.end24
  %47 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !780
  %archive48 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %47, i32 0, i32 3, !dbg !781
  %48 = load %struct.archive_read*, %struct.archive_read** %archive48, align 8, !dbg !781
  %archive49 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %48, i32 0, i32 0, !dbg !782
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive49, i32 -1, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.5, i32 0, i32 0)), !dbg !783
  store i64 -30, i64* %retval, align 8, !dbg !784
  br label %return, !dbg !784

sw.epilog:                                        ; preds = %if.end47, %sw.bb
  br label %while.cond, !dbg !785

while.end:                                        ; preds = %if.then8, %land.end
  %49 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !787
  %stream50 = getelementptr inbounds %struct.private_data, %struct.private_data* %49, i32 0, i32 0, !dbg !788
  %next_out51 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream50, i32 0, i32 3, !dbg !789
  %50 = load i8*, i8** %next_out51, align 8, !dbg !789
  %51 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !790
  %out_block52 = getelementptr inbounds %struct.private_data, %struct.private_data* %51, i32 0, i32 2, !dbg !791
  %52 = load i8*, i8** %out_block52, align 8, !dbg !791
  %sub.ptr.lhs.cast = ptrtoint i8* %50 to i64, !dbg !792
  %sub.ptr.rhs.cast = ptrtoint i8* %52 to i64, !dbg !792
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !792
  store i64 %sub.ptr.sub, i64* %decompressed, align 8, !dbg !793
  %53 = load i64, i64* %decompressed, align 8, !dbg !794
  %54 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !795
  %total_out = getelementptr inbounds %struct.private_data, %struct.private_data* %54, i32 0, i32 4, !dbg !796
  %55 = load i64, i64* %total_out, align 8, !dbg !797
  %add = add i64 %55, %53, !dbg !797
  store i64 %add, i64* %total_out, align 8, !dbg !797
  %56 = load i64, i64* %decompressed, align 8, !dbg !798
  %cmp53 = icmp eq i64 %56, 0, !dbg !800
  br i1 %cmp53, label %if.then55, label %if.else, !dbg !801

if.then55:                                        ; preds = %while.end
  %57 = load i8**, i8*** %p.addr, align 8, !dbg !802
  store i8* null, i8** %57, align 8, !dbg !803
  br label %if.end57, !dbg !804

if.else:                                          ; preds = %while.end
  %58 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !805
  %out_block56 = getelementptr inbounds %struct.private_data, %struct.private_data* %58, i32 0, i32 2, !dbg !806
  %59 = load i8*, i8** %out_block56, align 8, !dbg !806
  %60 = load i8**, i8*** %p.addr, align 8, !dbg !807
  store i8* %59, i8** %60, align 8, !dbg !808
  br label %if.end57

if.end57:                                         ; preds = %if.else, %if.then55
  %61 = load i64, i64* %decompressed, align 8, !dbg !809
  store i64 %61, i64* %retval, align 8, !dbg !810
  br label %return, !dbg !810

return:                                           ; preds = %if.end57, %sw.default, %if.then45, %if.then22, %if.then12
  %62 = load i64, i64* %retval, align 8, !dbg !811
  ret i64 %62, !dbg !811
}

; Function Attrs: nounwind uwtable
define internal i32 @gzip_filter_close(%struct.archive_read_filter* %self) #0 !dbg !353 {
entry:
  %self.addr = alloca %struct.archive_read_filter*, align 8
  %state = alloca %struct.private_data*, align 8
  %ret = alloca i32, align 4
  store %struct.archive_read_filter* %self, %struct.archive_read_filter** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %self.addr, metadata !812, metadata !361), !dbg !813
  call void @llvm.dbg.declare(metadata %struct.private_data** %state, metadata !814, metadata !361), !dbg !815
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !816, metadata !361), !dbg !817
  %0 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !818
  %data = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %0, i32 0, i32 10, !dbg !819
  %1 = load i8*, i8** %data, align 8, !dbg !819
  %2 = bitcast i8* %1 to %struct.private_data*, !dbg !820
  store %struct.private_data* %2, %struct.private_data** %state, align 8, !dbg !821
  store i32 0, i32* %ret, align 4, !dbg !822
  %3 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !823
  %in_stream = getelementptr inbounds %struct.private_data, %struct.private_data* %3, i32 0, i32 1, !dbg !825
  %4 = load i8, i8* %in_stream, align 8, !dbg !825
  %tobool = icmp ne i8 %4, 0, !dbg !823
  br i1 %tobool, label %if.then, label %if.end, !dbg !826

if.then:                                          ; preds = %entry
  %5 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !827
  %stream = getelementptr inbounds %struct.private_data, %struct.private_data* %5, i32 0, i32 0, !dbg !829
  %call = call i32 @cm_zlib_inflateEnd(%struct.z_stream_s* %stream), !dbg !830
  switch i32 %call, label %sw.default [
    i32 0, label %sw.bb
  ], !dbg !831

sw.bb:                                            ; preds = %if.then
  br label %sw.epilog, !dbg !832

sw.default:                                       ; preds = %if.then
  %6 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !834
  %archive = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %6, i32 0, i32 3, !dbg !835
  %7 = load %struct.archive_read*, %struct.archive_read** %archive, align 8, !dbg !835
  %archive1 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %7, i32 0, i32 0, !dbg !836
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive1, i32 -1, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.12, i32 0, i32 0)), !dbg !837
  store i32 -30, i32* %ret, align 4, !dbg !838
  br label %sw.epilog, !dbg !839

sw.epilog:                                        ; preds = %sw.default, %sw.bb
  br label %if.end, !dbg !840

if.end:                                           ; preds = %sw.epilog, %entry
  %8 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !841
  %out_block = getelementptr inbounds %struct.private_data, %struct.private_data* %8, i32 0, i32 2, !dbg !842
  %9 = load i8*, i8** %out_block, align 8, !dbg !842
  call void @free(i8* %9) #5, !dbg !843
  %10 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !844
  %11 = bitcast %struct.private_data* %10 to i8*, !dbg !844
  call void @free(i8* %11) #5, !dbg !845
  %12 = load i32, i32* %ret, align 4, !dbg !846
  ret i32 %12, !dbg !847
}

; Function Attrs: nounwind uwtable
define internal i32 @consume_header(%struct.archive_read_filter* %self) #0 !dbg !351 {
entry:
  %retval = alloca i32, align 4
  %self.addr = alloca %struct.archive_read_filter*, align 8
  %state = alloca %struct.private_data*, align 8
  %avail = alloca i64, align 8
  %len = alloca i64, align 8
  %ret = alloca i32, align 4
  store %struct.archive_read_filter* %self, %struct.archive_read_filter** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %self.addr, metadata !848, metadata !361), !dbg !849
  call void @llvm.dbg.declare(metadata %struct.private_data** %state, metadata !850, metadata !361), !dbg !851
  call void @llvm.dbg.declare(metadata i64* %avail, metadata !852, metadata !361), !dbg !853
  call void @llvm.dbg.declare(metadata i64* %len, metadata !854, metadata !361), !dbg !855
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !856, metadata !361), !dbg !857
  %0 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !858
  %data = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %0, i32 0, i32 10, !dbg !859
  %1 = load i8*, i8** %data, align 8, !dbg !859
  %2 = bitcast i8* %1 to %struct.private_data*, !dbg !860
  store %struct.private_data* %2, %struct.private_data** %state, align 8, !dbg !861
  %3 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !862
  %upstream = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %3, i32 0, i32 2, !dbg !863
  %4 = load %struct.archive_read_filter*, %struct.archive_read_filter** %upstream, align 8, !dbg !863
  %call = call i64 @peek_at_header(%struct.archive_read_filter* %4, i32* null), !dbg !864
  store i64 %call, i64* %len, align 8, !dbg !865
  %5 = load i64, i64* %len, align 8, !dbg !866
  %cmp = icmp eq i64 %5, 0, !dbg !868
  br i1 %cmp, label %if.then, label %if.end, !dbg !869

if.then:                                          ; preds = %entry
  store i32 1, i32* %retval, align 4, !dbg !870
  br label %return, !dbg !870

if.end:                                           ; preds = %entry
  %6 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !871
  %upstream1 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %6, i32 0, i32 2, !dbg !872
  %7 = load %struct.archive_read_filter*, %struct.archive_read_filter** %upstream1, align 8, !dbg !872
  %8 = load i64, i64* %len, align 8, !dbg !873
  %call2 = call i64 @__archive_read_filter_consume(%struct.archive_read_filter* %7, i64 %8), !dbg !874
  %call3 = call i64 @cm_zlib_crc32(i64 0, i8* null, i32 0), !dbg !875
  %9 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !876
  %crc = getelementptr inbounds %struct.private_data, %struct.private_data* %9, i32 0, i32 5, !dbg !877
  store i64 %call3, i64* %crc, align 8, !dbg !878
  %10 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !879
  %upstream4 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %10, i32 0, i32 2, !dbg !880
  %11 = load %struct.archive_read_filter*, %struct.archive_read_filter** %upstream4, align 8, !dbg !880
  %call5 = call i8* @__archive_read_filter_ahead(%struct.archive_read_filter* %11, i64 1, i64* %avail), !dbg !881
  %12 = ptrtoint i8* %call5 to i64, !dbg !882
  %13 = inttoptr i64 %12 to i8*, !dbg !883
  %14 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !884
  %stream = getelementptr inbounds %struct.private_data, %struct.private_data* %14, i32 0, i32 0, !dbg !885
  %next_in = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream, i32 0, i32 0, !dbg !886
  store i8* %13, i8** %next_in, align 8, !dbg !887
  %15 = load i64, i64* %avail, align 8, !dbg !888
  %conv = trunc i64 %15 to i32, !dbg !889
  %16 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !890
  %stream6 = getelementptr inbounds %struct.private_data, %struct.private_data* %16, i32 0, i32 0, !dbg !891
  %avail_in = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream6, i32 0, i32 1, !dbg !892
  store i32 %conv, i32* %avail_in, align 8, !dbg !893
  %17 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !894
  %stream7 = getelementptr inbounds %struct.private_data, %struct.private_data* %17, i32 0, i32 0, !dbg !894
  %call8 = call i32 @cm_zlib_inflateInit2_(%struct.z_stream_s* %stream7, i32 -15, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.6, i32 0, i32 0), i32 112), !dbg !894
  store i32 %call8, i32* %ret, align 4, !dbg !895
  %18 = load i32, i32* %ret, align 4, !dbg !896
  switch i32 %18, label %sw.default [
    i32 0, label %sw.bb
    i32 -2, label %sw.bb9
    i32 -4, label %sw.bb11
    i32 -6, label %sw.bb14
  ], !dbg !897

sw.bb:                                            ; preds = %if.end
  %19 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !898
  %in_stream = getelementptr inbounds %struct.private_data, %struct.private_data* %19, i32 0, i32 1, !dbg !900
  store i8 1, i8* %in_stream, align 8, !dbg !901
  store i32 0, i32* %retval, align 4, !dbg !902
  br label %return, !dbg !902

sw.bb9:                                           ; preds = %if.end
  %20 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !903
  %archive = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %20, i32 0, i32 3, !dbg !904
  %21 = load %struct.archive_read*, %struct.archive_read** %archive, align 8, !dbg !904
  %archive10 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %21, i32 0, i32 0, !dbg !905
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive10, i32 -1, i8* getelementptr inbounds ([73 x i8], [73 x i8]* @.str.7, i32 0, i32 0)), !dbg !906
  br label %sw.epilog, !dbg !907

sw.bb11:                                          ; preds = %if.end
  %22 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !908
  %archive12 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %22, i32 0, i32 3, !dbg !909
  %23 = load %struct.archive_read*, %struct.archive_read** %archive12, align 8, !dbg !909
  %archive13 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %23, i32 0, i32 0, !dbg !910
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive13, i32 12, i8* getelementptr inbounds ([63 x i8], [63 x i8]* @.str.8, i32 0, i32 0)), !dbg !911
  br label %sw.epilog, !dbg !912

sw.bb14:                                          ; preds = %if.end
  %24 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !913
  %archive15 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %24, i32 0, i32 3, !dbg !914
  %25 = load %struct.archive_read*, %struct.archive_read** %archive15, align 8, !dbg !914
  %archive16 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %25, i32 0, i32 0, !dbg !915
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive16, i32 -1, i8* getelementptr inbounds ([73 x i8], [73 x i8]* @.str.9, i32 0, i32 0)), !dbg !916
  br label %sw.epilog, !dbg !917

sw.default:                                       ; preds = %if.end
  %26 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !918
  %archive17 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %26, i32 0, i32 3, !dbg !919
  %27 = load %struct.archive_read*, %struct.archive_read** %archive17, align 8, !dbg !919
  %archive18 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %27, i32 0, i32 0, !dbg !920
  %28 = load i32, i32* %ret, align 4, !dbg !921
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive18, i32 -1, i8* getelementptr inbounds ([64 x i8], [64 x i8]* @.str.10, i32 0, i32 0), i32 %28), !dbg !922
  br label %sw.epilog, !dbg !923

sw.epilog:                                        ; preds = %sw.default, %sw.bb14, %sw.bb11, %sw.bb9
  store i32 -30, i32* %retval, align 4, !dbg !924
  br label %return, !dbg !924

return:                                           ; preds = %sw.epilog, %sw.bb, %if.then
  %29 = load i32, i32* %retval, align 4, !dbg !925
  ret i32 %29, !dbg !925
}

declare i32 @cm_zlib_inflate(%struct.z_stream_s*, i32) #2

declare i64 @__archive_read_filter_consume(%struct.archive_read_filter*, i64) #2

; Function Attrs: nounwind uwtable
define internal i32 @consume_trailer(%struct.archive_read_filter* %self) #0 !dbg !352 {
entry:
  %retval = alloca i32, align 4
  %self.addr = alloca %struct.archive_read_filter*, align 8
  %state = alloca %struct.private_data*, align 8
  %p = alloca i8*, align 8
  %avail = alloca i64, align 8
  store %struct.archive_read_filter* %self, %struct.archive_read_filter** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %self.addr, metadata !926, metadata !361), !dbg !927
  call void @llvm.dbg.declare(metadata %struct.private_data** %state, metadata !928, metadata !361), !dbg !929
  call void @llvm.dbg.declare(metadata i8** %p, metadata !930, metadata !361), !dbg !931
  call void @llvm.dbg.declare(metadata i64* %avail, metadata !932, metadata !361), !dbg !933
  %0 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !934
  %data = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %0, i32 0, i32 10, !dbg !935
  %1 = load i8*, i8** %data, align 8, !dbg !935
  %2 = bitcast i8* %1 to %struct.private_data*, !dbg !936
  store %struct.private_data* %2, %struct.private_data** %state, align 8, !dbg !937
  %3 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !938
  %in_stream = getelementptr inbounds %struct.private_data, %struct.private_data* %3, i32 0, i32 1, !dbg !939
  store i8 0, i8* %in_stream, align 8, !dbg !940
  %4 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !941
  %stream = getelementptr inbounds %struct.private_data, %struct.private_data* %4, i32 0, i32 0, !dbg !942
  %call = call i32 @cm_zlib_inflateEnd(%struct.z_stream_s* %stream), !dbg !943
  switch i32 %call, label %sw.default [
    i32 0, label %sw.bb
  ], !dbg !944

sw.bb:                                            ; preds = %entry
  br label %sw.epilog, !dbg !945

sw.default:                                       ; preds = %entry
  %5 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !947
  %archive = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %5, i32 0, i32 3, !dbg !948
  %6 = load %struct.archive_read*, %struct.archive_read** %archive, align 8, !dbg !948
  %archive1 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %6, i32 0, i32 0, !dbg !949
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive1, i32 -1, i8* getelementptr inbounds ([37 x i8], [37 x i8]* @.str.11, i32 0, i32 0)), !dbg !950
  store i32 -30, i32* %retval, align 4, !dbg !951
  br label %return, !dbg !951

sw.epilog:                                        ; preds = %sw.bb
  %7 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !952
  %upstream = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %7, i32 0, i32 2, !dbg !953
  %8 = load %struct.archive_read_filter*, %struct.archive_read_filter** %upstream, align 8, !dbg !953
  %call2 = call i8* @__archive_read_filter_ahead(%struct.archive_read_filter* %8, i64 8, i64* %avail), !dbg !954
  store i8* %call2, i8** %p, align 8, !dbg !955
  %9 = load i8*, i8** %p, align 8, !dbg !956
  %cmp = icmp eq i8* %9, null, !dbg !958
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !959

lor.lhs.false:                                    ; preds = %sw.epilog
  %10 = load i64, i64* %avail, align 8, !dbg !960
  %cmp3 = icmp eq i64 %10, 0, !dbg !962
  br i1 %cmp3, label %if.then, label %if.end, !dbg !963

if.then:                                          ; preds = %lor.lhs.false, %sw.epilog
  store i32 -30, i32* %retval, align 4, !dbg !964
  br label %return, !dbg !964

if.end:                                           ; preds = %lor.lhs.false
  %11 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !965
  %upstream4 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %11, i32 0, i32 2, !dbg !966
  %12 = load %struct.archive_read_filter*, %struct.archive_read_filter** %upstream4, align 8, !dbg !966
  %call5 = call i64 @__archive_read_filter_consume(%struct.archive_read_filter* %12, i64 8), !dbg !967
  store i32 0, i32* %retval, align 4, !dbg !968
  br label %return, !dbg !968

return:                                           ; preds = %if.end, %if.then, %sw.default
  %13 = load i32, i32* %retval, align 4, !dbg !969
  ret i32 %13, !dbg !969
}

declare i64 @cm_zlib_crc32(i64, i8*, i32) #2

declare i32 @cm_zlib_inflateInit2_(%struct.z_stream_s*, i32, i8*, i32) #2

declare i32 @cm_zlib_inflateEnd(%struct.z_stream_s*) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind }
attributes #6 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!357, !358}
!llvm.ident = !{!359}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !341, globals: !354)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_support_filter_gzip.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !122, !23, !291, !335, !306, !340}
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
!292 = !DICompositeType(tag: DW_TAG_structure_type, name: "private_data", file: !1, line: 52, size: 1280, align: 64, elements: !293)
!293 = !{!294, !333, !334, !336, !337, !338, !339}
!294 = !DIDerivedType(tag: DW_TAG_member, name: "stream", scope: !292, file: !1, line: 53, baseType: !295, size: 896, align: 64)
!295 = !DIDerivedType(tag: DW_TAG_typedef, name: "z_stream", file: !296, line: 101, baseType: !297)
!296 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmzlib/zlib.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!297 = !DICompositeType(tag: DW_TAG_structure_type, name: "z_stream_s", file: !296, line: 82, size: 896, align: 64, elements: !298)
!298 = !{!299, !305, !307, !309, !310, !311, !312, !313, !318, !324, !329, !330, !331, !332}
!299 = !DIDerivedType(tag: DW_TAG_member, name: "next_in", scope: !297, file: !296, line: 83, baseType: !300, size: 64, align: 64)
!300 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !301, size: 64, align: 64)
!301 = !DIDerivedType(tag: DW_TAG_typedef, name: "Bytef", file: !302, line: 276, baseType: !303)
!302 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmzlib/zconf.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!303 = !DIDerivedType(tag: DW_TAG_typedef, name: "Byte", file: !302, line: 267, baseType: !304)
!304 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!305 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in", scope: !297, file: !296, line: 84, baseType: !306, size: 32, align: 32, offset: 64)
!306 = !DIDerivedType(tag: DW_TAG_typedef, name: "uInt", file: !302, line: 269, baseType: !13)
!307 = !DIDerivedType(tag: DW_TAG_member, name: "total_in", scope: !297, file: !296, line: 85, baseType: !308, size: 64, align: 64, offset: 128)
!308 = !DIDerivedType(tag: DW_TAG_typedef, name: "uLong", file: !302, line: 270, baseType: !47)
!309 = !DIDerivedType(tag: DW_TAG_member, name: "next_out", scope: !297, file: !296, line: 87, baseType: !300, size: 64, align: 64, offset: 192)
!310 = !DIDerivedType(tag: DW_TAG_member, name: "avail_out", scope: !297, file: !296, line: 88, baseType: !306, size: 32, align: 32, offset: 256)
!311 = !DIDerivedType(tag: DW_TAG_member, name: "total_out", scope: !297, file: !296, line: 89, baseType: !308, size: 64, align: 64, offset: 320)
!312 = !DIDerivedType(tag: DW_TAG_member, name: "msg", scope: !297, file: !296, line: 91, baseType: !95, size: 64, align: 64, offset: 384)
!313 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !297, file: !296, line: 92, baseType: !314, size: 64, align: 64, offset: 448)
!314 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !315, size: 64, align: 64)
!315 = !DICompositeType(tag: DW_TAG_structure_type, name: "internal_state", file: !296, line: 1346, size: 32, align: 32, elements: !316)
!316 = !{!317}
!317 = !DIDerivedType(tag: DW_TAG_member, name: "dummy", scope: !315, file: !296, line: 1346, baseType: !23, size: 32, align: 32)
!318 = !DIDerivedType(tag: DW_TAG_member, name: "zalloc", scope: !297, file: !296, line: 94, baseType: !319, size: 64, align: 64, offset: 512)
!319 = !DIDerivedType(tag: DW_TAG_typedef, name: "alloc_func", file: !296, line: 77, baseType: !320)
!320 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !321, size: 64, align: 64)
!321 = !DISubroutineType(types: !322)
!322 = !{!323, !323, !306, !306}
!323 = !DIDerivedType(tag: DW_TAG_typedef, name: "voidpf", file: !302, line: 285, baseType: !122)
!324 = !DIDerivedType(tag: DW_TAG_member, name: "zfree", scope: !297, file: !296, line: 95, baseType: !325, size: 64, align: 64, offset: 576)
!325 = !DIDerivedType(tag: DW_TAG_typedef, name: "free_func", file: !296, line: 78, baseType: !326)
!326 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !327, size: 64, align: 64)
!327 = !DISubroutineType(types: !328)
!328 = !{null, !323, !323}
!329 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !297, file: !296, line: 96, baseType: !323, size: 64, align: 64, offset: 640)
!330 = !DIDerivedType(tag: DW_TAG_member, name: "data_type", scope: !297, file: !296, line: 98, baseType: !23, size: 32, align: 32, offset: 704)
!331 = !DIDerivedType(tag: DW_TAG_member, name: "adler", scope: !297, file: !296, line: 99, baseType: !308, size: 64, align: 64, offset: 768)
!332 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !297, file: !296, line: 100, baseType: !308, size: 64, align: 64, offset: 832)
!333 = !DIDerivedType(tag: DW_TAG_member, name: "in_stream", scope: !292, file: !1, line: 54, baseType: !82, size: 8, align: 8, offset: 896)
!334 = !DIDerivedType(tag: DW_TAG_member, name: "out_block", scope: !292, file: !1, line: 55, baseType: !335, size: 64, align: 64, offset: 960)
!335 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !304, size: 64, align: 64)
!336 = !DIDerivedType(tag: DW_TAG_member, name: "out_block_size", scope: !292, file: !1, line: 56, baseType: !45, size: 64, align: 64, offset: 1024)
!337 = !DIDerivedType(tag: DW_TAG_member, name: "total_out", scope: !292, file: !1, line: 57, baseType: !52, size: 64, align: 64, offset: 1088)
!338 = !DIDerivedType(tag: DW_TAG_member, name: "crc", scope: !292, file: !1, line: 58, baseType: !47, size: 64, align: 64, offset: 1152)
!339 = !DIDerivedType(tag: DW_TAG_member, name: "eof", scope: !292, file: !1, line: 59, baseType: !82, size: 8, align: 8, offset: 1216)
!340 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !53, line: 122, baseType: !47)
!341 = !{!342, !343, !344, !345, !349, !350, !351, !352, !353}
!342 = distinct !DISubprogram(name: "archive_read_support_compression_gzip", scope: !1, file: !1, line: 84, type: !21, isLocal: false, isDefinition: true, scopeLine: 85, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!343 = distinct !DISubprogram(name: "archive_read_support_filter_gzip", scope: !1, file: !1, line: 91, type: !21, isLocal: false, isDefinition: true, scopeLine: 92, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!344 = distinct !DISubprogram(name: "gzip_bidder_bid", scope: !1, file: !1, line: 210, type: !166, isLocal: true, isDefinition: true, scopeLine: 212, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!345 = distinct !DISubprogram(name: "peek_at_header", scope: !1, file: !1, line: 126, type: !346, isLocal: true, isDefinition: true, scopeLine: 127, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!346 = !DISubroutineType(types: !347)
!347 = !{!38, !169, !348}
!348 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !23, size: 64, align: 64)
!349 = distinct !DISubprogram(name: "gzip_bidder_init", scope: !1, file: !1, line: 250, type: !178, isLocal: true, isDefinition: true, scopeLine: 251, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!350 = distinct !DISubprogram(name: "gzip_filter_read", scope: !1, file: !1, line: 373, type: !182, isLocal: true, isDefinition: true, scopeLine: 374, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!351 = distinct !DISubprogram(name: "consume_header", scope: !1, file: !1, line: 282, type: !178, isLocal: true, isDefinition: true, scopeLine: 283, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!352 = distinct !DISubprogram(name: "consume_trailer", scope: !1, file: !1, line: 340, type: !178, isLocal: true, isDefinition: true, scopeLine: 341, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!353 = distinct !DISubprogram(name: "gzip_filter_close", scope: !1, file: !1, line: 452, type: !178, isLocal: true, isDefinition: true, scopeLine: 453, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!354 = !{!355}
!355 = !DIGlobalVariable(name: "out_block_size", scope: !349, file: !1, line: 253, type: !356, isLocal: true, isDefinition: true, variable: i64* @gzip_bidder_init.out_block_size)
!356 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !45)
!357 = !{i32 2, !"Dwarf Version", i32 4}
!358 = !{i32 2, !"Debug Info Version", i32 3}
!359 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!360 = !DILocalVariable(name: "a", arg: 1, scope: !342, file: !1, line: 84, type: !24)
!361 = !DIExpression()
!362 = !DILocation(line: 84, column: 55, scope: !342)
!363 = !DILocation(line: 86, column: 42, scope: !342)
!364 = !DILocation(line: 86, column: 9, scope: !342)
!365 = !DILocation(line: 86, column: 2, scope: !342)
!366 = !DILocalVariable(name: "_a", arg: 1, scope: !343, file: !1, line: 91, type: !24)
!367 = !DILocation(line: 91, column: 50, scope: !343)
!368 = !DILocalVariable(name: "a", scope: !343, file: !1, line: 93, type: !4)
!369 = !DILocation(line: 93, column: 23, scope: !343)
!370 = !DILocation(line: 93, column: 50, scope: !343)
!371 = !DILocation(line: 93, column: 27, scope: !343)
!372 = !DILocalVariable(name: "bidder", scope: !343, file: !1, line: 94, type: !168)
!373 = !DILocation(line: 94, column: 37, scope: !343)
!374 = !DILocation(line: 96, column: 2, scope: !343)
!375 = !DILocalVariable(name: "magic_test", scope: !376, file: !1, line: 96, type: !23)
!376 = distinct !DILexicalBlock(scope: !343, file: !1, line: 96, column: 2)
!377 = !DILocation(line: 96, column: 2, scope: !376)
!378 = !DILocation(line: 96, column: 2, scope: !379)
!379 = !DILexicalBlockFile(scope: !376, file: !1, discriminator: 1)
!380 = !DILocation(line: 96, column: 2, scope: !381)
!381 = !DILexicalBlockFile(scope: !382, file: !1, discriminator: 2)
!382 = distinct !DILexicalBlock(scope: !376, file: !1, line: 96, column: 2)
!383 = !DILocation(line: 96, column: 2, scope: !384)
!384 = !DILexicalBlockFile(scope: !376, file: !1, discriminator: 3)
!385 = !DILocation(line: 99, column: 32, scope: !386)
!386 = distinct !DILexicalBlock(scope: !343, file: !1, line: 99, column: 6)
!387 = !DILocation(line: 99, column: 6, scope: !386)
!388 = !DILocation(line: 99, column: 44, scope: !386)
!389 = !DILocation(line: 99, column: 6, scope: !343)
!390 = !DILocation(line: 100, column: 3, scope: !386)
!391 = !DILocation(line: 102, column: 2, scope: !343)
!392 = !DILocation(line: 102, column: 10, scope: !343)
!393 = !DILocation(line: 102, column: 15, scope: !343)
!394 = !DILocation(line: 103, column: 2, scope: !343)
!395 = !DILocation(line: 103, column: 10, scope: !343)
!396 = !DILocation(line: 103, column: 15, scope: !343)
!397 = !DILocation(line: 104, column: 2, scope: !343)
!398 = !DILocation(line: 104, column: 10, scope: !343)
!399 = !DILocation(line: 104, column: 14, scope: !343)
!400 = !DILocation(line: 105, column: 2, scope: !343)
!401 = !DILocation(line: 105, column: 10, scope: !343)
!402 = !DILocation(line: 105, column: 15, scope: !343)
!403 = !DILocation(line: 106, column: 2, scope: !343)
!404 = !DILocation(line: 106, column: 10, scope: !343)
!405 = !DILocation(line: 106, column: 18, scope: !343)
!406 = !DILocation(line: 107, column: 2, scope: !343)
!407 = !DILocation(line: 107, column: 10, scope: !343)
!408 = !DILocation(line: 107, column: 15, scope: !343)
!409 = !DILocation(line: 110, column: 2, scope: !343)
!410 = !DILocation(line: 116, column: 1, scope: !343)
!411 = !DILocalVariable(name: "self", arg: 1, scope: !344, file: !1, line: 210, type: !168)
!412 = !DILocation(line: 210, column: 52, scope: !344)
!413 = !DILocalVariable(name: "filter", arg: 2, scope: !344, file: !1, line: 211, type: !169)
!414 = !DILocation(line: 211, column: 33, scope: !344)
!415 = !DILocalVariable(name: "bits_checked", scope: !344, file: !1, line: 213, type: !23)
!416 = !DILocation(line: 213, column: 6, scope: !344)
!417 = !DILocation(line: 215, column: 8, scope: !344)
!418 = !DILocation(line: 217, column: 21, scope: !419)
!419 = distinct !DILexicalBlock(scope: !344, file: !1, line: 217, column: 6)
!420 = !DILocation(line: 217, column: 6, scope: !419)
!421 = !DILocation(line: 217, column: 6, scope: !344)
!422 = !DILocation(line: 218, column: 11, scope: !419)
!423 = !DILocation(line: 218, column: 3, scope: !419)
!424 = !DILocation(line: 219, column: 2, scope: !344)
!425 = !DILocation(line: 220, column: 1, scope: !344)
!426 = !DILocalVariable(name: "self", arg: 1, scope: !349, file: !1, line: 250, type: !169)
!427 = !DILocation(line: 250, column: 46, scope: !349)
!428 = !DILocalVariable(name: "state", scope: !349, file: !1, line: 252, type: !291)
!429 = !DILocation(line: 252, column: 23, scope: !349)
!430 = !DILocalVariable(name: "out_block", scope: !349, file: !1, line: 254, type: !122)
!431 = !DILocation(line: 254, column: 8, scope: !349)
!432 = !DILocation(line: 256, column: 2, scope: !349)
!433 = !DILocation(line: 256, column: 8, scope: !349)
!434 = !DILocation(line: 256, column: 13, scope: !349)
!435 = !DILocation(line: 257, column: 2, scope: !349)
!436 = !DILocation(line: 257, column: 8, scope: !349)
!437 = !DILocation(line: 257, column: 13, scope: !349)
!438 = !DILocation(line: 259, column: 33, scope: !349)
!439 = !DILocation(line: 259, column: 10, scope: !349)
!440 = !DILocation(line: 259, column: 8, scope: !349)
!441 = !DILocation(line: 260, column: 31, scope: !349)
!442 = !DILocation(line: 260, column: 12, scope: !349)
!443 = !DILocation(line: 261, column: 6, scope: !444)
!444 = distinct !DILexicalBlock(scope: !349, file: !1, line: 261, column: 6)
!445 = !DILocation(line: 261, column: 12, scope: !444)
!446 = !DILocation(line: 261, column: 20, scope: !444)
!447 = !DILocation(line: 261, column: 23, scope: !448)
!448 = !DILexicalBlockFile(scope: !444, file: !1, discriminator: 1)
!449 = !DILocation(line: 261, column: 33, scope: !448)
!450 = !DILocation(line: 261, column: 6, scope: !448)
!451 = !DILocation(line: 262, column: 8, scope: !452)
!452 = distinct !DILexicalBlock(scope: !444, file: !1, line: 261, column: 42)
!453 = !DILocation(line: 262, column: 3, scope: !452)
!454 = !DILocation(line: 263, column: 8, scope: !452)
!455 = !DILocation(line: 263, column: 3, scope: !452)
!456 = !DILocation(line: 264, column: 22, scope: !452)
!457 = !DILocation(line: 264, column: 28, scope: !452)
!458 = !DILocation(line: 264, column: 37, scope: !452)
!459 = !DILocation(line: 264, column: 3, scope: !452)
!460 = !DILocation(line: 266, column: 3, scope: !452)
!461 = !DILocation(line: 269, column: 15, scope: !349)
!462 = !DILocation(line: 269, column: 2, scope: !349)
!463 = !DILocation(line: 269, column: 8, scope: !349)
!464 = !DILocation(line: 269, column: 13, scope: !349)
!465 = !DILocation(line: 270, column: 2, scope: !349)
!466 = !DILocation(line: 270, column: 9, scope: !349)
!467 = !DILocation(line: 270, column: 24, scope: !349)
!468 = !DILocation(line: 271, column: 21, scope: !349)
!469 = !DILocation(line: 271, column: 2, scope: !349)
!470 = !DILocation(line: 271, column: 9, scope: !349)
!471 = !DILocation(line: 271, column: 19, scope: !349)
!472 = !DILocation(line: 272, column: 2, scope: !349)
!473 = !DILocation(line: 272, column: 8, scope: !349)
!474 = !DILocation(line: 272, column: 13, scope: !349)
!475 = !DILocation(line: 273, column: 2, scope: !349)
!476 = !DILocation(line: 273, column: 8, scope: !349)
!477 = !DILocation(line: 273, column: 13, scope: !349)
!478 = !DILocation(line: 274, column: 2, scope: !349)
!479 = !DILocation(line: 274, column: 8, scope: !349)
!480 = !DILocation(line: 274, column: 14, scope: !349)
!481 = !DILocation(line: 276, column: 2, scope: !349)
!482 = !DILocation(line: 276, column: 9, scope: !349)
!483 = !DILocation(line: 276, column: 19, scope: !349)
!484 = !DILocation(line: 278, column: 2, scope: !349)
!485 = !DILocation(line: 279, column: 1, scope: !349)
!486 = !DILocalVariable(name: "filter", arg: 1, scope: !345, file: !1, line: 126, type: !169)
!487 = !DILocation(line: 126, column: 44, scope: !345)
!488 = !DILocalVariable(name: "pbits", arg: 2, scope: !345, file: !1, line: 126, type: !348)
!489 = !DILocation(line: 126, column: 57, scope: !345)
!490 = !DILocalVariable(name: "p", scope: !345, file: !1, line: 128, type: !491)
!491 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !492, size: 64, align: 64)
!492 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !304)
!493 = !DILocation(line: 128, column: 23, scope: !345)
!494 = !DILocalVariable(name: "avail", scope: !345, file: !1, line: 129, type: !38)
!495 = !DILocation(line: 129, column: 10, scope: !345)
!496 = !DILocalVariable(name: "len", scope: !345, file: !1, line: 129, type: !38)
!497 = !DILocation(line: 129, column: 17, scope: !345)
!498 = !DILocalVariable(name: "bits", scope: !345, file: !1, line: 130, type: !23)
!499 = !DILocation(line: 130, column: 6, scope: !345)
!500 = !DILocalVariable(name: "header_flags", scope: !345, file: !1, line: 131, type: !23)
!501 = !DILocation(line: 131, column: 6, scope: !345)
!502 = !DILocation(line: 135, column: 6, scope: !345)
!503 = !DILocation(line: 136, column: 34, scope: !345)
!504 = !DILocation(line: 136, column: 42, scope: !345)
!505 = !DILocation(line: 136, column: 6, scope: !345)
!506 = !DILocation(line: 136, column: 4, scope: !345)
!507 = !DILocation(line: 137, column: 6, scope: !508)
!508 = distinct !DILexicalBlock(scope: !345, file: !1, line: 137, column: 6)
!509 = !DILocation(line: 137, column: 8, scope: !508)
!510 = !DILocation(line: 137, column: 16, scope: !508)
!511 = !DILocation(line: 137, column: 19, scope: !512)
!512 = !DILexicalBlockFile(scope: !508, file: !1, discriminator: 1)
!513 = !DILocation(line: 137, column: 25, scope: !512)
!514 = !DILocation(line: 137, column: 6, scope: !512)
!515 = !DILocation(line: 138, column: 3, scope: !508)
!516 = !DILocation(line: 140, column: 13, scope: !517)
!517 = distinct !DILexicalBlock(scope: !345, file: !1, line: 140, column: 6)
!518 = !DILocation(line: 140, column: 6, scope: !517)
!519 = !DILocation(line: 140, column: 35, scope: !517)
!520 = !DILocation(line: 140, column: 6, scope: !345)
!521 = !DILocation(line: 141, column: 3, scope: !517)
!522 = !DILocation(line: 142, column: 7, scope: !345)
!523 = !DILocation(line: 143, column: 7, scope: !524)
!524 = distinct !DILexicalBlock(scope: !345, file: !1, line: 143, column: 6)
!525 = !DILocation(line: 143, column: 12, scope: !524)
!526 = !DILocation(line: 143, column: 19, scope: !524)
!527 = !DILocation(line: 143, column: 6, scope: !345)
!528 = !DILocation(line: 144, column: 3, scope: !524)
!529 = !DILocation(line: 145, column: 7, scope: !345)
!530 = !DILocation(line: 146, column: 17, scope: !345)
!531 = !DILocation(line: 146, column: 15, scope: !345)
!532 = !DILocation(line: 154, column: 6, scope: !533)
!533 = distinct !DILexicalBlock(scope: !345, file: !1, line: 154, column: 6)
!534 = !DILocation(line: 154, column: 19, scope: !533)
!535 = !DILocation(line: 154, column: 6, scope: !345)
!536 = !DILocation(line: 155, column: 35, scope: !537)
!537 = distinct !DILexicalBlock(scope: !533, file: !1, line: 154, column: 24)
!538 = !DILocation(line: 155, column: 43, scope: !537)
!539 = !DILocation(line: 155, column: 47, scope: !537)
!540 = !DILocation(line: 155, column: 7, scope: !537)
!541 = !DILocation(line: 155, column: 5, scope: !537)
!542 = !DILocation(line: 156, column: 7, scope: !543)
!543 = distinct !DILexicalBlock(scope: !537, file: !1, line: 156, column: 7)
!544 = !DILocation(line: 156, column: 9, scope: !543)
!545 = !DILocation(line: 156, column: 7, scope: !537)
!546 = !DILocation(line: 157, column: 4, scope: !543)
!547 = !DILocation(line: 158, column: 18, scope: !537)
!548 = !DILocation(line: 158, column: 22, scope: !537)
!549 = !DILocation(line: 158, column: 16, scope: !537)
!550 = !DILocation(line: 158, column: 11, scope: !537)
!551 = !DILocation(line: 158, column: 27, scope: !537)
!552 = !DILocation(line: 158, column: 42, scope: !537)
!553 = !DILocation(line: 158, column: 40, scope: !537)
!554 = !DILocation(line: 158, column: 35, scope: !537)
!555 = !DILocation(line: 158, column: 33, scope: !537)
!556 = !DILocation(line: 158, column: 10, scope: !537)
!557 = !DILocation(line: 158, column: 7, scope: !537)
!558 = !DILocation(line: 159, column: 7, scope: !537)
!559 = !DILocation(line: 160, column: 2, scope: !537)
!560 = !DILocation(line: 163, column: 6, scope: !561)
!561 = distinct !DILexicalBlock(scope: !345, file: !1, line: 163, column: 6)
!562 = !DILocation(line: 163, column: 19, scope: !561)
!563 = !DILocation(line: 163, column: 6, scope: !345)
!564 = !DILocation(line: 164, column: 3, scope: !565)
!565 = distinct !DILexicalBlock(scope: !561, file: !1, line: 163, column: 24)
!566 = !DILocation(line: 165, column: 4, scope: !567)
!567 = distinct !DILexicalBlock(scope: !565, file: !1, line: 164, column: 6)
!568 = !DILocation(line: 166, column: 8, scope: !569)
!569 = distinct !DILexicalBlock(scope: !567, file: !1, line: 166, column: 8)
!570 = !DILocation(line: 166, column: 16, scope: !569)
!571 = !DILocation(line: 166, column: 14, scope: !569)
!572 = !DILocation(line: 166, column: 8, scope: !567)
!573 = !DILocation(line: 167, column: 37, scope: !569)
!574 = !DILocation(line: 168, column: 9, scope: !569)
!575 = !DILocation(line: 167, column: 9, scope: !569)
!576 = !DILocation(line: 167, column: 7, scope: !569)
!577 = !DILocation(line: 167, column: 5, scope: !569)
!578 = !DILocation(line: 169, column: 8, scope: !579)
!579 = distinct !DILexicalBlock(scope: !567, file: !1, line: 169, column: 8)
!580 = !DILocation(line: 169, column: 10, scope: !579)
!581 = !DILocation(line: 169, column: 8, scope: !567)
!582 = !DILocation(line: 170, column: 5, scope: !579)
!583 = !DILocation(line: 171, column: 3, scope: !567)
!584 = !DILocation(line: 171, column: 14, scope: !585)
!585 = !DILexicalBlockFile(scope: !565, file: !1, discriminator: 1)
!586 = !DILocation(line: 171, column: 18, scope: !585)
!587 = !DILocation(line: 171, column: 12, scope: !585)
!588 = !DILocation(line: 171, column: 23, scope: !585)
!589 = !DILocation(line: 171, column: 3, scope: !585)
!590 = !DILocation(line: 172, column: 2, scope: !565)
!591 = !DILocation(line: 175, column: 6, scope: !592)
!592 = distinct !DILexicalBlock(scope: !345, file: !1, line: 175, column: 6)
!593 = !DILocation(line: 175, column: 19, scope: !592)
!594 = !DILocation(line: 175, column: 6, scope: !345)
!595 = !DILocation(line: 176, column: 3, scope: !596)
!596 = distinct !DILexicalBlock(scope: !592, file: !1, line: 175, column: 25)
!597 = !DILocation(line: 177, column: 4, scope: !598)
!598 = distinct !DILexicalBlock(scope: !596, file: !1, line: 176, column: 6)
!599 = !DILocation(line: 178, column: 8, scope: !600)
!600 = distinct !DILexicalBlock(scope: !598, file: !1, line: 178, column: 8)
!601 = !DILocation(line: 178, column: 16, scope: !600)
!602 = !DILocation(line: 178, column: 14, scope: !600)
!603 = !DILocation(line: 178, column: 8, scope: !598)
!604 = !DILocation(line: 179, column: 37, scope: !600)
!605 = !DILocation(line: 180, column: 9, scope: !600)
!606 = !DILocation(line: 179, column: 9, scope: !600)
!607 = !DILocation(line: 179, column: 7, scope: !600)
!608 = !DILocation(line: 179, column: 5, scope: !600)
!609 = !DILocation(line: 181, column: 8, scope: !610)
!610 = distinct !DILexicalBlock(scope: !598, file: !1, line: 181, column: 8)
!611 = !DILocation(line: 181, column: 10, scope: !610)
!612 = !DILocation(line: 181, column: 8, scope: !598)
!613 = !DILocation(line: 182, column: 5, scope: !610)
!614 = !DILocation(line: 183, column: 3, scope: !598)
!615 = !DILocation(line: 183, column: 14, scope: !616)
!616 = !DILexicalBlockFile(scope: !596, file: !1, discriminator: 1)
!617 = !DILocation(line: 183, column: 18, scope: !616)
!618 = !DILocation(line: 183, column: 12, scope: !616)
!619 = !DILocation(line: 183, column: 23, scope: !616)
!620 = !DILocation(line: 183, column: 3, scope: !616)
!621 = !DILocation(line: 184, column: 2, scope: !596)
!622 = !DILocation(line: 187, column: 7, scope: !623)
!623 = distinct !DILexicalBlock(scope: !345, file: !1, line: 187, column: 6)
!624 = !DILocation(line: 187, column: 20, scope: !623)
!625 = !DILocation(line: 187, column: 6, scope: !345)
!626 = !DILocation(line: 188, column: 35, scope: !627)
!627 = distinct !DILexicalBlock(scope: !623, file: !1, line: 187, column: 26)
!628 = !DILocation(line: 188, column: 43, scope: !627)
!629 = !DILocation(line: 188, column: 47, scope: !627)
!630 = !DILocation(line: 188, column: 7, scope: !627)
!631 = !DILocation(line: 188, column: 5, scope: !627)
!632 = !DILocation(line: 189, column: 7, scope: !633)
!633 = distinct !DILexicalBlock(scope: !627, file: !1, line: 189, column: 7)
!634 = !DILocation(line: 189, column: 9, scope: !633)
!635 = !DILocation(line: 189, column: 7, scope: !627)
!636 = !DILocation(line: 190, column: 4, scope: !633)
!637 = !DILocation(line: 198, column: 7, scope: !627)
!638 = !DILocation(line: 199, column: 2, scope: !627)
!639 = !DILocation(line: 201, column: 6, scope: !640)
!640 = distinct !DILexicalBlock(scope: !345, file: !1, line: 201, column: 6)
!641 = !DILocation(line: 201, column: 12, scope: !640)
!642 = !DILocation(line: 201, column: 6, scope: !345)
!643 = !DILocation(line: 202, column: 12, scope: !640)
!644 = !DILocation(line: 202, column: 4, scope: !640)
!645 = !DILocation(line: 202, column: 10, scope: !640)
!646 = !DILocation(line: 202, column: 3, scope: !640)
!647 = !DILocation(line: 203, column: 10, scope: !345)
!648 = !DILocation(line: 203, column: 2, scope: !345)
!649 = !DILocation(line: 204, column: 1, scope: !345)
!650 = !DILocalVariable(name: "self", arg: 1, scope: !350, file: !1, line: 373, type: !169)
!651 = !DILocation(line: 373, column: 46, scope: !350)
!652 = !DILocalVariable(name: "p", arg: 2, scope: !350, file: !1, line: 373, type: !64)
!653 = !DILocation(line: 373, column: 65, scope: !350)
!654 = !DILocalVariable(name: "state", scope: !350, file: !1, line: 375, type: !291)
!655 = !DILocation(line: 375, column: 23, scope: !350)
!656 = !DILocalVariable(name: "decompressed", scope: !350, file: !1, line: 376, type: !45)
!657 = !DILocation(line: 376, column: 9, scope: !350)
!658 = !DILocalVariable(name: "avail_in", scope: !350, file: !1, line: 377, type: !38)
!659 = !DILocation(line: 377, column: 10, scope: !350)
!660 = !DILocalVariable(name: "ret", scope: !350, file: !1, line: 378, type: !23)
!661 = !DILocation(line: 378, column: 6, scope: !350)
!662 = !DILocation(line: 380, column: 33, scope: !350)
!663 = !DILocation(line: 380, column: 39, scope: !350)
!664 = !DILocation(line: 380, column: 10, scope: !350)
!665 = !DILocation(line: 380, column: 8, scope: !350)
!666 = !DILocation(line: 383, column: 27, scope: !350)
!667 = !DILocation(line: 383, column: 34, scope: !350)
!668 = !DILocation(line: 383, column: 2, scope: !350)
!669 = !DILocation(line: 383, column: 9, scope: !350)
!670 = !DILocation(line: 383, column: 16, scope: !350)
!671 = !DILocation(line: 383, column: 25, scope: !350)
!672 = !DILocation(line: 384, column: 34, scope: !350)
!673 = !DILocation(line: 384, column: 41, scope: !350)
!674 = !DILocation(line: 384, column: 28, scope: !350)
!675 = !DILocation(line: 384, column: 2, scope: !350)
!676 = !DILocation(line: 384, column: 9, scope: !350)
!677 = !DILocation(line: 384, column: 16, scope: !350)
!678 = !DILocation(line: 384, column: 26, scope: !350)
!679 = !DILocation(line: 387, column: 2, scope: !350)
!680 = !DILocation(line: 387, column: 9, scope: !681)
!681 = !DILexicalBlockFile(scope: !350, file: !1, discriminator: 1)
!682 = !DILocation(line: 387, column: 16, scope: !681)
!683 = !DILocation(line: 387, column: 23, scope: !681)
!684 = !DILocation(line: 387, column: 33, scope: !681)
!685 = !DILocation(line: 387, column: 37, scope: !681)
!686 = !DILocation(line: 387, column: 41, scope: !687)
!687 = !DILexicalBlockFile(scope: !350, file: !1, discriminator: 2)
!688 = !DILocation(line: 387, column: 48, scope: !687)
!689 = !DILocation(line: 387, column: 40, scope: !687)
!690 = !DILocation(line: 387, column: 2, scope: !691)
!691 = !DILexicalBlockFile(scope: !350, file: !1, discriminator: 3)
!692 = !DILocation(line: 390, column: 8, scope: !693)
!693 = distinct !DILexicalBlock(scope: !694, file: !1, line: 390, column: 7)
!694 = distinct !DILexicalBlock(scope: !350, file: !1, line: 387, column: 53)
!695 = !DILocation(line: 390, column: 15, scope: !693)
!696 = !DILocation(line: 390, column: 7, scope: !694)
!697 = !DILocation(line: 391, column: 25, scope: !698)
!698 = distinct !DILexicalBlock(scope: !693, file: !1, line: 390, column: 26)
!699 = !DILocation(line: 391, column: 10, scope: !698)
!700 = !DILocation(line: 391, column: 8, scope: !698)
!701 = !DILocation(line: 392, column: 8, scope: !702)
!702 = distinct !DILexicalBlock(scope: !698, file: !1, line: 392, column: 8)
!703 = !DILocation(line: 392, column: 12, scope: !702)
!704 = !DILocation(line: 392, column: 8, scope: !698)
!705 = !DILocation(line: 393, column: 5, scope: !706)
!706 = distinct !DILexicalBlock(scope: !702, file: !1, line: 392, column: 28)
!707 = !DILocation(line: 393, column: 12, scope: !706)
!708 = !DILocation(line: 393, column: 16, scope: !706)
!709 = !DILocation(line: 394, column: 5, scope: !706)
!710 = !DILocation(line: 396, column: 8, scope: !711)
!711 = distinct !DILexicalBlock(scope: !698, file: !1, line: 396, column: 8)
!712 = !DILocation(line: 396, column: 12, scope: !711)
!713 = !DILocation(line: 396, column: 8, scope: !698)
!714 = !DILocation(line: 397, column: 13, scope: !711)
!715 = !DILocation(line: 397, column: 12, scope: !711)
!716 = !DILocation(line: 397, column: 5, scope: !711)
!717 = !DILocation(line: 398, column: 3, scope: !698)
!718 = !DILocation(line: 404, column: 35, scope: !694)
!719 = !DILocation(line: 404, column: 41, scope: !694)
!720 = !DILocation(line: 404, column: 7, scope: !694)
!721 = !DILocation(line: 403, column: 44, scope: !694)
!722 = !DILocation(line: 403, column: 27, scope: !694)
!723 = !DILocation(line: 403, column: 3, scope: !694)
!724 = !DILocation(line: 403, column: 10, scope: !694)
!725 = !DILocation(line: 403, column: 17, scope: !694)
!726 = !DILocation(line: 403, column: 25, scope: !694)
!727 = !DILocation(line: 405, column: 7, scope: !728)
!728 = distinct !DILexicalBlock(scope: !694, file: !1, line: 405, column: 7)
!729 = !DILocation(line: 405, column: 14, scope: !728)
!730 = !DILocation(line: 405, column: 21, scope: !728)
!731 = !DILocation(line: 405, column: 29, scope: !728)
!732 = !DILocation(line: 405, column: 7, scope: !694)
!733 = !DILocation(line: 406, column: 23, scope: !734)
!734 = distinct !DILexicalBlock(scope: !728, file: !1, line: 405, column: 38)
!735 = !DILocation(line: 406, column: 29, scope: !734)
!736 = !DILocation(line: 406, column: 38, scope: !734)
!737 = !DILocation(line: 406, column: 4, scope: !734)
!738 = !DILocation(line: 409, column: 4, scope: !734)
!739 = !DILocation(line: 411, column: 34, scope: !694)
!740 = !DILocation(line: 411, column: 28, scope: !694)
!741 = !DILocation(line: 411, column: 3, scope: !694)
!742 = !DILocation(line: 411, column: 10, scope: !694)
!743 = !DILocation(line: 411, column: 17, scope: !694)
!744 = !DILocation(line: 411, column: 26, scope: !694)
!745 = !DILocation(line: 414, column: 19, scope: !694)
!746 = !DILocation(line: 414, column: 26, scope: !694)
!747 = !DILocation(line: 414, column: 9, scope: !694)
!748 = !DILocation(line: 414, column: 7, scope: !694)
!749 = !DILocation(line: 415, column: 11, scope: !694)
!750 = !DILocation(line: 415, column: 3, scope: !694)
!751 = !DILocation(line: 417, column: 34, scope: !752)
!752 = distinct !DILexicalBlock(scope: !694, file: !1, line: 415, column: 16)
!753 = !DILocation(line: 417, column: 40, scope: !752)
!754 = !DILocation(line: 418, column: 8, scope: !752)
!755 = !DILocation(line: 418, column: 19, scope: !752)
!756 = !DILocation(line: 418, column: 26, scope: !752)
!757 = !DILocation(line: 418, column: 33, scope: !752)
!758 = !DILocation(line: 418, column: 17, scope: !752)
!759 = !DILocation(line: 417, column: 4, scope: !752)
!760 = !DILocation(line: 419, column: 4, scope: !752)
!761 = !DILocation(line: 421, column: 34, scope: !752)
!762 = !DILocation(line: 421, column: 40, scope: !752)
!763 = !DILocation(line: 422, column: 8, scope: !752)
!764 = !DILocation(line: 422, column: 19, scope: !752)
!765 = !DILocation(line: 422, column: 26, scope: !752)
!766 = !DILocation(line: 422, column: 33, scope: !752)
!767 = !DILocation(line: 422, column: 17, scope: !752)
!768 = !DILocation(line: 421, column: 4, scope: !752)
!769 = !DILocation(line: 425, column: 26, scope: !752)
!770 = !DILocation(line: 425, column: 10, scope: !752)
!771 = !DILocation(line: 425, column: 8, scope: !752)
!772 = !DILocation(line: 426, column: 8, scope: !773)
!773 = distinct !DILexicalBlock(scope: !752, file: !1, line: 426, column: 8)
!774 = !DILocation(line: 426, column: 12, scope: !773)
!775 = !DILocation(line: 426, column: 8, scope: !752)
!776 = !DILocation(line: 427, column: 13, scope: !773)
!777 = !DILocation(line: 427, column: 12, scope: !773)
!778 = !DILocation(line: 427, column: 5, scope: !773)
!779 = !DILocation(line: 428, column: 4, scope: !752)
!780 = !DILocation(line: 431, column: 23, scope: !752)
!781 = !DILocation(line: 431, column: 29, scope: !752)
!782 = !DILocation(line: 431, column: 38, scope: !752)
!783 = !DILocation(line: 431, column: 4, scope: !752)
!784 = !DILocation(line: 434, column: 4, scope: !752)
!785 = !DILocation(line: 387, column: 2, scope: !786)
!786 = !DILexicalBlockFile(scope: !350, file: !1, discriminator: 4)
!787 = !DILocation(line: 439, column: 17, scope: !350)
!788 = !DILocation(line: 439, column: 24, scope: !350)
!789 = !DILocation(line: 439, column: 31, scope: !350)
!790 = !DILocation(line: 439, column: 42, scope: !350)
!791 = !DILocation(line: 439, column: 49, scope: !350)
!792 = !DILocation(line: 439, column: 40, scope: !350)
!793 = !DILocation(line: 439, column: 15, scope: !350)
!794 = !DILocation(line: 440, column: 22, scope: !350)
!795 = !DILocation(line: 440, column: 2, scope: !350)
!796 = !DILocation(line: 440, column: 9, scope: !350)
!797 = !DILocation(line: 440, column: 19, scope: !350)
!798 = !DILocation(line: 441, column: 6, scope: !799)
!799 = distinct !DILexicalBlock(scope: !350, file: !1, line: 441, column: 6)
!800 = !DILocation(line: 441, column: 19, scope: !799)
!801 = !DILocation(line: 441, column: 6, scope: !350)
!802 = !DILocation(line: 442, column: 4, scope: !799)
!803 = !DILocation(line: 442, column: 6, scope: !799)
!804 = !DILocation(line: 442, column: 3, scope: !799)
!805 = !DILocation(line: 444, column: 8, scope: !799)
!806 = !DILocation(line: 444, column: 15, scope: !799)
!807 = !DILocation(line: 444, column: 4, scope: !799)
!808 = !DILocation(line: 444, column: 6, scope: !799)
!809 = !DILocation(line: 445, column: 10, scope: !350)
!810 = !DILocation(line: 445, column: 2, scope: !350)
!811 = !DILocation(line: 446, column: 1, scope: !350)
!812 = !DILocalVariable(name: "self", arg: 1, scope: !353, file: !1, line: 452, type: !169)
!813 = !DILocation(line: 452, column: 47, scope: !353)
!814 = !DILocalVariable(name: "state", scope: !353, file: !1, line: 454, type: !291)
!815 = !DILocation(line: 454, column: 23, scope: !353)
!816 = !DILocalVariable(name: "ret", scope: !353, file: !1, line: 455, type: !23)
!817 = !DILocation(line: 455, column: 6, scope: !353)
!818 = !DILocation(line: 457, column: 33, scope: !353)
!819 = !DILocation(line: 457, column: 39, scope: !353)
!820 = !DILocation(line: 457, column: 10, scope: !353)
!821 = !DILocation(line: 457, column: 8, scope: !353)
!822 = !DILocation(line: 458, column: 6, scope: !353)
!823 = !DILocation(line: 460, column: 6, scope: !824)
!824 = distinct !DILexicalBlock(scope: !353, file: !1, line: 460, column: 6)
!825 = !DILocation(line: 460, column: 13, scope: !824)
!826 = !DILocation(line: 460, column: 6, scope: !353)
!827 = !DILocation(line: 461, column: 24, scope: !828)
!828 = distinct !DILexicalBlock(scope: !824, file: !1, line: 460, column: 24)
!829 = !DILocation(line: 461, column: 31, scope: !828)
!830 = !DILocation(line: 461, column: 11, scope: !828)
!831 = !DILocation(line: 461, column: 3, scope: !828)
!832 = !DILocation(line: 463, column: 4, scope: !833)
!833 = distinct !DILexicalBlock(scope: !828, file: !1, line: 461, column: 41)
!834 = !DILocation(line: 465, column: 24, scope: !833)
!835 = !DILocation(line: 465, column: 30, scope: !833)
!836 = !DILocation(line: 465, column: 39, scope: !833)
!837 = !DILocation(line: 465, column: 4, scope: !833)
!838 = !DILocation(line: 468, column: 8, scope: !833)
!839 = !DILocation(line: 469, column: 3, scope: !833)
!840 = !DILocation(line: 470, column: 2, scope: !828)
!841 = !DILocation(line: 472, column: 7, scope: !353)
!842 = !DILocation(line: 472, column: 14, scope: !353)
!843 = !DILocation(line: 472, column: 2, scope: !353)
!844 = !DILocation(line: 473, column: 7, scope: !353)
!845 = !DILocation(line: 473, column: 2, scope: !353)
!846 = !DILocation(line: 474, column: 10, scope: !353)
!847 = !DILocation(line: 474, column: 2, scope: !353)
!848 = !DILocalVariable(name: "self", arg: 1, scope: !351, file: !1, line: 282, type: !169)
!849 = !DILocation(line: 282, column: 44, scope: !351)
!850 = !DILocalVariable(name: "state", scope: !351, file: !1, line: 284, type: !291)
!851 = !DILocation(line: 284, column: 23, scope: !351)
!852 = !DILocalVariable(name: "avail", scope: !351, file: !1, line: 285, type: !38)
!853 = !DILocation(line: 285, column: 10, scope: !351)
!854 = !DILocalVariable(name: "len", scope: !351, file: !1, line: 286, type: !45)
!855 = !DILocation(line: 286, column: 9, scope: !351)
!856 = !DILocalVariable(name: "ret", scope: !351, file: !1, line: 287, type: !23)
!857 = !DILocation(line: 287, column: 6, scope: !351)
!858 = !DILocation(line: 289, column: 33, scope: !351)
!859 = !DILocation(line: 289, column: 39, scope: !351)
!860 = !DILocation(line: 289, column: 10, scope: !351)
!861 = !DILocation(line: 289, column: 8, scope: !351)
!862 = !DILocation(line: 292, column: 23, scope: !351)
!863 = !DILocation(line: 292, column: 29, scope: !351)
!864 = !DILocation(line: 292, column: 8, scope: !351)
!865 = !DILocation(line: 292, column: 6, scope: !351)
!866 = !DILocation(line: 293, column: 6, scope: !867)
!867 = distinct !DILexicalBlock(scope: !351, file: !1, line: 293, column: 6)
!868 = !DILocation(line: 293, column: 10, scope: !867)
!869 = !DILocation(line: 293, column: 6, scope: !351)
!870 = !DILocation(line: 294, column: 3, scope: !867)
!871 = !DILocation(line: 295, column: 32, scope: !351)
!872 = !DILocation(line: 295, column: 38, scope: !351)
!873 = !DILocation(line: 295, column: 48, scope: !351)
!874 = !DILocation(line: 295, column: 2, scope: !351)
!875 = !DILocation(line: 298, column: 15, scope: !351)
!876 = !DILocation(line: 298, column: 2, scope: !351)
!877 = !DILocation(line: 298, column: 9, scope: !351)
!878 = !DILocation(line: 298, column: 13, scope: !351)
!879 = !DILocation(line: 302, column: 34, scope: !351)
!880 = !DILocation(line: 302, column: 40, scope: !351)
!881 = !DILocation(line: 302, column: 6, scope: !351)
!882 = !DILocation(line: 301, column: 43, scope: !351)
!883 = !DILocation(line: 301, column: 26, scope: !351)
!884 = !DILocation(line: 301, column: 2, scope: !351)
!885 = !DILocation(line: 301, column: 9, scope: !351)
!886 = !DILocation(line: 301, column: 16, scope: !351)
!887 = !DILocation(line: 301, column: 24, scope: !351)
!888 = !DILocation(line: 303, column: 33, scope: !351)
!889 = !DILocation(line: 303, column: 27, scope: !351)
!890 = !DILocation(line: 303, column: 2, scope: !351)
!891 = !DILocation(line: 303, column: 9, scope: !351)
!892 = !DILocation(line: 303, column: 16, scope: !351)
!893 = !DILocation(line: 303, column: 25, scope: !351)
!894 = !DILocation(line: 304, column: 8, scope: !351)
!895 = !DILocation(line: 304, column: 6, scope: !351)
!896 = !DILocation(line: 308, column: 10, scope: !351)
!897 = !DILocation(line: 308, column: 2, scope: !351)
!898 = !DILocation(line: 310, column: 3, scope: !899)
!899 = distinct !DILexicalBlock(scope: !351, file: !1, line: 308, column: 15)
!900 = !DILocation(line: 310, column: 10, scope: !899)
!901 = !DILocation(line: 310, column: 20, scope: !899)
!902 = !DILocation(line: 311, column: 3, scope: !899)
!903 = !DILocation(line: 313, column: 22, scope: !899)
!904 = !DILocation(line: 313, column: 28, scope: !899)
!905 = !DILocation(line: 313, column: 37, scope: !899)
!906 = !DILocation(line: 313, column: 3, scope: !899)
!907 = !DILocation(line: 317, column: 3, scope: !899)
!908 = !DILocation(line: 319, column: 22, scope: !899)
!909 = !DILocation(line: 319, column: 28, scope: !899)
!910 = !DILocation(line: 319, column: 37, scope: !899)
!911 = !DILocation(line: 319, column: 3, scope: !899)
!912 = !DILocation(line: 322, column: 3, scope: !899)
!913 = !DILocation(line: 324, column: 22, scope: !899)
!914 = !DILocation(line: 324, column: 28, scope: !899)
!915 = !DILocation(line: 324, column: 37, scope: !899)
!916 = !DILocation(line: 324, column: 3, scope: !899)
!917 = !DILocation(line: 328, column: 3, scope: !899)
!918 = !DILocation(line: 330, column: 22, scope: !899)
!919 = !DILocation(line: 330, column: 28, scope: !899)
!920 = !DILocation(line: 330, column: 37, scope: !899)
!921 = !DILocation(line: 333, column: 25, scope: !899)
!922 = !DILocation(line: 330, column: 3, scope: !899)
!923 = !DILocation(line: 334, column: 3, scope: !899)
!924 = !DILocation(line: 336, column: 2, scope: !351)
!925 = !DILocation(line: 337, column: 1, scope: !351)
!926 = !DILocalVariable(name: "self", arg: 1, scope: !352, file: !1, line: 340, type: !169)
!927 = !DILocation(line: 340, column: 45, scope: !352)
!928 = !DILocalVariable(name: "state", scope: !352, file: !1, line: 342, type: !291)
!929 = !DILocation(line: 342, column: 23, scope: !352)
!930 = !DILocalVariable(name: "p", scope: !352, file: !1, line: 343, type: !491)
!931 = !DILocation(line: 343, column: 23, scope: !352)
!932 = !DILocalVariable(name: "avail", scope: !352, file: !1, line: 344, type: !38)
!933 = !DILocation(line: 344, column: 10, scope: !352)
!934 = !DILocation(line: 346, column: 33, scope: !352)
!935 = !DILocation(line: 346, column: 39, scope: !352)
!936 = !DILocation(line: 346, column: 10, scope: !352)
!937 = !DILocation(line: 346, column: 8, scope: !352)
!938 = !DILocation(line: 348, column: 2, scope: !352)
!939 = !DILocation(line: 348, column: 9, scope: !352)
!940 = !DILocation(line: 348, column: 19, scope: !352)
!941 = !DILocation(line: 349, column: 23, scope: !352)
!942 = !DILocation(line: 349, column: 30, scope: !352)
!943 = !DILocation(line: 349, column: 10, scope: !352)
!944 = !DILocation(line: 349, column: 2, scope: !352)
!945 = !DILocation(line: 351, column: 3, scope: !946)
!946 = distinct !DILexicalBlock(scope: !352, file: !1, line: 349, column: 40)
!947 = !DILocation(line: 353, column: 22, scope: !946)
!948 = !DILocation(line: 353, column: 28, scope: !946)
!949 = !DILocation(line: 353, column: 37, scope: !946)
!950 = !DILocation(line: 353, column: 3, scope: !946)
!951 = !DILocation(line: 356, column: 3, scope: !946)
!952 = !DILocation(line: 360, column: 34, scope: !352)
!953 = !DILocation(line: 360, column: 40, scope: !352)
!954 = !DILocation(line: 360, column: 6, scope: !352)
!955 = !DILocation(line: 360, column: 4, scope: !352)
!956 = !DILocation(line: 361, column: 6, scope: !957)
!957 = distinct !DILexicalBlock(scope: !352, file: !1, line: 361, column: 6)
!958 = !DILocation(line: 361, column: 8, scope: !957)
!959 = !DILocation(line: 361, column: 16, scope: !957)
!960 = !DILocation(line: 361, column: 19, scope: !961)
!961 = !DILexicalBlockFile(scope: !957, file: !1, discriminator: 1)
!962 = !DILocation(line: 361, column: 25, scope: !961)
!963 = !DILocation(line: 361, column: 6, scope: !961)
!964 = !DILocation(line: 362, column: 3, scope: !957)
!965 = !DILocation(line: 367, column: 32, scope: !352)
!966 = !DILocation(line: 367, column: 38, scope: !352)
!967 = !DILocation(line: 367, column: 2, scope: !352)
!968 = !DILocation(line: 369, column: 2, scope: !352)
!969 = !DILocation(line: 370, column: 1, scope: !352)
