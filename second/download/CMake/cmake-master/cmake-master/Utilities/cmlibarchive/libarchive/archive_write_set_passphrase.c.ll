; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_set_passphrase.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { i32 (%struct.archive*)*, i32 (%struct.archive*)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)*, i8* (%struct.archive*, i32)* }
%struct.archive_entry = type opaque
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque
%struct.archive_write = type { %struct.archive, i32, i64, i64, i8*, i64, i32 (%struct.archive*, i8*)*, i64 (%struct.archive*, i8*, i8*, i64)*, i32 (%struct.archive*, i8*)*, i8*, i32, i32, %struct.archive_write_filter*, %struct.archive_write_filter*, i8*, i8*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*, i8*, i8*)*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*, %struct.archive_entry*)*, i64 (%struct.archive_write*, i8*, i64)*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)*, i8*, i8* (%struct.archive*, i8*)*, i8* }
%struct.archive_write_filter = type { i64, %struct.archive*, %struct.archive_write_filter*, i32 (%struct.archive_write_filter*, i8*, i8*)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*, i8*, i64)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*)*, i8*, i8*, i32, i32, i32 }

@.str = private unnamed_addr constant [29 x i8] c"archive_write_set_passphrase\00", align 1
@.str.1 = private unnamed_addr constant [33 x i8] c"Empty passphrase is unacceptable\00", align 1
@.str.2 = private unnamed_addr constant [35 x i8] c"Can't allocate data for passphrase\00", align 1
@.str.3 = private unnamed_addr constant [38 x i8] c"archive_write_set_passphrase_callback\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_write_set_passphrase(%struct.archive* %_a, i8* %p) #0 !dbg !192 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %p.addr = alloca i8*, align 8
  %a = alloca %struct.archive_write*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !204, metadata !205), !dbg !206
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !207, metadata !205), !dbg !208
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !209, metadata !205), !dbg !210
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !211
  %1 = bitcast %struct.archive* %0 to %struct.archive_write*, !dbg !212
  store %struct.archive_write* %1, %struct.archive_write** %a, align 8, !dbg !210
  br label %do.body, !dbg !213

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !214, metadata !205), !dbg !216
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !217
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 -1329217314, i32 1, i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str, i32 0, i32 0)), !dbg !217
  store i32 %call, i32* %magic_test, align 4, !dbg !217
  %3 = load i32, i32* %magic_test, align 4, !dbg !217
  %cmp = icmp eq i32 %3, -30, !dbg !217
  br i1 %cmp, label %if.then, label %if.end, !dbg !217

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !219
  br label %return, !dbg !219

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !222

do.end:                                           ; preds = %if.end
  %4 = load i8*, i8** %p.addr, align 8, !dbg !224
  %cmp1 = icmp eq i8* %4, null, !dbg !226
  br i1 %cmp1, label %if.then4, label %lor.lhs.false, !dbg !227

lor.lhs.false:                                    ; preds = %do.end
  %5 = load i8*, i8** %p.addr, align 8, !dbg !228
  %arrayidx = getelementptr inbounds i8, i8* %5, i64 0, !dbg !228
  %6 = load i8, i8* %arrayidx, align 1, !dbg !228
  %conv = sext i8 %6 to i32, !dbg !228
  %cmp2 = icmp eq i32 %conv, 0, !dbg !230
  br i1 %cmp2, label %if.then4, label %if.end5, !dbg !231

if.then4:                                         ; preds = %lor.lhs.false, %do.end
  %7 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !232
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %7, i32 0, i32 0, !dbg !234
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 -1, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.1, i32 0, i32 0)), !dbg !235
  store i32 -25, i32* %retval, align 4, !dbg !236
  br label %return, !dbg !236

