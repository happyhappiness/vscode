; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_support_filter_compress.c'
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
%struct.private_data = type { i8*, i64, i64, i32, i32, i64, i64, i8*, i32, i32, i32, i32, i32, i32, i32, i32, i32, [65536 x i8], [65536 x i16], i8*, [65300 x i8] }

@.str = private unnamed_addr constant [37 x i8] c"archive_read_support_filter_compress\00", align 1
@.str.1 = private unnamed_addr constant [14 x i8] c"compress (.Z)\00", align 1
@compress_bidder_init.out_block_size = internal constant i64 65536, align 8
@.str.2 = private unnamed_addr constant [41 x i8] c"Can't allocate data for %s decompression\00", align 1
@.str.3 = private unnamed_addr constant [24 x i8] c"Invalid compressed data\00", align 1
@getbits.mask = internal constant [17 x i32] [i32 0, i32 1, i32 3, i32 7, i32 15, i32 31, i32 63, i32 127, i32 255, i32 511, i32 1023, i32 2047, i32 4095, i32 8191, i32 16383, i32 32767, i32 65535], align 16
@next_code.debug_buff = internal global [1024 x i32] zeroinitializer, align 16
@next_code.debug_index = internal global i32 0, align 4

; Function Attrs: nounwind uwtable
define i32 @archive_read_support_compression_compress(%struct.archive* %a) #0 !dbg !329 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !356, metadata !357), !dbg !358
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !359
  %call = call i32 @archive_read_support_filter_compress(%struct.archive* %0), !dbg !360
  ret i32 %call, !dbg !361
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define i32 @archive_read_support_filter_compress(%struct.archive* %_a) #0 !dbg !330 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_read*, align 8
  %bidder = alloca %struct.archive_read_filter_bidder*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !362, metadata !357), !dbg !363
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !364, metadata !357), !dbg !365
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !366
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !367
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !365
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter_bidder** %bidder, metadata !368, metadata !357), !dbg !369
  br label %do.body, !dbg !370

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !371, metadata !357), !dbg !373
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !374
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 14594245, i32 1, i8* getelementptr inbounds ([37 x i8], [37 x i8]* @.str, i32 0, i32 0)), !dbg !374
  store i32 %call, i32* %magic_test, align 4, !dbg !374
  %3 = load i32, i32* %magic_test, align 4, !dbg !374
  %cmp = icmp eq i32 %3, -30, !dbg !374
  br i1 %cmp, label %if.then, label %if.end, !dbg !374

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !376
  br label %return, !dbg !376

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !379

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !381
  %call1 = call i32 @__archive_read_get_bidder(%struct.archive_read* %4, %struct.archive_read_filter_bidder** %bidder), !dbg !383
  %cmp2 = icmp ne i32 %call1, 0, !dbg !384
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !385

if.then3:                                         ; preds = %do.end
  store i32 -30, i32* %retval, align 4, !dbg !386
  br label %return, !dbg !386

if.end4:                                          ; preds = %do.end
  %5 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !387
  %data = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %5, i32 0, i32 0, !dbg !388
  store i8* null, i8** %data, align 8, !dbg !389
  %6 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !390
  %name = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %6, i32 0, i32 1, !dbg !391
  store i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.1, i32 0, i32 0), i8** %name, align 8, !dbg !392
  %7 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !393
  %bid = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %7, i32 0, i32 2, !dbg !394
  store i32 (%struct.archive_read_filter_bidder*, %struct.archive_read_filter*)* @compress_bidder_bid, i32 (%struct.archive_read_filter_bidder*, %struct.archive_read_filter*)** %bid, align 8, !dbg !395
  %8 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !396
  %init = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %8, i32 0, i32 3, !dbg !397
  store i32 (%struct.archive_read_filter*)* @compress_bidder_init, i32 (%struct.archive_read_filter*)** %init, align 8, !dbg !398
  %9 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !399
  %options = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %9, i32 0, i32 4, !dbg !400
  store i32 (%struct.archive_read_filter_bidder*, i8*, i8*)* null, i32 (%struct.archive_read_filter_bidder*, i8*, i8*)** %options, align 8, !dbg !401
  %10 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !402
  %free = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %10, i32 0, i32 5, !dbg !403
  store i32 (%struct.archive_read_filter_bidder*)* @compress_bidder_free, i32 (%struct.archive_read_filter_bidder*)** %free, align 8, !dbg !404
  store i32 0, i32* %retval, align 4, !dbg !405
  br label %return, !dbg !405

return:                                           ; preds = %if.end4, %if.then3, %if.then
  %11 = load i32, i32* %retval, align 4, !dbg !406
  ret i32 %11, !dbg !406
}

declare i32 @__archive_check_magic(%struct.archive*, i32, i32, i8*) #2

declare i32 @__archive_read_get_bidder(%struct.archive_read*, %struct.archive_read_filter_bidder**) #2

; Function Attrs: nounwind uwtable
define internal i32 @compress_bidder_bid(%struct.archive_read_filter_bidder* %self, %struct.archive_read_filter* %filter) #0 !dbg !331 {
entry:
  %retval = alloca i32, align 4
  %self.addr = alloca %struct.archive_read_filter_bidder*, align 8
  %filter.addr = alloca %struct.archive_read_filter*, align 8
  %buffer = alloca i8*, align 8
  %avail = alloca i64, align 8
  %bits_checked = alloca i32, align 4
  store %struct.archive_read_filter_bidder* %self, %struct.archive_read_filter_bidder** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter_bidder** %self.addr, metadata !407, metadata !357), !dbg !408
  store %struct.archive_read_filter* %filter, %struct.archive_read_filter** %filter.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %filter.addr, metadata !409, metadata !357), !dbg !410
  call void @llvm.dbg.declare(metadata i8** %buffer, metadata !411, metadata !357), !dbg !412
  call void @llvm.dbg.declare(metadata i64* %avail, metadata !413, metadata !357), !dbg !414
  call void @llvm.dbg.declare(metadata i32* %bits_checked, metadata !415, metadata !357), !dbg !416
  %0 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %self.addr, align 8, !dbg !417
  %1 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !418
  %call = call i8* @__archive_read_filter_ahead(%struct.archive_read_filter* %1, i64 3, i64* %avail), !dbg !419
  store i8* %call, i8** %buffer, align 8, !dbg !420
  %2 = load i8*, i8** %buffer, align 8, !dbg !421
  %cmp = icmp eq i8* %2, null, !dbg !423
  br i1 %cmp, label %if.then, label %if.end, !dbg !424

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !425
  br label %return, !dbg !425

if.end:                                           ; preds = %entry
  store i32 0, i32* %bits_checked, align 4, !dbg !426
  %3 = load i8*, i8** %buffer, align 8, !dbg !427
  %arrayidx = getelementptr inbounds i8, i8* %3, i64 0, !dbg !427
  %4 = load i8, i8* %arrayidx, align 1, !dbg !427
  %conv = zext i8 %4 to i32, !dbg !427
  %cmp1 = icmp ne i32 %conv, 31, !dbg !429
  br i1 %cmp1, label %if.then7, label %lor.lhs.false, !dbg !430

lor.lhs.false:                                    ; preds = %if.end
  %5 = load i8*, i8** %buffer, align 8, !dbg !431
  %arrayidx3 = getelementptr inbounds i8, i8* %5, i64 1, !dbg !431
  %6 = load i8, i8* %arrayidx3, align 1, !dbg !431
  %conv4 = zext i8 %6 to i32, !dbg !431
  %cmp5 = icmp ne i32 %conv4, 157, !dbg !433
  br i1 %cmp5, label %if.then7, label %if.end8, !dbg !434

if.then7:                                         ; preds = %lor.lhs.false, %if.end
  store i32 0, i32* %retval, align 4, !dbg !435
  br label %return, !dbg !435

if.end8:                                          ; preds = %lor.lhs.false
  %7 = load i8*, i8** %buffer, align 8, !dbg !436
  %arrayidx9 = getelementptr inbounds i8, i8* %7, i64 2, !dbg !436
  %8 = load i8, i8* %arrayidx9, align 1, !dbg !436
  %conv10 = zext i8 %8 to i32, !dbg !436
  %and = and i32 %conv10, 32, !dbg !438
  %tobool = icmp ne i32 %and, 0, !dbg !438
  br i1 %tobool, label %if.then11, label %if.end12, !dbg !439

if.then11:                                        ; preds = %if.end8
  store i32 0, i32* %retval, align 4, !dbg !440
  br label %return, !dbg !440

if.end12:                                         ; preds = %if.end8
  %9 = load i8*, i8** %buffer, align 8, !dbg !441
  %arrayidx13 = getelementptr inbounds i8, i8* %9, i64 2, !dbg !441
  %10 = load i8, i8* %arrayidx13, align 1, !dbg !441
  %conv14 = zext i8 %10 to i32, !dbg !441
  %and15 = and i32 %conv14, 64, !dbg !443
  %tobool16 = icmp ne i32 %and15, 0, !dbg !443
  br i1 %tobool16, label %if.then17, label %if.end18, !dbg !444

if.then17:                                        ; preds = %if.end12
  store i32 0, i32* %retval, align 4, !dbg !445
  br label %return, !dbg !445

if.end18:                                         ; preds = %if.end12
  %11 = load i32, i32* %bits_checked, align 4, !dbg !446
  %add = add nsw i32 %11, 18, !dbg !446
  store i32 %add, i32* %bits_checked, align 4, !dbg !446
  %12 = load i32, i32* %bits_checked, align 4, !dbg !447
  store i32 %12, i32* %retval, align 4, !dbg !448
  br label %return, !dbg !448

return:                                           ; preds = %if.end18, %if.then17, %if.then11, %if.then7, %if.then
  %13 = load i32, i32* %retval, align 4, !dbg !449
  ret i32 %13, !dbg !449
}

; Function Attrs: nounwind uwtable
define internal i32 @compress_bidder_init(%struct.archive_read_filter* %self) #0 !dbg !332 {
entry:
  %retval = alloca i32, align 4
  %self.addr = alloca %struct.archive_read_filter*, align 8
  %state = alloca %struct.private_data*, align 8
  %out_block = alloca i8*, align 8
  %code = alloca i32, align 4
  store %struct.archive_read_filter* %self, %struct.archive_read_filter** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %self.addr, metadata !450, metadata !357), !dbg !451
  call void @llvm.dbg.declare(metadata %struct.private_data** %state, metadata !452, metadata !357), !dbg !453
  call void @llvm.dbg.declare(metadata i8** %out_block, metadata !454, metadata !357), !dbg !455
  call void @llvm.dbg.declare(metadata i32* %code, metadata !456, metadata !357), !dbg !457
  %0 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !458
  %code1 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %0, i32 0, i32 12, !dbg !459
  store i32 3, i32* %code1, align 8, !dbg !460
  %1 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !461
  %name = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %1, i32 0, i32 11, !dbg !462
  store i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.1, i32 0, i32 0), i8** %name, align 8, !dbg !463
  %call = call noalias i8* @calloc(i64 262016, i64 1) #4, !dbg !464
  %2 = bitcast i8* %call to %struct.private_data*, !dbg !465
  store %struct.private_data* %2, %struct.private_data** %state, align 8, !dbg !466
  %call2 = call noalias i8* @malloc(i64 65536) #4, !dbg !467
  store i8* %call2, i8** %out_block, align 8, !dbg !468
  %3 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !469
  %cmp = icmp eq %struct.private_data* %3, null, !dbg !471
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !472

lor.lhs.false:                                    ; preds = %entry
  %4 = load i8*, i8** %out_block, align 8, !dbg !473
  %cmp3 = icmp eq i8* %4, null, !dbg !475
  br i1 %cmp3, label %if.then, label %if.end, !dbg !476

if.then:                                          ; preds = %lor.lhs.false, %entry
  %5 = load i8*, i8** %out_block, align 8, !dbg !477
  call void @free(i8* %5) #4, !dbg !479
  %6 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !480
  %7 = bitcast %struct.private_data* %6 to i8*, !dbg !480
  call void @free(i8* %7) #4, !dbg !481
  %8 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !482
  %archive = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %8, i32 0, i32 3, !dbg !483
  %9 = load %struct.archive_read*, %struct.archive_read** %archive, align 8, !dbg !483
  %archive4 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %9, i32 0, i32 0, !dbg !484
  %10 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !485
  %name5 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %10, i32 0, i32 11, !dbg !486
  %11 = load i8*, i8** %name5, align 8, !dbg !486
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive4, i32 12, i8* getelementptr inbounds ([41 x i8], [41 x i8]* @.str.2, i32 0, i32 0), i8* %11), !dbg !487
  store i32 -30, i32* %retval, align 4, !dbg !488
  br label %return, !dbg !488

if.end:                                           ; preds = %lor.lhs.false
  %12 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !489
  %13 = bitcast %struct.private_data* %12 to i8*, !dbg !489
  %14 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !490
  %data = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %14, i32 0, i32 10, !dbg !491
  store i8* %13, i8** %data, align 8, !dbg !492
  %15 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !493
  %out_block_size = getelementptr inbounds %struct.private_data, %struct.private_data* %15, i32 0, i32 6, !dbg !494
  store i64 65536, i64* %out_block_size, align 8, !dbg !495
  %16 = load i8*, i8** %out_block, align 8, !dbg !496
  %17 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !497
  %out_block6 = getelementptr inbounds %struct.private_data, %struct.private_data* %17, i32 0, i32 7, !dbg !498
  store i8* %16, i8** %out_block6, align 8, !dbg !499
  %18 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !500
  %read = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %18, i32 0, i32 5, !dbg !501
  store i64 (%struct.archive_read_filter*, i8**)* @compress_filter_read, i64 (%struct.archive_read_filter*, i8**)** %read, align 8, !dbg !502
  %19 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !503
  %skip = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %19, i32 0, i32 6, !dbg !504
  store i64 (%struct.archive_read_filter*, i64)* null, i64 (%struct.archive_read_filter*, i64)** %skip, align 8, !dbg !505
  %20 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !506
  %close = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %20, i32 0, i32 8, !dbg !507
  store i32 (%struct.archive_read_filter*)* @compress_filter_close, i32 (%struct.archive_read_filter*)** %close, align 8, !dbg !508
  %21 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !509
  %call7 = call i32 @getbits(%struct.archive_read_filter* %21, i32 8), !dbg !510
  %22 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !511
  %call8 = call i32 @getbits(%struct.archive_read_filter* %22, i32 8), !dbg !512
  %23 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !513
  %call9 = call i32 @getbits(%struct.archive_read_filter* %23, i32 8), !dbg !514
  store i32 %call9, i32* %code, align 4, !dbg !515
  %24 = load i32, i32* %code, align 4, !dbg !516
  %and = and i32 %24, 31, !dbg !518
  %cmp10 = icmp sgt i32 %and, 16, !dbg !519
  br i1 %cmp10, label %if.then11, label %if.end14, !dbg !520

if.then11:                                        ; preds = %if.end
  %25 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !521
  %archive12 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %25, i32 0, i32 3, !dbg !523
  %26 = load %struct.archive_read*, %struct.archive_read** %archive12, align 8, !dbg !523
  %archive13 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %26, i32 0, i32 0, !dbg !524
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive13, i32 -1, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.3, i32 0, i32 0)), !dbg !525
  store i32 -30, i32* %retval, align 4, !dbg !526
  br label %return, !dbg !526

