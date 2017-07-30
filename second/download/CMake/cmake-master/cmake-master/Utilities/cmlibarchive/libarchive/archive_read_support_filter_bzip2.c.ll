; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_support_filter_bzip2.c'
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
%struct.private_data = type { %struct.bz_stream, i8*, i64, i8, i8 }
%struct.bz_stream = type { i8*, i32, i32, i32, i8*, i32, i32, i32, i8*, i8* (i8*, i32, i32)*, void (i8*, i8*)*, i8* }

@.str = private unnamed_addr constant [34 x i8] c"archive_read_support_filter_bzip2\00", align 1
@.str.1 = private unnamed_addr constant [6 x i8] c"bzip2\00", align 1
@.str.2 = private unnamed_addr constant [4 x i8] c"BZh\00", align 1
@.str.3 = private unnamed_addr constant [7 x i8] c"1AY&SY\00", align 1
@.str.4 = private unnamed_addr constant [7 x i8] c"\17rE8P\90\00", align 1
@bzip2_reader_init.out_block_size = internal constant i64 65536, align 8
@.str.5 = private unnamed_addr constant [44 x i8] c"Can't allocate data for bzip2 decompression\00", align 1
@.str.6 = private unnamed_addr constant [24 x i8] c"invalid setup parameter\00", align 1
@.str.7 = private unnamed_addr constant [14 x i8] c"out of memory\00", align 1
@.str.8 = private unnamed_addr constant [21 x i8] c"mis-compiled library\00", align 1
@.str.9 = private unnamed_addr constant [45 x i8] c"Internal error initializing decompressor%s%s\00", align 1
@.str.10 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.11 = private unnamed_addr constant [3 x i8] c": \00", align 1
@.str.12 = private unnamed_addr constant [22 x i8] c"truncated bzip2 input\00", align 1
@.str.13 = private unnamed_addr constant [32 x i8] c"Failed to clean up decompressor\00", align 1
@.str.14 = private unnamed_addr constant [26 x i8] c"bzip decompression failed\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_read_support_compression_bzip2(%struct.archive* %a) #0 !dbg !325 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !338, metadata !339), !dbg !340
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !341
  %call = call i32 @archive_read_support_filter_bzip2(%struct.archive* %0), !dbg !342
  ret i32 %call, !dbg !343
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define i32 @archive_read_support_filter_bzip2(%struct.archive* %_a) #0 !dbg !326 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_read*, align 8
  %reader = alloca %struct.archive_read_filter_bidder*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !344, metadata !339), !dbg !345
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !346, metadata !339), !dbg !347
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !348
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !349
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !347
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter_bidder** %reader, metadata !350, metadata !339), !dbg !351
  br label %do.body, !dbg !352

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !353, metadata !339), !dbg !355
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !356
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 14594245, i32 1, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str, i32 0, i32 0)), !dbg !356
  store i32 %call, i32* %magic_test, align 4, !dbg !356
  %3 = load i32, i32* %magic_test, align 4, !dbg !356
  %cmp = icmp eq i32 %3, -30, !dbg !356
  br i1 %cmp, label %if.then, label %if.end, !dbg !356

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !358
  br label %return, !dbg !358

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !361

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !363
  %call1 = call i32 @__archive_read_get_bidder(%struct.archive_read* %4, %struct.archive_read_filter_bidder** %reader), !dbg !365
  %cmp2 = icmp ne i32 %call1, 0, !dbg !366
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !367

if.then3:                                         ; preds = %do.end
  store i32 -30, i32* %retval, align 4, !dbg !368
  br label %return, !dbg !368

if.end4:                                          ; preds = %do.end
  %5 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %reader, align 8, !dbg !369
  %data = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %5, i32 0, i32 0, !dbg !370
  store i8* null, i8** %data, align 8, !dbg !371
  %6 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %reader, align 8, !dbg !372
  %name = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %6, i32 0, i32 1, !dbg !373
  store i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i8** %name, align 8, !dbg !374
  %7 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %reader, align 8, !dbg !375
  %bid = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %7, i32 0, i32 2, !dbg !376
  store i32 (%struct.archive_read_filter_bidder*, %struct.archive_read_filter*)* @bzip2_reader_bid, i32 (%struct.archive_read_filter_bidder*, %struct.archive_read_filter*)** %bid, align 8, !dbg !377
  %8 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %reader, align 8, !dbg !378
  %init = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %8, i32 0, i32 3, !dbg !379
  store i32 (%struct.archive_read_filter*)* @bzip2_reader_init, i32 (%struct.archive_read_filter*)** %init, align 8, !dbg !380
  %9 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %reader, align 8, !dbg !381
  %options = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %9, i32 0, i32 4, !dbg !382
  store i32 (%struct.archive_read_filter_bidder*, i8*, i8*)* null, i32 (%struct.archive_read_filter_bidder*, i8*, i8*)** %options, align 8, !dbg !383
  %10 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %reader, align 8, !dbg !384
  %free = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %10, i32 0, i32 5, !dbg !385
  store i32 (%struct.archive_read_filter_bidder*)* @bzip2_reader_free, i32 (%struct.archive_read_filter_bidder*)** %free, align 8, !dbg !386
  store i32 0, i32* %retval, align 4, !dbg !387
  br label %return, !dbg !387

return:                                           ; preds = %if.end4, %if.then3, %if.then
  %11 = load i32, i32* %retval, align 4, !dbg !388
  ret i32 %11, !dbg !388
}

declare i32 @__archive_check_magic(%struct.archive*, i32, i32, i8*) #2

declare i32 @__archive_read_get_bidder(%struct.archive_read*, %struct.archive_read_filter_bidder**) #2

; Function Attrs: nounwind uwtable
define internal i32 @bzip2_reader_bid(%struct.archive_read_filter_bidder* %self, %struct.archive_read_filter* %filter) #0 !dbg !328 {
entry:
  %retval = alloca i32, align 4
  %self.addr = alloca %struct.archive_read_filter_bidder*, align 8
  %filter.addr = alloca %struct.archive_read_filter*, align 8
  %buffer = alloca i8*, align 8
  %avail = alloca i64, align 8
  %bits_checked = alloca i32, align 4
  store %struct.archive_read_filter_bidder* %self, %struct.archive_read_filter_bidder** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter_bidder** %self.addr, metadata !389, metadata !339), !dbg !390
  store %struct.archive_read_filter* %filter, %struct.archive_read_filter** %filter.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %filter.addr, metadata !391, metadata !339), !dbg !392
  call void @llvm.dbg.declare(metadata i8** %buffer, metadata !393, metadata !339), !dbg !396
  call void @llvm.dbg.declare(metadata i64* %avail, metadata !397, metadata !339), !dbg !398
  call void @llvm.dbg.declare(metadata i32* %bits_checked, metadata !399, metadata !339), !dbg !400
  %0 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %self.addr, align 8, !dbg !401
  %1 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !402
  %call = call i8* @__archive_read_filter_ahead(%struct.archive_read_filter* %1, i64 14, i64* %avail), !dbg !403
  store i8* %call, i8** %buffer, align 8, !dbg !404
  %2 = load i8*, i8** %buffer, align 8, !dbg !405
  %cmp = icmp eq i8* %2, null, !dbg !407
  br i1 %cmp, label %if.then, label %if.end, !dbg !408

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !409
  br label %return, !dbg !409

if.end:                                           ; preds = %entry
  store i32 0, i32* %bits_checked, align 4, !dbg !410
  %3 = load i8*, i8** %buffer, align 8, !dbg !411
  %call1 = call i32 @memcmp(i8* %3, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.2, i32 0, i32 0), i64 3) #5, !dbg !413
  %cmp2 = icmp ne i32 %call1, 0, !dbg !414
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !415

if.then3:                                         ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !416
  br label %return, !dbg !416

if.end4:                                          ; preds = %if.end
  %4 = load i32, i32* %bits_checked, align 4, !dbg !417
  %add = add nsw i32 %4, 24, !dbg !417
  store i32 %add, i32* %bits_checked, align 4, !dbg !417
  %5 = load i8*, i8** %buffer, align 8, !dbg !418
  %arrayidx = getelementptr inbounds i8, i8* %5, i64 3, !dbg !418
  %6 = load i8, i8* %arrayidx, align 1, !dbg !418
  %conv = zext i8 %6 to i32, !dbg !418
  %cmp5 = icmp slt i32 %conv, 49, !dbg !420
  br i1 %cmp5, label %if.then11, label %lor.lhs.false, !dbg !421

lor.lhs.false:                                    ; preds = %if.end4
  %7 = load i8*, i8** %buffer, align 8, !dbg !422
  %arrayidx7 = getelementptr inbounds i8, i8* %7, i64 3, !dbg !422
  %8 = load i8, i8* %arrayidx7, align 1, !dbg !422
  %conv8 = zext i8 %8 to i32, !dbg !422
  %cmp9 = icmp sgt i32 %conv8, 57, !dbg !424
  br i1 %cmp9, label %if.then11, label %if.end12, !dbg !425

if.then11:                                        ; preds = %lor.lhs.false, %if.end4
  store i32 0, i32* %retval, align 4, !dbg !426
  br label %return, !dbg !426

if.end12:                                         ; preds = %lor.lhs.false
  %9 = load i32, i32* %bits_checked, align 4, !dbg !427
  %add13 = add nsw i32 %9, 5, !dbg !427
  store i32 %add13, i32* %bits_checked, align 4, !dbg !427
  %10 = load i8*, i8** %buffer, align 8, !dbg !428
  %add.ptr = getelementptr inbounds i8, i8* %10, i64 4, !dbg !430
  %call14 = call i32 @memcmp(i8* %add.ptr, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.3, i32 0, i32 0), i64 6) #5, !dbg !431
  %cmp15 = icmp eq i32 %call14, 0, !dbg !432
  br i1 %cmp15, label %if.then17, label %if.else, !dbg !433

