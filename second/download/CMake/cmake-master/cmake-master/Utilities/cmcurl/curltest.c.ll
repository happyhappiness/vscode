; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmcurl/curltest.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [53 x i8] c"ftp://public.kitware.com/pub/cmake/cygwin/setup.hint\00", align 1
@.str.1 = private unnamed_addr constant [70 x i8] c"Error fetching: ftp://public.kitware.com/pub/cmake/cygwin/setup.hint\0A\00", align 1
@.str.2 = private unnamed_addr constant [27 x i8] c"Cannot create curl object\0A\00", align 1
@.str.3 = private unnamed_addr constant [11 x i8] c"HTTP_PROXY\00", align 1
@.str.4 = private unnamed_addr constant [16 x i8] c"HTTP_PROXY_PORT\00", align 1
@.str.5 = private unnamed_addr constant [6 x i8] c"%s:%s\00", align 1
@.str.6 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@.str.7 = private unnamed_addr constant [16 x i8] c"HTTP_PROXY_TYPE\00", align 1
@.str.8 = private unnamed_addr constant [5 x i8] c"HTTP\00", align 1
@.str.9 = private unnamed_addr constant [7 x i8] c"SOCKS4\00", align 1
@.str.10 = private unnamed_addr constant [7 x i8] c"SOCKS5\00", align 1
@.str.11 = private unnamed_addr constant [20 x i8] c"Error fetching: %s\0A\00", align 1
@.str.12 = private unnamed_addr constant [51 x i8] c"error: first argument should be a url to download\0A\00", align 1

; Function Attrs: nounwind uwtable
define i32 @GetFtpFile() #0 !dbg !360 {
entry:
  %retVal = alloca i32, align 4
  %curl = alloca i8*, align 8
  %res = alloca i32, align 4
  call void @llvm.dbg.declare(metadata i32* %retVal, metadata !377, metadata !378), !dbg !379
  store i32 0, i32* %retVal, align 4, !dbg !379
  call void @llvm.dbg.declare(metadata i8** %curl, metadata !380, metadata !378), !dbg !383
  call void @llvm.dbg.declare(metadata i32* %res, metadata !384, metadata !378), !dbg !386
  %call = call i8* @curl_easy_init(), !dbg !387
  store i8* %call, i8** %curl, align 8, !dbg !388
  %0 = load i8*, i8** %curl, align 8, !dbg !389
  %tobool = icmp ne i8* %0, null, !dbg !389
  br i1 %tobool, label %if.then, label %if.else, !dbg !391

if.then:                                          ; preds = %entry
  %1 = load i8*, i8** %curl, align 8, !dbg !392
  %call1 = call i32 (i8*, i32, ...) @curl_easy_setopt(i8* %1, i32 41, i32 1), !dbg !394
  %2 = load i8*, i8** %curl, align 8, !dbg !395
  %call2 = call i32 (i8*, i32, ...) @curl_easy_setopt(i8* %2, i32 42, i32 1), !dbg !396
  %3 = load i8*, i8** %curl, align 8, !dbg !397
  %call3 = call i32 (i8*, i32, ...) @curl_easy_setopt(i8* %3, i32 10002, i8* getelementptr inbounds ([53 x i8], [53 x i8]* @.str, i32 0, i32 0)), !dbg !398
  %4 = load i8*, i8** %curl, align 8, !dbg !399
  %call4 = call i32 @curl_easy_perform(i8* %4), !dbg !400
  store i32 %call4, i32* %res, align 4, !dbg !401
  %5 = load i32, i32* %res, align 4, !dbg !402
  %cmp = icmp ne i32 %5, 0, !dbg !404
  br i1 %cmp, label %if.then5, label %if.end, !dbg !405

if.then5:                                         ; preds = %if.then
  %call6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.1, i32 0, i32 0)), !dbg !406
  store i32 1, i32* %retVal, align 4, !dbg !408
  br label %if.end, !dbg !409

if.end:                                           ; preds = %if.then5, %if.then
  %6 = load i8*, i8** %curl, align 8, !dbg !410
  call void @curl_easy_cleanup(i8* %6), !dbg !411
  br label %if.end8, !dbg !412

if.else:                                          ; preds = %entry
  %call7 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.2, i32 0, i32 0)), !dbg !413
  store i32 1, i32* %retVal, align 4, !dbg !415
  br label %if.end8

if.end8:                                          ; preds = %if.else, %if.end
  %7 = load i32, i32* %retVal, align 4, !dbg !416
  ret i32 %7, !dbg !417
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i8* @curl_easy_init() #2

declare i32 @curl_easy_setopt(i8*, i32, ...) #2

declare i32 @curl_easy_perform(i8*) #2

declare i32 @printf(i8*, ...) #2

declare void @curl_easy_cleanup(i8*) #2

; Function Attrs: nounwind uwtable
define i32 @GetWebFiles(i8* %url1, i8* %url2) #0 !dbg !365 {
entry:
  %url1.addr = alloca i8*, align 8
  %url2.addr = alloca i8*, align 8
  %retVal = alloca i32, align 4
  %curl = alloca i8*, align 8
  %res = alloca i32, align 4
  %proxy = alloca [1024 x i8], align 16
  %proxy_type = alloca i32, align 4
  store i8* %url1, i8** %url1.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %url1.addr, metadata !418, metadata !378), !dbg !419
  store i8* %url2, i8** %url2.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %url2.addr, metadata !420, metadata !378), !dbg !421
  call void @llvm.dbg.declare(metadata i32* %retVal, metadata !422, metadata !378), !dbg !423
  store i32 0, i32* %retVal, align 4, !dbg !423
  call void @llvm.dbg.declare(metadata i8** %curl, metadata !424, metadata !378), !dbg !425
  call void @llvm.dbg.declare(metadata i32* %res, metadata !426, metadata !378), !dbg !427
  call void @llvm.dbg.declare(metadata [1024 x i8]* %proxy, metadata !428, metadata !378), !dbg !432
  call void @llvm.dbg.declare(metadata i32* %proxy_type, metadata !433, metadata !378), !dbg !434
  store i32 0, i32* %proxy_type, align 4, !dbg !434
  %call = call i8* @getenv(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.3, i32 0, i32 0)) #5, !dbg !435
  %tobool = icmp ne i8* %call, null, !dbg !435
  br i1 %tobool, label %if.then, label %if.end30, !dbg !437

if.then:                                          ; preds = %entry
  store i32 1, i32* %proxy_type, align 4, !dbg !438
  %call1 = call i8* @getenv(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.4, i32 0, i32 0)) #5, !dbg !440
  %tobool2 = icmp ne i8* %call1, null, !dbg !440
  br i1 %tobool2, label %if.then3, label %if.else, !dbg !442

if.then3:                                         ; preds = %if.then
  %arraydecay = getelementptr inbounds [1024 x i8], [1024 x i8]* %proxy, i32 0, i32 0, !dbg !443
  %call4 = call i8* @getenv(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.3, i32 0, i32 0)) #5, !dbg !445
  %call5 = call i8* @getenv(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.4, i32 0, i32 0)) #5, !dbg !446
  %call6 = call i32 (i8*, i8*, ...) @sprintf(i8* %arraydecay, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.5, i32 0, i32 0), i8* %call4, i8* %call5) #5, !dbg !448
  br label %if.end, !dbg !450

if.else:                                          ; preds = %if.then
  %arraydecay7 = getelementptr inbounds [1024 x i8], [1024 x i8]* %proxy, i32 0, i32 0, !dbg !451
  %call8 = call i8* @getenv(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.3, i32 0, i32 0)) #5, !dbg !453
  %call9 = call i32 (i8*, i8*, ...) @sprintf(i8* %arraydecay7, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.6, i32 0, i32 0), i8* %call8) #5, !dbg !454
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then3
  %call10 = call i8* @getenv(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.7, i32 0, i32 0)) #5, !dbg !456
  %tobool11 = icmp ne i8* %call10, null, !dbg !456
  br i1 %tobool11, label %if.then12, label %if.end29, !dbg !458

if.then12:                                        ; preds = %if.end
  %call13 = call i8* @getenv(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.7, i32 0, i32 0)) #5, !dbg !459
  %call14 = call i32 @strcmp(i8* %call13, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.8, i32 0, i32 0)) #6, !dbg !462
  %cmp = icmp eq i32 %call14, 0, !dbg !464
  br i1 %cmp, label %if.then15, label %if.else16, !dbg !465

if.then15:                                        ; preds = %if.then12
  store i32 1, i32* %proxy_type, align 4, !dbg !466
  br label %if.end28, !dbg !468

if.else16:                                        ; preds = %if.then12
  %call17 = call i8* @getenv(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.7, i32 0, i32 0)) #5, !dbg !469
  %call18 = call i32 @strcmp(i8* %call17, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.9, i32 0, i32 0)) #6, !dbg !471
  %cmp19 = icmp eq i32 %call18, 0, !dbg !473
  br i1 %cmp19, label %if.then20, label %if.else21, !dbg !474