if.end14:                                         ; preds = %if.end
  %27 = load i32, i32* %code, align 4, !dbg !527
  %and15 = and i32 %27, 31, !dbg !528
  %28 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !529
  %maxcode_bits = getelementptr inbounds %struct.private_data, %struct.private_data* %28, i32 0, i32 11, !dbg !530
  store i32 %and15, i32* %maxcode_bits, align 4, !dbg !531
  %29 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !532
  %maxcode_bits16 = getelementptr inbounds %struct.private_data, %struct.private_data* %29, i32 0, i32 11, !dbg !533
  %30 = load i32, i32* %maxcode_bits16, align 4, !dbg !533
  %shl = shl i32 1, %30, !dbg !534
  %31 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !535
  %maxcode = getelementptr inbounds %struct.private_data, %struct.private_data* %31, i32 0, i32 10, !dbg !536
  store i32 %shl, i32* %maxcode, align 8, !dbg !537
  %32 = load i32, i32* %code, align 4, !dbg !538
  %and17 = and i32 %32, 128, !dbg !539
  %33 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !540
  %use_reset_code = getelementptr inbounds %struct.private_data, %struct.private_data* %33, i32 0, i32 8, !dbg !541
  store i32 %and17, i32* %use_reset_code, align 8, !dbg !542
  %34 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !543
  %free_ent = getelementptr inbounds %struct.private_data, %struct.private_data* %34, i32 0, i32 16, !dbg !544
  store i32 256, i32* %free_ent, align 8, !dbg !545
  %35 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !546
  %stack = getelementptr inbounds %struct.private_data, %struct.private_data* %35, i32 0, i32 20, !dbg !547
  %arraydecay = getelementptr inbounds [65300 x i8], [65300 x i8]* %stack, i32 0, i32 0, !dbg !546
  %36 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !548
  %stackp = getelementptr inbounds %struct.private_data, %struct.private_data* %36, i32 0, i32 19, !dbg !549
  store i8* %arraydecay, i8** %stackp, align 8, !dbg !550
  %37 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !551
  %use_reset_code18 = getelementptr inbounds %struct.private_data, %struct.private_data* %37, i32 0, i32 8, !dbg !553
  %38 = load i32, i32* %use_reset_code18, align 8, !dbg !553
  %tobool = icmp ne i32 %38, 0, !dbg !551
  br i1 %tobool, label %if.then19, label %if.end21, !dbg !554

if.then19:                                        ; preds = %if.end14
  %39 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !555
  %free_ent20 = getelementptr inbounds %struct.private_data, %struct.private_data* %39, i32 0, i32 16, !dbg !556
  %40 = load i32, i32* %free_ent20, align 8, !dbg !557
  %inc = add nsw i32 %40, 1, !dbg !557
  store i32 %inc, i32* %free_ent20, align 8, !dbg !557
  br label %if.end21, !dbg !555

if.end21:                                         ; preds = %if.then19, %if.end14
  %41 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !558
  %bits = getelementptr inbounds %struct.private_data, %struct.private_data* %41, i32 0, i32 13, !dbg !559
  store i32 9, i32* %bits, align 4, !dbg !560
  %42 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !561
  %bits22 = getelementptr inbounds %struct.private_data, %struct.private_data* %42, i32 0, i32 13, !dbg !562
  %43 = load i32, i32* %bits22, align 4, !dbg !562
  %shl23 = shl i32 1, %43, !dbg !563
  %sub = sub nsw i32 %shl23, 1, !dbg !564
  %44 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !565
  %section_end_code = getelementptr inbounds %struct.private_data, %struct.private_data* %44, i32 0, i32 12, !dbg !566
  store i32 %sub, i32* %section_end_code, align 8, !dbg !567
  %45 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !568
  %oldcode = getelementptr inbounds %struct.private_data, %struct.private_data* %45, i32 0, i32 14, !dbg !569
  store i32 -1, i32* %oldcode, align 8, !dbg !570
  store i32 255, i32* %code, align 4, !dbg !571
  br label %for.cond, !dbg !573

for.cond:                                         ; preds = %for.inc, %if.end21
  %46 = load i32, i32* %code, align 4, !dbg !574
  %cmp24 = icmp sge i32 %46, 0, !dbg !577
  br i1 %cmp24, label %for.body, label %for.end, !dbg !578

for.body:                                         ; preds = %for.cond
  %47 = load i32, i32* %code, align 4, !dbg !579
  %idxprom = sext i32 %47 to i64, !dbg !581
  %48 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !581
  %prefix = getelementptr inbounds %struct.private_data, %struct.private_data* %48, i32 0, i32 18, !dbg !582
  %arrayidx = getelementptr inbounds [65536 x i16], [65536 x i16]* %prefix, i64 0, i64 %idxprom, !dbg !581
  store i16 0, i16* %arrayidx, align 2, !dbg !583
  %49 = load i32, i32* %code, align 4, !dbg !584
  %conv = trunc i32 %49 to i8, !dbg !584
  %50 = load i32, i32* %code, align 4, !dbg !585
  %idxprom25 = sext i32 %50 to i64, !dbg !586
  %51 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !586
  %suffix = getelementptr inbounds %struct.private_data, %struct.private_data* %51, i32 0, i32 17, !dbg !587
  %arrayidx26 = getelementptr inbounds [65536 x i8], [65536 x i8]* %suffix, i64 0, i64 %idxprom25, !dbg !586
  store i8 %conv, i8* %arrayidx26, align 1, !dbg !588
  br label %for.inc, !dbg !589

for.inc:                                          ; preds = %for.body
  %52 = load i32, i32* %code, align 4, !dbg !590
  %dec = add nsw i32 %52, -1, !dbg !590
  store i32 %dec, i32* %code, align 4, !dbg !590
  br label %for.cond, !dbg !592

for.end:                                          ; preds = %for.cond
  %53 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !593
  %call27 = call i32 @next_code(%struct.archive_read_filter* %53), !dbg !594
  store i32 0, i32* %retval, align 4, !dbg !595
  br label %return, !dbg !595

return:                                           ; preds = %for.end, %if.then11, %if.then
  %54 = load i32, i32* %retval, align 4, !dbg !596
  ret i32 %54, !dbg !596
}

; Function Attrs: nounwind uwtable
define internal i32 @compress_bidder_free(%struct.archive_read_filter_bidder* %self) #0 !dbg !339 {
entry:
  %self.addr = alloca %struct.archive_read_filter_bidder*, align 8
  store %struct.archive_read_filter_bidder* %self, %struct.archive_read_filter_bidder** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter_bidder** %self.addr, metadata !597, metadata !357), !dbg !598
  %0 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %self.addr, align 8, !dbg !599
  %data = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %0, i32 0, i32 0, !dbg !600
  store i8* null, i8** %data, align 8, !dbg !601
  ret i32 0, !dbg !602
}

declare i8* @__archive_read_filter_ahead(%struct.archive_read_filter*, i64, i64*) #2

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #3

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #3

; Function Attrs: nounwind
declare void @free(i8*) #3

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

; Function Attrs: nounwind uwtable
define internal i64 @compress_filter_read(%struct.archive_read_filter* %self, i8** %pblock) #0 !dbg !333 {
entry:
  %retval = alloca i64, align 8
  %self.addr = alloca %struct.archive_read_filter*, align 8
  %pblock.addr = alloca i8**, align 8
  %state = alloca %struct.private_data*, align 8
  %p = alloca i8*, align 8
  %start = alloca i8*, align 8
  %end = alloca i8*, align 8
  %ret = alloca i32, align 4
  store %struct.archive_read_filter* %self, %struct.archive_read_filter** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %self.addr, metadata !603, metadata !357), !dbg !604
  store i8** %pblock, i8*** %pblock.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %pblock.addr, metadata !605, metadata !357), !dbg !606
  call void @llvm.dbg.declare(metadata %struct.private_data** %state, metadata !607, metadata !357), !dbg !608
  call void @llvm.dbg.declare(metadata i8** %p, metadata !609, metadata !357), !dbg !610
  call void @llvm.dbg.declare(metadata i8** %start, metadata !611, metadata !357), !dbg !612
  call void @llvm.dbg.declare(metadata i8** %end, metadata !613, metadata !357), !dbg !614
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !615, metadata !357), !dbg !616
  %0 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !617
  %data = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %0, i32 0, i32 10, !dbg !618
  %1 = load i8*, i8** %data, align 8, !dbg !618
  %2 = bitcast i8* %1 to %struct.private_data*, !dbg !619
  store %struct.private_data* %2, %struct.private_data** %state, align 8, !dbg !620
  %3 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !621
  %end_of_stream = getelementptr inbounds %struct.private_data, %struct.private_data* %3, i32 0, i32 9, !dbg !623
  %4 = load i32, i32* %end_of_stream, align 4, !dbg !623
  %tobool = icmp ne i32 %4, 0, !dbg !621
  br i1 %tobool, label %if.then, label %if.end, !dbg !624

if.then:                                          ; preds = %entry
  %5 = load i8**, i8*** %pblock.addr, align 8, !dbg !625
  store i8* null, i8** %5, align 8, !dbg !627
  store i64 0, i64* %retval, align 8, !dbg !628
  br label %return, !dbg !628

if.end:                                           ; preds = %entry
  %6 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !629
  %out_block = getelementptr inbounds %struct.private_data, %struct.private_data* %6, i32 0, i32 7, !dbg !630
  %7 = load i8*, i8** %out_block, align 8, !dbg !630
  store i8* %7, i8** %start, align 8, !dbg !631
  store i8* %7, i8** %p, align 8, !dbg !632
  %8 = load i8*, i8** %start, align 8, !dbg !633
  %9 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !634
  %out_block_size = getelementptr inbounds %struct.private_data, %struct.private_data* %9, i32 0, i32 6, !dbg !635
  %10 = load i64, i64* %out_block_size, align 8, !dbg !635
  %add.ptr = getelementptr inbounds i8, i8* %8, i64 %10, !dbg !636
  store i8* %add.ptr, i8** %end, align 8, !dbg !637
  br label %while.cond, !dbg !638

while.cond:                                       ; preds = %if.end15, %if.end
  %11 = load i8*, i8** %p, align 8, !dbg !639
  %12 = load i8*, i8** %end, align 8, !dbg !641
  %cmp = icmp ult i8* %11, %12, !dbg !642
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !643

land.rhs:                                         ; preds = %while.cond
  %13 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !644
  %end_of_stream1 = getelementptr inbounds %struct.private_data, %struct.private_data* %13, i32 0, i32 9, !dbg !646
  %14 = load i32, i32* %end_of_stream1, align 4, !dbg !646
  %tobool2 = icmp ne i32 %14, 0, !dbg !647
  %lnot = xor i1 %tobool2, true, !dbg !647
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond
  %15 = phi i1 [ false, %while.cond ], [ %lnot, %land.rhs ]
  br i1 %15, label %while.body, label %while.end, !dbg !648

while.body:                                       ; preds = %land.end
  %16 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !650
  %stackp = getelementptr inbounds %struct.private_data, %struct.private_data* %16, i32 0, i32 19, !dbg !653
  %17 = load i8*, i8** %stackp, align 8, !dbg !653
  %18 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !654
  %stack = getelementptr inbounds %struct.private_data, %struct.private_data* %18, i32 0, i32 20, !dbg !655
  %arraydecay = getelementptr inbounds [65300 x i8], [65300 x i8]* %stack, i32 0, i32 0, !dbg !654
  %cmp3 = icmp ugt i8* %17, %arraydecay, !dbg !656
  br i1 %cmp3, label %if.then4, label %if.else, !dbg !657

if.then4:                                         ; preds = %while.body
  %19 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !658
  %stackp5 = getelementptr inbounds %struct.private_data, %struct.private_data* %19, i32 0, i32 19, !dbg !660
  %20 = load i8*, i8** %stackp5, align 8, !dbg !661
  %incdec.ptr = getelementptr inbounds i8, i8* %20, i32 -1, !dbg !661
  store i8* %incdec.ptr, i8** %stackp5, align 8, !dbg !661
  %21 = load i8, i8* %incdec.ptr, align 1, !dbg !662
  %22 = load i8*, i8** %p, align 8, !dbg !663
  %incdec.ptr6 = getelementptr inbounds i8, i8* %22, i32 1, !dbg !663
  store i8* %incdec.ptr6, i8** %p, align 8, !dbg !663
  store i8 %21, i8* %22, align 1, !dbg !664
  br label %if.end15, !dbg !665

if.else:                                          ; preds = %while.body
  %23 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !666
  %call = call i32 @next_code(%struct.archive_read_filter* %23), !dbg !668
  store i32 %call, i32* %ret, align 4, !dbg !669
  %24 = load i32, i32* %ret, align 4, !dbg !670
  %cmp7 = icmp eq i32 %24, -1, !dbg !672
  br i1 %cmp7, label %if.then8, label %if.else10, !dbg !673

if.then8:                                         ; preds = %if.else
  %25 = load i32, i32* %ret, align 4, !dbg !674
  %26 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !675
  %end_of_stream9 = getelementptr inbounds %struct.private_data, %struct.private_data* %26, i32 0, i32 9, !dbg !676
  store i32 %25, i32* %end_of_stream9, align 4, !dbg !677
  br label %if.end14, !dbg !675

if.else10:                                        ; preds = %if.else
  %27 = load i32, i32* %ret, align 4, !dbg !678
  %cmp11 = icmp ne i32 %27, 0, !dbg !680
  br i1 %cmp11, label %if.then12, label %if.end13, !dbg !681

if.then12:                                        ; preds = %if.else10
  %28 = load i32, i32* %ret, align 4, !dbg !682
  %conv = sext i32 %28 to i64, !dbg !683
  store i64 %conv, i64* %retval, align 8, !dbg !684
  br label %return, !dbg !684

if.end13:                                         ; preds = %if.else10
  br label %if.end14

if.end14:                                         ; preds = %if.end13, %if.then8
  br label %if.end15

if.end15:                                         ; preds = %if.end14, %if.then4
  br label %while.cond, !dbg !685

while.end:                                        ; preds = %land.end
  %29 = load i8*, i8** %start, align 8, !dbg !687
  %30 = load i8**, i8*** %pblock.addr, align 8, !dbg !688
  store i8* %29, i8** %30, align 8, !dbg !689
  %31 = load i8*, i8** %p, align 8, !dbg !690
  %32 = load i8*, i8** %start, align 8, !dbg !691
  %sub.ptr.lhs.cast = ptrtoint i8* %31 to i64, !dbg !692
  %sub.ptr.rhs.cast = ptrtoint i8* %32 to i64, !dbg !692
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !692
  store i64 %sub.ptr.sub, i64* %retval, align 8, !dbg !693
  br label %return, !dbg !693

return:                                           ; preds = %while.end, %if.then12, %if.then
  %33 = load i64, i64* %retval, align 8, !dbg !694
  ret i64 %33, !dbg !694
}