if.then17:                                        ; preds = %if.end12
  %11 = load i32, i32* %bits_checked, align 4, !dbg !434
  %add18 = add nsw i32 %11, 48, !dbg !434
  store i32 %add18, i32* %bits_checked, align 4, !dbg !434
  br label %if.end27, !dbg !435

if.else:                                          ; preds = %if.end12
  %12 = load i8*, i8** %buffer, align 8, !dbg !436
  %add.ptr19 = getelementptr inbounds i8, i8* %12, i64 4, !dbg !438
  %call20 = call i32 @memcmp(i8* %add.ptr19, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.4, i32 0, i32 0), i64 6) #5, !dbg !439
  %cmp21 = icmp eq i32 %call20, 0, !dbg !440
  br i1 %cmp21, label %if.then23, label %if.else25, !dbg !441

if.then23:                                        ; preds = %if.else
  %13 = load i32, i32* %bits_checked, align 4, !dbg !442
  %add24 = add nsw i32 %13, 48, !dbg !442
  store i32 %add24, i32* %bits_checked, align 4, !dbg !442
  br label %if.end26, !dbg !443

if.else25:                                        ; preds = %if.else
  store i32 0, i32* %retval, align 4, !dbg !444
  br label %return, !dbg !444

if.end26:                                         ; preds = %if.then23
  br label %if.end27

if.end27:                                         ; preds = %if.end26, %if.then17
  %14 = load i32, i32* %bits_checked, align 4, !dbg !445
  store i32 %14, i32* %retval, align 4, !dbg !446
  br label %return, !dbg !446

return:                                           ; preds = %if.end27, %if.else25, %if.then11, %if.then3, %if.then
  %15 = load i32, i32* %retval, align 4, !dbg !447
  ret i32 %15, !dbg !447
}

; Function Attrs: nounwind uwtable
define internal i32 @bzip2_reader_init(%struct.archive_read_filter* %self) #0 !dbg !329 {
entry:
  %retval = alloca i32, align 4
  %self.addr = alloca %struct.archive_read_filter*, align 8
  %out_block = alloca i8*, align 8
  %state = alloca %struct.private_data*, align 8
  store %struct.archive_read_filter* %self, %struct.archive_read_filter** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %self.addr, metadata !448, metadata !339), !dbg !449
  call void @llvm.dbg.declare(metadata i8** %out_block, metadata !450, metadata !339), !dbg !451
  call void @llvm.dbg.declare(metadata %struct.private_data** %state, metadata !452, metadata !339), !dbg !453
  %0 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !454
  %code = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %0, i32 0, i32 12, !dbg !455
  store i32 2, i32* %code, align 8, !dbg !456
  %1 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !457
  %name = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %1, i32 0, i32 11, !dbg !458
  store i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i8** %name, align 8, !dbg !459
  %call = call noalias i8* @calloc(i64 104, i64 1) #6, !dbg !460
  %2 = bitcast i8* %call to %struct.private_data*, !dbg !461
  store %struct.private_data* %2, %struct.private_data** %state, align 8, !dbg !462
  %call1 = call noalias i8* @malloc(i64 65536) #6, !dbg !463
  store i8* %call1, i8** %out_block, align 8, !dbg !464
  %3 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !465
  %cmp = icmp eq %struct.private_data* %3, null, !dbg !467
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !468

lor.lhs.false:                                    ; preds = %entry
  %4 = load i8*, i8** %out_block, align 8, !dbg !469
  %cmp2 = icmp eq i8* %4, null, !dbg !471
  br i1 %cmp2, label %if.then, label %if.end, !dbg !472

if.then:                                          ; preds = %lor.lhs.false, %entry
  %5 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !473
  %archive = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %5, i32 0, i32 3, !dbg !475
  %6 = load %struct.archive_read*, %struct.archive_read** %archive, align 8, !dbg !475
  %archive3 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %6, i32 0, i32 0, !dbg !476
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive3, i32 12, i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.5, i32 0, i32 0)), !dbg !477
  %7 = load i8*, i8** %out_block, align 8, !dbg !478
  call void @free(i8* %7) #6, !dbg !479
  %8 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !480
  %9 = bitcast %struct.private_data* %8 to i8*, !dbg !480
  call void @free(i8* %9) #6, !dbg !481
  store i32 -30, i32* %retval, align 4, !dbg !482
  br label %return, !dbg !482

if.end:                                           ; preds = %lor.lhs.false
  %10 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !483
  %11 = bitcast %struct.private_data* %10 to i8*, !dbg !483
  %12 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !484
  %data = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %12, i32 0, i32 10, !dbg !485
  store i8* %11, i8** %data, align 8, !dbg !486
  %13 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !487
  %out_block_size = getelementptr inbounds %struct.private_data, %struct.private_data* %13, i32 0, i32 2, !dbg !488
  store i64 65536, i64* %out_block_size, align 8, !dbg !489
  %14 = load i8*, i8** %out_block, align 8, !dbg !490
  %15 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !491
  %out_block4 = getelementptr inbounds %struct.private_data, %struct.private_data* %15, i32 0, i32 1, !dbg !492
  store i8* %14, i8** %out_block4, align 8, !dbg !493
  %16 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !494
  %read = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %16, i32 0, i32 5, !dbg !495
  store i64 (%struct.archive_read_filter*, i8**)* @bzip2_filter_read, i64 (%struct.archive_read_filter*, i8**)** %read, align 8, !dbg !496
  %17 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !497
  %skip = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %17, i32 0, i32 6, !dbg !498
  store i64 (%struct.archive_read_filter*, i64)* null, i64 (%struct.archive_read_filter*, i64)** %skip, align 8, !dbg !499
  %18 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !500
  %close = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %18, i32 0, i32 8, !dbg !501
  store i32 (%struct.archive_read_filter*)* @bzip2_filter_close, i32 (%struct.archive_read_filter*)** %close, align 8, !dbg !502
  store i32 0, i32* %retval, align 4, !dbg !503
  br label %return, !dbg !503

return:                                           ; preds = %if.end, %if.then
  %19 = load i32, i32* %retval, align 4, !dbg !504
  ret i32 %19, !dbg !504
}

; Function Attrs: nounwind uwtable
define internal i32 @bzip2_reader_free(%struct.archive_read_filter_bidder* %self) #0 !dbg !327 {
entry:
  %self.addr = alloca %struct.archive_read_filter_bidder*, align 8
  store %struct.archive_read_filter_bidder* %self, %struct.archive_read_filter_bidder** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter_bidder** %self.addr, metadata !505, metadata !339), !dbg !506
  %0 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %self.addr, align 8, !dbg !507
  ret i32 0, !dbg !508
}

declare i8* @__archive_read_filter_ahead(%struct.archive_read_filter*, i64, i64*) #2

; Function Attrs: nounwind readonly
declare i32 @memcmp(i8*, i8*, i64) #3

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #4

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #4

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

; Function Attrs: nounwind
declare void @free(i8*) #4

; Function Attrs: nounwind uwtable
define internal i64 @bzip2_filter_read(%struct.archive_read_filter* %self, i8** %p) #0 !dbg !330 {
entry:
  %retval = alloca i64, align 8
  %self.addr = alloca %struct.archive_read_filter*, align 8
  %p.addr = alloca i8**, align 8
  %state = alloca %struct.private_data*, align 8
  %decompressed = alloca i64, align 8
  %read_buf = alloca i8*, align 8
  %ret = alloca i64, align 8
  %detail = alloca i8*, align 8
  %err = alloca i32, align 4
  store %struct.archive_read_filter* %self, %struct.archive_read_filter** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %self.addr, metadata !509, metadata !339), !dbg !510
  store i8** %p, i8*** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %p.addr, metadata !511, metadata !339), !dbg !512
  call void @llvm.dbg.declare(metadata %struct.private_data** %state, metadata !513, metadata !339), !dbg !514
  call void @llvm.dbg.declare(metadata i64* %decompressed, metadata !515, metadata !339), !dbg !516
  call void @llvm.dbg.declare(metadata i8** %read_buf, metadata !517, metadata !339), !dbg !518
  call void @llvm.dbg.declare(metadata i64* %ret, metadata !519, metadata !339), !dbg !520
  %0 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !521
  %data = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %0, i32 0, i32 10, !dbg !522
  %1 = load i8*, i8** %data, align 8, !dbg !522
  %2 = bitcast i8* %1 to %struct.private_data*, !dbg !523
  store %struct.private_data* %2, %struct.private_data** %state, align 8, !dbg !524
  %3 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !525
  %eof = getelementptr inbounds %struct.private_data, %struct.private_data* %3, i32 0, i32 4, !dbg !527
  %4 = load i8, i8* %eof, align 1, !dbg !527
  %tobool = icmp ne i8 %4, 0, !dbg !525
  br i1 %tobool, label %if.then, label %if.end, !dbg !528

if.then:                                          ; preds = %entry
  %5 = load i8**, i8*** %p.addr, align 8, !dbg !529
  store i8* null, i8** %5, align 8, !dbg !531
  store i64 0, i64* %retval, align 8, !dbg !532
  br label %return, !dbg !532