if.then20:                                        ; preds = %if.else16
  store i32 2, i32* %proxy_type, align 4, !dbg !475
  br label %if.end27, !dbg !477

if.else21:                                        ; preds = %if.else16
  %call22 = call i8* @getenv(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.7, i32 0, i32 0)) #5, !dbg !478
  %call23 = call i32 @strcmp(i8* %call22, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.10, i32 0, i32 0)) #6, !dbg !480
  %cmp24 = icmp eq i32 %call23, 0, !dbg !482
  br i1 %cmp24, label %if.then25, label %if.end26, !dbg !483

if.then25:                                        ; preds = %if.else21
  store i32 3, i32* %proxy_type, align 4, !dbg !484
  br label %if.end26, !dbg !486

if.end26:                                         ; preds = %if.then25, %if.else21
  br label %if.end27

if.end27:                                         ; preds = %if.end26, %if.then20
  br label %if.end28

if.end28:                                         ; preds = %if.end27, %if.then15
  br label %if.end29, !dbg !487

if.end29:                                         ; preds = %if.end28, %if.end
  br label %if.end30, !dbg !488

if.end30:                                         ; preds = %if.end29, %entry
  %call31 = call i8* @curl_easy_init(), !dbg !489
  store i8* %call31, i8** %curl, align 8, !dbg !490
  %0 = load i8*, i8** %curl, align 8, !dbg !491
  %tobool32 = icmp ne i8* %0, null, !dbg !491
  br i1 %tobool32, label %if.then33, label %if.else51, !dbg !493

if.then33:                                        ; preds = %if.end30
  %1 = load i8*, i8** %curl, align 8, !dbg !494
  %call34 = call i32 (i8*, i32, ...) @curl_easy_setopt(i8* %1, i32 41, i32 1), !dbg !496
  %2 = load i8*, i8** %curl, align 8, !dbg !497
  %call35 = call i32 (i8*, i32, ...) @curl_easy_setopt(i8* %2, i32 42, i32 1), !dbg !498
  %3 = load i32, i32* %proxy_type, align 4, !dbg !499
  %cmp36 = icmp sgt i32 %3, 0, !dbg !501
  br i1 %cmp36, label %if.then37, label %if.end44, !dbg !502

if.then37:                                        ; preds = %if.then33
  %4 = load i8*, i8** %curl, align 8, !dbg !503
  %arraydecay38 = getelementptr inbounds [1024 x i8], [1024 x i8]* %proxy, i32 0, i32 0, !dbg !505
  %call39 = call i32 (i8*, i32, ...) @curl_easy_setopt(i8* %4, i32 10004, i8* %arraydecay38), !dbg !506
  %5 = load i32, i32* %proxy_type, align 4, !dbg !507
  switch i32 %5, label %sw.default [
    i32 2, label %sw.bb
    i32 3, label %sw.bb41
  ], !dbg !508

sw.bb:                                            ; preds = %if.then37
  %6 = load i8*, i8** %curl, align 8, !dbg !509
  %call40 = call i32 (i8*, i32, ...) @curl_easy_setopt(i8* %6, i32 101, i32 4), !dbg !511
  br label %sw.epilog, !dbg !512

sw.bb41:                                          ; preds = %if.then37
  %7 = load i8*, i8** %curl, align 8, !dbg !513
  %call42 = call i32 (i8*, i32, ...) @curl_easy_setopt(i8* %7, i32 101, i32 5), !dbg !514
  br label %sw.epilog, !dbg !515

sw.default:                                       ; preds = %if.then37
  %8 = load i8*, i8** %curl, align 8, !dbg !516
  %call43 = call i32 (i8*, i32, ...) @curl_easy_setopt(i8* %8, i32 101, i32 0), !dbg !517
  br label %sw.epilog, !dbg !518

sw.epilog:                                        ; preds = %sw.default, %sw.bb41, %sw.bb
  br label %if.end44, !dbg !519

if.end44:                                         ; preds = %sw.epilog, %if.then33
  %9 = load i8*, i8** %curl, align 8, !dbg !520
  %10 = load i8*, i8** %url1.addr, align 8, !dbg !521
  %call45 = call i32 (i8*, i32, ...) @curl_easy_setopt(i8* %9, i32 10002, i8* %10), !dbg !522
  %11 = load i8*, i8** %curl, align 8, !dbg !523
  %call46 = call i32 @curl_easy_perform(i8* %11), !dbg !524
  store i32 %call46, i32* %res, align 4, !dbg !525
  %12 = load i32, i32* %res, align 4, !dbg !526
  %cmp47 = icmp ne i32 %12, 0, !dbg !528
  br i1 %cmp47, label %if.then48, label %if.end50, !dbg !529

if.then48:                                        ; preds = %if.end44
  %13 = load i8*, i8** %url1.addr, align 8, !dbg !530
  %call49 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.11, i32 0, i32 0), i8* %13), !dbg !532
  store i32 1, i32* %retVal, align 4, !dbg !533
  br label %if.end50, !dbg !534

if.end50:                                         ; preds = %if.then48, %if.end44
  %14 = load i8*, i8** %url2.addr, align 8, !dbg !535
  %15 = load i8*, i8** %curl, align 8, !dbg !536
  call void @curl_easy_cleanup(i8* %15), !dbg !537
  br label %if.end53, !dbg !538

if.else51:                                        ; preds = %if.end30
  %call52 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.2, i32 0, i32 0)), !dbg !539
  store i32 1, i32* %retVal, align 4, !dbg !541
  br label %if.end53

if.end53:                                         ; preds = %if.else51, %if.end50
  %16 = load i32, i32* %retVal, align 4, !dbg !542
  ret i32 %16, !dbg !543
}

; Function Attrs: nounwind
declare i8* @getenv(i8*) #3

; Function Attrs: nounwind
declare i32 @sprintf(i8*, i8*, ...) #3

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #4

; Function Attrs: nounwind uwtable
define i32 @main(i32 %argc, i8** %argv) #0 !dbg !370 {
entry:
  %retval = alloca i32, align 4
  %argc.addr = alloca i32, align 4
  %argv.addr = alloca i8**, align 8
  %retVal = alloca i32, align 4
  store i32 0, i32* %retval, align 4
  store i32 %argc, i32* %argc.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %argc.addr, metadata !544, metadata !378), !dbg !545
  store i8** %argv, i8*** %argv.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %argv.addr, metadata !546, metadata !378), !dbg !547
  call void @llvm.dbg.declare(metadata i32* %retVal, metadata !548, metadata !378), !dbg !549
  store i32 0, i32* %retVal, align 4, !dbg !549
  %call = call i32 @curl_global_init(i64 3), !dbg !550
  %0 = load i32, i32* %argc.addr, align 4, !dbg !551
  %cmp = icmp sgt i32 %0, 1, !dbg !553
  br i1 %cmp, label %if.then, label %if.else, !dbg !554

if.then:                                          ; preds = %entry
  %1 = load i8**, i8*** %argv.addr, align 8, !dbg !555
  %arrayidx = getelementptr inbounds i8*, i8** %1, i64 1, !dbg !555
  %2 = load i8*, i8** %arrayidx, align 8, !dbg !555
  %call1 = call i32 @GetWebFiles(i8* %2, i8* null), !dbg !557
  %3 = load i32, i32* %retVal, align 4, !dbg !558
  %add = add nsw i32 %3, %call1, !dbg !558
  store i32 %add, i32* %retVal, align 4, !dbg !558
  br label %if.end, !dbg !559

if.else:                                          ; preds = %entry
  %call2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([51 x i8], [51 x i8]* @.str.12, i32 0, i32 0)), !dbg !560
  store i32 1, i32* %retVal, align 4, !dbg !562
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  call void @curl_global_cleanup(), !dbg !563
  %4 = load i32, i32* %retVal, align 4, !dbg !564
  ret i32 %4, !dbg !565
}

declare i32 @curl_global_init(i64) #2

