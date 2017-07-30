; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_support_filter_rpm.c'
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
%struct.rpm = type { i64, i64, i64, [16 x i8], i32, i32 }

@.str = private unnamed_addr constant [32 x i8] c"archive_read_support_filter_rpm\00", align 1
@.str.1 = private unnamed_addr constant [4 x i8] c"rpm\00", align 1
@.str.2 = private unnamed_addr constant [5 x i8] c"\ED\AB\EE\DB\00", align 1
@.str.3 = private unnamed_addr constant [28 x i8] c"Can't allocate data for rpm\00", align 1
@.str.4 = private unnamed_addr constant [25 x i8] c"Unrecoginized rpm header\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_read_support_compression_rpm(%struct.archive* %a) #0 !dbg !312 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !327, metadata !328), !dbg !329
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !330
  %call = call i32 @archive_read_support_filter_rpm(%struct.archive* %0), !dbg !331
  ret i32 %call, !dbg !332
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define i32 @archive_read_support_filter_rpm(%struct.archive* %_a) #0 !dbg !314 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_read*, align 8
  %bidder = alloca %struct.archive_read_filter_bidder*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !333, metadata !328), !dbg !334
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !335, metadata !328), !dbg !336
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !337
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !338
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !336
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter_bidder** %bidder, metadata !339, metadata !328), !dbg !340
  br label %do.body, !dbg !341

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !342, metadata !328), !dbg !344
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !345
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 14594245, i32 1, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str, i32 0, i32 0)), !dbg !345
  store i32 %call, i32* %magic_test, align 4, !dbg !345
  %3 = load i32, i32* %magic_test, align 4, !dbg !345
  %cmp = icmp eq i32 %3, -30, !dbg !345
  br i1 %cmp, label %if.then, label %if.end, !dbg !345

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !347
  br label %return, !dbg !347

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !350

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !352
  %call1 = call i32 @__archive_read_get_bidder(%struct.archive_read* %4, %struct.archive_read_filter_bidder** %bidder), !dbg !354
  %cmp2 = icmp ne i32 %call1, 0, !dbg !355
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !356

if.then3:                                         ; preds = %do.end
  store i32 -30, i32* %retval, align 4, !dbg !357
  br label %return, !dbg !357

if.end4:                                          ; preds = %do.end
  %5 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !358
  %data = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %5, i32 0, i32 0, !dbg !359
  store i8* null, i8** %data, align 8, !dbg !360
  %6 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !361
  %name = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %6, i32 0, i32 1, !dbg !362
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.1, i32 0, i32 0), i8** %name, align 8, !dbg !363
  %7 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !364
  %bid = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %7, i32 0, i32 2, !dbg !365
  store i32 (%struct.archive_read_filter_bidder*, %struct.archive_read_filter*)* @rpm_bidder_bid, i32 (%struct.archive_read_filter_bidder*, %struct.archive_read_filter*)** %bid, align 8, !dbg !366
  %8 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !367
  %init = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %8, i32 0, i32 3, !dbg !368
  store i32 (%struct.archive_read_filter*)* @rpm_bidder_init, i32 (%struct.archive_read_filter*)** %init, align 8, !dbg !369
  %9 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !370
  %options = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %9, i32 0, i32 4, !dbg !371
  store i32 (%struct.archive_read_filter_bidder*, i8*, i8*)* null, i32 (%struct.archive_read_filter_bidder*, i8*, i8*)** %options, align 8, !dbg !372
  %10 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !373
  %free = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %10, i32 0, i32 5, !dbg !374
  store i32 (%struct.archive_read_filter_bidder*)* null, i32 (%struct.archive_read_filter_bidder*)** %free, align 8, !dbg !375
  store i32 0, i32* %retval, align 4, !dbg !376
  br label %return, !dbg !376

return:                                           ; preds = %if.end4, %if.then3, %if.then
  %11 = load i32, i32* %retval, align 4, !dbg !377
  ret i32 %11, !dbg !377
}

declare i32 @__archive_check_magic(%struct.archive*, i32, i32, i8*) #2

declare i32 @__archive_read_get_bidder(%struct.archive_read*, %struct.archive_read_filter_bidder**) #2

; Function Attrs: nounwind uwtable
define internal i32 @rpm_bidder_bid(%struct.archive_read_filter_bidder* %self, %struct.archive_read_filter* %filter) #0 !dbg !315 {
entry:
  %retval = alloca i32, align 4
  %self.addr = alloca %struct.archive_read_filter_bidder*, align 8
  %filter.addr = alloca %struct.archive_read_filter*, align 8
  %b = alloca i8*, align 8
  %avail = alloca i64, align 8
  %bits_checked = alloca i32, align 4
  store %struct.archive_read_filter_bidder* %self, %struct.archive_read_filter_bidder** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter_bidder** %self.addr, metadata !378, metadata !328), !dbg !379
  store %struct.archive_read_filter* %filter, %struct.archive_read_filter** %filter.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %filter.addr, metadata !380, metadata !328), !dbg !381
  call void @llvm.dbg.declare(metadata i8** %b, metadata !382, metadata !328), !dbg !383
  call void @llvm.dbg.declare(metadata i64* %avail, metadata !384, metadata !328), !dbg !385
  call void @llvm.dbg.declare(metadata i32* %bits_checked, metadata !386, metadata !328), !dbg !387
  %0 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %self.addr, align 8, !dbg !388
  %1 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter.addr, align 8, !dbg !389
  %call = call i8* @__archive_read_filter_ahead(%struct.archive_read_filter* %1, i64 8, i64* %avail), !dbg !390
  store i8* %call, i8** %b, align 8, !dbg !391
  %2 = load i8*, i8** %b, align 8, !dbg !392
  %cmp = icmp eq i8* %2, null, !dbg !394
  br i1 %cmp, label %if.then, label %if.end, !dbg !395

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !396
  br label %return, !dbg !396

if.end:                                           ; preds = %entry
  store i32 0, i32* %bits_checked, align 4, !dbg !397
  %3 = load i8*, i8** %b, align 8, !dbg !398
  %call1 = call i32 @memcmp(i8* %3, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.2, i32 0, i32 0), i64 4) #7, !dbg !400
  %cmp2 = icmp ne i32 %call1, 0, !dbg !401
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !402

if.then3:                                         ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !403
  br label %return, !dbg !403

if.end4:                                          ; preds = %if.end
  %4 = load i32, i32* %bits_checked, align 4, !dbg !404
  %add = add nsw i32 %4, 32, !dbg !404
  store i32 %add, i32* %bits_checked, align 4, !dbg !404
  %5 = load i8*, i8** %b, align 8, !dbg !405
  %arrayidx = getelementptr inbounds i8, i8* %5, i64 4, !dbg !405
  %6 = load i8, i8* %arrayidx, align 1, !dbg !405
  %conv = zext i8 %6 to i32, !dbg !405
  %cmp5 = icmp ne i32 %conv, 3, !dbg !407
  br i1 %cmp5, label %land.lhs.true, label %if.end12, !dbg !408

land.lhs.true:                                    ; preds = %if.end4
  %7 = load i8*, i8** %b, align 8, !dbg !409
  %arrayidx7 = getelementptr inbounds i8, i8* %7, i64 4, !dbg !409
  %8 = load i8, i8* %arrayidx7, align 1, !dbg !409
  %conv8 = zext i8 %8 to i32, !dbg !409
  %cmp9 = icmp ne i32 %conv8, 4, !dbg !411
  br i1 %cmp9, label %if.then11, label %if.end12, !dbg !412

if.then11:                                        ; preds = %land.lhs.true
  store i32 0, i32* %retval, align 4, !dbg !413
  br label %return, !dbg !413

if.end12:                                         ; preds = %land.lhs.true, %if.end4
  %9 = load i32, i32* %bits_checked, align 4, !dbg !414
  %add13 = add nsw i32 %9, 8, !dbg !414
  store i32 %add13, i32* %bits_checked, align 4, !dbg !414
  %10 = load i8*, i8** %b, align 8, !dbg !415
  %arrayidx14 = getelementptr inbounds i8, i8* %10, i64 6, !dbg !415
  %11 = load i8, i8* %arrayidx14, align 1, !dbg !415
  %conv15 = zext i8 %11 to i32, !dbg !415
  %cmp16 = icmp ne i32 %conv15, 0, !dbg !417
  br i1 %cmp16, label %if.then18, label %if.end19, !dbg !418

if.then18:                                        ; preds = %if.end12
  store i32 0, i32* %retval, align 4, !dbg !419
  br label %return, !dbg !419

if.end19:                                         ; preds = %if.end12
  %12 = load i32, i32* %bits_checked, align 4, !dbg !420
  %add20 = add nsw i32 %12, 8, !dbg !420
  store i32 %add20, i32* %bits_checked, align 4, !dbg !420
  %13 = load i8*, i8** %b, align 8, !dbg !421
  %arrayidx21 = getelementptr inbounds i8, i8* %13, i64 7, !dbg !421
  %14 = load i8, i8* %arrayidx21, align 1, !dbg !421
  %conv22 = zext i8 %14 to i32, !dbg !421
  %cmp23 = icmp ne i32 %conv22, 0, !dbg !423
  br i1 %cmp23, label %land.lhs.true25, label %if.end31, !dbg !424

land.lhs.true25:                                  ; preds = %if.end19
  %15 = load i8*, i8** %b, align 8, !dbg !425
  %arrayidx26 = getelementptr inbounds i8, i8* %15, i64 7, !dbg !425
  %16 = load i8, i8* %arrayidx26, align 1, !dbg !425
  %conv27 = zext i8 %16 to i32, !dbg !425
  %cmp28 = icmp ne i32 %conv27, 1, !dbg !427
  br i1 %cmp28, label %if.then30, label %if.end31, !dbg !428

if.then30:                                        ; preds = %land.lhs.true25
  store i32 0, i32* %retval, align 4, !dbg !429
  br label %return, !dbg !429

if.end31:                                         ; preds = %land.lhs.true25, %if.end19
  %17 = load i32, i32* %bits_checked, align 4, !dbg !430
  %add32 = add nsw i32 %17, 8, !dbg !430
  store i32 %add32, i32* %bits_checked, align 4, !dbg !430
  %18 = load i32, i32* %bits_checked, align 4, !dbg !431
  store i32 %18, i32* %retval, align 4, !dbg !432
  br label %return, !dbg !432

return:                                           ; preds = %if.end31, %if.then30, %if.then18, %if.then11, %if.then3, %if.then
  %19 = load i32, i32* %retval, align 4, !dbg !433
  ret i32 %19, !dbg !433
}

; Function Attrs: nounwind uwtable
define internal i32 @rpm_bidder_init(%struct.archive_read_filter* %self) #0 !dbg !316 {
entry:
  %retval = alloca i32, align 4
  %self.addr = alloca %struct.archive_read_filter*, align 8
  %rpm = alloca %struct.rpm*, align 8
  store %struct.archive_read_filter* %self, %struct.archive_read_filter** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %self.addr, metadata !434, metadata !328), !dbg !435
  call void @llvm.dbg.declare(metadata %struct.rpm** %rpm, metadata !436, metadata !328), !dbg !437
  %0 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !438
  %code = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %0, i32 0, i32 12, !dbg !439
  store i32 8, i32* %code, align 8, !dbg !440
  %1 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !441
  %name = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %1, i32 0, i32 11, !dbg !442
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.1, i32 0, i32 0), i8** %name, align 8, !dbg !443
  %2 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !444
  %read = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %2, i32 0, i32 5, !dbg !445
  store i64 (%struct.archive_read_filter*, i8**)* @rpm_filter_read, i64 (%struct.archive_read_filter*, i8**)** %read, align 8, !dbg !446
  %3 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !447
  %skip = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %3, i32 0, i32 6, !dbg !448
  store i64 (%struct.archive_read_filter*, i64)* null, i64 (%struct.archive_read_filter*, i64)** %skip, align 8, !dbg !449
  %4 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !450
  %close = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %4, i32 0, i32 8, !dbg !451
  store i32 (%struct.archive_read_filter*)* @rpm_filter_close, i32 (%struct.archive_read_filter*)** %close, align 8, !dbg !452
  %call = call noalias i8* @calloc(i64 48, i64 1) #8, !dbg !453
  %5 = bitcast i8* %call to %struct.rpm*, !dbg !454
  store %struct.rpm* %5, %struct.rpm** %rpm, align 8, !dbg !455
  %6 = load %struct.rpm*, %struct.rpm** %rpm, align 8, !dbg !456
  %cmp = icmp eq %struct.rpm* %6, null, !dbg !458
  br i1 %cmp, label %if.then, label %if.end, !dbg !459

if.then:                                          ; preds = %entry
  %7 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !460
  %archive = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %7, i32 0, i32 3, !dbg !462
  %8 = load %struct.archive_read*, %struct.archive_read** %archive, align 8, !dbg !462
  %archive1 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %8, i32 0, i32 0, !dbg !463
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive1, i32 12, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.3, i32 0, i32 0)), !dbg !464
  store i32 -30, i32* %retval, align 4, !dbg !465
  br label %return, !dbg !465

if.end:                                           ; preds = %entry
  %9 = load %struct.rpm*, %struct.rpm** %rpm, align 8, !dbg !466
  %10 = bitcast %struct.rpm* %9 to i8*, !dbg !466
  %11 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !467
  %data = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %11, i32 0, i32 10, !dbg !468
  store i8* %10, i8** %data, align 8, !dbg !469
  %12 = load %struct.rpm*, %struct.rpm** %rpm, align 8, !dbg !470
  %state = getelementptr inbounds %struct.rpm, %struct.rpm* %12, i32 0, i32 4, !dbg !471
  store i32 0, i32* %state, align 8, !dbg !472
  store i32 0, i32* %retval, align 4, !dbg !473
  br label %return, !dbg !473

return:                                           ; preds = %if.end, %if.then
  %13 = load i32, i32* %retval, align 4, !dbg !474
  ret i32 %13, !dbg !474
}

declare i8* @__archive_read_filter_ahead(%struct.archive_read_filter*, i64, i64*) #2

; Function Attrs: nounwind readonly
declare i32 @memcmp(i8*, i8*, i64) #3

