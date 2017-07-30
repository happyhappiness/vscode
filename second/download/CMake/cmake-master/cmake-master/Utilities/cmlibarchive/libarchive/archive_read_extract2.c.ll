; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_extract2.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive_read_extract = type { %struct.archive*, void (i8*)*, i8* }
%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { i32 (%struct.archive*)*, i32 (%struct.archive*)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)*, i8* (%struct.archive*, i32)* }
%struct.archive_entry = type opaque
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque
%struct.archive_read = type { %struct.archive, %struct.archive_entry*, i32, i64, i64, %struct.archive_read_client, [16 x %struct.archive_read_filter_bidder], %struct.archive_read_filter*, i32, i64, i32, i32, [16 x %struct.archive_format_descriptor], %struct.archive_format_descriptor*, %struct.archive_read_extract*, i32 (%struct.archive_read*)*, %struct.anon }
%struct.archive_read_client = type { i32 (%struct.archive*, i8*)*, i64 (%struct.archive*, i8*, i8**)*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i32)*, i32 (%struct.archive*, i8*)*, i32 (%struct.archive*, i8*, i8*)*, i32, i32, i64, %struct.archive_read_data_node* }
%struct.archive_read_data_node = type { i64, i64, i8* }
%struct.archive_read_filter_bidder = type { i8*, i8*, i32 (%struct.archive_read_filter_bidder*, %struct.archive_read_filter*)*, i32 (%struct.archive_read_filter*)*, i32 (%struct.archive_read_filter_bidder*, i8*, i8*)*, i32 (%struct.archive_read_filter_bidder*)* }
%struct.archive_read_filter = type { i64, %struct.archive_read_filter_bidder*, %struct.archive_read_filter*, %struct.archive_read*, i32 (%struct.archive_read_filter*)*, i64 (%struct.archive_read_filter*, i8**)*, i64 (%struct.archive_read_filter*, i64)*, i64 (%struct.archive_read_filter*, i64, i32)*, i32 (%struct.archive_read_filter*)*, i32 (%struct.archive_read_filter*, i32)*, i8*, i8*, i32, i8*, i64, i8*, i64, i8*, i64, i8*, i64, i8, i8, i8 }
%struct.archive_format_descriptor = type { i8*, i8*, i32 (%struct.archive_read*, i32)*, i32 (%struct.archive_read*, i8*, i8*)*, i32 (%struct.archive_read*, %struct.archive_entry*)*, i32 (%struct.archive_read*, i8**, i64*, i64*)*, i32 (%struct.archive_read*)*, i64 (%struct.archive_read*, i64, i32)*, i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)* }
%struct.anon = type { %struct.archive_read_passphrase*, %struct.archive_read_passphrase**, i32, i8* (%struct.archive*, i8*)*, i8* }
%struct.archive_read_passphrase = type { i8*, %struct.archive_read_passphrase* }

@.str = private unnamed_addr constant [14 x i8] c"Can't extract\00", align 1
@.str.1 = private unnamed_addr constant [3 x i8] c"%s\00", align 1

; Function Attrs: nounwind uwtable
define %struct.archive_read_extract* @__archive_read_get_extract(%struct.archive_read* %a) #0 !dbg !292 {
entry:
  %retval = alloca %struct.archive_read_extract*, align 8
  %a.addr = alloca %struct.archive_read*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !308, metadata !309), !dbg !310
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !311
  %extract = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 14, !dbg !313
  %1 = load %struct.archive_read_extract*, %struct.archive_read_extract** %extract, align 8, !dbg !313
  %cmp = icmp eq %struct.archive_read_extract* %1, null, !dbg !314
  br i1 %cmp, label %if.then, label %if.end5, !dbg !315

if.then:                                          ; preds = %entry
  %call = call noalias i8* @calloc(i64 1, i64 24) #4, !dbg !316
  %2 = bitcast i8* %call to %struct.archive_read_extract*, !dbg !318
  %3 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !319
  %extract1 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %3, i32 0, i32 14, !dbg !320
  store %struct.archive_read_extract* %2, %struct.archive_read_extract** %extract1, align 8, !dbg !321
  %4 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !322
  %extract2 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %4, i32 0, i32 14, !dbg !324
  %5 = load %struct.archive_read_extract*, %struct.archive_read_extract** %extract2, align 8, !dbg !324
  %cmp3 = icmp eq %struct.archive_read_extract* %5, null, !dbg !325
  br i1 %cmp3, label %if.then4, label %if.end, !dbg !326

if.then4:                                         ; preds = %if.then
  %6 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !327
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %6, i32 0, i32 0, !dbg !329
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str, i32 0, i32 0)), !dbg !330
  store %struct.archive_read_extract* null, %struct.archive_read_extract** %retval, align 8, !dbg !331
  br label %return, !dbg !331

if.end:                                           ; preds = %if.then
  %7 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !332
  %cleanup_archive_extract = getelementptr inbounds %struct.archive_read, %struct.archive_read* %7, i32 0, i32 15, !dbg !333
  store i32 (%struct.archive_read*)* @archive_read_extract_cleanup, i32 (%struct.archive_read*)** %cleanup_archive_extract, align 8, !dbg !334
  br label %if.end5, !dbg !335

if.end5:                                          ; preds = %if.end, %entry
  %8 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !336
  %extract6 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %8, i32 0, i32 14, !dbg !337
  %9 = load %struct.archive_read_extract*, %struct.archive_read_extract** %extract6, align 8, !dbg !337
  store %struct.archive_read_extract* %9, %struct.archive_read_extract** %retval, align 8, !dbg !338
  br label %return, !dbg !338

return:                                           ; preds = %if.end5, %if.then4
  %10 = load %struct.archive_read_extract*, %struct.archive_read_extract** %retval, align 8, !dbg !339
  ret %struct.archive_read_extract* %10, !dbg !339
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #2

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #3

; Function Attrs: nounwind uwtable
define internal i32 @archive_read_extract_cleanup(%struct.archive_read* %a) #0 !dbg !301 {
entry:
  %a.addr = alloca %struct.archive_read*, align 8
  %ret = alloca i32, align 4
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !340, metadata !309), !dbg !341
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !342, metadata !309), !dbg !343
  store i32 0, i32* %ret, align 4, !dbg !343
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !344
  %extract = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 14, !dbg !346
  %1 = load %struct.archive_read_extract*, %struct.archive_read_extract** %extract, align 8, !dbg !346
  %ad = getelementptr inbounds %struct.archive_read_extract, %struct.archive_read_extract* %1, i32 0, i32 0, !dbg !347
  %2 = load %struct.archive*, %struct.archive** %ad, align 8, !dbg !347
  %cmp = icmp ne %struct.archive* %2, null, !dbg !348
  br i1 %cmp, label %if.then, label %if.end, !dbg !349

if.then:                                          ; preds = %entry
  %3 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !350
  %extract1 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %3, i32 0, i32 14, !dbg !352
  %4 = load %struct.archive_read_extract*, %struct.archive_read_extract** %extract1, align 8, !dbg !352
  %ad2 = getelementptr inbounds %struct.archive_read_extract, %struct.archive_read_extract* %4, i32 0, i32 0, !dbg !353
  %5 = load %struct.archive*, %struct.archive** %ad2, align 8, !dbg !353
  %call = call i32 @archive_write_free(%struct.archive* %5), !dbg !354
  store i32 %call, i32* %ret, align 4, !dbg !355
  br label %if.end, !dbg !356

if.end:                                           ; preds = %if.then, %entry
  %6 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !357
  %extract3 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %6, i32 0, i32 14, !dbg !358
  %7 = load %struct.archive_read_extract*, %struct.archive_read_extract** %extract3, align 8, !dbg !358
  %8 = bitcast %struct.archive_read_extract* %7 to i8*, !dbg !357
  call void @free(i8* %8) #4, !dbg !359
  %9 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !360
  %extract4 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %9, i32 0, i32 14, !dbg !361
  store %struct.archive_read_extract* null, %struct.archive_read_extract** %extract4, align 8, !dbg !362
  %10 = load i32, i32* %ret, align 4, !dbg !363
  ret i32 %10, !dbg !364
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_extract2(%struct.archive* %_a, %struct.archive_entry* %entry1, %struct.archive* %ad) #0 !dbg !295 {
entry:
  %_a.addr = alloca %struct.archive*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %ad.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_read*, align 8
  %r = alloca i32, align 4
  %r2 = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !365, metadata !309), !dbg !366
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !367, metadata !309), !dbg !368
  store %struct.archive* %ad, %struct.archive** %ad.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %ad.addr, metadata !369, metadata !309), !dbg !370
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !371, metadata !309), !dbg !372
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !373
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !374
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !372
  call void @llvm.dbg.declare(metadata i32* %r, metadata !375, metadata !309), !dbg !376
  call void @llvm.dbg.declare(metadata i32* %r2, metadata !377, metadata !309), !dbg !378
  %2 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !379
  %skip_file_set = getelementptr inbounds %struct.archive_read, %struct.archive_read* %2, i32 0, i32 2, !dbg !381
  %3 = load i32, i32* %skip_file_set, align 8, !dbg !381
  %tobool = icmp ne i32 %3, 0, !dbg !379
  br i1 %tobool, label %if.then, label %if.end, !dbg !382