if.end5:                                          ; preds = %lor.lhs.false
  %8 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !237
  %passphrase = getelementptr inbounds %struct.archive_write, %struct.archive_write* %8, i32 0, i32 23, !dbg !238
  %9 = load i8*, i8** %passphrase, align 8, !dbg !238
  call void @free(i8* %9) #4, !dbg !239
  %10 = load i8*, i8** %p.addr, align 8, !dbg !240
  %call6 = call noalias i8* @strdup(i8* %10) #4, !dbg !241
  %11 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !242
  %passphrase7 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %11, i32 0, i32 23, !dbg !243
  store i8* %call6, i8** %passphrase7, align 8, !dbg !244
  %12 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !245
  %passphrase8 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %12, i32 0, i32 23, !dbg !247
  %13 = load i8*, i8** %passphrase8, align 8, !dbg !247
  %cmp9 = icmp eq i8* %13, null, !dbg !248
  br i1 %cmp9, label %if.then11, label %if.end13, !dbg !249

if.then11:                                        ; preds = %if.end5
  %14 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !250
  %archive12 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %14, i32 0, i32 0, !dbg !252
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive12, i32 12, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.2, i32 0, i32 0)), !dbg !253
  store i32 -30, i32* %retval, align 4, !dbg !254
  br label %return, !dbg !254

if.end13:                                         ; preds = %if.end5
  store i32 0, i32* %retval, align 4, !dbg !255
  br label %return, !dbg !255

return:                                           ; preds = %if.end13, %if.then11, %if.then4, %if.then
  %15 = load i32, i32* %retval, align 4, !dbg !256
  ret i32 %15, !dbg !256
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @__archive_check_magic(%struct.archive*, i32, i32, i8*) #2

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

; Function Attrs: nounwind
declare void @free(i8*) #3

; Function Attrs: nounwind
declare noalias i8* @strdup(i8*) #3

; Function Attrs: nounwind uwtable
define i32 @archive_write_set_passphrase_callback(%struct.archive* %_a, i8* %client_data, i8* (%struct.archive*, i8*)* %cb) #0 !dbg !195 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %client_data.addr = alloca i8*, align 8
  %cb.addr = alloca i8* (%struct.archive*, i8*)*, align 8
  %a = alloca %struct.archive_write*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !257, metadata !205), !dbg !258
  store i8* %client_data, i8** %client_data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %client_data.addr, metadata !259, metadata !205), !dbg !260
  store i8* (%struct.archive*, i8*)* %cb, i8* (%struct.archive*, i8*)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata i8* (%struct.archive*, i8*)** %cb.addr, metadata !261, metadata !205), !dbg !262
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !263, metadata !205), !dbg !264
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !265
  %1 = bitcast %struct.archive* %0 to %struct.archive_write*, !dbg !266
  store %struct.archive_write* %1, %struct.archive_write** %a, align 8, !dbg !264
  br label %do.body, !dbg !267

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !268, metadata !205), !dbg !270
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !271
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 -1329217314, i32 1, i8* getelementptr inbounds ([38 x i8], [38 x i8]* @.str.3, i32 0, i32 0)), !dbg !271
  store i32 %call, i32* %magic_test, align 4, !dbg !271
  %3 = load i32, i32* %magic_test, align 4, !dbg !271
  %cmp = icmp eq i32 %3, -30, !dbg !271
  br i1 %cmp, label %if.then, label %if.end, !dbg !271

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !273
  br label %return, !dbg !273

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !276

do.end:                                           ; preds = %if.end
  %4 = load i8* (%struct.archive*, i8*)*, i8* (%struct.archive*, i8*)** %cb.addr, align 8, !dbg !278
  %5 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !279
  %passphrase_callback = getelementptr inbounds %struct.archive_write, %struct.archive_write* %5, i32 0, i32 24, !dbg !280
  store i8* (%struct.archive*, i8*)* %4, i8* (%struct.archive*, i8*)** %passphrase_callback, align 8, !dbg !281
  %6 = load i8*, i8** %client_data.addr, align 8, !dbg !282
  %7 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !283
  %passphrase_client_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %7, i32 0, i32 25, !dbg !284
  store i8* %6, i8** %passphrase_client_data, align 8, !dbg !285
  store i32 0, i32* %retval, align 4, !dbg !286
  br label %return, !dbg !286