; Function Attrs: nounwind uwtable
define internal i64 @rpm_filter_read(%struct.archive_read_filter* %self, i8** %buff) #0 !dbg !317 {
entry:
  %retval = alloca i64, align 8
  %self.addr = alloca %struct.archive_read_filter*, align 8
  %buff.addr = alloca i8**, align 8
  %rpm = alloca %struct.rpm*, align 8
  %b = alloca i8*, align 8
  %avail_in = alloca i64, align 8
  %total = alloca i64, align 8
  %used = alloca i64, align 8
  %n = alloca i64, align 8
  %section = alloca i32, align 4
  %bytes = alloca i32, align 4
  store %struct.archive_read_filter* %self, %struct.archive_read_filter** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %self.addr, metadata !475, metadata !328), !dbg !476
  store i8** %buff, i8*** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %buff.addr, metadata !477, metadata !328), !dbg !478
  call void @llvm.dbg.declare(metadata %struct.rpm** %rpm, metadata !479, metadata !328), !dbg !480
  call void @llvm.dbg.declare(metadata i8** %b, metadata !481, metadata !328), !dbg !482
  call void @llvm.dbg.declare(metadata i64* %avail_in, metadata !483, metadata !328), !dbg !484
  call void @llvm.dbg.declare(metadata i64* %total, metadata !485, metadata !328), !dbg !486
  call void @llvm.dbg.declare(metadata i64* %used, metadata !487, metadata !328), !dbg !488
  call void @llvm.dbg.declare(metadata i64* %n, metadata !489, metadata !328), !dbg !490
  call void @llvm.dbg.declare(metadata i32* %section, metadata !491, metadata !328), !dbg !492
  call void @llvm.dbg.declare(metadata i32* %bytes, metadata !493, metadata !328), !dbg !494
  %0 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !495
  %data = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %0, i32 0, i32 10, !dbg !496
  %1 = load i8*, i8** %data, align 8, !dbg !496
  %2 = bitcast i8* %1 to %struct.rpm*, !dbg !497
  store %struct.rpm* %2, %struct.rpm** %rpm, align 8, !dbg !498
  %3 = load i8**, i8*** %buff.addr, align 8, !dbg !499
  store i8* null, i8** %3, align 8, !dbg !500
  store i64 0, i64* %avail_in, align 8, !dbg !501
  store i64 0, i64* %total, align 8, !dbg !502
  store i8* null, i8** %b, align 8, !dbg !503
  store i64 0, i64* %used, align 8, !dbg !504
  br label %do.body, !dbg !505

do.body:                                          ; preds = %land.end, %entry
  %4 = load i8*, i8** %b, align 8, !dbg !506
  %cmp = icmp eq i8* %4, null, !dbg !509
  br i1 %cmp, label %if.then, label %if.end5, !dbg !510

if.then:                                          ; preds = %do.body
  %5 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !511
  %upstream = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %5, i32 0, i32 2, !dbg !513
  %6 = load %struct.archive_read_filter*, %struct.archive_read_filter** %upstream, align 8, !dbg !513
  %call = call i8* @__archive_read_filter_ahead(%struct.archive_read_filter* %6, i64 1, i64* %avail_in), !dbg !514
  store i8* %call, i8** %b, align 8, !dbg !515
  %7 = load i8*, i8** %b, align 8, !dbg !516
  %cmp1 = icmp eq i8* %7, null, !dbg !518
  br i1 %cmp1, label %if.then2, label %if.end, !dbg !519

if.then2:                                         ; preds = %if.then
  %8 = load i64, i64* %avail_in, align 8, !dbg !520
  %cmp3 = icmp slt i64 %8, 0, !dbg !523
  br i1 %cmp3, label %if.then4, label %if.else, !dbg !524

if.then4:                                         ; preds = %if.then2
  store i64 -30, i64* %retval, align 8, !dbg !525
  br label %return, !dbg !525

if.else:                                          ; preds = %if.then2
  br label %do.end, !dbg !526

if.end:                                           ; preds = %if.then
  br label %if.end5, !dbg !527

if.end5:                                          ; preds = %if.end, %do.body
  %9 = load %struct.rpm*, %struct.rpm** %rpm, align 8, !dbg !528
  %state = getelementptr inbounds %struct.rpm, %struct.rpm* %9, i32 0, i32 4, !dbg !529
  %10 = load i32, i32* %state, align 8, !dbg !529
  switch i32 %10, label %sw.epilog [
    i32 0, label %sw.bb
    i32 1, label %sw.bb14
    i32 2, label %sw.bb76
    i32 3, label %sw.bb97
    i32 4, label %sw.bb108
  ], !dbg !530

sw.bb:                                            ; preds = %if.end5
  %11 = load %struct.rpm*, %struct.rpm** %rpm, align 8, !dbg !531
  %total_in = getelementptr inbounds %struct.rpm, %struct.rpm* %11, i32 0, i32 0, !dbg !534
  %12 = load i64, i64* %total_in, align 8, !dbg !534
  %13 = load i64, i64* %avail_in, align 8, !dbg !535
  %add = add nsw i64 %12, %13, !dbg !536
  %cmp6 = icmp slt i64 %add, 96, !dbg !537
  br i1 %cmp6, label %if.then7, label %if.else9, !dbg !538

if.then7:                                         ; preds = %sw.bb
  %14 = load i64, i64* %avail_in, align 8, !dbg !539
  %15 = load i64, i64* %used, align 8, !dbg !540
  %add8 = add i64 %15, %14, !dbg !540
  store i64 %add8, i64* %used, align 8, !dbg !540
  br label %if.end13, !dbg !541

if.else9:                                         ; preds = %sw.bb
  %16 = load %struct.rpm*, %struct.rpm** %rpm, align 8, !dbg !542
  %total_in10 = getelementptr inbounds %struct.rpm, %struct.rpm* %16, i32 0, i32 0, !dbg !544
  %17 = load i64, i64* %total_in10, align 8, !dbg !544
  %sub = sub nsw i64 96, %17, !dbg !545
  store i64 %sub, i64* %n, align 8, !dbg !546
  %18 = load i64, i64* %n, align 8, !dbg !547
  %19 = load i64, i64* %used, align 8, !dbg !548
  %add11 = add i64 %19, %18, !dbg !548
  store i64 %add11, i64* %used, align 8, !dbg !548
  %20 = load i64, i64* %n, align 8, !dbg !549
  %21 = load i8*, i8** %b, align 8, !dbg !550
  %add.ptr = getelementptr inbounds i8, i8* %21, i64 %20, !dbg !550
  store i8* %add.ptr, i8** %b, align 8, !dbg !550
  %22 = load %struct.rpm*, %struct.rpm** %rpm, align 8, !dbg !551
  %state12 = getelementptr inbounds %struct.rpm, %struct.rpm* %22, i32 0, i32 4, !dbg !552
  store i32 1, i32* %state12, align 8, !dbg !553
  %23 = load %struct.rpm*, %struct.rpm** %rpm, align 8, !dbg !554
  %hpos = getelementptr inbounds %struct.rpm, %struct.rpm* %23, i32 0, i32 1, !dbg !555
  store i64 0, i64* %hpos, align 8, !dbg !556
  %24 = load %struct.rpm*, %struct.rpm** %rpm, align 8, !dbg !557
  %hlen = getelementptr inbounds %struct.rpm, %struct.rpm* %24, i32 0, i32 2, !dbg !558
  store i64 0, i64* %hlen, align 8, !dbg !559
  %25 = load %struct.rpm*, %struct.rpm** %rpm, align 8, !dbg !560
  %first_header = getelementptr inbounds %struct.rpm, %struct.rpm* %25, i32 0, i32 5, !dbg !561
  store i32 1, i32* %first_header, align 4, !dbg !562
  br label %if.end13

if.end13:                                         ; preds = %if.else9, %if.then7
  br label %sw.epilog, !dbg !563

sw.bb14:                                          ; preds = %if.end5
  %26 = load %struct.rpm*, %struct.rpm** %rpm, align 8, !dbg !564
  %hpos15 = getelementptr inbounds %struct.rpm, %struct.rpm* %26, i32 0, i32 1, !dbg !565
  %27 = load i64, i64* %hpos15, align 8, !dbg !565
  %sub16 = sub i64 16, %27, !dbg !566
  store i64 %sub16, i64* %n, align 8, !dbg !567
  %28 = load i64, i64* %n, align 8, !dbg !568
  %29 = load i64, i64* %avail_in, align 8, !dbg !570
  %30 = load i64, i64* %used, align 8, !dbg !571
  %sub17 = sub i64 %29, %30, !dbg !572
  %cmp18 = icmp ugt i64 %28, %sub17, !dbg !573
  br i1 %cmp18, label %if.then19, label %if.end21, !dbg !574

if.then19:                                        ; preds = %sw.bb14
  %31 = load i64, i64* %avail_in, align 8, !dbg !575
  %32 = load i64, i64* %used, align 8, !dbg !576
  %sub20 = sub i64 %31, %32, !dbg !577
  store i64 %sub20, i64* %n, align 8, !dbg !578
  br label %if.end21, !dbg !579

if.end21:                                         ; preds = %if.then19, %sw.bb14
  %33 = load %struct.rpm*, %struct.rpm** %rpm, align 8, !dbg !580
  %header = getelementptr inbounds %struct.rpm, %struct.rpm* %33, i32 0, i32 3, !dbg !581
  %arraydecay = getelementptr inbounds [16 x i8], [16 x i8]* %header, i32 0, i32 0, !dbg !580
  %34 = load %struct.rpm*, %struct.rpm** %rpm, align 8, !dbg !582
  %hpos22 = getelementptr inbounds %struct.rpm, %struct.rpm* %34, i32 0, i32 1, !dbg !583
  %35 = load i64, i64* %hpos22, align 8, !dbg !583
  %add.ptr23 = getelementptr inbounds i8, i8* %arraydecay, i64 %35, !dbg !584
  %36 = load i8*, i8** %b, align 8, !dbg !585
  %37 = load i64, i64* %n, align 8, !dbg !586
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %add.ptr23, i8* %36, i64 %37, i32 1, i1 false), !dbg !587
  %38 = load i64, i64* %n, align 8, !dbg !588
  %39 = load i8*, i8** %b, align 8, !dbg !589
  %add.ptr24 = getelementptr inbounds i8, i8* %39, i64 %38, !dbg !589
  store i8* %add.ptr24, i8** %b, align 8, !dbg !589
  %40 = load i64, i64* %n, align 8, !dbg !590
  %41 = load i64, i64* %used, align 8, !dbg !591
  %add25 = add i64 %41, %40, !dbg !591
  store i64 %add25, i64* %used, align 8, !dbg !591
  %42 = load i64, i64* %n, align 8, !dbg !592
  %43 = load %struct.rpm*, %struct.rpm** %rpm, align 8, !dbg !593
  %hpos26 = getelementptr inbounds %struct.rpm, %struct.rpm* %43, i32 0, i32 1, !dbg !594
  %44 = load i64, i64* %hpos26, align 8, !dbg !595
  %add27 = add i64 %44, %42, !dbg !595
  store i64 %add27, i64* %hpos26, align 8, !dbg !595
  %45 = load %struct.rpm*, %struct.rpm** %rpm, align 8, !dbg !596
  %hpos28 = getelementptr inbounds %struct.rpm, %struct.rpm* %45, i32 0, i32 1, !dbg !598
  %46 = load i64, i64* %hpos28, align 8, !dbg !598
  %cmp29 = icmp eq i64 %46, 16, !dbg !599
  br i1 %cmp29, label %if.then30, label %if.end75, !dbg !600

if.then30:                                        ; preds = %if.end21
  %47 = load %struct.rpm*, %struct.rpm** %rpm, align 8, !dbg !601
  %header31 = getelementptr inbounds %struct.rpm, %struct.rpm* %47, i32 0, i32 3, !dbg !604
  %arrayidx = getelementptr inbounds [16 x i8], [16 x i8]* %header31, i64 0, i64 0, !dbg !601
  %48 = load i8, i8* %arrayidx, align 8, !dbg !601
  %conv = zext i8 %48 to i32, !dbg !601
  %cmp32 = icmp ne i32 %conv, 142, !dbg !605
  br i1 %cmp32, label %if.then51, label %lor.lhs.false, !dbg !606

lor.lhs.false:                                    ; preds = %if.then30
  %49 = load %struct.rpm*, %struct.rpm** %rpm, align 8, !dbg !607
  %header34 = getelementptr inbounds %struct.rpm, %struct.rpm* %49, i32 0, i32 3, !dbg !608
  %arrayidx35 = getelementptr inbounds [16 x i8], [16 x i8]* %header34, i64 0, i64 1, !dbg !607
  %50 = load i8, i8* %arrayidx35, align 1, !dbg !607
  %conv36 = zext i8 %50 to i32, !dbg !607
  %cmp37 = icmp ne i32 %conv36, 173, !dbg !609
  br i1 %cmp37, label %if.then51, label %lor.lhs.false39, !dbg !610

lor.lhs.false39:                                  ; preds = %lor.lhs.false
  %51 = load %struct.rpm*, %struct.rpm** %rpm, align 8, !dbg !611
  %header40 = getelementptr inbounds %struct.rpm, %struct.rpm* %51, i32 0, i32 3, !dbg !612
  %arrayidx41 = getelementptr inbounds [16 x i8], [16 x i8]* %header40, i64 0, i64 2, !dbg !611
  %52 = load i8, i8* %arrayidx41, align 2, !dbg !611
  %conv42 = zext i8 %52 to i32, !dbg !611
  %cmp43 = icmp ne i32 %conv42, 232, !dbg !613
  br i1 %cmp43, label %if.then51, label %lor.lhs.false45, !dbg !614

lor.lhs.false45:                                  ; preds = %lor.lhs.false39
  %53 = load %struct.rpm*, %struct.rpm** %rpm, align 8, !dbg !615
  %header46 = getelementptr inbounds %struct.rpm, %struct.rpm* %53, i32 0, i32 3, !dbg !616
  %arrayidx47 = getelementptr inbounds [16 x i8], [16 x i8]* %header46, i64 0, i64 3, !dbg !615
  %54 = load i8, i8* %arrayidx47, align 1, !dbg !615
  %conv48 = zext i8 %54 to i32, !dbg !615
  %cmp49 = icmp ne i32 %conv48, 1, !dbg !617
  br i1 %cmp49, label %if.then51, label %if.end60, !dbg !618

if.then51:                                        ; preds = %lor.lhs.false45, %lor.lhs.false39, %lor.lhs.false, %if.then30
  %55 = load %struct.rpm*, %struct.rpm** %rpm, align 8, !dbg !620
  %first_header52 = getelementptr inbounds %struct.rpm, %struct.rpm* %55, i32 0, i32 5, !dbg !623
  %56 = load i32, i32* %first_header52, align 4, !dbg !623
  %tobool = icmp ne i32 %56, 0, !dbg !620
  br i1 %tobool, label %if.then53, label %if.end55, !dbg !624