if.then:                                          ; preds = %entry
  %4 = load %struct.archive*, %struct.archive** %ad.addr, align 8, !dbg !383
  %5 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !384
  %skip_file_dev = getelementptr inbounds %struct.archive_read, %struct.archive_read* %5, i32 0, i32 3, !dbg !385
  %6 = load i64, i64* %skip_file_dev, align 8, !dbg !385
  %7 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !386
  %skip_file_ino = getelementptr inbounds %struct.archive_read, %struct.archive_read* %7, i32 0, i32 4, !dbg !387
  %8 = load i64, i64* %skip_file_ino, align 8, !dbg !387
  %call = call i32 @archive_write_disk_set_skip_file(%struct.archive* %4, i64 %6, i64 %8), !dbg !388
  br label %if.end, !dbg !388

if.end:                                           ; preds = %if.then, %entry
  %9 = load %struct.archive*, %struct.archive** %ad.addr, align 8, !dbg !389
  %10 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !390
  %call2 = call i32 @archive_write_header(%struct.archive* %9, %struct.archive_entry* %10), !dbg !391
  store i32 %call2, i32* %r, align 4, !dbg !392
  %11 = load i32, i32* %r, align 4, !dbg !393
  %cmp = icmp slt i32 %11, -20, !dbg !395
  br i1 %cmp, label %if.then3, label %if.end4, !dbg !396

if.then3:                                         ; preds = %if.end
  store i32 -20, i32* %r, align 4, !dbg !397
  br label %if.end4, !dbg !398

if.end4:                                          ; preds = %if.then3, %if.end
  %12 = load i32, i32* %r, align 4, !dbg !399
  %cmp5 = icmp ne i32 %12, 0, !dbg !401
  br i1 %cmp5, label %if.then6, label %if.else, !dbg !402

if.then6:                                         ; preds = %if.end4
  %13 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !403
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %13, i32 0, i32 0, !dbg !404
  %14 = load %struct.archive*, %struct.archive** %ad.addr, align 8, !dbg !405
  call void @archive_copy_error(%struct.archive* %archive, %struct.archive* %14), !dbg !406
  br label %if.end14, !dbg !406

if.else:                                          ; preds = %if.end4
  %15 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !407
  %call7 = call i32 @archive_entry_size_is_set(%struct.archive_entry* %15), !dbg !409
  %tobool8 = icmp ne i32 %call7, 0, !dbg !409
  br i1 %tobool8, label %lor.lhs.false, label %if.then11, !dbg !410

lor.lhs.false:                                    ; preds = %if.else
  %16 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !411
  %call9 = call i64 @archive_entry_size(%struct.archive_entry* %16), !dbg !413
  %cmp10 = icmp sgt i64 %call9, 0, !dbg !414
  br i1 %cmp10, label %if.then11, label %if.end13, !dbg !415

if.then11:                                        ; preds = %lor.lhs.false, %if.else
  %17 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !416
  %18 = load %struct.archive*, %struct.archive** %ad.addr, align 8, !dbg !417
  %call12 = call i32 @copy_data(%struct.archive* %17, %struct.archive* %18), !dbg !418
  store i32 %call12, i32* %r, align 4, !dbg !419
  br label %if.end13, !dbg !420

if.end13:                                         ; preds = %if.then11, %lor.lhs.false
  br label %if.end14

if.end14:                                         ; preds = %if.end13, %if.then6
  %19 = load %struct.archive*, %struct.archive** %ad.addr, align 8, !dbg !421
  %call15 = call i32 @archive_write_finish_entry(%struct.archive* %19), !dbg !422
  store i32 %call15, i32* %r2, align 4, !dbg !423
  %20 = load i32, i32* %r2, align 4, !dbg !424
  %cmp16 = icmp slt i32 %20, -20, !dbg !426
  br i1 %cmp16, label %if.then17, label %if.end18, !dbg !427

if.then17:                                        ; preds = %if.end14
  store i32 -20, i32* %r2, align 4, !dbg !428
  br label %if.end18, !dbg !429

if.end18:                                         ; preds = %if.then17, %if.end14
  %21 = load i32, i32* %r2, align 4, !dbg !430
  %cmp19 = icmp ne i32 %21, 0, !dbg !432
  br i1 %cmp19, label %land.lhs.true, label %if.end23, !dbg !433

land.lhs.true:                                    ; preds = %if.end18
  %22 = load i32, i32* %r, align 4, !dbg !434
  %cmp20 = icmp eq i32 %22, 0, !dbg !436
  br i1 %cmp20, label %if.then21, label %if.end23, !dbg !437

if.then21:                                        ; preds = %land.lhs.true
  %23 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !438
  %archive22 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %23, i32 0, i32 0, !dbg !439
  %24 = load %struct.archive*, %struct.archive** %ad.addr, align 8, !dbg !440
  call void @archive_copy_error(%struct.archive* %archive22, %struct.archive* %24), !dbg !441
  br label %if.end23, !dbg !441

if.end23:                                         ; preds = %if.then21, %land.lhs.true, %if.end18
  %25 = load i32, i32* %r2, align 4, !dbg !442
  %26 = load i32, i32* %r, align 4, !dbg !444
  %cmp24 = icmp slt i32 %25, %26, !dbg !445
  br i1 %cmp24, label %if.then25, label %if.end26, !dbg !446

if.then25:                                        ; preds = %if.end23
  %27 = load i32, i32* %r2, align 4, !dbg !447
  store i32 %27, i32* %r, align 4, !dbg !448
  br label %if.end26, !dbg !449

if.end26:                                         ; preds = %if.then25, %if.end23
  %28 = load i32, i32* %r, align 4, !dbg !450
  ret i32 %28, !dbg !451
}

declare i32 @archive_write_disk_set_skip_file(%struct.archive*, i64, i64) #3

declare i32 @archive_write_header(%struct.archive*, %struct.archive_entry*) #3

declare void @archive_copy_error(%struct.archive*, %struct.archive*) #3

declare i32 @archive_entry_size_is_set(%struct.archive_entry*) #3

declare i64 @archive_entry_size(%struct.archive_entry*) #3

; Function Attrs: nounwind uwtable
define internal i32 @copy_data(%struct.archive* %ar, %struct.archive* %aw) #0 !dbg !302 {
entry:
  %retval = alloca i32, align 4
  %ar.addr = alloca %struct.archive*, align 8
  %aw.addr = alloca %struct.archive*, align 8
  %offset = alloca i64, align 8
  %buff = alloca i8*, align 8
  %extract = alloca %struct.archive_read_extract*, align 8
  %size = alloca i64, align 8
  %r = alloca i32, align 4
  store %struct.archive* %ar, %struct.archive** %ar.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %ar.addr, metadata !452, metadata !309), !dbg !453
  store %struct.archive* %aw, %struct.archive** %aw.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %aw.addr, metadata !454, metadata !309), !dbg !455
  call void @llvm.dbg.declare(metadata i64* %offset, metadata !456, metadata !309), !dbg !457
  call void @llvm.dbg.declare(metadata i8** %buff, metadata !458, metadata !309), !dbg !459
  call void @llvm.dbg.declare(metadata %struct.archive_read_extract** %extract, metadata !460, metadata !309), !dbg !461
  call void @llvm.dbg.declare(metadata i64* %size, metadata !462, metadata !309), !dbg !463
  call void @llvm.dbg.declare(metadata i32* %r, metadata !464, metadata !309), !dbg !465
  %0 = load %struct.archive*, %struct.archive** %ar.addr, align 8, !dbg !466
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !467
  %call = call %struct.archive_read_extract* @__archive_read_get_extract(%struct.archive_read* %1), !dbg !468
  store %struct.archive_read_extract* %call, %struct.archive_read_extract** %extract, align 8, !dbg !469
  %2 = load %struct.archive_read_extract*, %struct.archive_read_extract** %extract, align 8, !dbg !470
  %cmp = icmp eq %struct.archive_read_extract* %2, null, !dbg !472
  br i1 %cmp, label %if.then, label %if.end, !dbg !473

if.then:                                          ; preds = %entry
  store i32 -30, i32* %retval, align 4, !dbg !474
  br label %return, !dbg !474

if.end:                                           ; preds = %entry
  br label %for.cond, !dbg !475

for.cond:                                         ; preds = %if.end21, %if.end
  %3 = load %struct.archive*, %struct.archive** %ar.addr, align 8, !dbg !476
  %call1 = call i32 @archive_read_data_block(%struct.archive* %3, i8** %buff, i64* %size, i64* %offset), !dbg !480
  store i32 %call1, i32* %r, align 4, !dbg !481
  %4 = load i32, i32* %r, align 4, !dbg !482
  %cmp2 = icmp eq i32 %4, 1, !dbg !484
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !485