return:                                           ; preds = %do.end, %if.then
  %8 = load i32, i32* %retval, align 4, !dbg !287
  ret i32 %8, !dbg !287
}

; Function Attrs: nounwind uwtable
define i8* @__archive_write_get_passphrase(%struct.archive_write* %a) #0 !dbg !198 {
entry:
  %retval = alloca i8*, align 8
  %a.addr = alloca %struct.archive_write*, align 8
  %p = alloca i8*, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !288, metadata !205), !dbg !289
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !290
  %passphrase = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 23, !dbg !292
  %1 = load i8*, i8** %passphrase, align 8, !dbg !292
  %cmp = icmp ne i8* %1, null, !dbg !293
  br i1 %cmp, label %if.then, label %if.end, !dbg !294

if.then:                                          ; preds = %entry
  %2 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !295
  %passphrase1 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %2, i32 0, i32 23, !dbg !296
  %3 = load i8*, i8** %passphrase1, align 8, !dbg !296
  store i8* %3, i8** %retval, align 8, !dbg !297
  br label %return, !dbg !297

if.end:                                           ; preds = %entry
  %4 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !298
  %passphrase_callback = getelementptr inbounds %struct.archive_write, %struct.archive_write* %4, i32 0, i32 24, !dbg !300
  %5 = load i8* (%struct.archive*, i8*)*, i8* (%struct.archive*, i8*)** %passphrase_callback, align 8, !dbg !300
  %cmp2 = icmp ne i8* (%struct.archive*, i8*)* %5, null, !dbg !301
  br i1 %cmp2, label %if.then3, label %if.end16, !dbg !302

if.then3:                                         ; preds = %if.end
  call void @llvm.dbg.declare(metadata i8** %p, metadata !303, metadata !205), !dbg !305
  %6 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !306
  %passphrase_callback4 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %6, i32 0, i32 24, !dbg !307
  %7 = load i8* (%struct.archive*, i8*)*, i8* (%struct.archive*, i8*)** %passphrase_callback4, align 8, !dbg !307
  %8 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !308
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %8, i32 0, i32 0, !dbg !309
  %9 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !310
  %passphrase_client_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %9, i32 0, i32 25, !dbg !311
  %10 = load i8*, i8** %passphrase_client_data, align 8, !dbg !311
  %call = call i8* %7(%struct.archive* %archive, i8* %10), !dbg !306
  store i8* %call, i8** %p, align 8, !dbg !312
  %11 = load i8*, i8** %p, align 8, !dbg !313
  %cmp5 = icmp ne i8* %11, null, !dbg !315
  br i1 %cmp5, label %if.then6, label %if.end15, !dbg !316

if.then6:                                         ; preds = %if.then3
  %12 = load i8*, i8** %p, align 8, !dbg !317
  %call7 = call noalias i8* @strdup(i8* %12) #4, !dbg !319
  %13 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !320
  %passphrase8 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %13, i32 0, i32 23, !dbg !321
  store i8* %call7, i8** %passphrase8, align 8, !dbg !322
  %14 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !323
  %passphrase9 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %14, i32 0, i32 23, !dbg !325
  %15 = load i8*, i8** %passphrase9, align 8, !dbg !325
  %cmp10 = icmp eq i8* %15, null, !dbg !326
  br i1 %cmp10, label %if.then11, label %if.end13, !dbg !327

if.then11:                                        ; preds = %if.then6
  %16 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !328
  %archive12 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %16, i32 0, i32 0, !dbg !330
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive12, i32 12, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.2, i32 0, i32 0)), !dbg !331
  store i8* null, i8** %retval, align 8, !dbg !332
  br label %return, !dbg !332

if.end13:                                         ; preds = %if.then6
  %17 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !333
  %passphrase14 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %17, i32 0, i32 23, !dbg !334
  %18 = load i8*, i8** %passphrase14, align 8, !dbg !334
  store i8* %18, i8** %retval, align 8, !dbg !335
  br label %return, !dbg !335

