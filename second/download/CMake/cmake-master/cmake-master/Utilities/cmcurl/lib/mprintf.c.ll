; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmcurl/lib/mprintf.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }
%struct.__va_list_tag = type { i32, i32, i8*, i8* }
%struct.nsprintf = type { i8*, i64, i64 }
%struct.va_stack_t = type { i32, i32, i64, i64, %union.anon }
%union.anon = type { i8* }
%union.anon.0 = type { i64 }
%struct.asprintf = type { i8*, i64, i64, i32 }

@Curl_cfree = external global void (i8*)*, align 8
@Curl_cstrdup = external global i8* (i8*)*, align 8
@.str = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@stdout = external global %struct._IO_FILE*, align 8
@lower_digits = internal constant [37 x i8] c"0123456789abcdefghijklmnopqrstuvwxyz\00", align 16
@upper_digits = internal constant [37 x i8] c"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ\00", align 16
@dprintf_formatf.null = internal constant [6 x i8] c"(nil)\00", align 1
@dprintf_formatf.strnil = internal constant [6 x i8] c"(nil)\00", align 1
@dprintf_formatf.formatbuf = private unnamed_addr constant [32 x i8] c"%\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00\00", align 16
@.str.1 = private unnamed_addr constant [4 x i8] c"%ld\00", align 1
@.str.2 = private unnamed_addr constant [5 x i8] c".%ld\00", align 1
@Curl_cmalloc = external global i8* (i64)*, align 8
@Curl_crealloc = external global i8* (i8*, i64)*, align 8

; Function Attrs: nounwind uwtable
define i32 @curl_mvsnprintf(i8* %buffer, i64 %maxlength, i8* %format, %struct.__va_list_tag* %ap_save) #0 !dbg !140 {
entry:
  %buffer.addr = alloca i8*, align 8
  %maxlength.addr = alloca i64, align 8
  %format.addr = alloca i8*, align 8
  %ap_save.addr = alloca %struct.__va_list_tag*, align 8
  %retcode = alloca i32, align 4
  %info = alloca %struct.nsprintf, align 8
  store i8* %buffer, i8** %buffer.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buffer.addr, metadata !235, metadata !236), !dbg !237
  store i64 %maxlength, i64* %maxlength.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %maxlength.addr, metadata !238, metadata !236), !dbg !239
  store i8* %format, i8** %format.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %format.addr, metadata !240, metadata !236), !dbg !241
  store %struct.__va_list_tag* %ap_save, %struct.__va_list_tag** %ap_save.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.__va_list_tag** %ap_save.addr, metadata !242, metadata !236), !dbg !243
  call void @llvm.dbg.declare(metadata i32* %retcode, metadata !244, metadata !236), !dbg !245
  call void @llvm.dbg.declare(metadata %struct.nsprintf* %info, metadata !246, metadata !236), !dbg !247
  %0 = load i8*, i8** %buffer.addr, align 8, !dbg !248
  %buffer1 = getelementptr inbounds %struct.nsprintf, %struct.nsprintf* %info, i32 0, i32 0, !dbg !249
  store i8* %0, i8** %buffer1, align 8, !dbg !250
  %length = getelementptr inbounds %struct.nsprintf, %struct.nsprintf* %info, i32 0, i32 1, !dbg !251
  store i64 0, i64* %length, align 8, !dbg !252
  %1 = load i64, i64* %maxlength.addr, align 8, !dbg !253
  %max = getelementptr inbounds %struct.nsprintf, %struct.nsprintf* %info, i32 0, i32 2, !dbg !254
  store i64 %1, i64* %max, align 8, !dbg !255
  %2 = bitcast %struct.nsprintf* %info to i8*, !dbg !256
  %3 = load i8*, i8** %format.addr, align 8, !dbg !257
  %4 = load %struct.__va_list_tag*, %struct.__va_list_tag** %ap_save.addr, align 8, !dbg !258
  %call = call i32 @dprintf_formatf(i8* %2, i32 (i32, %struct._IO_FILE*)* @addbyter, i8* %3, %struct.__va_list_tag* %4), !dbg !259
  store i32 %call, i32* %retcode, align 4, !dbg !260
  %5 = load i32, i32* %retcode, align 4, !dbg !261
  %cmp = icmp ne i32 %5, -1, !dbg !263
  br i1 %cmp, label %land.lhs.true, label %if.end10, !dbg !264

land.lhs.true:                                    ; preds = %entry
  %max2 = getelementptr inbounds %struct.nsprintf, %struct.nsprintf* %info, i32 0, i32 2, !dbg !265
  %6 = load i64, i64* %max2, align 8, !dbg !265
  %tobool = icmp ne i64 %6, 0, !dbg !267
  br i1 %tobool, label %if.then, label %if.end10, !dbg !268

if.then:                                          ; preds = %land.lhs.true
  %max3 = getelementptr inbounds %struct.nsprintf, %struct.nsprintf* %info, i32 0, i32 2, !dbg !269
  %7 = load i64, i64* %max3, align 8, !dbg !269
  %length4 = getelementptr inbounds %struct.nsprintf, %struct.nsprintf* %info, i32 0, i32 1, !dbg !272
  %8 = load i64, i64* %length4, align 8, !dbg !272
  %cmp5 = icmp eq i64 %7, %8, !dbg !273
  br i1 %cmp5, label %if.then6, label %if.else, !dbg !274

if.then6:                                         ; preds = %if.then
  %buffer7 = getelementptr inbounds %struct.nsprintf, %struct.nsprintf* %info, i32 0, i32 0, !dbg !275
  %9 = load i8*, i8** %buffer7, align 8, !dbg !275
  %arrayidx = getelementptr inbounds i8, i8* %9, i64 -1, !dbg !276
  store i8 0, i8* %arrayidx, align 1, !dbg !277
  br label %if.end, !dbg !276

if.else:                                          ; preds = %if.then
  %buffer8 = getelementptr inbounds %struct.nsprintf, %struct.nsprintf* %info, i32 0, i32 0, !dbg !278
  %10 = load i8*, i8** %buffer8, align 8, !dbg !278
  %arrayidx9 = getelementptr inbounds i8, i8* %10, i64 0, !dbg !279
  store i8 0, i8* %arrayidx9, align 1, !dbg !280
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then6
  br label %if.end10, !dbg !281

if.end10:                                         ; preds = %if.end, %land.lhs.true, %entry
  %11 = load i32, i32* %retcode, align 4, !dbg !282
  ret i32 %11, !dbg !283
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define internal i32 @dprintf_formatf(i8* %data, i32 (i32, %struct._IO_FILE*)* %stream, i8* %format, %struct.__va_list_tag* %ap_save) #0 !dbg !181 {
entry:
  %retval = alloca i32, align 4
  %data.addr = alloca i8*, align 8
  %stream.addr = alloca i32 (i32, %struct._IO_FILE*)*, align 8
  %format.addr = alloca i8*, align 8
  %ap_save.addr = alloca %struct.__va_list_tag*, align 8
  %digits = alloca i8*, align 8
  %f = alloca i8*, align 8
  %done = alloca i32, align 4
  %param = alloca i64, align 8
  %param_num = alloca i64, align 8
  %vto = alloca [128 x %struct.va_stack_t], align 16
  %endpos = alloca [128 x i8*], align 16
  %end = alloca i8**, align 8
  %work = alloca [326 x i8], align 16
  %p = alloca %struct.va_stack_t*, align 8
  %workend = alloca i8*, align 8
  %is_alt = alloca i32, align 4
  %width = alloca i64, align 8
  %prec = alloca i64, align 8
  %is_neg = alloca i32, align 4
  %base = alloca i64, align 8
  %num = alloca i64, align 8
  %signed_num = alloca i64, align 8
  %w = alloca i8*, align 8
  %str = alloca i8*, align 8
  %len = alloca i64, align 8
  %ptr = alloca i8*, align 8
  %point = alloca i8*, align 8
  %formatbuf = alloca [32 x i8], align 16
  %fptr = alloca i8*, align 8
  %left = alloca i64, align 8
  %len611 = alloca i32, align 4
  %maxprec = alloca i64, align 8
  %val = alloca double, align 8
  store i8* %data, i8** %data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %data.addr, metadata !284, metadata !236), !dbg !285
  store i32 (i32, %struct._IO_FILE*)* %stream, i32 (i32, %struct._IO_FILE*)** %stream.addr, align 8
  call void @llvm.dbg.declare(metadata i32 (i32, %struct._IO_FILE*)** %stream.addr, metadata !286, metadata !236), !dbg !287
  store i8* %format, i8** %format.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %format.addr, metadata !288, metadata !236), !dbg !289
  store %struct.__va_list_tag* %ap_save, %struct.__va_list_tag** %ap_save.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.__va_list_tag** %ap_save.addr, metadata !290, metadata !236), !dbg !291
  call void @llvm.dbg.declare(metadata i8** %digits, metadata !292, metadata !236), !dbg !293
  store i8* getelementptr inbounds ([37 x i8], [37 x i8]* @lower_digits, i32 0, i32 0), i8** %digits, align 8, !dbg !293
  call void @llvm.dbg.declare(metadata i8** %f, metadata !294, metadata !236), !dbg !295
  call void @llvm.dbg.declare(metadata i32* %done, metadata !296, metadata !236), !dbg !297
  store i32 0, i32* %done, align 4, !dbg !297
  call void @llvm.dbg.declare(metadata i64* %param, metadata !298, metadata !236), !dbg !299
  call void @llvm.dbg.declare(metadata i64* %param_num, metadata !300, metadata !236), !dbg !301
  store i64 0, i64* %param_num, align 8, !dbg !301
  call void @llvm.dbg.declare(metadata [128 x %struct.va_stack_t]* %vto, metadata !302, metadata !236), !dbg !306
  call void @llvm.dbg.declare(metadata [128 x i8*]* %endpos, metadata !307, metadata !236), !dbg !309
  call void @llvm.dbg.declare(metadata i8*** %end, metadata !310, metadata !236), !dbg !311
  call void @llvm.dbg.declare(metadata [326 x i8]* %work, metadata !312, metadata !236), !dbg !316
  call void @llvm.dbg.declare(metadata %struct.va_stack_t** %p, metadata !317, metadata !236), !dbg !318
  call void @llvm.dbg.declare(metadata i8** %workend, metadata !319, metadata !236), !dbg !320
  %arrayidx = getelementptr inbounds [326 x i8], [326 x i8]* %work, i64 0, i64 324, !dbg !321
  store i8* %arrayidx, i8** %workend, align 8, !dbg !320
  %0 = load i8*, i8** %format.addr, align 8, !dbg !322
  %arraydecay = getelementptr inbounds [128 x %struct.va_stack_t], [128 x %struct.va_stack_t]* %vto, i32 0, i32 0, !dbg !324
  %arraydecay1 = getelementptr inbounds [128 x i8*], [128 x i8*]* %endpos, i32 0, i32 0, !dbg !325
  %1 = load %struct.__va_list_tag*, %struct.__va_list_tag** %ap_save.addr, align 8, !dbg !326
  %call = call i32 @dprintf_Pass1(i8* %0, %struct.va_stack_t* %arraydecay, i8** %arraydecay1, %struct.__va_list_tag* %1), !dbg !327
  %tobool = icmp ne i32 %call, 0, !dbg !327
  br i1 %tobool, label %if.then, label %if.end, !dbg !328

if.then:                                          ; preds = %entry
  store i32 -1, i32* %retval, align 4, !dbg !329
  br label %return, !dbg !329

if.end:                                           ; preds = %entry
  %arrayidx2 = getelementptr inbounds [128 x i8*], [128 x i8*]* %endpos, i64 0, i64 0, !dbg !330
  store i8** %arrayidx2, i8*** %end, align 8, !dbg !331
  %2 = load i8*, i8** %format.addr, align 8, !dbg !332
  store i8* %2, i8** %f, align 8, !dbg !333
  br label %while.cond, !dbg !334

while.cond:                                       ; preds = %sw.epilog, %do.end37, %do.end20, %if.end
  %3 = load i8*, i8** %f, align 8, !dbg !335
  %4 = load i8, i8* %3, align 1, !dbg !337
  %conv = sext i8 %4 to i32, !dbg !337
  %cmp = icmp ne i32 %conv, 0, !dbg !338
  br i1 %cmp, label %while.body, label %while.end786, !dbg !339

while.body:                                       ; preds = %while.cond
  call void @llvm.dbg.declare(metadata i32* %is_alt, metadata !340, metadata !236), !dbg !342
  call void @llvm.dbg.declare(metadata i64* %width, metadata !343, metadata !236), !dbg !344
  call void @llvm.dbg.declare(metadata i64* %prec, metadata !345, metadata !236), !dbg !346
  call void @llvm.dbg.declare(metadata i32* %is_neg, metadata !347, metadata !236), !dbg !348
  call void @llvm.dbg.declare(metadata i64* %base, metadata !349, metadata !236), !dbg !350
  call void @llvm.dbg.declare(metadata i64* %num, metadata !351, metadata !236), !dbg !352
  call void @llvm.dbg.declare(metadata i64* %signed_num, metadata !353, metadata !236), !dbg !354
  call void @llvm.dbg.declare(metadata i8** %w, metadata !355, metadata !236), !dbg !356
  %5 = load i8*, i8** %f, align 8, !dbg !357
  %6 = load i8, i8* %5, align 1, !dbg !359
  %conv4 = sext i8 %6 to i32, !dbg !359
  %cmp5 = icmp ne i32 %conv4, 37, !dbg !360
  br i1 %cmp5, label %if.then7, label %if.end21, !dbg !361

if.then7:                                         ; preds = %while.body
  br label %do.body, !dbg !362

do.body:                                          ; preds = %land.end, %if.then7
  br label %do.body8, !dbg !364

do.body8:                                         ; preds = %do.body
  %7 = load i32 (i32, %struct._IO_FILE*)*, i32 (i32, %struct._IO_FILE*)** %stream.addr, align 8, !dbg !366
  %8 = load i8*, i8** %f, align 8, !dbg !366
  %9 = load i8, i8* %8, align 1, !dbg !366
  %conv9 = zext i8 %9 to i32, !dbg !366
  %10 = load i8*, i8** %data.addr, align 8, !dbg !366
  %11 = bitcast i8* %10 to %struct._IO_FILE*, !dbg !366
  %call10 = call i32 %7(i32 %conv9, %struct._IO_FILE* %11), !dbg !366
  %cmp11 = icmp ne i32 %call10, -1, !dbg !366
  br i1 %cmp11, label %if.then13, label %if.else, !dbg !366

if.then13:                                        ; preds = %do.body8
  %12 = load i32, i32* %done, align 4, !dbg !370
  %inc = add nsw i32 %12, 1, !dbg !370
  store i32 %inc, i32* %done, align 4, !dbg !370
  br label %if.end14, !dbg !370

if.else:                                          ; preds = %do.body8
  %13 = load i32, i32* %done, align 4, !dbg !372
  store i32 %13, i32* %retval, align 4, !dbg !372
  br label %return, !dbg !372

if.end14:                                         ; preds = %if.then13
  br label %do.end, !dbg !374

do.end:                                           ; preds = %if.end14
  br label %do.cond, !dbg !376

do.cond:                                          ; preds = %do.end
  %14 = load i8*, i8** %f, align 8, !dbg !377
  %incdec.ptr = getelementptr inbounds i8, i8* %14, i32 1, !dbg !377
  store i8* %incdec.ptr, i8** %f, align 8, !dbg !377
  %15 = load i8, i8* %incdec.ptr, align 1, !dbg !379
  %conv15 = sext i8 %15 to i32, !dbg !379
  %tobool16 = icmp ne i32 %conv15, 0, !dbg !379
  br i1 %tobool16, label %land.rhs, label %land.end, !dbg !380

land.rhs:                                         ; preds = %do.cond
  %16 = load i8*, i8** %f, align 8, !dbg !381
  %17 = load i8, i8* %16, align 1, !dbg !383
  %conv17 = sext i8 %17 to i32, !dbg !383
  %cmp18 = icmp ne i32 37, %conv17, !dbg !384
  br label %land.end

land.end:                                         ; preds = %land.rhs, %do.cond
  %18 = phi i1 [ false, %do.cond ], [ %cmp18, %land.rhs ]
  br i1 %18, label %do.body, label %do.end20, !dbg !385

do.end20:                                         ; preds = %land.end
  br label %while.cond, !dbg !387

if.end21:                                         ; preds = %while.body
  %19 = load i8*, i8** %f, align 8, !dbg !388
  %incdec.ptr22 = getelementptr inbounds i8, i8* %19, i32 1, !dbg !388
  store i8* %incdec.ptr22, i8** %f, align 8, !dbg !388
  %20 = load i8*, i8** %f, align 8, !dbg !389
  %21 = load i8, i8* %20, align 1, !dbg !391
  %conv23 = sext i8 %21 to i32, !dbg !391
  %cmp24 = icmp eq i32 %conv23, 37, !dbg !392
  br i1 %cmp24, label %if.then26, label %if.end38, !dbg !393

if.then26:                                        ; preds = %if.end21
  %22 = load i8*, i8** %f, align 8, !dbg !394
  %incdec.ptr27 = getelementptr inbounds i8, i8* %22, i32 1, !dbg !394
  store i8* %incdec.ptr27, i8** %f, align 8, !dbg !394
  br label %do.body28, !dbg !396

do.body28:                                        ; preds = %if.then26
  %23 = load i32 (i32, %struct._IO_FILE*)*, i32 (i32, %struct._IO_FILE*)** %stream.addr, align 8, !dbg !397
  %24 = load i8*, i8** %data.addr, align 8, !dbg !397
  %25 = bitcast i8* %24 to %struct._IO_FILE*, !dbg !397
  %call29 = call i32 %23(i32 37, %struct._IO_FILE* %25), !dbg !397
  %cmp30 = icmp ne i32 %call29, -1, !dbg !397
  br i1 %cmp30, label %if.then32, label %if.else34, !dbg !397

if.then32:                                        ; preds = %do.body28
  %26 = load i32, i32* %done, align 4, !dbg !401
  %inc33 = add nsw i32 %26, 1, !dbg !401
  store i32 %inc33, i32* %done, align 4, !dbg !401
  br label %if.end35, !dbg !401

if.else34:                                        ; preds = %do.body28
  %27 = load i32, i32* %done, align 4, !dbg !403
  store i32 %27, i32* %retval, align 4, !dbg !403
  br label %return, !dbg !403

if.end35:                                         ; preds = %if.then32
  br label %do.end37, !dbg !405

do.end37:                                         ; preds = %if.end35
  br label %while.cond, !dbg !407

if.end38:                                         ; preds = %if.end21
  %28 = load i8*, i8** %f, align 8, !dbg !408
  %call39 = call i64 @dprintf_DollarString(i8* %28, i8** %f), !dbg !409
  store i64 %call39, i64* %param, align 8, !dbg !410
  %29 = load i64, i64* %param, align 8, !dbg !411
  %tobool40 = icmp ne i64 %29, 0, !dbg !411
  br i1 %tobool40, label %if.else42, label %if.then41, !dbg !413

if.then41:                                        ; preds = %if.end38
  %30 = load i64, i64* %param_num, align 8, !dbg !414
  store i64 %30, i64* %param, align 8, !dbg !415
  br label %if.end43, !dbg !416

if.else42:                                        ; preds = %if.end38
  %31 = load i64, i64* %param, align 8, !dbg !417
  %dec = add nsw i64 %31, -1, !dbg !417
  store i64 %dec, i64* %param, align 8, !dbg !417
  br label %if.end43

if.end43:                                         ; preds = %if.else42, %if.then41
  %32 = load i64, i64* %param_num, align 8, !dbg !418
  %inc44 = add nsw i64 %32, 1, !dbg !418
  store i64 %inc44, i64* %param_num, align 8, !dbg !418
  %33 = load i64, i64* %param, align 8, !dbg !419
  %arrayidx45 = getelementptr inbounds [128 x %struct.va_stack_t], [128 x %struct.va_stack_t]* %vto, i64 0, i64 %33, !dbg !420
  store %struct.va_stack_t* %arrayidx45, %struct.va_stack_t** %p, align 8, !dbg !421
  %34 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !422
  %flags = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %34, i32 0, i32 1, !dbg !424
  %35 = load i32, i32* %flags, align 4, !dbg !424
  %and = and i32 %35, 16384, !dbg !425
  %tobool46 = icmp ne i32 %and, 0, !dbg !425
  br i1 %tobool46, label %if.then47, label %if.else60, !dbg !426

if.then47:                                        ; preds = %if.end43
  %36 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !427
  %width48 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %36, i32 0, i32 2, !dbg !429
  %37 = load i64, i64* %width48, align 8, !dbg !429
  %arrayidx49 = getelementptr inbounds [128 x %struct.va_stack_t], [128 x %struct.va_stack_t]* %vto, i64 0, i64 %37, !dbg !430
  %data50 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx49, i32 0, i32 4, !dbg !431
  %num51 = bitcast %union.anon* %data50 to %union.anon.0*, !dbg !432
  %as_signed = bitcast %union.anon.0* %num51 to i64*, !dbg !433
  %38 = load i64, i64* %as_signed, align 8, !dbg !433
  store i64 %38, i64* %width, align 8, !dbg !434
  %39 = load i64, i64* %param_num, align 8, !dbg !435
  %inc52 = add nsw i64 %39, 1, !dbg !435
  store i64 %inc52, i64* %param_num, align 8, !dbg !435
  %40 = load i64, i64* %width, align 8, !dbg !436
  %cmp53 = icmp slt i64 %40, 0, !dbg !438
  br i1 %cmp53, label %if.then55, label %if.end59, !dbg !439

if.then55:                                        ; preds = %if.then47
  %41 = load i64, i64* %width, align 8, !dbg !440
  %sub = sub nsw i64 0, %41, !dbg !442
  store i64 %sub, i64* %width, align 8, !dbg !443
  %42 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !444
  %flags56 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %42, i32 0, i32 1, !dbg !445
  %43 = load i32, i32* %flags56, align 4, !dbg !446
  %or = or i32 %43, 4, !dbg !446
  store i32 %or, i32* %flags56, align 4, !dbg !446
  %44 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !447
  %flags57 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %44, i32 0, i32 1, !dbg !448
  %45 = load i32, i32* %flags57, align 4, !dbg !449
  %and58 = and i32 %45, -257, !dbg !449
  store i32 %and58, i32* %flags57, align 4, !dbg !449
  br label %if.end59, !dbg !450

if.end59:                                         ; preds = %if.then55, %if.then47
  br label %if.end62, !dbg !451

if.else60:                                        ; preds = %if.end43
  %46 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !452
  %width61 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %46, i32 0, i32 2, !dbg !453
  %47 = load i64, i64* %width61, align 8, !dbg !453
  store i64 %47, i64* %width, align 8, !dbg !454
  br label %if.end62

if.end62:                                         ; preds = %if.else60, %if.end59
  %48 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !455
  %flags63 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %48, i32 0, i32 1, !dbg !457
  %49 = load i32, i32* %flags63, align 4, !dbg !457
  %and64 = and i32 %49, 65536, !dbg !458
  %tobool65 = icmp ne i32 %and64, 0, !dbg !458
  br i1 %tobool65, label %if.then66, label %if.else76, !dbg !459

if.then66:                                        ; preds = %if.end62
  %50 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !460
  %precision = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %50, i32 0, i32 3, !dbg !462
  %51 = load i64, i64* %precision, align 8, !dbg !462
  %arrayidx67 = getelementptr inbounds [128 x %struct.va_stack_t], [128 x %struct.va_stack_t]* %vto, i64 0, i64 %51, !dbg !463
  %data68 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx67, i32 0, i32 4, !dbg !464
  %num69 = bitcast %union.anon* %data68 to %union.anon.0*, !dbg !465
  %as_signed70 = bitcast %union.anon.0* %num69 to i64*, !dbg !466
  %52 = load i64, i64* %as_signed70, align 8, !dbg !466
  store i64 %52, i64* %prec, align 8, !dbg !467
  %53 = load i64, i64* %param_num, align 8, !dbg !468
  %inc71 = add nsw i64 %53, 1, !dbg !468
  store i64 %inc71, i64* %param_num, align 8, !dbg !468
  %54 = load i64, i64* %prec, align 8, !dbg !469
  %cmp72 = icmp slt i64 %54, 0, !dbg !471
  br i1 %cmp72, label %if.then74, label %if.end75, !dbg !472

if.then74:                                        ; preds = %if.then66
  store i64 -1, i64* %prec, align 8, !dbg !473
  br label %if.end75, !dbg !474

if.end75:                                         ; preds = %if.then74, %if.then66
  br label %if.end84, !dbg !475

if.else76:                                        ; preds = %if.end62
  %55 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !476
  %flags77 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %55, i32 0, i32 1, !dbg !478
  %56 = load i32, i32* %flags77, align 4, !dbg !478
  %and78 = and i32 %56, 32768, !dbg !479
  %tobool79 = icmp ne i32 %and78, 0, !dbg !479
  br i1 %tobool79, label %if.then80, label %if.else82, !dbg !480

if.then80:                                        ; preds = %if.else76
  %57 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !481
  %precision81 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %57, i32 0, i32 3, !dbg !482
  %58 = load i64, i64* %precision81, align 8, !dbg !482
  store i64 %58, i64* %prec, align 8, !dbg !483
  br label %if.end83, !dbg !484

if.else82:                                        ; preds = %if.else76
  store i64 -1, i64* %prec, align 8, !dbg !485
  br label %if.end83

if.end83:                                         ; preds = %if.else82, %if.then80
  br label %if.end84

if.end84:                                         ; preds = %if.end83, %if.end75
  %59 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !486
  %flags85 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %59, i32 0, i32 1, !dbg !487
  %60 = load i32, i32* %flags85, align 4, !dbg !487
  %and86 = and i32 %60, 8, !dbg !488
  %tobool87 = icmp ne i32 %and86, 0, !dbg !489
  %cond = select i1 %tobool87, i32 1, i32 0, !dbg !489
  store i32 %cond, i32* %is_alt, align 4, !dbg !490
  %61 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !491
  %type = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %61, i32 0, i32 0, !dbg !492
  %62 = load i32, i32* %type, align 8, !dbg !492
  switch i32 %62, label %sw.default [
    i32 3, label %sw.bb
    i32 1, label %sw.bb414
    i32 2, label %sw.bb536
    i32 7, label %sw.bb606
    i32 4, label %sw.bb755
  ], !dbg !493

sw.bb:                                            ; preds = %if.end84
  %63 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !494
  %data88 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %63, i32 0, i32 4, !dbg !496
  %num89 = bitcast %union.anon* %data88 to %union.anon.0*, !dbg !497
  %as_unsigned = bitcast %union.anon.0* %num89 to i64*, !dbg !498
  %64 = load i64, i64* %as_unsigned, align 8, !dbg !498
  store i64 %64, i64* %num, align 8, !dbg !499
  %65 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !500
  %flags90 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %65, i32 0, i32 1, !dbg !502
  %66 = load i32, i32* %flags90, align 4, !dbg !502
  %and91 = and i32 %66, 131072, !dbg !503
  %tobool92 = icmp ne i32 %and91, 0, !dbg !503
  br i1 %tobool92, label %if.then93, label %if.end147, !dbg !504

if.then93:                                        ; preds = %sw.bb
  %67 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !505
  %flags94 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %67, i32 0, i32 1, !dbg !508
  %68 = load i32, i32* %flags94, align 4, !dbg !508
  %and95 = and i32 %68, 4, !dbg !509
  %tobool96 = icmp ne i32 %and95, 0, !dbg !509
  br i1 %tobool96, label %if.end113, label %if.then97, !dbg !510

if.then97:                                        ; preds = %if.then93
  br label %while.cond98, !dbg !511

while.cond98:                                     ; preds = %do.end112, %if.then97
  %69 = load i64, i64* %width, align 8, !dbg !512
  %dec99 = add nsw i64 %69, -1, !dbg !512
  store i64 %dec99, i64* %width, align 8, !dbg !512
  %cmp100 = icmp sgt i64 %dec99, 0, !dbg !514
  br i1 %cmp100, label %while.body102, label %while.end, !dbg !515

while.body102:                                    ; preds = %while.cond98
  br label %do.body103, !dbg !516

do.body103:                                       ; preds = %while.body102
  %70 = load i32 (i32, %struct._IO_FILE*)*, i32 (i32, %struct._IO_FILE*)** %stream.addr, align 8, !dbg !517
  %71 = load i8*, i8** %data.addr, align 8, !dbg !517
  %72 = bitcast i8* %71 to %struct._IO_FILE*, !dbg !517
  %call104 = call i32 %70(i32 32, %struct._IO_FILE* %72), !dbg !517
  %cmp105 = icmp ne i32 %call104, -1, !dbg !517
  br i1 %cmp105, label %if.then107, label %if.else109, !dbg !517

if.then107:                                       ; preds = %do.body103
  %73 = load i32, i32* %done, align 4, !dbg !521
  %inc108 = add nsw i32 %73, 1, !dbg !521
  store i32 %inc108, i32* %done, align 4, !dbg !521
  br label %if.end110, !dbg !521

if.else109:                                       ; preds = %do.body103
  %74 = load i32, i32* %done, align 4, !dbg !523
  store i32 %74, i32* %retval, align 4, !dbg !523
  br label %return, !dbg !523

if.end110:                                        ; preds = %if.then107
  br label %do.end112, !dbg !525

do.end112:                                        ; preds = %if.end110
  br label %while.cond98, !dbg !527

while.end:                                        ; preds = %while.cond98
  br label %if.end113, !dbg !529

if.end113:                                        ; preds = %while.end, %if.then93
  br label %do.body114, !dbg !531

do.body114:                                       ; preds = %if.end113
  %75 = load i32 (i32, %struct._IO_FILE*)*, i32 (i32, %struct._IO_FILE*)** %stream.addr, align 8, !dbg !532
  %76 = load i64, i64* %num, align 8, !dbg !532
  %conv115 = trunc i64 %76 to i8, !dbg !532
  %conv116 = zext i8 %conv115 to i32, !dbg !532
  %77 = load i8*, i8** %data.addr, align 8, !dbg !532
  %78 = bitcast i8* %77 to %struct._IO_FILE*, !dbg !532
  %call117 = call i32 %75(i32 %conv116, %struct._IO_FILE* %78), !dbg !532
  %cmp118 = icmp ne i32 %call117, -1, !dbg !532
  br i1 %cmp118, label %if.then120, label %if.else122, !dbg !532

if.then120:                                       ; preds = %do.body114
  %79 = load i32, i32* %done, align 4, !dbg !536
  %inc121 = add nsw i32 %79, 1, !dbg !536
  store i32 %inc121, i32* %done, align 4, !dbg !536
  br label %if.end123, !dbg !536

if.else122:                                       ; preds = %do.body114
  %80 = load i32, i32* %done, align 4, !dbg !538
  store i32 %80, i32* %retval, align 4, !dbg !538
  br label %return, !dbg !538

if.end123:                                        ; preds = %if.then120
  br label %do.end125, !dbg !540

do.end125:                                        ; preds = %if.end123
  %81 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !542
  %flags126 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %81, i32 0, i32 1, !dbg !544
  %82 = load i32, i32* %flags126, align 4, !dbg !544
  %and127 = and i32 %82, 4, !dbg !545
  %tobool128 = icmp ne i32 %and127, 0, !dbg !545
  br i1 %tobool128, label %if.then129, label %if.end146, !dbg !546

if.then129:                                       ; preds = %do.end125
  br label %while.cond130, !dbg !547

while.cond130:                                    ; preds = %do.end144, %if.then129
  %83 = load i64, i64* %width, align 8, !dbg !548
  %dec131 = add nsw i64 %83, -1, !dbg !548
  store i64 %dec131, i64* %width, align 8, !dbg !548
  %cmp132 = icmp sgt i64 %dec131, 0, !dbg !550
  br i1 %cmp132, label %while.body134, label %while.end145, !dbg !551

while.body134:                                    ; preds = %while.cond130
  br label %do.body135, !dbg !552

do.body135:                                       ; preds = %while.body134
  %84 = load i32 (i32, %struct._IO_FILE*)*, i32 (i32, %struct._IO_FILE*)** %stream.addr, align 8, !dbg !553
  %85 = load i8*, i8** %data.addr, align 8, !dbg !553
  %86 = bitcast i8* %85 to %struct._IO_FILE*, !dbg !553
  %call136 = call i32 %84(i32 32, %struct._IO_FILE* %86), !dbg !553
  %cmp137 = icmp ne i32 %call136, -1, !dbg !553
  br i1 %cmp137, label %if.then139, label %if.else141, !dbg !553

if.then139:                                       ; preds = %do.body135
  %87 = load i32, i32* %done, align 4, !dbg !557
  %inc140 = add nsw i32 %87, 1, !dbg !557
  store i32 %inc140, i32* %done, align 4, !dbg !557
  br label %if.end142, !dbg !557

if.else141:                                       ; preds = %do.body135
  %88 = load i32, i32* %done, align 4, !dbg !559
  store i32 %88, i32* %retval, align 4, !dbg !559
  br label %return, !dbg !559

if.end142:                                        ; preds = %if.then139
  br label %do.end144, !dbg !561

do.end144:                                        ; preds = %if.end142
  br label %while.cond130, !dbg !563

while.end145:                                     ; preds = %while.cond130
  br label %if.end146, !dbg !565

if.end146:                                        ; preds = %while.end145, %do.end125
  br label %sw.epilog, !dbg !567

if.end147:                                        ; preds = %sw.bb
  %89 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !568
  %flags148 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %89, i32 0, i32 1, !dbg !570
  %90 = load i32, i32* %flags148, align 4, !dbg !570
  %and149 = and i32 %90, 1024, !dbg !571
  %tobool150 = icmp ne i32 %and149, 0, !dbg !571
  br i1 %tobool150, label %if.then151, label %if.else152, !dbg !572

if.then151:                                       ; preds = %if.end147
  store i64 8, i64* %base, align 8, !dbg !573
  br label %unsigned_number, !dbg !575

if.else152:                                       ; preds = %if.end147
  %91 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !576
  %flags153 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %91, i32 0, i32 1, !dbg !578
  %92 = load i32, i32* %flags153, align 4, !dbg !578
  %and154 = and i32 %92, 2048, !dbg !579
  %tobool155 = icmp ne i32 %and154, 0, !dbg !579
  br i1 %tobool155, label %if.then156, label %if.else161, !dbg !580

if.then156:                                       ; preds = %if.else152
  %93 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !581
  %flags157 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %93, i32 0, i32 1, !dbg !583
  %94 = load i32, i32* %flags157, align 4, !dbg !583
  %and158 = and i32 %94, 4096, !dbg !584
  %tobool159 = icmp ne i32 %and158, 0, !dbg !585
  %cond160 = select i1 %tobool159, i8* getelementptr inbounds ([37 x i8], [37 x i8]* @upper_digits, i32 0, i32 0), i8* getelementptr inbounds ([37 x i8], [37 x i8]* @lower_digits, i32 0, i32 0), !dbg !585
  store i8* %cond160, i8** %digits, align 8, !dbg !586
  store i64 16, i64* %base, align 8, !dbg !587
  br label %unsigned_number, !dbg !588

if.else161:                                       ; preds = %if.else152
  %95 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !589
  %flags162 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %95, i32 0, i32 1, !dbg !591
  %96 = load i32, i32* %flags162, align 4, !dbg !591
  %and163 = and i32 %96, 512, !dbg !592
  %tobool164 = icmp ne i32 %and163, 0, !dbg !592
  br i1 %tobool164, label %if.then165, label %if.end166, !dbg !593

if.then165:                                       ; preds = %if.else161
  store i64 10, i64* %base, align 8, !dbg !594
  br label %unsigned_number, !dbg !596

if.end166:                                        ; preds = %if.else161
  br label %if.end167

if.end167:                                        ; preds = %if.end166
  br label %if.end168

if.end168:                                        ; preds = %if.end167
  store i64 10, i64* %base, align 8, !dbg !597
  %97 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !598
  %data169 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %97, i32 0, i32 4, !dbg !599
  %num170 = bitcast %union.anon* %data169 to %union.anon.0*, !dbg !600
  %as_signed171 = bitcast %union.anon.0* %num170 to i64*, !dbg !601
  %98 = load i64, i64* %as_signed171, align 8, !dbg !601
  %cmp172 = icmp slt i64 %98, 0, !dbg !602
  %cond174 = select i1 %cmp172, i32 1, i32 0, !dbg !603
  store i32 %cond174, i32* %is_neg, align 4, !dbg !604
  %99 = load i32, i32* %is_neg, align 4, !dbg !605
  %tobool175 = icmp ne i32 %99, 0, !dbg !605
  br i1 %tobool175, label %if.then176, label %if.end182, !dbg !607

if.then176:                                       ; preds = %if.end168
  %100 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !608
  %data177 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %100, i32 0, i32 4, !dbg !610
  %num178 = bitcast %union.anon* %data177 to %union.anon.0*, !dbg !611
  %as_signed179 = bitcast %union.anon.0* %num178 to i64*, !dbg !612
  %101 = load i64, i64* %as_signed179, align 8, !dbg !612
  %add = add nsw i64 %101, 1, !dbg !613
  store i64 %add, i64* %signed_num, align 8, !dbg !614
  %102 = load i64, i64* %signed_num, align 8, !dbg !615
  %sub180 = sub nsw i64 0, %102, !dbg !616
  store i64 %sub180, i64* %signed_num, align 8, !dbg !617
  %103 = load i64, i64* %signed_num, align 8, !dbg !618
  store i64 %103, i64* %num, align 8, !dbg !619
  %104 = load i64, i64* %num, align 8, !dbg !620
  %add181 = add i64 %104, 1, !dbg !620
  store i64 %add181, i64* %num, align 8, !dbg !620
  br label %if.end182, !dbg !621

if.end182:                                        ; preds = %if.then176, %if.end168
  br label %number, !dbg !622

unsigned_number:                                  ; preds = %if.then165, %if.then156, %if.then151
  store i32 0, i32* %is_neg, align 4, !dbg !623
  br label %number, !dbg !624

number:                                           ; preds = %if.then541, %unsigned_number, %if.end182
  %105 = load i64, i64* %prec, align 8, !dbg !625
  %cmp183 = icmp eq i64 %105, -1, !dbg !627
  br i1 %cmp183, label %if.then185, label %if.end186, !dbg !628

if.then185:                                       ; preds = %number
  store i64 1, i64* %prec, align 8, !dbg !629
  br label %if.end186, !dbg !630

if.end186:                                        ; preds = %if.then185, %number
  %106 = load i8*, i8** %workend, align 8, !dbg !631
  store i8* %106, i8** %w, align 8, !dbg !632
  br label %while.cond187, !dbg !633

while.cond187:                                    ; preds = %while.body190, %if.end186
  %107 = load i64, i64* %num, align 8, !dbg !634
  %cmp188 = icmp ugt i64 %107, 0, !dbg !636
  br i1 %cmp188, label %while.body190, label %while.end193, !dbg !637

while.body190:                                    ; preds = %while.cond187
  %108 = load i64, i64* %num, align 8, !dbg !638
  %109 = load i64, i64* %base, align 8, !dbg !640
  %rem = urem i64 %108, %109, !dbg !641
  %110 = load i8*, i8** %digits, align 8, !dbg !642
  %arrayidx191 = getelementptr inbounds i8, i8* %110, i64 %rem, !dbg !642
  %111 = load i8, i8* %arrayidx191, align 1, !dbg !642
  %112 = load i8*, i8** %w, align 8, !dbg !643
  %incdec.ptr192 = getelementptr inbounds i8, i8* %112, i32 -1, !dbg !643
  store i8* %incdec.ptr192, i8** %w, align 8, !dbg !643
  store i8 %111, i8* %112, align 1, !dbg !644
  %113 = load i64, i64* %base, align 8, !dbg !645
  %114 = load i64, i64* %num, align 8, !dbg !646
  %div = udiv i64 %114, %113, !dbg !646
  store i64 %div, i64* %num, align 8, !dbg !646
  br label %while.cond187, !dbg !647

while.end193:                                     ; preds = %while.cond187
  %115 = load i8*, i8** %workend, align 8, !dbg !649
  %116 = load i8*, i8** %w, align 8, !dbg !650
  %sub.ptr.lhs.cast = ptrtoint i8* %115 to i64, !dbg !651
  %sub.ptr.rhs.cast = ptrtoint i8* %116 to i64, !dbg !651
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !651
  %117 = load i64, i64* %width, align 8, !dbg !652
  %sub194 = sub nsw i64 %117, %sub.ptr.sub, !dbg !652
  store i64 %sub194, i64* %width, align 8, !dbg !652
  %118 = load i8*, i8** %workend, align 8, !dbg !653
  %119 = load i8*, i8** %w, align 8, !dbg !654
  %sub.ptr.lhs.cast195 = ptrtoint i8* %118 to i64, !dbg !655
  %sub.ptr.rhs.cast196 = ptrtoint i8* %119 to i64, !dbg !655
  %sub.ptr.sub197 = sub i64 %sub.ptr.lhs.cast195, %sub.ptr.rhs.cast196, !dbg !655
  %120 = load i64, i64* %prec, align 8, !dbg !656
  %sub198 = sub nsw i64 %120, %sub.ptr.sub197, !dbg !656
  store i64 %sub198, i64* %prec, align 8, !dbg !656
  %121 = load i32, i32* %is_alt, align 4, !dbg !657
  %tobool199 = icmp ne i32 %121, 0, !dbg !657
  br i1 %tobool199, label %land.lhs.true, label %if.end208, !dbg !659

land.lhs.true:                                    ; preds = %while.end193
  %122 = load i64, i64* %base, align 8, !dbg !660
  %cmp200 = icmp eq i64 %122, 8, !dbg !662
  br i1 %cmp200, label %land.lhs.true202, label %if.end208, !dbg !663

land.lhs.true202:                                 ; preds = %land.lhs.true
  %123 = load i64, i64* %prec, align 8, !dbg !664
  %cmp203 = icmp sle i64 %123, 0, !dbg !666
  br i1 %cmp203, label %if.then205, label %if.end208, !dbg !667

if.then205:                                       ; preds = %land.lhs.true202
  %124 = load i8*, i8** %w, align 8, !dbg !668
  %incdec.ptr206 = getelementptr inbounds i8, i8* %124, i32 -1, !dbg !668
  store i8* %incdec.ptr206, i8** %w, align 8, !dbg !668
  store i8 48, i8* %124, align 1, !dbg !670
  %125 = load i64, i64* %width, align 8, !dbg !671
  %dec207 = add nsw i64 %125, -1, !dbg !671
  store i64 %dec207, i64* %width, align 8, !dbg !671
  br label %if.end208, !dbg !672

if.end208:                                        ; preds = %if.then205, %land.lhs.true202, %land.lhs.true, %while.end193
  %126 = load i64, i64* %prec, align 8, !dbg !673
  %cmp209 = icmp sgt i64 %126, 0, !dbg !675
  br i1 %cmp209, label %if.then211, label %if.end220, !dbg !676

if.then211:                                       ; preds = %if.end208
  %127 = load i64, i64* %prec, align 8, !dbg !677
  %128 = load i64, i64* %width, align 8, !dbg !679
  %sub212 = sub nsw i64 %128, %127, !dbg !679
  store i64 %sub212, i64* %width, align 8, !dbg !679
  br label %while.cond213, !dbg !680

while.cond213:                                    ; preds = %while.body217, %if.then211
  %129 = load i64, i64* %prec, align 8, !dbg !681
  %dec214 = add nsw i64 %129, -1, !dbg !681
  store i64 %dec214, i64* %prec, align 8, !dbg !681
  %cmp215 = icmp sgt i64 %129, 0, !dbg !683
  br i1 %cmp215, label %while.body217, label %while.end219, !dbg !684

while.body217:                                    ; preds = %while.cond213
  %130 = load i8*, i8** %w, align 8, !dbg !685
  %incdec.ptr218 = getelementptr inbounds i8, i8* %130, i32 -1, !dbg !685
  store i8* %incdec.ptr218, i8** %w, align 8, !dbg !685
  store i8 48, i8* %130, align 1, !dbg !686
  br label %while.cond213, !dbg !687

while.end219:                                     ; preds = %while.cond213
  br label %if.end220, !dbg !689

if.end220:                                        ; preds = %while.end219, %if.end208
  %131 = load i32, i32* %is_alt, align 4, !dbg !690
  %tobool221 = icmp ne i32 %131, 0, !dbg !690
  br i1 %tobool221, label %land.lhs.true222, label %if.end227, !dbg !692

land.lhs.true222:                                 ; preds = %if.end220
  %132 = load i64, i64* %base, align 8, !dbg !693
  %cmp223 = icmp eq i64 %132, 16, !dbg !695
  br i1 %cmp223, label %if.then225, label %if.end227, !dbg !696

if.then225:                                       ; preds = %land.lhs.true222
  %133 = load i64, i64* %width, align 8, !dbg !697
  %sub226 = sub nsw i64 %133, 2, !dbg !697
  store i64 %sub226, i64* %width, align 8, !dbg !697
  br label %if.end227, !dbg !698

if.end227:                                        ; preds = %if.then225, %land.lhs.true222, %if.end220
  %134 = load i32, i32* %is_neg, align 4, !dbg !699
  %tobool228 = icmp ne i32 %134, 0, !dbg !699
  br i1 %tobool228, label %if.then236, label %lor.lhs.false, !dbg !701

lor.lhs.false:                                    ; preds = %if.end227
  %135 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !702
  %flags229 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %135, i32 0, i32 1, !dbg !704
  %136 = load i32, i32* %flags229, align 4, !dbg !704
  %and230 = and i32 %136, 2, !dbg !705
  %tobool231 = icmp ne i32 %and230, 0, !dbg !705
  br i1 %tobool231, label %if.then236, label %lor.lhs.false232, !dbg !706

lor.lhs.false232:                                 ; preds = %lor.lhs.false
  %137 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !707
  %flags233 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %137, i32 0, i32 1, !dbg !709
  %138 = load i32, i32* %flags233, align 4, !dbg !709
  %and234 = and i32 %138, 1, !dbg !710
  %tobool235 = icmp ne i32 %and234, 0, !dbg !710
  br i1 %tobool235, label %if.then236, label %if.end238, !dbg !711

if.then236:                                       ; preds = %lor.lhs.false232, %lor.lhs.false, %if.end227
  %139 = load i64, i64* %width, align 8, !dbg !712
  %dec237 = add nsw i64 %139, -1, !dbg !712
  store i64 %dec237, i64* %width, align 8, !dbg !712
  br label %if.end238, !dbg !712

if.end238:                                        ; preds = %if.then236, %lor.lhs.false232
  %140 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !713
  %flags239 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %140, i32 0, i32 1, !dbg !715
  %141 = load i32, i32* %flags239, align 4, !dbg !715
  %and240 = and i32 %141, 4, !dbg !716
  %tobool241 = icmp ne i32 %and240, 0, !dbg !716
  br i1 %tobool241, label %if.end263, label %land.lhs.true242, !dbg !717

land.lhs.true242:                                 ; preds = %if.end238
  %142 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !718
  %flags243 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %142, i32 0, i32 1, !dbg !720
  %143 = load i32, i32* %flags243, align 4, !dbg !720
  %and244 = and i32 %143, 256, !dbg !721
  %tobool245 = icmp ne i32 %and244, 0, !dbg !721
  br i1 %tobool245, label %if.end263, label %if.then246, !dbg !722

if.then246:                                       ; preds = %land.lhs.true242
  br label %while.cond247, !dbg !723

while.cond247:                                    ; preds = %do.end261, %if.then246
  %144 = load i64, i64* %width, align 8, !dbg !724
  %dec248 = add nsw i64 %144, -1, !dbg !724
  store i64 %dec248, i64* %width, align 8, !dbg !724
  %cmp249 = icmp sgt i64 %144, 0, !dbg !725
  br i1 %cmp249, label %while.body251, label %while.end262, !dbg !726

while.body251:                                    ; preds = %while.cond247
  br label %do.body252, !dbg !727

do.body252:                                       ; preds = %while.body251
  %145 = load i32 (i32, %struct._IO_FILE*)*, i32 (i32, %struct._IO_FILE*)** %stream.addr, align 8, !dbg !728
  %146 = load i8*, i8** %data.addr, align 8, !dbg !728
  %147 = bitcast i8* %146 to %struct._IO_FILE*, !dbg !728
  %call253 = call i32 %145(i32 32, %struct._IO_FILE* %147), !dbg !728
  %cmp254 = icmp ne i32 %call253, -1, !dbg !728
  br i1 %cmp254, label %if.then256, label %if.else258, !dbg !728

if.then256:                                       ; preds = %do.body252
  %148 = load i32, i32* %done, align 4, !dbg !732
  %inc257 = add nsw i32 %148, 1, !dbg !732
  store i32 %inc257, i32* %done, align 4, !dbg !732
  br label %if.end259, !dbg !732

if.else258:                                       ; preds = %do.body252
  %149 = load i32, i32* %done, align 4, !dbg !734
  store i32 %149, i32* %retval, align 4, !dbg !734
  br label %return, !dbg !734

if.end259:                                        ; preds = %if.then256
  br label %do.end261, !dbg !736

do.end261:                                        ; preds = %if.end259
  br label %while.cond247, !dbg !738

while.end262:                                     ; preds = %while.cond247
  br label %if.end263, !dbg !740

if.end263:                                        ; preds = %while.end262, %land.lhs.true242, %if.end238
  %150 = load i32, i32* %is_neg, align 4, !dbg !742
  %tobool264 = icmp ne i32 %150, 0, !dbg !742
  br i1 %tobool264, label %if.then265, label %if.else276, !dbg !744

if.then265:                                       ; preds = %if.end263
  br label %do.body266, !dbg !745

do.body266:                                       ; preds = %if.then265
  %151 = load i32 (i32, %struct._IO_FILE*)*, i32 (i32, %struct._IO_FILE*)** %stream.addr, align 8, !dbg !746
  %152 = load i8*, i8** %data.addr, align 8, !dbg !746
  %153 = bitcast i8* %152 to %struct._IO_FILE*, !dbg !746
  %call267 = call i32 %151(i32 45, %struct._IO_FILE* %153), !dbg !746
  %cmp268 = icmp ne i32 %call267, -1, !dbg !746
  br i1 %cmp268, label %if.then270, label %if.else272, !dbg !746

if.then270:                                       ; preds = %do.body266
  %154 = load i32, i32* %done, align 4, !dbg !750
  %inc271 = add nsw i32 %154, 1, !dbg !750
  store i32 %inc271, i32* %done, align 4, !dbg !750
  br label %if.end273, !dbg !750

if.else272:                                       ; preds = %do.body266
  %155 = load i32, i32* %done, align 4, !dbg !752
  store i32 %155, i32* %retval, align 4, !dbg !752
  br label %return, !dbg !752

if.end273:                                        ; preds = %if.then270
  br label %do.end275, !dbg !754

do.end275:                                        ; preds = %if.end273
  br label %if.end308, !dbg !756

if.else276:                                       ; preds = %if.end263
  %156 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !758
  %flags277 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %156, i32 0, i32 1, !dbg !760
  %157 = load i32, i32* %flags277, align 4, !dbg !760
  %and278 = and i32 %157, 2, !dbg !761
  %tobool279 = icmp ne i32 %and278, 0, !dbg !761
  br i1 %tobool279, label %if.then280, label %if.else291, !dbg !762

if.then280:                                       ; preds = %if.else276
  br label %do.body281, !dbg !763

do.body281:                                       ; preds = %if.then280
  %158 = load i32 (i32, %struct._IO_FILE*)*, i32 (i32, %struct._IO_FILE*)** %stream.addr, align 8, !dbg !764
  %159 = load i8*, i8** %data.addr, align 8, !dbg !764
  %160 = bitcast i8* %159 to %struct._IO_FILE*, !dbg !764
  %call282 = call i32 %158(i32 43, %struct._IO_FILE* %160), !dbg !764
  %cmp283 = icmp ne i32 %call282, -1, !dbg !764
  br i1 %cmp283, label %if.then285, label %if.else287, !dbg !764

if.then285:                                       ; preds = %do.body281
  %161 = load i32, i32* %done, align 4, !dbg !768
  %inc286 = add nsw i32 %161, 1, !dbg !768
  store i32 %inc286, i32* %done, align 4, !dbg !768
  br label %if.end288, !dbg !768

if.else287:                                       ; preds = %do.body281
  %162 = load i32, i32* %done, align 4, !dbg !770
  store i32 %162, i32* %retval, align 4, !dbg !770
  br label %return, !dbg !770

if.end288:                                        ; preds = %if.then285
  br label %do.end290, !dbg !772

do.end290:                                        ; preds = %if.end288
  br label %if.end307, !dbg !774

if.else291:                                       ; preds = %if.else276
  %163 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !776
  %flags292 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %163, i32 0, i32 1, !dbg !778
  %164 = load i32, i32* %flags292, align 4, !dbg !778
  %and293 = and i32 %164, 1, !dbg !779
  %tobool294 = icmp ne i32 %and293, 0, !dbg !779
  br i1 %tobool294, label %if.then295, label %if.end306, !dbg !780

if.then295:                                       ; preds = %if.else291
  br label %do.body296, !dbg !781

do.body296:                                       ; preds = %if.then295
  %165 = load i32 (i32, %struct._IO_FILE*)*, i32 (i32, %struct._IO_FILE*)** %stream.addr, align 8, !dbg !782
  %166 = load i8*, i8** %data.addr, align 8, !dbg !782
  %167 = bitcast i8* %166 to %struct._IO_FILE*, !dbg !782
  %call297 = call i32 %165(i32 32, %struct._IO_FILE* %167), !dbg !782
  %cmp298 = icmp ne i32 %call297, -1, !dbg !782
  br i1 %cmp298, label %if.then300, label %if.else302, !dbg !782

if.then300:                                       ; preds = %do.body296
  %168 = load i32, i32* %done, align 4, !dbg !786
  %inc301 = add nsw i32 %168, 1, !dbg !786
  store i32 %inc301, i32* %done, align 4, !dbg !786
  br label %if.end303, !dbg !786

if.else302:                                       ; preds = %do.body296
  %169 = load i32, i32* %done, align 4, !dbg !788
  store i32 %169, i32* %retval, align 4, !dbg !788
  br label %return, !dbg !788

if.end303:                                        ; preds = %if.then300
  br label %do.end305, !dbg !790

do.end305:                                        ; preds = %if.end303
  br label %if.end306, !dbg !792

if.end306:                                        ; preds = %do.end305, %if.else291
  br label %if.end307

if.end307:                                        ; preds = %if.end306, %do.end290
  br label %if.end308

if.end308:                                        ; preds = %if.end307, %do.end275
  %170 = load i32, i32* %is_alt, align 4, !dbg !794
  %tobool309 = icmp ne i32 %170, 0, !dbg !794
  br i1 %tobool309, label %land.lhs.true310, label %if.end350, !dbg !796

land.lhs.true310:                                 ; preds = %if.end308
  %171 = load i64, i64* %base, align 8, !dbg !797
  %cmp311 = icmp eq i64 %171, 16, !dbg !799
  br i1 %cmp311, label %if.then313, label %if.end350, !dbg !800

if.then313:                                       ; preds = %land.lhs.true310
  br label %do.body314, !dbg !801

do.body314:                                       ; preds = %if.then313
  %172 = load i32 (i32, %struct._IO_FILE*)*, i32 (i32, %struct._IO_FILE*)** %stream.addr, align 8, !dbg !803
  %173 = load i8*, i8** %data.addr, align 8, !dbg !803
  %174 = bitcast i8* %173 to %struct._IO_FILE*, !dbg !803
  %call315 = call i32 %172(i32 48, %struct._IO_FILE* %174), !dbg !803
  %cmp316 = icmp ne i32 %call315, -1, !dbg !803
  br i1 %cmp316, label %if.then318, label %if.else320, !dbg !803

if.then318:                                       ; preds = %do.body314
  %175 = load i32, i32* %done, align 4, !dbg !807
  %inc319 = add nsw i32 %175, 1, !dbg !807
  store i32 %inc319, i32* %done, align 4, !dbg !807
  br label %if.end321, !dbg !807

if.else320:                                       ; preds = %do.body314
  %176 = load i32, i32* %done, align 4, !dbg !809
  store i32 %176, i32* %retval, align 4, !dbg !809
  br label %return, !dbg !809

if.end321:                                        ; preds = %if.then318
  br label %do.end323, !dbg !811

do.end323:                                        ; preds = %if.end321
  %177 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !813
  %flags324 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %177, i32 0, i32 1, !dbg !815
  %178 = load i32, i32* %flags324, align 4, !dbg !815
  %and325 = and i32 %178, 4096, !dbg !816
  %tobool326 = icmp ne i32 %and325, 0, !dbg !816
  br i1 %tobool326, label %if.then327, label %if.else338, !dbg !817

if.then327:                                       ; preds = %do.end323
  br label %do.body328, !dbg !818

do.body328:                                       ; preds = %if.then327
  %179 = load i32 (i32, %struct._IO_FILE*)*, i32 (i32, %struct._IO_FILE*)** %stream.addr, align 8, !dbg !819
  %180 = load i8*, i8** %data.addr, align 8, !dbg !819
  %181 = bitcast i8* %180 to %struct._IO_FILE*, !dbg !819
  %call329 = call i32 %179(i32 88, %struct._IO_FILE* %181), !dbg !819
  %cmp330 = icmp ne i32 %call329, -1, !dbg !819
  br i1 %cmp330, label %if.then332, label %if.else334, !dbg !819

if.then332:                                       ; preds = %do.body328
  %182 = load i32, i32* %done, align 4, !dbg !823
  %inc333 = add nsw i32 %182, 1, !dbg !823
  store i32 %inc333, i32* %done, align 4, !dbg !823
  br label %if.end335, !dbg !823

if.else334:                                       ; preds = %do.body328
  %183 = load i32, i32* %done, align 4, !dbg !825
  store i32 %183, i32* %retval, align 4, !dbg !825
  br label %return, !dbg !825

if.end335:                                        ; preds = %if.then332
  br label %do.end337, !dbg !827

do.end337:                                        ; preds = %if.end335
  br label %if.end349, !dbg !829

if.else338:                                       ; preds = %do.end323
  br label %do.body339, !dbg !831

do.body339:                                       ; preds = %if.else338
  %184 = load i32 (i32, %struct._IO_FILE*)*, i32 (i32, %struct._IO_FILE*)** %stream.addr, align 8, !dbg !832
  %185 = load i8*, i8** %data.addr, align 8, !dbg !832
  %186 = bitcast i8* %185 to %struct._IO_FILE*, !dbg !832
  %call340 = call i32 %184(i32 120, %struct._IO_FILE* %186), !dbg !832
  %cmp341 = icmp ne i32 %call340, -1, !dbg !832
  br i1 %cmp341, label %if.then343, label %if.else345, !dbg !832

if.then343:                                       ; preds = %do.body339
  %187 = load i32, i32* %done, align 4, !dbg !836
  %inc344 = add nsw i32 %187, 1, !dbg !836
  store i32 %inc344, i32* %done, align 4, !dbg !836
  br label %if.end346, !dbg !836

if.else345:                                       ; preds = %do.body339
  %188 = load i32, i32* %done, align 4, !dbg !838
  store i32 %188, i32* %retval, align 4, !dbg !838
  br label %return, !dbg !838

if.end346:                                        ; preds = %if.then343
  br label %do.end348, !dbg !840

do.end348:                                        ; preds = %if.end346
  br label %if.end349

if.end349:                                        ; preds = %do.end348, %do.end337
  br label %if.end350, !dbg !842

if.end350:                                        ; preds = %if.end349, %land.lhs.true310, %if.end308
  %189 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !843
  %flags351 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %189, i32 0, i32 1, !dbg !845
  %190 = load i32, i32* %flags351, align 4, !dbg !845
  %and352 = and i32 %190, 4, !dbg !846
  %tobool353 = icmp ne i32 %and352, 0, !dbg !846
  br i1 %tobool353, label %if.end375, label %land.lhs.true354, !dbg !847

land.lhs.true354:                                 ; preds = %if.end350
  %191 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !848
  %flags355 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %191, i32 0, i32 1, !dbg !850
  %192 = load i32, i32* %flags355, align 4, !dbg !850
  %and356 = and i32 %192, 256, !dbg !851
  %tobool357 = icmp ne i32 %and356, 0, !dbg !851
  br i1 %tobool357, label %if.then358, label %if.end375, !dbg !852

if.then358:                                       ; preds = %land.lhs.true354
  br label %while.cond359, !dbg !853

while.cond359:                                    ; preds = %do.end373, %if.then358
  %193 = load i64, i64* %width, align 8, !dbg !854
  %dec360 = add nsw i64 %193, -1, !dbg !854
  store i64 %dec360, i64* %width, align 8, !dbg !854
  %cmp361 = icmp sgt i64 %193, 0, !dbg !855
  br i1 %cmp361, label %while.body363, label %while.end374, !dbg !856

while.body363:                                    ; preds = %while.cond359
  br label %do.body364, !dbg !857

do.body364:                                       ; preds = %while.body363
  %194 = load i32 (i32, %struct._IO_FILE*)*, i32 (i32, %struct._IO_FILE*)** %stream.addr, align 8, !dbg !858
  %195 = load i8*, i8** %data.addr, align 8, !dbg !858
  %196 = bitcast i8* %195 to %struct._IO_FILE*, !dbg !858
  %call365 = call i32 %194(i32 48, %struct._IO_FILE* %196), !dbg !858
  %cmp366 = icmp ne i32 %call365, -1, !dbg !858
  br i1 %cmp366, label %if.then368, label %if.else370, !dbg !858

if.then368:                                       ; preds = %do.body364
  %197 = load i32, i32* %done, align 4, !dbg !862
  %inc369 = add nsw i32 %197, 1, !dbg !862
  store i32 %inc369, i32* %done, align 4, !dbg !862
  br label %if.end371, !dbg !862

if.else370:                                       ; preds = %do.body364
  %198 = load i32, i32* %done, align 4, !dbg !864
  store i32 %198, i32* %retval, align 4, !dbg !864
  br label %return, !dbg !864

if.end371:                                        ; preds = %if.then368
  br label %do.end373, !dbg !866

do.end373:                                        ; preds = %if.end371
  br label %while.cond359, !dbg !868

while.end374:                                     ; preds = %while.cond359
  br label %if.end375, !dbg !870

if.end375:                                        ; preds = %while.end374, %land.lhs.true354, %if.end350
  br label %while.cond376, !dbg !872

while.cond376:                                    ; preds = %do.end391, %if.end375
  %199 = load i8*, i8** %w, align 8, !dbg !873
  %incdec.ptr377 = getelementptr inbounds i8, i8* %199, i32 1, !dbg !873
  store i8* %incdec.ptr377, i8** %w, align 8, !dbg !873
  %200 = load i8*, i8** %workend, align 8, !dbg !874
  %cmp378 = icmp ule i8* %incdec.ptr377, %200, !dbg !875
  br i1 %cmp378, label %while.body380, label %while.end392, !dbg !876

while.body380:                                    ; preds = %while.cond376
  br label %do.body381, !dbg !877

do.body381:                                       ; preds = %while.body380
  %201 = load i32 (i32, %struct._IO_FILE*)*, i32 (i32, %struct._IO_FILE*)** %stream.addr, align 8, !dbg !879
  %202 = load i8*, i8** %w, align 8, !dbg !879
  %203 = load i8, i8* %202, align 1, !dbg !879
  %conv382 = zext i8 %203 to i32, !dbg !879
  %204 = load i8*, i8** %data.addr, align 8, !dbg !879
  %205 = bitcast i8* %204 to %struct._IO_FILE*, !dbg !879
  %call383 = call i32 %201(i32 %conv382, %struct._IO_FILE* %205), !dbg !879
  %cmp384 = icmp ne i32 %call383, -1, !dbg !879
  br i1 %cmp384, label %if.then386, label %if.else388, !dbg !879

if.then386:                                       ; preds = %do.body381
  %206 = load i32, i32* %done, align 4, !dbg !883
  %inc387 = add nsw i32 %206, 1, !dbg !883
  store i32 %inc387, i32* %done, align 4, !dbg !883
  br label %if.end389, !dbg !883

if.else388:                                       ; preds = %do.body381
  %207 = load i32, i32* %done, align 4, !dbg !885
  store i32 %207, i32* %retval, align 4, !dbg !885
  br label %return, !dbg !885

if.end389:                                        ; preds = %if.then386
  br label %do.end391, !dbg !887

do.end391:                                        ; preds = %if.end389
  br label %while.cond376, !dbg !889

while.end392:                                     ; preds = %while.cond376
  %208 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !890
  %flags393 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %208, i32 0, i32 1, !dbg !892
  %209 = load i32, i32* %flags393, align 4, !dbg !892
  %and394 = and i32 %209, 4, !dbg !893
  %tobool395 = icmp ne i32 %and394, 0, !dbg !893
  br i1 %tobool395, label %if.then396, label %if.end413, !dbg !894

if.then396:                                       ; preds = %while.end392
  br label %while.cond397, !dbg !895

while.cond397:                                    ; preds = %do.end411, %if.then396
  %210 = load i64, i64* %width, align 8, !dbg !896
  %dec398 = add nsw i64 %210, -1, !dbg !896
  store i64 %dec398, i64* %width, align 8, !dbg !896
  %cmp399 = icmp sgt i64 %210, 0, !dbg !898
  br i1 %cmp399, label %while.body401, label %while.end412, !dbg !899

while.body401:                                    ; preds = %while.cond397
  br label %do.body402, !dbg !900

do.body402:                                       ; preds = %while.body401
  %211 = load i32 (i32, %struct._IO_FILE*)*, i32 (i32, %struct._IO_FILE*)** %stream.addr, align 8, !dbg !901
  %212 = load i8*, i8** %data.addr, align 8, !dbg !901
  %213 = bitcast i8* %212 to %struct._IO_FILE*, !dbg !901
  %call403 = call i32 %211(i32 32, %struct._IO_FILE* %213), !dbg !901
  %cmp404 = icmp ne i32 %call403, -1, !dbg !901
  br i1 %cmp404, label %if.then406, label %if.else408, !dbg !901

if.then406:                                       ; preds = %do.body402
  %214 = load i32, i32* %done, align 4, !dbg !905
  %inc407 = add nsw i32 %214, 1, !dbg !905
  store i32 %inc407, i32* %done, align 4, !dbg !905
  br label %if.end409, !dbg !905

if.else408:                                       ; preds = %do.body402
  %215 = load i32, i32* %done, align 4, !dbg !907
  store i32 %215, i32* %retval, align 4, !dbg !907
  br label %return, !dbg !907

if.end409:                                        ; preds = %if.then406
  br label %do.end411, !dbg !909

do.end411:                                        ; preds = %if.end409
  br label %while.cond397, !dbg !911

while.end412:                                     ; preds = %while.cond397
  br label %if.end413, !dbg !913

if.end413:                                        ; preds = %while.end412, %while.end392
  br label %sw.epilog, !dbg !915

sw.bb414:                                         ; preds = %if.end84
  call void @llvm.dbg.declare(metadata i8** %str, metadata !916, metadata !236), !dbg !918
  call void @llvm.dbg.declare(metadata i64* %len, metadata !919, metadata !236), !dbg !920
  %216 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !921
  %data415 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %216, i32 0, i32 4, !dbg !922
  %str416 = bitcast %union.anon* %data415 to i8**, !dbg !923
  %217 = load i8*, i8** %str416, align 8, !dbg !923
  store i8* %217, i8** %str, align 8, !dbg !924
  %218 = load i8*, i8** %str, align 8, !dbg !925
  %cmp417 = icmp eq i8* %218, null, !dbg !927
  br i1 %cmp417, label %if.then419, label %if.else430, !dbg !928

if.then419:                                       ; preds = %sw.bb414
  %219 = load i64, i64* %prec, align 8, !dbg !929
  %cmp420 = icmp eq i64 %219, -1, !dbg !932
  br i1 %cmp420, label %if.then425, label %lor.lhs.false422, !dbg !933

lor.lhs.false422:                                 ; preds = %if.then419
  %220 = load i64, i64* %prec, align 8, !dbg !934
  %cmp423 = icmp sge i64 %220, 5, !dbg !936
  br i1 %cmp423, label %if.then425, label %if.else428, !dbg !937

if.then425:                                       ; preds = %lor.lhs.false422, %if.then419
  store i8* getelementptr inbounds ([6 x i8], [6 x i8]* @dprintf_formatf.null, i32 0, i32 0), i8** %str, align 8, !dbg !938
  store i64 5, i64* %len, align 8, !dbg !940
  %221 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !941
  %flags426 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %221, i32 0, i32 1, !dbg !942
  %222 = load i32, i32* %flags426, align 4, !dbg !943
  %and427 = and i32 %222, -9, !dbg !943
  store i32 %and427, i32* %flags426, align 4, !dbg !943
  br label %if.end429, !dbg !944

if.else428:                                       ; preds = %lor.lhs.false422
  store i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str, i32 0, i32 0), i8** %str, align 8, !dbg !945
  store i64 0, i64* %len, align 8, !dbg !947
  br label %if.end429

if.end429:                                        ; preds = %if.else428, %if.then425
  br label %if.end437, !dbg !948

if.else430:                                       ; preds = %sw.bb414
  %223 = load i64, i64* %prec, align 8, !dbg !949
  %cmp431 = icmp ne i64 %223, -1, !dbg !951
  br i1 %cmp431, label %if.then433, label %if.else434, !dbg !952

if.then433:                                       ; preds = %if.else430
  %224 = load i64, i64* %prec, align 8, !dbg !953
  store i64 %224, i64* %len, align 8, !dbg !954
  br label %if.end436, !dbg !955

if.else434:                                       ; preds = %if.else430
  %225 = load i8*, i8** %str, align 8, !dbg !956
  %call435 = call i64 @strlen(i8* %225) #8, !dbg !957
  store i64 %call435, i64* %len, align 8, !dbg !958
  br label %if.end436

if.end436:                                        ; preds = %if.else434, %if.then433
  br label %if.end437

if.end437:                                        ; preds = %if.end436, %if.end429
  %226 = load i64, i64* %len, align 8, !dbg !959
  %cmp438 = icmp ugt i64 %226, 9223372036854775807, !dbg !960
  br i1 %cmp438, label %cond.true, label %cond.false, !dbg !961

cond.true:                                        ; preds = %if.end437
  br label %cond.end, !dbg !962

cond.false:                                       ; preds = %if.end437
  %227 = load i64, i64* %len, align 8, !dbg !964
  br label %cond.end, !dbg !966

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond440 = phi i64 [ 9223372036854775807, %cond.true ], [ %227, %cond.false ], !dbg !967
  %228 = load i64, i64* %width, align 8, !dbg !969
  %sub441 = sub nsw i64 %228, %cond440, !dbg !969
  store i64 %sub441, i64* %width, align 8, !dbg !969
  %229 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !970
  %flags442 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %229, i32 0, i32 1, !dbg !972
  %230 = load i32, i32* %flags442, align 4, !dbg !972
  %and443 = and i32 %230, 8, !dbg !973
  %tobool444 = icmp ne i32 %and443, 0, !dbg !973
  br i1 %tobool444, label %if.then445, label %if.end456, !dbg !974

if.then445:                                       ; preds = %cond.end
  br label %do.body446, !dbg !975

do.body446:                                       ; preds = %if.then445
  %231 = load i32 (i32, %struct._IO_FILE*)*, i32 (i32, %struct._IO_FILE*)** %stream.addr, align 8, !dbg !976
  %232 = load i8*, i8** %data.addr, align 8, !dbg !976
  %233 = bitcast i8* %232 to %struct._IO_FILE*, !dbg !976
  %call447 = call i32 %231(i32 34, %struct._IO_FILE* %233), !dbg !976
  %cmp448 = icmp ne i32 %call447, -1, !dbg !976
  br i1 %cmp448, label %if.then450, label %if.else452, !dbg !976

if.then450:                                       ; preds = %do.body446
  %234 = load i32, i32* %done, align 4, !dbg !980
  %inc451 = add nsw i32 %234, 1, !dbg !980
  store i32 %inc451, i32* %done, align 4, !dbg !980
  br label %if.end453, !dbg !980

if.else452:                                       ; preds = %do.body446
  %235 = load i32, i32* %done, align 4, !dbg !982
  store i32 %235, i32* %retval, align 4, !dbg !982
  br label %return, !dbg !982

if.end453:                                        ; preds = %if.then450
  br label %do.end455, !dbg !984

do.end455:                                        ; preds = %if.end453
  br label %if.end456, !dbg !986

if.end456:                                        ; preds = %do.end455, %cond.end
  %236 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !988
  %flags457 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %236, i32 0, i32 1, !dbg !990
  %237 = load i32, i32* %flags457, align 4, !dbg !990
  %and458 = and i32 %237, 4, !dbg !991
  %tobool459 = icmp ne i32 %and458, 0, !dbg !991
  br i1 %tobool459, label %if.end477, label %if.then460, !dbg !992

if.then460:                                       ; preds = %if.end456
  br label %while.cond461, !dbg !993

while.cond461:                                    ; preds = %do.end475, %if.then460
  %238 = load i64, i64* %width, align 8, !dbg !994
  %dec462 = add nsw i64 %238, -1, !dbg !994
  store i64 %dec462, i64* %width, align 8, !dbg !994
  %cmp463 = icmp sgt i64 %238, 0, !dbg !996
  br i1 %cmp463, label %while.body465, label %while.end476, !dbg !997

while.body465:                                    ; preds = %while.cond461
  br label %do.body466, !dbg !998

do.body466:                                       ; preds = %while.body465
  %239 = load i32 (i32, %struct._IO_FILE*)*, i32 (i32, %struct._IO_FILE*)** %stream.addr, align 8, !dbg !999
  %240 = load i8*, i8** %data.addr, align 8, !dbg !999
  %241 = bitcast i8* %240 to %struct._IO_FILE*, !dbg !999
  %call467 = call i32 %239(i32 32, %struct._IO_FILE* %241), !dbg !999
  %cmp468 = icmp ne i32 %call467, -1, !dbg !999
  br i1 %cmp468, label %if.then470, label %if.else472, !dbg !999

if.then470:                                       ; preds = %do.body466
  %242 = load i32, i32* %done, align 4, !dbg !1003
  %inc471 = add nsw i32 %242, 1, !dbg !1003
  store i32 %inc471, i32* %done, align 4, !dbg !1003
  br label %if.end473, !dbg !1003

if.else472:                                       ; preds = %do.body466
  %243 = load i32, i32* %done, align 4, !dbg !1005
  store i32 %243, i32* %retval, align 4, !dbg !1005
  br label %return, !dbg !1005

if.end473:                                        ; preds = %if.then470
  br label %do.end475, !dbg !1007

do.end475:                                        ; preds = %if.end473
  br label %while.cond461, !dbg !1009

while.end476:                                     ; preds = %while.cond461
  br label %if.end477, !dbg !1011

if.end477:                                        ; preds = %while.end476, %if.end456
  br label %while.cond478, !dbg !1013

while.cond478:                                    ; preds = %do.end498, %if.end477
  %244 = load i64, i64* %len, align 8, !dbg !1014
  %dec479 = add i64 %244, -1, !dbg !1014
  store i64 %dec479, i64* %len, align 8, !dbg !1014
  %cmp480 = icmp ugt i64 %244, 0, !dbg !1015
  br i1 %cmp480, label %land.rhs482, label %land.end485, !dbg !1016

land.rhs482:                                      ; preds = %while.cond478
  %245 = load i8*, i8** %str, align 8, !dbg !1017
  %246 = load i8, i8* %245, align 1, !dbg !1018
  %conv483 = sext i8 %246 to i32, !dbg !1018
  %tobool484 = icmp ne i32 %conv483, 0, !dbg !1019
  br label %land.end485

land.end485:                                      ; preds = %land.rhs482, %while.cond478
  %247 = phi i1 [ false, %while.cond478 ], [ %tobool484, %land.rhs482 ]
  br i1 %247, label %while.body486, label %while.end499, !dbg !1020

while.body486:                                    ; preds = %land.end485
  br label %do.body487, !dbg !1021

do.body487:                                       ; preds = %while.body486
  %248 = load i32 (i32, %struct._IO_FILE*)*, i32 (i32, %struct._IO_FILE*)** %stream.addr, align 8, !dbg !1022
  %249 = load i8*, i8** %str, align 8, !dbg !1022
  %incdec.ptr488 = getelementptr inbounds i8, i8* %249, i32 1, !dbg !1022
  store i8* %incdec.ptr488, i8** %str, align 8, !dbg !1022
  %250 = load i8, i8* %249, align 1, !dbg !1022
  %conv489 = zext i8 %250 to i32, !dbg !1022
  %251 = load i8*, i8** %data.addr, align 8, !dbg !1022
  %252 = bitcast i8* %251 to %struct._IO_FILE*, !dbg !1022
  %call490 = call i32 %248(i32 %conv489, %struct._IO_FILE* %252), !dbg !1022
  %cmp491 = icmp ne i32 %call490, -1, !dbg !1022
  br i1 %cmp491, label %if.then493, label %if.else495, !dbg !1022

if.then493:                                       ; preds = %do.body487
  %253 = load i32, i32* %done, align 4, !dbg !1026
  %inc494 = add nsw i32 %253, 1, !dbg !1026
  store i32 %inc494, i32* %done, align 4, !dbg !1026
  br label %if.end496, !dbg !1026

if.else495:                                       ; preds = %do.body487
  %254 = load i32, i32* %done, align 4, !dbg !1028
  store i32 %254, i32* %retval, align 4, !dbg !1028
  br label %return, !dbg !1028

if.end496:                                        ; preds = %if.then493
  br label %do.end498, !dbg !1030

do.end498:                                        ; preds = %if.end496
  br label %while.cond478, !dbg !1032

while.end499:                                     ; preds = %land.end485
  %255 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !1034
  %flags500 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %255, i32 0, i32 1, !dbg !1036
  %256 = load i32, i32* %flags500, align 4, !dbg !1036
  %and501 = and i32 %256, 4, !dbg !1037
  %tobool502 = icmp ne i32 %and501, 0, !dbg !1037
  br i1 %tobool502, label %if.then503, label %if.end520, !dbg !1038

if.then503:                                       ; preds = %while.end499
  br label %while.cond504, !dbg !1039

while.cond504:                                    ; preds = %do.end518, %if.then503
  %257 = load i64, i64* %width, align 8, !dbg !1040
  %dec505 = add nsw i64 %257, -1, !dbg !1040
  store i64 %dec505, i64* %width, align 8, !dbg !1040
  %cmp506 = icmp sgt i64 %257, 0, !dbg !1042
  br i1 %cmp506, label %while.body508, label %while.end519, !dbg !1043

while.body508:                                    ; preds = %while.cond504
  br label %do.body509, !dbg !1044

do.body509:                                       ; preds = %while.body508
  %258 = load i32 (i32, %struct._IO_FILE*)*, i32 (i32, %struct._IO_FILE*)** %stream.addr, align 8, !dbg !1045
  %259 = load i8*, i8** %data.addr, align 8, !dbg !1045
  %260 = bitcast i8* %259 to %struct._IO_FILE*, !dbg !1045
  %call510 = call i32 %258(i32 32, %struct._IO_FILE* %260), !dbg !1045
  %cmp511 = icmp ne i32 %call510, -1, !dbg !1045
  br i1 %cmp511, label %if.then513, label %if.else515, !dbg !1045

if.then513:                                       ; preds = %do.body509
  %261 = load i32, i32* %done, align 4, !dbg !1049
  %inc514 = add nsw i32 %261, 1, !dbg !1049
  store i32 %inc514, i32* %done, align 4, !dbg !1049
  br label %if.end516, !dbg !1049

if.else515:                                       ; preds = %do.body509
  %262 = load i32, i32* %done, align 4, !dbg !1051
  store i32 %262, i32* %retval, align 4, !dbg !1051
  br label %return, !dbg !1051

if.end516:                                        ; preds = %if.then513
  br label %do.end518, !dbg !1053

do.end518:                                        ; preds = %if.end516
  br label %while.cond504, !dbg !1055

while.end519:                                     ; preds = %while.cond504
  br label %if.end520, !dbg !1057

if.end520:                                        ; preds = %while.end519, %while.end499
  %263 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !1059
  %flags521 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %263, i32 0, i32 1, !dbg !1061
  %264 = load i32, i32* %flags521, align 4, !dbg !1061
  %and522 = and i32 %264, 8, !dbg !1062
  %tobool523 = icmp ne i32 %and522, 0, !dbg !1062
  br i1 %tobool523, label %if.then524, label %if.end535, !dbg !1063

if.then524:                                       ; preds = %if.end520
  br label %do.body525, !dbg !1064

do.body525:                                       ; preds = %if.then524
  %265 = load i32 (i32, %struct._IO_FILE*)*, i32 (i32, %struct._IO_FILE*)** %stream.addr, align 8, !dbg !1065
  %266 = load i8*, i8** %data.addr, align 8, !dbg !1065
  %267 = bitcast i8* %266 to %struct._IO_FILE*, !dbg !1065
  %call526 = call i32 %265(i32 34, %struct._IO_FILE* %267), !dbg !1065
  %cmp527 = icmp ne i32 %call526, -1, !dbg !1065
  br i1 %cmp527, label %if.then529, label %if.else531, !dbg !1065

if.then529:                                       ; preds = %do.body525
  %268 = load i32, i32* %done, align 4, !dbg !1069
  %inc530 = add nsw i32 %268, 1, !dbg !1069
  store i32 %inc530, i32* %done, align 4, !dbg !1069
  br label %if.end532, !dbg !1069

if.else531:                                       ; preds = %do.body525
  %269 = load i32, i32* %done, align 4, !dbg !1071
  store i32 %269, i32* %retval, align 4, !dbg !1071
  br label %return, !dbg !1071

if.end532:                                        ; preds = %if.then529
  br label %do.end534, !dbg !1073

do.end534:                                        ; preds = %if.end532
  br label %if.end535, !dbg !1075

if.end535:                                        ; preds = %do.end534, %if.end520
  br label %sw.epilog, !dbg !1077

sw.bb536:                                         ; preds = %if.end84
  call void @llvm.dbg.declare(metadata i8** %ptr, metadata !1078, metadata !236), !dbg !1080
  %270 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !1081
  %data537 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %270, i32 0, i32 4, !dbg !1082
  %ptr538 = bitcast %union.anon* %data537 to i8**, !dbg !1083
  %271 = load i8*, i8** %ptr538, align 8, !dbg !1083
  store i8* %271, i8** %ptr, align 8, !dbg !1084
  %272 = load i8*, i8** %ptr, align 8, !dbg !1085
  %cmp539 = icmp ne i8* %272, null, !dbg !1087
  br i1 %cmp539, label %if.then541, label %if.else546, !dbg !1088

if.then541:                                       ; preds = %sw.bb536
  store i64 16, i64* %base, align 8, !dbg !1089
  %273 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !1091
  %flags542 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %273, i32 0, i32 1, !dbg !1092
  %274 = load i32, i32* %flags542, align 4, !dbg !1092
  %and543 = and i32 %274, 4096, !dbg !1093
  %tobool544 = icmp ne i32 %and543, 0, !dbg !1094
  %cond545 = select i1 %tobool544, i8* getelementptr inbounds ([37 x i8], [37 x i8]* @upper_digits, i32 0, i32 0), i8* getelementptr inbounds ([37 x i8], [37 x i8]* @lower_digits, i32 0, i32 0), !dbg !1094
  store i8* %cond545, i8** %digits, align 8, !dbg !1095
  store i32 1, i32* %is_alt, align 4, !dbg !1096
  %275 = load i8*, i8** %ptr, align 8, !dbg !1097
  %276 = ptrtoint i8* %275 to i64, !dbg !1098
  store i64 %276, i64* %num, align 8, !dbg !1099
  store i32 0, i32* %is_neg, align 4, !dbg !1100
  br label %number, !dbg !1101

if.else546:                                       ; preds = %sw.bb536
  call void @llvm.dbg.declare(metadata i8** %point, metadata !1102, metadata !236), !dbg !1104
  %277 = load i64, i64* %width, align 8, !dbg !1105
  %sub547 = sub nsw i64 %277, 5, !dbg !1105
  store i64 %sub547, i64* %width, align 8, !dbg !1105
  %278 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !1106
  %flags548 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %278, i32 0, i32 1, !dbg !1108
  %279 = load i32, i32* %flags548, align 4, !dbg !1108
  %and549 = and i32 %279, 4, !dbg !1109
  %tobool550 = icmp ne i32 %and549, 0, !dbg !1109
  br i1 %tobool550, label %if.then551, label %if.end568, !dbg !1110

if.then551:                                       ; preds = %if.else546
  br label %while.cond552, !dbg !1111

while.cond552:                                    ; preds = %do.end566, %if.then551
  %280 = load i64, i64* %width, align 8, !dbg !1112
  %dec553 = add nsw i64 %280, -1, !dbg !1112
  store i64 %dec553, i64* %width, align 8, !dbg !1112
  %cmp554 = icmp sgt i64 %280, 0, !dbg !1114
  br i1 %cmp554, label %while.body556, label %while.end567, !dbg !1115

while.body556:                                    ; preds = %while.cond552
  br label %do.body557, !dbg !1116

do.body557:                                       ; preds = %while.body556
  %281 = load i32 (i32, %struct._IO_FILE*)*, i32 (i32, %struct._IO_FILE*)** %stream.addr, align 8, !dbg !1117
  %282 = load i8*, i8** %data.addr, align 8, !dbg !1117
  %283 = bitcast i8* %282 to %struct._IO_FILE*, !dbg !1117
  %call558 = call i32 %281(i32 32, %struct._IO_FILE* %283), !dbg !1117
  %cmp559 = icmp ne i32 %call558, -1, !dbg !1117
  br i1 %cmp559, label %if.then561, label %if.else563, !dbg !1117

if.then561:                                       ; preds = %do.body557
  %284 = load i32, i32* %done, align 4, !dbg !1121
  %inc562 = add nsw i32 %284, 1, !dbg !1121
  store i32 %inc562, i32* %done, align 4, !dbg !1121
  br label %if.end564, !dbg !1121

if.else563:                                       ; preds = %do.body557
  %285 = load i32, i32* %done, align 4, !dbg !1123
  store i32 %285, i32* %retval, align 4, !dbg !1123
  br label %return, !dbg !1123

if.end564:                                        ; preds = %if.then561
  br label %do.end566, !dbg !1125

do.end566:                                        ; preds = %if.end564
  br label %while.cond552, !dbg !1127

while.end567:                                     ; preds = %while.cond552
  br label %if.end568, !dbg !1129

if.end568:                                        ; preds = %while.end567, %if.else546
  store i8* getelementptr inbounds ([6 x i8], [6 x i8]* @dprintf_formatf.strnil, i32 0, i32 0), i8** %point, align 8, !dbg !1131
  br label %for.cond, !dbg !1133

for.cond:                                         ; preds = %for.inc, %if.end568
  %286 = load i8*, i8** %point, align 8, !dbg !1134
  %287 = load i8, i8* %286, align 1, !dbg !1137
  %conv569 = sext i8 %287 to i32, !dbg !1137
  %cmp570 = icmp ne i32 %conv569, 0, !dbg !1138
  br i1 %cmp570, label %for.body, label %for.end, !dbg !1139

for.body:                                         ; preds = %for.cond
  br label %do.body572, !dbg !1140

do.body572:                                       ; preds = %for.body
  %288 = load i32 (i32, %struct._IO_FILE*)*, i32 (i32, %struct._IO_FILE*)** %stream.addr, align 8, !dbg !1141
  %289 = load i8*, i8** %point, align 8, !dbg !1141
  %290 = load i8, i8* %289, align 1, !dbg !1141
  %conv573 = zext i8 %290 to i32, !dbg !1141
  %291 = load i8*, i8** %data.addr, align 8, !dbg !1141
  %292 = bitcast i8* %291 to %struct._IO_FILE*, !dbg !1141
  %call574 = call i32 %288(i32 %conv573, %struct._IO_FILE* %292), !dbg !1141
  %cmp575 = icmp ne i32 %call574, -1, !dbg !1141
  br i1 %cmp575, label %if.then577, label %if.else579, !dbg !1141

if.then577:                                       ; preds = %do.body572
  %293 = load i32, i32* %done, align 4, !dbg !1145
  %inc578 = add nsw i32 %293, 1, !dbg !1145
  store i32 %inc578, i32* %done, align 4, !dbg !1145
  br label %if.end580, !dbg !1145

if.else579:                                       ; preds = %do.body572
  %294 = load i32, i32* %done, align 4, !dbg !1147
  store i32 %294, i32* %retval, align 4, !dbg !1147
  br label %return, !dbg !1147

if.end580:                                        ; preds = %if.then577
  br label %do.end582, !dbg !1149

do.end582:                                        ; preds = %if.end580
  br label %for.inc, !dbg !1151

for.inc:                                          ; preds = %do.end582
  %295 = load i8*, i8** %point, align 8, !dbg !1153
  %incdec.ptr583 = getelementptr inbounds i8, i8* %295, i32 1, !dbg !1153
  store i8* %incdec.ptr583, i8** %point, align 8, !dbg !1153
  br label %for.cond, !dbg !1155

for.end:                                          ; preds = %for.cond
  %296 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !1156
  %flags584 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %296, i32 0, i32 1, !dbg !1158
  %297 = load i32, i32* %flags584, align 4, !dbg !1158
  %and585 = and i32 %297, 4, !dbg !1159
  %tobool586 = icmp ne i32 %and585, 0, !dbg !1159
  br i1 %tobool586, label %if.end604, label %if.then587, !dbg !1160

if.then587:                                       ; preds = %for.end
  br label %while.cond588, !dbg !1161

while.cond588:                                    ; preds = %do.end602, %if.then587
  %298 = load i64, i64* %width, align 8, !dbg !1162
  %dec589 = add nsw i64 %298, -1, !dbg !1162
  store i64 %dec589, i64* %width, align 8, !dbg !1162
  %cmp590 = icmp sgt i64 %298, 0, !dbg !1164
  br i1 %cmp590, label %while.body592, label %while.end603, !dbg !1165

while.body592:                                    ; preds = %while.cond588
  br label %do.body593, !dbg !1166

do.body593:                                       ; preds = %while.body592
  %299 = load i32 (i32, %struct._IO_FILE*)*, i32 (i32, %struct._IO_FILE*)** %stream.addr, align 8, !dbg !1167
  %300 = load i8*, i8** %data.addr, align 8, !dbg !1167
  %301 = bitcast i8* %300 to %struct._IO_FILE*, !dbg !1167
  %call594 = call i32 %299(i32 32, %struct._IO_FILE* %301), !dbg !1167
  %cmp595 = icmp ne i32 %call594, -1, !dbg !1167
  br i1 %cmp595, label %if.then597, label %if.else599, !dbg !1167

if.then597:                                       ; preds = %do.body593
  %302 = load i32, i32* %done, align 4, !dbg !1171
  %inc598 = add nsw i32 %302, 1, !dbg !1171
  store i32 %inc598, i32* %done, align 4, !dbg !1171
  br label %if.end600, !dbg !1171

if.else599:                                       ; preds = %do.body593
  %303 = load i32, i32* %done, align 4, !dbg !1173
  store i32 %303, i32* %retval, align 4, !dbg !1173
  br label %return, !dbg !1173

if.end600:                                        ; preds = %if.then597
  br label %do.end602, !dbg !1175

do.end602:                                        ; preds = %if.end600
  br label %while.cond588, !dbg !1177

while.end603:                                     ; preds = %while.cond588
  br label %if.end604, !dbg !1179

if.end604:                                        ; preds = %while.end603, %for.end
  br label %if.end605

if.end605:                                        ; preds = %if.end604
  br label %sw.epilog, !dbg !1181

sw.bb606:                                         ; preds = %if.end84
  call void @llvm.dbg.declare(metadata [32 x i8]* %formatbuf, metadata !1182, metadata !236), !dbg !1187
  %304 = bitcast [32 x i8]* %formatbuf to i8*, !dbg !1187
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %304, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @dprintf_formatf.formatbuf, i32 0, i32 0), i64 32, i32 16, i1 false), !dbg !1187
  call void @llvm.dbg.declare(metadata i8** %fptr, metadata !1188, metadata !236), !dbg !1189
  %arrayidx607 = getelementptr inbounds [32 x i8], [32 x i8]* %formatbuf, i64 0, i64 1, !dbg !1190
  store i8* %arrayidx607, i8** %fptr, align 8, !dbg !1189
  call void @llvm.dbg.declare(metadata i64* %left, metadata !1191, metadata !236), !dbg !1192
  %arraydecay608 = getelementptr inbounds [32 x i8], [32 x i8]* %formatbuf, i32 0, i32 0, !dbg !1193
  %call609 = call i64 @strlen(i8* %arraydecay608) #8, !dbg !1194
  %sub610 = sub i64 32, %call609, !dbg !1195
  store i64 %sub610, i64* %left, align 8, !dbg !1192
  call void @llvm.dbg.declare(metadata i32* %len611, metadata !1196, metadata !236), !dbg !1197
  store i64 -1, i64* %width, align 8, !dbg !1198
  %305 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !1199
  %flags612 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %305, i32 0, i32 1, !dbg !1201
  %306 = load i32, i32* %flags612, align 4, !dbg !1201
  %and613 = and i32 %306, 8192, !dbg !1202
  %tobool614 = icmp ne i32 %and613, 0, !dbg !1202
  br i1 %tobool614, label %if.then615, label %if.else617, !dbg !1203

if.then615:                                       ; preds = %sw.bb606
  %307 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !1204
  %width616 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %307, i32 0, i32 2, !dbg !1205
  %308 = load i64, i64* %width616, align 8, !dbg !1205
  store i64 %308, i64* %width, align 8, !dbg !1206
  br label %if.end628, !dbg !1207

if.else617:                                       ; preds = %sw.bb606
  %309 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !1208
  %flags618 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %309, i32 0, i32 1, !dbg !1210
  %310 = load i32, i32* %flags618, align 4, !dbg !1210
  %and619 = and i32 %310, 16384, !dbg !1211
  %tobool620 = icmp ne i32 %and619, 0, !dbg !1211
  br i1 %tobool620, label %if.then621, label %if.end627, !dbg !1212

if.then621:                                       ; preds = %if.else617
  %311 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !1213
  %width622 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %311, i32 0, i32 2, !dbg !1214
  %312 = load i64, i64* %width622, align 8, !dbg !1214
  %arrayidx623 = getelementptr inbounds [128 x %struct.va_stack_t], [128 x %struct.va_stack_t]* %vto, i64 0, i64 %312, !dbg !1215
  %data624 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx623, i32 0, i32 4, !dbg !1216
  %num625 = bitcast %union.anon* %data624 to %union.anon.0*, !dbg !1217
  %as_signed626 = bitcast %union.anon.0* %num625 to i64*, !dbg !1218
  %313 = load i64, i64* %as_signed626, align 8, !dbg !1218
  store i64 %313, i64* %width, align 8, !dbg !1219
  br label %if.end627, !dbg !1220

if.end627:                                        ; preds = %if.then621, %if.else617
  br label %if.end628

if.end628:                                        ; preds = %if.end627, %if.then615
  store i64 -1, i64* %prec, align 8, !dbg !1221
  %314 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !1222
  %flags629 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %314, i32 0, i32 1, !dbg !1224
  %315 = load i32, i32* %flags629, align 4, !dbg !1224
  %and630 = and i32 %315, 32768, !dbg !1225
  %tobool631 = icmp ne i32 %and630, 0, !dbg !1225
  br i1 %tobool631, label %if.then632, label %if.else634, !dbg !1226

if.then632:                                       ; preds = %if.end628
  %316 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !1227
  %precision633 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %316, i32 0, i32 3, !dbg !1228
  %317 = load i64, i64* %precision633, align 8, !dbg !1228
  store i64 %317, i64* %prec, align 8, !dbg !1229
  br label %if.end645, !dbg !1230

if.else634:                                       ; preds = %if.end628
  %318 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !1231
  %flags635 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %318, i32 0, i32 1, !dbg !1233
  %319 = load i32, i32* %flags635, align 4, !dbg !1233
  %and636 = and i32 %319, 65536, !dbg !1234
  %tobool637 = icmp ne i32 %and636, 0, !dbg !1234
  br i1 %tobool637, label %if.then638, label %if.end644, !dbg !1235

if.then638:                                       ; preds = %if.else634
  %320 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !1236
  %precision639 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %320, i32 0, i32 3, !dbg !1237
  %321 = load i64, i64* %precision639, align 8, !dbg !1237
  %arrayidx640 = getelementptr inbounds [128 x %struct.va_stack_t], [128 x %struct.va_stack_t]* %vto, i64 0, i64 %321, !dbg !1238
  %data641 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx640, i32 0, i32 4, !dbg !1239
  %num642 = bitcast %union.anon* %data641 to %union.anon.0*, !dbg !1240
  %as_signed643 = bitcast %union.anon.0* %num642 to i64*, !dbg !1241
  %322 = load i64, i64* %as_signed643, align 8, !dbg !1241
  store i64 %322, i64* %prec, align 8, !dbg !1242
  br label %if.end644, !dbg !1243

if.end644:                                        ; preds = %if.then638, %if.else634
  br label %if.end645

if.end645:                                        ; preds = %if.end644, %if.then632
  %323 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !1244
  %flags646 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %323, i32 0, i32 1, !dbg !1246
  %324 = load i32, i32* %flags646, align 4, !dbg !1246
  %and647 = and i32 %324, 4, !dbg !1247
  %tobool648 = icmp ne i32 %and647, 0, !dbg !1247
  br i1 %tobool648, label %if.then649, label %if.end651, !dbg !1248

if.then649:                                       ; preds = %if.end645
  %325 = load i8*, i8** %fptr, align 8, !dbg !1249
  %incdec.ptr650 = getelementptr inbounds i8, i8* %325, i32 1, !dbg !1249
  store i8* %incdec.ptr650, i8** %fptr, align 8, !dbg !1249
  store i8 45, i8* %325, align 1, !dbg !1250
  br label %if.end651, !dbg !1251

if.end651:                                        ; preds = %if.then649, %if.end645
  %326 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !1252
  %flags652 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %326, i32 0, i32 1, !dbg !1254
  %327 = load i32, i32* %flags652, align 4, !dbg !1254
  %and653 = and i32 %327, 2, !dbg !1255
  %tobool654 = icmp ne i32 %and653, 0, !dbg !1255
  br i1 %tobool654, label %if.then655, label %if.end657, !dbg !1256

if.then655:                                       ; preds = %if.end651
  %328 = load i8*, i8** %fptr, align 8, !dbg !1257
  %incdec.ptr656 = getelementptr inbounds i8, i8* %328, i32 1, !dbg !1257
  store i8* %incdec.ptr656, i8** %fptr, align 8, !dbg !1257
  store i8 43, i8* %328, align 1, !dbg !1258
  br label %if.end657, !dbg !1259

if.end657:                                        ; preds = %if.then655, %if.end651
  %329 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !1260
  %flags658 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %329, i32 0, i32 1, !dbg !1262
  %330 = load i32, i32* %flags658, align 4, !dbg !1262
  %and659 = and i32 %330, 1, !dbg !1263
  %tobool660 = icmp ne i32 %and659, 0, !dbg !1263
  br i1 %tobool660, label %if.then661, label %if.end663, !dbg !1264

if.then661:                                       ; preds = %if.end657
  %331 = load i8*, i8** %fptr, align 8, !dbg !1265
  %incdec.ptr662 = getelementptr inbounds i8, i8* %331, i32 1, !dbg !1265
  store i8* %incdec.ptr662, i8** %fptr, align 8, !dbg !1265
  store i8 32, i8* %331, align 1, !dbg !1266
  br label %if.end663, !dbg !1267

if.end663:                                        ; preds = %if.then661, %if.end657
  %332 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !1268
  %flags664 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %332, i32 0, i32 1, !dbg !1270
  %333 = load i32, i32* %flags664, align 4, !dbg !1270
  %and665 = and i32 %333, 8, !dbg !1271
  %tobool666 = icmp ne i32 %and665, 0, !dbg !1271
  br i1 %tobool666, label %if.then667, label %if.end669, !dbg !1272

if.then667:                                       ; preds = %if.end663
  %334 = load i8*, i8** %fptr, align 8, !dbg !1273
  %incdec.ptr668 = getelementptr inbounds i8, i8* %334, i32 1, !dbg !1273
  store i8* %incdec.ptr668, i8** %fptr, align 8, !dbg !1273
  store i8 35, i8* %334, align 1, !dbg !1274
  br label %if.end669, !dbg !1275

if.end669:                                        ; preds = %if.then667, %if.end663
  %335 = load i8*, i8** %fptr, align 8, !dbg !1276
  store i8 0, i8* %335, align 1, !dbg !1277
  %336 = load i64, i64* %width, align 8, !dbg !1278
  %cmp670 = icmp sge i64 %336, 0, !dbg !1280
  br i1 %cmp670, label %if.then672, label %if.end680, !dbg !1281

if.then672:                                       ; preds = %if.end669
  %337 = load i64, i64* %width, align 8, !dbg !1282
  %cmp673 = icmp sge i64 %337, 326, !dbg !1285
  br i1 %cmp673, label %if.then675, label %if.end676, !dbg !1286

if.then675:                                       ; preds = %if.then672
  store i64 325, i64* %width, align 8, !dbg !1287
  br label %if.end676, !dbg !1288

if.end676:                                        ; preds = %if.then675, %if.then672
  %338 = load i8*, i8** %fptr, align 8, !dbg !1289
  %339 = load i64, i64* %left, align 8, !dbg !1290
  %340 = load i64, i64* %width, align 8, !dbg !1291
  %call677 = call i32 (i8*, i64, i8*, ...) @curl_msnprintf(i8* %338, i64 %339, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.1, i32 0, i32 0), i64 %340), !dbg !1292
  store i32 %call677, i32* %len611, align 4, !dbg !1293
  %341 = load i32, i32* %len611, align 4, !dbg !1294
  %342 = load i8*, i8** %fptr, align 8, !dbg !1295
  %idx.ext = sext i32 %341 to i64, !dbg !1295
  %add.ptr = getelementptr inbounds i8, i8* %342, i64 %idx.ext, !dbg !1295
  store i8* %add.ptr, i8** %fptr, align 8, !dbg !1295
  %343 = load i32, i32* %len611, align 4, !dbg !1296
  %conv678 = sext i32 %343 to i64, !dbg !1296
  %344 = load i64, i64* %left, align 8, !dbg !1297
  %sub679 = sub i64 %344, %conv678, !dbg !1297
  store i64 %sub679, i64* %left, align 8, !dbg !1297
  br label %if.end680, !dbg !1298

if.end680:                                        ; preds = %if.end676, %if.end669
  %345 = load i64, i64* %prec, align 8, !dbg !1299
  %cmp681 = icmp sge i64 %345, 0, !dbg !1301
  br i1 %cmp681, label %if.then683, label %if.end700, !dbg !1302

if.then683:                                       ; preds = %if.end680
  call void @llvm.dbg.declare(metadata i64* %maxprec, metadata !1303, metadata !236), !dbg !1305
  store i64 324, i64* %maxprec, align 8, !dbg !1305
  call void @llvm.dbg.declare(metadata double* %val, metadata !1306, metadata !236), !dbg !1307
  %346 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !1308
  %data684 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %346, i32 0, i32 4, !dbg !1309
  %dnum = bitcast %union.anon* %data684 to double*, !dbg !1310
  %347 = load double, double* %dnum, align 8, !dbg !1310
  store double %347, double* %val, align 8, !dbg !1307
  br label %while.cond685, !dbg !1311

while.cond685:                                    ; preds = %while.body688, %if.then683
  %348 = load double, double* %val, align 8, !dbg !1312
  %cmp686 = fcmp oge double %348, 1.000000e+01, !dbg !1314
  br i1 %cmp686, label %while.body688, label %while.end691, !dbg !1315

while.body688:                                    ; preds = %while.cond685
  %349 = load double, double* %val, align 8, !dbg !1316
  %div689 = fdiv double %349, 1.000000e+01, !dbg !1316
  store double %div689, double* %val, align 8, !dbg !1316
  %350 = load i64, i64* %maxprec, align 8, !dbg !1318
  %dec690 = add i64 %350, -1, !dbg !1318
  store i64 %dec690, i64* %maxprec, align 8, !dbg !1318
  br label %while.cond685, !dbg !1319

while.end691:                                     ; preds = %while.cond685
  %351 = load i64, i64* %prec, align 8, !dbg !1321
  %352 = load i64, i64* %maxprec, align 8, !dbg !1323
  %cmp692 = icmp sgt i64 %351, %352, !dbg !1324
  br i1 %cmp692, label %if.then694, label %if.end696, !dbg !1325

if.then694:                                       ; preds = %while.end691
  %353 = load i64, i64* %maxprec, align 8, !dbg !1326
  %sub695 = sub nsw i64 %353, 1, !dbg !1327
  store i64 %sub695, i64* %prec, align 8, !dbg !1328
  br label %if.end696, !dbg !1329

if.end696:                                        ; preds = %if.then694, %while.end691
  %354 = load i8*, i8** %fptr, align 8, !dbg !1330
  %355 = load i64, i64* %left, align 8, !dbg !1331
  %356 = load i64, i64* %prec, align 8, !dbg !1332
  %call697 = call i32 (i8*, i64, i8*, ...) @curl_msnprintf(i8* %354, i64 %355, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.2, i32 0, i32 0), i64 %356), !dbg !1333
  store i32 %call697, i32* %len611, align 4, !dbg !1334
  %357 = load i32, i32* %len611, align 4, !dbg !1335
  %358 = load i8*, i8** %fptr, align 8, !dbg !1336
  %idx.ext698 = sext i32 %357 to i64, !dbg !1336
  %add.ptr699 = getelementptr inbounds i8, i8* %358, i64 %idx.ext698, !dbg !1336
  store i8* %add.ptr699, i8** %fptr, align 8, !dbg !1336
  br label %if.end700, !dbg !1337

if.end700:                                        ; preds = %if.end696, %if.end680
  %359 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !1338
  %flags701 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %359, i32 0, i32 1, !dbg !1340
  %360 = load i32, i32* %flags701, align 4, !dbg !1340
  %and702 = and i32 %360, 32, !dbg !1341
  %tobool703 = icmp ne i32 %and702, 0, !dbg !1341
  br i1 %tobool703, label %if.then704, label %if.end706, !dbg !1342

if.then704:                                       ; preds = %if.end700
  %361 = load i8*, i8** %fptr, align 8, !dbg !1343
  %incdec.ptr705 = getelementptr inbounds i8, i8* %361, i32 1, !dbg !1343
  store i8* %incdec.ptr705, i8** %fptr, align 8, !dbg !1343
  store i8 108, i8* %361, align 1, !dbg !1344
  br label %if.end706, !dbg !1345

if.end706:                                        ; preds = %if.then704, %if.end700
  %362 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !1346
  %flags707 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %362, i32 0, i32 1, !dbg !1348
  %363 = load i32, i32* %flags707, align 4, !dbg !1348
  %and708 = and i32 %363, 262144, !dbg !1349
  %tobool709 = icmp ne i32 %and708, 0, !dbg !1349
  br i1 %tobool709, label %if.then710, label %if.else717, !dbg !1350

if.then710:                                       ; preds = %if.end706
  %364 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !1351
  %flags711 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %364, i32 0, i32 1, !dbg !1352
  %365 = load i32, i32* %flags711, align 4, !dbg !1352
  %and712 = and i32 %365, 4096, !dbg !1353
  %tobool713 = icmp ne i32 %and712, 0, !dbg !1354
  %cond714 = select i1 %tobool713, i32 69, i32 101, !dbg !1354
  %conv715 = trunc i32 %cond714 to i8, !dbg !1355
  %366 = load i8*, i8** %fptr, align 8, !dbg !1356
  %incdec.ptr716 = getelementptr inbounds i8, i8* %366, i32 1, !dbg !1356
  store i8* %incdec.ptr716, i8** %fptr, align 8, !dbg !1356
  store i8 %conv715, i8* %366, align 1, !dbg !1357
  br label %if.end731, !dbg !1358

if.else717:                                       ; preds = %if.end706
  %367 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !1359
  %flags718 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %367, i32 0, i32 1, !dbg !1361
  %368 = load i32, i32* %flags718, align 4, !dbg !1361
  %and719 = and i32 %368, 524288, !dbg !1362
  %tobool720 = icmp ne i32 %and719, 0, !dbg !1362
  br i1 %tobool720, label %if.then721, label %if.else728, !dbg !1363

if.then721:                                       ; preds = %if.else717
  %369 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !1364
  %flags722 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %369, i32 0, i32 1, !dbg !1365
  %370 = load i32, i32* %flags722, align 4, !dbg !1365
  %and723 = and i32 %370, 4096, !dbg !1366
  %tobool724 = icmp ne i32 %and723, 0, !dbg !1367
  %cond725 = select i1 %tobool724, i32 71, i32 103, !dbg !1367
  %conv726 = trunc i32 %cond725 to i8, !dbg !1368
  %371 = load i8*, i8** %fptr, align 8, !dbg !1369
  %incdec.ptr727 = getelementptr inbounds i8, i8* %371, i32 1, !dbg !1369
  store i8* %incdec.ptr727, i8** %fptr, align 8, !dbg !1369
  store i8 %conv726, i8* %371, align 1, !dbg !1370
  br label %if.end730, !dbg !1371

if.else728:                                       ; preds = %if.else717
  %372 = load i8*, i8** %fptr, align 8, !dbg !1372
  %incdec.ptr729 = getelementptr inbounds i8, i8* %372, i32 1, !dbg !1372
  store i8* %incdec.ptr729, i8** %fptr, align 8, !dbg !1372
  store i8 102, i8* %372, align 1, !dbg !1373
  br label %if.end730

if.end730:                                        ; preds = %if.else728, %if.then721
  br label %if.end731

if.end731:                                        ; preds = %if.end730, %if.then710
  %373 = load i8*, i8** %fptr, align 8, !dbg !1374
  store i8 0, i8* %373, align 1, !dbg !1375
  %arraydecay732 = getelementptr inbounds [326 x i8], [326 x i8]* %work, i32 0, i32 0, !dbg !1376
  %arraydecay733 = getelementptr inbounds [32 x i8], [32 x i8]* %formatbuf, i32 0, i32 0, !dbg !1377
  %374 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !1378
  %data734 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %374, i32 0, i32 4, !dbg !1379
  %dnum735 = bitcast %union.anon* %data734 to double*, !dbg !1380
  %375 = load double, double* %dnum735, align 8, !dbg !1380
  %call736 = call i32 (i8*, i8*, ...) @sprintf(i8* %arraydecay732, i8* %arraydecay733, double %375) #2, !dbg !1381
  %arraydecay737 = getelementptr inbounds [326 x i8], [326 x i8]* %work, i32 0, i32 0, !dbg !1382
  store i8* %arraydecay737, i8** %fptr, align 8, !dbg !1384
  br label %for.cond738, !dbg !1385

for.cond738:                                      ; preds = %for.inc752, %if.end731
  %376 = load i8*, i8** %fptr, align 8, !dbg !1386
  %377 = load i8, i8* %376, align 1, !dbg !1389
  %tobool739 = icmp ne i8 %377, 0, !dbg !1390
  br i1 %tobool739, label %for.body740, label %for.end754, !dbg !1390

for.body740:                                      ; preds = %for.cond738
  br label %do.body741, !dbg !1391

do.body741:                                       ; preds = %for.body740
  %378 = load i32 (i32, %struct._IO_FILE*)*, i32 (i32, %struct._IO_FILE*)** %stream.addr, align 8, !dbg !1392
  %379 = load i8*, i8** %fptr, align 8, !dbg !1392
  %380 = load i8, i8* %379, align 1, !dbg !1392
  %conv742 = zext i8 %380 to i32, !dbg !1392
  %381 = load i8*, i8** %data.addr, align 8, !dbg !1392
  %382 = bitcast i8* %381 to %struct._IO_FILE*, !dbg !1392
  %call743 = call i32 %378(i32 %conv742, %struct._IO_FILE* %382), !dbg !1392
  %cmp744 = icmp ne i32 %call743, -1, !dbg !1392
  br i1 %cmp744, label %if.then746, label %if.else748, !dbg !1392

if.then746:                                       ; preds = %do.body741
  %383 = load i32, i32* %done, align 4, !dbg !1396
  %inc747 = add nsw i32 %383, 1, !dbg !1396
  store i32 %inc747, i32* %done, align 4, !dbg !1396
  br label %if.end749, !dbg !1396

if.else748:                                       ; preds = %do.body741
  %384 = load i32, i32* %done, align 4, !dbg !1398
  store i32 %384, i32* %retval, align 4, !dbg !1398
  br label %return, !dbg !1398

if.end749:                                        ; preds = %if.then746
  br label %do.end751, !dbg !1400

do.end751:                                        ; preds = %if.end749
  br label %for.inc752, !dbg !1402

for.inc752:                                       ; preds = %do.end751
  %385 = load i8*, i8** %fptr, align 8, !dbg !1404
  %incdec.ptr753 = getelementptr inbounds i8, i8* %385, i32 1, !dbg !1404
  store i8* %incdec.ptr753, i8** %fptr, align 8, !dbg !1404
  br label %for.cond738, !dbg !1406

for.end754:                                       ; preds = %for.cond738
  br label %sw.epilog, !dbg !1407

sw.bb755:                                         ; preds = %if.end84
  %386 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !1408
  %flags756 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %386, i32 0, i32 1, !dbg !1410
  %387 = load i32, i32* %flags756, align 4, !dbg !1410
  %and757 = and i32 %387, 64, !dbg !1411
  %tobool758 = icmp ne i32 %and757, 0, !dbg !1411
  br i1 %tobool758, label %if.then759, label %if.else763, !dbg !1412

if.then759:                                       ; preds = %sw.bb755
  %388 = load i32, i32* %done, align 4, !dbg !1413
  %conv760 = sext i32 %388 to i64, !dbg !1414
  %389 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !1415
  %data761 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %389, i32 0, i32 4, !dbg !1416
  %ptr762 = bitcast %union.anon* %data761 to i8**, !dbg !1417
  %390 = load i8*, i8** %ptr762, align 8, !dbg !1417
  %391 = bitcast i8* %390 to i64*, !dbg !1418
  store i64 %conv760, i64* %391, align 8, !dbg !1419
  br label %if.end784, !dbg !1420

if.else763:                                       ; preds = %sw.bb755
  %392 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !1421
  %flags764 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %392, i32 0, i32 1, !dbg !1423
  %393 = load i32, i32* %flags764, align 4, !dbg !1423
  %and765 = and i32 %393, 32, !dbg !1424
  %tobool766 = icmp ne i32 %and765, 0, !dbg !1424
  br i1 %tobool766, label %if.then767, label %if.else771, !dbg !1425

if.then767:                                       ; preds = %if.else763
  %394 = load i32, i32* %done, align 4, !dbg !1426
  %conv768 = sext i32 %394 to i64, !dbg !1427
  %395 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !1428
  %data769 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %395, i32 0, i32 4, !dbg !1429
  %ptr770 = bitcast %union.anon* %data769 to i8**, !dbg !1430
  %396 = load i8*, i8** %ptr770, align 8, !dbg !1430
  %397 = bitcast i8* %396 to i64*, !dbg !1431
  store i64 %conv768, i64* %397, align 8, !dbg !1432
  br label %if.end783, !dbg !1433

if.else771:                                       ; preds = %if.else763
  %398 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !1434
  %flags772 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %398, i32 0, i32 1, !dbg !1436
  %399 = load i32, i32* %flags772, align 4, !dbg !1436
  %and773 = and i32 %399, 16, !dbg !1437
  %tobool774 = icmp ne i32 %and773, 0, !dbg !1437
  br i1 %tobool774, label %if.else778, label %if.then775, !dbg !1438

if.then775:                                       ; preds = %if.else771
  %400 = load i32, i32* %done, align 4, !dbg !1439
  %401 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !1440
  %data776 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %401, i32 0, i32 4, !dbg !1441
  %ptr777 = bitcast %union.anon* %data776 to i8**, !dbg !1442
  %402 = load i8*, i8** %ptr777, align 8, !dbg !1442
  %403 = bitcast i8* %402 to i32*, !dbg !1443
  store i32 %400, i32* %403, align 4, !dbg !1444
  br label %if.end782, !dbg !1445

if.else778:                                       ; preds = %if.else771
  %404 = load i32, i32* %done, align 4, !dbg !1446
  %conv779 = trunc i32 %404 to i16, !dbg !1447
  %405 = load %struct.va_stack_t*, %struct.va_stack_t** %p, align 8, !dbg !1448
  %data780 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %405, i32 0, i32 4, !dbg !1449
  %ptr781 = bitcast %union.anon* %data780 to i8**, !dbg !1450
  %406 = load i8*, i8** %ptr781, align 8, !dbg !1450
  %407 = bitcast i8* %406 to i16*, !dbg !1451
  store i16 %conv779, i16* %407, align 2, !dbg !1452
  br label %if.end782

if.end782:                                        ; preds = %if.else778, %if.then775
  br label %if.end783

if.end783:                                        ; preds = %if.end782, %if.then767
  br label %if.end784

if.end784:                                        ; preds = %if.end783, %if.then759
  br label %sw.epilog, !dbg !1453

sw.default:                                       ; preds = %if.end84
  br label %sw.epilog, !dbg !1454

sw.epilog:                                        ; preds = %sw.default, %if.end784, %for.end754, %if.end605, %if.end535, %if.end413, %if.end146
  %408 = load i8**, i8*** %end, align 8, !dbg !1455
  %incdec.ptr785 = getelementptr inbounds i8*, i8** %408, i32 1, !dbg !1455
  store i8** %incdec.ptr785, i8*** %end, align 8, !dbg !1455
  %409 = load i8*, i8** %408, align 8, !dbg !1456
  store i8* %409, i8** %f, align 8, !dbg !1457
  br label %while.cond, !dbg !1458

while.end786:                                     ; preds = %while.cond
  %410 = load i32, i32* %done, align 4, !dbg !1460
  store i32 %410, i32* %retval, align 4, !dbg !1461
  br label %return, !dbg !1461

return:                                           ; preds = %while.end786, %if.else748, %if.else599, %if.else579, %if.else563, %if.else531, %if.else515, %if.else495, %if.else472, %if.else452, %if.else408, %if.else388, %if.else370, %if.else345, %if.else334, %if.else320, %if.else302, %if.else287, %if.else272, %if.else258, %if.else141, %if.else122, %if.else109, %if.else34, %if.else, %if.then
  %411 = load i32, i32* %retval, align 4, !dbg !1462
  ret i32 %411, !dbg !1462
}

; Function Attrs: nounwind uwtable
define internal i32 @addbyter(i32 %output, %struct._IO_FILE* %data) #0 !dbg !218 {
entry:
  %retval = alloca i32, align 4
  %output.addr = alloca i32, align 4
  %data.addr = alloca %struct._IO_FILE*, align 8
  %infop = alloca %struct.nsprintf*, align 8
  %outc = alloca i8, align 1
  store i32 %output, i32* %output.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %output.addr, metadata !1463, metadata !236), !dbg !1464
  store %struct._IO_FILE* %data, %struct._IO_FILE** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %data.addr, metadata !1465, metadata !236), !dbg !1466
  call void @llvm.dbg.declare(metadata %struct.nsprintf** %infop, metadata !1467, metadata !236), !dbg !1468
  %0 = load %struct._IO_FILE*, %struct._IO_FILE** %data.addr, align 8, !dbg !1469
  %1 = bitcast %struct._IO_FILE* %0 to %struct.nsprintf*, !dbg !1470
  store %struct.nsprintf* %1, %struct.nsprintf** %infop, align 8, !dbg !1468
  call void @llvm.dbg.declare(metadata i8* %outc, metadata !1471, metadata !236), !dbg !1472
  %2 = load i32, i32* %output.addr, align 4, !dbg !1473
  %conv = trunc i32 %2 to i8, !dbg !1474
  store i8 %conv, i8* %outc, align 1, !dbg !1472
  %3 = load %struct.nsprintf*, %struct.nsprintf** %infop, align 8, !dbg !1475
  %length = getelementptr inbounds %struct.nsprintf, %struct.nsprintf* %3, i32 0, i32 1, !dbg !1477
  %4 = load i64, i64* %length, align 8, !dbg !1477
  %5 = load %struct.nsprintf*, %struct.nsprintf** %infop, align 8, !dbg !1478
  %max = getelementptr inbounds %struct.nsprintf, %struct.nsprintf* %5, i32 0, i32 2, !dbg !1479
  %6 = load i64, i64* %max, align 8, !dbg !1479
  %cmp = icmp ult i64 %4, %6, !dbg !1480
  br i1 %cmp, label %if.then, label %if.end, !dbg !1481

if.then:                                          ; preds = %entry
  %7 = load i8, i8* %outc, align 1, !dbg !1482
  %8 = load %struct.nsprintf*, %struct.nsprintf** %infop, align 8, !dbg !1484
  %buffer = getelementptr inbounds %struct.nsprintf, %struct.nsprintf* %8, i32 0, i32 0, !dbg !1485
  %9 = load i8*, i8** %buffer, align 8, !dbg !1485
  %arrayidx = getelementptr inbounds i8, i8* %9, i64 0, !dbg !1484
  store i8 %7, i8* %arrayidx, align 1, !dbg !1486
  %10 = load %struct.nsprintf*, %struct.nsprintf** %infop, align 8, !dbg !1487
  %buffer2 = getelementptr inbounds %struct.nsprintf, %struct.nsprintf* %10, i32 0, i32 0, !dbg !1488
  %11 = load i8*, i8** %buffer2, align 8, !dbg !1489
  %incdec.ptr = getelementptr inbounds i8, i8* %11, i32 1, !dbg !1489
  store i8* %incdec.ptr, i8** %buffer2, align 8, !dbg !1489
  %12 = load %struct.nsprintf*, %struct.nsprintf** %infop, align 8, !dbg !1490
  %length3 = getelementptr inbounds %struct.nsprintf, %struct.nsprintf* %12, i32 0, i32 1, !dbg !1491
  %13 = load i64, i64* %length3, align 8, !dbg !1492
  %inc = add i64 %13, 1, !dbg !1492
  store i64 %inc, i64* %length3, align 8, !dbg !1492
  %14 = load i8, i8* %outc, align 1, !dbg !1493
  %conv4 = zext i8 %14 to i32, !dbg !1493
  store i32 %conv4, i32* %retval, align 4, !dbg !1494
  br label %return, !dbg !1494

if.end:                                           ; preds = %entry
  store i32 -1, i32* %retval, align 4, !dbg !1495
  br label %return, !dbg !1495

return:                                           ; preds = %if.end, %if.then
  %15 = load i32, i32* %retval, align 4, !dbg !1496
  ret i32 %15, !dbg !1496
}

; Function Attrs: nounwind uwtable
define i32 @curl_msnprintf(i8* %buffer, i64 %maxlength, i8* %format, ...) #0 !dbg !154 {
entry:
  %buffer.addr = alloca i8*, align 8
  %maxlength.addr = alloca i64, align 8
  %format.addr = alloca i8*, align 8
  %retcode = alloca i32, align 4
  %ap_save = alloca [1 x %struct.__va_list_tag], align 16
  store i8* %buffer, i8** %buffer.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buffer.addr, metadata !1497, metadata !236), !dbg !1498
  store i64 %maxlength, i64* %maxlength.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %maxlength.addr, metadata !1499, metadata !236), !dbg !1500
  store i8* %format, i8** %format.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %format.addr, metadata !1501, metadata !236), !dbg !1502
  call void @llvm.dbg.declare(metadata i32* %retcode, metadata !1503, metadata !236), !dbg !1504
  call void @llvm.dbg.declare(metadata [1 x %struct.__va_list_tag]* %ap_save, metadata !1505, metadata !236), !dbg !1511
  %arraydecay = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %ap_save, i32 0, i32 0, !dbg !1512
  %arraydecay1 = bitcast %struct.__va_list_tag* %arraydecay to i8*, !dbg !1512
  call void @llvm.va_start(i8* %arraydecay1), !dbg !1512
  %0 = load i8*, i8** %buffer.addr, align 8, !dbg !1513
  %1 = load i64, i64* %maxlength.addr, align 8, !dbg !1514
  %2 = load i8*, i8** %format.addr, align 8, !dbg !1515
  %arraydecay2 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %ap_save, i32 0, i32 0, !dbg !1516
  %call = call i32 @curl_mvsnprintf(i8* %0, i64 %1, i8* %2, %struct.__va_list_tag* %arraydecay2), !dbg !1517
  store i32 %call, i32* %retcode, align 4, !dbg !1518
  %arraydecay3 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %ap_save, i32 0, i32 0, !dbg !1519
  %arraydecay34 = bitcast %struct.__va_list_tag* %arraydecay3 to i8*, !dbg !1519
  call void @llvm.va_end(i8* %arraydecay34), !dbg !1519
  %3 = load i32, i32* %retcode, align 4, !dbg !1520
  ret i32 %3, !dbg !1521
}

; Function Attrs: nounwind
declare void @llvm.va_start(i8*) #2

; Function Attrs: nounwind
declare void @llvm.va_end(i8*) #2

; Function Attrs: nounwind uwtable
define i8* @curl_maprintf(i8* %format, ...) #0 !dbg !157 {
entry:
  %retval = alloca i8*, align 8
  %format.addr = alloca i8*, align 8
  %ap_save = alloca [1 x %struct.__va_list_tag], align 16
  %retcode = alloca i32, align 4
  %info = alloca %struct.asprintf, align 8
  store i8* %format, i8** %format.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %format.addr, metadata !1522, metadata !236), !dbg !1523
  call void @llvm.dbg.declare(metadata [1 x %struct.__va_list_tag]* %ap_save, metadata !1524, metadata !236), !dbg !1525
  call void @llvm.dbg.declare(metadata i32* %retcode, metadata !1526, metadata !236), !dbg !1527
  call void @llvm.dbg.declare(metadata %struct.asprintf* %info, metadata !1528, metadata !236), !dbg !1529
  %buffer = getelementptr inbounds %struct.asprintf, %struct.asprintf* %info, i32 0, i32 0, !dbg !1530
  store i8* null, i8** %buffer, align 8, !dbg !1531
  %len = getelementptr inbounds %struct.asprintf, %struct.asprintf* %info, i32 0, i32 1, !dbg !1532
  store i64 0, i64* %len, align 8, !dbg !1533
  %alloc = getelementptr inbounds %struct.asprintf, %struct.asprintf* %info, i32 0, i32 2, !dbg !1534
  store i64 0, i64* %alloc, align 8, !dbg !1535
  %fail = getelementptr inbounds %struct.asprintf, %struct.asprintf* %info, i32 0, i32 3, !dbg !1536
  store i32 0, i32* %fail, align 8, !dbg !1537
  %arraydecay = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %ap_save, i32 0, i32 0, !dbg !1538
  %arraydecay1 = bitcast %struct.__va_list_tag* %arraydecay to i8*, !dbg !1538
  call void @llvm.va_start(i8* %arraydecay1), !dbg !1538
  %0 = bitcast %struct.asprintf* %info to i8*, !dbg !1539
  %1 = load i8*, i8** %format.addr, align 8, !dbg !1540
  %arraydecay2 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %ap_save, i32 0, i32 0, !dbg !1541
  %call = call i32 @dprintf_formatf(i8* %0, i32 (i32, %struct._IO_FILE*)* @alloc_addbyter, i8* %1, %struct.__va_list_tag* %arraydecay2), !dbg !1542
  store i32 %call, i32* %retcode, align 4, !dbg !1543
  %arraydecay3 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %ap_save, i32 0, i32 0, !dbg !1544
  %arraydecay34 = bitcast %struct.__va_list_tag* %arraydecay3 to i8*, !dbg !1544
  call void @llvm.va_end(i8* %arraydecay34), !dbg !1544
  %2 = load i32, i32* %retcode, align 4, !dbg !1545
  %cmp = icmp eq i32 -1, %2, !dbg !1547
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !1548

lor.lhs.false:                                    ; preds = %entry
  %fail5 = getelementptr inbounds %struct.asprintf, %struct.asprintf* %info, i32 0, i32 3, !dbg !1549
  %3 = load i32, i32* %fail5, align 8, !dbg !1549
  %tobool = icmp ne i32 %3, 0, !dbg !1551
  br i1 %tobool, label %if.then, label %if.end10, !dbg !1552

if.then:                                          ; preds = %lor.lhs.false, %entry
  %alloc6 = getelementptr inbounds %struct.asprintf, %struct.asprintf* %info, i32 0, i32 2, !dbg !1553
  %4 = load i64, i64* %alloc6, align 8, !dbg !1553
  %tobool7 = icmp ne i64 %4, 0, !dbg !1556
  br i1 %tobool7, label %if.then8, label %if.end, !dbg !1557

if.then8:                                         ; preds = %if.then
  %5 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !1558
  %buffer9 = getelementptr inbounds %struct.asprintf, %struct.asprintf* %info, i32 0, i32 0, !dbg !1558
  %6 = load i8*, i8** %buffer9, align 8, !dbg !1558
  call void %5(i8* %6), !dbg !1558
  br label %if.end, !dbg !1558

if.end:                                           ; preds = %if.then8, %if.then
  store i8* null, i8** %retval, align 8, !dbg !1559
  br label %return, !dbg !1559

if.end10:                                         ; preds = %lor.lhs.false
  %alloc11 = getelementptr inbounds %struct.asprintf, %struct.asprintf* %info, i32 0, i32 2, !dbg !1560
  %7 = load i64, i64* %alloc11, align 8, !dbg !1560
  %tobool12 = icmp ne i64 %7, 0, !dbg !1562
  br i1 %tobool12, label %if.then13, label %if.end17, !dbg !1563

if.then13:                                        ; preds = %if.end10
  %len14 = getelementptr inbounds %struct.asprintf, %struct.asprintf* %info, i32 0, i32 1, !dbg !1564
  %8 = load i64, i64* %len14, align 8, !dbg !1564
  %buffer15 = getelementptr inbounds %struct.asprintf, %struct.asprintf* %info, i32 0, i32 0, !dbg !1566
  %9 = load i8*, i8** %buffer15, align 8, !dbg !1566
  %arrayidx = getelementptr inbounds i8, i8* %9, i64 %8, !dbg !1567
  store i8 0, i8* %arrayidx, align 1, !dbg !1568
  %buffer16 = getelementptr inbounds %struct.asprintf, %struct.asprintf* %info, i32 0, i32 0, !dbg !1569
  %10 = load i8*, i8** %buffer16, align 8, !dbg !1569
  store i8* %10, i8** %retval, align 8, !dbg !1570
  br label %return, !dbg !1570

if.end17:                                         ; preds = %if.end10
  %11 = load i8* (i8*)*, i8* (i8*)** @Curl_cstrdup, align 8, !dbg !1571
  %call18 = call i8* %11(i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str, i32 0, i32 0)), !dbg !1571
  store i8* %call18, i8** %retval, align 8, !dbg !1572
  br label %return, !dbg !1572

return:                                           ; preds = %if.end17, %if.then13, %if.end
  %12 = load i8*, i8** %retval, align 8, !dbg !1573
  ret i8* %12, !dbg !1573
}

; Function Attrs: nounwind uwtable
define internal i32 @alloc_addbyter(i32 %output, %struct._IO_FILE* %data) #0 !dbg !219 {
entry:
  %retval = alloca i32, align 4
  %output.addr = alloca i32, align 4
  %data.addr = alloca %struct._IO_FILE*, align 8
  %infop = alloca %struct.asprintf*, align 8
  %outc = alloca i8, align 1
  %newptr = alloca i8*, align 8
  %newsize = alloca i64, align 8
  store i32 %output, i32* %output.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %output.addr, metadata !1574, metadata !236), !dbg !1575
  store %struct._IO_FILE* %data, %struct._IO_FILE** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %data.addr, metadata !1576, metadata !236), !dbg !1577
  call void @llvm.dbg.declare(metadata %struct.asprintf** %infop, metadata !1578, metadata !236), !dbg !1579
  %0 = load %struct._IO_FILE*, %struct._IO_FILE** %data.addr, align 8, !dbg !1580
  %1 = bitcast %struct._IO_FILE* %0 to %struct.asprintf*, !dbg !1581
  store %struct.asprintf* %1, %struct.asprintf** %infop, align 8, !dbg !1579
  call void @llvm.dbg.declare(metadata i8* %outc, metadata !1582, metadata !236), !dbg !1583
  %2 = load i32, i32* %output.addr, align 4, !dbg !1584
  %conv = trunc i32 %2 to i8, !dbg !1585
  store i8 %conv, i8* %outc, align 1, !dbg !1583
  %3 = load %struct.asprintf*, %struct.asprintf** %infop, align 8, !dbg !1586
  %buffer = getelementptr inbounds %struct.asprintf, %struct.asprintf* %3, i32 0, i32 0, !dbg !1588
  %4 = load i8*, i8** %buffer, align 8, !dbg !1588
  %tobool = icmp ne i8* %4, null, !dbg !1586
  br i1 %tobool, label %if.else, label %if.then, !dbg !1589

if.then:                                          ; preds = %entry
  %5 = load i8* (i64)*, i8* (i64)** @Curl_cmalloc, align 8, !dbg !1590
  %call = call i8* %5(i64 32), !dbg !1590
  %6 = load %struct.asprintf*, %struct.asprintf** %infop, align 8, !dbg !1592
  %buffer1 = getelementptr inbounds %struct.asprintf, %struct.asprintf* %6, i32 0, i32 0, !dbg !1593
  store i8* %call, i8** %buffer1, align 8, !dbg !1594
  %7 = load %struct.asprintf*, %struct.asprintf** %infop, align 8, !dbg !1595
  %buffer2 = getelementptr inbounds %struct.asprintf, %struct.asprintf* %7, i32 0, i32 0, !dbg !1597
  %8 = load i8*, i8** %buffer2, align 8, !dbg !1597
  %tobool3 = icmp ne i8* %8, null, !dbg !1595
  br i1 %tobool3, label %if.end, label %if.then4, !dbg !1598

if.then4:                                         ; preds = %if.then
  %9 = load %struct.asprintf*, %struct.asprintf** %infop, align 8, !dbg !1599
  %fail = getelementptr inbounds %struct.asprintf, %struct.asprintf* %9, i32 0, i32 3, !dbg !1601
  store i32 1, i32* %fail, align 8, !dbg !1602
  store i32 -1, i32* %retval, align 4, !dbg !1603
  br label %return, !dbg !1603

if.end:                                           ; preds = %if.then
  %10 = load %struct.asprintf*, %struct.asprintf** %infop, align 8, !dbg !1604
  %alloc = getelementptr inbounds %struct.asprintf, %struct.asprintf* %10, i32 0, i32 2, !dbg !1605
  store i64 32, i64* %alloc, align 8, !dbg !1606
  %11 = load %struct.asprintf*, %struct.asprintf** %infop, align 8, !dbg !1607
  %len = getelementptr inbounds %struct.asprintf, %struct.asprintf* %11, i32 0, i32 1, !dbg !1608
  store i64 0, i64* %len, align 8, !dbg !1609
  br label %if.end24, !dbg !1610

if.else:                                          ; preds = %entry
  %12 = load %struct.asprintf*, %struct.asprintf** %infop, align 8, !dbg !1611
  %len5 = getelementptr inbounds %struct.asprintf, %struct.asprintf* %12, i32 0, i32 1, !dbg !1613
  %13 = load i64, i64* %len5, align 8, !dbg !1613
  %add = add i64 %13, 1, !dbg !1614
  %14 = load %struct.asprintf*, %struct.asprintf** %infop, align 8, !dbg !1615
  %alloc6 = getelementptr inbounds %struct.asprintf, %struct.asprintf* %14, i32 0, i32 2, !dbg !1616
  %15 = load i64, i64* %alloc6, align 8, !dbg !1616
  %cmp = icmp uge i64 %add, %15, !dbg !1617
  br i1 %cmp, label %if.then8, label %if.end23, !dbg !1618

if.then8:                                         ; preds = %if.else
  call void @llvm.dbg.declare(metadata i8** %newptr, metadata !1619, metadata !236), !dbg !1621
  store i8* null, i8** %newptr, align 8, !dbg !1621
  call void @llvm.dbg.declare(metadata i64* %newsize, metadata !1622, metadata !236), !dbg !1623
  %16 = load %struct.asprintf*, %struct.asprintf** %infop, align 8, !dbg !1624
  %alloc9 = getelementptr inbounds %struct.asprintf, %struct.asprintf* %16, i32 0, i32 2, !dbg !1625
  %17 = load i64, i64* %alloc9, align 8, !dbg !1625
  %mul = mul i64 %17, 2, !dbg !1626
  store i64 %mul, i64* %newsize, align 8, !dbg !1623
  %18 = load i64, i64* %newsize, align 8, !dbg !1627
  %19 = load %struct.asprintf*, %struct.asprintf** %infop, align 8, !dbg !1629
  %alloc10 = getelementptr inbounds %struct.asprintf, %struct.asprintf* %19, i32 0, i32 2, !dbg !1630
  %20 = load i64, i64* %alloc10, align 8, !dbg !1630
  %cmp11 = icmp ugt i64 %18, %20, !dbg !1631
  br i1 %cmp11, label %if.then13, label %if.end16, !dbg !1632

if.then13:                                        ; preds = %if.then8
  %21 = load i8* (i8*, i64)*, i8* (i8*, i64)** @Curl_crealloc, align 8, !dbg !1633
  %22 = load %struct.asprintf*, %struct.asprintf** %infop, align 8, !dbg !1633
  %buffer14 = getelementptr inbounds %struct.asprintf, %struct.asprintf* %22, i32 0, i32 0, !dbg !1633
  %23 = load i8*, i8** %buffer14, align 8, !dbg !1633
  %24 = load i64, i64* %newsize, align 8, !dbg !1633
  %call15 = call i8* %21(i8* %23, i64 %24), !dbg !1633
  store i8* %call15, i8** %newptr, align 8, !dbg !1634
  br label %if.end16, !dbg !1635

if.end16:                                         ; preds = %if.then13, %if.then8
  %25 = load i8*, i8** %newptr, align 8, !dbg !1636
  %tobool17 = icmp ne i8* %25, null, !dbg !1636
  br i1 %tobool17, label %if.end20, label %if.then18, !dbg !1638

if.then18:                                        ; preds = %if.end16
  %26 = load %struct.asprintf*, %struct.asprintf** %infop, align 8, !dbg !1639
  %fail19 = getelementptr inbounds %struct.asprintf, %struct.asprintf* %26, i32 0, i32 3, !dbg !1641
  store i32 1, i32* %fail19, align 8, !dbg !1642
  store i32 -1, i32* %retval, align 4, !dbg !1643
  br label %return, !dbg !1643

if.end20:                                         ; preds = %if.end16
  %27 = load i8*, i8** %newptr, align 8, !dbg !1644
  %28 = load %struct.asprintf*, %struct.asprintf** %infop, align 8, !dbg !1645
  %buffer21 = getelementptr inbounds %struct.asprintf, %struct.asprintf* %28, i32 0, i32 0, !dbg !1646
  store i8* %27, i8** %buffer21, align 8, !dbg !1647
  %29 = load i64, i64* %newsize, align 8, !dbg !1648
  %30 = load %struct.asprintf*, %struct.asprintf** %infop, align 8, !dbg !1649
  %alloc22 = getelementptr inbounds %struct.asprintf, %struct.asprintf* %30, i32 0, i32 2, !dbg !1650
  store i64 %29, i64* %alloc22, align 8, !dbg !1651
  br label %if.end23, !dbg !1652

if.end23:                                         ; preds = %if.end20, %if.else
  br label %if.end24

if.end24:                                         ; preds = %if.end23, %if.end
  %31 = load i8, i8* %outc, align 1, !dbg !1653
  %32 = load %struct.asprintf*, %struct.asprintf** %infop, align 8, !dbg !1654
  %len25 = getelementptr inbounds %struct.asprintf, %struct.asprintf* %32, i32 0, i32 1, !dbg !1655
  %33 = load i64, i64* %len25, align 8, !dbg !1655
  %34 = load %struct.asprintf*, %struct.asprintf** %infop, align 8, !dbg !1656
  %buffer26 = getelementptr inbounds %struct.asprintf, %struct.asprintf* %34, i32 0, i32 0, !dbg !1657
  %35 = load i8*, i8** %buffer26, align 8, !dbg !1657
  %arrayidx = getelementptr inbounds i8, i8* %35, i64 %33, !dbg !1656
  store i8 %31, i8* %arrayidx, align 1, !dbg !1658
  %36 = load %struct.asprintf*, %struct.asprintf** %infop, align 8, !dbg !1659
  %len27 = getelementptr inbounds %struct.asprintf, %struct.asprintf* %36, i32 0, i32 1, !dbg !1660
  %37 = load i64, i64* %len27, align 8, !dbg !1661
  %inc = add i64 %37, 1, !dbg !1661
  store i64 %inc, i64* %len27, align 8, !dbg !1661
  %38 = load i8, i8* %outc, align 1, !dbg !1662
  %conv28 = zext i8 %38 to i32, !dbg !1662
  store i32 %conv28, i32* %retval, align 4, !dbg !1663
  br label %return, !dbg !1663

return:                                           ; preds = %if.end24, %if.then18, %if.then4
  %39 = load i32, i32* %retval, align 4, !dbg !1664
  ret i32 %39, !dbg !1664
}

; Function Attrs: nounwind uwtable
define i8* @curl_mvaprintf(i8* %format, %struct.__va_list_tag* %ap_save) #0 !dbg !160 {
entry:
  %retval = alloca i8*, align 8
  %format.addr = alloca i8*, align 8
  %ap_save.addr = alloca %struct.__va_list_tag*, align 8
  %retcode = alloca i32, align 4
  %info = alloca %struct.asprintf, align 8
  store i8* %format, i8** %format.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %format.addr, metadata !1665, metadata !236), !dbg !1666
  store %struct.__va_list_tag* %ap_save, %struct.__va_list_tag** %ap_save.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.__va_list_tag** %ap_save.addr, metadata !1667, metadata !236), !dbg !1668
  call void @llvm.dbg.declare(metadata i32* %retcode, metadata !1669, metadata !236), !dbg !1670
  call void @llvm.dbg.declare(metadata %struct.asprintf* %info, metadata !1671, metadata !236), !dbg !1672
  %buffer = getelementptr inbounds %struct.asprintf, %struct.asprintf* %info, i32 0, i32 0, !dbg !1673
  store i8* null, i8** %buffer, align 8, !dbg !1674
  %len = getelementptr inbounds %struct.asprintf, %struct.asprintf* %info, i32 0, i32 1, !dbg !1675
  store i64 0, i64* %len, align 8, !dbg !1676
  %alloc = getelementptr inbounds %struct.asprintf, %struct.asprintf* %info, i32 0, i32 2, !dbg !1677
  store i64 0, i64* %alloc, align 8, !dbg !1678
  %fail = getelementptr inbounds %struct.asprintf, %struct.asprintf* %info, i32 0, i32 3, !dbg !1679
  store i32 0, i32* %fail, align 8, !dbg !1680
  %0 = bitcast %struct.asprintf* %info to i8*, !dbg !1681
  %1 = load i8*, i8** %format.addr, align 8, !dbg !1682
  %2 = load %struct.__va_list_tag*, %struct.__va_list_tag** %ap_save.addr, align 8, !dbg !1683
  %call = call i32 @dprintf_formatf(i8* %0, i32 (i32, %struct._IO_FILE*)* @alloc_addbyter, i8* %1, %struct.__va_list_tag* %2), !dbg !1684
  store i32 %call, i32* %retcode, align 4, !dbg !1685
  %3 = load i32, i32* %retcode, align 4, !dbg !1686
  %cmp = icmp eq i32 -1, %3, !dbg !1688
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !1689

lor.lhs.false:                                    ; preds = %entry
  %fail1 = getelementptr inbounds %struct.asprintf, %struct.asprintf* %info, i32 0, i32 3, !dbg !1690
  %4 = load i32, i32* %fail1, align 8, !dbg !1690
  %tobool = icmp ne i32 %4, 0, !dbg !1692
  br i1 %tobool, label %if.then, label %if.end6, !dbg !1693

if.then:                                          ; preds = %lor.lhs.false, %entry
  %alloc2 = getelementptr inbounds %struct.asprintf, %struct.asprintf* %info, i32 0, i32 2, !dbg !1694
  %5 = load i64, i64* %alloc2, align 8, !dbg !1694
  %tobool3 = icmp ne i64 %5, 0, !dbg !1697
  br i1 %tobool3, label %if.then4, label %if.end, !dbg !1698

if.then4:                                         ; preds = %if.then
  %6 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !1699
  %buffer5 = getelementptr inbounds %struct.asprintf, %struct.asprintf* %info, i32 0, i32 0, !dbg !1699
  %7 = load i8*, i8** %buffer5, align 8, !dbg !1699
  call void %6(i8* %7), !dbg !1699
  br label %if.end, !dbg !1699

if.end:                                           ; preds = %if.then4, %if.then
  store i8* null, i8** %retval, align 8, !dbg !1700
  br label %return, !dbg !1700

if.end6:                                          ; preds = %lor.lhs.false
  %alloc7 = getelementptr inbounds %struct.asprintf, %struct.asprintf* %info, i32 0, i32 2, !dbg !1701
  %8 = load i64, i64* %alloc7, align 8, !dbg !1701
  %tobool8 = icmp ne i64 %8, 0, !dbg !1703
  br i1 %tobool8, label %if.then9, label %if.end13, !dbg !1704

if.then9:                                         ; preds = %if.end6
  %len10 = getelementptr inbounds %struct.asprintf, %struct.asprintf* %info, i32 0, i32 1, !dbg !1705
  %9 = load i64, i64* %len10, align 8, !dbg !1705
  %buffer11 = getelementptr inbounds %struct.asprintf, %struct.asprintf* %info, i32 0, i32 0, !dbg !1707
  %10 = load i8*, i8** %buffer11, align 8, !dbg !1707
  %arrayidx = getelementptr inbounds i8, i8* %10, i64 %9, !dbg !1708
  store i8 0, i8* %arrayidx, align 1, !dbg !1709
  %buffer12 = getelementptr inbounds %struct.asprintf, %struct.asprintf* %info, i32 0, i32 0, !dbg !1710
  %11 = load i8*, i8** %buffer12, align 8, !dbg !1710
  store i8* %11, i8** %retval, align 8, !dbg !1711
  br label %return, !dbg !1711

if.end13:                                         ; preds = %if.end6
  %12 = load i8* (i8*)*, i8* (i8*)** @Curl_cstrdup, align 8, !dbg !1712
  %call14 = call i8* %12(i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str, i32 0, i32 0)), !dbg !1712
  store i8* %call14, i8** %retval, align 8, !dbg !1713
  br label %return, !dbg !1713

return:                                           ; preds = %if.end13, %if.then9, %if.end
  %13 = load i8*, i8** %retval, align 8, !dbg !1714
  ret i8* %13, !dbg !1714
}

; Function Attrs: nounwind uwtable
define i32 @curl_msprintf(i8* %buffer, i8* %format, ...) #0 !dbg !163 {
entry:
  %buffer.addr = alloca i8*, align 8
  %format.addr = alloca i8*, align 8
  %ap_save = alloca [1 x %struct.__va_list_tag], align 16
  %retcode = alloca i32, align 4
  store i8* %buffer, i8** %buffer.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buffer.addr, metadata !1715, metadata !236), !dbg !1716
  store i8* %format, i8** %format.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %format.addr, metadata !1717, metadata !236), !dbg !1718
  call void @llvm.dbg.declare(metadata [1 x %struct.__va_list_tag]* %ap_save, metadata !1719, metadata !236), !dbg !1720
  call void @llvm.dbg.declare(metadata i32* %retcode, metadata !1721, metadata !236), !dbg !1722
  %arraydecay = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %ap_save, i32 0, i32 0, !dbg !1723
  %arraydecay1 = bitcast %struct.__va_list_tag* %arraydecay to i8*, !dbg !1723
  call void @llvm.va_start(i8* %arraydecay1), !dbg !1723
  %0 = bitcast i8** %buffer.addr to i8*, !dbg !1724
  %1 = load i8*, i8** %format.addr, align 8, !dbg !1725
  %arraydecay2 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %ap_save, i32 0, i32 0, !dbg !1726
  %call = call i32 @dprintf_formatf(i8* %0, i32 (i32, %struct._IO_FILE*)* @storebuffer, i8* %1, %struct.__va_list_tag* %arraydecay2), !dbg !1727
  store i32 %call, i32* %retcode, align 4, !dbg !1728
  %arraydecay3 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %ap_save, i32 0, i32 0, !dbg !1729
  %arraydecay34 = bitcast %struct.__va_list_tag* %arraydecay3 to i8*, !dbg !1729
  call void @llvm.va_end(i8* %arraydecay34), !dbg !1729
  %2 = load i8*, i8** %buffer.addr, align 8, !dbg !1730
  store i8 0, i8* %2, align 1, !dbg !1731
  %3 = load i32, i32* %retcode, align 4, !dbg !1732
  ret i32 %3, !dbg !1733
}

; Function Attrs: nounwind uwtable
define internal i32 @storebuffer(i32 %output, %struct._IO_FILE* %data) #0 !dbg !220 {
entry:
  %output.addr = alloca i32, align 4
  %data.addr = alloca %struct._IO_FILE*, align 8
  %buffer = alloca i8**, align 8
  %outc = alloca i8, align 1
  store i32 %output, i32* %output.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %output.addr, metadata !1734, metadata !236), !dbg !1735
  store %struct._IO_FILE* %data, %struct._IO_FILE** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %data.addr, metadata !1736, metadata !236), !dbg !1737
  call void @llvm.dbg.declare(metadata i8*** %buffer, metadata !1738, metadata !236), !dbg !1739
  %0 = load %struct._IO_FILE*, %struct._IO_FILE** %data.addr, align 8, !dbg !1740
  %1 = bitcast %struct._IO_FILE* %0 to i8**, !dbg !1741
  store i8** %1, i8*** %buffer, align 8, !dbg !1739
  call void @llvm.dbg.declare(metadata i8* %outc, metadata !1742, metadata !236), !dbg !1743
  %2 = load i32, i32* %output.addr, align 4, !dbg !1744
  %conv = trunc i32 %2 to i8, !dbg !1745
  store i8 %conv, i8* %outc, align 1, !dbg !1743
  %3 = load i8, i8* %outc, align 1, !dbg !1746
  %4 = load i8**, i8*** %buffer, align 8, !dbg !1747
  %5 = load i8*, i8** %4, align 8, !dbg !1748
  store i8 %3, i8* %5, align 1, !dbg !1749
  %6 = load i8**, i8*** %buffer, align 8, !dbg !1750
  %7 = load i8*, i8** %6, align 8, !dbg !1751
  %incdec.ptr = getelementptr inbounds i8, i8* %7, i32 1, !dbg !1751
  store i8* %incdec.ptr, i8** %6, align 8, !dbg !1751
  %8 = load i8, i8* %outc, align 1, !dbg !1752
  %conv1 = zext i8 %8 to i32, !dbg !1752
  ret i32 %conv1, !dbg !1753
}

; Function Attrs: nounwind uwtable
define i32 @curl_mprintf(i8* %format, ...) #0 !dbg !166 {
entry:
  %format.addr = alloca i8*, align 8
  %retcode = alloca i32, align 4
  %ap_save = alloca [1 x %struct.__va_list_tag], align 16
  store i8* %format, i8** %format.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %format.addr, metadata !1754, metadata !236), !dbg !1755
  call void @llvm.dbg.declare(metadata i32* %retcode, metadata !1756, metadata !236), !dbg !1757
  call void @llvm.dbg.declare(metadata [1 x %struct.__va_list_tag]* %ap_save, metadata !1758, metadata !236), !dbg !1759
  %arraydecay = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %ap_save, i32 0, i32 0, !dbg !1760
  %arraydecay1 = bitcast %struct.__va_list_tag* %arraydecay to i8*, !dbg !1760
  call void @llvm.va_start(i8* %arraydecay1), !dbg !1760
  %0 = load %struct._IO_FILE*, %struct._IO_FILE** @stdout, align 8, !dbg !1761
  %1 = bitcast %struct._IO_FILE* %0 to i8*, !dbg !1761
  %2 = load i8*, i8** %format.addr, align 8, !dbg !1762
  %arraydecay2 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %ap_save, i32 0, i32 0, !dbg !1763
  %call = call i32 @dprintf_formatf(i8* %1, i32 (i32, %struct._IO_FILE*)* @fputc, i8* %2, %struct.__va_list_tag* %arraydecay2), !dbg !1764
  store i32 %call, i32* %retcode, align 4, !dbg !1765
  %arraydecay3 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %ap_save, i32 0, i32 0, !dbg !1766
  %arraydecay34 = bitcast %struct.__va_list_tag* %arraydecay3 to i8*, !dbg !1766
  call void @llvm.va_end(i8* %arraydecay34), !dbg !1766
  %3 = load i32, i32* %retcode, align 4, !dbg !1767
  ret i32 %3, !dbg !1768
}

declare i32 @fputc(i32, %struct._IO_FILE*) #3

; Function Attrs: nounwind uwtable
define i32 @curl_mfprintf(%struct._IO_FILE* %whereto, i8* %format, ...) #0 !dbg !169 {
entry:
  %whereto.addr = alloca %struct._IO_FILE*, align 8
  %format.addr = alloca i8*, align 8
  %retcode = alloca i32, align 4
  %ap_save = alloca [1 x %struct.__va_list_tag], align 16
  store %struct._IO_FILE* %whereto, %struct._IO_FILE** %whereto.addr, align 8
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %whereto.addr, metadata !1769, metadata !236), !dbg !1770
  store i8* %format, i8** %format.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %format.addr, metadata !1771, metadata !236), !dbg !1772
  call void @llvm.dbg.declare(metadata i32* %retcode, metadata !1773, metadata !236), !dbg !1774
  call void @llvm.dbg.declare(metadata [1 x %struct.__va_list_tag]* %ap_save, metadata !1775, metadata !236), !dbg !1776
  %arraydecay = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %ap_save, i32 0, i32 0, !dbg !1777
  %arraydecay1 = bitcast %struct.__va_list_tag* %arraydecay to i8*, !dbg !1777
  call void @llvm.va_start(i8* %arraydecay1), !dbg !1777
  %0 = load %struct._IO_FILE*, %struct._IO_FILE** %whereto.addr, align 8, !dbg !1778
  %1 = bitcast %struct._IO_FILE* %0 to i8*, !dbg !1778
  %2 = load i8*, i8** %format.addr, align 8, !dbg !1779
  %arraydecay2 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %ap_save, i32 0, i32 0, !dbg !1780
  %call = call i32 @dprintf_formatf(i8* %1, i32 (i32, %struct._IO_FILE*)* @fputc, i8* %2, %struct.__va_list_tag* %arraydecay2), !dbg !1781
  store i32 %call, i32* %retcode, align 4, !dbg !1782
  %arraydecay3 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %ap_save, i32 0, i32 0, !dbg !1783
  %arraydecay34 = bitcast %struct.__va_list_tag* %arraydecay3 to i8*, !dbg !1783
  call void @llvm.va_end(i8* %arraydecay34), !dbg !1783
  %3 = load i32, i32* %retcode, align 4, !dbg !1784
  ret i32 %3, !dbg !1785
}

; Function Attrs: nounwind uwtable
define i32 @curl_mvsprintf(i8* %buffer, i8* %format, %struct.__va_list_tag* %ap_save) #0 !dbg !172 {
entry:
  %buffer.addr = alloca i8*, align 8
  %format.addr = alloca i8*, align 8
  %ap_save.addr = alloca %struct.__va_list_tag*, align 8
  %retcode = alloca i32, align 4
  store i8* %buffer, i8** %buffer.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buffer.addr, metadata !1786, metadata !236), !dbg !1787
  store i8* %format, i8** %format.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %format.addr, metadata !1788, metadata !236), !dbg !1789
  store %struct.__va_list_tag* %ap_save, %struct.__va_list_tag** %ap_save.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.__va_list_tag** %ap_save.addr, metadata !1790, metadata !236), !dbg !1791
  call void @llvm.dbg.declare(metadata i32* %retcode, metadata !1792, metadata !236), !dbg !1793
  %0 = bitcast i8** %buffer.addr to i8*, !dbg !1794
  %1 = load i8*, i8** %format.addr, align 8, !dbg !1795
  %2 = load %struct.__va_list_tag*, %struct.__va_list_tag** %ap_save.addr, align 8, !dbg !1796
  %call = call i32 @dprintf_formatf(i8* %0, i32 (i32, %struct._IO_FILE*)* @storebuffer, i8* %1, %struct.__va_list_tag* %2), !dbg !1797
  store i32 %call, i32* %retcode, align 4, !dbg !1798
  %3 = load i8*, i8** %buffer.addr, align 8, !dbg !1799
  store i8 0, i8* %3, align 1, !dbg !1800
  %4 = load i32, i32* %retcode, align 4, !dbg !1801
  ret i32 %4, !dbg !1802
}

; Function Attrs: nounwind uwtable
define i32 @curl_mvprintf(i8* %format, %struct.__va_list_tag* %ap_save) #0 !dbg !175 {
entry:
  %format.addr = alloca i8*, align 8
  %ap_save.addr = alloca %struct.__va_list_tag*, align 8
  store i8* %format, i8** %format.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %format.addr, metadata !1803, metadata !236), !dbg !1804
  store %struct.__va_list_tag* %ap_save, %struct.__va_list_tag** %ap_save.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.__va_list_tag** %ap_save.addr, metadata !1805, metadata !236), !dbg !1806
  %0 = load %struct._IO_FILE*, %struct._IO_FILE** @stdout, align 8, !dbg !1807
  %1 = bitcast %struct._IO_FILE* %0 to i8*, !dbg !1807
  %2 = load i8*, i8** %format.addr, align 8, !dbg !1808
  %3 = load %struct.__va_list_tag*, %struct.__va_list_tag** %ap_save.addr, align 8, !dbg !1809
  %call = call i32 @dprintf_formatf(i8* %1, i32 (i32, %struct._IO_FILE*)* @fputc, i8* %2, %struct.__va_list_tag* %3), !dbg !1810
  ret i32 %call, !dbg !1811
}

; Function Attrs: nounwind uwtable
define i32 @curl_mvfprintf(%struct._IO_FILE* %whereto, i8* %format, %struct.__va_list_tag* %ap_save) #0 !dbg !178 {
entry:
  %whereto.addr = alloca %struct._IO_FILE*, align 8
  %format.addr = alloca i8*, align 8
  %ap_save.addr = alloca %struct.__va_list_tag*, align 8
  store %struct._IO_FILE* %whereto, %struct._IO_FILE** %whereto.addr, align 8
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %whereto.addr, metadata !1812, metadata !236), !dbg !1813
  store i8* %format, i8** %format.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %format.addr, metadata !1814, metadata !236), !dbg !1815
  store %struct.__va_list_tag* %ap_save, %struct.__va_list_tag** %ap_save.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.__va_list_tag** %ap_save.addr, metadata !1816, metadata !236), !dbg !1817
  %0 = load %struct._IO_FILE*, %struct._IO_FILE** %whereto.addr, align 8, !dbg !1818
  %1 = bitcast %struct._IO_FILE* %0 to i8*, !dbg !1818
  %2 = load i8*, i8** %format.addr, align 8, !dbg !1819
  %3 = load %struct.__va_list_tag*, %struct.__va_list_tag** %ap_save.addr, align 8, !dbg !1820
  %call = call i32 @dprintf_formatf(i8* %1, i32 (i32, %struct._IO_FILE*)* @fputc, i8* %2, %struct.__va_list_tag* %3), !dbg !1821
  ret i32 %call, !dbg !1822
}

; Function Attrs: nounwind uwtable
define internal i32 @dprintf_Pass1(i8* %format, %struct.va_stack_t* %vto, i8** %endpos, %struct.__va_list_tag* %arglist) #0 !dbg !187 {
entry:
  %retval = alloca i32, align 4
  %format.addr = alloca i8*, align 8
  %vto.addr = alloca %struct.va_stack_t*, align 8
  %endpos.addr = alloca i8**, align 8
  %arglist.addr = alloca %struct.__va_list_tag*, align 8
  %fmt = alloca i8*, align 8
  %param_num = alloca i32, align 4
  %this_param = alloca i64, align 8
  %width = alloca i64, align 8
  %precision = alloca i64, align 8
  %flags = alloca i32, align 4
  %max_param = alloca i64, align 8
  %i = alloca i64, align 8
  %k = alloca i64, align 8
  %k174 = alloca i64, align 8
  store i8* %format, i8** %format.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %format.addr, metadata !1823, metadata !236), !dbg !1824
  store %struct.va_stack_t* %vto, %struct.va_stack_t** %vto.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.va_stack_t** %vto.addr, metadata !1825, metadata !236), !dbg !1826
  store i8** %endpos, i8*** %endpos.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %endpos.addr, metadata !1827, metadata !236), !dbg !1828
  store %struct.__va_list_tag* %arglist, %struct.__va_list_tag** %arglist.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.__va_list_tag** %arglist.addr, metadata !1829, metadata !236), !dbg !1830
  call void @llvm.dbg.declare(metadata i8** %fmt, metadata !1831, metadata !236), !dbg !1832
  %0 = load i8*, i8** %format.addr, align 8, !dbg !1833
  store i8* %0, i8** %fmt, align 8, !dbg !1832
  call void @llvm.dbg.declare(metadata i32* %param_num, metadata !1834, metadata !236), !dbg !1835
  store i32 0, i32* %param_num, align 4, !dbg !1835
  call void @llvm.dbg.declare(metadata i64* %this_param, metadata !1836, metadata !236), !dbg !1837
  call void @llvm.dbg.declare(metadata i64* %width, metadata !1838, metadata !236), !dbg !1839
  call void @llvm.dbg.declare(metadata i64* %precision, metadata !1840, metadata !236), !dbg !1841
  call void @llvm.dbg.declare(metadata i32* %flags, metadata !1842, metadata !236), !dbg !1843
  call void @llvm.dbg.declare(metadata i64* %max_param, metadata !1844, metadata !236), !dbg !1845
  store i64 0, i64* %max_param, align 8, !dbg !1845
  call void @llvm.dbg.declare(metadata i64* %i, metadata !1846, metadata !236), !dbg !1847
  br label %while.cond, !dbg !1848

while.cond:                                       ; preds = %if.end189, %if.then5, %entry
  %1 = load i8*, i8** %fmt, align 8, !dbg !1849
  %2 = load i8, i8* %1, align 1, !dbg !1851
  %tobool = icmp ne i8 %2, 0, !dbg !1852
  br i1 %tobool, label %while.body, label %while.end190, !dbg !1852

while.body:                                       ; preds = %while.cond
  %3 = load i8*, i8** %fmt, align 8, !dbg !1853
  %incdec.ptr = getelementptr inbounds i8, i8* %3, i32 1, !dbg !1853
  store i8* %incdec.ptr, i8** %fmt, align 8, !dbg !1853
  %4 = load i8, i8* %3, align 1, !dbg !1856
  %conv = sext i8 %4 to i32, !dbg !1856
  %cmp = icmp eq i32 %conv, 37, !dbg !1857
  br i1 %cmp, label %if.then, label %if.end189, !dbg !1858

if.then:                                          ; preds = %while.body
  %5 = load i8*, i8** %fmt, align 8, !dbg !1859
  %6 = load i8, i8* %5, align 1, !dbg !1862
  %conv2 = sext i8 %6 to i32, !dbg !1862
  %cmp3 = icmp eq i32 %conv2, 37, !dbg !1863
  br i1 %cmp3, label %if.then5, label %if.end, !dbg !1864

if.then5:                                         ; preds = %if.then
  %7 = load i8*, i8** %fmt, align 8, !dbg !1865
  %incdec.ptr6 = getelementptr inbounds i8, i8* %7, i32 1, !dbg !1865
  store i8* %incdec.ptr6, i8** %fmt, align 8, !dbg !1865
  br label %while.cond, !dbg !1867

if.end:                                           ; preds = %if.then
  store i32 0, i32* %flags, align 4, !dbg !1868
  %8 = load i32, i32* %param_num, align 4, !dbg !1869
  %inc = add nsw i32 %8, 1, !dbg !1869
  store i32 %inc, i32* %param_num, align 4, !dbg !1869
  %9 = load i8*, i8** %fmt, align 8, !dbg !1870
  %call = call i64 @dprintf_DollarString(i8* %9, i8** %fmt), !dbg !1871
  store i64 %call, i64* %this_param, align 8, !dbg !1872
  %10 = load i64, i64* %this_param, align 8, !dbg !1873
  %cmp7 = icmp eq i64 0, %10, !dbg !1875
  br i1 %cmp7, label %if.then9, label %if.end11, !dbg !1876

if.then9:                                         ; preds = %if.end
  %11 = load i32, i32* %param_num, align 4, !dbg !1877
  %conv10 = sext i32 %11 to i64, !dbg !1877
  store i64 %conv10, i64* %this_param, align 8, !dbg !1878
  br label %if.end11, !dbg !1879

if.end11:                                         ; preds = %if.then9, %if.end
  %12 = load i64, i64* %this_param, align 8, !dbg !1880
  %13 = load i64, i64* %max_param, align 8, !dbg !1882
  %cmp12 = icmp sgt i64 %12, %13, !dbg !1883
  br i1 %cmp12, label %if.then14, label %if.end15, !dbg !1884

if.then14:                                        ; preds = %if.end11
  %14 = load i64, i64* %this_param, align 8, !dbg !1885
  store i64 %14, i64* %max_param, align 8, !dbg !1886
  br label %if.end15, !dbg !1887

if.end15:                                         ; preds = %if.then14, %if.end11
  store i64 0, i64* %width, align 8, !dbg !1888
  store i64 0, i64* %precision, align 8, !dbg !1889
  br label %while.cond16, !dbg !1890

while.cond16:                                     ; preds = %sw.epilog, %if.end15
  %15 = load i8*, i8** %fmt, align 8, !dbg !1891
  %call17 = call zeroext i1 @dprintf_IsQualifierNoDollar(i8* %15), !dbg !1893
  br i1 %call17, label %while.body18, label %while.end, !dbg !1894

while.body18:                                     ; preds = %while.cond16
  %16 = load i8*, i8** %fmt, align 8, !dbg !1895
  %incdec.ptr19 = getelementptr inbounds i8, i8* %16, i32 1, !dbg !1895
  store i8* %incdec.ptr19, i8** %fmt, align 8, !dbg !1895
  %17 = load i8, i8* %16, align 1, !dbg !1897
  %conv20 = sext i8 %17 to i32, !dbg !1897
  switch i32 %conv20, label %sw.default [
    i32 32, label %sw.bb
    i32 43, label %sw.bb21
    i32 45, label %sw.bb23
    i32 35, label %sw.bb25
    i32 46, label %sw.bb27
    i32 104, label %sw.bb48
    i32 108, label %sw.bb50
    i32 76, label %sw.bb58
    i32 113, label %sw.bb60
    i32 122, label %sw.bb62
    i32 79, label %sw.bb64
    i32 48, label %sw.bb66
    i32 49, label %sw.bb72
    i32 50, label %sw.bb72
    i32 51, label %sw.bb72
    i32 52, label %sw.bb72
    i32 53, label %sw.bb72
    i32 54, label %sw.bb72
    i32 55, label %sw.bb72
    i32 56, label %sw.bb72
    i32 57, label %sw.bb72
    i32 42, label %sw.bb75
  ], !dbg !1898

sw.bb:                                            ; preds = %while.body18
  %18 = load i32, i32* %flags, align 4, !dbg !1899
  %or = or i32 %18, 1, !dbg !1899
  store i32 %or, i32* %flags, align 4, !dbg !1899
  br label %sw.epilog, !dbg !1901

sw.bb21:                                          ; preds = %while.body18
  %19 = load i32, i32* %flags, align 4, !dbg !1902
  %or22 = or i32 %19, 2, !dbg !1902
  store i32 %or22, i32* %flags, align 4, !dbg !1902
  br label %sw.epilog, !dbg !1903

sw.bb23:                                          ; preds = %while.body18
  %20 = load i32, i32* %flags, align 4, !dbg !1904
  %or24 = or i32 %20, 4, !dbg !1904
  store i32 %or24, i32* %flags, align 4, !dbg !1904
  %21 = load i32, i32* %flags, align 4, !dbg !1905
  %and = and i32 %21, -257, !dbg !1905
  store i32 %and, i32* %flags, align 4, !dbg !1905
  br label %sw.epilog, !dbg !1906

sw.bb25:                                          ; preds = %while.body18
  %22 = load i32, i32* %flags, align 4, !dbg !1907
  %or26 = or i32 %22, 8, !dbg !1907
  store i32 %or26, i32* %flags, align 4, !dbg !1907
  br label %sw.epilog, !dbg !1908

sw.bb27:                                          ; preds = %while.body18
  %23 = load i8*, i8** %fmt, align 8, !dbg !1909
  %24 = load i8, i8* %23, align 1, !dbg !1911
  %conv28 = sext i8 %24 to i32, !dbg !1911
  %cmp29 = icmp eq i32 42, %conv28, !dbg !1912
  br i1 %cmp29, label %if.then31, label %if.else44, !dbg !1913

if.then31:                                        ; preds = %sw.bb27
  %25 = load i32, i32* %flags, align 4, !dbg !1914
  %or32 = or i32 %25, 65536, !dbg !1914
  store i32 %or32, i32* %flags, align 4, !dbg !1914
  %26 = load i8*, i8** %fmt, align 8, !dbg !1916
  %incdec.ptr33 = getelementptr inbounds i8, i8* %26, i32 1, !dbg !1916
  store i8* %incdec.ptr33, i8** %fmt, align 8, !dbg !1916
  %27 = load i32, i32* %param_num, align 4, !dbg !1917
  %inc34 = add nsw i32 %27, 1, !dbg !1917
  store i32 %inc34, i32* %param_num, align 4, !dbg !1917
  %28 = load i8*, i8** %fmt, align 8, !dbg !1918
  %call35 = call i64 @dprintf_DollarString(i8* %28, i8** %fmt), !dbg !1919
  store i64 %call35, i64* %i, align 8, !dbg !1920
  %29 = load i64, i64* %i, align 8, !dbg !1921
  %tobool36 = icmp ne i64 %29, 0, !dbg !1921
  br i1 %tobool36, label %if.then37, label %if.else, !dbg !1923

if.then37:                                        ; preds = %if.then31
  %30 = load i64, i64* %i, align 8, !dbg !1924
  store i64 %30, i64* %precision, align 8, !dbg !1925
  br label %if.end39, !dbg !1926

if.else:                                          ; preds = %if.then31
  %31 = load i32, i32* %param_num, align 4, !dbg !1927
  %conv38 = sext i32 %31 to i64, !dbg !1927
  store i64 %conv38, i64* %precision, align 8, !dbg !1928
  br label %if.end39

if.end39:                                         ; preds = %if.else, %if.then37
  %32 = load i64, i64* %precision, align 8, !dbg !1929
  %33 = load i64, i64* %max_param, align 8, !dbg !1931
  %cmp40 = icmp sgt i64 %32, %33, !dbg !1932
  br i1 %cmp40, label %if.then42, label %if.end43, !dbg !1933

if.then42:                                        ; preds = %if.end39
  %34 = load i64, i64* %precision, align 8, !dbg !1934
  store i64 %34, i64* %max_param, align 8, !dbg !1935
  br label %if.end43, !dbg !1936

if.end43:                                         ; preds = %if.then42, %if.end39
  br label %if.end47, !dbg !1937

if.else44:                                        ; preds = %sw.bb27
  %35 = load i32, i32* %flags, align 4, !dbg !1938
  %or45 = or i32 %35, 32768, !dbg !1938
  store i32 %or45, i32* %flags, align 4, !dbg !1938
  %36 = load i8*, i8** %fmt, align 8, !dbg !1940
  %call46 = call i64 @strtol(i8* %36, i8** %fmt, i32 10) #2, !dbg !1941
  store i64 %call46, i64* %precision, align 8, !dbg !1942
  br label %if.end47

if.end47:                                         ; preds = %if.else44, %if.end43
  br label %sw.epilog, !dbg !1943

sw.bb48:                                          ; preds = %while.body18
  %37 = load i32, i32* %flags, align 4, !dbg !1944
  %or49 = or i32 %37, 16, !dbg !1944
  store i32 %or49, i32* %flags, align 4, !dbg !1944
  br label %sw.epilog, !dbg !1945

sw.bb50:                                          ; preds = %while.body18
  %38 = load i32, i32* %flags, align 4, !dbg !1946
  %and51 = and i32 %38, 32, !dbg !1948
  %tobool52 = icmp ne i32 %and51, 0, !dbg !1948
  br i1 %tobool52, label %if.then53, label %if.else55, !dbg !1949

if.then53:                                        ; preds = %sw.bb50
  %39 = load i32, i32* %flags, align 4, !dbg !1950
  %or54 = or i32 %39, 64, !dbg !1950
  store i32 %or54, i32* %flags, align 4, !dbg !1950
  br label %if.end57, !dbg !1951

if.else55:                                        ; preds = %sw.bb50
  %40 = load i32, i32* %flags, align 4, !dbg !1952
  %or56 = or i32 %40, 32, !dbg !1952
  store i32 %or56, i32* %flags, align 4, !dbg !1952
  br label %if.end57

if.end57:                                         ; preds = %if.else55, %if.then53
  br label %sw.epilog, !dbg !1953

sw.bb58:                                          ; preds = %while.body18
  %41 = load i32, i32* %flags, align 4, !dbg !1954
  %or59 = or i32 %41, 128, !dbg !1954
  store i32 %or59, i32* %flags, align 4, !dbg !1954
  br label %sw.epilog, !dbg !1955

sw.bb60:                                          ; preds = %while.body18
  %42 = load i32, i32* %flags, align 4, !dbg !1956
  %or61 = or i32 %42, 64, !dbg !1956
  store i32 %or61, i32* %flags, align 4, !dbg !1956
  br label %sw.epilog, !dbg !1957

sw.bb62:                                          ; preds = %while.body18
  %43 = load i32, i32* %flags, align 4, !dbg !1958
  %or63 = or i32 %43, 32, !dbg !1958
  store i32 %or63, i32* %flags, align 4, !dbg !1958
  br label %sw.epilog, !dbg !1959

sw.bb64:                                          ; preds = %while.body18
  %44 = load i32, i32* %flags, align 4, !dbg !1960
  %or65 = or i32 %44, 32, !dbg !1960
  store i32 %or65, i32* %flags, align 4, !dbg !1960
  br label %sw.epilog, !dbg !1961

sw.bb66:                                          ; preds = %while.body18
  %45 = load i32, i32* %flags, align 4, !dbg !1962
  %and67 = and i32 %45, 4, !dbg !1964
  %tobool68 = icmp ne i32 %and67, 0, !dbg !1964
  br i1 %tobool68, label %if.end71, label %if.then69, !dbg !1965

if.then69:                                        ; preds = %sw.bb66
  %46 = load i32, i32* %flags, align 4, !dbg !1966
  %or70 = or i32 %46, 256, !dbg !1966
  store i32 %or70, i32* %flags, align 4, !dbg !1966
  br label %if.end71, !dbg !1967

if.end71:                                         ; preds = %if.then69, %sw.bb66
  br label %sw.bb72, !dbg !1968

sw.bb72:                                          ; preds = %while.body18, %while.body18, %while.body18, %while.body18, %while.body18, %while.body18, %while.body18, %while.body18, %while.body18, %if.end71
  %47 = load i32, i32* %flags, align 4, !dbg !1970
  %or73 = or i32 %47, 8192, !dbg !1970
  store i32 %or73, i32* %flags, align 4, !dbg !1970
  %48 = load i8*, i8** %fmt, align 8, !dbg !1971
  %add.ptr = getelementptr inbounds i8, i8* %48, i64 -1, !dbg !1972
  %call74 = call i64 @strtol(i8* %add.ptr, i8** %fmt, i32 10) #2, !dbg !1973
  store i64 %call74, i64* %width, align 8, !dbg !1974
  br label %sw.epilog, !dbg !1975

sw.bb75:                                          ; preds = %while.body18
  %49 = load i32, i32* %flags, align 4, !dbg !1976
  %or76 = or i32 %49, 16384, !dbg !1976
  store i32 %or76, i32* %flags, align 4, !dbg !1976
  %50 = load i32, i32* %param_num, align 4, !dbg !1977
  %inc77 = add nsw i32 %50, 1, !dbg !1977
  store i32 %inc77, i32* %param_num, align 4, !dbg !1977
  %51 = load i8*, i8** %fmt, align 8, !dbg !1978
  %call78 = call i64 @dprintf_DollarString(i8* %51, i8** %fmt), !dbg !1979
  store i64 %call78, i64* %i, align 8, !dbg !1980
  %52 = load i64, i64* %i, align 8, !dbg !1981
  %tobool79 = icmp ne i64 %52, 0, !dbg !1981
  br i1 %tobool79, label %if.then80, label %if.else81, !dbg !1983

if.then80:                                        ; preds = %sw.bb75
  %53 = load i64, i64* %i, align 8, !dbg !1984
  store i64 %53, i64* %width, align 8, !dbg !1985
  br label %if.end83, !dbg !1986

if.else81:                                        ; preds = %sw.bb75
  %54 = load i32, i32* %param_num, align 4, !dbg !1987
  %conv82 = sext i32 %54 to i64, !dbg !1987
  store i64 %conv82, i64* %width, align 8, !dbg !1988
  br label %if.end83

if.end83:                                         ; preds = %if.else81, %if.then80
  %55 = load i64, i64* %width, align 8, !dbg !1989
  %56 = load i64, i64* %max_param, align 8, !dbg !1991
  %cmp84 = icmp sgt i64 %55, %56, !dbg !1992
  br i1 %cmp84, label %if.then86, label %if.end87, !dbg !1993

if.then86:                                        ; preds = %if.end83
  %57 = load i64, i64* %width, align 8, !dbg !1994
  store i64 %57, i64* %max_param, align 8, !dbg !1995
  br label %if.end87, !dbg !1996

if.end87:                                         ; preds = %if.then86, %if.end83
  br label %sw.epilog, !dbg !1997

sw.default:                                       ; preds = %while.body18
  br label %sw.epilog, !dbg !1998

sw.epilog:                                        ; preds = %sw.default, %if.end87, %sw.bb72, %sw.bb64, %sw.bb62, %sw.bb60, %sw.bb58, %if.end57, %sw.bb48, %if.end47, %sw.bb25, %sw.bb23, %sw.bb21, %sw.bb
  br label %while.cond16, !dbg !1999

while.end:                                        ; preds = %while.cond16
  %58 = load i64, i64* %this_param, align 8, !dbg !2001
  %sub = sub nsw i64 %58, 1, !dbg !2002
  store i64 %sub, i64* %i, align 8, !dbg !2003
  %59 = load i64, i64* %i, align 8, !dbg !2004
  %cmp88 = icmp slt i64 %59, 0, !dbg !2006
  br i1 %cmp88, label %if.then92, label %lor.lhs.false, !dbg !2007

lor.lhs.false:                                    ; preds = %while.end
  %60 = load i64, i64* %i, align 8, !dbg !2008
  %cmp90 = icmp sge i64 %60, 128, !dbg !2010
  br i1 %cmp90, label %if.then92, label %if.end93, !dbg !2011

if.then92:                                        ; preds = %lor.lhs.false, %while.end
  store i32 1, i32* %retval, align 4, !dbg !2012
  br label %return, !dbg !2012

if.end93:                                         ; preds = %lor.lhs.false
  %61 = load i8*, i8** %fmt, align 8, !dbg !2013
  %62 = load i8, i8* %61, align 1, !dbg !2014
  %conv94 = sext i8 %62 to i32, !dbg !2014
  switch i32 %conv94, label %sw.default146 [
    i32 83, label %sw.bb95
    i32 115, label %sw.bb97
    i32 110, label %sw.bb98
    i32 112, label %sw.bb101
    i32 100, label %sw.bb104
    i32 105, label %sw.bb104
    i32 117, label %sw.bb107
    i32 111, label %sw.bb111
    i32 120, label %sw.bb115
    i32 88, label %sw.bb119
    i32 99, label %sw.bb123
    i32 102, label %sw.bb127
    i32 101, label %sw.bb130
    i32 69, label %sw.bb134
    i32 103, label %sw.bb138
    i32 71, label %sw.bb142
  ], !dbg !2015

sw.bb95:                                          ; preds = %if.end93
  %63 = load i32, i32* %flags, align 4, !dbg !2016
  %or96 = or i32 %63, 8, !dbg !2016
  store i32 %or96, i32* %flags, align 4, !dbg !2016
  br label %sw.bb97, !dbg !2018

sw.bb97:                                          ; preds = %if.end93, %sw.bb95
  %64 = load i64, i64* %i, align 8, !dbg !2019
  %65 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2020
  %arrayidx = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %65, i64 %64, !dbg !2020
  %type = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx, i32 0, i32 0, !dbg !2021
  store i32 1, i32* %type, align 8, !dbg !2022
  br label %sw.epilog149, !dbg !2023

sw.bb98:                                          ; preds = %if.end93
  %66 = load i64, i64* %i, align 8, !dbg !2024
  %67 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2025
  %arrayidx99 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %67, i64 %66, !dbg !2025
  %type100 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx99, i32 0, i32 0, !dbg !2026
  store i32 4, i32* %type100, align 8, !dbg !2027
  br label %sw.epilog149, !dbg !2028

sw.bb101:                                         ; preds = %if.end93
  %68 = load i64, i64* %i, align 8, !dbg !2029
  %69 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2030
  %arrayidx102 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %69, i64 %68, !dbg !2030
  %type103 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx102, i32 0, i32 0, !dbg !2031
  store i32 2, i32* %type103, align 8, !dbg !2032
  br label %sw.epilog149, !dbg !2033

sw.bb104:                                         ; preds = %if.end93, %if.end93
  %70 = load i64, i64* %i, align 8, !dbg !2034
  %71 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2035
  %arrayidx105 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %71, i64 %70, !dbg !2035
  %type106 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx105, i32 0, i32 0, !dbg !2036
  store i32 3, i32* %type106, align 8, !dbg !2037
  br label %sw.epilog149, !dbg !2038

sw.bb107:                                         ; preds = %if.end93
  %72 = load i64, i64* %i, align 8, !dbg !2039
  %73 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2040
  %arrayidx108 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %73, i64 %72, !dbg !2040
  %type109 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx108, i32 0, i32 0, !dbg !2041
  store i32 3, i32* %type109, align 8, !dbg !2042
  %74 = load i32, i32* %flags, align 4, !dbg !2043
  %or110 = or i32 %74, 512, !dbg !2043
  store i32 %or110, i32* %flags, align 4, !dbg !2043
  br label %sw.epilog149, !dbg !2044

sw.bb111:                                         ; preds = %if.end93
  %75 = load i64, i64* %i, align 8, !dbg !2045
  %76 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2046
  %arrayidx112 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %76, i64 %75, !dbg !2046
  %type113 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx112, i32 0, i32 0, !dbg !2047
  store i32 3, i32* %type113, align 8, !dbg !2048
  %77 = load i32, i32* %flags, align 4, !dbg !2049
  %or114 = or i32 %77, 1024, !dbg !2049
  store i32 %or114, i32* %flags, align 4, !dbg !2049
  br label %sw.epilog149, !dbg !2050

sw.bb115:                                         ; preds = %if.end93
  %78 = load i64, i64* %i, align 8, !dbg !2051
  %79 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2052
  %arrayidx116 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %79, i64 %78, !dbg !2052
  %type117 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx116, i32 0, i32 0, !dbg !2053
  store i32 3, i32* %type117, align 8, !dbg !2054
  %80 = load i32, i32* %flags, align 4, !dbg !2055
  %or118 = or i32 %80, 2560, !dbg !2055
  store i32 %or118, i32* %flags, align 4, !dbg !2055
  br label %sw.epilog149, !dbg !2056

sw.bb119:                                         ; preds = %if.end93
  %81 = load i64, i64* %i, align 8, !dbg !2057
  %82 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2058
  %arrayidx120 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %82, i64 %81, !dbg !2058
  %type121 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx120, i32 0, i32 0, !dbg !2059
  store i32 3, i32* %type121, align 8, !dbg !2060
  %83 = load i32, i32* %flags, align 4, !dbg !2061
  %or122 = or i32 %83, 6656, !dbg !2061
  store i32 %or122, i32* %flags, align 4, !dbg !2061
  br label %sw.epilog149, !dbg !2062

sw.bb123:                                         ; preds = %if.end93
  %84 = load i64, i64* %i, align 8, !dbg !2063
  %85 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2064
  %arrayidx124 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %85, i64 %84, !dbg !2064
  %type125 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx124, i32 0, i32 0, !dbg !2065
  store i32 3, i32* %type125, align 8, !dbg !2066
  %86 = load i32, i32* %flags, align 4, !dbg !2067
  %or126 = or i32 %86, 131072, !dbg !2067
  store i32 %or126, i32* %flags, align 4, !dbg !2067
  br label %sw.epilog149, !dbg !2068

sw.bb127:                                         ; preds = %if.end93
  %87 = load i64, i64* %i, align 8, !dbg !2069
  %88 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2070
  %arrayidx128 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %88, i64 %87, !dbg !2070
  %type129 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx128, i32 0, i32 0, !dbg !2071
  store i32 7, i32* %type129, align 8, !dbg !2072
  br label %sw.epilog149, !dbg !2073

sw.bb130:                                         ; preds = %if.end93
  %89 = load i64, i64* %i, align 8, !dbg !2074
  %90 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2075
  %arrayidx131 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %90, i64 %89, !dbg !2075
  %type132 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx131, i32 0, i32 0, !dbg !2076
  store i32 7, i32* %type132, align 8, !dbg !2077
  %91 = load i32, i32* %flags, align 4, !dbg !2078
  %or133 = or i32 %91, 262144, !dbg !2078
  store i32 %or133, i32* %flags, align 4, !dbg !2078
  br label %sw.epilog149, !dbg !2079

sw.bb134:                                         ; preds = %if.end93
  %92 = load i64, i64* %i, align 8, !dbg !2080
  %93 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2081
  %arrayidx135 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %93, i64 %92, !dbg !2081
  %type136 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx135, i32 0, i32 0, !dbg !2082
  store i32 7, i32* %type136, align 8, !dbg !2083
  %94 = load i32, i32* %flags, align 4, !dbg !2084
  %or137 = or i32 %94, 266240, !dbg !2084
  store i32 %or137, i32* %flags, align 4, !dbg !2084
  br label %sw.epilog149, !dbg !2085

sw.bb138:                                         ; preds = %if.end93
  %95 = load i64, i64* %i, align 8, !dbg !2086
  %96 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2087
  %arrayidx139 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %96, i64 %95, !dbg !2087
  %type140 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx139, i32 0, i32 0, !dbg !2088
  store i32 7, i32* %type140, align 8, !dbg !2089
  %97 = load i32, i32* %flags, align 4, !dbg !2090
  %or141 = or i32 %97, 524288, !dbg !2090
  store i32 %or141, i32* %flags, align 4, !dbg !2090
  br label %sw.epilog149, !dbg !2091

sw.bb142:                                         ; preds = %if.end93
  %98 = load i64, i64* %i, align 8, !dbg !2092
  %99 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2093
  %arrayidx143 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %99, i64 %98, !dbg !2093
  %type144 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx143, i32 0, i32 0, !dbg !2094
  store i32 7, i32* %type144, align 8, !dbg !2095
  %100 = load i32, i32* %flags, align 4, !dbg !2096
  %or145 = or i32 %100, 528384, !dbg !2096
  store i32 %or145, i32* %flags, align 4, !dbg !2096
  br label %sw.epilog149, !dbg !2097

sw.default146:                                    ; preds = %if.end93
  %101 = load i64, i64* %i, align 8, !dbg !2098
  %102 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2099
  %arrayidx147 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %102, i64 %101, !dbg !2099
  %type148 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx147, i32 0, i32 0, !dbg !2100
  store i32 0, i32* %type148, align 8, !dbg !2101
  br label %sw.epilog149, !dbg !2102

sw.epilog149:                                     ; preds = %sw.default146, %sw.bb142, %sw.bb138, %sw.bb134, %sw.bb130, %sw.bb127, %sw.bb123, %sw.bb119, %sw.bb115, %sw.bb111, %sw.bb107, %sw.bb104, %sw.bb101, %sw.bb98, %sw.bb97
  %103 = load i32, i32* %flags, align 4, !dbg !2103
  %104 = load i64, i64* %i, align 8, !dbg !2104
  %105 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2105
  %arrayidx150 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %105, i64 %104, !dbg !2105
  %flags151 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx150, i32 0, i32 1, !dbg !2106
  store i32 %103, i32* %flags151, align 4, !dbg !2107
  %106 = load i64, i64* %width, align 8, !dbg !2108
  %107 = load i64, i64* %i, align 8, !dbg !2109
  %108 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2110
  %arrayidx152 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %108, i64 %107, !dbg !2110
  %width153 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx152, i32 0, i32 2, !dbg !2111
  store i64 %106, i64* %width153, align 8, !dbg !2112
  %109 = load i64, i64* %precision, align 8, !dbg !2113
  %110 = load i64, i64* %i, align 8, !dbg !2114
  %111 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2115
  %arrayidx154 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %111, i64 %110, !dbg !2115
  %precision155 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx154, i32 0, i32 3, !dbg !2116
  store i64 %109, i64* %precision155, align 8, !dbg !2117
  %112 = load i32, i32* %flags, align 4, !dbg !2118
  %and156 = and i32 %112, 16384, !dbg !2120
  %tobool157 = icmp ne i32 %and156, 0, !dbg !2120
  br i1 %tobool157, label %if.then158, label %if.end170, !dbg !2121

if.then158:                                       ; preds = %sw.epilog149
  call void @llvm.dbg.declare(metadata i64* %k, metadata !2122, metadata !236), !dbg !2124
  %113 = load i64, i64* %width, align 8, !dbg !2125
  %sub159 = sub nsw i64 %113, 1, !dbg !2126
  store i64 %sub159, i64* %k, align 8, !dbg !2124
  %114 = load i64, i64* %k, align 8, !dbg !2127
  %115 = load i64, i64* %i, align 8, !dbg !2128
  %116 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2129
  %arrayidx160 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %116, i64 %115, !dbg !2129
  %width161 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx160, i32 0, i32 2, !dbg !2130
  store i64 %114, i64* %width161, align 8, !dbg !2131
  %117 = load i64, i64* %k, align 8, !dbg !2132
  %118 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2133
  %arrayidx162 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %118, i64 %117, !dbg !2133
  %type163 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx162, i32 0, i32 0, !dbg !2134
  store i32 9, i32* %type163, align 8, !dbg !2135
  %119 = load i64, i64* %k, align 8, !dbg !2136
  %120 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2137
  %arrayidx164 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %120, i64 %119, !dbg !2137
  %flags165 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx164, i32 0, i32 1, !dbg !2138
  store i32 0, i32* %flags165, align 4, !dbg !2139
  %121 = load i64, i64* %k, align 8, !dbg !2140
  %122 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2141
  %arrayidx166 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %122, i64 %121, !dbg !2141
  %width167 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx166, i32 0, i32 2, !dbg !2142
  store i64 0, i64* %width167, align 8, !dbg !2143
  %123 = load i64, i64* %k, align 8, !dbg !2144
  %124 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2145
  %arrayidx168 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %124, i64 %123, !dbg !2145
  %precision169 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx168, i32 0, i32 3, !dbg !2146
  store i64 0, i64* %precision169, align 8, !dbg !2147
  br label %if.end170, !dbg !2148

if.end170:                                        ; preds = %if.then158, %sw.epilog149
  %125 = load i32, i32* %flags, align 4, !dbg !2149
  %and171 = and i32 %125, 65536, !dbg !2151
  %tobool172 = icmp ne i32 %and171, 0, !dbg !2151
  br i1 %tobool172, label %if.then173, label %if.end186, !dbg !2152

if.then173:                                       ; preds = %if.end170
  call void @llvm.dbg.declare(metadata i64* %k174, metadata !2153, metadata !236), !dbg !2155
  %126 = load i64, i64* %precision, align 8, !dbg !2156
  %sub175 = sub nsw i64 %126, 1, !dbg !2157
  store i64 %sub175, i64* %k174, align 8, !dbg !2155
  %127 = load i64, i64* %k174, align 8, !dbg !2158
  %128 = load i64, i64* %i, align 8, !dbg !2159
  %129 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2160
  %arrayidx176 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %129, i64 %128, !dbg !2160
  %precision177 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx176, i32 0, i32 3, !dbg !2161
  store i64 %127, i64* %precision177, align 8, !dbg !2162
  %130 = load i64, i64* %k174, align 8, !dbg !2163
  %131 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2164
  %arrayidx178 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %131, i64 %130, !dbg !2164
  %type179 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx178, i32 0, i32 0, !dbg !2165
  store i32 9, i32* %type179, align 8, !dbg !2166
  %132 = load i64, i64* %k174, align 8, !dbg !2167
  %133 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2168
  %arrayidx180 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %133, i64 %132, !dbg !2168
  %flags181 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx180, i32 0, i32 1, !dbg !2169
  store i32 0, i32* %flags181, align 4, !dbg !2170
  %134 = load i64, i64* %k174, align 8, !dbg !2171
  %135 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2172
  %arrayidx182 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %135, i64 %134, !dbg !2172
  %width183 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx182, i32 0, i32 2, !dbg !2173
  store i64 0, i64* %width183, align 8, !dbg !2174
  %136 = load i64, i64* %k174, align 8, !dbg !2175
  %137 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2176
  %arrayidx184 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %137, i64 %136, !dbg !2176
  %precision185 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx184, i32 0, i32 3, !dbg !2177
  store i64 0, i64* %precision185, align 8, !dbg !2178
  br label %if.end186, !dbg !2179

if.end186:                                        ; preds = %if.then173, %if.end170
  %138 = load i8*, i8** %fmt, align 8, !dbg !2180
  %add.ptr187 = getelementptr inbounds i8, i8* %138, i64 1, !dbg !2181
  %139 = load i8**, i8*** %endpos.addr, align 8, !dbg !2182
  %incdec.ptr188 = getelementptr inbounds i8*, i8** %139, i32 1, !dbg !2182
  store i8** %incdec.ptr188, i8*** %endpos.addr, align 8, !dbg !2182
  store i8* %add.ptr187, i8** %139, align 8, !dbg !2183
  br label %if.end189, !dbg !2184

if.end189:                                        ; preds = %if.end186, %while.body
  br label %while.cond, !dbg !2185

while.end190:                                     ; preds = %while.cond
  store i64 0, i64* %i, align 8, !dbg !2187
  br label %for.cond, !dbg !2189

for.cond:                                         ; preds = %for.inc, %while.end190
  %140 = load i64, i64* %i, align 8, !dbg !2190
  %141 = load i64, i64* %max_param, align 8, !dbg !2193
  %cmp191 = icmp slt i64 %140, %141, !dbg !2194
  br i1 %cmp191, label %for.body, label %for.end, !dbg !2195

for.body:                                         ; preds = %for.cond
  %142 = load i64, i64* %i, align 8, !dbg !2196
  %143 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2199
  %arrayidx193 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %143, i64 %142, !dbg !2199
  %flags194 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx193, i32 0, i32 1, !dbg !2200
  %144 = load i32, i32* %flags194, align 4, !dbg !2200
  %and195 = and i32 %144, 16384, !dbg !2201
  %tobool196 = icmp ne i32 %and195, 0, !dbg !2201
  br i1 %tobool196, label %if.then197, label %if.end202, !dbg !2202

if.then197:                                       ; preds = %for.body
  %145 = load %struct.__va_list_tag*, %struct.__va_list_tag** %arglist.addr, align 8, !dbg !2203
  %gp_offset_p = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %145, i32 0, i32 0, !dbg !2203
  %gp_offset = load i32, i32* %gp_offset_p, align 8, !dbg !2203
  %fits_in_gp = icmp ule i32 %gp_offset, 40, !dbg !2203
  br i1 %fits_in_gp, label %vaarg.in_reg, label %vaarg.in_mem, !dbg !2203

vaarg.in_reg:                                     ; preds = %if.then197
  %146 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %145, i32 0, i32 3, !dbg !2205
  %reg_save_area = load i8*, i8** %146, align 8, !dbg !2205
  %147 = getelementptr i8, i8* %reg_save_area, i32 %gp_offset, !dbg !2205
  %148 = bitcast i8* %147 to i32*, !dbg !2205
  %149 = add i32 %gp_offset, 8, !dbg !2205
  store i32 %149, i32* %gp_offset_p, align 8, !dbg !2205
  br label %vaarg.end, !dbg !2205

vaarg.in_mem:                                     ; preds = %if.then197
  %overflow_arg_area_p = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %145, i32 0, i32 2, !dbg !2207
  %overflow_arg_area = load i8*, i8** %overflow_arg_area_p, align 8, !dbg !2207
  %150 = bitcast i8* %overflow_arg_area to i32*, !dbg !2207
  %overflow_arg_area.next = getelementptr i8, i8* %overflow_arg_area, i32 8, !dbg !2207
  store i8* %overflow_arg_area.next, i8** %overflow_arg_area_p, align 8, !dbg !2207
  br label %vaarg.end, !dbg !2207

vaarg.end:                                        ; preds = %vaarg.in_mem, %vaarg.in_reg
  %vaarg.addr = phi i32* [ %148, %vaarg.in_reg ], [ %150, %vaarg.in_mem ], !dbg !2209
  %151 = load i32, i32* %vaarg.addr, align 4, !dbg !2209
  %conv198 = sext i32 %151 to i64, !dbg !2211
  %152 = load i64, i64* %i, align 8, !dbg !2212
  %153 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2213
  %arrayidx199 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %153, i64 %152, !dbg !2213
  %width200 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx199, i32 0, i32 2, !dbg !2214
  %154 = load i64, i64* %width200, align 8, !dbg !2214
  %155 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2215
  %arrayidx201 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %155, i64 %154, !dbg !2215
  %data = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx201, i32 0, i32 4, !dbg !2216
  %num = bitcast %union.anon* %data to %union.anon.0*, !dbg !2217
  %as_signed = bitcast %union.anon.0* %num to i64*, !dbg !2218
  store i64 %conv198, i64* %as_signed, align 8, !dbg !2219
  br label %if.end202, !dbg !2220

if.end202:                                        ; preds = %vaarg.end, %for.body
  %156 = load i64, i64* %i, align 8, !dbg !2221
  %157 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2223
  %arrayidx203 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %157, i64 %156, !dbg !2223
  %flags204 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx203, i32 0, i32 1, !dbg !2224
  %158 = load i32, i32* %flags204, align 4, !dbg !2224
  %and205 = and i32 %158, 65536, !dbg !2225
  %tobool206 = icmp ne i32 %and205, 0, !dbg !2225
  br i1 %tobool206, label %if.then207, label %if.end226, !dbg !2226

if.then207:                                       ; preds = %if.end202
  %159 = load %struct.__va_list_tag*, %struct.__va_list_tag** %arglist.addr, align 8, !dbg !2227
  %gp_offset_p208 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %159, i32 0, i32 0, !dbg !2227
  %gp_offset209 = load i32, i32* %gp_offset_p208, align 8, !dbg !2227
  %fits_in_gp210 = icmp ule i32 %gp_offset209, 40, !dbg !2227
  br i1 %fits_in_gp210, label %vaarg.in_reg211, label %vaarg.in_mem213, !dbg !2227

vaarg.in_reg211:                                  ; preds = %if.then207
  %160 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %159, i32 0, i32 3, !dbg !2229
  %reg_save_area212 = load i8*, i8** %160, align 8, !dbg !2229
  %161 = getelementptr i8, i8* %reg_save_area212, i32 %gp_offset209, !dbg !2229
  %162 = bitcast i8* %161 to i32*, !dbg !2229
  %163 = add i32 %gp_offset209, 8, !dbg !2229
  store i32 %163, i32* %gp_offset_p208, align 8, !dbg !2229
  br label %vaarg.end217, !dbg !2229

vaarg.in_mem213:                                  ; preds = %if.then207
  %overflow_arg_area_p214 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %159, i32 0, i32 2, !dbg !2231
  %overflow_arg_area215 = load i8*, i8** %overflow_arg_area_p214, align 8, !dbg !2231
  %164 = bitcast i8* %overflow_arg_area215 to i32*, !dbg !2231
  %overflow_arg_area.next216 = getelementptr i8, i8* %overflow_arg_area215, i32 8, !dbg !2231
  store i8* %overflow_arg_area.next216, i8** %overflow_arg_area_p214, align 8, !dbg !2231
  br label %vaarg.end217, !dbg !2231

vaarg.end217:                                     ; preds = %vaarg.in_mem213, %vaarg.in_reg211
  %vaarg.addr218 = phi i32* [ %162, %vaarg.in_reg211 ], [ %164, %vaarg.in_mem213 ], !dbg !2233
  %165 = load i32, i32* %vaarg.addr218, align 4, !dbg !2233
  %conv219 = sext i32 %165 to i64, !dbg !2235
  %166 = load i64, i64* %i, align 8, !dbg !2236
  %167 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2237
  %arrayidx220 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %167, i64 %166, !dbg !2237
  %precision221 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx220, i32 0, i32 3, !dbg !2238
  %168 = load i64, i64* %precision221, align 8, !dbg !2238
  %169 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2239
  %arrayidx222 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %169, i64 %168, !dbg !2239
  %data223 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx222, i32 0, i32 4, !dbg !2240
  %num224 = bitcast %union.anon* %data223 to %union.anon.0*, !dbg !2241
  %as_signed225 = bitcast %union.anon.0* %num224 to i64*, !dbg !2242
  store i64 %conv219, i64* %as_signed225, align 8, !dbg !2243
  br label %if.end226, !dbg !2244

if.end226:                                        ; preds = %vaarg.end217, %if.end202
  %170 = load i64, i64* %i, align 8, !dbg !2245
  %171 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2246
  %arrayidx227 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %171, i64 %170, !dbg !2246
  %type228 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx227, i32 0, i32 0, !dbg !2247
  %172 = load i32, i32* %type228, align 8, !dbg !2247
  switch i32 %172, label %sw.default407 [
    i32 1, label %sw.bb229
    i32 4, label %sw.bb243
    i32 0, label %sw.bb243
    i32 2, label %sw.bb243
    i32 3, label %sw.bb257
    i32 7, label %sw.bb393
    i32 9, label %sw.bb404
  ], !dbg !2248

sw.bb229:                                         ; preds = %if.end226
  %173 = load %struct.__va_list_tag*, %struct.__va_list_tag** %arglist.addr, align 8, !dbg !2249
  %gp_offset_p230 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %173, i32 0, i32 0, !dbg !2249
  %gp_offset231 = load i32, i32* %gp_offset_p230, align 8, !dbg !2249
  %fits_in_gp232 = icmp ule i32 %gp_offset231, 40, !dbg !2249
  br i1 %fits_in_gp232, label %vaarg.in_reg233, label %vaarg.in_mem235, !dbg !2249

vaarg.in_reg233:                                  ; preds = %sw.bb229
  %174 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %173, i32 0, i32 3, !dbg !2251
  %reg_save_area234 = load i8*, i8** %174, align 8, !dbg !2251
  %175 = getelementptr i8, i8* %reg_save_area234, i32 %gp_offset231, !dbg !2251
  %176 = bitcast i8* %175 to i8**, !dbg !2251
  %177 = add i32 %gp_offset231, 8, !dbg !2251
  store i32 %177, i32* %gp_offset_p230, align 8, !dbg !2251
  br label %vaarg.end239, !dbg !2251

vaarg.in_mem235:                                  ; preds = %sw.bb229
  %overflow_arg_area_p236 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %173, i32 0, i32 2, !dbg !2253
  %overflow_arg_area237 = load i8*, i8** %overflow_arg_area_p236, align 8, !dbg !2253
  %178 = bitcast i8* %overflow_arg_area237 to i8**, !dbg !2253
  %overflow_arg_area.next238 = getelementptr i8, i8* %overflow_arg_area237, i32 8, !dbg !2253
  store i8* %overflow_arg_area.next238, i8** %overflow_arg_area_p236, align 8, !dbg !2253
  br label %vaarg.end239, !dbg !2253

vaarg.end239:                                     ; preds = %vaarg.in_mem235, %vaarg.in_reg233
  %vaarg.addr240 = phi i8** [ %176, %vaarg.in_reg233 ], [ %178, %vaarg.in_mem235 ], !dbg !2255
  %179 = load i8*, i8** %vaarg.addr240, align 8, !dbg !2255
  %180 = load i64, i64* %i, align 8, !dbg !2257
  %181 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2258
  %arrayidx241 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %181, i64 %180, !dbg !2258
  %data242 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx241, i32 0, i32 4, !dbg !2259
  %str = bitcast %union.anon* %data242 to i8**, !dbg !2260
  store i8* %179, i8** %str, align 8, !dbg !2261
  br label %sw.epilog408, !dbg !2262

sw.bb243:                                         ; preds = %if.end226, %if.end226, %if.end226
  %182 = load %struct.__va_list_tag*, %struct.__va_list_tag** %arglist.addr, align 8, !dbg !2263
  %gp_offset_p244 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %182, i32 0, i32 0, !dbg !2263
  %gp_offset245 = load i32, i32* %gp_offset_p244, align 8, !dbg !2263
  %fits_in_gp246 = icmp ule i32 %gp_offset245, 40, !dbg !2263
  br i1 %fits_in_gp246, label %vaarg.in_reg247, label %vaarg.in_mem249, !dbg !2263

vaarg.in_reg247:                                  ; preds = %sw.bb243
  %183 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %182, i32 0, i32 3, !dbg !2264
  %reg_save_area248 = load i8*, i8** %183, align 8, !dbg !2264
  %184 = getelementptr i8, i8* %reg_save_area248, i32 %gp_offset245, !dbg !2264
  %185 = bitcast i8* %184 to i8**, !dbg !2264
  %186 = add i32 %gp_offset245, 8, !dbg !2264
  store i32 %186, i32* %gp_offset_p244, align 8, !dbg !2264
  br label %vaarg.end253, !dbg !2264

vaarg.in_mem249:                                  ; preds = %sw.bb243
  %overflow_arg_area_p250 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %182, i32 0, i32 2, !dbg !2265
  %overflow_arg_area251 = load i8*, i8** %overflow_arg_area_p250, align 8, !dbg !2265
  %187 = bitcast i8* %overflow_arg_area251 to i8**, !dbg !2265
  %overflow_arg_area.next252 = getelementptr i8, i8* %overflow_arg_area251, i32 8, !dbg !2265
  store i8* %overflow_arg_area.next252, i8** %overflow_arg_area_p250, align 8, !dbg !2265
  br label %vaarg.end253, !dbg !2265

vaarg.end253:                                     ; preds = %vaarg.in_mem249, %vaarg.in_reg247
  %vaarg.addr254 = phi i8** [ %185, %vaarg.in_reg247 ], [ %187, %vaarg.in_mem249 ], !dbg !2266
  %188 = load i8*, i8** %vaarg.addr254, align 8, !dbg !2266
  %189 = load i64, i64* %i, align 8, !dbg !2267
  %190 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2268
  %arrayidx255 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %190, i64 %189, !dbg !2268
  %data256 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx255, i32 0, i32 4, !dbg !2269
  %ptr = bitcast %union.anon* %data256 to i8**, !dbg !2270
  store i8* %188, i8** %ptr, align 8, !dbg !2271
  br label %sw.epilog408, !dbg !2272

sw.bb257:                                         ; preds = %if.end226
  %191 = load i64, i64* %i, align 8, !dbg !2273
  %192 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2275
  %arrayidx258 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %192, i64 %191, !dbg !2275
  %flags259 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx258, i32 0, i32 1, !dbg !2276
  %193 = load i32, i32* %flags259, align 4, !dbg !2276
  %and260 = and i32 %193, 64, !dbg !2277
  %tobool261 = icmp ne i32 %and260, 0, !dbg !2277
  br i1 %tobool261, label %land.lhs.true, label %if.else281, !dbg !2278

land.lhs.true:                                    ; preds = %sw.bb257
  %194 = load i64, i64* %i, align 8, !dbg !2279
  %195 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2281
  %arrayidx262 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %195, i64 %194, !dbg !2281
  %flags263 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx262, i32 0, i32 1, !dbg !2282
  %196 = load i32, i32* %flags263, align 4, !dbg !2282
  %and264 = and i32 %196, 512, !dbg !2283
  %tobool265 = icmp ne i32 %and264, 0, !dbg !2283
  br i1 %tobool265, label %if.then266, label %if.else281, !dbg !2284

if.then266:                                       ; preds = %land.lhs.true
  %197 = load %struct.__va_list_tag*, %struct.__va_list_tag** %arglist.addr, align 8, !dbg !2285
  %gp_offset_p267 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %197, i32 0, i32 0, !dbg !2285
  %gp_offset268 = load i32, i32* %gp_offset_p267, align 8, !dbg !2285
  %fits_in_gp269 = icmp ule i32 %gp_offset268, 40, !dbg !2285
  br i1 %fits_in_gp269, label %vaarg.in_reg270, label %vaarg.in_mem272, !dbg !2285

vaarg.in_reg270:                                  ; preds = %if.then266
  %198 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %197, i32 0, i32 3, !dbg !2286
  %reg_save_area271 = load i8*, i8** %198, align 8, !dbg !2286
  %199 = getelementptr i8, i8* %reg_save_area271, i32 %gp_offset268, !dbg !2286
  %200 = bitcast i8* %199 to i64*, !dbg !2286
  %201 = add i32 %gp_offset268, 8, !dbg !2286
  store i32 %201, i32* %gp_offset_p267, align 8, !dbg !2286
  br label %vaarg.end276, !dbg !2286

vaarg.in_mem272:                                  ; preds = %if.then266
  %overflow_arg_area_p273 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %197, i32 0, i32 2, !dbg !2287
  %overflow_arg_area274 = load i8*, i8** %overflow_arg_area_p273, align 8, !dbg !2287
  %202 = bitcast i8* %overflow_arg_area274 to i64*, !dbg !2287
  %overflow_arg_area.next275 = getelementptr i8, i8* %overflow_arg_area274, i32 8, !dbg !2287
  store i8* %overflow_arg_area.next275, i8** %overflow_arg_area_p273, align 8, !dbg !2287
  br label %vaarg.end276, !dbg !2287

vaarg.end276:                                     ; preds = %vaarg.in_mem272, %vaarg.in_reg270
  %vaarg.addr277 = phi i64* [ %200, %vaarg.in_reg270 ], [ %202, %vaarg.in_mem272 ], !dbg !2289
  %203 = load i64, i64* %vaarg.addr277, align 8, !dbg !2289
  %204 = load i64, i64* %i, align 8, !dbg !2291
  %205 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2292
  %arrayidx278 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %205, i64 %204, !dbg !2292
  %data279 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx278, i32 0, i32 4, !dbg !2293
  %num280 = bitcast %union.anon* %data279 to %union.anon.0*, !dbg !2294
  %as_unsigned = bitcast %union.anon.0* %num280 to i64*, !dbg !2295
  store i64 %203, i64* %as_unsigned, align 8, !dbg !2296
  br label %if.end392, !dbg !2292

if.else281:                                       ; preds = %land.lhs.true, %sw.bb257
  %206 = load i64, i64* %i, align 8, !dbg !2297
  %207 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2299
  %arrayidx282 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %207, i64 %206, !dbg !2299
  %flags283 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx282, i32 0, i32 1, !dbg !2300
  %208 = load i32, i32* %flags283, align 4, !dbg !2300
  %and284 = and i32 %208, 64, !dbg !2301
  %tobool285 = icmp ne i32 %and284, 0, !dbg !2301
  br i1 %tobool285, label %if.then286, label %if.else302, !dbg !2302

if.then286:                                       ; preds = %if.else281
  %209 = load %struct.__va_list_tag*, %struct.__va_list_tag** %arglist.addr, align 8, !dbg !2303
  %gp_offset_p287 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %209, i32 0, i32 0, !dbg !2303
  %gp_offset288 = load i32, i32* %gp_offset_p287, align 8, !dbg !2303
  %fits_in_gp289 = icmp ule i32 %gp_offset288, 40, !dbg !2303
  br i1 %fits_in_gp289, label %vaarg.in_reg290, label %vaarg.in_mem292, !dbg !2303

vaarg.in_reg290:                                  ; preds = %if.then286
  %210 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %209, i32 0, i32 3, !dbg !2304
  %reg_save_area291 = load i8*, i8** %210, align 8, !dbg !2304
  %211 = getelementptr i8, i8* %reg_save_area291, i32 %gp_offset288, !dbg !2304
  %212 = bitcast i8* %211 to i64*, !dbg !2304
  %213 = add i32 %gp_offset288, 8, !dbg !2304
  store i32 %213, i32* %gp_offset_p287, align 8, !dbg !2304
  br label %vaarg.end296, !dbg !2304

vaarg.in_mem292:                                  ; preds = %if.then286
  %overflow_arg_area_p293 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %209, i32 0, i32 2, !dbg !2306
  %overflow_arg_area294 = load i8*, i8** %overflow_arg_area_p293, align 8, !dbg !2306
  %214 = bitcast i8* %overflow_arg_area294 to i64*, !dbg !2306
  %overflow_arg_area.next295 = getelementptr i8, i8* %overflow_arg_area294, i32 8, !dbg !2306
  store i8* %overflow_arg_area.next295, i8** %overflow_arg_area_p293, align 8, !dbg !2306
  br label %vaarg.end296, !dbg !2306

vaarg.end296:                                     ; preds = %vaarg.in_mem292, %vaarg.in_reg290
  %vaarg.addr297 = phi i64* [ %212, %vaarg.in_reg290 ], [ %214, %vaarg.in_mem292 ], !dbg !2308
  %215 = load i64, i64* %vaarg.addr297, align 8, !dbg !2308
  %216 = load i64, i64* %i, align 8, !dbg !2310
  %217 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2311
  %arrayidx298 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %217, i64 %216, !dbg !2311
  %data299 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx298, i32 0, i32 4, !dbg !2312
  %num300 = bitcast %union.anon* %data299 to %union.anon.0*, !dbg !2313
  %as_signed301 = bitcast %union.anon.0* %num300 to i64*, !dbg !2314
  store i64 %215, i64* %as_signed301, align 8, !dbg !2315
  br label %if.end391, !dbg !2311

if.else302:                                       ; preds = %if.else281
  %218 = load i64, i64* %i, align 8, !dbg !2316
  %219 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2319
  %arrayidx303 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %219, i64 %218, !dbg !2319
  %flags304 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx303, i32 0, i32 1, !dbg !2320
  %220 = load i32, i32* %flags304, align 4, !dbg !2320
  %and305 = and i32 %220, 32, !dbg !2321
  %tobool306 = icmp ne i32 %and305, 0, !dbg !2321
  br i1 %tobool306, label %land.lhs.true307, label %if.else328, !dbg !2322

land.lhs.true307:                                 ; preds = %if.else302
  %221 = load i64, i64* %i, align 8, !dbg !2323
  %222 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2325
  %arrayidx308 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %222, i64 %221, !dbg !2325
  %flags309 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx308, i32 0, i32 1, !dbg !2326
  %223 = load i32, i32* %flags309, align 4, !dbg !2326
  %and310 = and i32 %223, 512, !dbg !2327
  %tobool311 = icmp ne i32 %and310, 0, !dbg !2327
  br i1 %tobool311, label %if.then312, label %if.else328, !dbg !2328

if.then312:                                       ; preds = %land.lhs.true307
  %224 = load %struct.__va_list_tag*, %struct.__va_list_tag** %arglist.addr, align 8, !dbg !2329
  %gp_offset_p313 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %224, i32 0, i32 0, !dbg !2329
  %gp_offset314 = load i32, i32* %gp_offset_p313, align 8, !dbg !2329
  %fits_in_gp315 = icmp ule i32 %gp_offset314, 40, !dbg !2329
  br i1 %fits_in_gp315, label %vaarg.in_reg316, label %vaarg.in_mem318, !dbg !2329

vaarg.in_reg316:                                  ; preds = %if.then312
  %225 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %224, i32 0, i32 3, !dbg !2330
  %reg_save_area317 = load i8*, i8** %225, align 8, !dbg !2330
  %226 = getelementptr i8, i8* %reg_save_area317, i32 %gp_offset314, !dbg !2330
  %227 = bitcast i8* %226 to i64*, !dbg !2330
  %228 = add i32 %gp_offset314, 8, !dbg !2330
  store i32 %228, i32* %gp_offset_p313, align 8, !dbg !2330
  br label %vaarg.end322, !dbg !2330

vaarg.in_mem318:                                  ; preds = %if.then312
  %overflow_arg_area_p319 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %224, i32 0, i32 2, !dbg !2331
  %overflow_arg_area320 = load i8*, i8** %overflow_arg_area_p319, align 8, !dbg !2331
  %229 = bitcast i8* %overflow_arg_area320 to i64*, !dbg !2331
  %overflow_arg_area.next321 = getelementptr i8, i8* %overflow_arg_area320, i32 8, !dbg !2331
  store i8* %overflow_arg_area.next321, i8** %overflow_arg_area_p319, align 8, !dbg !2331
  br label %vaarg.end322, !dbg !2331

vaarg.end322:                                     ; preds = %vaarg.in_mem318, %vaarg.in_reg316
  %vaarg.addr323 = phi i64* [ %227, %vaarg.in_reg316 ], [ %229, %vaarg.in_mem318 ], !dbg !2333
  %230 = load i64, i64* %vaarg.addr323, align 8, !dbg !2333
  %231 = load i64, i64* %i, align 8, !dbg !2335
  %232 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2336
  %arrayidx324 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %232, i64 %231, !dbg !2336
  %data325 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx324, i32 0, i32 4, !dbg !2337
  %num326 = bitcast %union.anon* %data325 to %union.anon.0*, !dbg !2338
  %as_unsigned327 = bitcast %union.anon.0* %num326 to i64*, !dbg !2339
  store i64 %230, i64* %as_unsigned327, align 8, !dbg !2340
  br label %if.end390, !dbg !2336

if.else328:                                       ; preds = %land.lhs.true307, %if.else302
  %233 = load i64, i64* %i, align 8, !dbg !2341
  %234 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2343
  %arrayidx329 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %234, i64 %233, !dbg !2343
  %flags330 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx329, i32 0, i32 1, !dbg !2344
  %235 = load i32, i32* %flags330, align 4, !dbg !2344
  %and331 = and i32 %235, 32, !dbg !2345
  %tobool332 = icmp ne i32 %and331, 0, !dbg !2345
  br i1 %tobool332, label %if.then333, label %if.else349, !dbg !2346

if.then333:                                       ; preds = %if.else328
  %236 = load %struct.__va_list_tag*, %struct.__va_list_tag** %arglist.addr, align 8, !dbg !2347
  %gp_offset_p334 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %236, i32 0, i32 0, !dbg !2347
  %gp_offset335 = load i32, i32* %gp_offset_p334, align 8, !dbg !2347
  %fits_in_gp336 = icmp ule i32 %gp_offset335, 40, !dbg !2347
  br i1 %fits_in_gp336, label %vaarg.in_reg337, label %vaarg.in_mem339, !dbg !2347

vaarg.in_reg337:                                  ; preds = %if.then333
  %237 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %236, i32 0, i32 3, !dbg !2348
  %reg_save_area338 = load i8*, i8** %237, align 8, !dbg !2348
  %238 = getelementptr i8, i8* %reg_save_area338, i32 %gp_offset335, !dbg !2348
  %239 = bitcast i8* %238 to i64*, !dbg !2348
  %240 = add i32 %gp_offset335, 8, !dbg !2348
  store i32 %240, i32* %gp_offset_p334, align 8, !dbg !2348
  br label %vaarg.end343, !dbg !2348

vaarg.in_mem339:                                  ; preds = %if.then333
  %overflow_arg_area_p340 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %236, i32 0, i32 2, !dbg !2350
  %overflow_arg_area341 = load i8*, i8** %overflow_arg_area_p340, align 8, !dbg !2350
  %241 = bitcast i8* %overflow_arg_area341 to i64*, !dbg !2350
  %overflow_arg_area.next342 = getelementptr i8, i8* %overflow_arg_area341, i32 8, !dbg !2350
  store i8* %overflow_arg_area.next342, i8** %overflow_arg_area_p340, align 8, !dbg !2350
  br label %vaarg.end343, !dbg !2350

vaarg.end343:                                     ; preds = %vaarg.in_mem339, %vaarg.in_reg337
  %vaarg.addr344 = phi i64* [ %239, %vaarg.in_reg337 ], [ %241, %vaarg.in_mem339 ], !dbg !2352
  %242 = load i64, i64* %vaarg.addr344, align 8, !dbg !2352
  %243 = load i64, i64* %i, align 8, !dbg !2354
  %244 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2355
  %arrayidx345 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %244, i64 %243, !dbg !2355
  %data346 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx345, i32 0, i32 4, !dbg !2356
  %num347 = bitcast %union.anon* %data346 to %union.anon.0*, !dbg !2357
  %as_signed348 = bitcast %union.anon.0* %num347 to i64*, !dbg !2358
  store i64 %242, i64* %as_signed348, align 8, !dbg !2359
  br label %if.end389, !dbg !2355

if.else349:                                       ; preds = %if.else328
  %245 = load i64, i64* %i, align 8, !dbg !2360
  %246 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2362
  %arrayidx350 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %246, i64 %245, !dbg !2362
  %flags351 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx350, i32 0, i32 1, !dbg !2363
  %247 = load i32, i32* %flags351, align 4, !dbg !2363
  %and352 = and i32 %247, 512, !dbg !2364
  %tobool353 = icmp ne i32 %and352, 0, !dbg !2364
  br i1 %tobool353, label %if.then354, label %if.else371, !dbg !2365

if.then354:                                       ; preds = %if.else349
  %248 = load %struct.__va_list_tag*, %struct.__va_list_tag** %arglist.addr, align 8, !dbg !2366
  %gp_offset_p355 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %248, i32 0, i32 0, !dbg !2366
  %gp_offset356 = load i32, i32* %gp_offset_p355, align 8, !dbg !2366
  %fits_in_gp357 = icmp ule i32 %gp_offset356, 40, !dbg !2366
  br i1 %fits_in_gp357, label %vaarg.in_reg358, label %vaarg.in_mem360, !dbg !2366

vaarg.in_reg358:                                  ; preds = %if.then354
  %249 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %248, i32 0, i32 3, !dbg !2367
  %reg_save_area359 = load i8*, i8** %249, align 8, !dbg !2367
  %250 = getelementptr i8, i8* %reg_save_area359, i32 %gp_offset356, !dbg !2367
  %251 = bitcast i8* %250 to i32*, !dbg !2367
  %252 = add i32 %gp_offset356, 8, !dbg !2367
  store i32 %252, i32* %gp_offset_p355, align 8, !dbg !2367
  br label %vaarg.end364, !dbg !2367

vaarg.in_mem360:                                  ; preds = %if.then354
  %overflow_arg_area_p361 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %248, i32 0, i32 2, !dbg !2369
  %overflow_arg_area362 = load i8*, i8** %overflow_arg_area_p361, align 8, !dbg !2369
  %253 = bitcast i8* %overflow_arg_area362 to i32*, !dbg !2369
  %overflow_arg_area.next363 = getelementptr i8, i8* %overflow_arg_area362, i32 8, !dbg !2369
  store i8* %overflow_arg_area.next363, i8** %overflow_arg_area_p361, align 8, !dbg !2369
  br label %vaarg.end364, !dbg !2369

vaarg.end364:                                     ; preds = %vaarg.in_mem360, %vaarg.in_reg358
  %vaarg.addr365 = phi i32* [ %251, %vaarg.in_reg358 ], [ %253, %vaarg.in_mem360 ], !dbg !2371
  %254 = load i32, i32* %vaarg.addr365, align 4, !dbg !2371
  %conv366 = zext i32 %254 to i64, !dbg !2373
  %255 = load i64, i64* %i, align 8, !dbg !2374
  %256 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2375
  %arrayidx367 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %256, i64 %255, !dbg !2375
  %data368 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx367, i32 0, i32 4, !dbg !2376
  %num369 = bitcast %union.anon* %data368 to %union.anon.0*, !dbg !2377
  %as_unsigned370 = bitcast %union.anon.0* %num369 to i64*, !dbg !2378
  store i64 %conv366, i64* %as_unsigned370, align 8, !dbg !2379
  br label %if.end388, !dbg !2375

if.else371:                                       ; preds = %if.else349
  %257 = load %struct.__va_list_tag*, %struct.__va_list_tag** %arglist.addr, align 8, !dbg !2380
  %gp_offset_p372 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %257, i32 0, i32 0, !dbg !2380
  %gp_offset373 = load i32, i32* %gp_offset_p372, align 8, !dbg !2380
  %fits_in_gp374 = icmp ule i32 %gp_offset373, 40, !dbg !2380
  br i1 %fits_in_gp374, label %vaarg.in_reg375, label %vaarg.in_mem377, !dbg !2380

vaarg.in_reg375:                                  ; preds = %if.else371
  %258 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %257, i32 0, i32 3, !dbg !2381
  %reg_save_area376 = load i8*, i8** %258, align 8, !dbg !2381
  %259 = getelementptr i8, i8* %reg_save_area376, i32 %gp_offset373, !dbg !2381
  %260 = bitcast i8* %259 to i32*, !dbg !2381
  %261 = add i32 %gp_offset373, 8, !dbg !2381
  store i32 %261, i32* %gp_offset_p372, align 8, !dbg !2381
  br label %vaarg.end381, !dbg !2381

vaarg.in_mem377:                                  ; preds = %if.else371
  %overflow_arg_area_p378 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %257, i32 0, i32 2, !dbg !2382
  %overflow_arg_area379 = load i8*, i8** %overflow_arg_area_p378, align 8, !dbg !2382
  %262 = bitcast i8* %overflow_arg_area379 to i32*, !dbg !2382
  %overflow_arg_area.next380 = getelementptr i8, i8* %overflow_arg_area379, i32 8, !dbg !2382
  store i8* %overflow_arg_area.next380, i8** %overflow_arg_area_p378, align 8, !dbg !2382
  br label %vaarg.end381, !dbg !2382

vaarg.end381:                                     ; preds = %vaarg.in_mem377, %vaarg.in_reg375
  %vaarg.addr382 = phi i32* [ %260, %vaarg.in_reg375 ], [ %262, %vaarg.in_mem377 ], !dbg !2383
  %263 = load i32, i32* %vaarg.addr382, align 4, !dbg !2383
  %conv383 = sext i32 %263 to i64, !dbg !2384
  %264 = load i64, i64* %i, align 8, !dbg !2385
  %265 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2386
  %arrayidx384 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %265, i64 %264, !dbg !2386
  %data385 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx384, i32 0, i32 4, !dbg !2387
  %num386 = bitcast %union.anon* %data385 to %union.anon.0*, !dbg !2388
  %as_signed387 = bitcast %union.anon.0* %num386 to i64*, !dbg !2389
  store i64 %conv383, i64* %as_signed387, align 8, !dbg !2390
  br label %if.end388

if.end388:                                        ; preds = %vaarg.end381, %vaarg.end364
  br label %if.end389

if.end389:                                        ; preds = %if.end388, %vaarg.end343
  br label %if.end390

if.end390:                                        ; preds = %if.end389, %vaarg.end322
  br label %if.end391

if.end391:                                        ; preds = %if.end390, %vaarg.end296
  br label %if.end392

if.end392:                                        ; preds = %if.end391, %vaarg.end276
  br label %sw.epilog408, !dbg !2391

sw.bb393:                                         ; preds = %if.end226
  %266 = load %struct.__va_list_tag*, %struct.__va_list_tag** %arglist.addr, align 8, !dbg !2392
  %fp_offset_p = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %266, i32 0, i32 1, !dbg !2392
  %fp_offset = load i32, i32* %fp_offset_p, align 4, !dbg !2392
  %fits_in_fp = icmp ule i32 %fp_offset, 160, !dbg !2392
  br i1 %fits_in_fp, label %vaarg.in_reg394, label %vaarg.in_mem396, !dbg !2392

vaarg.in_reg394:                                  ; preds = %sw.bb393
  %267 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %266, i32 0, i32 3, !dbg !2393
  %reg_save_area395 = load i8*, i8** %267, align 8, !dbg !2393
  %268 = getelementptr i8, i8* %reg_save_area395, i32 %fp_offset, !dbg !2393
  %269 = bitcast i8* %268 to double*, !dbg !2393
  %270 = add i32 %fp_offset, 16, !dbg !2393
  store i32 %270, i32* %fp_offset_p, align 4, !dbg !2393
  br label %vaarg.end400, !dbg !2393

vaarg.in_mem396:                                  ; preds = %sw.bb393
  %overflow_arg_area_p397 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %266, i32 0, i32 2, !dbg !2394
  %overflow_arg_area398 = load i8*, i8** %overflow_arg_area_p397, align 8, !dbg !2394
  %271 = bitcast i8* %overflow_arg_area398 to double*, !dbg !2394
  %overflow_arg_area.next399 = getelementptr i8, i8* %overflow_arg_area398, i32 8, !dbg !2394
  store i8* %overflow_arg_area.next399, i8** %overflow_arg_area_p397, align 8, !dbg !2394
  br label %vaarg.end400, !dbg !2394

vaarg.end400:                                     ; preds = %vaarg.in_mem396, %vaarg.in_reg394
  %vaarg.addr401 = phi double* [ %269, %vaarg.in_reg394 ], [ %271, %vaarg.in_mem396 ], !dbg !2395
  %272 = load double, double* %vaarg.addr401, align 8, !dbg !2395
  %273 = load i64, i64* %i, align 8, !dbg !2396
  %274 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2397
  %arrayidx402 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %274, i64 %273, !dbg !2397
  %data403 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx402, i32 0, i32 4, !dbg !2398
  %dnum = bitcast %union.anon* %data403 to double*, !dbg !2399
  store double %272, double* %dnum, align 8, !dbg !2400
  br label %sw.epilog408, !dbg !2401

sw.bb404:                                         ; preds = %if.end226
  %275 = load i64, i64* %i, align 8, !dbg !2402
  %276 = load %struct.va_stack_t*, %struct.va_stack_t** %vto.addr, align 8, !dbg !2403
  %arrayidx405 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %276, i64 %275, !dbg !2403
  %type406 = getelementptr inbounds %struct.va_stack_t, %struct.va_stack_t* %arrayidx405, i32 0, i32 0, !dbg !2404
  store i32 3, i32* %type406, align 8, !dbg !2405
  br label %sw.epilog408, !dbg !2406

sw.default407:                                    ; preds = %if.end226
  br label %sw.epilog408, !dbg !2407

sw.epilog408:                                     ; preds = %sw.default407, %sw.bb404, %vaarg.end400, %if.end392, %vaarg.end253, %vaarg.end239
  br label %for.inc, !dbg !2408

for.inc:                                          ; preds = %sw.epilog408
  %277 = load i64, i64* %i, align 8, !dbg !2409
  %inc409 = add nsw i64 %277, 1, !dbg !2409
  store i64 %inc409, i64* %i, align 8, !dbg !2409
  br label %for.cond, !dbg !2411

for.end:                                          ; preds = %for.cond
  store i32 0, i32* %retval, align 4, !dbg !2412
  br label %return, !dbg !2412

return:                                           ; preds = %for.end, %if.then92
  %278 = load i32, i32* %retval, align 4, !dbg !2413
  ret i32 %278, !dbg !2413
}

; Function Attrs: nounwind uwtable
define internal i64 @dprintf_DollarString(i8* %input, i8** %end) #0 !dbg !215 {
entry:
  %retval = alloca i64, align 8
  %input.addr = alloca i8*, align 8
  %end.addr = alloca i8**, align 8
  %number = alloca i32, align 4
  store i8* %input, i8** %input.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %input.addr, metadata !2414, metadata !236), !dbg !2415
  store i8** %end, i8*** %end.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %end.addr, metadata !2416, metadata !236), !dbg !2417
  call void @llvm.dbg.declare(metadata i32* %number, metadata !2418, metadata !236), !dbg !2419
  store i32 0, i32* %number, align 4, !dbg !2419
  br label %while.cond, !dbg !2420

while.cond:                                       ; preds = %while.body, %entry
  %0 = load i8*, i8** %input.addr, align 8, !dbg !2421
  %1 = load i8, i8* %0, align 1, !dbg !2421
  %conv = zext i8 %1 to i32, !dbg !2421
  %idxprom = sext i32 %conv to i64, !dbg !2421
  %call = call i16** @__ctype_b_loc() #1, !dbg !2421
  %2 = load i16*, i16** %call, align 8, !dbg !2421
  %arrayidx = getelementptr inbounds i16, i16* %2, i64 %idxprom, !dbg !2421
  %3 = load i16, i16* %arrayidx, align 2, !dbg !2421
  %conv1 = zext i16 %3 to i32, !dbg !2421
  %and = and i32 %conv1, 2048, !dbg !2421
  %tobool = icmp ne i32 %and, 0, !dbg !2423
  br i1 %tobool, label %while.body, label %while.end, !dbg !2423

while.body:                                       ; preds = %while.cond
  %4 = load i32, i32* %number, align 4, !dbg !2424
  %mul = mul nsw i32 %4, 10, !dbg !2424
  store i32 %mul, i32* %number, align 4, !dbg !2424
  %5 = load i8*, i8** %input.addr, align 8, !dbg !2426
  %6 = load i8, i8* %5, align 1, !dbg !2427
  %conv2 = sext i8 %6 to i32, !dbg !2427
  %sub = sub nsw i32 %conv2, 48, !dbg !2428
  %7 = load i32, i32* %number, align 4, !dbg !2429
  %add = add nsw i32 %7, %sub, !dbg !2429
  store i32 %add, i32* %number, align 4, !dbg !2429
  %8 = load i8*, i8** %input.addr, align 8, !dbg !2430
  %incdec.ptr = getelementptr inbounds i8, i8* %8, i32 1, !dbg !2430
  store i8* %incdec.ptr, i8** %input.addr, align 8, !dbg !2430
  br label %while.cond, !dbg !2431

while.end:                                        ; preds = %while.cond
  %9 = load i32, i32* %number, align 4, !dbg !2433
  %tobool3 = icmp ne i32 %9, 0, !dbg !2433
  br i1 %tobool3, label %land.lhs.true, label %if.end, !dbg !2435

land.lhs.true:                                    ; preds = %while.end
  %10 = load i8*, i8** %input.addr, align 8, !dbg !2436
  %incdec.ptr4 = getelementptr inbounds i8, i8* %10, i32 1, !dbg !2436
  store i8* %incdec.ptr4, i8** %input.addr, align 8, !dbg !2436
  %11 = load i8, i8* %10, align 1, !dbg !2438
  %conv5 = sext i8 %11 to i32, !dbg !2438
  %cmp = icmp eq i32 36, %conv5, !dbg !2439
  br i1 %cmp, label %if.then, label %if.end, !dbg !2440

if.then:                                          ; preds = %land.lhs.true
  %12 = load i8*, i8** %input.addr, align 8, !dbg !2441
  %13 = load i8**, i8*** %end.addr, align 8, !dbg !2443
  store i8* %12, i8** %13, align 8, !dbg !2444
  %14 = load i32, i32* %number, align 4, !dbg !2445
  %conv7 = sext i32 %14 to i64, !dbg !2445
  store i64 %conv7, i64* %retval, align 8, !dbg !2446
  br label %return, !dbg !2446

if.end:                                           ; preds = %land.lhs.true, %while.end
  store i64 0, i64* %retval, align 8, !dbg !2447
  br label %return, !dbg !2447

return:                                           ; preds = %if.end, %if.then
  %15 = load i64, i64* %retval, align 8, !dbg !2448
  ret i64 %15, !dbg !2448
}

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #4

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #5

; Function Attrs: nounwind
declare i32 @sprintf(i8*, i8*, ...) #6

; Function Attrs: nounwind uwtable
define internal zeroext i1 @dprintf_IsQualifierNoDollar(i8* %fmt) #0 !dbg !211 {
entry:
  %retval = alloca i1, align 1
  %fmt.addr = alloca i8*, align 8
  store i8* %fmt, i8** %fmt.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %fmt.addr, metadata !2449, metadata !236), !dbg !2450
  %0 = load i8*, i8** %fmt.addr, align 8, !dbg !2451
  %1 = load i8, i8* %0, align 1, !dbg !2452
  %conv = sext i8 %1 to i32, !dbg !2452
  switch i32 %conv, label %sw.default [
    i32 45, label %sw.bb
    i32 43, label %sw.bb
    i32 32, label %sw.bb
    i32 35, label %sw.bb
    i32 46, label %sw.bb
    i32 48, label %sw.bb
    i32 49, label %sw.bb
    i32 50, label %sw.bb
    i32 51, label %sw.bb
    i32 52, label %sw.bb
    i32 53, label %sw.bb
    i32 54, label %sw.bb
    i32 55, label %sw.bb
    i32 56, label %sw.bb
    i32 57, label %sw.bb
    i32 104, label %sw.bb
    i32 108, label %sw.bb
    i32 76, label %sw.bb
    i32 122, label %sw.bb
    i32 113, label %sw.bb
    i32 42, label %sw.bb
    i32 79, label %sw.bb
  ], !dbg !2453

sw.bb:                                            ; preds = %entry, %entry, %entry, %entry, %entry, %entry, %entry, %entry, %entry, %entry, %entry, %entry, %entry, %entry, %entry, %entry, %entry, %entry, %entry, %entry, %entry, %entry
  store i1 true, i1* %retval, align 1, !dbg !2454
  br label %return, !dbg !2454

sw.default:                                       ; preds = %entry
  store i1 false, i1* %retval, align 1, !dbg !2456
  br label %return, !dbg !2456

return:                                           ; preds = %sw.default, %sw.bb
  %2 = load i1, i1* %retval, align 1, !dbg !2457
  ret i1 %2, !dbg !2457
}

; Function Attrs: nounwind
declare i64 @strtol(i8*, i8**, i32) #6

; Function Attrs: nounwind readnone
declare i16** @__ctype_b_loc() #7

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { argmemonly nounwind }
attributes #6 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #8 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!232, !233}
!llvm.ident = !{!234}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !53, subprograms: !139, globals: !221)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/mprintf.c", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!2 = !{!3, !15, !38}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !1, line: 114, size: 32, align: 32, elements: !4)
!4 = !{!5, !6, !7, !8, !9, !10, !11, !12, !13, !14}
!5 = !DIEnumerator(name: "FORMAT_UNKNOWN", value: 0)
!6 = !DIEnumerator(name: "FORMAT_STRING", value: 1)
!7 = !DIEnumerator(name: "FORMAT_PTR", value: 2)
!8 = !DIEnumerator(name: "FORMAT_INT", value: 3)
!9 = !DIEnumerator(name: "FORMAT_INTPTR", value: 4)
!10 = !DIEnumerator(name: "FORMAT_LONG", value: 5)
!11 = !DIEnumerator(name: "FORMAT_LONGLONG", value: 6)
!12 = !DIEnumerator(name: "FORMAT_DOUBLE", value: 7)
!13 = !DIEnumerator(name: "FORMAT_LONGDOUBLE", value: 8)
!14 = !DIEnumerator(name: "FORMAT_WIDTH", value: 9)
!15 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !1, line: 128, size: 32, align: 32, elements: !16)
!16 = !{!17, !18, !19, !20, !21, !22, !23, !24, !25, !26, !27, !28, !29, !30, !31, !32, !33, !34, !35, !36, !37}
!17 = !DIEnumerator(name: "FLAGS_NEW", value: 0)
!18 = !DIEnumerator(name: "FLAGS_SPACE", value: 1)
!19 = !DIEnumerator(name: "FLAGS_SHOWSIGN", value: 2)
!20 = !DIEnumerator(name: "FLAGS_LEFT", value: 4)
!21 = !DIEnumerator(name: "FLAGS_ALT", value: 8)
!22 = !DIEnumerator(name: "FLAGS_SHORT", value: 16)
!23 = !DIEnumerator(name: "FLAGS_LONG", value: 32)
!24 = !DIEnumerator(name: "FLAGS_LONGLONG", value: 64)
!25 = !DIEnumerator(name: "FLAGS_LONGDOUBLE", value: 128)
!26 = !DIEnumerator(name: "FLAGS_PAD_NIL", value: 256)
!27 = !DIEnumerator(name: "FLAGS_UNSIGNED", value: 512)
!28 = !DIEnumerator(name: "FLAGS_OCTAL", value: 1024)
!29 = !DIEnumerator(name: "FLAGS_HEX", value: 2048)
!30 = !DIEnumerator(name: "FLAGS_UPPER", value: 4096)
!31 = !DIEnumerator(name: "FLAGS_WIDTH", value: 8192)
!32 = !DIEnumerator(name: "FLAGS_WIDTHPARAM", value: 16384)
!33 = !DIEnumerator(name: "FLAGS_PREC", value: 32768)
!34 = !DIEnumerator(name: "FLAGS_PRECPARAM", value: 65536)
!35 = !DIEnumerator(name: "FLAGS_CHAR", value: 131072)
!36 = !DIEnumerator(name: "FLAGS_FLOATE", value: 262144)
!37 = !DIEnumerator(name: "FLAGS_FLOATG", value: 524288)
!38 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !39, line: 46, size: 32, align: 32, elements: !40)
!39 = !DIFile(filename: "/usr/include/ctype.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!40 = !{!41, !42, !43, !44, !45, !46, !47, !48, !49, !50, !51, !52}
!41 = !DIEnumerator(name: "_ISupper", value: 256)
!42 = !DIEnumerator(name: "_ISlower", value: 512)
!43 = !DIEnumerator(name: "_ISalpha", value: 1024)
!44 = !DIEnumerator(name: "_ISdigit", value: 2048)
!45 = !DIEnumerator(name: "_ISxdigit", value: 4096)
!46 = !DIEnumerator(name: "_ISspace", value: 8192)
!47 = !DIEnumerator(name: "_ISprint", value: 16384)
!48 = !DIEnumerator(name: "_ISgraph", value: 32768)
!49 = !DIEnumerator(name: "_ISblank", value: 1)
!50 = !DIEnumerator(name: "_IScntrl", value: 2)
!51 = !DIEnumerator(name: "_ISpunct", value: 4)
!52 = !DIEnumerator(name: "_ISalnum", value: 8)
!53 = !{!54, !56, !57, !90, !55, !118, !119, !105, !110, !120, !121, !64, !122, !123, !124, !92, !125, !131, !138}
!54 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !55, size: 64, align: 64)
!55 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!56 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!57 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !58, size: 64, align: 64)
!58 = !DIDerivedType(tag: DW_TAG_typedef, name: "FILE", file: !59, line: 48, baseType: !60)
!59 = !DIFile(filename: "/usr/include/stdio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!60 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_FILE", file: !61, line: 245, size: 1728, align: 64, elements: !62)
!61 = !DIFile(filename: "/usr/include/libio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!62 = !{!63, !65, !66, !67, !68, !69, !70, !71, !72, !73, !74, !75, !76, !84, !85, !86, !87, !91, !93, !95, !99, !102, !104, !106, !107, !108, !109, !113, !114}
!63 = !DIDerivedType(tag: DW_TAG_member, name: "_flags", scope: !60, file: !61, line: 246, baseType: !64, size: 32, align: 32)
!64 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!65 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_ptr", scope: !60, file: !61, line: 251, baseType: !54, size: 64, align: 64, offset: 64)
!66 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_end", scope: !60, file: !61, line: 252, baseType: !54, size: 64, align: 64, offset: 128)
!67 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_base", scope: !60, file: !61, line: 253, baseType: !54, size: 64, align: 64, offset: 192)
!68 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_base", scope: !60, file: !61, line: 254, baseType: !54, size: 64, align: 64, offset: 256)
!69 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_ptr", scope: !60, file: !61, line: 255, baseType: !54, size: 64, align: 64, offset: 320)
!70 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_end", scope: !60, file: !61, line: 256, baseType: !54, size: 64, align: 64, offset: 384)
!71 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_base", scope: !60, file: !61, line: 257, baseType: !54, size: 64, align: 64, offset: 448)
!72 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_end", scope: !60, file: !61, line: 258, baseType: !54, size: 64, align: 64, offset: 512)
!73 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_base", scope: !60, file: !61, line: 260, baseType: !54, size: 64, align: 64, offset: 576)
!74 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_backup_base", scope: !60, file: !61, line: 261, baseType: !54, size: 64, align: 64, offset: 640)
!75 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_end", scope: !60, file: !61, line: 262, baseType: !54, size: 64, align: 64, offset: 704)
!76 = !DIDerivedType(tag: DW_TAG_member, name: "_markers", scope: !60, file: !61, line: 264, baseType: !77, size: 64, align: 64, offset: 768)
!77 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !78, size: 64, align: 64)
!78 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_marker", file: !61, line: 160, size: 192, align: 64, elements: !79)
!79 = !{!80, !81, !83}
!80 = !DIDerivedType(tag: DW_TAG_member, name: "_next", scope: !78, file: !61, line: 161, baseType: !77, size: 64, align: 64)
!81 = !DIDerivedType(tag: DW_TAG_member, name: "_sbuf", scope: !78, file: !61, line: 162, baseType: !82, size: 64, align: 64, offset: 64)
!82 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !60, size: 64, align: 64)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "_pos", scope: !78, file: !61, line: 166, baseType: !64, size: 32, align: 32, offset: 128)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "_chain", scope: !60, file: !61, line: 266, baseType: !82, size: 64, align: 64, offset: 832)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "_fileno", scope: !60, file: !61, line: 268, baseType: !64, size: 32, align: 32, offset: 896)
!86 = !DIDerivedType(tag: DW_TAG_member, name: "_flags2", scope: !60, file: !61, line: 272, baseType: !64, size: 32, align: 32, offset: 928)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "_old_offset", scope: !60, file: !61, line: 274, baseType: !88, size: 64, align: 64, offset: 960)
!88 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off_t", file: !89, line: 131, baseType: !90)
!89 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!90 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!91 = !DIDerivedType(tag: DW_TAG_member, name: "_cur_column", scope: !60, file: !61, line: 278, baseType: !92, size: 16, align: 16, offset: 1024)
!92 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!93 = !DIDerivedType(tag: DW_TAG_member, name: "_vtable_offset", scope: !60, file: !61, line: 279, baseType: !94, size: 8, align: 8, offset: 1040)
!94 = !DIBasicType(name: "signed char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!95 = !DIDerivedType(tag: DW_TAG_member, name: "_shortbuf", scope: !60, file: !61, line: 280, baseType: !96, size: 8, align: 8, offset: 1048)
!96 = !DICompositeType(tag: DW_TAG_array_type, baseType: !55, size: 8, align: 8, elements: !97)
!97 = !{!98}
!98 = !DISubrange(count: 1)
!99 = !DIDerivedType(tag: DW_TAG_member, name: "_lock", scope: !60, file: !61, line: 284, baseType: !100, size: 64, align: 64, offset: 1088)
!100 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !101, size: 64, align: 64)
!101 = !DIDerivedType(tag: DW_TAG_typedef, name: "_IO_lock_t", file: !61, line: 154, baseType: null)
!102 = !DIDerivedType(tag: DW_TAG_member, name: "_offset", scope: !60, file: !61, line: 293, baseType: !103, size: 64, align: 64, offset: 1152)
!103 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off64_t", file: !89, line: 132, baseType: !90)
!104 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !60, file: !61, line: 302, baseType: !105, size: 64, align: 64, offset: 1216)
!105 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !60, file: !61, line: 303, baseType: !105, size: 64, align: 64, offset: 1280)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "__pad3", scope: !60, file: !61, line: 304, baseType: !105, size: 64, align: 64, offset: 1344)
!108 = !DIDerivedType(tag: DW_TAG_member, name: "__pad4", scope: !60, file: !61, line: 305, baseType: !105, size: 64, align: 64, offset: 1408)
!109 = !DIDerivedType(tag: DW_TAG_member, name: "__pad5", scope: !60, file: !61, line: 306, baseType: !110, size: 64, align: 64, offset: 1472)
!110 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !111, line: 62, baseType: !112)
!111 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!112 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "_mode", scope: !60, file: !61, line: 308, baseType: !64, size: 32, align: 32, offset: 1536)
!114 = !DIDerivedType(tag: DW_TAG_member, name: "_unused2", scope: !60, file: !61, line: 310, baseType: !115, size: 160, align: 8, offset: 1568)
!115 = !DICompositeType(tag: DW_TAG_array_type, baseType: !55, size: 160, align: 8, elements: !116)
!116 = !{!117}
!117 = !DISubrange(count: 20)
!118 = !DIBasicType(name: "long long int", size: 64, align: 64, encoding: DW_ATE_signed)
!119 = !DIBasicType(name: "long long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!120 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !118, size: 64, align: 64)
!121 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !90, size: 64, align: 64)
!122 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !64, size: 64, align: 64)
!123 = !DIBasicType(name: "short", size: 16, align: 16, encoding: DW_ATE_signed)
!124 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !123, size: 64, align: 64)
!125 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !126, size: 64, align: 64)
!126 = !DICompositeType(tag: DW_TAG_structure_type, name: "nsprintf", file: !1, line: 168, size: 192, align: 64, elements: !127)
!127 = !{!128, !129, !130}
!128 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !126, file: !1, line: 169, baseType: !54, size: 64, align: 64)
!129 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !126, file: !1, line: 170, baseType: !110, size: 64, align: 64, offset: 64)
!130 = !DIDerivedType(tag: DW_TAG_member, name: "max", scope: !126, file: !1, line: 171, baseType: !110, size: 64, align: 64, offset: 128)
!131 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !132, size: 64, align: 64)
!132 = !DICompositeType(tag: DW_TAG_structure_type, name: "asprintf", file: !1, line: 174, size: 256, align: 64, elements: !133)
!133 = !{!134, !135, !136, !137}
!134 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !132, file: !1, line: 175, baseType: !54, size: 64, align: 64)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "len", scope: !132, file: !1, line: 176, baseType: !110, size: 64, align: 64, offset: 64)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "alloc", scope: !132, file: !1, line: 177, baseType: !110, size: 64, align: 64, offset: 128)
!137 = !DIDerivedType(tag: DW_TAG_member, name: "fail", scope: !132, file: !1, line: 178, baseType: !64, size: 32, align: 32, offset: 192)
!138 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !54, size: 64, align: 64)
!139 = !{!140, !154, !157, !160, !163, !166, !169, !172, !175, !178, !181, !187, !211, !215, !218, !219, !220}
!140 = distinct !DISubprogram(name: "curl_mvsnprintf", scope: !1, file: !1, line: 1002, type: !141, isLocal: false, isDefinition: true, scopeLine: 1004, flags: DIFlagPrototyped, isOptimized: false, variables: !153)
!141 = !DISubroutineType(types: !142)
!142 = !{!64, !54, !110, !143, !145}
!143 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !144, size: 64, align: 64)
!144 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !55)
!145 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !146, size: 64, align: 64)
!146 = !DICompositeType(tag: DW_TAG_structure_type, name: "__va_list_tag", file: !1, size: 192, align: 64, elements: !147)
!147 = !{!148, !150, !151, !152}
!148 = !DIDerivedType(tag: DW_TAG_member, name: "gp_offset", scope: !146, file: !1, baseType: !149, size: 32, align: 32)
!149 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!150 = !DIDerivedType(tag: DW_TAG_member, name: "fp_offset", scope: !146, file: !1, baseType: !149, size: 32, align: 32, offset: 32)
!151 = !DIDerivedType(tag: DW_TAG_member, name: "overflow_arg_area", scope: !146, file: !1, baseType: !105, size: 64, align: 64, offset: 64)
!152 = !DIDerivedType(tag: DW_TAG_member, name: "reg_save_area", scope: !146, file: !1, baseType: !105, size: 64, align: 64, offset: 128)
!153 = !{}
!154 = distinct !DISubprogram(name: "curl_msnprintf", scope: !1, file: !1, line: 1024, type: !155, isLocal: false, isDefinition: true, scopeLine: 1025, flags: DIFlagPrototyped, isOptimized: false, variables: !153)
!155 = !DISubroutineType(types: !156)
!156 = !{!64, !54, !110, !143, null}
!157 = distinct !DISubprogram(name: "curl_maprintf", scope: !1, file: !1, line: 1072, type: !158, isLocal: false, isDefinition: true, scopeLine: 1073, flags: DIFlagPrototyped, isOptimized: false, variables: !153)
!158 = !DISubroutineType(types: !159)
!159 = !{!54, !143, null}
!160 = distinct !DISubprogram(name: "curl_mvaprintf", scope: !1, file: !1, line: 1098, type: !161, isLocal: false, isDefinition: true, scopeLine: 1099, flags: DIFlagPrototyped, isOptimized: false, variables: !153)
!161 = !DISubroutineType(types: !162)
!162 = !{!54, !143, !145}
!163 = distinct !DISubprogram(name: "curl_msprintf", scope: !1, file: !1, line: 1131, type: !164, isLocal: false, isDefinition: true, scopeLine: 1132, flags: DIFlagPrototyped, isOptimized: false, variables: !153)
!164 = !DISubroutineType(types: !165)
!165 = !{!64, !54, !143, null}
!166 = distinct !DISubprogram(name: "curl_mprintf", scope: !1, file: !1, line: 1142, type: !167, isLocal: false, isDefinition: true, scopeLine: 1143, flags: DIFlagPrototyped, isOptimized: false, variables: !153)
!167 = !DISubroutineType(types: !168)
!168 = !{!64, !143, null}
!169 = distinct !DISubprogram(name: "curl_mfprintf", scope: !1, file: !1, line: 1153, type: !170, isLocal: false, isDefinition: true, scopeLine: 1154, flags: DIFlagPrototyped, isOptimized: false, variables: !153)
!170 = !DISubroutineType(types: !171)
!171 = !{!64, !57, !143, null}
!172 = distinct !DISubprogram(name: "curl_mvsprintf", scope: !1, file: !1, line: 1163, type: !173, isLocal: false, isDefinition: true, scopeLine: 1164, flags: DIFlagPrototyped, isOptimized: false, variables: !153)
!173 = !DISubroutineType(types: !174)
!174 = !{!64, !54, !143, !145}
!175 = distinct !DISubprogram(name: "curl_mvprintf", scope: !1, file: !1, line: 1171, type: !176, isLocal: false, isDefinition: true, scopeLine: 1172, flags: DIFlagPrototyped, isOptimized: false, variables: !153)
!176 = !DISubroutineType(types: !177)
!177 = !{!64, !143, !145}
!178 = distinct !DISubprogram(name: "curl_mvfprintf", scope: !1, file: !1, line: 1176, type: !179, isLocal: false, isDefinition: true, scopeLine: 1177, flags: DIFlagPrototyped, isOptimized: false, variables: !153)
!179 = !DISubroutineType(types: !180)
!180 = !{!64, !57, !143, !145}
!181 = distinct !DISubprogram(name: "dprintf_formatf", scope: !1, file: !1, line: 558, type: !182, isLocal: true, isDefinition: true, scopeLine: 565, flags: DIFlagPrototyped, isOptimized: false, variables: !153)
!182 = !DISubroutineType(types: !183)
!183 = !{!64, !105, !184, !143, !145}
!184 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !185, size: 64, align: 64)
!185 = !DISubroutineType(types: !186)
!186 = !{!64, !64, !57}
!187 = distinct !DISubprogram(name: "dprintf_Pass1", scope: !1, file: !1, line: 231, type: !188, isLocal: true, isDefinition: true, scopeLine: 233, flags: DIFlagPrototyped, isOptimized: false, variables: !153)
!188 = !DISubroutineType(types: !189)
!189 = !{!64, !143, !190, !138, !145}
!190 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !191, size: 64, align: 64)
!191 = !DIDerivedType(tag: DW_TAG_typedef, name: "va_stack_t", file: !1, line: 166, baseType: !192)
!192 = !DICompositeType(tag: DW_TAG_structure_type, file: !1, line: 152, size: 256, align: 64, elements: !193)
!193 = !{!194, !196, !197, !198, !199}
!194 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !192, file: !1, line: 153, baseType: !195, size: 32, align: 32)
!195 = !DIDerivedType(tag: DW_TAG_typedef, name: "FormatType", file: !1, line: 125, baseType: !3)
!196 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !192, file: !1, line: 154, baseType: !64, size: 32, align: 32, offset: 32)
!197 = !DIDerivedType(tag: DW_TAG_member, name: "width", scope: !192, file: !1, line: 155, baseType: !90, size: 64, align: 64, offset: 64)
!198 = !DIDerivedType(tag: DW_TAG_member, name: "precision", scope: !192, file: !1, line: 156, baseType: !90, size: 64, align: 64, offset: 128)
!199 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !192, file: !1, line: 165, baseType: !200, size: 64, align: 64, offset: 192)
!200 = !DICompositeType(tag: DW_TAG_union_type, scope: !192, file: !1, line: 157, size: 64, align: 64, elements: !201)
!201 = !{!202, !203, !204, !209}
!202 = !DIDerivedType(tag: DW_TAG_member, name: "str", scope: !200, file: !1, line: 158, baseType: !54, size: 64, align: 64)
!203 = !DIDerivedType(tag: DW_TAG_member, name: "ptr", scope: !200, file: !1, line: 159, baseType: !105, size: 64, align: 64)
!204 = !DIDerivedType(tag: DW_TAG_member, name: "num", scope: !200, file: !1, line: 163, baseType: !205, size: 64, align: 64)
!205 = !DICompositeType(tag: DW_TAG_union_type, scope: !200, file: !1, line: 160, size: 64, align: 64, elements: !206)
!206 = !{!207, !208}
!207 = !DIDerivedType(tag: DW_TAG_member, name: "as_signed", scope: !205, file: !1, line: 161, baseType: !118, size: 64, align: 64)
!208 = !DIDerivedType(tag: DW_TAG_member, name: "as_unsigned", scope: !205, file: !1, line: 162, baseType: !119, size: 64, align: 64)
!209 = !DIDerivedType(tag: DW_TAG_member, name: "dnum", scope: !200, file: !1, line: 164, baseType: !210, size: 64, align: 64)
!210 = !DIBasicType(name: "double", size: 64, align: 64, encoding: DW_ATE_float)
!211 = distinct !DISubprogram(name: "dprintf_IsQualifierNoDollar", scope: !1, file: !1, line: 197, type: !212, isLocal: true, isDefinition: true, scopeLine: 198, flags: DIFlagPrototyped, isOptimized: false, variables: !153)
!212 = !DISubroutineType(types: !213)
!213 = !{!214, !143}
!214 = !DIBasicType(name: "_Bool", size: 8, align: 8, encoding: DW_ATE_boolean)
!215 = distinct !DISubprogram(name: "dprintf_DollarString", scope: !1, file: !1, line: 182, type: !216, isLocal: true, isDefinition: true, scopeLine: 183, flags: DIFlagPrototyped, isOptimized: false, variables: !153)
!216 = !DISubroutineType(types: !217)
!217 = !{!90, !54, !138}
!218 = distinct !DISubprogram(name: "addbyter", scope: !1, file: !1, line: 987, type: !185, isLocal: true, isDefinition: true, scopeLine: 988, flags: DIFlagPrototyped, isOptimized: false, variables: !153)
!219 = distinct !DISubprogram(name: "alloc_addbyter", scope: !1, file: !1, line: 1035, type: !185, isLocal: true, isDefinition: true, scopeLine: 1036, flags: DIFlagPrototyped, isOptimized: false, variables: !153)
!220 = distinct !DISubprogram(name: "storebuffer", scope: !1, file: !1, line: 1122, type: !185, isLocal: true, isDefinition: true, scopeLine: 1123, flags: DIFlagPrototyped, isOptimized: false, variables: !153)
!221 = !{!222, !226, !227, !231}
!222 = !DIGlobalVariable(name: "null", scope: !181, file: !1, line: 810, type: !223, isLocal: true, isDefinition: true, variable: [6 x i8]* @dprintf_formatf.null)
!223 = !DICompositeType(tag: DW_TAG_array_type, baseType: !144, size: 48, align: 8, elements: !224)
!224 = !{!225}
!225 = !DISubrange(count: 6)
!226 = !DIGlobalVariable(name: "strnil", scope: !181, file: !1, line: 869, type: !223, isLocal: true, isDefinition: true, variable: [6 x i8]* @dprintf_formatf.strnil)
!227 = !DIGlobalVariable(name: "lower_digits", scope: !0, file: !1, line: 100, type: !228, isLocal: true, isDefinition: true, variable: [37 x i8]* @lower_digits)
!228 = !DICompositeType(tag: DW_TAG_array_type, baseType: !144, size: 296, align: 8, elements: !229)
!229 = !{!230}
!230 = !DISubrange(count: 37)
!231 = !DIGlobalVariable(name: "upper_digits", scope: !0, file: !1, line: 103, type: !228, isLocal: true, isDefinition: true, variable: [37 x i8]* @upper_digits)
!232 = !{i32 2, !"Dwarf Version", i32 4}
!233 = !{i32 2, !"Debug Info Version", i32 3}
!234 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!235 = !DILocalVariable(name: "buffer", arg: 1, scope: !140, file: !1, line: 1002, type: !54)
!236 = !DIExpression()
!237 = !DILocation(line: 1002, column: 27, scope: !140)
!238 = !DILocalVariable(name: "maxlength", arg: 2, scope: !140, file: !1, line: 1002, type: !110)
!239 = !DILocation(line: 1002, column: 42, scope: !140)
!240 = !DILocalVariable(name: "format", arg: 3, scope: !140, file: !1, line: 1002, type: !143)
!241 = !DILocation(line: 1002, column: 65, scope: !140)
!242 = !DILocalVariable(name: "ap_save", arg: 4, scope: !140, file: !1, line: 1003, type: !145)
!243 = !DILocation(line: 1003, column: 29, scope: !140)
!244 = !DILocalVariable(name: "retcode", scope: !140, file: !1, line: 1005, type: !64)
!245 = !DILocation(line: 1005, column: 7, scope: !140)
!246 = !DILocalVariable(name: "info", scope: !140, file: !1, line: 1006, type: !126)
!247 = !DILocation(line: 1006, column: 19, scope: !140)
!248 = !DILocation(line: 1008, column: 17, scope: !140)
!249 = !DILocation(line: 1008, column: 8, scope: !140)
!250 = !DILocation(line: 1008, column: 15, scope: !140)
!251 = !DILocation(line: 1009, column: 8, scope: !140)
!252 = !DILocation(line: 1009, column: 15, scope: !140)
!253 = !DILocation(line: 1010, column: 14, scope: !140)
!254 = !DILocation(line: 1010, column: 8, scope: !140)
!255 = !DILocation(line: 1010, column: 12, scope: !140)
!256 = !DILocation(line: 1012, column: 29, scope: !140)
!257 = !DILocation(line: 1012, column: 46, scope: !140)
!258 = !DILocation(line: 1012, column: 54, scope: !140)
!259 = !DILocation(line: 1012, column: 13, scope: !140)
!260 = !DILocation(line: 1012, column: 11, scope: !140)
!261 = !DILocation(line: 1013, column: 7, scope: !262)
!262 = distinct !DILexicalBlock(scope: !140, file: !1, line: 1013, column: 6)
!263 = !DILocation(line: 1013, column: 15, scope: !262)
!264 = !DILocation(line: 1013, column: 22, scope: !262)
!265 = !DILocation(line: 1013, column: 30, scope: !266)
!266 = !DILexicalBlockFile(scope: !262, file: !1, discriminator: 1)
!267 = !DILocation(line: 1013, column: 25, scope: !266)
!268 = !DILocation(line: 1013, column: 6, scope: !266)
!269 = !DILocation(line: 1015, column: 13, scope: !270)
!270 = distinct !DILexicalBlock(scope: !271, file: !1, line: 1015, column: 8)
!271 = distinct !DILexicalBlock(scope: !262, file: !1, line: 1013, column: 35)
!272 = !DILocation(line: 1015, column: 25, scope: !270)
!273 = !DILocation(line: 1015, column: 17, scope: !270)
!274 = !DILocation(line: 1015, column: 8, scope: !271)
!275 = !DILocation(line: 1017, column: 12, scope: !270)
!276 = !DILocation(line: 1017, column: 7, scope: !270)
!277 = !DILocation(line: 1017, column: 23, scope: !270)
!278 = !DILocation(line: 1019, column: 12, scope: !270)
!279 = !DILocation(line: 1019, column: 7, scope: !270)
!280 = !DILocation(line: 1019, column: 22, scope: !270)
!281 = !DILocation(line: 1020, column: 3, scope: !271)
!282 = !DILocation(line: 1021, column: 10, scope: !140)
!283 = !DILocation(line: 1021, column: 3, scope: !140)
!284 = !DILocalVariable(name: "data", arg: 1, scope: !181, file: !1, line: 559, type: !105)
!285 = !DILocation(line: 559, column: 9, scope: !181)
!286 = !DILocalVariable(name: "stream", arg: 2, scope: !181, file: !1, line: 562, type: !184)
!287 = !DILocation(line: 562, column: 9, scope: !181)
!288 = !DILocalVariable(name: "format", arg: 3, scope: !181, file: !1, line: 563, type: !143)
!289 = !DILocation(line: 563, column: 15, scope: !181)
!290 = !DILocalVariable(name: "ap_save", arg: 4, scope: !181, file: !1, line: 564, type: !145)
!291 = !DILocation(line: 564, column: 11, scope: !181)
!292 = !DILocalVariable(name: "digits", scope: !181, file: !1, line: 567, type: !143)
!293 = !DILocation(line: 567, column: 15, scope: !181)
!294 = !DILocalVariable(name: "f", scope: !181, file: !1, line: 570, type: !54)
!295 = !DILocation(line: 570, column: 9, scope: !181)
!296 = !DILocalVariable(name: "done", scope: !181, file: !1, line: 573, type: !64)
!297 = !DILocation(line: 573, column: 7, scope: !181)
!298 = !DILocalVariable(name: "param", scope: !181, file: !1, line: 575, type: !90)
!299 = !DILocation(line: 575, column: 8, scope: !181)
!300 = !DILocalVariable(name: "param_num", scope: !181, file: !1, line: 576, type: !90)
!301 = !DILocation(line: 576, column: 8, scope: !181)
!302 = !DILocalVariable(name: "vto", scope: !181, file: !1, line: 578, type: !303)
!303 = !DICompositeType(tag: DW_TAG_array_type, baseType: !191, size: 32768, align: 64, elements: !304)
!304 = !{!305}
!305 = !DISubrange(count: 128)
!306 = !DILocation(line: 578, column: 14, scope: !181)
!307 = !DILocalVariable(name: "endpos", scope: !181, file: !1, line: 579, type: !308)
!308 = !DICompositeType(tag: DW_TAG_array_type, baseType: !54, size: 8192, align: 64, elements: !304)
!309 = !DILocation(line: 579, column: 9, scope: !181)
!310 = !DILocalVariable(name: "end", scope: !181, file: !1, line: 580, type: !138)
!311 = !DILocation(line: 580, column: 10, scope: !181)
!312 = !DILocalVariable(name: "work", scope: !181, file: !1, line: 582, type: !313)
!313 = !DICompositeType(tag: DW_TAG_array_type, baseType: !55, size: 2608, align: 8, elements: !314)
!314 = !{!315}
!315 = !DISubrange(count: 326)
!316 = !DILocation(line: 582, column: 8, scope: !181)
!317 = !DILocalVariable(name: "p", scope: !181, file: !1, line: 584, type: !190)
!318 = !DILocation(line: 584, column: 15, scope: !181)
!319 = !DILocalVariable(name: "workend", scope: !181, file: !1, line: 589, type: !54)
!320 = !DILocation(line: 589, column: 9, scope: !181)
!321 = !DILocation(line: 589, column: 20, scope: !181)
!322 = !DILocation(line: 592, column: 20, scope: !323)
!323 = distinct !DILexicalBlock(scope: !181, file: !1, line: 592, column: 6)
!324 = !DILocation(line: 592, column: 28, scope: !323)
!325 = !DILocation(line: 592, column: 33, scope: !323)
!326 = !DILocation(line: 592, column: 41, scope: !323)
!327 = !DILocation(line: 592, column: 6, scope: !323)
!328 = !DILocation(line: 592, column: 6, scope: !181)
!329 = !DILocation(line: 593, column: 5, scope: !323)
!330 = !DILocation(line: 595, column: 10, scope: !181)
!331 = !DILocation(line: 595, column: 7, scope: !181)
!332 = !DILocation(line: 598, column: 15, scope: !181)
!333 = !DILocation(line: 598, column: 5, scope: !181)
!334 = !DILocation(line: 599, column: 3, scope: !181)
!335 = !DILocation(line: 599, column: 10, scope: !336)
!336 = !DILexicalBlockFile(scope: !181, file: !1, discriminator: 1)
!337 = !DILocation(line: 599, column: 9, scope: !336)
!338 = !DILocation(line: 599, column: 12, scope: !336)
!339 = !DILocation(line: 599, column: 3, scope: !336)
!340 = !DILocalVariable(name: "is_alt", scope: !341, file: !1, line: 601, type: !64)
!341 = distinct !DILexicalBlock(scope: !181, file: !1, line: 599, column: 21)
!342 = !DILocation(line: 601, column: 9, scope: !341)
!343 = !DILocalVariable(name: "width", scope: !341, file: !1, line: 604, type: !90)
!344 = !DILocation(line: 604, column: 10, scope: !341)
!345 = !DILocalVariable(name: "prec", scope: !341, file: !1, line: 607, type: !90)
!346 = !DILocation(line: 607, column: 10, scope: !341)
!347 = !DILocalVariable(name: "is_neg", scope: !341, file: !1, line: 610, type: !64)
!348 = !DILocation(line: 610, column: 9, scope: !341)
!349 = !DILocalVariable(name: "base", scope: !341, file: !1, line: 613, type: !90)
!350 = !DILocation(line: 613, column: 10, scope: !341)
!351 = !DILocalVariable(name: "num", scope: !341, file: !1, line: 616, type: !119)
!352 = !DILocation(line: 616, column: 18, scope: !341)
!353 = !DILocalVariable(name: "signed_num", scope: !341, file: !1, line: 619, type: !118)
!354 = !DILocation(line: 619, column: 17, scope: !341)
!355 = !DILocalVariable(name: "w", scope: !341, file: !1, line: 621, type: !54)
!356 = !DILocation(line: 621, column: 11, scope: !341)
!357 = !DILocation(line: 623, column: 9, scope: !358)
!358 = distinct !DILexicalBlock(scope: !341, file: !1, line: 623, column: 8)
!359 = !DILocation(line: 623, column: 8, scope: !358)
!360 = !DILocation(line: 623, column: 11, scope: !358)
!361 = !DILocation(line: 623, column: 8, scope: !341)
!362 = !DILocation(line: 626, column: 7, scope: !363)
!363 = distinct !DILexicalBlock(scope: !358, file: !1, line: 623, column: 19)
!364 = !DILocation(line: 627, column: 9, scope: !365)
!365 = distinct !DILexicalBlock(scope: !363, file: !1, line: 626, column: 10)
!366 = !DILocation(line: 627, column: 9, scope: !367)
!367 = !DILexicalBlockFile(scope: !368, file: !1, discriminator: 1)
!368 = distinct !DILexicalBlock(scope: !369, file: !1, line: 627, column: 9)
!369 = distinct !DILexicalBlock(scope: !365, file: !1, line: 627, column: 9)
!370 = !DILocation(line: 627, column: 9, scope: !371)
!371 = !DILexicalBlockFile(scope: !368, file: !1, discriminator: 2)
!372 = !DILocation(line: 627, column: 9, scope: !373)
!373 = !DILexicalBlockFile(scope: !368, file: !1, discriminator: 3)
!374 = !DILocation(line: 627, column: 9, scope: !375)
!375 = !DILexicalBlockFile(scope: !369, file: !1, discriminator: 4)
!376 = !DILocation(line: 628, column: 7, scope: !365)
!377 = !DILocation(line: 628, column: 16, scope: !378)
!378 = !DILexicalBlockFile(scope: !363, file: !1, discriminator: 1)
!379 = !DILocation(line: 628, column: 15, scope: !378)
!380 = !DILocation(line: 628, column: 20, scope: !378)
!381 = !DILocation(line: 628, column: 32, scope: !382)
!382 = !DILexicalBlockFile(scope: !363, file: !1, discriminator: 2)
!383 = !DILocation(line: 628, column: 31, scope: !382)
!384 = !DILocation(line: 628, column: 28, scope: !382)
!385 = !DILocation(line: 628, column: 7, scope: !386)
!386 = !DILexicalBlockFile(scope: !365, file: !1, discriminator: 3)
!387 = !DILocation(line: 629, column: 7, scope: !363)
!388 = !DILocation(line: 632, column: 5, scope: !341)
!389 = !DILocation(line: 638, column: 9, scope: !390)
!390 = distinct !DILexicalBlock(scope: !341, file: !1, line: 638, column: 8)
!391 = !DILocation(line: 638, column: 8, scope: !390)
!392 = !DILocation(line: 638, column: 11, scope: !390)
!393 = !DILocation(line: 638, column: 8, scope: !341)
!394 = !DILocation(line: 639, column: 7, scope: !395)
!395 = distinct !DILexicalBlock(scope: !390, file: !1, line: 638, column: 19)
!396 = !DILocation(line: 640, column: 7, scope: !395)
!397 = !DILocation(line: 640, column: 7, scope: !398)
!398 = !DILexicalBlockFile(scope: !399, file: !1, discriminator: 1)
!399 = distinct !DILexicalBlock(scope: !400, file: !1, line: 640, column: 7)
!400 = distinct !DILexicalBlock(scope: !395, file: !1, line: 640, column: 7)
!401 = !DILocation(line: 640, column: 7, scope: !402)
!402 = !DILexicalBlockFile(scope: !399, file: !1, discriminator: 2)
!403 = !DILocation(line: 640, column: 7, scope: !404)
!404 = !DILexicalBlockFile(scope: !399, file: !1, discriminator: 3)
!405 = !DILocation(line: 640, column: 7, scope: !406)
!406 = !DILexicalBlockFile(scope: !400, file: !1, discriminator: 4)
!407 = !DILocation(line: 641, column: 7, scope: !395)
!408 = !DILocation(line: 646, column: 32, scope: !341)
!409 = !DILocation(line: 646, column: 11, scope: !341)
!410 = !DILocation(line: 646, column: 10, scope: !341)
!411 = !DILocation(line: 648, column: 9, scope: !412)
!412 = distinct !DILexicalBlock(scope: !341, file: !1, line: 648, column: 8)
!413 = !DILocation(line: 648, column: 8, scope: !341)
!414 = !DILocation(line: 649, column: 15, scope: !412)
!415 = !DILocation(line: 649, column: 13, scope: !412)
!416 = !DILocation(line: 649, column: 7, scope: !412)
!417 = !DILocation(line: 651, column: 7, scope: !412)
!418 = !DILocation(line: 653, column: 14, scope: !341)
!419 = !DILocation(line: 656, column: 14, scope: !341)
!420 = !DILocation(line: 656, column: 10, scope: !341)
!421 = !DILocation(line: 656, column: 7, scope: !341)
!422 = !DILocation(line: 659, column: 8, scope: !423)
!423 = distinct !DILexicalBlock(scope: !341, file: !1, line: 659, column: 8)
!424 = !DILocation(line: 659, column: 11, scope: !423)
!425 = !DILocation(line: 659, column: 17, scope: !423)
!426 = !DILocation(line: 659, column: 8, scope: !341)
!427 = !DILocation(line: 660, column: 25, scope: !428)
!428 = distinct !DILexicalBlock(scope: !423, file: !1, line: 659, column: 37)
!429 = !DILocation(line: 660, column: 28, scope: !428)
!430 = !DILocation(line: 660, column: 21, scope: !428)
!431 = !DILocation(line: 660, column: 35, scope: !428)
!432 = !DILocation(line: 660, column: 40, scope: !428)
!433 = !DILocation(line: 660, column: 44, scope: !428)
!434 = !DILocation(line: 660, column: 13, scope: !428)
!435 = !DILocation(line: 661, column: 16, scope: !428)
!436 = !DILocation(line: 663, column: 10, scope: !437)
!437 = distinct !DILexicalBlock(scope: !428, file: !1, line: 663, column: 10)
!438 = !DILocation(line: 663, column: 16, scope: !437)
!439 = !DILocation(line: 663, column: 10, scope: !428)
!440 = !DILocation(line: 666, column: 18, scope: !441)
!441 = distinct !DILexicalBlock(scope: !437, file: !1, line: 663, column: 21)
!442 = !DILocation(line: 666, column: 17, scope: !441)
!443 = !DILocation(line: 666, column: 15, scope: !441)
!444 = !DILocation(line: 667, column: 9, scope: !441)
!445 = !DILocation(line: 667, column: 12, scope: !441)
!446 = !DILocation(line: 667, column: 18, scope: !441)
!447 = !DILocation(line: 668, column: 9, scope: !441)
!448 = !DILocation(line: 668, column: 12, scope: !441)
!449 = !DILocation(line: 668, column: 18, scope: !441)
!450 = !DILocation(line: 669, column: 7, scope: !441)
!451 = !DILocation(line: 670, column: 5, scope: !428)
!452 = !DILocation(line: 672, column: 15, scope: !423)
!453 = !DILocation(line: 672, column: 18, scope: !423)
!454 = !DILocation(line: 672, column: 13, scope: !423)
!455 = !DILocation(line: 675, column: 8, scope: !456)
!456 = distinct !DILexicalBlock(scope: !341, file: !1, line: 675, column: 8)
!457 = !DILocation(line: 675, column: 11, scope: !456)
!458 = !DILocation(line: 675, column: 17, scope: !456)
!459 = !DILocation(line: 675, column: 8, scope: !341)
!460 = !DILocation(line: 676, column: 24, scope: !461)
!461 = distinct !DILexicalBlock(scope: !456, file: !1, line: 675, column: 36)
!462 = !DILocation(line: 676, column: 27, scope: !461)
!463 = !DILocation(line: 676, column: 20, scope: !461)
!464 = !DILocation(line: 676, column: 38, scope: !461)
!465 = !DILocation(line: 676, column: 43, scope: !461)
!466 = !DILocation(line: 676, column: 47, scope: !461)
!467 = !DILocation(line: 676, column: 12, scope: !461)
!468 = !DILocation(line: 677, column: 16, scope: !461)
!469 = !DILocation(line: 679, column: 10, scope: !470)
!470 = distinct !DILexicalBlock(scope: !461, file: !1, line: 679, column: 10)
!471 = !DILocation(line: 679, column: 15, scope: !470)
!472 = !DILocation(line: 679, column: 10, scope: !461)
!473 = !DILocation(line: 682, column: 14, scope: !470)
!474 = !DILocation(line: 682, column: 9, scope: !470)
!475 = !DILocation(line: 683, column: 5, scope: !461)
!476 = !DILocation(line: 684, column: 13, scope: !477)
!477 = distinct !DILexicalBlock(scope: !456, file: !1, line: 684, column: 13)
!478 = !DILocation(line: 684, column: 16, scope: !477)
!479 = !DILocation(line: 684, column: 22, scope: !477)
!480 = !DILocation(line: 684, column: 13, scope: !456)
!481 = !DILocation(line: 685, column: 14, scope: !477)
!482 = !DILocation(line: 685, column: 17, scope: !477)
!483 = !DILocation(line: 685, column: 12, scope: !477)
!484 = !DILocation(line: 685, column: 7, scope: !477)
!485 = !DILocation(line: 687, column: 12, scope: !477)
!486 = !DILocation(line: 689, column: 15, scope: !341)
!487 = !DILocation(line: 689, column: 18, scope: !341)
!488 = !DILocation(line: 689, column: 24, scope: !341)
!489 = !DILocation(line: 689, column: 14, scope: !341)
!490 = !DILocation(line: 689, column: 12, scope: !341)
!491 = !DILocation(line: 691, column: 12, scope: !341)
!492 = !DILocation(line: 691, column: 15, scope: !341)
!493 = !DILocation(line: 691, column: 5, scope: !341)
!494 = !DILocation(line: 693, column: 13, scope: !495)
!495 = distinct !DILexicalBlock(scope: !341, file: !1, line: 691, column: 21)
!496 = !DILocation(line: 693, column: 16, scope: !495)
!497 = !DILocation(line: 693, column: 21, scope: !495)
!498 = !DILocation(line: 693, column: 25, scope: !495)
!499 = !DILocation(line: 693, column: 11, scope: !495)
!500 = !DILocation(line: 694, column: 10, scope: !501)
!501 = distinct !DILexicalBlock(scope: !495, file: !1, line: 694, column: 10)
!502 = !DILocation(line: 694, column: 13, scope: !501)
!503 = !DILocation(line: 694, column: 19, scope: !501)
!504 = !DILocation(line: 694, column: 10, scope: !495)
!505 = !DILocation(line: 696, column: 14, scope: !506)
!506 = distinct !DILexicalBlock(scope: !507, file: !1, line: 696, column: 12)
!507 = distinct !DILexicalBlock(scope: !501, file: !1, line: 694, column: 33)
!508 = !DILocation(line: 696, column: 17, scope: !506)
!509 = !DILocation(line: 696, column: 23, scope: !506)
!510 = !DILocation(line: 696, column: 12, scope: !507)
!511 = !DILocation(line: 697, column: 11, scope: !506)
!512 = !DILocation(line: 697, column: 17, scope: !513)
!513 = !DILexicalBlockFile(scope: !506, file: !1, discriminator: 1)
!514 = !DILocation(line: 697, column: 25, scope: !513)
!515 = !DILocation(line: 697, column: 11, scope: !513)
!516 = !DILocation(line: 698, column: 13, scope: !506)
!517 = !DILocation(line: 698, column: 13, scope: !518)
!518 = !DILexicalBlockFile(scope: !519, file: !1, discriminator: 1)
!519 = distinct !DILexicalBlock(scope: !520, file: !1, line: 698, column: 13)
!520 = distinct !DILexicalBlock(scope: !506, file: !1, line: 698, column: 13)
!521 = !DILocation(line: 698, column: 13, scope: !522)
!522 = !DILexicalBlockFile(scope: !519, file: !1, discriminator: 2)
!523 = !DILocation(line: 698, column: 13, scope: !524)
!524 = !DILexicalBlockFile(scope: !519, file: !1, discriminator: 3)
!525 = !DILocation(line: 698, column: 13, scope: !526)
!526 = !DILexicalBlockFile(scope: !520, file: !1, discriminator: 4)
!527 = !DILocation(line: 697, column: 11, scope: !528)
!528 = !DILexicalBlockFile(scope: !506, file: !1, discriminator: 2)
!529 = !DILocation(line: 697, column: 11, scope: !530)
!530 = !DILexicalBlockFile(scope: !506, file: !1, discriminator: 3)
!531 = !DILocation(line: 699, column: 9, scope: !507)
!532 = !DILocation(line: 699, column: 9, scope: !533)
!533 = !DILexicalBlockFile(scope: !534, file: !1, discriminator: 1)
!534 = distinct !DILexicalBlock(scope: !535, file: !1, line: 699, column: 9)
!535 = distinct !DILexicalBlock(scope: !507, file: !1, line: 699, column: 9)
!536 = !DILocation(line: 699, column: 9, scope: !537)
!537 = !DILexicalBlockFile(scope: !534, file: !1, discriminator: 2)
!538 = !DILocation(line: 699, column: 9, scope: !539)
!539 = !DILexicalBlockFile(scope: !534, file: !1, discriminator: 3)
!540 = !DILocation(line: 699, column: 9, scope: !541)
!541 = !DILexicalBlockFile(scope: !535, file: !1, discriminator: 4)
!542 = !DILocation(line: 700, column: 12, scope: !543)
!543 = distinct !DILexicalBlock(scope: !507, file: !1, line: 700, column: 12)
!544 = !DILocation(line: 700, column: 15, scope: !543)
!545 = !DILocation(line: 700, column: 21, scope: !543)
!546 = !DILocation(line: 700, column: 12, scope: !507)
!547 = !DILocation(line: 701, column: 11, scope: !543)
!548 = !DILocation(line: 701, column: 17, scope: !549)
!549 = !DILexicalBlockFile(scope: !543, file: !1, discriminator: 1)
!550 = !DILocation(line: 701, column: 25, scope: !549)
!551 = !DILocation(line: 701, column: 11, scope: !549)
!552 = !DILocation(line: 702, column: 13, scope: !543)
!553 = !DILocation(line: 702, column: 13, scope: !554)
!554 = !DILexicalBlockFile(scope: !555, file: !1, discriminator: 1)
!555 = distinct !DILexicalBlock(scope: !556, file: !1, line: 702, column: 13)
!556 = distinct !DILexicalBlock(scope: !543, file: !1, line: 702, column: 13)
!557 = !DILocation(line: 702, column: 13, scope: !558)
!558 = !DILexicalBlockFile(scope: !555, file: !1, discriminator: 2)
!559 = !DILocation(line: 702, column: 13, scope: !560)
!560 = !DILexicalBlockFile(scope: !555, file: !1, discriminator: 3)
!561 = !DILocation(line: 702, column: 13, scope: !562)
!562 = !DILexicalBlockFile(scope: !556, file: !1, discriminator: 4)
!563 = !DILocation(line: 701, column: 11, scope: !564)
!564 = !DILexicalBlockFile(scope: !543, file: !1, discriminator: 2)
!565 = !DILocation(line: 701, column: 11, scope: !566)
!566 = !DILexicalBlockFile(scope: !543, file: !1, discriminator: 3)
!567 = !DILocation(line: 703, column: 9, scope: !507)
!568 = !DILocation(line: 705, column: 10, scope: !569)
!569 = distinct !DILexicalBlock(scope: !495, file: !1, line: 705, column: 10)
!570 = !DILocation(line: 705, column: 13, scope: !569)
!571 = !DILocation(line: 705, column: 19, scope: !569)
!572 = !DILocation(line: 705, column: 10, scope: !495)
!573 = !DILocation(line: 707, column: 14, scope: !574)
!574 = distinct !DILexicalBlock(scope: !569, file: !1, line: 705, column: 34)
!575 = !DILocation(line: 708, column: 9, scope: !574)
!576 = !DILocation(line: 710, column: 15, scope: !577)
!577 = distinct !DILexicalBlock(scope: !569, file: !1, line: 710, column: 15)
!578 = !DILocation(line: 710, column: 18, scope: !577)
!579 = !DILocation(line: 710, column: 24, scope: !577)
!580 = !DILocation(line: 710, column: 15, scope: !569)
!581 = !DILocation(line: 713, column: 19, scope: !582)
!582 = distinct !DILexicalBlock(scope: !577, file: !1, line: 710, column: 37)
!583 = !DILocation(line: 713, column: 22, scope: !582)
!584 = !DILocation(line: 713, column: 28, scope: !582)
!585 = !DILocation(line: 713, column: 18, scope: !582)
!586 = !DILocation(line: 713, column: 16, scope: !582)
!587 = !DILocation(line: 714, column: 14, scope: !582)
!588 = !DILocation(line: 715, column: 9, scope: !582)
!589 = !DILocation(line: 717, column: 15, scope: !590)
!590 = distinct !DILexicalBlock(scope: !577, file: !1, line: 717, column: 15)
!591 = !DILocation(line: 717, column: 18, scope: !590)
!592 = !DILocation(line: 717, column: 24, scope: !590)
!593 = !DILocation(line: 717, column: 15, scope: !577)
!594 = !DILocation(line: 719, column: 14, scope: !595)
!595 = distinct !DILexicalBlock(scope: !590, file: !1, line: 717, column: 42)
!596 = !DILocation(line: 720, column: 9, scope: !595)
!597 = !DILocation(line: 724, column: 12, scope: !495)
!598 = !DILocation(line: 726, column: 17, scope: !495)
!599 = !DILocation(line: 726, column: 20, scope: !495)
!600 = !DILocation(line: 726, column: 25, scope: !495)
!601 = !DILocation(line: 726, column: 29, scope: !495)
!602 = !DILocation(line: 726, column: 39, scope: !495)
!603 = !DILocation(line: 726, column: 16, scope: !495)
!604 = !DILocation(line: 726, column: 14, scope: !495)
!605 = !DILocation(line: 727, column: 10, scope: !606)
!606 = distinct !DILexicalBlock(scope: !495, file: !1, line: 727, column: 10)
!607 = !DILocation(line: 727, column: 10, scope: !495)
!608 = !DILocation(line: 729, column: 22, scope: !609)
!609 = distinct !DILexicalBlock(scope: !606, file: !1, line: 727, column: 18)
!610 = !DILocation(line: 729, column: 25, scope: !609)
!611 = !DILocation(line: 729, column: 30, scope: !609)
!612 = !DILocation(line: 729, column: 34, scope: !609)
!613 = !DILocation(line: 729, column: 44, scope: !609)
!614 = !DILocation(line: 729, column: 20, scope: !609)
!615 = !DILocation(line: 730, column: 23, scope: !609)
!616 = !DILocation(line: 730, column: 22, scope: !609)
!617 = !DILocation(line: 730, column: 20, scope: !609)
!618 = !DILocation(line: 731, column: 29, scope: !609)
!619 = !DILocation(line: 731, column: 13, scope: !609)
!620 = !DILocation(line: 732, column: 13, scope: !609)
!621 = !DILocation(line: 733, column: 7, scope: !609)
!622 = !DILocation(line: 735, column: 7, scope: !495)
!623 = !DILocation(line: 739, column: 14, scope: !495)
!624 = !DILocation(line: 739, column: 7, scope: !495)
!625 = !DILocation(line: 745, column: 10, scope: !626)
!626 = distinct !DILexicalBlock(scope: !495, file: !1, line: 745, column: 10)
!627 = !DILocation(line: 745, column: 15, scope: !626)
!628 = !DILocation(line: 745, column: 10, scope: !495)
!629 = !DILocation(line: 746, column: 14, scope: !626)
!630 = !DILocation(line: 746, column: 9, scope: !626)
!631 = !DILocation(line: 749, column: 11, scope: !495)
!632 = !DILocation(line: 749, column: 9, scope: !495)
!633 = !DILocation(line: 750, column: 7, scope: !495)
!634 = !DILocation(line: 750, column: 13, scope: !635)
!635 = !DILexicalBlockFile(scope: !495, file: !1, discriminator: 1)
!636 = !DILocation(line: 750, column: 17, scope: !635)
!637 = !DILocation(line: 750, column: 7, scope: !635)
!638 = !DILocation(line: 751, column: 23, scope: !639)
!639 = distinct !DILexicalBlock(scope: !495, file: !1, line: 750, column: 22)
!640 = !DILocation(line: 751, column: 29, scope: !639)
!641 = !DILocation(line: 751, column: 27, scope: !639)
!642 = !DILocation(line: 751, column: 16, scope: !639)
!643 = !DILocation(line: 751, column: 11, scope: !639)
!644 = !DILocation(line: 751, column: 14, scope: !639)
!645 = !DILocation(line: 752, column: 16, scope: !639)
!646 = !DILocation(line: 752, column: 13, scope: !639)
!647 = !DILocation(line: 750, column: 7, scope: !648)
!648 = !DILexicalBlockFile(scope: !495, file: !1, discriminator: 2)
!649 = !DILocation(line: 754, column: 23, scope: !495)
!650 = !DILocation(line: 754, column: 33, scope: !495)
!651 = !DILocation(line: 754, column: 31, scope: !495)
!652 = !DILocation(line: 754, column: 13, scope: !495)
!653 = !DILocation(line: 755, column: 22, scope: !495)
!654 = !DILocation(line: 755, column: 32, scope: !495)
!655 = !DILocation(line: 755, column: 30, scope: !495)
!656 = !DILocation(line: 755, column: 12, scope: !495)
!657 = !DILocation(line: 757, column: 10, scope: !658)
!658 = distinct !DILexicalBlock(scope: !495, file: !1, line: 757, column: 10)
!659 = !DILocation(line: 757, column: 17, scope: !658)
!660 = !DILocation(line: 757, column: 20, scope: !661)
!661 = !DILexicalBlockFile(scope: !658, file: !1, discriminator: 1)
!662 = !DILocation(line: 757, column: 25, scope: !661)
!663 = !DILocation(line: 757, column: 30, scope: !661)
!664 = !DILocation(line: 757, column: 33, scope: !665)
!665 = !DILexicalBlockFile(scope: !658, file: !1, discriminator: 2)
!666 = !DILocation(line: 757, column: 38, scope: !665)
!667 = !DILocation(line: 757, column: 10, scope: !665)
!668 = !DILocation(line: 758, column: 11, scope: !669)
!669 = distinct !DILexicalBlock(scope: !658, file: !1, line: 757, column: 44)
!670 = !DILocation(line: 758, column: 14, scope: !669)
!671 = !DILocation(line: 759, column: 9, scope: !669)
!672 = !DILocation(line: 760, column: 7, scope: !669)
!673 = !DILocation(line: 762, column: 10, scope: !674)
!674 = distinct !DILexicalBlock(scope: !495, file: !1, line: 762, column: 10)
!675 = !DILocation(line: 762, column: 15, scope: !674)
!676 = !DILocation(line: 762, column: 10, scope: !495)
!677 = !DILocation(line: 763, column: 18, scope: !678)
!678 = distinct !DILexicalBlock(scope: !674, file: !1, line: 762, column: 20)
!679 = !DILocation(line: 763, column: 15, scope: !678)
!680 = !DILocation(line: 764, column: 9, scope: !678)
!681 = !DILocation(line: 764, column: 19, scope: !682)
!682 = !DILexicalBlockFile(scope: !678, file: !1, discriminator: 1)
!683 = !DILocation(line: 764, column: 22, scope: !682)
!684 = !DILocation(line: 764, column: 9, scope: !682)
!685 = !DILocation(line: 765, column: 13, scope: !678)
!686 = !DILocation(line: 765, column: 16, scope: !678)
!687 = !DILocation(line: 764, column: 9, scope: !688)
!688 = !DILexicalBlockFile(scope: !678, file: !1, discriminator: 2)
!689 = !DILocation(line: 766, column: 7, scope: !678)
!690 = !DILocation(line: 768, column: 10, scope: !691)
!691 = distinct !DILexicalBlock(scope: !495, file: !1, line: 768, column: 10)
!692 = !DILocation(line: 768, column: 17, scope: !691)
!693 = !DILocation(line: 768, column: 20, scope: !694)
!694 = !DILexicalBlockFile(scope: !691, file: !1, discriminator: 1)
!695 = !DILocation(line: 768, column: 25, scope: !694)
!696 = !DILocation(line: 768, column: 10, scope: !694)
!697 = !DILocation(line: 769, column: 15, scope: !691)
!698 = !DILocation(line: 769, column: 9, scope: !691)
!699 = !DILocation(line: 771, column: 10, scope: !700)
!700 = distinct !DILexicalBlock(scope: !495, file: !1, line: 771, column: 10)
!701 = !DILocation(line: 771, column: 17, scope: !700)
!702 = !DILocation(line: 771, column: 21, scope: !703)
!703 = !DILexicalBlockFile(scope: !700, file: !1, discriminator: 1)
!704 = !DILocation(line: 771, column: 24, scope: !703)
!705 = !DILocation(line: 771, column: 30, scope: !703)
!706 = !DILocation(line: 771, column: 48, scope: !703)
!707 = !DILocation(line: 771, column: 52, scope: !708)
!708 = !DILexicalBlockFile(scope: !700, file: !1, discriminator: 2)
!709 = !DILocation(line: 771, column: 55, scope: !708)
!710 = !DILocation(line: 771, column: 61, scope: !708)
!711 = !DILocation(line: 771, column: 10, scope: !708)
!712 = !DILocation(line: 772, column: 9, scope: !700)
!713 = !DILocation(line: 774, column: 12, scope: !714)
!714 = distinct !DILexicalBlock(scope: !495, file: !1, line: 774, column: 10)
!715 = !DILocation(line: 774, column: 15, scope: !714)
!716 = !DILocation(line: 774, column: 21, scope: !714)
!717 = !DILocation(line: 774, column: 35, scope: !714)
!718 = !DILocation(line: 774, column: 40, scope: !719)
!719 = !DILexicalBlockFile(scope: !714, file: !1, discriminator: 1)
!720 = !DILocation(line: 774, column: 43, scope: !719)
!721 = !DILocation(line: 774, column: 49, scope: !719)
!722 = !DILocation(line: 774, column: 10, scope: !719)
!723 = !DILocation(line: 775, column: 9, scope: !714)
!724 = !DILocation(line: 775, column: 20, scope: !719)
!725 = !DILocation(line: 775, column: 23, scope: !719)
!726 = !DILocation(line: 775, column: 9, scope: !719)
!727 = !DILocation(line: 776, column: 11, scope: !714)
!728 = !DILocation(line: 776, column: 11, scope: !729)
!729 = !DILexicalBlockFile(scope: !730, file: !1, discriminator: 1)
!730 = distinct !DILexicalBlock(scope: !731, file: !1, line: 776, column: 11)
!731 = distinct !DILexicalBlock(scope: !714, file: !1, line: 776, column: 11)
!732 = !DILocation(line: 776, column: 11, scope: !733)
!733 = !DILexicalBlockFile(scope: !730, file: !1, discriminator: 2)
!734 = !DILocation(line: 776, column: 11, scope: !735)
!735 = !DILexicalBlockFile(scope: !730, file: !1, discriminator: 3)
!736 = !DILocation(line: 776, column: 11, scope: !737)
!737 = !DILexicalBlockFile(scope: !731, file: !1, discriminator: 4)
!738 = !DILocation(line: 775, column: 9, scope: !739)
!739 = !DILexicalBlockFile(scope: !714, file: !1, discriminator: 2)
!740 = !DILocation(line: 775, column: 9, scope: !741)
!741 = !DILexicalBlockFile(scope: !714, file: !1, discriminator: 3)
!742 = !DILocation(line: 778, column: 10, scope: !743)
!743 = distinct !DILexicalBlock(scope: !495, file: !1, line: 778, column: 10)
!744 = !DILocation(line: 778, column: 10, scope: !495)
!745 = !DILocation(line: 779, column: 9, scope: !743)
!746 = !DILocation(line: 779, column: 9, scope: !747)
!747 = !DILexicalBlockFile(scope: !748, file: !1, discriminator: 1)
!748 = distinct !DILexicalBlock(scope: !749, file: !1, line: 779, column: 9)
!749 = distinct !DILexicalBlock(scope: !743, file: !1, line: 779, column: 9)
!750 = !DILocation(line: 779, column: 9, scope: !751)
!751 = !DILexicalBlockFile(scope: !748, file: !1, discriminator: 2)
!752 = !DILocation(line: 779, column: 9, scope: !753)
!753 = !DILexicalBlockFile(scope: !748, file: !1, discriminator: 3)
!754 = !DILocation(line: 779, column: 9, scope: !755)
!755 = !DILexicalBlockFile(scope: !749, file: !1, discriminator: 4)
!756 = !DILocation(line: 779, column: 9, scope: !757)
!757 = !DILexicalBlockFile(scope: !749, file: !1, discriminator: 5)
!758 = !DILocation(line: 780, column: 15, scope: !759)
!759 = distinct !DILexicalBlock(scope: !743, file: !1, line: 780, column: 15)
!760 = !DILocation(line: 780, column: 18, scope: !759)
!761 = !DILocation(line: 780, column: 24, scope: !759)
!762 = !DILocation(line: 780, column: 15, scope: !743)
!763 = !DILocation(line: 781, column: 9, scope: !759)
!764 = !DILocation(line: 781, column: 9, scope: !765)
!765 = !DILexicalBlockFile(scope: !766, file: !1, discriminator: 1)
!766 = distinct !DILexicalBlock(scope: !767, file: !1, line: 781, column: 9)
!767 = distinct !DILexicalBlock(scope: !759, file: !1, line: 781, column: 9)
!768 = !DILocation(line: 781, column: 9, scope: !769)
!769 = !DILexicalBlockFile(scope: !766, file: !1, discriminator: 2)
!770 = !DILocation(line: 781, column: 9, scope: !771)
!771 = !DILexicalBlockFile(scope: !766, file: !1, discriminator: 3)
!772 = !DILocation(line: 781, column: 9, scope: !773)
!773 = !DILexicalBlockFile(scope: !767, file: !1, discriminator: 4)
!774 = !DILocation(line: 781, column: 9, scope: !775)
!775 = !DILexicalBlockFile(scope: !767, file: !1, discriminator: 5)
!776 = !DILocation(line: 782, column: 15, scope: !777)
!777 = distinct !DILexicalBlock(scope: !759, file: !1, line: 782, column: 15)
!778 = !DILocation(line: 782, column: 18, scope: !777)
!779 = !DILocation(line: 782, column: 24, scope: !777)
!780 = !DILocation(line: 782, column: 15, scope: !759)
!781 = !DILocation(line: 783, column: 9, scope: !777)
!782 = !DILocation(line: 783, column: 9, scope: !783)
!783 = !DILexicalBlockFile(scope: !784, file: !1, discriminator: 1)
!784 = distinct !DILexicalBlock(scope: !785, file: !1, line: 783, column: 9)
!785 = distinct !DILexicalBlock(scope: !777, file: !1, line: 783, column: 9)
!786 = !DILocation(line: 783, column: 9, scope: !787)
!787 = !DILexicalBlockFile(scope: !784, file: !1, discriminator: 2)
!788 = !DILocation(line: 783, column: 9, scope: !789)
!789 = !DILexicalBlockFile(scope: !784, file: !1, discriminator: 3)
!790 = !DILocation(line: 783, column: 9, scope: !791)
!791 = !DILexicalBlockFile(scope: !785, file: !1, discriminator: 4)
!792 = !DILocation(line: 783, column: 9, scope: !793)
!793 = !DILexicalBlockFile(scope: !785, file: !1, discriminator: 5)
!794 = !DILocation(line: 785, column: 10, scope: !795)
!795 = distinct !DILexicalBlock(scope: !495, file: !1, line: 785, column: 10)
!796 = !DILocation(line: 785, column: 17, scope: !795)
!797 = !DILocation(line: 785, column: 20, scope: !798)
!798 = !DILexicalBlockFile(scope: !795, file: !1, discriminator: 1)
!799 = !DILocation(line: 785, column: 25, scope: !798)
!800 = !DILocation(line: 785, column: 10, scope: !798)
!801 = !DILocation(line: 786, column: 9, scope: !802)
!802 = distinct !DILexicalBlock(scope: !795, file: !1, line: 785, column: 32)
!803 = !DILocation(line: 786, column: 9, scope: !804)
!804 = !DILexicalBlockFile(scope: !805, file: !1, discriminator: 1)
!805 = distinct !DILexicalBlock(scope: !806, file: !1, line: 786, column: 9)
!806 = distinct !DILexicalBlock(scope: !802, file: !1, line: 786, column: 9)
!807 = !DILocation(line: 786, column: 9, scope: !808)
!808 = !DILexicalBlockFile(scope: !805, file: !1, discriminator: 2)
!809 = !DILocation(line: 786, column: 9, scope: !810)
!810 = !DILexicalBlockFile(scope: !805, file: !1, discriminator: 3)
!811 = !DILocation(line: 786, column: 9, scope: !812)
!812 = !DILexicalBlockFile(scope: !806, file: !1, discriminator: 4)
!813 = !DILocation(line: 787, column: 12, scope: !814)
!814 = distinct !DILexicalBlock(scope: !802, file: !1, line: 787, column: 12)
!815 = !DILocation(line: 787, column: 15, scope: !814)
!816 = !DILocation(line: 787, column: 21, scope: !814)
!817 = !DILocation(line: 787, column: 12, scope: !802)
!818 = !DILocation(line: 788, column: 11, scope: !814)
!819 = !DILocation(line: 788, column: 11, scope: !820)
!820 = !DILexicalBlockFile(scope: !821, file: !1, discriminator: 1)
!821 = distinct !DILexicalBlock(scope: !822, file: !1, line: 788, column: 11)
!822 = distinct !DILexicalBlock(scope: !814, file: !1, line: 788, column: 11)
!823 = !DILocation(line: 788, column: 11, scope: !824)
!824 = !DILexicalBlockFile(scope: !821, file: !1, discriminator: 2)
!825 = !DILocation(line: 788, column: 11, scope: !826)
!826 = !DILexicalBlockFile(scope: !821, file: !1, discriminator: 3)
!827 = !DILocation(line: 788, column: 11, scope: !828)
!828 = !DILexicalBlockFile(scope: !822, file: !1, discriminator: 4)
!829 = !DILocation(line: 788, column: 11, scope: !830)
!830 = !DILexicalBlockFile(scope: !822, file: !1, discriminator: 5)
!831 = !DILocation(line: 790, column: 11, scope: !814)
!832 = !DILocation(line: 790, column: 11, scope: !833)
!833 = !DILexicalBlockFile(scope: !834, file: !1, discriminator: 1)
!834 = distinct !DILexicalBlock(scope: !835, file: !1, line: 790, column: 11)
!835 = distinct !DILexicalBlock(scope: !814, file: !1, line: 790, column: 11)
!836 = !DILocation(line: 790, column: 11, scope: !837)
!837 = !DILexicalBlockFile(scope: !834, file: !1, discriminator: 2)
!838 = !DILocation(line: 790, column: 11, scope: !839)
!839 = !DILexicalBlockFile(scope: !834, file: !1, discriminator: 3)
!840 = !DILocation(line: 790, column: 11, scope: !841)
!841 = !DILexicalBlockFile(scope: !835, file: !1, discriminator: 4)
!842 = !DILocation(line: 791, column: 7, scope: !802)
!843 = !DILocation(line: 793, column: 12, scope: !844)
!844 = distinct !DILexicalBlock(scope: !495, file: !1, line: 793, column: 10)
!845 = !DILocation(line: 793, column: 15, scope: !844)
!846 = !DILocation(line: 793, column: 21, scope: !844)
!847 = !DILocation(line: 793, column: 35, scope: !844)
!848 = !DILocation(line: 793, column: 39, scope: !849)
!849 = !DILexicalBlockFile(scope: !844, file: !1, discriminator: 1)
!850 = !DILocation(line: 793, column: 42, scope: !849)
!851 = !DILocation(line: 793, column: 48, scope: !849)
!852 = !DILocation(line: 793, column: 10, scope: !849)
!853 = !DILocation(line: 794, column: 9, scope: !844)
!854 = !DILocation(line: 794, column: 20, scope: !849)
!855 = !DILocation(line: 794, column: 23, scope: !849)
!856 = !DILocation(line: 794, column: 9, scope: !849)
!857 = !DILocation(line: 795, column: 11, scope: !844)
!858 = !DILocation(line: 795, column: 11, scope: !859)
!859 = !DILexicalBlockFile(scope: !860, file: !1, discriminator: 1)
!860 = distinct !DILexicalBlock(scope: !861, file: !1, line: 795, column: 11)
!861 = distinct !DILexicalBlock(scope: !844, file: !1, line: 795, column: 11)
!862 = !DILocation(line: 795, column: 11, scope: !863)
!863 = !DILexicalBlockFile(scope: !860, file: !1, discriminator: 2)
!864 = !DILocation(line: 795, column: 11, scope: !865)
!865 = !DILexicalBlockFile(scope: !860, file: !1, discriminator: 3)
!866 = !DILocation(line: 795, column: 11, scope: !867)
!867 = !DILexicalBlockFile(scope: !861, file: !1, discriminator: 4)
!868 = !DILocation(line: 794, column: 9, scope: !869)
!869 = !DILexicalBlockFile(scope: !844, file: !1, discriminator: 2)
!870 = !DILocation(line: 794, column: 9, scope: !871)
!871 = !DILexicalBlockFile(scope: !844, file: !1, discriminator: 3)
!872 = !DILocation(line: 798, column: 7, scope: !495)
!873 = !DILocation(line: 798, column: 13, scope: !635)
!874 = !DILocation(line: 798, column: 20, scope: !635)
!875 = !DILocation(line: 798, column: 17, scope: !635)
!876 = !DILocation(line: 798, column: 7, scope: !635)
!877 = !DILocation(line: 799, column: 9, scope: !878)
!878 = distinct !DILexicalBlock(scope: !495, file: !1, line: 798, column: 29)
!879 = !DILocation(line: 799, column: 9, scope: !880)
!880 = !DILexicalBlockFile(scope: !881, file: !1, discriminator: 1)
!881 = distinct !DILexicalBlock(scope: !882, file: !1, line: 799, column: 9)
!882 = distinct !DILexicalBlock(scope: !878, file: !1, line: 799, column: 9)
!883 = !DILocation(line: 799, column: 9, scope: !884)
!884 = !DILexicalBlockFile(scope: !881, file: !1, discriminator: 2)
!885 = !DILocation(line: 799, column: 9, scope: !886)
!886 = !DILexicalBlockFile(scope: !881, file: !1, discriminator: 3)
!887 = !DILocation(line: 799, column: 9, scope: !888)
!888 = !DILexicalBlockFile(scope: !882, file: !1, discriminator: 4)
!889 = !DILocation(line: 798, column: 7, scope: !648)
!890 = !DILocation(line: 802, column: 10, scope: !891)
!891 = distinct !DILexicalBlock(scope: !495, file: !1, line: 802, column: 10)
!892 = !DILocation(line: 802, column: 13, scope: !891)
!893 = !DILocation(line: 802, column: 19, scope: !891)
!894 = !DILocation(line: 802, column: 10, scope: !495)
!895 = !DILocation(line: 803, column: 9, scope: !891)
!896 = !DILocation(line: 803, column: 20, scope: !897)
!897 = !DILexicalBlockFile(scope: !891, file: !1, discriminator: 1)
!898 = !DILocation(line: 803, column: 23, scope: !897)
!899 = !DILocation(line: 803, column: 9, scope: !897)
!900 = !DILocation(line: 804, column: 11, scope: !891)
!901 = !DILocation(line: 804, column: 11, scope: !902)
!902 = !DILexicalBlockFile(scope: !903, file: !1, discriminator: 1)
!903 = distinct !DILexicalBlock(scope: !904, file: !1, line: 804, column: 11)
!904 = distinct !DILexicalBlock(scope: !891, file: !1, line: 804, column: 11)
!905 = !DILocation(line: 804, column: 11, scope: !906)
!906 = !DILexicalBlockFile(scope: !903, file: !1, discriminator: 2)
!907 = !DILocation(line: 804, column: 11, scope: !908)
!908 = !DILexicalBlockFile(scope: !903, file: !1, discriminator: 3)
!909 = !DILocation(line: 804, column: 11, scope: !910)
!910 = !DILexicalBlockFile(scope: !904, file: !1, discriminator: 4)
!911 = !DILocation(line: 803, column: 9, scope: !912)
!912 = !DILexicalBlockFile(scope: !891, file: !1, discriminator: 2)
!913 = !DILocation(line: 803, column: 9, scope: !914)
!914 = !DILexicalBlockFile(scope: !891, file: !1, discriminator: 3)
!915 = !DILocation(line: 805, column: 7, scope: !495)
!916 = !DILocalVariable(name: "str", scope: !917, file: !1, line: 811, type: !143)
!917 = distinct !DILexicalBlock(scope: !495, file: !1, line: 809, column: 7)
!918 = !DILocation(line: 811, column: 21, scope: !917)
!919 = !DILocalVariable(name: "len", scope: !917, file: !1, line: 812, type: !110)
!920 = !DILocation(line: 812, column: 16, scope: !917)
!921 = !DILocation(line: 814, column: 24, scope: !917)
!922 = !DILocation(line: 814, column: 27, scope: !917)
!923 = !DILocation(line: 814, column: 32, scope: !917)
!924 = !DILocation(line: 814, column: 13, scope: !917)
!925 = !DILocation(line: 815, column: 12, scope: !926)
!926 = distinct !DILexicalBlock(scope: !917, file: !1, line: 815, column: 12)
!927 = !DILocation(line: 815, column: 16, scope: !926)
!928 = !DILocation(line: 815, column: 12, scope: !917)
!929 = !DILocation(line: 817, column: 14, scope: !930)
!930 = distinct !DILexicalBlock(scope: !931, file: !1, line: 817, column: 14)
!931 = distinct !DILexicalBlock(scope: !926, file: !1, line: 815, column: 25)
!932 = !DILocation(line: 817, column: 19, scope: !930)
!933 = !DILocation(line: 817, column: 25, scope: !930)
!934 = !DILocation(line: 817, column: 28, scope: !935)
!935 = !DILexicalBlockFile(scope: !930, file: !1, discriminator: 1)
!936 = !DILocation(line: 817, column: 33, scope: !935)
!937 = !DILocation(line: 817, column: 14, scope: !935)
!938 = !DILocation(line: 818, column: 17, scope: !939)
!939 = distinct !DILexicalBlock(scope: !930, file: !1, line: 817, column: 61)
!940 = !DILocation(line: 819, column: 17, scope: !939)
!941 = !DILocation(line: 821, column: 13, scope: !939)
!942 = !DILocation(line: 821, column: 16, scope: !939)
!943 = !DILocation(line: 821, column: 22, scope: !939)
!944 = !DILocation(line: 822, column: 11, scope: !939)
!945 = !DILocation(line: 824, column: 17, scope: !946)
!946 = distinct !DILexicalBlock(scope: !930, file: !1, line: 823, column: 16)
!947 = !DILocation(line: 825, column: 17, scope: !946)
!948 = !DILocation(line: 827, column: 9, scope: !931)
!949 = !DILocation(line: 828, column: 17, scope: !950)
!950 = distinct !DILexicalBlock(scope: !926, file: !1, line: 828, column: 17)
!951 = !DILocation(line: 828, column: 22, scope: !950)
!952 = !DILocation(line: 828, column: 17, scope: !926)
!953 = !DILocation(line: 829, column: 25, scope: !950)
!954 = !DILocation(line: 829, column: 15, scope: !950)
!955 = !DILocation(line: 829, column: 11, scope: !950)
!956 = !DILocation(line: 831, column: 24, scope: !950)
!957 = !DILocation(line: 831, column: 17, scope: !950)
!958 = !DILocation(line: 831, column: 15, scope: !950)
!959 = !DILocation(line: 833, column: 19, scope: !917)
!960 = !DILocation(line: 833, column: 23, scope: !917)
!961 = !DILocation(line: 833, column: 18, scope: !917)
!962 = !DILocation(line: 833, column: 18, scope: !963)
!963 = !DILexicalBlockFile(scope: !917, file: !1, discriminator: 1)
!964 = !DILocation(line: 833, column: 54, scope: !965)
!965 = !DILexicalBlockFile(scope: !917, file: !1, discriminator: 2)
!966 = !DILocation(line: 833, column: 18, scope: !965)
!967 = !DILocation(line: 833, column: 18, scope: !968)
!968 = !DILexicalBlockFile(scope: !917, file: !1, discriminator: 3)
!969 = !DILocation(line: 833, column: 15, scope: !968)
!970 = !DILocation(line: 835, column: 12, scope: !971)
!971 = distinct !DILexicalBlock(scope: !917, file: !1, line: 835, column: 12)
!972 = !DILocation(line: 835, column: 15, scope: !971)
!973 = !DILocation(line: 835, column: 21, scope: !971)
!974 = !DILocation(line: 835, column: 12, scope: !917)
!975 = !DILocation(line: 836, column: 11, scope: !971)
!976 = !DILocation(line: 836, column: 11, scope: !977)
!977 = !DILexicalBlockFile(scope: !978, file: !1, discriminator: 1)
!978 = distinct !DILexicalBlock(scope: !979, file: !1, line: 836, column: 11)
!979 = distinct !DILexicalBlock(scope: !971, file: !1, line: 836, column: 11)
!980 = !DILocation(line: 836, column: 11, scope: !981)
!981 = !DILexicalBlockFile(scope: !978, file: !1, discriminator: 2)
!982 = !DILocation(line: 836, column: 11, scope: !983)
!983 = !DILexicalBlockFile(scope: !978, file: !1, discriminator: 3)
!984 = !DILocation(line: 836, column: 11, scope: !985)
!985 = !DILexicalBlockFile(scope: !979, file: !1, discriminator: 4)
!986 = !DILocation(line: 836, column: 11, scope: !987)
!987 = !DILexicalBlockFile(scope: !979, file: !1, discriminator: 5)
!988 = !DILocation(line: 838, column: 14, scope: !989)
!989 = distinct !DILexicalBlock(scope: !917, file: !1, line: 838, column: 12)
!990 = !DILocation(line: 838, column: 17, scope: !989)
!991 = !DILocation(line: 838, column: 22, scope: !989)
!992 = !DILocation(line: 838, column: 12, scope: !917)
!993 = !DILocation(line: 839, column: 11, scope: !989)
!994 = !DILocation(line: 839, column: 22, scope: !995)
!995 = !DILexicalBlockFile(scope: !989, file: !1, discriminator: 1)
!996 = !DILocation(line: 839, column: 25, scope: !995)
!997 = !DILocation(line: 839, column: 11, scope: !995)
!998 = !DILocation(line: 840, column: 13, scope: !989)
!999 = !DILocation(line: 840, column: 13, scope: !1000)
!1000 = !DILexicalBlockFile(scope: !1001, file: !1, discriminator: 1)
!1001 = distinct !DILexicalBlock(scope: !1002, file: !1, line: 840, column: 13)
!1002 = distinct !DILexicalBlock(scope: !989, file: !1, line: 840, column: 13)
!1003 = !DILocation(line: 840, column: 13, scope: !1004)
!1004 = !DILexicalBlockFile(scope: !1001, file: !1, discriminator: 2)
!1005 = !DILocation(line: 840, column: 13, scope: !1006)
!1006 = !DILexicalBlockFile(scope: !1001, file: !1, discriminator: 3)
!1007 = !DILocation(line: 840, column: 13, scope: !1008)
!1008 = !DILexicalBlockFile(scope: !1002, file: !1, discriminator: 4)
!1009 = !DILocation(line: 839, column: 11, scope: !1010)
!1010 = !DILexicalBlockFile(scope: !989, file: !1, discriminator: 2)
!1011 = !DILocation(line: 839, column: 11, scope: !1012)
!1012 = !DILexicalBlockFile(scope: !989, file: !1, discriminator: 3)
!1013 = !DILocation(line: 842, column: 9, scope: !917)
!1014 = !DILocation(line: 842, column: 19, scope: !963)
!1015 = !DILocation(line: 842, column: 22, scope: !963)
!1016 = !DILocation(line: 842, column: 27, scope: !963)
!1017 = !DILocation(line: 842, column: 31, scope: !965)
!1018 = !DILocation(line: 842, column: 30, scope: !965)
!1019 = !DILocation(line: 842, column: 27, scope: !965)
!1020 = !DILocation(line: 842, column: 9, scope: !968)
!1021 = !DILocation(line: 843, column: 11, scope: !917)
!1022 = !DILocation(line: 843, column: 11, scope: !1023)
!1023 = !DILexicalBlockFile(scope: !1024, file: !1, discriminator: 1)
!1024 = distinct !DILexicalBlock(scope: !1025, file: !1, line: 843, column: 11)
!1025 = distinct !DILexicalBlock(scope: !917, file: !1, line: 843, column: 11)
!1026 = !DILocation(line: 843, column: 11, scope: !1027)
!1027 = !DILexicalBlockFile(scope: !1024, file: !1, discriminator: 2)
!1028 = !DILocation(line: 843, column: 11, scope: !1029)
!1029 = !DILexicalBlockFile(scope: !1024, file: !1, discriminator: 3)
!1030 = !DILocation(line: 843, column: 11, scope: !1031)
!1031 = !DILexicalBlockFile(scope: !1025, file: !1, discriminator: 4)
!1032 = !DILocation(line: 842, column: 9, scope: !1033)
!1033 = !DILexicalBlockFile(scope: !917, file: !1, discriminator: 4)
!1034 = !DILocation(line: 844, column: 12, scope: !1035)
!1035 = distinct !DILexicalBlock(scope: !917, file: !1, line: 844, column: 12)
!1036 = !DILocation(line: 844, column: 15, scope: !1035)
!1037 = !DILocation(line: 844, column: 20, scope: !1035)
!1038 = !DILocation(line: 844, column: 12, scope: !917)
!1039 = !DILocation(line: 845, column: 11, scope: !1035)
!1040 = !DILocation(line: 845, column: 22, scope: !1041)
!1041 = !DILexicalBlockFile(scope: !1035, file: !1, discriminator: 1)
!1042 = !DILocation(line: 845, column: 25, scope: !1041)
!1043 = !DILocation(line: 845, column: 11, scope: !1041)
!1044 = !DILocation(line: 846, column: 13, scope: !1035)
!1045 = !DILocation(line: 846, column: 13, scope: !1046)
!1046 = !DILexicalBlockFile(scope: !1047, file: !1, discriminator: 1)
!1047 = distinct !DILexicalBlock(scope: !1048, file: !1, line: 846, column: 13)
!1048 = distinct !DILexicalBlock(scope: !1035, file: !1, line: 846, column: 13)
!1049 = !DILocation(line: 846, column: 13, scope: !1050)
!1050 = !DILexicalBlockFile(scope: !1047, file: !1, discriminator: 2)
!1051 = !DILocation(line: 846, column: 13, scope: !1052)
!1052 = !DILexicalBlockFile(scope: !1047, file: !1, discriminator: 3)
!1053 = !DILocation(line: 846, column: 13, scope: !1054)
!1054 = !DILexicalBlockFile(scope: !1048, file: !1, discriminator: 4)
!1055 = !DILocation(line: 845, column: 11, scope: !1056)
!1056 = !DILexicalBlockFile(scope: !1035, file: !1, discriminator: 2)
!1057 = !DILocation(line: 845, column: 11, scope: !1058)
!1058 = !DILexicalBlockFile(scope: !1035, file: !1, discriminator: 3)
!1059 = !DILocation(line: 848, column: 12, scope: !1060)
!1060 = distinct !DILexicalBlock(scope: !917, file: !1, line: 848, column: 12)
!1061 = !DILocation(line: 848, column: 15, scope: !1060)
!1062 = !DILocation(line: 848, column: 21, scope: !1060)
!1063 = !DILocation(line: 848, column: 12, scope: !917)
!1064 = !DILocation(line: 849, column: 11, scope: !1060)
!1065 = !DILocation(line: 849, column: 11, scope: !1066)
!1066 = !DILexicalBlockFile(scope: !1067, file: !1, discriminator: 1)
!1067 = distinct !DILexicalBlock(scope: !1068, file: !1, line: 849, column: 11)
!1068 = distinct !DILexicalBlock(scope: !1060, file: !1, line: 849, column: 11)
!1069 = !DILocation(line: 849, column: 11, scope: !1070)
!1070 = !DILexicalBlockFile(scope: !1067, file: !1, discriminator: 2)
!1071 = !DILocation(line: 849, column: 11, scope: !1072)
!1072 = !DILexicalBlockFile(scope: !1067, file: !1, discriminator: 3)
!1073 = !DILocation(line: 849, column: 11, scope: !1074)
!1074 = !DILexicalBlockFile(scope: !1068, file: !1, discriminator: 4)
!1075 = !DILocation(line: 849, column: 11, scope: !1076)
!1076 = !DILexicalBlockFile(scope: !1068, file: !1, discriminator: 5)
!1077 = !DILocation(line: 851, column: 7, scope: !495)
!1078 = !DILocalVariable(name: "ptr", scope: !1079, file: !1, line: 856, type: !105)
!1079 = distinct !DILexicalBlock(scope: !495, file: !1, line: 855, column: 7)
!1080 = !DILocation(line: 856, column: 15, scope: !1079)
!1081 = !DILocation(line: 857, column: 24, scope: !1079)
!1082 = !DILocation(line: 857, column: 27, scope: !1079)
!1083 = !DILocation(line: 857, column: 32, scope: !1079)
!1084 = !DILocation(line: 857, column: 13, scope: !1079)
!1085 = !DILocation(line: 858, column: 12, scope: !1086)
!1086 = distinct !DILexicalBlock(scope: !1079, file: !1, line: 858, column: 12)
!1087 = !DILocation(line: 858, column: 16, scope: !1086)
!1088 = !DILocation(line: 858, column: 12, scope: !1079)
!1089 = !DILocation(line: 860, column: 16, scope: !1090)
!1090 = distinct !DILexicalBlock(scope: !1086, file: !1, line: 858, column: 25)
!1091 = !DILocation(line: 861, column: 21, scope: !1090)
!1092 = !DILocation(line: 861, column: 24, scope: !1090)
!1093 = !DILocation(line: 861, column: 30, scope: !1090)
!1094 = !DILocation(line: 861, column: 20, scope: !1090)
!1095 = !DILocation(line: 861, column: 18, scope: !1090)
!1096 = !DILocation(line: 862, column: 18, scope: !1090)
!1097 = !DILocation(line: 863, column: 26, scope: !1090)
!1098 = !DILocation(line: 863, column: 17, scope: !1090)
!1099 = !DILocation(line: 863, column: 15, scope: !1090)
!1100 = !DILocation(line: 864, column: 18, scope: !1090)
!1101 = !DILocation(line: 865, column: 11, scope: !1090)
!1102 = !DILocalVariable(name: "point", scope: !1103, file: !1, line: 870, type: !143)
!1103 = distinct !DILexicalBlock(scope: !1086, file: !1, line: 867, column: 14)
!1104 = !DILocation(line: 870, column: 23, scope: !1103)
!1105 = !DILocation(line: 872, column: 17, scope: !1103)
!1106 = !DILocation(line: 873, column: 14, scope: !1107)
!1107 = distinct !DILexicalBlock(scope: !1103, file: !1, line: 873, column: 14)
!1108 = !DILocation(line: 873, column: 17, scope: !1107)
!1109 = !DILocation(line: 873, column: 23, scope: !1107)
!1110 = !DILocation(line: 873, column: 14, scope: !1103)
!1111 = !DILocation(line: 874, column: 13, scope: !1107)
!1112 = !DILocation(line: 874, column: 24, scope: !1113)
!1113 = !DILexicalBlockFile(scope: !1107, file: !1, discriminator: 1)
!1114 = !DILocation(line: 874, column: 27, scope: !1113)
!1115 = !DILocation(line: 874, column: 13, scope: !1113)
!1116 = !DILocation(line: 875, column: 15, scope: !1107)
!1117 = !DILocation(line: 875, column: 15, scope: !1118)
!1118 = !DILexicalBlockFile(scope: !1119, file: !1, discriminator: 1)
!1119 = distinct !DILexicalBlock(scope: !1120, file: !1, line: 875, column: 15)
!1120 = distinct !DILexicalBlock(scope: !1107, file: !1, line: 875, column: 15)
!1121 = !DILocation(line: 875, column: 15, scope: !1122)
!1122 = !DILexicalBlockFile(scope: !1119, file: !1, discriminator: 2)
!1123 = !DILocation(line: 875, column: 15, scope: !1124)
!1124 = !DILexicalBlockFile(scope: !1119, file: !1, discriminator: 3)
!1125 = !DILocation(line: 875, column: 15, scope: !1126)
!1126 = !DILexicalBlockFile(scope: !1120, file: !1, discriminator: 4)
!1127 = !DILocation(line: 874, column: 13, scope: !1128)
!1128 = !DILexicalBlockFile(scope: !1107, file: !1, discriminator: 2)
!1129 = !DILocation(line: 874, column: 13, scope: !1130)
!1130 = !DILexicalBlockFile(scope: !1107, file: !1, discriminator: 3)
!1131 = !DILocation(line: 876, column: 21, scope: !1132)
!1132 = distinct !DILexicalBlock(scope: !1103, file: !1, line: 876, column: 11)
!1133 = !DILocation(line: 876, column: 15, scope: !1132)
!1134 = !DILocation(line: 876, column: 32, scope: !1135)
!1135 = !DILexicalBlockFile(scope: !1136, file: !1, discriminator: 1)
!1136 = distinct !DILexicalBlock(scope: !1132, file: !1, line: 876, column: 11)
!1137 = !DILocation(line: 876, column: 31, scope: !1135)
!1138 = !DILocation(line: 876, column: 38, scope: !1135)
!1139 = !DILocation(line: 876, column: 11, scope: !1135)
!1140 = !DILocation(line: 877, column: 13, scope: !1136)
!1141 = !DILocation(line: 877, column: 13, scope: !1142)
!1142 = !DILexicalBlockFile(scope: !1143, file: !1, discriminator: 1)
!1143 = distinct !DILexicalBlock(scope: !1144, file: !1, line: 877, column: 13)
!1144 = distinct !DILexicalBlock(scope: !1136, file: !1, line: 877, column: 13)
!1145 = !DILocation(line: 877, column: 13, scope: !1146)
!1146 = !DILexicalBlockFile(scope: !1143, file: !1, discriminator: 2)
!1147 = !DILocation(line: 877, column: 13, scope: !1148)
!1148 = !DILexicalBlockFile(scope: !1143, file: !1, discriminator: 3)
!1149 = !DILocation(line: 877, column: 13, scope: !1150)
!1150 = !DILexicalBlockFile(scope: !1144, file: !1, discriminator: 4)
!1151 = !DILocation(line: 877, column: 13, scope: !1152)
!1152 = !DILexicalBlockFile(scope: !1144, file: !1, discriminator: 5)
!1153 = !DILocation(line: 876, column: 47, scope: !1154)
!1154 = !DILexicalBlockFile(scope: !1136, file: !1, discriminator: 2)
!1155 = !DILocation(line: 876, column: 11, scope: !1154)
!1156 = !DILocation(line: 878, column: 17, scope: !1157)
!1157 = distinct !DILexicalBlock(scope: !1103, file: !1, line: 878, column: 14)
!1158 = !DILocation(line: 878, column: 20, scope: !1157)
!1159 = !DILocation(line: 878, column: 26, scope: !1157)
!1160 = !DILocation(line: 878, column: 14, scope: !1103)
!1161 = !DILocation(line: 879, column: 13, scope: !1157)
!1162 = !DILocation(line: 879, column: 24, scope: !1163)
!1163 = !DILexicalBlockFile(scope: !1157, file: !1, discriminator: 1)
!1164 = !DILocation(line: 879, column: 27, scope: !1163)
!1165 = !DILocation(line: 879, column: 13, scope: !1163)
!1166 = !DILocation(line: 880, column: 15, scope: !1157)
!1167 = !DILocation(line: 880, column: 15, scope: !1168)
!1168 = !DILexicalBlockFile(scope: !1169, file: !1, discriminator: 1)
!1169 = distinct !DILexicalBlock(scope: !1170, file: !1, line: 880, column: 15)
!1170 = distinct !DILexicalBlock(scope: !1157, file: !1, line: 880, column: 15)
!1171 = !DILocation(line: 880, column: 15, scope: !1172)
!1172 = !DILexicalBlockFile(scope: !1169, file: !1, discriminator: 2)
!1173 = !DILocation(line: 880, column: 15, scope: !1174)
!1174 = !DILexicalBlockFile(scope: !1169, file: !1, discriminator: 3)
!1175 = !DILocation(line: 880, column: 15, scope: !1176)
!1176 = !DILexicalBlockFile(scope: !1170, file: !1, discriminator: 4)
!1177 = !DILocation(line: 879, column: 13, scope: !1178)
!1178 = !DILexicalBlockFile(scope: !1157, file: !1, discriminator: 2)
!1179 = !DILocation(line: 879, column: 13, scope: !1180)
!1180 = !DILexicalBlockFile(scope: !1157, file: !1, discriminator: 3)
!1181 = !DILocation(line: 883, column: 7, scope: !495)
!1182 = !DILocalVariable(name: "formatbuf", scope: !1183, file: !1, line: 887, type: !1184)
!1183 = distinct !DILexicalBlock(scope: !495, file: !1, line: 886, column: 7)
!1184 = !DICompositeType(tag: DW_TAG_array_type, baseType: !55, size: 256, align: 8, elements: !1185)
!1185 = !{!1186}
!1186 = !DISubrange(count: 32)
!1187 = !DILocation(line: 887, column: 14, scope: !1183)
!1188 = !DILocalVariable(name: "fptr", scope: !1183, file: !1, line: 888, type: !54)
!1189 = !DILocation(line: 888, column: 15, scope: !1183)
!1190 = !DILocation(line: 888, column: 23, scope: !1183)
!1191 = !DILocalVariable(name: "left", scope: !1183, file: !1, line: 889, type: !110)
!1192 = !DILocation(line: 889, column: 16, scope: !1183)
!1193 = !DILocation(line: 889, column: 48, scope: !1183)
!1194 = !DILocation(line: 889, column: 41, scope: !1183)
!1195 = !DILocation(line: 889, column: 40, scope: !1183)
!1196 = !DILocalVariable(name: "len", scope: !1183, file: !1, line: 890, type: !64)
!1197 = !DILocation(line: 890, column: 13, scope: !1183)
!1198 = !DILocation(line: 892, column: 15, scope: !1183)
!1199 = !DILocation(line: 893, column: 12, scope: !1200)
!1200 = distinct !DILexicalBlock(scope: !1183, file: !1, line: 893, column: 12)
!1201 = !DILocation(line: 893, column: 15, scope: !1200)
!1202 = !DILocation(line: 893, column: 21, scope: !1200)
!1203 = !DILocation(line: 893, column: 12, scope: !1183)
!1204 = !DILocation(line: 894, column: 19, scope: !1200)
!1205 = !DILocation(line: 894, column: 22, scope: !1200)
!1206 = !DILocation(line: 894, column: 17, scope: !1200)
!1207 = !DILocation(line: 894, column: 11, scope: !1200)
!1208 = !DILocation(line: 895, column: 17, scope: !1209)
!1209 = distinct !DILexicalBlock(scope: !1200, file: !1, line: 895, column: 17)
!1210 = !DILocation(line: 895, column: 20, scope: !1209)
!1211 = !DILocation(line: 895, column: 26, scope: !1209)
!1212 = !DILocation(line: 895, column: 17, scope: !1200)
!1213 = !DILocation(line: 896, column: 29, scope: !1209)
!1214 = !DILocation(line: 896, column: 32, scope: !1209)
!1215 = !DILocation(line: 896, column: 25, scope: !1209)
!1216 = !DILocation(line: 896, column: 39, scope: !1209)
!1217 = !DILocation(line: 896, column: 44, scope: !1209)
!1218 = !DILocation(line: 896, column: 48, scope: !1209)
!1219 = !DILocation(line: 896, column: 17, scope: !1209)
!1220 = !DILocation(line: 896, column: 11, scope: !1209)
!1221 = !DILocation(line: 898, column: 14, scope: !1183)
!1222 = !DILocation(line: 899, column: 12, scope: !1223)
!1223 = distinct !DILexicalBlock(scope: !1183, file: !1, line: 899, column: 12)
!1224 = !DILocation(line: 899, column: 15, scope: !1223)
!1225 = !DILocation(line: 899, column: 21, scope: !1223)
!1226 = !DILocation(line: 899, column: 12, scope: !1183)
!1227 = !DILocation(line: 900, column: 18, scope: !1223)
!1228 = !DILocation(line: 900, column: 21, scope: !1223)
!1229 = !DILocation(line: 900, column: 16, scope: !1223)
!1230 = !DILocation(line: 900, column: 11, scope: !1223)
!1231 = !DILocation(line: 901, column: 17, scope: !1232)
!1232 = distinct !DILexicalBlock(scope: !1223, file: !1, line: 901, column: 17)
!1233 = !DILocation(line: 901, column: 20, scope: !1232)
!1234 = !DILocation(line: 901, column: 26, scope: !1232)
!1235 = !DILocation(line: 901, column: 17, scope: !1223)
!1236 = !DILocation(line: 902, column: 28, scope: !1232)
!1237 = !DILocation(line: 902, column: 31, scope: !1232)
!1238 = !DILocation(line: 902, column: 24, scope: !1232)
!1239 = !DILocation(line: 902, column: 42, scope: !1232)
!1240 = !DILocation(line: 902, column: 47, scope: !1232)
!1241 = !DILocation(line: 902, column: 51, scope: !1232)
!1242 = !DILocation(line: 902, column: 16, scope: !1232)
!1243 = !DILocation(line: 902, column: 11, scope: !1232)
!1244 = !DILocation(line: 904, column: 12, scope: !1245)
!1245 = distinct !DILexicalBlock(scope: !1183, file: !1, line: 904, column: 12)
!1246 = !DILocation(line: 904, column: 15, scope: !1245)
!1247 = !DILocation(line: 904, column: 21, scope: !1245)
!1248 = !DILocation(line: 904, column: 12, scope: !1183)
!1249 = !DILocation(line: 905, column: 16, scope: !1245)
!1250 = !DILocation(line: 905, column: 19, scope: !1245)
!1251 = !DILocation(line: 905, column: 11, scope: !1245)
!1252 = !DILocation(line: 906, column: 12, scope: !1253)
!1253 = distinct !DILexicalBlock(scope: !1183, file: !1, line: 906, column: 12)
!1254 = !DILocation(line: 906, column: 15, scope: !1253)
!1255 = !DILocation(line: 906, column: 21, scope: !1253)
!1256 = !DILocation(line: 906, column: 12, scope: !1183)
!1257 = !DILocation(line: 907, column: 16, scope: !1253)
!1258 = !DILocation(line: 907, column: 19, scope: !1253)
!1259 = !DILocation(line: 907, column: 11, scope: !1253)
!1260 = !DILocation(line: 908, column: 12, scope: !1261)
!1261 = distinct !DILexicalBlock(scope: !1183, file: !1, line: 908, column: 12)
!1262 = !DILocation(line: 908, column: 15, scope: !1261)
!1263 = !DILocation(line: 908, column: 21, scope: !1261)
!1264 = !DILocation(line: 908, column: 12, scope: !1183)
!1265 = !DILocation(line: 909, column: 16, scope: !1261)
!1266 = !DILocation(line: 909, column: 19, scope: !1261)
!1267 = !DILocation(line: 909, column: 11, scope: !1261)
!1268 = !DILocation(line: 910, column: 12, scope: !1269)
!1269 = distinct !DILexicalBlock(scope: !1183, file: !1, line: 910, column: 12)
!1270 = !DILocation(line: 910, column: 15, scope: !1269)
!1271 = !DILocation(line: 910, column: 21, scope: !1269)
!1272 = !DILocation(line: 910, column: 12, scope: !1183)
!1273 = !DILocation(line: 911, column: 16, scope: !1269)
!1274 = !DILocation(line: 911, column: 19, scope: !1269)
!1275 = !DILocation(line: 911, column: 11, scope: !1269)
!1276 = !DILocation(line: 913, column: 10, scope: !1183)
!1277 = !DILocation(line: 913, column: 15, scope: !1183)
!1278 = !DILocation(line: 915, column: 12, scope: !1279)
!1279 = distinct !DILexicalBlock(scope: !1183, file: !1, line: 915, column: 12)
!1280 = !DILocation(line: 915, column: 18, scope: !1279)
!1281 = !DILocation(line: 915, column: 12, scope: !1183)
!1282 = !DILocation(line: 916, column: 14, scope: !1283)
!1283 = distinct !DILexicalBlock(scope: !1284, file: !1, line: 916, column: 14)
!1284 = distinct !DILexicalBlock(scope: !1279, file: !1, line: 915, column: 24)
!1285 = !DILocation(line: 916, column: 20, scope: !1283)
!1286 = !DILocation(line: 916, column: 14, scope: !1284)
!1287 = !DILocation(line: 917, column: 19, scope: !1283)
!1288 = !DILocation(line: 917, column: 13, scope: !1283)
!1289 = !DILocation(line: 919, column: 32, scope: !1284)
!1290 = !DILocation(line: 919, column: 38, scope: !1284)
!1291 = !DILocation(line: 919, column: 51, scope: !1284)
!1292 = !DILocation(line: 919, column: 17, scope: !1284)
!1293 = !DILocation(line: 919, column: 15, scope: !1284)
!1294 = !DILocation(line: 920, column: 19, scope: !1284)
!1295 = !DILocation(line: 920, column: 16, scope: !1284)
!1296 = !DILocation(line: 921, column: 19, scope: !1284)
!1297 = !DILocation(line: 921, column: 16, scope: !1284)
!1298 = !DILocation(line: 922, column: 9, scope: !1284)
!1299 = !DILocation(line: 923, column: 12, scope: !1300)
!1300 = distinct !DILexicalBlock(scope: !1183, file: !1, line: 923, column: 12)
!1301 = !DILocation(line: 923, column: 17, scope: !1300)
!1302 = !DILocation(line: 923, column: 12, scope: !1183)
!1303 = !DILocalVariable(name: "maxprec", scope: !1304, file: !1, line: 926, type: !110)
!1304 = distinct !DILexicalBlock(scope: !1300, file: !1, line: 923, column: 23)
!1305 = !DILocation(line: 926, column: 18, scope: !1304)
!1306 = !DILocalVariable(name: "val", scope: !1304, file: !1, line: 927, type: !210)
!1307 = !DILocation(line: 927, column: 18, scope: !1304)
!1308 = !DILocation(line: 927, column: 24, scope: !1304)
!1309 = !DILocation(line: 927, column: 27, scope: !1304)
!1310 = !DILocation(line: 927, column: 32, scope: !1304)
!1311 = !DILocation(line: 928, column: 11, scope: !1304)
!1312 = !DILocation(line: 928, column: 17, scope: !1313)
!1313 = !DILexicalBlockFile(scope: !1304, file: !1, discriminator: 1)
!1314 = !DILocation(line: 928, column: 21, scope: !1313)
!1315 = !DILocation(line: 928, column: 11, scope: !1313)
!1316 = !DILocation(line: 929, column: 17, scope: !1317)
!1317 = distinct !DILexicalBlock(scope: !1304, file: !1, line: 928, column: 30)
!1318 = !DILocation(line: 930, column: 20, scope: !1317)
!1319 = !DILocation(line: 928, column: 11, scope: !1320)
!1320 = !DILexicalBlockFile(scope: !1304, file: !1, discriminator: 2)
!1321 = !DILocation(line: 933, column: 14, scope: !1322)
!1322 = distinct !DILexicalBlock(scope: !1304, file: !1, line: 933, column: 14)
!1323 = !DILocation(line: 933, column: 27, scope: !1322)
!1324 = !DILocation(line: 933, column: 19, scope: !1322)
!1325 = !DILocation(line: 933, column: 14, scope: !1304)
!1326 = !DILocation(line: 934, column: 26, scope: !1322)
!1327 = !DILocation(line: 934, column: 33, scope: !1322)
!1328 = !DILocation(line: 934, column: 18, scope: !1322)
!1329 = !DILocation(line: 934, column: 13, scope: !1322)
!1330 = !DILocation(line: 936, column: 32, scope: !1304)
!1331 = !DILocation(line: 936, column: 38, scope: !1304)
!1332 = !DILocation(line: 936, column: 52, scope: !1304)
!1333 = !DILocation(line: 936, column: 17, scope: !1304)
!1334 = !DILocation(line: 936, column: 15, scope: !1304)
!1335 = !DILocation(line: 937, column: 19, scope: !1304)
!1336 = !DILocation(line: 937, column: 16, scope: !1304)
!1337 = !DILocation(line: 938, column: 9, scope: !1304)
!1338 = !DILocation(line: 939, column: 12, scope: !1339)
!1339 = distinct !DILexicalBlock(scope: !1183, file: !1, line: 939, column: 12)
!1340 = !DILocation(line: 939, column: 15, scope: !1339)
!1341 = !DILocation(line: 939, column: 21, scope: !1339)
!1342 = !DILocation(line: 939, column: 12, scope: !1183)
!1343 = !DILocation(line: 940, column: 16, scope: !1339)
!1344 = !DILocation(line: 940, column: 19, scope: !1339)
!1345 = !DILocation(line: 940, column: 11, scope: !1339)
!1346 = !DILocation(line: 942, column: 12, scope: !1347)
!1347 = distinct !DILexicalBlock(scope: !1183, file: !1, line: 942, column: 12)
!1348 = !DILocation(line: 942, column: 15, scope: !1347)
!1349 = !DILocation(line: 942, column: 21, scope: !1347)
!1350 = !DILocation(line: 942, column: 12, scope: !1183)
!1351 = !DILocation(line: 943, column: 29, scope: !1347)
!1352 = !DILocation(line: 943, column: 32, scope: !1347)
!1353 = !DILocation(line: 943, column: 38, scope: !1347)
!1354 = !DILocation(line: 943, column: 28, scope: !1347)
!1355 = !DILocation(line: 943, column: 21, scope: !1347)
!1356 = !DILocation(line: 943, column: 16, scope: !1347)
!1357 = !DILocation(line: 943, column: 19, scope: !1347)
!1358 = !DILocation(line: 943, column: 11, scope: !1347)
!1359 = !DILocation(line: 944, column: 17, scope: !1360)
!1360 = distinct !DILexicalBlock(scope: !1347, file: !1, line: 944, column: 17)
!1361 = !DILocation(line: 944, column: 20, scope: !1360)
!1362 = !DILocation(line: 944, column: 26, scope: !1360)
!1363 = !DILocation(line: 944, column: 17, scope: !1347)
!1364 = !DILocation(line: 945, column: 29, scope: !1360)
!1365 = !DILocation(line: 945, column: 32, scope: !1360)
!1366 = !DILocation(line: 945, column: 38, scope: !1360)
!1367 = !DILocation(line: 945, column: 28, scope: !1360)
!1368 = !DILocation(line: 945, column: 21, scope: !1360)
!1369 = !DILocation(line: 945, column: 16, scope: !1360)
!1370 = !DILocation(line: 945, column: 19, scope: !1360)
!1371 = !DILocation(line: 945, column: 11, scope: !1360)
!1372 = !DILocation(line: 947, column: 16, scope: !1360)
!1373 = !DILocation(line: 947, column: 19, scope: !1360)
!1374 = !DILocation(line: 949, column: 10, scope: !1183)
!1375 = !DILocation(line: 949, column: 15, scope: !1183)
!1376 = !DILocation(line: 953, column: 19, scope: !1183)
!1377 = !DILocation(line: 953, column: 25, scope: !1183)
!1378 = !DILocation(line: 953, column: 36, scope: !1183)
!1379 = !DILocation(line: 953, column: 39, scope: !1183)
!1380 = !DILocation(line: 953, column: 44, scope: !1183)
!1381 = !DILocation(line: 953, column: 9, scope: !1183)
!1382 = !DILocation(line: 957, column: 18, scope: !1383)
!1383 = distinct !DILexicalBlock(scope: !1183, file: !1, line: 957, column: 9)
!1384 = !DILocation(line: 957, column: 17, scope: !1383)
!1385 = !DILocation(line: 957, column: 13, scope: !1383)
!1386 = !DILocation(line: 957, column: 25, scope: !1387)
!1387 = !DILexicalBlockFile(scope: !1388, file: !1, discriminator: 1)
!1388 = distinct !DILexicalBlock(scope: !1383, file: !1, line: 957, column: 9)
!1389 = !DILocation(line: 957, column: 24, scope: !1387)
!1390 = !DILocation(line: 957, column: 9, scope: !1387)
!1391 = !DILocation(line: 958, column: 11, scope: !1388)
!1392 = !DILocation(line: 958, column: 11, scope: !1393)
!1393 = !DILexicalBlockFile(scope: !1394, file: !1, discriminator: 1)
!1394 = distinct !DILexicalBlock(scope: !1395, file: !1, line: 958, column: 11)
!1395 = distinct !DILexicalBlock(scope: !1388, file: !1, line: 958, column: 11)
!1396 = !DILocation(line: 958, column: 11, scope: !1397)
!1397 = !DILexicalBlockFile(scope: !1394, file: !1, discriminator: 2)
!1398 = !DILocation(line: 958, column: 11, scope: !1399)
!1399 = !DILexicalBlockFile(scope: !1394, file: !1, discriminator: 3)
!1400 = !DILocation(line: 958, column: 11, scope: !1401)
!1401 = !DILexicalBlockFile(scope: !1395, file: !1, discriminator: 4)
!1402 = !DILocation(line: 958, column: 11, scope: !1403)
!1403 = !DILexicalBlockFile(scope: !1395, file: !1, discriminator: 5)
!1404 = !DILocation(line: 957, column: 35, scope: !1405)
!1405 = !DILexicalBlockFile(scope: !1388, file: !1, discriminator: 2)
!1406 = !DILocation(line: 957, column: 9, scope: !1405)
!1407 = !DILocation(line: 960, column: 7, scope: !495)
!1408 = !DILocation(line: 965, column: 10, scope: !1409)
!1409 = distinct !DILexicalBlock(scope: !495, file: !1, line: 965, column: 10)
!1410 = !DILocation(line: 965, column: 13, scope: !1409)
!1411 = !DILocation(line: 965, column: 19, scope: !1409)
!1412 = !DILocation(line: 965, column: 10, scope: !495)
!1413 = !DILocation(line: 966, column: 59, scope: !1409)
!1414 = !DILocation(line: 966, column: 43, scope: !1409)
!1415 = !DILocation(line: 966, column: 29, scope: !1409)
!1416 = !DILocation(line: 966, column: 32, scope: !1409)
!1417 = !DILocation(line: 966, column: 37, scope: !1409)
!1418 = !DILocation(line: 966, column: 10, scope: !1409)
!1419 = !DILocation(line: 966, column: 41, scope: !1409)
!1420 = !DILocation(line: 966, column: 9, scope: !1409)
!1421 = !DILocation(line: 969, column: 12, scope: !1422)
!1422 = distinct !DILexicalBlock(scope: !1409, file: !1, line: 969, column: 12)
!1423 = !DILocation(line: 969, column: 15, scope: !1422)
!1424 = !DILocation(line: 969, column: 21, scope: !1422)
!1425 = !DILocation(line: 969, column: 12, scope: !1409)
!1426 = !DILocation(line: 970, column: 41, scope: !1422)
!1427 = !DILocation(line: 970, column: 35, scope: !1422)
!1428 = !DILocation(line: 970, column: 21, scope: !1422)
!1429 = !DILocation(line: 970, column: 24, scope: !1422)
!1430 = !DILocation(line: 970, column: 29, scope: !1422)
!1431 = !DILocation(line: 970, column: 12, scope: !1422)
!1432 = !DILocation(line: 970, column: 33, scope: !1422)
!1433 = !DILocation(line: 970, column: 11, scope: !1422)
!1434 = !DILocation(line: 971, column: 17, scope: !1435)
!1435 = distinct !DILexicalBlock(scope: !1422, file: !1, line: 971, column: 15)
!1436 = !DILocation(line: 971, column: 20, scope: !1435)
!1437 = !DILocation(line: 971, column: 26, scope: !1435)
!1438 = !DILocation(line: 971, column: 15, scope: !1422)
!1439 = !DILocation(line: 972, column: 37, scope: !1435)
!1440 = !DILocation(line: 972, column: 18, scope: !1435)
!1441 = !DILocation(line: 972, column: 21, scope: !1435)
!1442 = !DILocation(line: 972, column: 26, scope: !1435)
!1443 = !DILocation(line: 972, column: 10, scope: !1435)
!1444 = !DILocation(line: 972, column: 30, scope: !1435)
!1445 = !DILocation(line: 972, column: 9, scope: !1435)
!1446 = !DILocation(line: 974, column: 41, scope: !1435)
!1447 = !DILocation(line: 974, column: 34, scope: !1435)
!1448 = !DILocation(line: 974, column: 20, scope: !1435)
!1449 = !DILocation(line: 974, column: 23, scope: !1435)
!1450 = !DILocation(line: 974, column: 28, scope: !1435)
!1451 = !DILocation(line: 974, column: 10, scope: !1435)
!1452 = !DILocation(line: 974, column: 32, scope: !1435)
!1453 = !DILocation(line: 975, column: 7, scope: !495)
!1454 = !DILocation(line: 978, column: 7, scope: !495)
!1455 = !DILocation(line: 980, column: 13, scope: !341)
!1456 = !DILocation(line: 980, column: 9, scope: !341)
!1457 = !DILocation(line: 980, column: 7, scope: !341)
!1458 = !DILocation(line: 599, column: 3, scope: !1459)
!1459 = !DILexicalBlockFile(scope: !181, file: !1, discriminator: 2)
!1460 = !DILocation(line: 983, column: 10, scope: !181)
!1461 = !DILocation(line: 983, column: 3, scope: !181)
!1462 = !DILocation(line: 984, column: 1, scope: !181)
!1463 = !DILocalVariable(name: "output", arg: 1, scope: !218, file: !1, line: 987, type: !64)
!1464 = !DILocation(line: 987, column: 25, scope: !218)
!1465 = !DILocalVariable(name: "data", arg: 2, scope: !218, file: !1, line: 987, type: !57)
!1466 = !DILocation(line: 987, column: 39, scope: !218)
!1467 = !DILocalVariable(name: "infop", scope: !218, file: !1, line: 989, type: !125)
!1468 = !DILocation(line: 989, column: 20, scope: !218)
!1469 = !DILocation(line: 989, column: 45, scope: !218)
!1470 = !DILocation(line: 989, column: 26, scope: !218)
!1471 = !DILocalVariable(name: "outc", scope: !218, file: !1, line: 990, type: !56)
!1472 = !DILocation(line: 990, column: 17, scope: !218)
!1473 = !DILocation(line: 990, column: 39, scope: !218)
!1474 = !DILocation(line: 990, column: 24, scope: !218)
!1475 = !DILocation(line: 992, column: 6, scope: !1476)
!1476 = distinct !DILexicalBlock(scope: !218, file: !1, line: 992, column: 6)
!1477 = !DILocation(line: 992, column: 13, scope: !1476)
!1478 = !DILocation(line: 992, column: 22, scope: !1476)
!1479 = !DILocation(line: 992, column: 29, scope: !1476)
!1480 = !DILocation(line: 992, column: 20, scope: !1476)
!1481 = !DILocation(line: 992, column: 6, scope: !218)
!1482 = !DILocation(line: 994, column: 24, scope: !1483)
!1483 = distinct !DILexicalBlock(scope: !1476, file: !1, line: 992, column: 34)
!1484 = !DILocation(line: 994, column: 5, scope: !1483)
!1485 = !DILocation(line: 994, column: 12, scope: !1483)
!1486 = !DILocation(line: 994, column: 22, scope: !1483)
!1487 = !DILocation(line: 995, column: 5, scope: !1483)
!1488 = !DILocation(line: 995, column: 12, scope: !1483)
!1489 = !DILocation(line: 995, column: 18, scope: !1483)
!1490 = !DILocation(line: 996, column: 5, scope: !1483)
!1491 = !DILocation(line: 996, column: 12, scope: !1483)
!1492 = !DILocation(line: 996, column: 18, scope: !1483)
!1493 = !DILocation(line: 997, column: 12, scope: !1483)
!1494 = !DILocation(line: 997, column: 5, scope: !1483)
!1495 = !DILocation(line: 999, column: 3, scope: !218)
!1496 = !DILocation(line: 1000, column: 1, scope: !218)
!1497 = !DILocalVariable(name: "buffer", arg: 1, scope: !154, file: !1, line: 1024, type: !54)
!1498 = !DILocation(line: 1024, column: 26, scope: !154)
!1499 = !DILocalVariable(name: "maxlength", arg: 2, scope: !154, file: !1, line: 1024, type: !110)
!1500 = !DILocation(line: 1024, column: 41, scope: !154)
!1501 = !DILocalVariable(name: "format", arg: 3, scope: !154, file: !1, line: 1024, type: !143)
!1502 = !DILocation(line: 1024, column: 64, scope: !154)
!1503 = !DILocalVariable(name: "retcode", scope: !154, file: !1, line: 1026, type: !64)
!1504 = !DILocation(line: 1026, column: 7, scope: !154)
!1505 = !DILocalVariable(name: "ap_save", scope: !154, file: !1, line: 1027, type: !1506)
!1506 = !DIDerivedType(tag: DW_TAG_typedef, name: "va_list", file: !59, line: 79, baseType: !1507)
!1507 = !DIDerivedType(tag: DW_TAG_typedef, name: "__gnuc_va_list", file: !1508, line: 50, baseType: !1509)
!1508 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stdarg.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1509 = !DIDerivedType(tag: DW_TAG_typedef, name: "__builtin_va_list", file: !1, line: 1027, baseType: !1510)
!1510 = !DICompositeType(tag: DW_TAG_array_type, baseType: !146, size: 192, align: 64, elements: !97)
!1511 = !DILocation(line: 1027, column: 11, scope: !154)
!1512 = !DILocation(line: 1028, column: 3, scope: !154)
!1513 = !DILocation(line: 1029, column: 29, scope: !154)
!1514 = !DILocation(line: 1029, column: 37, scope: !154)
!1515 = !DILocation(line: 1029, column: 48, scope: !154)
!1516 = !DILocation(line: 1029, column: 56, scope: !154)
!1517 = !DILocation(line: 1029, column: 13, scope: !154)
!1518 = !DILocation(line: 1029, column: 11, scope: !154)
!1519 = !DILocation(line: 1030, column: 3, scope: !154)
!1520 = !DILocation(line: 1031, column: 10, scope: !154)
!1521 = !DILocation(line: 1031, column: 3, scope: !154)
!1522 = !DILocalVariable(name: "format", arg: 1, scope: !157, file: !1, line: 1072, type: !143)
!1523 = !DILocation(line: 1072, column: 33, scope: !157)
!1524 = !DILocalVariable(name: "ap_save", scope: !157, file: !1, line: 1074, type: !1506)
!1525 = !DILocation(line: 1074, column: 11, scope: !157)
!1526 = !DILocalVariable(name: "retcode", scope: !157, file: !1, line: 1075, type: !64)
!1527 = !DILocation(line: 1075, column: 7, scope: !157)
!1528 = !DILocalVariable(name: "info", scope: !157, file: !1, line: 1076, type: !132)
!1529 = !DILocation(line: 1076, column: 19, scope: !157)
!1530 = !DILocation(line: 1078, column: 8, scope: !157)
!1531 = !DILocation(line: 1078, column: 15, scope: !157)
!1532 = !DILocation(line: 1079, column: 8, scope: !157)
!1533 = !DILocation(line: 1079, column: 12, scope: !157)
!1534 = !DILocation(line: 1080, column: 8, scope: !157)
!1535 = !DILocation(line: 1080, column: 14, scope: !157)
!1536 = !DILocation(line: 1081, column: 8, scope: !157)
!1537 = !DILocation(line: 1081, column: 13, scope: !157)
!1538 = !DILocation(line: 1083, column: 3, scope: !157)
!1539 = !DILocation(line: 1084, column: 29, scope: !157)
!1540 = !DILocation(line: 1084, column: 52, scope: !157)
!1541 = !DILocation(line: 1084, column: 60, scope: !157)
!1542 = !DILocation(line: 1084, column: 13, scope: !157)
!1543 = !DILocation(line: 1084, column: 11, scope: !157)
!1544 = !DILocation(line: 1085, column: 3, scope: !157)
!1545 = !DILocation(line: 1086, column: 13, scope: !1546)
!1546 = distinct !DILexicalBlock(scope: !157, file: !1, line: 1086, column: 6)
!1547 = !DILocation(line: 1086, column: 10, scope: !1546)
!1548 = !DILocation(line: 1086, column: 22, scope: !1546)
!1549 = !DILocation(line: 1086, column: 30, scope: !1550)
!1550 = !DILexicalBlockFile(scope: !1546, file: !1, discriminator: 1)
!1551 = !DILocation(line: 1086, column: 25, scope: !1550)
!1552 = !DILocation(line: 1086, column: 6, scope: !1550)
!1553 = !DILocation(line: 1087, column: 13, scope: !1554)
!1554 = distinct !DILexicalBlock(scope: !1555, file: !1, line: 1087, column: 8)
!1555 = distinct !DILexicalBlock(scope: !1546, file: !1, line: 1086, column: 36)
!1556 = !DILocation(line: 1087, column: 8, scope: !1554)
!1557 = !DILocation(line: 1087, column: 8, scope: !1555)
!1558 = !DILocation(line: 1088, column: 7, scope: !1554)
!1559 = !DILocation(line: 1089, column: 5, scope: !1555)
!1560 = !DILocation(line: 1091, column: 11, scope: !1561)
!1561 = distinct !DILexicalBlock(scope: !157, file: !1, line: 1091, column: 6)
!1562 = !DILocation(line: 1091, column: 6, scope: !1561)
!1563 = !DILocation(line: 1091, column: 6, scope: !157)
!1564 = !DILocation(line: 1092, column: 22, scope: !1565)
!1565 = distinct !DILexicalBlock(scope: !1561, file: !1, line: 1091, column: 18)
!1566 = !DILocation(line: 1092, column: 10, scope: !1565)
!1567 = !DILocation(line: 1092, column: 5, scope: !1565)
!1568 = !DILocation(line: 1092, column: 27, scope: !1565)
!1569 = !DILocation(line: 1093, column: 17, scope: !1565)
!1570 = !DILocation(line: 1093, column: 5, scope: !1565)
!1571 = !DILocation(line: 1095, column: 10, scope: !157)
!1572 = !DILocation(line: 1095, column: 3, scope: !157)
!1573 = !DILocation(line: 1096, column: 1, scope: !157)
!1574 = !DILocalVariable(name: "output", arg: 1, scope: !219, file: !1, line: 1035, type: !64)
!1575 = !DILocation(line: 1035, column: 31, scope: !219)
!1576 = !DILocalVariable(name: "data", arg: 2, scope: !219, file: !1, line: 1035, type: !57)
!1577 = !DILocation(line: 1035, column: 45, scope: !219)
!1578 = !DILocalVariable(name: "infop", scope: !219, file: !1, line: 1037, type: !131)
!1579 = !DILocation(line: 1037, column: 20, scope: !219)
!1580 = !DILocation(line: 1037, column: 45, scope: !219)
!1581 = !DILocation(line: 1037, column: 26, scope: !219)
!1582 = !DILocalVariable(name: "outc", scope: !219, file: !1, line: 1038, type: !56)
!1583 = !DILocation(line: 1038, column: 17, scope: !219)
!1584 = !DILocation(line: 1038, column: 39, scope: !219)
!1585 = !DILocation(line: 1038, column: 24, scope: !219)
!1586 = !DILocation(line: 1040, column: 7, scope: !1587)
!1587 = distinct !DILexicalBlock(scope: !219, file: !1, line: 1040, column: 6)
!1588 = !DILocation(line: 1040, column: 14, scope: !1587)
!1589 = !DILocation(line: 1040, column: 6, scope: !219)
!1590 = !DILocation(line: 1041, column: 21, scope: !1591)
!1591 = distinct !DILexicalBlock(scope: !1587, file: !1, line: 1040, column: 22)
!1592 = !DILocation(line: 1041, column: 5, scope: !1591)
!1593 = !DILocation(line: 1041, column: 12, scope: !1591)
!1594 = !DILocation(line: 1041, column: 19, scope: !1591)
!1595 = !DILocation(line: 1042, column: 9, scope: !1596)
!1596 = distinct !DILexicalBlock(scope: !1591, file: !1, line: 1042, column: 8)
!1597 = !DILocation(line: 1042, column: 16, scope: !1596)
!1598 = !DILocation(line: 1042, column: 8, scope: !1591)
!1599 = !DILocation(line: 1043, column: 7, scope: !1600)
!1600 = distinct !DILexicalBlock(scope: !1596, file: !1, line: 1042, column: 24)
!1601 = !DILocation(line: 1043, column: 14, scope: !1600)
!1602 = !DILocation(line: 1043, column: 19, scope: !1600)
!1603 = !DILocation(line: 1044, column: 7, scope: !1600)
!1604 = !DILocation(line: 1046, column: 5, scope: !1591)
!1605 = !DILocation(line: 1046, column: 12, scope: !1591)
!1606 = !DILocation(line: 1046, column: 18, scope: !1591)
!1607 = !DILocation(line: 1047, column: 5, scope: !1591)
!1608 = !DILocation(line: 1047, column: 12, scope: !1591)
!1609 = !DILocation(line: 1047, column: 16, scope: !1591)
!1610 = !DILocation(line: 1048, column: 3, scope: !1591)
!1611 = !DILocation(line: 1049, column: 11, scope: !1612)
!1612 = distinct !DILexicalBlock(scope: !1587, file: !1, line: 1049, column: 11)
!1613 = !DILocation(line: 1049, column: 18, scope: !1612)
!1614 = !DILocation(line: 1049, column: 21, scope: !1612)
!1615 = !DILocation(line: 1049, column: 27, scope: !1612)
!1616 = !DILocation(line: 1049, column: 34, scope: !1612)
!1617 = !DILocation(line: 1049, column: 24, scope: !1612)
!1618 = !DILocation(line: 1049, column: 11, scope: !1587)
!1619 = !DILocalVariable(name: "newptr", scope: !1620, file: !1, line: 1050, type: !54)
!1620 = distinct !DILexicalBlock(scope: !1612, file: !1, line: 1049, column: 41)
!1621 = !DILocation(line: 1050, column: 11, scope: !1620)
!1622 = !DILocalVariable(name: "newsize", scope: !1620, file: !1, line: 1051, type: !110)
!1623 = !DILocation(line: 1051, column: 12, scope: !1620)
!1624 = !DILocation(line: 1051, column: 22, scope: !1620)
!1625 = !DILocation(line: 1051, column: 29, scope: !1620)
!1626 = !DILocation(line: 1051, column: 34, scope: !1620)
!1627 = !DILocation(line: 1054, column: 8, scope: !1628)
!1628 = distinct !DILexicalBlock(scope: !1620, file: !1, line: 1054, column: 8)
!1629 = !DILocation(line: 1054, column: 18, scope: !1628)
!1630 = !DILocation(line: 1054, column: 25, scope: !1628)
!1631 = !DILocation(line: 1054, column: 16, scope: !1628)
!1632 = !DILocation(line: 1054, column: 8, scope: !1620)
!1633 = !DILocation(line: 1055, column: 16, scope: !1628)
!1634 = !DILocation(line: 1055, column: 14, scope: !1628)
!1635 = !DILocation(line: 1055, column: 7, scope: !1628)
!1636 = !DILocation(line: 1057, column: 9, scope: !1637)
!1637 = distinct !DILexicalBlock(scope: !1620, file: !1, line: 1057, column: 8)
!1638 = !DILocation(line: 1057, column: 8, scope: !1620)
!1639 = !DILocation(line: 1058, column: 7, scope: !1640)
!1640 = distinct !DILexicalBlock(scope: !1637, file: !1, line: 1057, column: 17)
!1641 = !DILocation(line: 1058, column: 14, scope: !1640)
!1642 = !DILocation(line: 1058, column: 19, scope: !1640)
!1643 = !DILocation(line: 1059, column: 7, scope: !1640)
!1644 = !DILocation(line: 1061, column: 21, scope: !1620)
!1645 = !DILocation(line: 1061, column: 5, scope: !1620)
!1646 = !DILocation(line: 1061, column: 12, scope: !1620)
!1647 = !DILocation(line: 1061, column: 19, scope: !1620)
!1648 = !DILocation(line: 1062, column: 20, scope: !1620)
!1649 = !DILocation(line: 1062, column: 5, scope: !1620)
!1650 = !DILocation(line: 1062, column: 12, scope: !1620)
!1651 = !DILocation(line: 1062, column: 18, scope: !1620)
!1652 = !DILocation(line: 1063, column: 3, scope: !1620)
!1653 = !DILocation(line: 1065, column: 33, scope: !219)
!1654 = !DILocation(line: 1065, column: 18, scope: !219)
!1655 = !DILocation(line: 1065, column: 25, scope: !219)
!1656 = !DILocation(line: 1065, column: 3, scope: !219)
!1657 = !DILocation(line: 1065, column: 10, scope: !219)
!1658 = !DILocation(line: 1065, column: 31, scope: !219)
!1659 = !DILocation(line: 1067, column: 3, scope: !219)
!1660 = !DILocation(line: 1067, column: 10, scope: !219)
!1661 = !DILocation(line: 1067, column: 13, scope: !219)
!1662 = !DILocation(line: 1069, column: 10, scope: !219)
!1663 = !DILocation(line: 1069, column: 3, scope: !219)
!1664 = !DILocation(line: 1070, column: 1, scope: !219)
!1665 = !DILocalVariable(name: "format", arg: 1, scope: !160, file: !1, line: 1098, type: !143)
!1666 = !DILocation(line: 1098, column: 34, scope: !160)
!1667 = !DILocalVariable(name: "ap_save", arg: 2, scope: !160, file: !1, line: 1098, type: !145)
!1668 = !DILocation(line: 1098, column: 50, scope: !160)
!1669 = !DILocalVariable(name: "retcode", scope: !160, file: !1, line: 1100, type: !64)
!1670 = !DILocation(line: 1100, column: 7, scope: !160)
!1671 = !DILocalVariable(name: "info", scope: !160, file: !1, line: 1101, type: !132)
!1672 = !DILocation(line: 1101, column: 19, scope: !160)
!1673 = !DILocation(line: 1103, column: 8, scope: !160)
!1674 = !DILocation(line: 1103, column: 15, scope: !160)
!1675 = !DILocation(line: 1104, column: 8, scope: !160)
!1676 = !DILocation(line: 1104, column: 12, scope: !160)
!1677 = !DILocation(line: 1105, column: 8, scope: !160)
!1678 = !DILocation(line: 1105, column: 14, scope: !160)
!1679 = !DILocation(line: 1106, column: 8, scope: !160)
!1680 = !DILocation(line: 1106, column: 13, scope: !160)
!1681 = !DILocation(line: 1108, column: 29, scope: !160)
!1682 = !DILocation(line: 1108, column: 52, scope: !160)
!1683 = !DILocation(line: 1108, column: 60, scope: !160)
!1684 = !DILocation(line: 1108, column: 13, scope: !160)
!1685 = !DILocation(line: 1108, column: 11, scope: !160)
!1686 = !DILocation(line: 1109, column: 13, scope: !1687)
!1687 = distinct !DILexicalBlock(scope: !160, file: !1, line: 1109, column: 6)
!1688 = !DILocation(line: 1109, column: 10, scope: !1687)
!1689 = !DILocation(line: 1109, column: 22, scope: !1687)
!1690 = !DILocation(line: 1109, column: 30, scope: !1691)
!1691 = !DILexicalBlockFile(scope: !1687, file: !1, discriminator: 1)
!1692 = !DILocation(line: 1109, column: 25, scope: !1691)
!1693 = !DILocation(line: 1109, column: 6, scope: !1691)
!1694 = !DILocation(line: 1110, column: 13, scope: !1695)
!1695 = distinct !DILexicalBlock(scope: !1696, file: !1, line: 1110, column: 8)
!1696 = distinct !DILexicalBlock(scope: !1687, file: !1, line: 1109, column: 36)
!1697 = !DILocation(line: 1110, column: 8, scope: !1695)
!1698 = !DILocation(line: 1110, column: 8, scope: !1696)
!1699 = !DILocation(line: 1111, column: 7, scope: !1695)
!1700 = !DILocation(line: 1112, column: 5, scope: !1696)
!1701 = !DILocation(line: 1115, column: 11, scope: !1702)
!1702 = distinct !DILexicalBlock(scope: !160, file: !1, line: 1115, column: 6)
!1703 = !DILocation(line: 1115, column: 6, scope: !1702)
!1704 = !DILocation(line: 1115, column: 6, scope: !160)
!1705 = !DILocation(line: 1116, column: 22, scope: !1706)
!1706 = distinct !DILexicalBlock(scope: !1702, file: !1, line: 1115, column: 18)
!1707 = !DILocation(line: 1116, column: 10, scope: !1706)
!1708 = !DILocation(line: 1116, column: 5, scope: !1706)
!1709 = !DILocation(line: 1116, column: 27, scope: !1706)
!1710 = !DILocation(line: 1117, column: 17, scope: !1706)
!1711 = !DILocation(line: 1117, column: 5, scope: !1706)
!1712 = !DILocation(line: 1119, column: 10, scope: !160)
!1713 = !DILocation(line: 1119, column: 3, scope: !160)
!1714 = !DILocation(line: 1120, column: 1, scope: !160)
!1715 = !DILocalVariable(name: "buffer", arg: 1, scope: !163, file: !1, line: 1131, type: !54)
!1716 = !DILocation(line: 1131, column: 25, scope: !163)
!1717 = !DILocalVariable(name: "format", arg: 2, scope: !163, file: !1, line: 1131, type: !143)
!1718 = !DILocation(line: 1131, column: 45, scope: !163)
!1719 = !DILocalVariable(name: "ap_save", scope: !163, file: !1, line: 1133, type: !1506)
!1720 = !DILocation(line: 1133, column: 11, scope: !163)
!1721 = !DILocalVariable(name: "retcode", scope: !163, file: !1, line: 1134, type: !64)
!1722 = !DILocation(line: 1134, column: 7, scope: !163)
!1723 = !DILocation(line: 1135, column: 3, scope: !163)
!1724 = !DILocation(line: 1136, column: 29, scope: !163)
!1725 = !DILocation(line: 1136, column: 51, scope: !163)
!1726 = !DILocation(line: 1136, column: 59, scope: !163)
!1727 = !DILocation(line: 1136, column: 13, scope: !163)
!1728 = !DILocation(line: 1136, column: 11, scope: !163)
!1729 = !DILocation(line: 1137, column: 3, scope: !163)
!1730 = !DILocation(line: 1138, column: 4, scope: !163)
!1731 = !DILocation(line: 1138, column: 10, scope: !163)
!1732 = !DILocation(line: 1139, column: 10, scope: !163)
!1733 = !DILocation(line: 1139, column: 3, scope: !163)
!1734 = !DILocalVariable(name: "output", arg: 1, scope: !220, file: !1, line: 1122, type: !64)
!1735 = !DILocation(line: 1122, column: 28, scope: !220)
!1736 = !DILocalVariable(name: "data", arg: 2, scope: !220, file: !1, line: 1122, type: !57)
!1737 = !DILocation(line: 1122, column: 42, scope: !220)
!1738 = !DILocalVariable(name: "buffer", scope: !220, file: !1, line: 1124, type: !138)
!1739 = !DILocation(line: 1124, column: 10, scope: !220)
!1740 = !DILocation(line: 1124, column: 28, scope: !220)
!1741 = !DILocation(line: 1124, column: 19, scope: !220)
!1742 = !DILocalVariable(name: "outc", scope: !220, file: !1, line: 1125, type: !56)
!1743 = !DILocation(line: 1125, column: 17, scope: !220)
!1744 = !DILocation(line: 1125, column: 39, scope: !220)
!1745 = !DILocation(line: 1125, column: 24, scope: !220)
!1746 = !DILocation(line: 1126, column: 14, scope: !220)
!1747 = !DILocation(line: 1126, column: 5, scope: !220)
!1748 = !DILocation(line: 1126, column: 4, scope: !220)
!1749 = !DILocation(line: 1126, column: 12, scope: !220)
!1750 = !DILocation(line: 1127, column: 5, scope: !220)
!1751 = !DILocation(line: 1127, column: 12, scope: !220)
!1752 = !DILocation(line: 1128, column: 10, scope: !220)
!1753 = !DILocation(line: 1128, column: 3, scope: !220)
!1754 = !DILocalVariable(name: "format", arg: 1, scope: !166, file: !1, line: 1142, type: !143)
!1755 = !DILocation(line: 1142, column: 30, scope: !166)
!1756 = !DILocalVariable(name: "retcode", scope: !166, file: !1, line: 1144, type: !64)
!1757 = !DILocation(line: 1144, column: 7, scope: !166)
!1758 = !DILocalVariable(name: "ap_save", scope: !166, file: !1, line: 1145, type: !1506)
!1759 = !DILocation(line: 1145, column: 11, scope: !166)
!1760 = !DILocation(line: 1146, column: 3, scope: !166)
!1761 = !DILocation(line: 1148, column: 29, scope: !166)
!1762 = !DILocation(line: 1148, column: 44, scope: !166)
!1763 = !DILocation(line: 1148, column: 52, scope: !166)
!1764 = !DILocation(line: 1148, column: 13, scope: !166)
!1765 = !DILocation(line: 1148, column: 11, scope: !166)
!1766 = !DILocation(line: 1149, column: 3, scope: !166)
!1767 = !DILocation(line: 1150, column: 10, scope: !166)
!1768 = !DILocation(line: 1150, column: 3, scope: !166)
!1769 = !DILocalVariable(name: "whereto", arg: 1, scope: !169, file: !1, line: 1153, type: !57)
!1770 = !DILocation(line: 1153, column: 25, scope: !169)
!1771 = !DILocalVariable(name: "format", arg: 2, scope: !169, file: !1, line: 1153, type: !143)
!1772 = !DILocation(line: 1153, column: 46, scope: !169)
!1773 = !DILocalVariable(name: "retcode", scope: !169, file: !1, line: 1155, type: !64)
!1774 = !DILocation(line: 1155, column: 7, scope: !169)
!1775 = !DILocalVariable(name: "ap_save", scope: !169, file: !1, line: 1156, type: !1506)
!1776 = !DILocation(line: 1156, column: 11, scope: !169)
!1777 = !DILocation(line: 1157, column: 3, scope: !169)
!1778 = !DILocation(line: 1158, column: 29, scope: !169)
!1779 = !DILocation(line: 1158, column: 45, scope: !169)
!1780 = !DILocation(line: 1158, column: 53, scope: !169)
!1781 = !DILocation(line: 1158, column: 13, scope: !169)
!1782 = !DILocation(line: 1158, column: 11, scope: !169)
!1783 = !DILocation(line: 1159, column: 3, scope: !169)
!1784 = !DILocation(line: 1160, column: 10, scope: !169)
!1785 = !DILocation(line: 1160, column: 3, scope: !169)
!1786 = !DILocalVariable(name: "buffer", arg: 1, scope: !172, file: !1, line: 1163, type: !54)
!1787 = !DILocation(line: 1163, column: 26, scope: !172)
!1788 = !DILocalVariable(name: "format", arg: 2, scope: !172, file: !1, line: 1163, type: !143)
!1789 = !DILocation(line: 1163, column: 46, scope: !172)
!1790 = !DILocalVariable(name: "ap_save", arg: 3, scope: !172, file: !1, line: 1163, type: !145)
!1791 = !DILocation(line: 1163, column: 62, scope: !172)
!1792 = !DILocalVariable(name: "retcode", scope: !172, file: !1, line: 1165, type: !64)
!1793 = !DILocation(line: 1165, column: 7, scope: !172)
!1794 = !DILocation(line: 1166, column: 29, scope: !172)
!1795 = !DILocation(line: 1166, column: 51, scope: !172)
!1796 = !DILocation(line: 1166, column: 59, scope: !172)
!1797 = !DILocation(line: 1166, column: 13, scope: !172)
!1798 = !DILocation(line: 1166, column: 11, scope: !172)
!1799 = !DILocation(line: 1167, column: 4, scope: !172)
!1800 = !DILocation(line: 1167, column: 10, scope: !172)
!1801 = !DILocation(line: 1168, column: 10, scope: !172)
!1802 = !DILocation(line: 1168, column: 3, scope: !172)
!1803 = !DILocalVariable(name: "format", arg: 1, scope: !175, file: !1, line: 1171, type: !143)
!1804 = !DILocation(line: 1171, column: 31, scope: !175)
!1805 = !DILocalVariable(name: "ap_save", arg: 2, scope: !175, file: !1, line: 1171, type: !145)
!1806 = !DILocation(line: 1171, column: 47, scope: !175)
!1807 = !DILocation(line: 1173, column: 26, scope: !175)
!1808 = !DILocation(line: 1173, column: 41, scope: !175)
!1809 = !DILocation(line: 1173, column: 49, scope: !175)
!1810 = !DILocation(line: 1173, column: 10, scope: !175)
!1811 = !DILocation(line: 1173, column: 3, scope: !175)
!1812 = !DILocalVariable(name: "whereto", arg: 1, scope: !178, file: !1, line: 1176, type: !57)
!1813 = !DILocation(line: 1176, column: 26, scope: !178)
!1814 = !DILocalVariable(name: "format", arg: 2, scope: !178, file: !1, line: 1176, type: !143)
!1815 = !DILocation(line: 1176, column: 47, scope: !178)
!1816 = !DILocalVariable(name: "ap_save", arg: 3, scope: !178, file: !1, line: 1176, type: !145)
!1817 = !DILocation(line: 1176, column: 63, scope: !178)
!1818 = !DILocation(line: 1178, column: 26, scope: !178)
!1819 = !DILocation(line: 1178, column: 42, scope: !178)
!1820 = !DILocation(line: 1178, column: 50, scope: !178)
!1821 = !DILocation(line: 1178, column: 10, scope: !178)
!1822 = !DILocation(line: 1178, column: 3, scope: !178)
!1823 = !DILocalVariable(name: "format", arg: 1, scope: !187, file: !1, line: 231, type: !143)
!1824 = !DILocation(line: 231, column: 38, scope: !187)
!1825 = !DILocalVariable(name: "vto", arg: 2, scope: !187, file: !1, line: 231, type: !190)
!1826 = !DILocation(line: 231, column: 58, scope: !187)
!1827 = !DILocalVariable(name: "endpos", arg: 3, scope: !187, file: !1, line: 231, type: !138)
!1828 = !DILocation(line: 231, column: 70, scope: !187)
!1829 = !DILocalVariable(name: "arglist", arg: 4, scope: !187, file: !1, line: 232, type: !145)
!1830 = !DILocation(line: 232, column: 34, scope: !187)
!1831 = !DILocalVariable(name: "fmt", scope: !187, file: !1, line: 234, type: !54)
!1832 = !DILocation(line: 234, column: 9, scope: !187)
!1833 = !DILocation(line: 234, column: 23, scope: !187)
!1834 = !DILocalVariable(name: "param_num", scope: !187, file: !1, line: 235, type: !64)
!1835 = !DILocation(line: 235, column: 7, scope: !187)
!1836 = !DILocalVariable(name: "this_param", scope: !187, file: !1, line: 236, type: !90)
!1837 = !DILocation(line: 236, column: 8, scope: !187)
!1838 = !DILocalVariable(name: "width", scope: !187, file: !1, line: 237, type: !90)
!1839 = !DILocation(line: 237, column: 8, scope: !187)
!1840 = !DILocalVariable(name: "precision", scope: !187, file: !1, line: 238, type: !90)
!1841 = !DILocation(line: 238, column: 8, scope: !187)
!1842 = !DILocalVariable(name: "flags", scope: !187, file: !1, line: 239, type: !64)
!1843 = !DILocation(line: 239, column: 7, scope: !187)
!1844 = !DILocalVariable(name: "max_param", scope: !187, file: !1, line: 240, type: !90)
!1845 = !DILocation(line: 240, column: 8, scope: !187)
!1846 = !DILocalVariable(name: "i", scope: !187, file: !1, line: 241, type: !90)
!1847 = !DILocation(line: 241, column: 8, scope: !187)
!1848 = !DILocation(line: 243, column: 3, scope: !187)
!1849 = !DILocation(line: 243, column: 10, scope: !1850)
!1850 = !DILexicalBlockFile(scope: !187, file: !1, discriminator: 1)
!1851 = !DILocation(line: 243, column: 9, scope: !1850)
!1852 = !DILocation(line: 243, column: 3, scope: !1850)
!1853 = !DILocation(line: 244, column: 12, scope: !1854)
!1854 = distinct !DILexicalBlock(scope: !1855, file: !1, line: 244, column: 8)
!1855 = distinct !DILexicalBlock(scope: !187, file: !1, line: 243, column: 15)
!1856 = !DILocation(line: 244, column: 8, scope: !1854)
!1857 = !DILocation(line: 244, column: 15, scope: !1854)
!1858 = !DILocation(line: 244, column: 8, scope: !1855)
!1859 = !DILocation(line: 245, column: 11, scope: !1860)
!1860 = distinct !DILexicalBlock(scope: !1861, file: !1, line: 245, column: 10)
!1861 = distinct !DILexicalBlock(scope: !1854, file: !1, line: 244, column: 23)
!1862 = !DILocation(line: 245, column: 10, scope: !1860)
!1863 = !DILocation(line: 245, column: 15, scope: !1860)
!1864 = !DILocation(line: 245, column: 10, scope: !1861)
!1865 = !DILocation(line: 246, column: 12, scope: !1866)
!1866 = distinct !DILexicalBlock(scope: !1860, file: !1, line: 245, column: 23)
!1867 = !DILocation(line: 247, column: 9, scope: !1866)
!1868 = !DILocation(line: 250, column: 13, scope: !1861)
!1869 = !DILocation(line: 254, column: 16, scope: !1861)
!1870 = !DILocation(line: 256, column: 41, scope: !1861)
!1871 = !DILocation(line: 256, column: 20, scope: !1861)
!1872 = !DILocation(line: 256, column: 18, scope: !1861)
!1873 = !DILocation(line: 257, column: 15, scope: !1874)
!1874 = distinct !DILexicalBlock(scope: !1861, file: !1, line: 257, column: 10)
!1875 = !DILocation(line: 257, column: 12, scope: !1874)
!1876 = !DILocation(line: 257, column: 10, scope: !1861)
!1877 = !DILocation(line: 259, column: 22, scope: !1874)
!1878 = !DILocation(line: 259, column: 20, scope: !1874)
!1879 = !DILocation(line: 259, column: 9, scope: !1874)
!1880 = !DILocation(line: 261, column: 10, scope: !1881)
!1881 = distinct !DILexicalBlock(scope: !1861, file: !1, line: 261, column: 10)
!1882 = !DILocation(line: 261, column: 23, scope: !1881)
!1883 = !DILocation(line: 261, column: 21, scope: !1881)
!1884 = !DILocation(line: 261, column: 10, scope: !1861)
!1885 = !DILocation(line: 262, column: 21, scope: !1881)
!1886 = !DILocation(line: 262, column: 19, scope: !1881)
!1887 = !DILocation(line: 262, column: 9, scope: !1881)
!1888 = !DILocation(line: 270, column: 13, scope: !1861)
!1889 = !DILocation(line: 271, column: 17, scope: !1861)
!1890 = !DILocation(line: 275, column: 7, scope: !1861)
!1891 = !DILocation(line: 275, column: 41, scope: !1892)
!1892 = !DILexicalBlockFile(scope: !1861, file: !1, discriminator: 1)
!1893 = !DILocation(line: 275, column: 13, scope: !1892)
!1894 = !DILocation(line: 275, column: 7, scope: !1892)
!1895 = !DILocation(line: 288, column: 20, scope: !1896)
!1896 = distinct !DILexicalBlock(scope: !1861, file: !1, line: 275, column: 47)
!1897 = !DILocation(line: 288, column: 16, scope: !1896)
!1898 = !DILocation(line: 288, column: 9, scope: !1896)
!1899 = !DILocation(line: 290, column: 17, scope: !1900)
!1900 = distinct !DILexicalBlock(scope: !1896, file: !1, line: 288, column: 24)
!1901 = !DILocation(line: 291, column: 11, scope: !1900)
!1902 = !DILocation(line: 293, column: 17, scope: !1900)
!1903 = !DILocation(line: 294, column: 11, scope: !1900)
!1904 = !DILocation(line: 296, column: 17, scope: !1900)
!1905 = !DILocation(line: 297, column: 17, scope: !1900)
!1906 = !DILocation(line: 298, column: 11, scope: !1900)
!1907 = !DILocation(line: 300, column: 17, scope: !1900)
!1908 = !DILocation(line: 301, column: 11, scope: !1900)
!1909 = !DILocation(line: 303, column: 22, scope: !1910)
!1910 = distinct !DILexicalBlock(scope: !1900, file: !1, line: 303, column: 14)
!1911 = !DILocation(line: 303, column: 21, scope: !1910)
!1912 = !DILocation(line: 303, column: 18, scope: !1910)
!1913 = !DILocation(line: 303, column: 14, scope: !1900)
!1914 = !DILocation(line: 306, column: 19, scope: !1915)
!1915 = distinct !DILexicalBlock(scope: !1910, file: !1, line: 303, column: 27)
!1916 = !DILocation(line: 307, column: 16, scope: !1915)
!1917 = !DILocation(line: 308, column: 22, scope: !1915)
!1918 = !DILocation(line: 310, column: 38, scope: !1915)
!1919 = !DILocation(line: 310, column: 17, scope: !1915)
!1920 = !DILocation(line: 310, column: 15, scope: !1915)
!1921 = !DILocation(line: 311, column: 16, scope: !1922)
!1922 = distinct !DILexicalBlock(scope: !1915, file: !1, line: 311, column: 16)
!1923 = !DILocation(line: 311, column: 16, scope: !1915)
!1924 = !DILocation(line: 312, column: 27, scope: !1922)
!1925 = !DILocation(line: 312, column: 25, scope: !1922)
!1926 = !DILocation(line: 312, column: 15, scope: !1922)
!1927 = !DILocation(line: 314, column: 27, scope: !1922)
!1928 = !DILocation(line: 314, column: 25, scope: !1922)
!1929 = !DILocation(line: 316, column: 16, scope: !1930)
!1930 = distinct !DILexicalBlock(scope: !1915, file: !1, line: 316, column: 16)
!1931 = !DILocation(line: 316, column: 28, scope: !1930)
!1932 = !DILocation(line: 316, column: 26, scope: !1930)
!1933 = !DILocation(line: 316, column: 16, scope: !1915)
!1934 = !DILocation(line: 317, column: 27, scope: !1930)
!1935 = !DILocation(line: 317, column: 25, scope: !1930)
!1936 = !DILocation(line: 317, column: 15, scope: !1930)
!1937 = !DILocation(line: 318, column: 11, scope: !1915)
!1938 = !DILocation(line: 320, column: 19, scope: !1939)
!1939 = distinct !DILexicalBlock(scope: !1910, file: !1, line: 319, column: 16)
!1940 = !DILocation(line: 321, column: 32, scope: !1939)
!1941 = !DILocation(line: 321, column: 25, scope: !1939)
!1942 = !DILocation(line: 321, column: 23, scope: !1939)
!1943 = !DILocation(line: 323, column: 11, scope: !1900)
!1944 = !DILocation(line: 325, column: 17, scope: !1900)
!1945 = !DILocation(line: 326, column: 11, scope: !1900)
!1946 = !DILocation(line: 337, column: 14, scope: !1947)
!1947 = distinct !DILexicalBlock(scope: !1900, file: !1, line: 337, column: 14)
!1948 = !DILocation(line: 337, column: 20, scope: !1947)
!1949 = !DILocation(line: 337, column: 14, scope: !1900)
!1950 = !DILocation(line: 338, column: 19, scope: !1947)
!1951 = !DILocation(line: 338, column: 13, scope: !1947)
!1952 = !DILocation(line: 340, column: 19, scope: !1947)
!1953 = !DILocation(line: 341, column: 11, scope: !1900)
!1954 = !DILocation(line: 343, column: 17, scope: !1900)
!1955 = !DILocation(line: 344, column: 11, scope: !1900)
!1956 = !DILocation(line: 346, column: 17, scope: !1900)
!1957 = !DILocation(line: 347, column: 11, scope: !1900)
!1958 = !DILocation(line: 354, column: 17, scope: !1900)
!1959 = !DILocation(line: 356, column: 11, scope: !1900)
!1960 = !DILocation(line: 361, column: 17, scope: !1900)
!1961 = !DILocation(line: 363, column: 11, scope: !1900)
!1962 = !DILocation(line: 365, column: 16, scope: !1963)
!1963 = distinct !DILexicalBlock(scope: !1900, file: !1, line: 365, column: 14)
!1964 = !DILocation(line: 365, column: 22, scope: !1963)
!1965 = !DILocation(line: 365, column: 14, scope: !1900)
!1966 = !DILocation(line: 366, column: 19, scope: !1963)
!1967 = !DILocation(line: 366, column: 13, scope: !1963)
!1968 = !DILocation(line: 365, column: 34, scope: !1969)
!1969 = !DILexicalBlockFile(scope: !1963, file: !1, discriminator: 1)
!1970 = !DILocation(line: 370, column: 17, scope: !1900)
!1971 = !DILocation(line: 371, column: 26, scope: !1900)
!1972 = !DILocation(line: 371, column: 29, scope: !1900)
!1973 = !DILocation(line: 371, column: 19, scope: !1900)
!1974 = !DILocation(line: 371, column: 17, scope: !1900)
!1975 = !DILocation(line: 372, column: 11, scope: !1900)
!1976 = !DILocation(line: 374, column: 17, scope: !1900)
!1977 = !DILocation(line: 375, column: 20, scope: !1900)
!1978 = !DILocation(line: 377, column: 36, scope: !1900)
!1979 = !DILocation(line: 377, column: 15, scope: !1900)
!1980 = !DILocation(line: 377, column: 13, scope: !1900)
!1981 = !DILocation(line: 378, column: 14, scope: !1982)
!1982 = distinct !DILexicalBlock(scope: !1900, file: !1, line: 378, column: 14)
!1983 = !DILocation(line: 378, column: 14, scope: !1900)
!1984 = !DILocation(line: 379, column: 21, scope: !1982)
!1985 = !DILocation(line: 379, column: 19, scope: !1982)
!1986 = !DILocation(line: 379, column: 13, scope: !1982)
!1987 = !DILocation(line: 381, column: 21, scope: !1982)
!1988 = !DILocation(line: 381, column: 19, scope: !1982)
!1989 = !DILocation(line: 382, column: 14, scope: !1990)
!1990 = distinct !DILexicalBlock(scope: !1900, file: !1, line: 382, column: 14)
!1991 = !DILocation(line: 382, column: 22, scope: !1990)
!1992 = !DILocation(line: 382, column: 20, scope: !1990)
!1993 = !DILocation(line: 382, column: 14, scope: !1900)
!1994 = !DILocation(line: 383, column: 23, scope: !1990)
!1995 = !DILocation(line: 383, column: 22, scope: !1990)
!1996 = !DILocation(line: 383, column: 13, scope: !1990)
!1997 = !DILocation(line: 384, column: 11, scope: !1900)
!1998 = !DILocation(line: 386, column: 11, scope: !1900)
!1999 = !DILocation(line: 275, column: 7, scope: !2000)
!2000 = !DILexicalBlockFile(scope: !1861, file: !1, discriminator: 2)
!2001 = !DILocation(line: 392, column: 11, scope: !1861)
!2002 = !DILocation(line: 392, column: 22, scope: !1861)
!2003 = !DILocation(line: 392, column: 9, scope: !1861)
!2004 = !DILocation(line: 394, column: 11, scope: !2005)
!2005 = distinct !DILexicalBlock(scope: !1861, file: !1, line: 394, column: 10)
!2006 = !DILocation(line: 394, column: 13, scope: !2005)
!2007 = !DILocation(line: 394, column: 18, scope: !2005)
!2008 = !DILocation(line: 394, column: 22, scope: !2009)
!2009 = !DILexicalBlockFile(scope: !2005, file: !1, discriminator: 1)
!2010 = !DILocation(line: 394, column: 24, scope: !2009)
!2011 = !DILocation(line: 394, column: 10, scope: !2009)
!2012 = !DILocation(line: 396, column: 9, scope: !2005)
!2013 = !DILocation(line: 398, column: 16, scope: !1861)
!2014 = !DILocation(line: 398, column: 15, scope: !1861)
!2015 = !DILocation(line: 398, column: 7, scope: !1861)
!2016 = !DILocation(line: 400, column: 15, scope: !2017)
!2017 = distinct !DILexicalBlock(scope: !1861, file: !1, line: 398, column: 21)
!2018 = !DILocation(line: 400, column: 9, scope: !2017)
!2019 = !DILocation(line: 403, column: 13, scope: !2017)
!2020 = !DILocation(line: 403, column: 9, scope: !2017)
!2021 = !DILocation(line: 403, column: 16, scope: !2017)
!2022 = !DILocation(line: 403, column: 21, scope: !2017)
!2023 = !DILocation(line: 404, column: 9, scope: !2017)
!2024 = !DILocation(line: 406, column: 13, scope: !2017)
!2025 = !DILocation(line: 406, column: 9, scope: !2017)
!2026 = !DILocation(line: 406, column: 16, scope: !2017)
!2027 = !DILocation(line: 406, column: 21, scope: !2017)
!2028 = !DILocation(line: 407, column: 9, scope: !2017)
!2029 = !DILocation(line: 409, column: 13, scope: !2017)
!2030 = !DILocation(line: 409, column: 9, scope: !2017)
!2031 = !DILocation(line: 409, column: 16, scope: !2017)
!2032 = !DILocation(line: 409, column: 21, scope: !2017)
!2033 = !DILocation(line: 410, column: 9, scope: !2017)
!2034 = !DILocation(line: 412, column: 13, scope: !2017)
!2035 = !DILocation(line: 412, column: 9, scope: !2017)
!2036 = !DILocation(line: 412, column: 16, scope: !2017)
!2037 = !DILocation(line: 412, column: 21, scope: !2017)
!2038 = !DILocation(line: 413, column: 9, scope: !2017)
!2039 = !DILocation(line: 415, column: 13, scope: !2017)
!2040 = !DILocation(line: 415, column: 9, scope: !2017)
!2041 = !DILocation(line: 415, column: 16, scope: !2017)
!2042 = !DILocation(line: 415, column: 21, scope: !2017)
!2043 = !DILocation(line: 416, column: 15, scope: !2017)
!2044 = !DILocation(line: 417, column: 9, scope: !2017)
!2045 = !DILocation(line: 419, column: 13, scope: !2017)
!2046 = !DILocation(line: 419, column: 9, scope: !2017)
!2047 = !DILocation(line: 419, column: 16, scope: !2017)
!2048 = !DILocation(line: 419, column: 21, scope: !2017)
!2049 = !DILocation(line: 420, column: 15, scope: !2017)
!2050 = !DILocation(line: 421, column: 9, scope: !2017)
!2051 = !DILocation(line: 423, column: 13, scope: !2017)
!2052 = !DILocation(line: 423, column: 9, scope: !2017)
!2053 = !DILocation(line: 423, column: 16, scope: !2017)
!2054 = !DILocation(line: 423, column: 21, scope: !2017)
!2055 = !DILocation(line: 424, column: 15, scope: !2017)
!2056 = !DILocation(line: 425, column: 9, scope: !2017)
!2057 = !DILocation(line: 427, column: 13, scope: !2017)
!2058 = !DILocation(line: 427, column: 9, scope: !2017)
!2059 = !DILocation(line: 427, column: 16, scope: !2017)
!2060 = !DILocation(line: 427, column: 21, scope: !2017)
!2061 = !DILocation(line: 428, column: 15, scope: !2017)
!2062 = !DILocation(line: 429, column: 9, scope: !2017)
!2063 = !DILocation(line: 431, column: 13, scope: !2017)
!2064 = !DILocation(line: 431, column: 9, scope: !2017)
!2065 = !DILocation(line: 431, column: 16, scope: !2017)
!2066 = !DILocation(line: 431, column: 21, scope: !2017)
!2067 = !DILocation(line: 432, column: 15, scope: !2017)
!2068 = !DILocation(line: 433, column: 9, scope: !2017)
!2069 = !DILocation(line: 435, column: 13, scope: !2017)
!2070 = !DILocation(line: 435, column: 9, scope: !2017)
!2071 = !DILocation(line: 435, column: 16, scope: !2017)
!2072 = !DILocation(line: 435, column: 21, scope: !2017)
!2073 = !DILocation(line: 436, column: 9, scope: !2017)
!2074 = !DILocation(line: 438, column: 13, scope: !2017)
!2075 = !DILocation(line: 438, column: 9, scope: !2017)
!2076 = !DILocation(line: 438, column: 16, scope: !2017)
!2077 = !DILocation(line: 438, column: 21, scope: !2017)
!2078 = !DILocation(line: 439, column: 15, scope: !2017)
!2079 = !DILocation(line: 440, column: 9, scope: !2017)
!2080 = !DILocation(line: 442, column: 13, scope: !2017)
!2081 = !DILocation(line: 442, column: 9, scope: !2017)
!2082 = !DILocation(line: 442, column: 16, scope: !2017)
!2083 = !DILocation(line: 442, column: 21, scope: !2017)
!2084 = !DILocation(line: 443, column: 15, scope: !2017)
!2085 = !DILocation(line: 444, column: 9, scope: !2017)
!2086 = !DILocation(line: 446, column: 13, scope: !2017)
!2087 = !DILocation(line: 446, column: 9, scope: !2017)
!2088 = !DILocation(line: 446, column: 16, scope: !2017)
!2089 = !DILocation(line: 446, column: 21, scope: !2017)
!2090 = !DILocation(line: 447, column: 15, scope: !2017)
!2091 = !DILocation(line: 448, column: 9, scope: !2017)
!2092 = !DILocation(line: 450, column: 13, scope: !2017)
!2093 = !DILocation(line: 450, column: 9, scope: !2017)
!2094 = !DILocation(line: 450, column: 16, scope: !2017)
!2095 = !DILocation(line: 450, column: 21, scope: !2017)
!2096 = !DILocation(line: 451, column: 15, scope: !2017)
!2097 = !DILocation(line: 452, column: 9, scope: !2017)
!2098 = !DILocation(line: 454, column: 13, scope: !2017)
!2099 = !DILocation(line: 454, column: 9, scope: !2017)
!2100 = !DILocation(line: 454, column: 16, scope: !2017)
!2101 = !DILocation(line: 454, column: 21, scope: !2017)
!2102 = !DILocation(line: 455, column: 9, scope: !2017)
!2103 = !DILocation(line: 458, column: 22, scope: !1861)
!2104 = !DILocation(line: 458, column: 11, scope: !1861)
!2105 = !DILocation(line: 458, column: 7, scope: !1861)
!2106 = !DILocation(line: 458, column: 14, scope: !1861)
!2107 = !DILocation(line: 458, column: 20, scope: !1861)
!2108 = !DILocation(line: 459, column: 22, scope: !1861)
!2109 = !DILocation(line: 459, column: 11, scope: !1861)
!2110 = !DILocation(line: 459, column: 7, scope: !1861)
!2111 = !DILocation(line: 459, column: 14, scope: !1861)
!2112 = !DILocation(line: 459, column: 20, scope: !1861)
!2113 = !DILocation(line: 460, column: 26, scope: !1861)
!2114 = !DILocation(line: 460, column: 11, scope: !1861)
!2115 = !DILocation(line: 460, column: 7, scope: !1861)
!2116 = !DILocation(line: 460, column: 14, scope: !1861)
!2117 = !DILocation(line: 460, column: 24, scope: !1861)
!2118 = !DILocation(line: 462, column: 10, scope: !2119)
!2119 = distinct !DILexicalBlock(scope: !1861, file: !1, line: 462, column: 10)
!2120 = !DILocation(line: 462, column: 16, scope: !2119)
!2121 = !DILocation(line: 462, column: 10, scope: !1861)
!2122 = !DILocalVariable(name: "k", scope: !2123, file: !1, line: 465, type: !90)
!2123 = distinct !DILexicalBlock(scope: !2119, file: !1, line: 462, column: 36)
!2124 = !DILocation(line: 465, column: 14, scope: !2123)
!2125 = !DILocation(line: 465, column: 18, scope: !2123)
!2126 = !DILocation(line: 465, column: 24, scope: !2123)
!2127 = !DILocation(line: 466, column: 24, scope: !2123)
!2128 = !DILocation(line: 466, column: 13, scope: !2123)
!2129 = !DILocation(line: 466, column: 9, scope: !2123)
!2130 = !DILocation(line: 466, column: 16, scope: !2123)
!2131 = !DILocation(line: 466, column: 22, scope: !2123)
!2132 = !DILocation(line: 467, column: 13, scope: !2123)
!2133 = !DILocation(line: 467, column: 9, scope: !2123)
!2134 = !DILocation(line: 467, column: 16, scope: !2123)
!2135 = !DILocation(line: 467, column: 21, scope: !2123)
!2136 = !DILocation(line: 468, column: 13, scope: !2123)
!2137 = !DILocation(line: 468, column: 9, scope: !2123)
!2138 = !DILocation(line: 468, column: 16, scope: !2123)
!2139 = !DILocation(line: 468, column: 22, scope: !2123)
!2140 = !DILocation(line: 470, column: 13, scope: !2123)
!2141 = !DILocation(line: 470, column: 9, scope: !2123)
!2142 = !DILocation(line: 470, column: 16, scope: !2123)
!2143 = !DILocation(line: 470, column: 22, scope: !2123)
!2144 = !DILocation(line: 471, column: 13, scope: !2123)
!2145 = !DILocation(line: 471, column: 9, scope: !2123)
!2146 = !DILocation(line: 471, column: 16, scope: !2123)
!2147 = !DILocation(line: 471, column: 26, scope: !2123)
!2148 = !DILocation(line: 472, column: 7, scope: !2123)
!2149 = !DILocation(line: 473, column: 10, scope: !2150)
!2150 = distinct !DILexicalBlock(scope: !1861, file: !1, line: 473, column: 10)
!2151 = !DILocation(line: 473, column: 16, scope: !2150)
!2152 = !DILocation(line: 473, column: 10, scope: !1861)
!2153 = !DILocalVariable(name: "k", scope: !2154, file: !1, line: 476, type: !90)
!2154 = distinct !DILexicalBlock(scope: !2150, file: !1, line: 473, column: 35)
!2155 = !DILocation(line: 476, column: 14, scope: !2154)
!2156 = !DILocation(line: 476, column: 18, scope: !2154)
!2157 = !DILocation(line: 476, column: 28, scope: !2154)
!2158 = !DILocation(line: 477, column: 28, scope: !2154)
!2159 = !DILocation(line: 477, column: 13, scope: !2154)
!2160 = !DILocation(line: 477, column: 9, scope: !2154)
!2161 = !DILocation(line: 477, column: 16, scope: !2154)
!2162 = !DILocation(line: 477, column: 26, scope: !2154)
!2163 = !DILocation(line: 478, column: 13, scope: !2154)
!2164 = !DILocation(line: 478, column: 9, scope: !2154)
!2165 = !DILocation(line: 478, column: 16, scope: !2154)
!2166 = !DILocation(line: 478, column: 21, scope: !2154)
!2167 = !DILocation(line: 479, column: 13, scope: !2154)
!2168 = !DILocation(line: 479, column: 9, scope: !2154)
!2169 = !DILocation(line: 479, column: 16, scope: !2154)
!2170 = !DILocation(line: 479, column: 22, scope: !2154)
!2171 = !DILocation(line: 481, column: 13, scope: !2154)
!2172 = !DILocation(line: 481, column: 9, scope: !2154)
!2173 = !DILocation(line: 481, column: 16, scope: !2154)
!2174 = !DILocation(line: 481, column: 22, scope: !2154)
!2175 = !DILocation(line: 482, column: 13, scope: !2154)
!2176 = !DILocation(line: 482, column: 9, scope: !2154)
!2177 = !DILocation(line: 482, column: 16, scope: !2154)
!2178 = !DILocation(line: 482, column: 26, scope: !2154)
!2179 = !DILocation(line: 483, column: 7, scope: !2154)
!2180 = !DILocation(line: 484, column: 19, scope: !1861)
!2181 = !DILocation(line: 484, column: 23, scope: !1861)
!2182 = !DILocation(line: 484, column: 14, scope: !1861)
!2183 = !DILocation(line: 484, column: 17, scope: !1861)
!2184 = !DILocation(line: 485, column: 5, scope: !1861)
!2185 = !DILocation(line: 243, column: 3, scope: !2186)
!2186 = !DILexicalBlockFile(scope: !187, file: !1, discriminator: 2)
!2187 = !DILocation(line: 489, column: 8, scope: !2188)
!2188 = distinct !DILexicalBlock(scope: !187, file: !1, line: 489, column: 3)
!2189 = !DILocation(line: 489, column: 7, scope: !2188)
!2190 = !DILocation(line: 489, column: 12, scope: !2191)
!2191 = !DILexicalBlockFile(scope: !2192, file: !1, discriminator: 1)
!2192 = distinct !DILexicalBlock(scope: !2188, file: !1, line: 489, column: 3)
!2193 = !DILocation(line: 489, column: 14, scope: !2191)
!2194 = !DILocation(line: 489, column: 13, scope: !2191)
!2195 = !DILocation(line: 489, column: 3, scope: !2191)
!2196 = !DILocation(line: 492, column: 12, scope: !2197)
!2197 = distinct !DILexicalBlock(scope: !2198, file: !1, line: 492, column: 8)
!2198 = distinct !DILexicalBlock(scope: !2192, file: !1, line: 489, column: 30)
!2199 = !DILocation(line: 492, column: 8, scope: !2197)
!2200 = !DILocation(line: 492, column: 15, scope: !2197)
!2201 = !DILocation(line: 492, column: 21, scope: !2197)
!2202 = !DILocation(line: 492, column: 8, scope: !2198)
!2203 = !DILocation(line: 494, column: 22, scope: !2204)
!2204 = distinct !DILexicalBlock(scope: !2197, file: !1, line: 492, column: 41)
!2205 = !DILocation(line: 494, column: 22, scope: !2206)
!2206 = !DILexicalBlockFile(scope: !2204, file: !1, discriminator: 1)
!2207 = !DILocation(line: 494, column: 22, scope: !2208)
!2208 = !DILexicalBlockFile(scope: !2204, file: !1, discriminator: 2)
!2209 = !DILocation(line: 494, column: 22, scope: !2210)
!2210 = !DILexicalBlockFile(scope: !2204, file: !1, discriminator: 3)
!2211 = !DILocation(line: 494, column: 9, scope: !2210)
!2212 = !DILocation(line: 493, column: 15, scope: !2204)
!2213 = !DILocation(line: 493, column: 11, scope: !2204)
!2214 = !DILocation(line: 493, column: 18, scope: !2204)
!2215 = !DILocation(line: 493, column: 7, scope: !2204)
!2216 = !DILocation(line: 493, column: 25, scope: !2204)
!2217 = !DILocation(line: 493, column: 30, scope: !2204)
!2218 = !DILocation(line: 493, column: 34, scope: !2204)
!2219 = !DILocation(line: 493, column: 44, scope: !2204)
!2220 = !DILocation(line: 495, column: 5, scope: !2204)
!2221 = !DILocation(line: 496, column: 12, scope: !2222)
!2222 = distinct !DILexicalBlock(scope: !2198, file: !1, line: 496, column: 8)
!2223 = !DILocation(line: 496, column: 8, scope: !2222)
!2224 = !DILocation(line: 496, column: 15, scope: !2222)
!2225 = !DILocation(line: 496, column: 21, scope: !2222)
!2226 = !DILocation(line: 496, column: 8, scope: !2198)
!2227 = !DILocation(line: 498, column: 22, scope: !2228)
!2228 = distinct !DILexicalBlock(scope: !2222, file: !1, line: 496, column: 40)
!2229 = !DILocation(line: 498, column: 22, scope: !2230)
!2230 = !DILexicalBlockFile(scope: !2228, file: !1, discriminator: 1)
!2231 = !DILocation(line: 498, column: 22, scope: !2232)
!2232 = !DILexicalBlockFile(scope: !2228, file: !1, discriminator: 2)
!2233 = !DILocation(line: 498, column: 22, scope: !2234)
!2234 = !DILexicalBlockFile(scope: !2228, file: !1, discriminator: 3)
!2235 = !DILocation(line: 498, column: 9, scope: !2234)
!2236 = !DILocation(line: 497, column: 15, scope: !2228)
!2237 = !DILocation(line: 497, column: 11, scope: !2228)
!2238 = !DILocation(line: 497, column: 18, scope: !2228)
!2239 = !DILocation(line: 497, column: 7, scope: !2228)
!2240 = !DILocation(line: 497, column: 29, scope: !2228)
!2241 = !DILocation(line: 497, column: 34, scope: !2228)
!2242 = !DILocation(line: 497, column: 38, scope: !2228)
!2243 = !DILocation(line: 497, column: 48, scope: !2228)
!2244 = !DILocation(line: 499, column: 5, scope: !2228)
!2245 = !DILocation(line: 501, column: 16, scope: !2198)
!2246 = !DILocation(line: 501, column: 12, scope: !2198)
!2247 = !DILocation(line: 501, column: 19, scope: !2198)
!2248 = !DILocation(line: 501, column: 5, scope: !2198)
!2249 = !DILocation(line: 503, column: 25, scope: !2250)
!2250 = distinct !DILexicalBlock(scope: !2198, file: !1, line: 501, column: 25)
!2251 = !DILocation(line: 503, column: 25, scope: !2252)
!2252 = !DILexicalBlockFile(scope: !2250, file: !1, discriminator: 1)
!2253 = !DILocation(line: 503, column: 25, scope: !2254)
!2254 = !DILexicalBlockFile(scope: !2250, file: !1, discriminator: 2)
!2255 = !DILocation(line: 503, column: 25, scope: !2256)
!2256 = !DILexicalBlockFile(scope: !2250, file: !1, discriminator: 3)
!2257 = !DILocation(line: 503, column: 11, scope: !2256)
!2258 = !DILocation(line: 503, column: 7, scope: !2256)
!2259 = !DILocation(line: 503, column: 14, scope: !2256)
!2260 = !DILocation(line: 503, column: 19, scope: !2256)
!2261 = !DILocation(line: 503, column: 23, scope: !2256)
!2262 = !DILocation(line: 504, column: 7, scope: !2250)
!2263 = !DILocation(line: 509, column: 25, scope: !2250)
!2264 = !DILocation(line: 509, column: 25, scope: !2252)
!2265 = !DILocation(line: 509, column: 25, scope: !2254)
!2266 = !DILocation(line: 509, column: 25, scope: !2256)
!2267 = !DILocation(line: 509, column: 11, scope: !2256)
!2268 = !DILocation(line: 509, column: 7, scope: !2256)
!2269 = !DILocation(line: 509, column: 14, scope: !2256)
!2270 = !DILocation(line: 509, column: 19, scope: !2256)
!2271 = !DILocation(line: 509, column: 23, scope: !2256)
!2272 = !DILocation(line: 510, column: 7, scope: !2250)
!2273 = !DILocation(line: 514, column: 15, scope: !2274)
!2274 = distinct !DILexicalBlock(scope: !2250, file: !1, line: 514, column: 10)
!2275 = !DILocation(line: 514, column: 11, scope: !2274)
!2276 = !DILocation(line: 514, column: 18, scope: !2274)
!2277 = !DILocation(line: 514, column: 24, scope: !2274)
!2278 = !DILocation(line: 514, column: 42, scope: !2274)
!2279 = !DILocation(line: 514, column: 50, scope: !2280)
!2280 = !DILexicalBlockFile(scope: !2274, file: !1, discriminator: 1)
!2281 = !DILocation(line: 514, column: 46, scope: !2280)
!2282 = !DILocation(line: 514, column: 53, scope: !2280)
!2283 = !DILocation(line: 514, column: 59, scope: !2280)
!2284 = !DILocation(line: 514, column: 10, scope: !2280)
!2285 = !DILocation(line: 516, column: 25, scope: !2274)
!2286 = !DILocation(line: 516, column: 25, scope: !2280)
!2287 = !DILocation(line: 516, column: 25, scope: !2288)
!2288 = !DILexicalBlockFile(scope: !2274, file: !1, discriminator: 2)
!2289 = !DILocation(line: 516, column: 25, scope: !2290)
!2290 = !DILexicalBlockFile(scope: !2274, file: !1, discriminator: 3)
!2291 = !DILocation(line: 515, column: 13, scope: !2274)
!2292 = !DILocation(line: 515, column: 9, scope: !2274)
!2293 = !DILocation(line: 515, column: 16, scope: !2274)
!2294 = !DILocation(line: 515, column: 21, scope: !2274)
!2295 = !DILocation(line: 515, column: 25, scope: !2274)
!2296 = !DILocation(line: 515, column: 37, scope: !2274)
!2297 = !DILocation(line: 517, column: 19, scope: !2298)
!2298 = distinct !DILexicalBlock(scope: !2274, file: !1, line: 517, column: 15)
!2299 = !DILocation(line: 517, column: 15, scope: !2298)
!2300 = !DILocation(line: 517, column: 22, scope: !2298)
!2301 = !DILocation(line: 517, column: 28, scope: !2298)
!2302 = !DILocation(line: 517, column: 15, scope: !2274)
!2303 = !DILocation(line: 519, column: 24, scope: !2298)
!2304 = !DILocation(line: 519, column: 24, scope: !2305)
!2305 = !DILexicalBlockFile(scope: !2298, file: !1, discriminator: 1)
!2306 = !DILocation(line: 519, column: 24, scope: !2307)
!2307 = !DILexicalBlockFile(scope: !2298, file: !1, discriminator: 2)
!2308 = !DILocation(line: 519, column: 24, scope: !2309)
!2309 = !DILexicalBlockFile(scope: !2298, file: !1, discriminator: 3)
!2310 = !DILocation(line: 518, column: 13, scope: !2298)
!2311 = !DILocation(line: 518, column: 9, scope: !2298)
!2312 = !DILocation(line: 518, column: 16, scope: !2298)
!2313 = !DILocation(line: 518, column: 21, scope: !2298)
!2314 = !DILocation(line: 518, column: 25, scope: !2298)
!2315 = !DILocation(line: 518, column: 35, scope: !2298)
!2316 = !DILocation(line: 523, column: 17, scope: !2317)
!2317 = distinct !DILexicalBlock(scope: !2318, file: !1, line: 523, column: 12)
!2318 = distinct !DILexicalBlock(scope: !2298, file: !1, line: 522, column: 7)
!2319 = !DILocation(line: 523, column: 13, scope: !2317)
!2320 = !DILocation(line: 523, column: 20, scope: !2317)
!2321 = !DILocation(line: 523, column: 26, scope: !2317)
!2322 = !DILocation(line: 523, column: 40, scope: !2317)
!2323 = !DILocation(line: 523, column: 48, scope: !2324)
!2324 = !DILexicalBlockFile(scope: !2317, file: !1, discriminator: 1)
!2325 = !DILocation(line: 523, column: 44, scope: !2324)
!2326 = !DILocation(line: 523, column: 51, scope: !2324)
!2327 = !DILocation(line: 523, column: 57, scope: !2324)
!2328 = !DILocation(line: 523, column: 12, scope: !2324)
!2329 = !DILocation(line: 525, column: 27, scope: !2317)
!2330 = !DILocation(line: 525, column: 27, scope: !2324)
!2331 = !DILocation(line: 525, column: 27, scope: !2332)
!2332 = !DILexicalBlockFile(scope: !2317, file: !1, discriminator: 2)
!2333 = !DILocation(line: 525, column: 27, scope: !2334)
!2334 = !DILexicalBlockFile(scope: !2317, file: !1, discriminator: 3)
!2335 = !DILocation(line: 524, column: 15, scope: !2317)
!2336 = !DILocation(line: 524, column: 11, scope: !2317)
!2337 = !DILocation(line: 524, column: 18, scope: !2317)
!2338 = !DILocation(line: 524, column: 23, scope: !2317)
!2339 = !DILocation(line: 524, column: 27, scope: !2317)
!2340 = !DILocation(line: 524, column: 39, scope: !2317)
!2341 = !DILocation(line: 526, column: 21, scope: !2342)
!2342 = distinct !DILexicalBlock(scope: !2317, file: !1, line: 526, column: 17)
!2343 = !DILocation(line: 526, column: 17, scope: !2342)
!2344 = !DILocation(line: 526, column: 24, scope: !2342)
!2345 = !DILocation(line: 526, column: 30, scope: !2342)
!2346 = !DILocation(line: 526, column: 17, scope: !2317)
!2347 = !DILocation(line: 528, column: 26, scope: !2342)
!2348 = !DILocation(line: 528, column: 26, scope: !2349)
!2349 = !DILexicalBlockFile(scope: !2342, file: !1, discriminator: 1)
!2350 = !DILocation(line: 528, column: 26, scope: !2351)
!2351 = !DILexicalBlockFile(scope: !2342, file: !1, discriminator: 2)
!2352 = !DILocation(line: 528, column: 26, scope: !2353)
!2353 = !DILexicalBlockFile(scope: !2342, file: !1, discriminator: 3)
!2354 = !DILocation(line: 527, column: 15, scope: !2342)
!2355 = !DILocation(line: 527, column: 11, scope: !2342)
!2356 = !DILocation(line: 527, column: 18, scope: !2342)
!2357 = !DILocation(line: 527, column: 23, scope: !2342)
!2358 = !DILocation(line: 527, column: 27, scope: !2342)
!2359 = !DILocation(line: 527, column: 37, scope: !2342)
!2360 = !DILocation(line: 529, column: 21, scope: !2361)
!2361 = distinct !DILexicalBlock(scope: !2342, file: !1, line: 529, column: 17)
!2362 = !DILocation(line: 529, column: 17, scope: !2361)
!2363 = !DILocation(line: 529, column: 24, scope: !2361)
!2364 = !DILocation(line: 529, column: 30, scope: !2361)
!2365 = !DILocation(line: 529, column: 17, scope: !2342)
!2366 = !DILocation(line: 531, column: 27, scope: !2361)
!2367 = !DILocation(line: 531, column: 27, scope: !2368)
!2368 = !DILexicalBlockFile(scope: !2361, file: !1, discriminator: 1)
!2369 = !DILocation(line: 531, column: 27, scope: !2370)
!2370 = !DILexicalBlockFile(scope: !2361, file: !1, discriminator: 2)
!2371 = !DILocation(line: 531, column: 27, scope: !2372)
!2372 = !DILexicalBlockFile(scope: !2361, file: !1, discriminator: 3)
!2373 = !DILocation(line: 531, column: 13, scope: !2372)
!2374 = !DILocation(line: 530, column: 15, scope: !2361)
!2375 = !DILocation(line: 530, column: 11, scope: !2361)
!2376 = !DILocation(line: 530, column: 18, scope: !2361)
!2377 = !DILocation(line: 530, column: 23, scope: !2361)
!2378 = !DILocation(line: 530, column: 27, scope: !2361)
!2379 = !DILocation(line: 530, column: 39, scope: !2361)
!2380 = !DILocation(line: 534, column: 26, scope: !2361)
!2381 = !DILocation(line: 534, column: 26, scope: !2368)
!2382 = !DILocation(line: 534, column: 26, scope: !2370)
!2383 = !DILocation(line: 534, column: 26, scope: !2372)
!2384 = !DILocation(line: 534, column: 13, scope: !2372)
!2385 = !DILocation(line: 533, column: 15, scope: !2361)
!2386 = !DILocation(line: 533, column: 11, scope: !2361)
!2387 = !DILocation(line: 533, column: 18, scope: !2361)
!2388 = !DILocation(line: 533, column: 23, scope: !2361)
!2389 = !DILocation(line: 533, column: 27, scope: !2361)
!2390 = !DILocation(line: 533, column: 37, scope: !2361)
!2391 = !DILocation(line: 536, column: 7, scope: !2250)
!2392 = !DILocation(line: 539, column: 26, scope: !2250)
!2393 = !DILocation(line: 539, column: 26, scope: !2252)
!2394 = !DILocation(line: 539, column: 26, scope: !2254)
!2395 = !DILocation(line: 539, column: 26, scope: !2256)
!2396 = !DILocation(line: 539, column: 11, scope: !2256)
!2397 = !DILocation(line: 539, column: 7, scope: !2256)
!2398 = !DILocation(line: 539, column: 14, scope: !2256)
!2399 = !DILocation(line: 539, column: 19, scope: !2256)
!2400 = !DILocation(line: 539, column: 24, scope: !2256)
!2401 = !DILocation(line: 540, column: 7, scope: !2250)
!2402 = !DILocation(line: 546, column: 11, scope: !2250)
!2403 = !DILocation(line: 546, column: 7, scope: !2250)
!2404 = !DILocation(line: 546, column: 14, scope: !2250)
!2405 = !DILocation(line: 546, column: 19, scope: !2250)
!2406 = !DILocation(line: 547, column: 7, scope: !2250)
!2407 = !DILocation(line: 550, column: 7, scope: !2250)
!2408 = !DILocation(line: 552, column: 3, scope: !2198)
!2409 = !DILocation(line: 489, column: 26, scope: !2410)
!2410 = !DILexicalBlockFile(scope: !2192, file: !1, discriminator: 2)
!2411 = !DILocation(line: 489, column: 3, scope: !2410)
!2412 = !DILocation(line: 554, column: 3, scope: !187)
!2413 = !DILocation(line: 556, column: 1, scope: !187)
!2414 = !DILocalVariable(name: "input", arg: 1, scope: !215, file: !1, line: 182, type: !54)
!2415 = !DILocation(line: 182, column: 40, scope: !215)
!2416 = !DILocalVariable(name: "end", arg: 2, scope: !215, file: !1, line: 182, type: !138)
!2417 = !DILocation(line: 182, column: 54, scope: !215)
!2418 = !DILocalVariable(name: "number", scope: !215, file: !1, line: 184, type: !64)
!2419 = !DILocation(line: 184, column: 7, scope: !215)
!2420 = !DILocation(line: 185, column: 3, scope: !215)
!2421 = !DILocation(line: 185, column: 9, scope: !2422)
!2422 = !DILexicalBlockFile(scope: !215, file: !1, discriminator: 1)
!2423 = !DILocation(line: 185, column: 3, scope: !2422)
!2424 = !DILocation(line: 186, column: 12, scope: !2425)
!2425 = distinct !DILexicalBlock(scope: !215, file: !1, line: 185, column: 26)
!2426 = !DILocation(line: 187, column: 16, scope: !2425)
!2427 = !DILocation(line: 187, column: 15, scope: !2425)
!2428 = !DILocation(line: 187, column: 21, scope: !2425)
!2429 = !DILocation(line: 187, column: 12, scope: !2425)
!2430 = !DILocation(line: 188, column: 10, scope: !2425)
!2431 = !DILocation(line: 185, column: 3, scope: !2432)
!2432 = !DILexicalBlockFile(scope: !215, file: !1, discriminator: 2)
!2433 = !DILocation(line: 190, column: 6, scope: !2434)
!2434 = distinct !DILexicalBlock(scope: !215, file: !1, line: 190, column: 6)
!2435 = !DILocation(line: 190, column: 13, scope: !2434)
!2436 = !DILocation(line: 190, column: 28, scope: !2437)
!2437 = !DILexicalBlockFile(scope: !2434, file: !1, discriminator: 1)
!2438 = !DILocation(line: 190, column: 22, scope: !2437)
!2439 = !DILocation(line: 190, column: 20, scope: !2437)
!2440 = !DILocation(line: 190, column: 6, scope: !2437)
!2441 = !DILocation(line: 191, column: 12, scope: !2442)
!2442 = distinct !DILexicalBlock(scope: !2434, file: !1, line: 190, column: 33)
!2443 = !DILocation(line: 191, column: 6, scope: !2442)
!2444 = !DILocation(line: 191, column: 10, scope: !2442)
!2445 = !DILocation(line: 192, column: 12, scope: !2442)
!2446 = !DILocation(line: 192, column: 5, scope: !2442)
!2447 = !DILocation(line: 194, column: 3, scope: !215)
!2448 = !DILocation(line: 195, column: 1, scope: !215)
!2449 = !DILocalVariable(name: "fmt", arg: 1, scope: !211, file: !1, line: 197, type: !143)
!2450 = !DILocation(line: 197, column: 53, scope: !211)
!2451 = !DILocation(line: 205, column: 11, scope: !211)
!2452 = !DILocation(line: 205, column: 10, scope: !211)
!2453 = !DILocation(line: 205, column: 3, scope: !211)
!2454 = !DILocation(line: 214, column: 5, scope: !2455)
!2455 = distinct !DILexicalBlock(scope: !211, file: !1, line: 205, column: 16)
!2456 = !DILocation(line: 217, column: 5, scope: !2455)
!2457 = !DILocation(line: 219, column: 1, scope: !211)