; Function Attrs: nounwind uwtable
define internal i32 @compress_filter_close(%struct.archive_read_filter* %self) #0 !dbg !334 {
entry:
  %self.addr = alloca %struct.archive_read_filter*, align 8
  %state = alloca %struct.private_data*, align 8
  store %struct.archive_read_filter* %self, %struct.archive_read_filter** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %self.addr, metadata !695, metadata !357), !dbg !696
  call void @llvm.dbg.declare(metadata %struct.private_data** %state, metadata !697, metadata !357), !dbg !698
  %0 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !699
  %data = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %0, i32 0, i32 10, !dbg !700
  %1 = load i8*, i8** %data, align 8, !dbg !700
  %2 = bitcast i8* %1 to %struct.private_data*, !dbg !701
  store %struct.private_data* %2, %struct.private_data** %state, align 8, !dbg !698
  %3 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !702
  %out_block = getelementptr inbounds %struct.private_data, %struct.private_data* %3, i32 0, i32 7, !dbg !703
  %4 = load i8*, i8** %out_block, align 8, !dbg !703
  call void @free(i8* %4) #4, !dbg !704
  %5 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !705
  %6 = bitcast %struct.private_data* %5 to i8*, !dbg !705
  call void @free(i8* %6) #4, !dbg !706
  ret i32 0, !dbg !707
}

; Function Attrs: nounwind uwtable
define internal i32 @getbits(%struct.archive_read_filter* %self, i32 %n) #0 !dbg !335 {
entry:
  %retval = alloca i32, align 4
  %self.addr = alloca %struct.archive_read_filter*, align 8
  %n.addr = alloca i32, align 4
  %state = alloca %struct.private_data*, align 8
  %code = alloca i32, align 4
  %ret = alloca i64, align 8
  store %struct.archive_read_filter* %self, %struct.archive_read_filter** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %self.addr, metadata !708, metadata !357), !dbg !709
  store i32 %n, i32* %n.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %n.addr, metadata !710, metadata !357), !dbg !711
  call void @llvm.dbg.declare(metadata %struct.private_data** %state, metadata !712, metadata !357), !dbg !713
  %0 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !714
  %data = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %0, i32 0, i32 10, !dbg !715
  %1 = load i8*, i8** %data, align 8, !dbg !715
  %2 = bitcast i8* %1 to %struct.private_data*, !dbg !716
  store %struct.private_data* %2, %struct.private_data** %state, align 8, !dbg !713
  call void @llvm.dbg.declare(metadata i32* %code, metadata !717, metadata !357), !dbg !718
  call void @llvm.dbg.declare(metadata i64* %ret, metadata !719, metadata !357), !dbg !720
  br label %while.cond, !dbg !721

while.cond:                                       ; preds = %if.end17, %entry
  %3 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !722
  %bits_avail = getelementptr inbounds %struct.private_data, %struct.private_data* %3, i32 0, i32 4, !dbg !724
  %4 = load i32, i32* %bits_avail, align 4, !dbg !724
  %5 = load i32, i32* %n.addr, align 4, !dbg !725
  %cmp = icmp slt i32 %4, %5, !dbg !726
  br i1 %cmp, label %while.body, label %while.end, !dbg !727

while.body:                                       ; preds = %while.cond
  %6 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !728
  %avail_in = getelementptr inbounds %struct.private_data, %struct.private_data* %6, i32 0, i32 1, !dbg !731
  %7 = load i64, i64* %avail_in, align 8, !dbg !731
  %cmp1 = icmp ule i64 %7, 0, !dbg !732
  br i1 %cmp1, label %if.then, label %if.end17, !dbg !733

if.then:                                          ; preds = %while.body
  %8 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !734
  %consume_unnotified = getelementptr inbounds %struct.private_data, %struct.private_data* %8, i32 0, i32 2, !dbg !737
  %9 = load i64, i64* %consume_unnotified, align 8, !dbg !737
  %tobool = icmp ne i64 %9, 0, !dbg !734
  br i1 %tobool, label %if.then2, label %if.end, !dbg !738

if.then2:                                         ; preds = %if.then
  %10 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !739
  %upstream = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %10, i32 0, i32 2, !dbg !741
  %11 = load %struct.archive_read_filter*, %struct.archive_read_filter** %upstream, align 8, !dbg !741
  %12 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !742
  %consume_unnotified3 = getelementptr inbounds %struct.private_data, %struct.private_data* %12, i32 0, i32 2, !dbg !743
  %13 = load i64, i64* %consume_unnotified3, align 8, !dbg !743
  %call = call i64 @__archive_read_filter_consume(%struct.archive_read_filter* %11, i64 %13), !dbg !744
  %14 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !745
  %consume_unnotified4 = getelementptr inbounds %struct.private_data, %struct.private_data* %14, i32 0, i32 2, !dbg !746
  store i64 0, i64* %consume_unnotified4, align 8, !dbg !747
  br label %if.end, !dbg !748

if.end:                                           ; preds = %if.then2, %if.then
  %15 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !749
  %upstream5 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %15, i32 0, i32 2, !dbg !750
  %16 = load %struct.archive_read_filter*, %struct.archive_read_filter** %upstream5, align 8, !dbg !750
  %call6 = call i8* @__archive_read_filter_ahead(%struct.archive_read_filter* %16, i64 1, i64* %ret), !dbg !751
  %17 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !752
  %next_in = getelementptr inbounds %struct.private_data, %struct.private_data* %17, i32 0, i32 0, !dbg !753
  store i8* %call6, i8** %next_in, align 8, !dbg !754
  %18 = load i64, i64* %ret, align 8, !dbg !755
  %cmp7 = icmp eq i64 %18, 0, !dbg !757
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !758

if.then8:                                         ; preds = %if.end
  store i32 -1, i32* %retval, align 4, !dbg !759
  br label %return, !dbg !759

if.end9:                                          ; preds = %if.end
  %19 = load i64, i64* %ret, align 8, !dbg !760
  %cmp10 = icmp slt i64 %19, 0, !dbg !762
  br i1 %cmp10, label %if.then13, label %lor.lhs.false, !dbg !763

lor.lhs.false:                                    ; preds = %if.end9
  %20 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !764
  %next_in11 = getelementptr inbounds %struct.private_data, %struct.private_data* %20, i32 0, i32 0, !dbg !766
  %21 = load i8*, i8** %next_in11, align 8, !dbg !766
  %cmp12 = icmp eq i8* %21, null, !dbg !767
  br i1 %cmp12, label %if.then13, label %if.end14, !dbg !768

if.then13:                                        ; preds = %lor.lhs.false, %if.end9
  store i32 -30, i32* %retval, align 4, !dbg !769
  br label %return, !dbg !769

if.end14:                                         ; preds = %lor.lhs.false
  %22 = load i64, i64* %ret, align 8, !dbg !770
  %23 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !771
  %avail_in15 = getelementptr inbounds %struct.private_data, %struct.private_data* %23, i32 0, i32 1, !dbg !772
  store i64 %22, i64* %avail_in15, align 8, !dbg !773
  %24 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !774
  %consume_unnotified16 = getelementptr inbounds %struct.private_data, %struct.private_data* %24, i32 0, i32 2, !dbg !775
  store i64 %22, i64* %consume_unnotified16, align 8, !dbg !776
  br label %if.end17, !dbg !777

if.end17:                                         ; preds = %if.end14, %while.body
  %25 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !778
  %next_in18 = getelementptr inbounds %struct.private_data, %struct.private_data* %25, i32 0, i32 0, !dbg !779
  %26 = load i8*, i8** %next_in18, align 8, !dbg !780
  %incdec.ptr = getelementptr inbounds i8, i8* %26, i32 1, !dbg !780
  store i8* %incdec.ptr, i8** %next_in18, align 8, !dbg !780
  %27 = load i8, i8* %26, align 1, !dbg !781
  %conv = zext i8 %27 to i32, !dbg !781
  %28 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !782
  %bits_avail19 = getelementptr inbounds %struct.private_data, %struct.private_data* %28, i32 0, i32 4, !dbg !783
  %29 = load i32, i32* %bits_avail19, align 4, !dbg !783
  %shl = shl i32 %conv, %29, !dbg !784
  %30 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !785
  %bit_buffer = getelementptr inbounds %struct.private_data, %struct.private_data* %30, i32 0, i32 3, !dbg !786
  %31 = load i32, i32* %bit_buffer, align 8, !dbg !787
  %or = or i32 %31, %shl, !dbg !787
  store i32 %or, i32* %bit_buffer, align 8, !dbg !787
  %32 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !788
  %avail_in20 = getelementptr inbounds %struct.private_data, %struct.private_data* %32, i32 0, i32 1, !dbg !789
  %33 = load i64, i64* %avail_in20, align 8, !dbg !790
  %dec = add i64 %33, -1, !dbg !790
  store i64 %dec, i64* %avail_in20, align 8, !dbg !790
  %34 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !791
  %bits_avail21 = getelementptr inbounds %struct.private_data, %struct.private_data* %34, i32 0, i32 4, !dbg !792
  %35 = load i32, i32* %bits_avail21, align 4, !dbg !793
  %add = add nsw i32 %35, 8, !dbg !793
  store i32 %add, i32* %bits_avail21, align 4, !dbg !793
  %36 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !794
  %bytes_in_section = getelementptr inbounds %struct.private_data, %struct.private_data* %36, i32 0, i32 5, !dbg !795
  %37 = load i64, i64* %bytes_in_section, align 8, !dbg !796
  %inc = add i64 %37, 1, !dbg !796
  store i64 %inc, i64* %bytes_in_section, align 8, !dbg !796
  br label %while.cond, !dbg !797

while.end:                                        ; preds = %while.cond
  %38 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !799
  %bit_buffer22 = getelementptr inbounds %struct.private_data, %struct.private_data* %38, i32 0, i32 3, !dbg !800
  %39 = load i32, i32* %bit_buffer22, align 8, !dbg !800
  store i32 %39, i32* %code, align 4, !dbg !801
  %40 = load i32, i32* %n.addr, align 4, !dbg !802
  %41 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !803
  %bit_buffer23 = getelementptr inbounds %struct.private_data, %struct.private_data* %41, i32 0, i32 3, !dbg !804
  %42 = load i32, i32* %bit_buffer23, align 8, !dbg !805
  %shr = ashr i32 %42, %40, !dbg !805
  store i32 %shr, i32* %bit_buffer23, align 8, !dbg !805
  %43 = load i32, i32* %n.addr, align 4, !dbg !806
  %44 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !807
  %bits_avail24 = getelementptr inbounds %struct.private_data, %struct.private_data* %44, i32 0, i32 4, !dbg !808
  %45 = load i32, i32* %bits_avail24, align 4, !dbg !809
  %sub = sub nsw i32 %45, %43, !dbg !809
  store i32 %sub, i32* %bits_avail24, align 4, !dbg !809
  %46 = load i32, i32* %code, align 4, !dbg !810
  %47 = load i32, i32* %n.addr, align 4, !dbg !811
  %idxprom = sext i32 %47 to i64, !dbg !812
  %arrayidx = getelementptr inbounds [17 x i32], [17 x i32]* @getbits.mask, i64 0, i64 %idxprom, !dbg !812
  %48 = load i32, i32* %arrayidx, align 4, !dbg !812
  %and = and i32 %46, %48, !dbg !813
  store i32 %and, i32* %retval, align 4, !dbg !814
  br label %return, !dbg !814

return:                                           ; preds = %while.end, %if.then13, %if.then8
  %49 = load i32, i32* %retval, align 4, !dbg !815
  ret i32 %49, !dbg !815
}

; Function Attrs: nounwind uwtable
define internal i32 @next_code(%struct.archive_read_filter* %self) #0 !dbg !338 {
entry:
  %retval = alloca i32, align 4
  %self.addr = alloca %struct.archive_read_filter*, align 8
  %state = alloca %struct.private_data*, align 8
  %code = alloca i32, align 4
  %newcode = alloca i32, align 4
  %skip_bytes = alloca i32, align 4
  store %struct.archive_read_filter* %self, %struct.archive_read_filter** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %self.addr, metadata !816, metadata !357), !dbg !817
  call void @llvm.dbg.declare(metadata %struct.private_data** %state, metadata !818, metadata !357), !dbg !819
  %0 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !820
  %data = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %0, i32 0, i32 10, !dbg !821
  %1 = load i8*, i8** %data, align 8, !dbg !821
  %2 = bitcast i8* %1 to %struct.private_data*, !dbg !822
  store %struct.private_data* %2, %struct.private_data** %state, align 8, !dbg !819
  call void @llvm.dbg.declare(metadata i32* %code, metadata !823, metadata !357), !dbg !824
  call void @llvm.dbg.declare(metadata i32* %newcode, metadata !825, metadata !357), !dbg !826
  %3 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !827
  %4 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !828
  %bits = getelementptr inbounds %struct.private_data, %struct.private_data* %4, i32 0, i32 13, !dbg !829
  %5 = load i32, i32* %bits, align 4, !dbg !829
  %call = call i32 @getbits(%struct.archive_read_filter* %3, i32 %5), !dbg !830
  store i32 %call, i32* %newcode, align 4, !dbg !831
  store i32 %call, i32* %code, align 4, !dbg !832
  %6 = load i32, i32* %code, align 4, !dbg !833
  %cmp = icmp slt i32 %6, 0, !dbg !835
  br i1 %cmp, label %if.then, label %if.end, !dbg !836

if.then:                                          ; preds = %entry
  %7 = load i32, i32* %code, align 4, !dbg !837
  store i32 %7, i32* %retval, align 4, !dbg !838
  br label %return, !dbg !838

if.end:                                           ; preds = %entry
  %8 = load i32, i32* %code, align 4, !dbg !839
  %9 = load i32, i32* @next_code.debug_index, align 4, !dbg !840
  %inc = add i32 %9, 1, !dbg !840
  store i32 %inc, i32* @next_code.debug_index, align 4, !dbg !840
  %idxprom = zext i32 %9 to i64, !dbg !841
  %arrayidx = getelementptr inbounds [1024 x i32], [1024 x i32]* @next_code.debug_buff, i64 0, i64 %idxprom, !dbg !841
  store i32 %8, i32* %arrayidx, align 4, !dbg !842
  %10 = load i32, i32* @next_code.debug_index, align 4, !dbg !843
  %conv = zext i32 %10 to i64, !dbg !843
  %cmp1 = icmp uge i64 %conv, 1024, !dbg !845
  br i1 %cmp1, label %if.then3, label %if.end4, !dbg !846

if.then3:                                         ; preds = %if.end
  store i32 0, i32* @next_code.debug_index, align 4, !dbg !847
  br label %if.end4, !dbg !848

if.end4:                                          ; preds = %if.then3, %if.end
  %11 = load i32, i32* %code, align 4, !dbg !849
  %cmp5 = icmp eq i32 %11, 256, !dbg !851
  br i1 %cmp5, label %land.lhs.true, label %if.end27, !dbg !852

land.lhs.true:                                    ; preds = %if.end4
  %12 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !853
  %use_reset_code = getelementptr inbounds %struct.private_data, %struct.private_data* %12, i32 0, i32 8, !dbg !855
  %13 = load i32, i32* %use_reset_code, align 8, !dbg !855
  %tobool = icmp ne i32 %13, 0, !dbg !853
  br i1 %tobool, label %if.then7, label %if.end27, !dbg !856