declare void @curl_global_cleanup() #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind }
attributes #6 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!374, !375}
!llvm.ident = !{!376}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !359)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/curltest.c", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl")
!2 = !{!3, !100, !350}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 434, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/include/curl/curl.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl")
!5 = !{!6, !7, !8, !9, !10, !11, !12, !13, !14, !15, !16, !17, !18, !19, !20, !21, !22, !23, !24, !25, !26, !27, !28, !29, !30, !31, !32, !33, !34, !35, !36, !37, !38, !39, !40, !41, !42, !43, !44, !45, !46, !47, !48, !49, !50, !51, !52, !53, !54, !55, !56, !57, !58, !59, !60, !61, !62, !63, !64, !65, !66, !67, !68, !69, !70, !71, !72, !73, !74, !75, !76, !77, !78, !79, !80, !81, !82, !83, !84, !85, !86, !87, !88, !89, !90, !91, !92, !93, !94, !95, !96, !97, !98, !99}
!6 = !DIEnumerator(name: "CURLE_OK", value: 0)
!7 = !DIEnumerator(name: "CURLE_UNSUPPORTED_PROTOCOL", value: 1)
!8 = !DIEnumerator(name: "CURLE_FAILED_INIT", value: 2)
!9 = !DIEnumerator(name: "CURLE_URL_MALFORMAT", value: 3)
!10 = !DIEnumerator(name: "CURLE_NOT_BUILT_IN", value: 4)
!11 = !DIEnumerator(name: "CURLE_COULDNT_RESOLVE_PROXY", value: 5)
!12 = !DIEnumerator(name: "CURLE_COULDNT_RESOLVE_HOST", value: 6)
!13 = !DIEnumerator(name: "CURLE_COULDNT_CONNECT", value: 7)
!14 = !DIEnumerator(name: "CURLE_WEIRD_SERVER_REPLY", value: 8)
!15 = !DIEnumerator(name: "CURLE_REMOTE_ACCESS_DENIED", value: 9)
!16 = !DIEnumerator(name: "CURLE_FTP_ACCEPT_FAILED", value: 10)
!17 = !DIEnumerator(name: "CURLE_FTP_WEIRD_PASS_REPLY", value: 11)
!18 = !DIEnumerator(name: "CURLE_FTP_ACCEPT_TIMEOUT", value: 12)
!19 = !DIEnumerator(name: "CURLE_FTP_WEIRD_PASV_REPLY", value: 13)
!20 = !DIEnumerator(name: "CURLE_FTP_WEIRD_227_FORMAT", value: 14)
!21 = !DIEnumerator(name: "CURLE_FTP_CANT_GET_HOST", value: 15)
!22 = !DIEnumerator(name: "CURLE_HTTP2", value: 16)
!23 = !DIEnumerator(name: "CURLE_FTP_COULDNT_SET_TYPE", value: 17)
!24 = !DIEnumerator(name: "CURLE_PARTIAL_FILE", value: 18)
!25 = !DIEnumerator(name: "CURLE_FTP_COULDNT_RETR_FILE", value: 19)
!26 = !DIEnumerator(name: "CURLE_OBSOLETE20", value: 20)
!27 = !DIEnumerator(name: "CURLE_QUOTE_ERROR", value: 21)
!28 = !DIEnumerator(name: "CURLE_HTTP_RETURNED_ERROR", value: 22)
!29 = !DIEnumerator(name: "CURLE_WRITE_ERROR", value: 23)
!30 = !DIEnumerator(name: "CURLE_OBSOLETE24", value: 24)
!31 = !DIEnumerator(name: "CURLE_UPLOAD_FAILED", value: 25)
!32 = !DIEnumerator(name: "CURLE_READ_ERROR", value: 26)
!33 = !DIEnumerator(name: "CURLE_OUT_OF_MEMORY", value: 27)
!34 = !DIEnumerator(name: "CURLE_OPERATION_TIMEDOUT", value: 28)
!35 = !DIEnumerator(name: "CURLE_OBSOLETE29", value: 29)
!36 = !DIEnumerator(name: "CURLE_FTP_PORT_FAILED", value: 30)
!37 = !DIEnumerator(name: "CURLE_FTP_COULDNT_USE_REST", value: 31)
!38 = !DIEnumerator(name: "CURLE_OBSOLETE32", value: 32)
!39 = !DIEnumerator(name: "CURLE_RANGE_ERROR", value: 33)
!40 = !DIEnumerator(name: "CURLE_HTTP_POST_ERROR", value: 34)
!41 = !DIEnumerator(name: "CURLE_SSL_CONNECT_ERROR", value: 35)
!42 = !DIEnumerator(name: "CURLE_BAD_DOWNLOAD_RESUME", value: 36)
!43 = !DIEnumerator(name: "CURLE_FILE_COULDNT_READ_FILE", value: 37)
!44 = !DIEnumerator(name: "CURLE_LDAP_CANNOT_BIND", value: 38)
!45 = !DIEnumerator(name: "CURLE_LDAP_SEARCH_FAILED", value: 39)
!46 = !DIEnumerator(name: "CURLE_OBSOLETE40", value: 40)
!47 = !DIEnumerator(name: "CURLE_FUNCTION_NOT_FOUND", value: 41)
!48 = !DIEnumerator(name: "CURLE_ABORTED_BY_CALLBACK", value: 42)
!49 = !DIEnumerator(name: "CURLE_BAD_FUNCTION_ARGUMENT", value: 43)
!50 = !DIEnumerator(name: "CURLE_OBSOLETE44", value: 44)
!51 = !DIEnumerator(name: "CURLE_INTERFACE_FAILED", value: 45)
!52 = !DIEnumerator(name: "CURLE_OBSOLETE46", value: 46)
!53 = !DIEnumerator(name: "CURLE_TOO_MANY_REDIRECTS", value: 47)
!54 = !DIEnumerator(name: "CURLE_UNKNOWN_OPTION", value: 48)
!55 = !DIEnumerator(name: "CURLE_TELNET_OPTION_SYNTAX", value: 49)
!56 = !DIEnumerator(name: "CURLE_OBSOLETE50", value: 50)
!57 = !DIEnumerator(name: "CURLE_PEER_FAILED_VERIFICATION", value: 51)
!58 = !DIEnumerator(name: "CURLE_GOT_NOTHING", value: 52)
!59 = !DIEnumerator(name: "CURLE_SSL_ENGINE_NOTFOUND", value: 53)
!60 = !DIEnumerator(name: "CURLE_SSL_ENGINE_SETFAILED", value: 54)
!61 = !DIEnumerator(name: "CURLE_SEND_ERROR", value: 55)
!62 = !DIEnumerator(name: "CURLE_RECV_ERROR", value: 56)
!63 = !DIEnumerator(name: "CURLE_OBSOLETE57", value: 57)
!64 = !DIEnumerator(name: "CURLE_SSL_CERTPROBLEM", value: 58)
!65 = !DIEnumerator(name: "CURLE_SSL_CIPHER", value: 59)
!66 = !DIEnumerator(name: "CURLE_SSL_CACERT", value: 60)
!67 = !DIEnumerator(name: "CURLE_BAD_CONTENT_ENCODING", value: 61)
!68 = !DIEnumerator(name: "CURLE_LDAP_INVALID_URL", value: 62)
!69 = !DIEnumerator(name: "CURLE_FILESIZE_EXCEEDED", value: 63)
!70 = !DIEnumerator(name: "CURLE_USE_SSL_FAILED", value: 64)
!71 = !DIEnumerator(name: "CURLE_SEND_FAIL_REWIND", value: 65)
!72 = !DIEnumerator(name: "CURLE_SSL_ENGINE_INITFAILED", value: 66)
!73 = !DIEnumerator(name: "CURLE_LOGIN_DENIED", value: 67)
!74 = !DIEnumerator(name: "CURLE_TFTP_NOTFOUND", value: 68)
!75 = !DIEnumerator(name: "CURLE_TFTP_PERM", value: 69)
!76 = !DIEnumerator(name: "CURLE_REMOTE_DISK_FULL", value: 70)
!77 = !DIEnumerator(name: "CURLE_TFTP_ILLEGAL", value: 71)
!78 = !DIEnumerator(name: "CURLE_TFTP_UNKNOWNID", value: 72)
!79 = !DIEnumerator(name: "CURLE_REMOTE_FILE_EXISTS", value: 73)
!80 = !DIEnumerator(name: "CURLE_TFTP_NOSUCHUSER", value: 74)
!81 = !DIEnumerator(name: "CURLE_CONV_FAILED", value: 75)
!82 = !DIEnumerator(name: "CURLE_CONV_REQD", value: 76)
!83 = !DIEnumerator(name: "CURLE_SSL_CACERT_BADFILE", value: 77)
!84 = !DIEnumerator(name: "CURLE_REMOTE_FILE_NOT_FOUND", value: 78)
!85 = !DIEnumerator(name: "CURLE_SSH", value: 79)
!86 = !DIEnumerator(name: "CURLE_SSL_SHUTDOWN_FAILED", value: 80)
!87 = !DIEnumerator(name: "CURLE_AGAIN", value: 81)
!88 = !DIEnumerator(name: "CURLE_SSL_CRL_BADFILE", value: 82)
!89 = !DIEnumerator(name: "CURLE_SSL_ISSUER_ERROR", value: 83)
!90 = !DIEnumerator(name: "CURLE_FTP_PRET_FAILED", value: 84)
!91 = !DIEnumerator(name: "CURLE_RTSP_CSEQ_ERROR", value: 85)
!92 = !DIEnumerator(name: "CURLE_RTSP_SESSION_ERROR", value: 86)
!93 = !DIEnumerator(name: "CURLE_FTP_BAD_FILE_LIST", value: 87)
!94 = !DIEnumerator(name: "CURLE_CHUNK_FAILED", value: 88)
!95 = !DIEnumerator(name: "CURLE_NO_CONNECTION_AVAILABLE", value: 89)
!96 = !DIEnumerator(name: "CURLE_SSL_PINNEDPUBKEYNOTMATCH", value: 90)
!97 = !DIEnumerator(name: "CURLE_SSL_INVALIDCERTSTATUS", value: 91)
!98 = !DIEnumerator(name: "CURLE_HTTP2_STREAM", value: 92)
!99 = !DIEnumerator(name: "CURL_LAST", value: 93)
!100 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 888, size: 32, align: 32, elements: !101)
!101 = !{!102, !103, !104, !105, !106, !107, !108, !109, !110, !111, !112, !113, !114, !115, !116, !117, !118, !119, !120, !121, !122, !123, !124, !125, !126, !127, !128, !129, !130, !131, !132, !133, !134, !135, !136, !137, !138, !139, !140, !141, !142, !143, !144, !145, !146, !147, !148, !149, !150, !151, !152, !153, !154, !155, !156, !157, !158, !159, !160, !161, !162, !163, !164, !165, !166, !167, !168, !169, !170, !171, !172, !173, !174, !175, !176, !177, !178, !179, !180, !181, !182, !183, !184, !185, !186, !187, !188, !189, !190, !191, !192, !193, !194, !195, !196, !197, !198, !199, !200, !201, !202, !203, !204, !205, !206, !207, !208, !209, !210, !211, !212, !213, !214, !215, !216, !217, !218, !219, !220, !221, !222, !223, !224, !225, !226, !227, !228, !229, !230, !231, !232, !233, !234, !235, !236, !237, !238, !239, !240, !241, !242, !243, !244, !245, !246, !247, !248, !249, !250, !251, !252, !253, !254, !255, !256, !257, !258, !259, !260, !261, !262, !263, !264, !265, !266, !267, !268, !269, !270, !271, !272, !273, !274, !275, !276, !277, !278, !279, !280, !281, !282, !283, !284, !285, !286, !287, !288, !289, !290, !291, !292, !293, !294, !295, !296, !297, !298, !299, !300, !301, !302, !303, !304, !305, !306, !307, !308, !309, !310, !311, !312, !313, !314, !315, !316, !317, !318, !319, !320, !321, !322, !323, !324, !325, !326, !327, !328, !329, !330, !331, !332, !333, !334, !335, !336, !337, !338, !339, !340, !341, !342, !343, !344, !345, !346, !347, !348, !349}
!102 = !DIEnumerator(name: "CURLOPT_WRITEDATA", value: 10001)
!103 = !DIEnumerator(name: "CURLOPT_URL", value: 10002)
!104 = !DIEnumerator(name: "CURLOPT_PORT", value: 3)
!105 = !DIEnumerator(name: "CURLOPT_PROXY", value: 10004)
!106 = !DIEnumerator(name: "CURLOPT_USERPWD", value: 10005)
!107 = !DIEnumerator(name: "CURLOPT_PROXYUSERPWD", value: 10006)
!108 = !DIEnumerator(name: "CURLOPT_RANGE", value: 10007)
!109 = !DIEnumerator(name: "CURLOPT_READDATA", value: 10009)
!110 = !DIEnumerator(name: "CURLOPT_ERRORBUFFER", value: 10010)
!111 = !DIEnumerator(name: "CURLOPT_WRITEFUNCTION", value: 20011)
!112 = !DIEnumerator(name: "CURLOPT_READFUNCTION", value: 20012)
!113 = !DIEnumerator(name: "CURLOPT_TIMEOUT", value: 13)
!114 = !DIEnumerator(name: "CURLOPT_INFILESIZE", value: 14)
!115 = !DIEnumerator(name: "CURLOPT_POSTFIELDS", value: 10015)
!116 = !DIEnumerator(name: "CURLOPT_REFERER", value: 10016)
!117 = !DIEnumerator(name: "CURLOPT_FTPPORT", value: 10017)
!118 = !DIEnumerator(name: "CURLOPT_USERAGENT", value: 10018)
!119 = !DIEnumerator(name: "CURLOPT_LOW_SPEED_LIMIT", value: 19)
!120 = !DIEnumerator(name: "CURLOPT_LOW_SPEED_TIME", value: 20)
!121 = !DIEnumerator(name: "CURLOPT_RESUME_FROM", value: 21)
!122 = !DIEnumerator(name: "CURLOPT_COOKIE", value: 10022)
!123 = !DIEnumerator(name: "CURLOPT_HTTPHEADER", value: 10023)
!124 = !DIEnumerator(name: "CURLOPT_HTTPPOST", value: 10024)
!125 = !DIEnumerator(name: "CURLOPT_SSLCERT", value: 10025)
!126 = !DIEnumerator(name: "CURLOPT_KEYPASSWD", value: 10026)
!127 = !DIEnumerator(name: "CURLOPT_CRLF", value: 27)
!128 = !DIEnumerator(name: "CURLOPT_QUOTE", value: 10028)
!129 = !DIEnumerator(name: "CURLOPT_HEADERDATA", value: 10029)
!130 = !DIEnumerator(name: "CURLOPT_COOKIEFILE", value: 10031)
!131 = !DIEnumerator(name: "CURLOPT_SSLVERSION", value: 32)
!132 = !DIEnumerator(name: "CURLOPT_TIMECONDITION", value: 33)
!133 = !DIEnumerator(name: "CURLOPT_TIMEVALUE", value: 34)
!134 = !DIEnumerator(name: "CURLOPT_CUSTOMREQUEST", value: 10036)
!135 = !DIEnumerator(name: "CURLOPT_STDERR", value: 10037)
!136 = !DIEnumerator(name: "CURLOPT_POSTQUOTE", value: 10039)
!137 = !DIEnumerator(name: "CURLOPT_OBSOLETE40", value: 10040)
!138 = !DIEnumerator(name: "CURLOPT_VERBOSE", value: 41)
!139 = !DIEnumerator(name: "CURLOPT_HEADER", value: 42)
!140 = !DIEnumerator(name: "CURLOPT_NOPROGRESS", value: 43)
!141 = !DIEnumerator(name: "CURLOPT_NOBODY", value: 44)
!142 = !DIEnumerator(name: "CURLOPT_FAILONERROR", value: 45)
!143 = !DIEnumerator(name: "CURLOPT_UPLOAD", value: 46)
!144 = !DIEnumerator(name: "CURLOPT_POST", value: 47)
!145 = !DIEnumerator(name: "CURLOPT_DIRLISTONLY", value: 48)
!146 = !DIEnumerator(name: "CURLOPT_APPEND", value: 50)
!147 = !DIEnumerator(name: "CURLOPT_NETRC", value: 51)
!148 = !DIEnumerator(name: "CURLOPT_FOLLOWLOCATION", value: 52)
!149 = !DIEnumerator(name: "CURLOPT_TRANSFERTEXT", value: 53)
!150 = !DIEnumerator(name: "CURLOPT_PUT", value: 54)
!151 = !DIEnumerator(name: "CURLOPT_PROGRESSFUNCTION", value: 20056)
!152 = !DIEnumerator(name: "CURLOPT_PROGRESSDATA", value: 10057)
!153 = !DIEnumerator(name: "CURLOPT_AUTOREFERER", value: 58)
!154 = !DIEnumerator(name: "CURLOPT_PROXYPORT", value: 59)
!155 = !DIEnumerator(name: "CURLOPT_POSTFIELDSIZE", value: 60)
!156 = !DIEnumerator(name: "CURLOPT_HTTPPROXYTUNNEL", value: 61)
!157 = !DIEnumerator(name: "CURLOPT_INTERFACE", value: 10062)
!158 = !DIEnumerator(name: "CURLOPT_KRBLEVEL", value: 10063)
!159 = !DIEnumerator(name: "CURLOPT_SSL_VERIFYPEER", value: 64)
!160 = !DIEnumerator(name: "CURLOPT_CAINFO", value: 10065)
!161 = !DIEnumerator(name: "CURLOPT_MAXREDIRS", value: 68)
!162 = !DIEnumerator(name: "CURLOPT_FILETIME", value: 69)
!163 = !DIEnumerator(name: "CURLOPT_TELNETOPTIONS", value: 10070)
!164 = !DIEnumerator(name: "CURLOPT_MAXCONNECTS", value: 71)
!165 = !DIEnumerator(name: "CURLOPT_OBSOLETE72", value: 72)
!166 = !DIEnumerator(name: "CURLOPT_FRESH_CONNECT", value: 74)
!167 = !DIEnumerator(name: "CURLOPT_FORBID_REUSE", value: 75)
!168 = !DIEnumerator(name: "CURLOPT_RANDOM_FILE", value: 10076)
!169 = !DIEnumerator(name: "CURLOPT_EGDSOCKET", value: 10077)
!170 = !DIEnumerator(name: "CURLOPT_CONNECTTIMEOUT", value: 78)
!171 = !DIEnumerator(name: "CURLOPT_HEADERFUNCTION", value: 20079)
!172 = !DIEnumerator(name: "CURLOPT_HTTPGET", value: 80)
!173 = !DIEnumerator(name: "CURLOPT_SSL_VERIFYHOST", value: 81)
!174 = !DIEnumerator(name: "CURLOPT_COOKIEJAR", value: 10082)
!175 = !DIEnumerator(name: "CURLOPT_SSL_CIPHER_LIST", value: 10083)
!176 = !DIEnumerator(name: "CURLOPT_HTTP_VERSION", value: 84)
!177 = !DIEnumerator(name: "CURLOPT_FTP_USE_EPSV", value: 85)
!178 = !DIEnumerator(name: "CURLOPT_SSLCERTTYPE", value: 10086)
!179 = !DIEnumerator(name: "CURLOPT_SSLKEY", value: 10087)
!180 = !DIEnumerator(name: "CURLOPT_SSLKEYTYPE", value: 10088)
!181 = !DIEnumerator(name: "CURLOPT_SSLENGINE", value: 10089)
!182 = !DIEnumerator(name: "CURLOPT_SSLENGINE_DEFAULT", value: 90)
!183 = !DIEnumerator(name: "CURLOPT_DNS_USE_GLOBAL_CACHE", value: 91)
!184 = !DIEnumerator(name: "CURLOPT_DNS_CACHE_TIMEOUT", value: 92)
!185 = !DIEnumerator(name: "CURLOPT_PREQUOTE", value: 10093)
!186 = !DIEnumerator(name: "CURLOPT_DEBUGFUNCTION", value: 20094)
!187 = !DIEnumerator(name: "CURLOPT_DEBUGDATA", value: 10095)
!188 = !DIEnumerator(name: "CURLOPT_COOKIESESSION", value: 96)
!189 = !DIEnumerator(name: "CURLOPT_CAPATH", value: 10097)
!190 = !DIEnumerator(name: "CURLOPT_BUFFERSIZE", value: 98)
!191 = !DIEnumerator(name: "CURLOPT_NOSIGNAL", value: 99)
!192 = !DIEnumerator(name: "CURLOPT_SHARE", value: 10100)
!193 = !DIEnumerator(name: "CURLOPT_PROXYTYPE", value: 101)
!194 = !DIEnumerator(name: "CURLOPT_ACCEPT_ENCODING", value: 10102)
!195 = !DIEnumerator(name: "CURLOPT_PRIVATE", value: 10103)
!196 = !DIEnumerator(name: "CURLOPT_HTTP200ALIASES", value: 10104)
!197 = !DIEnumerator(name: "CURLOPT_UNRESTRICTED_AUTH", value: 105)
!198 = !DIEnumerator(name: "CURLOPT_FTP_USE_EPRT", value: 106)
!199 = !DIEnumerator(name: "CURLOPT_HTTPAUTH", value: 107)
!200 = !DIEnumerator(name: "CURLOPT_SSL_CTX_FUNCTION", value: 20108)
!201 = !DIEnumerator(name: "CURLOPT_SSL_CTX_DATA", value: 10109)
!202 = !DIEnumerator(name: "CURLOPT_FTP_CREATE_MISSING_DIRS", value: 110)
!203 = !DIEnumerator(name: "CURLOPT_PROXYAUTH", value: 111)
!204 = !DIEnumerator(name: "CURLOPT_FTP_RESPONSE_TIMEOUT", value: 112)
!205 = !DIEnumerator(name: "CURLOPT_IPRESOLVE", value: 113)
!206 = !DIEnumerator(name: "CURLOPT_MAXFILESIZE", value: 114)
!207 = !DIEnumerator(name: "CURLOPT_INFILESIZE_LARGE", value: 30115)
!208 = !DIEnumerator(name: "CURLOPT_RESUME_FROM_LARGE", value: 30116)
!209 = !DIEnumerator(name: "CURLOPT_MAXFILESIZE_LARGE", value: 30117)
!210 = !DIEnumerator(name: "CURLOPT_NETRC_FILE", value: 10118)
!211 = !DIEnumerator(name: "CURLOPT_USE_SSL", value: 119)
!212 = !DIEnumerator(name: "CURLOPT_POSTFIELDSIZE_LARGE", value: 30120)
!213 = !DIEnumerator(name: "CURLOPT_TCP_NODELAY", value: 121)
!214 = !DIEnumerator(name: "CURLOPT_FTPSSLAUTH", value: 129)
!215 = !DIEnumerator(name: "CURLOPT_IOCTLFUNCTION", value: 20130)
!216 = !DIEnumerator(name: "CURLOPT_IOCTLDATA", value: 10131)
!217 = !DIEnumerator(name: "CURLOPT_FTP_ACCOUNT", value: 10134)
!218 = !DIEnumerator(name: "CURLOPT_COOKIELIST", value: 10135)
!219 = !DIEnumerator(name: "CURLOPT_IGNORE_CONTENT_LENGTH", value: 136)
!220 = !DIEnumerator(name: "CURLOPT_FTP_SKIP_PASV_IP", value: 137)
!221 = !DIEnumerator(name: "CURLOPT_FTP_FILEMETHOD", value: 138)
!222 = !DIEnumerator(name: "CURLOPT_LOCALPORT", value: 139)
!223 = !DIEnumerator(name: "CURLOPT_LOCALPORTRANGE", value: 140)
!224 = !DIEnumerator(name: "CURLOPT_CONNECT_ONLY", value: 141)
!225 = !DIEnumerator(name: "CURLOPT_CONV_FROM_NETWORK_FUNCTION", value: 20142)
!226 = !DIEnumerator(name: "CURLOPT_CONV_TO_NETWORK_FUNCTION", value: 20143)
!227 = !DIEnumerator(name: "CURLOPT_CONV_FROM_UTF8_FUNCTION", value: 20144)
!228 = !DIEnumerator(name: "CURLOPT_MAX_SEND_SPEED_LARGE", value: 30145)
!229 = !DIEnumerator(name: "CURLOPT_MAX_RECV_SPEED_LARGE", value: 30146)
!230 = !DIEnumerator(name: "CURLOPT_FTP_ALTERNATIVE_TO_USER", value: 10147)
!231 = !DIEnumerator(name: "CURLOPT_SOCKOPTFUNCTION", value: 20148)
!232 = !DIEnumerator(name: "CURLOPT_SOCKOPTDATA", value: 10149)
!233 = !DIEnumerator(name: "CURLOPT_SSL_SESSIONID_CACHE", value: 150)
!234 = !DIEnumerator(name: "CURLOPT_SSH_AUTH_TYPES", value: 151)
!235 = !DIEnumerator(name: "CURLOPT_SSH_PUBLIC_KEYFILE", value: 10152)
!236 = !DIEnumerator(name: "CURLOPT_SSH_PRIVATE_KEYFILE", value: 10153)
!237 = !DIEnumerator(name: "CURLOPT_FTP_SSL_CCC", value: 154)
!238 = !DIEnumerator(name: "CURLOPT_TIMEOUT_MS", value: 155)
!239 = !DIEnumerator(name: "CURLOPT_CONNECTTIMEOUT_MS", value: 156)
!240 = !DIEnumerator(name: "CURLOPT_HTTP_TRANSFER_DECODING", value: 157)
!241 = !DIEnumerator(name: "CURLOPT_HTTP_CONTENT_DECODING", value: 158)
!242 = !DIEnumerator(name: "CURLOPT_NEW_FILE_PERMS", value: 159)
!243 = !DIEnumerator(name: "CURLOPT_NEW_DIRECTORY_PERMS", value: 160)
!244 = !DIEnumerator(name: "CURLOPT_POSTREDIR", value: 161)
!245 = !DIEnumerator(name: "CURLOPT_SSH_HOST_PUBLIC_KEY_MD5", value: 10162)
!246 = !DIEnumerator(name: "CURLOPT_OPENSOCKETFUNCTION", value: 20163)
!247 = !DIEnumerator(name: "CURLOPT_OPENSOCKETDATA", value: 10164)
!248 = !DIEnumerator(name: "CURLOPT_COPYPOSTFIELDS", value: 10165)
!249 = !DIEnumerator(name: "CURLOPT_PROXY_TRANSFER_MODE", value: 166)
!250 = !DIEnumerator(name: "CURLOPT_SEEKFUNCTION", value: 20167)
!251 = !DIEnumerator(name: "CURLOPT_SEEKDATA", value: 10168)
!252 = !DIEnumerator(name: "CURLOPT_CRLFILE", value: 10169)
!253 = !DIEnumerator(name: "CURLOPT_ISSUERCERT", value: 10170)
!254 = !DIEnumerator(name: "CURLOPT_ADDRESS_SCOPE", value: 171)
!255 = !DIEnumerator(name: "CURLOPT_CERTINFO", value: 172)
!256 = !DIEnumerator(name: "CURLOPT_USERNAME", value: 10173)
!257 = !DIEnumerator(name: "CURLOPT_PASSWORD", value: 10174)
!258 = !DIEnumerator(name: "CURLOPT_PROXYUSERNAME", value: 10175)
!259 = !DIEnumerator(name: "CURLOPT_PROXYPASSWORD", value: 10176)
!260 = !DIEnumerator(name: "CURLOPT_NOPROXY", value: 10177)
!261 = !DIEnumerator(name: "CURLOPT_TFTP_BLKSIZE", value: 178)
!262 = !DIEnumerator(name: "CURLOPT_SOCKS5_GSSAPI_SERVICE", value: 10179)
!263 = !DIEnumerator(name: "CURLOPT_SOCKS5_GSSAPI_NEC", value: 180)
!264 = !DIEnumerator(name: "CURLOPT_PROTOCOLS", value: 181)
!265 = !DIEnumerator(name: "CURLOPT_REDIR_PROTOCOLS", value: 182)
!266 = !DIEnumerator(name: "CURLOPT_SSH_KNOWNHOSTS", value: 10183)
!267 = !DIEnumerator(name: "CURLOPT_SSH_KEYFUNCTION", value: 20184)
!268 = !DIEnumerator(name: "CURLOPT_SSH_KEYDATA", value: 10185)
!269 = !DIEnumerator(name: "CURLOPT_MAIL_FROM", value: 10186)
!270 = !DIEnumerator(name: "CURLOPT_MAIL_RCPT", value: 10187)
!271 = !DIEnumerator(name: "CURLOPT_FTP_USE_PRET", value: 188)
!272 = !DIEnumerator(name: "CURLOPT_RTSP_REQUEST", value: 189)
!273 = !DIEnumerator(name: "CURLOPT_RTSP_SESSION_ID", value: 10190)
!274 = !DIEnumerator(name: "CURLOPT_RTSP_STREAM_URI", value: 10191)
!275 = !DIEnumerator(name: "CURLOPT_RTSP_TRANSPORT", value: 10192)
!276 = !DIEnumerator(name: "CURLOPT_RTSP_CLIENT_CSEQ", value: 193)
!277 = !DIEnumerator(name: "CURLOPT_RTSP_SERVER_CSEQ", value: 194)
!278 = !DIEnumerator(name: "CURLOPT_INTERLEAVEDATA", value: 10195)
!279 = !DIEnumerator(name: "CURLOPT_INTERLEAVEFUNCTION", value: 20196)
!280 = !DIEnumerator(name: "CURLOPT_WILDCARDMATCH", value: 197)
!281 = !DIEnumerator(name: "CURLOPT_CHUNK_BGN_FUNCTION", value: 20198)
!282 = !DIEnumerator(name: "CURLOPT_CHUNK_END_FUNCTION", value: 20199)
!283 = !DIEnumerator(name: "CURLOPT_FNMATCH_FUNCTION", value: 20200)
!284 = !DIEnumerator(name: "CURLOPT_CHUNK_DATA", value: 10201)
!285 = !DIEnumerator(name: "CURLOPT_FNMATCH_DATA", value: 10202)
!286 = !DIEnumerator(name: "CURLOPT_RESOLVE", value: 10203)
!287 = !DIEnumerator(name: "CURLOPT_TLSAUTH_USERNAME", value: 10204)
!288 = !DIEnumerator(name: "CURLOPT_TLSAUTH_PASSWORD", value: 10205)
!289 = !DIEnumerator(name: "CURLOPT_TLSAUTH_TYPE", value: 10206)
!290 = !DIEnumerator(name: "CURLOPT_TRANSFER_ENCODING", value: 207)
!291 = !DIEnumerator(name: "CURLOPT_CLOSESOCKETFUNCTION", value: 20208)
!292 = !DIEnumerator(name: "CURLOPT_CLOSESOCKETDATA", value: 10209)
!293 = !DIEnumerator(name: "CURLOPT_GSSAPI_DELEGATION", value: 210)
!294 = !DIEnumerator(name: "CURLOPT_DNS_SERVERS", value: 10211)
!295 = !DIEnumerator(name: "CURLOPT_ACCEPTTIMEOUT_MS", value: 212)
!296 = !DIEnumerator(name: "CURLOPT_TCP_KEEPALIVE", value: 213)
!297 = !DIEnumerator(name: "CURLOPT_TCP_KEEPIDLE", value: 214)
!298 = !DIEnumerator(name: "CURLOPT_TCP_KEEPINTVL", value: 215)
!299 = !DIEnumerator(name: "CURLOPT_SSL_OPTIONS", value: 216)
!300 = !DIEnumerator(name: "CURLOPT_MAIL_AUTH", value: 10217)
!301 = !DIEnumerator(name: "CURLOPT_SASL_IR", value: 218)
!302 = !DIEnumerator(name: "CURLOPT_XFERINFOFUNCTION", value: 20219)
!303 = !DIEnumerator(name: "CURLOPT_XOAUTH2_BEARER", value: 10220)
!304 = !DIEnumerator(name: "CURLOPT_DNS_INTERFACE", value: 10221)
!305 = !DIEnumerator(name: "CURLOPT_DNS_LOCAL_IP4", value: 10222)
!306 = !DIEnumerator(name: "CURLOPT_DNS_LOCAL_IP6", value: 10223)
!307 = !DIEnumerator(name: "CURLOPT_LOGIN_OPTIONS", value: 10224)
!308 = !DIEnumerator(name: "CURLOPT_SSL_ENABLE_NPN", value: 225)
!309 = !DIEnumerator(name: "CURLOPT_SSL_ENABLE_ALPN", value: 226)
!310 = !DIEnumerator(name: "CURLOPT_EXPECT_100_TIMEOUT_MS", value: 227)
!311 = !DIEnumerator(name: "CURLOPT_PROXYHEADER", value: 10228)
!312 = !DIEnumerator(name: "CURLOPT_HEADEROPT", value: 229)
!313 = !DIEnumerator(name: "CURLOPT_PINNEDPUBLICKEY", value: 10230)
!314 = !DIEnumerator(name: "CURLOPT_UNIX_SOCKET_PATH", value: 10231)
!315 = !DIEnumerator(name: "CURLOPT_SSL_VERIFYSTATUS", value: 232)
!316 = !DIEnumerator(name: "CURLOPT_SSL_FALSESTART", value: 233)
!317 = !DIEnumerator(name: "CURLOPT_PATH_AS_IS", value: 234)
!318 = !DIEnumerator(name: "CURLOPT_PROXY_SERVICE_NAME", value: 10235)
!319 = !DIEnumerator(name: "CURLOPT_SERVICE_NAME", value: 10236)
!320 = !DIEnumerator(name: "CURLOPT_PIPEWAIT", value: 237)
!321 = !DIEnumerator(name: "CURLOPT_DEFAULT_PROTOCOL", value: 10238)
!322 = !DIEnumerator(name: "CURLOPT_STREAM_WEIGHT", value: 239)
!323 = !DIEnumerator(name: "CURLOPT_STREAM_DEPENDS", value: 10240)
!324 = !DIEnumerator(name: "CURLOPT_STREAM_DEPENDS_E", value: 10241)
!325 = !DIEnumerator(name: "CURLOPT_TFTP_NO_OPTIONS", value: 242)
!326 = !DIEnumerator(name: "CURLOPT_CONNECT_TO", value: 10243)
!327 = !DIEnumerator(name: "CURLOPT_TCP_FASTOPEN", value: 244)
!328 = !DIEnumerator(name: "CURLOPT_KEEP_SENDING_ON_ERROR", value: 245)
!329 = !DIEnumerator(name: "CURLOPT_PROXY_CAINFO", value: 10246)
!330 = !DIEnumerator(name: "CURLOPT_PROXY_CAPATH", value: 10247)
!331 = !DIEnumerator(name: "CURLOPT_PROXY_SSL_VERIFYPEER", value: 248)
!332 = !DIEnumerator(name: "CURLOPT_PROXY_SSL_VERIFYHOST", value: 249)
!333 = !DIEnumerator(name: "CURLOPT_PROXY_SSLVERSION", value: 250)
!334 = !DIEnumerator(name: "CURLOPT_PROXY_TLSAUTH_USERNAME", value: 10251)
!335 = !DIEnumerator(name: "CURLOPT_PROXY_TLSAUTH_PASSWORD", value: 10252)
!336 = !DIEnumerator(name: "CURLOPT_PROXY_TLSAUTH_TYPE", value: 10253)
!337 = !DIEnumerator(name: "CURLOPT_PROXY_SSLCERT", value: 10254)
!338 = !DIEnumerator(name: "CURLOPT_PROXY_SSLCERTTYPE", value: 10255)
!339 = !DIEnumerator(name: "CURLOPT_PROXY_SSLKEY", value: 10256)
!340 = !DIEnumerator(name: "CURLOPT_PROXY_SSLKEYTYPE", value: 10257)
!341 = !DIEnumerator(name: "CURLOPT_PROXY_KEYPASSWD", value: 10258)
!342 = !DIEnumerator(name: "CURLOPT_PROXY_SSL_CIPHER_LIST", value: 10259)
!343 = !DIEnumerator(name: "CURLOPT_PROXY_CRLFILE", value: 10260)
!344 = !DIEnumerator(name: "CURLOPT_PROXY_SSL_OPTIONS", value: 261)
!345 = !DIEnumerator(name: "CURLOPT_PRE_PROXY", value: 10262)
!346 = !DIEnumerator(name: "CURLOPT_PROXY_PINNEDPUBLICKEY", value: 10263)
!347 = !DIEnumerator(name: "CURLOPT_ABSTRACT_UNIX_SOCKET", value: 10264)
!348 = !DIEnumerator(name: "CURLOPT_SUPPRESS_CONNECT_HEADERS", value: 265)
!349 = !DIEnumerator(name: "CURLOPT_LASTENTRY", value: 266)
!350 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 644, size: 32, align: 32, elements: !351)
!351 = !{!352, !353, !354, !355, !356, !357, !358}
!352 = !DIEnumerator(name: "CURLPROXY_HTTP", value: 0)
!353 = !DIEnumerator(name: "CURLPROXY_HTTP_1_0", value: 1)
!354 = !DIEnumerator(name: "CURLPROXY_HTTPS", value: 2)
!355 = !DIEnumerator(name: "CURLPROXY_SOCKS4", value: 4)
!356 = !DIEnumerator(name: "CURLPROXY_SOCKS5", value: 5)
!357 = !DIEnumerator(name: "CURLPROXY_SOCKS4A", value: 6)
!358 = !DIEnumerator(name: "CURLPROXY_SOCKS5_HOSTNAME", value: 7)
!359 = !{!360, !365, !370}
!360 = distinct !DISubprogram(name: "GetFtpFile", scope: !1, file: !1, line: 8, type: !361, isLocal: false, isDefinition: true, scopeLine: 9, flags: DIFlagPrototyped, isOptimized: false, variables: !364)
!361 = !DISubroutineType(types: !362)
!362 = !{!363}
!363 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!364 = !{}
!365 = distinct !DISubprogram(name: "GetWebFiles", scope: !1, file: !1, line: 39, type: !366, isLocal: false, isDefinition: true, scopeLine: 40, flags: DIFlagPrototyped, isOptimized: false, variables: !364)
!366 = !DISubroutineType(types: !367)
!367 = !{!363, !368, !368}
!368 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !369, size: 64, align: 64)
!369 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!370 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 136, type: !371, isLocal: false, isDefinition: true, scopeLine: 137, flags: DIFlagPrototyped, isOptimized: false, variables: !364)
!371 = !DISubroutineType(types: !372)
!372 = !{!363, !363, !373}
!373 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !368, size: 64, align: 64)
!374 = !{i32 2, !"Dwarf Version", i32 4}
!375 = !{i32 2, !"Debug Info Version", i32 3}
!376 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!377 = !DILocalVariable(name: "retVal", scope: !360, file: !1, line: 10, type: !363)
!378 = !DIExpression()
!379 = !DILocation(line: 10, column: 7, scope: !360)
!380 = !DILocalVariable(name: "curl", scope: !360, file: !1, line: 11, type: !381)
!381 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !382, size: 64, align: 64)
!382 = !DIDerivedType(tag: DW_TAG_typedef, name: "CURL", file: !4, line: 103, baseType: null)
!383 = !DILocation(line: 11, column: 9, scope: !360)
!384 = !DILocalVariable(name: "res", scope: !360, file: !1, line: 12, type: !385)
!385 = !DIDerivedType(tag: DW_TAG_typedef, name: "CURLcode", file: !4, line: 561, baseType: !3)
!386 = !DILocation(line: 12, column: 12, scope: !360)
!387 = !DILocation(line: 13, column: 10, scope: !360)
!388 = !DILocation(line: 13, column: 8, scope: !360)
!389 = !DILocation(line: 14, column: 6, scope: !390)
!390 = distinct !DILexicalBlock(scope: !360, file: !1, line: 14, column: 6)
!391 = !DILocation(line: 14, column: 6, scope: !360)
!392 = !DILocation(line: 17, column: 22, scope: !393)
!393 = distinct !DILexicalBlock(scope: !390, file: !1, line: 15, column: 5)
!394 = !DILocation(line: 17, column: 5, scope: !393)
!395 = !DILocation(line: 18, column: 22, scope: !393)
!396 = !DILocation(line: 18, column: 5, scope: !393)
!397 = !DILocation(line: 19, column: 22, scope: !393)
!398 = !DILocation(line: 19, column: 5, scope: !393)
!399 = !DILocation(line: 21, column: 29, scope: !393)
!400 = !DILocation(line: 21, column: 11, scope: !393)
!401 = !DILocation(line: 21, column: 9, scope: !393)
!402 = !DILocation(line: 22, column: 10, scope: !403)
!403 = distinct !DILexicalBlock(scope: !393, file: !1, line: 22, column: 10)
!404 = !DILocation(line: 22, column: 14, scope: !403)
!405 = !DILocation(line: 22, column: 10, scope: !393)
!406 = !DILocation(line: 24, column: 7, scope: !407)
!407 = distinct !DILexicalBlock(scope: !403, file: !1, line: 23, column: 7)
!408 = !DILocation(line: 25, column: 14, scope: !407)
!409 = !DILocation(line: 26, column: 7, scope: !407)
!410 = !DILocation(line: 29, column: 23, scope: !393)
!411 = !DILocation(line: 29, column: 5, scope: !393)
!412 = !DILocation(line: 30, column: 5, scope: !393)
!413 = !DILocation(line: 33, column: 5, scope: !414)
!414 = distinct !DILexicalBlock(scope: !390, file: !1, line: 32, column: 5)
!415 = !DILocation(line: 34, column: 12, scope: !414)
!416 = !DILocation(line: 36, column: 10, scope: !360)
!417 = !DILocation(line: 36, column: 3, scope: !360)
!418 = !DILocalVariable(name: "url1", arg: 1, scope: !365, file: !1, line: 39, type: !368)
!419 = !DILocation(line: 39, column: 23, scope: !365)
!420 = !DILocalVariable(name: "url2", arg: 2, scope: !365, file: !1, line: 39, type: !368)
!421 = !DILocation(line: 39, column: 35, scope: !365)
!422 = !DILocalVariable(name: "retVal", scope: !365, file: !1, line: 41, type: !363)
!423 = !DILocation(line: 41, column: 7, scope: !365)
!424 = !DILocalVariable(name: "curl", scope: !365, file: !1, line: 42, type: !381)
!425 = !DILocation(line: 42, column: 9, scope: !365)
!426 = !DILocalVariable(name: "res", scope: !365, file: !1, line: 43, type: !385)
!427 = !DILocation(line: 43, column: 12, scope: !365)
!428 = !DILocalVariable(name: "proxy", scope: !365, file: !1, line: 45, type: !429)
!429 = !DICompositeType(tag: DW_TAG_array_type, baseType: !369, size: 8192, align: 8, elements: !430)
!430 = !{!431}
!431 = !DISubrange(count: 1024)
!432 = !DILocation(line: 45, column: 8, scope: !365)
!433 = !DILocalVariable(name: "proxy_type", scope: !365, file: !1, line: 46, type: !363)
!434 = !DILocation(line: 46, column: 7, scope: !365)
!435 = !DILocation(line: 48, column: 8, scope: !436)
!436 = distinct !DILexicalBlock(scope: !365, file: !1, line: 48, column: 8)
!437 = !DILocation(line: 48, column: 8, scope: !365)
!438 = !DILocation(line: 50, column: 16, scope: !439)
!439 = distinct !DILexicalBlock(scope: !436, file: !1, line: 49, column: 5)
!440 = !DILocation(line: 51, column: 9, scope: !441)
!441 = distinct !DILexicalBlock(scope: !439, file: !1, line: 51, column: 9)
!442 = !DILocation(line: 51, column: 9, scope: !439)
!443 = !DILocation(line: 53, column: 15, scope: !444)
!444 = distinct !DILexicalBlock(scope: !441, file: !1, line: 52, column: 7)
!445 = !DILocation(line: 53, column: 31, scope: !444)
!446 = !DILocation(line: 53, column: 53, scope: !447)
!447 = !DILexicalBlockFile(scope: !444, file: !1, discriminator: 1)
!448 = !DILocation(line: 53, column: 7, scope: !449)
!449 = !DILexicalBlockFile(scope: !444, file: !1, discriminator: 2)
!450 = !DILocation(line: 54, column: 7, scope: !444)
!451 = !DILocation(line: 57, column: 15, scope: !452)
!452 = distinct !DILexicalBlock(scope: !441, file: !1, line: 56, column: 7)
!453 = !DILocation(line: 57, column: 28, scope: !452)
!454 = !DILocation(line: 57, column: 7, scope: !455)
!455 = !DILexicalBlockFile(scope: !452, file: !1, discriminator: 1)
!456 = !DILocation(line: 59, column: 10, scope: !457)
!457 = distinct !DILexicalBlock(scope: !439, file: !1, line: 59, column: 10)
!458 = !DILocation(line: 59, column: 10, scope: !439)
!459 = !DILocation(line: 62, column: 19, scope: !460)
!460 = distinct !DILexicalBlock(scope: !461, file: !1, line: 62, column: 12)
!461 = distinct !DILexicalBlock(scope: !457, file: !1, line: 60, column: 7)
!462 = !DILocation(line: 62, column: 12, scope: !463)
!463 = !DILexicalBlockFile(scope: !460, file: !1, discriminator: 1)
!464 = !DILocation(line: 62, column: 54, scope: !460)
!465 = !DILocation(line: 62, column: 12, scope: !461)
!466 = !DILocation(line: 64, column: 20, scope: !467)
!467 = distinct !DILexicalBlock(scope: !460, file: !1, line: 63, column: 9)
!468 = !DILocation(line: 65, column: 9, scope: !467)
!469 = !DILocation(line: 66, column: 24, scope: !470)
!470 = distinct !DILexicalBlock(scope: !460, file: !1, line: 66, column: 17)
!471 = !DILocation(line: 66, column: 17, scope: !472)
!472 = !DILexicalBlockFile(scope: !470, file: !1, discriminator: 1)
!473 = !DILocation(line: 66, column: 61, scope: !470)
!474 = !DILocation(line: 66, column: 17, scope: !460)
!475 = !DILocation(line: 68, column: 20, scope: !476)
!476 = distinct !DILexicalBlock(scope: !470, file: !1, line: 67, column: 9)
!477 = !DILocation(line: 69, column: 9, scope: !476)
!478 = !DILocation(line: 70, column: 24, scope: !479)
!479 = distinct !DILexicalBlock(scope: !470, file: !1, line: 70, column: 17)
!480 = !DILocation(line: 70, column: 17, scope: !481)
!481 = !DILexicalBlockFile(scope: !479, file: !1, discriminator: 1)
!482 = !DILocation(line: 70, column: 61, scope: !479)
!483 = !DILocation(line: 70, column: 17, scope: !470)
!484 = !DILocation(line: 72, column: 20, scope: !485)
!485 = distinct !DILexicalBlock(scope: !479, file: !1, line: 71, column: 9)
!486 = !DILocation(line: 73, column: 9, scope: !485)
!487 = !DILocation(line: 74, column: 7, scope: !461)
!488 = !DILocation(line: 75, column: 5, scope: !439)
!489 = !DILocation(line: 77, column: 10, scope: !365)
!490 = !DILocation(line: 77, column: 8, scope: !365)
!491 = !DILocation(line: 78, column: 6, scope: !492)
!492 = distinct !DILexicalBlock(scope: !365, file: !1, line: 78, column: 6)
!493 = !DILocation(line: 78, column: 6, scope: !365)
!494 = !DILocation(line: 80, column: 22, scope: !495)
!495 = distinct !DILexicalBlock(scope: !492, file: !1, line: 79, column: 5)
!496 = !DILocation(line: 80, column: 5, scope: !495)
!497 = !DILocation(line: 81, column: 22, scope: !495)
!498 = !DILocation(line: 81, column: 5, scope: !495)
!499 = !DILocation(line: 84, column: 10, scope: !500)
!500 = distinct !DILexicalBlock(scope: !495, file: !1, line: 84, column: 10)
!501 = !DILocation(line: 84, column: 21, scope: !500)
!502 = !DILocation(line: 84, column: 10, scope: !495)
!503 = !DILocation(line: 86, column: 24, scope: !504)
!504 = distinct !DILexicalBlock(scope: !500, file: !1, line: 85, column: 7)
!505 = !DILocation(line: 86, column: 45, scope: !504)
!506 = !DILocation(line: 86, column: 7, scope: !504)
!507 = !DILocation(line: 87, column: 15, scope: !504)
!508 = !DILocation(line: 87, column: 7, scope: !504)
!509 = !DILocation(line: 90, column: 28, scope: !510)
!510 = distinct !DILexicalBlock(scope: !504, file: !1, line: 88, column: 9)
!511 = !DILocation(line: 90, column: 11, scope: !510)
!512 = !DILocation(line: 91, column: 11, scope: !510)
!513 = !DILocation(line: 93, column: 28, scope: !510)
!514 = !DILocation(line: 93, column: 11, scope: !510)
!515 = !DILocation(line: 94, column: 11, scope: !510)
!516 = !DILocation(line: 96, column: 28, scope: !510)
!517 = !DILocation(line: 96, column: 11, scope: !510)
!518 = !DILocation(line: 97, column: 9, scope: !510)
!519 = !DILocation(line: 98, column: 7, scope: !504)
!520 = !DILocation(line: 101, column: 22, scope: !495)
!521 = !DILocation(line: 101, column: 41, scope: !495)
!522 = !DILocation(line: 101, column: 5, scope: !495)
!523 = !DILocation(line: 102, column: 29, scope: !495)
!524 = !DILocation(line: 102, column: 11, scope: !495)
!525 = !DILocation(line: 102, column: 9, scope: !495)
!526 = !DILocation(line: 103, column: 10, scope: !527)
!527 = distinct !DILexicalBlock(scope: !495, file: !1, line: 103, column: 10)
!528 = !DILocation(line: 103, column: 14, scope: !527)
!529 = !DILocation(line: 103, column: 10, scope: !495)
!530 = !DILocation(line: 105, column: 38, scope: !531)
!531 = distinct !DILexicalBlock(scope: !527, file: !1, line: 104, column: 7)
!532 = !DILocation(line: 105, column: 7, scope: !531)
!533 = !DILocation(line: 106, column: 14, scope: !531)
!534 = !DILocation(line: 107, column: 7, scope: !531)
!535 = !DILocation(line: 112, column: 12, scope: !495)
!536 = !DILocation(line: 124, column: 23, scope: !495)
!537 = !DILocation(line: 124, column: 5, scope: !495)
!538 = !DILocation(line: 125, column: 5, scope: !495)
!539 = !DILocation(line: 128, column: 5, scope: !540)
!540 = distinct !DILexicalBlock(scope: !492, file: !1, line: 127, column: 5)
!541 = !DILocation(line: 129, column: 12, scope: !540)
!542 = !DILocation(line: 132, column: 10, scope: !365)
!543 = !DILocation(line: 132, column: 3, scope: !365)
!544 = !DILocalVariable(name: "argc", arg: 1, scope: !370, file: !1, line: 136, type: !363)
!545 = !DILocation(line: 136, column: 14, scope: !370)
!546 = !DILocalVariable(name: "argv", arg: 2, scope: !370, file: !1, line: 136, type: !373)
!547 = !DILocation(line: 136, column: 27, scope: !370)
!548 = !DILocalVariable(name: "retVal", scope: !370, file: !1, line: 138, type: !363)
!549 = !DILocation(line: 138, column: 7, scope: !370)
!550 = !DILocation(line: 140, column: 3, scope: !370)
!551 = !DILocation(line: 142, column: 6, scope: !552)
!552 = distinct !DILexicalBlock(scope: !370, file: !1, line: 142, column: 6)
!553 = !DILocation(line: 142, column: 10, scope: !552)
!554 = !DILocation(line: 142, column: 6, scope: !370)
!555 = !DILocation(line: 144, column: 27, scope: !556)
!556 = distinct !DILexicalBlock(scope: !552, file: !1, line: 143, column: 5)
!557 = !DILocation(line: 144, column: 15, scope: !556)
!558 = !DILocation(line: 144, column: 12, scope: !556)
!559 = !DILocation(line: 145, column: 5, scope: !556)
!560 = !DILocation(line: 148, column: 5, scope: !561)
!561 = distinct !DILexicalBlock(scope: !552, file: !1, line: 147, column: 5)
!562 = !DILocation(line: 149, column: 12, scope: !561)
!563 = !DILocation(line: 156, column: 3, scope: !370)
!564 = !DILocation(line: 158, column: 10, scope: !370)
!565 = !DILocation(line: 158, column: 3, scope: !370)