if.end:                                           ; preds = %entry
  %6 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !533
  %out_block = getelementptr inbounds %struct.private_data, %struct.private_data* %6, i32 0, i32 1, !dbg !534
  %7 = load i8*, i8** %out_block, align 8, !dbg !534
  %8 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !535
  %stream = getelementptr inbounds %struct.private_data, %struct.private_data* %8, i32 0, i32 0, !dbg !536
  %next_out = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %stream, i32 0, i32 4, !dbg !537
  store i8* %7, i8** %next_out, align 8, !dbg !538
  %9 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !539
  %out_block_size = getelementptr inbounds %struct.private_data, %struct.private_data* %9, i32 0, i32 2, !dbg !540
  %10 = load i64, i64* %out_block_size, align 8, !dbg !540
  %conv = trunc i64 %10 to i32, !dbg !539
  %11 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !541
  %stream1 = getelementptr inbounds %struct.private_data, %struct.private_data* %11, i32 0, i32 0, !dbg !542
  %avail_out = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %stream1, i32 0, i32 5, !dbg !543
  store i32 %conv, i32* %avail_out, align 8, !dbg !544
  br label %for.cond, !dbg !545

for.cond:                                         ; preds = %sw.epilog91, %if.end
  %12 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !546
  %valid = getelementptr inbounds %struct.private_data, %struct.private_data* %12, i32 0, i32 3, !dbg !551
  %13 = load i8, i8* %valid, align 8, !dbg !551
  %tobool2 = icmp ne i8 %13, 0, !dbg !546
  br i1 %tobool2, label %if.end32, label %if.then3, !dbg !552

if.then3:                                         ; preds = %for.cond
  %14 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !553
  %bidder = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %14, i32 0, i32 1, !dbg !556
  %15 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !556
  %16 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !557
  %upstream = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %16, i32 0, i32 2, !dbg !558
  %17 = load %struct.archive_read_filter*, %struct.archive_read_filter** %upstream, align 8, !dbg !558
  %call = call i32 @bzip2_reader_bid(%struct.archive_read_filter_bidder* %15, %struct.archive_read_filter* %17), !dbg !559
  %cmp = icmp eq i32 %call, 0, !dbg !560
  br i1 %cmp, label %if.then5, label %if.end11, !dbg !561

if.then5:                                         ; preds = %if.then3
  %18 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !562
  %eof6 = getelementptr inbounds %struct.private_data, %struct.private_data* %18, i32 0, i32 4, !dbg !564
  store i8 1, i8* %eof6, align 1, !dbg !565
  %19 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !566
  %out_block7 = getelementptr inbounds %struct.private_data, %struct.private_data* %19, i32 0, i32 1, !dbg !567
  %20 = load i8*, i8** %out_block7, align 8, !dbg !567
  %21 = load i8**, i8*** %p.addr, align 8, !dbg !568
  store i8* %20, i8** %21, align 8, !dbg !569
  %22 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !570
  %stream8 = getelementptr inbounds %struct.private_data, %struct.private_data* %22, i32 0, i32 0, !dbg !571
  %next_out9 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %stream8, i32 0, i32 4, !dbg !572
  %23 = load i8*, i8** %next_out9, align 8, !dbg !572
  %24 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !573
  %out_block10 = getelementptr inbounds %struct.private_data, %struct.private_data* %24, i32 0, i32 1, !dbg !574
  %25 = load i8*, i8** %out_block10, align 8, !dbg !574
  %sub.ptr.lhs.cast = ptrtoint i8* %23 to i64, !dbg !575
  %sub.ptr.rhs.cast = ptrtoint i8* %25 to i64, !dbg !575
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !575
  store i64 %sub.ptr.sub, i64* %decompressed, align 8, !dbg !576
  %26 = load i64, i64* %decompressed, align 8, !dbg !577
  store i64 %26, i64* %retval, align 8, !dbg !578
  br label %return, !dbg !578

if.end11:                                         ; preds = %if.then3
  %27 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !579
  %stream12 = getelementptr inbounds %struct.private_data, %struct.private_data* %27, i32 0, i32 0, !dbg !580
  %call13 = call i32 @BZ2_bzDecompressInit(%struct.bz_stream* %stream12, i32 0, i32 0), !dbg !581
  %conv14 = sext i32 %call13 to i64, !dbg !581
  store i64 %conv14, i64* %ret, align 8, !dbg !582
  %28 = load i64, i64* %ret, align 8, !dbg !583
  %cmp15 = icmp eq i64 %28, -3, !dbg !585
  br i1 %cmp15, label %if.then17, label %if.end21, !dbg !586

if.then17:                                        ; preds = %if.end11
  %29 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !587
  %stream18 = getelementptr inbounds %struct.private_data, %struct.private_data* %29, i32 0, i32 0, !dbg !588
  %call19 = call i32 @BZ2_bzDecompressInit(%struct.bz_stream* %stream18, i32 0, i32 1), !dbg !589
  %conv20 = sext i32 %call19 to i64, !dbg !589
  store i64 %conv20, i64* %ret, align 8, !dbg !590
  br label %if.end21, !dbg !591

if.end21:                                         ; preds = %if.then17, %if.end11
  %30 = load i64, i64* %ret, align 8, !dbg !592
  %cmp22 = icmp ne i64 %30, 0, !dbg !594
  br i1 %cmp22, label %if.then24, label %if.end30, !dbg !595

if.then24:                                        ; preds = %if.end21
  call void @llvm.dbg.declare(metadata i8** %detail, metadata !596, metadata !339), !dbg !598
  store i8* null, i8** %detail, align 8, !dbg !598
  call void @llvm.dbg.declare(metadata i32* %err, metadata !599, metadata !339), !dbg !600
  store i32 -1, i32* %err, align 4, !dbg !600
  %31 = load i64, i64* %ret, align 8, !dbg !601
  switch i64 %31, label %sw.epilog [
    i64 -2, label %sw.bb
    i64 -3, label %sw.bb25
    i64 -9, label %sw.bb26
  ], !dbg !602

sw.bb:                                            ; preds = %if.then24
  store i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.6, i32 0, i32 0), i8** %detail, align 8, !dbg !603
  br label %sw.epilog, !dbg !605

sw.bb25:                                          ; preds = %if.then24
  store i32 12, i32* %err, align 4, !dbg !606
  store i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.7, i32 0, i32 0), i8** %detail, align 8, !dbg !607
  br label %sw.epilog, !dbg !608

sw.bb26:                                          ; preds = %if.then24
  store i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.8, i32 0, i32 0), i8** %detail, align 8, !dbg !609
  br label %sw.epilog, !dbg !610

sw.epilog:                                        ; preds = %if.then24, %sw.bb26, %sw.bb25, %sw.bb
  %32 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !611
  %archive = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %32, i32 0, i32 3, !dbg !612
  %33 = load %struct.archive_read*, %struct.archive_read** %archive, align 8, !dbg !612
  %archive27 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %33, i32 0, i32 0, !dbg !613
  %34 = load i32, i32* %err, align 4, !dbg !614
  %35 = load i8*, i8** %detail, align 8, !dbg !615
  %cmp28 = icmp eq i8* %35, null, !dbg !616
  %cond = select i1 %cmp28, i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.10, i32 0, i32 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.11, i32 0, i32 0), !dbg !615
  %36 = load i8*, i8** %detail, align 8, !dbg !617
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive27, i32 %34, i8* getelementptr inbounds ([45 x i8], [45 x i8]* @.str.9, i32 0, i32 0), i8* %cond, i8* %36), !dbg !618
  store i64 -30, i64* %retval, align 8, !dbg !619
  br label %return, !dbg !619

if.end30:                                         ; preds = %if.end21
  %37 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !620
  %valid31 = getelementptr inbounds %struct.private_data, %struct.private_data* %37, i32 0, i32 3, !dbg !621
  store i8 1, i8* %valid31, align 8, !dbg !622
  br label %if.end32, !dbg !623

if.end32:                                         ; preds = %if.end30, %for.cond
  %38 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !624
  %upstream33 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %38, i32 0, i32 2, !dbg !625
  %39 = load %struct.archive_read_filter*, %struct.archive_read_filter** %upstream33, align 8, !dbg !625
  %call34 = call i8* @__archive_read_filter_ahead(%struct.archive_read_filter* %39, i64 1, i64* %ret), !dbg !626
  store i8* %call34, i8** %read_buf, align 8, !dbg !627
  %40 = load i8*, i8** %read_buf, align 8, !dbg !628
  %cmp35 = icmp eq i8* %40, null, !dbg !630
  br i1 %cmp35, label %if.then37, label %if.end40, !dbg !631

if.then37:                                        ; preds = %if.end32
  %41 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !632
  %archive38 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %41, i32 0, i32 3, !dbg !634
  %42 = load %struct.archive_read*, %struct.archive_read** %archive38, align 8, !dbg !634
  %archive39 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %42, i32 0, i32 0, !dbg !635
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive39, i32 -1, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.12, i32 0, i32 0)), !dbg !636
  store i64 -30, i64* %retval, align 8, !dbg !637
  br label %return, !dbg !637

if.end40:                                         ; preds = %if.end32
  %43 = load i8*, i8** %read_buf, align 8, !dbg !638
  %44 = ptrtoint i8* %43 to i64, !dbg !639
  %45 = inttoptr i64 %44 to i8*, !dbg !640
  %46 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !641
  %stream41 = getelementptr inbounds %struct.private_data, %struct.private_data* %46, i32 0, i32 0, !dbg !642
  %next_in = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %stream41, i32 0, i32 0, !dbg !643
  store i8* %45, i8** %next_in, align 8, !dbg !644
  %47 = load i64, i64* %ret, align 8, !dbg !645
  %conv42 = trunc i64 %47 to i32, !dbg !645
  %48 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !646
  %stream43 = getelementptr inbounds %struct.private_data, %struct.private_data* %48, i32 0, i32 0, !dbg !647
  %avail_in = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %stream43, i32 0, i32 1, !dbg !648
  store i32 %conv42, i32* %avail_in, align 8, !dbg !649
  %49 = load i64, i64* %ret, align 8, !dbg !650
  %cmp44 = icmp eq i64 %49, 0, !dbg !652
  br i1 %cmp44, label %if.then46, label %if.end55, !dbg !653