if.then7:                                         ; preds = %land.lhs.true
  call void @llvm.dbg.declare(metadata i32* %skip_bytes, metadata !857, metadata !357), !dbg !859
  %14 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !860
  %bits8 = getelementptr inbounds %struct.private_data, %struct.private_data* %14, i32 0, i32 13, !dbg !861
  %15 = load i32, i32* %bits8, align 4, !dbg !861
  %conv9 = sext i32 %15 to i64, !dbg !860
  %16 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !862
  %bytes_in_section = getelementptr inbounds %struct.private_data, %struct.private_data* %16, i32 0, i32 5, !dbg !863
  %17 = load i64, i64* %bytes_in_section, align 8, !dbg !863
  %18 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !864
  %bits10 = getelementptr inbounds %struct.private_data, %struct.private_data* %18, i32 0, i32 13, !dbg !865
  %19 = load i32, i32* %bits10, align 4, !dbg !865
  %conv11 = sext i32 %19 to i64, !dbg !864
  %rem = urem i64 %17, %conv11, !dbg !866
  %sub = sub i64 %conv9, %rem, !dbg !867
  %conv12 = trunc i64 %sub to i32, !dbg !860
  store i32 %conv12, i32* %skip_bytes, align 4, !dbg !859
  %20 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !868
  %bits13 = getelementptr inbounds %struct.private_data, %struct.private_data* %20, i32 0, i32 13, !dbg !869
  %21 = load i32, i32* %bits13, align 4, !dbg !869
  %22 = load i32, i32* %skip_bytes, align 4, !dbg !870
  %rem14 = srem i32 %22, %21, !dbg !870
  store i32 %rem14, i32* %skip_bytes, align 4, !dbg !870
  %23 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !871
  %bits_avail = getelementptr inbounds %struct.private_data, %struct.private_data* %23, i32 0, i32 4, !dbg !872
  store i32 0, i32* %bits_avail, align 4, !dbg !873
  br label %while.cond, !dbg !874

while.cond:                                       ; preds = %if.end21, %if.then7
  %24 = load i32, i32* %skip_bytes, align 4, !dbg !875
  %dec = add nsw i32 %24, -1, !dbg !875
  store i32 %dec, i32* %skip_bytes, align 4, !dbg !875
  %cmp15 = icmp sgt i32 %24, 0, !dbg !877
  br i1 %cmp15, label %while.body, label %while.end, !dbg !878

while.body:                                       ; preds = %while.cond
  %25 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !879
  %call17 = call i32 @getbits(%struct.archive_read_filter* %25, i32 8), !dbg !881
  store i32 %call17, i32* %code, align 4, !dbg !882
  %26 = load i32, i32* %code, align 4, !dbg !883
  %cmp18 = icmp slt i32 %26, 0, !dbg !885
  br i1 %cmp18, label %if.then20, label %if.end21, !dbg !886

if.then20:                                        ; preds = %while.body
  %27 = load i32, i32* %code, align 4, !dbg !887
  store i32 %27, i32* %retval, align 4, !dbg !888
  br label %return, !dbg !888

if.end21:                                         ; preds = %while.body
  br label %while.cond, !dbg !889

while.end:                                        ; preds = %while.cond
  %28 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !891
  %bytes_in_section22 = getelementptr inbounds %struct.private_data, %struct.private_data* %28, i32 0, i32 5, !dbg !892
  store i64 0, i64* %bytes_in_section22, align 8, !dbg !893
  %29 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !894
  %bits23 = getelementptr inbounds %struct.private_data, %struct.private_data* %29, i32 0, i32 13, !dbg !895
  store i32 9, i32* %bits23, align 4, !dbg !896
  %30 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !897
  %bits24 = getelementptr inbounds %struct.private_data, %struct.private_data* %30, i32 0, i32 13, !dbg !898
  %31 = load i32, i32* %bits24, align 4, !dbg !898
  %shl = shl i32 1, %31, !dbg !899
  %sub25 = sub nsw i32 %shl, 1, !dbg !900
  %32 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !901
  %section_end_code = getelementptr inbounds %struct.private_data, %struct.private_data* %32, i32 0, i32 12, !dbg !902
  store i32 %sub25, i32* %section_end_code, align 8, !dbg !903
  %33 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !904
  %free_ent = getelementptr inbounds %struct.private_data, %struct.private_data* %33, i32 0, i32 16, !dbg !905
  store i32 257, i32* %free_ent, align 8, !dbg !906
  %34 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !907
  %oldcode = getelementptr inbounds %struct.private_data, %struct.private_data* %34, i32 0, i32 14, !dbg !908
  store i32 -1, i32* %oldcode, align 8, !dbg !909
  %35 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !910
  %call26 = call i32 @next_code(%struct.archive_read_filter* %35), !dbg !911
  store i32 %call26, i32* %retval, align 4, !dbg !912
  br label %return, !dbg !912

if.end27:                                         ; preds = %land.lhs.true, %if.end4
  %36 = load i32, i32* %code, align 4, !dbg !913
  %37 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !915
  %free_ent28 = getelementptr inbounds %struct.private_data, %struct.private_data* %37, i32 0, i32 16, !dbg !916
  %38 = load i32, i32* %free_ent28, align 8, !dbg !916
  %cmp29 = icmp sgt i32 %36, %38, !dbg !917
  br i1 %cmp29, label %if.then38, label %lor.lhs.false, !dbg !918

lor.lhs.false:                                    ; preds = %if.end27
  %39 = load i32, i32* %code, align 4, !dbg !919
  %40 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !921
  %free_ent31 = getelementptr inbounds %struct.private_data, %struct.private_data* %40, i32 0, i32 16, !dbg !922
  %41 = load i32, i32* %free_ent31, align 8, !dbg !922
  %cmp32 = icmp eq i32 %39, %41, !dbg !923
  br i1 %cmp32, label %land.lhs.true34, label %if.end40, !dbg !924

land.lhs.true34:                                  ; preds = %lor.lhs.false
  %42 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !925
  %oldcode35 = getelementptr inbounds %struct.private_data, %struct.private_data* %42, i32 0, i32 14, !dbg !927
  %43 = load i32, i32* %oldcode35, align 8, !dbg !927
  %cmp36 = icmp slt i32 %43, 0, !dbg !928
  br i1 %cmp36, label %if.then38, label %if.end40, !dbg !929

if.then38:                                        ; preds = %land.lhs.true34, %if.end27
  %44 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !931
  %archive = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %44, i32 0, i32 3, !dbg !933
  %45 = load %struct.archive_read*, %struct.archive_read** %archive, align 8, !dbg !933
  %archive39 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %45, i32 0, i32 0, !dbg !934
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive39, i32 -1, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.3, i32 0, i32 0)), !dbg !935
  store i32 -30, i32* %retval, align 4, !dbg !936
  br label %return, !dbg !936

if.end40:                                         ; preds = %land.lhs.true34, %lor.lhs.false
  %46 = load i32, i32* %code, align 4, !dbg !937
  %47 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !939
  %free_ent41 = getelementptr inbounds %struct.private_data, %struct.private_data* %47, i32 0, i32 16, !dbg !940
  %48 = load i32, i32* %free_ent41, align 8, !dbg !940
  %cmp42 = icmp sge i32 %46, %48, !dbg !941
  br i1 %cmp42, label %if.then44, label %if.end47, !dbg !942

if.then44:                                        ; preds = %if.end40
  %49 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !943
  %finbyte = getelementptr inbounds %struct.private_data, %struct.private_data* %49, i32 0, i32 15, !dbg !945
  %50 = load i32, i32* %finbyte, align 4, !dbg !945
  %conv45 = trunc i32 %50 to i8, !dbg !943
  %51 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !946
  %stackp = getelementptr inbounds %struct.private_data, %struct.private_data* %51, i32 0, i32 19, !dbg !947
  %52 = load i8*, i8** %stackp, align 8, !dbg !948
  %incdec.ptr = getelementptr inbounds i8, i8* %52, i32 1, !dbg !948
  store i8* %incdec.ptr, i8** %stackp, align 8, !dbg !948
  store i8 %conv45, i8* %52, align 1, !dbg !949
  %53 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !950
  %oldcode46 = getelementptr inbounds %struct.private_data, %struct.private_data* %53, i32 0, i32 14, !dbg !951
  %54 = load i32, i32* %oldcode46, align 8, !dbg !951
  store i32 %54, i32* %code, align 4, !dbg !952
  br label %if.end47, !dbg !953

if.end47:                                         ; preds = %if.then44, %if.end40
  br label %while.cond48, !dbg !954

while.cond48:                                     ; preds = %while.body51, %if.end47
  %55 = load i32, i32* %code, align 4, !dbg !955
  %cmp49 = icmp sge i32 %55, 256, !dbg !956
  br i1 %cmp49, label %while.body51, label %while.end59, !dbg !957

while.body51:                                     ; preds = %while.cond48
  %56 = load i32, i32* %code, align 4, !dbg !958
  %idxprom52 = sext i32 %56 to i64, !dbg !960
  %57 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !960
  %suffix = getelementptr inbounds %struct.private_data, %struct.private_data* %57, i32 0, i32 17, !dbg !961
  %arrayidx53 = getelementptr inbounds [65536 x i8], [65536 x i8]* %suffix, i64 0, i64 %idxprom52, !dbg !960
  %58 = load i8, i8* %arrayidx53, align 1, !dbg !960
  %59 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !962
  %stackp54 = getelementptr inbounds %struct.private_data, %struct.private_data* %59, i32 0, i32 19, !dbg !963
  %60 = load i8*, i8** %stackp54, align 8, !dbg !964
  %incdec.ptr55 = getelementptr inbounds i8, i8* %60, i32 1, !dbg !964
  store i8* %incdec.ptr55, i8** %stackp54, align 8, !dbg !964
  store i8 %58, i8* %60, align 1, !dbg !965
  %61 = load i32, i32* %code, align 4, !dbg !966
  %idxprom56 = sext i32 %61 to i64, !dbg !967
  %62 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !967
  %prefix = getelementptr inbounds %struct.private_data, %struct.private_data* %62, i32 0, i32 18, !dbg !968
  %arrayidx57 = getelementptr inbounds [65536 x i16], [65536 x i16]* %prefix, i64 0, i64 %idxprom56, !dbg !967
  %63 = load i16, i16* %arrayidx57, align 2, !dbg !967
  %conv58 = zext i16 %63 to i32, !dbg !967
  store i32 %conv58, i32* %code, align 4, !dbg !969
  br label %while.cond48, !dbg !970

while.end59:                                      ; preds = %while.cond48
  %64 = load i32, i32* %code, align 4, !dbg !972
  %65 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !973
  %finbyte60 = getelementptr inbounds %struct.private_data, %struct.private_data* %65, i32 0, i32 15, !dbg !974
  store i32 %64, i32* %finbyte60, align 4, !dbg !975
  %conv61 = trunc i32 %64 to i8, !dbg !973
  %66 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !976
  %stackp62 = getelementptr inbounds %struct.private_data, %struct.private_data* %66, i32 0, i32 19, !dbg !977
  %67 = load i8*, i8** %stackp62, align 8, !dbg !978
  %incdec.ptr63 = getelementptr inbounds i8, i8* %67, i32 1, !dbg !978
  store i8* %incdec.ptr63, i8** %stackp62, align 8, !dbg !978
  store i8 %conv61, i8* %67, align 1, !dbg !979
  %68 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !980
  %free_ent64 = getelementptr inbounds %struct.private_data, %struct.private_data* %68, i32 0, i32 16, !dbg !981
  %69 = load i32, i32* %free_ent64, align 8, !dbg !981
  store i32 %69, i32* %code, align 4, !dbg !982
  %70 = load i32, i32* %code, align 4, !dbg !983
  %71 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !985
  %maxcode = getelementptr inbounds %struct.private_data, %struct.private_data* %71, i32 0, i32 10, !dbg !986
  %72 = load i32, i32* %maxcode, align 8, !dbg !986
  %cmp65 = icmp slt i32 %70, %72, !dbg !987
  br i1 %cmp65, label %land.lhs.true67, label %if.end84, !dbg !988

land.lhs.true67:                                  ; preds = %while.end59
  %73 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !989
  %oldcode68 = getelementptr inbounds %struct.private_data, %struct.private_data* %73, i32 0, i32 14, !dbg !991
  %74 = load i32, i32* %oldcode68, align 8, !dbg !991
  %cmp69 = icmp sge i32 %74, 0, !dbg !992
  br i1 %cmp69, label %if.then71, label %if.end84, !dbg !993

if.then71:                                        ; preds = %land.lhs.true67
  %75 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !994
  %oldcode72 = getelementptr inbounds %struct.private_data, %struct.private_data* %75, i32 0, i32 14, !dbg !996
  %76 = load i32, i32* %oldcode72, align 8, !dbg !996
  %conv73 = trunc i32 %76 to i16, !dbg !994
  %77 = load i32, i32* %code, align 4, !dbg !997
  %idxprom74 = sext i32 %77 to i64, !dbg !998
  %78 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !998
  %prefix75 = getelementptr inbounds %struct.private_data, %struct.private_data* %78, i32 0, i32 18, !dbg !999
  %arrayidx76 = getelementptr inbounds [65536 x i16], [65536 x i16]* %prefix75, i64 0, i64 %idxprom74, !dbg !998
  store i16 %conv73, i16* %arrayidx76, align 2, !dbg !1000
  %79 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1001
  %finbyte77 = getelementptr inbounds %struct.private_data, %struct.private_data* %79, i32 0, i32 15, !dbg !1002
  %80 = load i32, i32* %finbyte77, align 4, !dbg !1002
  %conv78 = trunc i32 %80 to i8, !dbg !1001
  %81 = load i32, i32* %code, align 4, !dbg !1003
  %idxprom79 = sext i32 %81 to i64, !dbg !1004
  %82 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1004
  %suffix80 = getelementptr inbounds %struct.private_data, %struct.private_data* %82, i32 0, i32 17, !dbg !1005
  %arrayidx81 = getelementptr inbounds [65536 x i8], [65536 x i8]* %suffix80, i64 0, i64 %idxprom79, !dbg !1004
  store i8 %conv78, i8* %arrayidx81, align 1, !dbg !1006
  %83 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1007
  %free_ent82 = getelementptr inbounds %struct.private_data, %struct.private_data* %83, i32 0, i32 16, !dbg !1008
  %84 = load i32, i32* %free_ent82, align 8, !dbg !1009
  %inc83 = add nsw i32 %84, 1, !dbg !1009
  store i32 %inc83, i32* %free_ent82, align 8, !dbg !1009
  br label %if.end84, !dbg !1010

if.end84:                                         ; preds = %if.then71, %land.lhs.true67, %while.end59
  %85 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1011
  %free_ent85 = getelementptr inbounds %struct.private_data, %struct.private_data* %85, i32 0, i32 16, !dbg !1013
  %86 = load i32, i32* %free_ent85, align 8, !dbg !1013
  %87 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1014
  %section_end_code86 = getelementptr inbounds %struct.private_data, %struct.private_data* %87, i32 0, i32 12, !dbg !1015
  %88 = load i32, i32* %section_end_code86, align 8, !dbg !1015
  %cmp87 = icmp sgt i32 %86, %88, !dbg !1016
  br i1 %cmp87, label %if.then89, label %if.end104, !dbg !1017