if.then53:                                        ; preds = %if.then51
  %57 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !625
  %archive = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %57, i32 0, i32 3, !dbg !627
  %58 = load %struct.archive_read*, %struct.archive_read** %archive, align 8, !dbg !627
  %archive54 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %58, i32 0, i32 0, !dbg !628
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive54, i32 84, i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.4, i32 0, i32 0)), !dbg !629
  store i64 -30, i64* %retval, align 8, !dbg !630
  br label %return, !dbg !630

if.end55:                                         ; preds = %if.then51
  %59 = load %struct.rpm*, %struct.rpm** %rpm, align 8, !dbg !631
  %state56 = getelementptr inbounds %struct.rpm, %struct.rpm* %59, i32 0, i32 4, !dbg !632
  store i32 4, i32* %state56, align 8, !dbg !633
  %60 = load %struct.rpm*, %struct.rpm** %rpm, align 8, !dbg !634
  %header57 = getelementptr inbounds %struct.rpm, %struct.rpm* %60, i32 0, i32 3, !dbg !635
  %arraydecay58 = getelementptr inbounds [16 x i8], [16 x i8]* %header57, i32 0, i32 0, !dbg !634
  %61 = load i8**, i8*** %buff.addr, align 8, !dbg !636
  store i8* %arraydecay58, i8** %61, align 8, !dbg !637
  %62 = load %struct.rpm*, %struct.rpm** %rpm, align 8, !dbg !638
  %hpos59 = getelementptr inbounds %struct.rpm, %struct.rpm* %62, i32 0, i32 1, !dbg !639
  %63 = load i64, i64* %hpos59, align 8, !dbg !639
  store i64 %63, i64* %total, align 8, !dbg !640
  br label %sw.epilog, !dbg !641

if.end60:                                         ; preds = %lor.lhs.false45
  %64 = load %struct.rpm*, %struct.rpm** %rpm, align 8, !dbg !642
  %header61 = getelementptr inbounds %struct.rpm, %struct.rpm* %64, i32 0, i32 3, !dbg !643
  %arraydecay62 = getelementptr inbounds [16 x i8], [16 x i8]* %header61, i32 0, i32 0, !dbg !642
  %add.ptr63 = getelementptr inbounds i8, i8* %arraydecay62, i64 8, !dbg !644
  %call64 = call i32 @archive_be32dec(i8* %add.ptr63), !dbg !645
  store i32 %call64, i32* %section, align 4, !dbg !646
  %65 = load %struct.rpm*, %struct.rpm** %rpm, align 8, !dbg !647
  %header65 = getelementptr inbounds %struct.rpm, %struct.rpm* %65, i32 0, i32 3, !dbg !648
  %arraydecay66 = getelementptr inbounds [16 x i8], [16 x i8]* %header65, i32 0, i32 0, !dbg !647
  %add.ptr67 = getelementptr inbounds i8, i8* %arraydecay66, i64 12, !dbg !649
  %call68 = call i32 @archive_be32dec(i8* %add.ptr67), !dbg !650
  store i32 %call68, i32* %bytes, align 4, !dbg !651
  %66 = load i32, i32* %section, align 4, !dbg !652
  %mul = mul i32 %66, 16, !dbg !653
  %add69 = add i32 16, %mul, !dbg !654
  %67 = load i32, i32* %bytes, align 4, !dbg !655
  %add70 = add i32 %add69, %67, !dbg !656
  %conv71 = zext i32 %add70 to i64, !dbg !657
  %68 = load %struct.rpm*, %struct.rpm** %rpm, align 8, !dbg !658
  %hlen72 = getelementptr inbounds %struct.rpm, %struct.rpm* %68, i32 0, i32 2, !dbg !659
  store i64 %conv71, i64* %hlen72, align 8, !dbg !660
  %69 = load %struct.rpm*, %struct.rpm** %rpm, align 8, !dbg !661
  %state73 = getelementptr inbounds %struct.rpm, %struct.rpm* %69, i32 0, i32 4, !dbg !662
  store i32 2, i32* %state73, align 8, !dbg !663
  %70 = load %struct.rpm*, %struct.rpm** %rpm, align 8, !dbg !664
  %first_header74 = getelementptr inbounds %struct.rpm, %struct.rpm* %70, i32 0, i32 5, !dbg !665
  store i32 0, i32* %first_header74, align 4, !dbg !666
  br label %if.end75, !dbg !667

if.end75:                                         ; preds = %if.end60, %if.end21
  br label %sw.epilog, !dbg !668

sw.bb76:                                          ; preds = %if.end5
  %71 = load %struct.rpm*, %struct.rpm** %rpm, align 8, !dbg !669
  %hlen77 = getelementptr inbounds %struct.rpm, %struct.rpm* %71, i32 0, i32 2, !dbg !670
  %72 = load i64, i64* %hlen77, align 8, !dbg !670
  %73 = load %struct.rpm*, %struct.rpm** %rpm, align 8, !dbg !671
  %hpos78 = getelementptr inbounds %struct.rpm, %struct.rpm* %73, i32 0, i32 1, !dbg !672
  %74 = load i64, i64* %hpos78, align 8, !dbg !672
  %sub79 = sub i64 %72, %74, !dbg !673
  store i64 %sub79, i64* %n, align 8, !dbg !674
  %75 = load i64, i64* %n, align 8, !dbg !675
  %76 = load i64, i64* %avail_in, align 8, !dbg !677
  %77 = load i64, i64* %used, align 8, !dbg !678
  %sub80 = sub i64 %76, %77, !dbg !679
  %cmp81 = icmp ugt i64 %75, %sub80, !dbg !680
  br i1 %cmp81, label %if.then83, label %if.end85, !dbg !681

if.then83:                                        ; preds = %sw.bb76
  %78 = load i64, i64* %avail_in, align 8, !dbg !682
  %79 = load i64, i64* %used, align 8, !dbg !683
  %sub84 = sub i64 %78, %79, !dbg !684
  store i64 %sub84, i64* %n, align 8, !dbg !685
  br label %if.end85, !dbg !686

if.end85:                                         ; preds = %if.then83, %sw.bb76
  %80 = load i64, i64* %n, align 8, !dbg !687
  %81 = load i8*, i8** %b, align 8, !dbg !688
  %add.ptr86 = getelementptr inbounds i8, i8* %81, i64 %80, !dbg !688
  store i8* %add.ptr86, i8** %b, align 8, !dbg !688
  %82 = load i64, i64* %n, align 8, !dbg !689
  %83 = load i64, i64* %used, align 8, !dbg !690
  %add87 = add i64 %83, %82, !dbg !690
  store i64 %add87, i64* %used, align 8, !dbg !690
  %84 = load i64, i64* %n, align 8, !dbg !691
  %85 = load %struct.rpm*, %struct.rpm** %rpm, align 8, !dbg !692
  %hpos88 = getelementptr inbounds %struct.rpm, %struct.rpm* %85, i32 0, i32 1, !dbg !693
  %86 = load i64, i64* %hpos88, align 8, !dbg !694
  %add89 = add i64 %86, %84, !dbg !694
  store i64 %add89, i64* %hpos88, align 8, !dbg !694
  %87 = load %struct.rpm*, %struct.rpm** %rpm, align 8, !dbg !695
  %hpos90 = getelementptr inbounds %struct.rpm, %struct.rpm* %87, i32 0, i32 1, !dbg !697
  %88 = load i64, i64* %hpos90, align 8, !dbg !697
  %89 = load %struct.rpm*, %struct.rpm** %rpm, align 8, !dbg !698
  %hlen91 = getelementptr inbounds %struct.rpm, %struct.rpm* %89, i32 0, i32 2, !dbg !699
  %90 = load i64, i64* %hlen91, align 8, !dbg !699
  %cmp92 = icmp eq i64 %88, %90, !dbg !700
  br i1 %cmp92, label %if.then94, label %if.end96, !dbg !701

if.then94:                                        ; preds = %if.end85
  %91 = load %struct.rpm*, %struct.rpm** %rpm, align 8, !dbg !702
  %state95 = getelementptr inbounds %struct.rpm, %struct.rpm* %91, i32 0, i32 4, !dbg !703
  store i32 3, i32* %state95, align 8, !dbg !704
  br label %if.end96, !dbg !702

if.end96:                                         ; preds = %if.then94, %if.end85
  br label %sw.epilog, !dbg !705

sw.bb97:                                          ; preds = %if.end5
  br label %while.cond, !dbg !706

while.cond:                                       ; preds = %if.end107, %sw.bb97
  %92 = load i64, i64* %used, align 8, !dbg !707
  %93 = load i64, i64* %avail_in, align 8, !dbg !709
  %cmp98 = icmp ult i64 %92, %93, !dbg !710
  br i1 %cmp98, label %while.body, label %while.end, !dbg !711

while.body:                                       ; preds = %while.cond
  %94 = load i8*, i8** %b, align 8, !dbg !712
  %95 = load i8, i8* %94, align 1, !dbg !715
  %conv100 = zext i8 %95 to i32, !dbg !715
  %cmp101 = icmp ne i32 %conv100, 0, !dbg !716
  br i1 %cmp101, label %if.then103, label %if.end107, !dbg !717

if.then103:                                       ; preds = %while.body
  %96 = load %struct.rpm*, %struct.rpm** %rpm, align 8, !dbg !718
  %state104 = getelementptr inbounds %struct.rpm, %struct.rpm* %96, i32 0, i32 4, !dbg !720
  store i32 1, i32* %state104, align 8, !dbg !721
  %97 = load %struct.rpm*, %struct.rpm** %rpm, align 8, !dbg !722
  %hpos105 = getelementptr inbounds %struct.rpm, %struct.rpm* %97, i32 0, i32 1, !dbg !723
  store i64 0, i64* %hpos105, align 8, !dbg !724
  %98 = load %struct.rpm*, %struct.rpm** %rpm, align 8, !dbg !725
  %hlen106 = getelementptr inbounds %struct.rpm, %struct.rpm* %98, i32 0, i32 2, !dbg !726
  store i64 0, i64* %hlen106, align 8, !dbg !727
  br label %while.end, !dbg !728

if.end107:                                        ; preds = %while.body
  %99 = load i8*, i8** %b, align 8, !dbg !729
  %incdec.ptr = getelementptr inbounds i8, i8* %99, i32 1, !dbg !729
  store i8* %incdec.ptr, i8** %b, align 8, !dbg !729
  %100 = load i64, i64* %used, align 8, !dbg !730
  %inc = add i64 %100, 1, !dbg !730
  store i64 %inc, i64* %used, align 8, !dbg !730
  br label %while.cond, !dbg !731

while.end:                                        ; preds = %if.then103, %while.cond
  br label %sw.epilog, !dbg !733

sw.bb108:                                         ; preds = %if.end5
  %101 = load i8*, i8** %b, align 8, !dbg !734
  %102 = load i8**, i8*** %buff.addr, align 8, !dbg !735
  store i8* %101, i8** %102, align 8, !dbg !736
  %103 = load i64, i64* %avail_in, align 8, !dbg !737
  store i64 %103, i64* %total, align 8, !dbg !738
  %104 = load i64, i64* %avail_in, align 8, !dbg !739
  store i64 %104, i64* %used, align 8, !dbg !740
  br label %sw.epilog, !dbg !741

sw.epilog:                                        ; preds = %if.end5, %sw.bb108, %while.end, %if.end96, %if.end75, %if.end55, %if.end13
  %105 = load i64, i64* %used, align 8, !dbg !742
  %106 = load i64, i64* %avail_in, align 8, !dbg !744
  %cmp109 = icmp eq i64 %105, %106, !dbg !745
  br i1 %cmp109, label %if.then111, label %if.end116, !dbg !746

if.then111:                                       ; preds = %sw.epilog
  %107 = load i64, i64* %used, align 8, !dbg !747
  %108 = load %struct.rpm*, %struct.rpm** %rpm, align 8, !dbg !749
  %total_in112 = getelementptr inbounds %struct.rpm, %struct.rpm* %108, i32 0, i32 0, !dbg !750
  %109 = load i64, i64* %total_in112, align 8, !dbg !751
  %add113 = add i64 %109, %107, !dbg !751
  store i64 %add113, i64* %total_in112, align 8, !dbg !751
  %110 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !752
  %upstream114 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %110, i32 0, i32 2, !dbg !753
  %111 = load %struct.archive_read_filter*, %struct.archive_read_filter** %upstream114, align 8, !dbg !753
  %112 = load i64, i64* %used, align 8, !dbg !754
  %call115 = call i64 @__archive_read_filter_consume(%struct.archive_read_filter* %111, i64 %112), !dbg !755
  store i8* null, i8** %b, align 8, !dbg !756
  store i64 0, i64* %used, align 8, !dbg !757
  br label %if.end116, !dbg !758

if.end116:                                        ; preds = %if.then111, %sw.epilog
  br label %do.cond, !dbg !759

do.cond:                                          ; preds = %if.end116
  %113 = load i64, i64* %total, align 8, !dbg !760
  %cmp117 = icmp eq i64 %113, 0, !dbg !762
  br i1 %cmp117, label %land.rhs, label %land.end, !dbg !763

land.rhs:                                         ; preds = %do.cond
  %114 = load i64, i64* %avail_in, align 8, !dbg !764
  %cmp119 = icmp sgt i64 %114, 0, !dbg !766
  br label %land.end

land.end:                                         ; preds = %land.rhs, %do.cond
  %115 = phi i1 [ false, %do.cond ], [ %cmp119, %land.rhs ]
  br i1 %115, label %do.body, label %do.end, !dbg !767

do.end:                                           ; preds = %land.end, %if.else
  %116 = load i64, i64* %used, align 8, !dbg !769
  %cmp121 = icmp ugt i64 %116, 0, !dbg !771
  br i1 %cmp121, label %land.lhs.true, label %if.end130, !dbg !772

land.lhs.true:                                    ; preds = %do.end
  %117 = load i8*, i8** %b, align 8, !dbg !773
  %cmp123 = icmp ne i8* %117, null, !dbg !775
  br i1 %cmp123, label %if.then125, label %if.end130, !dbg !776