if.then46:                                        ; preds = %if.end40
  %50 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !654
  %eof47 = getelementptr inbounds %struct.private_data, %struct.private_data* %50, i32 0, i32 4, !dbg !656
  store i8 1, i8* %eof47, align 1, !dbg !657
  %51 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !658
  %out_block48 = getelementptr inbounds %struct.private_data, %struct.private_data* %51, i32 0, i32 1, !dbg !659
  %52 = load i8*, i8** %out_block48, align 8, !dbg !659
  %53 = load i8**, i8*** %p.addr, align 8, !dbg !660
  store i8* %52, i8** %53, align 8, !dbg !661
  %54 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !662
  %stream49 = getelementptr inbounds %struct.private_data, %struct.private_data* %54, i32 0, i32 0, !dbg !663
  %next_out50 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %stream49, i32 0, i32 4, !dbg !664
  %55 = load i8*, i8** %next_out50, align 8, !dbg !664
  %56 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !665
  %out_block51 = getelementptr inbounds %struct.private_data, %struct.private_data* %56, i32 0, i32 1, !dbg !666
  %57 = load i8*, i8** %out_block51, align 8, !dbg !666
  %sub.ptr.lhs.cast52 = ptrtoint i8* %55 to i64, !dbg !667
  %sub.ptr.rhs.cast53 = ptrtoint i8* %57 to i64, !dbg !667
  %sub.ptr.sub54 = sub i64 %sub.ptr.lhs.cast52, %sub.ptr.rhs.cast53, !dbg !667
  store i64 %sub.ptr.sub54, i64* %decompressed, align 8, !dbg !668
  %58 = load i64, i64* %decompressed, align 8, !dbg !669
  store i64 %58, i64* %retval, align 8, !dbg !670
  br label %return, !dbg !670

if.end55:                                         ; preds = %if.end40
  %59 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !671
  %stream56 = getelementptr inbounds %struct.private_data, %struct.private_data* %59, i32 0, i32 0, !dbg !672
  %call57 = call i32 @BZ2_bzDecompress(%struct.bz_stream* %stream56), !dbg !673
  %conv58 = sext i32 %call57 to i64, !dbg !673
  store i64 %conv58, i64* %ret, align 8, !dbg !674
  %60 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !675
  %upstream59 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %60, i32 0, i32 2, !dbg !676
  %61 = load %struct.archive_read_filter*, %struct.archive_read_filter** %upstream59, align 8, !dbg !676
  %62 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !677
  %stream60 = getelementptr inbounds %struct.private_data, %struct.private_data* %62, i32 0, i32 0, !dbg !678
  %next_in61 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %stream60, i32 0, i32 0, !dbg !679
  %63 = load i8*, i8** %next_in61, align 8, !dbg !679
  %64 = load i8*, i8** %read_buf, align 8, !dbg !680
  %sub.ptr.lhs.cast62 = ptrtoint i8* %63 to i64, !dbg !681
  %sub.ptr.rhs.cast63 = ptrtoint i8* %64 to i64, !dbg !681
  %sub.ptr.sub64 = sub i64 %sub.ptr.lhs.cast62, %sub.ptr.rhs.cast63, !dbg !681
  %call65 = call i64 @__archive_read_filter_consume(%struct.archive_read_filter* %61, i64 %sub.ptr.sub64), !dbg !682
  %65 = load i64, i64* %ret, align 8, !dbg !683
  switch i64 %65, label %sw.default88 [
    i64 4, label %sw.bb66
    i64 0, label %sw.bb74
  ], !dbg !684

sw.bb66:                                          ; preds = %if.end55
  %66 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !685
  %stream67 = getelementptr inbounds %struct.private_data, %struct.private_data* %66, i32 0, i32 0, !dbg !687
  %call68 = call i32 @BZ2_bzDecompressEnd(%struct.bz_stream* %stream67), !dbg !688
  switch i32 %call68, label %sw.default [
    i32 0, label %sw.bb69
  ], !dbg !689

sw.bb69:                                          ; preds = %sw.bb66
  br label %sw.epilog72, !dbg !690

sw.default:                                       ; preds = %sw.bb66
  %67 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !692
  %archive70 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %67, i32 0, i32 3, !dbg !693
  %68 = load %struct.archive_read*, %struct.archive_read** %archive70, align 8, !dbg !693
  %archive71 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %68, i32 0, i32 0, !dbg !694
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive71, i32 -1, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.13, i32 0, i32 0)), !dbg !695
  store i64 -30, i64* %retval, align 8, !dbg !696
  br label %return, !dbg !696

sw.epilog72:                                      ; preds = %sw.bb69
  %69 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !697
  %valid73 = getelementptr inbounds %struct.private_data, %struct.private_data* %69, i32 0, i32 3, !dbg !698
  store i8 0, i8* %valid73, align 8, !dbg !699
  br label %sw.bb74, !dbg !697

sw.bb74:                                          ; preds = %if.end55, %sw.epilog72
  %70 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !700
  %stream75 = getelementptr inbounds %struct.private_data, %struct.private_data* %70, i32 0, i32 0, !dbg !702
  %avail_out76 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %stream75, i32 0, i32 5, !dbg !703
  %71 = load i32, i32* %avail_out76, align 8, !dbg !703
  %cmp77 = icmp eq i32 %71, 0, !dbg !704
  br i1 %cmp77, label %if.then79, label %if.end87, !dbg !705

if.then79:                                        ; preds = %sw.bb74
  %72 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !706
  %out_block80 = getelementptr inbounds %struct.private_data, %struct.private_data* %72, i32 0, i32 1, !dbg !708
  %73 = load i8*, i8** %out_block80, align 8, !dbg !708
  %74 = load i8**, i8*** %p.addr, align 8, !dbg !709
  store i8* %73, i8** %74, align 8, !dbg !710
  %75 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !711
  %stream81 = getelementptr inbounds %struct.private_data, %struct.private_data* %75, i32 0, i32 0, !dbg !712
  %next_out82 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %stream81, i32 0, i32 4, !dbg !713
  %76 = load i8*, i8** %next_out82, align 8, !dbg !713
  %77 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !714
  %out_block83 = getelementptr inbounds %struct.private_data, %struct.private_data* %77, i32 0, i32 1, !dbg !715
  %78 = load i8*, i8** %out_block83, align 8, !dbg !715
  %sub.ptr.lhs.cast84 = ptrtoint i8* %76 to i64, !dbg !716
  %sub.ptr.rhs.cast85 = ptrtoint i8* %78 to i64, !dbg !716
  %sub.ptr.sub86 = sub i64 %sub.ptr.lhs.cast84, %sub.ptr.rhs.cast85, !dbg !716
  store i64 %sub.ptr.sub86, i64* %decompressed, align 8, !dbg !717
  %79 = load i64, i64* %decompressed, align 8, !dbg !718
  store i64 %79, i64* %retval, align 8, !dbg !719
  br label %return, !dbg !719

if.end87:                                         ; preds = %sw.bb74
  br label %sw.epilog91, !dbg !720

sw.default88:                                     ; preds = %if.end55
  %80 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !721
  %archive89 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %80, i32 0, i32 3, !dbg !722
  %81 = load %struct.archive_read*, %struct.archive_read** %archive89, align 8, !dbg !722
  %archive90 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %81, i32 0, i32 0, !dbg !723
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive90, i32 -1, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.14, i32 0, i32 0)), !dbg !724
  store i64 -30, i64* %retval, align 8, !dbg !725
  br label %return, !dbg !725

sw.epilog91:                                      ; preds = %if.end87
  br label %for.cond, !dbg !726

return:                                           ; preds = %sw.default88, %if.then79, %sw.default, %if.then46, %if.then37, %sw.epilog, %if.then5, %if.then
  %82 = load i64, i64* %retval, align 8, !dbg !728
  ret i64 %82, !dbg !728
}

; Function Attrs: nounwind uwtable
define internal i32 @bzip2_filter_close(%struct.archive_read_filter* %self) #0 !dbg !331 {
entry:
  %self.addr = alloca %struct.archive_read_filter*, align 8
  %state = alloca %struct.private_data*, align 8
  %ret = alloca i32, align 4
  store %struct.archive_read_filter* %self, %struct.archive_read_filter** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %self.addr, metadata !729, metadata !339), !dbg !730
  call void @llvm.dbg.declare(metadata %struct.private_data** %state, metadata !731, metadata !339), !dbg !732
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !733, metadata !339), !dbg !734
  store i32 0, i32* %ret, align 4, !dbg !734
  %0 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !735
  %data = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %0, i32 0, i32 10, !dbg !736
  %1 = load i8*, i8** %data, align 8, !dbg !736
  %2 = bitcast i8* %1 to %struct.private_data*, !dbg !737
  store %struct.private_data* %2, %struct.private_data** %state, align 8, !dbg !738
  %3 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !739
  %valid = getelementptr inbounds %struct.private_data, %struct.private_data* %3, i32 0, i32 3, !dbg !741
  %4 = load i8, i8* %valid, align 8, !dbg !741
  %tobool = icmp ne i8 %4, 0, !dbg !739
  br i1 %tobool, label %if.then, label %if.end, !dbg !742

if.then:                                          ; preds = %entry
  %5 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !743
  %stream = getelementptr inbounds %struct.private_data, %struct.private_data* %5, i32 0, i32 0, !dbg !745
  %call = call i32 @BZ2_bzDecompressEnd(%struct.bz_stream* %stream), !dbg !746
  switch i32 %call, label %sw.default [
    i32 0, label %sw.bb
  ], !dbg !747