if.then89:                                        ; preds = %if.end84
  %89 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1018
  %bits90 = getelementptr inbounds %struct.private_data, %struct.private_data* %89, i32 0, i32 13, !dbg !1020
  %90 = load i32, i32* %bits90, align 4, !dbg !1021
  %inc91 = add nsw i32 %90, 1, !dbg !1021
  store i32 %inc91, i32* %bits90, align 4, !dbg !1021
  %91 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1022
  %bytes_in_section92 = getelementptr inbounds %struct.private_data, %struct.private_data* %91, i32 0, i32 5, !dbg !1023
  store i64 0, i64* %bytes_in_section92, align 8, !dbg !1024
  %92 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1025
  %bits93 = getelementptr inbounds %struct.private_data, %struct.private_data* %92, i32 0, i32 13, !dbg !1027
  %93 = load i32, i32* %bits93, align 4, !dbg !1027
  %94 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1028
  %maxcode_bits = getelementptr inbounds %struct.private_data, %struct.private_data* %94, i32 0, i32 11, !dbg !1029
  %95 = load i32, i32* %maxcode_bits, align 4, !dbg !1029
  %cmp94 = icmp eq i32 %93, %95, !dbg !1030
  br i1 %cmp94, label %if.then96, label %if.else, !dbg !1031

if.then96:                                        ; preds = %if.then89
  %96 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1032
  %maxcode97 = getelementptr inbounds %struct.private_data, %struct.private_data* %96, i32 0, i32 10, !dbg !1033
  %97 = load i32, i32* %maxcode97, align 8, !dbg !1033
  %98 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1034
  %section_end_code98 = getelementptr inbounds %struct.private_data, %struct.private_data* %98, i32 0, i32 12, !dbg !1035
  store i32 %97, i32* %section_end_code98, align 8, !dbg !1036
  br label %if.end103, !dbg !1034

if.else:                                          ; preds = %if.then89
  %99 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1037
  %bits99 = getelementptr inbounds %struct.private_data, %struct.private_data* %99, i32 0, i32 13, !dbg !1038
  %100 = load i32, i32* %bits99, align 4, !dbg !1038
  %shl100 = shl i32 1, %100, !dbg !1039
  %sub101 = sub nsw i32 %shl100, 1, !dbg !1040
  %101 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1041
  %section_end_code102 = getelementptr inbounds %struct.private_data, %struct.private_data* %101, i32 0, i32 12, !dbg !1042
  store i32 %sub101, i32* %section_end_code102, align 8, !dbg !1043
  br label %if.end103

if.end103:                                        ; preds = %if.else, %if.then96
  br label %if.end104, !dbg !1044

if.end104:                                        ; preds = %if.end103, %if.end84
  %102 = load i32, i32* %newcode, align 4, !dbg !1045
  %103 = load %struct.private_data*, %struct.private_data** %state, align 8, !dbg !1046
  %oldcode105 = getelementptr inbounds %struct.private_data, %struct.private_data* %103, i32 0, i32 14, !dbg !1047
  store i32 %102, i32* %oldcode105, align 8, !dbg !1048
  store i32 0, i32* %retval, align 4, !dbg !1049
  br label %return, !dbg !1049

return:                                           ; preds = %if.end104, %if.then38, %while.end, %if.then20, %if.then
  %104 = load i32, i32* %retval, align 4, !dbg !1050
  ret i32 %104, !dbg !1050
}