if.then125:                                       ; preds = %land.lhs.true
  %118 = load i64, i64* %used, align 8, !dbg !777
  %119 = load %struct.rpm*, %struct.rpm** %rpm, align 8, !dbg !779
  %total_in126 = getelementptr inbounds %struct.rpm, %struct.rpm* %119, i32 0, i32 0, !dbg !780
  %120 = load i64, i64* %total_in126, align 8, !dbg !781
  %add127 = add i64 %120, %118, !dbg !781
  store i64 %add127, i64* %total_in126, align 8, !dbg !781
  %121 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !782
  %upstream128 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %121, i32 0, i32 2, !dbg !783
  %122 = load %struct.archive_read_filter*, %struct.archive_read_filter** %upstream128, align 8, !dbg !783
  %123 = load i64, i64* %used, align 8, !dbg !784
  %call129 = call i64 @__archive_read_filter_consume(%struct.archive_read_filter* %122, i64 %123), !dbg !785
  br label %if.end130, !dbg !786

if.end130:                                        ; preds = %if.then125, %land.lhs.true, %do.end
  %124 = load i64, i64* %total, align 8, !dbg !787
  store i64 %124, i64* %retval, align 8, !dbg !788
  br label %return, !dbg !788

return:                                           ; preds = %if.end130, %if.then53, %if.then4
  %125 = load i64, i64* %retval, align 8, !dbg !789
  ret i64 %125, !dbg !789
}

; Function Attrs: nounwind uwtable
define internal i32 @rpm_filter_close(%struct.archive_read_filter* %self) #0 !dbg !323 {
entry:
  %self.addr = alloca %struct.archive_read_filter*, align 8
  %rpm = alloca %struct.rpm*, align 8
  store %struct.archive_read_filter* %self, %struct.archive_read_filter** %self.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %self.addr, metadata !790, metadata !328), !dbg !791
  call void @llvm.dbg.declare(metadata %struct.rpm** %rpm, metadata !792, metadata !328), !dbg !793
  %0 = load %struct.archive_read_filter*, %struct.archive_read_filter** %self.addr, align 8, !dbg !794
  %data = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %0, i32 0, i32 10, !dbg !795
  %1 = load i8*, i8** %data, align 8, !dbg !795
  %2 = bitcast i8* %1 to %struct.rpm*, !dbg !796
  store %struct.rpm* %2, %struct.rpm** %rpm, align 8, !dbg !797
  %3 = load %struct.rpm*, %struct.rpm** %rpm, align 8, !dbg !798
  %4 = bitcast %struct.rpm* %3 to i8*, !dbg !798
  call void @free(i8* %4) #8, !dbg !799
  ret i32 0, !dbg !800
}

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #4

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #5

; Function Attrs: inlinehint nounwind uwtable
define internal i32 @archive_be32dec(i8* %pp) #6 !dbg !318 {
entry:
  %pp.addr = alloca i8*, align 8
  %p = alloca i8*, align 8
  %p3 = alloca i32, align 4
  %p2 = alloca i32, align 4
  %p1 = alloca i32, align 4
  %p0 = alloca i32, align 4
  store i8* %pp, i8** %pp.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %pp.addr, metadata !801, metadata !328), !dbg !802
  call void @llvm.dbg.declare(metadata i8** %p, metadata !803, metadata !328), !dbg !804
  %0 = load i8*, i8** %pp.addr, align 8, !dbg !805
  store i8* %0, i8** %p, align 8, !dbg !804
  call void @llvm.dbg.declare(metadata i32* %p3, metadata !806, metadata !328), !dbg !807
  %1 = load i8*, i8** %p, align 8, !dbg !808
  %arrayidx = getelementptr inbounds i8, i8* %1, i64 3, !dbg !808
  %2 = load i8, i8* %arrayidx, align 1, !dbg !808
  %conv = zext i8 %2 to i32, !dbg !808
  store i32 %conv, i32* %p3, align 4, !dbg !807
  call void @llvm.dbg.declare(metadata i32* %p2, metadata !809, metadata !328), !dbg !810
  %3 = load i8*, i8** %p, align 8, !dbg !811
  %arrayidx1 = getelementptr inbounds i8, i8* %3, i64 2, !dbg !811
  %4 = load i8, i8* %arrayidx1, align 1, !dbg !811
  %conv2 = zext i8 %4 to i32, !dbg !811
  store i32 %conv2, i32* %p2, align 4, !dbg !810
  call void @llvm.dbg.declare(metadata i32* %p1, metadata !812, metadata !328), !dbg !813
  %5 = load i8*, i8** %p, align 8, !dbg !814
  %arrayidx3 = getelementptr inbounds i8, i8* %5, i64 1, !dbg !814
  %6 = load i8, i8* %arrayidx3, align 1, !dbg !814
  %conv4 = zext i8 %6 to i32, !dbg !814
  store i32 %conv4, i32* %p1, align 4, !dbg !813
  call void @llvm.dbg.declare(metadata i32* %p0, metadata !815, metadata !328), !dbg !816
  %7 = load i8*, i8** %p, align 8, !dbg !817
  %arrayidx5 = getelementptr inbounds i8, i8* %7, i64 0, !dbg !817
  %8 = load i8, i8* %arrayidx5, align 1, !dbg !817
  %conv6 = zext i8 %8 to i32, !dbg !817
  store i32 %conv6, i32* %p0, align 4, !dbg !816
  %9 = load i32, i32* %p0, align 4, !dbg !818
  %shl = shl i32 %9, 24, !dbg !819
  %10 = load i32, i32* %p1, align 4, !dbg !820
  %shl7 = shl i32 %10, 16, !dbg !821
  %or = or i32 %shl, %shl7, !dbg !822
  %11 = load i32, i32* %p2, align 4, !dbg !823
  %shl8 = shl i32 %11, 8, !dbg !824
  %or9 = or i32 %or, %shl8, !dbg !825
  %12 = load i32, i32* %p3, align 4, !dbg !826
  %or10 = or i32 %or9, %12, !dbg !827
  ret i32 %or10, !dbg !828
}

declare i64 @__archive_read_filter_consume(%struct.archive_read_filter*, i64) #2