sw.bb:                                            ; preds = %if.then
  br label %sw.epilog, !dbg !748

sw.default:                                       ; preds = %if.then
  %6 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !750
  %archive = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %6, i32 0, i32 3, !dbg !751
  %7 = load %struct.archive_read*, %struct.archive_read** %archive, align 8, !dbg !751
  %archive1 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %7, i32 0, i32 0, !dbg !752
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive1, i32 -1, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.13, i32 0, i32 0)), !dbg !753
  store i32 -30, i32* %ret, align 4, !dbg !754
  br label %sw.epilog, !dbg !755

sw.epilog:                                        ; preds = %sw.default, %sw.bb
  %8 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !756
  %valid2 = getelementptr inbounds %struct.private_data, %struct.private_data* %8, i32 0, i32 3, !dbg !757
  store i8 0, i8* %valid2, align 8, !dbg !758
  br label %if.end, !dbg !759

if.end:                                           ; preds = %sw.epilog, %entry
  %9 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !760
  %out_block = getelementptr inbounds %struct.private_data, %struct.private_data* %9, i32 0, i32 1, !dbg !761
  %10 = load i8*, i8** %out_block, align 8, !dbg !761
  call void @free(i8* %10) #6, !dbg !762
  %11 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !763
  %12 = bitcast %struct.private_data* %11 to i8*, !dbg !763
  call void @free(i8* %12) #6, !dbg !764
  %13 = load i32, i32* %ret, align 4, !dbg !765
  ret i32 %13, !dbg !766
}

declare i32 @BZ2_bzDecompressInit(%struct.bz_stream*, i32, i32) #2

declare i32 @BZ2_bzDecompress(%struct.bz_stream*) #2

declare i64 @__archive_read_filter_consume(%struct.archive_read_filter*, i64) #2