if.then3:                                         ; preds = %for.cond
  store i32 0, i32* %retval, align 4, !dbg !486
  br label %return, !dbg !486

if.end4:                                          ; preds = %for.cond
  %5 = load i32, i32* %r, align 4, !dbg !487
  %cmp5 = icmp ne i32 %5, 0, !dbg !489
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !490

if.then6:                                         ; preds = %if.end4
  %6 = load i32, i32* %r, align 4, !dbg !491
  store i32 %6, i32* %retval, align 4, !dbg !492
  br label %return, !dbg !492

if.end7:                                          ; preds = %if.end4
  %7 = load %struct.archive*, %struct.archive** %aw.addr, align 8, !dbg !493
  %8 = load i8*, i8** %buff, align 8, !dbg !494
  %9 = load i64, i64* %size, align 8, !dbg !495
  %10 = load i64, i64* %offset, align 8, !dbg !496
  %call8 = call i64 @archive_write_data_block(%struct.archive* %7, i8* %8, i64 %9, i64 %10), !dbg !497
  %conv = trunc i64 %call8 to i32, !dbg !498
  store i32 %conv, i32* %r, align 4, !dbg !499
  %11 = load i32, i32* %r, align 4, !dbg !500
  %cmp9 = icmp slt i32 %11, -20, !dbg !502
  br i1 %cmp9, label %if.then11, label %if.end12, !dbg !503

if.then11:                                        ; preds = %if.end7
  store i32 -20, i32* %r, align 4, !dbg !504
  br label %if.end12, !dbg !505

if.end12:                                         ; preds = %if.then11, %if.end7
  %12 = load i32, i32* %r, align 4, !dbg !506
  %cmp13 = icmp slt i32 %12, 0, !dbg !508
  br i1 %cmp13, label %if.then15, label %if.end18, !dbg !509

if.then15:                                        ; preds = %if.end12
  %13 = load %struct.archive*, %struct.archive** %ar.addr, align 8, !dbg !510
  %14 = load %struct.archive*, %struct.archive** %aw.addr, align 8, !dbg !512
  %call16 = call i32 @archive_errno(%struct.archive* %14), !dbg !513
  %15 = load %struct.archive*, %struct.archive** %aw.addr, align 8, !dbg !514
  %call17 = call i8* @archive_error_string(%struct.archive* %15), !dbg !515
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %13, i32 %call16, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.1, i32 0, i32 0), i8* %call17), !dbg !516
  %16 = load i32, i32* %r, align 4, !dbg !517
  store i32 %16, i32* %retval, align 4, !dbg !518
  br label %return, !dbg !518

if.end18:                                         ; preds = %if.end12
  %17 = load %struct.archive_read_extract*, %struct.archive_read_extract** %extract, align 8, !dbg !519
  %extract_progress = getelementptr inbounds %struct.archive_read_extract, %struct.archive_read_extract* %17, i32 0, i32 1, !dbg !521
  %18 = load void (i8*)*, void (i8*)** %extract_progress, align 8, !dbg !521
  %tobool = icmp ne void (i8*)* %18, null, !dbg !519
  br i1 %tobool, label %if.then19, label %if.end21, !dbg !522

if.then19:                                        ; preds = %if.end18
  %19 = load %struct.archive_read_extract*, %struct.archive_read_extract** %extract, align 8, !dbg !523
  %extract_progress20 = getelementptr inbounds %struct.archive_read_extract, %struct.archive_read_extract* %19, i32 0, i32 1, !dbg !524
  %20 = load void (i8*)*, void (i8*)** %extract_progress20, align 8, !dbg !524
  %21 = load %struct.archive_read_extract*, %struct.archive_read_extract** %extract, align 8, !dbg !525
  %extract_progress_user_data = getelementptr inbounds %struct.archive_read_extract, %struct.archive_read_extract* %21, i32 0, i32 2, !dbg !526
  %22 = load i8*, i8** %extract_progress_user_data, align 8, !dbg !526
  call void %20(i8* %22), !dbg !527
  br label %if.end21, !dbg !527

if.end21:                                         ; preds = %if.then19, %if.end18
  br label %for.cond, !dbg !528

return:                                           ; preds = %if.then15, %if.then6, %if.then3, %if.then
  %23 = load i32, i32* %retval, align 4, !dbg !530
  ret i32 %23, !dbg !530
}

declare i32 @archive_write_finish_entry(%struct.archive*) #3

; Function Attrs: nounwind uwtable
define void @archive_read_extract_set_progress_callback(%struct.archive* %_a, void (i8*)* %progress_func, i8* %user_data) #0 !dbg !298 {
entry:
  %_a.addr = alloca %struct.archive*, align 8
  %progress_func.addr = alloca void (i8*)*, align 8
  %user_data.addr = alloca i8*, align 8
  %a = alloca %struct.archive_read*, align 8
  %extract = alloca %struct.archive_read_extract*, align 8
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !531, metadata !309), !dbg !532
  store void (i8*)* %progress_func, void (i8*)** %progress_func.addr, align 8
  call void @llvm.dbg.declare(metadata void (i8*)** %progress_func.addr, metadata !533, metadata !309), !dbg !534
  store i8* %user_data, i8** %user_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %user_data.addr, metadata !535, metadata !309), !dbg !536
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !537, metadata !309), !dbg !538
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !539
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !540
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !538
  call void @llvm.dbg.declare(metadata %struct.archive_read_extract** %extract, metadata !541, metadata !309), !dbg !542
  %2 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !543
  %call = call %struct.archive_read_extract* @__archive_read_get_extract(%struct.archive_read* %2), !dbg !544
  store %struct.archive_read_extract* %call, %struct.archive_read_extract** %extract, align 8, !dbg !542
  %3 = load %struct.archive_read_extract*, %struct.archive_read_extract** %extract, align 8, !dbg !545
  %cmp = icmp ne %struct.archive_read_extract* %3, null, !dbg !547
  br i1 %cmp, label %if.then, label %if.end, !dbg !548

if.then:                                          ; preds = %entry
  %4 = load void (i8*)*, void (i8*)** %progress_func.addr, align 8, !dbg !549
  %5 = load %struct.archive_read_extract*, %struct.archive_read_extract** %extract, align 8, !dbg !551
  %extract_progress = getelementptr inbounds %struct.archive_read_extract, %struct.archive_read_extract* %5, i32 0, i32 1, !dbg !552
  store void (i8*)* %4, void (i8*)** %extract_progress, align 8, !dbg !553
  %6 = load i8*, i8** %user_data.addr, align 8, !dbg !554
  %7 = load %struct.archive_read_extract*, %struct.archive_read_extract** %extract, align 8, !dbg !555
  %extract_progress_user_data = getelementptr inbounds %struct.archive_read_extract, %struct.archive_read_extract* %7, i32 0, i32 2, !dbg !556
  store i8* %6, i8** %extract_progress_user_data, align 8, !dbg !557
  br label %if.end, !dbg !558

if.end:                                           ; preds = %if.then, %entry
  ret void, !dbg !559
}

declare i32 @archive_write_free(%struct.archive*) #3

; Function Attrs: nounwind
declare void @free(i8*) #2

declare i32 @archive_read_data_block(%struct.archive*, i8**, i64*, i64*) #3

declare i64 @archive_write_data_block(%struct.archive*, i8*, i64, i64) #3

declare i32 @archive_errno(%struct.archive*) #3