if.end15:                                         ; preds = %if.then3
  br label %if.end16, !dbg !336

if.end16:                                         ; preds = %if.end15, %if.end
  store i8* null, i8** %retval, align 8, !dbg !337
  br label %return, !dbg !337

return:                                           ; preds = %if.end16, %if.end13, %if.then11, %if.then
  %19 = load i8*, i8** %retval, align 8, !dbg !338
  ret i8* %19, !dbg !338
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!201, !202}
!llvm.ident = !{!203}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !191)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_set_passphrase.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !123}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !5, size: 64, align: 64)
!5 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_write", file: !6, line: 72, size: 2816, align: 64, elements: !7)
!6 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!7 = !{!8, !110, !111, !112, !113, !117, !118, !124, !130, !133, !134, !135, !136, !162, !163, !164, !165, !169, !173, !174, !178, !182, !183, !184, !185, !190}
!8 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !5, file: !6, line: 73, baseType: !9, size: 1280, align: 64)
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
!110 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_set", scope: !5, file: !6, line: 76, baseType: !23, size: 32, align: 32, offset: 1280)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_dev", scope: !5, file: !6, line: 77, baseType: !52, size: 64, align: 64, offset: 1344)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_ino", scope: !5, file: !6, line: 78, baseType: !52, size: 64, align: 64, offset: 1408)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "nulls", scope: !5, file: !6, line: 81, baseType: !114, size: 64, align: 64, offset: 1472)
!114 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !115, size: 64, align: 64)
!115 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !116)
!116 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!117 = !DIDerivedType(tag: DW_TAG_member, name: "null_length", scope: !5, file: !6, line: 82, baseType: !45, size: 64, align: 64, offset: 1536)
!118 = !DIDerivedType(tag: DW_TAG_member, name: "client_opener", scope: !5, file: !6, line: 85, baseType: !119, size: 64, align: 64, offset: 1600)
!119 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !120, size: 64, align: 64)
!120 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_open_callback", file: !32, line: 241, baseType: !121)
!121 = !DISubroutineType(types: !122)
!122 = !{!23, !24, !123}
!123 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!124 = !DIDerivedType(tag: DW_TAG_member, name: "client_writer", scope: !5, file: !6, line: 86, baseType: !125, size: 64, align: 64, offset: 1664)
!125 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !126, size: 64, align: 64)
!126 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_write_callback", file: !32, line: 237, baseType: !127)
!127 = !DISubroutineType(types: !128)
!128 = !{!129, !24, !123, !43, !45}
!129 = !DIDerivedType(tag: DW_TAG_typedef, name: "la_ssize_t", file: !32, line: 95, baseType: !38)
!130 = !DIDerivedType(tag: DW_TAG_member, name: "client_closer", scope: !5, file: !6, line: 87, baseType: !131, size: 64, align: 64, offset: 1728)
!131 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !132, size: 64, align: 64)
!132 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_close_callback", file: !32, line: 243, baseType: !121)
!133 = !DIDerivedType(tag: DW_TAG_member, name: "client_data", scope: !5, file: !6, line: 88, baseType: !123, size: 64, align: 64, offset: 1792)
!134 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_per_block", scope: !5, file: !6, line: 96, baseType: !23, size: 32, align: 32, offset: 1856)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_in_last_block", scope: !5, file: !6, line: 97, baseType: !23, size: 32, align: 32, offset: 1888)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "filter_first", scope: !5, file: !6, line: 102, baseType: !137, size: 64, align: 64, offset: 1920)
!137 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !138, size: 64, align: 64)
!138 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_write_filter", file: !6, line: 43, size: 768, align: 64, elements: !139)
!139 = !{!140, !141, !142, !143, !147, !151, !155, !156, !157, !158, !159, !160, !161}
!140 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_written", scope: !138, file: !6, line: 44, baseType: !52, size: 64, align: 64)
!141 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !138, file: !6, line: 45, baseType: !24, size: 64, align: 64, offset: 64)
!142 = !DIDerivedType(tag: DW_TAG_member, name: "next_filter", scope: !138, file: !6, line: 46, baseType: !137, size: 64, align: 64, offset: 128)
!143 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !138, file: !6, line: 47, baseType: !144, size: 64, align: 64, offset: 192)
!144 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !145, size: 64, align: 64)
!145 = !DISubroutineType(types: !146)
!146 = !{!23, !137, !80, !80}
!147 = !DIDerivedType(tag: DW_TAG_member, name: "open", scope: !138, file: !6, line: 49, baseType: !148, size: 64, align: 64, offset: 256)
!148 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !149, size: 64, align: 64)
!149 = !DISubroutineType(types: !150)
!150 = !{!23, !137}
!151 = !DIDerivedType(tag: DW_TAG_member, name: "write", scope: !138, file: !6, line: 50, baseType: !152, size: 64, align: 64, offset: 320)
!152 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !153, size: 64, align: 64)
!153 = !DISubroutineType(types: !154)
!154 = !{!23, !137, !43, !45}
!155 = !DIDerivedType(tag: DW_TAG_member, name: "close", scope: !138, file: !6, line: 51, baseType: !148, size: 64, align: 64, offset: 384)
!156 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !138, file: !6, line: 52, baseType: !148, size: 64, align: 64, offset: 448)
!157 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !138, file: !6, line: 53, baseType: !123, size: 64, align: 64, offset: 512)
!158 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !138, file: !6, line: 54, baseType: !80, size: 64, align: 64, offset: 576)
!159 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !138, file: !6, line: 55, baseType: !23, size: 32, align: 32, offset: 640)
!160 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_per_block", scope: !138, file: !6, line: 56, baseType: !23, size: 32, align: 32, offset: 672)
!161 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_in_last_block", scope: !138, file: !6, line: 57, baseType: !23, size: 32, align: 32, offset: 704)
!162 = !DIDerivedType(tag: DW_TAG_member, name: "filter_last", scope: !5, file: !6, line: 103, baseType: !137, size: 64, align: 64, offset: 1984)
!163 = !DIDerivedType(tag: DW_TAG_member, name: "format_data", scope: !5, file: !6, line: 109, baseType: !123, size: 64, align: 64, offset: 2048)
!164 = !DIDerivedType(tag: DW_TAG_member, name: "format_name", scope: !5, file: !6, line: 110, baseType: !80, size: 64, align: 64, offset: 2112)
!165 = !DIDerivedType(tag: DW_TAG_member, name: "format_init", scope: !5, file: !6, line: 111, baseType: !166, size: 64, align: 64, offset: 2176)
!166 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !167, size: 64, align: 64)
!167 = !DISubroutineType(types: !168)
!168 = !{!23, !4}
!169 = !DIDerivedType(tag: DW_TAG_member, name: "format_options", scope: !5, file: !6, line: 112, baseType: !170, size: 64, align: 64, offset: 2240)
!170 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !171, size: 64, align: 64)
!171 = !DISubroutineType(types: !172)
!172 = !{!23, !4, !80, !80}
!173 = !DIDerivedType(tag: DW_TAG_member, name: "format_finish_entry", scope: !5, file: !6, line: 114, baseType: !166, size: 64, align: 64, offset: 2304)
!174 = !DIDerivedType(tag: DW_TAG_member, name: "format_write_header", scope: !5, file: !6, line: 115, baseType: !175, size: 64, align: 64, offset: 2368)
!175 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !176, size: 64, align: 64)
!176 = !DISubroutineType(types: !177)
!177 = !{!23, !4, !30}
!178 = !DIDerivedType(tag: DW_TAG_member, name: "format_write_data", scope: !5, file: !6, line: 117, baseType: !179, size: 64, align: 64, offset: 2432)
!179 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !180, size: 64, align: 64)
!180 = !DISubroutineType(types: !181)
!181 = !{!38, !4, !43, !45}
!182 = !DIDerivedType(tag: DW_TAG_member, name: "format_close", scope: !5, file: !6, line: 119, baseType: !166, size: 64, align: 64, offset: 2496)
!183 = !DIDerivedType(tag: DW_TAG_member, name: "format_free", scope: !5, file: !6, line: 120, baseType: !166, size: 64, align: 64, offset: 2560)
!184 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase", scope: !5, file: !6, line: 126, baseType: !95, size: 64, align: 64, offset: 2624)
!185 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase_callback", scope: !5, file: !6, line: 127, baseType: !186, size: 64, align: 64, offset: 2688)
!186 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !187, size: 64, align: 64)
!187 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_passphrase_callback", file: !32, line: 256, baseType: !188)
!188 = !DISubroutineType(types: !189)
!189 = !{!80, !24, !123}
!190 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase_client_data", scope: !5, file: !6, line: 128, baseType: !123, size: 64, align: 64, offset: 2752)
!191 = !{!192, !195, !198}
!192 = distinct !DISubprogram(name: "archive_write_set_passphrase", scope: !1, file: !1, line: 35, type: !193, isLocal: false, isDefinition: true, scopeLine: 36, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!193 = !DISubroutineType(types: !194)
!194 = !{!23, !24, !80}
!195 = distinct !DISubprogram(name: "archive_write_set_passphrase_callback", scope: !1, file: !1, line: 59, type: !196, isLocal: false, isDefinition: true, scopeLine: 61, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!196 = !DISubroutineType(types: !197)
!197 = !{!23, !24, !123, !186}
!198 = distinct !DISubprogram(name: "__archive_write_get_passphrase", scope: !1, file: !1, line: 74, type: !199, isLocal: false, isDefinition: true, scopeLine: 75, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!199 = !DISubroutineType(types: !200)
!200 = !{!80, !4}
!201 = !{i32 2, !"Dwarf Version", i32 4}
!202 = !{i32 2, !"Debug Info Version", i32 3}
!203 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!204 = !DILocalVariable(name: "_a", arg: 1, scope: !192, file: !1, line: 35, type: !24)
!205 = !DIExpression()
!206 = !DILocation(line: 35, column: 46, scope: !192)
!207 = !DILocalVariable(name: "p", arg: 2, scope: !192, file: !1, line: 35, type: !80)
!208 = !DILocation(line: 35, column: 62, scope: !192)
!209 = !DILocalVariable(name: "a", scope: !192, file: !1, line: 37, type: !4)
!210 = !DILocation(line: 37, column: 24, scope: !192)
!211 = !DILocation(line: 37, column: 52, scope: !192)
!212 = !DILocation(line: 37, column: 28, scope: !192)
!213 = !DILocation(line: 39, column: 2, scope: !192)
!214 = !DILocalVariable(name: "magic_test", scope: !215, file: !1, line: 39, type: !23)
!215 = distinct !DILexicalBlock(scope: !192, file: !1, line: 39, column: 2)
!216 = !DILocation(line: 39, column: 2, scope: !215)
!217 = !DILocation(line: 39, column: 2, scope: !218)
!218 = !DILexicalBlockFile(scope: !215, file: !1, discriminator: 1)
!219 = !DILocation(line: 39, column: 2, scope: !220)
!220 = !DILexicalBlockFile(scope: !221, file: !1, discriminator: 2)
!221 = distinct !DILexicalBlock(scope: !215, file: !1, line: 39, column: 2)
!222 = !DILocation(line: 39, column: 2, scope: !223)
!223 = !DILexicalBlockFile(scope: !215, file: !1, discriminator: 3)
!224 = !DILocation(line: 42, column: 6, scope: !225)
!225 = distinct !DILexicalBlock(scope: !192, file: !1, line: 42, column: 6)
!226 = !DILocation(line: 42, column: 8, scope: !225)
!227 = !DILocation(line: 42, column: 16, scope: !225)
!228 = !DILocation(line: 42, column: 19, scope: !229)
!229 = !DILexicalBlockFile(scope: !225, file: !1, discriminator: 1)
!230 = !DILocation(line: 42, column: 24, scope: !229)
!231 = !DILocation(line: 42, column: 6, scope: !229)
!232 = !DILocation(line: 43, column: 22, scope: !233)
!233 = distinct !DILexicalBlock(scope: !225, file: !1, line: 42, column: 33)
!234 = !DILocation(line: 43, column: 25, scope: !233)
!235 = !DILocation(line: 43, column: 3, scope: !233)
!236 = !DILocation(line: 45, column: 3, scope: !233)
!237 = !DILocation(line: 47, column: 7, scope: !192)
!238 = !DILocation(line: 47, column: 10, scope: !192)
!239 = !DILocation(line: 47, column: 2, scope: !192)
!240 = !DILocation(line: 48, column: 25, scope: !192)
!241 = !DILocation(line: 48, column: 18, scope: !192)
!242 = !DILocation(line: 48, column: 2, scope: !192)
!243 = !DILocation(line: 48, column: 5, scope: !192)
!244 = !DILocation(line: 48, column: 16, scope: !192)
!245 = !DILocation(line: 49, column: 6, scope: !246)
!246 = distinct !DILexicalBlock(scope: !192, file: !1, line: 49, column: 6)
!247 = !DILocation(line: 49, column: 9, scope: !246)
!248 = !DILocation(line: 49, column: 20, scope: !246)
!249 = !DILocation(line: 49, column: 6, scope: !192)
!250 = !DILocation(line: 50, column: 22, scope: !251)
!251 = distinct !DILexicalBlock(scope: !246, file: !1, line: 49, column: 29)
!252 = !DILocation(line: 50, column: 25, scope: !251)
!253 = !DILocation(line: 50, column: 3, scope: !251)
!254 = !DILocation(line: 52, column: 3, scope: !251)
!255 = !DILocation(line: 54, column: 2, scope: !192)
!256 = !DILocation(line: 55, column: 1, scope: !192)
!257 = !DILocalVariable(name: "_a", arg: 1, scope: !195, file: !1, line: 59, type: !24)
!258 = !DILocation(line: 59, column: 55, scope: !195)
!259 = !DILocalVariable(name: "client_data", arg: 2, scope: !195, file: !1, line: 59, type: !123)
!260 = !DILocation(line: 59, column: 65, scope: !195)
!261 = !DILocalVariable(name: "cb", arg: 3, scope: !195, file: !1, line: 60, type: !186)
!262 = !DILocation(line: 60, column: 34, scope: !195)
!263 = !DILocalVariable(name: "a", scope: !195, file: !1, line: 62, type: !4)
!264 = !DILocation(line: 62, column: 24, scope: !195)
!265 = !DILocation(line: 62, column: 52, scope: !195)
!266 = !DILocation(line: 62, column: 28, scope: !195)
!267 = !DILocation(line: 64, column: 2, scope: !195)
!268 = !DILocalVariable(name: "magic_test", scope: !269, file: !1, line: 64, type: !23)
!269 = distinct !DILexicalBlock(scope: !195, file: !1, line: 64, column: 2)
!270 = !DILocation(line: 64, column: 2, scope: !269)
!271 = !DILocation(line: 64, column: 2, scope: !272)
!272 = !DILexicalBlockFile(scope: !269, file: !1, discriminator: 1)
!273 = !DILocation(line: 64, column: 2, scope: !274)
!274 = !DILexicalBlockFile(scope: !275, file: !1, discriminator: 2)
!275 = distinct !DILexicalBlock(scope: !269, file: !1, line: 64, column: 2)
!276 = !DILocation(line: 64, column: 2, scope: !277)
!277 = !DILexicalBlockFile(scope: !269, file: !1, discriminator: 3)
!278 = !DILocation(line: 67, column: 27, scope: !195)
!279 = !DILocation(line: 67, column: 2, scope: !195)
!280 = !DILocation(line: 67, column: 5, scope: !195)
!281 = !DILocation(line: 67, column: 25, scope: !195)
!282 = !DILocation(line: 68, column: 30, scope: !195)
!283 = !DILocation(line: 68, column: 2, scope: !195)
!284 = !DILocation(line: 68, column: 5, scope: !195)
!285 = !DILocation(line: 68, column: 28, scope: !195)
!286 = !DILocation(line: 69, column: 2, scope: !195)
!287 = !DILocation(line: 70, column: 1, scope: !195)
!288 = !DILocalVariable(name: "a", arg: 1, scope: !198, file: !1, line: 74, type: !4)
!289 = !DILocation(line: 74, column: 54, scope: !198)
!290 = !DILocation(line: 77, column: 6, scope: !291)
!291 = distinct !DILexicalBlock(scope: !198, file: !1, line: 77, column: 6)
!292 = !DILocation(line: 77, column: 9, scope: !291)
!293 = !DILocation(line: 77, column: 20, scope: !291)
!294 = !DILocation(line: 77, column: 6, scope: !198)
!295 = !DILocation(line: 78, column: 11, scope: !291)
!296 = !DILocation(line: 78, column: 14, scope: !291)
!297 = !DILocation(line: 78, column: 3, scope: !291)
!298 = !DILocation(line: 80, column: 6, scope: !299)
!299 = distinct !DILexicalBlock(scope: !198, file: !1, line: 80, column: 6)
!300 = !DILocation(line: 80, column: 9, scope: !299)
!301 = !DILocation(line: 80, column: 29, scope: !299)
!302 = !DILocation(line: 80, column: 6, scope: !198)
!303 = !DILocalVariable(name: "p", scope: !304, file: !1, line: 81, type: !80)
!304 = distinct !DILexicalBlock(scope: !299, file: !1, line: 80, column: 38)
!305 = !DILocation(line: 81, column: 15, scope: !304)
!306 = !DILocation(line: 82, column: 7, scope: !304)
!307 = !DILocation(line: 82, column: 10, scope: !304)
!308 = !DILocation(line: 82, column: 31, scope: !304)
!309 = !DILocation(line: 82, column: 34, scope: !304)
!310 = !DILocation(line: 83, column: 7, scope: !304)
!311 = !DILocation(line: 83, column: 10, scope: !304)
!312 = !DILocation(line: 82, column: 5, scope: !304)
!313 = !DILocation(line: 84, column: 7, scope: !314)
!314 = distinct !DILexicalBlock(scope: !304, file: !1, line: 84, column: 7)
!315 = !DILocation(line: 84, column: 9, scope: !314)
!316 = !DILocation(line: 84, column: 7, scope: !304)
!317 = !DILocation(line: 85, column: 27, scope: !318)
!318 = distinct !DILexicalBlock(scope: !314, file: !1, line: 84, column: 18)
!319 = !DILocation(line: 85, column: 20, scope: !318)
!320 = !DILocation(line: 85, column: 4, scope: !318)
!321 = !DILocation(line: 85, column: 7, scope: !318)
!322 = !DILocation(line: 85, column: 18, scope: !318)
!323 = !DILocation(line: 86, column: 8, scope: !324)
!324 = distinct !DILexicalBlock(scope: !318, file: !1, line: 86, column: 8)
!325 = !DILocation(line: 86, column: 11, scope: !324)
!326 = !DILocation(line: 86, column: 22, scope: !324)
!327 = !DILocation(line: 86, column: 8, scope: !318)
!328 = !DILocation(line: 87, column: 24, scope: !329)
!329 = distinct !DILexicalBlock(scope: !324, file: !1, line: 86, column: 31)
!330 = !DILocation(line: 87, column: 27, scope: !329)
!331 = !DILocation(line: 87, column: 5, scope: !329)
!332 = !DILocation(line: 89, column: 5, scope: !329)
!333 = !DILocation(line: 91, column: 12, scope: !318)
!334 = !DILocation(line: 91, column: 15, scope: !318)
!335 = !DILocation(line: 91, column: 4, scope: !318)
!336 = !DILocation(line: 93, column: 2, scope: !304)
!337 = !DILocation(line: 94, column: 2, scope: !198)
!338 = !DILocation(line: 95, column: 1, scope: !198)