declare i32 @BZ2_bzDecompressEnd(%struct.bz_stream*) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind readonly }
attributes #6 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!335, !336}
!llvm.ident = !{!337}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !324, globals: !332)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_support_filter_bzip2.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !122, !291, !321, !95, !323}
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
!38 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !39, line: 102, baseType: !40)
!39 = !DIFile(filename: "/usr/include/stdio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
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
!292 = !DICompositeType(tag: DW_TAG_structure_type, name: "private_data", file: !1, line: 52, size: 832, align: 64, elements: !293)
!293 = !{!294, !317, !318, !319, !320}
!294 = !DIDerivedType(tag: DW_TAG_member, name: "stream", scope: !292, file: !1, line: 53, baseType: !295, size: 640, align: 64)
!295 = !DIDerivedType(tag: DW_TAG_typedef, name: "bz_stream", file: !296, line: 66, baseType: !297)
!296 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmbzip2/bzlib.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!297 = !DICompositeType(tag: DW_TAG_structure_type, file: !296, line: 49, size: 640, align: 64, elements: !298)
!298 = !{!299, !300, !301, !302, !303, !304, !305, !306, !307, !308, !312, !316}
!299 = !DIDerivedType(tag: DW_TAG_member, name: "next_in", scope: !297, file: !296, line: 50, baseType: !95, size: 64, align: 64)
!300 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in", scope: !297, file: !296, line: 51, baseType: !13, size: 32, align: 32, offset: 64)
!301 = !DIDerivedType(tag: DW_TAG_member, name: "total_in_lo32", scope: !297, file: !296, line: 52, baseType: !13, size: 32, align: 32, offset: 96)
!302 = !DIDerivedType(tag: DW_TAG_member, name: "total_in_hi32", scope: !297, file: !296, line: 53, baseType: !13, size: 32, align: 32, offset: 128)
!303 = !DIDerivedType(tag: DW_TAG_member, name: "next_out", scope: !297, file: !296, line: 55, baseType: !95, size: 64, align: 64, offset: 192)
!304 = !DIDerivedType(tag: DW_TAG_member, name: "avail_out", scope: !297, file: !296, line: 56, baseType: !13, size: 32, align: 32, offset: 256)
!305 = !DIDerivedType(tag: DW_TAG_member, name: "total_out_lo32", scope: !297, file: !296, line: 57, baseType: !13, size: 32, align: 32, offset: 288)
!306 = !DIDerivedType(tag: DW_TAG_member, name: "total_out_hi32", scope: !297, file: !296, line: 58, baseType: !13, size: 32, align: 32, offset: 320)
!307 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !297, file: !296, line: 60, baseType: !122, size: 64, align: 64, offset: 384)
!308 = !DIDerivedType(tag: DW_TAG_member, name: "bzalloc", scope: !297, file: !296, line: 62, baseType: !309, size: 64, align: 64, offset: 448)
!309 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !310, size: 64, align: 64)
!310 = !DISubroutineType(types: !311)
!311 = !{!122, !122, !23, !23}
!312 = !DIDerivedType(tag: DW_TAG_member, name: "bzfree", scope: !297, file: !296, line: 63, baseType: !313, size: 64, align: 64, offset: 512)
!313 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !314, size: 64, align: 64)
!314 = !DISubroutineType(types: !315)
!315 = !{null, !122, !122}
!316 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !297, file: !296, line: 64, baseType: !122, size: 64, align: 64, offset: 576)
!317 = !DIDerivedType(tag: DW_TAG_member, name: "out_block", scope: !292, file: !1, line: 54, baseType: !95, size: 64, align: 64, offset: 640)
!318 = !DIDerivedType(tag: DW_TAG_member, name: "out_block_size", scope: !292, file: !1, line: 55, baseType: !45, size: 64, align: 64, offset: 704)
!319 = !DIDerivedType(tag: DW_TAG_member, name: "valid", scope: !292, file: !1, line: 56, baseType: !82, size: 8, align: 8, offset: 768)
!320 = !DIDerivedType(tag: DW_TAG_member, name: "eof", scope: !292, file: !1, line: 57, baseType: !82, size: 8, align: 8, offset: 776)
!321 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !322, size: 64, align: 64)
!322 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!323 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !53, line: 122, baseType: !47)
!324 = !{!325, !326, !327, !328, !329, !330, !331}
!325 = distinct !DISubprogram(name: "archive_read_support_compression_bzip2", scope: !1, file: !1, line: 78, type: !21, isLocal: false, isDefinition: true, scopeLine: 79, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!326 = distinct !DISubprogram(name: "archive_read_support_filter_bzip2", scope: !1, file: !1, line: 85, type: !21, isLocal: false, isDefinition: true, scopeLine: 86, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!327 = distinct !DISubprogram(name: "bzip2_reader_free", scope: !1, file: !1, line: 112, type: !218, isLocal: true, isDefinition: true, scopeLine: 112, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!328 = distinct !DISubprogram(name: "bzip2_reader_bid", scope: !1, file: !1, line: 125, type: !166, isLocal: true, isDefinition: true, scopeLine: 126, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!329 = distinct !DISubprogram(name: "bzip2_reader_init", scope: !1, file: !1, line: 190, type: !178, isLocal: true, isDefinition: true, scopeLine: 191, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!330 = distinct !DISubprogram(name: "bzip2_filter_read", scope: !1, file: !1, line: 223, type: !182, isLocal: true, isDefinition: true, scopeLine: 224, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!331 = distinct !DISubprogram(name: "bzip2_filter_close", scope: !1, file: !1, line: 346, type: !178, isLocal: true, isDefinition: true, scopeLine: 347, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!332 = !{!333}
!333 = !DIGlobalVariable(name: "out_block_size", scope: !329, file: !1, line: 192, type: !334, isLocal: true, isDefinition: true, variable: i64* @bzip2_reader_init.out_block_size)
!334 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !45)
!335 = !{i32 2, !"Dwarf Version", i32 4}
!336 = !{i32 2, !"Debug Info Version", i32 3}
!337 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!338 = !DILocalVariable(name: "a", arg: 1, scope: !325, file: !1, line: 78, type: !24)
!339 = !DIExpression()
!340 = !DILocation(line: 78, column: 56, scope: !325)
!341 = !DILocation(line: 80, column: 43, scope: !325)
!342 = !DILocation(line: 80, column: 9, scope: !325)
!343 = !DILocation(line: 80, column: 2, scope: !325)
!344 = !DILocalVariable(name: "_a", arg: 1, scope: !326, file: !1, line: 85, type: !24)
!345 = !DILocation(line: 85, column: 51, scope: !326)
!346 = !DILocalVariable(name: "a", scope: !326, file: !1, line: 87, type: !4)
!347 = !DILocation(line: 87, column: 23, scope: !326)
!348 = !DILocation(line: 87, column: 50, scope: !326)
!349 = !DILocation(line: 87, column: 27, scope: !326)
!350 = !DILocalVariable(name: "reader", scope: !326, file: !1, line: 88, type: !168)
!351 = !DILocation(line: 88, column: 37, scope: !326)
!352 = !DILocation(line: 90, column: 2, scope: !326)
!353 = !DILocalVariable(name: "magic_test", scope: !354, file: !1, line: 90, type: !23)
!354 = distinct !DILexicalBlock(scope: !326, file: !1, line: 90, column: 2)
!355 = !DILocation(line: 90, column: 2, scope: !354)
!356 = !DILocation(line: 90, column: 2, scope: !357)
!357 = !DILexicalBlockFile(scope: !354, file: !1, discriminator: 1)
!358 = !DILocation(line: 90, column: 2, scope: !359)
!359 = !DILexicalBlockFile(scope: !360, file: !1, discriminator: 2)
!360 = distinct !DILexicalBlock(scope: !354, file: !1, line: 90, column: 2)
!361 = !DILocation(line: 90, column: 2, scope: !362)
!362 = !DILexicalBlockFile(scope: !354, file: !1, discriminator: 3)
!363 = !DILocation(line: 93, column: 32, scope: !364)
!364 = distinct !DILexicalBlock(scope: !326, file: !1, line: 93, column: 6)
!365 = !DILocation(line: 93, column: 6, scope: !364)
!366 = !DILocation(line: 93, column: 44, scope: !364)
!367 = !DILocation(line: 93, column: 6, scope: !326)
!368 = !DILocation(line: 94, column: 3, scope: !364)
!369 = !DILocation(line: 96, column: 2, scope: !326)
!370 = !DILocation(line: 96, column: 10, scope: !326)
!371 = !DILocation(line: 96, column: 15, scope: !326)
!372 = !DILocation(line: 97, column: 2, scope: !326)
!373 = !DILocation(line: 97, column: 10, scope: !326)
!374 = !DILocation(line: 97, column: 15, scope: !326)
!375 = !DILocation(line: 98, column: 2, scope: !326)
!376 = !DILocation(line: 98, column: 10, scope: !326)
!377 = !DILocation(line: 98, column: 14, scope: !326)
!378 = !DILocation(line: 99, column: 2, scope: !326)
!379 = !DILocation(line: 99, column: 10, scope: !326)
!380 = !DILocation(line: 99, column: 15, scope: !326)
!381 = !DILocation(line: 100, column: 2, scope: !326)
!382 = !DILocation(line: 100, column: 10, scope: !326)
!383 = !DILocation(line: 100, column: 18, scope: !326)
!384 = !DILocation(line: 101, column: 2, scope: !326)
!385 = !DILocation(line: 101, column: 10, scope: !326)
!386 = !DILocation(line: 101, column: 15, scope: !326)
!387 = !DILocation(line: 103, column: 2, scope: !326)
!388 = !DILocation(line: 109, column: 1, scope: !326)
!389 = !DILocalVariable(name: "self", arg: 1, scope: !328, file: !1, line: 125, type: !168)
!390 = !DILocation(line: 125, column: 53, scope: !328)
!391 = !DILocalVariable(name: "filter", arg: 2, scope: !328, file: !1, line: 125, type: !169)
!392 = !DILocation(line: 125, column: 87, scope: !328)
!393 = !DILocalVariable(name: "buffer", scope: !328, file: !1, line: 127, type: !394)
!394 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !395, size: 64, align: 64)
!395 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !322)
!396 = !DILocation(line: 127, column: 23, scope: !328)
!397 = !DILocalVariable(name: "avail", scope: !328, file: !1, line: 128, type: !38)
!398 = !DILocation(line: 128, column: 10, scope: !328)
!399 = !DILocalVariable(name: "bits_checked", scope: !328, file: !1, line: 129, type: !23)
!400 = !DILocation(line: 129, column: 6, scope: !328)
!401 = !DILocation(line: 131, column: 8, scope: !328)
!402 = !DILocation(line: 134, column: 39, scope: !328)
!403 = !DILocation(line: 134, column: 11, scope: !328)
!404 = !DILocation(line: 134, column: 9, scope: !328)
!405 = !DILocation(line: 135, column: 6, scope: !406)
!406 = distinct !DILexicalBlock(scope: !328, file: !1, line: 135, column: 6)
!407 = !DILocation(line: 135, column: 13, scope: !406)
!408 = !DILocation(line: 135, column: 6, scope: !328)
!409 = !DILocation(line: 136, column: 3, scope: !406)
!410 = !DILocation(line: 139, column: 15, scope: !328)
!411 = !DILocation(line: 140, column: 13, scope: !412)
!412 = distinct !DILexicalBlock(scope: !328, file: !1, line: 140, column: 6)
!413 = !DILocation(line: 140, column: 6, scope: !412)
!414 = !DILocation(line: 140, column: 31, scope: !412)
!415 = !DILocation(line: 140, column: 6, scope: !328)
!416 = !DILocation(line: 141, column: 3, scope: !412)
!417 = !DILocation(line: 142, column: 15, scope: !328)
!418 = !DILocation(line: 145, column: 6, scope: !419)
!419 = distinct !DILexicalBlock(scope: !328, file: !1, line: 145, column: 6)
!420 = !DILocation(line: 145, column: 16, scope: !419)
!421 = !DILocation(line: 145, column: 22, scope: !419)
!422 = !DILocation(line: 145, column: 25, scope: !423)
!423 = !DILexicalBlockFile(scope: !419, file: !1, discriminator: 1)
!424 = !DILocation(line: 145, column: 35, scope: !423)
!425 = !DILocation(line: 145, column: 6, scope: !423)
!426 = !DILocation(line: 146, column: 3, scope: !419)
!427 = !DILocation(line: 147, column: 15, scope: !328)
!428 = !DILocation(line: 152, column: 13, scope: !429)
!429 = distinct !DILexicalBlock(scope: !328, file: !1, line: 152, column: 6)
!430 = !DILocation(line: 152, column: 20, scope: !429)
!431 = !DILocation(line: 152, column: 6, scope: !429)
!432 = !DILocation(line: 152, column: 56, scope: !429)
!433 = !DILocation(line: 152, column: 6, scope: !328)
!434 = !DILocation(line: 153, column: 16, scope: !429)
!435 = !DILocation(line: 153, column: 3, scope: !429)
!436 = !DILocation(line: 154, column: 18, scope: !437)
!437 = distinct !DILexicalBlock(scope: !429, file: !1, line: 154, column: 11)
!438 = !DILocation(line: 154, column: 25, scope: !437)
!439 = !DILocation(line: 154, column: 11, scope: !437)
!440 = !DILocation(line: 154, column: 61, scope: !437)
!441 = !DILocation(line: 154, column: 11, scope: !429)
!442 = !DILocation(line: 155, column: 16, scope: !437)
!443 = !DILocation(line: 155, column: 3, scope: !437)
!444 = !DILocation(line: 157, column: 3, scope: !437)
!445 = !DILocation(line: 159, column: 10, scope: !328)
!446 = !DILocation(line: 159, column: 2, scope: !328)
!447 = !DILocation(line: 160, column: 1, scope: !328)
!448 = !DILocalVariable(name: "self", arg: 1, scope: !329, file: !1, line: 190, type: !169)
!449 = !DILocation(line: 190, column: 47, scope: !329)
!450 = !DILocalVariable(name: "out_block", scope: !329, file: !1, line: 193, type: !122)
!451 = !DILocation(line: 193, column: 8, scope: !329)
!452 = !DILocalVariable(name: "state", scope: !329, file: !1, line: 194, type: !291)
!453 = !DILocation(line: 194, column: 23, scope: !329)
!454 = !DILocation(line: 196, column: 2, scope: !329)
!455 = !DILocation(line: 196, column: 8, scope: !329)
!456 = !DILocation(line: 196, column: 13, scope: !329)
!457 = !DILocation(line: 197, column: 2, scope: !329)
!458 = !DILocation(line: 197, column: 8, scope: !329)
!459 = !DILocation(line: 197, column: 13, scope: !329)
!460 = !DILocation(line: 199, column: 33, scope: !329)
!461 = !DILocation(line: 199, column: 10, scope: !329)
!462 = !DILocation(line: 199, column: 8, scope: !329)
!463 = !DILocation(line: 200, column: 31, scope: !329)
!464 = !DILocation(line: 200, column: 12, scope: !329)
!465 = !DILocation(line: 201, column: 6, scope: !466)
!466 = distinct !DILexicalBlock(scope: !329, file: !1, line: 201, column: 6)
!467 = !DILocation(line: 201, column: 12, scope: !466)
!468 = !DILocation(line: 201, column: 20, scope: !466)
!469 = !DILocation(line: 201, column: 23, scope: !470)
!470 = !DILexicalBlockFile(scope: !466, file: !1, discriminator: 1)
!471 = !DILocation(line: 201, column: 33, scope: !470)
!472 = !DILocation(line: 201, column: 6, scope: !470)
!473 = !DILocation(line: 202, column: 22, scope: !474)
!474 = distinct !DILexicalBlock(scope: !466, file: !1, line: 201, column: 42)
!475 = !DILocation(line: 202, column: 28, scope: !474)
!476 = !DILocation(line: 202, column: 37, scope: !474)
!477 = !DILocation(line: 202, column: 3, scope: !474)
!478 = !DILocation(line: 204, column: 8, scope: !474)
!479 = !DILocation(line: 204, column: 3, scope: !474)
!480 = !DILocation(line: 205, column: 8, scope: !474)
!481 = !DILocation(line: 205, column: 3, scope: !474)
!482 = !DILocation(line: 206, column: 3, scope: !474)
!483 = !DILocation(line: 209, column: 15, scope: !329)
!484 = !DILocation(line: 209, column: 2, scope: !329)
!485 = !DILocation(line: 209, column: 8, scope: !329)
!486 = !DILocation(line: 209, column: 13, scope: !329)
!487 = !DILocation(line: 210, column: 2, scope: !329)
!488 = !DILocation(line: 210, column: 9, scope: !329)
!489 = !DILocation(line: 210, column: 24, scope: !329)
!490 = !DILocation(line: 211, column: 21, scope: !329)
!491 = !DILocation(line: 211, column: 2, scope: !329)
!492 = !DILocation(line: 211, column: 9, scope: !329)
!493 = !DILocation(line: 211, column: 19, scope: !329)
!494 = !DILocation(line: 212, column: 2, scope: !329)
!495 = !DILocation(line: 212, column: 8, scope: !329)
!496 = !DILocation(line: 212, column: 13, scope: !329)
!497 = !DILocation(line: 213, column: 2, scope: !329)
!498 = !DILocation(line: 213, column: 8, scope: !329)
!499 = !DILocation(line: 213, column: 13, scope: !329)
!500 = !DILocation(line: 214, column: 2, scope: !329)
!501 = !DILocation(line: 214, column: 8, scope: !329)
!502 = !DILocation(line: 214, column: 14, scope: !329)
!503 = !DILocation(line: 216, column: 2, scope: !329)
!504 = !DILocation(line: 217, column: 1, scope: !329)
!505 = !DILocalVariable(name: "self", arg: 1, scope: !327, file: !1, line: 112, type: !168)
!506 = !DILocation(line: 112, column: 54, scope: !327)
!507 = !DILocation(line: 113, column: 8, scope: !327)
!508 = !DILocation(line: 114, column: 2, scope: !327)
!509 = !DILocalVariable(name: "self", arg: 1, scope: !330, file: !1, line: 223, type: !169)
!510 = !DILocation(line: 223, column: 47, scope: !330)
!511 = !DILocalVariable(name: "p", arg: 2, scope: !330, file: !1, line: 223, type: !64)
!512 = !DILocation(line: 223, column: 66, scope: !330)
!513 = !DILocalVariable(name: "state", scope: !330, file: !1, line: 225, type: !291)
!514 = !DILocation(line: 225, column: 23, scope: !330)
!515 = !DILocalVariable(name: "decompressed", scope: !330, file: !1, line: 226, type: !45)
!516 = !DILocation(line: 226, column: 9, scope: !330)
!517 = !DILocalVariable(name: "read_buf", scope: !330, file: !1, line: 227, type: !80)
!518 = !DILocation(line: 227, column: 14, scope: !330)
!519 = !DILocalVariable(name: "ret", scope: !330, file: !1, line: 228, type: !38)
!520 = !DILocation(line: 228, column: 10, scope: !330)
!521 = !DILocation(line: 230, column: 33, scope: !330)
!522 = !DILocation(line: 230, column: 39, scope: !330)
!523 = !DILocation(line: 230, column: 10, scope: !330)
!524 = !DILocation(line: 230, column: 8, scope: !330)
!525 = !DILocation(line: 232, column: 6, scope: !526)
!526 = distinct !DILexicalBlock(scope: !330, file: !1, line: 232, column: 6)
!527 = !DILocation(line: 232, column: 13, scope: !526)
!528 = !DILocation(line: 232, column: 6, scope: !330)
!529 = !DILocation(line: 233, column: 4, scope: !530)
!530 = distinct !DILexicalBlock(scope: !526, file: !1, line: 232, column: 18)
!531 = !DILocation(line: 233, column: 6, scope: !530)
!532 = !DILocation(line: 234, column: 3, scope: !530)
!533 = !DILocation(line: 238, column: 27, scope: !330)
!534 = !DILocation(line: 238, column: 34, scope: !330)
!535 = !DILocation(line: 238, column: 2, scope: !330)
!536 = !DILocation(line: 238, column: 9, scope: !330)
!537 = !DILocation(line: 238, column: 16, scope: !330)
!538 = !DILocation(line: 238, column: 25, scope: !330)
!539 = !DILocation(line: 239, column: 28, scope: !330)
!540 = !DILocation(line: 239, column: 35, scope: !330)
!541 = !DILocation(line: 239, column: 2, scope: !330)
!542 = !DILocation(line: 239, column: 9, scope: !330)
!543 = !DILocation(line: 239, column: 16, scope: !330)
!544 = !DILocation(line: 239, column: 26, scope: !330)
!545 = !DILocation(line: 242, column: 2, scope: !330)
!546 = !DILocation(line: 243, column: 8, scope: !547)
!547 = distinct !DILexicalBlock(scope: !548, file: !1, line: 243, column: 7)
!548 = distinct !DILexicalBlock(scope: !549, file: !1, line: 242, column: 11)
!549 = distinct !DILexicalBlock(scope: !550, file: !1, line: 242, column: 2)
!550 = distinct !DILexicalBlock(scope: !330, file: !1, line: 242, column: 2)
!551 = !DILocation(line: 243, column: 15, scope: !547)
!552 = !DILocation(line: 243, column: 7, scope: !548)
!553 = !DILocation(line: 244, column: 25, scope: !554)
!554 = distinct !DILexicalBlock(scope: !555, file: !1, line: 244, column: 8)
!555 = distinct !DILexicalBlock(scope: !547, file: !1, line: 243, column: 22)
!556 = !DILocation(line: 244, column: 31, scope: !554)
!557 = !DILocation(line: 244, column: 39, scope: !554)
!558 = !DILocation(line: 244, column: 45, scope: !554)
!559 = !DILocation(line: 244, column: 8, scope: !554)
!560 = !DILocation(line: 244, column: 55, scope: !554)
!561 = !DILocation(line: 244, column: 8, scope: !555)
!562 = !DILocation(line: 245, column: 5, scope: !563)
!563 = distinct !DILexicalBlock(scope: !554, file: !1, line: 244, column: 61)
!564 = !DILocation(line: 245, column: 12, scope: !563)
!565 = !DILocation(line: 245, column: 16, scope: !563)
!566 = !DILocation(line: 246, column: 10, scope: !563)
!567 = !DILocation(line: 246, column: 17, scope: !563)
!568 = !DILocation(line: 246, column: 6, scope: !563)
!569 = !DILocation(line: 246, column: 8, scope: !563)
!570 = !DILocation(line: 247, column: 20, scope: !563)
!571 = !DILocation(line: 247, column: 27, scope: !563)
!572 = !DILocation(line: 247, column: 34, scope: !563)
!573 = !DILocation(line: 248, column: 11, scope: !563)
!574 = !DILocation(line: 248, column: 18, scope: !563)
!575 = !DILocation(line: 248, column: 9, scope: !563)
!576 = !DILocation(line: 247, column: 18, scope: !563)
!577 = !DILocation(line: 249, column: 13, scope: !563)
!578 = !DILocation(line: 249, column: 5, scope: !563)
!579 = !DILocation(line: 252, column: 33, scope: !555)
!580 = !DILocation(line: 252, column: 40, scope: !555)
!581 = !DILocation(line: 252, column: 10, scope: !555)
!582 = !DILocation(line: 252, column: 8, scope: !555)
!583 = !DILocation(line: 257, column: 8, scope: !584)
!584 = distinct !DILexicalBlock(scope: !555, file: !1, line: 257, column: 8)
!585 = !DILocation(line: 257, column: 12, scope: !584)
!586 = !DILocation(line: 257, column: 8, scope: !555)
!587 = !DILocation(line: 258, column: 34, scope: !584)
!588 = !DILocation(line: 258, column: 41, scope: !584)
!589 = !DILocation(line: 258, column: 11, scope: !584)
!590 = !DILocation(line: 258, column: 9, scope: !584)
!591 = !DILocation(line: 258, column: 5, scope: !584)
!592 = !DILocation(line: 262, column: 8, scope: !593)
!593 = distinct !DILexicalBlock(scope: !555, file: !1, line: 262, column: 8)
!594 = !DILocation(line: 262, column: 12, scope: !593)
!595 = !DILocation(line: 262, column: 8, scope: !555)
!596 = !DILocalVariable(name: "detail", scope: !597, file: !1, line: 263, type: !80)
!597 = distinct !DILexicalBlock(scope: !593, file: !1, line: 262, column: 22)
!598 = !DILocation(line: 263, column: 17, scope: !597)
!599 = !DILocalVariable(name: "err", scope: !597, file: !1, line: 264, type: !23)
!600 = !DILocation(line: 264, column: 9, scope: !597)
!601 = !DILocation(line: 265, column: 13, scope: !597)
!602 = !DILocation(line: 265, column: 5, scope: !597)
!603 = !DILocation(line: 267, column: 13, scope: !604)
!604 = distinct !DILexicalBlock(scope: !597, file: !1, line: 265, column: 18)
!605 = !DILocation(line: 268, column: 6, scope: !604)
!606 = !DILocation(line: 270, column: 10, scope: !604)
!607 = !DILocation(line: 271, column: 13, scope: !604)
!608 = !DILocation(line: 272, column: 6, scope: !604)
!609 = !DILocation(line: 274, column: 13, scope: !604)
!610 = !DILocation(line: 275, column: 6, scope: !604)
!611 = !DILocation(line: 277, column: 24, scope: !597)
!612 = !DILocation(line: 277, column: 30, scope: !597)
!613 = !DILocation(line: 277, column: 39, scope: !597)
!614 = !DILocation(line: 277, column: 48, scope: !597)
!615 = !DILocation(line: 279, column: 9, scope: !597)
!616 = !DILocation(line: 279, column: 16, scope: !597)
!617 = !DILocation(line: 280, column: 9, scope: !597)
!618 = !DILocation(line: 277, column: 5, scope: !597)
!619 = !DILocation(line: 281, column: 5, scope: !597)
!620 = !DILocation(line: 283, column: 4, scope: !555)
!621 = !DILocation(line: 283, column: 11, scope: !555)
!622 = !DILocation(line: 283, column: 17, scope: !555)
!623 = !DILocation(line: 284, column: 3, scope: !555)
!624 = !DILocation(line: 289, column: 35, scope: !548)
!625 = !DILocation(line: 289, column: 41, scope: !548)
!626 = !DILocation(line: 289, column: 7, scope: !548)
!627 = !DILocation(line: 288, column: 12, scope: !548)
!628 = !DILocation(line: 290, column: 7, scope: !629)
!629 = distinct !DILexicalBlock(scope: !548, file: !1, line: 290, column: 7)
!630 = !DILocation(line: 290, column: 16, scope: !629)
!631 = !DILocation(line: 290, column: 7, scope: !548)
!632 = !DILocation(line: 291, column: 23, scope: !633)
!633 = distinct !DILexicalBlock(scope: !629, file: !1, line: 290, column: 25)
!634 = !DILocation(line: 291, column: 29, scope: !633)
!635 = !DILocation(line: 291, column: 38, scope: !633)
!636 = !DILocation(line: 291, column: 4, scope: !633)
!637 = !DILocation(line: 294, column: 4, scope: !633)
!638 = !DILocation(line: 296, column: 46, scope: !548)
!639 = !DILocation(line: 296, column: 35, scope: !548)
!640 = !DILocation(line: 296, column: 27, scope: !548)
!641 = !DILocation(line: 296, column: 3, scope: !548)
!642 = !DILocation(line: 296, column: 10, scope: !548)
!643 = !DILocation(line: 296, column: 17, scope: !548)
!644 = !DILocation(line: 296, column: 25, scope: !548)
!645 = !DILocation(line: 297, column: 28, scope: !548)
!646 = !DILocation(line: 297, column: 3, scope: !548)
!647 = !DILocation(line: 297, column: 10, scope: !548)
!648 = !DILocation(line: 297, column: 17, scope: !548)
!649 = !DILocation(line: 297, column: 26, scope: !548)
!650 = !DILocation(line: 299, column: 7, scope: !651)
!651 = distinct !DILexicalBlock(scope: !548, file: !1, line: 299, column: 7)
!652 = !DILocation(line: 299, column: 11, scope: !651)
!653 = !DILocation(line: 299, column: 7, scope: !548)
!654 = !DILocation(line: 300, column: 4, scope: !655)
!655 = distinct !DILexicalBlock(scope: !651, file: !1, line: 299, column: 17)
!656 = !DILocation(line: 300, column: 11, scope: !655)
!657 = !DILocation(line: 300, column: 15, scope: !655)
!658 = !DILocation(line: 301, column: 9, scope: !655)
!659 = !DILocation(line: 301, column: 16, scope: !655)
!660 = !DILocation(line: 301, column: 5, scope: !655)
!661 = !DILocation(line: 301, column: 7, scope: !655)
!662 = !DILocation(line: 302, column: 19, scope: !655)
!663 = !DILocation(line: 302, column: 26, scope: !655)
!664 = !DILocation(line: 302, column: 33, scope: !655)
!665 = !DILocation(line: 303, column: 10, scope: !655)
!666 = !DILocation(line: 303, column: 17, scope: !655)
!667 = !DILocation(line: 303, column: 8, scope: !655)
!668 = !DILocation(line: 302, column: 17, scope: !655)
!669 = !DILocation(line: 304, column: 12, scope: !655)
!670 = !DILocation(line: 304, column: 4, scope: !655)
!671 = !DILocation(line: 308, column: 28, scope: !548)
!672 = !DILocation(line: 308, column: 35, scope: !548)
!673 = !DILocation(line: 308, column: 9, scope: !548)
!674 = !DILocation(line: 308, column: 7, scope: !548)
!675 = !DILocation(line: 309, column: 33, scope: !548)
!676 = !DILocation(line: 309, column: 39, scope: !548)
!677 = !DILocation(line: 310, column: 7, scope: !548)
!678 = !DILocation(line: 310, column: 14, scope: !548)
!679 = !DILocation(line: 310, column: 21, scope: !548)
!680 = !DILocation(line: 310, column: 31, scope: !548)
!681 = !DILocation(line: 310, column: 29, scope: !548)
!682 = !DILocation(line: 309, column: 3, scope: !548)
!683 = !DILocation(line: 312, column: 11, scope: !548)
!684 = !DILocation(line: 312, column: 3, scope: !548)
!685 = !DILocation(line: 314, column: 34, scope: !686)
!686 = distinct !DILexicalBlock(scope: !548, file: !1, line: 312, column: 16)
!687 = !DILocation(line: 314, column: 41, scope: !686)
!688 = !DILocation(line: 314, column: 12, scope: !686)
!689 = !DILocation(line: 314, column: 4, scope: !686)
!690 = !DILocation(line: 316, column: 5, scope: !691)
!691 = distinct !DILexicalBlock(scope: !686, file: !1, line: 314, column: 51)
!692 = !DILocation(line: 318, column: 25, scope: !691)
!693 = !DILocation(line: 318, column: 31, scope: !691)
!694 = !DILocation(line: 318, column: 40, scope: !691)
!695 = !DILocation(line: 318, column: 5, scope: !691)
!696 = !DILocation(line: 321, column: 5, scope: !691)
!697 = !DILocation(line: 323, column: 4, scope: !686)
!698 = !DILocation(line: 323, column: 11, scope: !686)
!699 = !DILocation(line: 323, column: 17, scope: !686)
!700 = !DILocation(line: 327, column: 8, scope: !701)
!701 = distinct !DILexicalBlock(scope: !686, file: !1, line: 327, column: 8)
!702 = !DILocation(line: 327, column: 15, scope: !701)
!703 = !DILocation(line: 327, column: 22, scope: !701)
!704 = !DILocation(line: 327, column: 32, scope: !701)
!705 = !DILocation(line: 327, column: 8, scope: !686)
!706 = !DILocation(line: 328, column: 10, scope: !707)
!707 = distinct !DILexicalBlock(scope: !701, file: !1, line: 327, column: 38)
!708 = !DILocation(line: 328, column: 17, scope: !707)
!709 = !DILocation(line: 328, column: 6, scope: !707)
!710 = !DILocation(line: 328, column: 8, scope: !707)
!711 = !DILocation(line: 329, column: 20, scope: !707)
!712 = !DILocation(line: 329, column: 27, scope: !707)
!713 = !DILocation(line: 329, column: 34, scope: !707)
!714 = !DILocation(line: 330, column: 11, scope: !707)
!715 = !DILocation(line: 330, column: 18, scope: !707)
!716 = !DILocation(line: 330, column: 9, scope: !707)
!717 = !DILocation(line: 329, column: 18, scope: !707)
!718 = !DILocation(line: 331, column: 13, scope: !707)
!719 = !DILocation(line: 331, column: 5, scope: !707)
!720 = !DILocation(line: 333, column: 4, scope: !686)
!721 = !DILocation(line: 335, column: 23, scope: !686)
!722 = !DILocation(line: 335, column: 29, scope: !686)
!723 = !DILocation(line: 335, column: 38, scope: !686)
!724 = !DILocation(line: 335, column: 4, scope: !686)
!725 = !DILocation(line: 337, column: 4, scope: !686)
!726 = !DILocation(line: 242, column: 2, scope: !727)
!727 = !DILexicalBlockFile(scope: !549, file: !1, discriminator: 1)
!728 = !DILocation(line: 340, column: 1, scope: !330)
!729 = !DILocalVariable(name: "self", arg: 1, scope: !331, file: !1, line: 346, type: !169)
!730 = !DILocation(line: 346, column: 48, scope: !331)
!731 = !DILocalVariable(name: "state", scope: !331, file: !1, line: 348, type: !291)
!732 = !DILocation(line: 348, column: 23, scope: !331)
!733 = !DILocalVariable(name: "ret", scope: !331, file: !1, line: 349, type: !23)
!734 = !DILocation(line: 349, column: 6, scope: !331)
!735 = !DILocation(line: 351, column: 33, scope: !331)
!736 = !DILocation(line: 351, column: 39, scope: !331)
!737 = !DILocation(line: 351, column: 10, scope: !331)
!738 = !DILocation(line: 351, column: 8, scope: !331)
!739 = !DILocation(line: 353, column: 6, scope: !740)
!740 = distinct !DILexicalBlock(scope: !331, file: !1, line: 353, column: 6)
!741 = !DILocation(line: 353, column: 13, scope: !740)
!742 = !DILocation(line: 353, column: 6, scope: !331)
!743 = !DILocation(line: 354, column: 32, scope: !744)
!744 = distinct !DILexicalBlock(scope: !740, file: !1, line: 353, column: 20)
!745 = !DILocation(line: 354, column: 39, scope: !744)
!746 = !DILocation(line: 354, column: 11, scope: !744)
!747 = !DILocation(line: 354, column: 3, scope: !744)
!748 = !DILocation(line: 356, column: 4, scope: !749)
!749 = distinct !DILexicalBlock(scope: !744, file: !1, line: 354, column: 48)
!750 = !DILocation(line: 358, column: 23, scope: !749)
!751 = !DILocation(line: 358, column: 29, scope: !749)
!752 = !DILocation(line: 358, column: 38, scope: !749)
!753 = !DILocation(line: 358, column: 4, scope: !749)
!754 = !DILocation(line: 361, column: 8, scope: !749)
!755 = !DILocation(line: 362, column: 3, scope: !749)
!756 = !DILocation(line: 363, column: 3, scope: !744)
!757 = !DILocation(line: 363, column: 10, scope: !744)
!758 = !DILocation(line: 363, column: 16, scope: !744)
!759 = !DILocation(line: 364, column: 2, scope: !744)
!760 = !DILocation(line: 366, column: 7, scope: !331)
!761 = !DILocation(line: 366, column: 14, scope: !331)
!762 = !DILocation(line: 366, column: 2, scope: !331)
!763 = !DILocation(line: 367, column: 7, scope: !331)
!764 = !DILocation(line: 367, column: 2, scope: !331)
!765 = !DILocation(line: 368, column: 10, scope: !331)
!766 = !DILocation(line: 368, column: 2, scope: !331)