; Function Attrs: nounwind
declare void @free(i8*) #4

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { argmemonly nounwind }
attributes #6 = { inlinehint nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { nounwind readonly }
attributes #8 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!324, !325}
!llvm.ident = !{!326}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !29, subprograms: !311)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_support_filter_rpm.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{!3}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !4, file: !1, line: 45, size: 32, align: 32, elements: !23)
!4 = !DICompositeType(tag: DW_TAG_structure_type, name: "rpm", file: !1, line: 40, size: 384, align: 64, elements: !5)
!5 = !{!6, !10, !14, !15, !20, !21}
!6 = !DIDerivedType(tag: DW_TAG_member, name: "total_in", scope: !4, file: !1, line: 41, baseType: !7, size: 64, align: 64)
!7 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !8, line: 40, baseType: !9)
!8 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!9 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!10 = !DIDerivedType(tag: DW_TAG_member, name: "hpos", scope: !4, file: !1, line: 42, baseType: !11, size: 64, align: 64, offset: 64)
!11 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !12, line: 62, baseType: !13)
!12 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!13 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!14 = !DIDerivedType(tag: DW_TAG_member, name: "hlen", scope: !4, file: !1, line: 43, baseType: !11, size: 64, align: 64, offset: 128)
!15 = !DIDerivedType(tag: DW_TAG_member, name: "header", scope: !4, file: !1, line: 44, baseType: !16, size: 128, align: 8, offset: 192)
!16 = !DICompositeType(tag: DW_TAG_array_type, baseType: !17, size: 128, align: 8, elements: !18)
!17 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!18 = !{!19}
!19 = !DISubrange(count: 16)
!20 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !4, file: !1, line: 53, baseType: !3, size: 32, align: 32, offset: 320)
!21 = !DIDerivedType(tag: DW_TAG_member, name: "first_header", scope: !4, file: !1, line: 54, baseType: !22, size: 32, align: 32, offset: 352)
!22 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!23 = !{!24, !25, !26, !27, !28}
!24 = !DIEnumerator(name: "ST_LEAD", value: 0)
!25 = !DIEnumerator(name: "ST_HEADER", value: 1)
!26 = !DIEnumerator(name: "ST_HEADER_DATA", value: 2)
!27 = !DIEnumerator(name: "ST_PADDING", value: 3)
!28 = !DIEnumerator(name: "ST_ARCHIVE", value: 4)
!29 = !{!30, !141, !308, !11, !309}
!30 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !31, size: 64, align: 64)
!31 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read", file: !32, line: 159, size: 20288, align: 64, elements: !33)
!32 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!33 = !{!34, !129, !130, !131, !132, !133, !177, !239, !240, !241, !242, !243, !244, !277, !279, !289, !290}
!34 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !31, file: !32, line: 160, baseType: !35, size: 1280, align: 64)
!35 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !36, line: 89, size: 1280, align: 64, elements: !37)
!36 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!37 = !{!38, !40, !41, !102, !103, !104, !105, !106, !107, !108, !109, !117, !118, !119, !120, !123, !124, !125, !126, !127, !128}
!38 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !35, file: !36, line: 96, baseType: !39, size: 32, align: 32)
!39 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!40 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !35, file: !36, line: 97, baseType: !39, size: 32, align: 32, offset: 32)
!41 = !DIDerivedType(tag: DW_TAG_member, name: "vtable", scope: !35, file: !36, line: 103, baseType: !42, size: 64, align: 64, offset: 64)
!42 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !43, size: 64, align: 64)
!43 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_vtable", file: !36, line: 63, size: 832, align: 64, elements: !44)
!44 = !{!45, !50, !51, !58, !59, !69, !73, !78, !79, !86, !87, !91, !95}
!45 = !DIDerivedType(tag: DW_TAG_member, name: "archive_close", scope: !43, file: !36, line: 64, baseType: !46, size: 64, align: 64)
!46 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !47, size: 64, align: 64)
!47 = !DISubroutineType(types: !48)
!48 = !{!22, !49}
!49 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !35, size: 64, align: 64)
!50 = !DIDerivedType(tag: DW_TAG_member, name: "archive_free", scope: !43, file: !36, line: 65, baseType: !46, size: 64, align: 64, offset: 64)
!51 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_header", scope: !43, file: !36, line: 66, baseType: !52, size: 64, align: 64, offset: 128)
!52 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !53, size: 64, align: 64)
!53 = !DISubroutineType(types: !54)
!54 = !{!22, !49, !55}
!55 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !56, size: 64, align: 64)
!56 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_entry", file: !57, line: 180, flags: DIFlagFwdDecl)
!57 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!58 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_finish_entry", scope: !43, file: !36, line: 68, baseType: !46, size: 64, align: 64, offset: 192)
!59 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data", scope: !43, file: !36, line: 69, baseType: !60, size: 64, align: 64, offset: 256)
!60 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !61, size: 64, align: 64)
!61 = !DISubroutineType(types: !62)
!62 = !{!63, !49, !67, !11}
!63 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !64, line: 109, baseType: !65)
!64 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!65 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !66, line: 172, baseType: !9)
!66 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!67 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !68, size: 64, align: 64)
!68 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!69 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data_block", scope: !43, file: !36, line: 71, baseType: !70, size: 64, align: 64, offset: 320)
!70 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !71, size: 64, align: 64)
!71 = !DISubroutineType(types: !72)
!72 = !{!63, !49, !67, !11, !7}
!73 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header", scope: !43, file: !36, line: 74, baseType: !74, size: 64, align: 64, offset: 384)
!74 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !75, size: 64, align: 64)
!75 = !DISubroutineType(types: !76)
!76 = !{!22, !49, !77}
!77 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !55, size: 64, align: 64)
!78 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header2", scope: !43, file: !36, line: 76, baseType: !52, size: 64, align: 64, offset: 448)
!79 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_data_block", scope: !43, file: !36, line: 78, baseType: !80, size: 64, align: 64, offset: 512)
!80 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !81, size: 64, align: 64)
!81 = !DISubroutineType(types: !82)
!82 = !{!22, !49, !83, !84, !85}
!83 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !67, size: 64, align: 64)
!84 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !11, size: 64, align: 64)
!85 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !7, size: 64, align: 64)
!86 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_count", scope: !43, file: !36, line: 81, baseType: !46, size: 64, align: 64, offset: 576)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_bytes", scope: !43, file: !36, line: 82, baseType: !88, size: 64, align: 64, offset: 640)
!88 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !89, size: 64, align: 64)
!89 = !DISubroutineType(types: !90)
!90 = !{!7, !49, !22}
!91 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_code", scope: !43, file: !36, line: 83, baseType: !92, size: 64, align: 64, offset: 704)
!92 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !93, size: 64, align: 64)
!93 = !DISubroutineType(types: !94)
!94 = !{!22, !49, !22}
!95 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_name", scope: !43, file: !36, line: 84, baseType: !96, size: 64, align: 64, offset: 768)
!96 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !97, size: 64, align: 64)
!97 = !DISubroutineType(types: !98)
!98 = !{!99, !49, !22}
!99 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !100, size: 64, align: 64)
!100 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !101)
!101 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!102 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format", scope: !35, file: !36, line: 105, baseType: !22, size: 32, align: 32, offset: 128)
!103 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format_name", scope: !35, file: !36, line: 106, baseType: !99, size: 64, align: 64, offset: 192)
!104 = !DIDerivedType(tag: DW_TAG_member, name: "compression_code", scope: !35, file: !36, line: 108, baseType: !22, size: 32, align: 32, offset: 256)
!105 = !DIDerivedType(tag: DW_TAG_member, name: "compression_name", scope: !35, file: !36, line: 109, baseType: !99, size: 64, align: 64, offset: 320)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "file_count", scope: !35, file: !36, line: 112, baseType: !22, size: 32, align: 32, offset: 384)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "archive_error_number", scope: !35, file: !36, line: 114, baseType: !22, size: 32, align: 32, offset: 416)
!108 = !DIDerivedType(tag: DW_TAG_member, name: "error", scope: !35, file: !36, line: 115, baseType: !99, size: 64, align: 64, offset: 448)
!109 = !DIDerivedType(tag: DW_TAG_member, name: "error_string", scope: !35, file: !36, line: 116, baseType: !110, size: 192, align: 64, offset: 512)
!110 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string", file: !111, line: 58, size: 192, align: 64, elements: !112)
!111 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_string.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!112 = !{!113, !115, !116}
!113 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !110, file: !111, line: 59, baseType: !114, size: 64, align: 64)
!114 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !101, size: 64, align: 64)
!115 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !110, file: !111, line: 60, baseType: !11, size: 64, align: 64, offset: 64)
!116 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !110, file: !111, line: 61, baseType: !11, size: 64, align: 64, offset: 128)
!117 = !DIDerivedType(tag: DW_TAG_member, name: "current_code", scope: !35, file: !36, line: 118, baseType: !114, size: 64, align: 64, offset: 704)
!118 = !DIDerivedType(tag: DW_TAG_member, name: "current_codepage", scope: !35, file: !36, line: 119, baseType: !39, size: 32, align: 32, offset: 768)
!119 = !DIDerivedType(tag: DW_TAG_member, name: "current_oemcp", scope: !35, file: !36, line: 120, baseType: !39, size: 32, align: 32, offset: 800)
!120 = !DIDerivedType(tag: DW_TAG_member, name: "sconv", scope: !35, file: !36, line: 121, baseType: !121, size: 64, align: 64, offset: 832)
!121 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !122, size: 64, align: 64)
!122 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string_conv", file: !111, line: 70, flags: DIFlagFwdDecl)
!123 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_block", scope: !35, file: !36, line: 127, baseType: !99, size: 64, align: 64, offset: 896)
!124 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_offset", scope: !35, file: !36, line: 128, baseType: !7, size: 64, align: 64, offset: 960)
!125 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_output_offset", scope: !35, file: !36, line: 129, baseType: !7, size: 64, align: 64, offset: 1024)
!126 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_remaining", scope: !35, file: !36, line: 130, baseType: !11, size: 64, align: 64, offset: 1088)
!127 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_is_posix_read", scope: !35, file: !36, line: 137, baseType: !101, size: 8, align: 8, offset: 1152)
!128 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_requested", scope: !35, file: !36, line: 138, baseType: !11, size: 64, align: 64, offset: 1216)
!129 = !DIDerivedType(tag: DW_TAG_member, name: "entry", scope: !31, file: !32, line: 162, baseType: !55, size: 64, align: 64, offset: 1280)
!130 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_set", scope: !31, file: !32, line: 165, baseType: !22, size: 32, align: 32, offset: 1344)
!131 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_dev", scope: !31, file: !32, line: 166, baseType: !7, size: 64, align: 64, offset: 1408)
!132 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_ino", scope: !31, file: !32, line: 167, baseType: !7, size: 64, align: 64, offset: 1472)
!133 = !DIDerivedType(tag: DW_TAG_member, name: "client", scope: !31, file: !32, line: 170, baseType: !134, size: 576, align: 64, offset: 1536)
!134 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_client", file: !32, line: 134, size: 576, align: 64, elements: !135)
!135 = !{!136, !142, !148, !154, !159, !162, !167, !168, !169, !170}
!136 = !DIDerivedType(tag: DW_TAG_member, name: "opener", scope: !134, file: !32, line: 135, baseType: !137, size: 64, align: 64)
!137 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !138, size: 64, align: 64)
!138 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_open_callback", file: !57, line: 241, baseType: !139)
!139 = !DISubroutineType(types: !140)
!140 = !{!22, !49, !141}
!141 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!142 = !DIDerivedType(tag: DW_TAG_member, name: "reader", scope: !134, file: !32, line: 136, baseType: !143, size: 64, align: 64, offset: 64)
!143 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !144, size: 64, align: 64)
!144 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_read_callback", file: !57, line: 218, baseType: !145)
!145 = !DISubroutineType(types: !146)
!146 = !{!147, !49, !141, !83}
!147 = !DIDerivedType(tag: DW_TAG_typedef, name: "la_ssize_t", file: !57, line: 95, baseType: !63)
!148 = !DIDerivedType(tag: DW_TAG_member, name: "skipper", scope: !134, file: !32, line: 137, baseType: !149, size: 64, align: 64, offset: 128)
!149 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !150, size: 64, align: 64)
!150 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_skip_callback", file: !57, line: 226, baseType: !151)
!151 = !DISubroutineType(types: !152)
!152 = !{!153, !49, !141, !153}
!153 = !DIDerivedType(tag: DW_TAG_typedef, name: "la_int64_t", file: !57, line: 73, baseType: !7)
!154 = !DIDerivedType(tag: DW_TAG_member, name: "seeker", scope: !134, file: !32, line: 138, baseType: !155, size: 64, align: 64, offset: 192)
!155 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !156, size: 64, align: 64)
!156 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_seek_callback", file: !57, line: 233, baseType: !157)
!157 = !DISubroutineType(types: !158)
!158 = !{!153, !49, !141, !153, !22}
!159 = !DIDerivedType(tag: DW_TAG_member, name: "closer", scope: !134, file: !32, line: 139, baseType: !160, size: 64, align: 64, offset: 256)
!160 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !161, size: 64, align: 64)
!161 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_close_callback", file: !57, line: 243, baseType: !139)
!162 = !DIDerivedType(tag: DW_TAG_member, name: "switcher", scope: !134, file: !32, line: 140, baseType: !163, size: 64, align: 64, offset: 320)
!163 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !164, size: 64, align: 64)
!164 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_switch_callback", file: !57, line: 249, baseType: !165)
!165 = !DISubroutineType(types: !166)
!166 = !{!22, !49, !141, !141}
!167 = !DIDerivedType(tag: DW_TAG_member, name: "nodes", scope: !134, file: !32, line: 141, baseType: !39, size: 32, align: 32, offset: 384)
!168 = !DIDerivedType(tag: DW_TAG_member, name: "cursor", scope: !134, file: !32, line: 142, baseType: !39, size: 32, align: 32, offset: 416)
!169 = !DIDerivedType(tag: DW_TAG_member, name: "position", scope: !134, file: !32, line: 143, baseType: !7, size: 64, align: 64, offset: 448)
!170 = !DIDerivedType(tag: DW_TAG_member, name: "dataset", scope: !134, file: !32, line: 144, baseType: !171, size: 64, align: 64, offset: 512)
!171 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !172, size: 64, align: 64)
!172 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_data_node", file: !32, line: 129, size: 192, align: 64, elements: !173)
!173 = !{!174, !175, !176}
!174 = !DIDerivedType(tag: DW_TAG_member, name: "begin_position", scope: !172, file: !32, line: 130, baseType: !7, size: 64, align: 64)
!175 = !DIDerivedType(tag: DW_TAG_member, name: "total_size", scope: !172, file: !32, line: 131, baseType: !7, size: 64, align: 64, offset: 64)
!176 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !172, file: !32, line: 132, baseType: !141, size: 64, align: 64, offset: 128)
!177 = !DIDerivedType(tag: DW_TAG_member, name: "bidders", scope: !31, file: !32, line: 173, baseType: !178, size: 6144, align: 64, offset: 2112)
!178 = !DICompositeType(tag: DW_TAG_array_type, baseType: !179, size: 6144, align: 64, elements: !18)
!179 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_filter_bidder", file: !32, line: 60, size: 384, align: 64, elements: !180)
!180 = !{!181, !182, !183, !230, !231, !235}
!181 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !179, file: !32, line: 62, baseType: !141, size: 64, align: 64)
!182 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !179, file: !32, line: 64, baseType: !99, size: 64, align: 64, offset: 64)
!183 = !DIDerivedType(tag: DW_TAG_member, name: "bid", scope: !179, file: !32, line: 66, baseType: !184, size: 64, align: 64, offset: 128)
!184 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !185, size: 64, align: 64)
!185 = !DISubroutineType(types: !186)
!186 = !{!22, !187, !188}
!187 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !179, size: 64, align: 64)
!188 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !189, size: 64, align: 64)
!189 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_filter", file: !32, line: 82, size: 1408, align: 64, elements: !190)
!190 = !{!191, !192, !193, !194, !195, !199, !203, !207, !211, !212, !216, !217, !218, !219, !220, !221, !222, !223, !224, !225, !226, !227, !228, !229}
!191 = !DIDerivedType(tag: DW_TAG_member, name: "position", scope: !189, file: !32, line: 83, baseType: !7, size: 64, align: 64)
!192 = !DIDerivedType(tag: DW_TAG_member, name: "bidder", scope: !189, file: !32, line: 86, baseType: !187, size: 64, align: 64, offset: 64)
!193 = !DIDerivedType(tag: DW_TAG_member, name: "upstream", scope: !189, file: !32, line: 87, baseType: !188, size: 64, align: 64, offset: 128)
!194 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !189, file: !32, line: 88, baseType: !30, size: 64, align: 64, offset: 192)
!195 = !DIDerivedType(tag: DW_TAG_member, name: "open", scope: !189, file: !32, line: 90, baseType: !196, size: 64, align: 64, offset: 256)
!196 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !197, size: 64, align: 64)
!197 = !DISubroutineType(types: !198)
!198 = !{!22, !188}
!199 = !DIDerivedType(tag: DW_TAG_member, name: "read", scope: !189, file: !32, line: 92, baseType: !200, size: 64, align: 64, offset: 320)
!200 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !201, size: 64, align: 64)
!201 = !DISubroutineType(types: !202)
!202 = !{!63, !188, !83}
!203 = !DIDerivedType(tag: DW_TAG_member, name: "skip", scope: !189, file: !32, line: 94, baseType: !204, size: 64, align: 64, offset: 384)
!204 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !205, size: 64, align: 64)
!205 = !DISubroutineType(types: !206)
!206 = !{!7, !188, !7}
!207 = !DIDerivedType(tag: DW_TAG_member, name: "seek", scope: !189, file: !32, line: 96, baseType: !208, size: 64, align: 64, offset: 448)
!208 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !209, size: 64, align: 64)
!209 = !DISubroutineType(types: !210)
!210 = !{!7, !188, !7, !22}
!211 = !DIDerivedType(tag: DW_TAG_member, name: "close", scope: !189, file: !32, line: 98, baseType: !196, size: 64, align: 64, offset: 512)
!212 = !DIDerivedType(tag: DW_TAG_member, name: "sswitch", scope: !189, file: !32, line: 100, baseType: !213, size: 64, align: 64, offset: 576)
!213 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !214, size: 64, align: 64)
!214 = !DISubroutineType(types: !215)
!215 = !{!22, !188, !39}
!216 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !189, file: !32, line: 102, baseType: !141, size: 64, align: 64, offset: 640)
!217 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !189, file: !32, line: 104, baseType: !99, size: 64, align: 64, offset: 704)
!218 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !189, file: !32, line: 105, baseType: !22, size: 32, align: 32, offset: 768)
!219 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !189, file: !32, line: 108, baseType: !114, size: 64, align: 64, offset: 832)
!220 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_size", scope: !189, file: !32, line: 109, baseType: !11, size: 64, align: 64, offset: 896)
!221 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !189, file: !32, line: 110, baseType: !114, size: 64, align: 64, offset: 960)
!222 = !DIDerivedType(tag: DW_TAG_member, name: "avail", scope: !189, file: !32, line: 111, baseType: !11, size: 64, align: 64, offset: 1024)
!223 = !DIDerivedType(tag: DW_TAG_member, name: "client_buff", scope: !189, file: !32, line: 112, baseType: !67, size: 64, align: 64, offset: 1088)
!224 = !DIDerivedType(tag: DW_TAG_member, name: "client_total", scope: !189, file: !32, line: 113, baseType: !11, size: 64, align: 64, offset: 1152)
!225 = !DIDerivedType(tag: DW_TAG_member, name: "client_next", scope: !189, file: !32, line: 114, baseType: !99, size: 64, align: 64, offset: 1216)
!226 = !DIDerivedType(tag: DW_TAG_member, name: "client_avail", scope: !189, file: !32, line: 115, baseType: !11, size: 64, align: 64, offset: 1280)
!227 = !DIDerivedType(tag: DW_TAG_member, name: "end_of_file", scope: !189, file: !32, line: 116, baseType: !101, size: 8, align: 8, offset: 1344)
!228 = !DIDerivedType(tag: DW_TAG_member, name: "closed", scope: !189, file: !32, line: 117, baseType: !101, size: 8, align: 8, offset: 1352)
!229 = !DIDerivedType(tag: DW_TAG_member, name: "fatal", scope: !189, file: !32, line: 118, baseType: !101, size: 8, align: 8, offset: 1360)
!230 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !179, file: !32, line: 69, baseType: !196, size: 64, align: 64, offset: 192)
!231 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !179, file: !32, line: 71, baseType: !232, size: 64, align: 64, offset: 256)
!232 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !233, size: 64, align: 64)
!233 = !DISubroutineType(types: !234)
!234 = !{!22, !187, !99, !99}
!235 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !179, file: !32, line: 74, baseType: !236, size: 64, align: 64, offset: 320)
!236 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !237, size: 64, align: 64)
!237 = !DISubroutineType(types: !238)
!238 = !{!22, !187}
!239 = !DIDerivedType(tag: DW_TAG_member, name: "filter", scope: !31, file: !32, line: 176, baseType: !188, size: 64, align: 64, offset: 8256)
!240 = !DIDerivedType(tag: DW_TAG_member, name: "bypass_filter_bidding", scope: !31, file: !32, line: 179, baseType: !22, size: 32, align: 32, offset: 8320)
!241 = !DIDerivedType(tag: DW_TAG_member, name: "header_position", scope: !31, file: !32, line: 182, baseType: !7, size: 64, align: 64, offset: 8384)
!242 = !DIDerivedType(tag: DW_TAG_member, name: "data_start_node", scope: !31, file: !32, line: 185, baseType: !39, size: 32, align: 32, offset: 8448)
!243 = !DIDerivedType(tag: DW_TAG_member, name: "data_end_node", scope: !31, file: !32, line: 186, baseType: !39, size: 32, align: 32, offset: 8480)
!244 = !DIDerivedType(tag: DW_TAG_member, name: "formats", scope: !31, file: !32, line: 209, baseType: !245, size: 11264, align: 64, offset: 8512)
!245 = !DICompositeType(tag: DW_TAG_array_type, baseType: !246, size: 11264, align: 64, elements: !18)
!246 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_format_descriptor", file: !32, line: 196, size: 704, align: 64, elements: !247)
!247 = !{!248, !249, !250, !254, !258, !262, !266, !270, !274, !275, !276}
!248 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !246, file: !32, line: 197, baseType: !141, size: 64, align: 64)
!249 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !246, file: !32, line: 198, baseType: !99, size: 64, align: 64, offset: 64)
!250 = !DIDerivedType(tag: DW_TAG_member, name: "bid", scope: !246, file: !32, line: 199, baseType: !251, size: 64, align: 64, offset: 128)
!251 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !252, size: 64, align: 64)
!252 = !DISubroutineType(types: !253)
!253 = !{!22, !30, !22}
!254 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !246, file: !32, line: 200, baseType: !255, size: 64, align: 64, offset: 192)
!255 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !256, size: 64, align: 64)
!256 = !DISubroutineType(types: !257)
!257 = !{!22, !30, !99, !99}
!258 = !DIDerivedType(tag: DW_TAG_member, name: "read_header", scope: !246, file: !32, line: 202, baseType: !259, size: 64, align: 64, offset: 256)
!259 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !260, size: 64, align: 64)
!260 = !DISubroutineType(types: !261)
!261 = !{!22, !30, !55}
!262 = !DIDerivedType(tag: DW_TAG_member, name: "read_data", scope: !246, file: !32, line: 203, baseType: !263, size: 64, align: 64, offset: 320)
!263 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !264, size: 64, align: 64)
!264 = !DISubroutineType(types: !265)
!265 = !{!22, !30, !83, !84, !85}
!266 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_skip", scope: !246, file: !32, line: 204, baseType: !267, size: 64, align: 64, offset: 384)
!267 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !268, size: 64, align: 64)
!268 = !DISubroutineType(types: !269)
!269 = !{!22, !30}
!270 = !DIDerivedType(tag: DW_TAG_member, name: "seek_data", scope: !246, file: !32, line: 205, baseType: !271, size: 64, align: 64, offset: 448)
!271 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !272, size: 64, align: 64)
!272 = !DISubroutineType(types: !273)
!273 = !{!7, !30, !7, !22}
!274 = !DIDerivedType(tag: DW_TAG_member, name: "cleanup", scope: !246, file: !32, line: 206, baseType: !267, size: 64, align: 64, offset: 512)
!275 = !DIDerivedType(tag: DW_TAG_member, name: "format_capabilties", scope: !246, file: !32, line: 207, baseType: !267, size: 64, align: 64, offset: 576)
!276 = !DIDerivedType(tag: DW_TAG_member, name: "has_encrypted_entries", scope: !246, file: !32, line: 208, baseType: !267, size: 64, align: 64, offset: 640)
!277 = !DIDerivedType(tag: DW_TAG_member, name: "format", scope: !31, file: !32, line: 210, baseType: !278, size: 64, align: 64, offset: 19776)
!278 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !246, size: 64, align: 64)
!279 = !DIDerivedType(tag: DW_TAG_member, name: "extract", scope: !31, file: !32, line: 215, baseType: !280, size: 64, align: 64, offset: 19840)
!280 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !281, size: 64, align: 64)
!281 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_extract", file: !32, line: 151, size: 192, align: 64, elements: !282)
!282 = !{!283, !284, !288}
!283 = !DIDerivedType(tag: DW_TAG_member, name: "ad", scope: !281, file: !32, line: 152, baseType: !49, size: 64, align: 64)
!284 = !DIDerivedType(tag: DW_TAG_member, name: "extract_progress", scope: !281, file: !32, line: 155, baseType: !285, size: 64, align: 64, offset: 64)
!285 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !286, size: 64, align: 64)
!286 = !DISubroutineType(types: !287)
!287 = !{null, !141}
!288 = !DIDerivedType(tag: DW_TAG_member, name: "extract_progress_user_data", scope: !281, file: !32, line: 156, baseType: !141, size: 64, align: 64, offset: 128)
!289 = !DIDerivedType(tag: DW_TAG_member, name: "cleanup_archive_extract", scope: !31, file: !32, line: 216, baseType: !267, size: 64, align: 64, offset: 19904)
!290 = !DIDerivedType(tag: DW_TAG_member, name: "passphrases", scope: !31, file: !32, line: 227, baseType: !291, size: 320, align: 64, offset: 19968)
!291 = !DICompositeType(tag: DW_TAG_structure_type, scope: !31, file: !32, line: 221, size: 320, align: 64, elements: !292)
!292 = !{!293, !299, !301, !302, !307}
!293 = !DIDerivedType(tag: DW_TAG_member, name: "first", scope: !291, file: !32, line: 222, baseType: !294, size: 64, align: 64)
!294 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !295, size: 64, align: 64)
!295 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_passphrase", file: !32, line: 146, size: 128, align: 64, elements: !296)
!296 = !{!297, !298}
!297 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase", scope: !295, file: !32, line: 147, baseType: !114, size: 64, align: 64)
!298 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !295, file: !32, line: 148, baseType: !294, size: 64, align: 64, offset: 64)
!299 = !DIDerivedType(tag: DW_TAG_member, name: "last", scope: !291, file: !32, line: 223, baseType: !300, size: 64, align: 64, offset: 64)
!300 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !294, size: 64, align: 64)
!301 = !DIDerivedType(tag: DW_TAG_member, name: "candidate", scope: !291, file: !32, line: 224, baseType: !22, size: 32, align: 32, offset: 128)
!302 = !DIDerivedType(tag: DW_TAG_member, name: "callback", scope: !291, file: !32, line: 225, baseType: !303, size: 64, align: 64, offset: 192)
!303 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !304, size: 64, align: 64)
!304 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_passphrase_callback", file: !57, line: 256, baseType: !305)
!305 = !DISubroutineType(types: !306)
!306 = !{!99, !49, !141}
!307 = !DIDerivedType(tag: DW_TAG_member, name: "client_data", scope: !291, file: !32, line: 226, baseType: !141, size: 64, align: 64, offset: 256)
!308 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !4, size: 64, align: 64)
!309 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !310, size: 64, align: 64)
!310 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !17)
!311 = !{!312, !314, !315, !316, !317, !318, !323}
!312 = distinct !DISubprogram(name: "archive_read_support_compression_rpm", scope: !1, file: !1, line: 69, type: !47, isLocal: false, isDefinition: true, scopeLine: 70, flags: DIFlagPrototyped, isOptimized: false, variables: !313)
!313 = !{}
!314 = distinct !DISubprogram(name: "archive_read_support_filter_rpm", scope: !1, file: !1, line: 76, type: !47, isLocal: false, isDefinition: true, scopeLine: 77, flags: DIFlagPrototyped, isOptimized: false, variables: !313)
!315 = distinct !DISubprogram(name: "rpm_bidder_bid", scope: !1, file: !1, line: 97, type: !185, isLocal: true, isDefinition: true, scopeLine: 99, flags: DIFlagPrototyped, isOptimized: false, variables: !313)
!316 = distinct !DISubprogram(name: "rpm_bidder_init", scope: !1, file: !1, line: 137, type: !197, isLocal: true, isDefinition: true, scopeLine: 138, flags: DIFlagPrototyped, isOptimized: false, variables: !313)
!317 = distinct !DISubprogram(name: "rpm_filter_read", scope: !1, file: !1, line: 161, type: !201, isLocal: true, isDefinition: true, scopeLine: 162, flags: DIFlagPrototyped, isOptimized: false, variables: !313)
!318 = distinct !DISubprogram(name: "archive_be32dec", scope: !319, file: !319, line: 77, type: !320, isLocal: true, isDefinition: true, scopeLine: 78, flags: DIFlagPrototyped, isOptimized: false, variables: !313)
!319 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_endian.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!320 = !DISubroutineType(types: !321)
!321 = !{!322, !67}
!322 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !8, line: 51, baseType: !39)
!323 = distinct !DISubprogram(name: "rpm_filter_close", scope: !1, file: !1, line: 280, type: !197, isLocal: true, isDefinition: true, scopeLine: 281, flags: DIFlagPrototyped, isOptimized: false, variables: !313)
!324 = !{i32 2, !"Dwarf Version", i32 4}
!325 = !{i32 2, !"Debug Info Version", i32 3}
!326 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!327 = !DILocalVariable(name: "a", arg: 1, scope: !312, file: !1, line: 69, type: !49)
!328 = !DIExpression()
!329 = !DILocation(line: 69, column: 54, scope: !312)
!330 = !DILocation(line: 71, column: 41, scope: !312)
!331 = !DILocation(line: 71, column: 9, scope: !312)
!332 = !DILocation(line: 71, column: 2, scope: !312)
!333 = !DILocalVariable(name: "_a", arg: 1, scope: !314, file: !1, line: 76, type: !49)
!334 = !DILocation(line: 76, column: 49, scope: !314)
!335 = !DILocalVariable(name: "a", scope: !314, file: !1, line: 78, type: !30)
!336 = !DILocation(line: 78, column: 23, scope: !314)
!337 = !DILocation(line: 78, column: 50, scope: !314)
!338 = !DILocation(line: 78, column: 27, scope: !314)
!339 = !DILocalVariable(name: "bidder", scope: !314, file: !1, line: 79, type: !187)
!340 = !DILocation(line: 79, column: 37, scope: !314)
!341 = !DILocation(line: 81, column: 2, scope: !314)
!342 = !DILocalVariable(name: "magic_test", scope: !343, file: !1, line: 81, type: !22)
!343 = distinct !DILexicalBlock(scope: !314, file: !1, line: 81, column: 2)
!344 = !DILocation(line: 81, column: 2, scope: !343)
!345 = !DILocation(line: 81, column: 2, scope: !346)
!346 = !DILexicalBlockFile(scope: !343, file: !1, discriminator: 1)
!347 = !DILocation(line: 81, column: 2, scope: !348)
!348 = !DILexicalBlockFile(scope: !349, file: !1, discriminator: 2)
!349 = distinct !DILexicalBlock(scope: !343, file: !1, line: 81, column: 2)
!350 = !DILocation(line: 81, column: 2, scope: !351)
!351 = !DILexicalBlockFile(scope: !343, file: !1, discriminator: 3)
!352 = !DILocation(line: 84, column: 32, scope: !353)
!353 = distinct !DILexicalBlock(scope: !314, file: !1, line: 84, column: 6)
!354 = !DILocation(line: 84, column: 6, scope: !353)
!355 = !DILocation(line: 84, column: 44, scope: !353)
!356 = !DILocation(line: 84, column: 6, scope: !314)
!357 = !DILocation(line: 85, column: 3, scope: !353)
!358 = !DILocation(line: 87, column: 2, scope: !314)
!359 = !DILocation(line: 87, column: 10, scope: !314)
!360 = !DILocation(line: 87, column: 15, scope: !314)
!361 = !DILocation(line: 88, column: 2, scope: !314)
!362 = !DILocation(line: 88, column: 10, scope: !314)
!363 = !DILocation(line: 88, column: 15, scope: !314)
!364 = !DILocation(line: 89, column: 2, scope: !314)
!365 = !DILocation(line: 89, column: 10, scope: !314)
!366 = !DILocation(line: 89, column: 14, scope: !314)
!367 = !DILocation(line: 90, column: 2, scope: !314)
!368 = !DILocation(line: 90, column: 10, scope: !314)
!369 = !DILocation(line: 90, column: 15, scope: !314)
!370 = !DILocation(line: 91, column: 2, scope: !314)
!371 = !DILocation(line: 91, column: 10, scope: !314)
!372 = !DILocation(line: 91, column: 18, scope: !314)
!373 = !DILocation(line: 92, column: 2, scope: !314)
!374 = !DILocation(line: 92, column: 10, scope: !314)
!375 = !DILocation(line: 92, column: 15, scope: !314)
!376 = !DILocation(line: 93, column: 2, scope: !314)
!377 = !DILocation(line: 94, column: 1, scope: !314)
!378 = !DILocalVariable(name: "self", arg: 1, scope: !315, file: !1, line: 97, type: !187)
!379 = !DILocation(line: 97, column: 51, scope: !315)
!380 = !DILocalVariable(name: "filter", arg: 2, scope: !315, file: !1, line: 98, type: !188)
!381 = !DILocation(line: 98, column: 33, scope: !315)
!382 = !DILocalVariable(name: "b", scope: !315, file: !1, line: 100, type: !309)
!383 = !DILocation(line: 100, column: 23, scope: !315)
!384 = !DILocalVariable(name: "avail", scope: !315, file: !1, line: 101, type: !63)
!385 = !DILocation(line: 101, column: 10, scope: !315)
!386 = !DILocalVariable(name: "bits_checked", scope: !315, file: !1, line: 102, type: !22)
!387 = !DILocation(line: 102, column: 6, scope: !315)
!388 = !DILocation(line: 104, column: 8, scope: !315)
!389 = !DILocation(line: 106, column: 34, scope: !315)
!390 = !DILocation(line: 106, column: 6, scope: !315)
!391 = !DILocation(line: 106, column: 4, scope: !315)
!392 = !DILocation(line: 107, column: 6, scope: !393)
!393 = distinct !DILexicalBlock(scope: !315, file: !1, line: 107, column: 6)
!394 = !DILocation(line: 107, column: 8, scope: !393)
!395 = !DILocation(line: 107, column: 6, scope: !315)
!396 = !DILocation(line: 108, column: 3, scope: !393)
!397 = !DILocation(line: 110, column: 15, scope: !315)
!398 = !DILocation(line: 114, column: 13, scope: !399)
!399 = distinct !DILexicalBlock(scope: !315, file: !1, line: 114, column: 6)
!400 = !DILocation(line: 114, column: 6, scope: !399)
!401 = !DILocation(line: 114, column: 39, scope: !399)
!402 = !DILocation(line: 114, column: 6, scope: !315)
!403 = !DILocation(line: 115, column: 3, scope: !399)
!404 = !DILocation(line: 116, column: 15, scope: !315)
!405 = !DILocation(line: 120, column: 6, scope: !406)
!406 = distinct !DILexicalBlock(scope: !315, file: !1, line: 120, column: 6)
!407 = !DILocation(line: 120, column: 11, scope: !406)
!408 = !DILocation(line: 120, column: 16, scope: !406)
!409 = !DILocation(line: 120, column: 19, scope: !410)
!410 = !DILexicalBlockFile(scope: !406, file: !1, discriminator: 1)
!411 = !DILocation(line: 120, column: 24, scope: !410)
!412 = !DILocation(line: 120, column: 6, scope: !410)
!413 = !DILocation(line: 121, column: 3, scope: !406)
!414 = !DILocation(line: 122, column: 15, scope: !315)
!415 = !DILocation(line: 126, column: 6, scope: !416)
!416 = distinct !DILexicalBlock(scope: !315, file: !1, line: 126, column: 6)
!417 = !DILocation(line: 126, column: 11, scope: !416)
!418 = !DILocation(line: 126, column: 6, scope: !315)
!419 = !DILocation(line: 127, column: 3, scope: !416)
!420 = !DILocation(line: 128, column: 15, scope: !315)
!421 = !DILocation(line: 129, column: 6, scope: !422)
!422 = distinct !DILexicalBlock(scope: !315, file: !1, line: 129, column: 6)
!423 = !DILocation(line: 129, column: 11, scope: !422)
!424 = !DILocation(line: 129, column: 16, scope: !422)
!425 = !DILocation(line: 129, column: 19, scope: !426)
!426 = !DILexicalBlockFile(scope: !422, file: !1, discriminator: 1)
!427 = !DILocation(line: 129, column: 24, scope: !426)
!428 = !DILocation(line: 129, column: 6, scope: !426)
!429 = !DILocation(line: 130, column: 3, scope: !422)
!430 = !DILocation(line: 131, column: 15, scope: !315)
!431 = !DILocation(line: 133, column: 10, scope: !315)
!432 = !DILocation(line: 133, column: 2, scope: !315)
!433 = !DILocation(line: 134, column: 1, scope: !315)
!434 = !DILocalVariable(name: "self", arg: 1, scope: !316, file: !1, line: 137, type: !188)
!435 = !DILocation(line: 137, column: 45, scope: !316)
!436 = !DILocalVariable(name: "rpm", scope: !316, file: !1, line: 139, type: !308)
!437 = !DILocation(line: 139, column: 16, scope: !316)
!438 = !DILocation(line: 141, column: 2, scope: !316)
!439 = !DILocation(line: 141, column: 8, scope: !316)
!440 = !DILocation(line: 141, column: 13, scope: !316)
!441 = !DILocation(line: 142, column: 2, scope: !316)
!442 = !DILocation(line: 142, column: 8, scope: !316)
!443 = !DILocation(line: 142, column: 13, scope: !316)
!444 = !DILocation(line: 143, column: 2, scope: !316)
!445 = !DILocation(line: 143, column: 8, scope: !316)
!446 = !DILocation(line: 143, column: 13, scope: !316)
!447 = !DILocation(line: 144, column: 2, scope: !316)
!448 = !DILocation(line: 144, column: 8, scope: !316)
!449 = !DILocation(line: 144, column: 13, scope: !316)
!450 = !DILocation(line: 145, column: 2, scope: !316)
!451 = !DILocation(line: 145, column: 8, scope: !316)
!452 = !DILocation(line: 145, column: 14, scope: !316)
!453 = !DILocation(line: 147, column: 22, scope: !316)
!454 = !DILocation(line: 147, column: 8, scope: !316)
!455 = !DILocation(line: 147, column: 6, scope: !316)
!456 = !DILocation(line: 148, column: 6, scope: !457)
!457 = distinct !DILexicalBlock(scope: !316, file: !1, line: 148, column: 6)
!458 = !DILocation(line: 148, column: 10, scope: !457)
!459 = !DILocation(line: 148, column: 6, scope: !316)
!460 = !DILocation(line: 149, column: 22, scope: !461)
!461 = distinct !DILexicalBlock(scope: !457, file: !1, line: 148, column: 19)
!462 = !DILocation(line: 149, column: 28, scope: !461)
!463 = !DILocation(line: 149, column: 37, scope: !461)
!464 = !DILocation(line: 149, column: 3, scope: !461)
!465 = !DILocation(line: 151, column: 3, scope: !461)
!466 = !DILocation(line: 154, column: 15, scope: !316)
!467 = !DILocation(line: 154, column: 2, scope: !316)
!468 = !DILocation(line: 154, column: 8, scope: !316)
!469 = !DILocation(line: 154, column: 13, scope: !316)
!470 = !DILocation(line: 155, column: 2, scope: !316)
!471 = !DILocation(line: 155, column: 7, scope: !316)
!472 = !DILocation(line: 155, column: 13, scope: !316)
!473 = !DILocation(line: 157, column: 2, scope: !316)
!474 = !DILocation(line: 158, column: 1, scope: !316)
!475 = !DILocalVariable(name: "self", arg: 1, scope: !317, file: !1, line: 161, type: !188)
!476 = !DILocation(line: 161, column: 45, scope: !317)
!477 = !DILocalVariable(name: "buff", arg: 2, scope: !317, file: !1, line: 161, type: !83)
!478 = !DILocation(line: 161, column: 64, scope: !317)
!479 = !DILocalVariable(name: "rpm", scope: !317, file: !1, line: 163, type: !308)
!480 = !DILocation(line: 163, column: 14, scope: !317)
!481 = !DILocalVariable(name: "b", scope: !317, file: !1, line: 164, type: !309)
!482 = !DILocation(line: 164, column: 23, scope: !317)
!483 = !DILocalVariable(name: "avail_in", scope: !317, file: !1, line: 165, type: !63)
!484 = !DILocation(line: 165, column: 10, scope: !317)
!485 = !DILocalVariable(name: "total", scope: !317, file: !1, line: 165, type: !63)
!486 = !DILocation(line: 165, column: 20, scope: !317)
!487 = !DILocalVariable(name: "used", scope: !317, file: !1, line: 166, type: !11)
!488 = !DILocation(line: 166, column: 9, scope: !317)
!489 = !DILocalVariable(name: "n", scope: !317, file: !1, line: 166, type: !11)
!490 = !DILocation(line: 166, column: 15, scope: !317)
!491 = !DILocalVariable(name: "section", scope: !317, file: !1, line: 167, type: !322)
!492 = !DILocation(line: 167, column: 11, scope: !317)
!493 = !DILocalVariable(name: "bytes", scope: !317, file: !1, line: 168, type: !322)
!494 = !DILocation(line: 168, column: 11, scope: !317)
!495 = !DILocation(line: 170, column: 22, scope: !317)
!496 = !DILocation(line: 170, column: 28, scope: !317)
!497 = !DILocation(line: 170, column: 8, scope: !317)
!498 = !DILocation(line: 170, column: 6, scope: !317)
!499 = !DILocation(line: 171, column: 3, scope: !317)
!500 = !DILocation(line: 171, column: 8, scope: !317)
!501 = !DILocation(line: 172, column: 19, scope: !317)
!502 = !DILocation(line: 172, column: 8, scope: !317)
!503 = !DILocation(line: 173, column: 4, scope: !317)
!504 = !DILocation(line: 174, column: 7, scope: !317)
!505 = !DILocation(line: 175, column: 2, scope: !317)
!506 = !DILocation(line: 176, column: 7, scope: !507)
!507 = distinct !DILexicalBlock(scope: !508, file: !1, line: 176, column: 7)
!508 = distinct !DILexicalBlock(scope: !317, file: !1, line: 175, column: 5)
!509 = !DILocation(line: 176, column: 9, scope: !507)
!510 = !DILocation(line: 176, column: 7, scope: !508)
!511 = !DILocation(line: 177, column: 36, scope: !512)
!512 = distinct !DILexicalBlock(scope: !507, file: !1, line: 176, column: 18)
!513 = !DILocation(line: 177, column: 42, scope: !512)
!514 = !DILocation(line: 177, column: 8, scope: !512)
!515 = !DILocation(line: 177, column: 6, scope: !512)
!516 = !DILocation(line: 179, column: 8, scope: !517)
!517 = distinct !DILexicalBlock(scope: !512, file: !1, line: 179, column: 8)
!518 = !DILocation(line: 179, column: 10, scope: !517)
!519 = !DILocation(line: 179, column: 8, scope: !512)
!520 = !DILocation(line: 180, column: 9, scope: !521)
!521 = distinct !DILexicalBlock(scope: !522, file: !1, line: 180, column: 9)
!522 = distinct !DILexicalBlock(scope: !517, file: !1, line: 179, column: 19)
!523 = !DILocation(line: 180, column: 18, scope: !521)
!524 = !DILocation(line: 180, column: 9, scope: !522)
!525 = !DILocation(line: 181, column: 6, scope: !521)
!526 = !DILocation(line: 183, column: 6, scope: !521)
!527 = !DILocation(line: 185, column: 3, scope: !512)
!528 = !DILocation(line: 187, column: 11, scope: !508)
!529 = !DILocation(line: 187, column: 16, scope: !508)
!530 = !DILocation(line: 187, column: 3, scope: !508)
!531 = !DILocation(line: 189, column: 8, scope: !532)
!532 = distinct !DILexicalBlock(scope: !533, file: !1, line: 189, column: 8)
!533 = distinct !DILexicalBlock(scope: !508, file: !1, line: 187, column: 23)
!534 = !DILocation(line: 189, column: 13, scope: !532)
!535 = !DILocation(line: 189, column: 24, scope: !532)
!536 = !DILocation(line: 189, column: 22, scope: !532)
!537 = !DILocation(line: 189, column: 33, scope: !532)
!538 = !DILocation(line: 189, column: 8, scope: !533)
!539 = !DILocation(line: 190, column: 13, scope: !532)
!540 = !DILocation(line: 190, column: 10, scope: !532)
!541 = !DILocation(line: 190, column: 5, scope: !532)
!542 = !DILocation(line: 192, column: 34, scope: !543)
!543 = distinct !DILexicalBlock(scope: !532, file: !1, line: 191, column: 9)
!544 = !DILocation(line: 192, column: 39, scope: !543)
!545 = !DILocation(line: 192, column: 32, scope: !543)
!546 = !DILocation(line: 192, column: 7, scope: !543)
!547 = !DILocation(line: 193, column: 13, scope: !543)
!548 = !DILocation(line: 193, column: 10, scope: !543)
!549 = !DILocation(line: 194, column: 10, scope: !543)
!550 = !DILocation(line: 194, column: 7, scope: !543)
!551 = !DILocation(line: 195, column: 5, scope: !543)
!552 = !DILocation(line: 195, column: 10, scope: !543)
!553 = !DILocation(line: 195, column: 16, scope: !543)
!554 = !DILocation(line: 196, column: 5, scope: !543)
!555 = !DILocation(line: 196, column: 10, scope: !543)
!556 = !DILocation(line: 196, column: 15, scope: !543)
!557 = !DILocation(line: 197, column: 5, scope: !543)
!558 = !DILocation(line: 197, column: 10, scope: !543)
!559 = !DILocation(line: 197, column: 15, scope: !543)
!560 = !DILocation(line: 198, column: 5, scope: !543)
!561 = !DILocation(line: 198, column: 10, scope: !543)
!562 = !DILocation(line: 198, column: 23, scope: !543)
!563 = !DILocation(line: 200, column: 4, scope: !533)
!564 = !DILocation(line: 202, column: 13, scope: !533)
!565 = !DILocation(line: 202, column: 18, scope: !533)
!566 = !DILocation(line: 202, column: 11, scope: !533)
!567 = !DILocation(line: 202, column: 6, scope: !533)
!568 = !DILocation(line: 203, column: 8, scope: !569)
!569 = distinct !DILexicalBlock(scope: !533, file: !1, line: 203, column: 8)
!570 = !DILocation(line: 203, column: 12, scope: !569)
!571 = !DILocation(line: 203, column: 23, scope: !569)
!572 = !DILocation(line: 203, column: 21, scope: !569)
!573 = !DILocation(line: 203, column: 10, scope: !569)
!574 = !DILocation(line: 203, column: 8, scope: !533)
!575 = !DILocation(line: 204, column: 9, scope: !569)
!576 = !DILocation(line: 204, column: 20, scope: !569)
!577 = !DILocation(line: 204, column: 18, scope: !569)
!578 = !DILocation(line: 204, column: 7, scope: !569)
!579 = !DILocation(line: 204, column: 5, scope: !569)
!580 = !DILocation(line: 205, column: 11, scope: !533)
!581 = !DILocation(line: 205, column: 16, scope: !533)
!582 = !DILocation(line: 205, column: 23, scope: !533)
!583 = !DILocation(line: 205, column: 28, scope: !533)
!584 = !DILocation(line: 205, column: 22, scope: !533)
!585 = !DILocation(line: 205, column: 34, scope: !533)
!586 = !DILocation(line: 205, column: 37, scope: !533)
!587 = !DILocation(line: 205, column: 4, scope: !533)
!588 = !DILocation(line: 206, column: 9, scope: !533)
!589 = !DILocation(line: 206, column: 6, scope: !533)
!590 = !DILocation(line: 207, column: 12, scope: !533)
!591 = !DILocation(line: 207, column: 9, scope: !533)
!592 = !DILocation(line: 208, column: 17, scope: !533)
!593 = !DILocation(line: 208, column: 4, scope: !533)
!594 = !DILocation(line: 208, column: 9, scope: !533)
!595 = !DILocation(line: 208, column: 14, scope: !533)
!596 = !DILocation(line: 210, column: 8, scope: !597)
!597 = distinct !DILexicalBlock(scope: !533, file: !1, line: 210, column: 8)
!598 = !DILocation(line: 210, column: 13, scope: !597)
!599 = !DILocation(line: 210, column: 18, scope: !597)
!600 = !DILocation(line: 210, column: 8, scope: !533)
!601 = !DILocation(line: 211, column: 9, scope: !602)
!602 = distinct !DILexicalBlock(scope: !603, file: !1, line: 211, column: 9)
!603 = distinct !DILexicalBlock(scope: !597, file: !1, line: 210, column: 25)
!604 = !DILocation(line: 211, column: 14, scope: !602)
!605 = !DILocation(line: 211, column: 24, scope: !602)
!606 = !DILocation(line: 211, column: 32, scope: !602)
!607 = !DILocation(line: 212, column: 9, scope: !602)
!608 = !DILocation(line: 212, column: 14, scope: !602)
!609 = !DILocation(line: 212, column: 24, scope: !602)
!610 = !DILocation(line: 212, column: 32, scope: !602)
!611 = !DILocation(line: 213, column: 9, scope: !602)
!612 = !DILocation(line: 213, column: 14, scope: !602)
!613 = !DILocation(line: 213, column: 24, scope: !602)
!614 = !DILocation(line: 213, column: 32, scope: !602)
!615 = !DILocation(line: 214, column: 9, scope: !602)
!616 = !DILocation(line: 214, column: 14, scope: !602)
!617 = !DILocation(line: 214, column: 24, scope: !602)
!618 = !DILocation(line: 211, column: 9, scope: !619)
!619 = !DILexicalBlockFile(scope: !603, file: !1, discriminator: 1)
!620 = !DILocation(line: 215, column: 10, scope: !621)
!621 = distinct !DILexicalBlock(scope: !622, file: !1, line: 215, column: 10)
!622 = distinct !DILexicalBlock(scope: !602, file: !1, line: 214, column: 33)
!623 = !DILocation(line: 215, column: 15, scope: !621)
!624 = !DILocation(line: 215, column: 10, scope: !622)
!625 = !DILocation(line: 217, column: 12, scope: !626)
!626 = distinct !DILexicalBlock(scope: !621, file: !1, line: 215, column: 29)
!627 = !DILocation(line: 217, column: 18, scope: !626)
!628 = !DILocation(line: 217, column: 27, scope: !626)
!629 = !DILocation(line: 216, column: 7, scope: !626)
!630 = !DILocation(line: 220, column: 7, scope: !626)
!631 = !DILocation(line: 222, column: 6, scope: !622)
!632 = !DILocation(line: 222, column: 11, scope: !622)
!633 = !DILocation(line: 222, column: 17, scope: !622)
!634 = !DILocation(line: 223, column: 14, scope: !622)
!635 = !DILocation(line: 223, column: 19, scope: !622)
!636 = !DILocation(line: 223, column: 7, scope: !622)
!637 = !DILocation(line: 223, column: 12, scope: !622)
!638 = !DILocation(line: 224, column: 14, scope: !622)
!639 = !DILocation(line: 224, column: 19, scope: !622)
!640 = !DILocation(line: 224, column: 12, scope: !622)
!641 = !DILocation(line: 225, column: 6, scope: !622)
!642 = !DILocation(line: 228, column: 31, scope: !603)
!643 = !DILocation(line: 228, column: 36, scope: !603)
!644 = !DILocation(line: 228, column: 42, scope: !603)
!645 = !DILocation(line: 228, column: 15, scope: !603)
!646 = !DILocation(line: 228, column: 13, scope: !603)
!647 = !DILocation(line: 229, column: 29, scope: !603)
!648 = !DILocation(line: 229, column: 34, scope: !603)
!649 = !DILocation(line: 229, column: 40, scope: !603)
!650 = !DILocation(line: 229, column: 13, scope: !603)
!651 = !DILocation(line: 229, column: 11, scope: !603)
!652 = !DILocation(line: 230, column: 22, scope: !603)
!653 = !DILocation(line: 230, column: 30, scope: !603)
!654 = !DILocation(line: 230, column: 20, scope: !603)
!655 = !DILocation(line: 230, column: 37, scope: !603)
!656 = !DILocation(line: 230, column: 35, scope: !603)
!657 = !DILocation(line: 230, column: 17, scope: !603)
!658 = !DILocation(line: 230, column: 5, scope: !603)
!659 = !DILocation(line: 230, column: 10, scope: !603)
!660 = !DILocation(line: 230, column: 15, scope: !603)
!661 = !DILocation(line: 231, column: 5, scope: !603)
!662 = !DILocation(line: 231, column: 10, scope: !603)
!663 = !DILocation(line: 231, column: 16, scope: !603)
!664 = !DILocation(line: 232, column: 5, scope: !603)
!665 = !DILocation(line: 232, column: 10, scope: !603)
!666 = !DILocation(line: 232, column: 23, scope: !603)
!667 = !DILocation(line: 233, column: 4, scope: !603)
!668 = !DILocation(line: 234, column: 4, scope: !533)
!669 = !DILocation(line: 236, column: 8, scope: !533)
!670 = !DILocation(line: 236, column: 13, scope: !533)
!671 = !DILocation(line: 236, column: 20, scope: !533)
!672 = !DILocation(line: 236, column: 25, scope: !533)
!673 = !DILocation(line: 236, column: 18, scope: !533)
!674 = !DILocation(line: 236, column: 6, scope: !533)
!675 = !DILocation(line: 237, column: 8, scope: !676)
!676 = distinct !DILexicalBlock(scope: !533, file: !1, line: 237, column: 8)
!677 = !DILocation(line: 237, column: 12, scope: !676)
!678 = !DILocation(line: 237, column: 23, scope: !676)
!679 = !DILocation(line: 237, column: 21, scope: !676)
!680 = !DILocation(line: 237, column: 10, scope: !676)
!681 = !DILocation(line: 237, column: 8, scope: !533)
!682 = !DILocation(line: 238, column: 9, scope: !676)
!683 = !DILocation(line: 238, column: 20, scope: !676)
!684 = !DILocation(line: 238, column: 18, scope: !676)
!685 = !DILocation(line: 238, column: 7, scope: !676)
!686 = !DILocation(line: 238, column: 5, scope: !676)
!687 = !DILocation(line: 239, column: 9, scope: !533)
!688 = !DILocation(line: 239, column: 6, scope: !533)
!689 = !DILocation(line: 240, column: 12, scope: !533)
!690 = !DILocation(line: 240, column: 9, scope: !533)
!691 = !DILocation(line: 241, column: 17, scope: !533)
!692 = !DILocation(line: 241, column: 4, scope: !533)
!693 = !DILocation(line: 241, column: 9, scope: !533)
!694 = !DILocation(line: 241, column: 14, scope: !533)
!695 = !DILocation(line: 242, column: 8, scope: !696)
!696 = distinct !DILexicalBlock(scope: !533, file: !1, line: 242, column: 8)
!697 = !DILocation(line: 242, column: 13, scope: !696)
!698 = !DILocation(line: 242, column: 21, scope: !696)
!699 = !DILocation(line: 242, column: 26, scope: !696)
!700 = !DILocation(line: 242, column: 18, scope: !696)
!701 = !DILocation(line: 242, column: 8, scope: !533)
!702 = !DILocation(line: 243, column: 5, scope: !696)
!703 = !DILocation(line: 243, column: 10, scope: !696)
!704 = !DILocation(line: 243, column: 16, scope: !696)
!705 = !DILocation(line: 244, column: 4, scope: !533)
!706 = !DILocation(line: 246, column: 4, scope: !533)
!707 = !DILocation(line: 246, column: 11, scope: !708)
!708 = !DILexicalBlockFile(scope: !533, file: !1, discriminator: 1)
!709 = !DILocation(line: 246, column: 26, scope: !708)
!710 = !DILocation(line: 246, column: 16, scope: !708)
!711 = !DILocation(line: 246, column: 4, scope: !708)
!712 = !DILocation(line: 247, column: 10, scope: !713)
!713 = distinct !DILexicalBlock(scope: !714, file: !1, line: 247, column: 9)
!714 = distinct !DILexicalBlock(scope: !533, file: !1, line: 246, column: 36)
!715 = !DILocation(line: 247, column: 9, scope: !713)
!716 = !DILocation(line: 247, column: 12, scope: !713)
!717 = !DILocation(line: 247, column: 9, scope: !714)
!718 = !DILocation(line: 249, column: 6, scope: !719)
!719 = distinct !DILexicalBlock(scope: !713, file: !1, line: 247, column: 18)
!720 = !DILocation(line: 249, column: 11, scope: !719)
!721 = !DILocation(line: 249, column: 17, scope: !719)
!722 = !DILocation(line: 250, column: 6, scope: !719)
!723 = !DILocation(line: 250, column: 11, scope: !719)
!724 = !DILocation(line: 250, column: 16, scope: !719)
!725 = !DILocation(line: 251, column: 6, scope: !719)
!726 = !DILocation(line: 251, column: 11, scope: !719)
!727 = !DILocation(line: 251, column: 16, scope: !719)
!728 = !DILocation(line: 252, column: 6, scope: !719)
!729 = !DILocation(line: 254, column: 6, scope: !714)
!730 = !DILocation(line: 255, column: 9, scope: !714)
!731 = !DILocation(line: 246, column: 4, scope: !732)
!732 = !DILexicalBlockFile(scope: !533, file: !1, discriminator: 2)
!733 = !DILocation(line: 257, column: 4, scope: !533)
!734 = !DILocation(line: 259, column: 12, scope: !533)
!735 = !DILocation(line: 259, column: 5, scope: !533)
!736 = !DILocation(line: 259, column: 10, scope: !533)
!737 = !DILocation(line: 260, column: 12, scope: !533)
!738 = !DILocation(line: 260, column: 10, scope: !533)
!739 = !DILocation(line: 261, column: 11, scope: !533)
!740 = !DILocation(line: 261, column: 9, scope: !533)
!741 = !DILocation(line: 262, column: 4, scope: !533)
!742 = !DILocation(line: 264, column: 7, scope: !743)
!743 = distinct !DILexicalBlock(scope: !508, file: !1, line: 264, column: 7)
!744 = !DILocation(line: 264, column: 23, scope: !743)
!745 = !DILocation(line: 264, column: 12, scope: !743)
!746 = !DILocation(line: 264, column: 7, scope: !508)
!747 = !DILocation(line: 265, column: 21, scope: !748)
!748 = distinct !DILexicalBlock(scope: !743, file: !1, line: 264, column: 33)
!749 = !DILocation(line: 265, column: 4, scope: !748)
!750 = !DILocation(line: 265, column: 9, scope: !748)
!751 = !DILocation(line: 265, column: 18, scope: !748)
!752 = !DILocation(line: 266, column: 34, scope: !748)
!753 = !DILocation(line: 266, column: 40, scope: !748)
!754 = !DILocation(line: 266, column: 50, scope: !748)
!755 = !DILocation(line: 266, column: 4, scope: !748)
!756 = !DILocation(line: 267, column: 6, scope: !748)
!757 = !DILocation(line: 268, column: 9, scope: !748)
!758 = !DILocation(line: 269, column: 3, scope: !748)
!759 = !DILocation(line: 270, column: 2, scope: !508)
!760 = !DILocation(line: 270, column: 11, scope: !761)
!761 = !DILexicalBlockFile(scope: !317, file: !1, discriminator: 1)
!762 = !DILocation(line: 270, column: 17, scope: !761)
!763 = !DILocation(line: 270, column: 22, scope: !761)
!764 = !DILocation(line: 270, column: 25, scope: !765)
!765 = !DILexicalBlockFile(scope: !317, file: !1, discriminator: 2)
!766 = !DILocation(line: 270, column: 34, scope: !765)
!767 = !DILocation(line: 270, column: 2, scope: !768)
!768 = !DILexicalBlockFile(scope: !508, file: !1, discriminator: 3)
!769 = !DILocation(line: 272, column: 6, scope: !770)
!770 = distinct !DILexicalBlock(scope: !317, file: !1, line: 272, column: 6)
!771 = !DILocation(line: 272, column: 11, scope: !770)
!772 = !DILocation(line: 272, column: 15, scope: !770)
!773 = !DILocation(line: 272, column: 18, scope: !774)
!774 = !DILexicalBlockFile(scope: !770, file: !1, discriminator: 1)
!775 = !DILocation(line: 272, column: 20, scope: !774)
!776 = !DILocation(line: 272, column: 6, scope: !774)
!777 = !DILocation(line: 273, column: 20, scope: !778)
!778 = distinct !DILexicalBlock(scope: !770, file: !1, line: 272, column: 29)
!779 = !DILocation(line: 273, column: 3, scope: !778)
!780 = !DILocation(line: 273, column: 8, scope: !778)
!781 = !DILocation(line: 273, column: 17, scope: !778)
!782 = !DILocation(line: 274, column: 33, scope: !778)
!783 = !DILocation(line: 274, column: 39, scope: !778)
!784 = !DILocation(line: 274, column: 49, scope: !778)
!785 = !DILocation(line: 274, column: 3, scope: !778)
!786 = !DILocation(line: 275, column: 2, scope: !778)
!787 = !DILocation(line: 276, column: 10, scope: !317)
!788 = !DILocation(line: 276, column: 2, scope: !317)
!789 = !DILocation(line: 277, column: 1, scope: !317)
!790 = !DILocalVariable(name: "self", arg: 1, scope: !323, file: !1, line: 280, type: !188)
!791 = !DILocation(line: 280, column: 46, scope: !323)
!792 = !DILocalVariable(name: "rpm", scope: !323, file: !1, line: 282, type: !308)
!793 = !DILocation(line: 282, column: 14, scope: !323)
!794 = !DILocation(line: 284, column: 22, scope: !323)
!795 = !DILocation(line: 284, column: 28, scope: !323)
!796 = !DILocation(line: 284, column: 8, scope: !323)
!797 = !DILocation(line: 284, column: 6, scope: !323)
!798 = !DILocation(line: 285, column: 7, scope: !323)
!799 = !DILocation(line: 285, column: 2, scope: !323)
!800 = !DILocation(line: 287, column: 2, scope: !323)
!801 = !DILocalVariable(name: "pp", arg: 1, scope: !318, file: !319, line: 77, type: !67)
!802 = !DILocation(line: 77, column: 29, scope: !318)
!803 = !DILocalVariable(name: "p", scope: !318, file: !319, line: 79, type: !309)
!804 = !DILocation(line: 79, column: 23, scope: !318)
!805 = !DILocation(line: 79, column: 50, scope: !318)
!806 = !DILocalVariable(name: "p3", scope: !318, file: !319, line: 84, type: !39)
!807 = !DILocation(line: 84, column: 15, scope: !318)
!808 = !DILocation(line: 84, column: 20, scope: !318)
!809 = !DILocalVariable(name: "p2", scope: !318, file: !319, line: 85, type: !39)
!810 = !DILocation(line: 85, column: 15, scope: !318)
!811 = !DILocation(line: 85, column: 20, scope: !318)
!812 = !DILocalVariable(name: "p1", scope: !318, file: !319, line: 86, type: !39)
!813 = !DILocation(line: 86, column: 15, scope: !318)
!814 = !DILocation(line: 86, column: 20, scope: !318)
!815 = !DILocalVariable(name: "p0", scope: !318, file: !319, line: 87, type: !39)
!816 = !DILocation(line: 87, column: 15, scope: !318)
!817 = !DILocation(line: 87, column: 20, scope: !318)
!818 = !DILocation(line: 89, column: 11, scope: !318)
!819 = !DILocation(line: 89, column: 14, scope: !318)
!820 = !DILocation(line: 89, column: 24, scope: !318)
!821 = !DILocation(line: 89, column: 27, scope: !318)
!822 = !DILocation(line: 89, column: 21, scope: !318)
!823 = !DILocation(line: 89, column: 37, scope: !318)
!824 = !DILocation(line: 89, column: 40, scope: !318)
!825 = !DILocation(line: 89, column: 34, scope: !318)
!826 = !DILocation(line: 89, column: 48, scope: !318)
!827 = !DILocation(line: 89, column: 46, scope: !318)
!828 = !DILocation(line: 89, column: 2, scope: !318)