declare i64 @__archive_read_filter_consume(%struct.archive_read_filter*, i64) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!353, !354}
!llvm.ident = !{!355}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !328, globals: !340)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_support_filter_compress.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !122, !291, !323}
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
!292 = !DICompositeType(tag: DW_TAG_structure_type, name: "private_data", file: !1, line: 94, size: 2096128, align: 64, elements: !293)
!293 = !{!294, !298, !299, !300, !301, !302, !303, !304, !305, !306, !307, !308, !309, !310, !311, !312, !313, !314, !318, !322, !324}
!294 = !DIDerivedType(tag: DW_TAG_member, name: "next_in", scope: !292, file: !1, line: 96, baseType: !295, size: 64, align: 64)
!295 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !296, size: 64, align: 64)
!296 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !297)
!297 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!298 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in", scope: !292, file: !1, line: 97, baseType: !45, size: 64, align: 64, offset: 64)
!299 = !DIDerivedType(tag: DW_TAG_member, name: "consume_unnotified", scope: !292, file: !1, line: 98, baseType: !45, size: 64, align: 64, offset: 128)
!300 = !DIDerivedType(tag: DW_TAG_member, name: "bit_buffer", scope: !292, file: !1, line: 99, baseType: !23, size: 32, align: 32, offset: 192)
!301 = !DIDerivedType(tag: DW_TAG_member, name: "bits_avail", scope: !292, file: !1, line: 100, baseType: !23, size: 32, align: 32, offset: 224)
!302 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_in_section", scope: !292, file: !1, line: 101, baseType: !45, size: 64, align: 64, offset: 256)
!303 = !DIDerivedType(tag: DW_TAG_member, name: "out_block_size", scope: !292, file: !1, line: 104, baseType: !45, size: 64, align: 64, offset: 320)
!304 = !DIDerivedType(tag: DW_TAG_member, name: "out_block", scope: !292, file: !1, line: 105, baseType: !122, size: 64, align: 64, offset: 384)
!305 = !DIDerivedType(tag: DW_TAG_member, name: "use_reset_code", scope: !292, file: !1, line: 108, baseType: !23, size: 32, align: 32, offset: 448)
!306 = !DIDerivedType(tag: DW_TAG_member, name: "end_of_stream", scope: !292, file: !1, line: 109, baseType: !23, size: 32, align: 32, offset: 480)
!307 = !DIDerivedType(tag: DW_TAG_member, name: "maxcode", scope: !292, file: !1, line: 110, baseType: !23, size: 32, align: 32, offset: 512)
!308 = !DIDerivedType(tag: DW_TAG_member, name: "maxcode_bits", scope: !292, file: !1, line: 111, baseType: !23, size: 32, align: 32, offset: 544)
!309 = !DIDerivedType(tag: DW_TAG_member, name: "section_end_code", scope: !292, file: !1, line: 112, baseType: !23, size: 32, align: 32, offset: 576)
!310 = !DIDerivedType(tag: DW_TAG_member, name: "bits", scope: !292, file: !1, line: 113, baseType: !23, size: 32, align: 32, offset: 608)
!311 = !DIDerivedType(tag: DW_TAG_member, name: "oldcode", scope: !292, file: !1, line: 114, baseType: !23, size: 32, align: 32, offset: 640)
!312 = !DIDerivedType(tag: DW_TAG_member, name: "finbyte", scope: !292, file: !1, line: 115, baseType: !23, size: 32, align: 32, offset: 672)
!313 = !DIDerivedType(tag: DW_TAG_member, name: "free_ent", scope: !292, file: !1, line: 118, baseType: !23, size: 32, align: 32, offset: 704)
!314 = !DIDerivedType(tag: DW_TAG_member, name: "suffix", scope: !292, file: !1, line: 119, baseType: !315, size: 524288, align: 8, offset: 736)
!315 = !DICompositeType(tag: DW_TAG_array_type, baseType: !297, size: 524288, align: 8, elements: !316)
!316 = !{!317}
!317 = !DISubrange(count: 65536)
!318 = !DIDerivedType(tag: DW_TAG_member, name: "prefix", scope: !292, file: !1, line: 120, baseType: !319, size: 1048576, align: 16, offset: 525024)
!319 = !DICompositeType(tag: DW_TAG_array_type, baseType: !320, size: 1048576, align: 16, elements: !316)
!320 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint16_t", file: !53, line: 49, baseType: !321)
!321 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!322 = !DIDerivedType(tag: DW_TAG_member, name: "stackp", scope: !292, file: !1, line: 130, baseType: !323, size: 64, align: 64, offset: 1573632)
!323 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !297, size: 64, align: 64)
!324 = !DIDerivedType(tag: DW_TAG_member, name: "stack", scope: !292, file: !1, line: 131, baseType: !325, size: 522400, align: 8, offset: 1573696)
!325 = !DICompositeType(tag: DW_TAG_array_type, baseType: !297, size: 522400, align: 8, elements: !326)
!326 = !{!327}
!327 = !DISubrange(count: 65300)
!328 = !{!329, !330, !331, !332, !333, !334, !335, !338, !339}
!329 = distinct !DISubprogram(name: "archive_read_support_compression_compress", scope: !1, file: !1, line: 147, type: !21, isLocal: false, isDefinition: true, scopeLine: 148, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!330 = distinct !DISubprogram(name: "archive_read_support_filter_compress", scope: !1, file: !1, line: 154, type: !21, isLocal: false, isDefinition: true, scopeLine: 155, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!331 = distinct !DISubprogram(name: "compress_bidder_bid", scope: !1, file: !1, line: 179, type: !166, isLocal: true, isDefinition: true, scopeLine: 181, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!332 = distinct !DISubprogram(name: "compress_bidder_init", scope: !1, file: !1, line: 212, type: !178, isLocal: true, isDefinition: true, scopeLine: 213, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!333 = distinct !DISubprogram(name: "compress_filter_read", scope: !1, file: !1, line: 278, type: !182, isLocal: true, isDefinition: true, scopeLine: 279, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!334 = distinct !DISubprogram(name: "compress_filter_close", scope: !1, file: !1, line: 322, type: !178, isLocal: true, isDefinition: true, scopeLine: 323, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!335 = distinct !DISubprogram(name: "getbits", scope: !1, file: !1, line: 428, type: !336, isLocal: true, isDefinition: true, scopeLine: 429, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!336 = !DISubroutineType(types: !337)
!337 = !{!23, !169, !23}
!338 = distinct !DISubprogram(name: "next_code", scope: !1, file: !1, line: 337, type: !178, isLocal: true, isDefinition: true, scopeLine: 338, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!339 = distinct !DISubprogram(name: "compress_bidder_free", scope: !1, file: !1, line: 312, type: !218, isLocal: true, isDefinition: true, scopeLine: 313, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!340 = !{!341, !343, !348, !352}
!341 = !DIGlobalVariable(name: "out_block_size", scope: !332, file: !1, line: 215, type: !342, isLocal: true, isDefinition: true, variable: i64* @compress_bidder_init.out_block_size)
!342 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !45)
!343 = !DIGlobalVariable(name: "mask", scope: !335, file: !1, line: 433, type: !344, isLocal: true, isDefinition: true, variable: [17 x i32]* @getbits.mask)
!344 = !DICompositeType(tag: DW_TAG_array_type, baseType: !345, size: 544, align: 32, elements: !346)
!345 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !23)
!346 = !{!347}
!347 = !DISubrange(count: 17)
!348 = !DIGlobalVariable(name: "debug_buff", scope: !338, file: !1, line: 342, type: !349, isLocal: true, isDefinition: true, variable: [1024 x i32]* @next_code.debug_buff)
!349 = !DICompositeType(tag: DW_TAG_array_type, baseType: !23, size: 32768, align: 32, elements: !350)
!350 = !{!351}
!351 = !DISubrange(count: 1024)
!352 = !DIGlobalVariable(name: "debug_index", scope: !338, file: !1, line: 343, type: !13, isLocal: true, isDefinition: true, variable: i32* @next_code.debug_index)
!353 = !{i32 2, !"Dwarf Version", i32 4}
!354 = !{i32 2, !"Debug Info Version", i32 3}
!355 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!356 = !DILocalVariable(name: "a", arg: 1, scope: !329, file: !1, line: 147, type: !24)
!357 = !DIExpression()
!358 = !DILocation(line: 147, column: 59, scope: !329)
!359 = !DILocation(line: 149, column: 46, scope: !329)
!360 = !DILocation(line: 149, column: 9, scope: !329)
!361 = !DILocation(line: 149, column: 2, scope: !329)
!362 = !DILocalVariable(name: "_a", arg: 1, scope: !330, file: !1, line: 154, type: !24)
!363 = !DILocation(line: 154, column: 54, scope: !330)
!364 = !DILocalVariable(name: "a", scope: !330, file: !1, line: 156, type: !4)
!365 = !DILocation(line: 156, column: 23, scope: !330)
!366 = !DILocation(line: 156, column: 50, scope: !330)
!367 = !DILocation(line: 156, column: 27, scope: !330)
!368 = !DILocalVariable(name: "bidder", scope: !330, file: !1, line: 157, type: !168)
!369 = !DILocation(line: 157, column: 37, scope: !330)
!370 = !DILocation(line: 159, column: 2, scope: !330)
!371 = !DILocalVariable(name: "magic_test", scope: !372, file: !1, line: 159, type: !23)
!372 = distinct !DILexicalBlock(scope: !330, file: !1, line: 159, column: 2)
!373 = !DILocation(line: 159, column: 2, scope: !372)
!374 = !DILocation(line: 159, column: 2, scope: !375)
!375 = !DILexicalBlockFile(scope: !372, file: !1, discriminator: 1)
!376 = !DILocation(line: 159, column: 2, scope: !377)
!377 = !DILexicalBlockFile(scope: !378, file: !1, discriminator: 2)
!378 = distinct !DILexicalBlock(scope: !372, file: !1, line: 159, column: 2)
!379 = !DILocation(line: 159, column: 2, scope: !380)
!380 = !DILexicalBlockFile(scope: !372, file: !1, discriminator: 3)
!381 = !DILocation(line: 162, column: 32, scope: !382)
!382 = distinct !DILexicalBlock(scope: !330, file: !1, line: 162, column: 6)
!383 = !DILocation(line: 162, column: 6, scope: !382)
!384 = !DILocation(line: 162, column: 44, scope: !382)
!385 = !DILocation(line: 162, column: 6, scope: !330)
!386 = !DILocation(line: 163, column: 3, scope: !382)
!387 = !DILocation(line: 165, column: 2, scope: !330)
!388 = !DILocation(line: 165, column: 10, scope: !330)
!389 = !DILocation(line: 165, column: 15, scope: !330)
!390 = !DILocation(line: 166, column: 2, scope: !330)
!391 = !DILocation(line: 166, column: 10, scope: !330)
!392 = !DILocation(line: 166, column: 15, scope: !330)
!393 = !DILocation(line: 167, column: 2, scope: !330)
!394 = !DILocation(line: 167, column: 10, scope: !330)
!395 = !DILocation(line: 167, column: 14, scope: !330)
!396 = !DILocation(line: 168, column: 2, scope: !330)
!397 = !DILocation(line: 168, column: 10, scope: !330)
!398 = !DILocation(line: 168, column: 15, scope: !330)
!399 = !DILocation(line: 169, column: 2, scope: !330)
!400 = !DILocation(line: 169, column: 10, scope: !330)
!401 = !DILocation(line: 169, column: 18, scope: !330)
!402 = !DILocation(line: 170, column: 2, scope: !330)
!403 = !DILocation(line: 170, column: 10, scope: !330)
!404 = !DILocation(line: 170, column: 15, scope: !330)
!405 = !DILocation(line: 171, column: 2, scope: !330)
!406 = !DILocation(line: 172, column: 1, scope: !330)
!407 = !DILocalVariable(name: "self", arg: 1, scope: !331, file: !1, line: 179, type: !168)
!408 = !DILocation(line: 179, column: 56, scope: !331)
!409 = !DILocalVariable(name: "filter", arg: 2, scope: !331, file: !1, line: 180, type: !169)
!410 = !DILocation(line: 180, column: 33, scope: !331)
!411 = !DILocalVariable(name: "buffer", scope: !331, file: !1, line: 182, type: !295)
!412 = !DILocation(line: 182, column: 23, scope: !331)
!413 = !DILocalVariable(name: "avail", scope: !331, file: !1, line: 183, type: !38)
!414 = !DILocation(line: 183, column: 10, scope: !331)
!415 = !DILocalVariable(name: "bits_checked", scope: !331, file: !1, line: 184, type: !23)
!416 = !DILocation(line: 184, column: 6, scope: !331)
!417 = !DILocation(line: 186, column: 8, scope: !331)
!418 = !DILocation(line: 189, column: 39, scope: !331)
!419 = !DILocation(line: 189, column: 11, scope: !331)
!420 = !DILocation(line: 189, column: 9, scope: !331)
!421 = !DILocation(line: 191, column: 6, scope: !422)
!422 = distinct !DILexicalBlock(scope: !331, file: !1, line: 191, column: 6)
!423 = !DILocation(line: 191, column: 13, scope: !422)
!424 = !DILocation(line: 191, column: 6, scope: !331)
!425 = !DILocation(line: 192, column: 3, scope: !422)
!426 = !DILocation(line: 194, column: 15, scope: !331)
!427 = !DILocation(line: 196, column: 6, scope: !428)
!428 = distinct !DILexicalBlock(scope: !331, file: !1, line: 196, column: 6)
!429 = !DILocation(line: 196, column: 16, scope: !428)
!430 = !DILocation(line: 196, column: 24, scope: !428)
!431 = !DILocation(line: 196, column: 27, scope: !432)
!432 = !DILexicalBlockFile(scope: !428, file: !1, discriminator: 1)
!433 = !DILocation(line: 196, column: 37, scope: !432)
!434 = !DILocation(line: 196, column: 6, scope: !432)
!435 = !DILocation(line: 197, column: 3, scope: !428)
!436 = !DILocation(line: 199, column: 6, scope: !437)
!437 = distinct !DILexicalBlock(scope: !331, file: !1, line: 199, column: 6)
!438 = !DILocation(line: 199, column: 16, scope: !437)
!439 = !DILocation(line: 199, column: 6, scope: !331)
!440 = !DILocation(line: 200, column: 3, scope: !437)
!441 = !DILocation(line: 201, column: 6, scope: !442)
!442 = distinct !DILexicalBlock(scope: !331, file: !1, line: 201, column: 6)
!443 = !DILocation(line: 201, column: 16, scope: !442)
!444 = !DILocation(line: 201, column: 6, scope: !331)
!445 = !DILocation(line: 202, column: 3, scope: !442)
!446 = !DILocation(line: 203, column: 15, scope: !331)
!447 = !DILocation(line: 205, column: 10, scope: !331)
!448 = !DILocation(line: 205, column: 2, scope: !331)
!449 = !DILocation(line: 206, column: 1, scope: !331)
!450 = !DILocalVariable(name: "self", arg: 1, scope: !332, file: !1, line: 212, type: !169)
!451 = !DILocation(line: 212, column: 50, scope: !332)
!452 = !DILocalVariable(name: "state", scope: !332, file: !1, line: 214, type: !291)
!453 = !DILocation(line: 214, column: 23, scope: !332)
!454 = !DILocalVariable(name: "out_block", scope: !332, file: !1, line: 216, type: !122)
!455 = !DILocation(line: 216, column: 8, scope: !332)
!456 = !DILocalVariable(name: "code", scope: !332, file: !1, line: 217, type: !23)
!457 = !DILocation(line: 217, column: 6, scope: !332)
!458 = !DILocation(line: 219, column: 2, scope: !332)
!459 = !DILocation(line: 219, column: 8, scope: !332)
!460 = !DILocation(line: 219, column: 13, scope: !332)
!461 = !DILocation(line: 220, column: 2, scope: !332)
!462 = !DILocation(line: 220, column: 8, scope: !332)
!463 = !DILocation(line: 220, column: 13, scope: !332)
!464 = !DILocation(line: 222, column: 33, scope: !332)
!465 = !DILocation(line: 222, column: 10, scope: !332)
!466 = !DILocation(line: 222, column: 8, scope: !332)
!467 = !DILocation(line: 223, column: 14, scope: !332)
!468 = !DILocation(line: 223, column: 12, scope: !332)
!469 = !DILocation(line: 224, column: 6, scope: !470)
!470 = distinct !DILexicalBlock(scope: !332, file: !1, line: 224, column: 6)
!471 = !DILocation(line: 224, column: 12, scope: !470)
!472 = !DILocation(line: 224, column: 20, scope: !470)
!473 = !DILocation(line: 224, column: 23, scope: !474)
!474 = !DILexicalBlockFile(scope: !470, file: !1, discriminator: 1)
!475 = !DILocation(line: 224, column: 33, scope: !474)
!476 = !DILocation(line: 224, column: 6, scope: !474)
!477 = !DILocation(line: 225, column: 8, scope: !478)
!478 = distinct !DILexicalBlock(scope: !470, file: !1, line: 224, column: 42)
!479 = !DILocation(line: 225, column: 3, scope: !478)
!480 = !DILocation(line: 226, column: 8, scope: !478)
!481 = !DILocation(line: 226, column: 3, scope: !478)
!482 = !DILocation(line: 227, column: 22, scope: !478)
!483 = !DILocation(line: 227, column: 28, scope: !478)
!484 = !DILocation(line: 227, column: 37, scope: !478)
!485 = !DILocation(line: 229, column: 7, scope: !478)
!486 = !DILocation(line: 229, column: 13, scope: !478)
!487 = !DILocation(line: 227, column: 3, scope: !478)
!488 = !DILocation(line: 230, column: 3, scope: !478)
!489 = !DILocation(line: 233, column: 15, scope: !332)
!490 = !DILocation(line: 233, column: 2, scope: !332)
!491 = !DILocation(line: 233, column: 8, scope: !332)
!492 = !DILocation(line: 233, column: 13, scope: !332)
!493 = !DILocation(line: 234, column: 2, scope: !332)
!494 = !DILocation(line: 234, column: 9, scope: !332)
!495 = !DILocation(line: 234, column: 24, scope: !332)
!496 = !DILocation(line: 235, column: 21, scope: !332)
!497 = !DILocation(line: 235, column: 2, scope: !332)
!498 = !DILocation(line: 235, column: 9, scope: !332)
!499 = !DILocation(line: 235, column: 19, scope: !332)
!500 = !DILocation(line: 236, column: 2, scope: !332)
!501 = !DILocation(line: 236, column: 8, scope: !332)
!502 = !DILocation(line: 236, column: 13, scope: !332)
!503 = !DILocation(line: 237, column: 2, scope: !332)
!504 = !DILocation(line: 237, column: 8, scope: !332)
!505 = !DILocation(line: 237, column: 13, scope: !332)
!506 = !DILocation(line: 238, column: 2, scope: !332)
!507 = !DILocation(line: 238, column: 8, scope: !332)
!508 = !DILocation(line: 238, column: 14, scope: !332)
!509 = !DILocation(line: 242, column: 16, scope: !332)
!510 = !DILocation(line: 242, column: 8, scope: !332)
!511 = !DILocation(line: 243, column: 16, scope: !332)
!512 = !DILocation(line: 243, column: 8, scope: !332)
!513 = !DILocation(line: 246, column: 17, scope: !332)
!514 = !DILocation(line: 246, column: 9, scope: !332)
!515 = !DILocation(line: 246, column: 7, scope: !332)
!516 = !DILocation(line: 247, column: 7, scope: !517)
!517 = distinct !DILexicalBlock(scope: !332, file: !1, line: 247, column: 6)
!518 = !DILocation(line: 247, column: 12, scope: !517)
!519 = !DILocation(line: 247, column: 20, scope: !517)
!520 = !DILocation(line: 247, column: 6, scope: !332)
!521 = !DILocation(line: 248, column: 22, scope: !522)
!522 = distinct !DILexicalBlock(scope: !517, file: !1, line: 247, column: 26)
!523 = !DILocation(line: 248, column: 28, scope: !522)
!524 = !DILocation(line: 248, column: 37, scope: !522)
!525 = !DILocation(line: 248, column: 3, scope: !522)
!526 = !DILocation(line: 250, column: 3, scope: !522)
!527 = !DILocation(line: 252, column: 24, scope: !332)
!528 = !DILocation(line: 252, column: 29, scope: !332)
!529 = !DILocation(line: 252, column: 2, scope: !332)
!530 = !DILocation(line: 252, column: 9, scope: !332)
!531 = !DILocation(line: 252, column: 22, scope: !332)
!532 = !DILocation(line: 253, column: 25, scope: !332)
!533 = !DILocation(line: 253, column: 32, scope: !332)
!534 = !DILocation(line: 253, column: 22, scope: !332)
!535 = !DILocation(line: 253, column: 2, scope: !332)
!536 = !DILocation(line: 253, column: 9, scope: !332)
!537 = !DILocation(line: 253, column: 17, scope: !332)
!538 = !DILocation(line: 254, column: 26, scope: !332)
!539 = !DILocation(line: 254, column: 31, scope: !332)
!540 = !DILocation(line: 254, column: 2, scope: !332)
!541 = !DILocation(line: 254, column: 9, scope: !332)
!542 = !DILocation(line: 254, column: 24, scope: !332)
!543 = !DILocation(line: 257, column: 2, scope: !332)
!544 = !DILocation(line: 257, column: 9, scope: !332)
!545 = !DILocation(line: 257, column: 18, scope: !332)
!546 = !DILocation(line: 258, column: 18, scope: !332)
!547 = !DILocation(line: 258, column: 25, scope: !332)
!548 = !DILocation(line: 258, column: 2, scope: !332)
!549 = !DILocation(line: 258, column: 9, scope: !332)
!550 = !DILocation(line: 258, column: 16, scope: !332)
!551 = !DILocation(line: 259, column: 6, scope: !552)
!552 = distinct !DILexicalBlock(scope: !332, file: !1, line: 259, column: 6)
!553 = !DILocation(line: 259, column: 13, scope: !552)
!554 = !DILocation(line: 259, column: 6, scope: !332)
!555 = !DILocation(line: 260, column: 3, scope: !552)
!556 = !DILocation(line: 260, column: 10, scope: !552)
!557 = !DILocation(line: 260, column: 18, scope: !552)
!558 = !DILocation(line: 261, column: 2, scope: !332)
!559 = !DILocation(line: 261, column: 9, scope: !332)
!560 = !DILocation(line: 261, column: 14, scope: !332)
!561 = !DILocation(line: 262, column: 32, scope: !332)
!562 = !DILocation(line: 262, column: 39, scope: !332)
!563 = !DILocation(line: 262, column: 30, scope: !332)
!564 = !DILocation(line: 262, column: 45, scope: !332)
!565 = !DILocation(line: 262, column: 2, scope: !332)
!566 = !DILocation(line: 262, column: 9, scope: !332)
!567 = !DILocation(line: 262, column: 26, scope: !332)
!568 = !DILocation(line: 263, column: 2, scope: !332)
!569 = !DILocation(line: 263, column: 9, scope: !332)
!570 = !DILocation(line: 263, column: 17, scope: !332)
!571 = !DILocation(line: 264, column: 12, scope: !572)
!572 = distinct !DILexicalBlock(scope: !332, file: !1, line: 264, column: 2)
!573 = !DILocation(line: 264, column: 7, scope: !572)
!574 = !DILocation(line: 264, column: 19, scope: !575)
!575 = !DILexicalBlockFile(scope: !576, file: !1, discriminator: 1)
!576 = distinct !DILexicalBlock(scope: !572, file: !1, line: 264, column: 2)
!577 = !DILocation(line: 264, column: 24, scope: !575)
!578 = !DILocation(line: 264, column: 2, scope: !575)
!579 = !DILocation(line: 265, column: 17, scope: !580)
!580 = distinct !DILexicalBlock(scope: !576, file: !1, line: 264, column: 38)
!581 = !DILocation(line: 265, column: 3, scope: !580)
!582 = !DILocation(line: 265, column: 10, scope: !580)
!583 = !DILocation(line: 265, column: 23, scope: !580)
!584 = !DILocation(line: 266, column: 25, scope: !580)
!585 = !DILocation(line: 266, column: 17, scope: !580)
!586 = !DILocation(line: 266, column: 3, scope: !580)
!587 = !DILocation(line: 266, column: 10, scope: !580)
!588 = !DILocation(line: 266, column: 23, scope: !580)
!589 = !DILocation(line: 267, column: 2, scope: !580)
!590 = !DILocation(line: 264, column: 34, scope: !591)
!591 = !DILexicalBlockFile(scope: !576, file: !1, discriminator: 2)
!592 = !DILocation(line: 264, column: 2, scope: !591)
!593 = !DILocation(line: 268, column: 12, scope: !332)
!594 = !DILocation(line: 268, column: 2, scope: !332)
!595 = !DILocation(line: 270, column: 2, scope: !332)
!596 = !DILocation(line: 271, column: 1, scope: !332)
!597 = !DILocalVariable(name: "self", arg: 1, scope: !339, file: !1, line: 312, type: !168)
!598 = !DILocation(line: 312, column: 57, scope: !339)
!599 = !DILocation(line: 314, column: 2, scope: !339)
!600 = !DILocation(line: 314, column: 8, scope: !339)
!601 = !DILocation(line: 314, column: 13, scope: !339)
!602 = !DILocation(line: 315, column: 2, scope: !339)
!603 = !DILocalVariable(name: "self", arg: 1, scope: !333, file: !1, line: 278, type: !169)
!604 = !DILocation(line: 278, column: 50, scope: !333)
!605 = !DILocalVariable(name: "pblock", arg: 2, scope: !333, file: !1, line: 278, type: !64)
!606 = !DILocation(line: 278, column: 69, scope: !333)
!607 = !DILocalVariable(name: "state", scope: !333, file: !1, line: 280, type: !291)
!608 = !DILocation(line: 280, column: 23, scope: !333)
!609 = !DILocalVariable(name: "p", scope: !333, file: !1, line: 281, type: !323)
!610 = !DILocation(line: 281, column: 17, scope: !333)
!611 = !DILocalVariable(name: "start", scope: !333, file: !1, line: 281, type: !323)
!612 = !DILocation(line: 281, column: 21, scope: !333)
!613 = !DILocalVariable(name: "end", scope: !333, file: !1, line: 281, type: !323)
!614 = !DILocation(line: 281, column: 29, scope: !333)
!615 = !DILocalVariable(name: "ret", scope: !333, file: !1, line: 282, type: !23)
!616 = !DILocation(line: 282, column: 6, scope: !333)
!617 = !DILocation(line: 284, column: 33, scope: !333)
!618 = !DILocation(line: 284, column: 39, scope: !333)
!619 = !DILocation(line: 284, column: 10, scope: !333)
!620 = !DILocation(line: 284, column: 8, scope: !333)
!621 = !DILocation(line: 285, column: 6, scope: !622)
!622 = distinct !DILexicalBlock(scope: !333, file: !1, line: 285, column: 6)
!623 = !DILocation(line: 285, column: 13, scope: !622)
!624 = !DILocation(line: 285, column: 6, scope: !333)
!625 = !DILocation(line: 286, column: 4, scope: !626)
!626 = distinct !DILexicalBlock(scope: !622, file: !1, line: 285, column: 28)
!627 = !DILocation(line: 286, column: 11, scope: !626)
!628 = !DILocation(line: 287, column: 3, scope: !626)
!629 = !DILocation(line: 289, column: 31, scope: !333)
!630 = !DILocation(line: 289, column: 38, scope: !333)
!631 = !DILocation(line: 289, column: 12, scope: !333)
!632 = !DILocation(line: 289, column: 4, scope: !333)
!633 = !DILocation(line: 290, column: 8, scope: !333)
!634 = !DILocation(line: 290, column: 16, scope: !333)
!635 = !DILocation(line: 290, column: 23, scope: !333)
!636 = !DILocation(line: 290, column: 14, scope: !333)
!637 = !DILocation(line: 290, column: 6, scope: !333)
!638 = !DILocation(line: 292, column: 2, scope: !333)
!639 = !DILocation(line: 292, column: 9, scope: !640)
!640 = !DILexicalBlockFile(scope: !333, file: !1, discriminator: 1)
!641 = !DILocation(line: 292, column: 13, scope: !640)
!642 = !DILocation(line: 292, column: 11, scope: !640)
!643 = !DILocation(line: 292, column: 17, scope: !640)
!644 = !DILocation(line: 292, column: 21, scope: !645)
!645 = !DILexicalBlockFile(scope: !333, file: !1, discriminator: 2)
!646 = !DILocation(line: 292, column: 28, scope: !645)
!647 = !DILocation(line: 292, column: 20, scope: !645)
!648 = !DILocation(line: 292, column: 2, scope: !649)
!649 = !DILexicalBlockFile(scope: !333, file: !1, discriminator: 3)
!650 = !DILocation(line: 293, column: 7, scope: !651)
!651 = distinct !DILexicalBlock(scope: !652, file: !1, line: 293, column: 7)
!652 = distinct !DILexicalBlock(scope: !333, file: !1, line: 292, column: 43)
!653 = !DILocation(line: 293, column: 14, scope: !651)
!654 = !DILocation(line: 293, column: 23, scope: !651)
!655 = !DILocation(line: 293, column: 30, scope: !651)
!656 = !DILocation(line: 293, column: 21, scope: !651)
!657 = !DILocation(line: 293, column: 7, scope: !652)
!658 = !DILocation(line: 294, column: 14, scope: !659)
!659 = distinct !DILexicalBlock(scope: !651, file: !1, line: 293, column: 37)
!660 = !DILocation(line: 294, column: 21, scope: !659)
!661 = !DILocation(line: 294, column: 12, scope: !659)
!662 = !DILocation(line: 294, column: 11, scope: !659)
!663 = !DILocation(line: 294, column: 6, scope: !659)
!664 = !DILocation(line: 294, column: 9, scope: !659)
!665 = !DILocation(line: 295, column: 3, scope: !659)
!666 = !DILocation(line: 296, column: 20, scope: !667)
!667 = distinct !DILexicalBlock(scope: !651, file: !1, line: 295, column: 10)
!668 = !DILocation(line: 296, column: 10, scope: !667)
!669 = !DILocation(line: 296, column: 8, scope: !667)
!670 = !DILocation(line: 297, column: 8, scope: !671)
!671 = distinct !DILexicalBlock(scope: !667, file: !1, line: 297, column: 8)
!672 = !DILocation(line: 297, column: 12, scope: !671)
!673 = !DILocation(line: 297, column: 8, scope: !667)
!674 = !DILocation(line: 298, column: 28, scope: !671)
!675 = !DILocation(line: 298, column: 5, scope: !671)
!676 = !DILocation(line: 298, column: 12, scope: !671)
!677 = !DILocation(line: 298, column: 26, scope: !671)
!678 = !DILocation(line: 299, column: 13, scope: !679)
!679 = distinct !DILexicalBlock(scope: !671, file: !1, line: 299, column: 13)
!680 = !DILocation(line: 299, column: 17, scope: !679)
!681 = !DILocation(line: 299, column: 13, scope: !671)
!682 = !DILocation(line: 300, column: 13, scope: !679)
!683 = !DILocation(line: 300, column: 12, scope: !679)
!684 = !DILocation(line: 300, column: 5, scope: !679)
!685 = !DILocation(line: 292, column: 2, scope: !686)
!686 = !DILexicalBlockFile(scope: !333, file: !1, discriminator: 4)
!687 = !DILocation(line: 304, column: 12, scope: !333)
!688 = !DILocation(line: 304, column: 3, scope: !333)
!689 = !DILocation(line: 304, column: 10, scope: !333)
!690 = !DILocation(line: 305, column: 10, scope: !333)
!691 = !DILocation(line: 305, column: 14, scope: !333)
!692 = !DILocation(line: 305, column: 12, scope: !333)
!693 = !DILocation(line: 305, column: 2, scope: !333)
!694 = !DILocation(line: 306, column: 1, scope: !333)
!695 = !DILocalVariable(name: "self", arg: 1, scope: !334, file: !1, line: 322, type: !169)
!696 = !DILocation(line: 322, column: 51, scope: !334)
!697 = !DILocalVariable(name: "state", scope: !334, file: !1, line: 324, type: !291)
!698 = !DILocation(line: 324, column: 23, scope: !334)
!699 = !DILocation(line: 324, column: 54, scope: !334)
!700 = !DILocation(line: 324, column: 60, scope: !334)
!701 = !DILocation(line: 324, column: 31, scope: !334)
!702 = !DILocation(line: 326, column: 7, scope: !334)
!703 = !DILocation(line: 326, column: 14, scope: !334)
!704 = !DILocation(line: 326, column: 2, scope: !334)
!705 = !DILocation(line: 327, column: 7, scope: !334)
!706 = !DILocation(line: 327, column: 2, scope: !334)
!707 = !DILocation(line: 328, column: 2, scope: !334)
!708 = !DILocalVariable(name: "self", arg: 1, scope: !335, file: !1, line: 428, type: !169)
!709 = !DILocation(line: 428, column: 37, scope: !335)
!710 = !DILocalVariable(name: "n", arg: 2, scope: !335, file: !1, line: 428, type: !23)
!711 = !DILocation(line: 428, column: 47, scope: !335)
!712 = !DILocalVariable(name: "state", scope: !335, file: !1, line: 430, type: !291)
!713 = !DILocation(line: 430, column: 23, scope: !335)
!714 = !DILocation(line: 430, column: 54, scope: !335)
!715 = !DILocation(line: 430, column: 60, scope: !335)
!716 = !DILocation(line: 430, column: 31, scope: !335)
!717 = !DILocalVariable(name: "code", scope: !335, file: !1, line: 431, type: !23)
!718 = !DILocation(line: 431, column: 6, scope: !335)
!719 = !DILocalVariable(name: "ret", scope: !335, file: !1, line: 432, type: !38)
!720 = !DILocation(line: 432, column: 10, scope: !335)
!721 = !DILocation(line: 438, column: 2, scope: !335)
!722 = !DILocation(line: 438, column: 9, scope: !723)
!723 = !DILexicalBlockFile(scope: !335, file: !1, discriminator: 1)
!724 = !DILocation(line: 438, column: 16, scope: !723)
!725 = !DILocation(line: 438, column: 29, scope: !723)
!726 = !DILocation(line: 438, column: 27, scope: !723)
!727 = !DILocation(line: 438, column: 2, scope: !723)
!728 = !DILocation(line: 439, column: 7, scope: !729)
!729 = distinct !DILexicalBlock(scope: !730, file: !1, line: 439, column: 7)
!730 = distinct !DILexicalBlock(scope: !335, file: !1, line: 438, column: 32)
!731 = !DILocation(line: 439, column: 14, scope: !729)
!732 = !DILocation(line: 439, column: 23, scope: !729)
!733 = !DILocation(line: 439, column: 7, scope: !730)
!734 = !DILocation(line: 440, column: 8, scope: !735)
!735 = distinct !DILexicalBlock(scope: !736, file: !1, line: 440, column: 8)
!736 = distinct !DILexicalBlock(scope: !729, file: !1, line: 439, column: 29)
!737 = !DILocation(line: 440, column: 15, scope: !735)
!738 = !DILocation(line: 440, column: 8, scope: !736)
!739 = !DILocation(line: 441, column: 35, scope: !740)
!740 = distinct !DILexicalBlock(scope: !735, file: !1, line: 440, column: 35)
!741 = !DILocation(line: 441, column: 41, scope: !740)
!742 = !DILocation(line: 442, column: 6, scope: !740)
!743 = !DILocation(line: 442, column: 13, scope: !740)
!744 = !DILocation(line: 441, column: 5, scope: !740)
!745 = !DILocation(line: 443, column: 5, scope: !740)
!746 = !DILocation(line: 443, column: 12, scope: !740)
!747 = !DILocation(line: 443, column: 31, scope: !740)
!748 = !DILocation(line: 444, column: 4, scope: !740)
!749 = !DILocation(line: 446, column: 38, scope: !736)
!750 = !DILocation(line: 446, column: 44, scope: !736)
!751 = !DILocation(line: 446, column: 10, scope: !736)
!752 = !DILocation(line: 445, column: 4, scope: !736)
!753 = !DILocation(line: 445, column: 11, scope: !736)
!754 = !DILocation(line: 446, column: 8, scope: !736)
!755 = !DILocation(line: 448, column: 8, scope: !756)
!756 = distinct !DILexicalBlock(scope: !736, file: !1, line: 448, column: 8)
!757 = !DILocation(line: 448, column: 12, scope: !756)
!758 = !DILocation(line: 448, column: 8, scope: !736)
!759 = !DILocation(line: 449, column: 5, scope: !756)
!760 = !DILocation(line: 450, column: 8, scope: !761)
!761 = distinct !DILexicalBlock(scope: !736, file: !1, line: 450, column: 8)
!762 = !DILocation(line: 450, column: 12, scope: !761)
!763 = !DILocation(line: 450, column: 16, scope: !761)
!764 = !DILocation(line: 450, column: 19, scope: !765)
!765 = !DILexicalBlockFile(scope: !761, file: !1, discriminator: 1)
!766 = !DILocation(line: 450, column: 26, scope: !765)
!767 = !DILocation(line: 450, column: 34, scope: !765)
!768 = !DILocation(line: 450, column: 8, scope: !765)
!769 = !DILocation(line: 451, column: 5, scope: !761)
!770 = !DILocation(line: 452, column: 50, scope: !736)
!771 = !DILocation(line: 452, column: 32, scope: !736)
!772 = !DILocation(line: 452, column: 39, scope: !736)
!773 = !DILocation(line: 452, column: 48, scope: !736)
!774 = !DILocation(line: 452, column: 4, scope: !736)
!775 = !DILocation(line: 452, column: 11, scope: !736)
!776 = !DILocation(line: 452, column: 30, scope: !736)
!777 = !DILocation(line: 453, column: 3, scope: !736)
!778 = !DILocation(line: 454, column: 25, scope: !730)
!779 = !DILocation(line: 454, column: 32, scope: !730)
!780 = !DILocation(line: 454, column: 39, scope: !730)
!781 = !DILocation(line: 454, column: 24, scope: !730)
!782 = !DILocation(line: 454, column: 45, scope: !730)
!783 = !DILocation(line: 454, column: 52, scope: !730)
!784 = !DILocation(line: 454, column: 42, scope: !730)
!785 = !DILocation(line: 454, column: 3, scope: !730)
!786 = !DILocation(line: 454, column: 10, scope: !730)
!787 = !DILocation(line: 454, column: 21, scope: !730)
!788 = !DILocation(line: 455, column: 3, scope: !730)
!789 = !DILocation(line: 455, column: 10, scope: !730)
!790 = !DILocation(line: 455, column: 18, scope: !730)
!791 = !DILocation(line: 456, column: 3, scope: !730)
!792 = !DILocation(line: 456, column: 10, scope: !730)
!793 = !DILocation(line: 456, column: 21, scope: !730)
!794 = !DILocation(line: 457, column: 3, scope: !730)
!795 = !DILocation(line: 457, column: 10, scope: !730)
!796 = !DILocation(line: 457, column: 26, scope: !730)
!797 = !DILocation(line: 438, column: 2, scope: !798)
!798 = !DILexicalBlockFile(scope: !335, file: !1, discriminator: 2)
!799 = !DILocation(line: 460, column: 9, scope: !335)
!800 = !DILocation(line: 460, column: 16, scope: !335)
!801 = !DILocation(line: 460, column: 7, scope: !335)
!802 = !DILocation(line: 461, column: 24, scope: !335)
!803 = !DILocation(line: 461, column: 2, scope: !335)
!804 = !DILocation(line: 461, column: 9, scope: !335)
!805 = !DILocation(line: 461, column: 20, scope: !335)
!806 = !DILocation(line: 462, column: 23, scope: !335)
!807 = !DILocation(line: 462, column: 2, scope: !335)
!808 = !DILocation(line: 462, column: 9, scope: !335)
!809 = !DILocation(line: 462, column: 20, scope: !335)
!810 = !DILocation(line: 464, column: 10, scope: !335)
!811 = !DILocation(line: 464, column: 22, scope: !335)
!812 = !DILocation(line: 464, column: 17, scope: !335)
!813 = !DILocation(line: 464, column: 15, scope: !335)
!814 = !DILocation(line: 464, column: 2, scope: !335)
!815 = !DILocation(line: 465, column: 1, scope: !335)
!816 = !DILocalVariable(name: "self", arg: 1, scope: !338, file: !1, line: 337, type: !169)
!817 = !DILocation(line: 337, column: 39, scope: !338)
!818 = !DILocalVariable(name: "state", scope: !338, file: !1, line: 339, type: !291)
!819 = !DILocation(line: 339, column: 23, scope: !338)
!820 = !DILocation(line: 339, column: 54, scope: !338)
!821 = !DILocation(line: 339, column: 60, scope: !338)
!822 = !DILocation(line: 339, column: 31, scope: !338)
!823 = !DILocalVariable(name: "code", scope: !338, file: !1, line: 340, type: !23)
!824 = !DILocation(line: 340, column: 6, scope: !338)
!825 = !DILocalVariable(name: "newcode", scope: !338, file: !1, line: 340, type: !23)
!826 = !DILocation(line: 340, column: 12, scope: !338)
!827 = !DILocation(line: 345, column: 27, scope: !338)
!828 = !DILocation(line: 345, column: 33, scope: !338)
!829 = !DILocation(line: 345, column: 40, scope: !338)
!830 = !DILocation(line: 345, column: 19, scope: !338)
!831 = !DILocation(line: 345, column: 17, scope: !338)
!832 = !DILocation(line: 345, column: 7, scope: !338)
!833 = !DILocation(line: 346, column: 6, scope: !834)
!834 = distinct !DILexicalBlock(scope: !338, file: !1, line: 346, column: 6)
!835 = !DILocation(line: 346, column: 11, scope: !834)
!836 = !DILocation(line: 346, column: 6, scope: !338)
!837 = !DILocation(line: 347, column: 11, scope: !834)
!838 = !DILocation(line: 347, column: 3, scope: !834)
!839 = !DILocation(line: 349, column: 30, scope: !338)
!840 = !DILocation(line: 349, column: 24, scope: !338)
!841 = !DILocation(line: 349, column: 2, scope: !338)
!842 = !DILocation(line: 349, column: 28, scope: !338)
!843 = !DILocation(line: 350, column: 6, scope: !844)
!844 = distinct !DILexicalBlock(scope: !338, file: !1, line: 350, column: 6)
!845 = !DILocation(line: 350, column: 18, scope: !844)
!846 = !DILocation(line: 350, column: 6, scope: !338)
!847 = !DILocation(line: 351, column: 15, scope: !844)
!848 = !DILocation(line: 351, column: 3, scope: !844)
!849 = !DILocation(line: 354, column: 7, scope: !850)
!850 = distinct !DILexicalBlock(scope: !338, file: !1, line: 354, column: 6)
!851 = !DILocation(line: 354, column: 12, scope: !850)
!852 = !DILocation(line: 354, column: 20, scope: !850)
!853 = !DILocation(line: 354, column: 23, scope: !854)
!854 = !DILexicalBlockFile(scope: !850, file: !1, discriminator: 1)
!855 = !DILocation(line: 354, column: 30, scope: !854)
!856 = !DILocation(line: 354, column: 6, scope: !854)
!857 = !DILocalVariable(name: "skip_bytes", scope: !858, file: !1, line: 362, type: !23)
!858 = distinct !DILexicalBlock(scope: !850, file: !1, line: 354, column: 46)
!859 = !DILocation(line: 362, column: 7, scope: !858)
!860 = !DILocation(line: 362, column: 21, scope: !858)
!861 = !DILocation(line: 362, column: 28, scope: !858)
!862 = !DILocation(line: 363, column: 8, scope: !858)
!863 = !DILocation(line: 363, column: 15, scope: !858)
!864 = !DILocation(line: 363, column: 34, scope: !858)
!865 = !DILocation(line: 363, column: 41, scope: !858)
!866 = !DILocation(line: 363, column: 32, scope: !858)
!867 = !DILocation(line: 362, column: 33, scope: !858)
!868 = !DILocation(line: 364, column: 17, scope: !858)
!869 = !DILocation(line: 364, column: 24, scope: !858)
!870 = !DILocation(line: 364, column: 14, scope: !858)
!871 = !DILocation(line: 365, column: 3, scope: !858)
!872 = !DILocation(line: 365, column: 10, scope: !858)
!873 = !DILocation(line: 365, column: 21, scope: !858)
!874 = !DILocation(line: 366, column: 3, scope: !858)
!875 = !DILocation(line: 366, column: 20, scope: !876)
!876 = !DILexicalBlockFile(scope: !858, file: !1, discriminator: 1)
!877 = !DILocation(line: 366, column: 23, scope: !876)
!878 = !DILocation(line: 366, column: 3, scope: !876)
!879 = !DILocation(line: 367, column: 19, scope: !880)
!880 = distinct !DILexicalBlock(scope: !858, file: !1, line: 366, column: 28)
!881 = !DILocation(line: 367, column: 11, scope: !880)
!882 = !DILocation(line: 367, column: 9, scope: !880)
!883 = !DILocation(line: 368, column: 8, scope: !884)
!884 = distinct !DILexicalBlock(scope: !880, file: !1, line: 368, column: 8)
!885 = !DILocation(line: 368, column: 13, scope: !884)
!886 = !DILocation(line: 368, column: 8, scope: !880)
!887 = !DILocation(line: 369, column: 13, scope: !884)
!888 = !DILocation(line: 369, column: 5, scope: !884)
!889 = !DILocation(line: 366, column: 3, scope: !890)
!890 = !DILexicalBlockFile(scope: !858, file: !1, discriminator: 2)
!891 = !DILocation(line: 372, column: 3, scope: !858)
!892 = !DILocation(line: 372, column: 10, scope: !858)
!893 = !DILocation(line: 372, column: 27, scope: !858)
!894 = !DILocation(line: 373, column: 3, scope: !858)
!895 = !DILocation(line: 373, column: 10, scope: !858)
!896 = !DILocation(line: 373, column: 15, scope: !858)
!897 = !DILocation(line: 374, column: 35, scope: !858)
!898 = !DILocation(line: 374, column: 42, scope: !858)
!899 = !DILocation(line: 374, column: 32, scope: !858)
!900 = !DILocation(line: 374, column: 48, scope: !858)
!901 = !DILocation(line: 374, column: 3, scope: !858)
!902 = !DILocation(line: 374, column: 10, scope: !858)
!903 = !DILocation(line: 374, column: 27, scope: !858)
!904 = !DILocation(line: 375, column: 3, scope: !858)
!905 = !DILocation(line: 375, column: 10, scope: !858)
!906 = !DILocation(line: 375, column: 19, scope: !858)
!907 = !DILocation(line: 376, column: 3, scope: !858)
!908 = !DILocation(line: 376, column: 10, scope: !858)
!909 = !DILocation(line: 376, column: 18, scope: !858)
!910 = !DILocation(line: 377, column: 21, scope: !858)
!911 = !DILocation(line: 377, column: 11, scope: !858)
!912 = !DILocation(line: 377, column: 3, scope: !858)
!913 = !DILocation(line: 380, column: 6, scope: !914)
!914 = distinct !DILexicalBlock(scope: !338, file: !1, line: 380, column: 6)
!915 = !DILocation(line: 380, column: 13, scope: !914)
!916 = !DILocation(line: 380, column: 20, scope: !914)
!917 = !DILocation(line: 380, column: 11, scope: !914)
!918 = !DILocation(line: 381, column: 6, scope: !914)
!919 = !DILocation(line: 381, column: 10, scope: !920)
!920 = !DILexicalBlockFile(scope: !914, file: !1, discriminator: 1)
!921 = !DILocation(line: 381, column: 18, scope: !920)
!922 = !DILocation(line: 381, column: 25, scope: !920)
!923 = !DILocation(line: 381, column: 15, scope: !920)
!924 = !DILocation(line: 381, column: 34, scope: !920)
!925 = !DILocation(line: 381, column: 37, scope: !926)
!926 = !DILexicalBlockFile(scope: !914, file: !1, discriminator: 2)
!927 = !DILocation(line: 381, column: 44, scope: !926)
!928 = !DILocation(line: 381, column: 52, scope: !926)
!929 = !DILocation(line: 380, column: 6, scope: !930)
!930 = !DILexicalBlockFile(scope: !338, file: !1, discriminator: 1)
!931 = !DILocation(line: 383, column: 23, scope: !932)
!932 = distinct !DILexicalBlock(scope: !914, file: !1, line: 381, column: 58)
!933 = !DILocation(line: 383, column: 29, scope: !932)
!934 = !DILocation(line: 383, column: 38, scope: !932)
!935 = !DILocation(line: 383, column: 3, scope: !932)
!936 = !DILocation(line: 385, column: 3, scope: !932)
!937 = !DILocation(line: 389, column: 6, scope: !938)
!938 = distinct !DILexicalBlock(scope: !338, file: !1, line: 389, column: 6)
!939 = !DILocation(line: 389, column: 14, scope: !938)
!940 = !DILocation(line: 389, column: 21, scope: !938)
!941 = !DILocation(line: 389, column: 11, scope: !938)
!942 = !DILocation(line: 389, column: 6, scope: !338)
!943 = !DILocation(line: 390, column: 22, scope: !944)
!944 = distinct !DILexicalBlock(scope: !938, file: !1, line: 389, column: 31)
!945 = !DILocation(line: 390, column: 29, scope: !944)
!946 = !DILocation(line: 390, column: 4, scope: !944)
!947 = !DILocation(line: 390, column: 11, scope: !944)
!948 = !DILocation(line: 390, column: 17, scope: !944)
!949 = !DILocation(line: 390, column: 20, scope: !944)
!950 = !DILocation(line: 391, column: 10, scope: !944)
!951 = !DILocation(line: 391, column: 17, scope: !944)
!952 = !DILocation(line: 391, column: 8, scope: !944)
!953 = !DILocation(line: 392, column: 2, scope: !944)
!954 = !DILocation(line: 395, column: 2, scope: !338)
!955 = !DILocation(line: 395, column: 9, scope: !930)
!956 = !DILocation(line: 395, column: 14, scope: !930)
!957 = !DILocation(line: 395, column: 2, scope: !930)
!958 = !DILocation(line: 396, column: 36, scope: !959)
!959 = distinct !DILexicalBlock(scope: !338, file: !1, line: 395, column: 22)
!960 = !DILocation(line: 396, column: 22, scope: !959)
!961 = !DILocation(line: 396, column: 29, scope: !959)
!962 = !DILocation(line: 396, column: 4, scope: !959)
!963 = !DILocation(line: 396, column: 11, scope: !959)
!964 = !DILocation(line: 396, column: 17, scope: !959)
!965 = !DILocation(line: 396, column: 20, scope: !959)
!966 = !DILocation(line: 397, column: 24, scope: !959)
!967 = !DILocation(line: 397, column: 10, scope: !959)
!968 = !DILocation(line: 397, column: 17, scope: !959)
!969 = !DILocation(line: 397, column: 8, scope: !959)
!970 = !DILocation(line: 395, column: 2, scope: !971)
!971 = !DILexicalBlockFile(scope: !338, file: !1, discriminator: 2)
!972 = !DILocation(line: 399, column: 38, scope: !338)
!973 = !DILocation(line: 399, column: 21, scope: !338)
!974 = !DILocation(line: 399, column: 28, scope: !338)
!975 = !DILocation(line: 399, column: 36, scope: !338)
!976 = !DILocation(line: 399, column: 3, scope: !338)
!977 = !DILocation(line: 399, column: 10, scope: !338)
!978 = !DILocation(line: 399, column: 16, scope: !338)
!979 = !DILocation(line: 399, column: 19, scope: !338)
!980 = !DILocation(line: 402, column: 9, scope: !338)
!981 = !DILocation(line: 402, column: 16, scope: !338)
!982 = !DILocation(line: 402, column: 7, scope: !338)
!983 = !DILocation(line: 403, column: 6, scope: !984)
!984 = distinct !DILexicalBlock(scope: !338, file: !1, line: 403, column: 6)
!985 = !DILocation(line: 403, column: 13, scope: !984)
!986 = !DILocation(line: 403, column: 20, scope: !984)
!987 = !DILocation(line: 403, column: 11, scope: !984)
!988 = !DILocation(line: 403, column: 28, scope: !984)
!989 = !DILocation(line: 403, column: 31, scope: !990)
!990 = !DILexicalBlockFile(scope: !984, file: !1, discriminator: 1)
!991 = !DILocation(line: 403, column: 38, scope: !990)
!992 = !DILocation(line: 403, column: 46, scope: !990)
!993 = !DILocation(line: 403, column: 6, scope: !990)
!994 = !DILocation(line: 404, column: 25, scope: !995)
!995 = distinct !DILexicalBlock(scope: !984, file: !1, line: 403, column: 52)
!996 = !DILocation(line: 404, column: 32, scope: !995)
!997 = !DILocation(line: 404, column: 17, scope: !995)
!998 = !DILocation(line: 404, column: 3, scope: !995)
!999 = !DILocation(line: 404, column: 10, scope: !995)
!1000 = !DILocation(line: 404, column: 23, scope: !995)
!1001 = !DILocation(line: 405, column: 25, scope: !995)
!1002 = !DILocation(line: 405, column: 32, scope: !995)
!1003 = !DILocation(line: 405, column: 17, scope: !995)
!1004 = !DILocation(line: 405, column: 3, scope: !995)
!1005 = !DILocation(line: 405, column: 10, scope: !995)
!1006 = !DILocation(line: 405, column: 23, scope: !995)
!1007 = !DILocation(line: 406, column: 5, scope: !995)
!1008 = !DILocation(line: 406, column: 12, scope: !995)
!1009 = !DILocation(line: 406, column: 3, scope: !995)
!1010 = !DILocation(line: 407, column: 2, scope: !995)
!1011 = !DILocation(line: 408, column: 6, scope: !1012)
!1012 = distinct !DILexicalBlock(scope: !338, file: !1, line: 408, column: 6)
!1013 = !DILocation(line: 408, column: 13, scope: !1012)
!1014 = !DILocation(line: 408, column: 24, scope: !1012)
!1015 = !DILocation(line: 408, column: 31, scope: !1012)
!1016 = !DILocation(line: 408, column: 22, scope: !1012)
!1017 = !DILocation(line: 408, column: 6, scope: !338)
!1018 = !DILocation(line: 409, column: 3, scope: !1019)
!1019 = distinct !DILexicalBlock(scope: !1012, file: !1, line: 408, column: 49)
!1020 = !DILocation(line: 409, column: 10, scope: !1019)
!1021 = !DILocation(line: 409, column: 14, scope: !1019)
!1022 = !DILocation(line: 410, column: 3, scope: !1019)
!1023 = !DILocation(line: 410, column: 10, scope: !1019)
!1024 = !DILocation(line: 410, column: 27, scope: !1019)
!1025 = !DILocation(line: 411, column: 7, scope: !1026)
!1026 = distinct !DILexicalBlock(scope: !1019, file: !1, line: 411, column: 7)
!1027 = !DILocation(line: 411, column: 14, scope: !1026)
!1028 = !DILocation(line: 411, column: 22, scope: !1026)
!1029 = !DILocation(line: 411, column: 29, scope: !1026)
!1030 = !DILocation(line: 411, column: 19, scope: !1026)
!1031 = !DILocation(line: 411, column: 7, scope: !1019)
!1032 = !DILocation(line: 412, column: 30, scope: !1026)
!1033 = !DILocation(line: 412, column: 37, scope: !1026)
!1034 = !DILocation(line: 412, column: 4, scope: !1026)
!1035 = !DILocation(line: 412, column: 11, scope: !1026)
!1036 = !DILocation(line: 412, column: 28, scope: !1026)
!1037 = !DILocation(line: 414, column: 36, scope: !1026)
!1038 = !DILocation(line: 414, column: 43, scope: !1026)
!1039 = !DILocation(line: 414, column: 33, scope: !1026)
!1040 = !DILocation(line: 414, column: 49, scope: !1026)
!1041 = !DILocation(line: 414, column: 4, scope: !1026)
!1042 = !DILocation(line: 414, column: 11, scope: !1026)
!1043 = !DILocation(line: 414, column: 28, scope: !1026)
!1044 = !DILocation(line: 415, column: 2, scope: !1019)
!1045 = !DILocation(line: 418, column: 19, scope: !338)
!1046 = !DILocation(line: 418, column: 2, scope: !338)
!1047 = !DILocation(line: 418, column: 9, scope: !338)
!1048 = !DILocation(line: 418, column: 17, scope: !338)
!1049 = !DILocation(line: 419, column: 2, scope: !338)
!1050 = !DILocation(line: 420, column: 1, scope: !338)