declare i8* @archive_error_string(%struct.archive*) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!305, !306}
!llvm.ident = !{!307}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !291)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_extract2.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !5, !116, !25}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!5 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !6, size: 64, align: 64)
!6 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_extract", file: !7, line: 151, size: 192, align: 64, elements: !8)
!7 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!8 = !{!9, !111, !115}
!9 = !DIDerivedType(tag: DW_TAG_member, name: "ad", scope: !6, file: !7, line: 152, baseType: !10, size: 64, align: 64)
!10 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !11, size: 64, align: 64)
!11 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !12, line: 89, size: 1280, align: 64, elements: !13)
!12 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!13 = !{!14, !16, !17, !84, !85, !86, !87, !88, !89, !90, !91, !99, !100, !101, !102, !105, !106, !107, !108, !109, !110}
!14 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !11, file: !12, line: 96, baseType: !15, size: 32, align: 32)
!15 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!16 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !11, file: !12, line: 97, baseType: !15, size: 32, align: 32, offset: 32)
!17 = !DIDerivedType(tag: DW_TAG_member, name: "vtable", scope: !11, file: !12, line: 103, baseType: !18, size: 64, align: 64, offset: 64)
!18 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !19, size: 64, align: 64)
!19 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_vtable", file: !12, line: 63, size: 832, align: 64, elements: !20)
!20 = !{!21, !26, !27, !34, !35, !49, !55, !60, !61, !68, !69, !73, !77}
!21 = !DIDerivedType(tag: DW_TAG_member, name: "archive_close", scope: !19, file: !12, line: 64, baseType: !22, size: 64, align: 64)
!22 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !23, size: 64, align: 64)
!23 = !DISubroutineType(types: !24)
!24 = !{!25, !10}
!25 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!26 = !DIDerivedType(tag: DW_TAG_member, name: "archive_free", scope: !19, file: !12, line: 65, baseType: !22, size: 64, align: 64, offset: 64)
!27 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_header", scope: !19, file: !12, line: 66, baseType: !28, size: 64, align: 64, offset: 128)
!28 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !29, size: 64, align: 64)
!29 = !DISubroutineType(types: !30)
!30 = !{!25, !10, !31}
!31 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !32, size: 64, align: 64)
!32 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_entry", file: !33, line: 180, flags: DIFlagFwdDecl)
!33 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!34 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_finish_entry", scope: !19, file: !12, line: 68, baseType: !22, size: 64, align: 64, offset: 192)
!35 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data", scope: !19, file: !12, line: 69, baseType: !36, size: 64, align: 64, offset: 256)
!36 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !37, size: 64, align: 64)
!37 = !DISubroutineType(types: !38)
!38 = !{!39, !10, !44, !46}
!39 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !40, line: 109, baseType: !41)
!40 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!41 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !42, line: 172, baseType: !43)
!42 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!43 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!44 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !45, size: 64, align: 64)
!45 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!46 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !47, line: 62, baseType: !48)
!47 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!48 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!49 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data_block", scope: !19, file: !12, line: 71, baseType: !50, size: 64, align: 64, offset: 320)
!50 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !51, size: 64, align: 64)
!51 = !DISubroutineType(types: !52)
!52 = !{!39, !10, !44, !46, !53}
!53 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !54, line: 40, baseType: !43)
!54 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!55 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header", scope: !19, file: !12, line: 74, baseType: !56, size: 64, align: 64, offset: 384)
!56 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !57, size: 64, align: 64)
!57 = !DISubroutineType(types: !58)
!58 = !{!25, !10, !59}
!59 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !31, size: 64, align: 64)
!60 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header2", scope: !19, file: !12, line: 76, baseType: !28, size: 64, align: 64, offset: 448)
!61 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_data_block", scope: !19, file: !12, line: 78, baseType: !62, size: 64, align: 64, offset: 512)
!62 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !63, size: 64, align: 64)
!63 = !DISubroutineType(types: !64)
!64 = !{!25, !10, !65, !66, !67}
!65 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !44, size: 64, align: 64)
!66 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !46, size: 64, align: 64)
!67 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !53, size: 64, align: 64)
!68 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_count", scope: !19, file: !12, line: 81, baseType: !22, size: 64, align: 64, offset: 576)
!69 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_bytes", scope: !19, file: !12, line: 82, baseType: !70, size: 64, align: 64, offset: 640)
!70 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !71, size: 64, align: 64)
!71 = !DISubroutineType(types: !72)
!72 = !{!53, !10, !25}
!73 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_code", scope: !19, file: !12, line: 83, baseType: !74, size: 64, align: 64, offset: 704)
!74 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !75, size: 64, align: 64)
!75 = !DISubroutineType(types: !76)
!76 = !{!25, !10, !25}
!77 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_name", scope: !19, file: !12, line: 84, baseType: !78, size: 64, align: 64, offset: 768)
!78 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !79, size: 64, align: 64)
!79 = !DISubroutineType(types: !80)
!80 = !{!81, !10, !25}
!81 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !82, size: 64, align: 64)
!82 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !83)
!83 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format", scope: !11, file: !12, line: 105, baseType: !25, size: 32, align: 32, offset: 128)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format_name", scope: !11, file: !12, line: 106, baseType: !81, size: 64, align: 64, offset: 192)
!86 = !DIDerivedType(tag: DW_TAG_member, name: "compression_code", scope: !11, file: !12, line: 108, baseType: !25, size: 32, align: 32, offset: 256)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "compression_name", scope: !11, file: !12, line: 109, baseType: !81, size: 64, align: 64, offset: 320)
!88 = !DIDerivedType(tag: DW_TAG_member, name: "file_count", scope: !11, file: !12, line: 112, baseType: !25, size: 32, align: 32, offset: 384)
!89 = !DIDerivedType(tag: DW_TAG_member, name: "archive_error_number", scope: !11, file: !12, line: 114, baseType: !25, size: 32, align: 32, offset: 416)
!90 = !DIDerivedType(tag: DW_TAG_member, name: "error", scope: !11, file: !12, line: 115, baseType: !81, size: 64, align: 64, offset: 448)
!91 = !DIDerivedType(tag: DW_TAG_member, name: "error_string", scope: !11, file: !12, line: 116, baseType: !92, size: 192, align: 64, offset: 512)
!92 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string", file: !93, line: 58, size: 192, align: 64, elements: !94)
!93 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_string.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!94 = !{!95, !97, !98}
!95 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !92, file: !93, line: 59, baseType: !96, size: 64, align: 64)
!96 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !83, size: 64, align: 64)
!97 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !92, file: !93, line: 60, baseType: !46, size: 64, align: 64, offset: 64)
!98 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !92, file: !93, line: 61, baseType: !46, size: 64, align: 64, offset: 128)
!99 = !DIDerivedType(tag: DW_TAG_member, name: "current_code", scope: !11, file: !12, line: 118, baseType: !96, size: 64, align: 64, offset: 704)
!100 = !DIDerivedType(tag: DW_TAG_member, name: "current_codepage", scope: !11, file: !12, line: 119, baseType: !15, size: 32, align: 32, offset: 768)
!101 = !DIDerivedType(tag: DW_TAG_member, name: "current_oemcp", scope: !11, file: !12, line: 120, baseType: !15, size: 32, align: 32, offset: 800)
!102 = !DIDerivedType(tag: DW_TAG_member, name: "sconv", scope: !11, file: !12, line: 121, baseType: !103, size: 64, align: 64, offset: 832)
!103 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !104, size: 64, align: 64)
!104 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string_conv", file: !93, line: 70, flags: DIFlagFwdDecl)
!105 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_block", scope: !11, file: !12, line: 127, baseType: !81, size: 64, align: 64, offset: 896)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_offset", scope: !11, file: !12, line: 128, baseType: !53, size: 64, align: 64, offset: 960)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_output_offset", scope: !11, file: !12, line: 129, baseType: !53, size: 64, align: 64, offset: 1024)
!108 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_remaining", scope: !11, file: !12, line: 130, baseType: !46, size: 64, align: 64, offset: 1088)
!109 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_is_posix_read", scope: !11, file: !12, line: 137, baseType: !83, size: 8, align: 8, offset: 1152)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_requested", scope: !11, file: !12, line: 138, baseType: !46, size: 64, align: 64, offset: 1216)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "extract_progress", scope: !6, file: !7, line: 155, baseType: !112, size: 64, align: 64, offset: 64)
!112 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !113, size: 64, align: 64)
!113 = !DISubroutineType(types: !114)
!114 = !{null, !4}
!115 = !DIDerivedType(tag: DW_TAG_member, name: "extract_progress_user_data", scope: !6, file: !7, line: 156, baseType: !4, size: 64, align: 64, offset: 128)
!116 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !117, size: 64, align: 64)
!117 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read", file: !7, line: 159, size: 20288, align: 64, elements: !118)
!118 = !{!119, !120, !121, !122, !123, !124, !167, !231, !232, !233, !234, !235, !236, !269, !271, !272, !273}
!119 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !117, file: !7, line: 160, baseType: !11, size: 1280, align: 64)
!120 = !DIDerivedType(tag: DW_TAG_member, name: "entry", scope: !117, file: !7, line: 162, baseType: !31, size: 64, align: 64, offset: 1280)
!121 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_set", scope: !117, file: !7, line: 165, baseType: !25, size: 32, align: 32, offset: 1344)
!122 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_dev", scope: !117, file: !7, line: 166, baseType: !53, size: 64, align: 64, offset: 1408)
!123 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_ino", scope: !117, file: !7, line: 167, baseType: !53, size: 64, align: 64, offset: 1472)
!124 = !DIDerivedType(tag: DW_TAG_member, name: "client", scope: !117, file: !7, line: 170, baseType: !125, size: 576, align: 64, offset: 1536)
!125 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_client", file: !7, line: 134, size: 576, align: 64, elements: !126)
!126 = !{!127, !132, !138, !144, !149, !152, !157, !158, !159, !160}
!127 = !DIDerivedType(tag: DW_TAG_member, name: "opener", scope: !125, file: !7, line: 135, baseType: !128, size: 64, align: 64)
!128 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !129, size: 64, align: 64)
!129 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_open_callback", file: !33, line: 241, baseType: !130)
!130 = !DISubroutineType(types: !131)
!131 = !{!25, !10, !4}
!132 = !DIDerivedType(tag: DW_TAG_member, name: "reader", scope: !125, file: !7, line: 136, baseType: !133, size: 64, align: 64, offset: 64)
!133 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !134, size: 64, align: 64)
!134 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_read_callback", file: !33, line: 218, baseType: !135)
!135 = !DISubroutineType(types: !136)
!136 = !{!137, !10, !4, !65}
!137 = !DIDerivedType(tag: DW_TAG_typedef, name: "la_ssize_t", file: !33, line: 95, baseType: !39)
!138 = !DIDerivedType(tag: DW_TAG_member, name: "skipper", scope: !125, file: !7, line: 137, baseType: !139, size: 64, align: 64, offset: 128)
!139 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !140, size: 64, align: 64)
!140 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_skip_callback", file: !33, line: 226, baseType: !141)
!141 = !DISubroutineType(types: !142)
!142 = !{!143, !10, !4, !143}
!143 = !DIDerivedType(tag: DW_TAG_typedef, name: "la_int64_t", file: !33, line: 73, baseType: !53)
!144 = !DIDerivedType(tag: DW_TAG_member, name: "seeker", scope: !125, file: !7, line: 138, baseType: !145, size: 64, align: 64, offset: 192)
!145 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !146, size: 64, align: 64)
!146 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_seek_callback", file: !33, line: 233, baseType: !147)
!147 = !DISubroutineType(types: !148)
!148 = !{!143, !10, !4, !143, !25}
!149 = !DIDerivedType(tag: DW_TAG_member, name: "closer", scope: !125, file: !7, line: 139, baseType: !150, size: 64, align: 64, offset: 256)
!150 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !151, size: 64, align: 64)
!151 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_close_callback", file: !33, line: 243, baseType: !130)
!152 = !DIDerivedType(tag: DW_TAG_member, name: "switcher", scope: !125, file: !7, line: 140, baseType: !153, size: 64, align: 64, offset: 320)
!153 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !154, size: 64, align: 64)
!154 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_switch_callback", file: !33, line: 249, baseType: !155)
!155 = !DISubroutineType(types: !156)
!156 = !{!25, !10, !4, !4}
!157 = !DIDerivedType(tag: DW_TAG_member, name: "nodes", scope: !125, file: !7, line: 141, baseType: !15, size: 32, align: 32, offset: 384)
!158 = !DIDerivedType(tag: DW_TAG_member, name: "cursor", scope: !125, file: !7, line: 142, baseType: !15, size: 32, align: 32, offset: 416)
!159 = !DIDerivedType(tag: DW_TAG_member, name: "position", scope: !125, file: !7, line: 143, baseType: !53, size: 64, align: 64, offset: 448)
!160 = !DIDerivedType(tag: DW_TAG_member, name: "dataset", scope: !125, file: !7, line: 144, baseType: !161, size: 64, align: 64, offset: 512)
!161 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !162, size: 64, align: 64)
!162 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_data_node", file: !7, line: 129, size: 192, align: 64, elements: !163)
!163 = !{!164, !165, !166}
!164 = !DIDerivedType(tag: DW_TAG_member, name: "begin_position", scope: !162, file: !7, line: 130, baseType: !53, size: 64, align: 64)
!165 = !DIDerivedType(tag: DW_TAG_member, name: "total_size", scope: !162, file: !7, line: 131, baseType: !53, size: 64, align: 64, offset: 64)
!166 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !162, file: !7, line: 132, baseType: !4, size: 64, align: 64, offset: 128)
!167 = !DIDerivedType(tag: DW_TAG_member, name: "bidders", scope: !117, file: !7, line: 173, baseType: !168, size: 6144, align: 64, offset: 2112)
!168 = !DICompositeType(tag: DW_TAG_array_type, baseType: !169, size: 6144, align: 64, elements: !229)
!169 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_filter_bidder", file: !7, line: 60, size: 384, align: 64, elements: !170)
!170 = !{!171, !172, !173, !220, !221, !225}
!171 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !169, file: !7, line: 62, baseType: !4, size: 64, align: 64)
!172 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !169, file: !7, line: 64, baseType: !81, size: 64, align: 64, offset: 64)
!173 = !DIDerivedType(tag: DW_TAG_member, name: "bid", scope: !169, file: !7, line: 66, baseType: !174, size: 64, align: 64, offset: 128)
!174 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !175, size: 64, align: 64)
!175 = !DISubroutineType(types: !176)
!176 = !{!25, !177, !178}
!177 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !169, size: 64, align: 64)
!178 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !179, size: 64, align: 64)
!179 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_filter", file: !7, line: 82, size: 1408, align: 64, elements: !180)
!180 = !{!181, !182, !183, !184, !185, !189, !193, !197, !201, !202, !206, !207, !208, !209, !210, !211, !212, !213, !214, !215, !216, !217, !218, !219}
!181 = !DIDerivedType(tag: DW_TAG_member, name: "position", scope: !179, file: !7, line: 83, baseType: !53, size: 64, align: 64)
!182 = !DIDerivedType(tag: DW_TAG_member, name: "bidder", scope: !179, file: !7, line: 86, baseType: !177, size: 64, align: 64, offset: 64)
!183 = !DIDerivedType(tag: DW_TAG_member, name: "upstream", scope: !179, file: !7, line: 87, baseType: !178, size: 64, align: 64, offset: 128)
!184 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !179, file: !7, line: 88, baseType: !116, size: 64, align: 64, offset: 192)
!185 = !DIDerivedType(tag: DW_TAG_member, name: "open", scope: !179, file: !7, line: 90, baseType: !186, size: 64, align: 64, offset: 256)
!186 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !187, size: 64, align: 64)
!187 = !DISubroutineType(types: !188)
!188 = !{!25, !178}
!189 = !DIDerivedType(tag: DW_TAG_member, name: "read", scope: !179, file: !7, line: 92, baseType: !190, size: 64, align: 64, offset: 320)
!190 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !191, size: 64, align: 64)
!191 = !DISubroutineType(types: !192)
!192 = !{!39, !178, !65}
!193 = !DIDerivedType(tag: DW_TAG_member, name: "skip", scope: !179, file: !7, line: 94, baseType: !194, size: 64, align: 64, offset: 384)
!194 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !195, size: 64, align: 64)
!195 = !DISubroutineType(types: !196)
!196 = !{!53, !178, !53}
!197 = !DIDerivedType(tag: DW_TAG_member, name: "seek", scope: !179, file: !7, line: 96, baseType: !198, size: 64, align: 64, offset: 448)
!198 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !199, size: 64, align: 64)
!199 = !DISubroutineType(types: !200)
!200 = !{!53, !178, !53, !25}
!201 = !DIDerivedType(tag: DW_TAG_member, name: "close", scope: !179, file: !7, line: 98, baseType: !186, size: 64, align: 64, offset: 512)
!202 = !DIDerivedType(tag: DW_TAG_member, name: "sswitch", scope: !179, file: !7, line: 100, baseType: !203, size: 64, align: 64, offset: 576)
!203 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !204, size: 64, align: 64)
!204 = !DISubroutineType(types: !205)
!205 = !{!25, !178, !15}
!206 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !179, file: !7, line: 102, baseType: !4, size: 64, align: 64, offset: 640)
!207 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !179, file: !7, line: 104, baseType: !81, size: 64, align: 64, offset: 704)
!208 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !179, file: !7, line: 105, baseType: !25, size: 32, align: 32, offset: 768)
!209 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !179, file: !7, line: 108, baseType: !96, size: 64, align: 64, offset: 832)
!210 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_size", scope: !179, file: !7, line: 109, baseType: !46, size: 64, align: 64, offset: 896)
!211 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !179, file: !7, line: 110, baseType: !96, size: 64, align: 64, offset: 960)
!212 = !DIDerivedType(tag: DW_TAG_member, name: "avail", scope: !179, file: !7, line: 111, baseType: !46, size: 64, align: 64, offset: 1024)
!213 = !DIDerivedType(tag: DW_TAG_member, name: "client_buff", scope: !179, file: !7, line: 112, baseType: !44, size: 64, align: 64, offset: 1088)
!214 = !DIDerivedType(tag: DW_TAG_member, name: "client_total", scope: !179, file: !7, line: 113, baseType: !46, size: 64, align: 64, offset: 1152)
!215 = !DIDerivedType(tag: DW_TAG_member, name: "client_next", scope: !179, file: !7, line: 114, baseType: !81, size: 64, align: 64, offset: 1216)
!216 = !DIDerivedType(tag: DW_TAG_member, name: "client_avail", scope: !179, file: !7, line: 115, baseType: !46, size: 64, align: 64, offset: 1280)
!217 = !DIDerivedType(tag: DW_TAG_member, name: "end_of_file", scope: !179, file: !7, line: 116, baseType: !83, size: 8, align: 8, offset: 1344)
!218 = !DIDerivedType(tag: DW_TAG_member, name: "closed", scope: !179, file: !7, line: 117, baseType: !83, size: 8, align: 8, offset: 1352)
!219 = !DIDerivedType(tag: DW_TAG_member, name: "fatal", scope: !179, file: !7, line: 118, baseType: !83, size: 8, align: 8, offset: 1360)
!220 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !169, file: !7, line: 69, baseType: !186, size: 64, align: 64, offset: 192)
!221 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !169, file: !7, line: 71, baseType: !222, size: 64, align: 64, offset: 256)
!222 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !223, size: 64, align: 64)
!223 = !DISubroutineType(types: !224)
!224 = !{!25, !177, !81, !81}
!225 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !169, file: !7, line: 74, baseType: !226, size: 64, align: 64, offset: 320)
!226 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !227, size: 64, align: 64)
!227 = !DISubroutineType(types: !228)
!228 = !{!25, !177}
!229 = !{!230}
!230 = !DISubrange(count: 16)
!231 = !DIDerivedType(tag: DW_TAG_member, name: "filter", scope: !117, file: !7, line: 176, baseType: !178, size: 64, align: 64, offset: 8256)
!232 = !DIDerivedType(tag: DW_TAG_member, name: "bypass_filter_bidding", scope: !117, file: !7, line: 179, baseType: !25, size: 32, align: 32, offset: 8320)
!233 = !DIDerivedType(tag: DW_TAG_member, name: "header_position", scope: !117, file: !7, line: 182, baseType: !53, size: 64, align: 64, offset: 8384)
!234 = !DIDerivedType(tag: DW_TAG_member, name: "data_start_node", scope: !117, file: !7, line: 185, baseType: !15, size: 32, align: 32, offset: 8448)
!235 = !DIDerivedType(tag: DW_TAG_member, name: "data_end_node", scope: !117, file: !7, line: 186, baseType: !15, size: 32, align: 32, offset: 8480)
!236 = !DIDerivedType(tag: DW_TAG_member, name: "formats", scope: !117, file: !7, line: 209, baseType: !237, size: 11264, align: 64, offset: 8512)
!237 = !DICompositeType(tag: DW_TAG_array_type, baseType: !238, size: 11264, align: 64, elements: !229)
!238 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_format_descriptor", file: !7, line: 196, size: 704, align: 64, elements: !239)
!239 = !{!240, !241, !242, !246, !250, !254, !258, !262, !266, !267, !268}
!240 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !238, file: !7, line: 197, baseType: !4, size: 64, align: 64)
!241 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !238, file: !7, line: 198, baseType: !81, size: 64, align: 64, offset: 64)
!242 = !DIDerivedType(tag: DW_TAG_member, name: "bid", scope: !238, file: !7, line: 199, baseType: !243, size: 64, align: 64, offset: 128)
!243 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !244, size: 64, align: 64)
!244 = !DISubroutineType(types: !245)
!245 = !{!25, !116, !25}
!246 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !238, file: !7, line: 200, baseType: !247, size: 64, align: 64, offset: 192)
!247 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !248, size: 64, align: 64)
!248 = !DISubroutineType(types: !249)
!249 = !{!25, !116, !81, !81}
!250 = !DIDerivedType(tag: DW_TAG_member, name: "read_header", scope: !238, file: !7, line: 202, baseType: !251, size: 64, align: 64, offset: 256)
!251 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !252, size: 64, align: 64)
!252 = !DISubroutineType(types: !253)
!253 = !{!25, !116, !31}
!254 = !DIDerivedType(tag: DW_TAG_member, name: "read_data", scope: !238, file: !7, line: 203, baseType: !255, size: 64, align: 64, offset: 320)
!255 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !256, size: 64, align: 64)
!256 = !DISubroutineType(types: !257)
!257 = !{!25, !116, !65, !66, !67}
!258 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_skip", scope: !238, file: !7, line: 204, baseType: !259, size: 64, align: 64, offset: 384)
!259 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !260, size: 64, align: 64)
!260 = !DISubroutineType(types: !261)
!261 = !{!25, !116}
!262 = !DIDerivedType(tag: DW_TAG_member, name: "seek_data", scope: !238, file: !7, line: 205, baseType: !263, size: 64, align: 64, offset: 448)
!263 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !264, size: 64, align: 64)
!264 = !DISubroutineType(types: !265)
!265 = !{!53, !116, !53, !25}
!266 = !DIDerivedType(tag: DW_TAG_member, name: "cleanup", scope: !238, file: !7, line: 206, baseType: !259, size: 64, align: 64, offset: 512)
!267 = !DIDerivedType(tag: DW_TAG_member, name: "format_capabilties", scope: !238, file: !7, line: 207, baseType: !259, size: 64, align: 64, offset: 576)
!268 = !DIDerivedType(tag: DW_TAG_member, name: "has_encrypted_entries", scope: !238, file: !7, line: 208, baseType: !259, size: 64, align: 64, offset: 640)
!269 = !DIDerivedType(tag: DW_TAG_member, name: "format", scope: !117, file: !7, line: 210, baseType: !270, size: 64, align: 64, offset: 19776)
!270 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !238, size: 64, align: 64)
!271 = !DIDerivedType(tag: DW_TAG_member, name: "extract", scope: !117, file: !7, line: 215, baseType: !5, size: 64, align: 64, offset: 19840)
!272 = !DIDerivedType(tag: DW_TAG_member, name: "cleanup_archive_extract", scope: !117, file: !7, line: 216, baseType: !259, size: 64, align: 64, offset: 19904)
!273 = !DIDerivedType(tag: DW_TAG_member, name: "passphrases", scope: !117, file: !7, line: 227, baseType: !274, size: 320, align: 64, offset: 19968)
!274 = !DICompositeType(tag: DW_TAG_structure_type, scope: !117, file: !7, line: 221, size: 320, align: 64, elements: !275)
!275 = !{!276, !282, !284, !285, !290}
!276 = !DIDerivedType(tag: DW_TAG_member, name: "first", scope: !274, file: !7, line: 222, baseType: !277, size: 64, align: 64)
!277 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !278, size: 64, align: 64)
!278 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_passphrase", file: !7, line: 146, size: 128, align: 64, elements: !279)
!279 = !{!280, !281}
!280 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase", scope: !278, file: !7, line: 147, baseType: !96, size: 64, align: 64)
!281 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !278, file: !7, line: 148, baseType: !277, size: 64, align: 64, offset: 64)
!282 = !DIDerivedType(tag: DW_TAG_member, name: "last", scope: !274, file: !7, line: 223, baseType: !283, size: 64, align: 64, offset: 64)
!283 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !277, size: 64, align: 64)
!284 = !DIDerivedType(tag: DW_TAG_member, name: "candidate", scope: !274, file: !7, line: 224, baseType: !25, size: 32, align: 32, offset: 128)
!285 = !DIDerivedType(tag: DW_TAG_member, name: "callback", scope: !274, file: !7, line: 225, baseType: !286, size: 64, align: 64, offset: 192)
!286 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !287, size: 64, align: 64)
!287 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_passphrase_callback", file: !33, line: 256, baseType: !288)
!288 = !DISubroutineType(types: !289)
!289 = !{!81, !10, !4}
!290 = !DIDerivedType(tag: DW_TAG_member, name: "client_data", scope: !274, file: !7, line: 226, baseType: !4, size: 64, align: 64, offset: 256)
!291 = !{!292, !295, !298, !301, !302}
!292 = distinct !DISubprogram(name: "__archive_read_get_extract", scope: !1, file: !1, line: 52, type: !293, isLocal: false, isDefinition: true, scopeLine: 53, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!293 = !DISubroutineType(types: !294)
!294 = !{!5, !116}
!295 = distinct !DISubprogram(name: "archive_read_extract2", scope: !1, file: !1, line: 82, type: !296, isLocal: false, isDefinition: true, scopeLine: 84, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!296 = !DISubroutineType(types: !297)
!297 = !{!25, !10, !31, !10}
!298 = distinct !DISubprogram(name: "archive_read_extract_set_progress_callback", scope: !1, file: !1, line: 114, type: !299, isLocal: false, isDefinition: true, scopeLine: 116, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!299 = !DISubroutineType(types: !300)
!300 = !{null, !10, !112, !4}
!301 = distinct !DISubprogram(name: "archive_read_extract_cleanup", scope: !1, file: !1, line: 69, type: !260, isLocal: true, isDefinition: true, scopeLine: 70, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!302 = distinct !DISubprogram(name: "copy_data", scope: !1, file: !1, line: 126, type: !303, isLocal: true, isDefinition: true, scopeLine: 127, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!303 = !DISubroutineType(types: !304)
!304 = !{!25, !10, !10}
!305 = !{i32 2, !"Dwarf Version", i32 4}
!306 = !{i32 2, !"Debug Info Version", i32 3}
!307 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!308 = !DILocalVariable(name: "a", arg: 1, scope: !292, file: !1, line: 52, type: !116)
!309 = !DIExpression()
!310 = !DILocation(line: 52, column: 49, scope: !292)
!311 = !DILocation(line: 54, column: 6, scope: !312)
!312 = distinct !DILexicalBlock(scope: !292, file: !1, line: 54, column: 6)
!313 = !DILocation(line: 54, column: 9, scope: !312)
!314 = !DILocation(line: 54, column: 17, scope: !312)
!315 = !DILocation(line: 54, column: 6, scope: !292)
!316 = !DILocation(line: 55, column: 47, scope: !317)
!317 = distinct !DILexicalBlock(scope: !312, file: !1, line: 54, column: 26)
!318 = !DILocation(line: 55, column: 16, scope: !317)
!319 = !DILocation(line: 55, column: 3, scope: !317)
!320 = !DILocation(line: 55, column: 6, scope: !317)
!321 = !DILocation(line: 55, column: 14, scope: !317)
!322 = !DILocation(line: 56, column: 7, scope: !323)
!323 = distinct !DILexicalBlock(scope: !317, file: !1, line: 56, column: 7)
!324 = !DILocation(line: 56, column: 10, scope: !323)
!325 = !DILocation(line: 56, column: 18, scope: !323)
!326 = !DILocation(line: 56, column: 7, scope: !317)
!327 = !DILocation(line: 57, column: 23, scope: !328)
!328 = distinct !DILexicalBlock(scope: !323, file: !1, line: 56, column: 27)
!329 = !DILocation(line: 57, column: 26, scope: !328)
!330 = !DILocation(line: 57, column: 4, scope: !328)
!331 = !DILocation(line: 58, column: 4, scope: !328)
!332 = !DILocation(line: 60, column: 3, scope: !317)
!333 = !DILocation(line: 60, column: 6, scope: !317)
!334 = !DILocation(line: 60, column: 30, scope: !317)
!335 = !DILocation(line: 61, column: 2, scope: !317)
!336 = !DILocation(line: 62, column: 10, scope: !292)
!337 = !DILocation(line: 62, column: 13, scope: !292)
!338 = !DILocation(line: 62, column: 2, scope: !292)
!339 = !DILocation(line: 63, column: 1, scope: !292)
!340 = !DILocalVariable(name: "a", arg: 1, scope: !301, file: !1, line: 69, type: !116)
!341 = !DILocation(line: 69, column: 51, scope: !301)
!342 = !DILocalVariable(name: "ret", scope: !301, file: !1, line: 71, type: !25)
!343 = !DILocation(line: 71, column: 6, scope: !301)
!344 = !DILocation(line: 73, column: 6, scope: !345)
!345 = distinct !DILexicalBlock(scope: !301, file: !1, line: 73, column: 6)
!346 = !DILocation(line: 73, column: 9, scope: !345)
!347 = !DILocation(line: 73, column: 18, scope: !345)
!348 = !DILocation(line: 73, column: 21, scope: !345)
!349 = !DILocation(line: 73, column: 6, scope: !301)
!350 = !DILocation(line: 74, column: 28, scope: !351)
!351 = distinct !DILexicalBlock(scope: !345, file: !1, line: 73, column: 30)
!352 = !DILocation(line: 74, column: 31, scope: !351)
!353 = !DILocation(line: 74, column: 40, scope: !351)
!354 = !DILocation(line: 74, column: 9, scope: !351)
!355 = !DILocation(line: 74, column: 7, scope: !351)
!356 = !DILocation(line: 75, column: 2, scope: !351)
!357 = !DILocation(line: 76, column: 7, scope: !301)
!358 = !DILocation(line: 76, column: 10, scope: !301)
!359 = !DILocation(line: 76, column: 2, scope: !301)
!360 = !DILocation(line: 77, column: 2, scope: !301)
!361 = !DILocation(line: 77, column: 5, scope: !301)
!362 = !DILocation(line: 77, column: 13, scope: !301)
!363 = !DILocation(line: 78, column: 10, scope: !301)
!364 = !DILocation(line: 78, column: 2, scope: !301)
!365 = !DILocalVariable(name: "_a", arg: 1, scope: !295, file: !1, line: 82, type: !10)
!366 = !DILocation(line: 82, column: 39, scope: !295)
!367 = !DILocalVariable(name: "entry", arg: 2, scope: !295, file: !1, line: 82, type: !31)
!368 = !DILocation(line: 82, column: 65, scope: !295)
!369 = !DILocalVariable(name: "ad", arg: 3, scope: !295, file: !1, line: 83, type: !10)
!370 = !DILocation(line: 83, column: 21, scope: !295)
!371 = !DILocalVariable(name: "a", scope: !295, file: !1, line: 85, type: !116)
!372 = !DILocation(line: 85, column: 23, scope: !295)
!373 = !DILocation(line: 85, column: 50, scope: !295)
!374 = !DILocation(line: 85, column: 27, scope: !295)
!375 = !DILocalVariable(name: "r", scope: !295, file: !1, line: 86, type: !25)
!376 = !DILocation(line: 86, column: 6, scope: !295)
!377 = !DILocalVariable(name: "r2", scope: !295, file: !1, line: 86, type: !25)
!378 = !DILocation(line: 86, column: 9, scope: !295)
!379 = !DILocation(line: 89, column: 6, scope: !380)
!380 = distinct !DILexicalBlock(scope: !295, file: !1, line: 89, column: 6)
!381 = !DILocation(line: 89, column: 9, scope: !380)
!382 = !DILocation(line: 89, column: 6, scope: !295)
!383 = !DILocation(line: 90, column: 36, scope: !380)
!384 = !DILocation(line: 91, column: 7, scope: !380)
!385 = !DILocation(line: 91, column: 10, scope: !380)
!386 = !DILocation(line: 91, column: 25, scope: !380)
!387 = !DILocation(line: 91, column: 28, scope: !380)
!388 = !DILocation(line: 90, column: 3, scope: !380)
!389 = !DILocation(line: 92, column: 27, scope: !295)
!390 = !DILocation(line: 92, column: 31, scope: !295)
!391 = !DILocation(line: 92, column: 6, scope: !295)
!392 = !DILocation(line: 92, column: 4, scope: !295)
!393 = !DILocation(line: 93, column: 6, scope: !394)
!394 = distinct !DILexicalBlock(scope: !295, file: !1, line: 93, column: 6)
!395 = !DILocation(line: 93, column: 8, scope: !394)
!396 = !DILocation(line: 93, column: 6, scope: !295)
!397 = !DILocation(line: 94, column: 5, scope: !394)
!398 = !DILocation(line: 94, column: 3, scope: !394)
!399 = !DILocation(line: 95, column: 6, scope: !400)
!400 = distinct !DILexicalBlock(scope: !295, file: !1, line: 95, column: 6)
!401 = !DILocation(line: 95, column: 8, scope: !400)
!402 = !DILocation(line: 95, column: 6, scope: !295)
!403 = !DILocation(line: 97, column: 24, scope: !400)
!404 = !DILocation(line: 97, column: 27, scope: !400)
!405 = !DILocation(line: 97, column: 36, scope: !400)
!406 = !DILocation(line: 97, column: 4, scope: !400)
!407 = !DILocation(line: 98, column: 38, scope: !408)
!408 = distinct !DILexicalBlock(scope: !400, file: !1, line: 98, column: 11)
!409 = !DILocation(line: 98, column: 12, scope: !408)
!410 = !DILocation(line: 98, column: 45, scope: !408)
!411 = !DILocation(line: 98, column: 67, scope: !412)
!412 = !DILexicalBlockFile(scope: !408, file: !1, discriminator: 1)
!413 = !DILocation(line: 98, column: 48, scope: !412)
!414 = !DILocation(line: 98, column: 74, scope: !412)
!415 = !DILocation(line: 98, column: 11, scope: !412)
!416 = !DILocation(line: 100, column: 17, scope: !408)
!417 = !DILocation(line: 100, column: 21, scope: !408)
!418 = !DILocation(line: 100, column: 7, scope: !408)
!419 = !DILocation(line: 100, column: 5, scope: !408)
!420 = !DILocation(line: 100, column: 3, scope: !408)
!421 = !DILocation(line: 101, column: 34, scope: !295)
!422 = !DILocation(line: 101, column: 7, scope: !295)
!423 = !DILocation(line: 101, column: 5, scope: !295)
!424 = !DILocation(line: 102, column: 6, scope: !425)
!425 = distinct !DILexicalBlock(scope: !295, file: !1, line: 102, column: 6)
!426 = !DILocation(line: 102, column: 9, scope: !425)
!427 = !DILocation(line: 102, column: 6, scope: !295)
!428 = !DILocation(line: 103, column: 6, scope: !425)
!429 = !DILocation(line: 103, column: 3, scope: !425)
!430 = !DILocation(line: 105, column: 6, scope: !431)
!431 = distinct !DILexicalBlock(scope: !295, file: !1, line: 105, column: 6)
!432 = !DILocation(line: 105, column: 9, scope: !431)
!433 = !DILocation(line: 105, column: 23, scope: !431)
!434 = !DILocation(line: 105, column: 26, scope: !435)
!435 = !DILexicalBlockFile(scope: !431, file: !1, discriminator: 1)
!436 = !DILocation(line: 105, column: 28, scope: !435)
!437 = !DILocation(line: 105, column: 6, scope: !435)
!438 = !DILocation(line: 106, column: 23, scope: !431)
!439 = !DILocation(line: 106, column: 26, scope: !431)
!440 = !DILocation(line: 106, column: 35, scope: !431)
!441 = !DILocation(line: 106, column: 3, scope: !431)
!442 = !DILocation(line: 108, column: 6, scope: !443)
!443 = distinct !DILexicalBlock(scope: !295, file: !1, line: 108, column: 6)
!444 = !DILocation(line: 108, column: 11, scope: !443)
!445 = !DILocation(line: 108, column: 9, scope: !443)
!446 = !DILocation(line: 108, column: 6, scope: !295)
!447 = !DILocation(line: 109, column: 7, scope: !443)
!448 = !DILocation(line: 109, column: 5, scope: !443)
!449 = !DILocation(line: 109, column: 3, scope: !443)
!450 = !DILocation(line: 110, column: 10, scope: !295)
!451 = !DILocation(line: 110, column: 2, scope: !295)
!452 = !DILocalVariable(name: "ar", arg: 1, scope: !302, file: !1, line: 126, type: !10)
!453 = !DILocation(line: 126, column: 27, scope: !302)
!454 = !DILocalVariable(name: "aw", arg: 2, scope: !302, file: !1, line: 126, type: !10)
!455 = !DILocation(line: 126, column: 47, scope: !302)
!456 = !DILocalVariable(name: "offset", scope: !302, file: !1, line: 128, type: !53)
!457 = !DILocation(line: 128, column: 10, scope: !302)
!458 = !DILocalVariable(name: "buff", scope: !302, file: !1, line: 129, type: !44)
!459 = !DILocation(line: 129, column: 14, scope: !302)
!460 = !DILocalVariable(name: "extract", scope: !302, file: !1, line: 130, type: !5)
!461 = !DILocation(line: 130, column: 31, scope: !302)
!462 = !DILocalVariable(name: "size", scope: !302, file: !1, line: 131, type: !46)
!463 = !DILocation(line: 131, column: 9, scope: !302)
!464 = !DILocalVariable(name: "r", scope: !302, file: !1, line: 132, type: !25)
!465 = !DILocation(line: 132, column: 6, scope: !302)
!466 = !DILocation(line: 134, column: 62, scope: !302)
!467 = !DILocation(line: 134, column: 39, scope: !302)
!468 = !DILocation(line: 134, column: 12, scope: !302)
!469 = !DILocation(line: 134, column: 10, scope: !302)
!470 = !DILocation(line: 135, column: 6, scope: !471)
!471 = distinct !DILexicalBlock(scope: !302, file: !1, line: 135, column: 6)
!472 = !DILocation(line: 135, column: 14, scope: !471)
!473 = !DILocation(line: 135, column: 6, scope: !302)
!474 = !DILocation(line: 136, column: 3, scope: !471)
!475 = !DILocation(line: 137, column: 2, scope: !302)
!476 = !DILocation(line: 138, column: 31, scope: !477)
!477 = distinct !DILexicalBlock(scope: !478, file: !1, line: 137, column: 11)
!478 = distinct !DILexicalBlock(scope: !479, file: !1, line: 137, column: 2)
!479 = distinct !DILexicalBlock(scope: !302, file: !1, line: 137, column: 2)
!480 = !DILocation(line: 138, column: 7, scope: !477)
!481 = !DILocation(line: 138, column: 5, scope: !477)
!482 = !DILocation(line: 139, column: 7, scope: !483)
!483 = distinct !DILexicalBlock(scope: !477, file: !1, line: 139, column: 7)
!484 = !DILocation(line: 139, column: 9, scope: !483)
!485 = !DILocation(line: 139, column: 7, scope: !477)
!486 = !DILocation(line: 140, column: 4, scope: !483)
!487 = !DILocation(line: 141, column: 7, scope: !488)
!488 = distinct !DILexicalBlock(scope: !477, file: !1, line: 141, column: 7)
!489 = !DILocation(line: 141, column: 9, scope: !488)
!490 = !DILocation(line: 141, column: 7, scope: !477)
!491 = !DILocation(line: 142, column: 12, scope: !488)
!492 = !DILocation(line: 142, column: 4, scope: !488)
!493 = !DILocation(line: 143, column: 37, scope: !477)
!494 = !DILocation(line: 143, column: 41, scope: !477)
!495 = !DILocation(line: 143, column: 47, scope: !477)
!496 = !DILocation(line: 143, column: 53, scope: !477)
!497 = !DILocation(line: 143, column: 12, scope: !477)
!498 = !DILocation(line: 143, column: 7, scope: !477)
!499 = !DILocation(line: 143, column: 5, scope: !477)
!500 = !DILocation(line: 144, column: 7, scope: !501)
!501 = distinct !DILexicalBlock(scope: !477, file: !1, line: 144, column: 7)
!502 = !DILocation(line: 144, column: 9, scope: !501)
!503 = !DILocation(line: 144, column: 7, scope: !477)
!504 = !DILocation(line: 145, column: 6, scope: !501)
!505 = !DILocation(line: 145, column: 4, scope: !501)
!506 = !DILocation(line: 146, column: 7, scope: !507)
!507 = distinct !DILexicalBlock(scope: !477, file: !1, line: 146, column: 7)
!508 = !DILocation(line: 146, column: 9, scope: !507)
!509 = !DILocation(line: 146, column: 7, scope: !477)
!510 = !DILocation(line: 147, column: 22, scope: !511)
!511 = distinct !DILexicalBlock(scope: !507, file: !1, line: 146, column: 23)
!512 = !DILocation(line: 147, column: 40, scope: !511)
!513 = !DILocation(line: 147, column: 26, scope: !511)
!514 = !DILocation(line: 148, column: 35, scope: !511)
!515 = !DILocation(line: 148, column: 14, scope: !511)
!516 = !DILocation(line: 147, column: 4, scope: !511)
!517 = !DILocation(line: 149, column: 12, scope: !511)
!518 = !DILocation(line: 149, column: 4, scope: !511)
!519 = !DILocation(line: 151, column: 7, scope: !520)
!520 = distinct !DILexicalBlock(scope: !477, file: !1, line: 151, column: 7)
!521 = !DILocation(line: 151, column: 16, scope: !520)
!522 = !DILocation(line: 151, column: 7, scope: !477)
!523 = !DILocation(line: 152, column: 5, scope: !520)
!524 = !DILocation(line: 152, column: 14, scope: !520)
!525 = !DILocation(line: 153, column: 9, scope: !520)
!526 = !DILocation(line: 153, column: 18, scope: !520)
!527 = !DILocation(line: 152, column: 4, scope: !520)
!528 = !DILocation(line: 137, column: 2, scope: !529)
!529 = !DILexicalBlockFile(scope: !478, file: !1, discriminator: 1)
!530 = !DILocation(line: 155, column: 1, scope: !302)
!531 = !DILocalVariable(name: "_a", arg: 1, scope: !298, file: !1, line: 114, type: !10)
!532 = !DILocation(line: 114, column: 60, scope: !298)
!533 = !DILocalVariable(name: "progress_func", arg: 2, scope: !298, file: !1, line: 115, type: !112)
!534 = !DILocation(line: 115, column: 12, scope: !298)
!535 = !DILocalVariable(name: "user_data", arg: 3, scope: !298, file: !1, line: 115, type: !4)
!536 = !DILocation(line: 115, column: 42, scope: !298)
!537 = !DILocalVariable(name: "a", scope: !298, file: !1, line: 117, type: !116)
!538 = !DILocation(line: 117, column: 23, scope: !298)
!539 = !DILocation(line: 117, column: 50, scope: !298)
!540 = !DILocation(line: 117, column: 27, scope: !298)
!541 = !DILocalVariable(name: "extract", scope: !298, file: !1, line: 118, type: !5)
!542 = !DILocation(line: 118, column: 31, scope: !298)
!543 = !DILocation(line: 118, column: 68, scope: !298)
!544 = !DILocation(line: 118, column: 41, scope: !298)
!545 = !DILocation(line: 119, column: 6, scope: !546)
!546 = distinct !DILexicalBlock(scope: !298, file: !1, line: 119, column: 6)
!547 = !DILocation(line: 119, column: 14, scope: !546)
!548 = !DILocation(line: 119, column: 6, scope: !298)
!549 = !DILocation(line: 120, column: 31, scope: !550)
!550 = distinct !DILexicalBlock(scope: !546, file: !1, line: 119, column: 23)
!551 = !DILocation(line: 120, column: 3, scope: !550)
!552 = !DILocation(line: 120, column: 12, scope: !550)
!553 = !DILocation(line: 120, column: 29, scope: !550)
!554 = !DILocation(line: 121, column: 41, scope: !550)
!555 = !DILocation(line: 121, column: 3, scope: !550)
!556 = !DILocation(line: 121, column: 12, scope: !550)
!557 = !DILocation(line: 121, column: 39, scope: !550)
!558 = !DILocation(line: 122, column: 2, scope: !550)
!559 = !DILocation(line: 123, column: 1, scope: !298)
